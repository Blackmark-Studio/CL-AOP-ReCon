
//=========================================================================================
//Events
//=========================================================================================

void wdmEvent_EncounterCreate()
{
	float dltTime = GetEventData();
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	//Skip encounters
	if(CheckAttribute(&worldMap, "noenc") != 0)
	{
		if(worldMap.noenc == "true") return;
	}
	//Save player ship position
	worldMap.playerShipX = playerShipX;
	worldMap.playerShipZ = playerShipZ;
	worldMap.playerShipAY = playerShipAY;
	//DeleteAttribute(pchar, "SkipEshipIndex");// boal
	//Generate encounters
	wdmCheckReadyGoToLSC();
	wdmStormGen(dltTime, playerShipX, playerShipZ, playerShipAY);
	wdmShipEncounter(dltTime, playerShipX, playerShipZ, playerShipAY);
}


void wdmEvent_PlayerInStorm()
{
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	int stormIndex = GetEventData();
	//с Штормометром в шторм можно не идти, иначе не избежать
	if (CheckCharacterItem(pchar, "stop_storm")) LaunchMapScreen();
	else
	{
		wdmEventHandler_PlayerInStorm_EnterSeaQuestEncounter();
		wdmReloadToSea();
	}
}
void wdmEventHandler_PlayerInStorm_EnterSeaQuestEncounter()
{
	if (CheckAttribute(pchar, "questTemp.Sharp") && pchar.questTemp.Sharp == "SharpRevenge")
	{
		int numEncounters = wdmGetNumberShipEncounters();
		for(int i = 0; i < numEncounters; i++)
		{
			if(wdmSetCurrentShipData(i))
			{
				if(MakeInt(worldMap.encounter.select) == 0) continue;
				string encStringID = worldMap.encounter.id;
				if(encStringID == "") continue;
				string encStringIdPath = "encounters." + encStringID + ".encdata";
				if(CheckAttribute(&worldMap, encStringIdPath) == 0) continue;
				
				aref rEncounter;
				makearef(rEncounter, worldMap.(encStringIdPath));
				
				if (CheckAttribute(rEncounter, "CharacterID") && rEncounter.CharacterID == "Sharp")
				{
					wdmEnterSeaQuest(rEncounter.CharacterID);
					break; // > достаточно первого совпадения
				}
			}
		}
	}
}

void wdmEvent_ShipEncounter()
{
	float playerShipX = GetEventData();
	float playerShipZ = GetEventData();
	float playerShipAY = GetEventData();
	int eshipIndex = GetEventData();	
	if (CheckAttribute(pchar, "SkipEshipIndex") && pchar.SkipEshipIndex == eshipIndex) return; // boal
	if (!bWMEncounterCheck) return;
	pchar.eshipIndex = eshipIndex;
	LaunchMapScreen();

}

#event_handler("WorldMap_GetCheckEncounter", "wdmEvent_GetCheckEncounter");
bool wdmEvent_GetCheckEncounter()
{
	return bWMEncounterCheck;
}

void wdmEvent_UpdateDate()
{
	Environment.date.day = worldMap.date.day;
	Environment.date.month = worldMap.date.month;	
	Environment.date.year = worldMap.date.year;
	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = GetEventData();
}

//Добавляем по запросу квестовых энкоунтеров
#event_handler("WorldMap_AddQuestEncounters", "wdmEvent_AddQuestEncounters");
void wdmEvent_AddQuestEncounters()
{
	int idx = -1;
	string encID = "";
	string encPath = "";
	aref encs, at;
	makearef(encs, worldMap.addQuestEncounters);
	int num = GetAttributesNum(encs);
	for(int i = 0; i < num; i++)
	{
		at = GetAttributeN(encs, i);
		
		if (CheckAttribute(at, "characterID")) // boal fix 14.09.06
		{
			if(at.type == "trader")
			{
				if(!GenerateMapEncounter_Alone(at.characterID, &idx))
				{
					PostEvent("Map_TraderSucces", 100, "s", at.characterID);
					continue;
				}
				//Создаём в карте энкоунтера
				encID = "";
				if (CheckAttribute(at, "XZGoto")) // покоординатный boal 04/10/06
				{
					if(!wdmCreateMerchantShipXZByIndex(1.0, idx, &encID, stf(at.x1), stf(at.z1), stf(at.x2), stf(at.z2), sti(at.TimeOut)))
					{
						PostEvent("Map_TraderSucces", 100, "s", at.characterID);
						continue;
					}
				}
				else
				{
					if(!wdmCreateMerchantShipByIndex(1.0, idx, &encID, at.beginlocator, at.endLocator, sti(at.TimeOut)))
					{
						PostEvent("Map_TraderSucces", 100, "s", at.characterID);
						continue;
					}
				}
				//Путь до энкоунтера
				encPath = "encounters." + encID;
				//Сохраняем принадлежность к квестовым энкоунтеров
				worldMap.(encPath).quest.event = "Map_TraderSucces";
				worldMap.(encPath).quest.chrID = at.characterID;
				wdmApplyShipFX(encID); // > эффекты на только что появившийся квестовый энкаунтер
			}
			if(at.type == "warrior")
			{			
				if(!GenerateMapEncounter_Alone(at.characterID, &idx))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					continue;
				}
				//Создаём в карте энкоунтера
				encID = "";
				//if(!wdmCreateFollowShipByIndex(1.0, idx, &encID, at.beginlocator, sti(at.TimeOut)))
				if(!wdmCreateRealFollowShipByIndex(1.0, idx, &encID, sti(at.TimeOut)))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					continue;
				}
				//Путь до энкоунтера
				encPath = "encounters." + encID;
				//Сохраняем принадлежность к квестовым энкоунтеров
				worldMap.(encPath).quest.event = "Map_WarriorEnd";
				worldMap.(encPath).quest.chrID = at.characterID;
				wdmApplyShipFX(encID); // > эффекты на только что появившийся квестовый энкаунтер
			}
			if(at.type == "coolwarrior")
			{			
				if(!GenerateMapEncounter_Alone(at.characterID, &idx))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					continue;
				}
				//Создаём в карте энкоунтера
				encID = "";
				//if(!wdmCreateFollowShipByIndex(1.0, idx, &encID, at.beginlocator, sti(at.TimeOut)))
				if(!wdmCreateRealFollowShipByIndex(1.7, idx, &encID, sti(at.TimeOut)))
				{
					PostEvent("Map_WarriorEnd", 100, "s", at.characterID);
					continue;
				}
				//Путь до энкоунтера
				encPath = "encounters." + encID;
				//Сохраняем принадлежность к квестовым энкоунтеров
				worldMap.(encPath).quest.event = "Map_WarriorEnd";
				worldMap.(encPath).quest.chrID = at.characterID;
				wdmApplyShipFX(encID); // > эффекты на только что появившийся квестовый энкаунтер
			}
			if(at.type == "battle")
			{
				//wdmQuestCreateBattle(at.characterID, sti(at.iEnemyNation), sti(at.TimeOut));
			}
		}
	}
	DeleteAttribute(&worldMap, "addQuestEncounters");
	worldMap.addQuestEncounters = "";
	//Очищаем массив энкоунтеров
	ReleaseMapEncounters();
}

void wdmEvent_ShipRadiusUpdate()
{
	if(CheckAttribute(&TEV, "WDM_ShipRadiusUpdate"))
	{
		DeleteAttribute(&TEV, "WDM_ShipRadiusUpdate");
		worldMap.playerShipActionRadius = wdmGetPlayerShipActionRadius();
		worldMap.enemyShipActionRadius = wdmGetEnemyShipActionRadius();
		worldMap.stormShipActionRadius = wdmGetStormShipActionRadius();
		worldMap.shipRadiusUpdate = "";
	}
}

#event_handler("WorldMap_IsSkipEnable", "wdmIsSkipEnable");
bool wdmSkipReturnBool = false;
bool wdmIsSkipEnable()
{
	wdmSkipReturnBool = false;
	if(CheckOfficersPerk(pchar, "SailingProfessional")) //TODO del
	{
		if(rand(100) <= 50)
		{
			wdmSkipReturnBool = true;
		}
	}
	return wdmSkipReturnBool;
}



void wdmDeleteLoginEncounter(string encID)
{
	Event("WorldMap_EncounterDelete", "s", encID);
}

#event_handler("WorldMap_EncounterDelete", "wdmEncounterDelete");
ref wdmEncounterDelete()
{
	BI_intRetValue = true;

	string encID = GetEventData();
	string encPath = "encounters." + encID;
	if(CheckAttribute(&worldMap, encPath) == 0)
	{
		return &BI_intRetValue;
	}
	aref enc;
	makearef(enc, worldMap.(encPath));
	//Сохраняем событие
	bool needEvent = false;
	string eventName = "";
	string chrID = "";
	if(CheckAttribute(enc, "quest.chrID"))
	{
    //homo 14/04/07 не ясно если энкоутер ещё не доплыл до пункта назанчения значит его нельзя тереть?
    //Даже если его трет программист?
    	if(CheckAttribute(&enc, "Gotox") && CheckAttribute(&enc, "Gotoz"))
		{

			float fDeltaX = (stf(enc.x) - stf(enc.Gotox));
			float fDeltaZ = (stf(enc.z) - stf(enc.Gotoz));
			float fRadSqr = fDeltaX*fDeltaX + fDeltaZ*fDeltaZ;
			if( fRadSqr > 100.0 && stf(enc.livetime) > 1.0) 
			{
				BI_intRetValue = false;
				//return &BI_intRetValue;   убрал
			}
		}

		if(CheckAttribute(enc, "quest.event") != 0)
		{
			eventName = enc.quest.event;
			chrID = enc.quest.chrID;
			needEvent = true;
		}
		/*else
		{
			return &BI_intRetValue;
		}*/
	}
	//Отмечаем, что удалён
	enc.needDelete = "wdmEncounterDelete";
	//Удаляем квестовую пометку
	DeleteAttribute(&enc, "quest");
	if (!IsEntity(&worldMap))
	{
	   //Трем сам энкаутер сразу homo 10/04/07
        DeleteAttribute(&worldMap, encPath);
    }
	//Отправляем квестовый эвент, если надо
	if(needEvent)
	{
		PostEvent(eventName, 100, "s", chrID);
	}
	return &BI_intRetValue;
}

#event_handler("WorldMap_GetMoral", "wdmGetMoral");
float wdmGetMoral()
{
	int iMorale = 0;
	int cn = -1;
	int iRealCompNum = 0;
	for(int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			iMorale = iMorale + GetCharacterCrewMorale(&characters[cn]);
			iRealCompNum++;
		}
	}
	iMorale = iMorale / iRealCompNum;
	return stf(iMorale);
}

#event_handler("WorldMap_GetFood", "wdmGetFood");
float wdmGetFood()
{
	return makefloat(CalculateFood());
}

#event_handler("WorldMap_GetRum", "wdmGetRum");
float wdmGetRum()
{
	return makefloat(CalculateShipRum(pchar));
}

//  квестовый отлов входа в море по начилию НПС в случайке
void wdmEnterSeaQuest(string _chrId)
{
	ref NPChar = characterFromID(_chrId);
	
	/*if (HasSubStr(_chrId, "Hunter0")) // ОЗГи > убираем все записи в СЖ по ним
	{
		CloseQuestHeader("HeadHunter");
		AddQuestRecord("HeadHunter", "HeadHunter_Sea");
		AddQuestUserData("HeadHunter", "sSex", GetSexPhrase("ся","ась"));
		AddQuestUserData("HeadHunter", "sNation", NationNameGenitive(sti(NPChar.Nation)));
	}*/
	
	if (HasSubStr(_chrId, "GhostCapt")) // GhostCapt
	{
		AddQuestRecord("GhostShipQuest", "3_1");
	}
		// homo 19/07/06 GlodFleet
	if (_chrId == "Head_of_Gold_Squadron")
	{
        string sQuest = "GoldFleetEncounter";
        pchar.quest.(sQuest).win_condition.l1 = "EnterToSea";  // fix homo 20/01/07
        pchar.quest.(sQuest).function = "GoldFleetEncounter";
	}
	//homo 27/09/06
	if (HasSubStr(_chrId, "SiegeCap_1"))// Осаждающая эскадра
	{
        SiegeSquadronOnMap(_chrId);
	}
	//пиратка, квест №7. фрегат Леон
	if (_chrId == "LeonCapitain") 
	{
		AddQuestRecord("Pir_Line_7_Soukins", "15");
	}
	//пиратка, квест №7. Баттлшип найден
	if (_chrId == "QuestCap_PL7")
	{
		AddQuestRecord("Pir_Line_7_Soukins", "11");
		pchar.questTemp.piratesLine = "Soukins_battlshipFound";
		//Map_ReleaseQuestEncounter("QuestCap_PL7");
		pchar.quest.PQ7_BattleShip_notFound.over = "yes";
        pchar.quest.PQ7_winBattleShip.win_condition.l1 = "Group_Death";
		pchar.quest.PQ7_winBattleShip.win_condition.l1.group = "Quest_Ship";
		pchar.quest.PQ7_winBattleShip.function = "PQ7_winBattleShip";
	}
	//жемчужный генератор Шарпа
	if (_chrId == "Sharp")
	{
		int iSharpIdx = GetCharacterIndex(_chrId);
		if (iSharpIdx != -1) characters[iSharpIdx].nation = pchar.nation;
		
		if (CheckAttribute(pchar, "questTemp.Sharp") && pchar.questTemp.Sharp == "SharpRevenge")
		{
			pchar.quest.SharpRevengeEncounter.win_condition.l1 = "EnterToSea";
			pchar.quest.SharpRevengeEncounter.function = "SeaPearl_SharpRevenge_AtLoginSharp";
			
			pchar.quest.SharpRevengeEncounter_Death.win_condition.l1 = "Group_Death";
			pchar.quest.SharpRevengeEncounter_Death.win_condition.l1.group = "Sharp_Group";
			pchar.quest.SharpRevengeEncounter_Death.function = "SeaPearl_SharpRevenge_AfterBattle";
			
			int numEncounters = wdmGetNumberShipEncounters();
			
			for(int i = 0; i < numEncounters; i++)
			{
				//Получим информацию о данном энкоунтере
				if(wdmSetCurrentShipData(i))
				{
					//Если не активен, то пропустим его
					if(MakeInt(worldMap.encounter.select) == 0) continue;
					//Добавляем информацию об морских энкоунтере
					string encStringID = worldMap.encounter.id;
					if(encStringID == "") continue;
					string encStringIdPath = "encounters." + encStringID + ".encdata";
					if(CheckAttribute(&worldMap, encStringIdPath) == 0) continue;
					
					aref rEncounter;
					makearef(rEncounter, worldMap.(encStringIdPath));
					
					if (!CheckAttribute(rEncounter, "CharacterID") || rEncounter.CharacterID != "Sharp")
					{
						wdmDeleteLoginEncounter(encStringID);
					}
				}
			}
			worldMap.deleteUpdate = "";
			worldMap.playerInStorm = 0;
		}
	}
}

//Попадание в ГПК
void wdmCheckReadyGoToLSC()
{
	if (!CheckAttribute(pchar, "quest.EnterToSeaLSC")) return; //нет атрибута, нет катсцены

    int indexLSC = FindIsland("LostShipsCity");
    float X1 = makefloat(worldMap.playerShipX)+1000;
    float Z1 = -makefloat(worldMap.playerShipZ)+980;
    string sColonyIslandID = Islands[indexLSC].id;
    float X2 = makefloat(worldMap.islands.(sColonyIslandID).position.x)+1000;
    float Z2 = -makefloat(worldMap.islands.(sColonyIslandID).position.z)+1000;

    int distanceToLSC = makeint(GetDistance2D(X1, Z1, X2, Z2));
    if (distanceToLSC >= 70) return; //если далеко, то рано кораблекрушить

    if (!CheckAttribute(&TEV,"stormLSC"))
    {
        int charIndex;
        int i;
        //проверяем можно ли пускать игрока в ГПК
        for (i = 1; i < COMPANION_MAX; i++)
        {
            charIndex = GetCompanionIndex(pchar, i);
            if (charIndex != -1 && !GetRemovable(&characters[charIndex]))
            {
                TEV.waitingForConditionsLSC = true;
            }
        }
        for (i = 0; i < PASSENGERS_MAX; i++)
        {
            charIndex = GetPassenger(pchar, i);
            if (charIndex != -1 && or(!GetRemovable(&characters[charIndex]), LAi_IsImmortal(&characters[charIndex])))
            {
                TEV.waitingForConditionsLSC = true;
            }
        }
        //если не готовы, то в ГПК не идём
        if (CheckAttribute(&TEV, "waitingForConditionsLSC"))
        {
            Log_Info(StringFromKey("InfoMessages_215"));
            Islands[indexLSC].reload_enable = false;
            SetTimerCondition("WaitingForConditionsLSC", 0, 0, 1, false);
            return;
        }

        TEV.stormLSC = true;
        SendMessage(&worldMap, "ll", MSG_WORLDMAP_CLEARSTORM, true);
        DoQuestFunctionDelay("EnterToStormLSC", 7);
    }
    SendMessage(&worldMap, "ll", MSG_WORLDMAP_CREATESTORM, true);
}
//подготовка к бою, клонирование локаций, инит аи и прочее
//------- СУША ----------
void Duel_Prepare_Fight()
{
	DeleteAttributeEx(&TEV, "Music.KeepPlaying,Music.ForceKeepPlaying");
	ResetSound();	
	int i, iTemp;
	string sModel;
	ref npchar, rLoc, sld;

	npchar = CharacterFromID(pchar.questTemp.duel.enemy);

	DeleteAttribute(npchar, "City"); // чтоб не было ругани с нацией

	if (CheckAttribute(npchar, "LifeDay") && npchar.LifeDay >= 0)
	{
		npchar.LifeDay = sti(npchar.LifeDay) + 2;
	}
	
	if (CheckAttribute(LoadedLocation, "type") && LoadedLocation.type == "tavern")
	{
		LAi_SetPlayerType(pchar);
		LAi_PlaceCharInTavern(pchar);
		npchar.location = "Clone_location";
//		LAi_PlaceCharInTavern(npchar); // не работает - перенёс в прерывание
		PChar.Quest.Duel_Fight_Right_Now.win_condition.l1 = "Location";
		PChar.Quest.Duel_Fight_Right_Now.win_condition.l1.Location = "Clone_location";
		PChar.Quest.Duel_Fight_Right_Now.function = "Duel_Fight_Right_Now";
		
		LocationMakeClone(pchar.location);
		Locations[FindLocation("Clone_location")].image = "loading\tavern_fight.tga";
		LAi_LocationDisableOfficersGen("Clone_location", true); //офицеры не участвуют
		DoReloadCharacterToLocation("Clone_location", pchar.location.group, pchar.location.locator);

		arrayNPCModelHow = 1;
		arrayNPCModel[0] = npchar.model; //вот я подзапарился, да? а то чо это мы клонов на дуэлях встречам
		if (CheckAttribute(PChar,"questTemp.duel.enemyQty")) // если не один
		{
			iTemp = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE);
			bool pirate_town = false;
			if (CheckAttribute(LoadedLocation, "townsack") && GetCityNation(LoadedLocation.townsack) == PIRATE)
			{
				i = FindColony(LoadedLocation.townsack);
				if (i > -1)
				{
					rLoc = GetColonyByIndex(i);
					if (!sti(rLoc.HeroOwn))
						pirate_town = true;
				}
			}
			for (i = 0; i < sti(PChar.questTemp.duel.enemyQty); i++)
			{
				if (pirate_town) sModel = RandPirCitizenModel();
				else sModel = RandCitizenModel();
				sld = GetCharacter(NPC_GenerateCharacter("Berglar_Duel_"+i, sModel, "man", "man", iTemp, PIRATE, 1, true));
				SetNPCModelUniq(sld, GetModelType(sModel), MAN);
				sld.location = "Clone_location";
//				LAi_PlaceCharInTavern(sld); не работает - перенёс в прерывание
				SetFantomParamHunter(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "DUEL_FIGHTER");
			}
		}
	}
	else
	{
//		DoQuestCheckDelay("Duel_Fight_Right_Now", 0.5);
		DoQuestFunctionDelay("Duel_Fight_Right_Now", 0.5);
	}

	if (GetCharacterEquipByGroup(npchar, BLADE_ITEM_TYPE) == "")
	{
		Log_TestInfo(npchar.id + " has no blade.");
		//TODO: параметры у него должны быть вне зависимости от наличия меча, 
		//иначе моряки и перцы в пиратских тавернах могут быть в среднем слабее пьяни в городах
		SetFantomParamHunter(npchar);
	}

	LAi_SetWarriorType(npchar);
	LAi_group_MoveCharacter(npchar, "DUEL_FIGHTER");
}

//поместить оппонента за пределы города, чтобы ждал ГГ
void Duel_Move_Opponent2Place(string qName)
{
	ref npchar, sld;
	aref arAll;
	string sTemp, attrName;

	npchar = CharacterFromID(pchar.questTemp.duel.enemy);
    
	if (GetQuestPastTimeParam("questTemp.Duel.StartTime") < sti(pchar.questTemp.Duel.WaitTime))
	{
		DeleteAttribute(pchar, "quest.duel_move_opponent2place.over");
		pchar.quest.Duel_CheckSituation.win_condition.l1 = "ExitFromLocation";
		pchar.quest.Duel_CheckSituation.win_condition.l1.location = pchar.location;
		pchar.quest.Duel_CheckSituation.function = "Duel_CheckSituation";
		return;
	}

	if (GetQuestPastTimeParam("questTemp.Duel.StartTime") >= sti(pchar.questTemp.Duel.WaitTime) + 1)
	{
		pchar.questTemp.Duel.Coward = true;
		return;
	}

	npchar.Dialog.CurrentNode = "talk_off_town";

	sTemp = LAi_FindRandomLocator("encdetector");
	attrName = "locators." + sTemp;
	sld = &Locations[FindLocation(pchar.questTemp.duel.place)];
	makearef(arAll, sld.(attrName));
	attrName = GetAttributeName(GetAttributeN(arAll, rand(0)));
	ChangeCharacterAddressGroup(npchar, pchar.questTemp.duel.place, sTemp, attrName);
	//прерывание на попадание в локатор
	pchar.quest.Duel_Talk_Off_Town.win_condition.l1        = "locator";
	pchar.quest.Duel_Talk_Off_Town.win_condition.l1.location = sld.id;
	pchar.quest.Duel_Talk_Off_Town.win_condition.l1.locator_group = "Encdetector";
	pchar.quest.Duel_Talk_Off_Town.win_condition.l1.locator = sTemp;
	pchar.quest.Duel_Talk_Off_Town.function = "Duel_Talk_Off_Town";
	pchar.quest.Duel_Talk_Off_Town.EncQty = 1;
	pchar.quest.Duel_Talk_Off_Town.LocIdx = sld.index;

	//чтобы не сидел, а стоял на месте
	LAi_SetGuardianType(npchar);
	//после дуэли разрешаем офицерам заход в локу
	LAi_LocationDisableOfficersGen(pchar.questTemp.duel.place, false);
	DeleteAttribute(&locations[FindLocation(pchar.questTemp.duel.place)], "DisableEncounters");
}

void Duel_CheckSituation(string qName)
{
	if (CheckAttribute(pchar, "questTemp.Duel.End")) return;
	if (GetQuestPastTimeParam("questTemp.Duel.StartTime") >= sti(pchar.questTemp.Duel.WaitTime))
	{
		if (GetQuestPastTimeParam("questTemp.Duel.StartTime") >= sti(pchar.questTemp.Duel.WaitTime)+1)
		{
			pchar.quest.duel_move_opponent2place.over = "yes";
			pchar.questTemp.Duel.End = true;
		}
		else
		{
			DoQuestFunctionDelay("Duel_Move_Opponent2Place", 2.0);
		}
	}
}

//по входу в локатор, последний разговор перед боем
void Duel_Talk_Off_Town(string qName)
{	
	ref sld;
	sld = CharacterFromID(pchar.questTemp.duel.enemy);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

//начать дуэль!
void Duel_Fight_Right_Now(string qName)
{
	bool bOk = false;
	int i, chIdx = 0;
	ref sld;

	if (CheckAttribute(LoadedLocation, "type") && LoadedLocation.type == "clone")
	{
		if (CheckAttribute(PChar,"questTemp.duel.enemy"))
		{
			sld = CharacterFromID(pchar.questTemp.duel.enemy);
			LAi_PlaceCharInTavern(sld);
		}
		if (CheckAttribute(PChar,"questTemp.duel.enemyQty")) // если не один
		{
			for (i = 0; i < sti(PChar.questTemp.duel.enemyQty); i++)
			{
				chIdx = GetCharacterIndex("Berglar_Duel_"+i);
				if (chIdx != -1)
				{
					LAi_PlaceCharInTavern(&Characters[chIdx]);
				}
			}
		}
	}

	sld = &Locations[FindLocation(pchar.location)];
	//запоминаем запрет на оружие в локации
	if (CheckAttribute(sld, "noFight"))
	{
		bOk = sti(sld.noFight);
	}
	if (bOk)
	{
		LAi_LocationFightDisable(sld, !bOk);
		pchar.questTemp.LocFightEnable = bOk;
	}
	//достать саблю
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("DUEL_FIGHTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("DUEL_FIGHTER", LAI_GROUP_PLAYER, true);

	SetEventHandler("LAi_event_GroupKill", "Duel_Kill_Enemy", 0);
	LAi_group_SetCheckEvent("DUEL_FIGHTER");
	PChar.questTemp.Duel.Enemy.GrpId = "DUEL_FIGHTER";
}

//убили противника
void Duel_Kill_Enemy()
{
	ref sld;
	string sGroup = GetEventData();
	if (sGroup != PChar.questTemp.Duel.Enemy.GrpId) return;

    DelEventHandler("LAi_event_GroupKill", "Duel_Kill_Enemy");
	//репутация в плюс
	//ChangeCharacterReputationABS(pchar, 5.0);
	//убираем из локации, чтобы не респаунился.
	pchar.quest.Duel_Clear_Enemy.win_condition.l1 = "ExitFromLocation";
	pchar.quest.Duel_Clear_Enemy.win_condition.l1.location = pchar.location;
	pchar.quest.Duel_Clear_Enemy.function = "Duel_Clear_Enemy";
	
	// считаем общее кол-во дуэлей
	if(CheckAttribute(PChar,"questTemp.duelQty")) 	
	{	
		pchar.questTemp.duelQty = sti(pchar.questTemp.duelQty) + 1;
		if(sti(pchar.questTemp.duelQty) == 7 + rand(2))
		{
			SetCharacterPerk(pchar, "Bully"); // дуэлянта посылаем нафик в таверне 2 месяца
			SetTimerCondition("HabitueSpeakDisable_End", 0, 2, rand(10), false);
		}
	}	
	else pchar.questTemp.duelQty = 1;
	
	if(CheckAttribute(PChar,"questTemp.duel.enemyQty")) DeleteAttribute(PChar,"questTemp.duel.enemyQty");	
	//восстанавливаем запрет на оружие, если был
	if (CheckAttribute(pchar, "questTemp.LocFightEnable") && sti(pchar.questTemp.LocFightEnable))
	{
		sld = &Locations[FindLocation(pchar.location)];
		LAi_LocationFightDisable(sld, true);
		DeleteAttribute(pchar, "questTemp.LocFightEnable");
	}

	//если в локации клоне, то объясняем куда все делись
	if (CheckAttribute(pchar, "questTemp.LocationClone") && sti(pchar.questTemp.LocationClone))
	{
		DoQuestCheckDelay("TalkSelf_Start", 0.2);
		LAi_LocationDisableOfficersGen("Clone_location", false); //офицерам уже можно
	}

	//убрать оружие, нефиг
	DoQuestCheckDelay("hide_weapon", 2.0);
	//статистика
	if (Statistic_AddValue(PChar, "DuelKills", 1) > 20)
	{
		//и слухи
		AddTemplRumour("DuelHero", id_counter+1) ;
	}

	DoQuestFunctionDelay("Duel_Fight_End", 0.5);
}

void Duel_Fight_End(string qName)
{
	if (Number_Group_People("DUEL_FIGHTER", 0) <= 0)
		LAi_group_Delete("DUEL_FIGHTER");
}

//убираем тело из локации, а то зомби будет...
void Duel_Clear_Enemy(string qName)
{
	ref sld = characterFromID(pchar.questTemp.duel.enemy);
	if (CheckAttribute(PChar, "questTemp.duel.Start") && sti(PChar.questTemp.duel.Start))
	{
		//чтобы репу не понизили
		sld.Duel.End = true;
		//чтобы не вернулся
		sld.BackUp.location = "None";
		sld.BackUp.location.group = "";
		sld.BackUp.location.locator = "";
	}
	//и убрать из локации
	ChangeCharacterAddressGroup(sld, "None", "", "");
}

//вернуть оппонента назад, где был с его параметрами. Если ГГ не приходил, минус в репу!
void Duel_Move_OpponentBack(string qName)
{
	ref npchar = CharacterFromID(pchar.questTemp.duel.enemy);

    LAi_LocationDisableOfficersGen(pchar.questTemp.duel.place, false);
	if (!CheckAttribute(pchar, "questTemp.Duel.End") || CheckAttribute(pchar, "questTemp.Duel.Coward"))
	{
		ChangeCharacterReputationABS(pchar, -5.0);
		AddTemplRumour("DuelCoward", id_counter+1);
	}

	if (CheckAttribute(npchar, "BackUp"))
	{
		ChangeCharacterAddressGroup(npchar, npchar.BackUp.location, npchar.BackUp.location.group, npchar.BackUp.location.locator);
		npchar.Dialog.CurrentNode = npchar.BackUp.DialogNode;
		if (sti(npchar.PGGAi))
			npchar.PGGAi.location.town = npchar.BackUp.town;
	}
	DeleteAttribute(&locations[FindLocation(pchar.questTemp.duel.place)], "DisableEncounters");
	//чистим аттрибуты
	Log_TestInfo("Duel: POST CHECK!");
	if (CheckAttribute(pchar, "quest.duel_move_opponent2place"))
	{
	    pchar.quest.duel_move_opponent2place.over = "yes";
	}
	if (CheckAttribute(pchar, "quest.Duel_CheckSituation"))
	{
	    pchar.quest.Duel_CheckSituation.over = "yes";
	}
	if (CheckAttribute(pchar, "quest.Duel_Talk_Off_Town"))
	{
	    pchar.quest.Duel_Talk_Off_Town.over = "yes";
	}
	DeleteAttribute(pchar, "questTemp.Duel");
	DeleteAttribute(npchar, "BackUp");
}

//------- Море -------
void Duel_Sea_Prepare()
{
	string sTemp = "DUEL_SEA";
	ref NPChar = characterFromID(pchar.questTemp.duel.enemy);
	//
	//TODO: Нужно убрать все малусы за тех у кого аттрибут AlwaysEnemy = true
	//		это квестовые персы...
	NPChar.AlwaysEnemy = true;		  
	NPChar.Coastal_Captain = true;  // не ругать нации
	NPChar.Abordage.Enable = false;
	NPChar.Nation.Bak = NPChar.Nation;
	NPChar.Nation = GetCityNation(GetCurrentTown());
	SetCharacterRelationBoth(sti(pchar.index), sti(npchar.index), RELATION_ENEMY);

	Group_AddCharacter(sTemp, npchar.id);
	Group_SetGroupCommander(sTemp, npchar.id);
	Group_SetAddress(sTemp, pchar.questTemp.Duel.Sea_Location, "Quest_Ships", "Quest_Ship_3");

	pchar.quest.Duel_Sea_Start.win_condition.l1 = "location";
	pchar.quest.Duel_Sea_Start.win_condition.l1.location = pchar.questTemp.Duel.Sea_Location;
	pchar.quest.Duel_Sea_Start.function = "Duel_Sea_Start";
}

void Duel_Sea_Start(string qName)
{
	string sTemp = "DUEL_SEA";
	Group_SetTaskAttackEx(sTemp, PLAYER_GROUP, false);
	Group_LockTask(sTemp);

	PChar.Quest.Duel_Sea_End.win_condition.l1 = "Group_Death";
	PChar.Quest.Duel_Sea_End.win_condition.l1.group = sTemp;
	PChar.Quest.Duel_Sea_End.function = "Duel_Sea_End";
}

void Duel_Sea_End(string qName)
{
	ref sld;
	sld = characterFromID(PChar.questTemp.duel.enemy);
	sld.Nation = sld.Nation.Bak;
	sld.Abordage.Enable = true;
	DeleteAttribute(PChar, "questTemp.duel");
	Group_DeleteGroup("DUEL_SEA");
}

//=========== слухи ================
void OnInit_DuelCoward(ref rTmpl)
{
	object oPrm;

	oPrm.Name = GetFullName(pchar);
	ttttstr = GetAssembledString(ttttstr, &oPrm);
}

string Event_DuelHero(ref rRum)
{
	object oPrm;

	oPrm.Name = GetFullName(pchar);
	oPrm.Kill = Statistic_AddValue(pchar, "DuelKills", 0);
	return GetAssembledString(rRum.text, &oPrm);
}

//=========== диалоги ================
//случайный порядок фраз ответа
void MakeRandomLinkOrderTwo(aref link, string l1, string l1_go, string l2, string l2_go)
{
	link.l1 = l1;
	link.l1.go = l1_go;
	link.l2 = l2;
	link.l2.go = l2_go;
	if (rand(1))
	{
		link.l1 = l2;
		link.l1.go = l2_go;
		link.l2 = l1;
		link.l2.go = l1_go;
	}
}
//шесть вариантов %)
void MakeRandomLinkOrderThree(aref link, string l1, string l1_go, string l2, string l2_go, string l3, string l3_go)
{
	switch (rand(5))
	{
	case 0:
		link.l1 = l1;
		link.l1.go = l1_go;
		link.l2 = l2;
		link.l2.go = l2_go;
		link.l3 = l3;
		link.l3.go = l3_go;
		break;

	case 1:
		link.l1 = l1;
		link.l1.go = l1_go;
		link.l2 = l3;
		link.l2.go = l3_go;
		link.l3 = l2;
		link.l3.go = l2_go;
		break;

	case 2:
		link.l1 = l2;
		link.l1.go = l2_go;
		link.l2 = l1;
		link.l2.go = l1_go;
		link.l3 = l3;
		link.l3.go = l3_go;
		break;

	case 3:
		link.l1 = l2;
		link.l1.go = l2_go;
		link.l2 = l3;
		link.l2.go = l3_go;
		link.l3 = l1;
		link.l3.go = l1_go;
		break;

	case 4:
		link.l1 = l3;
		link.l1.go = l3_go;
		link.l2 = l1;
		link.l2.go = l1_go;
		link.l3 = l2;
		link.l3.go = l2_go;
		break;

	case 5:
		link.l1 = l3;
		link.l1.go = l3_go;
		link.l2 = l2;
		link.l2.go = l2_go;
		link.l3 = l1;
		link.l3.go = l1_go;
		break;
	}
}

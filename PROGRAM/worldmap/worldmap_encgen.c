//--------------------------------------------------------------------------------------
//Генерация энкаунтеров
//--------------------------------------------------------------------------------------

//Частота штормов в секунду
#define WDM_STORM_RATE   		0.0001
//Частота торговцев в секунду
#define WDM_MERCHANTS_RATE		0.09
//Частота воюищих кораблей в секунду
#define WDM_WARRING_RATE		0.015
//Частота нападающих кораблей в секунду
#define WDM_FOLLOW_RATE  		0.025
//Частота специальных событий  (бочка или шлюпка) в секунду
#define WDM_SPECIAL_RATE  		0.002

//MAX, это поменял Я!!!!!!! Шуршунчик.
//Boal - учите мат. часть, г-н Шуршунчик. не работает это до начала новой игры, всегда по уполчанию идет. Дефайн правильно, тем более  iEncountersRate далее работает
//float WDM_FOLLOW_RATE = 0.025 * iEncountersRate;
//float WDM_STORM_RATE = 0.0001 * iEncountersRate;

float wdmTimeOfLastStorm = 0.0;
float wdmTimeOfLastMerchant = 0.0;
float wdmTimeOfLastWarring = 0.0;
float wdmTimeOfLastFollow = 0.0;
float wdmTimeOfLastSpecial = 0.0;

void wdmReset()
{
	wdmTimeOfLastStorm = 0.0;
	wdmTimeOfLastMerchant = 0.0;
	wdmTimeOfLastWarring = 0.0;
	wdmTimeOfLastFollow = 0.0;
	wdmTimeOfLastSpecial = 0.0;
}

//Storm
void wdmStormGen(float dltTime, float playerShipX, float playerShipZ, float playerShipAY)
{
	if(CheckAttribute(pchar,"worldmapencountersoff") == 1)
	{
		if(sti(pchar.worldmapencountersoff)) return;
	}
	int numStorms = wdmGetNumberStorms();
	if(numStorms < 1)
	{
		wdmTimeOfLastStorm = wdmTimeOfLastStorm + dltTime*WDM_STORM_RATE*1000.0*iEncountersRate;
		if(rand(1001) < wdmTimeOfLastStorm)
		{
			wdmCreateStorm();
			wdmTimeOfLastStorm = 0.0;
		}
	}else{
		wdmTimeOfLastStorm = 0.0;
	}
}

//Random ships
void wdmShipEncounter(float dltTime, float playerShipX, float playerShipZ, float playerShipAY)
{
	int numShips = wdmGetNumberShipEncounters();
	if( CheckAttribute(pchar,"worldmap.shipcounter") ) {
		numShips = numShips - sti(pchar.worldmap.shipcounter);
	}
	if( numShips < 0 )
	{
//		trace("Warning! World map ship quantity < 0 : numShips = " + numShips);
//		trace("pchar.worldmap.shipcounter = " + pchar.worldmap.shipcounter);
		numShips = 0;
	}
	if(numShips < 8)
	{
		//Вероятности появления
		wdmTimeOfLastMerchant = wdmTimeOfLastMerchant + dltTime*WDM_MERCHANTS_RATE*1000.0*iEncountersRate;
		wdmTimeOfLastWarring = wdmTimeOfLastWarring + dltTime*WDM_WARRING_RATE*1000.0*iEncountersRate;
		wdmTimeOfLastFollow = wdmTimeOfLastFollow + dltTime*WDM_FOLLOW_RATE*1000.0*iEncountersRate;
		wdmTimeOfLastSpecial = wdmTimeOfLastSpecial + dltTime*WDM_SPECIAL_RATE*1000.0*iEncountersRate;
		//Вероятность от количества созданных
		//Выбираем
		if(rand(1001) + 1 < wdmTimeOfLastMerchant)
		{
			wdmTimeOfLastMerchant = 0.0;
			wdmCreateMerchantShip(0.8 + rand(10)*0.03);
		}
		else
		{
			bool encoff = false;
			if(CheckAttribute(pchar,"worldmapencountersoff") == 1)
			{
				encoff = sti(pchar.worldmapencountersoff);
			}
			if(encoff == false)
			{
				if(rand(1001) + 1 < wdmTimeOfLastWarring)
				{
					wdmTimeOfLastWarring = 0.0;
					wdmCreateWarringShips();
				}
				else
				{
					if(rand(1001) + 1 < wdmTimeOfLastFollow)
					{
						wdmTimeOfLastFollow = 0.0;
						if(!IsStopMapFollowEncounters())
						{
							wdmCreateFollowShip(0.8 + rand(10)*0.05);
						}						
					}
				}
				if(rand(1001) + 1 < wdmTimeOfLastSpecial)
				{
					wdmTimeOfLastSpecial = 0.0;
					wdmCreateSpecial(0.05 + rand(10)*0.02);
				}					
			}
		}
	}
	else
	{
		wdmTimeOfLastMerchant = 0.0;
		wdmTimeOfLastWarring = 0.0;
		wdmTimeOfLastFollow = 0.0;
		wdmTimeOfLastSpecial = 0.0;
	}
}


#event_handler("Map_TraderSucces", "Map_TraderSucces");
#event_handler("Map_WarriorEnd", "Map_WarriorEnd");
// TODO -->
void Map_WarriorEnd()
{
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		return;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	if(sti(pchar.worldmap.shipcounter) < 0)
	{
		pchar.worldmap.shipcounter = 0;
	}

	string sChar = GetEventData();
	//нападение Шарпа
	if (sChar == "Sharp")
	{
		Log_TestInfo("Шарпоносец устал за вами гнаться.");
	}
}
void Map_TraderSucces()
{
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{		
		return;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	if(sti(pchar.worldmap.shipcounter) < 0)
	{
		pchar.worldmap.shipcounter = 0;
	}
	string sChar = GetEventData();

	Map_TraderSucces_quest(sChar); //обработка квестов по поиску кэпов

	//homo 03/08/06 Наводка на купца
	if (HasSubStr(sChar, "_QuestMerchant"))
	{
        Map_ReleaseQuestEncounter(sChar);
        Group_DeleteGroup("Sea_"+sChar);
        CloseQuestHeader("MerchantOnMap");
	}
    // homo 07/10/06 GoldFleet
    if (sChar == "Head_of_Gold_Squadron")
	{
        RouteGoldFleet();
	}
	
	if (HasSubStr(sChar, "SiegeCap_"))
	{
        SiegeProgress();
	}
	/*if(GetCharacterIndex(sChar) != -1)  // типа пример
	{
		if(CheckAttribute(&characters[GetCharacterIndex(sChar)], "hovernor"))
		{
			if(sti(characters[GetCharacterIndex(sChar)].hovernor) == 1)
			{
				//  TODO MakeNewCapital(sChar);
				return;
			}
		}
	}
	else
	{
		trace("Can't find character with character id " + sChar);
		return;
	}

	if(sChar == "Head of Gold Squadron")
	{
		PrepareContinueGoldConvoy();
		return;
	}
	if(CheckAttribute(&characters[GetCharacterIndex(sChar)], "mapEnc.quest"))
	{
		int iQuest = sti(characters[GetCharacterIndex(sChar)].mapEnc.quest);
		string sQuest = "sink_ship_character_" + sChar + "_wait_before_travel";
		pchar.quest.(sQuest).win_condition.l1 = "timer";
		pchar.quest.(sQuest).win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
		pchar.quest.(sQuest).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
		pchar.quest.(sQuest).win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
		pchar.quest.(sQuest).win_condition.l1.date.hour = rand(23);
		pchar.quest.(sQuest).win_condition = "sink_ship_travel";
		pchar.quest.(sQuest).quest = iQuest;

		return;
	}  */
}

void Map_TraderSucces_quest(string sChar)
{
	if (GetCharacterIndex(sChar) < 0)
		return;
	
	ref character = CharacterFromID(sChar);
	
	// Линейка ле Баска. Третий квест.
if (sChar == "Esteban_Molina")
{
	if (!CheckAttribute(pchar, "questTemp.AoP.LaPalomaOutcome"))
	{
		ref sldLB;
		pchar.questTemp.AoP.LaPalomaOutcome = "escaped";
		pchar.quest.LaPaloma_ShipSink.over = "yes";
		AddQuestRecord("Hunting_huntsman", "2");
		CloseQuestHeader("Hunting_huntsman");
		LocatorReloadEnterDisable("Bucaneer_Outpost", "reload6_back", true); // закрыть дом ле Баска
		sldLB = characterFromId("Etien_Marso");
		sldLB.lifeday = 0;
		sldLB = characterFromId("Gaspar_Leru");
		RemoveLandQuestmark_Main(sldLB, "Hunting_huntsman");
		sldLB.lifeday = 0;
		Map_ReleaseQuestEncounter("Esteban_Molina");
		group_DeleteGroup("LaPaloma_Group");
		RemoveMapQuestMark("Havana_town", "Hunting_huntsman"); // убрать метку острова
		// снять квестовые локи с Рималье
		DeleteAttribute(pchar, "questTemp.Brides_Tortuga.RimalierDismissLocked");
		sldLB = characterFromId("Rimalier");
		SetCharacterRemovable(sldLB, true);
	}
}

	//пиратка, квест №7
	if (sChar == "LeonCapitain")
	{
		pchar.questTemp.piratesLine = "Soukins_LeonNotFound";
		//HardCoffee ref Morgan's dialogue
		//QuestSetCurrentNode("Henry Morgan", "PL_Q7_LeonNotFound"); //нода, ничего не узнал
		pchar.QuestTemp.PirLine_quests_task = "PL_Q7_AboutLiney";
		AddQuestRecord("Pir_Line_7_Soukins", "14");
		Log_TestInfo("Фрегат Леон удален.");
		Map_ReleaseQuestEncounter("LeonCapitain");
		group_DeleteGroup("Leon_Group");
	}
	//пиратка, квест №7
	if (sChar == "QuestCap_PL7")
	{
		pchar.questTemp.piratesLine = "Soukins_battlshipNotFound";
		AddQuestRecord("Pir_Line_7_Soukins", "12");
		AddQuestUserData("Pir_Line_7_Soukins", "sSex", GetSexPhrase("","а"));
		Log_TestInfo("Энкаунтер баттлшипа удален.");
		Map_ReleaseQuestEncounter("QuestCap_PL7");
		group_DeleteGroup("Quest_Ship");
		AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
	}
	
	// Warship 08.07.09 Пасхалка с бригантиной Мэри Селест
	if(sChar == "MaryCelesteCapitan")
	{
		Map_ReleaseQuestEncounter("MaryCelesteCapitan");
		
		// Для палубы, при Map_ReleaseQuestEncounter() рассылалось событие, а ставить ещё раз не нужно
		if(PChar.QuestTemp.MaryCeleste != "OnDeck")
		{
			character.fromCity = character.toCity; // Колония, из бухты которой выйдет
			character.fromShore = character.toShore;
			character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придет
			character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
			
			Map_CreateTrader(character.fromShore, character.toShore, "MaryCelesteCapitan", GetMaxDaysFromColony2Colony(character.toCity, character.fromCity));
			
			Log_TestInfo("Бригантина Мэри Селест вышла из " + character.fromCity + " и направилась в " + character.toShore);
		}
	}
	
	// Warship Генер "Пираты на необитайке"
	// В город не выходит, только по глобалке: город - это лишние телодвижения, которые погоды особо не сделают
	if(sChar == "PiratesOnUninhabited_BadPirate")
	{
		Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate");
		
		if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.ClearShip"))
		{
			character.fromCity = character.toCity; // Колония, из бухты которой выйдет
			character.fromShore = character.toShore;
			character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придет
			character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
			
			Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", -1);
			
			Log_TestInfo("Пираты на необитайке: кэп вышел из " + character.fromCity + " и направился в: " + character.toShore);
		}
	}
	
	// ugeen --> генератор "Повод для спешки"
	if(sChar == "PirateCapt")
	{
		Log_TestInfo("Пиратский корабль дошёл до места назначения.");
		Map_ReleaseQuestEncounter(sChar);
		AddQuestRecord("ReasonToFast","26");
		AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("им","ой"));
		CloseQuestHeader("ReasonToFast");
		DeleteAttribute(pchar,"questTemp.ReasonToFast");
	}
	
	//розыск и отдача кэпу судового журнала
	if (HasSubStr(sChar, "PortmansCap_") && character.quest == "InMap")
	{
		SetCapitainFromSeaToCity(sChar);
		Log_TestInfo("Энканутер рассеянного кэпа " + sChar + " дошёл до места назначения.");
	}
	//поиски кэпа-вора
	if (HasSubStr(sChar, "SeekCap_") && character.quest == "InMap")
	{
		SetRobberFromMapToSea(sChar);
		Log_TestInfo("Энканутер кэпа-вора " + sChar + " дошёл до места назначения.");
	}
	//поиски кэпа, квест дают горожане
	if (HasSubStr(sChar, "SeekCitizCap_"))
	{
		if(character.quest == "InMap")
		{
			CitizCapFromMapToCity(sChar);
			Log_TestInfo("Энканутер кэпа " + sChar + " дошёл до места назначения.");
		}
		
		if(character.quest == "outMap")
		{
			string sTemp = "SCQ_" + character.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
			character.lifeDay = 0;
		}
	}
	//поиски бригантины с мушкетом
	if (sChar == "MushketCap" && character.quest == "InMap")
	{
		SetMushketFromMapToSea();
		Log_TestInfo("Энканутер кэпа с мушкетом дошёл до места назначения.");
	}
	//поиски брига Королева
	if (sChar == "Danielle" && character.quest == "InMap")
	{
		SetDanielleFromMapToSea();
		Log_TestInfo("Энканутер кэпа брига Queen дошёл до места назначения.");
	}
}
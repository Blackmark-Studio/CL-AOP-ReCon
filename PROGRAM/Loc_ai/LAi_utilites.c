string arrayNPCModel[128];
int    arrayNPCModelHow; // для рандомизации моделей в одной локации

// создаем горожан в локацию + солдаты, фантомы-многодневки (живут 48ч) переработка boal 13.05.06
void CreateCitizens(aref loc)
{
	if (loc.type != "town" && loc.type != "church" && loc.type != "residence") return; //городской генератор не должен отрабатывать везде
	if (LAi_IsCapturedLocation) return; // fix нефиг грузить, когда город трупов или боевка
	
	int iColony = -1;
	int iNation = -1;

	if (isLocationHasCitizens(loc.id))
	{
		if(!CheckAttribute(&TEV, "need_citizens") || sti(TEV.need_citizens) != 1) //на случай, когда фантомы есть, но от квестовых функций
		return; // boal  если есть еще с того раза, но не нужно
		else DeleteAttribute(&TEV, "need_citizens");
	}
	
	if (CheckAttribute(loc, "fastreload")) iColony = FindColony(loc.fastreload);
	if (iColony == -1) return;
	
	iNation = GetCityNation(loc.fastreload);
	if (iNation == -1) return;

	int iCitizensQuantity, iModel;
	int iSailorQty, iContraQty, iCommonerQty, iCitizQty, iNobleQty, iGipsyQty, iMonkQty;
	ref chr;
	int iChar, i, iSex;
	bool bOk;
	bool pirate_town = iNation == PIRATE && !sti(Colonies[iColony].HeroOwn);
	string slai_group, locatorName, sType;
    slai_group = GetNationNameByType(iNation) + "_citizens";

	// нищие -->
	if (loc.type == "town")
	{
		int iPoorIdx = GetCharacterIndex(colonies[iColony].id + "_Poorman");
		if (iPoorIdx != -1)
		{
			if (rand(1)) 
			{
				characters[iPoorIdx].PoorSit = true;
				sType = "locator" + rand(2);
				locatorName = characters[iPoorIdx].forSit.(sType);
			}
			else 
			{ 
				DeleteAttribute(&characters[iPoorIdx], "PoorSit");
				locatorName = characters[iPoorIdx].forStay.locator;
			}
			LAi_SetPoorTypeNoGroup(&characters[iPoorIdx]);
			if (LAi_CheckLocatorFree("goto", locatorName))
				ChangeCharacterAddressGroup(&characters[iPoorIdx], loc.id, "goto", locatorName);
			else
				PlaceCharacter(&characters[iPoorIdx], "patrol", "random_free");
		}
	}
	// нищие <--

	// горожане -->	
	if (!sti(Colonies[iColony].HeroOwn))
	{
		iSailorQty = rand(2)+2;
		iContraQty = rand(2);
		iCommonerQty = rand(4)+2;
		iCitizQty = 10;
		iNobleQty = rand(2)+1;
		iGipsyQty = rand(1);
		iMonkQty = rand(1);
	}
	else
	{
		iSailorQty = rand(2)+2;
		iContraQty = 0;
		iCommonerQty = rand(4)+2;
		iCitizQty = 10;
		iNobleQty = 0;
		iGipsyQty = 0;
		iMonkQty = 0;
	}
	if (loc.type == "church")
	{//Jason: лучше так, отдельным циклом работает некорректно
		iSailorQty = 0;
		iContraQty = 0;
		iCommonerQty = rand(4);
		iCitizQty = rand(4)+2;
		iNobleQty = 0;
		iGipsyQty = 0;
		iMonkQty = 0;
	}
	arrayNPCModelHow = 0;
	// торговцы -->
	aref st; //arrayNPCModelHow можно дополнительно занулить для пиратских городов, если не делать отдельный стек
	if (checkAttribute(loc, "locators.merchant"))
	{
		if (pirate_town) TEV.pirate_hawker = "";
		makearef(st, loc.locators.merchant);
		iCitizensQuantity = GetAttributesNum(st) / 2;
		for (i=0; i<iCitizensQuantity; i++)
		{
			if (pirate_town) iSex = MAN;
			else iSex = rand(WOMAN);
			sType = "hawker";
			iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 2);
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, iSex);
			chr.City = Colonies[iColony].id;
			chr.CityType = "citizen";
			chr.Merchant = true; // Флаг "торговец"
			chr.money = makeint(MERCH_TRADER_MIN_MONEY + frand(1.0)*MERCH_TRADER_RAND_MONEY); //ограничение денег лоточникам
			LAi_SetLoginTime(chr, 7.0, 20.0);
			ChangeCharacterAddressGroup(chr, loc.id, "merchant", "merchant"+(i+1));
			LAi_SetMerchantType(chr);
			chr.dialog.filename = "Common_ItemTrader.c";
			chr.dialog.currentnode = "first time";
			if (pirate_town) chr.greeting = "pirate_hawker";
			else
			{
				if (chr.sex == "man") chr.greeting = "tra_common";
				else chr.greeting = "tra_woman_common";
			}
			if (sti(Colonies[iColony].HeroOwn))
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
			SetLandQuestMarksToFantom(chr, "ItemTrader"); // фантом будет с квест-метками
		}
		DeleteAttribute(&TEV, "pirate_hawker");
	} 
	// торговцы <--	
	// солдаты -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
	{
		aref solderLoc;
		makearef(st, loc.locators.soldiers);
		iCitizensQuantity = GetAttributesNum(st);		
		for (i=0; i<iCitizensQuantity; i++)
		{
			solderLoc = GetAttributeN(st, i);
			locatorName = GetAttributeName(solderLoc);
			bool special = HasSubStr(locatorName, "special");
			if(HasSubStr(locatorName, "soldier"))
			{	//гвардия
				if(iNation != PIRATE) sType = "guard";
				else sType = "mercenary";
			}
			if(HasSubStr(locatorName, "sentry") || HasSubStr(locatorName, "protector"))
			{	//часовые
				if(iNation != PIRATE) sType = "urban_sold";
				else sType = "pirate";
			}
			if(special)
			{	//особые
				switch(loc.id)
				{
					case "Villemstad_town": //Охрана ГВИК
						if(GetCityNation("Villemstad") != HOLLAND) continue;
						sType = "elite_hol";
					break;
					case "FortFrance_town": //Мальтийцы
						if(GetCityNation("FortFrance") != FRANCE) continue;
						if(CheckAttribute(pchar, "quest.PDM_Jori") && locatorName == "special2") continue;
						if(CheckAttribute(pchar, "quest.PDM_Aler") && locatorName == "special1") continue;
						sType = "elite_fra";
					break;
				}
			}
			if(HasSubStr(locatorName, "mush"))
			{	//снайперы
				if(iNation == PIRATE)
					sType = "mush_ctz_" + (rand(2)+7);
				else
					sType = "urban_mush_" + NationShortName(iNation) + "_" + (rand(7)+1);
				chr = GetCharacter(NPC_GenerateCharacter("GenChar_", sType, "man", "mushketer", sti(pchar.rank), iNation, 2, false));
				chr.id = "GenChar_" + chr.index;
				chr.MusketerDistance = 0; //зависит от ситуации, может потребоваться ещё ветвление
			}
			else
			{
				iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
			}
			chr.City = Colonies[iColony].id;
			chr.CityType = "soldier";
			chr.RebirthPhantom = true;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			if(special)
			{	//особые
				switch(loc.id)
				{
					case "Villemstad_town": //Охрана ГВИК
						FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 70, 70, BLADE_LONG, "pistol3", 100); //TODO: настроить снаряжение
					break;
					case "FortFrance_town": //Мальтийцы
						FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 90, 90, "blade_maltes", "pistol2", 100);
					break;
				}
			}
			else SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); //бравые орлы
			LAi_SetLoginTime(chr, 6.0, 23.0); //а ночью будет беготня от патруля
			ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
			
			// eddy. проверяем, должен ли солдат быть протектором -->
			if (HasSubStr(locatorName, "protector") && iNation != PIRATE) 
			{
				chr.protector = true;
				chr.greeting = "soldier_arest";
			}
			else chr.greeting = "soldier_common";
			if(pirate_town) chr.greeting = "pirat_common";
			// <-- eddy. проверяем, должен ли солдат быть протектором
			
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
			
			LAi_SetGuardianType(chr);
			
			if (sti(Colonies[iColony].HeroOwn))
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
			SetLandQuestMarksToFantom(chr, "soldier");
		}
	}
	// солдаты <--
	// патруль -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
	{
		makearef(st, loc.locators.patrol);
		iCitizensQuantity = GetAttributesNum(st);
		if(iCitizensQuantity > 10)
		{
			if(loc.id == "Villemstad_town") iCitizensQuantity = 14;
			else iCitizensQuantity = 10;
		}
		for (i=0; i<iCitizensQuantity-3; i++)
		{
			if(iNation != PIRATE && LAi_IsCapturedLocation == 0)
			{
				sType = "urban_sold";
				iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
			}
			else
			{
				sType = "pirate";
				iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
			}
			chr = &characters[iChar];
			SetNPCModelUniq(chr, sType, MAN);
			chr.City = Colonies[iColony].id;
			chr.CityType = "soldier";
			SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			chr.RebirthPhantom = true;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			LAi_SetLoginTime(chr, 0.0, 24.0);
			if(pirate_town) chr.greeting = "pirat_common";
			else chr.greeting = "soldier_common";
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";

			LAi_SetPatrolType(chr);
			
			if (sti(Colonies[iColony].HeroOwn))
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
			if(loc.id == "Villemstad_town" && Whr_IsDay() == 0) TEV.place_check = "Villemstad";
			PlaceCharacter(chr, "patrol", "random_free");
			SetLandQuestMarksToFantom(chr, "soldier");
		}
		//мушкетеры
		int iQtyMush = 3;
		if(loc.id == "Villemstad_town") iQtyMush++;
		for (i=1; i<=iQtyMush; i++)
		{
			if(iNation == PIRATE)
				sType = "mush_ctz_" + (rand(2)+7);
			else
				sType = "urban_mush_" + NationShortName(iNation) + "_" + (rand(7)+1);
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_", sType, "man", "mushketer", sti(pchar.rank), iNation, 2, false));
			chr.id = "GenChar_" + chr.index;	
			chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
			chr.CityType = "soldier";
			if(pirate_town) chr.greeting = "pirat_common";
			else chr.greeting = "soldier_common";
			chr.RebirthPhantom = true;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			LAi_SetLoginTime(chr, 0.0, 24.0); //а ночью будет беготня от патруля
			
			if(loc.id == "Villemstad_town" && Whr_IsDay() == 0) TEV.place_check = "Villemstad";
			PlaceCharacter(chr, "patrol", "random_free");

			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";				

			LAi_SetPatrolType(chr);
			
			if (sti(Colonies[iColony].HeroOwn))
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
			SetLandQuestMarksToFantom(chr, "soldier");
		}
	}
	// патруль <--
	// грузчики -->
	if (loc.type == "town" && CheckAttribute(loc, "carrier") && IsLoginTime())
	{
		int iTemp;
		int iQtyCarrier = rand(2) + 2;
		for (i=iQtyCarrier; i>0; i--)
		{
			chr = GetCharacter(NPC_GenerateCharacter("Carrier", GetUniqCarrierModel("carrier_city"), "man", "genres", 35, iNation, 2, false));
			chr.id = chr.id + "_" + chr.index;
			chr.CityType = "citizen";
			LAi_SetImmortal(chr, true);
			LAi_SetLoginTime(chr, 7.0, 20.0);

            LAi_SetCarrierType(chr);
			if (sti(Colonies[iColony].HeroOwn))
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
		}
	}
	// грузчики <--
	//--> возможная генерация квестодателя на розыск капитанов
	if (GetCharacterIndex(colonies[iColony].id + "_Priest") && CheckAttribute(loc, "questSeekCap") && GetCharacterIndex("QuestCitiz_" + loc.fastreload) == -1)
	{
		string sModel, sSex, sAnimation, sGr;	
		if (rand(1))
		{
			sModel = "citiz_"+(rand(9)+11);
			sSex = "man";
			sAnimation = "man";
			sGr = "cit_quest";
		}
		else
		{
			sModel = "women_"+(rand(11)+1);
			sSex = "woman";
			sAnimation = "towngirl";
			sGr = "Gr_Woman_Citizen";
		}
		// evganat - генераторы
		Log_TestInfo("Зашли на генерацию, пол "+sSex);
		int iQuest = 7; // = 111
		int iRandQuest = rand(2); // fix - если свич в iQuest не отработает
		string sQuest;
		if(CheckAttribute(pchar, "questTemp.SeekCap"))
		{
			aref arQSeekCap, arSeekCap;
			makearef(arQSeekCap, pchar.questTemp.SeekCap);
			int n = GetAttributesNum(arQSeekCap);
			Log_TestInfo("Зашли в иф, количество квестов "+n+", iQuest "+iQuest);
			for(i=0; i < n; i++)
			{
				arSeekCap = GetAttributeN(arQSeekCap, i);
				sQuest = GetAttributeValue(arSeekCap);
				if(sSex == "man")
				{
					switch(sQuest)
					{
						case "slave":		iQuest = and(iQuest,3);	break; // &= 011
						case "rapewife":	iQuest = and(iQuest,5);	break; // &= 101
						case "friend":		iQuest = and(iQuest,6);	break; // &= 110
					}
				}
				else
				{
					switch(sQuest)
					{
						case "husband":		iQuest = and(iQuest,3);	break;
						case "revenge":		iQuest = and(iQuest,5);	break;
						case "pirates":		iQuest = and(iQuest,6);	break;
					}
				}
				Log_TestInfo("Проход номер "+i+", обнаружен квест "+sQuest+" теперь iQuest "+iQuest);
			}
			switch(iQuest)
			{
				case 7:	iRandQuest = rand(2);	break;
				case 6:	iRandQuest = rand(1);	break;
				case 5:	iRandQuest = rand(1)*2;	break;
				case 3:	iRandQuest = rand(1)+1;	break;
				case 2:	iRandQuest = 1;			break;
				case 1:	iRandQuest = 2;			break;
				case 4:	iRandQuest = 0;			break;
			}
			Log_TestInfo("Расчёт окончен, итоговый iRandQuest "+iRandQuest);
		}
		if(iQuest > 0)
		{
			Log_TestInfo("Выдаём квест");
			chr = GetCharacter(NPC_GenerateCharacter("QuestCitiz_"+loc.fastreload, sModel, sSex, sAnimation, 10, iNation, -1, false));
			chr.city = loc.fastreload;
			chr.dialog.filename   = "Quest\ForAll_dialog.c";
			chr.dialog.currentnode = "SCQ_" + sSex;
			chr.greeting = sGr;
			chr.talker = sti(loc.questSeekCap); //начать диалог
			chr.quest.SeekCap.numQuest = iRandQuest; //какой квест будет давать
			LAi_SetLoginTime(chr, 6.0, 21.99);
			LAi_SetCitizenType(chr);
			LAi_group_MoveCharacter(chr, slai_group);
			PlaceCharacter(chr, "goto", "random_free");
		}
	}
	if (checkAttribute(loc, "citizens") || loc.type == "church")
	{
		if (pirate_town)
		{
			if(loc.id == "PuertoPrincipe_town") iCitizQty = 6;
			for(i=0; i<iCitizQty; i++) // Пиратское поселение
			{
				iSex = MAN;
				sType = "smuggler";
				iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				LAi_SetWarriorType(chr);
				LAi_warrior_DialogEnable(chr, true);
				chr.watchBoxes = true;
				LAi_group_MoveCharacter(chr, slai_group);
				chr.dialog.filename = "Common_Citizen.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "pirat_common";
				PlaceCharacter(chr, "goto", "random_free");
			}
		}
		else
		{
			if(Pchar.questTemp.CapBloodLine != true && !GetGlobalTutor())
			{
				for(i=0; i<iSailorQty; i++) // Матросы
				{
					iSex = MAN;
					sType = "sailor";
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 2);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sType, iSex);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_SetCitizenType(chr);
					if (sti(Colonies[iColony].HeroOwn)) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					else LAi_group_MoveCharacter(chr, slai_group);
					PlaceCharacter(chr, "goto", "random_free");
					chr.dialog.filename    = "Population\Sailor.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "town_sailor";
					if (rand(4) == 1) // Найм в команду
					{
						chr.quest.crew = "true";
						chr.quest.crew.qty = (10 + rand(15)) * (1 + sti(pchar.rank)/10);
						chr.quest.crew.type = rand(2);
						chr.quest.crew.money = (1+rand(1))*100+rand(50);
						chr.talker = rand(9);
					}
				}
				for(i=0; i<iContraQty; i++) // Тёмные личности
				{
					iSex = MAN;
					sType = "smuggler";
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 2);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sType, iSex);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_SetCitizenType(chr);
					if (rand(7) < 2 && !CheckAttribute(pchar, "GenQuest.Marginpassenger") && chr.City != "Panama") //захват пассажира
					{
						chr.quest.passenger = "true";
						chr.talker = rand(5);
					}
					if (sti(Colonies[iColony].HeroOwn)) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					else LAi_group_MoveCharacter(chr, slai_group);
					PlaceCharacter(chr, "goto", "random_free");
					chr.dialog.filename    = "Population\Marginal.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "marginal";
				}
				for(i=0; i<iGipsyQty; i++) // Цыганки
				{
					if(rand(1)) continue; //поменьше цыганок, не в каждый второй город
					iSex = WOMAN;
					sType = "gipsy";
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 2);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sType, iSex);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_SetCitizenType(chr);
					if (sti(Colonies[iColony].HeroOwn)) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					else LAi_group_MoveCharacter(chr, slai_group);
					PlaceCharacter(chr, "goto", "random_free");
					chr.dialog.filename    = "Population\Gipsy.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "gipsy";
					chr.talker = 5;
				}
				for(i=0; i<iNobleQty; i++) // Дворяне
				{
					iSex = rand(WOMAN);
					sType = "noble";
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 2);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sType, iSex);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_SetCitizenType(chr);
					if (sti(Colonies[iColony].HeroOwn)) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					else LAi_group_MoveCharacter(chr, slai_group);
					PlaceCharacter(chr, "goto", "random_free");
					if(chr.sex == "man")
					{
						chr.dialog.filename = "Population\Nobleman.c";
						chr.greeting = "noble_male";
						if (GetCharacterIndex(chr.city + "_Priest") >= 0 && rand(11) > 9 && GetCharacterIndex("QuestCitiz_" + loc.fastreload) == -1)
						{	//поисковый генератор
							chr.id = "QuestCitiz_" + loc.fastreload;
							chr.dialog.filename = "Quest\ForAll_dialog.c";
							chr.dialog.currentnode = "SCQ_Nobleman";
							chr.talker = rand(3);
							chr.quest.SeekCap.numQuest = rand(1);
						}
						if (rand(11) < 2) //пассажирский генератор
						{
							chr.quest.passenger = "true";
							if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && 5-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
								chr.talker = rand(3);
						}
						if (rand(11) == 3)
						{
							chr.quest.donation = "true"; //клянчит деньги
							AddLandQuestMark_Gen_WithCondition(chr, "Nobledonation", "Gen_Nobelman_Donation_QuestMarkCondition");
						}
						if (GetCharacterIndex(chr.city + "_usurer") >= 0 && rand(11) == 5)
						{
							chr.quest.lombard = "true"; //семейная реликвия
							AddLandQuestMark_Gen_WithCondition(chr, "Noblelombard", "Gen_Nobelman_Lombard_Begin_QuestMarkCondition");
						}
						if (GetCharacterIndex(chr.city + "_Priest") >= 0 && rand(11) == 7)
						{
							chr.quest.slaves = "true"; //привезти рабов
							AddLandQuestMark_Gen_WithCondition(chr, "Nobleslaves", "Gen_Nobelman_Slaves_Begin_QuestMarkCondition");
						}
					}
					else
					{
						chr.dialog.filename = "Population\Noblegirl.c";
						chr.greeting = "noble_female";
					}
					SetCharacterPerk(chr, "Nobleman");
				}
				for(i=0; i<iMonkQty; i++) // Монахи
				{
					iSex = MAN;
					sType = "monk";
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 2);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sType, iSex);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					LAi_SetLoginTime(chr, 6.0, 21.99);
					LAi_SetCitizenType(chr);
					if (sti(Colonies[iColony].HeroOwn)) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					else LAi_group_MoveCharacter(chr, slai_group);
					if (rand(4) == 1) //собирает пожертвования
					{
						chr.quest.donation = "true";
						chr.talker = rand(3);
					}
					if (rand(4) == 0 && chr.City != "Panama") //пассажирский генератор
					{
						chr.quest.passenger = "true";
						if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(RealShips[sti(Pchar.Ship.Type)].Class) != 7 && 7-sti(RealShips[sti(Pchar.Ship.Type)].Class) < 4)
							chr.talker = rand(4);
					}
					if (rand(4) == 4 && !CheckAttribute(pchar, "questTemp.ShipCapellan") && pchar.ship.type != SHIP_NOTUSED && 5-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0) //корабельный капеллан
					{
						chr.quest.capellan = "true";
						chr.talker = rand(5)+4;
						SetCharacterPerk(chr, "Capellan1");
						SetCharacterPerk(chr, "Capellan2");
					}
					PlaceCharacter(chr, "goto", "random_free");
					chr.dialog.filename    = "Population\Monk.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "monk";
					SetCharacterPerk(chr, "Monk");
				}
			}

			bool generateAffairOfHonor = loc.type == "town" && CanGenerateAffairOfHonor(loc, iColony);
			bool _isChurchLoginTime = IsLoginTime();
			// Для правильной усадки в церкви нужно генерить персов только в отведенное время
			if (loc.type == "church" && !_isChurchLoginTime) return;

			for (i = 0; i < iCitizQty; i++) // Горожане
			{
				if (rand(4) > 1) iSex = WOMAN; // 60% девушки, т.к. простолюдины все мужчины
				else iSex = MAN;
				if(iSex == WOMAN && rand(9) == 0) sType = "oldwoman";
				else sType = "citizen";
				iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				if (loc.type == "church")
				{
					chr.nonTable = true;
					LAi_SetSitType(chr);
					chr.diag = rand(16);
					if(chr.diag == "2" && iSex == MAN) RandTeacher(chr);
					chr.dialog.filename = "Encounters\Walker.c"; // TODO: женщинам отдельный вариант
					PlaceCharacter(chr, "sit", "random_free");
				}
				else 
				{
					LAi_SetCitizenType(chr);
					if(loc.id == "Villemstad_town" && Whr_IsDay() == 0) TEV.place_check = "Villemstad";
					chr.dialog.filename = "Common_Citizen.c";
					PlaceCharacter(chr, "goto", "random_free");
				}
				if (sti(Colonies[iColony].HeroOwn)) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				chr.dialog.currentnode = "first time";
				if (!CheckAttribute(chr, "greeting"))
				{
					if (chr.sex == "man") chr.greeting = "townman";
					else chr.greeting = "Gr_Woman_Citizen";
				}
                SetLandQuestMarksToFantom(chr, "Citizen");
				// Warship, 25.05.11 "Дело чести" -->
				if (generateAffairOfHonor)
				{
					bool bManBranch = chr.sex == "man" && NumManAffairQuests() < 6;
					bool bWomanBranch = chr.sex == "woman" && !CheckAttribute(pchar, "QuestTemp.AffairOfHonor.Cavalier");
					if (bManBranch || bWomanBranch) //если доступна хоть 1 ветка разговора на улице
					{
						chr.id = "AffairOfHonor_QuestMan";
						chr.dialog.filename = "Quest\ForAll_dialog.c";
						chr.dialog.currentnode = "AffairOfHonor_1";
						chr.talker = rand(5);
						LAi_SetImmortal(chr, true);

						if (chr.sex == "man")
						{
							int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10;
							int Scl = 30+2*sti(pchar.rank);
							int qNum = GetHonorQuestNum();
							chr.rank = Rank;
							chr.quest.AffairOfHonor.numQuest = qNum;
							if(qNum == 2 || qNum == 4) FantomMakeCoolFighter(chr, Rank, Scl, Scl, "auto", "auto", Scl*3);
							float Mft = MOD_SKILL_ENEMY_RATE/20;
							chr.MultiFighter = 1.0+Mft; // мультифайтер
						}

						generateAffairOfHonor = false; // Чтобы по двести раз не генерило квестодателей
						Log_TestInfo("Сгенерилось дело чести");
					}
				}
				// <-- "Дело чести"
			}
			for(i=0; i<iCommonerQty; i++) // Простолюдины
			{
				iSex = MAN;
				sType = "commoner";
				iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, 2);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, iSex);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				LAi_SetLoginTime(chr, 6.0, 21.99);
				if (loc.type == "church")
				{
					chr.nonTable = true;
					LAi_SetSitType(chr);
					chr.diag = rand(16);
					if(chr.diag == "2" && iSex == MAN) RandTeacher(chr);
					chr.dialog.filename = "Encounters\Walker.c";
					PlaceCharacter(chr, "sit", "random_free");
				}
				else 
				{
					LAi_SetCitizenType(chr);
					if(loc.id == "Villemstad_town" && Whr_IsDay() == 0) TEV.place_check = "Villemstad";
					chr.dialog.filename = "Common_Citizen.c";
					PlaceCharacter(chr, "goto", "random_free");
				}
				if (sti(Colonies[iColony].HeroOwn)) LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				else LAi_group_MoveCharacter(chr, slai_group);
				chr.dialog.currentnode = "first time";
				if(!CheckAttribute(chr, "greeting"))
					chr.greeting = "cit_common";

				SetLandQuestMarksToFantom(chr, "Commoner");
			}
		}
	}
	// горожане <--
}

// плодим завсегдатеев в таверну, тоже фантомы-многодневки (24ч) переработка boal 13.05.06
void CreateHabitues(aref loc)
{
	int iColony = -1;
	int iNation = -1;
	
	if (!checkAttribute(loc, "habitues")) return;
	if (LAi_IsCapturedLocation) return;
	
	OfficersReactionResult(); // уход офов в местах, где есть пьянь и др офы - пока это таверна
	
	if (!isLocationHasCitizens(loc.id))  // boal  если есть еще с того раза, но не нужно
	{
		if (CheckAttribute(loc, "fastreload"))
		{
			iColony = FindColony(loc.fastreload);
			
			if(iColony == -1)
			{
				return;
			}
			
			iNation = GetCityNation(loc.fastreload);
			
			if (iNation == -1)
			{
				return;
			}
			
			string sColony = loc.fastreload;
			int iCitizensQuantity, iModel;
			ref chr;
			string slai_group, sModel, sTemp;
			int iChar;
			int i, n, k;
			bool pirate_town = iNation == PIRATE && !sti(Colonies[iColony].HeroOwn);

			bool generateAffairOfHonor = CanGenerateAffairOfHonor(loc, iColony) && !CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor");
			slai_group = GetNationNameByType(iNation)  + "_citizens";
			
			arrayNPCModelHow = 0;
			// сажаем пьянь, на козырные места под ГГ
			for (i = 1; i <=4; i++)
			{
				if (CheckFreeLocator(loc.id, "sit_base" + i, -1) && CheckFreeLocatorEx(loc.id, "sit_base" + i, -1)) //Rosarak. fix
				{
					if (pirate_town)
					{
						if (rand(1)) sModel = "pirate";
						else sModel = "smuggler";
					}
					else
					{
						if (rand(4) > 0) sModel = RandCitizenType();
						else sModel = "sailor"; //20%
					}
					iChar = NPC_GeneratePhantomCharacter(sModel, iNation, MAN, 1);
					
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sModel, MAN);
					
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					ChangeCharacterAddressGroup(chr, loc.id, "sit", "sit_base" + i);
					chr.Default           = loc.id;
					chr.Default.group     = "sit";
					chr.Default.ToLocator = "sit_front" + i;
					LAi_SetLoginTime(chr, 0.0, 24.0);
					LAi_SetSitType(chr);
					if (sti(Colonies[iColony].HeroOwn))
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "Gr_Tavern_Mate";
					// Игрок или алкаш определяется при генерации
					// в Бета-тесте осталось возможность выбирать архетип через диалог
					chr.quest.last_theme = rand(1);
					chr.quest.last_theme_game = rand(1);
					SetLandQuestMarksToFantom(chr, "habitue");

					// Warship, 30.05.11 "Дело чести" -->
					if (generateAffairOfHonor)
					{
						chr.id = "AffairOfHonor_QuestMan";
						chr.dialog.filename = "Quest\ForAll_dialog.c";
						chr.dialog.currentnode = "AffairOfHonor_1";
						LAi_SetImmortal(chr, true);
						CreateModel(iChar, "milit_off", MAN);
						Characters_RefreshModel(chr); // Jason: рефрешить модель обязательно
						generateAffairOfHonor = false; // Чтобы по двести раз не генерило квестодателей
						Log_TestInfo("Сгенерилось дело чести");
						// квест-метки
						RemoveLandQuestMarksToFantom(chr);
						AddLandQuestMark_Gen(chr, "AffairOfHonor");
					}
					// <-- "Дело чести"
				}
			}
			iChar = GetCharacterIndex(Colonies[iColony].id + "_Smuggler");
			if (iChar != -1 && !GetGlobalTutor()) // у пиратов нет вообще - это статики
			{
				chr = &characters[iChar];
				if (!sti(Colonies[iColony].HeroOwn))
				{ // грузим контрикова агента, он статик, но локацию и локатор ставим тут
					chr.City = Colonies[iColony].id;  // это можно прописать в статике, но мне лениво по 20 городам лазить.
					chr.nation = iNation; // нация его нужна, тк она будет нацией патруля на берегу, он не пират
					CreateModel(iChar, "smuggler", MAN);	//пересоздадим, т.к. это статик
					SetNPCModelUniq(chr, "smuggler", MAN);	//вдруг совпадёт с кладменом или квестовыми
					sTemp = PlaceCharacter(chr, "sit", "random_free");
					ReSitCharacterOnFree(chr, loc.id, sTemp);
					LAi_group_MoveCharacter(chr, slai_group);
				}
				else
				{
					ChangeCharacterAddressGroup(chr, "none", "none", "none");
				}
				// вне группы
			}
			// агенты наций и контриков, только в пиратских тавернах -->
			if (pirate_town)
			{
				iChar = NPC_GeneratePhantomCharacter("diplomat", iNation, MAN, 1);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, "diplomat", MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				sTemp = PlaceCharacter(chr, "sit", "random_free"); // может не быть вовсе, если все места заняты
				ReSitCharacterOnFree(chr, loc.id, sTemp);
				
				LAi_SetSitType(chr);
				LAi_group_MoveCharacter(chr, slai_group);
				chr.Name = FindPersonalName("diplomat_name");
				chr.LastName = "";
				chr.dialog.filename = "Diplomat_dialog.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "Gr_RelationAgent";
				LAi_group_MoveCharacter(chr, slai_group);

				SetLandQuestMarksToFantom(chr, "diplomat");
			}
			// агенты наций и контриков, только в пиратских тавернах <--
			// офицеры -->
			iCitizensQuantity = rand(6) - 3;
			if (GetGlobalTutor()) {iCitizensQuantity = 0;}
			for (i = 0; i <iCitizensQuantity; i++)
			{
				iChar = NPC_GeneratePhantomCharacter("pofficer", iNation, MAN, 1);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, "pofficer", MAN);
				SetOfficerParam(chr, rand(6));
				sTemp = PlaceCharacter(chr, "sit", "random_free");
				ReSitCharacterOnFree(chr, loc.id, sTemp);
				
				LAi_SetSitType(chr);
				// без группы
				chr.dialog.filename = "Officer_Man.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "Gr_Officer";
				if (sti(Colonies[iColony].HeroOwn))
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
			// офицеры <--
			if (and(rand(10) == 3, !GetGlobalTutor()) || TestRansackCaptain)
			{ // карты кладов
				iChar = NPC_GeneratePhantomCharacter("smuggler", iNation, MAN, 1);
				chr = &characters[iChar];
				SetNPCModelUniq(chr, "smuggler", MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "citizen";
				sTemp = PlaceCharacter(chr, "sit", "random_free"); // может не быть вовсе, если все места заняты
				ReSitCharacterOnFree(chr, loc.id, sTemp);
				
				LAi_SetSitType(chr);
				LAi_group_MoveCharacter(chr, slai_group);
				chr.dialog.filename = "Smuggler_Treasure_dialog.c";
				chr.dialog.currentnode = "first time";
				chr.greeting = "Gr_Smuggler Agent";
				
				if (GetCharacterItem(pchar, "map_full") == 0) // нет карты - генерим, если купит
				{
					aref item;
					Items_FindItem("map_full", &item);
					FillMapForTreasure(item);
					pchar.GenQuest.TreasureMoney = 5000 + rand(60)*500;
				}
				if (sti(Colonies[iColony].HeroOwn))
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}

				AddLandQuestMark_Gen_WithCondition(chr, "Gen_Smuggler_Treasure", "Gen_Smuggler_Treasure_QuestMarkCondition");
			}
			else
			{
				iCitizensQuantity = rand(3) - 1 ; // простая пьянь для антуражу
				for (i = 0; i <iCitizensQuantity; i++)
				{
					if (pirate_town)
					{
						if (rand(1)) sModel = "pirate";
						else sModel = "smuggler";
					}
					else
					{
						if (rand(4) > 0) sModel = RandCitizenType();
						else sModel = "sailor";
					}
				    iChar = NPC_GeneratePhantomCharacter(sModel, iNation, MAN, 1);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, sModel, MAN);
					chr.City = Colonies[iColony].id;
					chr.CityType = "citizen";
					sTemp = PlaceCharacter(chr, "sit", "random_free"); // может не быть вовсе, если все места заняты
					ReSitCharacterOnFree(chr, loc.id, sTemp);
					
					LAi_SetLoginTime(chr, 0.0 + rand(6), 24.0 - rand(10));
					LAi_SetSitType(chr);
					if (sti(Colonies[iColony].HeroOwn))
					{
						LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					}
					else
					{
						LAi_group_MoveCharacter(chr, slai_group);
					}
					chr.dialog.filename = "Habitue_dialog.c";
					chr.dialog.currentnode = "first time";
					chr.greeting = "Gr_Tavern_Mate";

					chr.quest.last_theme = rand(1);
                    chr.quest.last_theme_game = rand(1);
                    SetLandQuestMarksToFantom(chr, "habitue");
				}
			}
		}
	}
	PGG_TavernCheckIsPGGHere();
}

void CreateMaltains(aref loc) //Jason, заполнение базы мальтийцев в Сен-Пьере (Hirurg39)
{	
    if(GetCityNation("FortFrance") != FRANCE) return;
	if(CheckAttribute(loc, "QuestCapture")) return; // если идет квестовый бой 
	
	if (CheckAttribute(loc, "Maltains"))
	{
		ref sld;
		int i;
		string sTemp;
		if (!CheckAttribute(loc, "Maltains_date") || GetNpcQuestPastDayParam(loc, "Maltains_date") >= 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Maltains_date");
			//офицер
			sld = GetCharacter(NPC_GenerateCharacter("Maltie_officer", "off_Malt_"+(rand(1)+1), "man", "man", 35, FRANCE, 2, false));
			FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 100, 100, "blade_maltes", "pistol5", 150); //спецназ
			sld.greeting = "off_special";
			sld.Dialog.Filename = "Maltese_dialog.c";
			sld.dialog.currentnode = "Maltie_officer";
			ChangeCharacterAddressGroup(sld, "FortFrance_Malta_Dungeon", "sit", "sit1");
			LAi_SetHuberType(sld);
			sld.standUp = true;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			SetLandQuestMarksToFantom(sld, "Maltie_officer");
			//протекторы, 4 шт
			arrayNPCModelHow = 0; //TODO: ниже можно и через NPC_GeneratePhantomCharacter("elite_fra", FRANCE, MAN, 2)
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsPro_"+i, "elite_fra_"+(rand(7)+1), "man", "man", 25, FRANCE, 2, false));
				SetNPCModelUniq(sld, "elite_fra", MAN);
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 90, 90, "blade_maltes", "pistol2", 100); //спецназ
				sld.greeting = "soldier_arest";
				sld.Dialog.Filename = "Maltese_dialog.c";
				sld.dialog.currentnode = "Maltie_soldier";
				ChangeCharacterAddressGroup(sld, "FortFrance_Malta_Dungeon", "soldiers", "soldier"+i);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
			//сидячие рыцари, 4 шт
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsSit_"+i, "elite_fra_"+(rand(7)+1), "man", "man", 20, FRANCE, 2, false));
				SetNPCModelUniq(sld, "elite_fra", MAN);
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 70, 70, "blade_maltes", "pistol2", 100); //спецназ
				sld.Dialog.Filename = "Maltese_dialog.c";
				sld.dialog.currentnode = "Maltie_soldier";	
				sld.greeting = "soldier_common";
				sld.nonTable = true;
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetSitType(sld);
				sld.standUp = true;
				PlaceCharacter(sld, "sit", "random_free");
				sTemp = sld.location.locator;
				while(HasSubStr("sit12,sit13,sit14",sTemp)) //не шалим, ребята
				{
					PlaceCharacter(sld, "sit", "random_free");
					sTemp = sld.location.locator;
				}
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
			//стоячие рыцари, 5 шт
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsStay_"+i, "elite_fra_"+(rand(7)+1), "man", "man", 20, FRANCE, 2, false));
				SetNPCModelUniq(sld, "elite_fra", MAN);
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 70, 70, "blade_maltes", "pistol2", 100); //спецназ
				sld.Dialog.Filename = "Maltese_dialog.c";
				sld.dialog.currentnode = "Maltie_soldier";	
				sld.greeting = "soldier_common";
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				PlaceCharacter(sld, "soldiers", "random_free");
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
			//бродячие рыцари, 5 шт
			for (i=1; i<=5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsGo_"+i, "elite_fra_"+(rand(7)+1), "man", "man", 20, FRANCE, 2, false));
				SetNPCModelUniq(sld, "elite_fra", MAN);
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+10, 70, 70, "blade_maltes", "pistol2", 100); //спецназ
				sld.Dialog.Filename = "Maltese_dialog.c";
				sld.dialog.currentnode = "Maltie_soldier";	
				sld.greeting = "soldier_common";
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetPatrolType(sld);
				sld.city = "FortFrance";
				sld.citytype = "soldier";
				PlaceCharacter(sld, "goto", "random_free");
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
		}
		//заключенные
		if (!CheckAttribute(loc, "Maltaprisoner_date") || GetNpcQuestPastDayParam(loc, "Maltaprisoner_date") > 15)
		{
			SaveCurrentNpcQuestDateParam(loc, "Maltaprisoner_date");
			for (i=2; i<=(rand(2)+2); i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("MaltainsPrisoner_"+i, "citiz_"+(rand(9)+51), "man", "man", 10, FRANCE, 15, false)); //watch_quest_moment
				SetNPCModelUniq(sld, "mercenary", MAN);
				RemoveAllCharacterItems(sld, true);
				LAi_CharacterDisableDialog(sld);
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				if (rand(1) == 0) LAi_SetStayType(sld);
				else LAi_SetGroundSitType(sld);
				ChangeCharacterAddressGroup(sld, "FortFrance_Malta_Dungeon", "quest", "quest"+i);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			}
		}
	}
}

// заполнение инквизиции. eddy
void CreateIncquisitio(aref loc)
{	
	if (GetCityNation("Santiago") != SPAIN) return;
	
	if (CheckAttribute(loc, "Incquisitio"))
	{
		ref sld;
		string LocatorGroup, LocatorName, sPrison;
		int i, nSit;
		//====> накидаем священников
		if (CheckNPCQuestDate(loc, "Incquisitor_date"))
		{
			SetNPCQuestDate(loc, "Incquisitor_date");
			LocatorGroup = "goto";
			nSit = rand(2)+1;
			for (i=1; i<=3; i++)
			{
				LocatorGroup = "goto";
				LocatorName = LAi_FindRandomLocator("goto");				 
				if (i==nSit) 
				{
					LocatorGroup = "sit";
					LocatorName = "sit"+(rand(3)+1);			
				}
				sld = GetCharacter(NPC_GenerateCharacter("Incquisitor_"+i, "priest_sp"+i, "man", "man_B", 20, SPAIN, 1, false));
				sld.Dialog.Filename = "Incquistors_dialog.c";									
				LAi_LoginInCaptureTown(sld, true);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				if (i==nSit) LAi_SetSitType(sld);
				else LAi_SetCitizenType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", LocatorGroup, LocatorName);
				SetLandQuestMarksToFantom(sld, "Incquisitor"); // фантом будет с квест-метками
			}
		}
		//====> накидаем солдат
		if (CheckNPCQuestDate(loc, "Guard_date"))
		{
			SetNPCQuestDate(loc, "Guard_date");
			arrayNPCModelHow = 0;
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("IncqGuard_"+i, "elite_spa_"+(rand(2)+1), "man", "man", 35, SPAIN, 1, true)); //watch_quest_moment
				SetNPCModelUniq(sld, "elite_spa", MAN);
				sld.City = "Santiago";
				sld.CityType = "soldier";
				LAi_LoginInCaptureTown(sld, true);
				FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+15, 100, 90, BLADE_LONG, "pistol3", 200); //спецназ
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");	
				locatorName = PlaceCharacter(sld, "soldiers", "random");				
				if (locatorName == "soldier1" || locatorName == "soldier2")
				{
					sld.protector.CheckAlways = true; //проверять всегда
					sld.Dialog.Filename = "Incquistors_dialog.c";
					sld.greeting = "soldier_arest";
				}
				else
				{
					if (HasSubStr(locatorName, "protector")) sld.protector = true;
					sld.Dialog.Filename = "Common_Soldier.c";
					sld.greeting = "Gr_Guard";
				}
			}
		}
		//====> накидаем заключенных, раз в месяц
		if (!CheckAttribute(loc, "Prison_date") || GetNpcQuestPastDayParam(loc, "Prison_date") > 30)
		{
			SaveCurrentNpcQuestDateParam(loc, "Prison_date");
			for (i=1; i<=8; i++)
			{
				if (rand(100)<70)
				{
					sPrison = GetRandSubString("pirate_4,prison_2,prison_4,prison_5,citiz_35");
					sld = GetCharacter(NPC_GenerateCharacter("Prisoner_"+i, sPrison, "man", "man", 10, SPAIN, 30, false));							
					sld.Dialog.Filename = "Incquistors_dialog.c";
					sld.greeting = "Gr_prison";
					LAi_LoginInCaptureTown(sld, true); //TODO: зачем?
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetActorType(sld);
					if (rand(10)>5) LAi_ActorSetLayMode(sld);
					else LAi_SetGroundSitType(sld);
					PlaceCharacter(sld, "prison", "random_free");
				}
			}
		}
	}
}

//Маяк Порт-Ройал
void CreateMayak(aref loc)
{
	if(GetCityNation("PortRoyal") == PIRATE) return; //временная заглушка; TODO: потом пропишем корректно
	
	if (loc.type == "mayak")
	{
		if (!CheckAttribute(loc, "Mayak_date") || GetNpcQuestPastDayParam(loc, "Mayak_date") > 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Mayak_date");
            ref rColony = GetColonyRefByID("PortRoyal");
			int iNation = GetCityNation("PortRoyal");
			
			int iCitizensQuantity, iModel;
			ref chr;
			aref st, solderLoc;
			int iChar, i;
			string slai_group, locatorName, nShortName;
			nShortName = NationShortName(iNation);
			slai_group = GetNationNameByType(iNation)  + "_mayak";
			// солдаты -->
			if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
			{
				makearef(st, loc.locators.soldiers);
				iCitizensQuantity = GetAttributesNum(st);
				for (i=0; i<iCitizensQuantity; i++)
				{
					solderLoc = GetAttributeN(st, i);
					locatorName = GetAttributeName(solderLoc);
					arrayNPCModelHow = 0;
					if (HasSubStr(locatorName, "protector")) 
					{		
						iChar = NPC_GeneratePhantomCharacter("army_sold", iNation, MAN, 2);
						chr = &characters[iChar];
						SetNPCModelUniq(chr, "army_sold", MAN);
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter("GenChar_", nShortName + "_mush_" + (rand(3)+5), "man", "mushketer", sti(pchar.rank), iNation, 2, false)); //снайпер
						chr.id = "GenChar_" + chr.index;
						chr.MusketerDistance = 0;
					}					
					chr.City = rColony.id;
					chr.CityType = "soldier";
					chr.greeting = "soldier_common";
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+6, true); // бравые орлы
					LAi_SetLoginTime(chr, 0.0, 24.0);
					solderLoc = GetAttributeN(st, i);
					locatorName = GetAttributeName(solderLoc);
					ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
					// eddy. проверяем, должен ли солдат быть протектором -->
					if (HasSubStr(locatorName, "protector")) 
					{
						chr.protector = true;
						chr.greeting = "soldier_arest";
						if (locatorName != "protector1" && locatorName != "protector2") 
						{
							chr.protector.CheckAlways = 1; //проверять всегда
							if (locatorName == "protector11") chr.dialog.currentnode = "PortRoyal_Mayak";
							else chr.dialog.currentnode = "PortRoyal_Gans";
						}
					}
					// <-- eddy. проверяем, должен ли солдат быть протектором
					chr.dialog.filename = "Common_Soldier.c";
					LAi_SetGuardianType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
				}
			}
			// солдаты <--
			// патруль -->
			if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
			{
				makearef(st, loc.locators.patrol);
				iCitizensQuantity = GetAttributesNum(st);
				for (i=0; i<iCitizensQuantity; i++)
				{
					iChar = NPC_GeneratePhantomCharacter("army_sold", iNation, MAN, 2);
					chr = &characters[iChar];
					SetNPCModelUniq(chr, "army_sold", MAN);
					chr.City = rColony.id;
					chr.CityType = "soldier";
					SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
					LAi_SetLoginTime(chr, 0.0, 24.0);
					LAi_SetPatrolType(chr);
					LAi_group_MoveCharacter(chr, slai_group);
					chr.greeting = "soldier_common";
					PlaceCharacter(chr, "patrol", "random_free");
					chr.dialog.filename = "Common_Soldier.c";
					chr.dialog.currentnode = "first time";
				}
			}
			// патруль <--
			LAi_group_SetLookRadius(slai_group, 80);
			LAi_group_SetHearRadius(slai_group, 80);
		}
	}
}

void CreateBrothels(aref loc)
{
	if (CheckAttribute(loc, "brothel"))
	{
		ref location;
		if (HasSubStr(loc.id, "SecBrRoom"))
		{
			location = &locations[FindLocation(loc.fastreload + "_Brothel")];
		}
		else
		{
			makeref(location, loc);
		}
		if (!CheckAttribute(location, "Brothel_date") || GetNpcQuestPastDayParam(location, "Brothel_date") > 100)
		{
			ref sld;
			int iColony, iNation, qtyAll;
			SaveCurrentNpcQuestDateParam(location, "Brothel_date");
			if(CheckAttribute(location, "fastreload"))
			{
				iColony = FindColony(location.fastreload);
			}
			else return;
			iNation = GetCityNation(location.fastreload);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			qtyAll = rand(2) + 4;
			arrayNPCModelHow = 0;
			for(int i = 1; i < qtyAll; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("HorseGen_"+location.index +"_"+ i, "horse0"+(rand(7)+1), "woman", "towngirl", 3, iNation, 100, false));
				SetNPCModelUniq(sld, "whore", WOMAN);
				sld.City = location.fastreload;
				sld.CityType = "horse";
				sld.dialog.filename = "Common_Brothel.c";
				sld.dialog.currentnode = "Horse_talk";
				sld.greeting = "whore";
				switch (location.fastreload)
				{
					case "PortRoyal":	 sld.quest.price = 1100*(rand(4)+5); break;
					case "Tortuga":		 sld.quest.price = 1000*(rand(4)+5); break;
					case "Villemstad":	 sld.quest.price = 900*(rand(4)+5); break;
					case "Panama":		 sld.quest.price = 800*(rand(4)+5); break;
					case "Marigo":	     sld.quest.price = 700*(rand(4)+5); break;
					case "FortFrance":	 sld.quest.price = 500*(rand(4)+5); break;
					case "Providencia":	 sld.quest.price = 450*(rand(4)+5); break;
					case "Bridgetown":	 sld.quest.price = 400*(rand(4)+5); break;
					case "Charles":		 sld.quest.price = 300*(rand(4)+5); break;
					case "SantoDomingo": sld.quest.price = 200*(rand(4)+5); break;
				}
				LAi_SetCitizenType(sld);
				LAi_group_MoveCharacter(sld, slai_group);
				ChangeCharacterAddressGroup(sld, location.id, "goto", "goto"+i);
				SetLandQuestMarksToFantom(sld, "Horse"); // фантом будет с квест-метками
			}
		}
	}
}

//eddy. наполнение жемчужных поселений
void CreatePearlVillage(aref loc)
{
	if (CheckAttribute(loc, "pearlVillage") && sti(loc.pearlVillage) == true)
	{	
		string iPrefix, sTemp;
		sTemp = loc.id;
		iPrefix = GetSymbol(sTemp, strlen(sTemp)-1); //получаем префикс куда грузить нпс
		int iPearNation = sti(colonies[FindColony("SantaCatalina")].nation);
		int iTemp = GetCharacterIndex("PearlGuardMan_"+iPrefix);
		if (iTemp != -1 && !CheckAttribute(&characters[iTemp], "quest.TalkOk")) 
		{//если не завалил часового
			if (characters[iTemp].location == "none")
			{
				loc.pearlVillage = false;
				DeleteAttribute(&locations[FindLocation("PearlTown"+iPrefix+"_Townhall")], "box1");
				DeleteAttribute(&locations[FindLocation("PearlTown"+iPrefix+"_Townhall")], "box2");
				Log_SetStringToLog(StringFromKey("InfoMessages_83"));
				return;
			}
			else
			{//если успел вперёд часового
				DoQuestCheckDelay("Pearl_GuardManIsLife", 3.5);
				pchar.quest.Pearl_GuardManIsLife.idx = iTemp;//индекс часового передаем
				chrDisableReloadToLocation = true;			
			}
		}
		else 
		{//часовой убит
			//LAi_group_SetRelation("PearlGroup_"+iPrefix, LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
		}
		ref chr;
		int num, i, iMassive, iRank;
		string model[10];
		loc.pearlVillage = false; //флаг не генерить пиплов
		// ==> глава администрации
		iRank = 20+rand(15);
		switch(iPearNation)
		{
			case ENGLAND:	sTemp = "off_eng_"+(rand(1)+1);		break;
			case FRANCE:	sTemp = "off_fra_"+(rand(1)+1);		break;
			case SPAIN: 	sTemp = "off_spa_"+(rand(1)+1);		break;
			case HOLLAND:	sTemp = "off_hol_"+(rand(1)+1);		break;
			case PIRATE:	sTemp = "citiz_"+(rand(9)+51);		break; //наш слон, наш базич;
		}
		chr = GetCharacter(NPC_GenerateCharacter("HeadMan_"+iPrefix, sTemp, "man", "man", iRank, iPearNation, 30, true));
		SetCharacterPerk(chr, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, дается ГГ и боссам уровней  
		SetCharacterPerk(chr, "SwordplayProfessional");
		chr.dialog.Filename = "Pearl_dialog.c";
	    chr.dialog.currentnode = "HeadMan";		
		chr.city = "SantaCatalina"; //НЗГ Санта-Каталины
		SetFantomParamFromRank(chr, iRank, true);
		LAi_SetWarriorType(chr);
		LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
        sTemp = "PearlTown"+iPrefix+"_Townhall"; //ID резиденции
		ChangeCharacterAddressGroup(chr, sTemp, "goto", "goto5");
		SetLandQuestMarksToFantom(chr, "Pearl_HeadMan"); // фантом будет с квест-метками
		// ==> кладём жемчуг
		DeleteAttribute(&locations[FindLocation(sTemp)], "box1");
		DeleteAttribute(&locations[FindLocation(sTemp)], "box2");
		pchar.GenQuestBox.(sTemp) = true;
        pchar.GenQuestBox.(sTemp).box1.items.jewelry11 = rand(150) + rand(150);
        pchar.GenQuestBox.(sTemp).box2.items.jewelry12 = rand(250) + rand(250);
		// ==> защитники, повоевать таки придется
		i = 0;
		arrayNPCModelHow = 0;
		num = rand(3) + 2; //кол-во защитников
		while(i < num)
		{
			chr = GetCharacter(NPC_GenerateCharacter("FightMan"+iPrefix+"_"+i, GetRandSubString(COMMONERS), "man", "man", 15, iPearNation, 30, true));
			SetNPCModelUniq(chr, "commoner", MAN);
			SetFantomParamFromRank(chr, 15, true);
			chr.dialog.Filename = "Pearl_dialog.c";
			chr.dialog.currentnode = "PearlMan";
			chr.greeting = "cit_common";
			chr.city = "SantaCatalina"; //НЗГ Санта-Каталины
			PlaceCharacter(chr, "goto", "random");
			LAi_SetWarriorType(chr);
			LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
			i++;
		}
		// ==> просто работники
		model[0] = "indsar1";
		model[1] = "indsair2";
		model[2] = "worker_48";
		model[3] = "barmen_0";
		model[4] = "citiz_43";
		model[5] = "citiz_44";
		model[6] = "citiz_45";
		model[7] = "citiz_47";
		model[8] = "citiz_49";
		model[9] = "shipowner_17";
		i = 0;
		num = rand(3) + 2;
		while(i < num)
		{
		    //если квест "Найти человека среди ловцов жемчуга, который даёт информацию Шарпу." может быть взят, то генерим одного 100% индейца
		    if (i == 0 && pchar.questTemp.Sharp != "begin" && pchar.questTemp.Sharp != "over" && pchar.questTemp.Sharp.SeekSpy == "begin") iMassive = rand(1);
		    else iMassive = rand(9);
			if (model[iMassive] != "")
			{
				chr = GetCharacter(NPC_GenerateCharacter("WorkMan"+iPrefix+"_"+i, model[iMassive], "man", "man", 7, iPearNation, 30, false));
				chr.indian = "1";
				SetLandQuestMarksToFantom(chr, "Pearl_WorkMan"); // фантом будет с квест-метками
				chr.dialog.Filename = "Pearl_dialog.c";
				chr.dialog.currentnode = "PearlMan";
				if (model[iMassive] == "indsair2" || model[iMassive] == "indsar1")
				{
					chr.name = GetIndianName(MAN);
					chr.lastname = "";
					chr.dialog.currentnode = "IndPearlMan";
					chr.greeting = "Gr_PearlIndian";
				}
				else
				{
				    chr.greeting = "cit_common";
				}
				chr.CityType = "citizen";
				chr.city = "SantaCatalina"; //НЗГ Санта-Каталины

				PlaceCharacter(chr, "goto", "random");
				LAi_SetCitizenType(chr);
				LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
				i++;
				model[iMassive] = "";
			}
		}
		//=========================== квесты в поселениях ================================
		//--> перс Белый Мальчик
		if (loc.id == "Pearl_town_1" && !CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle"))
		{
			chr = GetCharacter(NPC_GenerateCharacter("JohnDavy", "Ole", "man", "man", 10, iPearNation, -1, false)); // постоянный перец, чтоб помнил реплики, второй раз он не создается, а просто ищется
			chr.dialog.Filename = "Quest\GhostShip_dialog.c";
			chr.name = FindPersonalName("JohnDavy_name");
			chr.lastname = FindPersonalName("JohnDavy_lastname");
			chr.CityType = "citizen";
			chr.city = "SantaCatalina"; //испанские НЗГ
			chr.RebirthPhantom = true;  // не тереть фантома-многодневку (с -1), если умер
			chr.greeting = "Gr_JohnDavy";
			PlaceCharacter(chr, "goto", "random");
			LAi_SetCitizenType(chr);
			LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
			SetLandQuestMarksToFantom(chr, "JohnDavy"); // фантом будет с квест-метками
		}
		//<-- перс Алекса
        // грузчики -->
        if (CheckAttribute(loc, "carrier") && IsLoginTime())
        {
            int iQtyCarrier = rand(1) + 1;
            for (i=iQtyCarrier; i>0; i--)
            {
                chr = GetCharacter(NPC_GenerateCharacter("Carrier", GetUniqCarrierModel("carrier_city"), "man", "genres", 35, iPearNation, 2, false));
                chr.id = chr.id + "_" + chr.index;
                aref aLocator;
                makearef(aLocator, loc.locators.reload);
                LAi_SetImmortal(chr, true);
                LAi_SetLoginTime(chr, 6.0, 23.0);//homo ночью пусть спят
                chr.plantation = "carrier";

                LAi_SetCarrierType(chr);
                if (sti(Colonies[iPearNation].HeroOwn))
                    LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
                else
                    LAi_group_MoveCharacter(chr, "PearlGroup_"+iPrefix);
            }
        }
        // грузчики <--
		//--> главарь грабителей
		if (loc.id == "Pearl_town_2" && sti(pchar.questTemp.tugs.berglarState) > 6)
		{
			pchar.quest.Berglars_Ostin.win_condition.l1 = "location";
			pchar.quest.Berglars_Ostin.win_condition.l1.location = "PearlTown2_House6";
			pchar.quest.Berglars_Ostin.win_condition = "Berglars_Ostin";
			//==> трем базу по квесту
			DeleteAttribute(pchar, "questTemp.tugs");
			//==> ставим счетчик, чтобы не глючило по коду
			pchar.questTemp.tugs.berglarState = 0;
		}
		//<-- главарь грабителей
		//=========================== квесты в поселениях ================================
		LAi_group_SetLookRadius("PearlGroup_"+iPrefix, 16);
		LAi_group_SetHearRadius("PearlGroup_"+iPrefix, 10);
	}
}

void CreateInsideHouseEncounters(aref loc)
{	
	if (CheckAttribute(loc, "MustSetReloadBack") && loc.id.label == "house" && !IsLocationCaptured(loc.fastreload+"_town"))
	{
		// проверяем разрешение города на формирование энкаунтеров
		int iBaseCity = FindLocation(loc.fastreload+"_town");
		int iColony = -1; // Rosarak. Для проверки владения городом
		if(CheckAttribute(loc, "fastreload")) iColony = FindColony(loc.fastreload);
		
		if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return;
		//==> блокируем квест мэра
		if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location") && pchar.GenQuest.SeekSpy.Location == loc.id) return;
		//==> блокируем квест доставки малявы
		if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") && pchar.questTemp.jailCanMove.Deliver.locationId == loc.id) return;
		//--> ночью не забалуешь
		bool bDN = IsDay();
    	aref arRld, arDis;
		makearef(arRld, loc.reload);
		int i;
    	int	Qty = GetAttributesNum(arRld);
		for (i=0; i<Qty; i++)
    	{
    		arDis = GetAttributeN(arRld, i);
    		if (arDis.name != "reload1")
    		{
				if (bDN && !isBadReputation(pchar, 40)) DeleteAttribute(arDis, "disable");
				else arDis.disable = true; //закрываем вход в коммоны 2 уровня
    		}
    	}
		//<-- ночью не забалуешь
		//==> блокируем локации второго уровня		
		if (locations[reload_cur_location_index].type == "town")
		{
			ref chr, npchar;
			aref rCity;
			makearef(rCity, locations[iBaseCity].houseEnc);		
			bool bMW = rand(1);
			int iNation = GetCityNation(loc.fastreload);
			bool pirate_town = iNation == PIRATE && !sti(Colonies[iColony].HeroOwn);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			string Model, Name, LastName, sName;
			string sTemp = reload_locator_ref.name + loc.index;
			int iManIdx = GetCharacterIndex("HouseMan_"+iBaseCity+"_"+loc.index);
			int iWomanIdx = GetCharacterIndex("HouseWoman_"+iBaseCity+"_"+loc.index);
			if (iWomanIdx != -1 || iManIdx != -1)
			{				
				if (!CheckAttribute(rCity, sTemp)) //уже есть хозяин, но дом не тот же, новый!!! сделаем из старого хозяина нового
				{
					if (iWomanIdx != -1) 
					{
						npchar = &characters[iWomanIdx];
						SetRandomNameToCharacter(npchar);
						if (pirate_town) npchar.model = "horse0"+(rand(7)+1);
						else
						{
							if (rand(9) > 0) npchar.model = "women_"+(rand(11)+1);
							else npchar.model = "oldWoman_"+(rand(3)+1);
						}
						FaceMaker(npchar);
						SetNewModelToChar(npchar);  // перерисуем модель на лету			
						LAi_SetActorType(npchar);
						LAi_ActorDialog(npchar, pchar, "", 1.0, 0);
						LAi_group_MoveCharacter(npchar, slai_group);
						rCity.(sTemp) = "woman"; //последний сгенеренный
						rCity.(sTemp).woman.model = npchar.model;
						rCity.(sTemp).woman.name = npchar.name;
						rCity.(sTemp).woman.lastname = npchar.lastname;
						//<-- запомним параметры нпс в структуре колонии
					}
					else
					{
						npchar = &characters[iManIdx];
						SetRandomNameToCharacter(npchar);
						if (pirate_town) npchar.model = "citiz_"+(rand(9)+21);
						npchar.model = "citiz_"+(rand(9)+11); //TODO: делим домики по стоимости
						FaceMaker(npchar);
						SetNewModelToChar(npchar);  // перерисуем модель на лету			
						LAi_SetActorType(npchar);
						LAi_ActorDialog(npchar, pchar, "", 1.0, 0);
						LAi_group_MoveCharacter(npchar, slai_group);
						//--> запомним параметры нпс в структуре колонии
						rCity.(sTemp) = "man"; //последний сгенеренный
						rCity.(sTemp).man.model = npchar.model;
						rCity.(sTemp).man.name = npchar.name;
						rCity.(sTemp).man.lastname = npchar.lastname;
						//<-- запомним параметры нпс в структуре колонии
					}
				}
				else //уже есть структура на дом с данными хозяина
				{
					if (iWomanIdx != -1) npchar = &characters[iWomanIdx];
					else npchar =  &characters[iManIdx];
					string sSex = sTemp + "." + rCity.(sTemp);
					if (rCity.(sSex).model != npchar.model) 
					{	//данные на хозяина другие, преобразим текущего	
						npchar.model = rCity.(sSex).model;
						if (rCity.(sTemp) == "man") 
						{
							npchar.sex = "man";
							npchar.model.animation = "man";
							npchar.dialog.currentnode = "HouseMan";
							if (pirate_town) npchar.greeting = "pirat_common";
							else npchar.greeting = "cit_common";
							LAi_NPC_Equip(npchar, sti(npchar.rank), true, true);
						}
						else 
						{
							npchar.sex = "woman";
							npchar.model.animation = "towngirl";
							npchar.dialog.currentnode = "HouseWoman";
							npchar.greeting = "Gr_Woman_Citizen";
							DeleteAttribute(npchar, "equip");
						}
						npchar.name = rCity.(sSex).name;
						npchar.lastname = rCity.(sSex).lastname;
						FaceMaker(npchar);
						SetNewModelToChar(npchar);  // перерисуем модель на лету					
					}
				}
				return;
			}
			Model = "";
			Name = "";
			LastName = "";
			//-->> генерился ли такой раньше		
			if (CheckAttribute(rCity, sTemp))
			{
				if (GetNpcQuestPastDayParam(rCity, sTemp) < 30)
				{
					if (rCity.(sTemp) == "man") 
					{//если был мужик, то след. - баба
						bMW = true;
						if (CheckAttribute(rCity, sTemp + ".woman.model"))
						{
							Model = rCity.(sTemp).woman.model;
							Name = rCity.(sTemp).woman.name;
							LastName = rCity.(sTemp).woman.lastname;
						}
						else
						{
							if (CheckAttribute(rCity, sTemp + ".man.lastname"))
							{
								LastName = rCity.(sTemp).man.lastname;
							}
						}
					}
					else 
					{//если была баба, то след. - мужик
						bMW = false;
						if (CheckAttribute(rCity, sTemp + ".man.model"))
						{
							Model = rCity.(sTemp).man.model;
							Name = rCity.(sTemp).man.name;
							LastName = rCity.(sTemp).man.lastname;
						}
						else
						{
							if (CheckAttribute(rCity, sTemp + ".woman.lastname"))
							{
								LastName = rCity.(sTemp).woman.lastname;
							}
						}
					}
				}
				else //смена хозяев в доме
				{
					if (rand(10) > 8) //шанс на пустой дом.
					{
						for (i=0; i<Qty; i++) 
    					{//снимаем возможный блок коммонов второго уровня (если репа у ГГ хреновая) 
    						arDis = GetAttributeN(arRld, i);
    						if (arDis.name != "reload1")
    						{
								DeleteAttribute(arDis, "disable");
    						}
    					}
						return;
					}
					SaveCurrentNpcQuestDateParam(rCity, sTemp); //пишем дату генерации первого нпс в этой локации
				}
			}
			else 
			{
				if (rand(10) > 8) //шанс на пустой дом.
				{
					for (i=0; i<Qty; i++) 
    				{//снимаем возможный блок коммонов второго уровня (если репа у ГГ хреновая) 
    					arDis = GetAttributeN(arRld, i);
    					if (arDis.name != "reload1")
    					{
							DeleteAttribute(arDis, "disable");
    					}
    				}
					return;
				}
				SaveCurrentNpcQuestDateParam(rCity, sTemp); //пишем дату генерации первого нпс в этой локации
			}
			//<<-- генерился ли такой раньше
			if (bMW)
			{//============= генерим бабу ====================
				if (Model == "")
				{
					if (pirate_town) Model = "horse0"+(rand(7)+1);
					else
					{
						if (rand(9) > 0) Model = "women_"+(rand(11)+1);
						else Model = "oldWoman_"+(rand(3)+1);
					}
				}
				sName = "HouseWoman_"+reload_cur_location_index+"_"+loc.index;
				chr = GetCharacter(NPC_GenerateCharacter(sName, Model, "woman", "towngirl", rand(2)+4, iNation, 3, false));
				if (Name != "") chr.name = Name;
				if (LastName != "") chr.lastname = LastName;
				chr.dialog.Filename = "House_dialog.c";
				chr.dialog.currentnode = "HouseWoman";
				chr.CityType = "citizen";
				chr.city = loc.fastreload; //НЗГ
				chr.greeting = "Gr_Woman_Citizen";			
				ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
				LAi_SetActorType(chr);
				LAi_ActorDialog(chr, pchar, "", 1.0, 0);
				if (iColony != -1 && sti(Colonies[iColony].HeroOwn))
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
				//--> запомним параметры нпс в структуре колонии
				rCity.(sTemp) = "woman"; //последний сгенеренный
				rCity.(sTemp).woman.model = chr.model;
				rCity.(sTemp).woman.name = chr.name;
				rCity.(sTemp).woman.lastname = chr.lastname;
				//<-- запомним параметры нпс в структуре колонии
			}
			else
			{//============ генерим мужика ==================
				if (Model == "")
				{
					if (pirate_town) Model = "citiz_"+(rand(9)+21);
					else Model = "citiz_"+(rand(9)+11);
				}
				sName = "HouseMan_"+reload_cur_location_index+"_"+loc.index;
				chr = GetCharacter(NPC_GenerateCharacter(sName, Model, "man", "man", rand(10)+4, iNation, 3, true));
				if (Name != "") chr.name = Name;
				if (LastName != "") chr.lastname = LastName;
				chr.dialog.Filename = "House_dialog.c";
				chr.dialog.currentnode = "HouseMan";
				chr.CityType = "citizen";
				chr.city = loc.fastreload; //НЗГ
				if (pirate_town) chr.greeting = "pirat_common";
				else chr.greeting = "cit_common";
				ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
				LAi_SetActorType(chr);
				LAi_ActorDialog(chr, pchar, "", 1.0, 0);
				if (iColony != -1 && sti(Colonies[iColony].HeroOwn))
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
				//--> запомним параметры нпс в структуре колонии
				rCity.(sTemp) = "man"; //последний сгенеренный
				rCity.(sTemp).man.model = chr.model;
				rCity.(sTemp).man.name = chr.name;
				rCity.(sTemp).man.lastname = chr.lastname;
				//<-- запомним параметры нпс в структуре колонии
			}
		}
		//==> следование хозяина за ГГ в другие комнаты дома
		else
		{
			//если в комнате уже есть кто-то, то не следуем за ГГ на второй этаж
			for(int n=0; n<MAX_CHARACTERS; n++)
			{
				if (characters[n].location == pchar.location && characters[n].id != "Blaze")
				{
					return;
				}
			}
			//переносим хозяина на второй этаж				
			int iLocIndexEnc;
			if (pchar.location.locator == "reload1") iLocIndexEnc = reload_cur_location_index;
			else iLocIndexEnc = reload_location_index;
			int iEnc = GetCharacterIndex("HouseWoman_"+iBaseCity+"_"+iLocIndexEnc);
			if (iEnc != -1)
			{
				ChangeCharacterAddressGroup(&characters[iEnc], loc.id, "barmen", "stay");
			}
			else
			{
				iEnc = GetCharacterIndex("HouseMan_"+iBaseCity+"_"+iLocIndexEnc);
				if (iEnc != -1)
				{
					ChangeCharacterAddressGroup(&characters[iEnc], loc.id, "barmen", "stay");
				}
			}
			
		}
	}
}

//энкаунтеры в резиденциях
void CreateInsideResidenceEncounters(aref loc)
{	
	bool bOk;
	if (CheckAttribute(loc, "MustSetReloadBack") || loc.id == "Villemstad_BedRoomK2")
	{ //если заглушка
		if (loc.id.label == "TownhallRoom" || loc.id.label == "Townhall")
		{
			bOk = CreateQuestResidenceNPC(loc);
			if(!bOk) 
			{
				CreateResidenceNpc(loc);
			}	
		}	
	}
	else
	{ //если статичная локация
		if (loc.id.label == "TownhallRoom")
		{
			bOk = CreateQuestResidenceNPC(loc);
			if(!bOk)
			{
				CreateResidenceNpc(loc);
			}	
		}	
	}
}
//относится к методу выше
void CreateResidenceNpc(aref loc)
{
	ref chr;
	int Rank;
	string sModel, sSex, sAni, sNode, sGreeting;
	bool bWeapon;
	if (!CheckAttribute(loc, "fastreload")) return;
	int iBaseCity = FindLocation(loc.fastreload + "_town");
	int iColony = FindColony(loc.fastreload);
	
	if (!CheckAttribute(&locations[iBaseCity], "houseEnc")) return;
	if (rand(10) > 8) return; //шанс на пустую комнату
	//==> выбираем тип
	int iEncType = rand(2); //0 - служанка, 1 - прислуга, 2 - солдат.
	if (loc.id.label  == "TownhallRoom") iEncType = 2;
	if (CheckAttribute(loc, "Bedroom"))  iEncType = 0;	
	if (CheckAttribute(loc, "PlayHall")) iEncType = 1;	
	int iNation = GetCityNation(loc.fastreload);
	if (iNation == PIRATE && iColony != -1 && !sti(Colonies[iColony].HeroOwn)) return; // Rosarak. Убираем только в пиратских городах, для колоний ГГ оставляем
	switch (iEncType)
	{
	case 0:
		Rank = 3;
		if(rand(9) == 0) sModel = "oldwoman_"+(rand(3)+1);
		else sModel = "women_"+(rand(11)+1);
		sSex = "woman";
		sAni = "towngirl";
		bWeapon = false;
		sNode = "ResWoman";
		sGreeting = "Gr_Woman_Citizen";
		break;
	case 1:
		Rank = 5;
		sModel = "barmen_"+(rand(15)+1);
		sSex = "man";
		sAni = "man";
		bWeapon = true;
		sNode = "ResMan";
		sGreeting = "worker";
		break;
	case 2:
		Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
		if(iColony != -1 && !sti(Colonies[iColony].HeroOwn)) sModel = "guard_" + NationShortName(iNation) + "_" + (rand(3)+1);
		else sModel = "citiz_" + (rand(9)+51);
		sSex = "man";
		sAni = "man";
		bWeapon = true;
		sNode = "ResGuard";
		sGreeting = "guardHouse";
		break;
	}
	//==> генерим непися
	string slai_group = GetNationNameByType(iNation) + "_citizens";		
	string sName = "EncResidence_" + iBaseCity + "_" + loc.index;
	if (GetCharacterIndex(sName) > 0) return; //если есть
	chr = GetCharacter(NPC_GenerateCharacter(sName, sModel, sSex, sAni, Rank, iNation, 1, bWeapon));
	chr.dialog.Filename = "Residence_dialog.c";
	chr.dialog.currentnode = sNode;
	chr.CityType = "citizen";
	chr.city = loc.fastreload; //НЗГ
	chr.greeting = sGreeting;
	if(chr.sex == "woman") 			
	{
		//Для служанок введём даты секса, чтобы не предлагать слишком часто
		SaveCurrentNpcQuestDateParam(chr, "sex");
		chr.sex.control_day = -3; //Скручивание счётчика для самой первой проверки
		int iRand = rand(19); //75% свободна, 5% мутки с наместником, 20% замужем
		chr.relations = "";
		if (iRand > 4) chr.relations = 1;
		if (iRand == 0) chr.relations = 2;
	}
	ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
	LAi_SetOwnerType(chr);
	if (iColony != -1 && sti(Colonies[iColony].HeroOwn))
	{
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
	}
	else
	{
		LAi_group_MoveCharacter(chr, slai_group);
	}
}

bool CreateQuestResidenceNPC(aref loc)
{
	bool bOk;
	if(CheckAttribute(pchar,"questTemp.ReasonToFast"))
	{
		if(!CheckAttribute(pchar,"questTemp.ReasonToFast.GenerateLakey") && (pchar.questTemp.ReasonToFast.chain == "A1"))
		{
			// генерим лакея
			if(CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther")) return false;
			bOk = ReasonToFast_CreateResidenceNPC(loc);
			if(bOk) 
			{
				pchar.questTemp.ReasonToFast.GenerateLakey = true;
				return true;	
			}
			else return false;	
		}
	}
	return false;
}

//энкаунтеры на склад верфи и магазине
void CreateSkladInsideEncounters(aref loc)
{
	if (CheckAttribute(loc, "packhouse") && !IsLocationCaptured(loc.id))
	{
		if (CheckAttribute(&TEV, "SkladManIsDead") && HasStr(TEV.SkladManIsDead, "SkladMan_" + loc.index))
			return;
		
		ref chr;
		int iNation = GetCityNation(loc.fastreload);
		int iColony = -1;
		if(CheckAttribute(loc, "fastreload")) iColony = FindColony(loc.fastreload);
		
		string slai_group = GetNationNameByType(iNation) + "_citizens";		
		string sName = "SkladMan_"+loc.index;
		if (GetCharacterIndex(sName) > 0) return; //если есть
		int Rank = sti(pchar.rank) + rand(6);
		if (Rank < 10) Rank += 10;
		if (Rank > 30) Rank -= 10;
		chr = GetCharacter(NPC_GenerateCharacter(sName, "citiz_"+(rand(9)+51), "man", "man", Rank, iNation, 2, true));
		chr.dialog.Filename = "House_dialog.c";
		chr.dialog.currentnode = "SkladMan";
		chr.CityType = "citizen";
		chr.city = loc.fastreload; //НЗГ
		LAi_LoginInCaptureTown(chr, false);

		if (CheckAttribute(loc, "type") && loc.type == "shipyard")
		{
		    ChangeCharacterAddressGroup(chr, loc.id, "goto", "goto1");
		    LAi_SetWarriorType(chr);
		}
		else
		{
		    ChangeCharacterAddressGroup(chr, loc.id, "barmen", "stay");
            LAi_SetOwnerType(chr);
		}
		
		if (iColony != -1 && sti(Colonies[iColony].HeroOwn))
		{
			chr.greeting = "Gr_Guard";
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
		}
		else
		{
			chr.greeting = "pirat_common";
			LAi_group_MoveCharacter(chr, slai_group);
		}
	}
}

//тюрьма
void CreateJail(aref loc)
{
	if (loc.type == "jail")
	{
		ref sld;
		string LocatorGroup, LocatorName, slai_group, nShortName;
		int i, nSit, iNation, iRank;
		float fJailTakeMoneyChance;
		if(!CheckAttribute(pchar, "isload") && reload_location_index != reload_cur_location_index)
		{
			pchar.questTemp.jailCanMove = false;
		}
		if (CheckNPCQuestDate(loc, "Jail_date"))
		{
			SetNPCQuestDate(loc, "Jail_date");
			LAi_group_Delete("Prisoner_Group");
			iNation = GetCityNation(loc.parent_colony);
			slai_group = GetNationNameByType(iNation)  + "_citizens";
			nShortName = NationShortName(iNation);
			iRank = sti(pchar.rank) + rand(4);
			if (iRank < 10) iRank = 10;
			if (iRank > 20) iRank = 20;
			//====> начальник тюрьмы
			sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"JailOff", "off_"+nShortName+"_"+(rand(1)+3), "man", "man", iRank+5, iNation, 2, true));
			if (sti(colonies[FindColony(loc.parent_colony)].jail) && !CheckAttribute(sld, "jailTakeMoney"))
			{
				fJailTakeMoneyChance = 0.5 + (GetCharacterSPECIAL(pchar, SPECIAL_C) > 5) * 0.03 * (GetCharacterSPECIAL(pchar, SPECIAL_C) - 5) +
					(GetCharacterSPECIAL(pchar, SPECIAL_L) > 5) * 0.03 * (GetCharacterSPECIAL(pchar, SPECIAL_L) - 5);
				sld.jailTakeMoney = frandSmall(1.0) < fJailTakeMoneyChance; // начальник тюрьмы мздоимец, шанс 50% + 3% за каждый поинт A, S > 5
			}
			
			sld.City = loc.parent_colony;
			sld.CityType = "soldier";
			sld.standUp = true; //вставать и нападать на врага
 			sld.Dialog.Filename = "Common_prison.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Gr_Guard";
			FantomMakeCoolFighter(sld, iRank+5, 70, 50, BLADE_LONG, "pistol3", 30); //спецназ
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, slai_group);
			ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit1");
			SetLandQuestMarksToFantom(sld, "JailOff");
			//====> солдаты
			for (i=1; i<=4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"JailSold_"+i, "urban_"+nShortName+"_"+(rand(7)+1), "man", "man", iRank, iNation, 2, true));
				sld.City = loc.parent_colony;
				sld.CityType = "soldier";
				sld.rank = iRank;
				sld.Dialog.Filename = "Common_prison.c";
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, slai_group);
				locatorName = PlaceCharacter(sld, "soldiers", "random_free");			
				if (locatorName == "protector1")
				{
					sld.protector = true;
					sld.protector.CheckAlways = 1; //проверять всегда
					sld.dialog.currentnode = "First_protector";
					sld.greeting = "soldier_arest";
				}
				else
				{
					sld.dialog.currentnode = "First_soldier";
					sld.greeting = "soldier_common";
				}
			}
			//====> зеки
			for (i=1; i<=10; i++)
			{
				if (rand(100)<70)
				{
					sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"Prisoner_"+i, "Prison_"+(rand(5)+1), "man", "man", 10, iNation, 2, false));							
					sld.Dialog.Filename = "Common_prison.c";
					sld.dialog.currentnode = "First_prisoner";
					sld.City = loc.parent_colony;
					sld.greeting = "Gr_prison";
					//LAi_LoginInCaptureTown(sld, true);
					LAi_SetLoginTime(sld, 0.0, 24.0);
					LAi_SetActorType(sld);
					locatorName = "prison"+i;
					if (rand(10)>5) 
					{
						LAi_ActorSetLayMode(sld);
						locatorName += "lay";
					}
					else LAi_SetGroundSitType(sld);
					LAi_group_MoveCharacter(sld, "Prisoner_Group");
					ChangeCharacterAddressGroup(sld, loc.id, "prison", locatorName);
				}
			}
		}
	}
}

//форты
void CreateFortsNPC(aref loc)
{	
	if (loc.type == "fort")
	{
		int iNation = GetCityNation(loc.parent_colony);	
		if(iNation == -1) return;
		string slai_group = GetNationNameByType(iNation)  + "_citizens";
		if (locations[reload_cur_location_index].type == "jail" && GetNationRelation2MainCharacter(iNation) == RELATION_ENEMY && !CheckAttribute(loc, "loginNpc"))
		{
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			return;
		}
		DeleteAttribute(loc, "loginNpc"); //снимаем возможный флаг на генерацию нпс при выходе из тюрьмы
		if (GetNpcQuestPastDayWOInit(loc, "Fort_date") < 2) return;
		ref chr;
		int iCitizensQuantity, iChar, i;
		string locatorName, sType;
		int iColony = -1;
		SaveCurrentNpcQuestDateParam(loc, "Fort_date");
		if(CheckAttribute(loc, "parent_colony")) iColony = FindColony(loc.parent_colony);
		if(iColony == -1) return;		
		arrayNPCModelHow = 0;
		aref solderLoc, st;
		// солдаты -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
		{
			makearef(st, loc.locators.soldiers);
			iCitizensQuantity = GetAttributesNum(st);		
			for (i=0; i<iCitizensQuantity; i++)
			{	
				if(iNation != PIRATE)
				{
					sType = "army_sold";
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
				}
				else
				{
					sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "soldier";
				chr.RebirthPhantom = true;
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
				SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
				solderLoc = GetAttributeN(st, i);
				locatorName = GetAttributeName(solderLoc);
				ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", locatorName);
				// eddy. проверяем, должен ли солдат быть протектором -->
				if (HasSubStr(locatorName, "protector") && iNation != PIRATE) 
				{
					chr.protector = true;
					chr.greeting = "soldier_arest";
				}
				else chr.greeting = "soldier_common";
				// <-- eddy. проверяем, должен ли солдат быть протектором
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetGuardianType(chr);
				if (sti(Colonies[iColony].HeroOwn))
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
				}
				chr.dialog.filename = "Common_Fort.c";
				chr.dialog.currentnode = "First time";
			}
		}
		// солдаты <--
		// патруль -->
		if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.patrol"))
		{			
			makearef(st, loc.locators.patrol);
			iCitizensQuantity = GetAttributesNum(st);
			for (i=0; i<iCitizensQuantity; i++)
			{
				if(iNation != PIRATE)
				{
					sType = "army_sold";
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
				}
				else
				{
					sType = "pirate";
					iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
				}
				chr = &characters[iChar];
				SetNPCModelUniq(chr, sType, MAN);
				chr.City = Colonies[iColony].id;
				chr.CityType = "fortPatrol";
				SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
				chr.RebirthPhantom = true;
				LAi_CharacterReincarnation(chr, true, true);
				LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetPatrolType(chr);

				if (sti(Colonies[iColony].HeroOwn))
				{
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
					chr.greeting = "pirat_guard";
				}
				else
				{
					LAi_group_MoveCharacter(chr, slai_group);
					chr.greeting = "soldier_common";
				}
				PlaceCharacter(chr, "patrol", "random_free");
				chr.dialog.filename = "Common_Fort.c";
				chr.dialog.currentnode = "First time";
			}
		}
		// патруль <--
	}
}

void CreateAmmo(aref loc) // Jason, оружейная
{
	if (loc.type == "ammo")
	{
		ref sld;
		int i, iNation, iRank;			
		if (!CheckAttribute(loc, "Ammo_date") || GetNpcQuestPastDayParam(loc, "Ammo_date") > 2)
		{
			SaveCurrentNpcQuestDateParam(loc, "Ammo_date");
			iNation = GetCityNation(loc.parent_colony);
			string slai_group = GetNationNameByType(iNation)  + "_citizens";
			iRank = sti(pchar.rank)+5+MOD_SKILL_ENEMY_RATE*2;
			// комендант
			sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"AmmoOff", "off_"+NationShortName(iNation)+"_"+(rand(4)+7), "man", "man", iRank, iNation, 2, true));
			FantomMakeCoolFighter(sld, iRank+5, 70, 70, BLADE_LONG, GUN_COMMON, 100);
			sld.City = loc.parent_colony;
			sld.CityType = "soldier";
			sld.standUp = true; //вставать и нападать на врага
			sld.Dialog.Filename = "Common_Ammo.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "soldier_common";
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, slai_group);
			ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit1");
			SetLandQuestMarksToFantom(sld, "AmmoOff");
			// солдаты
			for (i=1; i<=3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter(loc.parent_colony+"AmmoSold_"+i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+9), "man", "man", iRank, iNation, 2, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, iRank, 60, 60, BLADE_LONG, GUN_COMMON, 50);
				sld.City = loc.parent_colony;
				sld.CityType = "soldier";
				sld.rank = iRank;
				sld.Dialog.Filename = "Common_soldier.c";
				sld.greeting = "Gr_Guard";
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetGuardianType(sld);
				LAi_group_MoveCharacter(sld, slai_group);
				ChangeCharacterAddressGroup(sld, loc.id, "soldiers", "soldier"+i);
			}
		}
	}
}

void CreateHWICOffice(aref loc)//Jason, заполнение офиса ГВИК
{
	if (CheckAttribute(loc, "HWIC"))
	{
		ref sld;
		int i;
		if (GetCityNation("Villemstad") != HOLLAND)
        {
            sld = CharacterFromId("HWIC_headclerk");
            if (sld.location == "none") return;
            DeleteAttribute(loc, "HWIC_date");
            for (i=1; i<=6; i++)
            {
                if (GetCharacterIndex("HWIC_sold_"+i != -1)) ChangeCharacterAddress(CharacterFromId("HWIC_sold_"+i), "none", "");
            }
            for (i=1; i<=2; i++)
            {
                if (GetCharacterIndex("HWIC_clerk_"+i != -1)) ChangeCharacterAddress(CharacterFromId("HWIC_clerk_"+i), "none", "");
            }
            ChangeCharacterAddress(sld, "none", "");
        }
        else
        {
            if (!CheckAttribute(loc, "HWIC_date") || GetNpcQuestPastDayParam(loc, "HWIC_date") >= 30)
            {
                SaveCurrentNpcQuestDateParam(loc, "HWIC_date");
                //солдаты, 5 шт
                arrayNPCModelHow = 0;
                for (i=1; i<=6; i++)
                {
                    if  (i == 3) continue;
                    sld = GetCharacter(NPC_GenerateCharacter("HWIC_sold_"+i, "wic_hol_"+(rand(7)+1), "man", "man", 25, HOLLAND, 30, false));
                    FantomMakeCoolFighter(sld, 35, 90, 90, "blade7", "pistol1", 100);
                    SetNPCModelUniq(sld, "hwic", MAN);
                    sld.Dialog.Filename = "HWIC_Office.c";
                    sld.dialog.currentnode = "HWIC_soldier";
                    sld.greeting = "Gr_Guard";
                    ChangeCharacterAddressGroup(sld, "GVIK", "soldiers", "soldier"+i);
                    LAi_SetGuardianType(sld);
                    LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
                }
                //клерки, 2 шт
                arrayNPCModelHow = 0;
                for (i=1; i<=2; i++)
                {
                    sld = GetCharacter(NPC_GenerateCharacter("HWIC_clerk_"+i, "citiz_"+(rand(9)+11), "man", "man", 10, HOLLAND, 30, false));
                    SetNPCModelUniq(sld, "diplomat", MAN);
                    SetFantomParamFromRank(sld, 10, true);
                    sld.Dialog.Filename = "HWIC_Office.c";
                    sld.dialog.currentnode = "HWIC_clerk";
                    sld.greeting = "official";
                    RemoveAllCharacterItems(sld, true);
                    LAi_SetLoginTime(sld, 6.0, 21.99);
                    LAi_SetHuberType(sld);
                    ChangeCharacterAddressGroup(sld, "GVIK", "sit", "sit"+i);
                    LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
                }
            }
            // главный клерк
            sld = CharacterFromId("HWIC_headclerk");
            if (sld.location != "GVIK") ChangeCharacterAddressGroup(sld, "GVIK", "sit", "sit3");
        }
	}
}

// KZ > заселение форта в джунглях основными NPC, выполняется один раз
void CreateSecretFort()
{
	ref sld;
	string slai_group = "Group_Secret_Fort";
	int i, iRank = sti(pchar.rank) + 5 + MOD_SKILL_ENEMY_RATE * 2;

	sld = &locations[FindLocation("Shore_ship2")];

	DeleteAttribute(sld, "deadlocked");
	sld.reload.l1.go = "Beliz_jungle_04";

	LocatorReloadEnterDisable("Secret_Fort_Exit", "reload3", true);

	sld = &locations[FindLocation("Secret_Fort_Tizer_House")];
	sld.secret1.difficult = -2;

	for (i = 0; i <= 1; i++)
	{
		iRank = sti(pchar.rank) + 5 + MOD_SKILL_ENEMY_RATE * 2;
		sld = GetCharacter(NPC_GenerateCharacter("Secret_Fort_Exit_Man" + i, "panhandler_1" + i, "man", "man", iRank, PIRATE, -1, true));
		FantomMakeCoolFighter(sld, iRank + 5, 70, 70, BLADE_LONG, GUN_COMMON, 100);
		sld.dialog.Filename = "Quest\LostShipsCity\Secret_Fort.c";
		sld.dialog.currentnode = "First time patrol";
		LAi_RemoveLoginTime(sld);
		LAi_group_MoveCharacter(sld, "Group_Secret_Fort");
		ChangeCharacterAddressGroup(sld, "Secret_Fort_Exit", "officers", "reload3_" + (i + 1));
		LAi_SetGuardianType(sld);
		sld.protector = true;
		sld.protector.CheckAlways = 1;
		sld.greeting = "Gr_SecretFort_Patrol";
	}

	// > главный бродяга
	sld = GetCharacter(NPC_GenerateCharacter("Secret_Fort_Commander", "DEDnoName", "man", "man", iRank, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, iRank + 5, 70, 70, BLADE_LONG, GUN_COMMON, 100);
	sld.name = FindPersonalName("SecretFortCommander_name");
	sld.lastname = FindPersonalName("SecretFortCommander_lastname");
	sld.standUp = true;
	sld.Dialog.Filename = "Quest\LostShipsCity\Secret_Fort.c";
	sld.dialog.currentnode = "First time commander";
	sld.greeting = "Gr_SecretFort_Commander";
	LAi_SetLoginTime(sld, 0.0, 24.0);
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, slai_group);
	ChangeCharacterAddressGroup(sld, "Secret_Fort_Ammo", "sit", "sit1");

	// > бродяга в арсенале
	iRank = sti(pchar.rank) + 5 + MOD_SKILL_ENEMY_RATE * 2;
	sld = GetCharacter(NPC_GenerateCharacter("Secret_Fort_Guard", "panhandler_12", "man", "man", iRank, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, iRank, 60, 60, BLADE_LONG, GUN_COMMON, 50);
	sld.name = FindPersonalName("SecretFortGuard_name");
	sld.Dialog.Filename = "Quest\LostShipsCity\Secret_Fort.c";
	sld.dialog.currentnode = "First time guard";
	sld.greeting = "Gr_Guard";
	LAi_SetLoginTime(sld, 0.0, 24.0);
	LAi_SetGuardianType(sld);
	LAi_group_MoveCharacter(sld, slai_group);
	ChangeCharacterAddressGroup(sld, "Secret_Fort_Ammo", "soldiers", "soldier" + (1 + rand(2)));

	// > бродяга в таверне за стойкой TODO > функционал
	iRank = sti(pchar.rank) + 5 + MOD_SKILL_ENEMY_RATE * 2;
	sld = GetCharacter(NPC_GenerateCharacter("Secret_Fort_Tavern_Barman", "prison_6", "man", "man", iRank, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, iRank + 5, 70, 70, BLADE_LONG, GUN_COMMON, 100);
	sld.dialog.Filename = "Quest\LostShipsCity\Secret_Fort.c";
	sld.dialog.currentnode = "First time barman";
	LAi_group_MoveCharacter(sld, slai_group);
	ChangeCharacterAddressGroup(sld, "Secret_Fort_Tavern", "barmen", "stay");
	LAi_SetBarmanType(sld);
	LAi_RemoveLoginTime(sld);
	sld.greeting = "Gr_SecretFort_Barman";

	CreateSecretFortNPC();
}

// KZ > заселение форта в джунглях временными NPC, выполняется раз в 7-10 дней
void CreateSecretFortNPC()
{
	ref sld;
	string slai_group = "Group_Secret_Fort";
	int i, q, iRank = sti(pchar.rank) + 5 + MOD_SKILL_ENEMY_RATE * 2;

	string sLocator, sModel, arLocators[2], arModels[2];

	// > подбор уникальной модельки
	for (i = 2; i <= 12; i++)
	{
		if (i == 6) i++;
		else if (i == 10 || i == 11) i = 12;
		ArrayAddValue(&arModels, "panhandler_" + i);
	}

	for (i = 0; i < 32; i++)
	{
		ArrayAddValue(&arLocators, "goto" + (i + 1));
	}

	// > бродяги во дворе форта (1-3)
	q = 1 + rand(2);
	for (i = 1; i <= q; i++)
	{
		sLocator = ArrayGetRandomValue(&arLocators);
		ArrayRemoveValue(&arLocators, sLocator);

		sModel = ArrayGetRandomValue(&arModels);
		ArrayRemoveValue(&arModels, sModel);

		if (sModel == "" || sLocator == "") continue;

		iRank = sti(pchar.rank) + 5 + MOD_SKILL_ENEMY_RATE * 2;
		sld = GetCharacter(NPC_GenerateCharacter("Secret_Fort_Man" + i, sModel, "man", "man", iRank, PIRATE, 3, true));
		FantomMakeCoolFighter(sld, iRank + 5, 70, 70, BLADE_LONG, GUN_COMMON, 100);
		sld.dialog.Filename = "Quest\LostShipsCity\Secret_Fort.c";
		sld.dialog.currentnode = "First time courtyard";
		LAi_group_MoveCharacter(sld, slai_group);
		LAi_SetLoginTime(sld, 0.0, 24.0);
		ChangeCharacterAddressGroup(sld, "Secret_Fort", "goto", sLocator);
		LAi_SetWarriorType(sld);
		sld.greeting = "Gr_poorman";
	}

	// > бродяга в церкви (1)
	sLocator = ArrayGetRandomValue(&arLocators);
	ArrayRemoveValue(&arLocators, sLocator);

	sModel = ArrayGetRandomValue(&arModels);
	ArrayRemoveValue(&arModels, sModel);

	if (sModel != "" && sLocator != "")
	{
		iRank = sti(pchar.rank) + 5 + MOD_SKILL_ENEMY_RATE * 2;
		sld = GetCharacter(NPC_GenerateCharacter("Secret_Fort_Tavern_Man" + i, sModel, "man", "man", iRank, PIRATE, 3, true));
		FantomMakeCoolFighter(sld, iRank + 5, 70, 70, BLADE_LONG, GUN_COMMON, 100);
		sld.dialog.Filename = "Quest\LostShipsCity\Secret_Fort.c";
		sld.dialog.currentnode = "First time chapel";
		LAi_group_MoveCharacter(sld, slai_group);
		LAi_SetLoginTime(sld, 6.0, 21.99);
		LAi_SetWarriorType(sld);
		ChangeCharacterAddressGroup(sld, "Secret_Fort_Chapel", "goto", "goto3");
		sld.greeting = "Gr_SecretFort_Padre_" + GetSexCase(pchar, "Man", "Woman", "Man");
	}

	// бродяги в таверне за столом (1-2) TODO > сделать картёжниками
	q = 1 + rand(1);
	for (i = 1; i <= q; i++)
	{
		if (i == 1) sModel = "panhandler_1";
		else sModel = "panhandler_6";

		iRank = sti(pchar.rank) + 5 + MOD_SKILL_ENEMY_RATE * 2;
		sld = GetCharacter(NPC_GenerateCharacter("Secret_Fort_Tavern_Man" + i, sModel, "man", "man", iRank, PIRATE, 3, true));
		FantomMakeCoolFighter(sld, iRank + 5, 70, 70, BLADE_LONG, GUN_COMMON, 100);
		sld.dialog.Filename = "Quest\LostShipsCity\Secret_Fort.c";
		sld.dialog.currentnode = "First time gambler";
		LAi_group_MoveCharacter(sld, slai_group);
		LAi_SetLoginTime(sld, 0.0, 24.0);
		ChangeCharacterAddressGroup(sld, "Secret_Fort_Tavern", "sit", "sit_base" + i);
		LAi_SetSitType(sld);
		sld.greeting = "Gr_poorman";
	}

	TEV.SecretFortUnlocked = "";
	SaveEventStartTime("CreateSecretFortNPC");
}

/// boal
// проверка локации на сгенеренного в ней фантома многодневку, если есть, то новый не плодим
bool isLocationHasCitizens(string _locId)
{
    ref rCharacter; //ищем
	int n, Qty;
	bool bOk = false;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "CityType")) // признак фантома-многодневки
		{
            if (rCharacter.location == _locId)
			{
				bOk = true;
				if (rCharacter.chr_ai.type == "patrol")
				{
					if(_locId == "Villemstad_town" && Whr_IsDay() == 0) TEV.place_check = "Villemstad";
					PlaceCharacter(rCharacter, "patrol", "random_free"); //патруль генерится в разных локаторах
				}
			}
		}
    }
	return bOk;
}

void ReSitCharacterOnFree(ref chr, string _locId, string sTemp)
{
	int n, k;
	
	n = 0;
	while (!CheckFreeLocator(_locId, sTemp, sti(chr.index)) && n < 10)
	{
	    sTemp = PlaceCharacter(chr, "sit", "random_free");
	    n++;
	}
	
	n = 0;
	while (HasSubStr(sTemp, "sit_front") && n < 20)
	{    // чтоб не занимали место напротив
	    sTemp = PlaceCharacter(chr, "sit", "random_free");
	    k = 0;
	    while (!CheckFreeLocator(_locId, sTemp, sti(chr.index)) && k < 10)
		{
		    sTemp = PlaceCharacter(chr, "sit", "random_free");
		    k++;
		}
	    n++;
	}
}

bool CheckNPCModelUniq(ref chr)
{
	int   i, n;
	bool  bOk;
	string sModel = chr.model;
	
    bOk = true;
	for (i=0; i<arrayNPCModelHow; i++)
	{
	    if (arrayNPCModel[i] == sModel)
	    {
	        bOk = false;
	        break;
	    }
	}
	return bOk;
}

void SetNPCModelUniq(ref chr, string sType, int iSex)
{
	if (sType == "") return; //под GetModelType
	
	int i = 0;
	while (!CheckNPCModelUniq(chr) && i < 10)
	{
	    i++;
	    CreateModel(sti(chr.index), sType, iSex);
	}
	arrayNPCModel[arrayNPCModelHow] = chr.model;
	arrayNPCModelHow++;
}

bool CanGenerateAffairOfHonor(aref loc, int iColony)
{
	//HardCoffee ref условий генерации
	if (GetCharacterIndex("AffairOfHonor_QuestMan") != -1) return false;
	if (pchar.questTemp.CapBloodLine == "1") return false;
	if (Colonies[iColony].HeroOwn == "1") return false;
	if (Colonies[iColony].id == "PortRoyal") return false;
	if (Colonies[iColony].id == "FortOrange") return false;
	if (!IsDay()) return false;
	if (GetGlobalTutor())  return false;
	if (idRand("GenerateAffairOfHonor", 10) != 5) return false;

	bool bGenerate = false;
	// добавить условия сложности
	if (MOD_SKILL_ENEMY_RATE < 10)
	{
		bGenerate = sti(pchar.rank) > 5;
		if (bGenerate) bGenerate =
		GetSummonSkillFromName(Pchar, "FencingLight") > 49
		|| GetSummonSkillFromName(Pchar, "Fencing") > 49
		|| GetSummonSkillFromName(Pchar, "FencingHeavy") > 49;
	}
	else bGenerate = true;

	if (!bGenerate) return false;

	//Warship локацию маяка перезаписываем только если текущего квеста нет, параллель не предусмотрена
	if (AffairOfHonor_GetCurQuest() != "") return false;

	pchar.questTemp.AffairOfHonor.LighthouseId = Colony_GetLighthouseId(loc.fastreload);
	if (PChar.QuestTemp.AffairOfHonor.LighthouseId == "") return false;

	if (!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FinishCount"))
	{
		PChar.QuestTemp.AffairOfHonor.FinishCount = 0;
	}

	return true;
}

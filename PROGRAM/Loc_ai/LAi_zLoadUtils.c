//Город погибших кораблей
void CreateLostShipsCity(aref loc)
{	
	int i;
	ref sld;
	int locNum, n, Index;
	bool isLSCInsideLoc;
	
	if (loc.id == "LostShipsCity_town" && isDay())
	{
		string sTemp, sLocator;
		int qtyTavern = 0;
		int qtyResidence = 0;
		int qtyChurch = 0;
		int qtyPrison = 0;
		int qtyStore = 0;
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (sld.location == "FleuronTavern") qtyTavern++;
			if (sld.location == "SanAugustineResidence") qtyResidence++;
			if (sld.location == "GloriaChurch") qtyChurch++;
			if (sld.location == "TartarusPrison") qtyPrison++;
			if (sld.location == "EsmeraldaStoreBig") qtyStore++;
		}
		//размещаем нпс
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (CheckAttribute(sld, "city") && sld.city == "LostShipsCity")
			{
				//////// если это адмирал /////////
				if (sld.cityTape == "mayor")
				{
					if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours))
					{
						DeleteAttribute(sld, "location.going"); //снимаем флаг
						//--> вечером организовываем толпу в таверне
						if (GetTime() > 19.0 && rand(1))
						{
							if (qtyTavern < LSC_MAX_TAVERN)
							{
								sld.location.going = "toTavern"; //флаг генерации в таверне
								qtyTavern++;
							}
							continue;
						}
						//<-- вечером организовываем толпу в таверне
						if (sld.location == "SanAugustineResidence") //если адмирал в резиденции
						{
							if (rand(1))	//вероятность выхода из резиденции
							{
								SaveCurrentNpcQuestDateParam(sld, "location");
								sld.location.hours = rand(5)+1;
								if (rand(1))
								{	//выходим на улицы
									//проверим занятость локатора								
									if (!LAi_CheckLocatorFree("goto", sld.location.baseLocator))
									{	//выберем незанятый 
										sTemp = sld.location.baseLocator;									
										sTemp = strcut(sTemp, 4, 5);
										for (n=0; n<=9; n++)
										{											
											sLocator = "goto" + sTemp + "_" + n;
											if (LAi_CheckLocatorFree("goto", sLocator))
											{
												LAi_SetLSCoutTypeNoGroup(sld);
												ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sLocator);
												break;
											}
										}
									}
									else
									{
										LAi_SetLSCoutTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
									}
								}
								else
								{	//в таверну
									if (qtyTavern < LSC_MAX_TAVERN)
									{
										sld.location.going = "toTavern"; //флаг генерации в таверне
										qtyTavern++;
									}
								}
							}
						}
						else
						{	//рулим в резиденцию
							LAi_SetHuberTypeNoGroup(sld); //садим за стол
							ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");
						}
					}
				}
				//////// если это менты /////////
				if (sld.cityTape == "ment")
				{
					if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours)) 
					{
						DeleteAttribute(sld, "location.going"); //снимаем флаг
						//if (rand(1)) LAi_SetLoginTime(sld, 6.0, 21.99);
						//else LAi_RemoveLoginTime(sld);
						//--> вечером организовываем толпу в таверне
						if (GetTime() > 20.0 && rand(1))
						{
							if (qtyTavern < LSC_MAX_TAVERN)
							{
								sld.location.going = "toTavern"; //флаг генерации в таверне
								qtyTavern++;
							}
							continue;
						}
						//<-- вечером организовываем толпу в таверне
						if (sld.location == "LostShipsCity_town") //если мент на улице
						{
							if (rand(1))
							{
								SaveCurrentNpcQuestDateParam(sld, "location");
								sld.location.hours = rand(5)+1;
								switch (rand(2))
								{
								case 0: //в резиденцию к шефу
									if (qtyResidence < LSC_MAX_RESIDENCE)
									{
										qtyResidence++;
										LAi_SetWarriorTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto"+qtyResidence);
									}
									break;
								case 1: //в таверну
									if (qtyTavern < LSC_MAX_TAVERN)
									{
										sld.location.going = "toTavern"; //флаг генерации в таверне
										qtyTavern++;
									}
									break;
								case 2: //в тюрьму
									if (qtyPrison < LSC_MAX_PRISON)
									{
										qtyPrison++;
										LAi_SetWarriorTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "TartarusPrison", "goto", "goto"+qtyPrison);
									}
									break;									
								}
							}
						}
						else
						{	//возвращемся на варшип
							//проверим занятость локатора								
							if (!LAi_CheckLocatorFree("goto", sld.location.baseLocator))
							{	//выберем незанятый 
								sTemp = sld.location.baseLocator;									
								sTemp = strcut(sTemp, 4, 5);
								for (n=0; n<=9; n++)
								{											
									sLocator = "goto" + sTemp + "_" + n;
									if (LAi_CheckLocatorFree("goto", sLocator))
									{
										LAi_SetLSCoutTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sLocator);
										break;
									}
								}
							}
							else
							{
								LAi_SetLSCoutTypeNoGroup(sld);
								ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
							}
						}
					}
				}
				//////// если внешний горожанин /////////
				if (sld.cityTape == "citizen")
				{
					if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours)) 
					{
						DeleteAttribute(sld, "location.going"); //снимаем флаг
						LAi_SetLoginTime(sld, 6.0, 21.99);
						//--> вечером организовываем толпу в таверне
						if (GetTime() > 19.0 && sld.sex == "man" && rand(1))
						{
							if (qtyTavern < LSC_MAX_TAVERN)
							{
								sld.location.going = "toTavern"; //флаг генерации в таверне
								qtyTavern++;
							}
							continue;
						}
						//<-- вечером организовываем толпу в таверне
						if (sld.location == "LostShipsCity_town") //если горожанин на улице
						{
							if (rand(1))
							{
								SaveCurrentNpcQuestDateParam(sld, "location");
								sld.location.hours = rand(3)+1;
								switch (rand(2))
								{
								case 0: //в церковь
									if (qtyChurch < LSC_MAX_CHURCH)
									{
										sld.location.going = "toChurch"; //флаг генерации в церкви
										qtyChurch++;
									}
									break;
								case 1: //в таверну
									if (qtyTavern < LSC_MAX_TAVERN)
									{
										sld.location.going = "toTavern"; //флаг генерации в таверне
										qtyTavern++;
									}
									break;
								case 2: //в магазин
									if (qtyStore < LSC_MAX_STORE)
									{
										sld.location.going = "toStore"; //флаг генерации в магазине	
										qtyStore++;
									}
									break;									
								}
							}
						}
						else
						{	//возвращемся на свой корабль
							//проверим занятость локатора								
							if (!LAi_CheckLocatorFree("goto", sld.location.baseLocator))
							{	//выберем незанятый 
								sTemp = sld.location.baseLocator;
								isLSCInsideLoc = true;
								if (strlen(sTemp) > 6)
								{
									// если локатор не внутренний
									sTemp = strcut(sTemp, 4, 5);
									isLSCInsideLoc = false;
								}
								for (n=0; n<=9; n++)
								{	
									if (!isLSCInsideLoc)
										sLocator = "goto" + sTemp + "_" + n;
									else
										sLocator = "goto" + n;
									if (LAi_CheckLocatorFree("goto", sLocator))
									{
										LAi_SetLSCoutTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sLocator);
										break;
									}
								}
							}
							else
							{
								LAi_SetLSCoutTypeNoGroup(sld);
								ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
							}
						}
					}
				}
				//////// если домашний горожанин /////////
				if (sld.cityTape == "citizenHome")
				{
					if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours)) 
					{
						DeleteAttribute(sld, "location.going"); //снимаем флаг
						LAi_SetLoginTime(sld, 6.0, 21.99);
						//--> вечером организовываем толпу в таверне
						if (GetTime() > 19.0 && sld.sex == "man" && rand(1))
						{
							if (qtyTavern < LSC_MAX_TAVERN)
							{
								sld.location.going = "toTavern"; //флаг генерации в таверне
								qtyTavern++;
							}
							continue;
						}
						//<-- вечером организовываем толпу в таверне
						if (sld.location == sld.location.baseLocation) //если горожанин у себя дома
						{
							if (rand(1))
							{
								SaveCurrentNpcQuestDateParam(sld, "location");
								sld.location.hours = rand(6)+1;
								switch (rand(3))
								{
								case 0: //в церковь
									if (qtyChurch < LSC_MAX_CHURCH)
									{
										sld.location.going = "toChurch"; //флаг генерации в церкви
										qtyChurch++;
									}
									break;
								case 1: //в таверну
									if (qtyTavern < LSC_MAX_TAVERN)
									{
										sld.location.going = "toTavern"; //флаг генерации в таверне
										qtyTavern++;
									}
									break;
								case 2: //в магазин
									if (qtyStore < LSC_MAX_STORE)
									{
										sld.location.going = "toStore"; //флаг генерации в магазине	
										qtyStore++;
									}
									break;	
								case 3: //на улицы
									//проверим занятость локатора								
									if (!LAi_CheckLocatorFree("goto", sld.location.baseLocator))
									{	//выберем незанятый 
										sTemp = sld.location.baseLocator;
										sTemp = strcut(sTemp, 4, 5);
										for (n=0; n<=9; n++)
										{											
											sLocator = "goto" + sTemp + "_" + n;
											if (LAi_CheckLocatorFree("goto", sLocator))
											{
												LAi_SetLSCoutTypeNoGroup(sld);
												ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sLocator);
												break;
											}
										}
									}
									else
									{
										LAi_SetLSCoutTypeNoGroup(sld);
										ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
									}
									break;	
								}
							}
						}
						else
						{	//возвращемся на свой корабль
							LAi_SetOwnerTypeNoGroup(sld);
							ChangeCharacterAddressGroup(sld, sld.location.baseLocation, "barmen", "stay");
						}
					}
				}
			}
		}
	}
	//------------------- таверна ------------------------
	if (loc.id == "FleuronTavern")
	{
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (CheckAttribute(sld, "location.going") && sld.location.going == "toTavern")
			{
				DeleteAttribute(sld, "location.going");
				LAi_RemoveLoginTime(sld);
				if (sld.sex == "man")
				{
					DeleteAttribute(sld, "nonTable");
					LAi_SetSitTypeNoGroup(sld);
					if (sld.id == "LSCMayor")
						ChangeCharacterAddressGroup(sld, loc.id, "quest", "head_sit");
					else
						PlaceCharacter(sld, "sit", "random_free");
				}
				else
				{
					LAi_SetCitizenTypeNoGroup(sld);
					PlaceCharacter(sld, "goto", "random_free");
				}
			}
		}
	}
	//------------------- церковь ------------------------
	if (loc.id == "GloriaChurch")
	{
		//сам падре
		if (!isDay())
		{
			Index = GetCharacterIndex("LSC_Priest");	
			if (Index != -1)
			{
				sld = &characters[Index];
				LAi_SetSitTypeNoGroup(sld);
				PlaceCharacter(sld, "quest", "priest");
			}
		}
		else
		{
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				makeref(sld, characters[i]);
				//падре днем
				if (sld.id == "LSC_Priest")
				{
					LAi_SetPriestTypeNoGroup(sld);
					ChangeCharacterAddressGroup(sld, sld.location, "barmen",  "stay");
				}
				//граждане
				if (CheckAttribute(sld, "location.going") && sld.location.going == "toChurch")
				{
					DeleteAttribute(sld, "location.going");
					sld.nonTable = true;
					LAi_SetSitTypeNoGroup(sld);
					PlaceCharacter(sld, "sit", "random_free");
				}
			}
		}
	}
	//------------------- магазин ------------------------
	if (loc.id == "EsmeraldaStoreBig")
	{
	    string locArray[10];
        for (i = 0; i < 10; i++)
        {
            locArray[i] = "goto" + (i + 1);
        }
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			makeref(sld, characters[i]);
			if (CheckAttribute(sld, "location.going") && sld.location.going == "toStore")
			{
				DeleteAttribute(sld, "location.going");
                LAi_SetStayTypeNoGroup(sld);
				ChangeCharacterAddress(sld, "EsmeraldaStoreBig", ArrayCutRandomValue(&locArray));
			}
		}
	}
	//------------------- тюрьма ------------------- 
	if (loc.id == "TartarusPrison")
	{
		Index = GetCharacterIndex("LSC_PrisonerHead");
		if (Index != -1)
		{
			sld = &characters[Index];
			if (GetNpcQuestPastDayParam(sld, "location") > sti(sld.location.days))
			{
				SaveCurrentNpcQuestDateParam(sld, "location");
				if (rand(1))	
				{
					LAi_SetHuberTypeNoGroup(sld);
					ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit1");
				}
				else
				{
					LAi_SetWarriorTypeNoGroup(sld);
					PlaceCharacter(sld, "goto", "random_free");
				}
			}
		}
		Index = GetCharacterIndex("LSC_Prisoner1");
		if (Index != -1)
		{
			sld = &characters[Index];
			if (CheckAttribute(sld, "cityTape") && sld.cityTape == "prisoner")
			{
				if (GetNpcQuestPastTimeParam(sld, "location") > sti(sld.location.hours))
				{
					SaveCurrentNpcQuestDateParam(sld, "location");
					if (rand(1))	
					{
						LAi_SetSitTypeNoGroup(sld);
						ChangeCharacterAddressGroup(sld, loc.id, "sit", "sit2");
					}
					else
					{
						LAi_SetWarriorTypeNoGroup(sld);
						PlaceCharacter(sld, "goto", "random_free");
					}
				}
			}
		}
	}
	//------------------- Церес Смити -------------------
	if (loc.id == "CeresSmithy")
	{
		for(i=0; i<MAX_CHARACTERS; i++)
		{
			sld = &characters[i];
			if (CheckAttribute(sld, "location.baseShip.going") && sti(sld.location.baseShip.going) == false)
			{
				if (CheckAttribute(sld, "location") && sld.location == loc.id &&
					CheckAttribute(sld, "location.group") && sld.location.group == "goto")
				{
                	LAi_SetStayTypeNoGroup(sld);
				}
			}
		}
	}
}

void CreatPlantation(aref loc)
{
	if (loc.id != "Bridgetown_Plantation" && loc.id != "Villemstad_Plantation") return;
	if (LAi_IsCapturedLocation) return;
	
	if (GetNpcQuestPastDayWOInit(loc, "Plantation_date") < 2) return;

	int iColony = -1;
	int iNation = -1;

	string sAreal = GetRealmByLocation(loc);	
	string sCity = GetCityNameByRealm(sAreal);
	iColony = FindColony(sCity);
	iNation = GetCityNation(sCity);
	
	SaveCurrentNpcQuestDateParam(loc, "Plantation_date");
	int iCitizensQuantity;
	int iChar, i, iSex, num;
	ref chr;
	aref st;
	string slai_group, sType;
	slai_group = GetNationNameByType(iNation)  + "_citizens";
	
	arrayNPCModelHow = 0;
	num = rand(3) + 7; //количество
	for (i = 0; i < num; i++)
	{
		chr = GetCharacter(NPC_GenerateCharacter("Slave_"+i, "slave_"+(rand(8)+1), "man", "man", 7, iNation, 2, false));
		SetNPCModelUniq(chr, "convict", MAN);
		chr.dialog.filename = "Quest\CapBloodLine\questNPC.c";
		chr.dialog.currentnode = "first time";
		chr.greeting = "Gr_slave";
		chr.CityType = "citizen";
		chr.city = Colonies[iColony].id;
		LAi_SetLoginTime(chr, 6.0, 22.99);

		PlaceCharacter(chr, "goto", "random_free");
		LAi_SetCitizenType(chr);
		LAi_group_MoveCharacter(chr, slai_group);
	}
	// солдаты -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
	{
		if(Pchar.questTemp.CapBloodLine == true) num = 1;
		else num = 3;
		for (i=1; i<=num; i++)
		{
			if(iNation == PIRATE)
			{
				sType = "mush_ctz_" + (rand(2)+7);
			}
			else
			{
				sType = "milit_mush_" + NationShortName(iNation) + "_" + (rand(7)+1);
			}
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_"+i+"_", sType, "man", "mushketer", sti(pchar.rank), iNation, 2, false));
			chr.id = "GenChar_"+i+"_" + chr.index;	
			chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
			chr.CityType = "soldier";
			chr.plantation = "guardian";
			//chr.greeting = "soldier_common";
			chr.MusketerDistance = 0;
			LAi_SetLoginTime(chr, 6.0, 23.0); //а ночью будет беготня от патруля
			LAi_SetGuardianType(chr);
			chr.dialog.filename = "Slavery\Plantation_dialog.c";
			// протекторы
			if (i == 2 || i == 3) 
			{
				chr.protector = true;
				chr.dialog.currentnode = "plantation_protector";
				chr.greeting = "soldier_arest";
			}
			else 
			{
				chr.dialog.currentnode = "plantation_soldier";
				chr.greeting = "Gr_Guard";
			}
			
			if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
			ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", "soldier"+i);
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
			iCitizensQuantity = 10;
		}
		for (i=0; i<iCitizensQuantity-3; i++)
		{
            if(iNation != PIRATE && LAi_IsCapturedLocation == 0)
			{
                sType = "milit_sold";
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
			chr.plantation = "patrol";
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			chr.RebirthPhantom = true;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			LAi_SetLoginTime(chr, 0.0, 24.0);
			LAi_SetPatrolType(chr);

            if (sti(Colonies[iColony].HeroOwn) == true)
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
			if(Pchar.questTemp.CapBloodLine == true)  // Линейка Блада
			{
                chr.dialog.filename = "Quest\CapBloodLine\questNPC.c";
            }
            else
            {
                chr.dialog.filename = "Common_Soldier.c";
            }
			chr.dialog.currentnode = "first time";
			SetLandQuestMarksToFantom(chr, "soldier");
		}
	}
	// патруль <--
	// грузчики -->
	if (CheckAttribute(loc, "carrier") && IsLoginTime())
	{
		int iTemp;
		int iQtyCarrier = rand(2) + 2;
		for (i=iQtyCarrier; i>0; i--)
		{
			chr = GetCharacter(NPC_GenerateCharacter("Carrier", GetUniqCarrierModel("carrier_plantation"), "man", "genres", 35, iNation, 2, false));
			chr.id = chr.id + "_" + chr.index;
			aref aLocator;
			makearef(aLocator, loc.locators.reload);
			LAi_SetImmortal(chr, true);
			LAi_SetLoginTime(chr, 6.0, 23.0);//homo ночью пусть спят
			chr.plantation = "carrier";

			LAi_SetCarrierType(chr);
			if (sti(Colonies[iColony].HeroOwn))
			    LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			else
			    LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	// грузчики <--
	// офицер и солдат в резиденции -->
    if (pchar.questTemp.CapBloodLine == true) return; //У капитана Блада Полковник в начальниках
	//пингующий солдат
    if (CheckNPCQuestDate(loc, "plantation_date"))
    {
        SetNPCQuestDate(loc, "plantation_date");
        if(iNation != PIRATE && LAi_IsCapturedLocation == 0)
        {
            sType = "milit_sold";
            iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
        }
        else
        {
            sType = "pirate";
            iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
        }
        chr = &characters[iChar];
        chr.CityType = "soldier";
        chr.greeting = "soldier_arest";
        chr.protector = true;
        chr.protector.CheckAlways = 1; //проверять всегда
        chr.Dialog.Filename = "Slavery\Plantation_dialog.c";
        SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
        LAi_SetLoginTime(chr, 0.0, 24.0);
        LAi_SetGuardianType(chr);
        chr.watchBoxes = true;
        ChangeCharacterAddressGroup(chr, loc.townsack + "_Plantation_Sp1", "goto", "goto1");

        //владелец плантации
        if(iNation != PIRATE && LAi_IsCapturedLocation == 0)
        {
            sType = "milit_off";
            iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
        }
        else
        {
            sType = "smuggler";
            iChar = NPC_GeneratePhantomCharacter(sType, iNation, MAN, 2);
        }
        chr = &characters[iChar];
        chr.CityType = "soldier";
        chr.greeting = "eng_gov_common";
        chr.Dialog.Filename = "Slavery\Plantation_dialog.c";
        SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
        LAi_SetLoginTime(chr, 7.0, 21.0);
        LAi_SetHuberType(chr);
        chr.watchBoxes = true;
        chr.standUp = true;
        ChangeCharacterAddressGroup(chr, loc.townsack + "_Plantation_Sp2", "sit", "sit1");
    }
	// офицер и солдат в резиденции <--
}

void CreatMinetown(aref loc)
{
    if (loc.id != "FortOrange_Mine") return;
    if (LAi_IsCapturedLocation) return; // fix нефиг грузить, когда город трупов или боевка
	
	if (GetNpcQuestPastDayWOInit(loc, "Plantation_date") < 2) return;
	
	int iColony = -1;
	int iNation = -1;
	
	string sAreal = GetRealmByLocation(loc);
	string sCity = GetCityNameByRealm(sAreal);
	iColony = FindColony(sCity);
	iNation = GetCityNation(sCity);
	
	SaveCurrentNpcQuestDateParam(loc, "Plantation_date");
	int iCitizensQuantity;
	int iChar, i, iSex, num;
	ref chr;
	aref st;
	string slai_group, sType;
	slai_group = GetNationNameByType(iNation)  + "_citizens";

	//количество рабов в рудниках
	if (pchar.questTemp.LSC == "over") num = rand(5) + 5;
	else num = 0;
	arrayNPCModelHow = 0;
	for (i = 0; i < num; i++)
	{
		chr = GetCharacter(NPC_GenerateCharacter("Slave_"+i, "slave_"+(rand(8)+1), "man", "man", 7, iNation, 2, false));
		SetNPCModelUniq(chr, "convict", MAN);
		chr.dialog.filename = "Slavery\Minetown_dialog.c";
		chr.dialog.currentnode = "plantation_slave";
		chr.greeting = "Gr_slave";
		chr.CityType = "citizen";
		chr.city = Colonies[iColony].id;

		ChangeCharacterAddress(chr, "Orange_mines", "goto" + (i + 1));
		LAi_SetCitizenType(chr);
		LAi_group_MoveCharacter(chr, slai_group);
	}

	//количество рабов на поверхности
	if (pchar.questTemp.LSC == "over") num = rand(3) + 1;
	else num = rand(3) + 7;
	arrayNPCModelHow = 0;
	for (i = 0; i < num; i++)
	{
		chr = GetCharacter(NPC_GenerateCharacter("Slave_"+i, "slave_"+(rand(8)+1), "man", "man", 7, iNation, 2, false));
		SetNPCModelUniq(chr, "convict", MAN);
		chr.dialog.filename = "Slavery\Minetown_dialog.c";
		chr.dialog.currentnode = "plantation_slave";
		chr.greeting = "Gr_slave";
		chr.CityType = "citizen";
		chr.city = Colonies[iColony].id;
		LAi_SetLoginTime(chr, 6.0, 22.99);

		PlaceCharacter(chr, "goto", "random_free");
		LAi_SetCitizenType(chr);
		LAi_group_MoveCharacter(chr, slai_group);
	}

	// солдаты -->
	if (checkAttribute(loc, "soldiers") && CheckAttribute(loc, "locators.soldiers"))
	{
		if (pchar.questTemp.LSC == "over") num = 5;
		else num = 3;
 		for (i = 1; i <= num; i++)
		{
			if(iNation == PIRATE)
			{
				sType = "mush_ctz_" + (rand(2)+7);
			}
			else
			{
				sType = "milit_mush_" + NationShortName(iNation) + "_" + (rand(7)+1);
			}
			chr = GetCharacter(NPC_GenerateCharacter("GenChar_"+i+"_", sType, "man", "mushketer", sti(pchar.rank), iNation, 2, false));
			chr.id = "GenChar_"+i+"_" + chr.index;	
			chr.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
			chr.City = Colonies[iColony].id;
			chr.CityType = "soldier";
			chr.plantation = "guardian";
			chr.MusketerDistance = 0;
			LAi_SetLoginTime(chr, 6.0, 23.0); //а ночью будет беготня от патруля
			LAi_SetGuardianType(chr);
			chr.dialog.filename = "Slavery\Minetown_dialog.c";
			// протекторы
			if (i == 2 || i == 3) 
			{
				chr.protector = true;
				chr.dialog.currentnode = "plantation_protector";
				chr.greeting = "soldier_arest";
			}
			else 
			{
				chr.dialog.currentnode = "plantation_soldier";
				chr.greeting = "Gr_Guard";
			}
			
			if (sti(Colonies[iColony].HeroOwn) == true)
			{
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
				chr.greeting = "pirat_guard";
			}
			else
			{
				LAi_group_MoveCharacter(chr, slai_group);
			}
			if (i < 4)
				ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", "soldier" + i);
			else
				ChangeCharacterAddressGroup(chr, "Orange_mines", "quest", "mushketer" + (i - 3));
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
			iCitizensQuantity = 10;
		}
		for (i=0; i<iCitizensQuantity-3; i++)
		{
            if(iNation != PIRATE && LAi_IsCapturedLocation == 0)
			{
                sType = "milit_sold";
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
			chr.plantation = "patrol";
            SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
			chr.RebirthPhantom = true;
			LAi_CharacterReincarnation(chr, true, true);
			LAi_SetReincarnationRankStep(chr, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
			LAi_SetLoginTime(chr, 0.0, 24.0);
			LAi_SetPatrolType(chr);

            if (sti(Colonies[iColony].HeroOwn) == true)
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
			chr.dialog.filename = "Common_Soldier.c";
			chr.dialog.currentnode = "first time";
		}
	}
	// патруль <--
	// грузчики -->
	if (CheckAttribute(loc, "carrier") && IsLoginTime())
	{
		int iTemp;
		int iQtyCarrier = rand(2) + 2;
		for (i=iQtyCarrier; i>0; i--)
		{
			chr = GetCharacter(NPC_GenerateCharacter("Carrier", GetUniqCarrierModel("carrier_mine"), "man", "genres", 35, iNation, 2, false));
			chr.id = chr.id + "_" + chr.index;
			LAi_SetImmortal(chr, true);
			LAi_SetLoginTime(chr, 6.0, 23.0);//homo ночью пусть спят
			chr.plantation = "carrier";

			LAi_SetCarrierType(chr);
			if (sti(Colonies[iColony].HeroOwn))
			    LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
			else
			    LAi_group_MoveCharacter(chr, slai_group);
		}
	}
	// грузчики <--
}

void CreatUnderwater(aref loc)
{
	if (loc.type == "underwater")
	{
		if (CheckAttribute(loc, "type.LSC"))
		{
			LocatorReloadEnterDisable("LostShipsCity_town", "reload73", true);
			pchar.questTemp.LSC.immersions.pay = false; //оплаченное погружение использовано
			pchar.questTemp.LSC.immersions = sti(pchar.questTemp.LSC.immersions);
			if(!LAi_IsImmortal(pchar)) SetShowTimer(400.0); //таймер
			ref sld;
			for (int i=1; i<=22; i++)
			{
				int iTemp = GetCharacterIndex("Crab_"+i);
				if (iTemp == -1)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Crab_"+i, "crabBig", "crab", "crabBig", 40+(MOD_SKILL_ENEMY_RATE), PIRATE, -1, false));
					sld.monster = "1";
					GiveItem2Character(sld, "unarmed");
					EquipCharacterbyItem(sld, "unarmed");
					LAi_SetWarriorType(sld);
					LAi_warrior_SetStay(sld, true);
					LAi_warrior_DialogEnable(sld, false);
					LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
				}
				else
				{
					sld = &Characters[iTemp];
				}
				PlaceCharacter(sld, "goto", "random_free");
			}
		}
		else
		{
			if(!LAi_IsImmortal(pchar)) SetShowTimer(80.0); //таймер
		}
	}
}

void CreatTenochtitlan(aref loc)
{	
	if (loc.id == "Tenochtitlan")
	{
		int i;
		//проверяем наличие тотемов у ГГ, чтобы купленным дать shown
		if (locations[reload_cur_location_index].id == "Tenotchitlan_Jungle_06")
		{	//срабатывает только, если заходим из джунглей
			ref itm;
			string sTemp;
			for (i=1; i<=15; i++)
			{
				if (i == 11) continue;
				sTemp = "Totem_" + i;
				if (CheckCharacterItem(pchar, sTemp))
				{
					itm = ItemsFromID(sTemp);
					//если тотем ещё не использован, то помечаем на укладку в button
					if (!CheckAttribute(itm, "shown.used"))
					{
						itm.shown = 0;
					}
				}
			}
		}
		else
		{
			//близнецов расставим иначе
			int iTemp;
			for (i=1; i<=2; i++)
			{
				iTemp = GetCharacterIndex("AztecCitizen_"+i);
				if (iTemp != -1)
				{
					PlaceCharacter(&characters[iTemp], "goto", "random_free");
				}
			}
		}
	}
}

void CreatTenochtitlanInside(aref loc)
{
	if (loc.type == "teno_inside")
	{
		ref chr;
		int iMassive, warriorQty, warriorRank, i, n;	
		string model[5];
		string sLocator;
		//----------------- генерим войнов в малых храмах богов -----------------
		if (CheckAttribute(loc, "smallGodTemple"))
		{
			chrDisableReloadToLocation = true;
			//определим кол-во войнов в храме
			warriorQty = sti(MOD_SKILL_ENEMY_RATE /2);
			if (warriorQty < 3) warriorQty = 3;
			//определим ранг войнов. обработаем от сложности, но не менее 15 уровня
			warriorRank = GetCoffDiff(sti(pchar.rank), 1000) + MOD_SKILL_ENEMY_RATE;
			if (warriorRank < 15) warriorRank = 15;
			//инкремент на кол-во посещений
			loc.smallGodTemple = sti(loc.smallGodTemple) + 1;
			warriorRank = warriorRank + sti(loc.smallGodTemple) * 4;
			//генерим ацтеков с неповторяемыми модельками
		    model[0] = "AztecWarrior1";
			model[1] = "AztecWarrior2";
			model[2] = "AztecWarrior3";
			model[3] = "AztecWarrior4";
			model[4] = "AztecWarrior5";
			i = 0;
			while(i < warriorQty)
			{
				iMassive = rand(4);
				if (model[iMassive] != "")
				{
					chr = GetCharacter(NPC_GenerateCharacter("AztecWarrior"+loc.index+"_"+i, model[iMassive], "skeleton", "man", warriorRank, PIRATE, 0, true));
					chr.undead = "1";
					SetFantomParamFromRank(chr, warriorRank, true);
					while (FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE) != "")
					{
						TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
					}
					while (FindCharacterItemByGroup(chr, GUN_ITEM_TYPE) != "")
					{             
						TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
					}
					GiveItem2Character(chr, "maquahuitl");
					EquipCharacterbyItem(chr, "maquahuitl");
					SetCharacterPerk(chr, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, дается ГГ и боссам уровней
					if (sti(loc.smallGodTemple) > 3 && MOD_SKILL_ENEMY_RATE > 1)
					{
						SetCharacterPerk(chr, "SwordplayProfessional");
						SetCharacterPerk(chr, "AdvancedDefense");
						SetCharacterPerk(chr, "CriticalHit");
						SetCharacterPerk(chr, "Sliding");
						TakeNItems(chr,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
					}
					PlaceCharacter(chr, "goto", "random_free");
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, "teno_monsters_group");
					i++;
					model[iMassive] = "";
				}
			}
			LAi_group_SetRelation("teno_monsters_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("teno_monsters_group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("teno_monsters_group", "OpenTheDoors");
		}
		//----------------- генерим войнов в большом храме -----------------
		if (CheckAttribute(loc, "greatTemple") && locations[reload_cur_location_index].id == "Tenochtitlan")
		{
			LAi_group_Delete("teno_monsters_group");
			//определим кол-во войнов в храме
			warriorQty = 4;
			if (MOD_SKILL_ENEMY_RATE > 6) warriorQty = 5;
			if (MOD_SKILL_ENEMY_RATE <= 1) warriorQty = 3;
			//определим ранг войнов. обработаем от сложности, но не менее 20 уровня
			warriorRank = GetCoffDiff(sti(pchar.rank), 1000) + MOD_SKILL_ENEMY_RATE;
			if (warriorRank < 20) warriorRank = 20;
			//генерим ацтеков с неповторяемыми модельками
			for (n=1; n<=7; n++)
			{
				model[0] = "AztecWarrior1";
				model[1] = "AztecWarrior2";
				model[2] = "AztecWarrior3";
				model[3] = "AztecWarrior4";
				model[4] = "AztecWarrior5";	
				i = 0;
				while(i < warriorQty)
				{
					iMassive = rand(4);
					if (model[iMassive] != "")
					{
						chr = GetCharacter(NPC_GenerateCharacter("AztecWarrior"+loc.index+"_"+n+""+i, model[iMassive], "skeleton", "man", warriorRank, PIRATE, 0, true));
						chr.undead = "1";
						SetFantomParamFromRank(chr, 15, true);
						while (FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE) != "")
						{
							TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
						}
						while (FindCharacterItemByGroup(chr, GUN_ITEM_TYPE) != "")
						{             
							TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
						}
						GiveItem2Character(chr, "maquahuitl");
						EquipCharacterbyItem(chr, "maquahuitl");
						SetCharacterPerk(chr, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, дается ГГ и боссам уровней
						if (MOD_SKILL_ENEMY_RATE > 5)
						{
							SetCharacterPerk(chr, "SwordplayProfessional");
							SetCharacterPerk(chr, "AdvancedDefense");
							SetCharacterPerk(chr, "CriticalHit");
							SetCharacterPerk(chr, "Sliding");
							TakeNItems(chr,"potion2", rand(3)+1);
						}
						sLocator = "monster"+n;
						ChangeCharacterAddressGroup(chr, loc.id, "monsters", sLocator+(i+1));
						LAi_SetWarriorType(chr);
						LAi_warrior_SetStay(chr, true);
						LAi_warrior_DialogEnable(chr, false);
						LAi_group_MoveCharacter(chr, "teno_monsters_group");
						i++;
						model[iMassive] = "";
					}
				}
			}
			LAi_group_SetRelation("teno_monsters_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		}
	}
}

void CreatDesMoines(aref loc)
{
	ref chr;
	bool bImmortal;
	int i, iMassive;
	string sSex, sNode, sModel;
	string model[10];
	if (pchar.questTemp.MC != "Incquisitio")
	{
		if (loc.id == "DesMoines_town")
		{
			if (GetHour() > 6.0 && GetHour() < 21.99)
			{
				model[0] = "citiz_46";
				model[1] = "citiz_41";
				model[2] = "citiz_45";
				model[3] = "citiz_7";
				model[4] = "citiz_47";
				model[5] = "shipowner_2";
				model[6] = "shipowner_13";
				model[7] = "milit_spa_5";
				model[8] = "trader_4";
				model[9] = "barmen_6";
				sSex = "man";
				sNode = "DMCitiz";
				sModel = "citiz_15";
				bImmortal = false;
			}
			else
			{
				if (pchar.questTemp.MC == "over")
				{
					model[0] = "citiz_46";
					model[1] = "citiz_41";
					model[2] = "citiz_45";
					model[3] = "citiz_7";
					model[4] = "citiz_47";
					model[5] = "shipowner_2";
					model[6] = "shipowner_13";
					model[7] = "milit_spa_5";
					model[8] = "trader_4";
					model[9] = "barmen_6";
					sSex = "man";
					sNode = "DMCitiz";
					sModel = "citiz_15";
					bImmortal = false;
				}
				else
				{
					model[0] = "skel1";
					model[1] = "skel2";
					model[2] = "skel3";
					model[3] = "skel4";
					model[4] = "skel1";
					model[5] = "skel2";
					model[6] = "skel3";
					model[7] = "skel4";
					model[8] = "skel1";
					model[9] = "skel2";
					sSex = "skeleton";
					sNode = "DMSkel";
					sModel = "SkeletD";
					bImmortal = true;
				}
			}
			i = 0;
			while(i < 8)
			{
				iMassive = rand(9);
				if (model[iMassive] != "")
				{
					chr = GetCharacter(NPC_GenerateCharacter("MCCitiz_"+i, model[iMassive], sSex, "man", 15, SPAIN, 0, true));
					if (sSex == "skeleton")
						chr.skeleton = "1";
					else
						DeleteAttribute(chr, "skeleton");
					chr.dialog.filename = "Quest\MagicCity.c";
					chr.dialog.currentnode = sNode;
					chr.greeting = "cit_common";
					chr.city = "DesMoines";
					LAi_RemoveLoginTime(chr);
					LAi_SetImmortal(chr, bImmortal);
					PlaceCharacter(chr, "goto", "random_free");
					LAi_SetCitizenType(chr);
					LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
					i++;
					model[iMassive] = "";
				}
			}
		}
		if (loc.id == "DesMoines_Townhall")
		{
			if (GetHour() > 6.0 && GetHour() < 21.99 )
			{	
				sSex = "man";
				sNode = "DMCitiz";
				sModel = "citiz_15";
				bImmortal = false;
			}
			else
			{
				if (pchar.questTemp.MC == "over")
				{
					sSex = "man";
					sNode = "DMCitiz";
					sModel = "citiz_15";
					bImmortal = false;
				}
				else
				{
					sSex = "skeleton";
					sNode = "DMSkel";
					sModel = "SkeletD";
					bImmortal = true;
				}
			}
			//глава поселения
			chr = GetCharacter(NPC_GenerateCharacter("DesMoinesHead", sModel, sSex, "man", 25, SPAIN, 0, true));
			if (sSex == "skeleton")
				chr.skeleton = "1";
			else
				DeleteAttribute(chr, "skeleton");
			chr.name = FindPersonalName("DesMoinesHead_name");
			chr.lastname = FindPersonalName("DesMoinesHead_lastname");
			chr.dialog.filename = "Quest\MagicCity.c";
			chr.dialog.currentnode = sNode + "Head";
			chr.greeting = "pirat_common";
			chr.city = "DesMoines";
			chr.watchBoxes = true;
			chr.watchBoxes.exitDisable = true;
			LAi_RemoveLoginTime(chr);
			LAi_SetImmortal(chr, bImmortal);
			ChangeCharacterAddressGroup(chr, "DesMoines_Townhall", "goto", "goto1");
			LAi_SetWarriorType(chr);
			LAi_group_MoveCharacter(chr, "SPAIN_CITIZENS");
			SetLandQuestMarksToFantom(chr, "DesMoinesHead"); // фантом будет с квест-метками
		}
	}
}

// устанавливаем охранников в LSC
void CreateLSCGuardClan()
{
    ref sld;
    string LocatorGroup, LocatorName;
    int i;
    int iRank = MOD_SKILL_ENEMY_RATE*2+10;
    int iScl = 30 + 2*iRank;

    int imush = 10; // общее число мушкетеров
    int isold = 5; // общее число солдат
    int iprot = 10; // общее число протекторов
    LocatorGroup = "soldiers";
    // ставим мушкетеров
    for (i = 1; i <= imush; i++)
    {
        LocatorName = "mushketer"+i;
        if (i <= 4) // касперы 4 шт молодняк
        {
            sld = GetCharacter(NPC_GenerateCharacter("CasperMush_"+i, "Casper_mush_"+(rand(7)+1), "man", "mushketer", iRank, PIRATE, 1, false));
            FantomMakeCoolFighter(sld, iRank, iScl, iScl, "unarmed", "mushket", iScl+100);
            sld.dialog.Filename = "Quest\LostShipsCity\Guardian.c";
            sld.dialog.currentnode = "Casper_soldier";
            sld.greeting = "pirat_common";
            ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
            LAi_SetLoginTime(sld, 0.0, 24.0);
            LAi_SetGuardianType(sld);
            sld.MusketerDistance = 0;
            LAi_group_MoveCharacter(sld, "LSC_CASPER");
        }
        if (i >= 5 && i <= 6) // нарвалы 2 шт прислужники
        {
            sld = GetCharacter(NPC_GenerateCharacter("NarvalMush_"+i, "Narval_mush_"+(rand(5)+1), "man", "mushketer", iRank, PIRATE, 1, false));
            FantomMakeCoolFighter(sld, iRank, iScl, iScl, "unarmed", "mushket", iScl+100);
            sld.dialog.Filename = "Quest\LostShipsCity\Guardian.c";
            sld.dialog.currentnode = "Narval_soldier";
            sld.greeting = "pirat_common";
            ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
            LAi_SetLoginTime(sld, 0.0, 24.0);
            LAi_SetGuardianType(sld);
            sld.MusketerDistance = 0;
            LAi_group_MoveCharacter(sld, "LSC_NARVAL");
        }
        if (i >= 7) // ментозавры 2 шт
        {
            sld = GetCharacter(NPC_GenerateCharacter("MentMush_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", iRank, PIRATE, 1, false));
            FantomMakeCoolFighter(sld, iRank, iScl, iScl, "unarmed", "mushket", iScl+100);
            sld.dialog.Filename = "Quest\LostShipsCity\Guardian.c";
            sld.dialog.currentnode = "Ment_soldier";
            sld.greeting = "pirat_common";
            ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
            LAi_SetLoginTime(sld, 0.0, 24.0);
            LAi_SetGuardianType(sld);
            sld.MusketerDistance = 0;
            LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
        }
        DeleteAttribute(sld, "LifeDay");
    }
    // ставим солдат
    arrayNPCModelHow = 0;
    for (i = 1; i <= isold; i++)
    {
        LocatorName = "soldier"+i;
        if (i <= 2) // касперы шестёрки молодняк
        {
            sld = GetCharacter(NPC_GenerateCharacter("CasperSold_"+i, "Casper_"+(rand(7)+1), "man", "man", iRank, PIRATE, 1, false));
            FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade19","blade24","blade20"), RandPhraseSimple("pistol6","pistol4"), iScl+100);
            //SetNPCModelUniq(sld, "casper", MAN); //TODO добавить группу в string GetModelType(string model)
            sld.dialog.Filename = "Quest\LostShipsCity\Guardian.c";
            sld.dialog.currentnode = "Casper_soldier";
            sld.greeting = "pirat_common";
            ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
            LAi_SetLoginTime(sld, 0.0, 24.0);
            LAi_SetGuardianType(sld);
            LAi_group_MoveCharacter(sld, "LSC_CASPER");
        }
        if (i >= 3 && i <= 5) // нарвалы младшие члены - прислужники
        {
            sld = GetCharacter(NPC_GenerateCharacter("NarvalSold_"+i, "narval_"+(rand(5)+1), "man", "man", iRank, PIRATE, 1, false));
            FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade14","blade7","blade33"), RandPhraseSimple("pistol6","pistol5"), iScl+100);
            //SetNPCModelUniq(sld, "narval", MAN); //TODO добавить группу в string GetModelType(string model)
            sld.dialog.Filename = "Quest\LostShipsCity\Guardian.c";
            sld.dialog.currentnode = "Narval_soldier";
            sld.greeting = "pirat_common";
            ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
            LAi_SetLoginTime(sld, 0.0, 24.0);
            LAi_SetGuardianType(sld);
            LAi_group_MoveCharacter(sld, "LSC_NARVAL");
        }
        DeleteAttribute(sld, "LifeDay");
    }
    // ставим протекторов
    for (i=1; i<=iprot; i++)
    {
        if (i > 8) LocatorName = "protector"+(i+1);
        else LocatorName = "protector"+i;
        if (i <= 4) // касперы
        {
            sld = GetCharacter(NPC_GenerateCharacter("CasperProt_"+i, "Casper_"+(rand(7)+1), "man", "man", iRank, PIRATE, 1, false));
            FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade19","blade24","blade20"), "pistol4", iScl+100);
            //SetNPCModelUniq(sld, "casper", MAN); //TODO добавить группу в string GetModelType(string model)
            sld.protector = true;
            sld.dontTalkOnDuty = true; //не общаться с гражданскими на посту
            sld.dialog.Filename = "Quest\LostShipsCity\Guardian.c";
            if (i == 1 || i == 4)
            {
                sld.dialog.currentnode = "Casper_warning";
                sld.protector.CheckAlways = true; //проверять всегда
            }
            else if (i == 2 || i == 3) sld.dialog.currentnode = "Casper_parol";
            sld.greeting = "pirat_common";
            ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
            LAi_SetLoginTime(sld, 0.0, 24.0);
            LAi_SetGuardianType(sld);
            LAi_group_MoveCharacter(sld, "LSC_CASPER");
        }
        if (i >= 5 && i <= 6) // нарвалы
        {
            sld = GetCharacter(NPC_GenerateCharacter("NarvalProt_"+i, "narval_"+(rand(5)+1), "man", "man", iRank, PIRATE, 1, false));
            FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade14","blade7","blade33"), "pistol4", iScl+100);
            //SetNPCModelUniq(sld, "narval", MAN); //TODO добавить группу в string GetModelType(string model)
            sld.dialog.Filename = "Quest\LostShipsCity\Guardian.c";
            if (i == 5) sld.dialog.currentnode = "Narval_warning";
            if (i == 6) sld.dialog.currentnode = "Narval_parol";
            sld.greeting = "pirat_common";
            ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
            LAi_SetLoginTime(sld, 0.0, 24.0);
            LAi_SetGuardianType(sld);
            sld.protector = true;
            sld.dontTalkOnDuty = true; //не общаться с гражданскими на посту
            if (i == 5 ) sld.protector.CheckAlways = true; //проверять всегда
            LAi_group_MoveCharacter(sld, "LSC_NARVAL");
        }
        if (i >= 7) // менты защитники
        {
            sld = GetCharacter(NPC_GenerateCharacter("MentProt_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, false));
            FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade14","blade24","blade33"), "pistol4", iScl+100);
            //SetNPCModelUniq(sld, "mercenary", MAN); //TODO добавить группу в string GetModelType(string model)
            sld.dialog.Filename = "Quest\LostShipsCity\Guardian.c";
            sld.dialog.currentnode = "Ment_soldier";
            sld.greeting = "pirat_common";
            ChangeCharacterAddressGroup(sld, "LostShipsCity_town", LocatorGroup, LocatorName);
            LAi_SetLoginTime(sld, 0.0, 24.0);
            LAi_SetGuardianType(sld);
            LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
        }
        DeleteAttribute(sld, "LifeDay");
    }
    // протекторы менты-менты внутри Варшипа
    for (i=1; i<=3; i++)
    {
        LocatorName = "protector"+i;
        sld = GetCharacter(NPC_GenerateCharacter("MentProt_"+i, "citiz_"+(rand(9)+51), "man", "man", iRank, PIRATE, 1, false));
        FantomMakeCoolFighter(sld, iRank, iScl, iScl, LinkRandPhrase("blade14","blade24","blade33"), "pistol4", iScl+100);
        SetNPCModelUniq(sld, "mercenary", MAN);
        sld.dialog.Filename = "Quest\LostShipsCity\Mentos.c";
        sld.dialog.currentnode = "First Time";
        sld.greeting = "pirat_common";
        sld.stay_man = true; //что бы не ходили
        sld.talker = true; //начать диалог
        sld.watchBoxes = true;
        ChangeCharacterAddressGroup(sld, "SanAugustineResidence", LocatorGroup, LocatorName);
        LAi_SetLoginTime(sld, 0.0, 24.0);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
        DeleteAttribute(sld, "LifeDay");
    }
}
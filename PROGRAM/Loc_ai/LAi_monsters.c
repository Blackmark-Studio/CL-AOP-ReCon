//Создать фантома основываясь на характеристиках данного персонажа в самом дальнем углу
void LAi_GenerateFantomFromMe(aref chr)
{
	//Проверяем возможность генерации фантома в данной локации
	if(!TestRef(loadedLocation)) return;
	if(!IsEntity(loadedLocation)) return;
	if(!LAi_LocationIsFantomsGen(loadedLocation)) return;
	//Проверяем возможность перерождения персонажа
	if(!LAi_CharacterIsReincarnation(chr)) return;
	//Проверяем какую модельку использовать для перерождения
	bool isGen = LAi_CharacterReincarnationMode(chr);
	if(!CheckAttribute(chr, "model")) isGen = true;
	if(!CheckAttribute(chr, "model.animation")) isGen = true;
	if(chr.model == "") isGen = true;
	if(chr.model.animation == "") isGen = true;
	string model, ani;
	if(isGen) //Пока что не используется
	{
		int nat = GetLocationNation(loadedLocation);
		if(nat < 0) nat = PIRATE;
		if(nat >= MAX_NATIONS) nat = PIRATE;
		if(!CheckAttribute(&Nations[nat], "fantomModel"))
		{
			Trace("Nation (Nations[" + nat + "]) by name " + Nations[nat].name + " not include fantoms");
			return;
		}
		aref fantoms;
		makearef(fantoms, Nations[nat].fantomModel);
		int num = GetAttributesNum(fantoms);
		if(num <= 0)
		{
			Trace("Nation (Nations[" + nat + "]) by name " + Nations[nat].name + " not include have fantoms");
			return;
		}
		num = rand(num - 1);
		string m = GetAttributeName(GetAttributeN(fantoms, num));
		model = fantoms.(m);
		ani = "man";
		m = m + ".ani";
		if(CheckAttribute(fantoms, m))
		{
			ani = fantoms.(m);
		}
	}
	else
	{
		model = chr.model;
		ani = chr.model.animation;
	}
	//Сохраняем параметры персонажа
	object tmp;
	CopyAttributes(&tmp, chr);
	//Создаём фантома	
	if(ani == "mushketer")
	{
		ref sld = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", chr.rank, sti(chr.nation), sti(chr.lifeDay), false));
		sld.id = "GenChar_" + sld.index;
		sld.reputation = chr.reputation;
		sld.City = chr.City;
		sld.CityType = chr.CityType;
		sld.RebirthPhantom = true;
		sld.dialog.filename = "Common_Soldier.c";
		sld.dialog.currentnode = "first time";
		sld.greeting = chr.greeting;
		LAi_CharacterReincarnation(sld, true, true);
		LAi_SetReincarnationRankStep(sld, MOD_SKILL_ENEMY_RATE+2); //задаем шаг на увеличение ранга фантомам на реинкарнацию
		if (CheckAttribute(chr, "chr_ai.reincarnation.step"))
		{
			SetFantomParamFromRank(sld, sti(chr.rank) + sti(chr.chr_ai.reincarnation.step), true); // бравые орлы
		}
		LAi_SetLoginTime(sld, 6.0, 23.0); //а ночью будет беготня от патруля		
		sld.dialog.filename = chr.dialog.filename;
		sld.dialog.currentnode = chr.dialog.currentnode;
		SetRandomNameToCharacter(sld);
		LAi_SetPatrolType(sld);
		LAi_group_MoveCharacter(sld, chr.chr_ai.group);
		PlaceCharacter(sld, "patrol", "random_free");
	}
	else
	{
		ref fnt = LAi_CreateFantomCharacterEx(model, ani, LAi_CharacterReincarnationGroup(chr), "");
		string curidx = fnt.index;
		//Устанавливаем параметры предыдущего персонажа
		CopyAttributes(fnt, &tmp);
		// boal оружие дать! 19.01.2004 -->
		// фантомы точные клоны SetFantomParam(fnt);  
		//--> eddy. шаг на увеличение ранга фантома.
		if (CheckAttribute(chr, "chr_ai.reincarnation.step"))
		{
			SetFantomParamFromRank(fnt, sti(chr.rank) + sti(chr.chr_ai.reincarnation.step), true); // бравые орлы
			characters[sti(fnt.baseIndex)].rank = fnt.rank; //в структуру прародителя ранг с наворотом
		}
		else //не даем падать рангу от SetFantomParam
		{
			LAi_NPC_Equip(fnt, sti(fnt.rank), true, true);
			LAi_SetCurHPMax(fnt);
		}
		// boal 19.01.2004 <--
		if(CheckAttribute(fnt, "chr_ai.group"))
		{
			LAi_group_MoveCharacter(fnt, fnt.chr_ai.group);
		}
		else LAi_group_MoveCharacter(fnt, "");
		//Сохраняем модельку и анимацию
		fnt.model = model;
		fnt.model.animation = ani;
		//Инициализируем тип
		if(!CheckAttribute(fnt, "chr_ai.type")) fnt.chr_ai.type = "";
		string chrtype = fnt.chr_ai.type;
		SetRandomNameToCharacter(fnt);
		fnt.id = tmp.id;
		fnt.index = curidx;
		LAi_tmpl_stay_InitTemplate(fnt);
		fnt.chr_ai.type = "";
		if(chrtype != "")
		{
			chrtype = "LAi_type_" + chrtype + "_Init";
			call chrtype(fnt);
		}
		SetNewModelToChar(fnt);
	}
}

void LAi_CreateSecretChest(ref location) //HardCoffee определение и заполнение тайников с хабаром при заходе на локацию
{
	string locationName = location.id;
	aref secretBox;
	if (findlocator(locationName, "secret0", &secretBox, true)) FillSecretBox(location, "secret0");// это тайник викторинщика
	for (int i = 1; i <= MAX_SECRET_CHESTS; i++)
	{
	    if (!(findlocator(locationName, "secret"+i, &secretBox, true))) return; // если sectet1 нет, то курим
	    // заполняем тайник в ChestLogic.c, вешаем на него аттрибут .difficult
        // еcли .difficult на первом тайнике уже висит понимаем, что всё заполнено в прошлый раз
        if (FillSecretBox(location, "secret"+i)) return;
    }
}

// Jason выброшенные на берег сундуки - 5%
bool LAi_CreateShoreChest(ref location)
{
	string sTemp = location.id;
	DeleteAttributeEx(location, "box1.NotChest,box2.NotChest");

	if (CheckAttribute(location, "Chestgennot")) return false;

	if (CheckAttribute(location, "type") && location.type == "seashore" && CheckAttributeMass(location, "locators.box", "box1,box2", "&"))
	{
		location.box1.NotChest = true;
		location.box2.NotChest = true;

		if (!CheckAttribute(location, "shorechest") && idRand(location.id + "_box", 99) < makeint(5 + GetFortuneBonus(2))) // KZ > гадание цыганки за 5к повышает шанс на 40%
		{
			string sModel = "chest_" + (idRand(location.id + "sModel", 2) + 1);

			if (!FindFile("RESOURCE/MODELS/" + location.filespath.models, sModel + ".gm", "*.gm", true))
			{
				trace("LAi_CreateShoreChest > Can't find geometry file " + sModel + " in RESOURCE\MODELS\" + location.filespath.models);
				return false;
			}

			location.num = idRand(location.id + "num", 1) + 1;
			location.numbox = "box"+(sti(location.num));
			location.shorechest = true;
			location.models.always.chest = sModel;
			location.models.always.chest.locator.group = "box";
			location.models.always.chest.locator.name = location.numbox;
			location.models.always.chest.tech = "DLightModel";
			return true;
		}

		if (CheckAttribute(location, "shorechest")) // есть сундук
		{
			DeleteAttribute(location, "box" + location.num + ".NotChest");
			if (CheckAttribute(location, "chest_date") && GetNpcQuestPastDayParam(location, "chest_date") > 2) // > TODO > pchar.location != location.id
			{
				DeleteAttributeEx(location, "shorechest,shorefill,chest_date,models.always.chest,numbox,num");
			}
			else
			{
				if (!CheckAttribute(location, "shorefill"))
				{
					FillShorechestBox(sTemp, sti(location.num), idRand(location.id + "shorechest", 5));
					SaveCurrentNpcQuestDateParam(location, "chest_date");
					location.shorefill = true;

					if (IsDay())
						Playsound("bird_chest_day");
					else
						Playsound("bird_chest_night");
				}
			}
		}
	}

	return true;
}

bool LAi_CreateEncounters(ref location)
{
	aref grp, st, at;
	ref chr, rCharacter;
	string encGroup, str, locator, sAreal, sCity;
	int num, i, iChar, iNation, iRank, n, iTemp, iRnd, iRand, iEncrnd; //TODO: рефактор
	
	if (!bLandEncountersGen) //если прерывание на локацию, энкаунтеров не генерим
	{		
		bLandEncountersGen = true;
		return false;
	}
	
	//Можем ли генерить
	if(CheckAttribute(location, "DisableEncounters")) return false;
	if(GetArealByLocation(location) == "Guadeloupe" && CheckAttribute(pchar,"questTemp.Ascold.tmp_disable")) return false; //fix отдельно для Гваделупы
	if(!CheckAttribute(location, "locators.encdetector") || !CheckNPCQuestDate(location, "Enc_date") || bDisableLandEncounters) return false;
	if (LAi_IsCapturedLocation) return false; // fix - не генерить в захваченные ExitTown
	//if(CheckAttribute(location, "fastreload")) return false; //Отсекаем локации ExitTown у сухопутных городов
	
    // Пауза случаек на один раз (boal)
	if (CheckAttribute(pchar, "GenQuest.Enc2Pause"))
	{
	    DeleteAttribute(pchar, "GenQuest.Enc2Pause");
	    return false;
	}
	
	// Если бухта с контрой, то не ставим никого
	if (location.type == "seashore") 
	{
		makearef(st, location.models.always);
		num = GetAttributesNum(st);
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(st, i);	
			str = GetAttributeName(at);
			if(st.(str) == "smg")
			{
				return false;
			}
		}
	}
	
	SetNPCQuestDate(location, "Enc_date");
	
	sAreal = GetRealmByLocation(location);
	if (sAreal == "none") return false;
	if(!CheckAttribute(location, "onUninhabitedIsland"))
	{
		sCity = GetCityNameByRealm(sAreal);
		if (sCity == "none") return false;
		iNation = GetCityNation(sCity);
		if (iNation == -1) return false;
	}
	
	// Warship 10.08.09 Если прерывание на локацию - не генерим энкаунтеров, иначе погло накладываться, судя по всму
	// bLandEncountersGen устанавливался вручную и не гарантиварол избежание пересечений квест-энкаункеры
	if(!isLocationFreeForQuests(location.Id)) return false;
	
	// Группа, куда будем помещать фантомов
	encGroup = LAi_FindRandomLocator("encdetector");
	str = "locators." + encGroup;
	makearef(grp, location.(str));
	
	if(CheckAttribute(location, "onUninhabitedIsland") || CheckAttribute(location, "deadlocked")) 
	{
		iRand = rand(1) + 7;
	}
	else
	{
		//Это временное решение, при переделке энкаунтеров свич вообще будет идти по string аргументу
		if(iNation == PIRATE || sCity == "FortOrange") iRand = rand(3);
		else iRand = rand(6);
	}
	switch (iRand)
	{
		// Разбойники
		case 0:
			if(rand(10) > 6) return false;
			if(location.type == "seashore" || location.type == "mayak") return false;
			num = GetAttributesNum(grp) - rand(2); //кол-во человек в банде
			if(num <= 0) num = 1; //если локаторов меньше четырёх
			str = "Gang"+ location.index + "_";
			
			// Генерим ранг 
			if (sti(pchar.rank) > 6) 
			{
				if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
				else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
			}
			else iRank = sti(pchar.rank);
			
			//Начинаем перебирать локаторы и логинить фантомов
			LAi_grp_alarmactive = false;
			LAi_group_ClearAllTargets();
			
			i = 0;
			iEncrnd = rand(3);
			if (!CheckAttribute(location, "locators.goto.fire")) iEncrnd = 1; // фикс костров
			arrayNPCModelHow = 0;
			while(i < num)
			{
				chr = GetCharacter(NPC_GenerateCharacter(str + i, "pirate_"+(rand(15)+1), "man", "man", iRank, iNation, 1, true));
				SetNPCModelUniq(chr, "pirate", MAN);
				SetFantomParamFromRank(chr, iRank, true);
				//Получим локатор для логина
				if (!iEncrnd)
				{
					location.bonfire = true;
					encGroup = "enc01";
					locator = "ass"+(i+1);
					ChangeCharacterAddressGroup(chr, location.id, "goto", locator);
					LAi_SetGroundSitTypeNoGroup(chr);
				}
				else
				{
					locator = GetAttributeName(GetAttributeN(grp, i));
					ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
					LAi_SetStayType(chr);
				}
				chr.dialog.filename = "Encounters\Raiders.c";
				chr.greeting = "Enc_Raiders";
				chr.EncQty = num;
				LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_RaidersBeforeDialog");
				LAi_group_MoveCharacter(chr, "RaidersGroup_" + location.index);
				if (i == 0) 			
				{
					sAreal = "Raiders_" + location.index;
					pchar.GenQuest.(sAreal).name = GetFullName(chr); //имя бандита, будет главарем
					pchar.GenQuest.(sAreal).nation = iNation; //нация для слухов 
				}
				i++;
			}
			str = "EncRaiders_" + location.index;
			pchar.quest.(str).win_condition.l1        = "locator";
			pchar.quest.(str).win_condition.l1.location = location.id;
			pchar.quest.(str).win_condition.l1.locator_group = "encdetector";
			pchar.quest.(str).win_condition.l1.locator = encGroup;
			pchar.quest.(str).win_condition = "LandEnc_RaidersBegin";
			pchar.quest.(str).EncQty = num; //кол-во бандитов
			pchar.quest.(str).LocIdx = location.index;
			str = "TimeRaiders_" + location.index;
			pchar.quest.(str).win_condition.l1            = "Timer";
			pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.(str).win_condition               = "LandEnc_RaidersOver";
			pchar.quest.(str).EncQty = num; //кол-во бандитов
			pchar.quest.(str).LocIdx = location.index;
		break;
		
		// Праздношатающиеся перцы
		case 1:
			LAi_group_Delete("LandEncGroup");
			if (isDay())
			{	//70% днём, что появится
			    if (rand(9) > 6) return false;
			}
			else
			{	//40% ночью
			    if (rand(9) > 3) return false;
			}
			locator = GetAttributeName(GetAttributeN(grp, 0));
			//Начинаем перебирать локаторы и логинить фантомов
			if (rand(5) > 3 && location.id.label == "ExitTown")
			{
				chr = GetCharacter(NPC_GenerateCharacter("WalkerGirl", "women_"+(rand(11)+1), "woman", "towngirl", 5, iNation, 0, false));
				chr.greeting = "Gr_Woman_Citizen";
				pchar.GenQuest.EncWalker = "woman"; //слухи
			}
			else
			{
				chr = GetCharacter(NPC_GenerateCharacter("Walker", RandCitizenModel(), "man", "man", sti(pchar.rank), iNation, 0, true));
				SetFantomParamFromRank(chr, sti(pchar.rank), true);
				chr.greeting = "cit_common";
				chr.diag = rand(17);
				if(chr.diag == "2") //Учитель
				{
					RandTeacher(chr);
					chr.talker = 4;
				}
				if(chr.diag == "17")//Офицер
				{
					chr.greeting = "Gr_Officer"; //"VOICE\Russian\officer03.wav"
					if (sti(chr.reputation) > 41)
					{
						chr.alignment = "good";
						SetCharacterPerk(chr, "Honest");
					}
					else
					{
						chr.alignment = "bad";
						SetCharacterPerk(chr, "Rebel");
					}
					chr.talker = 6;
					chr.id = "GenOff_" + chr.index;
					chr.OfficerWantToGo.DontGo = true; //не пытаться уйти
					chr.loyality = MAX_LOYALITY;
					SetCharacterPerk(chr, "LoyalOff");
					//SetCharacterPerk(chr, "EncWalker"); можно потом придумать
					if (!CheckAttribute(chr, "faceId") || sti(chr.faceId) != 107) // TODO Врем. фикс пока не будут портреты для COMMONERS
					{
						chr.model =  "citiz_11"; // если нет портрета, ставим дефолтную модель
						FaceMaker(chr);
					}
				}
				pchar.GenQuest.EncWalker = "man"; //слухи
			}
			chr.dialog.filename = "Encounters\Walker.c";
			chr.dialog.currentnode = "First time";
			LAi_SetCitizenType(chr);
			LAi_group_MoveCharacter(chr, "LandEncGroup");
			//--> слухи
			pchar.GenQuest.EncWalker.City = sCity;
			pchar.GenQuest.EncWalker.Name = GetFullName(chr);
			LAi_group_SetCheck("LandEncGroup", "EncWalker_Rumours"); //TODO: отдельная группа по индексу
			PChar.quest.EncWalker_Over.win_condition.l1	= "ExitFromLocation";
			PChar.quest.EncWalker_Over.win_condition.l1.location = PChar.location;
			PChar.quest.EncWalker_Over.win_condition	= "EncWalker_Over";
			//<-- слухи
			SetLandQuestMarksToFantom(chr, "Citizen");
			ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
		break;
		
		// Беглые каторжники
		case 2:
			if(rand(15) > 3 || CheckAttribute(pchar, "GenQuest.Convict") || location.type == "seashore" || location.type == "mayak" ) return false;			
			if (sAreal == "Panama") return false;
			num = GetAttributesNum(grp); //кол-во человек в группе
			if(num <= 1) return false;
			if (num <= 2) num = 2;
			iRank = 2 + rand(3); //ранг каторжан
			
			pchar.GenQuest.Convict.ConvictQty = num;
			pchar.GenQuest.Convict.city = sCity;

			chrDisableReloadToLocation = true;
			
			arrayNPCModelHow = 0;
			for(i = 0; i < num; i++)
			{
				chr = GetCharacter(NPC_GenerateCharacterEx("Convict_" + i, "slave_"+(rand(8)+1), "man", "man", iRank, PIRATE, -1, true, "slave"));
				SetNPCModelUniq(chr, "convict", MAN);
				SetFantomParamFromRank(chr, iRank, true);
				locator = GetAttributeName(GetAttributeN(grp, i));
				ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
				chr.dialog.filename = "Quest\GenQuests_dialog.c";
				chr.dialog.currentnode = "First time";
				chr.greeting = "Gr_slave";
				chr.city = sCity;
				LAi_SetImmortal(chr, true); // До поры нельзя убить
				LAi_SetActorTypeNoGroup(chr);	
				if(i == 0) LAi_ActorDialog(chr, pchar, "", -1, 0.0);
				else LAi_ActorFollow(chr, pchar, "", -1);	
				LAi_Group_MoveCharacter(chr, "ConvictGroup");
				LAi_Group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
			}
			
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			pchar.GenQuest.Convict.Item = GenQuest_GenerateArtefact();
			pchar.GenQuest.Convict.city = sCity;
				
			iRnd = rand(9);
			if(iRnd <= 5) pchar.GenQuest.Convict.variant = 1;
			if(iRnd > 5 && iRnd < 8) pchar.GenQuest.Convict.variant = 2;
			if(iRnd >= 8) pchar.GenQuest.Convict.variant = 3;				
			pchar.GenQuest.Convict.var = rand(2);
			Log_TestInfo("Каторжане: сгенерился квест");			
		break;
		
		// Индейцы
		case 3:
			if (rand(10) > 7) return false;
			if (location.type == "seashore" || location.type == "mayak") return false;
			num = 4; //кол-во человек в банде
			str = "Carib"+ location.index + "_";
			
			// Генерим ранг
			if (sti(pchar.rank) > 6)
			{
				if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE * 2.5 / num);
				else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE * 1.6 / num);
			}
			else iRank = sti(pchar.rank) + 3;
			
			// определим тип энкаунтера
			string sEncType = "peace";
			if(rand(1)) sEncType = "war";
			
			//Начинаем перебирать локаторы и логинить фантомов
			string sModel = "miskito";
			if(sEncType == "war") sModel = "canib";
			
			LAi_grp_alarmactive = false;
			LAi_group_ClearAllTargets();
			
			iEncrnd = rand(2);
			if (!CheckAttribute(location, "locators.goto.fire")) iEncrnd = 0; // фикс костров
			if (!iEncrnd) num = GetAttributesNum(grp); //подстройка количества индейцев под количество локаторов, если спавн не у костра

			arrayNPCModelHow = 0;
			for(i = 0; i < num; i++)
			{
                chr = GetCharacter(NPC_GenerateCharacterEx(str + i, sModel + "_" + (rand(5) + 1), "man", "man", iRank, PIRATE, 1, true, "native"));
				chr.indian = "1";
				SetNPCModelUniq(chr, sModel, MAN);
                SetFantomParamFromRank(chr, iRank, true);
                if (iEncrnd)
                {
                    location.bonfire = true;
                    encGroup = "enc01";
                    locator = "ass"+(i+1);
                    ChangeCharacterAddressGroup(chr, location.id, "goto", locator);
                    LAi_SetGroundSitTypeNoGroup(chr);
                }
                else
                {
                    locator = GetAttributeName(GetAttributeN(grp, i));
                    ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
                    LAi_SetStayType(chr);
                }
                chr.dialog.filename = "Encounters\Indians.c";
                chr.greeting = "indiano"; //TODO: господи, это нужно поменять на что-то вменяемое...
                chr.name = GetIndianName(MAN);
                chr.lastname = "";
                chr.EncQty = num;
                if (sEncType == "war")
                {
                    chr.dialog.currentnode = "war_indian";
                    if (idRand(location.id + "war_indian", 9) < 8) LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_CaribBeforeDialog");
                    else LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_MiskitoBeforeDialog");
                }
                else
                {
                    chr.dialog.currentnode = "peace_indian";
                    if (idRand(location.id + "peace_indian", 9) > 8) LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_CaribBeforeDialog");
                    else LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, true, "LandEnc_MiskitoBeforeDialog");
                }
                LAi_group_MoveCharacter(chr, "CaribGroup_" + location.index);
			}
			
			str = "EncCarib_" + location.index;
			pchar.quest.(str).win_condition.l1					= "locator";
			pchar.quest.(str).win_condition.l1.location			= location.id;
			pchar.quest.(str).win_condition.l1.locator_group	= "encdetector";
			pchar.quest.(str).win_condition.l1.locator			= encGroup;
			pchar.quest.(str).win_condition						= "LandEnc_CaribBegin";
			pchar.quest.(str).EncQty							= num; //кол-во аборигенов
			pchar.quest.(str).LocIdx							= location.index;
			str = "TimeCarib_" + location.index;
			pchar.quest.(str).win_condition.l1				= "Timer";
			pchar.quest.(str).win_condition.l1.date.day		= GetAddingDataDay(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.month	= GetAddingDataMonth(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.year	= GetAddingDataYear(0, 0, 1);
			pchar.quest.(str).win_condition					= "LandEnc_CaribOver";
			pchar.quest.(str).EncQty						= num;
			pchar.quest.(str).LocIdx						= location.index;
		break;
		
		// Девицы в джунглях
		case 4:
			if (rand(12) > 6) return false;
			if (location.type == "seashore" || location.type == "mayak") return false; // На необитаемых  островах, маяках и бухтах нельзя
			num = GetAttributesNum(grp); //кол-во локаторов 
			if (num < 2) return false;
			if (CheckAttribute(pchar, "GenQuest.EncGirl")) return false;
			if (!CheckAttribute(location, "locators.reload.reloadW_back"))
			{			
				// Генерим ранг
				if (sti(pchar.rank) > 6)
				{
					if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
					else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
				}
				
				LAi_group_Delete("EnemyFight");
				LAi_group_Delete("LandEncGroup");
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
				LAi_SetFightMode(pchar, false);
				LAi_LockFightMode(pchar, true);
				chrDisableReloadToLocation = true;
				//Начинаем перебирать локаторы и логинить фантомов
				i = 0;
				arrayNPCModelHow = 0;
				while(i < num)
				{
					//Получим локатор для логина
					locator = GetAttributeName(GetAttributeN(grp, i));
					if (i == 0)
					{
						iChar = GetCharacterIndex("CangGirl");
						if (iChar > -1)
						{
						    InitCharacter(&characters[iChar], iChar);
						    iChar = -1;
						}

						switch(rand(2)) // генерим один из вариантов начала квеста
						{
							case 0:
								Log_QuestInfo("Девица в джунглях: сгенерился вариант 1");
								iChar =	NPC_GenerateCharacter("CangGirl", "girl_"+(rand(9)+1), "woman", "towngirl", 5, iNation, -1, false);
								chr = &characters[iChar];
								chr.dialog.filename = "Encounters\RapersGirl.c";
								chr.dialog.currentnode = "Begin_1";
								pchar.GenQuest.EncGirl = "Begin_1";
							break;
							case 1:	
								Log_QuestInfo("Девица в джунглях: сгенерился вариант 2");
								iChar =	NPC_GenerateCharacter("CangGirl", "horse0"+(rand(7)+1), "woman", "towngirl", 5, iNation, -1, false);
								chr = &characters[iChar];
								chr.dialog.filename = "Encounters\RapersGirl.c";
								chr.dialog.currentnode = "Begin_2";
								pchar.GenQuest.EncGirl = "Begin_2";
								pchar.GenQuest.EncGirl.Horse = true;									
							break;
							case 2:								
								Log_QuestInfo("Девица в джунглях: сгенерился вариант 3");
								iChar =	NPC_GenerateCharacter("CangGirl", "girl_"+(rand(9)+1), "woman", "towngirl", 5, iNation, -1, false);
								chr = &characters[iChar];
								chr.dialog.filename = "Encounters\RapersGirl.c";
								chr.dialog.currentnode = "Begin_3";
								pchar.GenQuest.EncGirl = "Begin_3";
							break;
						}
						chr.name = GenerateRandomName_Generator(iNation, "woman");
						chr.lastname = "";
						chr.greeting = "Enc_RapersGirl_1";
						ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
						LAi_SetActorType(chr);
						LAi_group_MoveCharacter(chr, "LandEncGroup");
						LAi_ActorDialog(chr, pchar, "", -1, 0);
						LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_RapersBeforeDialog");
						str = location.index;
						pchar.GenQuest.EncGirl.city = sCity; //  город девицы
						pchar.GenQuest.EncGirl.nation = iNation; //нация для слухов
						pchar.GenQuest.EncGirl.name = GetFullName(chr); //имя девицы
						pchar.GenQuest.EncGirl.LocIdx = location.index;
						chr.city = sCity;
						chr.chr_ai.disableDlg = "0";
						i++;
						continue;
					}
					chr = GetCharacter(NPC_GenerateCharacter("GangMan_" + i, "pirate_"+(rand(15)+1), "man", "man", iRank, PIRATE, 100, true));
					SetNPCModelUniq(chr, "pirate", MAN);
					SetFantomParamFromRank(chr, iRank, true);
					chr.dialog.filename = "Encounters\Rapers.c";
					chr.dialog.currentnode = "First time";
					chr.greeting = "Enc_Raiders";
					ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
					LAi_SetActorType(chr);
					LAi_group_MoveCharacter(chr, "EnemyFight");
					LAi_ActorFollow(chr, &characters[iChar], "", -1);
					LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_RapersBeforeDialog");
					// evganat - энциклопедия
					if (i == 1)
					{
						if (CheckRandomPage("questjungle", "rapers", -1))
						{
							chr.encyclopedia.tome = GetRandomTome();
							chr.encyclopedia.page = 5;
						}
					}
					i++;
				}

				if ("FortOrange" == sCity) iRnd = 0; //в оранже нет церкви
				else if (sti(pchar.rank) > 10) iRnd = 2;
				else iRnd = 1;
				pchar.GenQuest.EncGirl.variant = rand(iRnd);
				pchar.GenQuest.EncGirl.item = GenQuest_GenerateArtefact();
				pchar.GenQuest.EncGirl.sum  = its(500 * (sti(pchar.rank) + 10) + rand(5000));

				//сюрприз для любителей просто свалить из локации
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
				pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
			}
			else
			{	// Замануха в колодец
				LAi_group_Delete("LandEncGroup");
    			aref arRld, arDis;
				makearef(arRld, Locations[sti(location.index)].reload);
    			int	Qty = GetAttributesNum(arRld);
				str = "none";
				for (int a = 0; a < Qty; a++)
    			{
    				arDis = GetAttributeN(arRld, a);
    				if (arDis.name == "reloadW_back")
    				{
						str = arDis.go; //ID смежной локации, куда ведёт колодец
    				}
    			}
				if (str == "none") return false; //на всякий случай
				//--> снимаем возможный конфликт с бергларами
				if (sAreal == "SentMartin" || sAreal == "SantaCatalina")
				{
					iTemp = GetCharacterIndex("BerglarSantaCatalina");
					if (iTemp != -1 && characters[iTemp].location == str) return false;
					iTemp = GetCharacterIndex("BerglarMarigo");
					if (iTemp != -1 && characters[iTemp].location == str) return false;
				}
				//<-- снимаем возможный конфликт с бергларами
				locator = GetAttributeName(GetAttributeN(grp, 1));
				chr =	GetCharacter(NPC_GenerateCharacter("FriendGirl", "girl_"+(rand(9)+1), "woman", "towngirl", 5, iNation, 0, false));
				chr.dialog.filename = "Encounters\Colodec.c";
				chr.dialog.currentnode = "First time";
				chr.greeting = "Enc_RapersGirl_1";
				ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
				LAi_SetActorType(chr);
				LAi_group_MoveCharacter(chr, "LandEncGroup");
				LAi_ActorDialog(chr, pchar, "", -1, 0);
				pchar.GenQuest.EncGirl.locationId = str; //ID локации
				pchar.GenQuest.EncGirl.nation = iNation; //нация для слухов
				pchar.GenQuest.EncGirl.name = GetFullName(chr); //имя девки
				pchar.quest.Enc_FriendGirl_after.win_condition.l1 = "NPC_Death";
				pchar.quest.Enc_FriendGirl_after.win_condition.l1.character = "FriendGirl";
				pchar.quest.Enc_FriendGirl_after.win_condition = "Enc_FriendGirl_after";
			}
		break;
		
		// Военный патруль
		case 5:
			if (rand(10) > 3) return false;
			
			// Военному патрулю и палец в рот не клади даже на начальных уровнях
			num = GetAttributesNum(grp); //кол-во человек в патруле
			if (num <= 0) num = 1;
			if (sti(pchar.rank) > 14) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
			else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
			
			//Начинаем перебирать локаторы и логинить фантомов
			str = "Patrol"+ location.index + "_";
			string sGroup = "PatrolGroup_" + location.index; //имя группы
			LAi_group_Register("PatrolGroup_" + location.index);
			for(i = 0; i < num; i++)
			{
				if (i == 0)
				{
					chr = GetCharacter(NPC_GenerateCharacter(str + i, "off_"+NationShortName(iNation)+"_"+(rand(1)+5), "man", "man", iRank+2, iNation, 1, true));
					SetFantomParamFromRank(chr, iRank+2, true);
					chr.greeting = "off_kks"; //TODO: обновить подборку на другую, тут одна фраза
				}
				else
				{
					if (i == 3)
					{
						chr = GetCharacter(NPC_GenerateCharacter(str + i, NationShortName(iNation)+"_mush_"+(rand(3)+1), "man", "mushketer", iRank, iNation, 1, false));
						//SetFantomParamFromRank(chr, iRank, true);
					}
					else
					{
						chr = GetCharacter(NPC_GenerateCharacter(str + i, "sold_"+NationShortName(iNation)+"_"+(rand(7)+1), "man", "man", iRank, iNation, 1, true));
						SetFantomParamFromRank(chr, iRank, true);
					}
					chr.greeting = "soldier_arest";
				}
				chr.City = sCity;
				chr.CityType = "soldier";				
				chr.dialog.filename = "Encounters\Patrol.c";
				chr.EncQty = num;
				LAi_SetStayType(chr);
				LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "LandEnc_PatrolBeforeDialog");
				LAi_group_MoveCharacter(chr, sGroup);
				//Получим локатор для логина
				locator = GetAttributeName(GetAttributeN(grp, i));
				ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
			}
			LAi_group_SetLookRadius(sGroup, 100);
			LAi_group_SetHearRadius(sGroup, 100);

			str = "EncPatrol_" + location.index;
			pchar.quest.(str).win_condition.l1        = "locator";
			pchar.quest.(str).win_condition.l1.location = location.id;
			pchar.quest.(str).win_condition.l1.locator_group = "encdetector";
			pchar.quest.(str).win_condition.l1.locator = encGroup;
			pchar.quest.(str).win_condition = "LandEnc_PatrolBegin";
			pchar.quest.(str).EncQty = num; //кол-во патрульных
			pchar.quest.(str).LocIdx = location.index;
			str = "TimePatrol_" + location.index;
			pchar.quest.(str).win_condition.l1            = "Timer";
			pchar.quest.(str).win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.(str).win_condition               = "LandEnc_PatrolOver";	
			pchar.quest.(str).LocIdx = location.index;
			str = location.index;
			pchar.GenQuest.(str).nation = iNation; //нация патруля для слухов 
		break;
			
		// Квест "Правосудие на продажу" (Warship, Rosarak)
		case 6:
			if(rand(10) > 6) return false;
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale")) return false;
			if(location.type == "seashore" || location.type == "mayak") return false;
			num = GetAttributesNum(grp) - rand(2); //кол-во контриков
			if(num <= 0) num = 1; //если локаторов меньше четырех

			// Генерим ранг
			if (sti(pchar.rank) > 6)
			{
				if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
				else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
			}
			else iRank = sti(pchar.rank);
			
			//Начинаем перебирать локаторы и логинить фантомов
			LAi_grp_alarmactive = false;
			LAi_group_ClearAllTargets();
			
			arrayNPCModelHow = 0;
			for(i = 0; i < num; i++)
			{
                chr = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Jungle_" + i, "citiz_"+(rand(9)+21), "man", "man", iRank, PIRATE, 0, true));
				SetNPCModelUniq(chr, "smuggler", MAN);
                SetFantomParamFromRank(chr, iRank, true);
                locator = GetAttributeName(GetAttributeN(grp, i));
                ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
                chr.dialog.filename = "Quest\GenQuests_dialog.c";
                chr.dialog.currentnode = "First time";
                chr.greeting = "Gr_Smuggler_OnShore";
				chr.talker = rand(10);
				chr.NoCheckFightMode = true; //для CitizenType
                LAi_SetCitizenType(chr);
				LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr)-1, false, "JusticeOnSale_BeforeDialog");
                LAi_group_MoveCharacter(chr, "JusticeOnSaleGroup_" + location.index);
			}
			//--> Rosarak. Корабль контры фиксируется сразу, а не на ходу
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.CapModel = "citiz_"+(rand(9)+21);
			PChar.GenQuest.JusticeOnSale.CapName  = GenerateRandomName_Generator(PIRATE, "man");
			//<-- Корабль контры
			PChar.GenQuest.JusticeOnSale.LocIdx = location.index;
			PChar.GenQuest.JusticeOnSale.EncQty = num;
			PChar.GenQuest.JusticeOnSale.CityId = sCity;
			PChar.GenQuest.JusticeOnSale.Nation = iNation;
			if (sCity != "Panama") PChar.GenQuest.JusticeOnSale.ShoreId = SelectQuestShoreLocation();
			else
			{
                if (rand(1)) PChar.GenQuest.JusticeOnSale.ShoreId = "Shore47";
                else PChar.GenQuest.JusticeOnSale.ShoreId = "Shore48";
            }
			PChar.GenQuest.JusticeOnSale.SmugglerName  = GenerateRandomName_Generator(PIRATE, "man");
			PChar.GenQuest.JusticeOnSale.SmugglerModel = "officer_"+(rand(19)+1);
			PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.JusticeOnSale_LocationExit.win_condition.l1.location = PChar.location;
			PChar.Quest.JusticeOnSale_LocationExit.function = "JusticeOnSale_LocationExit";
			PChar.Quest.DeleteGroupOnExitLocation.GroupName = "JusticeOnSaleGroup_" + location.index;
		break;
		
		// Пираты на необитаемом острове (Warship)
		case 7:
			// if(num <= 0) return false;
			if(rand(4) == 1 && !CheckAttribute(location, "deadlocked") && !CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited") 
			&& !CheckAttribute(pchar, "GenQuest.ShipWreck") && reload_cur_island_index > -1) // reload_cur_island_index > -1, значит ГГ пришёл с моря
			{
				iRank = sti(PChar.rank) + MOD_SKILL_ENEMY_RATE;
				
				num = 2 + makeint(MOD_SKILL_ENEMY_RATE / 3) + idRand(location.id + "PiratesOnUninhabited", 1); // Кол-во пиратов
				PChar.GenQuest.PiratesOnUninhabited.PiratesQty = num;
				
				i = 0;
				arrayNPCModelHow = 0;
				while(i < num)
				{
					chr = GetCharacter(NPC_GenerateCharacter("PirateOnUninhabited_" + i, "pirate_"+(rand(15)+1), "man", "man", iRank, PIRATE, -1, true));
					SetNPCModelUniq(chr, "pirate", MAN);
					SetFantomParamFromRank(chr, iRank, true);
					locator = GetAttributeName(GetAttributeN(grp, i));
					ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
					//ChangeCharacterAddressGroup(chr, location.id, "goto", "goto" + (i + 1));
					chr.dialog.filename = "Quest\GenQuests_dialog.c";
					chr.dialog.currentnode = "First time";
					chr.greeting = "Gr_MiddPirate"; // Enc_Raiders
					LAi_SetImmortal(chr, true); // До поры нельзя убить
					LAi_SetActorTypeNoGroup(chr);
					
					if(i == 0)
					{
						LAi_ActorDialog(chr, PChar, "", -1, 0.0);
					}
					else
					{
						LAi_ActorFollow(chr, PChar, "", -1);
					}
					
					LAi_Group_MoveCharacter(chr, "PiratesOnUninhabitedGroup");
					LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
					
					i++;
				}
				
				PChar.quest.PiratesOnUninhabited_LocExit.win_condition.l1 = "ExitFromLocation";
				PChar.quest.PiratesOnUninhabited_LocExit.win_condition.l1.location = PChar.location;
				PChar.quest.PiratesOnUninhabited_LocExit.function = "PiratesOnUninhabited_LocationExit";
				
				Log_TestInfo("Пираты на необитайке: сгенерился квест");
			}
		break;
		
		// Потерпевшие кораблекрушение
		case 8:
			// if(num <= 0) return false; // <- Зачем это здесь???
			if(rand(4) == 1 && !CheckAttribute(pchar, "GenQuest.PiratesOnUninhabited") && !CheckAttribute(pchar, "GenQuest.ShipWreck") && pchar.location == pchar.location.from_sea)
			{
				iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
				
				num = 4; // Кол-во кораблекрушенцев
				pchar.GenQuest.ShipWreck.Qty = num;	
				pchar.GenQuest.ShipWreck.Nation = idRand(location.id + "Nation", 3); // нация
				pchar.GenQuest.ShipWreck.Prize = GenQuest_GenerateTotem();
				
				i = 0;
				arrayNPCModelHow = 0;
				while(i < num)
				{
					chr = GetCharacter(NPC_GenerateCharacter("ShipWreck_" + i, "pirate_"+(rand(15)+1), "man", "man", iRank, sti(pchar.GenQuest.ShipWreck.nation), -1, true));
					SetNPCModelUniq(chr, "pirate", MAN);
					SetFantomParamFromRank(chr, iRank, true);
					locator = GetAttributeName(GetAttributeN(grp, i));
					ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
					//ChangeCharacterAddressGroup(chr, location.id, "goto", "goto" + (i + 1));
					FaceMaker(chr);
					chr.dialog.filename = "Quest\GenQuests_dialog.c";
					chr.dialog.currentnode = "First time";
					chr.greeting = "Gr_MiddPirate"; // Enc_Raiders
					LAi_SetImmortal(chr, true); // До поры нельзя убить
					LAi_SetActorTypeNoGroup(chr);
					
					if(i == 0)
					{
						pchar.GenQuest.ShipWreck.Name = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
						chr.name = pchar.GenQuest.ShipWreck.Name;
						chr.lastname = "";
						LAi_ActorDialog(chr, pchar, "", -1, 0);
					}
					else
					{
						LAi_ActorFollow(chr, pchar, "", -1);
					}
					
					LAi_Group_MoveCharacter(chr, "ShipWreckGroup");
					LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
					
					i++;
				}
				SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
				Log_TestInfo("Кораблекрушенцы: сгенерился квест");				
			}
		break;
	}
	return true;
}

//функция для генерации в локацию "монстров" с которыми можно взаимодействовать. Пока только обезьяны
void LAi_CreateMonsters(ref location)
{
    if (CheckAttribute(location, "type") && StrHasStr(location.type, "Dungeon,cave", 1)) return;
	//Не всегда генерим
	if (rand(99) <= 94) return;

	//Возможность логина монстров в локацию
	if (!LAi_LocationIsMonstersGen(location)) return;
	if (LAi_IsCapturedLocation) return; // fix - не генерить в захваченные ExitTown

	//монстров не генерим если начался какой-нибудь энкаунтер
	int checkEnc = LAi_numloginedcharacters - 1 - GetCountFighters();
    if (checkEnc > 0) return;

	string group = "locators." + LAI_GROUP_MONSTERS;
	//Максимально возможное количество монстров
	int maxMonsters = 20 - LAi_numloginedcharacters;
	if(maxMonsters <= 0) return;
	//Перебераем локаторы, выбирая свободные
	aref grp;
	makearef(grp, location.(group));
	int num = GetAttributesNum(grp);
	if (num <= 0) return;
	if (maxMonsters > num) maxMonsters = num;
	int locatorPos = 0;
	int loginedMonsters = 0;
	for (int i = 0; i < maxMonsters; i++)
	{
		//тут должна быть логика распределения монстров. Но пока только обезьяны
		LAi_MonkeyLogin(location, LAI_GROUP_MONSTERS, GetAttributeName(GetAttributeN(grp, i)));
	}
}

void LAi_MonkeyLogin(ref location, string group, string locator)
{
    if (rand(100) < 25) return; //скорее да, чем нет
	ref chr;
	//В лунную ночь с дикими карибами спавнятся обезьяны-скелеты
	if (or(GetTime() < 6.0, GetTime() > 23.0) && CheckCharacterPerk(pchar, "WildCaribbean"))
	{
	    chr = LAi_CreateFantomCharacterEx("monkey", "monkey", group, locator);
		chr.skeleton = "1";
	    chr.name = FindPersonalName("DeathMonkey_name");
	    chr.sex = "skeleton";
        LAi_group_MoveCharacter(chr, LAI_GROUP_MONSTERS);
	}
	//в остальное время мирные обезьянки <3
	else
	{
	    chr = LAi_CreateFantomCharacterEx("koata1", "monkey", group, locator);
		chr.animal = "1";
	    chr.name = FindPersonalName("Monkey_name");
	    LAi_SetHP(chr, 10.0, 10.0); //макаки дохлые
	    LAi_group_MoveCharacter(chr, LAI_GROUP_ACTOR);
	}
	LAi_SetMonkeyTypeNoGroup(chr);
	chr.lastname = "";
    RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);
    GiveItem2Character(chr, "unarmed");
    EquipCharacterbyItem(chr, "unarmed");

    ChangeCharacterAddressGroup(chr, pchar.location, group,  locator);
}
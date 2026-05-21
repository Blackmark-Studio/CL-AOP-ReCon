int CheckColonyMoney(string sColony)
{
	int iMoney;
	iMoney = sti(Colonies[FindColony(sColony)].money);
	return iMoney;
}

void RemoveColonyMoney(string sColony)
{
	int iMoney;
	int iColony = FindColony(sColony);
	iMoney = sti(Colonies[iColony].money);
	AddMoneyToCharacter(pchar, iMoney);
	Colonies[iColony].money = 0;
}

// клепаем фортовых командеров
void CreateColonyCommanders()
{
	int iChar;
	
	string sColony;

	int i;
	float x, y, z;
	
	for (i=0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation == "none") continue; // необитайки
		
		// зададим базовых мэров городов
		iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
		if (iChar != -1)
		{   // мэр есть
        	SetTownMayor(&characters[iChar], sti(colonies[i].nation));
        	characters[iChar].from_sea = colonies[i].from_sea; // для захвата с суши
        	characters[iChar].Default  = characters[iChar].location;  // чтоб сухопутные города вернули население
        	characters[iChar].Default.BoardLocation = colonies[i].Default.BoardLocation;
        	characters[iChar].Mayor = true; // признак мэра
        }
		
		if (CheckAttribute(&colonies[i], "HasNoFort"))
		{
            if (iChar != -1)
            {   // мэрам пропишем кол-во солдат
				characters[iChar].Default.Crew.Quantity    = 1900;
				characters[iChar].Default.Crew.MinQuantity = 1200;
				characters[iChar].Default.nation = characters[iChar].nation; // запоминаем нацию, тех кто бы изначально (кто отбивать приплывет)
			}
			continue;
		}
		
		colonies[i].commander = colonies[i].id + " Fort Commander";
		
		iChar = GeneratePortCharacter(sti(colonies[i].nation), WITH_SHIP, "pofficer", MAN, 1, FORT_COMMANDER); //pofficer как заглушка
		Nations[sti(colonies[i].nation)].fort = sti(Nations[sti(colonies[i].nation)].fort) + 1; // число фортов нации
		characters[iChar].id = colonies[i].id + " Fort Commander";
		
		if (HasStr(characters[iChar].id, "Providencia")) // запрет абордажа форта Провиденсии
			characters[iChar].Abordage.Enable = false;
		
		characters[iChar].location = colonies[i].island;
		characters[iChar].location.group = "reload";
		characters[iChar].location.locator = "reload_fort" + Colonies[i].num;
		colonies[i].commanderIdx = iChar; // оптимизация поиска фортовика для погоды (волны у острова)
		// boal -->
		characters[iChar].City = colonies[i].id;  // признак горожанина
		characters[iChar].CheckLicence    = true; // Проверять наличие торговой лицензии при распознании,нужно фортам и сторожевикам
		if (FindIslandLocatorXYZ(characters[iChar].location, characters[iChar].location.locator, &x, &y, &z))
		{
		    characters[iChar].Ship.Pos.x = x;
		    characters[iChar].Ship.Pos.z = y;
		    characters[iChar].Ship.Pos.z = z;
		}
		SetCaptanModelByEncType(&characters[iChar], "war"); // модель офицера нации
		SetSeaFantomParam(&characters[iChar], "war"); // генератор!!
		// boal <--
		SetCharacterRelationBoth(iChar,nMainCharacterIndex,RELATION_FRIEND);
		UpdateRelations();

  		characters[iChar].Fort.Cannons.Charge.Type = GOOD_BOMBS;

        SetCrewQuantityFull(&characters[iChar]);
        
		characters[iChar].Fort.Cannons.Type.1 = CANNON_TYPE_CANNON_LBS42;
		characters[iChar].Fort.Cannons.Type.2 = -1;
		characters[iChar].Fort.Cannons.Type.3 = -1;

		if(sti(colonies[i].fort) > 1)
		{
			characters[iChar].Fort.Cannons.Type.2 = CANNON_TYPE_CULVERINE_LBS32;
		}
		if(sti(colonies[i].fort) > 2)
		{
			characters[iChar].Fort.Cannons.Type.3 = CANNON_TYPE_CANNON_LBS48;
		}
		// boal -->
		if(colonies[i].id == "Panama")
		{
			characters[iChar].Default.Crew.Quantity    = 2700;
			characters[iChar].Default.Crew.MinQuantity = 2700; // Не появится атрибут Fort.Mode
		}
		else
		{
			characters[iChar].Fort.Mode = FORT_NORMAL; // fix по умолчанию
			characters[iChar].Default.Crew.Quantity    = ShipsTypes[SHIP_FORT].MaxCrew;  // для всех одинаково, для генератора сухопутных боевок
			characters[iChar].Default.Crew.MinQuantity = ShipsTypes[SHIP_FORT].MinCrew;
		}
		characters[iChar].Default.nation        = characters[iChar].nation; // запоминаем нацию, тех кто бы изначально (кто отбивать приплывет)
		characters[iChar].Default               = colonies[i].from_sea;
        characters[iChar].Default.BoardLocation = colonies[i].Default.BoardLocation;
        characters[iChar].Default.Island        = colonies[i].island; // остров для осад
        characters[iChar].from_sea              = colonies[i].from_sea; // для захвата с суши
		// boal <--
	}
}

// чиним корабли ГГ после захвата города
void RepairAllShips()
{
    int cn;
	ref chr;
	for (int i = 0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			chr = &characters[cn];
			ProcessHullRepair(chr, 100.0);
			ProcessSailRepair(chr, 100.0);
			ShipOverhaul(chr);
		}
	}
}
//// boal -->
int GetFortCommanderIdx(string _city)
{
     int ind = -1;
     ind = GetCharacterIndex(_city + " Fort Commander");
	 if (ind != -1) return ind;
	 // если нет командера, значит мэр главный
	 ind = GetCharacterIndex(_city + "_Mayor");
	 return ind;
}

ref GetFortCommander(string _city)
{
     int ind = GetFortCommanderIdx(_city);

	 return GetCharacter(ind);
}

#define MAX_TOWN_CREW 9 // мах колво реальных солдат в локации (в сумме 32 мах)
#define MAX_ESCADRA_CREW 5 // помощь эскадре - наши солдаты
#define MAX_TOWN_MUSHKETER 3 //мушкетеры в городе

void SetCrewBackAfterBattle()
{
    float  fTemp, fTemp2;
    int    i, iTemp;
	// вернём живых на корабль -->
	fTemp = stf(Pchar.GenQuestFort.PlayerCrew) * stf(Pchar.GenQuestFort.PlayerCrew_per_char); // живые
	fTemp2 = 0.9 + MakeFloat(GetSummonSkillFromName(Pchar, SKILL_DEFENCE)) / SKILL_MAX;
	i     = makeint((stf(Pchar.GenQuestFort.PlayerCrew_Start) - fTemp) /fTemp2 + 0.3); // трупы
	iTemp = makeint((stf(Pchar.GenQuestFort.PlayerCrew_Start) - fTemp)); // трупы  без бонуса
	// расчёт медицины -->
	iTemp = makeint((iTemp - i)*0.6);
	if (iTemp > 0)
	{
	    if (GetCargoGoods(Pchar, GOOD_MEDICAMENT) < iTemp)
	    {
            iTemp = iTemp - GetCargoGoods(Pchar, GOOD_MEDICAMENT); // умерли от ран
			RemoveCharacterGoodsSelf(Pchar, GOOD_MEDICAMENT, GetCargoGoods(Pchar, GOOD_MEDICAMENT)); // все нулим
			i += iTemp; // трупов больше
			Log_Info(StringFromKey("InfoMessages_70", FindSailorString(iTemp, "No")));
	    }
	    else
	    {
	        RemoveCharacterGoodsSelf(Pchar, GOOD_MEDICAMENT, iTemp);
	        if (GetCargoGoods(Pchar, GOOD_MEDICAMENT) < 16)
		    {
		        Log_Info(StringFromKey("InfoMessages_71", UpperFirst(XI_ConvertString("musicmod_s")), pchar.Ship.Name));
		    }
	    }
	}
	// расчёт медицины <--
	Statistic_AddValue(Pchar, "DeadCrewTown", i);
	AddCharacterExpToSkill(Pchar, "Defence", makeint(i / 3 + 0.5)); //качаем защиту
	RemoveCharacterGoodsSelf(Pchar, GOOD_WEAPON, i*0.7);// тк сабли уже брали
	i = sti(Pchar.GenQuestFort.PlayerCrew_Start) - i; // выжившие с бонусом
	SetCrewQuantityOverMax(Pchar, i);
	AddTroopersCrewToOther(Pchar); // 09.07.05
}

bool PrepareTownBattle()
{
    ref    fortChr;
    int    mcrew, ecrew, maxcrew;
    float  rel;
    string sTemp, sCity, sNext;
    int    i, how;
    ref    nulChr;

    nulChr  = &NullCharacter;
    fortChr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));

    sCity   = fortChr.City;
    if (!CheckAttribute(nulChr, "GenQuestFort." + sCity))
    {
        Log_TestInfo("ERROR: Не задан обход города при захвате!!!");
        return false;
    }

    mcrew = GetCrewQuantity(Pchar) + GetTroopersCrewQuantity(Pchar);
    if (CheckAttribute(fortChr, "Fort.Mode") && sti(fortChr.Fort.Mode) != FORT_DEAD)
    { // это фортовый город и форт целый
        ecrew = sti(fortChr.Default.Crew.Quantity) + makeint(sti(fortChr.Default.Crew.Quantity) * (MOD_SKILL_ENEMY_RATE / 10.0));
    }
    else
    { // форт убит
        ecrew = sti(fortChr.Default.Crew.MinQuantity) + makeint(sti(fortChr.Default.Crew.MinQuantity) * (MOD_SKILL_ENEMY_RATE / 10.0));
    }

    Pchar.GenQuestFort.PlayerCrew_Start = mcrew; // скока было
	// учет морали -->
    rel = (stf(Pchar.ship.crew.morale) - MORALE_NORMAL) / MORALE_NORMAL;
	if (rel < -0.99) rel = -0.99;
	if (rel > 0.5)  rel = 0.5 + rel / 5.0;
	mcrew = makeint(mcrew * (rel * 0.3 + 1.0));
    // учет морали <--
    
    // опыт солдат
    ///  TODO 29.07.06 пока не ясно как выделить долю и прикрутить опыт со всех коарблей, когдя это выжившие после форта. rel = (GetCrewQuantity(Pchar) * GetCrewExp(Pchar, "Soldiers") / GetCrewExpRate()) / stf(Pchar.GenQuestFort.PlayerCrew_Start);
    // получается, что опыт солдат только для моря, на суше всё по-старому.

    how     = sti(nulChr.GenQuestFort.(sCity).howSolder);
    maxcrew = (how - 1) * MAX_TOWN_CREW;

    if(mcrew > ecrew)
	{
        if(mcrew > maxcrew)
		{
			rel = makefloat(mcrew) / makefloat(maxcrew);
			mcrew = maxcrew;
			ecrew = MakeInt(ecrew / rel + 0.5);
		}
	}
	else
	{
        if(ecrew > maxcrew)
		{
			rel = makefloat(ecrew) / makefloat(maxcrew);
			ecrew = maxcrew;
			mcrew = MakeInt(mcrew/rel + 0.5);
		}
	}
	if(mcrew < 1) mcrew = 1;
	if(ecrew < 1) ecrew = 1;

    Pchar.GenQuestFort.TownCrew   = ecrew;
    Pchar.GenQuestFort.PlayerCrew = mcrew; // сколько моделей
	
	// AlexBlade - Для Лейфа считаем отдельно
	if (CheckAttribute(pchar, "questTemp.Ascold") && pchar.questTemp.Ascold == "Ascold_ImMummy")
	{
		Pchar.GenQuestFort.PlayerCrew = makeint(makefloat(ecrew) * 1.25);
	}

    Pchar.GenQuestFort.PlayerCrew_per_char = makefloat(stf(Pchar.GenQuestFort.PlayerCrew_Start) / stf(Pchar.GenQuestFort.PlayerCrew));

    if (CheckAttribute(pchar, "quest.Enemy_" + sCity))// уже в осаде будет токо у сухопутных, тк иначе убирается при форте
    {
        Pchar.quest.FightInTown_Next0.win_condition.l1          = "location";
	    Pchar.quest.FightInTown_Next0.win_condition.l1.location = Pchar.location;
	    Pchar.quest.FightInTown_Next0.win_condition             = "FightInTown";
        return true;
    }

    // прерывания
    how     = sti(nulChr.GenQuestFort.(sCity).how);
    for (i=0; i < how; i++)
    {
        sTemp = "FightInTown_Next" + i;
        sNext = "next" + i;

		Pchar.quest.(sTemp).win_condition.l1          = "location";
	    Pchar.quest.(sTemp).win_condition.l1.location = nulChr.GenQuestFort.(sCity).(sNext);
	    Pchar.quest.(sTemp).win_condition             = "FightInTown";
    }
    // прерывание на сброс захвата (если слиняли раньше)
    Pchar.quest.FreeCaptureForts.win_condition.l1 = "MapEnter";
    Pchar.quest.FreeCaptureForts.win_condition    = "FreeCaptureForts";
    return true;
}

void AfterTownBattle()
{
    ref    fortChr;
    string sTemp, sCity;
    int    i, how;
    ref    nulChr;

    nulChr  = &NullCharacter;
	if (CheckAttribute(Pchar, "GenQuestFort.StartAttack" )) DeleteAttribute(Pchar, "GenQuestFort.StartAttack");	
    if (!CheckAttribute(Pchar, "GenQuestFort.fortCharacterIdx")) return; // ещё не было

	fortChr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    bDisableFastReload = false;
    chrDisableReloadToLocation = false;

    sCity   = fortChr.City;
    how     = sti(nulChr.GenQuestFort.(sCity).how);

    // прерывания
    for (i=0; i < how; i++)
    {
        sTemp = "FightInTown_Next" + i;

		Pchar.quest.(sTemp).over          = "yes";
    }
}

void SoundInResidenceBattle()
{
	switch (rand(1))
    {
        case 0:
            PlaySound("soldier_arest");
        break;
        case 1:
            PlaySound("soldier_common");
        break;
    }
}

// Нужны две разные функции, чтобы использовать в винкондах
void VillemstadResGatesLock()
{
	int n = FindLocation("Villemstad_town");
	locations[n].models.night.rinok = "Villemstad_rinokN";
	DeleteAttribute(&locations[n], "models.night.rinok.tech");
	locations[n].models.night.charactersPatch = "Villemstad_patch_night";
}
void VillemstadResGatesUnlock()
{
	int n = FindLocation("Villemstad_town");
	locations[n].models.night.rinok = "Villemstad_rinokN_Capture";
	locations[n].models.night.rinok.tech = "DLightModel";	
	locations[n].models.night.charactersPatch = "Villemstad_patch_night_Capture";
}

// противники рабы
ref SetFantomSlaves(string group, string locator, string enemygroup)
{
    string emodel;
    ref    Cr;

	switch(rand(12))
	{
		//нигры 2/3
		case 0:  emodel = "slave_1";	break;
		case 1:  emodel = "slave_2";	break;
		case 2:  emodel = "slave_3";	break;
		case 3:  emodel = "slave_4";	break;
		case 4:  emodel = "slave_1";	break;
		case 5:  emodel = "slave_2";	break;
		case 6:  emodel = "slave_3";	break;
		case 7:  emodel = "slave_4";	break;
		//белые
		case 8:  emodel = "slave_5";	break;
		case 9:  emodel = "slave_6";	break;
		case 10: emodel = "slave_7";	break;
		case 11: emodel = "slave_8";	break;
		case 12: emodel = "slave_9";	break;
	}

    Cr = LAi_CreateFantomCharacterEx(emodel, "man", group, locator);

    if (Cr.location.locator != "")
    {
		SetFantomParam(Cr);
		string blade;
		switch (rand(3))
        {
            case 0: blade = "kocherg";					break;
            case 1: blade = GetGeneratedItem("blade1");	break;
            case 2: blade = GetGeneratedItem("blade5");	break;
            case 3: blade = GetGeneratedItem("topor3");	break;
        }
		GiveItem2Character(Cr, blade);
		EquipCharacterByItem(Cr, blade);

	    LAi_group_MoveCharacter(Cr, enemygroup);
	    LAi_NoRebirthEnable(Cr); //не показывать убитых при входе в локацию
	    LAi_LoginInCaptureTown(Cr, true); // для записи игры
    }
    return Cr;
}

/* AlexBlade - defenderType: [
	fort(_mush),
	town(_mush | _off),
	guard,
	elite,
	navy(_mush),
] */
ref SetFantomDefenceForts(string group, string locator, int nation, string enemygroup, string defenderType)
{
    ref chr;
	string sCharType;
	bool isMush = false;
	
	if (defenderType == "")
	{
		if (nation == PIRATE)
		{
			sCharType = "pirate";
		} 
		else
		{
			sCharType = "army_sold";
		}
	}
	else
	{
		if (nation == PIRATE)
		{
			sCharType = "pirate";
			
			switch(defenderType)
			{
				case "fort": sCharType = "pirate"; break;
				case "fort_mush": 
					sCharType = "pirate_mush";
					isMush = true;
				break;
				case "town_mush": 
					sCharType = "pirate_mush";
					isMush = true;
				break;
				case "guard": sCharType = "mercenary"; break;
			}
		}
		else
		{
			switch(defenderType)
			{
				case "fort": sCharType = "army_sold"; break;
				case "fort_mush": 
					sCharType = "army_sold_mush";
					isMush = true;
				break;
				case "town": sCharType = "urban_sold"; break;
				case "town_mush": 
					sCharType = "urban_mush";
					isMush = true;
				break;
				case "town_off": sCharType = "urban_off"; break;
				case "guard": sCharType = "guard"; break;
				case "elite":
					sCharType = "elite_" + NationShortName(nation);
					if (nation == ENGLAND)
						isMush = true;
				break;
				case "navy": sCharType = "navy_sold"; break;
				case "navy_mush":
					sCharType = "navy_mush";
					isMush = true;
				break;
			}
		}
	}
	
    chr = GetCharacter(NPC_GeneratePhantomCharacter(sCharType, nation, MAN, 0));
	if (isMush)
		chr.model.animation = "mushketer";

	//Логинем персонажа в локацию
	if(IsEntity(loadedLocation) != true)
		chr.location = "none";
	else
		chr.location = loadedLocation.id;
	chr.location.group = "";
	chr.location.locator = "";
	chr.location.from_sea = "";
	chr.location.fantom = "1";

	chr.chr_ai.type    = LAI_DEFAULT_TYPE;
	chr.chr_ai.tmpl    = LAI_DEFAULT_TEMPLATE;
	chr.chr_ai.group   = LAI_DEFAULT_GROUP;
	chr.chr_ai.alarmreact = LAI_DEFAULT_ALARMREACT;
	chr.chr_ai.grpalarmr  = LAI_DEFAULT_GRPALARMR;
	chr.chr_ai.gun.charge  = LAI_DEFAULT_CHARGE;
	chr.chr_ai.musket.charge  = LAI_DEFAULT_CHARGE;
	chr.chr_ai.FencingType  = "Fencing";
	SetEnergyToCharacter(chr);
	if(LAi_numloginedcharacters >= MAX_CHARS_IN_LOC)
	{
		Trace("SetFantomDefenceForts -> many logined characters in location > " + MAX_CHARS_IN_LOC);
		return chr;
	}
	LAi_AddLoginedCharacter(chr);
	if(!CreateCharacter(chr))
	{
		Trace("SetFantomDefenceForts -> CreateCharacter return false");
		return chr;
	}
	//Поставим персонажа на локатор
	if(group == "")
	{
		group = "goto";
		locator = "";
	}
	if(locator == "")
	{
		//Выбираем дальний локатор
		locator = LAi_FindNPCLocator(group);
	}
	
	chr.location.group = group;
	chr.location.locator = locator;
	
	if(SendMessage(chr, "lss", MSG_CHARACTER_ENTRY_TO_LOCATION, group, locator) == false)
	{
		Trace("SetFantomDefenceForts -> can't teleportation character to <" + group + "::" + locator + ">");
	}

    if (chr.location.locator != "")
    {
		if (isMush)
		{
    		CalculateAppropriateSkills(chr);
    		SetFantomHP(chr);
			LAi_SetWarriorType(chr);
		}
		
	    LAi_group_MoveCharacter(chr, enemygroup);
	    LAi_NoRebirthEnable(chr); //не показывать убитых при входе в локацию
	    LAi_LoginInCaptureTown(chr, true); // для записи игры
    }
    return chr;
}

//AlexBlade - Расширение SetFantomDefenceForts, для локальных столкновений
ref SetFantomDefenceLocal(string group, string locator, int nation, string enemygroup)
{
	return SetFantomDefenceForts(group, locator, nation, enemygroup, "");
}

ref SetFantomDefenceLocal_ExType(string group, string locator, int nation, string enemygroup, string defenderType)
{
	return SetFantomDefenceForts(group, locator, nation, enemygroup, defenderType);
}

ref SetFantomOfficer(string group, string locator, int nation, string enemygroup)
{
    string emodel,natmod;
    ref Cr;

    natmod = NationShortName(nation);
    if(nation == PIRATE)
    {
		//officer_
		emodel = "citiz_" + (rand(9) + 51); //watch_quest_moment, смотреть в каких моментах фунция используется
											//вроде, пиратов там вообще не бывает, так что это просто так здесь
    }
    else
    {
		emodel = "off_" + natmod + "_" + (rand(1) + 5);
    }

    Cr = LAi_CreateFantomCharacter(emodel, group, locator);
    FaceMaker(Cr);

    if (Cr.location.locator != "")
    {
		SetFantomParam(Cr);
		Cr.nation = nation;
	    LAi_group_MoveCharacter(Cr, enemygroup);
	    LAi_NoRebirthEnable(Cr); //не показывать убитых при входе в локацию
	    LAi_LoginInCaptureTown(Cr, true); // для записи игры
    }
    return Cr;
}

void TWN_FreeCaptureForts() // уберем солдат, откроем входы (на всяк случай) при выходе на карту
{
	ref sld, Builder;
	
	AfterTownBattle();
    // вернём людей досрочно
    sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Builder = characterFromID(sld.City + "_Mayor");
    if (CheckAttribute(Builder, "Default"))
    {
        SetLocationCapturedState(Builder.Default, false); // тк может быть убит или в тюрме - берем его резиденцию всегда
		if(Builder.greeting == "mayor_capture") Builder.greeting = NationShortName(sti(Builder.nation)) + "_gov_common";
    }
}

void TWN_Capture_Forts()
{
    ref    sld, Builder;
    aref   aData;
    string sCap, sGroup;
	iAbordageMode = 0;
    
    sGroup = "NoGroupFind"; // чтоб не нашли в Group_FindGroup
    makearef(aData, NullCharacter.Siege);
    if (CheckAttribute(aData, "nation"))
    {
        sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
        sGroup = "Sea_"+sCap+"1";
    }
    
	if (PrepareTownBattle())
    {
        sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));

		if (!CheckAttribute(Pchar, "GenQuestFort.SoundOff"))  // будет для выхода в море и повтора захвата
		{
        	PlaySound("Boarding_1");
        	if (isCityHasFort(sld.City))// довесок после форта
            {
            	AddCharacterExpToSkillSquadron(Pchar, "Leadership", 230);
			    AddCharacterExpToSkillSquadron(Pchar, "Sailing", 200);
			    AddCharacterExpToSkillSquadron(Pchar, "Sneak", 200);
		    }
        }
        else
        {
            DeleteAttribute(Pchar, "GenQuestFort.SoundOff");
        }
		
        Builder = characterFromID(sld.City + "_Mayor");
		
        if (!CheckQuestAttribute("Union_with_Escadra", "Yes") || 
			!CheckAttribute(aData, "Colony") || 
			!CheckAttribute(aData, "island") || 
			Builder.City != aData.Colony) 
	    { // иначе за место мэра будет сам ГЛАВА эскадры
            LAi_LoginInCaptureTown(Builder, true);
			//homo
			if (Group_FindGroup(sGroup)!= -1)
			{
                Builder = Group_GetGroupCommander(sGroup);
                LAi_LoginInCaptureTown(Builder, false); // убрать с того раза
            }
            return;	 // по утверждению Хомо идет почему-то дальше код
		}
		else
		{   // TODO
            LAi_LoginInCaptureTown(Builder, false); // убрать мэра с того раза
            //homo
			Builder = Group_GetGroupCommander(sGroup);
            LAi_SetSitTypeNoGroup(Builder);
            ChangeCharacterAddressGroup(Builder, aData.Colony+"_townhall", "sit", "sit1" );
		    LAi_LoginInCaptureTown(Builder, true);
		    LAi_SetCurHPMax(Builder); // если он умер
		    LAi_SetImmortal(Builder, true);
		    Builder.dialog.currentnode = "Talk_Capture_City";
		    
        	string sQuest = "LeaveTown";
            pchar.quest.(sQuest).win_condition.l1 = "location";
            pchar.quest.(sQuest).win_condition.l1.location = aData.island;
            pchar.quest.(sQuest).function = "LeaveTown";
		}
	}
}

void TWN_FightInTown()
{
	if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Attack", "1"))
		TEV.Music.ForceKeepPlaying = "";

    ref sld, Builder;
    int j, i, natEsc;
    string sTemp, snCity, sModel, sMethod;
    aref aData;  //  homo
    makearef(aData, NullCharacter.Siege);   // homo
    
	sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Log_TestInfo("Cur boarding_player_crew: " + Pchar.GenQuestFort.PlayerCrew);
    Log_TestInfo("Cur TownCrew: " + Pchar.GenQuestFort.TownCrew);
    snCity = sld.City;

    bool bDefenderHpBonus = false; //HardCoffee бонус к хп солдат от перка командира.
    ref rCommander = GetFortCommander(snCity);
    if (rCommander.id != NullCharacter.id) bDefenderHpBonus = CheckOfficersPerk(rCommander, "Prevention");

    if (loadedLocation.type == "residence")
    {
		DeleteAttributeMass(&TEV, "LootCollector", "CanBeRun,Transfer");
		// вернём живых на корабль -->
		SetCrewBackAfterBattle();
        
		if (CheckQuestAttribute("Union_with_Escadra", "Yes") && CheckAttribute(aData, "Colony") && snCity == aData.Colony) //fix homo
        {
            chrDisableReloadToLocation = true;
			// от вмл DoQuestCheckDelay("Union_with_Escadra_End", 0.5);
            return; // только помощь эскадре - город их
		}
        sTemp = sld.City;
		if (sti(sld.nation) == PIRATE) // мятеж подавлен    // TODO
        {
			if (CheckAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp))
			{ // квестовый захват пиратов
				if (sti(PChar.GenQuestFort.ResidenceQuest.(sTemp).MayorOff) == true)
				{   // считаем, что мэр есть
                    Builder = characterFromID(sld.City + "_Mayor");
					LAi_LoginInCaptureTown(Builder, false);
                    if (!isCityHasFort(Builder.City))
		            {
		                Pchar.quest.FreeCaptureForts_Land.win_condition.l1          = "location";
		        	    Pchar.quest.FreeCaptureForts_Land.win_condition.l1.location = Builder.Default.BoardLocation;
		        	    Pchar.quest.FreeCaptureForts_Land.win_condition             = "FreeCaptureForts";
		            }
					LogoffCharacter(Builder);
				}
				if (CheckAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp + ".method"))
				{
                    sMethod = PChar.GenQuestFort.ResidenceQuest.(sTemp).method;
					call sMethod();
				}
				DeleteAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp);
				return;
			}
			if (pchar.questTemp.State != "Sp5LaVegaAttack_AttackLaVega")
			{
				// Исп. линейка - это должно вызоваться позже
			    AfterTownBattle();  // все, все свободны
			}

			//AddQuestRecord("tales_" + sld.City, "6");
			//sTemp = "Enable_Gover_" + sld.City;
            //pchar.GenQuestFort.(sTemp) = "1";

            //Pchar.GenQuestFort.MunityCharacterIdx = sld.index;
            //DoQuestCheckDelay("LaunchMunityCapture", 1.0);

            //Log_Info("Мятеж в городе " + GetCityName(sld.City) + " подавлен.");
            SetCaptureTownByHero(sld.City);
            Statistic_AddValue(Pchar, NationShortName(sti(sld.nation)) + "_TakeTown", 1);
            Achievement_AddStats_SturmColonies();
        }
        else
        {  // город нации
			// перехват по квестам
			Builder = characterFromID(sld.City + "_Mayor");
			if (CheckAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp))
			{
				if (sti(PChar.GenQuestFort.ResidenceQuest.(sTemp).MayorOff) == false)
				{
					// диалог только тут меняем, если раньше свалим - мэр на месте
					//Builder.Dialog.Filename    = "Capture_Gover_dialog.c";
					// в к3 на месте диалог будет
                    Builder.dialog.CurrentNode = "CAPTURE_Main";
					LAi_SetImmortal(Builder, true);
					chrDisableReloadToLocation = true;
				}
				else
				{
                    LAi_LoginInCaptureTown(Builder, false);
                    if (!isCityHasFort(Builder.City))
		            {
		                Pchar.quest.FreeCaptureForts_Land.win_condition.l1          = "location";
		        	    Pchar.quest.FreeCaptureForts_Land.win_condition.l1.location = Builder.Default.BoardLocation;
		        	    Pchar.quest.FreeCaptureForts_Land.win_condition             = "FreeCaptureForts";
		            }
					LogoffCharacter(Builder);
				}
				if (CheckAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp + ".method"))
				{
                    sMethod = PChar.GenQuestFort.ResidenceQuest.(sTemp).method;
					call sMethod();
				}
				DeleteAttribute(PChar, "GenQuestFort.ResidenceQuest." + sTemp);
				return;
			}
			else
			{
				//Builder.Dialog.Filename    = "Capture_Gover_dialog.c";
                
				LAi_SetImmortal(Builder, true);
				if(HasSubStr(Builder.greeting, "gov_common")) Builder.greeting = "mayor_capture";
				chrDisableReloadToLocation = true;
				if (!isCityHasFort(Builder.City))   // вернуть жителей
	            {
	                Pchar.quest.FreeCaptureForts_Land.win_condition.l1          = "location";
	        	    Pchar.quest.FreeCaptureForts_Land.win_condition.l1.location = Builder.Default.BoardLocation;
	        	    Pchar.quest.FreeCaptureForts_Land.win_condition             = "FreeCaptureForts";
	            }
			}

			// AlexBlade - вместо недобитков, 2-3 гвардейца на десерт
			j = 2 + rand(1);
			natEsc = sti(sld.nation);
			for (i = 0; i < j; i++)
			{
				sld = SetFantomDefenceForts("goto", "", natEsc, "TOWN_BATTLE_SOLDIERS", "guard");
				SetFantomParamHunter(sld); //крутые парни
				if (bDefenderHpBonus) AddCharHP(sld, makeint(stf(sld.chr_ai.hp_max) / 10));
			}
			Pchar.GenQuestFort.TownCrew = 0;
			// натравим
			LAi_group_SetHearRadius("TOWN_BATTLE_SOLDIERS", 100.0);
			LAi_group_FightGroupsEx("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			LAi_group_SetRelation("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

			LAi_group_SetCheck("TOWN_BATTLE_SOLDIERS", "FightInTown_Finish");
			LAi_LocationFightDisable(&Locations[FindLocation(Pchar.location)], false);
			LAi_SetFightMode(Pchar, true);
        }
    }
    else
    {   // не резиденция - ворота или порт
		if (sti(Pchar.GenQuestFort.TownCrew) <= 0)
		{
			return;
		}
		
		// если есть враги
		bDisableFastReload = true;
		// враги
		if (CheckAttribute(pchar, "quest.Enemy_" + sld.City))
		{  // сухопутный город
		   natEsc = sti(sld.Default.nation);
		}
		else
		{
		   natEsc = sti(sld.nation);
		}
		Pchar.GenQuestFort.FarLocator = true;
		sTemp = LAi_FindNPCLocator("rld");
		
		// AlexBlade - грузим доп. челиков: членов орденов и коменданта тюрьмы
		if (loadedLocation.type == "town")
		{
			// комендант
			SetFantomDefenceForts("goto", "", natEsc, "TOWN_BATTLE_SOLDIERS", "town_off");
			
			bool areEliteLoading = false;
			switch(loadedLocation.id)
			{
				case "FortFrance_town": //Мальтийцы
					if(GetCityNation("FortFrance_town") == FRANCE) areEliteLoading = true;
				break;
				case "Santiago_town": //Стража Инквизиции
					if(GetCityNation("Santiago") == SPAIN) areEliteLoading = true;
				break;
				case "Villemstad_town": //Охрана ГВИК
					if(GetCityNation("Villemstad") == HOLLAND) areEliteLoading = true;
				break;
				case "PortRoyal_town": //Хайлендеры (Элитные стрелки Шотландцы)
					if(GetCityNation("PortRoyal") == ENGLAND) areEliteLoading = true;
				break;
			}
			if (areEliteLoading)
			{
				int elitesCount = 2 + rand(1);
				for (i = 0; i < elitesCount; i++)
				{
					sld = SetFantomDefenceForts("goto", "", natEsc, "TOWN_BATTLE_SOLDIERS", "elite");
					SetFantomParamHunter(sld); //крутые парни
					if (bDefenderHpBonus) AddCharHP(sld, makeint(stf(sld.chr_ai.hp_max) / 10));
				}
			}
		}
		
		int townDefendersMax = MAX_TOWN_CREW + MAX_TOWN_MUSHKETER;
		int everyNextMushNumber = MAX_TOWN_CREW / MAX_TOWN_MUSHKETER;
		for (i = 1; i <= townDefendersMax; i++)
		{
			if (sti(Pchar.GenQuestFort.TownCrew) < 1) break;

			if (i % everyNextMushNumber == 0) //вражеские мушкетеры
			{
				sld = SetFantomDefenceForts("rld", sTemp, natEsc, "TOWN_BATTLE_SOLDIERS", "town_mush");

			}
			else
			{
				sld = SetFantomDefenceForts("rld", sTemp, natEsc, "TOWN_BATTLE_SOLDIERS", "town");
			}
			if (bDefenderHpBonus) AddCharHP(sld, makeint(stf(sld.chr_ai.hp_max) / 10));

			if (sld.location.locator == "") break;
			Pchar.GenQuestFort.TownCrew = sti(Pchar.GenQuestFort.TownCrew) - 1;
			chrDisableReloadToLocation = true; // не везде есть локаторы
		}
		
		if (chrDisableReloadToLocation)
		{
			// наши
			Pchar.GenQuestFort.FarLocator = false;
			sTemp = LAi_FindNPCLocator("rld");
			string  ani;
			bool bOurHasMush = true;
			if (CheckAttribute(pchar, "questTemp.Ascold") && pchar.questTemp.Ascold == "Ascold_ImMummy")
			{
				bOurHasMush = false;
				townDefendersMax = 13;
			}

			for (i = 1; i <= townDefendersMax; i++)
			{
				if (sti(Pchar.GenQuestFort.PlayerCrew) < 1)
					break;
				
				if (bOurHasMush && i % everyNextMushNumber == 0) //наши мушкетеры
				{
					sModel = LAi_GetBoardingMushketerModel(Pchar);
					sld = GetCharacter(NPC_GenerateCharacter("GenChar_", sModel, "man", "mushketer", 5, sti(pchar.nation), 0, false));
					sld.id = "GenChar_" + sld.index;
					LAi_NoRebirthEnable(sld); //не показывать убитых при входе в локацию
					LAi_LoginInCaptureTown(sld, true); // для записи игры
					sld.OurMan = true;
					CalculateAppropriateSkills(sld);
					SetFantomHP(sld);
					DeleteAttribute(sld, "OurMan");
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					ChangeCharacterAddressGroup(sld, loadedLocation.id, "rld", sTemp);
				}
				else
				{	// boal 08.01.05 патент влияет
					smodel = LAi_GetBoardingModel(GetMainCharacter(), &ani);
					sld = LAi_CreateFantomCharacterEx(smodel, ani, "rld", sTemp);
					if (sld.location.locator != "")
					{
						SetFantomParam(sld);
						LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
						LAi_LoginInCaptureTown(sld, true); // для записи игры
					}
				}
				if (CheckOfficersPerk(pchar, "Prevention")) // KZ > работа перка "Профилактика" - увеличивает общее здоровье абордажной команды на 10% во время сражения
					AddCharHP(sld, makeint(stf(sld.chr_ai.hp_max) * 0.1));
				Pchar.GenQuestFort.PlayerCrew = sti(Pchar.GenQuestFort.PlayerCrew) - 1;
			}
			
			// помощь эскадре
			if (CheckQuestAttribute("Union_with_Escadra", "Yes") && CheckAttribute(aData, "Colony") && snCity == aData.Colony) //fix homo
			{

				natEsc = sti(aData.nation); // homo
				//sti(Characters[GetCharacterIndex("NatCapitan_1")].nation);

				for (i = 0; i < MAX_ESCADRA_CREW; i++) //всегда 5 даем
				{
					// SetFantomDefenceLocal("rld", sTemp, natEsc, LAI_GROUP_PLAYER);
					// AlexBlade - Сделаем тут морпехов
					SetFantomDefenceLocal_ExType("rld", sTemp, natEsc, LAI_GROUP_PLAYER, "navy");
				}
			}
			Pchar.GenQuestFort.FarLocator = true;
			// натравим
			LAi_group_SetHearRadius("TOWN_BATTLE_SOLDIERS", 100.0);
			LAi_group_FightGroupsEx("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			LAi_group_SetRelation("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

			LAi_group_SetCheck("TOWN_BATTLE_SOLDIERS", "FightInTown_OpenNext");

			LAi_SetFightMode(Pchar, true);
        }
    }
}

void TWN_FightInTown_OpenNext()
{
    ref sld, Builder;
    int j, i, natEsc;
    string sTemp, snCity;
    float fTemp;
    aref aData;  //  homo
    makearef(aData, NullCharacter.Siege);   // homo
    
	sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
	snCity = sld.City;
    if (CheckAttribute(pchar, "quest.Enemy_" + sld.City))
    {// конец сухопутной боевки
        TWN_End_Siege_Any(sld.City);
        AfterTownBattle();  // все, все свободны
        SetLocationCapturedState(sld.Default, false);
    }
    chrDisableReloadToLocation = false;
    LAi_SetFightMode(Pchar, false);
    Log_Info(StringFromKey("InfoMessages_90"));
    PlaySound("DoorLocked");
    // подсчет живых матросов
    Log_TestInfo("Old boarding_player_crew: " + Pchar.GenQuestFort.PlayerCrew);
    for(i = 0; i < LAi_numloginedcharacters; i++)
	{
		j = LAi_loginedcharacters[i];
		if(j >= 0)
		{
			if(j != GetMainCharacterIndex())
			{
				sld = &Characters[j];
				if(LAi_IsDead(sld) == false && !IsOfficer(sld) && sld.model.animation != "mushketer") // не нужны офицеры для матросов
				{
					if (sld.chr_ai.group == LAI_GROUP_PLAYER)
					{
						Pchar.GenQuestFort.PlayerCrew = sti(Pchar.GenQuestFort.PlayerCrew) + 1;
					}
				}
			}
		}
	}
	if (CheckQuestAttribute("Union_with_Escadra", "Yes") && CheckAttribute(aData, "Colony") && snCity == aData.Colony ) //fix homo
    {
        Pchar.GenQuestFort.PlayerCrew = sti(Pchar.GenQuestFort.PlayerCrew) - MAX_ESCADRA_CREW; //всегда 5 даем
    }
    Log_TestInfo("New boarding_player_crew: " + Pchar.GenQuestFort.PlayerCrew);
    Log_TestInfo("New TownCrew: " + Pchar.GenQuestFort.TownCrew);
    // вернём живых на корабль -->
	fTemp = stf(Pchar.GenQuestFort.PlayerCrew) * stf(Pchar.GenQuestFort.PlayerCrew_per_char); // живые
	i     = makeint((stf(Pchar.GenQuestFort.PlayerCrew_Start) - fTemp) /1.5 + 0.5); // трупы
	// это после резиденции RemoveCharacterGoodsSelf(Pchar, GOOD_WEAPON, i);
	i = sti(Pchar.GenQuestFort.PlayerCrew_Start) - i; // выжившие с бонусом
	SetCrewQuantityOverMax(Pchar, i);
	// вернём живых на корабль <--
	if (loadedLocation.type != "residence" && CheckAttribute(&TEV, "LootCollector.Mode"))
	{
		if (sti(TEV.LootCollector.Mode) == 3)
		{
			TEV.LootCollector.Transfer = "1";
			Log_Info(StringFromKey("InfoMessages_72"));
			Log_Info(StringFromKey("InfoMessages_73"));
			LootCollectorTransferItemsToShip(false);
			PlaySound("Notebook_1");
			//PlaySound("Gotcha");
		}
		else
		{
			DeleteAttribute(&TEV, "LootCollector.Transfer");
			TEV.LootCollector.CanBeRun = true;
			if (sti(TEV.LootCollector.Mode) == 2)
			{
				LootCollector();
				//PlaySound("Gotcha");
			}
			else
			{
				if (sti(TEV.LootCollector.Mode) == 1)
					Log_Info(StringFromKey("InfoMessages_74"));
			}
		}
	}
}

void TWN_Residence_Captured_Any()
{
    ref sld, Builder;
    int j, i, natEsc;
    string sTemp;
    float fTemp;
    
	Lai_SetPlayerType(pchar);
    DoQuestCheckDelay("CapturedToOurCity", 1.5);

    sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Builder = characterFromID(sld.City + "_Mayor");
    if (Builder.location.group == "sit")
    {// сидит гад!
        LAi_SetHuberStayTypeNoGroup(Builder);
		PlaceCharacter(Builder, "goto", pchar.location);
    }
    sld = GetOurSailor("OurSailorForArest");
    sld.location = "none"; //fix
    LAi_LoginInCaptureTown(sld, true);

    if (PlaceCharacter(sld, "reload", pchar.location) != "")
    {
        chrDisableReloadToLocation = true; // чтоб ГГ не свалил до ухода
    }
    else
    {
        Builder.location = "none";
    }

    LAi_SetActorType(sld);
    LAi_ActorFollow(sld, Builder, "Residence_Captured_Any_02", 7.0);
}

void TWN_Residence_Captured_Any_02()
{
    ref sld, Builder;
    int j, i, natEsc;
    string sTemp;
    float fTemp;
    
	sTemp = "reload1"; //LAi_FindRandomLocator("reload");
	LAi_ActorRunToLocation(characterFromID("OurSailorForArest"), "reload", sTemp, "none", "", "", "", 7.0);

    sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Builder = characterFromID(sld.City + "_Mayor");
    LAi_SetActorType(Builder);
    if (CheckAttribute(sld, "Default.Prison"))
    {  // есть тюрма
    	LAi_ActorRunToLocation(Builder, "reload", sTemp, sld.Default.Prison, "goto", "goto9", "Back_Mayor_Type", 7.0);  // TODO
    }
    else
    {
        LAi_ActorRunToLocation(Builder, "reload", sTemp, "none", "", "", "Back_Mayor_Type", 7.0);
    }
}

void TWN_Back_Mayor_Type()
{
    ref sld, Builder;
    int j, i, natEsc;
    string sTemp;
    float fTemp;
    
	sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Builder = characterFromID(sld.City + "_Mayor");
    chrDisableReloadToLocation = false;
	LAi_SetHuberStayTypeNoGroup(Builder);
    LAi_SetImmortal(Builder, false);
    if (!CheckAttribute(sld, "Default.Prison"))
    { // тут анимация казни
    }
}

void TWN_ExitForPay() // мэр даёт откуп - табличка прибыли
{
    ref sld, Builder;
    
    sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
    Builder = characterFromID(sld.City + "_Mayor");
    LAi_SetImmortal(Builder, false);

	ResetSoundBoarding();
	StopMusic();
	KZ|Random("Action\Battle\Victory");

    int nBooty, iTest = FindColony(sld.City); // город
    ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	chrDisableReloadToLocation = false;
	ClearIslandShips(sld.City); // убрать корабли в порту, сбегли

	if (CheckAttribute(Pchar, "HalfOfPaymentByCity"))
	{
        nBooty = 700;
		DeleteAttribute(Pchar, "HalfOfPaymentByCity");
		SetNull2StoreManPart(rColony, 6.0);
	}
	else
	{
        nBooty = 2000;
		SetNull2StoreManPart(rColony, 3.0);
	}
	if (CheckAttribute(rColony, "FortValue"))
	{
		AddMoneyToCharacter(pchar, (sti(rColony.FortValue) + rand(10)) * nBooty);
	}
	else
	{
	    AddMoneyToCharacter(pchar, (20 + rand(10)) * nBooty);
	}
	LaunchColonyCapture(rColony);
}

//Для любой страны захват форта
// SetAllTownNation старый
void SetCaptureTownByNation(string sColony, int iNation)
{
	ref  rChar;
	int  j;
	int iColony = FindColony(sColony);

    // табличка
    pchar.GenQuest.CapturedCity  = sColony;
	pchar.GenQuest.CaptureNation = iNation;
	
    string sGroup;
	sGroup = GetNationNameByType(iNation) + "_CITIZENS";
	
    for (j=0; j< MAX_CHARACTERS; j++)
    {
        rChar = GetCharacter(j);

        if(CheckAttribute(rChar, "city") && rChar.City == sColony)
        {
            if (CheckAttribute(rChar, "CityType")) // фантом
        	{
        	    rChar.LifeDay = 0; // трем
        	}
        	rChar.nation = iNation;
        	LAi_group_MoveCharacter(rChar, sGroup);
			if (rChar.id == (sColony + "_Mayor"))
			{
			    // мэр есть
	          	if (iNation != PIRATE)
			    {
			        rChar.Default.nation = iNation; // они потом выкуп будут просить и корабди присылать
			    }
	        	SetTownMayor(rChar, iNation); // новый мэр
				TEV.oldMayor = rChar.id;
				pchar.quest.NewMayorName.win_condition.l1 = "ExitFromLocation";
				pchar.quest.NewMayorName.win_condition.l1.location = pchar.location;
				pchar.quest.NewMayorName.win_condition = "NewMayorName";
	        }
	        if (rChar.id == (sColony + " Fort Commander"))
			{
			    // фортовый коммандер
	          	if (iNation != PIRATE)
			    {
			        rChar.Default.nation = iNation; // они потом выкуп будут просить и корабди присылать
			    }
			    SetTownOfficForts(rChar, iNation);
	        }
        }
    }
    if (!CheckAttribute(Pchar, "questTemp.DontNullDeposit"))
    {
	    SetNull2Deposit(sColony); // нулим, если берут  не ГГ
	    SetNull2StoreMan(&Colonies[iColony]); // нулим магазин при захвате города эскадрой
    }
    else
    {
        DeleteAttribute(PChar, "questTemp.DontNullDeposit");
    }
    ClearIslandShips(sColony); // убрать корабли в порту, сбегли
	// флаг на карте
	sColony = sColony + "_town";
	worldMap.labels.(sColony).icon = iNation;
	if (IsEntity(&worldmap))
	{
	    SendMessage(&worldMap,"l",MSG_WORLDMAP_UPDATE_LABELS);
	}
	AddFortNation(sti(Colonies[iColony].nation), -1);
	j = sti(Colonies[iColony].nation);
 	AddFortNation(iNation, 1);
    Colonies[iColony].nation = iNation;
    Move_Govenour_Nation(j); // переселяем губера нации, которая была если паузы мира нет
	if (CheckAttribute(&Colonies[iColony], "OfficerIdx"))
	{
		if(Colonies[iColony].isBought == false) // TODO: вариант при мятеже
		{ // убиваем наместника, если был во время захвата
			rChar = GetCharacter(sti(Colonies[iColony].OfficerIdx));
			rChar.location = "none";
			rChar.LifeDay = 0;
			DeleteAttribute(&Colonies[iColony], "OfficerIdx");
		}
		else
		{ // наместника на прогулку, если передали колонию
			rChar = GetCharacter(sti(Colonies[iColony].OfficerIdx));
			log_setstringtolog(XI_ConvertString("Officer") + " " + rChar.name + " " + rChar.lastname + XI_ConvertString("wait you") + XI_ConvertString("colony" + Colonies[iColony].id + "Pre") + ".");
			rChar.walker = true; // флаг для диалога
			rChar.Dialog.CurrentNode = "Hired";
			LAi_SetImmortal(rChar, false);
			LAi_SetCitizenTypeNoGroup(rChar);
			LAi_SetLoginTime(rChar, 6.0, 21.99);
			PlaceCharacter(rChar, "goto", Colonies[iColony].id + "_town");
			DeleteAttribute(&Colonies[iColony], "OfficerIdx");
		}
	}
	if (sti(Colonies[iColony].HeroOwn) == true)
	{
    	Colonies[iColony].HeroOwn = false; // все, это не наш город
		if(Colonies[iColony].id == "Villemstad") VillemstadResGatesLock();
    	if(Colonies[iColony].isBought == false)
		{
			if (!CheckAttribute(pchar, "questTemp.State") || pchar.questTemp.State != "Sp5LaVegaAttack_WeWon") //fix
			{
				// СЖ
				sGroup =  GetNationNameByType(iNation);
				ReOpenQuestHeader("Gen_CityCapture");
				AddQuestRecord("Gen_CityCapture", "t4");
				AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + Colonies[iColony].id));
				AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sGroup + "Gen"));
			}
		}
    }
 	if (iNation != PIRATE)
 	{
    	Colonies[iColony].isBought = false; // если мятеж, то не сбросится
    }
    SaveCurrentNpcQuestDateParam(&Colonies[iColony], "CaptureDate");
}


//Если мы захватываем
//void SetAllTownOurCity(ref FortCrefM) - аналог в вмл
void SetCaptureTownByHero(string sColony)
{
    ref  rChar;
	int  j;
	int iColony = FindColony(sColony);
    int iNation = PIRATE;

    // табличка
    pchar.GenQuest.CapturedCity  = sColony;
	pchar.GenQuest.CaptureNation = iNation;

    for (j=0; j< MAX_CHARACTERS; j++)
    {
        rChar = GetCharacter(j);

        if(CheckAttribute(rChar, "city") && rChar.City == sColony)
        {
            if (rChar.id != (sColony + "_Mayor"))  // мэр в тюряге, его не трогаем
			{
			    if (CheckAttribute(rChar, "CityType")) // фантом
	        	{
	        	    rChar.LifeDay = 0; // трем
	        	}
	        	rChar.nation = iNation;
	        	LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER_OWN);

		        if (rChar.id == (sColony + " Fort Commander"))
				{
				    SetTownOurOfficForts(rChar); // модель и отношения
		        }
	        }
			else
			{
			    LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER_OWN);
			}
        }
    }
    ClearIslandShips(sColony); // убрать корабли в порту, сбегли
	// флаг на карте
	sColony = sColony + "_town";
	worldMap.labels.(sColony).icon = iNation;
	if (IsEntity(&worldmap))
	{
	    SendMessage(&worldMap,"l",MSG_WORLDMAP_UPDATE_LABELS);
	}
	AddFortNation(sti(Colonies[iColony].nation), -1);
	j = sti(Colonies[iColony].nation);
 	AddFortNation(iNation, 1);
    Colonies[iColony].nation = iNation;
    Move_Govenour_Nation(j); // переселяем губера нации, которая была если паузы мира нет
    Colonies[iColony].HeroOwn = true;
    // выкупленность города не меняем, тк отбив от мятежа дело ГГ
    SaveCurrentNpcQuestDateParam(&Colonies[iColony], "CaptureDate");
}


//меняем модель мэра
void SetTownMayor(ref Ch, int natGover)
{
    string rmodel;

	if (natGover == PIRATE)
	{
	    // Когда берут пираты - а это только мятеж, мэра менять не нужно
        rmodel = Ch.model;
	}
	else
	{
		if (Environment.date.year == 1665 && Environment.date.month == 1 && Environment.date.day == 1)
		{
			rmodel = Ch.model;  //Оставляем уникальную модельку стартовым мэрам 
		}
		else
		{
			if(rand(30) <= 14) rmodel = "usurer_"+(rand(14)+1);
			else rmodel = "portman_"+(rand(15)+1);
		}
	}

    if (natGover != PIRATE) // как сидел мэр в тюрме так и будет сидеть... диалог старый + мордобой.
    {
		if(CheckAttribute(Ch, "Sp5LaVegaAttackDone")) //Капитан Купер RIP
		{
			DeleteAttribute(Ch, "Sp5LaVegaAttackDone");
			Ch.greeting = NationShortName(sti(Ch.nation)) + "_gov_common";
		}
		
 		// не сбивать имена нужных мэров
		if (!CheckAttribute(Ch, "name"))
		{       
			SetRandomNameToCharacter(Ch);
		}
        Ch.model = rmodel;
        FaceMaker(Ch);
        Ch.quest.meeting = 0; // типа первый раз знакомимся
        if (!CheckAttribute(pchar, "questTemp.DontSetNewDialogToMayor"))
        {
            Ch.dialog.currentnode = "First time"; // диалог на ноль
        }
		// он был в тюрме - на место
		LAi_SetCurHPMax(Ch); // восстановим, если расстрелян
		ReturnMayorPosition(Ch);
		LAi_LoginInCaptureTown(Ch, false);
    }
}
// мэра на место, если был в тюряге или скрыт
void ReturnMayorPosition(ref Ch)
{
	Ch.location = Ch.City + "_townhall";
	Ch.location.group   = "sit";
	Ch.location.locator = "sit1";
	LAi_SetHuberTypeNoGroup(Ch);
}

//Добавить форт к нации  (не работает, в осадах расчёт по факту)
int AddFortNation(int nation,int fort)
{
	int newfort = sti(Nations[nation].fort) + fort;
	if(newfort<0) newfort=0;
	Nations[nation].fort = newfort;
	return newfort;
}

// boal переселение губернатора -->
void Move_Govenour()
{
    int iNation = rand(4);

    if (bWorldAlivePause) return;

    while (iNation == PIRATE)
    {
        iNation = rand(4);
    }
    // нацию нашли  <--
    Move_Govenour_Nation(iNation);
}
void Move_Govenour_Nation(int iNation)
{
    ref rChar;
    if (bWorldAlivePause) return;

    if (iNation != PIRATE)
    {
    	rChar = CharacterFromID(NationShortName(iNation)+"_guber");  // губер

		if (CheckAttribute(rChar, "notMoveAble")) return; //проверяем личный флаг губернатора на переезд

        ref ch;
    	int i, iChar;
        int storeGover[40];
        int howGover = 0;

        for (i=0; i<MAX_COLONIES; i++)
		{
			if (colonies[i].nation == "none") continue; // необитайки

			// добавить проверку на пиратов, у них нет фортов, нафиг им коммандер?
			if (CheckAttribute(&colonies[i], "HasNoFort"))  continue;
			
			// проверим базовых мэров городов
			iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
			if (iChar != -1)
			{   // мэр есть, значит есть резиденция
			    if (sti(colonies[i].nation) == iNation) // если город нации, то мэр не в тюрме
			    {
			        storeGover[howGover] = i; // индекс города
                	howGover++;
			    }
	        }
		}

        if (howGover > 0) // иначе нечего делать - один город остался
        {
			i = storeGover[rand(howGover-1)];
            SetGovenourToCity(iNation, colonies[i].id);
        }
        else
        {// труба делу - городов с фортами больше нет, губера прячем
            if (CheckAttribute(rChar, "CityToStay")) // где был
			{
		        i = GetCharacterIndex(rChar.CityToStay + "_Mayor");  // старого мэра на место
		        if (characters[i].location == rChar.location)
		        {   //если он ещё в резиденции, а не в тюрьме
		            characters[i].location.group = "sit";
					characters[i].location.locator = "sit1";
					LAi_SetHuberTypeNoGroup(&characters[i]);
				}
			}
			rChar.location = "none";
			DeleteAttribute(rChar, "CityToStay");
        }
    }
}
// метод для рассидки и пересидки губера ручками и в начале игры
void SetGovenourToCity(int iNation, string sCity)
{
    ref     rChar;
    int     iChar, i2;
    
    rChar = CharacterFromID(NationShortName(iNation) + "_guber");  // губер
    
    iChar = GetCharacterIndex(sCity + "_Mayor");  // куда
	
	if (CheckAttribute(rChar, "CityToStay") && rChar.CityToStay != "Villemstad") // где был
	{
        i2 = GetCharacterIndex(rChar.CityToStay + "_Mayor");  // старого мэра на место
        if (characters[i2].location == rChar.location)
        {   //если он ещё в резиденции, а не в тюрьме
            characters[i2].location.group = "sit";
			characters[i2].location.locator = "sit1";
			LAi_SetHuberTypeNoGroup(&characters[i2]);
		}
	}
 	rChar.location = characters[iChar].location;
	if(sCity == "Villemstad") rChar.location = "Villemstad_townhall2";
	rChar.CityToStay = characters[iChar].City;
	rChar.location.group = "sit";
	rChar.location.locator = "sit1";
	LAi_SetHuberTypeNoGroup(rChar);
	
	if(sCity != "Villemstad")
	{
		characters[iChar].location.group = "goto";
		characters[iChar].location.locator = "governor1";
		LAi_SetHuberStayTypeNoGroup(&characters[iChar]);
	}
}
// boal переселение губернатора <--

//Меняем модель коменданта форта и отношение к нам
void SetTownOurOfficForts(ref ChOff)
{
    // сухопутные города
	if (CheckAttribute(ChOff, "Mayor")) return; // сам себе командир (виртуальный форт)

    SetCaptanModelByEncType(ChOff, "pirate");
    SetCharacterRelationAsOtherCharacter(sti(ChOff.index), GetMainCharacterIndex());
    SetCharacterRelation(sti(ChOff.index),GetMainCharacterIndex(),RELATION_FRIEND);
    UpdateRelations();
}

//Меняем модель коменданта форта
void SetTownOfficForts(ref ChOf, int fnat)
{
	// сухопутные города
	if (CheckAttribute(ChOf, "Mayor")) return; // сам себе командир (виртуальный форт)

    SetCaptanModelByEncType(ChOf, "war");
    // отношения как у губера нации
	if (fnat != PIRATE)
	{
	    ref govenour = CharacterFromID(NationShortName(fnat)+"_guber"); // пираты не захватывают города сами.
	    SetCharacterRelationAsOtherCharacter(sti(ChOf.index), sti(govenour.index));
    }
    else
    {
        SetCharacterRelationAsOtherCharacter(sti(ChOf.index), -1);
    }
    /*   TODO тут нации сторожевиков
    */
}
///////////////////////////////////////////////////////////   ОТБИВ ГОРОДА //////////////////////////////////
//  прерывания
// "Attack_Fort_" + city - начало осады, таймер, отработает TWN_Siege_Any
// "End_Siege_" + city; - прерывание на убивание эскадры, отработает  TWN_End_Siege_Any, для сухопутных нет, сразу метод
// "LandBattleStart_For_" + city - на локацию, начало сухопутной боевки у ворот
//  "Enemy_" + city - конец не снятой осады, город у ГГ забрать, метод  TWN_Enemy_Any
// осада наших городов
void TWN_Siege_Any(string city)
{
    ref    sld, rCap;
    int    i, iDay;
    string sTemp, sGroup, sCapId, sAttr;

    city = PChar.Quest.(city).CityId; // реальный город
    
    if (!isCityHasFort(city)) // сухопутный город
    {
        TWN_SiegeLand_Any(city);
    }
    else
    {
	    sld = GetFortCommander(city);

	    Log_Info(StringFromKey("InfoMessages_91", GetCityName(city)));

	    sTemp = "Enemy_" + city;
	    iDay = 9 + rand(15);
	    SetTimerCondition(sTemp, 0, 0, iDay, false);
	    PChar.Quest.(sTemp).CityId   = city;
		PChar.Quest.(sTemp).function = "TWN_Enemy_Any";

		//  СЖ -->
		sTemp =  GetNationNameByType(sti(sld.Default.nation));
		ReOpenQuestHeader("Gen_CityCapture");
	    AddQuestRecord("Gen_CityCapture", "t5");
		AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(city));
		AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
		AddQuestUserData("Gen_CityCapture", "sDay", FindDaysString(iDay));
		//  СЖ <--

        sGroup = city + "Squadron";
	    Group_FindOrCreateGroup(sGroup);
	    sCapId = city + "CapSquadron_";
	    sTemp = "End_Siege_" + city;
        for (i = 1; i <= 6; i++)
	    {
	        rCap = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, sti(sld.Default.nation), iDay + 2, true));

	        SetShipSquadron(rCap, sti(sld.Default.nation));
	        SetFantomParamHunter(rCap); //крутые парни
	        SetCaptanModelByEncType(rCap, "war");
	        Group_AddCharacter(sGroup, sCapId + i);
	        rCap.AlwaysEnemy        = true; //всегда враг
	        SetCharacterRelationBoth(sti(rCap.index), GetMainCharacterIndex(), RELATION_ENEMY);
	        // прерывание
	        sAttr = "l" + i;
			Pchar.quest.(sTemp).win_condition.(sAttr) = "NPC_Death";
	        Pchar.quest.(sTemp).win_condition.(sAttr).character = sCapId + i;
	        
	        SetRandGeraldSail(rCap, sti(rCap.Nation));
	    }
        Pchar.quest.(sTemp).win_condition = sTemp;
	    PChar.Quest.(sTemp).CityId   = city;
		PChar.Quest.(sTemp).function = "TWN_End_Siege_Any";
		
	    Group_SetGroupCommander(sGroup, sCapId + "1");
	    Group_SetAddress(sGroup, sld.Default.Island, "Quest_ships", "reload_fort1_siege");
	    Group_SetTaskAttack(sGroup, PLAYER_GROUP);
	    
	    ClearIslandShips(city); // убрать корабли в порту
	    makeref(rCap, Colonies[FindColony(city)]);
    	rCap.DontSetShipInPort = true;
    	
    	if (!bQuestCheckProcessFreeze) // можно показать
		{
	        Pchar.GenQuestFort.ColonySiegeId   = city;
	        Pchar.GenQuestFort.ColonySiegeNation = sti(sld.Default.nation);
	        Pchar.GenQuestFort.ColonySiegeTime = iDay;
			PChar.GenQuest.CallFunctionParam = "LaunchColonyInfoScreen";
			DoQuestCheckDelay("CallFunctionParam", 1.5);
		}
	}
}
void SetShipSquadron(ref rChar, int iNation)
{
    int SiegeShips, hcrew;

    SiegeShips = GetShipTypeNational(2, 1, "War", iNation);	//ZhilyaevDm

    SetRandomNameToCharacter(rChar);
    SetRandomNameToShip(rChar);
    rChar.Ship.Type = GenerateShipExt(SiegeShips, 1, rChar);
    SetBaseShipData(rChar);
    hcrew = GetMaxCrewQuantity(rChar);
    SetCrewQuantity(rChar, hcrew);

    ShipOverhaul(rChar);

    Fantom_SetCannons(rChar, "war");
    Fantom_SetBalls(rChar, "war");
    Fantom_SetGoods(rChar, "war");
}
// отбились
void TWN_End_Siege_Any(string city)
{
    ref    sld, rColony;
    int    i;
    string sTemp, sAttr;

	if (CheckAttribute(PChar, "Quest." + city +".CityId")) // это прерывание
	{
    	city = PChar.Quest.(city).CityId; // реальный город
    } // иначе сухопутный, а там сразу город на входе

	sld = GetFortCommander(city);

 	//  СЖ -->
	sTemp =  GetNationNameByType(sti(sld.Default.nation));
	ReOpenQuestHeader("Gen_CityCapture");
	if (isCityHasFort(city)) // фортовой город
    {
    	// нулим капитанов - сами померли
        AddQuestRecord("Gen_CityCapture", "t6");
        makeref(rColony, Colonies[FindColony(city)]);
        DeleteAttribute(rColony, "DontSetShipInPort"); //возвращаем жизнь
	}
	else
	{
    	AddQuestRecord("Gen_CityCapture", "t6_1");
    }
	AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(city));
	AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
	//  СЖ <--
	
	sTemp   = "Enemy_" + city;
    Pchar.quest.(sTemp).over = "yes";

    sTemp = "Attack_Fort_" + city;
    SetTimerCondition(sTemp, 0, 0, 25 + rand(70), false);
    PChar.Quest.(sTemp).CityId   = city;
	PChar.Quest.(sTemp).function = "TWN_Siege_Any";
	
    Log_Info(StringFromKey("InfoMessages_93"));
}
///////////////////////////////
// сухопутная осада
void TWN_SiegeLand_Any(string city)
{
    ref    sld;
    int    i;
    string sTemp, sAttr;

    sld = GetFortCommander(city);

    Log_Info(StringFromKey("InfoMessages_91", GetCityName(city)));

    sTemp = "Enemy_" + city;
    i = 9 + rand(15);
    SetTimerCondition(sTemp, 0, 0, i, false);
    PChar.Quest.(sTemp).CityId   = city;
	PChar.Quest.(sTemp).function = "TWN_Enemy_Any";
	
	//  СЖ -->
	sTemp =  GetNationNameByType(sti(sld.Default.nation));
	ReOpenQuestHeader("Gen_CityCapture");
    AddQuestRecord("Gen_CityCapture", "t5_1");
	AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(city));
	AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
	AddQuestUserData("Gen_CityCapture", "sDay", FindDaysString(i));
	//  СЖ <--
	
	if (!bQuestCheckProcessFreeze) // можно показать
	{
        Pchar.GenQuestFort.ColonySiegeId   = city;
        Pchar.GenQuestFort.ColonySiegeNation = sti(sld.Default.nation);
        Pchar.GenQuestFort.ColonySiegeTime = i;
        
        PChar.GenQuest.CallFunctionParam = "LaunchColonyInfoScreen";
		DoQuestCheckDelay("CallFunctionParam", 1.5);
	}
			
    sTemp = "LandBattleStart_For_" + city;
	Pchar.quest.(sTemp).win_condition.l1          = "location";
    Pchar.quest.(sTemp).win_condition.l1.location = sld.Default.BoardLocation;
    Pchar.quest.(sTemp).win_condition             = sTemp;
    PChar.Quest.(sTemp).CityId   = city;
	PChar.Quest.(sTemp).function = "TWN_LandBattleStart_For_Any";
}

// начнём отбив города на суше после мятежа
void TWN_LandBattleStart_For_Any(string city)
{
    ref    sld;
    string sTemp;

    city = PChar.Quest.(city).CityId; // реальный город
    
    sld = GetFortCommander(city);

	Pchar.GenQuestFort.fortCharacterIdx = sld.index;

    DeleteQuestAttribute("Union_with_Escadra"); // TODO

    SetLocationCapturedState(sld.Default, true);

    if (CheckAttribute(pchar, "quest.Enemy_" + city))// уже в осаде
    {
        DoQuestCheckDelay("Capture_Town_Siege", 0.1); // боевка у ворот два раза!
    }
    else
    {
        DoQuestCheckDelay("Capture_Forts", 0.1); // мятеж
    }
}
// они захватили город
void TWN_Enemy_Any(string city)
{
    ref    sld, rColony;
    int    i;
    string sTemp, sAttr;

    city = PChar.Quest.(city).CityId; // реальный город
    sld = GetFortCommander(city);

    sTemp = "End_Siege_" + city;
	Pchar.quest.(sTemp).over               = "yes";
	sTemp = "Attack_Fort_" + city;
	Pchar.quest.(sTemp).over               = "yes";
	sTemp = "LandBattleStart_For_" + city;
	Pchar.quest.(sTemp).over               = "yes";

	// контрабандиста на место
	// сам в CreateHabitues будет

    SetCaptureTownByNation(city, sti(sld.Default.nation));
    // капитаны потрутся сами от времени, какое-то время будут тусить у форта

    if (!bQuestCheckProcessFreeze) // можно показать
	{
        Pchar.GenQuestFort.ColonySiegeId     = city;
        Pchar.GenQuestFort.ColonySiegeNation = sti(sld.Default.nation);
        Pchar.GenQuestFort.ColonySiegeEnd    = true;
		PChar.GenQuest.CallFunctionParam = "LaunchColonyInfoScreen";
		DoQuestCheckDelay("CallFunctionParam", 2.0);
	}
	Log_Info(StringFromKey("InfoMessages_92", GetCityName(city)));
	makeref(rColony, Colonies[FindColony(city)]);
    DeleteAttribute(rColony, "DontSetShipInPort"); //возвращаем жизнь
}

void TWN_RealeseForMoney(string city, bool _agent)
{
    string  sTemp;
    ref     sld, rColony;
    
	sTemp = "Attack_Fort_" + city;
	Pchar.quest.(sTemp).over               = "yes";
	sTemp = "End_Siege_" + city;
	Pchar.quest.(sTemp).over               = "yes";
	sTemp = "LandBattleStart_For_" + city;
	Pchar.quest.(sTemp).over               = "yes";
    sTemp   = "Enemy_" + city;
    Pchar.quest.(sTemp).over = "yes";
    // если корабли были, то они простоят ещё до конца срока и растают
    
	makeref(rColony, Colonies[FindColony(city)]);
	rColony.isBought = true;
	DeleteAttribute(rColony, "DontSetShipInPort"); //возвращаем жизнь
	
	if (_agent)
	{
		sld = GetFortCommander(city);
		//  СЖ -->
		sTemp =  GetNationNameByType(sti(sld.Default.nation));
		ReOpenQuestHeader("Gen_CityCapture");
	    AddQuestRecord("Gen_CityCapture", "t7");
		AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("","а"));
		AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(city));
		AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
		//  СЖ <--
		AddMoneyToCharacter(pchar, -TWN_CityCost(city));
	}
}

bool isHeroOwnCity(bool _isBoughtCare) // _isBoughtCare - true, то проверять проданность, если нет, то пофиг, просто город ГГ (для подарить)
{
	int i;

	for (i=0; i<MAX_COLONIES; i++)
	{
		if (sti(colonies[i].HeroOwn) == true)
		{
			if (!_isBoughtCare || sti(colonies[i].isBought) == false) return true;
		}
	}
	return false;
}

int TWN_CityCost(string city)
{
    ref     rColony;
    
	makeref(rColony, Colonies[FindColony(city)]);
	int money =  1000;
	if (CheckAttribute(rColony, "FortValue"))
	{
		money = (sti(rColony.FortValue) * 50000);
	}
	else
	{
	    money = (25 * 50000);
	}
	return money;
}

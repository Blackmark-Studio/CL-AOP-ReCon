// KZ > Максимум суток, на которые откладывается окончание осады, пока игрок находится рядом
#define SIEGE_MAX_END_DELAY		3

// > Вкл/выкл (1/0) отслеживание процесса осады (записи в system.log)
#define SIEGE_DEBUG				0

// > Стадии осады (aData.progress)
#define SIEGE_ST_APPROACH		0	// > эскадра идёт к колонии
#define SIEGE_ST_BATTLE			1	// > эскадра у колонии, осада идёт
#define SIEGE_ST_DONE			2	// > всё закончено и убрано

// > Порог "важности" колонии при решении оставить её себе
#define SIEGE_CAPTURE_PIVOT		60

// > Считать/нет (1/0) переход во внутренние помещения корабля уходом из акватории осаждаемой колонии (aData.island).
// > 0 - при любой смене локации = игрок покинул акваторию (ванильный вариант). Зайти в каюту или выслать шлюпку значит досрочно зафиксировать исход осады, а в последние сутки срока - получить её завершение прямо во время боя.
// > 1 - пока игрок в акватории осаждаемой колонии, он свободно может ходить по своему кораблю (каюта, палуба, трюм, кубрик) и высылать шлюпки на другие корабли.
#define SIEGE_PLAYER_CAN_VISIT_CABIN	1

// > Игрок сейчас в акватории острова осаждаемой колонии?
bool IsPlayerHoldingAtSiegeIsland()
{
    if (SIEGE_PLAYER_CAN_VISIT_CABIN != 1) return false;

    aref aData;
    makearef(aData, NullCharacter.Siege);
    if (!CheckAttribute(aData, "PlayerAtIsland")) return false;
    if (sti(aData.PlayerAtIsland) != 1) return false;

    return isShipInside(pchar.location);
}

// > Трассировка цикла осады
void SiegeTrace(string sText)
{
	if (SIEGE_DEBUG != 1) return;
    trace("SIEGE| " + GetQuestBookDataDigit() + " | " + sText);
}

// > Короткая сводка текущей осады (чтобы каждая строка лога была самодостаточной)
string SiegeTag()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    if (!CheckAttribute(aData, "colony")) return "[осады нет]";
    string s = "[" + aData.colony;
    if (CheckAttribute(aData, "nation"))   s = s + " <- " + NationShortName(sti(aData.nation));
    if (CheckAttribute(aData, "conation")) s = s + " (защ. " + NationShortName(sti(aData.conation)) + ")";
    if (CheckAttribute(aData, "progress")) s = s + " стадия=" + aData.progress;
    return s + "]";
}

// > Попытка настроить осаду для нации-жертвы iNation
bool TrySetupSiege(int iNation, string sLog)
{
    if (iNation == -1)
    {
        SiegeTrace("подбор цели: нация-жертва не задана (-1) - попытка отменена");
        return false;
    }

    int iColony = SelectColonyForSiege(iNation); // нация-жертва, сразу ищем город
    if (iColony == -1)
    {
        SiegeTrace("подбор цели: у нации " + NationShortName(iNation) + " нет подходящих колоний (форт/HeroOwn/квестовый запрет) - попытка отменена");
        return false;
    }

    int iAtaker = FindEnemyNation2NationWithoutPirates(iNation); // нашли - ищем атакера по врагу
    if (iAtaker == -1)
    {
        SiegeTrace("подбор цели: колония " + Colonies[iColony].id + " (" + NationShortName(iNation) + ") найдена, но у нации нет врагов-агрессоров - попытка отменена");
        return false;
    }

    aref aData; makearef(aData, NullCharacter.Siege);
    ref rColony; makeref(rColony, Colonies[iColony]);

    aData.nation   = iAtaker;
    aData.conation = sti(rColony.nation);
    aData.colony   = rColony.id;
    aData.island   = rColony.island;
    Log_TestInfo(sLog + iColony);
    SiegeTrace("ЦЕЛЬ ВЫБРАНА (" + sLog + "): " + NationShortName(iAtaker) + " идёт на " + rColony.id + " (нация " + NationShortName(sti(rColony.nation)) + ", остров " + rColony.island + ", форт " + rColony.FortValue + ", индекс колонии " + iColony + ")");
    return true;
}

bool PrepareSiege()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);

    // > Расклад колоний по нациям в пределах попыток не меняется, считать в каждой итерации ни к чему
    NationForceBalance(aData);
   
    int n, iMaxNation = func_max_pos(sti(aData.nation_0), sti(aData.nation_1), sti(aData.nation_2), sti(aData.nation_3));

    SiegeTrace("подготовка: колоний по нациям Eng=" + aData.nation_0 + " Fra=" + aData.nation_1 + " Spa=" + aData.nation_2 + " Hol=" + aData.nation_3 + " Pir=" + aData.nation_4 + "; самая крупная - " + NationShortName(iMaxNation) + "; до 10 попыток подбора");

    for (n = 0; n < 10; n++)
    {
        if (rand(100) <= 60) // 40 мало всё время испанские колонии осаждают причём одни и те же
        {
            // > Не выбирать пиратов жертвой
            if (TrySetupSiege(rand(PIRATE - 1), "рандом ")) return true;
        }
        else
        {
            // > Ищем жертву по максимальному числу колоний
            if (TrySetupSiege(iMaxNation, "мочим тех, у кого колоний много ")) return true;
        }
    }

    SiegeTrace("подготовка ПРОВАЛЕНА: за 10 попыток подходящая пара агрессор/жертва не найдена - осада не начнётся");
    return false;
}

int func_max_pos(int a, int b, int c, int d)
{
	if (a >= b && a >= c && a >= d) return 0;
	if (b >= a && b >= c && b >= d) return 1;
	if (c >= a && c >= b && c >= d) return 2;
	if (d >= a && d >= b && d >= c) return 3;

	return 0;
}

bool CheckQuestColonyList(string sColony)
{
	if (sColony == "Providencia") return false; //временно заблокируем
    if (sColony == "Maracaibo" && CheckAttribute(pchar, "questTemp.MaracaiboSiegeLock")) return false;
	
    if (CheckAttribute(pchar, "GenQuest.Intelligence.City" ) && pchar.GenQuest.Intelligence.City == sColony) return false;

    if (CheckAttribute(pchar, "GenQuest.Intelligence.MayorId"))
    {
        // > MayorId может устареть, чекаем
        int iMayor = GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId);
        if (iMayor != -1 && characters[iMayor].City == sColony) return false;
    }
        
    //fix не осаждать Барбадос по линейке Блада
    if (sColony == "Bridgetown" || sColony == "Tortuga")
    {
        if (CheckAttribute(pchar, "questTemp.CapBloodLine") && Pchar.questTemp.CapBloodLine == true) return false;
        if (GetGlobalTutor()) return false;
    }

    if (CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "EndOfQuestLine") return true;

    // > Атрибут этот заводится пустым на новой игре и не удаляется, отсюда sti(pchar.questTemp.NationQuest) = 0, а 0 - это всегда ENGLAND пока не взять нацлинейку.
    if (CheckAttribute(pchar, "questTemp.NationQuest") && pchar.questTemp.NationQuest != "")
    {
        switch(sti(pchar.questTemp.NationQuest))
        {
            case ENGLAND:
                if (sColony == "SentJons" || sColony == "Beliz"
                || sColony == "Villemstad" || sColony == "PortRoyal"
                || sColony == "SanJuan" || sColony == "LaVega"
                || sColony == "Havana" || sColony == "Santiago") return false;
            break;

            case FRANCE:
                // > Вместо города BasTer был указан остров Guadeloupe
                if (sColony == "FortFrance" || sColony == "Villemstad"
                || sColony == "Havana" || sColony == "BasTer"
                || sColony == "Cumana" || sColony == "Tortuga" || sColony == "PortPax") return false;
            break;
			
            case SPAIN:
                if (sColony == "PortRoyal" || sColony == "Santiago"
                || sColony == "Villemstad" || sColony == "Maracaibo"
                || sColony == "Tortuga" || sColony == "Panama"
                || sColony == "Cumana" || sColony == "LaVega"
                || sColony == "Havana" || sColony == "SentJons") return false;
            break;
			
            case HOLLAND:
                if (sColony == "Marigo" || sColony == "Villemstad"
                || sColony == "PortRoyal" || sColony == "LaVega"
                || sColony == "Cartahena" || sColony == "Tortuga") return false;
            break;
        }
    }
    return true;
}


void NationForceBalance(aref base)
{
    string nat;

    base.nation_0 = 0;
    base.nation_1 = 0;
    base.nation_2 = 0;
    base.nation_3 = 0;
    base.nation_4 = 0;

    for (int i=0; i<MAX_COLONIES; i++)
	{
        nat = "nation_"+sti(Colonies[i].nation);
        if (Colonies[i].nation != "none") base.(nat) = sti(base.(nat))+ 1;
	}
	Log_TestInfo("Eng = "+base.nation_0);
	Log_TestInfo("Fra = "+base.nation_1);
	Log_TestInfo("Spa = "+base.nation_2);
	Log_TestInfo("Hol = "+base.nation_3);
	Log_TestInfo("Pir = "+base.nation_4);
}

int SelectColonyForSiege(int ination)  // выбираем колонию для нападения
{
    // > Один проход по всем колониям с равномерным случайным выбором среди подходящих.
    // > Раньше было до 20 случайных попыток и могло вернуть -1, даже если подходящая колония существует.
    ref rAttakColony;
    int iChosen = -1;
    int iCount = 0;

    for (int i = 0; i < MAX_COLONIES; i++)
    {
        makeref(rAttakColony, Colonies[i]);

        if (sti(rAttakColony.nation) == ination && !CheckAttribute(rAttakColony, "HasNoFort") && CheckAttribute(rAttakColony, "FortValue") && sti(rAttakColony.HeroOwn) == false && CheckQuestColonyList(rAttakColony.id))
        {
            iCount++;

            if (rand(iCount - 1) == 0)
				iChosen = i;
        }
    }

    if (iChosen == -1) SiegeTrace("выбор колонии: у " + NationShortName(ination) + " подходящих колоний нет (0 кандидатов)");
    else SiegeTrace("выбор колонии: у " + NationShortName(ination) + " кандидатов " + iCount + ", выбрана " + Colonies[iChosen].id);

    return iChosen;
}

void BeginSiegeMap(string sChar)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    SiegeRumourEx(StringFromKey("Common_rumours_155", NationNameSK(sti(aData.nation))), aData.Colony, sti(aData.nation)+10, -1, 2, 1, "citizen,habitue,trader,tavern");
    int idist = makeint(GetDistanceToColony(aData.Colony));
    SiegeTrace("ЭТАП 2/8 ПОДХОД: дистанция игрока до " + aData.Colony + " = " + idist + " (порог 100)");

    if (idist != -1 && idist <= 100 )
    {
        Log_TestInfo("Squadron on the map!");
        SiegeTrace("игрок рядом - эскадра " + sChar + " пойдёт видимым энкаунтером по глобальной карте, срок хода 1 сут");
        Map_CreateTrader("none", aData.Colony, sChar, 1);
    }
    else
    {
        Log_TestInfo("Squadron on the Timer");
        SiegeTrace("игрок далеко - эскадра дойдёт незаметно, только по таймеру");
    }

    // > Таймер ставится всегда
    string sQuest = "BattleOfTheColony";
    SetTimerCondition(sQuest, 0, 0, 2, false);
    pchar.quest.(sQuest).win_condition = "BattleOfTheColony";
    pchar.quest.(sQuest).function= "BattleOfTheColony";
    SiegeTrace("взведён страховочный таймер BattleOfTheColony на 2 сут (сработает, если событие прибытия эскадры потеряется)");
}

float GetDistanceToColony(string sColony)
{
    if (!IsEntity(loadedLocation))
    {

        int iCnum = FindColony(sColony);
		if (iCnum == -1) return -1.0;
		string sIsland = Colonies[iCnum].island;
		string sTemp = sColony+"_town";
		
        return GetDistance2D(stf(worldMap.playerShipX), stf(worldMap.playerShipZ), stf(worldMap.islands.(sIsland).(sTemp).position.x), stf(worldMap.islands.(sIsland).(sTemp).position.z));
    }
    else
    {
        int locnum = FindLocation(pchar.location);
        if (locnum != -1 && CheckAttribute(&locations[locnum], "townsack") )
        {
            if (sColony == locations[locnum].townsack)
            return makefloat(0);
        }

    }
    return makefloat(-1);
}

void EndSiegeMap()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sHead = FillSquadronGoods();

    // > FindNonEnemyColonyForNation вернёт -1, если нация враждебна всем.
    // > sHead может быть пуст, если у эскадры не осталось командира - энкаунтер на карте тогда не создаём.
    int iHomeColony = FindNonEnemyColonyForNation(sti(aData.nation), true);

    if (iHomeColony != -1 && sHead != "")
    {
        SiegeTrace("ЭТАП: эскадра уходит домой - " + sHead + " идёт " + aData.Colony + " -> " + colonies[iHomeColony].id + ", срок хода 4 сут " + SiegeTag());
        Map_CreateTrader(aData.Colony, colonies[iHomeColony].id, sHead, 4);
    }
    else
        SiegeTrace("ЭТАП: эскадра домой НЕ идёт (порт назначения=" + iHomeColony + ", командир='" + sHead + "') - уборку сделает только таймер ClearSiege " + SiegeTag());

    SiegeTrace("взведён таймер ClearSiege на 5 суток - финальная уборка осады");
    string sQuest = "ClearSiege";
    SetTimerCondition(sQuest, 0, 0, 5, false);
    pchar.quest.(sQuest).win_condition = "ClearSiege";
    pchar.quest.(sQuest).function= "SiegeClear";
    //--> слухи
    SiegeRumourEx(StringFromKey("Common_rumours_156", NationNameSK(sti(aData.nation))), aData.Colony, sti(aData.conation), -1, 5, 3, "citizen,habitue,trader,tavern");
    //<-- слухи

}

string FillSquadronGoods()
{
    aref aData;
    ref rchar;

    makearef(aData, NullCharacter.Siege);
    Group_FreeAllDead();
    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";

    ref rGroup = Group_GetGroupByID(sGroup);
    rGroup.Task = AITASK_MOVE;
    rchar = Group_GetGroupCommander(sGroup);
    if (!CheckAttribute(rchar, "id"))
    {
        SiegeTrace("возврат домой: у группы " + sGroup + " не осталось командира - энкаунтер ухода не создаём " + SiegeTag());
        return "";
    }
    SiegeTrace("возврат домой: командир уходящей эскадры " + rchar.id + ", кораблей в группе " + Group_GetCharactersNum(sGroup));
    return rchar.id;
}

int MakeSiegeSquadron(int ination)
{
    ref sld;
    aref aData;
    string sCapId = NationShortName(ination)+"SiegeCap_";
    string sGroup = "Sea_" + sCapId + "1";
    makearef(aData, NullCharacter.Siege);
    aData.iSquadronPower = 0;
	int iSP = 0;
    int itmp = 0;
    
    Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);

    aData.ishipcount = 5 + rand(2);
    int i, icon = sti(aData.ishipcount);

    SiegeTrace("ЭТАП: генерация эскадры " + sGroup + " для " + NationShortName(ination) + " - кораблей " + icon + ", класс 1-2, срок жизни капитанов 30 сут");

    for (i = 1; i <= icon; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter(sCapId + i, "off_hol_2", "man", "man", 5, ination, 30, true));

        sld.dialog.filename = "Capitan_dialog.c";
	    sld.dialog.currentnode = "Siegehelp";
	    sld.DeckDialogNode = "Siegehelp";
	    LAi_SetImmortal(sld, false);

        itmp = SetSiegeShip(sld, 2, 1, ination); // генерируем корабли для осады

        iSP += itmp;
        SetFantomParamHunter(sld); //крутые парни
        SetCaptanModelByEncType(sld, "war");
        sld.mapEnc.type = "war";
        sld.mapEnc.worldMapShip = Nations[ination].worldMapShip+"_manowar";
        sld.mapEnc.Name = FindPersonalName("SiegeCap_mapEnc");
        Group_AddCharacter(sGroup, sCapId + i);
        if (i == 1) SetRandGeraldSail(sld, sti(sld.Nation)); // homo Гербы
        SiegeTrace("  корабль " + i + "/" + icon + ": " + sld.id + " (" + GetFullName(sld) + ")" + ", индекс перса " + sld.index + ", тип " + sld.Ship.Type + " класс " + GetCharacterShipClass(sld) + ", команда " + sld.ship.crew.quantity + ", вклад в мощь " + itmp + ", накоплено " + aData.iSquadronPower);
    }
	
	aData.iSquadronPower = iSP;
	
    Log_TestInfo("Squadron Power: "+aData.iSquadronPower+"%");
    Log_TestInfo("Colony Power: "+sti(colonies[FindColony(aData.colony)].FortValue)+"%");
    
    Group_SetGroupCommander(sGroup, sCapId+ "1");
    ref rGroup = Group_GetGroupByID(sGroup);
    rGroup.Task = AITASK_MOVE;

    SiegeTrace("эскадра готова: мощь " + aData.iSquadronPower + " (после штрафа -19) против форта " + sti(colonies[FindColony(aData.colony)].FortValue) + " у " + aData.colony + "; командир " + sCapId + "1, задача AITASK_MOVE");

    return sti(aData.iSquadronPower);
}

int SetSiegeShip(ref rChar, int iClassMin, int iClassMax, int iNation)
{
    int SiegeShips, hcrew;

    SiegeShips = GetShipTypeNational(iClassMin, iClassMax, "War", iNation); //ZhilyaevDm

    SetRandomNameToCharacter(rChar);
    SetRandomNameToShip(rChar);
    rChar.Ship.Type = GenerateShipExt(SiegeShips, 1, rChar);
    SetBaseShipData(rChar);
    hcrew = GetMaxCrewQuantity(rChar);
    SetCrewQuantity(rChar, hcrew);
    SetCrewQuantityFull(rChar); // TODO

    ShipOverhaul(rChar);

    Fantom_SetCannons(rChar, "war");
    Fantom_SetBalls(rChar, "war");
    Fantom_SetGoods(rChar, "war");

	// > Мощь корабля считаем от класса, кол-ва макс. команды и ранга кэпа (кэп - фантом: чем выше ранг игрока, тем выше ранг кэпа)
	int iCapRank = sti(rChar.rank) / 10;
	int iShipClass = (8 - GetCharacterShipClass(rChar)) * 2;
	int iShipCrew = (hcrew - GetMinCrewQuantity(rChar)) / 100;
    return makeint(iShipCrew + iCapRank + iShipClass);
}

void Siege_DailyUpdate()
{
	int iDays;
    if(!actLoadFlag)
    {
		iDays = GetQuestPastDayParam("Siege_DailyUpdate");
		int iThreshold = 60+rand(60);
		if (iDays >= iThreshold)
		{
			SiegeTrace("=== ТИК: прошло " + iDays + " сут, порог " + iThreshold + " - ЗАПУСКАЕМ новую осаду ===");
	        CreateSiege("");
	        SaveCurrentQuestDateParam("Siege_DailyUpdate");
		}
		else
			SiegeTrace("тик: прошло " + iDays + " сут, порог этого броска " + iThreshold + " - рано");
	}
}

void CreateSiege(string tmp)
{
    SiegeTrace("ЭТАП 1/8 СОЗДАНИЕ: сперва подчищаем следы предыдущей осады " + SiegeTag());
    SiegeClear("");
    ref rColony;
    aref aData;
    makearef(aData, NullCharacter.Siege);
    
    if (PrepareSiege())
    {
        aData.progress = SIEGE_ST_APPROACH;
        DeleteAttribute(aData, "loot");
        DeleteAttribute(aData, "PlayerHelpMayor");
        DeleteAttribute(aData, "HelpColony");
        DeleteAttribute(aData, "EndLaterCount"); // > счётчик отсрочек - только в пределах одной осады
		DeleteAttribute(aData, "PlayerAtIsland"); // > присутствие игрока - тоже состояние одной осады
        DeleteAttribute(aData, "CabinHold");
        string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
        Log_TestInfo("CreateSiege "+NationShortName(sti(aData.nation)));
        makeref(rColony, Colonies[FindColony(aData.colony)]);
        MakeSiegeSquadron(sti(aData.nation));
        aData.SiegeHP = Group_GetPowerHP(sGroup);
        SiegeTrace("эталонное HP эскадры зафиксировано: " + aData.SiegeHP + " (от него считается CheckSquadronInjuri)");
        ClearIslandShips(aData.colony);
        SiegeTrace("сторожевые корабли у " + aData.colony + " убраны с рейда");
        BeginSiegeMap(NationShortName(sti(aData.nation))+"SiegeCap_1");
        aData.isSiege = 1;
        SiegeTrace("ОСАДА СОЗДАНА " + SiegeTag() + " isSiege=1");
    }
    else
        SiegeTrace("ОСАДА НЕ СОЗДАНА: PrepareSiege вернул false. Тик потрачен, следующая попытка через 60-120 сут");
}

void SiegeProgress()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    int i = sti(aData.progress);

    if (i == SIEGE_ST_APPROACH)
    {
        Log_TestInfo("По карте!");
        SiegeTrace("прибытие эскадры на карте: стадия ПОДХОД -> начинаем бой у колонии " + SiegeTag());
        BattleOfTheColony("");
        return;
    }
    if (i == SIEGE_ST_BATTLE)
    {
        SiegeTrace("прибытие эскадры домой: стадия БОЙ -> финальная уборка " + SiegeTag());
        SiegeClear("");
        return;
    }
    Log_TestInfo("SiegeProgress: неожиданная стадия progress="+i+" - пропускаем");
    SiegeTrace("прибытие эскадры при стадии " + i + " - обработчика нет, пропускаем " + SiegeTag());
}

int CheckSquadronInjuri()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    float maxHP = stf(aData.SiegeHP);
    if (maxHP <= 0.0) return 0;
    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
    return makeint(Group_GetPowerHP(sGroup)*(100/maxHP));
}

int CheckFortInjuri()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    ref FC = GetFortCommander(aData.colony);
    float maxCannons = 10;
    if (CheckAttribute(FC, "fort.cannons.quantity"))
    {
    	maxCannons = sti(FC.fort.cannons.quantity);
    }
    if (maxCannons <= 0.0) maxCannons = 1.0;
    if (CheckAttribute(FC, "Fort.Mode") && sti(FC.Fort.Mode) == FORT_DEAD) return 0;
    return makeint(makeint(GetCurrentShipHP(FC)/100)*(100/maxCannons));
}

void LeaveBattle(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    SiegeTrace("игрок ВОШЁЛ в акваторию " + aData.island + " (вызов '" + tmp + "') - взводим пересчёт исхода на выход оттуда " + SiegeTag());
    // > Переход во внутренние помещения корабля не считается выходом из акватории
    aData.PlayerAtIsland = 1;
    DeleteAttribute(aData, "CabinHold");
    string sQuest = "SiegeResult";
    pchar.quest.(sQuest).win_condition.l1 = "ExitFromLocation";
    pchar.quest.(sQuest).win_condition.l1.location = aData.island;
    pchar.quest.(sQuest).win_condition = "SiegeResult";
    pchar.quest.(sQuest).function = "SiegeResult";
}

void LeaveTown(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
    string sGroup = "Sea_"+sCap+"1";
    ref NPChar = Group_GetGroupCommander(sGroup);
    
    SiegeTrace("ЭТАП: игрок покидает взятый в союзе город (вызов '" + tmp + "') - командир " + NPChar.id + " уходит из ратуши, засчитываем ПОБЕДУ эскадры принудительно " + SiegeTag());

    AfterTownBattle();  // все, все свободны
    LAi_LoginInCaptureTown(NPChar, false);
    // > Флаг бессмертия командиров осадной эскадры передавался по наследству другому при каждой следующей генерации
    LAi_SetImmortal(NPChar, false);
    aData.win = 1;
    EndOfTheSiege("End");
    NPChar.location = "";
}

void SiegeResult(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);

    // > Проверка SIEGE_PLAYER_CAN_VISIT_CABIN
    if (IsPlayerHoldingAtSiegeIsland())
    {
        if (!CheckAttribute(aData, "CabinHold"))
            aData.CabinHold = 1;
            SiegeTrace("игрок ушёл во внутренние помещения корабля (" + pchar.location + "), оставаясь в акватории " + aData.island + " - выходом из акватории не считаем, исход не пересчитываем " + SiegeTag());

        DeleteAttribute(pchar, "quest.SiegeResult.over");
        return;
    }

    DeleteAttribute(aData, "CabinHold");
    aData.PlayerAtIsland = 0;

    int ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
    int fortDamage = CheckFortInjuri();
    int SquadronDamage = CheckSquadronInjuri();
    Log_TestInfo("fortDamage: "+ fortDamage);
    Log_TestInfo("SquadronDamage: "+ SquadronDamage);
    aData.win =((ifortPower)*fortDamage < sti(aData.iSquadronPower)*SquadronDamage );
    Log_TestInfo(" Win: "+aData.win);

    int iFortScore = ifortPower * fortDamage;
    int iSquadScore = sti(aData.iSquadronPower) * SquadronDamage;
    SiegeTrace("ЭТАП: игрок ВЫШЕЛ из акватории (вызов '" + tmp + "') - ПЕРЕСЧЁТ ИСХОДА по факту урона " + SiegeTag());
    SiegeTrace("  форт: мощь " + ifortPower + " x целость " + fortDamage + "% = " + iFortScore);
    SiegeTrace("  эскадра: мощь " + aData.iSquadronPower + " x целость " + SquadronDamage + "% = " + iSquadScore);
    SiegeTrace("  ИТОГ win=" + aData.win + " (1 = победа эскадры)");

    string sQuest = "LeaveBattle";
    pchar.quest.(sQuest).win_condition.l1 = "location";
    pchar.quest.(sQuest).win_condition.l1.location = aData.island;
    pchar.quest.(sQuest).function= "LeaveBattle";
    CheckGroupCommander("");
}

void CheckGroupCommander(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    string sCap = NationShortName(sti(aData.nation))+"SiegeCap_";
    string sGroup = "Sea_"+sCap+"1";
    ref rchar = Group_GetGroupCommander(sGroup);
    bool bhasCom = false;
    
    if ( !CharacterIsDead(rchar)) return;

    SiegeTrace("смена командира: прежний (" + rchar.id + ") мёртв, ищем замену среди " + sCap + "1.." + sti(aData.ishipcount));

    int k, CapNum = sti(aData.ishipcount);
    
    for(k = 1; k <= CapNum ; k++)
    {
       if (GetCharacterIndex(sCap+k) != -1 && !CharacterIsDead(CharacterFromID(sCap+k)))
       {
            Group_AddCharacter(sGroup,sCap + k);
            if (!bhasCom)
            {
                Group_SetGroupCommander(sGroup, sCap+k );
                bhasCom = true;
                SiegeTrace("  новый командир эскадры: " + sCap + k);
            }

       }
    }
    if (!bhasCom)
    	SiegeTrace("  живых капитанов не осталось - эскадра обезглавлена");
}

void BattleOfTheColony(string tmp)
{
    aref aData;
    ref rColony;
    makearef(aData, NullCharacter.Siege);
    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
    
    if (CheckAttribute(PChar, "quest.BattleOfTheColony")) Pchar.quest.BattleOfTheColony.over = "yes";

    int iColIdx = FindColony(aData.colony);
    makeref(rColony, Colonies[iColIdx]);

    if (CheckAttribute(rColony, "Siege"))
    {
        Log_TestInfo("BattleOfTheColony: осада уже идёт - повторный вход пропущен");
        SiegeTrace("ЭТАП 3/8 БОЙ: повторный вход (вызов '" + tmp + "') ПРОПУЩЕН - флаг осады у " + aData.colony + " уже стоит " + SiegeTag());
        return;
    }

    SiegeTrace("ЭТАП 3/8 БОЙ: эскадра встала у " + aData.colony + " (вызов '" + tmp + "') " + SiegeTag());

    CheckGroupCommander("");
    rColony.DontSetShipInPort = true;
    rColony.Siege = true;
    aData.progress = SIEGE_ST_BATTLE;
    SiegeTrace("  колонии выставлены Siege=1 и DontSetShipInPort=1 (корабли в порту больше не появляются)");

    ref FC = GetFortCommander(aData.colony);
    Group_SetTaskMove(sGroup, stf(FC.ship.pos.x), stf(FC.ship.pos.z));
    Group_SetAddress(sGroup, aData.island, "Quest_ships", "reload_fort1_siege");//  TODO

    string sQuest = "EndOfTheSiege";
    int ifort = sti(colonies[iColIdx].FortValue);
    int btime = ifort - sti(aData.iSquadronPower);
    aData.win =(ifort < sti(aData.iSquadronPower));
    int SiegeTime = 14 - makeint((abs(btime))/10);
    if (SiegeTime < 1) SiegeTime = 1; // > нулевого/отрицательного срока осады быть не должно
    aData.SiegeTime = SiegeTime;
    Log_TestInfo("Siege period: "+SiegeTime);
    Log_TestInfo("Win: "+aData.win);

    SiegeTrace("  расчёт: форт " + ifort + " против эскадры " + aData.iSquadronPower + ", разрыв " + btime + " -> срок осады " + SiegeTime + " сут, предварительный исход win=" + aData.win);
    SiegeTrace("  группа отправлена к форту (" + FC.id + ") на локатор reload_fort1_siege острова " + aData.island);
    SiegeTrace("  взводим квесты: EndOfTheSiege (таймер " + SiegeTime + " сут), LeaveBattle (вход в акваторию), PlayerKillSquadron (гибель группы)");

    SetTimerCondition(sQuest, 0, 0, SiegeTime, false);
    pchar.quest.(sQuest).win_condition = "EndOfTheSiege";
    pchar.quest.(sQuest).function= "EndOfTheSiege";
    
    sQuest = "LeaveBattle";
    pchar.quest.(sQuest).win_condition.l1 = "location";
    pchar.quest.(sQuest).win_condition.l1.location = aData.island;
    pchar.quest.(sQuest).function= "LeaveBattle";
    
    sQuest = "PlayerKillSquadron";
    pchar.quest.(sQuest).win_condition.l1 = "Group_Death";
    pchar.quest.(sQuest).win_condition.l1.group = sGroup;
    pchar.quest.(sQuest).function= "PlayerKillSquadron";
    
    SaveCurrentQuestDateParam("Siege_Start");
    aData.tmpID1 = SiegeRumourEx(StringFromKey("Common_rumours_157", NationNameSK(sti(aData.nation))), aData.Colony, sti(aData.nation)+10, -1, sti(aData.SiegeTime)-2, 3, "citizen,habitue,trader,tavern");
    aData.tmpID2 = SiegeRumour("OnSiege_1", "", sti(aData.conation)+10, sti(aData.nation)+10, sti(aData.SiegeTime)-2, 3);
    aData.tmpID3 = SiegeRumour("OnSiege_2", "", sti(aData.nation), -1, sti(aData.SiegeTime)-2, 3);
    aData.tmpID4 = SiegeRumour("OnSiege_3", "!"+aData.Colony, sti(aData.conation), -1, sti(aData.SiegeTime)-2, 3);
    int iRumourTerm = SiegeTime - 2;
    SiegeTrace("  разосланы слухи об осаде, id " + aData.tmpID1 + "/" + aData.tmpID2 + "/" + aData.tmpID3 + "/" + aData.tmpID4 + ", срок жизни " + iRumourTerm + " сут; отсчёт Siege_Start запущен");
}

void PlayerKillSquadron(string tmp)
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    Log_TestInfo("Player Kill Squadron!");
    SiegeTrace("ЭТАП: группа осады МЕРТВА (или снесена) - засчитываем ПОРАЖЕНИЕ эскадры " + SiegeTag());
    aData.win = 0;
    if (GetNationRelation2MainCharacter(sti(aData.nation))) aData.PlayerHelpMayor = true; // < ?! TODO
    SiegeTrace("  отношение игрока к " + NationShortName(sti(aData.nation)) + " = " + GetNationRelation2MainCharacter(sti(aData.nation)) + " -> право на награду мэра PlayerHelpMayor=" + aData.PlayerHelpMayor);
    EndOfTheSiege("End");
}

void  EndOfTheSiege(string tmp)
{
    ref sld;
    int l, f;
    string tmpName;
    
	Log_TestInfo("Siege End");
	
    bool bcapt = false;
    aref aData;
    
    makearef(aData, NullCharacter.Siege);
    
    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
    ref rColony = GetColonyByIndex(FindColony(aData.colony));
    int ifortPower = sti(rColony.FortValue);
    int idist = makeint(GetDistanceToColony(aData.Colony));

	// > GetDistanceToColony для внутренних помещений корабля возвращает -1 ("далеко"), потому как у каюты/палубы нет townsack осаждаемой колонии.
    if (idist == -1 && IsPlayerHoldingAtSiegeIsland())
    {
        idist = 0;
        SiegeTrace("игрок во внутренних помещениях корабля (" + pchar.location + ") в акватории " + aData.island + " - считаем, что он на месте (дистанция 0)");
    }

	// > Признак присутствия собираем из двух источников
    bool bPlayerNear = pchar.location == aData.island;

    // > Дистанция остаётся для суши и глобалки
    if (!bPlayerNear) bPlayerNear = idist != -1 && idist <= 60;

    // > Fix: раньше осада завершалась прямо под игроком, не успевшим закончить бой до полуночи последнего дня срока.
    // > Не успеет сейчас за SIEGE_MAX_END_DELAY - сам виноват.
    bool bForce = tmp == "End";
    int iLater = 0;
    if (CheckAttribute(aData, "EndLaterCount")) iLater = sti(aData.EndLaterCount);

    SiegeTrace("ЭТАП 4/8 ЗАВЕРШЕНИЕ: вход с параметром '" + tmp + "' (принудительно=" + bForce + "), локация игрока '" + pchar.location + "', акватория осады '" + aData.island + "', дистанция до " + aData.colony + " = " + idist + " (порог 60) -> рядом=" + bPlayerNear + ", отсрочек уже " + iLater + "/" + SIEGE_MAX_END_DELAY + ", исход win=" + aData.win + " " + SiegeTag());

    if(!bPlayerNear || bForce || iLater >= SIEGE_MAX_END_DELAY)
    {
        if (iLater >= SIEGE_MAX_END_DELAY) SiegeTrace("  причина: исчерпан лимит отсрочек - завершаем, даже если игрок рядом");
        else if (bForce)                   SiegeTrace("  причина: принудительный вызов");
        else                               SiegeTrace("  причина: игрока нет ни в акватории осаждаемого острова, ни рядом с колонией");

        DeleteAttribute(aData, "EndLaterCount");
        // чистим слухи
        for (l = 1; l <= 4; l++) // > tmpID0 не существует
        {
            tmpName = "tmpID"+l;
            if (CheckAttribute(aData, tmpName))
            {
                f = FindRumour(sti(aData.(tmpName)));
                if (f != -1)
                	Rumour[f].state = 0; // > Слух мог истечь или быть вытеснен из очереди (AddRumorR сдвигает её)
                else
                    SiegeTrace("  слух " + tmpName + "=" + aData.(tmpName) + " в очереди не найден (истёк или вытеснен) - гасить нечего");
                DeleteAttribute(aData, tmpName);
            }
        }
        SiegeTrace("  слухи об идущей осаде сняты");
        // меняем диалог
        ref comand = Group_GetGroupCommander(sGroup);
        SiegeTrace("  командир эскадры на момент завершения: " + comand.id + " - переводим его диалог в мирный узел");
        if (!CheckAttribute(comand, "dialog")
        || comand.dialog.currentnode != "no_return_02"
        || comand.DeckDialogNode != "no_return_02")
        {
            comand.dialog.currentnode = "First time";
		    comand.DeckDialogNode = "First time";
        }
        // возвращаем мэру обычный диалог
        DeleteAttribute(rColony, "Siege"); //снимаем осаду
        
        if (CheckAttribute(PChar, "quest.EndOfTheSiegeLater.again"))
        {
            DeleteAttribute(Pchar, "quest.EndOfTheSiegeLater.again");
            Pchar.quest.EndOfTheSiegeLater.over = "yes";
        }
        if (CheckAttribute(PChar, "quest.SiegeResult")) Pchar.quest.SiegeResult.over = "yes";
        if (CheckAttribute(PChar, "quest.LeaveBattle")) Pchar.quest.LeaveBattle.over = "yes";
        // > Гасим и остальные прерывания осады, иначе они срабатывают уже после её конца:
        // > EndOfTheSiege - собственный таймер при принудительном завершении
        // > PlayerKillSquadron - на распаде группы (переворачивает исход в поражение)
        // > LeaveTown - висел вечно и мог досрочно завершить уже другую осаду.
        if (CheckAttribute(PChar, "quest.EndOfTheSiege")) Pchar.quest.EndOfTheSiege.over = "yes";
        if (CheckAttribute(PChar, "quest.PlayerKillSquadron")) Pchar.quest.PlayerKillSquadron.over = "yes";
        if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
        SiegeTrace("  флаг осады с колонии снят, все квесты осады погашены");

        if (sti(aData.win) == 1)
        {
            aData.loot = 200000+100000*makeint(ifortPower/30);
            Log_TestInfo("Siege loot ="+aData.loot);
            SiegeTrace("ЭТАП 5/8 ИТОГ: ПОБЕДА ЭСКАДРЫ у " + aData.colony + ", добыча " + aData.loot + " (от мощи форта " + ifortPower + "), целость эскадры " + CheckSquadronInjuri() + "%");

            if (CheckSquadronInjuri()>= 70)
            {
                SiegeTrace("  эскадра сохранила >=70% - раздаём потери и трофеи по кораблям");
                int icon = Group_GetCharactersNum(sGroup);
                ref rgrp = Group_GetGroupByID(sGroup);
                int i, j;
                int qrew;
                aref arQ, arAttr;
                string sSldId;

                if (icon > 0) makearef(arQ, rgrp.Quest);

                for (i = icon - 1; i >= 0; i--) // > с конца - ниже возможно удаление персонажа из группы (иначе сместятся индексы)
                {
                    // > Раньше цикл шёл по снимку индекса без сверки и в день конца осады калечил (а то и удалял) совершенно постороннего живого перса
                    arAttr = GetAttributeN(arQ, i);
                    sSldId = GetAttributeValue(arAttr);
                    j = GetCharacterIndex(sSldId);
                    if (j == -1 || Characters[j].id != sSldId)
                    {
                        Log_TestInfo("Siege: stale group record "+sSldId+" - skipped");
                        SiegeTrace("  !! запись группы " + i + " протухла: id '" + sSldId + "' указывает в чужой/пустой слот " + j + " - НЕ трогаем персонажа, запись удаляем");
                        DeleteAttribute(rgrp, "Quest."+GetAttributeName(arAttr));
                        continue;
                    }
                    sld = &Characters[j];
                    Fantom_SetGoods(sld, "trade");
                    if (i > 3 && rand(1) == 0)
                    {
                        SiegeTrace("  корабль " + sSldId + " (слот " + j + ") не вернулся из похода - удаляем персонажа");
                        Group_DelCharacter(sGroup, sld.id);
                        Log_TestInfo(sld.id+" - dead!");
                        DeleteCharacter(sld);
                    }
                    else
                    {
                        if (rand(3)==1)
						{
							sld.ship.masts.mast3 = 1;
						}
                        else
						{
							sld.ship.SP = sti(sld.ship.SP) - 10*(rand(3)+1);
						}
    	                sld.ship.HP = sti(sld.ship.HP) - makeint(sti(sld.ship.HP)/(2+rand(2)));
    	                qrew = GetMaxCrewQuantity(sld);
    	                SetCrewQuantity(sld, qrew - makeint(qrew/(2+rand(1))));
                        SiegeTrace("  корабль " + sSldId + " (слот " + j + ") потрёпан: HP=" + sld.ship.HP + ", паруса=" + sld.ship.SP + ", команда=" + sld.ship.crew.quantity);
                    }
                }
            }
            else
                SiegeTrace("  эскадра целостью " + CheckSquadronInjuri() + "% (<70) - потери по кораблям НЕ раздаём");

            EndSiegeMap();

            if (sti(aData.iSquadronPower) > ifortPower)
            {
                if (ifortPower <= SIEGE_CAPTURE_PIVOT) //Решение о взятии колонии себе взвешивается очень тщательно!
                {
                    bcapt = rand(3)==2;
                }
                else
                {
                    int iDenom = abs(ifortPower - SIEGE_CAPTURE_PIVOT);
                    if (iDenom < 3) iDenom = 3;
                    bcapt = rand(iDenom) == 0;
                }
            }
            SiegeTrace("ЭТАП 6/8 СУДЬБА ГОРОДА: бросок на присоединение = " + bcapt + " (форт " + ifortPower + ", эскадра " + aData.iSquadronPower + ", мир на паузе=" + bWorldAlivePause + ", город помечен notCaptured=" + CheckAttribute(rColony, "notCaptured") + ")");

            if (!bWorldAlivePause && bcapt && !CheckAttribute(rColony, "notCaptured"))
            {
                SiegeTrace("  " + aData.colony + " МЕНЯЕТ НАЦИЮ: " + NationShortName(sti(aData.conation)) + " -> " + NationShortName(sti(aData.nation)));
                SetCaptureTownByNation(aData.colony, sti(aData.nation));
                
                SiegeRumour(StringFromKey("Common_rumours_158", NationNameGenitive(sti(aData.nation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt"), NationNameSK(sti(aData.conation))), aData.Colony, sti(aData.nation), -1, 15, 3);
                SiegeRumour(StringFromKey("Common_rumours_159", NationNameSK(sti(aData.nation)), NationNameSK(sti(aData.conation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt"), GetConvertStr(aData.Colony+" Town", "LocLables.txt"), NationNameSK(sti(aData.nation))), "", sti(aData.conation)+10, sti(aData.nation)+10, 30, 3);
                SiegeRumour(StringFromKey("Common_rumours_160", NationNamePeople(sti(aData.nation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt")), "", sti(aData.conation), -1, 30, 3);
                SiegeRumour(StringFromKey("Common_rumours_161", NationNameGenitive(sti(aData.conation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt")), ("!"+aData.Colony), sti(aData.nation), -1, 30, 3);
                
            }
            else
            {
                SiegeTrace("  " + aData.colony + " остаётся за " + NationShortName(sti(aData.conation)) + ", но разграблен: обнуляем магазин и вклады ростовщика");
                SetNull2StoreMan(rColony);// нулим магазин при захвате города эскадрой
                SetNull2Deposit(aData.colony);// нулим ростовщиков
                
                SiegeRumourEx(StringFromKey("Common_rumours_162", NationNameGenitive(sti(aData.conation)), NationNameSK(sti(aData.nation))), aData.Colony, sti(aData.conation), -1, 15, 3, "citizen,habitue,trader,tavern");
                SiegeRumour(StringFromKey("Common_rumours_163", NationNameSK(sti(aData.nation)), NationNameSK(sti(aData.conation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt"), NationNameSK(sti(aData.nation))), "", sti(aData.conation)+10, sti(aData.nation)+10, 30, 3);
                SiegeRumour(StringFromKey("Common_rumours_164", NationNamePeople(sti(aData.nation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt")), "!"+aData.Colony, sti(aData.conation), -1, 30, 3);
                SiegeRumour(StringFromKey("Common_rumours_165", NationNameSK(sti(aData.conation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt")), "!"+aData.Colony, sti(aData.nation), -1, 30, 3);
            }
            FortDestroy();// уничтожаем форт
            Group_SetAddressNone(sGroup);
            
            Log_TestInfo("Siege Finish - Squadron win!");
            SiegeTrace("ЭТАП 7/8 ОСАДА ЗАВЕРШЕНА ПОБЕДОЙ ЭСКАДРЫ; группа снята с адреса, ждём уборку " + SiegeTag());
        }
        else
        {
            SiegeTrace("ЭТАП 5/8 ИТОГ: ПОРАЖЕНИЕ ЭСКАДРЫ у " + aData.colony + " - город отбился, форт цел, добычи нет");
            SiegeRumourEx(StringFromKey("Common_rumours_166", NationNameSK(sti(aData.nation))), aData.Colony, sti(aData.conation), -1, 15, 3, "citizen,habitue,trader,tavern");
            SiegeRumour(StringFromKey("Common_rumours_167", NationNameSK(sti(aData.nation)), NationNameSK(sti(aData.conation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt")), "", sti(aData.conation)+10, sti(aData.nation)+10, 30, 3);
            SiegeRumour(StringFromKey("Common_rumours_168", NationNamePeople(sti(aData.nation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt"), NationNameSK(sti(aData.nation))), "!"+aData.Colony, sti(aData.conation), -1, 30, 3);
            SiegeRumour(StringFromKey("Common_rumours_169", NationNameSK(sti(aData.conation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt")), "!"+aData.Colony, sti(aData.nation), -1, 30, 3);
            SiegeClear("");
            Log_TestInfo("Siege Finish - Squadron defeat!");
            SiegeTrace("ЭТАП 7/8 ОСАДА ЗАВЕРШЕНА ПОРАЖЕНИЕМ ЭСКАДРЫ");
        }
    }
    else
    {
        iLater = iLater + 1;
        aData.EndLaterCount = iLater;
        Log_TestInfo("End Siege Later! attempt "+iLater);
        SiegeTrace("ОТСРОЧКА " + iLater + "/" + SIEGE_MAX_END_DELAY + ": игрок рядом (локация '" + pchar.location + "', дистанция " + idist + " до " + aData.colony + ") - не завершаем осаду под ним, переспросим через сутки " + SiegeTag());
        string sQuest = "EndOfTheSiegeLater";
        SetTimerCondition(sQuest, 0, 0, 1, true);
        pchar.quest.(sQuest).win_condition = "EndOfTheSiegeLater";
        pchar.quest.(sQuest).function= "EndOfTheSiege";
    }
    

}
void FortDestroy()
{
    aref aData;
    makearef(aData, NullCharacter.Siege);
    int ind = GetCharacterIndex(aData.colony + " Fort Commander");
    ref FC;
    
	if (ind == -1)
	{
	    SiegeTrace("форт: коменданта '" + aData.colony + " Fort Commander' в мире нет - разрушать нечего");
	    return;
	}

    FC = &Characters[ind];
    SiegeTrace("форт " + aData.colony + " РАЗРУШЕН (комендант " + FC.id + ", индекс " + ind + ") - шлём FORT_DESTROYED");
    FC.Fort.Mode = FORT_DEAD;
	FC.Fort.DieTime.Year = GetDataYear();
	FC.Fort.DieTime.Month = GetDataMonth();
	FC.Fort.DieTime.Day = GetDataDay();
	FC.Fort.DieTime.Time = GetTime();
	Event(FORT_DESTROYED, "l", sti(FC.index));
    Log_TestInfo("FORT_DEAD");
}

void SiegeClear(string tmp)
{
    aref aData;
    ref rColony;
    if (!CheckAttribute(&NullCharacter, "Siege.Colony"))
    {
        SiegeTrace("уборка: данных об осаде нет (первый запуск игры или уже вычищено) - пропускаем");
    }
    if (CheckAttribute(&NullCharacter, "Siege.Colony"))
    {
        makearef(aData, NullCharacter.Siege);
        SiegeTrace("ЭТАП 8/8 УБОРКА (вызов '" + tmp + "') " + SiegeTag());
        makeref(rColony, Colonies[FindColony(aData.Colony)]);
        DeleteAttribute(rColony, "DontSetShipInPort"); //возвращаем жизнь
        DeleteAttribute(rColony, "Siege"); //снимаем осаду
        SiegeTrace("  с " + aData.Colony + " сняты Siege и DontSetShipInPort - корабли в порту снова генерируются");
        if (CheckAttribute(PChar, "quest.Union_with_Escadra")) Pchar.quest.Union_with_Escadra.over = "yes";
        if (CheckAttribute(PChar, "quest.BattleOfTheColony")) Pchar.quest.BattleOfTheColony.over = "yes";
        if (CheckAttribute(PChar, "quest.EndOfTheSiege")) Pchar.quest.EndOfTheSiege.over = "yes";
        if (CheckAttribute(PChar, "quest.ClearSiege")) Pchar.quest.ClearSiege.over = "yes";
        if (CheckAttribute(PChar, "quest.LeaveBattle")) Pchar.quest.LeaveBattle.over = "yes";
        if (CheckAttribute(PChar, "quest.SiegeResult")) Pchar.quest.SiegeResult.over = "yes";
        if (CheckAttribute(PChar, "quest.PlayerKillSquadron")) Pchar.quest.PlayerKillSquadron.over = "yes";
        // > Отсрочка окончания живёт с again = true (сама по себе не гаснет), снимаем явно, иначе её обработчик продолжит дёргать EndOfTheSiege уже по снятой осаде
        if (CheckAttribute(PChar, "quest.EndOfTheSiegeLater"))
        {
            DeleteAttribute(Pchar, "quest.EndOfTheSiegeLater.again");
            Pchar.quest.EndOfTheSiegeLater.over = "yes";
        }
        if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
        DeleteAttribute(aData, "EndLaterCount");
		DeleteAttribute(aData, "PlayerAtIsland");
        DeleteAttribute(aData, "CabinHold");
        DeleteAttribute(PChar, "Siege_Start");
        string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
        aData.progress = SIEGE_ST_DONE;
        SiegeTrace("  погашены все квесты осады, снят отсчёт Siege_Start и счётчик отсрочек");
        SiegeTrace("  удаляем группу " + sGroup + " (кораблей в ней было " + Group_GetCharactersNum(sGroup) + ")");
        Group_SetAddressNone(sGroup);
        Group_DeleteGroup(sGroup);
        aData.isSiege = 0;
        SiegeTrace("ОСАДА ПОЛНОСТЬЮ УБРАНА, isSiege=0. Данные (colony/nation/loot) остаются для награды мэра и лута в каюте");
    }
}

void SiegeSquadronOnMap(string _chrId)
{
    Group_FreeAllDead();
}

//////////////////////////////СЛУХИ////////////////////////////////////////////
int SiegeRumour(string stext, string sCity, int nation1, int nation2, int terms, int qty)
{
   return SiegeRumourEX(stext, sCity, nation1, nation2, terms, qty, "all");
}

int SiegeRumourEX(string stext, string sCity, int nation1, int nation2, int terms, int qty, string tip)
{
    object tmp;
    
    if (HasSubStr(stext, "OnSiege_"))
	{
		tmp.event = stext;
	}
    else
	{
		tmp.event = "none";
	}
    
    tmp.text = stext;
    tmp.state = qty;//кол-во раз
    tmp.tip = tip;
    tmp.rep = "none";
    if (sCity != "") tmp.City = sCity;
	//10, 11, 12, 13 - исключить эти нации из слухов
    if (nation1 != -1)
    {
        if (nation1 > 5)
        {
	    	tmp.nonation.n1 = nation1 - 10;
	    }
	    else
		{
			tmp.onlynation = nation1; //локализация
		}
	}
	
	if (nation2 != -1 && nation2 > 5)
	tmp.nonation.n2 = nation2 - 10;
	
    tmp.starttime = 0;
    tmp.actualtime = terms; //сроки
    tmp.next = "none";
    return AddRumorR(&tmp);
}

string NationNameSK(int nat)
{
    switch (nat)
    {
        case ENGLAND:
        	return XI_ConvertString("EnglandSK");
        break;
        
        case FRANCE:
        	return XI_ConvertString("FranceSK");
        break;
        
        case SPAIN:
        	return XI_ConvertString("SpainSK");
        break;
        
        case HOLLAND:
        	return XI_ConvertString("HollandSK");
        break;
		
		case PIRATE:
        	return XI_ConvertString("PirateSK");
        break;
    }
   
    return "";
}

string SiegeRumourText(int inum)
{
    aref aData;
    string sDays;
    
    makearef(aData, NullCharacter.Siege);
    
    int iDays = sti(aData.SiegeTime) - GetQuestPastDayParam("Siege_Start");
    sDays = iDays + " " +XI_ConvertString("day3");
    
    if (iDays < 5) sDays = iDays + " " +XI_ConvertString("day2");
    if (iDays <= 1 ) sDays = XI_ConvertString("hour4");
    
    switch (inum)
    {
        case 1:
        	return StringFromKey("Common_rumours_170", NationNamePeople(sti(aData.nation)), NationNameSK(sti(aData.conation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt"), sDays);
        break;

        case 2:
        	return StringFromKey("Common_rumours_171", NationNameSK(sti(aData.conation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt"), sDays);
        break;
        
        case 3:
        	return StringFromKey("Common_rumours_172", NationNamePeople(sti(aData.nation)), GetConvertStr(aData.Colony+" Town", "LocLables.txt"), sDays);
        break;
    }
    return "";
}
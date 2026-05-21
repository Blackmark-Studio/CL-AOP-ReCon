// Блок условных функций для квестовых меток
// Для квест-меток на суше используются функции вида:
// bool QuestID_Name_QuestMarkCondition(ref chr)
// Для квест-меток на глобальной карте используются функции вида:
// bool QuestID_Name_WDMQuestMarkCondition(string sLocId)

// Кондотьер
bool Headhunt_Begin_Smuggler_QuestMarkCondition(ref chr)
{
    return sti(Pchar.Rank) > 4 && !CheckAttribute(pchar, "questTemp.Headhunter");
}

bool Headhunt_Rat_Habitues_QuestMarkCondition(ref chr)
{
    if (CheckAttribute(pchar, "questTemp.Headhunter"))
    {
        if (pchar.questTemp.Headhunter == "Rat_Tavern" && chr.location == pchar.questTemp.Headhunter.Ratrumcity + "_tavern")
        {
    		return true;
        }
    }

    return false;
}

bool Headhunt_Halen_Begin_QuestMarkCondition(ref chr)
{
    return CheckAttribute(pchar, "questTemp.Headhunter") && pchar.questTemp.Headhunter == "next_task_4" &&
		GetQuestPastDayParam("pchar.questTemp.Headhunter_next_task_4") > 17;
}

// Работорговец
bool Slavetrader_Begin_WDMQuestMarkCondition(string sLocId)
{
    return sti(pchar.rank) >= 15; // act 2
}

bool Slavetrader_EscapeSlave_Habitues_QuestMarkCondition(ref chr)
{
    if (CheckAttribute(pchar, "questTemp.Slavetrader"))
    {
        if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && chr.location == "Villemstad_tavern")
        {
    		return true;
        }
    }

    return false;
}

bool Slavetrader_FindRat_Habitues_QuestMarkCondition(ref chr)
{
    if (CheckAttribute(pchar, "questTemp.Slavetrader"))
    {
        if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && chr.location == "FortOrange_tavern")
        {
    		return true;
        }
    }

    return false;
}

bool Slavetrader_CheckSlaves_Usurer_QuestMarkCondition(ref chr)
{
    return GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity) >= 0;
}

bool Slavetrader_Wait_Usurer_QuestMarkCondition(ref chr)
{
    return or(pchar.questTemp.Slavetrader == "wait" &&
        GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20, pchar.questTemp.Slavetrader == "waitship");
}

bool Slavetrader_Wait_1_Usurer_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.Slavetrader == "wait_1" &&
        GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30;
}

bool Slavetrader_Wait_2_Usurer_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.Slavetrader == "wait_2" &&
        GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30;
}

bool Slavetrader_Wait_3_Usurer_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.Slavetrader == "wait_3" &&
        GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30;
}

bool Slavetrader_Wait_4_Usurer_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.Slavetrader == "wait_4" &&
        GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4;
}

bool Slavetrader_Wait_5_Usurer_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.Slavetrader == "wait_5" &&
        GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30;
}

bool Slavetrader_Wait_6_Usurer_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.Slavetrader == "wait_6" &&
        GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6;
}

bool Slavetrader_WaitQuest_WDMQuestMarkCondition(string sLocId)
{
    return Slavetrader_Wait_Usurer_QuestMarkCondition(pchar) ||
        Slavetrader_Wait_1_Usurer_QuestMarkCondition(pchar) ||
        Slavetrader_Wait_2_Usurer_QuestMarkCondition(pchar) ||
        Slavetrader_Wait_3_Usurer_QuestMarkCondition(pchar) ||
        Slavetrader_Wait_4_Usurer_QuestMarkCondition(pchar) ||
        Slavetrader_Wait_5_Usurer_QuestMarkCondition(pchar) ||
        Slavetrader_Wait_6_Usurer_QuestMarkCondition(pchar);
}

// Травля крыс
bool pSQ_Begin_WDMQuestMarkCondition(string sLocId)
{
    // Act 1
    return sti(pchar.rank) >= 5;
}

// Пиратская линейка
bool PirLine_Begin_QuestPirate1_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN;
}

bool PirLine_Begin_WDMQuestMarkCondition(string sLocId)
{
    return and(sti(pchar.rank) >= 5, pchar.questTemp.State == "" || sti(pchar.questTemp.CurQuestNumber) > 8 || sti(pchar.questTemp.NationQuest) == SPAIN);
}

bool PL5Hunter_toFirst_Habitues_QuestMarkCondition(ref chr)
{
    if (CheckAttribute(pchar, "questTemp.piratesLine") && CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_1"))
    {
        if (pchar.questTemp.piratesLine == "PL5Hunter_toFirst" && chr.location == pchar.questTemp.piratesLine.Q5.city_1 + "_tavern")
        {
    		return true;
        }
    }

    return false;
}

bool PL5Hunter_toSecond_Habitues_QuestMarkCondition(ref chr)
{
    if (CheckAttribute(pchar, "questTemp.piratesLine") && CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_2"))
    {
        if (pchar.questTemp.piratesLine == "PL5Hunter_toSecond" && chr.location == pchar.questTemp.piratesLine.Q5.city_2 + "_tavern")
        {
    		return true;
        }
    }

    return false;
}

bool PL5Hunter_toThird_Habitues_QuestMarkCondition(ref chr)
{
    if (CheckAttribute(pchar, "questTemp.piratesLine") && CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_3"))
    {
        if (pchar.questTemp.piratesLine == "PL5Hunter_toThird" && chr.location == pchar.questTemp.piratesLine.Q5.city_3 + "_tavern")
        {
    		return true;
        }
    }

    return false;
}

bool PirLine_waiting_Q4_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.piratesLine == "waiting_Q4" &&
        GetQuestPastDayParam("questTemp.piratesLine") > 5 &&
        pchar.questTemp.Sharp != "toPearl";
}

bool PirLine_waiting_Q8_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.piratesLine == "waiting_Q8" &&
        GetQuestPastDayParam("questTemp.piratesLine") > 30;
}

bool PirLine_PanamaToReady_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.piratesLine == "Panama_toReady" && GetQuestPastDayParam("questTemp.piratesLine") > 20;
}

bool PirLine_waiting_Q4_WDMQuestMarkCondition(string sLocId)
{
    return PirLine_waiting_Q4_QuestMarkCondition(pchar);
}

bool PirLine_waiting_Q8_WDMQuestMarkCondition(string sLocId)
{
    return PirLine_waiting_Q8_QuestMarkCondition(pchar);
}

bool PirLine_PanamaToReady_WDMQuestMarkCondition(string sLocId)
{
    return PirLine_PanamaToReady_QuestMarkCondition(pchar);
}

// Остинцы
bool Berglars_FirstTime_QuestMarkCondition(ref chr)
{
    if (CheckAttribute(pchar, "questTemp.tugs.berglarState") && sti(pchar.questTemp.tugs.berglarState) > 1)
    {
        return true;
    }
    return sti(pchar.rank) >= 5 || MOD_SKILL_ENEMY_RATE > 9;
}

bool Berglars_FindOthers_WDMQuestMarkCondition(string sLocId)
{
    if (CheckAttribute(pchar, "questTemp.tugs.berglarState") && sti(pchar.questTemp.tugs.berglarState) >= 4)
    {
        return true;
    }

    return false;
}

//Шарп
bool SharpPearl_Begin_Habitues_QuestMarkCondition(ref chr)
{
    return CheckAttribute(pchar, "questTemp.Sharp") && pchar.questTemp.Sharp == "begin" && sti(pchar.rank) >= 5;
}

bool SharpPearl_Begin_PearlVillages_WDMQuestMarkCondition(string sLocId)
{
    return CheckAttribute(pchar, "questTemp.Sharp") && pchar.questTemp.Sharp == "begin" && sti(pchar.rank) >= 5;
}

bool SharpPearl_SeekSharp_Hostess_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.Sharp == "seekSharp" && GetNpcQuestPastDayWOInit(chr, "quest.SharpTime") > 7 &&
        GetCharacterIndex("Sharp") >= 0 && !LAi_IsDead(&characters[GetCharacterIndex("Sharp")]);
}

bool SharpPearl_SeekSharp_Citizen_QuestMarkCondition(ref chr)
{
    return CheckAttribute(chr, "city") && pchar.questTemp.Sharp.City == chr.city && sti(pchar.questTemp.Sharp.City.rumour);
}

bool SharpPearl_SeekSpy_PearlWorkMan_QuestMarkCondition(ref chr)
{
    if (CheckAttribute(chr, "model"))
    {
        return chr.model == "indsair2" || chr.model == "indsar1";
    }

    return false;
}

// Убить всех нищих
bool ISS_PoorsMurder_Begin_WDMQuestMarkCondition(string sLocId)
{
    return sti(pchar.rank) >= 10;
}

bool ISS_PoorsMurder_Poorman_QuestMarkCondition(ref chr)
{
    bool bGood = and(pchar.questTemp.LSC == "SignOnPoorMurder" || pchar.questTemp.LSC == "PoorIsGood", !CheckAttribute(chr, "quest.talk"));
    bool bBad = pchar.questTemp.LSC == "PoorMurderBegin";

    return bGood || bBad;
}

bool PreparationForISS_Done_Colier_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.LSC == "PreparationsForDepartureLSC" && GetCompanionQuantity(pchar) <= 1;
}

bool PreparationForISS_Return_Colier_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.LSC == "over" && CheckAttribute(chr, "storedLSC");
}

// ГПК
bool LSC_Rumours_Citizen_QuestMarkCondition(ref chr)
{
    // старт начальных квестов
    if (!CheckActiveQuest("ISS_ElisHusband") || !CheckActiveQuest("TakeVineToPrisoner") ||
        !CheckActiveQuest("ISS_takeCandles") || !CheckActiveQuest("LSC_findDekster"))
    {
        return true;
    }
    // ключ адмирала
    if (CheckAttribute(pchar, "questTemp.LSC.private10") && CheckAttribute(pchar, "questTemp.LSC.lostDecster") &&
        pchar.questTemp.LSC.lostDecster == "foundAdmiralBox")
    {
        return true;
    }

    return false;
}

bool LSC_Questions_Citizen_QuestMarkCondition(ref chr)
{
    if (chr.id == "JorgeStouks")
    {
        if (!CheckAttribute(chr, "Dialog.int_quests.l4") && CheckCharacterItem(pchar, "TizerKey")) return true;
        if (!CheckAttribute(chr, "Dialog.int_quests.l6") && !CheckCharacterItem(pchar, "map_LSC")) return true;
    }

    if (chr.id == "LSCBarmen")
    {
        if (!CheckAttribute(chr, "Dialog.int_quests.l6")) return true; // вопрос о Тизере - осн. квест
        if (!CheckAttribute(chr, "Dialog.int_quests.l11") && !CheckCharacterItem(pchar, "map_LSC")) return true;
    }

    if (chr.id == "LSCwaitress")
    {
        if (!CheckAttribute(chr, "Dialog.int_quests.l5") && !CheckCharacterItem(pchar, "map_LSC")) return true;
    }

    return false;
}

bool LSC_Tizer_Barmen_QuestMarkCondition(ref chr)
{
    bool needStoreQuest = pchar.questTemp.LSC == "AfterAdmiral" && GetQuestPastDayParam("questTemp.LSC") > 1 &&
        !CheckActiveQuest("ISS_takeStoreMoney") && !CheckAttribute(pchar, "questTemp.LSC.takeStoreMoney");
    bool ok = pchar.questTemp.LSC == "AfterAdmiral" && IsLSCQuestsProgressCompleted();

    return needStoreQuest || ok;
}

bool LSC_WaitInterception_Barmen_QuestMarkCondition(ref chr)
{
    bool doneRing = CheckAttribute(chr, "quest.doneRing") && CheckAttribute(chr, "quest.startRing");
    bool ok = GetQuestPastDayParam("questTemp.LSC") > 2;

    return doneRing || ok;
}

bool LSC_ToSeekMechanik_Usurer_QuestMarkCondition(ref chr)
{
    return GetCharacterIndex("LSCStBandit3") == -1 || LAi_IsDead(CharacterFromId("LSCStBandit3"));
}

bool LSC_ToUnderwater_Mechanic_QuestMarkCondition(ref chr)
{
    bool givePinion = CheckAttribute(pchar, "questTemp.LSC.immersions.pinion") && sti(pchar.questTemp.LSC.immersions.pinion);
    return CheckCharacterItem(pchar, "Pinion") || givePinion;
}

bool LSC_ToSeekGoods_Mechanic_QuestMarkCondition(ref chr)
{
    return GetCargoGoods(pchar, GOOD_BALLS) >= 100 &&
        GetCargoGoods(pchar, GOOD_GRAPES) >= 100 &&
        GetCargoGoods(pchar, GOOD_KNIPPELS) >= 100 &&
        GetCargoGoods(pchar, GOOD_BOMBS) >= 100 &&
        GetCargoGoods(pchar, GOOD_SAILCLOTH) >= 50 &&
        GetCargoGoods(pchar, GOOD_PLANKS) >= 50 &&
        GetCargoGoods(pchar, GOOD_POWDER) >= 200 &&
        GetCargoGoods(pchar, GOOD_FOOD) >= 200 &&
        GetCargoGoods(pchar, GOOD_WEAPON) >= 50 &&
        GetCargoGoods(pchar, GOOD_MEDICAMENT) >= 50;
}

bool LSC_ToSeekGoods_MalcolmFawn_QuestMarkCondition(ref chr)
{
    bool bPotionwine = CheckCharacterItem(pchar, "potionwine") && sti(pchar.items.potionwine) < 3;
    bool bPotion5 = CheckCharacterItem(pchar, "potion5") && sti(pchar.items.potion5) < 10;
    bool bGoods = !CheckCharacterItem(pchar, "Mineral2") || !CheckCharacterItem(pchar, "potionwine") || !CheckCharacterItem(pchar, "potion5") || bPotionwine || bPotion5;
    bool ok1 = GetCargoGoods(pchar, GOOD_BOMBS) < 100 && bGoods && CheckAttribute(CharacterFromID("ElizaCalvo"), "quest.bombs");

    bool bMineral = CheckCharacterItem(pchar, "Mineral10") && sti(pchar.items.Mineral10) < 10;
    bGoods = !CheckCharacterItem(pchar, "Mineral10") || bMineral;
    bool ok2 = GetCargoGoods(pchar, GOOD_GRAPES) < 100 && bGoods && CheckAttribute(CharacterFromID("LeaToors"), "quest.grapes");

    return ok1 || ok2;
}

//Теночтитлан
bool Teno_Begin_WDMQuestMarkCondition(string sLocID)
{
    return sti(pchar.rank) >= 10; // act 2
}


bool Teno_TakeFire_QuestMarkCondition(ref chr)
{
    return CheckAttribute(pchar, "questTemp.Teno") && pchar.questTemp.Teno == "takeFire";
}

// Зачарованный город
bool MagicCity_Begin_WDMQuestMarkCondition(string sLocID)
{
    return sti(pchar.rank) >= 10; // act 2
}

bool MagicCity_ToSeekSkull_QuestMarkCondition(ref chr)
{
    return CheckCharacterItem(pchar, "SkullAztec");
}

// Найти двуствольный мушкет
bool SeekDoubleMushket_Begin_WDMQuestMarkCondition(string sLocId)
{
    return sti(pchar.rank) >= 10; // act 2
}

// Аскольд
bool Ascold_Begin_WDMQuestMarkCondition(string sLocId)
{
    return sti(pchar.rank) >= 10; // act 3
}

bool Ascold_SeekPowder_Trader_QuestMarkCondition(ref chr)
{
    return GetQuestPastDayParam("questTemp.Ascold") > 3;
}

bool Ascold_SeekPowder_RightCity_ItemTrader_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.Ascold == "Seek_powder" && chr.city == pchar.questTemp.Ascold.MerchantColony;
}

bool Ascold_SeekPowder_RightItemTrader_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.Ascold == "Seek_powder" && chr.city == pchar.questTemp.Ascold.MerchantColony && chr.location.locator == "merchant1";
}

bool Ascold_SeekThreeItems_QuestMarkCondition(ref chr)
{
    return CheckCharacterItem(pchar, "indian19") && CheckCharacterItem(pchar, "indian20") && CheckCharacterItem(pchar, "indian21");
}

bool Ascold_WalkTwoMonth_QuestMarkCondition(ref chr)
{
    return GetQuestPastDayParam("questTemp.Ascold") > 62;
}

bool Ascold_WalkTwoMonth_WDMQuestMarkCondition(string sLocId)
{
    return Ascold_WalkTwoMonth_QuestMarkCondition(pchar);
}

bool Ascold_MummieBegin_QuestMarkCondition(ref chr)
{
    return GetQuestPastDayParam("questTemp.Ascold") > 40;
}

bool Ascold_MummieBegin_WDMQuestMarkCondition(string sLocId)
{
    return Ascold_MummieBegin_QuestMarkCondition(pchar);
}

bool Ascold_SeekRockLetter_QuestMarkCondition(ref chr)
{
    return or(pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && CheckCharacterItem(pchar, "Rock_letter"), pchar.questTemp.Ascold == "Ascold_FoundMummy");
}

bool Ascold_SaveWorld_QuestMarkCondition(ref chr)
{
    return GetCharacterIndex("LeifEricson") == -1;
}

bool Ascold_FreeAzzy_QuestMarkCondition(ref chr)
{
    return CheckCharacterItem(pchar, "Azzy_bottle");
}

bool Ascold_DestrContract_Oliver_QuestMarkCondition(ref chr)
{
    return and(pchar.questTemp.Azzy == "DestrContract" || pchar.questTemp.Azzy == "2DestrContract",
        !CheckAttribute(pchar, "questTemp.Azzy.Oliver"));
}

bool AzzyWishes_Rum_QuestMarkCondition(ref chr)
{
    return GetNpcQuestPastDayParam(chr, "Step_Az8") >= 1;
}

// Корабль-призрак
bool GhostShipQuest_JohnDavy_QuestMarkCondition(ref chr)
{
    bool begin = and(sti(PChar.GenQuest.GhostShip.KillMe) > 0 || sti(PChar.GenQuest.GhostShip.DeadByMe) > 0, !CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins"));
    bool bringPearls = GetCharacterItem(Pchar, "Coins") >= 666 && CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins");
    return begin || bringPearls;
}

bool GhostShipQuest_JohnDavy_WDMQuestMarkCondition(string sLocId)
{
    return and(sti(PChar.GenQuest.GhostShip.KillMe) > 0 || sti(PChar.GenQuest.GhostShip.DeadByMe) > 0, !CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins"));
}

bool GhostShipQuest_Habitues_QuestMarkCondition(ref chr)
{
    bool needCoins = !CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle") &&
         CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins") &&
        !CheckAttribute(chr, "quest.GhostShipHelp") &&
        !CheckAttribute(pchar, "GenQuest.GhostShipWorkId");

    bool begin = !CheckAttribute(pchar , "GenQuest.GhostShip.LastBattleEnd") &&
        !checkAttribute(chr, "GhostShip_Speak_Yet") &&
         pchar.GenQuest.GhostShip.lastspeak_date != LastSpeakDate() &&
         sti(pchar.rank) >= 15; // act 3

    return begin || needCoins;
}

bool GhostShipQuest_NeedCoins_Mayor_QuestMarkCondition(ref chr)
{
    bool bOk = false;
    if (CheckAttribute(chr, "from_sea") && Pchar.location.from_sea == chr.from_sea)
    {
        if (!CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle") &&
             CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins") &&
            GetNpcQuestPastDayWOInit(chr, "GhostShipHelp") > 30 &&
            !CheckAttribute(pchar, "GenQuest.GhostShipWorkId"))
        {
            bOk = true;
        }
    }

    bOk = bOk || CheckAttribute(pchar, "GenQuest.GhostShipDone_" + chr.id);

    return bOk;
}

// Нац. линейки
bool StateLines_Begin_QuestMarkCondition(ref chr)
{
    if (CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(chr.nation))) && CheckAttribute(pchar, "EquipedPatentId"))
    {
        if (pchar.questTemp.NationQuest == "")
        {
            if (pchar.questTemp.piratesLine == "begin" || pchar.questTemp.piratesLine == "over" ||
                pchar.questTemp.piratesLine == "waiting_Q8" || pchar.questTemp.LSC == "over")
            {
                return or(bWorldAlivePause, CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State != ""); // только, если не проходил линейку.
            }
        }
        else
        {
            if (pchar.questTemp.NationQuest == chr.nation)
            {
                return true;
            }
        }
    }

    return false;
}

bool StateLines_Waiting_QuestMarkCondition(ref chr)
{
    if (CheckAttribute(pchar, "questTemp.Waiting_time") && pchar.questTemp.State == "empty")
    {
        return GetQuestPastDayParam("questTemp") >= sti(pchar.questTemp.Waiting_time) && pchar.questTemp.NationQuest == chr.nation;
    }

    return false;
}

bool StateLines_Waiting_WDMQuestMarkCondition(ref chr)
{
    return StateLines_Waiting_QuestMarkCondition(
        CharacterFromID(NationShortName(sti(pchar.questTemp.NationQuest)) + "_guber")
    );
}

bool PortRoyal_JailOff_QuestMarkCondition(ref chr)
{
    return CheckAttribute(chr, "City") && chr.City == "PortRoyal";
}

bool SentJons_JailOff_QuestMarkCondition(ref chr)
{
    return CheckAttribute(chr, "City") && chr.City == "SentJons";
}

bool StateLines_CaptureCity_QuestMarkCondition(ref chr)
{
    // метка будет видна только при штурме города
    if (CheckAttribute(chr, "location"))
    {
        return IsLocationCaptured(chr.location) || CheckAttribute(&Locations[FindLocation(chr.location)], "boarding");
    }
}

// Английская линейка
bool EngLine_Begin_WDMQuestMarkCondition(string sLocId)
{
    return StateLines_Begin_QuestMarkCondition(CharacterFromID("eng_guber"));
}

bool EngLine_SevenTreasures_QuestMarkCondition(ref chr)
{
    return CheckCharacterItem(pchar, "jewelry5") && pchar.questTemp.NationQuest == chr.nation;
}

bool EngLine_11_Guber_QuestMarkCondition(ref chr)
{
    return CheckAttribute(pchar, "questTemp.Q11_Caracas") && CheckAttribute(pchar, "questTemp.Q11_Cumana");
}

// Французская линейка
bool FraLine_Begin_WDMQuestMarkCondition(string sLocId)
{
    return StateLines_Begin_QuestMarkCondition(CharacterFromID("fra_guber"));
}

bool FraLine_3_WaitOneDay_QuestMarkCondition(ref chr)
{
    return CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "Fr3TakeAnna_WaitOneDay" &&
        GetQuestPastDayParam("questTemp") > 0;
}

bool FraLine_8_ThreeCorsairs_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek" && sti(pchar.questTemp.Count) == 3;
}

bool FraLine_8_ThreeCorsairs_JohnMorris_QuestMarkCondition(ref chr)
{
    return CheckCharacterItem(pchar, "ShipsJournal");
}

// Испанская линейка
bool SpaLine_Begin_WDMQuestMarkCondition(string sLocId)
{
    return StateLines_Begin_QuestMarkCondition(CharacterFromID("spa_guber"));
}

bool SpaLine_2_DeSouzaTask_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.State == "Inquisition_afterFrancisco" ||
        CheckAttribute(pchar, "questTemp.State.Store") || CheckAttribute(pchar, "questTemp.State.Usurer");
}

bool SpaLine_3_WaitTwoDays_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.State == "TakeRockBras_WaitTwoDays" && GetQuestPastDayParam("questTemp") > 2;
}

bool SpaLine_3_SeekRocksMoney_QuestMarkCondition(ref chr)
{
    return pchar.questTemp.State == "TakeRockBras_SeekRocksMoney" && sti(pchar.money) > 500000;
}

bool SpaLine_11_Guber_QuestMarkCondition(ref chr)
{
    return CheckAttribute(pchar, "questTemp.Q11_Villemstad") && CheckAttribute(pchar, "questTemp.Q11_Marigo");
}

// Голландская линейка
bool HolLine_Begin_WDMQuestMarkCondition(string sLocId)
{
    return StateLines_Begin_QuestMarkCondition(CharacterFromID("hol_guber"));
}

bool HolLine_2_FortOrangeStore_QuestMarkCondition(ref chr)
{
    string goodName;
    ref refStore = &Stores[FortOrange_STORE];

    goodName = Goods[GOOD_EBONY].Name;
    if (sti(refStore.Goods.(goodName).Quantity) > 0)
        return true;

    goodName = Goods[GOOD_COFFEE].Name;
    if (sti(refStore.Goods.(goodName).Quantity) > 0)
        return true;

    goodName = Goods[GOOD_MAHOGANY].Name;
    if (sti(refStore.Goods.(goodName).Quantity) > 0)
        return true;

    goodName = Goods[GOOD_SANDAL].Name;
    if (sti(refStore.Goods.(goodName).Quantity) > 0)
         return true;

    return false;
}

bool HolLine_3_WormPicarder_Morgan_QuestMarkCondition(ref chr)
{
    if (CheckAttribute(pchar, "questTemp.Hol_Line_AboutWorm"))
    {
        aref aTemp; makearef(aTemp, pchar.questTemp.Hol_Line_AboutWorm);
        int iTemp = GetAttributesNum(aTemp);
        if (iTemp > 2)
        {
            return or(pchar.questTemp.Hol_Line_AboutWorm.Again == false,
                pchar.questTemp.Hol_Line_AboutWorm.Again == true && iTemp > sti(pchar.questTemp.Hol_Line_AboutWorm.Nums));
        }
    }

    return false;
}

bool HolLine_7_WaitTwoHours_QuestMarkCondition(ref chr)
{
    return CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "DelivLettTortuga_WaitTwoHours" &&
        GetQuestPastTimeParam("questTemp") > 1;
}

bool HolLine_7_DelivLettTortuga_WaitingNews_QuestMarkCondition(ref chr)
{
    return CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "DelivLettTortuga_WaitingNews" &&
        GetQuestPastDayParam("questTemp") > 30;
}

bool HolLine_8_SeekBible_Horse_QuestMarkCondition(ref chr)
{
    return chr.id == "HorseGen_"+FindLocation("FortFrance_Brothel")+"_1";
}

bool HolLine_9_TakeThreeShips_toAbordage_QuestMarkCondition(ref chr)
{
    int tempQty = 0;
    for (int i=1; i<=COMPANION_MAX; i++)
    {
        int chComp = GetCompanionIndex(pchar,i);
        if(chComp != -1)
        {
            ref sld = GetCharacter(chComp);
            if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MANOWAR)
            {
                return true;
            }
        }
    }

    return false;
}

//Линейка Блада
bool CapBloodLine_HugtorpTrouble_QuestMarkCondition(ref chr)
{
    return GetCharacterItem(pchar,"HugtorpRing") > 0;
}

bool CapBloodLine_ReadyToEscape_Pitt_QuestMarkCondition(ref chr)
{
    return CheckAttribute(Pchar, "questTemp.CapBloodLine.Officer") && Pchar.questTemp.CapBloodLine.Officer == 4 &&
        Pchar.questTemp.CapBloodLine.stat == "ReadyToEscape";
}

bool CapBloodLine_QuestSmuggler_QuestMarkCondition(ref chr)
{
    return Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape" && sti(Pchar.reputation) >= 50;
}

bool CapBloodLine_ItemTrader_QuestMarkCondition(ref chr)
{
    return or(Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape", Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1") &&
        CheckAttribute(chr, "quest.bGoodMerch") && sti(Pchar.reputation) >= 55;
}

bool CapBloodLine_StidRing_QuestSmuggler_QuestMarkCondition(ref chr)
{
    return GetCharacterItem(pchar,"MsStid_ring") > 0;
}

bool CapBloodLine_SpainSpy_Soldier_QuestMarkCondition(ref chr)
{
    return Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape2_1";
}

bool CapBloodLine_WaitMoney_Griffin_QuestMarkCondition(ref chr)
{
    return makeint(pchar.money) >= sti(Pchar.questTemp.CapBloodLine.iMoney);
}

bool CapBloodLine_WaitWeapons_Griffin_QuestMarkCondition(ref chr)
{
    return Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1_3" && GetQuestPastTimeParam("questTemp.CapBloodLine.GriffinTime") >= 1;
}

bool CapBloodLine_NeedMoney_Nettl_QuestMarkCondition(ref chr)
{
    return makeint(pchar.money) >= 25000 && Pchar.questTemp.CapBloodLine.TalkWithNettl == true;
}

// Изабелла
bool RomanticLine_Begin_WDMQuestMarkCondition(string sLocId)
{
    return sti(pchar.rank) >= 15 && pchar.sex != "woman"; // act 3
}

bool RomanticLine_Begin_QuestMarkCondition(ref chr)
{
    return pchar.sex != "woman";
}

bool RomanticLine_ShipToCumana_Citizen_QuestMarkCondition(ref chr)
{
    return CheckAttribute(chr, "city") && chr.city == "Cumana" &&
        chr.location != "Cumana_church";
}

// Кольцо Жозефины Лодет
bool PDM_Poteryanoe_Koltso_UznatLichnost_QuestMarkCondition(ref chr)
{
    return CheckAttribute(pchar, "questTemp.PDM_PK_UznatLichnost") &&
        pchar.questTemp.PDM_PK_UznatLichnost == "UznatLichnost" &&
        CheckAttribute(chr, "city") && "PortPax" == chr.city &&
        chr.location != "PortPax_church";
}

bool PDM_Poteryanoe_Koltso_IshemKoltso_QuestMarkCondition(ref chr)
{
    return CheckAttribute(pchar, "questTemp.PDM_PK_IshemKoltso") &&
        CheckAttribute(chr, "city") && "SantoDomingo" == chr.city &&
        chr.location != "SantoDomingo_church";
}

// Невыносимая жара
bool PDM_Proklyataya_Jara_MaltieOfficer_QuestMarkCondition(ref chr)
{
    return CheckAttribute(pchar, "questTemp.PDM_PJ_SS");
}

// Опасный груз
bool zpq_Begin_WDMQuestMarkCondition(string sLocId)
{
    return sti(pchar.rank) >= 15; // act 3
}

bool zpq_Begin_AmmoOff_QuestMarkCondition(ref chr)
{
    return CheckAttribute(chr, "city") && chr.city == "Cumana";
}

bool zpq_WaitPowder_AmmoOff_QuestMarkCondition(ref chr)
{
    return CheckAttribute(chr, "city") && chr.city == "Cumana" &&
        pchar.questTemp.zpq == "begin" &&
        GetSquadronGoods(pchar, GOOD_POWDER) >= 50000 &&
        GetQuestPastDayParam("pchar.questTemp.zpq") >= 7;
}

// ========== Генераторы ===========
bool Gen_Smuggler_Treasure_QuestMarkCondition(ref chr)
{
    bool ok = (GetCharacterItem(Pchar, "map_part1")>0) && (GetCharacterItem(Pchar, "map_part2")>0);
    return GetCharacterItem(Pchar, "map_full") <= 0 && !ok;
}

// квесты дворян
bool Gen_Nobelman_Donation_QuestMarkCondition(ref chr)
{
	return chr.quest.meeting == "0" && CheckAttribute(chr, "quest.donation") && GetCharacterEquipSuitID(pchar) != "suit_1";
}

bool Gen_Nobelman_Lombard_Begin_QuestMarkCondition(ref chr)
{
	return chr.quest.meeting == "0" && CheckAttribute(chr, "quest.lombard") &&
		!CheckAttribute(pchar, "GenQuest.Noblelombard") && GetCharacterEquipSuitID(pchar) != "suit_1";
}

bool Gen_Nobelman_Lombard_Waiting_QuestMarkCondition(ref chr)
{
	return CheckAttribute(pchar, "GenQuest.Noblelombard.Regard") || pchar.GenQuest.Noblelombard == "fail";
}

bool Gen_Nobelman_Lombard_UsurerRegard_QuestMarkCondition(ref chr)
{
	return CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && chr.city == pchar.GenQuest.Noblelombard.City;
}

bool Gen_Nobelman_Slaves_Begin_QuestMarkCondition(ref chr)
{
	return chr.quest.meeting == "0" && CheckAttribute(chr, "quest.slaves") &&
		!CheckAttribute(&Colonies[FindColony(chr.city)], "questslaves") && GetCharacterEquipSuitID(pchar) != "suit_1";
}

bool Gen_Nobelman_Slaves_Waiting_QuestMarkCondition(ref chr)
{
	return GetNpcQuestPastDayParam(chr, "slaves_date") >= 180 || GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(chr.quest.slaves.qty);
}
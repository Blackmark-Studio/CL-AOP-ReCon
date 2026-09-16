
void GenerateRumour()
{
    string RumText;
    ref CurRum;

	///////////////////////////////////////Золотой флот///////////////////////////////////////////////
    // > Оба порта должны быть испанскими и не в осаде
    int iHavana     = FindColony("Havana");
    int iPortoBello = FindColony("PortoBello");

    if (iHavana != -1 && iPortoBello != -1 && !isGoldFleet)
    {
        bool bSpanishPorts = sti(Colonies[iHavana].nation) == SPAIN && sti(Colonies[iPortoBello].nation) == SPAIN;
        bool bNoSiege      = !CheckAttribute(&Colonies[iHavana], "Siege") && !CheckAttribute(&Colonies[iPortoBello], "Siege");

        if (bSpanishPorts && bNoSiege && rand(5) == 0)
        {
            GoldMonth = XI_ConvertString("target_month_"+GetAddingDataMonth(0, 6, 0));
            Log_TestInfo("loading GoldFleet " + GoldMonth);

            isGoldFleet = true;
            string sQuest = "GenerateGoldFleet";
            SetTimerCondition(sQuest, 0, 6, 0, false);
            pchar.quest.(sQuest).win_condition = "StartGoldFleet";
            pchar.quest.(sQuest).function= "StartGoldFleet";

            AddTemplRumour("Init_GoldFleet", id_counter+1);
        }
    }
    //////////////////////////////////////Наводка на купца/////////////////////////////////////////////
    ref MerPrm;
    makeref(MerPrm, MerchantParam);
    if (!CheckAttribute(MerPrm, "active") || MerPrm.active == false)
    {
        // > Держим в очереди не больше одной копии (раньше очередь забивалась копиями на все 55 слотов и вытесняла настоящие слухи)
        bool bMerchantQueued = false;

        for (int iRum = 0; iRum < MAX_RUMOURS; iRum++)
        {
            if (Rumour[iRum].text != "" && Rumour[iRum].event == "MerchantOnMap")
            {
                bMerchantQueued = true;
                break;
            }
        }

        if (!bMerchantQueued) AddTemplRumour("MerchantOnMap", id_counter+1);
    }
    ////////////////////////////////////////Цены в магазине////////////////////////////////////////////
    if (rand(5)==0) AddTemplRumour("GetColonyPrices", id_counter+1);
    //////////////////////////////////////////////////////////////////////////////////////////////////
}

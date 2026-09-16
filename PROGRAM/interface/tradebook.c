// BOAL меню торговли
#event_handler("Control Activation", "ProcessInterfaceControls");// гуляем по меню кнопками Q и E

string CurTable, CurRow;

void InitInterface(string iniName)
{
    InterfaceStack.SelectMenu_node = "LaunchTradeBook"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleTradeBook";
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("TableSelectChange", "TableSelectChange", 0);
    SetEventHandler("CheckShowInfoWindow","CheckShowInfoWindow",0);
    SetEventHandler("MouseRClickUp","HideInfoWindow",0);

	// доп инфа в шапку --->
	SetFormatedText("WEIGHT", FloatToString(GetItemsWeight(pchar), 1) + " / " + GetMaxItemsWeight(pchar));
	SetFormatedText("MONEY", FindMoneyString(sti(pchar.money)));
	SetFormatedText("CURRENT_DATE_CAPTION", GetDateString() + " "+ GetTimeString());
	// <--
    
//    XI_RegistryExitKey("IExit_F2");
    FillPriceListTown("TABLE_CITY");
	SetAlertMarks(pchar);
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("TableSelectChange", "TableSelectChange");
    DelEventHandler("CheckShowInfoWindow", "CheckShowInfoWindow");
    DelEventHandler("MouseRClickUp","HideInfoWindow");
    
	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
		case "I_CHARACTER_2":
			if(comName=="click")
			{
			    nodName = "I_CHARACTER";
			}
		break;
		case "I_SHIP_2":
			if(comName=="click")
			{
			    nodName = "I_SHIP";
			}
		break;
		case "I_QUESTBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_QUESTBOOK";
			}
		break;
		case "I_TRADEBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_TRADEBOOK";
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
			    nodName = "I_ITEMS";
			}
		break;
	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_CHARACTER" || nodName == "I_SHIP" ||
	    nodName == "I_QUESTBOOK" || nodName == "I_TRADEBOOK" ||
		nodName == "I_NATIONS" || nodName == "I_ITEMS")
	{
		if(comName=="click")
		{
            InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			return;
		}
	}
	// boal new menu 31.12.04 -->
}
//  таблица: город, местоположение, актуальность
void FillPriceListTown(string _tabName)
{
	string  cityId, attr2, firstId;
    int     i, cn, n;
    ref     nulChr;
    string  row;
    aref    rootItems;
    aref    curItem;
    ref     rCity;
    int     iFreeStore;                          // KZ FreeStores > свободный магазин
    string  sTownName, sIslandName, sNationPic;
    
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = XI_ConvertString("nation");
    GameInterface.(_tabName).hr.td1.scale = 0.77;
	GameInterface.(_tabName).hr.td2.str = XI_ConvertString("ColonyLevel4");
	GameInterface.(_tabName).hr.td2.scale = 0.8;
	GameInterface.(_tabName).hr.td3.str = UpperFirst(XI_ConvertString("PsHeroLocation"));
	GameInterface.(_tabName).hr.td3.scale = 0.7;
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("Relevance");
	GameInterface.(_tabName).hr.td4.scale = 0.7;
    // <--
    nulChr = &NullCharacter;
    makearef(rootItems, nulChr.PriceList);  // тут живут ИД города и служ. инфа.
    n = 1;
    firstId = "";
    for (i=0; i<GetAttributesNum(rootItems); i++)
    {
        row = "tr" + n;
		curItem = GetAttributeN(rootItems, i);
		cityId = GetAttributeName(curItem);
		// FreeStores > ветка прайса может принадлежать не колонии, а свободному магазину - показываем и его
		cn = FindColony(cityId);
		iFreeStore = -1;
		if (cn == -1) iFreeStore = FindFreeStore(cityId);

		if (cn != -1 || iFreeStore >= 0)
		{
			if (cn != -1)
			{
				rCity       = GetColonyByIndex(cn);
				sNationPic  = Nations[sti(rCity.nation)].Name;
				sTownName   = GetConvertStr(cityId + " Town", "LocLables.txt");
				sIslandName = GetConvertStr(rCity.islandLable, "LocLables.txt");
			}
			else
			{
				sNationPic  = Nations[PIRATE].Name;
				sIslandName = "";
				sTownName   = GetStoreTitleName(&Stores[iFreeStore]);
				if (CheckAttribute(&Stores[iFreeStore], "Island") && Stores[iFreeStore].Island != "")
					sIslandName = GetConvertStr(Stores[iFreeStore].Island, "LocLables.txt");
				if (sTownName == "") sTownName = cityId;
			}

			if (n == 1) firstId = cityId;
			GameInterface.(_tabName).(row).UserData.CityID  = cityId;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group  = "NATIONS";
			GameInterface.(_tabName).(row).td1.icon.image  = sNationPic;
			GameInterface.(_tabName).(row).td1.icon.width  = 26;
		    GameInterface.(_tabName).(row).td1.icon.height = 26;
		    GameInterface.(_tabName).(row).td1.icon.offset = "3, 3";
			GameInterface.(_tabName).(row).td2.str = sTownName;
			GameInterface.(_tabName).(row).td2.scale = 0.85;
			GameInterface.(_tabName).(row).td3.str = sIslandName;
			GameInterface.(_tabName).(row).td3.scale = 0.8;
			GameInterface.(_tabName).(row).td4.scale = 0.75;
			if (CheckAttribute(nulChr, "PriceList." + cityId + ".AltDate"))
		    {
		        GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(cityId).AltDate;
		    }
		    else
		    {
		        GameInterface.(_tabName).(row).td4.str = "??.??.????";
		    }
			n++;
		}
	}
	//if (n > 1) GameInterface.(_tabName).select = 1;
	Table_UpdateWindow(_tabName);
	FillPriceList("TABLE_GOODS", firstId);
}
//  таблица
// картинка, название, картинка экспорта, продажа, покупка, колво, пачка, вес пачки
void FillPriceList(string _tabName, string  attr1)
{
    string  sGoods;
    int     i, n;
    ref     nulChr;
    string  row;
    int tradetype, iColor;
    nulChr = &NullCharacter;
    DeleteAttribute(&GameInterface, _tabName); //Чтобы убрать товары, которых нет в этой колонии
    // шапка -->
    GameInterface.(_tabName).select = 0;
    GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Good name");
    GameInterface.(_tabName).hr.td1.scale = 0.8;
    GameInterface.(_tabName).hr.td2.str = XI_ConvertString("Name");
    GameInterface.(_tabName).hr.td2.scale = 0.85;
	GameInterface.(_tabName).hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.(_tabName).hr.td3.scale = 0.8;
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("Price buy");
	GameInterface.(_tabName).hr.td4.scale = 0.8;
	GameInterface.(_tabName).hr.td5.str = XI_ConvertString("In the store");
	GameInterface.(_tabName).hr.td5.scale = 0.8;
	GameInterface.(_tabName).hr.td6.str = XI_ConvertString("Pack");
	GameInterface.(_tabName).hr.td6.scale = 0.8;
	GameInterface.(_tabName).hr.td7.str = XI_ConvertString("PackWeight");
	GameInterface.(_tabName).hr.td7.scale = 0.8;
	if (attr1 != "")
	{
	    // <--
	    n = 1;
	    for (i = 0; i < GOODS_QUANTITY; i++)
	    {
	        row = "tr" + n;
	        sGoods = "Gidx" + i;
	        tradetype = sti(nulChr.PriceList.(attr1).(sGoods).TradeType);
	        if (tradetype == TRADE_TYPE_CANNONS && !bBettaTestMode) continue; // не пушки

			iColor = argb(255,255,255,255);
			switch(tradeType)
			{
				case TRADE_TYPE_EXPORT:		iColor = argb(255,196,255,196); break;
				case TRADE_TYPE_IMPORT:		iColor = argb(255,196,196,255); break;
				case TRADE_TYPE_CONTRABAND:	iColor = argb(255,255,196,196); break;
				//case TRADE_TYPE_SPECIAL:	iColor = argb(255,255,192,255); break;
			}

	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Sell")) //гг продаёт
				GameInterface.(_tabName).(row).td4.str = nulChr.PriceList.(attr1).(sGoods).Sell;
	        else if (i == GOOD_PINCTADA) continue; //HardCoffee молюсков показывать только после сделки
	        else GameInterface.(_tabName).(row).td4.str = "???";

	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Buy")) //гг покупает
				 GameInterface.(_tabName).(row).td3.str = nulChr.PriceList.(attr1).(sGoods).Buy;
	        else GameInterface.(_tabName).(row).td3.str = "???";

	        if (CheckAttribute(nulChr, "PriceList." + attr1 + "." + sGoods + ".Qty"))
				GameInterface.(_tabName).(row).td5.str = nulChr.PriceList.(attr1).(sGoods).Qty;
	        else GameInterface.(_tabName).(row).td5.str = "????";

            GameInterface.(_tabName).(row).UserData.ID = Goods[i].name;
            GameInterface.(_tabName).(row).UserData.IDX = i;
            
	        GameInterface.(_tabName).(row).td1.icon.group = "GOODS";
			GameInterface.(_tabName).(row).td1.icon.image = Goods[i].name;
			GameInterface.(_tabName).(row).td1.icon.offset = "1, 0";
			GameInterface.(_tabName).(row).td1.icon.width = 32;
			GameInterface.(_tabName).(row).td1.icon.height = 32;
			GameInterface.(_tabName).(row).td1.textoffset = "30,0";
			GameInterface.(_tabName).(row).td1.str = XI_ConvertString(Goods[i].name);
			GameInterface.(_tabName).(row).td1.scale = 0.85;
			GameInterface.(_tabName).(row).td1.color = iColor;

	        GameInterface.(_tabName).(row).td2.icon.group = "TRADE_TYPE";
			GameInterface.(_tabName).(row).td2.icon.image = "ico_" + nulChr.PriceList.(attr1).(sGoods).TradeType;
			GameInterface.(_tabName).(row).td2.icon.offset = "0, 1";
			GameInterface.(_tabName).(row).td2.icon.width = 16;
			GameInterface.(_tabName).(row).td2.icon.height = 28;

	        GameInterface.(_tabName).(row).td6.str = Goods[i].Units;
			GameInterface.(_tabName).(row).td7.str = Goods[i].Weight;
	        n++;
	    }
    }
    Table_UpdateWindow(_tabName);
}

void TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
 	//NullSelectTable("TABLE_CITY");
    NullSelectTable("TABLE_GOODS");
    // перерисуем "прайс"
    if (CurTable == "TABLE_CITY")
    {
    	FillPriceList("TABLE_GOODS", GameInterface.(CurTable).(CurRow).UserData.CityID);
    }
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

// Hokkins: проверим надо ли показывать ShowInfoWindow() -->
void CheckShowInfoWindow()
{
	if(GameInterface.TABLE_CITY.tr1.UserData.CityIDX == 0) return;
	
	ShowInfoWindow();
}
// Hokkins: <--

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		case "TABLE_GOODS":
		    sGroup = "GOODS";
		    sGroupPicture = GameInterface.(CurTable).(CurRow).UserData.ID;
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    iItem = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
		    sText1  = GetAssembledString(GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID + "_descr", "GoodsDescribe.txt"), &Goods[iItem]);
		    sText2 = XI_ConvertString("TradeInterfaceDescr_7") + "\n\n" + ColorText(LowerFirst(XI_ConvertString("Imports")) + "     ", "import") + ColorText(LowerFirst(XI_ConvertString("Contrabands")) + "     ", "contra") + ColorText(LowerFirst(XI_ConvertString("Exports")) + "\n", "export");
		break;

		case "WEIGHT":
			sHeader = XI_ConvertString("Weight");
			sText1 = GetRPGText("Weight_hint");
		break;

		case "MONEY":
			sHeader = XI_ConvertString("Money");
			sText1 = GetRPGText("Money_hint");
		break;
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,255,255), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);

}
void HideInfoWindow()
{
	CloseTooltip();
}

// гуляем по меню кнопками Q и E
void ProcessInterfaceControls()
{
	string controlName = GetEventData();

	if (controlName == "InterfaceGoLeft")
	{
		IDoExit(RC_INTERFACE_TO_LOGBOOK);
	}
	if (controlName == "InterfaceGoRight")
	{
		IDoExit(RC_INTERFACE_TO_ITEMS);
	}
}
////    boal 31/08/06 Cannons
string totalInfo = "";
int TableSelect = 0;
int nCurScrollNum = 0;
int iShipCapacity;
int iTotalSpace;
float fShipWeight, fStoreWeight;
int iMaxGoodsStore = 50000;

bool bShowChangeWin = false;
int BuyOrSell = 0; // 1-buy -1 sell
string sChrId;
ref refStore, refCharacter, refShipChar;
int iShipQty, iStoreQty, iShipPrice, iStorePrice, iUnits;
float fWeight;
int iCurGoodsIdx;

void InitInterface_R(string iniName, ref pStore)
{
	StartAboveForm(true);

	refStore = pStore;
	refCharacter = pchar;
	if (CheckAttribute(pchar, "shiptrade.character"))
	{
		refShipChar = CharacterFromID(pchar.shiptrade.character);
	}

	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("In the hold");
	aref arHR; makearef(arHR, GameInterface.TABLE_LIST.hr);
	arHR.td1.scale = 0.85;
	arHR.td2.str = XI_ConvertString("weight");
	arHR.td2.scale = 0.85;
	arHR.td3.str = XI_ConvertString("Price sell");
	arHR.td3.scale = 0.85;
	arHR.td4.str = XI_ConvertString("Good name");
	arHR.td4.scale = 0.85;
	arHR.td5.str = XI_ConvertString("Price buy");
	arHR.td5.scale = 0.85;
	arHR.td6.str = XI_ConvertString("weight") + XI_ConvertString("pcs");
	arHR.td6.scale = 0.85;
	arHR.td7.str = XI_ConvertString("Damage");
	arHR.td7.scale = 0.85;
	arHR.td8.str = XI_ConvertString("Fire range2") + "\n/" + XI_ConvertString("Time:");
	arHR.td8.scale = 0.85;
	if (IsSeaTradeStore(refStore))
	{
		arHR.td9.str = XI_ConvertString("In the hold");
	}
	else
	{
		arHR.td9.str = XI_ConvertString("In the shipyard");
	}
	arHR.td9.scale = 0.85;

	FillShipsScroll();

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);

	CreateString(true, "ShipName", "", FONT_NORMAL, COLOR_MONEY, 400, 98, SCRIPT_ALIGN_CENTER, 0.7);

	SetShipWeight();
	SetDescription();

	SetEventHandler("InterfaceBreak", "ProcessBreakExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("ievnt_command", "ProcCommand", 0);
	SetEventHandler("evntDoPostExit", "DoPostExit", 0);

	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("MouseRClickUP", "EndTooltip", 0);
	SetEventHandler("ShowHelpHint", "ShowHelpHint", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);

	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON", "ADD_BUTTON", 0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);
	SetEventHandler("CheckButtonChange", "procCheckBoxChange", 0);
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);

	SetEventHandler("frame", "ProcessFrame", 1);

	//SetEventHandler("RefreshTable","RefreshTable",0);
	//PostEvent("RefreshTable", 1000);

	if (IsSeaTradeStore(refStore))
	{
		SetFormatedText("MAIN_CAPTION", XI_ConvertString("Ship") + ": '" + refShipChar.ship.name + "'");
		SetNewPicture("OTHER_PICTURE", "interfaces\portraits\256\face_" + refShipChar.FaceId + ".tga");
	}
	else
	{
		SetFormatedText("MAIN_CAPTION", XI_ConvertString("titleShipyard") + "-  " + GetStoreTitleName(refStore));
	}

	if (!CheckAttribute(&InterfaceStates, "TradeAssistant"))
		InterfaceStates.TradeAssistant = "0";

	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TRADEASSISTANT_CHECKBOX", 2, 1, sti(InterfaceStates.TradeAssistant));
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
}

void ProcessCancelExit()
{
	if (bShowChangeWin)
	{
		EndTooltip();
	}
	else
	{
		IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
	}
}

void IDoExit(int exitCode)
{
	EndAboveForm(true);

	DelEventHandler("InterfaceBreak", "ProcessBreakExit");
	DelEventHandler("exitCancel", "ProcessCancelExit");
	DelEventHandler("ievnt_command", "ProcCommand");
	DelEventHandler("evntDoPostExit", "DoPostExit");

	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("MouseRClickUP", "EndTooltip");
	DelEventHandler("ShowHelpHint", "ShowHelpHint");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame", "ProcessFrame");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON", "ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	DelEventHandler("CheckButtonChange", "procCheckBoxChange");
	DelEventHandler("OnHeaderClick", "OnHeaderClick");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);

}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if (sNodName == "TRADEASSISTANT_CHECKBOX")
	{
		InterfaceStates.TradeAssistant = bBtnState;
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TRADEASSISTANT_CHECKBOX", 2, 1, sti(InterfaceStates.TradeAssistant));
		AddToTable();
	}
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch (nodName)
	{
		case "QTY_OK_BUTTON":
			if (comName == "leftstep")
			{
				ADD_BUTTON();
			}
			if (comName == "rightstep")
			{
				REMOVE_BUTTON();
			}
			if (comName == "speedleft")
			{
				ADD_ALL_BUTTON();
			}
			if (comName == "speedright")
			{
				REMOVE_ALL_BUTTON();
			}
		break;

		case "QTY_CANCEL_BUTTON":
			if (comName == "leftstep")
			{
				ADD_BUTTON();
			}
			if (comName == "rightstep")
			{
				REMOVE_BUTTON();
			}
			if (comName == "speedleft")
			{
				ADD_ALL_BUTTON();
			}
			if (comName == "speedright")
			{
				REMOVE_ALL_BUTTON();
			}
		break;

		case "TABLE_LIST":
			if (comName == "leftstep")
			{
				ADD_BUTTON();
			}
			if (comName == "rightstep")
			{
				REMOVE_BUTTON();
			}
			if (comName == "speedleft")
			{
				ADD_ALL_BUTTON();
			}
			if (comName == "speedright")
			{
				REMOVE_ALL_BUTTON();
			}
		break;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void CalculateInfoData()
{
	AddToTable();
	//SetCurrentNode("B_OK");
	if (CheckAttribute(&GameInterface, "TABLE_LIST.tr1.index"))
		ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
}

void AddToTable()
{
	int n, i;
	string row, sGood;
	int tradeType, iColor, iStoreQ, iShipQ;
	aref refGoods, rGood, arRow, arTd4;
	bool bStoreSells, bStoreBuys;

	bool bSea    = IsSeaTradeStore(refStore);
	bool bAssist = CheckAttrValue(&InterfaceStates, "TradeAssistant", "1") && GetRemovable(refCharacter);
	int  iShipCannType = CANNON_TYPE_NONECANNON;
	int  iMaxCaliber   = 0;

	if (bAssist)
	{
		iMaxCaliber = GetMaximumCaliber(refCharacter);
		// fix > Ship.Cannons.Type помнит калибр и с пустыми бортами, поэтому одного атрибута мало
		if (GetIntactCannonQuantity(refCharacter) > 0) iShipCannType = GetCaracterShipCannonsType(refCharacter);
	}

	n = 1;
	Table_Clear("TABLE_LIST", false, true, false);

	for (i = GOOD_CANNON_3; i <= GOOD_CANNON_48; i++)
	{
		makearef(rGood, Goods[i]);
		sGood = rGood.name;
		makearef(refGoods, refStore.Goods.(sGood));
		tradeType = MakeInt(refGoods.TradeType);
		//if (tradeType != TRADE_TYPE_CANNONS) continue; // не пушки

		iShipQ = GetCargoGoods(refCharacter, i);

		if (!bSea)
			iStoreQ = GetStoreGoodsQuantity(refStore, i);
		else
			iStoreQ = GetCargoGoods(refShipChar, i);

		if (iStoreQ < 0)
		{
			iStoreQ = 0;
			refGoods.quantity = 0;
		}
		if (iStoreQ == 0 && iShipQ == 0) continue; // только не нули

		// > запрет торговли этим товаром в этом магазине
		bStoreSells = StoreCanSellGood(refStore, i); // > ГГ может купить
		bStoreBuys  = StoreCanBuyGood(refStore, i);  // > ГГ может продать
		if (!bStoreSells && !bStoreBuys && IsStoreGoodHidden(refStore, i)) continue; // > строки нет ни у одной стороны

		row = "tr" + n;
		makearef(arRow, GameInterface.TABLE_LIST.(row));

		arRow.index = i;
		arRow.td1.str = "" + iShipQ;
		arRow.td2.str = GetGoodWeightByType(i, iShipQ);
		arRow.td6.str = rGood.Weight;
		arRow.td7.str = "x" + FloatToString(stf(rGood.DamageMultiply), 1);
		arRow.td8.str = sti(rGood.FireRange) + " / " + sti(rGood.ReloadTime);
		arRow.td9.str = iStoreQ;

		iColor = argb(255, 255, 255, 255);
		if (checkAttribute(refCharacter, "ship.cargo.goods." + sGood + ".isquest"))
			iColor = argb(255, 255, 192, 255);

		// KZ > цветовая дифференциация орудий в ассортименте верфиста
		if (bAssist)
		{
			int iCannonIdx = sti(rGood.CannonIdx);
			if (iShipCannType != CANNON_TYPE_NONECANNON && iShipCannType == iCannonIdx)
				iColor = argb(255, 218, 165, 32); // > эти орудия сейчас установлены
			else if (iMaxCaliber < GetCannonCaliber(iCannonIdx))
				iColor = argb(255, 169, 169, 169); // > нельзя установить на выделенный корабль
		}
		// KZ <

		if (!bStoreSells && !bStoreBuys) iColor = GetStoreGoodBanColor(refStore, i); // > товар вне торговли красим отдельно

		makearef(arTd4, arRow.td4);
		arTd4.icon.group = "GOODS";
		arTd4.icon.image = sGood;
		arTd4.icon.offset = "0, 0";
		arTd4.icon.width = 29;
		arTd4.icon.height = 29;
		arTd4.textoffset = "25,0";
		arTd4.str = XI_ConvertString(sGood);
		arTd4.color = iColor;
		arTd4.scale = 0.85;

		if (!bStoreBuys || tradeType == TRADE_TYPE_CONTRABAND)
		{
			arRow.td5.str = "-"; // > магазин этот товар не покупает
		}
		else
		{
			int iSell = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, pchar, 1);
			if (bSea) // в море
			{
				iSell = iSell / 2;
				if (iSell < 1) iSell = 1;
			}
			arRow.td5.str = iSell;
		}
		if ((tradeType == TRADE_TYPE_AMMUNITION) && bSea)
			arRow.td3.str = "-"; // нельзя купить в море
		else if (!bStoreSells)
			arRow.td3.str = "-"; // > магазин этот товар не продаёт
		else
			arRow.td3.str = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_BUY, pchar, 1);
		n++;
	}
	NextFrameRefreshTable();
}

void NextFrameRefreshTable()
{
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_LIST", 0);
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	Table_UpdateWindow(sControl);
}

void ChangePosTable()
{
}

void ShowHelpHint()
{
	string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	if (!bShowChangeWin)
	{
		// покажем помощь по работе с формой
		sHeader = XI_ConvertString("TradeInterfaceTitle");
		sText1 = XI_ConvertString("TradeInterfaceDescr_1") + newStr() +
				XI_ConvertString("TradeInterfaceDescr_2") + newStr() +
					XI_ConvertString("TradeInterfaceDescr_3") + newStr() +
						XI_ConvertString("TradeInterfaceDescr_4") + newStr() +
							XI_ConvertString("TradeInterfaceDescr_5");

		sText2 = XI_ConvertString("TradeInterfaceDescr_6");

		sText3 = XI_ConvertString("TradeInterfaceDescr_7") + "\n\n" + ColorText(LowerFirst(XI_ConvertString("Imports")) + "     ", "import") + ColorText(LowerFirst(XI_ConvertString("Contrabands")) + "     ", "contra") + ColorText(LowerFirst(XI_ConvertString("Exports")) + "\n\n", "export") +
				XI_ConvertString("TradeInterfaceDescr_8") + "\n\n" +
					ColorText(XI_ConvertString("CannonsTradeInterfaceDescr_1") + "\n", "white") + ColorText(XI_ConvertString("CannonsTradeInterfaceDescr_2") + "\n", "darkgray") +
						ColorText(XI_ConvertString("CannonsTradeInterfaceDescr_3") + "\n", "goldenrod");

		CreateTooltip("#" + sHeader, sText1, argb(255, 255, 255, 255), sText2, argb(255, 192, 192, 192), sText3, argb(255, 255, 255, 255), "", argb(255, 255, 255, 255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void EndTooltip()
{
	CloseTooltip(); // всегда убирать, если был
	GameInterface.qty_edit.str = 0;
	SetShipWeight();
	SetVariable();
	SetCurrentNode("TABLE_LIST");
	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	bShowChangeWin = false;
}

void ShowItemInfo()
{
	if (bShowChangeWin) // жмем окей, когда курсор на таблице
	{
		TransactionOK();
	}
	else
	{
		BuyOrSell = 0;
		ChangeQTY_EDIT();

		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		bShowChangeWin = true;
		if (GetRemovable(refCharacter))
		{
			SetSelectable("QTY_OK_BUTTON", true);
		}
		else
		{
			SetSelectable("QTY_OK_BUTTON", false);
		}
	}
}

void RefreshTable()
{
	PostEvent("RefreshTable", 100);

	if (TableSelect != sti(GameInterface.TABLE_LIST.select))
	{
		TableSelect = sti(GameInterface.TABLE_LIST.select);
		ChangePosTable();
	}
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
	TableSelect = iSelected;
	string sRow = "tr" + (iSelected);
	SetShipWeight();
	SetVariable();
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sRow).index));
}

void FillShipsScroll()
{
	nCurScrollNum = -1;
	FillScrollImageWithCompanionShips("SHIPS_SCROLL", 4);

	if (!CheckAttribute(&GameInterface, "SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}
}

void SetVariable()
{
	string sText, sTextSecond;

	iShipCapacity = GetCargoMaxSpace(refCharacter);
	sText = iShipCapacity;

	sText = makeint(fShipWeight) + " / " + sText;
	SetFormatedText("CAPACITY", XI_ConvertString("Capacity") + "\n" + sText);

	iTotalSpace = iMaxGoodsStore;
	string sMaxGoodsStore;
	if (IsSeaTradeStore(refStore))
	{
		iTotalSpace = sti(RealShips[sti(refShipChar.ship.type)].capacity);
		sMaxGoodsStore = XI_ConvertString("Capacity") + "\n" + makeint(fStoreWeight) + " / " + iTotalSpace;
	}
	else
	{
		sMaxGoodsStore = XI_ConvertString("Shipyard");
	}
	SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);

	sText = XI_ConvertString("OurMoney") + " " + FindMoneyString(sti(pchar.money));
	SetFormatedText("OUR_GOLD", sText);

	if (CheckAttribute(refCharacter, "ship.name"))
	{
		GameInterface.strings.shipname = refCharacter.ship.name;
	}
	else
	{
		GameInterface.strings.shipname = "";
	}
}

void ProcessFrame()
{
	if (GetCurrentNode() == "SHIPS_SCROLL")
	{
		if (sti(GameInterface.SHIPS_SCROLL.current) != nCurScrollNum)
		{
			XI_WindowDisable("QTY_WINDOW", true);
			XI_WindowShow("QTY_WINDOW", false);
			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			SetDescription();
			GameInterface.TABLE_LIST.select = 1;
			GameInterface.TABLE_LIST.top = 0;
		}
	}
}

void SetDescription()
{
	if (GetCurrentNode() == "SHIPS_SCROLL")
	{
		string attributeName = "pic" + (nCurScrollNum + 1);
		if (CheckAttribute(&GameInterface, "SHIPS_SCROLL." + attributeName))
		{
			int iCharacter = GameInterface.SHIPS_SCROLL.(attributeName).companionIndex;
			sChrId = characters[iCharacter].id;
			refCharacter = characterFromID(sChrId);
			SetShipWeight();
			//iFullPrice = 0;

		}
	}
	CalculateInfoData();
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\256\face_" + refCharacter.FaceId + ".tga");
	SetVariable();
}

void SetShipWeight()
{
	if (CheckAttribute(refCharacter, "Ship.Cargo.RecalculateCargoLoad") && sti(refCharacter.Ship.Cargo.RecalculateCargoLoad))
	{
		// остатки с моря
		RecalculateCargoLoad(refCharacter);
		refCharacter.Ship.Cargo.RecalculateCargoLoad = 0;
	}
	fShipWeight = makeint(GetCargoLoad(refCharacter) + 0.4);

	if (IsSeaTradeStore(refStore))
	{
		fStoreWeight = makeint(GetCargoLoad(refShipChar) + 0.4);
	}
	else
	{
		fStoreWeight = 0;
	}
}

void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = goods[iGoodIndex].name;

	bool ok = GetMaximumCaliber(refCharacter) < GetCannonCaliber(sti(Goods[iGoodIndex].CannonIdx));
	bool bNeedBuy = false;
	int iNeedCannons = GetCannonQuantity(refCharacter) - GetIntactCannonQuantity(refCharacter);
	string sHeader = XI_ConvertString(GoodName);

	iCurGoodsIdx = iGoodIndex;
	string goodsDescr = GetAssembledString(GetConvertStr(goodName + "_descr", "GoodsDescribe.txt"), &Goods[iGoodIndex]);
	goodsDescr += newStr() + XI_ConvertString("weight") + " " + Goods[iGoodIndex].weight + " " + XI_ConvertString("cwt") +
			", " + LowerFirst(XI_ConvertString("Pack")) + " " + Goods[iGoodIndex].Units + " " + XI_ConvertString("units");

	iUnits = sti(Goods[iGoodIndex].Units);
	fWeight = stf(Goods[iGoodIndex].weight);
	if (checkAttribute(pchar, "ship.cargo.goods." + GoodName + ".isquest"))
	{
		string sTradeQ = pchar.ship.cargo.goods.(GoodName).isquest.quantity;
		string sColony = pchar.ship.cargo.goods.(GoodName).isquest.colony;
		goodsDescr += NewStr() + XI_ConvertString("YouNeedToDelivery") + sTradeQ + XI_ConvertString("QuantityOfGoodsToColony") + XI_ConvertString("Colony" + sColony) + ".";
	}

	goodsDescr += "\n\n" + XI_ConvertString("CountCannonsOnShip") + ": " + GetCannonQuantity(refCharacter);

	BuyOrSell = 0;
	SetFormatedText("QTY_RESULT", "");
	GameInterface.qty_edit.str = "0";

	if (GetCaracterShipCannonsType(refCharacter) == sti(Goods[iCurGoodsIdx].CannonIdx))
	{
		if (!ok && iNeedCannons > 0)
		{
			goodsDescr += "\n" + XI_ConvertString("FreeCannonsOnShip") + ": " + ColorText("" + iNeedCannons, "export");

			// > учитываем и орудия в трюме - докупаем только нехватку
			int iLackCannons = iNeedCannons - GetCargoGoods(refCharacter, iCurGoodsIdx);

			if (iLackCannons > 0 && GetStoreGoodsQuantity(refStore, iCurGoodsIdx) >= iLackCannons && StoreCanSellGood(refStore, iCurGoodsIdx))
			{
				GameInterface.qty_edit.str = "" + iLackCannons;
				bNeedBuy = 1;
			}
		}
		else
			goodsDescr += "\n" + XI_ConvertString("InstalledCannonsOnShip") + " " + ColorText(XI_ConvertString("FullCannonsOnShip"), "export");
	}
	else
	{
		string sTemp = ColorText(XI_ConvertString("possible"), "export");

		if (ok)
			sTemp = ColorText(XI_ConvertString("impossible"), "contra");

		goodsDescr = goodsDescr + "\n" + XI_ConvertString("ThisIsCannon") + sTemp + XI_ConvertString("InstallCannonsToShip");
	}

	SetNewGroupPicture("QTY_GOODS_PICTURE", "GOODS", GoodName);
	SetFormatedText("QTY_CAPTION", sHeader);
	SetFormatedText("QTY_GOODS_INFO", goodsDescr);

	iShipQty = GetCargoGoods(refCharacter, iGoodIndex);

	if (!IsSeaTradeStore(refStore))
	{
		iStoreQty = GetStoreGoodsQuantity(refStore, iGoodIndex);
	}
	else
	{
		iStoreQty = GetCargoGoods(refShipChar, iGoodIndex);
	}

	SetFormatedText("QTY_INFO_STORE_QTY", "" + iStoreQty);
	SetFormatedText("QTY_INFO_SHIP_QTY", "" + iShipQty);
	BuyOrSell = 0;
	if (!StoreCanBuyGood(refStore, iGoodIndex) || MakeInt(refStore.Goods.(GoodName).TradeType) == TRADE_TYPE_CONTRABAND)
	{
		iStorePrice = 0;
		SetFormatedText("QTY_INFO_STORE_PRICE", XI_ConvertString("Price buy") + NewStr() + "-");
	}
	else
	{
		iStorePrice = GetStoreGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_SELL, pchar, 1);
		// для моря, чтоб было не выгодно
		if (IsSeaTradeStore(refStore))
		{
			iStorePrice /= 2;
			if (iStorePrice < 1) iStorePrice = 1;
		}
		SetFormatedText("QTY_INFO_STORE_PRICE", XI_ConvertString("Price buy") + NewStr() + ""+ iStorePrice);
	}
	if (!StoreCanSellGood(refStore, iGoodIndex) || and(MakeInt(refStore.Goods.(GoodName).TradeType) == TRADE_TYPE_AMMUNITION, IsSeaTradeStore(refStore)))
	{
		iShipPrice = 0;
		SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + "-");
	}
	else
	{
		iShipPrice = GetStoreGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_BUY, pchar, 1);
		SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + "" + iShipPrice);
	}

	if (bNeedBuy)
		SetFormatedText("QTY_RESULT", XI_ConvertString("BUY") + NewStr() + XI_ConvertString("money quantity") + " " + makeint(iShipPrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5) + ", " + LowerFirst(XI_ConvertString("weight")) + " " + GetGoodWeightByType(iGoodIndex, sti(GameInterface.qty_edit.str)) + " " + XI_ConvertString("cwt"));
}

void TransactionOK()
{
	int nTradeQuantity, moneyback, howMany, iTime = 20;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if (BuyOrSell == 0)
	{
		EndTooltip();
		return;
	}
	if (!GetRemovable(refCharacter)) return;

	if (BuyOrSell == 1) // BUY
	{
		if (!IsSeaTradeStore(refStore))
		{
			SetStoreGoods(refStore, iCurGoodsIdx, iStoreQty - nTradeQuantity);
		}
		else
		{
			RemoveCharacterGoods(refShipChar, iCurGoodsIdx, nTradeQuantity);
		}

		AddCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		moneyback = makeint(iShipPrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5);
		pchar.money = sti(pchar.money) - moneyback;
		Statistic_AddValue(Pchar, "Money_spend", moneyback);
		// boal  check skill -->
		AddCharacterExpToSkill(pchar, "Commerce", moneyback / 600);
		// boal <--
	}
	else
	{
		// SELL
		if (!IsSeaTradeStore(refStore))
		{
			SetStoreGoods(refStore, iCurGoodsIdx, iStoreQty + nTradeQuantity);
		}
		else
		{
			AddCharacterGoods(refShipChar, iCurGoodsIdx, nTradeQuantity);
		}

		RemoveCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		moneyback = makeint(iStorePrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5);
		pchar.money = sti(pchar.money) + moneyback;
		Statistic_AddValue(Pchar, "Money_get", moneyback);
		// boal  check skill -->
		AddCharacterExpToSkill(pchar, "Commerce", moneyback / 1200);
		// boal <--
	}

	howMany = nTradeQuantity / sti(Goods[iCurGoodsIdx].Units);
	if (howMany > 5)
	{
		if (howMany > 5 && howMany <= 10)                iTime = 20 + rand(10);
		else if (howMany > 10 && howMany <= 25 + rand(5))    iTime = 25 + rand(15);
		else if (howMany > 25 && howMany <= 50 + rand(5))    iTime = 35 + rand(20);
		else if (howMany > 50 && howMany <= 75 + rand(5))    iTime = 60 + rand(10);
		else if (howMany > 75 && howMany <= 100 + rand(10))    iTime = 120 + rand(20);
		else if (howMany > 100)                                iTime = 180 + rand(30);
	}

	if (CheckOfficer("treasurer"))
	{
		AddCharacterExpToSkill(RefOfficer("treasurer"), SKILL_COMMERCE, moneyback / 1600.0);
		iTime /= 2;
	}

	if (GetOfficersPerkUsing(refCharacter, "QuickCalculation", false))
		iTime /= 2;

	WaitDate("", 0, 0, 0, 0, iTime);

	AddToTable();
	EndTooltip();
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
	SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	int iWeight;
	SetShipWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);

	string GoodName = goods[iCurGoodsIdx].name;

	if (sti(GameInterface.qty_edit.str) == 0)
	{
		SetFormatedText("QTY_RESULT", "");
		BuyOrSell = 0;
	}
	else
	{
		if (sti(GameInterface.qty_edit.str) < 0 || BuyOrSell == -1)
		{
			if (BuyOrSell != -1)
			{
				GameInterface.qty_edit.str = -sti(GameInterface.qty_edit.str);
			}
			BuyOrSell = -1;
			if (!StoreCanBuyGood(refStore, iCurGoodsIdx)) GameInterface.qty_edit.str = 0; // > магазин этот товар не покупает
			if (MakeInt(refStore.Goods.(GoodName).TradeType) == TRADE_TYPE_CONTRABAND)
			{
				// контрабанду нельзя продать
				GameInterface.qty_edit.str = 0;
			}
			// проверка на колво доступное -->
			if (sti(GameInterface.qty_edit.str) > iShipQty)
			{
				GameInterface.qty_edit.str = iShipQty;
			}
			iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
			if ((fStoreWeight + iWeight) > iTotalSpace)
			{
				iWeight = iTotalSpace - fStoreWeight - fWeight;
				GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits);
				iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
				GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits); // округдение
			}
			// проверка на колво доступное <--
			SetFormatedText("QTY_RESULT", XI_ConvertString("SELL") + NewStr() + XI_ConvertString("money quantity") + " " + makeint(iStorePrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5) +
					", " + LowerFirst(XI_ConvertString("weight")) + " " + iWeight + " " + XI_ConvertString("cwt"));
		}
		else
		{
			// не нужно у кэпов в море пукупать порох и ядра, а то потом они беззащитны
			if ((MakeInt(refStore.Goods.(GoodName).TradeType) == TRADE_TYPE_AMMUNITION) && (IsSeaTradeStore(refStore)))
			{
				GameInterface.qty_edit.str = 0;
			}
			BuyOrSell = 1;
			if (!StoreCanSellGood(refStore, iCurGoodsIdx)) GameInterface.qty_edit.str = 0; // > магазин этот товар не продаёт
			// проверка на колво доступное -->
			if (sti(GameInterface.qty_edit.str) > iStoreQty)
			{
				GameInterface.qty_edit.str = iStoreQty;
			}
			iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
			if ((fShipWeight + iWeight) > iShipCapacity)
			{
				iWeight = iShipCapacity - fShipWeight - fWeight;
				if (iWeight < 0) iWeight = 0;
				GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits);
				iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
				GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits); // округдение
			}
			if (iShipPrice > 0 && makeint(iShipPrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5) > sti(pchar.money))
			{
				GameInterface.qty_edit.str = makeint(sti(pchar.money) * iUnits / iShipPrice);
				iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
			}
			// проверка на колво доступное <--

			SetFormatedText("QTY_RESULT", XI_ConvertString("BUY") + NewStr() + XI_ConvertString("money quantity") + " " + makeint(iShipPrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5) +
					", " + LowerFirst(XI_ConvertString("weight")) + " " + iWeight + " " + XI_ConvertString("cwt"));
		}
	}
	// если получили ноль
	if (sti(GameInterface.qty_edit.str) <= 0)
	{
		SetFormatedText("QTY_RESULT", "");
		BuyOrSell = 0;
	}
	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell * sti(GameInterface.qty_edit.str)));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty + BuyOrSell * sti(GameInterface.qty_edit.str)));
	SetShipWeight();
	fShipWeight = fShipWeight + BuyOrSell * iWeight;
	fStoreWeight = fStoreWeight - BuyOrSell * iWeight;
	SetVariable();
}

void REMOVE_ALL_BUTTON()  // продать все
{
	if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin)
	{
		ShowItemInfo();
	}
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = -iShipQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // купить все
{
	if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin)
	{
		ShowItemInfo();
	}
	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = iStoreQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // продать
{
	if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = -iUnits;
	}
	else
	{
		if (BuyOrSell == -1)
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) + iUnits);
		}
		else
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - iUnits);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // купить
{
	if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin) return;
	if (BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = iUnits;
	}
	else
	{
		if (BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + iUnits);
		}
		else
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - iUnits);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

void OnHeaderClick()
{
	string sControl = GetEventData();
	int iColumn = GetEventData();

	if (sControl == "TABLE_LIST") SortCannonsList(iColumn, false, sControl);
}

void SortCannonsList(int column, bool preserveState, string tableName)
{
	int offset = 0;
	string datatype = "integer";
	switch (column)
	{
		case 4: datatype = "index"; break;
		case 7: datatype = "floatEnd"; offset = 1; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, offset);
}
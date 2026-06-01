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

	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("In the hold");
	GameInterface.TABLE_LIST.hr.td1.scale = 0.85;
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("weight");
	GameInterface.TABLE_LIST.hr.td2.scale = 0.85;
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.TABLE_LIST.hr.td3.scale = 0.85;
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("Good name");
	GameInterface.TABLE_LIST.hr.td4.scale = 0.85;
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("Price buy");
	GameInterface.TABLE_LIST.hr.td5.scale = 0.85;
	GameInterface.TABLE_LIST.hr.td6.str = XI_ConvertString("weight") + XI_ConvertString("pcs");
	GameInterface.TABLE_LIST.hr.td6.scale = 0.85;
	GameInterface.TABLE_LIST.hr.td7.str = XI_ConvertString("Damage");
	GameInterface.TABLE_LIST.hr.td7.scale = 0.85;
	GameInterface.TABLE_LIST.hr.td8.str = XI_ConvertString("Fire range2") + "\n/" + XI_ConvertString("Time:");
	GameInterface.TABLE_LIST.hr.td8.scale = 0.85;
	if (refStore.Colony == "none")
	{
		GameInterface.TABLE_LIST.hr.td9.str = XI_ConvertString("In the hold");
	}
	else
	{
		GameInterface.TABLE_LIST.hr.td9.str = XI_ConvertString("In the shipyard");
	}
	GameInterface.TABLE_LIST.hr.td9.scale = 0.85;

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

	if (refStore.Colony == "none")
	{
		SetFormatedText("MAIN_CAPTION", XI_ConvertString("Ship") + ": '" + refShipChar.ship.name + "'");
	}
	else
	{
		SetFormatedText("MAIN_CAPTION", XI_ConvertString("titleShipyard") + "-  " + XI_ConvertString("Colony" + refStore.Colony));
	}

	if (refStore.Colony == "none")
	{
		SetNewPicture("OTHER_PICTURE", "interfaces\portraits\256\face_" + its(refShipChar.FaceId) + ".tga");
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
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
}

void AddToTable()
{
	int n, i;
	string row, sShipGroup;
	ref rShip;
	string sGood;
	string sBuy, sSell, sStoreWeight;
	int tradetype, iColor, iStoreQ, iShipQ;
	aref refGoods;
	n = 1;
	Table_Clear("TABLE_LIST", false, true, false);

	for (i = 0; i < GOODS_QUANTITY; i++)
	{
		row = "tr" + n;
		sGood = Goods[i].name;
		makearef(refGoods, refStore.Goods.(sGood));
		tradeType = MakeInt(refGoods.TradeType);
		if (tradeType != TRADE_TYPE_CANNONS) continue; // не пушки

		iShipQ = GetCargoGoods(refCharacter, i);

		if (refStore.Colony != "none")
		{
			iStoreQ = GetStoreGoodsQuantity(refStore, i);
		}
		else
		{
			iStoreQ = GetCargoGoods(refShipChar, i);
		}

		if (iStoreQ < 0)
		{
			iStoreQ = 0;
			refGoods.quantity = 0;
		}
		if (iStoreQ == 0 && iShipQ == 0) continue; // только не нули

		GameInterface.TABLE_LIST.(row).index = i;
		GameInterface.TABLE_LIST.(row).td1.str = "" + iShipQ;
		GameInterface.TABLE_LIST.(row).td2.str = GetGoodWeightByType(i, iShipQ);
		GameInterface.TABLE_LIST.(row).td6.str = Goods[i].Weight;
		GameInterface.TABLE_LIST.(row).td7.str = "x" + FloatToString(stf(Goods[i].DamageMultiply), 1);
		GameInterface.TABLE_LIST.(row).td8.str = sti(Goods[i].FireRange) + " / " + sti(Goods[i].ReloadTime);
		GameInterface.TABLE_LIST.(row).td9.str = iStoreQ;

		iColor = argb(255, 255, 255, 255);
		if (checkAttribute(refCharacter, "ship.cargo.goods." + sGood + ".isquest"))
		{
			iColor = argb(255, 255, 192, 255);
		}

		// KZ > цветовая дифференциация орудий в ассортименте верфиста
		if (CheckAttrValue(&InterfaceStates, "TradeAssistant", "1") && GetRemovable(refCharacter))
		{
			if (GetCaracterShipCannonsType(refCharacter) == sti(Goods[i].CannonIdx))
			{
				if ((GetIntactCannonQuantity(refCharacter) != GetCannonQuantity(refCharacter)) || (GetIntactCannonQuantity(refCharacter) == GetCannonQuantity(refCharacter))) // эти орудия сейчас установлены
					iColor = argb(255, 218, 165, 32);
			}
			else
			{
				if (sti(RealShips[sti(refCharacter.ship.type)].MaxCaliber) < GetCannonCaliber(sti(Goods[i].CannonIdx))) // эти орудия нельзя установить на выделенный корабль
					iColor = argb(255, 169, 169, 169);
			}
		}
		// KZ <

		GameInterface.TABLE_LIST.(row).td4.icon.group = "GOODS";
		GameInterface.TABLE_LIST.(row).td4.icon.image = sGood;
		GameInterface.TABLE_LIST.(row).td4.icon.offset = "0, 0";
		GameInterface.TABLE_LIST.(row).td4.icon.width = 29;
		GameInterface.TABLE_LIST.(row).td4.icon.height = 29;
		GameInterface.TABLE_LIST.(row).td4.textoffset = "25,0";
		GameInterface.TABLE_LIST.(row).td4.str = XI_ConvertString(sGood);
		GameInterface.TABLE_LIST.(row).td4.color = iColor;
		GameInterface.TABLE_LIST.(row).td4.scale = 0.85;

		if (tradeType == TRADE_TYPE_CONTRABAND)
		{
			GameInterface.TABLE_LIST.(row).td5.str = "-";
		}
		else
		{
			GameInterface.TABLE_LIST.(row).td5.str = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, pchar, 1);
			// в море
			if (refStore.Colony == "none")
			{
				GameInterface.TABLE_LIST.(row).td5.str = makeint(sti(GameInterface.TABLE_LIST.(row).td5.str) / 2);
				if (sti(GameInterface.TABLE_LIST.(row).td5.str) < 1) GameInterface.TABLE_LIST.(row).td5.str = 1;
			}
		}
		if ((tradeType == TRADE_TYPE_AMMUNITION) && (refStore.Colony == "none"))
		{
			GameInterface.TABLE_LIST.(row).td3.str = "-"; // нельзя купить в море
		}
		else
		{
			GameInterface.TABLE_LIST.(row).td3.str = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_BUY, pchar, 1);
		}
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

	string sRow = "tr" + (iRow + 1);
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
	sText = sText;
	SetFormatedText("CAPACITY", XI_ConvertString("Capacity") + "\n" + sText);

	iTotalSpace = iMaxGoodsStore;
	string sMaxGoodsStore;
	if (refStore.Colony == "none")
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
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\256\face_" + its(refCharacter.FaceId) + ".tga");
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

	if (refStore.Colony == "none")
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

	bool ok = sti(RealShips[sti(refCharacter.ship.type)].MaxCaliber) < GetCannonCaliber(sti(Goods[iGoodIndex].CannonIdx));
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

			if ((GetCargoGoods(refCharacter, iCurGoodsIdx) < iNeedCannons) && (GetStoreGoodsQuantity(refStore, iCurGoodsIdx) >= iNeedCannons))
			{
				GameInterface.qty_edit.str = "" + iNeedCannons;
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

	if (refStore.Colony != "none")
	{
		iStoreQty = GetStoreGoodsQuantity(refStore, iGoodIndex);
	}
	else
	{
		iStoreQty = GetCargoGoods(refShipChar, iGoodIndex);
	}

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty));
	BuyOrSell = 0;
	if (MakeInt(refStore.Goods.(GoodName).TradeType) == TRADE_TYPE_CONTRABAND)
	{
		iStorePrice = 0;
		SetFormatedText("QTY_INFO_STORE_PRICE", XI_ConvertString("Price buy") + NewStr() + "-");
	}
	else
	{
		iStorePrice = GetStoreGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_SELL, pchar, 1);
		// для моря, чтоб было не выгодно
		if (refStore.Colony == "none")
		{
			iStorePrice /= 2;
			if (iStorePrice < 1) iStorePrice = 1;
		}
		SetFormatedText("QTY_INFO_STORE_PRICE", XI_ConvertString("Price buy") + NewStr() + its(iStorePrice));
	}
	if ((MakeInt(refStore.Goods.(GoodName).TradeType) == TRADE_TYPE_AMMUNITION) && (refStore.Colony == "none"))
	{
		iShipPrice = 0;
		SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + "-");
	}
	else
	{
		iShipPrice = GetStoreGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_BUY, pchar, 1);
		SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + its(iShipPrice));
	}

	if (bNeedBuy)
		SetFormatedText("QTY_RESULT", XI_ConvertString("BUY") + NewStr() + XI_ConvertString("money quantity") + " " + makeint(iShipPrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5) + ", " + LowerFirst(XI_ConvertString("weight")) + " " + fWeight + " " + XI_ConvertString("cwt"));
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
		if (refStore.Colony != "none")
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
		if (refStore.Colony != "none")
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
			if ((MakeInt(refStore.Goods.(GoodName).TradeType) == TRADE_TYPE_AMMUNITION) && (refStore.Colony == "none"))
			{
				GameInterface.qty_edit.str = 0;
			}
			BuyOrSell = 1;
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
			if (makeint(iShipPrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5) > sti(pchar.money))
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
		case 9: datatype = "floatEnd"; break;
	}

	if (column == 9) offset = 1;

	QoLSortTable(tableName, column, datatype, preserveState, offset);
}
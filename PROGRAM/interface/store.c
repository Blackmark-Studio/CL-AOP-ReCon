// boal 31/03/06 STORE
// Hokkins: интерфейс покупки товаров в магазине. Обновленная верстка (10.07.2022)

int TableSelect = 0;
int nCurScrollNum = 0;
int iShipCapacity;
int iTotalSpace;
float fShipWeight, fStoreWeight;
int iMaxGoodsStore = 50000;
int FilterMode;

bool bShowChangeWin = false;
int BuyOrSell = 0; // 1-buy -1 sell
string sChrId;
aref arTableList;
ref refStore, refCharacter, refShipChar;
int iShipQty, iStoreQty, iShipPrice, iStorePrice, iUnits;
float fWeight;
int iCurGoodsIdx;
bool ok; // for if
bool bPirateBase;
int idGoodsDescr = -1;
bool bSeaTrade;
bool bSkipTableFill = false;

void InitInterface_R(string iniName, ref pStore)
{
	StartAboveForm(true);

	refStore = pStore;
	refCharacter = pchar;
	idGoodsDescr = LanguageOpenFile("GoodsDescribe.txt");
	bSeaTrade = IsSeaTradeStore(pStore); // KZ FreeStores > признак моря по слоту, а не по пустой колонии
	bPirateBase = CheckCharacterPerk(pchar, "BasePirate");
	SetQuestGoodsToStore(refStore); // установка квестовых товаров и цен
	if (CheckAttribute(pchar, "shiptrade.character"))
	{
		refShipChar = CharacterFromID(pchar.shiptrade.character);
	}
	//GameInterface.TABLE_LIST.hr.height = 36;
	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("In the hold");
	makearef(arTableList, GameInterface.TABLE_LIST.hr);
	arTableList.td1.scale = 0.87;
	arTableList.td2.str = XI_ConvertString("weight");
	arTableList.td2.scale = 0.87;
	arTableList.td3.str = XI_ConvertString("Price sell");
	arTableList.td3.scale = 0.87;
	arTableList.td4.str = XI_ConvertString("Good name");
	arTableList.td4.scale = 0.87;
	arTableList.td5.str = XI_ConvertString("Price buy");
	arTableList.td5.scale = 0.87;
	arTableList.td6.str = XI_ConvertString("Pack");
	arTableList.td6.scale = 0.87;
	arTableList.td7.str = XI_ConvertString("PackWeight");
	arTableList.td7.scale = 0.87;

	if (bSeaTrade)
	{
		arTableList.td8.str = XI_ConvertString("In the hold");
	}
	else
	{
		arTableList.td8.str = XI_ConvertString("In the store");
	}

	arTableList.td8.scale = 0.85;

	FillShipsScroll();

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);

	if (bSeaTrade)
	{
		SetFormatedText("MAIN_CAPTION", XI_ConvertString("Ship") + ": '" + refShipChar.ship.name + "'");
	}
	else
	{
		SetFormatedText("MAIN_CAPTION", XI_ConvertString("titleStore") + "-  " + GetStoreTitleName(refStore));
	}

	bSkipTableFill = true;
	SetControlsTabMode(1);
	bSkipTableFill = false;

	CreateString(true, "ShipName", "", FONT_NORMAL, COLOR_MONEY, 400, 99, SCRIPT_ALIGN_CENTER, 0.7);

	SetShipWeight();
	SetDescription();

	SetEventHandler("InterfaceBreak", "ProcessBreakExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("ievnt_command", "ProcCommand", 0);
	SetEventHandler("evntDoPostExit", "DoPostExit", 0);
	SetEventHandler("eTabControlPress", "procTabChange", 0);

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
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);
	SetEventHandler("Autotrade_All", "Autotrade_All", 0);

	SetEventHandler("frame", "ProcessFrame", 1);

	//SetEventHandler("RefreshTable","RefreshTable",0);
	//PostEvent("RefreshTable", 1000);

	if (bSeaTrade)
	{
		SetNewPicture("OTHER_PICTURE", "interfaces\portraits\256\face_" + its(refShipChar.FaceId) + ".tga");
	}

	if (!bSeaTrade && CheckOfficer("treasurer") && !CheckAttribute(pchar, "TransferGoods.Enable"))
	{
		SetNodeUsing("GOODSTRANSFER_BTN", true);
	}
	else
	{
		SetNodeUsing("GOODSTRANSFER_BTN", false);
	}
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
	DelEventHandler("eTabControlPress", "procTabChange");

	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("MouseRClickUP", "EndTooltip");
	DelEventHandler("ShowHelpHint", "ShowHelpHint");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame", "ProcessFrame");
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON", "ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");
	DelEventHandler("OnHeaderClick", "OnHeaderClick");

	DelEventHandler("Autotrade_All", "Autotrade_All");

	if (idGoodsDescr != -1)
	{
		LanguageCloseFile(idGoodsDescr);
		idGoodsDescr = -1;
	}

	//DelEventHandler("RefreshTable","RefreshTable");
	// boal 27.02.05 -->
	// FreeStores > у свободного магазина колонии нет, прайс пишем от него самого
	if (!bSeaTrade && IsFreeStore(refStore))
	{
		int iStoreColony = GetStorePriceColony(refStore);
		if (iStoreColony >= 0) SetPriceList(&Colonies[iStoreColony], false);
		else                   SetPriceList(refStore, false);
		if (CheckAttribute(pchar, "PriceList.StoreManIdx")) DeleteAttribute(pchar, "PriceList.StoreManIdx");
	}
	else
	{
		if (CheckAttribute(pchar, "PriceList.StoreManIdx"))
		{
			SetPriceList(&Colonies[sti(pchar.PriceList.StoreManIdx)], false);
			DeleteAttribute(pchar, "PriceList.StoreManIdx");
		}
	}
	// boal 27.02.05 <--
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
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
	AddToTable(FilterMode);
	//SetCurrentNode("B_OK");
}

float fPriceSkillBuy, fPriceSkillSell;

void PreparePriceModifiers()
{
	float fTradeSkill = GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE);
	fPriceSkillBuy  = 1.46 - fTradeSkill * 0.019; // PRICE_TYPE_BUY  - ГГ покупает
	fPriceSkillSell = 0.69 + fTradeSkill * 0.019; // PRICE_TYPE_SELL - ГГ продаёт

	if (CheckOfficersPerk(pchar, "ProfessionalCommerce"))
	{
		fPriceSkillBuy  = fPriceSkillBuy  - 0.15;
		fPriceSkillSell = fPriceSkillSell + 0.15;
	}
	else
	{
		if (CheckOfficersPerk(pchar, "BasicCommerce"))    fPriceSkillBuy  = fPriceSkillBuy  - 0.1;
		if (CheckOfficersPerk(pchar, "AdvancedCommerce")) fPriceSkillSell = fPriceSkillSell + 0.1;
	}
}

int StoreGoodsPriceFast(int iGood, int iTradeType, float fRndPriceModify, float fSkillModify)
{
	float fTradeModify = 0.85;
	switch (iTradeType)
	{
		case TRADE_TYPE_EXPORT:     fTradeModify = 0.55; break;
		case TRADE_TYPE_IMPORT:     fTradeModify = 1.2;  break;
		case TRADE_TYPE_CONTRABAND: fTradeModify = 2.4;  break;
	}
	fTradeModify = fTradeModify + fRndPriceModify;

	float fBase = MakeInt(Goods[iGood].Cost);
	int iRes = MakeInt(fBase * fTradeModify * fSkillModify + 0.5);
	if (iRes < 1) return 1;
	return iRes;
}

void AddToTable(int _mode)
{
	int n, i;
	string row;
	ref rShip;
	string sGood;
	string sBuy, sSell, sStoreWeight;
	int tradetype, iColor , iShipQ, iStoreQ;
	aref refGoods;
	bool bHasGoods, bStoreSells, bStoreBuys;
	float fRndPriceMod;
	string sTemp, sColony;
	ref nulChr;
	n = 1;
	PreparePriceModifiers();
	Table_Clear("TABLE_LIST", false, true, false);
	for (i = 0; i < GOODS_QUANTITY; i++)
	{
		row = "tr" + n;
		sGood = Goods[i].name;
		bHasGoods = CheckAttribute(refStore, "Goods." + sGood);
		if (bHasGoods)
		{
			makearef(refGoods, refStore.Goods.(sGood));
			tradeType = MakeInt(refGoods.TradeType);
			fRndPriceMod = stf(refGoods.RndPriceModify);
		}
		else
		{
			fRndPriceMod = 0.0;
			tradeType = TRADE_TYPE_NORMAL;
		}
		if (tradeType == TRADE_TYPE_CANNONS) continue; // не пушки

		// > запрет торговли этим товаром в этом магазине
		bStoreSells = StoreCanSellGood(refStore, i); // > ГГ может купить
		bStoreBuys  = StoreCanBuyGood(refStore, i);  // > ГГ может продать
		if (!bStoreSells && !bStoreBuys && IsStoreGoodHidden(refStore, i)) continue; // > строки нет ни у одной стороны
		if (i == GOOD_PINCTADA) //HardCoffee молюсков торговцам не продаём
		{
			if (bSeaTrade) continue;
			if (tradeType == TRADE_TYPE_CONTRABAND && !bBettaTestMode) continue;
		}

		iShipQ = GetCargoGoods(refCharacter, i);

		if (FilterMode == 2 && iShipQ == 0) continue;
		if (FilterMode == 3 && tradeType != TRADE_TYPE_EXPORT) continue;
		if (FilterMode == 4 && tradeType != TRADE_TYPE_IMPORT) continue;
		if (FilterMode == 5 && tradeType != TRADE_TYPE_CONTRABAND) continue;

		if (!bSeaTrade)
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
			if (bHasGoods) refGoods.quantity = 0; // > чинить нечего, если ветки нет
		}
		if (iStoreQ == 0 && iShipQ == 0) continue; // только не нули

		if (i == GOOD_PINCTADA) //HardCoffee отобразим цену на молюсков, если они не контрабанда
		{
			sTemp = "Gidx" + i;
			sColony = GetStorePriceKey(refStore);
			nulChr = &NullCharacter;
			if (sColony != "")
			{
				nulChr.PriceList.(sColony).(sTemp).Buy = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_BUY, pchar, 1);
				nulChr.PriceList.(sColony).(sTemp).Sell = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, pchar, 1);
				nulChr.PriceList.(sColony).(sTemp).Qty = GetStoreGoodsQuantity(refStore, i);
				nulChr.PriceList.(sColony).(sTemp).tradeType = tradeType;
			}
		}

		GameInterface.TABLE_LIST.(row).index = i;
		makearef(arTableList, GameInterface.TABLE_LIST.(row));
		arTableList.td1.str = iShipQ;
		arTableList.td2.str = GetGoodWeightByType(i, iShipQ);
		arTableList.td6.str = Goods[i].Units;
		arTableList.td7.str = Goods[i].Weight;

		arTableList.td1.scale = 0.9;
		arTableList.td2.scale = 0.9;
		arTableList.td3.scale = 0.9;
		arTableList.td5.scale = 0.9;
		arTableList.td6.scale = 0.9;
		arTableList.td7.scale = 0.9;
		arTableList.td8.scale = 0.9;

		if (tradeType == TRADE_TYPE_CONTRABAND && !bPirateBase && !bBettaTestMode)
			arTableList.td8.str = "-";
		else
			arTableList.td8.str = iStoreQ;

		switch (tradeType)
		{
			case TRADE_TYPE_NORMAL:
				iColor = argb(255, 255, 255, 255);
			break;
			case TRADE_TYPE_EXPORT:
				iColor = argb(255, 196, 255, 196);
			break;
			case TRADE_TYPE_IMPORT:
				iColor = argb(255, 196, 196, 255);
			break;
			case TRADE_TYPE_CONTRABAND:
				iColor = argb(255, 255, 196, 196);
			break;
			case TRADE_TYPE_AMMUNITION:
				if (bSeaTrade)
				{
					iColor = argb(255, 196, 196, 196);
				}
				else
				{
					iColor = argb(255, 255, 255, 255);
				}
			break;
		}

		if (checkAttribute(refCharacter, "ship.cargo.goods." + sGood + ".isquest"))
		{
			iColor = argb(255, 255, 192, 255);
		}

		if (!bStoreSells && !bStoreBuys) iColor = GetStoreGoodBanColor(refStore, i); // > товар вне торговли красим отдельно

		arTableList.td4.icon.group = "GOODS";
		arTableList.td4.icon.image = sGood;
		arTableList.td4.icon.offset = "0, 0";
		arTableList.td4.icon.width = 29;
		arTableList.td4.icon.height = 29;
		arTableList.td4.textoffset = "25,0";
		arTableList.td4.scale = 0.9;
		arTableList.td4.str = XI_ConvertString(sGood);
		arTableList.td4.color = iColor;

		if (!bStoreBuys || and(tradeType == TRADE_TYPE_CONTRABAND, !bBettaTestMode))
		{
			arTableList.td5.str = "-"; // > магазин этот товар не покупает
		}
		else
		{
			if (bHasGoods)
				arTableList.td5.str = StoreGoodsPriceFast(i, tradeType, fRndPriceMod, fPriceSkillSell);
			else
				arTableList.td5.str = 0;
			// в море
			if (bSeaTrade)
			{
				arTableList.td5.str = makeint(sti(arTableList.td5.str) / 2);
				if (sti(arTableList.td5.str) < 1)
					arTableList.td5.str = 1;
			}
		}

		if (!bStoreSells)
		{
			arTableList.td3.str = "-"; // > магазин этот товар не продаёт
		}
		else if ((tradeType == TRADE_TYPE_AMMUNITION) && (bSeaTrade))
		{
			arTableList.td3.str = "-"; // нельзя купить в море
		}
		else if (tradeType == TRADE_TYPE_CONTRABAND && !bPirateBase && !bBettaTestMode)
		{
			arTableList.td3.str = "-";
		}
		else
		{
			if (bHasGoods)
				arTableList.td3.str = StoreGoodsPriceFast(i, tradeType, fRndPriceMod, fPriceSkillBuy);
			else
				arTableList.td3.str = 0;
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
	//int iRow = GetEventData();
	//int iColumn = GetEventData();
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

		sText2 = XI_ConvertString("TradeInterfaceDescr_9");

		sText3 = XI_ConvertString("TradeInterfaceDescr_7") + "\n\n" + ColorText(LowerFirst(XI_ConvertString("Imports")) + "     ", "import") + ColorText(LowerFirst(XI_ConvertString("Contrabands")) + "     ", "contra") + ColorText(LowerFirst(XI_ConvertString("Exports")) + "\n", "export");

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
	XI_WindowDisable("MAIN_WINDOW", false);
	bShowChangeWin = false;
}

void ShowItemInfo()
{
	if (bShowChangeWin) // жмем окей, когда курсор на таблице
	{
		TransactionOK();
		return;
	}

	string sRow = "tr" + GameInterface.TABLE_LIST.select;
	if (!CheckAttribute(&GameInterface, "TABLE_LIST." + sRow + ".index")) return;
	iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(sRow).index);
	ShowGoodsInfo(iCurGoodsIdx);

	GameInterface.qty_edit.str = "0";
	BuyOrSell = 0;
	ChangeQTY_EDIT();

	XI_WindowDisable("QTY_WINDOW", false);
	XI_WindowShow("QTY_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", true);
	bShowChangeWin = true;
	if (GetRemovable(refCharacter)) SetSelectable("QTY_OK_BUTTON", true);
	else SetSelectable("QTY_OK_BUTTON", false);
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

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode("TABLE_LIST");

	switch (sNodName)
	{
		case "TABBTN_1": SetControlsTabMode(1); break;
		case "TABBTN_2": SetControlsTabMode(2); break;
		case "TABBTN_3": SetControlsTabMode(3); break;
		case "TABBTN_4": SetControlsTabMode(4); break;
		case "TABBTN_5": SetControlsTabMode(5); break;
	}
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255, 196, 196, 196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;
	int nColor5 = nColor1;

	string sPic1 = "TabSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;
	string sPic5 = sPic1;

	switch (nMode)
	{
		case 1: //
			sPic1 = "TabDeSelected";
			nColor1 = argb(255, 255, 255, 255);
		break;
		case 2:
			sPic2 = "TabDeSelected";
			nColor2 = argb(255, 255, 255, 255);
		break;
		case 3:
			sPic3 = "TabDeSelected";
			nColor3 = argb(255, 255, 255, 255);
		break;
		case 4:
			sPic4 = "TabDeSelected";
			nColor4 = argb(255, 255, 255, 255);
		break;
		case 5:
			sPic5 = "TabDeSelected";
			nColor5 = argb(255, 255, 255, 255);
		break;
	}

	// Выставим таблицу в начало
	GameInterface.TABLE_LIST.select = 1;
	GameInterface.TABLE_LIST.top = 0;

	SetNewGroupPicture("TABBTN_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_3", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_4", "TABS", sPic4);
	SetNewGroupPicture("TABBTN_5", "TABS", sPic5);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_1", 8, 0, nColor1);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_2", 8, 0, nColor2);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_3", 8, 0, nColor3);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_4", 8, 0, nColor4);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_5", 8, 0, nColor5);
	FillControlsList(nMode);
}

void FillControlsList(int nMode)
{
	switch (nMode)
	{
		case 1: FilterMode = 1; break;  // все
		case 2: FilterMode = 2; break;  // снаряжение
		case 3: FilterMode = 3; break;  // остальное
		case 4: FilterMode = 4; break;  // карты
		case 5: FilterMode = 5; break;  // карты
	}
	if (bSkipTableFill) return;
	AddToTable(FilterMode);
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
	TableSelect = iSelected;
//	SetShipWeight(); // > обе-две тут лишние: от выбора строки ни вес трюма, ни деньги не меняются - бессмысленные вычисления
//	SetVariable();
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
	SetFormatedText("CAPACITY", XI_ConvertString("Capacity") + ":\n" + sText);

	iTotalSpace = iMaxGoodsStore;
	string sMaxGoodsStore;
	if (bSeaTrade)
	{
		int iTraderShip = sti(refShipChar.ship.type);
		if (iTraderShip >= 0 && iTraderShip < REAL_SHIPS_QUANTITY) iTotalSpace = sti(RealShips[iTraderShip].capacity);
		else iTotalSpace = 0;
		sMaxGoodsStore = XI_ConvertString("Capacity") + ":\n" + makeint(fStoreWeight) + " / " + iTotalSpace;
		SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);
		sText = XI_ConvertString("TraderMoney") + " " + FindMoneyString(sti(refShipChar.money));
	}
	else
	{
		sMaxGoodsStore = XI_ConvertString("istrader");
		SetFormatedText("STORE_CAPACITY", sMaxGoodsStore);
		sText = XI_ConvertString("StoreMoney") + " " + FindMoneyString(sti(refStore.money));
	}
	SetFormatedText("TRADER_GOLD", sText);
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
	string sNode = GetCurrentNode();

	if (sNode == "SHIPS_SCROLL")
	{
		if (sti(GameInterface.SHIPS_SCROLL.current) != nCurScrollNum)
		{
			XI_WindowDisable("QTY_WINDOW", true);
			XI_WindowShow("QTY_WINDOW", false);
			XI_WindowDisable("MAIN_WINDOW", false);
			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			SetDescription();
			GameInterface.TABLE_LIST.select = 1;
			GameInterface.TABLE_LIST.top = 0;
		}
	}

	if (sNode == "")
	{
		SetCurrentNode("TABLE_LIST");
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

	if (bSeaTrade)
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
	string sHeader = XI_ConvertString(GoodName);
	int iTradeType = MakeInt(refStore.Goods.(GoodName).TradeType);

	iCurGoodsIdx = iGoodIndex;
	string goodsDescr = "";
	if (bBettaTestMode)
	{
		goodsDescr += NewStr() + "BaseNorm " + goods[iGoodIndex].Norm + " BaseCost " + goods[iGoodIndex].Cost + " StoreNorm " + refStore.Goods.(GoodName).Norm;
		goodsDescr += NewStr() + "NormPrMod " + FloatToString(stf(refStore.Goods.(GoodName).NormPriceModify), 4) + " CurPrMod " +
				FloatToString(stf(refStore.Goods.(GoodName).RndPriceModify), 4) + " Delta " +
					FloatToString(stf(stf(refStore.Goods.(GoodName).Quantity) / stf(refStore.Goods.(GoodName).Norm)), 3);
		goodsDescr += NewStr();
	}
	goodsDescr += GetAssembledString(GetConvertStr(goodName + "_descr", "GoodsDescribe.txt"), &Goods[iGoodIndex]);
	goodsDescr += newStr() + XI_ConvertString("weight") + " " + Goods[iGoodIndex].weight + " " + XI_ConvertString("cwt") +
			", " + XI_ConvertString("Pack") + " " + Goods[iGoodIndex].Units + " " + XI_ConvertString("units");

	iUnits = sti(Goods[iGoodIndex].Units);
	fWeight = stf(Goods[iGoodIndex].weight);
	if (checkAttribute(pchar, "ship.cargo.goods." + GoodName + ".isquest"))
	{
		string sTradeQ = pchar.ship.cargo.goods.(GoodName).isquest.quantity;
		string sColony = pchar.ship.cargo.goods.(GoodName).isquest.colony;
		goodsDescr += NewStr() + XI_ConvertString("YouNeedToDelivery") + sTradeQ + XI_ConvertString("QuantityOfGoodsToColony") + XI_ConvertString("Colony" + sColony) + ".";
	}

	SetFormatedText("QTY_Result", "");
	GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", "GOODS", GoodName);
	SetFormatedText("QTY_CAPTION", sHeader);
	SetFormatedText("QTY_GOODS_INFO", goodsDescr);



	if (!bSeaTrade)
	{
		if (iTradeType == TRADE_TYPE_CONTRABAND && !bPirateBase && !bBettaTestMode)
			iStoreQty = 0;
		else iStoreQty = GetStoreGoodsQuantity(refStore, iGoodIndex);
	}
	else
	{
		iStoreQty = GetCargoGoods(refShipChar, iGoodIndex);
	}
	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));

	iShipQty = GetCargoGoods(refCharacter, iGoodIndex);
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty));

	if (!StoreCanBuyGood(refStore, iGoodIndex) || and(iTradeType == TRADE_TYPE_CONTRABAND, !bBettaTestMode))
	{
		iStorePrice = 0; // > нулевая цена глушит и саму сделку в ChangeQTY_EDIT
		SetFormatedText("QTY_INFO_STORE_PRICE", XI_ConvertString("Price buy") + NewStr() + "-");
	}
	else
	{
		iStorePrice = GetStoreGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_SELL, pchar, 1);
		// для моря, чтоб было не выгодно
		if (bSeaTrade)
		{
			iStorePrice /= 2;
			if (iStorePrice < 1) iStorePrice = 1;
		}
		SetFormatedText("QTY_INFO_STORE_PRICE", XI_ConvertString("Price buy") + NewStr() + its(iStorePrice));
	}
	if (!StoreCanSellGood(refStore, iGoodIndex) || and(iTradeType == TRADE_TYPE_AMMUNITION, bSeaTrade))
	{
		iShipPrice = 0; // > нулевая цена глушит и саму сделку в ChangeQTY_EDIT
		SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + "-");
	}
	else if (iTradeType == TRADE_TYPE_CONTRABAND && !bPirateBase)
	{
		iShipPrice = 0;
		SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + "-");
	}
	else
	{
		iShipPrice = GetStoreGoodsPrice(refStore, iGoodIndex, PRICE_TYPE_BUY, pchar, 1);
		SetFormatedText("QTY_INFO_SHIP_PRICE", XI_ConvertString("Price sell") + NewStr() + its(iShipPrice));
	}
	ShowFoodInfo();
}

void ShowFoodInfo()
{
	int iPreview;
	string sGoodName;

	if (iCurGoodsIdx == GOOD_FOOD || iCurGoodsIdx == GOOD_RUM)
	{
		sGoodName = Goods[iCurGoodsIdx].name;
		iPreview = iShipQty + BuyOrSell * sti(GameInterface.qty_edit.str);
		if (iPreview < 0) iPreview = 0;

		// чтоб прикинуть как оно будет, скинем на время колво на продажное
		refCharacter.Ship.Cargo.Goods.(sGoodName) = iPreview;
		if (iCurGoodsIdx == GOOD_FOOD) SetFoodShipInfo(refCharacter, "QTY_FOOD_INFO");
		else SetRumShipInfo(refCharacter, "QTY_FOOD_INFO"); // Warship 11.07.09 На сколько хватит рому
		refCharacter.Ship.Cargo.Goods.(sGoodName) = iShipQty;
	}
	else
	{
		SetFormatedText("QTY_FOOD_INFO", "");
	}
}

void TransactionOK()
{
	int nTradeQuantity, moneyback, howMany, iTime = 15;
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

		AddCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		moneyback = makeint(iShipPrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5);
		pchar.money = sti(pchar.money) - moneyback;
		if (!bSeaTrade)
		{
			SetStoreGoods(refStore, iCurGoodsIdx, iStoreQty - nTradeQuantity);
			refStore.money = sti(refStore.money) + moneyback;
		}
		else
		{
			RemoveCharacterGoods(refShipChar, iCurGoodsIdx, nTradeQuantity);
			refShipChar.money = sti(refShipChar.money) + moneyback;
		}
		Statistic_AddValue(Pchar, "Money_spend", moneyback);
		// boal  check skill -->
		AddCharacterExpToSkill(pchar, "Commerce", moneyback / 800.0);
		// boal <--
	}
	else // SELL
	{
		CheckPGGQuestGoods(iCurGoodsIdx, nTradeQuantity); //фикс продажи товаров и сверх заработка у ПГГ
		RemoveCharacterGoods(refCharacter, iCurGoodsIdx, nTradeQuantity);
		moneyback = makeint(iStorePrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5);
		pchar.money = sti(pchar.money) + moneyback;
		if (!bSeaTrade)
		{
			SetStoreGoods(refStore, iCurGoodsIdx, iStoreQty + nTradeQuantity);
			refStore.money = sti(refStore.money) - moneyback;
		}
		else
		{
			AddCharacterGoods(refShipChar, iCurGoodsIdx, nTradeQuantity);
			refShipChar.money = sti(refShipChar.money) - moneyback;
		}
		Statistic_AddValue(Pchar, "Money_get", moneyback);
		AddCharacterExpToSkill(pchar, "Commerce", moneyback / 1600.0); // boal  check skill
	}

	howMany = nTradeQuantity / sti(Goods[iCurGoodsIdx].Units);
	if (howMany > 20)
	{
		if (howMany > 20 && howMany <= 50 + rand(5))    iTime = 15 + rand(10);
		else if (howMany > 50 && howMany <= 100 + rand(10))    iTime = 25 + rand(15);
		else if (howMany > 100 && howMany <= 250 + rand(25))    iTime = 35 + rand(20);
		else if (howMany > 250 && howMany <= 500 + rand(50))    iTime = 60 + rand(10);
		else if (howMany > 500 && howMany <= 1000 + rand(100))    iTime = 120 + rand(20);
		else if (howMany > 1000)                                iTime = 180 + rand(30);
	}

	if (CheckOfficer("treasurer"))
	{
		AddCharacterExpToSkill(RefOfficer("treasurer"), SKILL_COMMERCE, moneyback / 800.0);
		iTime /= 2;
	}

	if (GetOfficersPerkUsing(refCharacter, "QuickCalculation", false))
		iTime /= 2;

	WaitDate("", 0, 0, 0, 0, iTime);

	AddToTable(FilterMode);
	EndTooltip();
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
	SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	int iWeight, iTradeType;
	SetShipWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);

	string GoodName = goods[iCurGoodsIdx].name;
	iTradeType = MakeInt(refStore.Goods.(GoodName).TradeType);

	if (sti(GameInterface.qty_edit.str) == 0)
	{
		SetFormatedText("QTY_Result", "");
		BuyOrSell = 0;
	}
	else
	{
		if (sti(GameInterface.qty_edit.str) < 0 || BuyOrSell == -1)  //Игрок продаёт этот товар
		{
			if (BuyOrSell != -1)
			{
				GameInterface.qty_edit.str = -sti(GameInterface.qty_edit.str);
			}
			BuyOrSell = -1;
			if (iTradeType == TRADE_TYPE_CONTRABAND && !bBettaTestMode)
			{
				// контрабанду нельзя продать
				GameInterface.qty_edit.str = 0;
			}
			if (!StoreCanBuyGood(refStore, iCurGoodsIdx)) GameInterface.qty_edit.str = 0; // > магазин этот товар не покупает
			if (iStorePrice <= 0)
			{
				GameInterface.qty_edit.str = 0;
				iWeight = 0;
			}
			else
			{
				// проверка на колво доступное -->
				if (!bSeaTrade)
				{
					if (makeint(iStorePrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5) > sti(refStore.money))
					{
						GameInterface.qty_edit.str = makeint(sti(refStore.money) * iUnits / iStorePrice);
					}
				}
				if (bSeaTrade)
				{
					if (makeint(iStorePrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5) > sti(refShipChar.money))
					{
						GameInterface.qty_edit.str = makeint(sti(refShipChar.money) * iUnits / iStorePrice);
					}
				}
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
					GameInterface.qty_edit.str = makeint(iWeight / fWeight * iUnits); // округление
				}
				// проверка на колво доступное <--
			}
			SetFormatedText("QTY_Result", XI_ConvertString("SELL") + NewStr() + XI_convertString("money quantity") + " " + makeint(iStorePrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5) + ", " + XI_convertString("weight") + " " + iWeight + " " + XI_convertString("cwt"));
		}
		else //Игрок покупает этот товар
		{
			// не нужно у кэпов в море покупать порох и ядра, а то потом они беззащитны
			if (iTradeType == TRADE_TYPE_AMMUNITION && bSeaTrade)
			{
				GameInterface.qty_edit.str = 0;
			}
			BuyOrSell = 1;
			//Покупка контрабанды доступна только пиратам
			if (iTradeType == TRADE_TYPE_CONTRABAND && !bPirateBase && !bBettaTestMode)
			{
				GameInterface.qty_edit.str = 0;
			}
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
			if (iShipPrice <= 0)
			{
				GameInterface.qty_edit.str = 0;
				iWeight = 0;
			}
			else if (makeint(iShipPrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5) > sti(pchar.money))
			{
				GameInterface.qty_edit.str = makeint(sti(pchar.money) * iUnits / iShipPrice);
				iWeight = GetGoodWeightByType(iCurGoodsIdx, sti(GameInterface.qty_edit.str));
			}
			// проверка на колво доступное <--
			SetFormatedText("QTY_Result", XI_ConvertString("BUY") + NewStr() + XI_convertString("money quantity") + " " + makeint(iShipPrice * stf(GameInterface.qty_edit.str) / iUnits + 0.5) + ", " + XI_convertString("weight") + " " + iWeight + " " + XI_convertString("cwt"));
		}
	}
	// если получили ноль
	if (sti(GameInterface.qty_edit.str) <= 0)
	{
		SetFormatedText("QTY_Result", "");
		BuyOrSell = 0;
	}
	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell * sti(GameInterface.qty_edit.str)));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iShipQty + BuyOrSell * sti(GameInterface.qty_edit.str)));
	SetShipWeight();
	fShipWeight = fShipWeight + BuyOrSell * iWeight;
	fStoreWeight = fStoreWeight - BuyOrSell * iWeight;
	SetVariable();
	ShowFoodInfo();
}

void REMOVE_ALL_BUTTON()  // продать все
{
	if (!GetRemovable(refCharacter)) return;
	if (!bShowChangeWin)
	{
		ShowItemInfo();
	}
	//ShowGoodsInfo(iCurGoodsIdx); //HardCoffee TODO: после тестов убрать
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
	//ShowGoodsInfo(iCurGoodsIdx);
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

void Autotrade_All()
{
	int i, cn;
	ref chref;

	iAutotradeSeconds = 0;

	for (i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(PChar, i);
		if (cn > 0)
		{
			chref = GetCharacter(cn);
			if (!GetRemovable(chref)) continue;
			Autotrade_Goods(chref);
		}
	}

	if (iAutotradeSeconds > 0)
	{
		WaitDate("", 0, 0, 0, 0, iAutotradeSeconds);
		iAutotradeSeconds = 0;
	}

	AddToTable(FilterMode);
	EndTooltip();
}

int iAutotradeSeconds = 0;

void Autotrade_Goods(ref rChar)
{
	int i, iNeedGood, iCost, iStoreGoodQty;

	ref rGood;
	string sGood;
	float fNeedCargo;
	int iCurGoodQty, iNeedGoodsQty, iFreeCargo;
	int iMoneyQty = 0;

	for (i = 0; i < GOODS_QUANTITY; i++)
	{
		rGood = &Goods[i];
		sGood = rGood.name;

		if (!CheckAttribute(rChar, "TransferGoods." + sGood))
		{
			rChar.TransferGoods.(sGood) = 0;
		}

		iCurGoodQty = GetCargoGoods(rChar, i); // Сколько этого товара есть сейчас
		iNeedGoodsQty = sti(rChar.TransferGoods.(sGood)); // Сколько нужно ВСЕГО данного товара (не докупить!)
		//нужно ли чекать атрибут, если не заполнен - проверить логи

		if (iCurGoodQty == iNeedGoodsQty) continue; // ничего не нужно

		if (CheckAttribute(rChar, "TransferGoods.SellRestriction"))
		{
			if (iCurGoodQty > iNeedGoodsQty) // продаем
			{
				if (!StoreCanBuyGood(refStore, i)) continue; // > магазин этот товар не покупает
				if (CheckAttribute(refStore, "goods." + sGood + ".tradetype"))
				{
					if (refStore.goods.(sGood).tradetype == TRADE_TYPE_CONTRABAND || refStore.goods.(sGood).tradetype == TRADE_TYPE_CANNONS) continue;
				}
				iNeedGood = iCurGoodQty - iNeedGoodsQty; // Столько нужно продать

				/*if(bSeaTrade)//если продаём на корабль в море
				//Отключаю кнопку торговли в море, этот фрагмент пока не нужен
				{
					iFreeCargo = GetCargoFreeSpace(refShipChar);
					if (fNeedCargo > iFreeCargo) iNeedGood = iFreeCargo / sti(rGood.weight) * sti(rGood.Units);
				}
				*/

				RemoveCharacterGoodsSelf(rChar, i, iNeedGood); // Забираем только у этого перса
				AddStoreGoods(refStore, i, iNeedGood); // Прибавляем товар в магаз

				iCost = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_SELL, PChar, 1) * iNeedGood / sti(rGood.Units); // Цена товара для продажи

				iAutotradeSeconds++;
				iMoneyQty += iCost;
			}
		}

		if (iCurGoodQty < iNeedGoodsQty) // докупаем
		{
			if (!StoreCanSellGood(refStore, i)) continue; // > магазин этот товар не продаёт
			if (CheckAttribute(refStore, "goods." + sGood + ".tradetype") && refStore.goods.(sGood).tradetype == TRADE_TYPE_CONTRABAND)
			{
				if (!CheckAttribute(rChar, "TransferGoods.BuyContraband")) continue;
			}

			iNeedGood = iNeedGoodsQty - iCurGoodQty; // Столько нужно купить
			iStoreGoodQty = GetStoreGoodsQuantity(refStore, i); // Сколько можем купить (скоко есть в магазе)
			if (iNeedGood > iStoreGoodQty) iNeedGood = iStoreGoodQty; // Хотим купить больше, чем есть в магазе
			fNeedCargo = iNeedGood * stf(rGood.weight) / stf(rGood.Units);
			iFreeCargo = GetCargoFreeSpace(rChar); //проверить, что учитывается вес матросов, если включен
			if (fNeedCargo > iFreeCargo) iNeedGood = iFreeCargo / sti(rGood.weight) * sti(rGood.Units);

			iCost = GetStoreGoodsPrice(refStore, i, PRICE_TYPE_BUY, PChar, 1) * iNeedGood / sti(rGood.Units); // Цена товара для покупки
			if (sti(PChar.Money) >= iCost)
			{
				AddCharacterGoodsSimple(rChar, i, iNeedGood); // Даем только в этот корабль

				RemoveStoreGoods(refStore, i, iNeedGood); // Изымаем из магаза
				iAutotradeSeconds++;
				iMoneyQty -= iCost;
			}
		}
	}

	if (iMoneyQty != 0) // Если хоть что-то продали или купили
	{
		AddmoneyToCharacter(PChar, iMoneyQty);

		if (CheckOfficer("treasurer"))
			AddCharacterExpToSkill(RefOfficer("treasurer"), "Commerce", MakeInt(abs(iMoneyQty) / 800) + rand(1) + 2); // Экспа в навык торговли
	}
}
// TODO: автозакупку вернуть обатно из ванилы

void OnHeaderClick()
{
	string sControl = GetEventData();
	int iColumn = GetEventData();

	if (sControl == "TABLE_LIST") SortStoreGoods(iColumn, false, sControl);
}

void SortStoreGoods(int column, bool preserveState, string tableName)
{
	string datatype = "integer";
	switch (column)
	{
		case 4: datatype = "string"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 0);
}
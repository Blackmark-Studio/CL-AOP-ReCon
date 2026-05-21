/// boal 07/06/06 переделка СЖ под нужны ВМЛ
// Sith в сж добавлен журнал торговли
#event_handler("Control Activation", "ProcessInterfaceControls"); // обработка нажатия клавы

ref xi_refCharacter;
int curQuestTop;
string CurTable, CurRow;
int iMaxGoodsStore = 50000;
int currentTab = 0;
int maxQuestsNum = 0;

void InitInterface(string iniName)
{
	xi_refCharacter = pchar;
	InterfaceStack.SelectMenu_node = "LaunchQuestBook"; // запоминаем, что звать по Ф2
	GameInterface.title = "titleQuestBook";

	SetEventHandler("SetMaxStringsQuantity", "SetMaxStringsQuantity", 0);

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);
	SetFontType();

	selectJournal(1); // первый режим журнала, только активные

	SetEventHandler("InterfaceBreak", "ProcessCancelExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);

	SetEventHandler("eTabControlPress", "procTabChange", 0);
	SetEventHandler("SetScrollerPos", "SetScrollerPos", 0);
	SetEventHandler("ScrollPosChange", "ProcScrollPosChange", 0);
	SetEventHandler("ScrollTopChange", "ProcScrollChange", 0);
	SetEventHandler("ievnt_command", "ProcessCommandExecute", 0);
	SetEventHandler("QuestTopChange", "QuestTopChange", 0);
	SetEventHandler("QuestActivate", "XI_QuestActivate", 0);
	SetEventHandler("QuestDeActivate", "QuestDeActivate", 0);
	SetEventHandler("MouseRClickUp", "HideInfoWindow", 0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ShowInfoWindow", "ShowInfoWindow", 0); // belamour окно инфы на пкм
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);

	XI_RegistryExitKey("IExit_F3");

	// belamour для выхода из меню корабля или персонажа -->
	if (CheckAttribute(pchar, "SystemInfo.ShowShip"))
	{
		SetControlsTabModeManual(5);
		DeleteAttribute(pchar, "SystemInfo.ShowShip");
	}
	else
	{
		SetControlsTabModeManual(1); // первый режим журнала, только активные
	}
	// <--
	InitTableHeader();

	// доп инфа в шапку --->
	SetFormatedText("WEIGHT", FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / " + GetMaxItemsWeight(xi_refCharacter));
	SetFormatedText("MONEY", FindMoneyString(sti(xi_refCharacter.money)));
	SetFormatedText("CURRENT_DATE_CAPTION", GetDateString() + " " + GetTimeString());
	// <--
	//	SetFormatedText("Dublon", FindMoneyString(sti(xi_refCharacter.dublon)));
	SetFormatedText("Rank", xi_refCharacter.rank);
	SetFormatedText("Rank_progress", GetCharacterRankRateCur(xi_refCharacter) + " / " + GetCharacterRankRate(xi_refCharacter));
	// порог уровня
	GameInterface.StatusLine.BAR_RANK.Max = GetCharacterRankRate(xi_refCharacter);
	GameInterface.StatusLine.BAR_RANK.Min = 0;
	GameInterface.StatusLine.BAR_RANK.Value = GetCharacterRankRateCur(xi_refCharacter);
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "BAR_RANK", 0);
	// <---
	SetFormatedText("Difficulty", XI_ConvertString("m_Complexity") + ": " + GetLevelComplexity(MOD_SKILL_ENEMY_RATE));

	string herotype = XI_ConvertString("Corsair");
	if (pchar.HeroParam.HeroType == "Adventurer") herotype = XI_ConvertString("Adventurer");
	else if (pchar.HeroParam.HeroType == "Merchant") herotype = XI_ConvertString("Merchant");
	else if (pchar.HeroParam.HeroType == "Inquisitor") herotype = XI_ConvertString("Inquisitor");
	else if (pchar.HeroParam.HeroType == "SecretAgent") herotype = XI_ConvertString("SecretAgent");
	else if (pchar.HeroParam.HeroType == "Master") herotype = XI_ConvertString("Master");
	SetFormatedText("Herotype", XI_ConvertString("Archetype") + ": " + herotype);
}

// обработка нажатия клавы
void ProcessInterfaceControls()
{
	string controlName = GetEventData();

	if (controlName == "InterfaceGoLeft")
	{
		IDoExit(RC_INTERFACE_TO_SHIP);
	}
	if (controlName == "InterfaceGoRight")
	{
		IDoExit(RC_INTERFACE_TO_ALCHEMY);
	}
	if (controlName == "InterfaceTabSwitch")
	{
		currentTab = (currentTab + 1) % 8;
		SetControlsTabMode(currentTab + 1);
	}
	if (controlName == "IExit_F2")
	{
		IDoExit(RC_INTERFACE_TO_SHIP);
	}
	if (controlName == "IExit_F4")
	{
		IDoExit(RC_INTERFACE_TO_ITEMS);
	}
	if (controlName == "IExit_F5")
	{
		IDoExit(INTERFACE_NATIONRELATION);
	}
	if (controlName == "IExit_K")
	{
		IDoExit(RC_INTERFACE_TO_ALCHEMY);
	}
	if (controlName == "IExit_F1")
	{
		IDoExit(INTERFACE_CHARACTER_ALL);
	}
}
// метод на TAB переключает вкладки таблицы
void SetControlsTabModeManual(int mode)
{
	currentTab = mode - 1;
	SetControlsTabMode(mode);
}

void SetMaxStringsQuantity()
{
	maxQuestsNum = GetEventData();
}

void XI_SetQuestData()
{
	aref arefTmp;
	makearef(arefTmp, pchar.TmpQuestInfo);
	int nQuestsNum = GetAttributesNum(arefTmp);

	XI_SetQuestTitles("QUEST_TITLE", arefTmp, 0);
	curQuestTop = 0;

	if (currentTab > 2)
		HideQuests();
	else
	{
		SetNodeUsing("QUEST_TITLE", true);
		if (nQuestsNum <= maxQuestsNum)
			SetNodeUsing("QUESTSCROLL_TITLE", false);
		else
		{
			SetNodeUsing("QUESTSCROLL_TITLE", true);
			XI_SetScroller("QUEST_TITLE", 0.0);
		}
		SetNodeUsing("QUEST_TEXT", false);
		SetNodeUsing("QUESTSCROLL_TEXT", false);
	}

	SetAlertMarks(xi_refCharacter);
}

void HideQuests()
{
	SetNodeUsing("QUEST_TITLE", false);
	SetNodeUsing("QUEST_TEXT", false);
	SetNodeUsing("QUESTSCROLL_TITLE", false);
	SetNodeUsing("QUESTSCROLL_TEXT", false);
}

void HideCashBook()
{
	SetNodeUsing("SCROLL_DEBIT", false);
	SetNodeUsing("TABLE_DEBIT", false);
	SetNodeUsing("SCROLL_CREDIT", false);
	SetNodeUsing("TABLE_CREDIT", false);
}

void HideShipPlace()
{
	SetNodeUsing("TABLE_SHIP_PLACE", false);
	SetNodeUsing("SCROLL_SHIP_PLACE", false);
}

void HideStoreBook()
{
	SetNodeUsing("TABLE_CITY", false);
	SetNodeUsing("SCROLL_CITY", false);
	SetNodeUsing("TABLE_GOODS", false);
	SetNodeUsing("SCROLL_GOODS", false);
}

// tradebook --->
void HideTradeBook()
{
	SetNodeUsing("TRADEBOOK_TABLE_CITY", false);
	SetNodeUsing("TRADEBOOK_SCROLL_CITY", false);
	SetNodeUsing("TRADEBOOK_TABLE_GOODS", false);
	SetNodeUsing("TRADEBOOK_SCROLL_GOODS", false);
}
// <---
void HideStatistic()
{
	SetNodeUsing("TABLE_SHIPCLASS", false);
	SetNodeUsing("TABLE_HUMAN", false);
	SetNodeUsing("TABLE_NATION", false);
	SetNodeUsing("TABLE_OTHER", false);
	SetNodeUsing("DIFFICULTY", false);
	SetNodeUsing("HEROTYPE", false);
	// CreateString(true, "LevelComplexity", "", "INTERFACE_ULTRASMALL", COLOR_NORMAL, 0, 0, SCRIPT_ALIGN_RIGHT, 1);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void QuestTopChange()
{
	if (GetSelectable("QUEST_TITLE"))
	{
		int newTop = curQuestTop + GetEventData();

		aref arefTmp;
		makearef(arefTmp, pchar.TmpQuestInfo);
		int maxVal = GetAttributesNum(arefTmp);
		if (newTop >= maxVal)
		{
			newTop = maxVal - 1;
		}
		if (newTop < 0)
		{
			newTop = 0;
		}

		if (newTop != curQuestTop)
		{
			curQuestTop = newTop;
			XI_SetQuestTitles("QUEST_TITLE", arefTmp, curQuestTop);
			XI_SetScroller("QUEST_TITLE", MakeFloat(newTop) / MakeFloat(maxVal));
		}
	}
}

//void QuestTopChange()
//{
//	int iAdd = GetEventData();
//	int iCurOnPage = GetEventData();
//	aref arefTmp;
//	makearef(arefTmp, pchar.TmpQuestInfo);
//	int nQuestsNum = GetAttributesNum(arefTmp);
//	int maxVal = nQuestsNum - maxQuestsNum;
//	if (iAdd > 0 && curQuestTop >= maxVal)
//		return;
//	int newTop = curQuestTop + iAdd;
//	if (newTop >= nQuestsNum)
//		newTop = nQuestsNum - 1;
//	if (newTop < 0)
//		newTop = 0;
//	if (newTop != curQuestTop)
//	{
//		curQuestTop = newTop;
//		XI_SetQuestTitles("QUEST_TITLE", arefTmp, curQuestTop);
//		XI_SetScroller("QUEST_TITLE", MakeFloat(newTop) / MakeFloat(maxVal));
//	}
//}

void SetQTextShow(aref pA, int qnum)
{
	// boal Покраска, выбрали 22.06.07 -->
	aref arTopic = GetAttributeN(pA, qnum);
	string sTopic = GetAttributeName(arTopic);
	DeleteQuestHeaderColor(sTopic);
	if (CheckAttribute(arTopic, "color"))
	{
		DeleteAttribute(arTopic, "color");
		XI_SetQuestTitles("QUEST_TITLE", pA, 0);
		SetAlertMarks(xi_refCharacter);
	}

	SendMessage(&GameInterface, "lsal", MSG_INTERFACE_INIT_QTEXT_SHOW, "QUEST_TEXT", pA, qnum);
}

void XI_QuestActivate()
{
	int aq = curQuestTop + GetEventData();
	aref pA;
	makearef(pA, pchar.TmpQuestInfo);
	if (GetAttributesNum(pA) == 0) return;
	SetNodeUsing("QUEST_TEXT", true);
	SetNodeUsing("QUESTSCROLL_TEXT", true);
	SetQTextShow(pA, aq);
}

void XI_SetScroller(string nodName, float pos)
{
	switch (nodName)
	{
		case "QUEST_TITLE":
			SendMessage(&GameInterface, "lsf", MSG_INTERFACE_SET_SCROLLER, "QUESTSCROLL_TITLE", pos);
		break;
		case "QUEST_TEXT":
			SendMessage(&GameInterface, "lsf", MSG_INTERFACE_SET_SCROLLER, "QUESTSCROLL_TEXT", pos);
		break;
	}
}

void SetScrollerPos()
{
	string nodName = GetEventData();
	float pos = GetEventData();
	XI_SetScroller(nodName, pos);
}

void IDoExit(int exitCode)
{
	DelEventHandler("SetMaxStringsQuantity", "SetMaxStringsQuantity");
	DelEventHandler("InterfaceBreak", "ProcessCancelExit");
	DelEventHandler("exitCancel", "ProcessCancelExit");
	DelEventHandler("QuestTopChange", "QuestTopChange");
	DelEventHandler("QuestActivate", "XI_QuestActivate");
	DelEventHandler("SetScrollerPos", "SetScrollerPos");
	DelEventHandler("ScrollPosChange", "ProcScrollPosChange");
	DelEventHandler("ScrollTopChange", "ProcScrollChange");
	DelEventHandler("ievnt_command", "ProcessCommandExecute");
	DelEventHandler("eTabControlPress", "procTabChange");
	DelEventHandler("MouseRClickUp", "HideInfoWindow");
	DelEventHandler("QuestDeActivate", "QuestDeActivate");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ShowInfoWindow", "ShowInfoWindow"); // belamour окно инфы
	DelEventHandler("OnHeaderClick", "OnHeaderClick");

	interfaceResultCommand = exitCode;
	if (CheckAttribute(&InterfaceStates, "ReloadMenuExit"))
	{
		DeleteAttribute(&InterfaceStates, "ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}

void QuestDeActivate()
{
	XI_SetQuestData();
}

void ProcScrollPosChange()
{
	float newPos = GetEventData();
	string scrollName = GetEventData();
	if (scrollName == "QUESTSCROLL_TITLE")
	{
		aref arefTmp;
		makearef(arefTmp, pchar.TmpQuestInfo);
		int nQuests = GetAttributesNum(arefTmp);
		int maxVal = nQuests - maxQuestsNum;
		int newTop = makeint(newPos * maxVal + 0.5);

		if (newTop != curQuestTop)
		{
			curQuestTop = newTop;
			XI_SetQuestTitles("QUEST_TITLE", arefTmp, curQuestTop);
		}
	}
	else
	{
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "QUEST_TEXT", 1, newPos);
	}
}

void ProcScrollChange()
{
	int changeNum = GetEventData();
	if (changeNum == 0) return;
	string controlNode = "";
	if (GetSelectable("QUEST_TITLE")) controlNode = "QUEST_TITLE";
	if (GetSelectable("QUEST_TEXT")) controlNode = "QUEST_TEXT";

	if (controlNode != "")
	{
		if (changeNum > 0)
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, controlNode, -1, 0, ACTION_DOWNSTEP);
		}
		else
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, controlNode, -1, 0, ACTION_UPSTEP);
		}
	}
}

// Ни дня без костылей
// TODO ПЕРЕНЕСТИ в двигло
void SetScrollForSelectedTableRow(string tableNodeName, int selectRowIdx, int maxVisibleTableRows, int topIndex) {
	int i;

	GameInterface.(tableNodeName).select = 0;
	Table_UpdateWindow(tableNodeName);

	if (selectRowIdx <= 0) {
		return;
	}

	if (topIndex <= 0) {
		for (i = 0; i < selectRowIdx; i++)
			SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,tableNodeName, -1, 3, "downstep");
	} else {
		for (i = 0; i < maxVisibleTableRows + topIndex; i++)
			SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,tableNodeName, -1, 3, "downstep");

		int doDownQty = maxVisibleTableRows + topIndex - selectRowIdx;
		for (i = 0; i < doDownQty; i++)
			SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,tableNodeName, -1, 3, "upstep");
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	aref arCurRow;

	switch (nodName)
	{
		/////////////////////// menu ///////////////
		case "I_CHARACTER_2":
			if (comName == "click")
			{
				nodName = "I_CHARACTER";
			}
		break;
		case "I_SHIP_2":
			if (comName == "click")
			{
				nodName = "I_SHIP";
			}
		break;
		case "I_QUESTBOOK_2":
			if (comName == "click")
			{
				nodName = "I_QUESTBOOK";
			}
		break;
		case "I_ALCHEMY_2":
			if (comName == "click")
			{
				nodName = "I_ALCHEMY";
			}
		break;
		case "I_ITEMS_2":
			if (comName == "click")
			{
				nodName = "I_ITEMS";
			}
		break;
		case "I_NATIONS_2":
			if (comName == "click")
			{
				nodName = "I_NATIONS";
			}
		break;
		// belamour клик по кораблику
		case "TABLE_SHIP_PLACE":
			if (comName == "click")
			{
				// --> mitrokosta fix если не было кораблей, открывалось пустое меню
				makearef(arCurRow, GameInterface.(CurTable).(CurRow));
				if (!CheckAttribute(arCurRow, "UserData.IDX"))
				{
					break;
				}
				// mitrokosta <--
				int chrIdx = sti(arCurRow.UserData.IDX);
				pchar.SystemInfo.ShowShip = chrIdx;
				// if(XI_IsKeyPressed("control")) IDoExit(RC_INTERFACE_TO_CHAR);
				if (XI_IsKeyPressed("shift")) IDoExit(RC_INTERFACE_TO_SHIP);
			}
		break;

	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_CHARACTER" || nodName == "I_SHIP" || nodName == "I_QUESTBOOK" ||
	nodName == "I_ALCHEMY" || nodName == "I_ITEMS" || nodName == "I_NATIONS")
	{
		if (comName == "click")
		{
			InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame", 1, "sl", nodName, 2);
			return;
		}
	}
}

void selectJournal(int iMode)
{
	// HideQuests();
	SetFontType();
	HideCashBook();
	HideShipPlace();
	HideStoreBook();
	HideTradeBook();
	HideStatistic();
	// подменим квестовую ветку, зависимо от типа режима: журнал, архив, инфа
	aref arQuestInfo, arTmp;
	int i;
	string attributeName;
	aref newAttr;
	makearef(arQuestInfo, pchar.QuestInfo);
	DeleteAttribute(pchar, "TmpQuestInfo");
	pchar.TmpQuestInfo = "";
	for (i = 0; i < GetAttributesNum(arQuestInfo); i++)
	{
		arTmp = GetAttributeN(arQuestInfo, i);
		attributeName = GetAttributeName(arTmp);
		switch (iMode)
		{
			case 1:
				if (!CheckAttribute(pchar, "QuestInfo." + attributeName + ".InfoType") && sti(pchar.QuestInfo.(attributeName).Complete) == false)
				{
					SortedQuests(&arTmp);
				}
			break;

			case 2:
				if (!CheckAttribute(pchar, "QuestInfo." + attributeName + ".InfoType") && sti(pchar.QuestInfo.(attributeName).Complete) == true)
				{
					SortedQuests(&arTmp);
				}
			break;

			case 3:
				if (CheckAttribute(pchar, "QuestInfo." + attributeName + ".InfoType"))
				{
					CopyQuestInfoToTemp(pchar, &arTmp);
				}
			break;
		}
	}
	XI_SetQuestData();
}

void SortedQuests(aref arQuest)
{
	object oSorted;
	aref arTmp, aTmpQuestInfo;
	bool bSorted = false;
	int i;

	if (CheckAttribute(pchar, "TmpQuestInfo"))
	{
		makearef(aTmpQuestInfo, pchar.TmpQuestInfo);

		//если записей в pchar.TmpQuestInfo еще нет, то возвращем текущую
		if (GetAttributesNum(aTmpQuestInfo) == 0)
		{
			CopyQuestInfoToTemp(pchar, &arQuest);
			return;
		}
		oSorted.TmpQuestInfo = "";
		for (i = 0; i < GetAttributesNum(aTmpQuestInfo); i++)
		{
			arTmp = GetAttributeN(aTmpQuestInfo, i);

			//если нашли место для записи arQuest, то для всех остальных порядок не меняем
			if (bSorted)
			{
				CopyQuestInfoToTemp(&oSorted, &arTmp);
				continue;
			}
			//если дата и время закрытия квеста выше чем у существующей записи, то записываем пред текущей записью
			if (sti(arTmp.Order) < sti(arQuest.Order))
			{
				CopyQuestInfoToTemp(&oSorted, &arQuest);
				CopyQuestInfoToTemp(&oSorted, &arTmp);
				bSorted = true;
			}
			else
			{
				CopyQuestInfoToTemp(&oSorted, &arTmp);
			}
		}
		//если время закрытия arQuest позже всех остальных записей, то просто записывааем ее в хвост
		if (!bSorted) CopyQuestInfoToTemp(&oSorted, &arQuest);
	}
	else
	{
		CopyQuestInfoToTemp(pchar, &arQuest);
		return;
	}

	//копирование отсортированного списка в pchar.TmpQuestInfo для вывода в интерфейсе
	DeleteAttribute(pchar, "TmpQuestInfo");
	pchar.TmpQuestInfo = "";
	makearef(aTmpQuestInfo, oSorted.TmpQuestInfo);
	for (i = 0; i < GetAttributesNum(aTmpQuestInfo); i++)
	{
		arTmp = GetAttributeN(aTmpQuestInfo, i);
		CopyQuestInfoToTemp(pchar, &arTmp);
	}
}

void CopyQuestInfoToTemp(aref aCopy, aref arQuest)
{
	aref newAttr;
	string attributeName = GetAttributeName(arQuest);
	aCopy.TmpQuestInfo.(attributeName) = "";
	makearef(newAttr, aCopy.TmpQuestInfo.(attributeName));
	CopyAttributes(newAttr, arQuest);
}

void selectCashBook()
{
	SetNodeUsing("SCROLL_DEBIT", true);
	SetNodeUsing("TABLE_DEBIT", true);
	SetNodeUsing("SCROLL_CREDIT", true);
	SetNodeUsing("TABLE_CREDIT", true);
	CurTable = "TABLE_DEBIT";
	CurRow = "tr0";
	HideQuests();
	HideShipPlace();
	HideStoreBook();
	HideTradeBook();
	HideStatistic();
}

void selectShipPlace()
{
	SetNodeUsing("TABLE_SHIP_PLACE", true);
	SetNodeUsing("SCROLL_SHIP_PLACE", true);
	CurTable = "TABLE_SHIP_PLACE";
	CurRow = "tr0";
	HideQuests();
	HideCashBook();
	HideStoreBook();
	HideTradeBook();
	HideStatistic();
}

void selectStoreBook()
{
	SetNodeUsing("TABLE_CITY", true);
	SetNodeUsing("SCROLL_CITY", true);
	SetNodeUsing("TABLE_GOODS", true);
	SetNodeUsing("SCROLL_GOODS", true);
	CurTable = "TABLE_GOODS";
	CurRow = "tr0";
	HideQuests();
	HideCashBook();
	HideShipPlace();
	HideTradeBook();
	HideStatistic();
}
// tradebook --->
void selectTradeBook()
{
	SetNodeUsing("TRADEBOOK_TABLE_CITY", true);
	SetNodeUsing("TRADEBOOK_SCROLL_CITY", true);
	SetNodeUsing("TRADEBOOK_TABLE_GOODS", true);
	SetNodeUsing("TRADEBOOK_SCROLL_GOODS", true);
	CurTable = "TRADEBOOK_TABLE_GOODS";
	CurRow = "tr0";
	HideQuests();
	HideCashBook();
	HideShipPlace();
	HideStoreBook();
	HideStatistic();
}
// <---
void selectStatistic()
{
	SetNodeUsing("TABLE_SHIPCLASS", true);
	SetNodeUsing("TABLE_HUMAN", true);
	SetNodeUsing("TABLE_NATION", true);
	SetNodeUsing("TABLE_OTHER", true);
	SetNodeUsing("DIFFICULTY", true);
	SetNodeUsing("HEROTYPE", true);
	CurTable = "TABLE_HUMAN";
	CurRow = "tr0";
	HideQuests();
	HideCashBook();
	HideShipPlace();
	HideStoreBook();
	HideTradeBook();
}

void HideInfoWindow()
{
	CloseTooltip();
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem, picW, picH;
	aref arCurRow;
	ref rItem;

	makearef(arCurRow, GameInterface.(CurTable).(CurRow));
	sGroupPicture = "";
	sPicture = "-1";
	switch (sCurrentNode)
	{
		case "TABBTN_QUEST":
			sHeader = XI_ConvertString("QuestsBook");
			sText1 = XI_ConvertString("QuestsBook_Descr");
		break;
		case "TABBTN_QUESTARJ":
			sHeader = XI_ConvertString("QuestsLogBook");
			sText1 = XI_ConvertString("QuestsLogBook_Descr");
		break;
		case "TABBTN_INFO":
			sHeader = XI_ConvertString("DocsBook");
			sText1 = XI_ConvertString("DocsBook_Descr");
		break;
		case "TABBTN_CASHBOOK":
			sHeader = XI_ConvertString("CashBook");
			sText1 = XI_ConvertString("CashBook_Descr1");
			sText2 = XI_ConvertString("CashBook_Descr2");
		break;
		case "TABBTN_SHIP_PLACE":
			sHeader = XI_ConvertString("ShipsPlaceBook");
			sText1 = XI_ConvertString("ShipsPlaceBook_Descr1");
		break;
		case "TABBTN_STOREBOOK":
			sHeader = XI_ConvertString("StorageBook");
			sText1 = XI_ConvertString("StorageBook_Descr");
		break;
		case "TABBTN_TRADEBOOK":
			sHeader = XI_ConvertString("TradeBook");
			sText1 = XI_ConvertString("TradeBook_Descr1");
		break;
		case "TABBTN_STATISTIC":
			sHeader = XI_ConvertString("StatisticsBook");
			sText1 = XI_ConvertString("StatisticsBook_Descr");
		break;
		case "QUEST_TEXT":
			if (currentTab == 0)
			{
				sHeader = XI_ConvertString("QuestsBook");
				sText1 = XI_ConvertString("QuestsBook_Descr");
			}
			if (currentTab == 1)
			{
				sHeader = XI_ConvertString("QuestsLogBook");
				sText1 = XI_ConvertString("QuestsLogBook_Descr");
			}
			if (currentTab == 2)
			{
				sHeader = XI_ConvertString("DocsBook");
				sText1 = XI_ConvertString("DocsBook_Descr");
			}
		break;
		case "TABLE_CITY":
			sHeader = XI_ConvertString("StorageBook");
			sText1 = XI_ConvertString("StorageBook_Descr");
		break;
		case "TABLE_GOODS":
			sGroup = "GOODS";
			if (!CheckAttribute(arCurRow, "UserData.IDX"))
			{
				sHeader = XI_ConvertString("StorageBook");
				sText1 = XI_ConvertString("StorageBook_Descr");
			}
			else
			{
				if (sti(GameInterface.(CurTable).(CurRow).UserData.IsBank))
				{
					rItem = &Items[sti(GameInterface.(CurTable).(CurRow).UserData.IDX)];
					sPicture = "none";
					sGroup = rItem.picTexture;
					sGroupPicture = "itm" + rItem.picIndex;
					sHeader = GetConvertStr(rItem.name, "ItemsDescribe.txt");
					sText1 = GetConvertStr(rItem.describe, "ItemsDescribe.txt");
					picW = 128;
					picH = 128;
				}
				else
				{
					iItem = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
					sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
					sGroupPicture = GameInterface.(CurTable).(CurRow).UserData.ID;
					picW = 128;
					picH = 128;
					sText1 = GetAssembledString(GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID + "_descr", "GoodsDescribe.txt"), &Goods[iItem]);
				}
			}
		break;
		case "TABLE_SHIP_PLACE":
			if (!CheckAttribute(arCurRow, "UserData.IDX"))
			{
				sHeader = XI_ConvertString("ShipsPlaceBook");
				sText1 = XI_ConvertString("ShipsPlaceBook_Descr1");
			}
			else
			{
				int iShip = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
				ref refBaseShip = GetRealShip(iShip);

				sPicture = "INTERFACES\SHIPS\" + refBaseShip.BaseName + ".tga";
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = XI_ConvertString("Hull") + ": " + refBaseShip.hp + "\n";
				sText1 += XI_ConvertString("Sails") + ": " + refBaseShip.sp + "\n";
				sText1 += XI_ConvertString("Speed") + ": " + FloatToString(stf(refBaseShip.SpeedRate), 2) + "\n";
				sText1 += XI_ConvertString("Maneuver") + ": " + FloatToString(stf(refBaseShip.TurnRate), 2) + "\n";
				sText1 += XI_ConvertString("AgainstWind") + ": " + FloatToString(stf(refBaseShip.WindAgainstSpeed), 2) + "\n";
				sText1 += XI_ConvertString("Capacity") + ": " + refBaseShip.Capacity + "\n";
				sText1 += XI_ConvertString("Crew") + ": " + refBaseShip.MinCrew +" / " + refBaseShip.OptCrew + " / " + refBaseShip.MaxCrew + "\n";
				sText1 += XI_ConvertString("sCannons") + ": " + XI_ConvertString("caliber" + refBaseShip.MaxCaliber) + "\n";
				picW = 128;
				picH = 128;
			}
		break;
		case "TRADEBOOK_TABLE_CITY":
			sHeader = XI_ConvertString("TradeBook");
			sText1 = XI_ConvertString("TradeBook_Descr1");
		break;
		case "TRADEBOOK_TABLE_GOODS":
			sGroup = "GOODS";
			sGroupPicture = "";
			if (!CheckAttribute(arCurRow, "UserData.IDX"))
			{
				sHeader = XI_ConvertString("TradeBook");
				sText1 = XI_ConvertString("TradeBook_Descr1");
				sText2 = XI_ConvertString("TradeBook_Descr2");
			}
			else
			{
				if (CheckAttribute(arCurRow, "UserData.IsBank") && sti(GameInterface.(CurTable).(CurRow).UserData.IsBank))
				{
					rItem = &Items[sti(GameInterface.(CurTable).(CurRow).UserData.IDX)];
					sPicture = "none";
					sGroup = rItem.picTexture;
					sGroupPicture = "itm" + rItem.picIndex;
					sHeader = GetConvertStr(rItem.name, "ItemsDescribe.txt");
					sText1 = GetConvertStr(rItem.describe, "ItemsDescribe.txt");
					picW = 128;
					picH = 128;
				}
				else
				{
					iItem = sti(GameInterface.(CurTable).(CurRow).UserData.IDX);
					sGroupPicture = GameInterface.(CurTable).(CurRow).UserData.ID;
					sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
					sText1 = GetAssembledString(GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID + "_descr", "GoodsDescribe.txt"), &Goods[iItem]);
					sText2 = XI_ConvertString("TradeBook_Descr3");
					picW = 128;
					picH = 128;
				}
			}
		break;
		// sith --->
		case "WEIGHT":
			sHeader = XI_ConvertString("Weight");
			sText1 = GetRPGText("Weight_hint");
		break;
		case "MONEY":
			sHeader = XI_ConvertString("Money");
			sText1 = GetRPGText("Money_hint");
		break;
		case "RANK":
			sHeader = XI_ConvertString("Rank");
			sText1 = GetRPGText("Rank_hint");
		break;
		//<--- sith
	}
	CreateTooltip("#" + sHeader, sText1, argb(255, 255, 255, 255), sText2, argb(255, 255, 192, 192), sText3, argb(255, 192, 255, 192), "", argb(255, 255, 255, 255), sPicture, sGroup, sGroupPicture, picW, picH);
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	switch (sNodName)
	{
		case "TABBTN_QUEST":
			SetControlsTabModeManual(1);
		break;
		case "TABBTN_QUESTARJ":
			SetControlsTabModeManual(2);
		break;
		case "TABBTN_INFO":
			SetControlsTabModeManual(3);
		break;
		case "TABBTN_CASHBOOK":
			SetControlsTabModeManual(4);
		break;
		case "TABBTN_SHIP_PLACE":
			SetControlsTabModeManual(5);
		break;
		case "TABBTN_STOREBOOK":
			SetControlsTabModeManual(6);
		break;
		case "TABBTN_TRADEBOOK":
			SetControlsTabModeManual(7);
		break;
		case "TABBTN_STATISTIC":
			SetControlsTabModeManual(8);
		break;
	}
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(155, 196, 196, 196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;
	int nColor5 = nColor1;
	int nColor6 = nColor1;
	int nColor7 = nColor1;
	int nColor8 = nColor1;

	string sPic1 = "TabDeSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;
	string sPic5 = sPic1;
	string sPic6 = sPic1;
	string sPic7 = sPic1;
	string sPic8 = sPic1;

	switch (nMode)
	{
		case 1: //
			sPic1 = "TabSelected1";
			nColor1 = argb(255, 255, 255, 255);
		break;
		case 2:
			sPic2 = "TabSelected2";
			nColor2 = argb(255, 255, 255, 255);
		break;
		case 3:
			sPic3 = "TabSelected3";
			nColor3 = argb(255, 255, 255, 255);
		break;
		case 4:
			sPic4 = "TabSelected4";
			nColor4 = argb(255, 255, 255, 255);
		break;
		case 5:
			sPic5 = "TabSelected5";
			nColor5 = argb(255, 255, 255, 255);
		break;
		case 6:
			sPic6 = "TabSelected6";
			nColor6 = argb(255, 255, 255, 255);
		break;
		case 7:
			sPic7 = "TabSelected7";
			nColor7 = argb(255, 255, 255, 255);
		break;
		case 8:
			sPic8 = "TabSelected8";
			nColor8 = argb(255, 255, 255, 255);
		break;
	}

	SetNewGroupPicture("TABBTN_QUEST", "QUESTBOOK", sPic1);
	SetNewGroupPicture("TABBTN_QUESTARJ", "QUESTBOOK", sPic2);
	SetNewGroupPicture("TABBTN_INFO", "QUESTBOOK", sPic3);
	SetNewGroupPicture("TABBTN_CASHBOOK", "QUESTBOOK", sPic4);
	SetNewGroupPicture("TABBTN_SHIP_PLACE", "QUESTBOOK", sPic5);
	SetNewGroupPicture("TABBTN_STOREBOOK", "QUESTBOOK", sPic6);
	SetNewGroupPicture("TABBTN_TRADEBOOK", "QUESTBOOK", sPic7);
	SetNewGroupPicture("TABBTN_STATISTIC", "QUESTBOOK", sPic8);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_QUEST", 8, 0, nColor1);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_QUESTARJ", 8, 0, nColor2);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_INFO", 8, 0, nColor3);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_CASHBOOK", 8, 0, nColor4);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_SHIP_PLACE", 8, 0, nColor5);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_STOREBOOK", 8, 0, nColor6);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_TRADEBOOK", 8, 0, nColor7);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_STATISTIC", 8, 0, nColor8);

	currentTab = nMode - 1;
	FillControlsList(nMode);
	if (currentTab > 2) XI_SetQuestData();
}

void FillControlsList(int nMode)
{
	switch (nMode)
	{
		case 1: selectJournal(1); break;    // первый режим журнала, только активные
		case 2: selectJournal(2); break;    // только закрытые
		case 3: selectJournal(3); break;    // только инфа
		case 4: selectCashBook(); break;    // кассовая книга
		case 5: selectShipPlace(); break;    // корабли на приколе
		case 6: selectStoreBook(); break;    // складская книга
		case 7: selectTradeBook(); break;    // журнал торговли
		case 8: selectStatistic(); break;    // статистика
	}
}

void InitTableHeader()
{
	int i;
	string row;

	GameInterface.TABLE_SHIPCLASS.hr.td1.str = XI_ConvertString("Ships");
	GameInterface.TABLE_SHIPCLASS.hr.td1.line_space_modifier = 0.8;
	GameInterface.TABLE_SHIPCLASS.hr.td2.str = XI_ConvertString("QuestBookInfo_1");
	GameInterface.TABLE_SHIPCLASS.hr.td2.line_space_modifier = 0.8;
	GameInterface.TABLE_SHIPCLASS.hr.td3.str = XI_ConvertString("QuestBookInfo_2");
	GameInterface.TABLE_SHIPCLASS.hr.td3.line_space_modifier = 0.8;
	GameInterface.TABLE_SHIPCLASS.hr.td4.str = XI_ConvertString("QuestBookInfo_3");
	GameInterface.TABLE_SHIPCLASS.hr.td4.line_space_modifier = 0.8;

	for (i = 1; i < 7; i++)
	{
		row = "tr" + i;
		GameInterface.TABLE_SHIPCLASS.(row).td1.str = XI_ConvertString("StatClass") + i;
		GameInterface.TABLE_SHIPCLASS.(row).td2.str = Statistic_AddValue(pchar, "KillShip_" + i, 0);
		GameInterface.TABLE_SHIPCLASS.(row).td3.str = Statistic_AddValue(pchar, "KillAbordShip_" + i, 0);
		GameInterface.TABLE_SHIPCLASS.(row).td4.str = Statistic_AddValue(pchar, "AbordShip_" + i, 0);
	}

	GameInterface.TABLE_HUMAN.hr.td1.str = XI_ConvertString("People Killed");
	GameInterface.TABLE_HUMAN.hr.td2.str = XI_ConvertString("QuestBookInfo_4");
	GameInterface.TABLE_HUMAN.hr.td3.str = XI_ConvertString("QuestBookInfo_5");

	GameInterface.TABLE_HUMAN.tr1.td1.str = XI_ConvertString("Soldiers");
	GameInterface.TABLE_HUMAN.tr1.td2.str = Statistic_AddValue(pchar, "Solder_s", 0);
	GameInterface.TABLE_HUMAN.tr1.td3.str = Statistic_AddValue(pchar, "Solder_g", 0);

	GameInterface.TABLE_HUMAN.tr2.td1.str = XI_ConvertString("Citizens");
	GameInterface.TABLE_HUMAN.tr2.td2.str = Statistic_AddValue(pchar, "Citizen_s", 0);
	GameInterface.TABLE_HUMAN.tr2.td3.str = Statistic_AddValue(pchar, "Citizen_g", 0);

	GameInterface.TABLE_HUMAN.tr3.td1.str = XI_ConvertString("Undeads");
	GameInterface.TABLE_HUMAN.tr3.td2.str = Statistic_AddValue(pchar, "Monster_s", 0);
	GameInterface.TABLE_HUMAN.tr3.td3.str = Statistic_AddValue(pchar, "Monster_g", 0);

	GameInterface.TABLE_HUMAN.tr4.td1.str = XI_ConvertString("Others");
	GameInterface.TABLE_HUMAN.tr4.td2.str = Statistic_AddValue(pchar, "Warrior_s", 0);
	GameInterface.TABLE_HUMAN.tr4.td3.str = Statistic_AddValue(pchar, "Warrior_g", 0);

	GameInterface.TABLE_HUMAN.tr5.td1.str = XI_ConvertString("QuestbookTotal");
	GameInterface.TABLE_HUMAN.tr5.td2.str = Statistic_AddValue(pchar, "Solder_s", 0) + Statistic_AddValue(pchar, "Citizen_s", 0) + Statistic_AddValue(pchar, "Monster_s", 0) + Statistic_AddValue(pchar, "Warrior_s", 0);
	GameInterface.TABLE_HUMAN.tr5.td3.str = Statistic_AddValue(pchar, "Solder_g", 0) + Statistic_AddValue(pchar, "Citizen_g", 0) + Statistic_AddValue(pchar, "Monster_g", 0) + Statistic_AddValue(pchar, "Warrior_g", 0);

	GameInterface.TABLE_OTHER.hr.td1.str = XI_ConvertString("Events");
	GameInterface.TABLE_OTHER.hr.td2.str = XI_ConvertString("Meaning");

	GameInterface.TABLE_OTHER.tr1.td1.str = XI_ConvertString("QuestBookInfo_6");
	GameInterface.TABLE_OTHER.tr1.td2.str = Statistic_AddValue(PChar, "SellShip", 0);

	GameInterface.TABLE_OTHER.tr2.td1.str = XI_ConvertString("QuestBookInfo_7");
	GameInterface.TABLE_OTHER.tr2.td2.str = Statistic_AddValue(PChar, "BuyShip", 0);

	GameInterface.TABLE_OTHER.tr3.td1.str = XI_ConvertString("QuestBookInfo_8");
	GameInterface.TABLE_OTHER.tr3.td2.str = Statistic_AddValue(PChar, "ShipMunity", 0);

	GameInterface.TABLE_OTHER.tr4.td1.str = XI_ConvertString("QuestBookInfo_9");
	GameInterface.TABLE_OTHER.tr4.td2.str = Statistic_AddValue(PChar, "SlavesMunity", 0);

	GameInterface.TABLE_OTHER.tr5.td1.str = XI_ConvertString("QuestBookInfo_10");
	GameInterface.TABLE_OTHER.tr5.td2.str = Statistic_AddValue(PChar, "AbordShipFree", 0);

	GameInterface.TABLE_OTHER.tr6.td1.str = XI_ConvertString("QuestBookInfo_11");
	GameInterface.TABLE_OTHER.tr6.td2.str = Statistic_AddValue(PChar, "RatsEatGoods", 0);

	GameInterface.TABLE_OTHER.tr7.td1.str = XI_ConvertString("QuestBookInfo_27");
	GameInterface.TABLE_OTHER.tr7.td2.str = pchar.SystemInfo.SaveCount + " / " + pchar.SystemInfo.LoadCount;

	GameInterface.TABLE_OTHER.tr8.td1.str = XI_ConvertString("QuestBookInfo_12");
	GameInterface.TABLE_OTHER.tr8.td2.str = sti(pchar.Health.TotalDamg);

	GameInterface.TABLE_OTHER.tr9.td1.str = XI_ConvertString("QuestBookInfo_13");
	GameInterface.TABLE_OTHER.tr9.td2.str = Statistic_AddValue(PChar, "Sailors_dead", 0);

	GameInterface.TABLE_OTHER.tr10.td1.str = XI_ConvertString("QuestBookInfo_14");
	GameInterface.TABLE_OTHER.tr10.td2.str = Statistic_AddValue(PChar, "Treasure", 0);

	GameInterface.TABLE_OTHER.tr11.td1.str = XI_ConvertString("QuestBookInfo_20");
	GameInterface.TABLE_OTHER.tr11.td2.str = Statistic_AddValue(PChar, "Money_spend", 0);

	GameInterface.TABLE_OTHER.tr12.td1.str = XI_ConvertString("QuestBookInfo_21");
	GameInterface.TABLE_OTHER.tr12.td2.str = Statistic_AddValue(PChar, "PartitionPay", 0);

	GameInterface.TABLE_NATION.hr.td1.str = XI_ConvertString("Events");
	GameInterface.TABLE_NATION.hr.td2.icon.group = "NATIONS";
	GameInterface.TABLE_NATION.hr.td2.icon.image = Nations[0].Name;
	GameInterface.TABLE_NATION.hr.td2.icon.width = 32;
	GameInterface.TABLE_NATION.hr.td2.icon.height = 32;
	GameInterface.TABLE_NATION.hr.td2.icon.offset = "0, 0";
	GameInterface.TABLE_NATION.hr.td3.icon.group = "NATIONS";
	GameInterface.TABLE_NATION.hr.td3.icon.image = Nations[1].Name;
	GameInterface.TABLE_NATION.hr.td3.icon.width = 32;
	GameInterface.TABLE_NATION.hr.td3.icon.height = 32;
	GameInterface.TABLE_NATION.hr.td3.icon.offset = "0, 0";
	GameInterface.TABLE_NATION.hr.td4.icon.group = "NATIONS";
	GameInterface.TABLE_NATION.hr.td4.icon.image = Nations[2].Name;
	GameInterface.TABLE_NATION.hr.td4.icon.width = 32;
	GameInterface.TABLE_NATION.hr.td4.icon.height = 32;
	GameInterface.TABLE_NATION.hr.td4.icon.offset = "0, 0";
	GameInterface.TABLE_NATION.hr.td5.icon.group = "NATIONS";
	GameInterface.TABLE_NATION.hr.td5.icon.image = Nations[3].Name;
	GameInterface.TABLE_NATION.hr.td5.icon.width = 32;
	GameInterface.TABLE_NATION.hr.td5.icon.height = 32;
	GameInterface.TABLE_NATION.hr.td5.icon.offset = "0, 0";
	GameInterface.TABLE_NATION.hr.td6.icon.group = "NATIONS";
	GameInterface.TABLE_NATION.hr.td6.icon.image = Nations[4].Name;
	GameInterface.TABLE_NATION.hr.td6.icon.width = 32;
	GameInterface.TABLE_NATION.hr.td6.icon.height = 32;
	GameInterface.TABLE_NATION.hr.td6.icon.offset = "0, 0";
	GameInterface.TABLE_NATION.hr.td7.str = XI_ConvertString("QuestbookTotal");

	GameInterface.TABLE_NATION.tr1.td1.str = XI_ConvertString("QuestBookInfo_15");
	GameInterface.TABLE_NATION.tr1.td2.str = Statistic_AddValue(PChar, "eng_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td3.str = Statistic_AddValue(PChar, "fra_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td4.str = Statistic_AddValue(PChar, "spa_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td5.str = Statistic_AddValue(PChar, "hol_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td6.str = Statistic_AddValue(PChar, "pir_KillFort", 0);
	GameInterface.TABLE_NATION.tr1.td7.str = (Statistic_AddValue(PChar, "pir_KillFort", 0) +
				Statistic_AddValue(PChar, "eng_KillFort", 0) +
					Statistic_AddValue(PChar, "fra_KillFort", 0) +
						Statistic_AddValue(PChar, "spa_KillFort", 0) +
						Statistic_AddValue(PChar, "hol_KillFort", 0));

	GameInterface.TABLE_NATION.tr2.td1.str = XI_ConvertString("QuestBookInfo_16");
	GameInterface.TABLE_NATION.tr2.td2.str = Statistic_AddValue(PChar, "eng_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td3.str = Statistic_AddValue(PChar, "fra_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td4.str = Statistic_AddValue(PChar, "spa_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td5.str = Statistic_AddValue(PChar, "hol_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td6.str = Statistic_AddValue(PChar, "pir_TakeTown", 0);
	GameInterface.TABLE_NATION.tr2.td7.str = (Statistic_AddValue(PChar, "pir_TakeTown", 0) +
				Statistic_AddValue(PChar, "eng_TakeTown", 0) +
					Statistic_AddValue(PChar, "fra_TakeTown", 0) +
						Statistic_AddValue(PChar, "spa_TakeTown", 0) +
						Statistic_AddValue(PChar, "hol_TakeTown", 0));

	GameInterface.TABLE_NATION.tr3.td1.str = XI_ConvertString("QuestBookInfo_17");
	GameInterface.TABLE_NATION.tr3.td2.str = Statistic_AddValue(PChar, "eng_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td3.str = Statistic_AddValue(PChar, "fra_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td4.str = Statistic_AddValue(PChar, "spa_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td5.str = Statistic_AddValue(PChar, "hol_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td6.str = Statistic_AddValue(PChar, "pir_GrabbingTown", 0);
	GameInterface.TABLE_NATION.tr3.td7.str = (Statistic_AddValue(PChar, "pir_GrabbingTown", 0) +
				Statistic_AddValue(PChar, "eng_GrabbingTown", 0) +
					Statistic_AddValue(PChar, "fra_GrabbingTown", 0) +
						Statistic_AddValue(PChar, "spa_GrabbingTown", 0) +
						Statistic_AddValue(PChar, "hol_GrabbingTown", 0));

	GameInterface.TABLE_NATION.tr4.td1.str = XI_ConvertString("QuestBookInfo_18");
	GameInterface.TABLE_NATION.tr4.td2.str = Statistic_AddValue(PChar, "eng_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td3.str = Statistic_AddValue(PChar, "fra_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td4.str = Statistic_AddValue(PChar, "spa_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td5.str = Statistic_AddValue(PChar, "hol_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td6.str = Statistic_AddValue(PChar, "pir_AbordShip", 0);
	GameInterface.TABLE_NATION.tr4.td7.str = (Statistic_AddValue(PChar, "pir_AbordShip", 0) +
				Statistic_AddValue(PChar, "eng_AbordShip", 0) +
					Statistic_AddValue(PChar, "fra_AbordShip", 0) +
						Statistic_AddValue(PChar, "spa_AbordShip", 0) +
						Statistic_AddValue(PChar, "hol_AbordShip", 0));

	GameInterface.TABLE_NATION.tr5.td1.str = XI_ConvertString("QuestBookInfo_19");
	GameInterface.TABLE_NATION.tr5.td2.str = Statistic_AddValue(PChar, "eng_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td3.str = Statistic_AddValue(PChar, "fra_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td4.str = Statistic_AddValue(PChar, "spa_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td5.str = Statistic_AddValue(PChar, "hol_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td6.str = Statistic_AddValue(PChar, "pir_KillShip", 0);
	GameInterface.TABLE_NATION.tr5.td7.str = (Statistic_AddValue(PChar, "pir_KillShip", 0) +
				Statistic_AddValue(PChar, "eng_KillShip", 0) +
					Statistic_AddValue(PChar, "fra_KillShip", 0) +
						Statistic_AddValue(PChar, "spa_KillShip", 0) +
						Statistic_AddValue(PChar, "hol_KillShip", 0));

	Table_UpdateWindow("TABLE_SHIPCLASS");
	Table_UpdateWindow("TABLE_HUMAN");
	Table_UpdateWindow("TABLE_OTHER");
	Table_UpdateWindow("TABLE_NATION");

	//  ростовщики
	GameInterface.TABLE_CREDIT.hr.td1.str = XI_ConvertString("CreditCity");
	GameInterface.TABLE_CREDIT.hr.td2.str = XI_ConvertString("CreditSum");
	GameInterface.TABLE_CREDIT.hr.td3.str = XI_ConvertString("CreditDate");
	GameInterface.TABLE_CREDIT.hr.td4.str = XI_ConvertString("CreditTerm");
	GameInterface.TABLE_CREDIT.hr.td5.str = XI_ConvertString("CreditPercent");
	GameInterface.TABLE_CREDIT.select = 0;

	aref quests;
	aref quest;
	int nQuestsNum;
	int n;
	string sQuestName;
	i = 1;
	if (CheckAttribute(pchar, "Quest.Loans"))
	{
		makearef(quests, pchar.Quest.Loans);

		nQuestsNum = GetAttributesNum(quests);

		for (n = 0; n < nQuestsNum; n++)
		{
			quest = GetAttributeN(quests, n);

			sQuestName = GetAttributeName(quest);
			row = "tr" + i;
			i++;
			GameInterface.TABLE_CREDIT.(row).td1.str = GetCityName(sQuestName);
			GameInterface.TABLE_CREDIT.(row).td2.str = MakeMoneyShow(sti(Pchar.Quest.Loans.(sQuestName).Sum), MONEY_SIGN, MONEY_DELIVER);
			GameInterface.TABLE_CREDIT.(row).td3.str = GetBookData(sti(Pchar.Quest.Loans.(sQuestName).StartDay),
					sti(Pchar.Quest.Loans.(sQuestName).StartMonth),
					sti(Pchar.Quest.Loans.(sQuestName).StartYear));
			GameInterface.TABLE_CREDIT.(row).td4.str = Pchar.Quest.Loans.(sQuestName).Period;
			GameInterface.TABLE_CREDIT.(row).td5.str = Pchar.Quest.Loans.(sQuestName).Interest;
		}
	}
	Table_UpdateWindow("TABLE_CREDIT");

	GameInterface.TABLE_DEBIT.hr.td1.str = XI_ConvertString("DepCity");
	GameInterface.TABLE_DEBIT.hr.td2.str = XI_ConvertString("DepSum");
	GameInterface.TABLE_DEBIT.hr.td3.str = XI_ConvertString("DepDate");
	GameInterface.TABLE_DEBIT.hr.td4.str = XI_ConvertString("DepPercent");
	//	GameInterface.TABLE_DEBIT.hr.td5.str = XI_ConvertString("DepType");
	GameInterface.TABLE_DEBIT.select = 0;
	i = 1;
	if (CheckAttribute(pchar, "Quest.Deposits")) // не треться при возврате
	{
		makearef(quests, Characters[GetMainCharacterIndex()].Quest.Deposits);

		nQuestsNum = GetAttributesNum(quests);

		for (n = 0; n < nQuestsNum; n++)
		{
			quest = GetAttributeN(quests, n);

			sQuestName = GetAttributeName(quest);

			if (CheckAttribute(Pchar, "Quest.Deposits." + sQuestName + ".Sum"))
			{
				row = "tr" + i;
				i++;
				GameInterface.TABLE_DEBIT.(row).td1.str = GetCityName(sQuestName);
				//				GameInterface.TABLE_DEBIT.(row).td2.str = FindMoneyString(sti(xi_refCharacter.money))(sti(Pchar.Quest.Deposits.(sQuestName).Sum), MONEY_SIGN, MONEY_DELIVER);
				GameInterface.TABLE_DEBIT.(row).td2.str = MakeMoneyShow(sti(Pchar.Quest.Deposits.(sQuestName).Sum), MONEY_SIGN, MONEY_DELIVER);
				GameInterface.TABLE_DEBIT.(row).td3.str = GetBookData(sti(Pchar.Quest.Deposits.(sQuestName).StartDay),
						sti(Pchar.Quest.Deposits.(sQuestName).StartMonth),
						sti(Pchar.Quest.Deposits.(sQuestName).StartYear));
				GameInterface.TABLE_DEBIT.(row).td4.str = Pchar.Quest.Deposits.(sQuestName).Interest;
				//				if (HasSubStr(sQuestName, "_type1"))
				//				{
				//					GameInterface.TABLE_DEBIT.(row).td5.str = XI_ConvertString("DebitType1");
				//				}
				//				else
				//				{
				//					GameInterface.TABLE_DEBIT.(row).td5.str = XI_ConvertString("DebitType2");
				//				}
			}
		}
	}
	Table_UpdateWindow("TABLE_DEBIT");

	FillShipPlaceTable("TABLE_SHIP_PLACE"); // 1.2.3

	FillPriceListTown("TABLE_CITY");
	// tradebook --->
	TradebookFillPriceListTown("TRADEBOOK_TABLE_CITY");
	// <---
}

void FillShipPlaceTable(string _tabName)
{
	int cn, n, iPortManIndx;
	string row;
	ref rCity, chref;
	aref aDock, aTemp;

	// шапка -->
	GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "N";
	GameInterface.(_tabName).hr.td2.str = XI_ConvertString("Ship");
	GameInterface.(_tabName).hr.td2.textoffset = "40, 0";
	GameInterface.(_tabName).hr.td3.str = XI_ConvertString("Rank");
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("ColonyLevel4");
	GameInterface.(_tabName).hr.td5.str = XI_ConvertString("ColonyName");
	GameInterface.(_tabName).hr.td6.str = XI_ConvertString("MoorDate");
	GameInterface.(_tabName).hr.td7.str = XI_ConvertString("CostPerMonth");
	GameInterface.(_tabName).hr.td8.str = XI_ConvertString("PortmanRefundFee");
	GameInterface.(_tabName).hr.td8.line_space_modifier = 0.8;
	// <--
	cn = 1;
	for (n = 0; n < MAX_COLONIES; n++)
	{
		rCity = &Colonies[n];
		//TODO создать новую колонию под форт, иначе смириться с данными костылями
		if (rCity.id == "Pearl") iPortManIndx = GetCharacterIndex("Secret_Fort_Commander");
		else iPortManIndx = GetCharacterIndex(rCity.id + "_PortMan");
		if (iPortManIndx != -1)
		{
			makeref(chref, Characters[iPortManIndx]);
			if (CheckAttribute(chref, "ShipInStockMan"))
			{
				makearef(aDock, chref.ShipInStockMan);
				for (int i = 0; i < GetAttributesNum(aDock); i++)
				{
					row = "tr" + cn;
					aTemp = GetAttributeN(aDock, i);

					GameInterface.(_tabName).(row).UserData.IDX = sti(aTemp.Ship.Type); // belamour запомнить в кого тыкать будем
					GameInterface.(_tabName).(row).td1.str = cn;

					GameInterface.(_tabName).(row).td2.icon.texture = "INTERFACES\SHIPS\" + RealShips[sti(aTemp.Ship.Type)].BaseName + ".tga";
					GameInterface.(_tabName).(row).td2.icon.uv = "0,0,1,1";
					GameInterface.(_tabName).(row).td2.icon.offset = "0, 0";
					GameInterface.(_tabName).(row).td2.icon.width = 21;
					GameInterface.(_tabName).(row).td2.icon.height = 21;
					GameInterface.(_tabName).(row).td2.str = XI_ConvertString(RealShips[sti(aTemp.Ship.Type)].BaseName) + " '" + aTemp.Ship.Name + "'";
					GameInterface.(_tabName).(row).td2.line_space_modifier = 0.8;
					GameInterface.(_tabName).(row).td2.textoffset = "40, 0";

					GameInterface.(_tabName).(row).td3.str = sti(RealShips[sti(aTemp.Ship.Type)].Class) + "";

					GameInterface.(_tabName).(row).td4.icon.group = "NATIONS";
					if (chref.id == "Secret_Fort_Commander")
						GameInterface.(_tabName).(row).td4.icon.image = Nations[PIRATE].Name;
					else
						GameInterface.(_tabName).(row).td4.icon.image = Nations[sti(rCity.nation)].Name;
					GameInterface.(_tabName).(row).td4.icon.width = 21;
					GameInterface.(_tabName).(row).td4.icon.height = 21;
					GameInterface.(_tabName).(row).td4.icon.offset = "0, 0";
					if (chref.id == "Secret_Fort_Commander")
						GameInterface.(_tabName).(row).td4.str = GetConvertStr("Fort inside", "LocLables.txt");
					else
						GameInterface.(_tabName).(row).td4.str = GetConvertStr(rCity.id + " Town", "LocLables.txt");
					GameInterface.(_tabName).(row).td4.line_space_modifier = 0.8;
					GameInterface.(_tabName).(row).td4.textoffset = "10, 0";

					GameInterface.(_tabName).(row).td5.str = GetConvertStr(rCity.islandLable, "LocLables.txt");

					GameInterface.(_tabName).(row).td6.str = aTemp.AltDate;

					GameInterface.(_tabName).(row).td7.str = aTemp.MoneyForShip;

					int iPay = GetNpcQuestPastMonthParam(aTemp, "Date") * sti(aTemp.MoneyForShip);
					if (iPay <= 1) iPay = 0;
					GameInterface.(_tabName).(row).td8.str = iPay;
					GameInterface.(_tabName).(row).td8.color = argb(255, 255, 228, 80);
					GameInterface.(_tabName).(row).td8.scale = 0.85;

					cn++;
				}
			}
		}
	}
	Table_UpdateWindow(_tabName);
}

void FillPriceListTown(string _tabName)
{
	int i, cn, n, StoreNum;
	ref chref;
	string row, firstId, CityId;
	aref curItem;
	ref rCity;
	ref refStorage;

	// шапка -->
	GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Nation");
	GameInterface.(_tabName).hr.td2.str = XI_ConvertString("ColonyLevel4");
	GameInterface.(_tabName).hr.td3.str = XI_ConvertString("StoreType");
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("Workload");
	GameInterface.(_tabName).hr.td5.str = XI_ConvertString("Arenda");

	cn = 1;
	for (i = 1; i < MAX_CHARACTERS; i++)
	{
		makeref(chref, Characters[i]);
		if (CheckAttribute(chref, "Storage.Activate"))
		{
			row = "tr" + cn;
			//TODO создать новую колонию под бомжефорт, иначе смириться с данными костылями
			if (chref.id == "Secret_Fort_Commander")
			{
				if (n == 0) firstId = "Secret_Fort";
				GameInterface.(_tabName).(row).UserData.CityID = "Secret_Fort";
				GameInterface.(_tabName).(row).UserData.CityIDX = cn;
				GameInterface.(_tabName).(row).UserData.IsBank = 0;
				GameInterface.(_tabName).(row).td1.icon.group = "NATIONS";
				GameInterface.(_tabName).(row).td1.icon.image = Nations[PIRATE].Name;
				GameInterface.(_tabName).(row).td1.icon.width = 21;
				GameInterface.(_tabName).(row).td1.icon.height = 21;
				GameInterface.(_tabName).(row).td1.icon.offset = "5, 0";
				GameInterface.(_tabName).(row).td2.str = GetConvertStr("Fort inside", "LocLables.txt");
				GameInterface.(_tabName).(row).td3.str = GetConvertStr("Packhouse", "LocLables.txt");
				GameInterface.(_tabName).(row).td4.str = GetStorageUsedWeight(&Stores[SHIP_STORE]) + " / " + iMaxGoodsStore;
				GameInterface.(_tabName).(row).td5.str = GetNpcQuestPastMonthParam(chref, "Storage.Date") * sti(chref.MoneyForStorage);
				GameInterface.(_tabName).(row).td5.scale = 0.8;
			}
			else
			{
				CityId = chref.city;
				rCity = GetColonyByIndex(FindColony(CityId));
				StoreNum = GetStorage(CityId);
				refStorage = &stores[StoreNum];
				if (n == 0) firstId = CityId;
				GameInterface.(_tabName).(row).UserData.CityID = rCity.id;
				GameInterface.(_tabName).(row).UserData.CityIDX = cn;
				GameInterface.(_tabName).(row).UserData.IsBank = 0;
				GameInterface.(_tabName).(row).td1.icon.group = "NATIONS";
				GameInterface.(_tabName).(row).td1.icon.image = Nations[sti(rCity.nation)].Name;
				GameInterface.(_tabName).(row).td1.icon.width = 21;
				GameInterface.(_tabName).(row).td1.icon.height = 21;
				GameInterface.(_tabName).(row).td1.icon.offset = "5, 0";
				GameInterface.(_tabName).(row).td2.str = GetConvertStr(rCity.id + " Town", "LocLables.txt");
				GameInterface.(_tabName).(row).td3.str = GetConvertStr("Packhouse", "LocLables.txt");
				GameInterface.(_tabName).(row).td4.str = GetStorageUsedWeight(refStorage) + " / " + iMaxGoodsStore;
				GameInterface.(_tabName).(row).td5.str = GetNpcQuestPastMonthParam(chref, "Storage.Date") * sti(chref.MoneyForStorage);
				GameInterface.(_tabName).(row).td5.scale = 0.8;
			}
			cn++;
		}
		if (CheckAttribute(chref, "StorageOpen") && chref.StorageOpen == "Opened")
		{
			row = "tr" + cn;
			if (chref.id == "Secret_Fort_Commander")
			{
				//TODO создать новую колонию под бомжефорт, иначе смириться с данными костылями
				if (n == 0) firstId = "Secret_Fort";
				GameInterface.(_tabName).(row).UserData.CityID = "Secret_Fort";
				GameInterface.(_tabName).(row).UserData.CityIDX = cn;
				GameInterface.(_tabName).(row).UserData.IsBank = 1;
				GameInterface.(_tabName).(row).td1.icon.group = "NATIONS";
				GameInterface.(_tabName).(row).td1.icon.image = Nations[PIRATE].Name;
				GameInterface.(_tabName).(row).td1.icon.width = 21;
				GameInterface.(_tabName).(row).td1.icon.height = 21;
				GameInterface.(_tabName).(row).td1.icon.offset = "5, 0";
				GameInterface.(_tabName).(row).td2.str = GetConvertStr("Fort inside", "LocLables.txt");
				GameInterface.(_tabName).(row).td2.scale = 0.85;
				GameInterface.(_tabName).(row).td3.str = GetConvertStr("Warehouse", "LocLables.txt");
				GameInterface.(_tabName).(row).td3.scale = 0.8;
				GameInterface.(_tabName).(row).td4.str = sti(GetItemsWeight(&Stores[SHIP_STORE])) + " / 1000";
				GameInterface.(_tabName).(row).td4.scale = 0.8;
				GameInterface.(_tabName).(row).td5.str = GetNpcQuestPastMonthParam(chref, "Storage.Date") * sti(chref.StoragePrice);
				GameInterface.(_tabName).(row).td5.scale = 0.8;
			}
			else
			{
				CityId = chref.city;
				rCity = GetColonyByIndex(FindColony(CityId));
				StoreNum = GetStorage(CityId);
				refStorage = &stores[StoreNum];
				if (n == 0) firstId = CityId;
				GameInterface.(_tabName).(row).UserData.CityID = rCity.id;
				GameInterface.(_tabName).(row).UserData.CityIDX = cn;
				GameInterface.(_tabName).(row).UserData.IsBank = 1;
				GameInterface.(_tabName).(row).td1.icon.group = "NATIONS";
				GameInterface.(_tabName).(row).td1.icon.image = Nations[sti(rCity.nation)].Name;
				GameInterface.(_tabName).(row).td1.icon.width = 21;
				GameInterface.(_tabName).(row).td1.icon.height = 21;
				GameInterface.(_tabName).(row).td1.icon.offset = "5, 0";
				GameInterface.(_tabName).(row).td2.str = GetConvertStr(rCity.id + " Town", "LocLables.txt");
				GameInterface.(_tabName).(row).td2.scale = 0.85;
				GameInterface.(_tabName).(row).td3.str = GetConvertStr("Usurer House", "LocLables.txt");
				GameInterface.(_tabName).(row).td3.scale = 0.8;
				GameInterface.(_tabName).(row).td4.str = sti(GetItemsWeight(refStorage)) + " / 1000";
				GameInterface.(_tabName).(row).td4.scale = 0.8;
				GameInterface.(_tabName).(row).td5.str = GetNpcQuestPastMonthParam(chref, "Storage.Date") * sti(chref.StoragePrice);
				GameInterface.(_tabName).(row).td5.scale = 0.8;
			}
			cn++;
		}
	}
	Table_UpdateWindow(_tabName);
	FillPriceList("TABLE_GOODS", firstId, "");
}

void TableSelectChange()
{
	// Log_TestInfo("Click!");
	string sControl = GetEventData();
	int iSelected = GetEventData();
	CurTable = sControl;
	CurRow = "tr" + (iSelected);
	NullSelectTable("TABLE_GOODS");
	if (CurTable == "TABLE_CITY")
	{
		FillPriceList("TABLE_GOODS", GameInterface.(CurTable).(CurRow).UserData.CityID, GameInterface.(CurTable).(CurRow).UserData.IsBank);
	}
	// tradebook --->
//	NullSelectTable("TRADEBOOK_TABLE_GOODS");
	if (CurTable == "TRADEBOOK_TABLE_CITY")
	{
		TradebookFillPriceList("TRADEBOOK_TABLE_GOODS", GameInterface.(CurTable).(CurRow).UserData.CityID);
	}
	// <---
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
		GameInterface.(sControl).select = 0;
		Table_UpdateWindow(sControl);
	}
}

void FillPriceList(string _tabName, string attr1, string isBank)
{
	string sGoods, row;
	int StoreNum, iStoreQ;
	int i, n, index;
	ref nulChr, chref, refStorage;
	aref aItems;

	n = 1;
	DeleteAttribute(&GameInterface, _tabName);
	if (sti(isBank))
	{
		GameInterface.(_tabName).select = 0;
		GameInterface.(_tabName).hr.td1.str = XI_ConvertString("ItemsColonTitle");
		GameInterface.(_tabName).hr.td2.str = XI_ConvertString("In the deposit");
		GameInterface.(_tabName).hr.td3.str = XI_ConvertString("Cost");
		GameInterface.(_tabName).hr.td4.str = XI_ConvertString("Common") + "\n" + LowerFirst(XI_ConvertString("weight"));

		if (attr1 != "")
		{
			if (attr1 == "Secret_Fort") StoreNum = SHIP_STORE;
			else StoreNum = GetStorage(attr1);
			if (StoreNum >= 0)
			{
				refStorage = &stores[StoreNum];

				makearef(aItems, refStorage.items);
				int itemsNum = GetAttributesNum(aItems);

				for (i = 0; i < itemsNum; i++)
				{
					row = "tr" + n;
					sGoods = GetAttributeName(GetAttributeN(aItems, i));
					index = FindItem(sGoods);
					iStoreQ = sti(GetAttributeValue(GetAttributeN(aItems, i)));
					if (Items[index].name == "itmname_gold") sGoods = iStoreQ;
					else sGoods = sti(Items[index].price) * iStoreQ;

					GameInterface.(_tabName).(row).UserData.ID = Items[index].name;
					GameInterface.(_tabName).(row).UserData.IDX = index;
					GameInterface.(_tabName).(row).UserData.IsBank = isBank;
					GameInterface.(_tabName).(row).td1.icon.group = Items[index].picTexture;
					GameInterface.(_tabName).(row).td1.icon.image = "itm" + Items[index].picIndex;
					GameInterface.(_tabName).(row).td1.icon.offset = "1, 0";
					GameInterface.(_tabName).(row).td1.icon.width = 21;
					GameInterface.(_tabName).(row).td1.icon.height = 21;
					GameInterface.(_tabName).(row).td1.textoffset = "10,0";
					GameInterface.(_tabName).(row).td1.str = GetConvertStr(Items[index].name, "ItemsDescribe.txt");
					GameInterface.(_tabName).(row).td1.scale = 0.8;
					GameInterface.(_tabName).(row).td2.str = iStoreQ;
					GameInterface.(_tabName).(row).td2.scale = 0.9;
					GameInterface.(_tabName).(row).td3.str = sGoods;
					GameInterface.(_tabName).(row).td3.scale = 0.9;
					GameInterface.(_tabName).(row).td4.str = FloatToString(stf(Items[index].Weight) * iStoreQ, 1);
					GameInterface.(_tabName).(row).td4.scale = 0.9;
					n++;
				}
			}
		}
	}
	else
	{
		GameInterface.(_tabName).select = 0;
		GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Good name");
		GameInterface.(_tabName).hr.td2.str = XI_ConvertString("In the storage");
		GameInterface.(_tabName).hr.td3.str = XI_ConvertString("Pack");
		GameInterface.(_tabName).hr.td4.str = XI_ConvertString("weight");

		if (attr1 != "")
		{
			if (attr1 == "Secret_Fort") StoreNum = SHIP_STORE;
			else StoreNum = GetStorage(attr1);
			if (StoreNum >= 0)
			{
				refStorage = &stores[StoreNum];
				for (i = 0; i < GOODS_QUANTITY; i++)
				{
					row = "tr" + n;
					sGoods = "Gidx" + i;
					iStoreQ = GetStorageGoodsQuantity(refStorage, i);
					if (iStoreQ == 0) continue;
					GameInterface.(_tabName).(row).UserData.ID = Goods[i].name;
					GameInterface.(_tabName).(row).UserData.IDX = i;
					GameInterface.(_tabName).(row).td1.icon.group = "GOODS";
					GameInterface.(_tabName).(row).td1.icon.image = Goods[i].name;
					GameInterface.(_tabName).(row).td1.icon.offset = "1, 0";
					GameInterface.(_tabName).(row).td1.icon.width = 21;
					GameInterface.(_tabName).(row).td1.icon.height = 21;
					GameInterface.(_tabName).(row).td1.textoffset = "10,0";
					GameInterface.(_tabName).(row).td1.str = XI_ConvertString(Goods[i].name);
					GameInterface.(_tabName).(row).td1.scale = 0.85;
					GameInterface.(_tabName).(row).td2.str = iStoreQ;
					GameInterface.(_tabName).(row).td3.str = Goods[i].Units;
					GameInterface.(_tabName).(row).td4.str = GetGoodWeightByType(i, iStoreQ);
					n++;
				}
			}
		}
	}
	Table_UpdateWindow(_tabName);
}

// tradebook --->

//  таблица: город, местоположение, актуальность
void TradebookFillPriceListTown(string _tabName)
{
	string cityId, attr2, firstId;
	int i, cn, n;
	ref nulChr;
	string row;
	aref rootItems;
	aref curItem;
	ref rCity;

	// шапка -->
	GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Nation");
	GameInterface.(_tabName).hr.td2.str = XI_ConvertString("ColonyLevel4");
	GameInterface.(_tabName).hr.td3.str = XI_ConvertString("ColonyName");
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("Relevance");
	// <--
	nulChr = &NullCharacter;
	makearef(rootItems, nulChr.PriceList);  // тут живут ИД города и служ. инфа.
	n = 1;
	firstId = "";
	for (i = 0; i < GetAttributesNum(rootItems); i++)
	{
		row = "tr" + n;
		curItem = GetAttributeN(rootItems, i);
		cityId = GetAttributeName(curItem);
		// row = "tr" + n;
		cn = FindColony(cityId);
		if (cn != -1)
		{
			rCity = GetColonyByIndex(cn);
			if (n == 1) firstId = cityId;
			GameInterface.(_tabName).(row).UserData.CityID = cityId;
			GameInterface.(_tabName).(row).UserData.CityIDX = cn;
			GameInterface.(_tabName).(row).td1.icon.group = "NATIONS";
			GameInterface.(_tabName).(row).td1.icon.image = Nations[sti(rCity.nation)].Name;
			GameInterface.(_tabName).(row).td1.icon.width = 21;
			GameInterface.(_tabName).(row).td1.icon.height = 21;
			GameInterface.(_tabName).(row).td1.icon.offset = "12, 0";
			GameInterface.(_tabName).(row).td2.str = GetConvertStr(cityId + " Town", "LocLables.txt");
			GameInterface.(_tabName).(row).td3.str = GetConvertStr(rCity.islandLable, "LocLables.txt");
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
	Table_UpdateWindow(_tabName);
	TradebookFillPriceList("TRADEBOOK_TABLE_GOODS", firstId);
}

//  таблица: картинка, название, картинка экспорта, продажа, покупка, колво, пачка, вес пачки
void TradebookFillPriceList(string _tabName, string attr1)
{
	string sGoods;
	int i, n;
	ref nulChr;
	string row;
	nulChr = &NullCharacter;

	bool isTableGoods = false;
	int selectRowIdx = 1;
	int topIndex = 0;
	if (_tabName == "TRADEBOOK_TABLE_GOODS")
	{
		isTableGoods = true;

		selectRowIdx = sti(GameInterface.(_tabName).select);
		if (CheckAttribute(&GameInterface, _tabName + ".top"))
		{
			topIndex = sti(GameInterface.(_tabName).top);
		}
	}

	DeleteAttribute(&GameInterface, _tabName); //Чтобы убрать товары, которых нет в этой колонии
	// шапка -->
	GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = XI_ConvertString("Good name");
	GameInterface.(_tabName).hr.td1.line_space_modifier = 0.8;
	GameInterface.(_tabName).hr.td2.str = XI_ConvertString("Name");
	GameInterface.(_tabName).hr.td2.line_space_modifier = 0.8;
	GameInterface.(_tabName).hr.td3.str = XI_ConvertString("Price sell");
	GameInterface.(_tabName).hr.td3.line_space_modifier = 0.8;
	GameInterface.(_tabName).hr.td4.str = XI_ConvertString("Price buy");
	GameInterface.(_tabName).hr.td4.line_space_modifier = 0.8;
	GameInterface.(_tabName).hr.td5.str = XI_ConvertString("In the store");
	GameInterface.(_tabName).hr.td5.line_space_modifier = 0.8;
	GameInterface.(_tabName).hr.td6.str = XI_ConvertString("Pack");
	GameInterface.(_tabName).hr.td6.line_space_modifier = 0.8;
	GameInterface.(_tabName).hr.td7.str = XI_ConvertString("PackWeight");
	GameInterface.(_tabName).hr.td7.line_space_modifier = 0.8;
	if (attr1 != "")
	{
		// <--
		n = 1;
		for (i = 0; i < GOODS_QUANTITY; i++)
		{
			row = "tr" + n;
			sGoods = "Gidx" + i;
			if (i == 36) break; //пушки пропускаем
//			if (sti(nulChr.PriceList.(attr1).(sGoods).TradeType) == TRADE_TYPE_CANNONS && !bBettaTestMode) continue; // не пушки

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
			GameInterface.(_tabName).(row).td1.icon.offset = "5, 0";
			GameInterface.(_tabName).(row).td1.icon.width = 21;
			GameInterface.(_tabName).(row).td1.icon.height = 21;
			GameInterface.(_tabName).(row).td1.textoffset = "40,0";
			GameInterface.(_tabName).(row).td1.str = XI_ConvertString(Goods[i].name);

			GameInterface.(_tabName).(row).td2.icon.group = "TRADE_TYPE";
			GameInterface.(_tabName).(row).td2.icon.image = "ico_" + nulChr.PriceList.(attr1).(sGoods).TradeType;
			GameInterface.(_tabName).(row).td2.icon.offset = "4,2";
			GameInterface.(_tabName).(row).td2.icon.width = 11;
			GameInterface.(_tabName).(row).td2.icon.height = 16;

			GameInterface.(_tabName).(row).td6.str = Goods[i].Units;
			GameInterface.(_tabName).(row).td7.str = Goods[i].Weight;
			n++;
		}
	}
	if (isTableGoods)
	{
		SetScrollForSelectedTableRow("TRADEBOOK_TABLE_GOODS", selectRowIdx, 17, topIndex);
	}
	else
	{
		Table_UpdateWindow(_tabName);
	}
}
// <---
void SetFontType()
{
	if (CheckAttribute(&InterfaceStates, "FontType"))
	{
		switch (sti(InterfaceStates.FontType))
		{
			case 0:
				SetTabsFontType(1);
				SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "QUEST_TITLE", 0, "interface_quest_titleh");
				SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "QUEST_TEXT", 2, "interface_quest_texth");
			break;

			case 1:
				SetTabsFontType(2);
				SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "QUEST_TITLE", 0, "interface_quest_titlen");
				SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "QUEST_TEXT", 2, "interface_quest_textn");
			break;

			case 2:
				SetTabsFontType(2);
				if (currentTab == 2)
				{
					SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "QUEST_TITLE", 0, "interface_quest_titlen");
					SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "QUEST_TEXT", 2, "interface_quest_texth");
				}
				else
				{
					SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "QUEST_TITLE", 0, "interface_quest_titlen");
					SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "QUEST_TEXT", 2, "interface_quest_textn");
				}
			break;
		}
	}
}

void SetTabsFontType(int fontType)
{
	SetNodeUsing("TABSTR_QUEST", false);
	SetNodeUsing("TABSTR_QUESTN", false);
	SetNodeUsing("TABSTR_QUESTARJ", false);
	SetNodeUsing("TABSTR_QUESTARJN", false);
	SetNodeUsing("TABSTR_INFO", false);
	SetNodeUsing("TABSTR_INFON", false);
	SetNodeUsing("TABSTR_CASHBOOK", false);
	SetNodeUsing("TABSTR_CASHBOOKN", false);
	SetNodeUsing("TABSTR_SHIP_PLACE", false);
	SetNodeUsing("TABSTR_SHIP_PLACEN", false);
	SetNodeUsing("TABSTR_STOREBOOK", false);
	SetNodeUsing("TABSTR_STOREBOOKN", false);
	SetNodeUsing("TABSTR_TRADEBOOK", false);
	SetNodeUsing("TABSTR_TRADEBOOKN", false);
	SetNodeUsing("TABSTR_STATISTIC", false);
	SetNodeUsing("TABSTR_STATISTICN", false);
	switch (fontType)
	{
		case 1:
			SetNodeUsing("TABSTR_QUEST", true);
			SetNodeUsing("TABSTR_QUESTARJ", true);
			SetNodeUsing("TABSTR_INFO", true);
			SetNodeUsing("TABSTR_CASHBOOK", true);
			SetNodeUsing("TABSTR_SHIP_PLACE", true);
			SetNodeUsing("TABSTR_STOREBOOK", true);
			SetNodeUsing("TABSTR_TRADEBOOK", true);
			SetNodeUsing("TABSTR_STATISTIC", true);
		break;

		case 2:
			SetNodeUsing("TABSTR_QUESTN", true);
			SetNodeUsing("TABSTR_QUESTARJN", true);
			SetNodeUsing("TABSTR_INFON", true);
			SetNodeUsing("TABSTR_CASHBOOKN", true);
			SetNodeUsing("TABSTR_SHIP_PLACEN", true);
			SetNodeUsing("TABSTR_STOREBOOKN", true);
			SetNodeUsing("TABSTR_TRADEBOOKN", true);
			SetNodeUsing("TABSTR_STATISTICN", true);
		break;
	}
}

string GetShipDescr(ref refRealShip)
{
	ref refShip;
	makeref(refShip, ShipsTypes[sti(refRealShip.basetype)]);

	if (CheckAttribute(refShip, "modname"))
	{
		return GetConvertStr(refRealShip.BaseName, "mods\" + refShip.modname + "\ShipsDescribe.txt");
	}
	return GetConvertStr(refRealShip.BaseName, "ShipsDescribe.txt");
}

void OnHeaderClick()
{
	string sControl = GetEventData();
	int iColumn = GetEventData();

	if (sControl == "TABLE_CITY") SortTableStoreCity(iColumn, false, sControl);
	if (sControl == "TABLE_GOODS") SortStoreTable(iColumn, false, sControl);
	if (sControl == "TRADEBOOK_TABLE_CITY") SortTableCity(iColumn, false, sControl);
	if (sControl == "TRADEBOOK_TABLE_GOODS") SortGoodsTable(iColumn, false, sControl);
	if (sControl == "TABLE_CREDIT") SortBankTable(iColumn, false, sControl);
	if (sControl == "TABLE_DEBIT") SortBankTable(iColumn, false, sControl);
	if (sControl == "TABLE_SHIP_PLACE") SortShipPlaceTable(iColumn, false, sControl);
}

void SortTableStoreCity(int column, bool preserveState, string tableName)
{
	string datatype = "string";
	switch (column)
	{
		case 1: datatype = "sIcon"; break;
		case 4: datatype = "integer"; break;
		case 5: datatype = "integer"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 0);
}

void SortStoreTable(int column, bool preserveState, string tableName)
{
	string datatype = "integer";
	switch (column)
	{
		case 1: datatype = "string"; break;
		case 2: datatype = "float"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 0);
}

void SortTableCity(int column, bool preserveState, string tableName)
{
	string datatype = "string";
	switch (column)
	{
		case 1: datatype = "sIcon"; break;
		case 4: datatype = "date"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 0);
}

void SortGoodsTable(int column, bool preserveState, string tableName)
{
	string datatype = "integer";
	switch (column)
	{
		case 1: datatype = "string"; break;
		case 2: datatype = "intIcon"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 4);
}

void SortBankTable(int column, bool preserveState, string tableName)
{
	string datatype = "string";
	switch (column)
	{
		case 4: datatype = "integer"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 0);
}

void SortShipPlaceTable(int column, bool preserveState, string tableName)
{
	string datatype = "integer";
	switch (column)
	{
		case 2: datatype = "index"; break;
		case 4: datatype = "string"; break;
		case 5: datatype = "string"; break;
		case 6: datatype = "date"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 0);
}

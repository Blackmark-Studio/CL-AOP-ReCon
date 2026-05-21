// Ugeen 26.08.10 - интерфейс мультиобъектов (на базе интерфейса обыска)
// KZ > ref 30.11.24

#event_handler("Control Activation", "ProcessInterfaceControls");// гуляем по меню кнопками Q и E

int nCurScrollNum = 0;
int iCurGoodsIdx, iResult = 0;
ref rGlobItem;
aref alchemy;
string sCurItem;
int curShowTutorial = true;
object obGKIC;

void InitInterface(string iniName)
{
	InterfaceStack.SelectMenu_node = "LaunchAlchemy"; // запоминаем, что звать по F2

	SetAlchemyRecipeKnown("grapeshot");

	DeleteAttribute(&NullCharacter, "alchemy.items");
	makearef(alchemy, NullCharacter.alchemy);

	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("CraftItems");
	GameInterface.TABLE_LIST.hr.td1.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("CraftPurpose");
	GameInterface.TABLE_LIST.hr.td2.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("ItemsColonTitle");
	GameInterface.TABLE_LIST.hr.td3.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("CraftNeed");
	GameInterface.TABLE_LIST.hr.td4.scale = 0.9;
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("CraftItems");
	GameInterface.TABLE_LIST.hr.td5.scale = 0.9;

	CheckAlchemyRecipe();
	FillItemsScroll();

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);

	CreateString(true, "ItemName", "", FONT_NORMAL, COLOR_MONEY, 405, 127, SCRIPT_ALIGN_CENTER, 0.85);

	sCurItem = SetItemsName(0);
	GrabCabinItems(sCurItem);
	rGlobItem = ItemsFromId(sCurItem);
	AddToTable(rGlobItem);

	iCurGoodsIdx = sti(GameInterface.TABLE_LIST.tr1.index);

	SetNodeUsing("GETALL_BUTTON", true);
	SetSelectable("GETALL_BUTTON", false);

 	SetEventHandlers();
	XI_RegistryExitKey("IExit_K");

	// доп инфа в шапку --->
	SetFormatedText("WEIGHT", FloatToString(GetItemsWeight(pchar), 1) + " / " + GetMaxItemsWeight(pchar));
	SetFormatedText("MONEY", FindMoneyString(sti(pchar.money)));
	SetFormatedText("CURRENT_DATE_CAPTION", GetDateString() + " " + GetTimeString());
	// <--

	SetFormatedText("QTY_SELECTED", "1");

	if (CheckAttribute(&TEV, "TutorialInfo.Alchemy"))
	{
		DeleteAttribute(&TEV, "TutorialInfo.Alchemy");
		ShowAlchemyTutorial();
	}

//	SetNewPicture("BUG_L_PICTURE", "interfaces\PORTRAITS\64\face_" + pchar.faceId + ".tga");

	if (pchar.location == Get_My_Cabin())
		SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "BUG_R_PICTURE", 2, 0, "INTERFACES\BoxImage.tga");

	SetAlertMarks(pchar);
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_ALCHEMY_EXIT);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_ALCHEMY_EXIT);
}

void IDoExit(int exitCode)
{
	aref curItem, arItem, arChests, rootItems, arBoxes;
	int j, k, iItemQty, iRoot, iRes;
	string sBox, sItem;

	makearef(rootItems, alchemy.Items);
	iRoot = GetAttributesNum(rootItems);

	for (j = 0; j < iRoot; j++)
	{
		curItem = GetAttributeN(rootItems, j);

		if (Items_FindItem(GetAttributeName(curItem), &arItem) >= 0)
		{
			iItemQty = sti(GetAttributeValue(curItem));
			AddItems(pchar, arItem.id, iItemQty);
		}
	}

	makearef(rootItems, pchar.items);
	iRoot = GetAttributesNum(rootItems);

	for (j = 0; j < iRoot; j++)
	{
		curItem = GetAttributeN(rootItems, j);

		if (Items_FindItem(GetAttributeName(curItem), &arItem) >= 0 && CheckAttribute(&arItem, "CabinItems.Qty"))
		{
			makearef(arBoxes, arItem.CabinItems.Qty);
			iItemQty = sti(GetAttributeValue(curItem));

			for (k = 0; k < GetAttributesNum(arBoxes); k++)
			{
				if (iItemQty <= 0) break;

				sBox = GetAttributeName(GetAttributeN(arBoxes, k));
				sItem = arItem.id;
				iRes = sti(arItem.CabinItems.Qty.(sBox));

				if (iItemQty - iRes < 0)
					iRes = iItemQty;

				iItemQty -= iRes;

				makearef(arChests, locations[FindLocation(Get_My_Cabin())].(sBox));
				arChests.Items.(sItem) = (sti(GetAttrValue(arChests, "Items." + sItem)) + iRes);
				pchar.Items.(sItem) = (sti(GetAttrValue(pchar, "Items." + sItem)) - iRes);
			}

			DeleteAttribute(&arItem, "CabinItems");
		}
	}

	DelEventHandlers();
	DeleteAttribute(&NullCharacter, "alchemy.items");

	interfaceResultCommand = exitCode;

	if (CheckAttribute(&InterfaceStates, "ReloadMenuExit"))
	{
		DeleteAttribute(&InterfaceStates, "ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
		EndCancelInterface(true);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	if (comName == "activate" || comName == "click")
	{
		switch (nodName)
		{
			case "INCREASE_BUTTON": CALC_BUTTON(1); break;
			case "DECREASE_BUTTON": CALC_BUTTON(0); break;
			case "INCREASE_ALL_BUTTON": CALC_ALL_BUTTON(1); break;
			case "DECREASE_ALL_BUTTON": CALC_ALL_BUTTON(0); break;
			case "GETALL_BUTTON": onGetAllBtnClick(); break;
			case "I_CHARACTER_2": nodName = "I_CHARACTER"; break;
			case "I_SHIP_2": nodName = "I_SHIP"; break;
			case "I_QUESTBOOK_2": nodName = "I_QUESTBOOK"; break;
			case "I_ALCHEMY_2": nodName = "I_ALCHEMY"; break;
			case "I_NATIONS_2": nodName = "I_NATIONS"; break;
			case "I_ITEMS_2": nodName = "I_ITEMS"; break;
		}

		if (StrStartsWith(nodName, "I_"))
		{
			InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame", 1, "sl", nodName, 2);
			return;
		}
	}
}

void SetEventHandlers()
{
	SetEventHandler("InterfaceBreak", "ProcessBreakExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("ievnt_command", "ProcCommand", 0);
	SetEventHandler("evntDoPostExit", "DoPostExit", 0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("MouseRClickUP", "EndTooltip", 0);
	SetEventHandler("ShowHelpHint", "ShowHelpHint", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);
//	SetEventHandler("frame", "ProcessFrame", 1);
	SetEventHandler("ChangeSelectScrollImage", "ChangeSelectScrollImage", 0);
}

void DelEventHandlers()
{
	DelEventHandler("InterfaceBreak", "ProcessBreakExit");
	DelEventHandler("exitCancel", "ProcessCancelExit");
	DelEventHandler("ievnt_command", "ProcCommand");
	DelEventHandler("evntDoPostExit", "DoPostExit");
	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("MouseRClickUP", "EndTooltip");
	DelEventHandler("ShowHelpHint", "ShowHelpHint");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
//	DelEventHandler("frame", "ProcessFrame");
	DelEventHandler("ChangeSelectScrollImage", "ChangeSelectScrollImage");
	DelEventHandler("OnHeaderClick", "OnHeaderClick");
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void ShowHelpHint()
{
	ref rItm = ItemsFromID(sCurItem);
	int lngFileID = LanguageOpenFile("ItemsDescribe.txt");
	string sHeader, sText1, sText2, sText3, sPic, sGroup, sGroupPic, sCurrentNode = GetCurrentNode();

	if (sCurrentNode == "TABLE_LIST")
		rItm = ItemsFromID(Items[iCurGoodsIdx].id);

	sPic = "none";
	sGroup = rItm.picTexture;
	sGroupPic = "itm" + rItm.picIndex;
	sHeader = LanguageConvertString(lngFileID, rItm.name);
	sText1 = GetItemDescribe(sti(rItm.index));

	CreateTooltip("#" + sHeader, sText1, argb(255, 255, 255, 255), sText2, argb(255, 192, 192, 192), sText3, argb(255, 255, 255, 255), "", argb(255, 255, 255, 255), sPic, sGroup, sGroupPic, 64, 64);
	LanguageCloseFile(lngFileID);
}

void FillItemsScroll()
{
	int i, n, m = 0;
	string sAttr, sItemId;
	ref itm;
	aref arImgGrp, arTable;

	DeleteAttribute(&GameInterface, "ITEMS_SCROLL");
	makearef(arTable, GameInterface.ITEMS_SCROLL);

	nCurScrollNum = 0;
	arTable.current = 0;

	arTable.ImagesGroup.t0 = "EMPTY_ITEMS";

	makearef(arImgGrp, arTable.ImagesGroup);
	FillImagesGroupForItems(arImgGrp);

	arTable.BadTex1 = 0;
	arTable.BadPic1 = "pic9";
	arTable.BadTex2 = 0;
	arTable.BadPic2 = "pic16";

	for (n = 0; n < ITEMS_QUANTITY; n++)
	{
		makeref(itm, Items[n]);

		if (CheckAttribute(itm, "id") && CheckAttribute(itm, "craft") && itm.craft == "1" && or(bBettaTestMode, isMultiObjectKnown(itm.id)))
		{
			sAttr = "pic" + (m + 1);
			arTable.(sAttr).itemId = itm.id;
			arTable.(sAttr).img1 = GetItemPictureName(itm.id);
			arTable.(sAttr).tex1 = GetItemPictureTexture("ITEMS_SCROLL.ImagesGroup", itm.id);

			sItemId = itm.id;
			alchemy.items.(sItemId) = 0;

			m++;
		}
	}

	Restrictor(&m, 1, "");

	if (m < 5)
		arTable.NotUsed = 5;

	arTable.ListSize = m;
}

string SetItemsName(bool bSimple)
{
	string sAttr = "pic" + (nCurScrollNum + 1);
	string itemId = GameInterface.ITEMS_SCROLL.(sAttr).itemId;
	ref rItem = ItemsFromID(itemId);
	string sItemName = GetConvertStr(rItem.name, "ItemsDescribe.txt");
	GameInterface.strings.ItemName = sItemName + " (" + (GetCharacterItem(pchar, rItem.id) + GetCharacterItem(alchemy, rItem.id)) + ")";

	if (bSimple)
		return itemId;

	SetSelectable("GETALL_BUTTON", CheckAlchemy(itemId, 0) > 0);
	QTY_CREATE_UPDATE(itemId);

	return itemId;
}

void ChangeSelectScrollImage()
{
	string sNod = GetEventData();
	int nIdx = GetEventData();

	if (sNod == "ITEMS_SCROLL")
	{
		nCurScrollNum = nIdx;
		string sAttr = "pic" + (nCurScrollNum + 1);
		string sItemId = GameInterface.ITEMS_SCROLL.(sAttr).itemId;

		rGlobItem = ItemsFromId(sItemId);
		AddToTable(rGlobItem);
		sCurItem = sItemId;

		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;
		SetItemsName(0);
		SetFormatedText("QTY_SELECTED", "" + (nCurScrollNum + 1));
		TEXT_CRAFT_UPDATE();
	}
}

void AddToTable(ref rItem)
{
	string sItmId, sAttr, sList, sItmUse = XI_ConvertString("Component");
	string sTmp = "*";
	int n, i, q, iNum, iLeftQty, iRightQty, iQty, iChests, iconSize = 46;
	int iAlchemyItems, iPcharItems;
	ref itm;
	aref arTable;

	int iGreen	= argb(255, 196, 255, 196);
	int iRed	= argb(255, 255, 196, 196);
	int iWhite	= argb(255, 255, 255, 255);
	int iGrey	= argb(255, 160, 160, 160);

	n = 1;
	Table_Clear("TABLE_LIST", false, true, false);

	sItmId = rItem.craft.components;
	iNum = KZ|Symbol(sItmId, ",");
	sAttr = sItmId;

	if (sAttr != "")
	{
		for (i = 0; i <= iNum; i++)
		{
			if (iNum > 0)
				sAttr = GetSubStr(sItmId, ",", i);

			iQty = 1;

			if (HasStr(sAttr, ":"))
			{
				sTmp = FindStringAfterChar(sAttr, ":");

				if (HasStrEx(sTmp, "tool,cat", "|"))
				{
					if (HasStr(sTmp, "tool"))
						sItmUse = XI_ConvertString("Tool");
					else
					{
						iQty = 1;
						sItmUse = XI_ConvertString("Catalyst");
					}
				}
				else
				{
					iQty = sti(sTmp);
					Restrictor(&iQty, 1, "");
				}

				sAttr = FindStringBeforeChar(sAttr, ":");
			}

			if (CheckCharacterPerk(pchar, "Alchemy") && StrEndsWith(sAttr, "_kit"))
				continue;

			GrabCabinItems(sAttr);
			itm = ItemsFromId(sAttr);

			iPcharItems = GetCharacterItem(pchar, itm.id);
			iAlchemyItems = GetCharacterItem(alchemy, itm.id);

			// > инструменты при наличии сразу перекидываем вправо
			if (or(CheckAttribute(itm, "craft.tool"), HasStr(sTmp, "tool")) && iPcharItems > 0 && iAlchemyItems < 1)
			{
				RemoveItems(pchar, itm.id, 1);
				AddItems(alchemy, itm.id, 1);
				iPcharItems--;
				iAlchemyItems++;
			}

			sList = "tr" + n;

			iLeftQty = GetCharacterFreeItem(pchar, sAttr);

			if (CheckAttribute(alchemy, "items." + (sAttr)))
				iRightQty = sti(alchemy.items.(sAttr));
			else
				iRightQty = 0;

			makearef(arTable, GameInterface.TABLE_LIST.(sList));

			arTable.td1.str = iLeftQty;
			arTable.td1.scale = 0.9;

			arTable.td1.color = iGreen;
			//arTable.td2.color = iGreen;

			if (iPcharItems < iQty && iAlchemyItems < iQty)
			{
				arTable.td1.color = iRed;
				//arTable.td2.color = iRed;
			}

			arTable.td3.color = iGreen;
			arTable.td5.color = iRed;

			if (iLeftQty < iQty && iRightQty < iQty)
				arTable.td3.color = iRed;

			if (iAlchemyItems >= iQty)
				arTable.td5.color = iGreen;

			arTable.td2.str = sItmUse;
			arTable.td2.scale = 0.9;
			arTable.td3.icon.group = itm.picTexture;
			arTable.td3.icon.image = "itm" + itm.picIndex;
			arTable.td3.icon.offset = "0, 1";
			arTable.td3.icon.width = iconSize;
			arTable.td3.icon.height = iconSize;
			arTable.td3.textoffset = "45, 0";
			arTable.td3.str = GetConvertStr(itm.name, "ItemsDescribe.txt");
			//arTable.td3.color = COLOR_MONEY;
			arTable.index = itm.index;
			arTable.td3.scale = 0.9;
			arTable.td4.str = iQty;
			arTable.td4.scale = 0.9;
			arTable.td5.str = iRightQty;
			arTable.td5.scale = 0.9;
			n++;
		}
	}

	QTY_CREATE_UPDATE(sCurItem);
	Table_UpdateWindow("TABLE_LIST");
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void GrabCabinItems(string _sAttr)
{
	if (pchar.location != Get_My_Cabin() || GetCharacterItemCabin(pchar, _sAttr, 0, 1) <= 0) return;

	aref arChests;
	ref rItm = ItemsFromId(_sAttr);
	string sBox;
	int iBox, iChests = CheckCabinBoxes(locations[FindLocation(Get_My_Cabin())]);

	for (iBox = 1; iBox <= iChests; iBox++)
	{
		sBox = "box" + iBox;
		makearef(arChests, locations[FindLocation(Get_My_Cabin())].(sBox));

		if (CheckAttribute(arChests, "Items." + _sAttr))
		{
			rItm.CabinItems.Qty.(sBox) = "" + arChests.Items.(_sAttr);
			pchar.Items.(_sAttr) = sti(GetAttrValue(pchar, "Items." + _sAttr)) + sti(arChests.Items.(_sAttr));
			arChests.Items.(_sAttr) = "0";
		}
	}
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_LIST", 0);
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
	int iCol = GetEventData();
	int iSelLine = iSelected;

	if (CheckAttribute(&GameInterface, "TABLE_LIST.top"))
		iSelLine = iSelected - sti(GameInterface.TABLE_LIST.top);

	string sList = "tr" + iSelected;
	iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(sList).index);
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	string sRow = "tr" + (iRow + 1);
	Table_UpdateWindow(sControl);
}

void EndTooltip()
{
	CloseTooltip();
	SetCurrentNode("TABLE_LIST");
}

int CheckAlchemy(string sItemID, bool bCheck)
{
	if (FindItem(sItemID) < 0)
		return 0;

	ref rItem = ItemsFromID(sItemID);
	int i, iNum, iReq, itmQty, Qty = 0;
	int iAlchemyItems = 0;
	int iPCharItems = 0;
	string sAttr, sItmId, sTmp;
	bool bOk = false;
	bool bTool = false;

	sItmId = rItem.craft.components;
	iNum = KZ|Symbol(sItmId, ",");
	sAttr = sItmId;

	for (i = 0; i <= iNum; i++)
	{
		if (iNum > 0)
			sAttr = GetSubStr(sItmId, ",", i);

		iReq = 1;

		if (HasStr(sAttr, ":"))
		{
			sTmp = FindStringAfterChar(sAttr, ":");
			sAttr = FindStringBeforeChar(sAttr, ":");

			if (HasStrEx(sTmp, "tool,cat", "|"))
			{
				if (HasStr(sTmp, "tool"))
					bTool = true;
			}
			else
			{
				iReq = sti(sTmp);
				Restrictor(&iReq, 1, "");
			}
		}

		iAlchemyItems = GetCharacterFreeItem(alchemy, sAttr);
		iPCharItems = GetCharacterFreeItem(pchar, sAttr);

		if (!bTool)
		{
			if (bCheck)
				itmQty = makeint((iAlchemyItems + iPCharItems) / iReq);
			else
				itmQty = makeint(iAlchemyItems / iReq);

			if (itmQty > 0)
			{
				if (itmQty < Qty && Qty != 0)
					Qty = itmQty;
				else
				{
					if (Qty == 0)
						Qty = itmQty;
				}

				bOk = true;
			}
			else
			{
				Qty = 0;
				bOk = false;
				break;
			}
		}
		else
		{
			if (iAlchemyItems >= iReq || and(iAlchemyItems + iPCharItems >= iReq, bCheck))
				bOk = true;
			else
			{
				bOk = false;
				break;
			}
		}
	}

	if (!bOk)
		return 0;

	return Qty;
}

void onGetAllBtnClick()
{
	int i, iNum, iReq;
	string sAttr, sItmId, sTmp = "*";

	ref rItem = ItemsFromId(sCurItem);
	int Qty = CheckAlchemy(sCurItem, 0);

	sItmId = rItem.craft.components;
	iNum = KZ|Symbol(sItmId, ",");
	sAttr = sItmId;

	for (i = 0; i <= iNum; i++)
	{
		if (iNum > 0)
			sAttr = GetSubStr(sItmId, ",", i);

		iReq = 1;

		if (HasStr(sAttr, ":"))
		{
			sTmp = FindStringAfterChar(sAttr, ":");
			sAttr = FindStringBeforeChar(sAttr, ":");

			if (HasStrEx(sTmp, "tool,cat", "|"))
			{
				if (!HasStr(sTmp, "tool"))
					Qty = 1;
			}
			else
			{
				iReq = sti(sTmp);
				Restrictor(&iReq, 1, "");
			}
		}

		if (!HasStr(sTmp, "tool"))
			RemoveItems(alchemy, sAttr, Qty * iReq);
	}

	AddItems(pchar, sCurItem, Qty * sti(rItem.craft.qty));
	WaitDate("", 0, 0, 0, 0, 5 + (2 * Qty));

	AddToTable(ItemsFromId(sCurItem));
	SetItemsName(1);

	SetSelectable("GETALL_BUTTON", CheckAlchemy(sCurItem, 0) > 0);

	GameInterface.TABLE_LIST.top = 0;
	GameInterface.TABLE_LIST.select = 1;

	sTmp = ColorText(GetConvertStr(rItem.name, "ItemsDescribe.txt"), "goldenrod"); // > красиво, но багует

	PlaySound("Important_item");
	SetFormatedText("RESULT_DONE", XI_ConvertString("CraftItDone") + " " + Qty * sti(rItem.craft.qty) + XI_ConvertString("pcs") + " " + XI_ConvertString("CraftItem") + " : \n\n" + sTmp);
	TEXT_CRAFT_UPDATE();
}

void onTableAllBtnClick(ref rCharA, ref rCharB)
{
	string item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(rCharA, item);

	if (iItemsQty > 0)
	{
		RemoveItems(rCharA, item, iItemsQty);
		AddItems(rCharB, item, iItemsQty);

		AddToTable(ItemsFromId(sCurItem));
		SetSelectable("GETALL_BUTTON", CheckAlchemy(sCurItem, 0) > 0);
	}
}

void CALC_BUTTON(bool bAdd)
{
	int i = CheckAlchemy(sCurItem, 1);

	if (bAdd)
	{
		if (iResult < i)
		{
			iResult += 1;
			CalcMe(pchar, alchemy);
		}
		else
			iResult = i;
	}
	else
	{
		if (iResult > 0)
		{
			iResult -= 1;
			CalcMe(alchemy, pchar);
		}
	}

	TEXT_CRAFT_UPDATE();
	Restrictor(&iResult, 0, i);
}

void CALC_ALL_BUTTON(bool bAdd)
{
	int i = CheckAlchemy(sCurItem, 1);

	if (bAdd)
	{
		if (iResult < i)
		{
			iResult = i;
			CalcMe(pchar, alchemy);
		}
	}
	else
	{
		if (iResult > 0)
		{
			iResult = 0;
			CalcMe(alchemy, pchar);
		}
	}

	TEXT_CRAFT_UPDATE();
	Restrictor(&iResult, 0, i);
}

void TEXT_CRAFT_UPDATE()
{
	if (iResult > 0 && CheckAttribute(rGlobItem, "craft.qty"))
		SetFormatedText("RESULT_CRAFT", XI_ConvertString("CraftIt") + " " + (iResult * sti(rGlobItem.craft.qty)) + XI_ConvertString("pcs") + " " + XI_ConvertString("CraftItem") + " : \n\n" + ColorText(GetConvertStr(rGlobItem.name, "ItemsDescribe.txt"), "goldenrod"));
	else
		SetFormatedText("RESULT_CRAFT", "");
}

void QTY_CREATE_UPDATE(string sItem)
{
	iResult = CheckAlchemy(sItem, 0);
	SetFormatedText("QTY_CREATE", "" + iResult + " / " + CheckAlchemy(sItem, 1));
	SetSelectable("GETALL_BUTTON", iResult > 0);
}

void CalcMe(ref rChar, ref rStore)
{
	int i, iNum, iReq, iPcharItems, iAlchemyItems;
	string sAttr, sItmId, sTmp = "*";

	ref rItem = ItemsFromId(sCurItem);

	sItmId = rItem.craft.components;
	iNum = KZ|Symbol(sItmId, ",");
	sAttr = sItmId;

	for (i = 0; i <= iNum; i++)
	{
		if (iNum > 0)
			sAttr = GetSubStr(sItmId, ",", i);

		iReq = 1;

		if (HasStr(sAttr, ":"))
		{
			sTmp = FindStringAfterChar(sAttr, ":");
			sAttr = FindStringBeforeChar(sAttr, ":");

			if (!HasStrEx(sTmp, "tool,cat", "|"))
			{
				iReq = sti(sTmp);
				Restrictor(&iReq, 1, "");
			}
		}

		iPcharItems = GetCharacterFreeItem(rChar, sAttr);
		iAlchemyItems = GetCharacterFreeItem(rStore, sAttr);

		if (!HasStrEx(sTmp, "tool,cat", "|") && iPcharItems >= 1)
		{
			if (and(iPcharItems > 0, iPcharItems < iReq) || and(iResult < 1, CheckAttribute(rStore, "id") && rStore.id == pchar.id))
				iReq = iPcharItems;
			if (CheckAttribute(rChar, "id") && rChar.id == pchar.id && iResult > 1)
				iReq = iResult * iReq - iAlchemyItems;

			AddItems(rStore, sAttr, iReq);
			RemoveItems(rChar, sAttr, iReq);
		}
	}

	AddToTable(ItemsFromId(sCurItem));
}

void OnHeaderClick()
{
	string sNode = GetEventData();
	int iCol = GetEventData();

	if (sNode == "TABLE_LIST") SortAlchemyTable(iCol, false, sNode);
}

void SortAlchemyTable(int column, bool preserveState, string tableName)
{
	string datatype = "integer";
	switch (column)
	{
		case 2: datatype = "string"; break;
		case 3: datatype = "string"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 0);
}

// гуляем по меню кнопками Q и E
void ProcessInterfaceControls()
{
	// в туторе не гуляем
	if (CheckAttribute(&TEV, "Alchemy.Tutor"))
	{
		return;
	}

	string controlName = GetEventData();

	if (controlName == "InterfaceGoLeft")
	{
		IDoExit(RC_INTERFACE_TO_LOGBOOK);
	}
	if (controlName == "InterfaceGoRight")
	{
		IDoExit(RC_INTERFACE_TO_ITEMS);
	}
	if (controlName == "IExit_F2")
	{
		IDoExit(RC_INTERFACE_TO_SHIP);
	}
	if (controlName == "IExit_F3")
	{
		IDoExit(RC_INTERFACE_TO_LOGBOOK);
	}
	if (controlName == "IExit_F4")
	{
		IDoExit(RC_INTERFACE_TO_ITEMS);
	}
	if (controlName == "IExit_F5")
	{
		IDoExit(INTERFACE_NATIONRELATION);
	}
	if (controlName == "IExit_F1")
	{
		IDoExit(INTERFACE_CHARACTER_ALL);
	}
}

void ShowAlchemyTutorial()
{
	bool bGlobalTutor = GetGlobalTutor();
	if (CheckAttribute(&InterfaceStates, "ShowTutorial") && sti(InterfaceStates.ShowTutorial) == 0 && !bGlobalTutor)
		return;

	string descr = "";
	string loadScr = "";
	string cimg1 = "";
	string cimg2 = "";
	string cimg3 = "";
	string cimg4 = "";
	string cimg5 = "";
	string cimg6 = "";

	Playsound("Notebook_2");
	TEV.Alchemy.Tutor = true;

	DelEventHandlers(); // сносим дефолтные эвенты - потом восстановим
	SetEventHandler("ievnt_command","Tutorial_ProcCommand",0);
	SetEventHandler("CheckButtonChange","Tutorial_procCheckBoxChange",0);
	SetEventHandler("ShowInfoWindow","Tutorial_ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","Tutorial_HideInfoWindow",0);

	string TutorialName = "Alchemy";
	SetFormatedText("TUTORIAL_TITLE", GetConvertStr(tutorialName + "_title", "TutorialDescribe.txt"));

	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowDisable("TUTORIAL_MAIN_WINDOW", false);
	XI_WindowShow("TUTORIAL_MAIN_WINDOW", true);

	// включаем видео
	SetNodeUsing("TUTORIAL_INFO_PICTURE", false);
	SetNodeUsing("TUTORIAL_INFO_VIDEO", true);
	loadScr = "tutorial\" + tutorialName + ".webm";
//	loadScr = "wIp.webm";
	SetNewVideo("TUTORIAL_INFO_VIDEO", loadScr);
	SetNewVideo("TUTORIAL_INFO_VIDEOZ", loadScr);
	SetFormatedText("TUTORIAL_ZOOM", "w");

	cimg1 = GetConvertStr(tutorialName + "_controlsimg1", "TutorialDescribe.txt");
	cimg2 = GetConvertStr(tutorialName + "_controlsimg2", "TutorialDescribe.txt");
	cimg3 = GetConvertStr(tutorialName + "_controlsimg3", "TutorialDescribe.txt");
	cimg4 = GetConvertStr(tutorialName + "_controlsimg4", "TutorialDescribe.txt");
	cimg5 = GetConvertStr(tutorialName + "_controlsimg5", "TutorialDescribe.txt");
	cimg6 = GetConvertStr(tutorialName + "_controlsimg6", "TutorialDescribe.txt");
	SetFormatedText("CONTROLS_TEXT", XI_ConvertString("Controls") + ":");
	if(cimg1 !="" || cimg2 !="" || cimg3 !="" || cimg4 !="" || cimg5 !="" || cimg6 !="")
	{
		string cimTotal = "";
		if(cimg1 !="") cimTotal += GetKeyCodeImg(cimg1);
		if(cimg2 !="") cimTotal += GetKeyCodeImg(cimg2);
		if(cimg3 !="") cimTotal += GetKeyCodeImg(cimg3);
		if(cimg4 !="") cimTotal += GetKeyCodeImg(cimg4);
		if(cimg5 !="") cimTotal += GetKeyCodeImg(cimg5);
		if(cimg6 !="") cimTotal += GetKeyCodeImg(cimg6);
		SetFormatedText("TUTORIAL_CONTROLS_IMG", cimTotal);

		SetNodeUsing("TUTORIAL_B_OK", false);
		SetNodeUsing("TUTORIAL_B_OK2", true);
		SetNodeUsing("TUTORIAL_CONTROLS_TEXT", true);
		SetNodeUsing("TUTORIAL_CONTROLS_IMG", true);
	}
	else
	{
		SetFormatedText("TUTORIAL_CONTROLS_TEXT", "");
		SetNodeUsing("TUTORIAL_B_OK", true);
		SetNodeUsing("TUTORIAL_B_OK2", false);
		SetNodeUsing("TUTORIAL_CONTROLS_TEXT", false);
		SetNodeUsing("TUTORIAL_CONTROLS_IMG", false);
	}

   	SetKeyAttrs();
	descr = GetConvertStr(tutorialName + "_descr", "TutorialDescribe.txt");
    descr = GetAssembledString(descr, &obGKIC);
	SetFormatedText("TUTORIAL_INFO_TEXT", descr);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"TUTORIAL_INFO_TEXT",5);

	int nStrings = GetNumberOfStringsInFormatedText("TUTORIAL_INFO_TEXT", descr); // считаем сколько строк в форме
	if(nStrings < 8)// Запрет на скроллинг
	{
		SetNodeUsing("TUTORIAL_SCROLL_TEXT",false);
		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"TUTORIAL_INFO_TEXT", 13, 1); //1 - запрет, 0 - нет
	}

	if(CheckAttribute(&InterfaceStates,"ShowTutorial"))
	{
		curShowTutorial = sti(InterfaceStates.ShowTutorial);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TUTORIAL_CHECKBOX", 2, 1, curShowTutorial);
	SetNodeUsing("TUTORIAL_CHECKBOX",!bGlobalTutor);

	SetCurrentNode("TUTORIAL_INFO_TEXT");
}

void CloseAlchemyTutorial()
{
	DeleteAttribute(&TEV, "Alchemy.Tutor");

	if(CheckAttribute(&InterfaceStates,"ShowTutorial"))
	{
		if(sti(InterfaceStates.ShowTutorial) != curShowTutorial) SaveGameOptions();
	}

	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("CheckButtonChange","procCheckBoxChange");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	SetEventHandlers();

	XI_WindowDisable("TUTORIAL_MAIN_WINDOW", true);
	XI_WindowShow("TUTORIAL_MAIN_WINDOW", false);
	XI_WindowDisable("TUTORIAL_INFO_WINDOW", true);
	XI_WindowShow("TUTORIAL_INFO_WINDOW", false);

	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode("TABLE_LIST");
}

void SetKeyAttrs()
{
    // GKIC - взять из конкретной группы
    // GetKeyCodeImg - взять из релевантной группы
    obGKIC.Ship_TurnLeft = GetKeyImageChar("Ship_TurnLeft", "Sailing3Pers");
    obGKIC.TimeScale = GetKeyCodeImg("TimeScale");
}

void Tutorial_ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	if (comName == "activate" || comName == "click")
	{
		switch (nodName)
		{
			case "TUTORIAL_B_OK": CloseAlchemyTutorial(); break;
			case "TUTORIAL_B_OK2": CloseAlchemyTutorial(); break;
		}
	}
}

void Tutorial_ShowInfoWindow()
{
	XI_WindowDisable("TUTORIAL_INFO_WINDOW", false);
	XI_WindowShow("TUTORIAL_INFO_WINDOW", true);
}

void Tutorial_HideInfoWindow()
{
	XI_WindowDisable("TUTORIAL_INFO_WINDOW", true);
	XI_WindowShow("TUTORIAL_INFO_WINDOW", false);
}

void Tutorial_procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if(sNodName == "TUTORIAL_CHECKBOX")
	{
        InterfaceStates.ShowTutorial = bBtnState;
	}
}
// BOAL меню предметов
#include "interface\character_all.h"

#event_handler("Control Activation", "ProcessInterfaceControls"); // обработка нажатия клавы

string sPrevChar = "";
string sPrevNode = "";
string sInfoBackNode = "TABLE_ITEMS";

int iRows = 0;

int nLastFillMode = 1;
string sGunFilterNode = "";
int idItemsDescrFile = -1;

int iItemDropItemIndex = -1;
int iItemDropFreeQty = 0;
bool bItemDropQuestItem = false;
bool bItemDropWindowOpen = false;

void InitInterface(string iniName)
{
    InterfaceStack.SelectMenu_node = "LaunchItems"; // запоминаем, что звать по Ф2

	xi_refCharacter = pchar;

	idItemsDescrFile = LanguageOpenFile("ItemsDescribe.txt");

	FillCharactersScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	aref arTableItemsHR;
	makearef(arTableItemsHR, GameInterface.TABLE_ITEMS.hr);
	arTableItemsHR.td1.str = XI_ConvertString("ItemsColonTitle");
	arTableItemsHR.td1.scale = 0.8;
	arTableItemsHR.td2.str = XI_ConvertString("weight") + " " + XI_ConvertString("pcs");
	arTableItemsHR.td2.scale = 0.8;
	arTableItemsHR.td3.str = XI_ConvertString("QuantityShort");
	arTableItemsHR.td3.scale = 0.8;
	arTableItemsHR.td4.str = XI_ConvertString("weight");
	arTableItemsHR.td4.scale = 0.8;

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("frame","ProcessFrame",1);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("ExitMapWindow","ExitMapWindow",0);
	SetEventHandler("ExitReadWindow","ExitReadWindow",0);
	SetEventHandler("SetReadScrollerPos","SetReadScrollerPos",0);
	SetEventHandler("ClickToBlade", "ClickToBlade", 0);
	SetEventHandler("ClickToGun", "ClickToGun", 0);
    SetEventHandler("ClickToMusket", "ClickToMusket", 0);
	SetEventHandler("ClickToSpyGlass", "ClickToSpyGlass", 0);
	SetEventHandler("ClickToCirass", "ClickToCirass", 0);
	SetEventHandler("ClickToAmmo", "ClickToAmmo", 0);
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);
	SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);
	SetEventHandler("Event_UnselectNode", "ProcessInfoUnselect", 0);
	SetEventHandler("ChooseItem", "ShowItemDrop", 0);
	SetEventHandler("ItemDropCancel", "ItemDropCancel", 0);
	SetEventHandler("ItemDropConfirm", "ItemDropConfirm", 0);
	SetEventHandler("ItemDropEditConfirm", "ItemDropEditConfirm", 0);
	SetEventHandler("ItemDropLess", "ItemDropLess", 0);
	SetEventHandler("ItemDropMore", "ItemDropMore", 0);
	SetEventHandler("ItemDropZero", "ItemDropZero", 0);
	SetEventHandler("ItemDropMax", "ItemDropMax", 0);
	SetEventHandler("ItemDropWarningHide", "ItemDropWarningHide", 0);

	XI_RegistryExitKey("ItemsMenu");
    SetVariable();
    SetNewGroupPicture("Weight_PIC", "ICONS_CHAR", "weight");
    SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");

	// доп инфа в шапку --->
	SetFormatedText("WEIGHT", FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / " + GetMaxItemsWeight(xi_refCharacter));
	SetFormatedText("MONEY", FindMoneyString(sti(xi_refCharacter.money)));
	SetFormatedText("CURRENT_DATE_CAPTION", GetDateString() + " "+ GetTimeString());
	// <--

	SetNewPicture("SETUP_BIG_PICTURE", "interfaces\Recon\CharEquip_" + xi_refCharacter.sex + ".tga");
	SetAlertMarks(xi_refCharacter);
	sPrevChar = pchar.id;
}

void ProcessExitCancel()
{
	if (bItemDropWindowOpen)
	{
		ItemDropCancel();
		return;
	}
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("frame","ProcessFrame");
    DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("ExitMapWindow","ExitMapWindow");
	DelEventHandler("ExitReadWindow","ExitReadWindow");
	DelEventHandler("SetReadScrollerPos","SetReadScrollerPos");
	DelEventHandler("ClickToBlade", "ClickToBlade");
	DelEventHandler("ClickToGun", "ClickToGun");
    DelEventHandler("ClickToMusket", "ClickToMusket");
	DelEventHandler("ClickToSpyGlass", "ClickToSpyGlass");
	DelEventHandler("ClickToCirass", "ClickToCirass");
	DelEventHandler("ClickToAmmo", "ClickToAmmo");
	DelEventHandler("OnHeaderClick", "OnHeaderClick");
	DelEventHandler("ExitMsgMenu", "ExitMsgMenu");
	DelEventHandler("Event_UnselectNode", "ProcessInfoUnselect");
	DelEventHandler("ChooseItem", "ShowItemDrop");
	DelEventHandler("ItemDropCancel", "ItemDropCancel");
	DelEventHandler("ItemDropConfirm", "ItemDropConfirm");
	DelEventHandler("ItemDropEditConfirm", "ItemDropEditConfirm");
	DelEventHandler("ItemDropLess", "ItemDropLess");
	DelEventHandler("ItemDropMore", "ItemDropMore");
	DelEventHandler("ItemDropZero", "ItemDropZero");
	DelEventHandler("ItemDropMax", "ItemDropMax");
	DelEventHandler("ItemDropWarningHide", "ItemDropWarningHide");

	if (idItemsDescrFile != -1)
	{
		LanguageCloseFile(idItemsDescrFile);
		idItemsDescrFile = -1;
	}

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

	if (CheckAttribute(&TEV, "UpdateBattleInterface"))
	{
		DeleteAttribute(&TEV, "UpdateBattleInterface");
		DeleteBattleInterface();
		InitBattleInterface();
		StartBattleInterface();
		RefreshBattleInterface();
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

    switch(nodName)
	{
		case "EQUIP_BUTTON":
			if (comName=="activate" || comName=="click")
			{
				EquipPress();
			}
		break;

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
		case "I_ALCHEMY_2":
			if(comName=="click")
			{
			    nodName = "I_ALCHEMY";
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
	    nodName == "I_QUESTBOOK" || nodName == "I_ALCHEMY" ||
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

void ProcessFrame()
{
	string sCurNode = GetCurrentNode();

	// > пока мышь не над описанием - помним текущую ноду, чтобы вернуть ей фокус
	if (sCurNode != "" && sCurNode != "INFO_TEXT" && sCurNode != "INFO_PIC")
		sInfoBackNode = sCurNode;

	if (sInfoBackNode == "CHARACTERS_SCROLL" && sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum)
	{
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		SetButtonsState();
		return;
	}
}

// > мышь ушла с описания: движок сбросил текущую ноду, возвращаем фокус на место
void ProcessInfoUnselect()
{
	string sNode = GetEventData();

	if (sNode != "INFO_TEXT" && sNode != "INFO_PIC") return;

	ReturnInfoFocus();
}

// > фокус не должен оставаться на описании: колесо и стрелки уйдут в никуда
void ReturnInfoFocus()
{
	if (sInfoBackNode == "") sInfoBackNode = "TABLE_ITEMS";

	SetCurrentNode(sInfoBackNode);
}

void SetButtonsState()
{
	string attributeName = "pic" + (nCurScrollNum + 1);
	sPrevChar = xi_refCharacter.id;

	if (GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		xi_refCharacter = &characters[sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character)];
		//FillItemsTable(1) // KZ > убрано, ибо двойная работа: ниже при смене персонажа всё равно сортирует и заполняет
	}
	else
		xi_refCharacter = pchar;

	SetNewPicture("SETUP_BIG_PICTURE", "interfaces\Recon\CharEquip_" + xi_refCharacter.sex + ".tga");
	SetVariable();
}

void SetVariable()
{
	if (sPrevChar == xi_refCharacter.id) return;
	SetFormatedText("SETUP_FRAME_CAPTION", XI_ConvertString("Equipment") + ": " + GetFullNameTitulForm(xi_refCharacter));
	// сортировка -->
	SortItems(xi_refCharacter);
	// сортировка -->
	SetControlsTabMode(1);
	HideItemInfo();
	SetFormatedText("Weight_TEXT", XI_ConvertString("weight") + ": " + FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / "+GetMaxItemsWeight(xi_refCharacter));
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(xi_refCharacter.Money), MONEY_SIGN,MONEY_DELIVER));

	SetNodeUsing("EQUIP_BUTTON" , true);
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
}

void FillItemsTable(int _mode)
{
	int i, iItemQty, q, n = 1;
	float fItemWeight;
	string row, sGood, groupID, itemType;
	bool ok1, ok2, ok3, ok4, ok5;
	aref rootItems, arItem, curItem;
	aref arTableItems;
	aref arTableItemsTD, arTableItemsROW;

	nLastFillMode = _mode; // > запоминаем фильтр для RefreshItemsTable

    string sGun, sMus, sBulletGun, sBulletMus;
    ref rGun, rMus;
    sGun = GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE);
    sBulletGun = LAi_GetCharacterBulletType(xi_refCharacter, GUN_ITEM_TYPE);
    if (sGun != "") rGun = ItemsFromID(sGun);
    sMus = GetCharacterEquipByGroup(xi_refCharacter, MUSKET_ITEM_TYPE);
    sBulletMus = LAi_GetCharacterBulletType(xi_refCharacter, MUSKET_ITEM_TYPE);
    if (sMus != "") rMus = ItemsFromID(sMus);

    string sPowderGun = "";
	string sPowderMus = "";
    if (sGun != "" && sBulletGun != "") sPowderGun = GetGunAmmoAttr(rGun, sBulletGun, "gunpowder");
    if (sMus != "" && sBulletMus != "") sPowderMus = GetGunAmmoAttr(rMus, sBulletMus, "gunpowder");

	makearef(arTableItems, GameInterface.TABLE_ITEMS);
	arTableItems.select = 0;
	arTableItems.top = 0;
	Table_Clear("TABLE_ITEMS", false, true, false);

	// Заполним вещами от нас
	makearef(rootItems, xi_refCharacter.Items);
	q = GetAttributesNum(rootItems);

	// KZ > файл описаний открываем один раз, раньше в цикле открывался-читался-закрывался с диска на каждый предмет
	int idItemsDescr = LanguageOpenFile("ItemsDescribe.txt");
	int iItemIdx;

    for (i = 0; i < q; i++)
    {
		curItem = GetAttributeN(rootItems, i);
		groupID = "";
		itemType = "";

		iItemIdx = Items_FindItem(GetAttributeName(curItem), &arItem);

		if (iItemIdx >= 0)
		{
			row = "tr" + n;
			sGood = arItem.id;
			if ("unarmed" == sGood) continue; //HardCoffee не отображать в инвентаре кулаки
			// Hokkins: новая сортировка предметов -->
			if(CheckAttribute(arItem,"groupID"))  groupID = arItem.groupID;
			if(CheckAttribute(arItem,"itemType")) itemType = arItem.itemType;

			ok1 = false;
			ok2 = false;
			ok3 = false;
			ok4 = false;
			ok5 = false;

			// Снаряжение -->
			if ((groupID == BLADE_ITEM_TYPE)    ||  // холодное оружие
				(groupID == GUN_ITEM_TYPE)      ||  // пистолеты
				(groupID == MUSKET_ITEM_TYPE)   ||  // ружья
                (groupID == SPYGLASS_ITEM_TYPE) ||  // подзорные трубы
				(groupID == CIRASS_ITEM_TYPE)   ||  // костюмы и доспехи
				(groupID == AMMO_ITEM_TYPE))        // боеприпасы
			{
				ok1 = true;
			}
			// Зелья -->
			else if (groupID == POTION_ITEM_TYPE)	// зелья
			{
				ok2 = true;
			}
			// Важное -->
			else if ((groupID == PATENT_ITEM_TYPE) ||	// патенты
					(itemType == "QUESTITEMS")	||		// квестовые предметы
					CheckAttribute(arItem, "mapType"))	// карты сокровищ
			{
				ok3 = true;
			}
			// Разное -->
			else
			{
//				устал комментарить, очень мешает, кому понадобится расскоментит
//				if (MOD_BETTATESTMODE == "On" || bBettaTestMode)
//					DumpAttributes(&arItem);
				
				ok4 = true;
			}

			if(_mode == -1 && groupID != BLADE_ITEM_TYPE) continue;

			if(_mode == -2)
			{
				if (sGunFilterNode == "SLOT_GUN" && groupID != GUN_ITEM_TYPE) continue;
				if (sGunFilterNode == "SLOT_MUSKET" && groupID != MUSKET_ITEM_TYPE) continue;
			}

			if(_mode == -3 && groupID != SPYGLASS_ITEM_TYPE) continue;
			if(_mode == -4 && groupID != CIRASS_ITEM_TYPE) continue;
			if(_mode == -5 && groupID != AMMO_ITEM_TYPE) continue;
			if(_mode ==  1 && groupID == MAPS_ITEM_TYPE && !GetCharacterFreeItem(xi_refCharacter, sGood) && arItem.id != "MapsAtlas") continue;
			if(_mode == 2 && !ok1) continue;
			if(_mode == 3 && !ok2) continue;
			if(_mode == 4 && !ok3) continue;
			if(_mode == 5 && !ok4) continue;

			iItemQty = sti(GetAttributeValue(curItem));

			if (iItemQty > 0)
			{
				fItemWeight = stf(arItem.Weight);
				GameInterface.TABLE_ITEMS.(row).index = iItemIdx;

				makearef(arTableItemsTD, GameInterface.TABLE_ITEMS.(row).td1);
				arTableItemsTD.icon.group = arItem.picTexture;
				arTableItemsTD.icon.image = "itm" + arItem.picIndex;
				arTableItemsTD.icon.offset = "0, 1";
				arTableItemsTD.icon.width = 31;
				arTableItemsTD.icon.height = 31;
				arTableItemsTD.textoffset = "31,0";
				arTableItemsTD.str = LanguageConvertString(idItemsDescr, arItem.name);
				arTableItemsTD.scale = 0.85;
				arTableItemsTD.color = argb(255, 255, 255, 255);

				if (IsEquipCharacterByItem(xi_refCharacter, sGood))
					ok5 = true;
				else if (groupID == AMMO_ITEM_TYPE)
				{
					if (sGun != "" && sBulletGun != "")
					{
                        if (sGood == sBulletGun || sGood == sPowderGun)
                            ok5 = true; // Пуля или пороховые приблуды пистолета
                    }
                    if (!ok5 && sMus != "" && sBulletMus != "")
                    {
                        // Если не пуля/приблуда пистолета, то мб мушкета?
                        if (sGood == sBulletMus || sGood == sPowderMus)
                            ok5 = true;
                    }
				}

				if (ok5)
					arTableItemsTD.color = argb(255, 245, 230, 191);

				makearef(arTableItemsROW, GameInterface.TABLE_ITEMS.(row));
				arTableItemsROW.td2.str   = FloatToString(fItemWeight, 1);
				arTableItemsROW.td2.scale = 0.9;
				arTableItemsROW.td3.str   = iItemQty;
				arTableItemsROW.td3.scale = 0.9;
				arTableItemsROW.td4.str   = FloatToString(fItemWeight * iItemQty, 1);
				arTableItemsROW.td4.scale = 0.9;
				n++;
			}
		}
    }
    iRows = n;
	LanguageCloseFile(idItemsDescr);
	Table_UpdateWindow("TABLE_ITEMS");
	if (_mode == 1)
	{
		FillItemsSelected();
	}
}

void ClickToBlade()     {FillItemsTable(-1); ClickToItem(BLADE_ITEM_TYPE);}
void ClickToGun()       {sGunFilterNode = "SLOT_GUN";    FillItemsTable(-2); ClickToItem(GUN_ITEM_TYPE);}
void ClickToMusket()    {sGunFilterNode = "SLOT_MUSKET"; FillItemsTable(-2); ClickToItem(MUSKET_ITEM_TYPE);}
void ClickToSpyGlass()  {FillItemsTable(-3); ClickToItem(SPYGLASS_ITEM_TYPE);}
void ClickToCirass()    {FillItemsTable(-4); ClickToItem(CIRASS_ITEM_TYPE);}
void ClickToAmmo()      {FillItemsTable(-5); ClickToItem(AMMO_ITEM_TYPE);}

void ClickToItem(string sEquipType)
{
	sPrevNode = GetCurrentNode();
	// > наведённое описание не должно подменять слот, с которого пришли
	if (sPrevNode == "INFO_TEXT" || sPrevNode == "INFO_PIC") sPrevNode = sInfoBackNode;

	if (!CheckAttribute(xi_refCharacter, "equip." + sEquipType) || xi_refCharacter.equip.(sEquipType) == "")
	{
		HideItemInfo();
		return;
	}

	string row, sCurItem = GetCharacterEquipByGroup(xi_refCharacter, sEquipType);
    if (sCurItem == "unarmed")
    {
		HideItemInfo();
		return;
    }

	int q, iCurItemIdx = FindItem(sCurItem);

	for (q = 1; q < iRows; q++)
	{
		row = "tr" + q;

		if (iCurItemIdx == sti(GameInterface.TABLE_ITEMS.(row).index))
		{
			Event("TableSelectChange", "sll", "TABLE_ITEMS", q, 1); // Выбираем в таблице предмет снаряжения
			GameInterface.TABLE_ITEMS.select = q;
			if (q < 5) q = 5;
			GameInterface.TABLE_ITEMS.top = q-5; // Стараемся красиво проскроллить таблицу на этот предмет
			Table_UpdateWindow("TABLE_ITEMS");
			SetCurrentNode("TABLE_ITEMS");
			break;
		}
	}
}

// KZ > перезаполнить таблицу текущим фильтром, сохранив выбор и прокрутку после экипировки/снятия (+ теперь подсветка экипированных вещей обновляется на лету)
void RefreshItemsTable()
{
	int iSelSave = sti(GameInterface.TABLE_ITEMS.select);
	int iTopSave = sti(GameInterface.TABLE_ITEMS.top);

	FillItemsTable(nLastFillMode);

	if (iSelSave > iRows - 1) iSelSave = iRows - 1;
	if (iSelSave > 0)
	{
		GameInterface.TABLE_ITEMS.select = iSelSave;
		GameInterface.TABLE_ITEMS.top = iTopSave;
		Table_UpdateWindow("TABLE_ITEMS");
	}
}

void FillItemsSelected()
{
	ref rItem;
	aref arEquip; makearef(arEquip, xi_refCharacter.equip);
	int i, iItem, q = GetAttributesNum(arEquip);
	string sItem, sTemp = "interfaces\empty_back.tga";

	// Скроем по умолчанию
	SetNewPicture("SLOT_BLADE", sTemp);
	SetNewPicture("SLOT_GUN", sTemp);
	SetNewPicture("SLOT_SPYGLASS", sTemp);
	SetNewPicture("SLOT_CUIRASS", sTemp);
	SetNewPicture("SLOT_MUSKET", sTemp);
	SetNewPicture("SLOT_AMMO_GUN", sTemp);
	SetNewPicture("SLOT_POWDER_GUN", sTemp);
	SetNewPicture("SLOT_AMMO_MUSKET", sTemp);
	SetNewPicture("SLOT_POWDER_MUSKET", sTemp);

	SetAmmoBlink("SLOT_AMMO_GUN", false);
	SetAmmoBlink("SLOT_POWDER_GUN", false);
	SetAmmoBlink("SLOT_AMMO_MUSKET", false);
	SetAmmoBlink("SLOT_POWDER_MUSKET", false);

	for (i = 0; i < q; i++)
	{
		sItem = GetAttributeValue(GetAttributeN(arEquip, i));
		if (sItem == "") continue;

		iItem = FindItem(sItem);
		if (iItem >= 0) rItem = ItemsFromID(sItem);
		else continue;

		switch (rItem.groupID)
		{
			case BLADE_ITEM_TYPE:
				SetNewGroupPicture("SLOT_BLADE", rItem.picTexture, "itm" + rItem.picIndex);
				SetNodeUsing("SLOT_BLADE", true);
			break;

			case GUN_ITEM_TYPE:
				SetAmmoBlank("gun");
				SetGunNode("GUN", rItem);
			break;

			case MUSKET_ITEM_TYPE:
				SetAmmoBlank("musket");
				SetGunNode("MUSKET", rItem);
			break;

			case SPYGLASS_ITEM_TYPE:
				SetNewGroupPicture("SLOT_SPYGLASS", rItem.picTexture, "itm" + rItem.picIndex);
				SetNodeUsing("SLOT_SPYGLASS", true);
			break;

			case CIRASS_ITEM_TYPE:
				SetNewGroupPicture("SLOT_CUIRASS", rItem.picTexture, "itm" + rItem.picIndex);
				SetNodeUsing("SLOT_CUIRASS", true);
			break;
		}
	}
}

void SetGunNode(string sGunType, ref rItem)
{
    ref rAmmo, rPowder;
    string sBullet, sPowder;
    int iAmmoQty, iPowderQty;
    bool bNoAmmo, bNoPowder;

    SetNewGroupPicture("SLOT_" + sGunType, rItem.picTexture, "itm" + rItem.picIndex);
    SetNodeUsing("SLOT_" + sGunType, true);

    sBullet = LAi_GetCharacterBulletType(xi_refCharacter, sGunType);

    if (sBullet == "" || FindItem(sBullet) < 0)
    {
        // > боеприпас не выбран - мигать нечему
        SetAmmoBlink("SLOT_AMMO_" + sGunType, false);
        SetAmmoBlink("SLOT_POWDER_" + sGunType, false);
        return;
    }

    rAmmo = ItemsFromID(sBullet);
    iAmmoQty = GetCharacterItem(xi_refCharacter, rAmmo.id);
    bNoAmmo = iAmmoQty < 1; // > пуль нет - слот мигает красным
    SetAmmoBlink("SLOT_AMMO_" + sGunType, bNoAmmo);
    SetNewGroupPicture("SLOT_AMMO_" + sGunType, rAmmo.picTexture, "itm" + rAmmo.picIndex);

    sPowder = GetGunAmmoAttr(rItem, sBullet, "gunpowder");

    if (sPowder == "" || FindItem(sPowder) < 0)
    {
        // > этому боеприпасу порох\капсюли не требуются
        SetAmmoBlink("SLOT_POWDER_" + sGunType, false);
        return;
    }

    rPowder = ItemsFromID(sPowder);
    iPowderQty = GetCharacterItem(xi_refCharacter, rPowder.id);
    bNoPowder = iPowderQty < 1; // > пороха нет - слот мигает красным
    SetAmmoBlink("SLOT_POWDER_" + sGunType, bNoPowder);
    SetNewGroupPicture("SLOT_POWDER_" + sGunType, rPowder.picTexture, "itm" + rPowder.picIndex);
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture = "-1";
	string sGroup, sGroupPicture;

	switch (sCurrentNode)
	{
		case "WEIGHT":
			sHeader = XI_ConvertString("Weight");
			sText1 = GetRPGText("Weight_hint");
		break;

		case "MONEY":
			sHeader = XI_ConvertString("Money");
			sText1 = GetRPGText("Money_hint");
		break;
	}
	if (sHeader == "")
		sHeader = XI_ConvertString("buttonItems");

	if (sText1 == "")
		sText1 = XI_ConvertString("ItemsHelper_1") + XI_ConvertString("ItemsHelper_2") + XI_ConvertString("ItemsHelper_3");

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);

}

void HideInfoWindow()
{
	CloseTooltip();
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    
    // отрисовка инфы
    SetItemInfo();
}

void SetItemInfo()
{
	if (CurTable == "" || !CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index"))
		return;

	iItemDropItemIndex = sti(GameInterface.(CurTable).(CurRow).index);
	int iGoodIndex = iItemDropItemIndex;

	if (iGoodIndex < 0)
		return;

	iItemDropFreeQty = GetItemDropFreeQty(&Items[iGoodIndex]);
	bItemDropQuestItem = IsQuestItemForDrop(&Items[iGoodIndex]);

	string sID = "";
	if (bBettaTestMode) sID = "  ID: " +Items[iGoodIndex].id;
	SetFormatedText("INFO_TEXT", GetItemDescribe(iGoodIndex, xi_refCharacter) +sID);

	// evganat - пасха
	if(CheckAttribute(xi_refCharacter, "easter.damage"))
	{
		string sItem = Items[iGoodIndex].id;
		if(CheckAttribute(xi_refCharacter, "easter.damage."+sItem))
		{
			switch(xi_refCharacter.easter.damage.(sItem))
			{
				case "1":	AddLineToFormatedText("INFO_TEXT", XI_ConvertString("ItemsHelper_4") + " 25%");	break;
				case "2":	AddLineToFormatedText("INFO_TEXT", XI_ConvertString("ItemsHelper_4") + " 50%");	break;
			}
			SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 8, 1, argb(255,139,0,255));
		}
	}

	SetNewGroupPicture("INFO_PIC", Items[iGoodIndex].picTexture, "itm" + Items[iGoodIndex].picIndex);
	SetNodeUsing("INFO_TEXT", true);
	SetNodeUsing("INFO_PIC", true);
	SetVAligmentFormatedText("INFO_TEXT");

	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	SetSelectable("EQUIP_BUTTON",ThisItemCanBeEquip(&Items[iGoodIndex]));
}

bool IsQuestItemForDrop(ref rItem)
{
	if (IsQuestUsedItem(rItem.id)) return true;
	if (CheckAttribute(rItem, "ItemType") && rItem.ItemType == "QUESTITEMS") return true;
	return false;
}

int GetItemDropFreeQty(ref rItem)
{
	if (CheckAttribute(rItem, "groupID") && rItem.groupID == READING_ITEM_TYPE) return GetCharacterItem(xi_refCharacter, rItem.id);
	return GetCharacterFreeItem(xi_refCharacter, rItem.id);
}

int GetItemDropQty()
{
	if (CheckAttribute(&GameInterface, "item_drop_edit.str")) return sti(GameInterface.item_drop_edit.str);
	if (CheckAttribute(&GameInterface, "ITEM_DROP_EDIT.str")) return sti(GameInterface.ITEM_DROP_EDIT.str);
	if (CheckAttribute(&GameInterface, "qty_edit.str")) return sti(GameInterface.qty_edit.str);
	return 0;
}

void SetItemDropQty(int iQty)
{
	GameInterface.item_drop_edit.str = iQty;
	GameInterface.ITEM_DROP_EDIT.str = iQty;
	GameInterface.qty_edit.str = iQty;
}

void ShowItemDrop()
{
	if (bItemDropWindowOpen) return;
	if (CurTable == "" || !CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index")) return;

	iItemDropItemIndex = sti(GameInterface.(CurTable).(CurRow).index);
	if (iItemDropItemIndex < 0) return;

	ref rItem = &Items[iItemDropItemIndex];
	iItemDropFreeQty = GetItemDropFreeQty(rItem);
	bItemDropQuestItem = IsQuestItemForDrop(rItem);

	if (bItemDropQuestItem || iItemDropFreeQty <= 0)
	{
		if (bItemDropQuestItem) SetFormatedText("ITEM_DROP_WARNING_TEXT", XI_ConvertString("Drop Errorq"));
		else SetFormatedText("ITEM_DROP_WARNING_TEXT", XI_ConvertString("Drop Errore"));
		XI_WindowDisable("ITEM_DROP_WARNING_WINDOW", false);
		XI_WindowShow("ITEM_DROP_WARNING_WINDOW", true);
		PostEvent("ItemDropWarningHide", 1200);
		return;
	}

	bItemDropWindowOpen = true;
	XI_WindowDisable("MAIN_WINDOW", true);
	SetNodeUsing("INFO_TEXT", false);
	SetNodeUsing("INFO_PIC", false);

	SetFormatedText("ITEM_DROP_TITLE", XI_ConvertString("ItemDrop_Title"));
	SetFormatedText("ITEM_DROP_NAME", GetItemName(rItem.id));
	SetFormatedText("ITEM_DROP_DESC", GetItemDescribe(iItemDropItemIndex, xi_refCharacter));
	SetFormatedText("ITEM_DROP_HAVE", "" + iItemDropFreeQty);
	SetNewGroupPicture("ITEM_DROP_ICON", rItem.picTexture, "itm" + rItem.picIndex);

	if (iItemDropFreeQty < 2) SetItemDropQty(1);
	else SetItemDropQty(0);

	XI_WindowDisable("ITEM_DROP_WINDOW", false);
	XI_WindowShow("ITEM_DROP_WINDOW", true);
	ItemDropChangeQty();
	SetEventHandler("frame", "ItemDropDelaySelect", 0);
}

void ItemDropDelaySelect()
{
	DelEventHandler("frame", "ItemDropDelaySelect");
	SetCurrentNode("ITEM_DROP_EDIT");
}

void ItemDropDelaySelectSingle()
{
	DelEventHandler("frame", "ItemDropDelaySelectSingle");
	SetCurrentNode("ITEM_DROP_OK_S");
}

void ItemDropWarningHide()
{
	XI_WindowDisable("ITEM_DROP_WARNING_WINDOW", true);
	XI_WindowShow("ITEM_DROP_WARNING_WINDOW", false);
}

void ItemDropCancel()
{
	if (!bItemDropWindowOpen) return;

	XI_WindowDisable("ITEM_DROP_WINDOW", true);
	XI_WindowShow("ITEM_DROP_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);
	bItemDropWindowOpen = false;

	SetFormatedText("WEIGHT", FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / " + GetMaxItemsWeight(xi_refCharacter));
	SetFormatedText("Weight_TEXT", XI_ConvertString("weight") + ": " + FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / " + GetMaxItemsWeight(xi_refCharacter));
	if (CurTable != "" && CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index")) SetItemInfo();
	else HideItemInfo();
	SetCurrentNode("TABLE_ITEMS");
}

void ItemDropConfirm()
{
	if (!bItemDropWindowOpen || iItemDropItemIndex < 0) return;

	ref rItem = &Items[iItemDropItemIndex];
	if (IsQuestItemForDrop(rItem))
	{
		ItemDropCancel();
		return;
	}

	int iDropQuantity = GetItemDropQty();
	int iFreeQty = GetItemDropFreeQty(rItem);
	if (iDropQuantity > iFreeQty) iDropQuantity = iFreeQty;
	if (iDropQuantity <= 0) return;

	string sItemID = rItem.id;
	string sItemName = GetItemName(sItemID);
	RemoveItems(xi_refCharacter, sItemID, iDropQuantity);

	ItemDropCancel();
	RefreshItemsTable();
	FillItemsSelected();
	SetFormatedText("WEIGHT", FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / " + GetMaxItemsWeight(xi_refCharacter));
	SetFormatedText("Weight_TEXT", XI_ConvertString("weight") + ": " + FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / " + GetMaxItemsWeight(xi_refCharacter));

	if (CurTable != "" && CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index")) SetItemInfo();
	else HideItemInfo();

	Log_Info(StringFromKey("InfoMessages_267", sItemName, iDropQuantity));
}

void ItemDropEditConfirm()
{
	ItemDropChangeQty();
	if (GetSelectable("ITEM_DROP_OK")) SetCurrentNode("ITEM_DROP_OK");
	else SetCurrentNode("ITEM_DROP_CANCEL");
}

void ItemDropChangeQty()
{
	if (iItemDropItemIndex < 0) return;

	ref rItem = &Items[iItemDropItemIndex];
	iItemDropFreeQty = GetItemDropFreeQty(rItem);
	int iQty = GetItemDropQty();
	if (iQty < 0) iQty = 0;
	if (iQty > iItemDropFreeQty) iQty = iItemDropFreeQty;
	SetItemDropQty(iQty);

	SetSelectable("ITEM_DROP_OK", iQty > 0);
	SetSelectable("ITEM_DROP_LESS_ALL", iQty > 0);
	SetSelectable("ITEM_DROP_LESS", iQty > 0);
	SetSelectable("ITEM_DROP_MORE", iQty < iItemDropFreeQty);
	SetSelectable("ITEM_DROP_MORE_ALL", iQty < iItemDropFreeQty);

	float fWeight = GetItemsWeight(xi_refCharacter) - stf(rItem.Weight) * iQty;
	if (fWeight < 0.0) fWeight = 0.0;
	string sWeightAfter = FloatToString(fWeight, 1) + " / " + GetMaxItemsWeight(xi_refCharacter);

	SetFormatedText("ITEM_DROP_HAVE", "" + iItemDropFreeQty);
	SetFormatedText("ITEM_DROP_WEIGHT", sWeightAfter);
	SetFormatedText("WEIGHT", sWeightAfter);
	SetFormatedText("Weight_TEXT", XI_ConvertString("weight") + ": " + sWeightAfter);
}

void ItemDropLess()
{
	if (!bItemDropWindowOpen) return;
	SetItemDropQty(GetItemDropQty() - 1);
	ItemDropChangeQty();
}

void ItemDropMore()
{
	if (!bItemDropWindowOpen) return;
	SetItemDropQty(GetItemDropQty() + 1);
	ItemDropChangeQty();
}

void ItemDropZero()
{
	if (!bItemDropWindowOpen) return;
	SetItemDropQty(0);
	ItemDropChangeQty();
}

void ItemDropMax()
{
	if (!bItemDropWindowOpen) return;
	SetItemDropQty(iItemDropFreeQty);
	ItemDropChangeQty();
}

void HideItemInfo()
{
	string sCurNode = GetCurrentNode();

	SetNodeUsing("INFO_TEXT", false);
	SetNodeUsing("INFO_PIC", false);

	// > прячем ноду, на которой стоит фокус - мышь могла не сдвинуться и события ухода не будет
	if (sCurNode == "INFO_TEXT" || sCurNode == "INFO_PIC") ReturnInfoFocus();

	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	SetSelectable("EQUIP_BUTTON",false);
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode("TABLE_ITEMS");
	HideItemInfo();
	SetControlsTabMode(sti(strcut(sNodName, 7, 7)));
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255,196,196,196);
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
			nColor1 = argb(255,255,255,255);
		break;
		case 2:
			sPic2 = "TabDeSelected";
			nColor2 = argb(255,255,255,255);
		break;
		case 3:
			sPic3 = "TabDeSelected";
			nColor3 = argb(255,255,255,255);
		break;
		case 4:
			sPic4 = "TabDeSelected";
			nColor4 = argb(255,255,255,255);
		break;
		case 5:
			sPic5 = "TabDeSelected";
			nColor5 = argb(255,255,255,255);
		break;
	}
    
	SetNewGroupPicture("TABBTN_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_3", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_4", "TABS", sPic4);
	SetNewGroupPicture("TABBTN_5", "TABS", sPic5);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_2", 8,0,nColor2);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_3", 8,0,nColor3);
    SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_4", 8,0,nColor4);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_5", 8,0,nColor5);
	FillControlsList(nMode);
}

void FillControlsList(int nMode)
{
	switch (nMode)
	{
	    case 1: FillItemsTable(1); break;  // все
	    case 2: FillItemsTable(2); break;  // снаряжение
	    case 3: FillItemsTable(3); break;  // зелья
	    case 4: FillItemsTable(4); break;  // важное
		case 5: FillItemsTable(5); break;  // разное
	}
}

string GetPriorGun()
{
	string sPistol = GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE);
	string sMusket = GetCharacterEquipByGroup(xi_refCharacter, MUSKET_ITEM_TYPE);
	bool bMusPrior = MusketPriority(xi_refCharacter);
	bool bIsMusket = StrEndsWith(sPrevNode, "_MUSKET");

	if (sPistol != "")
	{
		if (sMusket == "" || and(!bMusPrior, !bIsMusket) || and(StrEndsWith(sPrevNode, "_GUN"), !bIsMusket))
			return sPistol;
		else if (sMusket != "" && or(bMusPrior, bIsMusket))
			return sMusket;
	}
	else if (sMusket != "")
		return sMusket;

	return "";
}

bool ThisItemCanBeEquip(aref arItem)
{
	ref rItem;
	string groupID;
    bool MushOfficer = CheckAttribute(xi_refCharacter, "MushForever");

	// evganat - энциклопедия
	if (arItem.id == "Encyclopedia")
	{
		return true;
	}
	if (arItem.id == "underwater") // скафандр
	{
		return false;
	}
	if (arItem.id == "recon_potion" && GetDlcEnabled(NABOB_PACK))
	{
		return true;
	}
	if (arItem.id == "legendGuide")
	{
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Read it"));
		if (CheckCharacterPerk(pchar, "legendGuideRead"))
		{
			return false;
		}
		return true;
	}
	if (!CheckAttribute(arItem,"groupID"))
	{
		return false;
	}

    groupID = arItem.groupID;

	if (groupID == POTION_ITEM_TYPE || groupID == ALCHEMY_ITEM_TYPE)
	{
		return false;
	}
	
	if (groupID == AMMO_ITEM_TYPE)
	{
		SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "EQUIP_BUTTON", 0, "#" + XI_ConvertString("Equip ammo"));

		string sGun = GetPriorGun();

		if (sGun == "")
			return false;

		rItem = ItemsFromID(sGun);
		if (HasStr(rItem.chargetype, arItem.id))
		{
            string sBullet = LAi_GetCharacterBulletType(xi_refCharacter, rItem.groupID);
			if (sBullet == arItem.id || and(sGun == "pistol7", !HasStr(arItem.id, "_colt")))
				return false;

			return true;
		}

		return false;
	}
	
	if (arItem.id == "MapsAtlas") 
	{
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Open that"));
		return true;
	}

	if (groupID == MAPS_ITEM_TYPE)
	{
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Explore"));
		return true;
	}
	else if (groupID == READING_ITEM_TYPE)
	{
		if (and(StrStartsWith(arItem.id, "recipe_"), CheckAttribute(arItem, "result") && isMultiObjectKnown(arItem.result)) || and(CheckAttribute(arItem, "blockRead") && arItem.blockRead == "1", true)) //если прочитано, то читать больше не даем
		{
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Already read"));
			return false;
		}
		else
		{
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Read it"));
			return true;
		}
	}
	else if (groupID == GUN_ITEM_TYPE)
	{
        if (MushOfficer) return false;
        // KZ > картечные пистолеты только с перком "Базовая стрельба"
        if (HasStrEx(arItem.chargetype, "grape,echin", "|") && !IsCharacterPerkOn(xi_refCharacter, "Gunman")) return false;
        // KZ > двухзарядные пистолеты только с перком "Экспертная стрельба"
        if (sti(arItem.chargeQ) == 2 && !IsCharacterPerkOn(xi_refCharacter, "GunAdvanced")) return false;
        // KZ > многозарядные пистолеты только с перком "Профессиональная стрельба"
        if (sti(arItem.chargeQ) > 2 && !IsCharacterPerkOn(xi_refCharacter, "GunProfessional")) return false;
	}
	else if (groupID == MUSKET_ITEM_TYPE)
	{
        // Дуглас
		if (xi_refCharacter.id == "Douglas" || arItem.id == "mushket2x2") return false;
        // Для мушкетов нужен соответствующий перк
        if (!IsCharacterPerkOn(xi_refCharacter, "MusketsTraining")) return false;
        if (arItem.id == "mushket_H2" && !IsCharacterPerkOn(xi_refCharacter, "GunProfessional")) return false;
	}
    else if (groupID == BLADE_ITEM_TYPE)
    {
    	if (arItem.id == "RapierReCon" && !GetDlcEnabled(NABOB_PACK)) return false; //HardCoffee TODO: после открытия скриптов убрать
        if (MushOfficer) return false;
    }

    if (xi_refCharacter.id == pchar.id && CheckAttribute(&TEV, "tPunch"))
    	return false; //HardCoffee на время кулачного боя нельзя сменить оружие

    if (IsEquipCharacterByItem(xi_refCharacter, arItem.id))
	{
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Remove that"));
        if (MushOfficer && groupID == MUSKET_ITEM_TYPE)
            return false;
		if (groupID == PATENT_ITEM_TYPE)
			return false;
		if (CheckAttribute(xi_refCharacter,"NonRemovable"))
			return false;	//HardCoffee убираю возможность снять вещи с квестовых персонажей
	}
	else
	{
		if (groupID == CIRASS_ITEM_TYPE && !IsCharacterPerkOn(xi_refCharacter,"Ciras"))
	    {
		    if (!CheckAttribute(arItem, "Clothes")) return false;
		    if (arItem.Clothes == false) return false;
	    }
		if (IsEquipCharacterByItem(xi_refCharacter, "underwater")) // Логика в скафандре
		{
            if (groupID == CIRASS_ITEM_TYPE || groupID == MUSKET_ITEM_TYPE || groupID == GUN_ITEM_TYPE)
                return false;
		}

		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	}

	return true;
}

void EquipPress()
{
	if (CurTable == "" || !CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".index"))
		return;

	int  iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	if (iGoodIndex < 0)
		return;

	sPrevChar = "";
	ref itmRef = &Items[iGoodIndex];
	string totalInfo;
	int  i = -1;

	// evganat - энциклопедия
	if (itmRef.ID == "encyclopedia")
	{
		pchar.ShowEncyclopedia = true;
		IDoExit(RC_INTERFACE_ENCYCLOPEDIA);
		return;
	}
	if (itmRef.ID == "recon_potion")
	{
		if (!GetDlcEnabled(NABOB_PACK))
		{
			Log_Info("You've the item, but don't have the Suppot Pack? Is that some mistake or not?");
			return;
		}
		if (!CheckAttribute(&TEV, "gotNabobRevard"))
		{
			Log_Info("There's something wrong... Have you took it from the cabin chest?");
			return;
		}
		if (TEV.gotNabobRevard == "skillTaken")
		{
			Log_Info("You've already used that item! Where did you get another one?");
		    return;
		}
		if (TEV.gotNabobRevard == "revardTaken")
		{
			//Передать офицеру эту хрень низя так как IsQuestUsedItem чекает цену
			TakeNItems(PChar, "recon_potion", -sti(PChar.Items.recon_potion));
			AddCharacterSkillDontClearExp(pchar, SKILL_F_LIGHT, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_FENCING, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_F_HEAVY, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_PISTOL, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_FORTUNE, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_LEADERSHIP, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_COMMERCE, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_ACCURACY, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_CANNONS, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_SAILING, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_REPAIR, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_GRAPPLING, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_DEFENCE, 5);
			AddCharacterSkillDontClearExp(pchar, SKILL_SNEAK, 5);
			TEV.gotNabobRevard = "skillTaken";
			SetVariable();
		}
		else
		{
		    Log_Info("There's kinda mistake...");
		}

		return;
	}
	if (itmRef.id == "legendGuide")
	{
		TakeNItems(PChar, "legendGuide", -sti(PChar.Items.legendGuide));
		SetCharacterPerk(pchar, "legendGuideRead");
		SetEnergyToCharacter(pchar);
		LAi_SetCurHP(pchar,LAi_GetCharacterMaxHP(pchar));
		PlaySound("Interface\important_item.wav");
		SetVariable();
		return;
	}

	if (CheckAttribute(itmRef, "groupID"))
	{
		string itmGroup = itmRef.groupID;
		// Dolphin -> (по квестам) в QuestUtilite.c
		if (itmGroup == READING_ITEM_TYPE)
        {
			if (StrStartsWith(itmRef.id, "recipe_")) // > рецепты
			{
				if (isMultiObjectKnown(itmRef.result))
					LogSound_WithNotify(XI_ConvertString("KnownRecipe"), "interface\knock.wav", "Alchemy");
				else
				{
					RemoveItems(pchar, itmRef.id, 1);
					AddQuestRecordInfo("Recipe", itmRef.result);
					SetAlchemyRecipeKnown(itmRef.result);
					SetVariable();
					LogSound_WithNotify(XI_ConvertString("RecipeUpdate"), "Notebook_2", "Alchemy");
				}
			}
			
            SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Read it"));
            //если возвращаем тру, то открываем окно для чтения письма, письма можно перечитывать сколько угодно раз
            //если возвращаем не тру, то обновляем описание и блочим кнопку на "Прочитанно"
            if (CheckLetterForQuest(itmRef)) ShowReadWindow();
            else itmRef.blockRead = true;
            SetFormatedText("INFO_TEXT", GetItemDescribe(iGoodIndex, xi_refCharacter));
            SetVAligmentFormatedText("INFO_TEXT");
        }
        // Dolphin чтение писем <--
		
		if (itmGroup == SPYGLASS_ITEM_TYPE && bSeaActive && !bAbordageStarted)
			TEV.UpdateBattleInterface = "1";
		
		if (itmGroup == MAPS_ITEM_TYPE)
		{
			// Warship. Отличная карта, у неё отдельный интерфейс
			if(itmRef.ID == "Map_Best")
			{
				TEV.BackToItems = true;
				IDoExit(RC_INTERFACE_BEST_MAP);
				return;
			}
			// Ugeen --> интерфейс атласа карт
			if(itmRef.ID == "MapsAtlas") // взяли атлас карт
			{
				TEV.ShowMapsAtlas = true; // Флаг, что смотрим из интерфейса предметов
				IDoExit(RC_INTERFACE_MAPVIEW);
				return;
			}
			// Ugeen --> специальная квестовая карта
			if(itmRef.id == "mapQuest")
			{
				totalInfo = GenQuest_GetQuestTreasureMapDescription(itmRef);
				SetNewPicture("MAP_PICTURE", "interfaces\Maps\treasure map.tga");
				SetFormatedText("MAP_TEXT", totalInfo);
				SetVAligmentFormatedText("MAP_TEXT");
				ShowMapWindow();
				return;
			}
            if (itmRef.id == "map_full" || itmRef.id == "map_part1" || itmRef.id == "map_part2")
            {// клады
            	SetNewPicture("MAP_PICTURE", "interfaces\Maps\treasure map.tga");
            	if (GetCharacterItem(pchar, "map_part1")>0  && GetCharacterItem(pchar, "map_part2")>0)
			    {
			        TakeNItems(pchar, "map_part1", -1);
			        TakeNItems(pchar, "map_part2", -1);
			        TakeNItems(pchar, "map_full", 1);
					itmRef = ItemsFromID("map_full");
			        // здесь генерация назначение и типа клада
			        pchar.GenQuest.TreasureBuild = true;
			        FillMapForTreasure(itmRef);
			        SetVariable();
			    }
			    // тут применяем логику двух кусков, из них одна карта <--
			    if (itmRef.mapType == "Full")
			    {
                    if (!CheckAttribute(itmRef, "MapIslId"))
                    {
                        FillMapForTreasure(itmRef); //заполним если смотрим карту из сундука
                    }
		            if (sti(itmRef.MapTypeIdx) == -1)
				    {
                        SetFormatedText("MAP_TEXT", GetConvertStr("type_fake", "MapDescribe.txt"));
					    DeleteAttribute(itmRef, "MapIslId");
					    TakeNItems(PChar, "map_full", -1);
                        SetVariable(); //fix
				    }
				    else
				    {
                        //totalInfo = GetConvertStr(itmRef.MapIslId, "LocLables.txt");
                        i = FindLocation(itmRef.MapLocId);  // ищем ареал
						if (i != -1 && locations[i].islandId != "Mein")
                        {
                            totalInfo = GetConvertStr(locations[i].islandId, "LocLables.txt");
                            totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx + "_isl", "MapDescribe.txt") + " " + totalInfo;
                        }
                        else
                        {
                            totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx + "_mein", "MapDescribe.txt");
                        }
						itmRef.MapIslName = totalInfo;
						totalInfo = GetConvertStr(itmRef.MapLocId, "MapDescribe.txt") + ", " + GetConvertStr(itmRef.MapLocId + "_" + itmRef.MapBoxId, "MapDescribe.txt");
				        itmRef.MaplocName = totalInfo;

				        totalInfo = GetConvertStr("type_full_" + itmRef.MapTypeIdx, "MapDescribe.txt");
				        totalInfo = GetAssembledString(totalInfo, itmRef);
				        SetFormatedText("MAP_TEXT", totalInfo);
				    }
			    }
			    else
			    {
           			SetFormatedText("MAP_TEXT", GetConvertStr("type_part", "MapDescribe.txt"));
				}
            	SetVAligmentFormatedText("MAP_TEXT");
            }
            else
            {
				if (LanguageGetLanguage() == "Russian")
				{
					SetNewPicture("MAP_PICTURE", "interfaces\Maps\russian\" + itmRef.imageTga + ".tga");
				}
				else
				{
					if (LanguageGetLanguage() == "Chinese")
					{
						SetNewPicture("MAP_PICTURE", "interfaces\Maps\chinese\" + itmRef.imageTga + ".tga");
					}
					else
					{
						SetNewPicture("MAP_PICTURE", "interfaces\Maps\english\" + itmRef.imageTga + ".tga");
					}
				}

            	SetFormatedText("MAP_TEXT", "");
            }
            SetFormatedText("MAP_CAPTION", XI_ConvertString("titleMapRead"));

            ShowMapWindow();
		}
		else
		{
			//не даем менять оружие, если оно уже в руках
			if (LAi_CheckFightMode(xi_refCharacter) != 0)
			{
				ShowMsgMenu();
				return;
			}
			if (itmGroup == MUSKET_ITEM_TYPE)
			{
                if (IsEquipCharacterByItem(xi_refCharacter, itmRef.id))
                {
                    SetAmmoBlank("musket");
                    SetCharacterToMushketer(xi_refCharacter, "");
				}
                else SetCharacterToMushketer(xi_refCharacter, itmRef.id);
			}
			else if (itmGroup == AMMO_ITEM_TYPE)
            {
                string sCurrGun = GetPriorGun();

                if (sCurrGun == "")
                {
                    SetAmmoBlank("gun");
                    SetAmmoBlank("musket");
                    return;
                }

                ref rGun = ItemsFromID(sCurrGun);
                string sGunType = rGun.groupID;

                if (CheckAttribute(xi_refCharacter, "chr_ai." + sGunType + ".bullet") && xi_refCharacter.chr_ai.(sGunType).bullet != "")
                    SetNewGroupPicture("SLOT_AMMO_" + sGunType, itmRef.picTexture, "itm" + itmRef.picIndex);
                else
                    SetNewGroupPicture("SLOT_AMMO_" + sGunType, "BLANK", "BLANK");

                LAi_SetCharacterUseBullet(xi_refCharacter, sGunType, itmRef.ID);
                LAi_GunSetUnload(xi_refCharacter, sGunType);

                LogSound_WithNotify(StringFromKey("InfoMessages_198", GetFullName(xi_refCharacter), GetConvertStr(rGun.name, "ItemsDescribe.txt"), GetConvertStr(itmRef.name, "ItemsDescribe.txt")), "Reload", "AmmoSelect");
                SetVariable();
                FillItemsSelected();
                return;
            }
            else
            {
                if (IsEquipCharacterByItem(xi_refCharacter, itmRef.id))
                {
                    if (itmGroup == GUN_ITEM_TYPE) SetAmmoBlank("gun");
                    RemoveCharacterEquip(xi_refCharacter, itmGroup);
                }
                else
                    EquipCharacterByItem(xi_refCharacter, itmRef.id);
            }

			RefreshItemsTable();
			FillItemsSelected();
			SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "EQUIP_BUTTON", 0, "#" + XI_ConvertString("Equip that"));
			SetSelectable("EQUIP_BUTTON", ThisItemCanBeEquip(&Items[iGoodIndex]));
		}
	}
}

void ExitMapWindow()
{
	XI_WindowShow("MAP_WINDOW", false);
	XI_WindowDisable("MAP_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_ITEMS");
}

void ShowMapWindow()
{
	XI_WindowShow("MAP_WINDOW", true);
	XI_WindowDisable("MAP_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MAP_TEXT");
}

void ExitReadWindow()
{
	XI_WindowShow("READ_WINDOW", false);
	XI_WindowDisable("READ_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_ITEMS");
	SetNodeUsing("READ_SCROLL", false);
	SetNodeUsing("TITLE", true);
}

void ShowReadWindow()
{
	XI_WindowShow("READ_WINDOW", true);
	XI_WindowDisable("READ_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("READ_TEXT");
	SetNodeUsing("READ_SCROLL", true);
	SetNodeUsing("TITLE", false);
}

void SetReadScrollerPos()
{
	string nodName = GetEventData();
	float pos = GetEventData();
	SendMessage(&GameInterface,"lsf",MSG_INTERFACE_SET_SCROLLER,"READ_SCROLL",pos);
}

void SetAmmoBlank(string sType)
{
	SetAmmoBlink("SLOT_AMMO_" + sType, false);
	SetAmmoBlink("SLOT_POWDER_" + sType, false);
	SetNewGroupPicture("SLOT_AMMO_" + sType, "BLANK", "BLANK");
	SetNewGroupPicture("SLOT_POWDER_" + sType, "BLANK", "BLANK");
}

// > Индикация слота боеприпаса: при отсутствии заряда слот мигает красным
void SetAmmoBlink(string sNode, bool bBlink)
{
	int iBlink = 0;
	if (bBlink) iBlink = 1;

	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 5, iBlink);

	// > движок при выключении мигания оставляет слоту blindMinColor (красный), поэтому нейтральный цвет нужно вернуть ручками
	if (iBlink == 0)
		SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNode, 4, argb(255, 128, 128, 128));
}

// обработка нажатия клавы
void ProcessInterfaceControls()
{
	string controlName = GetEventData();

	if (controlName == "InterfaceGoLeft")
	{
		IDoExit(RC_INTERFACE_TO_ALCHEMY);
	}
	if (controlName == "InterfaceGoRight")
	{
		IDoExit(INTERFACE_NATIONRELATION);
	}
	if (controlName == "CharacterShipMenu")
	{
		IDoExit(RC_INTERFACE_TO_SHIP);
	}
	if (controlName == "LogbookMenu")
	{
		IDoExit(RC_INTERFACE_TO_LOGBOOK);
	}
	if (controlName == "NationsMenu")
	{
		IDoExit(INTERFACE_NATIONRELATION);
	}
	if (controlName == "AlchemyKey")
	{
		IDoExit(RC_INTERFACE_TO_ALCHEMY);
	}
	if (controlName == "Interface")
	{
		IDoExit(INTERFACE_CHARACTER_ALL);
	}
}

void OnHeaderClick()
{
	string sControl = GetEventData();
	int iColumn = GetEventData();

	if (sControl == "TABLE_ITEMS") SortItemsTable(iColumn, false, sControl);
}

void SortItemsTable(int column, bool preserveState, string tableName)
{
	string datatype = "float";
	switch (column)
	{
		case 1: datatype = "string"; break;
		case 3: datatype = "integer"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 0);
}

void ExitMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", false);
	XI_WindowDisable("MSG_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_ITEMS");
}

void ShowMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", true);
	XI_WindowDisable("MSG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MSG_OK");
}

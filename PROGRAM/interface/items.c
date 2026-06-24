// BOAL меню предметов
#include "interface\character_all.h"

#event_handler("Control Activation", "ProcessInterfaceControls"); // обработка нажатия клавы

string sPrevChar = "";
string sPrevNode = "";

void InitInterface(string iniName)
{
    InterfaceStack.SelectMenu_node = "LaunchItems"; // запоминаем, что звать по Ф2

	xi_refCharacter = pchar;

	FillCharactersScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

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

	XI_RegistryExitKey("IExit_F4");
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
	if (sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		SetButtonsState();
		return;
	}
}

void SetButtonsState()
{
	string attributeName = "pic" + (nCurScrollNum + 1);
	sPrevChar = xi_refCharacter.id;

	if (GameInterface.CHARACTERS_SCROLL.(attributeName).character != "0")
	{
		xi_refCharacter = &characters[sti(GameInterface.CHARACTERS_SCROLL.(attributeName).character)];
		FillItemsTable(1);
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
	int n, i;
	string row, sGood, groupID, itemType, sCurNode = GetCurrentNode();
	bool ok1, ok2, ok3, ok4, ok5;
	aref rootItems, arItem;
	aref curItem;

    string sGun, sMus, sBulletGun, sBulletMus;
    ref rGun, rMus; 
    sGun = GetCharacterEquipByGroup(xi_refCharacter, GUN_ITEM_TYPE);
    sBulletGun = LAi_GetCharacterBulletType(xi_refCharacter, GUN_ITEM_TYPE);
    if (sGun != "") rGun = ItemsFromID(sGun);
    sMus = GetCharacterEquipByGroup(xi_refCharacter, MUSKET_ITEM_TYPE);
    sBulletMus = LAi_GetCharacterBulletType(xi_refCharacter, MUSKET_ITEM_TYPE);
    if (sMus != "") rMus = ItemsFromID(sMus);

	GameInterface.TABLE_ITEMS.hr.td1.str = XI_ConvertString("ItemsColonTitle");
	GameInterface.TABLE_ITEMS.hr.td1.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td2.str = XI_ConvertString("weight") + " " + XI_ConvertString("pcs");
	GameInterface.TABLE_ITEMS.hr.td2.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td3.str = XI_ConvertString("QuantityShort");
	GameInterface.TABLE_ITEMS.hr.td3.scale = 0.8;
	GameInterface.TABLE_ITEMS.hr.td4.str = XI_ConvertString("weight");
	GameInterface.TABLE_ITEMS.hr.td4.scale = 0.8;
	GameInterface.TABLE_ITEMS.select = 0;
	GameInterface.TABLE_ITEMS.top = 0;
	n = 1;
	Table_Clear("TABLE_ITEMS", false, true, false);

	// Заполним вещами от нас
	makearef(rootItems, xi_refCharacter.Items);
    for (i=0; i < GetAttributesNum(rootItems); i++)
    {
		curItem = GetAttributeN(rootItems, i);
		groupID = "";
		itemType = "";

		if (Items_FindItem(GetAttributeName(curItem), &arItem) >= 0)
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
					CheckAttribute(&arItem, "mapType"))	// карты сокровищ
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
				if (sCurNode == "SLOT_GUN" && groupID != GUN_ITEM_TYPE) continue;
				if (sCurNode == "SLOT_MUSKET" && groupID != MUSKET_ITEM_TYPE) continue;
			}

			if(_mode == -3 && groupID != SPYGLASS_ITEM_TYPE) continue;
			if(_mode == -4 && groupID != CIRASS_ITEM_TYPE) continue;
			if(_mode == -5 && groupID != AMMO_ITEM_TYPE) continue;
			if(_mode ==  1 && groupID == MAPS_ITEM_TYPE && !GetCharacterFreeItem(xi_refCharacter, sGood) && arItem.id != "MapsAtlas") continue;
			if(_mode == 2 && !ok1) continue;
			if(_mode == 3 && !ok2) continue;
			if(_mode == 4 && !ok3) continue;
			if(_mode == 5 && !ok4) continue;

			if (GetCharacterItem(xi_refCharacter, sGood) > 0)
			{
				GameInterface.TABLE_ITEMS.(row).index = FindItem(arItem.id);

				GameInterface.TABLE_ITEMS.(row).td1.icon.group = arItem.picTexture;
				GameInterface.TABLE_ITEMS.(row).td1.icon.image = "itm" + arItem.picIndex;
				GameInterface.TABLE_ITEMS.(row).td1.icon.offset = "0, 1";
				GameInterface.TABLE_ITEMS.(row).td1.icon.width = 31;
				GameInterface.TABLE_ITEMS.(row).td1.icon.height = 31;
				GameInterface.TABLE_ITEMS.(row).td1.textoffset = "31,0";
				GameInterface.TABLE_ITEMS.(row).td1.str = GetConvertStr(arItem.name, "ItemsDescribe.txt");
				GameInterface.TABLE_ITEMS.(row).td1.scale = 0.85;

				GameInterface.TABLE_ITEMS.(row).td1.color = argb(255, 255, 255, 255);

				if (IsEquipCharacterByItem(xi_refCharacter, sGood))
					ok5 = true;
				else if (groupID == AMMO_ITEM_TYPE)
				{
					if (sGun != "" && sBulletGun != "")
					{
                        if (sGood == sBulletGun || sGood == GetGunAmmoAttr(rGun, sBulletGun, "gunpowder"))
                            ok5 = true; // Пуля или пороховые приблуды пистолета
                    }
                    if (!ok5 && sMus != "" && sBulletMus != "")
                    {
                        // Если не пуля/приблуда пистолета, то мб мушкета?
                        if (sGood == sBulletMus || sGood == GetGunAmmoAttr(rMus, sBulletMus, "gunpowder"))
                            ok5 = true;
                    }
				}

				if (ok5)
					GameInterface.TABLE_ITEMS.(row).td1.color = argb(255, 245, 230, 191);

				GameInterface.TABLE_ITEMS.(row).td2.str   = FloatToString(stf(arItem.Weight), 1);
				GameInterface.TABLE_ITEMS.(row).td2.scale = 0.9;
				GameInterface.TABLE_ITEMS.(row).td3.str   = GetCharacterItem(xi_refCharacter, sGood);
				GameInterface.TABLE_ITEMS.(row).td3.scale = 0.9;
				GameInterface.TABLE_ITEMS.(row).td4.str   = FloatToString(stf(arItem.Weight) * sti(GameInterface.TABLE_ITEMS.(row).td3.str), 1);
				GameInterface.TABLE_ITEMS.(row).td4.scale = 0.9;
				n++;
			}
		}
    }
    
	Table_UpdateWindow("TABLE_ITEMS");
	if (_mode == 1)
	{
		FillItemsSelected();
	}
}

void ClickToBlade()     {FillItemsTable(-1); ClickToItem(BLADE_ITEM_TYPE);}
void ClickToGun()       {FillItemsTable(-2); ClickToItem(GUN_ITEM_TYPE);}
void ClickToMusket()    {FillItemsTable(-2); ClickToItem(MUSKET_ITEM_TYPE);}
void ClickToSpyGlass()  {FillItemsTable(-3); ClickToItem(SPYGLASS_ITEM_TYPE);}
void ClickToCirass()    {FillItemsTable(-4); ClickToItem(CIRASS_ITEM_TYPE);}
void ClickToAmmo()      {FillItemsTable(-5); ClickToItem(AMMO_ITEM_TYPE);}

void ClickToItem(string sEquipType)
{
	sPrevNode = GetCurrentNode();

	if (!CheckAttribute(xi_refCharacter, "equip." + sEquipType) || xi_refCharacter.equip.(sEquipType) == "")
	{
		HideItemInfo();
		return;
	}

	string sTemp, row, sCurItem = GetCharacterEquipByGroup(xi_refCharacter, sEquipType);
    if (sCurItem == "unarmed")
    {
		HideItemInfo();
		return;
    }
	for (int q = 1; q < 1000; q++)
	{
		row = "tr" + q;
		if (!CheckAttribute(&GameInterface, "TABLE_ITEMS." + row)) break; // Кончились строки таблицы, конец цикла

		if (FindItem(sCurItem) == sti(GameInterface.TABLE_ITEMS.(row).index))
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
    SetNewGroupPicture("SLOT_" + sGunType, rItem.picTexture, "itm" + rItem.picIndex);
    SetNodeUsing("SLOT_" + sGunType, true);
    string sBullet = LAi_GetCharacterBulletType(xi_refCharacter, sGunType);
    if (sBullet != "")
    {
        ref rAmmo = ItemsFromID(sBullet);
        SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "SLOT_AMMO_" + sGunType, 5, GetCharacterItem(xi_refCharacter, rAmmo.id) < 1);
        SetNewGroupPicture("SLOT_AMMO_" + sGunType, rAmmo.picTexture, "itm" + rAmmo.picIndex);

        string sTemp = GetGunAmmoAttr(rItem, sBullet, "gunpowder");
        if (sTemp != "")
        {
            rAmmo = ItemsFromID(sTemp);
            SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "SLOT_POWDER_" + sGunType, 5, GetCharacterItem(xi_refCharacter, rAmmo.id) < 1);
            SetNewGroupPicture("SLOT_POWDER_" + sGunType, rAmmo.picTexture, "itm" + rAmmo.picIndex);
        }
    }
}

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
		/*case "CHARACTER_NATION_PICTURE":
		    sHeader = XI_ConvertString("Nation");
			sText1 = GetRPGText("Nation_hint");
		break;   */

		case "WEIGHT":
			sHeader = XI_ConvertString("Weight");
			sText1 = GetRPGText("Weight_hint");
		break;

		case "MONEY":
			sHeader = XI_ConvertString("Money");
			sText1 = GetRPGText("Money_hint");
		break;
	}
	sHeader = XI_ConvertString("buttonItems");
	sText1  = XI_ConvertString("ItemsHelper_1") + XI_ConvertString("ItemsHelper_2") + XI_ConvertString("ItemsHelper_3");
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
	int iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
	string sID = "";
	if (bBettaTestMode) sID = "  ID: " +Items[iGoodIndex].id;
	SetFormatedText("INFO_TEXT", GetItemDescribe(iGoodIndex) +sID);

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

void HideItemInfo()
{
	SetNodeUsing("INFO_TEXT", false);
	SetNodeUsing("INFO_PIC", false);
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"EQUIP_BUTTON",0, "#"+XI_ConvertString("Equip that"));
	SetSelectable("EQUIP_BUTTON",false);
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode("TABLE_ITEMS");
	HideItemInfo();
	switch (sNodName)
	{
		case "TABBTN_1": SetControlsTabMode(1);	break;
		case "TABBTN_2": SetControlsTabMode(2);	break;
		case "TABBTN_3": SetControlsTabMode(3);	break;
		case "TABBTN_4": SetControlsTabMode(4);	break;
		case "TABBTN_5": SetControlsTabMode(5);	break;
	}
	return;
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
		if (and(StrStartsWith(arItem.id, "recipe_"), CheckAttribute(&arItem, "result") && isMultiObjectKnown(arItem.result)) || and(CheckAttribute(arItem, "blockRead") && arItem.blockRead == "1", true)) //если прочитано, то читать больше не даем
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
		if (groupID == CIRASS_ITEM_TYPE && !IsCharacterPerkOn(xi_refCharacter,"Ciras") && arItem.Clothes == false)
	    {
		    return false;
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
	sPrevChar = "";
	int  iGoodIndex = sti(GameInterface.(CurTable).(CurRow).index);
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
            SetFormatedText("INFO_TEXT", GetItemDescribe(iGoodIndex));
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
            //pchar.I_MAP_SHOW = true;
            //pchar.I_MAP_SHOW_ITEM = itmRef.id;
            //PostEvent("InterfaceBreak", 400);
            if (itmRef.id == "map_full" || itmRef.id == "map_part1" || itmRef.id == "map_part2")
            {// клады
            	SetNewPicture("MAP_PICTURE", "interfaces\Maps\treasure map.tga");
            	if (GetCharacterItem(pchar, "map_part1")>0  && GetCharacterItem(pchar, "map_part2")>0)
			    {
			        TakeNItems(xi_refCharacter, "map_part1", -1);
			        TakeNItems(xi_refCharacter, "map_part2", -1);
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
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "SLOT_AMMO_" + sType, 4, argb(255, 128, 128, 128));
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "SLOT_POWDER_" + sType, 4, argb(255, 128, 128, 128));
	SetNewGroupPicture("SLOT_AMMO_" + sType, "BLANK", "BLANK");
	SetNewGroupPicture("SLOT_POWDER_" + sType, "BLANK", "BLANK");
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
	if (controlName == "IExit_F2")
	{
		IDoExit(RC_INTERFACE_TO_SHIP);
	}
	if (controlName == "IExit_F3")
	{
		IDoExit(RC_INTERFACE_TO_LOGBOOK);
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
	if (controlName == "IExit_F1")
	{
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
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

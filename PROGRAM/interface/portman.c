// BOAL Портовое управление

int nCurScrollNum;
ref xi_refCharacter;
ref refNPCPortman;
ref refWarehouse;
int shipIndex;

int nCurScrollOfficerNum;

string CurTable, CurRow;
int iSelected, dSelected, iSalaryRequirement; // курсор в таблице

string sMessageMode, sFrom_sea, sShipId, sTemp;
string CrewState = "Fire";
string GoodState = "Store";
int nShipStock = 3;

bool bShipyardOnTop, bEmptySlot;
bool bAllInclusive = false; // > флаг Юстино

void InitInterface_R(string iniName, ref _portman)
{
	GameInterface.title = "titlePortman";

	xi_refCharacter = pchar;

	refNPCPortman = _portman;

	bAllInclusive = CheckAttribute(refNPCPortman, "id") && refNPCPortman.id == "Secret_Fort_Commander";

	if (CheckAttribute(refNPCPortman, "storeShipsNum")) nShipStock = sti(refNPCPortman.storeShipsNum);

	ref rColony;
	sFrom_sea = "";
	if (bAllInclusive)
	{
		GameInterface.title = "UnknownFortName";
		sFrom_sea = "Shore_ship2";
		nShipStock = 5;
	}
	else if (CheckAttribute(refNPCPortman, "City") && FindColony(refNPCPortman.City) >= 0)
	{
		rColony = GetColonyByIndex(FindColony(refNPCPortman.City));
		sFrom_sea = rColony.from_sea;
	}

	FillShipsScroll();

	GameInterface.StatusLine.LOYALITY.Max = 1;
	GameInterface.StatusLine.LOYALITY.Min = 0;
	GameInterface.StatusLine.LOYALITY.Value = 0;

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);

	SetEventHandler("InterfaceBreak", "ProcessExitCancel", 0);
	SetEventHandler("exitCancel", "ProcessExitCancel", 0);
	SetEventHandler("ievnt_command", "ProcessCommandExecute", 0);
	SetEventHandler("frame", "ProcessFrame", 1);
	SetEventHandler("ShowInfoWindow", "ShowInfoWindow", 0);
	SetEventHandler("MouseRClickUp", "HideInfoWindow", 0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);
	SetEventHandler("ShowOtherClick", "ShowOtherClick", 0);
	SetEventHandler("CanonsRemoveAll", "CanonsRemoveAll", 0);
	SetEventHandler("ExitCannonsMenu", "ExitCannonsMenu", 0);
	SetEventHandler("ExitOfficerMenu", "ExitOfficerMenu", 0);
	SetEventHandler("acceptaddofficer", "AcceptAddOfficer", 0);
	SetEventHandler("GetShipEvent", "GetShipEvent", 0);
	SetEventHandler("CheckButtonChange", "procCheckBoxChange", 0);
	SetEventHandler("GoToShipChange", "GoToShipChange", 0);
	SetEventHandler("ShipChange", "ShipChange", 0);
	SetEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu", 0);

	SetEventHandler("AcceptSalaryRequirement", "AcceptSalaryRequirement", 0);
	SetEventHandler("DeclineSalaryRequirement", "DeclineSalaryRequirement", 0);
	SetEventHandler("CancelSalaryRequirement", "CancelSalaryRequirement", 0);
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);
	//////////////////
	EI_CreateFrame("SHIP_BIG_PICTURE_BORDER", 156, 40, 366, 275); // tak from SHIP_BIG_PICTURE
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 161, 246, 361, 1, 4);
	EI_CreateFrame("SHIP_BIG_PICTURE_BORDER", 20, 46, 134, 161);
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8, 187, 147, 1, 4);
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8, 166, 147, 1, 4);

	SetNewGroupPicture("CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");

	SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");
	SetNewGroupPicture("Ship_PIC", "ICONS_CHAR", "Class");

	if (!CheckAttribute(refNPCPortman, "Portman")) refNPCPortman.Portman = 0;

	SetFormatedText("Ship_TEXT", refNPCPortman.Portman + " / " + nShipStock);

	SetNodeUsing("BUTTON_DETAIL", false); //кнопка пока не используется, оставил на расширение функционала
	//не даем возможность оставлять корамбли в доке
	if (CheckAttribute(refNPCPortman, "dontGive")) SetNodeUsing("BUTTON_GIVE", false);

	FillPortManTable();

	SetCurrentNode("SHIPS_SCROLL");
	bShipyardOnTop = false;
	OnShipScrollChange();
	bEmptySlot = false;
	sMessageMode = "";
	SetButtionsAccess();
}

void ProcessExitCancel()
{
	if (sti(pchar.ship.type) == SHIP_NOTUSED) PChar.nation = GetBaseHeroNation();
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak", "ProcessExitCancel");
	DelEventHandler("exitCancel", "ProcessExitCancel");
	DelEventHandler("ievnt_command", "ProcessCommandExecute");
	DelEventHandler("frame", "ProcessFrame");
	DelEventHandler("ShowInfoWindow", "ShowInfoWindow");
	DelEventHandler("MouseRClickUp", "HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ExitMsgMenu", "ExitMsgMenu");
	DelEventHandler("ShowOtherClick", "ShowOtherClick");
	DelEventHandler("CanonsRemoveAll", "CanonsRemoveAll");
	DelEventHandler("ExitCannonsMenu", "ExitCannonsMenu");
	DelEventHandler("ExitOfficerMenu", "ExitOfficerMenu");
	DelEventHandler("acceptaddofficer", "AcceptAddOfficer");
	DelEventHandler("GetShipEvent", "GetShipEvent");
	DelEventHandler("CheckButtonChange", "procCheckBoxChange");
	DelEventHandler("GoToShipChange", "GoToShipChange");
	DelEventHandler("ShipChange", "ShipChange");
	DelEventHandler("ExitShipChangeMenu", "ExitShipChangeMenu");
	DelEventHandler("AcceptSalaryRequirement", "AcceptSalaryRequirement");
	DelEventHandler("DeclineSalaryRequirement", "DeclineSalaryRequirement");
	DelEventHandler("CancelSalaryRequirement", "CancelSalaryRequirement");
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

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch (nodName)
	{
		case "MSG_BIG_CREW_CHECKBOX":
			if (comName == "rclick")
			{
				string sCrewText1, sCrewText2, sCrewText3, sCrewPicture, sCrewGroup, sCrewGroupPicture;
				sCrewText2 = XI_ConvertString("MessageCrewCheckbox_1");
				sCrewText3 = XI_ConvertString("MessageCrewCheckbox_2");
				sCrewText1 = XI_ConvertString("MessageCrewCheckbox_3");
				sCrewPicture = "none";
				CreateTooltip("#" + XI_ConvertString("MessageCrewCheckbox_4"), sCrewText1, argb(255, 255, 255, 255), sCrewText2, argb(255, 255, 255, 255), sCrewText3, argb(255, 255, 255, 255), "", argb(255, 255, 255, 255), sCrewPicture, sCrewGroup, sCrewGroupPicture, 256, 256);
			}
		break;

		case "MSG_BIG_GOOD_CHECKBOX":
			if (comName == "rclick")
			{
				string sGoodText1, sGoodText2, sGoodText3, sGoodPicture, sGoodGroup, sGoodGroupPicture;
				sGoodText1 = XI_ConvertString("MessageGoodCheckbox_1");
				sGoodText2 = XI_ConvertString("MessageGoodCheckbox_2");
				sGoodText3 = XI_ConvertString("MessageGoodCheckbox_3");
				sGoodPicture = "none";
				CreateTooltip("#" + XI_ConvertString("MessageGoodCheckbox_4"), sGoodText1, argb(255, 255, 255, 255), sGoodText2, argb(255, 255, 255, 255), sGoodText3, argb(255, 255, 255, 255), "", argb(255, 255, 255, 255), sGoodPicture, sGoodGroup, sGoodGroupPicture, 256, 256);
			}
		break;

		case "BUTTON_GIVE":
			if (comName == "click" || comName == "activate")
			{
				ShowMessageInfo();
			}
		break;

		case "BUTTON_PICKUP":
			if (comName == "click" || comName == "activate")
			{
				ShowMessageInfo();
			}
		break;

		case "MSG_OK":
			if (comName == "click" || comName == "activate")
			{
				MessageOk();
			}
		break;

		case "MSG_BIG_OK":
			if (comName == "click" || comName == "activate")
			{
				MessageOk();
			}
		break;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////
void FillShipsScroll()
{
	DeleteAttribute(&GameInterface, "SHIPS_SCROLL");
	nCurScrollNum = -1;
	if (!CheckAttribute(&GameInterface, "SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}

	string attributeName;
	string shipName;
	int iShipType, cn;
	GameInterface.SHIPS_SCROLL.ImagesGroup.t0 = "BLANK_SHIP2";

	FillShipList("SHIPS_SCROLL.ImagesGroup", xi_refCharacter);
	GameInterface.SHIPS_SCROLL.BadTex1 = 0;
	GameInterface.SHIPS_SCROLL.BadPic1 = "Not Used2";

	int m = 0;
	for (int i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if (cn != -1)
		{
			iShipType = sti(characters[cn].ship.type);
			if (iShipType != SHIP_NOTUSED)
			{
				attributeName = "pic" + (m + 1);
				iShipType = sti(RealShips[iShipType].basetype);
				shipName = ShipsTypes[iShipType].Name;

				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#" + XI_ConvertString("ShipClass") + " " + ShipsTypes[iShipType].Class;
				GameInterface.SHIPS_SCROLL.(attributeName).str4 = shipName;
				GameInterface.SHIPS_SCROLL.(attributeName).str3 = "#" + MakeMoneyShow(GetPortManPriceExt(refNPCPortman, &characters[cn]), MONEY_SIGN, MONEY_DELIVER);
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "ship";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("SHIPS_SCROLL.ImagesGroup", "SHIPS_" + shipName);
				m++;
			}
			else
			{
				attributeName = "pic" + (m + 1);
				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#";
				GameInterface.SHIPS_SCROLL.(attributeName).str2 = "NoneBoat";
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "Not Used2";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = "BLANK_SHIP2";
				m++;
			}
		}
	}

	GameInterface.SHIPS_SCROLL.ListSize = m;
	GameInterface.SHIPS_SCROLL.NotUsed = COMPANION_MAX - m + 1;
}

void ProcessFrame()
{
	string attributeName;
	int iCharacter;

	string sNode = GetCurrentNode();

	if (sNode == "PASSENGERSLIST" && sti(GameInterface.PASSENGERSLIST.current) != nCurScrollOfficerNum)
	{
		nCurScrollOfficerNum = sti(GameInterface.PASSENGERSLIST.current);
		SetOfficersSkills();
	}
	if (sNode == "SHIPS_SCROLL")
	{
		if (sti(GameInterface.SHIPS_SCROLL.current) != nCurScrollNum || CurTable != "")
		{
			CurTable = "";
			NullSelectTable("TABLE_PORTMAN"); // убрать скрол
			bShipyardOnTop = false;

			nCurScrollNum = sti(GameInterface.SHIPS_SCROLL.current);

			attributeName = "pic" + (nCurScrollNum + 1);

			iCharacter = sti(GameInterface.SHIPS_SCROLL.(attributeName).character);

			if (iCharacter > 0)
			{
				string sChrId = characters[iCharacter].id;

				xi_refCharacter = characterFromID(sChrId);
				bEmptySlot = false;
				shipIndex = nCurScrollNum + 1;
				if (shipIndex < 0)
				{
					shipIndex = 0;
				}
				if (sti(xi_refCharacter.ship.type) == SHIP_NOTUSED)
				{
					shipIndex = -1;
				}
				// boal оптимизация скилов -->
				DelBakSkillAttr(xi_refCharacter);
				ClearCharacterExpRate(xi_refCharacter);
				RefreshCharacterSkillExpRate(xi_refCharacter);

				SetEnergyToCharacter(xi_refCharacter);
				// boal оптимизация скилов <--
				OnShipScrollChange();
			}
			else
			{
				shipIndex = -1;
				bEmptySlot = true;
			}
			SetButtionsAccess();
		}
	}
}

void FillShipParam(ref _chr)
{
	int iShip = sti(_chr.ship.type);
	if (iShip != SHIP_NOTUSED)
	{
		if (CheckAttribute(_chr, "Ship.Cargo.RecalculateCargoLoad") && sti(_chr.Ship.Cargo.RecalculateCargoLoad))
		{
			RecalculateCargoLoad(_chr);
			_chr.Ship.Cargo.RecalculateCargoLoad = 0;
		}
		ref refBaseShip = GetRealShip(iShip);
		string sShip = refBaseShip.BaseName;
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\ships\" + sShip + ".tga");

		GameInterface.edit_box.str = _chr.ship.name;
		SetFormatedText("SHIP_RANK", refBaseShip.Class);
		SetShipOTHERTable("TABLE_OTHER", _chr);
		SetFormatedText("FRAME_INFO_CAPTION", XI_ConvertString(sShip));
		SetFormatedText("INFO_TEXT", GetConvertStr(sShip, "ShipsDescribe.txt"));
	}
	else
	{
		SetNewPicture("SHIP_BIG_PICTURE", "interfaces\blank_ship2.tga");
		GameInterface.edit_box.str = XI_Convertstring("NoneBoat");
		SetFormatedText("FRAME_INFO_CAPTION", "");
		SetFormatedText("INFO_TEXT", "");
	}
	Table_UpdateWindow("TABLE_OTHER");
}

void OnShipScrollChange()
{
	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\256\face_" + xi_refCharacter.FaceId + ".tga");
	SetFormatedText("HERO_NAME", GetFullNameTitulForm(xi_refCharacter));
	SetFormatedText("HERO_RANK", xi_refCharacter.Rank);
	// нулим все формы, тк корабля может не быть
	SetFormatedText("SHIP_RANK", "");
	SetFormatedText("CREW_QTY", "");
	SetFormatedText("CREW_MORALE_TEXT", "");
	SetFormatedText("FOOD", "");
	SetFormatedText("FOOD_SHIP", "");
	SetFormatedText("RUM_SHIP", "");
	SetFormatedText("RUM", "");
	SetFormatedText("MONEY_SHIP", "");
	Table_Clear("TABLE_OTHER", false, true, false);
	Table_Clear("TABLE_CREW", false, true, false);
	SetNewGroupPicture("CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(1));
	//Ship info window
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN, MONEY_DELIVER));
	FillShipParam(xi_refCharacter);
	RecalculateCrewBlock(xi_refCharacter);

	// теперь это Лояльность
	GameInterface.StatusLine.LOYALITY.Max = MAX_LOYALITY;
	GameInterface.StatusLine.LOYALITY.Min = 0;
	GameInterface.StatusLine.LOYALITY.Value = GetCharacterLoyality(xi_refCharacter);

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "LOYALITY", 0);

}

void RecalculateCrewBlock(ref _chr)
{
	//бар матросов
	int iShip = sti(_chr.ship.type);
	if (iShip != SHIP_NOTUSED)
	{
		// еда и ром -->
		int iColor, iFood, iRum;
		string sText;
		// в эскадре
		if (GetCompanionQuantity(pchar) > 1) // больше 1 ГГ
		{
			sText = XI_ConvertString("Provisions_on_squadron") + " " + XI_ConvertString("ForShip") + " ";
			iFood = CalculateFood();
			sText = sText + FindDaysString(iFood);
			SetFormatedText("FOOD", sText);
			if (iFood >= 5)
			{
				iColor = argb(255, 255, 255, 192);
			}
			if (iFood > 10)
			{
				iColor = argb(255, 192, 255, 192);
			}
			if (iFood < 5)
			{
				iColor = argb(255, 255, 192, 192);
			}
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "FOOD", 8, -1, iColor);

			sText = XI_ConvertString("Rum_on_squadron") + " " + XI_ConvertString("OnShip") + " ";
			iRum = CalculateRum();
			sText = sText + FindDaysString(iRum);
			SetFormatedText("RUM", sText);
			if (iRum >= 5)
			{
				iColor = argb(255, 255, 255, 192);
			}
			if (iRum > 10)
			{
				iColor = argb(255, 192, 255, 192);
			}
			if (iRum < 5)
			{
				iColor = argb(255, 255, 192, 192);
			}
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "RUM", 8, -1, iColor);

		}
		// на одном корабле
		SetFoodShipInfo(_chr, "FOOD_SHIP");
		SetRumShipInfo(_chr, "RUM_SHIP");
		// еда и ром <--

		if (GetRemovable(_chr)) // считаем только своих, а то вских сопровождаемых кормить!!!
		{
			// для каждого корабля учитываем класс и считаем отдельно
			SetFormatedText("MONEY_SHIP", XI_ConvertString("Pay_for_ship") + " " + NewStr() + FindMoneyString(GetSalaryForShip(_chr)));
		}

		SetFormatedText("CREW_QTY", "" + GetCrewQuantity(_chr));
		if (GetCrewQuantity(_chr) > GetOptCrewQuantity(_chr) || GetCrewQuantity(_chr) < GetMinCrewQuantity(_chr))
		{
			iColor = argb(255, 255, 64, 64);
		}
		else
		{
			iColor = argb(255, 255, 255, 255);
		}
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CREW_QTY", 8, -1, iColor);
		SetNewGroupPicture("CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(stf(_chr.ship.crew.morale)));
		SetFormatedText("CREW_MORALE_TEXT", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(sti(_chr.Ship.crew.morale))));
		if (sti(_chr.Ship.crew.morale) < MORALE_MAX && GetCrewQuantity(_chr) > 0)
		{
			SetSelectable("CREW_MORALE_BUTTON", true);
		}
		SetNodeUsing("BAR_Sailors", true);
		SetNodeUsing("BAR_Cannoners", true);
		SetNodeUsing("BAR_Soldiers", true);
		SetNodeUsing("BAR_CrewMoral", true);

		SetCrewExpTable(_chr, "TABLE_CREW", "BAR_Sailors", "BAR_Cannoners", "BAR_Soldiers");

		//BAR_CrewMoral
		GameInterface.StatusLine.BAR_CrewMoral.Max = 100;
		GameInterface.StatusLine.BAR_CrewMoral.Min = 0;
		GameInterface.StatusLine.BAR_CrewMoral.Value = sti(_chr.Ship.crew.morale);
		SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "BAR_CrewMoral", 0);
	}
	else
	{
		SetNodeUsing("BAR_Sailors", false);
		SetNodeUsing("BAR_Cannoners", false);
		SetNodeUsing("BAR_Soldiers", false);
		SetNodeUsing("BAR_CrewMoral", false);
	}
	Table_UpdateWindow("TABLE_CREW");
}

void ShipChange()
{
	bool bOk;
	if (xi_refCharacter.id != pchar.id && sti(pchar.ship.type) != SHIP_NOTUSED)
	{
		SetFormatedText("REMOVE_WINDOW_CAPTION", XI_ConvertString("companionship"));
		SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChangeMsg_1"));
		SetSelectable("REMOVE_ACCEPT_OFFICER", true);
		bOk = !bSeaActive && LAi_grp_alarmactive;
		if (!GetRemovable(xi_refCharacter))
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChangeMsg_2"));
			SetSelectable("REMOVE_ACCEPT_OFFICER", false);
		}
		if (sti(pchar.ship.type) == SHIP_NOTUSED)
		{
			SetFormatedText("REMOVE_WINDOW_TEXT", XI_ConvertString("ShipChangeMsg_3"));
			SetSelectable("REMOVE_ACCEPT_OFFICER", false);
		}
		ShowShipChangeMenu();
	}
}

void ShowShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("REMOVE_CANCEL_OFFICER");
}

void ExitShipChangeMenu()
{
	XI_WindowShow("REMOVE_OFFICER_WINDOW", false);
	XI_WindowDisable("REMOVE_OFFICER_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
}

void GoToShipChange()
{
	pchar.TransferChar = xi_refCharacter.index;
	InterfaceStates.ReloadMenuExit = true;
	IDoExit(RC_INTERFACE_ANY_EXIT);
	PostEvent("LaunchIAfterFrame", 1, "sl", "TransferMain", 2);
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
	int iShip;
	ref refBaseShip;

	bool bShowHint = true;

	ref rChr;
	if (bShipyardOnTop)
	{
		rChr = refNPCPortman;
	}
	else
	{
		rChr = xi_refCharacter;
	}
	switch (sCurrentNode)
	{
		case "SHIP_BIG_PICTURE":
			if (shipIndex != -1 || bShipyardOnTop)
			{
				iShip = sti(rChr.ship.type);
				refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1 = GetConvertStr("NoneBoat2", "ShipsDescribe.txt");
			}
		break;

		case "SHIPS_SCROLL":
			if (shipIndex != -1)
			{
				iShip = sti(xi_refCharacter.ship.type);
				refBaseShip = GetRealShip(iShip);
				sHeader = XI_ConvertString(refBaseShip.BaseName);
				sText1 = GetConvertStr(refBaseShip.BaseName, "ShipsDescribe.txt");
				//sText2 = GetRPGText("shipChoose_hint");
			}
			else
			{
				sHeader = XI_Convertstring("NoneBoat");
				sText1 = GetConvertStr("NoneBoat2", "ShipsDescribe.txt");
			}
		break;

		case "MAIN_CHARACTER_PICTURE":
		// отдельная форма
			bShowHint = false;
			ShowRPGHint();
		break;

		case "LOYALITY_STR":
			sHeader = XI_ConvertString("Loyality");
			sText1 = GetRPGText("Loyality_hint");
		break;

		case "TABLE_OTHER":
			sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
			sText1 = GetConvertStr(GameInterface.(CurTable).(CurRow).UserData.ID, "ShipsDescribe.txt");
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType" && sti(rChr.Ship.Cannons.Type) != CANNON_TYPE_NONECANNON)
			{
				ref Cannon = GetCannonByType(sti(rChr.Ship.Cannons.Type));
				sText2 = XI_ConvertString("ShipTypeShort") + ": " + XI_ConvertString(GetCannonType(sti(rChr.Ship.Cannons.Type)));
				sText2 = sText2 + NewStr() + XI_ConvertString("Caliber") + ": " + XI_ConvertString("caliber" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type)));
				sText2 = sText2 + NewStr() + XI_ConvertString("Fire range2") + ": " + sti(Cannon.FireRange);
				sText2 = sText2 + NewStr() + XI_ConvertString("Damage") + ": x" + FloatToString(stf(Cannon.DamageMultiply), 1);
				sText2 = sText2 + NewStr() + XI_ConvertString("Reload time") + ": " + sti(GetCannonReloadTime(Cannon)) + " " + XI_ConvertString("sec");
				sText2 = sText2 + NewStr() + XI_ConvertString("weight") + ": " + sti(Cannon.Weight) + " " + XI_ConvertString("cwt") + ".";

				sGroup = "GOODS";
				sGroupPicture = GetCannonType(sti(rChr.Ship.Cannons.Type)) + "_" + GetCannonCaliber(sti(rChr.Ship.Cannons.Type));

				sText3 = XI_ConvertString("Caliber_text1");
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Crew" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText2 = XI_ConvertString("Max_crew_text1");
				sText2 = sText2 + NewStr() + XI_ConvertString("Max_crew_text2") + ": " + GetMaxCrewQuantity(rChr);
			}
			// процент ремонта
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Hull" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(rChr), 1) + " %";
			}
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Sails" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(rChr), 1) + " %";
			}
			// трюм
			if (GameInterface.(CurTable).(CurRow).UserData.ID == "Capacity" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = XI_ConvertString("Occupied") + ": " + FloatToString((stf(GetCargoLoad(rChr)) / stf(GetCargoMaxSpace(rChr))) * 100.0, 1) + " %";
			}
		break;
		case "TABLE_PORTMAN" :
			sHeader = XI_Convertstring("titlePortman");
			sText1 = GetConvertStr("Portman_hint", "ShipsDescribe.txt");
		break;
		case "TABLE_CREW":
			sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
			sText1 = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");
		break;
	}
	if (bShowHint)
	{
		CreateTooltip("#" + sHeader, sText1, argb(255, 255, 255, 255), sText2, argb(255, 255, 192, 192), sText3, argb(255, 192, 255, 192), "", argb(255, 255, 255, 255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void HideInfoWindow()
{
	CloseTooltip();
	ExitRPGHint();
}

void FillPortManShip(ref NPChar, string _sShipNum)
{
	aref arTo, arFrom;

	DeleteAttribute(NPChar, "ShipInDock");

	makearef(arFrom, NPChar.ShipInStockMan.(_sShipNum));
	NPChar.ShipInDock = "";
	makearef(arTo, NPChar.ShipInDock);
	CopyAttributes(arTo, arFrom);
}

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
	CurTable = sControl;
	CurRow = "tr" + (iSelected);
	NullSelectTable("TABLE_OTHER");
	NullSelectTable("TABLE_CREW");

	// заполнялка
	if (CurTable == "TABLE_PORTMAN")
	{
		dSelected = iSelected;
		FillPortManShip(refNPCPortman, GameInterface.(CurTable).(CurRow).sShipId);
		aref aShipInDock;
		makearef(aShipInDock, refNPCPortman.ShipInDock);
		FillShipParam(aShipInDock);
		RecalculateCrewBlock(aShipInDock);
		bShipyardOnTop = true;
		SetButtionsAccess();
	}
}

void ExitRPGHint()
{
	if (sMessageMode == "RPG_Hint")
	{
		XI_WindowShow("RPG_WINDOW", false);
		XI_WindowDisable("RPG_WINDOW", true);
		XI_WindowDisable("MAIN_WINDOW", false);
		sMessageMode = "";
	}
}

void ShowRPGHint()
{
	SetSPECIALMiniTable("RPG_TABLE_SMALLSKILL", xi_refCharacter);
	SetOTHERMiniTable("RPG_TABLE_SMALLOTHER", xi_refCharacter);
	SetFormatedText("RPG_OFFICER_NAME", GetFullNameTitulForm(xi_refCharacter));

	XI_WindowShow("RPG_WINDOW", true);
	XI_WindowDisable("RPG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
	sMessageMode = "RPG_Hint";
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
		GameInterface.(sControl).select = 0;
		Table_UpdateWindow(sControl);
	}
}

void ExitMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", false);
	XI_WindowShow("MSG_BIG_WINDOW", false);
	XI_WindowShow("MSG_WARNING_WINDOW", false);
	XI_WindowShow("SALARY_REQUIREMENT_WINDOW", false);
	XI_WindowDisable("MSG_WINDOW", true);
	XI_WindowDisable("MSG_BIG_WINDOW", true);
	XI_WindowDisable("MSG_WARNING_WINDOW", true);
	XI_WindowDisable("SALARY_REQUIREMENT_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	//Восстановление позиции в таблице кораблей
	SetCurrentNode("TABLE_PORTMAN");
	if (!bEmptySlot)
	{
		sMessageMode = "";
	}
}

void ShowMsgTakeMenu()
{
	if (GetCompanionQuantity(pchar) < COMPANION_MAX)
	{
		XI_WindowShow("MSG_WINDOW", true);
		XI_WindowDisable("MSG_WINDOW", false);
		SetNodeUsing("MSG_WINDOW_TAKE_TEXT", false);
	}
	else
	{
		XI_WindowShow("MSG_WARNING_WINDOW", true);
		XI_WindowDisable("MSG_WARNING_WINDOW", false);
		SetFormatedText("MSG_WARNING_WINDOW_CAPTION", XI_ConvertString("PortmanChangeToHeroTitle"));
		SetFormatedText("MSG_WARNING_WINDOW_TEXT", XI_ConvertString("PortmanChangeToHeroMsg"));
	}
	XI_WindowDisable("MAIN_WINDOW", true);
	SetCurrentNode("MSG_CANCEL");
}

void ShowMsgGiveMenu()
{
	if (and(!bAllInclusive, sti(refNPCPortman.Portman) >= 3) || and(bAllInclusive, sti(refNPCPortman.Portman) >= 5))
	{
		XI_WindowShow("MSG_WARNING_WINDOW", true);
		XI_WindowDisable("MSG_WARNING_WINDOW", false);
		SetFormatedText("MSG_WARNING_WINDOW_CAPTION", XI_ConvertString("PortmanChangeToDokTitle"));
		SetFormatedText("MSG_WARNING_WINDOW_TEXT", XI_ConvertString("PortmanChangeToDokMsg"));
		SetCurrentNode("MSG_WARNING_OK");
	}
	else
	{
		XI_WindowShow("MSG_BIG_WINDOW", true);
		XI_WindowDisable("MSG_BIG_WINDOW", false);
		SetFormatedText("MSG_BIG_GOOD_CHECKBOX_TEXT", XI_ConvertString("MessageGoodCheckbox_4"));
		SetFormatedText("MSG_BIG_CREW_CHECKBOX_TEXT", XI_ConvertString("MessageCrewCheckbox_4"));

		if (bAllInclusive)
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_GOOD_CHECKBOX", 5, 1, true);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_GOOD_CHECKBOX", 5, 2, true);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_GOOD_CHECKBOX", 5, 3, true);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 5, 1, true);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 5, 2, true);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 5, 3, true);
		}
		else
		{
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_GOOD_CHECKBOX", 2, 1, true);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 2, 1, true);
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_GOOD_CHECKBOX", 5, 3, true);

			if (CheckAttribute(refNPCPortman, "City") || refNPCPortman.id == "Secret_Fort_Commander")
			{
				if (refNPCPortman.id == "Secret_Fort_Commander")
					refWarehouse = refNPCPortman;
				else
					refWarehouse = CharacterFromID(refNPCPortman.City + "_GlavSklad");

				if (CheckAttribute(refWarehouse, "Storage.Activate") || refWarehouse.id == "Secret_Fort_Commander")
				{
					int iStorageUsed;
					if (refWarehouse.id == "Secret_Fort_Commander") iStorageUsed = SHIP_STORE;
					else iStorageUsed = GetStorage(refWarehouse.City);
					int cargoShip = GetCargoLoad(xi_refCharacter);
					int warehouseCargo = 50000 - GetStorageUsedWeight(&Stores[iStorageUsed]);

					if (cargoShip < warehouseCargo)
						SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_GOOD_CHECKBOX", 5, 3, false);
				}
			}
			if (GetCrewQuantity(xi_refCharacter) == 0)
			{
				SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 5, 1, true);
				SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 5, 2, true);
				SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 5, 3, true);
				SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 2, 1, true);
				CrewState = "NonState";
			}
			else
			{
				SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 5, 1, false);
				SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 5, 2, false);
				SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 5, 3, false);
				if (CrewState == "Fire") sMessageMode = "SalaryReq";
			}
			if (sti(xi_refCharacter.index) == GetMainCharacterIndex())
			{
				//отключить чекбокс погрузки товаров на флагман
				SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_GOOD_CHECKBOX", 5, 2, true);
				//отключить чекбоксы распределения команды по кораблям
				SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 5, 2, true);
				SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "MSG_BIG_CREW_CHECKBOX", 5, 3, true);
			}
		}
		SetCurrentNode("MSG_BIG_CANCEL");
	}
	XI_WindowDisable("MAIN_WINDOW", true);
}

void ShowOtherClick()
{
	if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType")
	{
		ShowCannonsMenu();
	}
}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if (sNodName == "MSG_BIG_CREW_CHECKBOX")
	{
		if (bBtnState == true)
		{
			switch (nBtnIndex)
			{
				case 1:
					CrewState = "Fire";
					sMessageMode = "SalaryReq";
				break;
				case 2:
					CrewState = "Max";
					sMessageMode = "GiveShip";
				break;
				case 3:
					CrewState = "Opt";
					sMessageMode = "GiveShip";
				break;
			}
		}
		return;
	}
	if (sNodName == "MSG_BIG_GOOD_CHECKBOX")
	{
		if (bBtnState == true)
		{
			switch (nBtnIndex)
			{
				case 1: GoodState = "Store";      break;
				case 2: GoodState = "Ship";       break;
				case 3: GoodState = "Warehouse";  break;
			}
		}
		return;
	}
}

void ShowCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", true);
	XI_WindowDisable("CANNONS_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("CANNONS_CANCEL");

	DeleteAttribute(&GameInterface, "CANNONS_TABLE.BackUp");
	CannonsMenuRefresh();
}

void CanonsRemoveAll()
{
	SetCannonsToBort(xi_refCharacter, "fcannon", 0);
	SetCannonsToBort(xi_refCharacter, "bcannon", 0);
	SetCannonsToBort(xi_refCharacter, "rcannon", 0);
	SetCannonsToBort(xi_refCharacter, "lcannon", 0);

	OnShipScrollChange();
	CannonsMenuRefresh();
}

/// установить орудия по борту (сперва расчитать дельту было стало - лишнее в запасы)
void SetCannonsToBort(ref chr, string sBort, int iQty)
{
	int curQty = GetBortCannonsQty(chr, sBort);
	int maxQty = GetBortCannonsMaxQty(chr, sBort);
	int i, delta;
	string attr;
	int center, left, right; // счетчики орудий для распределения
	bool bLeft; // направление хода
	string sBort_real;

	if (sBort == "rcannon") sBort_real = "cannonr";
	if (sBort == "lcannon") sBort_real = "cannonl";
	if (sBort == "fcannon") sBort_real = "cannonf";
	if (sBort == "bcannon") sBort_real = "cannonb";

	if (iQty > maxQty) iQty = maxQty;
	if (iQty < 0) iQty = 0;

	int idx = GetCannonGoodsIdxByType(sti(chr.Ship.Cannons.Type));
	delta = iQty - curQty;
	if (delta > 0)
	{
		if (GetCargoGoods(chr, idx) < delta) iQty = curQty + GetCargoGoods(chr, idx);
	}
	if (iQty > curQty)
	{
		// списать со склада
		RemoveCharacterGoodsSelf(chr, idx, (iQty - curQty));
	}
	else
	{
		if (iQty < curQty)
		{
			// лишние на склад
			SetCharacterGoods(chr, idx, GetCargoGoods(chr, idx) + (curQty - iQty)); // этот метод, тк перегруз может быть, а  AddCharacterGoodsSimple режет перегруз
		}
	}
	// нулим колво пушек на борту и распределяем заново от центра (как они на модели по номерам не знаю, допуск, что подряд)
	for (i = 0; i < maxQty; i++)
	{
		attr = "c" + i;
		chr.Ship.Cannons.borts.(sBort).damages.(attr) = 1.0; // поломана на 100%, не палит, те нет её
		chr.Ship.Cannons.borts.(sBort_real).damages.(attr) = 1.0; // поломана на 100%, не палит, те нет её
	}
	// распределяем
	if (iQty > 0)
	{
		center = makeint(maxQty / 2); // целочисленное деление
		left = center - 1;
		right = center;
		i = 0; // сколько распределили уже
		bLeft = true;
		while (i < iQty)
		{
			if (bLeft)
			{
				if (left >= 0)
				{
					attr = "c" + left;
					left--;
				}
				else
				{
					attr = "c" + right;
					right++;
				}
				if (right < maxQty) bLeft = false;
			}
			else
			{
				if (right < maxQty)
				{
					attr = "c" + right;
					right++;
				}
				else
				{
					attr = "c" + left;
					left--;
				}
				if (left >= 0) bLeft = true;
			}
			chr.Ship.Cannons.borts.(sBort).damages.(attr) = 0.0; // новая, не битая
			chr.Ship.Cannons.borts.(sBort_real).damages.(attr) = 0.0; // новая, не битая
			i++;
		}
	}
	RecalculateCargoLoad(chr);  // пересчет, тк пушки снялись
}

void CannonsMenuRefresh()
{
	ref rChr;
	if (bShipyardOnTop)
	{
		rChr = refNPCPortman;
	}
	else
	{
		rChr = xi_refCharacter;
	}
	int idx = GetCannonGoodsIdxByType(sti(rChr.Ship.Cannons.Type));
	if (idx != -1)
	{
		SetNewGroupPicture("CANNONS_PIC", "GOODS", Goods[idx].Name);
		SetFormatedText("CANNONS_TEXT", XI_ConvertString(Goods[idx].Name));
		SetFormatedText("CANNONS_QTY_F", its(GetBortCannonsQty(rChr, "fcannon")));
		SetFormatedText("CANNONS_QTY_B", its(GetBortCannonsQty(rChr, "bcannon")));
		SetFormatedText("CANNONS_QTY_R", its(GetBortCannonsQty(rChr, "rcannon")));
		SetFormatedText("CANNONS_QTY_L", its(GetBortCannonsQty(rChr, "lcannon")));

		/// всего GetCannonsNum(xi_refCharacter)
	}
	else
	{
		SetNewGroupPicture("CANNONS_PIC", "GOODS", "");
		SetFormatedText("CANNONS_TEXT", "");
		SetFormatedText("CANNONS_QTY_F", "0");
		SetFormatedText("CANNONS_QTY_B", "0");
		SetFormatedText("CANNONS_QTY_R", "0");
		SetFormatedText("CANNONS_QTY_L", "0");
	}
}

void ExitCannonsMenu()
{
	HideCannonsMenu();
}

void HideCannonsMenu()
{
	XI_WindowShow("CANNONS_WINDOW", false);
	XI_WindowDisable("CANNONS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
	sMessageMode = "";
}

void FillPortManTable()
{
	Table_Clear("TABLE_PORTMAN", false, true, false);

	GameInterface.TABLE_PORTMAN.hr.td1.str = XI_ConvertString("Ship");
	GameInterface.TABLE_PORTMAN.hr.td1.scale = 0.9;
	GameInterface.TABLE_PORTMAN.hr.td2.str = XI_ConvertString("ShipClass");
	GameInterface.TABLE_PORTMAN.hr.td2.scale = 0.9;
	GameInterface.TABLE_PORTMAN.hr.td3.str = XI_ConvertString("PortmanMonthlyFee");
	GameInterface.TABLE_PORTMAN.hr.td3.scale = 0.9;
	GameInterface.TABLE_PORTMAN.hr.td4.str = XI_ConvertString("PortmanRefundFee");
	GameInterface.TABLE_PORTMAN.hr.td4.scale = 0.9;
	GameInterface.TABLE_PORTMAN.select = 0;
	GameInterface.TABLE_PORTMAN.top = 0;

	aref arDest, arImt;
	string sAttr;
	int iNum, i, iShip;
	ref refBaseShip;
	string sShip;
	string row;

	makearef(arDest, refNPCPortman.ShipInStockMan);
	iNum = GetAttributesNum(arDest);
	for (i = 0; i < iNum; i++)
	{
		row = "tr" + (i + 1);

		arImt = GetAttributeN(arDest, i);
		sAttr = GetAttributeName(arImt);
		FillPortManShip(refNPCPortman, sAttr); // скинуть в стандарт корабль из ШипХХ

		iShip = sti(arImt.Ship.Type);
		refBaseShip = GetRealShip(iShip);
		sShip = refBaseShip.BaseName;

		int iPay = GetNpcQuestPastMonthParam(arImt, "Date") * sti(arImt.MoneyForShip);
		if (iPay <= 1) iPay = 0;

		GameInterface.TABLE_PORTMAN.(row).sShipId = sAttr;
		GameInterface.TABLE_PORTMAN.(row).td1.icon.texture = "interfaces\ships\" + sShip + ".tga";
		GameInterface.TABLE_PORTMAN.(row).td1.icon.uv = "0,0,1,1";
		GameInterface.TABLE_PORTMAN.(row).td1.icon.width = 46;
		GameInterface.TABLE_PORTMAN.(row).td1.icon.height = 46;
		GameInterface.TABLE_PORTMAN.(row).td1.icon.offset = "0, 1";
		GameInterface.TABLE_PORTMAN.(row).td1.textoffset = "53,0";
		GameInterface.TABLE_PORTMAN.(row).td1.str = XI_Convertstring(sShip) + "\n\n" + arImt.ship.name;
		GameInterface.TABLE_PORTMAN.(row).td1.align = "left";
		GameInterface.TABLE_PORTMAN.(row).td1.scale = 0.82;
		GameInterface.TABLE_PORTMAN.(row).td2.str = refBaseShip.Class;
		GameInterface.TABLE_PORTMAN.(row).td3.str = arImt.MoneyForShip;
		GameInterface.TABLE_PORTMAN.(row).td3.color = argb(255, 255, 228, 80);
		GameInterface.TABLE_PORTMAN.(row).td4.str = iPay;
		GameInterface.TABLE_PORTMAN.(row).td4.color = argb(255, 255, 228, 80);
	}
	Table_UpdateWindow("TABLE_PORTMAN");
}

void SetButtionsAccess()
{
	SetSelectable("BUTTON_DETAIL", false);
	SetSelectable("BUTTON_GIVE", true);
	SetSelectable("BUTTON_PICKUP", true);
	int iMoney = 0;

	if (bShipyardOnTop)
	{
		SetSelectable("BUTTON_DETAIL", false);
		SetSelectable("BUTTON_GIVE", false);
		if (CheckAttribute(refNPCPortman, "ShipInDock"))
			iMoney = GetNpcQuestPastMonthParam(refNPCPortman, "ShipInDock.Date") * sti(refNPCPortman.ShipInDock.MoneyForShip);

		if (shipIndex == -1)// проверка на цену
		{
			if (iMoney > sti(pchar.Money))
			{
				SetSelectable("BUTTON_PICKUP", false);
			}
			if (bEmptySlot && sti(pchar.ship.type) == SHIP_NOTUSED)
			{
				// нельзя купить корабль компаньону, если у ГГ нету
				SetSelectable("BUTTON_PICKUP", false);
			}
		}
		else
		{
			if (iMoney > sti(pchar.Money) && !bAllInclusive)
			{
				SetSelectable("BUTTON_PICKUP", false);
			}
			if (!GetRemovable(xi_refCharacter) || !GetShipRemovable(xi_refCharacter))
			{
				SetSelectable("BUTTON_PICKUP", false);
			}
		}
	}
	else
	{
		SetSelectable("BUTTON_PICKUP", false);
		if (sti(xi_refCharacter.ship.type) != SHIP_NOTUSED) iMoney = GetPortManPriceExt(refNPCPortman, xi_refCharacter);
		if (sti(pchar.Money) < iMoney && !bAllInclusive)
		{
			SetSelectable("BUTTON_GIVE", false);
		}
		if (GetHullPercent(xi_refCharacter) < 100 || GetSailPercent(xi_refCharacter) < 100)
		{
			SetSelectable("BUTTON_DETAIL", true);
		}
		if (shipIndex == -1)
		{
			SetSelectable("BUTTON_GIVE", false);
			SetSelectable("BUTTON_DETAIL", false);
		}
		else
		{
			if (!GetRemovable(xi_refCharacter) || !GetShipRemovable(xi_refCharacter))
			{
				SetSelectable("BUTTON_GIVE", false);
			}
			if (xi_refCharacter.id == pchar.id && GetCompanionQuantity(pchar) > 1)
			{
				// нельзя продать корабль ГГ, если есть ещё компаньоны
				SetSelectable("BUTTON_GIVE", false);
			}
		}
	}

	if (GetGlobalTutor())
	{
		SetSelectable("BUTTON_PICKUP", false);

		if (xi_refCharacter.id == pchar.id)
		{
			SetSelectable("BUTTON_GIVE", false);
		}
	}
}

//////////////// назначение капитана  //////////////////////////////////////////////////////////////////////
void ShipChangeCaptan()
{
	FillPassengerScroll();
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, "PASSENGERSLIST", -1);
	SetCurrentNode("PASSENGERSLIST");
	ProcessFrame();
	SetOfficersSkills();

	XI_WindowShow("OFFICERS_WINDOW", true);
	XI_WindowDisable("OFFICERS_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);
}

void ExitOfficerMenu()
{
	XI_WindowShow("OFFICERS_WINDOW", false);
	XI_WindowDisable("OFFICERS_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	//Восстановление позиции в таблице кораблей верфи
	SetCurrentNode("TABLE_PORTMAN");
	sMessageMode = "";
}

void AcceptAddOfficer()
{
	string attributeName2 = "pic" + (nCurScrollOfficerNum + 1);
	ref sld;

	if (CheckAttribute(&GameInterface, "PASSENGERSLIST." + attributeName2 + ".character"))
	{
		int iChar = sti(GameInterface.PASSENGERSLIST.(attributeName2).character);
		// назначение нового кэпа, возможно, если там уже не наш, те или враг или снят
		sld = GetCharacter(iChar);
		DeleteAttribute(sld, "ship");
		sld.ship.Type = SHIP_NOTUSED;

		// снимем пассажира -->
		CheckForReleaseOfficer(iChar);
		RemovePassenger(pchar, sld);
		// снимем пассажира <--
		SetCompanionIndex(pchar, -1, iChar);

		xi_refCharacter = sld;
		DoTakeShip();
	}
	ExitOfficerMenu();
}

void FillPassengerScroll()
{
	int i, howWork;
	string faceName;
	string attributeName;
	int _curCharIdx;
	ref _refCurChar;
	bool ok;

	DeleteAttribute(&GameInterface, "PASSENGERSLIST");

	nCurScrollOfficerNum = -1;
	GameInterface.PASSENGERSLIST.current = 0;

	int nListSize = GetPassengersQuantity(pchar);
	int nListSizeFree = nListSize;

	GameInterface.PASSENGERSLIST.NotUsed = 6;
	GameInterface.PASSENGERSLIST.ListSize = nListSizeFree + 2;

	GameInterface.PASSENGERSLIST.ImagesGroup.t0 = "EMPTYFACE";

	FillFaceList("PASSENGERSLIST.ImagesGroup", pchar, 2); // passengers

	GameInterface.PASSENGERSLIST.BadTex1 = 0;
	GameInterface.PASSENGERSLIST.BadPic1 = "emptyface";

	int m = 0;

	if (sti(pchar.ship.type) == SHIP_NOTUSED)
	{
		attributeName = "pic" + (m + 1);
		GameInterface.PASSENGERSLIST.(attributeName).character = pchar.index;
		GameInterface.PASSENGERSLIST.(attributeName).img1 = GetFacePicName(pchar);
		GameInterface.PASSENGERSLIST.(attributeName).tex1 = FindFaceGroupNum("PASSENGERSLIST.ImagesGroup", "FACE128_" + pchar.FaceID);
		m++;
	}

	for (i = 0; i < nListSize; i++)
	{
		attributeName = "pic" + (m + 1);
		_curCharIdx = GetPassenger(pchar, i);

		if (_curCharIdx != -1)
		{
			ok = CheckAttribute(&characters[_curCharIdx], "prisoned") && sti(characters[_curCharIdx].prisoned) == true;
			if (!ok && !CheckAttribute(&characters[_curCharIdx], "CompanionDisable") && GetRemovable(&characters[_curCharIdx]))
			{
				GameInterface.PASSENGERSLIST.(attributeName).character = _curCharIdx;
				GameInterface.PASSENGERSLIST.(attributeName).img1 = GetFacePicName(GetCharacter(_curCharIdx));
				GameInterface.PASSENGERSLIST.(attributeName).tex1 = FindFaceGroupNum("PASSENGERSLIST.ImagesGroup", "FACE128_" + Characters[_curCharIdx].FaceID);
				m++;
			}
		}
	}
	GameInterface.PASSENGERSLIST.ListSize = m + 2; // не знаю зачем, но для совместимости с "было"
}
// рефреш скилов офа и ГГ, если офа сняли для компаньона
void DelBakSkill()
{
	DelBakSkillAttr(xi_refCharacter);
	ClearCharacterExpRate(xi_refCharacter);
	RefreshCharacterSkillExpRate(xi_refCharacter);
	SetEnergyToCharacter(xi_refCharacter);

	DelBakSkillAttr(pchar);
	ClearCharacterExpRate(pchar);
	RefreshCharacterSkillExpRate(pchar);
	SetEnergyToCharacter(pchar);
}

void ShowMessageInfo()
{
	int iMoney;
	string add = "";

	if (bShipyardOnTop) // забрать
	{
		SetFormatedText("MSG_WINDOW_CAPTION", XI_ConvertString("Ship"));
		iMoney = GetNpcQuestPastMonthParam(refNPCPortman, "ShipInDock.Date") * sti(refNPCPortman.ShipInDock.MoneyForShip);
		if (iMoney > 1)
			SetFormatedText("MSG_WINDOW_TEXT", XI_ConvertString("PortmanMessageInfo_1") + " '" + refNPCPortman.ShipInDock.Ship.Name + "' " + XI_ConvertString("PortmanMessageInfo_2") + " " + FindMoneyString(abs(iMoney)) + XI_ConvertString("PortmanMessageInfo_3"));
		else
			SetFormatedText("MSG_WINDOW_TEXT", XI_ConvertString("PortmanMessageInfo_1") + " '" + refNPCPortman.ShipInDock.Ship.Name + "'?");
		sMessageMode = "ShipTake";
		ShowMsgTakeMenu();
	}
	else  // отдать
	{
		SetFormatedText("MSG_BIG_WINDOW_CAPTION", XI_ConvertString("Ship"));
		iMoney = GetPortManPriceExt(refNPCPortman, xi_refCharacter);
		if (bAllInclusive)
			SetFormatedText("MSG_BIG_WINDOW_TEXT", XI_ConvertString("PortmanMessageInfo_4") + " '" + xi_refCharacter.Ship.Name + "' " + XI_ConvertString("PortmanMessageInfo_51") + "?\n" + ColorTextLine(XI_ConvertString("PortmanMessageInfo_15"), "contra") + "\n" + ColorTextLine(XI_ConvertString("PortmanMessageInfo_16"), "export"));
		else
			SetFormatedText("MSG_BIG_WINDOW_TEXT", XI_ConvertString("PortmanMessageInfo_4") + " '" + xi_refCharacter.Ship.Name + "' " + XI_ConvertString("PortmanMessageInfo_5") + " " + FindMoneyString(iMoney) + " " + XI_ConvertString("per month") + "?");
		sMessageMode = "GiveShip";
		ShowMsgGiveMenu();
	}
}

void MessageOk()
{
	switch (sMessageMode)
	{
		case "GiveShip" :
			DoGiveShip();
			ExitMsgMenu();
		break;

		case "SalaryReq" :
			ShowSalaryReqMenu();
		break;

		case "ShipTake" :
			DoTakeShipMain();
		break;
	}
}

void ShowSalaryReqMenu()
{
	iSalaryRequirement = GetSalaryForCrewMonthlyPay(xi_refCharacter, GetCrewQuantity(xi_refCharacter));
	string sSalaryForCrew = XI_ConvertString("CrewRebel_1") + NewStr() + XI_ConvertString("CrewRebel_2") + FindMoneyString(iSalaryRequirement) + ".";

	SetFormatedText("SALARY_REQUIREMENT_CAPTION", XI_ConvertString("CrewRebel_3"));
	SetFormatedText("SALARY_REQUIREMENT_WINDOW_TEXT", sSalaryForCrew);

	XI_WindowShow("SALARY_REQUIREMENT_WINDOW", true);
	XI_WindowDisable("SALARY_REQUIREMENT_WINDOW", false);

	XI_WindowShow("MSG_BIG_WINDOW", false);
	XI_WindowDisable("MSG_BIG_WINDOW", true);

	SetNodeUsing("SALARY_REQUIREMENT_ACCEPT", true);
	SetNodeUsing("SALARY_REQUIREMENT_CANCEL", true);

	if (sti(pchar.money) < iSalaryRequirement + GetPortManPriceExt(refNPCPortman, xi_refCharacter))
	{
		SetSelectable("SALARY_REQUIREMENT_ACCEPT", false);
	}

	SetCurrentNode("SALARY_REQUIREMENT_CANCEL");
}

void AcceptSalaryRequirement()
{
	AddMoneyToCharacter(pchar, -iSalaryRequirement);
	DoGiveShip();
	ExitMsgMenu();
}

void DeclineSalaryRequirement()
{
	if (!CheckAttribute(pchar, "CrewPayment")) pchar.CrewPayment = iSalaryRequirement;
	else pchar.CrewPayment = sti(pchar.CrewPayment) + iSalaryRequirement;
	DoGiveShip();
	ExitMsgMenu();
}

void CancelSalaryRequirement()
{
	XI_WindowShow("SALARY_REQUIREMENT_WINDOW", false);
	XI_WindowDisable("SALARY_REQUIREMENT_WINDOW", true);

	XI_WindowShow("MSG_BIG_WINDOW", true);
	XI_WindowDisable("MSG_BIG_WINDOW", false);

	SetCurrentNode("MSG_BIG_CANCEL");
}

void DoGiveShip()
{
	ref chref = xi_refCharacter;
	if (shipIndex != -1 && sti(chref.ship.type) != SHIP_NOTUSED)
	{
		aref aCopyToPortMan, aCopyFromCaptain;

		int dockPrice = GetPortManPriceExt(refNPCPortman, chref);
		if (bAllInclusive) dockPrice = 0;
		int iTime = 30;

		if (CrewState == "Max") SendCrewToPchar(chref);
		if (CrewState == "Opt") SendOptCrewToPchar(chref);
		if (CrewState == "Fire") FireCrew(chref);

		if (GoodState == "Store") SellGoods(chref);
		if (GoodState == "Ship") MoveGoodsToPchar(chref);
		if (GoodState == "Warehouse") SendGoodsToWarehouse(chref);
		SetCrewQuantity(chref, 0);

		refNPCPortman.MoneyForShip = dockPrice;
		int iFullPrice = iSalaryRequirement + dockPrice;
		AddMoneyToCharacter(pchar, -dockPrice);

		if (GetOfficersPerkUsing(chref, "QuickCalculation", false)) iTime /= 2;
		WaitDate("", 0, 0, 0, 0, iTime);

		/////////////////////////////////////////////////////////////
		sTemp = refNPCPortman.id + refNPCPortman.MoneyForShip + "_" + chref.ship.type;
		RealShips[sti(chref.ship.type)].StoreShip = true;
		makearef(aCopyToPortMan, refNPCPortman.ShipInStockMan.(sTemp).ship);
		makearef(aCopyFromCaptain, chref.ship);
		CopyAttributes(aCopyToPortMan, aCopyFromCaptain);
		refNPCPortman.ShipInStockMan.(sTemp).MoneyForShip = refNPCPortman.MoneyForShip;
		refNPCPortman.ShipInStockMan.(sTemp).AltDate = GetQuestBookDataDigit(); // для печати

		// для расчёта
		sTemp = "ShipInStockMan." + sTemp + ".Date";
		SaveCurrentNpcQuestDateParam(refNPCPortman, sTemp);
		refNPCPortman.Portman = sti(refNPCPortman.Portman) + 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) + 1;
		SetFormatedText("Ship_TEXT", refNPCPortman.Portman + " / " + nShipStock);

		// evganat - можно вставить отношение сюда
		if (!bAllInclusive && sti(refNPCPortman.Portman) == 1)
			IncreaseNPCDisposition(refNPCPortman, 1);
		/////////////////////////////////////////////////////////////////////////////////
		chref.ship.type = SHIP_NOTUSED;

		if (sti(chref.index) != GetMainCharacterIndex())
		{
			RemoveCharacterCompanion(pchar, chref);
			AddPassenger(pchar, chref, false);
			DelBakSkill();
		}
		else
		{
			pchar.location.from_sea = ""; // нет корабля в порту
		}
		RefreshShipLists();
	}
}

void MoveGoodsToPchar(ref chref)
{
	for (int iGoodIndex = 0; iGoodIndex < GOODS_QUANTITY; iGoodIndex++)
	{
		int ShipQ = GetCargoGoods(chref, iGoodIndex);
		if (ShipQ <= 0) continue;
		if ((sti(chref.index) != GetMainCharacterIndex())) AddCharacterGoods(pchar, iGoodIndex, ShipQ);
		RemoveCharacterGoods(chref, iGoodIndex, ShipQ);
	}
}

void SellGoods(ref chref)
{
	if (bAllInclusive) return;
	aref refGoods;
	ref Colony = GetColonyByIndex(FindColony(refNPCPortman.City));
	ref trader = &stores[sti(Colony.StoreNum)];
	int moneyback = 0;
	for (int iGoodIndex = 0; iGoodIndex < GOODS_QUANTITY; iGoodIndex++)
	{
		int ShipQ = GetCargoGoods(chref, iGoodIndex);
		if (ShipQ <= 0) continue;
		string goodname = Goods[iGoodIndex].Name;
		makearef(refGoods, trader.Goods.(goodname));
		if (sti(refGoods.TradeType) == TRADE_TYPE_CONTRABAND)
		{
			if ((sti(chref.index) != GetMainCharacterIndex())) AddCharacterGoods(pchar, iGoodIndex, ShipQ);
			RemoveCharacterGoods(chref, iGoodIndex, ShipQ);
			continue;
		}
		int iUnits = Goods[iGoodIndex].Units;
		int iStoreQty = GetStoreGoodsQuantity(trader, iGoodIndex);
		int iStorePrice = GetStoreGoodsPrice(trader, iGoodIndex, PRICE_TYPE_SELL, pchar, 1);
		RemoveCharacterGoods(chref, iGoodIndex, ShipQ);
		SetStoreGoods(trader, iGoodIndex, iStoreQty + ShipQ);
		moneyback += makeint(iStorePrice * ShipQ / iUnits + 0.5);
	}
	if (moneyback > 0) log_info(XI_ConvertString("PortmanMessageInfo_6"));
	AddMoneyToCharacter(pchar, moneyback);

	AddCharacterExpToSkill(pchar, "Commerce", moneyback / (2600.0 - sti(GetCharacterSPECIALSimple(pchar, SPECIAL_I)) * sti(GetCharacterSPECIALSimple(pchar, SPECIAL_C)) * 10));
}

void RefreshShipLists()
{
	xi_refCharacter = pchar;
	FillShipsScroll();
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, "SHIPS_SCROLL", -1);
	SetCurrentNode("SHIPS_SCROLL");
	ProcessFrame();

	FillPortManTable();
	bShipyardOnTop = false;
}

void DoTakeShip()
{
	aref arTo, arFrom;

	DeleteAttribute(refNPCPortman, "BakCargo");
	DeleteAttribute(refNPCPortman, "BakCrew");

	int iTime = 30;
	if (GetOfficersPerkUsing(pchar, "QuickCalculation", false)) iTime /= 2;
	WaitDate("", 0, 0, 0, 0, iTime);

	FillPortManShip(refNPCPortman, sShipId);
	int iPay = GetNpcQuestPastMonthParam(refNPCPortman, "ShipInDock.Date") * sti(refNPCPortman.ShipInDock.MoneyForShip);
	if (iPay > 1) AddMoneyToCharacter(pchar, -iPay);

	makearef(arTo, xi_refCharacter.ship);
	makearef(arFrom, refNPCPortman.ShipInDock.Ship);
	CopyAttributes(arTo, arFrom);

	DeleteAttribute(refNPCPortman, "ShipInStockMan." + sShipId);
	refNPCPortman.Portman = sti(refNPCPortman.Portman) - 1;
	pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
	SetFormatedText("Ship_TEXT", refNPCPortman.Portman + " / " + nShipStock);

	// evganat - можно вставить отношение сюда
	if (sti(refNPCPortman.Portman) == 0)
		IncreaseNPCDisposition(refNPCPortman, -1);

	if (sti(xi_refCharacter.index) == GetMainCharacterIndex())
	{
		pchar.location.from_sea = sFrom_sea; // корабль в порту
	}

	DeleteAttribute(&RealShips[sti(xi_refCharacter.ship.type)], "StoreShip");

	DelBakSkill();
	RefreshShipLists();
}

void DoTakeShipMain()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".sShipId"))
	{
		sShipId = GameInterface.(CurTable).(CurRow).sShipId;

		ExitMsgMenu();
		ShipChangeCaptan();
	}
}

void GetShipEvent()
{
	if (GetSelectable("BUTTON_PICKUP"))
	{
		ShowMessageInfo();
	}
}

void FireCrew(ref chref)
{
	if (bAllInclusive) return;
	int crewn = GetCrewQuantity(chref);
	ref refTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
	float fTemp3 = stf(GetCrewQuantity(refTown) + crewn);
	refTown.Ship.Crew.Exp.Sailors = (stf(refTown.Ship.Crew.Exp.Sailors) * GetCrewQuantity(refTown) +
			stf(chref.Ship.Crew.Exp.Sailors) * crewn) / fTemp3;
	refTown.Ship.Crew.Exp.Cannoners = (stf(refTown.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(refTown) +
			stf(chref.Ship.Crew.Exp.Cannoners) * crewn) / fTemp3;
	refTown.Ship.Crew.Exp.Soldiers = (stf(refTown.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(refTown) +
			stf(chref.Ship.Crew.Exp.Soldiers) * crewn) / fTemp3;
	refTown.Ship.Crew.Morale = (stf(refTown.Ship.Crew.Morale) * GetCrewQuantity(refTown) +
			stf(chref.Ship.Crew.Morale) * crewn) / fTemp3;
	refTown.Ship.Crew.Quantity = sti(refTown.Ship.Crew.Quantity) + crewn;
	Log_Info(XI_ConvertString("PortmanMessageInfo_7"));
}

void SendOptCrewToPchar(ref chref)
{
	int i, cn;
	ref chreff;
	if (GetCrewQuantity(pchar) < GetOptCrewQuantity(pchar))
	{
		int crewn = GetOptCrewQuantity(pchar) - GetCrewQuantity(pchar);
		float fTemp = stf(GetOptCrewQuantity(pchar));
		float fTemp2 = stf(GetCrewQuantity(pchar) + GetCrewQuantity(chref));

		if (GetCrewQuantity(chref) > crewn)
		{
			pchar.Ship.Crew.Exp.Sailors = (stf(pchar.Ship.Crew.Exp.Sailors) * GetCrewQuantity(pchar) +
					stf(chref.Ship.Crew.Exp.Sailors) * crewn) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners = (stf(pchar.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(pchar) +
					stf(chref.Ship.Crew.Exp.Cannoners) * crewn) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers = (stf(pchar.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(pchar) +
					stf(chref.Ship.Crew.Exp.Soldiers) * crewn) / fTemp;
			pchar.Ship.Crew.morale = (stf(pchar.Ship.Crew.morale) * GetCrewQuantity(pchar) +
					stf(chref.Ship.Crew.morale) * crewn) / fTemp;

			SetCrewQuantity(pchar, GetOptCrewQuantity(pchar));
			Log_Info(XI_ConvertString("PortmanMessageInfo_8"));
			crewn = GetCrewQuantity(chref) - crewn;
			if (crewn > 0)
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if (cn > 0 && crewn > 0)
					{
						chreff = GetCharacter(cn);
						if (crewn != 0) crewn = SendOptCrewToShip(chref, chreff, crewn);
					}
				}
				if (crewn > 0) SendCrewToTavern(chref, crewn);
			}
		}
		else
		{
			if (fTemp2 != 0)//фикс - убираем из лога ошибки деления на ноль
			{
				pchar.Ship.Crew.Exp.Sailors = (stf(pchar.Ship.Crew.Exp.Sailors) * GetCrewQuantity(pchar) +
						stf(chref.Ship.Crew.Exp.Sailors) * GetCrewQuantity(chref)) / fTemp2;
				pchar.Ship.Crew.Exp.Cannoners = (stf(pchar.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(pchar) +
						stf(chref.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(chref)) / fTemp2;
				pchar.Ship.Crew.Exp.Soldiers = (stf(pchar.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(pchar) +
						stf(chref.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(chref)) / fTemp2;

				pchar.Ship.Crew.morale = (stf(pchar.Ship.Crew.morale) * GetCrewQuantity(pchar) +
						stf(chref.Ship.Crew.morale) * GetCrewQuantity(chref)) / fTemp2;
				SetCrewQuantity(pchar, GetCrewQuantity(pchar) + GetCrewQuantity(chref));
				Log_Info(XI_ConvertString("PortmanMessageInfo_9"));
			}
		}
	}
	else
	{
		int creww = GetCrewQuantity(chref);
		for (i = 1; i < COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(PChar, i);
			if (cn > 0 && creww > 0)
			{
				chreff = GetCharacter(cn);
				creww = SendOptCrewToShip(chref, chreff, creww);
			}
		}
		if (creww > 0) SendCrewToTavern(chref, creww);
	}
}

void SendCrewToPchar(ref chref)
{
	int i, cn;
	ref chreff;
	if (GetCrewQuantity(pchar) < GetMaxCrewQuantity(pchar))
	{
		int crewn = GetMaxCrewQuantity(pchar) - GetCrewQuantity(pchar);
		float fTemp = stf(GetMaxCrewQuantity(pchar));
		float fTemp2 = stf(GetCrewQuantity(pchar) + GetCrewQuantity(chref));

		if (GetCrewQuantity(chref) > crewn)
		{
			pchar.Ship.Crew.Exp.Sailors = (stf(pchar.Ship.Crew.Exp.Sailors) * GetCrewQuantity(pchar) +
					stf(chref.Ship.Crew.Exp.Sailors) * crewn) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners = (stf(pchar.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(pchar) +
					stf(chref.Ship.Crew.Exp.Cannoners) * crewn) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers = (stf(pchar.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(pchar) +
					stf(chref.Ship.Crew.Exp.Soldiers) * crewn) / fTemp;
			pchar.Ship.Crew.morale = (stf(pchar.Ship.Crew.morale) * GetCrewQuantity(pchar) +
					stf(chref.Ship.Crew.morale) * crewn) / fTemp;

			SetCrewQuantity(pchar, GetMaxCrewQuantity(pchar));
			Log_Info(XI_ConvertString("PortmanMessageInfo_8"));
			crewn = GetCrewQuantity(chref) - crewn;
			if (crewn > 0)
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);
					if (cn > 0 && crewn > 0)
					{
						chreff = GetCharacter(cn);
						if (crewn != 0) crewn = SendCrewToShip(chref, chreff, crewn);
					}
				}
				if (crewn > 0) SendCrewToTavern(chref, crewn);
			}
		}
		else
		{
			if (fTemp2 != 0)//фикс - убираем из лога ошибки деления на ноль
			{
				pchar.Ship.Crew.Exp.Sailors = (stf(pchar.Ship.Crew.Exp.Sailors) * GetCrewQuantity(pchar) +
						stf(chref.Ship.Crew.Exp.Sailors) * GetCrewQuantity(chref)) / fTemp2;
				pchar.Ship.Crew.Exp.Cannoners = (stf(pchar.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(pchar) +
						stf(chref.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(chref)) / fTemp2;
				pchar.Ship.Crew.Exp.Soldiers = (stf(pchar.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(pchar) +
						stf(chref.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(chref)) / fTemp2;

				pchar.Ship.Crew.morale = (stf(pchar.Ship.Crew.morale) * GetCrewQuantity(pchar) +
						stf(chref.Ship.Crew.morale) * GetCrewQuantity(chref)) / fTemp2;
				SetCrewQuantity(pchar, GetCrewQuantity(pchar) + GetCrewQuantity(chref));
				Log_Info(XI_ConvertString("PortmanMessageInfo_9"));
			}
		}
	}
	else
	{
		int creww = GetCrewQuantity(chref);
		for (i = 1; i < COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(PChar, i);
			if (cn > 0 && creww > 0)
			{
				chreff = GetCharacter(cn);
				creww = SendCrewToShip(chref, chreff, creww);
			}
		}
		if (creww > 0) SendCrewToTavern(chref, creww);
	}
}

int SendCrewToShip(ref chref, ref chreff, int crewnum)
{
	int crewn = GetMaxCrewQuantity(chreff) - GetCrewQuantity(chreff);
	if (crewn == 0) return crewnum;
	float fTemp = stf(GetMaxCrewQuantity(chreff));
	float fTemp2 = stf(GetCrewQuantity(chreff) + crewnum);

	if (crewnum > crewn)
	{
		chreff.Ship.Crew.Exp.Sailors = (stf(chreff.Ship.Crew.Exp.Sailors) * GetCrewQuantity(chreff) +
				stf(chref.Ship.Crew.Exp.Sailors) * crewn) / fTemp;
		chreff.Ship.Crew.Exp.Cannoners = (stf(chreff.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(chreff) +
				stf(chref.Ship.Crew.Exp.Cannoners) * crewn) / fTemp;
		chreff.Ship.Crew.Exp.Soldiers = (stf(chreff.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(chreff) +
				stf(chref.Ship.Crew.Exp.Soldiers) * crewn) / fTemp;
		chreff.Ship.Crew.morale = (stf(chreff.Ship.Crew.morale) * GetCrewQuantity(chreff) +
				stf(chref.Ship.Crew.morale) * crewn) / fTemp;

		SetCrewQuantity(chreff, GetMaxCrewQuantity(chreff));
		Log_Info(XI_ConvertString("PortmanMessageInfo_10") + chreff.name + " " + chreff.lastname + ".");
		crewn = crewnum - crewn;
	}
	else
	{
		if (fTemp2 != 0)//фикс - убираем из лога ошибки деления на ноль
		{
			chreff.Ship.Crew.Exp.Sailors = (stf(chreff.Ship.Crew.Exp.Sailors) * GetCrewQuantity(chreff) +
					stf(chref.Ship.Crew.Exp.Sailors) * crewnum) / fTemp2;
			chreff.Ship.Crew.Exp.Cannoners = (stf(chreff.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(chreff) +
					stf(chref.Ship.Crew.Exp.Cannoners) * crewnum) / fTemp2;
			chreff.Ship.Crew.Exp.Soldiers = (stf(chreff.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(chreff) +
					stf(chref.Ship.Crew.Exp.Soldiers) * crewnum) / fTemp2;

			chreff.Ship.Crew.morale = (stf(chreff.Ship.Crew.morale) * GetCrewQuantity(chreff) +
					stf(chref.Ship.Crew.morale) * crewnum) / fTemp2;
			SetCrewQuantity(chreff, GetCrewQuantity(chreff) + crewnum);
			Log_Info(XI_ConvertString("PortmanMessageInfo_11") + chreff.name + " " + chreff.lastname + ".");
			crewn = 0;
		}
	}
	return crewn;
}

void SendCrewToTavern(ref chref, int crewn)
{
	if (bAllInclusive) return;
	ref refTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
	float fTemp3 = stf(GetCrewQuantity(refTown) + crewn);
	refTown.Ship.Crew.Exp.Sailors = (stf(refTown.Ship.Crew.Exp.Sailors) * GetCrewQuantity(refTown) +
			stf(chref.Ship.Crew.Exp.Sailors) * crewn) / fTemp3;
	refTown.Ship.Crew.Exp.Cannoners = (stf(refTown.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(refTown) +
			stf(chref.Ship.Crew.Exp.Cannoners) * crewn) / fTemp3;
	refTown.Ship.Crew.Exp.Soldiers = (stf(refTown.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(refTown) +
			stf(chref.Ship.Crew.Exp.Soldiers) * crewn) / fTemp3;
	refTown.Ship.Crew.Morale = (stf(refTown.Ship.Crew.Morale) * GetCrewQuantity(refTown) +
			stf(chref.Ship.Crew.Morale) * crewn) / fTemp3;
	refTown.Ship.Crew.Quantity = sti(refTown.Ship.Crew.Quantity) + crewn;
	Log_Info(XI_ConvertString("PortmanMessageInfo_7"));
}

int SendOptCrewToShip(ref chref, ref chreff, int crewnum)
{
	if (GetCrewQuantity(chreff) >= GetOptCrewQuantity(chreff)) return crewnum;
	int crewn = GetOptCrewQuantity(chreff) - GetCrewQuantity(chreff);
	if (crewn == 0) return crewnum;
	float fTemp = stf(GetOptCrewQuantity(chreff));
	float fTemp2 = stf(GetCrewQuantity(chreff) + crewnum);

	if (crewnum > crewn)
	{
		chreff.Ship.Crew.Exp.Sailors = (stf(chreff.Ship.Crew.Exp.Sailors) * GetCrewQuantity(chreff) +
				stf(chref.Ship.Crew.Exp.Sailors) * crewn) / fTemp;
		chreff.Ship.Crew.Exp.Cannoners = (stf(chreff.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(chreff) +
				stf(chref.Ship.Crew.Exp.Cannoners) * crewn) / fTemp;
		chreff.Ship.Crew.Exp.Soldiers = (stf(chreff.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(chreff) +
				stf(chref.Ship.Crew.Exp.Soldiers) * crewn) / fTemp;
		chreff.Ship.Crew.morale = (stf(chreff.Ship.Crew.morale) * GetCrewQuantity(chreff) +
				stf(chref.Ship.Crew.morale) * crewn) / fTemp;

		SetCrewQuantity(chreff, GetOptCrewQuantity(chreff));
		Log_Info(XI_ConvertString("PortmanMessageInfo_10") + chreff.name + " " + chreff.lastname + ".");
		crewn = crewnum - crewn;
	}
	else
	{
		if (fTemp2 != 0)//фикс - убираем из лога ошибки деления на ноль
		{
			chreff.Ship.Crew.Exp.Sailors = (stf(chreff.Ship.Crew.Exp.Sailors) * GetCrewQuantity(chreff) +
					stf(chref.Ship.Crew.Exp.Sailors) * crewnum) / fTemp2;
			chreff.Ship.Crew.Exp.Cannoners = (stf(chreff.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(chreff) +
					stf(chref.Ship.Crew.Exp.Cannoners) * crewnum) / fTemp2;
			chreff.Ship.Crew.Exp.Soldiers = (stf(chreff.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(chreff) +
					stf(chref.Ship.Crew.Exp.Soldiers) * crewnum) / fTemp2;

			chreff.Ship.Crew.morale = (stf(chreff.Ship.Crew.morale) * GetCrewQuantity(chreff) +
					stf(chref.Ship.Crew.morale) * crewnum) / fTemp2;
			SetCrewQuantity(chreff, GetCrewQuantity(chreff) + crewnum);
			Log_Info(XI_ConvertString("PortmanMessageInfo_11") + chreff.name + " " + chreff.lastname + ".");
			crewn = 0;
		}
	}
	return crewn;
}

void SendGoodsToWarehouse(ref chref)
{
	int iStorageUsed, iShipQ, iUnits, iStoreQty, iStorePrice;

	if (refWarehouse.id == "Secret_Fort_Commander") iStorageUsed = SHIP_STORE;
	else iStorageUsed = GetStorage(refWarehouse.City);

	for (int iGoodIndex = 0; iGoodIndex < GOODS_QUANTITY; iGoodIndex++)
	{
		iShipQ = GetCargoGoods(chref, iGoodIndex);
		if (iShipQ <= 0) continue;

		SetStorageGoods(&Stores[iStorageUsed], iGoodIndex, GetStorageGoodsQuantity(&Stores[iStorageUsed], iGoodIndex) + iShipQ);
		RemoveCharacterGoods(chref, iGoodIndex, iShipQ);
	}
}

void OnHeaderClick()
{
	string sControl = GetEventData();
	int iColumn = GetEventData();
	trace("sControl: " + sControl + " iColumn " + iColumn);

	if (sControl == "TABLE_PORTMAN") SortShipsList(iColumn, false, sControl);
}

void SortShipsList(int column, bool preserveState, string tableName)
{
	string datatype = "string";
	switch (column)
	{
		case 2: datatype = "integer"; break;
		case 3: datatype = "integer"; break;
		case 4: datatype = "integer"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 0);
}
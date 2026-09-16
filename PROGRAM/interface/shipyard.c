// BOAL Верфь

int nCurScrollNum;
ref xi_refCharacter;
ref refNPCShipyard;
int shipIndex;

int nCurScrollOfficerNum;

string CurTable, CurRow;
int iSelected, dSelected; // курсор в таблице

string sMessageMode, sFrom_sea, sShipId;

float shipCostRate;
bool bShipyardOnTop, bEmptySlot;

//HardCoffee для окна ремонта -->
int repairScrollNum, iTCost, iTTime;
object objSail;

bool bMastBatch = false;
// для окна ремонта <--

int idShipsDescr = -1;

string sTxCondition, sTxLimits, sTxRepairCost, sTxRepairTime;
string sTxNeedMoney, sTxNeedHull, sTxNeedMast;
string sTxCostTotal, sTxTimeTotal;

void RepairCacheStrings()
{
	sTxCondition  = XI_ConvertString("Condition");
	sTxLimits     = " " + XI_ConvertString("Limits");
	sTxRepairCost = XI_ConvertString("RepairCost");
	sTxRepairTime = XI_ConvertString("RepairTime");
	sTxNeedMoney  = "(" + XI_ConvertString("NeedMoney") + ")";
	sTxNeedHull   = "(" + XI_ConvertString("NeedHull") + ")";
	sTxNeedMast   = "(" + XI_ConvertString("NeedMast") + ")";
	sTxCostTotal  = XI_ConvertString("RepairCostT");
	sTxTimeTotal  = XI_ConvertString("RepairTimeT");
}

void InitInterface_R(string iniName, ref _shipyarder)
{
	GameInterface.title = "titleShipyard";

	xi_refCharacter = pchar;
	idShipsDescr = LanguageOpenFile("ShipsDescribe.txt");
	RepairCacheStrings();
	shipIndex = -1;

	refNPCShipyard = _shipyarder;
	SetShipyardStore(refNPCShipyard);

	shipCostRate = stf(refNPCShipyard.ShipCostRate);

	int iTest = FindColony(refNPCShipyard.City); // город магазина
	ref rColony;
	sFrom_sea = "";
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea; // ветка верфи, в сухопутных верфи нет, значит везде правильная
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
	SetEventHandler("confirmShipChangeName", "confirmShipChangeName", 0);
	SetEventHandler("CheckForRename", "CheckForRename", 0);
	SetEventHandler("ShowInfoWindow", "ShowInfoWindow", 0);
	SetEventHandler("MouseRClickUp", "HideInfoWindow", 0);
	SetEventHandler("TableSelectChange", "TableSelectChange", 0);
	SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);
	SetEventHandler("ExitRepairMenu", "ExitRepairMenu", 0);
	SetEventHandler("ShowOtherClick", "ShowOtherClick", 0);
	SetEventHandler("CanonsRemoveAll", "CanonsRemoveAll", 0);
	SetEventHandler("ExitCannonsMenu", "ExitCannonsMenu", 0);
	SetEventHandler("ExitOfficerMenu", "ExitOfficerMenu", 0);
	SetEventHandler("acceptaddofficer", "AcceptAddOfficer", 0);
	SetEventHandler("BuyShipEvent", "BuyShipEvent", 0);
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);
	//////////////////
	EI_CreateFrame("SHIP_BIG_PICTURE_BORDER", 156, 40, 366, 275); // tak from SHIP_BIG_PICTURE
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 161, 246, 361, 1, 4);
	EI_CreateFrame("SHIP_BIG_PICTURE_BORDER", 20, 46, 134, 161);
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8, 187, 147, 1, 4);
	EI_CreateHLine("SHIP_BIG_PICTURE_BORDER", 8, 166, 147, 1, 4);

	SetNewGroupPicture("Money_PIC", "ICONS_CHAR", "Money");
	SetNewGroupPicture("REPAIR_Money_PIC", "ICONS_CHAR", "Money");

	//HardCoffee для окна ремонта -->
	SetNewGroupPicture("REPAIR_HULL_PIC", "REPAIR_STATE_ICONS", "Hull");
	SetNewGroupPicture("REPAIR_MAST_PIC", "REPAIR_STATE_ICONS", "Mast");
	SetNewGroupPicture("REPAIR_SAIL_PIC", "REPAIR_STATE_ICONS", "Sail");
	SetNewGroupPicture("REPAIR_MONEY_PIC", "ICONS_CHAR", "Money");
	SetNewGroupPicture("REPAIR_HULL_P_PIC", "GOODS", "Planks");
	SetNewGroupPicture("REPAIR_MAST_P_PIC", "GOODS", "Planks");
	SetNewGroupPicture("REPAIR_SAIL_S_PIC", "GOODS", "SailCloth");
	// для окна ремонта <--
	FillShipyardTable();

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
	DelEventHandler("confirmShipChangeName", "confirmShipChangeName");
	DelEventHandler("CheckForRename", "CheckForRename");
	DelEventHandler("ShowInfoWindow", "ShowInfoWindow");
	DelEventHandler("MouseRClickUp", "HideInfoWindow");
	DelEventHandler("TableSelectChange", "TableSelectChange");
	DelEventHandler("ExitMsgMenu", "ExitMsgMenu");
	DelEventHandler("ShowOtherClick", "ShowOtherClick");
	DelEventHandler("CanonsRemoveAll", "CanonsRemoveAll");
	DelEventHandler("ExitCannonsMenu", "ExitCannonsMenu");
	DelEventHandler("ExitOfficerMenu", "ExitOfficerMenu");
	DelEventHandler("acceptaddofficer", "AcceptAddOfficer");
	DelEventHandler("ExitRepairMenu", "ExitRepairMenu");
	DelEventHandler("BuyShipEvent", "BuyShipEvent");
	DelEventHandler("OnHeaderClick", "OnHeaderClick");
	DelEventHandler("RehostDone", "RepairCalcSail");
	DelEventHandler("DamageSailOnBrokenMast", "DoSailDamageForRepair");

	if (idShipsDescr != -1)
	{
		LanguageCloseFile(idShipsDescr);
		idShipsDescr = -1;
	}

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
		case "BUTTON_SELL":
			if (comName == "click" || comName == "activate") ShowMessageInfo();
		break;
		case "BUTTON_BUY":
			if (comName == "click" || comName == "activate") ShowMessageInfo();
		break;
		case "MSG_OK":
			if (comName == "click" || comName == "activate") MessageOk();
		break;
		//HardCoffee для окна ремонта -->
		case "BUTTON_REPAIR":
			if (comName == "click" || comName == "activate") ShowRepairMenu();
		break;
		case "REPAIR_RIGHT_H":
			if (comName == "click" || comName == "activate") ClickRepairHullArror(1, xi_refCharacter);
			else if (comName == "rclick") ClickRepairHullArror(100, xi_refCharacter);
		break;
		case "REPAIR_LEFT_H":
			if (comName == "click" || comName == "activate") ClickRepairHullArror(-1, xi_refCharacter);
			else if (comName == "rclick") ClickRepairHullArror(-100, xi_refCharacter);
		break;
		case "REPAIR_RIGHT_M":
			if (comName == "click" || comName == "activate") ClickRepairMastArror(1, xi_refCharacter);
			else if (comName == "rclick") ClickRepairMastArror(100, xi_refCharacter);
		break;
		case "REPAIR_LEFT_M":
			if (comName == "click" || comName == "activate") ClickRepairMastArror(-1, xi_refCharacter);
			else if (comName == "rclick") ClickRepairMastArror(-100, xi_refCharacter);
		break;
		case "REPAIR_RIGHT_S":
			if (comName == "click" || comName == "activate") ClickRepairSailArror(1, xi_refCharacter);
			else if (comName == "rclick") ClickRepairSailArror(100, xi_refCharacter);
		break;
		case "REPAIR_LEFT_S":
			if (comName == "click" || comName == "activate") ClickRepairSailArror(-1, xi_refCharacter);
			else if (comName == "rclick") ClickRepairSailArror(-100, xi_refCharacter);
		break;
		case "REPAIR_CALC_ALL":
			if (comName == "click" || comName == "activate") RepairCalcAll(true);
		break;
		case "REPAIR_CALC_THIS":
			if (comName == "click" || comName == "activate") RepairCalcThis(xi_refCharacter, true);
		break;
		case "REPAIR_DISCARD_ALL":
			if (comName == "click" || comName == "activate") RepairCalcAll(false);
		break;
		case "REPAIR_BEGIN":
			if (comName == "click" || comName == "activate") RepairBegin();
		break;
		//для окна ремонта <--
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
		attributeName = "pic" + (m + 1);
		if (cn != -1)
		{
			iShipType = sti(characters[cn].ship.type);
			if (iShipType != SHIP_NOTUSED)
			{
				iShipType = sti(RealShips[iShipType].basetype);
				shipName = ShipsTypes[iShipType].Name;

				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#" + XI_ConvertString("ShipClass") + " " + ShipsTypes[iShipType].Class;
				GameInterface.SHIPS_SCROLL.(attributeName).str4 = shipName;
				GameInterface.SHIPS_SCROLL.(attributeName).str3 = "#" + MakeMoneyShow(GetShipSellPrice(&characters[cn], refNPCShipyard), MONEY_SIGN, MONEY_DELIVER);
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "ship";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("SHIPS_SCROLL.ImagesGroup", "SHIPS_" + shipName);
				m++;
			}
			else
			{
				GameInterface.SHIPS_SCROLL.(attributeName).character = cn;
				GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#";
				GameInterface.SHIPS_SCROLL.(attributeName).str2 = "NoneBoat";
				GameInterface.SHIPS_SCROLL.(attributeName).img1 = "Not Used2";
				GameInterface.SHIPS_SCROLL.(attributeName).tex1 = "BLANK_SHIP2";
				m++;
			}
		}
		else
		{
			GameInterface.SHIPS_SCROLL.(attributeName).character = -1;
			GameInterface.SHIPS_SCROLL.(attributeName).str1 = "#";
			GameInterface.SHIPS_SCROLL.(attributeName).str2 = "";
			GameInterface.SHIPS_SCROLL.(attributeName).img1 = "Not Used2";
			GameInterface.SHIPS_SCROLL.(attributeName).tex1 = "BLANK_SHIP2";
			m++;
		}
	}

	GameInterface.SHIPS_SCROLL.ListSize = m;
	GameInterface.SHIPS_SCROLL.NotUsed = 0;
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
	else if (sNode == "SHIPS_SCROLL")
	{
		if (sti(GameInterface.SHIPS_SCROLL.current) != nCurScrollNum || CurTable != "")
		{
			CurTable = "";
			NullSelectTable("TABLE_SHIPYARD"); // убрать скрол
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
	else if (sNode == "REPAIR_SHIPS_SCROLL") //HardCoffee
	{
		// KZ > пока скрол не дёргали, не строчим и не ищем по атрибутам каждый кадр
		int iCurScroll = sti(GameInterface.REPAIR_SHIPS_SCROLL.current);
		if (iCurScroll == repairScrollNum) return;
		repairScrollNum = iCurScroll;
		//Переключить персонажа
		attributeName = "pic" + (iCurScroll + 1);
		if (!CheckAttribute(&GameInterface, "REPAIR_SHIPS_SCROLL." + attributeName)) return;
		xi_refCharacter = &characters[sti(GameInterface.REPAIR_SHIPS_SCROLL.(attributeName).companionIndex)];
		SetRepairDescription(GetPreCost()); //посчитать предварительную стоимость, обновить имена и портреты
		RepairGetTotal(); //Для кнопок
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
	Table_Clear("TABLE_OTHER", false, true, false);
	//Ship info window
	SetFormatedText("Money_TEXT", MakeMoneyShow(sti(pchar.Money), MONEY_SIGN, MONEY_DELIVER));
	FillShipParam(xi_refCharacter);

	// теперь это Лояльность
	GameInterface.StatusLine.LOYALITY.Max = MAX_LOYALITY;
	GameInterface.StatusLine.LOYALITY.Min = 0;
	GameInterface.StatusLine.LOYALITY.Value = GetCharacterLoyality(xi_refCharacter);

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "LOYALITY", 0);
}

void confirmShipChangeName()
{
	/*
	if (shipIndex== -1) return;
	xi_refcharacter.ship.name = GameInterface.edit_box.str;
	GameInterface.edit_box.str = xi_refcharacter.ship.name;
	SetCurrentNode("SHIP_INFO_TEXT");   */
}

void CheckForRename()
{
	/*if (GetShipRemovable(xi_refCharacter) == true && shipIndex!= -1)
	{
		SetCurrentNode("EDIT_BOX");
	}    */
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
	int iShip, iCanType;
	string sID;
	ref refBaseShip;

	bool bShowHint = true;

	ref rChr;
	if (bShipyardOnTop)
	{
		rChr = refNPCShipyard;
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
			sID = GameInterface.(CurTable).(CurRow).UserData.ID;
			sHeader = XI_ConvertString(sID);
			sText1 = GetConvertStr(sID, "ShipsDescribe.txt");
			iCanType = sti(rChr.Ship.Cannons.Type);
			if (sID == "CannonType" && iCanType != CANNON_TYPE_NONECANNON)
			{
				ref Cannon = GetCannonByType(iCanType);
				sText2 = XI_ConvertString("Name") + ": " + XI_ConvertString(GetCannonType(iCanType));
				sText2 = sText2 + NewStr() + XI_ConvertString("Caliber") + ": " + XI_ConvertString("caliber" + GetCannonCaliber(iCanType));
				sText2 = sText2 + NewStr() + XI_ConvertString("Fire range2") + ": " + sti(Cannon.FireRange);
				sText2 = sText2 + NewStr() + XI_ConvertString("Damage") + ": x" + FloatToString(stf(Cannon.DamageMultiply), 1);
				sText2 = sText2 + NewStr() + XI_ConvertString("Reload time") + ": " + sti(GetCannonReloadTime(Cannon)) + " " + XI_ConvertString("sec");
				sText2 = sText2 + NewStr() + XI_ConvertString("weight") + ": " + sti(Cannon.Weight) + " " + XI_ConvertString("cwt") + ".";

				sGroup = "GOODS";
				sGroupPicture = GetCannonType(iCanType) + "_" + GetCannonCaliber(iCanType);

				sText3 = XI_ConvertString("Caliber_text1");
			}
			if (sID == "Crew" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText2 = XI_ConvertString("Max_crew_text1");
				sText2 = sText2 + NewStr() + XI_ConvertString("Max_crew_text2") + " " + GetMaxCrewQuantity(rChr);
			}
			// процент ремонта
			if (sID == "Hull" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Hull") + ": " + FloatToString(GetHullPercent(rChr), 1) + " %";
			}
			if (sID == "Sails" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = xiStr("Sails") + ": " + FloatToString(GetSailPercent(rChr), 1) + " %";
			}
			// трюм
			if (sID == "Capacity" && sti(rChr.ship.type) != SHIP_NOTUSED)
			{
				sText3 = XI_ConvertString("Occupied") + ": " + FloatToString((stf(GetCargoLoad(rChr)) / stf(GetCargoMaxSpace(rChr))) * 100.0, 1) + " %";
			}
		break;
		case "TABLE_SHIPYARD" :
			sHeader = XI_Convertstring("Shipyard");
			sText1 = GetConvertStr("Shipyard_hint", "ShipsDescribe.txt");
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

void TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
	CurTable = sControl;
	CurRow = "tr" + (iSelected);
	NullSelectTable("TABLE_OTHER");
	// не тереть скрол на верфи

	// заполнялка
	if (CurTable == "TABLE_SHIPYARD")
	{
		dSelected = iSelected;
		FillShipyardShip(refNPCShipyard, GameInterface.(CurTable).(CurRow).sShipId);
		FillShipParam(refNPCShipyard);
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
	DelBakSkillAttr(xi_refCharacter);
	ClearCharacterExpRate(xi_refCharacter);
	RefreshCharacterSkillExpRate(xi_refCharacter);
	SetEnergyToCharacter(xi_refCharacter);

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
	XI_WindowDisable("MSG_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	//Восстановление позиции в таблице кораблей верфи
	SetCurrentNode("TABLE_SHIPYARD");
	//	SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,"TABLE_SHIPYARD",-1, 3,"activate");
	//	SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,"TABLE_SHIPYARD",-1, 3,"click");
	if (dSelected > 0)
	{
		GameInterface.TABLE_SHIPYARD.select = dSelected;
	}
	else
	{
		GameInterface.TABLE_SHIPYARD.select = 1;
	}
	//	if (dSelected - 3 > 0) { GameInterface.TABLE_SHIPYARD.top = dSelected - 3; }
	//	else { GameInterface.TABLE_SHIPYARD.top = 1; }
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_SHIPYARD", 0);
	if (!bEmptySlot)
	{
		sMessageMode = "";
	}
}

void ShowMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", true);
	XI_WindowDisable("MSG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MSG_CANCEL");
}

void ShowOtherClick()
{
	if (GameInterface.(CurTable).(CurRow).UserData.ID == "CannonType")
	{
		ShowCannonsMenu();
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

	switch (sBort)
	{
		case "rcannon": sBort_real = "cannonr"; break;
		case "lcannon": sBort_real = "cannonl"; break;
		case "fcannon": sBort_real = "cannonf"; break;
		case "bcannon": sBort_real = "cannonb"; break;
	}

	if (iQty > maxQty) iQty = maxQty;
	if (iQty < 0) iQty = 0;

	int idx = GetCannonGoodsIdxByType(sti(chr.Ship.Cannons.Type));
	delta = iQty - curQty;
	if (delta > 0)
	{
		int iCargo = GetCargoGoods(chr, idx);
		if (iCargo < delta) iQty = curQty + iCargo;
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
		rChr = refNPCShipyard;
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

////////////// ценообразование

void FillShipyardTable()
{
	Table_Clear("TABLE_SHIPYARD", false, true, false);

	GameInterface.TABLE_SHIPYARD.hr.td1.str = XI_ConvertString("Ship");
	GameInterface.TABLE_SHIPYARD.hr.td1.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td2.str = XI_ConvertString("ShipClass");
	GameInterface.TABLE_SHIPYARD.hr.td2.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td3.str = XI_ConvertString("Cannons");
	GameInterface.TABLE_SHIPYARD.hr.td3.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td4.str = XI_ConvertString("Capacity");
	GameInterface.TABLE_SHIPYARD.hr.td4.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.hr.td5.str = XI_ConvertString("Cost");
	GameInterface.TABLE_SHIPYARD.hr.td5.scale = 0.9;
	GameInterface.TABLE_SHIPYARD.select = 0;
	GameInterface.TABLE_SHIPYARD.top = 0;

	aref arDest, arImt;
	string sAttr;
	int iNum, i, iShip;
	ref refBaseShip;
	string sShip;
	string row;

	int iCapacity;
	float fPackerBonus = 1.0;
	if (CheckOfficersPerk(refNPCShipyard, "Packer")) fPackerBonus = 1.1;

	makearef(arDest, refNPCShipyard.shipyard);
	iNum = GetAttributesNum(arDest);
	for (i = 0; i < iNum; i++)
	{
		row = "tr" + (i + 1);

		arImt = GetAttributeN(arDest, i);
		//Log_Info(GetAttributeName(arImt));
		sAttr = GetAttributeName(arImt);

		iShip = sti(arImt.Type);
		refBaseShip = GetRealShip(iShip);
		sShip = refBaseShip.BaseName;

		iCapacity = 0;
		if (iShip != SHIP_NOTUSED && iShip >= 0 && iShip < REAL_SHIPS_QUANTITY)
		{
			iCapacity = makeint(fPackerBonus * sti(RealShips[iShip].Capacity));
		}
		//
		GameInterface.TABLE_SHIPYARD.(row).sShipId = sAttr;
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.texture = "interfaces\ships\" + sShip + ".tga";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.uv = "0,0,1,1";
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.width = 46;
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.height = 46;
		GameInterface.TABLE_SHIPYARD.(row).td1.icon.offset = "0, 1";
		GameInterface.TABLE_SHIPYARD.(row).td1.textoffset = "53,0";
		GameInterface.TABLE_SHIPYARD.(row).td1.str = XI_Convertstring(sShip) + "\n\n" + arImt.Name;
		GameInterface.TABLE_SHIPYARD.(row).td1.align = "left";
		GameInterface.TABLE_SHIPYARD.(row).td1.scale = 0.82;
		GameInterface.TABLE_SHIPYARD.(row).td2.str = refBaseShip.Class;
		GameInterface.TABLE_SHIPYARD.(row).td3.str = sti(refBaseShip.CannonsQuantity);
		GameInterface.TABLE_SHIPYARD.(row).td4.str = iCapacity;
		GameInterface.TABLE_SHIPYARD.(row).td5.str = GetShipBuyPrice(iShip, refNPCShipyard);
		GameInterface.TABLE_SHIPYARD.(row).td5.color = argb(255, 255, 228, 80);
	}

	if (iNum > 0) FillShipyardShip(refNPCShipyard, sAttr);

	Table_UpdateWindow("TABLE_SHIPYARD");
}

void SetButtionsAccess()
{
	SetSelectable("BUTTON_REPAIR", false);
	SetSelectable("BUTTON_SELL", true);
	SetSelectable("BUTTON_BUY", true);

	if (bShipyardOnTop)
	{
		SetSelectable("BUTTON_REPAIR", false);
		SetSelectable("BUTTON_SELL", false);
		if (shipIndex == -1)// проверка на цену
		{
			if (GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) > sti(pchar.Money))
			{
				SetSelectable("BUTTON_BUY", false);
			}
			if (bEmptySlot && sti(pchar.ship.type) == SHIP_NOTUSED)
			{
				// нельзя купить корабль компаньону, если у ГГ нету
				SetSelectable("BUTTON_BUY", false);
			}
		}
		else
		{
			if (GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) > (GetShipSellPrice(xi_refCharacter, refNPCShipyard) + sti(pchar.Money)))
			{
				SetSelectable("BUTTON_BUY", false);
			}
			if (!GetRemovable(xi_refCharacter) || !GetShipRemovable(xi_refCharacter))
			{
				SetSelectable("BUTTON_BUY", false);
			}
		}
	}
	else
	{
		SetSelectable("BUTTON_BUY", false);

		if (GetHullPercent(xi_refCharacter) < 100 || GetSailPercent(xi_refCharacter) < 100)
		{
			SetSelectable("BUTTON_REPAIR", true);
		}
		if (shipIndex == -1)
		{
			SetSelectable("BUTTON_SELL", false);
			SetSelectable("BUTTON_REPAIR", false);
		}
		else
		{
			if (!GetRemovable(xi_refCharacter) || !GetShipRemovable(xi_refCharacter))
			{
				SetSelectable("BUTTON_SELL", false);
			}
			if (xi_refCharacter.id == pchar.id && GetCompanionQuantity(pchar) > 1)
			{
				// нельзя продать корабль ГГ, если есть ещё компаньоны
				SetSelectable("BUTTON_SELL", false);
			}
		}
	}

	if (GetGlobalTutor())
	{
		SetSelectable("BUTTON_REPAIR", false);
		SetSelectable("BUTTON_SELL", false);
		if (shipIndex != -1 && IsMainCharacter(xi_refCharacter))
		{
		    SetSelectable("BUTTON_BUY", false);
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
	SetCurrentNode("TABLE_SHIPYARD");
	SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "TABLE_SHIPYARD", -1, 3, "activate");
	SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "TABLE_SHIPYARD", -1, 3, "click");
	if (dSelected > 0)
	{
		GameInterface.TABLE_SHIPYARD.select = dSelected;
	}
	else
	{
		GameInterface.TABLE_SHIPYARD.select = 1;
	}
	if (dSelected - 3 > 0)
	{
		GameInterface.TABLE_SHIPYARD.top = dSelected - 3;
	}
	else
	{
		GameInterface.TABLE_SHIPYARD.top = 1;
	}
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_SHIPYARD", 0);
	sMessageMode = "";
}

void AcceptAddOfficer()
{
	string attributeName2 = "pic" + (nCurScrollOfficerNum + 1);
	ref sld;

	if (checkAttribute(&GameInterface, "PASSENGERSLIST." + attributeName2 + ".character"))
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
		DoBuyShip();
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
	bool bBuy;
	int iMoney;
	string add = "";

	if (bShipyardOnTop) // на стороне верфи (купить)
	{
		bBuy = true;
		if (shipIndex == -1)// проверка на цену
		{
			iMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard);
		}
		else
		{
			iMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard) - GetShipSellPrice(xi_refCharacter, refNPCShipyard);
		}
	}
	else  // продать
	{
		bBuy = false;
		iMoney = GetShipSellPrice(xi_refCharacter, refNPCShipyard);
	}
	SetFormatedText("MSG_WINDOW_CAPTION", XI_ConvertString("Ship"));

	if (bBuy)
	{
		if (iMoney < 0) add = "-";
		SetFormatedText("MSG_WINDOW_TEXT", XI_ConvertString("BuyShip") + add + " " + FindMoneyString(abs(iMoney)) + "?");
		SetSelectable("MSG_OK", true);
		sMessageMode = "ShipBuy";
	}
	else
	{
		SetFormatedText("MSG_WINDOW_TEXT", XI_ConvertString("SellShip") + add + " " + FindMoneyString(abs(iMoney)) + "?");
		SetSelectable("MSG_OK", true);
		sMessageMode = "ShipSell";
	}
	ShowMsgMenu();
}

void MessageOk()
{
	switch (sMessageMode)
	{
		case "ShipSell" :
			DoSellShip(true);
			ExitMsgMenu();
		break;

		case "ShipBuy" :
			DoBuyShipMain();
		break;
	}
}

void DoSellShip(bool _refresh)
{
	ref chref = xi_refCharacter;
	if (shipIndex != -1 && sti(chref.ship.type) != SHIP_NOTUSED)
	{
		int iTime = 30;
		int sellPrice = GetShipSellPrice(chref, refNPCShipyard);

		AddMoneyToCharacter(pchar, sellPrice);
		AddCharacterExpToSkill(pchar, "Commerce", sellPrice / 1600.0);

		if (GetOfficersPerkUsing(chref, "QuickCalculation", false)) iTime /= 2;
		WaitDate("", 0, 0, 0, 0, iTime);

		Statistic_AddValue(pchar, "SellShip", 1);

		ShipOverhaul(chref);

		// в списке на покупку. -->
		AddShip2Shipyard(chref);
		// в списке на покупку. <--
		chref.ship.type = SHIP_NOTUSED;
		// снять кэпа -->
		if (_refresh)
		{
			if (sti(chref.index) != GetMainCharacterIndex())
			{
				RemoveCharacterCompanion(pchar, chref);
				AddPassenger(pchar, chref, false);
				DelBakSkill();
				//navy --> Фигвам, а не халява
				if (CheckAttribute(chref, "PGGAi") && CheckAttribute(chref, "PGGAi.OwnShip")) //за корабли данные ГГ, деньги ГГ.
				{
					chref.Payment = true;
					DeleteAttribute(chref, "PGGAi.OwnShip");
					Log_Info(XI_ConvertString("SellCompanionShip"));
					AddMoneyToCharacter(pchar, -(sellPrice));
				}
				//navy <--
			}
			else
			{
				pchar.location.from_sea = ""; // нет корабля в порту
			}
			RefreshShipLists();
		}
	}
}

void RefreshShipLists()
{
	xi_refCharacter = pchar;
	FillShipsScroll();
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, "SHIPS_SCROLL", -1);
	SetCurrentNode("SHIPS_SCROLL");
	ProcessFrame();

	FillShipyardTable();
	bShipyardOnTop = false;
}

void AddShip2Shipyard(ref _chr)
{
	aref arTo, arFrom;

	aref arDest, arImt;
	string sAttr;
	int iNum, i, iShip;
	ref refBaseShip;
	string sShip;
	string row;

	iShip = sti(_chr.ship.type);
	RealShips[iShip].StoreShip = true;  // корабль на верфи, трется отдельным методом
	RealShips[iShip].Stolen = 0; // уже не ворованный
	makearef(arDest, refNPCShipyard.shipyard);
	iNum = GetAttributesNum(arDest);
	if (iNum == 0)
	{
		sAttr = "ship1";
	}
	else
	{
		arImt = GetAttributeN(arDest, iNum - 1);
		sAttr = GetAttributeName(arImt) + "2";
	}
	makearef(arTo, refNPCShipyard.ship);
	makearef(arFrom, _chr.Ship);
	CopyAttributes(arTo, arFrom);
	// нулим экипаж и трюм
	SetCrewQuantity(refNPCShipyard, 0);
	DeleteAttribute(refNPCShipyard, "Ship.Cargo");  //пустой трюм
	SetGoodsInitNull(refNPCShipyard);
	RecalculateCargoLoad(refNPCShipyard);

	FillShipyardShipBack(refNPCShipyard, sAttr);
	// бакапим атрибуты груза и матросов
	DeleteAttribute(refNPCShipyard, "BakCargo");
	DeleteAttribute(refNPCShipyard, "BakCrew");
	refNPCShipyard.BakCargo = "";
	makearef(arTo, refNPCShipyard.BakCargo);
	makearef(arFrom, _chr.Ship.Cargo);
	CopyAttributes(arTo, arFrom);

	refNPCShipyard.BakCrew = "";
	makearef(arTo, refNPCShipyard.BakCrew);
	makearef(arFrom, _chr.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void DoBuyShip()
{
	aref arTo, arFrom;
	int iBuyMoney = GetShipBuyPrice(sti(refNPCShipyard.Ship.Type), refNPCShipyard);
	int iTime = 30;

	DeleteAttribute(refNPCShipyard, "BakCargo");
	DeleteAttribute(refNPCShipyard, "BakCrew");
	DoSellShip(false);
	AddMoneyToCharacter(pchar, -iBuyMoney);

	AddCharacterExpToSkill(pchar, "Commerce", iBuyMoney / 700.0);

	if (GetOfficersPerkUsing(xi_refCharacter, "QuickCalculation", false)) iTime /= 2;
	WaitDate("", 0, 0, 0, 0, iTime);

	Statistic_AddValue(pchar, "BuyShip", 1);

	FillShipyardShip(refNPCShipyard, sShipId); // то, что покупаем

	makearef(arTo, xi_refCharacter.ship);
	makearef(arFrom, refNPCShipyard.Ship);
	CopyAttributes(arTo, arFrom);

	DeleteAttribute(refNPCShipyard, "shipyard." + sShipId);

	int iShip = sti(xi_refCharacter.ship.type);
	DeleteAttribute(&RealShips[iShip], "StoreShip"); // можно тереть

	if (CheckAttribute(refNPCShipyard, "BakCargo")) // есть бакап корабля
	{
		DeleteAttribute(xi_refCharacter, "Ship.Cargo");
		DeleteAttribute(xi_refCharacter, "Ship.Crew");

		xi_refCharacter.Ship.Cargo = "";
		makearef(arTo, xi_refCharacter.Ship.Cargo);
		makearef(arFrom, refNPCShipyard.BakCargo);
		CopyAttributes(arTo, arFrom);

		xi_refCharacter.Ship.Crew = "";
		makearef(arTo, xi_refCharacter.Ship.Crew);
		makearef(arFrom, refNPCShipyard.BakCrew);
		CopyAttributes(arTo, arFrom);

		AddCharacterCrew(xi_refCharacter, 0); // обрезать перегруз
		RecalculateCargoLoad(xi_refCharacter);
	}
	if (sti(xi_refCharacter.index) == GetMainCharacterIndex())
	{
		pchar.location.from_sea = sFrom_sea; // корабль в порту
	}
	DelBakSkill();
	RefreshShipLists();
}

void DoBuyShipMain()
{
	if (CheckAttribute(&GameInterface, CurTable + "." + CurRow + ".sShipId"))
	{
		sShipId = GameInterface.(CurTable).(CurRow).sShipId;

		if (!bEmptySlot) // был корабль или ГГ без корабля
		{
			DoBuyShip();
			ExitMsgMenu();
		}
		else
		{
			ExitMsgMenu();
			ShipChangeCaptan();
		}
	}
}

void BuyShipEvent()
{
	if (GetSelectable("BUTTON_BUY"))
	{
		ShowMessageInfo();
	}
}

//HardCoffee окно ремонта -->
void ShowRepairMenu()
{
	//по этому ивенту понимаем, что можно пересчитать паруса после спавна кораблей
	//Так как должно пройти время для переноса парусов на новый хост
	SetEventHandler("RehostDone", "RepairCalcSail", 1);
	//Во время спавна парусов дамажим паруса на упавших мачтах
	SetEventHandler("DamageSailOnBrokenMast", "DoSailDamageForRepair", 0);

	LocUnLoadShips();
	if (!LocLoadRepairShips(loadedLocation))
	{
		DelEventHandler("RehostDone", "RepairCalcSail");
		DelEventHandler("DamageSailOnBrokenMast", "DoSailDamageForRepair");
		return;
	}

	SetRepairData();

	XI_WindowShow("REPAIR_WINDOW", true);
	XI_WindowDisable("REPAIR_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("REPAIR_SHIPS_SCROLL");

	RepairFillShipsScroll();
	SetRepairDescription(GetPreCost());
	SetFormatedText("REPAIR_LOCATION_STR", GetCurLocationName());
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_LOCATION_STR", 5);

	PostEvent("RehostDone", REHOST_TIME, "l");
}

void SetRepairData()
{
	ref rChr;
	iTTime = 0; //глобальные
	iTCost = 0;
	//Установим атрибуты - они нужны для сохранения выбранных значений ремонта при переключении компаньонов в интерфейсе
	for (int i = 0; i < repairNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		rChr.repair.class = GetCharacterShipClass(rChr);
		rChr.repair.type = GetCharacterShipType(rChr);
		rChr.repair.hull = "0";
		rChr.repair.hull_cost = "0";
		rChr.repair.hull_time = "0";
		rChr.repair.HullLim = "0";
		rChr.repair.mast = "0";
		rChr.repair.mast_max = its(GetShipMastsQuantity(rChr)); //Запишим в атрибут, чтобы постоянно не пересчитывать
		rChr.repair.mast_cur = its(GetCurrMastsQuantity(rChr)); //Так как мачты будем временно восстанавливать - запомнм сколько их было в начале
		rChr.repair.mast_cost = "0";
		rChr.repair.mast_time = "0";
		rChr.repair.MastLim = "0";
		rChr.repair.sail = "0";
		rChr.repair.sail_cost = "0";
		rChr.repair.sail_time = "0";
		rChr.repair.SailLim = "0";
		rChr.ship.SailQuantity = "0"; //Этот атрибут считается в движке
	}

	//отключаем кнопки. включать будем по ситуации
	SetSelectable("REPAIR_CALC_ALL", false);
	SetSelectable("REPAIR_CALC_THIS", false);
	SetSelectable("REPAIR_DISCARD_ALL", false);
	SetSelectable("REPAIR_BEGIN", false);
}

void RepairFillShipsScroll()
{
	repairScrollNum = -1;
	FillScrollImageWithCompanionShips("REPAIR_SHIPS_SCROLL", 4);
	//Чтобы переключиться на корабль, выбранный в начальном скороле (вертикальном)
	GameInterface.REPAIR_SHIPS_SCROLL.current = sti(GameInterface.SHIPS_SCROLL.current);
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, "REPAIR_SHIPS_SCROLL", -1);
}

int GetPreCost() //Подсчёт предварительной стоимости ремонта
{
	int iPre = 0;
	ref rChr;
	int iShip, iHull, iMast, iSail;
	for (int i = 0; i < repairNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		iShip = sti(rChr.repair.type);
		iHull = 100 - MakeInt(GetHullPercent(rChr));
		iMast = sti(rChr.repair.mast_max) - sti(rChr.repair.mast_cur);
		iSail = 100 - MakeInt(GetSailPercent(rChr));
		if (iHull > 0) iPre += GetHullRepairCost(iShip, iHull, refNPCShipyard);
		if (iMast > 0) iPre += GetMastRepairCost(iShip, rChr, refNPCShipyard) * iMast;
		if (iSail > 0) iPre += GetSailRepairCost(iShip, iSail, refNPCShipyard);
	}
	return iPre;
}

void SetRepairDescription(int iCost) //имена и портреты
{
	string sFirst, sLast;

	SetNewPicture("REPAIR_MCHR_PICTURE", "interfaces\portraits\256\face_" + its(xi_refCharacter.FaceId) + ".tga");
	//На случай, если у НПС верфистов появятся портреты
	//SetNewPicture("REPAIR_OTHER_PICTURE", "interfaces\portraits\256\face_" + its(refNPCShipyard.FaceId) + ".tga");
	//Если у персонажа только имя, поместить его по центру
	sFirst = GetFirstName(xi_refCharacter); sLast = GetLastName(xi_refCharacter);
	if (sFirst == "" || sLast == "") SetFormatedText("REPAIR_NAME_STR", GetFullName(xi_refCharacter));
	else SetFormatedText("REPAIR_NAME_STR", sFirst + "\n" + sLast); //Принудительный перенос фамилии на новую строку
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_NAME_STR", 5);

	SetFormatedText("REPAIR_MONEY_TEXT", XI_ConvertString("OurMoney") + " " + FindMoneyString(sti(pchar.money)));
	//проверка на стоимость, если всё починено, или стоимость 0 - надпись не отображаем
	if (iCost > 0) SetFormatedText("REPAIR_NEED_MONEY_TEXT", XI_ConvertString("RepairMoneyNeed") + " " + FindMoneyString(iCost));

	if (CheckAttribute(xi_refCharacter, "ship.name"))
		SetFormatedText("REPAIR_SHIP_NAME", xi_refCharacter.ship.name);
	else SetFormatedText("REPAIR_SHIP_NAME", "");
}

void RepairCalcSail()
{
	//обновление состояния парусов вызывается по ивенту, так как после вызова LocLoadRepairShips()
	//должно пройти время для переноса мачт на новый хост
	if (!GetEntity(&objSail, "sail")) return;
	//пересчёт максимального количества парусов с учётом сломаных мачт
	SendMessage(&objSail, "l", MSG_SAIL_CALC);
	RepairGetTotal();
	ClickRepairSailArror(0, xi_refCharacter); //На случай, если до этого менялось количество мачт
}

void RepairGetTotal() //Общее время и стоимость ремонта
{
	ref rChr;
	bool bCalcAll = false;
	iTTime = 0; //глобальные
	iTCost = 0;

	// > суммы и лимиты разведены на два прохода, иначе лимиты для всех кораблей, кроме последнего, считались по неполной сумме затрат
	int i;
	bool bCurrDone = false;

	for (i = 0; i < repairNumShips; i++) // > проход 1: полные суммы
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		iTTime = iTTime + sti(rChr.repair.hull_time) + sti(rChr.repair.mast_time) + sti(rChr.repair.sail_time);
		iTCost = iTCost + sti(rChr.repair.hull_cost) + sti(rChr.repair.mast_cost) + sti(rChr.repair.sail_cost);
	}

	for (i = 0; i < repairNumShips; i++) // > проход 2: лимиты уже по полной сумме
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		RepairGetLimit(rChr); //для кнопок
		if (rChr.id == xi_refCharacter.id)
		{
			bCurrDone = true; // > надписи обновлены здесь же, повторный вызов не нужен
		}
		else
		{
			if (rChr.repair.calcThis == "1") bCalcAll = true;
		}
	}

	if (!bCurrDone) RepairGetLimit(xi_refCharacter);

	if (iTTime > 0 || iTCost > 0)
	{
		SetSelectable("REPAIR_DISCARD_ALL", true);
		SetSelectable("REPAIR_BEGIN", true);
	}
	else
	{
		SetSelectable("REPAIR_DISCARD_ALL", false);
		SetSelectable("REPAIR_BEGIN", false);
	}
	SetSelectable("REPAIR_CALC_ALL", bCalcAll);
}

void RepairGetLimit(ref rChr) //расчёт значений и надписей для пределов воcстановлений
{
	int iMoney = sti(pchar.Money);
	int iShip = sti(rChr.repair.type);
	int iHullCur = MakeInt(GetHullPercent(rChr));
	int iMastMax = sti(rChr.repair.mast_max);
	int iMastCur = sti(rChr.repair.mast_cur);
	int iMastTemp = GetCurrMastsQuantity(rChr); //так как мачты будут восстанавливаться при нажатии стрелки
	int iSailCur = MakeInt(GetSailPercent(rChr));
	int iTempLim, iHullLim, iMastLim, iSailLim;
	string sHullLim, sSailLim, sMastLim;
	bool bSwitch = false;
	bool bCurr = false;
	if (rChr.id == xi_refCharacter.id) bCurr = true; //надписи обновляем только для корабля, выбранного в шып-скроле

	//HULL	//Максимум корпуса зависит от количества бабла
	sHullLim = "";
	iTempLim = iMoney - iTCost + sti(rChr.repair.hull_cost); //Вычтим стоимость корпуса, чтобы при прибалени процента максимум не менялся
	iTempLim = makeint(iTempLim / GetHullRepairCost(iShip, 1, refNPCShipyard));
	iHullLim = iHullCur + iTempLim;
	if (iHullLim > 100) iHullLim = 100;
	else if (bCurr) sHullLim = sTxNeedMoney;

	rChr.repair.HullLim = iHullLim;

	//MAST	//Максимум мачт зависит от корпуса и бабла
	sMastLim = "";
	//С начала считаем корпус
	iMastLim = makeint(iMastMax * (iHullCur + sti(rChr.repair.hull)) / 90); // 90 - это минимальное сотояние корпуса для всех мачт
	if (iMastLim > iMastMax) iMastLim = iMastMax;
	else if (iMastLim < iMastCur) iMastLim = iMastCur;
	if (bCurr && iMastLim < iMastMax) sMastLim = sTxNeedHull;
	//Затем считаем бабки
	iTempLim = iMoney - iTCost + sti(rChr.repair.mast_cost);
	iTempLim = makeint(iTempLim / GetMastRepairCost(iShip, rChr, refNPCShipyard));
	//сравним с лимитом по корпусу, равно нужно для правильного отображения надписи
	if (iTempLim + iMastCur <= iMastLim)
	{
		iMastLim = iTempLim + iMastCur;
		if (bCurr && iMastLim != iMastMax) sMastLim = sTxNeedMoney;
	}

	rChr.repair.MastLim = iMastLim;

	//SAIL	//максимум зависит от количества мачт и бабла
	//считаем мачты
	iSailLim = sti(rChr.ship.SailQuantity);
	if (iSailLim < iSailCur) iSailLim = iSailCur;
	if (iSailLim > 100) iSailLim = 100;
	else if (bCurr) sSailLim = sTxNeedMast;

	//считаем бабки
	iTempLim = iMoney - iTCost + sti(rChr.repair.sail_cost);
	iTempLim = makeint(iTempLim / GetSailRepairCost(iShip, 1, refNPCShipyard));
	iTempLim = iSailCur + iTempLim;
	//сравним с лимитом по мачтам для правильного отображения надписи
	if (bCurr && iTempLim <= iSailLim) sSailLim = sTxNeedMoney;
	if (iTempLim < iSailLim) iSailLim = iTempLim;
	rChr.repair.SailLim = iSailLim;

	//Подключаем/отключаем кнопки. Оцениваем по порядку по каждому элементу
	if (iHullLim > iHullCur || iMastLim > iMastTemp || iSailLim > iSailCur) bSwitch = true;

	if (bSwitch &&
	iHullLim == iHullCur + sti(rChr.repair.hull) &&
	iMastLim == iMastTemp &&
	iSailLim == iSailCur + sti(rChr.repair.sail))
		bSwitch = false;

	rChr.repair.calcThis = bSwitch; //Запомним для кнопки все корабли

	if (bCurr)
	{
		SetSelectable("REPAIR_CALC_THIS", bSwitch);
		RepairStatShow(sHullLim, sMastLim, sSailLim); //Обновим надписи
	}
}

//измение значений в надписях для выбранного в скореле корабля
void RepairStatShow(string sHullLim, string sMastLim, string sSailLim)
{
	int iRepair, iCurr, iTempLim;
	bool bLimit; // > предел восстановления достигнут

	//HULL ************
	//в sHullLim уже записано чего не хватает
	iTempLim = sti(xi_refCharacter.repair.HullLim);
	iCurr = MakeInt(GetHullPercent(xi_refCharacter));
	iRepair = iCurr + sti(xi_refCharacter.repair.hull);

	bLimit = false;
	//Слева
	SetFormatedText("REPAIR_HULL_L_STR", sTxCondition + its(iCurr) + "%");

	if (iTempLim < 100)
	{
		if (iTempLim == iRepair) //если нельзя восстановить, красим в красный цвет
		{
			sHullLim = ColorText(xi_refCharacter.repair.HullLim + "%", "contra") + "\n" + ColorText(sHullLim, "contra");
			bLimit = true;
		}
		else sHullLim = xi_refCharacter.repair.HullLim + "%" + "\n" + sHullLim;
	}
	else sHullLim = ColorText(xi_refCharacter.repair.HullLim + "%", "lightblue");

	//Убрать инфу о пределах, если полностью починено
	if (100 != iCurr) AddLineToFormatedText("REPAIR_HULL_L_STR", sTxLimits + sHullLim);

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_HULL_L_STR", 5);

	//центр
	SetFormatedText("REPAIR_QTY_H", its(iRepair) + "%");
	if (iRepair == 100)
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_H", 8, 0, argb(255, 128, 255, 255));
	else if (bLimit)
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_H", 8, 0, argb(255, 255, 196, 196));

	//Справа
	SetFormatedText("REPAIR_HULL_R_STR", sTxRepairCost + "\n" + FindMoneyString(sti(xi_refCharacter.repair.hull_cost))
		+ "\n" + sTxRepairTime + "\n" + RepairWindowGetTime(sti(xi_refCharacter.repair.hull_time), false));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_HULL_R_STR", 5);

	//MAST ************
	iTempLim = sti(xi_refCharacter.repair.MastLim);
	iRepair = GetCurrMastsQuantity(xi_refCharacter); // так как мачты будут временно чиниться при нажатии стрелки
	iCurr = sti(xi_refCharacter.repair.mast_cur);
	int iMastMax = sti(xi_refCharacter.repair.mast_max);

	bLimit = false;
	//Слева
	SetFormatedText("REPAIR_MAST_L_STR", sTxCondition + xi_refCharacter.repair.mast_cur + "/" + xi_refCharacter.repair.mast_max);
	if (iTempLim == iRepair && iTempLim != iMastMax)
	{
		//Красим в красный
		sMastLim = ColorText(xi_refCharacter.repair.MastLim + "/" + xi_refCharacter.repair.mast_max, "contra") + "\n" + ColorText(sMastLim, "contra");
		bLimit = true;
	}
	else if (iTempLim == iMastMax) sMastLim = ColorText(xi_refCharacter.repair.MastLim + "/" + xi_refCharacter.repair.mast_max, "lightblue");
	else sMastLim = xi_refCharacter.repair.MastLim + "/" + xi_refCharacter.repair.mast_max + "\n" + sMastLim;

	if (iCurr != iMastMax) //убрать инфу о пределах
		AddLineToFormatedText("REPAIR_MAST_L_STR", sTxLimits + sMastLim);

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_MAST_L_STR", 5);

	//Центр
	SetFormatedText("REPAIR_QTY_M", its(iRepair) + "/" + xi_refCharacter.repair.mast_max);
	if (iRepair == iMastMax)
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_M", 8, 0, argb(255, 128, 255, 255));
	else if (bLimit)
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_M", 8, 0, argb(255, 255, 196, 196));

	//Справа
	SetFormatedText("REPAIR_MAST_R_STR", sTxRepairCost + "\n" + FindMoneyString(sti(xi_refCharacter.repair.mast_cost))
		+ "\n" + sTxRepairTime + "\n" + RepairWindowGetTime(sti(xi_refCharacter.repair.mast_time), false));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_MAST_R_STR", 5);

	//SAIL ************
	iTempLim = sti(xi_refCharacter.repair.SailLim);
	iCurr = makeint(GetSailPercent(xi_refCharacter));
	iRepair = iCurr + sti(xi_refCharacter.repair.sail);

	bLimit = false;
	//Слева
	SetFormatedText("REPAIR_SAIL_L_STR", sTxCondition + its(iCurr) + "%");

	if (iTempLim < 100)
	{
		if (iTempLim == iRepair)
		{
			sSailLim = ColorText(xi_refCharacter.repair.SailLim + "%", "contra") + "\n" + ColorText(sSailLim, "contra");
			bLimit = true;
		}
		else sSailLim = xi_refCharacter.repair.SailLim + "%" + "\n" + sSailLim;
	}
	else sSailLim = ColorText(xi_refCharacter.repair.SailLim + "%", "lightblue");

	if (100 != iCurr) AddLineToFormatedText("REPAIR_SAIL_L_STR", sTxLimits + sSailLim);
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_SAIL_L_STR", 5);

	//Центр
	SetFormatedText("REPAIR_QTY_S", its(iRepair) + "%");
	if (iRepair == 100)
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_S", 8, 0, argb(255, 128, 255, 255));
	else if (bLimit)
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_S", 8, 0, argb(255, 255, 196, 196));

	//Справа
	SetFormatedText("REPAIR_SAIL_R_STR", sTxRepairCost + "\n" + FindMoneyString(sti(xi_refCharacter.repair.sail_cost))
		+ "\n" + sTxRepairTime + "\n" + RepairWindowGetTime(sti(xi_refCharacter.repair.sail_time), false));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_SAIL_R_STR", 5);

	//total info
	SetFormatedText("REPAIR_COST_T_TEXT", sTxCostTotal + FindMoneyString(iTCost));
	SetFormatedText("REPAIR_TIME_T_TEXT", sTxTimeTotal + RepairWindowGetTime(iTTime, false));
}

//клики по стрелкам -->
void ClickRepairHullArror(int add, ref rChr)
{
	int iHullCur = MakeInt(GetHullPercent(rChr));
	int iHullRep = sti(rChr.repair.hull);
	int iHullLim = sti(rChr.repair.HullLim);
	int iTemp, iTemp2;
	if (add > 0)
	{
		if ((iHullCur + iHullRep + add) > iHullLim) iHullRep = iHullLim - iHullCur;
		else iHullRep += add;
	}
	else
	{
		iHullRep += add;
		if (iHullRep < 0) iHullRep = 0;
	}
	rChr.repair.hull = iHullRep;
	rChr.repair.hull_cost = GetHullRepairCost(sti(rChr.repair.type), iHullRep, refNPCShipyard);
	rChr.repair.hull_time = makeint((HULL_REPAIR_YARD_TIME * 0.05 / makefloat(sti(rChr.repair.class) + 2)) * makefloat(iHullRep));

	RepairGetTotal();
	//Пересчитаем накликаные мачты, с учётом пересчитанных пределов, если уменьшим корпус
	ClickRepairMastArror(0, rChr);
}

void ClickRepairMastArror(int add, ref rChr)
{
	int iMastRep = sti(rChr.repair.mast);
	int iMastMax = sti(rChr.repair.mast_max);
	int iMastTemp = GetCurrMastsQuantity(rChr);
	int iMastCur = sti(rChr.repair.mast_cur);
	int iMastLim = sti(rChr.repair.MastLim);
	int iOneCost = GetMastRepairCost(sti(rChr.repair.type), rChr, refNPCShipyard);
	if (add > 0)
	{
		//trace(rChr.id +" iMastMax " +iMastMax +" iMastTemp = " +iMastTemp +" iMastCur " +iMastCur +" iMastLim " +iMastLim);
		if (add > iMastLim - iMastTemp) add = iMastLim - iMastTemp;
		if (add == 0) return;
		if (iMastTemp + add <= iMastLim)
		{
			if (!bMastBatch) LocUnLoadShips();
			RepairTempRepairMast(rChr, add);
			if (!bMastBatch) LocLoadRepairShips(loadedLocation);
			iMastRep += add;
		}
	}
	else
	{
		if (add < iMastCur - iMastTemp) add = iMastCur - iMastTemp;
		else if (iMastLim < iMastTemp) add = iMastLim - iMastTemp; //Фикс, если передумали чнить корпус
		//trace(rChr.id +" iMastMax " +iMastMax +" iMastCur " +iMastCur +" iMastLim " +iMastLim);
		if (add == 0) return;
		if (iMastMax + add >= iMastCur)
		{
			if (!bMastBatch) LocUnLoadShips();
			RepairTempBrokeMast(rChr, add);
			if (!bMastBatch) LocLoadRepairShips(loadedLocation);
			iMastRep += add;
		}
	}
	rChr.repair.mast = iMastRep; //для подсчёта времени и стоимости
	rChr.repair.mast_cost = its(iOneCost * iMastRep);
	if (iMastMax < 1) rChr.repair.mast_time = 0;
	else rChr.repair.mast_time = makeint((MAST_REPAIR_YARD_TIME * 0.5 / makefloat(sti(rChr.repair.class) + 5)) * makefloat(iMastRep));
	EnableFailedSails(rChr); //Изменили мачты - удалим атрибуты с парусов, которые нельзя было поставить
	// > шлём один раз в конце
	if (!bMastBatch) PostEvent("RehostDone", REHOST_TIME, "l"); //по этому ивенту понимаем, что можно пересчитать паруса
	// RepairGetLimit считать после ивента
}

void ClickRepairSailArror(int add, ref rChr)
{
	int iShip = sti(rChr.repair.type);
	int iSailCur = makeint(GetSailPercent(rChr));
	int iSailRep = sti(rChr.repair.sail);
	int iSailLim = sti(rChr.repair.SailLim);
	//trace("add = " +add +" iSailLim = " +iSailLim +" iSailCur = " +iSailCur +" iSailRep = " +iSailRep);
	if (add > 0)
	{
		if (sti(pchar.Money) >= iTCost + GetSailRepairCost(iShip, add, refNPCShipyard)) iSailRep += add;
		else iSailRep += (sti(pchar.Money) - iTCost) / GetSailRepairCost(iShip, 1, refNPCShipyard); //на сколько хватит
		if ((iSailRep + iSailCur) > iSailLim) iSailRep = iSailLim - iSailCur; //Чтобы не выставлялось больше расчётного лимита
	}
	else if (add == 0 && iSailLim < iSailRep + iSailCur) //пересчёт, если передумали восстанавливать мачты
	{
		iSailRep = iSailLim - iSailCur;
	}
	else
	{
		iSailRep += add;
		if (iSailRep < 0) iSailRep = 0;
	}
	rChr.repair.sail = iSailRep;
	rChr.repair.sail_cost = GetSailRepairCost(iShip, iSailRep, refNPCShipyard);
	rChr.repair.sail_time = makeint((SAIL_REPAIR_YARD_TIME * 0.05 / makefloat(sti(rChr.repair.class))) * makefloat(iSailRep));
	RepairGetTotal();
}
//клики по стрелкам <--

void RepairCalcThis(ref rChr, bool bIncrease) //Кнопка посчитать это судно
{
	int iClicks = -100;
	if (bIncrease) iClicks = abs(iClicks);
	RepairGetLimit(rChr);
	ClickRepairHullArror(iClicks, rChr);
	ClickRepairMastArror(iClicks, rChr);
	//Coffee обсчитывать парус надо после ивента на подсчёт парусов, но здесь оно каким то образом работает сразу
	RepairCalcSail();
	ClickRepairSailArror(iClicks, rChr);
}

void RepairCalcAll(bool bIncrease) //Кнопка посчитать все корабли
{
	ref rChr;
	int i;
	int iClicks = -100;
	if (bIncrease) iClicks = abs(iClicks);
	if (repairNumShips <= 0) return;

	bMastBatch = true;
	for (i = 0; i < repairNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		RepairGetLimit(rChr);
		ClickRepairHullArror(iClicks, rChr);
		ClickRepairMastArror(iClicks, rChr);
	}
	bMastBatch = false;

	// > один респавн на всю пачку вместо одного на корабль
	LocUnLoadShips();
	LocLoadRepairShips(loadedLocation);
	PostEvent("RehostDone", REHOST_TIME, "l");

	RepairCalcSail();
	for (i = 0; i < repairNumShips; i++)
	{
		ClickRepairSailArror(iClicks, GetCharacter(sti(repairShips[i].chrIndex)));
	}
}

void RepairBegin() //Начинаем ремонт по кнопке Ремонт
{
	ref rChr;
	int i, iHullRep, iMastRep, iSailRep, iCurr;
	int iShClass;
	//Идём по всем кораблям так как заранее не известно какие корабли накликали
	for (i = 0; i < repairNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));

		iShClass = sti(rChr.repair.class);
		iHullRep = sti(rChr.repair.hull);
		iMastRep = sti(rChr.repair.mast);
		iSailRep = sti(rChr.repair.sail);

		if (iHullRep > 0)
		{
			AddCharacterExpToSkill(pchar, "Repair", (iHullRep * (7 - iShClass) / 2.5));
			ProcessHullRepair(rChr, stf(iHullRep));
			//Дырки вроде в движке удаляются, но на всякий оставлю
			if (MakeInt(GetHullPercent(rChr)) >= 90) DeleteAttribute(rChr, "ship.blots");//было 100			 
		}
		if (iMastRep > 0)
		{
			AddCharacterExpToSkill(rChr, "Repair", (3 * iMastRep * (7 - iShClass) / 3.5));
			//мачты уже починены, когда нажимались стрелки. Осталось удалить атрибут, чтобы на выходе он не поломал мачты
			if (CheckAttribute(rChr, "repair.tmpMast")) DeleteAttribute(rChr, "repair.tmpMast");
		}
		if (iSailRep > 0)
		{
			AddCharacterExpToSkill(pchar, "Repair", (iSailRep * (7 - iShClass) / 3.5));
			iCurr = makeint(GetSailPercent(rChr));
			ProcessSailRepair(rChr, makefloat(iSailRep));
			//костыль так так ProcessSailRepair прибавляет к дамагу парусов дамаг верёвок -->
			SendMessage(&objSail, "l", MSG_SAIL_CALC);
			iSailRep = iCurr + iSailRep - makeint(GetSailPercent(rChr));
			ProcessSailRepair(rChr, makefloat(iSailRep));
			//<--
		}
		//Удалять атрибут rChr.repair ненадо, он удалится во время выхода
	}
	AddMoneyToCharacter(pchar, -iTCost);

	if (iTTime > 0)
	{
		bIsRepairingProcess = true;
		//bQuestCheckProcessFreeze = true;
		PlaySound("interface\repair_ship.wav");
		WaitDate("", 0, 0, 0, iTTime, 0);
		RecalculateJumpTable();
		RefreshLandTime();

		bIsRepairingProcess = false;
		//bQuestCheckProcessFreeze = false;

		Log_info(sTxTimeTotal + RepairWindowGetTime(iTTime, false));
		//notification(sTemp, "Repair");
	}

	ExitRepairMenu();
	LAi_Fade("", "");

	if (sti(pchar.ship.type) == SHIP_NOTUSED) PChar.nation = GetBaseHeroNation();
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void ExitRepairMenu() //Кнопка Отмена
{
	DelEventHandler("RehostDone", "RepairCalcSail");
	DelEventHandler("DamageSailOnBrokenMast", "DoSailDamageForRepair");

	XI_WindowShow("REPAIR_WINDOW", false);
	XI_WindowDisable("REPAIR_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("SHIPS_SCROLL");
	sMessageMode = "";
	ref rChr;
	bool bOk = false;
	for (int i = 0; i < repairNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		RepairTempBrokeMast(rChr, -100); //Сломаем накликаные мачты заодно удалим атрибут brokenMast с парусов
		DeleteAttribute(rChr, "repair");

		// сменить EntityId с SHIP на Player для pchar, иначе после выхода сообщения будут отправляться в SHIP, а не в Character
		if (!SendMessage(&repairShips[i], "las", MSG_SHIP_SET_CHARACTER_EID, rChr, rChr.model.entity))
			trace("ERROR: shipyard MSG_SHIP_SET_CHARACTER_EID has returned false");
		else if (rChr.index == pchar.index)
			bOk = true;
	}
	iTCost = 0; //Обнулим глобальные переменные, на случай, если снова откроем окно
	iTTime = 0;
	//Чтобы переключить вертикальный скрол на корабль, выбранный в скроле окна
	GameInterface.SHIPS_SCROLL.current = sti(GameInterface.REPAIR_SHIPS_SCROLL.current);
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, "SHIPS_SCROLL", -1);

	if (bOk)
	{
		LocRestoreShipsAfterRepair(loadedLocation);
		if (!SendMessage(pchar, "las", MSG_SHIP_SET_CHARACTER_EID, pchar, pchar.model.entity))
			trace("ERROR: shipyard MSG_SHIP_SET_CHARACTER_EID has returned false");
	}
}
//окно ремонта <--

void OnHeaderClick()
{
	string sControl = GetEventData();
	int iColumn = GetEventData();

	if (sControl == "TABLE_SHIPYARD") SortShipsList(iColumn, false, sControl);
}

void SortShipsList(int column, bool preserveState, string tableName)
{
	string datatype = "string";
	switch (column)
	{
		case 2: datatype = "integer"; break;
		case 3: datatype = "integer"; break;
		case 4: datatype = "integer"; break;
		case 5: datatype = "integer"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 0);
}




////    boal 30.07.06 найм матросов
int	nCurScrollNum = 0;
ref refCharacter;
ref refTown;

int  BuyOrSell = 0; // 1-buy -1 sell
int  iPriceSailor;
int	 QtyMax = 0;
int  iSalaryRequirement = 0;

int AoP_GetBuccaneerCrewPrice(ref rTown)
{
	float fExp = (GetCrewExp(rTown, "Sailors") + GetCrewExp(rTown, "Cannoners") + GetCrewExp(rTown, "Soldiers")) / 100.0;
	float fSkill = GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_LEADERSHIP) + GetSummonSkillFromNameToOld(GetMainCharacter(), SKILL_COMMERCE);
	int nCrewCost = makeint((0.5 + MOD_SKILL_ENEMY_RATE / 5.0) * 30 * (1.0 - fSkill / 40.0));
	nCrewCost = makeint(fExp * nCrewCost + 0.5);
	if (nCrewCost < 5) nCrewCost = 5;
	return nCrewCost;
}

void InitInterface(string iniName)
{
	StartAboveForm(true);
	LAi_SetActorTypeNoGroup(pchar);
	refCharacter = pchar;

	int iColonyIdx;

	if (CheckAttribute(pchar, "AoP_BuccaneerHireNPC"))
	{
		int iBuccIdx = GetCharacterIndex(pchar.AoP_BuccaneerHireNPC);
		if (iBuccIdx >= 0)
		{
			refTown = GetCharacter(iBuccIdx);

			int iPastDays = 3;
			if (CheckAttribute(refTown, "AoP_BuccaneerCrewRefresh.year"))
			{
				iPastDays = GetPastTime("day", sti(refTown.AoP_BuccaneerCrewRefresh.year), sti(refTown.AoP_BuccaneerCrewRefresh.month), sti(refTown.AoP_BuccaneerCrewRefresh.day), stf(refTown.AoP_BuccaneerCrewRefresh.time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
			}

			if (iPastDays >= 3)
			{
				int iRep = sti(pchar.reputation);
				int iMaxCrew = 100 + makeint(100.0 * (iRep - REPUTATION_MIN) / (REPUTATION_MAX - REPUTATION_MIN));
				if (iMaxCrew < 100) iMaxCrew = 100;
				if (iMaxCrew > 200) iMaxCrew = 200;
				refTown.Ship.Crew.Quantity = 60 + rand(iMaxCrew - 60);
				refTown.AoP_BuccaneerCrewRefresh.year = GetDataYear();
				refTown.AoP_BuccaneerCrewRefresh.month = GetDataMonth();
				refTown.AoP_BuccaneerCrewRefresh.day = GetDataDay();
				refTown.AoP_BuccaneerCrewRefresh.time = GetTime();
			}
		}
		else
		{
			DeleteAttribute(pchar, "AoP_BuccaneerHireNPC");
			iColonyIdx = FindColony(loadedLocation.fastreload);
			if (iColonyIdx < 0) iColonyIdx = 0;
			refTown = GetColonyByIndex(iColonyIdx);
		}
	}
	else
	{
		iColonyIdx = FindColony(loadedLocation.fastreload);
		if (iColonyIdx < 0)
		{
			Trace("WARNING HireCrew > Colony not found for location " + loadedLocation.fastreload + ", fallback to 0");
			iColonyIdx = 0;
		}
		refTown = GetColonyByIndex(iColonyIdx);
	}

	FillShipsScroll();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	CreateString(true,"ShipName","",FONT_NORMAL,COLOR_MONEY, 400,170,SCRIPT_ALIGN_CENTER,0.7);

	SetDescription();

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcCommand",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0);

	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("frame","ProcessFrame",1);
	SetEventHandler("ChangeSelectScrollImage", "ChangeSelectScrollImage", 0);

	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("TransactionCancel", "TransactionCancel", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON","ADD_BUTTON",0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);

	SetEventHandler("ExitSalaryReqMenu", "ExitSalaryReqMenu", 0);
	SetEventHandler("AcceptSalaryRequirement", "AcceptSalaryRequirement", 0);
	SetEventHandler("DeclineSalaryRequirement", "DeclineSalaryRequirement", 0);

	SetNewGroupPicture("CREW_PICTURE", "SHIP_STATE_ICONS", "Crew");
	SetNewGroupPicture("CREW_PICTURE2", "SHIP_STATE_ICONS", "Crew");
	SetBackupQty();
	SetCurrentNode("SHIPS_SCROLL");
	GameInterface.qty_edit.str = 0;
	QtyMax = GetCargoFreeSpace(refCharacter);
	if (!CheckAttribute(&TEV, "AchievementData.HireTavernCrew"))
	{
		TEV.AchievementData.HireTavernCrew = 0;
	}
}

void ProcessBreakExit()
{
	IDoExit( RC_INTERFACE_FOOD_INFO_EXIT );
}

void ProcessCancelExit()
{
	IDoExit( RC_INTERFACE_FOOD_INFO_EXIT );
}

void IDoExit(int exitCode)
{
	EndAboveForm(true);
	RecalculateCargoLoad(refCharacter);
	GetBackupQty(); // если неожиданно вышли
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("evntDoPostExit","DoPostExit");

	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("frame","ProcessFrame");
	DelEventHandler("ChangeSelectScrollImage", "ChangeSelectScrollImage");

	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("TransactionCancel", "TransactionCancel");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON","ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");

	DelEventHandler("ExitSalaryReqMenu", "ExitSalaryReqMenu");
	DelEventHandler("AcceptSalaryRequirement", "AcceptSalaryRequirement");
	DelEventHandler("DeclineSalaryRequirement", "DeclineSalaryRequirement");

	XI_WindowShow("SALARY_REQUIREMENT_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);

	DeleteAttribute(pchar, "AoP_BuccaneerHireNPC");
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	LAi_SetPlayerType(pchar);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	if (nodName != "SHIPS_SCROLL")
	{
		if(comName=="leftstep")
		{
			ADD_BUTTON();
		}
		if(comName=="rightstep")
		{
			REMOVE_BUTTON();
		}
		if(comName=="speedleft")
		{
			ADD_ALL_BUTTON();
		}
		if(comName=="speedright")
		{
			REMOVE_ALL_BUTTON();
		}
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void FillShipsScroll()
{
	nCurScrollNum = -1;
	FillScrollImageWithCompanionShips("SHIPS_SCROLL", 4);

	if(!CheckAttribute(&GameInterface,"SHIPS_SCROLL.current"))
	{
		GameInterface.SHIPS_SCROLL.current = 0;
	}
}

void SetVariable()
{
	string sText, sTextSecond;
	int iColor;
	int nShipType = sti(refCharacter.ship.type);

	if (nShipType == SHIP_NOTUSED)
	{
		GameInterface.strings.shipname = "";
		return;
	}

	ref refBaseShip = GetRealShip(nShipType);

	int nCrew = GetCrewQuantity(refCharacter);
	int nOpt  = GetOptCrewQuantity(refCharacter);
	int nMin  = GetMinCrewQuantity(refCharacter);

	SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\256\face_" + its(refCharacter.FaceId) + ".tga");

	SetFormatedText("CAPACITY", GetFullNameTitulForm(refCharacter));

	sText = XI_ConvertString("OurMoney") + NewStr() + FindMoneyString(sti(pchar.money));
	SetFormatedText("OUR_GOLD", sText);

	if (CheckAttribute(refCharacter, "ship.name"))
	{
		GameInterface.strings.shipname = refCharacter.ship.name;
	}
	else
	{
		GameInterface.strings.shipname = "";
	}
	SetCrewExpTable(refCharacter, "TABLE_CREW", "BAR_Sailors", "BAR_Cannoners", "BAR_Soldiers");

	SetFormatedText("CREW_QTY", ""+nCrew);
	if (nCrew > nOpt || nCrew < nMin)
	{
		iColor = argb(255,255,64,64);
	}
	else
	{
		iColor = argb(255,255,255,255);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREW_QTY", 8,-1,iColor);
	float fCharMorale = stf(refCharacter.Ship.Crew.Morale);
	SetNewGroupPicture("CREW_MORALE_PIC", "MORALE_SMALL", GetMoraleGroupPicture(fCharMorale));
	SetFormatedText("CREW_MORALE_TEXT", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(makeint(fCharMorale))));

	// на одном корабле
	SetFoodShipInfo(refCharacter, "FOOD_SHIP");
	SetRumShipInfo(refCharacter, "RUM_SHIP");

	SetFormatedText("INFO_SHIP", XI_ConvertString(refBaseShip.BaseName) + ", " + LowerFirst(XI_ConvertString("ShipClass")) + " " + refBaseShip.Class + NewStr() + XI_ConvertString("CrewSize") + ": " + XI_ConvertString("Min_Crew") + " " + nMin + ", " + XI_ConvertString("Max_Crew") + " " + nOpt);
	SetFormatedText("MONEY_SHIP", XI_ConvertString("Pay_for_ship") + " " + NewStr() + FindMoneyString(GetSalaryForShip(refCharacter)));
	////  заполнялка города
	SetCrewExpTable(refTown, "TABLE_CREW2", "BAR_Sailors2", "BAR_Cannoners2", "BAR_Soldiers2");

	SetFormatedText("CREW_QTY2", ""+GetCrewQuantity(refTown));
	float fTownMorale = stf(refTown.Ship.Crew.Morale);
	SetNewGroupPicture("CREW_MORALE_PIC2", "MORALE_SMALL", GetMoraleGroupPicture(fTownMorale));
	SetFormatedText("CREW_MORALE_TEXT2", XI_ConvertString("CrewMorale") + ": " + XI_ConvertString(GetMoraleName(makeint(fTownMorale))));
	if (CheckAttribute(pchar, "AoP_BuccaneerHireNPC")) iPriceSailor = AoP_GetBuccaneerCrewPrice(refTown);
	else iPriceSailor = GetCrewPriceForTavern(refTown.id);
	SetFormatedText("TAVERN_PRICE", XI_ConvertString("CrewCost") + FindMoneyString(iPriceSailor));
}

void ProcessFrame()
{
	if(GetCurrentNode() == "")
	{
		SetCurrentNode("MAIN_FRAME");
	}
}

void ChangeSelectScrollImage()
{
	string sNod = GetEventData();
	int nIdx = GetEventData();

	if(sNod == "SHIPS_SCROLL")
	{
		if(nIdx!=nCurScrollNum)
		{
			GetBackupQty(); // если неожиданно вышли
			nCurScrollNum = nIdx;
			SetDescription();
			GameInterface.qty_edit.str = 0;
			SetFormatedText("QTY_TypeOperation", "");
			SetFormatedText("QTY_Result", "");
		}
	}
}

void SetDescription()
{
 	string sChrId;

	if(GetCurrentNode() == "SHIPS_SCROLL")
	{
		string attributeName = "pic" + (nCurScrollNum+1);
		if(CheckAttribute(&GameInterface, "SHIPS_SCROLL." + attributeName))
		{
			int iCharacter = GameInterface.SHIPS_SCROLL.(attributeName).companionIndex;
			sChrId = characters[iCharacter].id;
			refCharacter = characterFromID(sChrId);
			QtyMax = GetCargoFreeSpace(refCharacter);
			SetBackupQty();
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
	SetVariable();
}

void ShowInfoWindow()
{
	string sHeader, sText1, sText2, sText3, sPicture;
	sPicture = "-1";

	sHeader = GetConvertStr("Crew_Exp", "ShipsDescribe.txt");
	sText1  = GetConvertStr("Crew_Exp_hint", "ShipsDescribe.txt");

	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, "", "", 64, 64);
}

void HideInfoWindow()
{
	CloseTooltip();
}
// бакап значений, до применения
void SetBackupQty()
{
	aref    arTo, arFrom;
	NullCharacter.TavernBak.Hero = "";
	NullCharacter.TavernBak.Tavern = "";

	makearef(arTo,   NullCharacter.TavernBak.Hero);
	makearef(arFrom, refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);

	makearef(arTo,   NullCharacter.TavernBak.Tavern);
	makearef(arFrom, refTown.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void GetBackupQty()
{
	aref    arTo, arFrom;

	makearef(arFrom,   NullCharacter.TavernBak.Hero);
	makearef(arTo, refCharacter.Ship.Crew);
	CopyAttributes(arTo, arFrom);

	makearef(arFrom,   NullCharacter.TavernBak.Tavern);
	makearef(arTo, refTown.Ship.Crew);
	CopyAttributes(arTo, arFrom);
}

void TransactionCancel()
{
	if (sti(GameInterface.qty_edit.str) == 0)
	{   // выход
		ProcessCancelExit();
	}
	else
	{
		CancelQty();
	}
}

void CancelQty()
{
	GetBackupQty();
	SetVariable();
	GameInterface.qty_edit.str = 0;
	SetFormatedText("QTY_TypeOperation", "");
	SetFormatedText("QTY_Result", "");
}

void TransactionOK()
{
	int moneyback;
	confirmChangeQTY_EDIT();
	if (BuyOrSell == 0)
	{
		CancelQty();
		return;
	}

	if (!GetRemovable(refCharacter))
	{
		CancelQty();
		return;
	}

 	if (BuyOrSell == 1) // BUY  нанять
	{
		moneyback = makeint(iPriceSailor*stf(GameInterface.qty_edit.str));
		pchar.money = sti(pchar.money) - moneyback; // TODO > AddMoneyToCharacter(pchar, -moneyback); // > потом сделать, чтобы выводилось в конце разово
		RecalculateCargoLoad(refCharacter);
		QtyMax = GetCargoFreeSpace(refCharacter);
		Statistic_AddValue(Pchar, "Money", moneyback);
		// учёт нанятой команды для ачивки
		if (CheckAttribute(&TEV, "AchievementData.HireTavernCrew"))
		{
			TEV.AchievementData.HireTavernCrew = sti(TEV.AchievementData.HireTavernCrew) +
				sti(GameInterface.qty_edit.str);
		}

		SetBackupQty(); // применим и согласимся
		CancelQty();
	}
 	else
	{ // SELL
		ShowSalaryReqMenu();
	}
}

void ShowSalaryReqMenu()
{
	iSalaryRequirement = GetSalaryForCrewMonthlyPay(refCharacter, sti(GameInterface.qty_edit.str));
	string sSalaryForCrew = XI_ConvertString("CrewRebel_1") + NewStr() + XI_ConvertString("CrewRebel_2") + FindMoneyString(iSalaryRequirement) + ".";

	SetFormatedText("SALARY_REQUIREMENT_CAPTION", XI_ConvertString("CrewRebel_3"));
	SetFormatedText("SALARY_REQUIREMENT_WINDOW_TEXT", sSalaryForCrew);

	XI_WindowShow("SALARY_REQUIREMENT_WINDOW", true);
	XI_WindowDisable("SALARY_REQUIREMENT_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetNodeUsing("SALARY_REQUIREMENT_ACCEPT", true);
	SetNodeUsing("SALARY_REQUIREMENT_CANCEL", true);

	if(sti(pchar.money) < iSalaryRequirement)
	{
		SetSelectable("SALARY_REQUIREMENT_ACCEPT", false);
	}
	else
	{
		SetSelectable("SALARY_REQUIREMENT_ACCEPT", true);
	}

	SetCurrentNode("SALARY_REQUIREMENT_ACCEPT");
}

void AcceptSalaryRequirement()
{
	AddMoneyToCharacter(pchar,-iSalaryRequirement);
	if (CheckAttribute(&TEV, "AchievementData.HireTavernCrew"))
	{
		TEV.AchievementData.HireTavernCrew = sti(TEV.AchievementData.HireTavernCrew) -
			sti(GameInterface.qty_edit.str);
	}
	SetBackupQty();
	ExitSalaryReqMenu();
}

void DeclineSalaryRequirement()
{
	if(!CheckAttribute(pchar, "CrewPayment")) pchar.CrewPayment = iSalaryRequirement;
	else pchar.CrewPayment = sti(pchar.CrewPayment) + iSalaryRequirement;
	SetBackupQty();
	ExitSalaryReqMenu();
}

void ExitSalaryReqMenu()
{
	RecalculateCargoLoad(refCharacter);
	SetCurrentNode("SHIPS_SCROLL");
	XI_WindowShow("SALARY_REQUIREMENT_WINDOW", false);
	XI_WindowDisable("SALARY_REQUIREMENT_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);
	CancelQty();
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
	SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	float fQty;
	aref  arCC, arTC;
	int   nQty, nCharCrew, nTownCrew, nMaxCrew;

	GetBackupQty();	 // обновим как было до правок

	nQty      = sti(GameInterface.qty_edit.str); // приведение к целому
	nCharCrew = GetCrewQuantity(refCharacter);
	nTownCrew = GetCrewQuantity(refTown);

	if (nQty == 0)
	{
		SetFormatedText("QTY_TypeOperation", "");
		SetFormatedText("QTY_Result", "");
		BuyOrSell = 0;
	}
	else
	{
		if (nQty < 0 || BuyOrSell == -1)
		{  // уволить
			if (BuyOrSell != -1)
			{
				nQty = -nQty;
			}
			BuyOrSell = -1;
			// проверка на колво доступное -->
			if (nQty > nCharCrew)
			{
				nQty = nCharCrew;
			}
			// проверка на колво доступное <--
			if (GetGlobalTutor())
			{
				nQty = 0;
			}
			SetFormatedText("QTY_TypeOperation", XI_ConvertString("Fire"));
			SetFormatedText("QTY_Result", "");
		}
		else
		{  // нанять
			BuyOrSell = 1;
			nMaxCrew = GetMaxCrewQuantity(refCharacter);
			// проверка на колво доступное -->
			if (nQty > nTownCrew)
			{
				nQty = nTownCrew;
			}
			if (nQty > (nMaxCrew - nCharCrew))
			{
				nQty = nMaxCrew - nCharCrew;
			}

			if (iPriceSailor > 0 && makeint(iPriceSailor*makefloat(nQty)) > sti(pchar.money))
			{
				nQty = makeint(sti(pchar.money) / iPriceSailor);
			}

			QtyMax = GetCargoFreeSpace(refCharacter);
			if(QtyMax > 0)
			{
				if(nQty >= QtyMax)
				{
					nQty = QtyMax;
				}
			}
			else nQty = 0;

			// проверка на колво доступное <--

			SetFormatedText("QTY_TypeOperation", XI_ConvertString("Hire"));
			SetFormatedText("QTY_Result", XI_ConvertString("CrewCost2") + makeint(iPriceSailor*makefloat(nQty)));
		}
		// если получили ноль
		if (nQty == 0)
		{
			SetFormatedText("QTY_TypeOperation", "");
			SetFormatedText("QTY_Result", "");
			BuyOrSell = 0;
		}
	}
	if (nQty > 0)
	{ // применение кол-ва

		if (BuyOrSell == 1)
		{   // найм меняет опыт и мораль корабля
			makearef(arCC, refCharacter.Ship.Crew);
			makearef(arTC, refTown.Ship.Crew);

			fQty = stf(nCharCrew + nQty);
			arCC.Exp.Sailors   = (stf(arCC.Exp.Sailors)*nCharCrew   + stf(arTC.Exp.Sailors)*nQty)   / fQty;
			arCC.Exp.Cannoners = (stf(arCC.Exp.Cannoners)*nCharCrew + stf(arTC.Exp.Cannoners)*nQty) / fQty;
			arCC.Exp.Soldiers  = (stf(arCC.Exp.Soldiers)*nCharCrew  + stf(arTC.Exp.Soldiers)*nQty)  / fQty;
			arCC.Morale        = (stf(arCC.Morale)*nCharCrew        + stf(arTC.Morale)*nQty)        / fQty;
		}
		else
		{ // увольнение меняет таверну
			makearef(arCC, refCharacter.Ship.Crew);
			makearef(arTC, refTown.Ship.Crew);
			fQty = stf(nTownCrew + nQty);
			arTC.Exp.Sailors   = (stf(arTC.Exp.Sailors)*nTownCrew   + stf(arCC.Exp.Sailors)*nQty)   / fQty;
			arTC.Exp.Cannoners = (stf(arTC.Exp.Cannoners)*nTownCrew + stf(arCC.Exp.Cannoners)*nQty) / fQty;
			arTC.Exp.Soldiers  = (stf(arTC.Exp.Soldiers)*nTownCrew  + stf(arCC.Exp.Soldiers)*nQty)  / fQty;
			arTC.Morale        = (stf(arTC.Morale)*nTownCrew        + stf(arCC.Morale)*nQty)        / fQty;
		}
		SetCrewQuantity(refCharacter, nCharCrew + BuyOrSell*nQty);
		refTown.Ship.Crew.Quantity = nTownCrew - BuyOrSell*nQty;
	}
	GameInterface.qty_edit.str = nQty;
	if (CheckAttribute(pchar, "AoP_BuccaneerHireNPC"))
	{
		if (sti(refTown.Ship.Crew.Exp.Sailors) < 90) refTown.Ship.Crew.Exp.Sailors = 90;
		if (sti(refTown.Ship.Crew.Exp.Cannoners) < 90) refTown.Ship.Crew.Exp.Cannoners = 90;
		if (sti(refTown.Ship.Crew.Exp.Soldiers) < 90) refTown.Ship.Crew.Exp.Soldiers = 90;
		if (sti(refTown.Ship.Crew.Morale) < 90) refTown.Ship.Crew.Morale = 90;
	}
	SetVariable(); // обновим экран
}

void REMOVE_ALL_BUTTON()  // продать все (уволить)
{
	GetBackupQty();	// вернём все как было
	if (!GetRemovable(refCharacter)) return;
	GameInterface.qty_edit.str = -GetCrewQuantity(refCharacter);
	if (GetGlobalTutor())
	{
		GameInterface.qty_edit.str = 0;
	}
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // купить все
{
	GetBackupQty();	// вернём все как было
	if (!GetRemovable(refCharacter)) return;
	GameInterface.qty_edit.str = GetCrewQuantity(refTown);
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // продать
{
	if (!GetRemovable(refCharacter)) return;
	if (GetGlobalTutor())
	{
		if (BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);
			BuyOrSell = 0;
			ChangeQTY_EDIT();
		}
		return;
	}
	if (BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = -1;
	}
	else
	{
		if (BuyOrSell == -1)
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // купить
{
	if (!GetRemovable(refCharacter)) return;
	if (BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = 1;
	}
	else
	{
  		if (BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - 1);
		}
		BuyOrSell = 0;
	}
	ChangeQTY_EDIT();
}

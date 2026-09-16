ref xi_refCharacter;
ref refNPCShipyard;

int repairScrollNum, iTCost, iTTime;
object objSail;
bool bMastBatch = false;
int iLngShipsDescribe = -1;

string sTxCondition, sTxLimits, sTxRepairCost, sTxRepairTime;
string sTxNeedMoney, sTxNeedHull, sTxNeedMast;
string sTxCostTotal, sTxTimeTotal, sTxOurMoney, sTxMoneyNeed;

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
	sTxOurMoney   = XI_ConvertString("OurMoney") + " ";
	sTxMoneyNeed  = XI_ConvertString("RepairMoneyNeed") + " ";
}

bool RepairIsFreeForShip(ref rChr)
{
	if (!CheckAttribute(refNPCShipyard, "FreeRepairClass")) return false;
	return GetCharacterShipClass(rChr) >= sti(refNPCShipyard.FreeRepairClass);
}

int RepairGetHullCost(ref rChr, int iPercent)
{
	if (RepairIsFreeForShip(rChr)) return 0;
	return GetHullRepairCost(sti(rChr.repair.type), iPercent, refNPCShipyard);
}

int RepairGetMastCost(ref rChr)
{
	if (RepairIsFreeForShip(rChr)) return 0;
	return GetMastRepairCost(sti(rChr.repair.type), rChr, refNPCShipyard);
}

int RepairGetSailCost(ref rChr, int iPercent)
{
	if (RepairIsFreeForShip(rChr)) return 0;
	return GetSailRepairCost(sti(rChr.repair.type), iPercent, refNPCShipyard);
}

// > перезагрузка одного корабля вместо респавна всей эскадры
void RepairRespawnShip(ref rChr)
{
	if (bMastBatch) return;
	if (LocReloadRepairShip(loadedLocation, LocGetRepairShipSlot(rChr))) return;
	LocUnLoadShips(); // > слот не нашёлся
	LocLoadRepairShips(loadedLocation);
}

void InitInterface_R(string iniName, ref _shipyarder)
{
	GameInterface.title = "titleRepair";
	xi_refCharacter = pchar;
	refNPCShipyard = _shipyarder;
	if (!CheckAttribute(refNPCShipyard, "ShipCostRate")) refNPCShipyard.ShipCostRate = 1.0;
	RepairCacheStrings();
	iLngShipsDescribe = LanguageOpenFile("ShipsDescribe.txt");

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);

	SetEventHandler("InterfaceBreak", "ProcessExitCancel", 0);
	SetEventHandler("exitCancel", "ProcessExitCancel", 0);
	SetEventHandler("ievnt_command", "ProcessCommandExecute", 0);
	SetEventHandler("frame", "ProcessFrame", 1);
	SetEventHandler("RehostDone", "RepairCalcSail", 1);
	SetEventHandler("DamageSailOnBrokenMast", "DoSailDamageForRepair", 0);

	SetNewGroupPicture("REPAIR_HULL_PIC", "REPAIR_STATE_ICONS", "Hull");
	SetNewGroupPicture("REPAIR_MAST_PIC", "REPAIR_STATE_ICONS", "Mast");
	SetNewGroupPicture("REPAIR_SAIL_PIC", "REPAIR_STATE_ICONS", "Sail");
	SetNewGroupPicture("REPAIR_MONEY_PIC", "ICONS_CHAR", "Money");

	LocUnLoadShips();
	if (!LocLoadRepairShips(loadedLocation))
	{
		DelEventHandler("RehostDone", "RepairCalcSail");
		DelEventHandler("DamageSailOnBrokenMast", "DoSailDamageForRepair");
		ProcessExitCancel();
		return;
	}

	SetRepairData();
	RepairFillShipsScroll();
	SetCurrentNode("REPAIR_SHIPS_SCROLL");
	SetRepairDescription(GetPreCost());
	PostEvent("RehostDone", REHOST_TIME, "l");
}

void ProcessExitCancel()
{
	DelEventHandler("InterfaceBreak", "ProcessExitCancel");
	DelEventHandler("exitCancel", "ProcessExitCancel");
	DelEventHandler("ievnt_command", "ProcessCommandExecute");
	DelEventHandler("frame", "ProcessFrame");
	DelEventHandler("RehostDone", "RepairCalcSail");
	DelEventHandler("DamageSailOnBrokenMast", "DoSailDamageForRepair");

	ref rChr;
	int i;
	for (i = 0; i < repairNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		RepairTempBrokeMast(rChr, -100);
		DeleteAttribute(rChr, "repair");
		if (CheckAttribute(rChr, "model.entity"))
		{
			if (!SendMessage(&repairShips[i], "las", MSG_SHIP_SET_CHARACTER_EID, rChr, rChr.model.entity))
				trace("ERROR: shiprepair MSG_SHIP_SET_CHARACTER_EID has returned false for " + rChr.id);
		}
	}
	iTCost = 0;
	iTTime = 0;
	if (iLngShipsDescribe >= 0) { LanguageCloseFile(iLngShipsDescribe); iLngShipsDescribe = -1; }

	LocUnLoadShips();

	// > корабли и огни локации возвращаем всегда, а не только при наличии группы locators.ships
	if (LoadSegment("sea_ai\ShipLights.c"))
	{
		InitShipLights();
		UnloadSegment("sea_ai\ShipLights.c");
	}
	CreateEntity(&ShipLights, "ShipLights");
	LayerAddObject(EXECUTE, &ShipLights, 0);
	LayerAddObject(REALIZE, &ShipLights, -1);
	LayerAddObject(SEA_SUNROAD, &ShipLights, -1);
	LocLoadShips(loadedLocation);

	int iPchIdx = sti(pchar.index);
	if (CheckAttribute(pchar, "model.entity"))
	{
		for (i = 0; i < locNumShips; i++)
		{
			if (iShips[i] != iPchIdx) continue;
			if (!SendMessage(pchar, "las", MSG_SHIP_SET_CHARACTER_EID, pchar, pchar.model.entity))
				trace("ERROR: shiprepair MSG_SHIP_SET_CHARACTER_EID has returned false for " + pchar.id);
			break;
		}
	}

	interfaceResultCommand = RC_INTERFACE_SHIP_REPAIR;
	EndCancelInterface(true);
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch (nodName)
	{
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
	}
}

void ProcessFrame()
{
	int iCurScroll = sti(GameInterface.REPAIR_SHIPS_SCROLL.current);
	if (iCurScroll == repairScrollNum) return;
	if (GetCurrentNode() != "REPAIR_SHIPS_SCROLL") return;
	repairScrollNum = iCurScroll;

	string attributeName = "pic" + its(iCurScroll + 1);
	if (!CheckAttribute(&GameInterface, "REPAIR_SHIPS_SCROLL." + attributeName)) return;
	xi_refCharacter = &characters[sti(GameInterface.REPAIR_SHIPS_SCROLL.(attributeName).companionIndex)];
	SetRepairDescription(GetPreCost());
	RepairGetTotal();
}

void SetRepairData()
{
	ref rChr;
	iTTime = 0;
	iTCost = 0;
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
		rChr.repair.mast_max = its(GetShipMastsQuantity(rChr));
		rChr.repair.mast_cur = its(GetCurrMastsQuantity(rChr));
		rChr.repair.mast_cost = "0";
		rChr.repair.mast_time = "0";
		rChr.repair.MastLim = "0";
		rChr.repair.sail = "0";
		rChr.repair.sail_cost = "0";
		rChr.repair.sail_time = "0";
		rChr.repair.SailLim = "0";
		rChr.ship.SailQuantity = "0";
		// > цена за один процент/мачту не меняется, пока открыто окно
		if (RepairIsFreeForShip(rChr))
		{
			rChr.repair.hull_one = 0;
			rChr.repair.mast_one = 0;
			rChr.repair.sail_one = 0;
		}
		else
		{
			rChr.repair.hull_one = func_max(1, RepairGetHullCost(rChr, 1));
			rChr.repair.mast_one = func_max(1, RepairGetMastCost(rChr));
			rChr.repair.sail_one = func_max(1, RepairGetSailCost(rChr, 1));
		}
	}

	SetSelectable("REPAIR_CALC_ALL", false);
	SetSelectable("REPAIR_CALC_THIS", false);
	SetSelectable("REPAIR_DISCARD_ALL", false);
	SetSelectable("REPAIR_BEGIN", false);
}

void RepairFillShipsScroll()
{
	repairScrollNum = -1;
	FillScrollImageWithCompanionShips("REPAIR_SHIPS_SCROLL", 4);
	GameInterface.REPAIR_SHIPS_SCROLL.current = 0;
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, "REPAIR_SHIPS_SCROLL", -1);
}

int GetPreCost()
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
		if (iHull > 0) iPre += RepairGetHullCost(rChr, iHull);
		if (iMast > 0) iPre += RepairGetMastCost(rChr) * iMast;
		if (iSail > 0) iPre += RepairGetSailCost(rChr, iSail);
	}
	return iPre;
}

void SetRepairDescription(int iCost)
{
	string sFirst = GetFirstName(xi_refCharacter);
	string sLast = GetLastName(xi_refCharacter);
	SetNewPicture("REPAIR_MCHR_PICTURE", "interfaces\portraits\256\face_" + its(xi_refCharacter.FaceId) + ".tga");
	if (sFirst == "" || sLast == "") SetFormatedText("REPAIR_NAME_STR", GetFullName(xi_refCharacter));
	else SetFormatedText("REPAIR_NAME_STR", sFirst + "\n" + sLast);
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_NAME_STR", 5);
	SetFormatedText("REPAIR_LOCATION_STR", GetCurLocationName());
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_LOCATION_STR", 5);

	SetFormatedText("REPAIR_MONEY_TEXT", sTxOurMoney + FindMoneyString(sti(pchar.money)));
	if (iCost > 0) SetFormatedText("REPAIR_NEED_MONEY_TEXT", sTxMoneyNeed + FindMoneyString(iCost));
	else SetFormatedText("REPAIR_NEED_MONEY_TEXT", "");

	if (CheckAttribute(xi_refCharacter, "ship.name")) SetFormatedText("REPAIR_SHIP_NAME", xi_refCharacter.ship.name);
	else SetFormatedText("REPAIR_SHIP_NAME", "");

	int iShip = GetCharacterShipType(xi_refCharacter);
	if (iShip != SHIP_NOTUSED)
	{
		ref refBaseShip = GetRealShip(iShip);
		string sShip = refBaseShip.BaseName;
		SetNewPicture("REPAIR_SHIP_BIG_PICTURE", "interfaces\ships\" + sShip + ".tga");
		SetFormatedText("REPAIR_SHIP_TYPE", XI_ConvertString(sShip));
		SetFormatedText("REPAIR_SHIP_CLASS", XI_ConvertString("ShipClass") + " " + refBaseShip.Class);
		SetFormatedText("REPAIR_SHIP_DESCRIPTION", LanguageConvertString(iLngShipsDescribe, sShip));
		SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_SHIP_DESCRIPTION", 5);
	}
	else
	{
		SetNewPicture("REPAIR_SHIP_BIG_PICTURE", "interfaces\blank_ship2.tga");
		SetFormatedText("REPAIR_SHIP_TYPE", "");
		SetFormatedText("REPAIR_SHIP_CLASS", "");
		SetFormatedText("REPAIR_SHIP_DESCRIPTION", "");
	}
}

void RepairCalcSail()
{
	if (!GetEntity(&objSail, "sail")) return;
	SendMessage(&objSail, "l", MSG_SAIL_CALC);
	RepairGetTotal();
	ClickRepairSailArror(0, xi_refCharacter);
}

void RepairGetTotal()
{
	ref rChr;
	bool bCalcAll = false;
	bool bCurrDone = false;
	bool bAnyRepair = false;
	iTTime = 0;
	iTCost = 0;

	int i;
	for (i = 0; i < repairNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		iTTime += sti(rChr.repair.hull_time) + sti(rChr.repair.mast_time) + sti(rChr.repair.sail_time);
		iTCost += sti(rChr.repair.hull_cost) + sti(rChr.repair.mast_cost) + sti(rChr.repair.sail_cost);
		if (sti(rChr.repair.hull) > 0 || sti(rChr.repair.mast) > 0 || sti(rChr.repair.sail) > 0) bAnyRepair = true;
	}

	for (i = 0; i < repairNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		RepairGetLimit(rChr);
		if (rChr.id == xi_refCharacter.id) bCurrDone = true;
		else if (rChr.repair.calcThis == "1") bCalcAll = true;
	}
	if (!bCurrDone) RepairGetLimit(xi_refCharacter);

	if (bAnyRepair)
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

void RepairGetLimit(ref rChr)
{
	int iMoney = sti(pchar.Money);
	int iHullCur = MakeInt(GetHullPercent(rChr));
	int iMastMax = sti(rChr.repair.mast_max);
	int iMastCur = sti(rChr.repair.mast_cur);
	int iMastTemp = GetCurrMastsQuantity(rChr);
	int iSailCur = MakeInt(GetSailPercent(rChr));
	int iTempLim, iHullLim, iMastLim, iSailLim;
	string sHullLim = "";
	string sMastLim = "";
	string sSailLim = "";
	bool bSwitch = false;
	bool bCurr = (rChr.id == xi_refCharacter.id);
	bool bFree = RepairIsFreeForShip(rChr);

	if (bFree)
	{
		iHullLim = 100;
	}
	else
	{
		iTempLim = iMoney - iTCost + sti(rChr.repair.hull_cost);
		iTempLim = makeint(iTempLim / sti(rChr.repair.hull_one));
		iHullLim = iHullCur + iTempLim;
		if (iHullLim > 100) iHullLim = 100;
		else if (bCurr) sHullLim = sTxNeedMoney;
	}
	rChr.repair.HullLim = iHullLim;

	iMastLim = makeint(iMastMax * (iHullCur + sti(rChr.repair.hull)) / 90);
	if (iMastLim > iMastMax) iMastLim = iMastMax;
	else if (iMastLim < iMastCur) iMastLim = iMastCur;
	if (bCurr && iMastLim < iMastMax) sMastLim = sTxNeedHull;
	if (!bFree)
	{
		iTempLim = iMoney - iTCost + sti(rChr.repair.mast_cost);
		iTempLim = makeint(iTempLim / sti(rChr.repair.mast_one));
		if (iTempLim + iMastCur <= iMastLim)
		{
			iMastLim = iTempLim + iMastCur;
			if (bCurr && iMastLim != iMastMax) sMastLim = sTxNeedMoney;
		}
	}
	rChr.repair.MastLim = iMastLim;

	iSailLim = sti(rChr.ship.SailQuantity);
	if (iSailLim < iSailCur) iSailLim = iSailCur;
	if (iSailLim > 100) iSailLim = 100;
	else if (bCurr) sSailLim = sTxNeedMast;
	if (!bFree)
	{
		iTempLim = iMoney - iTCost + sti(rChr.repair.sail_cost);
		iTempLim = makeint(iTempLim / sti(rChr.repair.sail_one));
		iTempLim = iSailCur + iTempLim;
		if (bCurr && iTempLim <= iSailLim) sSailLim = sTxNeedMoney;
		if (iTempLim < iSailLim) iSailLim = iTempLim;
	}
	rChr.repair.SailLim = iSailLim;

	if (iHullLim > iHullCur || iMastLim > iMastTemp || iSailLim > iSailCur) bSwitch = true;
	if (bSwitch && iHullLim == iHullCur + sti(rChr.repair.hull) && iMastLim == iMastTemp && iSailLim == iSailCur + sti(rChr.repair.sail)) bSwitch = false;
	rChr.repair.calcThis = bSwitch;

	if (bCurr)
	{
		SetSelectable("REPAIR_CALC_THIS", bSwitch);
		RepairStatShow(sHullLim, sMastLim, sSailLim);
	}
}

void RepairStatShow(string sHullLim, string sMastLim, string sSailLim)
{
	int iRepair, iCurr, iTempLim;
	bool bLimit;

	iTempLim = sti(xi_refCharacter.repair.HullLim);
	iCurr = MakeInt(GetHullPercent(xi_refCharacter));
	iRepair = iCurr + sti(xi_refCharacter.repair.hull);
	bLimit = false;
	SetFormatedText("REPAIR_HULL_L_STR", sTxCondition + its(iCurr) + "%");
	if (iTempLim < 100)
	{
		if (iTempLim == iRepair)
		{
			sHullLim = ColorText(xi_refCharacter.repair.HullLim + "%", "contra") + "\n" + ColorText(sHullLim, "contra");
			bLimit = true;
		}
		else sHullLim = xi_refCharacter.repair.HullLim + "%\n" + sHullLim;
	}
	else sHullLim = ColorText(xi_refCharacter.repair.HullLim + "%", "lightblue");
	if (100 != iCurr) AddLineToFormatedText("REPAIR_HULL_L_STR", sTxLimits + sHullLim);
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_HULL_L_STR", 5);
	SetFormatedText("REPAIR_QTY_H", its(iRepair) + "%");
	if (iRepair == 100) SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_H", 8, 0, argb(255, 128, 255, 255));
	else if (bLimit) SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_H", 8, 0, argb(255, 255, 196, 196));
	SetFormatedText("REPAIR_HULL_R_STR", sTxRepairCost + "\n" + FindMoneyString(sti(xi_refCharacter.repair.hull_cost)) + "\n" + sTxRepairTime + "\n" + RepairWindowGetTime(sti(xi_refCharacter.repair.hull_time), false));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_HULL_R_STR", 5);

	iTempLim = sti(xi_refCharacter.repair.MastLim);
	iRepair = GetCurrMastsQuantity(xi_refCharacter);
	iCurr = sti(xi_refCharacter.repair.mast_cur);
	int iMastMax = sti(xi_refCharacter.repair.mast_max);
	bLimit = false;
	SetFormatedText("REPAIR_MAST_L_STR", sTxCondition + xi_refCharacter.repair.mast_cur + "/" + xi_refCharacter.repair.mast_max);
	if (iTempLim == iRepair && iTempLim != iMastMax)
	{
		sMastLim = ColorText(xi_refCharacter.repair.MastLim + "/" + xi_refCharacter.repair.mast_max, "contra") + "\n" + ColorText(sMastLim, "contra");
		bLimit = true;
	}
	else if (iTempLim == iMastMax) sMastLim = ColorText(xi_refCharacter.repair.MastLim + "/" + xi_refCharacter.repair.mast_max, "lightblue");
	else sMastLim = xi_refCharacter.repair.MastLim + "/" + xi_refCharacter.repair.mast_max + "\n" + sMastLim;
	if (iCurr != iMastMax) AddLineToFormatedText("REPAIR_MAST_L_STR", sTxLimits + sMastLim);
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_MAST_L_STR", 5);
	SetFormatedText("REPAIR_QTY_M", its(iRepair) + "/" + xi_refCharacter.repair.mast_max);
	if (iRepair == iMastMax) SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_M", 8, 0, argb(255, 128, 255, 255));
	else if (bLimit) SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_M", 8, 0, argb(255, 255, 196, 196));
	SetFormatedText("REPAIR_MAST_R_STR", sTxRepairCost + "\n" + FindMoneyString(sti(xi_refCharacter.repair.mast_cost)) + "\n" + sTxRepairTime + "\n" + RepairWindowGetTime(sti(xi_refCharacter.repair.mast_time), false));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_MAST_R_STR", 5);

	iTempLim = sti(xi_refCharacter.repair.SailLim);
	iCurr = makeint(GetSailPercent(xi_refCharacter));
	iRepair = iCurr + sti(xi_refCharacter.repair.sail);
	bLimit = false;
	SetFormatedText("REPAIR_SAIL_L_STR", sTxCondition + its(iCurr) + "%");
	if (iTempLim < 100)
	{
		if (iTempLim == iRepair)
		{
			sSailLim = ColorText(xi_refCharacter.repair.SailLim + "%", "contra") + "\n" + ColorText(sSailLim, "contra");
			bLimit = true;
		}
		else sSailLim = xi_refCharacter.repair.SailLim + "%\n" + sSailLim;
	}
	else sSailLim = ColorText(xi_refCharacter.repair.SailLim + "%", "lightblue");
	if (100 != iCurr) AddLineToFormatedText("REPAIR_SAIL_L_STR", sTxLimits + sSailLim);
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_SAIL_L_STR", 5);
	SetFormatedText("REPAIR_QTY_S", its(iRepair) + "%");
	if (iRepair == 100) SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_S", 8, 0, argb(255, 128, 255, 255));
	else if (bLimit) SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_S", 8, 0, argb(255, 255, 196, 196));
	SetFormatedText("REPAIR_SAIL_R_STR", sTxRepairCost + "\n" + FindMoneyString(sti(xi_refCharacter.repair.sail_cost)) + "\n" + sTxRepairTime + "\n" + RepairWindowGetTime(sti(xi_refCharacter.repair.sail_time), false));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_SAIL_R_STR", 5);

	SetFormatedText("REPAIR_COST_T_TEXT", sTxCostTotal + FindMoneyString(iTCost));
	SetFormatedText("REPAIR_TIME_T_TEXT", sTxTimeTotal + RepairWindowGetTime(iTTime, false));
}

void ClickRepairHullArror(int add, ref rChr)
{
	int iHullCur = MakeInt(GetHullPercent(rChr));
	int iHullRep = sti(rChr.repair.hull);
	int iHullLim = sti(rChr.repair.HullLim);
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
	rChr.repair.hull_cost = RepairGetHullCost(rChr, iHullRep);
	rChr.repair.hull_time = makeint((HULL_REPAIR_YARD_TIME * 0.05 / makefloat(sti(rChr.repair.class) + 2)) * makefloat(iHullRep));
	RepairGetTotal();
	ClickRepairMastArror(0, rChr);
}

void ClickRepairMastArror(int add, ref rChr)
{
	int iMastRep = sti(rChr.repair.mast);
	int iMastMax = sti(rChr.repair.mast_max);
	int iMastTemp = GetCurrMastsQuantity(rChr);
	int iMastCur = sti(rChr.repair.mast_cur);
	int iMastLim = sti(rChr.repair.MastLim);
	int iOneCost = sti(rChr.repair.mast_one);
	if (add > 0)
	{
		if (add > iMastLim - iMastTemp) add = iMastLim - iMastTemp;
		if (add == 0) return;
		if (iMastTemp + add <= iMastLim)
		{
			RepairTempRepairMast(rChr, add);
			RepairRespawnShip(rChr);
			iMastRep += add;
		}
	}
	else
	{
		if (add < iMastCur - iMastTemp) add = iMastCur - iMastTemp;
		else if (iMastLim < iMastTemp) add = iMastLim - iMastTemp;
		if (add == 0) return;
		if (iMastMax + add >= iMastCur)
		{
			RepairTempBrokeMast(rChr, add);
			RepairRespawnShip(rChr);
			iMastRep += add;
		}
	}
	rChr.repair.mast = iMastRep;
	rChr.repair.mast_cost = its(iOneCost * iMastRep);
	if (iMastMax < 1) rChr.repair.mast_time = 0;
	else rChr.repair.mast_time = makeint((MAST_REPAIR_YARD_TIME * 0.5 / makefloat(sti(rChr.repair.class) + 5)) * makefloat(iMastRep));
	EnableFailedSails(rChr);
	if (!bMastBatch) PostEvent("RehostDone", REHOST_TIME, "l");
}

void ClickRepairSailArror(int add, ref rChr)
{
	int iShip = sti(rChr.repair.type);
	int iSailCur = makeint(GetSailPercent(rChr));
	int iSailRep = sti(rChr.repair.sail);
	int iSailLim = sti(rChr.repair.SailLim);
	if (add > 0)
	{
		if (RepairIsFreeForShip(rChr)) iSailRep += add;
		else if (sti(pchar.Money) >= iTCost + RepairGetSailCost(rChr, add)) iSailRep += add;
		else iSailRep += (sti(pchar.Money) - iTCost) / sti(rChr.repair.sail_one);
		if ((iSailRep + iSailCur) > iSailLim) iSailRep = iSailLim - iSailCur;
	}
	else if (add == 0 && iSailLim < iSailRep + iSailCur) iSailRep = iSailLim - iSailCur;
	else
	{
		iSailRep += add;
		if (iSailRep < 0) iSailRep = 0;
	}
	rChr.repair.sail = iSailRep;
	rChr.repair.sail_cost = RepairGetSailCost(rChr, iSailRep);
	rChr.repair.sail_time = makeint((SAIL_REPAIR_YARD_TIME * 0.05 / makefloat(sti(rChr.repair.class))) * makefloat(iSailRep));
	RepairGetTotal();
}

void RepairCalcThis(ref rChr, bool bIncrease)
{
	int iClicks = -100;
	if (bIncrease) iClicks = abs(iClicks);
	RepairGetLimit(rChr);
	ClickRepairHullArror(iClicks, rChr);
	ClickRepairMastArror(iClicks, rChr);
	RepairCalcSail();
	ClickRepairSailArror(iClicks, rChr);
}

void RepairCalcAll(bool bIncrease)
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

	LocUnLoadShips();
	LocLoadRepairShips(loadedLocation);
	PostEvent("RehostDone", REHOST_TIME, "l");
	RepairCalcSail();
	for (i = 0; i < repairNumShips; i++) ClickRepairSailArror(iClicks, GetCharacter(sti(repairShips[i].chrIndex)));
}

void RepairBegin()
{
	ref rChr;
	int i, iHullRep, iMastRep, iSailRep, iCurr, iShClass;
	bool bAnyRepair = false;

	for (i = 0; i < repairNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		if (sti(rChr.repair.hull) > 0 || sti(rChr.repair.mast) > 0 || sti(rChr.repair.sail) > 0)
		{
			bAnyRepair = true;
			break;
		}
	}
	if (!bAnyRepair) return;
	if (iTCost > 0 && sti(pchar.Money) < iTCost)
	{
		PlaySound("interface\knock.wav");
		return;
	}
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
			if (MakeInt(GetHullPercent(rChr)) >= 90) DeleteAttribute(rChr, "ship.blots");
		}
		if (iMastRep > 0)
		{
			AddCharacterExpToSkill(rChr, "Repair", (3 * iMastRep * (7 - iShClass) / 3.5));
			if (CheckAttribute(rChr, "repair.tmpMast")) DeleteAttribute(rChr, "repair.tmpMast");
		}
		if (iSailRep > 0)
		{
			AddCharacterExpToSkill(pchar, "Repair", (iSailRep * (7 - iShClass) / 3.5));
			iCurr = makeint(GetSailPercent(rChr));
			ProcessSailRepair(rChr, makefloat(iSailRep));
			SendMessage(&objSail, "l", MSG_SAIL_CALC);
			iSailRep = iCurr + iSailRep - makeint(GetSailPercent(rChr));
			ProcessSailRepair(rChr, makefloat(iSailRep));
		}
	}

	AddMoneyToCharacter(pchar, -iTCost);
	if (iTTime > 0)
	{
		bIsRepairingProcess = true;
		PlaySound("interface\repair_ship.wav");
		WaitDate("", 0, 0, 0, iTTime, 0);
		RecalculateJumpTable();
		RefreshLandTime();
		bIsRepairingProcess = false;
		Log_info(sTxTimeTotal + RepairWindowGetTime(iTTime, false));
	}
	ProcessExitCancel();
}

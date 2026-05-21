
ref xi_refCharacter;

float fPerkK; //бонусы от перков
int iHasPlanks, iHasCloth;
int repairScrollNum, iTPlanks, iTCloth, iTTime;
object objSail;

void InitInterface_R(string iniName, ref rChar)
{
	xi_refCharacter = pchar;
//StartAboveForm(true);
	//LAi_SetActorTypeNoGroup(pchar);

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak", "ProcessExitCancel", 0);
	SetEventHandler("exitCancel", "ProcessExitCancel", 0);
	SetEventHandler("ievnt_command", "ProcessCommandExecute", 0);
	SetEventHandler("frame","ProcessFrame", 1);


	//по этому ивенту понимаем, что можно пересчитать паруса после спавна кораблей
	//Так как должно пройти время для переноса парусов на новый хост
	SetEventHandler("RehostDone", "RepairCalcSail", 1);
	//Во время спавна парусов дамажим паруса на упавших мачтах
	SetEventHandler("DamageSailOnBrokenMast", "DoSailDamageForRepair", 0);

	LocUnLoadShips();
	if (!LocLoadRepairShips(loadedLocation))
	{
		DelEventHandler("RehostDone", "RepairNewCalcSail");
		DelEventHandler("DamageSailOnBrokenMast", "DoSailDamageForRepair");
		return;
	}


	SetCurrentNode("REPAIR_SHIPS_SCROLL");

	SetRepairData();

	//scroll -->
	RepairFillShipsScroll();
	SetRepairDescription();
	SetFormatedText("REPAIR_LOCATION_STR", GetCurLocationName());
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_LOCATION_STR", 5);
	//scroll <--

	SetNewGroupPicture("REPAIR_HULL_PIC", "REPAIR_STATE_ICONS", "Hull");
	SetNewGroupPicture("REPAIR_MAST_PIC", "REPAIR_STATE_ICONS", "Mast");
	SetNewGroupPicture("REPAIR_SAIL_PIC", "REPAIR_STATE_ICONS", "Sail");
	SetNewGroupPicture("REPAIR_HULL_P_PIC", "GOODS", "Planks");
	SetNewGroupPicture("REPAIR_MAST_P_PIC", "GOODS", "Planks");
	SetNewGroupPicture("REPAIR_SAIL_S_PIC", "GOODS", "SailCloth");

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

	//Lai_Fade("", "");

	ref rChr;
	bool bOk = false;
	for (int i = 0; i < locNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		RepairTempBrokeMast(rChr, -100); //Сломаем накликаные мачты заодно удалим атрибут brokenMast с парусов
		DeleteAttribute(rChr, "repair");
	}
	iTPlanks = 0; //Обнулим глобальные переменные на всякий случай
	iTCloth = 0;
	iTTime = 0;

	LocUnLoadShips(); // <-- огоньки удаляются тут, иначе ночью вылет
	// восстановим огоньки -->
	if (LoadSegment("sea_ai\ShipLights.c"))
	{
		InitShipLights();
		UnloadSegment("sea_ai\ShipLights.c");
	}
	CreateEntity(&ShipLights, "ShipLights");
	LayerAddObject(EXECUTE, &ShipLights, 0);
	LayerAddObject(REALIZE, &ShipLights, -1);
	LayerAddObject(SEA_SUNROAD, &ShipLights, -1);
	// <--
	LocLoadShips(loadedlocation);

	// сменить EntityId с SHIP на Player для pchar, иначе после выхода сообщения будут отправляться в SHIP, а не в Character
/*	for (int i = 0; i < locNumShips; i++)
	{	//на случай, если компаньоны смогут быть аборжажниками
		rChr = GetCharacter(sti(&locShips[i].chrIndex));
	}*/
	if (!SendMessage(pchar, "las", MSG_SHIP_SET_CHARACTER_EID, pchar, pchar.model.entity))
		trace("ERROR: shipyard MSG_SHIP_SET_CHARACTER_EID has returned false");

	interfaceResultCommand = RC_INTERFACE_REPAIR;
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
	string sNode = GetCurrentNode();
	string attributeName;
	int iTemp;

	if (sNode == "REPAIR_SHIPS_SCROLL")
	{
		iTemp = xi_refCharacter.index;
		repairScrollNum = sti(GameInterface.REPAIR_SHIPS_SCROLL.current);
		//Переключить персонажа
		attributeName = "pic" + its(repairScrollNum + 1);
		if (!CheckAttribute(&GameInterface, "REPAIR_SHIPS_SCROLL." + attributeName)) return;
		xi_refCharacter = &characters[sti(GameInterface.REPAIR_SHIPS_SCROLL.(attributeName).companionIndex)];
		if (xi_refCharacter.index == iTemp) return; //чтобы не вызывать в каждом кадре

		SetRepairDescription(); //обновить имена и портреты
		RepairGetTotal(); //Для кнопок
	}
}

void SetRepairData()
{
	ref rChr;
	iTTime = 0; //глобальные
	iTPlanks = 0;
	iTCloth = 0;
	iHasPlanks = GetSquadronGoods(pchar, GOOD_PLANKS);
	iHasCloth = GetSquadronGoods(pchar, GOOD_SAILCLOTH);

	//HardCoffee бонусы от перков TODO: возможно есть смысл добавить бонусы от скилов? Но тогда надо будет балансить ремонт в море
	fPerkK = 1.0;
	if (CheckOfficersPerk(pchar, "Shipbuilder"))
	{
		fPerkK = fPerkK * (0.75 - 0.01 * GetParamPageBonus("Shipbuilder")); // evganat - энциклопедия
	}
	else if (CheckOfficersPerk(pchar, "Builder"))
	{
		fPerkK = fPerkK * 0.9;
	}

	//Установим атрибуты - они нужны для сохранения выбранных значений ремонта при переключении компаньонов в интерфейсе
	for (int i = 0; i < locNumShips; i++)
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
	GameInterface.REPAIR_SHIPS_SCROLL.current = 0;
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, "REPAIR_SHIPS_SCROLL", -1);
}

void SetRepairDescription() //имена и портреты
{
	string sFirst, sLast;

	SetNewPicture("REPAIR_MCHR_PICTURE", "interfaces\portraits\256\face_" + its(xi_refCharacter.FaceId) + ".tga");

	sFirst = GetFirstName(xi_refCharacter); sLast = GetLastName(xi_refCharacter);
	if (sFirst == "" || sLast == "") SetFormatedText("REPAIR_NAME_STR", GetFullName(xi_refCharacter));
	else SetFormatedText("REPAIR_NAME_STR", sFirst + "\n" + sLast); //Принудительный перенос фамилии на новую строку
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_NAME_STR", 5);

	//Предварительная стоимость ремонта
	ref rChr;
	int iNeedPlanks = 0;
	int iNeedCloth = 0;
	for (int i = 0; i < locNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		iNeedPlanks += makeint((makefloat(100 - MakeInt(GetHullPercent(rChr))) * GetHullPPPShore(rChr) + 0.9));
		iNeedPlanks += (sti(rChr.repair.mast_max) - sti(rChr.repair.mast_cur)) * GetMastMPPShore(rChr);
		iNeedCloth += makeint((makefloat(100 - MakeInt(GetSailPercent(rChr))) * GetSailSPPShore(rChr) + 0.9));
	}

	SetFormatedText("REPAIR_SUPPLES_TEXT", XI_ConvertString("RepairShoreSupples") +": " +GetStrSmallRegister(XI_ConvertString("Planks")) +" " +iHasPlanks +", " +GetStrSmallRegister(XI_ConvertString("Sailcloth")) +" " +iHasCloth);
	SetFormatedText("REPAIR_NEEDS_TEXT", XI_ConvertString("RepairShoreNeed") +": " +GetStrSmallRegister(XI_ConvertString("Planks")) +" " +iNeedPlanks +", " +GetStrSmallRegister(XI_ConvertString("Sailcloth")) +" " +iNeedCloth);
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
	iTPlanks = 0;
	iTCloth = 0;

	for (int i = 0; i < locNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		iTTime = iTTime + sti(rChr.repair.hull_time) + sti(rChr.repair.mast_time) + sti(rChr.repair.sail_time);
		iTPlanks = iTPlanks + sti(rChr.repair.hull_cost) + sti(rChr.repair.mast_cost);
		iTCloth = iTCloth + sti(rChr.repair.sail_cost);

		RepairGetLimit(rChr); //для кнопок
		if (rChr.repair.calcThis == "1" && rChr.id != xi_refCharacter.id) bCalcAll = true;
	}

	RepairGetLimit(xi_refCharacter); //для обновления надписей после отработки предыдущего RepairGetLimit()

	if (iTTime > 0 || iTPlanks > 0 || iTCloth > 0)
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
	string sHullLim, sMastLim, sSailLim;
	int iTempLim, iHullLim, iMastLim, iSailLim;

	int iHullCur = MakeInt(GetHullPercent(rChr));
	int iMastMax = sti(rChr.repair.mast_max);
	int iMastCur = sti(rChr.repair.mast_cur);
	int iMastTemp = GetCurrMastsQuantity(rChr); //так как мачты будут восстанавливаться при нажатии стрелки
	int iSailCur = MakeInt(GetSailPercent(rChr));

	bool bSwitch = false;
	bool bCurr = false;
	if (rChr.id == xi_refCharacter.id) bCurr = true; //надписи обновляем только для корабля, выбранного в шып-скроле

	//HULL	//Максимум корпуса зависит от количества досок
	sHullLim = "";
	iTempLim = iHasPlanks - iTPlanks + sti(rChr.repair.hull_cost); //Вычтим стоимость корпуса, чтобы при прибалени процента максимум не менялся
	iTempLim = iTempLim / GetHullPPPShore(rChr);
	iHullLim = iHullCur + iTempLim;
	if (iHullLim > 100) iHullLim = 100;
	else if (bCurr) sHullLim = "(" + XI_ConvertString("NeedPlanks") + ")";

	rChr.repair.HullLim = iHullLim;

	//MAST	//Максимум мачт зависит от корпуса и бабла
	sMastLim = "";
	//С начала считаем корпус
	iMastLim = makeint(iMastMax * (iHullCur + sti(rChr.repair.hull)) / 90); // 90 - это минимальное сотояние корпуса для всех мачт
	if (iMastLim > iMastMax) iMastLim = iMastMax;
	else if (iMastLim < iMastCur) iMastLim = iMastCur;
	if (bCurr && iMastLim < iMastMax) sMastLim = "(" + XI_ConvertString("NeedHull") + ")";
	//Затем считаем доски
	iTempLim = iHasPlanks - iTPlanks + sti(rChr.repair.mast_cost);
	iTempLim = iTempLim / GetMastMPPShore(rChr);
	//сравним с лимитом по корпусу, равно нужно для правильного отображения надписи
	if (iTempLim + iMastCur <= iMastLim)
	{
		iMastLim = iTempLim + iMastCur;
		if (bCurr && iMastLim != iMastMax) sMastLim = "(" + XI_ConvertString("NeedPlanks") + ")";
	}

	rChr.repair.MastLim = iMastLim;

	//SAIL	//максимум зависит от количества мачт и бабла
	//считаем мачты
	iSailLim = sti(rChr.ship.SailQuantity);
	if (iSailLim < iSailCur) iSailLim = iSailCur;
	if (iSailLim > 100) iSailLim = 100;
	else if (bCurr) sSailLim = "(" + XI_ConvertString("NeedMast") + ")";
	//считаем парусину
	iTempLim = iHasCloth - iTCloth + sti(rChr.repair.sail_cost);
	iTempLim = iTempLim / GetSailSPPShore(rChr);
	iTempLim = iSailCur + iTempLim;
	//сравним с лимитом по мачтам для правильного отображения надписи
	if (bCurr && iTempLim <= iSailLim) sSailLim = "(" + XI_ConvertString("NeedSailcloth") + ")";
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

	//HULL ************
	//в sHullLim уже записано чего не хватает
	iTempLim = sti(xi_refCharacter.repair.HullLim);
	iCurr = MakeInt(GetHullPercent(xi_refCharacter));
	iRepair = iCurr + sti(xi_refCharacter.repair.hull);

	//Слева
	SetFormatedText("REPAIR_HULL_L_STR", XI_ConvertString("Condition") + its(iCurr) + "%");

	if (iTempLim < 100)
	{
		if (iTempLim == iRepair) //если нельзя восстановить, красим в красный цвет
		{
			sHullLim = ColorText(xi_refCharacter.repair.HullLim + "%", "contra") + "\n" + ColorText(sHullLim, "contra");
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_H", 8, 0, argb(255, 255, 196, 196));
		}
		else sHullLim = xi_refCharacter.repair.HullLim + "%" + "\n" + sHullLim;
	}
	else sHullLim = ColorText(xi_refCharacter.repair.HullLim + "%", "lightblue");

	//Убрать инфу о пределах, если полностью починено
	if (100 != iCurr) AddLineToFormatedText("REPAIR_HULL_L_STR", " " + XI_ConvertString("Limits") + sHullLim);

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_HULL_L_STR", 5);

	//центр
	SetFormatedText("REPAIR_QTY_H", its(iRepair) + "%");
	if (iRepair == 100)
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_H", 8, 0, argb(255, 128, 255, 255));

	//Справа
	SetFormatedText("REPAIR_HULL_R_STR", XI_ConvertString("RepairCost") +"\n" +GetStrSmallRegister(XI_ConvertString("PlanksAcc")) +" " +FindQtyString(sti(xi_refCharacter.repair.hull_cost))
		+ "\n" + XI_ConvertString("RepairTime") +"\n" +RepairWindowGetTime(sti(xi_refCharacter.repair.hull_time), false));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_HULL_R_STR", 5);

	//MAST ************
	iTempLim = sti(xi_refCharacter.repair.MastLim);
	iRepair = GetCurrMastsQuantity(xi_refCharacter); // так как мачты будут временно чиниться при нажатии стрелки
	iCurr = sti(xi_refCharacter.repair.mast_cur);
	int iMastMax = sti(xi_refCharacter.repair.mast_max);

	//Слева
	SetFormatedText("REPAIR_MAST_L_STR", XI_ConvertString("Condition") + xi_refCharacter.repair.mast_cur + "/" + xi_refCharacter.repair.mast_max);
	if (iTempLim == iRepair && iTempLim != iMastMax)
	{
		//Красим в красный
		sMastLim = ColorText(xi_refCharacter.repair.MastLim + "/" + xi_refCharacter.repair.mast_max, "contra") + "\n" + ColorText(sMastLim, "contra");
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_M", 8, 0, argb(255, 255, 196, 196));
	}
	else if (iTempLim == iMastMax) sMastLim = ColorText(xi_refCharacter.repair.MastLim + "/" + xi_refCharacter.repair.mast_max, "lightblue");
	else sMastLim = xi_refCharacter.repair.MastLim + "/" + xi_refCharacter.repair.mast_max + "\n" + sMastLim;

	if (iCurr != iMastMax) //убрать инфу о пределах
		AddLineToFormatedText("REPAIR_MAST_L_STR", " " + XI_ConvertString("Limits") + sMastLim);

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_MAST_L_STR", 5);

	//Центр
	SetFormatedText("REPAIR_QTY_M", its(iRepair) + "/" + xi_refCharacter.repair.mast_max);
	if (iRepair == iMastMax)
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_M", 8, 0, argb(255, 128, 255, 255));

	//Справа
	SetFormatedText("REPAIR_MAST_R_STR", XI_ConvertString("RepairCost") + "\n" +GetStrSmallRegister(XI_ConvertString("PlanksAcc")) +" " +FindQtyString(sti(xi_refCharacter.repair.mast_cost))
		+ "\n" + XI_ConvertString("RepairTime") + "\n" + RepairWindowGetTime(sti(xi_refCharacter.repair.mast_time), false));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_MAST_R_STR", 5);

	//SAIL ************
	iTempLim = sti(xi_refCharacter.repair.SailLim);
	iCurr = makeint(GetSailPercent(xi_refCharacter));
	iRepair = iCurr + sti(xi_refCharacter.repair.sail);

	//Слева
	SetFormatedText("REPAIR_SAIL_L_STR", XI_ConvertString("Condition") + its(iCurr) + "%");

	if (iTempLim < 100)
	{
		if (iTempLim == iRepair)
		{
			sSailLim = ColorText(xi_refCharacter.repair.SailLim + "%", "contra") + "\n" + ColorText(sSailLim, "contra");
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_S", 8, 0, argb(255, 255, 196, 196));
		}
		else sSailLim = xi_refCharacter.repair.SailLim + "%" + "\n" + sSailLim;
	}
	else sSailLim = ColorText(xi_refCharacter.repair.SailLim + "%", "lightblue");

	if (100 != iCurr) AddLineToFormatedText("REPAIR_SAIL_L_STR", " " + XI_ConvertString("Limits") + sSailLim);
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_SAIL_L_STR", 5);

	//Центр
	SetFormatedText("REPAIR_QTY_S", its(iRepair) + "%");
	if (iRepair == 100)
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_QTY_S", 8, 0, argb(255, 128, 255, 255));

	//Справа
	SetFormatedText("REPAIR_SAIL_R_STR", XI_ConvertString("RepairCost") + "\n" + GetStrSmallRegister(XI_ConvertString("Sailcloth")) +" " +FindQtyString(sti(xi_refCharacter.repair.sail_cost))
		+ "\n" + XI_ConvertString("RepairTime") + "\n" + RepairWindowGetTime(sti(xi_refCharacter.repair.sail_time), false));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "REPAIR_SAIL_R_STR", 5);

	//total info
	SetFormatedText("REPAIR_COST_T_TEXT", XI_ConvertString("RepairCostTShore") +": " +GetStrSmallRegister(XI_ConvertString("Planks")) +" " +iTPlanks +", " +GetStrSmallRegister(XI_ConvertString("Sailcloth")) +" " +iTCloth);
	SetFormatedText("REPAIR_TIME_T_TEXT", XI_ConvertString("RepairTimeT") + RepairWindowGetTime(iTTime, false));
}

//клики по стрелкам -->
void ClickRepairHullArror(int add, ref rChr)
{
	int iShip = GetCharacterShipType(rChr);
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

	float fHullRep = makefloat(iHullRep);
	rChr.repair.hull_cost = makeint(fHullRep * GetHullPPPShore(rChr) + 0.9);
	rChr.repair.hull_time = makeint((HULL_REPAIR_YARD_TIME * 2.0 * 0.05 / makefloat(sti(rChr.repair.class) + 2)) * fHullRep * fPerkK);

	RepairGetTotal();
	//Пересчитаем накликаные мачты, с учётом пересчитанных пределов, если уменьшим корпус
	ClickRepairMastArror(0, rChr);
}

void ClickRepairMastArror(int add, ref rChr)
{
	int iShip = GetCharacterShipType(rChr);
	int iMastRep = sti(rChr.repair.mast);
	int iMastMax = sti(rChr.repair.mast_max);
	int iMastTemp = GetCurrMastsQuantity(rChr);
	int iMastCur = sti(rChr.repair.mast_cur);
	int iMastLim = sti(rChr.repair.MastLim);
	int iOneCost = GetMastMPPShore(rChr);
	if (add > 0)
	{
		//trace(rChr.id +" iMastMax " +iMastMax +" iMastTemp = " +iMastTemp +" iMastCur " +iMastCur +" iMastLim " +iMastLim);
		if (add > iMastLim - iMastTemp) add = iMastLim - iMastTemp;
		if (add == 0) return;
		if (iMastTemp + add <= iMastLim)
		{
			LocUnLoadShips();
			RepairTempRepairMast(rChr, add);
			LocLoadRepairShips(loadedLocation);
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
			LocUnLoadShips();
			RepairTempBrokeMast(rChr, add);
			LocLoadRepairShips(loadedLocation);
			iMastRep += add;
		}
	}
	rChr.repair.mast = iMastRep; //для подсчёта времени и стоимости
	rChr.repair.mast_cost = its(iOneCost * iMastRep);
	if (iMastMax < 1) rChr.repair.mast_time = 0;
	else rChr.repair.mast_time = makeint((MAST_REPAIR_YARD_TIME * 2.0 * 0.5 / makefloat(sti(rChr.repair.class) + 5)) * makefloat(iMastRep) * fPerkK);
	EnableFailedSails(rChr); //Изменили мачты - удалим атрибуты с парусов, которые нельзя было поставить
	PostEvent("RehostDone", REHOST_TIME, "l"); //по этому ивенту понимаем, что можно пересчитать паруса
	// RepairGetLimit считать после ивента
}

void ClickRepairSailArror(int add, ref rChr)
{
	int iShip = sti(rChr.repair.type);
	int iSailCur = makeint(GetSailPercent(rChr));
	int iSailRep = sti(rChr.repair.sail);
	int iSailLim = sti(rChr.repair.SailLim);
	float fOneCost = GetSailSPPShore(rChr);
	//trace("add = " +add +" iSailLim = " +iSailLim +" iSailCur = " +iSailCur +" iSailRep = " +iSailRep);
	if (add > 0)
	{
		if (iHasCloth >= iTCloth + makeint(fOneCost * add)) iSailRep += add;
		else iSailRep += makeint(makefloat(iHasCloth - iTCloth) / fOneCost); //на сколько хватит
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

	float fSailRep = makefloat(iSailRep);
	rChr.repair.sail_cost = makeint(fSailRep * fOneCost + 0.9);
	rChr.repair.sail_time = makeint((SAIL_REPAIR_YARD_TIME * 2.0 * 0.05 / makefloat(sti(rChr.repair.class) + 2)) * fSailRep * fPerkK);
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
	for (int i = 0; i < locNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));
		RepairCalcThis(rChr, bIncrease);
	}
}

void RepairBegin() //Начинаем ремонт по кнопке Ремонт
{
	ref rChr;
	int i, iHullRep, iMastRep, iSailRep, iCurr;
	int iShClass;
	//Идём по всем кораблям так как заранее не известно какие корабли накликали
	for (i = 0; i < locNumShips; i++)
	{
		rChr = GetCharacter(sti(repairShips[i].chrIndex));

		iShClass = sti(rChr.repair.class);
		iHullRep = sti(rChr.repair.hull);
		iMastRep = sti(rChr.repair.mast);
		iSailRep = sti(rChr.repair.sail);

		if (iHullRep > 0)
		{
			//HardCoffee TODO: экспа начисляется как на верфи. Может есть смысл добавить, так как чинимся сами?
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
			iCurr = GetSailPercent(rChr);
			ProcessSailRepair(rChr, makefloat(iSailRep));
			//костыль так так ProcessSailRepair прибавляет к дамагу парусов дамаг верёвок -->
			SendMessage(&objSail, "l", MSG_SAIL_CALC);
			iSailRep = iCurr + iSailRep - GetSailPercent(rChr);
			ProcessSailRepair(rChr, makefloat(iSailRep));
			//<--
		}
		//Удалять атрибут rChr.repair ненадо, он удалится во время выхода
	}

	RemoveCharacterGoods(pchar, GOOD_PLANKS, iTPlanks);
	RemoveCharacterGoods(pchar, GOOD_SAILCLOTH, iTCloth);

	if (iTTime > 0)
	{
		bIsRepairingProcess = true;
		//bQuestCheckProcessFreeze = true;
		//PlaySound("interface\repair_ship.wav")
		WaitDate("", 0, 0, 0, iTTime, 0);
		RecalculateJumpTable();
		RefreshLandTime();

		bIsRepairingProcess = false;
		//bQuestCheckProcessFreeze = false;

		Log_info(XI_ConvertString("RepairTimeT") + RepairWindowGetTime(iTTime, false));
		//notification(sTemp, "Repair");
		Lai_MethodDelay("RepairReloadShore", 0.2);
	}

	ProcessExitCancel();
	//LAi_Fade("", "");
}

// количество досок на один процент починки
float GetHullPPPShore(ref _refCharacter)
{
	float ret = 8 - sti(_refCharacter.repair.class);

	float HPpercent = GetCharacterShipHP(_refCharacter) / 700.0;

	if (HPpercent > ret) ret = HPpercent;

	return ret * fPerkK;
}

// количество досок на одну мачту
int GetMastMPPShore(ref _refCharacter)
{
	float ret = 8 - sti(_refCharacter.repair.class);

	ret *= 10.0;

	return makeint(ret * fPerkK);
}

// количество парусины на один процент починки
float GetSailSPPShore(ref _refCharacter)
{
	float ret = 8 - sti(_refCharacter.repair.class);

	return ret * fPerkK;
}

//Sith, mitrokosta меню ожидания в таверне.
//Добавлены варианты проматывания времени. Выведена информация до какого времени отдыхаем.
int iHourWait = 1;
bool days = false;
bool minutes = false;

void InitInterface(string iniName)
{
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);
	StartAboveForm(true);
	SetEventHandler("frame", "ProcessFrame", 0);
	SetEventHandler("ievnt_command", "ProcCommand", 0);
	SetEventHandler("exitcancel", "ExitCancel", 0);
	SetEventHandler("eSlideChange", "ProcSlideChange", 0);
	SetEventHandler("RefreshVariables", "RefreshVariables", 0);

	string sDate = " ";
	sDate = GetDateString();
	string sTime;
	sTime = GetTimeString();
	SetFormatedText("CURRENT_DATE_CAPTION", sDate + " " + sTime);

	SetVariable();
	SetTimeSlider();
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "HOURS_SLIDE", 2, 11);
	SetCurrentNode("HOURS_SLIDE");
}

void ProcessFrame()
{
	string sDate, sTime;
	int hour = sti(worldMap.date.hour);
	int minute = sti(worldMap.date.min);
	bool addDays = true;

	if (SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 1))
	{
		days = false;
		minutes = false;
		SetSelectable("HOURS_SLIDE", false);
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HOURS_SLIDE", 0, 0);
		SetFormatedText("TIME_TEXT", " ");
		SetFormatedText("RESTTIME_TEXT", "");
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));
		sTime = GetTimeStringEx(0, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
	}

	if (SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 2))
	{
		days = false;
		minutes = false;
		SetSelectable("HOURS_SLIDE", false);
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HOURS_SLIDE", 0, 0);
		SetFormatedText("TIME_TEXT", " ");
		if (hour < 7) addDays = false;
		SetFormatedText("RESTTIME_TEXT", "");
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));
		sTime = GetTimeStringEx(7, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
	}

	if (SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 3))
	{
		days = false;
		minutes = true;
		SetSelectable("HOURS_SLIDE", true);
	}
	if (SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 4))
	{
		days = false;
		minutes = false;
		SetSelectable("HOURS_SLIDE", true);
	}
	if (SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 5))
	{
		days = true;
		minutes = false;
		SetSelectable("HOURS_SLIDE", true);
	}
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch (nodName)
	{
		case "HOURS_SLIDE":
			if (comName == "downstep")
			{
				if (GetSelectable("OK_BTN"))
					SetCurrentNode("OK_BTN");
				else
					SetCurrentNode("CANCEL_BTN");
			}
		break;

		case "OK_BTN":
			if (comName == "activate" || comName == "click")
				WaitProcess(iHourWait);

			if (comName == "rightstep")
				SetCurrentNode("CANCEL_BTN");

			if (comName == "upstep")
				SetCurrentNode("HOURS_SLIDE");
		break;

		case "CANCEL_BTN":
			if (comName == "leftstep")
			{
				if (GetSelectable("OK_BTN"))
					SetCurrentNode("OK_BTN");
			}

			if (comName == "upstep")
				SetCurrentNode("HOURS_SLIDE");
		break;
	}
}

//Sith обновляем вывод инфы, когда кликаем по чекбоксам
void RefreshVariables()
{
	SetTimeSlider();
	string sDate, sTime;
	int hour = sti(worldMap.date.hour);
	int minute = sti(worldMap.date.min);
	int addDays;

	if (days == true)
	{
		addDays = iHourWait;
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));
		sTime = GetTimeStringEx(hour, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
		SetFormatedText("TIME_TEXT", FindRussianIdiomsString(iHourWait, "day"));
	}
	else if (minutes == true)
	{
		int addMin = minute + iHourWait;
		minute = addMin % 60;
		if (addMin > 59) hour = (hour + 1) % 24;
		addDays = hour / 24;
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));
		sTime = GetTimeStringEx(hour, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
		SetFormatedText("TIME_TEXT", FindRussianIdiomsString(iHourWait, "minute"));
	}
	else
	{
		if (SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 4))
		{
			addDays = (hour + iHourWait) / 24;
			hour = (hour + iHourWait) % 24;
			sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));
			sTime = GetTimeStringEx(hour, minute);
			SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
			SetFormatedText("TIME_TEXT", FindRussianIdiomsString(iHourWait, "hour"));
		}
		else SetFormatedText("TIME_TEXT", "");
	}
}
//Sith крутим вертим часы и дни
void ProcSlideChange()
{
	string sCurDayTime, sDate, sTime;
	string sNodeName    = GetEventData();
	int iVal        = GetEventData(); // int GameInterface.nodes.<node_name>.value
	float fVal        = GetEventData(); // float GameInterface.nodes.<node_name>.value
	sCurDayTime = GetDayTime();

	int hour = sti(worldMap.date.hour);
	int minute = sti(worldMap.date.min);
	int addDays;

	SetFormatedText("RESTTIME_TEXT", "");
	// Проверяем на галки дней или часов. Учитываем сменяемость суток, дней, месяцев, годов
	if (sNodeName != "HOURS_SLIDE") return;
	//галка дней
	if (days == true)
	{
		iHourWait = 1 + iVal;
		addDays = iHourWait;
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));
		sTime = GetTimeStringEx(hour, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
		SetFormatedText("TIME_TEXT", FindRussianIdiomsString(iHourWait, "day"));
	}
	//галка минуты
	else if (minutes == true)
	{
		iHourWait = 1 + iVal;
		addDays = 0;
		int addMin = minute + iHourWait;
		minute = addMin % 60;
		if (addMin > 59)
		{
			hour = (hour + 1) % 24;
			if (hour == 0) addDays = 1;
		}
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));
		sTime = GetTimeStringEx(hour, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
		SetFormatedText("TIME_TEXT", FindRussianIdiomsString(iHourWait, "minute"));
	}
	else
	//галка часы
	{
		iHourWait = 1 + iVal;
		addDays = (hour + iHourWait) / 24;
		hour = (hour + iHourWait) % 24;
		sDate = GetDateStringEx(GetAddingDataYear(0, 0, addDays), GetAddingDataMonth(0, 0, addDays), GetAddingDataDay(0, 0, addDays));
		sTime = GetTimeStringEx(hour, minute);
		SetFormatedText("RESTTIME_TEXT", sDate + " " + sTime);
		SetFormatedText("TIME_TEXT", FindRussianIdiomsString(iHourWait, "hour"));
	}
}

void SetTimeSlider()
{
	bool inTavern = (CheckAttribute(loadedLocation, "fastreload")) && (pchar.location == loadedLocation.fastreload + "_tavern");
	if (days == true)
	{
		GameInterface.nodes.HOURS_SLIDE.value = 1;
		GameInterface.nodes.HOURS_SLIDE.maxlimit = 6;

		SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "HOURS_SLIDE", 1, 6);
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HOURS_SLIDE", 0, 0.1);
	}
	else if (minutes == true)
	{
		GameInterface.nodes.HOURS_SLIDE.value = 30;
		GameInterface.nodes.HOURS_SLIDE.maxlimit = 59;

		SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "HOURS_SLIDE", 1, 59);
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HOURS_SLIDE", 0, 0.5);
	}
	else
	{
		GameInterface.nodes.HOURS_SLIDE.value = 12;
		GameInterface.nodes.HOURS_SLIDE.maxlimit = 23;

		SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "HOURS_SLIDE", 1, 23);
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HOURS_SLIDE", 0, 0.5);
	}
}

void SetVariable()
{
	int color1 = argb(255, 128, 128, 128);
	int color2 = argb(255, 196, 196, 196);
	string sCurDayTime;
	sCurDayTime = GetDayTime();
	bool inTavern = (CheckAttribute(loadedLocation, "fastreload")) && (pchar.location == loadedLocation.fastreload + "_tavern");
	// только в таверне
	if (!inTavern)
	{
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 5, 1);
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "DAYS_INFO", 8, 0, Color1);
	}
	else
	{
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 5, 5, 0);
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "DAYS_INFO", 8, 0, Color2);
	}
}

void WaitProcess(int _iHour)
{
	int iCurrentTime = sti(environment.time);
	int iAddtime = _iHour;
	int iOldDay = GetDataDay();
	if (SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 1))
	{
		if (iCurrentTime < 24) iAddtime = 24 - iCurrentTime;
	}

	if (SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TIME_CHECK", 3, 2))
	{
		if (iCurrentTime >= 21) iAddTime = 24 - iCurrentTime + 7;
		if (iCurrentTime < 7) iAddTime = 7 - iCurrentTime;
		if (iCurrentTime >= 7 && iCurrentTime < 21) iAddTime = 24 + 7 - iCurrentTime;
	}

	TEV.WaitHours = iAddtime;

	if (days == true)
	{
		DoQuestFunctionDelay("WaitNextDays", 0.1);
	}
	else if (minutes == true)
	{
		DoQuestFunctionDelay("WaitNextMinutes", 0.1);
	}
	else
	{
		DoQuestFunctionDelay("WaitNextHours", 0.1);
	}

	ExitCancel();
}

void IDoExit(int exitCode, bool bClear)
{
	EndAboveForm(true);

	DelEventHandler("frame", "ProcessFrame");
	DelEventHandler("ievnt_command", "ProcCommand");
	DelEventHandler("exitcancel", "ExitCancel");
	DelEventHandler("eSlideChange", "ProcSlideChange");
	DelEventHandler("RefreshVariables", "RefreshVariables");
	interfaceResultCommand = exitCode;
	EndCancelInterface(bClear);
}

void ExitCancel()
{
	IDoExit(RC_INTERFACE_TAVERN_WAIT, true);
}

void CanWait()
{
	if (iHourWait <= 0 || chrDisableReloadToLocation)
		SetSelectable("OK_BTN", false);
	else
		SetSelectable("OK_BTN", true);
}

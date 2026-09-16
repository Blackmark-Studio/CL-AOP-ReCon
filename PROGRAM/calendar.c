//--------------------------------------------------------------------
// Environment section
//--------------------------------------------------------------------
#define DAY_TIME_NIGHT		"Night"
#define DAY_TIME_MORNING	"Morning"
#define DAY_TIME_DAY		"Day"
#define DAY_TIME_EVENING	"Evening"

float	GetTime()		{ return stf(Environment.time); }
float	GetHour()		{ return stf(Environment.date.hour); }
float	GetMinute()		{ return stf(Environment.date.min); }
float	GetSecond()		{ return stf(Environment.date.sec); }
int		GetDataYear()	{ return sti(Environment.date.year); }
int		GetDataMonth()	{ return sti(Environment.date.month); }
int		GetDataDay()	{ return sti(Environment.date.day); }

void SetDayTime(string name)
{
	switch(name)
	{
		case DAY_TIME_NIGHT:	SetCurrentTime(0,1);	break;
		case DAY_TIME_MORNING:	SetCurrentTime(6,1);	break;
		case DAY_TIME_DAY:		SetCurrentTime(11,1);	break;
		case DAY_TIME_EVENING:	SetCurrentTime(19,1);	break;
	}
}

string GetDayTime()
{
	if (GetTime() < 6.0)	return DAY_TIME_NIGHT;
	if (GetTime() < 11.0)	return DAY_TIME_MORNING;
	if (GetTime() < 19.0)	return DAY_TIME_DAY;
	if (GetTime() < 24.0)	return DAY_TIME_EVENING;

	return DAY_TIME_NIGHT;
}

bool IsDay()
{
	return GetTime() > 6.0 && GetTime() < 23.0;
}

bool IsLoginTime()
{
	return GetTime() > 6.0 && GetTime() < 21.99;
}

// > високосный ли год по григорианскому правилу?
bool IsLeapYear(int year)
{
	return or(year % 400 == 0, year % 100 != 0 && year % 4 == 0);
}

int GetMonthDays(int month, int year)
{
	while (month > 12)
	{
		month -= 12;
	}

	switch(month)
	{
		case 1:		return 31;	break;
		case 2:
			if (IsLeapYear(year))
					return 29;
			else
					return 28;
		break;
		case 3:		return 31;	break;
		case 4:		return 30;	break;
		case 5:		return 31;	break;
		case 6:		return 30;	break;
		case 7:		return 31;	break;
		case 8:		return 31;	break;
		case 9:		return 30;	break;
		case 10:	return 31;	break;
		case 11:	return 30;	break;
		case 12:	return 31;	break;
	}

	Trace("ERROR GetMonthDays > " + month + " month is not relevant");
	return 30;
}

// KZ > вынес в отдельную функцию: общий расчёт будущей даты от текущей (с учётом високосных лет)
void GetAddingData(int addYear, int addMonth, int addDay, ref outYear, ref outMonth, ref outDay)
{
	int nextDay = GetDataDay()+addDay;
	int curMonth = GetDataMonth();
	int curYear = GetDataYear();

	while (GetMonthDays(curMonth, curYear) < nextDay)
	{
		nextDay = nextDay - GetMonthDays(curMonth, curYear);
		curMonth++;

		if (curMonth>12)
		{
			curMonth -= 12;
			curYear++;
		}
	}

	int nextMonth = curMonth+addMonth;
	int nextYear = curYear+addYear;

	while (12 < nextMonth)
	{
		nextMonth = nextMonth - 12;
		nextYear++;
	}

	outYear  = nextYear;
	outMonth = nextMonth;
	outDay   = nextDay;
}

int GetAddingDataYear(int addYear, int addMonth, int addDay)
{
	int outYear, outMonth, outDay;
	GetAddingData(addYear, addMonth, addDay, &outYear, &outMonth, &outDay);
	return outYear;
}

int GetAddingDataMonth(int addYear, int addMonth, int addDay)
{
	int outYear, outMonth, outDay;
	GetAddingData(addYear, addMonth, addDay, &outYear, &outMonth, &outDay);
	return outMonth;
}

int GetAddingDataDay(int addYear, int addMonth, int addDay)
{
	int outYear, outMonth, outDay;
	GetAddingData(addYear, addMonth, addDay, &outYear, &outMonth, &outDay);
	return outDay;
}

int GetAddingTimeDay(int hour, int minute)
{
	float curtime = GetTime();
	float nexttime = curtime+hour+(makefloat(minute)/60.0);
	int addingDays = 0;

	while(nexttime>=24.0)
	{
		nexttime = nexttime - 24.0;
		addingDays++;
	}

	return addingDays;
}

int AddTimeToCurrent(int hour, int minute)
{
	float curtime = GetTime();
	float nexttime = curtime+hour+(makefloat(minute)/60.0);
	int addingDays = 0;

	while(nexttime>=24.0)
	{
		nexttime = nexttime - 24.0;
		addingDays++;
	}

	AddDataToCurrent(0,0,addingDays);

	Environment.time = nexttime;
	Environment.date.hour = makeint(nexttime);
	worldMap.date.hour = makeint(nexttime);
	nexttime = (nexttime - stf(Environment.date.hour))*60.0;
	Environment.date.min = makeint(nexttime);
	worldMap.date.min = makeint(nexttime);
    Weather.Time.time = GetTime(); // новая погода
    
	return addingDays; // boal вернуть число дней, чтоб понять, что новый наступил
}

void AddDataToCurrent(int addYear, int addMonth, int addDay)
{
	int nextYear, nextMonth, nextDay;
	GetAddingData(addYear, addMonth, addDay, &nextYear, &nextMonth, &nextDay);

	Environment.date.year = nextYear;
	Environment.date.month = nextMonth;
	Environment.date.day = nextDay;
	worldMap.date.year = nextYear;
	worldMap.date.month = nextMonth;
	worldMap.date.day = nextDay;

	if (addYear!=0 || addMonth!=0 || addDay!=0)
		PostEvent("NextDay",500); // fix boal отложить время, чтоб успеть выйти из форм
}

// > порядковый номер дня от стартового года игры (STARTGAME_YEAR) с учётом високосных лет для точной разницы дат
int DateToEpochDays(int year, int month, int day)
{
	int days = 0;
	int y, m;

	for (y = STARTGAME_YEAR; y < year; y++)
	{
		if (IsLeapYear(y))
			days += 366;
		else
			days += 365;
	}

	for (m = 1; m < month; m++)
		days += GetMonthDays(m, year);

	return days + day - 1;
}

// timeUnit = "year", "month", "day", "hour", "minute"
int GetPastTime(string timeUnit, int pastYear, int pastMonth, int pastDay, float pastTime, int currentYear, int currentMonth, int currentDay, float currentTime)
{
	float dtime = currentTime - pastTime;
	int dyear = currentYear - pastYear;
	int dmonth = currentMonth - pastMonth;
	int dday = currentDay - pastDay;

	if (dtime < 0.0)
	{
		dday--;
		dtime = dtime + 24.0;
	}

	if (dday < 0)
	{
		dmonth--;
		if (pastMonth > 1)
			dday = dday + GetMonthDays(pastMonth, pastYear);
		else
			dday = dday + GetMonthDays(12, pastYear);
	}

	if (dmonth < 0)
	{
		dyear--;
		dmonth = dmonth + 12;
	}

	if (dyear < 0) return 0;
	if (timeUnit == "year") return dyear;

	if (timeUnit == "month")
	{
		return dmonth + dyear * 12;
	}
	
	// > day / hour / minute — точная разница в днях с учётом високосных лет (раньше было dyear*365 + суммирование месяцев по pastYear, что теряло високосные дни на интервалах через год)
	float elapsedHours = makefloat(DateToEpochDays(currentYear, currentMonth, currentDay) - DateToEpochDays(pastYear, pastMonth, pastDay)) * 24.0 + (currentTime - pastTime);
	if (elapsedHours < 0.0) return 0;

	if (timeUnit=="hour")   return makeint(elapsedHours);
	if (timeUnit=="minute") return makeint(elapsedHours * 60.0);

	return makeint(elapsedHours / 24.0); // "day" и значение по умолчанию
}

void SetCurrentTime(int hour, int minutes)
{
	Environment.date.hour = makefloat(hour);
	Environment.date.min = makefloat(minutes);
	Environment.time = makefloat(hour) + makefloat(minutes)/60.0;
	worldMap.date.hour = makefloat(hour);
	worldMap.date.min = makefloat(minutes);
}

// KZ > проверка прошедшего времени (minute, hour, day, month, year) с момента события sEvent; читается из TEV.Timer.(sEvent); если вернёт 100000, то значит события ещё не было
int GetEventPastTime(string sEvent, string sType)
{
	sType = GetStrSmallRegister(stripblank(sType));
	
	if (!StrHasStr(sType, "year,month,day,hour,minute", true))
		return 0;
	
	aref arParam; makearef(arParam, TEV.Timer.(sEvent));
	
	if (CheckAttribute(&TEV, "Timer." + sEvent + ".control_year"))
		return GetPastTime(sType, sti(arParam.control_year), sti(arParam.control_month), sti(arParam.control_day), stf(arParam.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	
	return 100000;
}

// KZ > запомнить время (minute, hour, day, month, year) события sEvent; пишется в TEV.Timer.(sEvent)
void SaveEventStartTime(string sEvent)
{
	aref arQ; makearef(arQ, TEV.Timer.(sEvent));
	
	arQ.control_day = GetDataDay();
	arQ.control_month = GetDataMonth();
	arQ.control_year = GetDataYear();
	arQ.control_time = GetTime();
}

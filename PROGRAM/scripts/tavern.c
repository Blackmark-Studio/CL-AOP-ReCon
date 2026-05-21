// SLiB Новый файл для ВМЛ, все от К3 потерто
void TavernWaitDate(string date)
{
	int iTime, iAddTime, iTmp;
	iTime = sti(environment.time);
	if (date == "wait_day")
	{
		if (iTime >= 21) iAddTime = 24 - iTime + 7;
		if (iTime < 7) iAddTime = 7 - iTime;
		// boal 03.03.05 -->
		if (iTime >= 7 && iTime < 21) iAddTime = 24  + 7 - iTime;
		// boal <--
		StoreDayUpdate();
	}
	else
	{
		if (iTime < 24) iAddtime = 24 - iTime;
	}
	LAi_Fade("", "");
	WaitDate("",0,0,0,iAddtime,5);
	//navy --> сон снимает алкоголь... 2 часа = кружка
	LAi_DawnWaitAlcoholState(iAddtime * 900);
	//navy <--
	RecalculateJumpTable();
	// boal -->
	RefreshWeather();
	RefreshLandTime();
	// boal <--
}

void TavernWaitDate_LSC(string date)
{
	int iTime, iAddTime, iTmp;
	iTime = sti(environment.time);
	if (date == "wait_day")
	{
		if (iTime >= 21) iAddTime = 24 - iTime + 7;
		if (iTime < 7) iAddTime = 7 - iTime;
		// boal 03.03.05 -->
		if (iTime >= 7 && iTime < 21) iAddTime = 24  + 7 - iTime;
		// boal <--
		StoreDayUpdate();
	}
	else
	{
		if (iTime < 24) iAddtime = 23 - iTime;
	}
	WaitDate("",0,0,0,iAddtime,5);
	//navy --> сон снимает алкоголь... 2 часа = кружка
	LAi_DawnWaitAlcoholState(iAddtime * 900);
	//navy <--

	DoQuestReloadToLocation("FleuronTavern",  "quest", "bed", "restore_hp");
	RecalculateJumpTable();
	// boal -->
	RefreshWeather();
	RefreshLandTime();
	// boal <--
}

void TavernWaitDateEx(int number)
{
	int iTime, iAddTime, iTmp;
	iTime = sti(environment.time);
	if (iTime >= 21) iAddTime = 24 - iTime + number;
	if (iTime < number) iAddTime = number - iTime;
	if (iTime >= number && iTime < 21) iAddTime = 24  + number - iTime;
	StoreDayUpdate();
	WaitDate("",0,0,0,iAddtime,0);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	CreateWeatherEnvironment();
}

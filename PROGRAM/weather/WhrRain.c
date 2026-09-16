object Rain;

void WhrDeleteRainEnvironment()
{
	if (isEntity(&Rain))
	{
		DeleteClass(&Rain);
	}
	DeleteAttribute(&Rain,"");
}

void WhrCreateRainEnvironment()
{
	bWeatherIsRain = false;

	if (!isEntity(&Rain))
	{
		CreateEntity(&Rain,"rain");
	}

	FillRainData(iCurWeatherNum,iBlendWeatherNum);
	Rain.isDone = "";

	if( sti(Rain.NumDrops) > 0 ) {bWeatherIsRain = true;}
}

void ClearRainEnvironment()
{
	if (!isEntity(&Rain))
	{
		CreateEntity(&Rain,"rain");
	}

	FillRainData(iCurWeatherNum,iBlendWeatherNum);
	Rain.NumDrops = 0.0;
	Rain.DropLength = 0.1;
	Rain.isDone = "";

	bWeatherIsRain = false;
}

void FillRainData(int nw1, int nw2)
{
	if( nw1 < 0 || nw1 >= MAX_WEATHERS ) {return;}

	aref aRain1; makearef(aRain1, Weathers[nw1].Rain);
	aref aRainbow1; makearef(aRainbow1, Weathers[nw1].Rainbow);

	Rain.Clear = ""; // > сигнал движку удалить частицы дождя
	DeleteAttribute(&Rain,"");

	if( nw2 < 0 )
	{
		Rain.NumDrops = Whr_GetLong(aRain1,"NumDrops");
		Rain.Color = Whr_GetColor(aRain1,"Color");
		Rain.DropLength = Whr_GetFloat(aRain1,"DropLength");
		Rain.Height = Whr_GetFloat(aRain1,"Height");
		Rain.Radius = Whr_GetFloat(aRain1,"Radius");
		Rain.Speed = Whr_GetFloat(aRain1,"Speed");
		Rain.Jitter = Whr_GetFloat(aRain1,"Jitter");
		Rain.WindSpeedJitter = Whr_GetFloat(aRain1,"WindSpeedJitter");
		Rain.TimeBlend = Whr_GetLong(aRain1,"TimeBlend");
		Rain.MaxBlend = Whr_GetLong(aRain1,"MaxBlend");

		Rain.RainDrops.DropsNearNum = Whr_GetLong(aRain1, "DropsNearNum");
		Rain.RainDrops.DropsFarNum = Whr_GetLong(aRain1, "DropsFarNum");
		Rain.RainDrops.DropsNearRadius = Whr_GetFloat(aRain1, "DropsNearRadius");
		Rain.RainDrops.DropsFarRadius = Whr_GetFloat(aRain1, "DropsFarRadius");
		Rain.RainDrops.DropsLifeTime = Whr_GetFloat(aRain1, "DropsLifeTime");
		Rain.RainDrops.DropsSize = Whr_GetFloat(aRain1, "DropsSize");
		Rain.RainDrops.DropsColor = Whr_GetLong(aRain1, "DropsColor");
		Rain.RainDrops.DropsTexture = Whr_GetString(aRain1, "DropsTexture");

		Rain.Rainbow.Enable = Whr_GetLong(aRainbow1,"Enable");
		Rain.Rainbow.Texture = Whr_GetString(aRainbow1,"Texture");

	}
	else
	{
		aref aRain2; makearef(aRain2, Weathers[nw2].Rain);
		aref aRainbow2; makearef(aRainbow2, Weathers[nw2].Rainbow);
		float fBlend = stf(Environment.Time) - sti(Environment.Time);

		Rain.NumDrops = Whr_BlendLong( fBlend, Whr_GetLong(aRain1,"NumDrops"), Whr_GetLong(aRain2,"NumDrops") );
		Rain.Color = Whr_BlendColor( fBlend, Whr_GetColor(aRain1,"Color"), Whr_GetColor(aRain2,"Color") );
		Rain.DropLength = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"DropLength"), Whr_GetFloat(aRain2,"DropLength") );
		Rain.Height = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"Height"), Whr_GetFloat(aRain2,"Height") );
		Rain.Radius = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"Radius"), Whr_GetFloat(aRain2,"Radius") );
		Rain.Speed = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"Speed"), Whr_GetFloat(aRain2,"Speed") );
		Rain.Jitter = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"Jitter"), Whr_GetFloat(aRain2,"Jitter") );
		Rain.WindSpeedJitter = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1,"WindSpeedJitter"), Whr_GetFloat(aRain2,"WindSpeedJitter") );
		Rain.TimeBlend = Whr_BlendLong( fBlend, Whr_GetLong(aRain1,"TimeBlend"), Whr_GetLong(aRain2,"TimeBlend") );
		Rain.MaxBlend = Whr_BlendLong( fBlend, Whr_GetLong(aRain1,"MaxBlend"), Whr_GetLong(aRain2,"MaxBlend") );

		Rain.RainDrops.DropsNearNum = Whr_BlendLong( fBlend, Whr_GetLong(aRain1, "DropsNearNum"), Whr_GetLong(aRain2, "DropsNearNum"));
		Rain.RainDrops.DropsFarNum = Whr_BlendLong( fBlend, Whr_GetLong(aRain1, "DropsFarNum"), Whr_GetLong(aRain2, "DropsFarNum"));
		Rain.RainDrops.DropsNearRadius = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1, "DropsNearRadius"), Whr_GetFloat(aRain2, "DropsNearRadius"));
		Rain.RainDrops.DropsFarRadius = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1, "DropsFarRadius"), Whr_GetFloat(aRain2, "DropsFarRadius"));
		Rain.RainDrops.DropsLifeTime = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1, "DropsLifeTime"), Whr_GetFloat(aRain2, "DropsLifeTime"));
		Rain.RainDrops.DropsSize = Whr_BlendFloat( fBlend, Whr_GetFloat(aRain1, "DropsSize"), Whr_GetFloat(aRain2, "DropsSize"));
		Rain.RainDrops.DropsColor = Whr_GetLong(aRain1, "DropsColor"); //Whr_BlendColor( fBlend, Whr_GetColor(aRain1, "DropsColor"), Whr_GetColor(aRain2, "DropsColor"));
		Rain.RainDrops.DropsTexture = Whr_GetString(aRain1, "DropsTexture");

		Rain.Rainbow.Enable = Whr_GetLong(aRainbow1,"Enable") || Whr_GetLong(aRainbow2,"Enable");
		Rain.Rainbow.Texture = Whr_GetString(aRainbow1,"Texture");

	}
}

void MoveRainToLayers(int sExecuteLayer, int sRealizeLayer)
{
	LayerDelObject(EXECUTE,&Rain);
	LayerDelObject(REALIZE,&Rain);
	LayerDelObject(SEA_EXECUTE,&Rain);
	LayerDelObject(SEA_REALIZE,&Rain);

	LayerAddObject(sExecuteLayer, &Rain, 65537);
	LayerAddObject(sRealizeLayer, &Rain, 65537);
}

void ShowRain(int bShow)
{
	SendMessage(&Rain,"ll",1,bShow);
}

// генератор дождей
void Whr_RainGenerator()
{
	int iMonth = GetDataMonth();

	WeatherParams.Rain 			= false;
	WeatherParams.Rain.ThisDay 	= false;

	WeatherParams.Fog 			= false;
	WeatherParams.Fog.ThisDay 	= false;

	int chance = 100;

	// дожди
	switch(iMonth)
	{
		case 1:  chance = 10; 	break;
		case 2:  chance = 5; 	break;
		case 3:  chance = 5; 	break;
		case 4:  chance = 5; 	break;
		case 5:  chance = 15; 	break; // начало сезона дождей
		case 6:  chance = 20; 	break;
		case 7:  chance = 30; 	break;
		case 8:  chance = 45; 	break;
		case 9:  chance = 90; 	break; // высокий шанс ежедневного дождя
		case 10: chance = 85; 	break; // высокий шанс ежедневного дождя
		case 11: chance = 35; 	break;
		case 12: chance = 15; 	break; // сухой сезон
	}

	if(CheckAttribute(&TEV, "debug_rain") || drand(100) < chance)
	{
		if(drand(100) < 30)
		{
			WeatherParams.Rain.StartTime = 2 + rand(13) + rand(59)/60.0; 	// время старта с минутами
			WeatherParams.Rain.Duration  = 180 + rand(360); 				// затяжной дождь
		}
		else
		{
			WeatherParams.Rain.StartTime = 2 + rand(19) + rand(59)/60.0;	// время старта с минутами
			WeatherParams.Rain.Duration  = 60 + rand(120); 					// короткий дождь
		}
		// > Не даём дождю уйти за полночь, иначе он застревает до суточной регенерации
		float fRainEnd = stf(WeatherParams.Rain.StartTime) + stf(WeatherParams.Rain.Duration)/60.0;
		if (fRainEnd > 24.0) WeatherParams.Rain.Duration = makeint((24.0 - stf(WeatherParams.Rain.StartTime)) * 60.0);
		WeatherParams.Rain.ThisDay 		= true;								// дождь сегодня будет
		WeatherParams.Rain.Type			= rand(1);							// тип дождя
		WeatherParams.Rain.year 		= GetDataYear();
		WeatherParams.Rain.month 		= GetDataMonth();
		WeatherParams.Rain.day 			= GetDataDay();
		WeatherParams.Rain.time 		= stf(WeatherParams.Rain.StartTime);

		Log_TestInfo("Дождь начнется в " + WeatherParams.Rain.time + " Выбран дождь : " + (sti(WeatherParams.Rain.Type) + 1));
		Log_TestInfo("Продолжительность дождя: " + WeatherParams.Rain.Duration + " мин.");

		if(drand(100) < 40) WeatherParams.Rain.IsLightingActive = true;		// гроза будет или нет
		else				WeatherParams.Rain.IsLightingActive = false;
	}
	else
	{
		Log_TestInfo("Дождя сегодня не будет");
	}
}

// ****************************************************************************************
// Mett: настройки дождя
// Ugeen : + куча моих правок (дождь может начаться в любое время часа, правка логики стадий)
// ****************************************************************************************

// настройки дождя
// 0 стадия - дождя нет, заканчиваем дождь, убираем молнии и звук дождя, запускем радугу
// 1 стадия - дождь усиливается
// 2 стадия - дождь льет как из ведра
// 3 стадия - дождь идёт на убыль
// по завершению мы возвращаемся на 0 стадию
void Whr_SetRainExt1(int iCurWeatherNum, int iBlendWeatherNum, bool bRain)
{
	float 	fTime = GetTime();
	float 	fTmp, fDuration;
	int 	iTmp;

	if(!CheckAttribute(&WeatherParams, "Rain.StartTime")) return;

	fDuration	= stf(WeatherParams.Rain.Duration)/60.0;
	fTmp 		= stf(WeatherParams.Rain.StartTime) + fDuration;

	if(bRain)
	{
		iTmp = 3; // > дождь кончался на ~80%, теперь идёт на убыль до реального конца
		if(fTime >= fTmp)														// 0 стадия - заканчиваем дождь
		{
			iTmp 					= 0;
			bRain 					= false;
			WeatherParams.Rain 		= false;
            WhrStopLightning();
            Weathers[iCurWeatherNum].Rainbow.Enable   = false;
			Log_TestInfo("Заканчиваем дождь. Время : " + fTime + " время остановки дождя : " + fTmp );
		}

		if(fTime < (stf(WeatherParams.Rain.StartTime) + 4 * (fDuration/5.0)))	iTmp = 3;	// 3 стадия - дождь идёт на убыль
		if(fTime < (stf(WeatherParams.Rain.StartTime) + 2 * (fDuration/3.0)))	iTmp = 2;	// 2 стадия - дождь льет как из ведра
		if(fTime < (stf(WeatherParams.Rain.StartTime) + fDuration/3.0) )		iTmp = 1;	// 1 стадия - дождь усиливается

		Log_TestInfo("Дождь - время : " + fTime + " время остановки дождя : " + fTmp + " стадия: " + iTmp);	//лог будет идти только во время дождя, чтоб не грузило

		switch(iTmp)
		{
			case 0:			// 0 стадия - дождя нет, заканчиваем дождь, убираем молнии и звук дождя, запускаем радугу
                WeatherParams.Rain 			= false;
                WhrStopLightning();
				TEV.Music.KeepPlaying = "";
                ResetSoundScheme(); //иначе звук дождя не прекращается
				DeleteAttribute(&TEV, "Music.KeepPlaying");
                Whr_SetRainSound(false, sti(Weathers[iCurWeatherNum].Night));
                Weathers[iCurWeatherNum].Rainbow.Enable   = false;
                Weathers[iCurWeatherNum].Rain.NumDrops 	= 0;
                DeleteAttribute(&WeatherParams, "Rain.StartTime");
                WeatherParams.SpecialFogChance = 90; //максимальный шанс генерации тумана
                Log_TestInfo("Стадия 0");
				WeatherParams.Rain.ThisDay = false;
				wRain = 0;
			break;

			case 1:		// 1 стадия - дождь усиливается
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 1500 + rand(2000);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 6 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
                WhrStopLightning();
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));	// звук
				Log_TestInfo("Стадия 1");
				wRain = 1;
			break;

			case 2:		// 2 стадия - дождь льет как из ведра
				if(CheckAttribute(&WeatherParams,"Rain.IsLightingActive") && sti(WeatherParams.Rain.IsLightingActive) == 1)
				{
					Log_TestInfo("Дождь : будут молнии");
					Weathers[iCurWeatherNum].Rainbow.Enable   			= false;
                    Weathers[iCurWeatherNum].Lightning.Enable 		    = true;
                    WhrStartLightning();
				}
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));	// звук
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 3500 + rand(1500);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 8 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
				Log_TestInfo("Стадия 2");
				wRain = 2;
			break;

			case 3:		// 3 стадия - дождь идёт на убыль
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 2500 + rand(1000);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 6 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));	// звук
                if(fTime > 7.0 && fTime < 20.0)
				{
					Weathers[iCurWeatherNum].Rainbow.Enable     = true;
                    Weathers[iCurWeatherNum].Rainbow.Texture 	= "weather\rainbow\rainbow.tga";
				}
                if(CheckAttribute(&WeatherParams,"Rain.IsLightingActive") && sti(WeatherParams.Rain.IsLightingActive) == 1)
				{
					Log_TestInfo("Дождь : будут молнии");
                    Weathers[iCurWeatherNum].Lightning.Enable 		    = true;
                    WhrStartLightning();
				}
				Log_TestInfo("Стадия 3");
				wRain = 1;
			break;
		}
		if(iTmp != 0)	// пока идёт дождь держим туман, не врубаем солнце
		{
			Whr_SetRainBlendWeather(iBlendWeatherNum, false);
		}
	}
	else	//начало дождя... если генератор не запущен...
	{
		if(CheckAttribute(&WeatherParams, "Rain.ThisDay") && sti(WeatherParams.Rain.ThisDay))
		{
			if(fTime >= stf(WeatherParams.Rain.StartTime) && fTime < fTmp)		// можем начинать
			{
				Whr_SetRainBlendWeather(iBlendWeatherNum, true); 				// Mett: интенсивность - лёгкий дождь
				WeatherParams.Rain = true;										// флаг "дождь"
                WhrStopLightning();
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));	// звук
                Weathers[iCurWeatherNum].Rainbow.Enable   = false;
				Log_TestInfo("Стартуем дождь. Стартовое время : " + stf(WeatherParams.Rain.StartTime) + " продолжительность : " + (stf(WeatherParams.Rain.Duration)/60.0));
			}
		}
	}
}

// второй вариант дождя
void Whr_SetRainExt2(int iCurWeatherNum, int iBlendWeatherNum, bool bRain)
{
	float 	fTime = GetTime();
	float 	fTmp, fDuration;
	int 	iTmp;

	if(!CheckAttribute(&WeatherParams, "Rain.StartTime")) return;

	fDuration	= stf(WeatherParams.Rain.Duration)/60.0;
	fTmp 		= stf(WeatherParams.Rain.StartTime) + fDuration;

	if (bRain)
	{
		iTmp = 3; // > дождь кончался на ~71%; теперь идёт на убыль до реального конца
		if(fTime >= fTmp)														// 5 стадия - заканчиваем дождь
		{
			iTmp 					= 4;
			bRain 					= false;
			WeatherParams.Rain 		= false;
            WhrStopLightning();
            Weathers[iCurWeatherNum].Rainbow.Enable   = false;
			Log_TestInfo("Заканчиваем дождь. Время : " + fTime + " время остановки дождя : " + fTmp );
		}

		if(fTime < (stf(WeatherParams.Rain.StartTime) + 5 * (fDuration)/7.0)) iTmp = 3;// четвертая стадия, дождь идёт на убыль
		if(fTime < (stf(WeatherParams.Rain.StartTime) + 4 * (fDuration)/7.0)) iTmp = 2;// третья стадия, дождь идёт на убыль
		if(fTime < (stf(WeatherParams.Rain.StartTime) + 3 * (fDuration)/7.0)) iTmp = 1;// вторая стадия, дождь льет как из ведра
		if(fTime < (stf(WeatherParams.Rain.StartTime) + 1 * (fDuration)/5.0)) iTmp = 0;// первая стадия, дождь усиливается

		Log_TestInfo("Дождь - время : " + fTime + " время остановки дождя : " + fTmp + " стадия: " + iTmp);	//лог будет идти только во время дождя, чтоб не грузило

		switch(iTmp)	//в зависимости от заданной стадия моделируем дождь, всего 4 стадий (0-3)
		{
			case 0:	//стадия 1: дождь усиливается
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 1500 + rand(2000);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 4 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
				Weathers[iCurWeatherNum].Rainbow.Enable   				= false;
                WhrStopLightning();
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));	// звук
				Log_TestInfo("Стадия 1");
				wRain = 1;
			break;
			case 1:	//стадия 2: дождь льет как из ведра
				if(CheckAttribute(&WeatherParams,"Rain.IsLightingActive") && sti(WeatherParams.Rain.IsLightingActive) == 1)
				{
					Log_TestInfo("Дождь : будут молнии");
                    Weathers[iCurWeatherNum].Rainbow.Enable   			= false;
                    Weathers[iCurWeatherNum].Lightning.Enable 		    = true;
                    WhrStartLightning();
				}
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 3500 + rand(1500);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 4 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));	// звук
				Log_TestInfo("Стадия 2");
				wRain = 2;
			break;
			case 2:	//стадия 3: дождь идёт на убыль
                if(CheckAttribute(&WeatherParams,"Rain.IsLightingActive") && sti(WeatherParams.Rain.IsLightingActive) == 1)
				{
					Weathers[iCurWeatherNum].Rainbow.Enable   			= false;
					Log_TestInfo("Дождь : будут молнии");
                    Weathers[iCurWeatherNum].Lightning.Enable 		    = true;
                    WhrStartLightning();
				}
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 2500 + rand(1000);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 4 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));	// звук
				Log_TestInfo("Стадия 3");
				wRain = 1;
			break;
			case 3:	//стадия 4: дождь идёт на убыль
                WhrStopLightning();
				Weathers[iCurWeatherNum].Rain.NumDrops 					= 1000 + rand(500);
				Weathers[iCurWeatherNum].Rain.DropLength 				= 4 + rand(8);
				Weathers[iCurWeatherNum].Rain.Color 					= argb(0,23,23,23);
                if(fTime > 7.0 && fTime < 20.0)
				{
					Weathers[iCurWeatherNum].Rainbow.Enable     = true;
                    Weathers[iCurWeatherNum].Rainbow.Texture 	= "weather\rainbow\rainbow.tga";
				}
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));	// звук
				Log_TestInfo("Стадия 4");
				wRain = 1;
			break;
			case 4:	//стадия 5: заканчиваем дождь, убираем молнии и звук дождя
                WeatherParams.Rain = false;
                Weathers[iCurWeatherNum].Lightning.Enable 	= false;
                WhrStopLightning();
				TEV.Music.KeepPlaying = "";
                ResetSoundScheme(); //иначе звук дождя не прекращается
				DeleteAttribute(&TEV, "Music.KeepPlaying");
                Whr_SetRainSound(false, sti(Weathers[iCurWeatherNum].Night));
                Weathers[iCurWeatherNum].Rainbow.Enable   = false;
                Weathers[iCurWeatherNum].Rain.NumDrops 	= 0;
                DeleteAttribute(&WeatherParams, "Rain.StartTime");
                WeatherParams.SpecialFogChance = 90; //максимальный шанс генерации тумана
                Log_TestInfo("Стадия 5");
				WeatherParams.Rain.ThisDay = false;
				wRain = 0;
			break;
		}
		if(iTmp != 4)	//пока идёт дождь держим туман, не врубаем солнце
		{
			Whr_SetRainBlendWeather(iBlendWeatherNum, false); 	//Mett: без дождя
		}
	}
	else	//начало дождя... если генератор не запущен...
	{	//начинаем...
		if(CheckAttribute(&WeatherParams, "Rain.ThisDay") && sti(WeatherParams.Rain.ThisDay))
		{
			if(fTime >= stf(WeatherParams.Rain.StartTime) && fTime < fTmp)		// можем начинать
			{
				Whr_SetRainBlendWeather(iBlendWeatherNum, true); 				// Mett: интенсивность - лёгкий дождь
				WeatherParams.Rain = true;										// флаг "дождь"
                WhrStopLightning();
				Weathers[iCurWeatherNum].Rainbow.Enable   = false;
				Whr_SetRainSound(true, sti(Weathers[iCurWeatherNum].Night));	// звук
				Log_TestInfo("Стартуем дождь. Стартовое время : " + stf(WeatherParams.Rain.StartTime) + " продолжительность : " + (stf(WeatherParams.Rain.Duration)/60.0));
			}
		}
	}
}

//общие настройки погоды в дождь
void Whr_SetRainBlendWeather(int iBlendWeatherNum, bool bRain)
{
	if (iBlendWeatherNum < 0) return;

	// > Реконструкция бэкапа пресета после дождя (дождь меняет LightingLm/InsideBack, вызывая косяки с освещением),
	if (!CheckAttribute(&Weathers[iBlendWeatherNum], "Bak"))
	{
		Weathers[iBlendWeatherNum].Bak.LightingLm = Weathers[iBlendWeatherNum].LightingLm;
		Weathers[iBlendWeatherNum].Bak.InsideBack = Weathers[iBlendWeatherNum].InsideBack;
	}

	if(bRain)	//идёт лёгкий дождь?
	{
		Weathers[iBlendWeatherNum].Rain.NumDrops 	= 500 + rand(500);
		Weathers[iBlendWeatherNum].Rain.DropLength 	= 4 + rand(8);
		Weathers[iBlendWeatherNum].Rain.Color 		= argb(0,23,23,23);
	}

	if(wRain == 1)
	{
		Weathers[iBlendWeatherNum].LightingLm				= "storm";
	}
	if(wRain == 2)
	{
		Weathers[iBlendWeatherNum].LightingLm				= "storm";
		Weathers[iBlendWeatherNum].InsideBack 				= "n";
	}
}

// генератор туманов
void Whr_FogGenerator(ref rCurrentHourWeather, ref rNextHourWeather)
{
    //если дождь, шторм, туман, то генерить нечего. расходимся
    if (Whr_CheckSpecialLandFog() || Whr_CheckRain() || Whr_CheckStorm()) return;
    //если вдруг нет нужных атрибутов, то заполняем
    if (!CheckAttribute(&WeatherParams, "SpecialFogChance") || !CheckAttribute(&WeatherParams, "SpecialFogBlock") || !CheckAttribute(pchar, "SpecialFogHours"))
    {
        WeatherParams.SpecialFogChance = 5;
        WeatherParams.SpecialFogBlock = 0;
        SaveCurrentQuestDateParam("SpecialFogHours");
    }
    //если нет специального атрибута в текущий и следующий час, то туман не генерим, просто снижаем шанс.
    if (!CheckAttribute(rCurrentHourWeather, "SpecialLandFog") && !CheckAttribute(rNextHourWeather, "SpecialLandFog"))
    {
        Whr_RecalculateFogChance();
        WeatherParams.SpecialFogBlock = 0;
        return;
    }
    if (sti(WeatherParams.SpecialFogBlock)) return;

	// рассчет шанса тумана по утрам и вечерам в локациях
	if (CheckAttribute(&TEV, "debug_fog") || drand(100) < sti(WeatherParams.SpecialFogChance))
	{
		WeatherParams.Fog 			= true;
		WeatherParams.Fog.ThisDay 	= true;
		//определяем что это за туман, вечерний или утренний
		if (GetTime() <= 12.0) WeatherParams.Fog.Type = 0;
		else WeatherParams.Fog.Type = 1;

		if(sti(WeatherParams.Fog.Type))	        Log_TestInfo("Будет вечерний туман в локациях. Шанс " + WeatherParams.SpecialFogChance + "%");
		else									Log_TestInfo("Будет утренний туман в локациях. Шанс " + WeatherParams.SpecialFogChance + "%");
		WeatherParams.SpecialFogChance = 5; //шанс последующего появления понижаем
		SaveCurrentQuestDateParam("SpecialFogHours");
	}
	else
	{
	    string sTemp = "Вечернего";
	    if (GetTime() <= 12.0) sTemp = "Утреннего";
		Log_TestInfo(sTemp + " тумана сегодня не будет. Шанс " + WeatherParams.SpecialFogChance + "%");
	    Whr_RecalculateFogChance();
	    WeatherParams.SpecialFogBlock = 1;
	}
}

void Whr_RecalculateFogChance()
{
    int pastHours = GetQuestPastTimeParam("SpecialFogHours");
    if (pastHours > 0)
    {
        int specialFogChance = sti(WeatherParams.SpecialFogChance);
        if (specialFogChance <= 10) specialFogChance = 5;
        else specialFogChance -= 10 * pastHours;
        WeatherParams.SpecialFogChance = specialFogChance;
        SaveCurrentQuestDateParam("SpecialFogHours");
    }
}
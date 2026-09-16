#include "weather\WhrUtils.c" //кодировка UTF-8 Konstrush
#include "weather\WhrLightning.c"
#include "weather\WhrRain.c"
#include "weather\WhrSea.c"
#include "weather\WhrSky.c"
#include "weather\WhrSun.c"
#include "weather\WhrTornado.c"
#include "weather\WhrAstronomy.c"
#include "weather\WhrSeaPresets.c"

#define WIND_NORMAL_POWER		20.0

#define MAX_WEATHERS   34

object	Weather, WeatherParams, WhrCommonParams;
int		iNextWeatherNum = -1;
int		iCurWeatherNum = -1;
int		iBlendWeatherNum = -1;
int		iCurWeatherHour = -1;
int		wRain = 0;
bool	bCurWeatherStorm = false;
int		iTotalNumWeathers = 0;
string	sLightingPath = "day";
string	sLmLightingPath = "day";
string	sInsideBack = "";
string	sNewExecuteLayer, sNewRealizeLayer;
string	sCurrentFog;
string  sBlendedFog;
string  sPreset;
float	fWeatherDelta = 0.0;
float	fWeatherAngle, fWeatherSpeed;
float	fFogDensity;
int		iShadowDensity[2];
int		sunIsShine = true;
bool	bWeatherLoaded = false;
bool	bWeatherIsNight = false;
bool	bWeatherIsLight = false;
bool	bWeatherIsRain = false;
bool	bWeatherIsStorm = false;
int		iUpdateReducer = 0;	// evganat - уменьшение частоты изменения скорости ветра

object Weathers[MAX_WEATHERS];

extern int InitWeather();

#event_handler("EWhr_GetWindAngle", "Whr_GetWindAngle");
#event_handler("EWhr_GetWindSpeed", "Whr_GetWindSpeed");
#event_handler("EWhr_GetShadowDensity", "Whr_GetShadowDensity");
#event_handler("EWhr_GetFogDensity", "Whr_GetFogDensity");
#event_handler("WeatherTimeUpdate", "Whr_TimeUpdate" );

void SetNextWeather(string sWeatherID)
{
	// find weather
	iNextWeatherNum = -1;
	for (int i=0; i<MAX_WEATHERS; i++)
	{
		if (!CheckAttribute(&Weathers[i], "id")) { continue; }
		if (Weathers[i].id == sWeatherID)
		{
			iNextWeatherNum = i;
			if (TestMode())
			{
				Trace("iNextWeatherNum = " + iNextWeatherNum);
				Log_SetStringToLog(ToUpper(XI_ConvertString("Weather")) + ": " + Weathers[i].Lighting);
			}
			return;
		}
	}
}

void Whr_ResetShadowDensity()
{
	iShadowDensity[0] = argb(255,96,96,96);
	iShadowDensity[1] = argb(255,96,96,64);
}

void WeatherInit()
{
	//DeleteAttribute(&WeatherParams,"");
	Whr_ResetShadowDensity();

	if (LoadSegment("weather\WhrInit.c"))
	{
		iTotalNumWeathers = InitWeather();
		UnloadSegment("weather\WhrInit.c");
	}
}

void DeleteWeatherEnvironment()
{
	iBlendWeatherNum = -1;
	if (isEntity(&Weather))
	{
		DeleteClass(&Weather);
	}
	DeleteAttribute(&Weather,"");
	//WeatherParams.Tornado = false; // включает-выключает торнадо на суше Hirurg39
	//DeleteAttribute(&WeatherParams,"");

	WhrDeleteRainEnvironment();
	WhrDeleteSkyEnvironment();
	WhrDeleteSunGlowEnvironment();
	WhrDeleteLightningEnvironment();
	WhrDeleteTornadoEnvironment();
	WhrDeleteSeaEnvironment();
	WhrDeleteAstronomyEnvironment();

	DelEventHandler(WEATHER_CALC_FOG_COLOR,"Whr_OnCalcFogColor");
	DelEventHandler("frame","Whr_OnWindChange");

	Whr_ResetShadowDensity();
	bWeatherLoaded = false;
}

aref GetCurrentWeather()
{
	//Boyer fix for when iCurWeatherNum = -1...borrowed from function Whr_LoadNextWeather(int nPlus)
	if (iCurWeatherNum < 0)
		iCurWeatherNum = iTotalNumWeathers - 1;
	//End fix
	aref arWeather;
	makearef(arWeather,Weathers[iCurWeatherNum]);
	return arWeather;
}

void CreateWeatherEnvironment()
{
	string sAttrName;
	string sSky = "";
	int iWeatherFound[MAX_WEATHERS];
	int iNumWeatherFound = 0;
	int iHour = MakeInt(GetHour());

	bool bWhrStorm = false;
	bool bWhrTornado = false;
	bool bRain = false;
	
	bWhrStorm = Whr_CheckStorm();
	if (CheckAttribute(&WeatherParams,"Tornado")) bWhrTornado = sti(WeatherParams.Tornado);

    if (CheckAttribute(&WeatherParams,"Rain") && !bWhrStorm) bRain = sti(WeatherParams.Rain); // в штормах своя специфика дождей

    if (bRain)
    {
        float fTmp = stf(WeatherParams.Rain.StartTime) + stf(WeatherParams.Rain.Duration)/60.0;
        if (GetTime() > fTmp)
        {
            bRain 						= false;
            WeatherParams.Rain 			= false;
            WeatherParams.Rain.ThisDay 	= false;
        }
    }

	if (iNextWeatherNum != -1)
	{
		iCurWeatherHour = iHour;
		iCurWeatherNum = iNextWeatherNum;
		iNextWeatherNum = -1;
		//Trace("Weather: used preset weather " + iCurWeatherNum);
	}
	else
	{
		// search weather for hour
		for (int i=0;i<MAX_WEATHERS;i++)
		{
			//navy --> чистим текущую погоду от остатков предыдущего дождя... иначе сохранненный дождь пойдет...
			//или нужно всю погоду инитить заново... но лучше наверно так.
			if (!bRain && sti(Weathers[i].Rain.NumDrops) > 0 && sti(Weathers[i].Rain.NumDrops) < 5100)
			{
				Weathers[i].Rain.NumDrops = 0;
				Weathers[i].Lightning.Enable = false;
			}
			if (CheckAttribute(&WeatherParams, "Rain.ThisDay") && !sti(WeatherParams.Rain.ThisDay) && CheckAttribute(&Weathers[i], "Bak")) 
			{
				// > Восстанавливаем оригинал после дождя. Реально дождь портит только LightingLm/InsideBack
				Weathers[i].LightingLm	= Weathers[i].Bak.LightingLm;
				Weathers[i].InsideBack	= Weathers[i].Bak.InsideBack;
				DeleteAttribute(&Weathers[i], "Bak");
			}
			if (!bRain) Weathers[i].Rainbow.Enable = false;
			//navy <--
			if (!CheckAttribute(&Weathers[i], "hour")) { continue; }
			if (CheckAttribute(&Weathers[i], "skip"))
			{
				if (sti(Weathers[i].skip)) { continue; }
			}

			bool bCanStorm = sti(Weathers[i].Storm);
			bool bCanTornado = sti(Weathers[i].Tornado);
			int iMin = sti(Weathers[i].Hour.Min);
			int iMax = sti(Weathers[i].Hour.Max);
			if (iMin == iMax && iMin != iHour) { continue; }
			if (iMin > iMax)
			{
				if (iHour < iMin && iHour > iMax) { continue; }
			}
			if (iMin < iMax)
			{
				if (iHour < iMin || iHour > iMax) { continue; }
			}
			if (bWhrStorm != bCanStorm) { continue; }
			if (bWhrTornado == true && bWhrTornado != bCanTornado && reload_location_index == -1) { continue; } //сухопутки без торнадо
			iWeatherFound[iNumWeatherFound] = i;
			iNumWeatherFound++;
		}

		// > Если по фильтру торнадо не нашлось ни одного пресета, повторяем поиск без него:
		// > иначе запасной вариант ниже ставит Weathers[0] (полночь) в любое время суток.
		if (iNumWeatherFound == 0 && bWhrTornado)
		{
			for (int iw=0;iw<MAX_WEATHERS;iw++)
			{
				if (!CheckAttribute(&Weathers[iw], "hour")) { continue; }
				if (CheckAttribute(&Weathers[iw], "skip"))
				{
					if (sti(Weathers[iw].skip)) { continue; }
				}
				int iMinT = sti(Weathers[iw].Hour.Min);
				int iMaxT = sti(Weathers[iw].Hour.Max);
				if (iMinT == iMaxT && iMinT != iHour) { continue; }
				if (iMinT > iMaxT)
				{
					if (iHour < iMinT && iHour > iMaxT) { continue; }
				}
				if (iMinT < iMaxT)
				{
					if (iHour < iMinT || iHour > iMaxT) { continue; }
				}
				if (bWhrStorm != sti(Weathers[iw].Storm)) { continue; }
				iWeatherFound[iNumWeatherFound] = iw;
				iNumWeatherFound++;
			}
			if (iNumWeatherFound > 0) Trace("Weather: tornado filter found nothing, fallback by hour = " + iHour);
		}

		iCurWeatherHour = iHour;

		if (iNumWeatherFound == 0)
		{
			Trace("Error: iNumWeatherFound = 0, for hour = " + iHour);
			iCurWeatherNum = 0;
		}
		else
		{
			iCurWeatherNum = iWeatherFound[rand(iNumWeatherFound-1)];
		}
	}

	int iCurLocation;
	int iTestWeather;
	bool bQuestlockWeather;
    float fGetTime = GetTime();

	bQuestlockWeather = false;
	sunIsShine = true;

	if(CheckAttribute(pchar, "location"))
	{
		iCurLocation = reload_location_index;
		if(iCurLocation != -1)
		{
			if(CheckAttribute(&locations[iCurLocation], "storm"))
			{
				bWhrStorm = 1;
			}
			if(CheckAttribute(&locations[iCurLocation], "tornado"))
			{
				bWhrTornado = 1;
			}
			//малый шторм в локациях
			if(CheckAttribute(&locations[iCurLocation], "alwaysStorm"))
			{
				if (GetTime() >= 6.0 && GetTime() < 10.0) locations[iCurLocation].QuestlockWeather = "Storm01_add";
				if (GetTime() >= 10.0 && GetTime() < 18.0) locations[iCurLocation].QuestlockWeather = "Storm02_add";
				if (GetTime() >= 18.0 && GetTime() < 22.0) locations[iCurLocation].QuestlockWeather = "Storm03_add";
				if (GetTime() >= 22.0 && GetTime() < 24.0) locations[iCurLocation].QuestlockWeather = "Storm04_add";
				if (GetTime() >= 0 && GetTime() < 6.0) locations[iCurLocation].QuestlockWeather = "Storm04_add";
				if (CheckAttribute(&locations[iCurLocation], "alwaysStorm.WaveHeigh")) locations[iCurLocation].MaxWaveHeigh = 1.7; //установим уровень воды
				bWhrStorm = 1;
			}
			//большой шторм в локациях
			if(CheckAttribute(&locations[iCurLocation], "alwaysStorm_2"))
			{
				if (GetTime() >= 6.0 && GetTime() < 10.0) locations[iCurLocation].QuestlockWeather = "Storm01";
				if (GetTime() >= 10.0 && GetTime() < 18.0) locations[iCurLocation].QuestlockWeather = "Storm02";
				if (GetTime() >= 18.0 && GetTime() < 22.0) locations[iCurLocation].QuestlockWeather = "Storm03";
				if (GetTime() >= 22.0 && GetTime() < 24.0) locations[iCurLocation].QuestlockWeather = "Storm04";
				if (GetTime() >= 0 && GetTime() < 6.0) locations[iCurLocation].QuestlockWeather = "Storm04";
				if (CheckAttribute(&locations[iCurLocation], "alwaysStorm_2.WaveHeigh")) locations[iCurLocation].MaxWaveHeigh = 1.7; //установим уровень воды
				bWhrStorm = 1;
			}
			if(CheckAttribute(&locations[iCurLocation], "QuestlockWeather"))
			{
				iTestWeather = FindWeather(locations[iCurLocation].QuestlockWeather);
				if(iTestWeather != -1)
				{
					iCurWeatherNum = iTestWeather;
					bQuestlockWeather = true;
					if (CheckAttribute(&locations[iCurLocation], "lockWeather") && locations[iCurLocation].lockWeather == "Inside")
					{
						sunIsShine = false; //выключить солнце
					}
				}
			}
		}
		if(iCurLocation == -1)
		{		
			iCurLocation = FindIsland(pchar.location);
			if(iCurLocation != -1)
			{
				if(CheckAttribute(&Islands[iCurLocation], "storm"))
				{
					bWhrStorm = 1;
				}
				if(CheckAttribute(&Islands[iCurLocation], "tornado"))
				{
					bWhrTornado = 1;
				}
				if(CheckAttribute(&Islands[iCurLocation], "alwaysStorm"))
				{
					if (GetTime() >= 6.0 && GetTime() < 10.0) Islands[iCurLocation].QuestlockWeather = "Storm01";
					if (GetTime() >= 10.0 && GetTime() < 18.0) Islands[iCurLocation].QuestlockWeather = "Storm02";
					if (GetTime() >= 18.0 && GetTime() < 22.0) Islands[iCurLocation].QuestlockWeather = "Storm03";
					if (GetTime() >= 22.0 && GetTime() < 24.0) Islands[iCurLocation].QuestlockWeather = "Storm04";
					if (GetTime() >= 0 && GetTime() < 6.0) Islands[iCurLocation].QuestlockWeather = "Storm04";
					bWhrStorm = 1;
				}
				if(CheckAttribute(&Islands[iCurLocation], "QuestlockWeather"))
				{
					iTestWeather = FindWeather(Islands[iCurLocation].QuestlockWeather);
					if(iTestWeather != -1)
					{
						iCurWeatherNum = iTestWeather;
						bQuestlockWeather = true;
					}
				}
			}
		}
	}

	if (!bQuestlockWeather)
	{
		iBlendWeatherNum = FindBlendWeather(iCurWeatherNum);
	}
	else
	{
		iBlendWeatherNum = -1; // залоченная погода
	}

	WeatherParams.Storm = bWhrStorm;
	bWeatherIsStorm = bWhrStorm;
	bCurWeatherStorm = bWhrStorm;

	//ставим погоду, сгенеренную в главном меню
	if (bMainMenu)
	{
		iTestWeather = sti(InterfaceStates.mainmenuweather);
		if(iTestWeather != -1)
		{
			iCurWeatherNum = iTestWeather;
			bQuestlockWeather = true;
		}
	}
	if (startGameWeather)
	{
		iTestWeather = sti(InterfaceStates.startGameWeather);
		if(iTestWeather != -1)
		{
			iCurWeatherNum = iTestWeather;
			bQuestlockWeather = true;
		}
		startGameWeather = false;
	}

	// create main module Weather
	DeleteAttribute(&Weather,"");
	if (!isEntity(&Weather))
	{
		CreateEntity(&Weather, "Weather");
	}

	aref aCurWeather = GetCurrentWeather();

	sLightingPath = Whr_GetString(aCurWeather,"Lighting");
	sLmLightingPath = Whr_GetString(aCurWeather,"LightingLm");
	sInsideBack = Whr_GetString(aCurWeather,"InsideBack");
	bWeatherIsNight = Whr_GetLong(aCurWeather,"Night");
	bWeatherIsLight = Whr_GetLong(aCurWeather,"Lights");

	if(CheckAttribute(pchar, "wind.angle"))
	{
		Weather.Wind.Angle = pchar.wind.angle;
		//DeleteAttribute(pchar, "wind.angle");
	}
	else
	{
		Weather.Wind.Angle = frand(PIm2);//  Блин!!! это не градусы!!!!! frand(180.0);//Whr_GetFloat(aCurWeather,"Wind.Angle");
		pchar.wind.angle = Weather.Wind.Angle;
	}

	if (CheckAttribute(pchar, "wind.speed"))
	{
		Weather.Wind.Speed = pchar.wind.speed;
		//DeleteAttribute(pchar, "wind.speed");
	}
	else
	{
		Weather.Wind.Speed = Whr_GetFloat(aCurWeather,"Wind.Speed");
		pchar.wind.speed = Weather.Wind.Speed;
	}

	pchar.quest.EraseWind.win_condition.l1 = "ExitFromSea";
	pchar.quest.EraseWind.win_condition = "EraseWind";

	sCurrentFog = "Fog";
    sBlendedFog = "Fog";

    if (CheckAttribute(&WeatherParams, "Fog.ThisDay") && sti(WeatherParams.Fog.ThisDay))
    {
        if (iBlendWeatherNum > -1)
        {
            if(CheckAttribute(&Weathers[iBlendWeatherNum],"SpecialLandFog") && (sti(WeatherParams.Fog.Type) == sti(Weathers[iBlendWeatherNum].SpecialLandFog.Type)))
            {
                if (Whr_CheckInsideLoc()) sBlendedFog = "Fog";
                else sBlendedFog = "SpecialLandFog";
            }
            else
            {
                sBlendedFog = "Fog";
            }
        }

        if(CheckAttribute(&Weathers[iCurWeatherNum],"SpecialLandFog") && (sti(WeatherParams.Fog.Type) == sti(Weathers[iCurWeatherNum].SpecialLandFog.Type)))
        {
            if (Whr_CheckInsideLoc()) sCurrentFog = "Fog";
            else sCurrentFog = "SpecialLandFog";
        }
        else
        {
            sCurrentFog = "Fog";
        }
    }
    bool isStorm = CheckAttribute(aCurWeather, "Storm") && sti(aCurWeather.Storm) == 1;
	if(CheckAttribute(&WeatherParams,"Rain") && Whr_isRainEnable() && !isStorm) // не для локаций, где низя дождить + не для штормов где своя специфика
	{
		if(CheckAttribute(&WeatherParams,"Rain.Type"))
		{
			if(sti(WeatherParams.Rain.Type) == 0)	Whr_SetRainExt1(iCurWeatherNum, iBlendWeatherNum, bRain);
			else									Whr_SetRainExt2(iCurWeatherNum, iBlendWeatherNum, bRain);
		}
		else
		{
			Whr_SetRainExt1(iCurWeatherNum, iBlendWeatherNum, bRain);
		}
	}

	WhrCreateSeaEnvironment();

    if (iBlendWeatherNum > -1) Whr_FogGenerator(&Weathers[iCurWeatherNum], &Weathers[iBlendWeatherNum]); //генератор туманов
	FillWeatherData(iCurWeatherNum, iBlendWeatherNum);

	if (iBlendWeatherNum < 0 || bQuestlockWeather) 
	{
		Weather.Time.time = GetTime();
		Weather.Time.speed = 350.0; // количество секунд на смену погоды
		Weather.Time.updatefrequence = 12; // количество обновлений на смену погоды
	} else {
		Weather.Time.time = GetTime();
		Weather.Time.speed = 450;
		Weather.Time.updatefrequence = 15; // количество обновлений на смену погоды
		if (bSeaActive && !bAbordageStarted)
		{
			if (iArcadeSails == 1)  // скорости в аркаде больше, время быстрее
			{
				Weather.Time.speed = 250; // количество секунд на смену погоды
				Weather.Time.updatefrequence = 10;
			}
		}
		else
		{ // суша
			Weather.Time.speed = 350;
			Weather.Time.updatefrequence = 12; // количество обновлений на смену погоды
		}

		if (CheckAttribute(PChar, "questTemp.TimeLock"))
            Weather.Time.speed = 99999.0; // лочим ~!~
	}

	Weather.isDone = "";

	SetEventHandler(WEATHER_CALC_FOG_COLOR,"Whr_OnCalcFogColor",0);
	SetEventHandler("frame","Whr_OnWindChange",0);

	fFogDensity = stf(Weather.Fog.Density);

	fWeatherDelta = 0.0;
	fWeatherAngle = stf(Weather.Wind.Angle);
	//fWeatherAngle = GetAngleY(stf(worldMap.WindX), stf(worldMap.WindZ));
	fWeatherSpeed = stf(Weather.Wind.Speed);
	
    // boal -->
	bRain = true; // тут не работает Whr_isRainEnable(); из-за гл меню
    string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref rLoc;
		rLoc = &Locations[iLocation];
		
		if (CheckAttribute(rLoc, "environment.weather.rain") && !sti(rLoc.environment.weather.rain))
		{
			bRain = false;
		}
		//хз зачем тут закомментированно, если везде проставили аттрибут environment.weather.rain,
		//то оно и не нужно, но оно НЕ ПРОСТАВЛЕНО
		//Кто и зачем, вообще, трогал дожди????
		//navy
		else
		{
			if (CheckAttribute(rLoc, "type"))
			{
				// тип помещение
				if(rLoc.type == "residence"
					|| rLoc.type == "tavern"
					|| rLoc.type == "house"
					|| rLoc.type == "shop"
					|| rLoc.type == "shipyard"
					|| rLoc.type == "church" 
					|| rLoc.type == "cave" )
				{
					//нет дождя
					bRain = false;
				}
			}
		}
	}
	//итак, если может быть дождь, создаем окружение
	if (bRain)
	{
		WhrCreateRainEnvironment();
	}
	//если не может, удаляем.
	else
	{
		ClearRainEnvironment();
	}
	// boal <--
	
	WhrCreateSunGlowEnvironment();
	WhrCreateLightningEnvironment();
	WhrCreateSkyEnvironment();
	
	WhrCreateAstronomyEnvironment();

	if(iLocation != -1)
	{
		if(CheckAttribute(&Locations[iLocation], "lockWeather"))
		{
			bWhrTornado = false;
		}
	}
	if (bWeatherIsStorm) WhrStartLightning();
	if (bWhrTornado) WhrCreateTornadoEnvironment();

	Particles.windpower = 0.05 * Clampf(Whr_GetWindSpeed() / WIND_NORMAL_POWER);
	Particles.winddirection.x = sin(Whr_GetWindAngle());
	Particles.winddirection.z = cos(Whr_GetWindAngle());

	bWeatherLoaded = true;

    //стабилизация погоды при отдыхе в каюте корабля
	if (isShipInside(pchar.location))
	{
        DoShipLightChange(aCurWeather);

        int iLoc = FindLocation(pchar.location);
        if (iLoc != -1)
        {
            float locx, locy, locz;
            GetCharacterPos(pchar, &locx, &locy, &locz);
            UnloadLocation(&Locations[iLoc]);
            LoadLocation(&Locations[iLoc]);
            TeleportCharacterToPos(pchar, locx, locy, locz);
        }
	}
	if (bSeaActive)
	{
		Island.LightingPath = GetLightingPath();
		Island.FogDensity = Weather.Fog.IslandDensity;
		SendMessage(&IslandReflModel, "lllf", MSG_MODEL_SET_FOG, 1, 1, stf(Weather.Fog.IslandDensity));
	}
	SetCameraForWeather();
}

void Whr_UpdateWeather()
{
	if (!isEntity(&Weather)) { return; }

	if (!bSeaActive || and(bAbordageStarted, !isShipInside(pchar.location)))
	{
		// KZ > Небо из сноса исключаем.
		bWhrKeepSkyEntity = true;
		DeleteWeather();
		bWhrKeepSkyEntity = false;
	}
	CreateWeatherEnvironment();
	// MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);
	if (bSeaActive && !bAbordageStarted)
		MoveWeatherToLayers(SEA_EXECUTE, SEA_REALIZE);
	else
		MoveWeatherToLayers(EXECUTE,REALIZE);
}

void Whr_LoadNextWeather(int nPlus)
{
	if (!isEntity(&Weather)) { return; }
	//WeatherInit();  //слишком много инитов

	iCurWeatherHour = MakeInt(GetHour());
	iCurWeatherNum = iCurWeatherNum + nPlus;

	if (iCurWeatherNum < 0)
	{
		iCurWeatherNum = iTotalNumWeathers - 1;
	}
	if (iCurWeatherNum >= iTotalNumWeathers)
	{
		iCurWeatherNum = 0;
	}

	if (CheckAttribute(&Weathers[iCurWeatherNum], "Skip")) 
	{ 
		if (sti(Weathers[iCurWeatherNum].skip)) 
		{ 
			Whr_LoadNextWeather(nPlus);
			return;
		}
	}
	Log_TestInfo(ToUpper(XI_ConvertString("Weather")) + ": " + Weathers[iCurWeatherNum].id + " " + ToUpper(XI_ConvertString("Lighting")) + ": " + Weathers[iCurWeatherNum].Lighting);
	Log_TestInfo("Sun: HeightAngle: " + Weathers[iCurWeatherNum].Sun.HeightAngle);

	iNextWeatherNum = iCurWeatherNum;
	CreateWeatherEnvironment();
	MoveWeatherToLayers(sNewExecuteLayer, sNewRealizeLayer);

	aref	aCurWeather = GetCurrentWeather();
	iCurWeatherHour = sti(aCurWeather.Hour.Min);

	SetCurrentTime(iCurWeatherHour, 0);
	Weather.Time.time = GetTime();
}

void Whr_OnWindChange()
{
	if(iUpdateReducer < 4)
	{
		iUpdateReducer++;
		return;
	}
	iUpdateReducer = 0;
	float fDeltaTime = MakeFloat(GetDeltaTime()) * 0.001;
	fWeatherDelta = fWeatherDelta + fDeltaTime;

	float fSpd = fWeatherSpeed + (fWeatherSpeed / 6.0) * 0.1 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));
	float fAng = fWeatherAngle + 0.02 * (sin(fWeatherDelta) + sin(0.2 * fWeatherDelta) + sin(PI + 0.8 * fWeatherDelta) + cos(1.5 * fWeatherDelta));

	Weather.Wind.Angle = fAng;
	Weather.Wind.Speed = fSpd;
}

int Whr_OnCalcFogColor()
{
	int		iAlpha, iColor;
	float	x, y, z;
	float 	fH = 0.0;
	int		iColorTmp = 0;

	x = GetEventData();
	y = GetEventData();
	z = GetEventData();

	if( iBlendWeatherNum < 0 )
	{
		aref aCurWeather = GetCurrentWeather();
		iAlpha = 255 - MakeInt(255.0 * Clampf(y / stf(aCurWeather.(sCurrentFog).Height)));

		int iFogColor = sti(Weather.Fog.Color);
		iColor = or(shl(iAlpha, 24), iFogColor);
	}
	else
	{
		float fBlend = stf(Environment.time) - sti(Environment.time);
		fH 			= Whr_BlendFloat(fBlend, stf(Weathers[iCurWeatherNum].(sCurrentFog).Height), stf(Weathers[iBlendWeatherNum].(sBlendedFog).Height));
        iColorTmp 	= Whr_BlendColor(fBlend, sti(Weathers[iCurWeatherNum].(sCurrentFog).Color), sti(Weathers[iBlendWeatherNum].(sBlendedFog).Color));

		iAlpha = 255 - MakeInt(255.0 * Clampf(y / fH));
		iColor = or(shl(iAlpha, 24), iColorTmp);
	}
	return iColor;
}

float Whr_BlendFloat(float fBlend, float f1, float f2)
{
	float f = f1 + fBlend * (f2-f1);
	return f;
}

int Whr_BlendLong(float fBlend, int i1, int i2)
{
	int i = makeint(i1 + fBlend * (i2-i1));
	return i;
}

int Whr_BlendColor(float fBlend, int col1, int col2)
{
//	int a1 = shr(and(col1,4278190080), 24); // get alpha 1
//	int a2 = shr(and(col2,4278190080), 24); // get alpha 2
	int r1 = shr(and(col1,16711680), 16); // get red color 1
	int r2 = shr(and(col2,16711680), 16); // get red color 2

	int g1 = shr(and(col1,65280), 8); // get green color 1
	int g2 = shr(and(col2,65280), 8); // get green color 2

	int b1 = and(col1,255); // get blue color 1
	int b2 = and(col2,255); // get blue color 2

	int r = r1 + MakeInt(fBlend * (r2-r1));
	int g = g1 + MakeInt(fBlend * (g2-g1));
	int b = b1 + MakeInt(fBlend * (b2-b1));
//	int a = a1 + MakeInt(fBlend * (a2-a1));

	return argb(0,r,g,b);
}

void Whr_TimeUpdate()
{
	if (CheckAttribute(pchar, "questTemp.TimeLock")) {
		return;
	}
	float fTime = GetEventData();
	//float fBlend = fTime - makeint(fTime);

	aref aCurWeather = GetCurrentWeather();
	Environment.time = fTime;
	int nOldHour = sti(Environment.date.hour);
	int nNewHour = makeint(fTime);
	int nNewMin = makeint((fTime - nNewHour)*60);
	int nNewSec = makeint(((fTime - nNewHour)*60 - nNewMin)*60);
	Environment.date.min = nNewMin;
	Environment.date.hour = nNewHour;
	Environment.date.sec = nNewSec;
	worldMap.date.hour = nNewHour;
	worldMap.date.min  = nNewMin;
	if( nNewHour < nOldHour ) // обновление дня переход с 23 в 0
	{
		AddDataToCurrent(0,0,1);
		Weather.Time.time = GetTime();
	} // TODO время идет в CalcLocalTime
    
	if( iBlendWeatherNum < 0 ) {return;}
	
	SetCameraForWeather();

	//navy --> Rain
	int iTmp, iTime;
	bool bRain = false;
	if (CheckAttribute(&WeatherParams,"Rain")) bRain = sti(WeatherParams.Rain);

	//navy <-- Rain
	iCurWeatherNum = FindWeatherByHour( makeint(fTime) );
	iBlendWeatherNum = FindBlendWeather( iCurWeatherNum );

	if (CheckAttribute(&WeatherParams, "Fog.ThisDay") && sti(WeatherParams.Fog.ThisDay))
    {
        if (iBlendWeatherNum > -1)
        {
            if(CheckAttribute(&Weathers[iBlendWeatherNum],"SpecialLandFog") && (sti(WeatherParams.Fog.Type) == sti(Weathers[iBlendWeatherNum].SpecialLandFog.Type)))
            {
                if (Whr_CheckInsideLoc()) sBlendedFog = "Fog";
                else sBlendedFog = "SpecialLandFog";
            }
            else
            {
                sBlendedFog = "Fog";
            }
        }

        if(CheckAttribute(&Weathers[iCurWeatherNum],"SpecialLandFog") && (sti(WeatherParams.Fog.Type) == sti(Weathers[iCurWeatherNum].SpecialLandFog.Type)))
        {
            if (Whr_CheckInsideLoc()) sCurrentFog = "Fog";
            else sCurrentFog = "SpecialLandFog";
        }
        else
        {
            sCurrentFog = "Fog";
        }
    }
	//Mett: переработал систему дождей
	bool isStorm = CheckAttribute(aCurWeather, "Storm") && sti(aCurWeather.Storm) == 1;
	bool bIsRainEnable = Whr_isRainEnable() && !isStorm;

	if(CheckAttribute(&WeatherParams,"Rain") && bIsRainEnable) // не для локаций, где низя дождить + не для штормов где своя специфика
	{
		//Mett: дожди 13.11.2019
		if(CheckAttribute(&WeatherParams,"Rain.Type"))
		{
			if(sti(WeatherParams.Rain.Type) == 0)	Whr_SetRainExt1(iCurWeatherNum, iBlendWeatherNum, bRain);
			else									Whr_SetRainExt2(iCurWeatherNum, iBlendWeatherNum, bRain);
		}
		else
		{
			Whr_SetRainExt1(iCurWeatherNum, iBlendWeatherNum, bRain);
		}
	}
	//navy <-- Rain

    //если погода залочена, то не обновляем ее в реалтайме
    if (!CheckAttribute(&Weather, "Lock"))
    {
        if (nNewHour != nOldHour)
        {
            if (iBlendWeatherNum > -1) Whr_FogGenerator(&Weathers[iCurWeatherNum], &Weathers[iBlendWeatherNum]); //генератор туманов
            Whr_UpdateWeatherHour();
        }
        else Whr_ColorizeSeaWater(); //красим воду
    }

	// update weather: sun lighting
   // Whr_ModifySeaFog();
	FillWeatherData(iCurWeatherNum, iBlendWeatherNum);
	Weather.isDone = "";

	//update rain: rain drops, rain colors, rain size, rainbow
	//navy -- попрбуем такую проверку, есть подозрение, что это оно. 5.03.07
	if (bIsRainEnable) 
	{
		FillRainData(iCurWeatherNum, iBlendWeatherNum);
		Rain.isDone = "";
	}

	// update sun glow: sun\moon, flares
    WhrFillSunGlowData(iCurWeatherNum, iBlendWeatherNum);
	SunGlow.isDone = true;

	// update sky: fog
	Sky.TimeUpdate = fTime;
}

#event_handler("eChangeDayNight", "eChangeDayNight");

void Whr_UpdateWeatherHour()
{
	bool bOldIsDay = Whr_IsDay();
	bool doLightChange = false;
	int i, j, iCharIdx;

	bWeatherIsLight = Whr_GetLong(&Weathers[iCurWeatherNum],"Lights");
	bWeatherIsNight = Whr_GetLong(&Weathers[iCurWeatherNum],"Night");

	
	aref aCurWeather = GetCurrentWeather();
	aref aStars;
	makearef(aStars, aCurWeather.Stars);
	FillStars(aStars);
	Astronomy.isDone = true;
	Astronomy.TimeUpdate = 1;

	if( Whr_IsDay() != bOldIsDay )
	{ // меняем источники освещения
		Whr_ChangeDayNight();
		Event("eChangeDayNight");
        doLightChange = true;
 	}
 	if (bSeaActive && !bAbordageStarted)
	{
	    bool isSeaEnt = false;
	    Whr_WindChange();
	    if (IsEntity(&Sea))
            isSeaEnt = true;
        if (isSeaEnt) WhrCreateSeaEnvironment();
 		//#20190211-01
        if(doLightChange && isSeaEnt) {
            doShipLightChange(aCurWeather);
        }
 	}
}

void doShipLightChange(ref aCurWeather)
{
    int j, iCharIdx;

    ref rChar;
    Sea.Lights = aCurWeather.Lights;
    for(j = 0; j < iNumShips; j++)
	{
        iCharIdx = Ships[j];
        if (iCharIdx < 0 || iCharIdx >= TOTAL_CHARACTERS) continue;
        rChar = GetCharacter(Ships[j]);
        Ship_SetLightsAndFlares(rChar);
        SendMessage(rChar, "ll", MSG_SHIP_LIGHTSRESET, sti(Sea.Lights));
    }
}

void Whr_ChangeDayNight()
{
	int loadLocationIndex = FindLoadedLocation();
	if (loadLocationIndex >= 0)
	{
		LocationSetLights(&Locations[loadLocationIndex]);
		if (Whr_IsDay())
		{
			SendMessage(&Locations[loadLocationIndex], "ls", MSG_LOCATION_EX_MSG, "DelFlys");
		}
	}
}

void FillWeatherData(int nw1, int nw2)
{	
	if(nw1 < 0 || nw1 >= MAX_WEATHERS) return;

    string sCurFog = Whr_GetCurrentFog();
    string sBldFog = Whr_GetBlendedFog();
    float fFogAdd = Whr_InitFogLocAdd();
    float fFogRain = 0.0;

    if (Whr_CheckRain() || Whr_CheckStorm()) fFogRain = 0.005;
    Whr_ModifySeaFog(&Weathers[nw1]);

    //TODO очень важная информация для отладки погоды, как погода устаканится отключить лог
	if (TestMode())
		trace("FillWeatherData - nw1: " + nw1 + " nw2: " + nw2 + " bStorm: " + bStorm + " sCurFog: " + sCurFog + " sBldFog: " + sBldFog);

    if(nw2 < 0 || Whr_CheckStorm())
    {
        Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");
        Weather.Fog.Start = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start");
        Weather.Fog.Color = Whr_GetColor(&Weathers[nw1], sCurFog + ".Color");
        Weather.Fog.IslandDensity = Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity");

        if (bSeaActive)
        {
			Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density");
			Weather.Fog.SeaDensity = Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity");
            if(CheckAttribute(&Weathers[nw1],"Sun.SeaColor"))   Weather.Sun.Color   = Whr_GetColor(&Weathers[nw1],"Sun.SeaColor");
            else                                                Weather.Sun.Color   = Whr_GetColor(&Weathers[nw1],"Sun.Color");
            if(CheckAttribute(&Weathers[nw1],"Sun.SeaAmbient")) Weather.Sun.Ambient = Whr_GetColor(&Weathers[nw1],"Sun.SeaAmbient");
            else                                                Weather.Sun.Ambient = Whr_GetColor(&Weathers[nw1],"Sun.Ambient");
        }
        else
        {
			Weather.Fog.Density = Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density") + fFogAdd + fFogRain;
			Weather.Fog.SeaDensity = Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity") + fFogAdd + fFogRain;
            Weather.Sun.Color	= Whr_GetColor(&Weathers[nw1],"Sun.Color");
            Weather.Sun.Ambient	= Whr_GetColor(&Weathers[nw1],"Sun.Ambient");
        }
    }
    else
    {
        float fBlend = stf(Environment.Time) - sti(Environment.Time);
        string sColor1, sColor2;
        string sAmbient1, sAmbient2;

        Whr_ModifySeaFog(&Weathers[nw2]);

        if (bSeaActive)
        {
            if(CheckAttribute(&Weathers[nw1],"Sun.SeaColor"))   sColor1     = "Sun.SeaColor";
            else                                                sColor1     = "Sun.Color";
            if(CheckAttribute(&Weathers[nw2],"Sun.SeaColor"))   sColor2     = "Sun.SeaColor";
            else                                                sColor2     = "Sun.Color";
            if(CheckAttribute(&Weathers[nw1],"Sun.SeaAmbient")) sAmbient1   = "Sun.SeaAmbient";
            else                                                sAmbient1   = "Sun.Ambient";
            if(CheckAttribute(&Weathers[nw2],"Sun.SeaAmbient")) sAmbient2   = "Sun.SeaAmbient";
            else                                                sAmbient2   = "Sun.Ambient";
            Weather.Sun.Color	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],sColor1), Whr_GetColor(&Weathers[nw2],sColor2));
            Weather.Sun.Ambient	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],sAmbient1), Whr_GetColor(&Weathers[nw2],sAmbient2));
        }
        else
        {
            Weather.Sun.Color	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Color"), Whr_GetColor(&Weathers[nw2],"Sun.Color"));
            Weather.Sun.Ambient	= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1],"Sun.Ambient"), Whr_GetColor(&Weathers[nw2],"Sun.Ambient"));
        }

        Weather.Fog.Enable = Whr_GetLong(&Weathers[nw1], sCurFog + ".Enable");

        if(bSeaActive)
        {
            Weather.Fog.Start			= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Start"));
            Weather.Fog.Density			= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Density"));
            Weather.Fog.Color			= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1], sCurFog + ".Color"), Whr_GetColor(&Weathers[nw2], sBldFog + ".Color"));
            Weather.Fog.IslandDensity	= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".IslandDensity"));
            Weather.Fog.SeaDensity		= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".SeaDensity"));
        }
        else
        {
            Weather.Fog.Start			= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Start"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Start"));
            Weather.Fog.Density	        = Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".Density"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".Density")) + fFogAdd + fFogRain;
            Weather.Fog.SeaDensity		= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".SeaDensity"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".SeaDensity")) + fFogAdd + fFogRain;
            Weather.Fog.Color			= Whr_BlendColor(fBlend, Whr_GetColor(&Weathers[nw1], sCurFog + ".Color"), Whr_GetColor(&Weathers[nw2], sBldFog + ".Color"));
            Weather.Fog.IslandDensity	= Whr_BlendFloat(fBlend, Whr_GetFloat(&Weathers[nw1], sCurFog + ".IslandDensity"), Whr_GetFloat(&Weathers[nw2], sBldFog + ".IslandDensity"));
        }
    }
    if (IsEntity(&Sea)) //для динамики туманов на воде
    {
		if (TestMode())
			trace("Fog - Density: " + weather.Fog.Density + " SeaDensity: " + weather.Fog.SeaDensity + " IslandDensity:" + weather.Fog.IslandDensity);
        Island.FogDensity = weather.Fog.IslandDensity;
        Sea.Fog.SeaDensity = weather.Fog.SeaDensity;
        Sea.Fog.Density = weather.Fog.Density;
        Sea.Fog.Start = weather.Fog.Start;
    }
	
	if(CheckAttribute(&TEV, "AscoldLeif_SetMists"))
	{
		Whr_SetMisteryMists();
	}

	// > Плотность тумана для теней раньше снималась один раз при создании погоды и потом устаревала.
	fFogDensity = stf(Weather.Fog.Density);
	// > Плотность теней считалась заново на каждую тень в кадре (событие от модуля теней);
	// > меняется она только вместе с погодой, поэтому считаем здесь.
	iShadowDensity[0] = Whr_GetColor(&Weathers[nw1], "Shadow.Density.Head");
	iShadowDensity[1] = Whr_GetColor(&Weathers[nw1], "Shadow.Density.Foot");
}

int FindWeatherByHour(int nHour)
{
	for (int n=0; n<MAX_WEATHERS; n++)
	{
		if (!CheckAttribute(&Weathers[n], "hour")) {continue;}
		if (CheckAttribute(&Weathers[n], "skip") && sti(Weathers[n].skip)==true) {continue;}
		if (CheckAttribute(&Weathers[n], "Storm") && sti(Weathers[n].Storm)==true) {continue;}

		if( sti(Weathers[n].hour.min) == nHour ) {return n;}
	}
	return -1;
}

int FindBlendWeather(int iWeatherNum)
{
	// чтоб вырубить return -1;
	if( iWeatherNum<0 || iWeatherNum>=MAX_WEATHERS ) {return -1;}

	if(!CheckAttribute(&Weathers[iWeatherNum], "hour")) {return -1;}
	if(CheckAttribute(&Weathers[iWeatherNum],"Storm") && sti(Weathers[iWeatherNum].Storm)==true ) return -1;
	if(CheckAttribute(&Weathers[iWeatherNum],"skip") && sti(Weathers[iWeatherNum].skip)==true ) return -1;

	int nBlendWeatherHour = sti(Weathers[iWeatherNum].hour.min) + 1;
	if( nBlendWeatherHour>=24 ) {nBlendWeatherHour = 0;}

	return FindWeatherByHour(nBlendWeatherHour);
}

void CreateWeather(int sExecuteLayer, int sRealizeLayer)
{
	CreateWeatherEnvironment();
	MoveWeatherToLayers(sExecuteLayer, sRealizeLayer);
}

void DeleteWeather()
{
	DeleteWeatherEnvironment();
}

void MoveWeatherToLayers(int sExecuteLayer, int sRealizeLayer)
{
	LayerDelObject(EXECUTE,&Weather);
	LayerDelObject(REALIZE,&Weather);
	LayerDelObject(SEA_EXECUTE,&Weather);
	LayerDelObject(SEA_REALIZE,&Weather);

	sNewExecuteLayer = sExecuteLayer;
	sNewRealizeLayer = sRealizeLayer;

	LayerAddObject(sExecuteLayer,&Weather,1000000);
	LayerAddObject(sRealizeLayer,&Weather,65530);

	MoveRainToLayers(sExecuteLayer, sRealizeLayer);
	MoveLightningToLayers(sExecuteLayer, sRealizeLayer);
	MoveSkyToLayers(sExecuteLayer, sRealizeLayer);
	MoveSunGlowToLayers(sExecuteLayer, sRealizeLayer);
	MoveAstronomyToLayers(sExecuteLayer, sRealizeLayer);
}

float Whr_GetFogDensity() { return fFogDensity; }

float Whr_GetWindAngle()
{
	if (!CheckAttribute(&Weather,"Wind.Angle")) { return 0.0; }
	return stf(Weather.Wind.Angle);
}

float Whr_GetWindSpeed()
{
	if (!CheckAttribute(&Weather,"Wind.Speed")) { return 3.0; }
	return stf(Weather.Wind.Speed);
}

ref Whr_GetShadowDensity()
{
	// > Значения обновляются в FillWeatherData (и сбрасываются в дефолт в DeleteWeatherEnvironment),
	// > поэтому здесь больше не нужен обход дерева атрибутов на каждую тень каждого кадра.
	return &iShadowDensity;
}

string	Whr_GetCurrentFog() { return sCurrentFog; }
string	Whr_GetBlendedFog() { return sBlendedFog; }
string	Whr_GetInsideBack() { return sInsideBack; }
string	GetLightingPath()	
{
/*navy -->
	if (CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return Whr_GetRainyLightningPath();
	}
navy <--*/
	return sLightingPath;
}
string	GetLmLightingPath() 
{ 
/*navy -->
	if (CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return "storm";
	}
navy <--*/
	return sLmLightingPath;
}

bool	Whr_IsDay() { return !bWeatherIsNight; }
bool	Whr_IsNight() { return bWeatherIsNight; }
bool	Whr_IsLight() { return bWeatherIsLight; }
bool	Whr_IsRain() { return bWeatherIsRain; }
bool	Whr_IsStorm() { return bWeatherIsStorm; }

int FindWeather(string sWeatherID)
{
	for (int i=0;i<MAX_WEATHERS;i++)
	{
		if (!CheckAttribute(&Weathers[i], "id")) 
		{ 
			continue;
		}
		if(Weathers[i].id == sWeatherID)
		{
			return i;
		}
	}
	return -1;
}

//navy --> Rain вернул
void Whr_SetRainSound(bool _set, bool _isNight)
{
//	return;
	// пока закрыл, тк работает метод CalcLocalTime, нужно понять где лучше и оставть один

	string scheme = "land";
	//ищем локацию ГГ, три схемы: land, sea, town
	//можно и больше...
	if (!bSeaActive || bAbordageStarted)
	{
		if (IsEntity(loadedLocation) && CheckAttribute(loadedLocation, "type"))
		{
			switch (loadedLocation.type)
			{
			case "town":
				scheme = "town";
				break;
			case "land":
				scheme = "land";
				break;
			case "deck":
				scheme = "deck";
				break;
			}
		}
	}
	else
	{
		scheme = "sea";
	}

	//проверка - день/ночь
	if (_isNight)
    {
		scheme = scheme+"_night";
    }
	else
	{
		scheme = scheme+"_day";
	}

	//если устанавливаем звук дождя
	if (_set)
	{
		scheme = scheme + "_rain";
	}

	if(CheckAttribute(&TEV, "CurrentSoundScheme"))
	{
		if (_set && scheme == TEV.CurrentSoundScheme)
		{
			// Не ставим одну и ту же схему подряд
			return;
		}
	}

	if (TestMode())
		trace("Whr_SetRainSound: Set Sound... " + scheme);

	SetSoundScheme(scheme);
}

string Whr_GetRainyLightningPath()
{
	//trace("__GET__COL__");
	return "storm1";
}
//navy <--

// boal -->
void Whr_WindChange()
{
	aref aCurWeather = GetCurrentWeather();

    if(CheckAttribute(pchar, "wind.angle"))
    {
    	Weather.Wind.Angle = stf(pchar.wind.angle) +  frand((PI/4.0)) - (PI / 8.0);
    	if (stf(Weather.Wind.Angle) < 0)  Weather.Wind.Angle = PIm2 + stf(Weather.Wind.Angle);
    }
    else
    {
		Weather.Wind.Angle = frand(PIm2);
	}
	pchar.wind.angle = Weather.Wind.Angle;

	Weather.Wind.Speed = Whr_GetFloat(aCurWeather,"Wind.Speed");
	pchar.wind.speed = Weather.Wind.Speed;
	
	pchar.quest.EraseWind.win_condition.l1 = "ExitFromSea";
	pchar.quest.EraseWind.win_condition = "EraseWind";
	
	fWeatherAngle = stf(Weather.Wind.Angle);
	fWeatherSpeed = stf(Weather.Wind.Speed);
}

bool Whr_isRainEnable()
{
	bool bRain  = true;
	//ГГ в локации
    if (CheckAttribute(GetMainCharacter(), "HeroParam") && IsEntity(loadedLocation)) // pchar проверяется для гл меню
	{
        if (CheckAttribute(loadedLocation, "environment.weather.rain") && !sti(loadedLocation.environment.weather.rain))
		{
		    bRain = false;
		}
	}
	else
	{
		if (bSeaActive && bAbordageStarted ) // в море не срабатывает bLandInterfaceStart
		{
			if (IsEntity(&loadedLocation))
			{
			    if(CheckAttribute(&loadedLocation, "environment.weather.rain"))
				{
                    if(!sti(loadedLocation.environment.weather.rain)) bRain = false;
			    }
			}
		}
	}
	return bRain;
}
// boal <--

//путь до col файлов для островов
string GetIslandLightingPath()
{
	if(CheckAttribute(&WeatherParams, "Rain") && sti(WeatherParams.Rain))
	{
		return Whr_GetRainyLightningPath();
	}
	return sLightingPath;
}

bool Whr_CheckInsideLoc() // фильтр внутренних локаций без погодных условий
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			if(loc.type == "residence"
				|| loc.type == "tavern"
				|| loc.type == "house"
				|| loc.type == "shop"
				|| loc.type == "shipyard"
				|| loc.type == "church"
				|| loc.type == "jail"
				|| loc.type == "dungeon"
				|| loc.type == "cave"
				|| loc.type == "LSC_inside"
				|| loc.type == "fort_attack"
                || loc.type == "boarding_cabine"
				|| loc.type == "ammo" || loc.type == "ammo_old"
				// || loc.type == "teno"
				|| loc.type == "teno_inside")
			{
			    return true;
			}
		}
	}
	return false;
}

float Whr_InitFogLocAdd() // фильтр локаций для повышенного тумана
{
    float fFogAdd = 0.0;
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if (iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if (CheckAttribute(loc, "type"))
		{
			if  (loc.type == "jungle"
			    || loc.type == "seashore"
				|| loc.type == "town"
				|| loc.type == "plantation"
				|| loc.type == "mine"
			    )
			{
				fFogAdd = 0.002;
			}
			else if (loc.type == "mayak"
			        || loc.type == "fort" || loc.type == "fort_old"
			        || loc.type == "fort_attack")
			{
				fFogAdd = 0.0005;
			}
		} 
	}
	return fFogAdd;
}

void Whr_SetLock(bool bLock)
{
    if (bLock)  Weather.Lock = true;
    else        DeleteAttribute(&Weather, "Lock");
}

// Туман для квеста Лейфа
void Whr_SetMisteryMists() {
	if (Whr_CheckInsideLoc())
		return;
		
	if (CheckAttribute(pchar, "location"))
	{
		int iLocation = FindLocation(pchar.location);
		if (iLocation != -1 && CheckAttribute(&Locations[iLocation], "islandId") && Locations[iLocation].islandId == "Guadeloupe")
		{
			Weather.Fog.Density			= 0.1;
			Weather.Fog.Color			= argb(0, 157,173,191);
			Weather.Fog.IslandDensity	= 0.1;
			Weather.Fog.SeaDensity		= 0.1;
			Weather.Fog.Height 			= 4000;

			if (IsEntity(&Sea)) //для динамики туманов на воде
			{
				Island.FogDensity = weather.Fog.IslandDensity;
				Sea.Fog.SeaDensity = weather.Fog.SeaDensity;
				Sea.Fog.Density = weather.Fog.Density;
			}
		}
	}
}

void SetCameraForWeather()
{
    if(!bSeaActive) return;
    if(GetCharacterShipType(pchar) == SHIP_NOTUSED) return;
    
    float ch            = 2.0;
    float bh            = 2.0;
    aref  aCurWeather   = GetCurrentWeather();
	int   shipType      = sti(RealShips[sti(pchar.ship.type)].basetype);

    switch (aCurWeather.Lighting)
    {
        case "storm1":	ch -= 0.3;	bh -= 0.3;	break;
        case "storm2":	ch -= 0.5;	bh -= 0.4;	break;
        case "storm3":	ch -= 0.4;	bh -= 0.3;	break;
        case "storm4":	ch -= 0.5;	bh -= 0.4;	break;
    }        

	SeaShipCamera.cam_height = ch;
	SeaShipCamera.box_height = bh;
}
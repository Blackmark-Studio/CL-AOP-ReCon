#event_handler("frame", "UpdateSky");

object Sky;

bool bWhrKeepSkyEntity = false;	// KZ > пересборка погоды на месте: сущность неба не сносим

float fLastSkyRotateSpeed = -1.0;	// > последнее записанное в движок значение, -1.0 = "надо записать"

void WhrDeleteSkyEnvironment()
{
	if(bWhrKeepSkyEntity)
	{
		return; // > Погода пересобирается на месте, а не сносится насовсем.
	}

	if(isEntity(&Sky))
	{
		DeleteClass(&Sky);
	}

	DeleteAttribute(&Sky, "");
	fLastSkyRotateSpeed = -1.0;
}

void WhrCreateSkyEnvironment()
{
	aref aCurWeather = GetCurrentWeather();
	aref aSky;
	makearef(aSky, aCurWeather.Sky);

	DeleteAttribute(&Sky, "");
	if(!isEntity(&Sky))
	{
		CreateEntity(&Sky, "Sky");
		if(bSeaActive)
		{
			LayerAddObject(SEA_REFLECTION,&Sky,1);
		}
        else
		{
			LayerAddObject(SEA_REFLECTION,&Sky,11);
		}
	}

	FillSkyDir(&Sky);
	//Sky.Dir = Whr_GetString(aSky, "Dir");

	Sky.Color = Whr_GetColor(aSky, "Color");
	Sky.RotateSpeed = Whr_GetFloat(aSky, "Rotate"); // Warship 02.06.09 - ротация неба ниже
	fLastSkyRotateSpeed = -1.0; // > небо пересобрано, следующий кадр обязан переписать скорость
	Sky.Angle = Whr_GetFloat(aSky, "Angle");
	Sky.Size = Whr_GetFloat(aSky, "Size");
	
	  if(bSeaActive) 
	{
        Sky.techSky = "Sky";
        Sky.techSkyBlend = "SkyBlend";
        Sky.techskyAlpha = "skyblend_alpha";
        Sky.techSkyFog = "SkyFog";
	}
	/* else
	{
         Sky.Size = 2048;
	    Sky.techSky = "SkyLand";
        Sky.techSkyBlend = "SkyBlendLand";
        Sky.techskyAlpha = "skyblend_alphaLand";
        Sky.techSkyFog = "SkyFogLand";
	}  //// *//////======>> Hirurg39 убрал прозрачную текстуру в небе при торнадо на суше

	Sky.isDone = "";
}

// Warship 02.06.09 - апдейт параметров неба (например, скорость ротации в зависимости от силы ветра)
void UpdateSky()
{
	if (!IsEntity(&Sky)) { return; }	// > в меню и внутренних локациях сущности неба нет

	float windSpeed = 5.0;
	float timeScale = 1.0 + TimeScaleCounter * 0.25; // Текущее ускорение времени

	// Вычисление делителя для ускорения, чтоб на x8 бешенно не крутились
	if(timeScale <= 2)
	{
		timeScale = 1;
	}
	else
	{
		timeScale /= 2;
	}

	if(CheckAttribute(&Weather, "Wind.Speed"))
	{
		windSpeed = stf(Weather.Wind.Speed);
	}

	float fNewSpeed = 0.0;
	if (CheckAttribute(&InterfaceStates, "SkyRotation") && sti(InterfaceStates.SkyRotation) == 1)
	{
		fNewSpeed = windSpeed / 10000 / timeScale;
	}

	// > Пишем атрибут только при реальном изменении: раньше запись шла каждый кадр и каждый раз дёргала разбор атрибута в движке.
	if (fNewSpeed != fLastSkyRotateSpeed)
	{
		Sky.RotateSpeed = fNewSpeed;
		fLastSkyRotateSpeed = fNewSpeed;
	}
}

void FillSkyDir(aref aSky)
{
	int i, nStart, nDur;
	string satr;
	aref aCurWeather = GetCurrentWeather();
	string sDir;

	DeleteAttribute(aSky,"Dir");
	if( iBlendWeatherNum < 0 )
	{
		aSky.Dir.d1 = aCurWeather.Sky.Dir;
		aSky.Dir = GetHour();
	} else {
		for (i=0;i<MAX_WEATHERS;i++)
		{
			if (!CheckAttribute(&Weathers[i], "Hour")) {continue;}
			if (CheckAttribute(&Weathers[i], "Skip") && sti(Weathers[i].Skip)==true) {continue;}
			if (CheckAttribute(&Weathers[i], "Storm")&& sti(Weathers[i].Storm)==true) {continue;}

			satr = "d" + sti(Weathers[i].Hour.Min);
			if( satr=="d24" ) {continue;}
			
//navy -->
			sDir = Weathers[i].Sky.Dir;
			if (CheckAttribute(&WeatherParams, "Rain.ThisDay") && sti(WeatherParams.Rain.ThisDay)) 
			{
				nStart = sti(WeatherParams.Rain.StartTime);
				nDur = MakeInt(stf(WeatherParams.Rain.Duration)/60.0 + 0.5);
				if (sti(Weathers[i].Hour.Min) >= nStart  && sti(Weathers[i].Hour.Max) <= (nStart + nDur))
				{
					sDir = "weather\skies\Storm01\";
				}
			}
//navy <--
			aSky.Dir.(satr) = sDir;
		}
		aSky.Dir = GetTime();
	}
}

void MoveSkyToLayers(int sExecuteLayer, int sRealizeLayer)
{
	LayerDelObject(EXECUTE,&Sky);
	LayerDelObject(REALIZE,&Sky);
	LayerDelObject(SEA_EXECUTE,&Sky);
	LayerDelObject(SEA_REALIZE,&Sky);
	
    LayerAddObject(sExecuteLayer,&Sky,2);
    LayerAddObject(sRealizeLayer,&Sky,3);
}
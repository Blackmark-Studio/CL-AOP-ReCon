// -------------------------------------------------------------
// Mett: настройки моря
// заготовки на разные типы волнения:
// штиль, лёгкий бриз, бриз, умеренный бриз, сильный бриз, шторм
// -------------------------------------------------------------

int SM_WaveType = 1;

string WhrGetSeaPresetFromWind(float fWind)
{
	string sLocation = pchar.location;
	string sLocalPreset = "calm";
    if (bSeaActive && !bAbordageStarted)
    {
        if (fWind > 4.0)    sLocalPreset = "light_breeze";
        if (fWind > 7.5)    sLocalPreset = "breeze";
        if (fWind > 11.0)   sLocalPreset = "moderate_breeze";
        if (fWind > 14.5)   sLocalPreset = "strong_breeze";
        if (fWind > 17.5)   sLocalPreset = "strong wind";

        //если сила волны больше чем может позволить уровень моря, то получается полный штиль
        //что бы при сильном ветре не было штиля опускаем уровень пресета под текущий уровень моря
        if (fWind > 7.5)
        {
            float distanceToIsland = Whr_GetNearestDistanceToIsland();
            if (distanceToIsland < 400)                         sLocalPreset = "light_breeze";
            else if (fWind > 11.0 && distanceToIsland < 800)    sLocalPreset = "breeze";
            else if (fWind > 14.5 && distanceToIsland < 1300)   sLocalPreset = "moderate_breeze";
        }

        if (Whr_CheckStorm())                   sLocalPreset = "storm"; //пресет на шторм игнорирует силу ветра
        else if (Whr_CheckSpecialLandFog())     sLocalPreset = "light_breeze"; //в туманы штиль

    }
	//пресеты на сушу
	else if (FindLocation(sLocation) != -1)
	{
        if (fWind > 12.0)                       sLocalPreset = "strong_breeze_land";
        else if (fWind <= 7.0)                  sLocalPreset = "light_breeze_land";
        else if (fWind <= 12.0)                 sLocalPreset = "breeze_land";

        ref loc = &Locations[FindLocation(sLocation)];
		if (Whr_CheckStorm())
		    sLocalPreset = "storm_land"; //пресет на шторм игнорирует силу ветра
		else if (Whr_CheckSpecialLandFog())
		    sLocalPreset = "light_breeze_land"; //в туманы штиль
		else if (CheckAttribute(loc, "fastreload") && loc.fastreload == "LostShipsCity")
		    sLocalPreset = "light_breeze_land";// в ГПК если не шторм то штиль

		if (CheckAttribute(loc, "type"))
		{
		    //тип воды для грота и речушек
		    if (HasStrEx(loc.type, "cave,plantation,teno_inside", "|")) sLocalPreset = "stock_land";
		    //тип воды для озёр
		    else if (HasStrEx(loc.type, "teno", "|")) sLocalPreset = "lake_land";
		}
	}

	return sLocalPreset;
}

void WhrSetSeaPreset(int iCurWeatherNum, float fWind)
{
    if (isShipInside(pchar.location)) return;

    ref Whr = &Weathers[iCurWeatherNum];
    Whr.Sea2.SkyColor = argb(0,255,255,255);

    float SeaAmp = 0.0;

    string sLocation = pchar.location;

    int iLoc = FindLocation(sLocation);
    ref loc;
    if (iLoc >= 0) makeref(loc, Locations[iLoc]);

    switch(sPreset)
    {
        case "calm": //штиль 0
            SM_WaveType = 2;

            Whr.Sea2.Amp1 = 0.5;
            Whr.Sea2.AnimSpeed1 = 1.0;
            Whr.Sea2.Scale1 = 1.75;
            Whr.Sea2.MoveSpeed1 = "0.5, 0.0, 0.0";

            Whr.Sea2.Amp2 = 0.5;
            Whr.Sea2.AnimSpeed2 = 1.0;
            Whr.Sea2.Scale2 = 1.75;
            Whr.Sea2.MoveSpeed2 = "0.0, 0.0, -0.5";

            Whr.Sea2.BumpScale = 0.10;
            Whr.Sea2.PosShift = 1.75;

            Whr.Sea2.FoamV = 5.0;
            Whr.Sea2.FoamK = 0.0;
            Whr.Sea2.FoamUV = 0.3;
            Whr.Sea2.FoamTexDisturb = 0.7;

            Whr.Sea2.Frenel = 0.3;
            Whr.Sea2.Attenuation = 0.3;
            Whr.Sea2.Reflection = 0.6;
            Whr.Sea2.Transparency = 0.6;

            Whr.Sea2.LodScale = 0.04;
            Whr.Sea2.GridStep = 0.2;

            Whr.Sea2.SkyColor = argb(0,180,220,240);
        break;

        case "light_breeze": //лёгкий бриз 1
            SM_WaveType = 2;
            SeaAmp = fWind * 0.4 + 1;

            Whr.Sea2.Amp1 = SeaAmp; // 4.0
            Whr.Sea2.AnimSpeed1 = 1.25;
            Whr.Sea2.Scale1 = 0.6;
            Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 2.0";

            Whr.Sea2.Amp2 = 2.0;
            Whr.Sea2.AnimSpeed2 = 2.0;
            Whr.Sea2.Scale2 = 1.5;
            Whr.Sea2.MoveSpeed2 = "-2.0, 0.0, 0.0";

            Whr.Sea2.BumpScale = 0.06; //Ю?О†ї? ђЭОНЯ
            Whr.Sea2.PosShift = 2.0;//остроконечность волн
            Whr.Sea2.LodScale = 0.04;
            Whr.Sea2.GridStep = 0.2;

            Whr.Sea2.FoamK = 0.4;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
            Whr.Sea2.FoamV = SeaAmp * 0.9;//высота с которой начинаетс§ пена
            Whr.Sea2.FoamUV = 0.4; //тайлинг пены
            Whr.Sea2.FoamTexDisturb = 0.5;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

            Whr.Sea2.Reflection = 0.4;
            Whr.Sea2.Transparency = 0.1;
            Whr.Sea2.Frenel = 0.5;
            Whr.Sea2.Attenuation = 0.2;
        break;

        case "breeze":	//бриз 2 8.15
            SM_WaveType = 2;
            SeaAmp = fWind * 0.60 + 1;

            Whr.Sea2.Amp1 = SeaAmp; // 8.0
            Whr.Sea2.AnimSpeed1 = 1.5;
            Whr.Sea2.Scale1 = 0.35;
            Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 3.0";

            Whr.Sea2.Amp2 = 3.0;
            Whr.Sea2.AnimSpeed2 = 3.0;
            Whr.Sea2.Scale2 = 1.25;
            Whr.Sea2.MoveSpeed2 = "1.0, 0.0, 1.0";

            Whr.Sea2.BumpScale = 0.06; //Ю?О†ї? ђЭОНЯ
            Whr.Sea2.PosShift = 2.0;//остроконечность волн
            Whr.Sea2.LodScale = 0.04;
            Whr.Sea2.GridStep = 0.2;

            Whr.Sea2.FoamK = 0.45;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
            Whr.Sea2.FoamV = SeaAmp * 0.85;//высота с которой начинаетс§ пена 6.0
            Whr.Sea2.FoamUV = 0.4; //тайлинг пены
            Whr.Sea2.FoamTexDisturb = 0.5;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

            Whr.Sea2.Reflection = 0.4;
            Whr.Sea2.Transparency = 0.1;
            Whr.Sea2.Frenel = 0.6;
            Whr.Sea2.Attenuation = 0.2;
        break;

        case "moderate_breeze":	//бриз 3
            SM_WaveType = 3;
            SeaAmp = fWind * 0.75 + 1;

            Whr.Sea2.Amp1 = SeaAmp; // 12.0 - 9.25
            Whr.Sea2.AnimSpeed1 = 1.65;
            Whr.Sea2.Scale1 = 0.25;
            Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 4.0";

            Whr.Sea2.Amp2 = 3.5;
            Whr.Sea2.AnimSpeed2 = 3.5;
            Whr.Sea2.Scale2 = 1.15;
            Whr.Sea2.MoveSpeed2 = "0.0, 0.0, 1.0";

            Whr.Sea2.BumpScale = 0.06; //Ю?О†ї? ђЭОНЯ
            Whr.Sea2.PosShift = 2.0; //остроконечность волн
            Whr.Sea2.LodScale = 0.04;
            Whr.Sea2.GridStep = 0.2;

            Whr.Sea2.FoamK = 0.4;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
            Whr.Sea2.FoamV = SeaAmp * 0.8;//высота с которой начинаетс§ пена 8.0
            Whr.Sea2.FoamUV = 0.4; //тайлинг пены
            Whr.Sea2.FoamTexDisturb = 0.5;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

            Whr.Sea2.Reflection = 0.4;
            Whr.Sea2.Transparency = 0.1;
            Whr.Sea2.Frenel = 0.6;
            Whr.Sea2.Attenuation = 0.2;
        break;

        case "strong_breeze"://ветрено 4
            SM_WaveType = 3;
            SeaAmp = fWind * 0.85 + 1;

            Whr.Sea2.Amp1 = SeaAmp; // 16.0 - 13
            Whr.Sea2.AnimSpeed1 = 1.75;
            Whr.Sea2.Scale1 = 0.20;
            Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 5.0";

            Whr.Sea2.Amp2 = 4.0;
            Whr.Sea2.AnimSpeed2 = 4.0;
            Whr.Sea2.Scale2 = 1.0;
            Whr.Sea2.MoveSpeed2 = "0.0, 0.0, -1.0";


            Whr.Sea2.BumpScale = 0.06; //Ю?О†ї? ђЭОНЯ
            Whr.Sea2.PosShift = 2.0; //остроконечность волн
            Whr.Sea2.LodScale = 0.04;
            Whr.Sea2.GridStep = 0.2;

            Whr.Sea2.FoamK = 0.2; //§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
            Whr.Sea2.FoamV = SeaAmp * 0.75; //высота с которой начинаетс§ пена 10.5
            Whr.Sea2.FoamUV = 0.4; //тайлинг пены
            Whr.Sea2.FoamTexDisturb = 0.5;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

            Whr.Sea2.Reflection = 0.4;
            Whr.Sea2.Transparency = 0.1;
            Whr.Sea2.Frenel = 0.6;
            Whr.Sea2.Attenuation = 0.2;
        break;

        case "strong wind"://ветрено 5 17.5 - 20
            SM_WaveType = 2;
            SeaAmp = fWind * 1.55 + 1;

            Whr.Sea2.Amp1 = SeaAmp; // 32.0 - 28.0
            Whr.Sea2.AnimSpeed1 = 3.75;
            Whr.Sea2.Scale1 = 0.125;
            Whr.Sea2.MoveSpeed1 = "8.0, 0.0, 0.0";

            Whr.Sea2.Amp2 = 6.0;
            Whr.Sea2.AnimSpeed2 = 6.0;
            Whr.Sea2.Scale2 = 0.75;
            Whr.Sea2.MoveSpeed2 = "0.0, 0.0, -1.0";

            Whr.Sea2.BumpScale = 0.06; //Ю?О†ї? ђЭОНЯ
            Whr.Sea2.PosShift = 2.0;//остроконечность волн
            Whr.Sea2.LodScale = 0.04;
            Whr.Sea2.GridStep = 0.2;

            Whr.Sea2.FoamK = 0.15;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
            Whr.Sea2.FoamV = SeaAmp * 0.7;//высота с которой начинаетс§ пена 21.0
            Whr.Sea2.FoamUV = 0.4; //тайлинг пены
            Whr.Sea2.FoamTexDisturb = 0.7;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

            Whr.Sea2.Reflection = 0.3;
            Whr.Sea2.Transparency = 0.1;
            Whr.Sea2.Frenel = 0.6;
            Whr.Sea2.Attenuation = 0.2;

            if (GetTime() < 6.0 || GetTime() >= 21.0) {
                Whr.Sea2.FoamK = 0.1;
                Whr.Sea2.Reflection = 0.5;
                Whr.Sea2.Transparency = 0.1;

            }else {
                if (Whr_CheckRain()){
                    Whr.Sea2.Reflection = 0.05;
                    Whr.Sea2.Transparency = 0.1;
                }
            }
        break;

        case "storm"://шторм 5
            SM_WaveType = 1;
            Whr.Sea2.Amp1 = 32.0;
            Whr.Sea2.AnimSpeed1 = 4.0;
            Whr.Sea2.Scale1 = 0.12;
            Whr.Sea2.MoveSpeed1 = "8.0, 0.0, 0.0";

            Whr.Sea2.Amp2 = 2.0;
            Whr.Sea2.AnimSpeed2 = 9.0;
            Whr.Sea2.Scale2 = 1.3;
            Whr.Sea2.MoveSpeed2 = "12.0, 0.0, 0.0";

            Whr.Sea2.BumpScale = 0.05; //Ю?О†ї? ђЭОНЯ
            Whr.Sea2.PosShift = 2.0;//остроконечность волн
            Whr.Sea2.LodScale = 0.04;
            Whr.Sea2.GridStep = 0.2;

            Whr.Sea2.FoamK = 0.02;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
            Whr.Sea2.FoamV = 10.0;//высота с которой начинаетс§ пена
            Whr.Sea2.FoamUV = 0.2; //тайлинг пены
            Whr.Sea2.FoamTexDisturb = 0.1;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

            Whr.Sea2.Reflection = 0.5;
            Whr.Sea2.Transparency = 0.1;
            Whr.Sea2.Frenel = 0.3;
            Whr.Sea2.Attenuation = 0.3;
            Whr.Sea2.SkyColor = argb(0,155,155,155);
        break;
        //======================================================================================================================
        //                  СУША
        //======================================================================================================================
        case "light_breeze_land":	//лёгкий ветер суша
            SM_WaveType = 2;
            Whr.Sea2.Amp1 = 0.5;
            Whr.Sea2.AnimSpeed1 = 1.0;
            Whr.Sea2.Scale1 = 1.75;
            Whr.Sea2.MoveSpeed1 = "0.5, 0.0, 0.0";

            Whr.Sea2.Amp2 = 0.5;
            Whr.Sea2.AnimSpeed2 = 1.0;
            Whr.Sea2.Scale2 = 1.75;
            Whr.Sea2.MoveSpeed2 = "0.0, 0.0, -0.5";

            Whr.Sea2.BumpScale = 0.06;
            Whr.Sea2.PosShift = 1.75;

            Whr.Sea2.FoamV = 5.0;
            Whr.Sea2.FoamK = 0.0;
            Whr.Sea2.FoamUV = 0.3;
            Whr.Sea2.FoamTexDisturb = 0.7;
            Whr.Sea2.Frenel = 0.3;
            Whr.Sea2.Attenuation = 0.3;
            Whr.Sea2.Reflection = 0.6;
            Whr.Sea2.Transparency = 0.6;
            Whr.Sea2.SkyColor = argb(0,180,220,240);
            
			if (loc.type == "town")
			{
				if (loc.id == "Villemstad_town" || loc.id == "BasTer_town" || loc.id == "PortPax_town" || loc.id == "Maracaibo_town")
				{
					Whr.Sea2.MoveSpeed1 = "-4.0, 0.0, 0.0";
					Whr.Sea2.MoveSpeed2 = "0.0, 0.0, -0.25";
				}
			}
            else if (loc.type == "fort" || loc.type == "mayak" || loc.id == "Shore32" || loc.id == "Shore28")
            {
                 Whr.Sea2.BumpScale = 0.02;
				if (loc.type == "fort")
				{
					Whr.Sea2.MoveSpeed1 = "-4.0, 0.0, 0.0";
					Whr.Sea2.MoveSpeed2 = "0.0, 0.0, -0.25";
				}
            }
        break;

        case "breeze_land": //средний ветер суша
            SM_WaveType = 2;
            SeaAmp = fWind * 0.08 + 0.5;
            Whr.Sea2.Amp1 = SeaAmp;
            Whr.Sea2.AnimSpeed1 = 3.75;
            Whr.Sea2.Scale1 = 0.5;
            Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 5.0";

            Whr.Sea2.Amp2 = -0.5;
            Whr.Sea2.AnimSpeed2 = 7.0;
            Whr.Sea2.Scale2 = 2.5;
            Whr.Sea2.MoveSpeed2 = "0.0, 0.0, -1.0";

            Whr.Sea2.BumpScale = 0.06;
            Whr.Sea2.PosShift = 2.0;//остроконечность волн

            Whr.Sea2.FoamV = 0.2;
            Whr.Sea2.FoamK = 0.6;
            Whr.Sea2.FoamUV = 0.5;
            Whr.Sea2.FoamTexDisturb = 0.5;
            Whr.Sea2.Frenel = 0.3;
            Whr.Sea2.Attenuation = 0.2;

			if (loc.type == "town")
			{
				if (loc.id == "Villemstad_town")
				{
					Whr.Sea2.Amp1 = 2.0;
					Whr.Sea2.Amp2 = 0.5;
					Whr.Sea2.FoamK = 0.15;
					Whr.Sea2.MoveSpeed1 = "-5.0, 0.0, 0.0";
					Whr.Sea2.MoveSpeed2 = "1.0, 0.0, 0.0";
				}
				else if (loc.id == "BasTer_town")
				{
					Whr.Sea2.MoveSpeed1 = "-5.0, 0.0, 0.0";
					Whr.Sea2.MoveSpeed2 = "-0.25, 0.0, 0.25";
					Whr.Sea2.FoamUV = 0.085;
				}
				else if (loc.id == "PortPax_town")
				{
					Whr.Sea2.MoveSpeed1 = "-5.0, 0.0, 0.0";
					Whr.Sea2.MoveSpeed2 = "-0.25, 0.0, 0.25";
					Whr.Sea2.FoamUV = 0.085;
				}
				else if (loc.id == "Maracaibo_town")
				{
					Whr.Sea2.MoveSpeed1 = "-5.0, 0.0, 0.0";
					Whr.Sea2.MoveSpeed2 = "-0.25, 0.0, 0.25";
					Whr.Sea2.FoamUV = 0.085;
				}
				else if (loc.id == "PortRoyal_town")
				{
					Whr.Sea2.Amp2 = -0.8;
					Whr.Sea2.FoamK = 2.5;
				}
			}
            else if (loc.type == "fort")
            {
				Whr.Sea2.FoamV = 0.6;
				Whr.Sea2.MoveSpeed1 = "-5.0, 0.0, 0.0";
				Whr.Sea2.MoveSpeed2 = "-0.25, 0.0, 0.25";
				Whr.Sea2.FoamUV = 0.115;
            }
            else if (loc.type == "mayak" || loc.id == "Shore32" || loc.id == "Shore28")
            {
                 Whr.Sea2.BumpScale = 0.02;
            }
        break;

        case "strong_breeze_land": //сильный ветер суша
            SM_WaveType = 2;
            Whr.Sea2.Amp1 = 1.5;
            Whr.Sea2.AnimSpeed1 = 1.5;
            Whr.Sea2.Scale1 = 0.5;
            Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 3.0";

            Whr.Sea2.Amp2 = -1.0;
            Whr.Sea2.AnimSpeed2 = 3.0;
            Whr.Sea2.Scale2 = 2.5;
            Whr.Sea2.MoveSpeed2 = "1.0, 0.0, 1.0";

            Whr.Sea2.BumpScale = 0.06;
            Whr.Sea2.PosShift = 1.75;//остроконечность волн

            Whr.Sea2.FoamK = 0.3;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
            Whr.Sea2.FoamV = 0.02;//высота с которой начинаетс§ пена 21.0
            Whr.Sea2.FoamUV = 0.2; //тайлинг пены
            Whr.Sea2.FoamTexDisturb = 0.7;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

            Whr.Sea2.Reflection = 0.6;
            Whr.Sea2.Transparency = 0.4;
            Whr.Sea2.Frenel = 0.5;
            Whr.Sea2.Attenuation = 0.1;

            if (loc.type == "town")
            {
                if (loc.id == "Villemstad_town")
                {
					Whr.Sea2.MoveSpeed1 = "-3.0, 0.0, 0.0";
					Whr.Sea2.MoveSpeed2 = "-1.0, 0.0, -1.0";
					Whr.Sea2.FoamUV = 0.085;
					Whr.Sea2.Amp1 = 2.5;
					Whr.Sea2.Amp2 = -0.5;
					Whr.Sea2.FoamK = 0.07;
                }
                else if (loc.id == "PortRoyal_town")
                {
                    Whr.Sea2.Amp2 = -1.6;
                    Whr.Sea2.FoamK = 0.8;
                }
                else if (loc.id == "BasTer_town")
                {
					Whr.Sea2.MoveSpeed1 = "-3.0, 0.0, 0.0";
					Whr.Sea2.MoveSpeed2 = "-0.5, 0.0, 0.5";
					Whr.Sea2.FoamUV = 0.085;
                }
                else if (loc.id == "PortPax_town")
                {
					Whr.Sea2.MoveSpeed1 = "-3.0, 0.0, 0.0";
					Whr.Sea2.MoveSpeed2 = "0.5, 0.0, -0.5";
					Whr.Sea2.FoamUV = 0.085;
                }
                else if (loc.id == "Beliz_town")
                {
                    Whr.Sea2.Amp2 = -1.2;
                }
                else if (loc.id == "Maracaibo_town")
                {
					Whr.Sea2.MoveSpeed1 = "-3.0, 0.0, 0.0";
					Whr.Sea2.MoveSpeed2 = "-1.0, 0.0, -1.0";
					Whr.Sea2.FoamUV = 0.085;
                }
            }
            else if (loc.type == "fort" || loc.type == "mayak" || loc.id == "Shore32" || loc.id == "Shore28")
            {
                Whr.Sea2.Amp1 = 2.0;
                Whr.Sea2.Amp2 = 0.5;
                Whr.Sea2.FoamV = 0.7;//высота с которой начинаетс§ пена 21.0
                Whr.Sea2.FoamUV = 0.05; //тайлинг пены
                Whr.Sea2.FoamTexDisturb = 0.9;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0
                Whr.Sea2.BumpScale = 0.2;
				if (loc.type == "fort")
				{
					Whr.Sea2.MoveSpeed1 = "-5.0, 0.0, 0.0";
					Whr.Sea2.MoveSpeed2 = "-2.0, 0.0, -2.0";
					Whr.Sea2.FoamUV = 0.0095;
				}
            }
            else if (loc.type == "seashore")
            {
                Whr.Sea2.Amp1 = 1.5;
                Whr.Sea2.Amp2 = 0.2;
            }
        break;

        case "storm_land": //шторм суша
            SM_WaveType = 1;
            Whr.Sea2.Amp1 = 2.0;
            Whr.Sea2.AnimSpeed1 = 4.25;
            Whr.Sea2.Scale1 = 1.0;
            Whr.Sea2.MoveSpeed1 = "3.0, 0.0, 3.0";

            Whr.Sea2.Amp2 = -0.5;
            Whr.Sea2.AnimSpeed2 = 9.0;
            Whr.Sea2.Scale2 = 2.5;
            Whr.Sea2.MoveSpeed2 = "0.0, 0.0, 5.0";

            Whr.Sea2.BumpScale = 0.1; //Ю?О†ї? ђЭОНЯ
            Whr.Sea2.PosShift = 1.75;//остроконечность волн
            Whr.Sea2.LodScale = 0.5;
            Whr.Sea2.GridStep = 0.05;

            Whr.Sea2.FoamK = 0.2;//§ркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
            Whr.Sea2.FoamV = 0.2;//высота с которой начинаетс§ пена 21.0
            Whr.Sea2.FoamUV = 0.2; //тайлинг пены
            Whr.Sea2.FoamTexDisturb = 0.7;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

            Whr.Sea2.Reflection = 0.3;
            Whr.Sea2.Transparency = 0.1;
            Whr.Sea2.Frenel = 0.6;
            Whr.Sea2.Attenuation = 0.2;
            if (CheckAttribute(loc, "type"))
            {
                if (loc.type == "fort")
                {
                    Whr.Sea2.FoamV = 0.001;
                    Whr.Sea2.FoamK = 0.05;
                    Whr.Sea2.FoamUV = 0.5;
                }
                if (loc.type == "mayak")
                {
                    Whr.Sea2.FoamV = 0.001;
                    Whr.Sea2.FoamK = 0.2;
                }
            }
            Whr.Sea2.SkyColor = argb(0,60,70,80);
        break;

        case "stock_land": //стоячая вода
            SM_WaveType = 4;

            Whr.Sea2.Amp1 = 0.0;
            Whr.Sea2.AnimSpeed1 = 0.0;
            Whr.Sea2.Scale1 = 0.0;
            Whr.Sea2.MoveSpeed1 = "1.5, 0.0, 1.5";

            Whr.Sea2.Amp2 = 0.0;
            Whr.Sea2.AnimSpeed2 = 0.0;
            Whr.Sea2.Scale2 = 0.0;
            Whr.Sea2.MoveSpeed2 = "-1.5, 0.0, -1.5";

            Whr.Sea2.BumpScale = 0.08; //Ю?О†ї? ђЭОНЯ
            Whr.Sea2.PosShift = 0.0;//остроконечность волн
            Whr.Sea2.LodScale = 0.399;
            Whr.Sea2.GridStep = 0.081;

            Whr.Sea2.FoamK = 0.4;//яркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
            Whr.Sea2.FoamV = 2.5;////высота с которой начинаетс§ пена
            Whr.Sea2.FoamUV = 0.4; //тайлинг пены
            Whr.Sea2.FoamTexDisturb = 0.5;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

            Whr.Sea2.Reflection = 0.75;
            Whr.Sea2.Transparency = 1.3;
            Whr.Sea2.Frenel = 0.5;
            Whr.Sea2.Attenuation = 0.2;
        break;

        case "lake_land": //озёрная вода
            SM_WaveType = 5;

            Whr.Sea2.Amp1 = 0.5;
            Whr.Sea2.AnimSpeed1 = 0.1;
            Whr.Sea2.Scale1 = 1.75;
            Whr.Sea2.MoveSpeed1 = "0.0, 0.0, 0.0";

            Whr.Sea2.Amp2 = 0.5;
            Whr.Sea2.AnimSpeed2 = 0.1;
            Whr.Sea2.Scale2 = 1.75;
            Whr.Sea2.MoveSpeed2 = "0.0, 0.0, 0.0";

            Whr.Sea2.BumpScale = 0.07;
            Whr.Sea2.PosShift = 1.75;
            Whr.Sea2.LodScale = 0.399;
            Whr.Sea2.GridStep = 0.081;

            Whr.Sea2.FoamK = 0.4;//яркость пены по высоте 0.1 - пена §рка§ с 10 метров 1.0 через метр после начала
            Whr.Sea2.FoamV = 2.5;////высота с которой начинаетс§ пена
            Whr.Sea2.FoamUV = 1.4; //тайлинг пены
            Whr.Sea2.FoamTexDisturb = 0.5;//сдвиг по нормали. х.з. что это надо поюзать. значение от 0.0 до 1.0

            Whr.Sea2.Reflection = 0.7;
            Whr.Sea2.Transparency = 2.3;
            Whr.Sea2.Frenel = 0.7;
            Whr.Sea2.Attenuation = 1.7;
        break;
    }

    SM_ModifyLightness();
}

void Whr_ColorizeSeaWater()
{
    if (Whr_CheckUnderwater()) return; //под водой пропускаем
    //==================================================================================================================
    //       РАСКРАСКА ВОДЫ НА МОРЕ
    //==================================================================================================================
    if (bSeaActive && !bAbordageStarted)
    {
        //--> фикс затопления городов при переходе из открытого моря
        float distanceToIsland = Whr_GetNearestDistanceToIsland();
        float fBlend = distanceToIsland / 1800;
        if (Whr_CheckStorm()) Sea.MaxSeaHeight = 200.0;
        else if (distanceToIsland < 800.0) Sea.MaxSeaHeight = 6.0;
        else if (distanceToIsland < 1300.0) Sea.MaxSeaHeight = Whr_BlendFloat((distanceToIsland - 800.0) / 500.0, 6.0, 50.0);
        else if (distanceToIsland < 1800.0) Sea.MaxSeaHeight = Whr_BlendFloat((distanceToIsland - 1300.0) / 500.0, 50.0, 200.0);
        else Sea.MaxSeaHeight = 200.0;
        //<-- фикс затопления городов при переходе из открытого моря

        //красим дневное море в ясную погоду
        if (!Whr_CheckRain() && !Whr_CheckStorm() && !Whr_CheckSpecialLandFog() && GetTime() >= 10.0 && GetTime() < 18.0)
        {
            //лагуна
            if (distanceToIsland < 400.0)
            {
                Sea.Sea2.WaterColor = argb(0,0,170,150);
                Sea.Sea2.Transparency = 0.11;
                Sea.Sea2.Reflection = 0.65;
                Sea.Sea2.Frenel = 0.8;
                Sea.Sea2.Attenuation = 0.08;
            }
            //между лагуной и открытым морем (смешиваем цвета)
            else if (distanceToIsland < 1800.0)
            {
                Sea.Sea2.WaterColor = Whr_BlendColor(fBlend, argb(0,0,170,150), argb(0,0,40,70));
                Sea.Sea2.Transparency = Whr_BlendFloat(fBlend, 0.11, 0.1);
                Sea.Sea2.Reflection = Whr_BlendFloat(fBlend, 0.65, 0.4);
                Sea.Sea2.Frenel = Whr_BlendFloat(fBlend, 0.8, 0.6);
                Sea.Sea2.Attenuation = Whr_BlendFloat(fBlend, 0.08, 0.2);
            }
            //открытое море
            else
            {
                Sea.Sea2.WaterColor = argb(0,0,40,70);
            }
        }
        //вода в шторм
        else if (Whr_CheckStorm())
        {
            Sea.Sea2.WaterColor = argb(0,4,45,65);
            if (GetTime() < 6.0 || GetTime() >= 20.0) {
                Sea.Sea2.FoamK = 0.02;
                Sea.Sea2.Reflection = 0.3;
                Sea.Sea2.Transparency = 0.1;
                Sea.Sea2.WaterColor = argb(0,5,15,22);
            }
        }
        //ночная вода
        else if (GetTime() < 6.0 || GetTime() >= 21.0)
        {
            Sea.Sea2.FoamK = 0.1;
            Sea.Sea2.Reflection = 0.5;
            Sea.Sea2.Transparency = 0.1;
            Sea.Sea2.WaterColor = argb(0,5,10,20);
        }
        //вода в дождик
        else if (Whr_CheckRain())
        {
            Sea.Sea2.Reflection = 0.3;
            Sea.Sea2.Transparency = 0.1;
            Sea.Sea2.WaterColor = argb(0,10,25,40);
        }
        //цвет морской воды по умолчанию
        else
        {
            Sea.Sea2.WaterColor = argb(0,0,40,70);
        }
        return;
    }

    //==================================================================================================================
    //       РАСКРАСКА ВОДЫ НА СУШЕ
    //==================================================================================================================
    if (FindLocation(pchar.location) == -1)
    {
        if (Whr_CheckRain())
        {
            Sea.Sea2.Reflection = 0.4;
            Sea.Sea2.Transparency = 0.3;
        }
    }
    else
    {
        ref loc = &Locations[FindLocation(pchar.location)];
        if (!CheckAttribute(loc, "environment.sea") || loc.environment.sea == "false") return;

        //вначале выставляем общие цвета моря на время суток
        if (GetTime() >= 23.0 || GetTime() < 7.0)       Sea.Sea2.WaterColor = argb(0,0,30,40);
        else if (GetTime() >= 7.0 && GetTime() < 10.0)  Sea.Sea2.WaterColor = argb(0,5,30,60);
        else if (GetTime() >= 10.0 && GetTime() < 11.0) Sea.Sea2.WaterColor = argb(0,84,162,175);
        else if (GetTime() >= 11.0 && GetTime() < 18.0) Sea.Sea2.WaterColor = argb(0,0,170,150);
        else if (GetTime() >= 18.0 && GetTime() < 21.0) Sea.Sea2.WaterColor = argb(0,0,55,90);
        else if (GetTime() >= 21.0 && GetTime() < 23.0) Sea.Sea2.WaterColor = argb(0,0,60,70);

        //костылим особые случаи
        if (Whr_CheckStorm())
        {
            Sea.Sea2.WaterColor = argb(0,0,30,30);
        }
        else if (Whr_CheckRain())
        {
            Sea.Sea2.Reflection = 0.3;
            Sea.Sea2.Transparency = 0.3;
            if (GetTime() < 6.0 || GetTime() >= 20.0)       Sea.Sea2.WaterColor = argb(0,5,10,20);
            else if (GetTime() >= 6.0 && GetTime() < 10.0)  Sea.Sea2.WaterColor = argb(0,5,30,60);
            else if (GetTime() >= 10.0 && GetTime() < 20.0) Sea.Sea2.WaterColor = argb(0,0,55,90);
        }
        else if (loc.type == "seashore" || loc.type == "mayak")
        {
            if (loc.type == "mayak" || loc.id == "Shore32" || loc.id == "Shore28") Sea.MaxSeaHeight = 2.0;
            else if (loc.type == "seashore") Sea.MaxSeaHeight = 0.8;
            Sea.Sea2.Reflection = 0.6;
            if (GetTime() >= 23.0 || GetTime() < 7.0)
            {
                Sea.Sea2.Transparency = 0.5;
            }
            else if (GetTime() >= 7.0 && GetTime() < 9.0)
            {
                Sea.Sea2.Transparency = 1.4;
            }
            else if (GetTime() >= 9.0 && GetTime() < 10.0)
            {
                Sea.Sea2.Transparency = 1.4;
                if (sPreset == "strong_breeze_land") Sea.Sea2.WaterColor = argb(0,0,140,120);
            }
            else if (GetTime() >= 10.0 && GetTime() < 19.0)
            {
                Sea.Sea2.Transparency = 0.4;
                if (sPreset == "strong_breeze_land") Sea.Sea2.WaterColor = argb(0,0,140,120);
            }
            else if (GetTime() >= 19.0 && GetTime() < 21.0)
            {
                Sea.Sea2.Transparency = 1.0;
            }
            else if (GetTime() >= 21.0 && GetTime() < 23.0)
            {
                Sea.Sea2.Transparency = 1.0;
            }
            if (sPreset == "strong_breeze_land") Sea.Sea2.Transparency = 0.3;
        }
        else if (loc.type == "fort")
        {
            Sea.MaxSeaHeight = 2.0;
            Sea.Sea2.Reflection = 0.6;
            Sea.Sea2.Transparency = 0.6;
        }
        else if (loc.type == "town")
        {
            if (loc.id == "Villemstad_town") Sea.MaxSeaHeight = 1.0; //Виллемстанду можно повышать увроень моря и нельзя понижать
            else if (loc.id == "FortFrance_town") //при волнении в Форт де Франс морская вода попадает в канал, потому понижаем уровень моря в городе
            {
                if (sPreset == "strong_breeze_land") Sea.MaxSeaHeight = 0.25;
                else if (sPreset == "breeze_land") Sea.MaxSeaHeight = 0.45;
            }
            else if (loc.id == "PortRoyal_town" || loc.id == "Beliz_town") //при волнении в Порт-Ройал морская вода топит пристань, потому понижаем уровень моря в городе
            {
                if (sPreset == "strong_breeze_land") Sea.MaxSeaHeight = 0.23;
                else if (sPreset == "breeze_land") Sea.MaxSeaHeight = 0.25;
            }

            Sea.Sea2.Reflection = 0.6;
            Sea.Sea2.Transparency = 0.3;

            if (GetTime() >= 23.0 || GetTime() < 7.0)
            {
               // Sea.Sea2.FoamK = 1.0;
            }
            else if (GetTime() >= 7.0 && GetTime() < 9.0)
            {
               // Sea.Sea2.FoamK = 1.0;
            }
            else if (GetTime() >= 9.0 && GetTime() < 10.0)
            {
                if (sPreset == "strong_breeze_land") Sea.Sea2.WaterColor = argb(0,0,140,120);
            }
            else if (GetTime() >= 10.0 && GetTime() < 19.0)
            {
                //Sea.Sea2.FoamK = 1.0;
                if (sPreset == "strong_breeze_land") Sea.Sea2.WaterColor = argb(0,0,140,120);
            }
            else if (GetTime() >= 19.0 && GetTime() < 21.0)
            {
               // Sea.Sea2.FoamK = 1.25;
            }
            else if (GetTime() >= 21.0 && GetTime() < 23.0)
            {
               // Sea.Sea2.FoamK = 1.0;
            }
        }
        else if (HasStrEx(loc.type, "cave,plantation", "|"))
        {
            if (GetTime() >= 9.0 && GetTime() < 19.0) Sea.Sea2.WaterColor = argb(0,84,162,175);
        }
    }
}
	
// подсветку делаем динамической, где 2 часа ночи - мин, 2 часа дня - макс. +обновляем блик под новую текстуру отражения
void SM_ModifyLightness()
{
	float lightIntencity = SM_CurrentHourToLightIntencity();
	int r, g, b;
		
	r = 255;
	g = 255;
	b = 255;
	
	r = makeint(r * lightIntencity);
	g = makeint(g * lightIntencity);
	b = makeint(b * lightIntencity);
	
	aref arCurWeather = GetCurrentWeather();

	arCurWeather.Sky.Color = argb(0, r, g, b);
	Weather.Sky.Color = arCurWeather.Sky.Color;

	arCurWeather.Sun.Reflection.Size = 100 + 500 * lightIntencity;
	
//Log_TestInfo("SM_ModifyLightness: выбрано значение " + lightIntencity);
}

//получить дистанцию до ближайшего берега (бухты, маяка или города)
float Whr_GetNearestDistanceToIsland()
{
    float isR = 2250.0; //450.0 squared;
    if (pchar.location != WDM_NONE_ISLAND)
    {
        string island = pchar.location;
        int li = Findisland(island);
        if (li >= 0)
        {
            float psX, psZ;
            if (CheckAttribute(&WeatherParams, "Whr_ColorizeSeaWater.SAIL_TO_LOCATOR"))
            {
                psX = MakeFloat(WeatherParams.Whr_ColorizeSeaWater.SAIL_TO_LOCATOR.x);
                psZ = MakeFloat(WeatherParams.Whr_ColorizeSeaWater.SAIL_TO_LOCATOR.z);
                DeleteAttribute(&WeatherParams,"Whr_ColorizeSeaWater");
            }
            else if (CheckAttribute(&WeatherParams, "Whr_ColorizeSeaWater.SAIL_TO_CHARACTER"))
            {
                ref char = &Characters[sti(WeatherParams.Whr_ColorizeSeaWater.SAIL_TO_CHARACTER)];
                psX = MakeFloat(char.Ship.Pos.x);
                psZ = MakeFloat(char.Ship.Pos.z);
                DeleteAttribute(&WeatherParams,"Whr_ColorizeSeaWater");
            }
            else
            {
                psX = MakeFloat(pchar.Ship.Pos.x);
                psZ = MakeFloat(pchar.Ship.Pos.z);
            }

            aref rl;
            makearef(rl, Islands[li].reload);
            int num = GetAttributesNum(rl);
            for(int i = 0; i< num; i++)
            {
                string tempattrname = GetAttributeName(GetAttributeN(rl,i));
                aref e; makearef(e, rl.(tempattrname));
                if (CheckAttribute(e, "x"))
                {
                    float ix = stf(e.x);
                    float iz = stf(e.z);

                    float dist = GetDistance2D(psX, psZ, ix, iz);
                    int iGo = FindLocation(e.go);
                    string sType = "";
                    if (iGo >= 0) sType = Locations[iGo].type;
                    if(sType == "seashore" || sType == "town" || sType == "mayak")
                    {
                        if(dist < isR)
                        {
                            isR = dist;
                        }
                    }
                }
            }
        }
    }
    return isR;
}





void WhrDeleteSeaEnvironment()
{
	DeleteAttribute(&Sea,"");
}

void WhrCreateSeaEnvironment()
{
	int   i;
	float fMaxSeaHeight = 0.0;
	string sLocation = pchar.location;
	float FogDensity = 10.0;
	float FogSeaDensity = 10.0;
	aref aCurWeather = GetCurrentWeather();
	int locIndex = FindLocation(sLocation);

	DeleteAttribute(&Sea,"");

	if (locIndex != -1)
    {
        Sea.MaxVertices = 32000;
        Sea.MaxIndices = 33200;
        Sea.MaxWaveDistance = 10.0;
        Sea.MaxDim = 65536 * 8;
        Sea.MinDim = 128;
        Sea.GridStep = 0.081;// GridStepPC*5.0;

        Sea.Sea2.LodScale = 0.399;
        Sea.Sea2.GridStep = 0.081;
        Sea.Sea2.BumpScale = 0.3;

        if (Whr_CheckStorm())
        {
            //во время штормов внутри помещения уровень воды не поднимаем
            if (CheckAttribute(&locations[locIndex], "lockWeather") && locations[locIndex].lockWeather == "Inside") Sea.MaxSeaHeight = 0.5;
            else fMaxSeaHeight = 2.0;
        }
        else
        {
            fMaxSeaHeight = 0.5;
        }
        FogDensity = 100.0;
        FogSeaDensity = 100.0;
        Sea.MaxSeaDistance = 3600.0;
    }
    else
    {
        SetSeaSettings();
        Sea.MaxSeaDistance = 4500.0;
	}

    sPreset = WhrGetSeaPresetFromWind(fWeatherSpeed);
    WhrSetSeaPreset(iCurWeatherNum, fWeatherSpeed);

	aref	aSea;    makearef(aSea, aCurWeather.Sea);
	aref	aSea2;   makearef(aSea2, aCurWeather.Sea2);
	aref	aCommon; makearef(aCommon, WhrCommonParams.Sea);

	if (CheckAttribute(&Sea,"MaxSeaHeight")) { fMaxSeaHeight = stf(Sea.MaxSeaHeight); }
	//#20190613-01
	if(fMaxSeaHeight < 0.0) return;

	Sea.Clear = "";
	Sea.MaxSeaHeight = fMaxSeaHeight;

	Sea.Transparency = Whr_GetFloat(aSea,"Transparency");
	Sea.FrenelCoefficient = Whr_GetFloat(aSea,"FrenelCoefficient");
	Sea.WaterReflection = Whr_GetFloat(aSea,"WaterReflection");
	Sea.WaterAttenuation = Whr_GetFloat(aSea,"WaterAttenuation");

	Sea.Sea2.BumpScale = Whr_GetFloat(aSea2, "BumpScale");

	Sea.Lights = aCurWeather.Lights;

	Sea.Water.Color = Whr_GetColor(aSea,"Water.Color");

	Sea.Sun.Color = Whr_GetColor(aCurWeather,"Sun.Color");
	Sea.Sun.HeightAngle = Whr_GetFloat(aCurWeather,"Sun.HeightAngle");
	Sea.Sun.AzimuthAngle = Whr_GetFloat(aCurWeather,"Sun.AzimuthAngle");

	string sCurFog = Whr_GetCurrentFog();
	Sea.Fog.Color = Whr_GetColor(aCurWeather, sCurFog + ".Color");
	Sea.Fog.Enable = Whr_GetLong(aCurWeather, sCurFog + ".Enable");
	Sea.Fog.Start = Whr_GetFloat(aCurWeather, sCurFog + ".Start");
	Sea.Fog.Density = Whr_GetFloat(aCurWeather, sCurFog + ".Density") * FogDensity;
	Sea.Fog.SeaDensity = Whr_GetFloat(aCurWeather, sCurFog + ".SeaDensity") * FogSeaDensity;
	
	if(CheckAttribute(&TEV, "AscoldLeif_SetMists"))
	{
		WhrSea_SetMisteryMists();
	}
	
	Sea.Pena.Color = Whr_GetColor(aSea,"Pena.Color");
	Sea.Pena.DepthSmall = 20.0;
	Sea.Pena.DepthBig = 20.0;
	Sea.Pena.BigIslandMultiply = Whr_GetFloat(aCommon, "Pena.BigIslandMultiply");
	Sea.Pena.SmallIslandMultiply = Whr_GetFloat(aCommon, "Pena.SmallIslandMultiply");

	Sea.Bump.Dir = Whr_GetString(aSea, "Bump.Dir");
	Sea.Bump.Tile = Whr_GetFloat(aSea, "Bump.Tile");
	Sea.Bump.Ang = Whr_GetFloat(aSea, "Bump.Ang");
	Sea.Bump.Speed = Whr_GetFloat(aSea, "Bump.Speed");
	Sea.Bump.Scale = Whr_GetFloat(aSea, "Bump.Scale");
	Sea.Bump.AnimSpeed = Whr_GetFloat(aSea, "Bump.AnimSpeed");
	Sea.Bump.MipLevels = 4;
	Sea.Bump.Size = 128;

	Sea.GF2MX.BumpDir = Whr_GetString(aSea, "GF2MX.Bump.Dir");
	Sea.GF2MX.BumpTile = Whr_GetFloat(aSea, "GF2MX.Bump.Tile");
	Sea.GF2MX.BumpAnimSpeed = Whr_GetFloat(aSea, "GF2MX.Bump.AnimSpeed");
	Sea.GF2MX.WaterColor = Whr_GetColor(aSea, "GF2MX.Water.Color");
	Sea.GF2MX.SkyColor = Whr_GetColor(aSea, "GF2MX.Sky.Color");

	Sea.GF3.BumpDir = Whr_GetString(aSea, "Bump.Dir");
	Sea.GF3.BumpTile = Whr_GetFloat(aSea, "Bump.Tile");
	Sea.GF3.BumpAnimSpeed = Whr_GetFloat(aSea, "Bump.AnimSpeed");
	Sea.GF3.WaterColor = Whr_GetColor(aSea, "Water.Color");
	Sea.GF3.SkyColor = Whr_GetColor(aSea, "Sky.Color");

	// Sun road section
	Sea.Road.Start = Whr_GetFloat(aSea, "SunRoad.Start");
	Sea.Road.Color1 = Whr_GetColor(aSea, "SunRoad.Color1");
	Sea.Road.Color2 = Whr_GetColor(aSea, "SunRoad.Color2");
	Sea.Road.Power = Whr_GetFloat(aSea, "SunRoad.Power");

	if (CheckAttribute(aSea, "SunRoad.Special"))
	{
		Sea.Sun.HeightAngle = Whr_GetFloat(aSea, "SunRoad.Special.HeightAngle");
		Sea.Sun.AzimuthAngle = Whr_GetFloat(aSea, "SunRoad.Special.AzimuthAngle");
	}

	Sea.CubeMap.Size = 2048;
	Sea.CubeMap.VectorsSize = 1024;

	Sea.CubeMap.Format = "r5g6b5";

	Sea.Sky.Color = Whr_GetColor(aSea, "Sky.Color");

	// Advanced Sea initialize
	Sea.Sea2.WaterColor = Whr_GetColor(aSea2, "WaterColor");
	Sea.Sea2.SkyColor = Whr_GetColor(aSea2, "SkyColor");

	Sea.Sea2.Amp1 = Whr_GetFloat(aSea2, "Amp1");
	Sea.Sea2.AnimSpeed1 = Whr_GetFloat(aSea2, "AnimSpeed1");
	Sea.Sea2.Scale1 = Whr_GetFloat(aSea2, "Scale1");
	Sea.Sea2.MoveSpeed1 = Whr_GetString(aSea2, "MoveSpeed1");

	Sea.Sea2.Amp2 = Whr_GetFloat(aSea2, "Amp2");
	Sea.Sea2.AnimSpeed2 = Whr_GetFloat(aSea2, "AnimSpeed2");
	Sea.Sea2.Scale2 = Whr_GetFloat(aSea2, "Scale2");
	Sea.Sea2.MoveSpeed2 = Whr_GetString(aSea2, "MoveSpeed2");

	Sea.Sea2.PosShift = Whr_GetFloat(aSea2, "PosShift");

	Sea.Sea2.Reflection = Whr_GetFloat(aSea2, "Reflection");
	Sea.Sea2.Transparency = Whr_GetFloat(aSea2, "Transparency");
	Sea.Sea2.Attenuation = Whr_GetFloat(aSea2, "Attenuation");
	Sea.Sea2.Frenel = Whr_GetFloat(aSea2, "Frenel");

	Sea.Sea2.SimpleSea = sti(InterfaceStates.SimpleSea);

	//#20171220-01 Foam enable
	Sea.Sea2.FoamEnable = Whr_GetLong(aSea2, "FoamEnable");
	Sea.Sea2.FoamK = Whr_GetFloat(aSea2, "FoamK");
	Sea.Sea2.FoamV = Whr_GetFloat(aSea2, "FoamV");
	Sea.Sea2.FoamUV = Whr_GetFloat(aSea2, "FoamUV");
	Sea.Sea2.FoamTexDisturb = Whr_GetFloat(aSea2, "FoamTexDisturb");

	if (CheckAttribute(aSea2, "GridStep")) Sea.Sea2.GridStep = Whr_GetFloat(aSea2, "GridStep");
	if (CheckAttribute(aSea2, "LodScale")) Sea.Sea2.LodScale = Whr_GetFloat(aSea2, "LodScale");

	Sea.MaxSeaHeight = fMaxSeaHeight;
	Whr_ColorizeSeaWater(); //красим воду
	Sea.isDone = "";

	// boal 14/09/06 запоминаем стреднюю волну для моря (не локации)
	if (bSeaActive && !bAbordageStarted)
	{
		pchar.SystemInfo.ScaleSeaHeight = GetScaleSeaHeight();
	}
}

void SetSeaSettings()
{
	Sea.LodScale = LodScale;
	Sea.MaxVertices = MaxVertices;
	Sea.MaxIndices = MaxIndices;
	Sea.MaxWaveDistance = MaxWaveDistance;
	Sea.MaxDim = 65536 * 8;
	Sea.MinDim = 128;
	//Sea.GridStep = GridStepPC;
	Sea.GridStep = 0.1 + 0.1 * (1.0 - stf(InterfaceStates.SeaDetails));

	Sea.Sea2.LodScale = 0.399;
	Sea.Sea2.GridStep = 0.07 + 0.1 * (1.0 - stf(InterfaceStates.SeaDetails));
}

void SetSeaGridStep(float SeaDetails)
{
	if (!IsEntity(&Sea)) { return; }

	string sLocation = pchar.location;

	// if current location is land - return
	int iLoc = FindLocation(sLocation);
	if(iLoc != -1)
	{
		if(CheckAttribute(&locations[iLoc], "fastreload"))
		{
			return;
		}
	}

	Sea.Sea2.GridStep = 0.07 + 0.1 * (1.0 - SeaDetails);

	Sea.Sea2.SimpleSea = sti(InterfaceStates.SimpleSea);
}

// boal 14.09.06 относительная высота волны
float GetScaleSeaHeight()
{
	/*
	из ядра
	float fScale = (fMaxSeaHeight >= _fAmp1 + _fAmp2) ? 1.0f : fMaxSeaHeight / (_fAmp1 + _fAmp2);

		fAmp1 = _fAmp1 * fScale;
		fAmp2 = _fAmp2 * fScale;

    будеи считать среднюю волну как (а1 + а2)/2
	*/
	float fMaxSeaHeight = 0.0;

	if (CheckAttribute(&Sea, "MaxSeaHeight")) { fMaxSeaHeight = stf(Sea.MaxSeaHeight); }

	aref arWeath = GetCurrentWeather();
	float fAmp1, fAmp2;

	fAmp1 = stf(arWeath.Sea2.Amp1);
	fAmp2 = stf(arWeath.Sea2.Amp2);

	float fScale;
	if (fMaxSeaHeight >= (fAmp1 + fAmp2))
	{
		fScale = 1.0;
	}
	else
	{
		fScale = fMaxSeaHeight / (fAmp1 + fAmp2);
	}

	fAmp1 = fAmp1 * fScale;
	fAmp2 = fAmp2 * fScale;

	return (fAmp1 + fAmp2) / 2.0;
}

//проверка на наличие шторма
bool Whr_CheckStorm()
{
	return CheckAttribute(&WeatherParams, "Storm") && sti(WeatherParams.Storm);
}

//проверка на наличие шторма
bool Whr_CheckRain()
{
	return CheckAttribute(&WeatherParams,"Rain") && sti(WeatherParams.Rain);
}

//проверка на туманы
bool Whr_CheckSpecialLandFog()
{
	return CheckAttribute(&WeatherParams, "Fog.ThisDay") && sti(WeatherParams.Fog.ThisDay) && CheckAttribute(GetCurrentWeather(), "SpecialLandFog");
}

//проверка на подводные локации
bool Whr_CheckUnderwater()
{
	string sLocation = pchar.location;
	int iLocation = FindLocation(sLocation);
	if(iLocation != -1)
	{
		ref loc = &Locations[iLocation];
		if(CheckAttribute(loc, "type"))
		{
			bool bOk = loc.type == "underwater";
			if(bOk)
			{
				return true;
			}
		}
	}
	return false;
}

// Усиливаем фог по ветру - чем больше ветер, тем больше волны, чем больше волны - тем больше ляпы вдали, прячем в тумане.
void Whr_ModifySeaFog(ref weather)
{
    if (CheckAttribute(&weather, "SpecialLandFog") && Whr_CheckSpecialLandFog())
    {
        weather.Fog.Height = weather.SpecialLandFog.Height;
        weather.Fog.Start = weather.SpecialLandFog.Start;
        weather.Fog.IslandDensity = weather.SpecialLandFog.IslandDensity;
        weather.Fog.SeaDensity = weather.SpecialLandFog.SeaDensity;
        weather.Fog.Density = weather.SpecialLandFog.Density;
    }
    else if (Whr_CheckStorm())
    {
        weather.Fog.Height = 4000;
        weather.Fog.Start = 25;
        weather.Fog.Density = 0.005;
        weather.Fog.IslandDensity = 0.0015;
        weather.Fog.SeaDensity = 0.0025;
    }
    else if (Whr_CheckRain())
    {
        weather.Fog.Start = 25;
        weather.Fog.IslandDensity = 0.0002 + 0.00002 * pow(SM_WaveType, 3);
        weather.Fog.SeaDensity = 0.00075 + 0.00005 * pow(SM_WaveType, 3);
        weather.Fog.Density = 0.00010 + 0.00005 * pow(SM_WaveType, 3);
    }
    else if (Whr_CheckUnderwater())
    {
        // > под водой оставляем туман пресета как есть
    }
    else
    {
        weather.Fog.Start = 25;
        weather.Fog.IslandDensity = 0.0002 + 0.00002 * pow(SM_WaveType, 2);
        weather.Fog.SeaDensity = 0.00035 + 0.00005 * pow(SM_WaveType, 2);
        weather.Fog.Density = 0.00010 + 0.00005 * pow(SM_WaveType, 2);
    }
}

// Туман для квеста Лейфа - для обновления тумана на море (при старте локации)
void WhrSea_SetMisteryMists() {
	if (IsEntity(&Sea))
	{
		Sea.Fog.SeaDensity = weather.Fog.SeaDensity;
		Sea.Fog.Density = weather.Fog.Density;
	}
}
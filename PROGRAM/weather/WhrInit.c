#include "Weather\Init\Common.c"
#include "Weather\Init\Day.c"
#include "Weather\Init\Evening.c"
#include "Weather\Init\Morning.c"
#include "Weather\Init\Night.c"
#include "Weather\Init\Storm.c"
#include "Weather\Init\Special.c"

int InitWeather()
{
	int i, n = 0;
	ref rWeather;

	n = Whr_InitNight(n);
	n = Whr_InitMorning(n);
	n = Whr_InitDay(n);
	n = Whr_InitEvening(n);
	n = Whr_InitDayStorm(n);
	n = Whr_InitSpecial(n);

	Whr_InitCommon();

	Trace("Init weathers complete. " + n + " weathers found.");

	for (i = 0; i < n; i++)
	{
		rWeather = &Weathers[i];
		if (!CheckAttribute(rWeather, "Stars.Enable")) { rWeather.Stars.Enable = false; }
		if (!CheckAttribute(rWeather, "Planets.Enable")) { rWeather.Planets.Enable = false; }
		if (!CheckAttribute(rWeather, "Sun.Reflection.Enable")) { rWeather.Sun.Reflection.Enable = false; }
		if (!CheckAttribute(rWeather, "Sounds.Sea.Postfix")) { rWeather.Sounds.Sea.Postfix = ""; }
		if (!CheckAttribute(rWeather, "Sun.Moon")) { rWeather.Sun.Moon = false; }

		if (!CheckAttribute(rWeather, "Rain.DropsNearNum")) { rWeather.Rain.DropsNearNum = 0; }
		if (!CheckAttribute(rWeather, "Rain.DropsFarNum")) { rWeather.Rain.DropsFarNum = 0; }
		if (!CheckAttribute(rWeather, "Rain.DropsNearRadius")) { rWeather.Rain.DropsNearRadius = 12.0; }
		if (!CheckAttribute(rWeather, "Rain.DropsFarRadius")) { rWeather.Rain.DropsFarRadius = 55.0; }
		if (!CheckAttribute(rWeather, "Rain.DropsLifeTime")) { rWeather.Rain.DropsLifeTime = 0.25; }
		if (!CheckAttribute(rWeather, "Rain.DropsSize")) { rWeather.Rain.DropsSize = 0.07; }
		if (!CheckAttribute(rWeather, "Rain.DropsTexture")) { rWeather.Rain.DropsTexture = "weather\rain_drops.tga"; }
		if (!CheckAttribute(rWeather, "Rain.DropsColor")) { rWeather.Rain.DropsColor = argb(63, 255, 255, 255); }

		//#20171220-01 Foam enable
		if (!CheckAttribute(rWeather, "Sea2.FoamEnable")) { rWeather.Sea2.FoamEnable = true; }
		if (!CheckAttribute(rWeather, "Sea2.FoamK")) { rWeather.Sea2.FoamK = 0.1; }
		if (!CheckAttribute(rWeather, "Sea2.FoamV")) { rWeather.Sea2.FoamV = 5.0; }
		if (!CheckAttribute(rWeather, "Sea2.FoamUV")) { rWeather.Sea2.FoamUV = 0.05; }
		if (!CheckAttribute(rWeather, "Sea2.FoamTexDisturb")) { rWeather.Sea2.FoamTexDisturb = 0.7; }
	}

	return n;
}

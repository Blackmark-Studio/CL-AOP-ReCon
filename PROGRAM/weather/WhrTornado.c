object Tornado;

void WhrDeleteTornadoEnvironment()
{
	if (isEntity(&Tornado))
	{
		DeleteClass(&Tornado);
		DeleteAttribute(&Tornado,"");
		WeatherParams.Tornado = false;
	}
}

void WhrCreateTornadoEnvironment()
{
	aref aCurWeather = GetCurrentWeather();
// KK -->
	if (CheckAttribute(aCurWeather, "Tornado") == false || sti(aCurWeather.Tornado) != true) return;
	// > Запрет торнадо на суше
	if (sPreset == "storm_land") return;

	ref rTornado; makeref(rTornado, Tornado);
	float x = 10000.0;
	float z = 10000.0;
	if (CheckAttribute(rTornado, "init.x")) x = stf(rTornado.init.x);
	if (CheckAttribute(rTornado, "init.z")) z = stf(rTornado.init.z);

	DeleteAttribute(&Tornado,"");

	if (!isEntity(&Tornado))
	{
		CreateEntity(&Tornado,"Tornado");
	}

	Tornado.x = x;
	Tornado.z = z;
// <-- KK

	SendMessage(&Tornado, "f", 300.0 + frnd() * 600.0);
	LayerAddObject(SEA_EXECUTE, &Tornado, 65535);
	LayerAddObject(SEA_REALIZE, &Tornado, 65535);
}
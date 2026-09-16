
int LocationInitAruba(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Остров Аруба
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пляж67
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore67";
	locations[n].id.label = "Shore67";
	locations[n].image = "loading\outside\harbor.tga";
	locations[n].worldmap = "Aruba";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Aruba";
	//locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	//Models
	locations[n].filespath.models = "locations\Outside\Shores\Shore08";
	//Always
	Locations[n].models.always.shore08 = "shore08";
	locations[n].models.always.shore08.sea_reflection = 1;
	Locations[n].models.always.shore08seabed = "shore08_sb";
	Locations[n].models.always.locators = "shore08_locators";
	Locations[n].models.always.grassPatch = "shore08_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	//Day
	locations[n].models.day.charactersPatch = "shore08_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore08_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Aruba_Jungle_03";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Aruba";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли 1
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Aruba_Jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Aruba";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	//Models
	locations[n].filespath.models = "locations\Outside\JunglesN\Jungle2";
	//Always
	Locations[n].models.always.jungle = "jungle2";
	Locations[n].models.always.l1 = "jungle2_BSP";
	Locations[n].models.always.locators = "jungle2_locators";
	Locations[n].models.always.grassPatch = "jungle2_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l2 = "plan1";
	Locations[n].models.always.l2.level = 9;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "Jungle2_caveBlock";
	//Day
	locations[n].models.day.charactersPatch = "jungle2_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "Aruba_Jungle_03";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload3_back";
	locations[n].reload.l2.go = "Shore68";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore68";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "Aruba_Jungle_02";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;

	/*locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Aruba_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;*/
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли 2
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Aruba_jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Aruba";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	//Models
	locations[n].filespath.models = "locations\Outside\JunglesN\Jungle3";
	//Always
	Locations[n].models.always.jungle = "jungle3";
	Locations[n].models.always.l1 = "jungle3_BSP";
	Locations[n].models.always.locators = "jungle3_locators";
	Locations[n].models.always.grassPatch = "jungle3_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l2 = "plan1";
	Locations[n].models.always.l2.level = 9;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "istukan";
	//Day
	locations[n].models.day.charactersPatch = "jungle3_patch_i";
	//Night
	locations[n].models.night.charactersPatch = "jungle3_patch_i";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Aruba_CaveEntrance";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 3.7;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Aruba_jungle_01";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.7;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Aruba_IndianVillage";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Village";
	locations[n].locators_radius.reload.reload3_back = 6.1;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Деревня карибов
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Aruba_IndianVillage";
	locations[n].id.label = "Village";
	Locations[n].image = "loading\towns\pearl_1.tga";
	locations[n].indianVillage = true;
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Aruba";
	//Models
	Locations[n].filespath.models = "locations\Outside\IndianVillage";
	//Always
	Locations[n].models.always.village = "village";
	Locations[n].models.always.village.tech = "DLightModel";
	Locations[n].models.always.locators = "village_locators";
	Locations[n].models.always.grassPatch = "village_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	//Day
	locations[n].models.day.charactersPatch = "village_patch";
	//Night
	locations[n].models.night.charactersPatch = "village_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	Locations[n].reload.l1.name = "reload1_back";
	Locations[n].reload.l1.go = "Aruba_Jungle_02";
	Locations[n].reload.l1.emerge = "reload3";
	Locations[n].reload.l1.label = "Jungle";
	Locations[n].reload.l1.autoreload = 1;
	Locations[n].locators_radius.reload.reload1_back = 2;

	/*Locations[n].reload.l2.name = "reload2";
	Locations[n].reload.l2.go = "Dominica_shack1";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.label = "shack";
	Locations[n].reload.l2.autoreload = "0";

	Locations[n].reload.l3.name = "reload3";
	Locations[n].reload.l3.go = "Dominica_shack2";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.label = "shack";
	Locations[n].reload.l3.autoreload = "0";

	Locations[n].reload.l4.name = "reload4";
	Locations[n].reload.l4.go = "Dominica_shack3";
	Locations[n].reload.l4.emerge = "reload1";
	Locations[n].reload.l4.label = "shack";
	Locations[n].reload.l4.autoreload = "0";*/

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли 3
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Aruba_Jungle_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Aruba";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	//Models
	locations[n].filespath.models = "locations\Outside\Jungles\jungle14";
	//Always
	Locations[n].models.always.jungle = "jungle14";
	Locations[n].models.always.locators = "jungle14_locators";
	Locations[n].models.always.grassPatch = "jungle14_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "jungle14_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle14_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Aruba_Jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 3.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore67";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore67";
	locations[n].locators_radius.reload.reload2_back = 4.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Aruba_Outpost";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 3.3;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Лагерь Буканьеров
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Aruba_Outpost";
	locations[n].id.label = "Village";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Aruba";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle11";
	Locations[n].models.always.jungle = "jungle11";
	Locations[n].models.always.jungle.tech = "DLightModel";
	Locations[n].models.always.locators = "jungle11_locators";
	Locations[n].models.always.grassPatch = "jungle11_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	//Day
	locations[n].models.day.charactersPatch = "jungle11_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle11_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Aruba_Jungle_03";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Aruba_Deadlock";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли тупиковые
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Aruba_Deadlock";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Aruba";
	//Models
	locations[n].filespath.models = "locations\Outside\Jungles\jungle9";
	//Always
	Locations[n].models.always.jungle = "jungle9";
	Locations[n].models.always.locators = "jungle9_locators";
	Locations[n].models.always.grassPatch = "jungle9_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";
	//Locations[n].models.always.l4 = "jungle9_l1";
	//Day
	locations[n].models.day.charactersPatch = "jungle9_patch";
	//locations[n].models.day.charactersPatch = "jungle9_patch2";
	//Night
	locations[n].models.night.charactersPatch = "jungle9_patch";
	//locations[n].models.night.charactersPatch = "jungle9_patch2";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Aruba_Outpost";
	locations[n].reload.l1.emerge = "reload2_back";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Village";
	locations[n].locators_radius.reload.reload1_back = 2.2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Aruba_MinesEntrance";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в шахты
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Aruba_MinesEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Aruba";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt2";
	Locations[n].models.always.caveEnt2 = "caveEnt2";
	Locations[n].models.always.locators = "caveEnt2_locators";
	Locations[n].models.always.grassPatch = "caveEnt2_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	Locations[n].models.always.l4 = "plan4";
	Locations[n].models.always.l4.level = 6;
	Locations[n].models.always.l4.tech = "LocationModelBlend";
	//Day
	locations[n].models.day.charactersPatch = "caveEnt2_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Aruba_SaltMines";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Aruba_Deadlock";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	// шахты соляные Арубы
	///////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Aruba_SaltMines";
	locations[n].id.label = "mines";
	locations[n].image = "loading\inside\Mine.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Aruba";
	//Models
	locations[n].filespath.models = "locations\inside\DungeonOrange1";
	//Always
	locations[n].models.always.Aruba_SaltMines1 = "DungeonOrange1";
	locations[n].models.always.locators = "DungeonOrange1_locators";
	//locations[n].models.always.DungeonOrange1.tech = "DLightModel";
	//бочки и прочее не трогать
	locations[n].models.always.Aruba_SaltMines1_stuff = "DungeonOrange1_stuff";
	//locations[n].models.always.DungeonOrange1_stuff.tech = "DLightModel";
	//завал в шахте, который убирается по квесту
	//locations[n].models.always.DungeonOrange1_rocks = "DungeonOrange1_rocks";
	//locations[n].models.always.DungeonOrange1_rocks.tech = "DLightModel";
	//стена подвала, которая убирается по квесту
	locations[n].models.always.Aruba_SaltMines1_wall = "DungeonOrange1_wall";
	//locations[n].models.always.DungeonOrange1_wall.tech = "DLightModel";
	//после взрыва стены построили дверь с охранником
	locations[n].models.always.Aruba_SaltMines1_door = "DungeonOrange1_door";
	//locations[n].models.always.DungeonOrange1_door.tech = "DLightModel";
	locations[n].locators_radius.soldiers.protector1 = 1.5;
	locations[n].locators_radius.quest.mushketer2 = 2.0;
	//Day
	//locations[n].models.day.charactersPatch = "DungeonOrange1_patch1";
	//после разгребания завала или после постройки двери
	locations[n].models.day.charactersPatch = "DungeonOrange1_patch2";
	//полный доступ, взорвали стену и разгребли завал
	//locations[n].models.day.charactersPatch = "DungeonOrange1_patch3";
	//Night
	//locations[n].models.night.charactersPatch = "DungeonOrange1_patch1";
	//после разгребания завала или после постройки двери
	locations[n].models.night.charactersPatch = "DungeonOrange1_patch2";
	//полный доступ, взорвали стену и разгребли завал
	//locations[n].models.night.charactersPatch = "DungeonOrange1_patch3";

	//Environment
	locations[n].environment.weather = "true";
	locations[n].lockWeather = "Inside";
	locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Aruba_MinesEntrance";
	locations[n].reload.l1.emerge = "reload1";
	Locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	/*
	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "FortOrange_Town";
	locations[n].reload.l2.emerge = "reload19";
	Locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Town";*/
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Маяк Арубы
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*locations[n].id = "Aruba_Mayak";
	locations[n].id.label = "Mayak";
	locations[n].image = "loading\outside\lighthouse.tga";
	//Sound
	locations[n].type = "mayak";
	locations[n].islandId = "Aruba";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Lighthouse2";
	Locations[n].models.always.lighthouse = "lighthouse2";
	locations[n].models.always.lighthouse.sea_reflection = 1;
	Locations[n].models.always.lighthouseSeabed = "lighthouse2_sb";
	Locations[n].models.always.locators = "lighthouse2_locators";

	Locations[n].models.always.dooropen = "lighthouse2_dooropen";
	Locations[n].models.always.dooropen.tech = "DLightModel";

	Locations[n].models.always.windows = "lighthouse2_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 66530;

	Locations[n].models.always.grassPatch = "lighthouse2_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	//Day
	locations[n].models.day.winday = "lighthouse2_winday";
	locations[n].models.day.fonar = "lighthouse2_fd";
	locations[n].models.day.charactersPatch = "lighthouse2_patch";
	Locations[n].models.day.jumpPatch = "lighthouse2_jamp";

	locations[n].models.day.glassinday = "lighthouse2_glassinday";
	Locations[n].models.day.glassinday.tech = "LocationWindows";
	locations[n].models.day.glassinday.level = 66531;

	locations[n].models.day.glassonday = "lighthouse2_glassonday";
	Locations[n].models.day.glassonday.tech = "LocationWindows";
	locations[n].models.day.glassonday.level = 66532;
	//Night
	locations[n].models.night.volumeLight = "lighthouse2_volumeLight";
	locations[n].models.night.volumeLight.tech = "LighthouseLight";
	locations[n].models.night.volumeLight.level = 66529;

	locations[n].models.night.fonar = "lighthouse2_fn";
	locations[n].models.night.winnight = "lighthouse2_winnight";
	locations[n].models.night.winnight.tech = "LighthouseLight";
	locations[n].models.night.winnight.level = 66529;
	locations[n].models.night.charactersPatch = "lighthouse2_patch";
	Locations[n].models.night.jumpPatch = "lighthouse2_jamp";

	locations[n].models.night.glassinnight = "lighthouse2_glassinnight";
	Locations[n].models.night.glassinnight.tech = "LocationWindows";
	locations[n].models.night.glassinnight.level = 66531;

	locations[n].models.night.glassonnight = "lighthouse2_glassonnight";
	Locations[n].models.night.glassonnight.tech = "LocationWindows";
	locations[n].models.night.glassonnight.level = 66532;

	locations[n].models.night.fonaronnight = "lighthouse2_fonaronnight";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Aruba_village";
	locations[n].reload.l1.emerge = "reload2_back";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Village";
	locations[n].locators_radius.reload.reload1_back = 3.0;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Aruba";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 12.0;

	locations[n].reload.l3.name = "reload2";
	locations[n].reload.l3.go = "Mayak2_Lighthouseroom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.label = "room";
	locations[n].locators_radius.reload.reload2 = 1.0;
	n = n + 1;*/

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пляж68
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore68";
	locations[n].id.label = "Shore68";
	locations[n].image = "loading\outside\harbor.tga";
	locations[n].worldmap = "Aruba";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Aruba";
	//locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	//Models
	locations[n].filespath.models = "locations\Outside\Shores\Shore06";
	//Always
	Locations[n].models.always.shore06 = "shore06";
	locations[n].models.always.shore06.sea_reflection = 1;
	Locations[n].models.always.shore06seabed = "shore06_sb";
	Locations[n].models.always.locators = "shore06_locators";

	Locations[n].models.always.grassPatch = "shore06_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";
	//Day
	locations[n].models.day.charactersPatch = "shore06_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore06_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Aruba_Jungle_01";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Aruba";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Aruba_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Aruba";
	locations[n].DisableEncounters = true;
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\CaveEnt1";
	Locations[n].models.always.caveEnt1 = "caveEnt1";	
	Locations[n].models.always.locators = "caveEnt1_locators";		
	Locations[n].models.always.grassPatch = "caveEnt1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";
	Locations[n].models.always.l3 = "plan3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "LocationModelBlend";	
	//Day
	locations[n].models.day.charactersPatch = "caveEnt1_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt1_patch";	
	//Environment	
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "Aruba_Grot";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Grot";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Aruba_Jungle_02";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Aruba_Grot";
	locations[n].id.label = "Grot";
    locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Aruba";
	locations[n].onUninhabitedIsland = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\grotto1";
	locations[n].models.always.grotto1 = "grotto1";
	locations[n].models.always.grotto1alpha = "grotto1_alpha";
	Locations[n].models.always.grotto1alpha.tech = "LocationWindows";	
	locations[n].models.always.grotto1alpha.level = 65532;
	locations[n].models.always.chest = "chest";	
	locations[n].models.always.locators = "grotto1_locators";

	// EvgAnat - "дикие Карибы", убираем дефолтные сферы
	locations[n].locators_radius.item.duhi1 = 0.0;
	
/*	Locations[n].models.always.rays = "grotto1_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;	*/
	//Day
	locations[n].models.day.charactersPatch = "grotto1_patch";
	//Night
	locations[n].models.night.charactersPatch = "grotto1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Aruba_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;

	return n;
}


int LocationInitLaVega(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОРОД
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_town";
	locations[n].id.label = "Street";
	locations[n].image = "loading\Town.tga";
	locations[n].worldmap = "LaVega_town";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	//Town sack
	locations[n].townsack = "LaVega";
	//Sound
	locations[n].type = "town";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	//Always
	locations[n].filespath.models = "locations\Town_LaVega\Town\";
	locations[n].models.always.town = "LaVega";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.L1 = "LaVega_signsA";
	locations[n].models.always.seabed = "LaVega_sb";
	locations[n].models.always.locatorsl2 = "LaVega_1";
	locations[n].models.always.locatorsl3 = "LaVega_locators";
	// Locations[n].models.always.locatorsl5 = "LaVega_quest";
	// Locations[n].models.always.locatorsl6 = "LaVega_1_quest";
	// Locations[n].models.always.locatorsl7 = "LaVega_locators_quest";
	locations[n].models.always.grassPatch = "LaVega_grass";
	
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.level = 9;

	//WindMill Fan
	locations[n].models.always.MillFan = "MillFan";
	Locations[n].models.always.MillFan.locator.group = "WindMill";
	Locations[n].models.always.MillFan.locator.name ="Fan";	
	Locations[n].models.always.MillFan.rotate.x = 0.0;
	Locations[n].models.always.MillFan.rotate.y = 0.0;
	Locations[n].models.always.MillFan.rotate.z = 0.3;

	//Day
	locations[n].models.day.fonar = "LaVega_fd";
	locations[n].models.day.charactersPatch = "LaVega_patch_day";
    //	locations[n].models.day.charactersPatch = "LaVega_patch_day_quest";
	locations[n].models.day.rinok = "LaVega_rinok";
	//Night
	locations[n].models.night.fonar = "LaVega_fn";
	locations[n].models.night.charactersPatch = "LaVega_patch_night";
    //	locations[n].models.night.charactersPatch = "LaVega_patch_night_quest";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map

    // --> Типовые городские локации, четкая фиксация на 10 номеров.
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Hispaniola1";
	locations[n].reload.l1.emerge = "reload_4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 4.6;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go =  "LaVega_ExitTown";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.5;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go =  "LaVega_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "LaVega_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "LaVega_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "store";
	locations[n].reload.l6.close_for_night = 1;
	
	/*
	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "LaVega_Bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;
	
	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "LaVega_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";
	locations[n].reload.l10.disable = 1; // Закроем на совсем
	*/

    // --> Комоны, загрушки. Номера с начинаются с 20.
	locations[n].reload.l20.name = "houseSp1";
	locations[n].reload.l20.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";
    
 	locations[n].reload.l21.name = "houseSp2";
	locations[n].reload.l21.go = "CommonStoneHouse";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House";

	locations[n].reload.l22.name = "reloadH1";
	locations[n].reload.l22.go = "CommonRoom_MH";
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";

	locations[n].reload.l23.name = "houseSp4";
	locations[n].reload.l23.go = "LaVega_CommonRoom_MH9_2";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";

	locations[n].reload.l24.name = "houseSp5";
	locations[n].reload.l24.go = "LaVega_CommonRoom_MH9_2";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "House";
	locations[n].reload.l24.disable = 1; // Закроем на совсем

     // --> Квестовые локации 
	/*locations[n].reload.l11.name = "reloadH1";
	locations[n].reload.l11.go = "LaVega_HouseHut1";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l11.autoreload = "0";
	locations[n].reload.l11.label = "House";*/

	locations[n].reload.l12.name = "houseSp3"; // вход в дом Эммы
	locations[n].reload.l12.go = "LaVega_roof";
	locations[n].reload.l12.emerge = "reload1";
	locations[n].reload.l12.autoreload = "0";
	locations[n].reload.l12.label = "House";

	locations[n].reload.l13.name = "reloadH2";
	locations[n].reload.l13.go = "LaVega_Hut1";
	locations[n].reload.l13.emerge = "reload1";
	locations[n].reload.l13.autoreload = "0";
	locations[n].reload.l13.label = "House";

	locations[n].reload.l14.name = "reloadF3";
	locations[n].reload.l14.go = "LaVega_sklad03";
	locations[n].reload.l14.emerge = "reload1";
	locations[n].reload.l14.autoreload = "0";
	locations[n].reload.l14.label = "House";
	locations[n].reload.l14.close_for_night = 1;

	// здесь не на что смотреть!
	locations[n].reload.l15.name = "reload5_back";
	locations[n].reload.l15.go = "LaVega_sklad03";
	locations[n].reload.l14.emerge = "reload1";
	locations[n].reload.l15.autoreload = "0";
	locations[n].reload.l15.label = "House";
	locations[n].reload.l15.disable = 1;

	locations[n].reload.l16.name = "reloadF2";
	locations[n].reload.l16.go = "LaVega_sklad03";
	locations[n].reload.l16.emerge = "reload1";
	locations[n].reload.l16.autoreload = "0";
	locations[n].reload.l16.label = "House";
	locations[n].reload.l16.disable = 1;

	locations[n].reload.l17.name = "reloadF4";
	locations[n].reload.l17.go = "LaVega_sklad03";
	locations[n].reload.l17.emerge = "reload1";
	locations[n].reload.l17.autoreload = "0";
	locations[n].reload.l17.label = "House";
	locations[n].reload.l17.disable = 1;

	locations[n].reload.l18.name = "reload9";
	locations[n].reload.l18.go = "LaVega_sklad03";
	locations[n].reload.l18.emerge = "reload1";
	locations[n].reload.l18.autoreload = "0";
	locations[n].reload.l18.label = "House";
	locations[n].reload.l18.disable = 1;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Таверна Ла Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	locations[n].id = "LaVega_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\Tavern09\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "LaVega";
 	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.tavern = "Tavern09";
	locations[n].models.always.locators = "Tavern09_locators";
	locations[n].models.always.window = "Tavern09_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Tavern09_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern09_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "LaVega_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната в таверне наверху, Ла Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.locators = "Tavern_room_locators";
	locations[n].models.always.tavern = "Tavern_room";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "tavern_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Tavern_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LaVega_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Магазин Ла Вега
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_store";
	locations[n].id.label = "Store";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\StoreSmall\";
	locations[n].models.always.locators = "StoreSmall_locators";
	locations[n].models.always.store = "StoreSmall";
	locations[n].models.always.window = "StoreSmall_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;
    locations[n].models.always.L1 = "storeSmall_part";
    locations[n].models.always.L1.tech = "DLightModel";

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "StoreSmall_patch";
	//Night
	locations[n].models.night.charactersPatch = "StoreSmall_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	////////////////////////==> комната в магазине
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonRoom_MH10";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Маленькая резиденция из ПКМ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_townhall";
	locations[n].id.label = "Residence";
	locations[n].image = "loading\inside\pirateresidence01.tga";
	//locations[n].MustSetReloadBack = true;

	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "LaVega";
 	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\residence_PKM";
	locations[n].models.always.locators = "ResP_locators";
	locations[n].models.always.tavern = "ResP";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "ResP_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "ResP_patch";
	//Night
	locations[n].models.night.charactersPatch = "ResP_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом Ремедиос
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_roof";
	locations[n].filespath.models = "locations\inside\FlamHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\flamhouse.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.tavern = "FlamHouse";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "FlamHouse_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.day.locators = "FlamHouse_locators";
	locations[n].models.night.locators = "FlamHouse_Nlocators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "FlamHouse_patch";
	//Night
	locations[n].models.night.charactersPatch = "FlamHouse_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "houseSp3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload3";
	locations[n].reload.l2.go = "LaVega_MH12";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";

	locations[n].reload.l3.name = "reload4";
	locations[n].reload.l3.go = "LaVega_JinoRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом из трёх комнат (комната 3)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_MH12";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\flamhouse.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	locations[n].islandId = "Hispaniola";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LaVega";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\mediumhouse11_12";
	locations[n].models.always.locators = "mediumhouse11_locators";
	locations[n].models.always.house = "mediumhouse11";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "mediumhouse11_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;

	//Day
	locations[n].models.day.charactersPatch = "mediumhouse11_patch";
	//Night
	locations[n].models.night.fonar = "mediumhouse11_fn";
	locations[n].models.night.charactersPatch = "mediumhouse11_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LaVega_roof";
	locations[n].reload.l3.emerge = "reload3";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната из ККС
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_JinoRoom";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\flamhouse.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	locations[n].islandId = "Hispaniola";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LaVega";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\JinoRoom";
	locations[n].models.always.locators = "JinoRoom_locators";
	locations[n].models.always.house = "JinoRoom";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "JinoRoom_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;

	//Day
	locations[n].models.day.charactersPatch = "JinoRoom_patch";
	//Night
	locations[n].models.night.fonar = "JinoRoom_Nlocators";
	locations[n].models.night.charactersPatch = "JinoRoom_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_roof";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Средний дом 8 (9 с заменённой стенкой)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_CommonRoom_MH9_2";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse08.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	locations[n].islandId = "Hispaniola";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LaVega";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\mediumhouse08";
	locations[n].models.always.house = "mediumhouse09";
	locations[n].models.always.house.level = 65538;
	locations[n].models.day.locators = "mediumhouse09_locators";
	locations[n].models.night.locators = "mediumhouse09_Nlocators";

	Locations[n].models.always.mediumhouse09windows = "mediumhouse09_windows";
	Locations[n].models.always.mediumhouse09windows.tech = "LocationWindows";
	locations[n].models.always.mediumhouse09windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.mediumhouse09rand= "mediumhouse09_rand";
	locations[n].models.day.charactersPatch = "mediumhouse09_patch";
	//Night
	locations[n].models.night.charactersPatch = "mediumhouse09_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "houseSp4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Изба рыбака
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_Hut1";
	locations[n].filespath.models = "locations\inside\Hut1_KNS";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\littlehut.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "LaVega";
	locations[n].lockWeather = "Inside";
	locations[n].islandId = "Hispaniola";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LaVega";
	//Models
	//Always
	locations[n].models.always.locators = "Hut1_locators";
	locations[n].models.always.tavern = "Hut1";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Hut1_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut1_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	Locations[n].QuestlockWeather = "23 Hour";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reloadH2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Склад 03 (ККС)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_sklad03";
	locations[n].id.label = "Warehouse";
	locations[n].image = "loading\inside\Sklad.tga";
	locations[n].MustSetReloadBack = true;
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LaVega";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Sklad03";
	locations[n].models.always.locators = "sklad03_locators";
	locations[n].models.always.modelSklad = "sklad03";
	locations[n].models.always.modelSklad.level = 65538;
	//Day
	locations[n].models.day.charactersPatch = "sklad03_patch";
	//Night
	locations[n].models.night.charactersPatch = "sklad03_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reloadF3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	return n;
}

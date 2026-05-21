
int LocationInitSantoDomingo(int n)
{

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОРОД
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_town";
	locations[n].id.label = "Street";
	locations[n].worldmap = "SantoDomingo";

	locations[n].townsack = "SantoDomingo";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";

	locations[n].filespath.models = "locations\Town_SantoDomingo\Town\";
	locations[n].image = "loading\Town.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	//==> флаг генерации квестодателя по розыску кэпов, int значение - шанс что сам заговорит(1-10)
	locations[n].questSeekCap = 5;
	//Sound
	locations[n].type = "town";
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	//Always
	locations[n].models.always.town = "Margarita";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.L1 = "Margarita1";
	locations[n].models.always.L2 = "Margarita_prison";
    locations[n].models.always.L2.tech = "DLightModel";
	locations[n].models.always.locatorsL1 = "Margarita_locators";
	locations[n].models.always.grassPatch = "Margarita_grass";	
	locations[n].models.always.seabed = "Margarita_sb";
	//Fontain
	locations[n].models.always.Waterfall1 = "fontain1";
	locations[n].models.always.Waterfall1.uvslide.v0 = 0.5;
    locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall1.level = 50;
	
	locations[n].models.always.Waterfall2 = "fontain2";
	locations[n].models.always.Waterfall2.uvslide.v0 = 0.2;
    locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall2.level = 49;

	//Day
	locations[n].models.day.fonar = "Margarita_fd";
	locations[n].models.day.charactersPatch = "Margarita_patch_day";
	locations[n].models.day.rinok = "Margarita_rinok";
	Locations[n].models.day.jumpPatch = "Margarita_jump_patch";
	//Night
	locations[n].models.night.fonar = "Margarita_fn";
	locations[n].models.night.charactersPatch = "Margarita_patch_night";
	Locations[n].models.night.jumpPatch = "Margarita_jump_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map

    // --> Типовые городские локации, четкая фиксация на 10 номеров.
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Hispaniola1";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 2.5;
	
	locations[n].reload.l2.name = "Store_61";
	locations[n].reload.l2.go = "SantoDomingo_store";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Store";
	locations[n].reload.l2.close_for_night = 1;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "SantoDomingo_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "SantoDomingo_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "SantoDomingo_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "SantoDomingo_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "reload7_back";
	locations[n].reload.l7.go = "SantoDomingo_church";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Church";
	//locations[n].reload.l7.close_for_night = 1;

	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "SantoDomingo_Bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;

	locations[n].reload.l9.name = "reload9_back";
	locations[n].reload.l9.go = "SantoDomingo_brothel";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Brothel";

	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "SantoDomingo_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";
	locations[n].reload.l10.close_for_night = 1;

	locations[n].reload.gate.name = "gate_back";
	locations[n].reload.gate.go = "SantoDomingo_ExitTown";
	locations[n].reload.gate.emerge = "reload1";
	locations[n].reload.gate.autoreload = "0";
	locations[n].reload.gate.label = "ExitTown";
	locations[n].locators_radius.reload.gate_back = 2.2;
	
	locations[n].reload.jail.name = "reload_jail";
	locations[n].reload.jail.go = "SantoDomingo_prison";
	locations[n].reload.jail.emerge = "reload1";
	locations[n].reload.jail.autoreload = "0";
	locations[n].reload.jail.label = "Prison";

    // --> Комоны, загрушки. Номера с начинаются с 20.
	locations[n].reload.l20.name = "houseSp1";
	locations[n].reload.l20.go = "CommonResidence_2";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";

 	locations[n].reload.l21.name = "houseSp2";
	locations[n].reload.l21.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House";

	locations[n].reload.l22.name = "houseSp3";
	locations[n].reload.l22.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";

	locations[n].reload.l23.name = "houseF1";
	locations[n].reload.l23.go = "CommonRoom_MH9";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";

	locations[n].reload.l24.name = "houseF2";
	locations[n].reload.l24.go = "CommonStoneHouse";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "House";

	locations[n].reload.l25.name = "houseF4";
	locations[n].reload.l25.go = "CommonStoneHouse";
	locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "House";

	locations[n].reload.l26.name = "houseH1";
	locations[n].reload.l26.go = "CommonRoom_MH3";
	locations[n].reload.l26.emerge = "reload1";
	locations[n].reload.l26.autoreload = "0";
	locations[n].reload.l26.label = "House";

	locations[n].reload.l27.name = "houseH2";
	locations[n].reload.l27.go = "CommonRoom_MH4";
	locations[n].reload.l27.emerge = "reload1";
	locations[n].reload.l27.autoreload = "0";
	locations[n].reload.l27.label = "House";

	locations[n].reload.l28.name = "houseS3";
	locations[n].reload.l28.go = "CommonPirateHouse";
	locations[n].reload.l28.emerge = "reload1";
	locations[n].reload.l28.autoreload = "0";
	locations[n].reload.l28.label = "House";

	locations[n].reload.l29.name = "houseS4";
	locations[n].reload.l29.go = "CommonCobHouse";
	locations[n].reload.l29.emerge = "reload1";
	locations[n].reload.l29.autoreload = "0";
	locations[n].reload.l29.label = "House";

	locations[n].reload.l30.name = "houseS5";
	locations[n].reload.l30.go = "CommonRoom_MH";
	locations[n].reload.l30.emerge = "reload1";
	locations[n].reload.l30.autoreload = "0";
	locations[n].reload.l30.label = "House";

	locations[n].reload.l31.name = "houseS_1";
	locations[n].reload.l31.go = "CommonRoom_MH2";
	locations[n].reload.l31.emerge = "reload1";
	locations[n].reload.l31.autoreload = "0";
	locations[n].reload.l31.label = "House";

 // --> Псевдоквестовые локации.
	locations[n].reload.l32.name = "houseK_2";
	locations[n].reload.l32.go = "SantoDomingo_roof"; //дом с выходом на крышу
	locations[n].reload.l32.emerge = "reload1";
	locations[n].reload.l32.autoreload = "0";
	locations[n].reload.l32.label = "House";

	locations[n].reload.l33.name = "houseF3";
	locations[n].reload.l33.go = "SantoDomingo_MH11";
	locations[n].reload.l33.emerge = "reload2";
	locations[n].reload.l33.autoreload = "0";
	locations[n].reload.l33.label = "House";

	locations[n].reload.l34.name = "houseK_1";
	locations[n].reload.l34.go = "SantoDomingo_MH11";
	locations[n].reload.l34.emerge = "reload1";
	locations[n].reload.l34.autoreload = "0";
	locations[n].reload.l34.label = "House";

	locations[n].reload.l35.name = "houseK_5";
	locations[n].reload.l35.go = "BigHouseKNS_SD";
	locations[n].reload.l35.emerge = "reload1";
	locations[n].reload.l35.autoreload = "0";
	locations[n].reload.l35.label = "House";

	locations[n].reload.l36.name = "houseK_6";
	locations[n].reload.l36.go = "BigHouseKNS_SD";
	locations[n].reload.l36.emerge = "reload2";
	locations[n].reload.l36.autoreload = "0";
	locations[n].reload.l36.label = "House";

	locations[n].reload.l37.name = "houseK_7";
	locations[n].reload.l37.go = "BigHouseKNS_SD";
	locations[n].reload.l37.emerge = "reload3";
	locations[n].reload.l37.autoreload = "0";
	locations[n].reload.l37.label = "House";
        locations[n].reload.l37.disable = 1; // Закроем на совсем

	locations[n].reload.l38.name = "houseS1";
	locations[n].reload.l38.go = "Smallhome_K2";
	locations[n].reload.l38.emerge = "reload1";
	locations[n].reload.l38.autoreload = "0";
	locations[n].reload.l38.label = "House";
        locations[n].reload.l38.disable = 1; // Закроем на совсем

	locations[n].reload.l39.name = "houseS2";
	locations[n].reload.l39.go = "Smallhome_K2";
	locations[n].reload.l39.emerge = "reload1";
	locations[n].reload.l39.autoreload = "0";
	locations[n].reload.l39.label = "House";
        locations[n].reload.l39.disable = 1; // Закроем на совсем

	locations[n].reload.l40.name = "houseK_4";
	locations[n].reload.l40.go = "BigHouseKNS_SD";
	locations[n].reload.l40.emerge = "reload3";
	locations[n].reload.l40.autoreload = "0";
	locations[n].reload.l40.label = "House";

	locations[n].reload.l41.name = "houseH3";
	locations[n].reload.l41.go = "Smallhome_K2";
	locations[n].reload.l41.emerge = "reload1";
	locations[n].reload.l41.autoreload = "0";
	locations[n].reload.l41.label = "House";

	locations[n].reload.l42.name = "houseA_1";
	locations[n].reload.l42.go = "SantoDomingo_Admiralty";
	locations[n].reload.l42.emerge = "reload1";
	locations[n].reload.l42.autoreload = "0";
	locations[n].reload.l42.label = "PortOffice";
	locations[n].reload.l42.close_for_night = 1;

	locations[n].reload.l62.name = "Store_62";
	locations[n].reload.l62.go = "SantoDomingo_sklad02";
	locations[n].reload.l62.emerge = "reload1";
	locations[n].reload.l62.autoreload = "0";
	locations[n].reload.l62.label = "Shipyard";
	locations[n].reload.l62.close_for_night = 1;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ТАВЕРНА
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\Tavern08\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.tavern = "Tavern08";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "Tavern08_locators";
	locations[n].models.always.window = "Tavern08_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Tavern08_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern08_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "SantoDomingo_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// КОМНАТА В ТАВЕРНЕ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_tavern_upstairs";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Tavern_room";
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
	locations[n].reload.l1.go = "SantoDomingo_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// МАГАЗИН
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\store01\";
	locations[n].image = "loading\inside\shop.tga";

	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.locators = "Store01_locators";
	locations[n].models.always.store = "Store01";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Store01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Store01_patch";
	//Night
	locations[n].models.night.charactersPatch = "Store01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.camdetector.camera1 = 5;
    ////////////////////////==> комната в магазине
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonPackhouse_1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "packhouse";
	LAi_LocationFightDisable(&locations[n], true);

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "SantoDomingo_town";
	locations[n].reload.l3.emerge = "Store_61";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Склад 02 не имеет отношение к магазину.
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_sklad02";
	locations[n].id.label = "Warehouse";
	locations[n].image = "loading\inside\Sklad_0.tga";
	locations[n].MustSetReloadBack = true;
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Sklad02";
	locations[n].models.always.locators = "sklad02_locators";
	locations[n].models.always.modelSklad = "sklad02";
	locations[n].models.always.modelSklad.level = 65538;
	//Day
	locations[n].models.day.charactersPatch = "sklad02_patch";
	//Night
	locations[n].models.night.charactersPatch = "sklad02_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "Store_62";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РОСТОВЩИК
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_Bank";
	locations[n].id.label = "Usurer House";
	locations[n].filespath.models = "locations\inside\Bank02\";
	locations[n].image = "loading\inside\bank.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.locators = "Bank02_locators";
	locations[n].models.always.store = "Bank02";
	locations[n].models.always.window = "bank02_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Bank02_patch";
	//Night
	locations[n].models.night.charactersPatch = "Bank02_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "reload8";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "SantoDomingo_bankvault";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Хранилище (Банк)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_bankvault";
	locations[n].id.label = "bankvault";
	locations[n].image = "loading\inside\vault.tga";
	//locations[n].MustSetReloadBack = true;
	//locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\bankvault01";
	locations[n].models.always.warehouse = "Store06";
	locations[n].models.always.warehouse.level = 65538;
	locations[n].models.always.locators = "Store06_locators";

	Locations[n].models.always.warehousewindows = "Store06_window";
	Locations[n].models.always.warehousewindows.tech = "LocationWindows";
	locations[n].models.always.warehousewindows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Store06_patch";
	//Night
	locations[n].models.night.charactersPatch = "Store06_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantoDomingo_bank";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ВЕРФЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_Shipyard";
	locations[n].id.label = "Shipyard";
	locations[n].filespath.models = "locations\inside\Shipyard03\";
	locations[n].image = "loading\inside\shipyard.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "SantoDomingo";
 	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.locators = "Shipyard03_locators";
	locations[n].models.always.shipyard = "Shipyard03";
	locations[n].models.always.shipyard.level = 65538;
	locations[n].models.always.window = "shipyard03_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Shipyard03_patch";
	//Night
	locations[n].models.night.charactersPatch = "Shipyard03_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "SantoDomingo_Packhouse";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Packhouse";
	locations[n].reload.l2.close_for_night = 1;
	locations[n].locators_radius.item.item1 = 1.0;
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пакгауз
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_Packhouse";
	locations[n].id.label = "Packhouse";
	locations[n].image = "loading\inside\sklad.tga";
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "SantoDomingo";
 	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Packhouse01";
	locations[n].models.always.locators = "angar_locators";
	locations[n].models.always.modelPackhouse = "angar";
	locations[n].models.always.modelPackhouse.level = 65538;
	//locations[n].models.always.window = "sklad_windows";
	//locations[n].models.always.window.tech = "LocationWindows";
	//locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "angar_patch";
	//Night
	locations[n].models.night.charactersPatch = "angar_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "SantoDomingo_Shipyard";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Shipyard";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "SantoDomingo_PackhouseOffice";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "PackhouseOffice";
	locations[n].reload.l2.close_for_night = 1;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Офис заведующиго пакгаузом
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_PackhouseOffice";
	locations[n].id.label = "PackhouseOffice";
	locations[n].image = "loading\inside\sklad.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\office02\";
	locations[n].models.always.housePortOffice = "office_small";
	locations[n].models.always.housePortOffice.level = 65538;
	locations[n].models.always.locators = "office_small_locators";
	//Day
	locations[n].models.day.charactersPatch = "office_small_patch";
	//Night
	locations[n].models.night.charactersPatch = "office_small_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "SantoDomingo_Packhouse";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Packhouse";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РЕЗИДЕНЦИЯ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_townhall";
	locations[n].id.label = "Townhall";
	locations[n].filespath.models = "locations\inside\Residence03";
	locations[n].image = "loading\inside\Residence03.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	// стража
	locations[n].soldiers = true;
	LAi_LocationFantomsGen(&locations[n], true);
	//Models
	//Always
	locations[n].models.always.locators = "Residence03_locators";
	locations[n].models.always.l1 = "Residence03";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.window = "residence03_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Residence03_patch";
	//Night
	locations[n].models.night.charactersPatch = "Residence03_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonResidence_2";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ЦЕРКОВЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_church";
	locations[n].id.label = "Church";
	locations[n].filespath.models = "locations\inside\Church01";
	locations[n].image = "loading\inside\church.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.locators = "Church01_locators";
	locations[n].models.always.tavern = "Church01";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Church01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Church01_patch";
	//Night
	locations[n].models.night.charactersPatch = "Church01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// БОРДЕЛЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_Brothel";
	locations[n].id.label = "Brothel";
	locations[n].filespath.models = "locations\inside\Brothel\";
	locations[n].image = "loading\inside\brothell_hall.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	locations[n].brothel = true;
	//Models
	//Always
	locations[n].models.always.locators = "Brothel_locators";
	locations[n].models.always.store = "Brothel";
	locations[n].models.always.window = "brothel_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Brothel_patch";
	//Night
	locations[n].models.night.charactersPatch = "Brothel_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "reload9";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "SantoDomingo_Brothel_room";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Brothel Room";
	locations[n].reload.l2.disable = 1;  //закроем, но связка пусть будет для квестов.

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "SantoDomingo_SecBrRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комнаты в борделе
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_Brothel_room";
	locations[n].id.label = "Brothel Room";
	locations[n].filespath.models = "locations\inside\Brothel_room\";
	locations[n].image = "loading\inside\brothell_room.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.locators = "Brothel_room_locators";
	locations[n].models.always.store = "Brothel_room";
	locations[n].models.always.window = "Brothel_room_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Brothel_room_patch";
	//Night
	locations[n].models.night.charactersPatch = "Brothel_room_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantoDomingo_brothel";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	locations[n].locators_radius.item.item1 = 1;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_SecBrRoom"; // вторая комната борделя
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\BigHouse03.tga";
 	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
 	locations[n].islandId = "Hispaniola";
	locations[n].brothel = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\BigHouse03\";
	locations[n].models.always.house = "BigHouse03";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "BigHouse03_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	
	locations[n].models.always.l1 = "BigHouse03_part";
	locations[n].models.always.l1.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "BigHouse03_patch";
	locations[n].models.day.locators = "BigHouse03_locators";
	//Night
	locations[n].models.night.charactersPatch = "BigHouse03_patch";
	locations[n].models.night.locators = "BigHouse03_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "SantoDomingo_Brothel";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "SantoDomingo_town";
	locations[n].reload.l2.emerge = "reload91";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	locations[n].reload.l2.disable = 1;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ПОРТОВЫЙ ОФИС / Адмиралтейство из КНС - правое крыло (NikK)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_PortOffice";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\inside\admiralteistvo.tga";

	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\AdmiraltyKNS2";
	locations[n].models.always.housePortOffice = "AdmiraltyKNS2";
	locations[n].models.always.housePortOffice.level = 65538;
	locations[n].models.always.locators = "AdmiraltyKNS2_locators";

	Locations[n].models.always.PortOffice = "AdmiraltyKNS2_windows";
	Locations[n].models.always.PortOffice.tech = "LocationWindows";
	locations[n].models.always.PortOffice.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "AdmiraltyKNS2_patch";
	//Night
	locations[n].models.night.charactersPatch = "AdmiraltyKNS2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "SantoDomingo_Admiralty";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "PortOffice";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Адмиралтейство из КНС - левое крыло (NikK)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_Admiralty";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\inside\admiralteistvo.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\AdmiraltyKNS1";
	locations[n].models.always.housePortOffice = "AdmiraltyKNS1";
	locations[n].models.always.housePortOffice.level = 65538;
	locations[n].models.always.locators = "AdmiraltyKNS1_locators";

	Locations[n].models.always.PortOffice = "AdmiraltyKNS1_windows";
	Locations[n].models.always.PortOffice.tech = "LocationWindows";
	locations[n].models.always.PortOffice.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "AdmiraltyKNS1_patch";
	//Night
	locations[n].models.night.charactersPatch = "AdmiraltyKNS1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "houseA_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "SantoDomingo_PortOffice";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "PortOffice";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Тюрьма
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "SantoDomingo_prison";
	locations[n].id.label = "Prison";
	Locations[n].image = "loading\inside\prison.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].parent_colony = "SantoDomingo";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Sound
	locations[n].type = "jail";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\prison1";
	locations[n].models.always.prison1 = "prison1";
	locations[n].models.always.lamps = "prison1_lamps";
	locations[n].models.always.locators = "prison1_locators";	
	locations[n].models.always.chest = "chest1";
	//Day
	locations[n].models.day.charactersPatch = "prison1_patch";
	//Night
	locations[n].models.night.charactersPatch = "prison1_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
    //Reload map
	Locations[n].reload.l1.name = "reload1";
	Locations[n].reload.l1.go = "SantoDomingo_town";
	Locations[n].reload.l1.emerge = "reload_jail";
	Locations[n].reload.l1.autoreload = "0";
	
	locations[n].locators_radius.box.box1 = 0.8;
	locations[n].box1.QuestClosed = true;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом с выходом на крышу
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_roof";
	locations[n].filespath.models = "locations\inside\FlamHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\flamhouse.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
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
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "houseK_2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload3";
	locations[n].reload.l2.go = "SantoDomingo_MH12";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";

	locations[n].reload.l3.name = "reload4";
	locations[n].reload.l3.go = "JinoRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";

	locations[n].reload.l4.name = "reload2"; //погребок-с.
	locations[n].reload.l4.go = "SantoDomingo_TownCave";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Dungeon";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом из трёх комнат (комната 3)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_MH12";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse12.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	locations[n].islandId = "Hispaniola";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
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
	locations[n].reload.l3.go = "SantoDomingo_roof";
	locations[n].reload.l3.emerge = "reload3";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Street";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "SantoDomingo_town";
	locations[n].reload.l4.emerge = "tavernWindow";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната из ККС
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "JinoRoom";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\flamhouse.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	locations[n].islandId = "Hispaniola";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
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
	locations[n].reload.l1.go = "SantoDomingo_roof";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом из трёх комнат (комнаты 1, 2)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_MH11";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse11.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	locations[n].islandId = "Hispaniola";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
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
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "houseK_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "SantoDomingo_town";
	locations[n].reload.l2.emerge = "houseF3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	n = n + 1;

	/////////////////////////////////////////////////////////////////////////////  Вход в подземелье Санто-доминго
	locations[n].id = "SantoDomingo_TownCave";
	locations[n].image = "loading\inside\dungeon.tga";
	locations[n].id.label = "Dungeon";
	//Sound
	locations[n].townsack = "SantoDomingo";
	locations[n].type = "Dungeon";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\DungeonDuffer1";
	locations[n].models.always.DungeonDuffer1 = "DungeonDuffer1";
	locations[n].models.always.DungeonDuffer1Stuff = "DungeonDuffer1_stuff";
	locations[n].models.always.locators = "DungeonDuffer1_locators";

	//Day
	locations[n].models.day.charactersPatch = "DungeonDuffer1_patch";
	//Night
	locations[n].models.night.charactersPatch = "DungeonDuffer1_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
 	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantoDomingo_roof";
	locations[n].reload.l1.emerge = "reload2";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "SantoDomingo_town";
	locations[n].reload.l2.emerge = "reloadT";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Каменный дом с 3 дверьми (NikK)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "BigHouseKNS_SD";
 	locations[n].id.label = "House";
	locations[n].image = "loading\inside\BigHouse06.tga";
 	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\BigHouse06\";
	locations[n].models.always.house = "BigHouse06";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "BigHouse06_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.locators = "BigHouse06_locators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "BigHouse06_patch";
	//Night
	locations[n].models.night.charactersPatch = "BigHouse06_patch";
	locations[n].models.night.locators = "BigHouse06_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "houseK_5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "SantoDomingo_town";
	locations[n].reload.l2.emerge = "houseK_6";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "SantoDomingo_town";
	locations[n].reload.l3.emerge = "houseK_4";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Маленький дом из ПКМ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Smallhome_K2";
	locations[n].filespath.models = "locations\inside\Smallhome";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\Smallhome.tga";
	locations[n].MustSetReloadBack = true;
 	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "SantoDomingo";
	locations[n].islandId = "Hispaniola";
	//Models
	//Always
	locations[n].models.always.locators = "SH_l";
	locations[n].models.always.tavern = "SH";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "SH_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "SH_p";
	//Night
	locations[n].models.night.charactersPatch = "SH_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "houseH3";
	locations[n].reload.l1.emerge = "SantoDomingo_town";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из города
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SantoDomingo_ExitTown";
	locations[n].fastreload = "SantoDomingo";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate.tga";

	//Town sack
	locations[n].townsack = "SantoDomingo";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	//Models
	//Always
	locations[n].filespath.models = "Locations\Outside\TownExitKSM";
	Locations[n].models.always.townExit = "DuelField";
	Locations[n].models.always.townWalls = "duelfield_gate";

	Locations[n].models.always.locators = "duelfield_locators";

	Locations[n].models.always.grassPatch = "duelfield_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

	Locations[n].models.always.l1 = "DuelField_plan";
	Locations[n].models.always.l1.level = 9;
	//Day
	locations[n].models.day.charactersPatch = "duelfield_patch";
	locations[n].models.day.fonars = "duelfield_fd";
	//Night
	locations[n].models.night.charactersPatch = "duelfield_patch";
	locations[n].models.night.fonars = "duelfield_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "SantoDomingo_town";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "SantoDomingo";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Hispaniola_Jungle_03";
	locations[n].reload.l2.emerge = "reload5";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.6;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Hispaniola_Jungle_03";
	locations[n].fastreload = "SantoDomingo";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\outside\jungle.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\TownExitT";
	Locations[n].models.always.townExit = "townExitT";

	Locations[n].models.always.locators = "townExitT_KNS_locators";

	Locations[n].models.always.grassPatch = "townExitT_grass";
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
	locations[n].models.always.l4 = "plan_KNS";
	//Day
	locations[n].models.day.charactersPatch = "townExitT_KNS_patch";
	locations[n].models.day.fonars = "townExitT_fd";
	//Night
	locations[n].models.night.charactersPatch = "townExitT_KNS_patch";
	locations[n].models.night.fonars = "townExitT_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload5_back";
	locations[n].reload.l1.go = "SantoDomingo_ExitTown";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "ExitTown";
	locations[n].locators_radius.reload.reload5_back = 3.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Hispaniola_Jungle_01";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "SantoDomingo_fort";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "SantoDomingo Fort";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Hispaniola_Jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle2";
	Locations[n].models.always.jungle = "jungle2";
	Locations[n].models.always.locators = "jungle2_locators";
	Locations[n].models.always.grassPatch = "jungle2_grass";
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
	locations[n].models.day.charactersPatch = "jungle2_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Hispaniola_Jungle_03";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Mayak8";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Mayak8";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Hispaniola_Jungle_02";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Маяк Санто-Доминго
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Mayak8";
	locations[n].id.label = "Mayak8";
	locations[n].worldmap = "Mayak8";
	locations[n].image = "loading\outside\lighthouse.tga";
	//Sound
	locations[n].type = "mayak";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Lighthouse";
	Locations[n].models.always.lighthouse = "lighthouse";
	locations[n].models.always.lighthouse.sea_reflection = 1;
	Locations[n].models.always.lighthouseSeabed = "lighthouse_sb";
	Locations[n].models.always.locators = "lighthouse_locators";
	
	Locations[n].models.always.dooropen = "lighthouse_dooropen";
	Locations[n].models.always.dooropen.tech = "DLightModel";	
	
	Locations[n].models.always.windows = "lighthouse_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 66530;
		
	Locations[n].models.always.grassPatch = "lighthouse_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	
	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "LocationModelBlend";
	Locations[n].models.always.l2 = "plan2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "LocationModelBlend";		
	//Day
	locations[n].models.day.winday = "lighthouse_winday";
	locations[n].models.day.fonar = "lighthouse_fd";
	locations[n].models.day.charactersPatch = "lighthouse_patch";
	Locations[n].models.day.jumpPatch = "lighthouse_jamp";
	
	locations[n].models.day.glassinday = "lighthouse_glassinday";
	Locations[n].models.day.glassinday.tech = "LocationWindows";
	locations[n].models.day.glassinday.level = 66531;
	
	locations[n].models.day.glassonday = "lighthouse_glassonday";
	Locations[n].models.day.glassonday.tech = "LocationWindows";
	locations[n].models.day.glassonday.level = 66532;	
	//Night
	locations[n].models.night.volumeLight= "lighthouse_volumeLight";
	locations[n].models.night.volumeLight.tech = "LighthouseLight";
	locations[n].models.night.volumeLight.level = 66529;	
	
	locations[n].models.night.fonar = "lighthouse_fn";
	locations[n].models.night.winnight = "lighthouse_winnight";
	locations[n].models.night.winnight.tech = "LighthouseLight";
	locations[n].models.night.winnight.level = 66529;
	locations[n].models.night.charactersPatch = "lighthouse_patch";	
	Locations[n].models.night.jumpPatch = "lighthouse_jamp";
	
	locations[n].models.night.glassinnight = "lighthouse_glassinnight";
	Locations[n].models.night.glassinnight.tech = "LocationWindows";
	locations[n].models.night.glassinnight.level = 66531;
	
	locations[n].models.night.glassonnight = "lighthouse_glassonnight";
	Locations[n].models.night.glassonnight.tech = "LocationWindows";
	locations[n].models.night.glassonnight.level = 66532;
	
	locations[n].models.night.fonaronnight = "lighthouse_fonaronnight";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Hispaniola_Jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 3.0;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Hispaniola1";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 12.0;
	locations[n].locators_radius.item.item1 = 0.8;
	
	locations[n].reload.l3.name = "reload2";
	locations[n].reload.l3.go = "Mayak8_Lighthouseroom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.label = "room";
	locations[n].locators_radius.reload.reload2 = 1.0;
	n = n + 1;
	
	////////////////////////////////////////////////////////////////////////////////
	//////////комната на маяке
	////////////////////////////////////////////////////////////////////////////////
	
	locations[n].id = "Mayak8_Lighthouseroom";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse05.tga";
	//Town sack
	locations[n].townsack = "SantoDomingo";
	locations[n].islandId = "Hispaniola1";
	//Sound
	locations[n].type = "house";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\mediumhouse05";
	locations[n].models.always.mediumhouse05 = "mediumhouse05";
	locations[n].models.always.mediumhouse05.level = 65538;
	locations[n].models.day.locators = "mediumhouse05_locators";
	locations[n].models.night.locators = "mediumhouse05_Nlocators";

	Locations[n].models.always.mediumhouse05windows = "mediumhouse05_windows";
	Locations[n].models.always.mediumhouse05windows.tech = "LocationWindows";
	locations[n].models.always.mediumhouse05windows.level = 65539;

	locations[n].models.always.back = "..\inside_back2";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.mediumhouse05rand= "mediumhouse05_rand";
	locations[n].models.day.charactersPatch = "mediumhouse05_patch";
	//Night
	locations[n].models.night.charactersPatch = "mediumhouse05_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Mayak8";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Mayak8";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Hispaniola_Jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle6";
	Locations[n].models.always.jungle = "jungle6";
	Locations[n].models.always.locators = "jungle6_lSD02";
	Locations[n].models.always.grassPatch = "jungle6_grass";
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

	locations[n].models.always.well_small = "well_small";
	Locations[n].models.always.well_small.locator.group = "reload";
	Locations[n].models.always.well_small.locator.name ="reloadW_back";
	Locations[n].models.always.well_small.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "jungle6_pSD02";
	//Night
	locations[n].models.night.charactersPatch = "jungle6_pSD02";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Hispaniola_Jungle_01";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore33";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore33";
    locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "LaVega_ExitTown";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;

	locations[n].reload.l4.name = "reloadW_back";
	locations[n].reload.l4.go = "Hispaniola_Cave";
	locations[n].reload.l4.emerge = "reload2";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Jungle";
	locations[n].locators_radius.reload.reloadW_back = 2.3;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// бухта Самана
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore33";
	locations[n].id.label = "Shore33";
	locations[n].image = "loading\outside\harbor.tga";
	locations[n].worldmap = "Shore33";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore10";
	Locations[n].models.always.shore10 = "shore10";
	locations[n].models.always.shore10.sea_reflection = 1;
	Locations[n].models.always.shore10seabed = "shore10_sb";
	Locations[n].models.always.locators = "shore10_locators";

	Locations[n].models.always.grassPatch = "shore10_grass";
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
	locations[n].models.day.charactersPatch = "shore10_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore10_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Hispaniola_Jungle_02";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Hispaniola1";
	locations[n].reload.l2.emerge = "reload_5";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из Ла Веги
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LaVega_ExitTown";
	locations[n].fastreload = "LaVega";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Town sack
	locations[n].townsack = "LaVega";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle5";
	Locations[n].models.always.jungle = "jungle5";
	Locations[n].models.always.locators = "jungle5_locators";
	Locations[n].models.always.grassPatch = "jungle5_grass";
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
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LaVega_town";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "LaVega_town";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Hispaniola_Jungle_02";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Hispaniola_Jungle_04";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2.0;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Hispaniola_Jungle_04";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	locations[n].Realm = "LaVega";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle7";
	Locations[n].models.always.jungle = "jungle7";
	Locations[n].models.always.locators = "jungle7_locators";
	Locations[n].models.always.grassPatch = "jungle7_grass";
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
	locations[n].models.day.charactersPatch = "jungle7_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle7_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore32";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore32";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "LaVega_ExitTown";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Hispaniola_Jungle_05";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// мыс Исабела
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore32";
	locations[n].id.label = "Shore32";
	locations[n].image = "loading\outside\harbor.tga";
	locations[n].worldmap = "Shore32";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	locations[n].Realm = "LaVega";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\ShoreIsabela";
	Locations[n].models.always.shore06 = "Isabela";
	locations[n].models.always.shore06.sea_reflection = 1;
	Locations[n].models.always.shore06seabed = "Isabela_sb";
	Locations[n].models.always.locators = "Isabela_locators";
	Locations[n].models.always.grassPatch = "Isabela_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

	Locations[n].models.always.l1 = "plan1";
	Locations[n].models.always.l1.level = 9;

	//River
	locations[n].models.always.Waterfall1 = "river1";
	locations[n].models.always.Waterfall1.uvslide.v0 = 0.03;
	locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall1.level = 70;
	
	locations[n].models.always.Waterfall2 = "river2";
	locations[n].models.always.Waterfall2.uvslide.v0 = 0.04;
	locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall2.level = 60;

	//Day
	locations[n].models.day.charactersPatch = "Isabela_patch";
	//Night
	locations[n].models.night.charactersPatch = "Isabela_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Hispaniola_Jungle_04";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Hispaniola1";
	locations[n].reload.l2.emerge = "reload_3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 9.0;

	locations[n].reload.l3.name = "reload2_back";
	locations[n].reload.l3.go = "Hispaniola_Grot";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;
	n = n + 1;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Hispaniola_Grot";
	locations[n].id.label = "Grot";
	locations[n].image = "loading\inside\Grotto.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\GrotI";
	locations[n].models.always.GrotI = "GrotI";
	locations[n].models.always.locators = "GrotI_locators";

	//Day
	locations[n].models.day.charactersPatch = "GrotI_patch";
	//Night
	locations[n].models.night.charactersPatch = "GrotI_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore32";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Hispaniola_Jungle_05";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	locations[n].Realm = "LaVega";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle3";
	Locations[n].models.always.jungle = "jungle3";
	Locations[n].models.always.locators = "jungle3_locators";
	Locations[n].models.always.grassPatch = "jungle3_grass";
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
	locations[n].models.day.charactersPatch = "jungle3_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle3_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Hispaniola_Jungle_04";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Hispaniola_Jungle_06";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Hispaniola_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в пещеру
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Hispaniola_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	locations[n].Realm = "LaVega";
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
	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "Hispaniola_Cave";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Hispaniola_Jungle_05";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пещера
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Hispaniola_Cave";
	locations[n].image = "loading\inside\cave.tga";
	locations[n].id.label = "Cave";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Hispaniola";
	locations[n].islandIdAreal = "Hispaniola1";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\cavernMedium1";
	locations[n].models.always.cavernMedium1 = "cavernMedium1";
	locations[n].models.always.cavernMedium1.sea_reflection = 1;
	locations[n].models.always.lamps = "cavernMedium1_lamps";
	locations[n].models.always.locators = "cavernMedium1_locators";

	// EvgAnat - "дикие Карибы", убираем дефолтные сферы
	locations[n].locators_radius.item.duhi1 = 0.0;

/*	Locations[n].models.always.rays = "cavernMedium1_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;	*/
	//Day
	locations[n].models.day.charactersPatch = "cavernMedium1_patch";
	Locations[n].models.day.jumpPatch = "CavernMedium1_jump";
	//Night
	locations[n].models.night.charactersPatch = "cavernMedium1_patch";
	Locations[n].models.night.jumpPatch = "CavernMedium1_jump";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "true";
	locations[n].environment.weather.rain = false;
 	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Hispaniola_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.label = "Jungle";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Hispaniola_Jungle_02";
	locations[n].reload.l2.emerge = "reloadW";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2 = 2;
	locations[n].locators_radius.item.CheckReload1 = 3.5;
	n = n + 1;

	return n;
}

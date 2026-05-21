int LocationInitJamaica(int n)
{
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОРОД
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_town";
	locations[n].id.label = "Street";
	locations[n].worldmap = "PortRoyal";
	
	locations[n].townsack = "PortRoyal";
	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
	
	locations[n].image = "loading\Town.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	//==> флаг генерации квестодателя по розыску кэпов, int значение - шанс что сам заговорит(1-10)
	locations[n].questSeekCap = 8;
	//Sound
	locations[n].type = "town";
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	locations[n].filespath.models = "locations\Town_PortRoyalN\Town\";
	//Always
	locations[n].models.always.town = "PortRoyal";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.L1 = "PortRoyal_signsA";
	locations[n].models.always.seabed = "PortRoyal_sb";
	locations[n].models.always.locators = "PortRoyal_locators";
	locations[n].models.always.grassPatch = "PortRoyal_grass";
	
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.level = 9;

	//River
	locations[n].models.always.Waterfall1 = "river1";
	locations[n].models.always.Waterfall1.uvslide.v0 = 0.2;
    locations[n].models.always.Waterfall1.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall1.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall1.level = 50;
	
	locations[n].models.always.Waterfall2 = "river2";
	locations[n].models.always.Waterfall2.uvslide.v0 = 0.3;
    locations[n].models.always.Waterfall2.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall2.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall2.level = 49;

	//WindMill Fan
	locations[n].models.always.MillFan = "MillFan";
	Locations[n].models.always.MillFan.locator.group = "WindMill";
	Locations[n].models.always.MillFan.locator.name ="Fan";	
	Locations[n].models.always.MillFan.rotate.x = 0.0;
	Locations[n].models.always.MillFan.rotate.y = 0.0;
	Locations[n].models.always.MillFan.rotate.z = 0.3;

	//Day
	locations[n].models.day.fonar = "PortRoyal_fd";
	locations[n].models.day.charactersPatch = "PortRoyal_patch_day";
	locations[n].models.day.rinok = "PortRoyal_rinok";
	Locations[n].models.day.jumpPatch = "PortRoyal_jump_patch";
	//Night
	locations[n].models.night.fonar = "PortRoyal_fn";
	locations[n].models.night.charactersPatch = "PortRoyal_patch_night";
	Locations[n].models.night.jumpPatch = "PortRoyal_jump_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map

    // --> Типовые городские локации, четкая фиксация на 10 номеров.
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Jamaica";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 4.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Jamaica";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "PortRoyal_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "PortRoyal_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "PortRoyal_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "PortRoyal_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "reload7_back";
	locations[n].reload.l7.go = "PortRoyal_church";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Church";
	//locations[n].reload.l7.close_for_night = 1;

	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "PortRoyal_Bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;

	locations[n].reload.l9.name = "reload9_back";
	locations[n].reload.l9.go = "PortRoyal_brothel";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Brothel";

 	locations[n].reload.l91.name = "reload91";
	locations[n].reload.l91.go = "PortRoyal_SecBrRoom";
	locations[n].reload.l91.emerge = "reload2";
	locations[n].reload.l91.autoreload = "0";
	locations[n].reload.l91.label = "Brothel";

	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "PortRoyal_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";
	locations[n].reload.l10.close_for_night = 1;

	locations[n].reload.gate.name = "gate_back";
	locations[n].reload.gate.go = "PortRoyal_ExitTown";
	locations[n].reload.gate.emerge = "reload4";
	locations[n].reload.gate.autoreload = "0";
	locations[n].reload.gate.label = "ExitTown";
	
	locations[n].reload.jail.name = "reload_jail";
	locations[n].reload.jail.go = "PortRoyal_prison";
	locations[n].reload.jail.emerge = "reload1";
	locations[n].reload.jail.autoreload = "0";
	locations[n].reload.jail.label = "Prison";
	
	// --> Квестовые локации, 9 номеров.
	locations[n].reload.l11.name = "houseS1";
	locations[n].reload.l11.go = "PortRoyal_houseS1";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l11.autoreload = "0";
	locations[n].reload.l11.label = "Morgan's House";

	locations[n].reload.l12.name = "houseBH1";
	locations[n].reload.l12.go = "PortRoyal_houseBH1";
	locations[n].reload.l12.emerge = "reload2";
	locations[n].reload.l12.autoreload = "0";
	locations[n].reload.l12.label = "House";

	locations[n].reload.l13.name = "houseBH2";
	locations[n].reload.l13.go = "PortRoyal_houseBH1";
	locations[n].reload.l13.emerge = "reload1";
	locations[n].reload.l13.autoreload = "0";
	locations[n].reload.l13.label = "House";

	locations[n].reload.l14.name = "houseH2";
	locations[n].reload.l14.go = "PortRoyal_MH9_2";
	locations[n].reload.l14.emerge = "reload1";
	locations[n].reload.l14.autoreload = "0";
	locations[n].reload.l14.label = "House";

	locations[n].reload.l15.name = "houseK3";
	locations[n].reload.l15.go = "PortRoyal_BigHouse6";
	locations[n].reload.l15.emerge = "reload1";
	locations[n].reload.l15.autoreload = "0";
	locations[n].reload.l15.label = "House";

	locations[n].reload.l16.name = "houseK2";
	locations[n].reload.l16.go = "PortRoyal_BigHouse6";
	locations[n].reload.l16.emerge = "reload2";
	locations[n].reload.l16.autoreload = "0";
	locations[n].reload.l16.label = "House";
	locations[n].reload.l16.disable = 1; //закроем

	locations[n].reload.l17.name = "houseSk5";
	locations[n].reload.l17.go = "PortRoyal_sklad02";
	locations[n].reload.l17.emerge = "reload1";
	locations[n].reload.l17.autoreload = "0";
	locations[n].reload.l17.label = "Sklad";
	locations[n].reload.l17.close_for_night = 1;

	locations[n].reload.l18.name = "houseSk4";
	locations[n].reload.l18.go = "PortRoyal_sklad02";
	locations[n].reload.l18.emerge = "reload1";
	locations[n].reload.l18.autoreload = "0";
	locations[n].reload.l18.label = "Sklad";
	locations[n].reload.l18.disable = 1; //закроем

	locations[n].reload.l19.name = "houseSk3";
	locations[n].reload.l19.go = "PortRoyal_sklad02";
	locations[n].reload.l19.emerge = "reload1";
	locations[n].reload.l19.autoreload = "0";
	locations[n].reload.l19.label = "Sklad";
	locations[n].reload.l19.disable = 1; //закроем	

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

	locations[n].reload.l22.name = "houseSp3";
	locations[n].reload.l22.go = "CommonDoubleflourHouse_2";
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";

	locations[n].reload.l23.name = "houseSp4";
	locations[n].reload.l23.go = "BuilderHouse";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "BuilderHouse";
	locations[n].reload.l23.disable = true;
	
	locations[n].reload.l24.name = "houseF1";
	locations[n].reload.l24.go = "CommonRoom_MH";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "House";

	locations[n].reload.l25.name = "houseK1";
	locations[n].reload.l25.go = "CommonCobHouse";
	locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "House";

	locations[n].reload.l26.name = "houseH1";
	locations[n].reload.l26.go = "CommonRoom_MH3";
	locations[n].reload.l26.emerge = "reload1";
	locations[n].reload.l26.autoreload = "0";
	locations[n].reload.l26.label = "House";

	locations[n].reload.l27.name = "houseSk2";
	locations[n].reload.l27.go = "PortRoyal_sklad03";
	locations[n].reload.l27.emerge = "reload1";
	locations[n].reload.l27.autoreload = "0";
	locations[n].reload.l27.label = "Sklad";
	locations[n].reload.l27.close_for_night = 1;

	locations[n].reload.l28.name = "boat";
	locations[n].reload.l28.go = "Jamaica";
	locations[n].reload.l28.emerge = "reload_1";
	locations[n].reload.l28.autoreload = "0";
	locations[n].reload.l28.label = "Sea";
	locations[n].locators_radius.reload.boat = 3.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ТАВЕРНА
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_tavern";
	locations[n].id.label = "Tavern";
	locations[n].image = "loading\inside\Tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\Tavern07\";
	//Always
	locations[n].models.always.tavern = "Tavern07";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "Tavern07_locators";
	locations[n].models.always.window = "Tavern07_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Tavern07_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern07_patch";
	//Environment
	locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "PortRoyal_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// КОМНАТА В ТАВЕРНЕ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_tavern_upstairs";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
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
	locations[n].reload.l1.go = "PortRoyal_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// МАГАЗИН
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_store";
	locations[n].id.label = "Store";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\store02\";
	//Always
	locations[n].models.always.locators = "Store02_locators";
	locations[n].models.always.store = "Store02";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Store02_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Store02_patch";
	//Night
	locations[n].models.night.charactersPatch = "Store02_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.camdetector.camera1 = 5;
    ////////////////////////==> комната в магазине
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonPackhouse_1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РОСТОВЩИК
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_Bank";
	locations[n].id.label = "Usurer House";
	locations[n].image = "loading\inside\bank.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\Bank02\";
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
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "reload8";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "PortRoyal_bankvault";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Хранилище (Банк)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_bankvault";
	locations[n].id.label = "bankvault";
	locations[n].image = "loading\inside\vault.tga";
	//locations[n].MustSetReloadBack = true;
	//locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
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
	locations[n].reload.l1.go = "PortRoyal_bank";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ВЕРФЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_Shipyard";
	locations[n].id.label = "Shipyard";
	locations[n].image = "loading\inside\shipyard.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\Shipyard03\";
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
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "PortRoyal_Packhouse";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Packhouse";
	locations[n].reload.l2.close_for_night = 1;
	locations[n].locators_radius.item.item1 = 1.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пакгауз
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_Packhouse";
	locations[n].id.label = "Packhouse";
	locations[n].image = "loading\inside\sklad.tga";
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
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
	locations[n].reload.l1.go = "PortRoyal_Shipyard";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Shipyard";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "PortRoyal_PackhouseOffice";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "PackhouseOffice";
	locations[n].reload.l2.close_for_night = 1;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Офис заведующиго пакгаузом
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_PackhouseOffice";
	locations[n].id.label = "PackhouseOffice";
	locations[n].image = "loading\inside\sklad.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
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
	locations[n].reload.l1.go = "PortRoyal_Packhouse";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Packhouse";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РЕЗИДЕНЦИЯ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_townhall";
	locations[n].id.label = "Townhall";
	locations[n].image = "loading\inside\Residence03.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
 	// Guards
	locations[n].soldiers = true;
	LAi_LocationFantomsGen(&locations[n], true);
	//Models
	locations[n].filespath.models = "locations\inside\Residence03";
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
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "PortRoyal_RoomTownhall";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_RoomTownhall"; // комната в резиденции c переходом в спальню
	locations[n].id.label = "TownhallRoom";
	locations[n].image = "loading\inside\BigHouse02.tga";
 	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\BigHouse02\";
	locations[n].models.always.models = "BigHouse02";
	locations[n].models.always.models.level = 65538;
	locations[n].models.always.boxes = "BigHouse02_boxes";
	locations[n].models.always.boxes.level = 65539;
	locations[n].models.always.window = "BigHouse02_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65540;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "BigHouse02_patch";
	locations[n].models.day.locators = "BigHouse02_locators";
	//Night
	locations[n].models.night.charactersPatch = "BigHouse02_patch";
	locations[n].models.night.locators = "BigHouse02_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PortRoyal_townhall";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Room";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonBedroom";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Bedroom";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ЦЕРКОВЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_church";
	locations[n].id.label = "Church";
	locations[n].image = "loading\inside\church.tga";
    //Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\Church01";
	//Always
	locations[n].filespath.models = "locations\inside\churchInside2";
	locations[n].models.always.churchInside2 = "churchInside2";
	locations[n].models.always.churchInside2.level = 65538;
	locations[n].models.always.locators = "churchInside2_locators";
	
	locations[n].models.always.backgroundInsides = "backgroundInsides";
	locations[n].models.always.backgroundInsides.level = 65529;
	
	Locations[n].models.always.churchInside2windows = "churchInside2_windows";
	Locations[n].models.always.churchInside2windows.tech = "LocationWindows";
	locations[n].models.always.churchInside2windows.level = 65539;
	
	Locations[n].models.always.churchInside2alpha = "churchInside2_alpha";
	Locations[n].models.always.churchInside2alpha.tech = "LocationWindows";
	locations[n].models.always.churchInside2alpha.level = 65540;
	
	Locations[n].models.always.churchInside2gold = "churchInside2_gold";
	Locations[n].models.always.churchInside2gold.reflection = 0.6;
	Locations[n].models.always.churchInside2gold.tech = "EnvironmentShader";
	locations[n].models.always.churchInside2gold.level = 65541;
	//Day
	locations[n].models.day.charactersPatch = "churchInside2_patch";
	//Night
	locations[n].models.night.charactersPatch = "churchInside2_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// БОРДЕЛЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_Brothel";
	locations[n].id.label = "Brothel";
	locations[n].image = "loading\inside\brothell_hall.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
	locations[n].brothel = true;
	//Models
	locations[n].filespath.models = "locations\inside\Brothel\";
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
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "reload9";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "PortRoyal_Brothel_room";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Brothel Room";
	locations[n].reload.l2.disable = 1;  //закроем, но связка пусть будет для квестов.

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "PortRoyal_SecBrRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комнаты в борделе
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_Brothel_room";
	locations[n].id.label = "Brothel Room";
	locations[n].image = "loading\inside\brothell_room.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\Brothel_room\";
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
	locations[n].reload.l1.go = "PortRoyal_brothel";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	locations[n].locators_radius.item.item1 = 1;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_SecBrRoom"; // вторая комната борделя
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\BigHouse03.tga";
 	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
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
	locations[n].reload.l1.go = "PortRoyal_Brothel";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "PortRoyal_town";
	locations[n].reload.l2.emerge = "reload91";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ПОРТОВЫЙ ОФИС
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_PortOffice";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\inside\portoffice.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\PortOffice4";
	locations[n].models.always.housePortOffice = "PortOffice";
	locations[n].models.always.housePortOffice.level = 65538;
	locations[n].models.always.locators = "PortOffice_locators";

	Locations[n].models.always.PortOffice = "PortOffice_windows";
	Locations[n].models.always.PortOffice.tech = "LocationWindows";
	locations[n].models.always.PortOffice.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "PortOffice_patch";
	//Night
	locations[n].models.night.charactersPatch = "PortOffice_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	////////////////////// prison ////////////////////////////
	Locations[n].id = "PortRoyal_prison";
	locations[n].id.label = "Prison";
	Locations[n].image = "loading\inside\prison.tga";
	locations[n].townsack = "PortRoyal";
    locations[n].parent_colony = "PortRoyal";
 	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
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
	Locations[n].reload.l1.go = "PortRoyal_town";
	Locations[n].reload.l1.emerge = "reload_jail";
	Locations[n].reload.l1.autoreload = "0";
	
	locations[n].locators_radius.box.box1 = 0.8;

	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом Моргана
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_houseS1"; // c переходом в малую резиденцию
	locations[n].id.label = "Morgan's House";
	locations[n].image = "loading\inside\BigHouse02.tga";
 	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\BigHouse02\";
	locations[n].models.always.models = "BigHouse02";
	locations[n].models.always.models.level = 65538;
	locations[n].models.always.boxes = "BigHouse02_boxes";
	locations[n].models.always.boxes.level = 65539;
	locations[n].models.always.window = "BigHouse02_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65540;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "BigHouse02_patch";
	locations[n].models.day.locators = "BigHouse02_PrLocators";
	//Night
	locations[n].models.night.charactersPatch = "BigHouse02_patch";
	locations[n].models.night.locators = "BigHouse02_PrNlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "houseS1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonBedroom";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";

	locations[n].private1.key = "keyMorgan";
	locations[n].private1.key.delItem = true;
	locations[n].private1.money = 5000;
	locations[n].private1.items.blade27 = 1; // Рапира Моргана
	locations[n].private1.items.cirass5 = 1; // Дорогая кираса
	locations[n].private1.items.suit_3 = 1; // Одежда дворнина
	
	locations[n].private2.key = "keyMorgan";
	locations[n].private2.key.delItem = true;
	locations[n].private2.money = 10000;
	locations[n].private2.items.maquahuitl = 1; // Макуауитль
	locations[n].private2.items.cirass3 = 1; // Испанская кираса
	locations[n].private2.items.suit_1 = 1; // Обноски

	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Большой дом с двумя входами
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_houseBH1";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\flamhouse.tga";
	locations[n].MustSetReloadBack = true;
 	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\FlamHouse";
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
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "houseBH2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "house";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "PortRoyal_town";
	locations[n].reload.l2.emerge = "houseBH1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "house";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "PortRoyal_MH12";
	locations[n].reload.l3.emerge = "reload3";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "PortRoyal_JinoRoom";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Room";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом из трёх комнат (комната 3)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_MH12";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse12.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\mediumhouse11_12";
	//Always
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
	locations[n].reload.l1.name = "reload3";
	locations[n].reload.l1.go = "PortRoyal_houseBH1";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната из ККС
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_JinoRoom";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\flamhouse.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\JinoRoom";
	//Always
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
	locations[n].reload.l1.go = "PortRoyal_houseBH1";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Средний дом 8 (9 с заменённой стенкой)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_MH9_2";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse08.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\mediumhouse08";
	//Always
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
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "houseH2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Дом с 3 дверьми
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_BigHouse6";
 	locations[n].id.label = "House";
	locations[n].image = "loading\inside\BigHouse06.tga";
 	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "PortRoyal";
 	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\BigHouse06\";
	//Always
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
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "houseK3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "PortRoyal_BigHouse6";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	locations[n].reload.l2.disable = 1; //закроем
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Склад 02
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_sklad02";
	locations[n].id.label = "packhouse";
	locations[n].image = "loading\inside\sklad.tga";
	locations[n].MustSetReloadBack = true;
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "sklad";
	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\Sklad02";
	//Always
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
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "ShouseSk5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Склад 03
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_sklad03";
	locations[n].id.label = "packhouse";
	locations[n].image = "loading\inside\sklad.tga";
	locations[n].MustSetReloadBack = true;
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "sklad";
	locations[n].fastreload = "PortRoyal";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\Sklad03";
	//Always
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
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "ShouseSk2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из города
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\Outside\JunglesN\TownExitW";
	//Always
	Locations[n].models.always.townExit = "townExitW";
	Locations[n].models.always.l1 = "townExitW_BSP";
	Locations[n].models.always.townWalls = "ExitJamaica2";
	Locations[n].models.always.locators = "townExitW_locators";
	Locations[n].models.always.grassPatch = "townExitW_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l2 = "plan1";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "ExitJamaica1";
	//Day
	locations[n].models.day.charactersPatch = "townExitW_patch";
	locations[n].models.day.fonars = "townExitW_fd";
	//Night
	locations[n].models.night.charactersPatch = "townExitW_patch";
	locations[n].models.night.fonars = "townExitW_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

	//Reload map
	locations[n].reload.l1.name = "reload4";
	locations[n].reload.l1.go = "PortRoyal_town";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "PortRoyal";
	locations[n].locators_radius.reload.reload3_back = 2.0;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "PortRoyal_fort";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "PortRoyal Fort";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l3.name = "reload2_back";
	locations[n].reload.l3.go = "Jamaica_jungle_01";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l4.name = "reload3_back";
	locations[n].reload.l4.go = "PortRoyal_Graveyard";
	locations[n].reload.l4.emerge = "reload2";
	locations[n].reload.l4.autoreload = "1";
	locations[n].reload.l4.label = "Graveyard";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// городское кладбище
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_Graveyard";
	locations[n].id.label = "Graveyard";
	locations[n].image = "loading\Outside\Cemetery.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Jamaica";
	locations[n].DisableEncounters = true;
	//Models
	locations[n].filespath.models = "locations\Outside\JunglesN\Graveyard";
	//Always
	Locations[n].models.always.Graveyard = "Churchyard";		
	Locations[n].models.always.grassPatch = "Churchyard_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "Churchyard_BSP";
	Locations[n].models.always.l2 = "Churchyard_plan1";
	//Day
	locations[n].models.day.charactersPatch = "Churchyard_patch";
	Locations[n].models.day.locators = "Churchyard_ld";	
	//Night
	locations[n].models.night.charactersPatch = "Churchyard_patch";	
	Locations[n].models.night.locators = "Churchyard_ln";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Mayak3";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Mayak3";
	locations[n].locators_radius.reload.reload1_back = 5.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "PortRoyal_ExitTown";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "ExitTown";
	locations[n].locators_radius.reload.reload2_back = 3.0;

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "PortRoyal_KeepersHouse";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "House";
	
	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "PortRoyal_CryptBig1";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Crypt";

	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "PortRoyal_Crypt";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Crypt";

	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "PortRoyal_Chapel";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Chapel";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////
	// домик смотрителя
	/////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_KeepersHouse";
	locations[n].id.label = "KeepersHouse";
	locations[n].image = "loading\inside\SmallHouse_inside.tga";
	locations[n].KeepersHouse = true;
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Jamaica";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\SmallHouse_inside\";
	locations[n].models.always.SmallHouse = "SmallHouse_inside";
	//locations[n].models.always.SmallHouse.level = 65538;
	Locations[n].models.always.windows = "SmallHouse_inside_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back2";
	//Day
	locations[n].models.day.charactersPatch = "SmallHouse_inside_patch";
	locations[n].models.day.locators = "SmallHouse_inside_ld";
	//Night
	locations[n].models.night.charactersPatch = "SmallHouse_inside_patch";
	locations[n].models.night.locators = "SmallHouse_inside_ln";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PortRoyal_Graveyard";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Graveyard";
	n = n + 1;

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// часовня
	/////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_Chapel";
	locations[n].id.label = "Chapel";
	locations[n].image = "loading\inside\IM_church.tga";
	// locations[n].Chapel = true;
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\church_IM\";
	//Always
	locations[n].models.always.church = "church_IM";
	locations[n].models.always.locators = "church_IM_locators";
	locations[n].models.always.window = "church_IM_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "church_IM_patch";
	//Night
	locations[n].models.night.charactersPatch = "church_IM_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PortRoyal_Graveyard";
	locations[n].reload.l1.emerge = "reload6";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Graveyard";

	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	/////////////////////////////////////////////////////////////////////////////////////////////
	// крипта большая - 1
	/////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_CryptBig1";
	locations[n].id.label = "Crypt";
	locations[n].image = "loading\Crypt.tga";
	locations[n].CryptBig1 = true;
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "dungeon";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\crypt_2_1_inside\";
	//Always
	locations[n].models.always.cryptbig = "crypt_2_1_inside";
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "crypt_2_1_inside_patch";
	locations[n].models.day.locators = "crypt_2_1_inside_ld";
	//Night
	locations[n].models.night.charactersPatch = "crypt_2_1_inside_patch";
	locations[n].models.night.locators = "crypt_2_1_inside_ln";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PortRoyal_Graveyard";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Graveyard";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "PortRoyal_CryptBig2";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Crypt";
	n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////
	// крипта большая - 2
	/////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_CryptBig2";
	locations[n].id.label = "Crypt";
	locations[n].image = "loading\Crypt.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "dungeon";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\crypt_2_2_inside\";
	//Always
	locations[n].models.always.cryptbig = "crypt_2_2_inside";
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.locators = "crypt_2_2_inside_locators";
	//Day
	locations[n].models.day.charactersPatch = "crypt_2_2_inside_patch";
	//Night
	locations[n].models.night.charactersPatch = "crypt_2_2_inside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PortRoyal_CryptBig1";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Crypt";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "PortRoyal_CryptDungeon";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Crypt dungeon";
	locations[n].reload.l2.disable = true; // закрыто до поры
	CryptBoxRadius(n, "big");
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	// логово
	/////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_CryptDungeon";
	locations[n].id.label = "Crypt dungeon";
	locations[n].image = "loading\inside\dungeon.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "dungeon";
	locations[n].islandId = "Jamaica";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Animists_cave\";
	locations[n].models.always.CryptDungeon = "Animists_cave";
	locations[n].models.always.locators = "Animists_cave_locators";
	//Day
	locations[n].models.day.charactersPatch = "Animists_cave_patch";
	//Night
	locations[n].models.night.charactersPatch = "Animists_cave_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "PortRoyal_CryptBig2";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Crypt";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////
	// крипта малая
	/////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "PortRoyal_Crypt";
	locations[n].id.label = "Crypt";
	locations[n].image = "loading\Crypt.tga";
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "dungeon";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\crypt_inside\";
	//Always
	locations[n].models.always.crypt = "crypt_inside";
	locations[n].models.always.locators = "crypt_inside_locators";

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "crypt_inside_patch";
	//Night
	locations[n].models.night.charactersPatch = "crypt_inside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "PortRoyal_Graveyard";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Graveyard";
	CryptBoxRadius(n, "small");
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Маяк Ямайки
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Mayak3";
	locations[n].id.label = "Mayak3";
	locations[n].worldmap = "Mayak3";
	locations[n].image = "loading\outside\lighthouse.tga";
	//Sound
	locations[n].type = "mayak";
	locations[n].islandId = "Jamaica";	
	locations[n].soldiers = true;
	//Models
	locations[n].filespath.models = "locations\Outside\JunglesN\LighthouseJamaica";
	//Always
	Locations[n].models.always.lighthouseJamaica = "lighthouseJamaica";
	//Locations[n].models.always.lighthouseJamaica.sea_reflection = 1;

	Locations[n].models.always.lighthouseJamaicaSeabed = "lighthouseJamaica_sb";
	Locations[n].models.always.locators = "lighthouseJamaica_locators";

	Locations[n].models.always.windows = "lighthouseInside_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	Locations[n].models.always.windows.level = 66530;

	Locations[n].models.always.grassPatch = "lighthouseJamaica_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga";

	Locations[n].models.always.l1 = "lighthouseJamaica_bsp";
	Locations[n].models.always.l2 = "plan1";

	//Day
	locations[n].models.day.fonar = "lighthouseJamaica_fd";
	locations[n].models.day.charactersPatch = "lighthouseJamaica_patch";
	Locations[n].models.day.jumpPatch = "lighthouseJamaica_jamp";

	locations[n].models.day.winday = "lighthouseJamaica_winday";
	locations[n].models.day.winday.tech = "LocationWindows";
	locations[n].models.day.winday.level = 66530;

	Locations[n].models.day.glassonday.tech = "LocationWindows";
	locations[n].models.day.glassonday.level = 66530;

	//Night
	locations[n].models.night.volumeLight = "lighthouseJamaica_volumeLight";
	locations[n].models.night.volumeLight.tech = "LighthouseLight";
	locations[n].models.night.volumeLight.level = 66529;

	locations[n].models.night.fonar = "lighthouseJamaica_fn";
	locations[n].models.night.charactersPatch = "lighthouseJamaica_patch";
	Locations[n].models.night.jumpPatch = "lighthouseJamaica_jamp";

	locations[n].models.night.winnight = "lighthouseJamaica_winnight";
	locations[n].models.night.winnight.tech = "LocationWindows";
	locations[n].models.night.winnight.level = 66530;

	locations[n].models.night.fonaronnight = "lighthouseInside_fonaronnight";

	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "PortRoyal_Graveyard";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Graveyard";
	locations[n].locators_radius.reload.reload1_back = 3.0;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Jamaica";
	locations[n].reload.l2.emerge = "reload_4";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 12.0;

	locations[n].reload.l3.name = "reload2";
	locations[n].reload.l3.go = "Jamaica_Hut1";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Hut";

	locations[n].locators_radius.item.detector1 = 2.6;
	locations[n].locators_radius.item.detector2 = 2.6;
	locations[n].locators_radius.item.detector3 = 2.6;
	locations[n].locators_radius.item.detector4 = 2.6;
	locations[n].locators_radius.item.detector5 = 2.6;
	locations[n].locators_radius.item.detector6 = 2.6;
	locations[n].DisableEncounters = true;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Хижина на маяке
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Jamaica_Hut1";
	locations[n].id.label = "Hut";
	locations[n].image = "loading\inside\hibara.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "PortRoyal";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	//Models
	locations[n].filespath.models = "locations\inside\Hut1_KNS";
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
	locations[n].reload.l1.name = "reload2";
	locations[n].reload.l1.go = "Mayak3";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Mayak3";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Jamaica_jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Jamaica";
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
	//Day
	locations[n].models.day.charactersPatch = "jungle3_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle3_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "PortRoyal_ExitTown";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "ExitTown";
	locations[n].locators_radius.reload.reload2_back = 3.0;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "Jamaica_jungle_02";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 4.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Jamaica_CaveEntrance";
	locations[n].reload.l3.emerge = "reload2";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 6.6;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Вход в пещеру
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Jamaica_CaveEntrance";
	locations[n].id.label = "Cave entrance";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\Outside\JunglesN\CaveEnt1";
	//Always
	Locations[n].models.always.caveEnt1 = "caveEnt1";
	Locations[n].models.always.l1 = "caveEnt1_bsp";
	Locations[n].models.always.locators = "caveEnt1_locators";
	Locations[n].models.always.grassPatch = "caveEnt1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
	Locations[n].models.always.l2 = "plan1";
	Locations[n].models.always.l2.level = 9;
	Locations[n].models.always.l2.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "caveEnt1_patch";
	//Night
	locations[n].models.night.charactersPatch = "caveEnt1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l3.name = "reload1_back";
	locations[n].reload.l3.go = "Jamaica_Grot";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Cave";
	locations[n].locators_radius.reload.reload1_back = 1.3;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Jamaica_jungle_01";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Грот
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Jamaica_Grot";
	locations[n].id.label = "Grot";
    locations[n].image = "loading\inside\cave.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Jamaica";
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
	locations[n].reload.l1.go = "Jamaica_CaveEntrance";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Cave entrance";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Jamaica_jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Jamaica";
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
	locations[n].reload.l1.name = "reload3_back";
	locations[n].reload.l1.go = "Shore36";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore36";
	locations[n].locators_radius.reload.reload3_back = 4;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "Jamaica_Jungle_03";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 4;

	locations[n].reload.l3.name = "reload2_back";
	locations[n].reload.l3.go = "Jamaica_Jungle_01";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 6;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// бухта Портленд
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore36";
	locations[n].id.label = "Shore36";
	locations[n].image = "loading\outside\harbor.tga";
	locations[n].worldmap = "Shore36";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\Outside\Shores\Shore08";
	//Always
	Locations[n].models.always.shore08 = "shore08";
	Locations[n].models.always.shore08.sea_reflection = 1;
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
	locations[n].reload.l1.go = "Jamaica_jungle_02";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Jamaica";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Jamaica_Jungle_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
 	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\Outside\JunglesN\Jungle5";
	//Always
	Locations[n].models.always.jungle = "jungle5";
	Locations[n].models.always.l1 = "jungle5_BSP";	
	Locations[n].models.always.locators = "jungle5_locators";		
	Locations[n].models.always.grassPatch = "jungle5_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l2 = "plan1";
	Locations[n].models.always.l2.level = 9;
	Locations[n].models.always.l2.tech = "DLightModel";
	//Day
	locations[n].models.day.charactersPatch = "jungle5_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle5_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "FortOrange_ExitTown";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 3.0;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "Jamaica_jungle_02";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 3.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// мыс Негрил
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore35";
	locations[n].id.label = "Shore35";
	locations[n].image = "loading\outside\harbor.tga";
	locations[n].worldmap = "Shore35";
	//Town sack
	locations[n].townsack = "FortOrange";
	//Sound
	locations[n].type = "seashore";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore11";
	Locations[n].models.always.shore11 = "shore11";
	locations[n].models.always.shore11.sea_reflection = 1;
	Locations[n].models.always.shore11seabed = "shore11_sb";
	Locations[n].models.always.locators = "shore11_locators";

	Locations[n].models.always.grassPatch = "shore11_grass";
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
    locations[n].models.always.L4 = "shore11_pier";
    locations[n].models.always.L4.tech = "DLightModel";

	//Day
	locations[n].models.day.charactersPatch = "shore11_patch";
	locations[n].models.day.fonars = "shore11_fd";
	Locations[n].models.day.fonars.tech = "DLightModel";
	//Night
	locations[n].models.night.charactersPatch = "shore11_patch";
	locations[n].models.night.fonars = "shore11_fn";
	Locations[n].models.night.fonars.tech = "DLightModel";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "FortOrange_ExitTown";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Jamaica";
	locations[n].reload.l2.emerge = "reload_3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 10.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// выход из форт Оранж
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "FortOrange_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate.tga";
	//Town sack
	locations[n].townsack = "FortOrange";
	//Sound
	locations[n].type = "jungle";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
	//Models
	Locations[n].filespath.models = "locations\Town_FortOrange\Exit";
	//Always
	Locations[n].models.always.townExit = "FortOrangeExit";
	Locations[n].models.always.townExit.tech = "DLightModel";
	Locations[n].models.always.locators = "FortOrangeexit_l";		
	Locations[n].models.always.grassPatch = "FortOrangeexit_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan_1";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	Locations[n].models.always.l2 = "plan_2";
	Locations[n].models.always.l2.level = 8;
	Locations[n].models.always.l2.tech = "DLightModel";
	Locations[n].models.always.l3 = "plan_3";
	Locations[n].models.always.l3.level = 7;
	Locations[n].models.always.l3.tech = "DLightModel";	
	//Day
	locations[n].models.day.charactersPatch = "FortOrangeexit_p";
	locations[n].models.day.fonars = "FortOrangeexit_fd";
	//Night
	locations[n].models.night.charactersPatch = "FortOrangeexit_p";
	locations[n].models.night.fonars = "FortOrangeexit_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Jamaica_Jungle_03";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore35";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore35";
	locations[n].locators_radius.reload.reload1_back = 2.0;

    Locations[n].reload.l3.name = "reload3";
	Locations[n].reload.l3.go = "FortOrange_town";
	Locations[n].reload.l3.emerge = "reload12";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Street";
	locations[n].locators_radius.reload.reload3 = 1.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// форт Оранж
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "FortOrange_town";
	locations[n].id.label = "Street";
	Locations[n].image = "loading\Town.tga";
	//Town sack
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	LAi_LocationFantomsGen(&locations[n], true);
	//Sound
	locations[n].type = "town";
	Locations[n].townsack = "FortOrange";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	Locations[n].filespath.models = "locations\Town_FortOrange\Town";
	//Always
	Locations[n].models.always.town = "FortOrangetown";
	Locations[n].models.always.town.tech = "DLightModel";
	Locations[n].models.always.mount = "FortOrangetown_exsk";
	Locations[n].models.always.mount.tech = "DLightModel";
	Locations[n].models.always.locators = "FortOrangetown_l";		
	Locations[n].models.always.grassPatch = "FortOrangetown_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "FortOrangetown_b04";
	Locations[n].models.always.l1.level = 9;
	Locations[n].models.always.l1.tech = "DLightModel";
	//Day
	locations[n].models.day.fonars = "FortOrangetown_fd";
	locations[n].models.day.fonars.tech = "DLightModel";
	locations[n].models.day.charactersPatch = "FortOrangetown_pd";
	locations[n].models.day.rinok = "FortOrangetown_e1";
	locations[n].models.day.rinok.tech = "DLightModel";
	Locations[n].models.day.jumpPatch = "FortOrangetown_j";
	//Night
	locations[n].models.night.charactersPatch = "FortOrangetown_pn";
	locations[n].models.night.fonars = "FortOrangetown_fn";	
	Locations[n].models.night.fonars.tech = "DLightModel";
	Locations[n].models.night.jumpPatch = "FortOrangetown_j";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	
	// --> Типовые городские локации, четкая фиксация на 10 номеров.
	Locations[n].reload.l1.name = "reload12";
	Locations[n].reload.l1.go = "FortOrange_ExitTown";
	Locations[n].reload.l1.emerge = "reload3";
	Locations[n].reload.l1.autoreload = "0";
	Locations[n].reload.l1.label = "ExitTown";
	locations[n].locators_radius.reload.reload12 = 1.8;

	Locations[n].reload.l2.name = "reload1";
	Locations[n].reload.l2.go = "FortOrange_Mine";
	Locations[n].reload.l2.emerge = "reload1";
	Locations[n].reload.l2.autoreload = "0";
	Locations[n].reload.l2.label = "MinentownOL";
	locations[n].locators_radius.reload.reload1 = 1.8;
	
	Locations[n].reload.l3.name = "reload13";
	Locations[n].reload.l3.go = "FortOrange_townhall";
	Locations[n].reload.l3.emerge = "reload1";
	Locations[n].reload.l3.autoreload = "0";
	Locations[n].reload.l3.label = "Townhall";
	Locations[n].reload.l3.close_for_night = 1;
	
	Locations[n].reload.l4.name = "reload15";
	Locations[n].reload.l4.go = "FortOrange_tavern";
	Locations[n].reload.l4.emerge = "reload1_back";
	Locations[n].reload.l4.autoreload = "0";
	Locations[n].reload.l4.label = "Tavern";

	Locations[n].reload.l6.name = "reload3";
	Locations[n].reload.l6.go = "FortOrange_store";
	Locations[n].reload.l6.emerge = "reload1";
	Locations[n].reload.l6.autoreload = "0";
	Locations[n].reload.l6.label = "Store";
	Locations[n].reload.l6.close_for_night = 1;
	
	locations[n].reload.l9.name = "reload7";
	locations[n].reload.l9.go = "FortOrange_church";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Church";
	
	Locations[n].reload.l10.name = "reload11";
	Locations[n].reload.l10.go = "FortOrange_packhouse";
	Locations[n].reload.l10.emerge = "reload1";
	Locations[n].reload.l10.autoreload = "0";
	Locations[n].reload.l10.label = "House";
	Locations[n].reload.l10.close_for_night = 1;
	
	// --> Комоны, загрушки. Номера с начинаются с 11.
	locations[n].reload.l11.name = "reload5";
	locations[n].reload.l11.go = "CommonRoom_MH2";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l11.autoreload = "0";
	locations[n].reload.l11.label = "House";
	
	locations[n].reload.l12.name = "reload16";
	locations[n].reload.l12.go = "CommonRoom_MH12";
	locations[n].reload.l12.emerge = "reload1";
	locations[n].reload.l12.autoreload = "0";
	locations[n].reload.l12.label = "House";
	
	locations[n].reload.l13.name = "reload4";
	locations[n].reload.l13.go = "CommonRoom_MH";
	locations[n].reload.l13.emerge = "reload1";
	locations[n].reload.l13.autoreload = "0";
	locations[n].reload.l13.label = "House";
	
	locations[n].reload.l14.name = "reload6";
	locations[n].reload.l14.go = "CommonStoneHouse";
	locations[n].reload.l14.emerge = "reload1";
	locations[n].reload.l14.autoreload = "0";
	locations[n].reload.l14.label = "House";
	
	locations[n].reload.l15.name = "reload9";
	locations[n].reload.l15.go = "CommonTripleFloorHouse";
	locations[n].reload.l15.emerge = "reload1";
	locations[n].reload.l15.autoreload = "0";
	locations[n].reload.l15.label = "House";
	
	locations[n].reload.l16.name = "reload8";
	locations[n].reload.l16.go = "CommonRoom_MH9";
	locations[n].reload.l16.emerge = "reload1";
	locations[n].reload.l16.autoreload = "0";
	locations[n].reload.l16.label = "House";
	
	// --> Псевдоквестовые локации.
	locations[n].reload.l19.name = "reload19";
	locations[n].reload.l19.go = "Orange_mines";
	locations[n].reload.l19.emerge = "reload2";
	locations[n].reload.l19.autoreload = "0";
	locations[n].reload.l19.label = "Dungeon";
    //locations[n].reload.l38.disable = 1; // Закроем на совсем
	
	locations[n].reload.l20.name = "reload2";
	locations[n].reload.l20.go = "Smallhome_K2";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";
    //locations[n].reload.l38.disable = 1; // Закроем на совсем
	
	locations[n].reload.l21.name = "reload14";
	locations[n].reload.l21.go = "Smallhome_K3";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House";
    //locations[n].reload.l21.disable = 1; // Закроем на совсем
	
	locations[n].reload.l22.name = "reload18";
	locations[n].reload.l22.go = "TripleHouse_T1"; //тут есть коммонка CommonFlamHouse
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";
    //locations[n].reload.l38.disable = 1; // Закроем на совсем
	
	locations[n].reload.l23.name = "reload17";
	locations[n].reload.l23.go = "FOrange_Hut3";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";
	//locations[n].reload.l38.disable = 1; // Закроем на совсем
	
	locations[n].reload.l24.name = "reload10";
	locations[n].reload.l24.go = "FortOrange_Crypt";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "dungeon";
	//locations[n].reload.l38.disable = 1; // Закроем на совсем
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом Трехэтажный
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "TripleHouse_T1";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\largehouse01.tga";
	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\largehouse01";
	//Always
	locations[n].models.always.TripleHouse = "largehouse01";
	locations[n].models.always.TripleHouse.level = 65538;
	
	Locations[n].models.always.windows = "largehouse01_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.TripleHouserand= "largehouse01_rand";
	locations[n].models.day.charactersPatch = "largehouse01_patch";
	locations[n].models.day.locators = "largehouse01_locators";
	//Night
	locations[n].models.night.charactersPatch = "largehouse01_patch";
	locations[n].models.night.locators = "largehouse01_Nlocators";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortOrange_town";
	locations[n].reload.l1.emerge = "reload18";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonFlamHouse";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Багованная хата
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Smallhome_K3";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\SmallHouse_inside.tga";
	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\SmallHouse_inside\";
	//Always
	locations[n].models.always.SmallHouse = "SmallHouse_inside";
	//locations[n].models.always.SmallHouse.level = 65538;
	Locations[n].models.always.windows = "SmallHouse_inside_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "SmallHouse_inside_patch";
	locations[n].models.day.locators = "SmallHouse_inside_ld";
	//Night
	locations[n].models.night.charactersPatch = "SmallHouse_inside_patch";
	locations[n].models.night.locators = "SmallHouse_inside_ln";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortOrange_town";
	locations[n].reload.l1.emerge = "reload14";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Маленький дом из ПКМ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Smallhome_K2";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\Smallhome.tga";
	locations[n].MustSetReloadBack = true;
 	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\Smallhome";
	//Always
	locations[n].models.always.Smallhome = "SH";
	locations[n].models.always.Smallhome.level = 65538;
	locations[n].models.always.locators = "SH_l";
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
	locations[n].reload.l1.go = "reload2";
	locations[n].reload.l1.emerge = "FortOrange_town";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом кузнеца с камином
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FOrange_Hut3";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\Hut3.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortOrange";
 	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\Hut3";
	//Always
	locations[n].models.always.locators = "Hut3_locators";
	locations[n].models.always.tavern = "Hut3";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Hut3_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut3_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut3_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortOrange_town";
	locations[n].reload.l1.emerge = "reload14";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	// склеп под часовней
	/////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortOrange_Crypt";
	locations[n].id.label = "Crypt";
	locations[n].image = "loading\Crypt.tga";
	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "Dungeon";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\crypt_inside\";
	//Always
	locations[n].models.always.crypt = "crypt_inside";
	locations[n].models.always.locators = "crypt_inside_locators";
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "crypt_inside_patch";
	//Night
	locations[n].models.night.charactersPatch = "crypt_inside_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortOrange_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Таверна "Синий Лев" в форт Оранж
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	locations[n].id = "FortOrange_tavern";
	locations[n].id.label = "Tavern";
	locations[n].tavern_name = "BlueLion";
	locations[n].filespath.models = "Locations\Inside\Tavern10";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
	//Models
	//Always
	locations[n].models.always.tavern = "Tavern10";
	locations[n].models.always.locators = "Tavern10_locators";
	locations[n].models.always.window = "Tavern10_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;
	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "Tavern10_patch";
	locations[n].models.day.fonars = "Tavern10_fn";
	locations[n].models.day.fonars.tech = "DLightModel";
	//Night
	locations[n].models.night.charactersPatch = "Tavern10_patch";
	locations[n].models.night.fonars = "Tavern10_fn";
	locations[n].models.night.fonars.tech = "DLightModel";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "FortOrange_town";
	locations[n].reload.l1.emerge = "reload15";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "FortOrange_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload11";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната в таверне наверху, форт Оранж
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortOrange_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
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
	locations[n].reload.l1.go = "FortOrange_tavern";
	locations[n].reload.l1.emerge = "reload2_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Магазин форт Оранж
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortOrange_store";
	locations[n].id.label = "Store";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\StoreSmall02";
	
	//Always
	locations[n].models.always.store = "StoreSmall";
	locations[n].models.always.store.tech = "DLightModel";
	locations[n].models.always.locators = "StoreSmall_locators";
	locations[n].models.always.window = "StoreSmall_window";
	locations[n].models.always.window.tech = "DLightModel";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 50;

	locations[n].models.always.back = "..\inside_back";
	//Day
	locations[n].models.day.charactersPatch = "StoreSmall_patch";
	locations[n].models.night.fonars = "storeSmall_fn";
	//Night
	locations[n].models.night.charactersPatch = "StoreSmall_patch";
	locations[n].models.night.fonars = "storeSmall_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortOrange_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
    ////////////////////////==> комната в магазине
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonPackhouse_1";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Резиденция форт Оранж
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortOrange_townhall";
	locations[n].id.label = "Townhall";
	locations[n].image = "loading\inside\smallresidence.tga";
	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
	// стража
	locations[n].soldiers = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\SmallResidence";
	locations[n].models.always.locators = "SmallResidence_locators";
	locations[n].models.always.house = "SmallResidence";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "SmallResidence_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "SmallResidence_patch";
	//Night
	locations[n].models.night.charactersPatch = "SmallResidence_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortOrange_town";
	locations[n].reload.l1.emerge = "reload13";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.box.box1 = 1.4;
    locations[n].locators_radius.randitem.randitem1 = 1.0;
    locations[n].locators_radius.item.item1 = 1.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ЦЕРКОВЬ форт Оранж
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortOrange_church";
	locations[n].id.label = "Church";
	locations[n].image = "loading\inside\church.tga";
	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\churchInside4";
	//Always
	locations[n].models.always.churchInside4 = "church2";
	locations[n].models.always.churchInside4.tech = "DLightModel";
	locations[n].models.always.churchInside4.level = 65538;
	locations[n].models.always.locators = "Church2_l"; //churchInside2_locators 
	
	locations[n].models.always.backgroundInsides = "backgroundInsides";
	locations[n].models.always.backgroundInsides.tech = "DLightModel";
	locations[n].models.always.backgroundInsides.level = 65529;
	
	Locations[n].models.always.churchInside2windows = "church2_w";
	Locations[n].models.always.churchInside2windows.tech = "DLightModel";
	locations[n].models.always.churchInside2windows.level = 65539;
	
	/*Locations[n].models.always.churchInside2alpha = "churchInside2_alpha";
	Locations[n].models.always.churchInside2alpha.tech = "LocationWindows";
	locations[n].models.always.churchInside2alpha.level = 65540;
	
	Locations[n].models.always.churchInside2gold = "churchInside2_gold";
	Locations[n].models.always.churchInside2gold.reflection = 0.6;
	Locations[n].models.always.churchInside2gold.tech = "EnvironmentShader";
	locations[n].models.always.churchInside2gold.level = 65541;*/
	//Day
	locations[n].models.day.charactersPatch = "Church2_p";
	//Night
	locations[n].models.night.charactersPatch = "Church2_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortOrange_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Склад 02 (ККС)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortOrange_packhouse";
	locations[n].id.label = "Warehouse";
	locations[n].image = "loading\inside\Sklad.tga";
	locations[n].MustSetReloadBack = true;
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortOrange";
	locations[n].islandId = "Jamaica";
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
	locations[n].reload.l1.go = "FortOrange_town";
	locations[n].reload.l1.emerge = "reload11";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Охраняемый рудник Оранье-Лавас около Форт Оранж
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "FortOrange_Mine";
	locations[n].id.label = "MinentownOL";
	locations[n].image = "loading\outside\GateMine.tga";
	//Town sack
	Locations[n].townsack = "FortOrange";
	locations[n].islandId = "Jamaica";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	//Sound
	locations[n].type = "plantation";
	//Models
	Locations[n].filespath.models = "locations\Outside\Mine";
	//Always
	Locations[n].models.always.mine = "canyon";
	Locations[n].models.always.mine.tech = "DLightModel";
	Locations[n].models.always.locators = "canyon_locators";		
	Locations[n].models.always.grassPatch = "canyon_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";	
	Locations[n].models.always.l1 = "plan3";
	Locations[n].models.always.l1.level = 7;
	Locations[n].models.always.l1.tech = "DLightModel"; //только горы приоры
	locations[n].models.always.L2 = "canyon_shackle";
    locations[n].models.always.L2.tech = "DLightModel";

	/*Locations[n].models.always.l2 = "plan1";
	Locations[n].models.always.l2.level = 9;
	Locations[n].models.always.l2.tech = "LocationModelBlend";*/ //я хз что это, но это поело говна konstrush
	//Day
	locations[n].models.day.charactersPatch = "canyon_patch";
	locations[n].models.day.fonars = "canyon_fd";
	Locations[n].models.day.fonars.tech = "DLightModel";
	//Night
	locations[n].models.night.charactersPatch = "canyon_patch";
	locations[n].models.night.fonars = "canyon_fn";
	Locations[n].models.night.fonars.tech = "DLightModel";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortOrange_town";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	locations[n].locators_radius.rld.attack1 = 2.5;

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonRoom_MH4";
    locations[n].reload.l2.emerge = "reload1";  
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "House";
	
	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Smallhome02_K2";
    locations[n].reload.l3.emerge = "reload1";  
    locations[n].reload.l3.autoreload = "0";
    locations[n].reload.l3.label = "House";
	
	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "Orange_mines";
    locations[n].reload.l4.emerge = "reload1";  
    locations[n].reload.l4.autoreload = "0";
    locations[n].reload.l4.label = "Mines";
	
	locations[n].reload.l5.name = "reload5";
	locations[n].reload.l5.go = "Mine_residence";
    locations[n].reload.l5.emerge = "reload3";  
    locations[n].reload.l5.autoreload = "0";
    locations[n].reload.l5.label = "House";
	
	locations[n].reload.l6.name = "reload6";
	locations[n].reload.l6.go = "OutRHouse";
    locations[n].reload.l6.emerge = "reload1";  
    locations[n].reload.l6.autoreload = "1";
    locations[n].reload.l6.label = "jungle";
    locations[n].locators_radius.reload.reload6 = 2.0;
	locations[n].locators_radius.rld.warrior = 5.0;
	n = n + 1;
	
	////////////////////////////////////////////////////////////////////////////////////////////////////
	// шахты Оранье-Лавас
	///////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Orange_mines";
	locations[n].id.label = "dungeon";
    locations[n].image = "loading\inside\Mine.tga";
	//Sound
	locations[n].type = "cave";
	locations[n].islandId = "Jamaica";
	locations[n].townsack = "FortOrange";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\DungeonOrange1";
	locations[n].models.always.DungeonOrange1 = "DungeonOrange1";
	locations[n].models.always.locators = "DungeonOrange1_locators";
	//locations[n].models.always.DungeonOrange1.tech = "DLightModel";
	//бочки и прочее не трогать
	locations[n].models.always.DungeonOrange1_stuff = "DungeonOrange1_stuff";
	//locations[n].models.always.DungeonOrange1_stuff.tech = "DLightModel";
	//завал в шахте, который убирается по квесту
	locations[n].models.always.DungeonOrange1_rocks = "DungeonOrange1_rocks";
	//locations[n].models.always.DungeonOrange1_rocks.tech = "DLightModel";
	//стена подвала, которая убирается по квесту
	locations[n].models.always.DungeonOrange1_wall = "DungeonOrange1_wall";
	//locations[n].models.always.DungeonOrange1_wall.tech = "DLightModel";
	//после взрыва стены построили дверь с охранником
	locations[n].models.always.DungeonOrange1_door = "DungeonOrange1_door";
	//locations[n].models.always.DungeonOrange1_door.tech = "DLightModel";
	locations[n].locators_radius.soldiers.protector1 = 1.5;
	locations[n].locators_radius.quest.mushketer2 = 2.0;
/*
	Locations[n].models.always.rays = "DungeonDuffer2_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;	
*/	
	//Day
	locations[n].models.day.charactersPatch = "DungeonOrange1_patch1";
	//после разгребания завала или после постройки двери
	//locations[n].models.day.charactersPatch = "DungeonOrange1_patch2";
	//полный доступ, взорвали стену и разгребли завал
	//locations[n].models.day.charactersPatch = "DungeonOrange1_patch3";
	//Night
	locations[n].models.night.charactersPatch = "DungeonOrange1_patch1";
	//после разгребания завала или после постройки двери
	//locations[n].models.night.charactersPatch = "DungeonOrange1_patch2";
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
	locations[n].reload.l1.go = "FortOrange_Mine";
	locations[n].reload.l1.emerge = "reload4";
	Locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "mines";
	
	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "FortOrange_Town";
	locations[n].reload.l2.emerge = "reload19";
	Locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Town";
	n = n + 1;
	
	/////////////////// Резиденция (комната 3) ////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Mine_residence";
	locations[n].id.label = "MineTown_residence";
	locations[n].MustSetReloadBack = true;
	locations[n].DisableEncounters = true;
	locations[n].image = "loading\inside\mediumhouse12.tga";
	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\mediumhouse11_12";
	//Always
	locations[n].models.always.house = "mediumhouse11";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "mediumhouse11_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.locators = "mediumhouse11_locators";

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
	locations[n].reload.l1.name = "reload3";
	locations[n].reload.l1.go = "FortOrange_Mine";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "";
	locations[n].locators_radius.item.item1 = 1.0;
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Маленький дом из ПКМ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Smallhome02_K2";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\Smallhome.tga";
 	//Town sack
	locations[n].townsack = "FortOrange";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].islandId = "Jamaica";
	//Models
	locations[n].filespath.models = "locations\inside\Smallhome02";
	//Always
	locations[n].models.always.Smallhome02 = "SH";
	locations[n].models.always.Smallhome02.level = 65538;
	locations[n].models.always.locators = "SH_l";
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
	locations[n].reload.l1.go = "FortOrange_Mine";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;
	
	/*//////////////////////////////////////////////////////////////////////////////////////////////////////////////
	////// дом в локации после шахты
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Pirl";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle_" + rand(3) + ".tga";
	locations[n].DisableEncounters = true;
 	//Sound
	locations[n].islandId = "Jamaica";
	locations[n].type = "jungle";
	locations[n].Realm = "FortOrange";
	//Models
	locations[n].filespath.models = "locations\Outside\Pirl";
	//Always
	Locations[n].models.always.pirl = "pirl";	
	Locations[n].models.always.locators = "pirl_locators";		
	Locations[n].models.always.grassPatch = "pirl_grass";
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
	locations[n].models.day.charactersPatch = "pirl_patch";
	locations[n].models.day.fonar = "pirl_fd";
	//Night
	locations[n].models.night.charactersPatch = "pirl_patch";	
	locations[n].models.night.fonar = "pirl_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore46";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Amelia_house";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Dunes house";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	n = n + 1;*/

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Локация с домиком в джунглях после шахты
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "OutRHouse";
	locations[n].id.label = "jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].islandId = "Jamaica";
	locations[n].type = "jungle";
	locations[n].DisableEncounters = true;
	locations[n].Realm = "FortOrange";
	//Models
	//Always
	Locations[n].filespath.models = "locations\Outside\OutRHouse";
    Locations[n].models.always.house = "RHouse";
	Locations[n].models.always.house.tech = "DLightModel";
    Locations[n].models.always.grassPatch = "rhouse_g";
    Locations[n].models.always.l1 = "rhouse_b01";
    Locations[n].models.always.l1.level = 9;
    Locations[n].models.always.l1.tech = "LocationModelBlend";
    Locations[n].models.always.l2 = "rhouse_b02";
    Locations[n].models.always.l2.level = 8;
    Locations[n].models.always.l2.tech = "LocationModelBlend";
    Locations[n].models.always.l3 = "rhouse_b03";
    Locations[n].models.always.l3.level = 7;
    Locations[n].models.always.l3.tech = "LocationModelBlend";
	Locations[n].models.always.l4 = "rhouse_b04";
    Locations[n].models.always.l4.level = 7;
    Locations[n].models.always.l4.tech = "LocationModelBlend";
	Locations[n].models.always.locators = "rhouse_l";
	
	Locations[n].models.always.grassPatch = "rhouse_g";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
    //Day
    Locations[n].models.day.charactersPatch = "rhouse_p";
    //Night
    Locations[n].models.night.charactersPatch = "rhouse_p";
    //Environment
    Locations[n].environment.weather = "true";
    Locations[n].environment.sea = "false";	
	//Reload map
	locations[n].reload.l1.name = "reload2_back";
	locations[n].reload.l1.go = "SmallHouse_Jungle";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "House";
	locations[n].locators_radius.reload.reload2 = 1.3;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "FortOrange_Mine";
	locations[n].reload.l2.emerge = "reload6";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Маленький домик
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "SmallHouse_Jungle";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\SmallHouse_inside.tga";
	locations[n].islandId = "Jamaica";
	locations[n].Realm = "FortOrange";
	//Town sack
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "House";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\SmallHouse_inside\";
	locations[n].models.always.SmallHouse = "SmallHouse_inside";
	//locations[n].models.always.SmallHouse.level = 65538;
	Locations[n].models.always.windows = "SmallHouse_inside_windows";
	Locations[n].models.always.windows.tech = "LocationWindows";
	locations[n].models.always.windows.level = 65539;

	locations[n].models.always.back = "..\inside_back2";
	//Day
	locations[n].models.day.charactersPatch = "SmallHouse_inside_patch";
	locations[n].models.day.locators = "SmallHouse_inside_ld";
	//Night
	locations[n].models.night.charactersPatch = "SmallHouse_inside_patch";
	locations[n].models.night.locators = "SmallHouse_inside_ln";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	Locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "OutRHouse";
	locations[n].reload.l1.emerge = "reload2_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "jungle";
	n = n + 1;
	
	return n;
}

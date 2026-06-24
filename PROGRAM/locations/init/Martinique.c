int LocationInitMartinique(int n)
{	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОРОД
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_town";
	locations[n].id.label = "Street";
	locations[n].worldmap = "Martinique";
	locations[n].filespath.models = "locations\Town_Martinique\Town\";
	locations[n].image = "loading\Town.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	//==> флаг генерации квестодателя по розыску кэпов, int значение - шанс что сам заговорит(1-10)
	locations[n].questSeekCap = 6;
	//Town sack
	locations[n].townsack = "FortFrance";
	//Sound
	locations[n].type = "town";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	//Always
	locations[n].models.always.town = "Martinique";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.L1 = "Martinique_signsA";
	locations[n].models.always.L2 = "Malta_doors";
	locations[n].models.always.L2.tech = "DLightModel";
	locations[n].models.always.seabed = "Martinique_sb";
	locations[n].models.always.locators = "Martinique_locators";
	locations[n].models.always.grassPatch = "Martinique_grass";
	
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.level = 9;

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

	//WindMill Fan
	locations[n].models.always.MillFan = "MillFan";
	Locations[n].models.always.MillFan.locator.group = "WindMill";
	Locations[n].models.always.MillFan.locator.name ="Fan";	
	Locations[n].models.always.MillFan.rotate.x = 0.0;
	Locations[n].models.always.MillFan.rotate.y = 0.0;
	Locations[n].models.always.MillFan.rotate.z = 0.2;

	//Day
	locations[n].models.day.fonar = "Martinique_fd";
	locations[n].models.day.charactersPatch = "Martinique_patch_day";
	locations[n].models.day.rinok = "Martinique_rinok";
	//Night
	locations[n].models.night.fonar = "Martinique_fn";
	locations[n].models.night.charactersPatch = "Martinique_patch_night";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map

    // --> Типовые городские локации, четкая фиксация на 10 номеров.
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Martinique";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 1.8;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Martinique";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.reload2_back = 1.8;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "FortFrance_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "FortFrance_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "FortFrance_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "FortFrance_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "reload7_back";
	locations[n].reload.l7.go = "FortFrance_church";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Church";
	//locations[n].reload.l7.close_for_night = 1;

	locations[n].reload.l8.name = "reload8_back";
	locations[n].reload.l8.go = "FortFrance_bank";
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "Usurer House";
	locations[n].reload.l8.close_for_night = 1;

	locations[n].reload.l9.name = "reload9_back";
	locations[n].reload.l9.go = "FortFrance_brothel";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "Brothel";

 	locations[n].reload.l91.name = "reload91";
	locations[n].reload.l91.go = "FortFrance_SecBrRoom";
	locations[n].reload.l91.emerge = "reload2";
	locations[n].reload.l91.autoreload = "0";
	locations[n].reload.l91.label = "Brothel";

	locations[n].reload.l10.name = "reload10_back";
	locations[n].reload.l10.go = "FortFrance_PortOffice";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "PortOffice";
	locations[n].reload.l10.close_for_night = 1;

	locations[n].reload.gate.name = "gate_back";
	locations[n].reload.gate.go = "FortFrance_ExitTown";
	locations[n].reload.gate.emerge = "reload3";
	locations[n].reload.gate.autoreload = "0";
	locations[n].reload.gate.label = "ExitTown";
	
	locations[n].reload.jail.name = "reload_jail";
	locations[n].reload.jail.go = "FortFrance_prison";
	locations[n].reload.jail.emerge = "reload1";
	locations[n].reload.jail.autoreload = "0";
	locations[n].reload.jail.label = "Prison";
	
    // --> Квестовые локации.
	locations[n].reload.l11.name = "houseK5"; // Дом Гранье
	locations[n].reload.l11.go = "FortFrance_houseK5";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l11.autoreload = "0";	
	locations[n].reload.l11.label = "Granie_house";

	locations[n].reload.l13.name = "reloadPr1"; // Мальтийский орден
	locations[n].reload.l13.go = "FortFrance_Malta_Dungeon";
	locations[n].reload.l13.emerge = "reload1";
	locations[n].reload.l13.autoreload = "0";
	locations[n].reload.l13.label = "Malta_Dungeon";
	locations[n].reload.l13.close_for_night = 1;

	locations[n].reload.l12.name = "basement2"; // Мальтийский орден
	locations[n].reload.l12.go = "FortFrance_Malta_Dungeon";
	locations[n].reload.l12.emerge = "reload2";
	locations[n].reload.l12.autoreload = "0";
	locations[n].reload.l12.label = "Malta_Dungeon";
	locations[n].reload.l12.close_for_night = 1;

	locations[n].reload.l14.name = "basement1"; // Подземелье
	locations[n].reload.l14.go = "FortFrance_Dungeon";
	locations[n].reload.l14.emerge = "reload1";
	locations[n].reload.l14.autoreload = "0";
	locations[n].reload.l14.label = "Dungeon";

	locations[n].reload.l15.name = "houseK12";
	locations[n].reload.l15.go = "FortFrance_BigHouse6";
	locations[n].reload.l15.emerge = "reload2";
	locations[n].reload.l15.autoreload = "0";
	locations[n].reload.l15.label = "House";

	locations[n].reload.l16.name = "houseK13";
	locations[n].reload.l16.go = "FortFrance_BigHouse6";
	locations[n].reload.l16.emerge = "reload3";
	locations[n].reload.l16.autoreload = "0";
	locations[n].reload.l16.label = "House";

	locations[n].reload.l17.name = "houseK14";
	locations[n].reload.l17.go = "FortFrance_BigHouse6";
	locations[n].reload.l17.emerge = "reload1";
	locations[n].reload.l17.autoreload = "0";
	locations[n].reload.l17.label = "House";

	locations[n].reload.l18.name = "houseH1";
	locations[n].reload.l18.go = "FortFrance_HouseHut";
	locations[n].reload.l18.emerge = "reload1";
	locations[n].reload.l18.autoreload = "0";
	locations[n].reload.l18.label = "House";

	locations[n].reload.l19.name = "houseH3";
	locations[n].reload.l19.go = "FortFrance_HouseHut";
	locations[n].reload.l19.emerge = "reload2";
	locations[n].reload.l19.autoreload = "0";
	locations[n].reload.l19.label = "House";	

    // --> Комоны, загрушки. Номера с начинаются с 20.
	locations[n].reload.l20.name = "houseK9";
	locations[n].reload.l20.go = "FortFrance_MH9_2";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";  

	locations[n].reload.l21.name = "houseK16";
	locations[n].reload.l21.go = "FortFrance_Hut1";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House";
	
	locations[n].reload.l22.name = "houseK7";
	locations[n].reload.l22.go = "FortFrance_HouseBig";
	locations[n].reload.l22.emerge = "reload2";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";

	locations[n].reload.l23.name = "houseK8";
	locations[n].reload.l23.go = "FortFrance_HouseBig";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";

	locations[n].reload.l24.name = "houseH2";
	locations[n].reload.l24.go = "FortFrance_Hut3";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "House";

	locations[n].reload.l25.name = "houseK1";
	locations[n].reload.l25.go = "FortFrance_HouseBig";
	locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "House";
	locations[n].reload.l25.disable = 1; // закрыто

	locations[n].reload.l26.name = "houseK2";
	locations[n].reload.l26.go = "FortFrance_HouseBig";
	locations[n].reload.l26.emerge = "reload1";
	locations[n].reload.l26.autoreload = "0";
	locations[n].reload.l26.label = "House";
	locations[n].reload.l26.disable = 1; // закрыто

	locations[n].reload.l27.name = "houseK3";
	locations[n].reload.l27.go = "FortFrance_HouseBig";
	locations[n].reload.l27.emerge = "reload1";
	locations[n].reload.l27.autoreload = "0";
	locations[n].reload.l27.label = "House";
	locations[n].reload.l27.disable = 1; // закрыто

	locations[n].reload.l28.name = "houseS2";
	locations[n].reload.l28.go = "FortFrance_MH9_2";
	locations[n].reload.l28.emerge = "reload1";
	locations[n].reload.l28.autoreload = "0";
	locations[n].reload.l28.label = "House";
	locations[n].reload.l28.disable = 1; // закрыто

	locations[n].reload.l29.name = "houseF3";
	locations[n].reload.l29.go = "CommonRoom_MH3";
	locations[n].reload.l29.emerge = "reload1";
	locations[n].reload.l29.autoreload = "0";
	locations[n].reload.l29.label = "House";		

	locations[n].reload.l30.name = "houseF4";
	locations[n].reload.l30.go = "CommonRoom_MH";
	locations[n].reload.l30.emerge = "reload1";
	locations[n].reload.l30.autoreload = "0";
	locations[n].reload.l30.label = "House";

	locations[n].reload.l31.name = "houseSp1";
	locations[n].reload.l31.go = "CommonResidence_BackHall";
	locations[n].reload.l31.emerge = "reload1";
	locations[n].reload.l31.autoreload = "0";
	locations[n].reload.l21.label = "House";	

	locations[n].reload.l32.name = "houseS1";
	locations[n].reload.l32.go = "CommonCobHouse";
	locations[n].reload.l32.emerge = "reload1";
	locations[n].reload.l32.autoreload = "0";
	locations[n].reload.l32.label = "House";

	locations[n].reload.l33.name = "houseF1";
	locations[n].reload.l33.go = "CommonRoom_MH5";
	locations[n].reload.l33.emerge = "reload1";
	locations[n].reload.l33.autoreload = "0";
	locations[n].reload.l33.label = "House";

	locations[n].reload.l34.name = "houseF2";
	locations[n].reload.l34.go = "CommonRoom_MH2";
	locations[n].reload.l34.emerge = "reload1";
	locations[n].reload.l34.autoreload = "0";
	locations[n].reload.l34.label = "House";	

	locations[n].reload.l35.name = "houseK4";
	locations[n].reload.l35.go = "CommonRoom_MH7";
	locations[n].reload.l35.emerge = "reload1";
	locations[n].reload.l35.autoreload = "0";
	locations[n].reload.l35.label = "House";

	locations[n].reload.l36.name = "houseK6";
	locations[n].reload.l36.go = "CommonStoneHouse";
	locations[n].reload.l36.emerge = "reload1";
	locations[n].reload.l36.autoreload = "0";
	locations[n].reload.l36.label = "House";

	locations[n].reload.l37.name = "houseK11";
	locations[n].reload.l37.go = "CommonStoneHouse";
	locations[n].reload.l37.emerge = "reload1";
	locations[n].reload.l37.autoreload = "0";
	locations[n].reload.l37.label = "House";

	locations[n].reload.l38.name = "houseK10";
	locations[n].reload.l38.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l38.emerge = "reload1";
	locations[n].reload.l38.autoreload = "0";
	locations[n].reload.l38.label = "House";

	locations[n].reload.l39.name = "houseD";
	locations[n].reload.l39.go = "CommonDoubleflourHouse_1";
	locations[n].reload.l39.emerge = "reload1";
	locations[n].reload.l39.autoreload = "0";
	locations[n].reload.l39.label = "House";

	locations[n].reload.l40.name = "boat";
	locations[n].reload.l40.go = "Martinique";
	locations[n].reload.l40.emerge = "reload_1";
	locations[n].reload.l40.autoreload = "0";
	locations[n].reload.l40.label = "Sea";
	locations[n].locators_radius.reload.boat = 3.5;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ТАВЕРНА
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_tavern";
	locations[n].id.label = "Tavern";
	locations[n].image = "loading\inside\Tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
	//Models
	locations[n].filespath.models = "locations\inside\Tavern01\";
	//Always
	locations[n].models.always.tavern = "Tavern01";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.locators = "Tavern01_locators";
	locations[n].models.always.window = "tavern01_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.window.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Tavern01_patch";
	//Night
	locations[n].models.night.charactersPatch = "Tavern01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "FortFrance_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// КОМНАТА В ТАВЕРНЕ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_tavern_upstairs";
	locations[n].filespath.models = "locations\inside\Tavern_room";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// МАГАЗИН
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\Store01\";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "reload6";
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
	// РОСТОВЩИК
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_Bank";
	locations[n].id.label = "Usurer House";
	locations[n].filespath.models = "locations\inside\bank01\";
	locations[n].image = "loading\inside\bank.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
	//Models
	//Always
	locations[n].models.always.locators = "Bank01_locators";
	locations[n].models.always.store = "Bank01";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Bank01_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "bank01_patch";
	//Night
	locations[n].models.night.charactersPatch = "bank01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "reload8";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "FortFrance_bankvault";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Хранилище (Банк)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_bankvault";
	locations[n].id.label = "bankvault";
	locations[n].image = "loading\inside\vault.tga";
	//locations[n].MustSetReloadBack = true;
	//locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_bank";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// БОРДЕЛЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_Brothel";
	locations[n].id.label = "Brothel";
	locations[n].filespath.models = "locations\inside\Brothel\";
	locations[n].image = "loading\inside\brothell_hall.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "reload9";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "FortFrance_Brothel_room";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Brothel Room";
	locations[n].reload.l2.disable = 1;  //закроем, но связка пусть будет для квестов.

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "FortFrance_SecBrRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комнаты в борделе
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_Brothel_room";
	locations[n].id.label = "Brothel Room";
	locations[n].filespath.models = "locations\inside\Brothel_room\";
	locations[n].image = "loading\inside\brothell_room.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
 	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_brothel";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	locations[n].locators_radius.item.item1 = 1;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_SecBrRoom"; // вторая комната борделя
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\BigHouse03.tga";
 	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_Brothel";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "FortFrance_town";
	locations[n].reload.l2.emerge = "reload91";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ВЕРФЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_Shipyard";
	locations[n].id.label = "Shipyard";
	locations[n].filespath.models = "locations\inside\Shipyard03\";
	locations[n].image = "loading\inside\shipyard.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "FortFrance";
 	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "FortFrance_Packhouse";
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
	locations[n].id = "FortFrance_Packhouse";
	locations[n].id.label = "Packhouse";
	locations[n].image = "loading\inside\sklad.tga";
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "FortFrance";
 	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_Shipyard";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Shipyard";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "FortFrance_PackhouseOffice";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "PackhouseOffice";
	locations[n].reload.l2.close_for_night = 1;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Офис заведующиго пакгаузом
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_PackhouseOffice";
	locations[n].id.label = "PackhouseOffice";
	locations[n].image = "loading\inside\sklad.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_Packhouse";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Packhouse";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// РЕЗИДЕНЦИЯ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_townhall";
	locations[n].id.label = "Townhall";
	locations[n].filespath.models = "locations\inside\Residence01";
	locations[n].image = "loading\inside\Residence01.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
	// стража
	locations[n].soldiers = true;
	LAi_LocationFantomsGen(&locations[n], true);
	//Models
	//Always
	locations[n].models.always.locators = "Residence01_locators";
	locations[n].models.always.l1 = "Residence01";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.window = "residence01_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;	
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Residence01_patch";
	//Night
	locations[n].models.night.charactersPatch = "Residence01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].locators_radius.reload.dialog_event = 0.2;
	locations[n].locators_radius.camdetector.dialog_event = 2.2;

	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "CommonResidence_4";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";

	locations[n].reload.l3.name = "reload3"; //кабинет направо от входа
	locations[n].reload.l3.go = "CommonResidence_2";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ЦЕРКОВЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_church";
	locations[n].id.label = "Church";
	locations[n].image = "loading\inside\church.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Church01";
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
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ПОРТОВЫЙ ОФИС
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_PortOffice";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\inside\portoffice.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\PortOffice";
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
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	////////////////////// prison ////////////////////////////
	Locations[n].id = "FortFrance_prison";
	locations[n].id.label = "Prison";
	Locations[n].image = "loading\inside\prison.tga";
	locations[n].townsack = "FortFrance";
    locations[n].parent_colony = "FortFrance";
 	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
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
	Locations[n].reload.l1.go = "FortFrance_town";
	Locations[n].reload.l1.emerge = "reload_jail";
	locations[n].reload.l1.label = "Street";
	Locations[n].reload.l1.autoreload = "0";
	
	locations[n].locators_radius.box.box1 = 0.8;

	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// База мальтийских рыцарей
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_Malta_Dungeon";
	locations[n].id.label = "Malta_Dungeon";
	locations[n].image = "loading\inside\Maltas.tga";
	//Town sack
	locations[n].type = "Dungeon";
	locations[n].townsack = "FortFrance";
	locations[n].islandId = "Martinique";
	//Sound
	locations[n].fastreload = "FortFrance";
	locations[n].Maltains = true;
	//Always
	locations[n].filespath.models = "locations\inside\Maltains";
	locations[n].models.always.Maltains = "Malta_Base";
	locations[n].models.always.InquisitionMaltainsFonars = "Malta_fonars";
	locations[n].models.always.locators = "Malta_locators";
	
	//Day
	locations[n].models.day.charactersPatch = "Malta_patch";
	//Night
	locations[n].models.night.charactersPatch = "Malta_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "reloadPr1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "FortFrance_town";
	locations[n].reload.l2.emerge = "basement2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Дом Гранье
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_houseK5";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse09.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\mediumhouse09";
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
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "houseK5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Средний дом 8 (9 с заменённой стенкой)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_MH9_2";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse08.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "houseK9";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Дом с 3 дверьми
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_BigHouse6";
 	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\BigHouse06.tga";
 	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "houseK14";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "FortFrance_town";
	locations[n].reload.l2.emerge = "houseK12";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "FortFrance_town";
	locations[n].reload.l3.emerge = "houseK13";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Street";

	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Изба рыбака
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_HouseHut";
	locations[n].filespath.models = "locations\inside\Hut";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\hut1.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
	//Models
	//Always
	locations[n].models.always.locators = "Hut_locators";
	locations[n].models.always.tavern = "Hut";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "Hut_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Hut_patch";
	//Night
	locations[n].models.night.charactersPatch = "Hut_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "houseH1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "FortFrance_town";
	locations[n].reload.l2.emerge = "houseH3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Подземелье Фор-де-Франс
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_Dungeon";
	locations[n].id.label = "Dungeon";
	locations[n].image = "loading\inside\dungeon.tga";
	//Town sack
	locations[n].type = "Dungeon";
	locations[n].townsack = "FortFrance";
	locations[n].islandId = "Martinique";
	//Sound
	//Always
	locations[n].filespath.models = "locations\inside\DungeonVault2";
	locations[n].models.always.DungeonVault2 = "DungeonVault2";
	locations[n].models.always.InquisitionDungeonVault2Fonars = "DungeonVault2_fonars";
	locations[n].models.always.locators = "DungeonVault2_locators";

	// EvgAnat - "дикие Карибы", убираем дефолтные сферы
	locations[n].locators_radius.item.duhi1 = 0.0;
	
/*	Locations[n].models.always.rays = "DungeonVault2_rays";
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech= "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;	*/
	//Day
	locations[n].models.day.charactersPatch = "DungeonVault2_patch";
	//Night
	locations[n].models.night.charactersPatch = "DungeonVault2_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "basement1";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.item.berglar1 = 4.5;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Хижина с гамаком
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_Hut1";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\littlehut.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l2.name = "reload1";
	locations[n].reload.l2.go = "FortFrance_town";
	locations[n].reload.l2.emerge = "houseK16";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);		
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Большой дом с двумя входами
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_HouseBig";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\flamhouse.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
 	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "houseK8";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "FortFrance_town";
	locations[n].reload.l2.emerge = "houseK7";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "CommonRoom_MH3";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";
	locations[n].reload.l3.disable = 0; //закроем

	locations[n].reload.l4.name = "reload4";
	locations[n].reload.l4.go = "CommonRoom_MH4";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Room";
	locations[n].reload.l4.disable = 0; //закроем
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Хижина с камином
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_Hut3";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\Hut3.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "FortFrance";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "FortFrance";
 	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "houseH2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход в джунгли из Фор-де-Франс
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "FortFrance_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate.tga";
	//Town sack
	locations[n].townsack = "FortFrance";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Martinique";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\TownExitY";
	Locations[n].models.always.townExit = "townExitY";
	Locations[n].models.always.townWalls = "townExitY_stone";
	
	Locations[n].models.always.locators = "townExitY_locators";
		
	Locations[n].models.always.grassPatch = "townExitY_grass";
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
	locations[n].models.day.charactersPatch = "townExitY_patch";
	locations[n].models.day.fonars = "townExitY_fd";
	//Night
	locations[n].models.night.charactersPatch = "townExitY_patch";
	locations[n].models.night.fonars = "townExitY_fn";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload3";
	locations[n].reload.l1.go = "FortFrance_town";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "FortFrance";

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "Martinique_jungle_01";
	locations[n].reload.l2.emerge = "reload2";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l3.name = "reload2_back";
	locations[n].reload.l3.go = "FortFrance_fort";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "FortFrance Fort";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;
	
 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Martinique_jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "Martinique_jungle_02";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "FortFrance_ExitTown";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "ExitTown";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Shore38";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Shore38";
	locations[n].locators_radius.reload.reload3_back = 2;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Пляж Ламантен
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore38";
	locations[n].id.label = "Shore38";
	locations[n].image = "loading\outside\harbor.tga";
	locations[n].worldmap = "Shore38";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "Martinique_jungle_01";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Martinique";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Martinique_jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "Martinique_jungle_01";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Martinique_jungle_03";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "LeFransua_ExitTown";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Martinique_jungle_03";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Martinique";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle1\";
	Locations[n].models.always.jungle = "jungle1";
	Locations[n].models.always.locators = "jungle1_locators";		
	Locations[n].models.always.grassPatch = "jungle1_grass";
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
	locations[n].models.day.charactersPatch = "jungle1_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle1_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Martinique_jungle_02";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore39";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore39";
	locations[n].locators_radius.reload.reload2_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Бухта Ле Марен
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore39";
	locations[n].id.label = "Shore39";
	locations[n].image = "loading\outside\harbor.tga";
	locations[n].worldmap = "Shore39";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Martinique";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore06";
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
	locations[n].reload.l1.go = "Martinique_jungle_03";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Martinique";
	locations[n].reload.l2.emerge = "reload_4";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли тупиковые
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_deadlock";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
    locations[n].islandId = "Martinique";
	locations[n].Realm = "LeFransua";
	//Models
	locations[n].filespath.models = "locations\Outside\Jungles\jungle9\";
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
	Locations[n].models.always.l4 = "jungle9_l1";

	//Day
	//locations[n].models.day.charactersPatch = "jungle9_patch";
	locations[n].models.day.charactersPatch = "jungle9_patch2";
	//Night
	//locations[n].models.night.charactersPatch = "jungle9_patch";
	locations[n].models.night.charactersPatch = "jungle9_patch2";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LeFransua_ExitTown";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "ExitTown";
	locations[n].locators_radius.reload.reload1_back = 2.2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из города Ле Франсуа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_ExitTown";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\Gate.tga";
	//Town sack
	locations[n].townsack = "LeFransua";
	//Sound
	locations[n].type = "jungle";
	locations[n].fastreload = "LeFransua";
    locations[n].islandId = "Martinique";
	//Models
	locations[n].filespath.models = "locations\Outside\Jungles\TownExitT";
	//Always
	Locations[n].models.always.townExit = "townExitT";
	Locations[n].models.always.locators = "townExitT_KNS_locators";
	Locations[n].models.always.grassPatch = "townExitT_grass";

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
    Locations[n].reload.l1.name = "reload5_back";
	Locations[n].reload.l1.go = "LeFransua_town";
	Locations[n].reload.l1.emerge = "reload_2";
	Locations[n].reload.l1.autoreload = "1";
	Locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.reload.reload5_back = 2.7;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "Martinique_jungle_02";
	locations[n].reload.l2.emerge = "reload3";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload2_back";
	locations[n].reload.l3.go = "LeFransua_deadlock";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Ле Франсуа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_town";
	locations[n].id.label = "Street";
	locations[n].image = "loading\Town.tga";
	locations[n].worldmap = "Martinique";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	//Town sack
	locations[n].townsack = "LeFransua";
	//Sound
	locations[n].type = "town";
	locations[n].fastreload = "LeFransua";
	locations[n].islandId = "Martinique";
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	Locations[n].filespath.models = "locations\LeFransua";
	//Always
	locations[n].models.always.town = "LeFransua";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.seabed = "LeFransua_sb";
	locations[n].models.always.locators = "LeFransua_locators";
	locations[n].models.always.grassPatch = "LeFransua_grass";
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.level = 9;
	//Day
	locations[n].models.day.fonar = "LeFransua_fd";
	locations[n].models.day.charactersPatch = "LeFransua_patch_day";
	locations[n].models.day.rinok = "LeFransua_rinok";
	//Night
	locations[n].models.night.fonar = "LeFransua_fn";
	locations[n].models.night.charactersPatch = "LeFransua_patch_night";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";

	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Martinique";
	locations[n].reload.l1.emerge = "reload_3";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 2;

	Locations[n].reload.l2.name = "gate_back";
	Locations[n].reload.l2.go = "LeFransua_ExitTown";
	Locations[n].reload.l2.emerge = "reload5";
	Locations[n].reload.l2.autoreload = "1";
	Locations[n].reload.l2.label = "ExitTown";
	locations[n].locators_radius.reload.gate_back = 3;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "LeFransua_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "LeFransua_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l5.name = "reload61";
	locations[n].reload.l5.go = "LeFransua_store";
	locations[n].reload.l5.emerge = "reload3";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Store";
	locations[n].reload.l5.close_for_night = 1;

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "LeFransua_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;

	//Квестовые локации, 9 номеров.
	locations[n].reload.l11.name = "houseH3"; //дом Эдварда Лоу
	locations[n].reload.l11.go = "LeFransua_House4";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l11.autoreload = "0";
	locations[n].reload.l11.label = "Loy_House";

	locations[n].reload.l12.name = "houseK1"; //Дараки
	locations[n].reload.l12.go = "LeFransua_barrack";
	locations[n].reload.l12.emerge = "reload1_back";
	locations[n].reload.l12.label = "House";
	locations[n].reload.l12.close_for_night = 1;

	locations[n].reload.l13.name = "reload5_back"; //Длинный дом
	locations[n].reload.l13.go = "LeFransua_barrack";
	locations[n].reload.l13.emerge = "reload1";
	locations[n].reload.l13.label = "House";
	locations[n].reload.l13.disable = 1; // закроем

	locations[n].reload.l14.name = "houseK3";
	locations[n].reload.l14.go = "LeFransua_Hut1";
	locations[n].reload.l14.emerge = "reload2";
	locations[n].reload.l14.autoreload = "0";
	locations[n].reload.l14.label = "House";

	locations[n].reload.l15.name = "houseK8";
	locations[n].reload.l15.go = "LeFransua_Hut";
	locations[n].reload.l15.emerge = "reload1";
	locations[n].reload.l15.autoreload = "0";
	locations[n].reload.l15.label = "House";

	locations[n].reload.l16.name = "houseK9";
	locations[n].reload.l16.go = "LeFransua_Hut";
	locations[n].reload.l16.emerge = "reload2";
	locations[n].reload.l16.autoreload = "0";
	locations[n].reload.l16.label = "house";

	Locations[n].reload.l17.name = "houseH7";
	Locations[n].reload.l17.go = "LeFransua_MH9_2";
	Locations[n].reload.l17.emerge = "reload1";
	locations[n].reload.l17.autoreload = "0";
	Locations[n].reload.l17.label = "house";

	Locations[n].reload.l18.name = "houseH5";
	Locations[n].reload.l18.go = "LeFransua_PackhouseOffice";
	Locations[n].reload.l18.emerge = "reload1";
	locations[n].reload.l18.autoreload = "0";
	Locations[n].reload.l18.label = "house";

	// --> Комоны, загрушки.
	locations[n].reload.l19.name = "houseK6";
	locations[n].reload.l19.go = "CommonRoom_MH7";
	locations[n].reload.l19.emerge = "reload1";
	locations[n].reload.l19.autoreload = "0";
	locations[n].reload.l19.label = "house";

	locations[n].reload.l20.name = "houseK7";
	locations[n].reload.l20.go = "CommonRoom_MH3";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "house";

	Locations[n].reload.l21.name = "houseH1";
	Locations[n].reload.l21.go = "CommonHut";
	Locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	Locations[n].reload.l21.label = "house";

	Locations[n].reload.l22.name = "houseH2";
	Locations[n].reload.l22.go = "CommonRoom_MH2";
	Locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	Locations[n].reload.l22.label = "house";

	Locations[n].reload.l23.name = "houseH3";
	Locations[n].reload.l23.go = "CommonRoom_MH";
	Locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	Locations[n].reload.l23.label = "house";

	Locations[n].reload.l24.name = "houseH4";
	Locations[n].reload.l24.go = "CommonRoom_MH5";
	Locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	Locations[n].reload.l24.label = "house";	

	Locations[n].reload.l25.name = "houseH6";
	Locations[n].reload.l25.go = "CommonRoom_MH9";
	Locations[n].reload.l25.emerge = "reload1";
	locations[n].reload.l25.autoreload = "0";
	Locations[n].reload.l25.label = "house";

	Locations[n].reload.l26.name = "houseH8";
	Locations[n].reload.l26.go = "CommonDoubleflourHouse_1";
	Locations[n].reload.l26.emerge = "reload1";
	locations[n].reload.l26.autoreload = "0";
	Locations[n].reload.l26.label = "house";

	Locations[n].reload.l27.name = "houseH9";
	Locations[n].reload.l27.go = "CommonStoneHouse";
	Locations[n].reload.l27.emerge = "reload1";
	Locations[n].reload.l27.label = "house";
	locations[n].reload.l27.autoreload = "0";

	locations[n].reload.l28.name = "houseS1";
	locations[n].reload.l28.go = "CommonRoom_MH3";
	locations[n].reload.l28.emerge = "reload1";
	locations[n].reload.l28.autoreload = "0";
	locations[n].reload.l28.label = "house";
	locations[n].reload.l28.disable = 1; // закроем	
	
	Locations[n].reload.l29.name = "housek5";
	Locations[n].reload.l29.go = "CommonStoneHouse";
	Locations[n].reload.l29.emerge = "reload1";
	Locations[n].reload.l29.label = "house";
	locations[n].reload.l29.disable = 1; // заглушка

	locations[n].reload.l30.name = "houseK4";
	locations[n].reload.l30.go = "CommonRoom_MH3";
	locations[n].reload.l30.emerge = "reload1";
	locations[n].reload.l30.autoreload = "0";
	locations[n].reload.l30.label = "house";
	locations[n].reload.l30.disable = 1; // заглушка

	/*locations[n].reload.l31.name = "houseU1";
	locations[n].reload.l31.go = "CommonRoom_MH3";
	locations[n].reload.l31.emerge = "reload1";
	locations[n].reload.l31.autoreload = "0";
	locations[n].reload.l31.label = "house";
	locations[n].reload.l31.disable = 1; // заглушка
	
	locations[n].reload.l32.name = "houseU2";
	locations[n].reload.l32.go = "CommonRoom_MH4";
	locations[n].reload.l32.emerge = "reload1";
	locations[n].reload.l32.autoreload = "0";
	locations[n].reload.l32.label = "house";
	locations[n].reload.l32.disable = 1; // заглушка*/

	locations[n].reload.l33.name = "boat";
	locations[n].reload.l33.go = "Martinique";
	locations[n].reload.l33.emerge = "reload_3";
	locations[n].reload.l33.label = "Sea";
	locations[n].locators_radius.reload.boat = 3.7;
    n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Таверна Ле Франсуа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	locations[n].id = "LeFransua_tavern";
	locations[n].id.label = "Tavern";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "LeFransua";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "LeFransua";
	locations[n].islandId = "Martinique";
	//Models
	locations[n].filespath.models = "locations\inside\Tavern09\";
	//Always
	locations[n].models.always.tavern = "Tavern09";
	locations[n].models.always.locators = "Tavern09_locators";
	locations[n].models.always.window = "tavern09_window";
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
	locations[n].reload.l1.go = "LeFransua_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "LeFransua_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.	
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната в таверне наверху, Ле Франсуа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_tavern_upstairs";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "LeFransua";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LeFransua";
	locations[n].islandId = "Martinique";
	//Models
	locations[n].filespath.models = "locations\inside\Tavern_room";
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
	locations[n].reload.l1.go = "LeFransua_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Магазин Ле Франсуа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_store";
	locations[n].id.label = "Store";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].townsack = "LeFransua";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "LeFransua";
	locations[n].islandId = "Martinique";
	//Models
	locations[n].filespath.models = "locations\inside\Store03\";
	//Always
	locations[n].models.always.locators = "Store03_locators";
	locations[n].models.always.store = "Store03";
	locations[n].models.always.store.level = 65538;
	locations[n].models.always.window = "Store03_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Store03_patch";
	//Night
	locations[n].models.night.charactersPatch = "Store03_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//locations[n].models.back = "back\redms_";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LeFransua_town";
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

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "LeFransua_town";
	locations[n].reload.l3.emerge = "reload61";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Резиденция Ле Франсуа
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_townhall";
	locations[n].id.label = "Townhall";
	locations[n].image = "loading\inside\pirateresidence01.tga";
	//Town sack
	locations[n].townsack = "LeFransua";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "LeFransua";
	locations[n].islandId = "Martinique";
	//Models
	locations[n].filespath.models = "locations\inside\residence_PKM";
	//Always
	locations[n].models.always.locators = "ResP_locators_x";
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
	locations[n].reload.l1.go = "LeFransua_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом Эдварда Лоу
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_House4";
	locations[n].id.label = "Loy_House";
	locations[n].image = "loading\inside\mediumhouse01.tga";
	//Town sack
	locations[n].townsack = "LeFransua";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "LeFransua";
	locations[n].islandId = "Martinique";
	//Models
	locations[n].filespath.models = "locations\inside\mediumhouse01";
	//Always
	locations[n].models.always.mediumhouse01 = "mediumhouse01";
	locations[n].models.always.mediumhouse01.level = 65538;
	locations[n].models.day.locators = "mediumhouse01_locators";
	locations[n].models.night.locators = "mediumhouse01_Nlocators";
	Locations[n].models.always.mediumhouse01windows = "mediumhouse01_windows";
	Locations[n].models.always.mediumhouse01windows.tech = "LocationWindows";
	locations[n].models.always.mediumhouse01windows.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	Locations[n].models.day.mediumhouse01rand= "mediumhouse01_rand";
	locations[n].models.day.charactersPatch = "mediumhouse01_patch";
	//Night
	locations[n].models.night.charactersPatch = "mediumhouse01_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
    //Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LeFransua_town";
	locations[n].reload.l1.emerge = "houseH3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Солдатская казарма
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_barrack";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\mediumhouse01.tga";
	//Town sack
	locations[n].townsack = "LeFransua";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LeFransua";
	locations[n].islandId = "Martinique";
	//Models
	locations[n].filespath.models = "locations\inside\barrack";
	//Always
	locations[n].models.always.locators = "barrack_locators";
	locations[n].models.always.house = "barrack";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "barrack_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "barrack_patch";
	//Night
	locations[n].models.night.charactersPatch = "barrack_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "LeFransua_town";
	locations[n].reload.l1.emerge = "houseK1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Изба рыбака
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_Hut1";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\hibara.tga";
	//Town sack
	locations[n].townsack = "LeFransua";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LeFransua";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LeFransua_town";
	locations[n].reload.l2.emerge = "houseK3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);		
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Хижины на сваях
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_Hut";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\hibara.tga";
	//Town sack
	locations[n].townsack = "LeFransua";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LeFransua";
	locations[n].islandId = "Martinique";
	//Models
	locations[n].filespath.models = "locations\inside\LeFransuaHut";
	//Always
	locations[n].models.always.locators = "Hut_locators";
	locations[n].models.always.house = "Hut";
	locations[n].models.always.house.level = 65538;
	locations[n].models.always.window = "Hut_windows";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	//Day
	locations[n].models.day.charactersPatch = "Hut_patch";
	locations[n].models.day.fonar = "Hut_back_fd";
	//Night
	locations[n].models.night.charactersPatch = "Hut_patch";
	locations[n].models.night.fonar = "Hut_back_fn";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "LeFransua_town";
	locations[n].reload.l1.emerge = "houseK8";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "LeFransua_town";
	locations[n].reload.l2.emerge = "houseK9";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Средний дом 8 (9 с заменённой стенкой)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_MH9_2";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\mediumhouse08.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "LeFransua";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LeFransua";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "LeFransua_town";
	locations[n].reload.l1.emerge = "houseH7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Офис заведующиго пакгаузом
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "LeFransua_PackhouseOffice";
	locations[n].id.label = "PackhouseOffice";
	locations[n].image = "loading\inside\sklad.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "LeFransua";
	locations[n].islandId = "Martinique";
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
	locations[n].reload.l1.go = "LeFransua_town";
	locations[n].reload.l1.emerge = "houseH5";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);

	n = n + 1;

	return n;
}

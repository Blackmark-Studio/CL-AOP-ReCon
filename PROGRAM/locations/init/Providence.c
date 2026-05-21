
int LocationInitProvidence(int n)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ГОРОД
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_town";
	locations[n].id.label = "Street";
	locations[n].worldmap = "Providence";
	
	locations[n].townsack = "Providencia";
	locations[n].fastreload = "Providencia";
	locations[n].islandId = "Providence";
	
	locations[n].filespath.models = "locations\Town_Providencia\Town\";
	locations[n].image = "loading\towns\piratebay.tga";
	locations[n].citizens = true;
	locations[n].soldiers = true;
	locations[n].carrier = true;
	//==> флаг генерации квестодателя по розыску кэпов, int значение - шанс что сам заговорит(1-10)
	//locations[n].questSeekCap = 7;
	
	//Sound
	locations[n].type = "town";
	LAi_LocationFantomsGen(&locations[n], true);
	locations[n].houseEnc = true; //для энкаунтеров в домах
	//Models
	//Always
	locations[n].models.always.town = "Providencia";
	locations[n].models.always.town.tech = "DLightModel";
	locations[n].models.always.town.sea_reflection = 1;
	locations[n].models.always.seabed = "Providencia_sb";
	locations[n].models.always.seabed.tech = "DLightModel";
	locations[n].models.always.locators = "Providencia_locators";
	locations[n].models.always.L1 = "Providencia_signsA";
	locations[n].models.always.L1.tech = "DLightModel";
	locations[n].models.always.grassPatch = "Providencia_grass";
	locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";	
	locations[n].models.always.plan = "plan1";
	locations[n].models.always.plan.tech = "DLightModel";
	locations[n].models.always.plan.level = 9;

	//Day
	
	locations[n].models.day.fonar = "Providencia_fd";
	locations[n].models.day.fonar.tech = "DLightModel";
	locations[n].models.day.charactersPatch = "Providencia_patch_day";
	locations[n].models.day.rinok.tech = "DLightModel";
	locations[n].models.day.rinok = "Providencia_rinok";
	//Night
	locations[n].models.night.fonar = "Providencia_fn";
	locations[n].models.night.fonar.tech = "DLightModel";
	locations[n].models.night.charactersPatch = "Providencia_patch_night";
	locations[n].models.night.locatorsL3 = "Providencia_gate";
	locations[n].models.night.locatorsL3.tech = "DLightModel";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map

    // --> Типовые городские локации, четкая фиксация на 10 номеров.
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Providence";
	locations[n].reload.l1.emerge = "reload_1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Sea";
	locations[n].locators_radius.reload.reload1_back = 1.8;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Providence";
	locations[n].reload.l2.emerge = "reload_1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.reload2_back = 1.8;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Providencia_townhall";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Residence";
	locations[n].reload.l3.close_for_night = 1;

	locations[n].reload.l4.name = "reload4_back";
	locations[n].reload.l4.go = "Providencia_tavern";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Tavern";

	locations[n].reload.l5.name = "reload5_back";
	locations[n].reload.l5.go = "Providencia_shipyard";
	locations[n].reload.l5.emerge = "reload1";
	locations[n].reload.l5.autoreload = "0";
	locations[n].reload.l5.label = "Shipyard";
	locations[n].reload.l5.close_for_night = 1;
	locations[n].reload.l5.disable  = true; //Закрыто, типа там ещё много всякого, но нас туды не пускают

	locations[n].reload.l6.name = "reload6_back";
	locations[n].reload.l6.go = "Providencia_store";
	locations[n].reload.l6.emerge = "reload1";
	locations[n].reload.l6.autoreload = "0";
	locations[n].reload.l6.label = "Store";
	locations[n].reload.l6.close_for_night = 1;

	locations[n].reload.l7.name = "reload9_back";
	locations[n].reload.l7.go = "Providencia_brothel";
	locations[n].reload.l7.emerge = "reload1";
	locations[n].reload.l7.autoreload = "0";
	locations[n].reload.l7.label = "Brothel";

	locations[n].reload.l8.name = "reloadSk";
	locations[n].reload.l8.go = "Providencia_sklad02"; //склад-хранилище
	locations[n].reload.l8.emerge = "reload1";
	locations[n].reload.l8.autoreload = "0";
	locations[n].reload.l8.label = "sklad";

	locations[n].reload.lgate.name = "gate1";
	locations[n].reload.lgate.go = "Providencia_ExitTown";
	locations[n].reload.lgate.emerge = "reload3";
	locations[n].reload.lgate.autoreload = "1";
	locations[n].reload.lgate.label = "ExitTown";
	locations[n].locators_radius.reload.gate1 = 3;

    // --> Квестовые локации.
	locations[n].reload.l9.name = "reload10_back";
	locations[n].reload.l9.go = "Providencia_PortOffice";
	locations[n].reload.l9.emerge = "reload1";
	locations[n].reload.l9.autoreload = "0";
	locations[n].reload.l9.label = "PortOffice";
	locations[n].reload.l9.close_for_night = 1;
	
	// барахольщик
	locations[n].reload.l10.name = "reload8_back";
	locations[n].reload.l10.go = "Providencia_Hoarder";
	locations[n].reload.l10.emerge = "reload1";
	locations[n].reload.l10.autoreload = "0";
	locations[n].reload.l10.label = "House Hoarder";
	locations[n].reload.l10.close_for_night = 1;
	
	//бывшая церковь
	locations[n].reload.l11.name = "reload7_back";
	locations[n].reload.l11.go = "Providencia_Monah";
	locations[n].reload.l11.emerge = "reload1";
	locations[n].reload.l11.autoreload = "0";
	locations[n].reload.l11.label = "House";
	locations[n].reload.l11.disable  = true;
	//locations[n].reload.l7.close_for_night = 1;
	
	locations[n].reload.l12.name = "houseV1";
	locations[n].reload.l12.go = "Providencia_HouseHut2";
	locations[n].reload.l12.emerge = "reload1";
	locations[n].reload.l12.autoreload = "0";
	locations[n].reload.l12.label = "House";
	locations[n].reload.l12.disable = 1; // закроем

	locations[n].reload.l13.name = "houseV2";
	locations[n].reload.l13.go = "Providencia_HouseHut2";
	locations[n].reload.l13.emerge = "reload1";
	locations[n].reload.l13.autoreload = "0";
	locations[n].reload.l13.label = "House";
	locations[n].reload.l13.disable = 1; // закроем

	locations[n].reload.l14.name = "houseS2";
	locations[n].reload.l14.go = "Providencia_HouseSp2";
	locations[n].reload.l14.emerge = "reload1";
	locations[n].reload.l14.autoreload = "0";
	locations[n].reload.l14.label = "House";
	locations[n].reload.l14.close_for_night = 1;

	locations[n].reload.l15.name = "houseD1";
	locations[n].reload.l15.go = "Providencia_HouseHut";
	locations[n].reload.l15.emerge = "reload2";
	locations[n].reload.l15.autoreload = "0";
	locations[n].reload.l15.label = "House";
	locations[n].reload.l15.close_for_night = 1;

	locations[n].reload.l16.name = "houseD2";
	locations[n].reload.l16.go = "Providencia_HouseHut";
	locations[n].reload.l16.emerge = "reload1";
	locations[n].reload.l16.autoreload = "0";
	locations[n].reload.l16.label = "House";
	locations[n].reload.l16.close_for_night = 1;

	locations[n].reload.l17.name = "houseH5";
	locations[n].reload.l17.go = "Providencia_Hut3_Kns";
	locations[n].reload.l17.emerge = "reload1";
	locations[n].reload.l17.autoreload = "0";
	locations[n].reload.l17.label = "House";
	locations[n].reload.l17.close_for_night = 1;

	locations[n].reload.l18.name = "houseV4";
	locations[n].reload.l18.go = "Providencia_HouseHut1";
	locations[n].reload.l18.emerge = "reload1";
	locations[n].reload.l18.autoreload = "0";
	locations[n].reload.l18.label = "House";
	locations[n].reload.l18.close_for_night = 1;

	locations[n].reload.l19.name = "houseS1";
	locations[n].reload.l19.go = "Providencia_CobHouse";
	locations[n].reload.l19.emerge = "reload1";
	locations[n].reload.l19.autoreload = "0";
	locations[n].reload.l19.label = "House";
	
    // --> Комоны, загрушки. Номера с начинаются с 20.
	locations[n].reload.l20.name = "houseF4";
	locations[n].reload.l20.go = "CommonRoom_MH3";
	locations[n].reload.l20.emerge = "reload1";
	locations[n].reload.l20.autoreload = "0";
	locations[n].reload.l20.label = "House";

	locations[n].reload.l21.name = "houseSp2";
	locations[n].reload.l21.go = "CommonStoneHouse";
	locations[n].reload.l21.emerge = "reload1";
	locations[n].reload.l21.autoreload = "0";
	locations[n].reload.l21.label = "House";

	locations[n].reload.l22.name = "houseH3";
	locations[n].reload.l22.go = "CommonRoom_MH";
	locations[n].reload.l22.emerge = "reload1";
	locations[n].reload.l22.autoreload = "0";
	locations[n].reload.l22.label = "House";

	locations[n].reload.l23.name = "houseF1";
	locations[n].reload.l23.go = "CommonRoom_MH9";
	locations[n].reload.l23.emerge = "reload1";
	locations[n].reload.l23.autoreload = "0";
	locations[n].reload.l23.label = "House";

	locations[n].reload.l24.name = "houseF2";
	locations[n].reload.l24.go = "CommonRoom_MH4";
	locations[n].reload.l24.emerge = "reload1";
	locations[n].reload.l24.autoreload = "0";
	locations[n].reload.l24.label = "House";
     // <--
	locations[n].reload.l25.name = "boat";
	locations[n].reload.l25.go = "Providence";
	locations[n].reload.l25.emerge = "reload_1";
	locations[n].reload.l25.autoreload = "0";
	locations[n].reload.l25.label = "Sea";
	locations[n].locators_radius.reload.boat = 3.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// ТАВЕРНА
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_tavern";
	locations[n].id.label = "Tavern";
	locations[n].filespath.models = "locations\inside\tavern05\";
	locations[n].image = "loading\inside\tavern.tga";
	locations[n].habitues = 1;
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "tavern";
	locations[n].fastreload = "Providencia";
	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].models.always.tavern = "tavern05";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.nobsp = "tavern05NB";
	locations[n].models.always.locators = "tavern05_locators";
	locations[n].models.always.window = "tavern05_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "tavern05_patch";
	//Night
	locations[n].models.night.charactersPatch = "tavern05_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "reload4";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Providencia_tavern_upstairs";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Tavern upstairs";
	locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;
				
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// КОМНАТА В ТАВЕРНЕ НАВЕРХУ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_tavern_upstairs";
	locations[n].id.label = "Tavern upstairs";
	locations[n].image = "loading\inside\tavern.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providencia_tavern";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Tavern";
	locations[n].locators_radius.reload.reload1 = 0.8;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////
	// Резиденция
	//////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_townhall";
	locations[n].id.label = "Townhall";
	locations[n].image = "loading\inside\smallresidence.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "residence";
	locations[n].fastreload = "Providencia";
	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	locations[n].locators_radius.box.box1 = 1.4;
    locations[n].locators_radius.randitem.randitem1 = 1.0;
    locations[n].locators_radius.item.item1 = 1.0;
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// МАГАЗИН
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_store";
	locations[n].id.label = "Store";
	locations[n].filespath.models = "locations\inside\Store03\";
	locations[n].image = "loading\inside\shop.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shop";
	locations[n].fastreload = "Providencia";
	locations[n].islandId = "Providence";
	//Models
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
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Providencia_town";
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
	// ВЕРФЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_Shipyard";
	locations[n].id.label = "Shipyard";
	locations[n].filespath.models = "locations\inside\Shipyard02\";
	locations[n].image = "loading\inside\shipyard.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "Providencia";
	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].models.always.locators = "Shipyard02_locators";
	locations[n].models.always.shipyard = "Shipyard02";
	locations[n].models.always.shipyard.level = 65538;
	locations[n].models.always.window = "shipyard02_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Shipyard02_patch";
	//Night
	locations[n].models.night.charactersPatch = "Shipyard02_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "reload5";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Providencia_Packhouse";
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
	locations[n].id = "Providencia_Packhouse";
	locations[n].id.label = "Packhouse";
	locations[n].image = "loading\inside\sklad.tga";
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "shipyard";
	locations[n].fastreload = "Providencia";
 	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providencia_Shipyard";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Shipyard";
	
	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Providencia_PackhouseOffice";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "PackhouseOffice";
	locations[n].reload.l2.close_for_night = 1;
	n = n + 1;
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Офис заведующиго пакгаузом
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_PackhouseOffice";
	locations[n].id.label = "PackhouseOffice";
	locations[n].image = "loading\inside\sklad.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providencia_Packhouse";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Packhouse";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// БОРДЕЛЬ
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_Brothel";
	locations[n].id.label = "Brothel";
	locations[n].filespath.models = "locations\inside\Brothel\";
	locations[n].image = "loading\inside\brothell_hall.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "reload9";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Providencia_Brothel_room";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Brothel Room";
	locations[n].reload.l2.disable = 1;  //закроем, но связка пусть будет для квестов.

	locations[n].reload.l3.name = "reload3";
	locations[n].reload.l3.go = "Providencia_SecBrRoom";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комнаты в борделе наверху
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_Brothel_room";
	locations[n].id.label = "Brothel Room";
	locations[n].filespath.models = "locations\inside\Brothel_room\";
	locations[n].image = "loading\inside\brothell_room.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
 	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providencia_Brothel";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";
	LAi_LocationFightDisable(&locations[n], true);
	locations[n].locators_radius.item.item1 = 1;
	n = n + 1;
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Комната бордельмаман
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_SecBrRoom";
	locations[n].id.label = "Room";
	locations[n].image = "loading\inside\Residence07.tga";
 	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
 	locations[n].islandId = "Providence";
	locations[n].brothel = true;
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Residence07";
	locations[n].models.always.locators = "Res07_l";
	locations[n].models.always.l1 = "Res07";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.window = "Res07_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;	
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "Res07_p";
	//Night
	locations[n].models.night.charactersPatch = "Res07_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Providencia_Brothel";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Brothel";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом монаха
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_monah";
	locations[n].id.label = "House";
	locations[n].image = "loading\jonny_load\inside\church_IM.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "church";
	locations[n].fastreload = "Providencia";
	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "reload7";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Graveyard";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом барахольщика
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_Hoarder";
	locations[n].id.label = "House Hoarder";
	locations[n].image = "loading\inside\barahol.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
 	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\Pirate_House";
	locations[n].models.always.locators = "PirH_l";
	locations[n].models.always.tavern = "PirH";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "PirH_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "PirH_p";
	//Night
	locations[n].models.night.charactersPatch = "PirH_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l2.name = "reload1";
	locations[n].reload.l2.go = "Providencia_town";
	locations[n].reload.l2.emerge = "reload8";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Портовый офис
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_PortOffice";
	locations[n].id.label = "PortOffice";
	locations[n].image = "loading\inside\portoffice.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "reload10";
	locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
	LAi_LocationFightDisable(&locations[n], true);
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Дом с подвалом
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_HouseSp2";
	locations[n].filespath.models = "locations\inside\FlamHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\flamhouse.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
 	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "houseS2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload3";
	locations[n].reload.l2.go = "CommonRoom_MH3";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";

	locations[n].reload.l3.name = "reload4";
	locations[n].reload.l3.go = "CommonRoom_MH4";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "0";
	locations[n].reload.l3.label = "Room";

	locations[n].reload.l4.name = "reload2";
	locations[n].reload.l4.go = "Providencia_Cave";
	locations[n].reload.l4.emerge = "reload1";
	locations[n].reload.l4.autoreload = "0";
	locations[n].reload.l4.label = "Street";
	locations[n].reload.l4.disable = 1; // закроем
	n = n + 1;

  	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Хижина с двумя входами
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_HouseHut";
	locations[n].filespath.models = "locations\inside\Hut";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\hut.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
 	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "houseD2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Providencia_town";
	locations[n].reload.l2.emerge = "houseD1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Хижина с камином
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_Hut3_Kns";
	locations[n].filespath.models = "locations\inside\Hut3";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\Hut3.tga";
	locations[n].MustSetReloadBack = true;
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
 	locations[n].islandId = "Providence";
	//Models
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
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "houseH5";
	locations[n].reload.l1.autoreload = "Hut3";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Изба рыбака
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_HouseHut1";
	locations[n].filespath.models = "locations\inside\Hut1_KNS";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\littlehut.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
 	locations[n].islandId = "Providence";
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
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l2.name = "reload1";
	locations[n].reload.l2.go = "Providencia_town";
	locations[n].reload.l2.emerge = "houseV4";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Большой дом
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_CobHouse";
	locations[n].filespath.models = "locations\inside\CobHouse";
	locations[n].id.label = "House";
	locations[n].image = "loading\inside\CobHouse.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
 	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].models.always.tavern = "CobHouse";
	locations[n].models.always.tavern.level = 65538;
	locations[n].models.always.window = "CobHouse_window";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;
	locations[n].models.day.locators = "CobHouse_locators";
	locations[n].models.night.locators = "CobHouse_Nlocators";

	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "CobHouse_patch";
	//Night
	locations[n].models.night.charactersPatch = "CobHouse_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "houseS1";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";

	locations[n].reload.l2.name = "reload2";
	locations[n].reload.l2.go = "Providencia_BedRoomK2";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Room";
	n = n + 1;

 	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Спальня резиденции (ПКМ)
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_BedRoomK2";
	locations[n].id.label = "BedRoom";
	locations[n].image = "loading\inside\bedroom.tga";
	locations[n].Bedroom = true;
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
 	locations[n].islandId = "Providence";
 	// стража
	locations[n].soldiers = true;
	LAi_LocationFantomsGen(&locations[n], true);
	//Models
	locations[n].filespath.models = "locations\inside\ResBedRoom";
	//Always
	locations[n].models.always.locators = "bed_l";
	locations[n].models.always.l1 = "bed";
	locations[n].models.always.l1.level = 65538;
	locations[n].models.always.window = "bed_w";
	locations[n].models.always.window.tech = "LocationWindows";
	locations[n].models.always.window.level = 65539;	
	locations[n].models.always.back = "..\inside_back";
	locations[n].models.always.back.level = 65529;
	//Day
	locations[n].models.day.charactersPatch = "bed_p";
	//Night
	locations[n].models.night.charactersPatch = "bed_p";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Providencia_CobHouse";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Townhall";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Склад 02 не имеет отношение к магазину. ККС
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_sklad02";
	locations[n].id.label = "packhouse";
	locations[n].image = "loading\inside\Sklad.tga";
	locations[n].MustSetReloadBack = true;
	locations[n].packhouse = true;
	//Town sack
	locations[n].townsack = "Providencia";
	locations[n].lockWeather = "Inside";
	//Sound
	locations[n].type = "house";
	locations[n].fastreload = "Providencia";
	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "reloadSk";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Street";
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Выход из города
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providencia_ExitTown";
	locations[n].fastreload = "Providencia";
	locations[n].id.label = "ExitTown";
	locations[n].image = "loading\outside\Jungle.tga";
	//Town sack
	locations[n].townsack = "Providencia";
	//Sound
	locations[n].type = "jungle";
 	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle3";
	Locations[n].models.always.jungle = "jungle3";
	Locations[n].models.always.locators = "jungle3_locators";
	Locations[n].models.always.grassPatch = "jungle3_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grass.tga.tx";	
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
	locations[n].models.day.charactersPatch = "jungle3_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle3_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";

	//Reload map
	locations[n].reload.l1.name = "reload3_back";
	locations[n].reload.l1.go = "Providencia_town";
	locations[n].reload.l1.emerge = "gate_back";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Providencia_town";
	locations[n].locators_radius.reload.reload3_back = 2.0;

	locations[n].reload.l2.name = "reload1_back";
	locations[n].reload.l2.go = "Providence_jungle_01";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;

	locations[n].reload.l3.name = "reload2_back";
	locations[n].reload.l3.go = "Providencia_fort";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли Южные
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providence_Jungle_01";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\Jungle4";
	Locations[n].models.always.jungle = "jungle4";	
	Locations[n].models.always.locators = "jungle4_locators";		
	Locations[n].models.always.grassPatch = "jungle4_grass";
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
	locations[n].models.day.charactersPatch = "jungle4_patch";
	//Night
	locations[n].models.night.charactersPatch = "jungle4_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Providencia_ExitTown";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "ExitTown";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Providence_deadlock";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Cave";
	locations[n].locators_radius.reload.reload2_back = 2;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Providence_jungle_02";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "Jungle";
	locations[n].locators_radius.reload.reload3_back = 3;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли Тупиковые
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providence_deadlock";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Jungles\jungle9\";
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
	locations[n].reload.l1.go = "Providence_jungle_01";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2.2;

	/*locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore66";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload2_back = 2.0;*/
	n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Бухта
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*locations[n].id = "Shore66";
	locations[n].id.label = "Shore66";
	locations[n].image = "loading\outside\harbor.tga";
	locations[n].worldmap = "Shore66";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore02";
	Locations[n].models.always.shore02 = "shore02";
	locations[n].models.always.shore02.sea_reflection = 1;
	Locations[n].models.always.shore02seabed = "shore02_sb";
	Locations[n].models.always.locators = "shore02_locators";
		
	Locations[n].models.always.grassPatch = "shore02_grass";
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
	locations[n].models.day.charactersPatch = "shore02_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore02_patch";		
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Providence_deadlock";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Providence";
	locations[n].reload.l2.emerge = "reload_3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;*/

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Сквозная пещера
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providence_Cavern";
	locations[n].id.label = "Cave";
	locations[n].image = "loading\inside\Cave.tga";
	//Sound
	locations[n].type = "cave";
 	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].filespath.models = "locations\inside\cavernLow1";
	locations[n].models.always.cavernLow1 = "cavernLow1";

	locations[n].models.always.cavernLow1Lamps = "cavernLow1_lamps";
	locations[n].models.always.cavernLow1Crystals = "cavernLow1_crystals";
	locations[n].models.always.cavernLow1Crystals.tech = "EnvironmentShader";
	locations[n].models.always.cavernLow1Crystals.reflection = 0.25;

	locations[n].models.always.Waterfall = "water";
	locations[n].models.always.Waterfall.uvslide.v0 = 0.0;
	locations[n].models.always.Waterfall.uvslide.v1 = 0.0;
	locations[n].models.always.Waterfall.tech = "LocationWaterFall";
	locations[n].models.always.Waterfall.level = 51;

	locations[n].models.always.Cfall = "cfall";
	locations[n].models.always.Cfall.uvslide.v0 = 0.3;
    locations[n].models.always.Cfall.uvslide.v1 = 0.0;
	locations[n].models.always.Cfall.tech = "LocationWaterFall";
	locations[n].models.always.Cfall.level = 50;

	locations[n].models.always.locators = "cavernLow1_locators";

	locations[n].locators_radius.item.duhi1 = 0.0;

	//Day
	locations[n].models.day.charactersPatch = "cavernLow1_patch";
	//Night
	locations[n].models.night.charactersPatch = "cavernLow1_patch";
	//Environment
	locations[n].environment.weather = "true";
	Locations[n].lockWeather = "Inside";
	Locations[n].QuestlockWeather = "23 Hour";
	locations[n].environment.sea = "false";
	locations[n].environment.weather.rain = false;
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Shore65";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Shore65";
	
	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Providencia_fort";
	locations[n].reload.l2.emerge = "reload3_back";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	Locations[n].DisableEncounters = true;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Серпантин - Мыс Моргана
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	Locations[n].id = "Shore65";
	locations[n].id.label = "Shore65";
	Locations[n].image = "loading\outside\harbor.tga";
	locations[n].worldmap = "Shore65";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Serpentine";
	Locations[n].models.always.Serpentine = "pass1";
	locations[n].models.always.Serpentine.sea_reflection = 1;
	Locations[n].models.always.seabed = "pass1_sb";
	Locations[n].models.always.locators = "pass1_locators";
	Locations[n].models.always.grassPatch = "pass1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

	//Day
	locations[n].models.day.charactersPatch = "pass1_patch";
	//Night
	locations[n].models.night.charactersPatch = "pass1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Providence_Cavern";
	locations[n].reload.l1.emerge = "reload1";
	locations[n].reload.l1.autoreload = 1;
	locations[n].reload.l1.label = "cave";
	locations[n].locators_radius.reload.reload1_back = 2.0;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Providence";
	locations[n].reload.l2.emerge = "reload_3";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
	locations[n].locators_radius.reload.boat = 5.0;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Джунгли Северные
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providence_jungle_02";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Providence";
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
	locations[n].reload.l1.go = "Providence_jungle_01";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.Reload1_back = 2.0;

	locations[n].reload.l2.name = "reload2_back";
	locations[n].reload.l2.go = "Shore64";
	locations[n].reload.l2.emerge = "reload1";
	locations[n].reload.l2.autoreload = "1";
	locations[n].reload.l2.label = "Shore6";
	locations[n].locators_radius.reload.Reload2_back = 2.0;

	locations[n].reload.l3.name = "reload3_back";
	locations[n].reload.l3.go = "Providence_Ruins";
	locations[n].reload.l3.emerge = "reload1";
	locations[n].reload.l3.autoreload = "1";
	locations[n].reload.l3.label = "4Cave entrance";
	locations[n].locators_radius.reload.Reload3_back = 2.0;
	n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Руины в джунглях
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Providence_Ruins";
	locations[n].id.label = "Jungle";
	locations[n].image = "loading\outside\jungle.tga";
	//Sound
	locations[n].type = "jungle";
	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Ruins";
	Locations[n].models.always.ruins1 = "ruins1";
	Locations[n].models.always.locators = "ruins1_locators";

	Locations[n].models.always.grassPatch = "ruins1_grass";
	Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";

	locations[n].models.always.ruins1_blockade = "ruins1_blockade";
	Locations[n].models.always.ruins1_blockade.locator.group = "Upgrades";
	Locations[n].models.always.ruins1_blockade.locator.name = "ruins1_blockade";
	Locations[n].models.always.ruins1_blockade.tech = "DLightModel";

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
	locations[n].models.day.charactersPatch = "ruins1_patch";
	//Night
	locations[n].models.night.charactersPatch = "ruins1_patch";
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "false";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Providence_Jungle_02";
	locations[n].reload.l1.emerge = "reload3";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;
	n = n + 1;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//  Пляж Мансанильо
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	locations[n].id = "Shore64";
	locations[n].id.label = "Shore64";
	locations[n].image = "loading\outside\harbor.tga";
	locations[n].worldmap = "Shore64";
	//Sound
	locations[n].type = "seashore";
	locations[n].islandId = "Providence";
	//Models
	//Always
	locations[n].filespath.models = "locations\Outside\Shores\Shore01";
	Locations[n].models.always.shore01 = "shore01";
	locations[n].models.always.shore01.sea_reflection = 1;
	Locations[n].models.always.shore01seabed = "shore01_sb";
	Locations[n].models.always.locators = "shore01_locators";

	Locations[n].models.always.grassPatch = "shore01_grass";
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
	locations[n].models.day.charactersPatch = "shore01_patch";
	//Night
	locations[n].models.night.charactersPatch = "shore01_patch";	
	//Environment
	locations[n].environment.weather = "true";
	locations[n].environment.sea = "true";
	//Reload map
	locations[n].reload.l1.name = "reload1_back";
	locations[n].reload.l1.go = "Providence_Jungle_02";
	locations[n].reload.l1.emerge = "reload2";
	locations[n].reload.l1.autoreload = "1";
	locations[n].reload.l1.label = "Jungle";
	locations[n].locators_radius.reload.reload1_back = 2;

	locations[n].reload.l2.name = "boat";
	locations[n].reload.l2.go = "Providence";
	locations[n].reload.l2.emerge = "reload_2";
	locations[n].reload.l2.autoreload = "0";
	locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
	n = n + 1;

	return n;
}

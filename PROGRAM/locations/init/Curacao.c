int LocationInitCuracao(int n)
{

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ГОРОД (Nikk)
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_town";
    locations[n].id.label = "Street";
    locations[n].worldmap = "Curacao";

    locations[n].townsack = "Villemstad";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";

    locations[n].image = "loading\Town.tga";
    locations[n].citizens = true;
    locations[n].soldiers = true;
    locations[n].carrier = true;
    //==> флаг генерации квестодателя по розыску кэпов, int значение - шанс что сам заговорит(1-10)
    locations[n].questSeekCap = 7;
    //Sound
    locations[n].type = "town";
    LAi_LocationFantomsGen(&locations[n], true);
    locations[n].houseEnc = true; //для энкаунтеров в домах
    //Models
    locations[n].filespath.models = "locations\Town_Villemstad\Town\";
    //Always
    locations[n].models.always.town = "Villemstad";
    locations[n].models.always.town.sea_reflection = 1;
    locations[n].models.always.L1 = "Villemstad_palms";
    locations[n].models.always.L2 = "Villemstad_flora";
    locations[n].models.always.locators = "Villemstad_locators";
    locations[n].models.always.seabed = "Villemstad_sb";
    locations[n].models.always.grassPatch = "Villemstad_grass";
    locations[n].models.always.plan = "plan1";

    //WindMill Fan
    locations[n].models.always.MillFan = "MillFan";
    Locations[n].models.always.MillFan.locator.group = "WindMill";
    Locations[n].models.always.MillFan.locator.name = "Fan";
    Locations[n].models.always.MillFan.rotate.x = 0.0;
    Locations[n].models.always.MillFan.rotate.y = 0.0;
    Locations[n].models.always.MillFan.rotate.z = 0.1;

    //Day
    locations[n].models.day.fonar = "Villemstad_fd";
    locations[n].models.day.charactersPatch = "Villemstad_patch_day";
    locations[n].models.day.rinok = "Villemstad_rinok";
    Locations[n].models.day.jumpPatch = "Villemstad_jump";
    //Night
    locations[n].models.night.fonar = "Villemstad_fn";
    locations[n].models.night.charactersPatch = "Villemstad_patch_night";
    locations[n].models.night.rinok = "Villemstad_rinokN";
    Locations[n].models.night.jumpPatch = "Villemstad_jump";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "true";
    //Reload map

    // --> Типовые городские локации, четкая фиксация на 10 номеров.
    locations[n].reload.l1.name = "reload1_back";
    locations[n].reload.l1.go = "Curacao";
    locations[n].reload.l1.emerge = "reload_1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Sea";
    locations[n].locators_radius.reload.reload1_back = 4.0;

    locations[n].reload.l2.name = "reload2_back";
    locations[n].reload.l2.go = "Curacao";
    locations[n].reload.l2.emerge = "reload_1";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.reload2_back = 7.0;

    locations[n].reload.l3.name = "reload3_back";
    locations[n].reload.l3.go = "Villemstad_hall";
    locations[n].reload.l3.emerge = "reload1";
    locations[n].reload.l3.autoreload = "0";
    locations[n].reload.l3.label = "Residence";
    locations[n].reload.l3.close_for_night = 1;

    locations[n].reload.l301.name = "reloadR2";
    locations[n].reload.l301.go = "Villemstad_hall";
    locations[n].reload.l301.emerge = "reload2";
    locations[n].reload.l301.autoreload = "0";
    locations[n].reload.l301.label = "Residence";

    locations[n].reload.l4.name = "reload4_back";
    locations[n].reload.l4.go = "Villemstad_tavern";
    locations[n].reload.l4.emerge = "reload1";
    locations[n].reload.l4.autoreload = "0";
    locations[n].reload.l4.label = "Tavern";

    locations[n].reload.l5.name = "reload5_back";
    locations[n].reload.l5.go = "Villemstad_shipyard";
    locations[n].reload.l5.emerge = "reload1";
    locations[n].reload.l5.autoreload = "0";
    locations[n].reload.l5.label = "Shipyard";
    locations[n].reload.l5.close_for_night = 1;

    locations[n].reload.l6.name = "reload6_back";
    locations[n].reload.l6.go = "Villemstad_store";
    locations[n].reload.l6.emerge = "reload1";
    locations[n].reload.l6.autoreload = "0";
    locations[n].reload.l6.label = "Store";
    locations[n].reload.l6.close_for_night = 1;

    locations[n].reload.l7.name = "reload7_back";
    locations[n].reload.l7.go = "Villemstad_church";
    locations[n].reload.l7.emerge = "reload1";
    locations[n].reload.l7.autoreload = "0";
    locations[n].reload.l7.label = "Church";

    locations[n].reload.l8.name = "reload8_back";
    locations[n].reload.l8.go = "Villemstad_bank";
    locations[n].reload.l8.emerge = "reload1";
    locations[n].reload.l8.autoreload = "0";
    locations[n].reload.l8.label = "Usurer House";
    locations[n].reload.l8.close_for_night = 1;

    locations[n].reload.l9.name = "reload9_back";
    locations[n].reload.l9.go = "Villemstad_brothel";
    locations[n].reload.l9.emerge = "reload1";
    locations[n].reload.l9.autoreload = "0";
    locations[n].reload.l9.label = "Brothel";

    locations[n].reload.l91.name = "reload91";
    locations[n].reload.l91.go = "Villemstad_SecBrRoom";
    locations[n].reload.l91.emerge = "reload2";
    locations[n].reload.l91.autoreload = "0";
    locations[n].reload.l91.label = "Brothel";

    locations[n].reload.l10.name = "reload10_back";
    locations[n].reload.l10.go = "Villemstad_PortOffice";
    locations[n].reload.l10.emerge = "reload1";
    locations[n].reload.l10.autoreload = "0";
    locations[n].reload.l10.label = "PortOffice";
    locations[n].reload.l10.close_for_night = 1;

    locations[n].reload.gate.name = "gate";
    locations[n].reload.gate.go = "Villemstad_ExitTown";
    locations[n].reload.gate.emerge = "reload4";
    locations[n].reload.gate.autoreload = "1";
    locations[n].reload.gate.label = "ExitTown";
    locations[n].locators_radius.reload.gate = 3.0;

    locations[n].reload.jail.name = "HouseT1";
    locations[n].reload.jail.go = "Villemstad_prison";
    locations[n].reload.jail.emerge = "reload1";
    locations[n].reload.jail.autoreload = "0";
    locations[n].reload.jail.label = "Prison";

    locations[n].reload.gate2.name = "reload33";
    locations[n].reload.gate2.go = "Curacao_jungle_04";
    locations[n].reload.gate2.emerge = "reload1";
    locations[n].reload.gate2.autoreload = "1";
    locations[n].reload.gate2.label = "Plantation";
    locations[n].locators_radius.reload.reload33 = 2.0;

    // --> Штаб квартира ГВИК
    locations[n].reload.l11.name = "HouseO1";
    locations[n].reload.l11.go = "GVIK";
    locations[n].reload.l11.emerge = "reload1";
    locations[n].reload.l11.autoreload = "0";
    locations[n].reload.l11.label = "GWIKshort";
    locations[n].reload.l11.close_for_night = 1;

    locations[n].reload.l12.name = "HouseO2";
    locations[n].reload.l12.go = "GVIK";
    locations[n].reload.l12.emerge = "reload2";
    locations[n].reload.l12.autoreload = "0";
    locations[n].reload.l12.label = "GWIKshort";
    locations[n].reload.l12.close_for_night = 1;

    // --> Квестовые локации.
    locations[n].reload.l13.name = "reloadR1"; //дом Аарона Мендеса Чумакейро
    locations[n].reload.l13.go = "Villemstad_houseS3";
    locations[n].reload.l13.emerge = "reload1";
    locations[n].reload.l13.autoreload = "0";
    locations[n].reload.l13.label = "Aaron's House";
    locations[n].reload.l13.close_for_night = 1;

    locations[n].reload.l14.name = "houseS1"; //дом мастера ключей
    locations[n].reload.l14.go = "Villemstad_houseSp5";
    locations[n].reload.l14.emerge = "reload1";
    locations[n].reload.l14.autoreload = "0";
    locations[n].reload.l14.label = "House";

    locations[n].reload.l15.name = "houseFa1"; //Аптека вход со двора
    locations[n].reload.l15.go = "Farmacia";
    locations[n].reload.l15.emerge = "reload1";
    locations[n].reload.l15.autoreload = "0";
    locations[n].reload.l15.label = "House";
    locations[n].reload.l15.disable = false;

    locations[n].reload.l16.name = "houseFa2"; //Аптека вход с улицы
    locations[n].reload.l16.go = "Farmacia";
    locations[n].reload.l16.emerge = "reload2";
    locations[n].reload.l16.autoreload = "0";
    locations[n].reload.l16.label = "House";
    locations[n].reload.l16.disable = 1; //закрыто

    locations[n].reload.l17.name = "houseK2"; //Хижина больного
    locations[n].reload.l17.go = "Smallhome_K2";
    locations[n].reload.l17.emerge = "reload1";
    locations[n].reload.l17.autoreload = "0";
    locations[n].reload.l17.label = "House";

    // --> Псевдоквестовые локации. (Можно юзать по новым квестам, но там где закрыто, не открывать. Это дома клоны)
    locations[n].reload.l18.name = "houseH3";
    locations[n].reload.l18.go = "Vil_Hut";
    locations[n].reload.l18.emerge = "reload1";
    locations[n].reload.l18.autoreload = "0";
    locations[n].reload.l18.label = "House";

    locations[n].reload.l19.name = "houseH4";
    locations[n].reload.l19.go = "Vil_Hut";
    locations[n].reload.l19.emerge = "reload2";
    locations[n].reload.l19.autoreload = "0";
    locations[n].reload.l19.label = "House";

    locations[n].reload.l20.name = "Hut3";
    locations[n].reload.l20.go = "Vil_Hut3";
    locations[n].reload.l20.emerge = "reload1";
    locations[n].reload.l20.autoreload = "0";
    locations[n].reload.l20.label = "House";

    locations[n].reload.l21.name = "houseB1";
    locations[n].reload.l21.go = "Vil_BigHouse06";
    locations[n].reload.l21.emerge = "reload1";
    locations[n].reload.l21.autoreload = "0";
    locations[n].reload.l21.label = "House";

    locations[n].reload.l22.name = "houseB2";
    locations[n].reload.l22.go = "Vil_BigHouse06";
    locations[n].reload.l22.emerge = "reload2";
    locations[n].reload.l22.autoreload = "0";
    locations[n].reload.l22.label = "House";

    locations[n].reload.l23.name = "houseB3";
    locations[n].reload.l23.go = "Vil_BigHouse06";
    locations[n].reload.l23.emerge = "reload3";
    locations[n].reload.l23.autoreload = "0";
    locations[n].reload.l23.label = "House";

    locations[n].reload.l24.name = "houseB4";
    locations[n].reload.l24.go = "Vil_BigHouse06";
    locations[n].reload.l24.emerge = "reload1";
    locations[n].reload.l24.autoreload = "0";
    locations[n].reload.l24.label = "House";
    locations[n].reload.l24.disable = 1; // Закроем навсегда

    locations[n].reload.l25.name = "houseRs1";
    locations[n].reload.l25.go = "Vil_ResidencePKM";
    locations[n].reload.l25.emerge = "reload1";
    locations[n].reload.l25.autoreload = "0";
    locations[n].reload.l25.label = "Residence";
    locations[n].reload.l25.close_for_night = 1;

    locations[n].reload.l26.name = "houseH5";
    locations[n].reload.l26.go = "Vil_MH9_2";
    locations[n].reload.l26.emerge = "reload1";
    locations[n].reload.l26.autoreload = "0";
    locations[n].reload.l26.label = "House";

    locations[n].reload.l27.name = "houseRs2";
    locations[n].reload.l27.go = "Vil_MH9_2";
    locations[n].reload.l27.emerge = "reload1";
    locations[n].reload.l27.autoreload = "0";
    locations[n].reload.l27.label = "House";
    locations[n].reload.l27.disable = 1; // Закроем навсегда

    locations[n].reload.l28.name = "houseRs3";
    locations[n].reload.l28.go = "Vil_MH9_2";
    locations[n].reload.l28.emerge = "reload1";
    locations[n].reload.l28.autoreload = "0";
    locations[n].reload.l28.label = "House";
    locations[n].reload.l28.disable = 1; // Закроем навсегда

    locations[n].reload.l29.name = "houseK2a";
    locations[n].reload.l29.go = "Vil_MH9_2";
    locations[n].reload.l29.emerge = "reload1";
    locations[n].reload.l29.autoreload = "0";
    locations[n].reload.l29.label = "House";
    locations[n].reload.l29.disable = 1; // Закроем навсегда

    locations[n].reload.l30.name = "Hut4";
    locations[n].reload.l30.go = "Vil_Hut3";
    locations[n].reload.l30.emerge = "reload1";
    locations[n].reload.l30.autoreload = "0";
    locations[n].reload.l30.label = "Hut";
    locations[n].reload.l30.disable = 1; // Закроем навсегда

    locations[n].reload.l31.name = "houseS3";
    locations[n].reload.l31.go = "Vil_MH9_2";
    locations[n].reload.l31.emerge = "reload1";
    locations[n].reload.l31.autoreload = "0";
    locations[n].reload.l31.label = "House";
    locations[n].reload.l31.disable = 1; // Закроем навсегда

    locations[n].reload.l32.name = "houseB5";
    locations[n].reload.l32.go = "Vil_BigHouse06";
    locations[n].reload.l32.emerge = "reload3";
    locations[n].reload.l32.autoreload = "0";
    locations[n].reload.l32.label = "House";
    locations[n].reload.l32.disable = 1; // Закроем навсегда

    locations[n].reload.l33.name = "Hut1";
    locations[n].reload.l33.go = "Vil_Hut1";
    locations[n].reload.l33.emerge = "reload2";
    locations[n].reload.l33.autoreload = "0";
    locations[n].reload.l33.label = "House";

    // --> Комнаты заглушки
    locations[n].reload.l34.name = "houseF1";
    locations[n].reload.l34.go = "CommonStoneHouse";
    locations[n].reload.l34.emerge = "reload1";
    locations[n].reload.l34.autoreload = "0";
    locations[n].reload.l34.label = "House";

    locations[n].reload.l35.name = "houseSp1";
    locations[n].reload.l35.go = "CommonDoubleflourHouse_1";
    locations[n].reload.l35.emerge = "reload1";
    locations[n].reload.l35.autoreload = "0";
    locations[n].reload.l35.label = "House";

    locations[n].reload.l36.name = "houseSp2";
    locations[n].reload.l36.go = "CommonRoom_MH7";
    locations[n].reload.l36.emerge = "reload1";
    locations[n].reload.l36.autoreload = "0";
    locations[n].reload.l36.label = "House";

    locations[n].reload.l37.name = "houseS2";
    locations[n].reload.l37.go = "CommonFlamHouse";
    locations[n].reload.l37.emerge = "reload1";
    locations[n].reload.l37.autoreload = "0";
    locations[n].reload.l37.label = "House";

    locations[n].reload.l38.name = "houseS4";
    locations[n].reload.l38.go = "CommonPirateHouse";
    locations[n].reload.l38.emerge = "reload1";
    locations[n].reload.l38.autoreload = "0";
    locations[n].reload.l38.label = "House";

    locations[n].reload.l39.name = "houseH1";
    locations[n].reload.l39.go = "CommonRoom_MH3";
    locations[n].reload.l39.emerge = "reload1";
    locations[n].reload.l39.autoreload = "0";
    locations[n].reload.l39.label = "House";

    locations[n].reload.l40.name = "houseH2";
    locations[n].reload.l40.go = "CommonRoom_MH2";
    locations[n].reload.l40.emerge = "reload1";
    locations[n].reload.l40.autoreload = "0";
    locations[n].reload.l40.label = "House";

    locations[n].reload.l41.name = "houseH6";
    locations[n].reload.l41.go = "CommonRoom_MH9";
    locations[n].reload.l41.emerge = "reload1";
    locations[n].reload.l41.autoreload = "0";
    locations[n].reload.l41.label = "House";

    locations[n].reload.l42.name = "Hut5";
    locations[n].reload.l42.go = "CommonHut";
    locations[n].reload.l42.emerge = "reload1";
    locations[n].reload.l42.autoreload = "0";
    locations[n].reload.l42.label = "Hut";

    locations[n].reload.l43.name = "houseM1";
    locations[n].reload.l43.go = "CommonRoom_MH4";
    locations[n].reload.l43.emerge = "reload1";
    locations[n].reload.l43.autoreload = "0";
    locations[n].reload.l43.label = "House";

    locations[n].reload.l44.name = "houseM2";
    locations[n].reload.l44.go = "CommonDoubleflourHouse_1";
    locations[n].reload.l44.emerge = "reload1";
    locations[n].reload.l44.autoreload = "0";
    locations[n].reload.l44.label = "House";

    locations[n].reload.l45.name = "houseM3";
    locations[n].reload.l45.go = "CommonRoom_MH";
    locations[n].reload.l45.emerge = "reload1";
    locations[n].reload.l45.autoreload = "0";
    locations[n].reload.l45.label = "House";

    locations[n].reload.l46.name = "houseM4";
    locations[n].reload.l46.go = "CommonRoom_MH5";
    locations[n].reload.l46.emerge = "reload1";
    locations[n].reload.l46.autoreload = "0";
    locations[n].reload.l46.label = "House";

    locations[n].reload.l47.name = "houseM5";
    locations[n].reload.l47.go = "CommonRoom_MH10";
    locations[n].reload.l47.emerge = "reload1";
    locations[n].reload.l47.autoreload = "0";
    locations[n].reload.l47.label = "House";

    locations[n].reload.l48.name = "houseRs3";
    locations[n].reload.l48.go = "Vil_MH9_2";
    locations[n].reload.l48.emerge = "reload1";
    locations[n].reload.l48.autoreload = "0";
    locations[n].reload.l48.label = "House";
    locations[n].reload.l48.disable = 1; // Закроем навсегда

    locations[n].reload.l49.name = "houseT4";
    locations[n].reload.l49.go = "CommonRoom_MH";
    locations[n].reload.l49.emerge = "reload1";
    locations[n].reload.l49.autoreload = "0";
    locations[n].reload.l49.label = "House";
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ТАВЕРНА
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_tavern";
    locations[n].id.label = "Tavern";
    locations[n].image = "loading\inside\tavern.tga";
    locations[n].habitues = 1;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "tavern";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\Tavern05\";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "reload4";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    locations[n].reload.l2.name = "reload2_back";
    locations[n].reload.l2.go = "Villemstad_tavern_upstairs";
    locations[n].reload.l2.emerge = "reload1";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Tavern upstairs";
    locations[n].reload.l2.disable = 1; // закроем, но связку сделаем для квестовых нужд.
    LAi_LocationFightDisable(&locations[n], true);

    locations[n].reload.l3.name = "reload3_back";
    locations[n].reload.l3.go = "Villemstad_town";
    locations[n].reload.l3.emerge = "reload4";
    locations[n].reload.l3.autoreload = "0";
    locations[n].reload.l3.label = "Street";
    locations[n].reload.l3.disable = 1; // Закроем навсегда
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // КОМНАТА В ТАВЕРНЕ
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_tavern_upstairs";
    locations[n].id.label = "Tavern upstairs";
    locations[n].image = "loading\inside\tavern.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_tavern";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Tavern";
    locations[n].locators_radius.reload.reload1 = 0.8;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // МАГАЗИН
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_store";
    locations[n].id.label = "Store";
    locations[n].image = "loading\inside\shop.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "shop";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\Store04\";
    //Always
    locations[n].models.always.locators = "Store04_locators";
    locations[n].models.always.store = "Store04";
    locations[n].models.always.window = "Store04_window";
    locations[n].models.always.window.tech = "LocationWindows";
    locations[n].models.always.window.level = 50;
    locations[n].models.always.back = "..\inside_back";
    //Day
    locations[n].models.day.charactersPatch = "Store04_patch";
    //Night
    locations[n].models.night.charactersPatch = "Store04_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1_back";
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "reload6";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
    locations[n].locators_radius.camdetector.camera1 = 5;
    LAi_LocationFightDisable(&locations[n], true);
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ВЕРФЬ
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_Shipyard";
    locations[n].id.label = "Shipyard";
    locations[n].image = "loading\inside\shipyard.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "shipyard";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "reload5";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_Packhouse";
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
    locations[n].id = "Villemstad_Packhouse";
    locations[n].id.label = "Packhouse";
    locations[n].image = "loading\inside\sklad.tga";
    locations[n].packhouse = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "shipyard";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_Shipyard";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Shipyard";

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_PackhouseOffice";
    locations[n].reload.l2.emerge = "reload1";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "PackhouseOffice";
	locations[n].reload.l2.close_for_night = 1;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Офис заведующиго пакгаузом
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_PackhouseOffice";
    locations[n].id.label = "PackhouseOffice";
    locations[n].image = "loading\inside\sklad.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_Packhouse";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Packhouse";
    LAi_LocationFightDisable(&locations[n], true);
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // РЕЗИДЕНЦИЯ (ХОЛЛ)
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    locations[n].id = "Villemstad_hall";
    locations[n].id.label = "Townhall";
    locations[n].image = "loading\inside\Residence06.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "residence";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    // стража
    locations[n].soldiers = true;
    LAi_LocationFantomsGen(&locations[n], true);
    //Models
    locations[n].filespath.models = "locations\inside\Residence06";
    //Always
    locations[n].models.always.l1 = "Residence06";
    locations[n].models.always.l1.level = 65538;
    locations[n].models.always.l2 = "flora";
    locations[n].models.always.locators = "Residence06_plan";
    locations[n].models.always.window = "residence06_window";
    locations[n].models.always.window.tech = "LocationWindows";
    locations[n].models.always.window.level = 65539;
    //Day
    locations[n].models.day.charactersPatch = "Residence06_patch";
    //Night
    locations[n].models.night.charactersPatch = "Residence06_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "true";
    //Reload map
    locations[n].reload.l1.name = "reload1_back";
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "reload3";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    locations[n].reload.l2.name = "reload2_back";
    locations[n].reload.l2.go = "Villemstad_town";
    locations[n].reload.l2.emerge = "reloadR2";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Street";

    locations[n].reload.l3.name = "reload3_back";
    locations[n].reload.l3.go = "Villemstad_BedRoomK2";
    locations[n].reload.l3.emerge = "reload1";
    locations[n].reload.l3.autoreload = "0";
    locations[n].reload.l3.label = "TownhallRoom";

    locations[n].reload.l4.name = "reload4_back";
    locations[n].reload.l4.go = "Villemstad_townhall";
    locations[n].reload.l4.emerge = "reload1";
    locations[n].reload.l4.autoreload = "0";
    locations[n].reload.l4.label = "Townhall";

    locations[n].reload.l5.name = "reload5_back";
    locations[n].reload.l5.go = "CommonBedroom";
    locations[n].reload.l5.emerge = "reload1";
    locations[n].reload.l5.autoreload = "0";
    locations[n].reload.l5.label = "TownhallRoom";

    locations[n].reload.l6.name = "reload6_back";
    locations[n].reload.l6.go = "Villemstad_townhall2";
    locations[n].reload.l6.emerge = "reload1";
    locations[n].reload.l6.autoreload = "0";
    locations[n].reload.l6.label = "TownhallRoom";
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // РЕЗИДЕНЦИЯ (КАБИНЕТ ГУБЕРНАТОРА)
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    locations[n].id = "Villemstad_townhall";
    locations[n].id.label = "Townhall";
    locations[n].image = "loading\inside\Residence07.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "residence";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    // стража
    locations[n].soldiers = true;
    LAi_LocationFantomsGen(&locations[n], true);
    //Models
    locations[n].filespath.models = "locations\inside\Residence07";
    //Always
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
    locations[n].reload.l1.go = "Villemstad_hall";
    locations[n].reload.l1.emerge = "reload4";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Townhall";
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // РЕЗИДЕНЦИЯ (ОФИС СТЕВЕЗАНА)
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_townhall2";
    locations[n].id.label = "Townhall";
    locations[n].filespath.models = "locations\inside\Residence02";
    locations[n].image = "loading\inside\Residence02.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "residence";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    // стража
    locations[n].soldiers = true;
    LAi_LocationFantomsGen(&locations[n], true);
    //Models
    //Always
    locations[n].models.always.locators = "Residence02_locators";
    locations[n].models.always.l1 = "Residence02";
    locations[n].models.always.l1.level = 65538;
    locations[n].models.always.window = "residence02_window";
    locations[n].models.always.window.tech = "LocationWindows";
    locations[n].models.always.window.level = 65539;
    locations[n].models.always.back = "..\inside_back";
    locations[n].models.always.back.level = 65529;
    //Day
    locations[n].models.day.charactersPatch = "Residence02_patch";
    //Night
    locations[n].models.night.charactersPatch = "Residence02_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload2";
    locations[n].reload.l1.go = "Villemstad_TownhallRoom";
    locations[n].reload.l1.emerge = "reload1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Townhall";
    locations[n].reload.l1.disable = 0; // Закроем на совсем

    locations[n].reload.l2.name = "reload1_back";
    locations[n].reload.l2.go = "Villemstad_hall";
    locations[n].reload.l2.emerge = "reload6";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Townhall";
    locations[n].locators_radius.item.item1 = 1.1;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Комната в офисе Стейвезанта
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    locations[n].id = "Villemstad_TownhallRoom";
    locations[n].id.label = "TownhallRoom";
    locations[n].image = "loading\inside\BigHouse01.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    //Always
    locations[n].filespath.models = "locations\inside\BigHouse01";
    locations[n].models.always.model = "BigHouse01";
    locations[n].models.always.model.level = 65538;
    locations[n].models.day.locators = "BigHouse01_Villemstad";
    locations[n].models.night.locators = "BigHouse01_Villemstad";
    locations[n].models.always.window = "BigHouse01_windows";
    locations[n].models.always.window.tech = "LocationWindows";
    locations[n].models.always.window.level = 65539;

    locations[n].models.always.back = "..\inside_back";
    locations[n].models.always.back.level = 65529;
    //Day
    locations[n].models.day.charactersPatch = "BigHouse01_patch";
    //Night
    locations[n].models.night.charactersPatch = "BigHouse01_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_Townhall2";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Townhall";

    /*locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_town";
    locations[n].reload.l2.emerge = "reloadR1";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Street";
    locations[n].locators_radius.reload.locator1 = 0.8;*/

    //ключи для сундуков и предметы внутри
    locations[n].private1.items.blade6 = 1;
    locations[n].private1.items.topor3 = 1;
    locations[n].private1.items.potion1 = 10;
    locations[n].private1.items.potion3 = 2;
    locations[n].private2.key = "keyQuestLSC";
    locations[n].private2.key.delItem = true;
    locations[n].private2.items.letter_LSC = 1;
    locations[n].private2.items.incas_collection = 1;
    //locations[n].private2.items.patent_hol = 1;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // РЕЗИДЕНЦИЯ (СПАЛЬНЯ ПКМ)
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    locations[n].id = "Villemstad_BedRoomK2";
    locations[n].id.label = "Townhall";
    locations[n].image = "loading\inside\bedroom.tga";
    locations[n].Bedroom = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_hall";
    locations[n].reload.l1.emerge = "reload3_back";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Townhall";
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ЦЕРКОВЬ
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_church";
    locations[n].id.label = "Church";
    locations[n].image = "loading\inside\church.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "church";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\Church01";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "reload7";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
    LAi_LocationFightDisable(&locations[n], true);
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // РОСТОВЩИК
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_bank";
    locations[n].id.label = "Usurer House";
    locations[n].image = "loading\inside\bank.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "shop";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\Bank01\";
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
    locations[n].models.day.charactersPatch = "Bank01_patch";
    //Night
    locations[n].models.night.charactersPatch = "Bank01_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1_back";
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "reload8";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_bankvault";
    locations[n].reload.l2.emerge = "reload1";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Room";
    LAi_LocationFightDisable(&locations[n], true);
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Хранилище (Банк)
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_bankvault";
    locations[n].id.label = "bankvault";
    locations[n].image = "loading\inside\vault.tga";
    //locations[n].MustSetReloadBack = true;
    //locations[n].packhouse = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_bank";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
    LAi_LocationFightDisable(&locations[n], true);
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // ПОРТОВЫЙ ОФИС
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_PortOffice";
    locations[n].id.label = "PortOffice";
    locations[n].image = "loading\inside\portoffice.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\PortOffice3";
    //Always
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "reload10";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
    LAi_LocationFightDisable(&locations[n], true);
    n = n + 1;

    ////////////////////// prison ////////////////////////////
    Locations[n].id = "Villemstad_prison";
    locations[n].id.label = "Prison";
    Locations[n].image = "loading\inside\prison.tga";
    locations[n].townsack = "Villemstad";
    locations[n].parent_colony = "Villemstad";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    Locations[n].reload.l1.go = "Villemstad_town";
    Locations[n].reload.l1.emerge = "HouseT1";
    Locations[n].reload.l1.autoreload = "0";

    locations[n].locators_radius.box.box1 = 0.8;

    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // БОРДЕЛЬ
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_Brothel";
    locations[n].id.label = "Brothel";
    locations[n].image = "loading\inside\brothell_hall.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "reload9";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    locations[n].reload.l2.name = "reload2_back";
    locations[n].reload.l2.go = "Villemstad_Brothel_room";
    locations[n].reload.l2.emerge = "reload1";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Brothel Room";
    locations[n].reload.l2.disable = 1;  //закроем, но связка пусть будет для квестов.

    locations[n].reload.l3.name = "reload3";
    locations[n].reload.l3.go = "Villemstad_SecBrRoom";
    locations[n].reload.l3.emerge = "reload1";
    locations[n].reload.l3.autoreload = "0";
    locations[n].reload.l3.label = "Brothel";
    LAi_LocationFightDisable(&locations[n], true);
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // БОРДЕЛЬ (комната наверху)
    locations[n].id = "Villemstad_Brothel_room";
    locations[n].id.label = "Brothel Room";
    locations[n].image = "loading\inside\brothell_room.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_brothel";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Brothel";
    LAi_LocationFightDisable(&locations[n], true);
    locations[n].locators_radius.item.item1 = 1;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // БОРДЕЛЬ (комната маман)
    locations[n].id = "Villemstad_SecBrRoom";
    locations[n].id.label = "Room";
    locations[n].image = "loading\inside\BigHouse03.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    locations[n].brothel = true;
    //Models
    locations[n].filespath.models = "locations\inside\BigHouse03\";
    //Always
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
    locations[n].reload.l1.go = "Villemstad_Brothel";
    locations[n].reload.l1.emerge = "reload3";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Brothel";

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_town";
    locations[n].reload.l2.emerge = "reload91";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Street";
    LAi_LocationFightDisable(&locations[n], true);
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    // Штаб-квартира ГВИК
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "GVIK";
    locations[n].id.label = "GWIKshort";
    locations[n].image = "loading\inside\GWIC.tga";
    locations[n].HWIC = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\office";
    //Always
    locations[n].models.always.office = "office";
    locations[n].models.always.office.level = 65538;
    locations[n].models.always.window = "office_windows";
    locations[n].models.always.window.tech = "LocationWindows";
    locations[n].models.always.window.level = 65539;
    locations[n].models.always.back = "..\inside_back";
    locations[n].models.always.back.level = 65529;
    //Day
    locations[n].models.day.locators = "office_locators";
    locations[n].models.day.charactersPatch = "office_patch";
    //Night
    locations[n].models.night.locators = "office_Nlocators";
    locations[n].models.night.charactersPatch = "office_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "HouseO1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_town";
    locations[n].reload.l2.emerge = "HouseO2";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Street";

    locations[n].reload.l3.name = "reload3";
    locations[n].reload.l3.go = "GVIK";
    locations[n].reload.l3.emerge = "reload3";
    locations[n].reload.l3.autoreload = "0";
    locations[n].reload.l3.label = "House";
    locations[n].reload.l3.disable = true; //Закрыто, типа там ещё много всякого, но нас туды не пускают

    locations[n].reload.l4.name = "reload4";
    locations[n].reload.l4.go = "Villemstad_Residence_GVIK";
    locations[n].reload.l4.emerge = "reload1";
    locations[n].reload.l4.autoreload = "0";
    locations[n].reload.l4.label = "residence";
    LAi_LocationFightDisable(&locations[n], true); //в ГВИК драться нельзя
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    // Офис представителя Голландской Вест-Индской компании
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_Residence_GVIK";
    locations[n].id.label = "Townhall";
    locations[n].image = "loading\inside\Residence08.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    locations[n].noFight = true; //до поры не даем тут драться
    //Models
    locations[n].filespath.models = "locations\inside\Residence08";
    //Always
    locations[n].models.always.locators = "Res08_l";
    locations[n].models.always.house = "Res08";
    locations[n].models.always.house.level = 65538;
    locations[n].models.always.window = "Res08_w";
    locations[n].models.always.window.tech = "LocationWindows";
    locations[n].models.always.window.level = 65539;
    locations[n].models.always.back = "..\inside_back";
    locations[n].models.always.back.level = 65529;
    //Day
    locations[n].models.day.charactersPatch = "Res08_p";
    //Night
    locations[n].models.night.charactersPatch = "Res08_p";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "GVIK";
    locations[n].reload.l1.emerge = "reload4";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "GWIKshort";
    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "GVIK";
    locations[n].reload.l2.emerge = "reload3";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "GWIKshort";
    locations[n].reload.l2.disable = true; //Закрыто, типа там ещё много всякого, но нас туды не пускают
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Дом Аарона Мендеса Чумакейро
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_houseS3";
    locations[n].id.label = "Aaron's House";
    locations[n].image = "loading\inside\CobHouse.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\CobHouse";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "reloadR1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "CommonPirateresidence";
    locations[n].reload.l2.emerge = "reload1";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Room";
    LAi_LocationFightDisable(&locations[n], true);
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Дом Мастера Ключей
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_houseSp5";
    locations[n].id.label = "MK_House";
    locations[n].image = "loading\inside\TwoFloorHouse.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\TwoFloorHouse";
    //Always
    locations[n].models.always.house = "TwoFloorHouse";
    locations[n].models.always.house.level = 65538;
    locations[n].models.day.locators = "TwoFloorHouse_locators";
    locations[n].models.night.locators = "TwoFloorHouse_Nlocators";
    locations[n].models.always.window = "TwoFloorHouse_windows";
    locations[n].models.always.window.tech = "LocationWindows";
    locations[n].models.always.window.level = 65539;
    locations[n].models.always.back = "..\inside_back";
    locations[n].models.always.back.level = 65529;
    //Day
    Locations[n].models.day.TwoFloorHouseRand = "TwoFloorHouse_rand";
    locations[n].models.day.charactersPatch = "TwoFloorHouse_patch";
    //Night
    locations[n].models.night.charactersPatch = "TwoFloorHouse_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "houseS1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
    locations[n].locators_radius.item.item2 = 0.9;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Аптека
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Farmacia";
    locations[n].id.label = "Apteka";
    locations[n].image = "loading\inside\Farmacia.tga";
    //locations[n].MustSetReloadBack = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\Farmacia1";
    //Always
    locations[n].models.always.office = "Farmacia";
    locations[n].models.always.office.level = 65538;
    locations[n].models.always.L1 = "Farmacia_back";
    locations[n].models.always.L2 = "Farmacia_lamp";
    locations[n].models.always.window = "Farmacia_glas";
    locations[n].models.always.window.tech = "LocationWindows";
    locations[n].models.always.window.level = 65539;
    locations[n].models.always.locators = "Farmacia_locators";
    //Day
    locations[n].models.day.charactersPatch = "patch";
    //Night
    locations[n].models.night.charactersPatch = "patch";
    locations[n].models.night.L3 = "Farmacia_locatorsN";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "true";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "houseFa1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_town";
    locations[n].reload.l2.emerge = "houseFa2";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Street";

    locations[n].reload.l3.name = "reload3";
    locations[n].reload.l3.go = "Vil_MH9_2";
    locations[n].reload.l3.emerge = "reload1";
    locations[n].reload.l3.autoreload = "0";
    locations[n].reload.l3.label = "House";
    locations[n].reload.l3.disable = 1; // Закроем навсегда

    //	locations[n].private1.key = "keyA";
    locations[n].private1.money = 2109;
    locations[n].private1.items.indian22 = 1;
    locations[n].private1.items.potion4 = 7;
    locations[n].private1.items.potion3 = 2;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Маленький дом из ПКМ, где живёт больной
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Smallhome_K2";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\Smallhome.tga";
    locations[n].MustSetReloadBack = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\Smallhome";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "houseK2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Хижина у пирса с двумя входами
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Vil_Hut";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\Hut.tga";
    locations[n].MustSetReloadBack = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\Hut";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "houseH3";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_town";
    locations[n].reload.l2.emerge = "houseH4";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Street";
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Хижина с камином
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Vil_Hut3";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\Hut3.tga";
    locations[n].MustSetReloadBack = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "Hut3";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Дом с 4 дверьми
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Vil_BigHouse06";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\BigHouse06.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "houseB1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_town";
    locations[n].reload.l2.emerge = "houseB2";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Street";

    locations[n].reload.l3.name = "reload3";
    locations[n].reload.l3.go = "Villemstad_town";
    locations[n].reload.l3.emerge = "houseB3";
    locations[n].reload.l3.autoreload = "0";
    locations[n].reload.l3.label = "Street";
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Маленькая резиденция из ПКМ
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Vil_ResidencePKM";
    locations[n].id.label = "Residence";
    locations[n].image = "loading\inside\pirateresidence01.tga";
    //locations[n].MustSetReloadBack = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "residence";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "houseRs1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Средний дом 8 (9 с заменённой стенкой)
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Vil_MH9_2";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\mediumhouse08.tga";
    locations[n].MustSetReloadBack = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    Locations[n].models.day.mediumhouse09rand = "mediumhouse09_rand";
    locations[n].models.day.charactersPatch = "mediumhouse09_patch";
    //Night
    locations[n].models.night.charactersPatch = "mediumhouse09_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "houseH5";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Изба рыбака
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Vil_Hut1";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\hibara.tga";
    locations[n].MustSetReloadBack = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].fastreload = "Villemstad";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "Hut1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Street";
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Выход из города
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_ExitTown";
    locations[n].id.label = "ExitTown";
    locations[n].image = "loading\Gate.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    //Sound
    locations[n].type = "jungle";
    locations[n].islandId = "Curacao";
    //Models
    //Always
    locations[n].filespath.models = "locations\Outside\Jungles\TownExitW";
    Locations[n].models.always.townExit = "townExitW";
    Locations[n].models.always.townWalls = "townExitW_wood";

    Locations[n].models.always.locators = "townExitW_locators";

    Locations[n].models.always.grassPatch = "townExitW_grass";
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
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "gate_back";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Villemstad";

    locations[n].reload.l2.name = "reload1_back";
    locations[n].reload.l2.go = "Curacao_jungle_01";
    locations[n].reload.l2.emerge = "reload3";
    locations[n].reload.l2.autoreload = "1";
    locations[n].reload.l2.label = "Jungle";
    locations[n].locators_radius.reload.reload1_back = 2.0;

    locations[n].reload.l3.name = "reload2_back";
    locations[n].reload.l3.go = "Villemstad_Graveyard";
    locations[n].reload.l3.emerge = "reload2";
    locations[n].reload.l3.autoreload = "1";
    locations[n].reload.l3.label = "Graveyard";
    locations[n].locators_radius.reload.reload2_back = 2.0;

    locations[n].reload.l4.name = "reload3_back";
    locations[n].reload.l4.go = "Villemstad_fort";
    locations[n].reload.l4.emerge = "reload1";
    locations[n].reload.l4.autoreload = "1";
    locations[n].reload.l4.label = "Villemstad Fort";
    locations[n].locators_radius.reload.reload3_back = 2.0;
    n = n + 1;
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // городское кладбище
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_Graveyard";
    locations[n].id.label = "Graveyard";
    locations[n].image = "loading\Outside\Cemetery.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    //Sound
    locations[n].type = "jungle";
    locations[n].islandId = "Curacao";
    locations[n].DisableEncounters = true;
    //Models
    locations[n].filespath.models = "locations\Outside\Graveyard";
    //Always
    Locations[n].models.always.Graveyard = "Churchyard";
    Locations[n].models.always.grassPatch = "Churchyard_grass";
    Locations[n].models.always.l1 = "Churchyard_plan1";
    Locations[n].models.always.l1.level = 9;
    Locations[n].models.always.l1.tech = "LocationModelBlend";
    Locations[n].models.always.l2 = "Churchyard_plan2";
    Locations[n].models.always.l2.level = 8;
    Locations[n].models.always.l2.tech = "LocationModelBlend";
    Locations[n].models.always.l3 = "Churchyard_plan3";
    Locations[n].models.always.l3.level = 7;
    Locations[n].models.always.l3.tech = "LocationModelBlend";
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
    locations[n].reload.l1.name = "reload2_back";
    locations[n].reload.l1.go = "Villemstad_ExitTown";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "1";
    locations[n].reload.l1.label = "Shore24";
    locations[n].locators_radius.reload.reload1_back = 2.0;

    locations[n].reload.l2.name = "reload1_back";
    locations[n].reload.l2.go = "Shore24";
    locations[n].reload.l2.emerge = "reload1";
    locations[n].reload.l2.autoreload = "1";
    locations[n].reload.l2.label = "ExitTown";
    locations[n].locators_radius.reload.reload2_back = 2.0;

    locations[n].reload.l3.name = "reload3";
    locations[n].reload.l3.go = "Villemstad_KeepersHouse";
    locations[n].reload.l3.emerge = "reload1";
    locations[n].reload.l3.autoreload = "0";
    locations[n].reload.l3.label = "House";

    locations[n].reload.l4.name = "reload4";
    locations[n].reload.l4.go = "Villemstad_CryptBig1";
    locations[n].reload.l4.emerge = "reload1";
    locations[n].reload.l4.autoreload = "0";
    locations[n].reload.l4.label = "Chapel";

    locations[n].reload.l5.name = "reload5";
    locations[n].reload.l5.go = "Villemstad_Crypt";
    locations[n].reload.l5.emerge = "reload1";
    locations[n].reload.l5.autoreload = "0";
    locations[n].reload.l5.label = "Crypt";

    locations[n].reload.l6.name = "reload6";
    locations[n].reload.l6.go = "Villemstad_Chapel";
    locations[n].reload.l6.emerge = "reload1";
    locations[n].reload.l6.autoreload = "0";
    locations[n].reload.l6.label = "Chapel";
    n = n + 1;

    /////////////////////////////////////////////////////////////////////////////////////////////
    // домик смотрителя
    /////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_KeepersHouse";
    locations[n].id.label = "KeepersHouse";
    locations[n].image = "loading\inside\SmallHouse_inside.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\SmallHouse_inside\";
    //Always
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
    locations[n].reload.l1.go = "Villemstad_Graveyard";
    locations[n].reload.l1.emerge = "reload3";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Graveyard";
    n = n + 1;

    /////////////////////////////////////////////////////////////////////////////////////////////
    // часовня
    /////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_Chapel";
    locations[n].id.label = "Chapel";
    locations[n].image = "loading\inside\IM_church.tga";
    // locations[n].Chapel = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "church";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_Graveyard";
    locations[n].reload.l1.emerge = "reload6";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Graveyard";

    LAi_LocationFightDisable(&locations[n], true);
    n = n + 1;

    /////////////////////////////////////////////////////////////////////////////////////////////
    // крипта большая - 1
    /////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_CryptBig1";
    locations[n].id.label = "Crypt";
    locations[n].image = "loading\Crypt.tga";
    locations[n].CryptBig1 = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "dungeon";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_Graveyard";
    locations[n].reload.l1.emerge = "reload4";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Graveyard";

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_CryptBig2";
    locations[n].reload.l2.emerge = "reload1";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Crypt";
    n = n + 1;

    /////////////////////////////////////////////////////////////////////////////////////////////
    // крипта большая - 2
    /////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_CryptBig2";
    locations[n].id.label = "Crypt";
    locations[n].image = "loading\Crypt.tga";
    locations[n].MustSetReloadBack = true;
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "dungeon";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_CryptBig1";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Crypt";

    /*locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_CryptDungeon";
    locations[n].reload.l2.emerge = "reload1";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Crypt dungeon";
    locations[n].reload.l2.disable = true; // закрыто до поры*/

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_CryptBig2";
    locations[n].reload.l2.emerge = "reload3";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Crypt";
    locations[n].reload.l2.disable = true; // закрыто до поры*/

    locations[n].reload.l3.name = "reload3";
    locations[n].reload.l3.go = "Villemstad_CryptBig2";
    locations[n].reload.l3.emerge = "reload2";
    locations[n].reload.l3.autoreload = "0";
    locations[n].reload.l3.label = "Crypt";
    CryptBoxRadius(n, "big");
    n = n + 1;

    /////////////////////////////////////////////////////////////////////////////////////////////
    // логово Мерримана
    /////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_CryptDungeon";
    locations[n].id.label = "Crypt";
    locations[n].image = "loading\inside\dungeon.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "dungeon";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\inside\Animists_cave\";
    //Always
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
    locations[n].reload.l1.go = "Villemstad_CryptBig2";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Crypt";
    n = n + 1;

    /////////////////////////////////////////////////////////////////////////////////////////////
    // крипта малая
    /////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_Crypt";
    locations[n].id.label = "Crypt";
    locations[n].image = "loading\Crypt.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "dungeon";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Villemstad_Graveyard";
    locations[n].reload.l1.emerge = "reload5";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Graveyard";
    CryptBoxRadius(n, "small");
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Пляж 24
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Shore24";
    locations[n].id.label = "Shore24";
    locations[n].image = "loading\outside\harbor.tga";
    locations[n].worldmap = "Shore24";
    //Sound
    locations[n].type = "seashore";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\Outside\Shores\Shore09";
    //Always
    Locations[n].models.always.shore09 = "shore09";
    locations[n].models.always.shore09.sea_reflection = 1;
    Locations[n].models.always.shore09seabed = "shore09_sb";
    Locations[n].models.always.locators = "shore09_locators";
    Locations[n].models.always.grassPatch = "shore09_grass";

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
    locations[n].models.day.charactersPatch = "shore09_patch";
    //Night
    locations[n].models.night.charactersPatch = "shore09_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "true";
    //Reload map
    locations[n].reload.l1.name = "reload1_back";
    locations[n].reload.l1.go = "Villemstad_Graveyard";
    locations[n].reload.l1.emerge = "reload1";
    locations[n].reload.l1.autoreload = "1";
    locations[n].reload.l1.label = "Graveyard";
    locations[n].locators_radius.reload.reload1_back = 2;

    locations[n].reload.l2.name = "boat";
    locations[n].reload.l2.go = "Curacao";
    locations[n].reload.l2.emerge = "reload_4";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Джунгли
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Curacao_jungle_01";
    locations[n].id.label = "Jungle";
    locations[n].image = "loading\outside\jungle.tga";
    //Sound
    locations[n].type = "jungle";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Curacao_jungle_02";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "1";
    locations[n].reload.l1.label = "Jungle";
    locations[n].locators_radius.reload.Reload1_back = 2.0;

    locations[n].reload.l2.name = "reload2_back";
    locations[n].reload.l2.go = "Curacao_CaveEntrance";
    locations[n].reload.l2.emerge = "reload2";
    locations[n].reload.l2.autoreload = "1";
    locations[n].reload.l2.label = "Cave entrance";
    locations[n].locators_radius.reload.Reload2_back = 2.0;

    locations[n].reload.l3.name = "reload3_back";
    locations[n].reload.l3.go = "Villemstad_ExitTown";
    locations[n].reload.l3.emerge = "reload1";
    locations[n].reload.l3.autoreload = "1";
    locations[n].reload.l3.label = "ExitTown";
    locations[n].locators_radius.reload.Reload3_back = 2.0;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Вход в пещеру
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Curacao_CaveEntrance";
    locations[n].id.label = "Cave entrance";
    locations[n].image = "loading\outside\jungle.tga";
    //Sound
    locations[n].type = "jungle";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Curacao_Cave";
    locations[n].reload.l1.emerge = "reload1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Cave";
    locations[n].locators_radius.reload.reload1_back = 1.3;

    locations[n].reload.l2.name = "reload2_back";
    locations[n].reload.l2.go = "Curacao_jungle_01";
    locations[n].reload.l2.emerge = "reload2";
    locations[n].reload.l2.autoreload = "1";
    locations[n].reload.l2.label = "Jungle";
    locations[n].locators_radius.reload.reload2_back = 2.0;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Пещера
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Curacao_Cave";
    locations[n].image = "loading\inside\cave.tga";
    locations[n].id.label = "Cave";
    //Sound
    locations[n].type = "cave";
    locations[n].islandId = "Curacao";
    //Models
    //Always
    locations[n].filespath.models = "locations\inside\cavernMedium2";
    locations[n].models.always.cavernMedium2 = "cavernMedium2";
    locations[n].models.always.lamps = "cavernMedium2_lamps";
    locations[n].models.always.locators = "cavernMedium2_locators";

    // EvgAnat - "дикие Карибы", убираем дефолтные сферы
    locations[n].locators_radius.item.duhi1 = 0.0;

    /*	Locations[n].models.always.rays = "cavernMedium2_rays";
        Locations[n].models.always.rays.level = 49;
        Locations[n].models.always.rays.tech= "LocVisRays";
        Locations[n].models.always.rays.uvslide.u1 = 0.0;
        Locations[n].models.always.rays.uvslide.v1 = 0.0;	*/
    //Day
    locations[n].models.day.charactersPatch = "cavernMedium2_patch";
    //Night
    locations[n].models.night.charactersPatch = "cavernMedium2_patch";
    //Environment
    locations[n].environment.weather = "true";
    Locations[n].lockWeather = "Inside";
    Locations[n].QuestlockWeather = "23 Hour";
    locations[n].environment.sea = "false";
    locations[n].environment.weather.rain = false;
    //Reload map
    locations[n].reload.l1.name = "reload1_back";
    locations[n].reload.l1.go = "Curacao_CaveEntrance";
    locations[n].reload.l1.emerge = "reload1";
    locations[n].locators_radius.reload.reload1 = 2.0;

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Curacao_jungle_03";
    locations[n].reload.l2.emerge = "reloadW";
    locations[n].locators_radius.reload.reload2 = 2.0;
    locations[n].locators_radius.item.CheckReload1 = 3.5;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Джунгли
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Curacao_jungle_02";
    locations[n].id.label = "Jungle";
    locations[n].image = "loading\outside\jungle.tga";
    //Sound
    locations[n].type = "jungle";
    locations[n].islandId = "Curacao";
    //Models
    //Always
    locations[n].filespath.models = "locations\Outside\Jungles\jungle8\";
    Locations[n].models.always.jungle = "jungle8";
    Locations[n].models.always.locators = "jungle8_locators";
    Locations[n].models.always.grassPatch = "jungle8_grass";
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
    locations[n].models.day.charactersPatch = "jungle8_patch";
    //Night
    locations[n].models.night.charactersPatch = "jungle8_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1_back";
    locations[n].reload.l1.go = "Curacao_jungle_03";
    locations[n].reload.l1.emerge = "reload1";
    locations[n].reload.l1.autoreload = "1";
    locations[n].reload.l1.label = "Jungle";
    locations[n].locators_radius.reload.reload1_back = 2.0;

    locations[n].reload.l2.name = "reload2_back";
    locations[n].reload.l2.go = "Curacao_jungle_01";
    locations[n].reload.l2.emerge = "reload1";
    locations[n].reload.l2.autoreload = "1";
    locations[n].reload.l2.label = "Jungle";
    locations[n].locators_radius.reload.reload2_back = 2.0;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Джунгли
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Curacao_jungle_03";
    locations[n].id.label = "Jungle";
    locations[n].image = "loading\outside\jungle.tga";
    //Sound
    locations[n].type = "jungle";
    locations[n].islandId = "Curacao";
    //Models
    //Always
    locations[n].filespath.models = "locations\Outside\Jungles\Jungle6";
    Locations[n].models.always.jungle = "jungle6";
    Locations[n].models.always.locators = "jungle6_lCuracao03";
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
    Locations[n].models.always.well_small.locator.name = "reloadW_back";
    Locations[n].models.always.well_small.tech = "DLightModel";
    //Day
    locations[n].models.day.charactersPatch = "jungle6_pCuracao03";
    //Night
    locations[n].models.night.charactersPatch = "jungle6_pCuracao03";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1_back";
    locations[n].reload.l1.go = "Curacao_jungle_02";
    locations[n].reload.l1.emerge = "reload1";
    locations[n].reload.l1.autoreload = "1";
    locations[n].reload.l1.label = "Jungle";
    locations[n].locators_radius.reload.reload1_back = 2;

    locations[n].reload.l2.name = "reload2_back";
    locations[n].reload.l2.go = "Shore22";
    locations[n].reload.l2.emerge = "reload1";
    locations[n].reload.l2.autoreload = "1";
    locations[n].reload.l2.label = "Shore22";
    locations[n].locators_radius.reload.reload2_back = 2;

    locations[n].reload.l3.name = "reload3_back";
    locations[n].reload.l3.go = "Shore23";
    locations[n].reload.l3.emerge = "reload1";
    locations[n].reload.l3.autoreload = "1";
    locations[n].reload.l3.label = "Shore23";
    locations[n].locators_radius.reload.reload3_back = 2;

    locations[n].reload.l4.name = "reloadW_back";
    locations[n].reload.l4.go = "Curacao_Cave";
    locations[n].reload.l4.emerge = "reload2";
    locations[n].reload.l4.autoreload = "0";
    locations[n].reload.l4.label = "Jungle";
    locations[n].locators_radius.reload.reloadW_back = 2.3;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Мыс Кальвинистов Пляж 23
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Shore23";
    locations[n].id.label = "Shore23";
    locations[n].image = "loading\outside\harbor.tga";
    locations[n].worldmap = "Shore23";
    //Sound
    locations[n].type = "seashore";
    locations[n].islandId = "Curacao";
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
    locations[n].reload.l1.go = "Curacao_jungle_03";
    locations[n].reload.l1.emerge = "reload3";
    locations[n].reload.l1.autoreload = "1";
    locations[n].reload.l1.label = "Jungle";
    locations[n].locators_radius.reload.reload1_back = 2;

    locations[n].reload.l2.name = "boat";
    locations[n].reload.l2.go = "Curacao";
    locations[n].reload.l2.emerge = "reload_2";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Пальмовый берег Пляж 22
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Shore22";
    locations[n].id.label = "Shore22";
    locations[n].image = "loading\outside\harbor.tga";
    locations[n].image = "loading\outside\harbor.tga";
    locations[n].worldmap = "Shore22";
    //Sound
    locations[n].type = "seashore";
    locations[n].islandId = "Curacao";
    //Models
    //Always
    locations[n].filespath.models = "locations\Outside\Shores\Shore05";
    Locations[n].models.always.shore05 = "shore05";
    locations[n].models.always.shore05.sea_reflection = 1;
    Locations[n].models.always.shore05seabed = "shore05_sb";
    Locations[n].models.always.locators = "Shore05_locators";

    Locations[n].models.always.grassPatch = "shore05_grass";
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
    locations[n].models.day.charactersPatch = "shore05_patch";
    //Night
    locations[n].models.night.charactersPatch = "shore05_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "true";
    //Reload map
    locations[n].reload.l1.name = "reload1_back";
    locations[n].reload.l1.go = "Curacao_jungle_03";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "1";
    locations[n].reload.l1.label = "Jungle";
    locations[n].locators_radius.reload.reload1_back = 2;

    locations[n].reload.l2.name = "boat";
    locations[n].reload.l2.go = "Curacao";
    locations[n].reload.l2.emerge = "reload_3";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Sea";
    locations[n].locators_radius.reload.boat = 9.0;
    locations[n].locators_radius.quest.detector1 = 7.0; //увеличиваем радиус детектора.
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Джунгли (альтернативный выход из города)
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Curacao_jungle_04";
    locations[n].id.label = "GoToPlantation";
    locations[n].image = "loading\outside\jungle.tga";
    //Sound
    locations[n].type = "jungle";
    locations[n].islandId = "Curacao";
    //Models
    locations[n].filespath.models = "locations\Outside\Jungles\Jungle10";
    //Always
    Locations[n].models.always.jungle = "jungle10";
    Locations[n].models.always.locators = "jungle10_locators";
    Locations[n].models.always.grassPatch = "jungle10_grass";
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
    locations[n].models.day.charactersPatch = "jungle10_patch";
    //Night
    locations[n].models.night.charactersPatch = "jungle10_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1_back";
    locations[n].reload.l1.go = "Villemstad_town";
    locations[n].reload.l1.emerge = "reload33_back";
    locations[n].reload.l1.autoreload = "1";
    locations[n].reload.l1.label = "Villemstad";
    locations[n].locators_radius.reload.Reload1_back = 2.0;

    locations[n].reload.l2.name = "reload2_back";
    locations[n].reload.l2.go = "Villemstad_Plantation";
    locations[n].reload.l2.emerge = "reload2";
    locations[n].reload.l2.autoreload = "1";
    locations[n].reload.l2.label = "Plantation";
    locations[n].locators_radius.reload.Reload2_back = 2.0;
    n = n + 1;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Плантация Кюрасао
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    locations[n].id = "Villemstad_Plantation";
    locations[n].id.label = "Plantation";
    locations[n].image = "loading\Plantation.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
    locations[n].islandIdAreal = "Villemstad";
    locations[n].citizens = true;    //homo жители
    locations[n].soldiers = true;    //homo солдаты
    locations[n].carrier = true;    //homo грузчики
    //Sound
    locations[n].type = "plantation";
    //Models
    //Always
    locations[n].filespath.models = "locations\Outside\Plantation";
    locations[n].models.always.Plantation = "Plantation";
    locations[n].models.always.reflect = "Plantation_reflect";
    Locations[n].models.always.reflect.sea_reflection = 1;
    locations[n].models.always.gate = "Plantation_gateopen";
    locations[n].models.always.locators = "Plantation_locators";    //чек
    locations[n].models.always.grassPatch = "Plantation_grass";
    Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
    Locations[n].models.always.Waterfall = "waterfall";
    Locations[n].models.always.Waterfall.uvslide.v0 = 0.3;
    Locations[n].models.always.Waterfall.uvslide.v1 = 0.0;
    Locations[n].models.always.Waterfall.tech = "LocationWaterFall";
    Locations[n].models.always.Waterfall.level = 99949;
    locations[n].models.always.plan1 = "plan1";
    locations[n].models.always.plan1.level = 9;
    locations[n].models.always.plan2 = "plan2";
    locations[n].models.always.plan2.level = 8;
    locations[n].models.always.plan3 = "plan3";
    locations[n].models.always.plan3.level = 7;
    locations[n].models.always.plan4 = "plan4";
    locations[n].models.always.plan4.level = 6;

    locations[n].models.always.l1 = "Plantation_wall";
    Locations[n].models.always.l1.tech = "DLightModel";

    //Day
    locations[n].models.day.charactersPatch = "Plantation_patchwall";
    locations[n].models.day.fonar = "Plantation_fd";
    //Night
    locations[n].models.night.charactersPatch = "Plantation_patchwall";
    locations[n].models.night.fonar = "Plantation_fn";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "true";
    //Reload map

    locations[n].reload.l1.name = "reload2_back";
    locations[n].reload.l1.go = "Curacao_jungle_04";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "1";
    locations[n].reload.l1.label = "Street";
    locations[n].locators_radius.reload.reload1_back = 2.5;

    //дома
    locations[n].reload.l3.name = "houseSp1";
    locations[n].reload.l3.go = "Villemstad_Plantation_Sp1";
    locations[n].reload.l3.emerge = "reload1";
    locations[n].reload.l3.autoreload = false;
    locations[n].reload.l3.label = "Townhall";

    locations[n].reload.l4.name = "houseS1";
    locations[n].reload.l4.go = "Villemstad_Plantation_S1";
    locations[n].reload.l4.emerge = "reload2";
    locations[n].reload.l4.autoreload = false;
    locations[n].reload.l4.label = "House";

    locations[n].reload.l5.name = "houseS2";
    locations[n].reload.l5.go = "Villemstad_Plantation_S2";
    locations[n].reload.l5.emerge = "reload1";
    locations[n].reload.l5.autoreload = false;
    locations[n].reload.l5.label = "House";

    locations[n].reload.l6.name = "houseG1";
    locations[n].reload.l6.go = "Villemstad_Plantation_G1";
    locations[n].reload.l6.emerge = "reload1";
    locations[n].reload.l6.autoreload = false;
    locations[n].reload.l6.label = "House";

    locations[n].reload.l7.name = "houseG2";
    locations[n].reload.l7.go = "Villemstad_Plantation_G2";
    locations[n].reload.l7.emerge = "reload1";
    locations[n].reload.l7.autoreload = false;
    locations[n].reload.l7.label = "House";

    locations[n].reload.l8.name = "houseG3";
    locations[n].reload.l8.go = "Villemstad_Plantation_G3";
    locations[n].reload.l8.emerge = "reload1";
    locations[n].reload.l8.autoreload = false;
    locations[n].reload.l8.label = "House";

    locations[n].reload.l9.name = "houseG4";
    locations[n].reload.l9.go = "Villemstad_Plantation_G4";
    locations[n].reload.l9.emerge = "reload1";
    locations[n].reload.l9.autoreload = false;
    locations[n].reload.l9.label = "House";

    locations[n].reload.l10.name = "houseG5";
    locations[n].reload.l10.go = "Villemstad_Plantation_G5";
    locations[n].reload.l10.emerge = "reload1";
    locations[n].reload.l10.autoreload = false;
    locations[n].reload.l10.label = "House";

    /*locations[n].reload.l11.name = "houseG6"; //Бладовские бараки
    locations[n].reload.l11.go = "Villemstad_Plantation_G6";
    locations[n].reload.l11.emerge = "reload1";
    locations[n].reload.l11.autoreload = false;
    locations[n].reload.l11.label = "House";*/

    locations[n].reload.l12.name = "houseG7"; //Бладовские бараки
    locations[n].reload.l12.go = "Villemstad_Plantation_G7";
    locations[n].reload.l12.emerge = "reload1";
    locations[n].reload.l12.autoreload = false;
    locations[n].reload.l12.label = "House";

    locations[n].reload.l13.name = "houseF1";
    locations[n].reload.l13.go = "Villemstad_Plantation_F1";
    locations[n].reload.l13.emerge = "reload1";
    locations[n].reload.l13.autoreload = false;
    locations[n].reload.l13.label = "House";

    locations[n].reload.l14.name = "houseF2";
    locations[n].reload.l14.go = "Villemstad_Plantation_F1";
    locations[n].reload.l14.emerge = "reload2";
    locations[n].reload.l14.autoreload = false;
    locations[n].reload.l14.label = "House";

    locations[n].locators_radius.quest.detector1 = 5.0; //homo
    n = n + 1;

    ///////////////////////// Дом плантатора /////////////////////////
    locations[n].id = "Villemstad_Plantation_Sp1";
    locations[n].filespath.models = "locations\inside\StoneHouse";
    locations[n].id.label = "Townhall";
    locations[n].image = "loading\inside\stonehouse.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
    //Sound
    locations[n].type = "house";
    //Models
    //Always
    locations[n].models.always.tavern = "StoneHouse";
    locations[n].models.always.tavern.level = 65538;
    locations[n].models.always.window = "StoneHouse_window";
    locations[n].models.always.window.tech = "LocationWindows";
    locations[n].models.always.window.level = 65539;
    locations[n].models.day.locators = "StoneHouse_locators";
    locations[n].models.night.locators = "StoneHouse_Nlocators";

    locations[n].models.always.back = "..\inside_back";
    locations[n].models.always.back.level = 65529;
    //Day
    locations[n].models.day.charactersPatch = "StoneHouse_patch";
    //Night
    locations[n].models.night.charactersPatch = "StoneHouse_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_Plantation";
    locations[n].reload.l1.emerge = "houseSp1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Plantation";

    locations[n].reload.l2.name = "reload2";
    locations[n].reload.l2.go = "Villemstad_Plantation_Sp2";
    locations[n].reload.l2.emerge = "reload1";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "TownhallRoom";
    locations[n].reload.l2.close_for_night = 1;
    n = n + 1;

    ///////////////////////// офис плантатора /////////////////////////
    locations[n].id = "Villemstad_Plantation_Sp2";
    locations[n].id.label = "TownhallRoom";
    locations[n].image = "loading\inside\smallresidence.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
    locations[n].lockWeather = "Inside";
    //Sound
    locations[n].type = "house";
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
    locations[n].reload.l1.go = "Villemstad_Plantation_Sp1";
    locations[n].reload.l1.emerge = "reload2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Townhall";

    n = n + 1;

    ///////////////////////// Бытовка /////////////////////////
    locations[n].id = "Villemstad_Plantation_S1";
    locations[n].filespath.models = "locations\inside\Hut1_KNS";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\hibara.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
    //Sound
    locations[n].type = "house";
    //Models
    //Always
    locations[n].models.always.locators = "Hut1_locators";
    locations[n].models.always.tavern = "Hut1";
    locations[n].models.always.tavern.level = 65538;
    locations[n].models.always.window = "Hut1_window";
    locations[n].models.always.window.tech = "LocationWindows";
    locations[n].models.always.window.level = 65539;
    locations[n].models.always.back = "..\inside_back2";
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
    locations[n].reload.l1.go = "Villemstad_Plantation";
    locations[n].reload.l1.emerge = "houseS1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Plantation";
    n = n + 1;

    ///////////////////////// Бытовка /////////////////////////
    locations[n].id = "Villemstad_Plantation_S2";
    locations[n].filespath.models = "locations\inside\Hut1_KNS";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\littlehut.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
    //Sound
    locations[n].type = "house";
    //Models
    //Always
    locations[n].models.always.locators = "Hut1_locators";
    locations[n].models.always.tavern = "Hut1";
    locations[n].models.always.tavern.level = 65538;
    locations[n].models.always.window = "Hut1_window";
    locations[n].models.always.window.tech = "LocationWindows";
    locations[n].models.always.window.level = 65539;
    locations[n].models.always.back = "..\inside_back2";
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
    locations[n].reload.l1.go = "Villemstad_Plantation";
    locations[n].reload.l1.emerge = "houseS2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Plantation";
    n = n + 1;

    ///////////////////////// Бытовка /////////////////////////
    locations[n].id = "Villemstad_Plantation_G1";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\mediumhouse05.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
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

    locations[n].models.always.back = "..\inside_back";
    locations[n].models.always.back.level = 65529;
    //Day
    Locations[n].models.day.mediumhouse05rand = "mediumhouse05_rand";
    locations[n].models.day.charactersPatch = "mediumhouse05_patch";
    //Night
    locations[n].models.night.charactersPatch = "mediumhouse05_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_Plantation";
    locations[n].reload.l1.emerge = "houseG1";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Plantation";
    n = n + 1;

    ///////////////////////// Бытовка /////////////////////////
    locations[n].id = "Villemstad_Plantation_G2";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\mediumhouse09.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
    //Sound
    locations[n].type = "house";
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
    Locations[n].models.day.mediumhouse09rand = "mediumhouse09_rand";
    locations[n].models.day.charactersPatch = "mediumhouse09_patch";
    //Night
    locations[n].models.night.charactersPatch = "mediumhouse09_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_Plantation";
    locations[n].reload.l1.emerge = "houseG2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Plantation";
    n = n + 1;

    ///////////////////////// Бытовка /////////////////////////
    locations[n].id = "Villemstad_Plantation_G3";
    locations[n].filespath.models = "locations\inside\Hut5";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\Hut5.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
    //Sound
    locations[n].type = "house";
    //Models
    //Always
    locations[n].models.always.locators = "Hut5_locators";
    locations[n].models.always.model = "Hut5";
    locations[n].models.always.model.level = 65538;
    //Day
    locations[n].models.day.charactersPatch = "Hut5_patch";
    //Night
    locations[n].models.night.charactersPatch = "Hut5_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    Locations[n].QuestlockWeather = "23 Hour";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_Plantation";
    locations[n].reload.l1.emerge = "houseG3";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Plantation";
    n = n + 1;

    ///////////////////////// Бытовка /////////////////////////
    locations[n].id = "Villemstad_Plantation_G4";
    locations[n].filespath.models = "locations\inside\Hut4";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\Hut4.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
    //Sound
    locations[n].type = "house";
    //Models
    //Always
    locations[n].models.always.locators = "Hut4_locators";
    locations[n].models.always.model = "Hut4";
    locations[n].models.always.model.level = 65538;
    //Day
    locations[n].models.day.charactersPatch = "Hut4_patch";
    //Night
    locations[n].models.night.charactersPatch = "Hut4_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    Locations[n].QuestlockWeather = "23 Hour";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_Plantation";
    locations[n].reload.l1.emerge = "houseG4";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Plantation";
    n = n + 1;
    ///////////////////////// Бытовка /////////////////////////
    locations[n].id = "Villemstad_Plantation_G5";
    locations[n].filespath.models = "locations\inside\Hut4";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\Hut4.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
    //Sound
    locations[n].type = "house";
    //Models
    //Always
    locations[n].models.always.locators = "Hut4_locators";
    locations[n].models.always.model = "Hut4";
    locations[n].models.always.model.level = 65538;
    //Day
    locations[n].models.day.charactersPatch = "Hut4_patch";
    //Night
    locations[n].models.night.charactersPatch = "Hut4_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    Locations[n].QuestlockWeather = "23 Hour";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_Plantation";
    locations[n].reload.l1.emerge = "houseG5";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Plantation";
    n = n + 1;

    ///////////////////////// Бытовка /////////////////////////
    locations[n].id = "Villemstad_Plantation_G7";
    locations[n].filespath.models = "locations\inside\Hut5";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\Hut5.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
    //Sound
    locations[n].type = "house";
    //Models
    //Always
    locations[n].models.always.locators = "Hut5_locators";
    locations[n].models.always.model = "Hut5";
    locations[n].models.always.model.level = 65538;
    //Day
    locations[n].models.day.charactersPatch = "Hut5_patch";
    //Night
    locations[n].models.night.charactersPatch = "Hut5_patch";
    //Environment
    locations[n].environment.weather = "true";
    locations[n].environment.sea = "false";
    Locations[n].QuestlockWeather = "23 Hour";
    //Reload map
    locations[n].reload.l1.name = "reload1";
    locations[n].reload.l1.go = "Villemstad_Plantation";
    locations[n].reload.l1.emerge = "houseG7";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Plantation";

    n = n + 1;

    ///////////// Дом из трёх комнат (комнаты 1, 2) //////////////
    locations[n].id = "Villemstad_Plantation_F1";
    locations[n].id.label = "House";
    locations[n].image = "loading\inside\mediumhouse11.tga";
    //Town sack
    locations[n].townsack = "Villemstad";
    locations[n].islandId = "Curacao";
    //Sound
    locations[n].type = "house";
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
    locations[n].lockWeather = "Inside";
    locations[n].environment.sea = "false";
    //Reload map
    locations[n].reload.l2.name = "reload1";
    locations[n].reload.l2.go = "Villemstad_Plantation";
    locations[n].reload.l2.emerge = "houseF1";
    locations[n].reload.l2.autoreload = "0";
    locations[n].reload.l2.label = "Plantation";

    locations[n].reload.l1.name = "reload2";
    locations[n].reload.l1.go = "Villemstad_Plantation";
    locations[n].reload.l1.emerge = "houseF2";
    locations[n].reload.l1.autoreload = "0";
    locations[n].reload.l1.label = "Plantation";

    n = n + 1;

    return n;
}

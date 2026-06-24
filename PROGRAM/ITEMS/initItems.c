// KZ > ref 07.04.2024

int InitItems()
{
	InitRandItems();
	ref itm;
	int n;

	for (n = 0; n < ITEMS_QUANTITY; n++)
	{
		makeref(itm, Items[n]);
		DeleteAttribute(&itm, "");
		itm.id = "empty_item_" + (n + 1);
		itm.describe = "";
		itm.name = "";
		itm.index = n;
		itm.model = "";
		itm.shown = "0";
		itm.startLocation = "";
		itm.startLocator = "";
		itm.useLocation = "";
		itm.useLocator = "";
		itm.Weight = 0.0;
		itm.price = 1;
		itm.uniq = "0";
		itm.ItemType = "VARIETY";
	}

	n = 0; // в начале идут все без заполнения трупов

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ПАТЕНТЫ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	n = InitPatents(n,	"eng",	ENGLAND);	// каперский патент Англии
	n = InitPatents(n,	"fra",	FRANCE);	// каперский патент Франции
	n = InitPatents(n,	"spa",	SPAIN);		// каперский патент Испании
	n = InitPatents(n,	"hol",	HOLLAND);	// каперский патент Голландии

	// >-----------------------------------------------------> WEAPONS >---------------------------------------------------->

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ЛЁГКОЕ ОРУЖИЕ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// предмет исключён из обычного спавна при: rare <= 0.0 или quality "excellent"/"unique"
	//																						block						minlevel	dmg_min.min.gen			dmg_max.max.gen			quality
	//									picIndex										piercing								price.gen			dmg_max.min.gen			weight.max.gen
	//			index	id					picTexture	blade type		dmg_min	dmg_max			weight	price	rare		qty.gen			dmg_min.max.gen			weight.min.gen					wType
	n = InitBlades(n,	"unarmed",		11,	"ITEMS_1",	"FencingLight",	1.0,	15.0,	1,	0,	0.0,	1,		0.0,	0,	0,	0,	1.0,	1.0,	15.0,	15.0,	0.0,	0.0,	"", 			"");						// "Безоружный"
	n = InitBlades(n,	"kocherg",		11,	"ITEMS_10",	"FencingLight",	1.0,	25.0,	5,	19,	4.0,	5,		0.1,	0,	0,	0,	1.0,	4.0,	25.0,	27.0,	2.0,	3.0,	"poor", 		"");						// "Кочерга"
	n = InitBlades(n,	"spear1",		5,	"ITEMS_21",	"FencingLight",	11.0,	36.0,	20,	15,	3.0,	250,	0.0,	0,	10,	1,	10.0,	12.0,	37.0,	39.0,	2.8,	3.1,	"poor", 		"indian");					// "Нааб-Те"
	n = InitBlades(n,	"spear2",		6,	"ITEMS_21",	"FencingLight",	8.0,	30.0,	20,	15,	3.0,	100,	0.1,	0,	10,	1,	7.0,	10.0,	30.0,	32.0,	2.0,	2.5,	"poor", 		"slave");					// "Гарпун"
	n = InitBlades(n,	"blade5",		9,	"ITEMS_6",	"FencingLight",	3.0,	10.0,	25,	5,	0.9,	90,		0.1,	0,	10,	1,	1.0,	4.0,	8.0,	17.0,	0.8,	1.0,	"poor",			"common");					// "Дага"
	n = InitBlades(n,	"blade2",		10,	"ITEMS_6",	"FencingLight",	7.0,	41.0,	15,	10,	2.9,	120,	0.1,	0,	10,	1,	5.0,	10.0,	40.0,	43.0,	2.8,	3.0,	"poor", 		"common,officer,solder");	// "Венецианская рапира"
	n = InitBlades(n,	"blade6",		12,	"ITEMS_6",	"FencingLight",	11.0,	48.0,	15,	15,	2.8,	460,	0.1,	1,	10,	1,	10.0,	12.0,	46.0,	50.0,	2.7,	2.9,	"ordinary", 	"common,officer,solder");	// "Дворянская шпага"
	n = InitBlades(n,	"blade9",		2,	"ITEMS_3",	"FencingLight",	11.0,	50.0,	20,	15,	2.7,	600,	0.1,	1,	10,	1,	10.0,	12.0,	48.0,	51.0,	2.5,	2.9,	"ordinary", 	"common,officer,solder");	// "Сайдсворд"
	n = InitBlades(n,	"blade19",		12,	"ITEMS_3",	"FencingLight",	13.0,	54.0,	20,	60,	2.6,	700,	0.001,	1,	15,	1,	12.0,	14.0,	53.0,	55.0,	2.5,	2.7,	"good",			"officer,cool");			// "Золингенская рапира"
	n = InitBlades(n,	"blade22",		15,	"ITEMS_3",	"FencingLight",	13.0,	54.0,	44,	73,	2.6,	900,	0.001,	1,	15,	1,	12.0,	14.0,	53.0,	55.0,	2.5,	2.7,	"good", 		"officer,cool");			// "Конкилья"
	n = InitBlades(n,	"blade23",		16,	"ITEMS_3",	"FencingLight",	17.0,	60.0,	50,	75,	2.5,	1300,	0.001,	1,	15,	1,	16.0,	18.0,	56.0,	65.0,	2.4,	2.6,	"excellent", 	"cool");					// "Бретта"
	n = InitBlades(n,	"blade27",		3,	"ITEMS_8",	"FencingLight",	18.0,	65.0,	99,	99,	2.5,	12000,	0.0001,	1,	3,	1,	17.0,	19.0,	64.0,	68.0,	2.4,	2.6,	"unique", 		"");						// "Моргана"
	n = InitBlades(n,	"blade14",		7,	"ITEMS_3",	"FencingLight",	20.0,	66.0,	20,	60,	3.0,	18000,	0.0,	1,	0,	0,	20.0,	20.0,	66.0,	66.0,	3.0,	3.0,	"unique", 		"");						// "Катана"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													СРЕДНЕЕ ОРУЖИЕ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//									picIndex											block						minlevel	dmg_min.min.gen			dmg_max.max.gen			quality
	//					id								blade type						piercing		price					price.gen			dmg_max.min.gen			weight.max.gen
	//			index						picTexture					dmg_min	dmg_max			weight			rare		qty.gen			dmg_min.max.gen			weight.min.gen					wType
	n = InitBlades(n,	"blade1",		11,	"ITEMS_6",	"Fencing",		8.0,	46.0,	10,	5,	5.0,	50,		0.1,	0,	10,	1,	6.0,	12.0,	45.0,	50.0,	4.5,	6.0,	"poor", 		"common,solder");			// "Канонирский тесак"
	n = InitBlades(n,	"blade4",		7,	"ITEMS_6",	"Fencing",		9.0,	47.0,	30,	1,	5.1,	100,	0.1,	0,	10,	1,	6.0,	12.0,	45.0,	50.0,	4.5,	6.0,	"poor", 		"common,solder");			// "Кавалерийская сабля"
	n = InitBlades(n,	"vikingSword",	3,	"ITEMS_3",	"Fencing",	    10.0,	52.0,	50,	10,	4.0,	300,	0.0,	1,	10,	1,	7.0,	8.0,	49.0,	50.0,	4.5,	5.0,	"poor", 		"common");					// "Меч викинга"
	n = InitBlades(n,	"blade37",		7,	"ITEMS_21",	"Fencing",		9.0,	47.0,	14,	2,	4.8,	150,	0.1,	0,	10,	1,	7.0,	11.0,	44.0,	49.0,	3.5,	4.5,	"poor", 		"common");					// "Мачете"
	n = InitBlades(n,	"topor3",		8,	"ITEMS_10",	"Fencing",		9.0,	50.0,	14,	2,	5.2,	150,	0.01,	1,	10,	1,	6.0,	14.0,	48.0,	55.0,	4.7,	5.9,	"poor", 		"common");					// "Клевец"
	n = InitBlades(n,	"blade3",		8,	"ITEMS_6",	"Fencing",		10.0,	49.0,	60,	5,	5.2,	200,	0.1,	0,	10,	1,	7.0,	12.0,	45.0,	50.0,	4.5,	5.4,	"poor", 		"common,solder");			// "Катласс"
	n = InitBlades(n,	"blade7",		13,	"ITEMS_6",	"Fencing",		13.0,	53.0,	18,	5,	4.5,	250,	0.1,	1,	10,	1,	12.0,	14.0,	52.0,	55.0,	4.0,	4.6,	"ordinary", 	"common,officer,solder");	// "Бильбо"
	n = InitBlades(n,	"blade12",		5,	"ITEMS_3",	"Fencing",		13.0,	54.0,	30,	20,	4.0,	300,	0.1,	1,	10,	1,	11.0,	15.0,	51.0,	56.0,	3.9,	4.2,	"ordinary", 	"common,officer");			// "Катцбальгер"
	n = InitBlades(n,	"blade18",		11,	"ITEMS_3",	"Fencing",		13.0,	54.0,	35,	35,	4.8,	400,	0.1,	1,	10,	1,	10.0,	16.0,	52.0,	57.0,	4.5,	4.8,	"ordinary", 	"common,officer");			// "Хангер"
	n = InitBlades(n,	"topor5",		8,	"ITEMS_21",	"Fencing",	    10.0,	57.0,	50,	2,	5.3,	500,	0.0,	0,	10,	1,	9.0,	15.0,	54.0,	60.0,	5.0,	5.7,	"ordinary", 	"indian");					// "Томагавк"
	n = InitBlades(n,	"blade_maltes",	5,	"ITEMS_14",	"Fencing",	    17.0,	57.0,	30,	30,	4.4,	700,	0.001,	5,	10,	1,	16.0,	18.0,	56.0,	58.0,	4.3,	4.5,	"good", 		"officer");					// "Мальтийский меч"

	n = InitBlades(n,	"blade31",		3,	"ITEMS_10",	"Fencing",		23.0,	64.0,	50,	65,	4.7,	800,	0.001,	1,	15,	1,	18.0,	25.0,	59.0,	65.0,	4.6,	4.8,	"good", 		"officer,cool");			// "Шамшир"
	n = InitBlades(n,	"blade34",		5,	"ITEMS_10",	"Fencing",		20.0,	61.0,	90,	70,	4.4,	1000,	0.001,	1,	15,	1,	19.0,	22.0,	60.0,	63.0,	4.3,	4.5,	"good", 		"officer,cool");			// "Скаллоп"
	n = InitBlades(n,	"blade30",		2,	"ITEMS_10",	"Fencing",		22.0,	67.0,	55,	40,	4.2,	1200,	0.0001,	1,	15,	1,	20.0,	25.0,	65.0,	70.0,	4.1,	4.5,	"excellent", 	"cool");					// "Нобиль"
	n = InitBlades(n,	"blade24",		5,	"ITEMS_8",	"Fencing",		22.0,	67.0,	58,	45,	4.3,	1500,	0.001,	1,	15,	1,	20.0,	25.0,	65.0,	70.0,	4.1,	4.5,	"excellent", 	"cool");					// "Скьявона"
	n = InitBlades(n,	"blade25",		1,	"ITEMS_8",	"Fencing",		23.0,	67.0,	60,	70,	4.2,	1700,	0.0001,	1,	15,	1,	20.0,	25.0,	65.0,	70.0,	4.1,	4.5,	"excellent", 	"cool");					// "Карабела"
	n = InitBlades(n,	"blade32",		4,	"ITEMS_10",	"Fencing",		26.0,	68.0,	90,	92,	4.3,	3000,	0.0001,	1,	15,	1,	24.0,	27.0,	67.0,	72.0,	4.2,	4.6,	"excellent", 	"cool");					// "Фламберж"
	n = InitBlades(n,	"blade26",		2,	"ITEMS_8",	"Fencing",		24.0,	73.0,	88,	72,	4.2,	2500,	0.0001,	1,	5,	1,	22.0,	26.0,	72.0,	74.0,	4.1,	4.3,	"unique", 		"");						// "Паппенхаймер"
	n = InitBlades(n,	"RapierReCon",  4,	"ITEMS_15",	"Fencing",		20.0,	57.0,	40,	72,	3.9,	2000,	0.0001,	1,	1,	1,	20.0,	21.0,	56.0,	58.0,	3.8,	4.1,	"unique", 		"");						// "DLC Support Pack"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ТЯЖЁЛОЕ ОРУЖИЕ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										picIndex											block						minlevel	dmg_min.min.gen			dmg_max.max.gen			quality
	//					id									blade type						piercing		price					price.gen			dmg_max.min.gen			weight.max.gen
	//			index							picTexture					dmg_min	dmg_max			weight			rare		qty.gen			dmg_min.max.gen			weight.min.gen					wType
	n = InitBlades(n,	"blade10",			3,	"ITEMS_3",	"FencingHeavy",	9.5,	50.0,	65,	25,	9.3,	300,	0.1,	1,	10,	1,	8.0,	10.0,	45.0,	57.0,	8.8,	9.5,	"poor", 		"common,solder");		// "Фальшион"
	n = InitBlades(n,	"blade35",			10,	"ITEMS_10",	"FencingHeavy",	8.5,	53.0,	50,	10,	9.0,	350,	0.1,	1,	10,	1,	8.0,	9.0,	48.0,	60.0,	8.3,	9.0,	"poor", 		"common,solder");		// "Корделас"
	n = InitBlades(n,	"topor1",			6,	"ITEMS_10",	"FencingHeavy",	7.5,	55.0,	70,	3,	8.5,	650,	0.1,	1,	10,	1,	8.0,	8.0,	50.0,	62.0,	8.0,	8.9,	"poor", 		"common");				// "Боевой топор"
	n = InitBlades(n,	"blade17",			10,	"ITEMS_3",	"FencingHeavy",	10.0,	57.0,	65,	10,	11.5,	900,	0.1,	1,	10,	1,	10.0,	14.0,	49.0,	64.0,	10.0,	12.5,	"poor", 		"common");				// "Клеймор"
	n = InitBlades(n,	"vikingAxe",		6,	"ITEMS_10",	"FencingHeavy",	6.5,	51.0,	70,	3,	7.5,	650,	0.0,	1,	10,	1,	6.0,	7.0,	50.0,	55.0,	6.2,	7.9,	"poor", 		"viking");				// "Топор викинга"
	n = InitBlades(n,	"blade8",			1,	"ITEMS_3",	"FencingHeavy",	11.0,	66.0,	35,	20,	9.1,	450,	0.1,	1,	10,	1,	12.0,	12.0,	64.0,	70.0,	8.5,	9.7,	"ordinary", 	"common,officer");		// "Госсемесер"
	n = InitBlades(n,	"blade11",			4,	"ITEMS_3",	"FencingHeavy",	12.0,	62.0,	60,	25,	8.0,	500,	0.1,	1,	10,	1,	12.0,	13.0,	61.0,	66.0,	7.7,	8.1,	"ordinary", 	"common,officer");		// "Риттершверт"
	n = InitBlades(n,	"blade16",			9,	"ITEMS_3",	"FencingHeavy",	13.0,	64.0,	45,	35,	8.5,	800,	0.1,	1,	10,	1,	12.0,	14.0,	62.0,	67.0,	8.3,	9.0,	"ordinary", 	"common,officer");		// "Кирасирский палаш"
	n = InitBlades(n,	"topor4",			9,	"ITEMS_21",	"FencingHeavy",	11.0,	68.0,	45,	35,	9.7,	850,	0.1,	1,	10,	1,	11.0,	19.0,	64.0,	75.0,	9.5,	10.6,	"ordinary", 	"indian");				// "Гансток"
	n = InitBlades(n,	"blade15",			8,	"ITEMS_3",	"FencingHeavy",	21.0,	78.0,	55,	25,	7.5,	900,	0.1,	1,	15,	1,	18.0,	20.0,	80.0,	83.0,	7.1,	8.5,	"good", 		"officer,cool");		// "Сторта"
	n = InitBlades(n,	"blade21",			14,	"ITEMS_3",	"FencingHeavy",	18.0,	85.0,	75,	25,	9.0,	1100,	0.1,	1,	15,	1,	18.0,	19.0,	85.0,	90.0,	8.5,	9.5,	"good", 		"officer,cool");		// "Бастард"
	n = InitBlades(n,	"blade13",			6,	"ITEMS_3",	"FencingHeavy",	25.0,	95.0,	65,	20,	8.1,	1300,	0.1,	1,	15,	1,	25.0,	26.0,	90.0,	95.0,	7.8,	8.3,	"excellent",	"cool");				// "Кракемарт"
	n = InitBlades(n,	"blade20",			13,	"ITEMS_3",	"FencingHeavy",	26.0,	95.0,	65,	30,	9.0,	1400,	0.1,	1,	15,	1,	25.0,	26.0,	90.0,	100.0,	9.0,	9.5,	"excellent", 	"cool");				// "Клейбэг"
	n = InitBlades(n,	"blade33",			9,	"ITEMS_10",	"FencingHeavy",	23.0,	92.0,	70,	60,	7.0,	1500,	0.001,	1,	15,	1,	22.0,	24.0,	92.0,	93.0,	6.7,	7.3,	"excellent", 	"cool");				// "Хаудеген"
	n = InitBlades(n,	"maquahuitl",		12,	"ITEMS_13",	"FencingHeavy",	29.0,	117.0,	95,	30,	9.0,	17500,	0.0001,	1,	15,	1,	28.0,	30.0,	110.0,	119.0,	8.5,	9.5,	"excellent", 	"cool");				// "Макуауитль"
	n = InitBlades(n,	"topor2",			7,	"ITEMS_10",	"FencingHeavy",	19.0,	123.0,	95,	20,	8.0,	6500,	0.0001,	1,	15,	1,	19.0,	20.0,	115.0,	125.0,	8.5,	9.0,	"excellent", 	"cool");				// "Кавалерийский топор"
	n = InitBlades(n,	"blade28",			16,	"ITEMS_10",	"FencingHeavy",	36.0,	109.0,	85,	75,	7.3,	3000,	0.0001,	1,	5,	1,	35.0,	37.0,	107.0,	113.0,	7.0,	8.0,	"unique", 		"");					// "Фламмард"
	n = InitBlades(n,	"vikingHeroSword",	2,  "ITEMS_15", "FencingHeavy",	100.0,	115.0,	85,	75,	9.5,	20000,	0.0,	1,	5,	1,	99.0,	101.0,	112.0,	120.0,	8.4,	8.7,	"unique", 		"");					// "Дайнслейф"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ОГНЕСТРЕЛЬНОЕ ОРУЖИЕ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//		 index	id					groupID				picIndex	picTexture	dmg_min dmg_max accuracy	chargeQ	chargespeed	weight	price	rare	minlevel	quality			wType
	/// ПИСТОЛЕТЫ >
	n = InitGuns(n,	"pistol1",			GUN_ITEM_TYPE,		1,			"ITEMS_6",	20.0,	100.0,	30.0,		1,		8.0,		3.0,	100,	0.1,	1,			"poor", 		"poor,common");		// "Пистоль"
	n = InitGuns(n,	"pistol2",			GUN_ITEM_TYPE,		2,			"ITEMS_6",	30.0,	120.0,	50.0,		1,		12.0,		4.0,	400,	0.05,	1,			"ordinary", 	"common,officer");	// "Колониальный пистолет"
	n = InitGuns(n,	"pistol3",			GUN_ITEM_TYPE,		3,			"ITEMS_6",	50.0,	175.0,	20.0,		1,		22.0,		6.0,	800,	0.005,	1,			"ordinary", 	"common,officer");	// "Тромбон"
	n = InitGuns(n,	"pistol6",			GUN_ITEM_TYPE,		6,			"ITEMS_6",	35.0,	130.0,	60.0,		2,		20.0,		5.0,	3600,	0.001,	1,			"good", 		"officer,cool");	// "Бок-пистолет"
	n = InitGuns(n,	"pistol5",			GUN_ITEM_TYPE,		5,			"ITEMS_6",	45.0,	170.0,	80.0,		1,		16.0,		3.0,	3800,	0.0001,	1,			"excellent", 	"cool");			// "Бретерский пистолет"
	n = InitGuns(n,	"pistol4",			GUN_ITEM_TYPE,		4,			"ITEMS_6",	40.0,	140.0,	60.0,		4,		28.0,		6.0,	5000,	0.0001,	1,			"excellent", 	"cool");			// "Четырёхствольный пистолет"
	n = InitGuns(n,	"pistol7",			GUN_ITEM_TYPE,		16,			"ITEMS_8",	100.0,	250.0,	80.0,		5,		52.0,		9.0,	25000,	0.0,	1,			"unique", 		"");				// "Револьвер Коллиера"
	/// ПИСТОЛЕТЫ <

	/// МУШКЕТЫ >
	n = InitGuns(n,	"mushket_poor",		MUSKET_ITEM_TYPE,	10,			"ITEMS_14",	55.0,	195.0,	60.0,		1,		15.0,		15.0,	5700,	0.1,	1,			"poor", 		"poor,common");		// "Старый мушкет"
	n = InitGuns(n,	"mushket",			MUSKET_ITEM_TYPE,	12,			"ITEMS_10",	80.0,	250.0,	75.0,		1,		13.0,		13.0,	10000,	0.01,	1,			"ordinary", 	"common,officer");	// "Фитильный мушкет"
	n = InitGuns(n,	"mushket_flint",	MUSKET_ITEM_TYPE,	9,			"ITEMS_14",	100.0,	275.0,	85.0,		1,		11.0,		11.0,	15000,	0.001,	1,			"good", 		"officer,cool");	// "Кремнёвый мушкет"
	n = InitGuns(n,	"mushket_indian",	MUSKET_ITEM_TYPE,	7,			"ITEMS_14",	95.0,	290.0,	95.0,		1,		10.0,		15.0,	100000,	0.0,	10,			"unique", 		"");				// "Мушкет Тичингиту"
	n = InitGuns(n,	"mushket_H2",		MUSKET_ITEM_TYPE,	8,			"ITEMS_14",	100.0,	270.0,	85.0,		2,		12.0,		14.0,	50000,	0.0001,	15,			"excellent", 	"cool");			// "Двуствольный мушкет"
	n = InitGuns(n,	"mushket2x2",		MUSKET_ITEM_TYPE,	16,			"ITEMS_13",	90.0,	290.0,	80.0,		2,		12.0,		17.0,	100000,	0.0,	20,			"unique", 		"");				// "Двуствольный мушкет" Хэмфри Дугласа
	/// МУШКЕТЫ <

	/// РАЗНОЕ >
	n = InitGuns(n,	"mortar",			MUSKET_ITEM_TYPE,	6,			"ITEMS_8",	100.0,	200.0,	100.0,		1,		50.0,		9.0,	100000,	0.0,	25,			"unique",		"");				// "Склопетта" > статы из ККС (по большей части)
	/// РАЗНОЕ <
	// предмет исключён из обычного спавна при: rare <= 0.0 или quality "excellent"/"unique"

	// <-----------------------------------------------------< WEAPONS <----------------------------------------------------<

	////////////////////////////////////////////////////////////////////////////////////////////
	// --> Заскриптованные предметы ТОЛЬКО ЗДЕСЬ
	////////////////////////////////////////////////////////////////////////////////////////////
	iScriptItemStartNum = n; // Начальный номер заскриптованных предметов
	iScriptItemEndNum = n; // Конечный номер заскриптованных предметов
	iScriptItemCount = iScriptItemStartNum-iScriptItemEndNum; // Всего заскриптованных предметов
	////////////////////////////////////////////////////////////////////////////////////////////
	// <-- Заскриптованные предметы ТОЛЬКО ЗДЕСЬ
	////////////////////////////////////////////////////////////////////////////////////////////

	// >---------------------------------------------------> QUEST ITEMS >-------------------------------------------------->

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													КВЕСТОВЫЕ ПРЕДМЕТЫ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//												picIndex
	//				index	id							picTexture	price	weight	model		itemtype	groupID
	n = InitQuestItems(n,	"gold",					2,	"ITEMS_4",	0,		0.0,	"",			"VARIETY",	"");
	n = InitQuestItems(n,	"Chest",				1,	"ITEMS_4",	15000,	15.0,	"stat1",	"VARIETY",	"");
	n = InitQuestItems(n,	"Coins",				15,	"ITEMS_4",	6666,	0.1,	"purse",	"",			"");
	n = InitQuestItems(n,	"fire",					1,	"HIGHLIGHT",0,		0.2,	"Bfire",	"",			"");
	n = InitQuestItems(n,	"letter_1",				10,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_2",				11,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_open",			16,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_notes",			9,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"leather_bag",			2,	"ITEMS_14",	0,		8.0,	"",			"",			"");
	n = InitQuestItems(n,	"Order",				15,	"ITEMS_8",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_Albermal",		7,	"ITEMS_12",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"EngTradeLicence",		14,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"FraTradeLicence",		4,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"SpaTradeLicence",		7,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"HolTradeLicence",		13,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"Trust",				3,	"ITEMS_9",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"sicretLetter",			8,	"ITEMS_12",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"mapQuest",				2,	"ITEMS_7",	0,		0.1,	"",			"",			MAPS_ITEM_TYPE);
	n = InitQuestItems(n,	"LegransMap",			1,	"ITEMS_10",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"Bible",				6,	"ITEMS_9",	0,		2.0,	"",			"",			"");
	n = InitQuestItems(n,	"ShipsJournal",			8,	"ITEMS_4",	0,		2.0,	"",			"",			"");
	n = InitQuestItems(n,	"MapsAtlas",			1,	"ITEMS_14",	0,		0.0,	"",			"",			MAPS_ITEM_TYPE);
	n = InitQuestItems(n,	"Powder_mummie",		1,	"ITEMS_12",	0,		0.5,	"pursel",	"",			"");
	n = InitQuestItems(n,	"DeSouzaCross",			5,	"ITEMS_12",	0,		0.3,	"sapphire",	"",			"");				// (+15 Везение, +10 Лидерство, +5 Коммерция)
	n = InitQuestItems(n,	"DOjeronRing",			2,	"ITEMS_9",	0,		0.3,	"RingJew",	"",			"");
	n = InitQuestItems(n,	"BlackLabel",			4,	"ITEMS_8",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"Term_arm",				2,	"ITEMS_12",	0,		5.5,	"pursel",	"",			"");
	n = InitQuestItems(n,	"Malyava",				10,	"ITEMS_12",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"PortmansBook",			9,	"ITEMS_1",	0,		0.2,	"",			"",			"");
	n = InitQuestItems(n,	"Griffins_Weapon",		14,	"ITEMS_13",	0,		3.4,	"",			"",			"");
	n = InitQuestItems(n,	"Weapon_for_escape",	13,	"ITEMS_13",	0,		10.0,	"",			"",			"");
	n = InitQuestItems(n,	"Cursed_idol",			3,	"ITEMS_14",	0,		1.0,	"stat1",	"",			"");				// (-80 Везение)
	n = InitQuestItems(n,	"PDM_PJ_Vino",			6,	"ITEMS_1",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"PDM_PJ_Rom",			3,	"ITEMS_1",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"PDM_PJ_BsRL",			4,	"ITEMS_14",	1000,	0.2,	"",			"",			"");				// (+2 Везение, +2 Коммерция, -2 Скрытность)
	n = InitQuestItems(n,	"letter_A",				10,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"PDM_PK_Koltso",		6,	"ITEMS_14",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"Litsenzia",			13,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"FQ_letter1",			15,	"ITEMS_8",	0,		0.0,	"",			"",			READING_ITEM_TYPE);
	n = InitQuestItems(n,	"LogbookLSC",			9,	"ITEMS_1",	0,		0.2,	"",			"",			READING_ITEM_TYPE);
	n = InitQuestItems(n,	"keyForCryptLSC",		13,	"ITEMS_12",	0,		0.0,	"",			"",			"");
	n = InitQuestItems(n,	"letter_church",		14,	"ITEMS_14",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"prayer_book",			15,	"ITEMS_14",	0,		1.0,	"",			"",			"");
	n = InitQuestItems(n,	"encyclopedia",			16,	"ITEMS_14",	0,		0.0,	"",			"",			"");
	n = InitQuestItems(n,	"encyclopedia_page",	10,	"ITEMS_12",	10000,	0.0,	"",			"",			"");
	n = InitQuestItems(n,	"key_drinkQ",			13,	"ITEMS_12",	0,		0.1,	"keymiddle","",			"");
	n = InitQuestItems(n,	"bequestLSC",			3,	"ITEMS_9",	0,		0.1,	"letter",	"",			"");
	n = InitQuestItems(n,	"letter_LSC_2",			16,	"ITEMS_4",	0,		0.1,	"letter",	"",			READING_ITEM_TYPE);
	n = InitQuestItems(n,	"letter_EngLineQ4",		10,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_open_EngLineQ4",16,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_EngLineQ8",		11,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_open_EngLineQ8",16,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"ChurchManuscript",		6,	"ITEMS_9",	0,		2.0,	"",			"",			"");
	n = InitQuestItems(n,	"TizerKey",				15,	"ITEMS_12",	0,		0.0,	"keymiddle","",			"");
	n = InitQuestItems(n,	"ChurchCup",			9,	"ITEMS_7",	0,		15.0,	"",			"",			"");
	n = InitQuestItems(n,	"letter_HolLineQ7_1",	10,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_FraLineQ1",		10,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_FraLineQ6",		10,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"Trust_HolLineQ2",		3,	"ITEMS_9",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_HolLineQ3",		10,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_HolLineQ7_2",	11,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_SpaLineQ10",	10,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"Andre_Abel_Letter_1",	10,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"Andre_Abel_Letter_2",	10,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"pirateStartQuest",		16,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"letter_FraLineQ3",		16,	"ITEMS_4",	0,		0.1,	"",			"",			"");
	n = InitQuestItems(n,	"AscoldInventoryList",	8,	"ITEMS_4",	0,		2.0,	"",			"",			"");
	n = InitQuestItems(n,	"RingNarval",			12,	"ITEMS_4",	0,		0.3,	"RingJew",	"",			"");
	n = InitQuestItems(n,	"HugtorpRing",			15,	"ITEMS_13",	0,		0.3,	"",			"",			"");
	n = InitQuestItems(n,	"shark_tooth",			13,	"ITEMS_14",	0,	    0.1,	"pursel",	"",			""); // "Акулий Зуб"
	n = InitQuestItems(n,	"DesMoinesLocies",		14,	"ITEMS_9",	0,	    0.1,	"",			"",			""); // Лоция поселения Дес-Мойнес
	n = InitQuestItems(n,	"HolFakeLicence",		13,	"ITEMS_4",	0,		0.1,	"",			"",			""); // фальш патент
	n = InitQuestItems(n,	"strangeNoteLSC",		10,	"ITEMS_4",	0,		0.1,	"",			"",			READING_ITEM_TYPE); //записка тизера
	n = InitQuestItems(n,	"TizerJournal",			6,	"ITEMS_9",	0,		0.2,	"",			"",			""); // дневник Тизера (становится читабельным позже по квесту)
	n = InitQuestItems(n,	"recon_potion",			3,	"ITEMS_15",	0,		0.4,	"balsam",	"",			""); // ром "ReConstruction"
	n = InitQuestItems(n,	"instrument1",			10,	"ITEMS_15",	1000,	0.2,	"ToolBox",	"VARIETY",	""); // отличная пила (+5 починка)

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	далее начинаются квестовые предметы, заюзаные в локаторах item
	//	оформлять эти предметы ТОЛЬКО ЗДЕСЬ, до конца сектора квестовых предметов
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ItemsForLocators_start = n;		// > начальный номер для спецпредметов

	//						index	id					picIndex	picTexture		price	weight	model			itemtype	shown	useLocation			 groupID   useLocator	startLocator			startLocation
	n = InitQuestItemsLocator(n,	"Rock_letter",		6,			"ITEMS_4",		0,		0.2,	"StoneMap",		"",			0,		"Guadeloupe_Cave",	 "",	   "button01",	"item"+(rand(2)+1),		GetRandSubString("Pearl_Grot,Caiman_Grot,Terks_Grot,Dominica_Grot,Temple"));
	n = InitQuestItemsLocator(n,	"Azzy_bottle",		3,			"ITEMS_12",		0,		2.5,	"pursel",		"",			1,		"",					 "",	   "button01",	"",						"");
	n = InitQuestItemsLocator(n,	"ShipyardsMap",		11,			"ITEMS_12",		0,		0.1,	"shipyardsMap",	"",			-1,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"CaptainBook",		11,			"ITEMS_12",		0,		0.1,	"shipyardsMap",	"",			-1,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"RingCapBook",		8,			"ITEMS_4",		0,		1.0,	"OpenBook",		"",			-1,		"",	  READING_ITEM_TYPE,	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"MayorsRing",		2,			"ITEMS_9",		0,		0.3,	"RingSimGold",	"",			-1,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"UsurersJew",		2,			"ITEMS_2",		0,		0.1,	"Diamond",		"",			-1,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"OpenBook",			8,			"ITEMS_4",		0,		0.2,	"OpenBook",		"",			0,		"",					 "",	   "",			"item1",				"PuertoPrincipe_townhall");
	n = InitQuestItemsLocator(n,	"LesopilkaDoc",		3,			"ITEMS_4",		0,		0.2,	"OpenBook",		"",			0,		"",					 "",	   "",			"",			 			"");
	n = InitQuestItemsLocator(n,	"LesopilkaLog",		9,			"ITEMS_1",		0,		0.2,	"OpenBook",		"",			-1,		"",	  READING_ITEM_TYPE,	   "",			"",			 			"");
	n = InitQuestItemsLocator(n,	"Ladder",			12,			"ITEMS_12",		0,		5.0,	"Ladder",		"",			-1,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"key1",				13,			"ITEMS_12",		0,		0.0,	"keysimple",	"",			-1,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"key2",				14,			"ITEMS_12",		0,		0.0,	"keymiddle",	"",			-1,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"key3",				15,			"ITEMS_12",		0,		0.0,	"keygrand",		"",			-1,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"keyPanama",		15,			"ITEMS_12",		0,		0.0,	"keygrand",		"",			-1,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"keyQuestLSC",		15,			"ITEMS_12",		0,		0.0,	"keymiddle",	"",			0,		"",					 "",	   "",			"item2",				"Villemstad_houseSp5");
	n = InitQuestItemsLocator(n,	"keyMorgan",		15,			"ITEMS_12",		0,		0.0,	"keygrand",		"",			-1,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"letter_LSC",		16,			"ITEMS_4",		0,		0.1,	"letter",		"",			-1,		"",	  READING_ITEM_TYPE,	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"migraine_potion",	4,			"ITEMS_12",		0,		0.4,	"balsam",		"",			0,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"MsStid_ring",		8,			"ITEMS_1",		0,		0.2,	"RingJew",		"",			0,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"Pinion",			16,			"ITEMS_12",		0,		0.1,	"Pinion",		"",			1,		"",					 "",	   "",			"item" + (rand(4)+1),	"UnderWater");
	n = InitQuestItemsLocator(n,	"Ascold_rabble",	9,			"ITEMS_12",		0,		1.0,	"kocherg",		"",			0,		"Guadeloupe_Cave",	 "",	   "button02",	"",						"");
	n = InitQuestItemsLocator(n,	"SkullAztec",		16,			"ITEMS_AZTEC",	100000,	0.3,	"SkullAztec",	"",			1,		"",					 "",	   "",			"item1",				"Temple_great");	// (-10 Везение, +15 Лидерство)
	n = InitQuestItemsLocator(n,	"KnifeAztec",		11,			"ITEMS_13",		25000,	0.3,	"KnifeAztec",	"",			0,		"Tenochtitlan",		 "",	   "button01",	"",						"");				// (-10 Огнестрельное оружие, -10 во все остальные типы оружия)
	n = InitQuestItemsLocator(n,	"WeddingRing",		10,			"ITEMS_1",		0,		0.3,	"RingJew",		"",			0,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"key_drink",		13,			"ITEMS_12",		0,		0.1,	"keymiddle",	"",			1,		"VelascoBank",		 "",	   "key1",		"",						"");
	n = InitQuestItemsLocator(n,	"admiralKey",		15,			"ITEMS_12",		0,		0.0,	"keygrand",		"",			-1,		"",					 "",	   "",			"",						"");
	n = InitQuestItemsLocator(n,	"letter_LSC_1",		16,			"ITEMS_4",		0,		0.1,	"letter",		"",			-1,		"",	  READING_ITEM_TYPE,	   "",			"",						"");

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ТОТЕМЫ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	Totems_start = n; // > для проверки тотемов начальный номер
	//								picIndex
	//			index	id				startLocation				useLocation		useLocator
	n = InitTotems(n,	"Totem_1",	10,	"Shore_ship1",				"Temple_1",		"");			// "Тотем Шочикецаль"
	n = InitTotems(n,	"Totem_2",	9,	"Shore55",					"Temple_2",		"");			// "Тотем Миктлантекутли"
	n = InitTotems(n,	"Totem_3",	7,	"Marigo_Cave",				"Temple_3",		"");			// "Тотем Кецалькоатля"
	n = InitTotems(n,	"Totem_4",	8,	"PortSpein_town",			"Temple_4",		"");			// "Тотем Мишкоатля"
	n = InitTotems(n,	"Totem_5",	6,	"FortFrance_Dungeon",		"Temple_5",		"");			// "Тотем Тескатлипока"
	n = InitTotems(n,	"Totem_6",	2,	"Tortuga_town",				"Temple_6",		"");			// "Тотем Чалчиуитликуэ"
	n = InitTotems(n,	"Totem_7",	1,	"Villemstad_townhall",		"Temple_7",		"");			// "Тотем Уицилопочтли"
	n = InitTotems(n,	"Totem_8",	4,	"Mayak8",					"Temple_8",		"");			// "Тотем Тлалока"
	n = InitTotems(n,	"Totem_9",	3,	"Santiago_Incquisitio",		"Temple_9",		"");			// "Тотем Майяуэль"
	n = InitTotems(n,	"Totem_10",	5,	"Temple",					"Temple_10",	"");			// "Тотем Тонакатекутли"
	n = InitTotems(n,	"Totem_11",	11,	"Tenochtitlan",				"Tenochtitlan",	"button04");	// "Тотем Камаштли"
	n = InitTotems(n,	"Totem_12",	12,	"",							"Temple_great",	"");			// "Тотем Центеотль"
	n = InitTotems(n,	"Totem_13",	13,	"Tenotchitlan_Jungle_06",	"Tenochtitlan",	"button02");	// "Тотем Тласолтеотль"
	n = InitTotems(n,	"Totem_14",	14,	"Panama_jungle_02",			"Tenochtitlan",	"button03");	// "Тотем Тонатиу"
	n = InitTotems(n,	"Totem_15",	15,	"Temple_Inside",			"Temple_great",	"button02");	// "Тотем Шипе-Тотеку

	Totems_end = n; // < для проверки тотемов конечный номер
	ItemsForLocators_end = n; // < конечный номер для спецпредметов

	// <---------------------------------------------------< QUEST ITEMS <--------------------------------------------------<

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													КАРТЫ АРХИПЕЛАГА
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//											picTexture
	//			index	id					picIndex		price				weight	rare	imageTga		imageType		mapSpecial
	n = InitMaps(n,		"map_bad",			1,	"ITEMS_10",	(rand(4)+6)*1000,	0.1,	0.005,	"map_1",		"cabin_map",	0);		// "Дешёвая карта"
	n = InitMaps(n,		"map_normal",		5,	"ITEMS_9",	(rand(8)+9)*1020,	0.1,	0.001,	"map_2",		"cabin_map",	0);		// "Обычная карта"
	n = InitMaps(n,		"Map_Best",			14,	"ITEMS_9",	(rand(8)+50)*1000,	0.1,	0.0001,	"map_good",		"cabin_map",	0);		// "Отличная карта"
	n = InitMaps(n,		"map_bermudas",		4,	"ITEMS_11",	(rand(8)+6)*1050,	0.2,	0.0,	"bermudas",		"",				0);		// "Карта Бермуды"
	n = InitMaps(n,		"map_jam",			11,	"ITEMS_11",	(rand(8)+6)*1100,	0.2,	0.0,	"Jamaica",		"",				0);		// "Карта Ямайки"
	n = InitMaps(n,		"map_cayman",		12,	"ITEMS_11",	(rand(8)+8)*1015,	0.2,	0.0,	"kayman",		"",				0);		// "Карта Каймана"
	n = InitMaps(n,		"map_barbados",		2,	"ITEMS_11",	(rand(8)+6)*1200,	0.2,	0.0,	"barbados",		"",				0);		// "Карта Барбадоса"
	n = InitMaps(n,		"map_TORTUGA",		8,	"ITEMS_13",	(rand(8)+6)*1070,	0.2,	0.0,	"TORTUGA",		"",				0);		// "Карта Тортуги"
	n = InitMaps(n,		"map_Curacao",		7,	"ITEMS_11",	(rand(8)+6)*1300,	0.2,	0.0,	"curacao",		"",				0);		// "Карта Кюрасао"
	n = InitMaps(n,		"map_martiniqua",	16,	"ITEMS_11",	(rand(8)+6)*1250,	0.2,	0.0,	"martinica",	"",				0);		// "Карта Мартиники"
	n = InitMaps(n,		"map_dominica",		8,	"ITEMS_11",	(rand(8)+7)*1030,	0.2,	0.0,	"dominica",		"",				0);		// "Карта Доминики"
	n = InitMaps(n,		"map_trinidad",		9,	"ITEMS_13",	(rand(8)+6)*1080,	0.2,	0.0,	"trinidad",		"",				0);		// "Карта Тринидад и Тобаго"
	n = InitMaps(n,		"map_puerto",		2,	"ITEMS_13",	(rand(8)+6)*1500,	0.2,	0.0,	"p_rico",		"",				0);		// "Карта Пуэрто-Рико"
	n = InitMaps(n,		"map_cuba",			5,	"ITEMS_11",	(rand(8)+12)*1090,	0.2,	0.0,	"cuba",			"",				0);		// "Карта Кубы"
	n = InitMaps(n,		"map_Pearl",		4,	"ITEMS_13",	(rand(8)+12)*1150,	0.2,	0.0,	"Pearl",		"",				0);		// "Карта жемчужных промыслов"
	n = InitMaps(n,		"map_hisp",			10,	"ITEMS_11",	(rand(8)+12)*1220,	0.2,	0.0,	"hispaniola",	"",				0);		// "Карта Эспаньолы"
	n = InitMaps(n,		"map_nevis",		1,	"ITEMS_13",	(rand(8)+6)*1010,	0.2,	0.0,	"nevis",		"",				0);		// "Карта Невиса"
	n = InitMaps(n,		"map_beliz",		3,	"ITEMS_11",	(rand(8)+9)*1300,	0.2,	0.0,	"beliz",		"",				0);		// "Карта Белиза"
	n = InitMaps(n,		"map_guad",			9,	"ITEMS_11",	(rand(8)+6)*1015,	0.2,	0.0,	"guadelupa",	"",				0);		// "Карта Гваделупы"
	n = InitMaps(n,		"map_santa",		6,	"ITEMS_13",	(rand(8)+8)*1280,	0.2,	0.0,	"santa",		"",				0);		// "Карта Санта-Каталины"
	n = InitMaps(n,		"map_antigua",		1,	"ITEMS_11",	(rand(8)+6)*1400,	0.2,	0.0,	"antigua",		"",				0);		// "Карта Антигуа"
	n = InitMaps(n,		"map_terks",		7,	"ITEMS_13",	(rand(8)+9)*1350,	0.2,	0.0,	"terks",		"",				0);		// "Карта Теркса"
	n = InitMaps(n,		"map_sm",			5,	"ITEMS_13",	(rand(8)+6)*1500,	0.2,	0.0,	"s_martin",		"",				0);		// "Карта Сан Мартина"
	n = InitMaps(n,		"map_maine_1",		13,	"ITEMS_11",	(rand(8)+17)*1100,	0.2,	0.0,	"maine_1",		"",				0);		// "Карта запада Мэйна"
	n = InitMaps(n,		"map_maine_2",		14,	"ITEMS_11",	(rand(8)+18)*1150,	0.2,	0.0,	"maine_2",		"",				0);		// "Карта юга Мэйна"
	n = InitMaps(n,		"map_panama",		3,	"ITEMS_13",	(rand(8)+7)*1200,	0.2,	0.0,	"panama",		"",				0);		// "Карта Панамы"
	n = InitMaps(n,		"map_maracaibo",	15,	"ITEMS_11",	(rand(8)+9)*1250,	0.2,	0.0,	"maracaibo",	"",				0);		// "Карта центра Мэйна"
	n = InitMaps(n,		"map_cumana",		6,	"ITEMS_11",	(rand(8)+7)*1400,	0.2,	0.0,	"cumana",		"",				0);		// "Карта Куманы"
	n = InitMaps(n,		"map_providence",	9,	"ITEMS_15",	(rand(8)+9)*1350,	0.2,	0.0,	"OldProvidence","",				0);		// "Карта Олд Провиденс"
	n = InitMaps(n,		"map_LSC",			10,	"ITEMS_13",	200000,				0.2,	0.0,	"LostShipsCity","cabin_map",	0);		// "Карта ГПК"
	n = InitMaps(n,		"map_full",			2,	"ITEMS_7",	0,					0.4,	0.0,	"none",			"MapRead",		1);		// "Карта сокровищ"
	n = InitMaps(n,		"map_part1",		1,	"ITEMS_7",	0,					0.2,	0.0,	"none",			"MapRead",		1);		// "Часть карты сокровищ"
	n = InitMaps(n,		"map_part2",		3,	"ITEMS_7",	0,					0.2,	0.0,	"none",			"MapRead",		1);		// "Часть карты сокровищ"

	//	ЗАПОЛНЕНИЕ ТРУПОВ
	ItemDeadStartCount = n;
	trace("Заполнение трупов с предмета "+ItemDeadStartCount);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ПОДЗОРНЫЕ ТРУБЫ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										picIndex																update			cannos		shiptype		crew	charge		skills	hold
	//				index	id					picTexture	price	weight	rare	texture			zoom	activate		nation		shipname	hull	sail	speed	cannontype	mushketshot
	n = InitSpyglass(n,		"spyglass1",	14,	"ITEMS_6",	250,	1,		0.1,	"eye_BadTub",	2.5,	500,	150,	1,		0,	1,		1,	0,		0,	0,	1,	0,	0,		0,	0,	0);			// "Дешёвая подзорная труба"
	n = InitSpyglass(n,		"spyglass2",	15,	"ITEMS_6",	1500,	1.5,	0.07,	"eye_CommonTub",4.0,	500,	150,	1,		0,	1,		1,	0,		1,	0,	1,	0,	0,		0,	0,	0);			// "Обычная подзорная труба"
	n = InitSpyglass(n,		"spyglass3",	16,	"ITEMS_6",	4500,	2.0,	0.05,	"eye_GoodTub",	7.0,	500,	150,	1,		1,	1,		1,	1,		1,	0,	1,	0,	0,		0,	1,	1);			// "Хорошая подзорная труба"
	n = InitSpyglass(n,		"spyglass4",	14,	"ITEMS_1",	12000,	4.0,	0.01,	"eye_BestTub",	10.0,	500,	150,	1,		1,	1,		1,	1,		1,	1,	1,	1,	0,		1,	1,	1);			// "Отличная подзорная труба"
	n = InitSpyglass(n,		"spyglass5",	13,	"ITEMS_1",	75000,	7.0,	0.0001,	"eye_BestTub",	15.0,	500,	150,	1,		1,	1,		1,	1,		1,	1,	1,	1,	1,		1,	1,	1);			// "Эксклюзивная подзорная труба"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ЗЕЛЬЯ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//			index	id				picIndex	picTexture	price	weight	pic		tex		health	healthSpeed	energy	energySpeed	drunk	drunkTime	rare	model			antidot	sound	minlevel
	n = InitPotions(n,	"potion1",		7,			"ITEMS_1",	100,	0.4,	21,		0,		40.0,	5.0,		0.0,	0.0,		0.0,	0.0,		0.2,	"potion",		0,		"",		0);		// "Лечебное зелье"
	n = InitPotions(n,	"potion2",		1,			"ITEMS_1",	500,	1.0,	22,		0,		150.0,	7.0,		0.0,	0.0,		0.0,	0.0,		0.1,	"potionbig",	0,		"",		1);		// "Эликсир"
	n = InitPotions(n,	"potion3",		5,			"ITEMS_1",	200,	0.3,	23,		0,		0.0,	0.0,		0.0,	0.0,		0.0,	0.0,		0.1,	"Antidote",		1,		"",		1);		// "Противоядие"
	n = InitPotions(n,	"potion4",		4,			"ITEMS_1",	700,	0.8,	24,		0,		100.0,	9.0,		0.0,	0.0,		0.0,	0.0,		0.1,	"balsam",		1,		"",		1);		// "Микстура"
	n = InitPotions(n,	"potionrum",	3,			"ITEMS_1",	150,	2.0,	25,		0,		50.0,	5.0,		20.0,	10.0,		50.0,	5600.0,		0.01,	"vodka",		1,		"",		1);		// "Бутылка рома"
	n = InitPotions(n,	"potionwine",	6,			"ITEMS_1",	500,	1.5,	26,		0,		175.0,	7.0,		0.0,	0.0,		10.0,	1120.0,		0.05,	"balsam",		0,		"",		1);		// "Отличное вино"
	n = InitPotions(n,	"potion5",		12,			"ITEMS_7",	30,		0.4,	27,		0,		25.0,	5.0,		0.0,	0.0,		0.0,	0.0,		0.2,	"balsam",		0,		"",		1);		// "Виноград"
	n = InitPotions(n,	"potionsangari",4,			"ITEMS_14",	900,	1.5,	26,		0,		145.0,	6.0,		10.0,	5.0,		15.0,	1700.0,		0.001,	"balsam",		0,		"",		7);		// "Сангари"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ДРАГОЦЕННОСТИ, БИЖУТЕРИЯ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//			index	id					picIndex	picTexture	price	weight	rare	model		minlevel
	n = InitJewelry(n,	"incas_collection",	5,			"ITEMS_4",	47000,	50.0,	0.0,	"stat1",	0);		// "Сокровища"
	n = InitJewelry(n,	"jewelry1",			1,			"ITEMS_2",	450,	0.2,	0.1,	"sapphire",	0);		// "Сапфир"
	n = InitJewelry(n,	"jewelry2",			2,			"ITEMS_2",	700,	0.2,	0.05,	"diamond",	1);		// "Алмаз"
	n = InitJewelry(n,	"jewelry3",			3,			"ITEMS_2",	550,	0.2,	0.1,	"ruby",		0);		// "Рубин"
	n = InitJewelry(n,	"jewelry4",			4,			"ITEMS_2",	500,	0.2,	0.1,	"emerald",	0);		// "Изумруд"
	n = InitJewelry(n,	"jewelry5",			5,			"ITEMS_2",	240,	0.7,	0.05,	"sapphire",	1);		// "Золотой самородок"
	n = InitJewelry(n,	"jewelry6",			6,			"ITEMS_2",	100,	0.1,	0.1,	"sapphire",	0);		// "Серебряное кольцо с сапфиром"
	n = InitJewelry(n,	"jewelry7",			7,			"ITEMS_2",	200,	0.1,	0.1,	"sapphire",	0);		// "Золотое кольцо с изумрудом"
	n = InitJewelry(n,	"jewelry8",			8,			"ITEMS_2",	10,		0.1,	0.2,	"sapphire",	0);		// "Бронзовое кольцо"				(+1 Везение)
	n = InitJewelry(n,	"jewelry9",			9,			"ITEMS_2",	80,		0.2,	0.2,	"sapphire",	0);		// "Бронзовый крестик"				(+1 Везение)
	n = InitJewelry(n,	"jewelry10",		10,			"ITEMS_2",	170,	0.1,	0.1,	"emerald",	1);		// "Золотое кольцо с сапфиром"
	n = InitJewelry(n,	"jewelry11",		11,			"ITEMS_2",	90,		0.3,	0.1,	"pearlbig",	0);		// "Большая жемчужина"
	n = InitJewelry(n,	"jewelry12",		12,			"ITEMS_2",	40,		0.1,	0.2,	"pearlbig",	0);		// "Маленькая жемчужина"
	n = InitJewelry(n,	"jewelry13",		13,			"ITEMS_2",	150,	0.3,	0.1,	"sapphire",	1);		// "Камея"
	n = InitJewelry(n,	"jewelry14",		14,			"ITEMS_2",	220,	0.1,	0.05,	"sapphire",	1);		// "Золотая брошь"
	n = InitJewelry(n,	"jewelry15",		15,			"ITEMS_2",	300,	0.5,	0.05,	"sapphire",	1);		// "Изумрудные подвески"
	n = InitJewelry(n,	"jewelry16",		16,			"ITEMS_2",	10,		0.3,	0.05,	"sapphire",	2);		// "Ожерелье"
	n = InitJewelry(n,	"jewelry17",		4,			"ITEMS_7",	110,	0.5,	0.05,	"pursel",	1);		// "Серебряный самородок"
	n = InitJewelry(n,	"jewelry18",		10,			"ITEMS_7",	330,	0.1,	0.1,	"pursel",	0);		// "Золотое кольцо с рубином"
	n = InitJewelry(n,	"stop_storm",		12,			"ITEMS_14",	10000,	0.1,	0.1,	"pursel",	0);		// "Штормометр"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													БОЕПРИПАСЫ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//		index	id					picIndex	picTexture	price	weight	rare
	n = InitAmmo(n,	"bullet",			2,			"ITEMS_18",	4,		0.1,	0.3);		// "Свинцовые пули"
	n = InitAmmo(n,	"GunPowder",		1,			"ITEMS_18",	8,		0.1,	0.3);		// "Гранулированный порох"
	n = InitAmmo(n,	"bullet_colt",		10,			"ITEMS_18",	4,		0.1,	0.0001);	// "Револьверная пуля"
	n = InitAmmo(n,	"GunPowder_colt",	9,			"ITEMS_18",	4,		0.1,	0.0001);	// "Револьверный порох"
	n = InitAmmo(n,	"grapeshot",		3,			"ITEMS_18",	40,		0.1,	0.01);		// "Картечь"
	n = InitAmmo(n,	"cartridge",		8,			"ITEMS_18",	100,	0.1,	0.001);		// "Бумажный патрон"
	n = InitAmmo(n,	"petard",			5,			"ITEMS_18",	200,	0.5,	0.001);		// "Петарда"
	n = InitAmmo(n,	"grenade",			6,			"ITEMS_18",	400,	0.5,	0.001);		// "Граната"
	n = InitAmmo(n,	"harpoon",			7,			"ITEMS_18",	500,	1.0,	0.01);		// "Гарпун"
	n = InitAmmo(n,	"GunEchin",			12,			"ITEMS_18",	50,		0.4,	0.0001);	// "Ежовый заряд"
	n = InitAmmo(n,	"GunCap_colt",		11,			"ITEMS_18",	20,		0.1,	0.0001);	// "Капсюли"
	n = InitAmmo(n,	"cartridge_colt",	13,			"ITEMS_18",	100,	0.1,	0.0001);	// "Револьверный картридж"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													КРАФТ: ИНСТРУМЕНТЫ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//					index	id						picIndex	picTexture	price	weight
	n = InitAlchemyTools(n,		"alchemy_kit",			1,			"ITEMS_21",	5000,	8.0);	// "Сундук алхимика"
	n = InitAlchemyTools(n,		"tailor_kit",			4,			"ITEMS_21",	1200,	1.0);	// "Портняжный инструмент"
	n = InitAlchemyTools(n,		"mechanic_kit",			2,			"ITEMS_21",	1500,	5.0);	// "Слесарный инструмент"
	n = InitAlchemyTools(n,		"carpenter_kit",		3,			"ITEMS_21",	1500,	5.0);	// "Плотницкий инструмент"
	n = InitAlchemyTools(n,		"crucible",				12,			"ITEMS_31",	2000,	2.0);	// "Тигель"
	n = InitAlchemyTools(n,		"bullet_mold",			9,			"ITEMS_32",	700,	0.3);	// "Пулелейка"
	n = InitAlchemyTools(n,		"mortar_and_pestle",	10,			"ITEMS_32",	60,		1.0);	// "Ступка с пестиком"
	n = InitAlchemyTools(n,		"lamp",					3,			"ITEMS_30",	40,		2.0);	// "Лампада"
	n = InitAlchemyTools(n,		"silver_spoon",			4,			"ITEMS_30",	90,		0.1);	// "Серебряная ложка"
	n = InitAlchemyTools(n,		"wooden_spoon",			13,			"ITEMS_30",	40,		0.1);	// "Деревянная ложка"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													КРАФТ: РЕДКИЕ ИНГРЕДИЕНТЫ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//						index	id					picIndex	picTexture	price	weight	model
	n = InitAlchemyIngredients(n,	"ethanol",			11,			"ITEMS_32",	140,	0.3,	"elixir");	// "Этиловый спирт"
	n = InitAlchemyIngredients(n,	"nitric_acid",		12,			"ITEMS_32",	170,	0.4,	"elixir");	// "Азотная кислота"
	n = InitAlchemyIngredients(n,	"fulminate_silver",	8,			"ITEMS_32",	300,	0.1,	"pursel");	// "Гремучее серебро"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													КРАФТ: РАСТЕНИЯ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	Ingredients_start = n; // для проверки кустов начальный номер позже планируется использвать для рандомного высаживания растений для крафта
	//
	//						index	id					picIndex	picTexture	price	weight	model
	n = InitAlchemyIngredients(n,	"herb_zingiber",	9,			"ITEMS_22",	100,	0.1,	"zingiber");	// "Корень имбиря"
	n = InitAlchemyIngredients(n,	"herb_matricaria",	12,			"ITEMS_22",	100,	0.1,	"matricaria");	// "Матрикария"
	n = InitAlchemyIngredients(n,	"herb_ginseng",		15,			"ITEMS_22",	100,	0.1,	"ginseng");		// "Женьшень"
	//
	Ingredients_end = n;
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													КРАФТ: РЕЦЕПТЫ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//					index	id							result				price
	n = InitAlchemyRecipies(n,	"recipe_cartridge",			"cartridge",		2500);		// рецепт "Бумажного патрона"
	n = InitAlchemyRecipies(n,	"recipe_harpoon",			"harpoon",			3500);		// рецепт "Стрелы"
	n = InitAlchemyRecipies(n,	"recipe_GunEchin",			"GunEchin",			10000);		// рецепт "Ежового заряда"

	n = InitAlchemyRecipies(n,	"recipe_petard",			"petard",			5000);		// рецепт "Петарды"
	n = InitAlchemyRecipies(n,	"recipe_grenade",			"grenade",			5000);		// рецепт "Гранаты"

	n = InitAlchemyRecipies(n,	"recipe_GunPowder_colt",	"GunPowder_colt",	15000);		// рецепт "Револьверного пороха"
	n = InitAlchemyRecipies(n,	"recipe_bullet_colt",		"bullet_colt",		15000);		// рецепт "Револьверной пули"
	n = InitAlchemyRecipies(n,	"recipe_GunCap_colt",		"GunCap_colt",		15000);		// рецепт "Капсюлей"
	n = InitAlchemyRecipies(n,	"recipe_cartridge_colt",	"cartridge_colt",	15000);		// рецепт "Револьверного картриджа"

	n = InitAlchemyRecipies(n,	"recipe_fulminate_silver",	"fulminate_silver",	25000);		// рецепт "Гремучего серебра"

	n = InitAlchemyRecipies(n,	"recipe_migraine_potion",	"migraine_potion",	1000);		// рецепт "Лекарство от мигрени"
	n = InitAlchemyRecipies(n,	"recipe_potion1",			"potion1",			5000);		// рецепт "Лечебное зелье"
	n = InitAlchemyRecipies(n,	"recipe_potionsangari",		"potionsangari",	5000);		// рецепт "Сангари"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ФИЛЛЕРНЫЙ МУСОР
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//										picTexture
	//				index	id			picIndex		price	weight	rare	model		minlevel
	n = InitMinerals(	n,	"mineral2",	7,	"ITEMS_8",	300,	6,		0.02,	"sapphire",	0);		// "Лютня"
	n = InitMinerals(	n,	"mineral3",	8,	"ITEMS_8",	15,		1,		0.05,	"sapphire",	0);		// "Свеча"
	n = InitMinerals(	n,	"mineral4",	9,	"ITEMS_8",	25,		2,		0.05,	"pursel",	0);		// "Баклан"			(-1 Лидерство и Скрытность)
	n = InitMinerals(	n,	"mineral5",	5,	"ITEMS_7",	5,		3,		0.02,	"pursel",	0);		// "Старое ведро"
	n = InitMinerals(	n,	"mineral6",	6,	"ITEMS_7",	20,		1,		0.4,	"pursel",	0);		// "Коралл"
	n = InitMinerals(	n,	"mineral7",	7,	"ITEMS_7",	140,	0.8,	0.2,	"pursel",	0);		// "Трубка"
	n = InitMinerals(	n,	"mineral8",	7,	"ITEMS_9",	30,		1,		0.05,	"pursel",	4);		// "Башмак"			(-1 Везение)
	n = InitMinerals(	n,	"mineral9",	8,	"ITEMS_9",	70,		1,		0.1,	"pursel",	2);		// "Кружка"
	n = InitMinerals(	n,	"mineral10",16,	"ITEMS_9",	10,		1,		0.1,	"pursel",	0);		// "Мешочек соли"
	n = InitMinerals(	n,	"mineral11",1,	"ITEMS_9",	90,		1,		0.1,	"pursel",	0);		// "Точильный камень"
	n = InitMinerals(	n,	"mineral12",9,	"ITEMS_9",	75,		1,		0.1,	"pursel",	0);		// "Верёвка"
	n = InitMinerals(	n,	"mineral13",15,	"ITEMS_9",	145,	1,		0.1,	"pursel",	0);		// "Бронзовый котелок"
	n = InitMinerals(	n,	"mineral14",14,	"ITEMS_10",	200,	1,		0.1,	"pursel",	0);		// "Ножницы"
	n = InitMinerals(	n,	"mineral15",15,	"ITEMS_10",	20,		1,		0.1,	"pursel",	0);		// "Старая амфора"
	n = InitMinerals(	n,	"mineral16",5,	"ITEMS_15",	10,		1,		0.1,	"pursel",	0);		// "Гвозди"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ХРУСТАЛЬНЫЕ ЧЕРЕПА ТОЛЬТЕКОВ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//									picTexture
	//			index	id			picIndex		price	minlevel
	n = InitToltecs(n,	"sculMa1",	11,	"ITEMS_9",	90000,	6);		// "Белый хрустальный череп"	(+5 Абордаж)
	n = InitToltecs(n,	"sculMa2",	12,	"ITEMS_9",	70000,	4);		// "Розовый хрустальный череп"	(+5 Орудия)
	n = InitToltecs(n,	"sculMa3",	13,	"ITEMS_9",	50000,	1);		// "Голубой хрустальный череп"	(+5 Защита) (Полный комплект: +10 Навигация, Орудия, Абордаж и Защита)

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ИНДЕЙСКИЕ ИДОЛЫ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//								picIndex
	//			 index	id				picTexture	price	weight	rare	model		minlevel
	n = InitTrinkets(n,	"Statue1",	15,	"ITEMS_1",	25500,	20.0,	0.001,	"stat1",	1);		// "Статуэтка Шочипилли"
	n = InitTrinkets(n,	"indian1",	1,	"ITEMS_5",	3530,	3.0,	0.005,	"pursel",	2);		// "Оберег Тлальчитонатиу"
	n = InitTrinkets(n,	"indian2",	2,	"ITEMS_5",	640,	1.0,	0.05,	"pursel",	1);		// "Пугающая фигурка"			(-1 Лидерство)
	n = InitTrinkets(n,	"indian3",	3,	"ITEMS_5",	500,	0.6,	0.05,	"pursel",	1);		// "Нефритовая маска"
	n = InitTrinkets(n,	"indian5",	5,	"ITEMS_5",	550,	1.5,	0.05,	"sapphire",	3);		// "Двойная маска"
	n = InitTrinkets(n,	"indian6",	6,	"ITEMS_5",	2010,	1.0,	0.005,	"sapphire",	2);		// "Амулет Шиукоатля"
	n = InitTrinkets(n,	"indian7",	7,	"ITEMS_5",	2550,	3.6,	0.03,	"sapphire",	4);		// "Идол Великой Матери"
	n = InitTrinkets(n,	"indian10",	10,	"ITEMS_5",	2010,	2.0,	0.03,	"sapphire",	7);		// "Оберег Эхекатля"
	n = InitTrinkets(n,	"indian11",	11,	"ITEMS_5",	50000,	1.0,	0.0,	"stat1",	5);		// "Крысиный бог"
	n = InitTrinkets(n,	"indian12",	12,	"ITEMS_5",	15030,	10.0,	0.001,	"sapphire",	7);		// "Кубок-тотем Тепейоллотля"
	n = InitTrinkets(n,	"indian14",	14,	"ITEMS_5",	3210,	3.0,	0.005,	"pursel",	5);		// "Чаша Ололиуки"
	n = InitTrinkets(n,	"indian15",	15,	"ITEMS_5",	3500,	30.0,	0.005,	"sapphire",	3);		// "Базальтовая голова"
	n = InitTrinkets(n,	"indian17",	10,	"ITEMS_9",	550,	2.0,	0.05,	"sapphire",	1);		// "Тельная ладанка"			(+3 Скрытность)
	n = InitTrinkets(n,	"indian18",	11,	"ITEMS_7",	25075,	2.0,	0.001,	"pursel",	1);		// "Идол Атлауа"				(+5 Навигация, -10 Скрытность)
	n = InitTrinkets(n,	"indian19",	13,	"ITEMS_7",	25950,	2.0,	0.001,	"pursel",	1);		// "Статуэтка Тлалока"			(+5 Меткость, +5 Орудия, -10 Скрытность)
	n = InitTrinkets(n,	"indian20",	14,	"ITEMS_7",	50750,	2.0,	0.001,	"pursel",	1);		// "Церемониальный нож"			(+10 Лидерство, -5 Везение)
	n = InitTrinkets(n,	"indian21",	15,	"ITEMS_7",	50025,	2.0,	0.001,	"sapphire",	1);		// "Церемониальный сосуд"		(+10 Лидерство, -5 Скрытность)
	n = InitTrinkets(n,	"indian22",	16,	"ITEMS_7",	80005,	2.0,	0.001,	"pursel",	1);		// "Голова воина племени майя"	(+10 Защита, +5 Лёгкое оружие, -10 Лидерство и Везение)

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													ИНДЕЙСКИЙ МУСОР
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//								picIndex
	//			 index	id				picTexture	price	weight	rare	model		minlevel
	n = InitTrinkets(n,	"indian4",	4,	"ITEMS_5",	7,		2.0,	0.2,	"pursel",	1);		// "Глиняный кувшин"
	n = InitTrinkets(n,	"indian9",	9,	"ITEMS_5",	20,		1.0,	0.03,	"sapphire",	5);		// "Алебастровый сосуд"
	n = InitTrinkets(n,	"indian8",	8,	"ITEMS_5",	140,	0.6,	0.07,	"sapphire",	4);		// "Серебряный кубок"
	n = InitTrinkets(n,	"indian13",	13,	"ITEMS_5",	40,		3.0,	0.1,	"pursel",	1);		// "Древняя курительница"
	n = InitTrinkets(n,	"indian16",	16,	"ITEMS_5",	15,		3.0,	0.05,	"sapphire",	3);		// "Раскрашенный сосуд"

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//													КИРАСЫ, БРОНЯ И КОСТЮМЫ
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//								picIndex		CirassLevel
	//			index	id				picTexture			weight	price	rare	model		clothes	minlevel	quality
	n = InitSuits(n,	"cirass1",	14,	"ITEMS_8",	0.10,	15,		7000,	0.01,	"1",		false,	3,			"poor");		// "Скальд"
	n = InitSuits(n,	"cirass2",	11,	"ITEMS_8",	0.18,	19,		15000,	0.01,	"2",		false,	5,			"ordinary");	// "Кирасирский панцирь"
	n = InitSuits(n,	"cirass4",	12,	"ITEMS_8",	0.22,	25,		19000,	0.005,	"3",		false,	10,			"ordinary");	// "Офицерская кираса"
	n = InitSuits(n,	"cirass3",	13,	"ITEMS_8",	0.27,	22,		22000,	0.001,	"4",		false,	14,			"good");		// "Гвардейская кираса"
	n = InitSuits(n,	"cirass5",	10,	"ITEMS_8",	0.35,	21,		30000,	0.0,	"5",		false,	20,			"excellent");	// "Наградная кираса"
	n = InitSuits(n,	"suit_1",	4,	"ITEMS_9",	0.0,	4,		20,		0.0,	"6",		true,	20,			"unique");		// "Обноски"			(при ношении: +20 Скрытность)
	n = InitSuits(n,	"suit_2",	16,	"ITEMS_1",	0.0,	7,		20000,	0.0,	"7",		true,	20,			"unique");		// "Костюм негоцианта"	(при ношении: +20 Коммерция)
	n = InitSuits(n,	"suit_3",	2,	"ITEMS_1",	0.0,	6,		150000,	0.0,	"8",		true,	20,			"unique");		// "Дворянское платье"	(при ношении: +20 Лидерство)
	n = InitSuits(n,  "underwater", 1,  "ITEMS_15",	0.30,	30,		300000,	0.0,  "protocusto", true,	20,			"unique");		// "Водолазный скафандр"
	//
	// предмет исключён из обычного спавна при: rare <= 0.0 или quality "excellent"/"unique"

	trace("Всего предметов (размерность массива) " + n);
	trace("Всего заскриптованных предметов - " + iScriptItemCount);
	trace("Начальный специальный предмет: " + Items[ItemsForLocators_start].id);
	trace("Конечный специальный предмет: " + Items[ItemsForLocators_end].id);

	InitAmmunition();
	InitAlchemyCraft();
	InitItemsRarity();

	return n;
}

// > инициализация патентов
int InitPatents(int idx, string id, int nation)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id				= "patent_" + id;
	itm.groupID			= PATENT_ITEM_TYPE;
	itm.name			= "itmname_" + itm.id;
	itm.describe		= "itmdescr_" + itm.id;
	itm.model			= "";
	itm.quest			= id + "_flag_rise";
	itm.picIndex		= 3;
	itm.picTexture		= "ITEMS_4";
	itm.price			= 0;
	itm.Nation			= nation;
	itm.TitulCur		= 1;
	itm.TitulCurNext	= 0;
	itm.Weight			= 0.1;
	itm.ItemType		= "QUESTITEMS";

	return idx + 1;
}

// > инициализация холодного оружия
int InitBlades(int idx, string id, int picIndex, string picTexture, string fencingType, float dmg_min, float dmg_max, float piercing, float block, float weight, int price, float rare, int minlevel,
				int gen_qty, bool gen_price, float gen_dmg_min_n, float gen_dmg_min_x, float gen_dmg_max_n, float gen_dmg_max_x, float gen_weight_n, float gen_weight_x, string quality, string wType)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.groupID					= BLADE_ITEM_TYPE;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.model					= id;
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.FencingType				= fencingType;
	itm.dmg_min					= dmg_min;
	itm.dmg_max					= dmg_max;
	itm.piercing				= piercing;
	itm.block					= block;
	itm.Weight					= weight;
	itm.price					= price;
	itm.rare					= rare;
	itm.minlevel				= minlevel;
	itm.folder					= "Ammo";
	itm.ItemType				= "WEAPON";
	itm.blade.time				= 0.1;
	itm.blade.colorstart		= argb(64, 64, 64, 64);
	itm.blade.colorend			= argb(0, 32, 32, 32);
	itm.wType					= wType;

	if (quality != "")
		itm.quality				= quality;

	if (gen_qty > 0)
	{
		itm.Generation.qty			= gen_qty;
		itm.Generation.price		= gen_price;
		itm.Generation.dmg_min.min	= gen_dmg_min_n;
		itm.Generation.dmg_min.max	= gen_dmg_min_x;
		itm.Generation.dmg_max.min	= gen_dmg_max_n;
		itm.Generation.dmg_max.max	= gen_dmg_max_x;
		itm.Generation.Weight.min	= gen_weight_n;
		itm.Generation.Weight.max	= gen_weight_x;
	}

	return idx + 1;
}

// > инициализация огнестрельного оружия
int InitGuns(int idx, string id, string groupID, int picIndex, string picTexture, float dmg_min, float dmg_max, float accuracy, int chargeQ, float chargespeed, float weight, int price, float rare, int minlevel, string quality, string wType)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.groupID					= groupID;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.model					= id;
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.dmg_min					= dmg_min;
	itm.dmg_max					= dmg_max;
	itm.accuracy				= accuracy;
	itm.chargeQ					= chargeQ;
	itm.chargespeed				= chargespeed;
	itm.Weight					= weight;
	itm.price					= price;
	itm.rare					= rare;
	itm.minlevel				= minlevel;
	itm.folder					= "Ammo";
	itm.ItemType				= "WEAPON";
	itm.wType					= wType;

	if (quality != "")
		itm.quality				= quality;

	if (id == "pistol7")
	{
		itm.shown				= "1";
		itm.startLocation		= "Temple_round";
		itm.startLocator		= "item1";
	}

	return idx + 1;
}

// > инициализация типов боеприпасов огнестрела
void InitGunsExt(string id, string AmmoType, string DmgMin_NC, string DmgMax_NC, string DmgMin_C, string DmgMax_C, string Accuracy, string Chargespeed, string EnergyP_NC, string EnergyP_C, string MisFire, string Stun_NC, string Stun_C, string AOEDamage, string SelfDamage, string Explosion)
{
	if (FindItem(id) < 0)
	{
		trace("WARNING! InitItems.c > InitGunsExt > Can't find item with id " + id);
		return;
	}

	if (AmmoType == "")
		AmmoType = "bullet,cartridge";

	string tmp, sAttr = AmmoType;
	int n, q = KZ|Symbol(AmmoType, ",");
	ref rGun = ItemsFromID(id);

	rGun.chargetype = AmmoType;

	for (n = 0; n <= q; n++)
	{
		if (q > 0)
			sAttr = GetSubStr(AmmoType, ",", n);

		if (sAttr != "" && FindItem(sAttr) >= 0)
		{
			tmp = GetSubStr(DmgMin_NC, ",", n);		rGun.type.(sAttr).DmgMin_NC		= tmp;	// > min урон по цели без кирасы
			tmp = GetSubStr(DmgMax_NC, ",", n);		rGun.type.(sAttr).DmgMax_NC		= tmp;	// > max урон по цели без кирасы
			tmp = GetSubStr(DmgMin_C, ",", n);		rGun.type.(sAttr).DmgMin_C		= tmp;	// > min урон по цели в кирасе
			tmp = GetSubStr(DmgMax_C, ",", n);		rGun.type.(sAttr).DmgMax_C		= tmp;	// > max урон по цели в кирасе
			tmp = GetSubStr(Accuracy, ",", n);		rGun.type.(sAttr).Accuracy		= tmp;	// > точность
			tmp = GetSubStr(Chargespeed, ",", n);	rGun.type.(sAttr).Chargespeed	= tmp;	// > скорость зарядки
			tmp = GetSubStr(EnergyP_NC, ",", n);	rGun.type.(sAttr).EnergyP_NC	= tmp;	// > кол-во отнимаемой энергии у цели без кирасы
			tmp = GetSubStr(EnergyP_C, ",", n);		rGun.type.(sAttr).EnergyP_C		= tmp;	// > кол-во отнимаемой энергии у цели в кирасе
			tmp = GetSubStr(Stun_NC, ",", n);		rGun.type.(sAttr).Stun_NC		= tmp;	// > станить цель без кирасы (1\0)	> TODO
			tmp = GetSubStr(Stun_C, ",", n);		rGun.type.(sAttr).Stun_C		= tmp;	// > станить цель в кирасе (1\0)	> TODO
			tmp = GetSubStr(AOEDamage, ",", n);		rGun.type.(sAttr).AOEDamage		= tmp;	// > урон по площади (1\0)
			tmp = GetSubStr(Misfire, ",", n);		rGun.type.(sAttr).Misfire		= tmp;	// > шанс взрыва оружия в руках при выстреле	> TODO сделать просто осечку, а взрыв отдельно
			tmp = GetSubStr(SelfDamage, ",", n);	rGun.type.(sAttr).SelfDamage	= tmp;	// > урон стрелку при выстреле (1 + rand(SelfDamage))
			tmp = GetSubStr(Explosion, ",", n);		rGun.type.(sAttr).Explosion		= tmp;	// > партиклы взрыва при попадании по цели (1\0)

			// > нужен ли порох\аналог этому боеприпасу
			rGun.type.(sAttr).gunpowder = LAi_GetAmmoGunpowderType(sAttr);
			// < нужен ли порох\аналог этому боеприпасу

			rGun.type.(sAttr).Bullet			= sAttr;

			if (n == 0)
				rGun.type.(sAttr).Default		= "1"; // > самый первый тип боеприпаса в списке AmmoType - дефолтный
			else
				rGun.type.(sAttr).Default		= "0";

			if (sti(rGun.type.(sAttr).Stun_NC) > 0 || sti(rGun.type.(sAttr).Stun_C) > 0)
				rGun.stun = true;
		}
	}
}

// > влияние определённого типа боеприпаса на ТТХ огнестрела
void InitAmmunition()
{
	// какой атрибут за что отвечает можно почитать выше
	// если AmmoType == "", то далее по коду в InitGunsExt AmmoType = "bullet,cartridge"
	//	*_C - противник в кирасе; *_NC - противник без кирасы
	// если боеприпасов (AmmoType) у огнестрела несколько (сейчас везде), то любой атрибут можно задать конкретно под каждый тип, заполняя статы через запятую; если задать только одно значение, то оно будет распространяться на все типы боеприпасов в списке AmmoType
	// TODO > всё ОБЯЗАТЕЛЬНО нужно забалансить под разные типы снарядов
	//			id					AmmoType 						DmgMin_NC	DmgMax_NC		DmgMin_C	DmgMax_C		Accuracy	Chargespeed	EnergyP_NC	EnergyP_C	Misfire		Stun_NC		Stun_C	AOEDamage		SelfDamage	Explosion
	InitGunsExt("pistol1",			"",								"20",		"100",			"16", 		"90",			"30",		"16,8",		"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Пистоль"
	InitGunsExt("pistol2",			"",								"30",		"120",			"25", 		"110",			"50",		"24,12",	"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Колониальный пистолет"
	InitGunsExt("pistol3",			"grapeshot,GunEchin,harpoon",	"5,30,50",	"5,30,185",		"5,30,45",	"5,30,160",		"50",		"33,22,33",	"0",		"0",		"0",		"0",		"0",	"1,1,0",		"0",		"0");		// "Тромбон"
	InitGunsExt("pistol6",			"",								"35",		"130",			"28", 		"120",			"60",		"32,20",	"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Бок-пистолет"
	InitGunsExt("pistol5",			"",								"45",		"170",			"40", 		"160",			"80",		"24,16",	"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Бретерский пистолет"
	InitGunsExt("pistol4",			"",								"40",		"140",			"35", 		"130",			"60",		"40,28",	"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Четырёхствольный пистолет"
	InitGunsExt("pistol7",			"bullet_colt,cartridge_colt",	"100",		"250",			"90", 		"240",			"80",		"52,26",	"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Револьвер Коллиера"

	InitGunsExt("mushket_poor",		"",								"55",		"195",			"50",		"180",			"60",		"24,15",	"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Старый мушкет"
	InitGunsExt("mushket",			"",								"80",		"250",			"75",		"240",			"75",		"22,13",	"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Фитильный мушкет"
	InitGunsExt("mushket_flint",	"",								"100",		"275",			"90",		"260",			"85",		"19,11",	"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Кремнёвый мушкет"
	InitGunsExt("mushket_indian",	"",								"95",		"290",			"85",		"280",			"95",		"18,10",	"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Мушкет Тичингиту"
	InitGunsExt("mushket_H2",		"",								"100",		"270",			"90",		"260",			"85",		"20,12",	"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Двуствольный мушкет"
	InitGunsExt("mushket2x2",		"",								"90",		"290",			"80",		"280",			"80",		"20,12",	"0",		"0",		"0",		"0",		"0",	"0",			"0",		"0");		// "Двуствольный мушкет" Хэмфри Дугласа

	InitGunsExt("mortar",			"grenade,petard",				"100,15",	"200,115",		"80,5",		"180,105",		"100",		"50",		"10,100",	"10,80",	"0",		"0",		"0",	"1",			"0",		"1");		// "Склопетта" > статы взяты из ККС
}

// > инициализация кирас и костюмов
int InitSuits(int idx, string id, int picIndex, string picTexture, float CirassLevel, float weight, int price, float rare, string model, bool Clothes, int minlevel, string quality)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.groupID					= CIRASS_ITEM_TYPE;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.model					= model;
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.Clothes					= clothes;
	itm.CirassLevel				= CirassLevel;
	itm.Weight					= weight;
	itm.price					= price;
	itm.rare					= rare;
	itm.minlevel				= minlevel;
	itm.folder					= "items";
	itm.ItemType				= "SUPPORT";

	if (quality != "")
		itm.quality				= quality;

	return idx + 1;
}

// > инициализация тотемов
int InitTotems(int idx, string id, int picIndex, string startLocation, string useLocation, string useLocator)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.model					= id;
	itm.picIndex				= picIndex;
	itm.picTexture				= "ITEMS_AZTEC";
	itm.Weight					= 0.3;
	itm.price					= (rand(8)+1)*1000;
	itm.ItemType				= "QUESTITEMS";

	if (itm.id == "Totem_12")
		itm.shown				= "0";
	else
	{
		itm.startLocation		= startLocation;
		itm.shown				= "1";
		itm.startLocator		= "item1";
	}

	itm.useLocation				= useLocation;

	if (useLocator == "")
		itm.useLocator			= "button01";
	else
		itm.useLocator			= useLocator;

	return idx + 1;
}

// > инициализация подзорных труб
int InitSpyglass(int idx, string id, int picIndex, string picTexture, int price, float weight, float rare,
	string scopeTexture, float zoom, int activate, int update, bool nation, bool cannons, bool ship_name, bool ship_type, bool hull, bool sail, bool crew, bool speed, bool charge, bool cannontype, bool skills, bool mush, bool hold)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.groupID					= SPYGLASS_ITEM_TYPE;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.model					= "spyglass4";
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.Weight					= weight;
	itm.price					= price;
	itm.rare					= rare;
	itm.minlevel				= 1;
	itm.folder					= "items";
	itm.ItemType				= "SUPPORT";

	itm.scope.texture			= scopeTexture + ".tga";
	itm.scope.zoom				= zoom;
	itm.scope.time_activate		= activate;
	itm.scope.time_update		= update;
	itm.scope.show.nation		= nation;
	itm.scope.show.cannons		= cannons;
	itm.scope.show.ship_name	= ship_name;
	itm.scope.show.ship_type	= ship_type;
	itm.scope.show.hull			= hull;
	itm.scope.show.sail			= sail;
	itm.scope.show.crew			= crew;
	itm.scope.show.speed		= speed;
	itm.scope.show.charge		= charge;
	itm.scope.show.cannontype	= cannontype;
	itm.scope.show.captain_skills	= skills;
	itm.scope.show.mushketshot	= mush;
	itm.scope.show.hold			= hold;

	return idx + 1;
}

// > инициализация карт архипелага
int InitMaps(int idx, string id, int picIndex, string picTexture, int price, float weight, float rare, string imageTga, string imageType, bool mapSpecial)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.groupID					= MAPS_ITEM_TYPE;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.model					= "shipyardsMap";
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.Weight					= weight;
	itm.price					= price;
	itm.ItemType				= "MAP";
	itm.rare					= rare;

	itm.imageTga				= imageTga;
	itm.imageType				= imageType;

	if (imageType == "")
		itm.MapIsland			= ""; // > если у карты имеется этот атрибут, то она идёт в счёт MAPS_IN_ATLAS

	if (mapSpecial)
		itm.mapSpecial			= "";

	if (HasStrEx(itm.id, "_full,_part", "|"))
	{
		if (HasStr(itm.id, "_full"))
			itm.mapType			= "Full";
		else
			itm.mapType			= "Part";
	}

	return idx + 1;
}

// > инициализация инструментов для алхимии
int InitAlchemyTools(int idx, string id, int picIndex, string picTexture, int price, float weight)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.groupID					= ALCHEMY_ITEM_TYPE;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.model					= "Diamond";
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.Weight					= weight;
	itm.price					= price;
	itm.minlevel				= 0;
	itm.SortIndex				= 1;
	itm.ItemType				= "SUPPORT"; // TODO > "TOOLS"

	return idx + 1;
}

// > инициализация ингредиентов для алхимии
int InitAlchemyIngredients(int idx, string id, int picIndex, string picTexture, int price, float weight, string model)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.groupID					= ALCHEMY_ITEM_TYPE;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.model					= model;
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.Weight					= weight;
	itm.price					= price;
	itm.minlevel				= 0;
	itm.SortIndex				= 1;
	itm.ItemType				= "SUPPORT"; // TODO > "INGREDIENT"

	return idx + 1;
}

// > инициализации рецептов
int InitAlchemyRecipies(int idx, string id, string result, int Price)
{
	ref	recipe; makeref(recipe, Items[idx]);

	recipe.id			= id;	
	recipe.result 		= result;
	recipe.groupID		= READING_ITEM_TYPE;
	recipe.name			= "itmname_" + id;
	recipe.describe		= "itmdescr_" + id;
	recipe.model		= "letter";
	recipe.picTexture	= "ITEMS_33";
	recipe.picIndex		= 16;
	recipe.price		= Price;
	recipe.rare 		= 0.0001;
	recipe.minlevel 	= 1;
	recipe.Weight 		= 0.1;
	recipe.ItemType 	= "SUPPORT";

	return idx + 1;
}

// > инициализация филлерного мусора
int InitMinerals(int idx, string id, int picIndex, string picTexture, int price, float weight, float rare, string model, int minlevel)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.price					= price;
	itm.Weight					= weight;
	itm.rare					= rare;
	itm.minlevel				= minlevel;
	itm.model					= model;

//	itm.ItemType				= "MINERAL"; // TODO

	return idx + 1;
}

// > инициализация хрустальных черепов Тольтеков
int InitToltecs(int idx, string id, int picIndex, string picTexture, int price, int minlevel)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.model					= "pursel";
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.price					= price;
	itm.Weight					= 3.5;
	itm.rare					= 0.01;
	itm.minlevel				= minlevel;

	return idx + 1;
}

// > инициализация индейских побрякушек
int InitTrinkets(int idx, string id, int picIndex, string picTexture, int price, float weight, float rare, string model, int minlevel)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id = id;
	itm.name = "itmname_" + id;
	itm.describe = "itmdescr_" + id;
	itm.model = model;
	itm.picIndex = picIndex;
	itm.picTexture = picTexture;
	itm.price = price;
	itm.Weight = weight;
	itm.rare = rare;
	itm.minlevel = minlevel;
//	itm.ItemType = "TRINKETS"; // TODO

	return idx + 1;
}

// > инициализация зелий
int InitPotions(int idx, string id, int picIndex, string picTexture, int price, float weight, int pic, int tex, float health, float healthSpeed, float energy, float energySpeed, float drunk, float drunkTime, float rare, string model, bool antidot, string sound, int minlevel)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.groupID					= POTION_ITEM_TYPE;
	itm.model					= model;
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.price					= price;
	itm.Weight					= weight;
	itm.potion.pic				= pic;
	itm.potion.tex				= tex;
	itm.rare					= rare;
	itm.minlevel				= minlevel;
	itm.SortIndex				= 2;
	itm.ItemType				= "SUPPORT";

	if (antidot)
		itm.potion.antidote		= true;

	if (drunk > 0.0)
		itm.potion.drunk		= drunk;

	if (drunkTime > 0.0)
		itm.potion.drunk.time	= drunkTime;

	if (health > 0.0)
		itm.potion.health		= health;

	if (healthSpeed > 0.0)
		itm.potion.health.speed = healthSpeed;

	if (energy > 0.0)
		itm.potion.energy		= energy;

	if (energySpeed > 0.0)
		itm.potion.energy.speed = energySpeed;

	if (sound != "")
		itm.potion.sound		= sound;

	return idx + 1;
}

// > инициализация бижутерии
int InitJewelry(int idx, string id, int picIndex, string picTexture, int price, float weight, float rare, string model, int minlevel)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.model					= model;
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.price					= price;
	itm.Weight					= weight;
	itm.rare					= rare;
	itm.minlevel				= minlevel;

	return idx + 1;
}

// > инициализация боеприпасов
int InitAmmo(int idx, string id, int picIndex, string picTexture, int price, float weight, float rare)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id						= id;
	itm.name					= "itmname_" + id;
	itm.describe				= "itmdescr_" + id;
	itm.groupID					= AMMO_ITEM_TYPE;
	itm.model					= "pursel";
	itm.picIndex				= picIndex;
	itm.picTexture				= picTexture;
	itm.price					= price;
	itm.Weight					= weight;
	itm.rare					= rare;
	itm.minlevel				= 0;
	itm.SortIndex				= 1;
	itm.ItemType				= "SUPPORT";

	return idx + 1;
}

// > инициализация квестовых предметов
int InitQuestItems(int idx, string id, int picIndex, string picTexture, int price, float weight, string model, string itemtype, string groupID)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id				= id;
	itm.name			= "itmname_" + id;
	itm.describe		= "itmdescr_" + id;
	itm.model			= model;
	itm.picIndex		= picIndex;
	itm.picTexture		= picTexture;
	itm.price			= price;
	itm.Weight			= weight;

	if (groupID != "")
		itm.groupID 	= groupID;

	if (id == "mapQuest" || id == "MapsAtlas")
	{
		itm.mapSpecial	= "";

		if (id == "mapQuest")
		{
			itm.imageTga	= "none";
			itm.imageType	= "MapRead";
		}
	}

	if (itemtype == "")
		itm.ItemType	= "QUESTITEMS";
	else
		itm.ItemType	= itemtype;

	return idx + 1;
}

// > инициализация локаторных квестовых предметов
int InitQuestItemsLocator(int idx, string id, int picIndex, string picTexture, int price, float weight, string model, string itemtype, int shown, string useLocation, string groupID, string useLocator, string startLocator, string startLocation)
{
	ref	itm; makeref(itm, Items[idx]);

	itm.id				= id;
	itm.name			= "itmname_" + id;
	itm.describe		= "itmdescr_" + id;
	itm.model			= model;
	itm.picIndex		= picIndex;
	itm.picTexture		= picTexture;
	itm.price			= price;
	itm.Weight			= weight;

	if (shown >= 0)
		itm.shown		= "" + shown;

	if (startLocation != "")
		itm.startLocation = startLocation;

	if (startLocator != "")
	{
		itm.startLocator = startLocator;
		
		if (id == "Rock_letter" && startLocation == "Temple")
			itm.startLocator = "item1";
	}

	if (groupID != "")
     		itm.groupID 	= groupID;

	if (useLocation != "")
		itm.useLocation = useLocation;

	if (useLocator != "")
		itm.useLocator = useLocator;

	if (itemtype == "")
		itm.ItemType	= "QUESTITEMS";
	else
		itm.ItemType	= itemtype;

	return idx + 1;
}

void SetItemRarity(string id, string sAttr, float rare, int minQ, int maxQ)
{
	ref rItem			= ItemsFromID(id);
	rItem.(sAttr).rare	= rare;
	rItem.(sAttr).min	= minQ;
	rItem.(sAttr).max	= maxQ;
}

void InitItemsRarity()
{
	//				что				у кого			шанс	мин	макс
	SetItemRarity(	"cirass1",		"Solder",		0.01,	1,	1);
	SetItemRarity(	"spyglass1",	"Solder",		0.05,	1,	1);
	SetItemRarity(	"spyglass2",	"Solder",		0.01,	1,	1);
	SetItemRarity(	"potion1",		"Solder",		0.1,	1,	3);
	SetItemRarity(	"potion2",		"Solder",		0.1,	1,	1);
	SetItemRarity(	"potion3",		"Solder",		0.05,	1,	1);
	SetItemRarity(	"potion4",		"Solder",		0.05,	1,	1);
	SetItemRarity(	"potion5",		"Solder",		0.1,	1,	5);
	SetItemRarity(	"potionrum",	"Solder",		0.05,	1,	1);
	SetItemRarity(	"potionwine",	"Solder",		0.05,	1,	1);
	SetItemRarity(	"mineral2",		"Solder",		0.01,	1,	1);
	SetItemRarity(	"mineral4",		"Solder",		0.05,	1,	1);
	SetItemRarity(	"mineral6",		"Solder",		0.001,	1,	1);
	SetItemRarity(	"mineral7",		"Solder",		0.1,	1,	1);
	SetItemRarity(	"mineral8",		"Solder",		0.1,	1,	1);
	SetItemRarity(	"mineral9",		"Solder",		0.1,	1,	1);
	SetItemRarity(	"mineral10",	"Solder",		0.001,	1,	5);
	SetItemRarity(	"mineral11",	"Solder",		0.05,	1,	1);
	SetItemRarity(	"mineral13",	"Solder",		0.025,	1,	1);
	SetItemRarity(	"mineral16",	"Solder",		0.025,	1,	2);
	SetItemRarity(	"indian1",		"Solder",		0.001,	1,	1);
	SetItemRarity(	"indian2",		"Solder",		0.02,	1,	1);
	SetItemRarity(	"indian12",		"Solder",		0.001,	1,	1);
	SetItemRarity(	"indian13",		"Solder",		0.001,	1,	1);
	SetItemRarity(	"indian14",		"Solder",		0.001,	1,	1);
	SetItemRarity(	"indian16",		"Solder",		0.1,	1,	1);
	SetItemRarity(	"indian17",		"Solder",		0.01,	1,	1);
	SetItemRarity(	"jewelry1",		"Solder",		0.05,	1,	1);
	SetItemRarity(	"jewelry6",		"Solder",		0.01,	1,	1);
	SetItemRarity(	"jewelry8",		"Solder",		0.1,	1,	1);
	SetItemRarity(	"jewelry9",		"Solder",		0.01,	1,	1);
	SetItemRarity(	"jewelry12",	"Solder",		0.05,	1,	5);
	SetItemRarity(	"jewelry17",	"Solder",		0.05,	1,	1);

	SetItemRarity(	"cirass1",		"Warrior",		0.01,	1,	1);
	SetItemRarity(	"cirass2",		"Warrior",		0.005,	1,	1);
	SetItemRarity(	"spyglass1",	"Warrior",		0.05,	1,	1);
	SetItemRarity(	"spyglass2",	"Warrior",		0.005,	1,	1);
	SetItemRarity(	"potion1",		"Warrior",		0.1,	1,	4);
	SetItemRarity(	"potion2",		"Warrior",		0.1,	1,	3);
	SetItemRarity(	"potion3",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"potion4",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"potion5",		"Warrior",		0.1,	1,	5);
	SetItemRarity(	"potionrum",	"Warrior",		0.1,	1,	1);
	SetItemRarity(	"potionwine",	"Warrior",		0.01,	1,	1);
	SetItemRarity(	"mineral4",		"Warrior",		0.01,	1,	1);
	SetItemRarity(	"mineral6",		"Warrior",		0.001,	1,	1);
	SetItemRarity(	"mineral7",		"Warrior",		0.3,	1,	1);
	SetItemRarity(	"mineral8",		"Warrior",		0.1,	1,	1);
	SetItemRarity(	"mineral9",		"Warrior",		0.2,	1,	1);
	SetItemRarity(	"mineral10",	"Warrior",		0.001,	1,	5);
	SetItemRarity(	"mineral11",	"Warrior",		0.05,	1,	1);
	SetItemRarity(	"mineral13",	"Warrior",		0.025,	1,	1);
	SetItemRarity(	"mineral14",	"Warrior",		0.025,	1,	1);
	SetItemRarity(	"mineral16",	"Warrior",		0.025,	1,	2);
	SetItemRarity(	"indian1",		"Warrior",		0.001,	1,	1);
	SetItemRarity(	"indian2",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"indian3",		"Warrior",		0.01,	1,	1);
	SetItemRarity(	"indian5",		"Warrior",		0.03,	1,	1);
	SetItemRarity(	"indian6",		"Warrior",		0.001,	1,	1);
	SetItemRarity(	"indian7",		"Warrior",		0.01,	1,	1);
	SetItemRarity(	"indian8",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"indian9",		"Warrior",		0.1,	1,	1);
	SetItemRarity(	"indian10",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"indian12",		"Warrior",		0.1,	1,	1);
	SetItemRarity(	"indian13",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"indian14",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"indian16",		"Warrior",		0.001,	1,	1);
	SetItemRarity(	"indian17",		"Warrior",		0.02,	1,	1);
	SetItemRarity(	"jewelry1",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"jewelry2",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"jewelry3",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"jewelry4",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"jewelry5",		"Warrior",		0.05,	1,	2);
	SetItemRarity(	"jewelry6",		"Warrior",		0.01,	1,	1);
	SetItemRarity(	"jewelry7",		"Warrior",		0.05,	1,	1);
	SetItemRarity(	"jewelry8",		"Warrior",		0.15,	1,	1);
	SetItemRarity(	"jewelry9",		"Warrior",		0.03,	1,	1);
	SetItemRarity(	"jewelry10",	"Warrior",		0.02,	1,	1);
	SetItemRarity(	"jewelry11",	"Warrior",		0.05,	1,	6);
	SetItemRarity(	"jewelry12",	"Warrior",		0.05,	1,	20);
	SetItemRarity(	"jewelry13",	"Warrior",		0.05,	1,	2);
	SetItemRarity(	"jewelry14",	"Warrior",		0.01,	1,	2);
	SetItemRarity(	"jewelry15",	"Warrior",		0.01,	1,	1);
	SetItemRarity(	"jewelry16",	"Warrior",		0.1,	1,	2);
	SetItemRarity(	"jewelry17",	"Warrior",		0.05,	1,	3);
	SetItemRarity(	"jewelry18",	"Warrior",		0.05,	1,	1);

	SetItemRarity(	"cirass2",		"Officer",		0.01,	1,	1);
	SetItemRarity(	"cirass3",		"Officer",		0.003,	1,	1);
	SetItemRarity(	"cirass4",		"Officer",		0.001,	1,	1);
	SetItemRarity(	"spyglass3",	"Officer",		0.01,	1,	1);
	SetItemRarity(	"spyglass4",	"Officer",		0.001,	1,	1);
	SetItemRarity(	"spyglass5",	"Officer",		0.0001,	1,	1);
	SetItemRarity(	"potion1",		"Officer",		0.3,	2,	6);
	SetItemRarity(	"potion2",		"Officer",		0.3,	1,	3);
	SetItemRarity(	"potion3",		"Officer",		0.05,	1,	1);
	SetItemRarity(	"potion4",		"Officer",		0.05,	1,	3);
	SetItemRarity(	"potionrum",	"Officer",		0.01,	1,	1);
	SetItemRarity(	"potionwine",	"Officer",		0.1,	1,	1);
	SetItemRarity(	"jewelry1",		"Officer",		0.1,	1,	4);
	SetItemRarity(	"jewelry2",		"Officer",		0.1,	1,	4);
	SetItemRarity(	"jewelry3",		"Officer",		0.1,	1,	4);
	SetItemRarity(	"jewelry4",		"Officer",		0.1,	1,	4);
	SetItemRarity(	"jewelry5",		"Officer",		0.2,	1,	4);
	SetItemRarity(	"jewelry7",		"Officer",		0.1,	1,	1);
	SetItemRarity(	"jewelry10",	"Officer",		0.2,	1,	1);
	SetItemRarity(	"jewelry11",	"Officer",		0.2,	1,	5);
	SetItemRarity(	"jewelry13",	"Officer",		0.05,	1,	1);
	SetItemRarity(	"jewelry14",	"Officer",		0.05,	1,	1);
	SetItemRarity(	"jewelry15",	"Officer",		0.01,	1,	1);
	SetItemRarity(	"jewelry18",	"Officer",		0.2,	1,	1);

	SetItemRarity(	"potion1",		"Monster",		0.1,	1,	7);
	SetItemRarity(	"potion2",		"Monster",		0.1,	1,	5);
	SetItemRarity(	"potion4",		"Monster",		0.05,	1,	3);
	SetItemRarity(	"mineral4",		"Monster",		0.005,	1,	3);
	SetItemRarity(	"mineral5",		"Monster",		0.01,	1,	1);
	SetItemRarity(	"mineral6",		"Monster",		0.3,	1,	3);
	SetItemRarity(	"mineral7",		"Monster",		0.1,	1,	3);
	SetItemRarity(	"mineral8",		"Monster",		0.1,	1,	1);
	SetItemRarity(	"mineral9",		"Monster",		0.1,	1,	3);
	SetItemRarity(	"mineral10",	"Monster",		0.001,	1,	3);
	SetItemRarity(	"mineral12",	"Monster",		0.025,	1,	1);
	SetItemRarity(	"Statue1",		"Monster",		0.005,	1,	1);
	SetItemRarity(	"indian1",		"Monster",		0.03,	1,	1);
	SetItemRarity(	"indian2",		"Monster",		0.03,	1,	3);
	SetItemRarity(	"indian3",		"Monster",		0.05,	1,	1);
	SetItemRarity(	"indian5",		"Monster",		0.05,	1,	1);
	SetItemRarity(	"indian6",		"Monster",		0.005,	1,	1);
	SetItemRarity(	"indian7",		"Monster",		0.07,	1,	1);
	SetItemRarity(	"indian8",		"Monster",		0.1,	1,	1);
	SetItemRarity(	"indian10",		"Monster",		0.005,	1,	1);
	SetItemRarity(	"indian12",		"Monster",		0.3,	1,	1);
	SetItemRarity(	"indian13",		"Monster",		0.05,	1,	1);
	SetItemRarity(	"indian14",		"Monster",		0.1,	1,	1);
	SetItemRarity(	"indian15",		"Monster",		0.005,	1,	1);
	SetItemRarity(	"indian16",		"Monster",		0.001,	1,	1);
	SetItemRarity(	"indian17",		"Monster",		0.06,	1,	1);
	SetItemRarity(	"indian18",		"Monster",		0.005,	1,	1);
	SetItemRarity(	"indian19",		"Monster",		0.005,	1,	1);
	SetItemRarity(	"indian20",		"Monster",		0.005,	1,	1);
	SetItemRarity(	"indian21",		"Monster",		0.005,	1,	1);
	SetItemRarity(	"indian22",		"Monster",		0.005,	1,	1);
	SetItemRarity(	"jewelry1",		"Monster",		0.1,	1,	4);
	SetItemRarity(	"jewelry2",		"Monster",		0.1,	1,	4);
	SetItemRarity(	"jewelry3",		"Monster",		0.1,	1,	4);
	SetItemRarity(	"jewelry4",		"Monster",		0.1,	1,	4);
	SetItemRarity(	"jewelry5",		"Monster",		0.3,	1,	4);
	SetItemRarity(	"jewelry7",		"Monster",		0.05,	1,	1);
	SetItemRarity(	"jewelry10",	"Monster",		0.3,	1,	1);
	SetItemRarity(	"jewelry11",	"Monster",		0.2,	1,	6);
	SetItemRarity(	"jewelry13",	"Monster",		0.01,	1,	4);
	SetItemRarity(	"jewelry14",	"Monster",		0.01,	1,	4);
	SetItemRarity(	"jewelry15",	"Monster",		0.02,	1,	4);
	SetItemRarity(	"jewelry16",	"Monster",		0.01,	1,	4);
	SetItemRarity(	"jewelry17",	"Monster",		0.1,	1,	5);
	SetItemRarity(	"jewelry18",	"Monster",		0.1,	1,	1);

	SetItemRarity(	"mineral2",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"mineral3",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"mineral4",		"Citizen",		0.05,	1,	1);
	SetItemRarity(	"mineral5",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"mineral6",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"mineral7",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"mineral14",	"Citizen",		0.05,	1,	1);
	SetItemRarity(	"indian3",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"indian4",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"indian5",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"indian7",		"Citizen",		0.01,	1,	1);
	SetItemRarity(	"indian8",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"indian9",		"Citizen",		0.2,	1,	1);
	SetItemRarity(	"indian10",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"indian12",		"Citizen",		0.2,	1,	1);
	SetItemRarity(	"indian13",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"indian14",		"Citizen",		0.2,	1,	1);
	SetItemRarity(	"indian16",		"Citizen",		0.2,	1,	1);
	SetItemRarity(	"indian17",		"Citizen",		0.01,	1,	1);
	SetItemRarity(	"jewelry1",		"Citizen",		0.05,	1,	1);
	SetItemRarity(	"jewelry6",		"Citizen",		0.1,	1,	1);
	SetItemRarity(	"jewelry8",		"Citizen",		0.15,	1,	1);
	SetItemRarity(	"jewelry9",		"Citizen",		0.2,	1,	1);
	SetItemRarity(	"jewelry10",	"Citizen",		0.1,	1,	1);
	SetItemRarity(	"jewelry11",	"Citizen",		0.1,	1,	5);
	SetItemRarity(	"jewelry12",	"Citizen",		0.15,	1,	15);
	SetItemRarity(	"jewelry17",	"Citizen",		0.1,	1,	1);

	SetItemRarity(	"mineral14",	"Citizen_f",	0.05,	1,	1);
	SetItemRarity(	"indian3",		"Citizen_f",	0.1,	1,	1);
	SetItemRarity(	"indian4",		"Citizen_f",	0.1,	1,	1);
	SetItemRarity(	"indian5",		"Citizen_f",	0.1,	1,	1);
	SetItemRarity(	"indian7",		"Citizen_f",	0.01,	1,	1);
	SetItemRarity(	"indian8",		"Citizen_f",	0.1,	1,	1);
	SetItemRarity(	"indian9",		"Citizen_f",	0.2,	1,	1);
	SetItemRarity(	"indian10",		"Citizen_f",	0.1,	1,	1);
	SetItemRarity(	"indian12",		"Citizen_f",	0.2,	1,	1);
	SetItemRarity(	"indian13",		"Citizen_f",	0.1,	1,	1);
	SetItemRarity(	"indian14",		"Citizen_f",	0.2,	1,	1);
	SetItemRarity(	"indian16",		"Citizen_f",	0.2,	1,	1);
	SetItemRarity(	"indian17",		"Citizen_f",	0.1,	1,	1);
	SetItemRarity(	"jewelry1",		"Citizen_f",	0.05,	1,	1);
	SetItemRarity(	"jewelry6",		"Citizen_f",	0.3,	1,	1);
	SetItemRarity(	"jewelry7",		"Citizen_f",	0.2,	1,	1);
	SetItemRarity(	"jewelry8",		"Citizen_f",	0.25,	1,	1);
	SetItemRarity(	"jewelry9",		"Citizen_f",	0.2,	1,	1);
	SetItemRarity(	"jewelry10",	"Citizen_f",	0.3,	1,	1);
	SetItemRarity(	"jewelry11",	"Citizen_f",	0.1,	1,	5);
	SetItemRarity(	"jewelry12",	"Citizen_f",	0.1,	1,	5);
	SetItemRarity(	"jewelry13",	"Citizen_f",	0.2,	1,	1);
	SetItemRarity(	"jewelry14",	"Citizen_f",	0.2,	1,	1);
	SetItemRarity(	"jewelry15",	"Citizen_f",	0.2,	1,	1);
	SetItemRarity(	"jewelry16",	"Citizen_f",	0.4,	1,	1);
	SetItemRarity(	"jewelry18",	"Citizen_f",	0.25,	1,	1);
}

void InitRandItems()
{
	ref rnditem;

	makeref(rnditem, RandItems[0]);
	rnditem.id = "wooden_spoon";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[1]);
	rnditem.id = "Mineral9";
	rnditem.maxQuantity = 2;

	makeref(rnditem, RandItems[2]);
	rnditem.id = "Mineral10";
	rnditem.maxQuantity = 2;

	makeref(rnditem, RandItems[3]);
	rnditem.id = "jewelry16";
	rnditem.maxQuantity = 15;

	makeref(rnditem, RandItems[4]);
	rnditem.id = "jewelry1";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[5]);
	rnditem.id = "jewelry2";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[6]);
	rnditem.id = "jewelry3";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[7]);
	rnditem.id = "jewelry5";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[8]);
	rnditem.id = "jewelry6";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[9]);
	rnditem.id = "jewelry7";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[10]);
	rnditem.id = "jewelry10";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[11]);
	rnditem.id = "jewelry11";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[12]);
	rnditem.id = "jewelry12";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[13]);
	rnditem.id = "jewelry13";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[14]);
	rnditem.id = "silver_spoon";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[15]);
	rnditem.id = "indian4";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[16]);
	rnditem.id = "potion1";
	rnditem.maxQuantity = 3;

	makeref(rnditem, RandItems[17]);
	rnditem.id = "potion2";
	rnditem.maxQuantity = 3;

	makeref(rnditem, RandItems[18]);
	rnditem.id = "indian13";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[19]);
	rnditem.id = "potion3";
	rnditem.maxQuantity = 3;

	makeref(rnditem, RandItems[20]);
	rnditem.id = "potion4";
	rnditem.maxQuantity = 3;

	makeref(rnditem, RandItems[21]);
	rnditem.id = "pistol3";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[22]);
	rnditem.id = "pistol2";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[23]);
	rnditem.id = "pistol1";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[24]);
	rnditem.id = "blade8";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[25]);
	rnditem.id = "blade7";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[26]);
	rnditem.id = "blade6";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[27]);
	rnditem.id = "blade5";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[28]);
	rnditem.id = "blade4";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[29]);
	rnditem.id = "blade3";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[30]);
	rnditem.id = "blade2";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[31]);
	rnditem.id = "spyglass1";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[32]);
	rnditem.id = "spyglass2";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[33]);
	rnditem.id = "blade1";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[34]);
	rnditem.id = "jewelry17";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[35]);
	rnditem.id = "jewelry18";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[36]);
	rnditem.id = "bullet";
	rnditem.maxQuantity = 20;

	makeref(rnditem, RandItems[37]);
	rnditem.id = "mineral3";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[38]);
	rnditem.id = "Mineral4";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[39]);
	rnditem.id = "Mineral5";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[40]);
	rnditem.id = "Mineral6";
	rnditem.maxQuantity = 4;

	makeref(rnditem, RandItems[41]);
	rnditem.id = "Mineral7";
	rnditem.maxQuantity = 1;

	makeref(rnditem, RandItems[42]);
	rnditem.id = "potion5";
	rnditem.maxQuantity = 3;

	makeref(rnditem, RandItems[43]);
	rnditem.id = "potionwine";
	rnditem.maxQuantity = 2;

	makeref(rnditem, RandItems[44]);
	rnditem.id = "potionrum";
	rnditem.maxQuantity = 2;
}

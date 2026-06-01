// KZ > ref 25.10.2024

void extrnInitPerks()
{
	DeleteAttribute(&ChrPerksList, "list");

	/// string id - id перка (описание подхватывается автоматом в AbilityDescribe.txt конструкцией "perk" + id)
	//	string BaseType - тип перков self (личные), ship (корабельные) и trait (черты)
	/// string condition - условие доступности (какие перки прежде должны быть взяты; писать через запятую)
	//	(все int) TimeDelay - кулдаун перка, TimeDuration - время действия перка;
	/// (все bool) PlayerOnly - только для игрока, NPCOnly - только для НПС, Hidden - скрытый перк (не отображается в интерфейсе), Free - перк, не требующий очков способностей;
	//	(все string) OfficerType - тип офицера (navigator, boatswain, cannoner, doctor, carpenter, treasurer, fighter);
	/// (все bool) FemName, FemDescr - у перка или черты имеется женская версия названия / описания.

	////////////////////////  ЛИЧНЫЕ ///////////////////////
	//		id							BaseType	condition									TimeDelay	TimeDuration	PlayerOnly	NPCOnly	OfficerType		Hidden	Free	FemName	FemDescr	Parameters
	/// Защита >
	InitPerk("BasicDefense",			"self",		"",											0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Основы защиты
	InitPerk("AdvancedDefense",			"self",		"BasicDefense",								0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Эксперт защиты
	InitPerk("Ciras",					"self",		"AdvancedDefense",							0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Кираса
	InitPerk("HPPlus",					"self",		"",											0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Растущая жизнь
	/// Атака > Холодное оружие
	InitPerk("BasicAttack",				"self",		"",											0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Основы атаки
	InitPerk("AdvancedAttack",			"self",		"BasicAttack,CriticalHit",					0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Эксперт атаки
	InitPerk("CriticalHit",				"self",		"BasicAttack",								0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Критический удар
	InitPerk("HardHitter",				"self",		"BasicAttack",								0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Тяжёлая рука
	InitPerk("Sliding",					"self",		"AdvancedAttack",							0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Неотразимый удар
	InitPerk("Rush",					"self",		"AdvancedAttack,Sliding,HardHitter",		70,			10,				1,			0,		"",				0,		0,		0,		0,			""); // Ярость
	InitPerk("Tireless",				"self",		"",											0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Неутомимость
	InitPerk("EnergyPlus",				"self",		"Tireless",									0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Растущая энергия
	InitPerk("SecondWind",				"self",		"Tireless,EnergyPlus",						60,			1,				1,			0,		"",				0,		0,		0,		0,			""); // Второе дыхание
	/// Атака и Защита > Холодное оружие
	InitPerk("BladeDancer",				"self",		"AdvancedAttack",							0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Танец с клинком
	InitPerk("SwordplayProfessional",	"self",		"AdvancedDefense,AdvancedAttack",			0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Профессиональный фехтовальщик
	/// Атака > Огнестрел
	InitPerk("Gunman",					"self",		"",											0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Базовая стрельба
	InitPerk("StunningShot",			"self",		"Gunman",									0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Оглушающий выстрел
	InitPerk("GunAdvanced",				"self",		"Gunman",									0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Экспертная стрельба
	InitPerk("Shoottech",				"self",		"GunAdvanced",								0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Техника стрельбы
	InitPerk("MusketsTraining",			"self",		"GunAdvanced",								0,			0,				0,			0,		"",				1,		0,		0,		0,			""); // Мушкетёрская подготовка
	InitPerk("GunProfessional",			"self",		"GunAdvanced",								0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Профессиональная стрельба
	InitPerk("DevilsEye",				"self",		"Shoottech,GunProfessional",				0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Глаз дьявола
	/// Персональные >
	InitPerk("Grus",					"self",		"",											0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Дополнительный вес
	InitPerk("Medic",					"self",		"HPPlus",									0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Отменное здоровье
	InitPerk("ByWorker",				"self",		"",											0,			0,				0,			1,		"",				1,		0,		0,		0,			""); // Совместитель
	InitPerk("ByWorker2",				"self",		"ByWorker",									0,			0,				0,			1,		"",				1,		0,		0,		0,			""); // Совместитель-универсал
	InitPerk("Alchemy",					"self",		"",											0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Алхимия
	InitPerk("SharedExperience",		"self",		"",											0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Обмен опытом
	InitPerk("ShipEscape",				"self",		"",											0,			0,				0,			0,		"",				0,		0,		0,		0,			""); // Спасение на шлюпке
	InitPerk("Trustworthy",				"self",		"",											0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Искусство обмана
	InitPerk("HawkEye",					"self",		"",											0,			0,				0,			0,		"fighter",		0,		0,		0,		0,			""); // Глаз Алмаз
	InitPerk("NachoPuncher",			"self",		"",											0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Кулачный Бой
	InitPerk("DrunkenMaster",			"self",		"NachoPuncher",								0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Пьяный мастер
	InitPerk("WildCaribbean",			"self",		"",											0,			0,				1,			0,		"",				0,		1,		0,		0,			""); // Дикие Карибы

	////////////////////////  КОРАБЕЛЬНЫЕ ///////////////////////
	//		id							BaseType	condition									TimeDelay	TimeDuration	PlayerOnly	NPCOnly	OfficerType		Hidden	Free	FemName	FemDescr	Parameters
	/// ГГ >
	InitPerk("FlagPir",					"ship",		"",											0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Флаг пиратов
	InitPerk("FlagEng",					"ship",		"",											0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Флаг Англии
	InitPerk("FlagFra",					"ship",		"",											0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Флаг Франции
	InitPerk("FlagSpa",					"ship",		"",											0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Флаг Испании
	InitPerk("FlagHol",					"ship",		"",											0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Флаг Голландии
	/// Боцман >
	InitPerk("Brander",					"ship",		"",											0,			0,				0,			0,		"boatswain",	0,		0,		0,		0,			""); // Брандер
	InitPerk("Troopers",				"ship",		"",											0,			0,				0,			0,		"boatswain",	0,		0,		0,		0,			""); // Высадка десанта союзных кораблей
	InitPerk("IronWill",				"ship",		"",											0,			0,				0,			0,		"boatswain",	0,		0,		0,		0,			""); // Железная воля
	InitPerk("LongRangeGrappling",		"ship",		"",											0,			0,				0,			0,		"boatswain",	0,		0,		0,		0,			""); // Абордаж с большого расстояния
	InitPerk("Mentor",					"ship",		"IronWill",									0,			0,				0,			0,		"boatswain",	0,		0,		0,		0,			""); // Наставник
	InitPerk("LootCollection",			"ship",		"Mentor",									0,			0,				0,			0,		"boatswain",	0,		0,		0,		0,			""); // Быстрый сбор трофеев
	InitPerk("MusketsShoot",			"ship",		"IronWill,LongRangeGrappling",				0,			0,				0,			0,		"boatswain",	0,		0,		0,		0,			""); // Мушкетный залп
	InitPerk("GrapplingProfessional",	"ship",		"LongRangeGrappling,MusketsShoot",			0,			0,				0,			0,		"boatswain",	0,		0,		0,		0,			""); // Мастерский абордаж
	/// Казначей >
	InitPerk("BasicCommerce",			"ship",		"",											0,			0,				0,			0,		"treasurer",	0,		0,		0,		0,			""); // Базовая торговля
	InitPerk("QuickCalculation",		"ship",		"",											0,			0,				0,			0,		"treasurer",	0,		0,		0,		0,			""); // Быстрые расчёты
	InitPerk("ArtOfDeals",				"ship",		"BasicCommerce",							0,			0,				0,			0,		"treasurer",	0,		0,		0,		0,			""); // Искусство сделок
	InitPerk("AdvancedCommerce",		"ship",		"BasicCommerce,QuickCalculation",			0,			0,				0,			0,		"treasurer",	0,		0,		0,		0,			""); // Экспертная торговля
	InitPerk("Packer",					"ship",		"AdvancedCommerce",							0,			0,				0,			0,		"treasurer",	0,		0,		0,		0,			""); // Упаковка грузов
	InitPerk("PriceRecon",				"ship",		"AdvancedCommerce,ArtOfDeals",				0,			0,				0,			0,		"treasurer",	0,		0,		0,		0,			""); // Ценовая разведка
	InitPerk("Investor",				"ship",		"AdvancedCommerce,ArtOfDeals",				0,			0,				0,			0,		"treasurer",	0,		0,		0,		0,			""); // Мастерство вкладов
	InitPerk("ProfessionalCommerce",	"ship",		"Investor,PriceRecon,Packer",				0,			0,				0,			0,		"treasurer",	0,		0,		0,		0,			""); // Профессиональная торговля
	InitPerk("CrewSalaryOptimization",	"ship",		"ProfessionalCommerce",				        0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Тотальный аудит
	/// Канонир >
	InitPerk("FastReload",				"ship",		"",											0,			0,				0,			0,		"cannoner",		0,		0,		0,		0,			""); // Быстрая перезарядка
	InitPerk("ImmediateReload",			"ship",		"FastReload",								300,		60,				0,			0,		"cannoner",		0,		0,		0,		0,			""); // Предварительная перезарядка
	InitPerk("HullDamageUp",			"ship",		"",											0,			0,				0,			0,		"cannoner",		0,		0,		0,		0,			""); // Увеличенные повреждения корпусу
	InitPerk("SailsDamageUp",			"ship",		"",											0,			0,				0,			0,		"cannoner",		0,		0,		0,		0,			""); // Увеличенные повреждения парусам
	InitPerk("CrewDamageUp",			"ship",		"",											0,			0,				0,			0,		"cannoner",		0,		0,		0,		0,			""); // Увеличенные повреждения команде
	InitPerk("CriticalShoot",			"ship",		"HullDamageUp,SailsDamageUp,CrewDamageUp",	0,			0,				0,			0,		"cannoner",		0,		0,		0,		0,			""); // Критический выстрел
	InitPerk("LongRangeShoot",			"ship",		"",											0,			0,				0,			0,		"cannoner",		0,		0,		0,		0,			""); // Увеличенное расстояние выстрела
	InitPerk("CannonProfessional",		"ship",		"CriticalShoot,LongRangeShoot,FastReload",	0,			0,				0,			0,		"cannoner",		0,		0,		0,		0,			""); // Профессиональный канонир
	/// Плотник >
	InitPerk("Carpenter",				"ship",		"",											0,			0,				0,			0,		"carpenter",	0,		0,		0,		0,			""); // Базовый ремонт
	InitPerk("Builder",					"ship",		"Carpenter",								0,			0,				0,			0,		"carpenter",	0,		0,		0,		0,			""); // Экспертный ремонт
	InitPerk("Shipbuilder",				"ship",		"Builder",									0,			0,				0,			0,		"carpenter",	0,		0,		0,		0,			""); // Профессиональный ремонт
	InitPerk("Caulking",				"ship",		"",											0,			0,				0,			0,		"carpenter",	0,		0,		0,		0,			""); // Конопачение
	InitPerk("LightRepair",				"ship",		"Caulking",									240,		60,				0,			0,		"carpenter",	0,		0,		0,		0,			""); // Латание пробоин
	InitPerk("InstantRepair",			"ship",		"LightRepair",								240,		30,				0,			0,		"carpenter",	0,		0,		0,		0,			""); // Экстренный ремонт
	InitPerk("SelfRepair",				"ship",		"InstantRepair",							0,			0,				0,			0,		"carpenter",	0,		0,		0,		0,			""); // Полный ремонт
	InitPerk("BasicBattleState",		"ship",		"",											0,			0,				0,			0,		"carpenter",	0,		0,		0,		0,			""); // Базовые укрепления
	InitPerk("AdvancedBattleState",		"ship",		"BasicBattleState",							0,			0,				0,			0,		"carpenter",	0,		0,		0,		0,			""); // Экспертные укрепления
	InitPerk("ShipDefenseProfessional",	"ship",		"AdvancedBattleState",						0,			0,				0,			0,		"carpenter",	0,		0,		0,		0,			""); // Профессиональные укрепления
	InitPerk("MasterOverload",			"ship","Shipbuilder,ShipDefenseProfessional,SelfRepair",0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Мастер перегруза
	/// Штурман >
	InitPerk("ShipSpeedUp",				"ship",		"",											0,			0,				0,			0,		"navigator",	0,		0,		0,		0,			""); // Увеличение скорости корабля
	InitPerk("ShipTurnRateUp",			"ship",		"",											0,			0,				0,			0,		"navigator",	0,		0,		0,		0,			""); // Увеличение манёвренности корабля
	InitPerk("StormProfessional",		"ship",		"",											0,			0,				0,			0,		"navigator",	0,		0,		0,		0,			""); // Плавание в штормах
	InitPerk("WindCatcher",				"ship",		"",											0,			0,				0,			0,		"navigator",	0,		0,		0,		0,			""); // Увеличение динамики
	InitPerk("SailsMan",				"ship",		"",											0,			0,				0,			0,		"navigator",	0,		0,		0,		0,			""); // Быстрые паруса
	InitPerk("Turn180",					"ship",		"ShipSpeedUp,ShipTurnRateUp,WindCatcher",	240,		60,				0,			0,		"navigator",	0,		0,		0,		0,			""); // Манёвренный разворот корабля
	InitPerk("SailingProfessional",		"ship",		"SailsMan,StormProfessional,Turn180",		0,			0,				0,			0,		"navigator",	0,		0,		0,		0,			""); // Опытный мореплаватель
	InitPerk("SeaDogProfessional",		"ship",		"SailingProfessional",						0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Гроза морей
	/// Врач >
	InitPerk("Naturalcure",				"ship",		"",											0,			0,				0,			0,		"doctor",		0,		0,		0,		0,			""); // Лечение травами
	InitPerk("Doctor1",					"ship",		"",											0,			0,				0,			0,		"doctor",		0,		0,		0,		0,			""); // Первая помощь
	InitPerk("Doctor2",					"ship",		"Doctor1",									0,			0,				0,			0,		"doctor",		0,		0,		0,		0,			""); // Эксперт хирургии
	InitPerk("LifeSupport",				"ship",		"",											0,			0,				0,			0,		"doctor",		0,		0,		0,		0,			""); // Поддержание жизни
	InitPerk("Aptekar",					"ship",		"Naturalcure,Doctor1",						0,			0,				0,			0,		"doctor",		0,		0,		0,		0,			""); // Аптекарство
	InitPerk("Prevention",				"ship",		"LifeSupport,Aptekar",						0,			0,				0,			0,		"doctor",		0,		0,		0,		0,			""); // Профилактика
	InitPerk("PainResistance",			"ship",		"Doctor2,Aptekar",							0,			0,				0,			0,		"doctor",		1,		0,		0,		0,			""); // Устойчивость к боли		(< скрыт) TODO
	InitPerk("PersonalCare",			"ship",		"Prevention",								0,			0,				0,			0,		"doctor",		0,		0,		0,		0,			""); // Персональный уход
	InitPerk("Doctor3",					"ship",		"Doctor2,Prevention",						0,			0,				0,			0,		"doctor",		0,		0,		0,		0,			""); // Профессиональная медицина
	InitPerk("Sanitary",				"ship",		"Doctor3",									0,			0,				1,			0,		"",				0,		0,		0,		0,			""); // Абсолютная санитария
	InitPerk("SeaSavior",				"ship",		"",											0,			0,				1,			0,		"",				1,		0,		0,		0,			""); // Спаситель морей			(< скрыт)
	InitPerk("Feldsher",				"ship",		"",											0,			0,				0,			0,		"",				1,		0,		0,		0,			""); // Фельдшер				(< скрыт)
	InitPerk("Sanitar",					"ship",		"",											0,			0,				0,			0,		"",				1,		0,		0,		0,			""); // Санитария				(< скрыт)
	/// Капеллан >
	InitPerk("Capellan1",				"ship",		"",											0,			0,				0,			1,		"capellan",		0,		0,		0,		0,			""); // Проповедь
	InitPerk("Capellan2",				"ship",		"",											0,			0,				0,			1,		"capellan",		0,		0,		0,		0,			""); // Причастие

	////////////////////////  ЧЕРТЫ ///////////////////////
	// Traits Group | ReCon Team
	/// BaseType "trait" - особенность персонажа, нельзя прокачать
	/// Parameters for interface: sea (blue), self (green), negative (red), dynamic, static, prize, spec, temper
	//		id							BaseType	condition	TimeDelay	TimeDuration	PlayerOnly	NPCOnly	OfficerType	Hidden	Free	FemName	FemDescr	Parameters
	/// ПРИЗОВЫЕ НАВЫКИ
	InitPerk("MapMaker",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"sea,static,prize");			// Картограф > Увеличение скорости корабля на 5% за полную коллекцию карт в атласе
	InitPerk("GhostsGift",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"sea,static,prize");			// Призрачный дар > +6% скорость, +6% манёвренность, +6% бейдевинд за морскую победу над проклятым ЛГ
	InitPerk("Merman",					"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,prize");			// Пловец > В 2 раза увеличена скорость плавания за 5 минут мучения в водах ГПК
	InitPerk("SlaveTraderTrait",		"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,prize");			// Гроза невольников > Наценка X% при продаже рабов, бонусы на плантации за завершение квеста "Работорговец"
	InitPerk("Duelist",					"trait",	"",			0,			0,				0,			0,		"",			0,		0,		1,		0,			"self,static,prize");			// Записной дуэлянт > +5% наносимого, -5% входящего урона на дуэли радиус поиска противников 15 метров за выполнение пяти "Дел чести"
	InitPerk("InquisitionBlessing",		"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,prize");			// Благословение инквизиции > +20% урона по монстрам, нежити и индейцам
	InitPerk("WitchCharm",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,prize");			// Ведьмовский оберег > -20% получаемого урона от монстров, нежити и индейцев

	/// ОСОБЕННОСТИ ПЕРСОНАЖЕЙ
	InitPerk("Schemer",					"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,prize");			// Махинатор > Возможность торговать контрабандой в составе эскадры, а так же на кораблях третьего класса.
	InitPerk("HighwaySmuggler",			"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Черта Малькольма Фауна, функционала нет
	InitPerk("BasePirate",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Посредник > Бонусы за стартовую нацию пиратов (сейчас это только возможность купить контрабанду в магазине)
	InitPerk("Energaiser",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Энергичность > Ускорение восстановления энергии в 1.5 раза, даётся ГГ, некоторым офицерам и боссам
	InitPerk("LoyalOff",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		1,		0,			"self,static,spec");			// Лояльность > Метка для офицеров с DontGo
	InitPerk("Monk",					"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Монах > Метка для них
	InitPerk("SweetBaby",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Неотразимая красотка > Метка для романтического интереса ГГ: Изабелла, Мари, даньки, дочки губернаторов, и т.д.
	InitPerk("PGGTrait",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Вольный капитан > Метка для ПГГ
	InitPerk("Nobleman",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		1,		0,			"self,static,spec");			// Дворянин > Метка для соотв статуса
	InitPerk("OneLegMan",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Одноногий > Метка для Леклерка с его анимацией ходьбы
	InitPerk("SaveLoadAbuser",			"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec,negative");	// Шулерство > Для любителей S/L
	InitPerk("Monomania",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Мономания
	InitPerk("Stuttering",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec,negative");	// Заикание
	InitPerk("Redskin",					"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Индеец
	InitPerk("NoCaptain",				"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Ведомый
	InitPerk("MusketeerOnly",			"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Убеждённый стрелок
	InitPerk("WeaponBonding",			"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Оружейная привязанность
	InitPerk("DuglasSchool",			"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static,spec");			// Мушкетерская спецподготовка


	/// ЧЕРТЫ ХАРАКТЕРА
	InitPerk("Honest",					"trait",	"",			0,			0,				0,			0,		"",			0,		0,		1,		0,			"self,static,temper");			// Порядочность > Метка для NPC с "good" alignment
	InitPerk("Rebel",					"trait",	"",			0,			0,				0,			0,		"",			0,		0,		1,		0,			"self,static,temper");			// Бунтарство > Метка для NPC с "bad" alignment
	InitPerk("Bully",					"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,dynamic,temper,negative");// Бретёрство > Для активных драчунов; посетители таверны отказываются выпивать примерно 2 месяца
	InitPerk("Dignity",					"trait",	"",			0,			0,				0,			0,		"",			0,		0,		0,		0,			"self,static");					// Достоинство > Блокирует кулачный бой


	/// черта Дугласа на навык стрельбы из двуствольного,
	/// черта Тичингиту, Шеппард, Блекера и т.д. с кратким описанием
}

void InitPerk(string sPerk, string sType, string sCond, int iDelay, int iDuration, bool bPlayer, bool bNPC, string sOfficer, bool bHidden, bool bFree, bool bFem, bool bFemDescr, string sParams)
{
	int i, q;
	string sTemp;

	sPerk = stripblank(sPerk);
	ChrPerksList.list.(sPerk).descr = "perk" + sPerk;
	ChrPerksList.list.(sPerk).BaseType = sType;

	if (sCond != "")
	{
		q = KZ|Symbol(sCond, ",");
		
		for (i = 0; i <= q; i++)
		{
			sTemp = GetSubStr(sCond, ",", i);
			ChrPerksList.list.(sPerk).condition.(sTemp) = true;
		}
	}

	if (iDelay != 0)
		ChrPerksList.list.(sPerk).TimeDelay	= iDelay;

	if (iDuration != 0)
		ChrPerksList.list.(sPerk).TimeDuration = iDuration;

	if (bPlayer)
		ChrPerksList.list.(sPerk).PlayerOnly = true;
	else
	{
		if (bNPC)
			ChrPerksList.list.(sPerk).NPCOnly = true;
	}

	if (sOfficer != "")
		ChrPerksList.list.(sPerk).OfficerType = sOfficer;

	if (bHidden)
		ChrPerksList.list.(sPerk).Hidden = true;

	if (bFree)
		ChrPerksList.list.(sPerk).Free = true;

	if (bFem)
		ChrPerksList.list.(sPerk).FemName = true;

	if (bFemDescr)
		ChrPerksList.list.(sPerk).FemDescr = true;

	if (sParams != "")
		ChrPerksList.list.(sPerk).Parameters = sParams;
}

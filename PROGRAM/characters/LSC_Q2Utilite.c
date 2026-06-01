// Warship -->
// Выставлялка рандомных скиллов
void SetRandSelfSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Leadership = _min + rand(iDelta);
	_ch.skill.FencingLight = _min + rand(iDelta);
	_ch.skill.Fencing = _min + rand(iDelta);
	_ch.skill.FencingHeavy = _min + rand(iDelta);
	_ch.skill.Pistol = _min + rand(iDelta);
	_ch.skill.Fortune = _min + rand(iDelta);
	_ch.skill.Sneak = _min + rand(iDelta);
}

void SetRandShipSkill(ref _ch, int _min, int _max)
{
	int iDelta = _max-_min;
	_ch.skill.Sailing = _min + rand(iDelta);
	_ch.skill.Commerce = _min + rand(iDelta);
	_ch.skill.Accuracy = _min + rand(iDelta);
	_ch.skill.Cannons = _min + rand(iDelta);
	_ch.skill.Repair = _min + rand(iDelta);
	_ch.skill.Grappling = _min + rand(iDelta);
	_ch.skill.Defence = _min + rand(iDelta);
}

// Установить персу все перки
void SelAllPerksToChar(ref _ch, bool _isOfficer)
{
	// Личные
	/// Защита >
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.Ciras = "1";
	_ch.perks.list.HPPlus = "1";
	/// Атака > Холодное оружие
	_ch.perks.list.BasicAttack = "1";
	_ch.perks.list.AdvancedAttack = "1";
	_ch.perks.list.CriticalHit = "1";
	_ch.perks.list.HardHitter = "1";
	_ch.perks.list.Sliding = "1";
	_ch.perks.list.Rush = "1";
	_ch.perks.list.Tireless = "1";
	_ch.perks.list.EnergyPlus = "1";
	_ch.perks.list.SecondWind = "1";
	/// Атака и Защита > Холодное оружие
	_ch.perks.list.BladeDancer = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	/// Атака > Огнестрел
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.StunningShot = "1";
	_ch.perks.list.GunAdvanced = "1";
	_ch.perks.list.Shoottech = "1";
	_ch.perks.list.MusketsTraining = "1";
	_ch.perks.list.GunProfessional = "1";
	_ch.perks.list.DevilsEye = "1";
	/// Персональные >
	_ch.perks.list.Grus = "1";
	_ch.perks.list.Medic = "1";
	_ch.perks.list.Alchemy = "1";
	_ch.perks.list.SharedExperience = "1";
	_ch.perks.list.ShipEscape = "1";
	_ch.perks.list.Trustworthy = "1";
	_ch.perks.list.HawkEye = "1";

	// Корабельные
	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	/// Канонир >
	_ch.perks.list.FastReload = "1";
	_ch.perks.list.ImmediateReload = "1";
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	_ch.perks.list.CannonProfessional = "1";
	/// Боцман >
	_ch.perks.list.Brander = "1";
	_ch.perks.list.Troopers = "1";
	_ch.perks.list.IronWill = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.LootCollection = "1";
	_ch.perks.list.MusketsShoot = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.Mentor = "1";
	/// Плотник >
	_ch.perks.list.Carpenter = "1";
	_ch.perks.list.Builder = "1";
	_ch.perks.list.Shipbuilder = "1";
	_ch.perks.list.Caulking = "1";
	_ch.perks.list.LightRepair = "1";
	_ch.perks.list.InstantRepair = "1";
	_ch.perks.list.SelfRepair = "1";
	_ch.perks.list.BasicBattleState = "1";
	_ch.perks.list.AdvancedBattleState = "1";
	_ch.perks.list.ShipDefenseProfessional = "1";
	_ch.perks.list.MasterOverload = "1";
	/// Штурман >
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SailingProfessional = "1";
	_ch.perks.list.SeaDogProfessional = "1";
	/// Врач >
	_ch.perks.list.Naturalcure = "1";
	_ch.perks.list.Doctor1 = "1";
	_ch.perks.list.Doctor2 = "1";
	_ch.perks.list.LifeSupport = "1";
	_ch.perks.list.Aptekar = "1";
	_ch.perks.list.Prevention = "1";
	// _ch.perks.list.PainResistance = "1";
	_ch.perks.list.PersonalCare = "1";
	_ch.perks.list.Doctor3 = "1";
	_ch.perks.list.Sanitary = "1";
	// _ch.perks.list.SeaSavior = "1";
	// _ch.perks.list.Feldsher = "1";
	// _ch.perks.list.Sanitar = "1";
	/// Казначей >
	_ch.perks.list.BasicCommerce = "1";
	_ch.perks.list.QuickCalculation = "1";
	_ch.perks.list.ArtOfDeals = "1";
	_ch.perks.list.AdvancedCommerce = "1";
	_ch.perks.list.Packer = "1";
	_ch.perks.list.PriceRecon = "1";
	_ch.perks.list.Investor = "1";
	_ch.perks.list.ProfessionalCommerce = "1";
	_ch.perks.list.CrewSalaryOptimization = "1";
	
	if(_isOfficer) // У офов есть доп. перки
	{
		_ch.perks.list.ByWorker = "1";
		_ch.perks.list.ByWorker2 = "1";
	}
	
	//Для интерфейса
	_ch.AllSelf = "";
	_ch.AllShip = "";
}

// Установить персу половину перков
void SetHalfPerksToChar(ref _ch, bool _isOfficer)
{
	// Личные
	/// Защита >
	_ch.perks.list.BasicDefense = "1";
	_ch.perks.list.AdvancedDefense = "1";
	_ch.perks.list.Ciras = "1";
	/// Атака > Холодное оружие
	_ch.perks.list.BasicAttack = "1";
	_ch.perks.list.AdvancedAttack = "1";
	_ch.perks.list.CriticalHit = "1";
	/// Атака и Защита > Холодное оружие
	_ch.perks.list.BladeDancer = "1";
	_ch.perks.list.SwordplayProfessional = "1";
	/// Атака > Огнестрел
	_ch.perks.list.Gunman = "1";
	_ch.perks.list.StunningShot = "1";
	_ch.perks.list.GunAdvanced = "1";
	/// Персональные >
	_ch.perks.list.Medic = "1";
	_ch.perks.list.Alchemy = "1";
	_ch.perks.list.SharedExperience = "1";

	// Корабельные
	_ch.perks.list.FlagPir = "1";
	_ch.perks.list.FlagEng = "1";
	_ch.perks.list.FlagFra = "1";
	_ch.perks.list.FlagSpa = "1";
	_ch.perks.list.FlagHol = "1";
	/// Канонир >
	_ch.perks.list.HullDamageUp = "1";
	_ch.perks.list.SailsDamageUp = "1";
	_ch.perks.list.CrewDamageUp = "1";
	_ch.perks.list.CriticalShoot = "1";
	_ch.perks.list.LongRangeShoot = "1";
	/// Боцман >
	_ch.perks.list.IronWill = "1";
	_ch.perks.list.LongRangeGrappling = "1";
	_ch.perks.list.MusketsShoot = "1";
	_ch.perks.list.GrapplingProfessional = "1";
	_ch.perks.list.Mentor = "1";
	/// Плотник >
	// ...
	/// Штурман >
	_ch.perks.list.ShipSpeedUp = "1";
	_ch.perks.list.ShipTurnRateUp = "1";
	_ch.perks.list.StormProfessional = "1";
	_ch.perks.list.WindCatcher = "1";
	_ch.perks.list.SailsMan = "1";
	_ch.perks.list.Turn180 = "1";
	_ch.perks.list.SailingProfessional = "1";
	/// Врач >
	_ch.perks.list.Naturalcure = "1";
	_ch.perks.list.Doctor1 = "1";
	/// Казначей >
	// ...
	
	
	if(_isOfficer) // У офов есть доп. перки
	{
		_ch.perks.list.ByWorker = "1";
		_ch.perks.list.ByWorker2 = "1";
	}
}

// Отобрать все предметы (кроме квестовых) у выбранного персонажа
void RemoveAllCharacterItems(ref _ch, bool _removemoney)
{
	// сносим нафик всю экипировку
	if(_ch == GetMainCharacter())
	{
		StoreEquippedMaps(_ch);
	}
	RemoveCharacterEquip(_ch, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(_ch, GUN_ITEM_TYPE);
    RemoveCharacterEquip(_ch, MUSKET_ITEM_TYPE);
	RemoveCharacterEquip(_ch, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(_ch, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(_ch, MAPS_ITEM_TYPE);
	
	//сносим все предметы, кроме квестовых -->
	aref arItems;
	string sName;
	ref rLoc;
	int a;
	makearef(arItems, _ch.items);
	int	Qty = GetAttributesNum(arItems);
	for (a=0; a<Qty; a++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if (rLoc.ItemType == "QUESTITEMS")
		{
			_ch.questTemp.items.(sName) = _ch.items.(sName);
		}
	}			
	DeleteAttribute(_ch, "items");
	_ch.items = "";
	makearef(arItems, _ch.questTemp.items);
	Qty = GetAttributesNum(arItems);
	for (a=0; a<Qty; a++)
	{		
		sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(_ch, sName, sti(arItems.(sName)));
	}		
	DeleteAttribute(_ch, "questTemp.items");
	
	if(_removemoney)
	{
		_ch.money = 0;
	}
}

// снести всех пассажиров и компаньонов ГГ
void RemoveAllPassengersAndCompanions()
{
    int iDay = GetPassengersQuantity(pchar);
    int i = 0;
    int n = 0;
	int idx;
	ref ch;
	
 	while (i < iDay)
	{
		i++;
		idx = GetPassenger(pchar, n); // всегда первый в массиве со смещением, если не трем
		if (idx == -1) break;
		ch = GetCharacter(idx);
		if (GetRemovable(ch)) // квестовых не трогаем
		{
		    ch.LifeDay = 1; // чтоб не сразу потерся
		    RemovePassenger(pchar, ch);
			ChangeCharacterAddress(ch,"none","");
		}
		else
		{
		    n++;
		}
	}
    for (i=0; i<COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(pchar, i);
		if (idx != -1)
		{
            ch = GetCharacter(idx);
			if (GetShipRemovable(ch) && GetRemovable(ch))  // не трогаем квестовых и ПГГ
			{
			    ch.LifeDay = 1; // чтоб не сразу потерся
			    RemoveCharacterCompanion(pchar, ch);
			}
		}
	}
}

void CleanAllShipBoxes(bool bDeleteAll)
{
	ref rLoc;
	int i, n;
	string sTemp, sLoc = Pchar.SystemInfo.CabinType;
	
    for (i = 0; i < 4; i++)
	{
		if (i > 0)
		{
			if (i > 1 && !bDeleteAll) // KZ > bDeleteAll = 0 - зачистить только сундуки в кабине и в трюме, как в оригинале; bDeleteAll = 1 - удалить вещи во всех сундуках на корабле ГГ
				break;
			
			if (i == 1)
				sLoc = "My_Deck";
			else
			{
				if (i == 2)
					sLoc = "My_Deck_Medium";
				else
					sLoc = "My_Campus";
			}
		}
		
		if (FindLocation(sLoc) < 0)
			continue;
		
		rLoc = &locations[FindLocation(sLoc)];
		
		for (n = 1; n <= 4; n++)
		{
			sTemp = "box" + n;
			
			if (!CheckAttribute(rLoc, sTemp))
				continue;
			
			DeleteAttribute(rLoc, sTemp + ".items");
			rLoc.(sTemp).items = "";
			rLoc.(sTemp) = Items_MakeTime(0, 0, 1, 2024);
			rLoc.(sTemp).money = 0;
		}
	}
}

// Метод вернёт случайный тип корабля, который зависит от класса шипа персонажа
// AlexBlade - Нигде не используется, закомментил
/*int RandShipFromShipClass(ref _ch)
{
	int iShipClass = sti(RealShips[sti(_ch.Ship.Type)].Class);
	int iShipType;
	switch(iShipClass)
	{
		case 1:
			iShipType = SHIP_WARSHIP + rand(2);
			break;
			
		case 2:
			iShipType = SHIP_FRIGATE + rand(1);
			break;
		
		case 3:
			iShipType = SHIP_CORVETTE + rand(2);
			break;
			
		case 4:
			iShipType = SHIP_FLEUT + rand(2);
			break;
			
		case 5:
			iShipType = SHIP_BARQUE + rand(1);
			break;
			
		case 6:
			iShipType = SHIP_SLOOP + rand(1);
			break;
			
		case 7:
			iShipType = SHIP_WAR_TARTANE + rand(1);
			break;
	}
	return iShipType;
}*/

// Метод вернёт значение атрибута
string GetAttrValue(ref _rChar, string _sAttr)
{
	string sTemp;
	if(!CheckAttribute(_rChar, _sAttr)) _rChar.(_sAttr) = "";
	
	sTemp = _rChar.(_sAttr);
	return sTemp;
}

// Получить рандомную локацию с указанным типом на заданном острове
string IslandGetLocationFromType(string _island, string _type)
{
	ref rLoc;
	int i, iMaxLoc[MAX_LOCATIONS];
	int iRandLoc = 0;
	string sArealType;

	for (i = 1; i < MAX_LOCATIONS; i++)
	{
		makeref(rLoc, locations[i]);
		sArealType = "islandId";

		if (CheckAttribute(rLoc, "islandIdAreal"))
			sArealType += "Areal";

		if (rLoc.type == _type && CheckAttrValue(rLoc, sArealType, _island))
		{
			iMaxLoc[iRandLoc] = i;
			iRandLoc++;
		}
	}

	if (iRandLoc == 0)
		return "none"; // > TODO убрать везде эти грёбанные none

	i = iMaxLoc[rand(iRandLoc - 1)];
	return locations[i].id;
}

// Просто сокращение -->
void DisableAllExits(bool _truefalse)
{
	chrDisableReloadToLocation = _truefalse;
	bDisableFastReload         = _truefalse;
}
// Просто сокращение <--

// Warship <--

void LockQuestLine(ref refChar) // Лочим квестовую линейку
{
	refChar.notQuestLine = true;
}

// Получить локацию для генерации банды
// Rosarak. Оставим здесь ареал без реалма для разброса
string QuestGetGangLocation(string _areal)	
{
	int n;
	string island = GetArealByCityName(_areal);
	string LocationId;
	string LocationType, sAreal;
	int storeArray[MAX_LOCATIONS];
	int howStore = 0;

	for(n=0; n<MAX_LOCATIONS; n++)
	{				
		if(GetArealByLocation(&locations[n]) == island)
		{			
			//на всякий случай
			if(CheckAttribute(&locations[n], "DisableEncounters")) continue;
			if (!CheckAttribute(&locations[n], "type")) continue;
			LocationType = locations[n].type;
			if (LocationType != "jungle" && LocationType != "seashore")
			{
				continue;
			}
			LocationId = locations[n].id;
			if (HasStrEx(LocationId, "jungle,Shore,CaveEntrance", "|"))
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	n = storeArray[rand(howStore-1)];
	return locations[n].id;
}

string GetColonyExpect2Colonies(string _city1, string _city2) // Исключая две колонии
{
	int storeArray[MAX_COLONIES];
	int howStore = 0;
	string sChrId;
	ref rColony;

	for(int n=0; n<MAX_COLONIES; n++)
	{
		makeref(rColony, colonies[n]);
		if(!CheckAttribute(rColony, "HasNoFort") && rColony.nation != "none" && sti(rColony.nation) != PIRATE && or(sti(pchar.nation == PIRATE) && GetNationRelation(GetCityNation(_city1), sti(rColony.nation)) != RELATION_ENEMY, GetNationRelation2MainCharacter(sti(rColony.nation)) != RELATION_ENEMY) && rColony.id != "Panama" && rColony.id != _city1 && rColony.id != _city2)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	return colonies[storeArray[rand(howStore-1)]].id;
}

void initStartState2Character(ref ch)
{// метод вызывается в момент новой игры, заполняет главного героя атрибутами, чтоб убрать лишние проверки в if
    NullCharacter.Siege = "";
    
	ch.SystemInfo.SaveCount = 0;
    ch.SystemInfo.LoadCount = 0;
    ch.SystemInfo.DeadCount = 0;

    ch.SystemInfo.CabinType          = ""; // boal 28.03.05 каюты нет  My_Cabin_Small
    
    ch.questTemp.Contraband.relation = 60;
    ch.questTemp.Indian.relation = 30; // репа у индейцев, от 0 до 100, выше 60 - друг, ниже 20 - враг
    DeleteAttribute(ch, "quest.meeting");
    ch.ShipInStock = 0; // кораблей в порту
	ch.questTemp.abordage = 0;   // двойной абордаж
	ch.questTemp.donate   = 0; // пожертвование церкви

	ch.questTemp.friend_in_tavern = ""; // оптимизация boal
	ch.questTemp.RelationAgentMet = "0"; // оптимизация boal

	ch.questTemp.NationQuest = ""; // взятая линейка квестов

	ch.GenQuest.BrothelCount = "0"; // счетчик посещений девочек
	//ch.GenQuest.Hunter2Pause   = false; // признак бойни в форте на суше - не делать ОЗГов
	ch.I_MAP_SHOW = false;  // boal карты смотрим из предметов
	ch.CameraHoldPos = false;
	ch.CameraShipNPC = 0;// номер компаньона для камеры 0 - ГГ
	ch.GenQuestFort.FarLocator = true; // для методов пихания фантомов в город

	// Черная жемчужина
	ch.GenQuest.GhostShip.DeadByMe       = 0;
	ch.GenQuest.GhostShip.KillMe         = 0;
	ch.GenQuest.GhostShip.AskAbout       = 0; // в таверне три раза спросить до появления
	ch.GenQuest.GhostShip.lastspeak_date = "";
    GhostShipInit();
    
    ch.GenQuest.Find_Merchant.lastspeak_date = "";
    ch.GenQuest.ConvoyPassenger = ""; //структура недовольных по квесту доставки пассажира

	// ==> Стираем квест метки на глобальной карте (чтобы избежать ненужного дублирования)
	if (CheckAttribute(&TEV, "MapQuestMarks"))
    {
        DeleteAttribute(&TEV, "MapQuestMarks");
    }
	// ==> состояние квеста текущей линейки
	ch.questTemp.State = "";
	// ==> кол-во дней ожидания выдачи следующего квеста губером, стандарт - два дня
	ch.questTemp.Waiting_time = "2";
	// ==> номер текущего квеста, присваиваем сразу второй, т.к. первый берётся на момент первого обращения к губеру.
	ch.questTemp.CurQuestNumber = "2";
	//параметры островов и бухт для корсарского метро, ПГГ, и много ещё чего
	InitTravelMap();
	// ==> проверка не посещение борделей после свадьбы
	pchar.RomanticQuest.HorseCheck = -1;
	// ==> Количество карт в навигационном атласе
	ResetMapMakerAtlas();
	// ==> Номер пиратского флага (берётся из текстуры персональных флагов ГГ)
	ch.Flags.Pirate = 3;
	// ==> Квест Аскольда.
    ch.questTemp.Ascold = "canTakeQuest"; // состояние, если равен "", то пока не даем квест.
	// ==> работорговец
	ch.questTemp.Slavetrader = "canTakeQuest"; //сюда же пихаем флаг
	// ==> общий индекс Аззи.
    ch.questTemp.Azzy = "1";
	// ==> выбор хозяна магазина и уличного торговца по Аскольду.
	SelectAscoldRendom();
	// ==> выбор ростовщика-работорговца
	SelectSlavetraderRendom(); //это непосредственно выбор
	// ==> квест Изабеллы
	IsabellaInit();
	// ==> Квест Сопровождение флейта 'Орион'
	Andre_Abel_Quest_Init();
	// ==>  флаги и иниты бергларов 
	BerglarsInit();
	// ==>  нищие
	PoormansInit();
	// ==>  дверь в гробницу викинга
	VikingDoorInit();
	// ==>  кол-во лута, отданного шлюхами
	pchar.questTemp.HorseLoot = 0;
	// ==>  кол-во перетраха со шлюхами
	pchar.questTemp.HorseQty = 0;
	// ==> прерывания на ход к жемчужному промыслу
	PearlGen_SetSantaCatalina("none");
	PearlGen_SetTeno("none");
	// ==> спрашивальщики
	// EvgAnat - дикие карибы
	QuestionsInit();
	SeaQuestionsInit(); //02/02/08
	// ==> тюремный флаг на проход внутрь
	ch.questTemp.jailCanMove = false;
	OfficerGirlInit();
	// ==> мушкетеры
	OfficerMushketerInit();
	// ==> линейка ГПК
	ch.questTemp.LSC = false;
	ch.questTemp.LSC.checkBoxes = false; //флаг проверки сундуков в полночь	
	pchar.quest.FirstLoginLostShipsCity.win_condition.l1 = "location";
	pchar.quest.FirstLoginLostShipsCity.win_condition.l1.location = "LostShipsCity_town";
	pchar.quest.FirstLoginLostShipsCity.function = "FirstLoginLostShipsCity";
	// ==> квест получения Синей Птицы
	ch.questTemp.BlueBird = "begin";
	ch.questTemp.BlueBird.City = "";
	ch.questTemp.BlueBird.count = 0;
	// ==> генератор Шарпа по жемчугу
	ch.questTemp.Sharp = "begin";
	ch.questTemp.Sharp.City = "";
	ch.questTemp.Sharp.count = 0; //счетчик кол-ва поисков
	ch.questTemp.Sharp.brothelChance = 1; //античит, шанс встретить Шарпа прямо в борделе
	ch.questTemp.Sharp.SeekSpy = "begin"; //состояние квест на поиски информатора Шарпа
	// ==> пиратская линейка
	PiratesLineInit();
	// ==> набор мелких квестов, дается по одному до закрытия
	ch.questTemp.different = "free";
	// ==> линейка Блада homo
	ch.questTemp.CapBloodLine = true;
	ch.questTemp.CapBUnarmed = false; //ГГ сабля не положена - false
	// ==> линейка Теночтитлана
	ch.questTemp.Teno = "begin";
	pchar.quest.Teno_startInShore.win_condition.l1 = "location";
	pchar.quest.Teno_startInShore.win_condition.l1.location = "Shore53";
	pchar.quest.Teno_startInShore.function = "Teno_startInShore";
	//зачарованный город
	TEV.DesMoinesTimeSkipDisable = "1"; // запрещаем отдых в поселении Дес-Мойнес до снятия проклятия
	TEV.DesMoinesMoorDisable = "1";
	LocatorReloadEnterDisable("Shore_ship3", "reload1", true);
	ch.questTemp.MC = "begin"; //флаг квеста
	pchar.quest.MC_QuestInit.win_condition.l1 = "Rank";
	pchar.quest.MC_QuestInit.win_condition.l1.value = 10;
	pchar.quest.MC_QuestInit.win_condition.l1.operation = ">=";
	pchar.quest.MC_QuestInit.function = "MC_QuestInit";
	//ситуации в море
	ch.CanGenerateShipSituation = true;
	// механика сбора трофеев по умолчанию оригинальная
	TEV.LootCollector.Mode = "0";
	//переменная для хранения крайнего порядкового номера для сортировки СЖ
	TEV.QuestOrder = 1;
	// добавление квест-маркеров
	MainQuestMarks_Init();
}

//==> eddy. квестовая обработка 'ноль часов'.
void QuestActions()
{
	ref sld;
	int i;
	CompanionTravel_ProcessAllTravellers(); // Warship. Процессирование компаньонов-путешественников
	// забираем просроченные лицензии
	for (i=0; i<4; i++)
	{
		if (CheckCharacterItem(pchar, NationShortName(i)+"TradeLicence") && GetDaysContinueNationLicence(i) == -1)
		{
			TakeNationLicence(i);
		}		
	}
	//Если идет линейка ГПК, то шмаляем открытые сундуки. Все, кроме Диффиндура.
	if (sti(pchar.questTemp.LSC.checkBoxes))
	{
		LSC_checkBoxes();
	}
	//************** Фр.линейка, третий квест. открываем двери дома коменданта Гаваны *******************
	if (pchar.questTemp.State == "Fr3TakeAnna_WaitMidnight")
	{
		LocatorReloadEnterDisable("Havana_town", "houseS1", false);
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition.l1 = "location";
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition.l1.location = "Havana_houseS1";
        Pchar.quest.Fr3TakeAnna_FightInHouse.win_condition = "Fr3TakeAnna_FightInHouse";
		pchar.questTemp.State = "Fr3TakeAnna_DoorIsOpen";
	}
	//************** Изабелла, вечер ужина после спасения братца наступил *******************
	if (CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "DelivMigel")
	{		
		pchar.RomanticQuest = "SeeTalkNearHouse"; //детектор на итеме теперь сработает        
        sld = CharacterFromID("MigelDeValdes");
		//Мигель
        sld.dialog.currentnode = "TalkNearHouse_1";
        ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto24");
        LAi_SetActorType(sld);
		sld.rank = 1; //чтобы умер сразу
		sld.skill.Fencing = 1;                
		sld.skill.Pistol = 1;
		LAi_SetHP(sld, 1, 1);
		DeleteAttribute(sld, "Items");
		GiveItem2Character(sld, "blade1");
		GiveItem2Character(sld, "pistol1");
		GiveItem2Character(sld, "order");
		TakeNItems(sld,"bullet", 1);
		TakeNItems(sld,"GunPowder", 1);
		//если ГГ рядом, то начинаем сцену без захода в итем
		if (pchar.location != "SanJuan_houseSp6" && LAi_CharacterSeesThePchar(sld, 10)) SeeBrotherDeadNearHouse();
		//Сальватор с бандюганами
		LAi_group_Delete("EnemyFight");
        sld = CharacterFromID("Husband");
        //sld.dialog.currentnode = "TalkNearHouse_1"; //если успеть поговорить с Сальваторе, то приводило к зависанию т.к. у него такого диалога нет
        ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto25");		
        for (i=15; i<=16; i++)
        {
			sld = GetCharacter(NPC_GenerateCharacter("Bandit_"+i, "citiz_"+(36+i), "man", "man", 30, PIRATE, 1, true)); //watch_quest_moment
			FantomMakeCoolFighter(sld, 30, 80, 70, "blade33", "pistol3", 100);			
			LAi_SetStayType(sld);			
			if (i==15) ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto7");
			else ChangeCharacterAddressGroup(sld, "SanJuan_town", "quest", "goto26");
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		SetTimerCondition("Romantic_DeadBrother_Cancel", 0, 0, 1, false);
	}
	//************** Изабелла, свадьба!!!! *******************
	if (CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "WaitBeginWidding")
	{	
		pchar.RomanticQuest = "BeginWidding";
		pchar.quest.Isabella_widding.win_condition.l1 = "locator";
		pchar.quest.Isabella_widding.win_condition.l1.location = "SanJuan_church";
		pchar.quest.Isabella_widding.win_condition.l1.locator_group = "quest";
		pchar.quest.Isabella_widding.win_condition.l1.locator = "detector1";
		pchar.quest.Isabella_widding.function = "Isabella_widding";
		sld = CharacterFromID("Isabella");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld , "SanJuan_church", "goto",  "goto11");
		sld.dialog.currentnode = "TalkWidding";
		//падре
		LAi_SetActorType(CharacterFromID("SanJuan_Priest"));
		SetTimerCondition("Romantic_Widding_Cancel", 0, 0, 1, false);
	}
	//************** ночной сторож в церкви *******************
	if (CheckAttribute(pchar, "questTemp.different.Church_NightGuard"))
	{
		if (pchar.questTemp.different.Church_NightGuard == pchar.location)
		{
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) < 3)
			{
                pchar.quest.ChurchNightGuard_exitFromLoc.win_condition.l1 = "ExitFromLocation";
                pchar.quest.ChurchNightGuard_exitFromLoc.win_condition.l1.location = pchar.location;
                pchar.quest.ChurchNightGuard_exitFromLoc.function = "ChurchNightGuard_exitFromLoc";
                DoQuestFunctionDelay("ChurchNightGuard_timerInChurch", 10.0 + frand(10.0));
			}
		}
		else
		{	//ГГ не находится в нужной церкви в момент полночи
			string sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			AddQuestRecordEx(sTitle, "Church_NightGuard", "2");
			CloseQuestHeader(sTitle);
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterReputation(pchar, -20);
		}
	}
	//************** линейка ГПК, расшифровка СЖ *******************
	if (CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "LogToDecryptLSC")
	{
	    pchar.questTemp.LSC = "DecryptedLogLSC";
	    sld = ItemsFromID("LogbookLSC");
	    DeleteAttribute(&sld, "read");
	    DeleteAttribute(&sld, "blockRead");
        sld.describe = "itmdescr_LogbookLSCDecrypted";
        AddLandQuestMark_Main(CharacterFromID(pchar.questTemp.LSC.decryptorId), "ISS_PoorsMurder");
	}
	//************** линейка ГПК, переход в погребок таверны *******************
	if (pchar.questTemp.LSC == "toWineCellar")
	{
        sld = characterFromId("LSCBarmen");

		if (GetHour() < 1)
		{
			pchar.questTemp.LSC = "toWineCellarGone";
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FleuronTavern", "rld", "stay1");
			PChar.quest.LSC_returnBarmen.win_condition.l1            = "Timer";
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.hour  = 1;
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.LSC_returnBarmen.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			PChar.quest.LSC_returnBarmen.function = "LSC_returnBarmen";
		}
		else pchar.questTemp.LSC = "toWineCellarLate";

		AddLandQuestMark_Main(sld, "ISS_MainLine");
	}
	//************** линейка ГПК, переход в погребок для подслушивания *******************
	if (pchar.questTemp.LSC == "toInterception")
	{
		if (pchar.location == "FleuronTavern" && LAi_CheckLocatorWithinRadius("item", "detector1", 50))
		{
			DoQuestFunctionDelay("LSC_scriptInterception", 10.0 + frand(20));
		}
		else
		{
			pchar.questTemp.LSC = "InterceptionLate";
			AddQuestRecord("ISS_MainLine", "20");
			AddLandQuestMark_Main(CharacterFromID("LSCBarmen"), "ISS_MainLine");
		}
	}
	//************** линейка ГПК, завал первого каспера с помощь Армо *******************
	if (CheckAttribute(pchar, "questTemp.LSC.Armo"))
	{
		//первый каспер пошёл
		if (sti(pchar.questTemp.LSC.Armo) == 1 || sti(pchar.questTemp.LSC.Armo) == 3 || sti(pchar.questTemp.LSC.Armo) == 5)
		{
			if (GetHour() < 2)
			{
				LAi_group_Delete("EnemyFight");
				sld = characterFromId("Casper_" + pchar.questTemp.LSC.Armo);
				sld.BreakTmplAndFight = true; //проверять на атаку
				sld.reactionOnFightModeOn = true; //проверять на вытаскивание оружия
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				pchar.questTemp.LSC.Armo.casperIdx = sld.index; //запомним индекс, пригодится на выходе
				//таймер на проверку, убит ли каспер
				pchar.quest.LSC_checkCasperDead.win_condition.l1            = "Timer";
				pchar.quest.LSC_checkCasperDead.win_condition.l1.date.hour  = 2;
				pchar.quest.LSC_checkCasperDead.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
				pchar.quest.LSC_checkCasperDead.function = "LSC_checkCasperDead";	
				pchar.quest.LSC_checkCasperDead.casperIdx = sld.index;
				if (pchar.location == "LostShipsCity_town")
				{
                    ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload55");
                    LAi_ActorGoToLocator(sld, "quest", "target", "LSC_casperIsGone", -1.0);
				}
				else
				{
				    ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "target");
                    sld.checkChrDistance = 5; //проверять дистанцию до характерса
                    sld.checkChrDistance.id = "Blaze"; //Id характерса
                    sld.checkChrDistance.time = 0; //время повторной проверки
                    sld.checkChrDistance.node = sld.id; //нода диалога
				}
			}
			else
			{
				pchar.questTemp.LSC.Armo = 11; //профукал каспера
			}
			AddLandQuestMark_Main(CharacterFromID("LSCwaitress"), "ISS_DefeatCasperClan");
		}
	}
	//************** генератор "Продажный патруль" *********************************
	if(CheckAttribute(pchar, "questTemp.ReasonToFast"))
	{
		if(pchar.questTemp.ReasonToFast == "SpeakHorse") // не пришёл в бухту
		{
			AddQuestRecord("ReasonToFast", "2");
			CloseQuestHeader("ReasonToFast");
			pchar.questTemp.ReasonToFast.end = true;
		}
		if(pchar.questTemp.ReasonToFast == "MeetPatrolFail") // в бухту пришёл не один или удачи не хватило
		{
			AddQuestRecord("ReasonToFast", "3");
			CloseQuestHeader("ReasonToFast");
			pchar.questTemp.ReasonToFast.end = true;
		}
		if(CheckAttribute(pchar, "questTemp.ReasonToFast.PatrolLocation"))
		{
			if(CheckAttribute(&Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)],"DisableEncounters"))
			{
				DeleteAttribute(&Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], "DisableEncounters");
			}
		}	
		if(CheckAttribute(pchar, "questTemp.ReasonToFast.end"))
		{
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
		}	
	}
	//************** генератор "Эпидемия на вражеском корабле" **********************
	if(CheckAttribute(pchar,"GenQuest.ShipSituation.Epidemy"))
	{
		ShipSituation_CheckConsequence(sti(pchar.GenQuest.ShipSituation.Epidemy));
	}
	//************** поверка нпс-кэпов 5 и 20 числа каждого месяца *******************
	if(GetDataDay() == 5 || GetDataDay() == 20)
	{
		if (CheckAttribute(&NullCharacter, "capitainBase"))
		{
			string sName;
			int capIndex, a;
			aref arCapBase, arBase;
    		makearef(arBase, NullCharacter.capitainBase);
    		int	Qty = GetAttributesNum(arBase);
    		for (a=0; a<Qty; a++)
    		{
    			arCapBase = GetAttributeN(arBase, a);
				sName = GetAttributeName(arCapBase); //Id кэпа
				capIndex = GetCharacterIndex(sName);
    			//---------- мёртв ------------
				if (capIndex == -1)
    			{	
					//страховка. если квест ещё открыт - закрываем его
					/*if (CheckActiveQuest(arCapBase.Tilte1))
					{
						CitizCapIsDead_CloseQuest(arCapBase, sName);
					}*/
					DeleteAttribute(arBase, sName);
					Qty --; //для корректной работы цикла при удалении записи в базе
					a--;
				}
				//---------- жив ------------
				else
				{
					if (GetNpcQuestPastDayParam(arCapBase, "checkTime") >= sti(arCapBase.checkTime))
					{
						//if (characters[capIndex].location == "none" && characters[capIndex].quest == "InMap")
						//{
							Cap_SetMapAgain(&characters[capIndex], arCapBase);
						//}
					}
				}		
    		}
		}
	}
	//************** Возвращение говорилки остинцам **********************
	if(pchar.questTemp.tugs.berglarState != 0)
	{
		string sTemp;
		for(i=1; i<=6; i++)
		{
			switch(i)
			{
				case 1: sTemp = "SentJons";		break;
				case 2: sTemp = "FortFrance";	break;
				case 3: sTemp = "Marigo";		break;
				case 4: sTemp = "Panama";		break;
				case 5: sTemp = "Cartahena";	break;
				case 6: sTemp = "SantaCatalina";break;
			}
			if (GetCharacterIndex("Berglar"+sTemp) != -1)
			{
				sld = characterFromId("Berglar"+sTemp);
				sld.talker = 7;
			}
		}
	}
}

//снятие квеста, если энкаунтер кэпа исчез на карте
void CitizCapIsDead_CloseQuest(aref arCapBase, string capId)
{
	ref sld;
	string sTemp;
	//снимаем установленный таймер
	sTemp = "SecondTimer_" + capId;
	if (capId == "MushketCap") sTemp = "MushketTimer";
	if (capId == "Danielle")   sTemp = "DanielleTimer";
	pchar.quest.(sTemp).over = "yes";
	//---------- нпс-квестодатель -------------
	int iTemp = GetCharacterIndex(arCapBase.questGiver);
	if (iTemp != -1)
	{
		//снимаем прерывание на смерть квестодателя
		ref npchar = &characters[iTemp];
		if (CheckAttribute(npchar, "quest.PortmansSeekShip") || CheckAttribute(npchar, "quest.PortmansJornal"))
		{
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			DeleteAttribute(npchar, "quest.PortmansJornal");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		}
		else
		{
			sTemp = "SCQ_" + iTemp;
			pchar.quest.(sTemp).over = "yes";
			characters[iTemp].lifeDay = 0;
		}
	}
	string sTitle1 = arCapBase.Tilte1;
	string sTitle2 = arCapBase.Tilte2;
}

//переустанавливаем на карте живого, но потерянного кэпа
void Cap_SetMapAgain(ref sld, aref arCapBase) 
{
	//в морскую группу кэпа
	int iTemp;
	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	switch (arCapBase.quest)
	{
        case "mushket":
            if (sld.cityShore == sld.quest.targetShore)
            {
                sld.quest.targetShore = SelectAnyColony(sld.cityShore);
            }
            Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-5);
        break;
        case "citizen":
            if (sld.city == sld.quest.targetCity)
            {
                sld.quest.targetCity = SelectAnyColony(sld.city);
            }
            Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
        break;
        case "robber":
            if (sld.city == sld.quest.targetCity)
            {
                sld.quest.targetCity = SelectAnyColony(sld.city);
            }
            Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
        break;
        case "jornal":
            if (sld.quest.baseShore == sld.quest.targetCity)
            {
                sld.quest.targetCity = SelectAnyColony(sld.quest.baseShore);
            }
            Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, sti(arCapBase.checkTime)-5);
        break;
        case "Danielle":
            if (sld.cityShore == sld.quest.targetCity)
            {
                sld.quest.targetCity = SelectAnyColony(sld.cityShore);
            }
            Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, sti(arCapBase.checkTime)-5);
        break;
        case "Sharp":
            Map_CreateCoolWarrior("", sld.id, sti(arCapBase.checkTime) - 3);
        break;
	}
	//меняем сроки проверки по Id кэпа в базе нпс-кэпов
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = sti(arCapBase.checkTime);
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//Иниты Остина, убийцы в городах
void BerglarsInit()
{
	ref sld;
	pchar.questTemp.tugs.berglarState = 1; //счетчик
	//============> грабитель в Сент-Джонсе
	pchar.questTemp.tugs.berglarSentJons = "SentJons_TownCave"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarSentJons.hp = 160; //сколько HP
	pchar.questTemp.tugs.berglarSentJons.locator = "basement1"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarSentJons", "Ostins_1", "man", "man", 22, ENGLAND, -1, false));
	sld.name 	= FindPersonalName("BerglarSentJons_name");
	sld.lastname = FindPersonalName("BerglarSentJons_lastname");
	sld.rank = 25;
	sld.city = "SentJons";
	sld.location	= "SentJons_town";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	GiveItem2Character(sld, "pistol2");
	GiveItem2Character(sld, GetGeneratedItem("blade7"));
	TakeNItems(sld, "jewelry1", 30+rand(10));
	TakeNItems(sld, "bullet", 50);
	TakeNItems(sld, "GunPowder", 50);
	sld.money = 10460;
	sld.talker = 7; //начать диалог
	SetSelfSkill(sld, 10, 100, 70, 100, 70);
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	AddLandQuestmark_Main_WithCondition(sld, "BerglarsGang", "Berglars_FirstTime_QuestMarkCondition");
    AddMapQuestMark_Major("SentJons_town", "BerglarsGang", "Berglars_FindOthers_WDMQuestMarkCondition");
    sld.quest.NoTalkerQuestMark = true;
	//=============> грабитель на Мартинике
	pchar.questTemp.tugs.berglarFortFrance = "FortFrance_Dungeon"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarFortFrance.hp = 180; //сколько HP
	pchar.questTemp.tugs.berglarFortFrance.locator = "basement1"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarFortFrance", "Ostins_2", "man", "man", 23, FRANCE, -1, false));
	sld.name 	= FindPersonalName("BerglarFortFrance_name");
	sld.lastname = FindPersonalName("BerglarFortFrances_lastname");
	sld.rank = 25;
	sld.city = "FortFrance";
	sld.location	= "FortFrance_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	GiveItem2Character(sld, "pistol2");
	GiveItem2Character(sld, GetGeneratedItem("blade7"));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	TakeNItems(sld, "jewelry2", 25+rand(10));
	sld.money = 12670;
	sld.talker = 7; //начать диалог
	SetSelfSkill(sld, 10, 100, 70, 50, 60);
	SetCharacterPerk(sld, "BasicDefense");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	AddLandQuestmark_Main_WithCondition(sld, "BerglarsGang", "Berglars_FirstTime_QuestMarkCondition");
	AddMapQuestMark_Major("FortFrance_town", "BerglarsGang", "Berglars_FindOthers_WDMQuestMarkCondition");
	sld.quest.NoTalkerQuestMark = true;
	//============> грабитель в Мариго 
	pchar.questTemp.tugs.berglarMarigo = "Marigo_Cave"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarMarigo.hp = 200; //сколько HP
	pchar.questTemp.tugs.berglarMarigo.locator = "gate_back"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarMarigo", "Ostins_3", "man", "man", 21, HOLLAND, -1, false));
	sld.name = 	FindPersonalName("BerglarMarigo_name");
	sld.lastname = FindPersonalName("BerglarMarigo_lastname");
	sld.rank = 25;
	sld.city = "Marigo";
	sld.location	= "Marigo_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	GiveItem2Character(sld, "pistol2");
	GiveItem2Character(sld, GetGeneratedItem("blade16"));
	TakeNItems(sld, "jewelry3", 25+rand(10));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 15480;
	sld.talker = 7; //начать диалог
	SetSelfSkill(sld, 60, 10, 100, 100, 40);
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	AddLandQuestmark_Main_WithCondition(sld, "BerglarsGang", "Berglars_FirstTime_QuestMarkCondition");
	AddMapQuestMark_Major("Marigo_town", "BerglarsGang", "Berglars_FindOthers_WDMQuestMarkCondition");
	sld.quest.NoTalkerQuestMark = true;
	//============> грабитель в Панаме
	pchar.questTemp.tugs.berglarPanama = "Panama_Cave"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarPanama.hp = 200; //сколько HP
	pchar.questTemp.tugs.berglarPanama.locator = "gate_back"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarPanama", "Ostins_4", "man", "man", 27, SPAIN, -1, false));
	sld.name 	= FindPersonalName("BerglarPanama_name");
	sld.lastname = FindPersonalName("BerglarPanama_lastname");
	sld.rank = 27;
	sld.city = "Panama";
	sld.location	= "Panama_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	GiveItem2Character(sld, "pistol2");
	GiveItem2Character(sld, GetGeneratedItem("blade9"));
	TakeNItems(sld, "jewelry2", 30+rand(5));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 15180;
	sld.talker = 8; //начать диалог
	SetSelfSkill(sld, 100, 10, 50, 50, 70);
	SetCharacterPerk(sld, "AdvancedDefense");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	AddLandQuestmark_Main_WithCondition(sld, "BerglarsGang", "Berglars_FirstTime_QuestMarkCondition");
	AddMapQuestMark_Major("Panama_town", "BerglarsGang", "Berglars_FindOthers_WDMQuestMarkCondition");
	sld.quest.NoTalkerQuestMark = true;
	//============> грабитель в Картахене
	pchar.questTemp.tugs.berglarCartahena = "Cartahena_Cave"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarCartahena.hp = 170; //сколько HP
	pchar.questTemp.tugs.berglarCartahena.locator = "gate_back"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarCartahena", "Ostins_5", "man", "man", 22, SPAIN, -1, false));
	sld.name 	= FindPersonalName("BerglarCartahena_name");
	sld.lastname = FindPersonalName("BerglarCartahena_lastname");
	sld.rank = 22;
	sld.city = "Cartahena";
	sld.location	= "Cartahena_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	GiveItem2Character(sld, "pistol2");
	GiveItem2Character(sld, GetGeneratedItem("blade9"));
	TakeNItems(sld, "jewelry1", 40+rand(10));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 15980;
	sld.talker = 7; //начать диалог
	SetSelfSkill(sld, 100, 10, 70, 100, 50);
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "CriticalHit");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	AddLandQuestmark_Main_WithCondition(sld, "BerglarsGang", "Berglars_FirstTime_QuestMarkCondition");
	AddMapQuestMark_Major("Cartahena_town", "BerglarsGang", "Berglars_FindOthers_WDMQuestMarkCondition");
	sld.quest.NoTalkerQuestMark = true;
	//============> грабитель в Санта Каталине
	pchar.questTemp.tugs.berglarSantaCatalina = "SantaCatalina_Cave"; //указание где забивать стрелу
	pchar.questTemp.tugs.berglarSantaCatalina.hp = 230; //сколько HP
	pchar.questTemp.tugs.berglarSantaCatalina.locator = "gate_back"; //выходной локатор
	sld = GetCharacter(NPC_GenerateCharacter("BerglarSantaCatalina", "Ostins_6", "man", "man", 25, SPAIN, -1, false));
	sld.name 	= FindPersonalName("BerglarSantaCatalina_name");
	sld.lastname = FindPersonalName("BerglarSantaCatalina_lastname");
	sld.rank = 25;
	sld.city = "SantaCatalina";
	sld.location	= "SantaCatalina_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.dialog.filename   = "Quest\Berglars.c";
	sld.greeting = "pirat_quest";
	GiveItem2Character(sld, "pistol2");
	GiveItem2Character(sld, GetGeneratedItem("blade16"));
	TakeNItems(sld, "jewelry3", 25+rand(10));
	TakeNItems(sld, "bullet", 51);
	TakeNItems(sld, "GunPowder", 51);
	sld.money = 16450;
	sld.talker = 7; //начать диалог
	SetSelfSkill(sld, 10, 10, 100, 50, 80);
	SetCharacterPerk(sld, "CriticalHit");
	sld.SuperShooter  = true;
	LAi_SetHP(sld, 1.0, 1.0);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	AddLandQuestmark_Main_WithCondition(sld, "BerglarsGang", "Berglars_FirstTime_QuestMarkCondition");
	AddMapQuestMark_Major("SantaCatalina_town", "BerglarsGang", "Berglars_FindOthers_WDMQuestMarkCondition");
	sld.quest.NoTalkerQuestMark = true;
}

void QuestionsInit() //TODO: Вырезать это говно для горожан, переделав в квесты
{
	ref sld;
	
	//============> база вопросов, специально делаю в коде, не в ини. шоб не ковыряли.
	//		Вопросы горожан.
	
	// KZ > ref квестовых вопрошаек
	int i, j = 73;
	int n = 0;
	string q, a;
	
    NullCharacter.questions = j; //кол-во вопросов (нумерация с нуля, соотв. последней записи структуры !!!)
	
	for (i = 0; i <= j; i++)
	{
		q = "q" + i;
		a = "a" + i;

		n++;
		NullCharacter.questions.(q) = StringFromKey("SeaQuestions_" + n);
		n++;
		NullCharacter.questions.(a) = StringFromKey("SeaQuestions_" + n);
	}
	
	//============> спрашиватель в Тринидаде
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortSpein", "citiz_"+(rand(9)+11), "man", "man", 5, ENGLAND, -1, false));
	sld.rank = 5;
	sld.city = "PortSpein";
	sld.location	= "PortSpein_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortSpein";
	sld.greeting = "cit_common";
	sld.talker = 4; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	SetSelfSkill(sld, 10, 10, 10, 10, 10);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//============> спрашивательница в Виллемстде даёт квест: "Найти пропавшего торговца"
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsVillemstad", "GrunIrma", "woman", "towngirl", 5, HOLLAND, -1, false));
	sld.name = FindPersonalName("QuetionsVillemstad_name");
	sld.lastname = FindPersonalName("QuetionsVillemstad_lastname");
	sld.rank = 5;
	sld.city = "Villemstad";
	sld.location	= "Villemstad_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Villemstad";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 3; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	AddLandQuestMark_Main(sld, "SCQ_Hasband_Truba");
	AddMapQuestMark_Major("Villemstad_town", "SCQ_Hasband_Truba", "");
	//============> спрашивательница в Порт-о-Принсе даёт квест: "Вызволение из плена мужа горожанки"
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortPax", "LabbeLiliana", "woman", "towngirl", 5, FRANCE, -1, false));
	sld.name = FindPersonalName("QuetionsPortPax_name");
	sld.lastname = FindPersonalName("QuetionsPortPax_lastname");
	sld.rank = 5;
	sld.city = "PortPax";
	sld.location	= "PortPax_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortPax";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 3; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	AddLandQuestMark_Main(sld, "SCQ_PirateFashion");
	AddMapQuestMark_Major("PortPax_town", "SCQ_PirateFashion", "");
	//============> спрашиватель в Сан-Хуане
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsSanJuan", "citiz_"+(rand(9)+11), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "SanJuan";
	sld.location	= "SanJuan_town";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "SanJuan";
	sld.greeting = "cit_common";
	sld.talker = 6; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> спрашиватель в Кумане
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsCumana", "citiz_"+(rand(9)+11), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "Cumana";
	sld.location	= "Cumana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Cumana";
	sld.greeting = "cit_common";
	sld.talker = 6; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	//============> спрашиватель в Порт-Ройал
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortRoyal", "women_"+(rand(11)+1), "woman", "towngirl", 5, ENGLAND, -1, false));
	sld.rank = 5;
	sld.city = "PortRoyal";
	sld.location	= "PortRoyal_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "PortRoyal";
	sld.greeting = "Gr_Woman_Citizen";
	sld.talker = 3; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	//============> спрашиватель в Сантьяго
	sld = GetCharacter(NPC_GenerateCharacter("QuetionsSantiago", "citiz_"+(rand(9)+11), "man", "man", 5, SPAIN, -1, false));
	sld.rank = 5;
	sld.city = "Santiago";
	sld.location	= "Santiago_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.dialog.filename   = "Quest\Questions.c";
	sld.dialog.currentnode   = "Santiago";
	sld.greeting = "cit_common";
	sld.talker = 5; //начать диалог
	sld.quest.numQuestion = SelectQuestions(); //номер вопроса
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");

}
// ==> обработка базы вопросов, относится к методу выше
int SelectQuestions()
{
	bool bOk = true;
	int iTemp;
	string sTemp;
	while (bOk)
	{
		iTemp = rand(sti(NullCharacter.questions));
		sTemp = "m" + iTemp;
		if (!CheckAttribute(&NullCharacter, "questions" + sTemp))
		{
			NullCharacter.questions.(sTemp) = true;
			break;
		}
	}
	return iTemp;
}
// -- нищие --
void PoormansInit()
{
	ref sld;
	//нищий в Сент-Джонсе
	sld = GetCharacter(NPC_GenerateCharacter("SentJons_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "SentJons";	
	sld.location	= "SentJons_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto15";
	sld.forSit.locator1 = "goto17"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	//нищий в Бриджтауне
	sld = GetCharacter(NPC_GenerateCharacter("Bridgetown_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "Bridgetown";
	sld.location	= "Bridgetown_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto19"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto4";
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	//нищий в Белизе
	sld = GetCharacter(NPC_GenerateCharacter("Beliz_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Beliz";
	sld.location	= "Beliz_town";
	sld.location.group = "goto";
	sld.location.locator = "goto9";
	sld.forStay.locator = "goto9"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto7";
	sld.forSit.locator1 = "goto19"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	//нищий в Каракасе
	sld = GetCharacter(NPC_GenerateCharacter("Caracas_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Caracas";
	sld.location	= "Caracas_town";
	sld.location.group = "goto";
	sld.location.locator = "goto20";
	sld.forStay.locator = "goto20"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto21"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto23";
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	//нищий в Картахене
	sld = GetCharacter(NPC_GenerateCharacter("Cartahena_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Cartahena";
	sld.location	= "Cartahena_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto18";
	sld.forSit.locator1 = "goto14"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto6";
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	//нищий в Кумане
	sld = GetCharacter(NPC_GenerateCharacter("Cumana_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Cumana";
	sld.location	= "Cumana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto13";
	sld.forSit.locator1 = "goto15"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	//нищий в Кюрасао
	/*sld = GetCharacter(NPC_GenerateCharacter("Villemstad_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, HOLLAND, -1, false));
	sld.city = "Villemstad";
	sld.location	= "Villemstad_town";
	sld.location.group = "goto";
	sld.location.locator = "goto24";
	sld.forStay.locator = "goto24"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto23";
	sld.forSit.locator1 = "goto7"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto8";
	LAi_SetLoginTime(sld, 9.0, 22.0);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");*/
	
	//нищий в Бас-Тере, Гваделупа
	sld = GetCharacter(NPC_GenerateCharacter("BasTer_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "BasTer";
	sld.location	= "BasTer_town";
	sld.location.group = "goto";
	sld.location.locator = "goto18";
	sld.forStay.locator = "goto18"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto24";
	sld.forSit.locator1 = "goto16"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto17";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	//нищий в Гаване
	sld = GetCharacter(NPC_GenerateCharacter("Havana_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Havana";
	sld.location	= "Havana_town";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	sld.forStay.locator = "goto12"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto22"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto23";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	//нищий в Порт-Ройал
	sld = GetCharacter(NPC_GenerateCharacter("PortRoyal_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "PortRoyal";
	sld.location	= "PortRoyal_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto28"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto7";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	//нищий в Фор-де-Франсе, Мартиника
	sld = GetCharacter(NPC_GenerateCharacter("FortFrance_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "FortFrance";
	sld.location	= "FortFrance_town";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	sld.forStay.locator = "goto4"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto14";
	sld.forSit.locator1 = "goto10"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	//нищий на Невисе
	sld = GetCharacter(NPC_GenerateCharacter("Charles_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "Charles";
	sld.location	= "Charles_town";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
	sld.forStay.locator = "goto5"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto19";
	sld.forSit.locator1 = "goto13"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto3";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	//нищий в Портобело
	sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "PortoBello";
	sld.location	= "PortoBello_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15";
	sld.forStay.locator = "goto15"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto25"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto12";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	//нищий в Порт-о-Принс, Эспаньола
	sld = GetCharacter(NPC_GenerateCharacter("PortPax_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "PortPax";
	sld.location	= "PortPax_town";
	sld.location.group = "goto";
	sld.location.locator = "goto14";
	sld.forStay.locator = "goto14"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto25";
	sld.forSit.locator1 = "goto13"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto11";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	//нищий в Сантьяго
	sld = GetCharacter(NPC_GenerateCharacter("Santiago_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, SPAIN, -1, false));
	sld.city = "Santiago";
	sld.location	= "Santiago_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto3";
	sld.forSit.locator1 = "goto15"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto28";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	//нищий в Мариго, Сан Мартин
	sld = GetCharacter(NPC_GenerateCharacter("Marigo_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, HOLLAND, -1, false));
	sld.city = "Marigo";
	sld.location	= "Marigo_town";
	sld.location.group = "goto";
	sld.location.locator = "goto16";
	sld.forStay.locator = "goto16"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto1";
	sld.forSit.locator1 = "goto4"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto9";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	
	//нищий в Тортуге
	sld = GetCharacter(NPC_GenerateCharacter("Tortuga_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, FRANCE, -1, false));
	sld.city = "Tortuga";
	sld.location	= "Tortuga_town";
	sld.location.group = "goto";
	sld.location.locator = "goto23";
	sld.forStay.locator = "goto23"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto16";
	sld.forSit.locator1 = "goto18"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	
	//нищий в Порт Спейне, Тринидад
	sld = GetCharacter(NPC_GenerateCharacter("PortSpein_Poorman", "panhandler_"+(rand(5)+1), "man", "man", 5, ENGLAND, -1, false));
	sld.city = "PortSpein";
	sld.location	= "PortSpein_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.forStay.locator = "goto6"; //где генеримся в случае стояния
	sld.forSit.locator0 = "goto9";
	sld.forSit.locator1 = "goto14"; //три локатора, где генеримся в случае сидения
	sld.forSit.locator2 = "goto1";
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Common_Poorman.c";
	LAi_SetPoorType(sld);
	LAi_SetHP(sld, 50.0, 50.0);
	sld.greeting = "Gr_poorman";
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	
	//заказчик нищих
	sld = GetCharacter(NPC_GenerateCharacter("PoorKillSponsor", "Oliver_Trusts", "man", "man", 30, PIRATE, -1, false));
	sld.name = FindPersonalName("PoorKillSponsor_name");
	sld.lastname = FindPersonalName("PoorKillSponsor_lastname");
	sld.talker = 8; //начать диалог
	LAi_SetLoginTime(sld, 9.0, 21.99);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "Begin_PoorKill";
	sld.greeting = "Gr_OliverTrast";
	LAi_SetCitizenType(sld);
	LAi_SetImmortal(sld, true);
	LAi_SetHP(sld, 100.0, 100.0);
	AddLandQuestMark_Main(sld, "ISS_PoorsMurder");

	//несчастный мушкетёр - Хэмфри Дуглас - Улучшил его. Konstrush
	sld = GetCharacter(NPC_GenerateCharacter("Douglas", "Humphrey_Douglas", "man", "man", 15, ENGLAND, -1, false));
	sld.name = FindPersonalName("OffMushketer_name");
	sld.lastname = FindPersonalName("OffMushketer_lastname");
	sld.location = "PortSpein_houseH3";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "OffMushketer";
	SetSelfSkill(sld, 61, 10, 2, 70, 50);
	SetShipSkill(sld, 5, 5, 2, 10, 5, 20, 10, 10, 70);
	SetSPECIAL(sld, 7, 5, 9, 3, 8, 9, 10); // улучшены пиратес 
	LAi_SetSitType(sld);
	sld.greeting = "cit_common";
    sld.MushForever = ""; // Использовать только мушкет
	LAi_SetHP(sld, 270.0, 270.0); // Задано НР.
	SetCharacterPerk(sld, "HPPlus");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "Ciras");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Medic");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunAdvanced");
	SetCharacterPerk(sld, "MusketsTraining");
	SetCharacterPerk(sld, "GunProfessional");
	//черты
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "LoyalOff");
	SetCharacterPerk(sld, "MusketeerOnly");
	SetCharacterPerk(sld, "DuglasSchool");
	SetCharacterPerk(sld, "WeaponBonding");

	DeleteAttribute(sld, "Items");
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	sld.HoldEquip = true; // не отдавать оружие (для мушкетёров)
	AddLandQuestMark_Main(sld, "SeekDoubleMushket");
	AddMapQuestMark_Major("PortSpein_town", "SeekDoubleMushket", "SeekDoubleMushket_Begin_WDMQuestMarkCondition");
}

//=============== капитан Шарп ====================
string Sharp_choiceAction()
{
	string sBack;
	ref sld;
	//удалим Шарпа с карты, если он плывет ещё где-то
	Map_ReleaseQuestEncounter("Sharp");
	group_DeleteGroup("Sharp_Group");
	if (rand(3) != 2 && sti(pchar.questTemp.Sharp.count) < 5)
	{	//ещё динамим, отправляем ГГ в другой город
		string sCity = pchar.questTemp.Sharp.City; //предыдущая цель, запомним для СЖ
		pchar.questTemp.Sharp.City.rumour = true; //флаг дать слух в городе
		pchar.questTemp.Sharp.City = GetSharpCity(); //новый город 
		sBack = GetSharpRumour_toCityTarget();
		pchar.questTemp.Sharp.count = sti(pchar.questTemp.Sharp.count) + 1; //счетчик
		AddQuestRecord("SharpPearl", "2");
		AddQuestUserData("SharpPearl", "sOldTarget", XI_ConvertString("Colony" + sCity + "Pre"));
		AddQuestUserData("SharpPearl", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc"));
		if (GetIslandNameByCity(pchar.questTemp.Sharp.City) != pchar.questTemp.Sharp.City)
		{
			AddQuestUserData("SharpPearl", "sAreal", StringFromKey("InfoMessages_6", XI_ConvertString(GetIslandNameByCity(pchar.questTemp.Sharp.City) + "Pre")));
		}

        if (pchar.questTemp.Sharp.SeekSpy == "begin") // если ищем в первый раз ставим мэйн-метки
        {
            AddLandQuestmarkToFantoms_Main("Citizen", "SharpPearl", "SharpPearl_SeekSharp_Citizen_QuestMarkCondition");
            AddLandQuestmarkToFantoms_Main("Commoner", "SharpPearl", "SharpPearl_SeekSharp_Citizen_QuestMarkCondition");
        }

		//запускаем опять Шарпа на карту
		sld = characterFromId("Sharp");
		sld.DontRansackCaptain = true; //fix
		string sGroup = "Sharp_Group";
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		sld.mapEnc.type = "trade";
		sld.mapEnc.worldMapShip = "quest_ship";
		sld.mapEnc.Name = FindPersonalName("Sharp_mapEnc");
		string sColony= SelectAnyColony(sCity); //колония, откуда плывет Шарп
		int daysQty = GetMaxDaysFromColony2Colony(sColony, pchar.questTemp.Sharp.City)+3; //дней доехать даем с запасом
		Map_CreateTrader(sColony, pchar.questTemp.Sharp.City, sld.id, daysQty);
	}
	else
	{
		if (rand(5) < 4 || pchar.questTemp.Sharp.SeekSpy == "begin") // если ещё не ходили с Шарпом на промысел, то в город не генерим
		{
			sBack = GetSharpRumour_inIsland();
			pchar.questTemp.Sharp.Island = GetArealByLocation(loadedLocation);
			pchar.questTemp.Sharp.count = 0; //счетчик нулим для след. раза
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
			pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
			Pchar.quest.Sharp_loginNearIsland.win_condition.l1 = "location";
			Pchar.quest.Sharp_loginNearIsland.win_condition.l1.location = pchar.questTemp.Sharp.Island;
			Pchar.quest.Sharp_loginNearIsland.function = "Sharp_loginNearIsland";
			AddQuestRecord("SharpPearl", "3");
			SaveCurrentQuestDateParam("questTemp.Sharp");
			Log_QuestInfo("Сработало на остров.");
		}
		else
		{
			sBack = GetSharpRumour_inCity();
			pchar.questTemp.Sharp.count = 0; //счетчик нулим для след. раза
			pchar.questTemp.Sharp.price = 5000+rand(20)*1000; //цена за наводку
			pchar.questTemp.Sharp.price.evil = rand(1); //добрый или злой, для скидки
			float locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			sld = &characters[GetCharacterIndex("Sharp")];
			sld.dialog.currentnode = "CitySharp";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			ChangeCharacterAddressGroup(sld, pchar.location, "patrol", LAi_FindFarLocator("patrol", locx, locy, locz));
			AddQuestRecord("SharpPearl", "11");
			Log_QuestInfo("Сработало на город.");
		}
	}
	return sBack;
}

//ищем новый город 
string GetSharpCity()
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	if (GetBaseHeroNation() != PIRATE)
	{
		for(n=0; n<MAX_COLONIES; n++)
		{	//не на свой остров-ареал
			if (colonies[n].nation != "none" && GetRelation2BaseNation(sti(colonies[n].nation)) != RELATION_ENEMY && GetArealByLocation(loadedLocation) != GetArealByCityName(colonies[n].id) && colonies[n].id != "Panama")
			{	//GetCharacterCurrentIslandId(pchar) != GetIslandNameByCity(colonies[n].id)
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	else
	{
		for(n=0; n<MAX_COLONIES; n++)
		{
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetArealByLocation(loadedLocation) != GetArealByCityName(colonies[n].id) && colonies[n].id != "Panama")
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	iRes = storeArray[rand(howStore-1)];
	return colonies[iRes].id;
}
//фразы по умолчанию
string GetSharpRumour_default()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = StringFromKey("LSC_Q2Utilite_1"); break;
        case 1: sRumour = StringFromKey("LSC_Q2Utilite_2"); break;
        case 2:	sRumour = StringFromKey("LSC_Q2Utilite_3"); break;
    }
	return sRumour;
}
//фразы в другой город
string GetSharpRumour_toCityTarget()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = StringFromKey("LSC_Q2Utilite_4", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc")); break;
        case 1: sRumour = StringFromKey("LSC_Q2Utilite_5", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc")); break;
        case 2:	sRumour = StringFromKey("LSC_Q2Utilite_6", XI_ConvertString("Colony" + pchar.questTemp.Sharp.City + "Acc")); break;
    }
	return sRumour;
}
//фразы у осрова
string GetSharpRumour_inIsland()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = StringFromKey("LSC_Q2Utilite_7"); break;
        case 1: sRumour = StringFromKey("LSC_Q2Utilite_8"); break;
        case 2:	sRumour = StringFromKey("LSC_Q2Utilite_9"); break;
    }
	return sRumour;
}
//фразы в городе
string GetSharpRumour_inCity()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = StringFromKey("LSC_Q2Utilite_10"); break;
        case 1: sRumour = StringFromKey("LSC_Q2Utilite_11"); break;
        case 2:	sRumour = StringFromKey("LSC_Q2Utilite_12"); break;
    }
	return sRumour;
}

//=============== шебека Синяя Птица.  ====================
string BlueBurd_setTradeShip()
{
	pchar.questTemp.BlueBird.Island = GetArealByLocation(loadedLocation);
	Pchar.quest.BlueBird_loginFleut.win_condition.l1 = "location";
	Pchar.quest.BlueBird_loginFleut.win_condition.l1.location = pchar.questTemp.BlueBird.Island;
	Pchar.quest.BlueBird_loginFleut.function = "BlueBird_loginFleut";
	pchar.questTemp.BlueBird.nation = colonies[FindColony(pchar.questTemp.BlueBird.City)].nation; //нация колонии, откуда кораблик
	aref aName;
	makearef(aName, pchar.questTemp.BlueBird);
	SetRandomNameToShip(aName);
	AddQuestRecord("Xebeca_BlueBird", "10");
	AddQuestUserData("Xebeca_BlueBird", "sCity", XI_ConvertString("Colony" + pchar.questTemp.BlueBird.City + "Pre"));
	AddQuestUserData("Xebeca_BlueBird", "sShipName", "'" + aName.Ship.Name + "'");
	AddQuestUserData("Xebeca_BlueBird", "sCity_2", XI_ConvertString("Colony" + pchar.questTemp.BlueBird.City + "Gen"));
	AddQuestUserData("Xebeca_BlueBird", "sTradeName", GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")));
	AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
	SaveCurrentQuestDateParam("questTemp.BlueBird");
	return GetBlueBirdRumour_Ship(); //текст слуха
}
//фразы по слухам, наводки на корабли тоговцев
string GetBlueBirdRumour_Ship()
{
	string sRumour;
	switch (rand(2))
    {
        case 0: sRumour = StringFromKey("LSC_Q2Utilite_13", GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")), pchar.questTemp.BlueBird.Ship.Name); break;
		case 1: sRumour = StringFromKey("LSC_Q2Utilite_14", GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")), pchar.questTemp.BlueBird.Ship.Name); break;
        case 2:	sRumour = StringFromKey("LSC_Q2Utilite_15", GetFullName(characterFromId(pchar.questTemp.BlueBird.City + "_trader")), pchar.questTemp.BlueBird.Ship.Name); break;
    }
	return sRumour;
}
//======================= пиратская линейка ===================================
void PiratesLineInit()
{
	ref sld;
	pchar.questTemp.piratesLine = "begin";
	sld = GetCharacter(NPC_GenerateCharacter("QuestPirate1", "Goodley", "man", "man", 20, PIRATE, -1, true));
	sld.name = FindPersonalName("QuestPirate1_name");
	sld.lastname = FindPersonalName("QuestPirate1_lastname");
	sld.rank = 20;
	sld.city = "PuertoPrincipe";
	sld.location	= "PuertoPrincipe_town";
	sld.location.group = "goto";
	sld.location.locator = "goto7";
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PiratesMan1";
	sld.greeting = "Gr_EvilPirate";
	sld.talker = 8; //начать диалог
	sld.NoCheckFightMode = ""; //для CitizenType
	sld.TiedItems.itm1.model = "HandsItems\meet";
	sld.TiedItems.itm1.locator = "Saber_hand";	
	sld.TiedItems.itm2.model = "HandsItems\cup";
	sld.TiedItems.itm2.locator = "Saber_hand";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");

	AddLandQuestmark_Main_WithCondition(sld, "Pir_Line", "PirLine_Begin_QuestPirate1_QuestMarkCondition");
	AddLandQuestmark_Main(CharacterFromID("Jackman"), "Pir_Line");

	AddMapQuestMark_Major("PuertoPrincipe_town", "Pir_Line", "PirLine_Begin_WDMQuestMarkCondition");
    AddMapQuestMark_Major("Pirates_town", "Pir_Line", "PirLine_Begin_WDMQuestMarkCondition");
}

//ищем город определённой нации, проверять наличие ростовщика и тавернщика
string GetQuestNationsCity(int _nation)
{
	int n, iRes;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{	//не на свой остров-ареал
		if (colonies[n].nation != "none"  && colonies[n].id != "Panama" && sti(colonies[n].nation) == _nation && GetArealByLocation(loadedLocation) != GetArealByCityName(colonies[n].id))
		{	//GetCharacterCurrentIslandId(pchar) != GetIslandNameByCity(colonies[n].id)
			if (GetCharacterIndex(colonies[n].id + "_tavernkeeper") > 0 && GetCharacterIndex(colonies[n].id + "_usurer") > 0)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore < 1) return GetColonyStartOwner(_nation, "tavernkeeper,usurer", 2);
	iRes = storeArray[idRand("GetQuestNationsCity_" + _nation, howStore-1)];
	return colonies[iRes].id;
}

// KZ > выбираем колонию по нации, основываясь на стартовых данных игры, а не на текущем положении дел (игрок может захватить все колонии нужной нации и засофтлочить себе квесты)
string GetColonyStartOwner(int _nation, string sNPC, int iRandType)
{
	Restrictor(&_nation, 0, 4);
	Restrictor(&iRandType, 0, 2);

	sNPC = stripblank(sNPC);
	int i, q, n, iRes, iNPC = KZ|Symbol(sNPC, ",");
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for (n = 0; n < MAX_COLONIES; n++)
	{
		if (colonies[n].smuggling_nation != "none" && colonies[n].id != "Panama" && sti(colonies[n].smuggling_nation) == _nation && GetArealByLocation(loadedLocation) != GetArealByCityName(colonies[n].id))
		{
			if (sNPC != "") // > если необходимо наличие конкретного NPC-статика (несколько указывать через запятую)
			{
				q = -1;

				for (i = 0; i <= iNPC; i++)
				{
					// NPC-статики: Mayor, Priest, tavernkeeper, waitress, trader, shipyarder, usurer, PortMan, Hostess, Smuggler, GlavSklad, bankvault, Lightman, Cemeteryman
					if (GetCharacterIndex(colonies[n].id + "_" + GetSubStr(sNPC, ",", i)) > 0)
						q++;
					else
						q--;
				}

				if (q >= iNPC)
				{
					storeArray[howStore] = n;
					howStore++;
				}
			}
			else
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}

	if (howStore < 1) return SelectColonyExt(pchar, "B", "5", 0, "Panama", iRandType, "");

	switch (iRandType)
	{
		case 0: iRes = storeArray[rand(howStore - 1)]; break;
		case 1: iRes = storeArray[dRand(howStore - 1)]; break;
		case 2: iRes = storeArray[idRand("GetColonyStartOwner" + _nation, howStore - 1)]; break;
	}

	return colonies[iRes].id;
}

// KZ > выбираем случайную колонию, подходящую по критериям
string SelectColonyExt(ref rChar, string sColonyType, string sNations, int iRelationType, string sExcludeColony, int iRandType, string sTag)
{
//	rChar							> от кого чекать отношения
//	sColonyType		"A" (All) 			> все обитаемые колонии и необитайки;
//					"I" (Island) 		> только обитаемые колонии на островах;
//					"M" (Mein) 			> только обитаемые колонии на материке;
//					"B" (Both) 			> все стандартные обитаемые колонии на островах и на материке;
//					"U" (Uninhabited) 	> только необитайки (Доминика, Кайман, Теркс);
//					"S" (Special) 		> только спецколонии (ГПК, Тено, Промыслы);
//					"" 					> вообще все колонии из Colonies_init.c
//	sNations						> колонии каких наций задействовать: "0" - Англия, "1" - Франция, "2" - Испания, "3" - Голландия, "4" - пираты, "5" - все, кроме пиратов, "" - все нации
//	iRelationType					> 1 - только дружественные и нейтральные к rChar колонии, 2 - только вражеские, 0 - любые
//	sExcludeColony					> список колоний, исключённых из выборки
//	iRandType						> тип рандома: 0 - rand, 1 - drand, 2 - idRand
//	sTag							> тэг для idRand

	Restrictor(&iRandType, 0, 2);
	Restrictor(&iRelationType, 0, 2);
	int storeArray[MAX_COLONIES]; // > склад колоний по критериям
	int defArray[MAX_COLONIES]; // > все подходящие колонии, на случай, если в storeArray ничего не подберётся
	int howStore = 0;
	int defStore = 0;
	int i, j, n, iRel = RELATION_UNKNOWN;
	string tmp = "";
	ref rColony;

	if (sColonyType != "" && !StrHasStr(sColonyType, "A,I,M,B,U,S", 1))
		sColonyType = "B";

	if (sNations != "" && !StrHasStr(sNations, "0,1,2,3,4,5", 1))
		sNations = "5";

	if (iRandType == 2 && sTag == "")
		sTag = "SelectColonyEx" + rChar.id + sColonyType;

	for (i = 0; i < MAX_COLONIES; i++)
	{
		rColony = &Colonies[i];

		if (sColonyType != "")
		{
			if (rColony.nation == "none")
			{
				if (!CheckAttribute(rColony, "type")) continue;
				if (rColony.type == "uninhabited" && sColonyType != "A" && sColonyType != "U") continue;
				if (rColony.type == "special" && sColonyType != "S") continue;
			}

			if (sColonyType == "M" && rColony.islandLable != "Mein") continue;
			if (sColonyType == "I" && rColony.islandLable == "Mein") continue;
		}

		defArray[defStore] = i;
		defStore++;

		if (sNations != "")
		{
			if (sNations == "5" && rColony.nation == PIRATE) continue;
			if (sNations != "5" && sti(rColony.nation) != sti(sNations)) continue;
		}

		if (iRelationType > 0)
		{
			iRel = GetNationRelation(sti(rChar.nation), sti(rColony.nation));
			if (iRelationType == 1 && iRel == RELATION_ENEMY) continue;
			if (iRelationType == 2 && iRel != RELATION_ENEMY) continue;
		}

		storeArray[howStore] = i;
		howStore++;
	}

	if (sExcludeColony != "")
	{
		n = KZ|Symbol(sExcludeColony, ",");
		for (j = 0; j <= n; j++)
		{
			tmp = GetSubStr(sExcludeColony, ",", j);
			i = FindColony(tmp);
			if (ArrayIsEqualValue(&storeArray, i))
			{
				ArrayRemoveValue(&storeArray, i);
				howStore--;
			}
		}
	}

	if (howStore < 1)
	{
		howStore = defStore;
		ArrayClear(&storeArray);
		ArrayAddAll(&storeArray, &defArray);
	}

	switch (iRandType)
	{
		case 0: i = storeArray[rand(howStore - 1)]; break;
		case 1: i = storeArray[dRand(howStore - 1)]; break;
		case 2: i = storeArray[idRand(sTag, howStore - 1)]; break;
	}

	return Colonies[i].id;
}

//ищем не вражескую колонию, куда можно доплыть
string SelectNotEnemyColony(ref NPChar)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandNameByCity(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}

//ищем любую национальную колонию, куда можно доплыть
string SelectAnyColony(string _City)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandNameByCity(_City) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}

string SelectAnyColony2(string _City1, string _City2)
{
	int n, nation;
    int storeArray[MAX_COLONIES];
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].id != "Panama" && colonies[n].id != "FortOrange" && colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetIslandNameByCity(_City1) != colonies[n].islandLable && GetIslandNameByCity(_City2) != colonies[n].islandLable) //не на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[idRand("SelectAnyColony2" + _City1 + _City2, howStore-1)];
	return colonies[nation].id;
}

ref CheckLSCCitizen()
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[3]);
	if (sSeeked == StringFromKey("LSC_Q2Utilite_74") || sSeeked == StringFromKey("LSC_Q2Utilite_75"))
	{
		return CharacterFromId("LSCMayor");
	}
	if (sSeeked == StringFromKey("LSC_Q2Utilite_76") || sSeeked == StringFromKey("LSC_Q2Utilite_77") || sSeeked == StringFromKey("LSC_Q2Utilite_78") || sSeeked == StringFromKey("LSC_Q2Utilite_79") || sSeeked == StringFromKey("LSC_Q2Utilite_80") || sSeeked == StringFromKey("LSC_Q2Utilite_81"))
	{
		return CharacterFromId("LSCBarmen");
	}
	if (sSeeked == StringFromKey("LSC_Q2Utilite_82") || sSeeked == StringFromKey("LSC_Q2Utilite_83"))
	{
		return CharacterFromId("LSCwaitress");
	}
	if (sSeeked == StringFromKey("LSC_Q2Utilite_84") || sSeeked == StringFromKey("LSC_Q2Utilite_85"))
	{
		rCharacter = CharacterFromId("Mechanic");
		if (CheckAttribute(rCharacter, "quest.money"))
			return rCharacter;
		else
			return &NullCharacter;
	}
	for(int n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "city") && rCharacter.city == "LostShipsCity")
		{
			sTemp = GetStrSmallRegister(rCharacter.name + " " + rCharacter.lastname);
			if (HasSubStr(sSeeked, sTemp))
			{
				return rCharacter;			
			}
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (HasSubStr(sSeeked, sTemp))
			{
				return rCharacter;			
			}
			else
			{
				sTemp = GetStrSmallRegister(rCharacter.name);
				if (HasSubStr(sSeeked, sTemp))
				{
					return rCharacter;			
				}
			}
		}
	}
	return &NullCharacter;
}

void SeekLSCCitizen_ChineseWrapper(ref Npchar, aref Link)
{
	if (LanguageGetLanguage() != "chinese")
	{
		return;
	}

	Link.l2 = StringFromKey("LSC_Q2Utilite_74");
	Link.l2.go = "SeekLSCCitizenCN_" + Link.l2;
	Link.l3 = StringFromKey("LSC_Q2Utilite_76");
	Link.l3.go = "SeekLSCCitizenCN_" + Link.l3;
	Link.l4 = StringFromKey("LSC_Q2Utilite_82");
	Link.l4.go = "SeekLSCCitizenCN_" + Link.l4;

	int iTemp = GetCharacterIndex("Mechanic");
	if (iTemp != -1 && Characters[iTemp].Dialog.currentnode != "First time")
	{
		Link.l5 = StringFromKey("LSC_Q2Utilite_85");
		Link.l5.go = "SeekLSCCitizenCN_" + Link.l5;
	}
}

string WhereLSCCitizen(ref rCharacter)
{
	string sShip = "none";
	string sTemp;
	if (rCharacter.location	== "LostShipsCity_town")
	{
		sTemp = rCharacter.location.locator;
		if (rCharacter.location.locator == "fawn") sTemp = "17";
		else sTemp = strcut(sTemp, 4, 5);
		switch (sTemp)
		{
			case "01": sShip = StringFromKey("LSC_Q2Utilite_16"); break;
			case "02": sShip = StringFromKey("LSC_Q2Utilite_17"); break;
			case "03": sShip = StringFromKey("LSC_Q2Utilite_18"); break;
			case "04": sShip = StringFromKey("LSC_Q2Utilite_19"); break;
			case "05": sShip = StringFromKey("LSC_Q2Utilite_20"); break;
			case "06": sShip = StringFromKey("LSC_Q2Utilite_21"); break;
			case "07": sShip = StringFromKey("LSC_Q2Utilite_22"); break;
			case "08": sShip = StringFromKey("LSC_Q2Utilite_23"); break;
			case "09": sShip = StringFromKey("LSC_Q2Utilite_24"); break;
			case "10": sShip = StringFromKey("LSC_Q2Utilite_25"); break;
			case "11": sShip = StringFromKey("LSC_Q2Utilite_26"); break;
			case "12": sShip = StringFromKey("LSC_Q2Utilite_27"); break;
			case "13": sShip = StringFromKey("LSC_Q2Utilite_28"); break;
			case "14": sShip = StringFromKey("LSC_Q2Utilite_29"); break;
			case "15": sShip = StringFromKey("LSC_Q2Utilite_30"); break;
			case "16": sShip = StringFromKey("LSC_Q2Utilite_31"); break;
			case "17": sShip = StringFromKey("LSC_Q2Utilite_32"); break;
		}
	}
	else
	{
		switch (rCharacter.location)
		{
			case "AvaShipInside3": sShip = StringFromKey("LSC_Q2Utilite_33");              break;
			case "CarolineBank": sShip = StringFromKey("LSC_Q2Utilite_34");                break;
			case "CeresSmithy": sShip = StringFromKey("LSC_Q2Utilite_35");                 break;
			case "EsmeraldaStoreBig": sShip = StringFromKey("LSC_Q2Utilite_36");           break;
			case "FenixPlatform": sShip = StringFromKey("LSC_Q2Utilite_37");               break;
			case "FernandaDiffIndoor": sShip = StringFromKey("LSC_Q2Utilite_38");          break;
			case "FleuronTavern": sShip = StringFromKey("LSC_Q2Utilite_39");               break;
			case "FurieShipInside2": sShip = StringFromKey("LSC_Q2Utilite_40");            break;
			case "GloriaChurch": sShip = StringFromKey("LSC_Q2Utilite_41");                break;
			case "PlutoStoreSmall": sShip = StringFromKey("LSC_Q2Utilite_42");             break;
			case "ProtectorFisher": sShip = StringFromKey("LSC_Q2Utilite_43");             break;
			case "SanAugustineResidence": sShip = StringFromKey("LSC_Q2Utilite_44");       break;
			case "SanGabrielMechanic": sShip = StringFromKey("LSC_Q2Utilite_45");          break;
			case "SantaFlorentinaShipInside4": sShip = StringFromKey("LSC_Q2Utilite_46");  break;
			case "TartarusPrison": sShip = StringFromKey("LSC_Q2Utilite_47");              break;
			case "VelascoShipInside1": sShip = StringFromKey("LSC_Q2Utilite_48");          break;
		}
	}
	return sShip;
}

//отдать забытый судовой журнал. помещаем в город кэпа, который приплыл к назначенной колонии
void SetCapitainFromSeaToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //флаг в городе
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	sld.location	= sld.City + "_PortOffice";
	sld.location.group = "goto";
	sld.location.locator = "goto"+(rand(2)+1);
	LAi_SetCitizenType(sld);

	/*int iColony = FindColony(sld.City);
	string sGroup = "PorpmansShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);			
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);*/

	//таймер через сколько опять выйти в море
	int Qty = rand(4)+3;
	string name = "Timer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetCapitainFromCityToSea";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//даем слух, что кэп в городе
	 AddSimpleRumourCity(
		StringFromKey("LSC_Q2Utilite_52", LinkRandPhrase(
	StringFromKey("LSC_Q2Utilite_49", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, GetFullName(sld)),
	StringFromKey("LSC_Q2Utilite_50", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name),
	StringFromKey("LSC_Q2Utilite_51", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, GetFullName(sld)))),sld.City,Qty,1,"none");
}
//отдать забытый судовой журнал. записть в квестбук из слухов
void PortmansBook_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString);
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;	
		string sTitle = characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")].id + "PortmansBook_Delivery";
		AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandNameByCity(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", StringFromKey("InfoMessages_6", XI_ConvertString(GetIslandNameByCity(sld.quest.targetCity) + "Pre")));
		}
	}
}

//разыскать кэпа-вора. помещаем в город кэпа, который приплыл к назначенной колонии
void SetRobberFromMapToSea(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InPort"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; //нацию дадим, что и у города

	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);			
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
	Group_SetTaskNone(sGroup);

	//таймер через сколько опять выйти на карту
	int Qty = rand(5)+4;
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetRobberFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	//даем слух, что кэп на рейде
	 AddSimpleRumourCity(
		StringFromKey("LSC_Q2Utilite_56", LinkRandPhrase(
	StringFromKey("LSC_Q2Utilite_53", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, GetFullName(sld)),
	StringFromKey("LSC_Q2Utilite_54", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name),
	StringFromKey("LSC_Q2Utilite_55", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, GetFullName(sld)))),sld.City,Qty,1,"none");
}
//разыскать кэпа-вора. запись в квестбук из слухов
void PortmansSeekShip_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString);
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;	
		ref npchar = &characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")];
		string sTitle = npchar.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTitle, "Portmans_SeekShip", "3");
		AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName)));
		AddQuestUserData(sTitle, "sShipName", sld.Ship.name);
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		iTemp = RealShips[sti(sld.Ship.Type)].basetype;
		AddQuestUserData(sTitle, "sSexWord", GetShipSexWord(ShipsTypes[iTemp].name, "ушёл", "ушла"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandNameByCity(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", StringFromKey("InfoMessages_6", XI_ConvertString(GetIslandNameByCity(sld.quest.targetCity) + "Pre")));
		}
	}
}

//розыск кэпов горожанами
void CitizCapFromMapToCity(string sChar)
{
	ref sld = &characters[GetCharacterIndex(sChar)];
	sld.quest = "InCity"; //флаг кэпа ходит по городу
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);
	sld.nation = colonies[iColony].nation; //нацию дадим, что и у города
	if (rand(1))
	{	//ходит в городе
		sld.location	= sld.City + "_town";
		sld.location.group = "goto";
		sld.location.locator = "goto"+(rand(5)+1);
		LAi_SetCitizenType(sld);
		string slai_group = GetNationNameByType(sti(colonies[iColony].nation))  + "_citizens";
		LAi_group_MoveCharacter(sld, slai_group);
		//даем слух, что кэп на рейде
		 AddSimpleRumourCity(
		StringFromKey("LSC_Q2Utilite_60", LinkRandPhrase(
	StringFromKey("LSC_Q2Utilite_57", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, GetFullName(sld)),
	StringFromKey("LSC_Q2Utilite_58", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name),
	StringFromKey("LSC_Q2Utilite_59", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, GetFullName(sld)))),sld.City,2,1,"none");
	}
	else
	{	//стоит на рейде в порту
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_AddCharacter(sGroup, sld.id);			
		Group_SetGroupCommander(sGroup, sld.id);
		Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+1));
		Group_SetTaskNone(sGroup);
		//даем слух, что кэп на рейде
		 AddSimpleRumourCity(
		StringFromKey("LSC_Q2Utilite_64", LinkRandPhrase(
	StringFromKey("LSC_Q2Utilite_61", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, GetFullName(sld)),
	StringFromKey("LSC_Q2Utilite_62", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name),
	StringFromKey("LSC_Q2Utilite_63", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, GetFullName(sld)))),sld.City,2,1,"none");
	}
	//таймер через сколько опять выйти на карту
	int Qty = rand(7)+5; //через сколько дней выйдем на карту
	string name = "SecondTimer_" + sld.id;
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "CitizCapFromSeaToMap";
	pchar.quest.(name).CapId = sld.id; //в прерывании запомним Id кэпа
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//разыск кэпа от горожан. запись в квестбук из слухов
void CitizSeekCap_writeQuestBook(ref rid)
{
	int iTemp = GetCharacterIndex(rid.addString);
	if (iTemp != -1)
	{
		ref sld = &characters[iTemp];
		if (LAi_IsDead(sld)) return;
		ref npchar = &characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)];
		string sTitle = sld.quest.cribCity + "SCQ_" + npchar.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + npchar.quest.SeekCap, "3");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rid.city + "Gen"));
		AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + sld.quest.targetCity + "Acc"));
		if (GetIslandNameByCity(sld.quest.targetCity) != sld.quest.targetCity)
		{
			AddQuestUserData(sTitle, "sAreal", StringFromKey("InfoMessages_6", XI_ConvertString(GetIslandNameByCity(sld.quest.targetCity) + "Pre")));
		}
	}
}

//Создаём мушкетерского кэпа
void SetMushketCapitainInWorld(bool bRumourCreate)
{
	//создаем кэпов
	int Rank = sti(pchar.rank) + 15;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("MushketCap", "citiz_58", "man", "man", Rank, PIRATE, -1, true)); //watch_quest_moment //вариант officer_26
	sld.name = FindPersonalName("MushketCap_name");
	sld.lastname = FindPersonalName("MushketCap_lastname");
	SetCaptanModelByEncType(sld, "pirate");
	FantomMakeCoolSailor(sld, SHIP_BRIGQEEN, FindPersonalName("MushketCap_ship"), CANNON_TYPE_CULVERINE_LBS24, 65, 60, 60);
	FantomMakeCoolFighter(sld, 20, 55, 55, "blade34", "pistol2", 80);
	sld.Ship.Mode = "pirate";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	sld.WatchFort = true; //видеть форты
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "MushketCapShip";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.city = "PortRoyal"; //определим колонию, из бухты которой с мушкетом выйдет
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	pchar.questTemp.Mushket.Shore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("Кэп с мушкетом вышел из: " + sld.city + " и направился в: " + sld.quest.targetShore + "");
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	// sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.worldMapShip = "BrigantineShip";
	sld.mapEnc.Name = FindPersonalName("MushketCap_mapEnc");
	int daysQty = GetMaxDaysFromColony2Colony(sld.quest.targetCity, sld.city) + 5; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	// прерывания по квесту
	pchar.quest.SeekDoubleMushket_Capture.win_condition.l1 = "Character_Capture";
	pchar.quest.SeekDoubleMushket_Capture.win_condition.l1.character = "MushketCap";
	pchar.quest.SeekDoubleMushket_Capture.function = "SeekDoubleMushket_Capture";

	pchar.quest.SeekDoubleMushket_GroupDeath.win_condition.l1 = "Group_Death";
	pchar.quest.SeekDoubleMushket_GroupDeath.win_condition.l1.group = "MushketCapShip";
	pchar.quest.SeekDoubleMushket_GroupDeath.function = "SeekDoubleMushket_GroupDeath";
	//заносим Id кэпа в базу нпс-кэпов
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "mushket"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = "SeekDoubleMushket"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SeekDoubleMushket"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	if (bRumourCreate)
	{
	    //пускаем слух
		SetMushketFromSeaToMap_AddRumour(daysQty);
	}
}

void SetMushketFromSeaToMap_AddRumour(int daysQty)
{
	ref sld = characterFromId("MushketCap");

	if (CheckAttribute(&TEV, "MushketCapShipRumourId")) DeleteRumor(FindRumour(sti(TEV.MushketCapShipRumourId)));
	string sRumourName = GetRandName(NAMETYPE_VIP, NAME_NOM);
    TEV.MushketCapShipRumourId = AddSimpleRumour(LinkRandPhrase(
        StringFromKey("Common_rumours_39", XI_ConvertString(sld.quest.targetShore + "Gen")),
        StringFromKey("Common_rumours_40", XI_ConvertString(sld.quest.targetShore + "Gen")),
        StringFromKey("Common_rumours_41", generateRandomNameToShip(1), sRumourName, XI_ConvertString(sld.quest.targetShore + "Gen"))
    ), 777, daysQty, 1);
}

//плавание мушкетерского кэпа
void SetMushketFromMapToSea()
{
	ref sld = characterFromId("MushketCap");
	sld.quest = "InShore"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);

	string sGroup = "MushketCapShip";
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);			
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+5));
	Group_SetTaskNone(sGroup);
	//таймер через сколько опять выйти на карту
	int Qty = rand(2)+3;
	string name = "MushketTimer";
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetMushketFromSeaToMap";
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
    //пускаем слух
    if (CheckAttribute(&TEV, "MushketCapShipRumourId")) DeleteRumor(FindRumour(sti(TEV.MushketCapShipRumourId)));
    string sRumourName = GetRandName(NAMETYPE_MAIN, NAME_NOM);
    TEV.MushketCapShipRumourId = AddSimpleRumour(
		StringFromKey("LSC_Q2Utilite_68", LinkRandPhrase(
	StringFromKey("LSC_Q2Utilite_65", XI_ConvertString(sld.quest.targetShore + "Pre")),
	StringFromKey("LSC_Q2Utilite_66", XI_ConvertString(sld.quest.targetShore + "Pre")),
	StringFromKey("LSC_Q2Utilite_67", sRumourName, XI_ConvertString(sld.quest.targetShore + "Pre")))),777,Qty,1);
}

//плавание Даньки
void SetDanielleFromMapToSea()
{
	ref sld = characterFromId("Danielle");
	sld.quest = "InShore"; //флаг кэпа стоит в порту
	sld.City = sld.quest.targetCity; //аттрибут текущего города пропишем
	int iColony = FindColony(sld.City);

	string sGroup = "DanielleGroup";
	group_DeleteGroup(sGroup);
	Group_AddCharacter(sGroup, sld.id);			
	Group_SetGroupCommander(sGroup, sld.id);
	Group_SetAddress(sGroup, colonies[iColony].island, "quest_ships", "Quest_ship_"+(rand(2)+3));
	Group_SetTaskNone(sGroup);
	//таймер через сколько опять выйти на карту
	int Qty = rand(5)+7;
	string name = "DanielleTimer";
	PChar.quest.(name).win_condition.l1            = "Timer";
    PChar.quest.(name).win_condition.l1.date.day   = GetAddingDataDay(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.month = GetAddingDataMonth(0, 0, Qty);
    PChar.quest.(name).win_condition.l1.date.year  = GetAddingDataYear(0, 0, Qty);
    PChar.quest.(name).function					= "SetDanielleFromSeaToMap";
	//обновим дату в базе для контроля кэпов на суше
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = Qty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
    //пускаем слух
    if (CheckAttribute(&TEV, "DanielleShipRumourId")) DeleteRumor(FindRumour(sti(TEV.DanielleShipRumourId)));
    TEV.DanielleShipRumourId = AddSimpleRumour(
		StringFromKey("LSC_Q2Utilite_72", LinkRandPhrase(
	StringFromKey("LSC_Q2Utilite_69", XI_ConvertString(sld.quest.targetShore + "Pre")),
	StringFromKey("LSC_Q2Utilite_70", XI_ConvertString(sld.quest.targetShore + "Pre")),
	StringFromKey("LSC_Q2Utilite_71", XI_ConvertString(sld.quest.targetShore + "Pre")))),1,Qty,1);
}

//линейка Блада в Барбадосе
//поставить Синко Льягас в город
void SetShipInBridgetown()
{
	int n = FindLocation("Bridgetown_town");
	locations[n].models.always.ship = "Bridgetown_ship";
	locations[n].models.always.shipreflect = "Bridgetown_shipreflect";
	Locations[n].models.always.shipreflect.sea_reflection = 1;
	locations[n].models.always.locators = "Bridgetown_locatorsShip";
	locations[n].models.day.fonarShip = "Bridgetown_fdShip";
	locations[n].models.night.fonarShip = "Bridgetown_fnShip";
	locations[n].models.day.charactersPatch = "Bridgetown_patchship_day";
	locations[n].models.night.charactersPatch = "Bridgetown_patchship_night";

	locations[n].reload.ship1.name = "reloadShip";
	locations[n].reload.ship1.go = "Cabin_Quest";
	locations[n].reload.ship1.emerge = "reload1";
	locations[n].reload.ship1.autoreload = "0";
	locations[n].reload.ship1.label = "cabine";

	n = FindLocation("Cabin_Quest");
	DeleteAttribute(&locations[n], "boarding");
	DeleteAttribute(&locations[n], "camshuttle");
	DeleteAttribute(&locations[n], "CabinType");

	locations[n].reload.l1.name = "reload1";
	locations[n].reload.l1.go = "Bridgetown_town";
	locations[n].reload.l1.emerge = "reloadShip";
	locations[n].reload.l1.autoreload = "0";
	locations[n].reload.l1.label = "Ship";
}
//убрать Синко Льягас из города
void RemoveShipFromBridgetown()
{
	int n = FindLocation("Bridgetown_town");	
	DeleteAttribute(&locations[n], "models.always.ship");
	DeleteAttribute(&locations[n], "models.always.shipreflect");
	DeleteAttribute(&locations[n], "models.always.shipreflect.sea_reflection");
	locations[n].models.always.locators = "Bridgetown_locators";
	DeleteAttribute(&locations[n], "models.day.fonarShip");
	DeleteAttribute(&locations[n], "models.night.fonarShip");
	locations[n].models.day.charactersPatch = "Bridgetown_patch_day";
	locations[n].models.night.charactersPatch = "Bridgetown_patch_night";
	DeleteAttribute(&locations[n], "reload.ship1");

	n = FindLocation("Cabin_Quest");
	DeleteAttribute(&locations[n], "reload");
	Locations[n].boarding = "true";
	Locations[n].boarding.nextdeck = "";
	Locations[n].camshuttle = 1;
	Locations[n].boarding.locatorNum = 1;
	Locations[n].CabinType = true;
	locations[n].environment.weather.rain = false;
	Locations[n].boarding.Loc.Hero = "loc2";
    Locations[n].boarding.Loc.Capt = "loc0";
}

bool CapBloodLine_CheckMoneyForNettl()
{
	int ci = GetCharacterIndex("Nettl");
	if (ci < 0)
		return false;

	ref chr = &Characters[ci];
    return makeint(pchar.money) >= 25000 && Pchar.questTemp.CapBloodLine.TalkWithNettl == true && chr.lifeday != 0;
}

bool CapBloodLine_NeedMoney_CheckHellsForQuest()
{
	bool verdict = false;
	ref chr;
	int ci = GetCharacterIndex("Hells");
	if (ci >= 0)
	{
	    chr = &Characters[ci];
	   	return Pchar.questTemp.CapBloodLine.stat == "needMoney" &&
	    	!CheckAttribute(Pchar, "questTemp.CapBloodLine.fishplace") &&
	    	chr.dialog.currentnode == "First time";
	}

    return false;
}

int CapBloodLine_GetEngGuardAddRank()
{
	int rate = MOD_SKILL_ENEMY_RATE;
	Restrictor(&rate, 1, 10);
	if (rate < 3)
	{
	    return 0;
	}
	if (rate < 8)
	{
		return makeint(2*rate/3);
	}

	return rate;
}

int CapBloodLine_GetSpaSoldierAddRank()
{
	int rate = MOD_SKILL_ENEMY_RATE;
	Restrictor(&rate, 1, 10);

	return 1 + makeint(rate / 4);
}

//------------------- линейка ГПК ----------------------
//пробежаться по сундукам
void LSC_checkBoxes()
{
	ref loc;
	aref arBox;
	string sName;
	for(int i=0; i<MAX_LOCATIONS; i++)
	{				
		loc = &locations[i];
		if (CheckAttribute(loc, "fastreload") && loc.fastreload == "LostShipsCity" && loc.id != "FernandaDiffIndoor")
		{	
			for(int n=1; n<=MAX_HANDLED_BOXES; n++)
			{
				sName = "private" + n;
				if (CheckAttribute(loc, sName) && sName != "private11")
				{					
					makearef(arBox, loc.(sName));
					if (CheckAttribute(arBox, "equip") && rand(1))
					{
						DeleteAttribute(arBox, "items");
						arBox.items = "";
					}
				}
				else break;
			}
		}
	}
}

//линейка ГПК. проверить дистанцию до своих во время атаки
void LSC_CheckCasperDistance(ref sld)
{
	if (!CheckAttribute(pchar, "questTemp.LSC.Armo.Interrapt"))
	{
		sld.quest.checkCasper = true; //для обработки в АИ warrior
		pchar.quest.LSC_KillOneCasper.win_condition.l1 = "NPC_Death";
		pchar.quest.LSC_KillOneCasper.win_condition.l1.character = sld.id;
		pchar.quest.LSC_KillOneCasper.function= "LSC_KillOneCasper";
		pchar.questTemp.LSC.Armo.casperFullName = GetFullName(sld);
		pchar.questTemp.LSC.Armo.Interrapt = true; //чтобы не вызывать больше прерывания
	}
	float dist;
	if (GetCharacterDistByLoc(sld, "goto", "goto12_4", &dist))
	{
		if (dist < 40.0) 
		{
			LSC_CasperIsHelp();
		}		
	}
}
//клан ломится на выручку
void LSC_CasperIsHelp()
{
	Log_SetStringToLog(StringFromKey("InfoMessages_242"));
	chrDisableReloadToLocation = true;
	pchar.questTemp.LSC = "toSeekMechanikCasperOff";
	//если пошёл навал, то чистим квест Армо
	pchar.questTemp.LSC.Armo = 15; //завязываем с дачей квестов от Армо
	pchar.quest.LSC_KillOneCasper.over = "yes";
	pchar.quest.LSC_checkCasperDead.over = "yes";
	//бойцов в подмогу
	int iTemp = GetCharacterIndex("Casper_head");
	if (iTemp != -1) ChangeCharacterAddressGroup(&characters[iTemp], "LostShipsCity_town", "reload", "reload55");
	for (int i=1; i<=11; i++)
	{
		iTemp = GetCharacterIndex("Casper_"+i);
		if (iTemp != -1)
		{
			if (characters[iTemp].location != "LostShipsCity_town")
			{
				ChangeCharacterAddressGroup(&characters[iTemp], "LostShipsCity_town", "reload", "reload55");
			}
			else
			{
				if (!LAi_IsDead(&characters[iTemp]))
				{
					LAi_group_MoveCharacter(&characters[iTemp], "LSC_CASPER");
					DeleteAttribute(&characters[iTemp], "quest.checkCasper"); //сносим флаги на проверку расстояния до базы
					if (CheckAttribute(&characters[iTemp], "protector")) //сносим проверки протекторов
					{
						DeleteAttribute(&characters[iTemp], "protector.CheckAlways");
						DeleteAttribute(&characters[iTemp], "protector");
					}
				}
			}
		}
	}
	//мушкетеров ставим
	// ref sld = GetCharacter(NPC_GenerateCharacter("CasperMush_1", "mush_ctz_1", "man", "mushketer", 30, PIRATE, -1, false)); //watch_coas_moment
	// SetCharacterPerk(sld, "GunProfessional");
	// sld.MusketerDistance = 0;
	// LAi_SetWarriorType(sld);
	// LAi_group_MoveCharacter(sld, "LSC_CASPER");
	// ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "mushketer1");

	// sld = GetCharacter(NPC_GenerateCharacter("CasperMush_2", "mush_ctz_12", "man", "mushketer", 30, PIRATE, -1, false));//watch_coas_moment
	// SetCharacterPerk(sld, "GunProfessional");
	// sld.MusketerDistance = 0;
	// LAi_SetWarriorType(sld);
	// LAi_group_MoveCharacter(sld, "LSC_CASPER");
	// ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "mushketer2");
	//дополнительно, на всякий случай
	LAi_group_SetRelation("LSC_CASPER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("LSC_CASPER", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("LSC_CASPER", "LSC_AfterFightCasper_Insane_OpenTheDoors");
}

//функция для опредения прогресса по ОС
void LSC_SuicideSquadEnough()
{
    if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad"))
	{
		aref aSuicideSquad; makearef(aSuicideSquad, pchar.questTemp.LSC.suicideSquad);

		if (GetAttributesNum(aSuicideSquad) == 1)
		{
			AddLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "ISS_DefeatCasperClan");
		}

		if (GetAttributesNum(aSuicideSquad) == 2)
		{
			SetFunctionLocationCondition("LSC_NotifySuicideSquadEnough", "LostShipsCity_town", false);
		}
	}
}


//функция для опредения закрыты ли все начальные побочные квесты ГПК
bool IsLSCQuestsProgressCompleted()
{
    if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "over"
        && CheckAttribute(pchar, "questTemp.LSC.lostDecster") && pchar.questTemp.LSC.lostDecster == "over"
        && CheckAttribute(pchar, "questTemp.LSC.LegroHelp") && pchar.questTemp.LSC.LegroHelp == "over"
        && CheckAttribute(pchar, "questTemp.LSC.takeCandles") && pchar.questTemp.LSC.takeCandles == "over"
        && CheckAttribute(pchar, "questTemp.LSC.takeStoreMoney") && pchar.questTemp.LSC.takeStoreMoney == "over"
        && CheckAttribute(pchar, "questTemp.LSC.control_day")
       ) return true;

    return false;
}

//функция добавления записи в СЖ что пора идти к бармену
void LSC_CheckReadyMainLine()
{
    if (IsLSCQuestsProgressCompleted()) AddQuestRecord("ISS_MainLine", "5");
}

// добавляем квест-метки жителям ГПК (вопросы, слухи, и т.п.)
void LSC_AddSecondaryQuestMarksToCitizens()
{
    for (int i = 0; i < MAX_CHARACTERS; i++)
    {
        ref chr = &Characters[i];

        if(CheckAttribute(chr, "city") && chr.city == "LostShipsCity" && CheckAttribute(chr, "cityTape"))
        {
            if (chr.cityTape == "citizen" || chr.cityTape == "citizenHome")
            {
                AddLandQuestMark_Main_WithCondition(chr, "LSC_Rumours", "LSC_Rumours_Citizen_QuestMarkCondition");
                AddLandQuestMark_Main_WithCondition(chr, "LSC_Questions", "LSC_Questions_Citizen_QuestMarkCondition");
            }
        }
    }
}

void LSC_UpdateQuestMarksToCitizens()
{
    for (int i = 0; i < MAX_CHARACTERS; i++)
    {
        ref chr = &Characters[i];

        if(CheckAttribute(chr, "city") && chr.city == "LostShipsCity")
        {
            SetCurrentQuestMark(chr);
        }
    }
}

void LSC_RemoveSecondaryQuestMarksToCitizens()
{
    for (int i = 0; i < MAX_CHARACTERS; i++)
    {
        ref chr = &Characters[i];

        if(CheckAttribute(chr, "city") && chr.city == "LostShipsCity")
        {
            RemoveLandQuestMark_Main(chr, "LSC_Rumours");
            RemoveLandQuestMark_Main(chr, "LSC_Questions");
        }
    }
}

void LSC_FindMapLSC_AddQuestMarksToWoman()
{
    AddLandQuestMark_Main(CharacterFromID("ElisTaylor"), "FindMapLSC");
    AddLandQuestMark_Main(CharacterFromID("ElisTaylor"), "FindMapLSC");
    AddLandQuestMark_Main(CharacterFromID("LeaToors"), "FindMapLSC");
    AddLandQuestMark_Main(CharacterFromID("MonikaRight"), "FindMapLSC");
    AddLandQuestMark_Main(CharacterFromID("OreliBertin"), "FindMapLSC");
    AddLandQuestMark_Main(CharacterFromID("SandraGomes"), "FindMapLSC");
    AddLandQuestMark_Main(CharacterFromID("SesilGalard"), "FindMapLSC");
}

void LSC_FindMapLSC_RemoveQuestMarksToWoman()
{
    RemoveLandQuestMark_Main(CharacterFromID("ElisTaylor"), "FindMapLSC");
    RemoveLandQuestMark_Main(CharacterFromID("ElisTaylor"), "FindMapLSC");
    RemoveLandQuestMark_Main(CharacterFromID("LeaToors"), "FindMapLSC");
    RemoveLandQuestMark_Main(CharacterFromID("MonikaRight"), "FindMapLSC");
    RemoveLandQuestMark_Main(CharacterFromID("OreliBertin"), "FindMapLSC");
    RemoveLandQuestMark_Main(CharacterFromID("SandraGomes"), "FindMapLSC");
    RemoveLandQuestMark_Main(CharacterFromID("SesilGalard"), "FindMapLSC");
}

//квест на мужа Элис Тейлор, после получения слуха
void LSC_rumourElisHusband()
{
	if (!CheckActiveQuest("ISS_ElisHusband"))
	{
		pchar.questTemp.LSC.ElisHusband = "begin";
		AddQuestRecord("ISS_ElisHusband", "1");

		AddLandQuestMark_Main(CharacterFromID("MaximTailor"), "ISS_ElisHusband");
	}
	LSC_UpdateQuestMarksToCitizens();
}
//квест на бутылку Доминика Легро
void LSC_rumourBottleOfLegro()
{
	if (!CheckActiveQuest("TakeVineToPrisoner"))
	{
		AddQuestRecord("TakeVineToPrisoner", "8");
	}
	LSC_UpdateQuestMarksToCitizens();
}
//квест на свечи для падре
void LSC_rumourTakeCandles()
{
	if (!CheckActiveQuest("ISS_takeCandles"))
	{
		AddQuestRecord("ISS_takeCandles", "4");
	}
	LSC_UpdateQuestMarksToCitizens();
}
//начало сразу, после первого базара с адмиралом
void LSC_beginElisHusband()
{	
	// муж Элис Тейлор
	ref sld = GetCharacter(NPC_GenerateCharacter("MaximTailor", "Max_Tailor", "man", "man", 10, PIRATE, -1, false));
	sld.name = FindPersonalName("MaximTailor_name");
	sld.lastname = FindPersonalName("MaximTailor_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "TartarusPrison";
	sld.location.group = "quest";
	sld.location.locator = "prison4";
	sld.dialog.filename   = "Quest\LostShipsCity\MaximTailor.c";
	sld.dialog.currentnode   = "InPrison";
	sld.cityTape = "quest"; //тип нпс
	sld.greeting = "pirat_common";
	sld.location.hours = 4; //передвижения через .. часов
	LAi_SetGroundSitType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	LAi_SetHP(sld, 350.0, 350.0);
}

//квест со скелетом Лейтона Декстера
void LSC_rumourLostDecster()
{
	if (!CheckActiveQuest("LSC_findDekster"))
	{
		AddQuestRecord("LSC_findDekster", "1");
		AddLandQuestMark_Main(CharacterFromID("LeaToors"), "LSC_findDekster");
	}
	LSC_UpdateQuestMarksToCitizens();
}

void LSC_enterAdmiralBox()
{
    if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && pchar.questTemp.LSC.lostDecster != "over" && CheckCharacterItem(pchar, "admiralKey"))
    {
        AddQuestRecord("LSC_findDekster", "17");
        if (CheckCharacterItem(pchar, "shark_tooth"))
        {
            ref item = &Items[FindItem("shark_tooth")];
            if (CheckAttribute(item, "ItemType"))
            {
                AddQuestRecord("LSC_findDekster", "18");
                RemoveItems(pchar, "shark_tooth", 1);
            }
        }
		CloseQuestHeader("LSC_findDekster");
		pchar.questTemp.LSC.lostDecster = "over";
		LSC_CheckReadyMainLine(); //проверка все ли готово для продолжения основной линейки

        RemoveLandQuestMark_Main(CharacterFromId("LSCMayor"), "LSC_findDekster");
        RemoveLandQuestMark_Main(CharacterFromId("Ment_6"), "LSC_findDekster");
        RemoveLandQuestMark_Main(CharacterFromID("LSC_PrisonerHead"), "LSC_findDekster");
        RemoveLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "LSC_findDekster");
    }
	else if (!CheckAttribute(pchar, "questTemp.LSC.private10"))
	{
		if (CheckAttribute(pchar, "questTemp.LSC.lostDecster"))
		{
			if (pchar.questTemp.LSC.lostDecster == "seekBox")
			{
				AddQuestRecord("LSC_findDekster", "6");
			}
			else
			{
				int iTemp = GetCharacterIndex("LSC_Prisoner1");
				if (iTemp != 1 && CheckAttribute(&characters[iTemp], "quest.decster"))
				{
					AddQuestRecord("LSC_findDekster", "7");	
				}
				else
				{
					AddQuestRecord("LSC_findDekster", "9");
				}
				if (pchar.questTemp.LSC.lostDecster == "fromMentos")
				{
				    ref sld = CharacterFromId("Ment_6");
				    sld.quest.DeksterDestiny = true;
				    AddQuestRecord("LSC_findDekster", "15");
				    AddLandQuestMark_Main(sld, "LSC_findDekster");
				}
			}		
		}
		else
		{
			AddQuestRecord("LSC_findDekster", "8");
		}
		pchar.questTemp.LSC.lostDecster = "foundAdmiralBox";
		RemoveLandQuestMark_Main(CharacterFromID("LeaToors"), "LSC_findDekster");
		 AddSimpleRumourCityTip(
		StringFromKey("LSC_Q2Utilite_73"),"LostShipsCity",10,1,"LSC","LSC_rumourAdmiralLostKey");
		pchar.questTemp.LSC.private10 = true; //чтобы больше не срабатывало
	}
}
void LSC_rumourAdmiralLostKey()
{
	//делаем видимым ключ
	ref sld = ItemsFromID("admiralKey");
	sld.shown = true;
	sld.startLocation = "LostShipsCity_town";
	sld.startLocator = "item" + (rand(4)+2);
	SetTimerFunction("LSC_admiralFoundOwnKey", 0, 0, 2); //таймер на снятие ключа из локатора
	pchar.questTemp.LSC.lostDecster = "admiralLostKey";
	AddQuestRecord("LSC_findDekster", "10");
	LSC_UpdateQuestMarksToCitizens();
	QuestPointerToLoc(sld.startLocation, "item", sld.startLocator);
}

//таймер
void SetShowTimer(float time)
{
	pchar.showTimer = time + 0.99;
	pchar.quest.ClearTimer.win_condition.l1 = "ExitFromLocation";
	pchar.quest.ClearTimer.win_condition.l1.location = pchar.location;
	pchar.quest.ClearTimer.function = "ClearTimer";
}

void ClearTimer(string qName)
{
	DeleteAttribute(pchar, "showTimer");
	ClearAllLogStrings();
}

//создание резервной базы на абордажников для юза нефритового черепа
void CopyPassForAztecSkull()
{
	if (CheckCharacterItem(pchar, "SkullAztec"))
	{	
        //сносим старую базу
		DeleteAttribute(pchar, "AztecSkull");
		pchar.AztecSkull = "";
		//заполняем архивную базу 
		aref	arFromBox, arToBox;
    	makearef(arFromBox, pchar.fellows.passengers.officers);
		makearef(arToBox, pchar.AztecSkull);
		CopyAttributes(arToBox, arFromBox);
	}
}

bool IsAztecSkullOfficer(ref sld)
{
	if (!CheckAttribute(pchar, "AztecSkull.id1")) return false;
	string sTemp;
	aref arOfficer;
    makearef(arOfficer, pchar.AztecSkull);
    for (int i=1; i<=3; i++)
    {
		sTemp = "id" + i;
		if (arOfficer.(sTemp) == sld.index)
		{
			return true;
		}
	}
	return false;
}

void SetAztecUsedTotem(ref _location, string _itemId, string _locator)
{	
	//-----------------------------------------
	if (_itemId == "Totem_11")    //снимаем огонь
	{
		DeleteAttribute(_location, "gotoFire");
		Log_SetStringToLog(StringFromKey("InfoMessages_7"));
		pchar.questTemp.Teno = "takeFire";
		SetCurrentQuestMark(characterFromId("Montesuma"));
	}
	//-----------------------------------------
	if (_itemId == "Totem_12") //открываем каменный сундук в большом храме (с кинжалом)
	{
		DeleteAttribute(_location, "private1.closed");
		Log_SetStringToLog(StringFromKey("InfoMessages_8"));
	}
	//-----------------------------------------
	if (_itemId == "Totem_13") //снимаем огонь 2х
	{
		_location.lockFire.button02.active = true;
		if (CheckAttribute(_location, "lockFire.button02.active") && CheckAttribute(_location, "lockFire.button03.active"))
		{
			DeleteAttribute(_location, "gotoFire");
			Log_SetStringToLog(StringFromKey("InfoMessages_7"));
			pchar.questTemp.Teno = "takeFire";
		    SetCurrentQuestMark(characterFromId("Montesuma"));
		}
	}
	if (_itemId == "Totem_14") //снимаем огонь 2х
	{
		_location.lockFire.button03.active = true;
		if (CheckAttribute(_location, "lockFire.button02.active") && CheckAttribute(_location, "lockFire.button03.active"))
		{
			DeleteAttribute(_location, "gotoFire");
			Log_SetStringToLog(StringFromKey("InfoMessages_7"));
			pchar.questTemp.Teno = "takeFire";
		    SetCurrentQuestMark(characterFromId("Montesuma"));
		}
	}
	//-----------------------------------------
	if (_itemId == "Totem_15") //открываем каменный сундук в большом храме
	{
		DeleteAttribute(_location, "private2.closed");
		Log_SetStringToLog(StringFromKey("InfoMessages_8"));
	}
	//-----------------------------------------
	if (_itemId == "Totem_1" || _itemId == "Totem_2" || _itemId == "Totem_3" || _itemId == "Totem_4" || _itemId == "Totem_5" ||
		_itemId == "Totem_6" || _itemId == "Totem_7" || _itemId == "Totem_8" || _itemId == "Totem_9" || _itemId == "Totem_10")
	{
		int n;
		int num = 0;
		int locIndex = sti(_location.idxTeno); //индекс Теночтитлана
		string sTemp;
		_location.openGreatTemple = true;
		for (int i=1 ; i<=10; i++)
		{
			sTemp = "idx" + i;
			n = sti(locations[locIndex].temples.(sTemp));
			if (CheckAttribute(&locations[n], "openGreatTemple")) num++;
		}
		if (num >= 10)
		{
			DeleteAttribute(&locations[locIndex], "reload.l32.disable");
			DeleteAttribute(&locations[locIndex], "reload.l33.disable");
			DeleteAttribute(&locations[locIndex], "reload.l34.disable");
			AddQuestRecord("TenochtitlanQuest", "7");
			pchar.questTemp.Teno = "takeSkull";
			Teno_SeekTempleTotems_DelQuestPointers();
		}		
	}
}

//бог мертвых разгневан
void LoginDeadmansGod()
{
	chrDisableReloadToLocation = true;
	LAi_group_SetRelation("teno_monsters_group", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//ставим бога мертвых	
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, false);
	LAi_LocationFightDisable(loadedLocation, true);
	ref sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod", "mictlantecuhtli", "skeleton", "man", 100, PIRATE, 0, true));
	sld.undead = "1";
    FantomMakeCoolFighter(sld, 100, 100, 100, "maquahuitl", "pistol5", 3000);
	sld.name = FindPersonalName("DeadmansGod_name");
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Mictlantecuhtli.c";
	sld.dialog.currentnode   = "InGreateTemple";
	ChangeCharacterAddressGroup(sld, "Temple_great", "goto", "goto1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0.0, 0);
	LAi_CharacterPlaySound(sld, "DeadmansGod");
}

//проверка на наличие тотемов в ГГ и их использование ранее
bool CheckMainHeroTotem(string itemName)
{
    if( CheckAttribute(pchar,"Items."+itemName) && sti(pchar.Items.(itemName))>0 )	
	{
		return true;
	}
	else
	{
		for (int i=Totems_start; i<Totems_end; i++)
		{			
			if (Items[i].id == itemName)
			{
				if (CheckAttribute(&Items[i], "shown.used"))
				{
					return true;	
				}
				break;
			}
		}
	}
	return false;	
}

// --> ugeen 20.06.09 - проверка на наличие карт у ГГ
bool CheckMainHeroMap(string itemName)
{
    if( CheckAttribute(pchar,"Items."+itemName) && sti(pchar.Items.(itemName))>0 )	
	{
		return true;
	}
	return false;	
}
// <-- ugeen

void LoginShotgunGuards()
{
	int i, n;
	ref sld;
	
	ItemTakeEx(pchar, "bullet_colt,GunPowder_colt", "30"); // KZ > Револьверные пули и порох по 30 шт. по факту взятия огнестрела
	
	if (pchar.questTemp.Teno != "YouWinGod")
	{
		LAi_group_Delete("Teno_CollierGroup");
		chrDisableReloadToLocation = true;
		
		for (i=1; i<=8; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("AztecWarrior_"+i, "AztecWarrior"+(rand(4)+1), "skeleton", "man", 30, PIRATE, 0, true));
			sld.undead = "1";
			FantomMakeCoolFighter(sld, 30, 90, 90, "maquahuitl", "", 100);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "Teno_CollierGroup");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
			LAi_group_SetRelation("Teno_CollierGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Teno_CollierGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Teno_CollierGroup", "Teno_CollierGroup_Dead");

			// KZ > Револьверные картриджи и капсюли только на трупах воинов, по 30 шт. со всех
			if (i == 1) n = 9;
			else n = 3;

			sld.KeepItems.cartridge_colt = "" + n;
			sld.KeepItems.GunCap_colt = "" + n;
		}
	}
}

// Warship 07.07.09 Пасхалка - бригантина "Мэри Селест"
void MaryCelesteInit()
{
	ref character, realShip;
	string capID = "MaryCelesteCapitan";
	string seaGroup = "MaryCelesteGroup";
	int good;
	
	// Сцуко.. В функции низя делать как generableGoods[15] = { GOOD_FOOD, GOOD_WEAPON, ... }; - даёт ошибку
	// Если вынести из функции, то все норм
	/*int generableGoods[15] = { GOOD_FOOD, GOOD_WEAPON, GOOD_MAHOGANY, GOOD_MEDICAMENT, GOOD_SILK,
		GOOD_SANDAL, GOOD_COFFEE, GOOD_CLOTHES, GOOD_EBONY, GOOD_TOBACCO,
		GOOD_CHOCOLATE, GOOD_WINE, GOOD_RUM, GOOD_CINNAMON, GOOD_LEATHER };*/
	
	int generableGoods[15];
	
	generableGoods[0] = GOOD_FOOD;
	generableGoods[1] = GOOD_WEAPON;
	generableGoods[2] = GOOD_MAHOGANY;
	generableGoods[3] = GOOD_MEDICAMENT;
	generableGoods[4] = GOOD_SILK;
	generableGoods[5] = GOOD_SANDAL;
	generableGoods[6] = GOOD_COFFEE;
	generableGoods[7] = GOOD_CLOTHES;
	generableGoods[8] = GOOD_EBONY;
	generableGoods[9] = GOOD_TOBACCO;
	generableGoods[10] = GOOD_CHOCOLATE;
	generableGoods[11] = GOOD_WINE;
	generableGoods[12] = GOOD_RUM;
	generableGoods[13] = GOOD_CINNAMON;
	generableGoods[14] = GOOD_LEATHER;
	
	character = GetCharacter(NPC_GenerateCharacter(capID , "Pirate_5", "man", "man", 50, ENGLAND, -1, true));
//	FantomMakeCoolFighter(character, 50, 50, 45, "blade34", "pistol5", 50);
	FantomMakeCoolSailor(character, SHIP_BRIGANTINE, FindPersonalName("MaryCelesteCapitan_name"), CANNON_TYPE_CULVERINE_LBS16, 50, 50, 50);
	character.name = FindPersonalName("EmptyShip_name");
	character.lastname = "";
	character.mapEnc.type = "trade";
	character.mapEnc.Name = FindPersonalName("EmptyShip_mapEnc");
	LAi_SetImmortal(character, true);
	SetCharacterGoods(character, GOOD_RUM, 700);
	Character_SetAbordageEnable(character, false); // Низя абордировать
	
	SetCrewQuantityOverMax(character, 0); // Никого живого
	
	realShip = GetRealShip(GetCharacterShipType(character));
	
	PChar.QuestTemp.MaryCeleste = "NotFind";
	PChar.QuestTemp.MaryCeleste.TurnRate = realShip.TurnRate; // Запомним, потом восстановим для интерфейса
	
	realShip.lowpolycrew = 0; // Нету никого на палубе
	realShip.TurnRate = 1; // Чтоб не особо изворотливым был
	realShip.capacity = 2820;
	
	NullCharacterGoods(character); // Нулим товары в трюме
	
	AddCharacterGoodsSimple(character, GOOD_BALLS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_GRAPES, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_KNIPPELS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_BOMBS, 200 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_POWDER, 500 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_FOOD, 50 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_WEAPON, 20 + rand(30));
	AddCharacterGoodsSimple(character, GOOD_MEDICAMENT, 10 + rand(20));
	AddCharacterGoodsSimple(character, GOOD_SAILCLOTH, 50 + rand(50));
	AddCharacterGoodsSimple(character, GOOD_PLANKS, 20 + rand(30));
	
	good = generableGoods[rand(14)];
	// GetCharacterFreeSpace(ref _refCharacter,int _Goods) - вернёт сколько можно положить данного товара в трюм персонажу
	AddCharacterGoodsSimple(character, good, GetCharacterFreeSpace(character, good) - 1);
	
	character.AlwaysFriend = true; // Друзья навек
	character.ShipEnemyDisable = true; // Флаг не обижаться на выстрелы
	character.CanDropSails = false; // Низя спускать паруса
	
	Group_FindOrCreateGroup(seaGroup);
	Group_SetTaskAttackInMap(seaGroup, PLAYER_GROUP);
	Group_LockTask(seaGroup);
	Group_AddCharacter(seaGroup, capID);
	Group_SetGroupCommander(seaGroup, capID);
	SetRandGeraldSail(character, ENGLAND);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придет
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	Map_CreateTrader(character.fromShore, character.toShore, capID, GetMaxDaysFromColony2Colony(character.toCity, character.fromCity));
	
	if (MOD_BETTATESTMODE == "On")
		trace("Бригантина Мэри Селест вышла из " + character.fromCity + " и направилась в " + character.toShore);
}

string UpdateLSCClanParol()
{
    string sTemp = "a" + rand(sti(NullCharacter.SeaQuestions));
    return NullCharacter.SeaQuestions.(sTemp);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------------------ "Корабль-призрак" ----------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void GhostShipQuest_Begin_AddQuestMarks()
{
    // Белый мальчик
    AddLandQuestmarkToFantoms_Main("JohnDavy", "GhostShipQuest", "GhostShipQuest_JohnDavy_QuestMarkCondition");
	AddLandQuestmarkToFantoms_Main("habitue", "GhostShipQuest", "GhostShipQuest_Habitues_QuestMarkCondition");

    AddMapQuestMark_Major("Shore9", "GhostShipQuest", "GhostShipQuest_JohnDavy_WDMQuestMarkCondition");
}

void GhostShipQuest_NeedCoins_Mayor_SetQuestMarks(bool isSet)
{
    for (int i=0; i<MAX_COLONIES; i++)
    {
        if (!CheckAttribute(&colonies[i], "nation")) continue;
        if (colonies[i].nation == "none") continue; // необитайки
        if (sti(colonies[i].nation) == PIRATE) continue;

        int iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
        if (iChar != -1)
        {
            if(isSet)
            {
                AddLandQuestmark_Main_WithCondition(&Characters[iChar], "GhostShipQuest", "GhostShipQuest_NeedCoins_Mayor_QuestMarkCondition");
            }
            else
            {
                RemoveLandQuestmark_Main(&Characters[iChar], "GhostShipQuest");
            }
        }
    }
}

void GhostShipQuest_NeedCoins_Mayor_AddQuestMarks()
{
    GhostShipQuest_NeedCoins_Mayor_SetQuestMarks(true);
}

void GhostShipQuest_NeedCoins_Mayor_DelQuestMarks()
{
    GhostShipQuest_NeedCoins_Mayor_SetQuestMarks(false);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <-- End ------------------------------- "Корабль-призрак" ----------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------------------ "Нац. линейки" ----------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void StateLines_Begin_AddQuestMarks()
{
    AddLandQuestmark_Main_WithCondition(CharacterFromID("eng_guber"), "Eng_Line", "StateLines_Begin_QuestMarkCondition");
    AddLandQuestmark_Main_WithCondition(CharacterFromID("fra_guber"), "Fra_Line", "StateLines_Begin_QuestMarkCondition");
    AddLandQuestmark_Main_WithCondition(CharacterFromID("spa_guber"), "Spa_Line", "StateLines_Begin_QuestMarkCondition");
    AddLandQuestmark_Main_WithCondition(CharacterFromID("hol_guber"), "Hol_Line", "StateLines_Begin_QuestMarkCondition");

    AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "EngLine_Begin_WDMQuestMarkCondition");
    AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "FraLine_Begin_WDMQuestMarkCondition");
    AddMapQuestMark_Major("Havana_town", "Spa_Line", "SpaLine_Begin_WDMQuestMarkCondition");
    AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "HolLine_Begin_WDMQuestMarkCondition");
}

void StateLines_Begin_DelQuestMarks()
{
    RemoveLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
    RemoveLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
    RemoveLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
    RemoveLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");

    RemoveMapQuestMark("PortRoyal_town", "Eng_Line");
    RemoveMapQuestMark("Tortuga_town", "Fra_Line");
    RemoveMapQuestMark("Havana_town", "Spa_Line");
    RemoveMapQuestMark("Villemstad_town", "Hol_Line");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <-- End ------------------------------- "Нац. линейки" ----------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

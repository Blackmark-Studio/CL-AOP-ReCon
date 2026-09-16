// KZ > Фон главного меню из обычной локации ресурсов, без дублирования моделей и текстур.
// > Локации перечисляются в MainMenuLoc_DeclareAll.
// > Объявленных локаций может быть сколько угодно, в меню выбирается случайная.
// > Кадр камеры подбирается прямо в меню (в engine.ini нужно выставить ondebugkeys = 1):
// > Ctrl+WASD - лететь, Ctrl+стрелки - вертеть, Shift/Alt - быстрее/медленнее, Ctrl+C - выписать текущий кадр в лог.
// > Если ни одна локация не объявлена или её не удалось загрузить, меню показывает оригинальную сцену MainMenu\MainMenu.

#define MSG_BACKSCENE_SET_CAMERA_POS	11	// "fffffff": откуда(3), куда(3), угол обзора

object mmDecl;		// > объявления локаций фона; строятся заново при каждой сборке сцены
int    mmDeclNum;

// > Объявление локации: id и кадр камеры "откуда - куда"
void MainMenuLoc_Add(string sLocID, float fx, float fy, float fz, float tx, float ty, float tz)
{
	string sD, sP;

	sD = "d" + mmDeclNum;
	mmDecl.(sD) = sLocID;

	sP = sD + ".camera.from.x";	mmDecl.(sP) = fx;
	sP = sD + ".camera.from.y";	mmDecl.(sP) = fy;
	sP = sD + ".camera.from.z";	mmDecl.(sP) = fz;
	sP = sD + ".camera.to.x";	mmDecl.(sP) = tx;
	sP = sD + ".camera.to.y";	mmDecl.(sP) = ty;
	sP = sD + ".camera.to.z";	mmDecl.(sP) = tz;

	mmDeclNum = mmDeclNum + 1;
}

// > имя ветки последней объявленной локации, пустая строка если объявлений ещё нет
string MainMenuLoc_LastDecl()
{
	if (mmDeclNum < 1) return "";
	return "d" + (mmDeclNum - 1);
}

// > угол обзора для последней объявленной локации
void MainMenuLoc_SetPerspective(float fPerspective)
{
	string sD, sP;
	sD = MainMenuLoc_LastDecl();
	if (sD == "") return;
	sP = sD + ".camera.perspective";
	mmDecl.(sP) = fPerspective;
}

// > пресет погоды для последней объявленной локации
void MainMenuLoc_SetWeather(string sWeatherID)
{
	string sD, sP;
	sD = MainMenuLoc_LastDecl();
	if (sD == "") return;
	sP = sD + ".weather";
	mmDecl.(sP) = sWeatherID;
}

// > жители сцены для последней объявленной локации
void MainMenuLoc_SetPopulation()
{
	string sD, sP;
	sD = MainMenuLoc_LastDecl();
	if (sD == "") return;
	sP = sD + ".population";
	mmDecl.(sP) = true;
}

// > декоративный корабль на локаторе группы ships для последней объявленной локации
void MainMenuLoc_AddShip(int iBaseType, string sLocator, int iNation)
{
	aref st;
	string sD, sP, sS;
	int n;

	sD = MainMenuLoc_LastDecl();
	if (sD == "") return;

	sP = sD + ".ship";
	n = 0;
	if (CheckAttribute(&mmDecl, sP))
	{
		makearef(st, mmDecl.(sP));
		n = GetAttributesNum(st);
	}

	sS = sP + ".s" + n;
	sP = sS + ".type";	mmDecl.(sP) = iBaseType;
	sP = sS + ".locator";	mmDecl.(sP) = sLocator;
	sP = sS + ".nation";	mmDecl.(sP) = iNation;
}

// > Здесь перечисляются локации фона главного меню.
// > Модификаторы применяются к последней добавленной локации.
void MainMenuLoc_DeclareAll()
{
	DeleteAttribute(&mmDecl, "");
	mmDeclNum = 0;

	// > Список локаций фона главного меню
	MainMenuLoc_Add("Maracaibo_town", 130.88, 30.82, 79.54, 123.70, 29.85, 72.65);
}

// ==========================================================================================
//   Чтение объявлений
// ==========================================================================================

// > id локации по номеру объявления
string MainMenuLoc_Id(int d)
{
	string sD;
	if (d < 0 || d >= mmDeclNum) return "";
	sD = "d" + d;
	return mmDecl.(sD);
}

// > индекс в Locations[] по номеру объявления, -1 если такой локации нет
int MainMenuLoc_LocIndex(int d)
{
	string sID;
	sID = MainMenuLoc_Id(d);
	if (sID == "") return -1;
	return FindLocation(sID);
}

// > булев флаг объявления: включён только при явном true
bool MainMenuLoc_DeclFlag(int d, string sName)
{
	string sP;
	if (d < 0 || d >= mmDeclNum) return false;
	sP = "d" + d + "." + sName;
	if (!CheckAttribute(&mmDecl, sP)) return false;
	return mmDecl.(sP) == "1";
}

// > пресет погоды объявления, пустая строка если не задан
string MainMenuLoc_Weather(int d)
{
	string sP;
	if (d < 0 || d >= mmDeclNum) return "";
	sP = "d" + d + ".weather";
	if (!CheckAttribute(&mmDecl, sP)) return "";
	return mmDecl.(sP);
}

// > Годится ли объявление к показу. bVerbose - писать ли в лог причину отказа.
bool MainMenuLoc_DeclOk(int d, bool bVerbose)
{
	ref loc;
	string sID, sPath;
	int idx;

	sID = MainMenuLoc_Id(d);
	if (sID == "") return false;

	idx = FindLocation(sID);
	if (idx < 0)
	{
		if (bVerbose) Trace("MainMenuLoc: локации " + sID + " нет в Locations[], объявление пропущено");
		return false;
	}

	// > папку моделей проверяем здесь, чтобы решение про море принималось по живой локе
	loc = &Locations[idx];
	if (!CheckAttribute(loc, "filespath.models"))
	{
		if (bVerbose) Trace("MainMenuLoc: у локации " + sID + " нет filespath.models");
		return false;
	}

	sPath = "RESOURCE\MODELS\" + loc.filespath.models;
	if (!XI_CheckFolder(sPath))
	{
		if (bVerbose) Trace("MainMenuLoc: папки " + sPath + " нет на диске, локация " + sID + " пропущена");
		return false;
	}

	return true;
}

// > индекс локации для меню или -1, если объявленных нет
int MainMenuLoc_Choose()
{
	int i, num, pick;

	// > живая локация означает, что предыдущую сцену не снесли: второй сущности "location" в движке быть не должно, поэтому в таком случае показываем оригинальную сцену меню
	if (FindLoadedLocation() != -1)
	{
		Trace("MainMenuLoc: локация уже загружена, фон меню из локации пропущен");
		return -1;
	}

	MainMenuLoc_DeclareAll();

	num = 0;
	for (i = 0; i < mmDeclNum; i++)
	{
		if (MainMenuLoc_DeclOk(i, true)) num = num + 1;
	}

	if (num == 0)
	{
		// > что-то пошло не так, жалуемся
		Trace("MainMenuLoc: подходящих локаций нет (объявлено " + mmDeclNum + "), показываю штатную сцену меню");
		return -1;
	}

	pick = rand(num - 1);
	for (i = 0; i < mmDeclNum; i++)
	{
		if (!MainMenuLoc_DeclOk(i, false)) continue;
		if (pick == 0) return i;
		pick = pick - 1;
	}

	return -1;
}

// > нужно ли локации море
bool MainMenuLoc_NeedSea(int d)
{
	int idx;
	idx = MainMenuLoc_LocIndex(d);
	if (idx < 0) return true;
	if (!CheckAttribute(&Locations[idx], "environment.sea")) return false;
	return Locations[idx].environment.sea == "true";
}

// > имя набора пены для локации, пустое - пену не заводить
string MainMenuLoc_FoamID(int d)
{
	int idx;
	idx = MainMenuLoc_LocIndex(d);
	if (idx < 0) return "MainMenu";
	if (CheckAttribute(&Locations[idx], "notCreateFoam")) return "";
	return Locations[idx].id;
}

// > кадр камеры сцены меню
void MainMenuLoc_SetCamera(int d)
{
	string sD, sP;
	float fPerspective, fx, fy, fz, tx, ty, tz;

	sD = "d" + d;

	fPerspective = 0.0;	// > 0 - оставить угол обзора, заданный движком
	sP = sD + ".camera.perspective";
	if (CheckAttribute(&mmDecl, sP)) fPerspective = stf(mmDecl.(sP));

	sP = sD + ".camera.from.x";	fx = stf(mmDecl.(sP));
	sP = sD + ".camera.from.y";	fy = stf(mmDecl.(sP));
	sP = sD + ".camera.from.z";	fz = stf(mmDecl.(sP));
	sP = sD + ".camera.to.x";	tx = stf(mmDecl.(sP));
	sP = sD + ".camera.to.y";	ty = stf(mmDecl.(sP));
	sP = sD + ".camera.to.z";	tz = stf(mmDecl.(sP));

	SendMessage(&InterfaceBackScene, "lfffffff", MSG_BACKSCENE_SET_CAMERA_POS, fx, fy, fz, tx, ty, tz, fPerspective);
}

// > набор моделей на текущее время суток
bool MainMenuLoc_LoadModelSet(ref loc, string sSet)
{
	aref st, at;
	string sat;
	int i, num;

	if (!CheckAttribute(loc, sSet)) return true;

	makearef(st, loc.(sSet));
	num = GetAttributesNum(st);
	for (i = 0; i < num; i++)
	{
		at = GetAttributeN(st, i);
		sat = GetAttributeName(at);

		// > трава грузится своим сообщением, а не как модель
		if (sat == "grassPatch")
		{
			LocLoadGrass(loc, sSet + "." + sat);
			continue;
		}
		// > патчи ходьбы и прыжков в меню не нужны - персонажей нет; lights это не модель
		if (sat == "charactersPatch") continue;
		if (sat == "jumpPatch") continue;
		if (sat == "lights") continue;

		if (!LocLoadModel(loc, sSet + "." + sat, ""))
		{
			Trace("MainMenuLoc: не загрузилась модель " + sSet + "." + sat + " локации " + loc.id);
			return false;
		}
	}

	return true;
}

// > Сколько кого заселять, если хватит локаторов
#define MAINMENU_NPC_PATROL		8	// > патрульных солдат
#define MAINMENU_NPC_CITIZEN	10	// > горожан по группе goto
#define MAINMENU_NPC_COMMONER	3	// > из них простолюдинов-мужчин
#define MAINMENU_NPC_MERCHANT	4	// > лоточников
#define MAINMENU_NPC_DRINKER	4	// > пьяниц каждого вида

// > сколько локаторов в группе
int MainMenuLoc_LocatorCount(ref loc, string sGroup)
{
	aref st;
	string sPath;

	sPath = "locators." + sGroup;
	if (!CheckAttribute(loc, sPath)) return 0;
	makearef(st, loc.(sPath));
	return GetAttributesNum(st);
}

// > имя i-го локатора группы, пустая строка если такого нет
string MainMenuLoc_LocatorName(ref loc, string sGroup, int idx)
{
	aref st, at;
	string sPath;

	sPath = "locators." + sGroup;
	if (!CheckAttribute(loc, sPath)) return "";
	makearef(st, loc.(sPath));
	if (idx < 0 || idx >= GetAttributesNum(st)) return "";
	at = GetAttributeN(st, idx);
	return GetAttributeName(at);
}

// > Один фантом на локатор. sBehaviour задаёт, что он делает: ходит, патрулирует, стоит на посту, торгует с лотка, сидит или стоит выпивши.
bool MainMenuLoc_AddNPC(ref loc, string sType, int iSex, int iNation, string sGroup, string sLocator, string sBehaviour)
{
	int iChar;
	ref chr;

	if (sLocator == "") return false;

	// > -1 в последнем аргументе - фантом без срока жизни, без записи даты создания
	iChar = NPC_GeneratePhantomCharacter(sType, iNation, iSex, -1);
	if (iChar == -1)
	{
		Trace("MainMenuLoc: нет свободного слота под фантома " + sType);
		return false;
	}

	chr = &Characters[iChar];
	SetNPCModelUniq(chr, sType, iSex);
	chr.CityType = "citizen";
	chr.MainMenuNPC = true;		// > метка своих: по ней сцена их же и снесёт

	switch (sBehaviour)
	{
		case "citizen":		LAi_SetCitizenType(chr);	break;
		case "patrol":		LAi_SetPatrolType(chr);		break;
		case "guardian":	LAi_SetGuardianType(chr);	break;
		case "merchant":	LAi_SetMerchantType(chr);	break;
		case "drinksit":
			RemoveAllCharacterItems(chr, true);
			MakeUnpushable(chr, true);
			LAi_SetDrinkerSitTypeNoGroup(chr);
		break;
		case "drinkstay":
			RemoveAllCharacterItems(chr, true);
			MakeUnpushable(chr, true);
			LAi_SetDrinkerStayTypeNoGroup(chr);
		break;
	}

	ChangeCharacterAddressGroup(chr, loc.id, sGroup, sLocator);
	return true;
}

// > Фейковое заселение локи меню по флагу mainmenu.population
// >   день  - горожане обоих полов и простолюдины по goto (ходят),
// >           патруль по patrol (ходят),
// >           постовые по soldiers (стоят),
// >           лоточники по merchant (стоят),
// >           пьяницы по drinkersit и drinkerstay (сидят и стоят);
// >   ночь  - в городе бдит только патруль.
void MainMenuLoc_LoadPopulation(ref loc, string sSet)
{
	string sAttr, sLocator, sType;
	int iNation, i, num, iSex;
	bool bDay, bPirate, bOfficersWereOff;

	// > патч ходьбы
	sAttr = sSet + ".charactersPatch";
	if (!CheckAttribute(loc, sAttr))
	{
		Trace("MainMenuLoc: у локации " + loc.id + " нет патча ходьбы (" + sAttr + "), население отменено");
		return;
	}
	if (!SendMessage(loc, "ls", MSG_LOCATION_SET_CHRS_PATCH, loc.(sAttr)))
	{
		Trace("MainMenuLoc: не загрузился патч ходьбы локации " + loc.id + ", население отменено");
		return;
	}

	sAttr = sSet + ".jumpPatch";
	if (CheckAttribute(loc, sAttr)) SendMessage(loc, "ls", MSG_LOCATION_SET_JMP_PATCH, loc.(sAttr));

	iNation = PIRATE;
	if (CheckAttribute(loc, "fastreload"))
	{
		i = GetCityNation(loc.fastreload);
		if (i >= 0) iNation = i;
	}
	bPirate = iNation == PIRATE;
	bDay = Whr_IsDay() != 0;

	// > поисковики свободных локаторов внутри поведения ИИ стоят на этом ref: без него горожане никуда не пойдут
	loadedLocation = loc;

	// > Заводим слой ИИ: только обработчики и группы
	DeleteAttribute(&Lai_questdelays, "");

	bOfficersWereOff = CheckAttribute(loc, "DisableOfficers");
	if (!bOfficersWereOff) loc.DisableOfficers = true;
	LocAi_Init(loc);
	if (!bOfficersWereOff) DeleteAttribute(loc, "DisableOfficers");

	// > обнуляем журнал занятых моделей TODO > ref arrayNPCModelHow
	arrayNPCModelHow = 0;

	// > Патруль - единственные, кто есть и ночью
	num = MainMenuLoc_LocatorCount(loc, "patrol");
	if (num > MAINMENU_NPC_PATROL) num = MAINMENU_NPC_PATROL;
	if (bPirate) sType = "pirate";
	else         sType = "urban_sold";
	for (i = 0; i < num; i++)
	{
		MainMenuLoc_AddNPC(loc, sType, MAN, iNation, "patrol", MainMenuLoc_LocatorName(loc, "patrol", i), "patrol");
	}

	if (!bDay) return;	// > ночью на улицах только патруль

	// > Постовые: тип по имени локатора, как в штатном генераторе
	num = MainMenuLoc_LocatorCount(loc, "soldiers");
	for (i = 0; i < num; i++)
	{
		sLocator = MainMenuLoc_LocatorName(loc, "soldiers", i);
		// > мушкетёров и особые посты в меню не ставим > TODO check
		if (HasSubStr(sLocator, "mush")) continue;
		if (HasSubStr(sLocator, "special")) continue;

		if (HasSubStr(sLocator, "soldier"))
		{
			if (bPirate) sType = "mercenary";
			else         sType = "guard";
		}
		else
		{
			if (bPirate) sType = "pirate";
			else         sType = "urban_sold";
		}
		MainMenuLoc_AddNPC(loc, sType, MAN, iNation, "soldiers", sLocator, "guardian");
	}

	// > Лоточники: в штатном генераторе их вдвое меньше, чем локаторов группы - делаем так же
	num = MainMenuLoc_LocatorCount(loc, "merchant") / 2;
	if (num > MAINMENU_NPC_MERCHANT) num = MAINMENU_NPC_MERCHANT;
	for (i = 0; i < num; i++)
	{
		if (bPirate) iSex = MAN;
		else         iSex = rand(WOMAN);
		MainMenuLoc_AddNPC(loc, "hawker", iSex, iNation, "merchant", "merchant" + (i + 1), "merchant");
	}

	// > Горожане и простолюдины: по одному на локатор группы goto
	num = MainMenuLoc_LocatorCount(loc, "goto");
	if (num > MAINMENU_NPC_CITIZEN) num = MAINMENU_NPC_CITIZEN;
	for (i = 0; i < num; i++)
	{
		if (i < MAINMENU_NPC_COMMONER)
		{
			iSex = MAN;
			sType = "commoner";
		}
		else
		{
			// > в штатном генераторе женщин примерно 60 процентов
			if (rand(4) > 1) iSex = WOMAN;
			else             iSex = MAN;
			if (iSex == WOMAN && rand(9) == 0) sType = "oldwoman";
			else                               sType = "citizen";
		}
		MainMenuLoc_AddNPC(loc, sType, iSex, iNation, "goto", MainMenuLoc_LocatorName(loc, "goto", i), "citizen");
	}

	// > Пьяницы: сидящие и стоячие, по своим группам локаторов
	num = MainMenuLoc_LocatorCount(loc, "drinkersit");
	if (num > MAINMENU_NPC_DRINKER) num = MAINMENU_NPC_DRINKER;
	for (i = 1; i <= num; i++)
	{
		MainMenuLoc_AddNPC(loc, "drinker", MAN, iNation, "drinkersit", "drinkersit" + i, "drinksit");
	}

	num = MainMenuLoc_LocatorCount(loc, "drinkerstay");
	if (num > MAINMENU_NPC_DRINKER) num = MAINMENU_NPC_DRINKER;
	for (i = 1; i <= num; i++)
	{
		MainMenuLoc_AddNPC(loc, "drinker", MAN, iNation, "drinkerstay", "drinkerstay" + i, "drinkstay");
	}
}

// > Декоративные корабли на рейде задаются MainMenuLoc_AddShip
void MainMenuLoc_LoadShips(ref loc, int d)
{
	aref st, at, locator;
	string sShip, sPath, sAttr, sLocName;
	int i, num, idx, iBaseType, iGen;
	ref chr;

	sAttr = "d" + d + ".ship";
	if (!CheckAttribute(&mmDecl, sAttr))
	{
		Trace("MainMenuLoc: у локации " + loc.id + " ни один корабль не описан");
		return;
	}
	makearef(st, mmDecl.(sAttr));
	num = GetAttributesNum(st);
	if (num == 0)
	{
		Trace("MainMenuLoc: у локации " + loc.id + " ни один корабль не описан");
		return;
	}

	for (i = 0; i < num; i++)
	{
		if (locNumShips >= MAX_SHIPS_IN_LOCATION) break;

		at = GetAttributeN(st, i);
		sShip = "d" + d + ".ship." + GetAttributeName(at);

		if (!CheckAttribute(&mmDecl, sShip + ".type") || !CheckAttribute(&mmDecl, sShip + ".locator"))
		{
			Trace("MainMenuLoc: " + loc.id + ", корабль " + sShip + " - не задан type или locator");
			continue;
		}

		sAttr = sShip + ".locator";
		sLocName = mmDecl.(sAttr);
		sPath = "locators.ships." + sLocName;
		if (!CheckAttribute(loc, sPath))
		{
			Trace("MainMenuLoc: в локации " + loc.id + " нет локатора ships." + sLocName);
			continue;
		}
		makearef(locator, loc.(sPath));

		idx = FindFirstEmptyCharacter();
		if (idx == -1)
		{
			Trace("MainMenuLoc: нет свободного слота персонажа под корабль меню");
			break;
		}

		sAttr = sShip + ".type";
		iBaseType = sti(mmDecl.(sAttr));

		chr = &Characters[idx];
		InitCharacter(chr, idx);		// > штатный сброс слота, как в NPC_GeneratePhantomCharacter
		chr.id = "MainMenuShip" + idx;
		chr.MainMenuNPC = true;			// > метка своих: по ней сцена слот и освободит
		sAttr = sShip + ".nation";
		if (CheckAttribute(&mmDecl, sAttr)) chr.nation = sti(mmDecl.(sAttr));
		else                                chr.nation = PIRATE;
		chr.Flags.Pirate = rand(2);

		chr.Ship.Name = "";
		chr.Ship.Type = GenerateShip(iBaseType, 1);
		iGen = sti(chr.Ship.Type);
		if (iGen == SHIP_NOTUSED || !CheckAttribute(&RealShips[iGen], "name") || sti(RealShips[iGen].basetype) >= SHIP_TYPES_QUANTITY)
		{
			Trace("MainMenuLoc: негодный тип корабля " + iBaseType + " для " + loc.id + "." + sShip);
			InitCharacter(chr, idx);
			continue;
		}
		chr.Ship.Stopped = true;

		SetBaseShipData(chr);
		Ship_SetFantomData(chr);
		CharacterUpdateShipFromBaseShip(idx);
		Ship_SetTrackSettings(chr);
		chr.Features.GeraldSails = true;
		chr.TmpPerks = "";
		chr.TmpPerks.StormProfessional = 0;	// > перк читается в шторм, лучше иметь его нулём

		if (CreateEntity(&locShips[locNumShips], "ship") == 0)
		{
			Trace("MainMenuLoc: не создалась сущность корабля для " + loc.id + "." + sShip);
			break;
		}
		// > дальше штатный путь: позиция и разворот по локатору, свет, фонари и MSG_SHIP_CREATE
		SetShipToLocator(chr, locator, locNumShips);
		iShips[locNumShips] = idx;
		locNumShips++;
	}
}

// > Загрузка локации как фона меню: геометрия, свет, трава, партиклы.
// > Население и корабли подключаются в объявлении: MainMenuLoc_SetPopulation и MainMenuLoc_AddShip.
bool MainMenuLoc_Load(int d)
{
	bool bOk;
	string sSet;
	ref loc;
	int idx;

	idx = MainMenuLoc_LocIndex(d);
	if (idx < 0) return false;
	loc = &Locations[idx];

	sColCheckPath = "";	// > сброс кэша проверки *.col, как в штатном загрузчике

	if (CreateEntity(&loc, "location") == 0)
	{
		Trace("MainMenuLoc: не создалась сущность локации " + loc.id);
		return false;
	}

	SendMessage(loc, "ls", MSG_LOCATION_MODELSPATH, loc.filespath.models);
	SendMessage(loc, "lss", MSG_LOCATION_EX_MSG, "SetLightsFile", "lights_menu.ini");

	if (CheckAttribute(loc, "filespath.textures"))
	{
		SendMessage(loc, "ls", MSG_LOCATION_TEXTURESPATH, loc.filespath.textures);
	}
	// > пути запечённого освещения зависят от погоды, поэтому погода заводится раньше сцены
	SendMessage(loc, "ls", MSG_LOCATION_LIGHTPATH, GetLightingPath());
	SendMessage(loc, "ls", MSG_LOCATION_SHADOWPATH, GetLmLightingPath());

	bOk = MainMenuLoc_LoadModelSet(loc, "models.always");

	if (bOk && CheckAttribute(loc, "models.back"))
	{
		if (!LocLoadModel(loc, "models.back", Whr_GetInsideBack()))
		{
			Trace("MainMenuLoc: не загрузилась фоновая модель локации " + loc.id);
		}
	}

	if (Whr_IsDay() != 0) sSet = "models.day";
	else                  sSet = "models.night";
	if (bOk) bOk = MainMenuLoc_LoadModelSet(loc, sSet);

	if (!bOk)
	{
		DeleteClass(&loc);
		return false;
	}

	// > Модификаторы
	MainMenuLoc_SetPopulation();						// > население
	MainMenuLoc_AddShip(SHIP_LUGGER, "ship1", SPAIN);	// > корабль на приколе ( индекс_корабля_в_ships.h, "имя_локатора_в_локации_для_него", флаг_нации (0 - 4) )
	MainMenuLoc_SetWeather("");							// > схема погоды ("" - случайная)

	LocationSetGrass(loc);

	SendMessage(loc, "l", MSG_LOCATION_UPDATELOCATORS);
	LocationSetLights(loc);		// > уличные фонари локации, порядок после UPDATELOCATORS обязателен
	InitParticles();			// > после выхода из игры в меню сущность партиклов снесена общим DeleteEntities
	CreateParticles(loc);		// > водопады, фонтаны, дым - всё по локаторам, персонажи не нужны

	// > Население и корабли - по флагам.
	// > Порядок обязателен: LocAi_Init внутри населения чистит слоты локационных фантомов, из которых потом берутся владельцы кораблей
	locNumShips = 0;
	if (MainMenuLoc_DeclFlag(d, "population"))
	{
		MainMenuLoc_LoadPopulation(loc, sSet);
	}
	if (CheckAttribute(&mmDecl, "d" + d + ".ship"))
	{
		if (bMainMenuSeaCreated) MainMenuLoc_LoadShips(loc, d);
		else Trace("MainMenuLoc: у локации " + loc.id + " нет моря (environment.sea), корабли пропущены");
	}

	MainMenuLoc_SetCamera(d);

	InterfaceStates.mainmenuloadedloc = loc.id;
	return true;
}

// > Сцены меню больше нет: сбросить выбор, чтобы следующий заход выбрал локацию заново.
// > Сами сущности к этому моменту уже снесены общим DeleteEntities.
void MainMenuLoc_Forget()
{
	int i, idx;

	// > свои фантомы - и жители сцены, и владельцы декоративных кораблей - освобождаем сами, иначе их слоты заняты до ближайшего InitGame
	for (i = 0; i < TOTAL_CHARACTERS; i++)
	{
		if (!CheckAttribute(&Characters[i], "MainMenuNPC")) continue;
		InitCharacter(&Characters[i], i);
	}
	locNumShips = 0;

	if (!CheckAttribute(&InterfaceStates, "mainmenuloadedloc")) return;

	idx = FindLocation(InterfaceStates.mainmenuloadedloc);
	if (idx >= 0 && IsEntity(&Locations[idx])) DeleteClass(&Locations[idx]);
	DeleteAttribute(&InterfaceStates, "mainmenuloadedloc");
}

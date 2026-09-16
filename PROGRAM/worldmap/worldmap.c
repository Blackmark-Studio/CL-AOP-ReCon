/*
	Programm interface:

	Init world map in start
		void wdmInitWorldMap();
	Create world map object
		void wdmCreateMap();
	Release world map object
		void wdmReleaseMap();


	SPI (Script program interface):
	Получение данных от карты
	(const) поля только для прочтения
	(var) поля только для записи и прочтения, запись в них приводит к обновления остальных полей,
	      принадлежащих этой группе

	Шторма
	worldMap.storm.num - текущие количество штормов в карте (const)
	worldMap.storm.cur - индекс текущего шторма 0..num-1, надо перезаписывать для обновления полей (var)
	worldMap.storm.x - позиция шторма по x (const)
	worldMap.storm.z - позиция шторма по z (const)
	worldMap.storm.time - оставшееся время жизни в секундах (const)

	Кораблики событий
	worldMap.encounter.num - текущие количество корабликов в карте (const)
	worldMap.encounter.cur - индекс текущего кораблика в карте (var)
	worldMap.encounter.x - позиция кораблика по x (const)
	worldMap.encounter.z - позиция кораблика по z (const)
	worldMap.encounter.time - оставшееся время жизни в секундах (const)
	worldMap.encounter.type - тип события, обозначаемый этим корабликом (define в таблице типов энкоунтеров)
	worldMap.encounter.attack - индекс кораблика, который атакуем (стоя на месте)
	worldMap.encounter.id - название описания энкоунтера: worldMap.encounters.(worldMap.encounter.id)...

	Разная информация
	worldMap.info.playerInStorm - если 1 то плеер находиться в шторме
	worldMap.info.updateinfo - апдейт информации


	//Внутреняя информация - !!!Осторожно, ни каких проверок!!!
	worldMap.enemyshipViewDistMin;		//Растояние на котором корабль начинает исчезать
	worldMap.enemyshipViewDistMax;		//Растояние на котором корабль исчезает полностью
	worldMap.enemyshipDistKill;			//Расстояние на котором убиваем корабль
	worldMap.enemyshipBrnDistMin;		//Минимальное растояние на котором рожается корабль
	worldMap.enemyshipBrnDistMax;		//Максимальное растояние на котором рожается корабль

	worldMap.stormViewDistMin;			//Растояние на котором шторм начинает исчезать
	worldMap.stormViewDistMax;			//Растояние на котором шторм исчезает полностью
	worldMap.stormDistKill;				//Расстояние на котором убиваем шторм
	worldMap.stormBrnDistMin;			//Минимальное растояние на котором рожается шторм
	worldMap.stormBrnDistMax;			//Максимальное растояние на котором рожается шторм

*/

#include "worldmap\worldmap_globals.c"
#include "worldmap\worldmap_events.c"
#include "worldmap\worldmap_reload.c"
#include "worldmap\worldmap_encgen.c"
#include "worldmap\worldmap_coords.c"


//=========================================================================================


#event_handler("WorldMap_EncounterCreate", "wdmEvent_EncounterCreate");
#event_handler("WorldMap_PlayerInStorm", "wdmEvent_PlayerInStorm");
#event_handler("WorldMap_ShipEncounter", "wdmEvent_ShipEncounter");
#event_handler("WorldMap_UpdateDate", "wdmEvent_UpdateDate");
#event_handler("WorldMap_ShipRadiusUpdate", "wdmEvent_ShipRadiusUpdate");
#event_handler("ExitFromWorldMap", "wdmReloadToSea");
//#event_handler("NextDay", "wdmNextDayUpdate");

#event_handler("EventTimeUpdate", "wdmTimeUpdate");


//=========================================================================================
// Programm interface
//=========================================================================================


void wdmCreateMap(float x, float z, float ay)
{
	//Координаты острова с которого уплыли
	float zeroX = MakeFloat(worldMap.zeroX);
	float zeroZ = MakeFloat(worldMap.zeroZ);
	//Находим новые координаты на карте (масштаб острова - через общий GetSeaToMapScale)
	int scale = GetSeaToMapScale();
	worldMap.playerShipX = (x/scale) + zeroX;
	worldMap.playerShipZ = (z/scale) + zeroZ;
	worldMap.playerShipAY = ay;
	worldMap.playerShipModel = wdmGetPlayerShipModelName();
//	worldMap.playerShipActionRadius = wdmGetPlayerShipActionRadius();
//	worldMap.enemyShipActionRadius = wdmGetEnemyShipActionRadius();
//	worldMap.stormShipActionRadius = wdmGetStormShipActionRadius();
//	trace(" X :" + x + " Z :" + z + " scale :" + scale + " ZeroX :" + zeroX + " ZeroZ:" + zeroZ + " WDMShipX:"+worldMap.playerShipX + " WDMShipZ:" + worldMap.playerShipZ + " ShipX:" + ShipX + " ShipZ:" + ShipZ);
	//Загружаем карту
	wdmCreateWorldMap();
}

void wdmTimeUpdate()
{
	//QuestsTimeCheck();
	// boal -->
	QuestsCheck();

	if (isEntity(&worldMap) && worldMap.isLoaded == "true")
	{
		PostEvent("EventTimeUpdate", 5000);
	}
	// boal <--
}

// метка по координатам (ле Баск)
int AoP_MapMarkAnimTick = 0;

// метка по координатам (ле Баск)
void AoP_AddMapMarkByCoords(string sMarkID, float x, float z)
{
	if (sMarkID == "") return;

	TEV.AoPCoordMapMarks.(sMarkID).x = x;
	TEV.AoPCoordMapMarks.(sMarkID).z = z;

	if (IsEntity(&worldMap)) AoP_UpdateMapMarksByCoords();
}

// метка по координатам (ле Баск)
void AoP_RemoveMapMarkByCoords(string sMarkID)
{
	if (sMarkID == "") return;
	if (CheckAttribute(&TEV, "AoPCoordMapMarks." + sMarkID)) DeleteAttribute(&TEV, "AoPCoordMapMarks." + sMarkID);

	if (IsEntity(&worldMap)) AoP_UpdateMapMarksByCoords();
}

// метка по координатам (ле Баск)
void AoP_UpdateMapMarksByCoords()
{
	if (!IsEntity(&worldMap)) return;

	int iLine = 0;
	float fPlayerX = stf(worldMap.playerShipX);
	float fPlayerZ = stf(worldMap.playerShipZ);

	// метка по координатам (ле Баск)
	AoP_MapMarkAnimTick++;
	if (AoP_MapMarkAnimTick >= 64) AoP_MapMarkAnimTick = 0;
	int iFrame = AoP_MapMarkAnimTick / 8;
	string sFrame = "" + iFrame;

	if (CheckAttribute(&TEV, "AoPCoordMapMarks"))
	{
		aref arMarks;
		makearef(arMarks, TEV.AoPCoordMapMarks);
		int iMarksNum = GetAttributesNum(arMarks);

		for (int i = 0; i < iMarksNum; i++)
		{
			if (iLine >= 8) break;

			aref arMark = GetAttributeN(arMarks, i);
			if (!CheckAttribute(arMark, "x")) continue;
			if (!CheckAttribute(arMark, "z")) continue;

			float fOffX = stf(arMark.x) - fPlayerX;
			float fOffZ = stf(arMark.z) - fPlayerZ;

			// метка по координатам (ле Баск)
			wdmSetShipText("", iLine, sFrame, "AOP_MAP_QUESTMARK", 1.0, argb(255, 255, 255, 255),
				0.0, 0.0, fOffX, 6.0, fOffZ, 0, 0);

			iLine++;
		}
	}

	for (int n = iLine; n < 8; n++)
	{
		wdmSetShipText("", n, "", "AOP_MAP_QUESTMARK", 1.0, argb(255, 255, 255, 255),
			0.0, 0.0, 0.0, 0.0, 0.0, 0, 0);
	}
}

void wdmCreateWorldMap()
{
	wdmLockReload = false;
	bWMEncounterCheck = true;
	//Уберём все сообщения для игрока
	ClearAllLogStrings();
	//
	ReloadProgressStart();
	wdmCreateWindInterface();
	//Удалим все устаревшие энкаунтеры
	wdmRemoveOldEncounters();
//	Trace("Save check ---------------================--------------")
//	DumpAttributes(&worldMap);
//	Trace("Save check ###########----================--------------")
	worldMap.playerInStorm = "0";
	//Сбросим счётчики генерации энкоунтеров
	wdmReset();
	// Ставим квест-метки
	SetMapQuestMarks();
	//Создаём карту
	CreateEntity(&worldMap,"worldmap");
	worldMap.isLoaded = "true";
	AoP_KeysLagoonPunitiveEnsureEncounter();
	//Обновляем параметры
	worldMap.update = "";
	//Фейдер
	CreateEntity(&wdm_fader, "fader");
	if (IsEntity(&wdm_fader) == 0) Trace("Fader not created!!!");	
	float fadeInTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_IN, fadeInTime, true);
	//SendMessage(&wdm_fader, "ls", FADER_PICTURE0, "interfaces\card_desk.tga");
	SendMessage(&wdm_fader, "ls", FADER_PICTURE0, GetLoadingImage_Sea());
	//Установим звуковую схему
	SetSchemeForMap();
	//Сообщим, что загрузились
	PostEvent("EventWorldMapInit", 830); //fix boal
	ReloadProgressEnd();
	PostEvent("EventTimeUpdate", 1000);
	// Ставим MapCoordinateQuest если есть
	if (sCurCoordinateQuest != "")
	{
		SetMapCoordinateQuest(sCurCoordinateQuest);
	}
	//Создаём накопившиеся квестовые энкоунтеры
	worldMap.addQuestEncounters = "updateQuest";
	wdmSetNationFlag(sti(pchar.nation));
	InitWmInterface();
	// обновляем радиусы кораблей
	TEV.WDM_ShipRadiusUpdate = true;
	wdmEvent_ShipRadiusUpdate();
	// ставим обработчик
	SetEventHandler("frame", "CheckMapCoordinateQuest", 0);
	// > накладывание эффектов на кораблики
	wdmApplyAllShipFX();
}

// Hokkins: инициализируем все текстурки и тексты на глобалке в зависимости от скейлинга -->
void wdmCreateWindInterface()
{
	float fHtRatio = GetScreenScale();
	
	worldMap.date.monthnames.m01 = XI_ConvertString("target_month_1");
	worldMap.date.monthnames.m02 = XI_ConvertString("target_month_2");
	worldMap.date.monthnames.m03 = XI_ConvertString("target_month_3");
	worldMap.date.monthnames.m04 = XI_ConvertString("target_month_4");
	worldMap.date.monthnames.m05 = XI_ConvertString("target_month_5");
	worldMap.date.monthnames.m06 = XI_ConvertString("target_month_6");
	worldMap.date.monthnames.m07 = XI_ConvertString("target_month_7");
	worldMap.date.monthnames.m08 = XI_ConvertString("target_month_8");
	worldMap.date.monthnames.m09 = XI_ConvertString("target_month_9");
	worldMap.date.monthnames.m10 = XI_ConvertString("target_month_10");
	worldMap.date.monthnames.m11 = XI_ConvertString("target_month_11");
	worldMap.date.monthnames.m12 = XI_ConvertString("target_month_12");
	
	worldMap.sky.texture = "Interfaces/Worldmap/sky.tga";
	worldMap.sky.maskTexture = "Interfaces/Worldmap/sky_mask.tga";
	worldMap.sky.leftPos = sti(showWindow.right) - RecalculateHIcon(makeint(214 * fHtRatio));
	worldMap.sky.topPos = sti(showWindow.top) + RecalculateVIcon(makeint(7 * fHtRatio));
	worldMap.sky.width = 195 * fHtRatio;
	worldMap.sky.height = 195 * fHtRatio;
	worldMap.sky.color = argb(255, 255, 255, 255);
	
	worldMap.windPointer.texture = "Interfaces/Worldmap/wind_pointer.tga";
	worldMap.windPointer.leftPos = sti(showWindow.right) - RecalculateHIcon(makeint(135 * fHtRatio));
	worldMap.windPointer.topPos = sti(showWindow.top) + RecalculateVIcon(makeint(35 * fHtRatio));
	worldMap.windPointer.width = 37 * fHtRatio;
	worldMap.windPointer.height = 145 * fHtRatio;
	worldMap.windPointer.color = argb(255, 255, 255, 255);
	
	worldMap.windBar.texture = "Interfaces/Worldmap/bar.tga";
	worldMap.windBar.maskTexture = "Interfaces/Worldmap/bar_mask.tga";
	worldMap.windBar.leftPos = sti(showWindow.right) - RecalculateHIcon(makeint(194 * fHtRatio));
	worldMap.windBar.topPos = sti(showWindow.top) + RecalculateVIcon(makeint(112 * fHtRatio));
	worldMap.windBar.width = 155 * fHtRatio;
	worldMap.windBar.height = 155 * fHtRatio;
	worldMap.windBar.color = argb(255, 255, 255, 255);
	
	worldMap.frame.texture = "Interfaces/Worldmap/back.tga";
	worldMap.frame.leftPos = sti(showWindow.right) - RecalculateHIcon(makeint(214 * fHtRatio));
	worldMap.frame.topPos = sti(showWindow.top) + RecalculateVIcon(makeint(7 * fHtRatio));
	worldMap.frame.width = 195 * fHtRatio;
	worldMap.frame.height = 390 * fHtRatio;
	worldMap.frame.color = argb(255, 255, 255, 255);

	worldMap.dateText.font = "interface_normal";
	worldMap.dateText.scale = 1.2 * fHtRatio;
	worldMap.dateText.color = argb(255, 255, 255, 255);
	worldMap.dateText.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(115 * fHtRatio));
	worldMap.dateText.pos.y = RecalculateVIcon(makeint(210 * fHtRatio));
	
	worldMap.morale.texture = "Interfaces/Worldmap/morale.tga";
	worldMap.morale.barTexture = "Interfaces/Worldmap/morale_bar.tga";
	worldMap.morale.maskTexture = "Interfaces/Worldmap/morale_mask.tga";
	worldMap.morale.leftPos = sti(showWindow.right) - RecalculateHIcon(makeint(196 * fHtRatio));
	worldMap.morale.topPos = sti(showWindow.top) + RecalculateVIcon(makeint(240 * fHtRatio));
	worldMap.morale.width = 156 * fHtRatio;
	worldMap.morale.height = 156 * fHtRatio;
	worldMap.morale.color = argb(255, 255, 255, 255);
	
	worldMap.foodText.font = "interface_normal";
	worldMap.foodText.scale = 1.2 * fHtRatio;
	worldMap.foodText.color = argb(255, 255, 255, 255);
	worldMap.foodText.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(150 * fHtRatio));
	worldMap.foodText.pos.y = RecalculateVIcon(makeint(362 * fHtRatio));
	
	worldMap.rumText.font = "interface_normal";
	worldMap.rumText.scale = 1.2 * fHtRatio;
	worldMap.rumText.color = argb(255, 255, 255, 255);
	worldMap.rumText.pos.x = sti(showWindow.right) - RecalculateHIcon(makeint(84 * fHtRatio));
	worldMap.rumText.pos.y = RecalculateVIcon(makeint(362 * fHtRatio));
	
	worldMap.nationFlag.texture = "Interfaces/Worldmap/WorldMapEnsigns.tga";
	worldMap.nationFlag.leftPos = sti(showWindow.right) - RecalculateHIcon(makeint(147 * fHtRatio));
	worldMap.nationFlag.topPos = sti(showWindow.top) + RecalculateVIcon(makeint(414 * fHtRatio));
	worldMap.nationFlag.width = 64 * fHtRatio;
	worldMap.nationFlag.height = 64 * fHtRatio;

	//fix
	worldMap.coord.texture = "Interfaces/Worldmap/coord.tga";

	worldMap.resizeRatio = fHtRatio;
}
// Hokkins: <--

void wdmLoadSavedMap()
{
	//Загружаем карту
	wdmCreateWorldMap();
}

void wdmRemoveOldEncounters()
{
	//Пометим протухшие энкаунтеры
	wdmMarkDeleteEncounters();
	//Собираем всех желающих
	aref encs;
	makearef(encs, worldMap.encounters);
	int num = GetAttributesNum(encs);
	object forDelete;
	string attr, encID;
	int i;
	int count = 0;
	for(i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "needDelete") != 0)
		{
			attr = "del" + count;
			forDelete.(attr) = GetAttributeName(enc);
			count = count + 1;
		}
	}
	for(i = 0; i < count; i++)
	{
		attr = "del" + i;
		encID = "encounters." + forDelete.(attr);
		DeleteAttribute(&worldMap, encID);
	}
}

float wdmGetDays(int year, int month, int day, int hour)
{
	Restrictor(&year, 0, 3000);
	// > Точный день с учётом високосных лет
	float days = makefloat(DateToEpochDays(year, month, day)) + (hour / 24.0);
	return days;
}

void wdmSetNationFlag(int iNation)
{
	int Nation;
	if (isEntity(&worldMap))
	{
		switch (iNation)
		{
			case ENGLAND 	: Nation = 1; break;			
			case FRANCE 	: Nation = 2; break;
			case SPAIN		: Nation = 3; break;
			case HOLLAND	: Nation = 0; break;
			case PIRATE		: Nation = 4; break;
		}
		SendMessage(&worldMap, "ll", MSG_WORLDMAP_SET_NATION_FLAG, Nation);
	}
}

void wdmMarkDeleteEncounters()
{
	//Получаем дату
	int year = sti(worldMap.date.year);
	int month = sti(worldMap.date.month);
	int day = sti(worldMap.date.day);
	int hour = sti(worldMap.date.hour);
	float days = wdmGetDays(year, month, day, hour);
	int encYear, encMonth, encDay, encHour;
	//Перебираем все энкоунтеры, помечая на удаление
	aref encs;
	makearef(encs, worldMap.encounters);
	int num = GetAttributesNum(encs);
	for(int i = 0; i < num; i++)
	{
		aref enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "Quest") != 0)
		{
			continue;
		}
		bool deleteMe = false;
		if(CheckAttribute(enc, "year") != 0)
		{
			encYear = sti(enc.year);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "month") != 0)
		{
			encMonth = sti(enc.month);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "day") != 0)
		{
			encDay = sti(enc.day);
		}else{
			deleteMe = true;
		}
		if(CheckAttribute(enc, "hour") != 0)
		{
			encHour = sti(enc.hour);
		}else{
			deleteMe = true;
		}
		if(deleteMe != true)
		{
			float deltaDays = wdmGetDays(encYear, encMonth, encDay, encHour) - days;
			if(deltaDays < 0)
			{
				deltaDays = -deltaDays;
			}
			if(deltaDays > 1.0)
			{
				deleteMe = true;
			}
		}
		if(deleteMe != false)
		{
			enc.needDelete = "Time delete";
		}
	}
}

string wdmGetPlayerShipModelName()
{
	string defaultModelName = "Ship";
	string resModelName = defaultModelName;
	int shipType = GetCharacterShipType(pchar);
	if (shipType == SHIP_NOTUSED)
	{
		return defaultModelName;
	}
	
	switch(sti(RealShips[shipType].basetype))
	{
		case SHIP_SOLEYRU: resModelName = "SoleyRuShip"; break;
		case SHIP_SANTISIMA: resModelName = "SantisimaShip"; break;
		case SHIP_BRIGQEEN: resModelName = "BrigantineShip"; break;
		case SHIP_BRIGSW: resModelName = "BrigSWShip"; break;
		case SHIP_XebekVML: resModelName = "XebekShip"; break;
		case SHIP_CORVETTE_QUEST: resModelName = "CorvetteShipOLD"; break;
		case SHIP_CORVETTE_QUEST_O: resModelName = "CorvetteShip"; break;
		case SHIP_ARABELLA: resModelName = "ArabellaShip"; break;
		case SHIP_FRIGATEQUEEN: resModelName = "QueenShip"; break;
		case SHIP_FLYINGDUTCHMAN: resModelName = "FlyingDutchmanShip"; break;
		case SHIP_FLYINGDUTCHMAN_O: resModelName = "FlyingDutchmanShipNew"; break;
		case SHIP_POLACRE_QUEST: resModelName = "PolacreShip"; break;
		case SHIP_VEINARD: resModelName = "VeinardShip"; break;
		case SHIP_FRIGATE_M: resModelName = "FrigateMShip"; break;
		case SHIP_LUGGERQUEST: resModelName = "LuggerQuestShip"; break;
	}
	
	if (FindWorldmapPlayerShipModelFile(resModelName))
	{
		return resModelName;
	}
	
	return defaultModelName;
}

bool FindWorldmapPlayerShipModelFile(string modelFileName)
{
	object objFileFinder;
	aref arList;
	int iNumFiles = 0;
	
	string worldmapDir = "resource\MODELS\WorldMap\";
	objFileFinder.dir = worldmapDir;
	objFileFinder.mask = modelFileName + ".gm";
	CreateEntity(&objFileFinder, "FINDFILESINTODIRECTORY");
	makearef(arList, objFileFinder.filelist);
	iNumFiles = GetAttributesNum(arList);	
	DeleteClass(&objFileFinder);
	
	if (iNumFiles <= 0)
	{
		Trace("FindWorldmapPlayerShipModelFile >> Can't find geometry file: " + worldmapDir + modelFileName + ".gm");
		return false;
	}
	
	return true;
}

// > ВСЕ РЕСУРСЫ НУЖНО КЛАСТЬ В:
// "RESOURCE\MODELS\WorldMap\<тут_или_далее_в_любой_папке>" - 3d-модели "*.gm"
// "RESOURCE\Textures\WorldMap\<тут_или_далее_в_любой_папке>" - текстуры

// > Спрайт (camera-facing billboard) на любом кораблике на глобалке
// > shipName = "" - игрок; иначе имя энкаунтера (worldMap.encounter.id)
// > size - полуразмер квада; yOffset - высота над корабликом; color - ARGB
// > пустой texturePath снимает спрайт
void wdmSetShipSprite(string shipName, string texturePath, float size, float yOffset, int color)
{
	if (IsEntity(&worldMap))
		SendMessage(&worldMap, "lssffl", MSG_WORLDMAP_SHIP_ATTACH_SPRITE, shipName, texturePath, size, yOffset, color);
}

// > Доп. 3d-модель ("*.gm" из RESOURCE\MODELS\WorldMap) на любом кораблике на глобалке, движется за корпусом
// > shipName = "" - игрок; иначе имя энкаунтера (worldMap.encounter.id)
// > gmName - имя "*.gm" (без расширения)
// > offX/offY/offZ - смещение в локале корабля
// > angleY - доп. поворот модели вокруг вертикали (радианы)
// > пустой gmName убирает доп. 3d-модель
void wdmSetShipModel(string shipName, string gmName, float offX, float offY, float offZ, float angleY)
{
	if (IsEntity(&worldMap))
		SendMessage(&worldMap, "lssffff", MSG_WORLDMAP_SHIP_ATTACH_MODEL, shipName, gmName, offX, offY, offZ, angleY);
}

// > Партикл-эффект (billboard-эмиттер, "клон шторма") на любом кораблике на глобалке, следует за моделькой
// > shipName - "" - игрок; иначе имя энкаунтера (worldMap.encounter.id)
// > size - базовый размер частицы
// > yOffset - высота эмиттера над корабликом
// > color - ARGB (альфа = базовая непрозрачность, частицы гаснут по времени жизни)
// > пустой texturePath снимает эффект
void wdmSetShipParticle(string shipName, string texturePath, float size, float yOffset, int color)
{
	if (IsEntity(&worldMap))
		SendMessage(&worldMap, "lssffl", MSG_WORLDMAP_SHIP_ATTACH_PARTICLE, shipName, texturePath, size, yOffset, color);
}

// > Анимация вращения прикреплённого спрайта на любом кораблике.
// mode: 0 = выкл, 1 = зациклено (бесконечно), 2 = периодически (крутится 'duration' секунд, затем останавливается).
// timeBase: 0 = реальные секунды (скорость не зависит от скорости течения игрового времени), 1 = игровые секунды (зависит).
// speed - радиан/сек.
// Повторный вызов с mode = 2 перезапускает периодический прогон.
void wdmSetShipSpriteRotate(string shipName, int mode, float speed, float duration, int timeBase)
{
	if (IsEntity(&worldMap))
		SendMessage(&worldMap, "lslffl", MSG_WORLDMAP_SHIP_SPRITE_ROTATE, shipName, mode, speed, duration, timeBase);
}

// > Анимация вращения прикреплённой модели на любом кораблике.
// shipName = "" - игрок; иначе имя энкаунтера (worldMap.encounter.id).
// parts: 1 = A (вращение самой модели вокруг оси axisA), 2 = B (прокрутка UV-текстуры), 3 = A и B одновременно.
// mode: 0 = выкл, 1 = зациклено, 2 = периодически (duration секунд, затем стоп).
// timeBase: 0 = реальные секунды, 1 = игровые секунды. speedA/speedB - радиан/сек. axisA: 0 = X, 1 = Y, 2 = Z.
void wdmSetShipModelRotate(string shipName, int parts, int mode, int timeBase, float duration, float speedA, int axisA, float speedB)
{
	if (IsEntity(&worldMap))
		SendMessage(&worldMap, "lslllfflf", MSG_WORLDMAP_SHIP_MODEL_ROTATE, shipName, parts, mode, timeBase, duration, speedA, axisA, speedB);
}

// > Текст над любым корабликом на глобальной карте. До 8 строк (lineIndex 0-7), каждая со своими параметрами.
// shipName = "" - игрок; иначе имя энкаунтера (worldMap.encounter.id).
// lineIndex - номер строки 0-7. Пустой text удаляет эту строку (когда строк не осталось - объект сам исчезает).
// fontName - имя шрифта (как в fonts.ini); size - масштаб шрифта; color - ARGB.
// fadeOut/fadeIn - мерцание в реальных секундах (0,0 = без мерцания; не ускоряется от изменения скорости игрового времени).
// offX/offY/offZ - смещение точки привязки в мире относительно кораблика.
// mode: 0 = 2D-надпись (постоянный экранный размер, всегда читаемо), 1 = 3D-текст (масштаб по перспективе, мельчает с расстоянием).
// shipFade - как строка реагирует на затухание самого кораблика:
//   0 = плавно гаснет и проявляется вместе с корабликом;
//   1 = без плавности: пока кораблик виден - чёткая, как только он ушёл за предел видимости (значение worldMap.enemyshipViewDistMax) - пропадает сразу, и так же сразу возвращается чёткой, когда кораблик снова попадает в зону видимости.
void wdmSetShipText(string shipName, int lineIndex, string text, string fontName, float size, int color, float fadeOut, float fadeIn, float offX, float offY, float offZ, int mode, int shipFade)
{
	if (IsEntity(&worldMap))
		SendMessage(&worldMap, "lslssflfffffll", MSG_WORLDMAP_SHIP_SET_TEXT, shipName, lineIndex, text, fontName, size, color, fadeOut, fadeIn, offX, offY, offZ, mode, shipFade);
}

// Радиус взаимодействия игрока с энкаунтерами
float wdmGetPlayerShipActionRadius()
{
	int perceptionValue = GetCharacterSPECIAL(pchar, "Perception");
	return GetPlayerShipActionRadiusByPerception(perceptionValue);
}

// Радиус взаимодействия враждебных энкаунтеров с игроком
float wdmGetEnemyShipActionRadius()
{
	return 20.0;
}

// Радиус взаимодействия игрока с штормами
float wdmGetStormShipActionRadius()
{
	int perceptionValue = (10 + 3) - GetCharacterSPECIAL(pchar, "Perception"); // (max + min) - Perception
	return GetPlayerShipActionRadiusByPerception(perceptionValue);
}

float GetPlayerShipActionRadiusByPerception(int perceptionValue)
{
	Restrictor(&perceptionValue, 3, 10);
	return 0.5 * perceptionValue + 18.0;
}
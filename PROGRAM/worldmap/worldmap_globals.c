#define WDM_MAP_TO_SEA_SCALE				50
#define WDM_MAP_ENCOUNTERS_TO_SEA_SCALE		25	// boal	18.02.06 80 - это много, нужно обязательнй бой, когда догнали	// 80 VANO был тут, чисто для того чтобы корабли ближе появлялись в море, а то они на горизонте тусуются

#define WDM_NONE_ISLAND				""

#define WDM_ETYPE_MERCHANT	0
#define WDM_ETYPE_FOLLOW	1
#define WDM_ETYPE_WARRING	2
#define WDM_ETYPE_SPECIAL	3


object worldMap;

//=========================================================================================
//Quest functions  - Квестовые энкаунтеры. Все эвенты приходят с параметром characterID
//=========================================================================================

//военный (догоняющий). TimeOut в днях, если -1, то неиспользуеться.
//торговец - в случае успешного достижения пункта назначения придёт эвент Map_TraderSucces
void Map_CreateTrader(string beginlocator, string endLocator, string characterID, int TimeOut)  //boal
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID); //boal fix
	encField.type = "trader";
	encField.characterID = characterID;
	encField.beginlocator = beginlocator;
	encField.endLocator = endLocator;
	encField.TimeOut = TimeOut; //boal
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}

// boal 04/10/06
//военный (догоняющий). TimeOut в днях, если -1, то неиспользуеться.
//торговец - в случае успешного достижения пункта назначения придёт эвент Map_TraderSucces
void Map_CreateTraderXZ(float x1, float z1, float x2, float z2, string characterID, int TimeOut)  
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID);
	encField.type = "trader";
	encField.XZGoto = true;
	encField.characterID = characterID;
	encField.x1 = x1;
	encField.z1 = z1;
	encField.x2 = x2;
	encField.z2 = z2;
	encField.TimeOut = TimeOut; //boal
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}

//военный (догоняющий). TimeOut в днях, если -1, то неиспользуеться.
//При таймауте придёт эвент Map_WarriorEnd
void Map_CreateWarrior(string beginLocator, string characterID, int TimeOut)
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID);
	encField.type = "warrior";
	encField.characterID = characterID;
	encField.beginlocator = beginlocator;
	encField.TimeOut = TimeOut;
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}

//Jason Квестовый скоростной энкаунтер. Уйти от него невозможно.
void Map_CreateCoolWarrior(string beginLocator, string characterID, int TimeOut)
{
	aref encField = wdmFindOrCreateQuestEncounter(characterID);
	encField.type = "coolwarrior";
	encField.characterID = characterID;
	encField.beginlocator = beginlocator;
	encField.TimeOut = TimeOut;
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}

//воюющий. TimeOut в днях. При таймауте придёт эвент Map_BattleEnd
//если же игрок вошел в этот энкаунтер до истечения таймаута удалиться энкоунтер из карты
void Map_CreateBattle(string characterID, int iEnemyNation, int TimeOut)
{
    trace("!!!battle " + characterID);
	aref encField = wdmFindOrCreateQuestEncounter(characterID);
	encField.type = "battle";
	encField.characterID = characterID;
	encField.iEnemyNation = iEnemyNation;
	encField.TimeOut = TimeOut;
	worldMap.addQuestEncounters = "updateQuest";
	if(!CheckAttribute(pchar, "worldmap.shipcounter"))
	{
		pchar.worldmap.shipcounter = 0;
	}
	pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) + 1;
}

//Удалить квестового энкоунтера
void Map_ReleaseQuestEncounter(string characterID)
{
	//Просматриваем список создаваемых
	aref encs, enc;
	string aname;
	makearef(encs, worldMap.addQuestEncounters);
	int num = GetAttributesNum(encs);
	int i;
	for(i = 0; i < num; i++)
	{
		enc = GetAttributeN(encs, i);
		if(CheckAttribute(enc, "characterID") && enc.characterID == characterID)
		{
			DeleteAttribute(enc, "characterID");
		}
	}
	//Просматриваем список созданных
	makearef(encs, worldMap.encounters);
	num = GetAttributesNum(encs);
	for(i = num-1; i >= 0; i--)
	{
		enc = GetAttributeN(encs, i);
		if(!CheckAttribute(enc, "quest.chrID")) continue;
		if(enc.quest.chrID == characterID)
        {
			wdmDeleteLoginEncounter(GetAttributeName(enc));
        }
	}

	worldMap.deleteUpdate = "";
}

bool AoP_KeysLagoonPunitiveCaptainID(string sID)
{
	return HasSubStr(sID, "Keys_lagoon_Punitive_Cap_");
}

bool AoP_KeysLagoonPunitiveCaptainAlive(string sID)
{
	int iChar = GetCharacterIndex(sID);
	if (iChar < 1) return false;
	if (LAi_IsDead(&characters[iChar])) return false;
	if (sti(characters[iChar].Ship.Type) == SHIP_NOTUSED) return false;
	return true;
}

bool AoP_KeysLagoonPunitiveEncounterExists()
{
	aref encs, enc;
	string sID;
	int i, num;

	if (CheckAttribute(&worldMap, "addQuestEncounters"))
	{
		makearef(encs, worldMap.addQuestEncounters);
		num = GetAttributesNum(encs);
		for (i = 0; i < num; i++)
		{
			enc = GetAttributeN(encs, i);
			if (!CheckAttribute(enc, "characterID")) continue;
			sID = enc.characterID;
			if (AoP_KeysLagoonPunitiveCaptainID(sID) && AoP_KeysLagoonPunitiveCaptainAlive(sID)) return true;
		}
	}

	if (CheckAttribute(&worldMap, "encounters"))
	{
		makearef(encs, worldMap.encounters);
		num = GetAttributesNum(encs);
		for (i = 0; i < num; i++)
		{
			enc = GetAttributeN(encs, i);
			if (!CheckAttribute(enc, "quest.chrID")) continue;
			sID = enc.quest.chrID;
			if (AoP_KeysLagoonPunitiveCaptainID(sID) && AoP_KeysLagoonPunitiveCaptainAlive(sID)) return true;
		}
	}
	return false;
}

void AoP_KeysLagoonPunitiveEnsureEncounter()
{
	ref rLeader;
	string sID, sGroup, sSlot;
	int i;
	int k;
	int iLeader;
	int iChar;
	iLeader = -1;

	if (!CheckAttribute(pchar, "questTemp.AoP.KeysLagoon.PunitiveActive")) return;
	for (i = 1; i <= 4; i++)
	{
		sID = "Keys_lagoon_Punitive_Cap_" + i;
		if (!AoP_KeysLagoonPunitiveCaptainAlive(sID)) Map_ReleaseQuestEncounter(sID);
	}
	if (AoP_KeysLagoonPunitiveEncounterExists()) return;
	for (i = 1; i <= 4; i++)
	{
		sID = "Keys_lagoon_Punitive_Cap_" + i;
		if (AoP_KeysLagoonPunitiveCaptainAlive(sID)) { iLeader = GetCharacterIndex(sID); break; }
	}
	if (iLeader < 1) return;

	rLeader = GetCharacter(iLeader);
	for (k = 1; k < COMPANION_MAX; k++) { sSlot = "id" + k; rLeader.Fellows.Companions.(sSlot) = -1; }
	for (i = 1; i <= 4; i++)
	{
		sID = "Keys_lagoon_Punitive_Cap_" + i;
		iChar = GetCharacterIndex(sID);
		if (iChar < 1 || iChar == iLeader || !AoP_KeysLagoonPunitiveCaptainAlive(sID)) continue;
		SetCompanionIndex(rLeader, -1, iChar);
	}

	rLeader.mapEnc.type = "war";
	rLeader.mapEnc.worldMapShip = "quest_ship";
	rLeader.mapEnc.Name = FindPersonalName("Keys_lagoon_Punitive_mapEnc");
	rLeader.AlwaysEnemy = true;
	SetCharacterRelationBoth(iLeader, GetMainCharacterIndex(), RELATION_ENEMY);

	sGroup = "Sea_" + rLeader.id;
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);

	pchar.questTemp.AoP.KeysLagoon.PunitiveLeader = rLeader.id;
	Map_CreateCoolWarrior("", rLeader.id, -1);
}

// > найти (онлайн) enc-id квестового кораблика по characterID; "" если на карте его нет.
string wdmFindEncounterByCharacterID(string characterID)
{
	aref encs, enc;
	makearef(encs, worldMap.encounters);
	int num = GetAttributesNum(encs);
	for (int i = 0; i < num; i++)
	{
		enc = GetAttributeN(encs, i);
		if (CheckAttribute(enc, "needDelete")) continue;	// > помечен на снос
		if (!CheckAttribute(enc, "quest.chrID")) continue;
		if (enc.quest.chrID == characterID) return GetAttributeName(enc);
	}
	return "";
}

// > ОТЛАДКА: подписи над энкаунтером - id, тип, слот генерации (trade/war/special, нация, модель), квестовая привязка (chrID > событие), цель движения (goto) и остаток жизни.
// Занимает строки 4..7 (строки 0..3 оставлены под игровые подписи из wdmApplyShipFX).
// ВКЛЮЧЕНИЕ:  worldMap.debugShipFX = 1;  затем перезайти на глобалку (или вызвать wdmApplyAllShipFX() из консоли).
// ВЫКЛЮЧЕНИЕ: DeleteAttribute(&worldMap, "debugShipFX"); подписи умрут при следующем перезаходе на карту.
void wdmDebugShipLabel(string encID)
{
	if (!CheckAttribute(&worldMap, "debugShipFX")) return;
	if (encID == "") return;
	string encPath = "encounters." + encID;
	if (!CheckAttribute(&worldMap, encPath)) return;
	aref enc;
	makearef(enc, worldMap.(encPath));
	if (CheckAttribute(enc, "needDelete")) return;

	// строка 4: id + тип (Merchant/Follow/Warring/Attacked/Storm)
	string sInfo = encID;
	if (CheckAttribute(enc, "type")) sInfo = sInfo + " [" + enc.type + "]";
	wdmSetShipText(encID, 4, sInfo, "INTERFACE_NORMAL", 1.0, argb(255, 255, 255, 120), 0.0, 0.0, 0.0, 17.0, 0.0, 0, 1);

	// строка 5: слот генерации — trade/war/special, нация, модель кораблика
	sInfo = "";
	if (CheckAttribute(enc, "encdata.Type")) sInfo = enc.encdata.Type;
	if (CheckAttribute(enc, "encdata.Nation")) sInfo = sInfo + " " + NationShortName(sti(enc.encdata.Nation));
	if (CheckAttribute(enc, "encdata.worldMapShip")) sInfo = sInfo + " " + enc.encdata.worldMapShip;
	wdmSetShipText(encID, 5, sInfo, "INTERFACE_NORMAL", 1.0, argb(255, 170, 255, 170), 0.0, 0.0, 0.0, 14.0, 0.0, 0, 1);

	// строка 6: квестовая привязка — chrID (или CharacterID слота) > событие завершения
	sInfo = "";
	if (CheckAttribute(enc, "quest.chrID")) sInfo = enc.quest.chrID;
	else
	{
		if (CheckAttribute(enc, "encdata.CharacterID")) sInfo = enc.encdata.CharacterID;
	}
	if (CheckAttribute(enc, "quest.event")) sInfo = sInfo + " > " + enc.quest.event;
	wdmSetShipText(encID, 6, sInfo, "INTERFACE_NORMAL", 1.0, argb(255, 255, 160, 160), 0.0, 0.0, 0.0, 11.0, 0.0, 0, 1);

	// строка 7: пункт назначения (goto-координаты торговца) + остаток жизни, сек (снимок на момент применения надписи! > TODO рефрешь?)
	sInfo = "";
	if (CheckAttribute(enc, "gotoX")) sInfo = "goto " + makeint(stf(enc.gotoX)) + "," + makeint(stf(enc.gotoZ));
	if (CheckAttribute(enc, "liveTime")) sInfo = sInfo + " t=" + makeint(stf(enc.liveTime));
	wdmSetShipText(encID, 7, sInfo, "INTERFACE_NORMAL", 1.0, argb(255, 190, 190, 190), 0.0, 0.0, 0.0, 7.0, 0.0, 0, 1);
}

// > Единая точка назначения эффектов кораблику-энкаунтеру.
// > Вызывается при каждом входе на глобалку и при создании квестового энкаунтера. Повторный вызов заменяет эффект, а не накапливает.
void wdmApplyShipFX(string encID)
{
	if (encID == "") return;
	string encPath = "encounters." + encID + ".quest.chrID";
	if (!CheckAttribute(&worldMap, encPath)) return;
	string chrID = worldMap.(encPath);

	string sTextureName = "WorldMap\Effects\AlarmBack_w.tga";
	int iColorMainQuest = argb(255, 255, 255, 255);
	int iColorGenQuest = argb(255, 0, 224, 16);
	int iTextureSize = 11;
	int iTextureYOffset = 0;
	int iTextureColor = argb(255, 224, 16, 192);
	float fTextureRotationSpeed = 0.7;
	bool bOk = false;

// > уникальные энкаунтеры
	switch (chrID)
	{
		case "Danielle": bOk = true; break;																// Королева
		case "GhostCapt": iTextureColor = argb(255, 0, 0, 0); bOk = true; break;						// ЛГ
		case "MushketCap": bOk = true; break;															// Стрела
		case "Sharp": bOk = true; break;																// Шарпоносец
		case "Head_of_Gold_Squadron": iTextureColor = argb(255, 255, 215, 0); bOk = true; break;		// ЗФ
	}

// > квестовые корабли
	if (!bOk)
	{
		switch (chrID)
		{
			// > основные квесты
			case "LeonCapitain": iTextureColor = iColorMainQuest; bOk = true; break;					// Фрегат "Леон"
			case "QuestCap_PL7": iTextureColor = iColorMainQuest; bOk = true; break;					// Баттлшип "Неуловимый"
			case "GaleonCap": iTextureColor = iColorMainQuest; bOk = true; break;						// Галеон по работорговцу
			case "Esteban_Molina": iTextureColor = argb(255, 255, 0, 0); bOk = true; break;				// Судно "Ла-Палома"
			// > генераторы
			case "MarginCap": iTextureColor = iColorGenQuest; bOk = true; break;						// Похититель
			case "SouthshipCap": iTextureColor = iColorGenQuest; bOk = true; break;						// Похититель тоже
			case "PirateCapt": iTextureColor = iColorGenQuest; bOk = true; break;						// Повод для спешки
			case "ShipWreck_BadPirate": iTextureColor = iColorGenQuest; bOk = true; break; 				// Кораблекрушенцы
			case "PiratesOnUninhabited_BadPirate": iTextureColor = iColorGenQuest; bOk = true; break;	// Необитайщики
		}
	}

// > джентельмены удачи (перехватчики фрахтов / охотники за головами / сокровищами)
	if (!bOk && or(StrStartsWith(chrID, "Follower0") || HasStr(chrID, "Hunter0"), StrEndsWith(chrID, "_QuestMerchant")))
	{
		sTextureName = "WorldMap\Effects\AlarmBack.tga";
		iTextureColor = argb(255, 255, 0, 0);
		bOk = true;
	}

// > корабли осады
	if (!bOk && HasStr(chrID, "SiegeCap_"))
	{
		iTextureColor = argb(255, 164, 164, 255);
		bOk = true;
	}

// > Различные генераторные квесты
// > генераторы ПУ (возврат СЖ, поиск украденного корабля)
	if (!bOk && StrStartsWith(chrID, "PortmansCap_") || StrStartsWith(chrID, "SeekCap_"))
	{
		iTextureColor = iColorGenQuest;
		bOk = true;
	}

// > генераторы горожан (украденная жена, похищенный муж и т.д.)
	if (!bOk && StrStartsWith(chrID, "SeekCitizCap_"))
	{
		iTextureColor = iColorGenQuest;
		bOk = true;
	}

	if (bOk)
	{
		wdmSetShipSprite(encID, sTextureName, iTextureSize, iTextureYOffset, iTextureColor);
		wdmSetShipSpriteRotate("", 1, fTextureRotationSpeed, 0.0, 0);
	}
}

// > Переналожить эффекты на все квестовые корабли (+ эффекты для корабля ГГ указывать тут). Выполняется один раз за вход на карту.
void wdmApplyAllShipFX()
{
	aref encs, enc;
	makearef(encs, worldMap.encounters);
	int i, num = GetAttributesNum(encs);

	for (i = 0; i < num; i++)
	{
		enc = GetAttributeN(encs, i);
		if (CheckAttribute(enc, "needDelete")) continue;
		if (!CheckAttribute(enc, "quest.chrID")) continue;
		wdmApplyShipFX(GetAttributeName(enc));
	}

	// > эффекты кораблей ГГ пихать сюда, если нужно >
}

//=========================================================================================
//Util functions
//=========================================================================================

//Storm functions

int wdmGetNumberStorms()
{
	return MakeInt(worldMap.storm.num);
}

//Ship encounter functions

int wdmGetNumberShipEncounters()
{
	return MakeInt(worldMap.encounter.num);
}

bool wdmSetCurrentShipData(int shipIndex)
{
	worldMap.encounter.cur = shipIndex;
	int i = MakeInt(worldMap.encounter.cur);
	if(i < 0 || i != shipIndex) return 0;
	return 1;
}

//Создание энкоунтеров...

// Специальный энкоунтер (сундук или кораблекрушенец)
bool wdmCreateSpecial(float kSpeed)
{
	//Получим описание энкоунтера в море
	int i1 = -1;
	int i2 = -1;
	//Создаём энкоунтера
	if(GenerateMapEncounter(WDM_ETYPE_SPECIAL, worldMap.island, &i1, &i2) == false)
	{
		ReleaseMapEncounters();
		return false;
	}
	string encID = "";
	bool res = wdmCreateSpecialByIndex(kSpeed, i1, &encID, "", "", 5+rand(5)); //boal new //homo 07/10/06
	//Очищаем массив энкоунтеров
	//Log_TestInfo("Create Special Encounter");
	ReleaseMapEncounters();
	return res;
}

//Бочонок или кораблекрушенец
bool wdmCreateSpecialByIndex(float kSpeed, int index, ref encID, string from, string to, int timeOutInDays)  // boal
{
	//Нация энкоунтера (моделька)
	string nationShipName = wdmEncounterModelName(index);
	//Создадим ссылку на атрибуты
	ref mapEncSlotRef = GetMapEncounterRef(index);
	// boal правки в ядре -->
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec);
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = SendMessage(&worldMap, "lsssff", MSG_WORLDMAP_CREATEENC_MER, nationShipName, from, to, kSpeed, timeOutInSec);
	// boal <--
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	//Вернём идентификатор
	encID = worldMap.EncounterID1;
	return res;
}

//Торговец
bool wdmCreateMerchantShip(float kSpeed)
{
	//Получим описание энкоунтера в море
	int i1 = -1;
	int i2 = -1;
	if(GenerateMapEncounter(WDM_ETYPE_MERCHANT, worldMap.island, &i1, &i2) == false)
	{
		ReleaseMapEncounters();
		return false;
	}
	//Создаём энкоунтера
	string encID = "";
	bool res = wdmCreateMerchantShipByIndex(kSpeed, i1, &encID, "", "", 5+rand(5)); //boal new //homo 07/10/06
	//Очищаем массив энкоунтеров
	ReleaseMapEncounters();
	return res;
}

//Торговец
bool wdmCreateMerchantShipByIndex(float kSpeed, int index, ref encID, string from, string to, int timeOutInDays)  // boal
{
	//Нация энкоунтера (моделька)
	string nationShipName = wdmEncounterModelName(index);
	//Создадим ссылку на атрибуты
	ref mapEncSlotRef = GetMapEncounterRef(index);
	// boal правки в ядре -->
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec);
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = SendMessage(&worldMap, "lsssff", MSG_WORLDMAP_CREATEENC_MER, nationShipName, from, to, kSpeed, timeOutInSec);
	// boal <--
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	//Вернём идентификатор
	encID = worldMap.EncounterID1;
	return res;
}
// boal 04/10/06
bool wdmCreateMerchantShipXZByIndex(float kSpeed, int index, ref encID, float x1, float z1, float x2, float z2, int timeOutInDays)  
{
	//Нация энкоунтера (моделька)
	string nationShipName = wdmEncounterModelName(index);
	//Создадим ссылку на атрибуты
	ref mapEncSlotRef = GetMapEncounterRef(index);
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec);
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = SendMessage(&worldMap, "lsffffff", MSG_WORLDMAP_CREATEENC_MER_XZ, nationShipName, x1, z1, x2, z2, kSpeed, timeOutInSec);
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	//Вернём идентификатор
	encID = worldMap.EncounterID1;
	return res;
}

//Преследователь
bool wdmCreateFollowShip(float kSpeed)
{
	//Получим описание энкоунтера в море
	int i1 = -1;
	int i2 = -1;
	if(GenerateMapEncounter(WDM_ETYPE_FOLLOW, worldMap.island, &i1, &i2) == false)
	{
		ReleaseMapEncounters();
		return false;
	}
	//Создаём энкоунтера
	string encID = "";
	bool res = wdmCreateFollowShipByIndex(kSpeed, i1, &encID, 5+rand(5)); //homo 07/10/06
	//Очищаем массив энкоунтеров
	ReleaseMapEncounters();
	return res;
}

//Преследователь
bool wdmCreateFollowShipByIndex(float kSpeed, int index, ref encID, int timeOutInDays)
{
	//Нация энкоунтера
	string nationShipName = wdmEncounterModelName(index);
	//Создадим ссылку на атрибуты
	ref mapEncSlotRef = GetMapEncounterRef(index);
	//Время жизни в секундах
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); // Boal супер бага была - делили на 24. Математику в школе прогуливали?
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = false;
	if (!wdmIsEncounterEnemy(index))
	{
		res = SendMessage(&worldMap, "lsssff", MSG_WORLDMAP_CREATEENC_MER, nationShipName, "", "", kSpeed, timeOutInSec); // boal new
	}
	else
	{   // boal - код этот полный абзац, я Вам, господа акеловцы, аплодирую - метод Следовать даёт убегание - и так весь код. плакаль
		// погано, что метод имеет право быть, но название должно быть иным, нужно чтоб мирные не доставали патрулями.
		res = SendMessage(&worldMap, "lsff", MSG_WORLDMAP_CREATEENC_FLW, nationShipName, kSpeed, timeOutInSec);
	}
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	encID = worldMap.EncounterID1;
	return res;
}

//Преследователь НАСТОЯЩИЙ
bool wdmCreateRealFollowShipByIndex(float kSpeed, int index, ref encID, int timeOutInDays)
{
	//Нация энкоунтера
	string nationShipName = wdmEncounterModelName(index);
	//проверим нацию
/*
	ref n = GetMapEncounterRef(index);
	int iNation = PIRATE;
	if(CheckAttribute(n, "nation"))
	{
		iNation = sti(n.Nation);
	}
*/
	//Создадим ссылку на атрибуты
	ref mapEncSlotRef = GetMapEncounterRef(index);
	//Время жизни в секундах
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); // Boal супер бага была - делили на 24. Математику в школе прогуливали?
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = false;
	/*if(GetNationRelation2MainCharacter(iNation) != RELATION_ENEMY)
	{
		res = SendMessage(&worldMap, "lsssf", MSG_WORLDMAP_CREATEENC_MER, nationShipName, "", "", kSpeed);
	}
	else
	{ */  // boal - код этот полный абзац, я Вам, господа акеловцы, аплодирую - метод Следовать даёт убегание - и так весь код. плакаль
		res = SendMessage(&worldMap, "lsff", MSG_WORLDMAP_CREATEENC_FLW, nationShipName, kSpeed, timeOutInSec);
	//}
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef, worldMap.EncounterID1);
	encID = worldMap.EncounterID1;
	return res;
}

//Воюющие корабли
bool wdmCreateWarringShips()
{
	//Получим описание энкоунтера в море
	int i1 = -1;
	int i2 = -1;
	if(GenerateMapEncounter(WDM_ETYPE_WARRING, worldMap.island, &i1, &i2) == false) 
	{
		ReleaseMapEncounters();
		return false;
	}
	//Создаём энкоунтера
	string encID1 = "";
	string encID2 = "";
	bool res = wdmCreateWarringShipsByIndex(i1, i2, &encID1, &encID2, 5+rand(5));  //homo 07/10/06
	//Очищаем массив энкоунтеров
	ReleaseMapEncounters();
	return res;
}

//Воюющие корабли
bool wdmCreateWarringShipsByIndex(int index1, int index2, ref encID1, ref encID2, int timeOutInDays)
{
	//Нации энкоунтера
	string nationShipName1 = wdmEncounterModelName(index1);
	string nationShipName2 = wdmEncounterModelName(index2);
	//Создадим ссылки на атрибуты
	ref mapEncSlotRef1 = GetMapEncounterRef(index1);
	ref mapEncSlotRef2 = GetMapEncounterRef(index2);
	//Время жизни в секундах
	float daysPerSec = 24.0/stf(worldMap.date.hourPerSec); // Boal супер бага была - делили на 24. Математику в школе прогуливали?
	float timeOutInSec = daysPerSec*timeOutInDays;
	//Создаём реального энкоунтера
	bool res = SendMessage(&worldMap, "lssf", MSG_WORLDMAP_CREATEENC_WAR, nationShipName1, nationShipName2, timeOutInSec);
	//Копируем данные
	WdmCopyEncounterData(mapEncSlotRef1, worldMap.EncounterID1);
	WdmCopyEncounterData(mapEncSlotRef2, worldMap.EncounterID2);
	encID1 = worldMap.EncounterID1;
	encID2 = worldMap.EncounterID2;
	return res;
}

//Шторм
void wdmCreateStorm()
{
    if(CheckAttribute(pchar,"worldmapencountersoff") == 1)
	{  // boal убиралка шторма
		if(sti(pchar.worldmapencountersoff)) return;
	}
	int isTornado = 0;
	if(worldMap.island == WDM_NONE_ISLAND)
	{
		int r = rand(1000);
		if(r != 0)
		{
			if(r < 450)
			{
				isTornado = 1;
			}
		}
	}
	// тест торнадор
	isTornado = 1;
	// конец теста
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_CREATESTORM, isTornado);
}

//Получить модельку кораблика по индексу нации
string wdmEncounterModelName(int encIndex)
{
	ref n = GetMapEncounterRef(encIndex);
	if(CheckAttribute(n, "worldMapShip") != 0)
	{
		return n.worldMapShip;
	}
	return "ship";
}

//Скопировать данные об энкоутере
void WdmCopyEncounterData(ref mapEncSlotRef, string encStringID)
{
	string sEncID = encStringID; // > чистый id для отладочной инфы
	encStringID = "encounters." + encStringID + ".encdata";
	worldMap.(encStringID) = "";
	aref destRef;
	makearef(destRef, worldMap.(encStringID));
	CopyAttributes(destRef, mapEncSlotRef);
	// > сюда сходятся все создаваемые энкаунтеры (торговец/преследователь/спец/воюющие оба id)
	// > вешаем отладочную подпись на каждого нового прямо при появлении
	wdmDebugShipLabel(sEncID);
}

//Зарезервировать место для добавления нового энкоунтера
aref wdmCreateNewQuestEncDescription()
{
	string gname, aname;
	aref encs, at;
	makearef(encs, worldMap.addQuestEncounters);
	int num = GetAttributesNum(encs);
	int i;
	for(int cnt = 0; cnt < num + 10; cnt++)
	{	
		gname = "e" + cnt;
		for(i = 0; i < num; i++)
		{
			at = GetAttributeN(encs, i);
			aname = GetAttributeName(at);
			if(aname == gname)
			{
				break;
			}
		}
		if(i >= num)
		{
			break;
		}
	}
	aref retVal;
	makearef(retVal, worldMap.addQuestEncounters.(gname));
	return retVal;
}

//// boal & homosapienz
void  wdmEmptyAllDeadQuestEncounter()
{
    aref encs;
    string sdel,aname;
	bool isWMap = IsEntity(&worldMap);
	int i, iChar;
    makearef(encs, worldMap.encounters);

    int num = GetAttributesNum(encs);
    for(i = 0; i < num; i++)
    {
        aref enc = GetAttributeN(encs, i);
        if(CheckAttribute(enc, "quest.chrID"))
        {
            iChar = GetCharacterIndex(enc.quest.chrID);
            sdel  = "encounters."+GetAttributeName(enc);
            if (iChar == -1 || CharacterIsDead(&characters[iChar]))
            {
	            if (!isWMap)
				{
					DeleteAttribute(&worldMap, sdel);
	                num = GetAttributesNum(encs);
	                pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	                i--;
	            }
	            else
	            {
	            	 enc.livetime = 0;
	            }
	        }
        }
    }

   	makearef(encs, worldMap.addQuestEncounters);
    num = GetAttributesNum(encs);
	for(i = 0; i < num; i++)
	{
		aref at = GetAttributeN(encs, i);
		sdel = GetAttributeName(at);
		aname = "addQuestEncounters." + sdel + ".characterID";
		if (CheckAttribute(&worldMap, aname))
		{
	        iChar = GetCharacterIndex(worldMap.(aname));
	        if (iChar == -1 || CharacterIsDead(&characters[iChar]))
	        {
	            DeleteAttribute(&worldMap, "addQuestEncounters." + sdel);
	            num = GetAttributesNum(encs);
	            pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	            i--;
	        }
        }
    }
}

// чистка энкоутеров на карте homosapienz
void  wdmEmptyAllOldEncounter()
{
    aref encs;
    string sdel,aname;
	bool isWMap = IsEntity(&worldMap);

    makearef(encs, worldMap.encounters);

    int num = GetAttributesNum(encs);
    aref enc;
    int  i;
    
    for (i = 0; i < num; i++)
    {
        enc = GetAttributeN(encs, i);
        if (CheckAttribute(enc, "needDelete") && enc.needDelete == "wdmEncounterDelete")
        {
	        if (CheckAttribute(enc, "quest")) pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1; // mitrokosta fix!!!!
	        sdel  = "encounters."+GetAttributeName(enc);
			DeleteAttribute(&worldMap, sdel);
	        num--; //fix
	        i--;
        }
    }
}

// время жизни на карте для квестовых энкоутеров
void  wdmUpdateAllEncounterLivetime()
{
    aref encs;
    int ihours;
    string sdel;
	string sChar;
    float b,k;
    if(!actLoadFlag)
    {
		ihours = GetQuestPastTimeParam("WordMapEncounters_DailyUpdate");
		if (ihours > 0)
		{
            Log_TestInfo("Прошло дней: "+makeint(ihours/24.0));
            float timeOutInSec = ihours/stf(worldMap.date.hourPerSec);

            makearef(encs, worldMap.encounters);
            int num = GetAttributesNum(encs);
            aref enc;
            int  i;

            for (i = 0; i < num; i++)
            {
                enc = GetAttributeN(encs, i);          // только квестовые
                if (CheckAttribute(enc, "livetime") && CheckAttribute(enc, "quest"))
                {
                    Log_TestInfo(enc.livetime+" - "+timeOutInSec+" : "+stf(stf(enc.livetime) - timeOutInSec));
                    /* По идее можно и координату приращивтаь, чтоб не просто время шло, но ещё и плыли.
                    k = (enc.gotoz - enc.z)/(enc.gotox - enc.x);
                    b = enc.z - k*enc.x
                    ...
                    */
                    enc.livetime = stf(stf(enc.livetime) - timeOutInSec);
                    DeleteAttribute(enc, "quest.event"); // удаляем  event = Map_TraderSucces

                    if (sti(enc.livetime)<=0)
                    {
                        //Map_ReleaseQuestEncounter(enc.quest.chrID);
						sChar = enc.quest.chrID; // belamour запомним айди, иначе трется и квестовые кэпы дают вылет на глобусе
               	        sdel  = "encounters."+GetAttributeName(enc);
                        DeleteAttribute(&worldMap, sdel);
						pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
						num--;
						i--;
						Map_TraderSucces_quest(sChar); // belamour теперь запустим обработку нпс-кэпов
                    }
                }
            }
		}
	}
}

// найти сущ случайку для НПС

aref wdmFindOrCreateQuestEncounter(string _chrId)
{
    aref encs;
    string sdel,aname;
	bool isWMap = IsEntity(&worldMap);
    int i, iChar;
    makearef(encs, worldMap.encounters);

    int num = GetAttributesNum(encs);
    for(i = 0; i < num; i++)
    {
        aref enc = GetAttributeN(encs, i);
        if (CheckAttribute(enc, "quest.chrID"))
        {
            iChar = GetCharacterIndex(enc.quest.chrID);
            sdel  = "encounters."+GetAttributeName(enc);
            if (iChar == -1 || characters[iChar].id == _chrId)
            {
	            if (!isWMap)
				{
					DeleteAttribute(&worldMap, sdel);
	                num = GetAttributesNum(encs);
	                pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	                i--;
	            }
	            else
	            {
	            	 enc.livetime = 0;
	            }
	        }
        }
    }

   	makearef(encs, worldMap.addQuestEncounters);
    num = GetAttributesNum(encs);
	for(i = 0; i < num; i++)
	{
		aref at = GetAttributeN(encs, i);
		sdel = GetAttributeName(at);
		aname = "addQuestEncounters." + sdel + ".characterID";
		if (CheckAttribute(&worldMap, aname))
		{
	        iChar = GetCharacterIndex(worldMap.(aname));
	        if (iChar == -1 || characters[iChar].id == _chrId)
	        {
	            DeleteAttribute(&worldMap, "addQuestEncounters." + sdel);
	            num = GetAttributesNum(encs);
	            pchar.worldmap.shipcounter = sti(pchar.worldmap.shipcounter) - 1;
	            i--;
	        }
        }
    }

	return wdmCreateNewQuestEncDescription();
}

// mitrokosta вернуть false если энкаунтер убегающий
bool wdmIsEncounterEnemy(int index)
{
	ref rEnc = GetMapEncounterRef(index);
	int iNation = PIRATE;
	int iSquadronBestClass = GetPcharSquadronShipClass(0, 0);					// лучший класс корабля в эскадре ГГ

	if (CheckAttribute(rEnc, "nation"))
		iNation = sti(rEnc.Nation);

	if (or(IsCharacterPerkOn(pchar, "SeaDogProfessional") && iSquadronBestClass <= 4, GetNationRelation2MainCharacter(iNation) != RELATION_ENEMY))
		return false;

	int iEncType = sti(rEnc.RealEncounterType);
	int iPcharShipClass = GetCharacterShipClass(pchar);							// класс корабля ГГ
	int iSquadronQuantity = GetCompanionQuantity(pchar);						// кол-во кораблей в эскадре ГГ
	int iSquadronAverageClass = GetPcharSquadronAverageClass(1);				// средний класс кораблей в эскадре ГГ
//	int iSquadronWorstClass = GetPcharSquadronShipClass(1, 0);					// худший класс корабля в эскадре ГГ > TODO
	bool bSquadronType = GetPcharSquadronType();								// тип эскадры ГГ: "боевая" (true) или "торговая" (false)
	bool smallPir = iEncType == ENCOUNTER_TYPE_PIRATE_SMALL;					// мелкий энкаунтер пиратов
	bool mediumPir = (smallPir) || (iEncType == ENCOUNTER_TYPE_PIRATE_MEDIUM);	// средний энкаунтер пиратов
	bool largePir = (mediumPir) || (iEncType == ENCOUNTER_TYPE_PIRATE_LARGE);	// крупный энкаунтер пиратов
//	ref rEncType = &EncountersTypes[iEncType];

	// TODO на будущее > чекать наличие установленных орудий, загруженность трюма, состояние корабля, численность команды и т.д.

	// если ГГ на <= 3 классе и корабли преимущественно боевые, то энкаунтеры малых пиратов не нападают
	if (iPcharShipClass <= 3 && bSquadronType && smallPir)
		return false;

	// если ГГ на <= 4 классе, есть 1+ компаньон и средний класс кораблей компаньонов <= 4 и эскадра преимущественно боевая, то энкаунтеры средних пиратов не нападают
	if (iPcharShipClass <= 4 && iSquadronQuantity > 1 && iSquadronAverageClass <= 4 && bSquadronType && mediumPir)
		return false;

	// если ГГ на <= 2 классе и эскадра преимущественно боевая, то энкаунтеры средних пиратов не нападают
	if (iPcharShipClass <= 2 && bSquadronType && mediumPir)
		return false;

	// если ГГ на <= 3 классе, есть 1+ компаньон, средний класс кораблей компаньонов <= 3 и эскадра преимущественно боевая, то энкаунтеры средних пиратов не нападают
	if (iPcharShipClass <= 3 && iSquadronQuantity > 1 && iSquadronAverageClass <= 3 && bSquadronType && mediumPir)
		return false;

	// если ГГ на 1 классе, есть 2+ компаньона, средний класс кораблей компаньонов <= 2 и эскадра преимущественно боевая, то энкаунтеры крупных пиратов не нападают
	if (iPcharShipClass < 2 && iSquadronQuantity > 2 && iSquadronAverageClass <= 2 && bSquadronType && largePir)
		return false;

	return true;
}

void wdmShowInterface(bool showUI)
{
	SendMessage(&worldMap, "ll", MSG_WORLDMAP_WIND_UI_SET_SHOW, showUI);
}

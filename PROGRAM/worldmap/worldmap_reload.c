

object wdmLoginToSea;
object wdm_fader;
bool wdmLockReload = false;

bool AoP_RoyalJackpot_CheckBrigBattle()
{
	if (!CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.BrigBattlePending"))
	{
		return false;
	}
	if (worldMap.island != WDM_NONE_ISLAND)
	{
		return false;
	}
	float fTargetX = -79.83;
	float fTargetZ = 315.727;

	float fDX = stf(worldMap.playerShipX) - fTargetX;
	float fDZ = stf(worldMap.playerShipZ) - fTargetZ;
	if (fDX * fDX + fDZ * fDZ > 225.0)
	{
		return false;
	}
	Group_SetAddressNone("RoyalJackpot_BrigGroup");
	Group_SetXZ_AY("RoyalJackpot_BrigGroup", 0.0, 900.0, 3.14);

	Group_SetTaskAttack("RoyalJackpot_BrigGroup", PLAYER_GROUP);
	Group_LockTask("RoyalJackpot_BrigGroup");
	wdmLoginToSea.QuestGroups.l0 = "RoyalJackpot_BrigGroup";
	AoP_RemoveMapMarkByCoords("RoyalJackpot_BrigBattle");

	DeleteAttribute(pchar, "questTemp.AoP.RoyalJackpot.BrigBattlePending");
	pchar.questTemp.AoP.RoyalJackpot.BrigBattleStarted = true;

	return true;
}

// выход в море по координатам (ле Баск)
bool AoP_RoyalJackpot_CheckMeetingPoint()
{
	if (!CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.MeetingPoint"))
	{
		return false;
	}
	if (worldMap.island != WDM_NONE_ISLAND)
	{
		return false;
	}

	float fTargetX = -79.83;
	float fTargetZ = 315.727;
	float fDX = stf(worldMap.playerShipX) - fTargetX;
	float fDZ = stf(worldMap.playerShipZ) - fTargetZ;
	if (fDX * fDX + fDZ * fDZ > 225.0)
	{
		return false;
	}
	DeleteAttribute(pchar, "questTemp.AoP.RoyalJackpot.MeetingPoint");
	AoP_RemoveMapMarkByCoords("Royal_jackpot_MeetingPoint");
	pchar.questTemp.AoP.RoyalJackpot.GoToDeckAfterSea = true;

	return true;
}

void wdmReloadToSea()
{
	//Если запрещена перегрузка, ничего не делаем
	if(wdmLockReload)
	{
		return;
	}
	// выход на палубу по координатам (ле Баск)
	AoP_RoyalJackpot_CheckMeetingPoint();
	// расчёты ВМЛ -->
	EmptyAllFantomCharacter();
	PGG_DailyUpdate();
	Siege_DailyUpdate();//homo осады 05/11/06
	SaveCurrentQuestDateParam("WordMapEncounters_DailyUpdate"); //homo карта 25/03/07
	// расчёты <--

	wdmLockReload = true;
	SoberParty();
	//Очищаем объект логина
	DeleteAttribute(&wdmLoginToSea, "");
	//Обновляем параметры
	worldMap.encounter.type = "";
	worldMap.playerShipUpdate = "";
	worldMap.info.updateinfo = "";
	//Добавляем группу игрока
	WdmAddPlayerGroup();
	//Добавляем энкоунтеры

// бой в открытом море по координатам (ле Баск)
bool bAoPRoyalBattle = AoP_RoyalJackpot_CheckBrigBattle();

//Добавляем энкоунтеры
bool isShipEncounterType;

if (bAoPRoyalBattle)
{
	ReleaseMapEncounters();
	isShipEncounterType = true;
}
else
{
	isShipEncounterType = WdmAddEncountersData();
}
	//Отконектим все энкоунтеры от атрибутов и поставим в очередь удаления
	SendMessage(&worldMap, "l", MSG_WORLDMAP_CREATEENC_RELEASE);
	//Погодные эффекты
	WdmStormEncounter();
	//Удаляем атрибуты выделенных энкоунтеров
	worldMap.deleteUpdate = "";

	if (MakeInt(wdmLoginToSea.storm) == 0 && !isShipEncounterType) // не в шторме, не в бою
		MapToSea_CheckAutoSave();
	else
		WdmReloadStart(isShipEncounterType);
}

void MapToSea_CheckAutoSave()
{
	if(GetMaxAutoSaves("MapToSea") != 0)
	{
		SetAfterSaveFunction("MapToSea_Continue");
		PostEvent("Event_NewAutoSave", 1, "s", "MapToSea");
	}
	else
		MapToSea_Continue();
}

void MapToSea_Continue()
{
	WdmReloadStart(false);
}

void WdmReloadStart(bool isShipEncounterType)
{
	//Фейдер
	SetEventHandler("FaderEvent_StartFade", "WdmStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "WdmEndFade", 0);
	wdm_fader.thisWorldMapFader = "";
	CreateEntity(&wdm_fader, "fader");
	if (IsEntity(&wdm_fader) == 0) Trace("Fader not created!!!");
	float fadeOutTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_OUT, fadeOutTime, true);
	SendMessage(&wdm_fader, "l", FADER_STARTFRAME);
	//Установим картинку для фейдера
	string imageName = GetLoadingImage_Sea();
	if(isShipEncounterType)
	{
		imageName = "loading\battle_" + rand(2) + ".tga";
	}
	if(MakeInt(wdmLoginToSea.storm) != 0)
	{
		imageName = "loading\Storm.tga";
		/*if(MakeInt(wdmLoginToSea.tornado) != 0)
		{
			imageName = "loading\Twister.tga";
		}*/ // boal пусть будет одна
	}
	wdmLoginToSea.imageName = imageName;
	//SendMessage(&wdm_fader, "ls", FADER_PICTURE0, "interfaces\card_desk.tga");
	SendMessage(&wdm_fader, "ls",FADER_PICTURE0, imageName);
}

void WdmStartFade()
{
	PauseAllSounds();
	//Delete EventHandler
	DelEventHandler("FaderEvent_StartFade", "WdmStartFade");
	//Delete entity
	worldMap.playerShipUpdate = "";
	DeleteClass(&worldMap);
	worldMap.isLoaded = "false";
	DeleteWmInterface();
	DelEventHandler("frame", "CheckMapCoordinateQuest");
}

void WdmEndFade()
{
	int a = GetEventData();
	aref reload_fader = GetEventData();
	//Delete EventHandler
	DelEventHandler("FaderEvent_EndFade", "WdmEndFade");
	//Switch to sea
	ReloadProgressStart();
	SeaLogin(&wdmLoginToSea);
	LayerAddObject(SEA_REALIZE, &reload_fader, -1);
	ReloadProgressEnd();
	// ле Баск - после выхода в млре через 3 сек на палубу
	if (CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.GoToDeckAfterSea"))
	{
		DeleteAttribute(pchar, "questTemp.AoP.RoyalJackpot.GoToDeckAfterSea");
		bQuestDisableMapEnter = true; // закрыть карту
		Ship_SetLightsOff(pchar, 0.0, true, true, true);
		DoQuestCheckDelay("Off_Interface", 0.2);
		DoQuestCheckDelay("Royal_jackpot_91", 3.0);
	}
}

void QuitFromWorldMap()
{
	//Fade out
	SetEventHandler("FaderEvent_StartFade", "WdmStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "WdmEndFadeA", 0);
	wdm_fader.thisWorldMapFader = "";
	CreateEntity(&wdm_fader, "fader");
	if (IsEntity(&wdm_fader) == 0) Trace("Fader not created!!!");
	float fadeOutTime = 0.5;
	SendMessage(&wdm_fader, "lfl", FADER_OUT, fadeOutTime, true);
	SendMessage(&wdm_fader, "l", FADER_STARTFRAME);
}

void WdmEndFadeA()
{
	//Delete EventHandler
	DelEventHandler("FaderEvent_EndFade", "WdmEndFadeA");
	//Switch to sea
	Event("QuitFromWorldMap");
}

// VANO function: return sea coordinates
void WdmPrepareMapForAbordage(aref arPos)
{
	//Координаты игрока на карте
	float psX = MakeFloat(worldMap.playerShipX);
	float psZ = MakeFloat(worldMap.playerShipZ);
	//Учитываем остров
	if(worldMap.island != WDM_NONE_ISLAND)
	{
		//Island
		wdmLoginToSea.island = worldMap.island;
		float ix = MakeFloat(worldMap.island.x);
		float iz = MakeFloat(worldMap.island.z);
		int scale = GetSeaToMapScale();
		arPos.x = (psX - ix)*scale;
		arPos.z = (psZ - iz)*scale;
		arPos.y = worldMap.playerShipAY;
		worldMap.zeroX = ix;
		worldMap.zeroZ = iz;
	}else{
		//no Island
		wdmLoginToSea.island = "";
		//Player ship
		arPos.x = 0;
		arPos.z = 0;
		arPos.y = worldMap.playerShipAY;
		worldMap.zeroX = worldMap.playerShipX;
		worldMap.zeroZ = worldMap.playerShipZ;
	}
}

void WdmAddPlayerGroup()
{
	if (CheckAttribute(pchar, "quest.EnterToSeaLSC") && worldMap.island == "LostShipsCity") //на случай нелегального попадания в ГПК
	{
		TEV.stormLSC = true;
		worldMap.playerInStorm = 1;
		worldMap.stormWhithTornado = 1;
		worldMap.stormId = 1;
	}
	//Координаты игрока на карте
	float psX = MakeFloat(worldMap.playerShipX);
	float psZ = MakeFloat(worldMap.playerShipZ);
	//Учитываем остров
	if(worldMap.island != WDM_NONE_ISLAND)
	{
		//Island
		wdmLoginToSea.island = worldMap.island;
		float ix = MakeFloat(worldMap.island.x);
		float iz = MakeFloat(worldMap.island.z);
		int scale = GetSeaToMapScale();
		wdmLoginToSea.playerGroup.x = (psX - ix)*scale;
		wdmLoginToSea.playerGroup.z = (psZ - iz)*scale;
		wdmLoginToSea.playerGroup.ay = worldMap.playerShipAY;
		worldMap.zeroX = ix;
		worldMap.zeroZ = iz;
	}else{
		//no Island
		wdmLoginToSea.island = "";
		//Player ship
		wdmLoginToSea.playerGroup.x = 0;
		wdmLoginToSea.playerGroup.z = 0;
		wdmLoginToSea.playerGroup.ay = worldMap.playerShipAY;
		worldMap.zeroX = worldMap.playerShipX;
		worldMap.zeroZ = worldMap.playerShipZ;
	}
}

bool WdmAddEncountersData()
{
	bool isShipEncounter = false;
	//Удалим все существующие записи об морских энкоунтерах
	ReleaseMapEncounters();
	//Количество корабельных энкоунтеров в карте
	int numEncounters = wdmGetNumberShipEncounters();
	//Позиция игрока на карте
	float mpsX = MakeFloat(worldMap.playerShipX);
	float mpsZ = MakeFloat(worldMap.playerShipZ);
	//Позиция игрока в мире
	float wpsX = MakeFloat(wdmLoginToSea.playerGroup.x);
	float wpsZ = MakeFloat(wdmLoginToSea.playerGroup.z);
	//Перебираем все энкоунтеры карты
	for(int i = 0; i < numEncounters; i++)
	{
		//Получим информацию о данном энкоунтере
		if(wdmSetCurrentShipData(i))
		{
			//Если не активен, то пропустим его
			if(MakeInt(worldMap.encounter.select) == 0) continue;
			//Добавляем информацию об морских энкоунтере
			string encStringID = worldMap.encounter.id;
			if(encStringID == "") continue;
			encStringID = "encounters." + encStringID + ".encdata";
			if(CheckAttribute(&worldMap, encStringID) == 0) continue;
			int mapEncSlot = FindFreeMapEncounterSlot();
			if(mapEncSlot < 0) continue;
			ref mapEncSlotRef = GetMapEncounterRef(mapEncSlot);
			aref encDataForSlot;
			makearef(encDataForSlot, worldMap.(encStringID));
			CopyAttributes(mapEncSlotRef, encDataForSlot);
			//Отмечаем свершение корабельного энкоунтера
			isShipEncounter = true;
			//Описываем его параметры
			string grp; grp = "group" + i;
			float encX = MakeFloat(worldMap.encounter.x);
			float encZ = MakeFloat(worldMap.encounter.z);
			wdmLoginToSea.encounters.(grp).x = wpsX + (encX - mpsX)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;//WDM_MAP_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).z = wpsZ + (encZ - mpsZ)*WDM_MAP_ENCOUNTERS_TO_SEA_SCALE;//WDM_MAP_TO_SEA_SCALE;
			wdmLoginToSea.encounters.(grp).ay = worldMap.encounter.ay;
			wdmLoginToSea.encounters.(grp).type = mapEncSlot;
			wdmLoginToSea.encounters.(grp).id = worldMap.encounter.id;
			//Помечаем энкоунтера на удаление
			encStringID = worldMap.encounter.id;
			encStringID = "encounters." + encStringID;
			if(CheckAttribute(&worldMap, encStringID + ".quest") == 0)
			{
				worldMap.(encStringID).needDelete = "Reload delete non quest encounter";
			}
		}
	}

	if (isShipEncounter && GetGlobalTutor())
	{
		WdmModifyEncountersData_OnGlobalTutor();
	}

	return isShipEncounter;
}

void WdmStormEncounter()
{
	wdmLoginToSea.storm = worldMap.playerInStorm;
	if(MakeInt(wdmLoginToSea.storm) != 0)
	{
		wdmLoginToSea.tornado = worldMap.stormWhithTornado;
	}else{
		wdmLoginToSea.tornado = "0";
	}

	//wdmLoginToSea.tornado = "1";

	if(CheckAttribute(&worldMap, "stormId") != 0)
	{
		if(worldMap.stormId != "")
		{
			string encStringID = worldMap.stormId;
			encStringID = "encounters." + encStringID;
			worldMap.(encStringID).needDelete = "Reload delete storm";
		}
	}
}

// Глобальный туториал - грузим только мирных энкаунтеров
void WdmModifyEncountersData_OnGlobalTutor()
{
	int i;
	aref encData, encRef;
	ref mapEncRef;
	string encForDelete = "";

	makearef(encData, wdmLoginToSea.encounters);

	int numEncounters = GetAttributesNum(encData);
	for (i = 0; i < numEncounters; i++)
	{
		encRef = GetAttributeN(encData, i);

		if(!CheckAttribute(encRef, "type")) continue;

		mapEncRef = GetMapEncounterRef(sti(encRef.type));
		if(GetNationRelation2MainCharacter(sti(mapEncRef.nation)) == RELATION_ENEMY)
		{
			encForDelete += GetAttributeName(encRef) + ",";
		}
	}

	if (encForDelete != "")
	{
		encForDelete = strcut(&encForDelete, 0, strlen(&encForDelete) - 2);
		DeleteAttributeEx(encData, encForDelete);
	}
}

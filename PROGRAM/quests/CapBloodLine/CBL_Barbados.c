// ---> andre39966, Прибытие мистера Блада на Барбадос

void CapBloodLine_MakeClonBridgetown()
{
	ref loc;
	CloneLocation("Bridgetown_town", "Clone_location");
	makeref(loc, Locations[FindLocation("Clone_location")]);

	DeleteAttribute(loc, "characters");
	DeleteAttribute(loc, "townsack");
	DeleteAttribute(loc, "city");
	DeleteAttribute(loc, "islandId");

	loc.type = "none";

	Environment.date.year = 1665;
	Environment.date.month = 9;
	Environment.date.day = 16;
	RecalculateJumpTable();

	SetFunctionLocationCondition("CapBloodLine_ArriweInBridgetown", "Clone_location", false);
	DoReloadCharacterToLocation("Clone_location", "reload", "reload1");
}

void CapBloodLine_ArriweInBridgetown(string qName)
{
	ref sld, rShip;
	string id, model, sex, ani;
	float x, y, z, ay;
	bool bMush;
	int i, rank, group;

	for (i = 1; i <= 46; i++)
	{
		id = "";
		model = "";
		sex = "man";
		ani = "man";
		x = 0.0;
		y = 0.0;
		z = 0.0;
		ay = 0.0;
		bMush = false;
		rank = 10;
		group = -1;

		switch(i)
		{
			// Братишки
			case 1: id = "Pitt_Clone"; model = "Pitt_6"; x = -1.62; y = 2.79; z = 7.80; ay = -1.45; break;
			case 2: id = "Volverston_Clone"; model = "Volverston_6"; x = -1.62; y = 2.79; z = 9.80; ay = -1.45; break;
			case 3: id = "Ogl_Clone"; model = "Ogl_6"; x = -1.62; y = 2.79; z = 11.80; ay = -1.45; break;
			case 4: id = "Dieke_Clone"; model = "Dieke_6"; x = -1.62; y = 2.79; z = 3.80; ay = -1.45; break;
			case 5: id = "Hugtorp_Clone"; model = "Hugtorp_6"; x = -1.62; y = 2.79; z = 1.80; ay = -1.45; break;
			case 6: id = "Picarini"; model = "Jan_Slave"; x = -1.62; y = 2.79; z = -0.80; ay = -1.45; break;
			// Мужики
			case 7: id = "CBLCitizMan_5"; model = "Citiz_18"; x = -8.05; y = 2.72; z = 11.90; ay = 2.17; break;
			case 8: id = "CBLCitizMan_6"; model = "navy_off_eng_1"; x = -7.88; y = 4.99; z = -8.84; ay = 0.17; break;
			case 9: id = "CBLCitizMan_7"; model = "Citiz_7"; x = 4.23; y = 6.17; z = -11.42; ay = -0.17; break;
			case 10: id = "CBLCitizMan_8"; model = "DEDnoName"; x = 4.94; y = 6.03; z = -11.49; ay = -0.17; break;
			case 11: id = "CBLCitizMan_9"; model = "merch_1"; x = 7.81; y = 3.99; z = 9.31; ay = -1.57; break;
			case 12: id = "CBLCitizMan_10"; model = "merch_3"; x = 7.81; y = 3.99; z = 11.11; ay = -1.57; break;
			case 13: id = "CBLCitizMan_11"; model = "Slave_1"; x = 1.87; y = 2.78; z = 11.74; ay = 1.57; break;
			case 14: id = "CBLCitizMan_12"; model = "Slave_6"; x = 1.87; y = 2.78; z = 9.74; ay = 1.57; break;
			case 15: id = "CBLCitizMan_13"; model = "Slave_3"; x = 1.87; y = 2.78; z = 7.74; ay = 1.57; break;
			case 16: id = "CBLCitizMan_14"; model = "Slave_4"; x = 1.87; y = 2.78; z = 5.74; ay = 1.57; break;
			case 17: id = "CBLCitizMan_15"; model = "Slave_5"; x = 1.87; y = 2.78; z = 3.74; ay = 1.57; break;
			case 18: id = "CBLCitizMan_16"; model = "Slave_2"; x = 1.87; y = 2.78; z = 1.74; ay = 1.57; break;
			case 19: id = "CBLCitizMan_17"; model = "Slave_7"; x = 1.87; y = 2.78; z = -0.74; ay = 1.57; break;
			case 20: id = "CBLCitizMan_18"; model = "Nettall"; x = -7.87; y = 3.99; z = 4.54; ay = 1.57; break;
			case 21: id = "CBLCitizMan_19"; model = "citiz_13"; x = -7.27; y = 3.99; z = 2.94; ay = 1.07; break;
			case 22: id = "CBLCitizMan_20"; model = "guard_eng_1"; x = 2.34; y = 6.00; z = -31.02; ay = 0.0; break;
			case 23: id = "CBLCitizMan_21"; model = "guard_eng_2"; x = -0.50; y = 6.00; z = -30.98; ay = 0.0; break;
			case 24: id = "CBLCitizMan_2"; model = "panhandler_2"; x = -8.85; y = 3.98; z = -0.92; ay = 1.17; break; // нищий
			case 25: id = "CBLCitizMan_3"; model = "urban_eng_1"; x = 3.85; y = 2.63; z = 34.14; ay = 1.17; break; // Солдат
			case 26: id = "CBLCitizMan_4"; model = "Citiz_38"; x = -17.47; y = 1.65; z = 16.87; ay = 1.17; break; // Матрос
			case 27: id = "CBLCitizMerch_2"; model = "MarketMan_2"; x = 5.91; y = 2.99; z = -6.40; ay = -1.17; break;
			case 28: id = "CBLCitizMerch_4"; model = "MarketMan_5"; x = -4.86; y = 2.99; z = -8.66; ay = 0.77; break;
			case 29: id = "CBLCitizMan_22"; model = "navy_off_eng_3"; x = -8.69; y = 5.99; z = -17.30; ay = 0.00; break;
			case 30: id = "CBLCitizMan_23"; model = "urban_eng_2"; x = -9.77; y = 5.99; z = -18.68; ay = 0.00; break;
			case 31: id = "CBLCitizMan_24"; model = "urban_eng_3"; x = -7.90; y = 5.99; z = -18.33; ay = 0.00; break;
			// Мушкетёры
			case 32: id = "CBLSoldierMush_1"; model = "urban_mush_eng_3"; x = -3.87; y = 2.99; z = -5.80; ay = -5.87; break;
			case 33: id = "CBLSoldierMush_2"; model = "urban_mush_eng_1"; x = -6.37; y = 2.99; z = 4.79; ay = -4.80; break;
			case 34: id = "CBLSoldierMush_3"; model = "urban_mush_eng_2"; x = 0.00; y = 2.63; z = 15.29; ay = -3.00; break;
			case 35: id = "CBLSoldierMush_4"; model = "urban_mush_eng_4"; x = 6.37; y = 2.99; z = 7.79; ay = -1.80; break;
			case 36: id = "CBLSoldierMush_5"; model = "urban_mush_eng_5"; x = 3.87; y = 2.99; z = -5.80; ay = -0.87; break;
			// Женщины
			case 37: id = "CBLCitizWoman_1"; model = "Women_1"; x = -7.90; y = 2.78; z = 10.94; ay = 1.87; break;
			case 38: id = "CBLCitizWoman_2"; model = "Women_5"; x = -7.11; y = 2.72; z = 11.90; ay = 1.87; break;
			case 39: id = "CBLCitizWoman_3"; model = "Mary_Trail"; x = -7.88; y = 4.99; z = -7.44; ay = 3.17; break;
			case 40: id = "CBLCitizWoman_4"; model = "CitizenWom_2"; x = 3.44; y = 6.23; z = -11.49; ay = -0.17; break;
			case 41: id = "CBLCitizWoman_5"; model = "Women_10"; x = 9.06; y = 3.20; z = 12.47; ay = -0.17; break; // уходит
			case 42: id = "CBLCitizWoman_6"; model = "horse04"; x = 7.68; y = 4.99; z = -6.77; ay = 0.57; break;
			case 43: id = "CBLCitizWoman_7"; model = "horse05"; x = 8.57; y = 4.99; z = -5.51; ay = -2.57; break;
			case 44: id = "CBLCitizWoman_8"; model = "horse06"; x = 9.23; y = 4.99; z = -7.07; ay = -1.37; break;
			case 45: id = "CBLCitizMerch_1"; model = "MarketGirl_1"; x = -6.27; y = 2.99; z = -2.19; ay = 1.37; break;
			case 46: id = "CBLCitizMerch_3"; model = "MarketGirl_4"; x = 6.34; y = 2.99; z = -2.54; ay = -1.77; break;
		}
		if (i >= 32 && i <= 36)
		{
			sex = "man";
			ani = "mushketer";
		}
		else if (i >= 37 && i <= 46)
		{
			sex = "woman";
			ani = "towngirl";
		}
		sld = GetCharacter(NPC_GenerateCharacter(id, model, sex, ani, rank, ENGLAND, group, false));
		if (i >= 32 && i <= 36)
		{
			GiveItem2Character(sld, "mushket");
			EquipCharacterbyItem(sld, "mushket");
		}
		LAi_SetStayType(sld);
		sld.lifeDay = 0;
		LAi_CharacterDisableDialog(sld);
		ChangeCharacterAddressGroup(sld, "Clone_location", "goto", "goto1");
		TeleportCharacterToPosAy(sld, x, y, z, ay);
	}

	sld = GetCharacter(NPC_GenerateCharacter("CBLCitizMan_1", GetUniqCarrierModel("carrier_city"), "man", "genres", 10, ENGLAND, -1, false));
	ChangeCharacterAddressGroup(sld, "Clone_location", "goto", "goto10");
	sld.gotoGroup = "reload";
	sld.gotoLocator = "reload4_back";
	sld.lifeDay = 0;
	LAi_SetCarrierType(sld);

	sld = CharacterFromID("CBLCitizMan_2");
	LAi_SetGroundSitType(sld);

	sld = CharacterFromID("CBLCitizMan_3");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload3_back", "none", "", "", "", -1);

	sld = CharacterFromID("CBLCitizMan_4");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload5_back", "none", "", "", "", -1);

	sld = CharacterFromID("CBLCitizWoman_5");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "gate_back", "none", "", "", "", -1);

	ref officer = CharacterFromID("CBLCitizMan_22");
	LAi_SetActorType(officer);
	LAi_ActorGoToLocator(officer, "goto", "goto15", "CapBloodLine_OfficerTurnToLoc", -1);

	sld = CharacterFromID("CBLCitizMan_23");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, officer, "", -1);

	sld = GetCharacter(NPC_GenerateCharacter("Jamaican_Merchant", "merch_11", "man", "man", 15, ENGLAND, -1, true));
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, "", CANNON_TYPE_CANNON_LBS20, 40, 35, 25);
	RealShips[sti(sld.Ship.Type)].ship.upgrades.hull = "4";
	rShip = GetRealShip(sti(sld.Ship.Type));
	CreateEntity(sld, "ship");
	Ship_SetLightsAndFlares(sld);
	sld.Ship.Pos.x = -10.55;
	sld.Ship.Pos.z = 61.37;
	sld.Ship.Ang.y = GetAngleY(-1.5,1.0);
	sld.Ship.stopped = true;
	sld.Ship.Speed.z = 0.0;
	Ship_PrepareShipForLocation(sld);
	SendMessage(sld, "laa", MSG_SHIP_CREATE, sld, rShip);

	Environment.date.year = 1665; // Второй раз, чтобы раскинуть скорость загрузок локаций после промотки большого количества времени
	Environment.date.month = 12;
	Environment.date.day = 16;
	RecalculateJumpTable();
	SetCurrentTime(12, 1);
	RefreshLandTime();

	TeleportCharacterToPosAy(pchar, -1.62, 2.79, 5.80, -1.45);
	LAi_SetActorType(pchar);

	LAi_FadeEx(0.1, 1.0, 1.5, "", "CapBloodLine_SeaCameraWiew", "");
	StartQuestMovie(true, false, true);
}

void CapBloodLine_SeaCameraWiew(string qName)
{
	LAi_MethodDelay("FadeDelay", 0.1);
	PlaySound("Music\Sea\Night\Sea_night_teho.ogg");
	locCameraFromToPos(-50.95, 15.77, 33.18, true, -25.05, 7.55, 50.9);
	DoQuestFunctionDelay("CapBloodLine_SeaCameraWiew_1", 4.0);
	DoQuestFunctionDelay("CapBloodLine_MusicRestart", 58.0);
	pchar.questTemp.CapBloodLine_MusicRestart = true;
	pchar.questTemp.CBL.Shipyard = true;
}

void CapBloodLine_MusicRestart(string qName)
{
	if (!CheckAttribute(pchar, "questTemp.CapBloodLine_MusicRestart")) return;
	PlaySound("Music\Sea\Night\Sea_night_teho.ogg");
	DoQuestFunctionDelay("CapBloodLine_MusicRestart", 58.0);
}

void CapBloodLine_SeaCameraWiew_1(string qName)
{
	LAi_FadeEx(1.0, 1.0, 1.0, "CapBloodLine_SeaCameraWiew_2", "", "");
}

void CapBloodLine_SeaCameraWiew_2(string qName)
{
	locCameraSleep(false);
	locCameraFromToPos(11.21, 10.55, -5.25, true, 0.05, 3.55, 6.0);
	DoQuestFunctionDelay("CapBloodLine_SeaCameraWiew_3", 4.0);
}

void CapBloodLine_SeaCameraWiew_3(string qName)
{
	LAi_FadeEx(1.0, 1.0, 1.0, "", "CapBloodLine_SeaCameraWiew_4", "");
}

void CapBloodLine_SeaCameraWiew_4(string qName)
{
	locCameraFlyToPositionLookToPoint(-2.31, 4.49, 14.30, -2.31, 4.49, -0.34, -2.31, 4.49, -0.34, 1, 4550/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_SeaCameraWiew_5";

	ref sld = GetCharacter(NPC_GenerateCharacter("Stid_Clone", "huber_11", "man", "man", 10, ENGLAND, -1, false));
	sld.lifeDay = 0;
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.Dialog.CurrentNode = "SOnSquere";
	LAi_CharacterDisableDialog(sld);
	ChangeCharacterAddressGroup(sld, "Clone_location", "goto", "goto1");
	TeleportCharacterToPosAy(sld, 2.10, 2.79, -17.56, -0.85);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest4", "CapBloodLine_Stid_GoFurder", -1);

	sld = GetCharacter(NPC_GenerateCharacter("FluitCap", "Citiz_10", "man", "man", 10, ENGLAND, -1, false));
	sld.lifeDay = 0;
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.Dialog.CurrentNode = "SOnSquere";
	LAi_CharacterDisableDialog(sld);
	ChangeCharacterAddressGroup(sld, "Clone_location", "goto", "goto1");
	TeleportCharacterToPosAy(sld, 3.06, 2.79, -16.52, -0.85);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest3", "CapBloodLine_FluitCap_GoFurder", -1);

	sld = GetCharacter(NPC_GenerateCharacter("Bishop_Clone", "huber_0", "man", "man", 1, ENGLAND, 3, false));
	sld.name 	= FindPersonalName("Bishop_name");
	sld.lastname 	= FindPersonalName("Bishop_lastname");
	sld.lifeDay = 0;
	sld.Dialog.CurrentNode = "SOnSquere";
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	LAi_CharacterDisableDialog(sld);
	ChangeCharacterAddressGroup(sld, "Clone_location", "goto", "goto1");
	TeleportCharacterToPosAy(sld, 5.74, 2.79, -18.78, -0.85);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest3", "CapBloodLine_Bishop_GoFurder", -1);

	sld = GetCharacter(NPC_GenerateCharacter("Arabella", "Arabella_h", "woman", "towngirl", 10, ENGLAND, -1, false));
	sld.name 	= FindPersonalName("Arabella_name");
	sld.lastname 	= FindPersonalName("Bishop_lastname");
	LAi_CharacterDisableDialog(sld);
	ChangeCharacterAddressGroup(sld, "Clone_location", "goto", "goto1");
	TeleportCharacterToPosAy(sld, 5.00, 2.83, -19.49, -0.85);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest4", "CapBloodLine_Arabella_GoFurder", -1);
}

void CapBloodLine_SeaCameraWiew_5()
{
	locCameraSleep(true);
	LAi_FadeEx(2.0, 1.0, 1.0, "", "CapBloodLine_SeaCameraWiew_6", "");
}

void CapBloodLine_SeaCameraWiew_6(string qName)
{
	locCameraSleep(false);
	locCameraFromToPos(0.25, 5.46, 5.94, true, -10.05, 0.05, 10.2);

	ref sld = CharacterFromID("FluitCap");
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest10");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest11", "CapBloodLine_FluitCapTurnToStid", -1.0);

	sld = CharacterFromID("Stid_Clone");
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest14");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest13", "CapBloodLine_StidCapTurnToFluit", - 1.0);

	sld = CharacterFromID("Bishop_Clone");
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest7");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest10", "CapBloodLine_BishopDialogWithFluitCap", - 1.0);

	sld = CharacterFromID("Arabella");
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest8");
	LAi_SetStayType(sld);
	CharacterTurnByChr(sld, pchar);
	DoQuestFunctionDelay("CapBloodLine_ArabellaGoToStid", 1.5);

	sld = GetCharacter(NPC_GenerateCharacter("CBLDialogNPC", "merch_13", "man", "man", 1, ENGLAND, 3, false));
	sld.name 	= FindPersonalName("BishopAndGardner");
	sld.lastname 	= "";
	sld.Dialog.CurrentNode = "SOnSquere";
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest8");
	sld.lifeDay = 0;
	TeleportCharacterToPosAy(sld, -11.97, 3.99, 5.34, -0.85);
}

void CapBloodLine_ArabellaGoToStid(string qName)
{
	ref sld = CharacterFromID("Arabella");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest14", "CapBloodLine_ArabellaTurnToFluit", - 1.0);
}

void CapBloodLine_SeaCameraWiew_7(string qName)
{
	locCameraFromToPos(-0.23, 5.44, 12.17, true, -13.05, -2.55, 0.2);
}

void CapBloodLine_ArabellaWantBuyBlood()
{
	ref sld = CharacterFromID("Bishop_Clone");

	ref arabella = CharacterFromID("Arabella");
	LAi_SetActorType(arabella);
	LAi_ActorFollow(arabella, sld, "CapBloodLine_ArabellaWantBuyBlood_1", -1);
	locCameraFromToPos(-0.23, 5.44, 12.17, true, -13.05, -2.55, 0.2);

	ref stid = CharacterFromID("Stid_Clone");
	TeleportCharacterToPosAy(stid, -7.13, 2.99, 14.15, 14.15);
	LAi_SetActorType(stid);
	LAi_ActorFollow(stid, sld, "CapBloodLine_StidTurnToBishop", -1);
}

void CapBloodLine_AllBandNearBlood(string qName)
{
	locCameraFromToPos(-5.21, 5.40, 8.11, true, 2.55, -0.55, 0.2);
	ref sld = CharacterFromID("FluitCap");
	LAi_SetStayType(sld);
	TeleportCharacterToPosAy(sld, -3.13, 2.99, 7.05, 3.15);

	sld = CharacterFromID("Bishop_Clone");
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest9");
	CharacterTurnByChr(sld, pchar);

	sld = CharacterFromID("Stid_Clone");
	LAi_SetStayType(sld);
	TeleportCharacterToPosAy(sld, -4.13, 2.99, 5.55, 1.25);

	sld = CharacterFromID("Arabella");
	LAi_SetStayType(sld);
	TeleportCharacterToPosAy(sld, -4.13, 2.99, 6.55, 1.95);

	DoQuestFunctionDelay("CapBloodLine_AllBandNearBlood_1", 1.0);
}

void CapBloodLine_AllBandNearBlood_1(string qName)
{
	ref sld = CharacterFromID("CBLDialogNPC");
	sld.dialog.currentNode = "SOnSquere_12";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);

	CharacterTurnByChr(CharacterFromID("Arabella"), CharacterFromID("Bishop_Clone"));
	CharacterTurnByChr(CharacterFromID("Bishop_Clone"), CharacterFromID("Arabella"));
}

void CapBloodLine_AllBandNearBlood_2(string qName)
{
	ref sld = CharacterFromID("CBLDialogNPC");
	sld.name = FindPersonalName("BishopAndGardner");
	sld.dialog.currentNode = "SOnSquere_15";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void CapBloodLine_AllBandNearBlood_3(string qName)
{
	ref sld = CharacterFromID("CBLDialogNPC");
	sld.name = FindPersonalName("Governor_Stid");
	sld.dialog.currentnode = "SOnSquere_18";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void CapBloodLine_AllBandNearBlood_4(string qName)
{
	ref sld = CharacterFromID("CBLDialogNPC");
	sld.name = FindPersonalName("BishopAndGardner");
	sld.dialog.currentnode = "SOnSquere_20";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void CapBloodLine_AllBishopsGroupGoAway()
{
	ref bishop = CharacterFromID("Bishop_Clone");
	LAi_SetActorType(bishop);
	LAi_ActorGoToLocator(bishop, "goto", "goto9", "", -1);

	ref sld = CharacterFromID("Arabella");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, bishop, "", -1);

	sld = CharacterFromID("Stid_Clone");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, bishop, "", -1);

	sld = CharacterFromID("FluitCap");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, bishop, "", -1);
}

void CapBloodLine_AllBishopsGroupGoAway_1(string qName)
{
	LAi_FadeEx(2.0, 1.0, 1.0, "", "CapBloodLine_EndSquereScene", "");
	DeleteAttribute(pchar, "questTemp.CapBloodLine_MusicRestart");
	pchar.questTemp.CapBloodSeeArabella = true; // На всякий случай
}

void CapBloodLine_EndSquereScene(string qName)
{
	// DeleteAttribute(pchar, "questTemp.NoFast");
	EndQuestMovie();
	locCameraTarget(pchar);
	locCameraFollow();
	LAi_SetPlayerType(pchar);

	// Первый квест

	pchar.quest.onPlantation.win_condition.l1          = "location";
	pchar.quest.onPlantation.win_condition.l1.location = "BridgeTown_Plantation";
	pchar.quest.onPlantation.function                  = "CapBloodLine_q1";

	//квест ночной, поэтому так вот               //TODO
	int n= FindLocation("Bridgetown_town");  // не забыть вернуть
	locations[n].reload.l3.close_for_night = false;

	ref loc = &locations[FindLocation("Bridgetown_plantation")];
	loc.locators_radius.quest.detector2 = 3.0;
	//для энкаунтеров в джанглах
	bDisableLandEncounters = true;
	DoReloadCharacterToLocation("Bridgetown_Plantation", "goto", "goto1");
}

void CapBloodLine_MetArabella(string qName)
{
	ResetTimeScale();
	TEV.StopTimeScale = 1;

	ref sld = GetCharacter(NPC_GenerateCharacter("Slave_Arabella", "Slave_1", "man", "man", 1, ENGLAND, -1, false));
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
	TeleportCharacterToPosAy(sld, -10.38, 6.12, -44.73, 0.0);
	sld.lifeDay = 0;

	sld = GetCharacter(NPC_GenerateCharacter("Slave_Arabella_1", "Slave_2", "man", "man", 1, ENGLAND, 3, false));
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
	TeleportCharacterToPosAy(sld, -8.38, 6.12, -44.73, 0.0);
	sld.lifeDay = 0;

	sld = CharacterFromID("Arabella");
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.dialog.currentNode = "ArabellaOnPlantation";
	ChangeCharacterAddressGroup(sld, "Bridgetown_plantation", "reload", "reload1_back");
	TeleportCharacterToPosAy(sld, -9.38, 5.8, -43.72, 0.0);
	LAi_SetStayType(pchar);
	pchar.GenQuest.CantRun = true;
	sld.GenQuest.CantRun = true;
	// sld.lifeDay = 0;

	DoQuestFunctionDelay("CapBloodLine_CameraFlyToArabella", 0.1); // Отдельно, чтобы камера не баговалась
	QuestPointerDelLoc("Bridgetown_plantation", "reload", "reload1_back"); // Временно удалить, чтобы не маячил
}

void CapBloodLine_CameraFlyToArabella(string qName)
{
	locCameraFlyToPositionLookToPoint(-9.59, 7.07, -34.41, -9.48, 7.03, -41.23, -9.48, 7.03, -41.23, 1, 550/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_CameraSleep";
	DoQuestFunctionDelay("CapBloodLine_ArabellaGoToBlad", 3.0);
}

void CapBloodLine_ArabellaGoToBlad(string qName)
{
	locCameraSleep(false);
	ref arabella = CharacterFromID("Arabella");
	LAi_CharacterEnableDialog(arabella);
	LAi_SetActorType(pchar);
	LAi_ActorFollow(pchar, arabella, "CapBloodLine_ArabellaOnPlantation", -1);
	LAi_SetActorType(arabella);
	LAi_ActorFollow(arabella, pchar, "", -1);

	ref sld = CharacterFromID("Slave_Arabella");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, arabella, "", -1);

	sld = CharacterFromID("Slave_Arabella_1");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, arabella, "", -1);
}

void CapBloodLine_ArabellaSlaveSitDown()
{
	ref sld = CharacterFromID("Slave_Arabella");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "Ground_SitDown", "CapBloodLine_ArabellaSlaveSitDown_1", 2.2);
}

void CapBloodLine_ArabellaSlaveSitDown_2(string qName)
{
	ref sld = CharacterFromID("Slave_Arabella_1");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "Ground_SitDown", "CapBloodLine_ArabellaSlaveSitDown_3", 2.2);
}

void CapBloodLine_ArabellaGoHome()
{
	ref sld = CharacterFromID("Arabella");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "houseSp1", "none", "", "", "", -1);

	sld = CharacterFromID("Slave_Arabella");
	LAi_ActorAnimation(sld, "Ground_StandUp_Fast", "CapBloodLine_ArabellaGoHome_1", 1.0);

	sld = CharacterFromID("Slave_Arabella_1");
	LAi_ActorAnimation(sld, "Ground_StandUp_Fast", "", 1.0);

	chrDisableReloadToLocation = false;
	DeleteAttribute(&TEV, "StopTimeScale");
	DeleteAttribute(pchar, "GenQuest.CantRun");
	LAi_SetPlayerType(pchar);
	SetFunctionExitFromLocationCondition("CapBloodLine_DelayArabellaAndSlave", PChar.location, false);
	QuestPointerToLoc("Bridgetown_plantation", "reload", "reload1_back");
	AddQuestRecord("Arabella", "2");

	sld = CharacterFromID("Bridgetown_Mayor");
	sld.dialog.currentnode = "Pride_Arrive";
	AddLandQuestmark_Main(sld, "CapBloodLine");
	QuestPointerToLoc("Bridgetown_town", "reload", "reload3_back");
}

void CapBloodLine_DelayArabellaAndSlave(string qName)
{
	ref sld = CharacterFromID("Arabella");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	QuestPointerDelLoc("Bridgetown_plantation", "reload", "reload1_back");

	LocatorReloadEnterDisable("Bridgetown_Shipyard", "reload2", true);
}

void CapBloodLine_InPackhouse(string qName)
{
	ref sld;
	string id, model, animType;
	float x, y, z, ay;
	int i;

	for (i = 1; i <= 6; i++)
	{
		id = "CBL_Matros_" + i;
		model = "";
		animType = "";
		x = 0.0; y = 0.05; z = -9.37; ay = 0.0;

		switch (i)
		{
			case 1: model = "barmen_1"; x =  7.65; ay = 0.2; animType = "sit";     break;
			case 2: model = "Citiz_50"; x =  4.65; ay = 3.2; animType = "lay";     break;
			case 3: model = "Citiz_49"; x =  1.65; ay = 3.2; animType = "dead";    break;
			case 4: model = "Citiz_48"; x = -1.65; ay = 0.2; animType = "sitdead"; break;
			case 5: model = "Citiz_42"; x = -4.65; y = 0.10; ay = 3.2; animType = "dead"; break;
			case 6: model = "barmen_9"; x = -7.65; ay = 3.2; animType = "lay";     break;
		}

		sld = GetCharacter(NPC_GenerateCharacter(id, model, "man", "man", 1, ENGLAND, 3, false));
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		TeleportCharacterToPosAy(sld, x, y, z, ay);
		LAi_CharacterDisableDialog(sld);
		sld.lifeDay = 0;

		switch (animType)
		{
			case "sit":
				LAi_SetSitPoorAnimation(sld);
			break;

			case "lay":
				LAi_SetLayType(sld);
			break;

			case "dead":
				SetCharacterActionAnimation(sld, "dead", "lay_2");
				LAi_KillCharacter(sld);
			break;

			case "sitdead":
				LAi_SetSitPoorAnimation(sld);
			break;
		}
	}

	for (i = 1; i <= 4; i++)
	{
		id = "";
		model = "";
		x = 0.0; y = 0.0; z = 0.0; ay = 0.0;

		switch (i)
		{
			case 1: id = "CBL_PackhouseGuard_Mush1"; model = "urban_mush_eng_3"; break;
			case 2: id = "CBL_PackhouseGuard_Mush2"; model = "urban_mush_eng_1"; x = -0.65; y = 3.94; z = -0.03; ay = 3.2; break;
			case 3: id = "CBL_PackhouseGuard_Sold1"; model = "urban_eng_2";      x =  9.59; y = 3.94; z = -3.75; ay = -1.5; break;
			case 4: id = "CBL_PackhouseGuard_Sold2"; model = "urban_eng_3";      x =  9.59; y = 3.94; z = -7.40; ay = -1.5; break;
		}
		if (i <= 2)
		{
			sld = GetCharacter(NPC_GenerateCharacter(id, model, "man", "mushketer", 10, ENGLAND, -1, true));
			GiveItem2Character(sld, "mushket");
			EquipCharacterbyItem(sld, "mushket");
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter(id, model, "man", "man", 10, ENGLAND, -1, true));
			FantomMakeCoolFighter(sld, 25, 30, 30, "blade26", "pistol3", 20);
		}
		sld.CityType = "soldier";
		sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
		sld.Dialog.CurrentNode = "First Time";
		sld.lifeDay = 0;
		ChangeCharacterAddressGroup(sld, "Bridgetown_Packhouse", "goto", "goto7");

		if (i == 1)
		{
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto9", "Pachouse_Mush_Trip", -1);
		}
		else
		{
			TeleportCharacterToPosAy(sld, x, y, z, ay);
			LAi_SetStayType(sld);
		}
	}

	for (i = 1; i <= 6; i++)
	{
		string sQuest = "CapBloodLine_InPackhouse_Quest0" + i;
		string sLoc = "quest0" + i;

		pchar.quest.(sQuest).win_condition.l1 = "locator";
		pchar.quest.(sQuest).win_condition.l1.location = "Bridgetown_Packhouse";
		pchar.quest.(sQuest).win_condition.l1.locator_group = "quest";
		pchar.quest.(sQuest).win_condition.l1.locator = sLoc;
		pchar.quest.(sQuest).function = "CapBloodLine_InPackhouse_1";
	}

	chrDisableReloadToLocation = true;
	InterfaceStates.Buttons.Save.enable = false;
	DoQuestCheckDelay("CapBloodLine_InPackhouse_DeleteGuard", 0.1);
	LAi_LocationFightDisable(&Locations[FindLocation("Bridgetown_Packhouse")], true);
}

void CapBloodLine_InPackhouse_1(string qName)
{
	string sLoc = "";

	switch (qName)
	{
		case "CapBloodLine_InPackhouse_Quest01": sLoc = "quest01"; break;
		case "CapBloodLine_InPackhouse_Quest02": sLoc = "quest02"; break;
		case "CapBloodLine_InPackhouse_Quest03": sLoc = "quest03"; break;
		case "CapBloodLine_InPackhouse_Quest04": sLoc = "quest04"; break;
		case "CapBloodLine_InPackhouse_Quest05": sLoc = "quest05"; break;
		case "CapBloodLine_InPackhouse_Quest06": sLoc = "quest06"; break;
	}

	pchar.questTemp.CapBloodLine.PackhouseLocator = sLoc;

	LAi_SetActorType(pchar);
	CharacterTurnAy(pchar, 1.5);
	LAi_FadeEx(0.5, 0.5, 0.5, "", "CapBloodLine_InPackhouse_2", "");
}

void CapBloodLine_InPackhouse_2(string qName)
{
	LAi_ActorAnimation(pchar, "Barman_idle", "CapBloodLine_InPackhouse_return", 5);

	if (CheckAttribute(pchar, "questTemp.CapBloodLine.PackhouseLocator"))
	{
		string sLoc = pchar.questTemp.CapBloodLine.PackhouseLocator;
		if (CheckAttribute(pchar, "questTemp.CapBloodLine.PackhouseDone." + sLoc)) return;
		pchar.questTemp.CapBloodLine.PackhouseDone.(sLoc) = true;
		QuestPointerDelLoc("Bridgetown_Packhouse", "quest", sLoc);
		if (!CheckAttribute(pchar, "questTemp.CapBloodLine.PackhouseSickCount"))
		{
			pchar.questTemp.CapBloodLine.PackhouseSickCount = 0;
		}
		pchar.questTemp.CapBloodLine.PackhouseSickCount = sti(pchar.questTemp.CapBloodLine.PackhouseSickCount) + 1;
		if (sti(pchar.questTemp.CapBloodLine.PackhouseSickCount) == 1)
		{
			DoQuestFunctionDelay("CapBloodLine_InPackhouse_4", 3.5);
		}
		if (sti(pchar.questTemp.CapBloodLine.PackhouseSickCount) == 5)
		{
			DoQuestFunctionDelay("CapBloodLine_InPackhouse_5", 5.0);
		}
		if (sti(pchar.questTemp.CapBloodLine.PackhouseSickCount) == 6)
		{
			DoQuestFunctionDelay("CapBloodLine_InPackhouse_7", 10.0);
			DoQuestFunctionDelay("CapBloodLine_InPackhouse_9", 5.0);
		}
		if (sLoc == "quest01")
		{
			TeleportCharacterToPosAy(pchar, 6.57, 0.00, -9.41, 1.5);
			locCameraFromToPos(9.90, 1.86, -7.91, true, -3.05, -4.85, -13.9);
		}
		else if (sLoc == "quest02")
		{
			TeleportCharacterToPosAy(pchar, 3.57, 0.00, -9.41, 1.5);
			locCameraFromToPos(6.90, 1.86, -7.91, true, -3.05, -3.85, -11.9);
		}
		else if (sLoc == "quest03")
		{
			TeleportCharacterToPosAy(pchar, 0.57, 0.00, -9.41, 1.5);
			locCameraFromToPos(3.90, 1.86, -7.91, true, -3.05, -2.55, -10.9);
		}
		else if (sLoc == "quest04")
		{
			TeleportCharacterToPosAy(pchar, -2.57, 0.00, -9.41, 1.5);
			locCameraFromToPos(0.90, 1.86, -7.91, true, -3.05, -1.25, -9.9);
		}
		else if (sLoc == "quest05")
		{
			TeleportCharacterToPosAy(pchar, -5.57, 0.00, -9.41, 1.5);
			locCameraFromToPos(-1.90, 1.86, -7.91, true, -9.95, -2.55, -10.9);
		}
		else if (sLoc == "quest06")
		{
			TeleportCharacterToPosAy(pchar, -8.87, 0.00, -9.41, 1.5);
			locCameraFromToPos(-4.90, 1.86, -7.91, true, -9.95, -1.55, -9.9);
		}
		DeleteAttribute(pchar, "questTemp.CapBloodLine.PackhouseLocator");
	}
}

void CapBloodLine_InPackhouse_3(string qName)
{
	LAi_SetPlayerType(pchar);
	locCameraTarget(pchar);
	locCameraFollow();
}

void CapBloodLine_InPackhouse_4(string qName)
{
	ref  sld = GetCharacter(NPC_GenerateCharacter("Bishop", "huber_0", "man", "man", 1, ENGLAND, -1, false));
	sld.name 	= FindPersonalName("Bishop_name");
	sld.lastname 	= FindPersonalName("Bishop_lastname");
	sld.Dialog.CurrentNode = "Bishop_Packhouse";
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.greeting = "Gr_Bishop";
	sld.GenQuest.CantRun = true; // Чтобы не бегал, как мальчишка

	SetSPECIAL(sld, 9,8,10,3,6,10,4);
	InitStartParam(sld);
	SetEnergyToCharacter(sld);

	GiveItem2Character(sld, "blade22");
	EquipCharacterByItem(sld, "blade22");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterByItem(sld, "pistol2");
	LAi_SetImmortal(sld, true);

	ChangeCharacterAddressGroup(sld, "BridgeTown_Packhouse", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CapBloodLine_InPackhouse_5(string qName)
{
	ref sld = CharacterFromID("Arabella");
	sld.dialog.currentnode = "ArabellaOnPackhouse";
	ChangeCharacterAddressGroup(sld, "BridgeTown_Packhouse", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 6.37, 0.00, -6.84, -1.5);

	sld = GetCharacter(NPC_GenerateCharacter("Slave_Arabella_2", "Slave_1", "man", "man", 1, ENGLAND, 0, false));
	sld.name 	= FindPersonalName("AralellaAndSlave_name");
	sld.lastname 	= "";
	sld.Dialog.CurrentNode = "ArabellaAndSlave";
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	ChangeCharacterAddressGroup(sld, "BridgeTown_Packhouse", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 7.22, 0.00, -4.91, -1.5);
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);

	sld = GetCharacter(NPC_GenerateCharacter("Slave_Arabella_3", "Slave_2", "man", "man", 1, ENGLAND, 0, false));
	ChangeCharacterAddressGroup(sld, "BridgeTown_Packhouse", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 8.04, 0.00, -6.02, -1.5);
	pchar.GenQuest.CantRun = true;
}

void CapBloodLine_InPackhouse_7(string qName)
{
	SetLaunchFrameFormParam(StringFromKey("Bishop_591"), "CapBloodLine_InPackhouse_8", 0, 3);
	LaunchFrameForm();
	bQuestCheckProcessFreeze = true;
	WaitDate("", 0, 0, 20, 0, 0);
	bQuestCheckProcessFreeze = false;
	RecalculateJumpTable();
	RefreshLandTime();
	LAi_MethodDelay("LaunchFrameForm", 0);

	ref sld = CharacterFromID("Arabella");
	if (CharacterIsHere(sld))
	{
		ChangeCharacterAddressGroup(sld, "none", "", "");
		ChangeCharacterAddressGroup(CharacterFromID("Slave_Arabella_2"), "none", "", "");
		ChangeCharacterAddressGroup(CharacterFromID("Slave_Arabella_3"), "none", "", "");
	}
}
void CapBloodLine_InPackhouse_9(string qName)
{
	AddQuestRecord("CapBloodLine_q1", "10");
	SetCharacterPerk(pchar, "Doctor2");
	LogSound_WithNotify(StringFromKey("Bishop_592"), "", "Ship abilities");
	AddCharacterExpToSkill(PChar, SKILL_LEADERSHIP, 100);
	AddCharacterExpToSkill(PChar, SKILL_DEFENCE, 30);
	RemoveItems(pchar, "MedicalSupplies", 1);

	ref sld = CharacterFromID("Bridgetown_Shipyarder");
	sld.questTemp.BloogEndTreatment = true;
	sld.dialog.currentnode = "first time";
	if (CheckAttribute(sld, "questTemp.BloogGoToPackhouse")) DeleteAttribute(sld, "questTemp.BloogGoToPackhouse");
}

void CapBloodLine_ClearPackhouse(string qName)
{
	LocatorReloadEnterDisable("Bridgetown_Shipyard", "reload2", true);

	ref loc = &Locations[FindLocation("Bridgetown_Packhouse")];
	DeleteAttribute(loc, "models.always.rugs");
	loc.models.day.charactersPatch = "angar_patch";
	loc.models.night.charactersPatch = "angar_patch";
	InterfaceStates.Buttons.Save.enable = true;
}

void CapBloodLine_ArabellaInTown(string qName)
{
	ref sld = CharacterFromID("Arabella");
	sld.dialog.currentnode = "ArabellaOnPirs";
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "Bridgetown_Town", "reload", "reload1");
	TeleportCharacterToPosAy(sld, 9.80, 2.63, 15.35, 0.0);
	AddLandQuestmark_Main(sld, "CapBloodLine");

	QuestPointerDelLoc("Bridgetown_Shipyard", "reload", "reload1_back");
	QuestPointerDelLoc("Bridgetown_Packhouse", "reload", "reload1");
	AddQuestRecord("Arabella", "4");
	chrDisableReloadToLocation = true;
	ChangeBridgeTownDialogs(false);
	SetFunctionLocationConditionDelay("CapBloodLine_ReturnCitizenDialogAgain", "Bridgetown_town", false, 0.2);
}

void CapBloodLine_CloseTavernRoom(string qName)
{
	ref loc = &Locations[FindLocation("Bridgetown_tavern")];
	loc.reload.l2.disable = true;
}

void CapBloodLine_ReturnCitizenDialogAgain(string qName)
{
	ChangeBridgeTownDialogs(false); // Заново, из-за перемотки времени
}

void CapBloodLine_BishopWaitBlood(string qName) // При входе на плантацию встретит солдат
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Bishop_soldier", "urban_eng_2", "man", "man", 1, ENGLAND, 0, false));
	FantomMakeCoolFighter(sld, 20, 90, 90, "blade26", "pistol4", 120);
	sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
	sld.dialog.currentnode = "Sold_Wait_Blad";
	ChangeCharacterAddressGroup(sld, "Bridgetown_plantation", "goto", "goto18");
	TeleportCharacterToPosAy(sld, -1.00, 1.10, 68.52, -3.2);
	LAi_SetStayType(sld);
	sld.talker = 10;
	AddLandQuestmark_Main(sld, "CapBloodLine");

	sld = CharacterFromID("Pitt");
	ChangeCharacterAddressGroup(sld, "none", "", ""); // сюда

	string sChars[5];
	sChars[0] = "Ogl";
	sChars[1] = "Volverston";
	sChars[2] = "Hugtorp";
	sChars[3] = "Dieke";
	sChars[4] = "Slave_Quest";

	for (int i = 0; i < 5; i++)
	{
		if (GetCharacterIndex(sChars[i]) != -1)
		{
			sld = CharacterFromID(sChars[i]);
			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
	}
	QuestPointerToLoc("Bridgetown_Plantation", "reload", "HouseG6");
}

void CapBloodLine_DelBishopsQuestPointer(string qName)
{
	QuestPointerDelLoc("Bridgetown_Plantation", "goto", "goto19");
}

void CapBloodLine_FailQuest(string qName)
{
	aref arFader;
	if (procEnableInterfaceLaunch(INTERFACE_FRAMEFORM) == false || GetEntity(arFader, "fader"))
	{
		DoQuestFunctionDelay("CapBloodLine_FailQuest", 1.0);
		return;
	}

	InterfaceStates.Buttons.Save.enable = false;
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_245"), "Run_Function", 0.1, 4.0);
	SetLaunchFrameRunFunctionParam("CapBloodLine_q2_Late_GameOver", 0.0);
	LaunchFrameForm();
}

void CapBloodLine_ReloadToStid(string qName)
{
	DoQuestReloadToLocation("Bridgetown_Townhall", "reload", "reload1_back", "");
	SetFunctionLocationCondition("CapBloodLine_ReloadToStid_2", "Bridgetown_Townhall", false);
	DeleteQuestCondition("CapBloodLine_FailQuest");
}

void CapBloodLine_ReloadToStid_2(string qName)
{
	LocatorReloadEnterDisable("Bridgetown_Townhall", "reload1_back", true);
	LocatorReloadEnterDisable("Bridgetown_TownhallRoom", "reload3", true);
	bDisableFastReload = false;
	TeleportCharacterToPosAy(pchar, -0.09, 0.00, 6.9, 3.2);

	ref sld = CharacterFromID("Bishop");
	ChangeCharacterAddressGroup(sld, "none", "", "");

	sld = CharacterFromID("CBL_Kent");
	ChangeCharacterAddressGroup(sld, "none", "", "");

	sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
	ChangeCharacterAddressGroup(sld, "none", "", "");

	SetFunctionLocationCondition("CapBloodLine_InStidBedroom", "commonBedroom", false);
	locations[FindLocation("commonBedroom")].locators_radius.goto.goto6 = 1.0;
	QuestPointerToLoc("Bridgetown_townhall", "reload", "reload3");
	QuestPointerToLoc("Bridgetown_townhallRoom", "reload", "reload2");
}

void CapBloodLine_InStidBedroom(string qName)
{
	string sTemp;
	LAi_LocationFightDisable(LoadedLocation, true);
	chrDisableReloadToLocation = true;

	ref sld = GetCharacter(NPC_GenerateCharacter("Stid_Clone_1", "huber_11", "man", "man", 10, ENGLAND, -1, false));
	sld.name = FindPersonalName("Bridgetown_Mayor_name");
	sld.lastname = FindPersonalName("Bridgetown_Mayor_lastname");
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	ChangeCharacterAddressGroup(sld, "commonBedroom", "goto", "goto5");
	LAi_SetLayType(sld);
	LAi_CharacterDisableDialog(sld);
	TeleportCharacterToPosAy(sld, -0.95, 2.85, -3.15, 3.2);

	sld = CharacterFromID("MisStid");
	sld.dialog.currentnode = "MissStid_InRoom";
	ChangeCharacterAddressGroup(sld, "CommonBedroom", "goto", "goto5");
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

	QuestPointerDelLoc("Bridgetown_townhall", "reload", "reload3");
	QuestPointerDelLoc("Bridgetown_townhallRoom", "reload", "reload2");
}

void CapBloodLine_InStidBedroom_1(string qName)
{
	TeleportCharacterToPosAy(pchar, -2.41, 1.93, -2.79, 1.5);
	locCameraFromToPos(-3.50, 4.26, -2.88, true, 0.05, 0.55, -2.9);
	QuestPointerToLoc("CommonBedroom", "goto", "goto6");
	LAi_SetActorType(pchar);
	LAi_ActorDialog(pchar, CharacterFromID("Stid_Clone_1"), "", -1, 0);
}

void CapBloodLine_InStidBedroom_2(string qName)
{
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_253"), "Run_Function", 0.1, 4.0);
	SetLaunchFrameRunFunctionParam("CapBloodLine_GoToNettal", 0.0);
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 3, 0);
	RecalculateJumpTable();
}

void CapBloodLine_InStidBedroom_4(string qName) // Второй заход
{
	WaitDate("", 0, 0, 0, 1, 0);
	RecalculateJumpTable();
	RefreshLandTime();
	ref sld = CharacterFromID("Stid_Clone_1");
	sld.dialog.currentnode = "StidOnBed_13";
	LAi_SetActorType(pchar);
	LAi_ActorDialog(pchar, sld, "", -1, 0);
}

void CapBloodLine_GoToNettal()
{
	SetCurrentTime(7, 35);
	RefreshWeather();
	RecalculateJumpTable();
	RefreshLandTime();

	SetFunctionLocationCondition("CapBloodLine_GoToNettal_1", "Bridgetown_Town", false);
	DoQuestReloadToLocation("Bridgetown_Town", "reload", "reload3_back", "");
}

void CapBloodLine_GoToNettal_1(string qName)
{
	LocatorReloadEnterDisable("Bridgetown_Townhall", "reload1_back", false);
	LocatorReloadEnterDisable("Bridgetown_TownhallRoom", "reload3", false);
	LocatorReloadEnterDisable("Bridgetown_Town", "reload3_back", true);
	LocatorReloadEnterDisable("Bridgetown_Town", "reloadR1", true);
	LocatorReloadEnterDisable("Bridgetown_Town", "gate_back", true);
	LocatorReloadEnterDisable("Bridgetown_Town", "gate1_back", true);
	QuestPointerToLoc("Bridgetown_Town", "reload", "reload4_back");
	AddQuestRecord("EscapeFormBarbados", "8");

	// Губернатор отпустил Блада лишь ненадолго: на возвращение есть два часа.
	pchar.quest.CapBloodLine_GovernorReturnLate.win_condition.l1 = "Timer";
	pchar.quest.CapBloodLine_GovernorReturnLate.win_condition.l1.date.hour = GetHour() + 2.0;
	pchar.quest.CapBloodLine_GovernorReturnLate.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
	pchar.quest.CapBloodLine_GovernorReturnLate.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	pchar.quest.CapBloodLine_GovernorReturnLate.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
	pchar.quest.CapBloodLine_GovernorReturnLate.function = "CapBloodLine_GovernorReturnLate";

	bDisableCharacterMenu = false;
	InterfaceStates.Buttons.Save.enable = true;
	DeleteAttribute(&TEV, "StopTimeScale");
	chrDisableReloadToLocation = false;

	ref sld = CharacterFromID("Nettl");
	sld.dialog.currentnode = "NettalTiredWait";
	ChangeCharacterAddressGroup(sld, "Bridgetown_Tavern", "sit", "sit8");
	LAi_SetSitType(sld);
	AddLandQuestMark_Main(sld, "CapBloodLine");
}

void CapBloodLine_GovernorReturnLate(string qName)
{
	if (procEnableInterfaceLaunch(INTERFACE_FRAMEFORM) == false)
	{
		DoQuestFunctionDelay("CapBloodLine_GovernorReturnLate", 1.0);
		return;
	}

	InterfaceStates.Buttons.Save.enable = false;
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_298"), "Run_Function", 0.1, 4.0);
	SetLaunchFrameRunFunctionParam("CapBloodLine_q2_Late_GameOver", 0.0);
	LaunchFrameForm();
}

void CapBloodLine_InGuberRoomAgain(string qName)
{
	// Блад успел вернуться к губернатору вовремя.
	pchar.quest.CapBloodLine_GovernorReturnLate.over = "yes";

	ref sld = CharacterFromID("Stid_Clone_1");
	sld.dialog.currentnode = "StidOnBed_10";
	LAi_CharacterEnableDialog(sld);
	TeleportCharacterToPosAy(sld, -0.95, 2.85, -3.15, 3.2);

	chrDisableReloadToLocation = true;
	QuestPointerToLoc("CommonBedroom", "goto", "goto6");

	pchar.quest.CapBloodLine_InGuberRoomAgain_1.win_condition.l1 = "locator";
	pchar.quest.CapBloodLine_InGuberRoomAgain_1.win_condition.l1.location = "CommonBedroom";
	pchar.quest.CapBloodLine_InGuberRoomAgain_1.win_condition.l1.locator_group = "goto";
	pchar.quest.CapBloodLine_InGuberRoomAgain_1.win_condition.l1.locator = "goto6";
	pchar.quest.CapBloodLine_InGuberRoomAgain_1.function = "CapBloodLine_InGuberRoomAgain_1";
}

void CapBloodLine_InGuberRoomAgain_1(string qName)
{
	TeleportCharacterToPosAy(pchar, -2.41, 1.93, -2.79, 1.5);
	locCameraFromToPos(-3.50, 4.26, -2.88, true, 0.05, 0.55, -2.9);
	QuestPointerDelLoc("CommonBedroom", "goto", "goto6");
	LAi_SetActorType(pchar);
	LAi_ActorDialog(pchar, CharacterFromID("Stid_Clone_1"), "", -1, 0);
}

void CapBloodLine_InGuberRoomReturn(string qName)
{
	ref sld = CharacterFromID("Stid_Clone_1");
	sld.dialog.currentnode = "StidOnBed_16";
	LAi_CharacterEnableDialog(sld);
	TeleportCharacterToPosAy(sld, -0.95, 2.85, -3.15, 3.2);
}

void CapBloodLine_InGuberRoomReturn_1()
{
	chrDisableReloadToLocation = false;
	LocatorReloadEnterDisable("Bridgetown_Town", "gate_back", false);
	LocatorReloadEnterDisable("Bridgetown_Town", "gate1_back", false);
	QuestPointerDelLoc("Bridgetown_Town", "reload", "reload3_back");
	QuestPointerDelLoc("Bridgetown_Town", "reload", "reloadR1");
	QuestPointerDelLoc("Bridgetown_TownhallRoom", "reload", "reload2");
	QuestPointerDelLoc("Bridgetown_Townhall", "reload", "reload3");
	QuestPointerToLoc("Bridgetown_Town", "reload", "gate1_back");
	QuestPointerToLoc("Bridgetown_TownhallRoom", "reload", "reload3");
	QuestPointerToLoc("Bridgetown_Townhall", "reload", "reload1_back");
	AddQuestRecord("EscapeFormBarbados", "10");
	SetFunctionLocationCondition("CapBloodLine_InGuberRoomReturn", "CommonBedroom", true);
	SetFunctionLocationCondition("CapBloodLine_OnPlantationAgain", "Bridgetown_Plantation", false);
	DeleteAttribute(&locations[FindLocation("Bridgetown_Plantation")], "carrier"); // Мешают сценам. Временно снесём
	CapBloodLine_RemovePlantationCarriers();
}

void CapBloodLine_OnPlantationAgain(string qName)
{
	StartQuestMovie(true, false, true);
	ResetTimeScale();
	TEV.StopTimeScale = 1;
	TeleportCharacterToPosAy(pchar, -9.39, 6.12, -44.71, 3.2);
	LAi_SetActorType(pchar);
	LAi_ActorMoveToPoint(pchar, false, -8.35, 5.29, -41.71, "CapBloodLine_OnPlantationAgain_Turn", -1.0);

	ref sld = CharacterFromID("Arabella");
	sld.dialog.currentnode = "ArabellaOnPlantation_18";
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "quest", "detector2");
	TeleportCharacterToPosAy(sld, -8.93, 3.40, -28.18, 3.2);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto18", "", -1);

	chrDisableReloadToLocation = true;
	QuestPointerDelLoc("Bridgetown_town", "reload", "gate1_back");
	DoQuestFunctionDelay("CapBloodLine_OnPlantationAgain_0", 0.1);
}

void CapBloodLine_OnPlantationAgain_0(string qName)
{
	locCameraFromToPos(-7.82, 7.17, -43.25, true, 1.05, -2.55, -1.9);
}

void CapBloodLine_OnPlantationAgain_1(string qName)
{
	ref sld = CharacterFromID("Arabella");
	LAi_SetActorType(sld);
	LAi_SetStayType(pchar);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void CapBloodLine_OnPlantationAgain_2(string qName)
{
	ref sld = CharacterFromID("Arabella");
	sld.dialog.currentnode = "ArabellaOnPlantation_38";
	TeleportCharacterToPosAy(sld, -1.69, 1.22, 56.88, 1.5);
	TeleportCharacterToPosAy(pchar, 0.77, 1.19, 56.88, -1.5);
	CharacterTurnByChr(sld, pchar);
	CharacterTurnByChr(pchar, sld);
	LAi_SetActorType(sld);
	LAi_SetStayType(pchar);
	LAi_ActorDialog(sld, pchar, "", 0, -1);
}

void CapBloodLine_OnPlantationAgain_3()
{
	locCameraSleep(true);
	LAi_FadeEx(0.5, 0.5, 0.5, "", "CapBloodLine_OnPlantationAgain_4", "");
}

void CapBloodLine_OnPlantationAgain_4(string qName)
{
	LAi_SetStayType(pchar);
	TeleportCharacterToPosAy(pchar, -8.17, 3.43, -25.43, -1.5);
	locCameraSleep(false);
	locCameraTarget(pchar);
	locCameraFollow();

	ref sld = CharacterFromID("Arabella");
	sld.dialog.currentnode = "ArabellaOnPlantation_20";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, -1);
}

void CapBloodLine_NeedToSavePitt(string qName) // Хотели побазарить с Питтом, но опоздали
{
	ResetTimeScale();
	TEV.StopTimeScale = 1;
	LAi_SetActorType(pchar);
	pchar.GenQuest.CantRun = true;
	LAi_FadeEx(1.0, 0.5, 1.0, "", "CapBloodLine_NeedToSavePitt_1", "");
	StopMusic(500);
	TEV.Music.LoopTrack = "";
	PlayMusic("Music\Special\Quest\Storm.mp3", 5000);

	QuestPointerDelLoc("Bridgetown_townhall", "reload", "reload3");
	QuestPointerDelLoc("Bridgetown_townhallRoom", "reload", "reload2");
	QuestPointerDelLoc("Bridgetown_Plantation", "quest", "sit2");
}

void CapBloodLine_NeedToSavePitt_1(string qName)
{
	StartQuestMovie(true, false, true);
	locCameraFlyToPositionLookToPoint(26.63, 2.94, 113.63, 22.14, 1.85, 111.05, 31.73, 0.95, 100.39, -1.0, 8000/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_NeedToSavePitt_3";

	TeleportCharacterToPosAy(pchar, 34.75, 1.10, 101.41, -1.10);
	LAi_SetStayType(pchar);
	DoQuestFunctionDelay("CapBloodLine_NeedToSavePitt_2", 2.5);
}

void CapBloodLine_NeedToSavePitt_2(string qName)
{
	LAi_SetActorType(pchar);
	LAi_ActorMoveToPoint(pchar, false, 24.81, 1.10, 107.14, "CapBloodLine_NeedToSavePitt_5", -1.0);
}

void CapBloodLine_NeedToSavePitt_3()
{
	locCameraSleep(true);
	pchar.questTemp.CBL_CameraIsReady = true;
}

void CapBloodLine_NeedToSavePitt_4(string qName)
{
	EndQuestMovie();
	locCameraSleep(false);
	//locCameraFollowEx(true);
}

void CapBloodLine_NeedToSavePitt_7(string qName)
{
	locCameraSleep(false);
	locCameraFromToPos(21.22, 2.90, 105.78, true, 75.05, -28.55, 195.9);
	TeleportCharacterToPosAy(pchar, 24.03, 1.10, 108.84, -1.5);

	ref sld = CharacterFromID("Pitt");
	sld.greeting = "";
	sld.dialog.currentnode = "Pitt_lay";
	LAi_CharacterEnableDialog(sld);
	LAi_SetStayType(pchar);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CapBloodLine_NeedToSavePitt_8(string qName)
{
	LAi_SetPlayerType(pchar);
	QuestPointerToLoc("BridgeTown_Plantation", "quest", "stay1");
}

void CapBloodLine_NeedToSavePitt_9(string qName)
{
	ref sld = CharacterFromID("Bishop");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	TeleportCharacterToPosAy(sld, 18.38, 1.18, 98.84, 0.75);
	LAi_SetActorType(sld);
	LAi_ActorMoveToPoint(sld, false, 24.68, 1.10, 103.96, "CapBloodLine_NeedToSavePitt_10", -1.0);
	locCameraFromToPos(23.27, 1.13, 102.59, true, -55.05, 12.55, 30.9);
}

void CapBloodLine_NeedToSavePitt_11(string qName)
{
	ref sld = CharacterFromID("Bishop");
	sld.dialog.currentnode = "Bishop_Plantation_9";
	TeleportCharacterToPosAy(sld, 24.08, 1.10, 107.24, 0.0);
	LAi_SetActorType(sld);
	LAi_SetStayType(pchar);
	LAi_CharacterEnableDialog(sld);
	LAi_ActorDialog(sld, pchar, "", 0, -1);

	locCameraFromToPos(23.05, 2.96, 109.74, true, 55.05, -21.55, 30.9);
}

void CapBloodLine_NeedToSavePitt_12() // Подозвать два ближайших солдата
{
	int i;
	ref chr;
	ref bishop = characterFromID("Bishop");

	int firstIdx = -1;
	int secondIdx = -1;

	float bx, by, bz;
	float cx, cy, cz;
	float dist;
	float firstDist = 999999.0;
	float secondDist = 999999.0;

	GetCharacterPos(bishop, &bx, &by, &bz);

	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		makeref(chr, Characters[i]);

		if (!CheckAttribute(chr, "location")) continue;
		if (chr.location != pchar.location) continue;
		if (chr.id == bishop.id) continue;
		if (LAi_IsDead(chr)) continue;

		if (!CheckAttribute(chr, "model")) continue;
		if (findsubstr(chr.model, "milit_eng_", 0) != 0) continue;

		GetCharacterPos(chr, &cx, &cy, &cz);

		dist = GetDistance2D(cx, cz, bx, bz);

		if (dist < firstDist)
		{
			secondDist = firstDist;
			secondIdx = firstIdx;

			firstDist = dist;
			firstIdx = i;
		}
		else
		{
			if (dist < secondDist)
			{
				secondDist = dist;
				secondIdx = i;
			}
		}
	}

	if (firstIdx != -1)
	{
		makeref(chr, Characters[firstIdx]);

		chr.quest.BishopGuard = true;
		chr.GenQuest.CantRun = true;
		LAi_SetActorType(chr);
		LAi_ActorFollow(chr, bishop, "", -1);
	}

	if (secondIdx != -1)
	{
		makeref(chr, Characters[secondIdx]);

		chr.quest.BishopGuard = true;
		chr.GenQuest.CantRun = true;
		LAi_SetActorType(chr);
		LAi_ActorFollow(chr, bishop, "", -1);
	}
}

void CapBloodLine_NeedToSavePitt_13(string qName) // Все услышали канонаду
{
	int i;
	ref chr;

	LAi_SetActorType(pchar);
	CharacterTurnAy(pchar, 2.2);

	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		makeref(chr, Characters[i]);

		if (!CheckAttribute(chr, "location")) continue;
		if (chr.location != pchar.location) continue;
		if (chr.id == pchar.id) continue;
		if (chr.id == "Pitt") continue;
		if (LAi_IsDead(chr)) continue;

		LAi_SetActorType(chr);
		CharacterTurnAy(chr, 2.2);
	}
	LocatorReloadEnterDisable("Bridgetown_Plantation", "houseSp1", true);
}

void CapBloodLine_NeedToSavePitt_14(string qName)
{
	locCameraFlyToPositionLookToPoint(71.99, 20.72, 71.10, 25.34, 2.88, 106.25, 25.34, 2.88, 106.25, 1, 3550/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_NeedToSavePitt_15";

	PlaySound("Sea Battles_01\Cannon_Fire_festive.wav");
	DoQuestFunctionDelay("CapBloodLine_NeedToSavePitt_13", 1.0);
	pchar.questTemp.CapBloodLine.stat = "Attack_Fort";
}

void CapBloodLine_NeedToSavePitt_15()
{
	locCameraSleep(true);
	DoQuestFunctionDelay("CapBloodLine_NeedToSavePitt_16", 1.0);
}

void CapBloodLine_NeedToSavePitt_16(string qName)
{
	ref sld = CharacterFromID("Bishop");
	sld.dialog.currentnode = "Bishop_Plantation_20";
	DeleteAttribute(sld, "GenQuest.CantRun");
	LAi_SetActorType(sld);
	LAi_SetStayType(pchar);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CapBloodLine_NeedToSavePitt_17()
{
	int i;
	ref chr, sld;
	ref bishop = characterFromID("Bishop");

	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		makeref(chr, Characters[i]);

		if (!CheckAttribute(chr, "location")) continue;
		if (chr.location != pchar.location) continue;
		if (chr.id == bishop.id) continue;
		if (LAi_IsDead(chr)) continue;

		if (!CheckAttribute(chr, "model")) continue;
		if (findsubstr(chr.model, "milit_eng_", 0) != 0) continue;

		LAi_SetActorType(chr);
		LAi_ActorFollow(chr, bishop, "", -1);
	}

	string sChars[5];

	sChars[0] = "Ogl";
	sChars[1] = "Volverston";
	sChars[2] = "Hugtorp";
	sChars[3] = "Dieke";
	sChars[4] = "Slave_Quest";

	for (int j = 0; j < 5; j++)
	{
		sld = CharacterFromID(sChars[j]);

		if (!CheckAttribute(sld, "location")) continue;
		if (sld.location != pchar.location) continue;

		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "goto", "goto9");
	}
	DoQuestFunctionDelay("CapBloodLine_NeedToSavePitt_18", 3.5);
}

void CapBloodLine_NeedToSavePitt_18(string qName)
{
	LAi_FadeEx(0.5, 0.5, 0.5, "", "CapBloodLine_NeedToSavePitt_19", "");
}

void CapBloodLine_NeedToSavePitt_19(string qName)
{
	ref sld = CharacterFromID("Pitt");
	sld.dialog.currentnode = "Pitt_lay_6";
	LAi_SetActorType(pchar);
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

	locCameraFromToPos(20.22, 3.03, 109.78, true, 75.05, -13.55, 86.9);

	string sChars[5];
	sChars[0] = "Ogl";
	sChars[1] = "Volverston";
	sChars[2] = "Hugtorp";
	sChars[3] = "Dieke";
	sChars[4] = "Slave_Quest";

	int pos[5];
	pos[0] = 0;
	pos[1] = 1;
	pos[2] = 2;
	pos[3] = 3;
	pos[4] = 4;

	int i, j, tmp, idx;

	for (i = 4; i > 0; i--)
	{
		j = rand(i);

		tmp = pos[i];
		pos[i] = pos[j];
		pos[j] = tmp;
	}

	for (i = 0; i < 5; i++)
	{
		idx = GetCharacterIndex(sChars[i]);
		if (idx < 0) continue;

		sld = GetCharacter(idx);
		if (sld.location != pchar.location) ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");

		switch (pos[i])
		{
			case 0: TeleportCharacterToPosAy(sld, 25.57, 1.10, 107.52, -1.70); break;
			case 1: TeleportCharacterToPosAy(sld, 25.05, 1.10, 106.72, -1.70); break;
			case 2: TeleportCharacterToPosAy(sld, 24.14, 1.10, 106.27, -1.70); break;
			case 3: TeleportCharacterToPosAy(sld, 22.71, 1.10, 106.21, -1.70); break;
			case 4: TeleportCharacterToPosAy(sld, 23.26, 1.10, 105.16, -1.70); break;
		}

		LAi_SetActorType(sld);
		LAi_ActorTurnToLocator(sld, "quest", "sit2");
	}


	sld = CharacterFromID("Slave_Quest");
	LAi_RemoveLoginTime(sld);

	sld = CharacterFromID("CBL_Kent");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
	TeleportCharacterToPosAy(sld, 32.91, 1.10, 102.25, 0.0);
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorMoveToPoint(sld, true, 26.20, 1.10, 109.15, "CapBloodLine_NeedToSavePitt_20", -1.0);
}

void CapBloodLine_NeedToSavePitt_21()
{
	ref sld;
	ref kent = CharacterFromID("CBL_Kent");

	for (int i = 0; i < MAX_CHARACTERS; i++)
	{
		makeref(sld, Characters[i]);

		if (CheckAttribute(sld, "model") && findsubstr(sld.model, "milit_eng_", 0) == 0) continue;
		if (!CheckAttribute(sld, "location")) continue;
		if (sld.location != pchar.location) continue;
		if (sld.id == kent.id) continue;
		if (sld.id == "Pitt") continue;
		if (sld.id == "Bishop") continue;
		if (LAi_IsDead(sld)) continue;

		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, kent);
	}
}

void CapBloodLine_NeedToSavePitt_22()
{
	ref sld;
	string sChars[5];

	sChars[0] = "Ogl";
	sChars[1] = "Volverston";
	sChars[2] = "Hugtorp";
	sChars[3] = "Dieke";
	sChars[4] = "Slave_Quest";

	int idx;
	for (int i = 0; i < 5; i++)
	{
		idx = GetCharacterIndex(sChars[i]);
		if (idx < 0) continue;

		sld = GetCharacter(idx);

		if (!CheckAttribute(sld, "location")) continue;
		if (sld.location != pchar.location) continue;
		if (LAi_IsDead(sld)) continue;

		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
	}

	for (int j = 0; j < MAX_CHARACTERS; j++)
	{
		makeref(sld, Characters[j]);

		if (!CheckAttribute(sld, "location")) continue;
		if (sld.location != pchar.location) continue;
		if (LAi_IsDead(sld)) continue;

		if (!CheckAttribute(sld, "model")) continue;
		if (findsubstr(sld.model, "Slave_", 0) != 0 && findsubstr(sld.model, "slave_", 0) != 0) continue;

		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "goto", "goto22", "none", "", "", "", -1.0);
	}

	LAi_ActorTurnToCharacter(pchar, CharacterFromID("Volverston"));
	DoQuestFunctionDelay("CapBloodLine_NeedToSavePitt_23", 1.0);
}

void CapBloodLine_NeedToSavePitt_23(string qName)
{
    ref sld = CharacterFromID("Volverston");
	sld.dialog.currentnode = "VolverstonNearPitt";
	LAi_SetActorType(sld);
	LAi_SetActorType(pchar);
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
	PlaySound("Sea Battles_01\Cannonade_dense.wav");
}

void CapBloodLine_BladGoesToCity(string qName) // Наступает ночь - пора на разведку
{
	ref sld;
	for (int j = 0; j < MAX_CHARACTERS; j++)
	{
		makeref(sld, Characters[j]);

		if (!CheckAttribute(sld, "location")) continue;
		if (sld.location != pchar.location) continue;
		if (LAi_IsDead(sld)) continue;

		if (!CheckAttribute(sld, "model")) continue;
		if (findsubstr(sld.model, "Slave_", 0) != 0 && findsubstr(sld.model, "slave_", 0) != 0) continue;

		ChangeCharacterAddressGroup(sld, "none", "", "");
	}

	for (int k = 0; k < MAX_CHARACTERS; k++)
	{
		makeref(sld, Characters[k]);

		if (!CheckAttribute(sld, "location")) continue;
		if (sld.location != pchar.location) continue;
		if (sld.id == "CBL_Kent") continue;
		if (LAi_IsDead(sld)) continue;

		if (!CheckAttribute(sld, "model")) continue;
		if (findsubstr(sld.model, "milit_eng_", 0) != 0 && findsubstr(sld.model, "milit_mush_eng_", 0) != 0) continue;

		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
	EndQuestMovie();
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_254"), "Reload_To_Location", 0.1, 4);
	SetLaunchFrameReloadLocationParam("Bridgetown_Plantation", "goto", "goto18", "CapBloodLine_BladGoesToCity_1");
	LaunchFrameForm();

	SetCurrentTime(23, 00);
	RefreshLandTime();
	RecalculateJumpTable();
	DeleteAttribute(&TEV, "Music.LoopTrack");
}

void CapBloodLine_BladGoesToCity_2(string qName) // В отдельную функцию, ибо со сменой локи персы улетают
{
	ref sld;
	string sChars[5];

	sChars[0] = "Pitt";
	sChars[1] = "Dieke";
	sChars[2] = "Slave_Quest";
	sChars[3] = "Ogl";
	sChars[4] = "Hugtorp";

	float x[5]; float y[5]; float z[5]; float ay[5];

	x[0] = 1.35; y[0] = 1.49; z[0] = 120.65; ay[0] = 2.2;
	x[1] = 4.65; y[1] = 1.32; z[1] = 123.04; ay[1] = 2.2;
	x[2] = 8.62; y[2] = 1.30; z[2] = 122.38; ay[2] = -1.2;
	x[3] = 3.29; y[3] = 1.37; z[3] = 121.04; ay[3] = -0.6;
	x[4] = 2.38; y[4] = 1.36; z[4] = 121.84; ay[4] = 2.6;

	int idx;
	for (int i = 0; i < 5; i++)
	{
		idx = GetCharacterIndex(sChars[i]);
		if (idx < 0) continue;

		sld = GetCharacter(idx);
		LAi_LoginInCaptureTown(sld, true);
		LAi_SetLoginTime(sld, 0.0, 24.0);
		if (sld.location != pchar.location) ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
		TeleportCharacterToPosAy(sld, x[i], y[i], z[i], ay[i]);

		switch (i)
		{
			case 0:
				sld.dialog.currentnode = "Pitt_In_Shack";
				LAi_SetLayType(sld);
			break;

			case 1:
				sld.dialog.currentnode = "Dieke_In_Shack";
				LAi_SetGroundSitType(sld);
			break;

			case 2:
				sld.dialog.currentnode = "Thorn_In_Shack";
				// LAi_RemoveLoginTime(sld);
				LAi_SetGroundSitType(sld);
			break;

			case 3:
				sld.dialog.currentnode = "Ogl_In_Shack";
				LAi_SetStayType(sld);
			break;

			case 4:
				sld.dialog.currentnode = "Hugtorp_In_Shack";
				LAi_SetStayType(sld);
			break;
		}
	}
	sld = CharacterFromID("Volverston");
	if (CheckAttribute(pchar, "questTemp.CapBloodLine.stat") && pchar.questTemp.CapBloodLine.stat == "Attack_Fort")
	{
		sld.dialog.currentnode = "VolverstonGiveWeapon";
		LAi_LoginInCaptureTown(sld, true);
		LAi_SetLoginTime(sld, 0.0, 24.0);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		TeleportCharacterToPosAy(sld, 1.73, 1.10, 74.44, -1.5);
	}
	else if (CheckAttribute(pchar, "questTemp.CapBloodLine.stat") && pchar.questTemp.CapBloodLine.stat == "Mary")
	{
		TeleportCharacterToPosAy(sld, 4.08, 1.30, 121.70, -1.5);
	}
	else if (CheckAttribute(pchar, "questTemp.CapBloodLine.stat") && pchar.questTemp.CapBloodLine.stat == "Mary_Saved")
	{
		sld.dialog.currentnode = "Volverston_OfficerNode";
		LAi_SetStayType(sld);
		TeleportCharacterToPosAy(sld, 4.08, 1.30, 121.70, -1.5);
	}
	SetFunctionExitFromLocationCondition("CapBloodLine_BladGoesToCity_3", pchar.location, false);
}

void CapBloodLine_BladGoesToCity_3(string qName)
{
	SetFunctionLocationCondition("CapBloodLine_BladGoesToCity_2", "Bridgetown_Plantation", false);
}

void CapBloodLine_ArabellaInHouse(string qName) // Пришли к дому Бишопа
{
	LAi_FadeEx(0.5, 0.5, 0.5, "", "CapBloodLine_ArabellaInHouse_1", "");
	LAi_SetStayType(pchar);
	SendMessage(pchar, "ls", MSG_CHARACTER_EX_MSG, "StopSprint");
}

void CapBloodLine_ArabellaInHouse_1(string qName)
{
	ref sld = CharacterFromID("ArabelaService");
	TeleportCharacterToPosAy(sld, 16.05, 1.25, 101.24, 0.0);
	LAi_SetActorType(sld);
	LAi_ActorMoveToPoint(sld, false, 13.40, 2.11, 103.93, "CapBloodLine_ArabellaInHouse_4", -1.0);

	TeleportCharacterToPosAy(pchar, 15.31, 1.35, 101.55, 0.0);
	LAi_SetActorType(pchar);
	LAi_ActorMoveToPoint(pchar, false, 14.13, 2.11, 103.97, "CapBloodLine_ArabellaInHouse_2", -1.0);

	QuestPointerDelLoc("Bridgetown_Town", "reload", "gate1_back");
	QuestPointerDelLoc("Bridgetown_Plantation", "reload", "houseSp1");
	locCameraFromToPos(15.49, 3.57, 104.70, true, -55.05, -5.55, 65.9);
}

void CapBloodLine_ArabellaInHouse_3(string qname)
{
	ref sld = CharacterFromID("Arabella");
	sld.dialog.currentnode = "ArabellaOnHouse";
	LAi_LoginInCaptureTown(sld, true);
	LAi_SetLoginTime(sld, 0.0, 24.0);
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto1");
	TeleportCharacterToPosAy(sld, 13.63, 2.11, 105.97, 0.0);
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
	locCameraFromToPos(14.72, 4.04, 102.83, true, -55.05, -39.55, 196.9);
	TeleportCharacterToPosAy(CharacterFromID("ArabelaService"), 13.40, 2.11, 103.93, 0.3);
}

void CapBloodLine_ArabellaInHouse_5(string qName)
{
    ref sld = CharacterFromID("Arabella");
	sld.dialog.currentnode = "ArabellaOnHouse_7";
	sld.model = "Arabella";
	Characters_RefreshModel(sld);
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_Sp1", "goto", "goto2");
	CharacterTurnAy(sld, -1.7);
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1);

	sld = CharacterFromID("ArabelaService");
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_Sp1", "goto", "goto1");
	TeleportCharacterToPosAy(sld, 0.37, 0.00, -0.42, 1.2);
	TeleportCharacterToPosAy(pchar, 0.54, 0.00, -1.35, 1.0);

	ref loc = &Locations[FindLocation("Bridgetown_Plantation")];
	loc.locators_radius.reload.houseSp1 = 1.0;
}

void CapBloodLine_ArabellaInHouse_6(string qName)
{
	ref sld = CharacterFromID("ArabelaService");
	sld.dialog.currentnode = "ArabellaOnHouse_21";
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto1");
	TeleportCharacterToPosAy(sld, 10.71, 1.18, 98.05, -2.0);
	TeleportCharacterToPosAy(pchar, 8.42, 1.12, 97.45, 1.2);
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void CapBloodLine_ArabellaInHouse_7()
{
	ref sld = CharacterFromID("Arabella");
	sld.dialog.currentnode = "ArabellaOnHouse_23";
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "reload", "houseSp1");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "CapBloodLine_ArabellaInHouse_8", -1);
	DoQuestFunctionDelay("CapBloodLine_ArabellaInHouse_9", 1.0);
}

void CapBloodLine_ArabellaInHouse_9(string qName)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("CBL_James", "Slave_James", "man", "man", 1, ENGLAND, -1, false));
	FantomMakeCoolFighter(sld, 20, 90, 90, "blade26", "pistol4", 120);
	LAi_LoginInCaptureTown(sld, true);
	LAi_SetLoginTime(sld, 0.0, 24.0);
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "reload", "houseSp1");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, CharacterFromID("Arabella"), "", -1);
}
void CapBloodLine_ArabellaInHouse_11()
{
	ref sld = CharacterFromID("Arabella");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "goto", "goto22", "none", "", "", "CapBloodLine_ArabellaInHouse_10", -1);
	QuestPointerToLoc("Bridgetown_Plantation", "quest", "detector3");
	SetFunctionLocatorCondition("CapBloodLine_Esape", "Bridgetown_Plantation", "quest", "detector3", false);

	sld = CharacterFromID("Volverston");
	sld.dialog.currentnode = "VolvInBarac";
	LAi_CharacterEnableDialog(sld);
	LAi_SetStayType(sld);
	AddLandQuestmark_Main(sld, "CapBloodLine");

	string sChars[5];

	sChars[0] = "Pitt";
	sChars[1] = "Dieke";
	sChars[2] = "Slave_Quest";
	sChars[3] = "Ogl";
	sChars[4] = "Hugtorp";

	for (int i = 0; i < 5; i++)
	{
		int iChar = GetCharacterIndex(sChars[i]);

		if (iChar != -1)
		{
			sld = &Characters[iChar];
			LAi_CharacterDisableDialog(sld);
		}
	}
}

void CapBloodLine_Esape(string qName)
{
	ref sld = CharacterFromID("Volverston");
	sld.dialog.currentnode = "VolvInBarac";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
	QuestPointerDelLoc("Bridgetown_Plantation", "quest", "detector3");
}

void CapBloodLine_EsapeDialog()
{
	string sChars[5];

	sChars[0] = "Pitt";
	sChars[1] = "Dieke";
	sChars[2] = "Slave_Quest";
	sChars[3] = "Ogl";
	sChars[4] = "Hugtorp";

	for (int i = 0; i < 5; i++)
	{
		int iChar = GetCharacterIndex(sChars[i]);

		if (iChar != -1)
		{
			ref sld = &Characters[iChar];
			LAi_CharacterEnableDialog(sld);

			switch (sChars[i])
			{
				case "Pitt":
				// Питта оставляем без изменений
				break;

				case "Dieke":
					LAi_SetActorType(sld);
					LAi_ActorAnimation(sld, "Ground_StandUp_Fast", "CapBloodLine_EsapeDialog_Dieke", -1.0);
				break;

				case "Slave_Quest":
					TeleportCharacterToPosAy(sld, 7.78, 1.15, 122.47, -1.2);
					LAi_SetActorType(sld);
					LAi_ActorAnimation(sld, "Ground_StandUp_Fast", "CapBloodLine_EsapeDialog_Slave_Quest", -1.0);
				break;

				case "Ogl":
					LAi_SetActorType(sld);
					LAi_ActorFollow(sld, pchar, "CapBloodLine_ED_TurnOgl", -1);
				break;

				case "Hugtorp":
					LAi_SetActorType(sld);
					LAi_ActorFollow(sld, pchar, "CapBloodLine_ED_TurnHugtorp", -1);
				break;
			}
		}
	}
}

void CapBloodLine_Esape_1(string qName) // VLStep_10 - как ориентир
{
	ref sld;
	int i;

	Pchar.questTemp.CapBUnarmed = false;
	ResetTimeScale();
	TEV.StopTimeScale = 1;
	StartQuestMovie(true, false, true);

	LAi_SetStayType(pchar);
	TeleportCharacterToPosAy(pchar, -25.41, 1.61, 14.65, 3.2);

	string sChars[5], sWeapons[5], sLocators[5];

	sChars[0] = "Volverston";	sWeapons[0] = "topor1";	sLocators[0] = "quest3";
	sChars[1] = "Hugtorp";		sWeapons[1] = "blade7";	sLocators[1] = "quest4";
	sChars[2] = "Ogl";			sWeapons[2] = "blade5";	sLocators[2] = "quest5";
	sChars[3] = "Dieke";		sWeapons[3] = "blade7";	sLocators[3] = "quest6";
	sChars[4] = "Pitt";			sWeapons[4] = "";		sLocators[4] = "sit2";

	for (i = 0; i < 5; i++)
	{
		sld = CharacterFromID(sChars[i]);
		LAi_LoginInCaptureTown(sld, true);

		if (sChars[i] == "Pitt")
		{
			LAi_SetActorType(sld);
			LAi_ActorSetLayMode(sld);
			ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "quest", sLocators[i]);
			LAi_CharacterDisableDialog(sld);
			continue;
		}
		if (sChars[i] == "Volverston")
		{
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "VLStep_10";
		}
		else
		{
			LAi_SetStayTypeNoGroup(sld);
			LAi_CharacterDisableDialog(sld);
		}
		GiveItem2Character(sld, sWeapons[i]);
		EquipCharacterByItem(sld, sWeapons[i]);
		TakeNItems(sld, "potion1", 5);

		if (sChars[i] == "Ogl" || sChars[i] == "Dieke") LAi_SetImmortal(sld, false);
		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", sLocators[i]);
		if (sChars[i] == "Volverston") LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		else CharacterTurnByChr(sld, pchar);
	}

	for (i = 1; i <= 3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FreeSlave_" + i, "slave_" + (rand(8) + 1), "man", "man", 10, SPAIN, -1, false));
		// статичная модель для FreeSlave_1 - белый раб
		if (i == 1)
		{
			sld.model = "slave_6";
			FaceMaker(sld);
		}
		else SetNPCModelUniq(sld, "convict", MAN);

		SetFantomParamFromRank(sld, sti(pchar.rank) + makeint(2 * MOD_SKILL_ENEMY_RATE / 3), true); // бравые орлы
		sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
		LAi_LoginInCaptureTown(sld, true);
		LAi_SetActorType(sld);
		LAi_ActorStay(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest" + (6 + i));
		LAi_CharacterDisableDialog(sld);
		CharacterTurnByChr(sld, pchar);
	}

	sld = GetCharacter(NPC_GenerateCharacter("SandroNew", "Sandro_Thorne_6", "man", "man", 10, SPAIN, -1, false)); // Сандро Торн в обносках
	SetFantomParamFromRank(sld, sti(pchar.rank) + makeint(2 * MOD_SKILL_ENEMY_RATE / 3), true);
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	LAi_LoginInCaptureTown(sld, true);
	LAi_SetActorType(sld);
	LAi_ActorStay(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest9");
	LAi_CharacterDisableDialog(sld);
	CharacterTurnByChr(sld, pchar);
}

void CapBloodLine_Esape_2(string qName)
{
	for (int i = 1; i < MAX_CHARACTERS; i++) // Если ПГГ заспаунился в бухте - убрать
	{
		if (!CheckAttribute(&Characters[i], "PGGAi")) continue;
		if (!CheckAttribute(&Characters[i], "location.from_sea")) continue;
		if (Characters[i].location.from_sea != "Bridgetown_town") continue;

		Characters[i].PGGAi.CapBloodLineFromSea = Characters[i].location.from_sea;
		Characters[i].location.from_sea = "";
	}
	DoQuestReloadToLocation("Bridgetown_Town", "quest", "quest10", "");
	SetFunctionLocationCondition("CapBloodLine_Esape_1", "Bridgetown_Town", false);
}


void SaveArabelaServiceAfraid_1(string qName)
{
	locCameraSleep(false);
	locCameraResetState();
	locCameraFromToPos(-36.37, 8.00, -20.28, true, 1.05, -0.55, -22.9);

	ref sld = characterFromID("SpaRaider");
	TeleportCharacterToPosAy(sld, -31.54, 6.02, -20.80, -1.5);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialogNow(sld, pchar, "",  -1);
	DeleteAttribute(&TEV, "StopTimeScale");
	QuestMovieSetup(false);
}

void CapBloodLine_TalkWithMary(string qName)
{
	LAi_FadeEx(0.5, 0.5, 0.5, "", "CapBloodLine_TalkWithMary_1", "");
}

void CapBloodLine_TalkWithMary_1(string qName)
{
	locCameraFromToPos(-34.74, 6.98, -16.03, true, -52.72, 14.03, 10.33);
	ref sld = CharacterFromID("ArabelaService");
	TeleportCharacterToPosAy(sld, -37.09, 7.28, -14.01, 2.7);
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "afraid", "SaveArabelaServiceAfraid_3", 4.5);

	TeleportCharacterToPosAy(pchar, -33.03, 6.64, -15.93, 0.0);
	LAi_SetActorType(pchar);
	LAi_ActorMoveToPoint(pchar, false, -35.73, 6.64, -14.33, "CapBloodLine_TalkWithMary_2", -1.0);
}

void CapBloodLine_TalkWithMary_3(string qName)
{
	ref sld = characterFromID("ArabelaService");
	LAi_SetActorType(sld);
	LAi_SetStayType(pchar);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	CharacterTurnAy(CharacterFromID("ArabelaService"), 1.5);
	QuestMovieSetup(false);
}

void CapBloodLine_TalkWithMaryOnPlantation(string qName)
{
    ref sld = CharacterFromID("ArabelaService");
	sld.greeting = "";
	sld.dialog.currentnode = "ASStep_4";
	TeleportCharacterToLocator(sld, "reload", "reload1_back");
	LAi_SetActorType(sld);
	LAi_SetStayType(pchar);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CapBloodLine_AddOfficerReady() // Счетчик на количество офицеров
{
	if (CheckAttribute(Pchar, "questTemp.CapBloodLine.Officer") && sti(Pchar.questTemp.CapBloodLine.Officer) >= 4 &&  CheckAttribute(Pchar, "questTemp.CapBloodLine.stat") && Pchar.questTemp.CapBloodLine.stat == "ReadyToEscape")
	{
		AddQuestRecord("CapBloodLine_q2", "15");
		ref sld = CharacterFromID("Bridgetown_Shipyarder");
		DeleteAttribute(sld, "questTemp.BloogEndTreatment");
	}
}

void CapBloodLine_UsurerQuest_MapEnter(string qName)
{
	AddQuestRecord("UsurerQuest", "6");
	ChangeCharacterHunterScore(pchar, "enghunter", 30);
	RemoveLandQuestmark_Main(characterFromID("Bridgetown_usurer"), "CapBloodLine");
}

void CapBloodLine_CheckReadyToFight(string qName)
{
	string sBlade = GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE);
	if (sBlade != "")
	{
		LocatorReloadEnterDisable("Bridgetown_Plantation", "reload1_back", false);
		DeleteQuestCondition("CapBloodLine_CheckReadyToFight");
		return;
	}
	LogSound_WithNotify(StringFromKey("InfoMessages_255"), "", "FencingLight");
}

void CapBloodLine_SpaSoldierDead(string qName)
{
	pchar.questTemp.CapBloodLine.SpaSoldierDead = sti(pchar.questTemp.CapBloodLine.SpaSoldierDead) + 1;

	if (sti(pchar.questTemp.CapBloodLine.SpaSoldierDead) == 3)
	{
		CapBloodLine_SpawnSpaReinforcements();
	}

	if (sti(pchar.questTemp.CapBloodLine.SpaSoldierDead) == 4)
	{
		PlaySound("Ambient\SEA\Ship_bell_Alarm.wav");
		pchar.quest.CapBloodLine_SpanishSoldierAlarm = true;
		if (CheckAttribute(pchar, "quest.CapBloodLine_q2_Late")) DeleteAttribute(pchar, "quest.CapBloodLine_q2_Late");
		DoQuestFunctionDelay("CapBloodLine_q2_Late", 7);
	}
}

void CapBloodLine_SpawnSpaReinforcements()
{
	ref sld;
	int i;
	string sID;
	string sQuest;
	string sGroup;

	sGroup = "CapBloodLine_SpaReinforcements";

	for (i = 1; i <= 3; i++)
	{
		sID = "SpaReinforce_A_" + i;

		sld = GetCharacter(NPC_GenerateCharacter(sID, "sold_spa_" + (rand(7) + 1), "man", "man", sti(pchar.rank) + CapBloodLine_GetSpaSoldierAddRank(), SPAIN, 1, false));
		sld.City = "Bridgetown";
		sld.CityType = "soldier";
		SetFantomParamFromRank(sld, sti(pchar.rank) + CapBloodLine_GetSpaSoldierAddRank(), true);
		LAi_LoginInCaptureTown(sld, true);
		LAi_SetLoginTime(sld, 0.0, 24.0);
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
		LAi_group_MoveCharacter(sld, sGroup);
		sld.greeting = "soldier_common";
		sld.dialog.filename = "Common_Soldier.c";
		sld.dialog.currentnode = "first time";

		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "reload", "reload3_back");
	}

	for (i = 1; i <= 2; i++)
	{
		sID = "SpaReinforce_B_" + i;

		sld = GetCharacter(NPC_GenerateCharacter(sID, "sold_spa_" + (rand(7) + 1), "man", "man", sti(pchar.rank) + CapBloodLine_GetSpaSoldierAddRank(), SPAIN, 1, false));
		sld.City = "Bridgetown";
		sld.CityType = "soldier";
		SetFantomParamFromRank(sld, sti(pchar.rank) + CapBloodLine_GetSpaSoldierAddRank(), true);
		LAi_LoginInCaptureTown(sld, true);
		LAi_SetLoginTime(sld, 0.0, 24.0);
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
		LAi_group_MoveCharacter(sld, sGroup);
		sld.greeting = "soldier_common";
		sld.dialog.filename = "Common_Soldier.c";
		sld.dialog.currentnode = "first time";

		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "reload", "reload4_back");
	}

	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
}

void CapBloodLine_FailTimer(string qName)
{
	SetFunctionTimerConditionParam("CapBloodLine_q2_Late", 0, 0, 0, GetHour() + 3, false);
}

void CapBloodLine_BridgetownReloadsLock(bool bLock) // Блокировать всё, кроме выхода на плантации
{
	string sLocation = "Bridgetown_town";
	string sLocators[24];
	int i;
	sLocators[0]  = "reload1_back";
	sLocators[1]  = "reload2_back";
	sLocators[2]  = "reload3_back";
	sLocators[3]  = "reload4_back";
	sLocators[4]  = "reload5_back";
	sLocators[5]  = "reload6_back";
	sLocators[6]  = "reload7_back";
	sLocators[7]  = "reload8_back";
	sLocators[8]  = "reload9_back";
	sLocators[9]  = "reload10_back";
	sLocators[10] = "reload11_back";
	sLocators[11] = "reloadR1";
	sLocators[12] = "reloadT1";
	sLocators[13] = "reload91_back";
	sLocators[14] = "gate_back";
	sLocators[15] = "houseS2";
	sLocators[16] = "houseH1";
	sLocators[17] = "houseF2";
	sLocators[18] = "houseS3";
	sLocators[19] = "houseSp2";
	sLocators[20] = "houseSp1";
	sLocators[21] = "houseF1";
	sLocators[22] = "houseS1";
	sLocators[23] = "boat";

	for (i = 0; i < 24; i++)
	{
		LocatorReloadEnterDisable(sLocation, sLocators[i], bLock);
	}
}

void CapBloodLine_MakeSpaSoldiersPeaceful()
{
	ref sld;
	string sID;
	string sQuest;

	for (int i = 0; i < 11; i++)
	{
		sID = "SpaSolder_" + i;
		sQuest = "CapBloodLine_SpaSoldierDead_" + i;
		DeleteQuestCondition(sQuest);

		if (GetCharacterIndex(sID) == -1) continue;
		sld = CharacterFromID(sID);
		if (LAi_IsDead(sld)) continue;

		LAi_group_MoveCharacter(sld, LAI_GROUP_NEITRAL);
	}
	LAi_group_SetRelation(LAI_GROUP_NEITRAL, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
}

void CapBloodLine_MedicalSuppliesMinusWeight()
{
	ref itm = ItemsFromID("MedicalSupplies");
	float fWeight = stf(itm.Weight) - 0.1;

	if (fWeight < 0.0) fWeight = 0.0;

	itm.Weight = fWeight;
}

void CapBloodLine_ReturnAtPlantation(string qName)
{
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_258"), "Reload_To_Location", 0.1, 4);
	SetLaunchFrameReloadLocationParam("Bridgetown_Plantation_G6", "goto", "goto1", "CapBloodLine_firstEnterHome");
	LaunchFrameForm();

	Environment.date.month = 4;
	Environment.date.day = 16;
	SetCurrentTime(23, 00);
	RefreshLandTime();
	RecalculateJumpTable();
}

void CapBloodLine_BishopOnHouse(string qName) // В хате у Бишопа - отправляет в резиденцию
{
	ref sld = CharacterFromID("Bishop");
	sld.dialog.currentnode = "BStep";
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1);

	QuestPointerDelLoc("Bridgetown_Plantation", "reload", "HouseSp1");
	QuestPointerDelLoc("Bridgetown_Plantation_G6", "reload", "reload1");
	ChrDisableReloadToLocation = true;
}

void CapBloodLine_StartMissisStidQuest() // Готовим резиденцию и губернатора
{
	LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", true);
	LocatorReloadEnterDisable("Bridgetown_Townhall", "reload2", true);
	LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", true);
	Pchar.questTemp.CapBloodLine.stat = "CureMisStid";
	//сроки 4 часа
	PChar.quest.CapBloodLineTimer_1.win_condition.l1 = "Timer";
	PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.hour = 4;
	PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
	PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
	PChar.quest.CapBloodLineTimer_1.function = "CapBloodLine_q1_Late";
	CapBloodLine_ReachQuestPointer_Plantation("");
	Tutorial_BloodPrologue_TimeScale_Delay();

	ref sld = &Characters[GetCharacterIndex("Bridgetown_Mayor")];
	sld.Dialog.CurrentNode = "First Time";
	AddLandQuestmark_Main(sld, "CapBloodLine");

	DoQuestReloadToLocation("Bridgetown_Plantation", "reload", "HouseSp1", "CapBloodLine_StartMissisStidQuest_QR");
	SetFunctionLocationConditionDelay("CapBloodLine_StartMissisStidQuest_1", "Bridgetown_town", false, 0.2);
	LocatorReloadEnterDisable("Bridgetown_Plantation", "reload1_back", false);
	LocatorReloadEnterDisable("Bridgetown_Plantation", "HouseSp1", true);
}

void CapBloodLine_StartMissisStidQuest_QR(string qName)
{
	AddQuestRecord("CapBloodLine_q1", "13");
}

void CapBloodLine_StartMissisStidQuest_1(string qName) // Отдельно для бойца
{
	ChangeBridgeTownDialogs(false); // Заново, из-за перемотки времени
	ref sld = &characters[GetCharacterbyLocation("Bridgetown_town", "soldiers", "soldier2")];
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.Dialog.CurrentNode = "First Guard";
	sld.protector = true;
	sld.protector.CheckAlways = 1 ;
	LAi_RemoveLoginTime(sld);
	LoginCharacter(sld, "BridgeTown_town");
	AddLandQuestmark_Main(sld, "CapBloodLine");
	chrDisableReloadToLocation = true;
}

void CapBloodLine_BishopInDiekeQuest(string qName)
{
	ref sld = characterFromID("Bishop");
	if (sld.location != "Bridgetown_Plantation_Sp1")
	{
		ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_Sp1", "goto", "goto1");
	}
	sld.Dialog.CurrentNode = "BStep_2";
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1);
}

void CapBloodLine_ReloadFromBishopsHouse(string qName)
{
	DoQuestReloadToLocation("Bridgetown_Plantation", "reload", "HouseSp1", "");
	LocatorReloadEnterDisable("Bridgetown_Plantation", "HouseSp1", true);
	chrDisableReloadToLocation = false;
	bDisableCharacterMenu = false;
}

float PB_Round2(float f)
{
	if (f < 0.0)
	{
		return makefloat(makeint(f * 100.0 - 0.5)) / 100.0;
	}

	return makefloat(makeint(f * 100.0 + 0.5)) / 100.0;
}

void CapBloodLine_DrawWeapon(string qName)
{
	LAi_SetFightMode(PChar, true);
}

void CapBloodLine_TalkOnDeck()  // Спрашиваем каждого о планах на будущее
{
	string sChars[3];

	sChars[0] = "Dieke";
	sChars[1] = "Ogl";
	sChars[2] = "Hugtorp";

	for (int i = 0; i < 3; i++)
	{
		int iChar = GetCharacterIndex(sChars[i]);
		if (iChar != -1)
		{
			ref sld = &Characters[iChar];
			LAi_CharacterEnableDialog(sld);
			AddLandQuestMark_Main(sld, "CapBloodLine");
		}
	}
}

void CapBloodLine_OfficersCount() // Счётчик разговоров
{
	if (!CheckAttribute(pchar, "CBL.OfficersCount")) pchar.CBL.OfficersCount = 0;
	pchar.CBL.OfficersCount = sti(pchar.CBL.OfficersCount) + 1;

	if (sti(pchar.CBL.OfficersCount) > 4)
	{
		pchar.CBL.OfficersCount = 4;
	}

	if (sti(pchar.CBL.OfficersCount) >= 4 && !CheckAttribute(pchar, "CBL.OfficersCountDone"))
	{
		CapBlood_DoneOfficersRecruit_StartOffTutorial("");

		pchar.CBL.OfficersCountDone = true;
		DeleteAttribute(pchar, "CBL.OfficersCount");
	}
}

void CapBloodLine_DinnerTime(string qName)
{
	QuestPointerDelLoc("Bridgetown_Town", "quest", "quest26");
	LAi_FadeEX(0.5, 0.5, 0.5, "CapBloodLine_DinnerTime_1", "", "");
	CapBloodLaspEpisode("");
}

void CapBloodLine_DinnerTime_1(string qName)
{
	LAi_SetStayType(pchar);
	TeleportCharacterToPosAy(pchar, 22.78, 2.66, 103.49, 2.4);
	locCameraFromToPos(19.22, 4.49, 102.1, true, 27.93, 1.34, 100.63);

	ref sld = GetCharacter(NPC_GenerateCharacter("CBL_DialogNPC", "huber_0", "man", "man", 1, ENGLAND, 1, false));
	sld.name 	= FindPersonalName("CBL_Officers");
	sld.lastname = "";
	LAi_LoginInCaptureTown(sld, true);
	// sld.lifeDay = 0;
	sld.Dialog.CurrentNode = "BloodTalkWithCrew";
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	ChangeCharacterAddressGroup(sld, "Bridgetown_Town", "goto", "goto1");
	TeleportCharacterToPosAy(sld, 27.98, 2.0, 98.49, -0.85);
	LAi_SetActorType(sld);
	LAi_ActorDialogDelay(sld, pchar, "", 1);
}

void CapBloodLine_MorningIsComming()
{
	ref sld = CharacterFromID("CBL_DialogNPC");
	sld.lifeDay = 0;
	ChangeCharacterAddressGroup(sld, "none", "", "");

	string sChars[4];

	sChars[0] = "Dieke";
	sChars[1] = "Ogl";
	sChars[2] = "Hugtorp";
	sChars[3] = "Volverston";

	for (int i = 0; i < 4; i++)
	{
		int iChar = GetCharacterIndex(sChars[i]);
		if (iChar != -1)
		{
			sld = &Characters[iChar];
			// LAi_SetCitizenType(sld);
			DeleteAttribute(sld, "SavedTeleportPos");
		}
	}
	LAi_SetActorType(pchar);

	bDisableCharacterMenu = true;
	InterfaceStates.Buttons.Save.enable = false;
	chrDisableReloadToLocation = true;

	DoQuestFunctionDelay("CapBloodLine_MorningIsComming_2", 1.0);
}

void CapBloodLine_MorningIsComming_2(string qName)
{
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_13"), "", 0, 3);
	LaunchFrameForm();
	DoQuestCheckDelay("CapBloodLine_MorningIsComming_1", 2.5);

	if (GetDataYear() == 1666 && GetDataMonth() == 4 && GetDataDay() == 19)
	{
		WaitDate("", 0, 0, 1, 0, 0);
		// RecalculateJumpTable();
	}

	SetCurrentTime(6, 0);
	RefreshWeather();
	RefreshLandTime();
}

void CapBloodLine_RedrawWeapons(string qName)
{
	ref sld;
	int i;
	string sChars[5];
	string sBlade, sGun;

	sChars[0] = pchar.id;
	sChars[1] = "Volverston";
	sChars[2] = "Hugtorp";
	sChars[3] = "Dieke";
	sChars[4] = "Ogl";

	for (i = 0; i < 5; i++)
	{
		if (GetCharacterIndex(sChars[i]) == -1) continue;

		sld = CharacterFromID(sChars[i]);

		sBlade = GetCharacterEquipByGroup(sld, BLADE_ITEM_TYPE);
		sGun = GetCharacterEquipByGroup(sld, GUN_ITEM_TYPE);

		if (sBlade != "")
		{
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			EquipCharacterByItem(sld, sBlade);
		}

		if (sGun != "")
		{
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			EquipCharacterByItem(sld, sGun);
		}
	}
}

void CapBloodLine_DiekeSeeBoat()
{
	ref sld = CharacterFromID("Dieke");
	TeleportCharacterToPosAy(sld, 6.79, 8.4, 84.32, 3.2);

	LAi_FadeEx(0.5, 0.5, 0.5, "CapBloodLine_DiekeSeeBoat_1", "", "");
}

void CapBloodLine_DiekeSeeBoat_1(string qName)
{
	locCameraSleep(false);
	locCameraFlyToPositionLookToPoint(7.21, 11.73, 78.26, 7.21, 11.48, 78.92, 6.61, 8.17, 86.98, 1, 3450/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_DiekeSeeBoat_2";
}

void CapBloodLine_DiekeSeeBoat_2()
{
	locCameraSleep(true);

	ref sld = CharacterFromID("Dieke");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);

	LAi_FadeEx(1.0, 1.0, 1.0, "", "CapBloodLine_DiekeSeeBoat_3", "");
}

void CapBloodLine_DiekeSeeBoat_3(string qName)
{
	ref sld = CharacterFromID("Dieke");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	TeleportCharacterToPosAy(sld, 30.79, 4.53, 112.2, 0.0);

	locCameraSleep(false);
	locCameraFromToPos(34.6, 6.09, 117.39, true, 25.32, 3.66, 114.02);
}

void CapBloodLine_DiegoOnDeck()
{
	string sChar[2];

	sChar[0] = "Volverston";
	sChar[1] = "Dieke";

	for (int i = 0; i < 2; i++)
	{
	    if (GetCharacterIndex(sChar[i]) == -1) continue;
		ref sld = CharacterFromID(sChar[i]);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "quest", "quest26", "", -1);
	}

   	LAi_FadeEx(1.0, 1.0, 1.0, "", "CapBloodLine_DiegoOnDeck_2", "");
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "quest", "quest26", "", -1);
}

void CapBloodLine_DiegoOnDeck_2(string qName)
{
	ref sld;
	string sChars[3];

	sChars[0] = "Ogl";
	sChars[1] = "Dieke";
	sChars[2] = "Volverston";

	for (int i = 0; i < 3; i++)
	{
		if (GetCharacterIndex(sChars[i]) == -1) continue;

		sld = CharacterFromID(sChars[i]);
		if (sld.location != pchar.location) ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest22");

		LAi_SetStayType(sld);

		if (sChars[i] == "Ogl") TeleportCharacterToPosAy(sld, 24.44, 2.66, 100.34, -0.7);
		if (sChars[i] == "Dieke") TeleportCharacterToPosAy(sld, 26.07, 2.62, 102.01, -0.7);
		if (sChars[i] == "Volverston") TeleportCharacterToPosAy(sld, 23.11, 2.71, 98.93, -0.7);
	}

	if (GetCharacterIndex("Hugtorp") != -1)
	{
		sld = CharacterFromID("Hugtorp");
		GiveItem2Character(sld, "kocherg");
		EquipCharacterByItem(sld, "kocherg");

		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest22");
		TeleportCharacterToPosAy(sld, 23.0, 2.59, 108.0, 3.0);
	}

	sld = GetCharacter(NPC_GenerateCharacter("Diego_Clone", "Esp_0", "man", "man", 1, SPAIN, -1, false));
	FantomMakeCoolFighter(sld, 20, 65, 40, "blade25", "pistol3", 80);
	sld.name = FindPersonalName("Diego_name");
	sld.lastname = FindPersonalName("De_Espinosa_lastname");
	sld.Dialog.Filename = "Quest\CapBloodLine\Bishop.c";
	sld.Dialog.CurrentNode = "DiegoOnDeck";
	LAi_LoginInCaptureTown(sld, true);
	LAi_SetLoginTime(sld, 0.0, 24.0);
	ChangeCharacterAddressGroup(sld, pchar.location, "quest", "quest22");
	TeleportCharacterToPosAy(sld, 21.33, 2.84, 106.73, 0.0);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

	LAi_SetStayType(pchar);
	TeleportCharacterToPosAy(pchar, 22.7, 2.68, 101.87, -0.3);
	// locCameraFromToPos(21.87, 4.69, 99.08, true, 19.46, 6.69, 108.58);
	locCameraFromToPos(21.45, 5.04, 97.27, true, 23.43, 1.38, 106.66);
}

void CapBloodLine_DiegoDeckStartFight(string qName)
{
	LAi_FadeEx(1.0, 1.0, 1.0, "CapBloodLine_DiegoDeckStartFight_1", "", "CapBloodLine_SaveOnDeckFight");

	string sLang = "English";
	if (LanguageGetLanguage() == "Russian") sLang = "Russian";
	PlaySound("Voice\" + sLang + "\EvilPirates01.wav");

	ref sld = CharacterFromID("Hugtorp");
	string sBlade;
	int iKochergQty;

	if (GetCharacterEquipByGroup(sld, BLADE_ITEM_TYPE) == "kocherg")
	{
		iKochergQty = GetCharacterItem(sld, "kocherg");
		TakeNItems(sld, "kocherg", -iKochergQty);
		sBlade = ForceFindCharacterItemByGroup(sld, BLADE_ITEM_TYPE);
		TakeNItems(sld, "kocherg", iKochergQty);

		if (sBlade != "") EquipCharacterByItem(sld, sBlade);
		else EquipCharacterByItem(sld, "kocherg");
	}

	LAi_ActorTurnToLocator(sld, "quest", "quest11");
	DeleteAttribute(&TEV, "StopTimeScale");
}

void CapBloodLine_DiegoDeckStartFight_1(string qName)
{
	ref sld;
	int i;
	string sChars[4];

	sChars[0] = "Ogl";
	sChars[1] = "Dieke";
	sChars[2] = "Volverston";
	sChars[3] = "Hugtorp";

	for (i = 0; i < 4; i++)
	{
		if (GetCharacterIndex(sChars[i]) == -1) continue;

		sld = CharacterFromID(sChars[i]);
		if (sld.location != pchar.location) continue;

		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}

	if (GetCharacterIndex("Diego_Clone") != -1)
	{
		sld = CharacterFromID("Diego_Clone");
		ChangeCharacterAddressGroup(sld, "none", "", "");

		ref chr = GetCharacter(NPC_GenerateCharacter("Diego_Espinosa", "Esp_0", "man", "man", 25, SPAIN, -1, false));
		FantomMakeCoolFighter(chr, 20, 65, 40, "blade25", "pistol3", 80);
		chr.name = FindPersonalName("Diego_name");
		chr.lastname = FindPersonalName("De_Espinosa_lastname");
		chr.FaceId = 1006;
		chr.Dialog.Filename = "Quest\CapBloodLine\Bishop.c";
		// chr.Dialog.CurrentNode = "DiegoOnDeck";
		LAi_LoginInCaptureTown(chr, true);
		LAi_SetImmortal(chr, true);
		ChangeCharacterAddressGroup(chr, pchar.location, "quest", "quest11");
		LAi_SetLayTypeNoGroup(chr);
		LAi_SetImmortal(sld, true);
		LAi_CharacterDisableDialog(chr);
		LAi_group_MoveCharacter(chr, LAI_GROUP_ACTOR);
		LAi_group_SetRelation(LAI_GROUP_ACTOR, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		LAi_group_SetRelation(LAI_GROUP_ACTOR, "DiegoGuards", LAI_GROUP_NEITRAL);
		TeleportCharacterToPosAy(chr, 22.99, 2.67, 102.28, 2.1);
	}

	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

		sld = CharacterFromID("DiegoGuard_" + i);
		if (sld.location != pchar.location) continue;

		switch (i)
		{
			case 1: TeleportCharacterToPosAy(sld, 21.93, 2.61, 106.74, 0.0); break;
			case 2: TeleportCharacterToPosAy(sld, 20.63, 2.65, 105.58, 0.0); break;
			case 3: TeleportCharacterToPosAy(sld, 21.54, 2.63, 105.93, 0.0); break;
			case 4: TeleportCharacterToPosAy(sld, 20.93, 3.37, 106.88, 0.0); break;
		}

		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "DiegoGuards");
	}
	sld = CharacterFromID("Esteban_Espinosa");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "DiegoGuards");
	TeleportCharacterToPosAy(sld, 22.04, 2.61, 106.35, 0.0);

	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("DiegoGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("DiegoGuards", LAI_GROUP_PLAYER, true);

	EndQuestMovie();
	bDisableCharacterMenu = false;
	InterfaceStates.Buttons.Save.enable = true;
	locCameraResetState();
	locCameraTarget(pchar);
	CharacterTurnToLoc(pchar, "quest", "quest11");
}

void CapBloodLine_SaveOnDeckFight(string qName)
{
	DoQuestFunctionDelay("MakeQuestAutoSaveDelay", 0.1);
}

void CapBloodLine_EstebanSurrendered_1(string qName)
{
	LAi_FadeEx(1.0, 1.0, 1.0, "", "CapBloodLine_EstebanSurrendered_2", "");
	LAi_SetActorType(CharacterFromID("Esteban_Espinosa"));
	LAi_SetActorType(CharacterFromID("Dieke"));
}

void CapBloodLine_EstebanSurrendered_2(string qName) // размещаем поверженных
{
	ref sld;
	int i, iPos;

	ResetTimeScale();
	TEV.StopTimeScale = 1;
	TEV.StopTimeScale = true;

	DoQuestFunctionDelay("CapBloodLine_RemoveDeadDiegoGuards", 0.5); // Удалить трупы, чтобы не мешали

	// Убираем офицеров с места сдачи испанцев
	string sOfficers[4], sLocators[4];

	sOfficers[0] = "Dieke";      sLocators[0] = "quest24";
	sOfficers[1] = "Ogl";        sLocators[1] = "aloc9";
	sOfficers[2] = "Hugtorp";    sLocators[2] = "quest23";
	sOfficers[3] = "Volverston"; sLocators[3] = "quest16";

	for (i = 0; i < 4; i++)
	{
		if (GetCharacterIndex(sOfficers[i]) == -1) continue;

		sld = CharacterFromID(sOfficers[i]);

		if (sOfficers[i] == "Ogl") ChangeCharacterAddressGroup(sld, pchar.location, "rld", sLocators[i]);
		else ChangeCharacterAddressGroup(sld, pchar.location, "quest", sLocators[i]);
		DeleteAttribute(sld, "GenQuest.CantRun");
		if (sOfficers[i] == "Dieke")
		{
			LAi_SetActorTypeNoGroup(sld);
			TeleportCharacterToPosAy(sld, 33.2, 4.52, 108.75, 2.7);
		}
	}

	sld = CharacterFromID("Esteban_Espinosa");
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	TeleportCharacterToPosAy(sld, 23.80, 2.65, 103.66, -2.2);
	LAi_SetGroundSitTypeNoGroup(sld);
	LAi_CharacterDisableDialog(sld);

	iPos = 0;
	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

		sld = CharacterFromID("DiegoGuard_" + i);
		if (sld.location != pchar.location) continue;
		if (LAi_IsDead(sld)) continue;

		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);

		switch (iPos)
		{
			case 0: TeleportCharacterToPosAy(sld, 24.93, 2.65, 103.56, 3.0); break;
			case 1: TeleportCharacterToPosAy(sld, 23.34, 2.65, 104.66, -1.1); break;
			case 2: TeleportCharacterToPosAy(sld, 25.58, 2.62, 104.4, 1.9); break;
			case 3: TeleportCharacterToPosAy(sld, 23.97, 2.63, 105.48, -0.2); break;
		}

		LAi_SetGroundSitTypeNoGroup(sld);
		LAi_CharacterDisableDialog(sld);
		iPos++;
	}
	TeleportCharacterToPosAy(pchar, 25.97, 2.61, 106.4, 2.4);
	LAi_SetStayType(pchar);
	locCameraFlyToPositionLookToPointDelay(22.5, 3.13, 102.2, 23.92, 5.06, 103.57, 26.02, 3.82, 105.92, 1, 1.0, 10.55);
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("CapBloodLine_EstebanSurrendered_4", 7.0);
}

void CapBloodLine_RemoveDeadDiegoGuards(string qName)
{
	ref sld;
	int i, j, iChar;

	for (i = 1; i <= 4; i++)
	{
		iChar = GetCharacterIndex("DiegoGuard_" + i);
		if (iChar == -1) continue;

		sld = &Characters[iChar];
		if (!LAi_IsDead(sld)) continue;

		for (j = 0; j < Dead_Char_num; j++)
		{
			if (Dead_Characters[j].index != iChar) continue;

			Dead_DelLoginedCharacter(&Dead_Characters[j]);
			break;
		}
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
}

void CapBloodLine_EstebanSurrendered_4(string qName)
{
	ref sld = CharacterFromID("Dieke");
	sld.dialog.currentnode = "DiekeOnDeck_4";
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "CapBloodLine_EstebanSurrendered_5", -1);
}

void DiekeOnDeck_StartSeaFightNow_Exit(string qName)
{
	SpaCrewAtack();
	// CapBlood_CheckOfficersRecruit();

	string cQuest = "CapBloodLine_FightOnSea";
	pchar.quest.(cQuest).win_condition.l1 = "EnterToSea";
	pchar.quest.(cQuest).function = "CapBloodLine_FightOnSea";

	Pchar.location.from_sea = "Bridgetown_town";
	setWDMPointXZ("Bridgetown_town");

	DeleteAttribute(&questToSeaLoginer, "");
	QuestToSeaLogin_PrepareLoc("Barbados", "islandShips1", "ship_2", false);
	QuestToSeaLogin_Launch();

	CapBloodLine_ClearSaveCord();
	DeleteQuestCondition("CapBloodLine_SeaFightWait_1");
}

void CapBloodLine_FightOnSea(string qName)
{
	DoQuestFunctionDelay("BloodLine_SpaCrewAtack_StartSeaTutorials", 1.5);
	LAi_LocationFightDisable(&Locations[FindLocation("Bridgetown_Town")], false);
	SpaCrewAtack_SetTasks();
	BloodLine_GlobalTutor_SetRestricts();
	DoQuestFunctionDelay("CapBloodLine_MakeQuickSave", 1.0);

	Island_SetGotoEnableLocal("Barbados", "reload_1", false);
	Island_SetGotoEnableLocal("Barbados", "reload_fort1", false);
	Island_SetGotoEnableLocal("Barbados", "reload_2", false);
	Island_SetGotoEnableLocal("Barbados", "reload_3", false);
	Island_SetGotoEnableLocal("Barbados", "reload_4", false);
}

void CapBloodLine_MakeQuickSave(string qName)
{
	MakeQuickSave();
}

void CapBloodLine_SpaCrewAtack_GroupDeath(string qName)
{
	DoQuestFunctionDelay("CapBloodLine_SpaCrewAtack_GroupDeath_1", 2.0);
}

void CapBloodLine_SpaCrewAtack_GroupDeath_1(string qName)
{
	DoReloadFromSeaToLocation("Bridgetown_town", "quest", "quest22");
}

void CapBloodLine_ClearSaveCord()
{
	ref sld;
	int i;
	string sChars[2];

	sChars[0] = "Esteban_Espinosa";
	sChars[1] = "Diego_Espinosa";

	for (i = 0; i < 2; i++)
	{
		if (GetCharacterIndex(sChars[i]) == -1) continue;
		if (!CharacterIsAlive(sChars[i])) continue;

		sld = CharacterFromID(sChars[i]);

		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
		ChangeCharacterAddressGroup(sld, "none", "", "");
		AddPassenger(pchar, sld, true);
	}

	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

		sld = CharacterFromID("DiegoGuard_" + i);
		if (LAi_IsDead(sld)) continue;

		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
		ChangeCharacterAddressGroup(sld, "none", "", "");
		AddPassenger(pchar, sld, true);
	}

	chrDisableReloadToLocation = false;
	pchar.NoNavyPenalty = true;
	DelBakSkillAttr(pchar);

	int iFoodPerDay = makeint((GetCrewQuantity(pchar) + 5.1) / 10.0 + GetPassengersQuantity(pchar) / 10.0);
	iFoodPerDay += makeint((GetCargoGoods(pchar, GOOD_SLAVES) + 6) / 20.0);
	if (iFoodPerDay == 0) iFoodPerDay = 1;
	SetCharacterGoods(pchar, GOOD_FOOD, iFoodPerDay * 7);
}

void CapBloodLine_SeaFightWait()
{
	ref sld;
	int i;
	string sChars[4];

	sChars[0] = "Dieke";
	sChars[1] = "Ogl";
	sChars[2] = "Hugtorp";
	sChars[3] = "Volverston";

	for (i = 0; i < 4; i++)
	{
		if (GetCharacterIndex(sChars[i]) == -1) continue;

		sld = CharacterFromID(sChars[i]);
		LAi_CharacterEnableDialog(sld);
		LAi_SetStayTypeNoGroup(sld);
	}
	SetFunctionLocationCondition("CapBloodLine_SeaFightWait_1", "Bridgetown_Town", true);
	SetFunctionLocatorCondition("CapBloodLine_SeaFightWait_2", "Bridgetown_Town", "quest", "quest27", false);
	QuestPointerToLoc("Bridgetown_Town", "quest", "quest27");

    LAi_SetPlayerType(pchar);
	chrDisableReloadToLocation = false;
	DeleteAttribute(&TEV, "StopTimeScale");
}

void CapBloodLine_SeaFightWait_1(string qName)
{
	ref sld;
	int i, iPos;
	string sOfficers[4];

	if (GetCharacterIndex("Esteban_Espinosa") != -1)
	{
		sld = CharacterFromID("Esteban_Espinosa");
		CheckCharacterPosAndTeleport(sld, 23.80, 2.65, 103.66, -2.2, 0.3);
	}

	sld = CharacterFromID("Diego_Espinosa");
	CheckCharacterPosAndTeleport(sld, 22.99, 2.67, 102.28, 2.1, 0.3);

	iPos = 0;

	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

		sld = CharacterFromID("DiegoGuard_" + i);
		if (!CheckAttribute(sld, "location")) continue;
		if (sld.location != pchar.location) continue;

		switch (iPos)
		{
			case 0: CheckCharacterPosAndTeleport(sld, 24.93, 2.65, 103.56, 3.0, 0.3); break;
			case 1: CheckCharacterPosAndTeleport(sld, 23.34, 2.65, 104.66, -1.1, 0.3); break;
			case 2: CheckCharacterPosAndTeleport(sld, 25.58, 2.62, 104.4, 1.9, 0.3); break;
			case 3: CheckCharacterPosAndTeleport(sld, 23.97, 2.63, 105.48, -0.2, 0.3); break;
		}

		iPos++;
	}

	VolverstonAdd();
	HugtorpAdd();
	DiekeAdd();
	OglAdd();

	sOfficers[0] = "Volverston";
	sOfficers[1] = "Hugtorp";
	sOfficers[2] = "Dieke";
	sOfficers[3] = "Ogl";

	for (i = 0; i < 4; i++)
	{
		sld = CharacterFromID(sOfficers[i]);
		sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
		sld.dialog.currentnode = sOfficers[i] + "_OfficerNode";
	}
}

void CapBloodLine_SeaFightWait_2(string qName)
{
	ref sld;
	Pchar.Ship.Type = GenerateShipExt(SHIP_ARABELLA, true, Pchar);
	Pchar.Ship.name = FindPersonalName("Blad2_ship");
	SetBaseShipData(Pchar);
	Pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
	SetCrewQuantity(Pchar, GetMinCrewQuantity(Pchar));
	sld = GetRealShip(sti(pchar.Ship.Type));
	sld.ship.upgrades.hull = 1; // хулл сбросим до дефолтного
	Set_My_Cabin();

	SetCharacterGoods(Pchar, GOOD_FOOD, 300);
	SetCharacterGoods(Pchar, GOOD_BALLS, 300);//2000);
	SetCharacterGoods(Pchar, GOOD_GRAPES, 300);//700);
	SetCharacterGoods(Pchar, GOOD_KNIPPELS, 300);//700);
	SetCharacterGoods(Pchar, GOOD_BOMBS, 300);//1500);
	SetCharacterGoods(Pchar, GOOD_POWDER, 1000);
	SetCharacterGoods(Pchar, GOOD_PLANKS, 100);
	SetCharacterGoods(Pchar, GOOD_RUM, 40);//600);
	SetCharacterGoods(Pchar, GOOD_WEAPON, 50);//2000);

	DoQuestFunctionDelay("DiekeOnDeck_StartSeaFightNow_Exit", 1.0);
	QuestPointerDelLoc("Bridgetown_Town", "quest", "quest27");
}

void CapBloodLine_PittInCabin(string qName) // Размещаем Питта в каюте
{
	ref sld = CharacterFromID("Pitt");
	ChangeCharacterAddressGroup(sld, "Cabin_Quest", "goto", "goto1");
	TeleportCharacterToPosAy(sld, 1.83, 9.05, 5.41, 0.0);
}

void BloodLine_SpaCrewAtack_NPCDeath0(string qName)
{
	BloodLine_SpaCrewAtack_NPCDeath(qName);
}

void BloodLine_SpaCrewAtack_NPCDeath1(string qName)
{
	BloodLine_SpaCrewAtack_NPCDeath(qName);
}

void BloodLine_SpaCrewAtack_NPCDeath(string qName)
{
	TW_IncreaseCounter("BloodLine_SeaBattle1", "SeaBattle1_text1", 1);
	BloodLine_SpaCrewAtack_CheckLuggers();
}

void BloodLine_SpaCrewAtack_CheckLuggers()
{
	int iDead = 0;
	int iChar;

	iChar = GetCharacterIndex("SpaBoat_0");
	if (iChar == -1 || LAi_IsDead(&Characters[iChar])) iDead++;

	iChar = GetCharacterIndex("SpaBoat_1");
	if (iChar == -1 || LAi_IsDead(&Characters[iChar])) iDead++;

	if (iDead < 2) return;

	aref arCnt;
	if (CheckAttribute(&objTask, "BloodLine_SeaBattle1.texts.SeaBattle1_text0"))
	{
		makearef(arCnt, objTask.BloodLine_SeaBattle1.texts.SeaBattle1_text0);
		TW_ColorWeak(arCnt);
	}

	Group_DeleteAtEnd("SpaCrew");

	AddCharacterExpToSkill(pchar, "Sailing", 100);       // Нава
	AddCharacterExpToSkill(pchar, "Leadership", 100);    // Лидерство
	AddCharacterExpToSkill(pchar, "Cannons", 100);       // Орудия
	AddCharacterExpToSkill(pchar, "Accuracy", 100);      // Меткость

	int iFoodPerDay = makeint((GetCrewQuantity(pchar) + 5.1) / 10.0 + GetPassengersQuantity(pchar) / 10.0);
	iFoodPerDay += makeint((GetCargoGoods(pchar, GOOD_SLAVES) + 6) / 20.0);
	if (iFoodPerDay == 0) iFoodPerDay = 1;
	SetCharacterGoods(pchar, GOOD_FOOD, iFoodPerDay * 7);

	DoQuestFunctionDelay("CapBloodLine_SpanishSoldierDie", 2.0);
	DoQuestFunctionDelay("TW_Finish_BloodLine_SeaBattle1", 2.0);
	TW_Release();
	// DoQuestFunctionDelay("BloodLine_GlobalTutor_ReloadToCabinDialog", 6.0);
}

void CapBloodLine_SpanishSoldierDie(string qName)
{
	SetFunctionLocationCondition("CapBloodLine_SpanishSoldierSwim", "Bridgetown_town", false);
	DoReloadFromSeaToLocation("Bridgetown_town", "quest", "quest22");
}

void CapBloodLine_SpanishSoldierSwim(string qName)
{
	LAi_FadeEx(0.0, 1.0, 1.0, "", "CapBloodLine_SpanishSoldierSwimCamera", "");

	// locCameraFlyToPositionLookToPoint(-52.78, 17.25, 19.47, -35.15, 8.38, 34.101, -33.18, 7.40, 35.8, 1, 10550 / GetDeltaTime());
	// Pchar.FuncCameraFly = "CapBloodLine_SpanishSoldierSwim_1";
	CapBloodLine_SpanishSoldierSwim_3();
}

void CapBloodLine_SpanishSoldierSwimCamera(string qName)
{
	locCameraFromToPos(-31.96, 5.78, 47.96, true, -23.82, 0.43, 46.59);
	DoQuestFunctionDelay("CapBloodLine_SpanishSoldierSwim_1", 3.5);

	StopMusic(0);
	PlayMusic("Music\Special\Quest\SantaMisericordia.mp3", 3000);
}

void CapBloodLine_SpanishSoldierSwim_1(string qName)
{
	LAi_FadeEx(1.0, 1.0, 1.0, "", "CapBloodLine_SpanishSoldierSwim_2", "");
}

void CapBloodLine_SpanishSoldierSwim_2(string qName)
{
	ref sld;
	int i;
	float x[3];
	float y[3];
	float z[3];
	float ay[3];

	locCameraSleep(false);

	locCameraFlyToPositionLookToPoint(-25.52, 4.94, 30.89, -3.09, 4.69, 38.45, -8.04, 3.09, 13.3, 1, 13550 / GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_BishopLookingForFight";

	for (i = 1; i <= 6; i++)
	{
		sld = CharacterFromID("CBL_SpaSoldSwim_" + i);
		LAi_type_actor_Reset(sld);
		TeleportCharacterToPosAy(sld, -14.9, 1.0, 28.4, 0.0);
		LAi_ActorRunToLocator(sld, "quest", "quest1", "CapBloodLine_SpanishSoldierVolley", -1);
	}

	sld = CharacterFromID("Bishop");
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", "goto2");
	LAi_SetStayType(sld);
	TeleportCharacterToPosAy(sld, -4.26, 2.64, 32.84, -2.1);

	x[0] = -9.03;  y[0] = 2.62; z[0] = 15.13; ay[0] = -0.7;
	x[1] = -10.34; y[1] = 2.62; z[1] = 15.33; ay[1] = -0.6;
	x[2] = -11.85; y[2] = 2.63; z[2] = 15.29; ay[2] = -0.5;

	for (i = 0; i < 3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("CBL_EngMushketer_" + (i + 1), "urban_mush_eng_3", "man", "mushketer", 10, ENGLAND, -1, true));
		LAi_LoginInCaptureTown(sld, true);

		GiveItem2Character(sld, "mushket_poor");
		EquipCharacterbyItem(sld, "mushket_poor");

		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest20");
		TeleportCharacterToPosAy(sld, x[i], y[i], z[i], ay[i]);
	}

	sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest20");
	TeleportCharacterToPosAy(sld, -4.09, 2.63, 31.75, -2.0);
	LAi_SetStayType(sld);

	sld = GetCharacter(NPC_GenerateCharacter("CBL_OfficerBishop", "off_eng_4", "man", "man", 20, ENGLAND, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", "goto" + (rand(18) + 1));
	TeleportCharacterToPosAy(sld, -3.55, 2.63, 32.57, -2.0);
	LAi_SetStayType(sld);
}

void CapBloodLine_SpanishSoldierSwim_3()
{
	ref sld;
	int i;
	string sModels[4];

	sModels[0] = "citiz_5";
	sModels[1] = "citiz_11";
	sModels[2] = "citiz_18";
	sModels[3] = "citiz_19";

	StartQuestMovie(true, false, true);

	for (i = 1; i <= 2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("CBL_SpaSoldSwim_" + i, "navy_spa_" + (rand(7) + 1), "man", "man", 1, SPAIN, -1, true));
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", "goto" + (rand(18) + 1));
		TeleportCharacterToPosAy(sld, -20.48 + frand(3.0), -1.5, 54.47 + frand(3.0), 0.0);
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
		while (FindCharacterItemByGroup(sld, GUN_ITEM_TYPE) != "") TakeItemFromCharacter(sld, FindCharacterItemByGroup(sld, GUN_ITEM_TYPE));
		LAi_SetHP(sld, 10.0, 10.0);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "quest", "quest1", "", -1.0);
	}

	for (i = 3; i <= 6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("CBL_SpaSoldSwim_" + i, "navy_spa_" + (rand(7) + 1), "man", "man", 1, SPAIN, -1, true));
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", "goto" + (rand(18) + 1));
		TeleportCharacterToPosAy(sld, -20.48 + frand(3.0), -1.5, 48.47 + frand(3.0), 0.0);
		LAi_SetHP(sld, 10.0, 10.0);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "quest", "quest1", "", -1.0);
	}

	for (i = 1; i <= 4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("CBL_Citizen_" + i, sModels[i - 1], "man", "man", 45, ENGLAND, -1, true));
		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", "goto1");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
		CharacterTurnToLoc(sld, "quest", "quest1");
		LAi_group_MoveCharacter(sld, "CBL_EngMushketers");
		TeleportCharacterToPosAy(sld, -16.84 + frand(3.0), 1.48, 12.19 + frand(3.0), 0.0);
	}
}

void CapBloodLine_BishopLookingForFight()
{
	ref sld, chr;
	int i, iDeadMan = 0;

	locCameraSleep(true);

	for (i = 4; i <= 6; i++)
	{
		if (GetCharacterIndex("CBL_SpaSoldSwim_" + i) == -1) continue;

		sld = CharacterFromID("CBL_SpaSoldSwim_" + i);
		if (LAi_IsDead(sld)) continue;

		iDeadMan++;

		if (iDeadMan == 1)
		{
			sld.quest.DeadMan_1 = true;

			chr = CharacterFromID("CBL_EngMushketer_1");
			LAi_SetActorType(chr);

			DoQuestCheckDelay("CapBloodLine_BishopShot_1", 0.70);
		}
		else if (iDeadMan == 2)
		{
			sld.quest.DeadMan_2 = true;

			chr = CharacterFromID("CBL_EngMushketer_2");
			LAi_SetActorType(chr);

			DoQuestCheckDelay("CapBloodLine_BishopShot_2", 0.35);
		}
		else if (iDeadMan == 3)
		{
			sld.quest.DeadMan_3 = true;

			chr = CharacterFromID("CBL_EngMushketer_3");
			LAi_SetActorType(chr);

			DoQuestCheckDelay("CapBloodLine_BishopShot_3", 0.1);
		}
	}
	DoQuestFunctionDelay("CapBloodLine_BishopLookingForFight_1", 1.5);
}

void CapBloodLine_BishopLookingForFight_1(string qName)
{
	ref sld = CharacterFromID("Bishop");
	LAi_SetActorType(sld);
	LAi_ActorMoveToPoint(sld, false, -4.4, 2.64, 34.01, "CapBloodLine_BishipOnPirsTurn", -1.0);
}

void CapBloodLine_StartBoatScene(string qName)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("CBL_BoatChar", "boatchareng", "man", "boatchareng", 1, ENGLAND, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "reload", "boat");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "boat", "", -1);
	CharacterTurnAy(sld, 0.0);

	FadeOutMusic(25000);

	locCameraSleep(false);
	locCameraFlyToPositionLookToPoint(-7.78, 0.58, 33.22, -15.79, 4.78, 39.41, 19.83, 0.65, 91.19, 1, 17550/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_StartBoatScene_1";
}

void CapBloodLine_StartBoatScene_1()
{
	ref sld;

	locCameraSleep(true);
	LAi_FadeEx(1.0, 1.0, 1.0, "", "CapBloodLine_BishopOnLiagas", "");

	sld = CharacterFromID("Bridgetown_Mayor");
	ChangeCharacterAddressGroup(sld, "Bridgetown_Townhall", "sit", "sit1");
	LAi_SetHuberType(sld);
	LAi_CharacterEnableDialog(sld);
	CapBloodLine_TownAlieve();
}

void CapBloodLine_TownAlieve() // Временная видимость жизни
{
	ref sld;
	int i;

	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("CBL_Citizen_" + i) == -1) continue;

		sld = CharacterFromID("CBL_Citizen_" + i);
		sld.dialog.filename = "Common_Citizen.c";
		sld.dialog.currentnode = "first time";
		sld.City = "Bridgetown";
		sld.CityType = "citizen";

		LAi_SetCitizenType(sld);
		LAi_CharacterEnableDialog(sld);
	}

	for (i = 1; i <= 8; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("CBL_EngSoldier_" + i, "urban_eng_" + (rand(2) + 1), "man", "man", 10, ENGLAND, -1, true));
		sld.dialog.filename = "Common_Soldier.c";
		sld.dialog.currentnode = "first time";
		sld.greeting = "soldier_common";
		sld.City = "Bridgetown";
		sld.CityType = "soldier";

		LAi_LoginInCaptureTown(sld, true);
		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", "goto" + (rand(18) + 1));
		LAi_SetCitizenType(sld);
		LAi_CharacterEnableDialog(sld);
	}

	for (i = 1; i <= 3; i++)
	{
		if (GetCharacterIndex("CBL_EngMushketer_" + i) == -1) continue;

		sld = CharacterFromID("CBL_EngMushketer_" + i);
		sld.dialog.filename = "Common_Soldier.c";
		sld.dialog.currentnode = "first time";
		sld.greeting = "soldier_common";
		sld.City = "Bridgetown";
		sld.CityType = "soldier";

		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "goto", "goto" + (rand(18) + 1));
		LAi_SetCitizenType(sld);
		LAi_CharacterEnableDialog(sld);
	}
}

void CapBloodLine_BishopOnLiagas(string qName)
{
	ref sld;
	string sChars[4];

	sChars[0] = "Volverston";
	sChars[1] = "Hugtorp";
	sChars[2] = "Ogl";
	sChars[3] = "Dieke";

	for (int i = 0; i < 4; i++)
	{
		sld = CharacterFromID(sChars[i]);
		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest16");
		LAi_CharacterDisableDialog(sld);

		switch (i)
		{
			case 0: TeleportCharacterToPosAy(sld, 23.01, 2.71, 98.88, -0.7); break;
			case 1: TeleportCharacterToPosAy(sld, 24.44, 2.66, 100.34, -0.7); break;
			case 2: TeleportCharacterToPosAy(sld, 27.61, 2.6, 103.35, -0.7); break;
			case 3: TeleportCharacterToPosAy(sld, 26.14, 2.62, 101.84, -0.7); break;
		}
	}

	ref bishop = CharacterFromID("Bishop");
	ChangeCharacterAddressGroup(bishop, pchar.location, "quest", "quest19");
	TeleportCharacterToPosAy(bishop, 21.33, 2.84, 106.73, 0.0);
	bishop.dialog.currentnode = "BishopOnLlagas_1";
	LAi_SetActorType(bishop);
	LAi_CharacterEnableDialog(bishop);
	LAi_ActorMoveToPoint(bishop, false, 22.24, 2.66, 103.63, "CapBloodLine_BishopDialogOnDeck", -1.0);

	sld = CharacterFromID("CBL_BoatChar");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld.LifeDay = 0;

	sld = GetCharacter(NPC_GenerateCharacter("CBL_OfficerBishop_1", "off_eng_3", "man", "man", 20, ENGLAND, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest11");
	LAi_SetActorType(sld);
	LAi_ActorMoveToPoint(sld, false, 23.21, 2.65, 104.92, "CapBloodLine_BishopOffTurn_1", -1.0);


	sld = CharacterFromID("CBL_OfficerBishop");
	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest11");
	LAi_SetActorType(sld);
	LAi_ActorMoveToPoint(sld, false, 21.29, 2.66, 104.4, "CapBloodLine_BishopOffTurn", -1.0);

	StopMusic(0);
	DeleteAttribute(&TEV, "Music.KeepPlaying");
	KZ|MusicSelect("");
	locCameraSleep(false);
	locCameraFromToPos(21.45, 5.04, 97.27, true, 23.43, 1.38, 106.66);

	LAi_SetStayType(pchar);
	TeleportCharacterToPosAy(pchar, 22.7, 2.68, 101.87, -0.3);
}

void CapBloodLine_ToSeaAgain()
{
	LAi_SetActorType(pchar);
	EndQuestMovie();

	ref sld;
	string sChars[4];
	sChars[0] = "Volverston";
	sChars[1] = "Hugtorp";
	sChars[2] = "Ogl";
	sChars[3] = "Dieke";

	for (int i = 0; i < 4; i++)
	{
		sld = CharacterFromID(sChars[i]);
		LAi_SetActorType(sld);

		switch (i)
		{
			case 0: LAi_ActorRunToLocation(sld, "quest", "quest27", "none", "", "", "", -1); break;
			case 1: LAi_ActorMoveToPoint(sld, false, 32.4, 4.56, 112.23, "", -1.0); break;
			case 2: LAi_ActorMoveToPoint(sld, true, 26.93, 2.59, 109.4, "", -1.0); break;
			case 3: LAi_ActorRunToLocation(sld, "rld", "aloc15", "none", "", "", "", -1); break;
		}
	}
	AddQuestRecord("EscapeFormBarbados", "13");
	DoQuestFunctionDelay("CapBloodLine_ToSeaAgain_1", 2.0);
	pchar.quest.CapBloodLine_LeaveBridgetown.win_condition.l1 = "EnterToSea";
	pchar.quest.CapBloodLine_LeaveBridgetown.function = "CapBloodLine_LeaveBridgetown";
}

void CapBloodLine_ToSeaAgain_1(string qName)
{
	ref sld;
	string sChars[4];

	sChars[0] = "Volverston";
	sChars[1] = "Hugtorp";
	sChars[2] = "Ogl";
	sChars[3] = "Dieke";

	for (int i = 0; i < 4; i++)
	{
		if (GetCharacterIndex(sChars[i]) == -1) continue;

		sld = CharacterFromID(sChars[i]);
		LAi_SetStayTypeNoGroup(sld);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}

	LAi_SetPlayerType(pchar);
	DeleteAttribute(&questToSeaLoginer, "");
	QuestToSeaLogin_PrepareLoc("Barbados", "islandShips1", "ship_2", false);
	QuestToSeaLogin_Launch();
	CapBloodLine_TownAlieveDelete();
}

void CapBloodLine_LeaveBridgetown(string qName)
{
	bQuestDisableMapEnter = true;

	TW_Init_BloodLine_LeaveFort();
	TW_Open("BloodLine_LeaveFort");
}

void CapBloodLine_AddArabellaTrap()
{
	int iLoc = FindLocation("Arabella_Deck");
	if (iLoc == -1) return;

	ref loc;
	makeref(loc, Locations[iLoc]);

	loc.models.always.l3 = "ArabellaDeck_part_Trap";

	loc.models.day.charactersPatch = "ArabellaDeck_patch_Trap";
	loc.models.night.charactersPatch = "ArabellaDeck_patch_Trap";
}

void CapBloodLine_TownAlieveDelete()
{
	ref sld;
	int i;

	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("CBL_Citizen_" + i) == -1) continue;

		sld = CharacterFromID("CBL_Citizen_" + i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}

	for (i = 1; i <= 8; i++)
	{
		if (GetCharacterIndex("CBL_EngSoldier_" + i) == -1) continue;

		sld = CharacterFromID("CBL_EngSoldier_" + i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld.lifeday = 0;
	}

	for (i = 1; i <= 3; i++)
	{
		if (GetCharacterIndex("CBL_EngMushketer_" + i) == -1) continue;

		sld = CharacterFromID("CBL_EngMushketer_" + i);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}
}

void CapBloodLine_OfficersToPcharLocation(string qName)
{
	ref sld;
	int i;
	string sChars[4];

	sChars[0] = "Volverston";
	sChars[1] = "Ogl";
	sChars[2] = "Dieke";
	sChars[3] = "Hugtorp";

	for (i = 0; i < 4; i++)
	{
		if (GetCharacterIndex(sChars[i]) == -1) continue;

		sld = CharacterFromID(sChars[i]);
		sld.dialog.currentnode = sChars[i] + "_OfficerStub";
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto" + (rand(10) + 1));
		LAi_SetCitizenType(sld);
		LAi_CharacterEnableDialog(sld);
	}

	sld = CharacterFromID("Bishop");
	sld.dialog.currentnode = "BishopOverboard_1";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto11");
	TeleportCharacterToPosAy(sld, -0.24, 3.79, 7.08, -1.0);
	AddLandQuestmark_Main(sld, "CapBloodLine");
}

void CapBloodLine_BishopGoToSwiming()
{
	LAi_FadeEx(1.0, 1.0, 1.0, "", "CapBloodLine_BishopGoToSwiming_1", "");
}

void CapBloodLine_BishopGoToSwiming_1(string qName)
{
	ref sld;
	int i;
	string sChars[4];

	sChars[0] = "Hugtorp";
	sChars[1] = "Dieke";
	sChars[2] = "Ogl";
	sChars[3] = "Volverston";

	sld = CharacterFromID("Bishop");
	LAi_SetActorType(sld);
	// LAi_ActorGoToLocator(sld, "goto", "goto4", "CapBloodLine_BishopGoToSwiming_2", -1);
	LAi_ActorMoveToPoint(sld, false, -6.18, 4.3, 7.1, "CapBloodLine_BishopGoToSwiming_2", -1.0);

	LAi_SetActorType(pchar);
	TeleportCharacterToPosAy(pchar, -1, 3.82, 4.44, -0.4);

	for (i = 0; i < 4; i++)
	{
		sld = CharacterFromID(sChars[i]);
		LAi_SetStayType(sld);

		switch (i)
		{
			case 0: TeleportCharacterToPosAy(sld, -2, 3.82, 4.15, -0.5); break;
			case 1: TeleportCharacterToPosAy(sld, 0.47, 3.8, 5.65, -1.1); break;
			case 2: TeleportCharacterToPosAy(sld, -3, 3.82, 4.15, -0.3); break;
			case 3: TeleportCharacterToPosAy(sld, -0.2, 3.82, 4.94, -1.0); break;
		}
	}

	locCameraFromToPos(0.59, 6.44, 2.67, true, -5.32, 1.53, 10.13);
}

void CapBloodLine_BishopGoToSwiming_3(string qName)
{
	ref sld = CharacterFromID("Bishop");
	sld.dialog.currentnode = "BishopOverboard_8";
	LAi_SetStayType(pchar);
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, pchar, "", -1);
}

void CapBloodLine_BishopGoToSwiming_4()
{
	ref sld = CharacterFromID("Bishop");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "quest", "quest1", "CapBloodLine_BishopGoToSwiming_5", -1);
	// TeleportCharacterToPosAy(pchar, -1, 3.82, 4.44, -0.4);
	locCameraFromToPos(-9.86, 6, 6.96, true, -5.01, -0.14, 0.45);
	DoQuestFunctionDelay("CapBloodLine_BishopGoToSwiming_6", 8.5);
	QuestPointerToLoc(pchar.location, "reload", "reload1");
	SetFunctionLocatorCondition("CapBloodLine_TalkWithDiego", "Arabella_Deck", "reload", "reload1", false);
}

void CapBloodLine_BishopGoToSwiming_6(string qName)
{
	ref sld;
	int i;
	string sChars[4];

	sChars[0] = "Volverston";
	sChars[1] = "Ogl";
	sChars[2] = "Dieke";
	sChars[3] = "Hugtorp";

	for (i = 0; i < 4; i++)
	{
		if (GetCharacterIndex(sChars[i]) == -1) continue;

		sld = CharacterFromID(sChars[i]);
		LAi_SetCitizenType(sld);
	}

	locCameraResetState();
	LAi_SetPlayerType(pchar);
	AddQuestRecord("EscapeFormBarbados", "14");
}

void CapBloodLine_TalkWithDiego(string qName)
{
	DoQuestReloadToLocation("My_Cabin_Quest", "reload", "reload1", "");
	SetFunctionLocationCondition("CapBloodLine_TalkWithDiego_1", "My_Cabin_Quest", false);
}

void CapBloodLine_TalkWithDiego_1(string qName)
{
	ref sld = CharacterFromID("Pitt");
	ChangeCharacterAddressGroup(sld, "My_Cabin_Quest", "goto", "goto1");
	TeleportCharacterToPosAy(sld, 1.83, 9.05, 5.41, 0.0);
	LAi_SetLayType(sld);

	sld = CharacterFromID("Diego_Espinosa");
	sld.dialog.currentnode = "Diego_FirstTalk";
	ChangeCharacterAddressGroup(sld, "My_Cabin_Quest", "goto", "goto1");
	LAi_SetGroundSitTypeNoGroup(sld);
	LAi_CharacterEnableDialog(sld);
	AddLandQuestmark_Main(sld, "CapBloodLine");

	chrDisableReloadToLOcation = true;
}

void CapBloodLine_RoadToEspaniola(string qName)
{
	QuestPointerDelLoc("My_Cabin_Quest", "reload", "reload1");
	QuestPointerDelLoc("Arabella_Deck", "reload", "reload1");

	LAi_SetPlayerType(pchar);

	DeleteAttribute(&questToSeaLoginer, "");
	Pchar.questTemp.CapBloodLine = false;

	SetLaunchFrameFormParam(StringFromKey("InfoMessages_219"), "", 0, 4);
	LaunchFrameForm();

	DoQuestFunctionDelay("CapBloodLine_RoadToEspaniola_1", 3.0);
}

void CapBloodLine_RoadToEspaniola_1(string qName)
{
	ref loc = &Locations[FindLocation("Shore33")];

	setCharacterShipLocation(pchar, "Shore33");
	pchar.location.from_sea = "Shore33";
	setWDMPointXZ("Shore33");

	AddDataToCurrent(0, 0, 3);
	SetCurrentTime(5, 0);
	RefreshLandTime();
	Whr_UpdateWeather();
	RestoreBridgetown();

	DoQuestReloadToLocation("Shore33", "reload", "sea", "");
	SetFunctionLocationCondition("CapBloodLine_RoadToEspaniola_3", "Shore33", false);

	for (int i = 1; i < MAX_CHARACTERS; i++) // если в порту Бриджтауна ранее был ПГГ - вернуть на место
	{
		if (!CheckAttribute(&Characters[i], "PGGAi.CapBloodLineFromSea")) continue;
		Characters[i].location.from_sea = Characters[i].PGGAi.CapBloodLineFromSea;
		DeleteAttribute(&Characters[i], "PGGAi.CapBloodLineFromSea");
	}

	int iFoodPerDay = makeint((GetCrewQuantity(pchar) + 5.1) / 10.0 + GetPassengersQuantity(pchar) / 10.0);
	iFoodPerDay += makeint((GetCargoGoods(pchar, GOOD_SLAVES) + 6) / 20.0);
	if (iFoodPerDay == 0) iFoodPerDay = 1;
	SetCharacterGoods(pchar, GOOD_FOOD, iFoodPerDay * 3);


	if (CheckAttribute(loc, "shorechest"))
	{
		if (CheckAttribute(loc, "numbox")) DeleteAttribute(loc, loc.numbox);
		DeleteAttributeEx(loc, "shorechest,shorefill,chest_date,models.always.chest,numbox,num");
	}

	loc.models.always.BloodChest = "chest_1"; // подарок самым пытливым
	loc.models.always.BloodChest.locator.group = "box";
	loc.models.always.BloodChest.locator.name = "box1";
	loc.models.always.BloodChest.tech = "DLightModel";

	pchar.GenQuestBox.Shore33 = true;
	pchar.GenQuestBox.Shore33.box1.items.spyglass1 = 1;
	pchar.GenQuestBox.Shore33.box1.items.map_full = 1;
	pchar.GenQuestBox.Shore33.box1.items.indian17 = 1;
	pchar.GenQuestBox.Shore33.box1.items.HelenNote = 1;

	pchar.quest.Ach_BrokenHeart.win_condition.l1 = "item";
	pchar.quest.Ach_BrokenHeart.win_condition.l1.item = "HelenNote";
	pchar.quest.Ach_BrokenHeart.function = "Ach_BrokenHeart";
}

void CapBloodLine_RoadToEspaniola_3(string qName)
{
	ref sld;
	int i;
	string sChar[2];

	sChar[0] = "Dieke";
	sChar[1] = "Volverston";

	for (i = 0; i < 2; i++)
	{
		if (GetCharacterIndex(sChar[i]) == -1) continue;
		sld = CharacterFromID(sChar[i]);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto" + (i + 1));
		LAi_SetCitizenType(sld);
	}
	TeleportCharacterToLocator(pchar, "goto", "goto5");
	LAi_SetStayType(pchar);
	CharacterTurnToLoc(pchar, "goto", "goto4");

	sld = CharacterFromID("Diego_Espinosa");
	sld.dialog.currentnode = "DiegoOnShore";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

	sld = CharacterFromID("Hugtorp");
	LAi_SetActorTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto4");
	LAi_ActorFollow(sld, pchar, "CapBloodLine_ED_TurnHugtorp", -1);

	chrDisableReloadToLocation = true;
	InterfaceStates.Buttons.Save.enable = true;

	Island_SetGotoEnableLocal("Barbados", "reload_1", true);
	Island_SetGotoEnableLocal("Barbados", "reload_fort1", true);
	Island_SetGotoEnableLocal("Barbados", "reload_2", true);
	Island_SetGotoEnableLocal("Barbados", "reload_3", true);
	Island_SetGotoEnableLocal("Barbados", "reload_4", true);
}

void Ach_BrokenHeart(string qName)
{
	AddCharacterExpToSkill(pchar, "Fortune", 500);
	Achievment_Set(ACH_Razbitoe_serdtse);
}

void CapBloodLine_ReadySiguayo()
{
	ref sld = CharacterFromID("Diego_Espinosa");
	LAi_CharacterDisableDialog(sld);

	LAi_FadeEx(1.0, 1.0, 1.0, "", "CapBloodLine_Siguayo", "");
}

void CapBloodLine_Siguayo(string qName)
{
	ref sld;
	int i;
	string sModel[6];

	sModel[0] = "Canib_6";
	sModel[1] = "Canib_3";
	sModel[2] = "Canib_2";
	sModel[3] = "Canib_1";
	sModel[4] = "Canib_5";
	sModel[5] = "Canib_4";

	for (i = 0; i < 6; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("CBL_Siguayo_" + i, sModel[i], "man", "man", 1, PIRATE, 0, true));
		sld.name = GetIndianName(MAN);
		sld.lastname = "";
		sld.indian = true;

		if (i < 3)
		{
			GiveItem2Character(sld, "spear1");
			EquipCharacterByItem(sld, "spear1");
		}
		else
		{
			GiveItem2Character(sld, "blade37");
			EquipCharacterByItem(sld, "blade37");
		}

		TakeNItems(sld, "potion1", -GetCharacterItem(sld, "potion1"));
		TakeNItems(sld, "potion2", -GetCharacterItem(sld, "potion2"));
		TakeNItems(sld, "potion3", -GetCharacterItem(sld, "potion3"));
		TakeNItems(sld, "potion4", -GetCharacterItem(sld, "potion4"));

		LAi_SetActorType(sld);
		sld.chr_ai.type.bottle = 100000.0;
		ChangeCharacterAddressGroup(sld, "Shore33", "reload", "reload1_back");
		LAi_ActorRunToLocator(sld, "goto", "goto2", "", -1.0);
		LAi_SetFightMode(sld, true);
	}
	locCameraFlyUpRotateLookYDelay(2.59, 2.89, -3.95, 180.0, 1.5, -60.0, 5.0, 4.5, 5.0, 0.5);
	Pchar.FuncCameraFly = "CapBloodLine_Siguayo_1";
	// DoQuestFunctionDelay("CapBloodLine_Siguayo_1", 4.0);
}

void CapBloodLine_Siguayo_1()
{
	locCameraSleep(true);
    LAi_FadeEx(1.0, 1.0, 1.0, "CapBloodLine_Siguayo_2", "", "");
}

void CapBloodLine_Siguayo_2(string qName)
{
	ref sld;
	int i;

	string sOfficers[3];

	sOfficers[0] = "Dieke";
	sOfficers[1] = "Volverston";
	sOfficers[2] = "Hugtorp";

	for (i = 0; i < 6; i++)
	{
		sld = CharacterFromID("CBL_Siguayo_" + i);
		TeleportCharacterToPosAy(sld, 10.07 + rand(3), 0.82, 6.67 + rand(3), 0.0);
		CharacterTurnByLoc(sld, "goto", "goto4");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "Blood_Siguayo_Group");
	}

	for (i = 0; i < 3; i++)
	{
		sld = CharacterFromID(sOfficers[i]);
		LAi_SetOfficerType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	LAi_LocationFightDisable(&Locations[FindLocation("Shore33")], false);

	sld = CharacterFromID("Diego_Espinosa");
	LAi_SetActorType(sld);
	// LAi_group_MoveCharacter(sld, LAI_GROUP_NEUTRAL);

	LAi_group_SetRelation("Blood_Siguayo_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("Blood_Siguayo_Group", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("Blood_Siguayo_Group", "CapBloodLine_Siguayo_3");

	locCameraSleep(false);
	locCameraTarget(pchar);
	locCameraFollow();
	Lai_SetPlayerType(pchar);
	TeleportCharacterToPosAy(pchar, 3.11, 1.15, 3.93, 1.4);
	LAi_SetFightMode(Pchar, true);

	sld = CharacterFromID("Diego_Espinosa");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorMoveToPoint(sld, true, -23.44, 1.35, 6.67, "CapBloodLine_DiegoOnShoreTurn", -1.0);
}

void CapBloodLine_Siguayo_4(string qName)
{
	ref sld;
	string sOfficers[3];

	sOfficers[0] = "Volverston";
	sOfficers[1] = "Dieke";
	sOfficers[2] = "Hugtorp";

	for (int i = 0; i < 3; i++)
	{
		sld = CharacterFromID(sOfficers[i]);

		if (sOfficers[i] == "Dieke")
		{
			sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
			sld.dialog.currentnode = "DiekeOnShore";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			sld.dialog.currentnode = sOfficers[i] + "_OfficerNode";
			LAi_SetCitizenTypeNoGroup(sld);
		}
	}
}

void CapBloodLine_DiegoLie()
{
	ref sld = CharacterFromID("Dieke");
	LAi_ActorFollow(sld, pchar, "", -1);

	sld = CharacterFromId("Diego_Espinosa");
	sld.dialog.currentnode = "DiegoOnShore_5";
	LAi_SetStayTypeNoGroup(sld);
	LAi_CharacterEnableDialog(sld);
	AddLandQuestMark_Main(sld, "CapBloodLine");

    AddQuestRecord("EscapeFormBarbados", "15");
}

void CapBloodLine_DiegoFistFightStart()  // Драка на кулаках
{
	ref chr;
	ref sld;

	string sOfficers[3];
	sOfficers[0] = "Volverston";
	sOfficers[1] = "Dieke";
	sOfficers[2] = "Hugtorp";

	sld = CharacterFromID("Diego_Espinosa");
	for (int j = 1; j <= 4; j++)
	{
		TakeNItems(sld, "potion" + j, -GetCharacterItem(sld, "potion" + j));
	}
	LAi_SetImmortal(sld, false);
	LAi_SetHP(sld, 100.0, 100.0);
	LAi_group_Delete("DiegoFistFightSpectators");
	LAi_group_SetRelation("DiegoFistFightSpectators", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation("DiegoFistFightSpectators", "DiegoFistFight", LAI_GROUP_NEITRAL);

	for (int i = 0; i < 3; i++)
	{
		if (GetCharacterIndex(sOfficers[i]) == -1) continue;

		chr = CharacterFromID(sOfficers[i]);
		if (chr.location != pchar.location) continue;

		LAi_SetActorType(chr);
		LAi_group_MoveCharacter(chr, "DiegoFistFightSpectators");
	}

	chrDisableReloadToLocation = true;
	InterfaceStates.Buttons.Save.enable = false;
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);

	pchar.CBL.DiegoFightTurnFrame = 0;
	SetEventHandler("frame", "CapBloodLine_DiegoFistFightTurnOfficers", true);
	Take_Fists();

	if (CheckAttribute(pchar, "MultiFighter")) TEV.tPunch.OldMultiFighter = pchar.MultiFighter;
	pchar.MultiFighter = 15.0;
	if (CheckAttribute(sld, "equip.blade") && sld.equip.blade != "") sld.FistFight.blade = sld.equip.blade;
	if (CheckAttribute(sld, "equip.gun") && sld.equip.gun != "") sld.FistFight.gun = sld.equip.gun;
	if (CheckAttribute(sld, "equip.cirass") && sld.equip.cirass != "") sld.FistFight.cirass = sld.equip.cirass;

	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	RemoveCharacterEquip(sld, MUSKET_ITEM_TYPE);
	RemoveCharacterEquip(sld, CIRASS_ITEM_TYPE);

	GiveItem2Character(sld, "unarmed");
	EquipCharacterByItem(sld, "unarmed");

	LAi_SetCheckMinHP(sld, 1.0, true, "CapBloodLine_DiegoFistFightWin");
	LAi_SetCheckMinHP(pchar, 1.0, true, "CapBloodLine_DiegoFistFightLose");

	LAi_SetWarriorType(sld);
	LAi_group_Delete("DiegoFistFight");
	LAi_group_MoveCharacter(sld, "DiegoFistFight");
	LAi_group_SetRelation("DiegoFistFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("DiegoFistFight", LAI_GROUP_PLAYER, true);

	LAi_SetFightMode(pchar, true);
}

void CapBloodLine_DiegoFistFightEnd(bool pcharWin)
{
	ref chr;
	ref sld;

	string sOfficers[3];
	sOfficers[0] = "Volverston";
	sOfficers[1] = "Dieke";
	sOfficers[2] = "Hugtorp";

	for (int i = 0; i < 3; i++)
	{
		if (GetCharacterIndex(sOfficers[i]) == -1) continue;

		chr = CharacterFromID(sOfficers[i]);
		LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
		LAi_SetActorTypeNoGroup(chr);
		LAi_ActorFollow(chr, pchar, "", -1);
	}

	sld = CharacterFromID("Diego_Espinosa");
	LAi_RemoveCheckMinHP(sld);
	LAi_RemoveCheckMinHP(pchar);
	LAi_SetImmortal(sld, true);
	LAi_SetImmortal(pchar, false);

	LAi_group_SetRelation("DiegoFistFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_Delete("DiegoFistFight");
	LAi_grp_alarmactive = false;

	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, false);

	if (CheckAttribute(&TEV, "tPunch.OldMultiFighter")) pchar.MultiFighter = TEV.tPunch.OldMultiFighter;
	else DeleteAttribute(pchar, "MultiFighter");
	InterfaceStates.Buttons.Save.enable = true;

	Take_Fists_Away();
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	TakeNItems(sld, "unarmed", -1);

	if (CheckAttribute(sld, "FistFight.blade")) EquipCharacterByItem(sld, sld.FistFight.blade);
	if (CheckAttribute(sld, "FistFight.gun")) EquipCharacterByItem(sld, sld.FistFight.gun);
	if (CheckAttribute(sld, "FistFight.cirass")) EquipCharacterByItem(sld, sld.FistFight.cirass);

	DeleteAttribute(sld, "FistFight");
	DelEventHandler("frame", "CapBloodLine_DiegoFistFightTurnOfficers");
	DeleteAttribute(pchar, "CBL.DiegoFightTurnFrame");

	LAi_SetPlayerType(pchar);
	LAi_SetActorType(sld);

	LAi_group_Delete("DiegoFistFightSpectators");

	if (pcharWin) sld.dialog.currentnode = "DiegoOnShore_8_Win";
	else sld.dialog.currentnode = "DiegoOnShore_8_Lose";
	DoQuestFunctionDelay("CapBloodLine_DiegoFistFightDialog", 0.5);
}

void CapBloodLine_DiegoFistFightDialog(string qName)
{
	ref sld;
	sld = CharacterFromID("Diego_Espinosa");
	LAi_SetPlayerType(pchar);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CapBloodLine_DiegoFistFightTurnOfficers()
{
	ref chr;
	string sOfficers[3];

	pchar.CBL.DiegoFightTurnFrame = sti(pchar.CBL.DiegoFightTurnFrame) + 1;
	if (sti(pchar.CBL.DiegoFightTurnFrame) < 5) return;

	pchar.CBL.DiegoFightTurnFrame = 0;

	sOfficers[0] = "Volverston";
	sOfficers[1] = "Dieke";
	sOfficers[2] = "Hugtorp";

	for (int i = 0; i < 3; i++)
	{
		if (GetCharacterIndex(sOfficers[i]) == -1) continue;

		chr = CharacterFromID(sOfficers[i]);
		if (chr.location != pchar.location) continue;

		CharacterTurnByChr(chr, pchar);
	}
}

void CapBloodLine_OfficersAndDiegoToBoat()
{
	ref sld;
	string sChars[4];

	sChars[0] = "Volverston";
	sChars[1] = "Dieke";
	sChars[2] = "Hugtorp";
	sChars[3] = "Diego_Espinosa";

	for (int i = 0; i < 4; i++)
	{
		if (GetCharacterIndex(sChars[i]) == -1) continue;

		sld = CharacterFromID(sChars[i]);
		LAi_SetActorType(sld);
		LAi_type_actor_Reset(sld);
		LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", -1);
	}
	AddQuestRecord("CBL_SonsRespect", "1");
	CloseQuestHeader("EscapeFormBarbados");
	ChrDisableReloadToLocation = false;
	SetFunctionExitFromLocationCondition("CapBloodLine_OfficersAndDiegoToNone", pchar.location, false);

	PChar.quest.CapBloodLine_ToArabellaDeck.win_condition.l1 = "EnterToSea";
	PChar.quest.CapBloodLine_ToArabellaDeck.function = "CapBloodLine_ToArabellaDeck_0";
}
void CapBloodLine_ToArabellaDeck_0(string qName)
{
	ref loc = &Locations[FindLocation("Shore33")];
	DeleteAttribute(loc, "models.always.BloodChest");
	DeleteAttribute(loc, "box1");
	DeleteAttribute(loc, "box1.items");
	DeleteAttribute(pchar, "GenQuestBox.Shore33");

	DoQuestFunctionDelay("CapBloodLine_ToArabellaDeck", 2.0);
}

void CapBloodLine_OfficersAndDiegoToNone(string qName)
{
	ref sld;
	string sChars[4];

	sChars[0] = "Volverston";
	sChars[1] = "Dieke";
	sChars[2] = "Hugtorp";
	sChars[3] = "Diego_Espinosa";

	for (int i = 0; i < 4; i++)
	{
		if (GetCharacterIndex(sChars[i]) == -1) continue;

		sld = CharacterFromID(sChars[i]);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}

	Island_SetReloadEnableGlobal("Hispaniola1", false);
}

void CapBloodLine_ToArabellaDeck(string qName)
{
	int iLoc = FindLocation("Arabella_Deck");
	if (iLoc == -1) return;

	ref loc;
	makeref(loc, Locations[iLoc]);

	DeleteAttribute(loc, "models.always.l3");

	loc.models.always.l2 = "ArabellaDeck_part_Espinosa";
	loc.models.day.charactersPatch = "ArabellaDeck_patch_Espinosa";
	loc.models.night.charactersPatch = "ArabellaDeck_patch_Espinosa";

	DoQuestReloadToLocation("Arabella_Deck", "reload", "reload1", "");
	SetFunctionLocationCondition("CapBloodLine_SonsTrable", "Arabella_Deck", false);
}

void CapBloodLine_SonsTrable(string qName)
{
	LAi_FadeEx(0.0, 0.5, 2.0, "", "CapBloodLine_SonsTrable_1", "");
	LAi_SetStayType(pchar);
}

void CapBloodLine_SonsTrable_1(string qName)
{
	locCameraFlyToPositionRotate(4.78, 4.82, 0.68, 1.84, 5.52, 3.89, 20.0, -60.0, 10.0, 10.0, 1.0, 7.0, 7.0);
	Pchar.FuncCameraFly = "CapBloodLine_CameraSleep";
	// TeleportCharacterToPosAy(pchar, 2.4, 3.81, 4.75, 0.0);
	TeleportCharacterToPosAy(pchar, 1.46, 3.84, 3.18, 2.4);

	CapBloodLine_SonsTrable_2();
}

void CapBloodLine_SonsTrable_2()
{
	ref sld;
	ref esteban;
	int i;

	string sChars[2];

	sChars[0] = "Volverston";
	sChars[1] = "Dieke";

	for (i = 0; i < 2; i++)
	{
		if (GetCharacterIndex(sChars[i]) == -1) continue;
		sld = CharacterFromID(sChars[i]);
		LAi_CharacterEnableDialog(sld);
		if (sld.location != pchar.location) ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto12");
	}

	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

		sld = CharacterFromID("DiegoGuard_" + i);
		if (LAi_IsDead(sld)) continue;
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");

		switch (i)
		{
			case 1: TeleportCharacterToPosAy(sld, 2.0, 3.8, 8.5, 2.9); break;
			case 2: TeleportCharacterToPosAy(sld, 3.3, 3.7, 7.9, 2.9); break;
			case 3: TeleportCharacterToPosAy(sld, 2.7, 3.7, 8.4, 2.9); break;
			case 4: TeleportCharacterToPosAy(sld, 1.0, 3.8, 7.9, 2.9); break;
		}
	}

	esteban = CharacterFromID("Esteban_Espinosa");
	LAi_SetStayType(esteban);
	ChangeCharacterAddressGroup(esteban, pchar.location, "goto", "goto2");
	TeleportCharacterToPosAy(esteban, 2.2, 3.8, 7.0, 2.9);
	CharacterTurnByChr(esteban, pchar);

	sld = CharacterFromID("Hugtorp");
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto11");
	TeleportCharacterToPosAy(sld, -0.16, 3.81, 5.59, 1.0);

	DoQuestFunctionDelay("CapBloodLine_SonsTrable_3", 6.0);
}

void CapBloodLine_SonsTrable_3(string qName)
{
	LAi_SetActorType(pchar);
	LAi_ActorMoveToPoint(pchar, false, 2.74, 3.8, 5.25, "CapBloodLine_SonsTrable_4", -1.0);
}

void CapBloodLine_SonsTrable_5()
{
	ref sld;
	int i;

	string sOfficers[4];
	sOfficers[0] = "Volverston";
	sOfficers[1] = "Hugtorp";
	sOfficers[2] = "Ogl";
	sOfficers[3] = "Dieke";

	for (i = 0; i < 4; i++)
	{
		sld = CharacterFromID(sOfficers[i]);
		LAi_CharacterEnableDialog(sld);

		if (sOfficers[i] == "Dieke")
		{
			sld.Dialog.CurrentNode = "Dieke_GiveGold";
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "CapBloodLine_SonsTrable_11", -1.0);
		}
		else
		{
			sld.Dialog.CurrentNode = sOfficers[i] + "_OfficerNode";
			LAi_SetCitizenTypeNoGroup(sld);
		}
	}

	sld = CharacterFromID("Esteban_Espinosa");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);

	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

		sld = CharacterFromID("DiegoGuard_" + i);
		if (LAi_IsDead(sld)) continue;

		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
	}

	locCameraSleep(false);
	locCameraResetState();
	LAi_SetStayType(pchar);
	CharacterTurnAy(pchar, 2.9);
	Flag_SPAIN();

	// 	AddQuestRecord("EscapeFormBarbados", "16");
	DoQuestFunctionDelay("CapBloodLine_SonsTrable_9", 1.0);
}

void CapBloodLine_SonsTrable_6(string qName)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Miguel_Espinosa", "navy_off_spa_6", "man", "man", 30, SPAIN, -1, false));

	sld.name = FindPersonalName("Miguel_name");
	sld.lastname = FindPersonalName("De_Espinosa_lastname");

	FantomMakeCoolSailor(sld, SHIP_GALEON_H, FindPersonalName("Encarnacion_ship"), CANNON_TYPE_CANNON_LBS32, 80, 80, 80);
	sld.Dialog.FileName = "Quest\CapBloodLine\Bishop.c";
	sld.Dialog.CurrentNode = "MiguelEncarnacion";
	sld.DeckDialogNode = "MiguelEncarnacion";
	sld.Ship.Mode = "war";

	sld.AlwaysFriend = true;
	sld.Abordage.Enable = false;
	sld.ShipEnemyDisable = true;
	sld.ShipTaskLock = true;

	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);

	Group_FindOrCreateGroup("Miguel_Espinosa_Group");
	Group_SetType("Miguel_Espinosa_Group", "war");
	Group_AddCharacter("Miguel_Espinosa_Group", sld.id);
	Group_SetGroupCommander("Miguel_Espinosa_Group", sld.id);
	Group_SetAddress("Miguel_Espinosa_Group", "Hispaniola1", "quest_ships", "quest_ship_4");
	Group_SetTaskNone("Miguel_Espinosa_Group");
	Group_LockTask("Miguel_Espinosa_Group");

	pchar.quest.CapBloodLine_EncarnacionTaskStart.win_condition.l1 = "EnterToSea";
	pchar.quest.CapBloodLine_EncarnacionTaskStart.function = "CapBloodLine_EncarnacionTaskStart";

	DeleteAttribute(&questToSeaLoginer, "");
	QuestToSeaLogin_PrepareLoc("Hispaniola1", "reload", "reload_5", false);
	QuestToSeaLogin_Launch();
	pchar.questTemp.CapBloodLine.AllowBoat = true;

	SetFunctionLocationCondition("CapBloodLine_SonsTrable_7", "Deck_Near_Ship", false);
}

void CapBloodLine_SonsTrable_7(string qName)
{
	ref sld;
	float x, y, z;

	sld = CharacterFromID("Miguel_Espinosa");
	LAi_SetStayType(sld);
	TeleportCharacterToPosAy(sld, 2.68, 4, 5.38, -1.5);
	AddLandQuestMark_Main(sld, "CapBloodLine");
	TeleportCharacterToPosAy(pchar, -2.76, 3.99, 5.51, 1.5);

	sld = CharacterFromID("Esteban_Espinosa");
	sld.Dialog.FileName = "Quest\CapBloodLine\Bishop.c";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto11");
	GetCharacterPos(pchar, &x, &y, &z);
	TeleportCharacterToPosAy(sld, x + 1.2, y, z, 1.5);
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);

	sld = GetCharacter(NPC_GenerateCharacter("Encarnacion_Priest", "priest_sp1", "man", "man_B", 20, SPAIN, -1, false));
	sld.Dialog.FileName = "Quest\CapBloodLine\Bishop.c";
	ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto8");
	TeleportCharacterToPosAy(sld, 2.7, 3.98, 6.51, -1.5);
	LAi_SetActorType(sld);

	if (!CheckAttribute(&objTask, "BloodLine_Encarnacion")) return;
	TW_IncreaseCounter("BloodLine_Encarnacion", "Encarnacion_text", 1);
	DoQuestFunctionDelay("TW_Finish_BloodLine_Encarnacion", 2.0);
}

void CapBloodLine_SonsTrable_8()
{
	ref sld, location;
	string boxId = "box1";

	sld = CharacterFromId("Dieke");
	sld.dialog.currentnode = "Dieke_OfficerNode";
	LAi_SetCitizenTypeNoGroup(sld);

	location = &Locations[FindLocation("My_Cabin_Quest")];
	location.(boxId).items.chest = 4;
	location.(boxId) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());

	QuestPointerToLoc("Arabella_Deck", "reload", "reload2");
	SetFunctionLocatorCondition("CapBloodLine_SonsTrable_6", "Arabella_Deck", "reload", "reload2", "");
}

void CapBloodLine_SonsTrable_9(string qName)
{
	StartActorNamedSelfDialog("CBL_TalkWithDiedDiego", "Diego_Espinosa", 3.42, 4.71, 1.88, 2.9);
}

string CapBloodLine_GetAliveDiegoGuard()
{
	ref chr;
	string sGuard;
	int i;

	for (i = 1; i <= 5; i++)
	{
		sGuard = "DiegoGuard_" + i;
		if (GetCharacterIndex(sGuard) == -1) continue;

		chr = CharacterFromID(sGuard);
		if (!LAi_IsDead(chr)) return sGuard;
	}

	return "";
}

void CapBloodLine_SonsTrable_10()
{
    ref sld = CharacterFromID("Dieke");
	sld.dialog.currentnode = "Dieke_GiveGold";
	LAi_CharacterEnableDialog(sld);
	if (!CheckAttribute(sld, "DiekeReadyTalk")) LAi_ActorDialogDelay(sld, pchar, "", 0.2);
}

void CapBloodLine_EncarnacionTaskStart(string qName)
{
	TW_Init_BloodLine_Encarnacion();
	TW_Open("BloodLine_Encarnacion");
	QuestPointerDelLoc("Arabella_Deck", "reload", "reload2");
}

void CapBloodLine_EncarnacionFarewell()
{
	ref sld;
	string sChars[2];

	sChars[0] = "Miguel_Espinosa";
	sChars[1] = "Encarnacion_Priest";

	for (int i = 0; i < 2; i++)
	{
		sld = CharacterFromID(sChars[i]);
		LAi_SetCitizenTypeNoGroup(sld);
		LAi_CharacterDisableDialog(sld);
	}

	sld = CharacterFromID("Esteban_Espinosa");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);

	DeleteAttribute(pchar, "questTemp.CapBloodLine.AllowBoat");
	DoQuestFunctionDelay("CapBloodLine_WaitEncarnacionExit", 0.5);
	// SetFunctionLocationCondition("CapBloodLine_LeaveEncarnacion", "Hispaniola1", false);
	// SetFunctionExitFromLocationCondition("CapBloodLine_LeaveEncarnacion", pchar.location, false);
	SetFunctionLocationCondition("CapBloodLine_SonsTrable_Dialog", "Arabella_Deck", false);
}

void CapBloodLine_WaitEncarnacionExit(string qName)
{
	if (bDeckBoatStarted)
	{
		DoQuestFunctionDelay("CapBloodLine_WaitEncarnacionExit", 0.5);
		return;
	}
	if (pchar.location == "Arabella_Deck") return;

	DoQuestFunctionDelay("CapBloodLine_ReturnToArabellaDeck", 2.0);
}

void CapBloodLine_ReturnToArabellaDeck(string qName)
{
	if (pchar.location == "Arabella_Deck") return;
	DoQuestReloadToLocation("Arabella_Deck", "reload", "reload2", "");
}

void CapBloodLine_SonsTrable_Dialog(string qName)
{
	ref sld;
	int i;

	LAi_SetStayType(pchar);
	TeleportCharacterToPosAy(pchar, -1.17, 3.78, 6.83, 2.0);

	sld = CharacterFromID("Esteban_Espinosa");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto11");
	TeleportCharacterToPosAy(sld, -1.81, 3.78, 6.54, 2.0);

	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

		sld = CharacterFromID("DiegoGuard_" + i);
		if (LAi_IsDead(sld)) continue;

		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto11");
		LAi_SetStayType(sld);
		TeleportCharacterToPosAy(sld, -2.26 + frand(1.5) - 0.5, 3.77, 7.35 + frand(1.5) - 0.5, 2.0);
	}

	sld = CharacterFromID("Hugtorp");
	sld.dialog.currentnode = "Hugtorp_AboutDigo";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto11");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void CapBloodLine_HugtorpSayDiegoDie()
{
    ref sld = CharacterFromID("Esteban_Espinosa");
	sld.dialog.currentnode = "EstebanAfterEncarnacion_1";
	LAi_SetActorType(sld);
	TeleportCharacterToPosAy(sld, -1.6, 3.79, 5.9, 1.70);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	// LAi_ActorMoveToPoint(sld, false, -1.6, 3.79, 5.3, "CapBloodLine_HugtorpSayDiegoDie_1", -1.0);
}

void CapBloodLine_HugtorpSayDiegoDie_2()
{
	ref sld;
	ref esteban = CharacterFromID("Esteban_Espinosa");
	int i;

	LAi_SetActorType(esteban);
	LAi_ActorMoveToPoint(esteban, false, 2.21, 3.71, 13.59, "", -1.0);

	sld = CharacterFromID("Hugtorp");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, esteban, "", -1.0);

	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

		sld = CharacterFromID("DiegoGuard_" + i);
		if (LAi_IsDead(sld) || sld.location != pchar.location) continue;

		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, esteban, "", -1.0);
	}
	LAi_SetPlayerType(pchar);
	LAi_FadeEx(2.0, 1.0, 2.0, "", "CapBloodLine_NeedSolution", "");
}

void CapBloodLine_NeedSolution(string qName)
{
	ref sld;
	int i;
	string sOfficers[4];

	sld = CharacterFromID("Esteban_Espinosa");
	RemovePassenger(pchar, sld);
	DeleteAttribute(sld, "prisoned");
	ChangeCharacterAddressGroup(sld, "none", "", "");

	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;
		sld = CharacterFromID("DiegoGuard_" + i);
		if (LAi_IsDead(sld)) continue;
		RemovePassenger(pchar, sld);
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld.LifeDay = 0;
	}

	sld = CharacterFromID("Diego_Espinosa");
	RemovePassenger(pchar, sld);
	if (!LAi_IsDead(sld)) LAi_KillCharacter(sld);

	sOfficers[0] = "Dieke";
	sOfficers[1] = "Hugtorp";
	sOfficers[2] = "Ogl";
	sOfficers[3] = "Volverston";

	for (i = 0; i < 4; i++)
	{
		sld = CharacterFromID(sOfficers[i]);

		switch (i)
		{
			case 0: TeleportCharacterToPosAy(sld, -0.7, 5.82, -1.9, 3.2); break;
			case 1: TeleportCharacterToPosAy(sld, -4.02, 5.31, -0.8, 0.0); break;
			case 2: TeleportCharacterToPosAy(sld, 0.7, 5.82, -1.9, 3.2); break;
			case 3: TeleportCharacterToPosAy(sld, 1.8, 5.82, -1.9, 3.2); break;
		}

		if (i == 1)
		{
			LAi_SetActorType(sld);
			LAi_ActorMoveToPoint(sld, false, -1.8, 5.82, -1.9, "CapBloodLine_NeedSolution_1", -1.0);
		}
		else
		{
			LAi_SetStayType(sld);
		}
	}
	TeleportCharacterToPosAy(pchar, -0.13, 5.91, -5.16, 0.0);
	LAi_SetStayType(pchar);
}

void CapBloodLine_FinalOfTheSecondStage()
{
	ref sld;
	int i;

	sld = CharacterFromID("Esteban_Espinosa");
	RemovePassenger(pchar, sld);
	ChangeCharacterAddressGroup(sld, "none", "", "");

	for (i = 1; i <= 4; i++)
	{
		if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

		sld = CharacterFromID("DiegoGuard_" + i);
		if (LAi_IsDead(sld)) continue;

		RemovePassenger(pchar, sld);
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}

	int iFoodPerDay = makeint((GetCrewQuantity(pchar) + 5.1) / 10.0 + GetPassengersQuantity(pchar) / 10.0);
	iFoodPerDay += makeint((GetCargoGoods(pchar, GOOD_SLAVES) + 6) / 20.0);
	if (iFoodPerDay == 0) iFoodPerDay = 1;
	SetCharacterGoods(pchar, GOOD_FOOD, iFoodPerDay * 2);

	CapBloodLine_SetStandardOfficerNodes();
	AddQuestRecord("CBL_SonsRespect", "2");
	CloseQuestHeader("CBL_SonsRespect");
	AddQuestRecord("CBL_Tortuga", "1");

	Group_SetAddress("Miguel_Espinosa_Group", "None", "", "");
	ChangeCharacterAddressGroup(CharacterFromID("Miguel_Espinosa"), "none", "", "");
	Flag_ENGLAND();

	DeleteAttribute(pchar, "NoNavyPenalty"); // возвращаем штрафы
	DelBakSkillAttr(pchar);

	LAi_FadeEx(3.0, 1.0, 1.0, "", "BloodLine_GlobalTutor_EndCabinDialog", "");
}

void CapBloodLine_SetStandardOfficerNodes()
{
	ref sld;
	string sOfficers[4];

	sOfficers[0] = "Volverston";
	sOfficers[1] = "Hugtorp";
	sOfficers[2] = "Dieke";
	sOfficers[3] = "Ogl";

	for (int i = 0; i < 4; i++)
	{
		sld = CharacterFromID(sOfficers[i]);

		sld.Dialog.FileName = "Officer_Man.c";
		sld.Dialog.CurrentNode = "hired";
		LAi_CharacterEnableDialog(sld);
	}
}

void CapBloodLine_RunRumourAboutEscape(string qName)
{
	CapBloodLine_AddEscapeRumour("CapBloodLine_Rumour_1", true);
	CapBloodLine_AddEscapeRumour("CapBloodLine_Rumour_2", true);
	CapBloodLine_AddEscapeRumour("CapBloodLine_Rumour_3", false);
	CapBloodLine_AddEscapeRumour("CapBloodLine_Rumour_4", true);
	CapBloodLine_AddEscapeRumour("CapBloodLine_Rumour_5", false);
	CapBloodLine_AddEscapeRumour("CapBloodLine_Rumour_6", true);

	CapBloodLine_AddStartRumour("CapBloodLine_SpanishBloodRumour_1", "", SPAIN, "CapBloodLine_SpanishBlood", true);
	CapBloodLine_AddStartRumour("CapBloodLine_SpanishBloodRumour_2", "", SPAIN, "CapBloodLine_SpanishBlood", true);
	CapBloodLine_AddStartRumour("CapBloodLine_SpanishBloodRumour_3", "", SPAIN, "CapBloodLine_SpanishBlood", true);
	CapBloodLine_AddStartRumour("CapBloodLine_SpanishBloodRumour_4", "", SPAIN, "CapBloodLine_SpanishBlood", false);
}

void CapBloodLine_AddStartRumour(string sKey, string sCity, int iNation, string sGroup, bool bManOnly)
{
	int iRumour;

	if (sCity != "") iRumour = FindRumour(AddSimpleRumourCity(StringFromKey(sKey), sCity, 30, 3, ""));
	else iRumour = FindRumour(AddSimpleRumour(StringFromKey(sKey), iNation, 30, 3));

	if (iRumour == -1) return;

	Rumour[iRumour].group = sGroup;
	if (bManOnly) Rumour[iRumour].sex = "man";
}

void CapBloodLine_AddEscapeRumour(string sKey, bool bManOnly)
{
	int iRumour = FindRumour(AddSimpleRumourCity(StringFromKey(sKey), "!Bridgetown", 30, 3, ""));

	if (iRumour == -1) return;

	Rumour[iRumour].group = "CapBloodLine_Escape";
	Rumour[iRumour].nonation.n1 = SPAIN;
	if (bManOnly) Rumour[iRumour].sex = "man";
}

void CapBloodLine_CameraSleep() // Служебная, чтобы не плодить каждый раз
{
	locCameraSleep(true);
}

void CapBloodLine_RemovePlantationCarriers()
{
	ref sld;

	for (int i = GlobalCharacters; i < MAX_CHARACTERS; i++)
	{
		sld = &Characters[i];

		if (!CheckAttribute(sld, "plantation") || sld.plantation != "carrier") continue;
		if (!CheckAttribute(sld, "location") || sld.location != "Bridgetown_Plantation") continue;

		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld.lifeDay = 0;
	}
}

void CapBloodLine_EncarnacionFailure() // для особо хитрых - присвоить сундуки не выйдет
{
	ref sld = CharacterFromID("Miguel_Espinosa");

	LAi_SetActorType(sld);
	CharacterTurnByChr(sld, pchar);
	CharacterTurnByChr(pchar, sld);

	GiveItem2Character(sld, "pistol1");
	EquipCharacterByItem(sld, "pistol1");

	DoQuestFunctionDelay("CapBloodLine_EncarnacionFailureDraw", 0.2);
}

void CapBloodLine_EncarnacionFailureDraw(string qName)
{
	LAi_SetPlayerType(pchar);
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
	LAi_SetFightMode(pchar, true);

	DoQuestFunctionDelay("CapBloodLine_EncarnacionFailureShot", 0.5);
}

void CapBloodLine_EncarnacionFailureShot(string qName)
{
	ref sld = CharacterFromID("Miguel_Espinosa");

	LAi_ActorAnimation(sld, "Shot", "", 1.5);
	DoQuestFunctionDelay("CapBloodLine_EncarnacionFailureKill", 0.75);
}

void CapBloodLine_EncarnacionFailureKill(string qName)
{
	ref sld = CharacterFromID("Miguel_Espinosa");

	LAi_type_actor_Reset(sld);

	LAi_SetImmortal(pchar, false);
	LaunchBlood(pchar, 1.0 + frand(0.6), true, "fight");
	LAi_SetCurHP(pchar, 0.0);
	LAi_KillCharacter(pchar);
}

void CapBloodLine_PlaceOfficersBehindPchar()
{
	ref sld, diego;
	float px, py, pz;
	float dx, dy, dz;
	float dirX, dirZ, dist;
	float backX, backZ;
	float rightX, rightZ;
	float tx, tz;

	diego = CharacterFromID("Diego_Espinosa");

	if (!GetCharacterPos(pchar, &px, &py, &pz)) return;
	if (!GetCharacterPos(diego, &dx, &dy, &dz)) return;

	dirX = dx - px;
	dirZ = dz - pz;
	dist = sqrt(dirX * dirX + dirZ * dirZ);

	if (dist < 0.01) return;

	dirX = dirX / dist;
	dirZ = dirZ / dist;

	backX = -dirX;
	backZ = -dirZ;

	rightX = dirZ;
	rightZ = -dirX;

	// Дайк
	sld = CharacterFromID("Dieke");
	tx = px + backX * 1.5736 - rightX * 0.8192;
	tz = pz + backZ * 1.5736 - rightZ * 0.8192;

	// создаём временный локатор, чтобы потом чекнуть, не за границами ли патча координаты
	loadedLocation.locators.temp.CBL_Dieke.x = tx;
	loadedLocation.locators.temp.CBL_Dieke.y = py;
	loadedLocation.locators.temp.CBL_Dieke.z = tz;

	if (SetCharacterTask_GotoPoint(sld, "temp", "CBL_Dieke"))
	{
		TeleportCharacterToPosAy(sld, tx, py, tz, 0.0);
		LAi_SetStayType(sld);
		CharacterTurnByChr(sld, diego);
	}

	// Хагторп
	sld = CharacterFromID("Hugtorp");
	tx = px + backX * 1.9962 + rightX * 0.0872;
	tz = pz + backZ * 1.9962 + rightZ * 0.0872;

	loadedLocation.locators.temp.CBL_Hugtorp.x = tx;
	loadedLocation.locators.temp.CBL_Hugtorp.y = py;
	loadedLocation.locators.temp.CBL_Hugtorp.z = tz;

	if (SetCharacterTask_GotoPoint(sld, "temp", "CBL_Hugtorp"))
	{
		TeleportCharacterToPosAy(sld, tx, py, tz, 0.0);
		LAi_SetStayType(sld);
		CharacterTurnByChr(sld, diego);
	}

	// Волверстон
	sld = CharacterFromID("Volverston");
	tx = px + backX * 1.4226 + rightX * 0.9063;
	tz = pz + backZ * 1.4226 + rightZ * 0.9063;

	loadedLocation.locators.temp.CBL_Volverston.x = tx;
	loadedLocation.locators.temp.CBL_Volverston.y = py;
	loadedLocation.locators.temp.CBL_Volverston.z = tz;

	if (SetCharacterTask_GotoPoint(sld, "temp", "CBL_Volverston"))
	{
		TeleportCharacterToPosAy(sld, tx, py, tz, 0.0);
		LAi_SetStayType(sld);
		CharacterTurnByChr(sld, diego);
	}
}

// ---> bool отбработчик
bool CapBloodLine_QuestComplete(string sQuestName, string qname)
{
	ref sld, chr;
	int i, n, j;

	string sTemp, sQuest;
	string sBlade, sGun;
	string sPcharBlade, sPcharGun;

	bool condition = true;

	if (sQuestName == "CapBloodLine_OfficerTurnToLoc") {
		sld = CharacterFromID("CBLCitizMan_22");
		LAi_ActorTurnToLocator(sld, "goto", "goto17");

		sld = CharacterFromID("CBLCitizMan_23");
		LAi_ActorTurnToLocator(sld, "goto", "goto17");
	}

	else if (sQuestName == "CapBloodLine_Stid_GoFurder")
	{
		if (CheckAttribute(pchar, "questTemp.FluitCap.Stage1"))
		{
			sld = CharacterFromID("Stid_Clone");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest6", "CapBloodLine_Stid_GoFurder_1", -1);

			sld = CharacterFromID("FluitCap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest5", "CapBloodLine_FluitCap_GoFurder_1", -1);
			DeleteAttribute(pchar, "questTemp.FluitCap.Stage1");
		}
		else
		{
			pchar.questTemp.Stid.Stage1 = true;
		}
	}

	else if (sQuestName == "CapBloodLine_FluitCap_GoFurder")
	{
		if (CheckAttribute(pchar, "questTemp.Stid.Stage1"))
		{
			sld = CharacterFromID("Stid_Clone");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest6", "CapBloodLine_Stid_GoFurder_1", -1);

			sld = CharacterFromID("FluitCap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest5", "CapBloodLine_FluitCap_GoFurder_1", -1);
			DeleteAttribute(pchar, "questTemp.Stid.Stage1");
		}
		else
		{
			pchar.questTemp.FluitCap.Stage1 = true;
		}
	}

	else if (sQuestName == "CapBloodLine_Bishop_GoFurder")
	{
		if (CheckAttribute(pchar, "questTemp.Arabella.Stage1"))
		{
			sld = CharacterFromID("Bishop_Clone");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest5", "", -1);

			sld = CharacterFromID("Arabella");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest6", "", -1);
			DeleteAttribute(pchar, "questTemp.Arabella.Stage1");
		}
		else
		{
			pchar.questTemp.Bishop.Stage1 = true;
		}
	}

	else if (sQuestName == "CapBloodLine_Arabella_GoFurder")
	{
		if (CheckAttribute(pchar, "questTemp.Bishop.Stage1"))
		{
			sld = CharacterFromID("Bishop_Clone");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest5", "", -1);

			sld = CharacterFromID("Arabella");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest6", "", -1);
			DeleteAttribute(pchar, "questTemp.Bishop.Stage1");
		}
		else
		{
			pchar.questTemp.Arabella.Stage1 = true;
		}
	}

	else if (sQuestName == "CapBloodLine_Stid_GoFurder_1")
	{
		if (CheckAttribute(pchar, "questTemp.FluitCap.Stage2"))
		{
			sld = CharacterFromID("Stid_Clone");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest8", "", -1);

			sld = CharacterFromID("FluitCap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest7", "", -1);
			DeleteAttribute(pchar, "questTemp.FluitCap.Stage2");
		}
		else
		{
			pchar.questTemp.Stid.Stage2 = true;
		}
	}

	else if (sQuestName == "CapBloodLine_FluitCap_GoFurder_1")
	{
		if (CheckAttribute(pchar, "questTemp.Stid.Stage2"))
		{
			sld = CharacterFromID("Stid_Clone");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest8", "", -1);

			sld = CharacterFromID("FluitCap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest7", "", -1);
			DeleteAttribute(pchar, "questTemp.Stid.Stage2");
		}
		else
		{
			pchar.questTemp.FluitCap.Stage2 = true;
		}
	}

	else if (sQuestName == "CapBloodLine_FluitCapTurnToStid")
	{
		sld = CharacterFromID("FluitCap");
		LAi_ActorTurnToLocator(sld, "quest", "quest13");
	}

	else if (sQuestName == "CapBloodLine_StidCapTurnToFluit")
	{
		sld = CharacterFromID("Stid_Clone");
		LAi_ActorTurnToLocator(sld, "quest", "quest11");
	}

	else if (sQuestName == "CapBloodLine_ArabellaTurnToFluit")
	{
		sld = CharacterFromID("Arabella");
		LAi_ActorTurnToLocator(sld, "quest", "quest11");
	}

	else if (sQuestName == "CapBloodLine_BishopDialogWithFluitCap")
	{
		sld = CharacterFromID("Bishop_Clone");
		LAi_ActorTurnToLocator(sld, "quest", "quest11");

		sld = CharacterFromID("FluitCap");
		LAi_ActorTurnToLocator(sld, "quest", "quest10");

		sld = CharacterFromID("CBLDialogNPC");
		LAi_SetActorType(pchar);
		LAi_ActorWaitDialog(pchar, sld);
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);

		sld = CharacterFromID("Stid_Clone");
		CharacterTurnByChr(sld, CharacterFromID("Pitt_Clone"));
	}

	else if (sQuestName == "CapBloodLine_StidAndArabellaLeave")
	{
		CharacterTurnByChr(CharacterFromID("Stid_Clone"), CharacterFromID("Arabella"));
		CharacterTurnByChr(CharacterFromID("CBLCitizWoman_2"), CharacterFromID("Stid_Clone"));
	}

	else if (sQuestName == "CapBloodLine_FluitCapTurnToBishop")
	{
		sld = CharacterFromID("FluitCap");
		LAi_ActorTurnToLocator(sld, "quest", "quest11");
	}

	else if (sQuestName == "CapBloodLine_BishopStartDialog")
	{
		sld = CharacterFromID("CBLDialogNPC");
		sld.dialog.currentNode = "SOnSquere_7";
		LAi_SetStayType(pchar);
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}

	else if (sQuestName == "CapBloodLine_ArabellaWantBuyBlood_1")
	{
		sld = CharacterFromID("CBLDialogNPC");
		sld.name = FindPersonalName("BishopAndArabella");
		sld.dialog.currentNode = "SOnSquere_10";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}

	else if (sQuestName == "CapBloodLine_StidTurnToBishop")
	{
		CharacterTurnByChr(CharacterFromID("Stid_Clone"), CharacterFromID("Bishop_Clone"));
	}

	else if (sQuestName == "CapBloodLine_ArabellaOnPlantation")
	{
		sld = CharacterFromID("Arabella");
		LAi_SetActorType(sld);
		LAi_SetStayType(pchar);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}

	else if (sQuestName == "CapBloodLine_ArabellaSlaveSitDown_1")
	{
		sld = CharacterFromID("Slave_Arabella");
		LAi_SetSitPoorAnimation(sld);

		sld = CharacterFromID("Slave_Arabella_1");
		CharacterTurnByChr(sld, CharacterFromID("Slave_Arabella"));
		DoQuestFunctionDelay("CapBloodLine_ArabellaSlaveSitDown_2", 1.0);
	}

	else if (sQuestName == "CapBloodLine_ArabellaSlaveSitDown_3")
	{
		sld = CharacterFromID("Slave_Arabella_1");
		LAi_SetSitPoorAnimation(sld);
	}

	else if (sQuestName == "CapBloodLine_ArabellaGoHome_1")
	{
		sld = CharacterFromID("Slave_Arabella");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, CharacterFromID("Arabella"), "", -1.2);

		sld = CharacterFromID("Slave_Arabella_1");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, CharacterFromID("Arabella"), "", -1.2);
	}

	else if (sQuestName == "CapBloodLine_InPackhouse_DeleteGuard")
	{
		sld = CharacterFromID("SkladMan_30");
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}

	else if (sQuestName == "Pachouse_Mush_Trip")
	{
		sld = CharacterFromID("CBL_PackhouseGuard_Mush1");
		LAi_ActorTurnToLocator(sld, "goto", "goto4");
		DoQuestCheckDelay("Pachouse_Mush_Trip_2", 10.0);
	}

	else if (sQuestName == "Pachouse_Mush_Trip_2")
	{
		sld = CharacterFromID("CBL_PackhouseGuard_Mush1");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto7", "Pachouse_Mush_Trip_3", -1);
	}

	else if (sQuestName == "Pachouse_Mush_Trip_3")
	{
		sld = CharacterFromID("CBL_PackhouseGuard_Mush1");
		LAi_ActorTurnToLocator(sld, "goto", "goto10");
		DoQuestCheckDelay("Pachouse_Mush_Trip_4", 10.0);
	}

	else if (sQuestName == "Pachouse_Mush_Trip_4")
	{
		sld = CharacterFromID("CBL_PackhouseGuard_Mush1");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto4", "Pachouse_Mush_Trip", -1);
	}

	else if (sQuestName == "CapBloodLine_InPackhouse_return")
	{
		LAi_FadeEx(0.5, 0.5, 0.5, "", "CapBloodLine_InPackhouse_3", "");
	}

	else if (sQuestName == "CapBloodLine_InPackhouse_6")
	{
		LAi_SetActorType(pchar);
		LAi_ActorDialog(pchar, CharacterFromID("Arabella"), "", -1, 0);
	}

	else if (sQuestName == "CapBloodLine_InPackhouse_8")
	{
		sld = CharacterFromID("CBL_Matros_2");
		LAi_SetSitPoorAnimation(sld);
		TeleportCharacterToPosAy(sld, 4.50, 0.05, -9.37, 0.2);

		sld = CharacterFromID("CBL_Matros_3");
		ChangeCharacterAddressGroup(sld, "none", "", "");

		sld = CharacterFromID("CBL_Matros_5");
		ChangeCharacterAddressGroup(sld, "none", "", "");

		sld = GetCharacter(NPC_GenerateCharacter("CBL_Matros_5_1", "Citiz_42", "man", "man", 1, ENGLAND, -1, false));
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetSitPoorAnimation(sld);
		TeleportCharacterToPosAy(sld, -4.60, 0.05, -9.37, 0.2);
		sld.lifeDay = 0;

		sld = CharacterFromID("CBL_Matros_6");
		LAi_SetSitPoorAnimation(sld);
		TeleportCharacterToPosAy(sld, -7.77, 0.05, -9.37, 0.2);

		bDisableFastReload = true;
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("BridgeTown_Packhouse", "reload2", true);
		QuestPointerDelLoc("Bridgetown_town", "reload", "reload5_back");
		QuestPointerDelLoc("Bridgetown_Shipyard", "reload", "reload2");
		QuestPointerToLoc("Bridgetown_Shipyard", "reload", "reload1_back");
		QuestPointerToLoc("Bridgetown_Packhouse", "reload", "reload1");
		SetFunctionExitFromLocationCondition("CapBloodLine_ClearPackhouse", PChar.location, false);
		SetFunctionLocationCondition("CapBloodLine_ArabellaInTown", "Bridgetown_town", false);
	}

	else if (sQuestName == "CapBloodLine_InStidBedroom_2")
	{
		sld = CharacterFromID("Stid_Clone_1");
		sld.dialog.currentnode = "StidOnBed_8";
		LAi_SetActorType(pchar);
		LAi_ActorDialog(pchar, sld, "", -1, 0);
		QuestPointerDelLoc("CommonBedroom", "goto", "goto6");
	}

	else if (sQuestName == "CapBloodLine_InStidBedroom_3")
	{
		LAi_FadeEx(0.5, 0.5, 0.5, "", "CapBloodLine_InStidBedroom_4", "");
	}

	else if (sQuestName == "CapBloodLine_OnPlantationAgain_Turn")
	{
		CharacterTurnByChr(pchar, CharacterFromID("Arabella"));
		DoQuestFunctionDelay("CapBloodLine_OnPlantationAgain_1", 1.0);
	}

	else if (sQuestName == "CapBloodLine_NeedToSavePitt_5")
	{
		CharacterTurnByChr(pchar, CharacterFromID("Pitt"));
		DoQuestCheckDelay("CapBloodLine_NeedToSavePitt_6", 3.5);
	}

	else if (sQuestName == "CapBloodLine_NeedToSavePitt_6")
	{
		if (CheckAttribute(pchar, "questTemp.CBL_CameraIsReady")) LAi_FadeEx(0.5, 0.5, 0.5, "", "CapBloodLine_NeedToSavePitt_7", "");
		else DoQuestCheckDelay("CapBloodLine_NeedToSavePitt_6", 3.5);
	}

	else if (sQuestName == "CapBloodLine_NeedToSavePitt_8")
	{
		sld = CharacterFromID("Pitt");
		sld.dialog.currentnode = "Pitt_lay_2";
		LAi_SetStayType(pchar);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		DeleteAttribute(pchar, "questTemp.CBL_CameraIsReady");
	}

	else if (sQuestName == "CapBloodLine_NeedToSavePitt_10")
	{
		LAi_FadeEx(0.5, 0.5, 0.5, "", "CapBloodLine_NeedToSavePitt_11", "");
	}

	else if (sQuestName == "CapBloodLine_ClearSoldier")
	{
		for (i = 0; i < MAX_CHARACTERS; i++)
		{
			makeref(sld, Characters[i]);

			if (!CheckAttribute(sld, "location")) continue;
			if (sld.location != pchar.location) continue;
			if (sld.id == "CBL_Kent") continue;
			if (LAi_IsDead(sld)) continue;

			if (!CheckAttribute(sld, "model")) continue;
			if (findsubstr(sld.model, "milit_eng_", 0) != 0 && findsubstr(sld.model, "milit_mush_eng_", 0) != 0) continue;

			ChangeCharacterAddressGroup(sld, "none", "", "");
		}
	}

	else if (sQuestName == "CapBloodLine_NeedToSavePitt_20")
	{
		sld = CharacterFromID("CBL_Kent");
		CharacterTurnAy(sld, -1.5);
		sld.dialog.currentnode = "KentOnPlantation_4";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
	}

	else if (sQuestName == "CapBloodLine_BladGoesToCity_1")
	{
		SetCurrentTime(23, 00);
		RefreshLandTime();
		RecalculateJumpTable();

		DeleteAttribute(pchar, "GenQuest.CantRun");
		LAi_SetPlayerType(pchar);
		DoQuestFunctionDelay("CapBloodLine_BladGoesToCity_2", 0.1);

		sld = CharacterFromID("Bishop");
		if (sld.location == pchar.location) ChangeCharacterAddressGroup(sld, "none", "", "");
	}

	else if (sQuestName == "CapBloodLine_ArabellaInHouse_2")
	{
		LAi_SetStayType(pchar);
		PlaySound("Interface\knock.wav");
		DoQuestFunctionDelay("CapBloodLine_ArabellaInHouse_3", 2.0);
	}

	else if (sQuestName == "CapBloodLine_ArabellaInHouse_4")
	{
		sld = CharacterFromID("ArabelaService");
		CharacterTurnAy(sld, 0.2);
	}

	else if (sQuestName == "CapBloodLine_ArabellaInHouse_8")
	{
		CharacterTurnByChr(CharacterFromID("Arabella"), pchar);
	}

	else if (sQuestName == "CapBloodLine_ArabellaInHouse_10")
	{
		ChangeCharacterAddressGroup(CharacterFromID("CBL_James"), "none", "", "");
	}

	else if (sQuestName == "CapBloodLine_EsapeDialog_Dieke")
	{
		sld = CharacterFromID("Dieke");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "CapBloodLine_ED_Dieke", -1);
	}

	else if (sQuestName == "CapBloodLine_EsapeDialog_Slave_Quest")
	{
		sld = CharacterFromID("Slave_Quest");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
	}

	else if (sQuestName == "SaveArabelaServiceAfraid")
	{
		sld = CharacterFromID("ArabelaService");
		LAi_SetActorType(sld);
		LAi_ActorMoveToPoint(sld, true, -37.29, 7.28, -13.51, "SaveArabelaServiceAfraid_2", -1.0);
		LAi_FadeEx(0.2, 0.1, 0.2, "SaveArabelaServiceAfraid_1", "", "");
	}

	else if (sQuestName == "SaveArabelaServiceAfraid_2")
	{
		sld = CharacterFromID("ArabelaService");
		CharacterTurnByChr(sld, CharacterFromID("SpaRaider"));
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "afraid", "SaveArabelaServiceAfraid_3", 4.5);
	}

	else if (sQuestName == "SaveArabelaServiceAfraid_3")
	{
		sld = CharacterFromID("ArabelaService");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "afraid", "SaveArabelaServiceAfraid_3", 4.5);
	}

	else if (sQuestName == "CapBloodLine_TalkWithMary_2")
	{
		DoQuestCheckDelay("CapBloodLine_TalkWithMary_4", 1.0);
	}

	else if (sQuestName == "CapBloodLine_TalkWithMary_4")
	{
		LAi_FadeEx(0.5, 0.5, 0.5, "", "CapBloodLine_TalkWithMary_3", "");
	}

	else if (sQuestName == "CapBloodLine_SpaSoldiersAlarm")
	{
		if (CheckAttribute(pchar, "questTemp.CapBloodLine.SpaSoldiersAlarm")) return;

		pchar.questTemp.CapBloodLine.SpaSoldiersAlarm = true;

		if (LanguageGetLanguage() == "russian") PlaySound("Voice\Russian\EvilPirates01.wav");
		else PlaySound("Voice\English\EvilPirates01.wav");

		string slai_group = "CapBloodLine_SpaSoldiers";

		for (i = 0; i < MAX_CHARACTERS; i++)
		{
			makeref(sld, Characters[i]);

			if (!CheckAttribute(sld, "location")) continue;
			if (sld.location != pchar.location) continue;
			if (LAi_IsDead(sld)) continue;
			if (!CheckAttribute(sld, "model")) continue;

			if (findsubstr(sld.model, "sold_spa_", 0) == 0)
			{
				if (!LAi_IsFightMode(sld))
				{
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, slai_group);
				}
			}
		}

		LAi_group_SetRelation(slai_group, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(slai_group, LAI_GROUP_PLAYER, true);
		LAi_SetFightMode(pchar, true);
	}

	else if (sQuestName == "CapBloodLine_ED_TurnOgl")
	{
		CharacterTurnByChr(CharacterFromID("Ogl"), pchar);
	}

	else if (sQuestName == "CapBloodLine_ED_TurnHugtorp")
	{
		CharacterTurnByChr(CharacterFromID("Hugtorp"), pchar);
	}

	else if (sQuestName == "CapBloodLine_ED_Dieke")
	{
		CharacterTurnByChr(CharacterFromID("Dieke"), pchar);
	}

	else if (sQuestName == "CapBloodLine_firstEnterHome")
	{
		bDisableCharacterMenu = false;

		sld = characterFromID("Pitt");
		sld.Dialog.CurrentNode = "PStep_7";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_G6", "goto", "goto2");
		CharacterTurnToLoc(sld, "goto", "goto1");
		AddLandQuestmark_Main(sld, "CapBloodLine");

		Pchar.questTemp.CapBloodLine.statcrew = "";
		DoQuestFunctionDelay("MakeQuestAutoSaveDelay", 1.0);

		LAi_SetPlayerType(pchar);
		CharacterTurnByChr(pchar, sld);

		sld = CharacterFromID("CBL_Kent");
		ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto14");
		LAi_SetCitizenType(sld);
	}
	else if (sQuestName == "CapBloodLine_q1_Complited_1")
	{
		bQuestCheckProcessFreeze = true;
		WaitDate("",0,0,0, 12, 0); // прошло время
		SetCurrentTime(7, 0);
		RecalculateJumpTable();
		RefreshLandTime();
		bQuestCheckProcessFreeze = false;

		chrDisableReloadToLocation = false;
		bDisableCharacterMenu = false;
		LAi_SetPlayerType(pchar);
	}
	else if (sQuestName == "CapBloodLine_VolvTurn")
	{
		sld = CharacterFromID("Volverston");
		TeleportCharacterToPosAy(sld, 23.01, 2.71, 98.88, -0.7);
		sld.dialog.currentnode = "VLStep_Return";
		LAi_SetStayTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_CharacterEnableDialog(sld);
	}
	else if (sQuestName == "CapBloodLine_MorningIsComming_1")
	{
		/*bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		chrDisableReloadToLocation = false;*/
		ResetTimeScale();
		TEV.StopTimeScale = 1;
		TEV.StopTimeScale = true;

		LAi_SetStayType(pchar);
		StartQuestMovie(true, false, true);

		locCameraFlyUpRotateLookY(34.6, 4.59, 117.39, -50.0, 1.5, -60.0, 10.0, 4.5, 10.0);
		Pchar.FuncCameraFly = "CapBloodLine_CameraSleep";
		TeleportCharacterToPosAy(pchar, 31.65, 4.85, 116.5, -0.7);

		// Переодеваемся
		pchar.model = "Blad_0";
		Characters_RefreshModel(pchar);
		if (!CheckCharacterItem(pchar, "suit_1")) GiveItem2Character(pchar, "suit_1");

		string sChars[5];

		sChars[0] = "Pitt";
		sChars[1] = "Volverston";
		sChars[2] = "Hugtorp";
		sChars[3] = "Dieke";
		sChars[4] = "Ogl";

		for (i = 0; i < 5; i++)
		{
			if (GetCharacterIndex(sChars[i]) == -1) continue;
			sld = CharacterFromID(sChars[i]);

			// Переодеваем офов, кроме Питта
			if (sld.id != "Pitt")
			{
				sld.model = sld.id;
				Characters_RefreshModel(sld);
			}

			switch (sld.id)
			{
				case "Pitt":
					AddPassenger(pchar, sld, false);
					SetCharacterRemovable(sld, false);
					LAi_SetCurHP(sld, 1.0);
					sld.Health.HP = 1.0;
					sld.chr_ai.energy = 1.0;
					LAi_SetRolyPoly(sld, true);
					LAi_SetLayType(sld);
					ChangeCharacterAddressGroup(sld, "Cabin_Quest", "goto", "goto1");
					TeleportCharacterToPosAy(sld, 1.83, 9.05, 5.41, 0.0);
					SetFunctionLocationCondition("CapBloodLine_PittInCabin", "Cabin_Quest", true);
				break;

				case "Volverston":
					sld.dialog.currentnode = "VolcOnDeck";
					sld.GenQuest.CantRun = true;
					TeleportCharacterToPosAy(sld, 21.93, 2.66, 104.34, 0.0);
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				break;

				case "Hugtorp":

					// LAi_SetActorType(sld);
					// LAi_ActorDialog(sld, pchar, "", -1, 0);
				break;

				case "Dieke":
					sld.dialog.currentnode = "DiekeOnDeck_1";
					TeleportCharacterToPosAy(sld, 6.79, 8.4, 84.32, 3.2);
				break;

				case "Ogl":
					ChangeCharacterAddressGroup(sld, "none", "", "");
				break;
			}
		}

		DoQuestFunctionDelay("CapBloodLine_RedrawWeapons", 0.2);
	}
	else if (sQuestName == "CapBloodLine_HugtorpAttackDiego")
	{
		sld = CharacterFromID("Hugtorp");
		CharacterTurnByChr(sld, CharacterFromID("Diego_Clone"));
		// LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "attack_break_1", "", 1.7);
		DoQuestCheckDelay("CapBloodLine_HugtorpAttackDiego_1", 1.0);
	}
	else if (sQuestName == "CapBloodLine_HugtorpAttackDiego_1")
	{
		sld = CharacterFromID("Diego_Clone");
		LAi_KillCharacter(sld);
		sld.lifeday = 0;

		for (i = 1; i <= 4; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DiegoGuard_" + i, "navy_spa_" + (rand(7) + 1), "man", "man", 10, SPAIN, -1, false));
			sld.FaceId = 522 + i;
			SetFantomParamFromRank(sld, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, true);
			LAi_LoginInCaptureTown(sld, true);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest20");
			LAi_ActorGoToLocator(sld, "quest", "quest11", "", -1);
		}

		chr = GetCharacter(NPC_GenerateCharacter("Esteban_Espinosa", "Esteban_Espinosa", "man", "man", 10, SPAIN, -1, false));
		FantomMakeCoolFighter(chr, 5, 5, 5, "blade22", "pistol5", 1);
		chr.name = FindPersonalName("Esteban_name");
		chr.lastname = FindPersonalName("De_Espinosa_lastname");
		chr.FaceId = 69692;
		chr.Dialog.Filename = "Quest\CapBloodLine\Bishop.c";
		LAi_SetCheckMinHP(chr, 1, true, "CapBloodLine_EstebanSurrendered");
		// chr.Dialog.CurrentNode = "DiegoOnDeck";
		LAi_LoginInCaptureTown(chr, true);
		ChangeCharacterAddressGroup(chr, pchar.location, "quest", "quest15");
		LAi_SetActorType(chr);
		LAi_ActorGoToLocator(chr, "quest", "quest11", "CapBloodLine_HugtorpAttackDiego_2", -1);
	}

	else if (sQuestName == "CapBloodLine_HugtorpAttackDiego_2")
	{
		for (i = 1; i <= 4; i++)
		{
			if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

			sld = CharacterFromID("DiegoGuard_" + i);
			if (sld.location != pchar.location) continue;
			CharacterTurnByChr(sld, pchar);
			LAi_SetStayType(sld);
		}

		sld = CharacterFromID("Esteban_Espinosa");
		CharacterTurnByChr(sld, pchar);
		LAi_SetStayType(sld);

		locCameraResetState();
		locCameraToPos(21.8, 4.35, 102.05, false);
		locCameraTarget(sld);

		DoQuestFunctionDelay("CapBloodLine_DiegoDeckStartFight", 1.5);
	}

	else if (sQuestName == "CapBloodLine_EstebanSurrendered")
	{
		int iDiegoGuardsAlive = 0;
		LAi_group_SetRelation("DiegoGuards", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);

		for (i = 1; i <= 4; i++)
		{
			if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

			sld = CharacterFromID("DiegoGuard_" + i);
			if (sld.location != pchar.location) continue;
			if (LAi_IsDead(sld)) continue;
			iDiegoGuardsAlive++;
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, true);
		}
		pchar.questTemp.CapBloodLine.DieGoGuardsAlive = iDiegoGuardsAlive;
		Log_TestInfo("Diego guards alive = " + iDiegoGuardsAlive);

		sld = CharacterFromID("Esteban_Espinosa");
		sld.Dialog.CurrentNode = "EstebanSurrender";
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);
		LAi_SetFightMode(pchar, false);
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);

		DoQuestFunctionDelay("CapBloodLine_EstebanSurrendered_1", 1.0);
	}

	else if (sQuestName == "CapBloodLine_EstebanSurrendered_5")
	{
		sld = CharacterFromID("Dieke");
		LAi_ActorDialog(sld, pchar, "", -1, 0);

		locCameraSleep(false);
		locCameraFromToPos(26.5, 4.26, 106.31, false, 36.43, 2.64, 105.15);
	}

	else if (sQuestName == "CapBloodLine_SpanishSoldierVolley")
	{
		if (CheckAttribute(pchar, "questTemp.CapBloodLine.SpanishSoldierVolley")) return;
		pchar.questTemp.CapBloodLine.SpanishSoldierVolley = true;

		DoQuestCheckDelay("CapBloodLine_SpanishSoldierVolley_Shot1", 0.42);
		DoQuestCheckDelay("CapBloodLine_SpanishSoldierVolley_Shot2", 0.1);
		DoQuestCheckDelay("CapBloodLine_SpanishSoldierVolley_Shot3", 0.28);
	}

	else if (sQuestName == "CapBloodLine_SpanishSoldierVolley_Kill_1")
	{
		sld = CharacterFromID("CBL_SpaSoldSwim_1");
		SetCharacterActionAnimation(sld, "dead", "death_1");
		LAi_KillCharacter(sld);

		for (i = 1; i <= 6; i++)
		{
			sld = CharacterFromID("CBL_SpaSoldSwim_" + i);
			if (LAi_IsDead(sld)) continue;

			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "CBL_SpaSwimEnemy");
		}
		DoQuestCheckDelay("CapBloodLine_SpanishSoldierFight", 1.0);
	}

	else if (sQuestName == "CapBloodLine_SpanishSoldierFight")
	{
		for (i = 1; i <= 3; i++)
		{
			sld = CharacterFromID("CBL_EngMushketer_" + i);
			sld.MusketerDistance = 0;
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_group_MoveCharacter(sld, "CBL_EngMushketers");
		}

		LAi_group_SetRelation("CBL_SpaSwimEnemy", "CBL_EngMushketers", LAI_GROUP_ENEMY);
		LAi_group_FightGroups("CBL_SpaSwimEnemy", "CBL_EngMushketers", true);
	}

	else if (sQuestName == "CapBloodLine_SpanishSoldierVolley_Kill_2")
	{
		sld = CharacterFromID("CBL_SpaSoldSwim_2");
		SetCharacterActionAnimation(sld, "dead", "death_3");
		LAi_KillCharacter(sld);
	}

	else if (sQuestName == "CapBloodLine_SpanishSoldierVolley_Kill_3")
	{
		sld = CharacterFromID("CBL_SpaSoldSwim_3");
		SetCharacterActionAnimation(sld, "dead", "death_9");
		LAi_KillCharacter(sld);
	}

	else if (sQuestName == "CapBloodLine_SpanishSoldierVolley_Shot1")
	{
		sld = CharacterFromID("CBL_EngMushketer_1");
		CharacterTurnByChr(sld, CharacterFromID("CBL_SpaSoldSwim_1"));
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Shot", "", 2.5);
		DoQuestCheckDelay("CapBloodLine_SpanishSoldierVolley_Kill_1", 0.8);
	}

	else if (sQuestName == "CapBloodLine_SpanishSoldierVolley_Shot2")
	{
		sld = CharacterFromID("CBL_EngMushketer_2");
		CharacterTurnByChr(sld, CharacterFromID("CBL_SpaSoldSwim_2"));
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Shot", "", 2.5);
		DoQuestCheckDelay("CapBloodLine_SpanishSoldierVolley_Kill_2", 0.8);
	}

	else if (sQuestName == "CapBloodLine_SpanishSoldierVolley_Shot3")
	{
		sld = CharacterFromID("CBL_EngMushketer_3");
		CharacterTurnByChr(sld, CharacterFromID("CBL_SpaSoldSwim_3"));
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Shot", "", 2.5);
		DoQuestCheckDelay("CapBloodLine_SpanishSoldierVolley_Kill_3", 0.8);
	}

	else if (sQuestName == "CapBloodLine_BishopShot_1")
	{
		chr = CharacterFromID("CBL_EngMushketer_1");

		for (i = 4; i <= 6; i++)
		{
			if (GetCharacterIndex("CBL_SpaSoldSwim_" + i) == -1) continue;

			sld = CharacterFromID("CBL_SpaSoldSwim_" + i);
			if (LAi_IsDead(sld)) continue;
			if (!CheckAttribute(sld, "quest.DeadMan_1")) continue;

			CharacterTurnByChr(chr, sld);
			LAi_ActorAnimation(chr, "Shot", "CapBloodLine_BishopKill_1", 1.8);
			break;
		}
	}

	else if (sQuestName == "CapBloodLine_BishopShot_2")
	{
		chr = CharacterFromID("CBL_EngMushketer_2");

		for (i = 4; i <= 6; i++)
		{
			if (GetCharacterIndex("CBL_SpaSoldSwim_" + i) == -1) continue;

			sld = CharacterFromID("CBL_SpaSoldSwim_" + i);
			if (LAi_IsDead(sld)) continue;
			if (!CheckAttribute(sld, "quest.DeadMan_2")) continue;

			CharacterTurnByChr(chr, sld);
			LAi_ActorAnimation(chr, "Shot", "CapBloodLine_BishopKill_2", 1.8);
			break;
		}
	}

	else if (sQuestName == "CapBloodLine_BishopShot_3")
	{
		chr = CharacterFromID("CBL_EngMushketer_3");

		for (i = 4; i <= 6; i++)
		{
			if (GetCharacterIndex("CBL_SpaSoldSwim_" + i) == -1) continue;

			sld = CharacterFromID("CBL_SpaSoldSwim_" + i);
			if (LAi_IsDead(sld)) continue;
			if (!CheckAttribute(sld, "quest.DeadMan_3")) continue;

			CharacterTurnByChr(chr, sld);
			LAi_ActorAnimation(chr, "Shot", "CapBloodLine_BishopKill_3", 1.8);
			break;
		}
	}

	else if (sQuestName == "CapBloodLine_BishopKill_1")
	{
		for (i = 4; i <= 6; i++)
		{
			if (GetCharacterIndex("CBL_SpaSoldSwim_" + i) == -1) continue;

			sld = CharacterFromID("CBL_SpaSoldSwim_" + i);
			if (LAi_IsDead(sld)) continue;
			if (!CheckAttribute(sld, "quest.DeadMan_1")) continue;

			SetCharacterActionAnimation(sld, "dead", "death_2");
			LAi_KillCharacter(sld);
			break;
		}
	}

	else if (sQuestName == "CapBloodLine_BishopKill_2")
	{
		for (i = 4; i <= 6; i++)
		{
			if (GetCharacterIndex("CBL_SpaSoldSwim_" + i) == -1) continue;

			sld = CharacterFromID("CBL_SpaSoldSwim_" + i);
			if (LAi_IsDead(sld)) continue;
			if (!CheckAttribute(sld, "quest.DeadMan_2")) continue;

			SetCharacterActionAnimation(sld, "dead", "death_4");
			LAi_KillCharacter(sld);
			break;
		}
	}

	else if (sQuestName == "CapBloodLine_BishopKill_3")
	{
		for (i = 4; i <= 6; i++)
		{
			if (GetCharacterIndex("CBL_SpaSoldSwim_" + i) == -1) continue;

			sld = CharacterFromID("CBL_SpaSoldSwim_" + i);
			if (LAi_IsDead(sld)) continue;
			if (!CheckAttribute(sld, "quest.DeadMan_3")) continue;

			SetCharacterActionAnimation(sld, "dead", "death_8");
			LAi_KillCharacter(sld);
			break;
		}
	}

	else if (sQuestName == "CapBloodLine_BishipOnPirsTurn")
	{
		sld = CharacterFromID("Bishop");
		CharacterTurnAy(sld, 0.4);

		sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
		CharacterTurnByChr(sld, CharacterFromID("bishop"));

		sld = CharacterFromID("CBL_OfficerBishop");
		CharacterTurnByChr(sld, CharacterFromID("Bishop"));

		LAi_FadeEx(2.0, 1.0, 1.0, "", "CapBloodLine_StartBoatScene", "");
	}

	else if (sQuestName == "CapBloodLine_BishopDialogOnDeck")
	{
		sld = CharacterFromID("Bishop");
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}

	else if (sQuestName == "CapBloodLine_BishopOffTurn")
	{
		sld = CharacterFromID("CBL_OfficerBishop");
		CharacterTurnByChr(sld, pchar);
	}

	else if (sQuestName == "CapBloodLine_BishopOffTurn_1")
	{
		sld = CharacterFromID("CBL_OfficerBishop_1");
		CharacterTurnByChr(sld, pchar);
	}

	else if (sQuestName == "CapBloodLine_BishopGoToSwiming_2")
	{
		sld = CharacterFromID("Bishop");
		CharacterTurnAy(sld, -3.0);
		DoQuestFunctionDelay("CapBloodLine_BishopGoToSwiming_3", 2.0);
	}

	else if (sQuestName == "CapBloodLine_BishopGoToSwiming_5")
	{
		sld = CharacterFromID("Bishop");
		ChangeCharacterAddressGroup(sld, "none", "", "");
	}

	else if (sQuestName == "CapBloodLine_RoadToEspaniola_2")
	{
		sld = CharacterFromID("Diego_Espinosa");
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
	}

	else if (sQuestName == "CapBloodLine_DiegoFistFightWin")
	{
		CapBloodLine_DiegoFistFightEnd(true);
	}

	else if (sQuestName == "CapBloodLine_DiegoFistFightLose")
	{
		CapBloodLine_DiegoFistFightEnd(false);
	}

	else if (sQuestName == "CapBloodLine_Siguayo_3")
	{
		DoQuestFunctionDelay("CapBloodLine_Siguayo_4", 2.0);
	}

	else if (sQuestName == "CapBloodLine_DiegoOnShoreTurn")
	{
		sld = CharacterFromID("Diego_Espinosa");
		CharacterTurnToLoc(sld, "goto", "goto7");
	}

	else if (sQuestName == "CapBloodLine_SonsTrable_4")
	{
		sld = CharacterFromID("Esteban_Espinosa");
		sld.dialog.currentnode = "EstebanFather_1";
		LAi_CharacterEnableDialog(sld);
		LAi_ActorDialog(pchar, sld, "", -1, 0);

		for (i = 1; i <= 4; i++)
		{
			if (GetCharacterIndex("DiegoGuard_" + i) == -1) continue;

			sld = CharacterFromID("DiegoGuard_" + i);
			if (LAi_IsDead(sld)) continue;
			CharacterTurnByChr(sld, pchar);
		}
	}

	else if (sQuestName == "CapBloodLine_SonsTrable_11")
	{
		sld = CharacterFromID("Dieke");
		if (!CheckAttribute(sld, "DiekeReadyTalk"))
		{
			sld.DiekeReadyTalk = true;
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
	}
	else if (sQuestName == "CapBloodLine_NeedSolution_1")
	{
		sld = CharacterFromID("Hugtorp");
		sld.Dialog.CurrentNode = "CapBloodLine_Tortuga_1";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
	}

else
	{
		condition = false;
	}

	return condition;
}



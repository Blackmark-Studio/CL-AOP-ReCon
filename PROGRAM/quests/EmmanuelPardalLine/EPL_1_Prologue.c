
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Эммануэль Пардаль
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void EPL_StartGame(string qName)
{
	SetQuestsCharacters();
	bDisableLandEncounters = true;
	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	pchar.GenQuest.CannotWait = true;
	TEV.captainInTheLSC = true;
	SetCaptureTownByNation("LaVega", SPAIN);
	pchar.questTemp.EPL_Prologue = true;
	pchar.questTemp.EPL_PrologueCitizens = "Dialogue 1";
	pchar.questTemp.EPL_Line = true;		//На всякий случай (нигде не задействовано)
	LocatorReloadEnterDisable("SantoDomingo_ExitTown", "reload1_back", true);
	LocatorReloadEnterDisable("PortPax_ExitTown", "reload3", true);
	LocatorReloadEnterDisable("LaVega_town", "reload4_back", true);
	
	DeleteAttribute(Pchar, "ship");
	DeleteAttribute(Pchar, "ShipSails.gerald_name");
	Pchar.ship.type = SHIP_NOTUSED;
	
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("EPL_Rebekka", "RebekkaRemedios", "woman", "Danielle", 10, SPAIN, -1, false));
	sld.name	= FindPersonalName("EPL_Rebekka_name");
	sld.lastname	= FindPersonalName("EPL_Rebekka_lastname");
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "Rebekka_v_komnate_1";
	LAi_SetActorType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_houseSp3_room1","goto","goto8");

	RemoveAllCharacterItems(pchar, true);
	DeleteAttribute(pchar, "items");
	GiveItem2Character(pchar, "blade9");
	EquipCharacterbyItem(pchar, "blade9");
	// GiveItem2Character(pchar, "suit_1");
	// EquipCharacterbyItem(pchar, "suit_1");
	TakeNItems(pchar, "potion1", 3);
	AddMoneyToCharacter(PChar, 500);
	ClearActiveStageNotifications();
	pchar.GenQuestBox.LaVega_houseSp3_room1.box4.items.map_hisp = 1;
	pchar.GenQuestBox.LaVega_houseSp3_room1.box4.items.jewelry7 = 1;
	pchar.GenQuestBox.LaVega_houseSp3_room1.box4.items.mineral8 = 2;
	pchar.GenQuestBox.LaVega_houseSp3_room1.box4.items.jewelry2 = 5;
	pchar.model = "Emmanuel_6";
	Characters_RefreshModel(pchar);
	
	LAi_SetActorType(pchar);
	StartQuestMovie(true, false, true);
	LAi_FadeEx(0.0, 1.0, 1.0, "", "EPL_StartGame_2", "");
	
	pchar.quest.EPL_PZD_Quest.win_condition.l1 = "Rank";
	pchar.quest.EPL_PZD_Quest.win_condition.l1.value = 3;
	pchar.quest.EPL_PZD_Quest.win_condition.l1.operation = ">=";
	PChar.quest.EPL_PZD_Quest.function = "EPL_PZD_Quest";
}
void EPL_StartGame_2(string qName)
{
	locCameraFromToPos(1.03, 3.36, 9.48, true, -0.90, 1.37, 10.71);
	DoQuestFunctionDelay("EPL_Razgovor_1", 2.5);
}

void EPL_Razgovor_1(string qName)
{
	LAi_ActorGoToLocator(pchar, "barmen", "stay", "", -1);
	DoQuestFunctionDelay("EPL_Razgovor_2", 2.0);
}
void EPL_Razgovor_2(string qName)
{
	LAi_SetStayType(pchar);
	
	ref sld;
	sld = CharacterFromID("EPL_Rebekka");
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void EPL_SettingHero()
{
	locCameraSleep(true);
	LAi_FadeEx(1.0, 0.5, 1.0, "EPL_SettingHero_2", "EPL_SettingHero_3", "EPL_SettingHero_4");
}

void EPL_SettingHero_2(string qName)
{
	locCameraSleep(false);
	EndQuestMovie();
	locCameraFollowEx(true);
}

void EPL_SettingHero_3(string qName)
{
	LAi_SetPlayerType(pchar);
}

void EPL_SettingHero_4(string qName)
{
	chrDisableReloadToLocation = false;
	SetQuestHeader("EPL_Prologue");
	AddQuestRecord("EPL_Prologue", "1");
	
	ref sld;
	sld = CharacterFromID("EPL_Rebekka");
	LAi_SetActorType(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	
	PChar.quest.EPL_Rebekka_gulyat.win_condition.l1 = "location";
	PChar.quest.EPL_Rebekka_gulyat.win_condition.l1.location = "LaVega_town";
	PChar.quest.EPL_Rebekka_gulyat.function = "EPL_Rebekka_gulyat";
	
	sld = CharacterFromID("Edward Mansfield");
	ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
	
	ref loc = &Locations[FindLocation("LaVega_town")];
	loc.locators_radius.merchant.merchant3 = 3.5;
	
	//Испанский губернатор
	sld = GetCharacter(NPC_GenerateCharacter("EPL_LaVegaIspanski_Gubernator", "huber_15", "man", "man", 15, SPAIN, -1, false));
	FantomMakeCoolFighter(sld, 100, 100, 100, "blade20", "howdah", 500);
	sld.name	= FindPersonalName("EPL_Aurelio_name");
	sld.lastname	= FindPersonalName("EPL_Aurelio_lastname");
	sld.SaveItemsForDead = true;
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "LaVegaIspanski_Gubernator";
	LAi_SetHuberType(sld);
	LAi_SetImmortal(sld, true);
	RemoveAllCharacterItems(sld, true);
	AddMoneyToCharacter(sld, 12345);
	GiveItem2Character(sld, "blade19");
	EquipCharacterByItem(sld, "blade19");
	GiveItem2Character(sld, "indian17");
	AddItems(sld, "jewelry4", 30);
	ChangeCharacterAddressGroup(sld,"LaVega_townhall","sit","sit1");
	
	//Торговец на улице (продолжение квеста)
	sld = GetCharacter(NPC_GenerateCharacter("EPL_Kotes", "merch_14", "man", "man", 1, SPAIN, -1, false));
	FantomMakeCoolFighter(sld, 1, 10, 10, "blade3", "", 0);
	sld.name	= FindPersonalName("EPL_Gasten_name");
	sld.lastname	= FindPersonalName("EPL_Gasten_lastname");
	SetCharacterPerk(sld, "Trader");
	SetCharacterPerk(sld, "BasicCommerce");
	SetSPECIAL(sld, 6, 4, 8, 8, 10, 6, 7);
	SetShipSkill(sld, 27, 45, 21, 14, 18, 21, 13, 9, 28);
	TakeNItems(sld,"potion1", -10);
	TakeNItems(sld,"potion2", -10);
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "Torgovets_1";
	LAi_SetActorType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","merchant","merchant3");
	
	//Девушка на улице (продолжение квеста)
	sld = GetCharacter(NPC_GenerateCharacter("EPL_SofiaPiedad", "Sofia_Piedad", "woman", "Beatrice", 10, SPAIN, -1, false));
	sld.name	= FindPersonalName("EPL_Sofia_name");
	sld.lastname	= FindPersonalName("EPL_Sofia_lastname");
	LAi_SetActorType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","merchant","mrcActive3");
	
	SetFunctionLocatorCondition("EPL_KotesStartsDialog", "LaVega_town", "merchant", "merchant3", false);
	QuestPointerToLoc("LaVega_houseSp3_room1", "reload", "reload3");
	QuestPointerToLoc("LaVega_houseSp3", "reload", "reload1");
	QuestPointerToLoc("LaVega_town", "merchant", "merchant3");
}

void EPL_Rebekka_gulyat(string qName)
{
	ref sld;
	sld = CharacterFromID("EPL_Rebekka");
	LAi_SetCitizenType(sld);
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	
	DoQuestFunctionDelay("EPL_UbiraemNPC_Gener", 0.5);	
}
void EPL_UbiraemNPC_Gener(string qName)
{
	//Убираем персонажа, который мешает
	ref sld, characterRef;
	sld = CharacterFromID("EPL_Kotes");
	int characterIndex = LAi_FindNearestVisCharacter(sld, 25);

	if(characterIndex != -1)
	{
		characterRef = &Characters[characterIndex];

		if(!LAi_IsImmortal(characterRef))
		{
			ChangeCharacterAddressGroup(characterRef, "none", "", "");
			LAi_KillCharacter(characterRef);
		}
	}
}

void EPL_KotesStartsDialog(string qName)
{
	LAi_SetActorType(pchar);
	LAi_FadeEx(1.0, 0.3, 1.0, "EPL_KotesStartsDialog_2", "", "");
	QuestPointerDelLoc("LaVega_houseSp3_room1", "reload", "reload3");
	QuestPointerDelLoc("LaVega_houseSp3", "reload", "reload1");
	QuestPointerDelLoc("LaVega_town", "merchant", "merchant3");
}

void EPL_KotesStartsDialog_2(string qName)
{
	StartQuestMovie(true, false, true);
	locCameraFromToPos(-45.58, 4.01, 25.93, true, -46.24, 1.03, 29.42);
	TeleportCharacterToPosAy(pchar, -41.47, 1.47, 27.46, -1.30);
	ref sld = CharacterFromID("EPL_SofiaPiedad");
	CharacterTurnByChr(sld, CharacterFromID("EPL_Kotes"));
	sld = CharacterFromID("EPL_Kotes");
	CharacterTurnByChr(sld, CharacterFromID("EPL_SofiaPiedad"));
	DoQuestFunctionDelay("EPL_KotesStartsDialog_3", 1.5);
}

void EPL_KotesStartsDialog_3(string qName)
{	
	AoP_NPCDialogClear();
	
	AoP_NPCDialogAddLine("EPL_Kotes", StringFromKey("EPL_1_Prologue_script_1"));
	AoP_NPCDialogAddLine("EPL_SofiaPiedad", StringFromKey("EPL_1_Prologue_script_2"));
	AoP_NPCDialogAddLine("EPL_Kotes", StringFromKey("EPL_1_Prologue_script_3"));
	AoP_NPCDialogLaunchFunction("EPL_SofiaPiedad", "EPL_Kotes", "EPL_KotesStartsDialog_4");
}

void EPL_KotesStartsDialog_4(string qName)
{
	locCameraFromToPos(-48.04, 4.08, 25.66, true, -45.41, 1.52, 27.79);
	
	DoQuestFunctionDelay("EPL_KotesStartsDialog_5", 0.5);
}

void EPL_KotesStartsDialog_5(string qName)
{
	LAi_ActorMoveToPoint(pchar, false, -43.56, 1.50, 28.36, "", -1);
	
	DoQuestFunctionDelay("EPL_KotesStartsDialog_6", 1.0);
}

void EPL_KotesStartsDialog_6(string qName)
{
	ref sld = CharacterFromID("EPL_Kotes");
	CharacterTurnByChr(sld, pchar);
	sld = CharacterFromID("EPL_SofiaPiedad");
	CharacterTurnByChr(sld, pchar);
	
	DoQuestFunctionDelay("EPL_KotesStartsDialog_7", 0.01);
}

void EPL_KotesStartsDialog_7(string qName)
{
	AoP_NPCDialogClear();
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_1_Prologue_script_4"));
	AoP_NPCDialogAddLine("EPL_Kotes", StringFromKey("EPL_1_Prologue_script_5", pchar.name));
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_1_Prologue_script_6"));
	AoP_NPCDialogAddLine("EPL_Kotes", StringFromKey("EPL_1_Prologue_script_7"));
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_1_Prologue_script_8"));
	AoP_NPCDialogAddLine("EPL_Kotes", StringFromKey("EPL_1_Prologue_script_9"));
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_1_Prologue_script_10"));
	AoP_NPCDialogLaunchFunction("Blaze", "EPL_Kotes", "EPL_KotesRun");
}

void EPL_KotesRun(string qName)
{
	LAi_SetActorType(pchar);
	
	ref sld = CharacterFromID("EPL_Kotes");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1);
	chrDisableReloadToLocation = true;
	
	sld = CharacterFromID("EPL_SofiaPiedad");
	LAi_SetActorType(sld);
	
	PChar.quest.EPL_Dialog_s_Kotesom.win_condition.l1 = "location";
	PChar.quest.EPL_Dialog_s_Kotesom.win_condition.l1.location = "LaVega_ExitTown";
	PChar.quest.EPL_Dialog_s_Kotesom.function = "EPL_Dialog_s_Kotesom";
	
	DoQuestFunctionDelay("EPL_KotesRun_1", 1.0);
	DoQuestFunctionDelay("EPL_KotesRun_2", 2.0);
}

void EPL_KotesRun_1(string qName)
{
	CharacterTurnToLoc(pchar, "goto", "goto10");
}

void EPL_KotesRun_2(string qName)
{
	locCameraFromToPos(-37.60, 4.70, 26.64, true, -30.45, 1.40, 27.15);
	ref sld = CharacterFromID("EPL_Kotes");
	TeleportCharacterToPosAy(sld, -38.89, 1.47, 26.38, 1.50);
	
	DoQuestFunctionDelay("EPL_KotesRun_3", 3.0);
}

void EPL_KotesRun_3(string qName)
{
	locCameraFromToPos(-18.19, 6.20, 9.58, true, -7.92, 2.94, 4.67);
	ref sld = CharacterFromID("EPL_Kotes");
	TeleportCharacterToPosAy(sld, -15.97, 0.89, 8.85, 1.70);
	
	DoQuestFunctionDelay("EPL_KotesRun_4", 3.0);
}

void EPL_KotesRun_4(string qName)
{
	LAi_FadeEx(1.0, 0.3, 1.0, "", "EPL_KotesRun_5", "");
}

void EPL_KotesRun_5(string qName)
{
	EndQuestMovie();
	LAi_SetPlayerType(pchar);
	locCameraFollowEx(true);
	
	ref sld;
	sld = CharacterFromID("EPL_Rebekka");
	LAi_SetCitizenType(sld);
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	
	AddQuestRecord("EPL_Prologue", "2");
	
	QuestPointerToLoc("LaVega_town", "reload", "reload2_back");
}

void EPL_Dialog_s_Kotesom(string qName)
{
	ref sld;
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("LaVega_ExitTown")], true);
	
	sld = CharacterFromID("EPL_Kotes");
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "Torgovets_10";
	ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "enc04", "enc04_04");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void EPL_Draka_s_Kotesom()
{
	ref sld;
	LAi_LocationFightDisable(&Locations[FindLocation("LaVega_ExitTown")], false);
	LAi_SetFightMode(pchar, true);
	
	sld = CharacterFromID("EPL_Kotes");
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, false);
	LAi_SetCheckMinHPFunction(sld, 1, true, "EPL_Draka_s_Kotesom_Pobeda");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	sld.MultiFighter = 0.3;
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	
	DoQuestFunctionDelay("MakeQuestAutoSaveDelay", 1.0);
}

void EPL_Draka_s_Kotesom_Pobeda(string qName)
{
	LAi_group_Delete("EnemyFight");
	DoQuestCheckDelay("hide_weapon", 1.2);
	LAi_RemoveCheckMinHP(pchar);
	ref sld = characterFromId("EPL_Kotes");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, pchar);
	LAi_ActorAnimationFunction(sld, "ground_sitdown", "EPL_Draka_s_Kotesom_Pobeda_2", 5.0);
	LAi_LocationFightDisable(&Locations[FindLocation("LaVega_ExitTown")], true);
}

void EPL_Draka_s_Kotesom_Pobeda_2(string qName)
{
	ref sld;
	sld = characterFromId("EPL_Kotes");
	LAi_SetActorType(sld);
	LAi_ActorSetGroundSitMode(sld);
	sld = CharacterFromID("EPL_Rebekka");
	PlaceCharacter(sld, "goto", PChar.location);
	sld.dialog.currentnode = "Rebekka_posle_draki";
	LAi_ActorDialogDelay(sld, pchar, "", 1.0);
}

void Rebekka_posle_draki()
{
	ref sld;
	chrDisableReloadToLocation = false;
	bDisableFastReload = true;
	AddQuestRecord("EPL_Prologue", "3");
	
	PChar.quest.EPL_Oba_ischezaut.win_condition.l1 = "ExitFromLocation";
	PChar.quest.EPL_Oba_ischezaut.win_condition.l1.location = PChar.location;
	PChar.quest.EPL_Oba_ischezaut.function = "EPL_Oba_ischezaut";

	sld = characterFromId("EPL_Rebekka");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, characterFromId("EPL_Kotes"), "", -1);
	
	sld = CharacterFromID("EPL_SofiaPiedad");
	LAi_SetCitizenType(sld);
	ChangeCharacterAddressGroup(sld, "LaVega_town", "goto", "goto2");
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "Sofia_1";
	
	QuestPointerDelLoc("LaVega_town", "reload", "reload2_back");
	QuestPointerToLoc("LaVega_ExitTown", "reload", "reload1_back");
	AddLandQuestMark_Main(CharacterFromID("EPL_SofiaPiedad"), "EPL_Prologue");
}

void EPL_Oba_ischezaut(string qName)
{
	ref sld;
	sld = CharacterFromID("EPL_Kotes");
	ChangeCharacterAddressGroup(sld,"none","","");
	sld = CharacterFromID("EPL_Rebekka");
	ChangeCharacterAddressGroup(sld,"none","","");
	LAi_LocationFightDisable(&Locations[FindLocation("LaVega_ExitTown")], false);
}

void EPL_SofiaDlgExit()
{
	ref sld;
	
	sld = CharacterFromID("EPL_SofiaPiedad");
	LAi_CharacterDisableDialog(sld);
	AddQuestRecord("EPL_Prologue", "4");
	
	PChar.quest.EPL_MS_PodskazkaGrot.win_condition.l1 = "location";
	PChar.quest.EPL_MS_PodskazkaGrot.win_condition.l1.location = "Shore32";
	PChar.quest.EPL_MS_PodskazkaGrot.function = "EPL_MS_PodskazkaGrot";
	
	PChar.quest.EPL_Grot.win_condition.l1 = "location";
	PChar.quest.EPL_Grot.win_condition.l1.location = "Hispaniola_Grot";
	PChar.quest.EPL_Grot.function = "EPL_Grot";
	
	pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry6 = 10;
	pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry17 = 5;
	pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry12 = 15;
	pchar.GenQuestBox.Hispaniola_Grot.box1.items.jewelry3 = 10;
	pchar.GenQuestBox.Hispaniola_Grot.box1.items.potionwine = 2;
	pchar.GenQuestBox.Hispaniola_Grot.box1.items.spyglass1 = 1;
	
	QuestPointerDelLoc("LaVega_ExitTown", "reload", "reload1_back");
	QuestPointerToLoc("LaVega_town", "reload", "reload2_back");
	QuestPointerToLoc("LaVega_ExitTown", "reload", "reload3_back");
	QuestPointerToLoc("Hispaniola_jungle_04", "reload", "reload1_back");
	QuestPointerToLoc("Shore32", "reload", "reload2_back");
}

void EPL_MS_PodskazkaGrot(string qName)
{
	AddQuestRecord("EPL_Prologue", "5");
}
void EPL_Grot(string qName)
{
	StartQuestMovie(true, true, true);
	LAi_FadeEx(0.0, 1.0, 1.0, "", "EPL_Grot_2", "");
	LAi_SetActorType(pchar);
	chrDisableReloadToLocation = true;
	
	ref sld;
	sld = CharacterFromID("EPL_Rebekka");
	ChangeCharacterAddressGroup(sld, "Hispaniola_Grot", "goto", "goto4");
}
void EPL_Grot_2(string qName)
{
	LAi_ActorGoToLocator(pchar, "goto", "goto5", "", -1);
	
	locCameraFlyToPositionRotate(-2.78, 4.96, -10.14, 2.00, 3.72, -6.65, 20.0, 40.0, 10.0, 10.0, 0.0, 5.5, 5.5);
	Pchar.FuncCameraFly = "EPL_Grot_3";
}
void EPL_Grot_3()
{
	LAi_SetPlayerType(pchar);
	ref sld;
	sld = CharacterFromID("EPL_Rebekka");
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "Rebekka_v_grote_1";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}
void EPL_Strelba_is_pushki(string qName)
{
	PlaySound("RMM\Gunsfire\Cannon_36_1.wav");
	DoQuestFunctionDelay("EPL_Strelba_is_pushki_2", 1.4);
}
void EPL_Strelba_is_pushki_2(string qName)
{
	PlaySound("RMM\Gunsfire\Cannon_24_3.wav");
	DoQuestFunctionDelay("EPL_Strelba_is_pushki_3", 1.0);
}
void EPL_Strelba_is_pushki_3(string qName)
{
	LAi_SetPlayerType(pchar);
	ref sld;
	sld = CharacterFromID("EPL_Rebekka");
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "Rebekka_v_grote_8";
	//LAi_ActorDialog(sld, pchar, "", 0.0, 0);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}
void EPL_Strelba_is_pushki_4(string qName)
{
	PlaySound("RMM\Gunsfire\Fort_cannon_02.wav");
	DoQuestFunctionDelay("EPL_Strelba_is_pushki_5", 1.4);
}
void EPL_Strelba_is_pushki_5(string qName)
{
	PlaySound("RMM\Gunsfire\Fort_cannon_03.wav");
	DoQuestFunctionDelay("EPL_Strelba_is_pushki_5_5", 1.4);
}
void EPL_Strelba_is_pushki_5_5(string qName)
{
	PlaySound("RMM\Gunsfire\Fort_cannon_04.wav");
	DoQuestFunctionDelay("EPL_Strelba_is_pushki_6", 1.0);
}
void EPL_Strelba_is_pushki_6(string qName)
{
	LAi_SetPlayerType(pchar);
	ref sld;
	sld = CharacterFromID("EPL_Rebekka");
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "Rebekka_v_grote_11";
	//LAi_ActorDialog(sld, pchar, "", 0.0, 0);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}
void EPL_Rebekka_v_grote_DlgExit()
{
	LAi_SetStayType(pchar);
	TavernWaitDateEx(22);
	locCameraSleep(false);
	locCameraFollowEx(true);
	LAi_SetCurHPMax(pchar);
	
	SetLaunchFrameFormParam(StringFromKey("EPL_1_Prologue_dialog_72"), "Run_Function", 0, 3.0);
	SetLaunchFrameRunFunctionParam("EPL_Piraty_v_grote", 0.0);
	LaunchFrameForm();
}

void EPL_Piraty_v_grote()
{
	DoFunctionReloadToLocation("Hispaniola_Grot", "goto", "goto4", "EPL_Piraty_v_grote_1");
}

void EPL_Piraty_v_grote_1()
{
	ref sld;
	int i;
	string sTemp;
	sld = CharacterFromID("EPL_Rebekka");
	ChangeCharacterAddressGroup(sld, "Hispaniola_Grot", "goto", "goto2");
	DoQuestFunctionDelay("EPL_Piraty_v_grote_2", 1.0);
	
	for (i=1; i<=2; i++)
	{
		sTemp = "pirate_"+(rand(15)+1);					
		sld = GetCharacter(NPC_GenerateCharacter("EPL_Piraty_"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		sld.MultiFighter = 0.3;
		if (i==1) ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto1");
		if (i==2) ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1_back");
	}
}
void EPL_Piraty_v_grote_2(string qName)
{
	ref sld;
	sld = CharacterFromID("EPL_Piraty_1");
	LAi_ActorDialog(sld, pchar, "", 2.3, 0);
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "Pirate_v_grote_1";
}
void EPL_Pobeda_v_grote(string qName)
{
	ref sld;
	AddQuestRecord("EPL_Prologue", "6");
	chrDisableReloadToLocation = false;
	
	SetLocationCapturedState("LaVega_town", true);
	locations[FindLocation("LaVega_town")].models.always.locatorsl2 = "LaVega_1_quest";
	locations[FindLocation("LaVega_town")].models.always.locatorsl3 = "LaVega_locators_quest";
	locations[FindLocation("LaVega_town")].models.day.charactersPatch = "LaVega_patch_day_quest";
	locations[FindLocation("LaVega_town")].models.night.charactersPatch = "LaVega_patch_night_quest";
	locations[FindLocation("LaVega_town")].type = "QuestTragic";
	locations[FindLocation("LaVega_town")].locators_radius.patrol.patrol4 = 1.6;
	
	PChar.quest.EPL_tragedia.win_condition.l1 = "location";
	PChar.quest.EPL_tragedia.win_condition.l1.location = "LaVega_town";
	PChar.quest.EPL_tragedia.function = "EPL_tragedia";
	PChar.quest.EPL_Korabl.win_condition.l1 = "location";
	PChar.quest.EPL_Korabl.win_condition.l1.location = "LaVega_ExitTown";
	PChar.quest.EPL_Korabl.function = "EPL_Korabl";
	SetFunctionLocatorCondition("EPL_FortSecret", "LaVega_town", "patrol", "patrol4", false);
	
	QuestPointerDelLoc("LaVega_town", "reload", "reload2_back");
	QuestPointerDelLoc("LaVega_ExitTown", "reload", "reload3_back");
	QuestPointerDelLoc("Hispaniola_jungle_04", "reload", "reload1_back");
	QuestPointerDelLoc("Shore32", "reload", "reload2_back");
	
	QuestPointerToLoc("Hispaniola_Grot", "reload", "reload1_back");
	QuestPointerToLoc("Shore32", "reload", "reload1_back");
	QuestPointerToLoc("Hispaniola_jungle_04", "reload", "reload2_back");
	QuestPointerToLoc("LaVega_ExitTown", "reload", "reload1_back");
}
void EPL_FortSecret(string qName)
{
	notification(StringFromKey("InfoMessages_261"), "X");
	AddCharacterExpToSkill(pchar, "Fortune", 500);
	PlaySound("interface\notebook.wav");
	Achievment_Set(ACH_EPL_SecretInFort);
}
void EPL_tragedia(string qName)
{	
	int i;
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("LaVega_town")], true);
	PlayMusic("Music\Special\Quest\Sorrow of Pardal.mp3", 15000);
	
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J1", "sold_spa_4", "man", "man", 1, SPAIN, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","patrol","patrol8");
	TeleportCharacterToPos(sld, -44.00, 7.80, 51.00);
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J2", "sold_spa_6", "man", "man", 1, SPAIN, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","patrol","patrol5");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J3", "priest_1", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto3");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J4", "trader_6", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto2");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J5", "pirate_4", "man", "man", 1, PIRATE, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto1");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J6", "pirate_13", "man", "man", 1, PIRATE, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","merchant","merchant3");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J7", "Girl_3", "woman", "woman", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","patrol","patrol1");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J8", "sold_spa_1", "man", "man", 1, SPAIN, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto9");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J9", "sold_spa_7", "man", "man", 1, SPAIN, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","officers","reload10_3");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J10", "sold_spa_2", "man", "man", 1, SPAIN, -1, true));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto11");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J11", "shipowner_18", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","reload","houseSp4");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J12", "prison_2", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto10");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J13", "barmen_16", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","patrol","patrol7");
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_J14", "trader_7", "man", "man", 1, SPAIN, -1, false));
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto4");
	
	DoQuestFunctionDelay("EPL_tragedia_2", 1.0);
	
	for (i=1; i<=14; i++)
	{
		sld = CharacterFromID("EPL_J"+i);
		LaunchBlood(sld, 1.0, true, "fight");
		LaunchBlood(sld, 2.0, true, "fight");
		LaunchBlood(sld, 3.0, true, "fight");
		LaunchBlood(sld, 4.0, true, "fight");
		LAi_KillCharacter(sld);
	}
	
	sld = CharacterFromID("EPL_Kotes");
	LAi_LoginInCaptureTown(sld, true);
	LAi_SetStayType(sld);
	LAi_CharacterEnableDialog(sld);
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "Stoim_na_pirse";
	sld.talker = 5;
	ChangeCharacterAddressGroup(sld, "LaVega_town", "officers", "reload1_2");
	TeleportCharacterToPos(sld, -16.34, 1.40, 25.96);
	AddLandQuestMark_Main(CharacterFromID("EPL_Kotes"), "EPL_Prologue");
}
void EPL_tragedia_2(string qName)
{
	ref sld = CharacterFromID("EPL_LaVegaIspanski_Gubernator");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_SetWarriorType(sld);
	LAi_LoginInCaptureTown(sld, true);
	LAi_SetImmortal(sld, false);
	ChangeCharacterAddressGroup(sld,"LaVega_town","patrol","patrol4");
	LaunchBlood(sld, 1.0, true, "fight");
	LAi_KillCharacter(sld);
}
void EPL_Korabl(string qName)
{
	pchar.Ship.Type = GenerateShipExt(SHIP_BARKENTINE, true, pchar);
	pchar.Ship.name = FindPersonalName("EPL_RedBull_ship");
	SetBaseShipData(pchar);
	ChangeCrewExp(pchar, "Sailors", 50);
	ChangeCrewExp(pchar, "Cannoners", 20);
	ChangeCrewExp(pchar, "Soldiers", 20);
	pchar.ship.Crew.Morale = 50;
	SetCharacterGoods(pchar, GOOD_FOOD, 200);
	SetCharacterGoods(pchar, GOOD_RUM, 50 + rand(100));
	SetCharacterGoods(pchar, GOOD_BALLS, 220);
	SetCharacterGoods(pchar, GOOD_BOMBS, 80);
	SetCharacterGoods(pchar, GOOD_POWDER, 240);
	AddCharacterCrew(pchar, -120);
	pchar.ship.HP = sti(pchar.ship.HP) - 450;
	pchar.Ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS16;
	realships[sti(pchar.ship.type)].SpeedRate = 14.0;
	pchar.location.from_sea = "LaVega_town";
	LocatorReloadEnterDisable("LaVega_town", "reload1_back", true);
	setWDMPointXZ("LaVega_town");
	pchar.NoNavyPenalty = true;
}

void EPL_CheckFort()
{
	ref sld;
	
	sld = CharacterFromID("EPL_Kotes");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "rld", "loc0", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_Sandro", "Sandro_Thorne", "man", "man", 18, PIRATE, -1, true));
	sld.name = FindPersonalName("BlueBirdCapitain_name");
	sld.lastname = FindPersonalName("BlueBirdCapitain_lastname");
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto4");
	TeleportCharacterToPosAy(sld, -38.96, 5.00, 55.26, 2.50);
	LAi_SetActorType(sld);
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_Hopkins", "shipowner_1", "man", "man", 10, PIRATE, -1, false));
    sld.name 	= FindPersonalName("Sailor_name");
    sld.lastname 	= FindPersonalName("Sailor_lastname");
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld,"LaVega_town","goto","goto4");
	TeleportCharacterToPosAy(sld, -39.99, 5.00, 54.00, 2.00);
	LAi_SetGroundSitType(sld);
	AddLandQuestMark_Main(sld, "EPL_Prologue");
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "EPL_Hopkins_1";
}

void EPL_SandroDialog()
{
	ref sld;
	
	sld = CharacterFromID("EPL_Sandro");
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "EPL_Sandro_1";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void EPL_GoToShip()
{
	ref sld;
	AddQuestRecord("EPL_Prologue", "7");
	
	sld = CharacterFromID("EPL_Sandro");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocatorFunction(sld, "officers", "reload1_2", "EPL_SandroStay", -1);
	
	sld = CharacterFromID("EPL_Hopkins");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocator(sld, "officers", "reload1_1", "", -1);
	
	sld = CharacterFromID("EPL_Kotes");
	CharacterTurnToLoc(sld, "goto", "goto4");
}

void EPL_SandroStay()
{
	ref sld;
	
	sld = CharacterFromID("EPL_Sandro");
	CharacterTurnToLoc(sld, "goto", "goto4");
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c";
	sld.dialog.currentnode = "EPL_Sandro_11";
	LAi_SetStayType(sld);
	AddLandQuestMark_Main(sld, "EPL_Prologue");
	
	sld = CharacterFromID("EPL_Hopkins");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "officers", "reload1_1", "", -1);
}

void EPL_GoToBoat()
{
	ref sld;
	
	sld = CharacterFromID("EPL_Sandro");
	LAi_SetActorType(sld);
	sld.location = "None";
	
	sld = CharacterFromID("EPL_Hopkins");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", 3);
	sld.location = "None";
	
	sld = CharacterFromID("EPL_Kotes");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", 3);
	sld.location = "None";

	chrDisableReloadToLocation = false;
	bDisableFastReload = true;
	LocatorReloadEnterDisable("LaVega_town", "reload1_back", false);
	
	Island_SetReloadEnableGlobal("Hispaniola1", false);
	Island_SetReloadEnableGlobal("Hispaniola2", false);
	bQuestDisableMapEnter = true;
	pchar.wind.angle = 900.0;
	pchar.worldmapencountersoff = "1";
	
	//Создаём вражеские корабли
	Group_FindOrCreateGroup("EPL_Pir_Attack_1");
	Group_SetType("EPL_Pir_Attack_1", "war");
	sld = GetCharacter(NPC_GenerateCharacter("EPL_1_CaptainAttack_1", "officer_"+(rand(42)+1), "man", "man", 1, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 70, 60, 60, "blade34", "pistol6", 100);
	FantomMakeCoolSailor(sld, SHIP_XebekVML, FindPersonalName("BlueBirdCapitain_ship"), CANNON_TYPE_CULVERINE_LBS16, 80, 60, 70);
	Group_AddCharacter("EPL_Pir_Attack_1", "EPL_1_CaptainAttack_1");
	Group_SetGroupCommander("EPL_Pir_Attack_1", "EPL_1_CaptainAttack_1");
	Group_SetTaskAttack("EPL_Pir_Attack_1", PLAYER_GROUP);
	Group_LockTask("EPL_Pir_Attack_1");
	Group_SetAddress("EPL_Pir_Attack_1", "Hispaniola1", "Quest_Ships", "Quest_ship_11");
	LAi_SetHP(sld, 999999.0, 999999.0);
	realships[sti(sld.ship.type)].SpeedRate = 7.0;
	
	Group_FindOrCreateGroup("EPL_Pir_Attack_2");
	Group_SetType("EPL_Pir_Attack_2", "war");
	sld = GetCharacter(NPC_GenerateCharacter("EPL_1_CaptainAttack_2", "officer_"+(rand(42)+1), "man", "man", 1, PIRATE, -1, true));
	FantomMakeCoolSailor(sld, SHIP_FLEUT, "", CANNON_TYPE_CULVERINE_LBS12, 15, 25, 15);
	FantomMakeCoolFighter(sld, 1, 10, 10, "blade2", "", 10);
	Group_AddCharacter("EPL_Pir_Attack_2", "EPL_1_CaptainAttack_2");
	Group_SetGroupCommander("EPL_Pir_Attack_2", "EPL_1_CaptainAttack_2");
	Group_SetTaskAttack("EPL_Pir_Attack_2", PLAYER_GROUP);
	Group_LockTask("EPL_Pir_Attack_2");
	Group_SetAddress("EPL_Pir_Attack_2", "Hispaniola1", "Quest_Ships", "Quest_ship_12");
	realships[sti(sld.ship.type)].SpeedRate = 30.0;
	
	sld = CharacterFromID("EPL_1_CaptainAttack_1");
	AddCharacterCrew(sld, -100);
	sld.ship.HP = sti(sld.ship.HP) - 700;		
	sld = CharacterFromID("EPL_1_CaptainAttack_2");
	AddCharacterCrew(sld, -60);
	sld.ship.HP = sti(sld.ship.HP) - 700;
	
	PChar.quest.EPL_Bejim_ot_piratov.win_condition.l1 = "EnterToSea";
	PChar.quest.EPL_Bejim_ot_piratov.function = "EPL_Bejim_ot_piratov";
	
	QuestPointerDelLoc("Hispaniola_Grot", "reload", "reload1_back");
	QuestPointerDelLoc("Shore32", "reload", "reload1_back");
	QuestPointerDelLoc("Hispaniola_jungle_04", "reload", "reload2_back");
	QuestPointerDelLoc("LaVega_ExitTown", "reload", "reload1_back");
	QuestPointerToLoc("LaVega_town", "reload", "reload1_back");
}

void EPL_Bejim_ot_piratov(string qName)
{
	DoQuestFunctionDelay("EPL_Bejim_ot_piratov_2", 4.0);
	DoQuestFunctionDelay("EPL_Bejim_ot_piratov_3", 200.0);
	DoQuestFunctionDelay("EPL_Bejim_ot_piratov_4", 300.0);
}

void EPL_Bejim_ot_piratov_2(string qName)
{
	AddQuestRecord("EPL_Prologue", "8");
}
void EPL_Bejim_ot_piratov_3(string qName)
{
	ref sld;
	AddQuestRecord("EPL_Prologue", "9");
	
	sld = CharacterFromID("EPL_1_CaptainAttack_2");
	realships[sti(sld.ship.type)].SpeedRate = 7.0;
}
void EPL_Bejim_ot_piratov_4(string qName)
{
	ref sld;
	bQuestDisableMapEnter = false;
	DeleteAttribute(pchar, "questTemp.EPL_Prologue");
	
	PChar.quest.EPL_PrologueEnd.win_condition.l1 = "MapEnter";
	PChar.quest.EPL_PrologueEnd.function = "EPL_PrologueEnd";
	
	QuestPointerDelLoc("LaVega_town", "reload", "reload1_back");
	AddMapQuestMark_Major("SantoDomingo_town", "EPL_Prologue", "");
	
	pchar.wind.speed = 15.0;
	fWeatherSpeed = stf(15.0);
	
	sld = CharacterFromID("EPL_1_CaptainAttack_1");
	realships[sti(sld.ship.type)].SpeedRate = 2.0;
	sld = CharacterFromID("EPL_1_CaptainAttack_2");
	realships[sti(sld.ship.type)].SpeedRate = 2.0;
}
void EPL_PrologueEnd(string qName)
{
	AddQuestRecord("EPL_Prologue", "10");
	ref sld = CharacterFromID("EPL_1_CaptainAttack_1");
	sld.lifeday = 0;
	sld = CharacterFromID("EPL_1_CaptainAttack_2");
	sld.lifeday = 0;
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_DOSD_SpainGuard", "guard_spa_1", "man", "man", 10, SPAIN, -1, true));
	sld.City = "SantoDomingo";
	ChangeCharacterAddressGroup(sld, "SantoDomingo_town", "officers", "Reload3_1");
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true);
	sld.Dialog.Filename = "Quest\EmmanuelPardalLine\EPL_2_DefenseOfSantoDomingo_dialog.c";
	sld.dialog.currentnode = "EPL_DOSD_Officer_u_rezidenta";
	sld.talker = 5;
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	AddLandQuestMark_Main(sld, "EPL_Prologue");
	
	PChar.quest.EPL_DOSD_Start.win_condition.l1 = "location";
	PChar.quest.EPL_DOSD_Start.win_condition.l1.location = "SantoDomingo_town";
	PChar.quest.EPL_DOSD_Start.function = "EPL_DOSD_Start";	
	pchar.questTemp.EPL_DOSD_SwimToSantoDomingo = true;		//Доплыть до Санто-Доминго нужно на глобалке
	
	SetTimerFunction("EPL_DOSD_Timer", 0, 0, 5);		//Таймер провала следующей миссии!!!
}

void EPL_LaVegaReset()
{
	//Восстанавливаем город из пепла
	SetLocationCapturedState("LaVega_town", false);
	SetCaptureTownByNation("LaVega", PIRATE);
	locations[FindLocation("LaVega_town")].models.always.locatorsl2 = "LaVega_1";
	locations[FindLocation("LaVega_town")].models.always.locatorsl3 = "LaVega_locators";
	locations[FindLocation("LaVega_town")].models.day.charactersPatch = "LaVega_patch_day";
	locations[FindLocation("LaVega_town")].models.night.charactersPatch = "LaVega_patch_night";
	locations[FindLocation("LaVega_town")].type = "town";
	locations[FindLocation("LaVega_town")].locators_radius.patrol.patrol4 = 0.5;
	locations[FindLocation("LaVega_town")].locators_radius.merchant.merchant3 = 1.0;
	LAi_LocationFightDisable(&Locations[FindLocation("LaVega_town")], false);
	
	ref sld = CharacterFromID("Edward Mansfield");
	ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
	
	sld = CharacterFromID("LaVega_tavernkeeper");	//Возвращаем тавернщику его родной диалог
	sld.Dialog.Filename = "Common_Tavern.c";
	sld.dialog.currentnode = "First time";
}

void EPL_SandBox()
{
	//Свободная игра
	bDisableFastReload = false;
	bDisableLandEncounters = false;
	DeleteAttribute(pchar, "NoNavyPenalty");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	DeleteAttribute(pchar, "questTemp.EPL_PrologueCitizens");
	DeleteQuestCondition("EPL_FortSecret");
	pchar.worldmapencountersoff = "0";
	DeleteAttribute(&TEV, "captainInTheLSC");
	pchar.model = "Emmanuel_0";
	Characters_RefreshModel(pchar);
	
	ref sld;
	sld = CharacterFromID("EPL_Kotes");
	// sld.Dialog.Filename = "Enc_Officer_dialog.c";
	// sld.quest.meeting = true;
	// Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
	// sld.OfficerWantToGo.DontGo = true;
	// ChangeCharacterReputation(sld, 20);
	// sld.loyality = MAX_LOYALITY;
	// LAi_SetCurHPMax(sld);
	// AddPassenger(pchar, sld, false);
	// SetCharacterRemovable(sld, true);
	// LAi_SetImmortal(sld, false);
	// sld.HalfImmortal = true;
	sld.location = "None";
	// sld.Dialog.CurrentNode = "hired";
	
	sld = CharacterFromID("EPL_DOSD_SpainGuard");
	sld.lifeday = 0;
	sld = CharacterFromID("EPL_SofiaPiedad");
	ChangeCharacterAddressGroup(sld, "none", "", "");
			
	AddSimpleRumour(StringFromKey("EPL_1_Prologue_script_11"), PIRATE, 5, 1);
	AddSimpleRumour(StringFromKey("EPL_1_Prologue_script_12"), SPAIN, 5, 1);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  -- Эммануэль Пардаль --    конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

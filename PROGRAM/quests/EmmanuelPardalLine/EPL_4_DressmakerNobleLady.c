
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Эммануэль Пардаль
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void EPL_PZD_Quest(string qName)
{	
	PChar.quest.EPL_PZD_Start.win_condition.l1 = "location";
	PChar.quest.EPL_PZD_Start.win_condition.l1.location = "Villemstad_town";
	PChar.quest.EPL_PZD_Start.function = "EPL_PZD_Start";
	AddMapQuestMark_Major("Villemstad_town", "EPL_PZD", "");
}

void EPL_PZD_Start(string qName)
{	
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_Pilar", "PilarTernera", "woman", "Danielle", 1, SPAIN, -1, false));
	sld.name = FindPersonalName("EPL_PZD_Pilar_name");
	sld.lastname = FindPersonalName("EPL_PZD_Pilar_lastname");
	LAi_SetImmortal(sld, true);
	LAi_SetCitizenType(sld);
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
	sld.dialog.currentnode = "EPL_PZD_Pilar_1_1";
	sld.talker = 4;
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto30");
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	AddLandQuestMark_Main(sld, "EPL_PZD");

	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_Herineldo", "sold_spa_4", "man", "man", 10, SPAIN, -1, true));
	sld.name = FindPersonalName("EPL_PZD_Herineldo_name");
	sld.lastname = FindPersonalName("EPL_PZD_Herineldo_lastname");
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto30");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, CharacterFromID("EPL_PZD_Pilar"), "", -1);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");

	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_R1", "sold_spa_2", "man", "man", 5, SPAIN, -1, true));
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto30");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, CharacterFromID("EPL_PZD_Pilar"), "", -1);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void EPL_PZD_PilarDlgExit()
{	
	ref sld;
	
	sld = CharacterFromID("EPL_PZD_Pilar");
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	sld.lifeday = 0;
	RemoveLandQuestmark_Main(sld, "EPL_PZD");
	
	sld = CharacterFromID("EPL_PZD_Herineldo");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, CharacterFromID("EPL_PZD_Pilar"), "", -1);
	sld.lifeday = 0;
	
	sld = CharacterFromID("EPL_PZD_R1");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, CharacterFromID("EPL_PZD_Pilar"), "", -1);
	sld.lifeday = 0;
	
	SetQuestHeader("EPL_PZD");
	AddQuestRecord("EPL_PZD", "1");
	LocatorReloadEnterDisable("Villemstad_town", "reload3_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "reloadR2", true);
	
	PChar.quest.EPL_PZD_ProvalMissii.win_condition.l1 = "MapEnter";
	PChar.quest.EPL_PZD_ProvalMissii.function = "EPL_PZD_ProvalMissii";
	
	pchar.questTemp.EPL_PZD_taverna = true;
	pchar.questTemp.EPL_PZD_PU = true;
	AddLandQuestMark_Main(CharacterFromID("Villemstad_tavernkeeper"), "EPL_PZD");
	AddLandQuestMark_Main(CharacterFromID("Villemstad_portman"), "EPL_PZD");
}

void EPL_PZD_ProvalMissii(string qName)
{	
	AddQuestRecord("EPL_PZD", "2");
	CloseQuestHeader("EPL_PZD");
	
	EPL_PZD_Reset();
}

void EPL_PZD_PortUprDialogExit()
{	
	AddQuestRecord("EPL_PZD", "3");
	
	ref sld;
	int i;
	//Сюда ставить матросов у костра
	for (i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_Matros_"+i, "citiz_3"+i, "man", "man", 3, HOLLAND, -1, false));
		LAi_SetLoginTime(sld, 22.0, 3.99);
		LAi_SetGroundSitType(sld);
		LAi_SetImmortal(sld, true);
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		sld.City = "Villemstad";
		LAi_CharacterDisableDialog(sld);
		if (i==1) ChangeCharacterAddressGroup(sld, "Villemstad_town", "sit", "fire1_1");
		else if (i==2)
		{
			sld.name = FindPersonalName("EPL_PZD_Palturs_name");
			sld.lastname = FindPersonalName("EPL_PZD_Palturs_lastname");
			sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
			sld.dialog.currentnode = "EPL_PZD_MatrosUKostra_1";
			ChangeCharacterAddressGroup(sld, "Villemstad_town", "sit", "fire1_2");
			LAi_CharacterEnableDialog(sld);
			AddLandQuestMark_Main(sld, "EPL_PZD");
		}
		else if (i==3) ChangeCharacterAddressGroup(sld, "Villemstad_town", "sit", "fire1_3");
		else if (i==4) ChangeCharacterAddressGroup(sld, "Villemstad_town", "sit", "fire2_1");
	}
}

void EPL_PZD_MatrosUKostra_DlgExit()
{	
	ref sld;
	int i;
	AddQuestRecord("EPL_PZD", "4");
			
	pchar.questTemp.EPL_PZD_Rostovshik = true;
	pchar.questTemp.EPL_PZD_Lavochniki = true;
	pchar.questTemp.EPL_PZD_Bordel = true;
	AddLandQuestMark_Main(CharacterFromID("Villemstad_usurer"), "EPL_PZD");
	AddLandQuestMark_Main(CharacterFromID("Villemstad_hostess"), "EPL_PZD");
	
	for (i=1; i<=4; i++)
	{
		if (CharacterIsAlive("EPL_PZD_Matros_"+i))
		{
			sld = CharacterFromID("EPL_PZD_Matros_"+i);
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
		}
	}
}

void EPL_PZD_BrothelDlgExit()
{	
	pchar.GenQuest.CantRun = true;
	LAi_LocationDisableOfficersGen("Villemstad_town", true);
	LAi_LocationDisableOfficersGen("Villemstad_hall", true);
	TavernWaitDateEx(22);
	DoFunctionReloadToLocation("Villemstad_town", "goto", "goto19", "EPL_PZD_IdemNaKarnaval");
}

void EPL_PZD_IdemNaKarnaval()
{	
	TeleportCharacterToPosAy(pchar, -5.17, 3.0, -4.0, 0.00);
	bDisableFastReload = true;
	pchar.GenQuest.CannotWait = true;
	
	SetFunctionLocatorCondition("EPL_PZD_JoinInResidence", "Villemstad_town", "reload", "reload3_back", false);
	
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
	RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
	pchar.model = "Emmanuel_8Bal";
	Characters_RefreshModel(pchar);
	
	//locations[FindLocation("Villemstad_hall")].models.always.l1 = "residence06";
	locations[FindLocation("Villemstad_hall")].models.always.l1 = "residence06_quest";
	//locations[FindLocation("Villemstad_hall")].models.always.locators = "residence06_locators";
	locations[FindLocation("Villemstad_hall")].models.always.locators = "residence06_quest_locators";
	//locations[FindLocation("Villemstad_hall")].models.day.charactersPatch = "residence06_patch";
	locations[FindLocation("Villemstad_hall")].models.day.charactersPatch = "residence06_quest_patch";
	//locations[FindLocation("Villemstad_hall")].models.night.charactersPatch = "residence06_patch";
	locations[FindLocation("Villemstad_hall")].models.night.charactersPatch = "residence06_quest_patch";
	
	QuestPointerToLoc("Villemstad_town", "reload", "reload3_back");
}

void EPL_PZD_JoinInResidence(string qName)
{	
	DoFunctionReloadToLocation("Villemstad_Hall", "reload", "reload1", "EPL_PZD_Karnaval");
}

void EPL_PZD_Karnaval()
{	
	ref sld;
	chrDisableReloadToLocation = true;
	AddQuestRecord("EPL_PZD", "5");
	QuestPointerDelLoc("Villemstad_town", "reload", "reload3_back");
	
	//Музыкант 1
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_Musicant1", "Musician1", "man", "man", 3, HOLLAND, -1, false));
	LAi_SetSitType(sld);
	sld.nonTable = true;
	LAi_CharacterDisableDialog(sld);
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_hall", "quest", "quest7");
	MakeUnpushable(sld, true);
	
	//Музыкант 2
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_Musicant2", "Musician2", "man", "man", 3, HOLLAND, -1, false));
	LAi_SetSitType(sld);
	sld.nonTable = true;
	LAi_CharacterDisableDialog(sld);
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_hall", "quest", "quest8");
	MakeUnpushable(sld, true);
	
	//Игрок в покер
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_ManBal5", "ManBal5", "man", "man", 3, HOLLAND, -1, false));
	sld.name = FindPersonalName("EPL_PZD_Ruud_name");
	sld.lastname = FindPersonalName("EPL_PZD_Ruud_lastname");
	LAi_SetSitType(sld);
	sld.nonTable = true;
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
	sld.dialog.currentnode = "EPL_PZD_ManBal5";
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_hall", "sit", "sit2");
	MakeUnpushable(sld, true);
	sld.HideNationIcon = true;
	
	//Женщина 1 в углу
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_WomanBal1", "WomanBal1", "woman", "towngirl", 3, SPAIN, -1, false));
	LAi_SetStayType(sld);
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
	sld.dialog.currentnode = "EPL_PZD_WomanBal1";
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_hall", "quest", "quest1");
	MakeUnpushable(sld, true);
	sld.HideNationIcon = true;
	
	//Женщина 2 в углу
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_WomanBal2", "WomanBal2", "woman", "towngirl", 3, SPAIN, -1, false));
	LAi_SetActorType(sld);
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_hall", "quest", "quest2");
	MakeUnpushable(sld, true);
	sld.HideNationIcon = true;
	
	//Мужчина в углу
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_ManBal4", "ManBal4", "man", "man", 3, SPAIN, -1, false));
	sld.name = FindPersonalName("EPL_PZD_Andres_name");
	sld.lastname = FindPersonalName("EPL_PZD_Andres_lastname");
	LAi_SetActorType(sld);
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_hall", "quest", "quest3");
	MakeUnpushable(sld, true);
	sld.HideNationIcon = true;
	
	//Дочь губернатора
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_DochGubera", "WomanBal4", "woman", "towngirl", 3, HOLLAND, -1, false));
	sld.name = FindPersonalName("EPL_PZD_Aletta_name");
	sld.lastname = "";
	LAi_SetStayType(sld);
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
	sld.dialog.currentnode = "EPL_PZD_DochGubera";
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_hall", "quest", "quest4");
	MakeUnpushable(sld, true);
	sld.HideNationIcon = true;
	
	//Мужик разносит напитки
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_Razdatchik", "ManBal1", "man", "man", 3, HOLLAND, -1, false));
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_hall", "goto", "goto3");
	
	//Мужик общается 1
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_ChattyMan1", "ManBal2", "man", "man", 3, HOLLAND, -1, false));
	LAi_SetStayType(sld);
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
	sld.dialog.currentnode = "EPL_PZD_ChattyMan";
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_hall", "quest", "quest5");
	MakeUnpushable(sld, true);
	sld.HideNationIcon = true;
	
	//Мужик общается 2
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_ChattyMan2", "ManBal3", "man", "man", 3, HOLLAND, -1, false));
	LAi_SetActorType(sld);
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_hall", "quest", "quest6");
	MakeUnpushable(sld, true);
	sld.HideNationIcon = true;
	
	//Босс этой качалки
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_GabrielDeSeguensa", "deSeguesa", "man", "man", 10, SPAIN, -1, false));
	sld.name = FindPersonalName("EPL_PZD_Gabriel_name");
	sld.lastname = FindPersonalName("EPL_PZD_Gabriel_lastname");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "barman_look_around", "", 2.9);
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
	sld.dialog.currentnode = "EPL_PZD_GabrielDeSeguensa";
	ChangeCharacterAddressGroup(sld, "Villemstad_hall", "quest", "quest9");
	AddLandQuestMark_Main(sld, "EPL_PZD");
	
	PChar.quest.EPL_PZD_GabrielZnakomstvo.win_condition.l1 = "locator";
	PChar.quest.EPL_PZD_GabrielZnakomstvo.win_condition.l1.location = "Villemstad_hall";
	PChar.quest.EPL_PZD_GabrielZnakomstvo.win_condition.l1.locator_group = "quest";
	PChar.quest.EPL_PZD_GabrielZnakomstvo.win_condition.l1.locator = "quest17";
	PChar.quest.EPL_PZD_GabrielZnakomstvo.function = "EPL_PZD_GabrielZnakomstvo";
}

void EPL_PZD_DochGubera_Dialog(string qName)
{	
	AoP_NPCDialogClear();
	AoP_NPCDialogAddLine("EPL_PZD_DochGubera", StringFromKey("EPL_4_DressmakerNobleLady_script_1"));
	AoP_NPCDialogAddLine("Blaze", "...");
	AoP_NPCDialogLaunchFunction("EPL_PZD_DochGubera", "Blaze", "EPL_PZD_DochGubera_DlgExit");
}

void EPL_PZD_DochGubera_DlgExit(string qName)
{	
	EndQuestMovie();
	locCameraFollowEx(true);
	ref sld = CharacterFromID("EPL_PZD_DochGubera");
	LAi_CharacterDisableDialog(sld);
	AddQuestRecord("EPL_PZD", "7");
}

void EPL_PZD_ChattyMan_MultiDialog(string qName)
{	
	AoP_NPCDialogClear();
	AoP_NPCDialogAddLine("EPL_PZD_ChattyMan1", StringFromKey("EPL_4_DressmakerNobleLady_script_2"));
	AoP_NPCDialogAddLine("EPL_PZD_ChattyMan2", StringFromKey("EPL_4_DressmakerNobleLady_script_3"));
	AoP_NPCDialogAddLine("EPL_PZD_ChattyMan1", StringFromKey("EPL_4_DressmakerNobleLady_script_4"));
	AoP_NPCDialogAddLine("EPL_PZD_ChattyMan2", StringFromKey("EPL_4_DressmakerNobleLady_script_5"));
	AoP_NPCDialogAddLine("EPL_PZD_ChattyMan1", StringFromKey("EPL_4_DressmakerNobleLady_script_6"));
	AoP_NPCDialogAddLine("EPL_PZD_ChattyMan1", StringFromKey("EPL_4_DressmakerNobleLady_script_7"));
	AoP_NPCDialogLaunchFunction("EPL_PZD_ChattyMan1", "EPL_PZD_ChattyMan2", "EPL_PZD_ChattyMan_DlgExit");
}

void EPL_PZD_ChattyMan_DlgExit(string qName)
{	
	EndQuestMovie();
	locCameraFollowEx(true);
	ref sld = CharacterFromID("EPL_PZD_ChattyMan1");
	LAi_CharacterDisableDialog(sld);
}

void EPL_PZD_WomanBal_MultiDialog(string qName)
{	
	AoP_NPCDialogClear();
	AoP_NPCDialogAddLine("EPL_PZD_WomanBal1", StringFromKey("EPL_4_DressmakerNobleLady_script_8"));
	AoP_NPCDialogAddLine("EPL_PZD_WomanBal2", StringFromKey("EPL_4_DressmakerNobleLady_script_9"));
	AoP_NPCDialogAddLine("EPL_PZD_WomanBal1", StringFromKey("EPL_4_DressmakerNobleLady_script_10"));
	AoP_NPCDialogAddLine("EPL_PZD_WomanBal2", StringFromKey("EPL_4_DressmakerNobleLady_script_11"));
	AoP_NPCDialogLaunchFunction("EPL_PZD_WomanBal1", "EPL_PZD_WomanBal2", "EPL_PZD_WomanBal_MultiDialog_2");
}

void EPL_PZD_WomanBal_MultiDialog_2(string qName)
{	
	AoP_NPCDialogClear();
	AoP_NPCDialogAddLine("EPL_PZD_ManBal4", StringFromKey("EPL_4_DressmakerNobleLady_script_12"));
	AoP_NPCDialogLaunchFunction("EPL_PZD_ManBal4", "EPL_PZD_WomanBal2", "EPL_PZD_WomanBal_DlgExit");
}

void EPL_PZD_WomanBal_DlgExit(string qName)
{	
	EndQuestMovie();
	locCameraFollowEx(true);
	ref sld = CharacterFromID("EPL_PZD_WomanBal1");
	LAi_CharacterDisableDialog(sld);
	AddQuestRecord("EPL_PZD", "6");
}

void EPL_PZD_GabrielZnakomstvo(string qName)
{	
	LAi_SetActorType(pchar);
	LAi_FadeEx(1.0, 0.3, 1.0, "EPL_PZD_GabrielZnakomstvo_2", "", "");
}

void EPL_PZD_GabrielZnakomstvo_2(string qName)
{	
	StartQuestMovie(true, false, true);
	ref sld = CharacterFromID("EPL_PZD_GabrielDeSeguensa");
	RemoveLandQuestmark_Main(sld, "EPL_PZD");
	LAi_ActorAnimation(sld, "barman_look_around", "", 2.9);
	locCameraFromToPos(-0.74, 8.81, 42.94, true, 2.00, 7.05, 42.00);
	ChangeCharacterAddressGroup(pchar, "Villemstad_hall", "quest", "quest17");
	DoQuestFunctionDelay("EPL_PZD_Gabriel_Dialog", 1.50);
}

void EPL_PZD_Gabriel_Dialog(string qName)
{	
	AoP_NPCDialogClear();
	
	AoP_NPCDialogAddLine("EPL_PZD_GabrielDeSeguensa", StringFromKey("EPL_4_DressmakerNobleLady_script_13"));
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_4_DressmakerNobleLady_script_14"));
	AoP_NPCDialogAddLine("EPL_PZD_GabrielDeSeguensa", StringFromKey("EPL_4_DressmakerNobleLady_script_15"));
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_4_DressmakerNobleLady_script_16"));
	AoP_NPCDialogAddLine("EPL_PZD_GabrielDeSeguensa", StringFromKey("EPL_4_DressmakerNobleLady_script_17"));
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_4_DressmakerNobleLady_script_18"));
	AoP_NPCDialogAddLine("EPL_PZD_GabrielDeSeguensa", StringFromKey("EPL_4_DressmakerNobleLady_script_19"));
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_4_DressmakerNobleLady_script_28", pchar.name));
	AoP_NPCDialogAddLine("EPL_PZD_GabrielDeSeguensa", StringFromKey("EPL_4_DressmakerNobleLady_script_20", pchar.name, FindPersonalName("Remedios_lastname")));
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_4_DressmakerNobleLady_script_21"));
	AoP_NPCDialogAddLine("EPL_PZD_GabrielDeSeguensa", StringFromKey("EPL_4_DressmakerNobleLady_script_22"));
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_4_DressmakerNobleLady_script_23"));
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_4_DressmakerNobleLady_script_24"));
	AoP_NPCDialogAddLine("EPL_PZD_GabrielDeSeguensa", StringFromKey("EPL_4_DressmakerNobleLady_script_25"));
	AoP_NPCDialogAddLine("Blaze", StringFromKey("EPL_4_DressmakerNobleLady_script_26"));
	AoP_NPCDialogAddLine("EPL_PZD_GabrielDeSeguensa", StringFromKey("EPL_4_DressmakerNobleLady_script_29", pchar.name));
	
	AoP_NPCDialogLaunchFunction("Blaze", "EPL_PZD_GabrielDeSeguensa", "EPL_PZD_Gabriel_DlgExit");
}

void EPL_PZD_Gabriel_DlgExit(string qName)
{	
	EndQuestMovie();
	locCameraFollowEx(true);
	LAi_SetPlayerType(pchar);
	
	AddQuestRecord("EPL_PZD", "8");
			
	ref sld = CharacterFromID("EPL_PZD_GabrielDeSeguensa");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload2_back", "", "", "", "", -1);
	
	sld = CharacterFromID("EPL_PZD_ManBal5");
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
	sld.dialog.currentnode = "EPL_PZD_IgraVKosti";
	AddLandQuestMark_Main(sld, "EPL_PZD");
}

void EPL_PZD_UbiliVremya(string qName)
{	
	WaitDate("", 0, 0, 0, 1, 0);
	AddQuestRecord("EPL_PZD", "9");
	QuestPointerToLoc("Villemstad_hall", "reload", "reload2_back");
	
	PChar.quest.EPL_PZD_Naberejnaya.win_condition.l1 = "locator";
	PChar.quest.EPL_PZD_Naberejnaya.win_condition.l1.location = "Villemstad_hall";
	PChar.quest.EPL_PZD_Naberejnaya.win_condition.l1.locator_group = "reload";
	PChar.quest.EPL_PZD_Naberejnaya.win_condition.l1.locator = "reload2_back";
	PChar.quest.EPL_PZD_Naberejnaya.function = "EPL_PZD_Naberejnaya";
}

void EPL_PZD_Naberejnaya(string qName)
{	
	DoFunctionReloadToLocation("Villemstad_town", "reload", "reloadR2", "EPL_PZD_Naberejnaya_2");
}

void EPL_PZD_Naberejnaya_2()
{	
	QuestPointerDelLoc("Villemstad_hall", "reload", "reload2_back");
	ref sld;
	//Женщина 1 на набережной
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_WomanBal3", "WomanBal3", "woman", "towngirl", 3, HOLLAND, -1, false));
	LAi_SetActorType(sld);
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "quest", "quest7");
	
	//Мужчина 1 на набережной
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_ManBal6", "Youngman_1", "man", "man", 3, HOLLAND, -1, false));
	LAi_SetActorType(sld);
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "quest", "quest8");
	
	//Габриэль на набережной
	sld = CharacterFromID("EPL_PZD_GabrielDeSeguensa");
	LAi_SetStayType(sld);
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
	sld.dialog.currentnode = "EPL_PZD_GabrielDeSeguensa_11";
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "quest", "quest9");
	AddLandQuestMark_Main(sld, "EPL_PZD");
}

void EPL_PZD_VGorod()
{	
	ref sld;
	sld = CharacterFromID("EPL_PZD_GabrielDeSeguensa");
	LAi_SetActorType(sld);
	CharacterTurnByChr(sld, pchar);
	LAi_SetStayType(pchar);
	LAi_FadeEx(1.0, 0.5, 1.0, "EPL_PZD_VGorod_2", "EPL_PZD_VGorod_3", "");
}

void EPL_PZD_VGorod_2(string qName)
{	
	ref sld;
	sld = CharacterFromID("EPL_PZD_GabrielDeSeguensa");

	ChangeCharacterAddressGroup(pchar, PChar.location, "quest", "quest16");
	ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest17");
	
	DeleteAttribute(pchar, "GenQuest.CantRun");
	pchar.model = "Emmanuel_8";
	Characters_RefreshModel(pchar);
}

void EPL_PZD_VGorod_3(string qName)
{	
	ref sld;
	sld = CharacterFromID("EPL_PZD_GabrielDeSeguensa");
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
	sld.dialog.currentnode = "EPL_PZD_GabrielDeSeguensa_15";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void EPL_PZD_GabrielDeSeguensa_DlgExit()
{	
	ref sld;
	LAi_SetPlayerType(pchar);
	sld = CharacterFromID("EPL_PZD_GabrielDeSeguensa");
	LAi_SetCitizenType(sld);
	LAi_CharacterDisableDialog(sld);
	// sld.lifeday = 0;
	sld.location = "None"; // на случай, если пригодится в будущем
	
	PChar.quest.EPL_PZD_VDom.win_condition.l1 = "locator";
	PChar.quest.EPL_PZD_VDom.win_condition.l1.location = "Villemstad_town";
	PChar.quest.EPL_PZD_VDom.win_condition.l1.locator_group = "reload";
	PChar.quest.EPL_PZD_VDom.win_condition.l1.locator = "houseB3";
	PChar.quest.EPL_PZD_VDom.function = "EPL_PZD_VDom";
	QuestPointerToLoc("Villemstad_town", "reload", "houseB3");
}

void EPL_PZD_VDom(string qName)
{	
	DoFunctionReloadToLocation("Villemstad_BigHouse06", "reload", "reload3", "EPL_PZD_VDom2");
}

void EPL_PZD_VDom2()
{	
	QuestPointerDelLoc("Villemstad_town", "reload", "houseB3");
	ref sld;
	//Рабочий
	sld = GetCharacter(NPC_GenerateCharacter("EPL_PZD_shipowner_3", "worker_1", "man", "man", 3, HOLLAND, -1, false));
	LAi_SetActorType(sld);
	LAi_CharacterDisableDialog(sld);
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Villemstad_BigHouse06", "goto", "goto4");
	
	//София де ла Пьедад
	sld = CharacterFromID("EPL_SofiaPiedad");
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
	sld.dialog.currentnode = "EPL_PZD_Sofia_1";
	LAi_SetStayType(sld);
	LAi_CharacterEnableDialog(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_BigHouse06", "quest", "quest2");
	AddLandQuestMark_Main(sld, "EPL_PZD");
}

void EPL_PZD_Final()
{	
	ref sld;
	sld = CharacterFromID("EPL_SofiaPiedad");
	LAi_SetActorType(sld);
	sld.location = "None";
	
	AddQuestRecord("EPL_PZD", "10");
	CloseQuestHeader("EPL_PZD");
	DeleteQuestCondition("EPL_PZD_ProvalMissii");
	
	AddCharacterExpToSkill(pchar, "Leadership", 150);
	AddCharacterExpToSkill(pchar, "Sneak", 150);
	
	pchar.questTemp.EPL_PZD = "end";
	Achievment_Set(ACH_EPL_DressmakerNobleLady);
	EPL_PZD_Reset();
}

void EPL_PZD_Reset()
{	
	ref sld;
	int i;

	DeleteAttribute(pchar, "GenQuest.CannotWait");
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	LAi_LocationDisableOfficersGen("Villemstad_town", false);
	LAi_LocationDisableOfficersGen("Villemstad_hall", false);
	LocatorReloadEnterDisable("Villemstad_town", "reload3_back", false);
	LocatorReloadEnterDisable("Villemstad_town", "reloadR2", false);			
	DeleteAttribute(pchar, "questTemp.EPL_PZD_Bordel");
	DeleteAttribute(pchar, "questTemp.EPL_PZD_Bordel_2");
	DeleteAttribute(pchar, "questTemp.EPL_PZD_Lavochniki");
	DeleteAttribute(pchar, "questTemp.EPL_PZD_Lavochniki_2");
	DeleteAttribute(pchar, "questTemp.EPL_PZD_Lavochniki_3");
	DeleteAttribute(pchar, "questTemp.EPL_PZD_taverna");
	DeleteAttribute(pchar, "questTemp.EPL_PZD_PU");
	DeleteAttribute(pchar, "questTemp.EPL_PZD_Rostovshik");
	RemoveLandQuestmark_Main(CharacterFromID("Villemstad_tavernkeeper"), "EPL_PZD");
	RemoveLandQuestmark_Main(CharacterFromID("Villemstad_portman"), "EPL_PZD");
	RemoveLandQuestmark_Main(CharacterFromID("Villemstad_usurer"), "EPL_PZD");
	RemoveLandQuestmark_Main(CharacterFromID("Villemstad_hostess"), "EPL_PZD");
	
	for (i=1; i<=4; i++)
	{
		if (CharacterIsAlive("EPL_PZD_Matros_"+i))
		{
			sld = CharacterFromID("EPL_PZD_Matros_"+i);
			sld.lifeday = 0;
			LAi_CharacterDisableDialog(sld);
		}
	}
	
	locations[FindLocation("Villemstad_hall")].models.always.l1 = "residence06";
	//locations[FindLocation("Villemstad_hall")].models.always.l1 = "residence06_quest";
	locations[FindLocation("Villemstad_hall")].models.always.locators = "residence06_locators";
	//locations[FindLocation("Villemstad_hall")].models.always.locators = "residence06_quest_locators";
	locations[FindLocation("Villemstad_hall")].models.day.charactersPatch = "residence06_patch";
	//locations[FindLocation("Villemstad_hall")].models.day.charactersPatch = "residence06_quest_patch";
	locations[FindLocation("Villemstad_hall")].models.night.charactersPatch = "residence06_patch";
	//locations[FindLocation("Villemstad_hall")].models.night.charactersPatch = "residence06_quest_patch";
	RemoveMapQuestMark("Villemstad_town", "EPL_PZD");
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  -- Эммануэль Пардаль --    конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

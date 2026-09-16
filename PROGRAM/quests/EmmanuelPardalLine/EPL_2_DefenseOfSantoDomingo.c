
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Эммануэль Пардаль
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void EPL_DOSD_OpenIsland()
{	
	Island_SetReloadEnableGlobal("Hispaniola1", true);
	Island_SetReloadEnableGlobal("Hispaniola2", true);
	DeleteAttribute(pchar, "questTemp.EPL_DOSD_SwimToSantoDomingo");
}

void EPL_DOSD_Start(string qName)
{	
	EPL_DOSD_OpenExitTown();
	bDisableFastReload = true;
	LocatorReloadEnterDisable("SantoDomingo_town", "Reload1_back", true);	//Не даём выйти из города (квест продолжается)
	LocatorReloadEnterDisable("SantoDomingo_town", "Reload3_back", true);	//Блакируем резиденцию
	DeleteQuestCondition("EPL_DOSD_Timer");					//Если успели в Санто-Доминго, то выключаем таймер
}

void EPL_DOSD_Timer(string qName)
{
	DeleteQuestCondition("EPL_DOSD_Start");
	AddQuestRecord("EPL_Prologue", "11");
	CloseQuestHeader("EPL_Prologue");
	
	EPL_DOSD_OpenExitTown(); //Разблокировать города на Эспаньоле
	EPL_LaVegaReset(); //Восстанавливаем город из пепла
	EPL_SandBox(); //Старт свободной игры
}

void EPL_DOSD_OpenExitTown()
{
	LocatorReloadEnterDisable("SantoDomingo_ExitTown", "reload1_back", false);
	LocatorReloadEnterDisable("PortPax_ExitTown", "reload3", false);
	LocatorReloadEnterDisable("LaVega_town", "reload4_back", false);
	RemoveMapQuestMark("SantoDomingo_town", "EPL_Prologue");
}

void EPL_DOSD_OboronaSD(string qName)
{	
	StartQuestMovie(true, false, true);
	LAi_SetActorType(pchar);
	ChangeCharacterAddressGroup(pchar, "SantoDomingo_ExitTown", "rld", "aloc15");
	chrDisableReloadToLocation = true;
	TavernWaitDateEx(14);
	RecalculateJumpTable();
	RefreshWeather();
	RefreshLandTime();
	
	ref sld;
	int i;
	for (i=1; i<=7; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("EPL_SoldierWithCannon"+i, "sold_spa_"+(rand(7)+1), "man", "man", sti(pchar.rank), SPAIN, 0, true));
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "goto",  "goto12");
		if (i==1) TeleportCharacterToPosAy(sld, 13.07, 4.40, 4.70, -1.50);
		if (i==2) TeleportCharacterToPosAy(sld, 13.07, 4.40, 7.30, -1.50);
		if (i==3) TeleportCharacterToPosAy(sld, 13.07, 4.40, 9.60, -1.50);
		if (i==4) TeleportCharacterToPosAy(sld, 13.75, 4.40, -5.50, -1.50);
		if (i==5) TeleportCharacterToPosAy(sld, 13.75, 4.40, -8.00, -1.50);
		if (i==6) TeleportCharacterToPosAy(sld, 13.45, 4.40, -13.00, -1.50);
		if (i==7) TeleportCharacterToPosAy(sld, 13.45, 4.40, -15.60, -1.50);
	}
	
	LAi_FadeEx(0.0, 1.0, 1.0, "", "EPL_DOSD_OboronaSD_2", "");
}

void EPL_DOSD_OboronaSD_2(string qName)
{	
	KZ|Mute(1);
	locCameraFromToPos(-14.50, 7.00, 0.00, true, 0.22, 2.60, 0.00);
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_3", 1.5);
}

void EPL_DOSD_OboronaSD_3(string qName)
{
	TEV.Music.QuestMusic = "Music\Special\Quest\PDM\Fight_01.mp3";
	PlayMusic(TEV.Music.QuestMusic, 1000);
	
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_4", 1.5);
	
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("EPL_SpaMush_1", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_2");
	LAi_ActorGoToLocator(sld, "rld", "aloc13", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_SpaMush_2", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_3");
	LAi_ActorGoToLocator(sld, "rld", "aloc15", "", -1);
}
void EPL_DOSD_OboronaSD_4(string qName)
{
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_5", 1.5);
	
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("EPL_SpaMush_3", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_2");
	LAi_ActorGoToLocator(sld, "rld", "aloc8", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_SpaMush_4", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_3");
	LAi_ActorGoToLocator(sld, "rld", "aloc11", "", -1);
}
void EPL_DOSD_OboronaSD_5(string qName)
{
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_6", 1.5);
	
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("EPL_SpaMush_5", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_2");
	LAi_ActorGoToLocator(sld, "rld", "aloc7", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_SpaMush_6", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_3");
	LAi_ActorGoToLocator(sld, "rld", "aloc9", "", -1);
}
void EPL_DOSD_OboronaSD_6(string qName)
{
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_7", 1.5);
	
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("EPL_SpaMush_7", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_2");
	LAi_ActorGoToLocator(sld, "rld", "aloc6", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_SpaMush_8", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_3");
	LAi_ActorGoToLocator(sld, "rld", "aloc1", "", -1);
}
void EPL_DOSD_OboronaSD_7(string qName)
{
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_7_1", 4.0);
	
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("EPL_SpaMush_9", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_2");
	LAi_ActorGoToLocator(sld, "rld", "aloc3", "", -1);
	
	sld = GetCharacter(NPC_GenerateCharacter("EPL_SpaMush_10", "spa_mush_"+(rand(2)+1), "man", "mushketer", 3, SPAIN, -1, false));
	sld.MusketerDistance = 0;
	LAi_SetWarriorType(sld);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "officers",  "reload1_3");
	LAi_ActorGoToLocator(sld, "rld", "aloc2", "", -1);
}
void EPL_DOSD_OboronaSD_7_1(string qName)
{
	locCameraFromToPos(7.78, 6.46, 12.21, true, 14.80, 3.15, 4.39);
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_8", 2.0);
}
void EPL_DOSD_OboronaSD_8(string qName)
{
	int i;
	ref sld;
	string sTemp;
	
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_8_1", 2.3);
	locCameraFromToPos(-3.00, 11.30, -26.00, true, 0.27, -0.36, 0.00);
	
	//Пираты 1 волна (#1)
	for (i=1; i<=7; i++)
    {
		sTemp = "pirate_"+(rand(15)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("EPL_Pirate_1_1"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
		LAi_SetActorType(sld);
		sld.CantLoot = true;
		ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc0");
    }
}
void EPL_DOSD_OboronaSD_8_1(string qName)
{
	int i;
	ref sld;
	// DoQuestFunctionDelay("EPL_DOSD_OboronaSD_8_2", 2.2);
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_8_2", 4.0);
	
	for (i=1; i<=7; i++)
    {
		sld = CharacterFromID("EPL_Pirate_1_1"+i);
		// LAi_ActorRunToLocator(sld, "rld", "loc11", "", -1);
		LAi_ActorAttack(sld, CharacterFromID("EPL_SpaMush_1"), "");
	}
	
	//Испанцы мушкетёны
	for (i=1; i<=10; i++)
    {
		sld = CharacterFromID("EPL_SpaMush_"+i);
		CharacterTurnByLoc(sld, "reload", "reload1");
	}
}

void EPL_DOSD_OboronaSD_8_2(string qName)
{
	locCameraFromToPos(3.51, 2.46, 2.41, true, 10.04, 3.82, 5.78);
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_8_3", 2.5);
}
void EPL_DOSD_OboronaSD_8_3(string qName)
{
	CreateLocationParticles("cancloud_fire_big", "effect", "effect2", 0, -90, -10, "");
	SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
	PlaySound("Sea Battles\vistrel_orudiya_004.wav");
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_8_4", 1.2);
	
	
	int i;
	ref sld;
	
	for (i=1; i<=7; i++)
    {
		sld = CharacterFromID("EPL_Pirate_1_1"+i);
		ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc5");
		// ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc1");
		// LAi_SetActorType(sld);
		// LAi_ActorRunToLocator(sld, "rld", "aloc14", "", -1);
	}
}
void EPL_DOSD_OboronaSD_8_4(string qName)
{
	// locCameraFromToPos(-4.15, 3.76, 7.64, true, -10.70, 0.70, 7.60);
	locCameraFromToPos(-2.71, 3.20, 5.71, true, -9.47, 0.33, 5.93);
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_9", 0.3);
}
void EPL_DOSD_OboronaSD_9(string qName)
{
	int i;
	ref sld;
	
	// CreateLocationParticles("shipfire", "rld", "loc6", -3.0, 0, 0, "");
	// CreateLocationParticles("ShipExplode", "rld", "loc6", 0, 0, 0, "boom");
	// CreateLocationParticles("blast", "rld", "loc6", 0, 0, 0, "boom");
	CreateLocationParticles("shipfire", "rld", "loc11", -3.0, 0, 0, "");
	CreateLocationParticles("ShipExplode", "rld", "loc11", 0, 0, 0, "boom");
	CreateLocationParticles("blast", "rld", "loc11", 0, 0, 0, "boom");
	SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
	PlayVoice("Sea Battles\sdavl_kriki_002.wav");
	PlaySound("Sea Battles\vsriv_orud_003.wav");
	
	for (i=1; i<=7; i++)
    {
		sld = CharacterFromID("EPL_Pirate_1_1"+i);
		SetCharacterActionAnimation(sld, "dead", "death_"+(rand(7)+1));
		LAi_KillCharacter(sld);
	}
	
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_9_1", 1.2);
}
void EPL_DOSD_OboronaSD_9_1(string qName)
{
	locCameraFromToPos(3.75, 4.45, -4.60, true, 8.69, 3.52, -7.62);
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_9_2", 1.2);
	
	int i;
	ref sld;
	string sTemp;
	//Пираты 1 волна (#2)
	for (i=1; i<=7; i++)
    {
		sTemp = "pirate_"+(rand(15)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("EPL_Pirate_1_2"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
		sld.CantLoot = true;
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "item",  "flower6");
		CharacterTurnByChr(sld, pchar);
    }
}
void EPL_DOSD_OboronaSD_9_2(string qName)
{
	CreateLocationParticles("cancloud_fire_big", "effect", "effect3", 0, -90, -10, "");
	SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
	PlaySound("Sea Battles\vistrel_orudiya_003.wav");
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_9_3", 1.2);
}
void EPL_DOSD_OboronaSD_9_3(string qName)
{
	CreateLocationParticles("cancloud_fire_big", "effect", "effect4", 0, -90, -10, "");
	SetCameraShake(1.5, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
	PlaySound("Sea Battles\vistrel_orudiya_005.wav");
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_10", 1.5);
}

void EPL_DOSD_OboronaSD_10(string qName)
{
	locCameraFromToPos(-19.22, 4.36, -11.48, true, -26.02, 1.81, -10.68);
	
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_11", 0.2);
}
void EPL_DOSD_OboronaSD_11(string qName)
{
	int i;
	ref sld;
	
	for (i=1; i<=7; i++)
    {
		sld = CharacterFromID("EPL_Pirate_1_2"+i);
		SetCharacterActionAnimation(sld, "dead", "death_"+i);
		LAi_KillCharacter(sld);
	}
	
	CreateLocationParticlesXZ("shipfire", "item",  "flower6", -3.0, 1, 0.5, "");
	CreateLocationParticlesXZ("ShipExplode", "item",  "flower6", 0, 1, 0.5, "boom");
	CreateLocationParticlesXZ("blast", "item",  "flower6", 0, 1, 0.5, "boom");
	SetCameraShake(1.5, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
	PlayVoice("Sea Battles\sdavl_kriki_004.wav");
	PlaySound("Sea Battles\vsriv_orud_003.wav");
	
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_11_1", 1.5);
}
void EPL_DOSD_OboronaSD_11_1(string qName)
{
	CreateLocationParticlesXZ("shipfire", "item",  "flower6", -3.0, -5, 7.5, "");
	CreateLocationParticlesXZ("ShipExplode", "item",  "flower6", 0, -5, 7.5, "boom");
	CreateLocationParticlesXZ("blast", "item",  "flower6", 0, -5, 7.5, "boom");
	SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
	PlaySound("Sea Battles\vsriv_orud_003.wav");
	
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_12", 1.2);
}

void EPL_DOSD_OboronaSD_12(string qName)
{
	locCameraFromToPos(8.17, 2.23, 18.26, true, 5.51, 0.24, 14.36);
	int i;
	ref sld;
	string sTemp;
	
	//Пираты 2 волна (#1)
	for (i=1; i<=7; i++)
    {
		sTemp = "pirate_"+(rand(15)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("EPL_Pirate_2_1"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
		LAi_SetHP(sld, 1.0, 1.0);
		LAi_SetWarriorType(sld);
		sld.CantLoot = true;
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc0");
    }
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "EPL_DOSD_3Volna");
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_13", 3.0);
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_12_1", 7.3);
}
void EPL_DOSD_OboronaSD_12_1(string qName)
{
	int i;
	ref sld;
	
	//Если пираты где-то застряли - добиваем
	for (i=1; i<=7; i++)
    {
		sld = CharacterFromID("EPL_Pirate_2_1"+i);
		LAi_KillCharacter(sld);
	}
	PlaySound("People Fight\MusketFire2.wav");
	PlaySound("People Fight\MusketFire2.wav");
	
}
void EPL_DOSD_OboronaSD_13(string qName)
{
	int i;
	ref sld;
	
	//Испанцы мушкетёны
	for (i=1; i<=10; i++)
    {
		sld = CharacterFromID("EPL_SpaMush_"+i);
		LAi_SetWarriorType(sld);
		sld.CantLoot = true;
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}
void EPL_DOSD_3Volna(string qName)
{
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_14", 1.0);
}
void EPL_DOSD_OboronaSD_14(string qName)
{
	EndQuestMovie();
	locCameraFollowEx(true);
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_15", 1.0);
}
void EPL_DOSD_OboronaSD_15(string qName)
{
	LAi_SetPlayerType(pchar);
	bDisableCharacterMenu = false;
	LAi_SetFightMode(pchar, true);
	
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_16", 1.0);
}
void EPL_DOSD_OboronaSD_16(string qName)
{	
	int i;
	ref sld;
	string sTemp;
	
	//Пираты 3 волна (#1)
	for (i=1; i<=18; i++)
    {
		sTemp = "pirate_"+(rand(15)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("EPL_Pirate_3_1"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc0");
		sld.MultiFighter = 0.6;
    }
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "EPL_DOSD_4Volna");
	
	DoQuestFunctionDelay("MakeQuestAutoSaveDelay", 0.1);
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_17", 1.0);
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_18", 20.0);
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_20", 26.0);
}
void EPL_DOSD_OboronaSD_17(string qName)
{	
	int i;
	ref sld;
	string sTemp;
	
	//Испанцы подкрепление (#1)
	for (i=1; i<=8; i++)
    {
		sTemp = "sold_spa_"+(rand(7)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("EPL_Spa_Guard_"+i, sTemp, "man", "man", 2, SPAIN, -1, true));
		LAi_SetWarriorType(sld);
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "reload",  "reload1_back");
		sld.MultiFighter = 0.8;
    }
}
void EPL_DOSD_OboronaSD_18(string qName)
{	
	int i;
	ref sld;
	string sTemp;
	
	PlaySound("People Fight\MusketFire1.wav");
	PlaySound("People Fight\MusketFire1.wav");
	//Испанцы подкрепление (#2)
	for (i=7; i<=16; i++)
    {
		sTemp = "sold_spa_"+(rand(7)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("EPL_Spa_Guard_"+i, sTemp, "man", "man", 2, SPAIN, -1, true));
		LAi_SetWarriorType(sld);
		sld.lifeday = 0;
		LAi_CharacterDisableDialog(sld);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "reload",  "reload1_back");
		sld.MultiFighter = 0.8;
    }
}
void EPL_DOSD_4Volna(string qName)
{
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_19", 1.0);
}
void EPL_DOSD_OboronaSD_19(string qName)
{	
	int i;
	ref sld;
	string sTemp;
	
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_22", 5.0);
	PlaySound("Interface\_musketshot_0.wav");
	//ПИРАТ БОСС
	sld = GetCharacter(NPC_GenerateCharacter("EPL_Pirate_4", "officer_24", "man", "man", 1, PIRATE, -1, false));
	FantomMakeCoolFighter(sld, 1, 10, 10, "blade12", "pistol6", 60);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc0");
	sld.SaveItemsForDead = true;
	sld.DontChangeBlade = true;
	AddMoneyToCharacter(sld, 3000);
	AddItems(sld, "jewelry5", rand(20)+30);
	AddItems(sld, "jewelry13", rand(5)+15);
	AddItems(sld, "mineral3", 20);
	sld.MultiFighter = 0.75;
	//Пираты 3 волна (#2)
	for (i=1; i<=10; i++)
    {
		sTemp = "pirate_"+(rand(15)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("EPL_Pirate_3_2"+i, sTemp, "man", "man", 1, PIRATE, -1, true));
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld",  "loc0");
		sld.MultiFighter = 0.6;
    }
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("EnemyFight", "EPL_DOSD_OboronaSD_GoodEnd");
}
void EPL_DOSD_OboronaSD_20(string qName)
{
	CreateLocationParticles("ShipExplode", "rld", "loc10", 0, 0, 0, "boom");
	CreateLocationParticles("blast", "rld", "loc10", 0, 0, 0, "boom");
	CreateLocationParticles("cancloud_fire_big", "effect", "effect2", 0, -90, -10, "");
	CreateLocationParticles("Bombard", "effect", "effect2", 0, -90, -10, "");
	SetCameraShake(1.5, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
	PlaySound("Sea Battles\vsriv_orud_003.wav");
	
	DoQuestFunctionDelay("EPL_DOSD_OboronaSD_21", 8.0);
}
void EPL_DOSD_OboronaSD_21(string qName)
{
	CreateLocationParticles("ShipExplode", "rld", "loc13", 0, 0, 0, "boom");
	CreateLocationParticles("blast", "rld", "loc13", 0, 0, 0, "boom");
	CreateLocationParticles("cancloud_fire_big", "effect", "effect3", 0, -90, -10, "");
	CreateLocationParticles("Bombard", "effect", "effect3", 0, -90, -10, "");
	SetCameraShake(1.5, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
	PlaySound("Sea Battles\vsriv_orud_003.wav");
}
void EPL_DOSD_OboronaSD_22(string qName)
{
	CreateLocationParticles("ShipExplode", "rld", "loc15", 0, 0, 0, "boom");
	CreateLocationParticles("blast", "rld", "loc15", 0, 0, 0, "boom");
	CreateLocationParticles("cancloud_fire_big", "effect", "effect2", 0, -90, -10, "");
	CreateLocationParticles("Bombard", "effect", "effect2", 0, -90, -10, "");
	SetCameraShake(1.5, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
	PlaySound("Sea Battles\vsriv_orud_003.wav");
}

void EPL_DOSD_OboronaSD_GoodEnd(string qName)
{
	LAi_group_Delete("EnemyFight");
	TEV.Music.QuestMusic = "Music\Action\Battle\Victory\Victory_teho.ogg";
	PlayMusic(TEV.Music.QuestMusic, 1000);
	ref sld = CharacterFromID("EPL_Kotes");
	LAi_SetCurHPMax(sld);
	LAi_SetStayType(sld);
	ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "reload", "reload1_back");
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_2_DefenseOfSantoDomingo_dialog.c";
	sld.dialog.currentnode = "EPL_DOSD_Koten_1";
	AddLandQuestMark_Main(sld, "EPL_Prologue");
}

void EPL_DOSD_TalkedToMan()
{
	EPL_LaVegaReset(); //Восстанавливаем город из пепла
	EPL_SandBox(); //Старт свободной игры
			
	pchar.questTemp.EPL_DOSD = "WonFight";
	DoQuestReloadToLocation("SantoDomingo_town", "reload", "gate_back", "");
	LocatorReloadEnterDisable("SantoDomingo_town", "Reload3_back", false);
	chrDisableReloadToLocation = false;
	
	ref sld = CharacterFromID("SantoDomingo_Mayor");
	SaveOldDialog(sld);
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_2_DefenseOfSantoDomingo_dialog.c";
	sld.dialog.currentnode = "EPL_DOSD_Gubernator_20";
	
	AddQuestRecord("EPL_Prologue", "13");
	
	QuestPointerDelLoc("SantoDomingo_Admiralty", "reload", "reload1_back");
	QuestPointerDelLoc("SantoDomingo_town", "reload", "gate_back");
	QuestPointerToLoc("SantoDomingo_town", "reload", "reload3_back");
	AddLandQuestMark_Main(CharacterFromID("SantoDomingo_Mayor"), "EPL_Prologue");
}

void EPL_DOSD_Final()
{
	RemoveLandQuestMark_Main(CharacterFromID("SantoDomingo_Mayor"), "EPL_Prologue");
	CloseQuestHeader("EPL_Prologue");
	pchar.questTemp.EPL_DOSD = "Final";
}



/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  -- Эммануэль Пардаль --    конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

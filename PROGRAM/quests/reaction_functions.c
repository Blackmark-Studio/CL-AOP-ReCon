/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  разное с оптимизации   начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//==> грабители Остина Sinistra
void Birglars_fight(string qName)
{
	if (GetCharacterIndex("Berglar" + pchar.quest.(qName).city) != -1)
	{
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);
		string sTemp = "berglar" + pchar.quest.(qName).city;
		pchar.questTemp.tugs.(sTemp) = "over";
		ref sld = characterFromId("Berglar" + pchar.quest.(qName).city);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 2.0, 0);
	}
}
/*void Birglars_Time(string qName)
{
	AddQuestRecord("BerglarsGang", "15");
	//CloseQuestHeader("BerglarsGang"); не закрываем, т.к. есть другие встречи. Konstrush
}
*///<== грабители Остина Sinistra

//==> грабители Остина willdam
void Birglars_Time(string qName) // удаление квеста Остина и всех остинцев в случае неявки на встречу или отказа в диалоге
{
	DeleteAttribute(pchar, "questTemp.tugs"); // удаляем базу квеста
	pchar.questTemp.tugs.berglarState = 0; // обнуляем счетчик во избежание глюков
	// --> удаляем всех остинцев, без разницы, кто жив, кто погиб, так как встречи с ними могут быть в произвольном порядке
	ref sld = characterFromId("BerglarSentJons");
	sld.lifeday = 0;
	RemoveMapQuestMark("SentJons_town", "BerglarsGang");
	sld = characterFromId("BerglarFortFrance");
	sld.lifeday = 0;
	RemoveMapQuestMark("FortFrance_town", "BerglarsGang");
	sld = characterFromId("BerglarMarigo");
	sld.lifeday = 0;
	RemoveMapQuestMark("Marigo_town", "BerglarsGang");
	sld = characterFromId("BerglarPanama");
	sld.lifeday = 0;
	RemoveMapQuestMark("Panama_town", "BerglarsGang");
	sld = characterFromId("BerglarCartahena");
	sld.lifeday = 0;
	RemoveMapQuestMark("Cartahena_town", "BerglarsGang");
	sld = characterFromId("BerglarSantaCatalina");
	sld.lifeday = 0;
	RemoveMapQuestMark("SantaCatalina_town", "BerglarsGang");
	// <-- удаляем всех остинцев, без разницы, кто жив, кто погиб, так как встречи с ними могут быть в произвольном порядке
	if (CheckAttribute(pchar, "questTemp.OstinDelete"))
	{
		AddQuestRecord("BerglarsGang", "16"); // запись на случай неправильного ответа в диалоге
	}
	else
	{
		AddQuestRecord("BerglarsGang", "15"); // запись на случай провала квеста при неявке на встречу
	}
	CloseQuestHeader("BerglarsGang"); // квест в архив
}
//<== грабители Остина willdam

//освободить флаг на дачу миниквестов
void SmallQuests_free(string qName)
{
	pchar.questTemp.different = "free";
}
//вернуть тип губернаторов обратно в sit после боевки
void MayorSitBack(string qName) 
{
	int iTemp = GetCharacterIndex(Pchar.quest.MayorSitBack.mayorId);
	if (iTemp > 0)
	{
		ref sld = &characters[iTemp];
		sld.location = Pchar.quest.MayorSitBack.locationName;
		sld.location.group = "sit";
		sld.location.locator = Pchar.quest.MayorSitBack.locatorName;
		LAi_SetHuberTypeNoGroup(sld);
		RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
		RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	}
}

void Ascold_fightInsideTemple(string qName)
{
	if (MOD_SKILL_ENEMY_RATE > 5) chrDisableReloadToLocation = true;
	characters[GetCharacterIndex("Ascold")].dialog.currentnode = "Ascold_KilledTemple";
	AddQuestRecord("Ascold", "11");
	AddQuestUserData("Ascold", "sSex", GetSexPhrase("","а"));
	AddLandQuestmark_Main(CharacterFromID("Ascold"), "Ascold");
    //--------------------------- испанцы ------------------------------
	LAi_group_Delete("EnemyFight");
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
 	ref sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_off", "elite_spa_1", "man", "man", Rank, SPAIN, -1, true));
    FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);	
	LAi_SetActorType(sld);
    LAi_group_MoveCharacter(sld, "EnemyFight");	
	ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto9");
	int i;
	string sTemp;
	for (i=1; i<=8; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+9);
		if (i==12) sTemp = "off_spa_1";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
        FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol3", 50);
		DeleteAttribute(sld, "SuperShooter");
		sld.BreakTmplAndFightGroup = true;
		LAi_SetActorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
    }
    for (i=10; i<=13; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(3)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);		
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
	DoQuestFunctionDelay("Ascold_actorSetWarrior", 3.5);
}

void Ascold_actorSetWarrior(string qName)
{
	int iTemp = GetCharacterIndex("SpaEnemy_off");
	if (iTemp != -1 && !LAi_IsDead(&characters[iTemp])) LAi_SetWarriorTypeNoGroup(&characters[iTemp]);
	for (int i=1; i<=8; i++)
    {
		iTemp = GetCharacterIndex("SpaEnemy_"+i);	
		if (iTemp != -1 && !LAi_IsDead(&characters[iTemp])) LAi_SetWarriorTypeNoGroup(&characters[iTemp]);
	}
}

void Ascold_LeifIsDead(string qName)
{
	LAi_LocationDisableMonstersGen("Guadeloupe_Cave", false); //Снимем монстров здесь
	LocatorReloadEnterDisable("Guadeloupe_Cave", "reload3_back", false);
}

void Ascold_OpenTheGrave(string qName)
{
	StartQuestMovie(true, false, true);
	LAi_FadeEx(1.0, 0.0, 1.0, "", "Ascold_OpenTheGrave_2", "");
}

void Ascold_OpenTheGrave_2(string qName)
{
	locCameraFlyToPositionLookToPoint(-41.42, 2.41, 44.72, -43.81, 2.37, 44.40, -54.07, 2.15, 42.99, -1.0, 10000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("Ascold_OpenTheGrave_3", 3.0);
	DoQuestFunctionDelay("Ascold_OpenTheGrave_4", 7.0);
}

void Ascold_OpenTheGrave_3(string qName)
{
	ref sld = CharacterFromID("VikingDoor");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "open", "", 5.0);
	IgnoreCollision(sld, true);
	PlaySound("StoneDoor_1");
	SetCameraShake(3.0, 4.0, 0.5, 0.1, 0.15, true, false, CAM_EASING_SMOOTH_STEP);
}

void Ascold_OpenTheGrave_4(string qName)
{
	locCameraSleep(false);
	locCameraResetState();
	locCameraFlyToPositionLookToPoint(-50.13, 2.95, 41.27, -50.94, 2.73, 42.12, -55.67, 1.43, 47.12, -1.0, 6000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("Ascold_OpenTheGrave_5", 4.0);
}

void Ascold_OpenTheGrave_5(string qName)
{
	LAi_FadeEx(1.0, 0.0, 1.0, "", "Ascold_OpenTheGrave_6", "");
}

void Ascold_OpenTheGrave_6(string qName)
{
	// удаляем "дверь"
	ref sld = CharacterFromID("VikingDoor");
	sld.LifeDay = 0;

	EndQuestMovie();
	locCameraSleep(false);
	locCameraResetState();
	LAi_SetPlayerType(pchar);
	locCameraFollowEx(true);
}



//AlexBlade > старт квеста Лейфа - переходки между диалогами
void Ascold_Leif_AfterBodyChange(string qName)
{
	ref sld = CharacterFromID("LeifEricson");
	LAi_SetActorType(sld);
	SetActorDialogAny2Pchar(sld.id, "", -1, 1.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

//AlexBlade > квест Лейфа - запуск диалога перед финальной битвой
void Ascold_LeifLastWord(string qName)
{
	ref sld = CharacterFromID("LeifEricson");
	LAi_SetActorType(sld);
	LAi_SetActorType(pchar);

	LAi_ActorWaitDialog(pchar, sld);

	LAi_ActorDialogNow(sld, pchar, "", -1);
//    locCameraFromToPos(-49.9, 2.25, 44.1, true, -56.0, 0.5, 45.1);
    locCameraFromToAngle(-49.9, 2.25, 44.1, true, -0.025, -1.385);
}

void Ascold_LeifGiveMeFog_Prepare(string qName)
{
	TEV.AscoldLeif_SetMists = true;
}

void Ascold_LeifGiveMeFog(string qName)
{
	chrDisableReloadToLocation = true;
	
	DoQuestFunctionDelay("Ascold_LeifGiveMeFog_Step1", 2.0);
}

void Ascold_LeifGiveMeFog_Step1(string qName)
{
	Log_Clear();
	LAi_SetActorTypeNoGroup(pchar);
	LAi_ActorStay(pchar);
	StartActorSelfDialog("Leif_MisteryMists");
}

void Ascold_LeifGiveMeFog_End()
{
	chrDisableReloadToLocation = false;
}

void Ascold_LeifTakeAwayFog(string qName)
{
	DeleteAttribute(&TEV, "AscoldLeif_SetMists");
}

void Ascold_FreeAzzy_SetQuestMarks(bool isSet)
{
    for (int i=0; i<MAX_COLONIES; i++)
    {
        if (!CheckAttribute(&colonies[i], "nation")) continue;
        if (colonies[i].nation == "none") continue; // необитайки
        if (sti(colonies[i].nation) == PIRATE) continue;

        int iChar = GetCharacterIndex(colonies[i].id + "_Shipyarder");
        if (iChar != -1)
        {
            if(isSet)
            {
                AddLandQuestmark_Main_WithCondition(&Characters[iChar], "Ascold", "Ascold_FreeAzzy_QuestMarkCondition");
            }
            else
            {
                RemoveLandQuestmark_Main(&Characters[iChar], "Ascold");
            }
        }

        iChar = GetCharacterIndex(colonies[i].id + "_Priest");
        if (iChar != -1)
        {
            if(isSet)
            {
                AddLandQuestmark_Main_WithCondition(&Characters[iChar], "Ascold", "Ascold_FreeAzzy_QuestMarkCondition");
            }
            else
            {
                RemoveLandQuestmark_Main(&Characters[iChar], "Ascold");
            }
        }
    }
}

void Ascold_FreeAzzy_AddQuestMarks()
{
    Ascold_FreeAzzy_SetQuestMarks(true);
}

void Ascold_FreeAzzy_DelQuestMarks()
{
    Ascold_FreeAzzy_SetQuestMarks(false);
}

void DelivLettTortuga_Digress(string qName)
{
	LAi_ActorAnimation(characterFromId("AntonioDeBarras"), "attack_fast_1", "DelivLettTortuga_2KickPhar", 0.8);
}

void SeekIsabella_exitTown(string qName)
{
	ref sld = CharacterFromID("ServantGirl");
	LAi_KillCharacter(sld);
    DeleteAttribute(&locations[FindLocation("Beliz_ExitTown")], "DisableEncounters"); //энкаутеры вернём
	DoQuestCheckDelay("TalkSelf_Quest", 0.1); //диалог сам-на-сам
}

void Fr2Letter_shore22(string qName)
{
    ref sld;
	if (characters[GetCharacterIndex("Bandit_13")].location == "Shore22")
	{
		for (int i=12; i<=13; i++)
		{
			sld = characterFromId("Bandit_"+i);
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		}
		LAi_SetActorType(pchar);
		SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
	}
}

void Isabella_widding(string qName)
{
	pchar.quest.Romantic_Widding_Cancel.over = "yes"; //убираем таймер на вовремя не явлился
	pchar.RomanticQuest = "Widding";
	ref sld = characterFromID("Isabella");
	LAi_SetActorType(pchar);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);	
}

void FrLine_HoverGoOnPrison()
{
    ref sld;
    string sTemp;
    pchar.questTemp.jailCanMove = true; //даем возможность выйти из тюрьмы
    LAi_SetPlayerType(pchar);
    pchar.questTemp.State = "Fr2Letter_SeekProblems";    
    AddQuestRecord("Fra_Line_2_DelivLetter", "3");
    //RestoreTempRemoveParam(pchar, "items");
    pchar.money = pchar.questTemp.money;
    //RestoreEquippedMaps(pchar);
    DeleteAttribute(pchar, "questTemp.money");
    //RefreshEquippedMaps(pchar);
    //==> странных типов помещаем в таверну
    LAi_group_Delete("PeaceGroup");
    FreeSitLocator("Villemstad_tavern", "sit5");
    FreeSitLocator("Villemstad_tavern", "sit6");
    for (int i=12; i<=13; i++)
    {
        if (i==12) sTemp = "sit6";
		else sTemp = "sit5";
        sld = GetCharacter(NPC_GenerateCharacter("Bandit_"+i, "pirate_"+i, "man", "man", 20, FRANCE, 5, true)); //watch_quest_moment
        FantomMakeCoolFighter(sld, 20, 70, 40, BLADE_NORMAL, "pistol3", 70);
        sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
        LAi_SetSitType(sld);
        LAi_group_MoveCharacter(sld, "PeaceGroup");
        LAi_SetCheckMinHP(sld, sti(sld.chr_ai.hp)-1, false, "Fr2Letter_FightAfterShot");
        ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "sit", sTemp);
        AddLandQuestmark_Main(sld, "Fra_Line");
    }
    sld = characterFromID("GoverFantom");
    LAi_SetActorType(sld);
    LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 2.0);
    DoQuestFunctionDelay("FrLine_HoverGoOnPrison_2", 2.5);
    AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
    AddLandQuestmark_Main(CharacterFromID("Villemstad_tavernkeeper"), "Fra_Line");
}

void FrLine_HoverGoOnPrison_2(string qName)
{
	DoReloadCharacterToLocation("Villemstad_prison",  "goto", "goto12");
}

void HL5_portManGiveFleuts()
{
    ref sld;
    pchar.questTemp.State = "ThreeFleutes_toLaVega";
    for (int j=1; j<=3; j++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("Captain_"+j, "merch_"+(rand(14)+1), "man", "man", 15, HOLLAND, -1, true));
        FantomMakeCoolSailor(sld, SHIP_FLEUT, "", CANNON_TYPE_CANNON_LBS20, 40, 35, 25);
        FantomMakeCoolFighter(sld, 15, 10, 10, BLADE_SHORT, "pistol1", 0);
        sld.Ship.Cargo.Goods.Balls = 18;
        sld.Ship.Cargo.Goods.Grapes = 18;
        sld.Ship.Cargo.Goods.Knippels = 18;
        sld.Ship.Cargo.Goods.Bombs = 18;
        sld.Ship.Cargo.Goods.Weapon = 0;
        sld.Ship.Cargo.Goods.Powder = 50;
		sld.CompanionEnemyEnable = false;
		sld.Abordage.Enable = false; // НЕЛЬЗЯ!
		SetShipRemovable(sld, false);
		AddCharacterGoods(sld, GOOD_CLOTHES, 5000);
        AddCharacterGoods(sld, GOOD_FRUITS, 200);
        AddCharacterGoods(sld, GOOD_RUM, 900);
        SetCompanionIndex(pchar, -1, sti(sld.index));
        pchar.GenQuest.StoreGoods.StoreIdx = LaVega_STORE;
        pchar.GenQuest.StoreGoods.HL5_ThreeFleutes = true;
        Pchar.quest.ThreeFleutes_TalkIntoLaVega.win_condition.l1 = "location";
        Pchar.quest.ThreeFleutes_TalkIntoLaVega.win_condition.l1.location = "LaVega_town";
        Pchar.quest.ThreeFleutes_TalkIntoLaVega.win_condition = "ThreeFleutes_TalkIntoLaVega";
    }
}

void SeekShip_Stay(string qName)
{
	ref sld = &characters[sti(pchar.quest.(qName).Idx)];
	LAi_SetStayType(sld);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  разное с оптимизации   конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  шебека Синяя Птица   начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BlueBird_inCavern(string qName)
{
	pchar.questTemp.BlueBird = "seenCarriers";
	DoQuestCheckDelay("TalkSelf_Quest", 0.2); //диалог сам-на-сам
}

void BlueBird_endCaveDialog()
{
	ref sld;
	LAi_SetActorType(pchar);
	LAi_ActorTurnByLocator(pchar, "goto", "goto1");
	string sQuest = "";
	for (int i=0; i<10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Carrier_" + i, GetUniqCarrierModel("carrier_city"), "man", "genres", 35, PIRATE, 0, true));
		sld.gotoGroup = "reload";
		sld.gotoLocator = "reload1_back";
		LAi_SetCarrierType(sld);
		ChangeCharacterAddressGroup(sld, "Bermudes_Cavern", "reload", "reload2");
	}
	DoQuestFunctionDelay("BlueBird_endCaveScript", 33.0);
}

void BlueBird_endCaveScript(string qName)
{
	ref sld;
	LAi_LocationDisableMonstersGen("Bermudes_Cavern", false); //монстров генерить
	LAi_LocationDisableOfficersGen("Bermudes_Cavern", false); //офицеров пускать
	for (int i=0; i<10; i++)
	{
		sld = characterFromId("Carrier_" + i);
		ChangeCharacterAddress(sld, "none", "");
	}
	AddQuestRecord("Xebeca_BlueBird", "6");
	AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("ёл","ла"));
	LAi_SetPlayerType(pchar);
	pchar.questTemp.BlueBird = "toSeaBattle";
	pchar.quest.BlueBird_seaBattle.win_condition.l1 = "location";
	pchar.quest.BlueBird_seaBattle.win_condition.l1.location = "Bermudes";
	pchar.quest.BlueBird_seaBattle.function = "BlueBird_seaBattle";	
}

void BlueBird_seaBattle(string qName) // ребалансим пацана
{
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("BlueBird_Group");
	ref sld = GetCharacter(NPC_GenerateCharacter("BlueBirdCapitain", "Sandro_Thorne", "man", "man", 18, PIRATE, 30, true)); // Сандро Торн Konstrush
	sld.name 	= FindPersonalName("BlueBirdCapitain_name");
	sld.lastname = FindPersonalName("BlueBirdCapitain_lastname");
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "BlueBirdCapitain";
	sld.greeting = "Gr_OliverTrast";
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true;
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "BasicAttack");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "AdvancedAttack");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "Gunman");
	GiveItem2Character(sld, "spyglass3");
	GiveItem2Character(sld, "indian5");
	GiveItem2Character(sld, "jewelry15");
	sld.ship.Crew.Morale = 45;
	ChangeCrewExp(sld, "Sailors", 50);
	ChangeCrewExp(sld, "Cannoners", 45);
	ChangeCrewExp(sld, "Soldiers", 45);
	if (MOD_SKILL_ENEMY_RATE >= 10)
	{
		FantomMakeCoolFighter(sld, 70, 60, 60, "blade34", "pistol6", 100);
		FantomMakeCoolSailor(sld, SHIP_XebekVML, FindPersonalName("BlueBirdCapitain_ship"), CANNON_TYPE_CULVERINE_LBS16, 80, 60, 70);
		SetCharacterPerk(sld, "CriticalShoot");
		SetCharacterPerk(sld, "LongRangeShoot");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Sliding");
		SetCharacterPerk(sld, "LootCollection");
		SetCharacterPerk(sld, "MusketsShoot");
		GiveItem2Character(sld, "incas_collection");
		RemoveItems(sld, "spyglass3", 1);
		GiveItem2Character(sld, "spyglass4");
		EquipCharacterbyItem(sld, "spyglass4");
		sld.ship.Crew.Morale = 75;
		ChangeCrewExp(sld, "Sailors", 100);
		ChangeCrewExp(sld, "Cannoners", 65);
		ChangeCrewExp(sld, "Soldiers", 70);
	}
	else
	{
		FantomMakeSmallSailor(sld, SHIP_XebekVML, FindPersonalName("BlueBirdCapitain_ship"), CANNON_TYPE_CULVERINE_LBS16, 40, 30, 35, 35, 25);
	}

	Group_AddCharacter("BlueBird_Group", "BlueBirdCapitain");
	Group_SetType("BlueBird_Group", "pirate");
	Group_SetGroupCommander("BlueBird_Group", "BlueBirdCapitain");
	string sTemp = "quest_ship_10";
	if (pchar.location.from_sea == "Shore_ship1") sTemp = "quest_ship_8";
	Group_SetAddress("BlueBird_Group", "Bermudes", "quest_ships", sTemp);
	Group_SetTaskAttack("BlueBird_Group", PLAYER_GROUP);
	
	pchar.quest.BlueBird_over_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.BlueBird_over_Sink.win_condition.l1.character = "BlueBirdCapitain";
	pchar.quest.BlueBird_over_Sink.function = "BlueBird_over_Sink";

	pchar.quest.BlueBird_over.win_condition.l1 = "NPC_Death";
	pchar.quest.BlueBird_over.win_condition.l1.character = "BlueBirdCapitain";
	pchar.quest.BlueBird_over.function = "BlueBird_over";

	pchar.quest.BlueBird_DieHard1.win_condition.l1 = "ExitFromLocation"; //перенес из КСП
	pchar.quest.BlueBird_DieHard1.win_condition.l1.location = "Bermudes";
	pchar.quest.BlueBird_DieHard1.function = "BlueBird_DieHard";
	Pchar.quest.BlueBird_DieHard2.win_condition.l1 = "MapEnter";
	pchar.quest.BlueBird_DieHard2.function = "BlueBird_DieHard";
	pchar.quest.BlueBird_DieHard1.win_condition.l1 = "MapEnter";
	pchar.quest.BlueBird_DieHard1.function = "BlueBird_DieHard";
}

void BlueBird_over_Sink(string qName)
{
	pchar.quest.BlueBird_over.over = "yes";
	AddQuestRecord("Xebeca_BlueBird", "7_1");
	AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("","а"));
	BlueBird_NewTrader();
}

void BlueBird_over(string qName)
{
	pchar.quest.BlueBird_over_Sink.over = "yes";
	AddQuestRecord("Xebeca_BlueBird", "7");
	AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("","а"));
	BlueBird_NewTrader();
}

void BlueBird_NewTrader()
{
	pchar.questTemp.BlueBird = "weWon";
	pchar.quest.BlueBird_DieHard1.over  = "yes";
	pchar.quest.BlueBird_DieHard2.over  = "yes";
	
	// Вуазье сбежал, ставим другого торгаша
	ref sld = characterFromId("Pirates_trader");
	sld.name = FindPersonalName("Pirates_trader2_name");
	sld.lastname = FindPersonalName("Pirates_trader2_lastname");
	sld.model = "trader_2";
	LAi_SetOwnerType(sld);
	sld.myselfRumour = AddSimpleRumourCity(StringFromKey("Common_rumours_35"),"Pirates", 30, 3, "");
	AddLandQuestMark_Main(sld, "Xebeca_BlueBird");
	AddLandQuestMark_Main(characterFromId(pchar.questTemp.BlueBird.traiderId), "Xebeca_BlueBird");
}
void BlueBird_DieHard(string qName)
{
	ref sld = characterFromId("BlueBirdCapitain");
	sld.lifeDay = 0;
	group_DeleteGroup("BlueBird_Group");
	pchar.quest.BlueBird_over.over = "yes";
	pchar.quest.BlueBird_DieHard1.over = "yes";
	//pchar.quest.BlueBird_DieHard2.over = "yes";
	AddQuestRecord("Xebeca_BlueBird", "8");
	pchar.questTemp.BlueBird = "DieHard";
	AddLandQuestMark_Main(characterFromId(pchar.questTemp.BlueBird.traiderId), "Xebeca_BlueBird");
}

//возмездие торгашам. нападение на личный флейт торговца
void BlueBird_loginFleut(string qName)
{
	if (GetQuestPastMinutesParam("questTemp.BlueBird") <= 15) 
	{
		LAi_group_Delete("EnemyFight");
		group_DeleteGroup("BlueBird_Group");
		ref sld = GetCharacter(NPC_GenerateCharacter("BlueBirdTrader", "", "man", "man", 20, sti(pchar.questTemp.BlueBird.nation), 30, true));
		sld.dialog.filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "BlueBirdTrader";
		sld.greeting = "CapSinkShip";		
		SetCaptanModelByEncType(sld, "trade");
		FantomMakeCoolSailor(sld, SHIP_FLEUT, pchar.questTemp.BlueBird.Ship.Name, CANNON_TYPE_CANNON_LBS20, 70, 70, 70);
		DeleteAttribute(sld, "SinkTenPercent"); // 08.10.23 Rosarak 
		sld.Ship.Mode = "trade"; //торговец
		sld.DontRansackCaptain = true;
		LAi_group_MoveCharacter(sld, "EnemyFight");
		Group_AddCharacter("BlueBird_Group", "BlueBirdTrader");			
		Group_SetGroupCommander("BlueBird_Group", "BlueBirdTrader");
		Group_SetAddress("BlueBird_Group", pchar.questTemp.BlueBird.Island, "quest_ships", "quest_ship_"+(rand(5)+1));
		Group_SetTaskRunaway("BlueBird_Group", PLAYER_GROUP);
		pchar.questTemp.BlueBird = "attackFleut"; //флаг квеста
		//прерывания на уход из локации
		pchar.Quest.BlueBirdFleut_over1.win_condition.l1 = "Location_Type";
		pchar.Quest.BlueBirdFleut_over1.win_condition.l1.location_type = "town";
		pchar.Quest.BlueBirdFleut_over1.function = "BlueBirdFleut_over";
		pchar.Quest.BlueBirdFleut_over2.win_condition.l1 = "Location_Type";
		pchar.Quest.BlueBirdFleut_over2.win_condition.l1.location_type = "seashore";
		pchar.Quest.BlueBirdFleut_over2.function = "BlueBirdFleut_over";
		Pchar.quest.BlueBirdFleut_over3.win_condition.l1 = "MapEnter";
		pchar.Quest.BlueBirdFleut_over3.function = "BlueBirdFleut_over";
		//прерывание на абордаж
    	pchar.quest.BlueBirdFleut_board.win_condition.l1 = "NPC_death";
    	pchar.quest.BlueBirdFleut_board.win_condition.l1.character = "BlueBirdTrader";
    	pchar.quest.BlueBirdFleut_board.function = "BlueBirdFleut_board";
	}
	else
	{
		AddQuestRecord("Xebeca_BlueBird", "11");
		AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("ел","ла"));
		AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
		DeleteAttribute(pchar, "questTemp.BlueBird.Island");
	}
}

void BlueBirdFleut_over(string qName)
{
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("BlueBird_Group");
	pchar.Quest.BlueBirdFleut_over1.over = "yes";
	pchar.Quest.BlueBirdFleut_over2.over = "yes";
	pchar.Quest.BlueBirdFleut_over3.over = "yes";
	pchar.Quest.BlueBirdFleut_board.over = "yes";
	AddQuestRecord("Xebeca_BlueBird", "12");
	AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("ел","ла"));
	AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
	DeleteAttribute(pchar, "questTemp.BlueBird.Island");
	pchar.questTemp.BlueBird = "returnMoney"; //иначе ивент на слухе не сработает
}
//флейт абордирован, задание выполнено
void BlueBirdFleut_board(string qName)
{
	pchar.Quest.BlueBirdFleut_over1.over = "yes";
	pchar.Quest.BlueBirdFleut_over2.over = "yes";
	pchar.Quest.BlueBirdFleut_over3.over = "yes";
	if(sti(pchar.questTemp.BlueBird.count) == 0) pchar.questTemp.BlueBird.Cities = pchar.questTemp.BlueBird.City;
	else pchar.questTemp.BlueBird.Cities = pchar.questTemp.BlueBird.Cities + "," + pchar.questTemp.BlueBird.City;
	pchar.questTemp.BlueBird.count = sti(pchar.questTemp.BlueBird.count) + 1; //счетчик потопленных флейтов
	if(sti(pchar.questTemp.BlueBird.count) < 5)
	{
		AddQuestRecord("Xebeca_BlueBird", "13");
		AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("ым","ой"));
		AddQuestUserData("Xebeca_BlueBird", "sIsland", XI_ConvertString(pchar.questTemp.BlueBird.Island + "Gen"));
		pchar.questTemp.BlueBird = "returnMoney"; //иначе ивент на слухе не сработает
	}
	else 
	{
		pchar.questTemp.BlueBird = "finish";
		AddQuestRecord("Xebeca_BlueBird", "14");
		AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("","а"));
		AddQuestUserData("Xebeca_BlueBird", "sCity", XI_ConvertString("Colony" + Characters[GetCharacterIndex(pchar.questTemp.BlueBird.traiderId)].city + "Gen"));
		DeleteAttribute(pchar, "questTemp.BlueBird.City");
		DeleteAttribute(pchar, "questTemp.BlueBird.Cities");
		DeleteAttribute(pchar, "questTemp.BlueBird.LastCity");
		AddLandQuestMark_Main(characterFromId(pchar.questTemp.BlueBird.traiderId), "Xebeca_BlueBird");
	}
	DeleteAttribute(pchar, "questTemp.BlueBird.Island");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  шебека Синяя Птица    конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Генератор жемчужного промысла Sharp    начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Sharp_loginNearIsland(string qName)
{	
	if (GetQuestPastMinutesParam("questTemp.Sharp") < 10) 
	{
		ref sld = &characters[GetCharacterIndex("Sharp")];
		LAi_SetCurHPMax(sld);
		sld.nation = pchar.nation; //нация Шарпа всегда как у ГГ
		SetCrewQuantityFull(sld);
		ShipOverhaul(sld);
		SetBaseShipData(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
		Group_AddCharacter("Sharp_Group", "Sharp");			
		Group_SetGroupCommander("Sharp_Group", "Sharp");
		float x, y, z;
		string locator = "";
		// если вышли у мыса Негрил - дадим ближайший локатор
		if (pchar.questTemp.Sharp.Island == "Jamaica" && pchar.location.locator == "reload_3")
		{
			FindIslandLocatorXYZ(pchar.questTemp.Sharp.Island, pchar.location.locator, &x, &y, &z);
			locator = GetSeaQuestShipNearestLocator(GetIslandByID(pchar.questTemp.Sharp.Island), "Quest_ships", x, y, z);
		}
		if (locator == "")
		{
		    locator = "quest_ship_"+(rand(1)+1);
		}
		Group_SetAddress("Sharp_Group", pchar.questTemp.Sharp.Island, "quest_ships", locator);
		Group_SetTaskRunaway("Sharp_Group", PLAYER_GROUP);
		pchar.Quest.Sharp_landOver1.win_condition.l1 = "Location_Type";
		pchar.Quest.Sharp_landOver1.win_condition.l1.location_type = "town";
		pchar.Quest.Sharp_landOver1.function = "Sharp_Over";
		pchar.Quest.Sharp_landOver2.win_condition.l1 = "Location_Type";
		pchar.Quest.Sharp_landOver2.win_condition.l1.location_type = "seashore";
		pchar.quest.Sharp_landOver2.function = "Sharp_Over";
	    Pchar.quest.Sharp_mapOver.win_condition.l1 = "MapEnter";
		pchar.quest.Sharp_mapOver.function = "Sharp_Over";
	}
	else
	{
		AddQuestRecord("SharpPearl", "12");
		AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("","а"));
		CloseQuestHeader("SharpPearl");
		pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
		pchar.questTemp.Sharp.brothelChance = rand(10);
		if (pchar.questTemp.Sharp.SeekSpy == "begin") // первый базар должен быть не в борделе
		{
		    pchar.questTemp.Sharp.brothelChance = 1;
		}
	}
}

void Sharp_Over(string qName)
{
	group_DeleteGroup("Sharp_Group");
	pchar.quest.Sharp_landOver1.over = "yes";
	pchar.quest.Sharp_landOver2.over = "yes";
	pchar.quest.Sharp_mapOver.over = "yes";
	//даем запись в СЖ, если не нашёл Шарпа
	if (pchar.questTemp.Sharp == "toSharp_going")
	{
		AddQuestRecord("SharpPearl", "4");
		CloseQuestHeader("SharpPearl");
		pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
		pchar.questTemp.Sharp.brothelChance = rand(10);
        if (pchar.questTemp.Sharp.SeekSpy == "begin") // первый базар должен быть не в борделе
        {
            pchar.questTemp.Sharp.brothelChance = 1;
        }
	}
}

//------------ жемчужный промысел ----------------
void SeaPearl_login(string qName)
{
	ref sld;
	string sTemp;
	characters[GetCharacterIndex("Sharp")].DeckDialogNode = "NewDeckSharp"; //новая нода на палубу Шарпу
	pchar.quest.SeaPearl_Late.over = "yes";
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("PearlGroup");
	int iTemp = sti(pchar.questTemp.Sharp.PearlAreal.qtyShips);
	Group_FindOrCreateGroup("PearlGroup");
	Group_SetType("PearlGroup", "trade");
	for (int j = 1; j <= iTemp; j++)
	{                
		sTemp = "PearlCapitain_" + j;
		sld = GetCharacter(NPC_GenerateCharacter(sTemp, "merch_"+(rand(14)+1), "man", "man", 10, SPAIN, 30, true)); //TODO: сюда простолюдинов или работников, но нужны портреты
		sld.Ship.Type = GenerateShip(SHIP_TARTANE, false);
		SetRandomNameToShip(sld);
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
//		Fantom_SetBalls(sld, "pirate");
        SetCharacterGoods(sld, GOOD_PINCTADA, 700 + rand(3 * 700));
        sld.Coastal_Captain = true;
		sld.ShipTaskLock = true;
		sld.AlwaysEnemy = true;
//		sld.Abordage.Enable = false;
        sld.AlwaysSurrender = true;
		sld.SinkTenPercent = true; //экономия в АИ шипов
		sld.PearlTartane = true; //тартана ловцов жемчуга, можно грабить
		LAi_group_MoveCharacter(sld, "EnemyFight");
		Group_AddCharacter("PearlGroup", sTemp);
	}
    // ==> стравливание
	Group_SetGroupCommander("PearlGroup", "PearlCapitain_1");			
	Group_SetTaskRunaway("PearlGroup", PLAYER_GROUP);
	Group_SetAddress("PearlGroup", pchar.questTemp.Sharp.PearlAreal.Island, "quest_ships", pchar.questTemp.Sharp.PearlAreal.locator);	
	Group_LockTask("PearlGroup");
	pchar.quest.SeaPearl_DieHard1.win_condition.l1 = "ExitFromLocation";
	pchar.quest.SeaPearl_DieHard1.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
	pchar.quest.SeaPearl_DieHard1.function = "SeaPearl_DieHard";
	Pchar.quest.SeaPearl_DieHard2.win_condition.l1 = "MapEnter";
	pchar.quest.SeaPearl_DieHard2.function = "SeaPearl_DieHard";
}

void SeaPearl_Late(string qName)
{	
	pchar.quest.SeaPearl_login.over = "yes";
	AddQuestRecord("SharpPearl", "9");
	AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("SharpPearl", "iDay", FindDaysString(sti(pchar.questTemp.Sharp.PearlAreal.terms)));
	AddQuestUserData("SharpPearl", "sTarget", GetConvertStr(pchar.questTemp.Sharp.PearlAreal.Shore, "LocLables.txt"));
	pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
	pchar.questTemp.Sharp.brothelChance = rand(10);
	DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
}

void SeaPearl_DieHard(string qName)
{
	group_DeleteGroup("PearlGroup");
	pchar.quest.SeaPearl_DieHard1.over = "yes";
	pchar.quest.SeaPearl_DieHard2.over = "yes";

	if (pchar.questTemp.Sharp == "SeaPearl_success")
	{	//успешное нападение
		AddQuestRecord("SharpPearl", "7");
//		AddQuestUserData("SharpPearl", "iSmall", pchar.questTemp.Sharp.PearlAreal.SmallPearlQty);
//		AddQuestUserData("SharpPearl", "iBig", pchar.questTemp.Sharp.PearlAreal.BigPearlQty);
		AddQuestUserData("SharpPearl", "iQty", pchar.questTemp.Sharp.PearlAreal.PinctadaQty);
	}
	else
	{	//неудачное нападение
		AddQuestRecord("SharpPearl", "8");
		AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("ёл","ла"));
		AddQuestUserData("SharpPearl", "sSex1", GetSexPhrase("","а"));
	}
	pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
	pchar.questTemp.Sharp.brothelChance = rand(10);
	DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
	CloseQuestHeader("SharpPearl");
}

void SeaPearl_FirstTime_login(string qName)
{
	ref sld;
	string sTemp;

	characters[GetCharacterIndex("Sharp")].DeckDialogNode = "NewDeckSharp"; //новая нода на палубу Шарпу
	pchar.quest.SeaPearl_FirstTime_Late.over = "yes";
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("PearlGroup");
	int iTemp = sti(pchar.questTemp.Sharp.PearlAreal.qtyShips);
	Group_FindOrCreateGroup("PearlGroup");
	Group_SetType("PearlGroup", "trade");
	for (int j = 1; j <= iTemp; j++)
	{                
		sTemp = "PearlCapitain_" + j;
		sld = GetCharacter(NPC_GenerateCharacter(sTemp, "merch_"+(rand(14)+1), "man", "man", 10, SPAIN, 30, true)); //TODO: сюда простолюдинов или работников, но нужны портреты
		sld.Ship.Type = GenerateShip(SHIP_TARTANE, false);
		SetRandomNameToShip(sld);
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
//		Fantom_SetBalls(sld, "pirate");
        SetCharacterGoods(sld, GOOD_PINCTADA, 700 + rand(3 * 700));
        sld.Coastal_Captain = true;
		sld.ShipTaskLock = true;
		sld.AlwaysEnemy = true;
//		sld.Abordage.Enable = false;
		sld.AlwaysSurrender = true;
		sld.SinkTenPercent = true; //экономия в АИ шипов
		sld.PearlTartane = true; //тартана ловцов жемчуга, можно грабить
		LAi_group_MoveCharacter(sld, "EnemyFight");
		Group_AddCharacter("PearlGroup", sTemp);

		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	}
    // ==> стравливание
	Group_SetGroupCommander("PearlGroup", "PearlCapitain_1");
	Group_SetTaskRunaway("PearlGroup", PLAYER_GROUP);
	Group_SetAddress("PearlGroup", pchar.questTemp.Sharp.PearlAreal.Island, "quest_ships", pchar.questTemp.Sharp.PearlAreal.locator);
	Group_LockTask("PearlGroup");

    DoQuestFunctionDelay("SeaPearl_FirstTime_login_post", 1.0);

	pchar.quest.SeaPearl_DieHard1.win_condition.l1 = "ExitFromLocation";
	pchar.quest.SeaPearl_DieHard1.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
	pchar.quest.SeaPearl_DieHard1.function = "SeaPearl_FirstTime_DieHard";
	Pchar.quest.SeaPearl_DieHard2.win_condition.l1 = "MapEnter";
	pchar.quest.SeaPearl_DieHard2.function = "SeaPearl_FirstTime_DieHard";
}

void SeaPearl_FirstTime_login_post(string qName)
{
    // Шарп не атакует тартаны
    int islandIdx = FindIsland(pchar.questTemp.Sharp.PearlAreal.Island);
    aref arPlTarget;
    makearef(arPlTarget, Islands[islandIdx].Quest_ships);
    string locatorName = pchar.questTemp.Sharp.PearlAreal.locator;

    Group_SetEnemyToCharacter("PearlGroup", GetMainCharacterIndex());

    Group_SetTaskMove("Sharp_Group", stf(arPlTarget.(locatorName).x), stf(arPlTarget.(locatorName).z));
    Ship_SetTaskDrift(SECONDARY_TASK, GetCharacterIndex("Sharp"));
    Ship_SetTaskMove(PRIMARY_TASK, GetCharacterIndex("Sharp"), stf(arPlTarget.(locatorName).x), stf(arPlTarget.(locatorName).z));
    Group_LockTask("Sharp_Group");

    ref sld = &Characters[GetCharacterIndex("Sharp")];

    Ship_ChangeCharge(sld, GOOD_KNIPPELS);
    sld.ShipCannonChargeType = GOOD_KNIPPELS;


    DoQuestCheckDelay("NationUpdate", 0.3);
    RefreshBattleInterface();
}

void SeaPearl_FirstTime_Late(string qName)
{	
	int i;
	string attrName;
	ref chr;
	aref arOldMapPos;

	chr = CharacterFromID("Sharp");
	if (!bQuestCheckProcessFreeze)
	{
		if (IsEntity(&worldMap))
		{
			PChar.Quest.SeaPearl_FirstTime_Late_01.over = "yes"; // сброс, если уже откладывали
			PChar.Quest.SeaPearl_FirstTime_Late_02.over = "yes";
			pchar.quest.SeaPearl_FirstTime_login.over = "yes";
	       
			makearef(arOldMapPos, worldMap.old);
			WdmPrepareMapForAbordage(arOldMapPos);
			MakeCloneShipDeck(pchar, true); // подмена палубы
			LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], true);
			DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto7");
			ReloadFromWMtoL_complete();
			LAi_LockFightMode(pchar, true);
	        
			ChangeCharacterAddressGroup(chr, "Ship_deck", "goto", "goto8");
			LAi_group_MoveCharacter(chr, "GroupDeck");
			chr.Dialog.CurrentNode = "SharpPearlFirst_Late";
			
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "", 3.0, 0);
	        
			// ==> антураж
			arrayNPCModelHow = 0;
			for (i=1; i<5; i++)
			{
				attrName = "pirate_" + (rand(15)+1);
				Log_TestInfo(attrName);
				chr = GetCharacter(NPC_GenerateCharacter("DeckSailor_"+i, attrName, "man", "man", 15, PIRATE, 1, true));
				SetNPCModelUniq(chr, "pirate", MAN);
				SetFantomParam(chr);
				chr.dialog.Filename = "Sailors_dialog.c";
				LAi_SetWarriorType(chr);
				LAi_SetLoginTime(chr, 0.0, 24.0);
				LAi_SetHP(chr, 100.0, 100.0);
				ChangeCharacterAddressGroup(chr, "Ship_deck", "goto", "goto"+(i+2));
				LAi_group_MoveCharacter(chr, "GroupDeck");
			}
    		pchar.quest.Munity = "";
		}
		else
		{
			if (isLocationFreeForQuests(PChar.location) && !bSeaActive && !LAi_grp_alarmactive)
			{
				if (PlaceCharacter(chr, "goto", "random_must_be_near") != "")
				{
					PChar.Quest.SeaPearl_FirstTime_Late_01.over = "yes";
					PChar.Quest.SeaPearl_FirstTime_Late_02.over = "yes";
					pchar.quest.SeaPearl_FirstTime_login.over = "yes";
	
					chrDisableReloadToLocation = true;

					chr.Dialog.CurrentNode = "SharpPearlFirst_Late";
					LAi_SetActorType(chr);
					LAi_ActorDialog(chr, pchar, "", 2.0, 0);
				}
				else
				{
					PChar.Quest.SeaPearl_FirstTime_Late_02.win_condition.l1 = "ExitFromLocation";
					PChar.Quest.SeaPearl_FirstTime_Late_02.win_condition.l1.Location = PChar.location;
					PChar.Quest.SeaPearl_FirstTime_Late_02.function = "SeaPearl_FirstTime_Late";
					DeleteAttribute(PChar, "Quest.SeaPearl_FirstTime_Late_02.Over");
				}
			}
			else
			{
				if (bSeaActive)
				{
					PChar.Quest.SeaPearl_FirstTime_Late_01.win_condition.l1 = "MapEnter";
					PChar.Quest.SeaPearl_FirstTime_Late_01.function = "SeaPearl_FirstTime_Late";
				}
				else
				{
					PChar.Quest.SeaPearl_FirstTime_Late_02.win_condition.l1 = "ExitFromLocation";
					PChar.Quest.SeaPearl_FirstTime_Late_02.win_condition.l1.Location = PChar.location;
					PChar.Quest.SeaPearl_FirstTime_Late_02.function = "SeaPearl_FirstTime_Late";
					DeleteAttribute(PChar, "Quest.SeaPearl_FirstTime_Late_02.Over");
				}
			}
		}
	}
	else
	{
		// отложим до разморозки (пролет табличек)
		PChar.Quest.SeaPearl_FirstTime_Late_01.win_condition.l1 = "MapEnter";
		PChar.Quest.SeaPearl_FirstTime_Late_01.function = "SeaPearl_FirstTime_Late";
	}
}

void SeaPearl_FirstTime_SharpDuel()
{
	ref chr = CharacterFromID("Sharp");
	bQuestDisableMapEnter = true;
	chr.DontRansackCaptain = true; //fix
	string curIslandId = pchar.questTemp.Sharp.PearlAreal.Island;
	int curIslandIndex = GetCharacterCurrentIsland(Pchar);
	if (curIslandIndex >= 0)
	{
		curIslandId = Islands[curIslandIndex].id;
	}
	TEV.Sharp_FirstTimeDuel_IslandId = curIslandId;
	Island_SetReloadEnableGlobal(curIslandId, false);
	 // ==> стравливание
	chr.nation = PIRATE;
	Group_addCharacter("Sharp_Group", "Sharp");
	Group_SetGroupCommander("Sharp_Group", "Sharp");
	Group_SetTaskAttack("Sharp_Group", PLAYER_GROUP);
	Group_SetPursuitGroup("Sharp_Group", PLAYER_GROUP);
	// Group_SetAddress("Sharp_Group", pchar.questTemp.Sharp.PearlAreal.Island, "quest_ships", pchar.questTemp.Sharp.PearlAreal.locator);
	Group_SetAddress("Sharp_Group", curIslandId, "", "");
	Group_LockTask("Sharp_Group");
			
    // ==> прерывание на убиение эскадры
    pchar.quest.SeaPearl_FirstTime_SharpDuel.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.SeaPearl_FirstTime_SharpDuel.win_condition.l1.group = "Sharp_Group";//какую группу уничтожить
	pchar.quest.SeaPearl_FirstTime_SharpDuel.function = "SeaPearl_FirstTime_SharpDuel_AfterBattle";//это победа

	pchar.quest.SeaPearl_FirstTime_SharpDuel_login.win_condition.l1 = "EnterToSea";
	pchar.quest.SeaPearl_FirstTime_SharpDuel_login.function = "SeaPearl_FirstTime_SharpDuel_login";

	 // сгрузим жемчуг в каюту, если возможно
    if (!CheckAttribute(Pchar, "SystemInfo.CabinType"))
        return;

    int iLoc = FindLocation(Pchar.SystemInfo.CabinType);
    if (iLoc >= 0)
    {
        ref rLoc = &locations[iLoc];

        for (int n = 1; n <= 4; n++)
        {
            string sTemp = "box" + n;

            if (!CheckAttribute(rLoc, sTemp))
                continue;

            aref rBox; makearef(rBox, rLoc.(sTemp));
            int smallPearlRem = GetCharacterItem(pchar, "jewelry12");
            int bigPearlRem = GetCharacterItem(pchar, "jewelry11");
            if (smallPearlRem > 0 || bigPearlRem > 0)
            {
                SeaPearl_FirstTime_TakePearlsFromCharacter(pchar, smallPearlRem, bigPearlRem);

                AddItems(rBox, "jewelry12", smallPearlRem);
                AddItems(rBox, "jewelry11", bigPearlRem);

                Log_Info(StringFromKey("InfoMessages_216"));
            }
            break;
        }
    }
}

void SeaPearl_FirstTime_SharpDuel_login()
{
    // Чтобы Шарп не тупил, пусть нападает сразу
    ref chr = CharacterFromID("Sharp");

    Group_SetEnemyToCharacter("Sharp_Group", GetMainCharacterIndex());
    Group_SetTaskAttack("Sharp_Group", PLAYER_GROUP);
    Group_SetPursuitGroup("Sharp_Group", PLAYER_GROUP);
    Ship_SetTaskAttack(PRIMARY_TASK, sti(chr.index), GetMainCharacterIndex());

    Group_LockTask("Sharp_Group");

    DoQuestCheckDelay("NationUpdate", 0.3);
    RefreshBattleInterface();
}

void SeaPearl_FirstTime_SharpDuel_AfterBattle(string qName)
{
	bQuestDisableMapEnter = false;
	if (CheckAttribute(&TEV, "Sharp_FirstTimeDuel_IslandId"))
	{
		Island_SetReloadEnableGlobal(TEV.Sharp_FirstTimeDuel_IslandId, true);
		DeleteAttribute(&TEV, "Sharp_FirstTimeDuel_IslandId");
	}
	
	DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
	AddQuestRecord("SharpPearl", "19");
	CloseQuestHeader("SharpPearl");
	pchar.questTemp.Sharp = "sharpDead";
}

void SeaPearl_FirstTime_DieHard(string qName)
{
	int i;
	string attrName;
	ref chr;
	aref arOldMapPos;
	string startDialogNode;

	bDisableLandEncounters = true; // защита от энкаунтеров

	chr = CharacterFromID("Sharp");
	if (!bQuestCheckProcessFreeze)
	{
		if (IsEntity(&worldMap))
		{
			PChar.Quest.SeaPearl_DieHard1.over = "yes"; // сброс, если уже откладывали
			PChar.Quest.SeaPearl_DieHard2.over = "yes";
			pchar.quest.SeaPearl_FirstTime_login.over = "yes";
			
			SetCharacterShipLocation(pchar, pchar.questTemp.Sharp.PearlAreal.Shore);
			DoFunctionReloadToLocation(pchar.questTemp.Sharp.PearlAreal.Shore, "reload", "sea", "SeaPearl_FirstTime_AfterPearlDialog");
		}
		else
		{
			if (isLocationFreeForQuests(PChar.location) && !bSeaActive && !LAi_grp_alarmactive)
			{
				if (PlaceCharacter(chr, "goto", "random_must_be_near") != "")
				{
				    bDisableLandEncounters = false; // снимаем защиту

					if (CheckAttribute(pchar, "questTemp.Sharp.PearlAreal.qtyShipsSuc") &&
					    sti(pchar.questTemp.Sharp.PearlAreal.qtyShipsSuc) >= sti(pchar.questTemp.Sharp.PearlAreal.qtyShips) / 3 &&
					    GetSquadronGoods(pchar, GOOD_PINCTADA) >= 700
					 )
					{	//успешное нападение, для первого раза
						startDialogNode = "SharpPearlFirst_Success";
					}
					else
					{	//неудачное нападение
						startDialogNode = "SharpPearlFirst_Late";
					}
					
					group_DeleteGroup("PearlGroup");
					PChar.Quest.SeaPearl_DieHard1.over = "yes";
					PChar.Quest.SeaPearl_DieHard2.over = "yes";
					pchar.quest.SeaPearl_FirstTime_login.over = "yes";
	
					chrDisableReloadToLocation = true;

					chr.Dialog.CurrentNode = startDialogNode;
					LAi_SetActorType(chr);
					LAi_ActorDialog(chr, pchar, "", 2.0, 0);
				}
				else
				{
					PChar.Quest.SeaPearl_DieHard1.win_condition.l1 = "ExitFromLocation";
					PChar.Quest.SeaPearl_DieHard1.win_condition.l1.Location = PChar.location;
					PChar.Quest.SeaPearl_DieHard1.function = "SeaPearl_FirstTime_DieHard";
					DeleteAttribute(PChar, "Quest.SeaPearl_DieHard1.Over");
				}
			}
			else
			{
				PChar.Quest.SeaPearl_DieHard1.win_condition.l1 = "ExitFromLocation";
				PChar.Quest.SeaPearl_DieHard1.win_condition.l1.Location = PChar.location;
				PChar.Quest.SeaPearl_DieHard1.function = "SeaPearl_FirstTime_DieHard";
				DeleteAttribute(PChar, "Quest.SeaPearl_DieHard1.Over");
			}
		}
	}
	else
	{
		// отложим до разморозки (пролет табличек)
		PChar.Quest.SeaPearl_DieHard2.win_condition.l1 = "MapEnter";
		PChar.Quest.SeaPearl_DieHard2.function = "SeaPearl_FirstTime_DieHard";
	}
}

void SeaPearl_FirstTime_AfterPearlDialog()
{
	SeaPearl_FirstTime_DieHard("");
}

void SeaPearl_FirstTime_SharpTakePearls(string qName)
{
	int i, cn;
	ref ch;
	string sTemp, sLoc = Pchar.SystemInfo.CabinType;
	
	int smallPearlRem = sti(pchar.questTemp.Sharp.PearlAreal.SmallPearlQty) - sti(pchar.questTemp.Sharp.PearlAreal.SmallPearlQty.Part);
	int bigPearlRem = sti(pchar.questTemp.Sharp.PearlAreal.BigPearlQty) - sti(pchar.questTemp.Sharp.PearlAreal.BigPearlQty.Part);
	DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
	pchar.questTemp.Sharp.PearlsTaken.Small = smallPearlRem;
	pchar.questTemp.Sharp.PearlsTaken.Big = bigPearlRem;
	
	SeaPearl_FirstTime_TakePearlsFromCharacter(pchar, &smallPearlRem, &bigPearlRem);

	if (smallPearlRem == 0 && bigPearlRem == 0)
	{
		return;
	}
	
	// проверим компаньонов
	for (i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if (cn != -1)
		{
            ch = GetCharacter(cn);
			if (GetShipRemovable(ch) && GetRemovable(ch))  // не трогаем квестовых и ПГГ
			{
			    SeaPearl_FirstTime_TakePearlsFromCharacter(ch, &smallPearlRem, &bigPearlRem);
				if (smallPearlRem == 0 && bigPearlRem == 0)
				{
					return;
				}
			}
		}
	}
	// проверим офицеров
	int psgQty = GetPassengersQuantity(pchar);
	for (i=0; i<psgQty; i++)
	{
		cn = GetPassenger(pchar, i);
		
		if (cn == -1) continue;
		ch = GetCharacter(cn);
		if (GetRemovable(ch)) // квестовых не трогаем
		{
			SeaPearl_FirstTime_TakePearlsFromCharacter(ch, &smallPearlRem, &bigPearlRem);
			if (smallPearlRem == 0 && bigPearlRem == 0)
			{
				return;
			}
		}
	}
	// проверим корабельные сундуки
    for (i = 0; i < 4; i++)
	{
		if (i > 0)
		{
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
		
		ref rLoc = &locations[FindLocation(sLoc)];
		
		for (int n = 1; n <= 4; n++)
		{
			sTemp = "box" + n;
			
			if (!CheckAttribute(rLoc, sTemp))
				continue;
			
			aref rBox; makearef(rBox, rLoc.(sTemp));
			SeaPearl_FirstTime_TakePearlsFromCharacter(rBox, &smallPearlRem, &bigPearlRem);
			if (smallPearlRem == 0 && bigPearlRem == 0)
			{
				return;
			}
		}
	}
}

void SeaPearl_FirstTime_TakePearlsFromCharacter(ref ch, int smallPearlRem, int bigPearlRem)
{
	int smallPearlRemTemp = smallPearlRem;
	int bigPearlRemTemp = bigPearlRem;
	
	if (smallPearlRemTemp - GetCharacterItem(ch, "jewelry12") > 0)
	{
		smallPearlRem -= GetCharacterItem(ch, "jewelry12");
		RemoveItems(ch, "jewelry12", GetCharacterItem(ch, "jewelry12"));
	}
	else
	{
		RemoveItems(ch, "jewelry12", smallPearlRemTemp);
		smallPearlRem = 0;
	}
	
	if (bigPearlRemTemp - GetCharacterItem(ch, "jewelry11") > 0)
	{
		bigPearlRem -= GetCharacterItem(ch, "jewelry11");
		RemoveItems(ch, "jewelry11", GetCharacterItem(ch, "jewelry11"));
	}
	else
	{
		RemoveItems(ch, "jewelry11", bigPearlRemTemp);
		bigPearlRem = 0;
	}
}

void SharpSeekSpy_loginSpy(string qName)
{
	int iTemp = 0;
	if (CheckAttribute(&TEV, "QuestTemp.SharpSeekSpy.againCounter"))
	{
		iTemp = sti(TEV.QuestTemp.SharpSeekSpy.againCounter);
	}
	
	// Если проверка происходит днем, то ставим триггер заново
	if (IsDay())
	{
		pchar.quest.SharpSeekSpy_loginSpy_1.win_condition.l1 = "ExitFromLocation";
		pchar.quest.SharpSeekSpy_loginSpy_1.win_condition.l1.location = pchar.location;
		pchar.quest.SharpSeekSpy_loginSpy_1.function = "SharpSeekSpy_again";
		return;
	}
	
	if (rand(2 - iTemp) == 0 && !IsDay())
	{
		if (CheckAttribute(&TEV, "QuestTemp.SharpSeekSpy.againCounter"))
			DeleteAttribute(&TEV, "QuestTemp.SharpSeekSpy.againCounter");

		chrDisableReloadToLocation = true;
		pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
		LAi_LocationFightDisable(loadedLocation, true); // вместо DoQuestCheckDelay("CanFightCurLocation", 0.0);

		LAi_group_Delete("EnemyFight");
		AddQuestRecord("SharpPearl_SeekSpy", "3");
		ref sld = GetCharacter(NPC_GenerateCharacter("Emillio", "milit_spa_3", "man", "man", 20, SPAIN, 0, true));
		sld.name = FindPersonalName("Emillio_name");
		sld.lastname = FindPersonalName("Emillio_lastname");
		sld.Dialog.Filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "SharpSeekSpy_Emi";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto5");
		AddLandQuestmark_Main(sld, "SharpPearl_SeekSpy");
		ref rCharacter = GetCharacter(NPC_GenerateCharacter("QuestMan_5", "citiz_27", "man", "man", 20, SPAIN, 0, true));
		rCharacter.Dialog.Filename = "Quest\ForAll_dialog.c";
		rCharacter.dialog.currentnode = "SharpSeekSpy_fri";
		LAi_SetActorType(rCharacter);
		LAi_group_MoveCharacter(rCharacter, "EnemyFight");
		ChangeCharacterAddressGroup(rCharacter, pchar.location, "goto", "goto6");
		pchar.questTemp.Sharp.SeekSpy = "inDelNorte";
		pchar.quest.SharpSeekSpy_script.win_condition.l1 = "locator";
		pchar.quest.SharpSeekSpy_script.win_condition.l1.location = "Shore55";
		pchar.quest.SharpSeekSpy_script.win_condition.l1.locator_group = "quest";
		pchar.quest.SharpSeekSpy_script.win_condition.l1.locator = "SharpSeekSpy";
		pchar.quest.SharpSeekSpy_script.function = "SharpSeekSpy_script";
	}
	else
	{
		if (!CheckAttribute(&TEV, "QuestTemp.SharpSeekSpy.againCounter"))
		{
			TEV.QuestTemp.SharpSeekSpy.againCounter = 1;
		}
		else
		{
			TEV.QuestTemp.SharpSeekSpy.againCounter = sti(TEV.QuestTemp.SharpSeekSpy.againCounter) + 1;
		}
		
		SetTimerFunction("SharpSeekSpy_again", 0, 0, 3);
	}
}

void SharpSeekSpy_script(string qName)
{
	if (GetCharacterIndex("Emillio") != -1)
	{
		LAi_ActorTurnToCharacter(characterFromId("QuestMan_5"), pchar);
		ref sld = characterFromId("Emillio");
		sld.dialog.currentnode = "SharpSeekSpy_Emi";
		LAi_ActorDialog(sld, pchar, "", 0, 0);
	}
	else
	{
		pchar.questTemp.Sharp.SeekSpy = "over";
	}
}

void SharpSeekSpy_again(string qName)
{
	pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1 = "location";
	pchar.quest.SharpSeekSpy_loginSpy.win_condition.l1.location = "Shore55";
	pchar.quest.SharpSeekSpy_loginSpy.function = "SharpSeekSpy_loginSpy";	
}

void SharpSeekSpy_caveDialog()
{
	ref sld = characterFromId("QuestMan_5");
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SharpSeekSpy_fri";
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharpSeekSpy_caveDialog_2()
{
	ref sld = characterFromId("Emillio");
	sld.dialog.currentnode = "SharpSeekSpy_Emi_1";
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SharpSeekSpy_caveDialog_3()
{
	LAi_LocationFightDisable(loadedLocation, false);
	ref sld = characterFromId("Emillio");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	sld = characterFromId("QuestMan_5");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

    LAi_SetPlayerType(pchar);
    LAi_SetFightMode(pchar, true);

    pchar.quest.SharpSeekSpy_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.SharpSeekSpy_afterFight.win_condition.l1.character = "Emillio";
    pchar.quest.SharpSeekSpy_afterFight.win_condition.l2 = "NPC_Death";
	pchar.quest.SharpSeekSpy_afterFight.win_condition.l2.character = "QuestMan_5";
	pchar.quest.SharpSeekSpy_afterFight.function = "SharpSeekSpy_afterFight";
}

void SharpSeekSpy_afterFight(string qName)
{
	AddQuestRecord("SharpPearl_SeekSpy", "4");
	pchar.questTemp.Sharp.SeekSpy = "alwaysKnow";
	AddLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl_SeekSpy", "");

	chrDisableReloadToLocation = false;
	if (CheckAttribute(pchar,"GenQuest.CannotWait"))
	    DeleteAttribute(pchar, "GenQuest.CannotWait");

	// pchar.questTemp.Sharp = "seekSharp"; //можно снова поискать Шарпа, upd: Сам нас найдёт через месяц
}

void SeaPearl_SharpSeekSpy_SharpRevenge(string qName)
{
	pchar.questTemp.Sharp = "SharpRevenge";
	
	// Спавним Шарпа
	ref sld = characterFromId("Sharp");
	sld.DontRansackCaptain = true; //fix
	sld.nation = pchar.nation;
	
	SetBaseShipData(sld);
	ShipOverhaul(sld);
	
	string sGroup = "Sharp_Group";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	sld.mapEnc.type = "war";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = FindPersonalName("Sharp_mapEnc");
	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
	Map_CreateCoolWarrior("", sld.id, 8);
	
	//заносим Id кэпа в базу нпс-кэпов
	string sTemp = "Sharp";
	NullCharacter.capitainBase.(sTemp).quest = "Sharp"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = "SharpPearl"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "SharpPearl"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = 8 + 3;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	
	Log_TestInfo("Шарпоносец начал преследовать вас.");
}

void SeaPearl_SharpRevenge_AtLoginSharp(string qName)
{
	bQuestDisableMapEnter = true;
	int iIsland = FindIsland(pchar.location);
	if (iIsland > 0)
	{
		Island_SetReloadEnableGlobal(pchar.location, false);
		TEV.Sharp_SharpRevenge_IslandID = pchar.location;
	}
	
	// angry
	if (CheckAttribute(pchar, "questTemp.Sharp.PearlFirstTimeIsFail"))
	{
		// стравливаем
		ref chr = CharacterFromID("Sharp");
		chr.nation = PIRATE;
		SetCharacterRelationBoth(sti(chr.index), GetMainCharacterIndex(), RELATION_ENEMY);
		UpdateRelations();
		Group_SetTaskAttack("Sharp_Group", PLAYER_GROUP);
		return;
	}
	
	DoQuestFunctionDelay("SeaPearl_SharpRevenge_StartDeckDialogDelay", 2.0);
}

void SeaPearl_SharpRevenge_StartDeckDialogDelay(string qName)
{
	Sea_DeckBoatLoad_ForQuest(sti(pchar.index));
	
	LAi_LocationFightDisable(&Locations[FindLocation("Ship_deck")], true);
	LAi_LockFightMode(pchar, true);
	pchar.quest.Munity = "";
	
	SetEventHandler(EVENT_LOCATION_LOAD, "SeaPearl_SharpRevenge_StartDeckDialog_Event", 1);
}

void SeaPearl_SharpRevenge_StartDeckDialog_Event()
{
	DelEventHandler(EVENT_LOCATION_LOAD, "SeaPearl_SharpRevenge_StartDeckDialog_Event");
	SeaPearl_SharpRevenge_StartDeckDialog("");
}

void SeaPearl_SharpRevenge_StartDeckDialog(string qName)
{
	ref rChr;
	int i;
	string model, ani;
	
	ChangeCharacterAddressGroup(pchar, "Ship_deck", "reload", "reload1");
	LAi_SetPlayerType(pchar);
	
	rChr = CharacterFromID("Sharp");
	ChangeCharacterAddressGroup(rChr, "Ship_deck", "goto", "goto2");
	LAi_group_MoveCharacter(rChr, "GroupDeck");
	rChr.Dialog.CurrentNode = "Sharp_Encounter_1";
	AddLandQuestmark_Main(rChr, "SharpPearl");
	
	LAi_SetStayType(rChr);
	
	// ==> антураж
	// Наши матросы
	for (i = 0; i <= 7; i++)
	{
		model = LAi_GetBoardingModel(pchar, &ani);
		rChr = LAi_CreateFantomCharacterEx(model, ani, "goto", LAi_FindFreeRandomLocator("goto"));
		LAi_NPC_Equip(rChr, sti(pchar.rank), true, true);
		setNewModelToChar(rChr);
		LAi_SetActorType(rChr);
		CharacterTurnToLoc(rChr, "goto", "goto2");
		rChr.LifeDay = 0;
		LAi_group_MoveCharacter(rChr, LAI_GROUP_PLAYER);
	}
	// Ребятки Шарпа
	arrayNPCModelHow = 0;
	for (i=1; i<=3; i++)
	{
		rChr = GetCharacter(NPC_GenerateCharacter("SharpCrewTemp_"+i, "pirate_" + (rand(15)+1), "man", "man", 15, PIRATE, 1, true));
		SetNPCModelUniq(rChr, "pirate", MAN);
		SetFantomParam(rChr);
		LAi_SetLoginTime(rChr, 0.0, 24.0);
		LAi_SetHP(rChr, 100.0, 100.0);
		ChangeCharacterAddressGroup(rChr, "Ship_deck", "goto", "goto2");
		rChr.Dialog.Filename = "Sailors_dialog.c";
		LAi_SetWarriorType(rChr);
		
		LAi_warrior_SetCommander(rChr, CharacterFromID("Sharp"));
		LAi_group_MoveCharacter(rChr, "GroupDeck");
		rChr.LifeDay = 0;
	}
	
	DoQuestFunctionDelay("SeaPearl_SharpRevenge_StartDeckDialog_AddQuestLog", 1.0);
}

void SeaPearl_SharpRevenge_StartDeckDialog_AddQuestLog(string qName)
{
	ReOpenQuestHeader("SharpPearl");
	AddQuestRecord("SharpPearl", "20");
}

void SeaPearl_SharpRevenge_NegotiationSuccessContinue()
{
	LAi_Fade("", "");
	WaitDate("",0,0,0,0,30);
	// Вернем жемчуг
	int smallPearlGiven = 0;
	int bigPearlGiven = 0;
	if (CheckAttribute(pchar, "questTemp.Sharp.PearlsTaken.Small"))
	{
		smallPearlGiven = sti(pchar.questTemp.Sharp.PearlsTaken.Small);
	}
	if (CheckAttribute(pchar, "questTemp.Sharp.PearlsTaken.Big"))
	{
		bigPearlGiven = sti(pchar.questTemp.Sharp.PearlsTaken.Big);
	}
	// AddItemLog(pchar, "jewelry11", its(bigPearlGiven), StringFromKey("InfoMessages_157", its(bigPearlGiven)), "");
	
	AddItems(pchar, "jewelry12", smallPearlGiven);
	AddItems(pchar, "jewelry11", bigPearlGiven);
	
	Log_Info(StringFromKey("InfoMessages_156", its(smallPearlGiven)));
	Log_Info(StringFromKey("InfoMessages_157", its(bigPearlGiven)));
	
	// Продолжим диалог
	ref rChr = CharacterFromID("Sharp");
	LAi_SetActorType(pchar);
	LAi_SetActorType(rChr);
	
	DoQuestFunctionDelay("SeaPearl_SharpRevenge_NegotiationSuccessContinue_DialogDelay", 1.5);
}

void SeaPearl_SharpRevenge_NegotiationSuccessContinue_DialogDelay(string q2Name)
{
	ref rChr = CharacterFromID("Sharp");
	
	SetActorDialogAny2Pchar(rChr.id, "", -1, 1.0);
	LAi_ActorFollow(rChr, pchar, "ActorDialog_Any2Pchar", -1);
}

void SeaPearl_SharpRevenge_AfterSuccessNegotiation()
{
	// очистка
	SeaPearl_SharpRevenge_ReleasePlayer();
	
	PChar.Quest.SeaPearl_SharpRevenge_OnExit.win_condition.l1 = "MapEnter";
	PChar.Quest.SeaPearl_SharpRevenge_OnExit.function = "SeaPearl_SharpRevenge_ExitClear";
	PChar.Quest.SeaPearl_SharpRevenge_OnExit_1.win_condition.l1 = "ExitFromSea";
	PChar.Quest.SeaPearl_SharpRevenge_OnExit_1.function = "SeaPearl_SharpRevenge_ExitClear";

	LAi_LockFightMode(pchar, false);
	LAi_SetPlayerType(pchar);
	ref rChr = CharacterFromID("Sharp");
	LAi_SetActorType(rChr);
	rChr.DeckDialogNode = "DeckSharp_overBad";
	ChangeCharacterAddressGroup(rChr, "none", "", "");
	// Удаляем Шарпа с карты
	Map_ReleaseQuestEncounter(rChr.id);
	group_DeleteGroup("Sharp_Group");
	
	for (int i=1; i<=3; i++)
	{
		int iTemp = GetCharacterIndex("SharpCrewTemp_"+i);
		if (iTemp != -1)
		{
			ChangeCharacterAddressGroup(&Characters[iTemp], "none", "", "");
		}
	}
	
	PChar.quest.Munity = "Deads";
	
	SetTimerFunction("SeaPearl_SharpRevenge_AfterSuccessNegotiation_PlantNewAgent", 0, 1, 0); // зашлем нового инорматора через месяц
	DoQuestFunctionDelay("SeaPearl_SharpRevenge_AfterSuccessNegotiation_AddQuestRecord", 2.0); // запись в СЖ
	
	// выход в море
	Return2SeaAfterCabin();
}

void SeaPearl_SharpRevenge_AfterSuccessNegotiation_AddQuestRecord(string qName)
{
	AddQuestRecord("SharpPearl", "21");
	CloseQuestHeader("SharpPearl");
}

void SeaPearl_SharpRevenge_AfterSuccessNegotiation_PlantNewAgent(string qName)
{
	Log_TestInfo("Шарп внедрил нового информатора в поселения.");
	pchar.questTemp.Sharp = "seekSharp"; // можно снова искать
	
	if (!LAi_IsDead(&Characters[GetCharacterIndex("Sharp")]))
	{
		ref rChr = CharacterFromID("Sharp");
		rChr.DeckDialogNode = "NewDeckSharp"; // новая нода на палубу Шарпу
		rChr.Dialog.CurrentNode = "CitySharp"; // нода суша
		
		pchar.questTemp.Sharp.SeekSpy.NewAgentPlanted = true;
	}
}

void SeaPearl_SharpRevenge_AfterFailureNegotiation()
{
	LAi_LockFightMode(pchar, false);
	LAi_SetPlayerType(pchar);
	ref rChr = CharacterFromID("Sharp");
	rChr.nation = PIRATE;
	LAi_SetActorType(rChr);
	ChangeCharacterAddressGroup(rChr, "none", "", "");
	
	for (int i=1; i<=3; i++)
	{
		int iTemp = GetCharacterIndex("SharpCrewTemp_"+i);
		if (iTemp != -1)
		{
			ChangeCharacterAddressGroup(&Characters[iTemp], "none", "", "");
		}
	}
	
	PChar.quest.Munity = "Deads";
	
	// стравливаем
	PChar.StartBattleAfterDeck = true;
	PChar.StartBattleMainCaptanId = "Sharp";
	PChar.StartBattleEncGroupName = "Sharp_Group";
	
	Return2SeaAfterCabin();
}

void SeaPearl_SharpRevenge_AfterBattle(string qName)
{
	Group_DeleteGroup("Sharp_Group");
	SeaPearl_SharpRevenge_ReleasePlayer();
	
	if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
	{
		pchar.questTemp.Sharp = "sharpDead";
		AddQuestRecord("SharpPearl", "19");
		CloseQuestHeader("SharpPearl");
	}
	else
	{
		pchar.questTemp.Sharp = "Sharp_Prisoner";
		AddQuestRecord("SharpPearl", "22");
		ref rChar = &characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)];
		rChar.id = "Sharp_Prisoner";
		SetCharacterRemovable(rChar, true);
		rChar.Dialog.FileName = "Quest\ForAll_dialog.c";
		rChar.Dialog.CurrentNode = "Sharp_Prisoner";
		AddLandQuestmark_Main(rChar, "SharpPearl");
		AddLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl", "");
		SeaPearl_SpainMayor_AddQuestMarks();
		AddLandQuestmark_Main(CharacterFromID("spa_guber"), "SharpPearl");
		
		// забыли поговорить с пленным, через месяц закроем квест
		SetTimerFunction("SeaPearl_SharpPrisoner_ForgotSpeaking", 0, 1, 0);
	}
}

void SeaPearl_SharpRevenge_ReleasePlayer()
{
	bQuestDisableMapEnter = false;
	if (CheckAttribute(&TEV,"Sharp_SharpRevenge_IslandID"))
	{
		Island_SetReloadEnableGlobal(TEV.Sharp_SharpRevenge_IslandID, true);
		DeleteAttribute(&TEV, "Sharp_SharpRevenge_IslandID");
	}
	
	//чистим базу нпс-кэпов  -->
	DeleteAttribute(&NullCharacter, "capitainBase.Sharp");
	//<-- чистим базу нпс-кэпов
}

void SeaPearl_SharpRevenge_ExitClear(string qName)
{
	pchar.quest.SeaPearl_SharpRevenge_OnExit.over = "yes";
	pchar.quest.SeaPearl_SharpRevenge_OnExit_1.over = "yes";
	pchar.quest.SharpRevengeEncounter_Death.over = "yes";
}

void SeaPearl_SharpPrisoner_ForgotSpeaking()
{
	pchar.questTemp.Sharp = "over_sharpEscape";
	ref rChr = CharacterFromID("Sharp_Prisoner");
	RemoveLandQuestmark_Main(rChr, "SharpPearl");
	ReleasePrisoner(rChr);
	
	if (CheckAttribute(&TEV, "Sharp_Prisoner_DialogChoosen"))
	{
		DeleteAttribute(&TEV, "Sharp_Prisoner_DialogChoosen");
	}
	
	AddQuestRecord("SharpPearl", "25");
	CloseQuestHeader("SharpPearl");
}

void SeaPearl_SharpPrisoner_StartBatter()
{
	chrDisableReloadToLocation = true;
	ref rChr = CharacterFromID("Sharp_Prisoner");
	LAi_SetActorType(pchar);
	
	LAi_SetActorType(rChr);
	LAi_SetImmortal(rChr, true);
	
	if (Get_My_Cabin() == pchar.location) //освобождаем локацию от посторонних
	{
		SetOfficersLocationToNone();
		CompanionSaveTasks();
	}
	
	StartQuestMovie(true, true, true);
	SeaPearl_SharpPrisoner_StartBatter_SetCamera();
	
	DoQuestFunctionDelay("SeaPearl_SharpPrisoner_StartBatter_StartScene", 2.0);
}

void SeaPearl_SharpPrisoner_StartBatterCallBoatswain()
{
	chrDisableReloadToLocation = true;
	LAi_Fade("", "");
	
	// здесь можно сгенерить клона нашего боцмана, если он мужик конечно, а то кулачка не будет работать
	ref rChr = LAi_CreateFantomCharacterEx("citiz_36", "man", "reload", LAi_FindFreeRandomLocator("reload"));
	rChr.id = "_SeaPearlQuest_OurBoatswain";
	LAi_NPC_Equip(rChr, sti(pchar.rank), true, true);
	setNewModelToChar(rChr);
	rChr.Dialog.FileName = "Quest\ForAll_dialog.c";
	rChr.Dialog.CurrentNode = "Sharp_Prisoner_StartBatterByBoatswain";
	
	LAi_SetActorType(rChr);
	LAi_SetActorType(pchar);
	LAi_ActorWaitDialog(pchar, rChr);
	rChr.LifeDay = -1;
	LAi_group_MoveCharacter(rChr, LAI_GROUP_PLAYER);
	
	LAi_ActorDialog(rChr, pchar, "", -1, 0);
}

void SeaPearl_SharpPrisoner_StartBatterByBoatswain()
{
	ref rChr = CharacterFromID("Sharp_Prisoner");
	ref rBoatswainChr = CharacterFromID("_SeaPearlQuest_OurBoatswain");
	
	LAi_Fade("", "");
	
	string _locator = "goto1";
	if (Get_My_Cabin() == pchar.location)
	{
		float to_x, to_y, to_z;
		GetCharacterPos(rChr, &to_x, &to_y, &to_z);
		_locator = LAi_FindNearestFreeLocator("goto", to_x, to_y, to_z);
	}
	TeleportCharacterToLocator(rChr, "goto", _locator);
	TeleportCharacterToLocator(rBoatswainChr, "goto", _locator);
	LAi_ActorTurnToCharacter(rBoatswainChr, rChr);
	
	TeleportCharacterToLocator(pchar, "reload", "reload1");
	
	LAi_SetActorType(rChr);
	LAi_SetImmortal(rChr, true);
	
	if (Get_My_Cabin() == pchar.location) //освобождаем локацию от посторонних
	{
		SetOfficersLocationToNone();
		CompanionSaveTasks();
	}
	
	StartQuestMovie(true, true, true);
	SeaPearl_SharpPrisoner_StartBatter_SetCamera();
	
	LAi_ActorFollow(rBoatswainChr, rChr, "", -1);
	DoQuestFunctionDelay("SeaPearl_SharpPrisoner_StartBatterByBoatswain_StartScene", 2.0);
}

void SeaPearl_SharpPrisoner_StartBatter_SetCamera()
{
	ref rChr = CharacterFromID("Sharp_Prisoner");
	
	float charAY, to_x, to_y, to_z;
	float offsetAY, _offsetX, _offsetY, _offsetZ;
	GetCharacterPos(rChr, &to_x, &to_y, &to_z);
	GetCharacterAy(rChr, &charAY);
	
	_offsetX = -2.5; _offsetZ = 2.5;
	offsetAY = atan2(_offsetZ, _offsetX);
	if(_offsetX > 0 && _offsetZ > 0)
	{
		offsetAY = offsetAY + PI;
	}
	
	locCameraFromToPos(to_x + _offsetX * sin(charAY + stf(offsetAY)), to_y + 2.0, to_z + _offsetZ * cos(charAY + stf(offsetAY)), false, to_x, to_y, to_z);
}

void SeaPearl_SharpPrisoner_StartBatter_StartScene(string qName)
{
	DoQuestFunctionDelay("SeaPearl_SharpPrisoner_StartBatter_EndScene", 10.0);
	
	ref rChr = CharacterFromID("Sharp_Prisoner");
	
	LAi_LocationFightDisable(&Locations[FindLocation(rChr.location)], false);
	Take_Fists();
	
	LAi_SetFightMode(pchar, true);
	LAi_ActorTurnToCharacter(rChr, pchar);
	LAi_ActorAfraid(rChr, pchar, false);
	LAi_tmpl_SetFight(pchar, rChr);
}

void SeaPearl_SharpPrisoner_StartBatterByBoatswain_StartScene(string qName)
{
	DoQuestFunctionDelay("SeaPearl_SharpPrisoner_StartBatterByBoatswain_EndScene", 10.0);
	
	ref rChr = CharacterFromID("Sharp_Prisoner");
	ref rBoatswainChr = CharacterFromID("_SeaPearlQuest_OurBoatswain");
	
	LAi_LocationFightDisable(&Locations[FindLocation(rChr.location)], false);
	SeaPearl_SharpPrisoner_StartBatterByBoatswain_TakeFists();
	
	LAi_SetFightMode(rBoatswainChr, true);
	LAi_ActorTurnToCharacter(rChr, rBoatswainChr);
	LAi_ActorAfraid(rChr, rBoatswainChr, false);
	LAi_tmpl_SetFight(rBoatswainChr, rChr);
}

void SeaPearl_SharpPrisoner_StartBatterByBoatswain_TakeFists()
{
	ref rBoatswainChr = CharacterFromID("_SeaPearlQuest_OurBoatswain");

	RemoveCharacterEquip(rBoatswainChr, BLADE_ITEM_TYPE); //снимаем экипировку
	GiveItem2Character(rBoatswainChr, "unarmed"); //выдаём кулаки
	EquipCharacterByItem(rBoatswainChr, "unarmed");
}

void SeaPearl_SharpPrisoner_StartBatter_EndScene(string qName)
{
	LAi_tmpl_fight_Stop(pchar);
	ref rChr = CharacterFromID("Sharp_Prisoner");
	
	EndQuestMovie();
	locCameraTarget(PChar);
	locCameraFollow();
	
	LAi_SetActorType(PChar);
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	
	LAi_SetImmortal(rChr, false);
	
	if (CheckAttribute(pchar,"equip.blade") && pchar.equip.blade == "unarmed")
		LAi_MethodDelay("Take_Fists_Away", 1.5);
	
	LaunchBlood(rChr, 1.0 + frand(0.6), true, "fight");
	LAi_SetGroundSitTypeNoGroup(rChr);
	
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	
	DoQuestFunctionDelay("SeaPearl_SharpPrisoner_AfterBatter_StartDialog", 1.5);
}

void SeaPearl_SharpPrisoner_StartBatterByBoatswain_EndScene(string qName)
{
	ref rBoatswainChr = CharacterFromID("_SeaPearlQuest_OurBoatswain");
	LAi_tmpl_fight_Stop(rBoatswainChr);
	LAi_SetActorType(rBoatswainChr);
	
	ref rChr = CharacterFromID("Sharp_Prisoner");
	
	EndQuestMovie();
	locCameraTarget(PChar);
	locCameraFollow();
	
	LAi_SetFightMode(rBoatswainChr, false);
	LAi_LockFightMode(rBoatswainChr, true);

	LAi_SetImmortal(rChr, false);
	
	LaunchBlood(rChr, 1.0 + frand(0.6), true, "fight");
	LAi_SetGroundSitTypeNoGroup(rChr);
	
	LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
	
	DoQuestFunctionDelay("SeaPearl_SharpPrisoner_AfterBatterByBoatswain_StartDialog", 1.5);
}

void SeaPearl_SharpPrisoner_AfterBatter_StartDialog(string qName)
{
	ref rChr = CharacterFromID("Sharp_Prisoner");
	
	LAi_ActorDialog(pchar, rChr, "", 1.5, 0);
}

void SeaPearl_SharpPrisoner_AfterBatterByBoatswain_StartDialog(string qName)
{
	LAi_Fade("", "");
	
	ref rBoatswainChr = CharacterFromID("_SeaPearlQuest_OurBoatswain");
	ChangeCharacterAddressGroup(rBoatswainChr, "none", "", "");
	
	ref rChr = CharacterFromID("Sharp_Prisoner");
	
	float to_x, to_y, to_z;
	GetCharacterPos(rChr, &to_x, &to_y, &to_z);
	string _locator = LAi_FindNearestFreeLocator("goto", to_x, to_y, to_z);
	TeleportCharacterToLocator(pchar, "goto", _locator);
	
	LAi_ActorDialog(pchar, rChr, "", 1.5, 0);
}

void SeaPearl_SharpPrisoner_AfterBatter_DialogExit()
{
	chrDisableReloadToLocation = false;
	InterfaceStates.Buttons.Save.enable = true;
	
	LAi_SetPlayerType(pchar);
	
	pchar.questTemp.Sharp = "Sharp_Prisoner_Bargain";
	AddQuestRecord("SharpPearl", "23");
	AddQuestUserData("SharpPearl", "sShoreName", XI_ConvertString("Shore32" + "Gen"));
	AddQuestUserData("SharpPearl", "sIslandName", XI_ConvertString("Hispaniola" + "Pre"));

    RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
    SeaPearl_SpainMayor_DelQuestMarks();
    RemoveLandQuestmark_Main(CharacterFromID("spa_guber"), "SharpPearl");
	
	pchar.quest.SharpPrisoner_GiveFree.win_condition.l1 = "location";
	pchar.quest.SharpPrisoner_GiveFree.win_condition.l1.location = "Hispaniola_Grot";
	pchar.quest.SharpPrisoner_GiveFree.function = "SeaPearl_SharpPrisoner_GiveFree_InGrot_StartDialog";

	pchar.quest.SharpPrisoner_GiveFree_1.win_condition.l1 = "location";
    pchar.quest.SharpPrisoner_GiveFree_1.win_condition.l1.location = "Shore32";
    pchar.quest.SharpPrisoner_GiveFree_1.function = "SeaPearl_SharpPrisoner_GiveFree_NearGrot_StartDialog";
}

void SeaPearl_SharpPrisoner_KillSharp_Clear()
{
	if (CheckAttribute(pchar, "quest.SharpPrisoner_GiveFree"))
	{
		pchar.quest.SharpPrisoner_GiveFree.over = "yes";
	}
	if (CheckAttribute(pchar, "quest.SharpPrisoner_GiveFree_1"))
	{
		pchar.quest.SharpPrisoner_GiveFree_1.over = "yes";
	}
	
	ref rChr = CharacterFromID("Sharp_Prisoner");
	ChangeCharacterAddressGroup(rChr, "none", "", "");
	ReleasePrisoner(rChr);
	
	if (CheckAttribute(&TEV, "Sharp_Prisoner_DialogChoosen"))
	{
		DeleteAttribute(&TEV, "Sharp_Prisoner_DialogChoosen");
	}
	
	int sharpCharIndex = GetCharacterIndex("Sharp");
	if (sharpCharIndex > 0)
	{
		LAi_KillCharacter(&Characters[sharpCharIndex]);
	}
}

void SeaPearl_SharpPrisoner_KillSharp()
{
	LAi_Fade("","");
	
	SeaPearl_SharpPrisoner_KillSharp_Clear();
	
	pchar.questTemp.Sharp = "sharpDead";

	RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
    SeaPearl_SpainMayor_DelQuestMarks();
    RemoveLandQuestmark_Main(CharacterFromID("spa_guber"), "SharpPearl");

	AddQuestRecord("SharpPearl", "24");
	CloseQuestHeader("SharpPearl");
}

void SeaPearl_SharpPrisoner_BetraySharpToSpainMayor()
{
	AddMoneyToCharacter(pchar, 40000);
	ChangeCharacterNationReputation(pchar, SPAIN, 40);
	
	SeaPearl_SharpPrisoner_KillSharp_Clear();
	
	pchar.questTemp.Sharp = "sharpDead";
    RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
    SeaPearl_SpainMayor_DelQuestMarks();
    RemoveLandQuestmark_Main(CharacterFromID("spa_guber"), "SharpPearl");
	
	string _city = GetCityNameByLocation(&Locations[FindLocation(pchar.location)]);
	ref rChr = characterFromID(_city + "_Mayor");
	AddQuestRecord("SharpPearl", "27");
	AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("SharpPearl", "sCity", XI_ConvertString("Colony" + _city + "Gen"));
	CloseQuestHeader("SharpPearl");
	Achievment_Set(ACH_Lovets_zhemchuga);
}

void SeaPearl_SharpPrisoner_BetraySharpToSpainGovernor()
{
	// GIVE PATENT
	if (!isMainCharacterPatented())
	{
		pchar.PatentNation = NationShortName(SPAIN);
		pchar.PatentPrice = 0;
		DoQuestCheckDelay("any_patent_take", 0.1);
		ChangeCharacterHunterScore(Pchar, NationShortName(SPAIN) + "hunter", -100);
	}
	ChangeCharacterNationReputation(pchar, SPAIN, 40);
	
	SeaPearl_SharpPrisoner_KillSharp_Clear();
	
	pchar.questTemp.Sharp = "sharpDead";
	RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
    SeaPearl_SpainMayor_DelQuestMarks();
    RemoveLandQuestmark_Main(CharacterFromID("spa_guber"), "SharpPearl");

	AddQuestRecord("SharpPearl", "29");
	AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("SharpPearl");
	Achievment_Set(ACH_Lovets_zhemchuga);
}

void SeaPearl_SharpPrisoner_BetraySharpToSpainGovernor_DenyPatent()
{
	AddMoneyToCharacter(pchar, 100000);
	ChangeCharacterNationReputation(pchar, SPAIN, 40);
	
	SeaPearl_SharpPrisoner_KillSharp_Clear();
	
	pchar.questTemp.Sharp = "sharpDead";
    RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
    SeaPearl_SpainMayor_DelQuestMarks();
    RemoveLandQuestmark_Main(CharacterFromID("spa_guber"), "SharpPearl");

	AddQuestRecord("SharpPearl", "28");
	AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("SharpPearl");
	Achievment_Set(ACH_Lovets_zhemchuga);
}

void SeaPearl_SharpPrisoner_GiveFree_NearGrot_StartDialog(string qName)
{
    if (CheckAttribute(pchar, "quest.SharpPrisoner_GiveFree_1"))
        pchar.quest.SharpPrisoner_GiveFree_1.over = "yes";

    chrDisableReloadToLocation = true;

	ref rChr = CharacterFromID("Sharp_Prisoner");
	rChr.Dialog.Currentnode = "SharpPrisoner_NearGrot";
	AddLandQuestmark_Main(rChr, "SharpPearl");

	LAi_SetActorTypeNoGroup(rChr);
    LAi_SetActorType(pchar);

    ChangeCharacterAddressGroup(rChr, pchar.location, "goto", LAi_FindNearestLocator2NPC(pchar, "goto"));
    LAi_ActorWaitDialog(pchar, rChr);
    LAi_ActorDialog(rChr, pchar, "", -1, 0);
}

void SeaPearl_SharpPrisoner_GiveFree_RunToGrot()
{
    ref rChr = CharacterFromID("Sharp_Prisoner");
    // идем ножками
    LAi_ActorRunToLocation(rChr, "reload", "reload2", "Hispaniola_Grot", "reload", "reload1", "SeaPearl_SharpPrisoner_GiveFree_ReloadToGrot", 40);
    LAi_ActorFollow(pchar, rChr, "", -1);
}

void SeaPearl_SharpPrisoner_GiveFree_InGrot_StartDialog(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationDisableMonstersGen(pchar.location, true);

	ref rChr = CharacterFromID("Sharp_Prisoner");
	rChr.Dialog.Currentnode = "SharpPrisoner_InPlace";

	LAi_SetActorTypeNoGroup(rChr);
	LAi_SetActorType(pchar);
	
	ChangeCharacterAddressGroup(rChr, pchar.location, "goto", "goto5");
	LAi_ActorWaitDialog(pchar, rChr);
	LAi_ActorDialog(rChr, pchar, "", -1, 0);
}

void SeaPearl_SharpPrisoner_GiveFree_TeleportToChest()
{
	ref rChr = CharacterFromID("Sharp_Prisoner");
	// идем ножками
	LAi_ActorRunToLocator(rChr, "goto", "goto3", "SeaPearl_SharpPrisoner_GiveFree_StartDialogDelay", 40);
	LAi_ActorFollow(pchar, rChr, "", -1);
}

void SeaPearl_SharpPrisoner_GiveFree_TeleportToRest()
{
	bQuestCheckProcessFreeze = true;
	WaitDate("", 0, 0, 0, 1, 0);
	bQuestCheckProcessFreeze = false;
	
	ref rChr = CharacterFromID("Sharp_Prisoner");
	
	float locx, locy, locz;
	GetCharacterPos(rChr, &locx, &locy, &locz);
	
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_14"), "Reload_To_Location", 0, 2.0);
	SetLaunchFrameReloadLocationParam(pchar.location, "goto", "goto5", "SeaPearl_SharpPrisoner_GiveFree_StartDialog");
	LAi_MethodDelay("LaunchFrameForm", 0);
	TeleportCharacterToLocator(rChr, "goto", "goto6");
}

void SeaPearl_SharpPrisoner_GiveFree_AddSharpToCrew()
{
	ref rChrOld = CharacterFromID("Sharp");
	rChrOld.lifeDay = 0;
	ref rChr = GetCharacter(NPC_GenerateCharacter("SharpOff", "Bartholomew_Sharp", "man", "man", 20, PIRATE, -1, false));
	
	GiveItem2Character(rChr, GUN_COMMON);
	rChr.equip.gun = GUN_COMMON;
	GiveItem2Character(rChr, "blade25");
	rChr.equip.blade = "blade25";
	ItemTakeEx(rChr, "bullet,gunpowder", "10");
	
	rChr.name = FindPersonalName("Sharp_name");
	rChr.lastname = FindPersonalName("Sharp_lastname");
	rChr.greeting = "Gr_Officer";
	rChr.Dialog.Filename = "Officer_Man.c";
	rChr.quest.meeting = true;
	SetSelfSkill(rChr, 60, 60, 60, 60, 60);
    SetShipSkill(rChr, 70, 50, 70, 70, 65, 50, 35, 55, 60);
	LAi_SetHP(rChr, 200.0, 200.0);
	
	rChr.rank = 18;
	SetSPECIAL(rChr, 
		GetCharacterSPECIAL(rChrOld, SPECIAL_S),
		GetCharacterSPECIAL(rChrOld, SPECIAL_P),
		GetCharacterSPECIAL(rChrOld, SPECIAL_E),
		GetCharacterSPECIAL(rChrOld, SPECIAL_C),
		GetCharacterSPECIAL(rChrOld, SPECIAL_I),
		GetCharacterSPECIAL(rChrOld, SPECIAL_A),
		GetCharacterSPECIAL(rChrOld, SPECIAL_L)
	);
	
	SetCharacterPerk(rChr, "FastReload");
	SetCharacterPerk(rChr, "HullDamageUp");
	SetCharacterPerk(rChr, "SailsDamageUp");
	SetCharacterPerk(rChr, "CrewDamageUp");
	SetCharacterPerk(rChr, "CriticalShoot");
	SetCharacterPerk(rChr, "LongRangeShoot");
	SetCharacterPerk(rChr, "CannonProfessional");
	SetCharacterPerk(rChr, "ShipDefenseProfessional");
	SetCharacterPerk(rChr, "ShipSpeedUp");
	SetCharacterPerk(rChr, "ShipTurnRateUp");
	SetCharacterPerk(rChr, "LootCollection");
    SetCharacterPerk(rChr, "ArtOfDeals");

	SetCharacterPerk(rChr, "BasicDefense");
	SetCharacterPerk(rChr, "AdvancedDefense");
	SetCharacterPerk(rChr, "Ciras");
	SetCharacterPerk(rChr, "BasicAttack");
	SetCharacterPerk(rChr, "AdvancedAttack");
	SetCharacterPerk(rChr, "HardHitter");
	SetCharacterPerk(rChr, "Gunman");
	SetCharacterPerk(rChr, "CriticalHit");
	SetCharacterPerk(rChr, "Sliding");
	SetCharacterPerk(rChr, "SwordplayProfessional");
	//черты
	SetCharacterPerk(rChr, "LoyalOff");
	SetCharacterPerk(rChr, "Energaiser");
	SetCharacterPerk(rChr, "Rebel");
	
	Pchar.questTemp.HiringOfficerIDX = sti(rChr.index);
	rChr.OfficerWantToGo.DontGo = true; //не пытаться уйти
	rChr.loyality = MAX_LOYALITY;
	rChr.id = "SharpOff";
	
	LandEnc_OfficerHired();
}

void SeaPearl_Begin_AddQuestMarks()
{
    AddLandQuestmarkToFantoms_Main("habitue", "SharpPearl", "SharpPearl_Begin_Habitues_QuestMarkCondition");
    AddLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl", "");

    AddMapQuestMark_Major("Shore9", "SharpPearl", "SharpPearl_Begin_PearlVillages_WDMQuestMarkCondition");
    AddMapQuestMark_Major("Shore55", "SharpPearl", "SharpPearl_Begin_PearlVillages_WDMQuestMarkCondition");
}

void SeaPearl_PiratesBaron_AddQuestMarks()
{
    AddLandQuestMark_Main(CharacterFromID("Jackman"), "SharpPearl");
    AddLandQuestMark_Main(CharacterFromID("Henry Morgan"), "SharpPearl");
    AddLandQuestMark_Main(CharacterFromID("LeFransua_Mayor"), "SharpPearl");
    AddLandQuestMark_Main(CharacterFromID("Edward Mansfield"), "SharpPearl");
    AddLandQuestMark_Main(CharacterFromID("Providencia_Mayor"), "SharpPearl");

    if (GetCharacterIndex("Richard_Soukins") >= 0)
    {
        AddLandQuestMark_Main(CharacterFromID("Richard_Soukins"), "SharpPearl");
    }
    if (GetCharacterIndex("John Morris") >= 0)
    {
        AddLandQuestMark_Main(CharacterFromID("John Morris"), "SharpPearl");
    }
    if (GetCharacterIndex("John_Coxon") >= 0)
    {
        AddLandQuestMark_Main(CharacterFromID("John_Coxon"), "SharpPearl");
    }
}

void SeaPearl_PiratesBaron_DelQuestMarks()
{
    RemoveLandQuestMark_Main(CharacterFromID("Jackman"), "SharpPearl");
    RemoveLandQuestMark_Main(CharacterFromID("Henry Morgan"), "SharpPearl");
    RemoveLandQuestMark_Main(CharacterFromID("LeFransua_Mayor"), "SharpPearl");
    RemoveLandQuestMark_Main(CharacterFromID("Edward Mansfield"), "SharpPearl");
    RemoveLandQuestMark_Main(CharacterFromID("Providencia_Mayor"), "SharpPearl");

    if (GetCharacterIndex("Richard_Soukins") >= 0)
    {
        RemoveLandQuestMark_Main(CharacterFromID("Richard_Soukins"), "SharpPearl");
    }
    if (GetCharacterIndex("John Morris") >= 0)
    {
        RemoveLandQuestMark_Main(CharacterFromID("John Morris"), "SharpPearl");
    }
    if (GetCharacterIndex("John_Coxon") >= 0)
    {
        RemoveLandQuestMark_Main(CharacterFromID("John_Coxon"), "SharpPearl");
    }
}

void SeaPearl_Hostess_SetQuestMarks(bool isSet)
{
    for (int i=0; i<MAX_COLONIES; i++)
    {
        if (!CheckAttribute(&colonies[i], "nation")) continue;
        if (colonies[i].nation == "none") continue; // необитайки

        int iChar = GetCharacterIndex(colonies[i].id + "_Hostess");
        if (iChar != -1)
        {
            if(isSet)
            {
                AddLandQuestmark_Main_WithCondition(&Characters[iChar], "SharpPearl", "SharpPearl_SeekSharp_Hostess_QuestMarkCondition");
            }
            else
            {
                RemoveLandQuestmark_Main(&Characters[iChar], "SharpPearl");
            }
        }
    }
}

void SeaPearl_Hostess_AddQuestMarks()
{
    SeaPearl_Hostess_SetQuestMarks(true);
}

void SeaPearl_Hostess_DelQuestMarks()
{
    SeaPearl_Hostess_SetQuestMarks(false);
}

void SeaPearl_SpainMayor_SetQuestMarks(bool isSet)
{
    for (int i=0; i<MAX_COLONIES; i++)
    {
        if (!CheckAttribute(&colonies[i], "nation")) continue;
        if (colonies[i].nation == "none") continue; // необитайки
        if (sti(colonies[i].nation) != SPAIN) continue;

        int iChar = GetCharacterIndex(colonies[i].id + "_Mayor");
        if (iChar != -1)
        {
            if(isSet)
            {
                AddLandQuestmark_Main(&Characters[iChar], "SharpPearl");
            }
            else
            {
                RemoveLandQuestmark_Main(&Characters[iChar], "SharpPearl");
            }
        }
    }
}

void SeaPearl_SpainMayor_AddQuestMarks()
{
    SeaPearl_SpainMayor_SetQuestMarks(true);
}

void SeaPearl_SpainMayor_DelQuestMarks()
{
    SeaPearl_SpainMayor_SetQuestMarks(false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Генератор жемчужного промысла Sharp   конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Пиратская линейка     начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void PiratesLine_q1_tavernEnd()
{
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	bDisableLandEncounters = false;
	LAI_SetPlayerType(pchar);
    DoReloadCharacterToLocation("PuertoPrincipe_tavern", "goto", LAi_FindNearestFreeLocator2Pchar("goto"));
    ref sld = CharacterFromID("QuestPirate1");
    LAI_SetSitType(sld);
}

void PiratesLine_q1_arrest(string qName)
{
	chrDisableReloadToLocation = true;
	bDisableFastReload = true;
	float locx, locy, locz;
	ref sld;
	//LocatorReloadEnterDisable("Portroyal_town", "houseS1", true); //закроем дом Моргана
	GetCharacterPos(pchar, &locx, &locy, &locz);
    for (int i=1; i<=3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("QuestSold_"+i, "sold_eng_"+i, "man", "man", 20, ENGLAND, 0, true));
		sld.City = "PortRoyal";
		//sld.CityType = "soldier";
		sld.BreakTmplAndFightGroup = true; //реагировать на атаку
		sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
		sld.dialog.currentnode = "ArrestInPR";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		ChangeCharacterAddressGroup(sld, pchar.location, "patrol", "patrol16");
		if (i == 1) LAi_ActorDialog(sld, pchar, "", -1, 0);
		else LAi_ActorFollow(sld, characterFromId("QuestSold_1"), "", -1);
	}	
	sld = characterFromId("QuestPirate2");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));	
	LAi_SetActorTypeNoGroup(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	LAi_ActorFollow(sld, pchar, "", -1);

	QuestPointerDelLoc("PortRoyal_town", "quest", "detector_PQ1");
}

void PiratesLine_q1_toPrison()
{
	ref sld = characterFromId("QuestPirate2");
	sld.lifeDay = 0;
	ChangeCharacterAddress(sld, "none", "");
	RemovePassenger(pchar, sld);
	DoReloadCharacterToLocation("PortRoyal_prison",  "goto", "goto9");
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
    RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
	LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_prison")], true);
    DoQuestFunctionDelay("PiratesLine_q1_MorganInPrison", 10.0);
    sld = characterFromId("Henry Morgan");
    LAi_SetStayTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "PortRoyal_prison", "goto", "goto13");
	locations[FindLocation("PortRoyal_fort")].loginNpc = true;
}

void PiratesLine_q1_MorganInPrison(string qName)
{
    ref sld = characterFromID("Henry Morgan");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorGoToLocator(sld, "goto", "goto23", "PiratesLine_q1_MorganGoTo", -1);
}

void PiratesLine_q1_MorganEnd()
{
	bDisableCharacterMenu = false; //Hokkins: откроем Ф2
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	LocatorReloadEnterDisable("Portroyal_town", "houseS1", false); //откроем дом Моргана
	LAi_LocationFightDisable(&Locations[FindLocation("PortRoyal_prison")], false);
	pchar.questTemp.jailCanMove = true; //чтобы спокойно выйти из тюрьмы
	AddQuestRecord("Pir_Line_1_JohnBolton", "4");
	DoQuestReloadToLocation("PortRoyal_prison", "goto", "goto12", "");
    ref sld = characterFromId("Henry Morgan");
    LAi_SetHuberTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
    AddLandQuestmark_Main(sld, "Pir_Line");
}
//пиратка, квест №3, поиски Лоу
void PiratesLine_q3_LoyHouse(string qName)
{
	AddQuestRecord("Pir_Line_3_KillLoy", "2");
	AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("ся","ась"));
	AddQuestUserData("Pir_Line_3_KillLoy", "sSex1", GetSexPhrase("","а"));
	pchar.questTemp.piratesLine = "KillLoy_toSeek";

	AddLandQuestmark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Pir_Line");
	AddLandQuestmark_Main(CharacterFromID("LeFransua_trader"), "Pir_Line");
	AddLandQuestmark_Main(CharacterFromID("FortFrance_PortMan"), "Pir_Line");
	AddLandQuestmark_Main(CharacterFromID("FortFrance_shipyarder"), "Pir_Line");
	AddLandQuestmark_Main(CharacterFromID("FortFrance_usurer"), "Pir_Line");
}

void PiratesLine_q3_loginSeaWolf(string qName)
{
	if (GetCompanionQuantity(pchar) <= 1 && 5-sti(RealShips[sti(pchar.ship.type)].Class) <= 0)
	{
		ref sld = characterFromId("EdwardLoy");
		sld.dialog.currentnode   = "SeaWolf";
		sld.greeting = "CapSinkShip";
		pchar.questTemp.piratesLine = "KillLoy_SeaWolfBattle";
		AddQuestRecord("Pir_Line_3_KillLoy", "15");
		AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("ел","ла"));
		AddQuestUserData("Pir_Line_3_KillLoy", "sSex1", GetSexPhrase("","а"));
		Group_AddCharacter("SW_Group", "EdwardLoy");			
		Group_SetType("SW_Group", "pirate");
		Group_SetGroupCommander("SW_Group", "EdwardLoy");
		string sTemp = "quest_ship_" + (rand(4)+5);
		Group_SetAddress("SW_Group", "Cumana", "quest_ships", sTemp);
		Group_SetTaskAttack("SW_Group", PLAYER_GROUP);
		pchar.Quest.PiratesLine_q3_over1.win_condition.l1 = "Location_Type";
		pchar.Quest.PiratesLine_q3_over1.win_condition.l1.location_type = "town";
		pchar.Quest.PiratesLine_q3_over1.function = "PiratesLine_q3_over";
		pchar.Quest.PiratesLine_q3_over2.win_condition.l1 = "Location_Type";
		pchar.Quest.PiratesLine_q3_over2.win_condition.l1.location_type = "seashore";
		pchar.quest.PiratesLine_q3_over2.function = "PiratesLine_q3_over";
		Pchar.quest.PiratesLine_q3_over3.win_condition.l1 = "MapEnter";
		pchar.quest.PiratesLine_q3_over3.function = "PiratesLine_q3_over";
		PiratesLine_q3_RemoveQuestMarksToTavernkeepers();
	}
	else
	{
		pchar.quest.PiratesLine_q3_SeaWolfAgain.win_condition.l1 = "ExitFromLocation";
		pchar.quest.PiratesLine_q3_SeaWolfAgain.win_condition.l1.location = "Cumana";
		pchar.quest.PiratesLine_q3_SeaWolfAgain.function = "PiratesLine_q3_SeaWolfAgain";	
	}
}

void PiratesLine_q3_SeaWolfAgain(string qName)
{
	pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1 = "location";
	pchar.quest.PiratesLine_q3_loginSeaWolf.win_condition.l1.location = "Cumana";
	pchar.quest.PiratesLine_q3_loginSeaWolf.function = "PiratesLine_q3_loginSeaWolf";	
}

void PiratesLine_q3_over(string qName)
{
	int i, iCap, iShip;
	bool bOk = false;
	pchar.quest.PiratesLine_q3_over1.over = "yes";
	pchar.quest.PiratesLine_q3_over2.over = "yes";
	pchar.quest.PiratesLine_q3_over3.over = "yes";
	if (GetCharacterIndex("EdwardLoy") == -1)
	{
		//HardCoffee реф дилогов Моргана
		pchar.QuestTemp.PirLine_quests_task = "PL_Q3_GoodWork";

		for (i = 0; i < COMPANION_MAX; i++)
		{
			iCap = GetCompanionIndex(pchar, i);
			if (iCap >= 0)
			{
				iShip = sti(characters[iCap].ship.type);
				if (iShip != SHIP_NOTUSED)
				{
					if (sti(RealShips[iShip].basetype) == SHIP_BRIGSW)
					{
						bOk = true;
						break;
					}
				}
			}
		}

		if (bOk)
		{
			AddQuestRecord("Pir_Line_3_KillLoy", "17");
			pchar.questTemp.piratesLine.T1 = "KillLoy_GoodWork"; //выполнено все, бриг захвачен
		}
		else
		{
			AddQuestRecord("Pir_Line_3_KillLoy", "18");
			pchar.questTemp.piratesLine.T1 = "KillLoy_LoyIsDied"; //Лоу убит, бриг не захвачен
		}
        AddLandQuestmark_Main(CharacterFromID("Jackman"), "Pir_Line");
	}
	else
	{
		AddQuestRecord("Pir_Line_3_KillLoy", "16");
		AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("","ла"));
		pchar.questTemp.piratesLine = "KillLoy_loose"; //Лоу остался жив, полный провал
		ref sld = characterFromId("EdwardLoy");
		sld.lifeDay = 0;
		QuestSetCurrentNode("Henry Morgan", "PL_Q3_notFound");
	}
	group_DeleteGroup("SW_Group");

	AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
}

void PiratesLine_q3_SetQuestMarksToTavernkeepers(bool isSet)
{
    for (int i=0; i<MAX_COLONIES; i++)
    {
        if (!CheckAttribute(&colonies[i], "nation")) continue;
        if (colonies[i].nation == "none") continue; // необитайки
        if (colonies[i].id == "pirates") continue; // Бермуды пропустим

        int iChar = GetCharacterIndex(colonies[i].id + "_tavernkeeper");
        if (iChar != -1)
        {
            if(isSet)
            {
                AddLandQuestmark_Main(&Characters[iChar], "Pir_Line");
            }
            else
            {
                RemoveLandQuestmark_Main(&Characters[iChar], "Pir_Line");
            }
        }
    }
}

void PiratesLine_q3_AddQuestMarksToTavernkeepers()
{
    PiratesLine_q3_SetQuestMarksToTavernkeepers(true);
}

void PiratesLine_q3_RemoveQuestMarksToTavernkeepers()
{
    PiratesLine_q3_SetQuestMarksToTavernkeepers(false);
}
//пиратка, квест №4, грабежи жемчужных тартан
void PQ4_SeaPearl_login(string qName)
{
	ref sld;
	string sTemp;
	pchar.quest.PQ4_SeaPearl_Late.over = "yes";
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("PearlGroup");
	int iTemp = sti(pchar.questTemp.Sharp.PearlAreal.qtyShips);
	Group_FindOrCreateGroup("PearlGroup");
	Group_SetType("PearlGroup", "trade");
	for (int j = 1; j <= iTemp; j++)
	{        
		sTemp = "PearlCapitain_" + j;
		sld = GetCharacter(NPC_GenerateCharacter(sTemp, "merch_"+(rand(14)+1), "man", "man", 10, SPAIN, 30, true)); //TODO: сюда простолюдинов или работников, но нужны портреты
		sld.Ship.Type = GenerateShip(SHIP_TARTANE, false);
		SetRandomNameToShip(sld);
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
//		Fantom_SetBalls(sld, "pirate");
        SetCharacterGoods(sld, GOOD_PINCTADA, 700 + rand(3 * 700));
        sld.Coastal_Captain = true;
		sld.ShipTaskLock = true;
		sld.AlwaysEnemy = true;
//		sld.Abordage.Enable = false;
        sld.AlwaysSurrender = true;
		sld.SinkTenPercent = true; //экономия в АИ шипов
		sld.PearlTartane = true; //тартана ловцов жемчуга, можно грабить
		LAi_group_MoveCharacter(sld, "EnemyFight");
		Group_AddCharacter("PearlGroup", sTemp);
	}
    // ==> стравливание
	Group_SetGroupCommander("PearlGroup", "PearlCapitain_1");			
	Group_SetTaskRunaway("PearlGroup", PLAYER_GROUP);
	Group_SetAddress("PearlGroup", pchar.questTemp.Sharp.PearlAreal.Island, "quest_ships", pchar.questTemp.Sharp.PearlAreal.locator);	
	Group_LockTask("PearlGroup");
	pchar.quest.PQ4_SeaPearl_DieHard1.win_condition.l1 = "ExitFromLocation";
	pchar.quest.PQ4_SeaPearl_DieHard1.win_condition.l1.location = pchar.questTemp.Sharp.PearlAreal.Island;
	pchar.quest.PQ4_SeaPearl_DieHard1.function = "PQ4_SeaPearl_DieHard";
	Pchar.quest.PQ4_SeaPearl_DieHard2.win_condition.l1 = "MapEnter";
	pchar.quest.PQ4_SeaPearl_DieHard2.function = "PQ4_SeaPearl_DieHard";
}

void PQ4_SeaPearl_Late(string qName)
{	
	pchar.quest.PQ4_SeaPearl_login.over = "yes";
	AddQuestRecord("Pir_Line_4_Pearl", "2");
	AddQuestUserData("Pir_Line_4_Pearl", "sSex", GetSexPhrase("","а"));
	pchar.questTemp.piratesLine = "PearlQ4_late";
	ref sld = characterFromId("Henry Morgan");
    LAi_SetHuberTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
	//HardCoffee реф диалогов Моргана
	pchar.QuestTemp.PirLine_quests_task = "PL_Q4_late";
	AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
}

void PQ4_SeaPearl_DieHard(string qName)
{
	group_DeleteGroup("PearlGroup");
	pchar.quest.PQ4_SeaPearl_DieHard1.over = "yes";
	pchar.quest.PQ4_SeaPearl_DieHard2.over = "yes";

	if (pchar.questTemp.Sharp == "SeaPearl_success" && GetSquadronGoods(pchar, GOOD_PINCTADA) >= 700)
	{	//успешное нападение
		AddQuestRecord("Pir_Line_4_Pearl", "3");
//		AddQuestUserData("Pir_Line_4_Pearl", "iSmall", pchar.questTemp.Sharp.PearlAreal.SmallPearlQty);
//		AddQuestUserData("Pir_Line_4_Pearl", "iBig", pchar.questTemp.Sharp.PearlAreal.BigPearlQty);
		AddQuestUserData("Pir_Line_4_Pearl", "iQty", pchar.questTemp.Sharp.PearlAreal.PinctadaQty);
		pchar.questTemp.piratesLine = "PearlQ4_goodWork";
		//QuestSetCurrentNode("Henry Morgan", "PL_Q4_goodWork");
//		pchar.questTemp.piratesLine.Qty.SmallPearl = pchar.questTemp.Sharp.PearlAreal.SmallPearlQty;
//		pchar.questTemp.piratesLine.Qty.BigPearl = pchar.questTemp.Sharp.PearlAreal.BigPearlQty;
		pchar.questTemp.piratesLine.Qty.Pinctada = pchar.questTemp.Sharp.PearlAreal.PinctadaQty;
	}
	else
	{	//неудачное нападение
		AddQuestRecord("Pir_Line_4_Pearl", "4");
		AddQuestUserData("Pir_Line_4_Pearl", "sSex", GetSexPhrase("","ла"));
		//HardCoffee реф диалогов Моргана
		pchar.questTemp.piratesLine = "PearlQ4_badWork";
	}
	pchar.QuestTemp.PirLine_quests_task = "PL_Q4_DidWork";
	pchar.questTemp.Sharp = "seekSharp"; //опять начинаем с борделей
	pchar.questTemp.Sharp.brothelChance = rand(10);
    if (pchar.questTemp.Sharp.SeekSpy == "begin") // первый базар должен быть не в борделе
    {
        pchar.questTemp.Sharp.brothelChance = 1;
    }
    else
    {
        CloseQuestHeader("SharpPearl");
    }
	DeleteAttribute(pchar, "questTemp.Sharp.PearlAreal");
	AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
}
//пиратка, квест №5, работа ОЗГа
void PQ5_meetInPortRoyal(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld = GetCharacter(NPC_GenerateCharacter("CapGoodly", "Goodley", "man", "man", 20, PIRATE, -1, true));
	sld.name = FindPersonalName("CapGoodly_name");
	sld.lastname = FindPersonalName("CapGoodly_lastname");
	sld.rank = 20;
	sld.city = "PortRoyal";
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PQ5CapGoodly";
	sld.greeting = "Gr_EvilPirate";
    ChangeCharacterAddressGroup(sld, "PortRoyal_town", "patrol", "patrol16");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void PQ5_inOrryHouse(string qName)
{
	pchar.questTemp.piratesLine = "PL5Hunter_exitReload";
	RemoveLandQuestmark_Main(CharacterFromID("Pirates_tavernkeeper"), "Pir_Line");

	LAi_LocationFightDisable(&locations[FindLocation("Pirates_houseS1")], true); //закроем боевки
	chrDisableReloadToLocation = true;
	LAi_group_Delete("EnemyFight");

	ref sld = GetCharacter(NPC_GenerateCharacter("Aivory", "officer_26", "man", "man", 30, PIRATE, -1, true)); //watch_quest_moment
	FantomMakeCoolFighter(sld, 30, 100, 100, "blade28", "pistol3", 80);
	sld.name = FindPersonalName("Aivory_name");
	sld.lastname = FindPersonalName("Aivory_lastname");
	sld.city = "Pirates";
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PQ5Hero";
	sld.greeting = "Gr_MiddPirate";
	LAi_SetStayType(sld);
    ChangeCharacterAddressGroup(sld, "Pirates_houseS1", "goto", "goto1");

	sld = GetCharacter(NPC_GenerateCharacter("Orry", "officer_5", "man", "man", 27, PIRATE, -1, true)); //watch_quest_moment; опять тут был вездесущий officer_15
	FantomMakeCoolFighter(sld, 27, 100, 100, "topor2", "pistol3", 50);
	sld.name = FindPersonalName("Orry_name");
	sld.lastname = FindPersonalName("Orry_lastname");
	sld.city = "Pirates";
	sld.money = 51600;
	sld.SaveItemsForDead   = true; // сохранять на трупе вещи
	sld.DontClearDead = true;  // не убирать труп через 200с
	sld.dialog.filename   = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode   = "PQ5Orry";
	sld.greeting = "pirat_quest";
	LAi_SetStayType(sld);
    ChangeCharacterAddressGroup(sld, "Pirates_houseS1", "goto", "goto2");

	pchar.quest.PQ5_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.PQ5_afterFight.win_condition.l1.character = "Aivory";
	pchar.quest.PQ5_afterFight.win_condition.l2 = "NPC_Death";
	pchar.quest.PQ5_afterFight.win_condition.l2.character = "Orry";
	pchar.quest.PQ5_afterFight.function = "PQ5_afterFight";
}

void PQ5_afterChangeMainHero()
{
	LAi_LocationFightDisable(&locations[FindLocation("Pirates_houseS1")], false);
    SetMainCharacterIndex(1);
    PChar = GetMainCharacter();
    LAi_SetPlayerType(PChar);
	locCameraTarget(PChar);
    locCameraFollow();	
	ref rCharacter = characterFromID("Orry");
	LAi_SetActorType(rCharacter);
	LAi_ActorTurnToCharacter(rCharacter, pchar);
	ref sld = characterFromID("Aivory");
	sld.dialog.currentnode = "PQ5Aivory";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	EndQuestMovie();
}

void PQ5_afterChangeMainHero2()
{	
	ref rCharacter = characterFromID("Orry");
	LAi_group_MoveCharacter(rCharacter, "EnemyFight");
	ref sld = characterFromID("Aivory");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_SetFightMode(pchar, true);
}

void PQ5_afterFight(string qName)
{
	AddQuestRecord("Pir_Line_5_Hunter", "11");
	AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Gen"));
	pchar.questTemp.piratesLine = "PL5Hunter_toMorgan";
	chrDisableReloadToLocation = false;
	Pchar.quest.PQ5_inPortPoyalTavern.win_condition.l1 = "location";
	Pchar.quest.PQ5_inPortPoyalTavern.win_condition.l1.location = "PortRoyal_tavern";
	Pchar.quest.PQ5_inPortPoyalTavern.function = "PQ5_inPortPoyalTavern";
	
	AddLandQuestmark_Main(CharacterFromID("CapGoodly"), "Pir_Line");
	AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.piratesLine.Q5.city_4+"_usurer"), "Pir_Line");
}

void PQ5_inPortPoyalTavern(string qName)
{
	FreeSitLocator("PortRoyal_tavern", "sit3");
	ref sld = characterFromID("CapGoodly");
	sld.dialog.currentnode = "PQ5CapGoodlyEnd";
	LAi_SetSitTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "PortRoyal_tavern", "sit", "sit3");
}

void PQ5_Morgan_1()
{
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "goto", "goto2", "PQ5_Morgan_2", -1.0);
}

void PQ5_Morgan_4()
{
    SetMainCharacterIndex(1);
    PChar = GetMainCharacter();
    LAi_SetPlayerType(PChar);
	locCameraTarget(PChar);
    locCameraFollow();	
	ref rCharacter = characterFromID("CapGoodly");
	LAi_SetActorType(rCharacter);
	LAi_ActorTurnToCharacter(rCharacter, pchar);
	ref sld = characterFromID("Henry Morgan");
	LAi_SetActorType(pchar);
	LAi_ActorDialog(pchar, sld, "", 0, 0);
}

void PQ5_Morgan_5()
{
	LAi_group_Delete("EnemyFight");
	LAi_SetPlayerType(pchar);
	ref sld = characterFromID("CapGoodly");
	LAi_group_MoveCharacter(sld, "EnemyFight");
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	pchar.quest.PQ5_Morgan_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.PQ5_Morgan_afterFight.win_condition.l1.character = "CapGoodly";
	pchar.quest.PQ5_Morgan_afterFight.function = "PQ5_Morgan_afterFight";
	LAi_SetFightMode(pchar, true);
}

void PQ5_Morgan_afterFight(string qName)
{
	QuestSetCurrentNode("Henry Morgan", "PL_Q5_afterFight");
	AddQuestRecord("Pir_Line_5_Hunter", "13");
	AddQuestUserData("Pir_Line_5_Hunter", "sSex", GetSexPhrase("","а"));
	AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
}
//пиратка, квест №6, двойник
void PQ6_ShoreBattle(string qName)
{
    ref sld;
    int iTemp, i;
    float locx, locy, locz;
    LAi_group_Delete("EnemyFight");
	LocatorReloadEnterDisable("Shore7", "boat", true); //закроем выход в море
	GetCharacterPos(pchar, &locx, &locy, &locz);
	//наши
	string sTemp = NationShortName(sti(pchar.nation));
	arrayNPCModelHow = 0;
    for (i=1; i<=5; i++)
    {
        iTemp = 10 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("OwnPirate_"+i, "pirate_"+(rand(15)+1), "man", "man", iTemp, sti(pchar.nation), 0, true)); //sailor
		SetNPCModelUniq(sld, "pirate", MAN);
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		//sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
		//if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
        ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto8");
    }
	//враги
	arrayNPCModelHow = 0;
	for (i=1; i<=(MOD_SKILL_ENEMY_RATE + 3); i++)
    {
        iTemp = 15 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("QuestPirate_"+i, "officer_"+(rand(19)+1), "man", "man", iTemp, PIRATE, -1, true));
		SetNPCModelUniq(sld, "pofficer", MAN);
		//watch_quest_moment; странный момент, надо посмотреть в игре и подобрать другой микс
        FantomMakeCoolFighter(sld, iTemp, 80, 80, BLADE_LONG, "pistol3", 50);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        PlaceCharacter(sld, "goto", PChar.location);
    }
    LAi_group_SetLookRadius("EnemyFight", 100);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
    Pchar.quest.PQ6_JungleDialog.win_condition.l1 = "location";
    Pchar.quest.PQ6_JungleDialog.win_condition.l1.location = "Common_jungle_01";
    Pchar.quest.PQ6_JungleDialog.function = "PQ6_JungleDialog";
}

void PQ6_JungleDialog(string qName)
{
	LAi_LocationFightDisable(&Locations[FindLocation("Common_jungle_01")], true);
	chrDisableReloadToLocation = true;
	ref sld = GetCharacter(NPC_GenerateCharacter("QuestPirateHead", pchar.model, pchar.sex, pchar.model.animation, 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 90, 90, "blade27", "pistol6", 100);
	sld.name = pchar.name;
	sld.lastname = pchar.lastname;
    sld.dialog.Filename = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode = "QuestPirateHead";
	sld.SaveItemsForDead = true;
	ChangeCharacterAddressGroup(sld, "Common_jungle_01", "goto", "goto1");
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void PQ6_JungleBattle()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	//наши
	ref sld;
	int iTemp, i;
	string sTemp = NationShortName(sti(pchar.nation));
	arrayNPCModelHow = 0;
    for (i=1; i<=5; i++)
    {
        iTemp = 10 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("OwnPirate2_"+i, "pirate_"+(rand(15)+1), "man", "man", iTemp, sti(pchar.nation), 0, true));
		SetNPCModelUniq(sld, "pirate", MAN);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
    }
	//враги
	for (i=1; i<=(MOD_SKILL_ENEMY_RATE + 3); i++)
    {
        iTemp = 17 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("QuestPirate2_"+i, "officer_"+(rand(19)+1), "man", "man", iTemp, PIRATE, -1, true));
		SetNPCModelUniq(sld, "pofficer", MAN);
		//watch_quest_moment; странный момент, надо посмотреть в игре и подобрать другой микс
        FantomMakeCoolFighter(sld, iTemp, 90, 90, "topor2", "pistol6", 100);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, "Common_jungle_01", "goto", "goto2");
    }
    LAi_group_SetLookRadius("EnemyFight", 100);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "PQ6_afterBattle");
}
//пиратка, квест №7, мочим Соукинса
void PQ7_FriendLinney(string qName)
{
	if (GetQuestPastMinutesParam("questTemp.piratesLine") < 20)
	{
		ref sld = GetCharacter(NPC_GenerateCharacter("FriendLinney", "officer_1", "man", "man", 20, sti(pchar.nation), 5, true)); //ниже обновляется
		SetCaptanModelByEncType(sld, "pirate");
		sld.dialog.filename = "Quest\PiratesLine_dialog.c";
		sld.DeckDialogNode = "FriendLinney";
		FantomMakeCoolFighter(sld, 20, 80, 70, "blade32", "pistol3", 20);
		FantomMakeCoolSailor(sld, SHIP_LUGGER_W, "", CANNON_TYPE_CANNON_LBS8, 70, 90, 85);
		sld.AlwaysSandbankManeuver = true;
		sld.DontRansackCaptain = true;
		sld.Ship.Mode = "Pirate";
		DeleteAttributeMass(sld, "", "SinkTenPercent,SaveItemsForDead,DontClearDead,AboardToFinalDeck,DontRansackCaptain");
		sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
		Group_AddCharacter("FriendLinney_Group", "FriendLinney");			
		Group_SetType("FriendLinney_Group", "pirate");
		Group_SetGroupCommander("FriendLinney_Group", "FriendLinney");
		Group_SetAddress("FriendLinney_Group", "Hispaniola1", "quest_ships", "quest_ship_4");
		Group_SetTaskNone("FriendLinney_Group");
		LogSound_WithNotify(StringFromKey("InfoMessages_35"), "EvEnemy_1", "ShipSight");
		SetBan("Map", 1);

        AddLandQuestMark_Main(sld, "Pir_Line");
	}
	else
	{
		PQ7_FriendLinneyExpire();
	}
}

void PQ7_FriendLinneyExpire()
{
	SetBan("Map", 0);
	AddQuestRecord("Pir_Line_7_Soukins", "3");
	AddQuestUserData("Pir_Line_7_Soukins", "sSex", GetSexPhrase("","а"));
	pchar.questTemp.piratesLine = "Soukins_LaVegaLate";
	//HardCoffee реф диалогов Моргана
	pchar.QuestTemp.PirLine_quests_task = "PL_Q7_AboutLiney";
	AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
}

void PQ7_LoginLeon()
{
	LAi_group_Delete("EnemyFight");
	group_DeleteGroup("FriendLinney_Group"); //сносим друга Стива Линнея
	ref sld = GetCharacter(NPC_GenerateCharacter("LeonCapitain", "officer_1", "man", "man", 25, PIRATE, 30, true)); //ниже обновляется
	SetCaptanModelByEncType(sld, "pirate");
	sld.dialog.filename = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentnode = "LeonCapitain";
	sld.greeting = "CapSinkShip";
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade32", "pistol6", 50);
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("LeonCapitain_ship"), CANNON_TYPE_CULVERINE_LBS24, 80, 80, 80);
	DeleteAttributeMass(sld, "", "SinkTenPercent,SaveItemsForDead,DontClearDead,AboardToFinalDeck,DontRansackCaptain");
	sld.Ship.Mode = "Pirate";
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true;
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	LAi_group_MoveCharacter(sld, "EnemyFight");

	string sGroup = "Leon_Group";
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));

	SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
	
	sld.mapEnc.type = "warrior";
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = FindPersonalName("LeonCapitain_mapEnc");
	Map_CreateWarrior("shore33", "LeonCapitain", 30);
	Log_TestInfo("Фрегат Леон установлен.");

	AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
}

void PQ7_inSoukinsResidence(string qName)
{
	ref rItm;
	//HardCoffee ref Morgan's dialogue
	pchar.QuestTemp.PirLine_quests_task = "PL_Q7_BadWork";
	AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
	if (IsLoginTime()) DoQuestFunctionDelay("PQ7_inSoukinsResidence_2", 1.5);
	else
	{
		rItm = ItemsFromID("OpenBook");
		QuestPointerToLoc(rItm.startLocation, "item", rItm.startLocator); // поставим указатель
	}
	rItm = ItemsFromID("Ladder");
	QuestPointerDelLoc(rItm.startLocation, "item", rItm.startLocator); // уберем указатель с лестницы на всякий
}

void PQ7_inSoukinsResidence_2(string qName)
{
	LAi_SetActorType(pchar);
	ref sld = characterFromId("Richard_Soukins");
	QuestSetCurrentNode("Richard_Soukins", "PL_Q7_5");
	LAi_ActorDialog(pchar, sld, "", 0, 0);
}

void PQ7_loadToRecidence(string qName)
{
	DoQuestReloadToLocation("PuertoPrincipe_townhall", "reload", "reload2", "");
}

void PQ7_setBattleShip(string qName)
{	
	ref sld = &locations[FindLocation("PuertoPrincipe_townhall")];
	DeleteAttribute(sld, "reload.l2"); //уберем возможность спуститься с лестницы
	if (GetQuestPastMinutesParam("questTemp.piratesLine") > 100)
	{
		Log_TestInfo("Искомый баттлшип не будет установлен. Не успел вовремя выйти в море.");
		pchar.questTemp.piratesLine = "Soukins_battlshipLate";
		AddQuestRecord("Pir_Line_7_Soukins", "10");
		AddQuestUserData("Pir_Line_7_Soukins", "sSex", GetSexPhrase("ёл","ела"));
		AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("QuestCap_PL7", "navy_off_spa_5", "man", "man", 40, SPAIN, -1, true));							
		sld.dialog.filename = "Quest\PiratesLine_dialog.c";
		sld.dialog.currentnode = "QuestCap_PL7";
		sld.DeckDialogNode = "QuestCap_PL7_inDeck";
		sld.greeting = "CapSinkShip";
		FantomMakeCoolFighter(sld, 40, 90, 90, "blade32", "pistol4", 200);
		FantomMakeCoolSailor(sld, SHIP_BATTLESHIP, FindPersonalName("QuestCap_PL7_ship"), CANNON_TYPE_CULVERINE_LBS32, 90, 90, 90);
		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		DeleteAttribute(sld, "AboardToFinalDeck");
		DeleteAttribute(sld, "DontRansackCaptain");
		sld.AlwaysSandbankManeuver = true;
		sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
		sld.DontRansackCaptain = true;
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
		SetCharacterPerk(sld, "Sliding");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");

		string sGroup = "Quest_Ship";
		Group_FindOrCreateGroup(sGroup);
		Group_SetType(sGroup,"trade");
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation));
		
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);

		sld.mapEnc.type = "trade";
		sld.mapEnc.worldMapShip = "quest_ship";
		sld.mapEnc.Name = FindPersonalName("QuestCap_PL7_mapEnc");
		Map_CreateTraderXZ(1009.22, -992.708, 988.514, 515.407, "QuestCap_PL7", 15);
		Log_TestInfo("Искомый баттлшип начал движение.");
	}
}

void PQ7_winBattleShip(string qName)
{
	pchar.questTemp.piratesLine = "Soukins_battlshipWin";
	//HardCoffee ref Morgan's dialogue
	pchar.QuestTemp.PirLine_quests_task = "PL_Q7_GoodWork";
	AddQuestRecord("Pir_Line_7_Soukins", "13");
	pchar.quest.PQ7_BattleShip_dieHard.over = "yes";
	AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Pir_Line");
}

void PQ8_timeOver(string qName) //убираем моргана
{
	pchar.questTemp.piratesLine = "over";
	ref sld = characterFromId("Henry Morgan");
	ChangeCharacterAddress(sld, "none", "");
	RemoveLandQuestmark_Main(sld, "Pir_Line");
	RemoveMapQuestMark("PortRoyal_town", "Pir_Line");

	AddQuestRecord("Pir_Line_8_Panama", "2");
	AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Pir_Line_8_Panama");
	SetTimerFunction("PQ8_openPanama", 0, 0, 40);
	QuestSetCurrentNode("Oliver_Green", "PL_Q8_over"); //ноду секретарю
}

void PQ8_openPanama(string qName) //откроем Панаму
{
	LocatorReloadEnterDisable("Shore48", "reload1_back", false);
	LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", false);
	ref sld = characterFromId("Henry Morgan");
	sld.dialog.currentnode = "First time";
    ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
    LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
}

void PQ8_openPanama_2(string qName) //откроем Панаму
{
	ref sld = characterFromId("Henry Morgan");
	if (pchar.questTemp.piratesLine == "Panama_backToShip") 
	{
		SetTimerFunction("PQ8_openPanama_3", 0, 0, 360); // Warship 18.07.09 fix - было 180 почему-то
	}
	else 
	{
		sld.dialog.currentnode = "I_know_you_good";
		ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
		LAi_SetImmortal(sld, true);
		LAi_LoginInCaptureTown(sld, false);
		LAi_SetHuberType(sld);
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	}
	//возвращаем Джекмена
	int iTemp = GetCharacterIndex("Jackman");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}               
		LAi_SetHuberType(&characters[iTemp]);
		LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
        ChangeCharacterAddressGroup(&characters[iTemp], "Pirates_townhall", "sit", "sit1");
        characters[iTemp].dialog.currentnode = "I_know_you_good";
    }
    //Возвращаем на место Джона Морриса
    iTemp = GetCharacterIndex("John Morris");
    if (iTemp != -1 && CheckAttribute(&TEV, "JohnMorrisIsLifeInHouse"))
    {
        if(IsCompanion(&characters[iTemp]))
        {
            RemoveCharacterCompanion(pchar, &characters[iTemp]);
        }
        LAi_SetHuberType(characterfromID("John Morris"));
        LAi_group_MoveCharacter(&characters[iTemp], "ENGLAND_CITIZENS");
        ChangeCharacterAddressGroup(&characters[iTemp], "PortSpein_houseF2", "sit", "sit1");
        characters[iTemp].dialog.currentnode = "I_know_you_good";
    }
    //Возвращаем на место Соукинса
	iTemp = GetCharacterIndex("Richard_Soukins");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}                   
		LAi_SetHuberType(&characters[iTemp]);
		LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
        ChangeCharacterAddressGroup(&characters[iTemp], "PuertoPrincipe_townhall", "sit", "sit1");
        characters[iTemp].dialog.currentnode = "First time";
    }
	LocatorReloadEnterDisable("Panama_ExitTown", "reload4", false);
	SetLocationCapturedState("Panama_town", false);
	bDisableLandEncounters = false;
	pchar.quest.PL_Q8_backFight_1.over = "yes"; //на всякий случай
}

void PQ8_openPanama_3(string qName) //Морган после поездки в Лондон
{
	ref sld = characterFromId("Henry Morgan");
	sld.dialog.currentnode = "PL_Q8_afterPanama";
	ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
	LAi_SetImmortal(sld, true);
	LAi_LoginInCaptureTown(sld, false);
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
	AddLandQuestmark_Main(sld, "Pir_Line");
}

void PQ8_PanamaTimerOver(string qName)
{
    if (IsEntity(&worldMap))
    {
        if (!bQuestCheckProcessFreeze) // можно показать
		{
	        pchar.quest.PQ8_PanamaTimerOver_01.over = "yes"; // сброс, если уже откладывали
	        pchar.quest.PQ8_PanamaTimerOver_02.over = "yes";
			pchar.quest.PQ8_EnterPortoBello.over = "yes"; //снимаем прерывание на вход
            
            aref arOldMapPos;
			makearef(arOldMapPos, worldMap.old);
            WdmPrepareMapForAbordage(arOldMapPos);
            MakeCloneShipDeck(pchar, true); // подмена палубы
            DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
	        ReloadFromWMtoL_complete();
	        
            ref sld = characterFromID("Henry Morgan");
            ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto6");
            LAi_SetWarriorType(sld);
	        LAi_warrior_DialogEnable(sld, true);
	        sld.dialog.currentnode = "PL_Q8_timeOver";
   	        // ==> антураж
			arrayNPCModelHow = 0;
            for (int i=1; i<5; i++)
        	{
                sld = GetCharacter(NPC_GenerateCharacter("MorganPir_"+i, "pirate_"+(rand(15)+1), "man", "man", 15, PIRATE, 1, true)); //watch_quest_moment; моргану наёмников мб?
				SetNPCModelUniq(sld, "pirate", MAN);
                sld.dialog.Filename = "Sailors_dialog.c";
	            sld.dialog.currentnode = "Morgan_wait_you";
                LAi_SetWarriorType(sld);
                LAi_warrior_DialogEnable(sld, true);
                LAi_SetLoginTime(sld, 0.0, 24.0);
                LAi_SetHP(sld, 100.0, 100.0);
                ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto"+i);
            }
            pchar.quest.Munity = "";  // признак выхода с палубы (закрыто, а то можно не говорить)
            LAi_LockFightMode(pchar, true);
		}
		else
		{   // отложим до разморозки (пролет табличек)
      		Pchar.quest.PQ8_PanamaTimerOver_01.win_condition.l1 = "MapEnter";
            Pchar.quest.PQ8_PanamaTimerOver_01.function = "PQ8_PanamaTimerOver";
		}
	}
	else
	{   // подождём выхода на карту, раз время прошло, но мы не на ней
		Pchar.quest.PQ8_PanamaTimerOver_02.win_condition.l1 = "MapEnter";
        Pchar.quest.PQ8_PanamaTimerOver_02.function = "PQ8_PanamaTimerOver";
	}
}

void PQ8_EnterPortoBello()
{
	ref sld = characterFromId("Henry Morgan");
	LAi_SetImmortal(sld, false);
	pchar.quest.PQ8_PanamaTimerOver.over = "yes"; //снимаем таймер 
	//bQuestDisableMapEnter = true;
}

void PQ8_MorganInPortoBello()
{
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("PQ8_MorganInPortoBello_2", 3.0);	
}

void PQ8_MorganInPortoBello_2(string qName)
{	
	ref sld = characterFromId("Henry Morgan");
	LAi_LoginInCaptureTown(sld, true);
	LAi_SetCurHPMax(sld);
	sld.dialog.currentNode = "PL_Q8_PBResidence";
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PQ8_PBExitResidence(string qName)
{
	int iTemp = GetCharacterIndex("Henry Morgan");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}   				
		ChangeCharacterAddress(&characters[iTemp], "none", "");
	}
	iTemp = GetCharacterIndex("Jackman");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}   				
		ChangeCharacterAddress(&characters[iTemp], "none", "");
	}
	iTemp = GetCharacterIndex("John Morris");
	if (iTemp != -1)
	{
		if(IsCompanion(&characters[iTemp]))  
		{
			RemoveCharacterCompanion(pchar, &characters[iTemp]);
		}   				
		ChangeCharacterAddress(&characters[iTemp], "none", "");
	}
	ref sld = characterFromId("Richard_Soukins");
	sld.DeckDialogNode = "PL_Q8_deck_2";
	AddQuestRecord("Pir_Line_8_Panama", "5");
	pchar.Quest.PQ8_fromPBport.win_condition.l1 = "EnterToSea";
	pchar.Quest.PQ8_fromPBport.function = "PQ8_fromPBport";
	SetTimerFunction("PQ8_controlShore48", 0, 0, 2);
}

void PQ8_fromPBport(string qName)
{
	pchar.Quest.PQ8_controlShore48_1.win_condition.l1 = "Location_Type";
	pchar.Quest.PQ8_controlShore48_1.win_condition.l1.location_type = "town";
	pchar.Quest.PQ8_controlShore48_1.function = "PQ8_controlShore48";
	pchar.Quest.PQ8_controlShore48_2.win_condition.l1 = "Location_Type";
	pchar.Quest.PQ8_controlShore48_2.win_condition.l1.location_type = "seashore";
	pchar.Quest.PQ8_controlShore48_2.function = "PQ8_controlShore48";
}

void PQ8_controlShore48(string qName)
{
	ref sld;
	int iTemp, i;
	pchar.Quest.PQ8_controlShore48.over = "yes";
	pchar.Quest.PQ8_controlShore48_1.over = "yes";
	pchar.Quest.PQ8_controlShore48_2.over = "yes";
	if (pchar.location == "Shore48")
	{	//ГГ вовремя и на месте -->
		LAi_LocationFightDisable(&Locations[FindLocation("Shore48")], true); //закрываем локацию для боевки
		LocatorReloadEnterDisable("Shore48", "boat", true); //Не даем выходить в море
		chrDisableReloadToLocation = true;
		bDisableLandEncounters = true; //энкаунтеры не генерим
		pchar.questTemp.piratesLine = "Panama_inShore";
		pchar.questTemp.piratesLine.crewHero = makeint(GetCrewQuantity(pchar) / 100 / 2);	//запомним кол-во десанта от ГГ
		if (sti(pchar.questTemp.piratesLine.crewHero) > 5) pchar.questTemp.piratesLine.crewHero = 5;
		pchar.questTemp.piratesLine.crewRichard = 3;   //запомним кол-во десанта от Соукинса
		//бойцы ГГ. предположительно ГГ имет 3 абордажника
		SetCrewQuantity(pchar, GetMinCrewQuantity(pchar)); //минимальную команду на шип
		iTemp = sti(pchar.questTemp.piratesLine.crewHero) ; //число обычных солдат ГГ
		arrayNPCModelHow = 0;
        for (i=1; i<=iTemp; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("MHpirate_"+i, "pirate_"+(rand(15)+1), "man", "man", sti(pchar.rank), PIRATE, -1, true));
			SetNPCModelUniq(sld, "pirate", MAN);
			//watch_quest_moment; либо вообще сейлоров
            LAi_SetWarriorType(sld);
			TakeNItems(sld,"potion1", rand(2)+1);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto12");
        }	
        for (i=1; i<=iTemp; i++) //мушкетеры ГГ
        {
            sld = GetCharacter(NPC_GenerateCharacter("MHmush_"+i, "mush_ctz_"+(rand(2)+7), "man", "mushketer", sti(pchar.rank), PIRATE, -1, false)); //watch_quest_moment
            LAi_SetWarriorType(sld);
			TakeNItems(sld,"potion1", rand(2)+1);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto12");
        }
		//бойцы Соукинса
		iTemp = sti(pchar.questTemp.piratesLine.crewRichard) ; //число обычных солдат Соукинса
		arrayNPCModelHow = 0;
        for (i=1; i<=iTemp; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("RSpirate_"+i, "pirate_"+(rand(15)+1), "man", "man", 25, PIRATE, -1, true));
			SetNPCModelUniq(sld, "pirate", MAN);
            LAi_SetWarriorType(sld);
			TakeNItems(sld,"potion1", rand(2)+1);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto2");
		}
        for (i=1; i<=iTemp; i++) //мушкетеры Соукинса
        {
            sld = GetCharacter(NPC_GenerateCharacter("RSmush_"+i, "mush_ctz_"+(rand(2)+10), "man", "mushketer", 25, PIRATE, -1, false));
            LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, false);
			TakeNItems(sld,"potion1", rand(2)+1);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto2");
		}
		//офицеры Соукинса
        for (i=1; i<=3; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("RSofficer_"+i, "citiz_"+(rand(9)+51), "man", "man", 30, PIRATE, -1, true)); //watch_quest_moment
            FantomMakeCoolFighter(sld, 30, 90, 90, "blade28", "pistol4", 100);
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
            ChangeCharacterAddressGroup(sld, "Shore48", "goto",  "goto4");
		}
		//сам Соукинс
		sld = characterFromId("Richard_Soukins");
		sld.dialog.currentNode = "Shore48";
		LAi_SetImmortal(sld, false);
		LAi_NoRebirthEnable(sld);
		GiveItem2Character(sld, "blade23");
		EquipCharacterbyItem(sld, "blade23");
		GiveItem2Character(sld, "pistol4");
		EquipCharacterbyItem(sld, "pistol4");
		TakeNItems(sld,"potion1", 5);
		RemoveCharacterCompanion(pchar, sld); //убираем Соукинса из компаньонов
		ChangeCharacterAddressGroup(sld, "Shore48", "goto", "goto11");	
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
		LAi_ActorDialog(sld, pchar, "", -1.0, 0);
		AddLandQuestmark_Main(sld, "Pir_Line");
		//прерывание на вход в джанглы
		pchar.Quest.PQ8_jungle_05.win_condition.l1 = "location";
		pchar.Quest.PQ8_jungle_05.win_condition.l1.location = "Panama_jungle_05";
		pchar.Quest.PQ8_jungle_05.function = "PQ8_jungle_05";
	}
	else
	{	//ГГ не успел или не туда зашёл -->
		iTemp = GetCharacterIndex("Richard_Soukins");
		if (iTemp != -1)
		{
			if(IsCompanion(&characters[iTemp]))  
			{
				RemoveCharacterCompanion(pchar, &characters[iTemp]);
			}                   
			LAi_SetHuberType(&characters[iTemp]);
			LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
            ChangeCharacterAddressGroup(&characters[iTemp], "PuertoPrincipe_townhall", "sit", "sit1");
            characters[iTemp].dialog.currentnode = "First time";
        }
        //Возвращаем на место Джекмена
		iTemp = GetCharacterIndex("Jackman");
		if (iTemp != -1)
		{              
			LAi_SetHuberType(&characters[iTemp]);
			LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
            ChangeCharacterAddressGroup(&characters[iTemp], "Pirates_townhall", "sit", "sit1");
            characters[iTemp].dialog.currentnode = "First time";
        }
        iTemp = GetCharacterIndex("John Morris");
        if (iTemp != -1 && CheckAttribute(&TEV, "JohnMorrisIsLifeInHouse"))
        {
            if(IsCompanion(&characters[iTemp]))
            {
                RemoveCharacterCompanion(pchar, &characters[iTemp]);
            }
            ChangeCharacterAddressGroup(&characters[iTemp], "PortSpein_houseF2", "sit", "sit1");
            LAi_SetHuberType(characterfromID("John Morris"));
            characters[iTemp].dialog.currentnode = "I_know_you_good";
        }
		AddQuestRecord("Pir_Line_8_Panama", "6");
		AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("ся","ась"));
		AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("","а"));
		CloseQuestHeader("Pir_Line_8_Panama");
		SetTimerFunction("PQ8_openPanama", 0, 0, 40);
		LocatorReloadEnterDisable("Shore48", "reload1_back", true); //закрывем подходы к Панаме
		LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", true);
		pchar.questTemp.piratesLine = "over";
	}
}

void PQ8_jungle_05(string qName)
{ 
	int iTemp, i;
	string sTemp;
	chrDisableReloadToLocation = true;
	pchar.questTemp.piratesLine = "Panama_inJungle";
	//--------------------------- наши ------------------------------
	//расставляем бойцов ГГ
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc5");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc6");
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc7");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc8");
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+i);
		}
	}
	//сам Соукинс
	iTemp = GetCharacterIndex("Richard_Soukins");
	ref sld;
	if(iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
	{
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc0");
	}
    //--------------------------- испанцы ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=12; i<=18; i++) //max - 21
    {
        sTemp = "sold_spa_"+(rand(7)+9);
		if (i==16) sTemp = "off_spa_6";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));       
		FantomMakeCoolFighter(sld, sti(pchar.rank), 80, 80, "blade34", "pistol6", 80);
		sld.BreakTmplAndFightGroup = true;
		LAi_SetActorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	iTemp = 8;
	if (MOD_SKILL_ENEMY_RATE < 5) iTemp = 6;
    if (MOD_SKILL_ENEMY_RATE == 1) iTemp = 3;
	for (i=1; i<=iTemp; i++) //max - 11
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(3)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_jungle_afterFight");
	pchar.Quest.PQ8_jungle_04.win_condition.l1 = "location";
	pchar.Quest.PQ8_jungle_04.win_condition.l1.location = "Panama_jungle_04";
	pchar.Quest.PQ8_jungle_04.function = "PQ8_jungle_04";
}


void PQ8_jungle_04(string qName)
{ 
	chrDisableReloadToLocation = true;
	pchar.questTemp.piratesLine = "Panama_inJungle";
	//--------------------------- наши ------------------------------
	//расставляем бойцов ГГ
	int iTemp, i;
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc5");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc6");
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc7");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc8");
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+i);
		}
	}
	//сам Соукинс
	ref sld;
	iTemp = GetCharacterIndex("Richard_Soukins");
	if(iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
	{
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc0");
	}
    //--------------------------- испанцы ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	string sTemp;
	for (i=11; i<=13; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+9);
		if (i==14) sTemp = "off_spa_6";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));      
        FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 100);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	for (i=14; i<=17; i++) //индейцы
    {
        if (i==14 || i==16) sTemp = "indsair2";
		else sTemp = "indsar1";
		sld = GetCharacter(NPC_GenerateCharacter("IndEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true)); //TODO анимация
		sld.indian = "1";
		FantomMakeCoolFighter(sld, Rank, 90, 90, "topor2", "", 5);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	iTemp = 10;
	if (MOD_SKILL_ENEMY_RATE < 5) iTemp = 7;
    if (MOD_SKILL_ENEMY_RATE == 1) iTemp = 4;
    for (i=1; i<=iTemp; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(3)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_jungle_afterFight");
	pchar.Quest.PQ8_jungle_03.win_condition.l1 = "location";
	pchar.Quest.PQ8_jungle_03.win_condition.l1.location = "Panama_jungle_03";
	pchar.Quest.PQ8_jungle_03.function = "PQ8_jungle_03";
}

void PQ8_jungle_03(string qName)
{ 
	chrDisableReloadToLocation = true;
	pchar.questTemp.piratesLine = "Panama_inJungle";
	//--------------------------- наши ------------------------------
	//расставляем бойцов ГГ
	int iTemp, i;
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc5");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc6");
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc7");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc8");
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+i);
		}
	}
	//сам Соукинс
	iTemp = GetCharacterIndex("Richard_Soukins");
	ref sld;
	if(iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
	{
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc0");
	}
    //--------------------------- испанцы ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	string sTemp;
	for (i=11; i<=16; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+9);
		if (i==13) sTemp = "off_spa_6";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
		FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);
		sld.BreakTmplAndFightGroup = true;
		LAi_SetActorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
	iTemp = 10;
	if (MOD_SKILL_ENEMY_RATE < 5) iTemp = 7;
    if (MOD_SKILL_ENEMY_RATE == 1) iTemp = 4;
    for (i=1; i<=iTemp; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(3)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		sld.MusketerDistance = 0;
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_jungle_afterFight");
	pchar.Quest.PQ8_ExitTown.win_condition.l1 = "location";
	pchar.Quest.PQ8_ExitTown.win_condition.l1.location = "Panama_ExitTown";
	pchar.Quest.PQ8_ExitTown.function = "PQ8_ExitTown";
}

void PQ8_ExitTown(string qName)
{ 
	int i;
	ref sld;
	int iTemp = GetCharacterIndex("Richard_Soukins");
	if(LAi_IsDead(&characters[iTemp]))
	{	//Соукинс мёртв, задание выполнено
		AddQuestRecord("Pir_Line_8_Panama", "7");	
		pchar.questTemp.piratesLine = "Panama_RichardGoodWork";
	}
	else
	{	//Соукинс жив, задание провалено
		AddQuestRecord("Pir_Line_8_Panama", "8");	
		pchar.questTemp.piratesLine = "Panama_RichardBadWork";
		sld = &characters[iTemp];
		LAi_SetCurHPMax(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc2");
		RemoveLandQuestmark_Main(sld, "Pir_Line");
	}
	chrDisableReloadToLocation = true;
//	pchar.questTemp.piratesLine = "Panama_inExitTown"; // Warship FIX 19.07.09 - Затирало флаг по Соукинсу
	//--------------------------- наши ------------------------------
	//расставляем бойцов ГГ
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc15");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc16");
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc17");
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc18");
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].lifeDay = 10;
			SaveCurrentNpcQuestDateParam(&characters[iTemp], "LifeTimeCreate");
			LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "rld",  "loc"+(i+10));
		}
	}
    //--------------------------- люди Моргана ------------------------------
	arrayNPCModelHow = 0;
    for (i=1; i<=5; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("HMpirate_"+i, "pirate_"+(rand(15)+1), "man", "man", 25, PIRATE, 10, true)); //watch_quest_moment
		SetNPCModelUniq(sld, "pirate", MAN);
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc20");
	}
    for (i=1; i<=5; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("HMmush_"+i, "mush_ctz_"+(rand(2)+7), "man", "mushketer", 25, PIRATE, 10, false)); //watch_quest_moment
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc19");
	}
    //--------------------------- испанцы ------------------------------
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	string sTemp;
	for (i=11; i<=15; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+9);
		if (i==12) sTemp = "off_spa_6";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, -1, true));
        FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
    }
    for (i=1; i<=10; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(3)+1), "man", "mushketer", Rank, SPAIN, -1, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);		
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "aloc"+i);
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "PQ8_ExitTown_afterFight");
}

void PQ8_piratesInPanama(string qName)
{
	DeleteAttribute(&colonies[FindColony("PortoBello")], "notCaptured"); //Портобело можно себе
	DeleteAttribute(&colonies[FindColony("Panama")], "notCaptured");	 //Панаму можно себе, если взят Портобело
	//фантома мэра Панамы в резиденцию
	ref rCharacter = characterFromId("Panama_Mayor");
	ref sld = GetCharacter(NPC_GenerateCharacter("FantomMayor", rCharacter.model, "man", "man", sti(rCharacter.rank), sti(rCharacter.nation), -1, false));
	sld.quest.type = "hovernor";
	sld.City = "Panama";
	sld.location = "Panama_TownhallRoom";
	sld.greeting = "spa_gov_common";
	sld.location.group = "goto";
	sld.location.locator = "goto5";
    sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
	sld.Dialog.CurrentNode = "PQ8_Mayor";
	LAi_SetStayType(sld);
	LAi_LoginInCaptureTown(sld, true);
	//--------------------------- наши ------------------------------
	//расставляем бойцов ГГ
	int iTemp, i;
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_PirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_PirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_RsPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_RsPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_RsPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
	}
    //--------------------------- люди Моргана ------------------------------
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMpirate_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_MPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
	}
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMmush_"+i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			LAi_warrior_DialogEnable(sld, true);
			LAi_LoginInCaptureTown(sld, true);
			sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
			sld.Dialog.CurrentNode = "PQ8_MPirInPan";
			PlaceCharacter(sld, "goto", pchar.location);
		}
	}
}	

void PQ8_MorganInPanama_1(string qName)
{
	float locx, locy, locz;
	chrDisableReloadToLocation = true;
	//делаем видимым ключ
	ref sld = ItemsFromID("keyPanama");
	sld.shown = true;
	sld.startLocation = "Panama_ammo";
	sld.startLocator = "item1";
	//Моргана в город и на диалог
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = characterFromId("Henry Morgan");
	sld.dialog.currentNode = "PL_Q8_Panama1";
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto6");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PL_Q8_ResEnterBox(string qName)
{
	if (CheckCharacterItem(pchar, "keyPanama"))
    {
		TakeItemFromCharacter(pchar, "keyPanama");
		SetBan("Exchange", 1);
		chrDisableReloadToLocation = true;
		ref sld = characterFromId("Henry Morgan");
		sld.dialog.currentNode = "PL_Q8_Panama2";		
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		LAi_ActorDialog(sld, pchar, "", -1, 0);

		TEV.BlockMoneyAchievements = true;
	}
	else
	{
		Pchar.quest.PL_Q8_ResEnterBox_2.win_condition.l1 = "ExitFromLocation";
        Pchar.quest.PL_Q8_ResEnterBox_2.win_condition.l1.location = pchar.location;
        Pchar.quest.PL_Q8_ResEnterBox_2.function = "PL_Q8_ResEnterBox_2";
	}
}

void PL_Q8_ResEnterBox_2(string qName)
{
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1 = "locator";
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.location = "Panama_TownhallRoom";
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator_group = "box";
	pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator = "private1";
	pchar.quest.PL_Q8_ResEnterBox.function = "PL_Q8_ResEnterBox";
}

void PL_Q8_inPanamaFort2(string qName)
{
	Pchar.quest.PL_Q8_inPanamaPirates_1.win_condition.l1 = "location";
	Pchar.quest.PL_Q8_inPanamaPirates_1.win_condition.l1.location = "Panama_town";
	Pchar.quest.PL_Q8_inPanamaPirates_1.function = "PL_Q8_inPanamaPirates_1";
}

void PL_Q8_inPanamaPirates_1(string qName)
{
	ref sld;
	int iTemp, i;
	float locx, locy, locz;
	chrDisableReloadToLocation = true;
	//--------------------------- меняем ноды у оставшихся пиратов ------------------------------
	//расставляем бойцов ГГ
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewHero); i++)
    {
        iTemp = GetCharacterIndex("MHmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    //расставляем бойцов Соукинса
	for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    for (i=1; i<=sti(pchar.questTemp.piratesLine.crewRichard); i++)
    {
        iTemp = GetCharacterIndex("RSmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
    }
    //офицеры Соукинса
	for (i=1; i<=3; i++)
    {
        iTemp = GetCharacterIndex("RSofficer_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
	}
    //--------------------------- люди Моргана ------------------------------
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMpirate_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
	}
    for (i=1; i<=5; i++)
    {
        iTemp = GetCharacterIndex("HMmush_"+i);
		if(iTemp != -1)
		{
			characters[iTemp].Dialog.CurrentNode = "PQ8_FackMorgan";
		}
	}	
	//разговорный барон пират
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sld = GetCharacter(NPC_GenerateCharacter("John Morris", "John_Morris", "man", "man", 25, PIRATE, 0, true));
	sld.name 	= FindPersonalName("JohnMorris_name");
    sld.lastname = FindPersonalName("JohnMorris_lastname");
	sld.Dialog.Filename = "Quest\PiratesLine_dialog.c";
	sld.dialog.currentNode = "PL_Q8_QFackMorgan";
	LAi_LoginInCaptureTown(sld, true);
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto10");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PL_Q8_backFight_1(string qName) 
{
    ref sld;
    int i;
    string sTemp;
    int Rank = sti(pchar.rank) - 5 + MOD_SKILL_ENEMY_RATE;
	if (Rank < 1) Rank = 1;
	for (i=1; i<=8; i++)
    {
        sTemp = "sold_spa_"+(rand(7)+9);
		if (i==2) sTemp = "off_spa_5";
 		sld = GetCharacter(NPC_GenerateCharacter("SpaEnemy_"+i, sTemp, "man", "man", Rank, SPAIN, 12, true));
		FantomMakeCoolFighter(sld, sti(pchar.rank), 90, 90, "blade26", "pistol4", 120);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc1");
    }
    for (i=1; i<=4; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SpaMush_"+i, "spa_mush_"+(rand(3)+1), "man", "mushketer", Rank, SPAIN, 12, false));
		if (MOD_SKILL_ENEMY_RATE > 5) TakeNItems(sld,"potion1", rand(MOD_SKILL_ENEMY_RATE)+1);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "loc3");
	}
	//стравливаем
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Пиратская линейка     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Миниквесты        начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
// ----------------- Переспать с официанткой ---------------------
void WaitressFack_null(string qName) //нулим квест официантки
{
	LocatorReloadEnterDisable(pchar.questTemp.different.FackWaitress.City + "_tavern", "reload2_back", true);
	pchar.questTemp.different = "free";
	pchar.quest.WaitressFack_inRoom.over = "yes";
	DeleteAttribute(pchar, "questTemp.different.FackWaitress");
}

void WaitressFack_inRoom(string qName)
{
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable(locations[reload_location_index].fastreload + "_tavern", "reload2_back", true);
	DoQuestFunctionDelay("WaitressFack_Enter", 10.0 + frand(10.0));
}

void WaitressFack_Enter(string qName)
{	
	ref sld;
	int iTemp, i;
	LAi_group_Delete("EnemyFight");
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	if (pchar.questTemp.different.FackWaitress.Kick == "0")
	{	//подстава
		iTemp = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE);
		sld = GetCharacter(NPC_GenerateCharacter("BerglarWairessQuest", "citiz_"+(rand(9)+51), "man", "man", iTemp, PIRATE, -1, true)); //watch_quest_moment
		FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor2", "pistol6", 50);
		sld.dialog.Filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "WaitressBerglar";	
		sld.greeting = "Enc_Raiders";
 		//меняем обличие официантки
		ref rCharacter = characterFromId(locations[reload_location_index].fastreload + "_waitress");
		rCharacter.model = "women_" + (rand(11)+1);
		SetRandomNameToCharacter(rCharacter);
		FaceMaker(rCharacter);  
	}
	else
	{
        sld = characterFromId("WairessQuest");
	}
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void WaitressFack_outRoom()
{
	// ==> Забираем клинки, пистоли и деньги.
	ref sld = characterFromId("BerglarWairessQuest");
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
    while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "")
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));
    while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")        
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
    while (FindCharacterItemByGroup(pchar, MUSKET_ITEM_TYPE) != "")        
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, MUSKET_ITEM_TYPE));
    pchar.money = 0;
    // <== Забираем клинки, пистоли и деньги.
	AddCharacterExpToSkill(pchar, "Pistol", 100);
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
	pchar.questTemp.different = "FackWaitress_noMoney"; //флаг ограбили
}

void WaitressFack_fight()
{
	AddCharacterExpToSkill(pchar, "FencingLight", 30);
	AddCharacterExpToSkill(pchar, "Fencing", 30);
	AddCharacterExpToSkill(pchar, "FencingHeavy", 30);
	LAi_SetFightMode(pchar, true);
	pchar.questTemp.different = "FackWaitress_fighted"; //флаг пришлось подраться
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	pchar.quest.WaitressFack_afterFight.win_condition.l1 = "NPC_Death";
	pchar.quest.WaitressFack_afterFight.win_condition.l1.character = "BerglarWairessQuest";
	pchar.quest.WaitressFack_afterFight.win_condition = "OpenTheDoors";
}

void WaitressFack_fack()
{
	pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
	DoQuestCheckDelay("PlaySex_1", 1.0);
	pchar.questTemp.different = "FackWaitress_facking";
}

// ----------------- Пожертвование хозяйки борделя ---------------------
void HostessChurch_null(string qName) //нулим квест 
{
	//если квест ещё взят, то деньги считай прикарманены
	if (characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch == "taken") 
	{
		characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "baster";
	}
	pchar.questTemp.different = "free";
	DeleteAttribute(pchar, "questTemp.different.HostessChurch");
}

// ----------------- Украсть чертежи на верфи ---------------------
void ShipyardsMap_returnCFN(string qName) 
{
	string  sName;
	aref	arDis, arRld;
	int location_index = FindLocation(pchar.questTemp.different.ShipyardsMap.city + "_town");
    makearef(arRld, Locations[location_index].reload);
    int		Qty = GetAttributesNum(arRld);
    for (int a=0; a<Qty; a++)
    {
    	arDis = GetAttributeN(arRld, a);
		sName = arDis.go;
    	if (HasSubStr(sName, "_shipyard"))
    	{
			arDis.close_for_night = true;
			break;
    	}
    }
	LocatorReloadEnterDisable(pchar.questTemp.different.ShipyardsMap.city + "_shipyard", "reload2", false);
}

// ----------------- Найти кольцо мэра в борделе ---------------------
void TakeMayorsRing_null(string qName) //нулим квест 
{
	pchar.questTemp.different = "free";
	if (CheckCharacterItem(pchar, "MayorsRing"))
    {
		TakeItemFromCharacter(pchar, "MayorsRing");
		AddQuestRecord("SeekMayorsRing", "4");
		AddQuestUserData("SeekMayorsRing", "sSex", GetSexPhrase("","а"));
		AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + pchar.questTemp.different.TakeMayorsRing.city + "Gen"));
		CloseQuestHeader("SeekMayorsRing");
		ChangeCharacterReputation(pchar, -3);
	}
	else
	{
		if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
		{
			AddQuestRecord("SeekMayorsRing", "5");
			AddQuestUserData("SeekMayorsRing", "sSex", GetSexPhrase("ёл","ла"));
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + pchar.questTemp.different.TakeMayorsRing.city + "Gen"));
			CloseQuestHeader("SeekMayorsRing");
			ChangeCharacterReputation(pchar, -5);
		}
	}
	DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
}

// ----------------- Спихнуть судовые бумаги ---------------------
void GiveShipLetters_null(string qName) //нулим квест 
{
	pchar.questTemp.different = "free";
	DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
}

void CheckShipLetters(string qName)
{	
	if (!CheckCharacterItem(pchar, "CaptainBook"))
	{
		Log_QuestInfo(StringFromKey("InfoMessages_36"));
		ref sld = ItemsFromID("CaptainBook");
		sld.shown = false;
		pchar.questTemp.different = "free";
		pchar.questTemp.different.GiveShipLetters.over = "yes"; //снимаем таймер 
		DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
	}
}
// ----------------- Спихнуть судовые бумаги ---------------------

// ----------------- Развод на секс хозяйки борделя ---------------------
void SexWithHostess_null(string qName) //нулим квест 
{
	ref sld;
	if (pchar.questTemp.different.HostessSex == "toRoom")
	{
		sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
		ChangeCharacterAddressGroup(sld, pchar.questTemp.different.HostessSex.city + "_SecBrRoom", "goto", "goto8");
		LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", true);
	}
	LAi_SetOwnerTypeNoGroup(sld);
	sld.dialog.currentnode = "First time";
	sld.quest.NotGoneToSex = true; //не пришёл. Секса больше не будет
	DeleteAttribute(pchar, "questTemp.different.HostessSex");
	pchar.questTemp.different = "free";
}

void SexWithHostess_goToRoom()  
{
	chrDisableReloadToLocation = true;
	ref sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", pchar.questTemp.different.HostessSex.city + "_Brothel_room", "goto", "goto3", "OpenTheDoors", -1);
	pchar.quest.SexWithHostess_inRoom.win_condition.l1 = "location";
	pchar.quest.SexWithHostess_inRoom.win_condition.l1.location = pchar.questTemp.different.HostessSex.city + "_Brothel_room";
	pchar.quest.SexWithHostess_inRoom.function = "SexWithHostess_inRoom";
	LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", false);
}

void SexWithHostess_inRoom(string qName)
{
	DoQuestFunctionDelay("SexWithHostess_inRoom_2", 1.5);
	LocatorReloadEnterDisable(pchar.questTemp.different.HostessSex.city + "_Brothel", "reload2_back", true);
}

void SexWithHostess_inRoom_2(string qName)
{
	ref sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
	sld.dialog.currentnode = "Hostess_inSexRoom";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void SexWithHostess_fack()
{
	pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1;
	DoQuestCheckDelay("PlaySex_1", 1.0);
	pchar.questTemp.different = "HostessSex";
}

// ----------------- Миниквесты портмана  ---------------------
void SetCapitainFromCityToSea(string qName) //помещаем в море кэпа, который сейчас ошивается в городе
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	ref sld;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId);
	if (capIndex != -1)
	{		
		sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		sld.location	= "none";
		sld.location.group = "";
		sld.location.locator = "";
		//в морскую группу кэпа
		string sGroup = "PorpmansShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetType(sGroup,"trade");
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation));
		//записываем данные в структуру кэпа
		sld.quest = "InMap"; //личный флаг рассеянного кэпа
		sld.quest.targetCity = SelectNotEnemyColony(sld); //определим колонию, куда отправится кэп
		sld.quest.stepsQty = sti(sld.quest.stepsQty) + 1; //количество выходов в море
		Log_TestInfo("Рассеянный кэп " + sld.id + " вышел из " + sld.city + " и направился в: " + sld.quest.targetCity);
		//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
		string sTemp = GetArealByCityName(sld.city);
		sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
		//на карту
		int iTemp = GetMaxDaysFromColony2Colony(sld.city, sld.quest.targetCity)+5; //дней доехать даем с запасом
		Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, iTemp);
		//даем общий слух, что кэп ушёл в другой город
		AddSimpleRumourEx(LinkRandPhrase(StringFromKey("Common_rumours_36", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, GetFullName(sld), XI_ConvertString("Colony"+sld.quest.targetCity+"Acc")),
			StringFromKey("Common_rumours_37", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, XI_ConvertString("Colony"+sld.quest.targetCity+"Acc")),
			StringFromKey("Common_rumours_38", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, XI_ConvertString("Colony"+sld.quest.targetCity+"Acc"), GetFullName(sld))),
			sld.city, iTemp, 1, "PortmansBook_DeliveryToCap", sld.id);
		//--> запись инфы по кэпу в базу местного портмана
		sTemp = sld.id; //Id кэпа, который оставил отметку
		ref rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //куда отправился
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //запишем дату, когда отправился
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery    #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = characters[GetCharacterIndex(sld.quest.firstCity + "_PortMan")].id + "PortmansBook_Delivery";
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "PortmansBook_Delivery";
		rCharacter.quest.capitainsList.(sTemp).QBQty = 5;
		//перезаносим время в базу кэпов
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

void SetRobberFromSeaToMap(string qName) //помещаем в море кэпа-вора, который счас стоит на рейде в порту
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId);
	if (capIndex != -1)
	{		
		ref sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		//в морскую группу кэпа
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation));
		//записываем данные в структуру кэпа
		sld.quest = "InMap"; //личный флаг рассеянного кэпа
		sld.quest.targetCity = SelectAnyColony2(sld.city, sld.quest.cribCity); //определим колонию, куда отправится кэп
		Log_TestInfo("Кэп-вор " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
		//на карту
		int iTemp = GetMaxDaysFromColony2Colony(sld.quest.targetCity, sld.city)+5; //дней доехать даем с запасом
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, iTemp);
		//даем общий слух, что кэп ушёл в другой город
		AddSimpleRumourEx(LinkRandPhrase(StringFromKey("Common_rumours_36", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, GetFullName(sld), XI_ConvertString("Colony"+sld.quest.targetCity+"Acc")),
			StringFromKey("Common_rumours_37", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, XI_ConvertString("Colony"+sld.quest.targetCity+"Acc")),
			StringFromKey("Common_rumours_38", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, XI_ConvertString("Colony"+sld.quest.targetCity+"Acc"), GetFullName(sld))),
			sld.city, iTemp, 1, "Portmans_SeekShip_rum", sld.id);
		//--> запись инфы по кэпу в базу местного портмана
		string sTemp = sld.id; //Id кэпа, который оставил отметку
		ref rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //куда отправился
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //запишем дату, когда отправился
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery    #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")].id + "Portmans_SeekShip";
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "Portmans_SeekShip";
		rCharacter.quest.capitainsList.(sTemp).QBQty = 2;
		//перезаносим время в базу кэпов
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

void SeekShip_checkAbordage(string qName) //кэп-вор успешно абордирован
{	
	//смотрим, взят корабль себе или потоплен
	int iTemp;
	ref sld = characterFromId(pchar.quest.(qName).CapId);
	ref rCharacter = &characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")];
	bool bOk = false;
	for (int i=0; i<=COMPANION_MAX; i++)
	{
		iTemp = GetCompanionIndex(pchar, i);
		if(iTemp != -1)
		{
			sld = &characters[iTemp];
			if (sld.ship.name == rCharacter.quest.PortmansSeekShip.shipName && 
				RealShips[sti(sld.ship.type)].BaseName == rCharacter.quest.PortmansSeekShip.shipTapeName &&
				RealShips[sti(sld.Ship.Type)].basetype == rCharacter.quest.PortmansSeekShip.shipTape)
			{
				bOk = true;
				break;
			}
		}
	}	
	//решение по результатам проверки
	sld = characterFromId(pchar.quest.(qName).CapId);
	string sTemp = "SeekShip_checkSink" + rCharacter.index;
	pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на утонул
	if (bOk)
	{		
		rCharacter.quest = "SeekShip_success"; //флаг успешного взятия на абордаж
		sTemp = rCharacter.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTemp, "Portmans_SeekShip", "5");
	}
	else
	{
		rCharacter.quest = "SeekShip_sink"; //флаг утопления судна, провал квеста
		sTemp = rCharacter.id + "Portmans_SeekShip";
		AddQuestRecordEx(sTemp, "Portmans_SeekShip", "9");
	}
}

void SeekShip_checkSink(string qName)
{
	ref sld = characterFromId(pchar.quest.(qName).CapId);
	ref rCharacter = &characters[GetCharacterIndex(sld.quest.cribCity + "_PortMan")];
	rCharacter.quest = "SeekShip_sink"; //флаг утопления судна, провал квеста
	string sTemp = rCharacter.id + "Portmans_SeekShip";
	AddQuestRecordEx(sTemp, "Portmans_SeekShip", "8");
	sTemp = "SeekShip_checkAbordage" + rCharacter.index;
	pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
}

// ----------------- ночной сторож в церкви ---------------------
void ChurchNightGuard_exitFromLoc(string qName)
{
	string sTemp;
	DeleteAttribute(pchar, "PostEventQuest.questDelay.ChurchNightGuard_timerInChurch"); //снимаем таймер на отработку действия
	if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) >= 3)
	{
		sTemp = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
		AddQuestRecordEx(sTemp, "Church_NightGuard", "4");
		AddQuestUserData(sTemp, "sSex", GetSexPhrase("","а"));
	}
	else
	{
	    ///если перезаписывать дату, то GetQuestPastDayParam() будет всегда возвращать 0,
	    ///так как разницы между сохраненной и фактической не будет
		/*if (GetTime() > 6.0 && GetTime() < 23.99)
		{
			//SaveCurrentQuestDateParam("questTemp.different.Church_NightGuard"); //перезапишем дату
		}*/
		if (GetTime() > 0.0 && GetTime() < 6.0)
		{
			sTemp = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			AddQuestRecordEx(sTemp, "Church_NightGuard", "3");
			AddQuestUserData(sTemp, "sSex", GetSexPhrase("","а"));
			AddQuestUserData(sTemp, "sSex1", GetSexPhrase("ен","на"));
			CloseQuestHeader(sTemp);
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard"); //снимаем флаг
			ChangeCharacterReputation(pchar, -20);
		}
	}
}

void ChurchNightGuard_timerInChurch(string qName)
{
    int iRank, num;
    int iQuestPastDay = GetQuestPastDayParam("questTemp.different.Church_NightGuard");
    if (iQuestPastDay > 0) pchar.questTemp.different.Church_NightGuard.NightQty = iQuestPastDay + 1;
	if (pchar.questTemp.different.Church_NightGuard.chance == pchar.questTemp.different.Church_NightGuard.NightQty)
	{	//грабители лезут
		pchar.quest.ChurchNightGuard_exitFromLoc.over = "yes"; //снимаем прерывание на выход из локации
		pchar.questTemp.different.Church_NightGuard.NightQty = 3; //присвоим максимум дней дежурства
		pchar.questTemp.different.Church_NightGuard.fight = true; //флаг боевки
        chrDisableReloadToLocation = true; // закрыть выход из локации.
		string sTemp = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
		AddQuestRecordEx(sTemp, "Church_NightGuard", "5");		
        LAi_group_Delete("EnemyFight");
		//--> генерим ранг 
		num = rand(1)+2;
		if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*2.5/num);
		else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE*1.6/num);
	
		//<-- генерим ранг
		ref sld;
		for (int i=1; i<=num; i++)
        {
            sld = GetCharacter(NPC_GenerateCharacter("Bandit"+i, "officer_"+(i+7), "man", "man", iRank, PIRATE, 0, true)); //watch_quest_moment; TODO: подборку бандитов
			SetFantomParamFromRank(sld, iRank, true);         
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
			LAi_warrior_DialogEnable(sld, false);
            LAi_group_MoveCharacter(sld, "EnemyFight");
            ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
        }
		sld.Dialog.Filename = "Quest\ForAll_dialog.c";
		sld.dialog.currentnode = "ChurchBerglar";
		GiveItem2Character(sld, "Chest");
		sld.SaveItemsForDead  = true;
		sld.DontClearDead = true;
        LAi_SetActorTypeNoGroup(sld);
		LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	}
	else
	{	//нету никого
        SetLaunchFrameFormParam(StringFromKey("InfoMessages_13"), "ChurchNightGuard_timerInChurch_2", 0, 3);
        LaunchFrameForm();
        RecalculateJumpTable();
        Log_TestInfo("Кол-во ночей в охране: " + pchar.questTemp.different.Church_NightGuard.NightQty);
	}
}
// --> Вернул удаленную часть кода Hirurg39
// ----------------- поиск кэпов, дача квеста горожанином ---------------------
void SCQ_seekCapIsDeath(string qName)
{	
	string sTitle, sGroup, sTemp;
	ref sld = characterFromId(pchar.quest.(qName).CapId); //капитан
	ref rCharacter = &characters[GetCharacterIndex("QuestCitiz_" + sld.quest.cribCity)]; //горожанин-квестодатель
	//чистим базу нпс-кэпов  -->
	aref forName;
	makearef(forName, NullCharacter.capitainBase);
	DeleteAttribute(forName, sld.id);
	//<-- чистим базу нпс-кэпов
	if (rCharacter.quest.SeekCap == "NM_battle")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
		rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
	}
	if (rCharacter.quest.SeekCap == "NM_prisoner")
	{
		if (CheckAttribute(pchar, "GenQuest.mustboarding"))//в каюте при абордаже
		{
			sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
			AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "5");
				AddQuestUserData(sTitle, "sName", rCharacter.quest.SeekCap.name);
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
			rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
				DeleteAttribute(pchar, "GenQuest.mustboarding");
		}
		else
		{
			sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
			sld.lifeDay = 0;
			Map_ReleaseQuestEncounter(sld.id);
			sGroup = "SeekCapShip_" + sld.index;
			group_DeleteGroup(sGroup);
			sTemp = "SecondTimer_" + sld.id;
			pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
			sTemp = "SCQ_" + rCharacter.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
			if (CheckAttribute(sld, "quest.release")) //если кэп сам отдал пассажира
			{
				AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "5");
				AddQuestUserData(sTitle, "sName", rCharacter.quest.SeekCap.name);
				AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
				rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
			}
			else
			{
				rCharacter.lifeDay = 0;
				AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "4");
				CloseQuestHeader(sTitle);
			}
		}
	}
	if (rCharacter.quest.SeekCap == "NM_peace")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		sld.lifeDay = 0;
		Map_ReleaseQuestEncounter(sld.id);
		sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		sTemp = "SecondTimer_" + sld.id;
		pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
		sTemp = "SCQ_" + rCharacter.index;
		pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "4");
		CloseQuestHeader(sTitle);
	}
	if (rCharacter.quest.SeekCap == "manSlave")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "4");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
		rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
		rCharacter.greeting = "cit_complete";
	}
	if (sld.quest.SeekCap == "womanRevengeFight") //проверим флаг боя на улице, уже можно валить
	{
		sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + rCharacter.quest.SeekCap, "5");
		AddQuestUserData(sTitle, "sCapName", GetFullName(sld));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + rCharacter.city + "Acc"));
		rCharacter.quest.SeekCap = rCharacter.quest.SeekCap + "over"; //дополняем флаг квест до 'выполнен'
		sTemp = "SecondTimer_" + sld.id;
		pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
		sTemp = "SCQ_" + rCharacter.index;
		pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
	}
	if (sld.quest.SeekCap == "womanHasband" || rCharacter.quest.SeekCap == "manRapeWife" || sld.quest.SeekCap == "manFriend" || sld.quest.SeekCap == "womanRevenge" || rCharacter.quest.SeekCap == "womanPirates")
	{
		sTitle = sld.quest.cribCity + "SCQ_" + sld.quest.SeekCap;
		AddQuestRecordEx(sTitle, "SCQ_" + sld.quest.SeekCap, "4");
		sld.lifeDay = 0;
		Map_ReleaseQuestEncounter(sld.id);
		sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		sTemp = "SecondTimer_" + sld.id;
		pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
		sTemp = "SCQ_" + rCharacter.index;
		pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть квестодателя
		sTitle = sld.quest.cribCity + "SCQ_" + sld.quest.SeekCap;
		CloseQuestHeader(sTitle);
		// evganat - генераторы
		string sNPCidx = rCharacter.index;
		DeleteAttribute(pchar, "questTemp.SeekCap."+sNPCidx);
		//снимаем горожанку-маньячку
		if (sld.quest.SeekCap == "womanRevenge")
		{
			rCharacter.lifeDay = 0;
		}
	}
}
//смерть квестодателя закрывает и чистит квест
void SCQ_CitizenIsDeath(string qName)
{
	ref sld = characterFromId(pchar.quest.(qName).CapId); //капитан
	sld.lifeDay = 0;
	ref rCharacter = characterFromId(pchar.quest.(qName).CitizenId); //горожанин-квестодатель
	//чистим базу нпс-кэпов  -->
	aref forName;
	makearef(forName, NullCharacter.capitainBase);
	DeleteAttribute(forName, sld.id);
	//<-- чистим базу нпс-кэпов
	Map_ReleaseQuestEncounter(sld.id);
	string sGroup = "SeekCapShip_" + sld.index;
	group_DeleteGroup(sGroup);
	string sTemp = "SecondTimer_" + sld.id;
	pchar.quest.(sTemp).over = "yes"; //снимаем возможно установленный таймер
	sTemp = "SCQ_" + sld.index;
	pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть кэпа
	string sTitle = sld.quest.cribCity + "SCQ_" + rCharacter.quest.SeekCap;
	CloseQuestHeader(sTitle);
	// evganat - генераторы
	string sNPCidx = rCharacter.index;
	DeleteAttribute(pchar, "questTemp.SeekCap."+sNPCidx);
}

void CitizCapFromSeaToMap(string qName) //помещаем на карту кэпа, разыскиваемого горожанами
{
	if (!CheckAttribute(pchar, "quest." + qName + ".CapId")) return;
	int capIndex = GetCharacterIndex(pchar.quest.(qName).CapId);
	if (capIndex != -1)
	{		
		ref sld = &characters[capIndex];
		if (LAi_IsDead(sld)) return;
		ChangeCharacterAddressGroup(sld, "none", "", "");	// evganat
 		sld.nation = sld.quest.nation;
		//в морскую группу кэпа
		string sGroup = "SeekCapShip_" + sld.index;
		group_DeleteGroup(sGroup);
		Group_FindOrCreateGroup(sGroup);
		Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
		Group_LockTask(sGroup);
		Group_AddCharacter(sGroup, sld.id);
		Group_SetGroupCommander(sGroup, sld.id);
		SetRandGeraldSail(sld, sti(sld.Nation));
		//записываем данные в структуру кэпа
		sld.quest = "InMap"; //личный флаг искомого кэпа
		sld.quest.targetCity = SelectAnyColony2(sld.city, sld.quest.cribCity); //определим колонию, куда отправится кэп
		Log_TestInfo("Искомый кэп " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity);
		//на карту
		int iTemp = GetMaxDaysFromColony2Colony(sld.quest.targetCity, sld.city)+5; //дней доехать даем с запасом
		Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, iTemp);
		//даем общий слух, что кэп ушел в другой город
		AddSimpleRumourEx(LinkRandPhrase(StringFromKey("Common_rumours_36", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, GetFullName(sld), XI_ConvertString("Colony"+sld.quest.targetCity+"Acc")),
			StringFromKey("Common_rumours_37", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, XI_ConvertString("Colony"+sld.quest.targetCity+"Acc")),
			StringFromKey("Common_rumours_38", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name, XI_ConvertString("Colony"+sld.quest.targetCity+"Acc"), GetFullName(sld))),
			sld.city, iTemp, 1, "Citiz_SeekCap_rum", sld.id);
		//--> запись инфы по кэпу в базу местного портмана
		string sTemp = sld.id; //Id кэпа, который оставил отметку
		ref rCharacter = &characters[GetCharacterIndex(sld.City + "_PortMan")];
		rCharacter.quest.capitainsList.(sTemp) = sld.quest.targetCity; //куда отправился
		rCharacter.quest.capitainsList.(sTemp).date = GetDateString(); //запишем дату, когда отправился
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery    #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		rCharacter.quest.capitainsList.(sTemp).QBString1 = sld.quest.cribCity + "SCQ_" + characters[GetCharacterIndex("QuestCitiz_"+sld.quest.cribCity)].quest.SeekCap;
		rCharacter.quest.capitainsList.(sTemp).QBString2 = "SCQ_" + characters[GetCharacterIndex("QuestCitiz_"+sld.quest.cribCity)].quest.SeekCap;
		rCharacter.quest.capitainsList.(sTemp).QBQty = 2;
		//меняем сроки проверки по Id кэпа в базе нпс-кэпов
		sTemp = sld.id;
		NullCharacter.capitainBase.(sTemp).checkTime = iTemp + 5;
		NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
		NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
		NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	}
}

//после боевки в каюте. для всех квестов по поисков кэпов ситезанами
void CitizSeekCap_afterCabinFight(string qName)
{	
	float locx, locy, locz;
	ref sld = GetCharacter(NPC_GenerateCharacter(pchar.quest.(qName).label + "_" + pchar.quest.(qName).WifeCity, pchar.quest.(qName).model, "woman", "towngirl", 5, pchar.quest.(qName).nation, -1, false));
	sld.name = pchar.quest.(qName).WifeName;
	sld.lastname = pchar.quest.(qName).WifeLastname;
	sld.dialog.filename   = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = pchar.quest.(qName).label + "_Board";
	sld.quest.SeekCap = pchar.quest.(qName).label;
	sld.quest.cribCity = pchar.quest.(qName).WifeCity;
	LAi_SetStayType(sld);
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
	LAi_SetActorType(pchar);
    LAi_SetActorType(sld);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
}
// <-- Вернул удаленную часть кода Hirurg39

//кораблик с капитаном, который имеет мушкет несчастного мушкетера
void SetMushketFromSeaToMap(string qName)
{
	ref sld = characterFromId("MushketCap");
	//в морскую группу кэпа
	string sGroup = "MushketCapShip";
	Group_FindOrCreateGroup(sGroup);
	Group_SetAddressNone(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("Кэп с мушкетом вышел из: " + sld.city + " и направился в: " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	// sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.worldMapShip = "BrigantineShip";
	sld.mapEnc.Name = FindPersonalName("MushketCap_mapEnc");
	int daysQty = GetMaxDaysFromColony2Colony(sld.quest.targetCity, sld.city)+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//пускаем слух
	SetMushketFromSeaToMap_AddRumour(daysQty);
	//меняем сроки проверки по Id кэпа в базе нпс-кэпов
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

//новый фрегат Даниэль
void SetDanielleFromSeaToMap(string qName)
{
	ref sld = characterFromId("Danielle");
	//в морскую группу кэпа
	string sGroup = "DanielleGroup";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	sld.quest = "InMap"; //личный флаг искомого кэпа
	sld.cityShore = GetIslandRandomShoreId(GetArealByCityName(sld.city));
	sld.quest.targetCity = SelectAnyColony(sld.city); //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("Кэп фрегата Queen вышел из: " + sld.city + " и направился в: " + sld.quest.targetShore);
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	// sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.worldMapShip = "QueenShip";
	sld.mapEnc.Name = FindPersonalName("Danielle_mapEnc");
	int daysQty = GetMaxDaysFromColony2Colony(sld.quest.targetCity, sld.city)+5; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);
	//меняем сроки проверки по Id кэпа в базе нпс-кэпов
	string sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
    NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
    NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
    NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
    //пускаем слух
    if (CheckAttribute(&TEV, "DanielleShipRumourId")) DeleteRumor(FindRumour(sti(TEV.DanielleShipRumourId)));
    string sRumourName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
    TEV.DanielleShipRumourId = AddSimpleRumour(LinkRandPhrase(
        StringFromKey("Common_rumours_42", XI_ConvertString(sld.quest.targetShore + "Gen")),
        StringFromKey("Common_rumours_43", XI_ConvertString(sld.quest.targetShore + "Pre")),
        StringFromKey("Common_rumours_44", sRumourName, XI_ConvertString(sld.quest.targetShore + "Acc"))
    ), 1, daysQty, 1);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   Миниквесты        конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Линейка ГПК           начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void DaytimeOutingLSCFunc()
{
	locCameraFromToPos(72.8, 2.7, -3.7, false, 0.27, -35.9, 100.00);
}

void DaytimeOutingLSCFunc_2()
{
	locCameraFromToPos(64.7, 13.7, 32.0, false, 77.42, -1.85, 1.00);

	ref sld = CharacterFromID("FreeSlave0");
	LAi_tmpl_ani_PlayAnimation(sld, "Shot", -1.0);
	DoQuestFunctionDelay("DaytimeOutingLSCFunc_3", 1.5);
}

void DaytimeOutingLSCFunc_3(string qName)
{
	ref npchar, sld;
	float locx, locy, locz;
	string loc;

	sld = CharacterFromID("FreeSlave0");
	LAi_tmpl_ani_EndAnimation(sld);

	CreateLocationParticles("ShipExplode", "quest", "effect1", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
	CreateLocationParticlesLoopedSound("shipfire", "quest", "effect1", 0.0, 0.0, 0, "fortfire");
	CreateLocationParticlesLoopedSound("shipfire", "quest", "effect1", 0.0, 0.0, 0, "fortfire");
	SetCameraShake(0.5, 5.0, 3.0, 1.2, 0.5, true, false, CAM_EASING_CUBE);
	PlaySound("Voice\" + VoiceGetLanguage() + "\EvilPirates01.wav");

	LAi_ActorTurnToLocator(sld, "quest", "effect1");

	//население реагирует
	for (int i = 0; i<MAX_CHARACTERS; i++)
	{
		makeref(npchar, characters[i]);
		if (npchar.location == "FortOrange_Mine" && CheckAttribute(npchar, "CityType"))
		{
			LAi_SetActorType(npchar);
			if (npchar.CityType == "soldier")
			{
				LAi_ActorAttack(npchar, CharacterFromID("FreeSlave14"), "");
			}
			else
			{
				GetCharacterPos(npchar, &locx, &locy, &locz);
				loc = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
				if (loc != "")
					LAi_ActorRunToLocation(npchar, "reload", loc, "none", "", "", "", 10.0);
				else
					LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", 10.0);

			}
		}
	}

	LAi_tmpl_ani_PlayAnimation(CharacterFromID("TizerDenLSC"), "death_9", -1.0);
	LAi_tmpl_ani_PlayAnimation(CharacterFromID("TizerSlaveLSC"), "death_10", -1.0);
	LAi_tmpl_ani_PlayAnimation(pchar, "death_10", -1.0);
	DoQuestFunctionDelay("DaytimeOutingLSCFunc_4", 2.0);
}

void DaytimeOutingLSCFunc_4(string qName)
{
	LAi_FadeEx(1.0, 2.0, 1.0, "DaytimeOutingLSCFunc_7", "DaytimeOutingLSCFunc_8", "");
}

void DaytimeOutingLSCFunc_7(string qName)
{
	int i, j;
	ref npchar;
	string sTemp;
	LAi_tmpl_ani_PlayAnimation(pchar, "Ground_StandUp", -1.0);

	WaitDate("", 0, 0, 0, 6, 0);
	RecalculateJumpTable();
	RefreshLandTime();
	RefreshWeather();

	//почти все негры уходят
	for (i = 0; i < 15; i++)
	{
		npchar = CharacterFromID("FreeSlave"+i);
		LAi_SetImmortal(npchar, false);
		if (i == 4 || i == 11 || i == 14) continue; //парочку трупов оставляем
		ChangeCharacterAddress(npchar, "none", "");
	}
	//создаем массовку
	for (i = 1; i<21; i++)
	{
		if (i > 5 && i < 9) continue; //скипаем локаторы на склонах что бы трупы не висели в воздухе
		if (rand(2) == 0)
			sTemp = "rivados";
		else
			sTemp = "slaves";
		npchar = GetCharacter(NPC_GeneratePhantomCharacter(sTemp, PIRATE, MAN, 0));
		ChangeCharacterAddress(npchar, "FortOrange_Mine", "goto" + i);
	}
	//убиваем всех
	for (i = 0; i<MAX_CHARACTERS; i++)
	{
		makeref(npchar, characters[i]);
		if (npchar.location == "FortOrange_Mine" && npchar.id != pchar.id)
		{
			for (j = 0; j < 5; j++)
			{
				LaunchBlood(npchar, 1.0 + frand(0.6), rand(1), "fight");
			}
			LAi_KillCharacter(npchar);
		}
	}
}

void DaytimeOutingLSCFunc_8(string qName)
{
	EndQuestMovie();
	AddQuestRecord("TheStarsAlignedISS", "2");
	Lai_SetPlayerType(pchar);
	locCameraTarget(pchar);
	locCameraFollow();
	LAi_ApplyCharacterDamage(pchar, LAi_GetCharacterHP(pchar) / 2, "fire");

	CreateLocationParticlesLoopedSound("shipfire", "quest", "effect1", 0.0, 0.0, 0, "fortfire");
	CreateLocationParticlesLoopedSound("shipfire", "quest", "effect2", 0.0, 0.0, 0, "fortfire");
	CreateLocationParticlesLoopedSound("shipfire", "quest", "sit3", 0.0, 0.0, 0, "fortfire");

	for (int i = 2; i<7; i++)
	{
		LocatorReloadEnterDisable("FortOrange_Mine", "reload"+i, true);
		if (i != 6) CreateLocationParticlesLoopedSound("shipfire", "reload", "reload"+i, 0.0, 0.0, 0, "fortfire");
	}

	ref sld = CharacterFromID("Minetown_Commend");
	sld.dialog.currentnode = "AhtungMinetown";
	ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "sit1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 10, 0);
}

void EnterToFortOrangeTownLSC(string qName)
{
	int i, iTemp;

	StopSound(musicID, 0);
	musicID = -1;
	KZ|Random("&Action\Fight,Action");

	StartQuestMovie(true, true, true);
	LAi_SetActorType(pchar);
	LAi_type_carrier_HideIntoFaultLines(pchar);

	ref sld = CharacterFromID("Minetown_Commend");
	LAi_type_actor_Reset(sld);
	LAi_type_carrier_HideIntoFaultLines(sld);

	LAi_group_Delete("EnemyFight");

	//поджигаем все
	for (i = 2; i<19; i++)
	{
		if (i == 12) continue;
		CreateLocationParticlesLoopedSound("shipfire", "reload", "reload"+i, 0.0, 0.0, 0, "fortfire");
	}
	CreateLocationParticlesLoopedSound("shipfire", "randitem", "randitem3", 0.0, 0.0, 0, "fortfire");
	DoQuestFunctionDelay("EnterToFortOrangeTownLSC_1", 0.0);
}

void EnterToFortOrangeTownLSC_1(string qName)
{
	ref sld;
	int i;
	string loc;
	float locx, locy, locz;

	//создаем массовку
	for (i = 1; i < 30; i++)
	{
		if (i < 11) continue;
		sld = GetCharacter(NPC_GeneratePhantomCharacter("slaves", PIRATE, MAN, 0));
		CalculateAppropriateSkillsParam(sld, 0.1, 0);
		if (rand(1)) LAi_SetHP(sld, 5000.0, 5000.0);
		LAi_SetCurHPMax(sld);
		ChangeCharacterAddress(sld, "FortOrange_town", "goto" + i);
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", "Holland_citizens", LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", "Holland_citizens", true);

	//население реагирует
	for (i = 0; i<MAX_CHARACTERS; i++)
	{
		makeref(sld, characters[i]);
		if (sld.location == "FortOrange_town" && CheckAttribute(sld, "CityType"))
		{
			if (rand(1)) LAi_SetHP(sld, 5000.0, 5000.0);
			//			LAi_SetCurHPMax(sld);
			if (sld.CityType != "soldier")
			{
				if (GetCharacterEquipByGroup(sld, BLADE_ITEM_TYPE) == "")
				{
					if (rand(3) < 3)
					{
						GetCharacterPos(sld, &locx, &locy, &locz);
						loc = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
						sld.lifeday = 0;
						LAi_SetActorTypeNoGroup(sld);
						if (loc != "")
							LAi_ActorRunToLocation(sld, "reload", loc, "none", "", "", "", 20.0);
						else
							LAi_ActorRunToLocation(sld, "reload", "reload12", "none", "", "", "", 20.0);
					}
					else
					{
						LAi_SetCitizenTypeNoGroup(sld);
					}
				}
			}
			else if (CheckAttribute(sld, "location.locator") && or(sld.location.locator == "protector3", sld.location.locator == "protector4"))
			{
				ChangeCharacterAddress(sld, "FortOrange_town", "goto30");
			}
		}
	}
	locCameraFlyToPositionLookToPoint(12.76, 7.95, -9.74, 20.76, 7.95, -9.74, 5.32, 0.03, 10.00, 1.0, 500);
	pchar.FuncCameraFly = "EnterToFortOrangeTownLSC_2";
}

void EnterToFortOrangeTownLSC_2()
{
	ChangeCharacterAddressGroup(pchar, "FortOrange_town", "officers", "reload1_2");
	ref chr = CharacterFromID("Minetown_Commend");
	LAi_SetImmortal(chr, false);
	ChangeCharacterAddress(chr, "FortOrange_town", "goto2");
	locCameraLockNearHero(2.0, 1.7, -1.1, -1, true);
	LAi_ActorTurnToLocator(pchar, "goto", "goto28");
	LAi_ActorTurnToLocator(chr, "officers", "reload11_1");

	ref sld = GetCharacter(NPC_GenerateCharacter("TitherDenLSC", "Tither", "man", "man", 27, PIRATE, -1, true));
	LAi_SetImmortal(sld, true);
	sld.dialog.filename = "Quest\LostShipsCity\TizerDen.c";
	GiveItem2Character(sld, "pistol1");
	EquipCharacterbyItem(sld, "pistol1");
	sld.dialog.CurrentNode = "FortOrangeAhtung";
	sld.name = FindPersonalName("Tizer_name");
	sld.lastname = FindPersonalName("Tizer_lastname");
	sld.greeting = "Gr_slave";
	ChangeCharacterAddressGroup(sld, "FortOrange_town", "officers", "reload9_1");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocator(sld, "goto", "goto28", "", -1);

	DoQuestFunctionDelay("EnterToFortOrangeTownLSC_3", 1.1);
}

void EnterToFortOrangeTownLSC_3(string qName)
{
	ref sld = CharacterFromID("TitherDenLSC");
	LAi_type_actor_Reset(sld);
	LAi_ActorTurnToLocator(sld, "goto", "goto2");
	LAi_tmpl_ani_PlayAnimation(sld, "Shot", -1.0);
	DoQuestFunctionDelay("EnterToFortOrangeTownLSC_4", 2.2);
}

void EnterToFortOrangeTownLSC_4(string qName)
{
	LAi_SetImmortal(pchar, true);

	ref sld = CharacterFromID("Minetown_Commend");
	LaunchBlood(sld, 1.0 + frand(0.6), rand(1), "fight");
	LAi_KillCharacter(sld);
	sld = CharacterFromID("TitherDenLSC");
	LAi_tmpl_ani_EndAnimation(sld);
	LAi_SetActorType(sld);
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
	TEV.NoDialogExit = true;
}

void NightTimeOutingLSCFunc_1(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld = CharacterFromID("TizerDenLSC");
	LAi_type_actor_Reset(sld);
	sld.dialog.CurrentNode = "NightTimeOutingLSC_1";
	ChangeCharacterAddress(sld, "Orange_mines", "goto1");

	//создаем массовку
	for (int i = 2; i < 12; i++)
	{
		sld = GetCharacter(NPC_GeneratePhantomCharacter("slaves", PIRATE, MAN, 1));
		sld.id = "slavesLSC"+i;
		DeleteAttribute(sld, "equip");
		GiveItem2Character(sld, "unarmed");
		EquipCharacterbyItem(sld, "unarmed");
		ChangeCharacterAddress(sld, "Orange_mines", "goto" + i);
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_warrior_DialogEnable(sld, false);
		if (i == 3)
		{
			TEV.NightTimeOutingNPC = sld.index;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto1", "", 2.0);
		}
	}
	pchar.quest.NightTimeOutingLSCFunc_2.win_condition.l1        			= "locator";
	pchar.quest.NightTimeOutingLSCFunc_2.win_condition.l1.location 			= "Orange_mines";
	pchar.quest.NightTimeOutingLSCFunc_2.win_condition.l1.locator_group 	= "quest";
	pchar.quest.NightTimeOutingLSCFunc_2.win_condition.l1.locator 			= "mushketer2";
	pchar.quest.NightTimeOutingLSCFunc_2.function 							= "NightTimeOutingLSCFunc_2";
}

void NightTimeOutingLSCFunc_2(string qName)
{
	LAi_SetActorType(pchar);
	LAi_ActorGoToLocator(pchar, "goto", "goto10", "NightTimeOutingLSC_6", -1);
}

void NightTimeOutingLSCFunc_3(string qName)
{
	LAi_SetActorType(pchar);
	ref sld = CharacterFromID("TizerDenLSC");
	ref slave = GetCharacter(FindNearCharacters(sld, 30.0, -1.0, -1.0, 0.001, false, true));
	LAi_SetActorType(pchar);
	sld = CharacterFromID("TizerDenLSC");
	LAi_SetActorType(sld);
	LAi_ActorWaitDialog(pchar, sld);
}

void NightTimeOutingLSCFunc_4()
{
	//рабы валят
	ref sld;
	for (int i = 2; i < 12; i++)
	{
		sld = CharacterFromID("slavesLSC"+i);
		LAi_SetActorTypeNoGroup(sld);
		if (i == 2) LAi_ActorRunToLocator(sld, "soldiers", "protector1", "OutFromMineLSC_1", 10.0);
		else LAi_ActorRunToLocator(sld, "soldiers", "protector1", "", 10.0);
	}
	DoQuestFunctionDelay("NightTimeOutingLSCFunc_5", 2.0);
}

void NightTimeOutingLSCFunc_5(string qName)
{
	ref sld = CharacterFromID("TizerDenLSC");
	sld.name = TEV.NightTimeOutingLSC.name;
	sld.lastname = TEV.NightTimeOutingLSC.lastname;
	DeleteAttribute(&TEV, "NightTimeOutingNPC");
	sld.Dialog.CurrentNode = "OutFromMineLSC_1";
	LAi_SetActorType(pchar);
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "", 2.0, -1);
}

void NightTimeOutingLSCFunc_6()
{
	ref sld = &locations[FindLocation("Orange_mines")];
	DeleteAttribute(sld, "models.always.DungeonOrange1_wall");
	DeleteAttribute(sld, "models.always.DungeonOrange1_door");
	sld.models.day.charactersPatch = "DungeonOrange1_patch3";
	sld.models.night.charactersPatch = "DungeonOrange1_patch3";
	ChangeCharacterAddress(CharacterFromID("TizerDenLSC"), "Orange_mines", "goto8");
	ChangeCharacterAddress(CharacterFromID("Minetown_Commend"), "none", "");
	ChangeCharacterAddress(CharacterFromID("mineGuard1"), "none", "");
	ChangeCharacterAddress(CharacterFromID("mineGuard2"), "none", "");
	Dead_DelLoginedCharacter(CharacterFromID("Minetown_Commend"));
	Dead_DelLoginedCharacter(CharacterFromID("mineGuard1"));
	Dead_DelLoginedCharacter(CharacterFromID("mineGuard2"));
	WaitDate("", 0, 0, 0, 0, 10);
	RecalculateJumpTable();
	RefreshLandTime();
	DoQuestReloadToLocation("Orange_mines", "officers", "reload1_1", "OutFromMineLSC_5");
}

void NightTimeOutingLSCFunc_8(string qName)
{
	ref sld = CharacterFromID("FortOrange_tavernkeeper");
	LAi_KillCharacter(sld);
	DoQuestFunctionDelay("NightTimeOutingLSCFunc_9", 0.1);
}

void NightTimeOutingLSCFunc_9(string qName)
{
	CreateLocationParticles("ShipExplode", "quest", "body2", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
	CreateLocationParticlesLoopedSound("shipfire", "quest", "body1", 0.0, 0.0, 0, "fortfire");
	CreateLocationParticlesLoopedSound("shipfire", "quest", "body2", 0.0, 0.0, 0, "fortfire");
	CreateLocationParticlesLoopedSound("shipfire", "quest", "body10", 0.0, -1.0, 0, "fortfire");
	SetCameraShake(0.5, 5.0, 3.0, 1.2, 0.5, true, false, CAM_EASING_CUBE);

	ref sld = CharacterFromID("TizerDenLSC");
	LAi_KillCharacter(sld);
	LAi_tmpl_ani_PlayAnimation(pchar, "death_10", -1.0);

	sld = &locations[FindLocation("Orange_mines")];
	sld.Orange_mines_fireLSC = true;

	for (int i = 2; i < 12; i++)
	{
		sld = CharacterFromID("slavesLSC"+i);
		LaunchBlood(sld, 1.0 + frand(0.6), rand(1), "fight");
		LAi_KillCharacter(sld);
	}
	DoQuestFunctionDelay("NightTimeOutingLSCFunc_10", 2.5);
}

void NightTimeOutingLSCFunc_10(string qName)
{
	LAi_FadeEx(1.0, 2.0, 1.0, "NightTimeOutingLSCFunc_11", "NightTimeOutingLSCFunc_12", "");
}

void NightTimeOutingLSCFunc_11(string qName)
{
	ref sld = CharacterFromID("TizerDenLSC");
	Dead_DelLoginedCharacter(sld);
	ChangeCharacterAddress(sld, "none", "");

	for (int i = 2; i < 12; i++)
	{
		sld = CharacterFromID("slavesLSC"+i);
		Dead_DelLoginedCharacter(sld);
		ChangeCharacterAddress(sld, "none", "");
	}
}

void NightTimeOutingLSCFunc_12(string qName)
{
	LAi_SetPlayerType(pchar);
	locCameraTarget(pchar);
	locCameraFollow();
	EndQuestMovie();
	LAi_LocationFightDisable(&Locations[FindLocation("Orange_mines")], false);
	LocatorReloadEnterDisable("Orange_mines", "reload1_back", true);
	LocatorReloadEnterDisable("Orange_mines", "reload2_back", false);
	AddQuestRecord("TheStarsAlignedISS", "3");
	chrDisableReloadToLocation = false;
	pchar.quest.NightTimeOutingLSCFunc_13.win_condition.l1 = "location";
	pchar.quest.NightTimeOutingLSCFunc_13.win_condition.l1.location = "FortOrange_town";
	pchar.quest.NightTimeOutingLSCFunc_13.function = "NightTimeOutingLSCFunc_13";
}

void NightTimeOutingLSCFunc_13(string qName)
{
	chrDisableReloadToLocation = true;
	int i, iTemp;

	StopSound(musicID, 0);
	musicID = -1;
	KZ|Random("&Action\Fight,Action");

	StartQuestMovie(true, true, true);
	LAi_SetActorType(pchar);

	ref sld = &locations[FindLocation("Orange_mines")];
	DeleteAttribute(sld, "Orange_mines_fireLSC");

	//поджигаем все
	for (i = 2; i<19; i++)
	{
		if (i == 12) continue;
		CreateLocationParticlesLoopedSound("shipfire", "reload", "reload"+i, 0.0, 0.0, 0, "fortfire");
	}
	CreateLocationParticlesLoopedSound("shipfire", "randitem", "randitem3", 0.0, 0.0, 0, "fortfire");
	DoQuestFunctionDelay("NightTimeOutingLSCFunc_14", 0.0);
}

void NightTimeOutingLSCFunc_14(string qName)
{
	ref sld;
	int i;
	string loc;
	float locx, locy, locz;
	int count = 0;

	LAi_group_Delete("EnemyFight");
	//создаем массовку
	for (i = 1; i < 20; i++)
	{
		sld = GetCharacter(NPC_GeneratePhantomCharacter("slaves", PIRATE, MAN, 0));
		sld.id = "NightSlaveLSC"+i;
		ChangeCharacterAddress(sld, "FortOrange_town", "goto" + i);
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_warrior_DialogEnable(sld, false);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}

	//население реагирует
	for (i = 0; i<MAX_CHARACTERS; i++)
	{
		makeref(sld, characters[i]);
		if (sld.location == "FortOrange_town" && CheckAttribute(sld, "CityType"))
		{
			if (sld.CityType != "soldier")
			{
				if (GetCharacterEquipByGroup(sld, BLADE_ITEM_TYPE) == "")
				{
					if (rand(3) < 3)
					{
						GetCharacterPos(sld, &locx, &locy, &locz);
						loc = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
						sld.lifeday = 0;
						LAi_SetActorTypeNoGroup(sld);
						if (loc != "")
							LAi_ActorRunToLocation(sld, "reload", loc, "none", "", "", "", 20.0);
						else
							LAi_ActorRunToLocation(sld, "reload", "reload12", "none", "", "", "", 20.0);
					}
					else
					{
						LAi_SetCitizenTypeNoGroup(sld);
						LAi_group_MoveCharacter(sld, "EnemyFight");
					}
				}
			}
			else
			{
				LAi_group_MoveCharacter(sld, "EnemyFight");
				count++;
			}
		}
	}
	//если осталось мало солдат в городе, то добавляем
	if (count < 8)
	{
		for (i = 20; i < 27; i++)
		{
			sld = GetCharacter(NPC_GeneratePhantomCharacter("urban_sold", HOLLAND, MAN, 0));
			ChangeCharacterAddress(sld, "FortOrange_town", "goto" + i);
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
	}
	LAi_SetImmortal(pchar, true);
	LAi_group_SetRelation(LAI_GROUP_PLAYER, "EnemyFight", LAI_GROUP_ENEMY);
	LAi_group_FightGroups(LAI_GROUP_PLAYER, "EnemyFight", true);
	LAi_group_SetCheck("EnemyFight", "OutFromMineLSC_13");
	locCameraFlyToPositionLookToPoint(12.76, 7.95, -9.74, 20.76, 7.95, -9.74, 5.32, 0.03, 10.00, 1.0, 500);
	pchar.FuncCameraFly = "NightTimeOutingLSCFunc_15";
}

void NightTimeOutingLSCFunc_15()
{
	LAi_SetPlayerType(pchar);
	pchar.FuncCameraFly = "";
	locCameraNextState();
	locCameraTarget(pchar);
	locCameraFollow();
	EndQuestMovie();
	LAi_SetFightMode(pchar, true);
	if (!CheckAttribute(pchar, "questTemp.Azzy.Immortal")) LAi_SetImmortal(pchar, false);
}

void TheStarsAlignedFuncLSC_1(string qName)
{
	int i, iTemp;
	ref chr = CharacterFromID("JungleManLSC");
	LAi_SetActorType(chr);
	ChangeCharacterAddress(chr, "FortOrange_ExitTown", "goto19");
	LAi_SetActorType(pchar);
	LAi_ActorStay(pchar);
	ChangeCharacterAddressGroup(pchar, "FortOrange_ExitTown", "quest", "pir20");
	ref sld = CharacterFromID("TitherDenLSC");
	LAi_SetImmortal(sld, true);
	sld.name = FindPersonalName("Tizer_name");
	sld.lastname = FindPersonalName("Tizer_lastname");
	LAi_SetActorType(sld);
	LAi_ActorStay(sld);
	ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "quest", "pir19");
	sld = CharacterFromID("John_CoxonLSC");
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	LAi_ActorStay(sld);
	ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "quest", "pir18");
	iTemp = 1;
	for (i = 1; i < 15; i++)
	{
		sld = CharacterFromID("JungleManBoysLSC" + i);
		LAi_type_actor_Reset(sld);
		if (i < 3 || i > 9)
		{
			LAi_SetActorType(sld);
			ChangeCharacterAddress(sld, "FortOrange_ExitTown", "goto7");
			LAi_ActorFollow(sld, chr, "", -1);
		}
		else
		{
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "quest", "eng" + iTemp);
			iTemp++;
		}
	}
	for (i = 1; i < 15; i++)
	{
		sld = CharacterFromID("John_CoxonBoysLSC" + i);
		if (LAi_IsDead(sld)) continue;
		LAi_SetActorType(sld);
		LAi_ActorStay(sld);
		ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "quest", "pir" + i);
	}
	iTemp = 15;
	if (pchar.questTemp.LSC.StarsAlignedCompanion == "PcharSailorLSC2")
	{
		for (i = 1; i < 3; i++)
		{
			sld = CharacterFromID("PcharSailorLSC"+i);
			if (LAi_IsDead(sld)) continue;
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "quest", "pir" + iTemp);
			iTemp++;
		}
	}
	else
	{
		for (i = 1; i < 4; i++)
		{
			iTemp = GetOfficersIndex(pchar, i);
			if (iTemp != -1) {
				if (LAi_IsDead(sld)) continue;
				LAi_SetActorType(sld);
				LAi_ActorStay(sld);
				ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "quest", "pir" + iTemp);
				iTemp++;
			}
		}
	}
}

void TheStarsAlignedFuncLSC_2(string qName)
{
	locCameraFromToPos(1.02, 4.73, 7.73, false, 20.28, -15.69, -90.00);
	ref sld = CharacterFromID("JungleManLSC");
	LAi_ActorRunToLocator(sld, "reload", "reload3", "TheStarsAlignedLSC_18", -1);
}

void TheStarsAlignedFightLSC()
{
	int i, iTemp;
	LAi_SetPlayerType(pchar);
	locCameraTarget(pchar);
	locCameraFollow();
	LAi_SetFightMode(pchar, true);
	ref sld = CharacterFromID("TitherDenLSC");
	LAi_SetWarriorTypeNoGroup(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld = CharacterFromID("John_CoxonLSC");
	LAi_SetWarriorTypeNoGroup(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld = CharacterFromID("JungleManLSC");
	if (sld.location == pchar.location)
	{
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (i = 1; i < 15; i++)
	{
		sld = CharacterFromID("JungleManBoysLSC" + i);
		if (LAi_IsDead(sld)) continue;
		if (sld.location != pchar.location) continue;
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (i = 1; i < 15; i++)
	{
		sld = CharacterFromID("John_CoxonBoysLSC" + i);
		if (LAi_IsDead(sld)) continue;
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	if (pchar.questTemp.LSC.StarsAlignedCompanion == "PcharSailorLSC2")
	{
		for (i = 1; i < 3; i++)
		{
			sld = CharacterFromID("PcharSailorLSC"+i);
			if (LAi_IsDead(sld)) continue;
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
	else
	{
		for (i = 1; i < 4; i++)
		{
			iTemp = GetOfficersIndex(pchar, i);
			if (iTemp != -1) {
				sld = GetCharacter(iTemp);
				if (LAi_IsDead(sld)) continue;
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		}
	}
	for (i = 0; i < 5; i++)
	{
		iTemp = GetCharacterIndex("John_CoxonSlaves" + i);
		if (iTemp != -1) {
			sld = GetCharacter(iTemp);
			if (LAi_IsDead(sld)) continue;
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		}
	}
}

void TheStarsAlignedReturnLSC(string qName)
{
	int i, iTemp, iChr;
	LAi_SetPlayerType(pchar);
	LAi_SetActorType(pchar);
	LAi_ActorRunToLocator(pchar, "quest", "pir20", qName, 10.0);
	ref sld = CharacterFromID("TitherDenLSC");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocator(sld, "quest", "pir19", "", -1);
	sld = CharacterFromID("John_CoxonLSC");
	LAi_SetActorType(sld);
	if (sld.location == pchar.location)
		LAi_ActorRunToLocator(sld, "quest", "pir18", "", -1);
	for (i = 1; i < 15; i++)
	{
		sld = CharacterFromID("JungleManBoysLSC" + i);
		if (LAi_IsDead(sld)) continue;
		if (sld.location != pchar.location) continue;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "quest", "eng" + i, "", -1);
	}
	for (i = 1; i < 15; i++)
	{
		sld = CharacterFromID("John_CoxonBoysLSC" + i);
		if (LAi_IsDead(sld)) continue;
		LAi_SetActorType(sld);
		LAi_ActorRunToLocator(sld, "quest", "pir" + i, "", -1);
	}
	iTemp = 15;
	if (pchar.questTemp.LSC.StarsAlignedCompanion == "PcharSailorLSC2")
	{
		for (i = 1; i < 3; i++)
		{
			sld = CharacterFromID("PcharSailorLSC"+i);
			if (LAi_IsDead(sld)) continue;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "pir" + iTemp, "", -1);
			iTemp++;
		}
	}
	else
	{
		for (i = 1; i < 4; i++)
		{
			iChr = GetOfficersIndex(pchar, i);
			if (iChr != -1) {
				sld = GetCharacter(iChr);
				if (LAi_IsDead(sld)) continue;
				LAi_SetActorType(sld);
				LAi_ActorRunToLocator(sld, "quest", "pir" + iTemp, "", -1);
				iTemp++;
			}
		}
	}
	for (i = 0; i < 5; i++)
	{
		iTemp = GetCharacterIndex("John_CoxonSlaves" + i);
		if (iTemp != -1) {
			sld = GetCharacter(iTemp);
			if (LAi_IsDead(sld)) continue;
			LAi_SetActorType(sld);
		}
	}
}

void BattleInShoreLSC(string qName)
{
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable("FortOrange_ExitTown", "reload2_back", false);
	int i, iTemp, index;

	//наши слоны
	LAi_SetFightMode(pchar, true);
	ref sld = CharacterFromID("TitherDenLSC");
	LAi_SetWarriorTypeNoGroup(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	ChangeCharacterAddressGroup(sld, "Shore35", "officers", "reload1_1");
	sld = CharacterFromID("John_CoxonLSC");
	LAi_SetWarriorTypeNoGroup(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	ChangeCharacterAddressGroup(sld, "Shore35", "officers", "reload1_1");
	sld = CharacterFromID("JungleManLSC");
	LAi_SetWarriorTypeNoGroup(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	ChangeCharacterAddressGroup(sld, "Shore35", "officers", "reload1_1");
	for (i = 1; i < 15; i++)
	{
		index = GetCharacterIndex("JungleManBoysLSC" + i);
		if (index == -1) continue;
		sld = GetCharacter(index);
		if (LAi_IsDead(sld)) continue;
		sld.LifeDay = 0;
		ChangeCharacterAddress(sld, "none", "");
	}
	for (i = 1; i < 15; i++)
	{
		index = GetCharacterIndex("John_CoxonBoysLSC" + i);
		if (index == -1) continue;
		sld = GetCharacter(index);
		if (LAi_IsDead(sld)) continue;
		sld.LifeDay = 0;
		ChangeCharacterAddress(sld, "none", "");
	}
	if (pchar.questTemp.LSC.StarsAlignedCompanion == "PcharSailorLSC2")
	{
		for (i = 1; i < 3; i++)
		{
			index = GetCharacterIndex("PcharSailorLSC" + i);
			if (index == -1) continue;
			sld = GetCharacter(index);
			if (LAi_IsDead(sld)) continue;
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_SetImmortal(sld, false);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "Shore35", "reload", "reload1_back");
		}
	}
	else
	{
		for (i = 1; i < 4; i++)
		{
			iTemp = GetOfficersIndex(pchar, i);
			if (iTemp != -1) {
				sld = GetCharacter(iTemp);
				if (LAi_IsDead(sld)) continue;
				if (sld.sex == "woman") sld.dialog.filename = "Officer_Girl.c";
				else sld.dialog.filename = "Officer_Man.c";
				sld.dialog.CurrentNode = "hired";
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "Shore35", "reload", "reload1_back");
			}
		}
	}
	for (i = 0; i < 5; i++)
	{
		iTemp = GetCharacterIndex("John_CoxonSlaves" + i);
		if (iTemp != -1) {
			sld = GetCharacter(iTemp);
			if (LAi_IsDead(sld)) continue;
			sld.LifeDay = 0;
			ChangeCharacterAddress(sld, "none", "");
		}
	}
	for (i = 0; i < 5; i++)
	{
		iTemp = GetCharacterIndex("JungleManSlavesLSC" + i);
		if (iTemp != -1) {
			sld = GetCharacter(iTemp);
			if (LAi_IsDead(sld)) continue;
			sld.LifeDay = 0;
			ChangeCharacterAddress(sld, "none", "");
		}
	}
	sld = CharacterFromID(pchar.questTemp.LSC.StarsAlignedCompanion);
	if (sld.sex == "woman")
		sld.dialog.filename = "Officer_Girl.c";
	else
		sld.dialog.filename = "Officer_Man.c";
	sld.dialog.CurrentNode = "hired";
	DeleteAttribute(pchar, "questTemp.LSC.StarsAlignedCompanion");

	//просто слоны
	LAi_group_Delete("EnemyFight");
	if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 20;
	else iTemp = 30;
	for (i = 0; i < iTemp; i++)
	{
		sld = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
		ChangeCharacterAddressGroup(sld, "Shore35", "smugglers", "smuggler01");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 5;
	else iTemp = 10;
	for (i = 0; i < iTemp; i++)
	{
		sld = GetCharacter(NPC_GeneratePhantomCharacter("rivados_mush", PIRATE, MAN, 0));
		ChangeCharacterAddressGroup(sld, "Shore35", "goto", "goto8");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheck("EnemyFight", "TheStarsAlignedLSC_47");
	DoQuestFunctionDelay("BattleInShoreLSC_1", 10.0);
}

void BattleInShoreLSC_1(string qName)
{
	int iCrew = GetCrewQuantity(pchar); // Получаем текущее кол-во матросов на корабле
	int iTotalHelp, iSailors, iMusketeers, i;
	ref sld;

	// Считаем общее кол-во помощи (2% от экипажа)
	iTotalHelp = makeint(iCrew * 0.02);

	// Проверка на минимальное значение
	if (iTotalHelp < 1) {
		iTotalHelp = 1;
	}

	// Распределяем роли (75% матросы, 25% мушкетеры)
	if (iTotalHelp > 3)
	{
		iMusketeers = makeint(iTotalHelp * 0.25);
		iSailors = iTotalHelp - iMusketeers;
	}
	else
	{
		iMusketeers = 0;
		iSailors = iTotalHelp;
	}

	if (iSailors > 15) iSailors = 15;
	if (iMusketeers > 5) iMusketeers = 5;

	//наши ребята
	for (i = 0; i < iSailors; i++)
	{
		sld = GetCharacter(NPC_GeneratePhantomCharacter("sailor", PIRATE, MAN, 0));
		ChangeCharacterAddressGroup(sld, "Shore35", "reload", "sea");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (i = 0; i < iMusketeers; i++)
	{
		sld = GetCharacter(NPC_GeneratePhantomCharacter("pirate_mush", PIRATE, MAN, 0));
		ChangeCharacterAddressGroup(sld, "Shore35", "reload", "sea");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	//пираты коксона
	for (i = 0; i < iSailors; i++)
	{
		sld = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 0));
		ChangeCharacterAddressGroup(sld, "Shore35", "goto", "goto5");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (i = 0; i < iMusketeers; i++)
	{
		sld = GetCharacter(NPC_GeneratePhantomCharacter("pirate_mush", PIRATE, MAN, 0));
		ChangeCharacterAddressGroup(sld, "Shore35", "goto", "goto5");
		LAi_SetWarriorTypeNoGroup(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}

void AfterStarsAlignedFuncLSC_1(string qName)
{
	QuestToSeaLogin_Prepare(-5898.92, 814.33, "Jamaica");
	questToSeaLoginer.FromCoast = true;
	QuestToSeaLogin_Launch();
	ref sld = CharacterFromID("TitherDenLSC");
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	for (int i = 0; i<MAX_CHARACTERS; i++)
	{
		makeref(sld, characters[i]);
		if (sld.location == "Shore35")
		{
			LAi_SetImmortal(sld, false);
			ChangeCharacterAddress(sld, "none", "");
		}
	}
}

void AfterStarsAlignedFuncLSC_2(string qName)
{
	AddQuestRecord("TheStarsAlignedISS", "5");
	CloseQuestHeader("TheStarsAlignedISS");
	//восстановление Форт Оранжа
	pchar.quest.HeadhunterTimer.win_condition.l1 = "Timer";
	pchar.quest.HeadhunterTimer.win_condition.l1.date.hour = GetTime();
	pchar.quest.HeadhunterTimer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 3);
	pchar.quest.HeadhunterTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
	pchar.quest.HeadhunterTimer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
	pchar.quest.HeadhunterTimer.function = "RevertFortOrangeLSC";
	LocatorReloadEnterDisable("FortOrange_ExitTown", "reload3", true);
	LocatorReloadEnterDisable("FortOrange_ExitTown", "reload1_back", false);
	ref sld = &locations[FindLocation("FortOrange_ExitTown")];
	DeleteAttribute(sld, "FortOrange_ExitTown_fireLSC");
	LAi_group_Delete("EnemyFight");
	//диалог в каюте
	Sea_CabinStartNow();
}

void AfterStarsAlignedFuncLSC_3(string qName)
{
	ref sld;
	int idx;
	bool bInit = false;
	if (CheckOfficer("doctor"))
	{
		sld = RefOfficer("doctor");
		bInit = true;
	}
	else if (GetPassengersQuantity(pchar) > 0)
	{
		for (int i = 0; i < GetPassengersQuantity(pchar); i++)
		{
			idx = GetPassenger(pchar, i);
			if (idx > 1) {
				if (isOfficerInShip(GetCharacter(idx), true))
				{
					sld = GetCharacter(idx);
					bInit = true;
					break;
				}
			}
		}
	}
	if (!bInit)
	{
		sld = GetCharacter(NPC_GeneratePhantomCharacter("sailor", PIRATE, MAN, 0));
		sld.dialog.filename = "Officer_Man.c";
	}
	if (CheckAttribute(sld, "quest.capellan")) sld.dialog.filename = "Officer_Man.c";
	ChangeCharacterAddressGroup(pchar, Get_My_Cabin(), "goto", "goto1");
	ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "reload", "reload1");
	LAi_SetActorType(sld);
	sld.dialog.CurrentNode = "TalkAboutTizerDen";
	LAi_SetActorType(pchar);
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "", 7.0, 0);
}

void RevertFortOrangeLSC(string qName)
{
	for (int i = 1; i < 7; i++)
	{
		LocatorReloadEnterDisable("FortOrange_Mine", "reload"+i, false);
	}
	LocatorReloadEnterDisable("OutRHouse", "reload2_back", false);
	LAi_LocationDisableOfficersGen("FortOrange_Mine", false);
	LAi_LocationDisableOfficersGen("FortOrange_town", false);
	LAi_LocationDisableOfficersGen("Orange_mines", false);
	LocatorReloadEnterDisable("FortOrange_ExitTown", "reload3", false);
	LAi_LocationDisableOfficersGen("OutRHouse", false);

	//нового коменданта в рудники
	ref sld = GetCharacter(NPC_GenerateCharacter("Minetown_Commend", "off_hol_4", "man", "man", 30, HOLLAND, -1, false));
	sld.name 	= FindPersonalName("Minetown_Commend_name");
	sld.lastname = FindPersonalName("Minetown_Commend_lastname");
	sld.City = "FortOrange_Mine";
	sld.location	= "Mine_residence";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.Dialog.Filename = "Mayor\Minentown_mayor.c";
	sld.greeting = "eng_gov_common";
	sld.quest.type = "hovernor";
	SetRandSPECIAL(sld);
	SetSelfSkill(sld, 90, 90, 90, 60, 70);
	sld.watchBoxes = true;
	sld.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_LoginInCaptureTown(sld, true);
	LAi_SetImmortal(sld, true);

	//нового трактирщика в трактир
	int index = GetCharacterIndex("FortOrange_tavernkeeper");
	if (index == -1 || LAi_IsDead(GetCharacter(index))) {
		sld = GetCharacter(index);
		sld = GetCharacter(NPC_GenerateCharacter("FortOrange_tavernkeeper", "barmen_9", "man", "man", 10, HOLLAND, -1, false));
		sld.greeting = "Gr_Barmen";
		sld.City = "FortOrange";
		sld.location	= "FortOrange_Tavern";
		sld.location.group = "barmen";
		sld.location.locator = "stay";
		sld.Dialog.Filename = "Common_Tavern.c";
		sld.TavernMan = true;
		LAi_SetBarmanType(sld);
		LAi_RemoveLoginTime(sld);
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		LAi_SetImmortal(sld, true);
	}

	//дверь в рудники
	sld = &locations[FindLocation("Orange_mines")];
	sld.models.always.DungeonOrange1_door = "DungeonOrange1_door";
	sld.models.always.DungeonOrange1_wall = "DungeonOrange1_wall";
	sld.models.day.charactersPatch = "DungeonOrange1_patch2";
	sld.models.night.charactersPatch = "DungeonOrange1_patch2";
}

void EnterToStormLSC(string qName)
{
    if (pchar.location != "LostShipsCity") //если увернулись от штормов то телепортируем в шторм насильно, ибо надо затонуть
    {
        wdmReloadToSea();
    }
}

void DamageShipLSC_Start(string qName)
{
    if (pchar.location == "LostShipsCity")
    {
        float psX = MakeFloat(pchar.Ship.Pos.x);
        float psZ = MakeFloat(pchar.Ship.Pos.z);
        Lightning_HitIt(psX, psZ);
        BrokeMasts(pchar, true);
        PlaySound("mast_fall");
    }
}

void DamageShipLSC_End(string qName)
{
    if (pchar.location == "LostShipsCity")
    {
        float psX = MakeFloat(pchar.Ship.Pos.x);
        float psZ = MakeFloat(pchar.Ship.Pos.z);
        Lightning_HitIt(psX, psZ);
        BrokeMasts(pchar, false);
        PlaySound("Abandon_3");
        Ship_ApplyHullHitpoints(pchar, makefloat(sti(pchar.ship.hp)*2), KILL_BY_TOUCH, -1);
    }
}

void ReloadToLSC(string qName)
{
    // прерывание на кат-сцену
	pchar.quest.LSC_AfterFirstReload.win_condition.l1 = "location";
	pchar.quest.LSC_AfterFirstReload.win_condition.l1.location = "LostShipsCity_town";
	pchar.quest.LSC_AfterFirstReload.function = "LSC_GettingToKnowLSC";
	DeleteAttribute(&TEV, "stormLSC");

	EndQuestMovie();
	bDisableMapEnter = false;
	DeleteSeaEnvironment();
	DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload77", "OpenTheDoors");
	AddCharacterHealth(pchar, -1 * MOD_SKILL_ENEMY_RATE);
	if (CheckCharacterItem(pchar, "letter_LSC_1"))
			TakeItemFromCharacter(pchar, "letter_LSC_1");
}

void LSC_GettingToKnowLSC(string qName)
{
	StartQuestMovie(true, false, true);
	LAi_FadeEx(0.0, 1.5, 1.0, "", "LSC_GettingToKnowLSC_1", "");
	locCameraFlyToPositionLookToPoint(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 100/GetDeltaTime()); // Сейчас есть баг, и эта камера временная, пока не решим
	Pchar.FuncCameraFly = "";

	Achievment_Set(ACH_Ostrov_Spravedlivosti);
}

void LSC_GettingToKnowLSC_1(string qName)
{
	locCameraFlyToPositionLookToPoint(-77.05, 23.63, 20.19, -72.54, 18.12, 21.04, -67.81, 12.34, 21.93, -1.0, 10000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("LSC_GettingToKnowLSC_2", 7.0);
}

void LSC_GettingToKnowLSC_2(string qName)
{
	LAi_FadeEx(1.0, 0.0, 1.0, "", "LSC_GettingToKnowLSC_3", "");
}

void LSC_GettingToKnowLSC_3(string qName)
{
	locCameraSleep(false);
	locCameraResetState();
	locCameraFlyToPositionLookToPoint(-29.68, 20.15, -121.90, -14.06, 17.52, -99.15, -8.52, 16.59, -91.08, -1.0, 6000/GetDeltaTime());
	Pchar.FuncCameraFly = "LSC_GettingToKnowLSC_4";
}

void LSC_GettingToKnowLSC_4()
{
	locCameraFlyToPositionLookToPoint(61.65, 9.90, -62.06, 55.81, 9.40, -31.75, 50.00, 2.00, 0.00, -1.0, 11000/GetDeltaTime());
	Pchar.FuncCameraFly = "CameraSleep";
	DoQuestFunctionDelay("LSC_GettingToKnowLSC_5", 9.0);
}

void LSC_GettingToKnowLSC_5(string qName)
{
	LAi_FadeEx(1.0, 0.5, 1.0, "LSC_GettingToKnowLSC_6", "LSC_GettingToKnowLSC_7", "");
}

void LSC_GettingToKnowLSC_6(string qName)
{
	ChangeCharacterAddressGroup(pchar, "LostShipsCity_town", "reload", "reload_ring");
	CharacterTurnToLoc(pchar, "quest", "ring");
}

void LSC_GettingToKnowLSC_7(string qName)
{
	locCameraSleep(false);
	locCameraResetState();
	locCameraFlyToPositionLookToPoint(-42.49, 2.62, -3.98, -35.47, 2.29, -4.23, -27.21, 1.90, -4.53, -1.0, 7000/GetDeltaTime());
	Pchar.FuncCameraFly = "LSC_GettingToKnowLSC_8";
}

void LSC_GettingToKnowLSC_8()
{
	locCameraSleep(true);
    int chrId = GetCharacterIndex("JorgeStouks");
    if (chrId >= 0)
    {
        ref chr = &Characters[chrId];
        if (CheckAttribute(chr, "talker"))
            DeleteAttribute(chr, "talker");

		LAi_SetActorType(chr);
        LAi_SetActorType(pchar);
		SetActorDialogAny2Pchar(chr.id, "", -1, 0.0);
		LAi_ActorFollow(pchar, chr, "ActorDialog_Any2Pchar", 2.0);
        // Lai_ActorGoToLocator(pchar, "quest", "ring", "LSC_AfterFirstReload_StartDialog", 10);
        // ChangeCharacterAddressGroup(chr, "LostShipsCity_town", "item", "item1");
//        AddLandQuestMark_Main(chr, "ISS_MainLine");
    }
}

void LSC_GettingToKnowLSC_9()
{
	locCameraSleep(false);
	locCameraFromToPos(-29.84, 2.18, -4.61, true, -26.28, 1.05, -4.69);
}

void ISS_MurderSignExecute(string qName)
{
	pchar.questTemp.LSC.killCost = sti(pchar.questTemp.LSC.killCost)-1;
	pchar.questTemp.LSC = "PoorMurderBegin";
	if (sti(pchar.questTemp.LSC.killCost) <= 0)
	{
		pchar.questTemp.LSC = "PoorMurderExecute";
		DeleteAttribute(pchar, "questTemp.LSC.killCost");
		SetQuestHeader("ISS_PoorsMurder");
		AddQuestRecord("ISS_PoorsMurder", "2");
		AddLandQuestmark_Main(CharacterFromId(pchar.questTemp.LSC.usurerId), "ISS_PoorsMurder");
	}
}

void ISS_PoorsMurder_Poorman_SetQuestMarks(bool isSet)
{
    for (int i=0; i<MAX_COLONIES; i++)
    {
        if (!CheckAttribute(&colonies[i], "nation")) continue;
        if (colonies[i].nation == "none") continue; // необитайки
        if (colonies[i].nation == PIRATE) continue;

        int iChar = GetCharacterIndex(colonies[i].id + "_Poorman");
        if (iChar != -1)
        {
            if(isSet)
            {
                AddLandQuestmark_Main_WithCondition(&Characters[iChar], "ISS_PoorsMurder", "ISS_PoorsMurder_Poorman_QuestMarkCondition");
            }
            else
            {
                RemoveLandQuestmark_Main(&Characters[iChar], "ISS_PoorsMurder");
            }
        }
    }
}

void ISS_PoorsMurder_Poorman_AddQuestMarks()
{
    ISS_PoorsMurder_Poorman_SetQuestMarks(true);
}

void ISS_PoorsMurder_Poorman_RemoveQuestMarks()
{
    ISS_PoorsMurder_Poorman_SetQuestMarks(false);
}

void ISS_PoorsMurder_FindTizer_Smuggler_SetQuestMarks(bool isSet)
{
    for (int i=0; i<MAX_COLONIES; i++)
    {
        if (!CheckAttribute(&colonies[i], "nation")) continue;
        if (colonies[i].nation == "none") continue; // необитайки
        if (colonies[i].nation == PIRATE) continue;

        int iChar = GetCharacterIndex(colonies[i].id + "_Smuggler");
        if (iChar != -1)
        {
            if(isSet)
            {
                AddLandQuestmark_Main(&Characters[iChar], "ISS_PoorsMurder");
            }
            else
            {
                RemoveLandQuestmark_Main(&Characters[iChar], "ISS_PoorsMurder");
            }
        }
    }
}

void ISS_PoorsMurder_FindTizer_Smuggler_AddQuestMarks()
{
    ISS_PoorsMurder_FindTizer_Smuggler_SetQuestMarks(true);
}

void ISS_PoorsMurder_FindTizer_Smuggler_RemoveQuestMarks()
{
    ISS_PoorsMurder_FindTizer_Smuggler_SetQuestMarks(false);
}

void ISS_PoorsMurder_SecretFort_TizerHouse_Sleep(string qName)
{
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_27"), "", 0, 3);
	LaunchFrameForm();
	ref sld = CharacterFromId("Secret_Fort_Commander");
	sld.dialog.currentnode = "Commander_4_talk_1";
	WaitDate("", 0, 0, 1, 0, 0);
	SetCurrentTime(8, 8 + rand(6));
	RefreshLandTime();
	Whr_UpdateWeather();
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	ItemTake(pchar, "TizerJournal", 0);
	TeleportCharacterToLocator(pchar, "goto", "goto9");
	LAi_LocationDisableOfficersGen("Secret_Fort_Tizer_House", false);
}

void LSC_enterStuvesantBox(string qName)
{
	AddQuestRecord("ISS_PoorsMurder", "5");
	AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("ёл","ла"));
	pchar.questTemp.LSC = "toVillemstadTavern";
	//посадим воришку в таверну
	FreeSitLocator("Villemstad_tavern", "sit1"); //watch_coas_moment
	ref sld = GetCharacter(NPC_GenerateCharacter("GiveKeyMan", "shipowner_1", "man", "man", 10, HOLLAND, -1, false)); //watch_coas_moment
	sld.name = FindPersonalName("GiveKeyMan_name");
	sld.lastname = FindPersonalName("GiveKeyMan_lastname");
	sld.city = "Villemstad";
	sld.location	= "Villemstad_tavern";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.dialog.filename   = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode   = "GiveKeyMan";
	sld.greeting = "Gr_Master";
	LAi_SetSitType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");

	AddLandQuestMark_Main(CharacterFromID("Villemstad_tavernkeeper"), "ISS_PoorsMurder");
}

void LSC_openMasterHouse(string qName)
{	
	LocatorReloadEnterDisable("Villemstad_town", "houseSp5", false);
	//делаем видимым ключ
	ref sld = ItemsFromID("keyQuestLSC");
	sld.shown = true;
	sld = CharacterFromId("GiveKeyMan");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	pchar.quest.LSC_enterMasterHouse.win_condition.l1 = "location";
	pchar.quest.LSC_enterMasterHouse.win_condition.l1.location = "Villemstad_houseSp5";
	pchar.quest.LSC_enterMasterHouse.function = "LSC_enterMasterHouse";	
}

void LSC_OpenCryptDoor(string qName)
{
    PlaySound("Key");
	Log_SetActiveAction("Reload");
	LocatorReloadEnterDisable("Villemstad_CryptBig2", "reload2", false);
    ref locCryptBig2 = &locations[FindLocation("Villemstad_CryptBig2")];
    DeleteAttribute(locCryptBig2, "MustSetReloadBack");
    locCryptBig2.box3.items.LogbookLSC = 1;
    locCryptBig2.box3 = Items_MakeTime(0, 1, 1, 2024);

	AddQuestRecord("ISS_PoorsMurder", "17");
	AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("ёл","ла"));
	AddQuestUserData("ISS_PoorsMurder", "sSex1", GetSexPhrase("","а"));
}

void LSC_enterMasterHouse(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_houseSp5")], true);
	//ставим Мастера Ключей
	ref sld = characterFromId("GiveKeyMan");
	sld.dialog.currentnode = "GiveKeyManInside";
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Villemstad_houseSp5", "barmen", "bar1");
    LAi_SetActorType(pchar);
    LAi_SetActorType(sld);
    SetActorDialogAny2Pchar("GiveKeyMan", "", 0.0, 1.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
}

void LSC_enterSoldiers()
{	
	LAi_SetPlayerType(pchar);
	LAi_group_Delete("EnemyFight");
	pchar.questTemp.LSC = "CanFoundStuvesantKey";
	ref sld = characterFromId("GiveKeyMan");
	LAi_CharacterDisableDialog(sld);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	int iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 15;
	int iNum = round_up(stf((2+MOD_SKILL_ENEMY_RATE)/3));
	arrayNPCModelHow = 0;
	for (int i=1; i<=iNum; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("MKSold"+i, "wic_hol_"+(rand(7)+1), "man", "man", iTemp, HOLLAND, 0, true));
        SetNPCModelUniq(sld, "hwic", MAN);
		SetFantomParamFromRank(sld, iTemp, true);         
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
    }
    sld = GetCharacter(NPC_GenerateCharacter("MKOfficer", "off_WIC_1", "man", "man", iTemp, HOLLAND, 0, true));
	SetFantomParamFromRank(sld, iTemp, true);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "MK_HollOfficer";
	sld.greeting = "soldier_arest";
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void LSC_mapFound(string qName)
{
	if (CheckActiveQuest("FindMapLSC"))
	{
		AddQuestRecord("FindMapLSC", "8");
		CloseQuestHeader("FindMapLSC");

		LSC_UpdateQuestMarksToCitizens();
        RemoveLandQuestMark_Main(CharacterFromID("LSC_Trader"), "FindMapLSC");
        LSC_FindMapLSC_RemoveQuestMarksToWoman();
	}
}

void FirstLoginLostShipsCity(string qName) //первоначальная генерация нпс в ГПК
{
	//начальные настройки
	ref sld;
	pchar.questTemp.LSC = "AdmiralIsWaiting";
	TEV.captainInTheLSC = true;
	pchar.MermanTimer = 666.0;
	//из письма делаем послание Тизера Дэна -->
	TakeItemFromCharacter(pchar, "letter_LSC_1");
	int i = FindLocation("LostShipsCity_town");
	locations[i].private11.items.letter_LSC_2 = 1;
	//восстанавливаем флаги и пр. в игре вне ГПК
	CloseQuestHeader("ISS_PoorsMurder");
	LAi_group_Delete(LAI_GROUP_TmpEnemy); //группа граждан которых можно валить безнаказанно
	//снять шторм с острова ГПК
	reload_cur_island_index = FindIsland("LostShipsCity"); //TODO, в релиз убрать
	DeleteAttribute(&Islands[reload_cur_island_index], "alwaysStorm");
	DeleteAttribute(&Islands[reload_cur_island_index], "storm");
	DeleteAttribute(&Islands[reload_cur_island_index], "tornado");
	DeleteAttribute(&Islands[reload_cur_island_index], "QuestlockWeather");
	DeleteAttribute(&Islands[reload_cur_island_index], "MaxSeaHeight");

    // определяем пароли кланов
    pchar.questTemp.LSC.CasperParol = UpdateLSCClanParol();
    pchar.questTemp.LSC.NarvalParol = UpdateLSCClanParol();
    //если вошли к нарвалам в гости
    pchar.quest.LSC_WarWithNarval.win_condition.l1 = "locator";
    pchar.quest.LSC_WarWithNarval.win_condition.l1.location = "VelascoShipInside1";
    pchar.quest.LSC_WarWithNarval.win_condition.l1.locator_group = "reload";
    pchar.quest.LSC_WarWithNarval.win_condition.l1.locator = "reload1";
    pchar.quest.LSC_WarWithNarval.function = "LSC_WarWithNarval";
    //если вошли к касперам в гости
    pchar.quest.LSC_WarWithCasper.win_condition.l1 = "locator";
    pchar.quest.LSC_WarWithCasper.win_condition.l1.location = "SanGabrielMechanic";
    pchar.quest.LSC_WarWithCasper.win_condition.l1.locator_group = "reload";
    pchar.quest.LSC_WarWithCasper.win_condition.l1.locator = "reload1";
    pchar.quest.LSC_WarWithCasper.function = "LSC_WarWithCasper";

	//сносим все корабли и компаньонов
	int cn;
	for (i=0; i<=COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn != -1)
		{
			sld = &characters[cn];
			if (i == 0)
			{	//снимаем корабль ГГ
				DeleteAttribute(pchar, "ship");
				pchar.ship.name = "";
				pchar.ship.type = SHIP_NOTUSED;
				SetCharacterShipLocation(pchar, "");
			}
			else
			{
				RemoveCharacterCompanion(pchar, sld);
				sld.lifeDay = 0;
				LAi_KillCharacter(sld); //смэрть TODO: пусть спасаются с некоторой вероятностью
				i--;
			}
		}
	}
	//сносим всех пассажиров и офицеров
	for (i=0; i<=PASSENGERS_MAX; i++)
	{
		cn = GetPassenger(pchar, i);
		if(cn != -1)
		{
			sld = &characters[cn];
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			LAi_KillCharacter(sld);
			i--;
		}
	}
	//адмирала на стрем, чтобы ГГ долго не гулял
	PChar.quest.LSC_stormTimer_1.win_condition.l1            = "Timer";
	PChar.quest.LSC_stormTimer_1.win_condition.l1.date.hour  = 23;
    PChar.quest.LSC_stormTimer_1.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
    PChar.quest.LSC_stormTimer_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
    PChar.quest.LSC_stormTimer_1.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
    PChar.quest.LSC_stormTimer_1.function = "LSC_stormTimer_1";
	//Начальные слухи
	AddSimpleRumourCityTip(StringFromKey("Common_rumours_45"), "LostShipsCity", 10, 1, "LSC", "");
	AddSimpleRumourCityTip(StringFromKey("Common_rumours_46"), "LostShipsCity", 10, 1, "LSC", "");

    pchar.quest.LSC_findMap.win_condition.l1 = "item";
    pchar.quest.LSC_findMap.win_condition.l1.item = "map_LSC";
    pchar.quest.LSC_findMap.function = "LSC_mapFound";

	//мэр-адмирал 
	sld = GetCharacter(NPC_GenerateCharacter("LSCMayor", "Chad_Capper", "man", "man", 50, PIRATE, -1, true)); // Чад Каппер
	FantomMakeCoolFighter(sld, 50, 90, 90, "blade33", "pistol4", 200);
	sld.name = FindPersonalName("LSCMayor_name");
	sld.lastname = FindPersonalName("LSCMayor_lastname");
	sld.city = "LostShipsCity";
	sld.location = "SanAugustineResidence";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_0";
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mayor.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "mayor"; //тип нпс
	sld.greeting = "Gr_Kapper";
	sld.standUp = true; //вставать и нападать на врага 
	sld.watchBoxes = true;
	sld.standUp.exitDisable = true;   //залочить выход в случае драки
	sld.watchBoxes.exitDisable = true; //залочить выход в случае драки
    sld.SaveItemsForDead = true;
    sld.DontClearDead = true;
	//sld.talker = true; //начать диалог
	LAi_SetHuberType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);	
	SaveCurrentNpcQuestDateParam(sld, "location");
	
	SetSPECIAL(sld, 10,6,10,7,6,10,10); //(Сила, Воспр, Выносл, Обаян, Обуч, Реак, Удача)
    SetSelfSkill(sld, 100,100,100,60,70); //(ЛО, СО, ТО, пистолеты, фортуна)

	// миллиционер №1
	sld = GetCharacter(NPC_GenerateCharacter("Ment_1", "officer_13", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 85, 80, "blade21", "pistol4", 125);
	sld.name = FindPersonalName("Ment_1_name");
	sld.lastname = FindPersonalName("Ment_1_lastname");
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto9";
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_1";
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.greeting = "pirat_common";
	sld.talker = true; //начать диалог
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// миллиционер №2
	sld = GetCharacter(NPC_GenerateCharacter("Ment_2", "officer_22", "man", "man", 30, PIRATE, -1, true)); //watch_coas_moment
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade25", "pistol4", 125);
	sld.name = FindPersonalName("Ment_2_name");
	sld.lastname = FindPersonalName("Ment_2_lastname");
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto8";
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_2";
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе	
	sld.location.hours = 2; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.greeting = "pirat_common";
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// миллиционер №3
	sld = GetCharacter(NPC_GenerateCharacter("Ment_3", "citiz_53", "man", "man", 30, PIRATE, -1, true)); //watch_coas_moment
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade22", "pistol4", 125);
	sld.name = FindPersonalName("Ment_3_name");
	sld.lastname = FindPersonalName("Ment_3_lastname");
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto11";
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_3";
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе
	sld.location.hours = 6; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.greeting = "pirat_common";
	sld.talker = true; //начать диалог
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// миллиционер №4
	sld = GetCharacter(NPC_GenerateCharacter("Ment_4", "officer_23", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade24", "pistol4", 100);
	sld.name = FindPersonalName("Ment_4_name");
	sld.lastname = FindPersonalName("Ment_4_lastname");
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_4";  
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе
	sld.location.hours = 3; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.greeting = "pirat_common";
	sld.watchBoxes = true;
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// миллиционер №5
	sld = GetCharacter(NPC_GenerateCharacter("Ment_5", "officer_28", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade33", "pistol4", 100);
	sld.name = FindPersonalName("Ment_5_name");
	sld.lastname = FindPersonalName("Ment_5_lastname");
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto3";
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_5";
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.greeting = "pirat_common";
	sld.watchBoxes = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// миллиционер №6
	sld = GetCharacter(NPC_GenerateCharacter("Ment_6", "Workman", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "topor2", "pistol4", 100);
	sld.name = FindPersonalName("Ment_6_name");
	sld.lastname = FindPersonalName("Ment_6_lastname");
	sld.rank = 25;
	sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
	sld.HeroModel = "Workman,Workman_1,Workman_2,Workman_3,Workman_4,Workman_5"; // Прописка всех моделей для кирас. <-- Konstrush
	sld.quest.AngerAtAdmiral = 0; //счетчик энрейджа по отношению к Адмиралу
	sld.city = "LostShipsCity";
	sld.location	= "SanAugustineResidence";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.location.baseShip = "11"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto11_6";
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе	
	sld.location.hours = 7; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\Mentos.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "ment"; //тип нпс
	sld.talker = true; //начать диалог
	sld.watchBoxes = true;
	sld.greeting = "pirat_common";
	SetSPECIAL(sld, 10, 4, 9, 6, 8, 9, 7);
	SetSelfSkill(sld, 70, 70, 95, 30, 90);
	SetShipSkill(sld, 10, 10, 5, 20, 20, 30, 10, 10, 60);
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Ciras");
	SetCharacterPerk(sld, "Grus");
	SetCharacterPerk(sld, "BasicAttack");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "AdvancedAttack");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunAdvanced");
	//черты
	SetCharacterPerk(sld, "LoyalOff");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	//клановые болванчики
	CreateLSCGuardClan();

	// ------------------------ таверна ------------------------ 
	//тавернщик
	sld = GetCharacter(NPC_GenerateCharacter("LSCBarmen", "Hill_Brunner", "man", "man", 20, PIRATE, -1, false));
	sld.name = FindPersonalName("LSCBarmen_name");
	sld.lastname = FindPersonalName("LSCBarmen_lastname");
	sld.rank = 20;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.dialog.filename   = "Quest\LostShipsCity\Barmen.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "tavern"; //тип нпс
	sld.greeting = "Gr_Barmen";
	LAi_SetBarmanType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	//официантка
	sld = GetCharacter(NPC_GenerateCharacter("LSCwaitress", "CitizenWom_1", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = FindPersonalName("LSCwaitress_name");
	sld.lastname = FindPersonalName("LSCwaitress_lastname");
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "waitress";
	sld.location.locator = "barmen";
	sld.dialog.filename   = "Quest\LostShipsCity\Waitress.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "tavern"; //тип нпс
	sld.greeting = "Armo_Dulin";
	LAi_SetWaitressType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ внешние горожане ------------------------	
	// внешний горожанин Педро Хуртадо
	sld = GetCharacter(NPC_GenerateCharacter("PedroHurtado", "trader_6", "man", "man", 10, PIRATE, -1, true));
	sld.name = FindPersonalName("PedroHurtado_name");
	sld.lastname = FindPersonalName("PedroHurtado_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto06_1";
	sld.location.baseShip = "06"; //базовый корабль в ГПК
	sld.location.baseLocator = sld.location.locator;
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 2; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\PedroHurtado.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внешний горожанин Жиль Бару
	sld = GetCharacter(NPC_GenerateCharacter("ZhilBaru", "trader_16", "man", "man", 10, PIRATE, -1, true));
	sld.name = FindPersonalName("ZhilBaru_name");
	sld.lastname = FindPersonalName("ZhilBaru_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto07_1";
	sld.location.baseShip = "07"; //базовый корабль в ГПК
	sld.location.baseLocator = sld.location.locator;
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 1; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\ZhilBaru.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внешний горожанин Тристан Борчер
	sld = GetCharacter(NPC_GenerateCharacter("TristanBorcher", "citiz_48", "man", "man", 10, PIRATE, -1, false));
	sld.name = FindPersonalName("TristanBorcher_name");
	sld.lastname = FindPersonalName("TristanBorcher_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto09_1";
	sld.location.baseShip = "09"; //базовый корабль в ГПК
	sld.location.baseLocator = sld.location.locator;
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 3; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\TristanBorcher.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внешний горожанин Ройел Хааг
	sld = GetCharacter(NPC_GenerateCharacter("RoyelHaag", "trader_11", "man", "man", 10, PIRATE, -1, false));
	sld.name = FindPersonalName("RoyelHaag_name");
	sld.lastname = FindPersonalName("RoyelHaag_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto14_1";
	sld.location.baseShip = "14"; //базовый корабль в ГПК
	sld.location.baseLocator = sld.location.locator;
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\RoyelHaag.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внешний горожанин Доминик Легро
	sld = GetCharacter(NPC_GenerateCharacter("DominicLegro", "trader_10", "man", "man", 10, PIRATE, -1, false));
	sld.name = FindPersonalName("DominicLegro_name");
	sld.lastname = FindPersonalName("DominicLegro_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto15_1";
	sld.location.baseShip = "15"; //базовый корабль в ГПК
	sld.location.baseLocator = sld.location.locator;
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\DiminicLegro.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внешний горожанин Джорж Стоукс
	sld = GetCharacter(NPC_GenerateCharacter("JorgeStouks", "barmen_5", "man", "man", 10, PIRATE, -1, true));
	sld.name = FindPersonalName("JorgeStouks_name");
	sld.lastname = FindPersonalName("JorgeStouks_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "LostShipsCity_town";
	sld.location.group = "goto";
	sld.location.locator = "goto08_1";
	sld.location.baseShip = "08"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto08_1";
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\JorgeStouks.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "Gr_JorgeStouks";
	sld.talker = true; //начать диалог
	LAi_RemoveLoginTime(sld);	
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");
	//ChangeCharacterAddress(sld, "LostShipsCity_town", "goto16_3");
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "ring");

	// ------------------------ внешние горожане в таверне ------------------------
	// в таверне Генри Фолдер
	sld = GetCharacter(NPC_GenerateCharacter("HenryFolder", "barmen_14", "man", "man", 10, PIRATE, -1, false));
	sld.name = FindPersonalName("HenryFolder_name");
	sld.lastname = FindPersonalName("HenryFolder_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit2";
	sld.location.baseShip = "05"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto05_2";
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 6; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\HenryFolder.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Феликс Мендоза
	sld = GetCharacter(NPC_GenerateCharacter("FelixMendoza", "shipowner_9", "man", "man", 10, PIRATE, -1, true));
	sld.name = FindPersonalName("FelixMendoza_name");
	sld.lastname = FindPersonalName("FelixMendoza_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit3";
	sld.location.baseShip = "10"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto10_2";
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\FelixMendoza.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Роджер Воулер
	sld = GetCharacter(NPC_GenerateCharacter("RodgerWoyler", "vrach_2", "man", "man", 10, PIRATE, -1, false));
	sld.name = FindPersonalName("RodgerWoyler_name");
	sld.lastname = FindPersonalName("RodgerWoyler_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit5";
	sld.location.baseShip = "01"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto01_2";
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 7; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\RodgerWoyler.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Андрэ Лабор
	sld = GetCharacter(NPC_GenerateCharacter("AndreLabor", "shipowner_7", "man", "man", 15, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 15, 60, 60, "blade20", "pistol2", 10);
	sld.name = FindPersonalName("AndreLabor_name");
	sld.lastname = FindPersonalName("AndreLabor_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit9";
	sld.location.baseShip = "15"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto15_2";
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\AndreLabor.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "Gr_Master";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Стефан Клейн
	sld = GetCharacter(NPC_GenerateCharacter("StefanKleyn", "worker_49", "man", "man", 10, PIRATE, -1, true));
	sld.name = FindPersonalName("StefanKleyn_name");
	sld.lastname = FindPersonalName("StefanKleyn_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit8";
	sld.location.baseShip = "14"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto14_2";  
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 3; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\StefanKleyn.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Томас Фланн
	sld = GetCharacter(NPC_GenerateCharacter("ThomasFlann", "citiz_12", "man", "man", 10, PIRATE, -1, false));
	sld.name = FindPersonalName("ThomasFlann_name");
	sld.lastname = FindPersonalName("ThomasFlann_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit6";
	sld.location.baseShip = "02"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto02_2";  
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 3; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\ThomasFlann.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	sld.talker = true; //начать диалог
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в таверне Пабло Барадес
	sld = GetCharacter(NPC_GenerateCharacter("PabloBarades", "citiz_22", "man", "man", 10, PIRATE, -1, true));
	sld.name = FindPersonalName("PabloBarades_name");
	sld.lastname = FindPersonalName("PabloBarades_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit14";
	sld.location.baseShip = "09"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto09_2";  
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\PabloBarades.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "cit_common";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ внешние горожане в церкви ------------------------
	// падре
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Priest", "priest_3", "man", "man", 5, PIRATE, -1, false));
	sld.name = FindPersonalName("LSC_Priest_name");
	sld.lastname = FindPersonalName("LSC_Priest_lastname");
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "GloriaChurch";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.dialog.filename   = "Quest\LostShipsCity\Priest.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "priest"; //тип нпс
	sld.greeting = "Gr_padre";
	LAi_SetPriestType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);		
	
	// в церкви Сандра Гомес
	sld = GetCharacter(NPC_GenerateCharacter("SandraGomes", "women_4", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = FindPersonalName("SandraGomes_name");
	sld.lastname = FindPersonalName("SandraGomes_lastname");
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "GloriaChurch";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.location.baseShip = "04"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto04_3";
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\SandraGomes.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// в церкви Моника Райт
	sld = GetCharacter(NPC_GenerateCharacter("MonikaRight", "women_5", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = FindPersonalName("MonikaRight_name");
	sld.lastname = FindPersonalName("MonikaRight_lastname");
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "GloriaChurch";
	sld.location.group = "goto";
	sld.location.locator = "goto2";
	sld.location.baseShip = "08"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto08_3";
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\MonikaRight.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ магазин ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Trader", "merch_12", "man", "man", 20, PIRATE, -1, true));
	sld.name = FindPersonalName("LSC_Trader_name");
	sld.lastname = FindPersonalName("LSC_Trader_lastname");
	sld.rank = 20;
	sld.city = "LostShipsCity";
	sld.location	= "EsmeraldaStoreBig";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.dialog.filename   = "Quest\LostShipsCity\Trader.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "trader"; //тип нпс
	sld.greeting = "tra_common";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	sld.Merchant = true; //атрибут можно будет снять, когда не будет соотв. проверки в интерфейсе
	sld.money = 8000000 + makeint(frand(1.0)*2000000); // барыга ГПК, у него много бабла, но он не обновляется

	// ------------------------ Тюрьма ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("LSC_PrisonerHead", "Eksmes", "man", "man", 40, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 40, 87, 87, "blade32", "pistol4", 100);
	sld.name = FindPersonalName("LSC_PrisonerHead_name");
	sld.lastname = FindPersonalName("LSC_PrisonerHead_lastname");
	sld.rank = 40;
	sld.city = "LostShipsCity";
	sld.location = "TartarusPrison";
	sld.location.group = "sit";
	sld.location.locator = "sit1";
	sld.dialog.filename   = "Quest\LostShipsCity\Prisoner.c";
	sld.dialog.currentnode   = "prisonerHead";
	sld.cityTape = "prisonerHead"; //тип нпс
	sld.greeting = "pirat_common";
	sld.standUp = true; //вставать и нападать на врага 
	sld.watchBoxes = true;
	sld.location.days = 2; //передвижения через .. дней
	//sld.talker = true; //начать диалог
	LAi_SetHuberType(sld);
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);	
	SaveCurrentNpcQuestDateParam(sld, "location");

	// тюремщик №1
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Prisoner1", "Thomas_Boyle", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade21", "pistol3", 100);
	sld.name = FindPersonalName("LSC_Prisoner1_name");
	sld.lastname = FindPersonalName("LSC_Prisoner1_lastname");
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "TartarusPrison";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\LostShipsCity\Prisoner.c";
	sld.dialog.currentnode   = "Prisoner";
	sld.cityTape = "prisoner"; //тип нпс
	sld.greeting = "pirat_common";
	sld.standUp = true; //вставать и нападать на врага 
	sld.watchBoxes = true;
	sld.location.hours = 4; //передвижения через .. часов
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// ------------------------ Банкир-чернокнижник ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("LSC_Usurer", "LSC_Usurer", "man", "man", 30, PIRATE, -1, true));
	sld.name = FindPersonalName("LSC_Usurer_name");
	sld.lastname = FindPersonalName("LSC_Usurer_lastname");
	sld.rank = 30;
	sld.city = "LostShipsCity";
	sld.location	= "CarolineBank";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.dialog.filename   = "Quest\LostShipsCity\Usurer.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "usurer"; //тип нпс
	sld.greeting = "LSC_Usurer";
	LAi_SetImmortal(sld, true);
	LAi_RemoveLoginTime(sld);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);	

	// ------------------------ Механик ------------------------
	sld = GetCharacter(NPC_GenerateCharacter("Mechanic", "Henry_Mechanic", "man", "man", 5, PIRATE, -1, false));
	sld.name = FindPersonalName("Mechanic_name");
	sld.lastname = FindPersonalName("Mechanic_lastname");
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.dialog.filename   = "Quest\LostShipsCity\Mechanic.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "mechanic"; //тип нпс
	sld.greeting = "mechanic";
	LAi_RemoveLoginTime(sld);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);

	// ------------------------ внутренние горожане ------------------------
	// внутреняя горожанка Элис Тейлор
	sld = GetCharacter(NPC_GenerateCharacter("ElisTaylor", "women_3", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = FindPersonalName("ElisTaylor_name");
	sld.lastname = FindPersonalName("ElisTaylor_lastname");
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "CeresSmithy";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.location.baseShip = "03"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto03_0";
	sld.location.baseLocation = "CeresSmithy"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\ElisTaylor.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внутреняя горожанка Орели Бертин
	sld = GetCharacter(NPC_GenerateCharacter("OreliBertin", "oldWoman_2", "woman", "towngirl", 5, PIRATE, -1, false));
	sld.name = FindPersonalName("OreliBertin_name");
	sld.lastname = FindPersonalName("OreliBertin_lastname");
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "FurieShipInside2";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.location.baseShip = "06"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto06_0";
	sld.location.baseLocation = "FurieShipInside2"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 6; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\OreliBertin.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внутреняя горожанка Леа Тоорс
	sld = GetCharacter(NPC_GenerateCharacter("LeaToors", "women_7", "woman", "towngirl", 5, PIRATE, -1, false));//watch_coas_moment
	sld.name = FindPersonalName("LeaToors_name");
	sld.lastname = FindPersonalName("LeaToors_lastname");
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "PlutoStoreSmall";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.location.baseShip = "09"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto09_0";
	sld.location.baseLocation = "PlutoStoreSmall"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\LeaToors.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внутреняя горожанка Элиза Кальво
	sld = GetCharacter(NPC_GenerateCharacter("ElizaCalvo", "women_8", "woman", "towngirl", 5, PIRATE, -1, false));//watch_coas_moment
	sld.name = FindPersonalName("ElizaCalvo_name");
	sld.lastname = FindPersonalName("ElizaCalvo_lastname");
	sld.rank = 5;
	sld.city = "LostShipsCity";
	sld.location	= "SantaFlorentinaShipInside4";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.location.baseShip = "14"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto14_0";
	sld.location.baseLocation = "SantaFlorentinaShipInside4"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 7; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\ElizaCalvo.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_Woman_Citizen";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внутреняя горожанка Сесиль Галард
	sld = GetCharacter(NPC_GenerateCharacter("SesilGalard", "oldWoman_1", "woman", "towngirl", 10, PIRATE, -1, false));
	sld.name = FindPersonalName("SesilGalard_name");
	sld.lastname = FindPersonalName("SesilGalard_lastname");
	sld.rank = 10;
	sld.city = "LostShipsCity";
	sld.location	= "AvaShipInside3";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.location.baseShip = "15"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto15_0";
	sld.location.baseLocation = "AvaShipInside3"; //базовая внутреняя локация
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе	
	sld.location.hours = 5; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\SesilGalard.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizenHome"; //тип нпс
	sld.greeting = "Gr_SesilGalard";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetOwnerType(sld);
	 LAi_SetHP(sld, 70.0, 70.0);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	// внешний горожанин Малькольм Фаун - контрабандист
	sld = GetCharacter(NPC_GenerateCharacter("MalcolmFawn", "Malcolm_Fawn", "man", "man", 19, PIRATE, -1, false));
	SetFantomParamFromRank(sld, 19, true);
	sld.name = FindPersonalName("MalcolmFawn_name");
	sld.lastname = FindPersonalName("MalcolmFawn_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "FleuronTavern";
	sld.location.group = "sit";
	sld.location.locator = "sit19";
	sld.location.baseShip = "02"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto02_3";
	sld.location.baseShip.going = true; //перемещаться между кораблями в городе
	sld.location.hours = 4; //передвижения через .. часов
	sld.dialog.filename   = "Quest\LostShipsCity\MalcolmFawn.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "citizen"; //тип нпс
	sld.greeting = "marginal";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetSitType(sld);
    //личные
    SetCharacterPerk(sld, "BasicDefense");
    SetCharacterPerk(sld, "Grus");
    SetCharacterPerk(sld, "HawkEye");
    SetCharacterPerk(sld, "ShipEscape");
    //корабельные
    SetCharacterPerk(sld, "ShipSpeedUp");
    SetCharacterPerk(sld, "ShipTurnRateUp");
    SetCharacterPerk(sld, "StormProfessional");
    SetCharacterPerk(sld, "BasicCommerce");
    SetCharacterPerk(sld, "AdvancedCommerce");
    SetCharacterPerk(sld, "WindCatcher");
    SetCharacterPerk(sld, "SailsMan");
    SetCharacterPerk(sld, "ArtOfDeals");
    SetCharacterPerk(sld, "Packer");
    SetCharacterPerk(sld, "ProfessionalCommerce");
    //черты
    SetCharacterPerk(sld, "HighwaySmuggler");
    SetCharacterPerk(sld, "LoyalOff");
    SetCharacterPerk(sld, "Honest");
    //добавлены пиратес, перки, черты, зарплата и лояльность
    LAi_SetHP(sld, 300.0, 350.0);
    SetSPECIAL(sld, 7,10,10,6,5,4,8); //(Сила, Воспр, Выносл, Обаян, Обуч, Реак, Удача)
    SetSelfSkill(sld, 43,18,18,20,53); //(ЛО, СО, ТО, пистолеты, фортуна)
    SetShipSkill(sld, 16,74,10,5,65,10,5,10,73); //(лидер, торг, точн, пушки, навиг, ремонт, аборд, защита, скрыт)
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	SaveCurrentNpcQuestDateParam(sld, "location");

	//------------------- Клан Нарвал -------------------
	// нарвал главарь
	sld = GetCharacter(NPC_GenerateCharacter("Narval_head", "Narval_head", "man", "man", 35, PIRATE, -1, true));//watch_coas_moment
	FantomMakeCoolFighter(sld, 35, 100, 100, "blade28", "pistol4", 200);
	sld.name = FindPersonalName("Narval_head_name");
	sld.lastname = FindPersonalName("Narval_head_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	LAi_warrior_DialogEnable(sld, false);
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, true);
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true;   // не убирать труп через 200с
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
	SaveCurrentNpcQuestDateParam(sld, "location"); //главе клана сделаем перемещения
	// нарвал №1
	sld = GetCharacter(NPC_GenerateCharacter("Narval_1", "narval_14", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 60, 60, "blade21", "pistol6", 70);
	sld.name = FindPersonalName("Narval_1_name");
	sld.lastname = FindPersonalName("Narval_1_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto2";
	LAi_warrior_DialogEnable(sld, false);
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
	// нарвал №2
	sld = GetCharacter(NPC_GenerateCharacter("Narval_2", "narval_15", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 26, 80, 80, "blade34", "pistol3", 70);
	sld.name = FindPersonalName("Narval_2_name");
	sld.lastname = FindPersonalName("Narval_2_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto3";
	LAi_warrior_DialogEnable(sld, false);
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
	// нарвал №3
	sld = GetCharacter(NPC_GenerateCharacter("Narval_3", "narval_12", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 24, 70, 70, "blade25", "pistol5", 70);
	sld.name = FindPersonalName("Narval_3_name");
	sld.lastname = FindPersonalName("Narval_3_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto4";
	LAi_warrior_DialogEnable(sld, false);
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
	// нарвал №4
	sld = GetCharacter(NPC_GenerateCharacter("Narval_4", "narval_10", "man", "man", 12, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 50, 50, "blade13", "pistol2", 50);
	sld.name = FindPersonalName("Narval_4_name");
	sld.lastname = FindPersonalName("Narval_4_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto12";
	LAi_warrior_DialogEnable(sld, false);
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
	// нарвал №5
	sld = GetCharacter(NPC_GenerateCharacter("Narval_5", "narval_15", "man", "man", 20, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "topor2", "pistol3", 75);
	sld.name = FindPersonalName("Narval_5_name");
	sld.lastname = FindPersonalName("Narval_5_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	LAi_warrior_DialogEnable(sld, false);
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
	// нарвал №6
	sld = GetCharacter(NPC_GenerateCharacter("Narval_6", "narval_11", "man", "man", 15, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 22, 45, 45, "blade22", "pistol6", 35);
	sld.name = FindPersonalName("Narval_5_name");
	sld.lastname = FindPersonalName("Narval_5_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto7";
	LAi_warrior_DialogEnable(sld, false);
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");
	// нарвал №7
	sld = GetCharacter(NPC_GenerateCharacter("Narval_7", "narval_13", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 85, 85, "blade23", "pistol4", 110);
	sld.name = FindPersonalName("Narval_5_name");
	sld.lastname = FindPersonalName("Narval_5_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "VelascoShipInside1";
	sld.location.group = "goto";
	sld.location.locator = "goto11";
	LAi_warrior_DialogEnable(sld, false);
	sld.cityTape = "narval"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_NARVAL");

	//------------------- Клан Каспер -------------------
	// каспер главарь
	sld = GetCharacter(NPC_GenerateCharacter("Casper_head", "Valet_5", "man", "man", 35, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 35, 100, 100, "blade28", "pistol5", 200);
	sld.name = FindPersonalName("Casper_head_name");
	sld.lastname = FindPersonalName("Casper_head_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto8"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	//SaveCurrentNpcQuestDateParam(sld, "location"); //главе клана сделаем перемещения
	//каспер №1
	sld = GetCharacter(NPC_GenerateCharacter("Casper_1", "Casper_8", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 80, 80, "topor2", "pistol3", 100);
	sld.name = FindPersonalName("Casper_1_name");
	sld.lastname = FindPersonalName("Casper_1_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto4"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetWarriorType(sld);
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	//каспер №2
	sld = GetCharacter(NPC_GenerateCharacter("Casper_2", "Casper_5", "man", "man", 21, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 21, 80, 80, "blade26", "pistol6", 120);
	sld.name = FindPersonalName("Casper_2_name");
	sld.lastname = FindPersonalName("Casper_2_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto6"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	//каспер №3
	sld = GetCharacter(NPC_GenerateCharacter("Casper_3", "Casper_12", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "blade34", "pistol4", 150);
	sld.name = FindPersonalName("Casper_3_name");
	sld.lastname = FindPersonalName("Casper_3_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto5"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	//каспер №4
	sld = GetCharacter(NPC_GenerateCharacter("Casper_4", "Casper_6", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 70, 70, "blade23", "pistol3", 100);
	sld.name = FindPersonalName("Casper_4_name");
	sld.lastname = FindPersonalName("Casper_4_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto7"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	//каспер №5
	sld = GetCharacter(NPC_GenerateCharacter("Casper_5", "Casper_7", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "topor2", "pistol3", 130);
	sld.name = FindPersonalName("Casper_4_name");
	sld.lastname = FindPersonalName("Casper_4_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto13"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	//каспер №6
	sld = GetCharacter(NPC_GenerateCharacter("Casper_6", "Casper_10", "man", "man", 29, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 29, 80, 80, "blade25", "pistol4", 100);
	sld.name = FindPersonalName("Casper_6_name");
	sld.lastname = FindPersonalName("Casper_6_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto1";
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	//каспер №7
	sld = GetCharacter(NPC_GenerateCharacter("Casper_7", "Casper_12", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade34", "pistol6", 150);
	sld.name = FindPersonalName("Casper_7_name");
	sld.lastname = FindPersonalName("Casper_7_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto2"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	//каспер №8
	sld = GetCharacter(NPC_GenerateCharacter("Casper_8", "officer_28", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade26", "pistol4", 150);
	sld.name = FindPersonalName("Casper_8_name");
	sld.lastname = FindPersonalName("Casper_8_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto3"; // 	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	//каспер №9
	sld = GetCharacter(NPC_GenerateCharacter("Casper_9", "officer_27", "man", "man", 30, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade28", "pistol6", 150);
	sld.name = FindPersonalName("Casper_9_name");
	sld.lastname = FindPersonalName("Casper_9_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto10"; //
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	//каспер №10
	sld = GetCharacter(NPC_GenerateCharacter("Casper_10", "Casper_9", "man", "man", 25, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 25, 80, 80, "blade28", "pistol3", 150);
	sld.name = FindPersonalName("Casper_10_name");
	sld.lastname = FindPersonalName("Casper_10_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto11"; //	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	//каспер №11
	sld = GetCharacter(NPC_GenerateCharacter("Casper_11", "Casper_11", "man", "man", 27, PIRATE, -1, true));
	FantomMakeCoolFighter(sld, 27, 80, 80, "blade28", "pistol4", 250);
	sld.name = FindPersonalName("Casper_11_name");
	sld.lastname = FindPersonalName("Casper_11_lastname");
	sld.city = "LostShipsCity";
	sld.location	= "SanGabrielMechanic";
	sld.location.group = "goto";
	sld.location.locator = "goto12"; 	
	sld.dialog.filename   = "Quest\LostShipsCity\Casper.c";
	sld.dialog.currentnode   = "First time";
	sld.cityTape = "casper"; //тип нпс
	sld.greeting = "pirat_common";
	LAi_SetImmortal(sld, true);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");

	LSC_AddSecondaryQuestMarksToCitizens();
}

void LSC_WarWithNarval(string qName)
{
	LAi_group_SetRelation("LSC_NARVAL", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("LSC_NARVAL", LAI_GROUP_PLAYER, true);
}

void LSC_WarWithCasper(string qName)
{
	LAi_group_SetRelation("LSC_CASPER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
}

//снять шторм
void LSC_stormTimer_1(string qName)
{
	for(int i=0; i<MAX_LOCATIONS; i++)
	{				
		if (CheckAttribute(&locations[i], "fastreload") && locations[i].fastreload == "LostShipsCity")
		{			
			DeleteAttribute(&locations[i], "alwaysStorm");
			DeleteAttribute(&locations[i], "storm");
			DeleteAttribute(&locations[i], "tornado");	
			DeleteAttribute(&locations[i], "QuestlockWeather");
			DeleteAttribute(&locations[i], "MaxWaveHeigh");
		}
	}
	WeatherParams.Storm = false;
	//адмирал ловит ГГ, если тот ещё не явился к нему
	if (pchar.questTemp.LSC == "AdmiralIsWaiting")
	{
		pchar.quest.LSC_admiralOwnFind.win_condition.l1 = "location";
		pchar.quest.LSC_admiralOwnFind.win_condition.l1.location = "LostShipsCity_town";
		pchar.quest.LSC_admiralOwnFind.function = "LSC_admiralOwnFind";
	}
}

void LSC_admiralOwnFind(string qName)
{
	chrDisableReloadToLocation = true;
	DoQuestFunctionDelay("LSC_admiralOwnFind_1", 1+rand(2));
}

void LSC_admiralOwnFind_1(string qName)
{
	ref sld = characterFromId("LSCMayor");
	sld.dialog.currentnode = "FoundHero";
	PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void LSC_admiralTakeAll()
{
	chrDisableReloadToLocation = false;
	//установим типовые ключи -->
	ref sld = ItemsFromID("key1");
	sld.shown = true;
	sld.startLocation = "LostShipsCity_town";
	sld.startLocator = "item1";
	//--
	sld = ItemsFromID("key2");
	sld.shown = true;
	sld.startLocation = "VelascoShipInside1";
	sld.startLocator = "item1";
	//--
	sld = ItemsFromID("key3");
	sld.shown = true;
	sld.startLocation = "EsmeraldaStoreBig";
	sld.startLocator = "item1";
	//откроем кланы
	ref rLoc = &locations[FindLocation("LostShipsCity_town")];
	DeleteAttribute(rLoc, "reload.l70.disable");
	DeleteAttribute(rLoc, "reload.l72.disable");
	pchar.questTemp.LSC = "AfterAdmiral";
	StoreEquippedMaps(pchar); // ugeen --> сохраним карты из атласа дабы Чад не прибрал
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
	RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, MAPS_ITEM_TYPE);
	//сносим все предметы, кроме квестовых -->
    aref arItems;
	string sName;
	int a;
    makearef(arItems, pchar.items);
    int	Qty = GetAttributesNum(arItems);
    sld = CharacterFromId("LSCMayor");
    for (a=0; a<Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		rLoc = ItemsFromID(sName);
		if (rLoc.ItemType == "QUESTITEMS")
		{
			pchar.questTemp.items.(sName) = pchar.items.(sName);
		}
		else //остальное перемещаем Чаду
		{
		    if (CheckAttribute(rLoc, "groupID") && rLoc.groupID != MAPS_ITEM_TYPE)
		        sld.items.(sName) = pchar.items.(sName);
		}
    }
	DeleteAttribute(pchar, "items");
	pchar.items = "";
	makearef(arItems, pchar.questTemp.items);
    Qty = GetAttributesNum(arItems);
    for (a=0; a<Qty; a++)
    {
        sName = GetAttributeName(GetAttributeN(arItems, a));
		TakeNItems(pchar, sName, sti(arItems.(sName)));
    }
	DeleteAttribute(pchar, "questTemp.items");
	if(CheckCharacterItem(pchar, "MapsAtlas")) 
	{
		EquipCharacterByAtlas(pchar);	// экипируем атласом, если он есть
		RestoreEquippedMaps(pchar); 	// вернём карты в атлас в 1 экземпляре, все остальное Чадушке или в сундук Тизера
		RefreshEquippedMaps(pchar);
	}	
	//<-- сносим все предметы, кроме квестовых
	AddQuestRecord("ISS_MainLine", "3");
	AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase(StringFromKey("SexPhrase_17"),StringFromKey("SexPhrase_18")));
	AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("ин","ка"));
	GiveItem2Character(pchar, "unarmed"); //добавляем безоружность
	EquipCharacterbyItem(pchar, "unarmed");
	//------->>> пул нужных слухов для наводок на квесты		AddSimpleRumourCityTip("", "LostShipsCity", 10, 1, "LSC", "");
	//освобождение мужа Элис Тейлор
	LSC_beginElisHusband();
	sld = CharacterFromId("ElisTaylor");
	sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_47"), "LostShipsCity", 10, 1, "LSC", "LSC_rumourElisHusband");
    AddLandQuestMark_Main(sld, "ISS_ElisHusband");
	//квест со скелетом Лейтона Декстера
	sld = CharacterFromId("LeaToors");
	sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_48"), "LostShipsCity", 10, 1, "LSC", "LSC_rumourLostDecster");
	//наводка на Доминика Легро с вином
	sld = CharacterFromId("DominicLegro");
	sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_49"), "LostShipsCity", 10, 1, "LSC", "LSC_rumourBottleOfLegro");
	AddLandQuestMark_Main(sld, "TakeVineToPrisoner");
	//наводка на свечи для падре
	sld = CharacterFromId("LSC_Priest");
	sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_175"), "LostShipsCity", 10, 1, "LSC", "LSC_rumourTakeCandles");
	AddLandQuestMark_Main(sld, "ISS_takeCandles");
	//квест проникновения в дом хозяина магазина
	sld = CharacterFromId("PedroHurtado");
	AddLandQuestMark_Main(sld, "ISS_takeStoreMoney");
}

void LSC_returnBarmen(string qName)
{
	pchar.questTemp.LSC = "toWineCellarLate";
	ref sld = characterFromId("LSCBarmen");
	LAi_SetBarmanTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "barmen",  "stay");
	AddLandQuestMark_Main(sld, "ISS_MainLine");
}

void LSC_returnBarmen_2(string qName)
{
	ref sld = characterFromId("LSCBarmen");
	LAi_CharacterEnableDialog(sld);
	LAi_SetBarmanTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "barmen",  "stay");

	if (pchar.questTemp.LSC == "toDiffindoor")
	{
        AddLandQuestMark_Main(sld, "ISS_MainLine");
	}
}

void LSC_enterToProtector(string qName)
{
    chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
    DoQuestFunctionDelay("LSC_enterToProtector_1", 7.0);
}

void LSC_enterToProtector_1(string qName)
{
	LAi_group_Delete("EnemyFight");
    ref sld = GetCharacter(NPC_GenerateCharacter("LSCQuestMent", "officer_24", "man", "man", 25, PIRATE, 0, true));
	FantomMakeCoolFighter(sld, 25, 70, 70, "blade28", "pistol3", 50);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "LSCQuestMent";
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void LSC_KillOneNarval(string qName)
{
    if (qName == "LSC_KillOneNarval") DeleteQuestCheck("LSC_KillOneNarval2");
    else DeleteQuestCheck("LSC_KillOneNarval");
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
    DoQuestFunctionDelay("LSC_KillOneNarval_1", 3.0 + frand(4.0));
}

void LSC_KillOneNarval_1(string qName)
{
	LAi_group_Delete("EnemyFight");
    ref sld = GetCharacter(NPC_GenerateCharacter("LSCQuestNarval", "narval_15", "man", "man", 25, PIRATE, 0, true));
	FantomMakeCoolFighter(sld, 30, 80, 80, "blade21", "pistol6", 150);
	sld.Dialog.Filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "LSCQuestNarval";
	GiveItem2Character(sld, "RingNarval");
	sld.SaveItemsForDead   = true; // сохранять на трупе вещи
	sld.DontClearDead = true;  // не убирать труп через 200с
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void LSCNarvalAssault(string qName)
{
    int idxMent, i, iPos;
    pchar.questTemp.LSC.qtyOfficers = 0; //max 3
    pchar.questTemp.LSC.qtyDeadNarvals = 0; //max 7
    chrDisableReloadToLocation = true;
	//открываем закрытые двери
	LocatorReloadEnterDisable("SanAugustineResidence", "reload4", false);
	LocatorReloadEnterDisable("SanAugustineResidence", "reload7", false);
	LocatorReloadEnterDisable("SanAugustineResidence", "reload8", false);
	LocatorReloadEnterDisable("FleuronTavern", "reload3", false);
	LocatorReloadEnterDisable("FleuronTavern", "reload4", false);
	LocatorReloadEnterDisable("FleuronTavern", "reload5", false);
    //перемещение штурмовиков
    for (i = 1 ; i < 4; i++)
    {
        idxMent = GetCharacterIndex("Ment_" + i);
        if (idxMent != -1)
        {
            ChangeCharacterAddressGroup(&characters[idxMent], "LostShipsCity_town", "officers", "officer_"+i);
            characters[idxMent].Dialog.CurrentNode = "OffNarval";
            characters[idxMent].cityTape = "quest"; //тип нпс
            LAi_SetStayTypeNoGroup(&characters[idxMent]);
            DeleteAttribute(&characters[idxMent], "talker"); //запрещаем самим варешку открывать
            pchar.questTemp.LSC.qtyOfficers = sti(pchar.questTemp.LSC.qtyOfficers) + 1;
        }
    }
    //перемещение Воркмена
    idxMent = GetCharacterIndex("Ment_6");
	LAi_SetRolyPoly(&characters[idxMent], true); //ему рано умирать
    ChangeCharacterAddressGroup(&characters[idxMent], "LostShipsCity_town", "goto", "goto16_4");
    characters[idxMent].Dialog.CurrentNode = "NarvalAssault";
    DeleteAttribute(&characters[idxMent], "talker"); //запрещаем самим варешку открывать
    characters[idxMent].cityTape = "quest"; //тип нпс
    LAi_SetStayTypeNoGroup(&characters[idxMent]);
    //перемещение мушкетеров ментов для пущего антуража
    for (i = 7; i < 9; i++)
    {
        idxMent = GetCharacterIndex("MentMush_" + i);
        if (idxMent != -1)
        {
            if (i == 7) ChangeCharacterAddressGroup(&characters[idxMent], "LostShipsCity_town", "soldiers", "protector5");
            else ChangeCharacterAddressGroup(&characters[idxMent], "LostShipsCity_town", "soldiers", "mushketer5");
            characters[idxMent].Dialog.CurrentNode = "Ment_NarvalAssault";
            LAi_SetActorTypeNoGroup(&characters[idxMent]);
        }
    }
    //погибшие мушкетеры нарвалов
    for (i = 5; i < 7; i++)
    {
        idxMent = GetCharacterIndex("NarvalMush_" + i);
        if (idxMent != -1)
        {
			characters[idxMent].DontClearDead = true; // не убирать труп через 200с
            LAi_KillCharacter(&characters[idxMent]);
        }
        else pchar.questTemp.LSC.qtyDeadNarvals = sti(pchar.questTemp.LSC.qtyDeadNarvals) + 1; //max 2
    }
    //погибшие протекторы нарвалов
    for (i = 5; i < 7; i++)
    {
        idxMent = GetCharacterIndex("NarvalProt_" + i);
        if (idxMent != -1)
        {
			characters[idxMent].DontClearDead = true; // не убирать труп через 200с
            LAi_KillCharacter(&characters[idxMent]);
        }
        else pchar.questTemp.LSC.qtyDeadNarvals = sti(pchar.questTemp.LSC.qtyDeadNarvals) + 1; //max 2
    }
    //кто сбежал, а кто погиб из солдат нарвалов
    for (i = 3; i < 6; i++)
    {
        idxMent = GetCharacterIndex("NarvalSold_" + i);
        if (idxMent != -1)
        {
            if (i < 4)
            {
                iPos = i + 7;
                ChangeCharacterAddressGroup(&characters[idxMent], "VelascoShipInside1", "goto", "goto" + iPos);
            }
            else
            {
                characters[idxMent].DontClearDead = true; // не убирать труп через 200с
                LAi_KillCharacter(&characters[idxMent]);
            }
        }
        else pchar.questTemp.LSC.qtyDeadNarvals = sti(pchar.questTemp.LSC.qtyDeadNarvals) + 1; //max 3
    }
}

void NavalEnterOfficers(string qName)
{
	int idxMent;
    //перемещение штурмовиков
	for (int i=1 ; i<=3; i++)
	{
		idxMent = GetCharacterIndex("Ment_" + i);
		if (idxMent != -1)
		{
			ChangeCharacterAddressGroup(&characters[idxMent], "VelascoShipInside1", "officers", "officer_"+i);
			characters[idxMent].Dialog.CurrentNode = "AffterFightN";
			TakeNItems(&characters[idxMent],"potion2", 1);
			LAi_SetWarriorType(&characters[idxMent]);
			LAi_group_MoveCharacter(&characters[idxMent], LAI_GROUP_PLAYER);
		}
	}
    //перемещение Воркмента -->
    idxMent = GetCharacterIndex("Ment_6");
    LAi_SetWarriorType(&characters[idxMent]);
	LAi_group_MoveCharacter(&characters[idxMent], LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(&characters[idxMent], "VelascoShipInside1", "officers", "officer_4");
    characters[idxMent].Dialog.CurrentNode = "AffterFightNWorkman";
	//перемещение Воркмента <--
	LAi_group_SetCheck("LSC_NARVAL", "NarvalDestroyed");
	LAi_SetImmortal(characterFromId("Narval_head"), false);
    LAi_SetFightMode(pchar, true);
}

void LSC_scriptInterception(string qName)
{
	if (pchar.location == "FleuronTavern")
	{
		// LAi_SetActorType(pchar);
		chrDisableReloadToLocation = true;
		ref sld = characterFromId("LSCMayor");
		sld.Dialog.CurrentNode = "Interception";
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto3");
		LAi_ActorGoToLocator(sld, "quest", "stay1", "LSC_EnterComplite_1", -1);
		sld = characterFromId("Casper_head");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
		LAi_ActorGoToLocator(sld, "quest", "stay2", "LSC_EnterComplite_2", -1);		
	}
	else
	{
		pchar.questTemp.LSC = "InterceptionLate";
		AddQuestRecord("ISS_MainLine", "20");
		AddLandQuestMark_Main(CharacterFromID("LSCBarmen"), "ISS_MainLine");
	}
}

void LCS_EndScriptInterception()
{
    //на место камеру и пр.
	SetMainCharacterIndex(1);
    PChar = GetMainCharacter();
    LAi_SetPlayerType(PChar);
	locCameraTarget(PChar);
    locCameraFollowEx(true);
    EndQuestMovie();
	chrDisableReloadToLocation = false;
	//разводим адмирала и каспера
	ref sld = characterFromId("LSCMayor");
	sld.Dialog.CurrentNode = "First time";
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "goto", "goto3", "", -1.0);
	sld = characterFromId("Casper_head");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1.0);	
	//прерывание на возврат адмирала и каспера на места
	pchar.quest.LCS_EndScriptInterception_2.win_condition.l1 = "ExitFromLocation";
	pchar.quest.LCS_EndScriptInterception_2.win_condition.l1.location = pchar.location;
	pchar.quest.LCS_EndScriptInterception_2.function = "LCS_EndScriptInterception_2";
	if (pchar.questTemp.LSC == "InterceptionOk")
	{
		AddQuestRecord("ISS_MainLine", "23");
		AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase(StringFromKey("SexPhrase_13"),StringFromKey("SexPhrase_14")));
		AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("","а"));
	}
	else
	{
		AddQuestRecord("ISS_MainLine", "21");
		AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся","ась"));
		AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("","а"));
	}
    AddLandQuestMark_Main(CharacterFromID("LSCBarmen"), "ISS_MainLine");
}

void LCS_EndScriptInterception_2(string qName)
{
	ref sld = characterFromId("LSCMayor");
	sld.Dialog.CurrentNode = "First time";
	sld.location.going = "toTavern"; //посадим в таверну, ведь он туда пошёл
	SaveCurrentNpcQuestDateParam(sld, "location");
	LAi_SetHuberType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);	
	ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");

	sld = characterFromId("Casper_head");
	sld.Dialog.CurrentNode = "First time";
	//LAi_SetImmortal(sld, false);
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CASPER");
	ChangeCharacterAddressGroup(sld, "SanGabrielMechanic", "goto", "goto1");
}

void LSC_changeBarmen(string qName)
{
    pchar.quest.LSC_changeBarmen_2.win_condition.l1 = "location";
    pchar.quest.LSC_changeBarmen_2.win_condition.l1.location = "FleuronTavern";
    pchar.quest.LSC_changeBarmen_2.function = "LSC_changeBarmen_2";
}

void LSC_changeBarmen_2(string qName)
{
    pchar.questTemp.LSC = "barmenIsDead";
    ref sld = characterFromId("LSCBarmen");
    sld.name = FindPersonalName("LSCBarmen2_name");
    sld.lastname = FindPersonalName("LSCBarmen2_lastname");
    sld.model = "barmen_2"; //watch_coas_moment
    SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
    AddSimpleRumourCityTip(StringFromKey("Common_rumours_60"), "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
    AddSimpleRumourCityTip(StringFromKey("Common_rumours_61"), "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
    AddSimpleRumourCityTip(StringFromKey("Common_rumours_62"), "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
    AddSimpleRumourCityTip(StringFromKey("Common_rumours_63"), "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
    AddSimpleRumourCityTip(StringFromKey("Common_rumours_64"), "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
    AddSimpleRumourCityTip(StringFromKey("Common_rumours_65"), "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
    AddSimpleRumourCityTip(StringFromKey("Common_rumours_66"), "LostShipsCity", 10, 1, "LSC", "LSC_HillBrunnerDead");
    AddLandQuestMark_Main(sld, "ISS_MainLine");
    AddLandQuestMark_Main(characterFromID("LSCwaitress"), "ISS_MainLine");
    // закроем "Пей до дна", если ещё не начинали
    if (CheckAttribute(sld, "quest.drink"))
    {
        sld = CharacterFromID("PedroHurtado");
        if (!CheckAttribute(sld, "quest.drink"))
        {
            RemoveLandQuestMark_Main(sld, "LSC_Drink");
            CloseQuestHeader("LSC_Drink");
        }
    }
    //загоняем Сессиль в стойло
    sld = characterFromId("SesilGalard");
	sld.location = "AvaShipInside3";
	sld.location.group = "barmen";
	sld.location.locator = "stay";
	sld.cityTape = "quest";
    DeleteAttribute(sld, "location.going");
    LAi_RemoveLoginTime(sld);
}

void LSC_SaveSesilGalard(string qName)
{
	string sTemp;
	if (pchar.location.locator == "reload1") sTemp = "goto5";
	else sTemp = "goto4";
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	ref sld = characterFromId("SesilGalard");
	sld.dialog.currentnode = "HelpMe";
	sld.greeting = "Enc_SesilGalard";
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto",  sTemp);
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);

	RemoveLandQuestMark_Main(CharacterFromID("MalcolmFawn"), "ISS_MainLine");
    RemoveLandQuestMark_Main(CharacterFromID("HenryFolder"), "ISS_MainLine");
    RemoveLandQuestMark_Main(CharacterFromID("OreliBertin"), "ISS_MainLine");
}

void LSC_SaveSesilGalard_2()
{	
	LAi_SetFightMode(pchar, true);
	LAi_LocationFightDisable(loadedLocation, false);
	//Сесилия
	ref sld = characterFromID("SesilGalard");
	LAi_SetActorTypeNoGroup(sld);
	if (pchar.location.locator == "reload1") 
	{		
		LAi_ActorRunToLocator(sld, "barmen", "bar2", "LSC_SesilAfraid", -1);	
	}
	else 
	{
		LAi_ActorRunToLocator(sld, "barmen", "stay", "LSC_SesilAfraid", -1);	
	}
	//клановцы
	LAi_group_Delete("EnemyFight");
	int iTemp = 10+MOD_SKILL_ENEMY_RATE*2;
    for (int i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("LSCBandit"+i, "officer_"+i, "man", "man", iTemp, PIRATE, 0, true)); //watch_coas_moment
        FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor2", "pistol6", 50);
        LAi_SetWarriorType(sld);			
        LAi_group_MoveCharacter(sld, "EnemyFight");				
        if (i == 2)
			ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
		else
			ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "start"+i);
    }
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
    LAi_group_SetCheck("EnemyFight", "LSC_SesilAfterFight");
}

//вход к касперам на Сан Габриэль
void LSC_enterCasper(string qName)
{
    int iTemp;
    if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad")) //если отряд самоубийц с нами
    {
        aref suicideSquad;
        ref sld;
        makearef(suicideSquad, pchar.questTemp.LSC.suicideSquad);
        for (int i = 0; i < GetAttributesNum(suicideSquad); i++)
        {
            iTemp = sti(GetAttributeName(GetAttributeN(suicideSquad, i)));
            sld = &characters[iTemp];
            ChangeCharacterAddressGroup(sld, "SanGabrielMechanic", "reload", "reload1");
            LAi_SetCurHPMax(sld);
            TakeNItems(sld, "potion2", 5); //даём штурмовикам бутылочек немного
            LAi_CharacterDisableDialog(sld);
            LAi_SetRolyPoly(sld, true);
            LAi_SetWarriorTypeNoGroup(sld);
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        }
		
		LAi_group_SetCheck("LSC_CASPER", "LSC_StableSuicideSquadWaitRolyPoly");
    }
    else //если тюремщик Томас Бойл с нами
    {
	    iTemp = GetCharacterIndex("LSC_Prisoner1");
        if (iTemp != -1 && characters[iTemp].location == "SanGabrielMechanic")
        {
			LAi_SetCurHPMax(&characters[iTemp]);
            characters[iTemp].lifeDay = 0;
            LAi_warrior_DialogEnable(&characters[iTemp], true);
        }
		
		LAi_group_SetCheck("LSC_CASPER", "LSC_AfterFightCasperNoSuicideSquad");
    }

	//касперы
	iTemp = GetCharacterIndex("Casper_head");
	if (iTemp != -1 && characters[iTemp].location == "SanGabrielMechanic") 
	{
		chrDisableReloadToLocation = true;
		pchar.questTemp.LSC.CasperDestroyed = true;
		DoQuestFunctionDelay("LSC_CaspersReinforcementsFromDeck", 20.0); //подкрепление из недобитков на верхней палуб
		AddSimpleRumourCityTip(StringFromKey("Common_rumours_67"), "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip(StringFromKey("Common_rumours_68"), "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip(StringFromKey("Common_rumours_69"), "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip(StringFromKey("Common_rumours_70"), "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip(StringFromKey("Common_rumours_71"), "LostShipsCity", 10, 1, "LSC", "");
	}
	
	if (iTemp != -1 || pchar.questTemp.LSC != "toSeekMechanikCasperOff")
		LAi_SetFightMode(pchar, true);
	
	//откроем возможность попасть к механику.
	LocatorReloadEnterDisable("SanGabrielMechanic", "reload2", false);
	LocatorReloadEnterDisable("LostShipsCity_town", "reload55", false);
	pchar.questTemp.LSC = "toSeekMechanikCanMove";
	AddQuestRecord("ISS_DefeatCasperClan", "20");
	CloseQuestHeader("ISS_DefeatCasperClan");
	DeleteAttribute(pchar, "questTemp.LSC.Armo");

    // снимем квест-метки
    RemoveLandQuestMark_Main(CharacterFromID("MalcolmFawn"), "ISS_DefeatCasperClan");
    RemoveLandQuestMark_Main(CharacterFromID("Ment_6"), "ISS_DefeatCasperClan");
    RemoveLandQuestMark_Main(CharacterFromID("MaximTailor"), "ISS_DefeatCasperClan");
    RemoveLandQuestMark_Main(CharacterFromID("LSC_Usurer"), "ISS_DefeatCasperClan");
    iTemp = GetCharacterIndex("LSCStBandit3");
    if (iTemp != -1)
    {
        RemoveLandQuestMark_Main(&Characters[iTemp], "ISS_DefeatCasperClan");
    }
    iTemp = GetCharacterIndex("LSC_Prisoner1");
    if (iTemp != -1)
    {
        RemoveLandQuestMark_Main(&Characters[iTemp], "ISS_DefeatCasperClan");
    }
}

void LSC_CaspersReinforcementsFromDeck(string qName)
{
    int i, index;
    for (i = 1; i < 5; i++)
    {
        index = GetCharacterIndex("CasperProt_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index]))
        {
            LAi_SetWarriorTypeNoGroup(&characters[index]);
            PlaceCharacter(&characters[index], "reload", "random_must_be_near");
        }
    }
    for (i = 1; i < 5; i++)
    {
        index = GetCharacterIndex("CasperMush_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index]))
        {
            LAi_SetWarriorTypeNoGroup(&characters[index]);
            PlaceCharacter(&characters[index], "reload", "random_must_be_near");
        }
    }
    for (i = 1; i < 3; i++)
    {
        index = GetCharacterIndex("CasperSold_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index]))
        {
            LAi_SetWarriorTypeNoGroup(&characters[index]);
            PlaceCharacter(&characters[index], "reload", "random_must_be_near");
        }
    }
}

//прерывание на завал каспера от Армо
void LSC_KillOneCasper(string qName)
{
	pchar.quest.LSC_checkCasperDead.over = "yes";
	if (sti(pchar.questTemp.LSC.Armo) < 5)
	{
		pchar.questTemp.LSC.Armo = sti(pchar.questTemp.LSC.Armo) + 1; //на следующего...
		pchar.questTemp.LSC.Armo.waiting = true;
		AddQuestRecord("ISS_DefeatCasperClan", "5");
		AddQuestUserData("ISS_DefeatCasperClan", "sName", pchar.questTemp.LSC.Armo.casperFullName);
        ref sld = CharacterFromId("LSCwaitress");
        sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_72"), "LostShipsCity", 2, 1, "LSC", "");
        sld = CharacterFromId("ElisTaylor");
        sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_73"), "LostShipsCity", 2, 1, "LSC", "");
	}
	else
	{	//засада после третьего каспера
		SetBan("Looting", 1);

		LAi_SetStayType(pchar);
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);

		DoQuestFunctionDelay("LSC_KillOneCasper_3", 4.0);
		chrDisableReloadToLocation = true;
	}
}

void LSC_KillOneCasper_3(string qName)
{
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	ref sld = characterFromId("Casper_6");
	sld.dialog.currentnode = "FackYou";
	LAi_SetActorTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestLocator("reload", locx, locy, locz));
	
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}

//таймер завален ли каспер от Армо
void LSC_checkCasperDead(string qName)
{
	pchar.quest.LSC_KillOneCasper.over = "yes";
	int iTemp = sti(pchar.quest.(qName).casperIdx);
	if (!LAi_IsDead(&characters[iTemp]))
	{
		pchar.questTemp.LSC.Armo = 11; //профукал каспера
		ref sld = &characters[iTemp];
		sld.dialog.currentnode   = "First time";
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "LSC_CASPER");
		ChangeCharacterAddressGroup(sld, "SanGabrielMechanic", "goto", "goto9");
	}
}

void LSC_3CarperAttackArmo()
{
	float locx, locy, locz;

	SetBan("Looting", 0);
	chrDisableReloadToLocation = false;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	//меняем убитую Армо
	ref sld = characterFromId("LSCwaitress");
    sld.dialog.currentnode = "ArmoIsDead";
	sld.name = FindPersonalName("LSCwaitress2_name");
    sld.lastname = FindPersonalName("LSCwaitress2_lastname");
	sld.model = "women_2"; //watch_coas_moment
    SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
    AddSimpleRumourCityTip(StringFromKey("Common_rumours_74"), "LostShipsCity", 10, 1, "LSC", "");
    AddSimpleRumourCityTip(StringFromKey("Common_rumours_75"), "LostShipsCity", 10, 1, "LSC", "");
    AddSimpleRumourCityTip(StringFromKey("Common_rumours_76"), "LostShipsCity", 10, 1, "LSC", "");
    RemoveLandQuestMark_Main(sld, "ISS_DefeatCasperClan");
    AddLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "ISS_DefeatCasperClan");
	//первый каспер
	sld = characterFromId("Casper_6");
	sld.quest.checkCasper = true; //для обработки в АИ warrior
	LAi_SetWarriorTypeNoGroup(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	//второй
	sld = characterFromId("Casper_7");
	sld.quest.checkCasper = true; //для обработки в АИ warrior
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetWarriorTypeNoGroup(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	//третий
	sld = characterFromId("Casper_8");
	sld.quest.checkCasper = true; //для обработки в АИ warrior
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	AddQuestRecord("ISS_DefeatCasperClan", "8");
	AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся","ась"));
	LAi_SetWarriorTypeNoGroup(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
	
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
}

void LSC_TempTomasWarrior(string qName)
{
	int iTemp = GetCharacterIndex("LSC_Prisoner1");
	if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
	{
		ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, pchar.location.group, pchar.location.locator);
	}
}

void LSC_NotifySuicideSquadEnough(string qName)
{
	if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad"))
	{
		aref aSuicideSquad; makearef(aSuicideSquad, pchar.questTemp.LSC.suicideSquad);
		if (GetAttributesNum(aSuicideSquad) >= 2)
		{
			int chIndex1 = sti(GetAttributeName(GetAttributeN(aSuicideSquad, 0)));
			int chIndex2 = sti(GetAttributeName(GetAttributeN(aSuicideSquad, 1)));
			
			AddQuestRecord("ISS_DefeatCasperClan", "23");
			AddQuestUserData("ISS_DefeatCasperClan", "sName1", GetFullName(&characters[chIndex1]));
			AddQuestUserData("ISS_DefeatCasperClan", "sName2", GetFullName(&characters[chIndex2]));
		}
	}
}

void LSC_underwaterDeathTimer(string qName)
{
	GameOver("sea"); //TODO: отдельный лоадинг
}

//начать малый шторм
void LSC_SmallStormIsBegin()
{
    int i;
    ref sld;
	for(i=0; i<MAX_LOCATIONS; i++)
	{				
		if (CheckAttribute(&locations[i], "fastreload") && locations[i].fastreload == "LostShipsCity")
		{			
			locations[i].alwaysStorm = true; //живем в штормах
			if (locations[i].id == "LostShipsCity_town")
			{
				locations[i].alwaysStorm.WaveHeigh = true; //поднять уровень воды до 2.5 для низкого волнения
			}
			locations[i].storm = true;
			locations[i].tornado = true;			
		}
	}
	TEV.FinalMusicLSC = "";
	//пустим слух о шторме
	AddSimpleRumourCityTip(StringFromKey("Common_rumours_77"), "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip(StringFromKey("Common_rumours_78"), "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip(StringFromKey("Common_rumours_79"), "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip(StringFromKey("Common_rumours_80"), "LostShipsCity", 5, 1, "LSC", "");
	AddSimpleRumourCityTip(StringFromKey("Common_rumours_81"), "LostShipsCity", 5, 1, "LSC", "");
	//расставим нпс на свои места, штормовые. ограничиваем хождение по городу
	LAi_group_Delete("EnemyFight");
	for(i=0; i<MAX_CHARACTERS; i++)
	{	
		makeref(sld, characters[i]);
		if (CheckAttribute(sld, "city") && sld.city == "LostShipsCity")
		{	
			if (sld.cityTape == "mayor")
			{
				//LAi_SetImmortal(sld, false);
				DeleteAttribute(sld, "location.going");
				sld.cityTape = "notMove";  //не перемещаться более
				LAi_SetHuberType(sld); //садим за стол
				LAi_group_MoveCharacter(sld, "EnemyFight");	
				ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "sit", "sit1");
			}
			if (sld.cityTape == "ment")
			{
				if (sld.id == "Ment_6")
				{
					LAi_SetImmortal(sld, false);
					DeleteAttribute(sld, "location.going");
					sld.cityTape = "notMove";  //не перемещаться более
					LAi_SetLSCoutTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
				}
				else
				{
					string  sTemp = sld.id;
					sTemp = "goto" + strcut(sTemp, 5, 5);
					LAi_SetImmortal(sld, false);
					DeleteAttribute(sld, "location.going");
					sld.cityTape = "notMove";  //не перемещаться более
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "EnemyFight");
					ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", sTemp);
				}				
			}
			if (sld.cityTape == "citizenHome")
			{
				DeleteAttribute(sld, "location.going");
				sld.cityTape = "notMoveCitizen";  //не перемещаться более
				LAi_SetOwnerTypeNoGroup(sld);
				ChangeCharacterAddressGroup(sld, sld.location.baseLocation, "barmen", "stay");
			}
			if (sld.cityTape == "prisonerHead" || sld.cityTape == "prisoner")
			{
				LAi_SetImmortal(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
		}
	}
	//Ривадос исчезают
	int index;
    for (i = 1; i < 4; i++)
    {
		index = GetCharacterIndex("LSCStBandit" + i);
		if (index == -1 || LAi_IsDead(GetCharacter(index))) continue;
		sld = GetCharacter(index);
		LAi_SetImmortal(sld, false);
		SetLifeDay(sld, 0);
    }
}

void LSC_MoveSeekCrewToTavern()
{
	ref sld;
	int i;
	
	pchar.questTemp.LSC = "toSeekCrewInTavern";
	
	int sitCount = 1;
	int stayCount = 1;
	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		sld = &characters[i];
		if (CheckAttribute(sld, "city") && sld.city == "LostShipsCity" && or(sld.cityTape == "citizen", sld.cityTape == "notMoveCitizen"))
		{
			sld.cityTape = "quest"; //тип нпс
			DeleteAttribute(sld, "location.going");
			LAi_RemoveLoginTime(sld);
			if (sld.sex == "man")
			{
				FreeSitLocator("FleuronTavern", "sit"+sitCount);
				LAi_SetSitTypeNoGroup(sld);
				ChangeCharacterAddressGroup(sld, "FleuronTavern", "sit",  "sit"+sitCount);
				sitCount++;
			}
			else
			{
				LAi_SetCitizenTypeNoGroup(sld);
				ChangeCharacterAddressGroup(sld, "FleuronTavern", "goto",  "goto"+stayCount);
				stayCount++;
			}
		}
	}
	pchar.questTemp.LSC.crew = 0; //количество уговоренных людей.
	pchar.quest.LSC_toSeekCrewInTavern.win_condition.l1 = "location";
	pchar.quest.LSC_toSeekCrewInTavern.win_condition.l1.location = "FleuronTavern";
	pchar.quest.LSC_toSeekCrewInTavern.win_condition = "LSC_toSeekCrewInTavern";
}

void LSC_afterArestMachanic(string qName)
{
	ref sld = &characters[sti(pchar.questTemp.LSC.lastManId)];
	LAi_SetStayTypeNoGroup(sld);			
	ChangeCharacterAddressGroup(sld, "SanGabrielMechanic", "barmen",  "stay");
    sld.dialog.currentnode = "MechanicIsPrison_" + sld.sex;
	sld = characterFromId("Mechanic");
	ChangeCharacterAddress(sld, "none", "");
}

void LSC_fightEnterResidence(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	//отравляем наверх
	string sLocator;
	ref sld;
	int iTemp;
	for (int i = 1; i < 6; i++)
	{
	    iTemp = GetCharacterIndex("Ment_" + i);
        if (iTemp != -1)
        {
            sld = &characters[iTemp];
            LAi_CharacterReincarnation(sld, false, false);
            LAi_SetLSCoutTypeNoGroup(sld);
            sld.cityTape = "quest";
            sLocator = 2 + i;
            ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto11_" + sLocator);
        }
	}
	ref chr = CharacterFromID("LSCMayor");
	chr.dialog.currentnode = "fightTalking";
	LAi_SetImmortal(chr, false);
	LAi_SetActorTypeNoGroup(chr);
	ChangeCharacterAddressGroup(chr, "SanAugustineResidence", "goto", "goto10");
	LAi_ActorDialog(chr, pchar, "", -1.0, 0);
	for (int j = 1; j <= 3; j++)
	{
	    iTemp = GetCharacterIndex("MentProt_" + j);
        if (iTemp != -1)
        {
            sld = &characters[iTemp];
            LAi_SetActorType(sld);
            LAi_ActorFollow(sld, chr, "", -1);
        }
	}
}

void LSC_figtInResidence()
{
    int iTemp;
	ref sld = characterFromId("Ment_6");
	LAi_SetCurHPMax(sld);
	LAi_group_Delete("EnemyFight");
	if (sti(sld.quest.AngerAtAdmiral) >= 1)
	{
	    float locx, locy, locz;
	    LAi_SetRolyPoly(sld, true);
	    sld.quest.AngerAtAdmiral = 4;
        GetCharacterPos(pchar, &locx, &locy, &locz);
        LAi_SetWarriorTypeNoGroup(sld);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
        ChangeCharacterAddressGroup(sld, pchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
        RemoveLandQuestMark_Main(sld, "ISS_MainLine");
	}
	for (int i = 1; i <= 3; i++)
	{
	    iTemp = GetCharacterIndex("MentProt_" + i);
        if (iTemp != -1)
        {
            sld = &characters[iTemp];
            LAi_group_MoveCharacter(sld, "EnemyFight");
            LAi_SetWarriorTypeNoGroup(sld);
        }
	}
    pchar.quest.LSC_figtInResidence_1.win_condition.l1 = "NPC_Death";
    pchar.quest.LSC_figtInResidence_1.win_condition.l1.character = "LSCMayor";
    pchar.quest.LSC_figtInResidence_1.win_condition.l2 = "NPC_Death";
    pchar.quest.LSC_figtInResidence_1.win_condition.l2.character = "MentProt_1";
    pchar.quest.LSC_figtInResidence_1.win_condition.l3 = "NPC_Death";
    pchar.quest.LSC_figtInResidence_1.win_condition.l3.character = "MentProt_2";
    pchar.quest.LSC_figtInResidence_1.win_condition.l4 = "NPC_Death";
    pchar.quest.LSC_figtInResidence_1.win_condition.l4.character = "MentProt_3";
    pchar.quest.LSC_figtInResidence_1.function= "LSC_figtInResidence_1";
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
    //тюрьму открываем
    LocatorReloadEnterDisable("LostShipsCity_town", "reload51", false);
    LocatorReloadEnterDisable("LostShipsCity_town", "reload52", false);
    DeleteShellBoat("LostShipsCity_town");
}

void LSC_figtInResidence_1(string qName)
{
	ref sld = characterFromId("Ment_6");
	if (sld.quest.AngerAtAdmiral != "4")
    {
        AddQuestRecord("ISS_MainLine", "66");
        chrDisableReloadToLocation = false;
    }
	else if (!CharacterIsDead(sld))
	{
		LAi_QuestDelay("Wait_Ment6_to_up", 5.0);
	}
	else
	{
		AddQuestRecord("ISS_MainLine", "61");
		chrDisableReloadToLocation = false;
	}
	pchar.quest.LSC_enterToPrison.win_condition.l1 = "location";
	pchar.quest.LSC_enterToPrison.win_condition.l1.location = "TartarusPrison";
	pchar.quest.LSC_enterToPrison.function = "LSC_enterToPrison";
	pchar.quest.LSC_exitFromResidence.win_condition.l1 = "ExitFromLocation";
	pchar.quest.LSC_exitFromResidence.win_condition.l1.location = pchar.location;
	pchar.quest.LSC_exitFromResidence.function = "LSC_exitFromResidence";

}

void LSC_exitFromResidence(string qName)
{
    int iTemp;
    ref sld = characterFromId("Ment_6");
    LAi_SetCurHPMax(sld);
    LAi_SetActorType(sld);
    LAi_ActorSetStayMode(sld);
    ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto11_2");
    ChangeCharacterAddressGroup(pchar, "LostShipsCity_town", "reload", "reload1");
    chrDisableReloadToLocation = true;
    StartQuestMovie(false, false, true);
	for (int i = 1; i < 6; i++)
	{
	    iTemp = GetCharacterIndex("Ment_" + i);
        if (iTemp != -1)
        {
            sld = &characters[iTemp];
            LAi_SetActorType(sld);
            LAi_ActorGoToLocator(sld, "goto", "goto11_0", "", 0);
        }
	}
    LAi_SetActorType(pchar);
    LAi_ActorGoToLocator(pchar, "goto", "goto11_1", "LSC_talkWithWalker", 0);
    DoQuestFunctionDelay("LSC_exitFromResidenceCamera", 1.5);
}

void LSC_exitFromResidenceCamera(string qName)
{
    locCameraFromToPos(-10.927, 15.261, 8.544, true, 13.00, 2.00, -5.00);
}

void LSC_enterToPrison(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld = CharacterFromId("Mechanic");
	sld.dialog.currentnode = "inPrison";
	LAi_SetImmortal(sld, true);
	LAi_SetGroundSitType(sld);
	ChangeCharacterAddressGroup(sld, "TartarusPrison", "quest", "prison3");
	AddLandQuestMark_Main(sld, "ISS_MainLine");
	sld = CharacterFromId("LSC_PrisonerHead");
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_SetImmortal(sld, false);
	
	int iTemp = GetCharacterIndex("LSC_Prisoner1");
	if (iTemp != -1)
	{
		sld = &Characters[iTemp];
		
		if (CheckAttribute(sld, "cityTape") && sld.cityTape != "toLeave")
		{
			LAi_SetCurHPMax(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
	}
}

//начать большой шторм
void LSC_BigStormIsBegin()
{
	bDisableFastReload = true;
	string sTemp;
	int i = FindLocation("LostShipsCity_town");
	//закрываем релоады
    locations[i].notCreateFoam = true; //не рисовать пену
    locations[i].reload.l231.disable = true;
    for (int n=3; n<=78; n++)
    {
        sTemp = "l" + n;
        locations[i].reload.(sTemp).disable = true;
    }
    pchar.GenQuest.CannotWait = true; // лочим интерфейс отдыха
    LocatorReloadEnterDisable("LostShipsCity_town", "reload74", false);
    pchar.location.from_sea = "LostShipsCity_town";
    //погода
    ///////////////////////Конец/////////////////////////////////////////
    DeleteAttribute(&locations[i], "alwaysStorm");
    DeleteAttribute(&locations[i], "QuestlockWeather");
    DeleteAttribute(&locations[i], "MaxWaveHeigh");
    locations[i].alwaysStorm_2 = true; //живем в штормах
    locations[i].storm = true;
    locations[i].MaxWaveHeigh = 100;
    locations[i].MaxWaveHeigh.Amp1 = 64.0;
    locations[i].MaxWaveHeigh.Amp2 = 9.0;
   // locations[i].tornado = true;
	pchar.quest.LSC_goodbyeLine.win_condition.l1 = "location";
	pchar.quest.LSC_goodbyeLine.win_condition.l1.location = "FernandaDiffIndoor";
	pchar.quest.LSC_goodbyeLine.function = "LSC_goodbyeLine";
	//снять шторм с острова ГПК
	i = FindIsland("LostShipsCity");
	Islands[i].reload.l2.emerge = "reload2_back";
	Islands[i].reload_enable = false;
	Islands[i].visible = true;
	Islands[i].alwaysStorm = true; //живем в штормах
	Islands[i].storm = true;
	Islands[i].tornado = true;
	//прерывание на удаление острова ГПК и снятие шторма с ареала
	SetTimerFunction("LSC_takeStormIsland", 0, 0, 10);

	pchar.quest.LSC_StormWaterUp.win_condition.l1 = "ExitFromLocation";
    pchar.quest.LSC_StormWaterUp.win_condition.l1.location = pchar.location;
    pchar.quest.LSC_StormWaterUp.function = "LSC_StormWaterUp";
}

void LSC_StormWaterUp(string qName)
{
	//настраиваем немного большее затопление
	Whr_SetLock(true);
	Sea.MaxSeaHeight = 3.5;

	Sea.Sea2.Amp1 = 3.0;
	Sea.Sea2.AnimSpeed1 = 4.25;
	Sea.Sea2.Scale1 = 0.75;

	Sea.Sea2.Amp2 = 0.0;
	Sea.Sea2.AnimSpeed2 = 9.0;
	Sea.Sea2.Scale2 = 1.5;

	Sea.Sea2.FoamV = 1.1;
	Sea.Sea2.FoamK = 0.2;
	Sea.Sea2.FoamUV = 0.7;
    Sea.Sea2.PosShift = 0.75;
}

void LSC_goodbyeLine(string qName)
{
	ref sld;
	int iCount = 1;
	//закрываем выходы во избежании поломки скриптов
    LocatorReloadEnterDisable("FernandaDiffIndoor", "reload1", true);
    LocatorReloadEnterDisable("FernandaDiffIndoor", "reload2", true);
    LocatorReloadEnterDisable("FernandaDiffIndoor", "reload3", true);
    // снимем второстепенные квест метки
    LSC_RemoveSecondaryQuestMarksToCitizens();
    //человеков портируем в диффиндур для братания
    for (int i = 0; i < MAX_LOCATIONS; i++)
    {
        sld = &characters[i];
        if (CheckAttribute(sld, "cityTape") && sld.cityTape == "toLeave")
        {
            sld.dialog.currentnode = "GoodBye";
            ChangeCharacterAddressGroup(sld, "FernandaDiffIndoor", "goto",  "goto" + iCount);
            LAi_SetStayType(sld);
            if (sld.id != "MalcolmFawn" && sld.id != "Ment_6") sld.lifeday = 0;
            iCount++;
        }
    }
    sld = CharacterFromID("MalcolmFawn");
	LAi_RemoveLoginTime(sld);
    sld.dialog.currentnode = "BeginningOfTransportation";
    ChangeCharacterAddress(sld, "FernandaDiffIndoor", "goto12");
    LAi_SetActorType(sld);
    LAi_ActorDialog(sld, pchar, "", -1, 0);
	pchar.quest.LSC_closeLine.win_condition.l1 = "location";
	pchar.quest.LSC_closeLine.win_condition.l1.location = "LostShipsCity_town";
	pchar.quest.LSC_closeLine.function = "LSC_startFinishMovie";
}

//функция для опредения прогресса по финалу ГПК
void LSC_GoodByeEnough(string qName)
{
    if (pchar.location == "FernandaDiffIndoor")
	{
		int chIndex = LAi_FindNearestCharacter(pchar, 200.0);
		// Log_Info("Name is " + Characters[chIndex].name);
		if (chIndex == -1)
		{
			//открываем целевые выходы
			LocatorReloadEnterDisable("FernandaDiffIndoor", "reload2", false);
            LocatorReloadEnterDisable("FernandaDiffIndoor", "reload3", false);
		}
	}
}

void LSC_startFinishMovie(string qName)
{
	Sea.MaxSeaHeight = 7.0;

	Sea.Sea2.Amp1 = 6.0;
	Sea.Sea2.AnimSpeed1 = 4.25;
	Sea.Sea2.Scale1 = 0.5;

	Sea.Sea2.Amp2 = 4.0;
	Sea.Sea2.AnimSpeed2 = 9.0;
	Sea.Sea2.Scale2 = 0.5;

    Sea.Sea2.FoamV = 0.4;
    Sea.Sea2.FoamK = 0.04;
    Sea.Sea2.FoamUV = 0.2;
    Sea.Sea2.PosShift = 0.75;

    DeployShipToReload("LostShipsCity_town", "locators.reload.reload_diffIndoor");
    LocatorReloadEnterDisable("LostShipsCity_town", "reload77", true);
    LocatorReloadEnterDisable("LostShipsCity_town", "reload78", true);
}


void LSC_finishMovieWaterFallFunction(string qName)
{
    if (stf(Sea.MaxSeaHeight) < 25.0)
    {
        LSC_WaterUpFunction();
        DoQuestCheckDelay("LSC_finishMovieWaterFall", 0.02);
    }
    else
    {
        DoQuestCheckDelay("LSC_TeleportFromLSC", 1.0);
    }
}

void LSC_WaterUpFunction()
{
    Sea.MaxSeaHeight = stf(Sea.MaxSeaHeight) + 0.01;
    Sea.Sea2.Amp1 = stf(Sea.Sea2.Amp1) + 0.01;
    Sea.Sea2.Amp2 = stf(Sea.Sea2.Amp2) + 0.01;
    Sea.Sea2.Scale1 = stf(Sea.Sea2.Scale1) - 0.0002;
    Sea.Sea2.Scale2 = stf(Sea.Sea2.Scale2) - 0.0002;
    Sea.Sea2.FoamK = stf(Sea.Sea2.FoamK) - 0.000013;
	Sea.Sea2.FoamV = stf(Sea.Sea2.FoamV) + 0.004;
}

void LSC_closeLine(string qName)
{
	DeleteAttributeEx(&TEV, "captainInTheLSC,FinalMusicLSC");
	DeleteAttribute(pchar, "MermanTimer");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	DeleteAttribute(pchar, "questTemp.FindMapLSC");
	RemoveItems(pchar, "RingCapBook", 1);
	AddQuestRecord("ISS_MainLine", "65");
	AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("ISS_MainLine");
	CloseQuestHeader("TakeVineToPrisoner");
	CloseQuestHeader("LSC_findDekster");
	CloseQuestHeader("ISS_ElisHusband");
	CloseQuestHeader("ISS_takeStoreMoney");
	CloseQuestHeader("ISS_takeCandles");
	CloseQuestHeader("LSC_Ring");
	CloseQuestHeader("LSC_Drink");
	CloseQuestHeader("FindMapLSC");
	bQuestDisableMapEnter = false;
	bDisableFastReload = false;
	TakeItemFromCharacter(pchar, "admiralKey");
	TakeNItems(pchar, "Key1", -3);
	TakeNItems(pchar, "Key2", -3);
	TakeNItems(pchar, "Key3", -3);
	DeleteAttribute(pchar, "questTemp.LSC"); //много мусора, надо бы почистить
	pchar.questTemp.LSC = "over";
	pchar.questTemp.LSC.checkBoxes = false;
	if (CheckAttribute(&TEV, "QuestTemp.deadHoum"))
		DeleteAttribute(&TEV, "QuestTemp.deadHoum");
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	//проверим наличие займа у банкира ГПК
	ref sld = characterFromId("LSC_Usurer");
	if (CheckAttribute(sld, "quest.loan.qtyMoney") && sti(sld.quest.loan.qtyMoney) > 0)
	{	
		SetTimerFunction("LSC_climeUsurer", 0, 3 + rand(3), 0);
		pchar.questTemp.LSC_climeUsurer.qtyMoney = sti(sld.quest.loan.qtyMoney) * 5; //сколько денег к возврату
	}
	//проверяем состояние Малькольма
	CheckMalcolmStatus();
	//Уоркман теперь офицер
	sld = CharacterFromId("Ment_6");
	if (!LAi_IsDead(sld))
	{
	    DeleteAttribute(sld, "quest"); //забываем все ужасы ГПК
        sld.Dialog.Filename = "Officer_Man.c";
        sld.greeting = "Gr_questOfficer";
        Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
        sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
        sld.loyality = MAX_LOYALITY;
        LandEnc_OfficerHired();
		LAi_SetRolyPoly(sld, true);
	}
	//вещи из сундука диффиндура перекладываем в сундук каюты
	Set_My_Cabin();
	int iLoc = FindLocation("LostShipsCity_town");
	aref aFromBox, aToBox;
	makearef(aFromBox, Locations[iLoc].private11);
	iLoc = FindLocation("My_Cabin_Quest");
	makearef(aToBox, Locations[iLoc].box1);
    CopyAttributes(aToBox, aFromBox);
    DeleteAttribute(aFromBox, "money");
    DeleteAttribute(aFromBox, "items");
	//убираем жителей ГПК из игры
	for (int i=0; i<MAX_LOCATIONS; i++)
	{	
		sld = &characters[i];
		if (CheckAttribute(sld, "city") && sld.city == "LostShipsCity")
			sld.lifeDay = 0;	
	}
    pchar.quest.Nation_Legend_Map.win_condition.l1 = "MapEnter";
    pchar.quest.Nation_Legend_Map.win_condition = "LSC_StopStorm";

    Achievment_Set(ACH_Spasshiysya);
}

void LSC_takeStormIsland(string qName)
{	
	int i = FindIsland("LostShipsCity");
	Islands[i].reload_enable = false;
	Islands[i].visible = false;
	DeleteAttribute(&Islands[i], "alwaysStorm");
	DeleteAttribute(&Islands[i], "alwaysStorm_2");
	DeleteAttribute(&Islands[i], "storm");
	DeleteAttribute(&Islands[i], "tornado");
	DeleteAttribute(&Islands[i], "QuestlockWeather");
	DeleteAttribute(&Islands[i], "MaxSeaHeight");
	i = FindLocation("LostShipsCity_town");
    DeleteAttribute(&locations[i], "alwaysStorm");
    DeleteAttribute(&locations[i], "alwaysStorm_2");
    DeleteAttribute(&locations[i], "storm");
    DeleteAttribute(&locations[i], "tornado");
    DeleteAttribute(&locations[i], "QuestlockWeather");
    DeleteAttribute(&locations[i], "MaxWaveHeigh");
}

//------------ посетить жилые помещения магазина ----------->>>>>>
void LCS_SetPedroHurtado(string qName)
{
	ref sld = characterFromId("PedroHurtado");
	sld.cityTape = "quest"; //тип нпс
	DeleteAttribute(sld, "location.going");
	LAi_SetLoginTime(sld, 10.0, 19.00);
	LAi_SetStayTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto04_6");
	AddLandQuestMark_Main(sld, "ISS_takeStoreMoney");
}

void LSC_PedroRunOpenDoor()
{
	ref sld = characterFromId("PedroHurtado");
	sld.BreakTmplAndFight = true;
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorRunToLocator(sld, "reload", "reload48", "LSC_PedroOpenedDoor", -1.0);
}

void LSC_Click(string qName)
{	
	PlaySound("Key");
	LocatorReloadEnterDisable("LostShipsCity_town", "reload48", false);
	chrDisableReloadToLocation = true;
}

void LSC_PedroGoWaiting()
{
	ref sld = characterFromId("PedroHurtado");
	LAi_RemoveLoginTime(sld);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorTurnToLocator(sld, "goto", "goto04_6");
	chrDisableReloadToLocation = false;
	pchar.quest.LSC_EnterStoreBig.win_condition.l1 = "locator";
	pchar.quest.LSC_EnterStoreBig.win_condition.l1.location = "EsmeraldaStoreBig";
	pchar.quest.LSC_EnterStoreBig.win_condition.l1.locator_group = "reload";
	pchar.quest.LSC_EnterStoreBig.win_condition.l1.locator = "reload2";
	pchar.quest.LSC_EnterStoreBig.function = "LSC_EnterStoreBig";
}

void LSC_EnterStoreBig(string qName)
{	
	//охрана
	chrDisableReloadToLocation = true;
	Group_FindOrCreateGroup("LSC_RIVADOS");
	ref sld;
	string sModel;
	int iTemp = 8+MOD_SKILL_ENEMY_RATE*2;
    for (int i = 1; i <= 3; i++)
    {
        if (i == 3) sModel = "Eddy_Black";
        else sModel = "rivados_"+i;
        sld = GetCharacter(NPC_GenerateCharacter("LSCStBandit"+i, sModel, "man", "man", iTemp, PIRATE, 0, true)); //watch_coas_moment
        FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor2", "pistol6", 50);
        sld.watchBoxes = true;
        sld.dialog.Filename = "Quest\LostShipsCity\Guardian.c";
		ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "quest"+i);
		DeleteAttribute(sld, "lifeDay");
        if (i == 3)
        {
            LAi_SetActorType(sld);
            LAi_ActorDialog(sld, pchar, "", -1, 0);
            sld.dialog.currentnode = "Hello_Rivados";
			sld.name = FindPersonalName("Eddy_Black_name");
			sld.lastname = FindPersonalName("Eddy_Black_lastname");
        }
        else
        {
            LAi_SetWarriorType(sld);
            sld.dialog.currentnode = "First time";
        }
        LAi_group_MoveCharacter(sld, "LSC_RIVADOS");
    }
    LAi_group_SetRelation("LSC_RIVADOS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	pchar.quest.LCS_HeroOutFromStory.win_condition.l1 = "ExitFromLocation";
	pchar.quest.LCS_HeroOutFromStory.win_condition.l1.location = pchar.location;
	pchar.quest.LCS_HeroOutFromStory.function = "LCS_HeroOutFromStory";
}

void LCS_HeroOutFromStory(string qName)
{
	ref sld = CharacterFromId("PedroHurtado");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
	sld = &locations[FindLocation("EsmeraldaStoreBig")];
	DeleteAttribute(sld, "private3.items");
	DeleteAttribute(sld, "private3.money");
	AddLandQuestMark_Main(sld, "ISS_takeStoreMoney");

    sld = CharacterFromId("LSCStBandit3");
    LAi_SetHuberTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "sit", "sit1");
	AddSimpleRumourCityTip(StringFromKey("Common_rumours_82"), "LostShipsCity", 10, 1, "LSC", "");
}
//<<<<<<-------- посетить жилые помещения магазина ----------------

//------------ должок ростовщика ГПК ----------->>>>>>
void LSC_climeUsurer(string qName)
{
	pchar.quest.LSC_climeUsurer_2.win_condition.l1 = "Location_Type";
	pchar.quest.LSC_climeUsurer_2.win_condition.l1.location_type = "shop";
	pchar.quest.LSC_climeUsurer_2.function = "LSC_climeUsurer_2";	
}

void LSC_climeUsurer_2(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld = characterFromId(loadedLocation.fastreload + "_trader");
	LAi_CharacterDisableDialog(sld);
	//запишем данные для возврата в локацию
	pchar.questTemp.LSC_climeUsurer.idx = sld.id;
	pchar.questTemp.LSC_climeUsurer.location = pchar.location;
	pchar.questTemp.LSC_climeUsurer.group = pchar.location.group;
	pchar.questTemp.LSC_climeUsurer.locator = pchar.location.locator;
	DoQuestFunctionDelay("LSC_climeUsurer_3", 3.5);
}

void LSC_climeUsurer_3(string qName)
{
 	//перемещаем ГГ
	DoQuestReloadToLocation("Temple_Skulls", "goto", "goto1", "");	
	DoQuestFunctionDelay("LSC_climeUsurer_4", 10.0);
	//вернём хозяину магазина возможность диалога
	ref sld = characterFromId(pchar.questTemp.LSC_climeUsurer.idx);
	LAi_CharacterEnableDialog(sld);
}

void LSC_climeUsurer_4(string qName)
{
	//ставим бога мертвых	
	LAi_LockFightMode(Pchar, false);
	LAi_LocationFightDisable(loadedLocation, true);
	ref sld = GetCharacter(NPC_GenerateCharacter("DeadmansGod", "mictlantecuhtli", "skeleton", "man", 100, PIRATE, 0, true));//watch_coas_moment
	FantomMakeCoolFighter(sld, 50, 100, 100, "maquahuitl", "pistol4", 3000); //дадим четырехствольник
	sld.name = FindPersonalName("DeadmansGod_name");
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Mictlantecuhtli.c";
	sld.dialog.currentnode   = "ClimeUsurer";
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Temple_Skulls", "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);	
}

void ClimeUsurer_haveMoney()
{
	DoQuestFunctionDelay("ClimeUsurer_haveMoney_1", 1.0);	
}

void ClimeUsurer_haveMoney_1(string qName)
{
	chrDisableReloadToLocation = false;
	LAi_LocationFightDisable(&locations[FindLocation("Temple_Skulls")], false);
	DoQuestReloadToLocation(pchar.questTemp.LSC_climeUsurer.location, pchar.questTemp.LSC_climeUsurer.group, pchar.questTemp.LSC_climeUsurer.locator, "");	
	DeleteAttribute(pchar, "questTemp.LSC_climeUsurer");
}

void ClimeUsurer_noMoney()
{
	LAi_LocationFightDisable(loadedLocation, false);
	ref sld = characterFromId("DeadmansGod");
	ChangeCharacterAddress(sld, "none", "");
	//если Аззи в дружбанах, то выручает ГГ
	if (pchar.questTemp.Azzy == "over")
	{
		DoQuestFunctionDelay("LSC_climeUsurer_Azzy", 30.0);
	}
}

void LSC_climeUsurer_Azzy(string qName)
{
	LAi_LockFightMode(Pchar, false);
	LAi_LocationFightDisable(loadedLocation, true);
	ref sld = GetCharacter(NPC_GenerateCharacter("Azzy", "Azzy", "man", "man", 22, PIRATE, 0, false));
	sld.name = FindPersonalName("Azzy_name");
	sld.lastname = FindPersonalName("Azzy_lastname");
	sld.Dialog.Filename = "Quest\Azzy_dialog.c";
	sld.dialog.currentnode = "ClimeUsurer";
	GiveItem2Character(sld, "blade28");// сабля Моргана
	sld.equip.blade = "blade28";
	sld.rank 	= 100;
	sld.reputation = "0";
	SetSelfSkill(sld, 100, 100, 100, 100, 100);
	SetShipSkill(sld, 100, 100, 100, 100, 100, 100, 100, 100, 100);
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	LAi_SetLoginTime(sld, 0.0, 24.0);
	LAi_SetHP(sld, 10000.0, 10000.0);
	sld.greeting = "Gr_Azzy";
	ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
}
//<<<<<<-------- должок ростовщика ГПК ----------------

//------------ освободить мужа Элис Тейлор ----------->>>>>>
void LSC_ElisHusbandSet(string qName)
{
	ref sld = characterFromId("MaximTailor");
	sld.dialog.currentnode = "First time";
	sld.watchBoxes = true;
	sld.location.baseShip = "03"; //базовый корабль в ГПК
	sld.location.baseLocator = "goto03_1";
	sld.location.baseLocation = "CeresSmithy"; //базовая внутреняя локация
	sld.location.baseShip.going = false; //перемещаться между кораблями в городе
	sld.location.hours = 4; //передвижения через .. часов
	sld.cityTape = "quest"; //тип нпс
	GiveItem2Character(sld, "blade15");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterbyItem(sld, "blade15");
 	EquipCharacterbyItem(sld, "pistol2");
	LAi_SetSitType(sld);
	sld.standUp = true; //вставать и нападать на врага
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	ChangeCharacterAddressGroup(sld, "CeresSmithy", "sit", "sit2");
}
//<<<<<<-------- освободить мужа Элис Тейлор ----------------

//------------ квест скелета Лейтона Декстера ----------->>>>>>
void LSC_admiralFoundOwnKey(string qName)
{
	ref sld = ItemsFromID("admiralKey");
	sld.shown = false;
	QuestPointerDelLoc(sld.startLocation, "item", sld.startLocator);
	AddQuestRecord("LSC_findDekster", "11");
	AddQuestUserData("LSC_findDekster", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("LSC_findDekster");
	if (CheckCharacterItem(pchar, "shark_tooth"))
	    RemoveItems(pchar, "shark_tooth", 1);
	sld = CharacterFromId("LSCMayor"); //если Адмирал нашел, то ключ будет у него
	GiveItem2Character(sld, "admiralKey");
	pchar.questTemp.LSC.lostDecster = "over";
	LSC_CheckReadyMainLine(); //проверка все ли готово для продолжения основной линейки

	RemoveLandQuestMark_Main(CharacterFromId("LSCMayor"), "LSC_findDekster");
    RemoveLandQuestMark_Main(CharacterFromId("Ment_6"), "LSC_findDekster");
    RemoveLandQuestMark_Main(CharacterFromID("LSC_PrisonerHead"), "LSC_findDekster");
    RemoveLandQuestMark_Main(CharacterFromID("LSC_Prisoner1"), "LSC_findDekster");
}
//<<<<<<-------- квест скелета Лейтона Декстера ----------------

// --> тайна Санта-Люсии
void LSC_RingOver(string qName) // чистка квеста
{
	ref sld = characterFromId("MalcolmFawn");
	LAi_RemoveLoginTime(sld);
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "sit", "random_free");
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "LSC_CITIZEN");
	if (!CheckAttribute(sld, "quest.ring_final"))
	{
		AddQuestRecord("LSC_Ring", "2");
		AddQuestUserData("LSC_Ring", "sSex", GetSexPhrase("","а"));
	}
	CloseQuestHeader("LSC_Ring");
	RemoveLandQuestMark_Main(sld, "LSC_Ring");
}

void LSC_RingStart(string qName) // готовы
{
	ref sld = characterFromId("MalcolmFawn");
	sld.dialog.currentnode = "ring_9";
	LAi_RemoveLoginTime(sld);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "ring");
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, "TMP_FRIEND");
	AddLandQuestMark_Main(sld, "LSC_Ring");
}

void LSC_RingEnter(string qName) // входим
{
	pchar.quest.LSC_Ring_Over.over = "yes"; //снять прерывание
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_14") + NewStr() + StringFromKey("InfoMessages_15"), "", 0, 6);//табличка
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 1, 10); //крутим время
	RecalculateJumpTable();
	DoQuestFunctionDelay("LSC_RingReload", 5.5);
}

void LSC_RingReload(string qName) // телепорт
{
	DoQuestReloadToLocation("ExternalRingInside", "reload", "reload1", "LSC_RingEnterInside");
}

void LSC_RingMalcolmTalk(string node) // говорилка Малькольма
{
	ref sld = characterFromId("MalcolmFawn");
	sld.dialog.currentnode = node;
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LSC_RingDeleteItemsBoxes(string qName)
{
	ref loc;
	aref arBox;
	string sName;
	for(int i=0; i<MAX_LOCATIONS; i++)
	{
		loc = &locations[i];
		if (loc.id == "ExternalRingDeck" || loc.id == "ExternalRingInside" || loc.id == "ExternalRingCabin1")
		{
			for(int n=1; n<=MAX_HANDLED_BOXES; n++)
			{
				sName = "private" + n;
				if (CheckAttribute(loc, sName))
				{
					makearef(arBox, loc.(sName));
					DeleteAttribute(arBox, "items");
					arBox.items = "";
				}
				else break;
			}
		}
	}
	pchar.GenQuestBox.ExternalRingInside = true;
	pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 1;
}
// <-- тайна Санта-Люсии

// --> пей до дна
void LSC_DrinkOver(string qName) // просрочил
{
	ref sld = characterFromId("PedroHurtado");
	sld.dialog.currentnode = "First time";
	sld.location = "LostShipsCity_town";
    sld.location.group = "goto";
    sld.location.locator = "goto06_1";
	AddQuestRecord("LSC_Drink", "7");
	AddQuestUserData("LSC_Drink", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("LSC_Drink");
	DeleteAttribute(pchar, "questTemp.LSC.Drink");
	RemoveLandQuestMark_Main(CharacterFromID("MalcolmFawn"), "LSC_Drink");
}

void LSC_DrinkDelete(string qName) // подчистка квеста
{
	Log_Testinfo("Зачищаем квест 'пей до дна'");
	ref sld = CharacterFromId("MalcolmFawn");
	sld.cityTape = "citizen";
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "sit", "sit19");
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	sld = CharacterFromId("PedroHurtado");
	sld.cityTape = "citizen";
	sld.dialog.currentnode = "First time";
	ChangeCharacterAddress(sld, "LostShipsCity_town", "goto06_1");
    LAi_SetStayTypeNoGroup(sld);
    LAi_SetLoginTime(sld, 6.0, 21.99);
    LAi_SetLSCoutType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
	DeleteAttribute(pchar, "questTemp.LSC.Drink");
	if (CheckAttribute(pchar, "GenQuest.CamShuttle")) DeleteAttribute(pchar, "GenQuest.CamShuttle");
	CloseQuestHeader("LSC_Drink");
}

void LSC_WaitDrinkPrepare(string qName)
{
	if (pchar.location == "FleuronTavern")
	{
        DoQuestFunctionDelay("LSC_DrinkPrepare", 0.5);
	}
	else
	{
	    pchar.quest.WaitDrinkPrepare.win_condition.l1 = "location";
        pchar.quest.WaitDrinkPrepare.win_condition.l1.location = "FleuronTavern";
        pchar.quest.WaitDrinkPrepare.function = "LSC_DrinkPrepare";
	}
}

void LSC_DrinkPrepare(string qName) // подготовка
{
	ref sld = characterFromId("MalcolmFawn");
	sld.cityTape = "quest";
	sld.dialog.currentnode = "drink_8";
	LAi_SetActorType(sld);
	LAi_ActorSetSitMode(sld);
	ChangeCharacterAddressGroup(sld, "FleuronTavern", "quest", "sit2");
	LAi_Actor2WaitDialog(sld, pchar);
	AddLandQuestMark_Main(sld, "LSC_Drink");

	sld = characterFromId("PedroHurtado");
	sld.cityTape = "quest";
    LAi_RemoveLoginTime(sld);
	ChangeCharacterAddress(sld, "FleuronTavern", "goto2");
	LAi_SetStayTypeNoGroup(sld);

	sld = ItemsFromID("potionrum");
	sld.shown = true;
	sld.startLocation = "FleuronTavern";
	sld.startLocator = "item1";
}

void LSC_DrinkGo(string qName) // бухалово
{
	KZ|Random("&Colony\Inside\Tavern\Spain,Colony\Inside\Tavern");
    InterfaceStates.Buttons.Save.enable = false;
	bDisableCharacterMenu = true; //лоченые интерфейсы
	locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1700);
	DoQuestFunctionDelay("LSC_DrinkResult", 32.5);

	// Если случайное число (0-99) строго меньше нашего процента - это успех
	if (rand(99) < sti(pchar.questTemp.LSC.Drink.Chance))
		pchar.questTemp.LSC.Drink.Result = 1;
	else
		pchar.questTemp.LSC.Drink.Result = 2;
}

void LSC_DrinkResult(string qName) // итоги
{
	locCameraResetState();
	InterfaceStates.Buttons.Save.enable = true;
	bDisableCharacterMenu = false;//лоченые интерфейсы
	ref chr = characterFromId("PedroHurtado");
	LAi_SetActorType(chr);
	LAi_Fade("", "");
	WaitDate("",0,0,0,3,5);
	if (sti(pchar.questTemp.LSC.Drink.Result) == 1)
	{
        // обыграл и нажрался
        ref sld = characterFromId("MalcolmFawn");
        LAi_SetActorType(sld);
        LAi_ActorSetSitMode(sld);
        LAi_ActorAnimation(sld, "Sit_Death", "OpenTheDoors", 2.7);
        chr.dialog.currentnode = "result_1";
        LAi_SetAlcoholState(3);
	}
	else
	{
        //ужрался
        LAi_SetActorType(pchar);
        LAi_ActorSetSitMode(pchar);
        LAi_ActorAnimation(pchar, "Sit_Death", "OpenTheDoors", 2.7);
        chr.dialog.currentnode = "result_2";
        LAi_SetAlcoholState(4);
	}
	DoQuestFunctionDelay("LSC_DrinkResult_1", 2.7);
	pchar.questTemp.LSC.Drink = "result";

}

void LSC_DrinkResult_1(string qName) // итоги-1
{
	LAi_SetPlayerType(pchar);
	ref chr = characterFromId("LSCBarmen");
	ref sld = characterFromId("MalcolmFawn");
	if (sti(pchar.questTemp.LSC.Drink.Result) == 1)
	{
		sld.dialog.currentnode = "drunk";
		chr.quest.drink = "win";
		sld.quest.drink = "win";
	}
	else
	{
		sld.dialog.currentnode = "First time";
		LAI_TYPE_LSCout_Goto(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
		chr.quest.drink = "fail";
		sld.quest.drink = "fail";
	}
	sld = ItemsFromID("potionrum");
	sld.shown = false;
	DoQuestReloadToLocation("FleuronTavern", "goto", "goto1", "LSC_DrinkPedroTalk");
}
// <-- пей до дна

//проверка что там по живым касерам. max 10
int LSC_CheckDeceasedCaspers()
{
    int i, index;
    int deceasedCaspers = 0;
    for (i = 1; i < 5; i++)
    {
        index = GetCharacterIndex("CasperProt_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index])) deceasedCaspers++;
    }
    for (i = 1; i < 5; i++)
    {
        index = GetCharacterIndex("CasperMush_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index])) deceasedCaspers++;
    }
    for (i = 1; i < 3; i++)
    {
        index = GetCharacterIndex("CasperSold_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index])) deceasedCaspers++;
    }
    return deceasedCaspers;
}

// --> помощь ментов в нарезке касперов
void LSC_MentosAttackOnCasper(string qName)
{
    pchar.questTemp.LSC.MentosHelp.Ready = true;
    AddLandQuestMark_Main(CharacterFromID("Ment_6"), "ISS_DefeatCasperClan");
}

void LSC_MentosAttackOnCasperMovie_1(string qName) //мушкетеры ждут
{
    LAi_Fade("", "");
    ref sld, target;
    int iTemp;
    string sTemp;
    target = CharacterFromId("CasperMush_3");
    if (!LAi_IsDead(target))
    {
        sld = CharacterFromId("MentMush_7");
        LAi_ActorTurnToCharacter(sld, target);
    }
    target = CharacterFromId("CasperMush_4");
    if (!LAi_IsDead(target))
    {
        sld = CharacterFromId("MentMush_8");
        LAi_ActorTurnToCharacter(sld, target);
    }
    for (int i = 1 ; i <= 3; i++)
    {
        iTemp = GetCharacterIndex("Ment_" + i);
        if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
        {
            sld = &characters[iTemp];
            iTemp = i+1;
            sTemp = "goto12_" + iTemp;
            LAi_type_actor_Reset(sld);
            LAi_ActorgoToLocator(sld, "goto", sTemp, "", -1);
        }
    }
    sld = CharacterFromId("Ment_6");
    LAi_type_actor_Reset(sld);
    LAi_ActorRunToLocator(sld, "goto", "goto12_0", "", -1);

    locCameraFromToPos(47.45, 9.27, 100.07, false, -100.28, -25.99, 0.00);
    DoQuestFunctionDelay("LSC_MentosAttackOnCasperMovie_2", 4.0);
}

void LSC_MentosAttackOnCasperMovie_2(string qName) //стрельба 1
{
    ref sld = CharacterFromId("CasperMush_3");
    if (!LAi_IsDead(sld))
    {
        sld = CharacterFromId("MentMush_7");
        CharacterPlayAction(sld, "Shot");
    }
    DoQuestFunctionDelay("LSC_MentosAttackOnCasperMovie_3", 0.5);
}


void LSC_MentosAttackOnCasperMovie_3(string qName) //стрельба 2
{
    ref sld = CharacterFromId("CasperMush_4");
    if (!LAi_IsDead(sld))
    {
        sld = CharacterFromId("MentMush_8");
        CharacterPlayAction(sld, "Shot");
    }
    DoQuestFunctionDelay("LSC_MentosAttackOnCasperMovie_4", 0.5);
}

void LSC_MentosAttackOnCasperMovie_4(string qName) //результат стрельбы 1
{
    ref sld = CharacterFromId("CasperMush_3");
    if (!LAi_IsDead(sld))
    {
        LAi_KillCharacter(sld);
        CreateLocationParticles("blood", "soldiers", "mushketer3", 1.3, 0, 0, "");
        sld = CharacterFromId("MentMush_7");
        CharacterPlayAction(sld, "");
    }
    DoQuestFunctionDelay("LSC_MentosAttackOnCasperMovie_5", 0.5);
}

void LSC_MentosAttackOnCasperMovie_5(string qName) //результат стрельбы 2
{
    ref sld = CharacterFromId("CasperMush_4");
    if (!LAi_IsDead(sld))
    {
        LAi_KillCharacter(sld);
        CreateLocationParticles("blood_big", "soldiers", "mushketer4", 1.3, 0, 0, "");
        sld = CharacterFromId("MentMush_8");
        CharacterPlayAction(sld, "");
    }
    DoQuestFunctionDelay("LSC_MentosAttackOnCasperMovie_6", 1.0);
}

void LSC_MentosAttackOnCasperMovie_6(string qName) //начинается рубилово
{
    int i, index;
    chrDisableReloadToLocation = true;
    LAi_Fade("", "");
    Lai_SetPlayerType(pchar);
    DoQuestCheckDelay("MainHeroFightModeOn", 0.1);
    //враги
    for (i = 1; i < 5; i++)
    {
        index = GetCharacterIndex("CasperProt_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index])) LAi_group_MoveCharacter(&characters[index], LAI_GROUP_BRDENEMY);
    }
    for (i = 1; i < 3; i++)
    {
        index = GetCharacterIndex("CasperMush_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index])) LAi_group_MoveCharacter(&characters[index], LAI_GROUP_BRDENEMY);
    }
    for (i = 1; i < 3; i++)
    {
        index = GetCharacterIndex("CasperSold_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index])) LAi_group_MoveCharacter(&characters[index], LAI_GROUP_BRDENEMY);
    }
    //наша команда
    for (i = 1 ; i <= 3; i++)
    {
        index = GetCharacterIndex("Ment_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index])) LAi_SetWarriorTypeNoGroup(&characters[index]);
    }
    ref sld = CharacterFromId("MentMush_7");
    LAi_SetWarriorTypeNoGroup(sld);
    sld = CharacterFromId("MentMush_8");
    LAi_SetWarriorTypeNoGroup(sld);
    sld = CharacterFromId("Ment_6");
    LAi_SetWarriorTypeNoGroup(sld);

	if (LSC_CheckDeceasedCaspers() == 0)
	{
		DoQuestFunctionDelay("LSC_MentosAttackOnCasper_AdditionalHelp", 0.1);
		DoQuestCheckDelay("LSC_ClearCasperDeck", 5.0);
	}
	else
	{
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "LSC_ClearCasperDeckWaitRolyPoly");
	}

    LAi_QuestFader.oldSaveState = true;
	EndQuestMovie();
    locCameraTarget(pchar);
    locCameraFollow();
}

void LSC_MentosAttackOnCasper_AdditionalHelp(string qName)
{
    if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad.ClearCasperDeck")) return;
    int index;
    ref sld;
    aref aSuicideSquad;
    int count = 0;
    makearef(aSuicideSquad, pchar.questTemp.LSC.suicideSquad);
    for (int i = 0; i < GetAttributesNum(aSuicideSquad); i++)
    {
        index = sti(GetAttributeName(GetAttributeN(aSuicideSquad, i)));
        sld = &characters[index];
        if (sld.id != "Ment_6")
        {
            LAi_SetRolyPoly(sld, true);
            LAi_RemoveLoginTime(sld);
            if (count == 0) ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto03_1");
            else if (count == 1) ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto03_6");
            else if (count == 2) ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto03_4");
            LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
            LAi_SetWarriorTypeNoGroup(sld);
            count++;
        }
    }
}
// <-- помощь ментов в нарезке касперов

// --> путь чернокнижника
void LSC_WarlocksWay(string qName)
{
    int index, i;
    for (i = 1; i <= 4; i++)
    {
        index = GetCharacterIndex("CasperProt_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index])) LAi_KillCharacter(&characters[index]);
    }
    for (i = 1; i <= 4; i++)
    {
        index = GetCharacterIndex("CasperMush_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index])) LAi_KillCharacter(&characters[index]);
    }
    for (i = 1; i <= 2; i++)
    {
        index = GetCharacterIndex("CasperSold_" + i);
        if (index != -1 && !LAi_IsDead(&characters[index])) LAi_KillCharacter(&characters[index]);
    }
    DoQuestReloadToLocation("LostShipsCity_town",  "goto", "goto12_3", "LSC_WarlocksWayTalkAboutUs");
}
// <-- путь чернокнижника

// --> месть Ривадос в 9 актах
void LSC_RivadosRevengeOver(string qName)
{
	ref sld = CharacterFromId("LSCStBandit3");
	sld.dialog.currentnode = "RivadosPlanOver";
	DeleteAttribute(pchar, "questTemp.LSC.RivadosHelp");
    AddQuestRecord("ISS_DefeatCasperClan", "16");
    AddQuestUserData("ISS_DefeatCasperClan", "sSex", GetSexPhrase("ёл","ла"));
    RemoveLandQuestMark_Main(sld, "ISS_DefeatCasperClan");
}

void LSC_RivadosRevengeStart(string qName)
{
	ref sld = CharacterFromId("LSCStBandit3");
	sld.dialog.currentnode = "RivadosPlanStart";
	AddLandQuestMark_Main(sld, "ISS_DefeatCasperClan");
}

void LSC_RivadosRevengeAmbushOver(string qName)
{
	ref sld = CharacterFromId("LSCStBandit3");
	sld.dialog.currentnode = "RivadosPlanOver";
	sld.model = "Eddy_Black";
    sld.model.animation = "man";
    SetNewModelToChar(sld);
	FantomMakeCoolFighter(sld, sti(sld.rank), 80, 80, "topor2", "pistol6", 50);
    LAi_SetHuberTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "sit", "sit1");
    DeleteAttribute(pchar, "questTemp.LSC.RivadosHelp");
    if (qName != "ok")
    {
        AddQuestRecord("ISS_DefeatCasperClan", "16");
        AddQuestUserData("ISS_DefeatCasperClan", "sSex", GetSexPhrase("ёл","ла"));
        RemoveLandQuestMark_Main(sld, "ISS_DefeatCasperClan");
    }
}

void LSC_RivadosRevengeAmbushStart(string qName)
{
	ref sld = CharacterFromId("LSCStBandit3");
	sld.dialog.currentnode = "RivadosRevengeAmbushStart";
	sld.model = "Eddy_Black_mush";
    sld.model.animation = "mushketer";
    SetNewModelToChar(sld);
	FantomMakeCoolFighter(sld, sti(sld.rank), 80, 80, "unarmed", "mortar", 50);
	LAi_SetStayTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto03_6");
	AddLandQuestMark_Main(sld, "ISS_DefeatCasperClan");
}

//месть Ривадос в 9 актах
void LSC_RivadosRevengeAct_1(string qName) //идут по кораблю
{
    int index;
    ref sld = CharacterFromId("LSCStBandit3");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorGoToLocator(sld, "goto", "goto03_8", "", -1);
    StartQuestMovie(false, false, true);
    locCameraFromToPos(61.32, 10.79, 106.22, false, -60.65, -60.4, 0.00);
    for (int i = 1; i < 3; i++)
    {
        index = NPC_GeneratePhantomCharacter("rivados_mush", PIRATE, MAN, 0);
        sld = &characters[index];
        SetNPCModelUniq(sld, "rivados_mush", MAN);
        sld.MusketerDistance = 0;
        sld.model.animation = "mushketer";
        FantomMakeCoolFighter(sld, 10, 100, 100, "unarmed", "mushket", 200);
        if (i == 1)
        {
            ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto03_9");
            LAi_SetActorType(sld);
            LAi_ActorGoToLocation(sld, "goto", "goto03_7", "LostShipsCity_town", "quest", "ambush2", "", 4.0);
        }
        else
        {
            ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto03_5");
            LAi_SetActorType(sld);
            LAi_ActorGoToLocation(sld, "reload", "reload65", "LostShipsCity_town", "quest", "ambush1", "", 4.0);
        }
    }
    DoQuestFunctionDelay("LSC_RivadosRevengeAct_2", 4.0);
}

void LSC_RivadosRevengeAct_2(string qName) //залезли на мачты
{
    LAi_Fade("", "");
    ref sld = CharacterFromId("CasperMush_4");

    //если два мушкетера то месть получается маленькая
    if (CheckAttribute(pchar, "questTemp.LSC.SmallRivadosRevenge"))
    {
        locCameraFromToPos(24.93, 19.45, 63.48, false, 60.55, -80.10, 200.00);
        if (!LAi_IsDead(sld)) DoQuestFunctionDelay("LSC_RivadosRevengeShoot", 4.0);
        DoQuestFunctionDelay("LSC_RivadosRevengeAct_7", 5.0);
    }
    else
    {
        locCameraFromToPos(63.51, 30.76, 97.64, false, -200.55, -150.88, 0.00);
        if (!LAi_IsDead(sld)) DoQuestFunctionDelay("LSC_RivadosRevengeShoot", 10.0);
        DoQuestFunctionDelay("LSC_RivadosRevengeAct_3", 5.0);
    }
}

void LSC_RivadosRevengeAct_3(string qName) //приблизим месиво
{
	KZ|Random("&Action\Fight,Action");
    locCameraFromToPos(32.58, 11.72, 99.49, false, 0.27, -20.9, 0.00);

    //беги форест! беги!!
    ref sld = CharacterFromId("CasperProt_1");
    if (!LAi_IsDead(sld))
    {
        LAi_SetActorType(sld);
        LAi_ActorRunToLocation(sld, "reload", "reload55", "none", "", "", "", 10.0);
    }
    DoQuestFunctionDelay("LSC_RivadosRevengeAct_4", 2.0);
}

void LSC_RivadosRevengeAct_4(string qName) //первая бомба
{
	CreateLocationParticles("ShipExplode", "quest", "mushketer1", 0, 0, 0, "");
	CreateLocationParticles("shipfire", "quest", "mushketer1", 0.0, 0, 0, "fortfire");
	PlayVoice("Sea Battles\sdavl_kriki_002.wav");
	PlaySound("Sea Battles\vistrel_orudiya_004.wav");

    //убитые бомбой
    ref sld = CharacterFromId("CasperProt_2");
    if (!LAi_IsDead(sld)) LAi_KillCharacter(sld);
    sld = CharacterFromId("CasperMush_1");
    if (!LAi_IsDead(sld)) LAi_KillCharacter(sld);
    sld = CharacterFromId("CasperMush_2");
    if (!LAi_IsDead(sld)) LAi_KillCharacter(sld);

    //остальные начинают шевелиться
    sld = CharacterFromId("CasperProt_3");
    if (!LAi_IsDead(sld)) LAi_type_patrol_Init(sld);
    sld = CharacterFromId("CasperProt_4");
    if (!LAi_IsDead(sld)) LAi_type_patrol_Init(sld);
    sld = CharacterFromId("CasperSold_1");
    if (!LAi_IsDead(sld)) LAi_type_patrol_Init(sld);
    sld = CharacterFromId("CasperSold_2");
    if (!LAi_IsDead(sld)) LAi_type_patrol_Init(sld);

    DoQuestFunctionDelay("LSC_RivadosRevengeAct_5", 1.0);
}

void LSC_RivadosRevengeAct_5(string qName) //достают оружие чо такое
{
    PlaySound("Voice\" + VoiceGetLanguage() + "\EvilPirates01.wav");
    ref sld = CharacterFromId("CasperProt_3");
    if (!LAi_IsDead(sld)) LAi_tmpl_SetFight(sld, pchar);
    sld = CharacterFromId("CasperProt_4");
    if (!LAi_IsDead(sld)) LAi_tmpl_SetFight(sld, pchar);
    sld = CharacterFromId("CasperSold_1");
    if (!LAi_IsDead(sld)) LAi_tmpl_SetFight(sld, pchar);
    sld = CharacterFromId("CasperSold_2");
    if (!LAi_IsDead(sld)) LAi_tmpl_SetFight(sld, pchar);

    DoQuestFunctionDelay("LSC_RivadosRevengeAct_6", 1.0);
}

void LSC_RivadosRevengeAct_6(string qName) //вторая бомба
{
    locCameraFromToPos(24.93, 19.45, 63.48, false, 60.55, -80.10, 200.00);
	CreateLocationParticles("ShipExplode", "soldiers", "soldier2", 0, 0, 0, "");
	CreateLocationParticles("shipfire", "soldiers", "soldier2", 0.0, 0, 0, "fortfire");
	PlayVoice("Sea Battles\sdavl_kriki_002.wav");
	PlaySound("Sea Battles\vistrel_orudiya_004.wav");

    ref sld = CharacterFromId("CasperProt_3");
    if (!LAi_IsDead(sld)) LAi_KillCharacter(sld);
    sld = CharacterFromId("CasperProt_4");
    if (!LAi_IsDead(sld)) LAi_KillCharacter(sld);
    sld = CharacterFromId("CasperSold_1");
    if (!LAi_IsDead(sld)) LAi_KillCharacter(sld);
    sld = CharacterFromId("CasperSold_2");
    if (!LAi_IsDead(sld)) LAi_KillCharacter(sld);
    sld = CharacterFromId("CasperProt_1");
    if (!LAi_IsDead(sld)) LAi_KillCharacter(sld);

    DoQuestFunctionDelay("LSC_RivadosRevengeAct_7", 2.0);
}

void LSC_RivadosRevengeAct_7(string qName) //работа снайперов
{
    ref sld = CharacterFromId("CasperMush_4");
    if (!LAi_IsDead(sld))
    {
        PlayVoice("PEOPLE FIGHT\Death_NPC_01.wav");
        CreateLocationParticles("blood_big", "soldiers", "mushketer4", 1.3, 0, 0, "");
        LAi_KillCharacter(sld);
    }
    sld = CharacterFromId("CasperMush_3");
    if (!LAi_IsDead(sld)) DoQuestFunctionDelay("LSC_RivadosRevengeShoot", 0.1);

    DoQuestFunctionDelay("LSC_RivadosRevengeAct_8", 1.0);
}

void LSC_RivadosRevengeAct_8(string qName) //последнего пристрелили
{
    ref sld;
    sld = CharacterFromId("CasperMush_3");
    if (!LAi_IsDead(sld))
    {
        PlayVoice("PEOPLE FIGHT\Death_NPC_02.wav");
        CreateLocationParticles("blood_big", "soldiers", "mushketer3", 1.3, 0, 0, "");
        LAi_KillCharacter(sld);
    }

    DoQuestFunctionDelay("LSC_RivadosRevengeAct_9", 6.0);
}

void LSC_RivadosRevengeAct_9(string qName) //разговор
{
    EndQuestMovie();
    locCameraTarget(pchar);
    locCameraFollow();
    StopMusic();
    ref sld = CharacterFromId("LSCStBandit3");
    sld.revengeDone = true;
	sld.dialog.currentnode = "RivadosRevengeAmbushEnd";
    LAi_SetActorType(sld);
    LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void LSC_RivadosRevengeShoot(string qName) //звук выстрела
{
    PlaySound("PEOPLE FIGHT\MushketShot.wav");
}
// <-- месть Ривадос
void AfterStormCaspers_ExitFromLocation(string qName)
{
    aref aSquad;
    int index;
    ref sld;
    makearef(aSquad, pchar.questTemp.LSC.suicideSquad);
    for (int i = 0; i < GetAttributesNum(aSquad); i++)
    {
        index = sti(GetAttributeName(GetAttributeN(aSquad, i)));
        sld = &characters[index];
        LAi_SetWarriorType(sld);
        LAi_CharacterEnableDialog(sld);
        switch (sld.id)
        {
            case "LSC_Prisoner1":
                ChangeCharacterAddress(sld, "TartarusPrison",  "goto1");
            break;
            case "Ment_6":
                ChangeCharacterAddress(sld, "SanAugustineResidence",  "goto1");
            break;
            case "MalcolmFawn":
                ChangeCharacterAddress(sld, "LostShipsCity_town",  "goto02_3");
                LAi_SetLSCoutType(sld);
            break;
            case "MaximTailor":
                ChangeCharacterAddress(sld, "CeresSmithy",  "goto03_1");
            break;
        }
        LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
    }
    DeleteAttribute(pchar, "questTemp.LSC.suicideSquad");
}
// --> табак Малькольма
void MalcolmIntoPuertoPrincipe(string qName)
{
	pchar.GenQuest.Hunter2Pause = true;
	ref sld = CharacterFromId("MalcolmFawn");
	LAi_CharacterEnableDialog(sld);
	RemovePassenger(pchar, sld);
	chrDisableReloadToLocation = true;
	sld.dialog.currentnode = "Tobacco";
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void MalcolmGoToPchar(string qName)
{
	pchar.GenQuest.Hunter2Pause = true;
	ref sld = characterFromId("MalcolmFawn");
	chrDisableReloadToLocation = true;
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void MalcolmBackToPchar(string qName)
{
	ref sld = characterFromId("MalcolmFawn");
	ref rChr;
	string sTemp = "Smuggler_";
	int iTemp = sti(sld.quest.MalcolmsTobacco.SmugglerNum);
	for (int i = 0; i < iTemp; i++)
	{
		rChr = CharacterFromID(sTemp + i);
		rChr.lifeDay = 0;
	}
	LAi_LocationFightDisable(&locations[FindLocation("Shore11")], false);
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "OpenTheDoors", -1, 0);
}

void GenerateTobaccoSmugglersInShore(string qName)
{
	string encGroup, str, locator;
	int num, i, k, iNation, iRank, n;
	ref pLoc, sld;
	aref grp;

	chrDisableReloadToLocation = true;
	pLoc = &locations[FindLocation("Shore11")];
	encGroup = "smugglers";
	str = "locators." + encGroup;
	makearef(grp, pLoc.(str));
	num = GetAttributesNum(grp); //кол-во человек в банде
	if (num <= 0) num = 1;

	str = "Smuggler_";
	string sGroup = "SmugglerMalcom_Group"; //имя группы
	LAi_LocationFightDisable(pLoc, true);
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);

	arrayNPCModelHow = 0;

	for (i = 0; i < num; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter(str + i, "Pirate_16", "man", "man", 5, PIRATE, 3, true));
        FantomMakeCoolFighter(sld, 30, 70, 70, "blade34", "pistol6", 100);
		SetModelPirate(sld);
		k = 0;
		while (!CheckNPCModelUniq(sld) && k < 10)
		{
		    k++;
			SetModelPirate(sld);
		}
		arrayNPCModel[arrayNPCModelHow] = sld.model;
		arrayNPCModelHow++;

		LAi_SetStayType(sld);
		LAi_group_MoveCharacter(sld, sGroup);
		pchar.GenQuest.CaptainComission.GangNum = num;
		sld.greeting = "Gr_Smuggler_OnShore";
		locator = GetAttributeName(GetAttributeN(grp, i));
		ChangeCharacterAddressGroup(sld, pLoc.id, encGroup, locator);
		LAi_CharacterDisableDialog(sld);
		if (i == 0)
		{
			sld.dialog.filename = "Quest\LostShipsCity\MalcolmFawn.c";
			sld.Dialog.CurrentNode = "Tobacco_5";
		}
		else
			LAi_CharacterDisableDialog(sld);
	}
	sld = CharacterFromID("MalcolmFawn");
	sld.quest.MalcolmsTobacco.SmugglerNum = num;
	RemovePassenger(pchar, sld);
	PlaceCharacter(sld, "goto", pchar.location);

    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void MalcolmDialogInShore()
{
	bDisableCharacterMenu = true;
	InterfaceStates.Buttons.Save.enable = false;
	StartQuestMovie(true, true, true);
	LAi_SetActorType(pchar);

	SetMainCharacterIndex(GetCharacterIndex("MalcolmFawn"));
	pchar = GetMainCharacter();
	locCameraTarget(pchar);
	locCameraFollow();
	LAi_SetActorType(pchar);
	ref sld = CharacterFromID("Smuggler_0");
	LAi_SetActorType(sld);
	LAi_CharacterEnableDialog(sld);
	SetActorDialogAny2Pchar("Smuggler_0", "", -1.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
}

void MalcolmBattleInShore(string qName)
{
	ref sld;
	string sTemp = "Smuggler_";
	string sGroup = "SmugglerMalcom_0";
	LAi_LocationFightDisable(&locations[FindLocation("Shore11")], false);
	chrDisableReloadToLocation = true;
	sld = CharacterFromID("MalcolmFawn");
	int iTemp = sti(sld.quest.MalcolmsTobacco.SmugglerNum);
	LAi_group_MoveCharacter(sld, sGroup);
	for (int i = 0; i < iTemp; i++)
	{
		sld = CharacterFromID(sTemp + i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, sGroup);
	}
	LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck(sGroup, "OpenTheDoors");
	LAi_group_SetCheckFunction(sGroup, "MalcolmDeathClear");
	LAi_SetFightMode(pchar, true);
}

void MalcolmDeathClear(string qName)
{
	ref sld = CharacterFromID("MalcolmFawn");
	if (CheckAttribute(sld, "quest.lie")) AddQuestRecord("MalcolmsTobacco", "8");
	else AddQuestRecord("MalcolmsTobacco", "9");
	AddQuestUserData("MalcolmsTobacco", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("MalcolmsTobacco");

	DeleteAttribute(pchar, "quest.MalcolmsTobacco");
	DeleteAttribute(pchar, "quest.WaitMalcolm");
	DeleteAttribute(pchar, "GenQuest.Hunter2Pause");

	InterfaceStates.Buttons.Save.enable = true;
    chrDisableReloadToLocation = false;
    bDisableFastReload = false;
}

void CheckMalcolmStatus()
{
	//Малькольм Фаун
	ref sld = characterFromId("MalcolmFawn");
	if (CheckAttribute(sld, "quest.crewDone"))
	{
		if (CheckAttribute(pchar, "quest.MalcolmsTobacco"))
		{
			sld.OfficerWantToGo.DontGo = true;
			sld.loyality = MAX_LOYALITY;
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			DeleteAttribute(sld, "city");
		}
		else
		{
			sld.lifeDay = 0;
		}
	}
	else
	{
        AddQuestRecord("MalcolmsTobacco", "3");
        AddQuestUserData("MalcolmsTobacco", "sSex", GetSexPhrase("","а"));
        CloseQuestHeader("MalcolmsTobacco");
        Ship_ApplyHullHitpoints(pchar, makefloat(sti(pchar.ship.hp)/5), KILL_BY_TOUCH, -1);
        Ship_ApplyCrewHitpoints(pchar, makefloat(GetMaxCrewQuantity(pchar)/3));
	}
}
// <-- табак Малькольма

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Линейка ГПК           конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Линейка Теночтитлана          начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//перец, что сваливает из Тено
void Teno_startInShore(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);
	ref sld = GetCharacter(NPC_GenerateCharacter("QuestMan_Shore", "shipowner_6", "man", "man", 100, SPAIN, 0, false));
	sld.name = FindPersonalName("QuestMan_Shore_name");
	sld.lastname = FindPersonalName("QuestMan_Shore_lastname");
	sld.dialog.filename   = "Quest\Tenochtitlan\ForAll_Teno.c";
	sld.dialog.currentnode   = "Shore53";
	ChangeCharacterAddressGroup(sld, "Shore53", "goto", "goto7");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);

	RemoveMapQuestMark("Shore53", "TenochtitlanQuest");
}

void Teno_startInShore_2()
{
	pchar.questTemp.Teno = "toMontesuma"; //флаг квеста
	ref sld = characterFromId("QuestMan_Shore");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "CanFightCurLocation", 10.0);
	//Ставим вождя
	sld = GetCharacter(NPC_GenerateCharacter("Montesuma", "Aztec", "man", "man", 50, PIRATE, -1, true));
	sld.undead = "1";
	FantomMakeCoolFighter(sld, 50, 100, 100, "maquahuitl", "", 500);
	sld.name = FindPersonalName("Montesuma_name");
	sld.lastname = "";
	sld.location = "Tenochtitlan";
	sld.location.group = "quest";
	sld.location.locator = "quest2";
	sld.dialog.filename   = "Quest\Tenochtitlan\Montesuma.c";
	sld.dialog.currentnode   = "First time";
	sld.greeting = "Gr_Montesuma";
	sld.reactionOnFightModeOn = true;
	sld.BreakTmplAndFight = true;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	LAi_SetWarriorType(sld);
	LAi_warrior_SetStay(sld, true);
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	//GiveItem2Character(sld, "Totem_15");
	LAi_group_MoveCharacter(sld, "MontesumaGroup");
	//ставим прерывание на вход в Теночтитлан
	pchar.quest.Teno_createAztecTwin.win_condition.l1 = "location";
	pchar.quest.Teno_createAztecTwin.win_condition.l1.location = "Tenochtitlan";
	pchar.quest.Teno_createAztecTwin.function = "Teno_createAztecTwin";

	pchar.quest.Teno_talkWithTwin.win_condition.l1 = "locator";
	pchar.quest.Teno_talkWithTwin.win_condition.l1.location = "Tenochtitlan";
	pchar.quest.Teno_talkWithTwin.win_condition.l1.locator_group = "teleport";
	pchar.quest.Teno_talkWithTwin.win_condition.l1.locator = "fire20";
	pchar.quest.Teno_talkWithTwin.function = "Teno_talkWithTwin";
	//открываем квест в СЖ
	SetQuestHeader("TenochtitlanQuest");
	AddQuestRecord("TenochtitlanQuest", "1");
	AddQuestUserData("TenochtitlanQuest", "sSex", GetSexPhrase("","а"));
}

//ставим ацтеков граждан
void Teno_createAztecTwin(string qName)
{
	//генерим близнецов
	ref sld = GetCharacter(NPC_GenerateCharacter("AztecCitizen_1", "AztecCitizen1", "man", "man", 15, PIRATE, -1, false));
	sld.indian = "1";
	sld.name = FindPersonalName("AztecCitizen_1_name");
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Tenochtitlan\AztecCitizens.c";
	sld.dialog.currentnode   = "AztecFT";
	sld.greeting = "cit_common";
	LAi_RemoveLoginTime(sld);
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "AztecCitizenGroup");  
	ChangeCharacterAddressGroup(sld, "Tenochtitlan", "goto", "goto23");
	
	sld = GetCharacter(NPC_GenerateCharacter("AztecCitizen_2", "AztecCitizen2", "man", "man", 15, PIRATE, -1, false));
	sld.indian = "1";
	sld.name = FindPersonalName("AztecCitizen_2_name");
	sld.lastname = "";
	sld.dialog.filename   = "Quest\Tenochtitlan\AztecCitizens.c";
	sld.dialog.currentnode   = "AztecFT2";
	sld.greeting = "cit_common";
	LAi_SetLoginTime(sld, 7.0, 20.0);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "AztecCitizenGroup");
	ChangeCharacterAddressGroup(sld, "Tenochtitlan", "goto", "goto14");
	//Монтесуму на ГГ
	sld = characterFromId("Montesuma");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 5.0, 0);
	AddLandQuestMark_Main_WithCondition(sld, "Tenochtitlan", "Teno_TakeFire_QuestMarkCondition");
}

void Teno_talkWithTwin(string qName)
{
	ref sld = characterFromId("AztecCitizen_1");
	LAi_ActorDialog(sld, pchar, "", 2.5, 0);
}

void Teno_MontesumaGoQuest1()
{
	AddQuestRecord("TenochtitlanQuest", "2");
	AddQuestUserData("TenochtitlanQuest", "sSex", GetSexPhrase("","а"));
	ref sld = characterFromId("Montesuma");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorRunToLocator(sld, "quest", "quest1", "Teno_MontesumaArrived", -1);
}

void Teno_SeekFireMagicTotems_SetQuestPointers()
{
	for (int i = Totems_start; i < Totems_end; i++)
	{
		string itemName = Items[i].id;
		if (StrHasStr(itemName, "Totem_11,Totem_13,Totem_14", 1))
		{
			ref itm = &Items[i];
			if (CheckAttribute(itm, "shown") && sti(itm.shown) == 1 &&
				CheckAttribute(itm, "startLocation") && CheckAttribute(itm, "startLocator"))
			{
				QuestPointerToLoc(itm.startLocation, "item", itm.startLocator);
			}
		}
	}
}

void Teno_SeekFireMagicTotems_DelQuestPointers()
{
	for (int i = Totems_start; i < Totems_end; i++)
	{
		string itemName = Items[i].id;
		if (StrHasStr(itemName, "Totem_11,Totem_13,Totem_14", 1))
		{
			ref itm = &Items[i];
			if (CheckAttribute(itm, "startLocation") && CheckAttribute(itm, "startLocator"))
			{
				QuestPointerDelLoc(itm.startLocation, "item", itm.startLocator);
			}
		}
	}
}

void Teno_SeekTempleTotems_SetQuestPointers()
{
	for (int i = Totems_start; i < Totems_end; i++)
	{
		string itemName = Items[i].id;
		if (!StrHasStr(itemName, "Totem_11,Totem_12,Totem_13,Totem_14,Totem_15", 1))
		{
			ref itm = &Items[i];
			if (CheckAttribute(itm, "shown") && sti(itm.shown) == 1 &&
				!CheckAttribute(itm, "shown.used") &&
				CheckAttribute(itm, "startLocation") && CheckAttribute(itm, "startLocator"))
			{
				QuestPointerToLoc(itm.startLocation, "item", itm.startLocator);
			}
		}
	}
}

void Teno_SeekTempleTotems_DelQuestPointers()
{
	for (int i = Totems_start; i < Totems_end; i++)
	{
		string itemName = Items[i].id;
		if (!StrHasStr(itemName, "Totem_11,Totem_12,Totem_13,Totem_14,Totem_15", 1))
		{
			ref itm = &Items[i];
			if (CheckAttribute(itm, "startLocation") && CheckAttribute(itm, "startLocator"))
			{
				QuestPointerDelLoc(itm.startLocation, "item", itm.startLocator);
			}
		}
	}
}

void Teno_fightInTemple()
{
	LAi_LocationFightDisable(loadedLocation, false);
	LAi_SetFightMode(pchar, true);
	ref sld = characterFromId("DeadmansGod");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "teno_monsters_group");
	LAi_group_SetRelation("teno_monsters_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("teno_monsters_group", LAI_GROUP_PLAYER, true);
	LAi_SetCheckMinHP(sld, 5.0, true, "Teno_youWinFight");
}

void Teno_exitFromTeno(string qName)
{
	ref sld = characterFromId("Montesuma");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0.0, 0);
}

void Teno_clearGroups(string qName)
{
	LAi_group_Delete("AztecCitizenGroup");
	LAi_group_Delete("MontesumaGroup");
	LAi_group_Delete("teno_monsters_group");
	ChangeItemDescribe("SkullAztec", "itmdescr_SkullAztecAdd");
	AddQuestRecord("TenochtitlanQuest", "6");
	CloseQuestHeader("TenochtitlanQuest");
	Achievment_Set(ACH_Povelitel_myortvykh);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Линейка Теночтитлана         конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Зачарованный город        начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void MC_QuestInit(string qName)
{
	// Если сработало прямо в городе, лучше рестартнуть
	if (pchar.location == "Caracas_town")
	{
		pchar.quest.MC_startAgain.win_condition.l1 = "MapEnter";
		pchar.quest.MC_startAgain.function = "MC_startAgain";
	}
	else
	{
		pchar.quest.MC_startInCaracas.win_condition.l1 = "location";
		pchar.quest.MC_startInCaracas.win_condition.l1.location = "Caracas_town";
		pchar.quest.MC_startInCaracas.function = "MC_startInCaracas";
	}

}

void MC_startInCaracas(string qName)
{
	if (sti(pchar.rank) >= 10 && GetHour() > 9.0 && GetHour() < 20.0 && !LAi_IsCapturedLocation)
	{
		ref sld;
		int i;
		pchar.questTemp.MC = "toCaracas"; //флаг квеста
		bDisableFastReload = true;
		int iTemp = FindLocation("Caracas_town");
		//убирается возможность генерации
		DeleteAttribute(&locations[iTemp], "citizens"); //уберем горожан
		DeleteAttribute(&locations[iTemp], "carrier");	//уберем грузчиков 
		DeleteAttribute(&locations[iTemp], "questSeekCap");	//уберем квестодателя
		//убираются уже сгенерированные
        for (i = 0; i<MAX_CHARACTERS; i++)
        {
            makeref(sld, characters[i]);
            if (CheckAttribute(sld, "CityType") && !CheckAttribute(sld, "Merchant") && sld.location == locations[iTemp].id && sld.CityType == "citizen")
            {
                sld.lifeday = 0;
                ChangeCharacterAddress(sld, "none", "");
            }
        }
		//закроем выходы из города
		locations[iTemp].reload.l1.disable = true;
		locations[iTemp].reload.l2.disable = true;
		locations[iTemp].reload.l3.disable = true;
		locations[iTemp].reload.l4.disable = true;
		locations[iTemp].reload.l41.disable = true;
		locations[iTemp].reload.l5.disable = true;
		locations[iTemp].reload.l6.disable = true;
		locations[iTemp].reload.l7.disable = true;
		locations[iTemp].reload.l8.disable = true;
		locations[iTemp].reload.l10.disable = true;
		locations[iTemp].reload.gate.disable = true;
		//очистим таверну
		iTemp = FindLocation("Caracas_tavern");
		//убирается возможность генерации
		DeleteAttribute(&locations[iTemp], "habitues"); //уберем в таверне наполнение нпс
		//убираются уже сгенерированные
        for (i = 0; i<MAX_CHARACTERS; i++)
        {
            makeref(sld, characters[i]);
            if (CheckAttribute(sld, "CityType") && !CheckAttribute(sld, "Merchant") && sld.location == locations[iTemp].id && sld.CityType == "citizen")
            {
                sld.lifeday = 0;
                ChangeCharacterAddress(sld, "none", "");
            }
        }
		locations[iTemp].reload.l1.disable = true;
		locations[iTemp].reload.l4.disable = true;
		sld = characterFromId("Caracas_waitress"); //официантку тоже
		ChangeCharacterAddress(sld, "none", "");
		sld = characterFromId("Caracas_Smuggler"); //контрабандиста еще забыли
		ChangeCharacterAddress(sld, "none", "");
		//ставим горожан
		arrayNPCModelHow = 0;
		for (i=1; i<=12; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("CaracasCit_"+i, RandCitizenModel(), "man", "man", 10, SPAIN, -1, true));
			if (HasSubStr(sld.model, "citiz") && sti(FindStringAfterChar(sld.model,"_")) < 21) SetNPCModelUniq(sld, "citizen", MAN);
			else SetNPCModelUniq(sld, "commoner", MAN);
			sld.dialog.filename = "Quest\MagicCity.c";
			sld.dialog.currentnode = "CaracasMan";
			sld.greeting = "cit_common";
			sld.BreakTmplAndFightGroup = true;
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(sld, pchar);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");	
			ChangeCharacterAddressGroup(sld, "Caracas_town", "quest", "MCquest"+i);
			AddLandQuestMark_Main(sld, "MagicCity");
		}
        AddLandQuestMark_Main(characterFromId("Caracas_tavernkeeper"), "MagicCity");
        RemoveMapQuestMark("Caracas_town", "MagicCity");
	}
	else
	{
		pchar.quest.MC_startAgain.win_condition.l1 = "MapEnter";
		pchar.quest.MC_startAgain.function = "MC_startAgain";
	}
}

void MC_startAgain(string qName)
{
	pchar.quest.MC_startInCaracas.win_condition.l1 = "location";
	pchar.quest.MC_startInCaracas.win_condition.l1.location = "Caracas_town";
	pchar.quest.MC_startInCaracas.function = "MC_startInCaracas";
}

void MC_endCaracas()
{
	bDisableFastReload = false;
	pchar.questTemp.MC = "toMaracaibo"; //флаг квеста	
	//вернём город
	int iTemp = FindLocation("Caracas_town");
	locations[iTemp].citizens = true;
	locations[iTemp].carrier = true;
	locations[iTemp].questSeekCap = 8;
	DeleteAttribute(&locations[iTemp], "reload.l1.disable");	
	DeleteAttribute(&locations[iTemp], "reload.l2.disable");
	DeleteAttribute(&locations[iTemp], "reload.l3.disable");
	DeleteAttribute(&locations[iTemp], "reload.l4.disable");
	DeleteAttribute(&locations[iTemp], "reload.l41.disable");
	DeleteAttribute(&locations[iTemp], "reload.l5.disable");
	DeleteAttribute(&locations[iTemp], "reload.l6.disable");
	DeleteAttribute(&locations[iTemp], "reload.l7.disable");
	DeleteAttribute(&locations[iTemp], "reload.l8.disable");
	DeleteAttribute(&locations[iTemp], "reload.l10.disable");
	DeleteAttribute(&locations[iTemp], "reload.gate.disable");
	DeleteAttribute(&locations[iTemp], "hidden_effects");
	//вернём таверну
	iTemp = FindLocation("Caracas_tavern");
	locations[iTemp].habitues = true;
	DeleteAttribute(&locations[iTemp], "reload.l1.disable");
	DeleteAttribute(&locations[iTemp], "reload.l4.disable");
	ref sld = characterFromId("Caracas_waitress"); //официантку тоже
	sld.location = "Caracas_tavern";
	sld.location.group = "waitress";
	sld.location.locator = "barmen";
	SetQuestHeader("MagicCity");
	AddQuestRecord("MagicCity", "1");
	pchar.quest.MC_DesMoinesInShore.win_condition.l1 = "location";
	pchar.quest.MC_DesMoinesInShore.win_condition.l1.location = "Shore_ship3";
	pchar.quest.MC_DesMoinesInShore.function = "MC_DesMoinesInShore";
	//добиваем служак что бы город ожил сразу, а не был мертвым еще 1-3 дня
    for (int i = 0; i<MAX_CHARACTERS; i++)
    {
        makeref(sld, characters[i]);
        if (CheckAttribute(sld, "CityType"))
        {
            sld.lifeday = 0;
            ChangeCharacterAddress(sld, "none", "");
        }
    }

    AddLandQuestMark_Main(CharacterFromId("Maracaibo_tavernkeeper"), "MagicCity");
    AddLandQuestMarkToFantoms_Main("DesMoinesHead", "MagicCity", "");
}

void MC_DesMoinesInShore(string qName)
{
	int i;
	ref sld;
	chrDisableReloadToLocation = true;
	LAi_LocationFightDisable(loadedLocation, true);

    for (i=1; i<=MOD_SKILL_ENEMY_RATE; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("ShoreGuard"+i, "officer_"+i, "man", "man", 20, PIRATE, 0, true)); //watch_quest_moment
		if(i == 6) sld.model = "officer_13"; //нигру скип
        FantomMakeCoolFighter(sld, 20, 70, 70, "topor2", "pistol3", 50);
		sld.dialog.filename = "Quest\MagicCity.c";
		sld.dialog.currentnode = "ShoreGuard";
		sld.BreakTmplAndFightGroup = true;
		sld.reactionOnFightModeOn = true;
        LAi_SetActorType(sld);			
        LAi_group_MoveCharacter(sld, "MC_DesMoinesInShore_Guards");				
		PlaceCharacter(sld, "goto", "random_must_be_near");
		LAi_ActorDialog(sld, pchar, "", -1.0, 0);
    }

	sld = CharacterFromID("ShoreGuard" + (1 + rand(i - 2)));
	AddItems(sld, "DesMoinesLocies", 1);
	sld.SaveQuestItemsForDead = true; // > сохранять только квестовые вещи
}

void MC_DesMoinesInShore_GuardsDead(string qName)
{
	AddQuestRecord("MagicCity", "3");

	pchar.quest.MC_DesMoinesInShore_GetDesMoinesLocies.win_condition.l1 = "item";
	pchar.quest.MC_DesMoinesInShore_GetDesMoinesLocies.win_condition.l1.item = "DesMoinesLocies";
	pchar.quest.MC_DesMoinesInShore_GetDesMoinesLocies.function = "MC_DesMoinesInShore_GetDesMoinesLocies";

	pchar.quest.MC_DesMoinesInShore_ExitShore_ship3.win_condition.l1 = "EnterToSea";
	pchar.quest.MC_DesMoinesInShore_ExitShore_ship3.function = "MC_DesMoinesInShore_ExitShore_ship3";

	pchar.quest.MC_DesMoinesInShore_EnterToMaracaibo_deadlock.win_condition.l1 = "location";
	pchar.quest.MC_DesMoinesInShore_EnterToMaracaibo_deadlock.win_condition.l1.location = "Maracaibo_deadlock";
	pchar.quest.MC_DesMoinesInShore_EnterToMaracaibo_deadlock.function = "MC_DesMoinesInShore_EnterToMaracaibo_deadlock";

	pchar.quest.MC_DesMoinesInShore_EnterToDesMoines.win_condition.l1 = "location";
	pchar.quest.MC_DesMoinesInShore_EnterToDesMoines.win_condition.l1.location = "DesMoines_town";
	pchar.quest.MC_DesMoinesInShore_EnterToDesMoines.function = "MC_DesMoinesInShore_EnterToDesMoines";

	LAi_MethodDelay("MC_DesMoinesInShore_GuardsDeadEndFight", 0.25);
}

void MC_DesMoinesInShore_GuardsDeadEndFight()
{
	LAi_group_Delete("MC_DesMoinesInShore_Guards");
	FightDisable_Forced();
}

void MC_DesMoinesInShore_GetDesMoinesLocies(string qName)
{
	AddQuestRecord("MagicCity", "3_1");
}

void MC_DesMoinesInShore_ExitShore_ship3(string qName)
{
	if (!CheckCharacterItem(pchar, "DesMoinesLocies"))
	{
		if (CheckAttribute(&TEV, "Quest_MagicCity_EnterToMaracaiboDeadlock"))
		{
			DeleteAttribute(&TEV, "Quest_MagicCity_EnterToMaracaiboDeadlock");
			AddQuestRecord("MagicCity", "3_4");
		}
		else
			AddQuestRecord("MagicCity", "3_2");

		AddItems(pchar, "DesMoinesLocies", 1);
	}

	DeleteAttribute(&TEV, "DesMoinesMoorDisable");
	DeleteQuestCheck("MC_DesMoinesInShore_GetDesMoinesLocies");
	DeleteQuestCheck("MC_DesMoinesInShore_EnterToMaracaibo_deadlock");
}

void MC_DesMoinesInShore_EnterToMaracaibo_deadlock(string qName)
{
	TEV.Quest_MagicCity_EnterToMaracaiboDeadlock = "1";
	AddQuestRecord("MagicCity", "3_3");
}

void MC_DesMoinesInShore_EnterToDesMoines(string qName)
{
	ref rItem = &Items[FindItem("DesMoinesLocies")];
	rItem.ItemType = "VARIETY";
	rItem.price = 69;
}

void MC_DanielleIsDead(string qName)
{
	AddQuestRecord("MagicCity", "10");
	CloseQuestHeader("MagicCity");
	
	ref sld = CharacterFromID("LizSheppard");
	sld.lifeDay = 30;
	SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");	
	sld.dialog.currentnode = "LizOver_end";
	sld.dialog.TempNode = "LizOver_end";
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Зачарованный город     eddy     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Линейка капитана Блада --     начало
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void Blood_StartGame(string qName)
{
    ref sld;
    Pchar.questTemp.CapBloodLine.stat = "Begining";
    Pchar.BaseNation = ENGLAND;
    //fix перков флагов
    DeleteAttribute(Pchar, "perks.list.FlagFra");
    DeleteAttribute(Pchar, "perks.list.FlagSpa");
    DeleteAttribute(Pchar, "perks.list.FlagHol");
    SetCharacterPerk(Pchar, "FlagEng");
    Flag_ENGLAND();
    //Подготовка Барбадоса
    int n = FindLocation("Bridgetown_town");
    DeleteAttribute(&locations[n], "questSeekCap");
    DeleteAttribute(&locations[n], "houseEnc");
    locations[n].notCloseCommonHouse = true;
    n = FindLocation("Bridgetown_tavern"); //homo fix
    DeleteAttribute(&locations[n], "habitues");
    //Обираем до нитки
    RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
    RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
    RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
    RemoveCharacterEquip(pchar, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(pchar, MAPS_ITEM_TYPE);
    DeleteAttribute(Pchar, "items");
    DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;
    TakeNItems(Pchar, "potion3", 1);
    TakeNItems(Pchar, "potion2", 3);
    TakeNItems(Pchar, "potion1", 4);
    SetCharacterPerk(Pchar, "Doctor1");
	SetCharacterPerk(Pchar, "Alchemy");
	
	//Эндрю Бэйнс
    sld = GetCharacter(NPC_GenerateCharacter("Beyns", "trader_8", "man", "man", 7, ENGLAND, 1, false));
    sld.name = FindPersonalName("Beyns_name");
    sld.lastname = FindPersonalName("Beyns_lastname");
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.dialog.currentnode = "First time";
	sld.greeting = "cit_common";
	string sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetStayTypeNoGroup(sld);
   	LAi_SetImmortal(sld, true);
	sld.talker = 10;
	ChangeCharacterAddressGroup(sld, "Estate", "goto", "goto12");
	AddLandQuestmark_Main(sld, "CapBloodLine");
	
    //==============//Джереми Питт//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Pitt", "Pitt", "man", "man", 1, ENGLAND, -1, false)); //TODO анимацию вернуть по готовности модельки
    sld.name 	= FindPersonalName("Pitt_name");
    sld.lastname 	= FindPersonalName("Pitt_lastname");
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_YoungMan";
//                  P I R  A T E  S
    SetSPECIAL(sld, 5,9,7,5,10,7,4);
    sld.rank = 3;
    sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
    sld.SaveItemsForDead = true; //оставлять эквип при смерти
	sld.HeroModel = "Pitt,Pitt_1,Pitt_2,Pitt_3,Pitt_4,Pitt_5,Pitt_6"; // Прописка всех моделей для кирас и обносков. <-- Konstrush
	sld.loyality = MAX_LOYALITY;
    InitStartParam(sld);
    //SetRandSPECIAL(sld);
    //int _fl, int _f, int _fh, int _p, int _fr
    SetSelfSkill(sld, 40, 35, 20, 40, 25);
    //int _ld, int _cr, int _ac, int _cn, int _sl, int _re, int _gr, int _de, int _sn
    SetShipSkill(sld, 45, 30, 25, 25, 50, 25, 25, 25, 30);
	//SetCharacterPerk(sld, "FastReload");
	//SetCharacterPerk(sld, "HullDamageUp");
	//SetCharacterPerk(sld, "SailsDamageUp");
	//SetCharacterPerk(sld, "CrewDamageUp");
	//SetCharacterPerk(sld, "CriticalShoot");
	//SetCharacterPerk(sld, "LongRangeShoot");
    //SetCharacterPerk(sld, "CannonProfessional");
	//SetCharacterPerk(sld, "ShipDefenseProfessional");
	
	SetCharacterPerk(sld, "ShipSpeedUp");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "WindCatcher");
	SetCharacterPerk(sld, "SailsMan");
	SetCharacterPerk(sld, "Ciras");
	
	//SetCharacterPerk(sld, "SwordplayProfessional");
	//SetCharacterPerk(sld, "AdvancedDefense");
	//SetCharacterPerk(sld, "CriticalHit");
	//SetCharacterPerk(sld, "Sliding");
	
	//черты
	SetCharacterPerk(sld, "LoyalOff");
	SetCharacterPerk(sld, "Honest"); //TODO: сверить по репутации
	
    SetFantomHP(sld);
    SetEnergyToCharacter(sld);
   	LAi_SetImmortal(sld, true);
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
	ChangeCharacterAddressGroup(sld, "Estate", "goto", "goto1");
	AddLandQuestmark_Main(sld, "CapBloodLine");
	
	pchar.quest.CureLordMovie.win_condition.l1 = "locator";
	pchar.quest.CureLordMovie.win_condition.l1.location = "EstateBadroom1";
	pchar.quest.CureLordMovie.win_condition.l1.locator_group = "quest";
	pchar.quest.CureLordMovie.win_condition.l1.locator = "quest1";
	pchar.quest.CureLordMovie.function = "CureLord";

	SetTutorials_Blood_Start();
}

void CureLord(string qName)
{
    ref sld;
    sld = &characters[GetCharacterIndex("Beyns")];
    ChangeCharacterAddressGroup(sld, "EstateBadroom1", "reload", "reload1");
    sld.dialog.currentnode = "EBStep_1";
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
//	LaunchInfoMessage(0);
    QuestPointerDelLoc("Estate", "reload", "reload3");
    QuestPointerDelLoc("EstateBadroom1", "quest", "quest1");
}

void CureLordMovie()
{
	InterfaceStates.Buttons.Save.enable = false;
	StartQuestMovie(true, true, true);
	Log_Clear();
	LAi_SetActorTypeNoGroup(Pchar);
	LAi_ActorGoToLocator(Pchar, "goto", "goto6", "CureLordMovie_Con1", 10.0);
}

void CureLordMovie_Con1()
{
    LAi_ActorTurnToLocator(Pchar, "goto", "goto7");
    LAi_ActorAnimation(Pchar, "Barman_idle", "CureLordMovie_Con2", 5);
}

void CureLordMovie_Con2()
{
	LAi_FadeEx(0.5, 0.0, 0.0, "", "", "CureLordMovie_Con3");
}

void CureLordMovie_Con3(string qName)
{
    ref sld;
    sld = &characters[GetCharacterIndex("Beyns")];
    sld.dialog.currentnode = "EBStep_2";
    AddLandQuestmark_Main(sld, "CapBloodLine");
//   	sld.talker = 10;
//    LAi_SetActorTypeNoGroup(sld);
//	LAi_ActorDialog(sld, pchar, "",  2, 0);
    ChangeCharacterAddressGroup(sld, "EstateOffice", "goto", "goto6");
    LAi_SetStayTypeNoGroup(sld);
    DoReloadCharacterToLocation("EstateOffice", "goto", "goto3");
    EndQuestMovie();
    LAi_SetPlayerType(Pchar);
    InterfaceStates.Buttons.Save.enable = true;
    LocatorReloadEnterDisable("Estate", "reload5", false);
}

void BloodGetBlade(string qName)
{
   	DoQuestFunctionDelay("Tutorial_BloodPrologue_Equipment", 1.0);
   	DoQuestFunctionDelay("DragunInvansion3", 30.0);
   	QuestPointerDelLoc("Estate", "quest", "quest3");
}

void DragunInvansion()
{
    ref sld;
    sld = &characters[GetCharacterIndex("Pitt")];
    sld.dialog.currentnode = "PStep_5";
    ChangeCharacterAddressGroup(sld, "EstateOffice", "reload", "reload1");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorDialog(sld, pchar, "",  -1, 0);

    sld = &characters[GetCharacterIndex("Beyns")];
    LAi_CharacterDisableDialog(sld);
}

void DragunInvansion2()
{
//	LaunchInfoMessage(1);
    pchar.quest.BloodGetBlade.win_condition.l1 = "item";
    pchar.quest.BloodGetBlade.win_condition.l1.item= "blade2";
    pchar.quest.BloodGetBlade.function = "BloodGetBlade";
    pchar.quest.DragunInvansion.win_condition.l1          = "location";
    pchar.quest.DragunInvansion.win_condition.l1.location = "Estate";
    pchar.quest.DragunInvansion.function                  = "_DragunInvansion3";

	LAi_SetCheckMinHP(Pchar, 1, true, "CapBlood_CheckMinHP");
   	LAi_SetImmortal(pchar, false);

	ref sld = &characters[GetCharacterIndex("Beyns")];
    LAi_CharacterEnableDialog(sld);
}

void _DragunInvansion3(string qName)
{
    chrDisableReloadToLocation = true; // закрыть выход из локации
//    DoQuestFunctionDelay("DragunInvansion3", 60.0); // перенесли на после лутания
    DoQuestFunctionDelay("Tutorial_BloodPrologue_LocItems", 1.0);
    // лок на обновление времени
	pchar.questTemp.TimeLock = true;
}

void DragunInvansion3(string qName)
{
	// Если в интерфейсе - ждём
	if (sti(InterfaceStates.Launched) == true || DialogRun != 0)
	{
    	DoQuestFunctionDelay("DragunInvansion3", 1.0);
    	return;
	}

	StartQuestMovie(true, false, true);
	LAi_FadeEx(1.0, 0.0, 1.0, "", "DragunInvansion3_1", "");
	LAi_SetActorType(pchar);
}

void DragunInvansion3_1(string qName)
{
	ref ch, sld;
	string sTemp;
	LAi_LocationFightDisable(loadedLocation, true);
	LAi_SetFightMode(Pchar, false);
	LAi_LockFightMode(pchar, true);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 3000.0); //fix
	
	LAi_SetStayType(pchar);
	ChangeCharacterAddressGroup(pchar, "Estate", "quest", "quest2");

	ch = GetCharacter(NPC_GenerateCharacter("CapGobart", "Hobart", "man", "man", 10, ENGLAND, 0, false));
	ch.name 	= FindPersonalName("CapGobart_name");
	ch.lastname 	= FindPersonalName("CapGobart_lastname");
	ch.location = "none";
	FantomMakeCoolFighter(ch, 25, 70, 70, "blade22", "pistol2", 20);
	LAi_SetImmortal(ch, true);
	ch.BreakTmplAndFightGroup = true; //fix
	LAi_group_MoveCharacter(ch, LAI_GROUP_TmpEnemy);
	//LAi_group_MoveCharacter(ch, "EnemyFight");
	ChangeCharacterAddressGroup(ch, "Estate", "quest", "quest1");
	LAi_SetActorTypeNoGroup(ch);
	// LAi_ActorDialog(ch, pchar, "", 7, 0);

	for (int i=0 ; i<=4; i++)
	{
		// генерим c сопровождение
		sTemp = "guard_eng_" + i;
		if (i == 0) sTemp = "Workman_1";
		sld = GetCharacter(NPC_GenerateCharacter(("Dragun_"+i), sTemp, "man", "man", 2, ENGLAND, 0, false));
		sld.location = "none";
		sld.BreakTmplAndFightGroup = true;
		SetSPECIAL(sld, 8,10,9,3,6,10,4);
		InitStartParam(sld);
		SetEnergyToCharacter(sld);
		LAi_SetImmortal(sld, true); // потом снимаем
		//LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
		GiveItem2Character(sld, "blade4");
		EquipCharacterByItem(sld, "blade4");
		sld.Dialog.CurrentNode = "Draguns_0";
		sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
		LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
		//LAi_group_MoveCharacter(sld, "EnemyFight");
		if (i == 0) ChangeCharacterAddressGroup(sld, "Estate", "goto", "stay5");
		else if (i == 1) ChangeCharacterAddressGroup(sld, "Estate", "goto", "stay6");
		else ChangeCharacterAddressGroup(sld, "Estate", "goto", "stay"+i);
		LAi_SetActorTypeNoGroup(sld);
		if(i < 3)
		{
			if( i > 0 )
			{
				GiveItem2Character(sld, "pistol2");
				EquipCharacterByItem(sld, "pistol2");
				TakeNItems(sld, "bullet", 30);
				AddItems(sld, "GunPowder", 30);
			}
			// LAi_ActorFollow(sld, ch, "", -1);
		}
		// if(i == 3)LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 20);
		// if(i == 4)LAi_ActorRunToLocation(sld, "reload", "reload5", "none", "", "", "", 20);
	}
	
	sld = GetCharacter(NPC_GenerateCharacter("Kirk", "huber_11", "man", "man", 10, ENGLAND, 0, false));
	sld.name 	= FindPersonalName("Kirk_name");
	sld.lastname 	= FindPersonalName("Kirk_lastname");
	sld.location = "none";
	FantomMakeCoolFighter(sld, 25, 70, 70, "blade22", "pistol2", 20);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Estate", "goto", "stay1");
	LAi_SetActorTypeNoGroup(sld);
	locCameraFromToPos(-14.21, 8.59, -1.65, true, -19.00, 5.91, -0.60);
	DoQuestFunctionDelay("CapBloodLine_Kirk", 0.5);
}

void CapBloodLine_Kirk(string qName)
{
 	ref sld = CharacterFromID("Kirk");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorFollow(sld, CharacterFromID("CapGobart"), "CapBloodLine_Kirk_2", -1);
}

void CapBloodLine_Kirk_2()
{
 	ref sld = CharacterFromID("Kirk");
	sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
	sld.Dialog.CurrentNode = "Kirk";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void CapBloodLine_Kirk_3()
{
	locCameraSleep(true);
 	ref sld = CharacterFromID("Kirk");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "CapBloodLine_Kirk_4", -1);
}

void CapBloodLine_Kirk_4()
{
 	ref sld = CharacterFromID("CapGobart");
	sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
	sld.Dialog.CurrentNode = "Gobart";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void CapBloodLine_Kirk_5()
{
	LAi_FadeEx(1.0, 3.5, 1.0, "CapBloodLine_Kirk_5_1", "CapBloodLine_Kirk_6", "");
}

void CapBloodLine_Kirk_5_1(string qName)
{
 	ref chr = CharacterFromID("CapGobart");
	LAi_SetActorType(chr);
	LAi_ActorGoToLocator(chr, "goto", "goto7", "", -1);
	
	for (int i=0 ; i<=4; i++)
	{
		ref sld = CharacterFromID("Dragun_"+i);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, chr, "", -1);
	}
}

void CapBloodLine_Kirk_6(string qName)
{
	locCameraSleep(false);
 	locCameraFlyToPositionLookToAngle(-23.8, 8.0, 3.25, -4.00, 15.15, 0.30, -20.0, 90.0, -1.0, 16000/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_Kirk_7";
}

void CapBloodLine_Kirk_7()
{
 	locCameraSleep(true);
	DoQuestFunctionDelay("CapBloodLine_Kirk_7_1", 1.5);
}

void CapBloodLine_Kirk_7_1(string qName)
{
	LAi_SetActorType(pchar);
 	LAi_ActorGoToLocator(pchar, "goto", "goto10", "", -1);
	DoQuestFunctionDelay("CapBloodLine_Kirk_8", 2.0);
}

void CapBloodLine_Kirk_8(string qName)
{
 	LAi_FadeEx(1.0, 0.3, 1.0, "", "DragunInvansion4", "");
}

void CapBloodLine_Kirk_9()
{
 	ref sld = &characters[GetCharacterIndex("Pitt")];
	LAi_type_actor_Reset(sld);
    CharacterTurnByChr(sld, pchar);
    
    sld = &characters[GetCharacterIndex("Beyns")];
	LAi_type_actor_Reset(sld);
	CharacterTurnByChr(sld, pchar);

    for (int i=3; i<=4; i++)
    {
        sld = &characters[GetCharacterIndex("Dragun_"+i)];
		LAi_type_actor_Reset(sld);
		CharacterTurnByChr(sld, pchar);
    }
}

void CapBloodLine_Kirk_10()
{
 	ref sld = CharacterFromID("CapGobart");
	CharacterTurnToLoc(sld, "goto", "goto12");
}

void DragunInvansion4(string qName)
{
	locCameraSleep(false);
 	LAi_SetStayType(pchar);
	ChangeCharacterAddressGroup(pchar, "Estate", "goto", "goto12");
	
	ref ch, sld;
    LAi_LockFightMode(pchar, false);
    LAi_LocationFightDisable(loadedLocation, false);
    ch = &characters[GetCharacterIndex("Pitt")];
    ChangeCharacterAddressGroup(ch, "Estate", "reload", "reload5");
    LAi_SetActorType(ch);
    LAi_ActorGoToLocator(ch, "goto", "goto5", "CapBloodLine_Kirk_9", -1);
    
    sld = &characters[GetCharacterIndex("Beyns")];
    ChangeCharacterAddressGroup(sld, "Estate", "reload", "reload5");
    LAi_SetActorType(sld);
    LAi_ActorFollow(sld, ch, "", -1);

    for (int i=0; i<5; i++)
    {
        sld = &characters[GetCharacterIndex("Dragun_"+i)];
        //LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
        if(i == 3 || i == 4)
        {
            ChangeCharacterAddressGroup(sld, "Estate", "reload", "reload5");
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorFollow(sld, ch, "", -1);
        }
        else
        {
			if(i == 0) TeleportCharacterToPosAy(sld, 8.11, 6.52, 0.15, 1.50);
			else if(i == 1) TeleportCharacterToPosAy(sld, 8.41, 6.52, -1.15, 1.30);
			else if(i == 2) TeleportCharacterToPosAy(sld, 8.41, 6.52, 1.15, 1.70);
			LAi_SetStayTypeNoGroup(sld);
        }
    }
	
	ch = CharacterFromID("CapGobart");
	TeleportCharacterToPosAy(ch, 9.41, 6.52, 0.15, 1.50);
	ch.Dialog.CurrentNode = "First time";
	ch.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	ch.greeting = "soldier_arest";
	LAi_SetActorType(ch);
	LAi_ActorDialogNow(ch, Pchar, "", -1);
}

void CapGobartAttack(string qName)
{
    ref sld;
    int numdead = 0;
    for (int i=0; i<=1; i++)
    {
        sld = characterFromID("Dragun_"+i);
        if (CharacterIsDead(sld))
        {
            numdead++;
        }
    }
    if(numdead == 2)
    {
        sld = characterFromID("CapGobart");
        // LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
		LAi_group_MoveCharacter(sld, "TmpEnemy");
        LAi_SetWarriorTypeNoGroup(sld);
        LAi_group_Attack(sld, Pchar);
    }
}
/////////////////////////////////////////////////////////////////////////
void Blood_StartGame_End(string qName)
{
	ResetSound();
    ref sld;
    chrDisableReloadToLocation = true;
    InterfaceStates.Launched = false;
    InterfaceStates.Buttons.Save.enable = true;
    sld = characterFromID("Dragun_0");
    LAi_RemoveCheckMinHP(sld);
    pchar.quest.CapGobartAttack_1.over = "yes";
    pchar.quest.CapGobartAttack_2.over = "yes";
    // снимаем лок на обновление времени
    DeleteAttribute(pchar, "questTemp.TimeLock");

	CreateEntity(&LAi_QuestFader, "fader");
	SendMessage(&LAi_QuestFader, "lfl", FADER_OUT, 0.5, false);
	LAi_QuestFader.oldSaveState = InterfaceStates.Buttons.Save.enable;
	InterfaceStates.Buttons.Save.enable = 0;

	DoQuestFunctionDelay("CapBloodLineInit", 0.1);
}


void CapBloodLineInit(string qName)
{
    //Возвращаем все после плена
    LAi_SetCurHPMax(Pchar);
    LAi_SetPlayerType(Pchar);
    //Рабство
    LAi_SetImmortal(Pchar, false);
    DeleteAttribute(Pchar, "items");
    DeleteAttribute(Pchar, "equip");
    DeleteAttribute(Pchar, "ship");
    DeleteAttribute(Pchar, "ShipSails.gerald_name");
    Pchar.ship.type = SHIP_NOTUSED;
    /*GiveItem2Character(Pchar, "unarmed");
    EquipCharacterByItem(Pchar, "unarmed");*/
    Pchar.money = 0;
    // Cтид
    ref sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.name = FindPersonalName("Bridgetown_Mayor_name");
    sld.lastname = FindPersonalName("Bridgetown_Mayor_lastname");
    // Первый квест
	Environment.date.month = 4;
    SetCurrentTime(23, 1);
    pchar.quest.onPlantation.win_condition.l1          = "location";
    pchar.quest.onPlantation.win_condition.l1.location = "BridgeTown_Plantation";
    pchar.quest.onPlantation.function                  = "CapBloodLine_q1";
    //DoReloadCharacterToLocation("BridgeTown_Plantation", "patrol", "patrol12");

    //квест ночной, поэтому так вот               //TODO
    int n= FindLocation("Bridgetown_town");  // не забыть вернуть
    locations[n].reload.l3.close_for_night = false;
    //для энкаунтеров в джанглах
    bDisableLandEncounters = true;

	PostLocaleVideoAndQuest("slave", 100, "move_slave_2");
}

void CapBloodLine_firstEnterHome(string qName)
{	
	ref sld = characterFromID("Pitt");
	sld.model = "Pitt_6";
	sld.Dialog.CurrentNode = "PStep_7";
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	string sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_G6", "reload", "reload1");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 3, 0);
	Pchar.questTemp.CapBloodLine.statcrew = "";	
}


void CapBloodLine_q1(string qName)
{
    ref sld; string sTemp;
    LAi_LocationFightDisable(loadedLocation, true);
    LAi_SetFightMode(Pchar, false);
    LAi_LockFightMode(pchar, true);
    chrDisableReloadToLocation = true; // закрыть выход из локации
    bDisableFastReload = true; // закрыть переходы.
    Pchar.questTemp.CapBUnarmed = true; //ГГ сабля не положена

    //Бишоп на плантациях
   	sld = GetCharacter(NPC_GenerateCharacter("Bishop", "merch_13", "man", "man", 1, ENGLAND, 3, false));
    sld.name 	= FindPersonalName("Bishop_name");
    sld.lastname 	= FindPersonalName("Bishop_lastname");
    sld.Dialog.CurrentNode = "First Bishop";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Bishop";

    SetSPECIAL(sld, 9,8,10,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    GiveItem2Character(sld, "blade22");
	EquipCharacterByItem(sld, "blade22");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterByItem(sld, "pistol2");
	LAi_SetImmortal(sld, true);

    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "reload", "houseSp1");
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);

    //Джереми Питт
    sld = characterFromID("Pitt");
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    LAi_SetCitizenType(sld);
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "officers", "houseS1_3");
    //кузнец
	sld = GetCharacter(NPC_GenerateCharacter("Griffin", "blacksmith_1", "man", "man", 10, ENGLAND, 3, false));
	sld.name = FindPersonalName("Griffin_name");
	sld.lastname = FindPersonalName("Griffin_lastname");
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Master";
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_SetOwnerType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
	ChangeCharacterAddressGroup(sld, "CommonFlamHouse", "goto","goto1");
	LAi_SetImmortal(sld, true);
    //Рыбак
	sld = GetCharacter(NPC_GenerateCharacter("Hells", "shipowner_9", "man", "man", 10, PIRATE, 3, false));
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.name = FindPersonalName("Hells_name");
	sld.lastname = FindPersonalName("Hells_lastname");
    sld.SaveItemsForDead = true; // сохранять на трупе вещи
    sld.DontClearDead = true;
	sld.greeting = "Gr_Fisher";
	AddMoneyToCharacter(sld, 2000);
	FantomMakeCoolFighter(sld, 7, 25, 50, "topor1", "", 10);
    TakeItemFromCharacter(sld, "spyglass3");
    LAi_SetOwnerTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "Bridgetown_Hut1", "goto","goto3");
	//Контра
	sld = GetCharacter(NPC_GenerateCharacter("Quest_Smuggler", "Animists_1", "man", "man", 10, ENGLAND, 3, false));
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	sld.name = FindPersonalName("Quest_Smuggler_name");
	sld.lastname = FindPersonalName("Quest_Smuggler_lastname");
    sld.greeting = "Gr_Smuggler Agent";
	LAi_SetSitTypeNoGroup(sld);
	ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit2");

    //алкаши в таверне
    int i=rand(2);
	sld = GetCharacter(NPC_GenerateCharacter("Quest_Habitue", RandCitizenModel(), "man", "man", 10, ENGLAND, 3, false));
	sld.greeting = "Gr_Tavern_Mate";
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.Default           = "Bridgetown_tavern";
    sld.Default.group     = "sit";
    sld.Default.ToLocator = "sit_front" + (i+1);
    LAi_SetCitizenType(sld);
    LAi_SetSitTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit_base"+(1+i));		

    //==============//Волверстон//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Volverston", "Volverston_6", "man", "man", 12, ENGLAND, -1, false));
    sld.name 	= FindPersonalName("Volverston_name");
    sld.lastname 	= FindPersonalName("Volverston_lastname");
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Officer";
   	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
    SetRandSPECIAL(sld);
    InitStartParam(sld);
    sld.rank = 10;
	sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
	sld.loyality = MAX_LOYALITY;
	//               P  I  E  A  T  R  S
	SetSPECIAL(sld, 10, 7, 9, 8, 8, 4, 8);
    //int           _fl,  f,  fh, p,  fr
    SetSelfSkill(sld, 20, 30, 45, 30, 40);//
    //int            ld,  cr, ac, cn, sl, re, gr, de, sn
    SetShipSkill(sld, 45, 30, 15, 15, 10, 40, 45, 30, 20);
   	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Grus");
	SetCharacterPerk(sld, "Rush");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "IronWill");
	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "GrapplingProfessional");
	//черты
	SetCharacterPerk(sld, "LoyalOff");
    SetEnergyToCharacter(sld);
    SetFantomHP(sld);
   	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "officers", "houseF2_1");

    //==============//Натаниэль   Хагторп//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Hugtorp", "Hugtorp_6", "man", "man", 10, ENGLAND, -1, false));
    sld.name 	= FindPersonalName("Hugtorp_name");
    sld.lastname 	= FindPersonalName("Hugtorp_lastname");
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Officer";
   	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
    SetRandSPECIAL(sld);
    InitStartParam(sld);
    sld.rank = 10;
	sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
	sld.loyality = MAX_LOYALITY;
	//              P  I  E  A  T  R  S
	SetSPECIAL(sld, 8, 9, 8, 8, 9, 8, 7);
    //int _fl, int _f, int _fh, int _p, int _fr
    SetSelfSkill(sld, 20, 40, 35, 30, 30);
    //int _ld, int _cr,  ac, cn, sl, re, gr, de, sn
    SetShipSkill(sld, 40, 30, 25, 25, 20, 25, 35, 30, 20);
   	SetCharacterPerk(sld, "LongRangeGrappling");
	SetCharacterPerk(sld, "BasicBattleState");
	SetCharacterPerk(sld, "Troopers");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "Gunman");
	//черты
	SetCharacterPerk(sld, "LoyalOff");
    SetEnergyToCharacter(sld);
    SetFantomHP(sld);
   	LAi_SetImmortal(sld, true);
   	ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "officers", "houseS2_2");
   	
    //==============//Николас Дайк//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Dieke", "Dieke_6", "man", "man", 10, ENGLAND, -1, false));
    sld.name 	= FindPersonalName("Dieke_name");
    sld.lastname 	= FindPersonalName("Dieke_lastname");
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Officer";
   	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
    SetRandSPECIAL(sld);
    InitStartParam(sld);
    sld.rank = 10;
	sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
	sld.loyality = MAX_LOYALITY;
//                    P  I  E  A  T  R  S
	SetSPECIAL(sld, 6, 8, 7, 5, 9, 9, 7);
    //int _fl, int _f, int _fh, int _p, int _fr
    SetSelfSkill(sld, 40, 35, 20, 30, 30);
    //                ld, cr, ac, cn, sl, re, gr, de, sn
    SetShipSkill(sld, 30, 35, 20, 20, 20, 40, 25, 35, 20);
   	SetCharacterPerk(sld, "BasicCommerce");
	SetCharacterPerk(sld, "LightRepair");
	SetCharacterPerk(sld, "Carpenter");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "EnergyPlus");
	//черты
	SetCharacterPerk(sld, "LoyalOff");
    SetEnergyToCharacter(sld);
    SetFantomHP(sld);
   	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "officers", "houseF1_1");
	
	
    //==============//Нед Огл//==============
   	sld = GetCharacter(NPC_GenerateCharacter("Ogl", "Ogl_6", "man", "man", 10, ENGLAND, -1, false));
    sld.name 	= FindPersonalName("Ogl_name");
    sld.lastname 	= FindPersonalName("Ogl_lastname");
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_Ogl";
   	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    LAi_SetCitizenType(sld);
    LAi_SetStayTypeNoGroup(sld);
    SetRandSPECIAL(sld);
    InitStartParam(sld);
    sld.rank = 10;
    sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
    sld.SaveItemsForDead = true; //оставлять эквип при смерти
	sld.loyality = MAX_LOYALITY;
//                     P  I  E  A  T  R  S
	SetSPECIAL(sld, 7, 10, 5, 5, 9, 5, 9);
    //int           _fl,  f,  fh, p,  fr
    SetSelfSkill(sld, 20, 30, 20, 35, 30);
    //int            ld,  cr, ac, cn, sl, re, gr, de, sn
    SetShipSkill(sld, 20, 10, 50, 40, 15, 20, 20, 20, 20);
   	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "SharedExperience");
	//черты
	SetCharacterPerk(sld, "LoyalOff");
    SetEnergyToCharacter(sld);
    SetFantomHP(sld);
   	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation_S2", "goto", "goto1");

	
    //==============//Сандро Торн//==============
    sld = GetCharacter(NPC_GenerateCharacter("Slave_Quest", "Sandro_Thorne_6", "man", "man", 7, ENGLAND, 2, false));
	sld.name 	= FindPersonalName("Slave_Quest_name");
    sld.lastname 	= FindPersonalName("Slave_Quest_lastname");
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.Dialog.CurrentNode = "SLQStep_0";
    sld.greeting = "Gr_SandroT";
    sld.talker = 10;
    sld.CityType = "citizen";
	sld.city = "BridgeTown";
	LAi_SetLoginTime(sld, 6.0, 22.99);
    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "goto", "goto12");
	LAi_SetCitizenType(sld);
    LAi_group_MoveCharacter(sld, sTemp);

    //раскидаем квестовых нпс по локациям
	SetQuestsCharacters();

    // первый заход в город
    pchar.quest.CapBloodLine_q1_1.win_condition.l1          = "location";
    pchar.quest.CapBloodLine_q1_1.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodLine_q1_1.function                  = "_PrepareBridgeTown";

	// Установка туториалов
	SetBloodTutorials_AfterEstate();
}

void ChangePIRATES()
{
	pchar.SystemInfo.ChangePIRATES = true;
	LaunchCharacter(pchar);
}

void _PrepareBridgeTown(string qName)
{
    DoQuestFunctionDelay("PrepareBridgeTown", 1.0);
}
void PrepareBridgeTown(string qName)
{
    trace("PrepareBridgeTown");
    //меняем город под рабство
    ChangeBridgeTownDialogs(false);
    //солдат на страже у резиденции
    ref sld = &characters[GetCharacterbyLocation("Bridgetown_town", "soldiers", "soldier2")];
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.Dialog.CurrentNode = "First Guard";
    sld.protector = true;
    sld.protector.CheckAlways = 1 ;
    LAi_RemoveLoginTime(sld);
    LoginCharacter(sld, "BridgeTown_town");
    AddLandQuestmark_Main(sld, "CapBloodLine");
    //Нэтталл
    LoginNettl("");
    //закроем резиденцию до поры
    LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", true); //fix
    LocatorReloadEnterDisable("BridgeTown_fort", "reload2", true); //fix
    //уберем пьянь из таверны
    //int n = FindLocation("Bridgetown_tavern");
    //locations[n].habitues = 0;
    //контрик нужен
    sld = &characters[GetCharacterIndex("Bridgetown_Smuggler")];
    LoginCharacter(sld, "Bridgetown_tavern");
    CapBloodLine_ReachQuestPointer_Plantation("");

	HarvestHerbCustom("Bridgetown_ExitTown", "herb_zingiber:6,herb_matricaria:3");
}

void DetectBlades()
{
	if (Pchar.questTemp.CapBloodLine == false) return;
	if (Pchar.questTemp.CapBUnarmed == false) return;
	if (loadedlocation.id != "Bridgetown_town" && loadedlocation.id != "BridgeTown_Plantation") return;

	aref arCurItem, arItem, arItems; makearef(arItems, pchar.items);
	int i, q = GetAttributesNum(arItems);
	string sItem;

	for (i = 0; i < q; i++)
	{
		arCurItem = GetAttributeN(arItems, i);
		if (Items_FindItem(GetAttributeName(arCurItem), &arItem) >= 0)
		{
			if (!CheckAttribute(arItem, "groupID")) continue;
			if (arItem.groupID == BLADE_ITEM_TYPE || arItem.groupID == GUN_ITEM_TYPE)
			{
				sItem = arItem.id;
				if (sItem == "unarmed" || HasSubStr(sItem, "blade5")) continue;
				if (!CheckAttribute(pchar, "items." + sItem) || sti(pchar.items.(sItem)) < 1) continue;
				BloodTakeBlades();
				return;
			}
		}
	}
}

//HardCoffee ref SoldierNotBlade
void BloodTakeBlades()
{
    ref sld = GetCharacter(NPC_GenerateCharacter("SolderTakeBlades", "sold_eng_1", "man", "man", 10, ENGLAND, 0, false));
    CreateModel(sti(sld.index), "urban_sold", MAN); // моделька городской стражи
	sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
	sld.dialog.currentnode = "First time";
	sld.city = "Bridgetown_town";
    sld.greeting = "VOICE\" + VoiceGetLanguage() + "\soldier_arest_1.wav";
    sld.location = "none";
    sld.BreakTmplAndFight = true;
    //SetFantomParamHunter(sld); //крутые парни
    SetFantomParamFromRank(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true);
	LAi_SetCitizenType(sld);
	string sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    PlaceCharacter(sld, "goto", "random_must_be_near"))
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;
    pchar.quest.SolderTakeBladesDie.win_condition.l1 = "NPC_death";
    pchar.quest.SolderTakeBladesDie.win_condition.l1.character = "SolderTakeBlades";
   	pchar.quest.SolderTakeBladesDie.function = "SolderTakeBladesDie";
	//Log_TestInfo("Сейчас у ГГ заберут саблю!");
}

void SolderTakeBladesDie(string qName)
{
    chrDisableReloadToLocation = false;
}


//Меняет всем дилоги
void ChangeBridgeTownDialogs(bool restore)
{
    ref sld;
    int num, cur;
    num = 0;
    cur = rand(3)+1;
    for(int i=0;i<MAX_CHARACTERS;i++)
	{
        sld = &characters[i];
        //солдаты
        if (CheckAttribute(sld, "city") && sld.city == "Bridgetown")
        {
            if(CheckAttribute(sld, "CityType") && sld.CityType == "soldier")
            {
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                }
                else
                {
                    sld.dialog.filename = "Common_Soldier.c";
                }
                sld.lifeDay = 3;
            }
            //горожане
            if(CheckAttribute(sld, "CityType") && sld.CityType == "citizen")
            {
				if(HasSubStr(sld.dialog.filename, "Population"))
				DeleteAttribute(sld, "talker"); // снимаем говорилку у новых NPC
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                    if(sld.location.group == "merchant")
                    {   //торговцы
                        num++;
                        if(num == cur) // для квеста по добычи оружия метим одного продавца
                        {
                            sld.quest.bGoodMerch = true;
                        }

                    }
                }
                else
                {
                    if(sld.location.group == "merchant")
                    {   //торговцы
                        sld.dialog.filename = "Common_ItemTrader.c";
                    }
                    else
                    {   //обычные
                        sld.dialog.filename = "Common_Citizen.c";
                    }
                }
                sld.lifeDay = 3;
            }
            //нищие
            if(sld.id == "Bridgetown_Poorman")
            {
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                }
                else
                {
                    sld.dialog.filename = "Common_Poorman.c";
                }
            }
            //квестовые
            if(sld.id == "QuestCitiz_Bridgetown")
            {
                if (!restore)
                {
                    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
                    sld.Dialog.CurrentNode = "First time";
                }
                else
                {
                    sld.dialog.filename = "Quest\ForAll_dialog.c";
                }
            }
        }
	}
}

void LoginNettl(string qName)
{
    Pchar.questTemp.CapBloodLine.TalkWithNettl = false;          //10//3
    ref sld = GetCharacter(NPC_GenerateCharacter("Nettl", "Nettall", "man", "man", 7, ENGLAND, 3, false));
    sld.name = FindPersonalName("Nettl_name");
    sld.lastname = FindPersonalName("Nettl_lastname");
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.dialog.currentnode = "First time";
    sld.city = "Bridgetown_town";
    sld.greeting = "vsluni";
//		LAi_SetLoginTime(sld, 0.0, 23.99);
    //SetFantomParamFromRank(sld, Rank, true);
    LAi_SetCitizenType(sld);
    string sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_group_MoveCharacter(sld, sTemp);
    sld.talker = 10;
    PlaceCharacter(sld, "goto", "random");
}

void Nettl_Away_Force(string qName)
{
    DoQuestCheckDelay("NettlOnTavern", 0.1);
}

void CapBloodLine_q1_Late(string qName)
{
	if (procEnableInterfaceLaunch(INTERFACE_FRAMEFORM) == false)
	{
		DoQuestFunctionDelay("CapBloodLine_q1_Late", 1.0);
		return;
	}

    InterfaceStates.Buttons.Save.enable = false;
    SetLaunchFrameFormParam(StringFromKey("InfoMessages_244"), "Run_Function", 0.1, 10.0);
    SetLaunchFrameRunFunctionParam("CapBloodLine_q1_Late_GameOver", 0.0);
	LaunchFrameForm();
}

void CapBloodLine_q1_Late_GameOver()
{
//    GameOver("blood");
    GameOver("land");
}

float CapBloodLine_CureMisStid_GetRangeToReload1Locator()
{
    float dx, dy, dz, d1, d2;
    float x, y, z;
    if(GetCharacterPos(pchar, &x, &y, &z) == false)
    {
        x = 0.0; y = 0.0; z = 0.0;
    }
    if(IsEntity(loadedLocation) != true) return 1000.0;
	if(!CheckAttribute(loadedLocation, "locators.reload.reload1_back")) return 1000.0;
	aref loc;
	makearef(loc, loadedLocation.locators.reload.reload1_back);
	dx = x - stf(loc.x);
    dy = y - stf(loc.y);
    dz = z - stf(loc.z);
    d1 = sqrt(dx*dx + dy*dy + dz*dz);

    return d1;
}

void CapBloodLine_CureMisStid_AddQuestPointers()
{
    if (CapBloodLine_CureMisStid_GetRangeToReload1Locator() < 128.0)
    {
        CapBloodLine_ReachQuestPointer_Plantation("");
        return;
    }
    QuestPointerToLoc("Bridgetown_Plantation", "goto", "goto17");
    TEV.CapBloodLine_PlantationGoto17Radius = loadedLocation.locators_radius.goto;
    if (CheckAttribute(loadedlocation, "locators_radius.goto.goto17"))
    {
        TEV.CapBloodLine_PlantationGoto17Radius = loadedLocation.locators_radius.goto.goto17;
        TEV.CapBloodLine_PlantationGoto17Radius.over = true;
    }
    float fNewRadius = 5.0;
    loadedLocation.locators_radius.goto.goto17 = fNewRadius;

    SetLocatorRadius(loadedLocation, "goto", "goto17", fNewRadius);
    SendMessage(loadedLocation, "l", MSG_LOCATION_UPDATELOCATORS);

    pchar.quest.CapBloodLine_ReachQuestPointer_Plantation.win_condition.l1 = "locator";
    pchar.quest.CapBloodLine_ReachQuestPointer_Plantation.win_condition.l1.location = "Bridgetown_Plantation";
    pchar.quest.CapBloodLine_ReachQuestPointer_Plantation.win_condition.l1.locator_group = "goto";
    pchar.quest.CapBloodLine_ReachQuestPointer_Plantation.win_condition.l1.locator = "goto17";
    pchar.quest.CapBloodLine_ReachQuestPointer_Plantation.function = "CapBloodLine_ReachQuestPointer_Plantation";
}

void CapBloodLine_ReachQuestPointer_Plantation(string qName)
{
    QuestPointerDelLoc("Bridgetown_Plantation", "goto", "goto17");
    QuestPointerToLoc("Bridgetown_Plantation", "reload", "reload1_back");
    QuestPointerToLoc("Bridgetown_town", "reload", "reload3_back");

    CapBloodLine_ReachQuestPointer_Plantation_Goto17Restore();
}

void CapBloodLine_ReachQuestPointer_Plantation_Goto17Restore()
{
    if (CheckAttribute(&TEV, "CapBloodLine_PlantationGoto17Radius"))
    {
        ref loadedLoc = &Locations[FindLocation("Bridgetown_Plantation")];

        float fRadius = stf(TEV.CapBloodLine_PlantationGoto17Radius);
        if (CheckAttribute(&TEV, "CapBloodLine_PlantationGoto17Radius.over"))
        {
            loadedLoc.locators_radius.goto.goto17 = stf(TEV.CapBloodLine_PlantationGoto17Radius);
        }
        else
        {
            DeleteAttribute(loadedLoc, "locators_radius.goto.goto17");
        }
        DeleteAttribute(&TEV, "CapBloodLine_PlantationGoto17Radius");

        SetLocatorRadius(loadedLoc, "goto", "goto17", fRadius);
        SendMessage(loadedLoc, "l", MSG_LOCATION_UPDATELOCATORS);
    }
}

void CapBloodLine_CureMisStid_AddQuestPointers_2()
{
    pchar.quest.CapBloodLine_ReachQuestPointer_Plantation.over = "yes";
    CapBloodLine_ReachQuestPointer_Plantation_Goto17Restore();

    QuestPointerDelLoc("Bridgetown_Plantation", "goto", "goto17");
    QuestPointerDelLoc("Bridgetown_Plantation", "reload", "reload1_back");
    QuestPointerDelLoc("Bridgetown_town", "reload", "reload3_back");

    QuestPointerToLoc("Bridgetown_townhall", "reload", "reload3");
    QuestPointerToLoc("Bridgetown_TownhallRoom", "reload", "reload2");
}

void CapBloodLine_CureMisStid_AddQuestPointers_3()
{
    QuestPointerDelLoc("Bridgetown_townhall", "reload", "reload3");
    QuestPointerDelLoc("Bridgetown_TownhallRoom", "reload", "reload2");

    QuestPointerToLoc("CommonBedroom", "reload", "reload1");
    QuestPointerToLoc("Bridgetown_TownhallRoom", "reload", "reload1");
    QuestPointerToLoc("Bridgetown_townhall", "reload", "reload1_back");
    QuestPointerToLoc("Bridgetown_town", "reload", "HouseSP1");
}

void CapBloodLine_WateDen()
{
    QuestPointerDelLoc("CommonBedroom", "reload", "reload1");
    QuestPointerDelLoc("Bridgetown_TownhallRoom", "reload", "reload1");
    QuestPointerDelLoc("Bridgetown_townhall", "reload", "reload1_back");
    QuestPointerDelLoc("Bridgetown_town", "reload", "HouseSP1");

    DoQuestFunctionDelay("CapBloodLine_TiredWateDen", 20.0);

    pchar.quest.CapBloodLine_TiredWateDan_1.win_condition.l1 = "ExitFromLocation";
    pchar.quest.CapBloodLine_TiredWateDan_1.win_condition.l1.location = pchar.location;
    pchar.quest.CapBloodLine_TiredWateDan_1.function = "CapBloodLine_TiredWateDen_1";
}

void CapBloodLine_TiredWateDen(string qName)
{
    QuestPointerToLoc("CommonPirateHouse", "reload", "reload1");
}

void CapBloodLine_TiredWateDen_1(string qName)
{
    DeleteAttribute(pchar, "PostEventQuest.questDelay.CapBloodLine_TiredWateDen");
    QuestPointerDelLoc("CommonPirateHouse", "reload", "reload1");
}

void CapBloodLine_q1_End(string qName)
{
	if (CheckAttribute(Pchar, "questTemp.CapBloodLine.isNotPotion")) 
	{
		AddQuestRecord("CapBloodLine_q1", "7");
	} 
	else 
	{
		AddQuestRecord("CapBloodLine_q1", "6");
	}
   Pchar.questTemp.CapBloodLine.stat = "CureMisStid_Complite";
   AddLandQuestmark_Main(CharacterFromID("MisStid"), "CapBloodLine");

   QuestPointerDelLoc("Bridgetown_town", "reload", "HouseSP1");
   QuestPointerDelLoc("CommonPirateHouse", "item", "item1");
}

void CapBloodLine_q1_Complited(string qName)
{
    ref sld;
    pchar.quest.CapBloodLineTimer_1.over = "yes";
    sld = &characters[GetCharacterIndex("MisStid")];
//    sld.lifeDay = 0;
    sld.location = "none";
    sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
    sld.Dialog.CurrentNode = "First time";
    RemoveLandQuestmark_Main(sld, "CapBloodLine");
    
    int n= FindLocation("Bridgetown_town");
    locations[n].reload.l3.close_for_night = true;//закрываем резиденцию
    AddQuestRecord("CapBloodLine_q1", "9");
    CloseQuestHeader("CapBloodLine_q1");
    //LAi_Fade("", "");
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,0, 12, 0); // прошло время
    SetCurrentTime(7, 0); // должно быть 2-е число 7 часов
    bQuestCheckProcessFreeze = false;
    SetLaunchFrameFormParam(StringFromKey("InfoMessages_16"), "Reload_To_Location", 0.1, 2.0);
    SetLaunchFrameReloadLocationParam("Bridgetown_tavern", "reload","reload1", "");
	LaunchFrameForm();
	CapBloodLine_q2();
}

void CapBloodLine_q2()
{
    ref sld;
    sld = &characters[GetCharacterIndex("Waker")];
    sld.dialog.currentnode = "First time";
    Pchar.questTemp.CapBloodLine.stat = "WakerOffer";
    ChangeCharacterAddressGroup(sld, "Bridgetown_tavern_upstairs", "goto","goto1");
    LAi_SetActorTypeNoGroup(sld);
    LAi_ActorDialog(sld, pchar, "", 2.0, 0);
    AddQuestRecord("CapBloodLine_q2", "2");
    AddQuestRecord("CapBloodLine_q2", "3");
    AddLandQuestmark_Main(sld, "CapBloodLine");
    AddLandQuestmark_Main(CharacterFromID("Bridgetown_tavernkeeper"), "CapBloodLine");

    //сроки 10 часов
    PChar.quest.CapBloodLineTimer_2.win_condition.l1            = "Timer";
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.hour  = 17;
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.function = "CapBloodLine_q2_Late";

}

void CapBloodLine_q2_PrepareToEscape_AddQuestMarks()
{
    AddLandQuestmark_Main(CharacterFromID("Bridgetown_tavernkeeper"), "CapBloodLine");
    AddLandQuestmark_Main(CharacterFromID("Griffin"), "CapBloodLine");
    QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_WeaponsForEscape");
    AddLandQuestmark_Main_WithCondition(CharacterFromID("Quest_Smuggler"), "CapBloodLine", "CapBloodLine_QuestSmuggler_QuestMarkCondition");
    AddLandQuestmarkToFantoms_Main("ItemTrader", "CapBloodLine", "CapBloodLine_ItemTrader_QuestMarkCondition");

    AddLandQuestmark_Main(CharacterFromID("Volverston"), "CapBloodLine");
    AddLandQuestmark_Main(CharacterFromID("Hugtorp"), "CapBloodLine");
    AddLandQuestmark_Main(CharacterFromID("Dieke"), "CapBloodLine");
    AddLandQuestmark_Main(CharacterFromID("Ogl"), "CapBloodLine");
    if (Characters[GetCharacterIndex("Ogl")].location != "Bridgetown_plantation")
    {
        QuestPointerToLoc("Bridgetown_plantation", "reload", "houseS2");
    }
}

void Spain_spyDie(string qName)
{
    ref sld;
    sld = &characters[GetCharacterIndex("Spain_spy")];
    LAi_KillCharacter(sld);
}

ref GenerateSpainSpyByLeveling()
{
	int rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE * 0.65);
	if (rank > 7)
		rank = 7;
	bool bEquip = MOD_SKILL_ENEMY_RATE < 10;
	ref sld = GetCharacter(NPC_GenerateCharacter("Spain_spy", "officer_27", "man", "man", rank, SPAIN, 2, bEquip));
	if (MOD_SKILL_ENEMY_RATE >= 10)
	{
		FantomMakeCoolFighter(sld, 7, 30, 50, "blade6", "", 20); //только для невозможки
   		TakeItemFromCharacter(sld, "spyglass3");
	}
	else
	{
		if (MOD_SKILL_ENEMY_RATE >= 5)
		{
			ItemTakeEquip(sld, "pistol1", 1);
			ItemTakeEx(sld, "bullet,GunPowder", "" + (5+rand(5)));
		}
	}

    return sld;
}


void LoginSpain_spy(string qName)
{
    ref sld;
    sld = GenerateSpainSpyByLeveling();
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.name = FindPersonalName("Spain_spy_name");
    sld.lastname = FindPersonalName("Spain_spy_lastname");
	sld.dialog.currentnode = "First time";
	sld.city = "Bridgetown_town";
    sld.greeting = "Gr_HUNTER";
    sld.location = "none";
	LAi_SetCitizenType(sld);
	string sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_group_MoveCharacter(sld, sTemp);
    PlaceCharacter(sld, "goto", "random_must_be_near"))
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;
}

void SpainSpyAttack(string qName)
{
    LAi_Fade("", "");
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,0, 0, 10); // прошло время
    bQuestCheckProcessFreeze = false;
    AddQuestRecord("WeaponsForEscape", "8");
    LocatorReloadEnterDisable("BridgeTown_town", "houseSp2", false);
}

void _DeadSolder(string qName)
{
    PlaySound("N_fight_death");
    DoQuestFunctionDelay("DeadSolder", 1.0);
}

void DeadSolder(string qName)
{
    ref sld;
    sld = &characters[GetCharacterIndex("CPBQuest_Solder")];
    TakeItemFromCharacter(sld, FindCharacterItemByGroup(sld, BLADE_ITEM_TYPE));
    GiveItem2Character(sld, "blade6");
    LAi_KillCharacter(sld);
}

void CapBloodLine_SpainSpy_AfterFight(string qName)
{
	ref sld = CharacterFromID("Griffin");
	LAi_CharacterEnableDialog(sld);
	AddLandQuestmark_Main(sld, "CapBloodLine");
	chrDisableReloadToLocation = false;

	DoQuestFunctionDelay("Tutorial_BloodPrologue_DeadSearch", 1.0);
}

void FindMsStid_ring(string qName)
{
    AddQuestRecord("WeaponsForEscape", "14");
    RemoveLandQuestmark_Main(characterFromID("Den"), "CapBloodLine");
    RemoveLandQuestmark_Main(characterFromID("MisStid"), "CapBloodLine");
	chrDisableReloadToLocation = true;
}

void CapBloodLine_SpainSpy_AddQuestMarks()
{
    AddLandQuestmarkToFantoms_Main("soldier", "CapBloodLine", "CapBloodLine_SpainSpy_Soldier_QuestMarkCondition");
}

void CapBloodLine_SpainSpy_DelQuestMarks()
{
    RemoveLandQuestmarkToFantoms_Main("soldier", "CapBloodLine");
}

void CapBloodLine_GriffinWeapon_SkipTime()
{
    SetLaunchFrameFormParam(StringFromKey("InfoMessages_14"), "", 0.1, 2.0);
	WaitDate("", 0, 0, 0, 1, 0);
	LaunchFrameForm();
	RefreshLandTime();
	Whr_UpdateWeather();
	SetCurrentQuestMark(CharacterFromId("Griffin"));
}

void CapBloodLine_Hells_Die(string qName)
{
	pchar.quest.CapBloodLine_Hells_GriffinWeaponTaken.win_condition.l1 = "item";
	pchar.quest.CapBloodLine_Hells_GriffinWeaponTaken.win_condition.l1.item = "Griffins_Weapon";
	pchar.quest.CapBloodLine_Hells_GriffinWeaponTaken.function = "CapBloodLine_Hells_GriffinWeaponTaken";

	DoQuestFunctionDelay("Tutorial_BloodPrologue_DeadSearch", 1.0);
}

void CapBloodLine_Hells_GriffinWeaponTaken(string qName)
{
	chrDisableReloadToLocation = false;
}

ref GenerateWinterwoodByLeveling()
{
	int rank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE * 0.65);
	if (rank > 10)
		rank = 10;
	bool bEquip = MOD_SKILL_ENEMY_RATE < 10; // не экипировать только на "невозможном"
	ref sld = GetCharacter(NPC_GenerateCharacter("Winterwood", "citiz_22", "man", "man", rank, PIRATE, 3, bEquip));
	if (MOD_SKILL_ENEMY_RATE >= 10)
	{
    	FantomMakeCoolFighter(sld, 7, 25, 20, "blade10", "pistol3", 10);
   		TakeItemFromCharacter(sld, "spyglass3");
	}
	else
	{
		if (MOD_SKILL_ENEMY_RATE >= 5)
		{
			ItemTakeEquip(sld, "pistol1", 1);
			ItemTakeEx(sld, "bullet,GunPowder", "" + (5+rand(5)));
		}
	}

    return sld;
}

void LoginWinterwood()
{
    ref sld, ch, itm;
	sld = GenerateWinterwoodByLeveling();
	sld.name = FindPersonalName("Winterwood_name");
	sld.lastname = FindPersonalName("Winterwood_lastname");
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.greeting = "pirat_common";
    GiveItem2Character(sld, "HugtorpRing"); //палец
    AddMoneyToCharacter(sld, 1000);
    sld.SaveItemsForDead = true; // сохранять на трупе вещи
    sld.DontClearDead = true;
    LAi_SetCitizenType(sld);
    
    string sQuest = "WinterwoodDuel";
    pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
    pchar.quest.(sQuest).win_condition.l1.character = sld.id;
    pchar.quest.(sQuest).function= "WinterwoodDie";

    if(!rand(1))
    {
   	    LAi_SetSitTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit4");
    }
    else
    {
   	    LAi_SetStayTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, "Bridgetown_Brothel_room", "goto","goto3");
        
		ch = GetCharacter(NPC_GenerateCharacter("Qhorse", "horse99", "woman", "towngirl", 10, ENGLAND, 1, false));
		string sTemp = GetNationNameByType(ENGLAND) + "_citizens";
        LAi_group_MoveCharacter(ch, sTemp);
        LAi_SetActorTypeNoGroup(ch);
		LAi_ActorAfraid(ch, Pchar, false);
		ChangeCharacterAddressGroup(ch, "Bridgetown_Brothel_room", "goto","goto1");
		
        int n = FindLocation("Bridgetown_Brothel");
        locations[n].reload.l2.disable = false;
        
    }
    AddLandQuestmark_Main(sld, "CapBloodLine");
}

void WinterwoodDuel(string qName)
{
	pchar.quest.Winterwood2Place.win_condition.l1 = "Location";
	pchar.quest.Winterwood2Place.win_condition.l1.location = "Bridgetown_ExitTown";
	pchar.quest.Winterwood2Place.function = "Winterwood2Place";

	QuestPointerToLoc("Bridgetown_town", "reload", "gate_back");
}

void Winterwood2Place(string qName)
{
    ref sld;
    sld = characterFromID("Winterwood");
   	sld.Dialog.CurrentNode = "talk_off_town";
    if (CheckAttribute(sld, "CityType"))
	{
		DeleteAttribute(sld, "City"); // чтоб не было ругани с нацией
		DeleteAttribute(sld, "CityType");
	}
   	ChangeCharacterAddressGroup(sld, "Bridgetown_ExitTown", "goto","goto1");
   	LAi_SetStayTypeNoGroup(sld);
    LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;
}

void Winterwood_Prepare_Fight()
{
	int i, idx;
	ref npchar, rLoc;

	npchar = characterFromID("Winterwood");
	LAi_CharacterDisableDialog(NPChar); //fix
	if (CheckAttribute(pchar, "quest.CapBloodLine_WinterwoodSkipTime"))
	{
	    pchar.quest.CapBloodLine_WinterwoodSkipTime.over = "yes";
	}

	makeref(rLoc, Locations[FindLoadedLocation()]);

	if (CheckAttribute(rLoc, "type") && rLoc.type == "tavern")
	{
		if (PChar.chr_ai.type == LAI_TYPE_SIT)
		{
			LAi_SetPlayerType(pchar);
			PlaceCharacter(pchar, "tables", pchar.location);
		}
		PChar.Quest.Duel_Fight_Right_Now.win_condition.l1 = "Location";
		PChar.Quest.Duel_Fight_Right_Now.win_condition.l1.Location = "Clone_location";
		PChar.Quest.Duel_Fight_Right_Now.function = "Winterwood_Fight_Right_Now";

		LocationMakeClone(pchar.location);
		Locations[FindLocation("Clone_location")].image = "loading\tavern_fight.tga";
		DoReloadCharacterToLocation("Clone_location", pchar.location.group, pchar.location.locator);
		PlaceCharacter(npchar, "goto", "Clone_location");
	}
	else
	{
		DoQuestFunctionDelay("Winterwood_Fight_Right_Now", 0.5);
	}
	LAi_SetWarriorType(npchar);
	LAi_group_MoveCharacter(npchar, "DUEL_FIGHTER");

	PChar.quest.Winterwood_RingTaken.win_condition.l1 = "item";
	PChar.quest.Winterwood_RingTaken.win_condition.l1.item = "HugtorpRing";
	PChar.quest.Winterwood_RingTaken.function = "Winterwood_RingTaken";
}

void Winterwood_Fight_Right_Now(string qName)
{
	bool bOk = false;
	ref sld = &Locations[FindLocation(pchar.location)];

	//запоминаем запрет на оружие в локации
	if (CheckAttribute(sld, "noFight"))
	{
		bOk = sti(sld.noFight);
	}
	if (bOk)
	{
		LAi_LocationFightDisable(sld, !bOk);
		pchar.questTemp.LocFightEnable = bOk;
	}
	//достать саблю
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("DUEL_FIGHTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("DUEL_FIGHTER", LAI_GROUP_PLAYER, true);
	chrDisableReloadToLocation = true;
}

void WinterwoodDie(string qName)
{
    if (CheckAttribute(PChar, "quest.Winterwood2Place")) Pchar.quest.Winterwood2Place.over = "yes";
    if (CheckAttribute(PChar, "quest.CapBloodLineTimer_3")) Pchar.quest.CapBloodLineTimer_3.over = "yes";
    QuestPointerDelLoc("Bridgetown_town", "reload", "gate_back");

	//восстанавливаем запрет на оружие, если был
	if (CheckAttribute(pchar, "questTemp.LocFightEnable") && sti(pchar.questTemp.LocFightEnable))
	{
		ref sld = &Locations[FindLocation(pchar.location)];
		LAi_LocationFightDisable(sld, true);
		DeleteAttribute(pchar, "questTemp.LocFightEnable");
	}

	//если в локации клоне, то объясняем куда все делись
	if (CheckAttribute(pchar, "questTemp.LocationClone") && sti(pchar.questTemp.LocationClone))
	{
		DoQuestCheckDelay("TalkSelf_Start", 0.2);
	}

	//убрать оружие
	DoQuestCheckDelay("hide_weapon", 2.0);

	DoQuestFunctionDelay("Tutorial_BloodPrologue_DeadSearch", 1.0);
	LAi_group_Delete("DUEL_FIGHTER");
}

void Winterwood_RingTaken(string qName)
{
	chrDisableReloadToLocation = false;
    AddQuestRecord("HugtorpTrouble", "4");
}

void CapBloodLine_WinterwoodSkipTime(string qName)
{
	if (!CheckAttribute(pchar, "quest.CapBloodLineTimer_3") || CheckAttribute(pchar, "quest.CapBloodLineTimer_3.over") ||
		GetTime() >= 16.0)
	{
		pchar.quest.CapBloodLine_WinterwoodSkipTime.over = "yes";
		return;
	}

	ref sld = characterFromID("Dieke");

    if (CheckAttribute(pchar, "questTemp.CapBloodLine.Ogl") && sti(Pchar.questTemp.CapBloodLine.Ogl) &&
    	CheckAttribute(sld, "Dialog.CurrentNode") && sld.Dialog.CurrentNode == "DKStep_3" &&
    	Pchar.questTemp.CapBloodLine.stat == "ReadyToEscape")
	{
		pchar.quest.CapBloodLine_WinterwoodSkipTime.over = "yes";
		DoQuestFunctionDelay("CapBloodLine_WinterwoodSkipTime_LaunchForm", 1.5);
	}
}

void CapBloodLine_WinterwoodSkipTime_LaunchForm(string qName)
{
	if (procEnableInterfaceLaunch(INTERFACE_FRAMEFORM) == false)
	{
		DoQuestFunctionDelay("CapBloodLine_WinterwoodSkipTime_LaunchForm", 1.0);
		return;
	}

	SetLaunchFrameFormParam(StringFromKey("InfoMessages_14"), "Reload_To_Location", 0.1, 2.0);
	SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "");
	WaitDate("", 0, 0, 0, 1, 0);
	LaunchFrameForm();
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

void MoneyForDieke(string qName)
{
    ref sld = characterFromID("Dieke");
    sld.Dialog.CurrentNode = "DKStep_3";
    AddQuestRecord("DiekeQuest", "4");
    AddLandQuestmark_Main(sld, "CapBloodLine");
    QuestPointerDelLoc("Bridgetown_town", "reload", "houseS3");
}

void CapBloodLine_q2_Late(string qName)
{
	if (CheckAttribute(pchar, "quest.CapBloodLine_WinterwoodSkipTime"))
	{
	    pchar.quest.CapBloodLine_WinterwoodSkipTime.over = "yes";
	}

	if (procEnableInterfaceLaunch(INTERFACE_FRAMEFORM) == false)
	{
		DoQuestFunctionDelay("CapBloodLine_q2_Late", 1.0);
		return;
	}

    InterfaceStates.Buttons.Save.enable = false;
    SetLaunchFrameFormParam(StringFromKey("InfoMessages_245"), "Run_Function", 0.1, 4.0);
    SetLaunchFrameRunFunctionParam("CapBloodLine_q2_Late_GameOver", 0.0);
	LaunchFrameForm();
}

void CapBloodLine_q2_Late_GameOver()
{
    GameOver("land");
}

void CapBloodLine_q2_Complited()
{
    ref sld;
    Pchar.quest.CapBloodLineTimer_2.over = "yes";
    AddQuestRecord("CapBloodLine_q2", "6");
    int n= FindLocation("Bridgetown_tavern");
    locations[n].reload.l2.disable = false;
    sld = &characters[GetCharacterIndex("Waker")];
    sld.Dialog.CurrentNode = "WStep_11";
    LAi_SetStayTypeNoGroup(sld);
    AddLandQuestmark_Main(sld, "CapBloodLine");
    
    bQuestCheckProcessFreeze = true;
    Environment.date.day = 3;
    SetCurrentTime(7, 0); // должно быть 3-е число 7 часов
    bQuestCheckProcessFreeze = false;
    
    //Шпион
    sld = GetCharacter(NPC_GenerateCharacter("MoneySpy", "citiz_50", "man", "man", 10, ENGLAND, 1, false));
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    FantomMakeCoolFighter(sld, 10, 25, 50, "blade9", "", 10);
    TakeItemFromCharacter(sld, "spyglass3");
    sld.quest.meeting = 0;
	string sTemp = GetNationNameByType(ENGLAND) + "_citizens";
    LAi_SetOwnerType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
    sld.talker = 10; //fix
   	ChangeCharacterAddressGroup(sld, "CommonDoubleFlourHouse_1", "barmen", "stay");
    AddLandQuestmark_Main(sld, "CapBloodLine");

    //Властелин рыб
    sld = GetCharacter(NPC_GenerateCharacter("Fisherman", "worker_3", "man", "man", 10, ENGLAND, 1, false));
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    sld.name = FindPersonalName("Fisherman_name");
    sld.lastname = FindPersonalName("Fisherman_lastname");
	sld.greeting = "Gr_Fisher";
    sld.Default           = "Bridgetown_tavern";
    sld.Default.group     = "sit";
    sld.Default.ToLocator = "sit_front4";//fix
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_SetSitType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
    ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit","sit_base4"); //fix
    
    //Жак Соловей
    sld = GetCharacter(NPC_GenerateCharacter("Jack", "DSolovey", "man", "man", 10, ENGLAND, 1, false));
    sld.name = FindPersonalName("Jack_name");
    sld.lastname = FindPersonalName("Jack_lastname");
    sld.greeting = "Gr_Solovey";
    sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    FantomMakeCoolFighter(sld, 10, 25, 50, "blade7", "", 10);
    sld.dialog.currentnode = "JSTStep_0";
    sld.talker = 10;
	sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	LAi_SetStayType(sld);
    LAi_group_MoveCharacter(sld, sTemp);
    //LAi_SetOwnerTypeNoGroup(sld);
   	ChangeCharacterAddressGroup(sld, "Bridgetown_Store", "goto", "goto1");
   	AddLandQuestmark_Main(sld, "CapBloodLine");

   	sld = characterFromID("Bridgetown_trader");
   	LAi_SetLoginTime(sld, 0.0, 1.0);

    //сроки
    PChar.quest.CapBloodLineTimer_2.win_condition.l1            = "Timer";
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.hour  = 15;
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
    PChar.quest.CapBloodLineTimer_2.function = "CapBloodLine_q2_Late";

    SetLaunchFrameFormParam(StringFromKey("InfoMessages_17"), "Reload_To_Location", 0.1, 2.0);
    SetLaunchFrameReloadLocationParam("Bridgetown_Plantation_G6", "goto", "goto1", "");
   	LaunchFrameForm();
   	CapBloodLine_WeaponsForEscape_ClearQuestMarks();
   	QuestPointerToLoc("Bridgetown_town", "reload", "reload4_back");
   	QuestPointerToLoc("Bridgetown_plantation", "reload", "reload1_back");
   	QuestPointerToLoc("Bridgetown_tavern", "reload", "reload2_back");
}

void CapBloodLine_WeaponsForEscape_ClearQuestMarks()
{
    RemoveLandQuestmark_Main(characterFromID("Den"), "CapBloodLine");
    RemoveLandQuestmark_Main(characterFromID("MisStid"), "CapBloodLine");
    RemoveLandQuestmark_Main(CharacterFromID("Quest_Smuggler"), "CapBloodLine");

    RemoveLandQuestmark_Main(CharacterFromID("Griffin"), "CapBloodLine");
    QuestPointerDelLoc("Bridgetown_town", "reload", "HouseSp2");
    RemoveLandQuestmarkToFantoms_Main("soldier", "CapBloodLine");

    RemoveLandQuestmarkToFantoms_Main("ItemTrader", "CapBloodLine");

    QuestPointerDelLoc("Bridgetown_town", "reload", "reload4_back");
    QuestPointerDelLoc("Bridgetown_town", "reload", "reload8_back");
}

void CapBloodLine_NeedMoney_AddQuestMarks()
{
    AddLandQuestmark_Main(characterFromID("Bridgetown_usurer"), "CapBloodLine");
    AddLandQuestmark_Main(characterFromID("Nettl"), "CapBloodLine");
    if (GetCharacterIndex("Hells") >= 0)
    	AddLandQuestmark_Main(characterFromID("Hells"), "CapBloodLine");
}

void CapBloodLine_NeedMoney_AddQuestPointers()
{
    QuestPointerToLoc("Bridgetown_town", "reload", "reload6_back");
}

void CapBloodLine_NeedMoney_Raff_DelQuestMarks()
{
    RemoveLandQuestmark_Main(characterFromID("Bridgetown_usurer"), "CapBloodLine");
}

void CapBloodLine_NeedMoney_DenyRaff_SetQuestPointers()
{
	if (CheckAttribute(pchar, "questTemp.CapBloodLine.QuestRaff") && PChar.questTemp.CapBloodLine.QuestRaff == true)
	{
	    return;
	}

	if (CapBloodLine_NeedMoney_CheckHellsForQuest())
	{
		QuestPointerToLocEx("Bridgetown_town", "reload", "reload11_back", "BloodLine_FishermanQuest");
	}
	else
	{
		ref sld = CharacterFromID("MoneySpy");
		if (sld.quest.meeting == 0)
			QuestPointerToLocEx("Bridgetown_town", "reload", "houseS1", "BloodLine_MoneySpy");
	}
}

void CapBloodLine_NeedMoney_MoneySpy_DelQuestMarks()
{
    RemoveLandQuestmark_Main(characterFromID("MoneySpy"), "CapBloodLine");
    QuestPointerDelLoc("Bridgetown_town", "reload", "houseS1");
}

void CapBloodLine_NeedMoney_Jack_DelQuestMarks()
{
    RemoveLandQuestmark_Main(characterFromID("Jack"), "CapBloodLine");
    QuestPointerDelLoc("Bridgetown_town", "reload", "reload6_back");
}

void CapBloodLine_NeedMoney_Jack_Disappear(string qName)
{
    ref sld = characterFromID("Jack");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
}

void QUsurerLate(string qName)
{
    ChangeCharacterHunterScore(PChar, "enghunter", 30);//fix было -30;
    RemoveLandQuestmark_Main(characterFromID("Bridgetown_usurer"), "CapBloodLine");
}

void LoginMainer()
{

        Pchar.questTemp.CapBloodLine.ShipForJack = false;
		ref sld = GetCharacter(NPC_GenerateCharacter("Mainer", "citiz_5", "man", "man", 7, ENGLAND, 3, false)); //watch_quest_moment
        sld.name = FindPersonalName("Mainer_name");
        sld.lastname = FindPersonalName("Mainer_lastname");
		sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
		sld.dialog.currentnode = "MNStep_0";
		sld.city = "Bridgetown_town";
		//sld.greeting = "Gr_Tavern_Mate";
//		LAi_SetLoginTime(sld, 0.0, 23.99);
		//SetFantomParamFromRank(sld, Rank, true);
		LAi_SetCitizenType(sld);
		string sTemp = GetNationNameByType(ENGLAND) + "_citizens";
		LAi_group_MoveCharacter(sld, sTemp);
	//	sld.talker = 10;
        ChangeCharacterAddressGroup(sld, "Bridgetown_town", "reload", "reload1");
        AddLandQuestmark_Main(sld, "CapBloodLine");
}

void CapBloodLine_q3_Complited()
{
    Pchar.quest.CapBloodLineTimer_2.over = "yes";
    pchar.quest.CapBloodEscape1.win_condition.l1          = "location";
    pchar.quest.CapBloodEscape1.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodEscape1.function                  = "ReturnToPlantation1";

    //pchar.quest.CapBloodEscape2.win_condition.l1          = "location";
    //pchar.quest.CapBloodEscape2.win_condition.l1.location = "BridgeTown_Plantation";
    //pchar.quest.CapBloodEscape.function                  = "ReturnToPlantation2";

}

void CapBloodLine_NeedMoney_DelQuestMarks()
{
    RemoveLandQuestmark_Main(characterFromID("Bridgetown_usurer"), "CapBloodLine");
    RemoveLandQuestmark_Main(characterFromID("QStranger"), "CapBloodLine");
    RemoveLandQuestmark_Main(characterFromID("Bridgetown_tavernkeeper"), "CapBloodLine");
    RemoveLandQuestmark_Main(characterFromID("Bridgetown_PortMan"), "CapBloodLine");
    RemoveLandQuestmark_Main(characterFromID("Nettl"), "CapBloodLine");
    RemoveLandQuestmark_Main(characterFromID("Hells"), "CapBloodLine");
    RemoveLandQuestmark_Main(characterFromID("MoneySpy"), "CapBloodLine");
    RemoveLandQuestmark_Main(characterFromID("Fisherman"), "CapBloodLine");
}

void CapBloodLine_NeedMoney_DelQuestPointers()
{
    QuestPointerDelLoc("Bridgetown_town", "reload", "reload4_back");
    QuestPointerDelLoc("Bridgetown_town", "reload", "reload5_back");
    QuestPointerDelLoc("Bridgetown_town", "reload", "reload6_back");
    QuestPointerDelLoc("Bridgetown_town", "reload", "reload7_back");
    QuestPointerDelLoc("Bridgetown_town", "reload", "reload8_back");
    QuestPointerDelLoc("Bridgetown_town", "reload", "reload10_back");
    QuestPointerDelLoc("Bridgetown_town", "reload", "reload11_back");
    QuestPointerDelLoc("Bridgetown_town", "reload", "houseS1");

    QuestPointerDelLoc("Bridgetown_plantation", "reload", "reload1_back");
	QuestPointerDelLoc("Bridgetown_town", "reload", "gate1_back");
	QuestPointerDelLoc("Bridgetown_tavern", "reload", "reload2_back");
}

void ReturnToPlantation1(string qName)
{
    ref sld;
    sld = GetCharacter(NPC_GenerateCharacter("SolderNStep_7", "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false));
	sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
	sld.dialog.currentnode = "NStep_7";
	sld.city = "Bridgetown_town";
    sld.greeting = "Gr_HUNTER";
    sld.location = "none";
    sld.BreakTmplAndFightGroup = true;
    SetFantomParamHunter(sld); //крутые парни
	LAi_SetCitizenType(sld);
	string sTemp = GetNationNameByType(ENGLAND) + "_citizens";
	
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, sTemp);
    PlaceCharacter(sld, "goto", "random_must_be_near");
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	chrDisableReloadToLocation = true;

}

void ReturnToPlantation2(string qName)
{
    ref sld;
    sld = characterFromID("Volverston");
    sld.Dialog.CurrentNode = "VLStep_2";
    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
	
    sld = characterFromID("Pitt");
    ChangeCharacterAddressGroup(sld, "None", "", "");
	chrDisableReloadToLocation = true;
	CapBloodLine_NeedMoney_DelQuestMarks();
	CapBloodLine_NeedMoney_DelQuestPointers();
}

void ReturnToPlantation3()
{
    ref sld;
    SetLocationCapturedState("BridgeTown_Plantation", true);
    string sTemp = LAI_GROUP_TmpEnemy;
   	LAi_group_SetHearRadius(sTemp, LAI_GROUP_GRD_HEAR - 3);
   	LAi_group_SetSayRadius(sTemp, LAI_GROUP_GRD_SAY - 1);
   	LAi_group_SetLookRadius(sTemp, LAI_GROUP_GRD_LOOK - 1);
    LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_SetAlarm(sTemp, LAI_GROUP_PLAYER, 0);

    SetShipInBridgetown(); // Готовим Бриджтаун
    Pchar.questTemp.CapBUnarmed = false;

    sld = characterFromID("Volverston");
    LAi_LoginInCaptureTown(sld, true);
    LAi_SetStayTypeNoGroup(sld);
    sld.talker = 10;
    sld.Dialog.CurrentNode = "VLStep_6"; //TODO
    GiveItem2Character(sld, "topor1"); // Волверстону топор
    EquipCharacterByItem(sld, "topor1");
    TakeNItems(sld, "potion1", 5);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest3");
    AddLandQuestmark_Main(sld, "CapBloodLine");

    sld = characterFromID("Hugtorp");
    LAi_LoginInCaptureTown(sld, true);
    LAi_SetStayTypeNoGroup(sld);
    sld.Dialog.CurrentNode = "VLStep_6"; //TODO
    GiveItem2Character(sld, "blade7");
    EquipCharacterByItem(sld, "blade7");
    TakeNItems(sld, "potion1", 5);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest4");
    AddLandQuestmark_Main(sld, "CapBloodLine");

    sld = characterFromID("Ogl");
    LAi_LoginInCaptureTown(sld, true);
    sld.Dialog.CurrentNode = "VLStep_6";  //TODO
    LAi_SetStayTypeNoGroup(sld);
    GiveItem2Character(sld, "blade5"); // Оглу кинжал
    EquipCharacterByItem(sld, "blade5");
    TakeNItems(sld, "potion1", 5);
    LAi_SetImmortal(sld, false);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest5");
    AddLandQuestmark_Main(sld, "CapBloodLine");

    sld = characterFromID("Dieke");
    LAi_LoginInCaptureTown(sld, true);
    LAi_SetStayTypeNoGroup(sld);
    sld.Dialog.CurrentNode = "VLStep_6";  //TODO
    GiveItem2Character(sld, "blade7");
    EquipCharacterByItem(sld, "blade7");
    TakeNItems(sld, "potion1", 5);
    LAi_SetImmortal(sld, false);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest6");
    AddLandQuestmark_Main(sld, "CapBloodLine");
    
    sld = characterFromID("Pitt");
    LAi_LoginInCaptureTown(sld, true);
    LAi_SetActorType(sld);
    LAi_ActorSetLayMode(sld);
    ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "quest", "sit2");

    worldMap.date.day = 4;
    Environment.date.day = 4;
    SetCurrentTime(0, 0);

    int n = FindLocation("BridgeTown_Plantation");
    DeleteAttribute(&locations[n], "citizens");
    DeleteAttribute(&locations[n], "carrier");
    
    DoReloadCharacterToLocation("BridgeTown_Plantation", "reload", "reload1_back");
    SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
    
    for (int i=0; i < 7; i++)
	{
        if(i < 2)
        {
            sld = GetCharacter(NPC_GenerateCharacter("PittGuard_"+i, "sold_eng_"+(rand(7)+1), "man", "man", 10, ENGLAND, 0, false));
            SetFantomParamFromRank(sld, sti(pchar.rank)+CapBloodLine_GetEngGuardAddRank(), true); // бравые орлы
            LAi_LoginInCaptureTown(sld, true);
            LAi_SetActorType(sld); // послабление
			// LAi_SetStayType(sld); // fix анимки страха
            LAi_group_MoveCharacter(sld, sTemp);
    		//LAi_SetGuardianTypeNoGroup(sld);
            ChangeCharacterAddressGroup(sld, "BridgeTown_Plantation", "quest", "sit"+(2*i+1));
        }
        else
        {
            int iChar = NPC_GeneratePhantomCharacter("milit_sold", ENGLAND, MAN, 2);
            sld = &characters[iChar];
    		SetNPCModelUniq(sld, "milit_sold", MAN);
    		sld.City = "Bridgetown";
            sld.CityType = "soldier";
            SetFantomParamFromRank(sld, sti(pchar.rank)+CapBloodLine_GetEngGuardAddRank(), true);
            LAi_LoginInCaptureTown(sld, true);
           	LAi_SetWarriorType(sld);
    		LAi_SetPatrolType(sld);
            LAi_group_MoveCharacter(sld, sTemp);
    		PlaceCharacter(sld, "patrol", "random_free");
        }
        LAi_SetLoginTime(sld, 0.0, 24.0);
        sld.greeting = "soldier_common";
        sld.dialog.filename = "Common_Soldier.c";
        sld.dialog.currentnode = "first time";
	}

	ref rLoc = &locations[FindLocation("BridgeTown_Plantation")];
	float questLocRad = 3.0;
	TEV.CapBloodLine_EscapePlantation_QuestLocRadius = rLoc.locators_radius.quest;
	rLoc.locators_radius.quest.stay1 = questLocRad;
	//	SetLocatorRadius(rLoc, "quest", "stay1", questLocRad);
	//  SendMessage(rLoc, "l", MSG_LOCATION_UPDATELOCATORS);
	pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation.win_condition.l1 = "locator";
    pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation.win_condition.l1.location = "BridgeTown_Plantation";
    pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation.win_condition.l1.locator_group = "quest";
    pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation.win_condition.l1.locator = "stay1";
    pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation.function = "CapBloodLine_ReachQuestPointer_EscapePlantation";

    //pchar.GenQuestBox.BridgeTown_Plantation.stay = true; fix
    pchar.GenQuestBox.BridgeTown_Plantation.box1.items.blade6 = 1;
    pchar.GenQuestBox.BridgeTown_Plantation.box1.items.potion2 = 10;
    
   	pchar.quest.CapBloodEscape3.win_condition.l1 = "locator";
	pchar.quest.CapBloodEscape3.win_condition.l1.location = "BridgeTown_Plantation";
	pchar.quest.CapBloodEscape3.win_condition.l1.locator_group = "quest";
	pchar.quest.CapBloodEscape3.win_condition.l1.locator = "detector1";
	pchar.quest.CapBloodEscape3.function = "ReturnToPlantation4";
    
    chrDisableReloadToLocation = true;

    //int n = FindLocation("BridgeTown_Plantation");
    //DeleteAttribute(&locations[n], "citizens");

	CapBloodLine_NeedToSavePitt();
	// временный фикс - хз, но почему-то слетают отношения между актерами ==>
	LAi_group_SetRelation(LAI_GROUP_ACTOR, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetAlarmReaction(LAI_GROUP_ACTOR, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL, LAI_GROUP_NEITRAL);
	// <==
}

void CapBloodLine_NeedToSavePitt()
{
	StartQuestMovie(true, false, true);
	LAi_FadeEx(0.0, 1.5, 1.0, "", "CapBloodLine_NeedToSavePitt_1", "");
	LAi_SetActorType(pchar);
	locCameraFlyToPositionLookToPoint(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 100/GetDeltaTime()); // Сейчас есть баг, и эта камера временная, пока не решим
	Pchar.FuncCameraFly = "";
}

void CapBloodLine_NeedToSavePitt_1(string qName)
{
	locCameraFlyToPositionLookToPoint(-6.29, 3.69, 77.79, -1.51, 3.48, 79.04, 7.46, 3.14, 81.43, -1.0, 5000/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_NeedToSavePitt_2";
}

void CapBloodLine_NeedToSavePitt_2()
{
	locCameraFlyToPositionLookToPoint(21.62, 3.72, 102.83, 22.02, 3.19, 104.60, 22.74, 2.19, 107.79, -1.0, 6000/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_NeedToSavePitt_3";
}

void CapBloodLine_NeedToSavePitt_3()
{
	locCameraFlyToPositionLookToPoint(49.70, 2.91, 99.32, 50.53, 2.83, 101.32, 52.08, 2.68, 105.07, -1.0, 3000/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_NeedToSavePitt_4";
}

void CapBloodLine_NeedToSavePitt_4()
{
	locCameraFlyToPositionLookToPoint(57.50, 2.70, 118.63, 57.74, 3.34, 113.18, 57.89, 1.74, 111.39, -1.0, 7000/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_NeedToSavePitt_5";
}

void CapBloodLine_NeedToSavePitt_5()
{
	locCameraSleep(true);
	DoQuestFunctionDelay("CapBloodLine_NeedToSavePitt_6", 1.5);
}

void CapBloodLine_NeedToSavePitt_6(string qName)
{
	LAi_FadeEx(1.0, 1.0, 1.0, "CapBloodLine_NeedToSavePitt_7", "CapBloodLine_NeedToSavePitt_8", "");
}

void CapBloodLine_NeedToSavePitt_7(string qName)
{
	EndQuestMovie();
	locCameraSleep(false);
	locCameraFollowEx(true);
}

void CapBloodLine_NeedToSavePitt_8(string qName)
{
	LAi_SetPlayerType(pchar);
	QuestPointerToLoc("BridgeTown_Plantation", "quest", "stay1");
}

void ReturnToPlantation4(string qName)
{
    ref sld;
    string sTemp = LAI_GROUP_TmpEnemy;
   	LAi_group_SetHearRadius(sTemp, 3); // послабление
   	LAi_group_SetSayRadius(sTemp, 4);
   	LAi_group_SetLookRadius(sTemp, 5);
    for (int i = 0 ; i < 2; i++)
    {
        sld = characterFromID("PittGuard_"+i);
        LAi_SetWarriorTypeNoGroup(sld);
        LAi_group_Attack(sld, Pchar);
    }
    sld = characterFromID("Pitt");
    sld.Dialog.CurrentNode = "PStep_11";
    LAi_SetGroundSitTypeNoGroup(sld);
    AddLandQuestmark_Main(sld, "CapBloodLine");
    SetLocationCapturedState("Bridgetown_town", true);
    pchar.quest.CapBloodEscape4.win_condition.l1          = "location";
    pchar.quest.CapBloodEscape4.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodEscape4.function                  = "StillShip";

    CapBloodLine_ReachQuestPointer_EscapePlantation_ClearAll();
}

void CapBloodLine_ReachQuestPointer_EscapePlantation(string qName)
{
    QuestPointerDelLoc("BridgeTown_Plantation", "quest", "stay1");
    QuestPointerToLoc("BridgeTown_Plantation", "box", "box1");

	pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation1.win_condition.l1 = "locator";
    pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation1.win_condition.l1.location = "BridgeTown_Plantation";
    pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation1.win_condition.l1.locator_group = "box";
    pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation1.win_condition.l1.locator = "box1";
    pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation1.function = "CapBloodLine_ReachQuestPointer_EscapePlantation1";
}

void CapBloodLine_ReachQuestPointer_EscapePlantation1(string qName)
{
    QuestPointerDelLoc("BridgeTown_Plantation", "box", "box1");
    QuestPointerToLoc("BridgeTown_Plantation", "quest", "detector1");

    // Снимем в ReturnToPlantation4
}

void CapBloodLine_ReachQuestPointer_EscapePlantation_ClearAll()
{
	if (CheckAttribute(PChar, "quest.CapBloodLine_ReachQuestPointer_EscapePlantation")) Pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation.over = "yes";
	if (CheckAttribute(PChar, "quest.CapBloodLine_ReachQuestPointer_EscapePlantation1")) Pchar.quest.CapBloodLine_ReachQuestPointer_EscapePlantation1.over = "yes";

	QuestPointerDelLoc("BridgeTown_Plantation", "quest", "stay1");
    QuestPointerDelLoc("BridgeTown_Plantation", "box", "box1");
    QuestPointerDelLoc("BridgeTown_Plantation", "quest", "detector1");
    QuestPointerDelLoc("BridgeTown_Plantation", "reload", "reload1_back");

	if (CheckAttribute(&TEV, "CapBloodLine_EscapePlantation_QuestLocRadius"))
	{
		ref rLoc = &locations[FindLocation("BridgeTown_Plantation")];
		float restoreRad = stf(TEV.CapBloodLine_EscapePlantation_QuestLocRadius);
		rLoc.locators_radius.quest.stay1 = restoreRad;

		DeleteAttribute(&TEV, "CapBloodLine_EscapePlantation_QuestLocRadius");
	}
}

void StillShip(string qName)
{
    //SetCurrentTime(2, 0);
    // снимем после диалога со служанкой
    chrDisableReloadToLocation = true;

    ref chr,sld ;
    aref st;
    int iNation = SPAIN;
	string slai_group, locatorName, sType, slocator;

    slai_group = LAI_GROUP_TmpEnemy;
   	LAi_group_SetHearRadius(slai_group, LAI_GROUP_GRD_HEAR - 3);
   	LAi_group_SetSayRadius(slai_group, LAI_GROUP_GRD_SAY - 1);
   	LAi_group_SetLookRadius(slai_group, LAI_GROUP_GRD_LOOK - 1);

    int spaSoldierQty = 7 + makeint((MOD_SKILL_ENEMY_RATE - 1) / 2); // 7..11
    Restrictor(&spaSoldierQty, 7, 11);
	for (int i = 0; i < spaSoldierQty; i++)
	{
        chr = GetCharacter(NPC_GenerateCharacter("SpaSolder_"+i, "sold_spa_"+(rand(7)+1), "man", "man", sti(pchar.rank)+CapBloodLine_GetSpaSoldierAddRank(), SPAIN, 1, false));
		chr.City = "Bridgetown";
        chr.CityType = "soldier";
        SetFantomParamFromRank(chr, sti(pchar.rank)+CapBloodLine_GetSpaSoldierAddRank(), true); // бравые орлы
		LAi_LoginInCaptureTown(chr, true);
        LAi_SetLoginTime(chr, 0.0, 24.0);
       	LAi_SetWarriorType(chr);
		LAi_warrior_DialogEnable(chr, false);
		LAi_group_MoveCharacter(chr, slai_group);
		chr.greeting = "soldier_common";
		slocator = PlaceCharacter(chr, "patrol", "random_free");
		while( slocator == "patrol13")  // слишком близко к воротам
		{
            slocator = PlaceCharacter(chr, "patrol", "random_free");
		}
        chr.dialog.filename = "Common_Soldier.c";
        chr.dialog.currentnode = "first time";
	}
	sld = GetCharacter(NPC_GenerateCharacter("SpaRaider", "off_spa_4", "man", "man", 10, SPAIN, 1, false));
	// послабление
	if (MOD_SKILL_ENEMY_RATE >= 10)
	{
		FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 25, 20, "blade22", "pistol2", 10);
    	TakeItemFromCharacter(sld, "spyglass3");
	}
	else
	{
		SetFantomParamFromRank(chr, sti(pchar.rank) + makeint(MOD_SKILL_ENEMY_RATE*0.65), false);

		ItemTakeEquip(sld, "blade22,pistol2", 1);
		ItemTakeEx(sld, "bullet,GunPowder", "" + (5 + makeint(MOD_SKILL_ENEMY_RATE / 2)));
		ItemTakeEx(sld, "potion1,potion2", "" + (1 + makeint(MOD_SKILL_ENEMY_RATE / 3)) + "," + (makeint(MOD_SKILL_ENEMY_RATE / 4)));
	}
    sld.SaveItemsForDead = true; // сохранять на трупе вещи
    sld.DontClearDead = true;
    sld.BreakTmplAndFight = true;
	LAi_LoginInCaptureTown(sld, true);
    LAi_SetLoginTime(chr, 0.0, 24.0);
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, slai_group);
	sld.greeting = "soldier_common";
    sld.dialog.filename = "Common_Soldier.c";
    sld.dialog.currentnode = "first time";
	sld.City = "Bridgetown";
    sld.CityType = "soldier";
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "reload", "houseF2");
    
    string sQuest = "SaveArabelaService";
    pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
    pchar.quest.(sQuest).win_condition.l1.character = sld.id;
    pchar.quest.(sQuest).function= "SaveArabelaService";
    
	chr = GetCharacter(NPC_GenerateCharacter("ArabelaService", "women_8", "woman", "towngirl", 10, ENGLAND, 1, false));
	chr.greeting = "Enc_RapersGirl_1";
    chr.dialog.filename = "Quest\CapBloodLine\questNPC.c";
    chr.dialog.currentnode = "ASStep_0";
//    LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER_OWN);
    LAi_SetActorType(chr);
   	LAi_LoginInCaptureTown(chr, true);
    LAi_SetLoginTime(chr, 0.0, 24.0);
    ChangeCharacterAddressGroup(chr, "Bridgetown_town", "officers", "houseH1_2");

    
	LAi_ActorRunToLocator(chr, "officers", "gate1_3", "SaveArabelaServiceAfraid", 5);
    LAi_ActorFollow(sld, chr, "", -1);
	DoQuestFunctionDelay("Tutorial_BloodPrologue_StartBarbadosFightTutorials", 5.0);
	
	ShipGuards();
	
	Pchar.questTemp.CapBloodLine.SpainInBridgetown = false;
	Pchar.questTemp.CapBloodLine.withCrew = false;
	
	LocatorReloadEnterDisable("BridgeTown_town", "reload5_back", true);
	LocatorReloadEnterDisable("BridgeTown_town", "reloadShip", true);
	
    Colonies[FindColony("Bridgetown")].DontSetShipInPort = true;
    sld = characterFromID("Bridgetown Fort Commander");
    sld.Fort.Mode = FORT_DEAD;
	// data of frot die
	sld.Fort.DieTime.Year = GetDataYear();
	sld.Fort.DieTime.Month = GetDataMonth();
	sld.Fort.DieTime.Day = GetDataDay();
	sld.Fort.DieTime.Time = GetTime();
	Event(FORT_DESTROYED, "l", sti(sld.index));

	// очистим метки с плантации
	CapBloodLine_ReachQuestPointer_EscapePlantation_ClearAll();

	// установка ограничителя для кат-сцены
	CapBloodLine_PrepareShipTakeGate();
}

void CapBloodLine_PrepareShipTakeGate()
{
	ref rLoc = loadedLocation;
	int questLocRad = 2.0;
	rLoc.locators_radius.quest.quest13 = questLocRad;
	SetLocatorRadius(rLoc, "quest", "quest13", questLocRad);
  	SendMessage(rLoc, "l", MSG_LOCATION_UPDATELOCATORS);

	pchar.quest.CapBloodLine_ShipTakeGate.win_condition.l1 = "locator";
	pchar.quest.CapBloodLine_ShipTakeGate.win_condition.l1.location = "Bridgetown_town";
	pchar.quest.CapBloodLine_ShipTakeGate.win_condition.l1.locator_group = "quest";
	pchar.quest.CapBloodLine_ShipTakeGate.win_condition.l1.locator = "quest13";
	pchar.quest.CapBloodLine_ShipTakeGate.function = "CapBloodLine_ShipTakeGate_GoAway";
}

void ShipGuards()
{
    ref chr,sld;
    string slai_group = "EnemyFight";
    int iChar, i;
	ref location;
	string boxId = "box1";
	string rldLocator;

    LAi_group_Delete(slai_group); // fix
	
	arrayNPCModelHow = 0;
	// гварды на палубе
	for (i = 0; i < 4; i++)
	{
		if (i == 0)
        {
			chr = GetCharacter(NPC_GenerateCharacter("ShipGuard_"+i, "navy_mush_spa_5", "man", "mushketer", 10, SPAIN, -1, false));
			rldLocator = "aloc7";
        }
        else
		{
			chr = GetCharacter(NPC_GenerateCharacter("ShipGuard_"+i, "navy_spa_"+(rand(7)+1), "man", "man", 10, SPAIN, -1, false));
			rldLocator = "aloc"+i;
		}
		SetFantomParamFromRank(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, true); // бравые орлы
		LAi_SetImmortal(chr, true); //homo в одиночку ГГ не справится ;-)
		LAi_LoginInCaptureTown(chr, true);
		LAi_SetLoginTime(chr, 0.0, 24.0);
		LAi_SetActorTypeNoGroup(chr);
		LAi_ActorStay(chr);
		LAi_group_MoveCharacter(chr, slai_group);
		ChangeCharacterAddressGroup(chr, "Bridgetown_town", "rld", rldLocator);
    }
    // <--
	// гварды в трюме
	for (i = 0; i < 6; i++)
	{
		if (i == 0)
        {
			chr = GetCharacter(NPC_GenerateCharacter("ShipGuardStore_"+i, "navy_off_spa_2", "man", "man", 10, SPAIN, -1, false));
        }
        else
		{
			chr = GetCharacter(NPC_GenerateCharacter("ShipGuardStore_"+i, "navy_spa_"+(rand(7)+9), "man", "man", 10, SPAIN, -1, false));
		}
		SetFantomParamFromRank(chr, sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE/2), true);
		LAi_LoginInCaptureTown(chr, true);
		LAi_SetLoginTime(chr, 0.0, 24.0);
		LAi_SetActorTypeNoGroup(chr);
		LAi_ActorStay(chr);
		LAi_group_MoveCharacter(chr, slai_group);
		ChangeCharacterAddressGroup(chr, "none", "", "");
    }
    // <--
	for (i = 1; i <= 3; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("FreeSlave_"+i, "slave_"+(rand(8)+1), "man", "man", 10, SPAIN, -1, false));
		// статичная модель для FreeSlave_1 - белый раб
		if (i == 1)
		{
			sld.model = "slave_6";
			FaceMaker(sld);
		}
		else
		{
			SetNPCModelUniq(sld, "convict", MAN);
		}
		SetFantomParamFromRank(sld, sti(pchar.rank)+makeint(2*MOD_SKILL_ENEMY_RATE/3), true); // бравые орлы
		sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
		LAi_LoginInCaptureTown(sld, true);
		LAi_SetActorType(sld);
		LAi_ActorStay(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest"+(7+(i-1)));
    }
	sld = GetCharacter(NPC_GenerateCharacter("SandroNew", "Sandro_Thorne_6", "man", "man", 10, SPAIN, -1, false)); // Сандро Торн в обносках
	SetFantomParamFromRank(sld, sti(pchar.rank)+makeint(2*MOD_SKILL_ENEMY_RATE/3), true);
	sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
	LAi_LoginInCaptureTown(sld, true);
    LAi_SetActorType(sld);
	LAi_ActorStay(sld);
    LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
    ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest9");

    sld = GetCharacter(NPC_GenerateCharacter("SpaFirstMate", "off_spa_5", "man", "man", sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE*0.65), SPAIN, -1, false));
	// послабление
	if (MOD_SKILL_ENEMY_RATE >= 10)
	{
		FantomMakeCoolFighter(sld, 12, 30, 30, "blade30", "pistol3", 10);
    	TakeItemFromCharacter(sld, "spyglass3");
	}
	else
	{
		SetFantomParamFromRank(chr, sti(pchar.rank)+makeint(MOD_SKILL_ENEMY_RATE*0.65), false);

		ItemTakeEquip(sld, "blade30,pistol3", 1);
		ItemTakeEx(sld, "grapeshot,GunPowder", "" + (5 + makeint(MOD_SKILL_ENEMY_RATE / 2)));
		ItemTakeEx(sld, "potion1,potion2", "" + (1 + makeint(MOD_SKILL_ENEMY_RATE / 3)) + "," + (makeint(MOD_SKILL_ENEMY_RATE / 4)));
	}
	LAi_LoginInCaptureTown(sld, true);
	//LAi_group_MoveCharacter(sld, slai_group); fix
    LAi_SetWarriorType(sld);
    ChangeCharacterAddressGroup(sld, "Cabin_Quest", "goto", "goto2");
    pchar.quest.SpaFirstMateDie.win_condition.l1 = "NPC_death";
    pchar.quest.SpaFirstMateDie.win_condition.l1.character = "SpaFirstMate";
   	pchar.quest.SpaFirstMateDie.function = "SpaFirstMateDie";

	location = &Locations[FindLocation("Cabin_Quest")];
	location.(boxId).money = 11500 * MOD_SKILL_ENEMY_RATE + rand(3000) + 250; //награда за сложность
	location.(boxId).items.chest = 4;
	location.(boxId) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
}

void SaveArabelaService(string qName)
{
    ref sld;
    sld = characterFromID("ArabelaService");

	LAi_SetActorType(pchar);
	LAi_ActorWaitDialog(pchar, sld);
	SetBan("Looting", 1); // бан на лутинг, чтобы не рвать скрипт диалога

    LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "",  -1.0, 0);

	sld = characterFromID("Volverston");
	sld.talker = 10;
}

void CapBloodLine_Escape_SetQuestPointers()
{
	//увеличиваем радиус квест локаторов, потом сбросим
	ref rLoc = loadedLocation;
	float questLocRad = 3.0;
	TEV.CapBloodLine_Escape_QuestLocRadius = rLoc.locators_radius.quest;
	rLoc.locators_radius.quest.quest1 = questLocRad;
	rLoc.locators_radius.quest.quest2 = questLocRad;
	SetLocatorRadius(rLoc, "quest", "quest1", questLocRad);
	SetLocatorRadius(rLoc, "quest", "quest2", questLocRad);
	SendMessage(rLoc, "l", MSG_LOCATION_UPDATELOCATORS);

	// ведём до наших коммандос
	QuestPointerToLoc("Bridgetown_town", "quest", "quest1");
	pchar.quest.CapBloodLine_ReachQuestPointer_Escape.win_condition.l1 = "locator";
	pchar.quest.CapBloodLine_ReachQuestPointer_Escape.win_condition.l1.location = "Bridgetown_town";
	pchar.quest.CapBloodLine_ReachQuestPointer_Escape.win_condition.l1.locator_group = "quest";
	pchar.quest.CapBloodLine_ReachQuestPointer_Escape.win_condition.l1.locator = "quest1";
	pchar.quest.CapBloodLine_ReachQuestPointer_Escape.function = "CapBloodLine_ReachQuestPointer_Escape";
}

void CapBloodOfficers()
{
	LAi_SetActorType(pchar);
	LAi_ActorStay(pchar);
	SendMessage(pchar, "ls", MSG_CHARACTER_EX_MSG, "StopSprint"); // fix

	DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_Init", 1.0);
}

void CapBloodLine_ReachQuestPointer_Escape(string qName)
{
    QuestPointerDelLoc("Bridgetown_town", "quest", "quest1");
    QuestPointerToLoc("Bridgetown_town", "quest", "quest2");

	pchar.quest.CapBloodLine_ReachQuestPointer_Escape1.win_condition.l1 = "locator";
    pchar.quest.CapBloodLine_ReachQuestPointer_Escape1.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodLine_ReachQuestPointer_Escape1.win_condition.l1.locator_group = "quest";
    pchar.quest.CapBloodLine_ReachQuestPointer_Escape1.win_condition.l1.locator = "quest2";
    pchar.quest.CapBloodLine_ReachQuestPointer_Escape1.function = "CapBloodLine_ReachQuestPointer_Escape1";
}

void CapBloodLine_ReachQuestPointer_Escape1(string qName)
{
    QuestPointerDelLoc("Bridgetown_town", "quest", "quest2");
    QuestPointerToLoc("Bridgetown_town", "quest", "quest3");
}

void CapBloodLine_ReachQuestPointer_Escape_ClearAll()
{
	pchar.quest.CapBloodLine_ReachQuestPointer_Escape.over = "yes";
	pchar.quest.CapBloodLine_ReachQuestPointer_Escape1.over = "yes";

	QuestPointerDelLoc("Bridgetown_town", "quest", "quest1");
    QuestPointerDelLoc("Bridgetown_town", "quest", "quest2");
    QuestPointerDelLoc("Bridgetown_town", "quest", "quest3");

    if (CheckAttribute(&TEV, "CapBloodLine_Escape_QuestLocRadius"))
	{
		ref rLoc = &locations[FindLocation("Bridgetown_town")];
		float restoreRad = stf(TEV.CapBloodLine_Escape_QuestLocRadius);
		rLoc.locators_radius.quest.quest1 = restoreRad;
		rLoc.locators_radius.quest.quest2 = restoreRad;

		DeleteAttribute(&TEV, "CapBloodLine_Escape_QuestLocRadius");
	}
}

void CapBloodLine_ShipTakeGate_GoAway(string qName)
{
	if (CheckAttribute(Pchar, "questTemp.CapBloodLine.withCrew") && sti(Pchar.questTemp.CapBloodLine.withCrew) == true)
	{
	    return;
	}

	LAi_SetFightMode(pchar, false);
	LAi_SetActorType(pchar);
	LAi_ActorRunToLocator(pchar, "quest", "quest14", "CapBloodLine_ShipTakeGate_Reset", -1);

	Notification(StringFromKey("InfoMessages_246"), "none");
}

void CapBloodLine_ShipTakeGate_Reset()
{
	if (CheckAttribute(pchar, "quest.CapBloodLine_ShipTakeGate.over"))
	{
	    DeleteAttribute(pchar, "quest.CapBloodLine_ShipTakeGate.over");
	}

	pchar.quest.CapBloodLine_ShipTakeGate.win_condition.l1 = "locator";
	pchar.quest.CapBloodLine_ShipTakeGate.win_condition.l1.location = "Bridgetown_town";
	pchar.quest.CapBloodLine_ShipTakeGate.win_condition.l1.locator_group = "quest";
	pchar.quest.CapBloodLine_ShipTakeGate.win_condition.l1.locator = "quest13";
	pchar.quest.CapBloodLine_ShipTakeGate.function = "CapBloodLine_ShipTakeGate_GoAway";

	LAi_SetPlayerType(pchar);
}

void CapBloodLine_ArabellaShipTakeScene_RemoveSpaSoldiers()
{
	string offName;
    ref sld;
    int i, iChar;
    for (i=0; i < 13; i++)
	{

    	offName = "SpaSolder_"+i;
		switch(i)
        {
            case 11:
                offName ="SpaRaider";
            break;

            case 12:
                offName ="ArabelaService";
            break;

        }
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
            sld.lifeDay = 0;
            ChangeCharacterAddressGroup(sld, "none", "", "");
        }
    }
}

void CapBloodLine_ArabellaShipTakeScene_PrepareOurCrew()
{
	string offName, rldLoc = "quest17";
    ref sld;
    int iChar;
    Pchar.questTemp.CapBloodLine.withCrew = true;

	LAi_SetActorType(pchar);
    ChangeCharacterAddressGroup(pchar, "Bridgetown_town", "quest", rldLoc);
    LAi_ActorGoToLocator(pchar, "quest", "quest14", "", -1);
    Pchar.SwordTakeOutSilent = true; // достаём оружие бесшумно
    rldLoc = "quest18";
    for (int i = 1; i <= 7; i++)
    {
        if (i > 4)
		{
			offName = "FreeSlave_"+(i-4);
		}

        switch(i)
        {
            case 1:
                offName ="Volverston";
            break;

            case 2:
                offName ="Hugtorp";
            break;

            case 3:
                offName ="Dieke";
            break;

            case 4:
                offName ="Ogl";
            break;
        }
		iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
			LAi_SetImmortal(sld, false);
			sld.DontClearDead = true;  // не убирать труп
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld.Dialog.CurrentNode = "VLStep_10b";  //
			sld.SwordTakeOutSilent = true; // достаём оружие бесшумно
			if (i <= 4)
			{
				LAi_SetRolyPoly(sld, true); //неваляхи бладовцы
			}
			RemoveLandQuestmark_Main(sld, "CapBloodLine");
			ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", rldLoc);
        }
    }
}

void CapBloodLine_ArabellaShipTakeScene_Init(string qName)
{
	pchar.quest.CapBloodLine_ShipTakeGate.over = "yes";
	pchar.quest.SaveArabelaService.over = "yes"; //fix

	StartQuestMovie(true, false, true);
	LAi_FadeEx(0.0, 1.5, 1.0, "", "CapBloodLine_ArabellaShipTakeScene_1", "");
	locCameraFlyToPositionLookToPoint(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 100/GetDeltaTime()); // Сейчас есть баг, и эта камера временная, пока не решим
	Pchar.FuncCameraFly = "";

	CapBloodLine_ArabellaShipTakeScene_RemoveSpaSoldiers();
	CapBloodLine_ArabellaShipTakeScene_PrepareOurCrew();
}

void CapBloodLine_ArabellaShipTakeScene_1(string qName)
{
	locCameraFlyToPositionLookToPoint(-17.269, 2.89, 66.596, 12.67, 8.308, 131.08, -30.7, 1.0, -18.19, -1.0, 9000/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_ArabellaShipTakeScene_2";

	DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_1_1", 3.5);
	DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_1_2", 8.0);
}

void CapBloodLine_ArabellaShipTakeScene_1_1(string qName)
{
	ref sld;

	sld = CharacterFromID("ShipGuard_1");
	LAi_SetImmortal(sld, false);
	TeleportCharacterToLocator(sld, "rld", "aloc14");
	LAi_ActorGoToLocator(sld, "rld", "aloc5", "", -1.0);

	sld = CharacterFromID("ShipGuard_0");
	LAi_SetImmortal(sld, false);
	TeleportCharacterToLocator(sld, "rld", "aloc7");
	LAi_ActorGoToLocator(sld, "rld", "aloc1", "", -1.0);
}

void CapBloodLine_ArabellaShipTakeScene_1_2(string qName)
{
	ref sld;

	sld = CharacterFromID("ShipGuard_1");
	LAi_type_actor_Reset(sld);
	TeleportCharacterToLocator(sld, "rld", "aloc5");
	LAi_ActorGoToLocator(sld, "rld", "aloc14", "", -1.0);

	sld = CharacterFromID("ShipGuard_0");
	LAi_type_actor_Reset(sld);
	TeleportCharacterToLocator(sld, "rld", "aloc1");
	LAi_ActorGoToLocator(sld, "rld", "aloc7", "", -1.0);
}

void CapBloodLine_ArabellaShipTakeScene_2()
{
	LAi_FadeEx(0.0, 1.5, 1.0, "CapBloodLine_ArabellaShipTakeScene_2_1", "CapBloodLine_ArabellaShipTakeScene_3", "");
	CapBloodLine_ArabellaShipTakeScene_OurCrewDisappear();
}

void CapBloodLine_ArabellaShipTakeScene_2_1(string qName)
{
	ref sld;

	sld = CharacterFromID("ShipGuard_2");
	LAi_SetImmortal(sld, false);
	TeleportCharacterToLocator(sld, "rld", "aloc2");

	sld = CharacterFromID("ShipGuard_3");
	LAi_SetImmortal(sld, false);
	TeleportCharacterToLocator(sld, "rld", "aloc3");

	DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_2_2", 1.0);
}
void CapBloodLine_ArabellaShipTakeScene_2_2(string qName)
{
	DoQuestFunctionDelay("CBL_AST_crewman1", 0.5);
	DoQuestFunctionDelay("CBL_AST_crewman2", 0.5);
	DoQuestFunctionDelay("CBL_AST_crewman3", 0.5);
	DoQuestFunctionDelay("CBL_AST_crewman4", 0.5);
	DoQuestFunctionDelay("CBL_AST_crewman5", 1.0);
}

void CapBloodLine_ArabellaShipTakeScene_Guard23_Patrol(string qName)
{
	ref sld;

	sld = CharacterFromID("ShipGuard_2");
	LAi_ActorGoToLocator(sld, "rld", "aloc6", "", -1.0);

	sld = CharacterFromID("ShipGuard_3");
	LAi_ActorGoToLocator(sld, "rld", "aloc4", "", -1.0);
}

void CapBloodLine_ArabellaShipTakeScene_OurCrewDisappear()
{
	string offName, rldLoc = "quest17";
    ref sld;
    int iChar;

	// Сандро удалим чтобы не мешался
  	iChar = GetCharacterIndex("SandroNew");
	if (iChar != -1)
	{
		sld = &characters[iChar];
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld.lifeday = 0;
	}

    for (int i = 1; i <= 7; i++)
    {
        if (i > 4)
		{
			offName = "FreeSlave_"+(i-4);
		}

        switch(i)
        {
            case 1:
                offName ="Volverston";
            break;

            case 2:
                offName ="Hugtorp";
            break;

            case 3:
                offName ="Dieke";
            break;

            case 4:
                offName ="Ogl";
            break;
        }
		iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
            LAi_SetActorType(pchar);
			LAi_SetActorReplaceWalkOnFightAnimation(sld);
			TeleportCharacterToLocator(sld, "quest", "quest4");
            LAi_type_actor_Reset(sld);
			LAi_ActorAnimation(sld, "CBL_Normal_to_fight_fast", "", -1);
        }
    }

	LAi_SetActorType(pchar);
	LAi_SetActorReplaceWalkOnFightAnimation(pchar);
	TeleportCharacterToLocator(pchar, "quest", "quest12");
	LAi_type_actor_Reset(pchar);
	LAi_ActorAnimation(pchar, "CBL_Normal_to_fight_fast", "", -1);
}

void CBL_AST_crewman1(string qName)
{
    TeleportCharacterToLocator(pchar, "rld", "aloc5");
	LAi_type_actor_Reset(pchar);
	LAi_ActorFollow(pchar, CharacterFromID("ShipGuard_2"), "CBL_AST_crewman1_Reached", 10.0);
}

void CBL_AST_crewman2(string qName)
{
	ref sld;

	sld = CharacterFromID("Hugtorp");
	TeleportCharacterToLocator(sld, "rld", "aloc1");
	LAi_type_actor_Reset(sld);
	LAi_ActorFollow(sld, CharacterFromID("ShipGuard_3"), "CBL_AST_crewman2_Reached", 10.0);
}

void CBL_AST_crewman3(string qName)
{
	ref sld;

	sld = CharacterFromID("Ogl");
	TeleportCharacterToLocator(sld, "quest", "quest15");
	LAi_type_actor_Reset(sld);
	LAi_ActorGoToLocator(sld, "rld", "aloc0", "CBL_AST_crewman3_Reached", 15.0);
}

void CBL_AST_crewman4(string qName)
{
	ref sld;

	sld = CharacterFromID("FreeSlave_1");
	TeleportCharacterToLocator(sld, "quest", "quest19");
	LAi_type_actor_Reset(sld);
	LAi_ActorGoToLocator(sld, "rld", "aloc4", "CBL_AST_crewman4_Reached", 15.0);
}

void CBL_AST_crewman5(string qName)
{
	ref sld;

	sld = CharacterFromID("Volverston");
	LAi_SetActorType(sld);
	TeleportCharacterToLocator(sld, "quest", "quest20");
	LAi_type_actor_Reset(sld);
	LAi_ActorGoToLocator(sld, "rld", "aloc13", "", 20.0);
}

void CBL_AST_crewman6(string qName)
{
	ref sld;

	sld = CharacterFromID("Dieke");
	TeleportCharacterToLocator(sld, "quest", "quest15");
	LAi_type_actor_Reset(sld);
	LAi_ActorGoToLocator(sld, "rld", "aloc6", "", 10.0);

	sld = CharacterFromID("FreeSlave_2");
	TeleportCharacterToLocator(sld, "quest", "quest19");
	LAi_type_actor_Reset(sld);
	LAi_ActorGoToLocator(sld, "rld", "aloc2", "", 12.0);

	sld = CharacterFromID("FreeSlave_3");
	TeleportCharacterToLocator(sld, "quest", "quest20");
	LAi_type_actor_Reset(sld);
	LAi_ActorGoToLocator(sld, "rld", "aloc1", "", 10.0);
}

void CapBloodLine_ArabellaShipTakeScene_3(string qName)
{
	locCameraFromToAngle(30.46, 6.14, 97.94, true, 0.221, -0.861);

	DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_Guard23_Patrol", 1.0);
}

void CapBloodLine_ArabellaShipTakeScene_4(string qName)
{
	locCameraFromToAngle(32.162, 4.851, 115.504, true, -0.093, -2.20);
}

void CapBloodLine_ArabellaShipTakeScene_4_1(string qName)
{
	locCameraFlyLookFromToAngle(32.162, 4.851, 115.504, -0.093, -2.20, -0.243, -2.20, 600/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_ArabellaShipTakeScene_4_2";
}

void CapBloodLine_ArabellaShipTakeScene_4_2()
{
	locCameraFromToAngle(32.162, 4.851, 115.504, true, -0.243, -2.20);
}

void CapBloodLine_ArabellaShipTakeScene_5(string qName)
{
	LAi_FadeEx(0.0, 1.0, 1.0, "CapBloodLine_ArabellaShipTakeScene_5_1", "CapBloodLine_ArabellaShipTakeScene_5_2", "");
}

void CapBloodLine_ArabellaShipTakeScene_5_1(string qName)
{
	ref sld;

	sld = CharacterFromID("FreeSlave_1");
	LAi_type_actor_Reset(sld);
	TeleportCharacterToLocator(sld, "rld", "aloc15");
}

void CapBloodLine_ArabellaShipTakeScene_5_2(string qName)
{
	locCameraFromToAngle(10.795, 5.488, 92.709, true, -0.0105, 1.09);

	ref sld;

	sld = CharacterFromID("FreeSlave_1");
	LAi_ActorFollow(sld, CharacterFromID("ShipGuard_0"), "CBL_AST_crewman4_1_Reached", 1.0);
}

void CapBloodLine_ArabellaShipTakeScene_5_3(string qName)
{
	locCameraFlyLookFromToAngle(10.795, 5.488, 92.709, -0.0105, 1.09, -0.0533, 0.633, 600/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_ArabellaShipTakeScene_5_4";
}

void CapBloodLine_ArabellaShipTakeScene_5_4()
{
	locCameraFromToAngle(10.795, 5.488, 92.709, true, -0.0533, 0.633);
}

void CapBloodLine_ArabellaShipTakeScene_6(string qName)
{
	LAi_FadeEx(0.0, 1.0, 1.0, "CapBloodLine_ArabellaShipTakeScene_6_1", "CapBloodLine_ArabellaShipTakeScene_7", "");
}

void CapBloodLine_ArabellaShipTakeScene_6_1(string qName)
{
	string offName;
	ref sld;
    int iChar;
    string rloc = "";

    for (int i=0; i <= 12; i++)
    {
        offName = "ShipGuardStore_"+i;
        switch(i)
        {
            case 7:
                offName ="Volverston";
                rloc = "";
            break;

            case 8:
                offName ="Hugtorp";
                rloc = "aloc2";
            break;

            case 9:
                offName ="Dieke";
                rloc = "aloc5";
            break;

            case 10:
                offName ="Ogl";
                rloc = "aloc0";
            break;

            case 11:
                offName ="FreeSlave_2";
                rloc = "aloc1";
            break;

            case 12:
                offName ="FreeSlave_3";
                rloc = "aloc3";
            break;
        }
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];

			if (i < 7)
			{
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Bridgetown_town", "rld", "aloc"+(8+i));
			}
			else
			{
				if (rloc != "")
				{
				    TeleportCharacterToLocator(sld, "rld", rLoc);
				}
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
				// сброс имитации файт-мода -->
				LAi_SetDefaultStayAnimation(sld);
				// <--
				CharacterTurnToLoc(sld, "rld", "aloc8");
			}
        }
    }

    LAi_SetDefaultStayAnimation(pchar); // сброс имитации файт-мода
    LAi_tmpl_SetFight_NoTarget(pchar);
    CharacterTurnToLoc(pchar, "rld", "aloc8");
}

void CapBloodLine_ArabellaShipTakeScene_7(string qName)
{
	ref sld;

	for (int i=0; i < 6; i++)
	{
		sld = CharacterFromId("ShipGuardStore_"+i);

		if (i < 3)
		{
			LAi_ActorGoToLocator(sld, "quest", "quest24", "", -1);
		}
		else
		{
		    LAi_ActorGoToLocator(sld, "quest", "quest16", "", -1);
		}
	}

	locCameraFlyToPositionLookToPoint(20.77, 4.49, 97.99, 25.686, 4.49, 103.26, 0.77, 4.49, 80.99, -1.0, 2000/GetDeltaTime());
	Pchar.FuncCameraFly = "CapBloodLine_ArabellaShipTakeScene_8";

	DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_7_1", 1.0);
}

void CapBloodLine_ArabellaShipTakeScene_7_1(string qName)
{
	string offName;
	ref sld;
    int iChar;

    for (int i=0; i <= 12; i++)
    {
        offName = "ShipGuardStore_"+i;
        switch(i)
        {
            case 7:
                offName ="Volverston";
            break;

            case 8:
                offName ="Hugtorp";
            break;

            case 9:
                offName ="Dieke";
            break;

            case 10:
                offName ="Ogl";
            break;

			case 11:
                offName ="FreeSlave_2";
            break;

            case 12:
                offName ="FreeSlave_3";
            break;
        }
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
			LAi_SetImmortal(sld, false);

		 	if (i < 7)
			{
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			else
			{
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				DeleteAttribute(sld, "SwordTakeOutSilent");
			}
        }
    }
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
    LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL); // Чтобы не кидались назад в город

    LAi_group_SetCheck("EnemyFight", "ShipGuardsDie");

    PlaySound("Voice\" + VoiceGetLanguage() + "\EvilPirates01.wav");
	CharacterTurnToLoc(pchar, "rld", "aloc8");
	DeleteAttribute(pchar, "SwordTakeOutSilent");

	chrDisableReloadToLocation = true; // закрыть выход из локации
}

void CapBloodLine_ArabellaShipTakeScene_8()
{
	locCameraSleep(true);
	DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_9", 1.5);
}

void CapBloodLine_ArabellaShipTakeScene_9(string qName)
{
	LAi_FadeEx(0.0, 1.0, 1.0, "CapBloodLine_ArabellaShipTakeScene_10", "CapBloodLine_ArabellaShipTakeScene_11", "");
}

void CapBloodLine_ArabellaShipTakeScene_10(string qName)
{
	EndQuestMovie();
	locCameraSleep(false);
	locCameraFollowEx(true);
}

void CapBloodLine_ArabellaShipTakeScene_11(string qName)
{
	LAi_SetPlayerType(pchar);
}

void ShipGuardsDie()
{
    ref sld;
    chrDisableReloadToLocation = false;
    LocatorReloadEnterDisable("BridgeTown_town", "reloadShip", false);
    sld = characterFromID("SpaFirstMate");
    LAi_group_MoveCharacter(sld, "EnemyFight");

    QuestPointerToLoc("Bridgetown_town", "reload", "reloadShip");
}

void SpaFirstMateDie(string qName)
{
    string offName;
    ref sld;
    int i, iChar;
    for (i=0; i < 13; i++)
	{

       offName = "SpaSolder_"+i;
        switch(i)
        {
            case 11:
                offName ="SpaRaider";
            break;

            case 12:
                offName ="ArabelaService";
            break;

        }
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
            sld.lifeDay = 0;
        }
    }
    pchar.quest.CapBloodEscape6.win_condition.l1          = "location";
    pchar.quest.CapBloodEscape6.win_condition.l1.location = "Bridgetown_town";
    pchar.quest.CapBloodEscape6.function                  = "QOfficersRecruit";
    AddQuestRecord("EscapeFormBarbados", "5");
    CloseQuestHeader("EscapeFormBarbados");
    ShipGuardsDie();
    QuestPointerDelLoc("Bridgetown_town", "reload", "reloadShip");

    // выдадим предметы умершему кэпу
	sld = characterFromID("SpaFirstMate");
	for(i = 0; i < Dead_Char_num; i++)
	{
		if (Dead_Characters[i].index == sld.index)
		{
			TakeNItems(&Dead_Characters[i], "spyglass2", 1); // обычная подзорная труба
			TakeNItems(&Dead_Characters[i], "map_normal", 1); // обычная карта
		}
	}
}

void QOfficersRecruit(string qName)
{
    string offName, sNode;
    ref sld;
    int iChar, i;

    // С этого момента стартуем глобальный туториал
  	TEV.GlobalTutor = true;

    for (i=0 ; i <= 4; i++)
    {
        switch(i)
        {
            case 0:
                offName ="Volverston";
                sNode = "VLStep_11";
            break;
			
			case 1:
                offName ="Ogl";
                sNode = "OGLStep_11";
            break;
            
            case 2:
                offName ="Dieke";
                sNode = "DKStep_5";
            break;

            case 3:
                offName ="Hugtorp";
                sNode = "HTStep_13";
            break;

            case 4:
                offName ="Pitt";
                sNode = "PStep_16";
            break;
        }
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
            sld.loyality = MAX_LOYALITY; //fix лояльности квестовых
            LAi_SetImmortal(sld, false);//fix бессмертного Питта
			if (offName =="Pitt")
			{
       	    	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest16");
       	    }
       	    else
			{
       	    	ChangeCharacterAddressGroup(sld, "Bridgetown_town", "quest", "quest"+(22+i));
			}
            LAi_SetActorTypeNoGroup(sld);
            LAi_ActorTurnToLocator(sld, "quest", "quest11");
            sld.dialog.currentnode = sNode;
			LAi_SetRolyPoly(sld, true); //неваляхи бладовцы
            if (offName =="Pitt")
			{
			    chrDisableReloadToLocation = true;
			    LAi_ActorDialog(sld, pchar, "",  -1.0, 0);
			}
            else LAi_SetStayTypeNoGroup(sld);
            AddLandQuestmark_Main(sld, "CapBloodLine");
        }
    }

    for (i=1; i <= 3; i++)
    {
        offName = "FreeSlave_"+i;
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
        	sld = &characters[iChar];
            ChangeCharacterAddressGroup(sld, "none", "", "");
            sld.lifeday = 0;
        }
    }
}

void VolverstonAdd()
{
    ref chref;
    chref = characterFromID("Volverston");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Officer_Man.c";
	chref.greeting = "Gr_questOfficer";
	CapBlood_CheckOfficersRecruit();
}

void HugtorpAdd()
{
    ref chref;
    chref = characterFromID("Hugtorp");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Officer_Man.c";
	chref.greeting = "Gr_questOfficer";
	CapBlood_CheckOfficersRecruit();
}

void DiekeAdd()
{
    ref chref;
    chref = characterFromID("Dieke");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Officer_Man.c";
	chref.greeting = "Gr_questOfficer";
	CapBlood_CheckOfficersRecruit();
}

void OglAdd()
{
    ref chref;
    chref = characterFromID("Ogl");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Officer_Man.c";
	CapBlood_CheckOfficersRecruit();
}

void CapBlood_CheckOfficersRecruit()
{
	string offName;
    ref sld;
    int iChar;
    string recruits = "Volverston,Ogl,Dieke,Hugtorp,Pitt";
    int q = KZ|Symbol(recruits, ",");

	bool isPassed = true;
    for (int i=0 ; i <= q; i++)
    {
    	isPassed = false;
        offName = GetSubStringByNum(recruits, i);
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
            isPassed = CheckPassengerInCharacter(pchar, sld.id);
            if (!isPassed)
			{
	            break;
			}
        }
    }

	if (isPassed)
	{
		DoQuestFunctionDelay("CapBlood_DoneOfficersRecruit_StartOffTutorial", 1.5);
	}
}

void CapBlood_DoneOfficersRecruit_StartOffTutorial(string qName)
{
	TW_Init_BloodLine_Officers();
	TW_Open("BloodLine_Officers");
	Tutorial_BloodPrologue_Officers("");
}

void CapBlood_DoneOfficersRecruit_OpenExit(string qName)
{
	LocatorReloadEnterDisable("BridgeTown_town", "reloadShip", false);
	ref rLoc = &locations[FindLocation("Bridgetown_town")];
	rLoc.reload.ship1.autoreload = "1";
	QuestPointerToLoc("Bridgetown_town", "reload", "reloadShip");
}

void CapBlood_DoneOfficersRecruit_CloseExit(string qName)
{
	LocatorReloadEnterDisable("BridgeTown_town", "reloadShip", true);
	ref rLoc = &locations[FindLocation("Bridgetown_town")];
	rLoc.reload.ship1.autoreload = "0";
	QuestPointerDelLoc("Bridgetown_town", "reload", "reloadShip");
}

void CapBloodLine_OfficersRecruit_DelQuestMarks()
{
    string offName;
    ref sld;
    int iChar;
    string recruits = "Volverston,Ogl,Dieke,Hugtorp,Pitt";
    int q = KZ|Symbol(recruits, ",");

    for (int i=0 ; i <= q; i++)
    {
        offName = GetSubStringByNum(recruits, i);
        iChar = GetCharacterIndex(offName);
        if (iChar != -1)
        {
            sld = &characters[iChar];
            RemoveLandQuestmark_Main(sld, "CapBloodLine");
        }
    }
}

void SpaCrewAtack()
{
    int iCommanderIdx,iChar,i;
    ref chref;
    
    chref = characterFromID("Pitt");
    chref.Dialog.CurrentNode = "hired";
   	chref.Dialog.FileName = "Officer_Man.c";

	// на берег нельзя
	Island_SetReloadEnableGlobal("Barbados", false);

    string sGroup = "SpaCrew";
    Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup,"war");
	Group_SetTaskNone(sGroup);

    for (i=0; i<2; i++)
    {
        iChar = NPC_GenerateCharacter("SpaBoat_"+i, "off_spa_2", "man", "man", 7, SPAIN, 1, true);
        makeref(chref, Characters[iChar]);
        chref.Ship.Mode = "war";
        chref.Ship.Type = GenerateShipExt(SHIP_LUGGER, 1, chref);
        SetRandomNameToCharacter(chref);
        SetRandomNameToShip(chref);
        
        SetBaseShipData(chref);
        SetCrewQuantityOverMax(chref, 150);
        ShipOverhaul(chref);

        Fantom_SetCannons(chref, "war");
        SetFantomParamHunter(chref); //крутые парни
        SetCaptanModelByEncType(chref, "war"); //фиксим баг с заменой модели Дайка Konstrush
        Group_AddCharacter(sGroup, chref.id);
        if (i == 0)
		{
        	iCommanderIdx = iChar;
		  	Fantom_SetBalls(chref, "war");
			Group_SetGroupCommander(sGroup, chref.id);
			chref.ship.HP = makeint(stf(chref.ship.HP) * 0.5);

			pchar.quest.SpaCrewAtack_NPCDeath1.win_condition.l1 = "NPC_Death";
			pchar.quest.SpaCrewAtack_NPCDeath1.win_condition.l1.character = chref.id;
			pchar.quest.SpaCrewAtack_NPCDeath1.function = "BloodLine_SpaCrewAtack_NPCDeath1";
		}
		if (i == 1)
		{
			Fantom_SetBalls(chref, "trade");
		}

		chref.Abordage.Enable = false; //нельзя брать на абордаж
		chref.AlwaysSandbankManeuver = true; //тупым запрет тонуть о берег
		chref.DontRansackCaptain = true; // в плен не сдаваться
    }
    Group_SetAddress(sGroup, "Barbados", "IslandShips1", "ship_3");
}

// Используется только в бета-тесте
// для квеста см. Bishop "PStep_19" ветку
void CincoLlagasCapture()
{
	initMainCharacterItem();
	pchar.Ship.Type = GenerateShipExt(SHIP_ARABELLA, true, pchar);
	pchar.Ship.name = FindPersonalName("Blad_ship");
	SetBaseShipData(pchar);
	pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS32;
	SetCrewQuantityFull(pchar);
	Set_My_Cabin();

	ref rShip = GetRealShip(sti(pchar.Ship.Type));
	rShip.ship.upgrades.hull = 1;

	SetCharacterGoods(pchar, GOOD_FOOD, 2000);
	SetCharacterGoods(pchar, GOOD_BALLS, 2000);
	SetCharacterGoods(pchar, GOOD_GRAPES, 300);
	SetCharacterGoods(pchar, GOOD_KNIPPELS, 400);
	SetCharacterGoods(pchar, GOOD_BOMBS, 2000);
	SetCharacterGoods(pchar, GOOD_POWDER, 2000);
	SetCharacterGoods(pchar, GOOD_PLANKS, 10);
	SetCharacterGoods(pchar, GOOD_RUM, 40);
	SetCharacterGoods(pchar, GOOD_WEAPON, 2000);
}

////////////////////////////////////////////////////////////////////////////////////////////
void RestoreBridgetown()
{
	ref sld, rColony;
	Pchar.questTemp.CapBloodLine = false;
	//Нормальная одежда
	Pchar.model = "Blad_0";
	sld = characterFromID("Pitt");			sld.model = "Pitt";
	sld = characterFromID("Volverston");	sld.model = "Volverston";
	sld = characterFromID("Hugtorp");		sld.model = "Hugtorp";
	sld = characterFromID("Dieke");			sld.model = "Dieke";
	sld = characterFromID("Ogl");			sld.model = "Ogl";
	//Губернатор
	sld = &characters[GetCharacterIndex("Bridgetown_Mayor")];
	sld.Dialog.Filename = "Common_Mayor.c";
	sld.Dialog.CurrentNode = "First time";
	//город
	int n = FindLocation("Bridgetown_town");  // не забыть вернуть
	locations[n].reload.l3.close_for_night = true;
	locations[n].questSeekCap = 6;
	locations[n].houseEnc = true;
	//Таверна пьянь
	n = FindLocation("Bridgetown_tavern");
	locations[n].habitues = 1;
	DeleteAttribute(&locations[n], "notCloseCommonHouse");
	//Диалоги горожан
	ChangeBridgeTownDialogs(true);
	bDisableLandEncounters = false;
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	Pchar.questTemp.CapBUnarmed = false;
	//сундуки почистим
	//if (CheckAttribute(PChar, "GenQuestBox.CommonStoneHouse")) DeleteAttribute(PChar, "GenQuestBox.CommonStoneHouse");
	n = FindLocation("CommonStoneHouse");
	locations[n].models.day.locators = "StoneHouse_locators";
	locations[n].models.night.locators = "StoneHouse_Nlocators";
	//Плантации
	n = FindLocation("BridgeTown_Plantation");
	locations[n].citizens = true;
	locations[n].carrier = true;
	//
	SetLocationCapturedState("Bridgetown_town", false);
	SetLocationCapturedState("BridgeTown_Plantation", false);
	LocatorReloadEnterDisable("BridgeTown_town", "reload5_back", false);
	LocatorReloadEnterDisable("BridgeTown_town", "reload1_back", false);
	LocatorReloadEnterDisable("BridgeTown_fort", "reload2", false); //fix

	LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//fix полностью открываем резиденцию
	LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", false);
	LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);

	//Торговца вернуть
	sld = characterFromID("Bridgetown_trader");
	LAi_RemoveLoginTime(sld);

	// переехало дальше по квесту
//	makeref(rColony, Colonies[FindColony("Bridgetown")]);
//	DeleteAttribute(rColony, "DontSetShipInPort"); //возвращаем жизнь
	RemoveShipFromBridgetown();
	//группы потереть
	LAi_group_Delete("EnemyFight");
	LAi_group_Delete(LAI_GROUP_TmpEnemy);

	//прерывания снять
	if (CheckAttribute(PChar, "quest.CureLordMovie")) Pchar.quest.CureLordMovie.over = "yes";
	if (CheckAttribute(PChar, "quest.DragunInvansion")) Pchar.quest.DragunInvansion.over = "yes";
	if (CheckAttribute(PChar, "quest.BloodGetBlade")) Pchar.quest.BloodGetBlade.over = "yes";
	if (CheckAttribute(PChar, "quest.CapBloodLine_q1_1")) Pchar.quest.CapBloodLine_q1_1.over = "yes";
	if (CheckAttribute(PChar, "quest.onPlantation")) Pchar.quest.onPlantation.over = "yes";
	if (CheckAttribute(PChar, "quest.CapBloodLineTimer_1")) Pchar.quest.CapBloodLineTimer_1.over = "yes";
	if (CheckAttribute(PChar, "quest.CureMisStid")) Pchar.quest.CureMisStid.over = "yes";
	if (CheckAttribute(PChar, "quest.PrepareToEscape2")) Pchar.quest.PrepareToEscape2.over = "yes";
	if (CheckAttribute(PChar, "quest.PrepareToEscape3")) Pchar.quest.PrepareToEscape3.over = "yes";
	if (CheckAttribute(PChar, "quest.WinterwoodDuel")) Pchar.quest.WinterwoodDuel.over = "yes";
	if (CheckAttribute(PChar, "quest.MoneyForDieke")) Pchar.quest.MoneyForDieke.over = "yes";
	if (CheckAttribute(PChar, "quest.CapBloodLineTimer_2")) Pchar.quest.CapBloodLineTimer_2.over = "yes";
	if (CheckAttribute(PChar, "quest.QUsurer")) Pchar.quest.QUsurer.over = "yes";
	if (CheckAttribute(PChar, "quest.CapBloodEscape1")) Pchar.quest.CapBloodEscape1.over = "yes";
	if (CheckAttribute(PChar, "quest.CapBloodEscape2")) Pchar.quest.CapBloodEscape2.over = "yes";
	if (CheckAttribute(PChar, "quest.CapBloodEscape3")) Pchar.quest.CapBloodEscape3.over = "yes";
	if (CheckAttribute(PChar, "quest.CapBloodEscape4")) Pchar.quest.CapBloodEscape4.over = "yes";
	if (CheckAttribute(PChar, "quest.CapBloodEscape5")) Pchar.quest.CapBloodEscape5.over = "yes";
	if (CheckAttribute(PChar, "quest.CapBloodEscape6")) Pchar.quest.CapBloodEscape6.over = "yes";
	if (CheckAttribute(PChar, "quest.CapBloodLine_ReachQuestPointer_AttackShip")) Pchar.quest.CapBloodLine_ReachQuestPointer_AttackShip.over = "yes";
	if (CheckAttribute(PChar, "quest.SolderTakeBladesDie")) Pchar.quest.SolderTakeBladesDie.over = "yes";
	if (CheckAttribute(PChar, "quest.SaveArabelaService")) pchar.quest.SaveArabelaService.over = "yes";
	DeleteAttribute(&TEV, "BloodDetectDagger");
	LAi_group_RemoveCheck("EnemyFight");
	//Квесты закрыть
	CloseQuestHeader("FishermanQuest");
	CloseQuestHeader("UsurerQuest");
	CloseQuestHeader("PirateQuest");
	n = GetCharacterIndex("Bishop");
	//убираем полковника с плантации
	if(n != -1)
	{
		sld = &characters[n];
		ChangeCharacterAddress(sld, "None", "");
	}

	HarvestHerbClear("Bridgetown_ExitTown", 1);
	DeleteAttribute(pchar, "alchemy.migraine_potion.isKnown");

	string sTemp = "migraine_potion";
	sld = ItemsFromID(sTemp);
	DeleteAttribute(sld, "craft");
	// удаляем зелья с мигренью если остались
	if (CheckCharacterItem(pchar, sTemp))
	{
	    TakeNItems(pchar, sTemp, -sti(pchar.items.(sTemp)));
	}

	// удаляем квест марки
    CapBloodLine_OfficersRecruit_DelQuestMarks();
    CapBloodLine_ReachQuestPointer_Escape_ClearAll();
    QuestPointerDelLoc("Bridgetown_town", "quest", "quest11");
    QuestPointerDelLoc("Bridgetown_town", "reload", "reloadShip");
}

void CapBloodLaspEpisode(string qName)
{
    RestoreBridgetown();
    BloodLine_GlobalTutor_SetRestricts();
    TW_Finish_BloodLine_Officers("");
    DoQuestFunctionDelay("BloodLine_SpaCrewAtack_StartSeaTutorials", 1.5);
    SpaCrewAtack_SetTasks();
}

void BloodLine_GlobalTutor_SetRestricts()
{
	// Блокируем генераторные квесты
	bDisableLandEncounters = true;
	pchar.questTemp.different = "GlobalTutor";

	// крысы не жрут товар, команда - праноеды
	bNoEatNoRats = true;
	// ОЗГов на паузу
	PChar.GenQuest.HunterLongPause = true;

	bQuestDisableMapEnter = true;
}

void BloodLine_SpaCrewAtack_StartSeaTutorials(string qName)
{
	Tutorial_BloodPrologue_ShipControl("");
	Tutorial_BloodPrologue_SeaBattle("");

	TW_Init_BloodLine_SeaBattle1();
	TW_Open("BloodLine_SeaBattle1");
}

void SpaCrewAtack_SetTasks()
{
	ref sld = CharacterFromId("SpaBoat_0");
	int iCommanderIdx = sti(sld.index);
	Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), sti(Pchar.index));
	sld.ShipTaskLock = true;

	sld = CharacterFromId("SpaBoat_1");
	Ship_SetTaskDefend(SECONDARY_TASK, sti(sld.index), iCommanderIdx);
	sld.ShipTaskLock = true;
}

void BloodLine_SpaCrewAtack_NPCDeath1(string qName)
{
	// отмечаем в таске
	TW_IncreaseCounter("BloodLine_SeaBattle1", "SeaBattle1_text1", 1);
	aref arCnt;
	if (CheckAttribute(&objTask, "BloodLine_SeaBattle1.texts.SeaBattle1_text0"))
	{
	   	makearef(arCnt, objTask.BloodLine_SeaBattle1.texts.SeaBattle1_text0);
		TW_ColorWeak(arCnt);
	}

	string sGroup = "SpaCrew";
	int iChar = GetCharacterIndex("SpaBoat_1");
	ref sld;
	if (iChar >= 0 && !LAi_IsDead(&characters[iChar]))
	{
		sld = &characters[iChar];

		Group_SetGroupCommander(sGroup, sld.id);
		Group_SetTaskNone(sGroup);
		Group_LockTask(sGroup);

		Ship_SetTaskRunAway(SECONDARY_TASK, sti(sld.index), sti(Pchar.index));
		PostEvent(SHIP_DROP_GOOD, 1000, "a", sld);
		sld.Abordage.Enable = false; //нельзя брать на абордаж

		DoQuestFunctionDelay("TW_Finish_BloodLine_SeaBattle1", 2.0);
	}
	else
	{
		TW_Release();
		DoQuestFunctionDelay("BloodLine_GlobalTutor_ReloadToCabinDialog", 6.0);
	}
	Group_DeleteAtEnd(sGroup);
}

void BloodLine_GlobalTutor_ReloadToCabinDialog(string qName)
{
	// AlexBlade > вся эта канитель нужна чтобы полностью рестартнуть море
	// и загрузить каюту как полноценную локацию, а не палубу

	// переход в каюту
	Set_My_Cabin();

	DoFunctionReloadToLocation(Get_My_Cabin(), "goto", "goto2", "BloodLine_GlobalTutor_StartCabinDialog");
}

void BloodLine_GlobalTutor_StartCabinDialog()
{
	chrDisableReloadToLocation = true;
	bAbordageStarted = true;

	PauseAllSounds();
	ResetSound();

	ref sld = characterFromID("Pitt");
    sld.Dialog.CurrentNode = "Pitt_GTutor_Cabin_1";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_YoungMan";

	ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
    LAi_SetActorType(sld);

	LAi_SetActorType(pchar);
	SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void BloodLine_GlobalTutor_SetPittOffDialogs()
{
	ref sld = characterFromID("Pitt");
	sld.Dialog.CurrentNode = "hired";
	sld.Dialog.FileName = "Officer_Man.c";
}

void BloodLine_GlobalTutor_EndCabinDialog(string qName)
{
	chrDisableReloadToLocation = false;
	bAbordageStarted = false;
	LAi_SetPlayerType(pchar);

	pchar.quest.BloodLine_GlobalTutor_GoWorldmapEnter.win_condition.l1 = "EnterToSea";
	pchar.quest.BloodLine_GlobalTutor_GoWorldmapEnter.function = "BloodLine_GlobalTutor_GoWorldmapEnter";

	// подготвка к выходу в море после диалога в каюте -->
	// Телепорт к острову, если просто в море, то возникают визуальные баги,
	// и координаты неправильно рассчитываются, хз почему =(
	DeleteAttribute(&questToSeaLoginer, "");
	QuestToSeaLogin_PrepareLoc("Barbados", "reload", "reload_3", true);
	// <--

	// выход в море
	QuestToSeaLogin_Launch();
}

void BloodLine_GlobalTutor_GoWorldmapEnter(string qName)
{
    // возвращаем жизнь в порту Бриджтауна
    ref rColony;
	makeref(rColony, Colonies[FindColony("Bridgetown")]);
	DeleteAttribute(rColony, "DontSetShipInPort");  //возвращаем жизнь

 	SetFunctionMapEnterCondition("BloodLine_GlobalTutor_WorldmapTutorial", false);

 	DoQuestFunctionDelay("BloodLine_GlobalTutor_StartEnterMapTutorial", 2.0);
}

void BloodLine_GlobalTutor_StartEnterMapTutorial(string qName)
{
    // обработчик на глобалке - лочит выход у островов
    // и блочит взаимодействие с энкаунтерами
    SetMapCoordinateQuest("CheckQuestCoordinates_GTutor");
    // энкаунтеров не генерим
    pchar.worldmapencountersoff = "1";

	// Блокируем остальные бухты, оставляем только Порт
	Island_SetReloadEnableLocal("Tortuga", "reload_2", false);
	Island_SetReloadEnableLocal("Tortuga", "reload_3", false);
	Island_SetReloadEnableLocal("Tortuga", "reload_fort1", false);

	// Офицеров в город пока не пустим
	LAi_LocationDisableOfficersGen("Tortuga_town", true);
	DeleteAttribute(&locations[FindLocation("Tortuga_town")], "questSeekCap");	//уберем квестодателя

	pchar.quest.BloodLine_GlobalTutor_OnTortugaArealEnter.win_condition.l1 = "EnterToSea";
	pchar.quest.BloodLine_GlobalTutor_OnTortugaArealEnter.function = "BloodLine_GlobalTutor_OnTortugaArealEnter";

	// стартуем туториал
	bQuestDisableMapEnter = false;
    Tutorial_BloodPrologue_EnterMap("");
}

void BloodLine_GlobalTutor_WorldmapTutorial(string qName)
{
    DoQuestFunctionDelay("Tutorial_BloodPrologue_WorldMap", 2.0);
}

void BloodLine_GlobalTutor_OnTortugaArealEnter(string qName)
{
	int iIsland = FindIsland(pchar.location);
	if(iIsland > 0 && Islands[iIsland].id == "Tortuga")
	{
		// закрываем Ф2
		bDisableCharacterMenu = true;
		// Поднимаем флаг
		if (sti(PChar.nation) != ENGLAND)
		{
			Flag_ENGLAND();
		}
		// стартуем туториал
   		DoQuestFunctionDelay("BloodLine_GlobalTutor_StartFastTravelTutorial", 2.0);
	}

	pchar.quest.BloodLine_GlobalTutor_OnExitToMapAgain.win_condition.l1 = "MapEnter";
	pchar.quest.BloodLine_GlobalTutor_OnExitToMapAgain.function = "BloodLine_GlobalTutor_OnExitToMapAgain";

	pchar.quest.BloodLine_GlobalTutor_OnTortugaTownEnter.win_condition.l1 = "Location";
	pchar.quest.BloodLine_GlobalTutor_OnTortugaTownEnter.win_condition.l1.location = "Tortuga_town";
	pchar.quest.BloodLine_GlobalTutor_OnTortugaTownEnter.function = "BloodLine_GlobalTutor_OnTortugaTownEnter";
}

void BloodLine_GlobalTutor_OnExitToMapAgain(string qName)
{
	bDisableCharacterMenu = false;

	pchar.quest.BloodLine_GlobalTutor_OnTortugaArealEnter.win_condition.l1 = "EnterToSea";
	pchar.quest.BloodLine_GlobalTutor_OnTortugaArealEnter.function = "BloodLine_GlobalTutor_OnTortugaArealEnter";
}

void BloodLine_GlobalTutor_StartFastTravelTutorial(string qName)
{
	Tutorial_BloodPrologue_FastTravel("");
}

void BloodLine_GlobalTutor_OnTortugaTownEnter(string qName)
{
	// трём предыдущие прерывания
	pchar.quest.BloodLine_GlobalTutor_OnTortugaArealEnter.over = "yes";
	pchar.quest.BloodLine_GlobalTutor_OnExitToMapAgain.over = "yes";
	// убираем обработчик с глобалки
	DeleteMapCoordinateQuest("CheckQuestCoordinates_GTutor");
 	// лочим переходы
	bDisableFastReload = true;
	// выставляем баны
	pchar.GenQuest.CannotWait = 1;
	// бан на обыск и обмен предметов, в конце туториала снимем
	// лок нужен чтобы игрок не "спрятал" деньги для стоянки и не вызвал софт-лок
	SetBan("Looting", true);
	SetBan("Exchange", true);

	// задел для глобал туториала - деньги на стоянку для Арабеллы
	pchar.questTemp.BloodLine_GTutor.shipBuyMoney = 40000; // цена за покупку нового корабля
	pchar.questTemp.BloodLine_GTutor.shipGiveMoney = makeint(0.125 * MOD_SKILL_ENEMY_RATE * 75) * 1000; // цена за стоянку фрегата
	pchar.questTemp.BloodLine_GTutor.hireCrewMoney = 100; // цена за одного матроса
	pchar.questTemp.BloodLine_GTutor.hireCrewQty = 60; // столько матросов будет доступно в таверне

	// Лочим все локаторы кроме верфи
	aref arDis, arRld;
	makearef(arRld, Locations[FindLocation("Tortuga_town")].reload);
	int	Qty = GetAttributesNum(arRld);
	for (int i=0; i<Qty; i++)
	{
		arDis = GetAttributeN(arRld, i);
        if (arDis.name != "reload5_back")
        {
    		arDis.disable = 1;
        }
	}

	//диалог с Питтом
	chrDisableReloadToLocation = true;

	ref sld = characterFromID("Pitt");
    sld.Dialog.CurrentNode = "Pitt_GTutor_Tortuga1";
    sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
    sld.greeting = "Gr_YoungMan";

	ChangeCharacterAddressGroup(sld, "Tortuga_town", "quest", "quest1");
    LAi_SetActorType(sld);

	LAi_SetActorType(pchar);
	SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void BloodLine_GlobalTutor_OnTortugaShipyard(string qName)
{
	chrDisableReloadToLocation = true;
	QuestPointerDelLoc("Tortuga_town", "reload", "reload5_back");

	if (CheckAttribute(&objTask, "BloodLine_NewShip"))
	{
		TW_IncreaseCounter("BloodLine_NewShip", "NewShip_text1", 1);
	}

	// стартуем туториал
	DoQuestFunctionDelay("BloodLine_GlobalTutor_StartBuyShipTutorial", 2.0);

	// прерывание в порту
	SetFunctionLocationCondition("BloodLine_GlobalTutor_OnTortugaTown1", "Tortuga_town", false);
}

void BloodLine_GlobalTutor_StartNavigationTutorial(string qName)
{
	Tutorial_BloodPrologue_Navigation("");
	TW_Init_BloodLine_NewShip();
	TW_Open("BloodLine_NewShip");
}

void BloodLine_GlobalTutor_StartBuyShipTutorial(string qName)
{
	Tutorial_BloodPrologue_BuyShip("");
}

void BloodLine_GlobalTutor_StartShipChangeTutorial(string qName)
{
	RemoveLandQuestmark_Main(CharacterFromId("Tortuga_shipyarder"), "GlobalTutor");
	Tutorial_BloodPrologue_ShipChange("");
}

void BloodLine_GlobalTutor_BuyShipDone_OpenExit(string qName)
{
	chrDisableReloadToLocation = false;
	QuestPointerToLoc("Tortuga_shipyard", "reload", "reload1_back");
}

void BloodLine_GlobalTutor_BuyShipDone_CloseExit(string qName)
{
	chrDisableReloadToLocation = true;
	QuestPointerDelLoc("Tortuga_shipyard", "reload", "reload1_back");
}

void BloodLine_GlobalTutor_OnTortugaTown1(string qName)
{
	TW_Finish_BloodLine_NewShip1("");
	DoQuestFunctionDelay("TW_Start_BloodLine_NewShip2", 1.0);
	bDisableCharacterMenu = true;
	LocatorReloadEnterDisable("Tortuga_town", "reload5_back", true);
	LocatorReloadEnterDisable("Tortuga_town", "reload10_back", false);
	QuestPointerToLoc("Tortuga_town", "reload", "reload10_back");
	AddLandQuestmark_Main(CharacterFromId("Tortuga_portman"), "GlobalTutor");

	// прерывание в портовом управлении
	SetFunctionLocationCondition("BloodLine_GlobalTutor_OnTortugaPortOffice", "Tortuga_portoffice", false);
}

void BloodLine_GlobalTutor_OnTortugaPortOffice(string qName)
{
	chrDisableReloadToLocation = true;
	QuestPointerDelLoc("Tortuga_town", "reload", "reload10_back");

	if (CheckAttribute(&objTask, "BloodLine_NewShip"))
	{
		TW_IncreaseCounter("BloodLine_NewShip", "NewShip_text1", 1);
	}

	// прерывание в порту
	SetFunctionLocationCondition("BloodLine_GlobalTutor_StartTortugaCrewDialog", "Tortuga_town", false);
}

void BloodLine_GlobalTutor_GiveShipDone_OpenExit(string qName)
{
	chrDisableReloadToLocation = false;
	QuestPointerToLoc("Tortuga_PortOffice", "reload", "reload1_back");
	RemoveLandQuestmark_Main(CharacterFromId("Tortuga_portman"), "GlobalTutor");
}

void BloodLine_GlobalTutor_StartTortugaCrewDialog(string qName)
{
	TW_Finish_BloodLine_NewShip2("");
	QuestPointerDelLoc("Tortuga_PortOffice", "reload", "reload1_back");
	LocatorReloadEnterDisable("Tortuga_town", "reload10_back", true);

	//диалог с Питтом
	chrDisableReloadToLocation = true;

	ref sld = characterFromID("Pitt");
    sld.Dialog.CurrentNode = "Pitt_GTutor_Tortuga2";

	PlaceCharacter(sld, "goto", "random_must_be_near");
    LAi_SetActorType(sld);

	LAi_SetActorType(pchar);
	SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
}

void BloodLine_GlobalTutor_StartCrewTutorial(string qName)
{
	TW_Init_BloodLine_NewShip3();
	TW_Open("BloodLine_NewShip");
}

void BloodLine_GlobalTutor_OnTortugaTavern(string qName)
{
	chrDisableReloadToLocation = true;
	QuestPointerDelLoc("Tortuga_town", "reload", "reload4_back");

	if (CheckAttribute(&objTask, "BloodLine_NewShip"))
	{
		TW_IncreaseCounter("BloodLine_NewShip", "NewShip_text1", 1);
	}

	// прерывание в порту
	SetFunctionLocationCondition("BloodLine_GlobalTutor_End", "Tortuga_town", false);
	SetFunctionExitFromLocationCondition("BloodLine_GlobalTutor_TortugaRevival", pchar.location, false);

	// садим Питта в таверну
	ref sld = CharacterFromID("Pitt");
	PlaceCharacter(sld, "sit", "random_free");
	LAi_SetSitType(sld);
}

void BloodLine_GlobalTutor_HireCrew_OpenExit(string qName)
{
    chrDisableReloadToLocation = false;
    QuestPointerToLoc("Tortuga_tavern", "reload", "reload1_back");
    RemoveLandQuestmark_Main(CharacterFromId("Tortuga_tavernkeeper"), "GlobalTutor");
}

void BloodLine_GlobalTutor_HireCrew_CloseExit(string qName)
{
    chrDisableReloadToLocation = true;
    QuestPointerDelLoc("Tortuga_tavern", "reload", "reload1_back");
    AddLandQuestmark_Main(CharacterFromId("Tortuga_tavernkeeper"), "GlobalTutor");
}

void BloodLine_GlobalTutor_End(string qName)
{
	DeleteAttribute(&TEV, "GlobalTutor");
	DeleteAttribute(pchar, "questTemp.BloodLine_GTutor");
	pchar.questTemp.BloodLine_GTutor.Done = true; // флаг что тутор Блада пройден

	TW_Finish_BloodLine_NewShip3("");

	BloodLine_GlobalTutor_RemoveRestricts();
	BloodLine_GlobalTutor_DelQuestMarks();

	DoQuestFunctionDelay("Tutorial_BloodPrologue_SandBox", 2.0);
	Achievment_Set(ACH_Beglets);
}

void BloodLine_GlobalTutor_RemoveRestricts()
{
	int n, i;

	// снимаем ограничения -->
	// энкаунтеров генерим
	DeleteAttribute(pchar, "worldmapencountersoff");
	bDisableLandEncounters = false;
	// включаем генераторы
	pchar.questTemp.different = "free";
	n = FindLocation("Tortuga_town");
	locations[n].questSeekCap = 8;
	// крысы вернулись, требуем еды
	bNoEatNoRats = false;
	// пускаем ОЗГов
	DeleteAttribute(pchar, "GenQuest.HunterLongPause");

	bDisableFastReload = false;
	bDisableCharacterMenu = false;
	DeleteAttribute(pchar, "GenQuest.CannotWait");
	SetBan("Looting", false);
	SetBan("Exchange", false);

	ref sld = CharacterFromID("Pitt");
	SetCharacterRemovable(sld, true);
	BloodLine_GlobalTutor_SetPittOffDialogs();
	ChangeCharacterAddressGroup(sld, "none", "", "");
	DeleteAttribute(pchar, "questTemp.TimeLock");
	// <--

	// локаторы в городе
	aref arDis, arRld;
	makearef(arRld, Locations[FindLocation("Tortuga_town")].reload);
	int	Qty = GetAttributesNum(arRld);
	for (i=0; i<Qty; i++)
	{
		arDis = GetAttributeN(arRld, i);
		DeleteAttribute(arDis, "disable");
	}

	LAi_LocationDisableOfficersGen("Tortuga_town", false);
	LAi_LocationDisableOfficersGen("Tortuga_shipyard", false);
	LAi_LocationDisableOfficersGen("Tortuga_PortOffice", false);
	LAi_LocationDisableOfficersGen("Tortuga_tavern", false);

	// локаторы в море
	Island_SetReloadEnableLocal("Tortuga", "reload_2", true);
	Island_SetReloadEnableLocal("Tortuga", "reload_3", true);
	Island_SetReloadEnableLocal("Tortuga", "reload_fort1", true);

	// можно на берег Барбадоса
	Island_SetReloadEnableGlobal("Barbados", true);
}

void BloodLine_GlobalTutor_TortugaRevival(string qName)
{
	// Обновление населения Тортуги
	int n;
	ref sld;
	for (n = 0; n<MAX_CHARACTERS; n++)
    {
        makeref(sld, characters[n]);
        if (CheckAttribute(sld, "CityType"))
        {
            sld.lifeday = 0;
            ChangeCharacterAddress(sld, "none", "");
        }
    }
}

void BloodLine_GlobalTutor_DelQuestMarks()
{
	QuestPointerDelLoc("Tortuga_town", "reload", "reload5_back");
	QuestPointerDelLoc("Tortuga_town", "reload", "reload10_back");
	QuestPointerDelLoc("Tortuga_town", "reload", "reload4_back");
	QuestPointerDelLoc("Tortuga_shipyard", "reload", "reload1_back");
	QuestPointerDelLoc("Tortuga_PortOffice", "reload", "reload1_back");
	QuestPointerDelLoc("Tortuga_tavern", "reload", "reload1_back");

	RemoveLandQuestmark_Main(CharacterFromId("Tortuga_shipyarder"), "GlobalTutor");
	RemoveLandQuestmark_Main(CharacterFromId("Tortuga_portman"), "GlobalTutor");
	RemoveLandQuestmark_Main(CharacterFromId("Tortuga_tavernkeeper"), "GlobalTutor");
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
////   -- Линейка капитана Блада --     конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

void Slavetrader_GetRandomShore()//выбор бухты
{	
	switch (rand(3))
	{
		case 0:
			pchar.questTemp.Slavetrader.Island = "Terks";
			break;
		case 1:
			pchar.questTemp.Slavetrader.Island = "Caiman";
			break;
		case 2:
			pchar.questTemp.Slavetrader.Island = "Dominica";
			break;
		case 3:
			pchar.questTemp.Slavetrader.Island = "Bermudes";
			break;
	}
	pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomFreeShoreId(pchar.questTemp.Slavetrader.Island);
	while(pchar.questTemp.Slavetrader.Island.Shore == "")
	{
		pchar.questTemp.Slavetrader.Island = GetRandomIslandExcept("Barbados,PuertoRico,Cuba1,Antigua,Jamaica,Curacao,Guadeloupe,Hispaniola1,Hispaniola2,Martinique,Cuba2,Nevis,PortoBello,Trinidad,Tortuga,SentMartin,Cartahena,Maracaibo,Caracas,Cumana,SantaCatalina,Beliz,Panama,Pearl,Tenotchitlan");
		pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomFreeShoreId(pchar.questTemp.Slavetrader.Island);
		if (!isLocationFreeForQuests(pchar.questTemp.Slavetrader.Island)) pchar.questTemp.Slavetrader.Island.Shore = ""; //уж лучше фик куда, чем глюки и конфликты
	}
}

void Slavetrader_SlaveShipsOver(string qName)//просроченный таймер
{
	pchar.quest.Slavetrader_ShipsAttack.over = "yes";
	AddQuestRecord("Slavetrader", "7");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "goaway";
	ChangeOfficersLoyality("bad_all", 1);
	AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}

void Slavetrader_ShoreShipsOver(string qName)//просроченный таймер пинаса
{
	pchar.quest.Slavetrader_ShoreAttack.over = "yes";
	AddQuestRecord("Slavetrader", "7_1");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "goaway_pinas";
	ChangeOfficersLoyality("bad_all", 1);
	AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}

void Slavetrader_CreateSlaveShips(string qName)//создание кораблей в бухте
{
	int i, ShipType, Rank, iShipRank, iCannonType;
	ref sld;
	string Blade, sTemp;
			
	sTemp = pchar.questTemp.Slavetrader.ShipName;//имя корабля
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, false);
    Group_FindOrCreateGroup("Slave_Attack");//создать группу
	Group_SetType("Slave_Attack", "war");//тип группы
	// ==> Контрабандист
	for (i=1; i<=2; i++)//постоянно такая структура
	{
		Rank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
		if(makeint(pchar.rank) >= 20) { iShipRank = 4; }
		if(makeint(pchar.rank) >= 13 && makeint(pchar.rank) < 20) { iShipRank = rand(1)+2; }	
		if(makeint(pchar.rank) >= 7 && makeint(pchar.rank) < 13) { iShipRank = rand(1); }	
		if(makeint(pchar.rank) < 7) { iShipRank = 0; }
		switch (iShipRank)
		{
			case 0:  
				ShipType = SHIP_BRIG;     					
				Rank = 12 + rand(5);
                Blade = "blade15";
				iCannonType = CANNON_TYPE_CANNON_LBS16;
			break; 		
			case 1:  
				ShipType = SHIP_BRIGANTINE;			
				Rank = 15 + rand(5);
                Blade = "blade21";
				iCannonType = CANNON_TYPE_CANNON_LBS16;
			break;
			case 2: 
				ShipType = SHIP_CORVETTE; 				
				Rank = 20 + rand(5);
                Blade = "blade21";
				iCannonType = CANNON_TYPE_CANNON_LBS20;
			break;
			case 3: 
				ShipType = SHIP_FRIGATE;         			
				Rank = 25 + rand(5);
                Blade = "blade21";
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break;
			case 4: 
				ShipType = SHIP_LINESHIP; 						
				Rank = 30 + rand(5);
                Blade = "blade33";
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break;  				
		}
		sld = GetCharacter(NPC_GenerateCharacter("CaptainSlaveAttack_"+i, "citiz_"+(rand(9)+51), "man", "man", Rank, PIRATE, 3, true)); //watch_quest_moment; создание кэпа; можно подбирать по кораблю через sTemp
		if (i == 1)
		{
            FantomMakeCoolSailor(sld, ShipType, "", iCannonType, 70, 50, 50);//создание кораблей
            FantomMakeCoolFighter(sld, Rank, 40, 40, Blade, "pistol2", 30);//создание фантома кэпа
		}
		if (i == 2)
		{
            FantomMakeCoolSailor(sld, SHIP_GALEON_L, sTemp, iCannonType, 70, 50, 50); //создание кораблей
            FantomMakeCoolFighter(sld, Rank, 40, 40, "blade16", "pistol2", 30);//создание фантома кэпа
		}
		
		Group_AddCharacter("Slave_Attack", "CaptainSlaveAttack_"+i);//добавление в группу
		sld.SuperShooter  = true;
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");
		SetCharacterGoods(sld, GOOD_SLAVES, 700 + rand(100));//положить в трюм рабов
		
		sld.ship.Crew.Morale = 50;
		ChangeCrewExp(sld, "Sailors", 70);
		ChangeCrewExp(sld, "Cannoners", 70);
		ChangeCrewExp(sld, "Soldiers", 50);
    }
    // ==> стравливание
	Group_SetGroupCommander("Slave_Attack", "CaptainSlaveAttack_1");
	Group_SetTaskAttack("Slave_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Slave_Attack", PLAYER_GROUP);
	Group_SetAddress("Slave_Attack", pchar.questTemp.Slavetrader.Island, "", "");
	Group_LockTask("Slave_Attack");
			
    // ==> прерывание на убиение эскадры
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Slave_Attack";//какую группу уничтожить
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_SlaveAttack_AfterBattle";//это победа
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";//условие на слинять
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_SlaveAttack_DieHard";//это слинял
	
	AddQuestRecord("Slavetrader", "3_1");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
}

void Slavetrader_SlaveAttack_AfterBattle(string qName)//реакция на победу
{
	Group_DeleteGroup("Slave_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
    pchar.quest.Slavetrader_DieHard.over = "yes";
	pchar.quest.Slavetrader_SlaveShipsOver.over = "yes";
	AddQuestRecord("Slavetrader", "4");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "died";//нода на диалог
	AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}

void Slavetrader_SlaveAttack_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Slave_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	pchar.quest.Slavetrader_SlaveShipsOver.over = "yes";
	AddQuestRecord("Slavetrader", "5");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "goaway";//нода на диалог
	ChangeOfficersLoyality("bad_all",1);
	AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}


void Slavetrader_CreateShoreShips(string qName)//создание пинаса в бухте
{
	int hcrew;
	ref sld;
	string sTemp, sNation;
	
	sNation = pchar.questTemp.Slavetrader.Nation;//нация
	sTemp = pchar.questTemp.Slavetrader.ShipName;//имя корабля
	pchar.questTemp.Slavetrader = "TakeShoreCap";//направление в диалоговый файл	
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, false);
    Group_FindOrCreateGroup("Shore_Attack");//создать группу
	Group_SetType("Shore_Attack", "war");//тип группы
	sld = GetCharacter(NPC_GenerateCharacter("Slaveshorecap", "merch_"+(rand(14)+1), "man", "man", 25, sNation, 3, true));//создание кэпа
	sld.DontRansackCaptain = true;
	FantomMakeCoolSailor(sld, SHIP_PINNACE, sTemp, CANNON_TYPE_CANNON_LBS24, 70, 80, 80);//создание кораблей
	sld.Ship.Mode = "trade";
	sld.Nation = sti(sNation);
	FantomMakeCoolFighter(sld, 30, 50, 50, "blade21", "pistol3", 50);//создание фантома кэпа
	Group_AddCharacter("Shore_Attack", "Slaveshorecap");//добавление в группу
	sld.SuperShooter  = true;
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "MusketsShoot");
	hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantityOverMax(sld, 1.5*hcrew);
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 70);
	ChangeCrewExp(sld, "Cannoners", 70);
	ChangeCrewExp(sld, "Soldiers", 100);
    // ==> стравливание
	Group_SetGroupCommander("Shore_Attack", "Slaveshorecap");
	Group_SetTaskAttack("Shore_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Shore_Attack", PLAYER_GROUP);
	Group_SetAddress("Shore_Attack", pchar.questTemp.Slavetrader.Island, "", "");
	Group_LockTask("Shore_Attack");
			
    // ==> прерывание на убиение эскадры
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Shore_Attack";//какую группу уничтожить
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_ShoreAttack_AfterBattle";//это победа
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";//условие на слинять
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_ShoreAttack_DieHard";//это слинял
	pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
}

void Slavetrader_ShoreAttack_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Shore_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	AddQuestRecord("Slavetrader", "11");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","ла"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "End_quest";
	CloseQuestHeader("Slavetrader");
	ChangeOfficersLoyality("bad_all",1);
}

void Slavetrader_ShoreAttack_AfterBattle(string qName)//реакция на победу
{
	if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
	{
	Group_DeleteGroup("Shore_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
    pchar.quest.Slavetrader_DieHard.over = "yes";
	AddQuestRecord("Slavetrader", "12");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	CloseQuestHeader("Slavetrader");
	pchar.questTemp.Slavetrader = "End_quest";
	}
	else
	{
		characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)].id = "Slaveshorecap"; //полная победа, если захватил, базар в каюте, проверка ИД кэпа
	}
}

void Slavetrader_BrigOver(string qName)//реакция на просроченный таймер
{
	pchar.questTemp.Slavetrader_BrigAttack.over = "yes";//ликвидация бригантины
	AddQuestRecord("Slavetrader", "15");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","ла"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
	CloseQuestHeader("Slavetrader");
	ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 50);
	pchar.questTemp.Slavetrader = "goodbye";
	ChangeOfficersLoyality("bad_all", 1);
}

void Slavetrader_CreateBrig(string qName)//создание бригантины
{
	int iNation = sti(pchar.questTemp.Slavetrader.Nation);
	ref sld;
	string sTemp, sNation;
			
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetraderbrig.Island, false);
    Group_FindOrCreateGroup("Brig_Attack");//создать группу
	Group_SetType("Brig_Attack", "war");//тип группы
	
	sTemp = pchar.questTemp.Slavetraderbrig.ShipName;//имя корабля
	sNation = pchar.questTemp.Slavetrader.Nation;//нация корабля
	sld = GetCharacter(NPC_GenerateCharacter("CapBrigAttack", "off_" + NationShortName(iNation) + "_" + (rand(1)+1), "man", "man", 35, sNation, 3, true));//создание кэпа
	FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, sTemp, CANNON_TYPE_CANNON_LBS16, 100, 100, 100);//создание кораблей
	FantomMakeCoolFighter(sld, 35, 90, 90, "blade26", "pistol3", 90);//создание фантома кэпа
	Group_AddCharacter("Brig_Attack", "CapBrigAttack");//добавление в группу
	sld.SuperShooter  = true;
	sld.AlwaysEnemy = true;
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	
	sld.ship.Crew.Morale = 80;
	ChangeCrewExp(sld, "Sailors", 80);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
 
    // ==> стравливание
	Group_SetGroupCommander("Brig_Attack", "CapBrigAttack");
	Group_SetTaskAttack("Brig_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Brig_Attack", PLAYER_GROUP);
	Group_SetAddress("Brig_Attack", pchar.questTemp.Slavetraderbrig.Island, "", "");
	Group_LockTask("Brig_Attack");
			
    // ==> прерывание на убиение эскадры
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Brig_Attack";//какую группу уничтожить
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_BrigAttack_AfterBattle";//это победа
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";//условие на слинять
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_BrigAttack_DieHard";//это слинял
}

void Slavetrader_BrigAttack_AfterBattle(string qName)//реакция на победу
{
	Group_DeleteGroup("Brig_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.Slavetraderbrig.Island, true);
    pchar.quest.Slavetrader_DieHard.over = "yes";
	pchar.quest.Slavetrader_BrigOver.over = "yes";
	if (CheckCharacterItem(pchar, "letter_1"))
	{
		AddQuestRecord("Slavetrader", "16");
		AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
		pchar.questTemp.Slavetrader = "winbrig";//нода на диалог
	}
	else
	{
		AddQuestRecord("Slavetrader", "17");
	    AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ёл","ла"));
		AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
		pchar.questTemp.Slavetrader = "goodbye_1";//нода на диалог
	}

    AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}

void Slavetrader_BrigAttack_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Brig_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.Slavetraderbrig.Island, true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	pchar.quest.Slavetrader_BrigShipsOver.over = "yes";
	AddQuestRecord("Slavetrader", "15");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","ла"));
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
	CloseQuestHeader("Slavetrader");
	ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 50);
	pchar.questTemp.Slavetrader = "goodbye";//нода на диалог
	ChangeOfficersLoyality("bad_all",1);
}

void Slavetrader_enterSoldiers() //арестовывающие солдеры
{	
	ref sld;
	LAi_SetPlayerType(pchar);
	LAi_group_Delete("EnemyFight");
	pchar.questTemp.Slavetrader = "After_enterSoldiers"; //это состояние квеста, пропишем для следующей ноды
	int iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE - 2; //это ранг от сложности
	int iNation = sti(pchar.questTemp.Slavetrader.Nation);
	for (int i=1; i<=3; i++)
    {
        sld = GetCharacter(NPC_GenerateCharacter("SLSold"+i, "sold_" + NationShortName(iNation) + "_" + (rand(1) + 1), "man", "man", iTemp, iNation, 0, true));
		SetFantomParamFromRank(sld, iTemp, true);         
		LAi_SetWarriorType(sld);
		//LAi_warrior_SetStay(sld, true);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto3");
    }
    sld = GetCharacter(NPC_GenerateCharacter("SLOfficer", "off_" + NationShortName(iNation) + "_" + (rand(1) + 5), "man", "man", iTemp, iNation, 0, true));
	FantomMakeCoolFighter(sld, 25, 100, 100, "topor2", "pistol3", 80);
	sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; //диалоговый файл, из которого говорить будет
	sld.dialog.currentnode = "Slave_arest"; // диалоговый узел
	sld.greeting = "VOICE\" + VoiceGetLanguage() + "\z_arest_01.wav";
    LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}
void Slavetrader_Bonanza(string qName)//cоздание индейцев 
{
	ref sld;
	string sTemp;
	float locx, locy, locz;
	chrDisableReloadToLocation = true;
    for (int i=1; i<=8; i++)
    {
		if (i == 2 || i == 4 || i == 6 || i == 8)
        {
			sld = GetCharacter(NPC_GenerateCharacter("Indian"+i, "indsar1", "man", "man", 25, PIRATE, 0, true));
			sld.indian = "1";
            FantomMakeCoolFighter(sld, 25, 80, 100, "topor2", "pistol3", 100);
		}	
		else
        {
			sld = GetCharacter(NPC_GenerateCharacter("Indian"+i, "indsair2", "man", "man", 35, PIRATE, 0, true));
		}
		sld.indian = "1";
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        GetCharacterPos(pchar, &locx, &locy, &locz);
        sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
        if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
        ChangeCharacterAddressGroup(sld, "Shore18", "goto", sTemp);
    }
	sld = GetCharacter(NPC_GenerateCharacter("Nabuki", "mummy", "man", "man", 25, PIRATE, 0, true));
	sld.indian = "1";
    sld.name 	= FindPersonalName("Nabuki_name");
    sld.lastname = FindPersonalName("Nabuki_lastname");
	FantomMakeCoolFighter(sld, 60, 100, 100, "maquahuitl", "pistol4", 100);
	TakeNItems(sld, "jewelry2", 120+rand(80));
	TakeNItems(sld, "jewelry3", 120+rand(60));
	TakeNItems(sld, "jewelry4", 140+rand(50));
	TakeNItems(sld, "jewelry15", rand(50));
	TakeNItems(sld, "indian11", 1);
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true;
	sld.cirassId = FindItem("cirass5");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	GetCharacterPos(pchar, &locx, &locy, &locz);
	sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
	if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
	ChangeCharacterAddressGroup(sld, "Shore18", "goto", sTemp);
					
    LAi_group_SetLookRadius("EnemyFight", 100);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
}

void Slavetrader_GetHispanShore()//определение бухты, из которой галеон выйдет
{
	pchar.questTemp.Slavetrader.Island = "Caracas";
	pchar.questTemp.Slavetrader.Island.Shore = "Shore21";
	pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("From") + " " + XI_ConvertString("ColonyCaracasGen");
	if (pchar.questTemp.Slavetrader.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
	{
		pchar.questTemp.Slavetrader.Island = "Cumana";
		pchar.questTemp.Slavetrader.Island.Shore = "Shore19";
		pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("From") + " " + XI_ConvertString("ColonyCumanaGen");
	}
}

void Slavetrader_SlaveHalleon_AfterBattle(string qName)//реакция на победу
{
	Group_DeleteGroup("SlaveGalleon");
	pchar.quest.Slavetrader_SlaveGalleonOver.over = "yes";
	AddQuestRecord("Slavetrader", "19");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	ChangeCharacterReputation(pchar, -5);
	pchar.questTemp.Slavetrader = "wingalleon";//нода на диалог
	AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}

void Slavetrader_SlaveGalleonOver(string qName)//просроченный таймер
{
	pchar.quest.Slavetrader_SlaveGalleon.over = "yes";
	AddQuestRecord("Slavetrader", "7_2");
	AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
	pchar.questTemp.Slavetrader = "lostgalleon";
	ChangeOfficersLoyality("bad_all", 1);
	AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}

void Slavetrader_RatCorvette(string qName)//создание корвета крысы
{
	ref sld;
	string sTemp;
			
    Island_SetReloadEnableGlobal("Tortuga", false);
    Group_FindOrCreateGroup("Rat_Attack");//создать группу
	Group_SetType("Rat_Attack", "war");//тип группы
	
	sTemp = pchar.questTemp.Slavetrader.ShipName;//имя корабля
	sld = GetCharacter(NPC_GenerateCharacter("RatCap", "officer_12", "man", "man", 35, FRANCE, 3, true)); //watch_quest_moment; создание кэпа
	sld.name = FindPersonalName("RatCap_name");
	sld.lastname = FindPersonalName("RatCap_lastname");
	FantomMakeCoolSailor(sld, SHIP_CORVETTE, sTemp, CANNON_TYPE_CANNON_LBS20, 85, 90, 85);//создание кораблей
	FantomMakeCoolFighter(sld, 35, 80, 80, "blade26", "pistol5", 70);//создание фантома кэпа
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.Ship.Mode = "pirate";
	Group_AddCharacter("Rat_Attack", "RatCap");//добавление в группу
	sld.SuperShooter  = true;
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
 
    // ==> стравливание
	Group_SetGroupCommander("Rat_Attack", "RatCap");
	Group_SetTaskAttack("Rat_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Rat_Attack", PLAYER_GROUP);
	Group_SetAddress("Rat_Attack", "Tortuga", "", "");
	Group_LockTask("Rat_Attack");
			
    // ==> прерывание на убиение эскадры
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Rat_Attack";//какую группу уничтожить
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_RatAttack_AfterBattle";//это победа
	pchar.quest.Slavetrader_DieHard.win_condition.l1 = "MapEnter";//условие на слинять
    pchar.quest.Slavetrader_DieHard.function = "Slavetrader_RatAttack_DieHard";//это слинял
	pchar.quest.Slavetrader_RatCorvetteOver.over = "yes";
}

void Slavetrader_RatAttack_AfterBattle(string qName)//реакция на победу
{
	Group_DeleteGroup("Rat_Attack");
	Island_SetReloadEnableGlobal("Tortuga", true);
    pchar.quest.Slavetrader_DieHard.over = "yes";
	AddQuestRecord("Slavetrader", "21_12");
	pchar.questTemp.Slavetrader = "wincorvette";//нода на диалог
	AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}

void Slavetrader_RatAttack_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Rat_Attack");
    Island_SetReloadEnableGlobal("Tortuga", true);
    pchar.quest.Slavetrader_AfterBattle.over = "yes";
	AddQuestRecord("Slavetrader", "21_11");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase(StringFromKey("SexPhrase_19"),StringFromKey("SexPhrase_20")));
	pchar.questTemp.Slavetrader = "lostcorvette";//нода на диалог
	ChangeOfficersLoyality("bad_all", 1);
	AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}

void Slavetrader_RatCorvetteOver(string qName)//просроченный таймер корвета
{
	pchar.quest.Slavetrader_RatAttack.over = "yes";
	AddQuestRecord("Slavetrader", "21_10");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
	pchar.questTemp.Slavetrader = "lostcorvette";
	ChangeOfficersLoyality("bad_all", 1);
	AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}


void Slavetrader_GetEscapeShore()//выбираем маяк, куда беглых рабов запхнем
{
	switch (rand(9))
	{
		case 0:
			pchar.questTemp.Slavetrader.EsIsland = "Barbados";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak2";
			pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("off_the_coast") + " " + XI_ConvertString("BarbadosGen");
			break;
		case 1:
			pchar.questTemp.Slavetrader.EsIsland = "Guadeloupe";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak4";
			pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("off_the_coast") + " " + XI_ConvertString("GuadeloupeGen");
			break;
		case 2:
			pchar.questTemp.Slavetrader.EsIsland = "Cuba1";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak9";
			pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("not_far_from") + " " + XI_ConvertString("ColonySantiagoGen");
			break;
		case 3:
			pchar.questTemp.Slavetrader.EsIsland = "Cuba2";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak10";
			pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("not_far_from") + " " + XI_ConvertString("ColonyHavanaGen");
			break;
		case 4:
			pchar.questTemp.Slavetrader.EsIsland = "Tortuga";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak6";
			pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("off_the_coast") + " " + XI_ConvertString("TortugaGen");
			break;
		case 5:
			pchar.questTemp.Slavetrader.EsIsland = "Trinidad";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak1";
			pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("off_the_coast") + " " + XI_ConvertString("TrinidadGen");
			break;
		case 6:
			pchar.questTemp.Slavetrader.EsIsland = "Nevis";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak5";
			pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("off_the_coast") + " " + XI_ConvertString("NevisGen");
			break;
		case 7:
			pchar.questTemp.Slavetrader.EsIsland = "Hispaniola1";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak8";
			pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("not_far_from") + " " + XI_ConvertString("ColonySantoDomingoGen");
			break;
		case 8:
			pchar.questTemp.Slavetrader.EsIsland = "Hispaniola2";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak7";
			pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("not_far_from") + " " + XI_ConvertString("ColonyPortPaxGen");
			break;
		case 9:
			pchar.questTemp.Slavetrader.EsIsland = "Cartahena";
			pchar.questTemp.Slavetrader.Island.Shore = "Mayak11";
			pchar.questTemp.SlavetraderAreal.add = XI_ConvertString("not_far_from") + " " + XI_ConvertString("ColonyCartahenaGen");
			break;
	}
}

void Slavetrader_EscapeSlaveInShore(string qName)
{
	SetBan("Looting,Exchange", 1);
	string sShore, sAnime, sTemp;
	ref sld;
	int iTemp, i;
	float locx, locy, locz;
	sShore = pchar.questTemp.Slavetrader.Island.Shore;
    LAi_group_Delete("EnemyFight");
	chrDisableReloadToLocation = true; //закроем локацию
	GetCharacterPos(pchar, &locx, &locy, &locz);
	//наши
	arrayNPCModelHow = 0;
    for (i=1; i<=3; i++)
    {
        iTemp = 10 + rand(10);
		sld = GetCharacter(NPC_GenerateCharacter("OwnCrew_"+i, "citiz_"+(rand(9)+31), "man", "man", iTemp, sti(pchar.nation), 0, true));
		SetNPCModelUniq(sld, "sailor", MAN); //TODO: по патенту
        LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
		if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
        ChangeCharacterAddressGroup(sld, sShore, "goto", sTemp);
		sld.DontClearDead = true;
    }
	//враги
	int iMassive;
	string slaves[8];
	slaves[0] = "slave_1";
	slaves[1] = "slave_2";
	slaves[2] = "slave_3";
	slaves[3] = "slave_4";
	slaves[4] = "prison_1";
	slaves[5] = "prison_3";
	slaves[6] = "pirate_11";
	slaves[7] = "officer_6";
	i = 0;
	while(i < 8)
	{
		iMassive = rand(7);
		if(slaves[iMassive] != "")
		{
			sAnime = "man";
			if(HasSubStr(slaves[iMassive],"slave")) sAnime = "man";
			iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 10;
			sld = GetCharacter(NPC_GenerateCharacter("EscapeSlave_"+i, slaves[iMassive], "man", sAnime, iTemp, PIRATE, -1, true));
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, sShore, "goto", "goto"+(21+i));
			i++;
			slaves[iMassive] = "";
			sld.DontClearDead = true;
		}
    }
	sld = GetCharacter(NPC_GenerateCharacter("Jimmy", "Tamango", "man", "man", 35, PIRATE, 0, true));
	sld.name 	= FindPersonalName("Jimmy_name");
	sld.lastname = "";
	FantomMakeCoolFighter(sld, 35, 100, 100, "topor2", "pistol3", 80);
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.cirassId = FindItem("cirass4");
	sld.DontClearDead = true;
	LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, "EnemyFight");
    GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, sShore, "goto", "goto30");
		
    LAi_group_SetLookRadius("EnemyFight", 100);
    LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Slavetrader_EscapeSlaves_Win");
}

void Slavetrader_Slavewoman()
{
	SetBan("Looting,Exchange", 0);
	LAi_group_Delete("EnemyFight");
	string sTemp, sAnime;
	ref sld = characterFromId("Slavewoman");
	LAi_SetPlayerType(pchar);
	SetCharacterRemovable(sld, false);
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "goto", "goto2", "none", "", "", "", 15.0);
	sld.lifeday = 0;
	for (int i=10; i<=25; i++)
	{
		sTemp = GetRandSubString("slave_1,slave_2,slave_3,slave_4,prison_1,prison_3,pirate_11,officer_6");
		sAnime = "man";
		if(HasSubStr(sTemp,"slave")) sAnime = "man";
		sld = GetCharacter(NPC_GenerateCharacter("SlaveShor_"+i, sTemp, "man", sAnime, 10, PIRATE, 0, true));
		FantomMakeCoolFighter(sld, 25, 100, 100, "", "", 80);
		ChangeCharacterAddressGroup(sld, pchar.questTemp.Slavetrader.Island.Shore, "goto",  "goto"+i);
		sld = characterFromID("SlaveShor_"+i);
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);
		LAi_SetCitizenTypeNoGroup(sld);
		sld.lifeday = 0;//на всякий случай
		LAi_CharacterDisableDialog(sld);
	}
	SetCharacterGoods(pchar, GOOD_SLAVES, 1000 + rand(100));
	sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
	AddQuestRecord("Slavetrader", "22");
	AddQuestUserData("Slavetrader", "sQty", FindSlavesWithCaseString(sti(sTemp), "Acc"));
	pchar.questTemp.Slavetrader = "escapeslave_win";
	ChangeCharacterReputation(pchar, -1);
	OfficersReaction("bad");
    AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}

void Slavetrader_CreateLineShips(string qName)//создание линейных кораблей
{
	int i;
	ref sld;
	string sTemp;

	Island_SetReloadEnableGlobal("Cuba2", false);
    Group_FindOrCreateGroup("Havana_Attack");//создать группу
	Group_SetType("Havana_Attack", "war");//тип группы
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);//ссорим ГГ и испанцев
	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("HavanaAttack_"+i, "navy_off_spa_5", "man", "man", 35, SPAIN, 3, true));//создание кэпа
		FantomMakeCoolSailor(sld, SHIP_LINESHIP, "", CANNON_TYPE_CANNON_LBS32, 90, 95, 90);//создание кораблей
		FantomMakeCoolFighter(sld, 45, 100, 100, "blade28", "pistol5", 100);//создание фантома кэпа
		Group_AddCharacter("Havana_Attack", "HavanaAttack_"+i);//добавление в группу
		sld.SuperShooter  = true;
		sld.AlwaysEnemy = true;
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "GunProfessional");
		
		sld.ship.Crew.Morale = 100;
		ChangeCrewExp(sld, "Sailors", 100);
		ChangeCrewExp(sld, "Cannoners", 100);
		ChangeCrewExp(sld, "Soldiers", 100);
    }
    // ==> стравливание
	Group_SetGroupCommander("Havana_Attack", "HavanaAttack_1");
	Group_SetTaskAttack("Havana_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Havana_Attack", PLAYER_GROUP);
	Group_SetAddress("Havana_Attack", "Cuba2", "", "");
	Group_LockTask("Havana_Attack");
	bQuestDisableMapEnter = true; //запрещаем выход на глобу, чтоб не взяли форт до потопления	
    // ==> прерывание на убиение эскадры
    pchar.quest.Slavetrader_AfterBattle.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.Slavetrader_AfterBattle.win_condition.l1.group = "Havana_Attack";//какую группу уничтожить
	pchar.quest.Slavetrader_AfterBattle.function = "Slavetrader_HavanaAttack_AfterBattle";//это победа
	pchar.quest.Slavetrader_DieHardHavana.win_condition.l1 = "MapEnter";//не лезь на карту
    pchar.quest.Slavetrader_DieHardHavana.function = "Slavetrader_HavanaAttack_DieHard";//теперь пеняй на себя
	AddQuestRecord("Slavetrader", "25");
}

void Slavetrader_HavanaAttack_AfterBattle(string qName)//реакция на победу
{
	bQuestDisableMapEnter = false;
	Group_DeleteGroup("Havana_Attack");
	Island_SetReloadEnableGlobal("Cuba2", true);
	AddQuestRecord("Slavetrader", "26");
}

void Slavetrader_HavanaAttack_DieHard(string qName)//если надумал починиться
{
	pchar.quest.Slavetrader_HavanaOver.over = "yes";//снимем таймер
	characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "CAPTURE_Main";//снимем ноду губеру
	AddQuestRecord("Slavetrader", "26_1");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Slavetrader");
	pchar.questTemp.Slavetrader = "End_quest";
}

void Slavetrader_HavanaOver(string qName)//просроченный таймер
{
	pchar.quest.Slavetrader_HavanaAttack.over = "yes";
	AddQuestRecord("Slavetrader", "28");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","ла"));
	ChangeOfficersLoyality("bad_all", 1);
	CloseQuestHeader("Slavetrader");
	characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "CAPTURE_Main";
	pchar.questTemp.Slavetrader = "End_quest";
}

void Slavetrader_FiveTSlavesOver(string qName)//просроченный таймер
{
	ChangeCharacterHunterScore(pchar, "spahunter", 100);
	ChangeCharacterHunterScore(pchar, "holhunter", 100);
	ChangeCharacterHunterScore(pchar, "frahunter", 100);
	ChangeCharacterHunterScore(pchar, "enghunter", 100);
	pchar.questTemp.Slavetrader = "End_quest_bad";
	AddQuestRecord("Slavetrader", "30");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Slavetrader");
	RemoveLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}

void Slavetrader_HavanaSeekOver(string qName)//просроченный таймер
{
	ChangeCharacterHunterScore(pchar, "spahunter", 100);
	ChangeCharacterHunterScore(pchar, "holhunter", 100);
	ChangeCharacterHunterScore(pchar, "frahunter", 100);
	ChangeCharacterHunterScore(pchar, "enghunter", 100);
	pchar.questTemp.Slavetrader = "End_quest_bad";
	AddQuestRecord("Slavetrader", "31");
	AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Slavetrader");
	RemoveLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
}

void Slavetrader_UsurerEscape(string qName)//меняем модель ростовщика
{
	ref sld = characterFromId(pchar.questTemp.Slavetrader.UsurerId);
	sld.name = FindPersonalName("Slavetrader_name");
	sld.lastname = FindPersonalName("Slavetrader_lastname");
	sld.model = "trader_8";
	LocatorReloadEnterDisable(pchar.questTemp.Slavetrader.Cityname, "reload8_back", false);
}

//-->малява, грабеж торгашей
void Deliver_CreateTraderShips(string qName)//создание торговых кораблей
{
	int i, ShipType, Rank, iShipRank, iCannonType;
	int iGoods, iSpace;
	ref sld;
	string sTemp1, sTemp2, sNation;
			
	sTemp1 = pchar.questTemp.jailCanMove.Deliver.ShipName1;//имя корабля
	sTemp2 = pchar.questTemp.jailCanMove.Deliver.ShipName2;//имя корабля
	sNation = pchar.questTemp.jailCanMove.Deliver.Nation;
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, false);
    Group_FindOrCreateGroup("Trade_Attack");//создать группу
	Group_SetType("Trade_Attack", "trade");//тип группы
	for (i=1; i<=2; i++)
	{
		if(makeint(pchar.rank) >= 20) { iShipRank = 3; }
		if(makeint(pchar.rank) >= 15 && makeint(pchar.rank) < 20) { iShipRank = rand(1)+2; }	
		if(makeint(pchar.rank) >= 10 && makeint(pchar.rank) < 15) { iShipRank = rand(1)+1; }	
		if(makeint(pchar.rank) >= 4 && makeint(pchar.rank) < 10) { iShipRank = rand(1); }	
		if(makeint(pchar.rank) < 4) { iShipRank = 0; }
		switch (iShipRank)
		{
			case 0:  
				ShipType = SHIP_BARQUE;     					
				Rank = 12 + rand(5);
				iCannonType = CANNON_TYPE_CANNON_LBS12;
			break; 		
			case 1:  
				ShipType = SHIP_FLEUT;			
				Rank = 18 + rand(5);
				iCannonType = CANNON_TYPE_CANNON_LBS20;
			break;
			case 2: 
				ShipType = SHIP_PINNACE; 				
				Rank = 25 + rand(5);
				iCannonType = CANNON_TYPE_CANNON_LBS24;
			break;
			case 3: 
				ShipType = SHIP_GALEON_H;         			
				Rank = 30 + rand(5);
				iCannonType = CANNON_TYPE_CANNON_LBS32;
			break; 			
		}
		sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_"+i, "merch_"+(rand(14)+1), "man", "man", Rank, sNation, 3, true));//создание кэпа
		if (i == 1)
		{
		    FantomMakeCoolSailor(sld, ShipType, sTemp1, iCannonType, 48, 35, 35);//создание кораблей
		}
		if (i == 2)
		{
		    FantomMakeCoolSailor(sld, ShipType, sTemp2, iCannonType, 44, 30, 30);//создание кораблей
		}
		sld.Ship.Mode = "trade";
		iGoods = sti(pchar.questTemp.jailCanMove.Deliver.Goods);
		iSpace = GetCharacterFreeSpace(sld, iGoods);
		iSpace = makeint(iSpace/2 + rand(iSpace/2));
		SetCharacterGoods(sld, iGoods, iSpace);
		Group_AddCharacter("Trade_Attack", "CaptainAttack_"+i);//добавление в группу
		sld.AlwaysEnemy = true;
		sld.ship.Crew.Morale = 60;
		ChangeCrewExp(sld, "Sailors", 50);
		ChangeCrewExp(sld, "Cannoners", 50);
		ChangeCrewExp(sld, "Soldiers", 100);
    }
    // ==> стравливание
	Group_SetGroupCommander("Trade_Attack", "CaptainAttack_1");
	Group_SetTaskAttack("Trade_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Trade_Attack", PLAYER_GROUP);
	Group_SetAddress("Trade_Attack", pchar.questTemp.jailCanMove.Deliver.Island, "Quest_Ships", "Quest_Ship_" + (3+ rand(4)));
	Group_LockTask("Trade_Attack");
			
    // ==> прерывание на убиение эскадры
    pchar.quest.jailCanMoveDeliver_AfterBattle.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.jailCanMoveDeliver_AfterBattle.win_condition.l1.group = "Trade_Attack";//какую группу уничтожить
	pchar.quest.jailCanMoveDeliver_AfterBattle.function = "Deliver_AfterBattle";//это победа
	pchar.quest.jailCanMoveDeliver_DieHard.win_condition.l1 = "MapEnter";//условие на слинять
    pchar.quest.jailCanMoveDeliver_DieHard.function = "Deliver_DieHard";//это слинял
	pchar.quest.Deliver_TraderShipsOver.over = "yes";
	AddQuestRecord("MalyavaDeliver", "6");
	AddQuestUserData("MalyavaDeliver", "sSex", GetSexPhrase("ёл","ла"));
	AddQuestUserData("MalyavaDeliver", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
	AddQuestUserData("MalyavaDeliver", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
}

void Deliver_AfterBattle(string qName)//реакция на победу
{
	Group_DeleteGroup("Trade_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_DieHard.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("MalyavaDeliver");
}

void Deliver_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Trade_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_AfterBattle.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("MalyavaDeliver");
}

void Deliver_TraderShipsOver(string qName)//просроченный таймер торговых кораблей и кидалова - 2 в 1
{
	pchar.quest.jailCanMoveDeliver_ShipsAttack.over = "yes";
	AddQuestRecord("MalyavaDeliver", "7");
	AddQuestUserData("MalyavaDeliver", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("MalyavaDeliver", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
	AddQuestUserData("MalyavaDeliver", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("MalyavaDeliver");
}
//<--малява, грабеж торгашей

//-->малява, перехват курьера
void Deliver_CreateCureerShips(string qName)//создание курьерского корабля
{
	int i, ShipType, Rank, iShipRank, iCannonType;
	int iNation = sti(pchar.questTemp.jailCanMove.Deliver.Nation);
	ref sld;
	string Blade, sTemp, sNation;
	
	sTemp = pchar.questTemp.jailCanMove.Deliver.ShipName;//имя корабля
	sNation = pchar.questTemp.jailCanMove.Deliver.Nation;
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, false);
    Group_FindOrCreateGroup("Cureer_Attack");//создать группу
	Group_SetType("Cureer_Attack", "war");//тип группы
	if(makeint(pchar.rank) >= 20) { iShipRank = 3; }
	if(makeint(pchar.rank) >= 12 && makeint(pchar.rank) < 20) { iShipRank = 2; }	
	if(makeint(pchar.rank) >= 5 && makeint(pchar.rank) < 12) { iShipRank = 1; }	
	if(makeint(pchar.rank) < 5) { iShipRank = 0; }
	switch (iShipRank)
	{
		case 0:  
			ShipType = SHIP_SCHOONER;     					
			Rank = 12 + rand(5);
			Blade = "blade15";
			iCannonType = CANNON_TYPE_CANNON_LBS8;
		break; 		
		case 1:  
			ShipType = SHIP_BRIGANTINE;			
			Rank = 17 + rand(5);
			Blade = "blade34";
			iCannonType = CANNON_TYPE_CANNON_LBS16;
		break;
		case 2: 
			ShipType = SHIP_CORVETTE; 				
			Rank = 22 + rand(5);
			Blade = "blade26";
			iCannonType = CANNON_TYPE_CANNON_LBS20;
		break;
		case 3: 
			ShipType = SHIP_FRIGATE;         			
			Rank = 30 + rand(5);
			Blade = "blade28";
			iCannonType = CANNON_TYPE_CANNON_LBS24;
		break; 			
	}
	sld = GetCharacter(NPC_GenerateCharacter("CureerAttack", "officer_1", "man", "man", Rank, sNation, 3, true));//создание кэпа; ниже обновление модели
	FantomMakeCoolSailor(sld, ShipType, sTemp, iCannonType, 75, 50, 50);//создание кораблей
	FantomMakeCoolFighter(sld, Rank, 40, 40, Blade, "pistol3", 40);//создание фантома кэпа
	SetCaptanModelByEncType(sld, "war");
	Group_AddCharacter("Cureer_Attack", "CureerAttack");//добавление в группу
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	SetCharacterPerk(sld, "MusketsShoot");
	sld.AlwaysEnemy = true;
  
    // ==> стравливание
	Group_SetGroupCommander("Cureer_Attack", "CureerAttack");
	Group_SetTaskAttack("Cureer_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Cureer_Attack", PLAYER_GROUP);
	Group_SetAddress("Cureer_Attack", pchar.questTemp.jailCanMove.Deliver.Island, "Quest_Ships", "Quest_Ship_" + (3+ rand(4)));
	Group_LockTask("Cureer_Attack");
			
    // ==> прерывание на убиение эскадры
    pchar.quest.jailCanMoveDeliver_AfterBattleC.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.jailCanMoveDeliver_AfterBattleC.win_condition.l1.group = "Cureer_Attack";//какую группу уничтожить
	pchar.quest.jailCanMoveDeliver_AfterBattleC.function = "DeliverC_AfterBattle";//это победа
	pchar.quest.jailCanMoveDeliver_DieHardC.win_condition.l1 = "MapEnter";//условие на слинять
    pchar.quest.jailCanMoveDeliver_DieHardC.function = "DeliverC_DieHard";//это слинял
	pchar.quest.Deliver_CureerShipsOver.over = "yes";
	AddQuestRecord("MalyavaDeliver", "9");
	AddQuestUserData("MalyavaDeliver", "sSex", GetSexPhrase("ёл","ла"));
	AddQuestUserData("MalyavaDeliver", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
}

void DeliverC_AfterBattle(string qName)//реакция на победу
{
	Group_DeleteGroup("Cureer_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_DieHardC.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("MalyavaDeliver");
}

void DeliverC_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Cureer_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.jailCanMove.Deliver.Island, true);
    pchar.quest.jailCanMoveDeliver_AfterBattleC.over = "yes";
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("MalyavaDeliver");
}

void Deliver_CureerShipsOver(string qName)//просроченный таймер курьерского корабля
{
	pchar.quest.jailCanMoveDeliver_ShipsCAttack.over = "yes";
	AddQuestRecord("MalyavaDeliver", "10");
	AddQuestUserData("MalyavaDeliver", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("MalyavaDeliver", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("MalyavaDeliver");
}
//<--малява, перехват курьера

//-->малява, кидалово
void Deliver_lay(string qName)//пришли - а нету никого
{
	pchar.quest.Deliver_TraderShipsOver.over = "yes";
	AddQuestRecord("MalyavaDeliver", "11");
	AddQuestUserData("MalyavaDeliver", "sSex", GetSexPhrase("ёл","ла"));
	AddQuestUserData("MalyavaDeliver", "sSex1", GetSexPhrase("","а"));
	AddQuestUserData("MalyavaDeliver", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
	AddQuestUserData("MalyavaDeliver", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
	DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
	CloseQuestHeader("MalyavaDeliver");
}
//<--малява, кидалово

//zagolski - побег офицера
void mOfficer_fc(string qName)
{
	if (IsEntity(&worldMap))
    {
		ref sld = &Characters[sti(Pchar.questTemp.MunityOfficerIDX)];
		if(sti(sld.Payment) == true)
		{
			if (sti(sld.ship.type) != SHIP_NOTUSED)
			{
				Log_SetStringToLog(XI_ConvertString("Officer") + " " + GetFullName(sld) + XI_ConvertString("left you2") + sld.ship.name + "");
				Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			else
			{
		Log_SetStringToLog(XI_ConvertString("Officer") + " " + GetFullName(sld) + XI_ConvertString("left you3") + pchar.ship.name + "");

		if (GetCrewQuantity(pchar) > 0)
		{
			AddCharacterExpToSkill(PChar, "Leadership", 200);
			MunityOnShip("ShipMunity");
				}
				else Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			sld.LifeDay = 0;
			RemovePassenger(Pchar, sld);
		}
		else Pchar.questTemp.MunityOfficerIDX.begin = "0";
	}
	else
	{
		pchar.quest.mOfficer_fc2.win_condition.l1 = "MapEnter";
		pchar.quest.mOfficer_fc2.function    = "mOfficer_fc2";
	}
}

void mOfficer_fc2(string qName)
{
	ref sld = &Characters[sti(Pchar.questTemp.MunityOfficerIDX)];
		if(sti(sld.Payment) == true)
		{
			if (sti(sld.ship.type) != SHIP_NOTUSED)
			{
				Log_SetStringToLog(XI_ConvertString("Officer") + " " + GetFullName(sld) + XI_ConvertString("left you2") + sld.ship.name + "");
				Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			else
			{
	Log_SetStringToLog(XI_ConvertString("Officer") + " " + GetFullName(sld) + XI_ConvertString("left you3") + pchar.ship.name + "");

        if (GetCrewQuantity(pchar) > 0)
	{
		AddCharacterExpToSkill(PChar, "Leadership", 200);
		MunityOnShip("ShipMunity");
				}
				else Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			sld.LifeDay = 0;
			RemovePassenger(Pchar, sld);
		}
		else Pchar.questTemp.MunityOfficerIDX.begin = "0";
}

//zagolski. битва в бухте по квесту шарпа
void sharp_pre(string qName)
{
	chrDisableReloadToLocation = true;
	AddQuestRecord("SharpPearl_SeekSpy", "6");
	CloseQuestHeader("SharpPearl_SeekSpy");
	SetTimerFunction("SeaPearl_SharpSeekSpy_SharpRevenge", 0, 1, 0); // через месяц Шарп начнет охоту на глобалке
	LAi_group_Delete("EnemyFight");
	ref sld;
	arrayNPCModelHow = 0;
	for (int i=1; i<=5; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("sh_pre_"+i, "citiz_"+(rand(9)+51), "man", "man", 15, PIRATE, 0, true));
		SetNPCModelUniq(sld, "mercenary", MAN);
		FantomMakeCoolFighter(sld, 15, 70, 70, RandPhraseSimple("blade21","blade31"), RandPhraseSimple("pistol3", "pistol6"), 20);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, "Shore9", "goto", "goto4");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
	}
}

// zagolski - опасный груз
void zpq_sld1_fc(string qName)
{
	ref sld;
	LAi_group_Delete("EnemyFight");
	LAi_LocationFightDisable(loadedLocation, true);

	arrayNPCModelHow = 0;
    for (int i=1; i<=3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("qp2_"+i, "pirate_"+(rand(15)+1), "man", "man", 20, PIRATE, 0, true)); //watch_quest_moment; мб наёмников? ниже они кулфайтеры
		SetNPCModelUniq(sld, "pirate", MAN);
		sld.Dialog.Filename = "Quest\zpq_dialog.c";
		sld.dialog.currentnode = "zpq_sld2";
		sld.greeting = "Enc_Waiker";
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		ChangeCharacterAddressGroup(sld, "Cumana_ExitTown", "goto", "goto5");
		if (i == 1)
		{
			FantomMakeCoolFighter(sld, 20, 90, 90, "blade31", "pistol6", 50);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
			sld.cirassId = FindItem("cirass2");
			GiveItem2Character(sld, "jewelry4");
			AddMoneyToCharacter(sld, 1000+rand(1000));
			sld.SaveItemsForDead  = true;
			sld.DontClearDead = true;
			if (GetCharacterItem(pchar, "map_full") == 0)
			{
				if (GetCharacterItem(pchar, "map_part1") == 0) GiveItem2Character(sld, "map_part1");
				else
				{
					if (GetCharacterItem(pchar, "map_part2") == 0) GiveItem2Character(sld, "map_part2");
				}
			}
			else GiveItem2Character(sld, "map_normal");
		}
		else
		{
			FantomMakeCoolFighter(sld, 15, 55, 55, "blade7", "pistol3", 20);
			LAi_ActorFollow(sld, characterFromId("qp2_1"), "", -1);
		}
	}		
}

void zpq_seaBattle(string qName)
{
	LAi_group_Delete("EnemyFight");
	ref sld = GetCharacter(NPC_GenerateCharacter("zpqCaptain", "citiz_21", "man", "man", 40, PIRATE, 1, true)); //watch_quest_moment; TODO: уникальную
	FantomMakeCoolFighter(sld, 40, 65, 55, "blade23", "pistol3", 75);
	FantomMakeCoolSailor(sld, SHIP_LUGGERQUEST, FindPersonalName("zpqCaptain_ship"), CANNON_TYPE_CULVERINE_LBS12, 75, 65, 55);
    sld.name 	= FindPersonalName("zpqCaptain_name");
    sld.lastname = FindPersonalName("zpqCaptain_lastname");
	sld.AlwaysSandbankManeuver = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	SetCharacterPerk(sld, "MusketsShoot");

	sld.ship.Crew.Morale = 75;
	ChangeCrewExp(sld, "Sailors", 75);
	ChangeCrewExp(sld, "Cannoners", 85);
	ChangeCrewExp(sld, "Soldiers", 85);

	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	
	LAi_group_MoveCharacter(sld, "EnemyFight");
	Group_AddCharacter("zpq_Group", "zpqCaptain");			
	Group_SetType("zpq_Group", "Pirate");
	Group_SetGroupCommander("zpq_Group", "zpqCaptain");
	Group_SetAddress("zpq_Group", "Cumana", "quest_ships", "quest_ship_4");
	Group_SetTaskAttack("zpq_Group", PLAYER_GROUP);
	Group_LockTask("zpq_Group");
}

//zagolski. начальный квест пирата
void pirateStartQuest_Begin_AddQuestMarks()
{
    AddLandQuestMark_Main(CharacterFromID("LeFransua_Mayor"), "pSQ");
    AddLandQuestMark_Main(CharacterFromID("Edward Mansfield"), "pSQ");
    AddLandQuestMark_Main(CharacterFromID("Richard_Soukins"), "pSQ");

    AddMapQuestMark_Major("LeFransua_town", "pSQ", "pSQ_Begin_WDMQuestMarkCondition");
    AddMapQuestMark_Major("LaVega_town", "pSQ", "pSQ_Begin_WDMQuestMarkCondition");
    AddMapQuestMark_Major("PuertoPrincipe_town", "pSQ", "pSQ_Begin_WDMQuestMarkCondition");
}

void pirateStartQuest_Begin_DelQuestMarks()
{
    RemoveLandQuestMark_Main(CharacterFromID("LeFransua_Mayor"), "pSQ");
    RemoveLandQuestMark_Main(CharacterFromID("Edward Mansfield"), "pSQ");
    RemoveLandQuestMark_Main(CharacterFromID("Richard_Soukins"), "pSQ");

    RemoveMapQuestMark("LeFransua_town", "pSQ");
    RemoveMapQuestMark("LaVega_town", "pSQ");
    RemoveMapQuestMark("PuertoPrincipe_town", "pSQ");
}

void pirateStartQuest_Smuggler_fc(string qName)
{
	chrDisableReloadToLocation = true;
	LAi_SetFightMode(pchar, false);
    LAi_LockFightMode(pchar, true);
    SetBan("Looting", 1);

	int iRank = makeint(sti(pchar.rank)+MOD_SKILL_ENEMY_RATE/2);
	int iNation = sti(pchar.questTemp.pirateStartQuest.City2Nation);
	ref sld;

    ref off_chr = GetCharacter(NPC_GenerateCharacter("psq1_off", "off_"+NationShortName(iNation)+"_"+(rand(1)+5), "man", "man", iRank, iNation, 0, true));
    SetFantomParamFromRank(off_chr, iRank, true);
    LAi_SetActorType(off_chr);
    LAi_group_MoveCharacter(off_chr, "pirateStartQuest_SmugglerPatrol_group");
    off_chr.Dialog.Filename = "Quest\pSQ_Smuggler_dialog.c";
    off_chr.Dialog.CurrentNode = "pirateStartQuest_Patrol1";
    off_chr.greeting = "Gr_Costal_Guards";
    ChangeCharacterAddressGroup(off_chr, pchar.location, "goto", LAi_FindNPCLocator("goto"));

    for (int i=1; i<=3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("psq1_"+i, "sold_"+NationShortName(iNation)+"_"+(rand(4)+1), "man", "man", iRank, iNation, 0, true));
		SetFantomParamFromRank(sld, iRank, true);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "pirateStartQuest_SmugglerPatrol_group");
        LAi_warrior_SetCommander(sld, off_chr);
        LAi_warrior_DialogEnable(sld, false);
		ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNPCLocator("goto"));
	}

    LAi_ActorDialog(off_chr, Pchar, "", 35.0, 1.0);
}

void pirateStartQuest_Smuggler_patrol_dead(string qName)
{
	LAi_group_Delete("pirateStartQuest_Smuggler_group");
	DoQuestFunctionDelay("pirateStartQuest_Smuggler_patrol_note", 1.2);
}

void pirateStartQuest_Smuggler_group_dead(string qName)
{
//    if (GetCharacterSkill(pchar, SKILL_SNEAK) < 75)
    if (!PlayerRPGCheck_Skill(SKILL_SNEAK, 75, false))
    {
        DoQuestFunctionDelay("pirateStartQuest_Smuggler_fc", 1.5);
    }
    else
    {
        LAi_group_Delete("pirateStartQuest_Smuggler_group");
        DoQuestCheckDelay("OpenTheDoors", 1.2);
    }
}

void pirateStartQuest_Smuggler_patrol_note(string qName)
{
	chrDisableReloadToLocation = false;
	bDisableFastReload = false;
	SetBan("Looting", 0);

	LAi_group_Delete("pirateStartQuest_SmugglerPatrol_group");
	
    AddQuestRecord("pSQ", "4");
}

void pirateStartQuest_Smuggler_patrol_note_NoFight(string qName)
{
	chrDisableReloadToLocation = false;
    bDisableFastReload = false;
    SetBan("Looting", 0);

    AddQuestRecord("pSQ", "9");
}

void pirateStartQuest_Smuggler_fc2(string qName)
{
    LAi_group_SetRelation("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	int iRank = makeint(sti(pchar.rank)+MOD_SKILL_ENEMY_RATE/2);
	ref sld;
    for (int i=1; i<=3; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("psq2_"+i, "citiz_"+((i-1)*3+rand(2)+21), "man", "man", iRank, PIRATE, -1, true));
		SetFantomParamFromRank(sld, iRank, true);
		sld.Dialog.Filename = "Quest\pSQ_Smuggler_dialog.c";
		sld.dialog.currentnode = "First time";
		sld.greeting = "Gr_Smuggler_OnShore";
		LAi_SetImmortal(sld, true);
		// LAi_SetGuardianType(sld);
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, true);
        LAi_warrior_SetStay(sld, true);

		LAi_group_MoveCharacter(sld, "pirateStartQuest_Smuggler_group");
		ChangeCharacterAddressGroup(sld, pchar.questTemp.pirateStartQuest.Shore, "Smugglers", "Smuggler0" + i);
		AddLandQuestMark_Main(sld, "pSQ");
	}
}

void pirateStartQuest_Smuggler_RemoveSmugglers(string qName)
{
    int cn, i;

    pchar.questTemp.pirateStartQuest = "0";
    CloseQuestHeader("pSQ");

    RemoveGeometryFromLocation(pchar.questTemp.pirateStartQuest.Shore, "smg");

    for (i=1; i<=3; i++)
    {
        cn = GetCharacterIndex("psq2_"+i);
        if (cn != -1)
        {
            characters[cn].lifeDay = 0;
        }
    }

    pchar.quest.pirateStartQuest_Smuggler_fc.over = "yes";
    pchar.quest.pirateStartQuest_Smuggler_fc2.over = "yes";
    RemoveLandQuestMark_Main(CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId), "pSQ");
}

void pirateStartQuest_Smuggler_LoadSlaves()
{
    LAi_SetActorType(pchar);

    SetLaunchFrameFormParam(StringFromKey("InfoMessages_23"), "Run_Function", 1.0, 4.0);
    SetLaunchFrameRunFunctionParam("pirateStartQuest_Smuggler_LoadSlaves_ContinueDialog", 0.2);

    DoQuestCheckDelay("LaunchFrameForm", 0.1);
}

void pirateStartQuest_Smuggler_LoadSlaves_ContinueDialog()
{
    WaitDate("", 0, 0, 0, 2, 0);
    RefreshLandTime();

    string charId = "psq2_" + 1;
    if (CheckAttribute(&TEV, "pirateStartQuest_SmugglerCharId"))
    {
        charId = TEV.pirateStartQuest_SmugglerCharId;
        DeleteAttribute(&TEV, "pirateStartQuest_SmugglerCharId");
    }

    LAi_ActorDialog(pchar, CharacterFromID(charId), "", 2.0, 0.0);
}

void pirateStartQuest_Lether_fc(string qName)
{
	if (GetCharacterItem(pchar, "pirateStartQuest") == 0)
	{
	    GiveItem2Character(pchar, "pirateStartQuest");
	}
}

void pirateStartQuest_Lether_fc1(string qName)
{
	AddQuestRecord("pSQ", "6");
	AddQuestUserData("pSQ", "sSex", GetSexPhrase("ёл","ла"));
	AddQuestUserData("pSQ", "sName", GetFullName(CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId)));
	SetTimerFunction("pirateStartQuest_Bahus_fc", 0, 0, 1);

	pchar.quest.pirateStartQuest_Lether_fc.over = "yes";
	AddLandQuestMark_Main(CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId), "pSQ");
}

void pirateStartQuest_Bahus_fc(string qName)
{
	pchar.quest.pirateStartQuest_Bahus_seaBattle.win_condition.l1 = "location";
	pchar.quest.pirateStartQuest_Bahus_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
	pchar.quest.pirateStartQuest_Bahus_seaBattle.function = "pirateStartQuest_Bahus_seaBattle";
}

void pirateStartQuest_Bahus_seaBattle(string qName)
{
	ref sld = GetCharacter(NPC_GenerateCharacter("pSQB_Captain", "pirate_7", "man", "man", 6, PIRATE, 1, true)); //watch_quest_moment; TODO: уникальную
	FantomMakeCoolFighter(sld, 6, 30, 30, "blade6", "pistol1", 30);
	FantomMakeCoolSailor(sld, SHIP_FLEUT, FindPersonalName("pSQB_Captain_ship"), CANNON_TYPE_CANNON_LBS16, 45, 35, 30);
	sld.name	 = FindPersonalName("pSQB_Captain_name");
	sld.lastname = FindPersonalName("pSQB_Captain_lastname");
	SetCharacterGoods(sld, GOOD_SLAVES, 300);
	SetCrewQuantity(sld, 150);
	sld.ship.Crew.Morale = 34;
	ChangeCrewExp(sld, "Sailors", 50);
	ChangeCrewExp(sld, "Cannoners", 40);
	ChangeCrewExp(sld, "Soldiers", 35);

	Group_AddCharacter("pSQB_Group", "pSQB_Captain");			
	Group_SetType("pSQB_Group", "Pirate");
	Group_SetGroupCommander("pSQB_Group", "pSQB_Captain");
	Group_SetAddress("pSQB_Group", pchar.questTemp.pirateStartQuest.Areal, "quest_ships", "quest_ship_"+(1+rand(2)));
	Group_LockTask("pSQB_Group");

	pchar.quest.pirateStartQuest_Bahus_capture.win_condition.l1 = "Character_Capture";
    pchar.quest.pirateStartQuest_Bahus_capture.win_condition.l1.character = "pSQB_Captain";
    pchar.quest.pirateStartQuest_Bahus_capture.function = "pirateStartQuest_Bahus_Capture";

    pchar.quest.pirateStartQuest_Bahus_seaBattleEnd.win_condition.l1 = "Group_Death";
    pchar.quest.pirateStartQuest_Bahus_seaBattleEnd.win_condition.l1.group = "pSQB_Group";
    pchar.quest.pirateStartQuest_Bahus_seaBattleEnd.function = "pirateStartQuest_Bahus_seaBattleEnd";
}

void pirateStartQuest_Bahus_Capture(string qName)
{
    if (CheckAttribute(pchar, "questTemp.pSQ_Bacchus") && pchar.questTemp.pSQ_Bacchus == "over")
    {
        return;
    }

    ref sld = CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId);

    if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 200)
    {
        if (CheckAttribute(pchar, "questTemp.pSQ_Bacchus") && pchar.questTemp.pSQ_Bacchus == "to_Bacchus")
        {
            pchar.questTemp.pSQ_Bacchus = "to_Baron";
        }
        else
        {
            pchar.questTemp.pSQ_Bacchus = "to_Baron_noTalk";

            AddQuestRecord("pSQ_Bacchus", "2");
            AddQuestUserData("pSQ_Bacchus", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Pre"));
            AddQuestUserData("pSQ_Bacchus", "sName", GetFullName(sld));
        }

        AddLandQuestMark_Main(sld, "pSQ_Bacchus");
    }
    else
    {
        pchar.questTemp.pSQ_Bacchus = "over";
    }

    SetTimerFunction("pirateStartQuest_Bahus_Expired", 0, 0, 3);
    TEV.pirateStartQuest_BacchusCapture = true;
    CharacterDelAngry(sld);
}

void pirateStartQuest_Bahus_seaBattleEnd(string qName)
{
    if (CheckAttribute(&TEV, "pirateStartQuest_BacchusCapture"))
    {
        DeleteAttribute(&TEV, "pirateStartQuest_BacchusCapture");
        return;
    }

    pchar.questTemp.pSQ_Bacchus = "over";
    CloseQuestHeader("pSQ_Bacchus");
}

void pirateStartQuest_Bahus_Expired(string qName)
{
    if (pchar.questTemp.pSQ_Bacchus == "to_Baron")
    {
        AddQuestRecord("pSQ_Bacchus", "4");
        AddQuestUserData("pSQ_Bacchus", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
    }
    if (pchar.questTemp.pSQ_Bacchus == "to_Baron_noTalk")
    {
        AddQuestRecord("pSQ_Bacchus", "5");
    }

    pchar.questTemp.pSQ_Bacchus = "over";
    CloseQuestHeader("pSQ_Bacchus");
    RemoveLandQuestMark_Main(CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId), "pSQ_Bacchus");
}

void pirateStartQuest_seaBattle(string qName)
{
	LAi_group_SetRelation("pirateStartQuest_Smuggler_group", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);

	ref sld = GetCharacter(NPC_GenerateCharacter("pSQ_Captain", "citiz_27", "man", "man", 8, PIRATE, -1, true)); //watch_quest_moment
	FantomMakeCoolFighter(sld, 8, 40, 40, "blade9", "pistol3", 40);
	FantomMakeCoolSailor(sld, SHIP_LUGGER, FindPersonalName("pSQ_Captain_ship"), CANNON_TYPE_CANNON_LBS6, 55, 35, 46);
	sld.name 	= FindPersonalName("pSQ_Captain_name");
	sld.lastname = FindPersonalName("pSQ_Captain_lastname");
	sld.AlwaysSandbankManeuver = true;
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	//SetCharacterPerk(sld, "MusketsShoot");

	sld.ship.Crew.Morale = 55;
	ChangeCrewExp(sld, "Sailors", 50);
	ChangeCrewExp(sld, "Cannoners", 40);
	ChangeCrewExp(sld, "Soldiers", 45);

	GiveItem2Character(sld, "cirass1");
	GiveItem2Character(sld, "jewelry9");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	
	LAi_group_MoveCharacter(sld, "pirateStartQuest_Smuggler_group");
	Group_AddCharacter("pSQ_Group", "pSQ_Captain");			
	Group_SetType("pSQ_Group", "Pirate");
	Group_SetGroupCommander("pSQ_Group", "pSQ_Captain");
	Group_SetAddress("pSQ_Group", pchar.questTemp.pirateStartQuest.Areal, "quest_ships", "quest_ship_4");
	Group_SetTaskAttack("pSQ_Group", PLAYER_GROUP);
	Group_LockTask("pSQ_Group");

	pchar.quest.pirateStartQuest_seaBattle_over.win_condition.l1 = "NPC_Death";
	pchar.quest.pirateStartQuest_seaBattle_over.win_condition.l1.character = "pSQ_Captain";
	pchar.quest.pirateStartQuest_seaBattle_over.function = "pirateStartQuest_seaBattle_over";
}

void pirateStartQuest_seaBattle_over(string qName)
{
    ref sld = CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId);
	pchar.questTemp.pirateStartQuest = "5";
	AddQuestRecord("pSQ", "8");
	AddQuestUserData("pSQ", "sName", GetFullName(sld));
	AddLandQuestMark_Main(sld, "pSQ");
	CharacterDelAngry(sld);
}

//--> ОЗГ, метки для контров
void HeadHunter_Smuggler_SetQuestMarks(bool isSet)
{
    for (int i=0; i < MAX_COLONIES; i++)
    {
        if (!CheckAttribute(&colonies[i], "nation")) continue;
        if (colonies[i].nation == "none") continue; // необитайки
        if (colonies[i].nation == PIRATE) continue;

        int iChar = GetCharacterIndex(colonies[i].id + "_Smuggler");
        if (iChar != -1)
        {
            if(isSet)
            {
                AddLandQuestmark_Main_WithCondition(&Characters[iChar], "Headhunt", "Headhunt_Begin_Smuggler_QuestMarkCondition");
            }
            else
            {
                RemoveLandQuestmark_Main(&Characters[iChar], "Headhunt");
            }
        }
    }
}

void HeadHunter_Smuggler_AddQuestMarks()
{
    HeadHunter_Smuggler_SetQuestMarks(true);
}

void HeadHunter_Smuggler_DelQuestMarks()
{
    HeadHunter_Smuggler_SetQuestMarks(false);
}
//<-- ОЗГ, метки для контров

//--> ОЗГ, Карлос Кассир
void SelectCarlosCity() //выбираем город
{
	switch (rand(6))
	{
		case 0:
			pchar.questTemp.Headhunter.City = "Bridgetown";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonyBridgetownPre");
		break;
		case 1:
			pchar.questTemp.Headhunter.City = "Charles";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonyCharlesPre");
		break;
		case 2:
			pchar.questTemp.Headhunter.City = "Tortuga";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonyTortugaPre");
		break;
		case 3:
			pchar.questTemp.Headhunter.City = "Santodomingo";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonySantoDomingoPre");
		break;
		case 4:
			pchar.questTemp.Headhunter.City = "Panama";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonyPanamaPre");
		break;
		case 5:
			pchar.questTemp.Headhunter.City = "Portroyal";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonyPortRoyalPre");
		break;
		case 6:
			pchar.questTemp.Headhunter.City = "Marigo";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonyMarigoPre");
		break;
	}
}

void CreateCarlos()//создаем Карлоса
{
    ref sld, ch;
	sld = GetCharacter(NPC_GenerateCharacter("Carlos", "ozg_carlos", "man", "man", 20, PIRATE, -1, false));
	sld.name = FindPersonalName("Carlos_name");
	sld.lastname = FindPersonalName("Carlos_lastname");
    sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "Carlos";
    sld.greeting = "pirat_common";
    FantomMakeCoolFighter(sld, 20, 70, 70, "blade21", "pistol3", 50);
    sld.DontClearDead = true;
    LAi_SetCitizenType(sld);
    
    if(pchar.questTemp.Headhunter.Chance == 1)
    {
   	    LAi_SetSitTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_tavern", "sit","sit2");
    }
    else
    {
   	    LAi_SetStayTypeNoGroup(sld);
        ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_Brothel_room", "goto","goto3");
        
		ch = GetCharacter(NPC_GenerateCharacter("Qhorse", "horse02", "woman", "towngirl", 10, ENGLAND, 1, false));
        LAi_SetActorTypeNoGroup(ch);
		ChangeCharacterAddressGroup(ch, pchar.questTemp.Headhunter.City + "_Brothel_room", "goto","goto1");
        int n = FindLocation(pchar.questTemp.Headhunter.City + "_Brothel");
        locations[n].reload.l2.disable = false;
    }

    AddLandQuestMark_Main(sld, "Headhunt");
}

void CarlosDuel(string qName)
{
	pchar.quest.CarlosPlace.win_condition.l1 = "Location";
	pchar.quest.CarlosPlace.win_condition.l1.location = pchar.questTemp.Headhunter.City + "_ExitTown";
	pchar.quest.CarlosPlace.function = "CarlosPlace";
}

void CarlosDuelOver(string qName)//не пришли на стрелку
{
	pchar.quest.CarlosPlace.over = "yes";
	LAi_LocationDisableOfficersGen(pchar.questTemp.Headhunter.City + "_ExitTown", false);//офицеров пускать
	DeleteAttribute(&locations[FindLocation(pchar.questTemp.Headhunter.City + "_ExitTown")], "DisableEncounters"); //энкаутеры откроем
	ref sld = characterFromId("Carlos");
	sld.lifeDay = 0;
	AddQuestRecord("Headhunt", "2_2");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","ла"));
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
}

void CarlosPlace(string qName)
{
	ref sld;
	pchar.quest.CarlosDuelOver.over = "yes";
	LAi_SetPlayerType(pchar);
	LAi_group_Delete("EnemyFight");
	int iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 5; //это ранг от сложности
	for (int i=2; i<=4; i++)
    {
		if (i == 4)
        {
			sld = GetCharacter(NPC_GenerateCharacter("Carloshelper_"+i, "mush_ctz_12", "man", "mushketer", iTemp, PIRATE, -1, true)); //watch_quest_moment                
            FantomMakeCoolFighter(sld, iTemp, 20, 20, "", "mushket", 50);
		}	
		else
        {
			sld = GetCharacter(NPC_GenerateCharacter("Carloshelper_"+i, "citiz_"+(49+i), "man", "man", iTemp, PIRATE, -1, true)); //watch_quest_moment; тут _51, _52 получатся
			FantomMakeCoolFighter(sld, iTemp, 40, 40, "blade16", "pistol2", 50);  
		}
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, false);
        LAi_group_MoveCharacter(sld, "EnemyFight");
        ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_ExitTown", "goto", "goto6");
    }
    sld = characterFromID("Carlos");
	sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; //диалоговый файл, из которого говорить будет
	sld.dialog.currentnode = "talk_off_town_Carlos"; // диалоговый узел
	if (CheckAttribute(sld, "CityType"))
	{
		DeleteAttribute(sld, "City"); // чтоб не было ругани с нацией
		DeleteAttribute(sld, "CityType");
	}
	ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_ExitTown", "goto", "goto1");
	LAi_SetActorType(pchar);
    LAi_SetActorType(sld);
    LAi_ActorTurnToCharacter(sld, pchar);
    SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
	LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
	AddLandQuestMark_Main(sld, "Headhunt");
}
//<-- ОЗГ, Карлос Кассир

void SelectHoumCity()//выберем колонию для Холма
{
	switch (sti(pchar.questTemp.Headhunter.Chance))
	{
		case 0:
			pchar.questTemp.Headhunter.City = "Bridgetown";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonyBridgetownPre");
			pchar.questTemp.Headhunter.Island = "Barbados";
		break;
		case 1:
			pchar.questTemp.Headhunter.City = "Charles";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonyCharlesPre");
			pchar.questTemp.Headhunter.Island = "Nevis";
		break;
		case 2:
			pchar.questTemp.Headhunter.City = "Sentjons";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonySentJonsPre");
			pchar.questTemp.Headhunter.Island = "Antigua";
		break;
		case 3:
			pchar.questTemp.Headhunter.City = "Portspein";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonyPortSpeinPre");
			pchar.questTemp.Headhunter.Island = "Trinidad";
		break;
		case 4:
			pchar.questTemp.Headhunter.City = "Portroyal";
			pchar.questTemp.Headhunter.Cityname = XI_ConvertString("ColonyPortRoyalPre");
			pchar.questTemp.Headhunter.Island = "Jamaica";
		break;
	}
}

void CreateHoum()//создадим Холма
{
    ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("Houm", "ozg_horn", "man", "man", 25, ENGLAND, -1, false));
	FantomMakeCoolFighter(sld, 25, 55, 55, "blade19", "pistol6", 75);
	FantomMakeCoolSailor(sld, SHIP_GALEON, FindPersonalName("Houmn_ship"), CANNON_TYPE_CANNON_LBS24, 70, 70, 70);
	sld.name = FindPersonalName("Houm_name");
	sld.lastname = FindPersonalName("Houm_lastname");
    sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "Houm";
    sld.greeting = "Gr_HeadPirates";
	sld.Ship.Mode = "pirate";
    DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
    sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterGoods(sld, GOOD_SILVER, 556);//положить в трюм серебро
	LAi_SetCitizenType(sld);
	LAi_SetImmortal(sld, true);
	sld.ship.Crew.Morale = 70;
	ChangeCrewExp(sld, "Sailors", 70);
	ChangeCrewExp(sld, "Cannoners", 70);
	ChangeCrewExp(sld, "Soldiers", 70);
    
    if(pchar.questTemp.Headhunter.Chance1 == 0)
    {
   	    LAi_SetSitTypeNoGroup(sld);
		FreeSitLocator(pchar.questTemp.Headhunter.City + "_tavern", "sit1");
        ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_tavern", "sit", "sit1");
    }
    else
    {
		LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
		ChangeCharacterAddressGroup(sld, pchar.questTemp.Headhunter.City + "_town", "quest", "quest1");
    }

    AddLandQuestMark_Main(sld, "Headhunt");
}

void Headhunter_CreateHoumShips(string qName)//cоздание кораблей Хоума
{
	ref sld;
    Island_SetReloadEnableGlobal(pchar.questTemp.Headhunter.Island, false);
    Group_FindOrCreateGroup("Houm_Attack");//создать группу
	Group_SetType("Houm_Attack", "war");//тип группы
	
	sld = CharacterFromID("Houm");
	LAi_SetImmortal(sld, false);
	Group_AddCharacter("Houm_Attack", "Houm");//добавим Хоума в группу
	
	sld = GetCharacter(NPC_GenerateCharacter("Houm_helper", "officer_6", "man", "man", 35, ENGLAND, -1, true));//watch_quest_moment; создание кэпа-помощника
	sld.name = FindPersonalName("Houm_helper_name");
	sld.lastname = FindPersonalName("Houm_helper_lastname");
	FantomMakeCoolSailor(sld, SHIP_BRIG, FindPersonalName("Houm_helper_ship"), CANNON_TYPE_CANNON_LBS16, 50, 50, 50);//создание брига
	FantomMakeCoolFighter(sld, 35, 40, 45, "blade15", "pistol5", 90);//создание фантома кэпа
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.Ship.Mode = "pirate";
	sld.AlwaysEnemy = true;
	sld.Abordage.Enable = true;
	Group_AddCharacter("Houm_Attack", "Houm_helper");//добавление в группу
 
    // ==> стравливание
	Group_SetGroupCommander("Houm_Attack", "Houm");
	Group_SetTaskAttack("Houm_Attack", PLAYER_GROUP);
	Group_SetPursuitGroup("Houm_Attack", PLAYER_GROUP);
	Group_SetAddress("Houm_Attack", pchar.questTemp.Headhunter.Island, "quest_ships", "quest_ship_6");
	Group_LockTask("Houm_Attack");
			
    // ==> прерывание на убиение эскадры
    pchar.quest.Headhunter_AfterBattle.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.Headhunter_AfterBattle.win_condition.l1.group = "Houm_Attack";//какую группу уничтожить
	pchar.quest.Headhunter_AfterBattle.function = "Headhunter_HoumAttack_AfterBattle";//это победа
	pchar.quest.Headhunter_DieHard.win_condition.l1 = "MapEnter";//условие на слинять
    pchar.quest.Headhunter_DieHard.function = "Headhunter_HoumAttack_DieHard";//это слинял
}

void Headhunter_HoumAttack_AfterBattle(string qName)//реакция на победу
{
	Group_DeleteGroup("Houm_Attack");
	Island_SetReloadEnableGlobal(pchar.questTemp.Headhunter.Island, true);
    pchar.quest.Headhunter_DieHard.over = "yes";
	AddQuestRecord("Headhunt", "7");
	pchar.questTemp.Headhunter = "hunt_houm_yes";
	if (pchar.questTemp.LSC != "over") TEV.QuestTemp.deadHoum = true;

    AddLandQuestMark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Headhunt");
}

void Headhunter_HoumAttack_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("Houm_Attack");
    Island_SetReloadEnableGlobal(pchar.questTemp.Headhunter.Island, true);
    pchar.quest.Headhunter_AfterBattle.over = "yes";
	AddQuestRecord("Headhunt", "8");
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
	ChangeOfficersLoyality("bad_all", 1);
}

void Headhunter_PinasseOver(string qName)//не сообразили, куда идти за 30 дней
{
	pchar.quest.Headhunter_Rattortuga.over = "yes";
	ref sld = characterFromId("RatOfficer");
	sld.lifeDay = 0;
	AddQuestRecord("Headhunt", "10");
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
}

void Headhunter_CreateRatpinasse(string qName)//создание пинаса Аделаида с перпомом
{
	pchar.quest.Headhunter_PinasseOver.over = "yes";
	ref sld;
	Group_FindOrCreateGroup("PinasseC");//создать группу
	Group_SetType("PinasseC", "war");//тип группы
	
	sld = GetCharacter(NPC_GenerateCharacter("RatSeaOfficer", "officer_3", "man", "man", 35, FRANCE, -1, true)); //watch_quest_moment; создание кэпа; ОПЯТЬ ОФИЦЕР_15
	sld.name = FindPersonalName("RatSeaOfficer_name");
	sld.lastname = FindPersonalName("RatSeaOfficer_lastname");
	FantomMakeCoolSailor(sld, SHIP_PINNACE, FindPersonalName("RatSeaOfficer_ship"), CANNON_TYPE_CANNON_LBS20, 65, 70, 70);//создание кораблей
	FantomMakeCoolFighter(sld, 35, 65, 65, "blade15", "pistol2", 90);//создание фантома кэпа
	sld.DontRansackCaptain = true;
	DeleteAttribute(sld, "AlwaysFriend");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.Ship.Mode = "pirate";
	Group_AddCharacter("PinasseC", "RatSeaOfficer");//добавление в группу
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	sld.ship.Crew.Morale = 90;
	ChangeCrewExp(sld, "Sailors", 50);
	ChangeCrewExp(sld, "Cannoners", 55);
	ChangeCrewExp(sld, "Soldiers", 50);
		
	Group_SetGroupCommander("PinasseC", "RatSeaOfficer");
	Group_SetTaskAttack("PinasseC", PLAYER_GROUP);
	Group_SetAddress("PinasseC", "Tortuga", "quest_ships", "quest_ship_1");
	Group_LockTask("PinasseC");
	AddQuestRecord("Headhunt", "15");
	AddLandQuestMark_Main(CharacterFromID("Tortuga_tavernkeeper"), "Headhunt");
			
    // ==> прерывание на убиение эскадры
    pchar.quest.HeadhunterC_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.HeadhunterC_AfterBattle.win_condition.l1.group = "PinasseC";
	pchar.quest.HeadhunterC_AfterBattle.function = "PinasseC_AfterBattle";
}

void PinasseC_AfterBattle(string qName)//реакция на досрочное уничтожение пинаса
{
	ref sld = characterFromId("RatOfficer");
	sld.lifeDay = 0;
	AddQuestRecord("Headhunt", "16");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","а"));
	ChangeCharacterHunterScore(PChar, "frahunter", 30); //начислить НЗГ
	pchar.questTemp.Headhunter = "end_quest";
	CloseQuestHeader("Headhunt");
	Group_DeleteGroup("PinasseC");

	RemoveLandQuestMark_Main(CharacterFromID("Tortuga_tavernkeeper"), "Headhunt");
}

void CreateRatOfficer()//посадим в таверну самого Крысу - не будем модель прятать
{
    ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("RatOfficer", "ozg_piRat", "man", "man", 10, PIRATE, -1, false));
	sld.name = FindPersonalName("RatOfficer_name");
	sld.lastname = FindPersonalName("RatOfficer_lastname");
    sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "RatOfficer";
    sld.greeting = "pirat_common";
    GiveItem2Character(sld, "blade15");
	EquipCharacterbyItem(sld, "blade15");
    DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
    LAi_SetCitizenType(sld);
   	LAi_SetSitTypeNoGroup(sld);
    ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit","sit2");
}

void Headhunter_Ratgulf(string qName)//высадились в заливе
{
	pchar.quest.HeadhunterC_AfterBattle.over = "yes";
	Group_DeleteGroup("PinasseC");
	pchar.quest.Headhunter_RatgulfOver.over = "yes";
	if (GetCompanionQuantity(pchar) > 1 || 3-sti(RealShips[sti(pchar.ship.type)].Class) > 0)
	{
		AddQuestRecord("Headhunt", "19_1");
		AddQuestUserData("Headhunt", "sSex", GetSexPhrase("ся","ась"));
		CloseQuestHeader("Headhunt");
		pchar.questTemp.Headhunter = "end_quest";
	}
	else
	{
		AddQuestRecord("Headhunt", "19");
		pchar.quest.HeadhunterRatgulfTimer.win_condition.l1 = "Timer";
		pchar.quest.HeadhunterRatgulfTimer.win_condition.l1.date.hour  = sti(GetTime() + 24);
		pchar.quest.HeadhunterRatgulfTimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, rand(1));
		pchar.quest.HeadhunterRatgulfTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, rand(1));
		pchar.quest.HeadhunterRatgulfTimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, rand(1));
		pchar.quest.HeadhunterRatgulfTimer.function = "Headhunter_CreateRatTruepinasse_prepare";
		SetFunctionTimerCondition("Headhunter_Ratgulf2Over", 0, 0, 5, false);
	}
}

void Headhunter_CreateRatTruepinasse_prepare(string qName)
{
	pchar.quest.Headhunter_RatgulfPinasse.win_condition.l1 = "location";
    pchar.quest.Headhunter_RatgulfPinasse.win_condition.l1.location = "Beliz";//отправляем в локацию
    pchar.quest.Headhunter_RatgulfPinasse.function = "Headhunter_CreateRatTruepinasse";
}

void Headhunter_RatOfficerOver(string qName)//просрочили поговорить с Крысой
{
	pchar.quest.HeadhunterC_AfterBattle.over = "yes";
	Group_DeleteGroup("PinasseC");
	ref sld = characterFromId("RatOfficer");
	sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "RatOfficer_5";
	sld.lifeDay = 0;
	AddQuestRecord("Headhunt", "17_1");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("ся","ась"));
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
}

void Headhunter_RatgulfOver(string qName)//просрочили дойти до залива
{
	pchar.quest.HeadhunterC_AfterBattle.over = "yes";
	pchar.quest.Headhunter_Ratgulf.over = "yes";
	Group_DeleteGroup("PinasseC");
	AddQuestRecord("Headhunt", "20");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("ся","лась"));
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
}

void Headhunter_Ratgulf2Over(string qName)//страдали фигней вместо поисков после высадки в заливе
{
	pchar.quest.Headhunter_RatgulfPinasse.over = "yes";
	AddQuestRecord("Headhunt", "20_1");
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
}

void Headhunter_CreateRatTruepinasse(string qName)//создание пинаса Аделаида с Крысой
{
	pchar.quest.Headhunter_Ratgulf2Over.over = "yes";
	int hcrew;
	Group_FindOrCreateGroup("PinasseT");//создать группу
	Group_SetType("PinasseT", "war");//тип группы
	Island_SetReloadEnableGlobal("Beliz", false);
    ref sld = GetCharacter(NPC_GenerateCharacter("RatCaptain", "ozg_piRat", "man", "man", 25, PIRATE, -1, true));//создание кэпа
	sld.name = FindPersonalName("RatOfficer_name");
	sld.lastname = FindPersonalName("RatOfficer_lastname");
	sld.DontRansackCaptain = true;
	FantomMakeCoolSailor(sld, SHIP_PINNACE, FindPersonalName("RatSeaOfficer_ship"), CANNON_TYPE_CANNON_LBS20, 65, 80, 80);//создание кораблей
	FantomMakeCoolFighter(sld, 25, 65, 70, "blade15", "pistol6", 100);//создание фантома кэпа
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.Ship.Mode = "pirate";
	Group_AddCharacter("PinasseT", "RatCaptain");//добавление в группу
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantityOverMax(sld, hcrew+100);
	sld.ship.Crew.Morale = 80;
	ChangeCrewExp(sld, "Sailors", 70);
	ChangeCrewExp(sld, "Cannoners", 80);
	ChangeCrewExp(sld, "Soldiers", 75);
		
	// ==> стравливание
	Group_SetGroupCommander("PinasseT", "RatCaptain");
	Group_SetTaskAttack("PinasseT", PLAYER_GROUP);
	Group_SetAddress("PinasseT", "Beliz", "quest_ships", "Quest_ship_8");
	Group_LockTask("PinasseT");
	AddQuestRecord("Headhunt", "21");
			
    // ==> прерывание на убиение эскадры
    pchar.quest.Headhunter_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Headhunter_AfterBattle.win_condition.l1.group = "PinasseT";
	pchar.quest.Headhunter_AfterBattle.function = "Headhunter_Pinassetrue_AfterBattle";
	pchar.quest.Headhunter_DieHard.win_condition.l1 = "MapEnter";//условие на слинять
    pchar.quest.Headhunter_DieHard.function = "Headhunter_Pinassetrue_DieHard";//это слинял
}

void Headhunter_Pinassetrue_DieHard(string qName)//реакция на поражение
{
	Group_DeleteGroup("PinasseT");
    Island_SetReloadEnableGlobal("Beliz", true);
    pchar.quest.Headhunter_AfterBattle.over = "yes";
	AddQuestRecord("Headhunt", "22");
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
	ChangeOfficersLoyality("bad_all", 1);
}

void Headhunter_Pinassetrue_AfterBattle(string qName)//реакция на победу
{
	if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
	{
		Group_DeleteGroup("PinasseT");
		Island_SetReloadEnableGlobal("Beliz", true);
		pchar.quest.Headhunter_DieHard.over = "yes";
		AddQuestRecord("Headhunt", "24");
		pchar.questTemp.Headhunter = "hunt_rat_yes2";
	}
	else
	{
		characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)].id = "RatCaptain"; //базар в каюте, проверка ИД кэпа
	}
	AddLandQuestMark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Headhunt");
}

void Headhunter_HalenOver(string qName)//опоздали за 10 дней до Кюрасао
{
	AddQuestRecord("Headhunt", "26_1");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
	RemoveLandQuestMark_Main(CharacterFromID("Villemstad_tavernkeeper"), "Headhunt");
}

void Headhunter_HalenOver_2(string qName)//пересидели на Кюрасао
{
	if(CheckAttribute(pchar, "quest.Headhunter_inRoom"))
	{
		LocatorReloadEnterDisable("Villemstad_tavern", "reload2_back", true);
		pchar.quest.Headhunter_inRoom.over = "yes";
	}
	AddQuestRecord("Headhunt", "29_1");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","ась"));
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
	RemoveLandQuestMark_Main(CharacterFromID("Villemstad_tavernkeeper"), "Headhunt");
}

void Headhunter_HalenOver_3(string qName)//пересидели на Кюрасао
{
	pchar.quest.Headhunter_SeekHalen.over = "yes";
	pchar.quest.Headhunter_FightInPort.over = "yes";
	pchar.quest.Headhunter_AfterBattle.over = "yes";
	pchar.quest.Headhunter_DieHard.over = "yes";
	Group_DeleteGroup("Halen_frigate");
	AddQuestRecord("Headhunt", "30_1");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("ся","ась"));
	CloseQuestHeader("Headhunt");
	pchar.questTemp.Headhunter = "end_quest";
}

void RatHunters_inRoom(string qName)//идем в комнату
{
	chrDisableReloadToLocation = true;
	LocatorReloadEnterDisable(locations[reload_location_index].fastreload + "_tavern", "reload2_back", true);
	DoQuestCheckDelay("TalkSelf_Quest", 5.0);
}

void RatHunters_Sleep()//спим в комнате
{
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_18"), "", 0, 6);
    LaunchFrameForm();
    WaitDate("", 0, 0, 0, 8, 10); //крутим время
    RecalculateJumpTable();
	DoQuestFunctionDelay("RatHunters_Enter", 0.5);
}

void RatHunters_Enter(string qName)//пришли киллеры
{	
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	ref sld;
	string sTemp;
	int iTemp = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
	for (int i=1; i<=2; i++)
	{
		if(i == 1) sTemp = "citiz_56";
		else sTemp = "citiz_58";
		sld = GetCharacter(NPC_GenerateCharacter("RatHunters"+i, sTemp, "man", "man", iTemp, PIRATE, -1, true)); //watch_quest_moment
		FantomMakeCoolFighter(sld, iTemp, 50, 50, "topor2", "pistol5", 50);
		LAi_SetActorType(sld);
		if (i == 1)
		{
			LAi_CharacterDisableDialog(sld);
         	ChangeCharacterAddressGroup(sld, "Villemstad_tavern_upstairs", "goto", "goto2");
		}
		else
		{
			sld.dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "RatHunters";	
			sld.greeting = "Gr_HUNTER";
         	ChangeCharacterAddressGroup(sld, "Villemstad_tavern_upstairs", "goto", "goto3");
			LAi_ActorDialog(sld, pchar, "", 2.0, 0);
		}
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	LAi_group_MoveCharacter(sld, "EnemyFight");
}

void CreateHalen()//создаем Халена и ближайшее окружение
{
    ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("Halen", "ozg_martin", "man", "man", 30, HOLLAND, -1, false));
	sld.name = FindPersonalName("Halen_name");
	sld.lastname = FindPersonalName("Halen_lastname");
    sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "Halen";
    sld.greeting = "pirat_common";
    FantomMakeCoolFighter(sld, 30, 70, 70, "blade34", "pistol6", 100);
    ChangeCharacterAddressGroup(sld, "Villemstad_town", "reload", "reload3");
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	GiveItem2Character(sld, "cirass5");
	EquipCharacterbyItem(sld, "cirass5");
	LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Headhunter_FightInPort");//сработает на атаку Халена
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "Headhunter_HalenOut", -1);//сработает, если Хален уйдет
	LAi_Actor2WaitDialog(sld, pchar);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	AddLandQuestMark_Main(sld, "Headhunt");

	LocatorReloadEnterDisable("Villemstad_town", "gate", true);
	LocatorReloadEnterDisable("Villemstad_town", "reload33", true);
	LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
	LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
	for (int i=1; i<=10; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("AddSolder"+i, "Sold_hol_"+(rand(7)+9), "man", "man", 20, HOLLAND, 1, true)); //халена охраняют элитки Konstrush
		sld.Dialog.Filename = "Common_Soldier.c";
		sld.city = "Villemstad";
		sld.citytype = "soldier";
		FantomMakeCoolFighter(sld, 20, 55, 55, "blade16", "pistol3", 55);
        LAi_SetPatrolType(sld);
		ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto"+i);    
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	}
	LAi_group_SetLookRadius("HOLLAND_CITIZENS", 100);
	LAi_group_SetHearRadius("HOLLAND_CITIZENS", 100);
	pchar.quest.Headhunter_FightInPort.win_condition.l1 = "location";
	pchar.quest.Headhunter_FightInPort.win_condition.l1.location = "Curacao";
	pchar.quest.Headhunter_FightInPort.function = "Headhunter_SeabattleInPort";
}

void Headhunter_SeabattleInPort(string qName)//создание корвета Халена
{
	ref sld;
	Group_FindOrCreateGroup("Halen_frigate");//создать группу
	Group_SetType("Halen_frigate", "war");//тип группы

	if (GetCharacterIndex("Halen") == -1)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Halen1", "officer_26", "man", "man", 25, HOLLAND, -1, true)); //watch_quest_moment
	}
	else
	{
		sld = GetCharacter(NPC_GenerateCharacter("Halen1", "ozg_martin", "man", "man", 25, HOLLAND, -1, true));//создание кэпа
		sld.name = FindPersonalName("Halen_name");
		sld.lastname = FindPersonalName("Halen_lastname");
		sld.greeting = "pirat_common";
		sld.dialog.filename = "Quest\Other_quests_NPC.c";
		sld.DeckDialogNode = "Halen_Deck";
	}
	sld.DontRansackCaptain = true;
	FantomMakeCoolSailor(sld, SHIP_CORVETTE, FindPersonalName("Halen_ship"), CANNON_TYPE_CANNON_LBS20, 85, 80, 75); //создание кораблей
	FantomMakeCoolFighter(sld, 30, 70, 70, "blade34", "pistol6", 100);//создание фантома кэпа
	sld.Ship.Mode = "war";
	Group_AddCharacter("Halen_frigate", "Halen1");//добавление в группу
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "MusketsShoot");
	if (GetCharacterIndex("Halen") != -1)
	{
		GiveItem2Character(sld, "cirass5");
	}
	sld.ship.Crew.Morale = 70;
	ChangeCrewExp(sld, "Sailors", 95);
	ChangeCrewExp(sld, "Cannoners", 70);
	ChangeCrewExp(sld, "Soldiers", 75);

	sld = GetCharacter(NPC_GenerateCharacter("Halen_helper", "navy_off_hol_3", "man", "man", 25, HOLLAND, -1, true)); //watch_quest_moment
	sld.DontRansackCaptain = true;
	FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("Halen_helper_ship"), CANNON_TYPE_CANNON_LBS24, 50, 50, 60);//призовем на помощь фрегат
	FantomMakeCoolFighter(sld, 35, 60, 60, "blade15", "pistol2", 90);//создание фантома кэпа
	sld.Ship.Mode = "war";
	Group_AddCharacter("Halen_frigate", "Halen_helper");//добавление в группу

	// ==> стравливание
	Group_SetGroupCommander("Halen_frigate", "Halen1");
	Group_SetTaskAttack("Halen_frigate", PLAYER_GROUP);
	Group_SetAddress("Halen_frigate", "Curacao", "quest_ships", "Quest_ship_2");
	Group_LockTask("Halen_frigate");

    // ==> прерывание на убиение эскадры
    pchar.quest.Headhunter_AfterBattle.win_condition.l1 = "Group_Death";
	pchar.quest.Headhunter_AfterBattle.win_condition.l1.group = "Halen_frigate";
	pchar.quest.Headhunter_AfterBattle.function = "Headhunter_Halen_frigate_AfterBattle";
	pchar.quest.Headhunter_DieHard.win_condition.l1 = "MapEnter";//условие на слинять
    pchar.quest.Headhunter_DieHard.function = "Headhunter_Halen_frigate_DieHard";//это слинял
}

void Headhunter_Halen_frigate_DieHard(string qName)//ушли на карту
{
	DeleteQuestCheck("Headhunter_HalenOver_3");
	DeleteQuestCheck("Headhunter_DieHard");
	DeleteQuestCheck("Headhunter_Halen_fight");
	Group_DeleteGroup("Halen_frigate");
    Island_SetReloadEnableGlobal("Curacao", true);
	if (GetCharacterIndex("Halen") == -1 || GetCharacterIndex("Halen1") == -1)
	{
		AddQuestRecord("Headhunt", "31");
		pchar.questTemp.Headhunter = "hunt_halen_yes";
		ChangeCharacterHunterScore(PChar, "holhunter", 30);
        AddLandQuestMark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Headhunt");
	}
	else
	{
		AddQuestRecord("Headhunt", "30");
		CloseQuestHeader("Headhunt");
		pchar.questTemp.Headhunter = "end_quest";
		ChangeOfficersLoyality("bad_all",1);
	}
	characters[GetCharacterIndex("Halen")].lifeDay = 0;
}

void Headhunter_Halen_frigate_AfterBattle(string qName)//потопили корвет
{
	DeleteQuestCheck("Headhunter_HalenOver_3");
	DeleteQuestCheck("Headhunter_DieHard");
	DeleteQuestCheck("Headhunter_Halen_fight");
	Group_DeleteGroup("Halen_frigate");
	Island_SetReloadEnableGlobal("Curacao", true);
	AddQuestRecord("Headhunt", "31");
	pchar.questTemp.Headhunter = "hunt_halen_yes";
	ChangeCharacterHunterScore(PChar, "holhunter", 30);
	characters[GetCharacterIndex("Halen")].lifeDay = 0;
	AddLandQuestMark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Headhunt");
}

void CreateMiko()//создадим Мико Пистольеро
{
    ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("Miko", "ozg_miko", "man", "man", 40, SPAIN, -1, false));
	FantomMakeCoolFighter(sld, 40, 50, 100, "blade22", "pistol4", 150);
	sld.name = FindPersonalName("Miko_name");
	sld.lastname = FindPersonalName("Miko_lastname");
    sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "Miko";
    sld.greeting = "pirat_common";
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "GunProfessional");
	GiveItem2Character(sld, "indian10");
	GiveItem2Character(sld, "Totem_5");
	GiveItem2Character(sld, "sculMa2");
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "Pearlgroup_2");
	ChangeCharacterAddressGroup(sld, "Pearl_Town_2", "goto", "goto1");
	AddLandQuestMark_Main(sld, "Headhunt");

	arrayNPCModelHow = 0;
	for (int i=2; i<=5; i++)//добавим охраны в поселение
	{
		sld = GetCharacter(NPC_GenerateCharacter("AddPearlguard"+i, "pirate_"+(rand(15)+1), "man", "man", 25, SPAIN, -1, true)); //watch_quest_moment; мб наёмники?
		SetNPCModelUniq(sld, "pirate", MAN);
		sld.Dialog.Filename = "Pearl_dialog.c";
		sld.dialog.currentnode = "PearlMan";
		sld.city = "Pearl_Town_2";
		sld.citytype = "soldier";
		sld.greeting = "pirat_common";
		FantomMakeCoolFighter(sld, 25, 50, 50, "blade16", "pistol3", 100);
        LAi_SetPatrolType(sld);
		ChangeCharacterAddressGroup(sld, "Pearl_Town_2", "goto", "goto"+i);    
		LAi_group_MoveCharacter(sld, "Pearlgroup_2");
	}
	LAi_group_SetLookRadius("Pearl_Town_2", 50);
	LAi_group_SetHearRadius("Pearl_Town_2", 50);
}

void Miko_die(string qName)
{
	chrDisableReloadToLocation = false;
	pchar.quest.Headhunter_Jahunters.win_condition.l1 = "location";
	pchar.quest.Headhunter_Jahunters.win_condition.l1.location = "shore55";
	pchar.quest.Headhunter_Jahunters.function = "Headhunter_Jahunters";	
}
		
void Headhunter_Jahunters(string qName)//наймиты Джа в бухте
{
	string sTemp;
	int iTemp;
	ref sld;
	chrDisableReloadToLocation = true;
	for (int i=1; i<=6; i++)
	{
		if(rand(1)) sTemp = "citiz_56";
		else		sTemp = "citiz_58";
		//switch(rand(3)) + officer_26
		sld = GetCharacter(NPC_GenerateCharacter("JaHunters"+i, sTemp, "man", "man", 25, PIRATE, -1, true)); //watch_quest_moment
		FantomMakeCoolFighter(sld, 25, 60, 60, "topor2", "pistol6", 70);
		LAi_SetActorType(sld);
		if (i == 1)
		{
			sld.dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "JaHunters";	
			sld.greeting = "Gr_HUNTER";
			ChangeCharacterAddressGroup(sld, "shore55", "goto", "goto4");
			LAi_ActorDialog(sld, pchar, "", 10.0, 0);
			LAi_SetImmortal(sld, true);
		}
		else
		{
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "shore55", "goto", "goto1");
		}
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	sld = GetCharacter(NPC_GenerateCharacter("JaMush", "mush_ctz_11", "man", "mushketer", 35, PIRATE, -1, true)); //watch_quest_moment
    FantomMakeCoolFighter(sld, iTemp, 80, 80, "", "mushket", 100);
	ChangeCharacterAddressGroup(sld, "shore55", "goto", "goto2");
	LAi_group_MoveCharacter(sld, "EnemyFight");	
}		

void Create_Ja(string qName) //cоздаем Полакр с Джа (раньше была СП) Konstrush
{
	int hcrew;
	Group_FindOrCreateGroup("BlueBird_Group2");
	bQuestDisableMapEnter = true;
	ref sld = GetCharacter(NPC_GenerateCharacter("Jafar", "Jafar_Preston", "man", "man", 28, PIRATE, -1, true));
	sld.name 	= FindPersonalName("Jafar_name");
    sld.lastname = FindPersonalName("Jafar_lastname");
	sld.dialog.filename = "Quest\Other_quests_NPC.c";
	sld.dialog.currentnode = "Ja_talk";
	sld.greeting = "CapSinkShip";
	FantomMakeCoolFighter(sld, 35, 80, 80, "blade14", "pistol6", 100);
	FantomMakeCoolSailor(sld, SHIP_POLACRE_QUEST, FindPersonalName("Jafar_ship"), CANNON_TYPE_CULVERINE_LBS24, 100, 90, 90);
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "AboardToFinalDeck");
	sld.AlwaysSandbankManeuver = true; //тупым запрет тонуть о берег
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.AlwaysEnemy = true;
	sld.DontRansackCaptain = true;
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "LootCollection");
	SetCharacterPerk(sld, "MusketsShoot");
	GiveItem2Character(sld, "indian5");
	GiveItem2Character(sld, "jewelry15");
	GiveItem2Character(sld, "incas_collection");
	RemoveItems(sld, "spyglass3", 1);
	GiveItem2Character(sld, "spyglass4");
	EquipCharacterbyItem(sld, "spyglass4");
	hcrew = GetMaxCrewQuantity(sld);
	SetCrewQuantityOverMax(sld, hcrew+100);
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	Group_AddCharacter("BlueBird_Group2", "Jafar");
	
	Group_SetGroupCommander("BlueBird_Group2", "Jafar");
	Group_SetAddress("BlueBird_Group2", "SantaCatalina", "quest_ships", "Quest_ship_9");
	Group_SetTaskAttack("BlueBird_Group2", PLAYER_GROUP);
	Group_LockTask("BlueBird_Group2");
	AddQuestRecord("Headhunt", "36");
	
	pchar.quest.Headhunter_AfterBattleJa.win_condition.l1 = "Group_Death";
	pchar.quest.Headhunter_AfterBattleJa.win_condition.l1.group = "BlueBird_Group2";
	pchar.quest.Headhunter_AfterBattleJa.function = "Ja_over";
}

void CreateJohnCoxon() //создание Джона Коксона
{
    ref sld;
    sld = GetCharacter(NPC_GenerateCharacter("John_Coxon", "pirate_13", "man", "man", 38, PIRATE, -1, false));
    sld.name = FindPersonalName("John_Coxon_name");
    sld.lastname = FindPersonalName("John_Coxon_lastname");
    sld.Dialog.Filename = "Mayor\JohnCoxon.c";
    sld.dialog.currentnode = "First time";
    sld.greeting = "Gr_HeadPirates";
    FantomMakeCoolFighter(sld, 35, 90, 50, BLADE_LONG, "pistol4", 150);
    LAi_SetStayType(sld);
    LAi_SetLoginTime(sld, 0.0, 24.0);
    LAi_SetHP(sld, 180.0, 180.0);
    LAi_SetHuberType(sld);
    LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
    ChangeCharacterAddressGroup(sld, "PuertoPrincipe_townhall", "sit", "sit1");
    sld.watchBoxes = true;
    sld.standUp = true;
    AddSimpleRumour(StringFromKey("Common_rumours_83"), PIRATE, 10, 1);
    AddSimpleRumour(StringFromKey("Common_rumours_84", XI_ConvertString("Colony" + "PuertoPrincipe" + "Pre")), PIRATE, 10, 2);
}

void Ja_over(string qName)//уничтожили Джа
{
	Group_DeleteGroup("BlueBird_Group2");
	bQuestDisableMapEnter = false;
	AddQuestRecord("Headhunt", "37");
	AddQuestUserData("Headhunt", "sSex", GetSexPhrase("","а"));
	pchar.questTemp.Headhunter = "hunt_ja_yes";
	AddLandQuestMark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Headhunt");
}

//Sinistra Проклятый идол -->
void PDM_Callow_ColierProdolg(string qName)
{
	chrDisableReloadToLocation = true;
	ClearAllLogStrings();
	Log_info(StringFromKey("InfoMessages_37"));

	ref sld = CharacterFromID("PDM_Providencia_Mayor_Klon");
	ChangeCharacterAddressGroup(sld, "Providencia_town", "none", "");
	sld.lifeday = 0;

	sld = CharacterFromID("Providencia_Mayor");
	ChangeCharacterAddressGroup(sld, "Providencia_townhall", "sit", "sit1");
}

void PDM_PI_Skelety_v_more(string qName)
{
	if (CheckAttribute(pchar, "questTemp.PDM_PI_Skelety_v_more"))
	{
		if (IsEntity(&worldMap))
		{
			DoQuestFunctionDelay("PDM_PI_Skelety_v_more_paluba", 0.0);
		}
		else
		{
			PChar.quest.PDM_Ne_Spryacheshsy.win_condition.l1 = "MapEnter";
			PChar.quest.PDM_Ne_Spryacheshsy.function = "PDM_PI_Skelety_v_more";
		}
	}
}

void PDM_PI_Skelety_v_more_paluba(string qName)
{
	int i;
	MakeCloneShipDeck(pchar, false); // подмена палубы
	i = FindLocation("Ship_deck");
	Locations[i].image = "loading\scelets_" + rand(1) + ".tga";
	DoQuestReloadToLocation("Ship_deck", "reload", "reload3", "PDM_PI_Skelety_on_Ship");
}

void PDM_PI_Vernut_Gorod(string qName)
{
	SetLocationCapturedState("Providencia_town", false);
	AddSimpleRumourToAllNations(StringFromKey("Common_rumours_85"), 7, 1);
}

void PDM_PI_Callow_na_dno(string qName)
{
	ref sld = CharacterFromID("James_Callow");
	sld.ship.HP = 0;
}

//Sinistra Проклятый идол <--

//Клан Ламбрини -->
void PDM_CL_OdliSpawn()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("PDM_Odli", "navy_off_eng_4", "man", "man", 10, ENGLAND, -1, false));
	sld.name = FindPersonalName("PDM_Odli_name");
	sld.lastname = FindPersonalName("PDM_Odli_lastname");
	sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
	sld.DeckDialogNode = "Antonio_1_1";
	FantomMakeCoolFighter(sld, 10, 40, 40, "blade19", "pistol2", 0);
	sld.SaveItemsForDead = true;
	FantomMakeCoolSailor(sld, RandShipFromPcharSquadron(), FindPersonalName("Tiburon_ship"), CANNON_TYPE_LBS_BY_SHIP, 40, 30, 45);
	sld.DontRansackCaptain = true;
	sld.SinkTenPercent = false;
	sld.SaveItemsForDead = true;
	sld.DontClearDead = true;
	sld.AnalizeShips = true;
	Group_FindOrCreateGroup("PDM_CL_Ship");
	Group_SetType("PDM_CL_Ship", "war");
	Group_AddCharacter("PDM_CL_Ship", "PDM_Odli");

	Group_SetGroupCommander("PDM_CL_Ship", "PDM_Odli");
	Group_SetTaskAttack("PDM_CL_Ship", PLAYER_GROUP);
	Group_SetAddress("PDM_CL_Ship", "Trinidad", "quest_ships", "Quest_ships_1");
	Group_LockTask("PDM_CL_Ship");

	PChar.quest.PDM_CL_Odli_Ubit.win_condition.l1 = "NPC_Death";
	PChar.quest.PDM_CL_Odli_Ubit.win_condition.l1.character = "PDM_Odli";
	PChar.quest.PDM_CL_Odli_Ubit.function = "PDM_CL_Odli_Ubit";
}

void PDM_CL_Odli_Ubit(string qName)
{
	ref sld = CharacterFromID("PDM_Octavio_Lambrini");
	sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
	sld.dialog.currentnode   = "Octavio_2_1";
	AddLandQuestMark_Main(sld, "PDM_Clan_Lambrini");
	AddQuestRecord("PDM_Clan_Lambrini", "2");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("ен","на"));
}

void PDM_CL_Ubrat_Lodku(string qName)
{
	ref sld = CharacterFromID("PDM_Odli");
	sld.nonTable = true;
	LAi_SetSitType(sld);
	sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
	sld.dialog.currentnode   = "Antonio_2_1";
	ChangeCharacterAddressGroup(sld, "PortSpein_church", "sit", "sit16");
	LAi_SetLoginTime(sld, 9.0, 14.00);
	DeleteAttribute(sld, "ship");
	sld.ship.type = SHIP_NOTUSED;
	AddLandQuestMark_Main(sld, "PDM_Clan_Lambrini");
} 

void PDM_CL_ClientSpawnInTavern()
{
	ref sld;
	/*if (CharacterIsAlive("PDM_CL_Pokupatel")) //если в будущем захочется пгг
	{
		sld = CharacterFromID("PDM_CL_Pokupatel");
	}
	else
	{*/
	sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_Pokupatel", "JamesB", "man", "man", 10, PIRATE, -1, true));
	sld.name	= FindPersonalName("PDM_CL_Pokupatel_name");
	sld.lastname	= FindPersonalName("PDM_CL_Pokupatel_lastname");
	//}
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	ChangeCharacterAddressGroup(sld, "PortSpein_tavern", "sit", "sit_base2");
}

void PDM_CL_TavernKino(string qName)
{
	StartQuestMovie(true, false, true);
	LAi_FadeEx(0.0, 2.0, 1.0, "", "PDM_CL_TavernKino_2", "");
	LAi_SetStayType(pchar);
	ChangeCharacterAddressGroup(pchar, PChar.location, "waitress", "barmen");
	ClearActiveStageNotifications();
}

void PDM_CL_TavernKino_2(string qName)
{
	locCameraFromToPos(-6.75, 0.92, -1.27, true, -6.90, -0.95, 1.83);
	
	ref sld = GetCharacter(CreateCharacterClone(CharacterFromID("PDM_Octavio_Lambrini"), 0));
	sld.id = "PDM_Octavio_Lambrini_Clone";
	sld.name = FindPersonalName("PDM_Octavio_Lambrini_Clone_name");
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
	sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
	sld.dialog.currentnode = "Octavio_4_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", 0, 0);
}

void PDM_CL_TavernKino_3()
{
	locCameraSleep(true);
	ref sld = CharacterFromID("PDM_Octavio_Lambrini_Clone");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	LAi_FadeEx(1.0, 0.5, 1.0, "", "PDM_CL_TavernKino_4", "");
}

void PDM_CL_TavernKino_4(string qName)
{
	locCameraSleep(false);
	EndQuestMovie();
	locCameraFollowEx(true);
	LAi_SetPlayerType(pchar);
	
	ref sld = characterFromID("PDM_Octavio_Lambrini");
	LAi_CharacterDisableDialog(sld);
	
	sld = CharacterFromID("PDM_CL_Pokupatel");
	ChangeCharacterAddressGroup(sld, "none", "", "");

	sld = CharacterFromID("PDM_Odli");
	sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
	sld.dialog.currentnode   = "Antonio_5_1";
	AddLandQuestMark_Main(sld, "PDM_Clan_Lambrini");

	AddQuestRecord("PDM_Clan_Lambrini", "6");
}

void PDM_CL_OnShore()
{
	int i;
	string sTemp;
	LocatorReloadEnterDisable("Shore60", "reload1_back", true);
	LocatorReloadEnterDisable("Shore60", "boat", true);

	ref sld = CharacterFromID("PDM_Odli");
	LAi_SetActorType(sld);
	ChangeCharacterAddressGroup(sld, "Shore60", "officers", "reload1_1");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

	for (i=1; i<=11; i++)	//англичане
	{
		sTemp = "navy_eng_"+(rand(7)+1);
		sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_EngFriend_"+i, sTemp, "man", "man", sti(pchar.rank), ENGLAND, -1, true));
		FantomMakeCoolFighter(sld, sti(pchar.rank), 30, 30, "blade10", "", 20);
		LAi_SetActorType(sld);
		LAi_CharacterDisableDialog(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		ChangeCharacterAddressGroup(sld, "Shore60", "reload",  "reload1_back");
	}

	for (i=1; i<=3; i++)	//пираты м контрабандисты 1
	{
		sTemp = "citiz_2"+(rand(8)+1);
		sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_PirEnemy_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
		// FantomMakeCoolFighter(sld, sti(pchar.rank), 30, 30, "blade10", "", 20);
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "PDM_CL_PirEnemy_Status");
		ChangeCharacterAddressGroup(sld, "Shore60", "smugglers",  "smuggler0"+i);
	}

	for (i=4; i<=7; i++)	//пираты м контрабандисты 2
	{
		sTemp = "citiz_2"+(rand(8)+1);
		sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_PirEnemy_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
		// FantomMakeCoolFighter(sld, sti(pchar.rank), 30, 30, "blade10", "", 20);
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "PDM_CL_PirEnemy_Status");
		ChangeCharacterAddressGroup(sld, "Shore60", "goto",  "goto4");
	}

	for (i=8; i<=11; i++)	//пираты м контрабандисты 3
	{
		sTemp = "citiz_2"+(rand(8)+1);
		sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_PirEnemy_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
		// FantomMakeCoolFighter(sld, sti(pchar.rank), 30, 30, "blade10", "", 20);
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "PDM_CL_PirEnemy_Status");
		ChangeCharacterAddressGroup(sld, "Shore60", "goto",  "goto2");
	}
	
	for (i=12; i<=15; i++)	//пираты м контрабандисты 4
	{
		sTemp = "citiz_2"+(rand(8)+1);
		sld = GetCharacter(NPC_GenerateCharacter("PDM_CL_PirEnemy_"+i, sTemp, "man", "man", sti(pchar.rank), PIRATE, -1, true));
		// FantomMakeCoolFighter(sld, sti(pchar.rank), 30, 30, "blade10", "", 20);
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "PDM_CL_PirEnemy_Status");
		ChangeCharacterAddressGroup(sld, "Shore60", "goto",  "goto8");
	}

	DoFunctionReloadToLocation("Shore60", "goto", "goto11", "PDM_CL_OnShore_2");
	AddGeometryToLocation("Shore60", "smg");
	pchar.location.from_sea = "Shore60";

	sld = characterFromID("PDM_Octavio_Lambrini");
	sld.rank = sti(pchar.rank);
	sld.SaveItemsForDead = true;
	AddItems(sld, "jewelry1", rand(20)+20);
	AddItems(sld, "jewelry2", rand(20)+20);
	AddItems(sld, "jewelry3", rand(20)+20);
	AddItems(sld, "jewelry4", rand(20)+20);
	AddItems(sld, "jewelry5", rand(20)+20);
	AddItems(sld, "blade9", 1);

	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "PDM_CL_PirEnemy_Status");
	ChangeCharacterAddressGroup(sld, "Shore60", "goto", "goto1");

	sld = CharacterFromID("PDM_CL_Pokupatel");
	sld.rank = sti(pchar.rank);
	sld.SaveItemsForDead = true;
	LAi_SetActorType(sld);
	AddMoneyToCharacter(sld, 50000);
	AddItems(sld, "suit_1", 1);
	AddItems(sld, "map_normal", 1);
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, "PDM_CL_PirEnemy_Status");
	ChangeCharacterAddressGroup(sld, "Shore60", "goto", "goto3");
}

void PDM_CL_OnShore_2()
{
	ref sld;
	int i;
	for (i=1; i<=3; i++)
	{
		sld = characterFromID("PDM_CL_PirEnemy_"+i);
		CharacterTurnByChr(sld, characterFromID("PDM_CL_Pokupatel"));
	}
	for (i=4; i<=11; i++)
	{
		sld = characterFromID("PDM_CL_PirEnemy_"+i);
		CharacterTurnByChr(sld, characterFromID("PDM_Octavio_Lambrini"));
	}
	for (i=12; i<=15; i++)
	{
		sld = characterFromID("PDM_CL_PirEnemy_"+i);
		CharacterTurnToLoc(sld, "goto", "goto9");
	}
	CharacterTurnByChr(characterFromID("PDM_CL_Pokupatel"), characterFromID("PDM_Octavio_Lambrini"));
	CharacterTurnByChr(characterFromID("PDM_Octavio_Lambrini"), characterFromID("PDM_CL_Pokupatel"));
		
	StartQuestMovie(true, false, true);
	LAi_FadeEx(0.0, 2.0, 1.0, "", "", "PDM_CL_OnShore_3");
	locCameraFromToPos(-6.58, 2.23, 11.20, true, -4.42, 0.36, 6.60);
	
	for (i=1; i<=11; i++)
	{
		sld = characterFromID("PDM_CL_EngFriend_"+i);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
	}
	sld = characterFromID("PDM_Odli");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
}

void PDM_CL_OnShore_3(string qName)
{
	DoQuestFunctionDelay("PDM_CL_OnShore_4", 2.0);
}

void PDM_CL_OnShore_4(string qName)
{
	ref sld;
	locCameraFromToPos(5.27, 2.24, -4.16, true, 7.17, 1.06, -7.36);
	DoQuestFunctionDelay("PDM_CL_OnShore_5", 2.2);
	
	sld = characterFromID("PDM_Octavio_Lambrini");
	LAi_ActorAnimation(sld, "dialog_stay9", "", 10.0);
	
	sld = CharacterFromID("PDM_CL_Pokupatel");
	LAi_ActorAnimation(sld, "dialog_stay14", "", 10.0);
}

void PDM_CL_OnShore_5(string qName)
{
	ref sld;
	int i;
	locCameraFromToPos(-11.19, 3.58, 1.51, true, -12.37, 2.56, -2.99);
	
	LAi_SetActorType(pchar);
	LAi_ActorMoveToPoint(pchar, true, 3.01, 1.0, -6.76, "PDM_CL_OnShore_7", -1);
	
	for (i=1; i<=11; i++)
	{
		sld = characterFromID("PDM_CL_EngFriend_"+i);
		LAi_SetActorType(sld);
		LAi_ActorMoveToPoint(sld, true, -1.01, 1.0, -5.76, "", -1);
	}
	sld = characterFromID("PDM_Odli");
	LAi_SetActorType(sld);
	LAi_ActorMoveToPoint(sld, true, 3.01, 1.0, -5.76, "", -1);
	DoQuestFunctionDelay("PDM_CL_OnShore_6", 4.0);
	
	CharacterTurnByPoint(characterFromID("PDM_CL_Pokupatel"), 3.01, 1.0, -5.76);
	CharacterTurnByPoint(characterFromID("PDM_Octavio_Lambrini"), 3.01, 1.0, -6.76);
}

void PDM_CL_OnShore_6(string qName)
{
	locCameraFromToPos(1.02, 2.40, -4.00, true, 2.85, 0.78, -5.63);
}

void PDM_CL_OnShore_7()
{
	LAi_SetPlayerType(pchar);
	ref sld = CharacterFromID("PDM_Octavio_Lambrini");
	sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
	sld.dialog.currentnode   = "Pokupatel_6_1";
	LAi_CharacterEnableDialog(sld);
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void PDM_CL_OnShore_8()
{
	ref sld;
	int i;
	EndQuestMovie();
	locCameraFollowEx(true);
	LAi_SetFightMode(pchar, true);
	
	for (i=1; i<=15; i++)	//пираты и контрабандисты
	{
		sld = CharacterFromID("PDM_CL_PirEnemy_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "PDM_CL_PirEnemy_Status");
	}
	for (i=1; i<=11; i++)	//англичане
	{
		sld = CharacterFromID("PDM_CL_EngFriend_"+i);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sld.lifeday = 0;
	}

	sld = CharacterFromID("PDM_Octavio_Lambrini");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PDM_CL_PirEnemy_Status");

	sld = CharacterFromID("PDM_CL_Pokupatel");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "PDM_CL_PirEnemy_Status");

	sld = CharacterFromID("PDM_Odli");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	sld.QuestImmortal = true;

	LAi_group_SetRelation("PDM_CL_PirEnemy_Status", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("PDM_CL_PirEnemy_Status", LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction("PDM_CL_PirEnemy_Status", "PDM_CL_FinishFight");
}

void PDM_CL_FinishFight(string qName)
{
	LAi_SetFightMode(pchar, false);

	ref sld = CharacterFromID("PDM_Odli");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	sld.lifeday = 0;
	sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
	sld.dialog.currentnode   = "Antonio_8_1";
}

void PDM_CL_FinalNagrada()
{
	SetFunctionExitFromLocationCondition("PDM_CL_ExitInSea", PChar.location, false);
	LocatorReloadEnterDisable("Shore60", "boat", false);
	
	AddCharacterExpToSkill(pchar, "Leadership", 200);
	AddCharacterExpToSkill(pchar, "FencingL", 200);
	AddCharacterExpToSkill(pchar, "FencingS", 200);
	AddCharacterExpToSkill(pchar, "FencingH", 200);
	AddCharacterExpToSkill(pchar, "Pistol", 100);
	ChangeCharacterNationReputation(pchar, ENGLAND, 10);
	ChangeCharacterReputation(pchar, 15);
	
	RemoveMapQuestMark("PortSpein_town", "PDM_Clan_Lambrini");
	CloseQuestHeader("PDM_Clan_Lambrini");
}

void PDM_CL_ExitInSea(string qName)
{
	LocatorReloadEnterDisable("Shore60", "reload1_back", false);
}
//Клан Ламбрини <--

//Прокажённая -->
void PDM_ONV_Nachalo(string qName)
{
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("PDM_secretary", "citiz_13", "man", "man", 10, SPAIN, -1, false));
	sld.name = FindPersonalName("PDM_secretary_name");
	sld.lastname = FindPersonalName("PDM_secretary_lastname");
	LAi_SetCitizenType(sld);
	sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
	sld.dialog.currentnode   = "First_time";
	sld.City = "Beliz";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	sld.talker = 7;
	sld.nation = SPAIN;
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	ChangeCharacterAddressGroup(sld,"Beliz_town","goto","goto5");
	AddLandQuestMark_Main(sld, "PDM_Ohota_na_vedmu");
	AddMapQuestMark_Major("Beliz_town", "PDM_Ohota_na_vedmu", "");
}

void PDM_ONV_InRoom(string qName)
{
	ref sld;
	sld = CharacterFromID("PDM_secretary");
	//ChangeCharacterAddressGroup(sld,"Beliz_TownhallRoom","goto","goto9");
	ChangeCharacterAddressGroup(sld, "CommonBedroom", "barmen", "stay");
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	LAi_ActorSetLayMode(sld);
	
	QuestPointerToLoc("Beliz_townhallroom", "reload", "reload2");
	LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload2", false);

	PChar.quest.PDM_ONV_InRoomTrup.win_condition.l1 = "locator";
	PChar.quest.PDM_ONV_InRoomTrup.win_condition.l1.location = "CommonBedroom";
	PChar.quest.PDM_ONV_InRoomTrup.win_condition.l1.locator_group = "reload";
	PChar.quest.PDM_ONV_InRoomTrup.win_condition.l1.locator = "reload1";
	PChar.quest.PDM_ONV_InRoomTrup.function = "PDM_ONV_InRoomTrup";
	
	sld = CharacterFromID("PDM_ONV_Guard");
	sld.lifeday = 0;
}

void PDM_ONV_InRoomTrup(string qName)
{
	AddQuestRecord("PDM_Ohota_na_vedmu", "4");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
	
	QuestPointerDelLoc("Beliz_townhallroom", "reload", "reload2");
	QuestPointerToLoc("Beliz_townhallroom", "reload", "reload1");
	LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload1", false);
	
	PChar.quest.PDM_ONV_townhall.win_condition.l1 = "location";
	PChar.quest.PDM_ONV_townhall.win_condition.l1.location = "Beliz_TownhallRoom";
	PChar.quest.PDM_ONV_townhall.function = "PDM_ONV_townhall";
}

void PDM_ONV_townhall(string qName)
{
	ref sld;
	int i;
	sld = CharacterFromID("Beliz_Mayor");
	SaveOldDialog(sld);
	sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
	sld.dialog.currentnode   = "DialogWithHuber";
	AddLandQuestMark_Main(sld, "PDM_Ohota_na_vedmu");

	for (i=1; i<=2; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_SoldatGub_"+i, "guard_spa_"+i, "man", "man", 10, SPAIN, -1, true));
		sld.city = "Beliz";
		if (i==1) ChangeCharacterAddressGroup(sld, "Beliz_townhall", "goto", "governor1");
		else ChangeCharacterAddressGroup(sld, "Beliz_townhall", "goto", "goto6");
		sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
		sld.dialog.currentnode   = "SoldatInTownHall";
		LAi_SetOwnerType(sld);
		LAi_SetImmortal(sld, true);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	}
}

void PDM_ONV_ReadyToWork(string qName)
{
	LAi_SetPlayerType(pchar);
	StartInstantDialogNoType("Beliz_Mayor", "DialogWithHuber_7", "Quest\PDM\Ohota_na_vedmu.c");
}

void PDM_ONV_FreeMove()
{
	LocatorReloadEnterDisable("Beliz_Townhall", "reload1_back", false);
	LocatorReloadEnterDisable("Beliz_Townhall", "reload3", true);

	PChar.quest.PDM_ONV_TookQuest.win_condition.l1 = "location";
	PChar.quest.PDM_ONV_TookQuest.win_condition.l1.location = "Beliz_town";
	PChar.quest.PDM_ONV_TookQuest.function = "PDM_ONW_BelizReset";
}

void PDM_ONW_BelizReset(string qName)
{
	LocatorReloadEnterDisable("Beliz_town", "reload3_back", false);
	LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload2", false);
	LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload3", false);
	LocatorReloadEnterDisable("Beliz_Townhall", "reload3", false);
	LocatorReloadEnterDisable("Beliz_townhall", "reload2", false);
	
	QuestPointerDelLoc("Beliz_town", "reload", "reloadR1");
	QuestPointerDelLoc("Beliz_townhallroom", "reload", "reload1");
	ref sld = &Locations[FindLocation("Beliz_TownhallRoom")];
	sld.locators_radius.goto.goto9 = 0.5;
	sld.id.label = "TownhallRoom"; //возвращает работников в спальни

	sld = CharacterFromID("Beliz_Mayor");
	RestoreOldDialog(sld);
}

void PDM_ONW_SilinoSpawn()
{
	AddQuestRecord("PDM_Ohota_na_vedmu", "8");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

	ref sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Silino_Sav", "officer_24", "man", "man", 10, SPAIN, -1, false));
	sld.name = FindPersonalName("PDM_ONV_Silino_Sav_name");
	sld.lastname = FindPersonalName("PDM_ONV_Silino_Sav_lastname");
	sld.city = "SantoDomingo";
	FreeSitLocator("SantoDomingo_tavern", "sit_base2");
	ChangeCharacterAddressGroup(sld,"SantoDomingo_tavern","sit","sit_base2");
	LAi_SetSitType(sld);
	sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
	sld.dialog.currentnode   = "DialogWithSilino_1";
	pchar.questTemp.PDM_ONV_SantoDomingo = true;
	AddLandQuestMark_Main(sld, "PDM_Ohota_na_vedmu");
	AddMapQuestMark_Major("SantoDomingo_town", "PDM_Ohota_na_vedmu", "");
	RemoveMapQuestMark("Beliz_town", "PDM_Ohota_na_vedmu");
}

void PDM_ONW_RoadToSantiago()
{
	ref sld = CharacterFromID("PDM_ONV_Silino_Sav");
	sld.lifeday = 0;

	AddQuestRecord("PDM_Ohota_na_vedmu", "11");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

	LAi_PlaceCharInTavern(pchar);
	LAi_SetPlayerType(pchar);
	locCameraFollowEx(true);

	sld = CharacterFromID("PDM_ONV_Carla");
	sld.city = "Santiago";
	sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
	sld.dialog.currentnode   = "Carla_Final_1";
	ChangeCharacterAddressGroup(sld, "Santiago_tavern", "goto", "goto4");
	LAi_SetWaitressType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	AddLandQuestMark_Main(sld, "PDM_Ohota_na_vedmu");
	AddMapQuestMark_Major("Santiago_town", "PDM_Ohota_na_vedmu", "");
	RemoveMapQuestMark("SantoDomingo_town", "PDM_Ohota_na_vedmu");
}

void PDM_ONW_Kino_1()
{
	ref sld;
	int i;
	StartQuestMovie(true, false, true);

	LAi_FadeEx(0.0, 2.0, 1.0, "", "PDM_ONW_Kino_2", "");
	LAi_SetStayType(pchar);
	
	// расставляем людей
	TeleportCharacterToPosAy(pchar, 19.64, 18.80, -111.19, 2.50);
	
	sld = GetCharacter(NPC_GenerateCharacter("PDM_ONW_Inqizitor", "priest_sp1", "man", "man_B", 20, SPAIN, -1, false));
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, "Cuba_jungle_01", "reload",  "reload1");
	TeleportCharacterToPosAy(sld, 21.80, 18.80, -113.30, 2.50);
	
	sld = CharacterFromID("PDM_ONV_Carla");
	sld.lifeday = 0;
	ChangeCharacterAddressGroup(sld, PChar.location, "quest", "quest1");
	LAi_SetActorType(sld);
	LAi_ActorAnimation(sld, "execution_1", "", 1.8);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("PDM_ONW_Inqizitor"), 0));
	sld.id = "Invisible";
	sld.name = FindPersonalName("PDM_ONW_Inqizitor_name");
	sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Cuba_jungle_01", "goto", "goto4");
	
	for (i=1; i<=4; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_InquisitionGuard_"+i, "elite_spa_3", "man", "man", sti(pchar.rank), SPAIN, 0, true));
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		ChangeCharacterAddressGroup(sld, "Cuba_jungle_01", "reload",  "reload1");
		LAi_CharacterDisableDialog(sld);
		
		if (i==1) TeleportCharacterToPosAy(sld, 20.00, 18.80, -113.10, 2.50);
		else if (i==2) TeleportCharacterToPosAy(sld, 22.00, 18.80, -111.62, 2.50);
		else if (i==3) TeleportCharacterToPosAy(sld, 23.20, 2.00, -120.15, 0.50);
		else if (i==4)
		{
			TeleportCharacterToPosAy(sld, 27.00, 2.00, -118.00, -1.20);
			SendMessage(sld, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", 1, "HandsItems\Fakel", "Saber_hand", 1); // держит факел
			LAi_ActorAnimation(sld, "torch_stand", "", 1.8);
		}
	}
	
	//Мирные жители
	for (i=1; i<=9; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Citizen_"+i, "citiz_"+i, "man", "man", sti(pchar.rank), SPAIN, 0, false));
		LAi_SetActorType(sld);
		LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		ChangeCharacterAddressGroup(sld, "Cuba_jungle_01", "reload",  "reload1");
		if (i==1) TeleportCharacterToPosAy(sld, 21.77, 18.80, -109.00, 2.80);
		else if (i==2) TeleportCharacterToPosAy(sld, 20.36, 18.80, -107.21, 2.50);
		else if (i==3) TeleportCharacterToPosAy(sld, 19.15, 18.80, -108.80, 2.50);
		else if (i==4) TeleportCharacterToPosAy(sld, 20.27, 18.80, -108.61, 2.50);
		else if (i==5) TeleportCharacterToPosAy(sld, 22.69, 18.80, -110.16, 3.00);
		else if (i==6) TeleportCharacterToPosAy(sld, 18.83, 18.80, -109.77, 2.50);
		else if (i==7) TeleportCharacterToPosAy(sld, 19.84, 18.80, -109.99, 2.50);
		else if (i==8) TeleportCharacterToPosAy(sld, 21.20, 18.80, -109.97, 2.65);
		else if (i==9) TeleportCharacterToPosAy(sld, 18.14, 18.80, -110.66, 2.30);
	}
}

void PDM_ONW_Kino_2(string qName)
{
	// locCameraFlyToPositionLookToPoint(27.45, 21.31, -124.83, 21.79, 20.50, -121.00, 24.69, 20.10, -117.79, -1.0, 10000/GetDeltaTime());
	locCameraFlyToPositionLookToPoint(22.45, 20.66, -126.00, 20.02, 20.38, -115.00, 24.69, 20.50, -117.79, -1.0, 10000/GetDeltaTime());
	Pchar.FuncCameraFly = "PDM_ONW_Kino_3";
}

void PDM_ONW_Kino_3()
{
	locCameraFlyToPositionLookToPoint(23.04, 20.72, -115.81, 22.73, 20.60, -115.20, 21.89, 20.26, -113.43, -1.0, 10000/GetDeltaTime());
	Pchar.FuncCameraFly = "";
	DoQuestFunctionDelay("PDM_ONW_Kino_4", 3.0);
}

void PDM_ONW_Kino_4(string qName)
{
	locCameraResetState();
	locCameraFlyToPositionLookToPoint(23.16, 21.44, -116.19, 23.79, 21.29, -116.61, 24.82, 21.04, -117.32, -1.0, 10000/GetDeltaTime());
	Pchar.FuncCameraFly = "";
	DoQuestFunctionDelay("PDM_ONW_Kino_5", 5.0);
	ref sld = CharacterFromID("PDM_ONV_Carla");
	LAi_ActorAnimation(sld, "execution_2", "", 1.8);
}

void PDM_ONW_Kino_5(string qName)
{
	locCameraResetState();
	locCameraFromToPos(21.48, 20.54, -111.64, true, 22.54, 18.87, -113.95);
	
	ref sld = CharacterFromID("Invisible");
	sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
	sld.dialog.currentnode   = "Inqizitor_1";
	LAi_SetActorType(sld);
	LAi_ActorDialogNow(sld, Pchar, "", -1);
	
	sld = CharacterFromID("PDM_ONV_Carla");
	LAi_ActorAnimation(sld, "execution_1", "", 1.8);
	
	//if (LanguageGetLanguage() == "russian") PlaySound("Quest\Witch\Inkvizitor.wav");
}

void PDM_ONW_Kino_6()
{
	// locCameraFromToPos(24.48, 21.13, -113.41, true, 24.73, 19.21, -115.82);
	locCameraFlyToPositionLookToPoint(26.85, 20.77, -112.18, 21.18, 20.90, -116.15, 24.90, 20.50, -117.44, -1.0, 17000/GetDeltaTime());
	Pchar.FuncCameraFly = "";
	
	ref sld = CharacterFromID("PDM_ONV_InquisitionGuard_4");
	TeleportCharacterToPosAy(sld, 26.50, 2.00, -118.70, -1.20);
	LAi_ActorAnimation(sld, "torch_fire", "", 1.8);
	
	DoQuestFunctionDelay("PDM_ONW_Kino_6_1", 1.0);
	DoQuestFunctionDelay("PDM_ONW_Kino_7", 3.0);
	
	KZ|Mute(1);
}

void PDM_ONW_Kino_6_1(string qName)
{
	PlaySound("Quest\Witch\Music.wav");
	PlaySound("Quest\Witch\piple.wav");
}

void PDM_ONW_Kino_7(string qName)
{
	CreateLocationParticles("shipfire", "quest", "quest1", -3.5, 0, 0, "");
	
	ref sld = CharacterFromID("PDM_ONV_Carla");
	LAi_ActorAnimation(sld, "execution_3", "", 1.8);
	
	PlaySound("Quest\Witch\fire.wav");
	
	DoQuestFunctionDelay("PDM_ONW_Kino_7_1", 1.0);
	DoQuestFunctionDelay("PDM_ONW_Kino_8", 7.0);
}

void PDM_ONW_Kino_7_1(string qName)
{
	PlaySound("Quest\Witch\scream.wav");
}

void PDM_ONW_Kino_8(string qName)
{
	CreateLocationParticles("shipfire", "quest", "quest1", 0, 0, 0, "");
	locCameraResetState();
	locCameraFlyToPositionLookToPoint(75.08, 16.98, -136.01, 76.71, 16.85, -136.62, 25.80, 20.92, -117.77, -1.0, 15000/GetDeltaTime());
	Pchar.FuncCameraFly = "";
	DoQuestFunctionDelay("PDM_ONW_Kino_9", 6.0);
}

void PDM_ONW_Kino_9(string qName)
{
	LAi_FadeEx(1.0, 0.0, 0.0, "PDM_ONW_Kino_10", "", "");
}

void PDM_ONW_Kino_10(string qName)
{
	LAi_SetPlayerType(pchar);
	EndQuestMovie();
	locCameraResetState();
	locCameraFollowEx(true);

	// временный фикс вылета
	ref sld = CharacterFromID("PDM_ONV_InquisitionGuard_4");
	LAi_UntieItemFromCharacter(sld, 1);
	// <--

	DoFunctionReloadToLocation("Santiago_Incquisitio", "goto", "goto28", "PDM_ONW_BackToHuber");
}

void PDM_ONW_BackToHuber()
{
	AddQuestRecord("PDM_Ohota_na_vedmu", "14");
	AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
	pchar.questTemp.PDM_ONV_VedmaKaznena = true;
	SetCharacterPerk(pchar, "InquisitionBlessing");
	
	QuestPointerDelLoc("Santiago_town", "reload", "basement1");
	RemoveLandQuestmark_Main(CharacterFromID("Santiago_Inquisitor"), "PDM_Ohota_na_vedmu");
	
	AddLandQuestMark_Main(CharacterFromID("Beliz_Mayor"), "PDM_Ohota_na_vedmu");
	AddMapQuestMark_Major("Beliz_town", "PDM_Ohota_na_vedmu", "");
	RemoveMapQuestMark("Santiago_town", "PDM_Ohota_na_vedmu");
	
	locations[FindLocation("Cuba_jungle_01")].DisableEncounters = false;
}

//Прокажённая <--

//Остепенившийся пират -->
void PDM_Lesopilka_GVIK_InviteHugo()
{
	SetQuestHeader("PDM_Lesopilka");
	AddQuestRecord("PDM_Lesopilka", "1");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Lesopilka", "sSex", GetSexPhrase("","а"));
	
	pchar.questTemp.PDM_Lesopilka_GVIK = "InviteHugo";
	
	RemoveLandQuestmark_Main(CharacterFromID("Hugo_Lesopilka"), "PDM_Lesopilka");
	AddLandQuestMark_Main(CharacterFromID("HWIC_head"), "PDM_Lesopilka");
	AddMapQuestMark_Major("Villemstad_town", "PDM_Lesopilka", "");
	RemoveMapQuestMark("Providencia_town", "PDM_Lesopilka");
}

void PDM_Lesopilka_GVIK_TookDocument()
{
	AddQuestRecord("PDM_Lesopilka", "2");
	AddQuestUserData("PDM_Lesopilka", "sSex", GetSexPhrase("","а"));
	
	pchar.questTemp.PDM_Lesopilka_GVIK = "TookDocument";
	
	ref sld = CharacterFromID("Hugo_Lesopilka");
	ChangeCharacterAddressGroup(sld,"none","","");
	
	RemoveLandQuestmark_Main(CharacterFromID("HWIC_head"), "PDM_Lesopilka");
	AddLandQuestMark_Main(CharacterFromID("Providencia_tavernkeeper"), "PDM_Lesopilka");
	AddMapQuestMark_Major("Providencia_town", "PDM_Lesopilka", "");
	RemoveMapQuestMark("Villemstad_town", "PDM_Lesopilka");
}

void PDM_Lesopilka_GVIK_RoadToLaVega()
{
	AddQuestRecord("PDM_Lesopilka", "3");
	
	pchar.questTemp.PDM_Lesopilka_GVIK = "LaVega";
	
	ref sld = CharacterFromID("Hugo_Lesopilka");
	ChangeCharacterAddressGroup(sld,"LaVega_Tavern","sit","sit5");
	
	RemoveLandQuestmark_Main(CharacterFromID("Providencia_tavernkeeper"), "PDM_Lesopilka");
	RemoveMapQuestMark("Providencia_town", "PDM_Lesopilka");
	AddLandQuestMark_Main(CharacterFromID("Hugo_Lesopilka"), "PDM_Lesopilka");
	AddMapQuestMark_Major("LaVega_town", "PDM_Lesopilka", "");
}

void PDM_Lesopilka_GVIK_HugoHappy()
{
	AddQuestRecord("PDM_Lesopilka", "4");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Lesopilka", "sSex", GetSexPhrase("","а"));
	
	PChar.quest.PDM_HugoSeaHavana.win_condition.l1 = "EnterToSea";
	Pchar.quest.PDM_HugoSeaHavana.function = "PDM_Lesopilka_GVIK_HugoLeave";
	
	pchar.questTemp.PDM_Lesopilka_GVIK = "AcceptHugo";
	
	RemoveLandQuestmark_Main(CharacterFromID("Hugo_Lesopilka"), "PDM_Lesopilka");
	RemoveMapQuestMark("LaVega_town", "PDM_Lesopilka");
	AddLandQuestMark_Main(CharacterFromID("HWIC_head"), "PDM_Lesopilka");
	AddMapQuestMark_Major("Villemstad_town", "PDM_Lesopilka", "");
}

void PDM_Lesopilka_GVIK_HugoLeave(string qName)
{
	ref sld = CharacterFromID("Hugo_Lesopilka");
	ChangeCharacterAddressGroup(sld,"none","","");
}

void PDM_Lesopilka_GVIK_HugoAccept()
{
	AddQuestRecord("PDM_Lesopilka", "5");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Lesopilka", "sSex", GetSexPhrase("","а"));
	
	pchar.questTemp.PDM_Lesopilka_GVIK = "Final";
	
	ref sld = CharacterFromID("Hugo_Lesopilka");
	sld.dialog.filename   = "Quest\PDM\Lesopilka.c";
	sld.dialog.currentnode   = "Novoe_Zadanie_1";
	ChangeCharacterAddressGroup(sld,"Villemstad_Town","goto","goto20");
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
	
	RemoveLandQuestmark_Main(CharacterFromID("HWIC_head"), "PDM_Lesopilka");
	AddLandQuestMark_Main(CharacterFromID("Hugo_Lesopilka"), "PDM_Lesopilka");
}

void PDM_Lesopilka_Treasures_NewQuest()
{
	AddQuestRecord("PDM_Lesopilka", "6");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Lesopilka", "sSex", GetSexPhrase("","а"));

	ref sld = GetCharacter(NPC_GenerateCharacter("PDM_Lesopilka_Galeon", "off_eng_1", "man", "man", sti(pchar.rank), ENGLAND, -1, true));
	//FantomMakeCoolSailor(sld, SHIP_GALEON_L, FindPersonalName("Stormbreaker_ship"), CANNON_TYPE_CANNON_LBS24, 20, 20, 50);
	FantomMakeSmallSailor(sld, SHIP_GALEON_L, FindPersonalName("Stormbreaker_ship"), CANNON_TYPE_CANNON_LBS12, 40, 25, 15, 15, 15);
	FantomMakeCoolFighter(sld, sti(pchar.rank), 20, 20, "blade22", "pistol2", 35);
	//GiveItem2Character(sld, "cirass1");
	//EquipCharacterByItem(sld, "cirass1");
	AddCharacterGoodsSimple(sld, GOOD_GOLD, 200 + rand(400));
	AddCharacterGoodsSimple(sld, GOOD_SILVER, 200 + rand(400));
	AddCharacterGoodsSimple(sld, GOOD_WEAPON, 200);
	SetShipSkill(sld, 20, 20, 25, 15, 40, 30, 15, 15, 15);
	sld.ship.Crew.Morale = 25;
	sld.ship.masts.mast3 = 1;
	sld.ship.masts.mast2 = 1;
	sld.ship.masts.mast1 = 1;
	sld.ship.HP = sti(sld.ship.HP) / 3.5;
	sld.DontRansackCaptain = true;

	Group_FindOrCreateGroup("PDM_Lesopilka_Fleet");
	Group_SetType("PDM_Lesopilka_Fleet", "war");
	Group_AddCharacter("PDM_Lesopilka_Fleet", "PDM_Lesopilka_Galeon");

	Group_SetGroupCommander("PDM_Lesopilka_Fleet", "PDM_Lesopilka_Galeon");
	Group_SetTaskAttack("PDM_Lesopilka_Fleet", PLAYER_GROUP);
	Group_SetAddress("PDM_Lesopilka_Fleet", "Dominica", "quest_ships", "Quest_ship_2");
	Group_LockTask("PDM_Lesopilka_Fleet");

	SetFunctionTimerCondition("PDM_Lesopilka_Treasures_Timer", 0, 0, 30, false);

	PChar.quest.PDM_Lesopilka_Treasures_Win.win_condition.l1 = "NPC_Death";
	PChar.quest.PDM_Lesopilka_Treasures_Win.win_condition.l1.character = "PDM_Lesopilka_Galeon";
	PChar.quest.PDM_Lesopilka_Treasures_Win.function = "PDM_Lesopilka_Treasures_Win";

	PChar.quest.PDM_Lesopilka_Treasures_FoundLog.win_condition.l1 = "item";
	PChar.quest.PDM_Lesopilka_Treasures_FoundLog.win_condition.l1.item = "LesopilkaLog";
	PChar.quest.PDM_Lesopilka_Treasures_FoundLog.function = "PDM_Lesopilka_Treasures_FoundLog";
	
	RemoveLandQuestmark_Main(CharacterFromID("Hugo_Lesopilka"), "PDM_Lesopilka");
	RemoveMapQuestMark("Villemstad_town", "PDM_Lesopilka");
	AddMapQuestMark_Major("Dominica", "PDM_Lesopilka", "");
	
	sld = CharacterFromID("Hugo_Lesopilka");
	LAi_RemoveLoginTime(sld);
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
}

void PDM_Lesopilka_Treasures_Timer(string qName)
{
	ref sld;
	AddQuestRecord("PDM_Lesopilka", "8");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Lesopilka", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("PDM_Lesopilka");
	
	sld = CharacterFromID("PDM_Lesopilka_Galeon");
	sld.lifeday = 0;
	
	sld = CharacterFromID("Hugo_Lesopilka");
	sld.lifeday = 0;
	RemovePassenger(pchar, sld);
	
	DeleteQuestCondition("PDM_Lesopilka_Treasures_Win");
	DeleteQuestCondition("PDM_Lesopilka_Treasures_FoundLog");
}

void PDM_Lesopilka_Treasures_Win(string qName)
{
	ref sld;
	if (!CheckCharacterItem(PChar, "LesopilkaLog"))
	{
		pchar.GenQuest.CabinLock = true;
		Island_SetReloadEnableGlobal("Dominica", false);
		bQuestDisableMapEnter = true;
		
		DoQuestFunctionDelay("PDM_Lesopilka_Treasures_InCabin", 2.5);
	}
	DeleteQuestCondition("PDM_Lesopilka_Treasures_Timer");
	
	Island_SetReloadEnableLocal("Dominica", "reload_1", false);
	Island_SetReloadEnableLocal("Dominica", "reload_2", false);
}

void PDM_Lesopilka_Treasures_InCabin(string qName)
{
	ref sld;
	DeleteAttribute(pchar, "GenQuest.CabinLock");
	pchar.GenQuest.DontSetCabinOfficer = true;
	chrDisableReloadToLocation = true;
	Sea_CabinStartNow();
	
	sld = CharacterFromID("Hugo_Lesopilka");
	ChangeCharacterAddressGroup(sld, Get_My_Cabin(), "rld", "loc1");
	DoQuestFunctionDelay("PDM_Lesopilka_Treasures_InCabin_2", 1.8);
	
	DeleteQuestCondition("PDM_Lesopilka_Treasures_FoundLog");
}

void PDM_Lesopilka_Treasures_InCabin_2(string qName)
{
	ref sld;
	sld = CharacterFromID("Hugo_Lesopilka");
	sld.dialog.filename   = "Quest\PDM\Lesopilka.c";
	sld.dialog.currentnode   = "InCabin_1";
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PDM_Lesopilka_Treasures_InCabin_DlgExit()
{
	ref sld;
	DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
	Island_SetReloadEnableGlobal("Dominica", true);
	chrDisableReloadToLocation = false;
	
	sld = CharacterFromID("Hugo_Lesopilka");
	LAi_SetActorType(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
	sld.location = "None";
	AddQuestRecord("PDM_Lesopilka", "6.2");
	AddQuestUserData("PDM_Lesopilka", "sShip", FindPersonalName("Stormbreaker_ship"));
}

void PDM_Lesopilka_Treasures_FoundLog(string qName)
{
	AddQuestRecord("PDM_Lesopilka", "6.1");
	AddQuestUserData("PDM_Lesopilka", "sShip", FindPersonalName("Stormbreaker_ship"));
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Lesopilka", "sSex", GetSexPhrase("ёл","ла"));
}

void PDM_Lesopilka_Treasures_ReadLog()
{
	AddQuestRecord("PDM_Lesopilka", "7");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Lesopilka", "sSex", GetSexPhrase("","а"));
	DeleteQuestCondition("PDM_Lesopilka_Treasures_Win");
	DeleteQuestCondition("PDM_Lesopilka_Treasures_Timer");

	PChar.quest.PDM_Lesopilka_Treasures_BeforeFight_Shore26.win_condition.l1 = "location";
	PChar.quest.PDM_Lesopilka_Treasures_BeforeFight_Shore26.win_condition.l1.location = "Shore26";
	PChar.quest.PDM_Lesopilka_Treasures_BeforeFight_Shore26.function = "PDM_Lesopilka_Treasures_BeforeFight";
	PChar.quest.PDM_Lesopilka_Treasures_BeforeFight_Shore27.win_condition.l1 = "location";
	PChar.quest.PDM_Lesopilka_Treasures_BeforeFight_Shore27.win_condition.l1.location = "Shore27";
	PChar.quest.PDM_Lesopilka_Treasures_BeforeFight_Shore27.function = "PDM_Lesopilka_Treasures_BeforeFight";
	
	bQuestDisableMapEnter = false;
	PChar.quest.PDM_Lesopilka_Treasures_Leave.win_condition.l1 = "MapEnter";
	PChar.quest.PDM_Lesopilka_Treasures_Leave.function = "PDM_Lesopilka_Treasures_Leave";
	
	Island_SetReloadEnableLocal("Dominica", "reload_1", true);
	Island_SetReloadEnableLocal("Dominica", "reload_2", true);
}

void PDM_Lesopilka_Treasures_Leave(string qName)
{
	ref sld = CharacterFromID("Hugo_Lesopilka");
	sld.lifeday = 0;
	RemovePassenger(pchar, sld);
	
	DeleteQuestCondition("PDM_Lesopilka_Treasures_Fight");
	AddQuestRecord("PDM_Lesopilka", "10");
	if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Lesopilka", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("PDM_Lesopilka");
	TakeItemFromCharacter(pchar, "LesopilkaLog");
	Island_SetReloadEnableLocal("Dominica", "reload_1", true);
	Island_SetReloadEnableLocal("Dominica", "reload_2", true);
}

void PDM_Lesopilka_Treasures_BeforeFight(string qName)
{
	ref sld, loc;
	int i;
	string sTemp;
	
	if (PChar.location == "Shore26") pchar.questTemp.PDM_Lesopilka_Treasures = "Shore26";
	if (PChar.location == "Shore27") pchar.questTemp.PDM_Lesopilka_Treasures = "Shore27";
	DeleteQuestCondition("PDM_Lesopilka_Treasures_BeforeFight_Shore26");
	DeleteQuestCondition("PDM_Lesopilka_Treasures_BeforeFight_Shore27");
	QuestPointerToLoc("Shore26", "reload", "reload1_back");
	QuestPointerToLoc("Shore27", "reload", "reload1_back");
	LocatorReloadEnterDisable("Shore26", "boat", true);
	LocatorReloadEnterDisable("Shore27", "boat", true);
	TakeItemFromCharacter(pchar, "LesopilkaLog");
	PChar.GenQuest.HunterLongPause = true;
	
	PChar.quest.PDM_Lesopilka_Treasures_Kino_1.win_condition.l1 = "location";
	PChar.quest.PDM_Lesopilka_Treasures_Kino_1.win_condition.l1.location = "Dominica_jungle_01";
	PChar.quest.PDM_Lesopilka_Treasures_Kino_1.function = "PDM_Lesopilka_Treasures_Kino_1";
	//ставим укрепления
	loc = &Locations[FindLocation("Dominica_jungle_01")];
	loc.models.always.jungle_outpost = "jungle6_outpost";
	loc.models.always.jungle_outpost.tech = "DLightModel";
	loc.models.always.locators = "jungle6_outpost_locators";
	loc.models.day.charactersPatch = "jungle6_outpost_patch";
	loc.models.night.charactersPatch = "jungle6_outpost_patch";
	//ставим в грот золото
	loc = &Locations[FindLocation("Dominica_Grot")];
	loc.models.always.GrotI_gold = "GrotI_gold";
	loc.models.day.charactersPatch = "GrotI_gold_patch";
	loc.models.night.charactersPatch = "GrotI_gold_patch";
	loc.models.always.locators = "GrotI_gold_locators";
	loc.locators_radius.box.private1 = 2.0;
	loc.locators_radius.box.box1 = 0.0;
	loc.private1.items.incas_collection = 3;
	loc.private1.items.Chest = 20;
	loc.private1.items.jewelry5 = 50;
	loc.private1.items.jewelry17 = 50;
	loc.private1.items.jewelry1 = rand(10)+5;
	loc.private1.items.jewelry3 = rand(10)+5;
	loc.private1.items.jewelry4 = rand(10)+5;

	sld = CharacterFromID("Hugo_Lesopilka");
	ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto8");
	LAi_SetActorType(sld);
	LAi_ActorFollow(sld, pchar, "", -1);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	
	//------------------------наши матросы-------------------
	for (i=1; i<=18; i++)
    {
		sTemp = "citiz_3"+(rand(8)+1);
		if (i==6) sTemp = "citiz_30";
		sld = GetCharacter(NPC_GenerateCharacter("OurSailor_"+i, sTemp, "man", "man", sti(pchar.rank), HOLLAND, -1, true));
		ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto8");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (i=19; i<=22; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("OurSailor_"+i, "mush_ctz_"+(rand(2)+4), "man", "mushketer", sti(pchar.rank), HOLLAND, -1, false));
		ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto8");
		LAi_SetWarriorType(sld);
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
}

void PDM_Lesopilka_Treasures_Kino_1(string qName)
{
	ref sld;
	int i;
	string sTemp;
	
	Log_Clear();
	bDisableCharacterMenu = true;
	chrDisableReloadToLocation = true;
	LAi_SetActorType(pchar);
	sld = CharacterFromID("Hugo_Lesopilka");
	if (CheckAttribute(pchar, "questTemp.PDM_Lesopilka_Treasures") && pchar.questTemp.PDM_Lesopilka_Treasures == "Shore26")
	{
		ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload2");
	}
	if (CheckAttribute(pchar, "questTemp.PDM_Lesopilka_Treasures") && pchar.questTemp.PDM_Lesopilka_Treasures == "Shore27")
	{
		ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload1");
	}
	
//----------------------враги-------------------------
	for (i=1; i<=6; i++)
    {
        sTemp = "navy_eng_"+(rand(7)+1);
		if (i==6) sTemp = "off_eng_1";
 		sld = GetCharacter(NPC_GenerateCharacter("EngEnemy_"+i, sTemp, "man", "man", sti(pchar.rank), ENGLAND, 0, true));
		LAi_SetActorType(sld);
        ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "quest8");
	}
	for (i=7; i<=12; i++)
    {
		sTemp = "navy_eng_"+(rand(7)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("EngEnemy_"+i, sTemp, "man", "man", sti(pchar.rank), ENGLAND, 0, true));
		LAi_SetActorType(sld);
        ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "quest10");
	}
	// for (i=13; i<=18; i++)
    // {
		// sTemp = "navy_eng_"+(rand(7)+1);
 		// sld = GetCharacter(NPC_GenerateCharacter("EngEnemy_"+i, sTemp, "man", "man", sti(pchar.rank), ENGLAND, 0, true));
		// LAi_SetActorType(sld);
        // ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "quest10");
	// }
	for (i=1; i<=7; i++)
    {
 		sld = GetCharacter(NPC_GenerateCharacter("EngEnemy_Mushket_"+i, "navy_mush_eng_"+(rand(2)+1), "man", "mushketer", sti(pchar.rank), ENGLAND, 0, false));
		sld.MusketerDistance = 0;
		LAi_SetWarriorType(sld);
        ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "quest"+i);
	}
	
	StartQuestMovie(true, false, true);
	LAi_FadeEx(0.0, 2.0, 1.0, "", "PDM_Lesopilka_Treasures_Kino_1_1", "");
}

void PDM_Lesopilka_Treasures_Kino_1_1(string qName)
{
	// locCameraFlyToPositionLookToPoint(-2.02, 6.82, 1.39, -2.17, 6.75, 1.25, -4.36, 5.74, -1.21, -1.0, 5000/GetDeltaTime());
	locCameraFlyToPositionLookToPoint(-3.07, 6.65, 0.92, -3.18, 6.53, 0.69, -4.17, 6.04, -1.33, -1.0, 5000/GetDeltaTime());
	Pchar.FuncCameraFly = "PDM_Lesopilka_Treasures_Kino_2";
	
	TEV.Music.QuestMusic = "Music\Special\Quest\PDM\Fight_01.mp3";
	PlayMusic(TEV.Music.QuestMusic, 1000);
}

void PDM_Lesopilka_Treasures_Kino_2(string qName)
{
	locCameraFlyToPositionLookToPoint(2.19, 4.71, -14.83, 0.78, 4.45, -11.77, -3.98, 3.39, -1.35, -1.0, 5000/GetDeltaTime());
	Pchar.FuncCameraFly = "PDM_Lesopilka_Treasures_Kino_3";
}

void PDM_Lesopilka_Treasures_Kino_3()
{
	locCameraFlyToPositionLookToPoint(5.15, 0.68, 4.90, -0.10, 1.45, 9.39, -4.03, 3.65, 0.50, -1.0, 5000/GetDeltaTime());
	Pchar.FuncCameraFly = "PDM_Lesopilka_Treasures_Kino_4";
}

void PDM_Lesopilka_Treasures_Kino_4()
{
	locCameraFlyToPositionLookToPoint(-14.25, 1.61, -9.11, -14.96, 1.51, -8.81, -20.03, 0.79, -6.67, -1.0, 7000/GetDeltaTime());
	Pchar.FuncCameraFly = "";
	
	ref sld = CharacterFromID("EngEnemy_6");
	LAi_ActorAnimation(sld, "dialog_stay10", "", 10.0);
	
	DoQuestFunctionDelay("PDM_Lesopilka_Treasures_Kino_5", 2.5);
}

void PDM_Lesopilka_Treasures_Kino_5(string qName)
{
	LAi_FadeEx(1.0, 0.5, 1.0, "PDM_Lesopilka_Treasures_Kino_6", "PDM_Lesopilka_Treasures_Fight", "");
}

void PDM_Lesopilka_Treasures_Kino_6(string qName)
{
	locCameraResetState();
	locCameraFollowEx(true);
}

void PDM_Lesopilka_Treasures_Fight(string qName)
{
	EndQuestMovie();
	LAi_SetPlayerType(pchar);
	
	ref sld;
	int i;
	string sTemp = "PDM_Lesopilka_Treasures_Fight_EnemyGroup";
	
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(pchar, true);
	bDisableCharacterMenu = false;
	
	sld = CharacterFromID("Hugo_Lesopilka");
	LAi_SetImmortal(sld, false);
	sld.QuestImmortal = true;
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	
//------------------------наши матросы-------------------
	for (i=1; i<=22; i++)
	{
		sld = CharacterFromID("OurSailor_"+i);
		if (CheckAttribute(pchar, "questTemp.PDM_Lesopilka_Treasures") && pchar.questTemp.PDM_Lesopilka_Treasures == "Shore26")
		{
			ChangeCharacterAddressGroup(sld, pchar.location, "officers",  "reload2_2");
		}
		if (CheckAttribute(pchar, "questTemp.PDM_Lesopilka_Treasures") && pchar.questTemp.PDM_Lesopilka_Treasures == "Shore27")
		{
			ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto2");
		}
	}
	
	for (i=1; i<=18; i++)
	{
		sld = CharacterFromID("OurSailor_"+i);
		LAi_SetWarriorType(sld);
		LAi_CharacterDisableDialog(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}
	for (i=19; i<=22; i++)
	{
		sld = CharacterFromID("OurSailor_"+i);
		sld.MusketerDistance = 5;
		LAi_SetWarriorType(sld);
		LAi_CharacterDisableDialog(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
	}

//----------------------враги-------------------------
	for (i=1; i<=7; i++)
	{
		sld = CharacterFromID("EngEnemy_Mushket_"+i);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, sTemp);
	}
	LAi_group_SetRelation(sTemp, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups(sTemp, LAI_GROUP_PLAYER, false);
	LAi_group_SetCheckFunction(sTemp, "PDM_Lesopilka_Treasures_WinInJungle");
	
	DoQuestFunctionDelay("PDM_Lesopilka_Treasures_Fight_2", 5.0);
}

void PDM_Lesopilka_Treasures_Fight_2(string qName)
{
	ref sld;
	int i;
	for (i=1; i<=12; i++)
	{
		sld = CharacterFromID("EngEnemy_"+i);
		LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "PDM_Lesopilka_Treasures_Fight_EnemyGroup"); 
	}
	
	DoQuestFunctionDelay("PDM_Lesopilka_Treasures_Fight_3", 5.0);
}

void PDM_Lesopilka_Treasures_Fight_3(string qName)
{
	ref sld;
	int i;
	string sTemp;
	for (i=19; i<=24; i++)
    {
		sTemp = "navy_eng_"+(rand(7)+1);
 		sld = GetCharacter(NPC_GenerateCharacter("EngEnemy_"+i, sTemp, "man", "man", sti(pchar.rank), ENGLAND, 0, true));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "PDM_Lesopilka_Treasures_Fight_EnemyGroup");
        ChangeCharacterAddressGroup(sld, pchar.location, "reload",  "reload3");
	}
}

void PDM_Lesopilka_Treasures_WinInJungle(string qName)
{
	StopMusic();
	DeleteAttribute(&TEV, "Music.QuestMusic");
	LAi_group_Delete("PDM_Lesopilka_Treasures_Fight_EnemyGroup");
	alarmed = 0;
	ref sld;
	sld = CharacterFromID("Hugo_Lesopilka");
	DeleteAttribute(sld, "QuestImmortal");
	LAi_SetImmortal(sld, true);
	sld.dialog.filename   = "Quest\PDM\Lesopilka.c";
	sld.dialog.currentnode   = "WinOnJungle_1";
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	KZ|Select("");
}

void PDM_Lesopilka_Treasures_GoToGrot(string qName)
{
	ref sld;
	int i;
	sld = CharacterFromID("Hugo_Lesopilka");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorFollowEverywhere(sld, "", -1);
	
	for (i=1; i<=22; i++)
	{
		if (CharacterIsAlive("OurSailor_"+i))
		{
			sld = CharacterFromID("OurSailor_"+i);
			sld.lifeday = 0;
		}
	}
	
	chrDisableReloadToLocation = false;
	AddQuestRecord("PDM_Lesopilka", "9");
	
	QuestPointerToLoc("Dominica_Jungle_01", "reload", "reload3_back");
	QuestPointerToLoc("Dominica_CaveEntrance", "reload", "reload1_back");
	
	SetFunctionLocationCondition("PDM_Lesopilka_Treasures_InGrot", "Dominica_Grot", false);
}

void PDM_Lesopilka_Treasures_InGrot(string qName)
{
	Log_Clear();
	bDisableCharacterMenu = true;
	RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
	ref sld;
	StartQuestMovie(true, false, true);
	LAi_FadeEx(0.0, 2.0, 1.0, "", "PDM_Lesopilka_Treasures_InGrot_2", "");
	
	LAi_SetStayType(pchar);
	TeleportCharacterToPos(pchar, 50.00, -5.22, 50.00);
	
	sld = CharacterFromID("Hugo_Lesopilka");
	LAi_type_actor_Reset(sld);
	LAi_SetActorType(sld);
	TeleportCharacterToPos(sld, 50.00, -5.22, 50.00);
	
	sld = GetCharacter(CreateCharacterClone(pchar, 0));
	sld.id = "PDM_GG_Clone";
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
	LAi_SetActorType(sld);
	
	sld = GetCharacter(CreateCharacterClone(CharacterFromID("Hugo_Lesopilka"), 0));
	sld.id = "PDM_Lesopilka_Clone";
	ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto1");
	LAi_SetActorType(sld);

	TEV.Music.QuestMusic = "Music\Colony\Town\Pirate\Day\Prt_Town_sd1.ogg";
	PlayMusic(TEV.Music.QuestMusic, 1000);
}

void PDM_Lesopilka_Treasures_InGrot_2(string qName)
{
	locCameraFlyToPositionLookToPoint(5.92, -0.10, 1.87, 5.61, -0.05, 2.59, 4.54, 0.09, 5.10, -1.0, 5000/GetDeltaTime());
	Pchar.FuncCameraFly = "PDM_Lesopilka_Treasures_InGrot_3";
}

void PDM_Lesopilka_Treasures_InGrot_3()
{
	ref sld;
	locCameraFromToPos(2.71, -0.02, 7.95, true, 3.15, -1.14, 3.84);
	
	sld = CharacterFromID("PDM_GG_Clone");
	LAi_ActorGoToLocatorNoCheck(sld, "quest", "quest1", "PDM_Lesopilka_Treasures_InGrot_3_1", -1);
	
	sld = CharacterFromID("PDM_Lesopilka_Clone");
	LAi_ActorGoToLocatorNoCheck(sld, "quest", "quest2", "", -1);
	
	DoQuestFunctionDelay("PDM_Lesopilka_Treasures_InGrot_4", 6.0);
}

void PDM_Lesopilka_Treasures_InGrot_4(string qName)
{
	LAi_FadeEx(1.0, 0.0, 1.0, "", "PDM_Lesopilka_Treasures_InGrot_5", "");
}

void PDM_Lesopilka_Treasures_InGrot_5(string qName)
{
	ref sld;
	// locCameraFromToPos(5.02, 1.67, 2.11, true, 4.88, -0.78, 4.25);
	locCameraFromToPos(6.71, 0.72, 7.69, true, 4.34, -1.04, 5.17);
	
	sld = CharacterFromID("PDM_GG_Clone");
	TeleportCharacterToLocatorIgnoreCollision(sld, "quest", "quest1");
	LAi_ActorAnimation(sld, "gold_1_1", "", 1.8);
	
	sld = CharacterFromID("PDM_Lesopilka_Clone");
	TeleportCharacterToLocatorIgnoreCollision(sld, "quest", "quest2");
	LAi_ActorAnimation(sld, "gold_2_1", "", 1.8);
	
	sld = CharacterFromID("Hugo_Lesopilka");
	sld.dialog.filename   = "Quest\PDM\Lesopilka.c";
	sld.dialog.currentnode   = "InGrot_1";
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void PDM_Lesopilka_Treasures_InGrot_6(string qName)
{
	locCameraFromToPos(6.18, 1.98, 2.29, true, 4.95, -1.00, 4.44);
	
	ref sld;
	
	sld = CharacterFromID("PDM_GG_Clone");
	LAi_ActorAnimation(sld, "gold_1_4", "", 10.8);
	
	sld = CharacterFromID("PDM_Lesopilka_Clone");
	LAi_ActorAnimation(sld, "gold_2_2", "", 10.8);
	
	DoQuestFunctionDelay("PDM_Lesopilka_Treasures_InGrot_6_1", 1.5);
}

void PDM_Lesopilka_Treasures_InGrot_6_1(string qName)
{
	locCameraFromToPos(7.04, 2.00, 6.23, true, 4.68, -1.00, 4.93);
	
	DoQuestFunctionDelay("PDM_Lesopilka_Treasures_InGrot_7", 2.5);
}

void PDM_Lesopilka_Treasures_InGrot_7(string qName)
{
	locCameraFromToPos(5.71, 1.61, 2.57, true, 4.78, -1.00, 4.13);
	
	DoQuestFunctionDelay("PDM_Lesopilka_Treasures_InGrot_8", 2.0);
}

void PDM_Lesopilka_Treasures_InGrot_8(string qName)
{
	LAi_FadeEx(1.0, 0.0, 1.0, "", "PDM_Lesopilka_Treasures_InGrot_9", "");
}

void PDM_Lesopilka_Treasures_InGrot_9(string qName)
{
	locCameraFromToPos(4.66, 2.14, 3.31, true, 4.66, -1.00, 4.65);

	ref sld;
	
	sld = CharacterFromID("PDM_GG_Clone");
	LAi_ActorAnimation(sld, "gold_1_5", "", 10.8);
	
	sld = CharacterFromID("PDM_Lesopilka_Clone");
	LAi_ActorAnimation(sld, "gold_2_5", "", 10.8);
	
	sld = CharacterFromID("Hugo_Lesopilka");
	sld.dialog.filename   = "Quest\PDM\Lesopilka.c";
	sld.dialog.currentnode   = "InGrot_11";
	LAi_ActorDialogNow(sld, Pchar, "", -1);
}

void PDM_Lesopilka_Treasures_InGrot_10(string qName)
{
	LAi_FadeEx(1.0, 1.0, 1.0, "PDM_Lesopilka_Treasures_InGrot_11", "PDM_Lesopilka_Treasures_InGrot_12", "");
	locCameraSleep(true);
}

void PDM_Lesopilka_Treasures_InGrot_11(string qName)
{
	ref sld;
	locCameraSleep(false);
	sld = CharacterFromID("PDM_GG_Clone");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("PDM_Lesopilka_Clone");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	sld = CharacterFromID("Hugo_Lesopilka");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	ChangeCharacterAddressGroup(pchar, PChar.location, "quest", "quest4");
}

void PDM_Lesopilka_Treasures_InGrot_12(string qName)
{
	EndQuestMovie();
	LAi_SetPlayerType(pchar);
	locCameraFollowEx(true);
	
	PChar.quest.PDM_Lesopilka_Treasures_BackToVillemstad.win_condition.l1 = "MapEnter";
	PChar.quest.PDM_Lesopilka_Treasures_BackToVillemstad.function = "PDM_Lesopilka_Treasures_BackToVillemstad";
	
	RemoveMapQuestMark("Dominica", "PDM_Lesopilka");
	AddMapQuestMark_Major("Villemstad_town", "PDM_Lesopilka", "");
	QuestPointerToLoc("Dominica_Grot", "box", "private1");
	QuestPointerDelLoc("Shore26", "reload", "reload1_back");
	QuestPointerDelLoc("Shore27", "reload", "reload1_back");
	QuestPointerDelLoc("Dominica_Jungle_01", "reload", "reload3_back");
	QuestPointerDelLoc("Dominica_CaveEntrance", "reload", "reload1_back");
	LocatorReloadEnterDisable("Shore26", "boat", false);
	LocatorReloadEnterDisable("Shore27", "boat", false);
	DeleteQuestCondition("PDM_Lesopilka_Treasures_Leave");
	bDisableCharacterMenu = false;
}

void PDM_Lesopilka_Treasures_BackToVillemstad(string qName)
{
	DeleteAttribute(pchar, "GenQuest.HunterLongPause");
	ref loc;
	
	loc = &Locations[FindLocation("Dominica_jungle_01")];
	DeleteAttribute(&Locations[loc], "models.always.jungle_outpost");	
	loc.models.always.locators = "jungle6_locators";		
	loc.models.day.charactersPatch = "jungle6_patch";
	loc.models.night.charactersPatch = "jungle6_patch";
	
	loc = &Locations[FindLocation("Dominica_Grot")];
	DeleteAttribute(&Locations[loc], "models.always.GrotI_gold");	
	loc.models.day.charactersPatch = "GrotI_patch";
	loc.models.night.charactersPatch = "GrotI_patch";
	loc.models.always.locators = "GrotI_locators";
	loc.locators_radius.box.box1 = 0.5;
	QuestPointerDelLoc("Dominica_Grot", "box", "private1");
	
	PChar.quest.PDM_Lesopilka_Treasures_Final.win_condition.l1 = "location";
	PChar.quest.PDM_Lesopilka_Treasures_Final.win_condition.l1.location = "Villemstad_town";
	PChar.quest.PDM_Lesopilka_Treasures_Final.function = "PDM_Lesopilka_Treasures_Final";
}

void PDM_Lesopilka_Treasures_Final(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld;
	sld = CharacterFromID("Hugo_Lesopilka");
	sld.dialog.filename   = "Quest\PDM\Lesopilka.c";
	sld.dialog.currentnode   = "Final_1";
	ChangeCharacterAddressGroup(sld, "Villemstad_town", "quest", "quest1");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void PDM_Lesopilka_Treasures_Final_2(string qName)
{
	chrDisableReloadToLocation = false;
	ref sld;
	sld = CharacterFromID("Hugo_Lesopilka");
	RemovePassenger(pchar, sld);
	sld.City = "Villemstad";
	sld.location = "None";
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
	CloseQuestHeader("PDM_Lesopilka");
	RemoveMapQuestMark("Villemstad_town", "PDM_Lesopilka");
}

//Остепенившийся пират <--

void StartInstantDialogNoType(string id, string node, string fileName)
{
	DialogExit();
	ref sld = CharacterFromId(id);
	sld.Dialog.Filename = fileName;
	sld.dialog.currentnode = node;
	pchar.InstantDialog = sld.id;
	DoQuestFunctionDelay("InstantDialogNoType", 0);
}

void InstantDialogNoType(string qName)
{
	ref sld = CharacterFromId(pchar.InstantDialog);
	sld.chr_ai.tmpl.dialog = "";
	sld.chr_ai.tmpl.time = "0";
	sld.chr_ai.tmpl.dlgtime = "-1";
	sld.chr_ai.tmpl.state = "wait";
	DeleteAttribute(sld, "chr_ai.tmpl.poklon");
	LAi_tmpl_dialog_StartDialog(sld, pchar, -1.0);
}

void StartInstantDialog(string id, string node, string fileName)
{
	DialogExit();
	ref sld = CharacterFromId(id);
	sld.Dialog.Filename = fileName;
	sld.dialog.currentnode = node;
	pchar.InstantDialog = sld.id;
	DoQuestFunctionDelay("InstantDialog", 0);
}

void InstantDialog(string qName)
{
	ref sld = CharacterFromID(pchar.InstantDialog);
	LAi_SetStayTypeNoGroup(sld);
	LAi_tmpl_SetDialog(sld, pchar, -1.0);
}

void SaveOldDialog(ref chr)
{
	chr.Dialog.FilenameBackup = chr.Dialog.Filename;
	chr.dialog.currentnodeBackup   = chr.dialog.currentnode;
}

void RestoreOldDialog(ref chr)
{
	chr.Dialog.Filename = chr.Dialog.FilenameBackup;
	chr.dialog.currentnode   = chr.dialog.currentnodeBackup;
}
//Тичингиту
void FreeTichingituOver(string qName)//удаляем Тичингиту
{
	DeleteAttribute(pchar, "questTemp.Tichingitu");
	if (CheckCharacterItem(pchar, "letter_A")) RemoveItems(pchar, "letter_A", 1); // 170712
}

void SetTichingituJail() //ставим Тичингиту
{
	ref sld = GetCharacter(NPC_GenerateCharacter("Tichingitu", "Tichingitu", "man", "man", 10, PIRATE, -1, false));
	sld.name = FindPersonalName("Tichingitu_name");
	sld.lastname = "";
	sld.greeting = "GR_Tichingitu";
    sld.Dialog.Filename = "Quest\Tichingitu.c";
	sld.dialog.currentnode = "Tichingitu";
	sld.rank = 12;
	sld.HeroModel = "Tichingitu,Tichingitu_1,Tichingitu_2,Tichingitu_3,Tichingitu_4,Tichingitu_5";
	LAi_SetHP(sld, 145.0, 145.0);
	SetSPECIAL(sld, 6, 9, 7, 3, 9, 7, 6); //(Сила, Воспр, Выносл, Обаяние, Обуч, Реак, Удача)
	SetSelfSkill(sld, 70, 10, 10, 50, 20);  //(ЛО, СО, ТО, огнестрел, фортуна)
    SetShipSkill(sld, 5, 5, 2, 5, 1, 2, 1, 1, 30); //(лидер, торг, точн, пушки, навиг, ремонт, аборд, защита, скрыт)
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "BasicDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunAdvanced");
	SetCharacterPerk(sld, "MusketsTraining");
	//черты
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "LoyalOff");
	SetCharacterPerk(sld, "Redskin");
	SetCharacterPerk(sld, "NoCaptain");
	SetCharacterPerk(sld, "MusketeerOnly");
	SetCharacterPerk(sld, "WeaponBonding");
	GiveItem2Character(sld, "unarmed");
	sld.equip.blade = "unarmed";
	sld.equip.gun = "";
	sld.HoldEquip = true; // не отдавать оружие (для мушкетёров)
	ChangeCharacterAddressGroup(sld, "BasTer_prison", "goto", "goto9");
	LAi_SetStayType(sld);
	LAi_SetImmortal(sld, true); // 170712
}
//
// EvgAnat - дикие карибы
void SetIndiansToLocation(string qName)
{
	aref _location;
	makearef(_location, Locations[FindLocation(pchar.location)]);
	int iRank;
	ref sld;
	bMonstersGen = true; //флаг генерации монстров

	// генерим ранг 
	iRank =	GetCoffDiff(sti(pchar.rank)+3, 1000);

	aref grp;
	makearef(grp, _location.locators.monsters);
	int num = GetAttributesNum(grp);
	int rNum = drand(num);

	for(int i = 0; i < num; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Indian_"+_location.index+"_"+i, "AztecWarrior"+(rand(4)+1), "man", "man", iRank, PIRATE, 1, true));
		sld.indian = "1";
		//один кулфайтер, типо босс. остальные послабже, но не лохи
		if (i == 0) FantomMakeCoolFighter(sld, sti(pchar.rank)+5, 90, 90, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol3"), MOD_SKILL_ENEMY_RATE*4);
		else SetFantomParamHunter(sld);
		DeleteAttribute(sld, "SuperShooter");
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
		ChangeCharacterAddressGroup(sld, _location.id, "monsters", GetAttributeName(GetAttributeN(grp, i)));
		// evganat - энциклопедия
		if(i == 0)
		{
			if(CheckRandomPage("questskeleton", "", -1))
			{
				sld.encyclopedia.tome = GetRandomTome();
				sld.encyclopedia.page = 5;
			}
		}
	}
	chrDisableReloadToLocation = true;
	characters[sti(_location.DestroyGhost)].quest.DestroyGhost = "GoodResult";
	DeleteAttribute(_location, "DestroyGhost");
	LAi_LocationDisableMonGenTimer(_location.id, 3); //монстров не генерить 3 дня
	LAi_group_SetCheck(LAI_GROUP_MONSTERS, "Church_ClearGhost");
	AddQuestRecordEx(pchar.questTemp.GhostType.title + "Church_DestroyGhost", "Church_DestroyGhost", "5");
}

void AddSimpleRumourToAllNations(string sText, int iTime, int iQty)
{
	for(int i=0; i<MAX_NATIONS; i++)
	{
		AddSimpleRumour(sText, i, iTime, iQty);
	}
}

// evganat - пасха

void EasterCheckSkeleton()
{
	DeleteAttribute(pchar, "questTemp.easter");
	return;
	if(pchar.location != "Cumana_deadlock")
		return;
	if(sti(pchar.rank) < 10 || !CheckCharacterPerk(pchar, "WildCaribbean"))
		return;
	int i = FindLocation("Cumana_deadlock");
	if(CheckAttribute(&locations[i],"private1.items.mineral8") && sti(locations[i].private1.items.mineral8) >= 10)
	{
		EasterGenerateIndian();
		pchar.questTemp.easter.checkskeleton = 1;
	}
}

void EasterGenerateIndian()
{
	DeleteAttribute(pchar, "questTemp.easter");
	return;
	ref sld = GetCharacter(NPC_GenerateCharacter("Huahuantli", "Huahuantli", "skeleton", "man", 100, PIRATE, -1, false));
	sld.undead = "1";
	sld.name = FindPersonalName("Huahuantli_name");	// покровитель мёртвых воинов, будет возмущаться по поводу осквернения тела павшего воина
	sld.lastname = "";
	LAi_SetActorType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_ACTOR);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Cumana_deadlock", "monsters", "monster4");
	sld.Dialog.Filename = "Quest\Easter.c";
	sld.dialog.currentnode = "Huahuantli_1";
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}	

void EasterOpenPassage()
{
	DeleteAttribute(pchar, "questTemp.easter");
	return;
	int i = FindLocation("Cumana_deadlock");
	DeleteAttribute(&Locations[i],"models.always.l4");
	locations[i].models.day.charactersPatch = "jungle9_patch";
	locations[i].models.night.charactersPatch = "jungle9_patch";
}

void EasterReload()
{
	DeleteAttribute(pchar, "questTemp.easter");
	return;
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	pchar.locx = locx;
	pchar.locy = locy;
	pchar.locz = locz;
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_19"), "Reload_To_Location", 0.1, 1.0);
	SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
	LaunchFrameForm();
	ref sld = CharacterFromId("Huahuantli");
	sld.dialog.currentnode = "Huahuantli_final";
	LAi_ActorDialog(sld, pchar, "", 1.0, 0);
}

void EasterGenerateGods()
{
	DeleteAttribute(pchar, "questTemp.easter");
	return;
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("Atlaua", "Atlaua", "skeleton", "man", 100, PIRATE, -1, false));
	sld.undead = "1";
	sld.name = FindPersonalName("Atlaua_name");	// бог воды
	sld.lastname = "";
	LAi_group_MoveCharacter(sld, LAI_GROUP_ACTOR);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Cave_Pashalka", "sit", "sit31");
	LAi_SetSitType(sld);
	sld.Dialog.Filename = "Quest\Easter.c";
	sld.dialog.currentnode = "Atlaua_1";
	
	sld = GetCharacter(NPC_GenerateCharacter("Xiuhtecuhtli", "Xiuhtecuhtli", "skeleton", "man", 100, PIRATE, -1, false));
	sld.undead = "1";
	sld.name = FindPersonalName("Xiuhtecuhtli_name");	// бог огня
	sld.lastname = "";
	LAi_group_MoveCharacter(sld, LAI_GROUP_ACTOR);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Cave_Pashalka", "sit", "sit1");
	LAi_SetHuberType(sld);
	sld.Dialog.Filename = "Quest\Easter.c";
	sld.dialog.currentnode = "Xiuhtecuhtli_1";
	
	sld = GetCharacter(NPC_GenerateCharacter("Huitzilopochtli", "Huitzilopochtli", "skeleton", "man", 100, PIRATE, -1, false));
	sld.undead = "1";
	sld.name = FindPersonalName("Huitzilopochtli_name");	// бог войны
	sld.lastname = "";
	LAi_SetStayType(sld);
	LAi_group_MoveCharacter(sld, LAI_GROUP_ACTOR);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld, "Cave_Pashalka", "goto", "goto3");
	sld.Dialog.Filename = "Quest\Easter.c";
	sld.dialog.currentnode = "Huitzilopochtli_1";
	
	SetFunctionTimerCondition("EasterGodDissapear", 0, 0, 1, false);
}

void EasterGodDissapear()
{
	DeleteAttribute(pchar, "questTemp.easter");
	return;
	ref sld;
	sld = characterFromId("Atlaua");	
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = characterFromId("Xiuhtecuhtli");	
	ChangeCharacterAddressGroup(sld, "none", "", "");
	sld = characterFromId("Huitzilopochtli");	
	ChangeCharacterAddressGroup(sld, "none", "", "");
	
	pchar.questTemp.easter.gods = 1;	// после первого исчезновения начнут появляться по расписанию.
}

void EasterCheckGodDay()
{
	DeleteAttribute(pchar, "questTemp.easter");
	return;
	if(!CheckAttribute(pchar, "questTemp.easter.gods"))
		return;
	ref sld;
	switch(GetDataDay())
	{
		case 9:	
			sld = CharacterFromId("Atlaua");
			ChangeCharacterAddressGroup(sld, "Cave_Pashalka", "sit", "sit31");
			SetFunctionTimerCondition("EasterGodDissapear", 0, 0, 1, false);
		break;
		
		case 21:
			sld = CharacterFromId("Xiuhtecuhtli");
			ChangeCharacterAddressGroup(sld, "Cave_Pashalka", "sit", "sit1");
			SetFunctionTimerCondition("EasterGodDissapear", 0, 0, 1, false);
		break;
		
		case 25:
			sld = CharacterFromId("Huitzilopochtli");
			ChangeCharacterAddressGroup(sld, "Cave_Pashalka", "goto", "goto3");
			SetFunctionTimerCondition("EasterGodDissapear", 0, 0, 1, false);
		break;
		
		case 13:
			sld = CharacterFromId("Atlaua");
			ChangeCharacterAddressGroup(sld, "Cave_Pashalka", "sit", "sit31");
			sld = CharacterFromId("Xiuhtecuhtli");
			ChangeCharacterAddressGroup(sld, "Cave_Pashalka", "sit", "sit1");
			sld = CharacterFromId("Huitzilopochtli");
			ChangeCharacterAddressGroup(sld, "Cave_Pashalka", "goto", "goto3");
			SetFunctionTimerCondition("EasterGodDissapear", 0, 0, 1, false);
		break;
	}
}

void EasterGenerateXolotl()
{
	DeleteAttribute(pchar, "questTemp.easter");
	return;
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("Xolotl", "Xolotl", "skeleton", "man", 100, PIRATE, -1, false));
	sld.undead = "1";
	sld.name = FindPersonalName("Xolotl_name");	// проводник в подземное царство
	sld.lastname = "";
	LAi_group_MoveCharacter(sld, LAI_GROUP_ACTOR);
	LAi_SetImmortal(sld, true);
	sld.Dialog.Filename = "Quest\Easter.c";
	sld.dialog.currentnode = "Xolotl_1";
	
	EasterXolotlMove();
}

void EasterXolotlMove()
{
	DeleteAttribute(pchar, "questTemp.easter");
	return;
	// умный рандом
	int i;
	if(!CheckAttribute(pchar,"questTemp.easter.xolotl_shore"))
	{
		i = rand(2)+1;
	}
	else
	{
		switch(sti(strright(pchar.questTemp.easter.xolotl_shore, 1)))
		{
			case 1:		i = rand(1)+2;		break;
			case 2:		i = 2*rand(1)+1;	break;
			case 3:		i = rand(1)+1;		break;
		}
	}
	string sShore = "Shore_ship"+i;
	pchar.questTemp.easter.xolotl_shore = sShore;
	// в бухте разбитого корыта сандал с шёлком, в заливе гибели красное дерево с хлопком, на мысе несбывшихся надежд чёрное дерево с кожей
	switch(i)
	{
		case 1:		pchar.questTemp.easter.xolotl_lumber = GOOD_SANDAL;		pchar.questTemp.easter.xolotl_material = GOOD_SILK;		break;
		case 2:		pchar.questTemp.easter.xolotl_lumber = GOOD_MAHOGANY;	pchar.questTemp.easter.xolotl_material = GOOD_COTTON;	break;
		case 3:		pchar.questTemp.easter.xolotl_lumber = GOOD_EBONY;		pchar.questTemp.easter.xolotl_material = GOOD_LEATHER;	break;
	}
	
	SetFunctionTimerCondition("EasterXolotlMove", 0, 1, 0, true);
}

void EasterSummonXolotl()
{
	DeleteAttribute(pchar, "questTemp.easter");
	return;
	ref sld = CharacterFromId("Xolotl");
	if(Get_My_Cabin() == "My_Cabin" || Get_My_Cabin() == "My_CabineFDM" || Get_My_Cabin() == "My_Cabin_Huge" || Get_My_Cabin() == "My_Cabin_Quest")
	{
		int i = rand(3);
		switch(i)
		{
			case 0:			
				ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc1");
				LAi_SetGroundSitType(sld);
			break;
			case 1:			
				ChangeCharacterAddressGroup(sld, pchar.location, "rld", "aloc0");
				LAi_SetBarmanType(sld);
			break;
			case 2:			
				ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc1");
				LAi_SetOwnerType(sld);
			break;
			case 3:			
				ChangeCharacterAddressGroup(sld, pchar.location, "rld", "loc1");
				LAi_SetWaitressType(sld);
			break;
		}
	}
	else
	{
		ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit0");
		LAi_SetSitType(sld);
	}
	
	
	pchar.questTemp.easter.xolotl_incabin = 1;
}

void EasterDissapearXolotl()
{
	DeleteAttribute(pchar, "questTemp.easter");
	return;
	ref sld;
	sld = CharacterFromId("Xolotl");
	ChangeCharacterAddressGroup(sld, "none", "", "");
	DeleteAttribute(pchar,"questTemp.easter.xolotl_incabin");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason -----------------------------------мини-квесты монахов-------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Monkshipshine_Over(string qName)//действие освящения окончено
{
	DeleteAttribute(Pchar, "GenQuest.Shipshine");
	log_testinfo("Действие освящения истекло!");
}

void Monkletter_Over(string qName)//опоздали с депешей
{
	pchar.GenQuest.Monkletter.Late = "true";
	AddQuestRecord("Monkletter", "4");
	AddQuestUserData("Monkletter", "sSex", GetSexPhrase("ся","ась"));
	SetFunctionTimerCondition("Monkletter_Failed", 0, 1, 0, false);
}

void Monkletter_Failed(string qName)//квест с депешей просрочен
{
	RemoveItems(PChar, "letter_church", 1);
	AddQuestRecord("Monkletter", "5");
	AddQuestUserData("Monkletter", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Monkletter");
	ChangeCharacterReputation(pchar, -4);
	DeleteAttribute(pchar, "GenQuest.Monkletter");
}

void Churchbooks_Over(string qName)//опоздали с доставкой молитвенников
{
	pchar.GenQuest.Churchbooks.Late = "true";
	AddQuestRecord("Churchbooks", "5");
	AddQuestUserData("Churchbooks", "sSex", GetSexPhrase("ёз","езла"));
}

void Monkpassenger_Over(string qName)//опоздали с пассажиром
{
	pchar.quest.Monkpassenger.over = "yes";
	ref sld = characterFromId(pchar.GenQuest.Monkpassenger.id);
	string sTemp = sld.index+"Citizpassenger";
	if (IsEntity(&worldMap) || bSeaActive) 
	{
		pchar.quest.Monkpassenger_remove.win_condition.l1 = "Location_Type";
		pchar.quest.Monkpassenger_remove.win_condition.l1.location_type = "town";
		pchar.quest.Monkpassenger_remove.function = "Monkpassenger_remove";
	}
	else
	{
		RemovePassenger(Pchar, sld);
		Log_Info(StringFromKey("InfoMessages_38", XI_ConvertString("passengership"), GetFullName(sld)));
		AddQuestRecordEx(sTemp, "Citizpassenger", "2");
		CloseQuestHeader(sTemp);
		sld.lifeday = 0;
		DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
	}
}

void Monkpassenger_remove(string qName)//удаление пассажира
{
	ChangeCharacterReputation(pchar, -3);
	ref sld = characterFromId(pchar.GenQuest.Monkpassenger.id);
	string sTemp = sld.index+"Citizpassenger";
	RemovePassenger(Pchar, sld);
	Log_Info(StringFromKey("InfoMessages_38", XI_ConvertString("passengership"), GetFullName(sld)));
	AddQuestRecordEx(sTemp, "Citizpassenger", "2");
	CloseQuestHeader(sTemp);
	sld.lifeday = 0;
	DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
}

void Monkpassenger_complete(string qName)//доставили пассажира
{
	float locx, locy, locz;
	chrDisableReloadToLocation = true;//закрыть локацию
	ref sld = characterFromId(pchar.GenQuest.Monkpassenger.id);
	sld.Dialog.currentnode = "passenger_3";
	GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, pchar.GenQuest.Monkpassenger.City+"_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void ShipCapellan_Remove()//удаление капеллана
{
	ref sld = characterFromId(pchar.questTemp.ShipCapellan.id);
	sld.dialog.currentnode = "capellan_7";
	DeleteAttribute(Pchar, "questTemp.ShipCapellan.Yes");
	if (IsEntity(&worldMap) || bSeaActive) 
	{
		pchar.quest.ShipCapellan_remove.win_condition.l1 = "Location_Type";
		pchar.quest.ShipCapellan_remove.win_condition.l1.location_type = "town";
		pchar.quest.ShipCapellan_remove.function = "ShipCapellan_remove_1";
	}
	else
	{
		RemovePassenger(Pchar, sld);
		Log_Info(StringFromKey("InfoMessages_38", XI_ConvertString("capellan"), GetFullName(sld)));
		PlaySound("interface\notebook.wav");
		sld.lifeday = 0;
		DeleteAttribute(pchar, "questTemp.ShipCapellan"); //вместо .id сразу возможность брать нового
	}
	if (sld.location == Get_My_Cabin()) //HardCoffee чтобы ушёл при увольнении в каюте
	{
		if (CheckAttribute(loadedLocation, "locators.reload.reload1") && LAi_IsLocatorFree("reload", "reload1", 0.05))
		{
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 4.0);
		}
		else ChangeCharacterAddress(sld, "none", "");
	}
}

void ShipCapellan_remove_1(string qName)//удаление капеллана
{
	ref sld = characterFromId(pchar.questTemp.ShipCapellan.id);
	RemovePassenger(Pchar, sld);
	Log_Info(StringFromKey("InfoMessages_38", XI_ConvertString("capellan"), GetFullName(sld)));
	PlaySound("interface\notebook.wav");
	sld.lifeday = 0;
	DeleteAttribute(pchar, "questTemp.ShipCapellan"); //вместо .id сразу возможность брать нового
}
//<-- мини-квесты монахов

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason -----------------------------------мини-квесты дворян-------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Noblepassenger_Over(string qName)//опоздали с пассажиром
{
	pchar.quest.Noblepassenger.over = "yes";
	ref sld = characterFromId(pchar.GenQuest.Noblepassenger.id);
	string sTemp = sld.index+"Citizpassenger";
	if (IsEntity(&worldMap) || bSeaActive) 
	{
		pchar.quest.Noblepassenger_remove.win_condition.l1 = "Location_Type";
		pchar.quest.Noblepassenger_remove.win_condition.l1.location_type = "town";
		pchar.quest.Noblepassenger_remove.function = "Noblepassenger_remove";
	}
	else
	{
		RemovePassenger(Pchar, sld);
		Log_Info(StringFromKey("InfoMessages_38", XI_ConvertString("passengership"), GetFullName(sld)));
		AddQuestRecordEx(sTemp, "Citizpassenger", "2");
		CloseQuestHeader(sTemp);
		sld.lifeday = 0;
		DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
	}
}

void Noblepassenger_remove(string qName)//удаление пассажира
{
	ChangeCharacterReputation(pchar, -3);
	ref sld = characterFromId(pchar.GenQuest.Noblepassenger.id);
	string sTemp = sld.index+"Citizpassenger";
	RemovePassenger(Pchar, sld);
	Log_Info(StringFromKey("InfoMessages_38", XI_ConvertString("passengership"), GetFullName(sld)));
	AddQuestRecordEx(sTemp, "Citizpassenger", "2");
	CloseQuestHeader(sTemp);
	sld.lifeday = 0;
	DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
}

void Noblepassenger_complete(string qName)//доставили пассажира
{
	float locx, locy, locz;
	chrDisableReloadToLocation = true;//закрыть локацию
	ref sld = characterFromId(pchar.GenQuest.Noblepassenger.id);
	sld.Dialog.currentnode = "passenger_3";
	GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, pchar.GenQuest.Noblepassenger.City+"_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void Noblelombard_Over(string qName) //время вышло
{
	ref sld = characterFromId(pchar.GenQuest.Noblelombard.id);
	sld.lifeday = 0;
	sld = characterFromId(pchar.GenQuest.Noblelombard.City + "_usurer");
	RemoveLandQuestMark_Gen(sld, "Noblelombard");
	if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard")) AddQuestRecord("Noblelombard", "3");
	else AddQuestRecord("Noblelombard", "2");
	CloseQuestHeader("Noblelombard");
	DeleteAttribute(pchar, "questTemp.noblelombard");
	DeleteAttribute(pchar, "GenQuest.Noblelombard");
}

void Noblelombard_Regard(string qName)//можно идти за наградой
{
	pchar.GenQuest.Noblelombard.Giveregard = "true";
}
//<-- мини-квесты дворян

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason -----------------------------------мини-квесты горожан-------------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Townpassenger_Over(string qName)//опоздали с пассажиром
{
	pchar.quest.Townpassenger.over = "yes";
	ref sld = characterFromId(pchar.GenQuest.Townpassenger.id);
	string sTemp = sld.index+"Citizpassenger";
	if (IsEntity(&worldMap) || bSeaActive) 
	{
		pchar.quest.Townpassenger_remove.win_condition.l1 = "Location_Type";
		pchar.quest.Townpassenger_remove.win_condition.l1.location_type = "town";
		pchar.quest.Townpassenger_remove.function = "Townpassenger_remove";
	}
	else
	{
		RemovePassenger(Pchar, sld);
		Log_Info(StringFromKey("InfoMessages_38", XI_ConvertString("passengership"), GetFullName(sld)));
		AddQuestRecordEx(sTemp, "Citizpassenger", "2");
		CloseQuestHeader(sTemp);
		sld.lifeday = 0;
		DeleteAttribute(Pchar, "GenQuest.Townpassenger");
	}
}

void Townpassenger_remove(string qName)//удаление пассажира
{
	ChangeCharacterReputation(pchar, -3);
	ref sld = characterFromId(pchar.GenQuest.Townpassenger.id);
	string sTemp = sld.index+"Citizpassenger";
	RemovePassenger(Pchar, sld);
	Log_Info(StringFromKey("InfoMessages_38", XI_ConvertString("passengership"), GetFullName(sld)));
	AddQuestRecordEx(sTemp, "Citizpassenger", "2");
	CloseQuestHeader(sTemp);
	sld.lifeday = 0;
	DeleteAttribute(Pchar, "GenQuest.Townpassenger");
}

void Townpassenger_complete(string qName)//доставили пассажира
{
	float locx, locy, locz;
	chrDisableReloadToLocation = true;//закрыть локацию
	ref sld = characterFromId(pchar.GenQuest.Townpassenger.id);
	sld.Dialog.currentnode = "passenger_3";
	GetCharacterPos(pchar, &locx, &locy, &locz);
    ChangeCharacterAddressGroup(sld, pchar.GenQuest.Townpassenger.City+"_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
//<-- мини-квесты горожан

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// --> Jason -----------------------------мини-квесты темных личностей----------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Marginpassenger_Over(string qName)
{
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
}

void Marginpassenger_InWorld(string qName)//запускаем кораблик с пассажиром на карте
{
    string sGroup = "Sea_MarginCap1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 3*sti(pchar.rank)+10;
	int iDays = GetMaxDaysFromColony2Colony(pchar.GenQuest.Marginpassenger.Targetcity, pchar.GenQuest.Marginpassenger.City)+5;
	int iShipType = pchar.GenQuest.Marginpassenger.ShipType;
	string sTemp = pchar.GenQuest.Marginpassenger.ShipName;
	//TODO: балансировка
	ref sld = GetCharacter(NPC_GenerateCharacter("MarginCap", "citiz_41", "man", "man", iRank, sti(pchar.GenQuest.Marginpassenger.Nation), iDays, true));
	FantomMakeSmallSailor(sld, iShipType, sTemp, CANNON_TYPE_LBS_BY_SHIP, iScl+10, iScl, iScl, iScl, iScl);
	SetFantomParamFromRank(sld, iRank, true);
	SetCaptanModelByEncType(sld, "trade");
	sld.Ship.Mode = "trade";
	SetRandomNameToCharacter(sld);
	sld.Dialog.Filename = "Quest\Marginpassenger.c";
	sld.DeckDialogNode = "MarginCap";
	LAi_SetHP(sld, 170+iScl, 170+iScl);
	sld.AnalizeShips = true;
	TakeNItems(sld, "potion2", 3);
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipSpeedUp");
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")))+" '"+pchar.GenQuest.Marginpassenger.ShipName + "'";
	Group_AddCharacter(sGroup, "MarginCap");
	Group_SetGroupCommander(sGroup, "MarginCap");
	Map_CreateTrader(pchar.GenQuest.Marginpassenger.City, pchar.GenQuest.Marginpassenger.Targetcity, "MarginCap", iDays);

	SetFunctionTimerCondition("Marginpassenger_InWorldOver", 0, 0, iDays, false);
	pchar.quest.Marginpassenger_Sink.win_condition.l1 = "Character_sink";
	pchar.quest.Marginpassenger_Sink.win_condition.l1.character = "MarginCap";
	pchar.quest.Marginpassenger_Sink.function = "Marginpassenger_InWorldFail";//потопили
}

void Marginpassenger_InWorldOver(string qName)//упустили кораблик
{
	pchar.quest.Marginpassenger_Sink.over = "yes"; //снять прерывание
	AddQuestRecord("Marginpassenger", "2");
	AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
	CloseQuestHeader("Marginpassenger");
	Group_DeleteGroup("Sea_MarginCap1");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	AddCrewMorale(Pchar, -10);
	ChangeOfficersLoyality("bad_all", 1);
}

void Marginpassenger_InWorldFail(string qName)//потопили в бою
{
	pchar.quest.Marginpassenger_InWorldOver.over = "yes"; //снять прерывание
	Group_DeleteGroup("Sea_MarginCap1");
	AddQuestRecord("Marginpassenger", "3");
	AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
	CloseQuestHeader("Marginpassenger");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	AddCrewMorale(Pchar, -10);
	ChangeOfficersLoyality("bad_all", 1);
}

void Marginpassenger_CreateNeedman()//создаем выкупателя
{
	ref sld = GetCharacter(NPC_GenerateCharacter("MarginNeed", "citiz_"+(rand(9)+11), "man", "man", 10, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true));
	sld.Dialog.Filename = "Quest\Marginpassenger.c";
	sld.Dialog.currentnode = "MarginNeed";
	sld.name = pchar.GenQuest.Marginpassenger.q2Name;
	sld.lastname = "";
	LAi_SetImmortal(sld, true);
	RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
	LAi_SetCitizenType(sld);
	ChangeCharacterAddressGroup(sld, pchar.GenQuest.Marginpassenger.Targetcity+"_town", "quest", "quest2");
	LAi_SetLoginTime(sld, 12.0, 21.0);
}

void Marginpassenger_SouthshoreOver(string qName)//опоздали в бухту
{
	AddQuestRecord("Marginpassenger", "14");
	AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore+"Dat"));
	CloseQuestHeader("Marginpassenger");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	AddCrewMorale(Pchar, -5);
	ChangeOfficersLoyality("bad_all", 1);
}

void Marginpassenger_Southshore(string qName)//бой в бухте
{
	float locx, locy, locz;
	pchar.quest.Marginpassenger_SouthshoreOver.over = "yes"; //снять таймер
	chrDisableReloadToLocation = true;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	int iRank = sti(pchar.rank)+2;
	int iScl = 15 + 2*sti(pchar.rank);
	int n = 5+makeint(MOD_SKILL_ENEMY_RATE/2);
	//наши
	int i;
	ref sld;
	string sTemp;
    for (i=1; i<=7; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("MPCrew_"+i, "citiz_"+(rand(9)+31), "man", "man", iRank, sti(pchar.nation), 0, true));
		SetNPCModelUniq(sld, "sailor", MAN); //TODO: по патенту
		FantomMakeCoolFighter(sld, iRank, iScl, iScl,  "auto", "auto", iScl*2);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
		if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
        ChangeCharacterAddressGroup(sld, pchar.GenQuest.Marginpassenger.Shore, "goto", sTemp);
    }
	//враги
	for (i=1; i <=n; i++)
	{
		if (i == 1)
		{
			sld = GetCharacter(NPC_GenerateCharacter("MPEnemy_"+i, "spa_mush_"+(rand(3)+5), "man", "mushketer", iRank+3, SPAIN, 0, false));
			FantomMakeCoolFighter(sld, iRank+3, iScl+2, iScl+2, "", "mushket_flint", iScl*2);
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("MPEnemy_"+i, "sold_spa_"+(rand(7)+9), "man", "man", iRank+3, SPAIN, 0, true));
			FantomMakeCoolFighter(sld, iRank+3, iScl+2, iScl+2, "auto", "auto", iScl*2);
		}
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		ChangeCharacterAddressGroup(sld, pchar.GenQuest.Marginpassenger.Shore, "reload", "reload1");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
	}
	sld = GetCharacter(NPC_GenerateCharacter("Spa_shore_off", "off_spa_"+(rand(1)+5), "man", "man", iRank+5, SPAIN, -1, true));
	FantomMakeCoolFighter(sld, iRank+5, iScl+5, iScl+5,  "auto", "pistol5", iScl*3);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	ChangeCharacterAddressGroup(sld, pchar.GenQuest.Marginpassenger.Shore, "reload", "reload1");
	LAi_SetWarriorType(sld);
	LAi_group_MoveCharacter(sld, "EnemyFight");
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "Marginpassenger_Afterbattle");
}

void Marginpassenger_SouthshipInWorld(string qName) //запускаем кораблик с деревом на карте
{
    string sGroup = "Sea_SouthshipCap1";
	Group_DeleteGroup(sGroup);
	Group_FindOrCreateGroup(sGroup);
	int iRank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE;
	int iScl = 3*sti(pchar.rank)+10;
	int iDays = GetMaxDaysFromColony2Colony(pchar.GenQuest.Marginpassenger.Southcity1, pchar.GenQuest.Marginpassenger.Southcity)+5;
	string sTemp = pchar.GenQuest.Marginpassenger.ShipName1;
	ref sld = GetCharacter(NPC_GenerateCharacter("SouthshipCap", "citiz_41"+(rand(9)), "man", "man", iRank, SPAIN, iDays, true));
	FantomMakeSmallSailor(sld, SHIP_BARKENTINE, sTemp, CANNON_TYPE_CANNON_LBS12, iScl+10, iScl, iScl, iScl, iScl); //TODO: баланс
	FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade15", "pistol5", 100); //TODO: баланс снаряжения
	SetCaptanModelByEncType(sld, "trade");
	sld.Ship.Mode = "trade";
	SetRandomNameToCharacter(sld);
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	sld.DontRansackCaptain = true;
	sld.AnalizeShips = true;
	sld.AlwaysEnemy = true;
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "AdvancedBattleState");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "ShipSpeedUp");
	AddCharacterGoods(sld, sti(pchar.GenQuest.Marginpassenger.Goods), sti(pchar.GenQuest.Marginpassenger.GoodsQty));//положить в трюм древесину
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = LowerFirst(XI_ConvertString("Barkentine")) + " '"+pchar.GenQuest.Marginpassenger.ShipName1 + "'";
	Group_AddCharacter(sGroup, "SouthshipCap");
	Group_SetGroupCommander(sGroup, "SouthshipCap");
	Map_CreateTrader(pchar.GenQuest.Marginpassenger.Southcity, pchar.GenQuest.Marginpassenger.Southcity1, "SouthshipCap", iDays);
	SetFunctionTimerCondition("Marginpassenger_SouthshipInWorldOver", 0, 0, iDays, false);
	pchar.quest.Marginpassenger_Sink1.win_condition.l1 = "Character_sink";
	pchar.quest.Marginpassenger_Sink1.win_condition.l1.character = "SouthshipCap";
	pchar.quest.Marginpassenger_Sink1.function = "Marginpassenger_SouthshipFail";//потопили
	pchar.quest.Marginpassenger_Abordage1.win_condition.l1 = "Character_Capture";
	pchar.quest.Marginpassenger_Abordage1.win_condition.l1.character = "SouthshipCap";
	pchar.quest.Marginpassenger_Abordage1.function = "Marginpassenger_SouthshipWin";//взяли на абордаж
}

void Marginpassenger_SouthshipInWorldOver(string qName)//упустили кораблик
{
	pchar.quest.Marginpassenger_Sink1.over = "yes"; //снять прерывание
	pchar.quest.Marginpassenger_Abordage1.over = "yes"; //снять прерывание
	AddQuestRecord("Marginpassenger", "17");
	AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
	CloseQuestHeader("Marginpassenger");
	Group_DeleteGroup("Sea_SouthshipCap1");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	AddCrewMorale(Pchar, -10);
	ChangeOfficersLoyality("bad_all", 1);
}

void Marginpassenger_SouthshipFail(string qName)//потопили в бою
{
	pchar.quest.Marginpassenger_SouthshipInWorldOver.over = "yes"; //снять прерывание
	pchar.quest.Marginpassenger_Abordage1.over = "yes"; //снять прерывание
	Group_DeleteGroup("Sea_SouthshipCap1");
	AddQuestRecord("Marginpassenger", "18");
	AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase("","а"));
	AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
	CloseQuestHeader("Marginpassenger");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	AddComplexSeaExpToScill(50, 50, 50, 0, 50, 50, 0);
}

void Marginpassenger_SouthshipWin(string qName)//абордировали
{
	pchar.quest.Marginpassenger_SouthshipInWorldOver.over = "yes"; //снять прерывание
	pchar.quest.Marginpassenger_Sink1.over = "yes"; //снять прерывание
	Group_DeleteGroup("Sea_SouthshipCap1");
	AddQuestRecord("Marginpassenger", "19");
	AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
	CloseQuestHeader("Marginpassenger");
	DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
	AddComplexSeaExpToScill(100, 100, 100, 150, 100, 100, 0);
	AddComplexSelfExpToScill(50, 50, 50, 50);
	AddCrewMorale(Pchar, 10);
	ChangeOfficersLoyality("good_all", 1);
	ChangeCharacterNationReputation(pchar, SPAIN, -1);
}
//<-- мини-квесты темных личностей

void CameraSleep() //Камера уходит в сон
{
	locCameraSleep(true);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ------------------------------------ "Найти двуствольный мушкет" ----------------------------------------
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SeekDoubleMushket_Capture(string qName)
{
    if (CheckCharacterItem(pchar, "mushket2x2"))
    {
        AddLandQuestmark_Main(CharacterFromID("Douglas"), "SeekDoubleMushket");
        AddMapQuestMark_Major("PortSpein_town", "SeekDoubleMushket", "");
    }

    TEV.SeekDoubleMushket_MushketCapCapture = true;
}

void SeekDoubleMushket_GroupDeath(string qName)
{
    if (CheckAttribute(pchar, "questTemp.mushket2x2_stid"))
    {
        DeleteAttribute(pchar, "questTemp.mushket2x2_stid");
        RemoveLandQuestMark_Main(CharacterFromID("PortoBello_Tavernkeeper"), "SeekDoubleMushket");
    }

    if (CheckAttribute(&TEV, "SeekDoubleMushket_MushketCapCapture"))
    {
        DeleteAttribute(&TEV, "SeekDoubleMushket_MushketCapCapture");
        return;
    }

    AddQuestRecord("SeekDoubleMushket", "10");
    CloseQuestHeader("SeekDoubleMushket");
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////
// <-- End ------------------------------- "Найти двуствольный мушкет" ----------------------------------------
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void RepairMonsterGroup(string qName)
{
	LAi_group_SetRelation(LAI_GROUP_MONSTERS, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_SetLookRadius(LAI_GROUP_MONSTERS, LAI_GROUP_MNS_LOOK);
	LAi_group_SetHearRadius(LAI_GROUP_MONSTERS, LAI_GROUP_MNS_HEAR);
	LAi_group_SetSayRadius(LAI_GROUP_MONSTERS, LAI_GROUP_MNS_SAY);
	LAi_group_SetPriority(LAI_GROUP_PLAYER, 0);
}

//HardCoffee заставить нпс наблюдать за гг
void TurnNPCToPcharInit(ref rChr)
{
	LAi_SetStayTypeNoGroup(rChr);
    TEV.TurnNPCToPchar.id = rChr.id;
    TEV.TurnNPCToPchar.location = rChr.location;
	Lai_MethodDelay("TurnNPCToPcharProcess", 0.75);
}

void TurnNpcToPcharProcess()
{
	if (!CheckAttribute(&TEV, "TurnNPCToPchar")) return;
    ref rChr = CharacterFromID(TEV.TurnNPCToPchar.id);
    if (rChr.id == Nullcharacter.id ||
     rChr.chr_ai.type != LAI_TYPE_STAY ||
     rChr.location != pchar.location ||
     rChr.location != TEV.TurnNPCToPchar.location)
	{
	    DeleteAttribute(&TEV, "TurnNPCToPchar");
	    return;
	}
    if (!DialogRun) CharacterTurnByChr(rChr, Pchar);
	Lai_MethodDelay("TurnNPCToPcharProcess", 0.75 + frandsmall(1.0));
}
//<--
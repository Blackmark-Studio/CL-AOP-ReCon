
void FranceLineQuestComplete(string sQuestName, string qname)
{
	return; //TODO
	ref chr, chr2, loc, ship;
	aref arTmp, arTo, arFrom;
	int i, iChar, n, iTemp;
	string sStr, sGroup, model, locator;

	object obj[20];

	bool bOk;

	float x, y, z, fTemp;

	int gray = argb(255, 129, 129, 129);
	int yellow = argb(255, 255, 240, 0);

	switch (sQuestName)
	{
		//====================================================================================================================
		//	Начало сюжета
		//====================================================================================================================
		case "FL1_s1":
			DeleteAttribute(Pchar, "ship");
			DeleteAttribute(Pchar, "ShipSails.gerald_name");
			Pchar.ship.type = SHIP_NOTUSED;
			GiveItem2Character(pchar, "blade23");
			TakeNItems(pchar, "potion1", 3);
			EquipCharacterByItem(pchar, "blade23");
			SetQuestsCharacters(); //Выставляем Траста; TODO: мб поставить его в другой момент, чтобы согласовалось с сюжетом
			DoQuestCheckDelay("FL1_s2", 0.1);
		break;

		case "FL1_s2":
			locCameraToPos(-130, 25, -10, 0);
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("FL1_s2_1", 2.5);
		break;

		case "FL1_s2_1":
			DoQuestCheckDelay("FL1_s2_2", 0.25);
			LAi_Fade("FL1_s2_3", "");
		break;

		case "FL1_s2_2":
			chr = GetCharacter(NPC_GenerateCharacter("FL_officer", "off_fra_6", "man", "man", 1, FRANCE, -1, false));
			SetFantomParamFromRank(chr, 2, true);
			chr.name = FindPersonalName("FL_officer_name");
			chr.lastname = FindPersonalName("FL_officer_lastname");
			chr.dialog.filename = "Quest\FranceLine\MarkLevua.c";
			chr.greeting = "Bonjour_mesie";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto4");
			LAi_SetActorType(chr);
			LAi_ActorGoToLocator(chr, "goto", "goto12", "", -1);
		break;

		case "FL1_s2_3":
			locCameraFromToPos(-11, 18.70, -29.30, true, -13.00, 7.00, 0.00);
			DoQuestCheckDelay("FL1_s2_4", 2.5);
		break;

		case "FL1_s2_4":
			LAi_Fade("FL1_s3", "");
		break;

		case "FL1_s3":
			locCameraToPos(5, 10, 5, 1);
			chr = CharacterFromID("FL_officer");
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto7");
			LAi_SetActorType(chr);
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL1_s4", -1, 0);
		break;

		case "FL1_s4":
			chr = GetCharacter(NPC_GenerateCharacter("GrammonMother", "lady_3", "woman", "towngirl", 1, FRANCE, -1, false));
			chr.name = FindPersonalName("GrammonMother_name");
			chr.lastname = FindPersonalName("GrammonMother_lastname");
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload6");
			LAi_SetActorType(chr);
			LAi_ActorFollow(chr, CharacterFromID("FL_officer"), "FL1_s5", -1);

			DoQuestCheckDelay("FL1_s4_1", 1.3);
		break;

		case "FL1_s4_1":
			chr = GetCharacter(NPC_GenerateCharacter("GrammonSister", "girl_6", "woman", "towngirl", 1, FRANCE, -1, false));
			chr.name = FindPersonalName("GrammonSister_name");
			chr.lastname = FindPersonalName("GrammonSister_lastname");
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload6");
			LAi_SetActorType(chr);
			LAi_ActorFollow(chr, CharacterFromID("GrammonMother"), "", -1);
		break;

		case "FL1_s5":
			chr = CharacterFromID("GrammonMother");
			chr2 = CharacterFromID("FL_officer");
			LAi_ActorWaitDialog(chr2, chr);
			LAi_ActorDialog(chr, chr2, "", -1, 0);

			pchar.name = FindPersonalName("OfficerMother_name");
			pchar.lastname = FindPersonalName("OfficerMother_lastname");
			pchar.dialog.currentnode = "FL1";
			LAi_ActorSelfDialog(pchar, "FL1_s6");
		break;

		case "FL1_s6":
			pchar.camera = "";
			locCameraFollow();
			EndQuestMovie();

			pchar.name = FindPersonalName("GrammonPchar_name");
			pchar.lastname = FindPersonalName("GrammonPchar_lastname");
			chr = CharacterFromID("FL_officer");
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL1_s7", -1, 0);
		break;

		case "FL1_s7":
			LAi_SetPlayerType(pchar);
			AddDataToCurrent(0, 0, 1);
			SetCurrentTime(21, 12);
			MakeAutoSave();
			DoQuestCheckDelay("FL1_s8", 0.5);
		break;

		case "FL1_s8":
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_26", NewStr()), "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("GrammonEstateExitTown", "rld", "loc4", "FL1_s9");
			LaunchFrameForm();
		break;

		case "FL1_s9":
			chr = CharacterFromID("FL_officer");
			ChangeCharacterAddressGroup(chr, pchar.location, "rld", "loc13");
			LAi_SetActorType(chr);
			LAi_ActorDialogNow(chr, pchar, "FL1_s10", 0);
		break;

		case "FL1_s10":
			chr = CharacterFromID("FL_officer");
			LAi_SetWarriorTypeNoGroup(chr);
			LAi_group_MoveCharacter(chr, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);

			LAi_SetCheckMinHP(chr, 5.0, true, "FL1_s11");
		break;

		case "FL1_s11":
			LAi_SetActorType(pchar);
			LAi_SetGroundSitType(CharacterFromID("FL_officer"));
			LAi_Fade("", "FL1_s12");
		break;

		case "FL1_s12":
			PlaySound("Voice\" + VoiceGetLanguage() + "\FranceLine\vsearestovan.wav");

			StartQuestMovie(false, false, true);

			for (i = 0; i < 3; i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("army_sold", FRANCE, MAN, 0));
				chr.id = "tmp_soldier" + i;
				ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1");
				LAi_SetActorType(chr);
				if (i == 0) LAi_ActorFollow(chr, CharacterFromID("FL_officer"), "FL1_s13", -1);
				else LAi_ActorFollow(chr, CharacterFromID("tmp_soldier0"), "", -1);
			}
		break;

		case "FL1_s13":
			LAi_ActorDialog(CharacterFromID("tmp_soldier0"), CharacterFromID("FL_officer"), "", -1, 0);
			pchar.name = FindPersonalName("tmp_soldier0_name");
			pchar.lastname = FindPersonalName("tmp_soldier0_lastname");
			pchar.dialog.currentnode = "FL2";
			LAi_ActorSelfDialog(pchar, "FL1_s14");
			EndQuestMovie();
		break;

		case "FL1_s14":
			pchar.name = FindPersonalName("GrammonPchar_name");
			pchar.lastname = FindPersonalName("GrammonPchar_lastname");
			locations[FindLocation("Prison")].parent_colony = "FortFrance";
			SetLifeDay(CharacterFromID("FL_officer"), 0);
			LAi_SetPlayerType(pchar);
			DelEqiup(pchar, false, false);
			DoQuestReloadToLocation("Prison", "goto", "goto9", "FL1_s15");
		break;

		case "FL1_s15":
			DoQuestCheckDelay("FL1_s16", 1.0);
		break;

		case "FL1_s16":
			LAi_SetCurHPMax(pchar);
			AddDataToCurrent(0, 0, 1);
			SetCurrentTime(9, 34);
			RefreshLandTime();
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_27"), "FL1_s17", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL1_s17":
			chr = GetCharacter(NPC_GenerateCharacter("DorianFurnier", "huber_spa", "man", "man", 20, FRANCE, 0, true));
			chr.name = FindPersonalName("DorianFurnier_name");
			chr.lastname = FindPersonalName("DorianFurnier_lastname");
			chr.dialog.filename = "Quest\FranceLine\DorianFurnier.c";
			chr.greeting = "nenujniproblem";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto22");
			LAi_SetActorType(chr);
			LAi_ActorGoToLocator(chr, "reload", "reload12", "FL1_s18", -1);
		break;

		case "FL1_s18":
			LAi_ActorDialogNow(CharacterFromID("DorianFurnier"), pchar, "FL1_s19", -1);
		break;

		case "FL1_s19":
			SetCurrentTime(11, 12);
			DoQuestReloadToLocation("Ship_deck", "goto", "goto5", "FL1_s20");
		break;

		case "FL1_s20":
			chr = GetCharacter(NPC_GenerateCharacter("JozephFushe", "Fushe", "man", "man", 5, FRANCE, -1, true));
			chr.name = FindPersonalName("JozephFushe_name");
			chr.lastname = FindPersonalName("JozephFushe_lastname");
			chr.dialog.filename = "Quest\FranceLine\JozefFushe.c";
			chr.greeting = "";
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL1_s21", -1, 0);

			for (i = 0; i < 6; i++)
			{
				chr = GetOurSailor("tmp_sailor" + i);
				LAi_CharacterDisableDialog(chr);
				PlaceCharacter(chr, "goto", "random");
				LAi_SetCitizenType(chr);
			}
		break;

		case "FL1_s21":
		//GiveItem2Character(pchar, "clothes32");
			GiveItem2Character(pchar, "blade2");
			EquipCharacterByItem(pchar, "blade2"); // надо поменять будет на что уникальное konstrush

			PostVideoAndQuest("France\01", 100, "FL1_s22");

			InterfaceStates.Buttons.Save.enable = true;
		break;

		case "FL1_s22":
			MakeAutoSave();
			DoQuestCheckDelay("FL1_s23", 0.5);
		break;

		case "FL1_s23":
			AddDataToCurrent(0, 1, 10);
			SetCurrentTime(13, 05);
			RefreshLandTime();

			SetLaunchFrameFormParam(StringFromKey("InfoMessages_28", NewStr(), NewStr()), "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("BOARDING_DECK", "rld", "loc0", "FL1_s24");
			LaunchFrameForm();
		break;

		case "FL1_s24":
			PlaySound("Voice\" + VoiceGetLanguage() + "\FranceLine\Ispantsi.wav");
			// наши
			for (i = 0; i < 10; i++)
			{
				chr = GetOurSailor("tmp_sold" + i);
				SetFantomParamFromRank(chr, 5, true);
				PlaceCharacter(chr, "rld", "random");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_warrior_DialogEnable(chr, false);
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
			}

			// Враги
			for (i = 0; i < 10; i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("navy_sold", SPAIN, MAN, 0)); //нужно заменить на морпехов Konstrush
				SetFantomParamFromRank(chr, 3, true);
				PlaceCharacter(chr, "rld", "random");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "EnemyFight");
			}

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "FL1_s25");
		break;

		case "FL1_s25":
			Delay_DeleteGroup("EnemyFight");
//			LaunchInfoMessage(1);
			chr = CharacterFromID("JozephFushe");
			chr.greeting = "fushe";
			ChangeCharacterAddressGroup(chr, pchar.location, "rld", "alocmush2");
			LAi_SetWarriorType(chr);
			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
		break;

		case "FL1_s26":
			LAi_SetCurHPMax(pchar);
			AddDataToCurrent(0, 0, 7);
			SetCurrentTime(8, 15);
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_29", NewStr(), NewStr()), "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_town", "reload", "reload1", "FL1_s27");
			LaunchFrameForm();
		break;

		case "FL1_s27":
			InterfaceStates.Buttons.Save.enable = true;

			chr = CharacterFromID("JozephFushe");
			chr.greeting = "fushe";
			chr.dialog.currentnode = "First_man";
			ChangeCharacterAddressGroup(chr, pchar.location, "quest", "quest1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL1_s28", -1, 0);
		break;

		case "FL1_s28":
			chr = CharacterFromID("JozephFushe");
			LAi_ActorRunToLocation(chr, "reload", "reload4_back", "none", "", "", "", 10.0);

			pchar.MainQuest = "FL1_s28";

			DoQuestCheckDelay("FL1_s29", 1.0);
			SetQuestHeader("FL1");
			AddQuestRecord("FL1", "1");
		break;

		case "FL1_s29":
			ChangePIRATES();
		break;

		case "FL1_s30":
			pchar.quest.FL1s30.win_condition.l1 = "location";
			pchar.quest.FL1s30.win_condition.l1.location = "FortFrance_tavern";
			pchar.quest.FL1s30.win_condition = "FL1_s31";
		break;

		case "FL1_s31":
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto2");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "", -1, 0);
		break;

		case "FL1_s31_end":
			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL1_s32_failed")
			{
				pchar.MainQuest = "FL1_s32_failed";
			}
			else
			{
				pchar.MainQuest = "";
			}
			SetLifeDay(CharacterFromID("JozephFushe"), 0);
			ChangeCharacterNationReputation(pchar, FRANCE, -5);

			AddQuestRecord("FL1", "2");
			SetQuestHeaderColor("FL1", gray);
			CloseQuestHeader("FL1");
		break;

		case "FL1_s32":
			pchar.MainQuest = "FL1_s32";
			AddMoneyToCharacter(pchar, 10000);

			OfficersReaction("good");
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, FRANCE, 3);

			AddQuestRecord("FL1", "3");
//			LaunchInfoMessage(0);

			SetTimerConditionParamEx("FL1s32failed", "FL1_s32_failed", 0, 0, 1);

			pchar.quest.FL1s32.win_condition.l1 = "location";
			pchar.quest.FL1s32.win_condition.l1.location = "FortFrance_Dungeon";
			pchar.quest.FL1s32.win_condition = "FL1_s33";
			LAi_LocationDisableMonGenTimer("FortFrance_Dungeon", 1); //заблочить скелетов 1 день konstrush
		break;

		//---------------------------------------------------------------------------------------------
		// Провал, опоздали в подземелье, Торговец больше никогда не заговорит?..
		// чтобы опять заговорил, надо снять pchar.MainQuest = "FL1_s32_failed"
		case "FL1_s32_failed":
			DeleteQuestCheck("FL1s32");
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -15);
			ChangeCharacterNationReputation(pchar, FRANCE, -13);

			pchar.MainQuest = "FL1_s32_failed";
			AddQuestRecord("FL1", "4");

			pchar.quest.FL1s30v2.win_condition.l1 = "location";
			pchar.quest.FL1s30v2.win_condition.l1.location = "FortFrance_tavern";
			pchar.quest.FL1s30v2.win_condition = "FL1_s31";
		break;

		//---------------------------------------------------------------------------------------------
		// Продолжаем играть
		case "FL1_s33":
			DeleteQuestCheck("FL1s32failed");
			chrDisableReloadTolocation = true;

			pchar.MainQuest = "FL1_s33";
			chr = GetCharacter(NPC_GenerateCharacter("FL_Mary", "Marie", "woman", "towngirl", 1, FRANCE, -1, false)); // нужна другая модель не Изабелла konstrush
			chr.name = FindPersonalName("FL_Mary_name");
			chr.lastname = characters[GetCharacterIndex("FortFrance_trader")].lastname;
			chr.dialog.filename = "Quest\FranceLine\Mary.c";
			chr.greeting = "Isabella";
			SetCharacterPerk(chr, "SweetBaby");
			SetCharacterPerk(chr, "Honest");
			LAi_CharacterDisableDialog(chr);
			LAi_SetStayType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "monsters", "monster37");

			chr = GetCharacter(NPC_GenerateCharacter("FL_Petit", "officer_7", "man", "man", 1, PIRATE, 0, false));
			SetFantomParamFromRank(chr, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, true);
			chr.name = FindPersonalName("FL_Petit_name");
			chr.lastname = FindPersonalName("FL_Petit_lastname");
			chr.dialog.filename = "Quest\FranceLine\JanPetit.c";
			chr.greeting = "Enc_Raiders";
			ChangeCharacterAddressGroup(chr, pchar.location, "monsters", "monster9");
			LAi_SetWarriorType(chr);
			LAi_warrior_SetStay(chr, true);
			LAi_group_MoveCharacter(chr, "FL1_s33_group");

			for (i = 35; i < 37; i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 0));
				SetFantomParamFromRank(chr, sti(pchar.rank), true);
				chr.id = "FL_Petit" + i;
				ChangeCharacterAddressGroup(chr, pchar.location, "monsters", "monster" + i);
				LAi_SetWarriorType(chr);
				LAi_warrior_SetStay(chr, true);
				LAi_warrior_DialogEnable(chr, false);
				LAi_group_MoveCharacter(chr, "FL1_s33_group");
			}

			LAi_group_SetCheck("FL1_s33_group", "FL1_s34");
			pchar.MainQuest = "FL1_s33";
		break;

		case "FL1_s34_fight":
			LAi_SetPlayerType(pchar);

			chr = CharacterFromID("FL_Petit");
			LAi_SetWarriorType(chr);
			LAi_group_MoveCharacter(chr, "FL1_s33_group");
			LAi_group_FightGroups("FL1_s33_group", LAI_GROUP_PLAYER, true);
		break;

		// убийство группы
		case "FL1_s34":
			Delay_DeleteGroup("FL1_s33_group");

			chr = CharacterFromID("FL_Mary");
			LAi_CharacterEnableDialog(chr);
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL1_s37", -1, 0);
		break;

		// вызывается по входу в локатор detector1 нужно добавить нам в локацию konstrush
		case "FL1_s35":
			pchar.MainQuest = "";
			chr = CharacterFromID("FL_Petit");
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, chr, "", 0);
		break;

		// пошли мирным путем и отдали деньги
		case "FL1_s36":
			LAi_SetPlayerType(pchar);

			LAi_group_RemoveCheck("FL1_s33_group");

			chr = CharacterFromID("FL_Mary");
			LAi_CharacterEnableDialog(chr);
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL1_s37", -1, 0);
		break;

		case "FL1_s37":
			pchar.MainQuest = "FL1_s37";
			chrDisableReloadTolocation = false;
			LAi_ActorFollowEverywhere(CharacterFromID("FL_Mary"), "", -1);
		break;

		case "FL1_s38":
			aref itm;
			// Генерим карту клада
			TEV.MapTreasureNoScam = true; // без подделки
			Items_FindItem("map_full", &itm);
			FillMapForTreasure(itm);

			itm.MapIslId = "Caiman";
			itm.MapLocId = GetLocationForTreasure(itm.MapIslId);
			itm.MapBoxId = GetBoxForTreasure(itm.MapIslId, itm.MapLocId);

			DeleteAttribute(itm, "BoxTreasure");
			itm.BoxTreasure.blade6 = 1; // дворянка, раньше был Плавник пираньи
			itm.BoxTreasure.spyglass2 = 1;
			itm.BoxTreasure.map_cayman = 1;
			itm.BoxTreasure.map_part1 = 1;
			itm.BoxTreasure.indian13 = 3;
			itm.BoxTreasure.pistol1 = 1;
			itm.BoxTreasure.bullet = 20;
			itm.BoxTreasure.GunPowder = 20;

			GiveItem2Character(pchar, "map_full");

			Pchar.quest.SetTreasureFromMap.win_condition.l1 = "location";
			Pchar.quest.SetTreasureFromMap.win_condition.l1.location = itm.MapLocId;
			Pchar.quest.SetTreasureFromMap.win_condition = "SetTreasureFromMap";
			// <- карта

			AddCharacterExpToSkill(pchar, "Commerce", 100.0);

			AddQuestRecord("FL1", "5");
			pchar.MainQuest = "";

			chr = CharacterFromID("FL_Mary");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL1_s39", 1.0, 0);
		break;

		case "FL1_s39":
			chr = CharacterFromID("FL_Mary");
			chr.location = pchar.location;
			chr.location.locator = "goto1";
			chr.location.group = "goto";
			LAi_SetCitizenType(chr);

			AddQuestRecord("FL1", "6");

			// идем к Фуше
			pchar.quest.FL1s39.win_condition.l1 = "location";
			pchar.quest.FL1s39.win_condition.l1.location = "FortFrance_tavern";
			pchar.quest.FL1s39.win_condition = "FL1_s31";
		break;

		case "FL1_s40":
			chrDisableReloadTolocation = true;
			LAi_ActorGoToLocation(CharacterFromID("JozephFushe"), "reload", "reload1_back", "none", "", "", "FL1_s41", -1);
			AddQuestRecord("FL1", "7");
		break;

		case "FL1_s41":
			chrDisableReloadTolocation = false;

			pchar.quest.FL1s41.win_condition.l1 = "location";
			pchar.quest.FL1s41.win_condition.l1.location = "FortFrance_PortOffice";
			pchar.quest.FL1s41.win_condition = "FL1_s42";
		break;

		case "FL1_s42":
			chrDisableReloadTolocation = true;
			pchar.MainQuest = "FL1_s42";

			chr = GetCharacter(NPC_GenerateCharacter("FL_Pablo", "officer_27", "man", "man", sti(pchar.rank), PIRATE, -1, false));
			SetFantomParamFromRank(chr, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, true);
			chr.name = FindPersonalName("FL_Pablo_name");
			chr.lastname = FindPersonalName("FL_Pablo_lastname");
			chr.dialog.filename = "Quest\FranceLine\Pablo.c";
			chr.greeting = "pogovorit_nado"; // поговорить надо пабло
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto1");
			LAi_SetActorType(chr);

			// для антуражу
			for (i = 0; i < 2; i++)
			{
				chr = GetOurSailor("FL_tmp_cap" + i); //TODO: другие модельки, а не голубых матросов
				LAi_CharacterDisableDialog(chr);
				PlaceCharacter(chr, "goto", "random");
				LAi_SetStayType(chr);
			}
		break;

		case "FL1_s43":
			pchar.MainQuest = "";
			chr = CharacterFromID("FL_Pablo");
			LAi_ActorDialog(chr, pchar, "FL1_s44", -1, 0);
		break;

		case "FL1_s44":
			LAi_ActorGoToLocation(CharacterFromID("FL_Pablo"), "reload", "reload1", "FortFrance_town", "goto", "goto26", "FL1_s45", -1);
			ChangeCharacterAddressGroup(CharacterFromID("JozephFushe"), "FortFrance_town", "reload", "reload1_back");
		break;

		case "FL1_s45":
			SetCurrentTime(22, 14);
			chrDisableReloadTolocation = false;
			bDisableFastReload = true;
			pchar.quest.FL1s45.win_condition.l1 = "locator";
			pchar.quest.FL1s45.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FL1s45.win_condition.l1.locator_group = "quest";
			pchar.quest.FL1s45.win_condition.l1.locator = "quest1";
			pchar.quest.FL1s45.win_condition = "FL1_s46";

			pchar.quest.FL1s45a.win_condition.l1 = "location";
			pchar.quest.FL1s45a.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FL1s45a.win_condition = "FL1_s46a";
		break;

		case "FL1_s46a":
			chrDisableReloadTolocation = true;
		break;

		case "FL1_s46":
			StartQuestMovie(false, false, true);

			LAi_ActorDialog(CharacterFromID("FL_Pablo"), CharacterFromID("JozephFushe"), "", -1, 0);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto26", "FL1_s47", -1);

			locCameraToPos(-5, 5, 67, 0);
		break;

		case "FL1_s47":
			ref sld = CharacterFromID("JozephFushe");
			LAi_ActorTurnToCharacter(pchar, sld);
			//LAi_ActorTurnToLocator(sld, "reload", "reload1"); //если надо на локатор повернуть персонажа
			pchar.name = FindPersonalName("JozephFusheFL3_1_name");
			pchar.lastname = FindPersonalName("JozephFusheFL3_1_lastname");
			pchar.dialog.currentnode = "FL3_1";
			LAi_ActorSelfDialog(pchar, "FL1_s48");
		break;

		case "FL1_s48":
			pchar.name = FindPersonalName("GrammonPchar_name");
			pchar.lastname = FindPersonalName("GrammonPchar_lastname");
			chr = CharacterFromID("FL_Pablo");
			LAi_SetActorType(chr);
			LAi_ActorRunToLocation(chr, "reload", "houseH1", "none", "", "", "", 5.0);
			chr = CharacterFromID("JozephFushe");
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL1_s49", -1, 0);
		break;

		case "FL1_s49":
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			LAi_ActorRunToLocation(CharacterFromID("JozephFushe"), "reload", "reload3_back", "none", "", "", "", 16.0);
			AddQuestRecord("FL1", "7_1");

			bDisableFastReload = false;
			chrDisableReloadTolocation = false;
			Pchar.quest.FL1_s49b.win_condition.l1 = "location";
			Pchar.quest.FL1_s49b.win_condition.l1.location = "FortFrance_tavern_upstairs";
			PChar.quest.FL1_s49b.win_condition = "FL1_s49b";
			pchar.MainQuest = "FL1_s50";
		break;

		case "FL1_s49b":
			chrDisableReloadToLocation = true;
			DoQuestCheckDelay("TalkSelf_Quest", 4.0);
		break;

		case "FL1_s49c":
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_30"), "FL1_s50", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 10, 20); //крутим время
			RecalculateJumpTable();
		break;

		case "FL1_s50":
			chr = CharacterFromID("FL_Pablo");
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL1_s51", -1, 0);
		break;

		case "FL1_s51":
			if (pchar.location == "FortFrance_tavern") LAi_locationFightDisable(&locations[Findlocation(pchar.location)], false);
			chr = CharacterFromID("FL_Pablo");
			GiveItem2Character(chr, "FQ_letter1");
			chr.SaveItemsForDead = true; //сохраняем все вещи на трупе Пабло
			LAi_SetWarriorTypeNoGroup(chr);
			LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("FL_EnemyFight", "FL1_s52");
		break;

		case "FL1_s52":
			if (pchar.location == "FortFrance_tavern") LAi_locationFightDisable(&locations[Findlocation(pchar.location)], true);
			Delay_DeleteGroup("FL_EnemyFight");
		break;

		case "FL1_s53":
			chrDisableReloadTolocation = false;
			AddQuestRecord("FL1", "8");
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, "FortFrance_town", "quest", "quest1");
			LAi_SetStayType(chr);
		break;

		case "FL1_s54":
			PostVideoAndQuest("France\02", 100, "FL1_s55");
		break;

		case "FL1_s55":
			AddDataToCurrent(0, 0, 4);
			SetCurrentTime(21, 46);
			RefreshLandTime();
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_31"), "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("QuestCabin_Medium", "reload", "reload1", "FL1_s56");
			LaunchFrameForm();
		break;

		case "FL1_s56":
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, pchar.location, "rld", "loc0");
			LAi_SetStayType(chr);
		break;

		case "FL1_s57":
			ChangeCharacterAddressGroup(CharacterFromID("JozephFushe"), "none", "", "");
			pchar.loading_image = "loading\boat.tga";
			DoQuestReloadToLocation("Ship_deck", "goto", "goto5", "FL1_s58");
		break;

		case "FL1_s58":
			chr = GetCharacter(NPC_GenerateCharacter("FL_DurantePascual", "navy_off_spa_1", "man", "man", 1, SPAIN, -1, false));
			FantomMakeCoolFighter(chr, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, 10, 10, "blade9", "pistol1", 20.0);
			chr.name = FindPersonalName("FL_DurantePascual_name");
			chr.lastname = FindPersonalName("FL_DurantePascual_lastname");
			chr.dialog.filename = "Quest\FranceLine\DurantePascual.c";
			chr.greeting = "";

			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto1");
			LAi_SetStayType(chr);

			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, chr, "FL1_s59", -1, 0);

			// логин врагов
			for (i = 1; i < 5; i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 0));
				SetFantomParamFromRank(chr, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, true);
				chr.id = "FL_tmp_enemy";
				PlaceCharacter(chr, "goto", "random");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			}
		break;

		case "FL1_s59":
			chr = CharacterFromID("FL_DurantePascual");
			LAi_SetActorType(chr);
			LAi_ActorRunToLocation(chr, "reload", "reload3", "none", "", "", "", 3.0);

			LAi_SetPlayerType(pchar);

			// наши из засады
			for (i = 1; i < 4; i++)
			{
				chr = GetOurSailor("our_sailor_" + i);
				ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto5");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_warrior_DialogEnable(chr, false);
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
			}

			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("FL_EnemyFight", "FL1_s60");
		break;

		case "FL1_s60":
			Delay_DeleteGroup("FL_EnemyFight");
			pchar.MainQuest = "FL1_s60";
		break;

		case "FL1_s61":
			pchar.loading_image = "";
			DoQuestReloadToLocation("QuestCabin_Medium", "reload", "reload1", "FL1_s62");
		break;

		case "FL1_s62":
			pchar.MainQuest = "";
			SetBan("Looting", 1); //запрещаем лутаться, чтобы не рвать скрипт диалога konstrush
			LAi_SetPlayerType(pchar);
			chr = CharacterFromID("FL_DurantePascual");
			ChangeCharacterAddressGroup(chr, pchar.location, "rld", "loc0");
			LAi_SetWarriorTypeNoGroup(chr);
			LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(chr, 2.0, true, "FL1_s63");
		break;

		case "FL1_s63":
			chr = CharacterFromID("FL_DurantePascual");
			LAi_SetActorType(chr);
			LAi_SetActorType(pchar);
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialogNow(chr, pchar, "FL1_s64", 0);
		break;

		case "FL1_s64":
			LAi_SetPlayerType(pchar);
			chr = CharacterFromID("FL_DurantePascual");
			LAi_SetImmortal(chr, false);
			LAi_SetWarriorTypeNoGroup(chr);
			LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("FL_EnemyFight", "FL1_s65");
		break;

		case "FL1_s65":
			Delay_DeleteGroup("FL_EnemyFight");
			SetLifeDay(CharacterFromID("FL_DurantePascual"), 0);
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL1_s66", -1, 0);
		break;

		case "FL1_s66":
			ChangeCharacterAddressGroup(CharacterFromID("JozephFushe"), "Tortuga_town", "goto", "goto17");
			AddDataToCurrent(0, 0, 7);
			SetCurrentTime(10, 24);
			RefreshLandTime();
			DoQuestCheckDelay("FL1_s66a", 0.5);
		break;

		case "FL1_s66a":
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_32"), "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("Tortuga_town", "reload", "reload1", "FL1_s67");
			LaunchFrameForm();
		break;

		case "FL1_s67":
			chrDisableReloadTolocation = true;
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);

			chr = GetCharacter(NPC_GeneratePhantomCharacter("urban_sold", FRANCE, MAN, 0));
			chr.id = "tmp_fr_sold";
			ChangeCharacterAddressGroup(chr, pchar.location, "quest", "quest1");
			LAi_SetActorType(chr);

			chr2 = CharacterFromID("JozephFushe");
			LAi_SetActorType(chr2);
			LAi_ActorTurnToCharacter(chr2, chr);
			LAi_ActorFollow(chr, chr2, "FL1_s68", -1);
			LAi_ActorFollow(pchar, chr2, "", -1);
		break;

		case "FL1_s68":
			pchar.name = FindPersonalName("FL1_s68_name");
			pchar.lastname = FindPersonalName("FL1_s68_lastname");
			pchar.dialog.currentnode = "FL4_1";

			LAi_ActorSelfDialog(pchar, "FL1_s69");
		break;

		case "FL1_s69":
			pchar.name = FindPersonalName("GrammonPchar_name");
			pchar.lastname = FindPersonalName("GrammonPchar_lastname");

			LAi_ActorGoToLocation(CharacterFromID("tmp_fr_sold"), "reload", "reload4_back", "none", "", "", "", 8.0);
			chr = CharacterFromID("JozephFushe");
			LAi_SetActorType(chr);
			LAi_SetPlayerType(pchar);
			LAi_ActorDialog(chr, pchar, "FL1_s70", -1, 0);
		break;

		case "FL1_s70":
			LAi_ActorRunToLocation(CharacterFromID("JozephFushe"), "reload", "reload3_back", "none", "", "", "FL1_s71", -1);
			EndQuestMovie();
		break;

		case "FL1_s71":
			DoQuestCheckDelay("FL1_s72", 60.0);
		break;

		case "FL1_s72":
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload3_back");
			LAi_ActorDialog(chr, pchar, "FL1_s73", -1, 0);
		break;

		case "FL1_s73":
			chr = CharacterFromID("JozephFushe");
			LAi_ActorGoToLocation(chr, "reload", "reload4_back", "Tortuga_tavern", "sit", "sit_base3", "FL1_s74", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, chr, "", -1);
		break;

		case "FL1_s74":
			LAi_SetSitType(CharacterFromID("JozephFushe"));
			DoQuestReloadToLocation("Tortuga_tavern", "sit", "sit_front3", "FL1_s75");

		break;

		case "FL1_s75":
			LAi_ActorSetSitMode(pchar);
			LAi_ActorDialogNow(pchar, CharacterFromID("JozephFushe"), "FL1_s76", 0);
			CloseQuestHeader("FL1");
			AddQuestRecord("FL1", "9");
		break;

		case "FL1_s76":
			locations[FindLocation("Tortuga_town")].reload.l17.label = "Fushe_House";
			locations[FindLocation("Tortuga_houseZ3")].id.label = "Fushe_House";
			locations[FindLocation("Tortuga_houseZ3")].freeboxes = "";

			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, "Tortuga_houseZ3", "sit", "sit1");
			LAi_SetBarmanType(chr);

			LAi_Fade("", "FL1_s77");

		break;

		case "FL1_s77":
			ChangeCharacterAddressGroup(pchar, pchar.location, "tables", "stay2");
			LAi_SetPlayerType(pchar);

			AddMoneyToCharacter(pchar, 3000);
			AddCharacterExpToSkill(pchar, "Sailing", 100.0);
			AddCharacterExpToSkill(pchar, "Leadership", 100.0);

			//GiveItem2Character(pchar, "clothes33");

			Pchar.Ship.Type = GenerateShipExt(SHIP_VEINARD, true, Pchar); //прописываем уникальность без рандома konstrush
			SetBaseShipData(pchar);
			pchar.Ship.Name = "Veinard";
			pchar.Ship.Crew.Quantity = 15;
			DeleteAttribute(pchar, "Ship.Cargo.Goods");

			SetGoodsInitNull(pchar);

			setCharacterShipLocation(pchar, GetCityFrom_Sea("Tortuga"));
			setWDMPointXZ(GetCityFrom_Sea("Tortuga"));

			Log_Info(StringFromKey("InfoMessages_61"));
			SetQuestHeader("FL2");
			AddQuestRecord("FL2", "1_1");

			chrDisableReloadTolocation = false;
			SetBan("Looting", 0); //снимаем атрибут на запрет лутание трупов konstrush

			// переход в дом Гранье
			pchar.quest.FL1s77.win_condition.l1 = "location";
			pchar.quest.FL1s77.win_condition.l1.location = "FortFrance_houseK5";
			pchar.quest.FL1s77.win_condition = "FL2_s1";

			locations[FindLocation("FortFrance_town")].reload.l15.label = "Granie_house";
			locations[FindLocation("FortFrance_houseK5")].id.label = "Granie_house";
		break;

		//====================================================================================================================
		//	Жан-Жак Гранье
		//====================================================================================================================
		case "FL2_s1":
			AddQuestRecord("FL2", "1");

			pchar.MainQuest = "FL2_s1";        // диалог с нищим
		break;

		case "FL2_s2":
			pchar.MainQuest = "FL2_s2";        // диалог с алкашом
			AddQuestRecord("FL2", "2");
		break;

		case "FL2_s3":
			pchar.MainQuest = "FL2_s3";        // даилог с хозяином верфи
			AddQuestRecord("FL2", "3");
		break;

		case "FL2_s4":
			pchar.MainQuest = "FL2_s4";        // даилог с тавернщиком Ле-Франсуа
			AddQuestRecord("FL2", "4");
		break;

		case "FL2_s5":
			AddCharacterExpToSkill(pchar, "Fortune", 50.0);

			pchar.MainQuest = "";
			bDisableFastReload = true;

			pchar.quest.FL2s5.win_condition.l1 = "location";
			pchar.quest.FL2s5.win_condition.l1.location = "LeFransua_town";
			pchar.quest.FL2s5.win_condition = "FL2_s6";
		break;

		case "FL2_s6":
			chr = GetCharacter(NPC_GenerateCharacter("FL_DuranRimber", "DuranRim", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			FantomMakeCoolFighter(chr, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, 20, 20, "blade9", "pistol1", 10.0);
			chr.dialog.filename = "Quest\FranceLine\DuranRimber.c";
			chr.greeting = "povezlojit";
			chr.name = FindPersonalName("FL_DuranRimber_name");
			chr.lastname = FindPersonalName("FL_DuranRimber_lastname");

			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto3");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL2_s7", -1, 0);
		break;

		case "FL2_s7":
			AddQuestRecord("FL2", "5");

			StartQuestMovie(false, false, true);

			LAi_ActorRunToLocation(CharacterFromID("FL_DuranRimber"), "reload", "reload5_back", "none", "", "", "FL2_s9", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload5_back");
		break;

		case "FL2_s9":
			chrDisableReloadTolocation = true;
			bDisableFastReload = false;

			EndQuestMovie();

			LAi_SetPlayerType(pchar);

			chr = GetOurSailor("FL_tmp_sailor");
			chr.dialog.filename = "Quest\FranceLine\sailor1.c";

			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL2_s10", -1, 0);
		break;

		case "FL2_s10":
			chrDisableReloadTolocation = false;
			LAi_ActorRunToLocation(CharacterFromID("FL_tmp_sailor"), "reload", "reload4_back", "none", "", "", "", -1);
			GiveItem2Character(pchar, "map_normal");
			AddQuestRecord("FL2", "6");
			pchar.MainQuest = "FL2_s10"; // даилог с тавернщиком в Пуэрто-Принсипе
		break;

		case "FL2_s11":
			pchar.MainQuest = "";
			AddQuestRecord("FL2", "7");

			pchar.quest.FL2s11.win_condition.l1 = "location";
			pchar.quest.FL2s11.win_condition.l1.location = "PuertoPrincipe_House1";
			pchar.quest.FL2s11.win_condition = "FL2_s12";
		break;

		case "FL2_s12":
			chrDisableReloadTolocation = true;

			for (i = 4; i < 6; i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 0));
				chr.id = "FL_tmp_pirate" + i;
				ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto" + i);
				LAi_SetActorType(chr);
				if (i == 4)
				{
					chr.dialog.filename = "Quest\FranceLine\pirate1.c";
					chr.greeting = "povezlojit";
					LAi_SetActorType(chr);
					LAi_ActorDialog(chr, pchar, "FL2_s13", -1, 0);
				}
			}
		break;

		case "FL2_s13":
			for (i = 4; i < 6; i++)
			{
				chr = CharacterFromID("FL_tmp_pirate" + i);
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			}

			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("FL_EnemyFight", "FL2_s14");
		break;

		case "FL2_s14":
			Delay_DeleteGroup("FL_EnemyFight");
			chrDisableReloadTolocation = false;
			AddQuestRecord("FL2", "8");

			pchar.quest.FL2s14.win_condition.l1 = "location";
			pchar.quest.FL2s14.win_condition.l1.location = "Terks";
			pchar.quest.FL2s14.win_condition = "FL2_s15";
		break;

		case "FL2_s15":
			chr = GetCharacter(NPC_GenerateCharacter("FL_pluto_captain", "officer_19", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			FantomMakeCoolSailor(chr, SHIP_SCHOONER, "Pluto", CANNON_TYPE_CANNON_LBS6, 25, 25, 25);
			SetFantomParamFromRank(chr, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, true);

			Group_FindOrCreateGroup("FL_PlutoGroup");
			Group_SetType("FL_PlutoGroup", "pirate");
			Group_AddCharacter("FL_PlutoGroup", "FL_pluto_captain");
			Group_SetGroupCommander("FL_PlutoGroup", "FL_pluto_captain");
			Group_SetPursuitGroup("FL_PlutoGroup", PLAYER_GROUP);
			Group_SetTaskAttack("FL_PlutoGroup", PLAYER_GROUP);
			Group_SetAddress("FL_PlutoGroup", "Terks", "", "");
			Group_LockTask("FL_PlutoGroup");

			pchar.quest.FL2s15.win_condition.l1 = "Group_Death";
			pchar.quest.FL2s15.win_condition.l1.group = "FL_PlutoGroup";
			pchar.quest.FL2s15.win_condition = "FL2_s16";
		break;

		case "FL2_s16":
			AddQuestRecord("FL2", "9");
			pchar.quest.FL2s16.win_condition.l1 = "location";
			pchar.quest.FL2s16.win_condition.l1.location = "Terks_grot";
			pchar.quest.FL2s16.win_condition = "FL2_s17";
		break;

		case "FL2_s17":
			chrDisableReloadTolocation = true;
			LAi_LocationDisableMonGenTimer("Terks_grot", 1); //заблочим скелетов на 1 день konstrush
			//Log_Info("Слышны чьи-то голоса, надо подойти поближе...");

			// Гранье
			chr = GetCharacter(NPC_GenerateCharacter("FL_granie", "granie", "man", "man", sti(pchar.rank), FRANCE, -1, false));
			chr.name = FindPersonalName("FL_granie_name");
			chr.lastname = FindPersonalName("FL_granie_lastname");
			chr.dialog.filename = "Quest\FranceLine\Granie.c";
			chr.dialog.currentnode = "0";
			chr.greeting = "";
			LAi_CharacterDisableDialog(chr);

			__DEPRECATED_SetOfficerParam(chr, 1);
			SetSPECIAL(chr, 8, 10, 5, 3, 10, 4, 10);
			SetSelfSkill(chr, 10, 10, 10, 10, 36);
			SetShipSkill(chr, 5, 13, 50, 50, 8, 16, 2, 7, 60);
			SetRankFromSkill(chr);
			chr.reputation = 80;
			chr.alignment = "good";
			//черты
			SetCharacterPerk(chr, "LoyalOff");
			SetCharacterPerk(chr, "Honest");

			DelEqiup(chr, true, false);

			chr.quest_character = true;
			LAi_SetGroundSitType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto6");
			LAi_SetImmortal(chr, true);

			// Бандиты
			chr = CharacterFromID("FL_DuranRimber");
			chr.greeting = "roja";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto5");
			LAi_SetActorType(chr);

			for (i = 2; i < 5; i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 0));
				chr.id = "FL_tmp_bandit" + i;
				ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto" + i);
				LAi_SetActorType(chr);
				LAi_ActorTurnToLocator(chr, "goto", "goto6");
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			}

			pchar.MainQuest = "FL2_s17";

			StartQuestMovie(false, false, true);
			DoQuestCheckDelay("FL2_s17_1", 0.05);
			LAi_SetActorType(pchar);
		break;

		case "FL2_s17_1":
			locCameraFromToPos(5.80, 7.80, -8.10, false, 1.50, 1.70, 5.40);
			DoQuestCheckDelay("FL2_s18", 1.60);
		break;

		case "FL2_s18":
			pchar.MainQuest = "";

			pchar.name = FindPersonalName("FL2_s18_name");
			pchar.lastname = FindPersonalName("FL2_s18_lastname");
			pchar.dialog.currentnode = "FL2_18";

			LAi_SetActorType(pchar);
			LAi_ActorSelfDialog(pchar, "FL2_s19");
		break;

		case "FL2_s18b":
			locCameraFromToPos(-4.00, 5.00, 4.00, true, 5.00, 0.00, 5.00);
		break;

		case "FL2_s18c":
			ChangeCharacterAddressGroup(pchar, "Terks_Grot", "monsters", "monster1");
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "item", "detector1", "FL2_s19", -1);
		break;

		case "FL2_s19":
			DoQuestCheckDelay("FL2_s20", 1.0);
			DoQuestCheckDelay("FL2_s20_1", 3.7);
		break;

		case "FL2_s20":
			pchar.name = FindPersonalName("FL2_s20_name");
			pchar.lastname = FindPersonalName("FL2_s20_lastname");
			pchar.dialog.currentnode = "FL2_s20";
			LAi_ActorSelfDialog(pchar, "FL2_s21");

		//LAi_ActorTurnToCharacter(chr, pchar);
		break;

		case "FL2_s20_1":
			chr = CharacterFromID("FL_tmp_bandit4");
			//LAi_SetActorType(chr);
			LAi_ActorTurnToCharacter(chr, pchar);
		break;

		case "FL2_s21":
			pchar.name = FindPersonalName("GrammonPchar_name");
			pchar.lastname = FindPersonalName("GrammonPchar_lastname");
			LAi_SetPlayerType(pchar);
			LAi_ActorDialog(CharacterFromID("FL_DuranRimber"), pchar, "FL2_s22", -1, 0);
			StartQuestMovie(false, false, true);
		break;

		case "FL2_s22":
			chr = CharacterFromID("FL_DuranRimber");
			chr.money = 10000;
			chr.SaveItemsForDead = true;
			LAi_SetWarriorType(chr);
			LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			/*chr = CharacterFromID("FL_tmp_bandit4");
			LAi_SetWarriorType(chr);
			LAi_group_MoveCharacter(chr, "FL_EnemyFight");*/

			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("FL_EnemyFight", "FL2_s23");

			pchar.MainQuest = "FL2_s22";

			EndQuestMovie();
		break;

		case "FL2_s23":
			Delay_DeleteGroup("FL_EnemyFight");
			LAi_CharacterEnableDialog(CharacterFromID("FL_granie"));
			pchar.MainQuest = "FL2_s23";
		break;

		case "FL2_s24":        // вызывается после обыска тела Дюрана (itemsbox.c)
		// если хотя бы один из бандитов в живых, задерживаем квест
			if (pchar.MainQuest != "FL2_s23") DoQuestCheckDelay("FL2_s24a", 0.5);
			else DoQuestCheckDelay("FL2_s25", 1.0);
		break;

		case "FL2_s24a":
			DoQuestCheckDelay("FL2_s24", 5.0);
		break;

		// все мертвы, труп обыскан
		case "FL2_s25":
			pchar.MainQuest = "";
		break;

		case "FL2_s26":
			OfficersReaction("good");
			ChangeCharacterReputation(pchar, 5);
			AddCharacterExpToSkill(pchar, "LeaderShip", 50.0);

			chrDisableReloadTolocation = false;
			chr = CharacterFromID("FL_granie");
			chr.location = "none";

			SetCharacterPerk(chr, "FastReload");
			SetCharacterPerk(chr, "HullDamageUp");

			AddPassenger(pchar, chr, false);
			SetCharacterRemovable(chr, false);
			chr.Payment = true; // признак офицера для бонусов от предметов; true с зарплатой
			chr.CompanionDisable = true;
			chr.AllowedPosts = "cannoner";
			chr.OfficerWantToGo.DontGo = true;
			DoReloadCharacterToLocation("Terks_CaveEntrance", "reload", "reload1");

			pchar.quest.FL2s26.win_condition.l1 = "EnterToSea";
			pchar.quest.FL2s26.win_condition = "FL2_s27";
		break;

		case "FL2_s27":
			Set_My_Cabin();
			pchar.quest.FL2s27.win_condition.l1 = "location";
			pchar.quest.FL2s27.win_condition.l1.location = Get_My_Cabin();
			pchar.quest.FL2s27.win_condition = "FL2_s28";
			DoQuestCheckDelay("FL2_s28a", 1.0);
		break;

		case "FL2_s28a":
			Sea_CabinStartNow();
		break;

		case "FL2_s28":
			chr = CharacterFromID("FL_granie");
			PlaceCharacter(chr, "rld", "random_must_be");
			LAi_SetStayType(chr);
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, chr, "FL2_s29", -1, 0);
		break;

		case "FL2_s29":
			AddQuestRecord("FL2", "10");
			chr = CharacterFromID("FL_granie");
			ChangeCharacterAddressGroup(chr, "none", "", "");
			chr.greeting = "granie";

			LAi_SetPlayerType(pchar);

			pchar.quest.FL2s29.win_condition.l1 = "location";
			pchar.quest.FL2s29.win_condition.l1.location = "Martinique";
			pchar.quest.FL2s29.win_condition = "FL2_s30";
		break;

		case "FL2_s30":
			bQuestDisableMapEnter = true;
			Island_SetReloadEnableGlobal("Martinique", false);

			chr = GetCharacter(NPC_GenerateCharacter("FL_blackTwister_captain", "officer_20", "man", "man", sti(pchar.rank), PIRATE, -1, true)); //другую модельку бы konstrush
			FantomMakeCoolSailor(chr, SHIP_SCHOONER_W, "Black Twister", CANNON_TYPE_CANNON_LBS8, 30, 30, 30);
			SetFantomParamFromRank(chr, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, true);
			chr.SaveItemsForDead = true;
			chr.DontClearDead = true;
			chr.name = FindPersonalName("FL_blackTwister_captain_name");
			chr.lastname = FindPersonalName("FL_blackTwister_captain_lastname");
			chr.dialog.filename = "Quest\FranceLine\BlackTwister_capitan.c";
			chr.dialog.currentnode = "BlackTwister_capitan";
			chr.greeting = "zdaus";

			Group_FindOrCreateGroup("FL_BT_Group");
			Group_SetType("FL_BT_Group", "pirate");
			Group_AddCharacter("FL_BT_Group", chr.id);
			Group_SetGroupCommander("FL_BT_Group", chr.id);
			Group_SetPursuitGroup("FL_BT_Group", PLAYER_GROUP);
			Group_SetTaskAttack("FL_BT_Group", PLAYER_GROUP);
			Group_SetAddress("FL_BT_Group", "Martinique", "", "");
			Group_LockTask("FL_BT_Group");

			SetQuestAboardCabinDialog(chr);

			pchar.quest.FL2s30a.win_condition.l1 = "Character_sink";
			pchar.quest.FL2s30a.win_condition.l1.character = "FL_blackTwister_captain";
			pchar.quest.FL2s30a.win_condition = "FL2_s31a";
		break;

		//------------------------------------------------------------------------------------------------------
		// если взяли в плен капитана Black Twister
		case "FL2_s31":
			DeleteQuestCheck("FL2s30");
			QuestAboardCabinDialogQuestSurrender();
			pchar.MainQuest.PtisonIdx = pchar.GenQuest.LastQuestPrisonerIdx; // запомним индекс
			AddQuestRecord("FL2", "12");
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Martinique", true);
			pchar.MainQuest = "FL2_s31";
		break;

		//------------------------------------------------------------------------------------------------------
		// если потопили Black Twister
		case "FL2_s31a":
			AddQuestRecord("FL2", "11");
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Martinique", true);
			pchar.MainQuest.usurer = "FL_BlackTwister_dead"; // на разговор с ростовщиком
		break;
		//------------------------------------------------------------------------------------------------------

		// это же событие приходит при выходе от ростовщика и при выходе от губера, т.е. сходится в одну точку
		case "FL2_s32":
			pchar.MainQuest = "";

			pchar.quest.FL2s32.win_condition.l1 = "location";
			pchar.quest.FL2s32.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FL2s32.win_condition = "FL2_s33";
		break;

		case "FL2_s33":
			chrDisableReloadTolocation = true;
			chr = CharacterFromID("FL_granie");
			RemovePassenger(pchar, chr);
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL2_s34", -1, 0);
		break;

		case "FL2_s34":
			AddQuestRecord("FL2", "13");
			LAi_ActorRunToLocation(CharacterFromID("FL_granie"), "reload", "houseK5", "none", "", "", "", 10.0);
			chrDisableReloadTolocation = false;
			locations[FindLocation("FortFrance_town")].reload.l15.disable = 1;
			SetTimerConditionParamEx("FL2s34", "FL2_s35", 0, 0, 3);
		break;

		case "FL2_s35":
			FreeSitlocator("FortFrance_tavern", "sit_base1");
			chr = CharacterFromID("FL_granie");
			LAi_NPC_Equip(chr, sti(pchar.rank), true, true);
			LAi_SetSitType(chr);
			ChangeCharacterAddressGroup(chr, "FortFrance_tavern", "sit", "sit_base1");
		break;

		case "FL2_s36":
			LAi_Fade("FL2_s37", "");
		break;

		case "FL2_s37":
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);

			FreeSitLocator("FortFrance_tavern", "sit_front1");
			ChangeCharacterAddressGroup(pchar, "FortFrance_tavern", "sit", "sit_front1");
			LAi_ActorDialogNow(pchar, CharacterFromID("FL_granie"), "FL2_s38", 0);
		break;

		case "FL2_s38":
			LAi_Fade("FL2_s39", "");
		break;

		case "FL2_s39":
			chr = CharacterFromID("FL_granie");
			AddPassenger(pchar, chr, false);
			SetCharacterRemovable(chr, false);
			ChangeCharacterAddressGroup(chr, "none", "", "");
			LAi_SetPlayerType(pchar);
			PlaceCharacter(pchar, "tables", pchar.location);

			AddQuestRecord("FL2", "14");

			locations[FindLocation("Tortuga_town")].reload.l17.disable = 1;

			pchar.quest.FL2s39.win_condition.l1 = "location";
			pchar.quest.FL2s39.win_condition.l1.location = "Tortuga_townhall";
			pchar.quest.FL2s39.win_condition = "FL2_s40";

			pchar.MainQuest = "FL2_s39";
		break;

		case "FL2_s40":
			chrDisableReloadTolocation = true;
			chr = CharacterFromID("FL_granie");
			RemovePassenger(pchar, chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1");
			LAi_SetActorType(chr);
			LAi_ActorFollow(chr, pchar, "", -1);
		break;

		case "FL2_s41":
			AddMoneyToCharacter(pchar, 5000);

			pchar.MainQuest = "";

			chrDisableReloadTolocation = false;
			chr = CharacterFromID("FL_granie");
			LAi_SetActorType(chr);
			chr.location = "none";
			AddQuestRecord("FL2", "15");
			locations[FindLocation("Tortuga_town")].reload.l3.disable = 1;
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
			ChangeCharacterAddressGroup(CharacterFromID("JozephFushe"), "none", "", "");

			chr = GetCharacter(NPC_GenerateCharacter("FL_ElizabetBrulua", "girl_5", "woman", "towngirl", 1, FRANCE, -1, false)); //TODO: уникальную
			ChangeCharacterAddressGroup(chr, "Tortuga_houseZ3", "barmen", "stay");
			LAi_SetBarmanType(chr);

			chr.name = FindPersonalName("FL_ElizabetBrulua_name");
			chr.lastname = FindPersonalName("FL_ElizabetBrulua_lastname");
			chr.dialog.filename = "Quest\FranceLine\ElizabetBrulua.c";
			chr.greeting = "france_woman";
		break;

		case "FL2_s42":
			AddQuestRecord("FL2", "16");
			FreeSitlocator("Tortuga_tavern", "sit_base4");
			chr = CharacterFromID("FL_granie");
			ChangeCharacterAddressGroup(chr, "Tortuga_tavern", "sit", "sit_base4");
			LAi_SetSitType(chr);

			pchar.quest.FL2s42.win_condition.l1 = "location";
			pchar.quest.FL2s42.win_condition.l1.location = "Tortuga_tavern";
			pchar.quest.FL2s42.win_condition = "FL2_s43";
		break;

		case "FL2_s43":
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "tables", "stay3", "FL2_s44", -1);
		break;

		case "FL2_s44":
			EndQuestMovie();
			//InterfaceStates.Buttons.Save.enable = true;
			LAi_Fade("FL2_s45", "");
		break;

		case "FL2_s45":
			LAi_ActorSetSitMode(pchar);

			FreeSitLocator("Tortuga_tavern", "sit_front4");
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_front4");
			LAi_ActorDialogNow(pchar, CharacterFromID("FL_granie"), "FL2_s46", 0);
		break;

		case "FL2_s46":
			LAi_Fade("FL2_s47", "");
		break;

		case "FL2_s47":
			LAi_SetPlayerType(pchar);
			PlaceCharacter(pchar, "tables", pchar.location);
			chr = CharacterFromID("FL_granie");
			ChangeCharacterAddressGroup(chr, "none", "", "");
			AddPassenger(pchar, chr, false);
			SetCharacterRemovable(chr, true);

			AddQuestRecord("FL2", "17");
			SetQuestHeaderColor("FL2", gray);
			CloseQuestHeader("FL2");

			pchar.MainQuest = "FL3";        // в диалог с губернатором
			locations[FindLocation("Tortuga_town")].reload.l3.disable = 0;
		break;

		//====================================================================================================================
		//	В поисках капитана Фуше
		//====================================================================================================================
		case "FL3":
			DeleteAttribute(pchar, "MainQuest.usurer");

			// назначаем нового банкира ->
			chr = CharacterFromID("FortFrance_usurer");
			SetRandomNameToCharacter(chr);
			chr.model = "usurer_7"; //watch_quest_moment
			chr.quest.meeting = "0";
			ChangeCharacterAddressGroup(chr, "FortFrance_Bank", "barmen", "stay");
			LAi_SetOwnerType(chr);
			// назначаем нового банкира <-

			pchar.MainQuest = "FL3_s1";
			SetQuestHeader("FL3");
			AddQuestRecord("FL3", "1");
		break;
	}
}/*	
		case "FL3_s2":
			pchar.MainQuest = "FL3_s2";			// в диалог с контрабандистом
		break;

		case "FL3_s3":
			AddQuestRecord("FL3", "2");
			pchar.MainQuest = "FL3_s3";			// в диалог с контрабандистом (сдача рабов)
		break;

		case "FL3_s4":
			pchar.MainQuest = "";
			AddQuestRecord("FL3", "4");
			SetTimerConditionParamEx("FL3s4", "FL3_s5", 0, 0, 1);
		break;

		case "FL3_s5":
			chr = GetCharacter(NPC_GenerateCharacter("FL_old_smuggler", "old_smuggler", "man", "man_B", 10, FRANCE, -1, true));
			chr.name = "Бьюв";
			chr.lastname = "Вуиттон";
			chr.dialog.filename = "Quest\FranceLine\OldSmuggler.c";
			chr.greeting = "maybe_buisness";
			FreeSitlocator("Tortuga_tavern", "sit_base1");
			LAi_SetSitType(chr);
			ChangeCharacterAddressGroup(chr, "Tortuga_tavern", "sit", "sit_base1");
		break;

		case "FL3_s6":
			FreeSitlocator("Tortuga_tavern", "sit_front1");
			LAi_Fade("FL3_s7", "");
		break;

		case "FL3_s7":
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
            
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit_front1");
			LAi_ActorDialogNow(pchar, CharacterFromID("FL_old_smuggler"), "FL3_s8", 0);
		break;

		case "FL3_s8":
			LAi_Fade("FL3_s9","");
		break;

		case "FL3_s9":
			LAi_SetPlayerType(pchar);
			PlaceCharacter(pchar, "tables", pchar.location);
			AddQuestRecord("FL3", "5");
			pchar.MainQuest = "FL3_s9";
			SetTimerConditionParamEx("FL3s9", "FL3a_s10", 0, 0, 5);

			pchar.quest.FL3s9a.win_condition.l1 = "location";
			pchar.quest.FL3s9a.win_condition.l1.location = "PortPax_town";
			pchar.quest.FL3s9a.win_condition = "FL3_s10";
		break;

		//------------------------------------------------------------------------------
		// Просрочили прибытие в город ->
		case "FL3a_s10":
			DeleteQuestCheck("FL3s9a");
			chr = CharacterFromID("PortPax_shipyarder");
			chr.model	= "shipowner_10";
			SetRandomNameToCharacter(chr);

			pchar.MainQuest = "FL3a_s10";
		break;

		case "FL3a_s11":
			pchar.MainQuest = "FL3a_s11";	// в диалог с контрабандистом
			AddQuestRecord("FL3", "6a");
		break;

		case "FL3a_s12":
			chr = CharacterFromID("FL_old_smuggler");
			chr.location = "none";
			SetLifeDay(chr, 0);
			AddQuestRecord("FL3", "7a");
		break;
		// Просрочили прибытие в город <-

		//------------------------------------------------------------------------------
		// Прибыли в город вовремя ->
		case "FL3_s10":
			pchar.MainQuest = "";
			DeleteQuestCheck("FL3s9");
			pchar.loading_image = "loading\fort_512.tga";
			SetTownCapturedState("PortPax", true);
			DoQuestCheckDelay("FL3_s10a", 0.1);
		break;

		case "FL3_s10a":
			DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "FL3_s11");
		break;

		case "FL3_s11":
			chrDisableReloadTolocation = true;
			pchar.loading_image = "";
			// накидаем трупов
			for(i = 0;i<8;i++)
			{
				switch(rand(2))
				{
					case 0: sStr = "citizen"; break;
					case 1: sStr = "soldier"; break;
					case 2: sStr = "soldier"; break;
				}
				n = MAN;
				if(sStr == "citizen") n = Rand(WOMAN);
				chr = GetCharacter(NPC_GeneratePhantomCharacter(sStr, FRANCE, n, 0));
				LAi_SetActorTypeNoGroup(chr);
				LAi_ActorSetLayMode(chr);
				LAi_LoginInCaptureTown(chr, true);
				PlaceCharacter(chr, "soldiers", "random");
			}

			for(i = 0;i<8;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter(sStr, SPAIN, n, 0));
				LAi_SetActorTypeNoGroup(chr);
				LAi_ActorSetLayMode(chr);
				LAi_LoginInCaptureTown(chr, true);
				PlaceCharacter(chr, "patrol", "random");
			}

			// Наших всего 8
			for(i=0; i<8; i++)
			{
				if(rand(3) == 3)
					chr = GetCharacter(NPC_GeneratePhantomCharacter("mushketer", FRANCE, MAN, 0));
				else
					chr = GetCharacter(NPC_GeneratePhantomCharacter("soldier", FRANCE, MAN, 0));

				LAi_LoginInCaptureTown(chr, true);
				PlaceCharacter(chr, "goto", "random");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
			}

			// Испанцев 16
			for(i=0; i<16; i++)
			{
				if(rand(3) == 3)
					chr = GetCharacter(NPC_GeneratePhantomCharacter("mushketer", SPAIN, MAN, 0));
				else
					chr = GetCharacter(NPC_GeneratePhantomCharacter("soldier", SPAIN, MAN, 0));

				LAi_LoginInCaptureTown(chr, true);
				PlaceCharacter(chr, "goto", "random");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_enemyFight");
			}

			LAi_group_SetRelation("FL_enemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_enemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("FL_enemyFight", "FL3_s12");
		break;

		case "FL3_s12":
			chr2 = CharacterFromID("PortPax_shipyarder");
			chr = GetCharacter(NPC_GenerateCharacter("FL_ShipYarderPhantom", chr2.model, "man", "man", 5, FRANCE, 0, true));
			chr.name = chr2.name;
			chr.lastname = chr2.lastname;
			chr.greeting = "spainsh_busters";
			chr.dialog.filename = "Quest\FranceLine\ShipYarderPhantom.c";
			LAi_LoginInCaptureTown(chr, true);
			PlaceCharacter(chr, "reload", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL3_s13", -1, 0);
		break;

		case "FL3_s13":
			chrDisableReloadTolocation = false;
			Island_SetReloadEnableGlobal("Hispaniola2", false);

			// Два испанских пинаса
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
			chr.id = "FL_SpainCaptain1";
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 40, 40, "", "", 100.0);
			FantomMakeCoolSailor(chr, SHIP_PINNACE, "Orfeo", CANNON_TYPE_CANNON_LBS12, 50, 50, 50);

			Group_CreateGroup("FL_SeaEnemy");
			Group_addCharacter("FL_SeaEnemy", "FL_SpainCaptain1");
			Group_SetGroupCommander("FL_SeaEnemy", "FL_SpainCaptain1");

			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
			chr.id = "FL_SpainCaptain2";
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 40, 40, "", "", 100.0);
			FantomMakeCoolSailor(chr, SHIP_PINNACE, "Santa Matilda", CANNON_TYPE_CANNON_LBS12, 50, 50, 50);
			Group_addCharacter("FL_SeaEnemy", "FL_SpainCaptain2");

			Group_SetAddress("FL_SeaEnemy", "Hispaniola2", "Quest_ships", "Quest_Ship_9");
			
			pchar.quest.FL3s13.win_condition.l1 = "Group_Death";
		    pchar.quest.FL3s13.win_condition.l1.group = "FL_SeaEnemy";
		    pchar.quest.FL3s13.win_condition = "FL3_s14";
		break;

		case "FL3_s14":
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			SetTownCapturedState("PortPax", false);
			pchar.MainQuest = "FL3_s14";
			AddQuestRecord("FL3", "6");
		break;

		case "FL3_s15":
			pchar.MainQuest = "FL3_s15";
			AddQuestRecord("FL3", "7");
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			ChangeCharacterReputation(pchar, 5);
			OfficersReaction("good");
		break;

		case "FL3_s16":
			chr = CharacterFromID("FL_old_smuggler");
			chr.location = "none";
			AddPassenger(pchar, chr, false);
			SetCharacterRemovable(chr, false);
			pchar.MainQuest = "FL3_s16";
			AddQuestRecord("FL3", "8");
			LAi_SetImmortal(chr, true);
			
			pchar.quest.FL3s16.win_condition.l1 = "location";
			pchar.quest.FL3s16.win_condition.l1.location = "PortoBello_store";
			pchar.quest.FL3s16.win_condition = "FL3_s17";
		break;

		case "FL3_s17":
			chr = CharacterFromID("FL_old_smuggler");
			PlaceCharacter(chr, "reload", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorFollow(chr, pchar, "", -1);
		break;
		// Прибыли в город вовремя <-

		// Дальше выбор события - реакция торговца Портобело на действия выше (льтерантива с кирпичами полностью в диалоге торговца)
		//------------------------------------------------------------------------------------------------
		case "FL3_s18":
			if(GetPassengerNumber(pchar, GetCharacterIndex("FL_old_smuggler")) != -1)
			{
				chr = CharacterFromID("FL_old_smuggler");
				chr.dialog.currentnode = "21";
				LAi_ActorDialogNow(chr, pchar, "FL3_s19", 0);
			}
			
			AddQuestRecord("FL3", "9");

			pchar.quest.FL3s18.win_condition.l1 = "EnterToSea";
			pchar.quest.FL3s18.win_condition = "FL3_s20";
		break;

		case "FL3_s19":
			chr = CharacterFromID("FL_old_smuggler");
			RemovePassenger(pchar, chr);
			SetLifeDay(chr, 0);
			LAi_ActorGoToLocation(chr, "reload", "reload1_back", "none", "", "", "", -1);
		break;

		case "FL3_s20":
			Set_My_Cabin();
			pchar.quest.FL3s20.win_condition.l1 = "location";
			pchar.quest.FL3s20.win_condition.l1.location = Get_My_Cabin();
			pchar.quest.FL3s20.win_condition = "FL3_s22";
			DoQuestCheckDelay("FL3_s21", 1.0);
		break;
		
		case "FL3_s21":
			Sea_CabinStartNow();
		break;

		case "FL3_s22":
			chr = CharacterFromID("FL_granie");
			ChangeCharacterAddressGroup(chr, pchar.location, "rld", "aloc1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL3_s23", -1, 0);
		break;

		case "FL3_s23":
			AddQuestRecord("FL3", "10")
			chr = CharacterFromID("FL_granie");
			chr.location = "none";

			Return2SeaAfterCabin();
			DoQuestCheckDelay("FL3_s24", 2.0);
		break;

		case "FL3_s24":
			PostVideoAndQuest("France\03", 100, "FL3_s25");
			AddTimeToCurrent(3, 17);
		break;

		case "FL3_s25":
			Sea_DeckBoatLoad(GetMainCharacterIndex());
			pchar.quest.FL3s25.win_condition.l1 = "location";
			pchar.quest.FL3s25.win_condition.l1.location = "Deck_Near_Ship"; // было Deck_Near_Ship
			pchar.quest.FL3s25.win_condition = "FL3_s26";
		break;

		case "FL3_s26":
			LAi_SetPlayerType(pchar);
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			
			chr = GetCharacter(NPC_GenerateCharacter("FL_Fushe_sailor", "pirate_10", "man", "man", 1, FRANCE, 0, false));
			chr.name = "Рулевой с";
			chr.lastname = "корабля Фуше";
			chr.dialog.filename = "Quest\FranceLine\Fushe_sailor.c";
			chr.greeting = "mesie";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto3");
			LAi_SetActorType(chr);
			LAi_ActorWaitDialog(chr, pchar);
			LAi_ActorDialog(pchar, chr, "FL3_s27", -1, 0);
		break;

		case "FL3_s27":
			LAi_SetPlayerType(pchar);
			EndQuestMovie();
			Return2SeaAfterCabin();
			AddQuestRecord("FL3", "11");

			pchar.quest.FL3s27.win_condition.l1 = "location";
			pchar.quest.FL3s27.win_condition.l1.location = "Cartahena_town";
			pchar.quest.FL3s27.win_condition = "FL3_s28";
		break;

		case "FL3_s28":
			chrDisableReloadTolocation = true;
			Pchar.GenQuest.Hunter2Pause = true;
			chr = CharacterFromID("FL_granie");
			chr.dialog.currentnode = "32";
			ChangeCharacterAddressGroup(chr, pchar.location, "quest", "quest1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL3_s29", -1, 0);
		break;

		case "FL3_s29":
			chr = CharacterFromID("FL_granie");
			RemovePassenger(pchar, chr);
			LAi_ActorRunToLocation(chr, "reload", "reload1_back", "none", "", "", "", -1);
			chrDisableReloadTolocation = false;
			AddQuestRecord("FL3", "12");

			SetTimerConditionParamEx("FL3s30", "FL3_s30", 0, 0, 14);
		break;

		case "FL3_s30":
			AddQuestRecord("FL3", "13");
			pchar.MainQuest = "FL3_s30";
		break;

		case "FL3_s31":
			GiveItem2Character(pchar, "FQ_letter3");
			pchar.MainQuest = "";
		break;

		case "FL3_s32":		// вызов после чтения письма
			pchar.quest.FL3s32.win_condition.l1 = "location";
			pchar.quest.FL3s32.win_condition.l1.location = "Cumana_town";
			pchar.quest.FL3s32.win_condition = "FL3_s33";
		break;

		case "FL3_s33":
			chrDisableReloadTolocation = true;
			Pchar.GenQuest.Hunter2Pause = true;

			chr = CharacterFromID("FL_granie");
			ChangeCharacterAddressGroup(chr, pchar.location, "quest", "quest1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL3_s34", -1, 0);
		break;

		case "FL3_s34":
			pchar.MainQuest = "FL3_s34";
			chr = CharacterFromID("FL_granie");
			LAi_ActorFollowEverywhere(chr, "", -1);
			DoQuestReloadToLocation("Cumana_tavern", "reload", "reload1", "");
		break;

		case "FL3_s35":
			pchar.MainQuest = "";
			chr = CharacterFromID("FL_granie");
			LAi_ActorDialog(chr, pchar, "FL3_s36", -1, 0);
		break;

		case "FL3_s36":
			chrDisableReloadTolocation = false;
			chr = CharacterFromID("FL_granie");
			chr.location = "none";
			LAi_SetActorType(chr);
			AddPassenger(pchar, chr, false);

			pchar.MainQuest = "FL3_s36";		// в диалог с начальником тюрьмы
			AddQuestRecord("FL3", "14");
		break;

		case "FL3_s37":
			pchar.MainQuest = "";
			AddMoneyToCharacter(pchar, -500);
			pchar.questTemp.jailCanMove = true;

			chr = GetCharacter(NPC_GenerateCharacter("FL_fushe_sailor2", "pirat8", "man", "man_B", 1, FRANCE, -1, false));
			chr.name = "Амильс";
			chr.lastname = "Ньюль";
			chr.dialog.filename = "Quest\FranceLine\sailor2.c";
			chr.greeting = "spainsh_busters";
			LAi_SetStayType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto9");
		break;

		case "FL3_s38":
			pchar.questTemp.jailCanMove = false;
			pchar.MainQuest = "";
			
			pchar.quest.FL3s38.win_condition.l1 = "locator";
			pchar.quest.FL3s38.win_condition.l1.location = "Cumana_cave";
			pchar.quest.FL3s38.win_condition.l1.locator_group = "item";
			pchar.quest.FL3s38.win_condition.l1.locator = "item1";
			pchar.quest.FL3s38.win_condition = "FL3_s39";
		break;

		case "FL3_s39":
			pchar.MainQuest = "FL3_s39";
			AddQuestRecord("FL3", "15");
			GiveItem2Character(pchar, "jewelry18");

			chrDisableReloadTolocation = true;
			for(i=0;i<3;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 0));
				chr.id = "FL_tmp_pirate"+i;
				chr.dialog.filename = "Quest\FranceLine\pirate2.c";
				chr.greeting = "uebat";
				LAi_SetActorType(chr);
				ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1_back");
				if(i==0) LAi_ActorDialog(chr, pchar, "FL3_s40", -1, 0);
				else LAi_ActorFollow(chr, CharacterFromID("FL_tmp_pirate0"), "", -1);
			}
		break;

		case "FL3_s40":
			for(i=0;i<3;i++)
			{
				chr = CharacterFromID("FL_tmp_pirate"+i);
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			}

			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("FL_EnemyFight", "FL3_s41");
		break;

		case "FL3_s41":
			Delay_DeleteGroup("FL_EnemyFight");
			chrDisableReloadTolocation = false;
		break;

		case "FL3_s42":
			pchar.MainQuest = "FL3_s42";
			TakeItemFromCharacter(pchar, "jewelry18");
			pchar.questTemp.jailCanMove = true;
			// тут надо идти к зеку и говорить с ним об освобождении
		break;

		case "FL3_s43":
			pchar.questTemp.jailCanMove = false;
			pchar.MainQuest = "";
			chr = CharacterFromID("FL_fushe_sailor2");
			LAi_SetActorType(chr);
			LAi_ActorFollowEverywhere(chr,"", -1);
			AddPassenger(pchar, chr, false);
			SetCharacterRemovable(chr, false);
			LAi_SetImmortal(chr, true);
			DoReloadCharacterToLocation("Cumana_Fort", "reload", "reload2");

			pchar.quest.FL3s43.win_condition.l1 = "EnterToSea";
			pchar.quest.FL3s43.win_condition = "FL3_s44";
		break;

		case "FL3_s44":
			Set_My_Cabin();
			pchar.quest.FL3s44.win_condition.l1 = "location";
			pchar.quest.FL3s44.win_condition.l1.location = Get_My_Cabin();
			pchar.quest.FL3s44.win_condition = "FL3_s46";
			DoQuestCheckDelay("FL3_s45", 1.0);
		break;
		
		case "FL3_s45":
			Sea_CabinStartNow();
		break;

		case "FL3_s46":
			chr = CharacterFromID("FL_fushe_sailor2");
			PlaceCharacter(chr, "rld", "random_must_be_near");
			LAi_ActorDialog(chr, pchar, "FL3_s47", -1, 0);
		break;

		case "FL3_s47":
			AddQuestRecord("FL3", "16");
			chr = CharacterFromID("FL_fushe_sailor2");
			chr.location = "none";

			pchar.MainQuest = "FL3_s47";		// в диалог с губером Гибралтара

			// Это для парня, который хочет отблагодарить за спасение
			pchar.quest.FL3s47.win_condition.l1 = "location";
			pchar.quest.FL3s47.win_condition.l1.location = "Shore57";
			pchar.quest.FL3s47.win_condition = "FL3_s47a";

			pchar.quest.FL3s47a.win_condition.l1 = "location";
			pchar.quest.FL3s47a.win_condition.l1.location = "Shore56";
			pchar.quest.FL3s47a.win_condition = "FL3_s47a";
		break;

		case "FL3_s47a":
			DeleteQuestCheck("FL3s47");
			DeleteQuestCheck("FL3s47a");
			chr = CharacterFromID("FL_fushe_sailor2");
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_ActorDialog(chr, pchar, "FL3_s47b", -1, 0);
		break;

		case "FL3_s47b":
			chr = CharacterFromID("FL_fushe_sailor2");
			RemovePassenger(pchar, chr);
			SetLifeDay(chr, 0);
			TakeNItems(pchar, "jewelry11", 20);
			log_info("Получено 20 жемчужин");
		break;

		// Тут дальше по Фуше
		case "FL3_s48":
			chrDisableReloadTolocation = true;
			pchar.MainQuest = "";
			
			LAi_Fade("FL3_s49", "FL3_s50");
		break;

		case "FL3_s49":
			chr = CharacterFromID("JozephFushe");
			chr.dialog.currentnode = "44";

			SetSPECIAL(chr, 10, 7, 5, 7, 3, 4, 5);		// Сила, Восприятие, Выносливость, Лидерство, Обучаемость, Реакция, Удача
			SetSelfSkill(chr, 10, 20, 30, 25, 15);
			SetShipSkill(chr, 60, 20, 25, 21, 55, 37, 24, 31, 50);
			SetRankFromSkill(chr);
			DelEqiup(chr, true, false);

			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1");
			LAi_SetActorType(chr);
		break;

		case "FL3_s50":
			LAi_ActorDialog(CharacterFromID("JozephFushe"), pchar, "FL3_s51", -1, 0);
		break;

		case "FL3_s51":
			pchar.MainQuest = "FL3_s51";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, CharacterFromID("Guibraltar_mayor"), "FL3_s52", -1, 0);
		break;

		case "FL3_s52":
			chrDisableReloadTolocation = false;
			pchar.MainQuest = "";
			LAi_SetPlayerType(pchar);
			AddQuestRecord("FL3", "17");
			chr = CharacterFromID("JozephFushe");
			
			LAi_ActorFollowEverywhere(chr, "", -1);
			AddPassenger(pchar, chr, false);
			SetCharacterRemovable(chr, false);
			LAi_SetImmortal(chr, true);
			
			pchar.quest.FL3s52.win_condition.l1 = "EnterToSea";
			pchar.quest.FL3s52.win_condition = "FL3_s53";
		break;
		
		case "FL3_s53":
			Set_My_Cabin();
			pchar.quest.FL3s53.win_condition.l1 = "location";
			pchar.quest.FL3s53.win_condition.l1.location = Get_My_Cabin();
			pchar.quest.FL3s53.win_condition = "FL3_s55";
			DoQuestCheckDelay("FL3_s54", 1.0);
		break;

		case "FL3_s54":
			Sea_CabinStartNow();
		break;

		case "FL3_s55":
			chr = CharacterFromID("JozephFushe");
			PlaceCharacter(chr, "rld", "random_must_be_near");
			LAi_ActorDialog(chr, pchar, "FL3_s56", -1, 0);
		break;

		case "FL3_s56":
			chr = CharacterFromID("JozephFushe");
			chr.location = "none";
			AddQuestRecord("FL3", "18");

			switch(rand(2))
			{
				case 0: sStr = "Caracas"; break;
				case 1: sStr = "PortSpein"; break;
				case 2: sStr = "Villemstad"; break;
			}

			Log_Testinfo(""+sStr);

			pchar.MainQuest = "FL3_s56_"+sStr;

			pchar.quest.FL3s56.win_condition.l1 = "location";
			pchar.quest.FL3s56.win_condition.l1.location = sStr+"_shipyard";
			pchar.quest.FL3s56.win_condition = "FL3_s57";
		break;

		case "FL3_s57":
			chr = CharacterFromID("JozephFushe");
			PlaceCharacter(chr, "reload", "random_must_be_near");
			LAi_ActorFollow(chr, pchar, "", -1);
		break;

		case "FL3_s58":
			pchar.MainQuest = "";
			AddMoneyToCharacter(pchar, -20000);
			chr = CharacterFromID("JozephFushe");
			RemovePassenger(pchar, chr);
			
			// Фуше получает назад свой Меркурий ->
			chr.ship.type = GenerateShip(SHIP_FLEUT, 0);
			SetBaseShipData(chr);
			chr.Ship.Name = "Mercury";
			chr.Ship.Crew.Quantity = 0;
			DeleteAttribute(chr, "Ship.Cargo.Goods");
			
			SetGoodsInitNull(chr);
			chr.ship.hp = 300;
			chr.ship.sp = 30;
			chr.ship.dirt_hull = 65;

			SetCompanionIndex(pchar, -1, sti(chr.index));
			SetShipRemovable(chr, false);
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;
			// <- Фуше получает назад свой Меркурий

			LAi_SetImmortal(chr, false);

			// заводим проверку на смерть Фуше
			pchar.quest.FL3s58_death.win_condition.l1 = "npc_death";
			pchar.quest.FL3s58_death.win_condition.l1.character = "JozephFushe";
			pchar.quest.FL3s58_death.win_condition = "FL3_s58_fushe_dead";

			pchar.quest.FL3s58.win_condition.l1 = "ExitFromLocation";
            pchar.quest.FL3s58.win_condition.l1.location = pchar.location;
		    pchar.quest.FL3s58.win_condition = "FL3_s59";

			AddQuestRecord("FL3", "19");
			bDisableFastReload = true;
		break;

		case "FL3_s59":
			chrDisableReloadTolocation = true;
			chr = CharacterFromID("JozephFushe");
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL3_s60", -1, 0);
		break;

		case "FL3_s60":
			chr = CharacterFromID("JozephFushe");
			chr.location = "none";
			bDisableFastReload = false;
			chrDisableReloadTolocation = false;
			AddQuestRecord("FL3", "20");
			pchar.quest.FL3s60.win_condition.l1 = "location";
			pchar.quest.FL3s60.win_condition.l1.location = "Tortuga_town";
			pchar.quest.FL3s60.win_condition = "FL4_s1";
		break;

		case "FL3_s58_fushe_dead":
			AddQuestRecord("FL3", "21");
			SetQuestHeaderColor("FL3", gray);
			CloseQuestHeader("FL3");
			DeleteQuestCheck("FL3s60");
		break;

//====================================================================================================================
//	Разоблачение
//====================================================================================================================
		case "FL4_s1":
			chr = CharacterFromID("FL_ElizabetBrulua");
			chr.location = "none";

			DeleteQuestCheck("FL3s58_death");
			chr = CharacterFromID("JozephFushe");
			RemoveCharacterCompanion(pchar, chr);
			chrDisableReloadTolocation = true;
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL4_s2", -1, 0);
			chr.greeting = "fushe";
		break;

		case "FL4_s2":
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 1;
			AddQuestRecord("FL3", "22");
			chr = CharacterFromID("JozephFushe");
			LAi_ActorRunToLocation(chr, "reload", "houseF3", "none", "", "", "FL4_s3", -1);
		break;

		case "FL4_s3":
			chr = CharacterFromID("JozephFushe");
			chr.location.from_sea = "Tortuga_town";
			chrDisableReloadTolocation = false;
			SetTimerConditionParamHourEx("FL4s3", "FL4_s4", 0, 0, 1, 8);
		break;

		case "FL4_s4":
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, "Tortuga_town", "reload", "reload3_back");
			chr.talker = 10;
			LAi_SetStayType(chr);
		break;

		case "FL4_s5":	// приходит из диалога с Фуше
			ChangeCharacterAddressGroup(CharacterFromID("JozephFushe"), "Tortuga_townhall", "goto", "governor1");
			DoQuestReloadToLocation("Tortuga_townhall", "goto", "goto2", "FL4_s6");
		break;

		case "FL4_s6":
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "sit", "sit1");
			chr = CharacterFromID("JozephFushe");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "sit", "sit1");

			StartQuestMovie(false, false, true);
			locCameraToPos(-1,5,-2,0);
			pchar.camera = "lock";
			pchar.name = "Губернатор де Пуансе";
			pchar.lastname = "и капитан Фуше";
			DoQuestCheckDelay("FL4_s7", 0.5);
		break;

		case "FL4_s7":
			pchar.dialog.currentnode = "FL4_s1";
			LAi_ActorSelfDialog(pchar, "");
		break;

		case "FL4_s7a":
			pchar.name = "Жак Непве";
			pchar.lastname = "де Пуансе";

			pchar.dialog.currentnode = "FL4_5c";
			LAi_ActorSelfDialog(pchar, "FL4_s8");
		break;

		case "FL4_s7b":
			pchar.name = "Жак Непве";
			pchar.lastname = "де Пуансе";

			pchar.dialog.currentnode = "FL4_10";
			LAi_ActorSelfDialog(pchar, "FL4_s8");
		break;

		// общий для 2-х
		case "FL4_s8":
			ChangeCharacterNationReputation(pchar, FRANCE, 5);

			chrDisableReloadTolocation = false;
			bDisableFastReload = true;

			pchar.name = "Мишель";
			pchar.lastname = "де Граммон";
			
			pchar.camera = "";
			locCameraFollow();
			EndQuestMovie();
			LAi_SetPlayerType(pchar);

			AddQuestRecord("FL3", "23");
			SetQuestHeaderColor("FL3", gray);
			CloseQuestHeader("FL3");

			pchar.quest.FL4s8.win_condition.l1 = "location";
			pchar.quest.FL4s8.win_condition.l1.location = "Tortuga_town";
			pchar.quest.FL4s8.win_condition = "FL4_s9";
		break;

		case "FL4_s9":
			chrDisableReloadTolocation = true;

			chr = GetCharacter(NPC_GenerateCharacter("FL_tmp_pir", "barmen_6", "man", "man", 1, FRANCE, 0, false));
			chr.dialog.filename = "Quest\FranceLine\pirate3.c";
			chr.greeting = "zdrastvuite_capitan";
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL4_s10", -1, 0);
		break;

		case "FL4_s10":
			StartQuestMovie(false, false, true);
			chr = CharacterFromID("FL_tmp_pir");
			LAi_ActorRunToLocation(chr, "reload", "houseF4", "none", "", "", "FL4_s11", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, chr, "", -1);
		break;

		case "FL4_s11":
			chrDisableReloadTolocation = false;
			bDisableFastReload = false;
			EndQuestMovie();
			DoQuestReloadToLocation("Tortuga_houseF4", "reload", "reload1", "FL4_s12");
		break;

		case "FL4_s12":
			for(i=1;i<3;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 0));
				LAi_SetSitType(chr);
				ChangeCharacterAddressGroup(chr, pchar.location, "sit", "sit"+i);
			}
			
			chr2 = &items[FindItem("shoofla")];
			chr2.model = "dubinka";
			chr2.groupID = BLADE_ITEM_TYPE;
			
			chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 0));
			chr.id = "FL_tmp_pir";
			FantomMakeCoolFighter(chr, 30, 99, 99, "shoofla", "", 1);
			LAi_SetActorType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto3");

			StartQuestMovie(false, false, true);
			locCameraToPos(-2.5,2,-2.8,0);

			LAi_ActorGoToLocator(pchar, "goto", "goto4", "FL4_s13", -1);
		break;

		case "FL4_s13":
			chr = CharacterFromID("FL_tmp_pir");
			LAi_ActorFollow(chr, pchar, "FL4_s14", -1);
		break;

		case "FL4_s14":
			LAi_ActorAttack(CharacterFromID("FL_tmp_pir"), pchar, "");
			DoQuestCheckDelay("FL4_s15", 1.5);
		break;

		case "FL4_s15":
			EndQuestMovie();
			//LAi_Fade("FL4_s16", "");

			SetLaunchFrameFormParam("Через некоторое время...", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("Hold", "rld", "loc1", "FL4_s17");
			LaunchFrameForm();

			// если вдруг был экипирован мушкетом
			pchar.model = items[FindItem(pchar.model.clothes)].model;
			pchar.model.animation = "man";

			SetCurrentTime(22,12);
		break;

		case "FL4_s17":
			chr2 = &items[FindItem("shoofla")];
			chr2.model = "shoofla";
			chr2.groupID = GUN_ITEM_TYPE;
						
			pchar.MainQuest.hold_items = "";
			makearef(arTo, pchar.MainQuest.hold_items);
			makearef(arFrom, pchar.items);
			CopyAttributes(arTo, arFrom);
			DeleteAttribute(pchar, "items");
			pchar.items = "";
			
			LAi_SetGroundSitType(pchar);
			
			chr = GetCharacter(NPC_GenerateCharacter("FL_nikolas", "nikolas", "man", "man_B", sti(pchar.rank), FRANCE, -1, false));
			chr.name = "Николас";
			chr.lastname = "Ван Хоорн";
			chr.greeting = "";
			chr.dialog.filename = "Quest\FranceLine\Nikolas.c";
			LAi_SetGroundSitType(chr);
			ChangeCharacterAddressGroup(chr, "Hold", "rld", "aloc1");
			DoQuestCheckDelay("FL4_s18", 2.0);
		break;

		case "FL4_s18":
			DialogMain(CharacterFromID("FL_nikolas"), false);
		break;

		case "FL4_s19":
			GiveItem2Character(pchar, "blade10");
			EquipCharacterByItem(pchar, "blade10");
			LAi_Fade("FL4_s20", "FL4_s21");
		break;

		case "FL4_s20":
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(CharacterFromID("FL_nikolas"));
		break;

		case "FL4_s21":
			LAi_ActorDialog(CharacterFromID("FL_nikolas"), pchar, "FL4_s22", -1, 0);
		break;

		case "FL4_s22":
			DoQuestReloadToLocation("Ship_deck_Medium", "goto", "goto4", "FL4_s23");
		break;

		case "FL4_s23":
			chr = GetCharacter(NPC_GenerateCharacter("FL_tmp_pirate0", "pirate_1", "man", "man", 1, PIRATE, 0, false));
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 20, 20, "blade18", "gun14", 0);
			chr.SaveItemsForDead = true;
			TakeNItems(chr, "potion1", 5);
			TakeNItems(chr, "bullet", 5);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto10");
			LAi_SetWarriorType(chr);
			LAi_warrior_SetStay(chr, true);

			LAi_group_Register("FL_EnemyGroup");
			LAi_group_SetLookRadius("FL_EnemyGroup", 5.0);
            LAi_group_SetHearRadius("FL_EnemyGroup", 5.0);
            LAi_group_SetSayRadius("FL_EnemyGroup", 5.0);
			LAi_group_MoveCharacter(chr, "FL_EnemyGroup");
			LAi_group_SetRelation("FL_EnemyGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheck("FL_EnemyGroup", "FL4_s24");
		break;

		case "FL4_s24":
			Delay_DeleteGroup("FL_EnemyGroup");
			DoQuestCheckDelay("FL4_s25", 10.0);
		break;

		case "FL4_s25":
			for(i=0; i<3;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, "man", 0));
				ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_warrior_SetStay(chr, true);
				LAi_group_MoveCharacter(chr, "FL_EnemyGroup2");
			}

			LAi_group_SetRelation("FL_EnemyGroup2", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyGroup2", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("FL_EnemyGroup2", "FL4_s26");
		break;

		case "FL4_s26":
			LAi_group_SetRelation("FL_EnemyGroup2", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_LocationFantomsGen(&locations[FindLocation(pchar.location)], true);
			for(i=0; i<6;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, "man", 0));
				FantomMakeCoolFighter(chr, 30, 99, 99, "", "", 100.0);
				ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_warrior_SetStay(chr, true);
				LAi_group_MoveCharacter(chr, "FL_EnemyGroup3");
				LAi_CharacterReincarnation(chr, true, true);
				LAi_CharacterDisableDialog(chr);
			}

			LAi_group_SetRelation("FL_EnemyGroup3", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyGroup3", LAI_GROUP_PLAYER, true);

			LAi_SetCheckMinHP(pchar, 5.0, true, "FL4_s27");
		break;
		
		case "FL4_s27":
			LAi_group_SetRelation("FL_EnemyGroup3", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_SetFightMode(pchar, false);
			
			ChangeCharacterAddressGroup(pchar, pchar.location, "goto", "goto1");
			LAi_Fade("FL4_s28", "");
		break;

		case "FL4_s28":
			chr = GetCharacter(NPC_GeneratePhantomCharacter("pofficer", PIRATE, MAN, 0));
			chr.id = "FL_tmp_captain";
			FantomMakeCoolFighter(chr, 30, 1, 99, "blade1", "gun314", 0);
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1");
			LAi_SetStayType(chr);
			GiveItem2Character(chr, "FQ_letter4");
			chr.dialog.filename = "Quest\FranceLine\pirate4.c";
			chr.SuperShooter = true;

			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, chr, "FL4_s29", 0);

			chr = CharacterFromID("FL_nikolas");
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto4");
			LAi_SetStayType(chr);

			chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 0));
			chr.id = "FL_tmp_sailor1";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto2");
			LAi_SetStayType(chr);

			LAi_LocationFantomsGen(&locations[FindLocation(pchar.location)], false);
			LAi_RemoveCheckMinHP(pchar);
			LAi_SetImmortal(pchar, false);
		break;

		case "FL4_s29":
			DoQuestCheckDelay("FL4_s29a", 0.5);
		break;

		case "FL4_s29a":
			LAi_ActorDialogNow(pchar, CharacterFromID("FL_nikolas"), "FL4_s30", 0);
		break;

		case "FL4_s30":
			LAi_ActorTurnToLocator(pchar, "reload", "reload2");
			DoQuestCheckDelay("FL4_s31", 1.0);
		break;

		case "FL4_s31":
			pchar.name = "Один из матросов";
			pchar.lastname = "и капитан корабля";
			pchar.dialog.currentnode = "FL4_13";
			LAi_ActorSelfDialog(pchar, "FL4_s32");
		break;

		case "FL4_s32":
			pchar.name = "Мишель";
			pchar.lastname = "де Граммон";

			chr = CharacterFromID("FL_tmp_captain");
			chr2 = CharacterFromID("FL_tmp_sailor1");
			LAi_SetCurHP(chr2, 2.0);
			
			LAi_SetWarriorTypeNoGroup(chr);
			LAi_group_MoveCharacter(chr, "FL_gr1");

			LAi_SetWarriorTypeNoGroup(chr2);
			LAi_group_MoveCharacter(chr2, "FL_gr2");
						
			LAi_group_SetRelation("FL_gr1", "FL_gr2", LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_gr1", "FL_gr2", true);
			LAi_group_SetCheck("FL_gr2", "FL4_s33");
		break;

		case "FL4_s33":
			LAi_SetCurHP(CharacterFromID("FL_tmp_captain"), 2.0);
			LAi_group_SetRelation("FL_gr1", "FL_EnemyGroup3", LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_gr1", "FL_EnemyGroup3", true);
			LAi_group_SetCheck("FL_gr1", "FL4_s34");
		break;

		case "FL4_s34":
			LAi_SetActorType(CharacterFromID("FL_nikolas"));

			SetQuestHeader("FL4");
			SetQuestHeaderColor("FL4", yellow);

			LAi_SetPlayerType(pchar);
			chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 0));
			chr.id = "FL_tmp_sailor2";
			chr.dialog.filename = "Quest\FranceLine\pirate5.c";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto5");
			LAi_SetActorType(chr);
			LAi_ActorDialogNow(chr, pchar, "FL4_s35", 0);
		break;
		
		case "FL4_s35":
			AddQuestRecord("FL4", "2");
			pchar.MainQuest = "FL4_s35";
		break;

		case "FL4_s36":
			if(CheckCharacterItem(pchar, "FQ_letter4")) bOk = true;
			
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
            RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);

			makearef(arFrom, pchar.MainQuest.hold_items);
			makearef(arTo, pchar.items);
			CopyAttributes(arTo, arFrom);
			DeleteAttribute(pchar, "MainQuest.hold_items");
			if(bOk) pchar.items.FQ_letter4 = 1;
			pchar.MainQuest = "";

			AddTimeToCurrent(4,11);
			SetLaunchFrameFormParam("Через несколько часов Николас прибежал в каюту"+NewStr()+"и сообщил, что к нам приближается корабль."+NewStr()+"Мы выскочили на палубу"+NewStr()+"и приготовились к абордажу...", "Reload_To_Location", 2.0, 6.0);
			SetLaunchFrameReloadLocationParam("BOARDING_DECK", "rld", "loc8", "FL4_s37");
			LaunchFrameForm();
		break;

		case "FL4_s37":
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "rld", "aloc8");

			ChangeCharacterAddressGroup(CharacterFromID("FL_nikolas"), pchar.location, "goto", "goto4");
			
			chr = CharacterFromID("FL_granie");
			chr.model.animation = "man";
			ChangeCharacterAddressGroup(chr, pchar.location, "rld", "loc10");
			LAi_SetActorType(chr);
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL4_s38", -1, 0);

			for(i=0;i<3;i++)
			{
				chr2 = GetOurSailor("FL_sailor"+i);
				ChangeCharacterAddressGroup(chr2, pchar.location, "rld", "loc10");
				LAi_SetActorType(chr2);
				LAi_ActorFollow(chr2, chr, "", -1);
			}
		break;

		case "FL4_s38":
			chr = CharacterFromID("FL_nikolas");
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL4_s39", 2.0, 0);
		break;

		case "FL4_s39":
			EndQuestMovie();
			AddTimeToCurrent(8,45);
			DoQuestCheckDelay("FL4_s40", 0.5);
		break;

		case "FL4_s40":
			LAi_SetPlayerType(pchar);
			ChangeCharacterAddressGroup(CharacterFromID("FL_granie"), "none", "", "");
			ChangeCharacterAddressGroup(CharacterFromID("FL_nikolas"), "none", "", "");
			SetLaunchFrameFormParam("Вечером того же дня"+NewStr()+"мы бросили якорь в порту Тортуги...", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("Tortuga_town", "reload", "reload1", "FL4_s41");
			LaunchFrameForm();
		break;

		case "FL4_s41":
			chrDisableReloadTolocation = true;
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, "Tortuga_town", "quest", "quest1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL4_s42", -1, 0);
		break;

		case "FL4_s42":
			LAi_ActorRunToLocation(CharacterFromID("JozephFushe"), "reload", "houseF3", "Tortuga_houseF3", "barmen", "stay", "FL4_s43", -1);
		break;

		case "FL4_s43":
			LAi_SetBarmanType(CharacterFromID("JozephFushe"));
			chrDisableReloadTolocation = false;
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
			AddQuestRecord("FL4", "3");
		break;

		case "FL4_s44":
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 1;
			DoReloadCharacterToLocation("Tortuga_town", "reload", "houseF3");
			SetTimerConditionParamEx("FL4s44", "FL4_s45", 0, 0, 1);
			AddQuestRecord("FL4", "4");
		break;

		case "FL4_s45":
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
			chr = CharacterFromID("FL_ElizabetBrulua");
			ChangeCharacterAddressGroup(chr, "Tortuga_houseF3", "barmen", "stay");
			LAi_SetBarmanType(chr);
			chr.dialog.currentnode = "7";

			ChangeCharacterAddressGroup(CharacterFromID("JozephFushe"), "none", "", "");
		break;

		case "FL4_s46":
			chrDisableReloadTolocation = false;
			bDisableFastReload = true;
			AddQuestRecord("FL4", "5");
			
			pchar.quest.FL4s46.win_condition.l1 = "ExitFromLocation";
            pchar.quest.FL4s46.win_condition.l1.location = pchar.location;
		    pchar.quest.FL4s46.win_condition = "FL4_s47";
		break;

		case "FL4_s47":
			Pchar.GenQuest.Hunter2Pause = true;
			TakeItemFromCharacter(pchar, "FQ_letter5");
			chrDisableReloadTolocation = true;
			bDisableFastReload = false;

			chr = CharacterFromID("FL_nikolas");
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL4_s48", -1, 0);
		break;

		case "FL4_s48":
			chrDisableReloadTolocation = false;
			characters[GetCharacterIndex("FL_nikolas")].location = "none";
			characters[GetCharacterIndex("FL_nikolas")].greeting = "VanHoorn";
			AddQuestRecord("FL4", "6");
			
			pchar.quest.FL4s48.win_condition.l1 = "location";
			pchar.quest.FL4s48.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FL4s48.win_condition = "FL4_s49";
		break;

		case "FL4_s49":
			AddQuestRecord("FL4", "7");
			pchar.MainQuest = "FL4_s49";
		break;

		case "FL4_s50":
			if(CheckAttribute(pchar, "MainQuest.FL4_s49.tavern") && CheckAttribute(pchar, "MainQuest.FL4_s49.store") && CheckAttribute(pchar, "MainQuest.FL4_s49.shipyard"))
			{
				pchar.MainQuest = "";
				DeleteAttribute(pchar, "MainQuest.FL4_s49");

				AddQuestRecord("FL4", "8");
				bDisableFastReload = true;
				Pchar.GenQuest.Hunter2Pause = true;

				pchar.quest.FL4s50.win_condition.l1 = "ExitFromLocation";
				pchar.quest.FL4s50.win_condition.l1.location = pchar.location;
				pchar.quest.FL4s50.win_condition = "FL4_s51";
			}
		break;

		case "FL4_s51":
			chrDisableReloadTolocation = true;
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", FRANCE, MAN, 0));
			chr.dialog.filename = "Quest\FranceLine\officer1.c";
			chr.greeting = "frc_sold";
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL4_s52", -1, 0);

			for(i=0;i<2;i++)
			{
				chr2 = GetCharacter(NPC_GeneratePhantomCharacter("soldier", FRANCE, MAN, 0));
				ChangeCharacterAddressGroup(chr2, chr.location, "goto", chr.location.locator);
				LAi_SetActorType(chr2);
				LAi_ActorFollow(chr2, chr, "", -1);
			}
		break;

		case "FL4_s52":
			DoQuestReloadToLocation("FortFrance_fort", "goto", "goto23", "FL4_s53");
		break;

		case "FL4_s53":
			chrDisableReloadTolocation = false;
			bDisableFastReload = false;
			chr = GetCharacter(NPC_GenerateCharacter("FL_JerarDePuanie", "Offic_fra", "man", "man_B", 1, FRANCE, -1, false));
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 50, 50, "", "", 200.0);
			chr.name = "Жерар";
			chr.lastname = "де Пуанье";
			chr.dialog.filename = "Quest\FranceLine\JerarDePuanie.c";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto43");
			LAi_SetActorType(chr);
			LAi_ActorDialogNow(chr, pchar, "FL4_s54", 0);
		break;

		case "FL4_s54":
			characters[GetCharacterIndex("FL_JerarDePuanie")].location = "none";
			AddQuestRecord("FL4", "9");

			locations[FindLocation("FortFrance_town")].reload.l16.label = "Polkovnik_house";
			locations[FindLocation("FortFrance_town")].reload.l16.disable = 1;
			locations[FindLocation("FortFrance_houseS1")].id.label = "Polkovnik_house";

			pchar.quest.FL4s54.win_condition.l1 = "location";
			pchar.quest.FL4s54.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FL4s54.win_condition = "FL4_s55";
		break;

		case "FL4_s55":
			chrDisableReloadTolocation = true;
			Pchar.GenQuest.Hunter2Pause = true;
			chr = CharacterFromID("FL_granie");
			chr.dialog.currentnode = "51";
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL4_s56", -1, 0);
		break;

		case "FL4_s56":
			chrDisableReloadTolocation = false;
			characters[GetCharacterIndex("FL_granie")].location = "none";
			
			pchar.quest.FL4s56.win_condition.l1 = "locator";
			pchar.quest.FL4s56.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FL4s56.win_condition.l1.locator_group = "reload";
			pchar.quest.FL4s56.win_condition.l1.locator = "houseS1";
			pchar.quest.FL4s56.win_condition = "FL4_s57";
		break;

		case "FL4_s57":
			if(GetTime() > 21 || GetTime() < 6)
			{
				chrDisableReloadTolocation = true;
				chr = GetCharacter(NPC_GenerateCharacter("FL_tmp_killer1", "officer_7", "man", "man", 1, PIRATE, 0, false));
				FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 50, 99, "", "gun13", 100.0);
				chr.SuperShooter = true;
				ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto19");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");

				chr = GetCharacter(NPC_GenerateCharacter("FL_tmp_killer2", "officer_17", "man", "man", 1, PIRATE, 0, false));
				FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 50, 99, "", "gun13", 100.0);
				chr.SuperShooter = true;
				ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto20");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");

				LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("FL_EnemyFight", "FL4_s58");
				PlayStereoSound("people fight\rifle_fire1.wav");
			}
			else
			{
				pchar.quest.FL4s57.win_condition.l1 = "ExitFromLocation";
				pchar.quest.FL4s57.win_condition.l1.location = pchar.location;
				pchar.quest.FL4s57.win_condition = "FL4_s57a";
			}
		break;

		case "FL4_s57a":
			sStr = "FL4s57a";
			pchar.quest.(sStr).win_condition.l1 = "locator";
			pchar.quest.(sStr).win_condition.l1.location = "FortFrance_town";
			pchar.quest.(sStr).win_condition.l1.locator_group = "reload";
			pchar.quest.(sStr).win_condition.l1.locator = "houseS1";
			pchar.quest.(sStr).win_condition = "FL4_s57";
		break;

		case "FL4_s58":
			Delay_DeleteGroup("FL_EnemyFight");
			AddQuestRecord("FL4", "10");
			chr = CharacterFromID("FL_JerarDePuanie");
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "houseS1");
			LAi_SetStayType(chr);
			chr.talker = 10;
		break;

		case "FL4_s59":
			chr = CharacterFromID("FL_JerarDePuanie");
			chr.greeting = "DePuanie";
			ChangeCharacterAddressGroup(chr, "FortFrance_houseS1_room", "goto", "goto5");
			DoQuestReloadToLocation("FortFrance_houseS1_room", "goto", "goto4", "FL4_s60");
		break;

		case "FL4_s60":
			chr = CharacterFromID("FL_JerarDePuanie");
			LAi_SetActorType(chr);
			LAi_ActorDialogNow(chr, pchar, "FL4_s61", 0);
		break;

		case "FL4_s61":
			DoQuestCheckDelay("FL4_s62", 0.5);
		break;

		case "FL4_s62":
			AddTimeToCurrent(2,7);
			SetLaunchFrameFormParam("За повествованием моей истории"+NewStr()+"прошло около 2х часов...", "FL4_s63", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL4_s63":
			LAi_ActorDialogNow(CharacterFromID("FL_JerarDePuanie"), pchar, "FL4_s64", 0);
		break;

		case "FL4_s64":
			locations[FindLocation("FortFrance_town")].reload.l16.disable = 0;
			chrDisableReloadTolocation = false;
			LAi_SetStayType(CharacterFromID("FL_JerarDePuanie"));
			AddQuestRecord("FL4", "11");
			for(i=1;i<3;i++)
			{
				chr = GetCharacter(NPC_GenerateCharacter("FL4_1stMate"+i, "off_fra_"+i, "man", "man", 5, FRANCE, -1, true));
				__DEPRECATED_SetOfficerParam(chr, 5); // 1-й помощник
				chr.description = "Один из офицеров, которых дал мне полковник де Пуанье.";
				chr.quest_character = true;
				AddPassenger(pchar, chr, false);
			}
			DoReloadCharacterToLocation("FortFrance_town", "reload", "houseS1");
		break;

		case "FL4_s65":
			locations[FindLocation("FortFrance_town")].reload.l16.disable = 1;
			DoReloadCharacterToLocation("FortFrance_town", "reload", "houseS1");

			RemoveCharacterCompanion(pchar, CharacterFromID("FL4_1stMate1"));
			RemoveCharacterCompanion(pchar, CharacterFromID("FL4_1stMate2"));

			AddCharacterExpToSkill(pchar, "Sailing", 100);
			ChangeCharacterNationReputation(pchar, FRANCE, 5);

			AddQuestRecord("FL4", "12");
			chr = CharacterFromID("FL_nikolas");
			ChangeCharacterAddressGroup(chr, "Tortuga_tavern", "goto", "goto1");
			LAi_SetStayType(chr);
		break;

		case "FL4_s66":
			locations[FindLocation("FortFrance_town")].reload.l16.disable = 0;

			chr = CharacterFromID("FL_nikolas");
			FantomMakeCoolSailor(chr, SHIP_FLEUT_H, "Avignon", CANNON_TYPE_CANNON_LBS12, 50, 44, 46);
			FantomMakeCoolFighter(chr, sti(pchar.rank), 30, 30, "", "", 0);
			
			SetCompanionIndex(pchar, -1, sti(chr.index));
			SetShipRemovable(chr, false);
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;
			
			chrDisableReloadTolocation = true;
			LAi_SetActorType(chr);
			LAi_ActorRunToLocation(chr, "reload", "reload1_back", "none", "", "", "FL4_s67", -1);
		break;

		case "FL4_s67":
			chrDisableReloadTolocation = false;

			pchar.quest.FL4s67.win_condition.l1 = "location";
			pchar.quest.FL4s67.win_condition.l1.location = "FortFrance_houseS1_room";
			pchar.quest.FL4s67.win_condition = "FL4_s68";
		break;

		case "FL4_s68":
			if(GetCompanionNumber(pchar, GetCharacterIndex("FL_nikolas")) != -1)
			{
				chr = CharacterFromID("FL_nikolas");
				ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto4");
				LAi_SetActorType(chr);
				LAi_ActorTurnToLocator(chr, "goto", "goto5");

				LAi_SetActorType(pchar);
				LAi_ActorDialog(pchar, CharacterFromID("FL_JerarDePuanie"), "FL4_s69", -1, 0);

			}
		break;

		case "FL4_s69":
			DoQuestCheckDelay("FL4_s70", 0.5);
		break;

		case "FL4_s70":
			pchar.dialog.currentnode = "FL4_15";
			pchar.name = "Полковник";
			pchar.lastname = "и Николас";
			LAi_ActorSelfDialog(pchar, "FL4_s71");
		break;

		case "FL4_s71":
			chr = CharacterFromID("FL_nikolas");
			RemoveCharacterCompanion(pchar, chr);
			LAi_ActorGoToLocation(chr, "reload", "reload1", "none", "", "", "FL4_s72", -1);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
		break;

		case "FL4_s72":
			pchar.name = "Мишель";
			pchar.lastname = "де Граммон";
			LAi_ActorDialogNow(pchar, CharacterFromID("FL_JerarDePuanie"), "FL4_s73", 0);
		break;

		case "FL4_s73":
			DoQuestCheckDelay("FL4_s74", 0.5);
		break;

		case "FL4_s74":
			AddTimeToCurrent(1,53);
			SetLaunchFrameFormParam("Прошло около 2х часов...", "FL4_s75", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL4_s75":
			LAi_ActorDialog(pchar, CharacterFromID("FL_JerarDePuanie"), "FL4_s76", -1, 0);
		break;

		case "FL4_s76":
			LAi_SetPlayerType(pchar);

			locations[FindLocation("FortFrance_town")].reload.l16.disable = 1;
			DoReloadCharacterToLocation("FortFrance_town", "reload", "houseS1");

			AddQuestRecord("FL4", "13");
			
			chr = GetCharacter(NPC_GenerateCharacter("FL_LoranDeGraff", "deGraff", "man", "man_B", 1, FRANCE, -1, false));
			FantomMakeCoolFighter(chr, sti(pchar.rank), 41, 47, "", "", 0.0);
			FantomMakeCoolSailor(chr, SHIP_CORVETTE_H, "Caen", CANNON_TYPE_CANNON_LBS12, 56, 47, 52);
			chr.name = "Лоран";
			chr.lastname = "де Графф";

			SetCompanionIndex(pchar, -1, sti(chr.index));
			SetShipRemovable(chr, false);
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;

			pchar.quest.FL4s76.win_condition.l1 = "location";
			pchar.quest.FL4s76.win_condition.l1.location = "Guadeloupe";
			pchar.quest.FL4s76.win_condition = "FL4_s77";
			
			// таймер на провал по времени
			SetTimerConditionParamEx("FL4s76a", "FL4_s77_failed", 0, 0, 3);	
			
			// смерть Лорана де Граффа
			pchar.quest.FL4s76b.win_condition.l1 = "npc_death";
			pchar.quest.FL4s76b.win_condition.l1.character = "FL_LoranDeGraff";
			pchar.quest.FL4s76b.win_condition = "FL4_s77_failed2";
		break;

		// провал по времени - Ван Хоорн мёртв
		case "FL4_s77_failed":
			AddQuestRecord("FL4", "14");
			SetQuestHeaderColor("FL4", gray);
			CloseQuestHeader("FL4");

			DeleteQuestCheck("FL4s76");
			DeleteQuestCheck("FL4s76b");

			i = GetCharacterIndex("FL_LoranDeGraff");
			if(i != -1) RemoveCharacterCompanion(pchar, &characters[i]);
			SetLifeDay(&characters[i], 0);
		break;
		
		// погиб Лоран де Графф
		case "FL4_s77_failed2":
			AddQuestRecord("FL4", "15");
			SetQuestHeaderColor("FL4", gray);
			CloseQuestHeader("FL4");

			DeleteQuestCheck("FL4s76");
			DeleteQuestCheck("FL4s76a");
		break;

		// пока все живы и все ОК, вышли в море возле Гваделупы
		case "FL4_s77":
			DeleteQuestCheck("FL4s76a");
			DeleteQuestCheck("FL4s76b");
			
			chr = CharacterFromID("FL_LoranDeGraff");
			SetCharacterPerk(chr, "IronWill");
			SetCharacterPerk(chr, "ShipEscape");
			chr.quest_character = true;
			chr.boat = true;
			
			bQuestDisableMapEnter = true;
            Island_SetReloadEnableGlobal("Guadeloupe", false);

			chr = CharacterFromID("FL_nikolas");
			chr.ShipEnemyDisable = true;
			LAi_SetImmortal(chr, true);

			Group_FindOrCreateGroup("FL_HoornSeaGroup");
			Group_SetType("FL_HoornSeaGroup", "war");
			Group_AddCharacter("FL_HoornSeaGroup", "FL_nikolas");
						
			// Французы, крепятся к Ван Хоорну
			for(i=1;i<8;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", FRANCE, MAN, -1));
				chr.id = "FL_HoornCaravan_"+i;
				chr.ShipEnemyDisable = true;
			}

			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravan_1"), SHIP_CARAVEL, "Etincelle", CANNON_TYPE_CANNON_LBS6, 30, 30, 30);
			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravan_2"), SHIP_XEBEC, "Le Gitan", CANNON_TYPE_CANNON_LBS9, 30, 30, 30);
			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravan_3"), SHIP_SCHOONER, "Gaulois", CANNON_TYPE_CANNON_LBS6, 30, 30, 30);
			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravan_4"), SHIP_BARQUE, "La Vierge", CANNON_TYPE_CANNON_LBS9, 30, 30, 30);
			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravan_5"), SHIP_SCHOONER_L, "Papillon", CANNON_TYPE_CANNON_LBS6, 30, 30, 30);
			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravan_6"), SHIP_BARQUE_L, "Vague", CANNON_TYPE_CANNON_LBS9, 30, 30, 30);
			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravan_7"), SHIP_SCHOONER, "Romarin", CANNON_TYPE_CANNON_LBS6, 30, 30, 30);
			
			for(i=1;i<8;i++) Group_AddCharacter("FL_HoornSeaGroup", "FL_HoornCaravan_"+i);
			
			Group_SetGroupCommander("FL_HoornSeaGroup", "FL_nikolas");
			//Group_SetTaskAttack("FL_HoornSeaGroup", "FL_SpainSeaGroup");
			Group_SetAddress("FL_HoornSeaGroup", "Guadeloupe", "Quest_ships", "quest_ship_5");
			Group_LockTask("FL_HoornSeaGroup");
			
			// Испанцы
			Group_FindOrCreateGroup("FL_SpainSeaGroup");
			Group_SetType("FL_SpainSeaGroup", "war");
			
			for(i=1;i<7;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
				chr.id = "FL_HoornCaravanEnemy_"+i;
				chr.AlwaysEnemy = true;
			}

			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravanEnemy_1"), SHIP_GALEON_H, "Pulpo", CANNON_TYPE_CANNON_LBS6, 60, 55, 50);
			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravanEnemy_2"), SHIP_CORVETTE, "Salvaje Perro", CANNON_TYPE_CANNON_LBS9, 55, 50, 50);
			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravanEnemy_3"), SHIP_BRIG_H, "Fulminante", CANNON_TYPE_CANNON_LBS6, 45, 45, 45);
			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravanEnemy_4"), SHIP_SCHOONER, "Rayo", CANNON_TYPE_CANNON_LBS9, 40, 40, 40);
			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravanEnemy_5"), SHIP_SCHOONER_L, "El Salvador", CANNON_TYPE_CANNON_LBS6, 40, 40, 40);
			FantomMakeCoolSailor(CharacterFromID("FL_HoornCaravanEnemy_6"), SHIP_PINNACE_H, "Serpiente", CANNON_TYPE_CANNON_LBS12, 55, 55, 55);

			for(i=1;i<6;i++) Group_AddCharacter("FL_SpainSeaGroup", "FL_HoornCaravanEnemy_"+i);
			
			Group_SetGroupCommander("FL_SpainSeaGroup", "FL_HoornCaravanEnemy_1");
			Group_SetPursuitGroup("FL_SpainSeaGroup", "FL_HoornSeaGroup");
			Group_SetAddress("FL_SpainSeaGroup", "Guadeloupe", "", "");
			Group_SetTaskAttack("FL_SpainSeaGroup", "FL_HoornSeaGroup");
			Group_LockTask("FL_SpainSeaGroup");
			
			pchar.quest.FL4s77.win_condition.l1 = "Group_Death";
			pchar.quest.FL4s77.win_condition.l1.group = "FL_SpainSeaGroup";
			pchar.quest.FL4s77.win_condition = "FL4_s78";
		break;

		case "FL4_s78":
			for(i=1;i<8;i++) SetLifeDay(CharacterFromID("FL_HoornCaravan_"+i),0);
			
			bQuestDisableMapEnter = false;
            Island_SetReloadEnableGlobal("Guadeloupe", true);
			
			AddQuestRecord("FL4", "16");
			locations[FindLocation("FortFrance_town")].reload.l16.disable = 0;

			Group_SetAddressNone("FL_HoornSeaGroup");
		break;

		case "FL4_s79_failed":
			AddQuestRecord("FL4", "17");
			SetQuestHeaderColor("FL4", gray);
			CloseQuestHeader("FL4");
			chr = CharacterFromID("FL_JerarDePuanie");
			LAi_CharacterDisableDialog(chr);
			SetLifeDay(chr, 0);
		break;

		case "FL4_s79":
			chr = CharacterFromID("FL_LoranDeGraff");
			RemoveCharacterCompanion(pchar, chr);
			RemovePassenger(pchar, chr);
			DoQuestReloadToLocation("FortFrance_town", "reload", "houseS1", "FL4_s80");
		break;

		case "FL4_s80":
			chrDisableReloadTolocation = true;
			locations[FindLocation("FortFrance_town")].reload.l16.disable = 1;
			
			AddMoneyToCharacter(pchar, 20000);
			AddCharacterExpToSkill(pchar, "LeaderShip", 500);
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			OfficersReaction("good");
			
			Items[sti(pchar.EquipedPatentId)].TitulCur = 2;
        	Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;

			characters[GetCharacterIndex("PortPax_Mayor")].location = "none";
			GiveItem2Character(pchar, "clothes35");

			chr = CharacterFromID("FL_nikolas");
			chr.dialog.currentnode = "31";
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL4_s81", -1, 0);
		break;

		case "FL4_s81":
			chrDisableReloadTolocation = false;
			AddMoneyToCharacter(pchar, -7500);
			characters[GetCharacterIndex("FL_nikolas")].location = "none";
			AddQuestRecord("FL4", "18");
			SetQuestHeaderColor("FL4", gray);
			CloseQuestHeader("FL4");

			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
			chr = CharacterFromID("FL_ElizabetBrulua");
			ChangeCharacterAddressGroup(chr, "none", "", "");
			
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, "Tortuga_houseF3", "barmen", "stay");
			LAi_SetBarmanType(chr);
		break;

//====================================================================================================================
//	Поход на Кюрасао
//====================================================================================================================
		case "FL5_s1":
			SetNationRelationBoth(HOLLAND, FRANCE, RELATION_ENEMY);
			SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(sti(pchar.nation), HOLLAND));

			DoQuestReloadToLocation("tortuga_town", "reload", "houseF3", "FL5_s2");
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 1;
		break;

		case "FL5_s2":
			SetQuestHeader("FL5");
			SetQuestHeaderColor("FL5", yellow);
			AddQuestRecord("FL5", "1");

			SetTimerConditionParamEx("FL5s2failed", "FL5_s2_failed", 0, 0, 1);
			
			pchar.quest.FL5s2.win_condition.l1 = "location";
			pchar.quest.FL5s2.win_condition.l1.location = "Tortuga_townhall";
			pchar.quest.FL5s2.win_condition = "FL5_s3";
		break;

		case "FL5_s2_failed":
			DeleteQuestCheck("FL5s2");
			AddQuestRecord("FL5", "2");
			SetQuestHeaderColor("FL5", gray);
			CloseQuestHeader("FL5");
		break;

		case "FL5_s3":
			DeleteQuestCheck("FL5s2failed");

			chr = GetCharacter(NPC_GenerateCharacter("FL_DeStre", "bankir_fr", "man", "man_B", 1, FRANCE, -1, false));
			FantomMakeCoolFighter(chr, sti(pchar.rank), 30, 30, "", "", 0.0);
			chr.name = "Жан";
			chr.lastname = "д'Эстре";
			chr.dialog.filename = "Quest\FranceLine\dEstre.c";
			chr.greeting = "are_you_pirate";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto6");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto1");

			// французские корсары
			chr = GetCharacter(NPC_GenerateCharacter("FL_FrCapitan1", "sold_fra_3", "man", "man", 1, FRANCE, -1, false));
			FantomMakeCoolFighter(chr, sti(pchar.rank), 50, 50, "", "", 0.0);
			chr.name = "Феликс";
			chr.lastname = "Трейер";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto5");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto6");

			chr = GetCharacter(NPC_GenerateCharacter("FL_FrCapitan2", "officer_1", "man", "man", 1, FRANCE, -1, false));
			FantomMakeCoolFighter(chr, sti(pchar.rank), 50, 50, "", "", 0.0);
			chr.name = "Арнольд";
			chr.lastname = "Бональе";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto2");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto6");

			chr = GetCharacter(NPC_GenerateCharacter("FL_FrCapitan3", "sold_fra_1", "man", "man", 1, FRANCE, -1, false));
			FantomMakeCoolFighter(chr, sti(pchar.rank), 50, 50, "", "", 0.0);
			chr.name = "Андре";
			chr.lastname = "Баша";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto3");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto6");

			chr = GetCharacter(NPC_GenerateCharacter("FL_FrCapitan4", "officer_19", "man", "man", 1, FRANCE, -1, false));
			FantomMakeCoolFighter(chr, sti(pchar.rank), 50, 50, "", "", 0.0);
			chr.name = "Клод";
			chr.lastname = "Козье";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto4");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto6");
			
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "FL5_s4", -1);
		break;

		case "FL5_s4":
			LAi_ActorTurnToLocator(pchar, "goto", "goto6");
			DoQuestCheckDelay("FL5_s5", 2.0);
		break;

		case "FL5_s5":
			pchar.name = "Адмирал д'Эстре";
			pchar.lastname = "и один из капитанов";
			pchar.dialog.currentnode = "FL5_1";
			LAi_ActorSelfDialog(pchar, "FL5_s6");
		break;

		case "FL5_s6":
			pchar.name = "Мишель";
			pchar.lastname = "де Граммон";
			
			DoQuestCheckDelay("FL5_s6a", 0.5)
		break;
		
		case "FL5_s6a":
			chr = CharacterFromID("FL_DeStre");
			LAi_ActorWaitDialog(chr, pchar);
			LAi_ActorDialogNow(pchar, chr, "FL5_s7", 0);
		break;

		case "FL5_s7":
			LAi_SetActorType(CharacterFromID("FL_DeStre"));
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			LAi_Fade("FL5_s8", "");
			for(i=1;i<5;i++) ChangeCharacterAddressGroup(CharacterFromID("FL_FrCapitan"+i), "none", "", "");
		break;

		case "FL5_s8":
			AddQuestRecord("FL5", "3");

			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
		break;

		case "FL5_s9":
			DoQuestReloadToLocation("tortuga_town", "reload", "houseF3", "");
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 1;

			pchar.MainQuest = "FL5_s9";
			AddQuestRecord("FL5", "4");
		break;

		case "FL5_s10":
			pchar.MainQuest = "";
			AddMoneyToCharacter(pchar, -10000);

			chr = GetCharacter(NPC_GeneratePhantomCharacter("pofficer", FRANCE, MAN, -1));
			FantomMakeCoolSailor(chr, SHIP_LE_ARDI, "Le Ardi", CANNON_TYPE_CANNON_LBS18, 30, 29, 35);
			
			chr.Ship.Crew.Quantity = 0;
			DeleteAttribute(chr, "Ship.Cargo.Goods");
			SetGoodsInitNull(chr);

			SetCompanionIndex(pchar, -1, sti(chr.index));
			SetShipRemovable(chr, true);
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;

			Log_Info("В эскадру добавлен корабль Le Ardi");

			AddQuestRecord("FL5", "5");
			SetTimerConditionParamEx("FL5s10", "FL5_s11", 0, 1, 0);
		break;

		case "FL5_s11":
			pchar.quest.FL5s11.win_condition.l1 = "location";
			pchar.quest.FL5s11.win_condition.l1.location = "Tortuga_town";
			pchar.quest.FL5s11.win_condition = "FL5_s12";
		break;

		case "FL5_s12":
			chr = CharacterFromID("FL_DeStre");
			LAi_SetStayType(chr);
			ChangeCharacterAddressGroup(chr, "Tortuga_town", "goto", "goto11");
			
			for(i=1;i<5;i++) 
			{
				chr = CharacterFromID("FL_FrCapitan"+i);
				ChangeCharacterAddressGroup(chr, "Tortuga_town", "goto", "goto18");
				LAi_SetActorType(chr);
				if(i==1)
				{
					LAi_ActorFollow(chr,  CharacterFromID("FL_DeStre"), "", -1);
					chr2 = chr;
				}
				else
				{
					LAi_ActorFollow(chr, chr2, "", -1);
				}
			}
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, CharacterFromID("FL_DeStre"), "FL5_s13", -1, 0.5);
		break;

		case "FL5_s13":
			LAi_SetPlayerType(pchar);
			EndQuestMovie();
			ChangeCharacterAddressGroup(CharacterFromID("FL_DeStre"), "none", "", "");
			for(i=1;i<5;i++) ChangeCharacterAddressGroup(CharacterFromID("FL_FrCapitan"+i), "none", "", "");
			LAi_Fade("FL5_s14","");
		break;

		case "FL5_s14":
			pchar.quest.FL5s14.win_condition.l1 = "EnterToSea";
			pchar.quest.FL5s14.win_condition = "FL5_s15";
		break;

		case "FL5_s15":
			DoQuestCheckDelay("FL5_s16", 0.5);
		break;

		case "FL5_s16":
			PostVideoAndQuest("France\04", 100, "FL5_s17");
		break;

		case "FL5_s17":
			pchar.Always_Storm2 = true;
			AddDataToCurrent(0,0,20);
			SetLaunchFrameFormParam("Через 20 дней плавания...", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("Ship_deck", "goto", "goto5", "FL5_s18");
			LaunchFrameForm();
			pchar.loading_image = "loading\boat.tga";
		break;

		case "FL5_s18":
			chr = CharacterFromID("FL_DeStre");
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto6");
			LAi_SetStayType(chr);

			for(i=0;i<5;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("soldier", FRANCE, MAN, 0));
				PlaceCharacter(chr, "goto", "random");
			}

			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, CharacterFromID("FL_DeStre"), "FL5_s19", -1, 0.5);

			DeleteAttribute(&locations[FindLocation("Ship_deck")], "QuestlockWeather");
		break;

		case "FL5_s19":
			EndQuestMovie();
			pchar.loading_image = "";
			PostVideoAndQuest("France\05", 100, "FL5_s20");
		break;

		case "FL5_s20":
			LAi_SetPlayerType(pchar);
			pchar.location.from_sea = "Shore22";
			setCharacterShipLocation(pchar, "Shore22"));
		    setWDMPointXZ("Shore22");
			DoQuestReloadToLocation("Shore22", "reload", "sea", "FL5_s21");

			DisableEncGen("Shore22", true);
			Pchar.GenQuest.Hunter2Pause = true;
		break;

		case "FL5_s21":
			chrDisableReloadTolocation = true;
			ChangeCharacterAddressGroup(CharacterFromID("FL_DeStre"), "Shore22", "goto", "goto8");
			for(i=1;i<5;i++)
			{	
				chr = CharacterFromID("FL_FrCapitan"+i);
				PlaceCharacter(chr, "goto", "random_must_be");
				LAi_SetWarriorType(chr);
				chr.dialog.filename = "Quest\FranceLine\Captain1.c";
				chr.greeting = "mesie";
			}
			
			for(i=0;i<8;i++)
			{
				sStr = "pofficer";
				if(rand(1)) sStr = "soldier";
				chr = GetCharacter(NPC_GeneratePhantomCharacter(sStr, FRANCE, MAN, 0));
				chr.id = "FL_tmp_dead_cap"+1;
				PlaceCharacter(chr, "goto", "random_must_be_near");
				LAi_SetActorType(chr);
				LAi_ActorSetLayMode(chr);
			}
		break;
		
		case "FL5_s22":
			DeleteAttribute(pchar, "Always_Storm2");
			
			chr = CharacterFromID("JozephFushe");
			chr.location.from_sea = "shore22";
			
			FantomMakeCoolSailor(CharacterFromID("FL_FrCapitan1"), SHIP_FRIGATE_L, "Ascold", CANNON_TYPE_CANNON_LBS18, 70, 65, 65);
			FantomMakeCoolSailor(CharacterFromID("FL_FrCapitan2"), SHIP_CORVETTE, "Meduse", CANNON_TYPE_CANNON_LBS12, 70, 65, 65);
			FantomMakeCoolSailor(CharacterFromID("FL_FrCapitan3"), SHIP_BRIG_H, "Le Calme", CANNON_TYPE_CANNON_LBS12, 70, 65, 65);
			FantomMakeCoolSailor(CharacterFromID("FL_FrCapitan4"), SHIP_FRIGATE, "De la Reine", CANNON_TYPE_CANNON_LBS18, 70, 65, 65);

			chr = CharacterFromID("FL_DeStre");
			chr.location = "none";
			SetLifeDay(chr, 0);
			
			AddDataToCurrent(0,1,15);
			SetDayTime(DAY_TIME_MORNING);
			SetNextWeather("6 Hours");
			
			DeleteAttribute(&locations[FindLocation("shore22")], "QuestlockWeather");
			DoQuestCheckDelay("FL5_s22a", 0.1);
		break;

		case "FL5_s22a":
			SetLaunchFrameFormParam("На ремонт кораблей понадобилось"+NewStr()+"полтора месяца...", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("shore22", "goto", "goto8", "FL5_s23");
			LaunchFrameForm();
			Pchar.GenQuest.Hunter2Pause = true;
		break;

		case "FL5_s23":
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, "shore22", "reload", "sea");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL5_s24", -1, 0);
		break;

		case "FL5_s24":
			chr = CharacterFromID("JozephFushe");
			SetBaseShipData(chr);
			chr.ship.name = "Mercury";
			SetCrewQuantityFull(chr);

			SetCompanionIndex(pchar, -1, sti(chr.index));
			SetShipRemovable(chr, false);
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;
			SetCharacterPerk(chr, "IronWill");
			SetCharacterPerk(chr, "ShipEscape");
			chr.boat = true;
			
			chr.location = "none";

			for(i=1;i<5;i++)
			{	
				chr = CharacterFromID("FL_FrCapitan"+i);
				SetCompanionIndex(pchar, -1, sti(chr.index));
				SetShipRemovable(chr, false);
				SetCharacterRemovable(chr, false);
				chr.CompanionEnemyEnable = false;
				chr.Abordage.Enable = false;
				chr.location = "none";
			}

			AddQuestRecord("FL5", "6");
			DisableEncGen("Shore22", false);
			chrDisableReloadTolocation = false;
			
			chr = GetCharacter(NPC_GenerateCharacter("FL_VaanStraten", "officer_9", "man", "man", 10, HOLLAND, -1, true));
			chr.name = "Ваан";
			chr.lastname = "Стратен";
			chr.ship.type = GenerateShip(SHIP_SEA_BOAT,0);
			SetBaseShipData(chr);
			chr.ship.name = "Шлюпка";
			chr.AlwaysFriend = true;
			LAi_SetImmortal(chr, true);
			
			chr.dialog.filename = "Quest\FranceLine\VaanStraten.c";
			chr.DeckDialogNode = "first time";

			chr.mapEnc.type = "trade";
			chr.mapEnc.worldMapShip = "quest_ship";
			chr.mapEnc.Name = "потерпевшие кораблекрушение";
			chr.wdm_speed = 0.5; // скорость на глобалке
			Map_CreateTrader("Shore37", "Shore22", chr.id, 10);	// бухта Гуахира на Пальмовый берег

			pchar.MainQuest = "FL5_s24";	// это для Маракайбо
		break;
		
		//------------------------------------------------------------------------------------------------------------
		// Помогаем голландцам - переход к серебрянному каравану
		case "FL5a_s24":
			Map_ReleaseQuestEncounter("FL_VaanStraten");
			chr = CharacterFromID("FL_VaanStraten");
			Group_SetAddressNone(chr.seaai.group.name);
			LAi_ActorDialogNow(CharacterFromID("JozephFushe"), pchar, "FL5a_s25", 0);
		break;

		case "FL5a_s25":
			AddQuestRecord("FL5", "7a");

			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, "none", "", "");
			Return2SeaAfterCabin();
			chr = CharacterFromID("FL_VaanStraten");
			DeleteAttribute(chr, "DeckDialogNode");

			AddPassenger(pchar, chr, false);
			SetCharacterRemovable(chr, false);
			
			pchar.MainQuest = "";		// снимим признак похода на Маракайбо
			
			// Серебрянный караван
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
			chr.id = "FL_SpainCapitan1";
			FantomMakeCoolSailor(chr, SHIP_FRIGATE, "Санта Акведа", CANNON_TYPE_CANNON_LBS18, 70, 70, 70);
			chr.AlwaysEnemy = true;
			SetCaptanModelByEncType(chr, "war");

			sGroup = "Sea_"+chr.id;							// имя группы = sea_+"ид НПС-энкаунтера" без этого группа по экнкаунтеру не логинится!!!!!
			Group_FindOrCreateGroup(sGroup);
			Group_SetType(sGroup,"trade");
			Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
			Group_LockTask(sGroup);
			Group_AddCharacter(sGroup, chr.id);
			Group_SetGroupCommander(sGroup, chr.id);
			
			// корабли с серебром
			chr = GetCharacter(NPC_GeneratePhantomCharacter("citizen", SPAIN, MAN, -1));
			chr.id = "FL_SpainCapitan2";
			FantomMakeCoolSailor(chr, SHIP_GALEON_L, "Санта-Каталина Мартир", CANNON_TYPE_CULVERINE_LBS12, 30, 30, 30);
			chr.AlwaysEnemy = true;
			AddCharacterGoods(chr, GOOD_SILVER, GetCharacterFreeSpace(chr, GOOD_SILVER));
			SetCaptanModelByEncType(chr, "trade");
			
			chr = GetCharacter(NPC_GeneratePhantomCharacter("citizen", SPAIN, MAN, -1));
			chr.id = "FL_SpainCapitan3";
			FantomMakeCoolSailor(chr, SHIP_CARAVEL, "Пуэбла", CANNON_TYPE_CULVERINE_LBS6, 30, 30, 30);
			chr.AlwaysEnemy = true;
			AddCharacterGoods(chr, GOOD_SILVER, GetCharacterFreeSpace(chr, GOOD_SILVER));
			SetCaptanModelByEncType(chr, "trade");
			
			chr = GetCharacter(NPC_GeneratePhantomCharacter("citizen", SPAIN, MAN, -1));
			chr.id = "FL_SpainCapitan4";
			FantomMakeCoolSailor(chr, SHIP_GALEON_L, "Лос Ангелас", CANNON_TYPE_CULVERINE_LBS12, 30, 30, 30);
			chr.AlwaysEnemy = true;
			AddCharacterGoods(chr, GOOD_SILVER, GetCharacterFreeSpace(chr, GOOD_SILVER));
			SetCaptanModelByEncType(chr, "trade");
			
			chr = GetCharacter(NPC_GeneratePhantomCharacter("citizen", SPAIN, MAN, -1));
			chr.id = "FL_SpainCapitan5";
			FantomMakeCoolSailor(chr, SHIP_PINNACE, "Сан Джеронимо", CANNON_TYPE_CANNON_LBS12, 30, 30, 30);
			chr.AlwaysEnemy = true;
			AddCharacterGoods(chr, GOOD_SILVER, GetCharacterFreeSpace(chr, GOOD_SILVER));
			SetCaptanModelByEncType(chr, "trade");
			
			// Охрана
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
			chr.id = "FL_SpainCapitan6";
			FantomMakeCoolSailor(chr, SHIP_CORVETTE_H, "Анфитрита", CANNON_TYPE_CANNON_LBS12, 70, 70, 70);
			chr.AlwaysEnemy = true;
			SetCaptanModelByEncType(chr, "war");
			Group_addCharacter(sGroup, chr.id);

			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
			chr.id = "FL_SpainCapitan7";
			FantomMakeCoolSailor(chr, SHIP_FRIGATE_L, "Сан Бруно", CANNON_TYPE_CANNON_LBS18, 70, 70, 70);
			chr.AlwaysEnemy = true;
			SetCaptanModelByEncType(chr, "war");
			
			for(i=2;i<8;i++)
			{
				Group_addCharacter(sGroup, "FL_SpainCapitan"+i);
			}

			chr = CharacterFromID("FL_SpainCapitan1");
			chr.mapEnc.type = "trade";
			chr.mapEnc.worldMapShip = "quest_ship";
			chr.mapEnc.Name = "Серебряный караван";
			chr.wdm_speed = 0.7; // скорость на глобалке
			Map_CreateTrader("Shore22", "Shore15", "FL_SpainCapitan1", 30); // с Кюрасао на Гавану

			pchar.quest.FL5as25.win_condition.l1 = "Group_Death";
			pchar.quest.FL5as25.win_condition.l1.group = sGroup;
			pchar.quest.FL5as25.win_condition = "FL5a_s26";
		break;

		case "FL5a_s26":
			pchar.quest.FL5as26.win_condition.l1 = "MapEnter";
            pchar.quest.FL5as26.win_condition = "FL5a_s27";
			
			for(i=1;i<5;i++)
			{	
				iChar = GetCharacterIndex("FL_FrCapitan"+i)
				if(iChar != -1) LAi_SetImmortal(&characters[iChar], true);
				RemoveCharacterCompanion(pchar, &characters[iChar]);
				SetLifeDay(&characters[iChar], 0);
			}
			
			pchar.MainQuest.Silver = GetCargoGoods(pchar, GOOD_SILVER);

			Map_ReleaseQuestEncounter("FL_SpainCapitan1");
		break;

		case "FL5a_s27":
			if(GetCharacterIndex("JozephFushe") == -1)
			{
				AddQuestRecord("FL5", "9a");
				SetQuestHeaderColor("FL5", gray);
				CloseQuestHeader("FL5");
				break;
			}
			
			AddQuestRecord("FL5", "8a");

			pchar.quest.FL5as27.win_condition.l1 = "location";
			pchar.quest.FL5as27.win_condition.l1.location = "Tortuga_town";
			pchar.quest.FL5as27.win_condition = "FL6_1";
		break;

		//------------------------------------------------------------------------------------------------------------
		// Посылаем голландцев, идем на Маракайбо
		case "FL5_s24":
			Map_ReleaseQuestEncounter("FL_VaanStraten");
			chr = CharacterFromID("FL_VaanStraten");
			DeleteAttribute(chr, "DeckDialogNode");
			SetLifeDay(chr, 0);
			Return2SeaAfterCabin();
		break;

		case "FL5_s25":				// приходит из AIFort.c
			pchar.MainQuest = "";
			chr = characterFromID("Maracaibo Fort Commander");
			chr.Fort.Mode = FORT_DEAD;
	
			chr.Fort.DieTime.Year = GetDataYear();
			chr.Fort.DieTime.Month = GetDataMonth();
			chr.Fort.DieTime.Day = GetDataDay();
			chr.Fort.DieTime.Time = GetTime();
			Event(FORT_DESTROYED, "l", sti(chr.index));
			
			Sea_DeckBoatLoad(GetMainCharacterIndex());
			pchar.quest.FL3s25.win_condition.l1 = "location";
			pchar.quest.FL3s25.win_condition.l1.location = "Deck_Near_Ship";
			pchar.quest.FL3s25.win_condition = "FL5_s26";
		break;

		case "FL5_s26":
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);

			chr2 = characterFromID("Maracaibo Fort Commander");
			chr = GetCharacter(NPC_GenerateCharacter("Maracaibo_commander_phantom", chr2.model, "man", "man", 20, SPAIN, 0, true));
			chr.name = chr2.name;
			chr.lastname = chr2.lastname;
			chr.dialog.filename = "Quest\FranceLine\Maracaibo_fortCommander.c";
			chr.greeting = "hi_senjor";

			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto2");
			LAi_SetActorType(chr);
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL5_s27", -1, 0);

			GenerateSailorsOnDeck(FRANCE, "", true, "goto", 9);
		break;

		case "FL5_s27":
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			Return2SeaAfterCabin();
			SetTownCapturedState("Maracaibo", true);
			pchar.MainQuest = "FL5_s27";
			
			pchar.quest.FL5s27.win_condition.l1 = "EnterToSea";
			pchar.quest.FL5s27.win_condition = "FL5_s27a";
		break;

		case "FL5_s27a":
			DoQuestCheckDelay("FL5_s27b", 0.5);
		break;

		case "FL5_s27b":
			pchar.NoExplose = true;
			pchar.location.from_sea = "Maracaibo_town";
			DoQuestReloadToLocation("Maracaibo_town", "reload", "reload1", "FL5_s28");
		break;

		case "FL5_s28":
			if(GetCharacterIndex("JozephFushe")==-1)
			{
				SetTownCapturedState("Maracaibo", false);
				DeleteAttribute(pchar, "NoExplose");
				AddQuestRecord("FL5", "9a");
				SetQuestHeaderColor("FL5", gray);
				CloseQuestHeader("FL5");
				pchar.MainQuest = "";
				break;
			}
			
			QuestCloseSeaExit();
			
			chr2 = CharacterFromID("Maracaibo_mayor");
			chr = GetCharacter(NPC_GenerateCharacter("Maracaibo_mayor_phantom", chr2.model, "man", "man", 20, SPAIN, -1, false));
			chr.name = chr2.name;
			chr.lastname = chr2.lastname;
			chr.dialog.filename = "Quest\FranceLine\MaracaiboMayorPhantom.c";
			chr.greeting = "respect_hovernor";
			ChangeCharacterAddressGroup(chr, "Maracaibo_townhall", "sit", "sit1");
			LAi_SetHuberType(chr);
			LAi_LoginInCaptureTown(chr, true);
		break;

		case "FL5_s29":
			pchar.quest.FL5s29.win_condition.l1 = "location";
			pchar.quest.FL5s29.win_condition.l1.location = "Maracaibo_town";
			pchar.quest.FL5s29.win_condition = "FL5_s30";
		break;

		case "FL5_s30":
			for(i = 0;i<GOOD_SILVER+1;i++) SetStoreGoods(&Stores[Maracaibo_STORE], i, rand(100));

			chr = CharacterFromID("JozephFushe");
			LAi_LoginInCaptureTown(chr, true);
			chr.dialog.currentnode = "102";
			ChangeCharacterAddressGroup(chr, "Maracaibo_town", "goto", "goto9");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL5_s31", -1, 0);

			// 4+1 мушкетер человек нашей команды
			for(i=0;i<5;i++)
			{
				if(i==4)
				{
					chr = GetCharacter(NPC_GeneratePhantomCharacter("mushketer", FRANCE, MAN, -1));
					chr.id = "FL_OurSoldier_"+i;
				}
				else
				{
					model = LAi_GetBoardingModel(GetMainCharacter(), &sStr);
					chr = GetCharacter(NPC_GenerateCharacter("FL_OurSoldier_"+i, model, "man", sStr, sti(pchar.rank), FRANCE, -1, true));
				}

				LAi_LoginInCaptureTown(chr, true);
				LAi_CharacterDisableDialog(chr);
				PlaceCharacter(chr, "goto", "random_must_be_near");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
			}
		break;

		case "FL5_s31":
			AddQuestRecord("FL5", "7");

			pchar.quest.FL5s31.win_condition.l1 = "location";
			pchar.quest.FL5s31.win_condition.l1.location = "Maracaibo_exittown";
			pchar.quest.FL5s31.win_condition = "FL5_s32";
		break;

		case "FL5_s32":
			chrDisableReloadTolocation = true;
			for(i=0;i<5;i++)
			{	
				chr = CharacterFromID("FL_OurSoldier_"+i);
				ChangeCharacterAddressGroup(chr, pchar.location, "rld", "aloc"+(i+6));
				LAi_SetOfficerType(chr);
			}

			// немного испанцев
			for(i=0;i<3;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("soldier", SPAIN, MAN, -1));
				LAi_LoginInCaptureTown(chr, true);
				ChangeCharacterAddressGroup(chr, pchar.location, "rld", "loc20");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
				LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				//LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("FL_EnemyFight", "FL5_s33");
			}
		break;

		case "FL5_s33":
			Delay_DeleteGroup("FL_EnemyFight");
			AddQuestRecord("FL5", "8");
			chrDisableReloadTolocation = false;
			
			pchar.quest.FL5s33a.win_condition.l1 = "location";
			pchar.quest.FL5s33a.win_condition.l1.location = "Maracaibo_jungle_03";
			pchar.quest.FL5s33a.win_condition = "FL5_s34a";

			pchar.quest.FL5s33.win_condition.l1 = "locator";
			pchar.quest.FL5s33.win_condition.l1.location = "Maracaibo_jungle_04";
			pchar.quest.FL5s33.win_condition.l1.locator_group = "encdetector";
			pchar.quest.FL5s33.win_condition.l1.locator = "enc02";
			pchar.quest.FL5s33.win_condition = "FL5_s34";
		break;

		case "FL5_s34a":
			for(i=0;i<5;i++)
			{	
				iChar = GetCharacterIndex("FL_OurSoldier_"+i);
				if(iChar != -1)
				{
					chr = GetCharacter(iChar);
					PlaceCharacter(chr, "rld", "random_must_be_near");
					LAi_SetOfficerType(chr);
				}
			}

			pchar.quest.FL5s34a.win_condition.l1 = "location";
			pchar.quest.FL5s34a.win_condition.l1.location = "Maracaibo_jungle_04";
			pchar.quest.FL5s34a.win_condition = "FL5_s34a";
		break;

		case "FL5_s34":
			chrDisableReloadTolocation = true;

			// немного испанцев
			for(i=1;i<7;i++)
			{
				if(i==1) chr = GetCharacter(NPC_GeneratePhantomCharacter("mushketer", SPAIN, MAN, -1));
				else chr = GetCharacter(NPC_GeneratePhantomCharacter("soldier", SPAIN, MAN, -1));
				LAi_LoginInCaptureTown(chr, true);
				ChangeCharacterAddressGroup(chr, pchar.location, "rld", "loc"+i);
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
				LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("FL_EnemyFight", "FL5_s35");
			}
		break;

		case "FL5_s35":
			Delay_DeleteGroup("FL_EnemyFight");
			chrDisableReloadTolocation = false;
			AddQuestRecord("FL5", "9");

			pchar.quest.FL5s35.win_condition.l1 = "location";
			pchar.quest.FL5s35.win_condition.l1.location = "Guibraltar_exittown";
			pchar.quest.FL5s35.win_condition = "FL5_s36";
		break;

		case "FL5_s36":
			chrDisableReloadTolocation = true;
			for(i=0;i<5;i++)
			{	
				iChar = GetCharacterIndex("FL_OurSoldier_"+i);
				if(iChar != -1)
				{
					chr = GetCharacter(iChar);
					ChangeCharacterAddressGroup(chr, pchar.location, "rld", "loc1");
					LAi_SetOfficerType(chr);
				}
			}
			
			// Финальные силы испанцев
			// Босс
			chr2 = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
			FantomMakeCoolFighter(chr2, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 70, 70, "", "", 300.0);
			ChangeCharacterAddressGroup(chr2, pchar.location, "rld", "aloc0");
			LAi_SetWarriorTypeNoGroup(chr2);
			LAi_group_MoveCharacter(chr2, "FL_EnemyFight");

			// два мушкетера
			for(i=0;i<2;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("mushketer", SPAIN, MAN, -1));
				FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 20, 70, "", "", 0.0);
				ChangeCharacterAddressGroup(chr, pchar.location, "rld", "aloc0");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			}

			// 5 солдат
			for(i=0;i<5;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("soldier", SPAIN, MAN, -1));
				FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 50, 50, "", "", 100.0);
				ChangeCharacterAddressGroup(chr, pchar.location, "rld", "aloc0");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			}

			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroupsEx("FL_EnemyFight", LAI_GROUP_PLAYER, true, sti(chr2.index), sti(pchar.index), true, false);
			LAi_group_SetCheck("FL_EnemyFight", "FL5_s37");
		break;

		case "FL5_s37":
			chrDisableReloadTolocation = false;
			Delay_DeleteGroup("FL_EnemyFight");
			AddQuestRecord("FL5", "10");
			pchar.MainQuest = "FL5_s37";

			for(i=0;i<5;i++)
			{	
				iChar = GetCharacterIndex("FL_OurSoldier_"+i);
				if(iChar != -1) SetLifeDay(GetCharacter(iChar), 0);
			}
		break;

		case "FL5_s38":
			pchar.MainQuest = "FL5_s38";
			SetStoreGoods(&Stores[Maracaibo_STORE], GOOD_GOLD, 112);
			SetStoreGoods(&Stores[Maracaibo_STORE], GOOD_SILVER, 674);
			LaunchColonyCapture(GetColonyByIndex(FindColony("Maracaibo")));
		break;

		case "FL5_s39":
			pchar.MainQuest = "FL5_s38";
			AddQuestRecord("FL5", "11");
		break;

		case "FL5_s40":
			AddMoneyToCharacter(pchar, 67000);
			AddQuestRecord("FL5", "12");
			chr = CharacterFromID("Maracaibo_mayor_phantom");
			SetLifeDay(chr, 0);
			LAi_CharacterDisableDialog(chr);
			pchar.MainQuest = "";
			pchar.quest.FL5s40.win_condition.l1 = "location";
			pchar.quest.FL5s40.win_condition.l1.location = "Maracaibo_town";
			pchar.quest.FL5s40.win_condition = "FL5_s41";
		break;

		case "FL5_s41":
			pchar.mainQuest.CapCount = 0;
			chr2 = CharacterFromID("JozephFushe");
			for(i=1; i<5; i++)
			{
				iChar = GetCharacterIndex("FL_FrCapitan"+i);
				if(iChar != -1)
				{
					chr = GetCharacter(iChar);
					if(IsCompanion(chr))
					{
						LAi_LoginInCaptureTown(chr, true);
						PlaceCharacter(chr, "goto", "random_must_be_near");
						LAi_SetActorType(chr);
						LAi_ActorFollow(chr, chr2, "", -1);
						pchar.mainQuest.CapCount = (sti(pchar.mainQuest.CapCount)+1);
					}
				}
			} 

			LAi_ActorDialog(chr2, pchar, "", -1, 0);

			SetTimerConditionParamEx("FL5s41", "FL5_RestoreMaracaibo", 0, 0, 6);
		break;
		
		// Восставноление Маракайбо
		case "FL5_RestoreMaracaibo":
			Log_testInfo("!!!Маракайбо восстановлен!!!!");
			SetTownCapturedState("Maracaibo", false);
		break;

		// Капитанов нет - уходим на тортугу
		case "FL5_s42a":
			AddQuestRecord("FL5", "13a");
			chr = CharacterFromID("JozephFushe");
			chr.location = "none";

			QuestOpenSeaExit();
			DeleteAttribute(pchar, "NoExplose");
			DeleteAttribute(pchar, "mainQuest.CapCount");
			pchar.MainQuest.Silver = GetCargoGoods(pchar, GOOD_SILVER);
			
			pchar.quest.FL5s42a.win_condition.l1 = "location";
			pchar.quest.FL5s42a.win_condition.l1.location = "Tortuga_town";
			pchar.quest.FL5s42a.win_condition = "FL6_1";
		break;

		// Капитаны есть - делим добычу
		case "FL5_s42":
			DoQuestCheckDelay("FL5_s43", 1.0);
		break;

		case "FL5_s43":
			AddDataToCurrent(0,0,1);
			AddTimeToCurrent(1,21);
			RefreshLandTime();
			SetLaunchFrameFormParam("На дележ добычи ушло около суток...", "FL5_s44", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL5_s44":
			AddQuestRecord("FL5", "13");
			i = makeint(GetSquadronGoods(pchar, GOOD_SILVER) / (sti(pchar.mainQuest.CapCount) + 1));
			SetCharacterGoods(pchar, GOOD_SILVER, i);
			AddMoneyToCharacter(pchar, (-67000 + makeint(67000 / (sti(pchar.mainQuest.CapCount) + 1))));
			pchar.MainQuest.Silver = GetCargoGoods(pchar, GOOD_SILVER);
			Log_Info("Серебро разделено");
			bOk = true;
			
			Group_FindOrCreateGroup("Old_Friends");
			Group_SetType("Old_Friends", "war");
			
			for(i=1; i<5; i++)
			{
				iChar = GetCharacterIndex("FL_FrCapitan"+i);
				if(iChar != -1)
				{
					chr = GetCharacter(iChar);
					if(IsCompanion(chr))
					{
						ChangeCharacterAddressGroup(chr, "none", "", "");
						RemoveCharacterCompanion(pchar, chr);
						Group_AddCharacter("Old_Friends", chr.id);
						chr.ShipEnemyDisable = true;
						if(bOk)
						{
							bOk = false;
							Group_SetGroupCommander("Old_Friends", chr.id);
							Group_SetPursuitGroup("Old_Friends", PLAYER_GROUP);
							Group_SetAddress("Old_Friends", "Maracaibo", "", "");
						}
					}
				}
			}
			
			// Эскадра испанцев
			for(i=0;i<3;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
				chr.id = "FL_spa_capitan_"+i;
				FantomMakeCoolFighter(chr, sti(pchar.rank), 70, 70, "", "", 100.0);
			}

			FantomMakeCoolSailor(CharacterFromID("FL_spa_capitan_0"), SHIP_GALEON, "Сан Лукас", CANNON_TYPE_CANNON_LBS12, 80, 80, 80);
			FantomMakeCoolSailor(CharacterFromID("FL_spa_capitan_1"), SHIP_FRIGATE, "Санта Казилда", CANNON_TYPE_CANNON_LBS18, 80, 80, 80);
			FantomMakeCoolSailor(CharacterFromID("FL_spa_capitan_2"), SHIP_LINEFRIGATE, "Ла Салутасьон", CANNON_TYPE_CANNON_LBS24, 80, 80, 80);
			
			Group_FindOrCreateGroup("FL_Spa_attack");
			Group_SetType("FL_Spa_attack", "war");
			for(i=0;i<3;i++) Group_AddCharacter("FL_Spa_attack", "FL_spa_capitan_"+i);
			Group_SetGroupCommander("FL_Spa_attack", "FL_spa_capitan_0");
			Group_SetPursuitGroup("FL_Spa_attack", PLAYER_GROUP);
			Group_SetAddress("FL_Spa_attack", "Maracaibo", "", "");
			Group_SetTaskAttack("FL_Spa_attack", "Old_Friends");
			Group_LockTask("FL_Spa_attack");

			LAi_ActorDialog(CharacterFromID("JozephFushe"), pchar, "FL5_s45", -1, 0);
		break;

		case "FL5_s45":
			chr = CharacterFromID("JozephFushe");
			chr.location = "none";
			
			DeleteAttribute(pchar, "NoExplose");
			DeleteAttribute(pchar, "mainQuest.CapCount");

			QuestOpenSeaExit();

			pchar.quest.FL5s45.win_condition.l1 = "MapEnter";
            pchar.quest.FL5s45.win_condition = "FL5_s46";
		break;

		case "FL5_s46":
			for(i=1; i<5; i++)
			{
				iChar = GetCharacterIndex("FL_FrCapitan"+i);
				if(iChar != -1) SetLifeDay(GetCharacter(iChar), 0);
			}

			for(i=0; i<3; i++)
			{
				iChar = GetCharacterIndex("FL_spa_capitan_"+i);
				if(iChar != -1) SetLifeDay(GetCharacter(iChar), 0);
			}
			
			pchar.quest.FL5s46.win_condition.l1 = "location";
			pchar.quest.FL5s46.win_condition.l1.location = "Tortuga_town";
			pchar.quest.FL5s46.win_condition = "FL6_1";
		break;

//====================================================================================================================
//	Мари
//====================================================================================================================
		case "FL6_1":
			iChar = GetCharacterIndex("JozephFushe");
			if(iChar == -1)
			{
				AddQuestRecord("FL5", "14");
				SetQuestHeaderColor("FL5", gray);
				CloseQuestHeader("FL5");
				pchar.MainQuest = "";
				break;
			}

			chrDisableReloadTolocation = true;
			chr = GetCharacter(iChar);
			chr.dialog.currentnode = "111";

			if(IsCompanion(chr)) RemoveCharacterCompanion(pchar, chr);
			RemovePassenger(pchar, chr);
			ChangeCharacterAddressGroup(chr, "Tortuga_town", "quest", "quest1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL6_2", -1, 0);
		break;

		case "FL6_2":
			LAi_ActorRunToLocation(CharacterFromID("JozephFushe"), "reload", "houseF3", "Tortuga_houseF3", "barmen", "stay", "FL6_3", -1);
		break;

		case "FL6_3":
			LAi_SetBarmanType(CharacterFromID("JozephFushe"));
			pchar.MainQuest = "FL6_3";
			chrDisableReloadTolocation = false;
			AddQuestRecord("FL5", "15");
			pchar.mainQuest.money = makeint(230 * (sti(pchar.MainQuest.Silver) * 0.05));
			DeleteAttribute(pchar, "mainQuest.silver");
		break;

		case "FL6_4":
			ChangeCharacterNationReputation(pchar, FRANCE, 10);
			OfficersReaction("good");
			ChangeCharacterReputation(pchar, 10);
			DeleteAttribute(pchar, "mainQuest.money");
			pchar.MainQuest = "";
			AddQuestRecord("FL5", "16");
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
		break;

		case "FL6_5":
			LAi_SetActorType(CharacterFromID("JozephFushe"));
			GiveItem2Character(pchar, "FQ_letter6");
		break;

		case "FL6_6":
			LAi_SetStayType(CharacterFromID("JozephFushe"));
		break;

		case "FL6_7":
			LAi_SetBarmanType(CharacterFromID("JozephFushe"));
			chrDisableReloadTolocation = false; // включается в диалоге с Фуше
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 1;

			SetQuestHeaderColor("FL5", gray);
			CloseQuestHeader("FL5");
			
			SetQuestHeader("FL6");
			SetQuestHeaderColor("FL6", yellow);
			AddQuestRecord("FL6", "1");
			
			ChangeCharacterAddressGroup(CharacterFromID("FortFrance_trader"), "none", "", "");
			chr = CharacterFromID("FL_Mary");
			ChangeCharacterAddressGroup(chr, "FortFrance_store", "barmen", "stay");
			LAi_SetStayType(chr);
			chr.dialog.currentnode = "7";

			DoReloadCharacterToLocation("Tortuga_town", "reload", "houseF3");
		break;

		case "FL6_8":
			pchar.MainQuest = "FL6_8";	// для диалога с алкашами
			AddQuestRecord("FL6", "2");
		break;

		case "FL6_9":
			pchar.MainQuest = "FL6_9";	// игра в карты
			pchar.MainQuest.game_count = 0;
			AddQuestRecord("FL6", "3");
		break;

		case "FL6_10":
			pchar.MainQuest = "";
			DeleteAttribute(pchar, "MainQuest.game_count");

			bDisableFastReload = true;
			
			pchar.quest.FL610.win_condition.l1 = "ExitFromLocation";
         pchar.quest.FL610.win_condition.l1.location = pchar.location;
		   pchar.quest.FL610.win_condition = "FL6_11";
		break;

		case "FL6_11":
			locations[FindLocation("PortPax_town")].reload.l14.disable = 1;
			Pchar.GenQuest.Hunter2Pause = true;
			bDisableFastReload = false;
			chrDisableReloadTolocation = true;

			chr = CharacterFromID("FL_granie");
			LAi_SetActorType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto3");
			LAi_ActorDialog(chr, pchar, "FL6_12", -1, 0);
		break;

		case "FL6_12":
			LAi_ActorRunToLocation(CharacterFromID("FL_granie"), "reload", "reload1_back", "none", "", "", "FL6_13", -1);
		break;

		case "FL6_13":
			chrDisableReloadTolocation = false;
			AddQuestRecord("FL6", "4");
			pchar.MainQuest = "FL6_13";
		break;

		case "FL6_14":
			pchar.MainQuest = "";
			pchar.name = "Голос из-за";
			pchar.lastname = "двери";
			pchar.dialog.currentnode = "FL6_1";
			LAi_SetActorType(pchar);
			LAi_ActorSelfDialog(pchar, "FL6_15");
		break;

		case "FL6_15":
			pchar.name = "Мишель";
			pchar.lastname = "де Граммон";
			LAi_SetPlayerType(pchar);
			locations[FindLocation("PortPax_town")].reload.l14.disable = 0;
			BLI_RefreshCommandMenu();

			pchar.quest.FL615.win_condition.l1 = "location";
			pchar.quest.FL615.win_condition.l1.location = "PortPax_houseF1";
			pchar.quest.FL615.win_condition = "FL6_16";
		break;

		case "FL6_16":
			chrDisableReloadTolocation = true;

			for(i=0;i<3;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, -1));
				chr.id = "FL_tmp_pirate_"+i;
				LAi_SetActorType(chr);
				if(i==0) ChangeCharacterAddressGroup(chr, pchar.location, "barmen", "bar2");
				else ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto"+i);
			}

			chr.name = "Морис";
			chr.lastname = "Дюпон";
			chr.dialog.filename = "Quest\FranceLine\MorisDupon.c";
			chr.greeting = "zdrastvuite_capitan";

			LAi_ActorDialog(chr, pchar, "FL6_17", -1, 0)
		break;

		case "FL6_17":
			DoQuestCheckDelay("FL6_18", 1.0);
		break;

		case "FL6_18":
			AddTimeToCurrent(2, 21);
			SetLaunchFrameFormParam("Мне несказанно везло!"+NewStr()+"За 2 часа игры мне удалось"+NewStr()+"выиграть 50000 пиастров!", "FL6_19", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL6_19":
			AddMoneyToCharacter(pchar, 50000);
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			LAi_ActorDialog(CharacterFromID("FL_tmp_pirate_2"), pchar, "FL6_20", -1, 0);
		break;

		case "FL6_20":
			DoQuestReloadToLocation("PortPax_houseF1_Cave", "goto", "goto1", "FL6_21");
		break;

		case "FL6_21":
			LAi_SetGroundSitType(pchar);

			chr2 = CharacterFromID("FortFrance_trader");
			chr = GetCharacter(NPC_GeneratePhantomCharacter("citizen", FRANCE, MAN, -1));
			chr.id = "FL_Mary_father";
			chr.name = chr2.name;
			chr.lastname = chr2.lastname;
			chr.model = chr2.model;
			chr.dialog.filename = "Quest\FranceLine\Mary_father.c";
			chr.greeting = "Kto_zdes";
			LAi_SetGroundSitType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto2");

			DoQuestCheckDelay("FL6_22", 1.0);
		break;

		case "FL6_22":
			DialogMain(CharacterFromID("FL_Mary_father"), false);
		break;

		case "FL6_23":
			chr = CharacterFromID("FL_granie");
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1_back");
			chr.dialog.currentnode = "59";
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL6_24", -1, 0);

			chr = GetOurSailor("FL_tmp_sailor");
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1_back");
			LAi_SetActorType(chr);
			LAi_ActorFollow(chr, CharacterFromID("FL_granie"), "", -1);
		break;

		case "FL6_24":
			LAi_Fade("FL6_25", "");
		break;

		case "FL6_25":
			LAi_SetActorType(pchar);
			LAi_SetActorType(CharacterFromID("FL_Mary_father"));

			chr = CharacterFromID("FL_tmp_pirate_2");
			chr.greeting = "run_away";
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1_back");
			LAi_SetActorType(chr);
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL6_26", -1, 0);
			
			chr = GetOurSailor("FL_tmp_sailor2");
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1_back");
			LAi_SetActorType(chr);
			LAi_ActorFollow(chr, CharacterFromID("FL_tmp_pirate_2"), "", -1);
		break;

		case "FL6_26":
			LAi_SetPlayerType(pchar);
			for(i=0;i<3;i++) SetLifeDay(CharacterFromID("FL_tmp_pirate_"+i), 0);
			chrDisableReloadTolocation = false;
			chr = CharacterFromID("FL_Mary_father");
			chr.location = "none";
			FaceMaker(chr);
			AddPassenger(pchar, chr, false);
			SetCharacterRemovable(chr, false);
			ChangeCharacterAddressGroup(CharacterFromID("FL_granie"), "none", "", "");
			DoReloadCharacterToLocation("PortPax_town", "reload", "houseF1");
			pchar.MainQuest = "FL6_26";
			AddQuestRecord("FL6", "5");
			characters[GetCharacterIndex("FL_Mary")].dialog.currentnode = "11";

			pchar.quest.FL626.win_condition.l1 = "location";
			pchar.quest.FL626.win_condition.l1.location = "FortFrance_store";
			pchar.quest.FL626.win_condition = "FL6_s27";
		break;

		case "FL6_s27":
			chr = CharacterFromID("FL_Mary_father");
			RemovePassenger(pchar, chr);
			chrDisableReloadTolocation = true;
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto2");
			LAi_SetActorType(chr);
			LAi_ActorFollow(chr, CharacterFromID("FL_Mary"), "", -1);

			LAi_SetActorType(pchar);
			pchar.name = "Мари ";
			pchar.lastname = "и её отец";
			pchar.dialog.currentnode = "FL6_3";
			LAi_ActorSelfDialog(pchar, "FL6_s28");
		break;

		case "FL6_s28":
			pchar.name = "Мишель";
			pchar.lastname = "де Граммон";
			DoQuestCheckDelay("FL6_s28a", 0.5);
		break;

		case "FL6_s28a":
			LAi_ActorDialogNow(pchar, CharacterFromID("FL_Mary"), "FL6_s29", 0);
		break;

		case "FL6_s29":
			LAi_SetActorType(CharacterFromID("FL_Mary"));
			LAi_ActorWaitDialog(CharacterFromID("FL_Mary_father"), pchar);
			DoQuestCheckDelay("FL6_s30", 0.5);
		break;

		case "FL6_s30":
			LAi_ActorDialogNow(pchar, CharacterFromID("FL_Mary_father"), "", 0);
			pchar.MainQuest = "";
			characters[GetCharacterIndex("FL_Mary")].location = "none";
			i = GetCharacterIndex("FortFrance_trader");
			characters[i].location = pchar.location;
			characters[i].location.group = "barmen";
			characters[i].location.locator = "stay";
		break;

		case "FL6_s31":
			AddMoneyToCharacter(pchar, -100000);
			pchar.MainQuest = "";
			AddQuestRecord("FL6", "6");
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
		break;

		case "FL6_s32":
			chr = CharacterFromID("JozephFushe");
			chr.ship.type = GenerateShip(SHIP_GALEON, 0);
			SetBaseShipData(chr);
			chr.ship.name = "Victoria";
			SetCrewQuantityFull(chr);
			chr.location.from_sea = "Tortuga_town";
			
			pchar.MainQuest = "";
			SetQuestHeaderColor("FL6", gray);
			CloseQuestHeader("FL6");
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 1;
			DoQuestReloadToLocation("Tortuga_town", "reload", "houseF3", "FL7_s1");
		break;

//====================================================================================================================
//	Поход на Куману
//====================================================================================================================
		case "FL7_s1":
			SetQuestHeader("FL7");
			SetQuestHeaderColor("FL7", yellow);
			AddQuestRecord("FL7", "1");
			SetTimerConditionParamEx("FL7s1", "FL7_s2", 0, 0, 2);
		break;

		case "FL7_s2":
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, "Tortuga_town", "quest", "quest1");
			LAi_SetStayType(chr);
		break;

		case "FL7_s3":
			chr = CharacterFromID("JozephFushe");
			chr.location = "none";
			LAi_SetActorType(chr);
			chr.rank = (sti(pchar.rank)-1);
			CalculateSkillsFromRank(chr, sti(chr.rank));
			SetCompanionIndex(pchar, -1, sti(chr.index));
			SetShipRemovable(chr, false);
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;
			SetCharacterPerk(chr, "IronWill");
			SetCharacterPerk(chr, "ShipEscape");
			chr.boat = true;

			AddQuestRecord("FL7", "2");

			pchar.quest.FL7s3.win_condition.l1 = "location";
			pchar.quest.FL7s3.win_condition.l1.location = "Shore19"; // бухта Карупано
			pchar.quest.FL7s3.win_condition = "FL7_s4";
		break;

		case "FL7_s4":
			if(GetCharacterIndex("JozephFushe") == -1)
			{
				Log_Info("Капитан Фуше мёртв. Мне здесь делать нечего.");
				break;
			}

			pchar.EncountersGen = false;
			QuestCloseSeaExit();
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto1");
			LAi_SetActorType(chr);
			
			// Индейцы
			chr = GetCharacter(NPC_GenerateCharacter("FL_indian_0", "Aztec", "man", "man", 1, PIRATE, -1, false));
			FantomMakeCoolFighter(chr, sti(pchar.rank), 30, 30, "toporAZ", "", 0);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto3");
			LAi_SetActorType(chr);

			for(i=1;i<3;i++)
			{
				chr2 = GetCharacter(NPC_GenerateCharacter("FL_indian_"+i, "aztecWarrior"+i, "man", "man", 1, PIRATE, -1, false));
				chr2.indian = "1";
				FantomMakeCoolFighter(chr2, sti(pchar.rank), 30, 30, "blade11", "", 0);
				ChangeCharacterAddressGroup(chr2, pchar.location, "goto", "goto5");
				LAi_SetActorType(chr2);
				LAi_ActorFollow(chr2, chr, "", -1);
			}

			chr2 = CharacterFromID("JozephFushe");
			// Наших 4+1 мушкетер
			for(i=1;i<5;i++)
			{
				if(i==1) chr = GetCharacter(NPC_GeneratePhantomCharacter("mushketer", FRANCE, MAN, -1));
				else  chr = GetCharacter(NPC_GeneratePhantomCharacter("soldier", FRANCE, MAN, -1));
				chr.id = "FL_our_sold_"+i;
				ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto6");
				LAi_SetActorType(chr);
				LAi_ActorFollow(chr, chr2, "", -1);
			}

			LAi_ActorFollow(chr2, CharacterFromID("FL_indian_0"), "", -1);
			LAi_ActorFollow(pchar, chr2, "FL7_s5", -1);
		break;

		case "FL7_s5":
			pchar.name = "Индеец и";
			pchar.lastname = "капитан Фуше";
			pchar.dialog.currentnode = "FL7_1";
			LAi_ActorSelfDialog(pchar, "FL7_s6");
		break;

		case "FL7_s6":
			SetLifeDay(CharacterFromID("FL_indian_0"), 0);
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			pchar.name = "Мишель";
			pchar.lastname = "де Граммон";
			DoQuestReloadToLocation("QuestCumana_Fort", "reload", "reload1", "FL7_s7");
		break;

		case "FL7_s7":
			// логиним наших
			for(i=1;i<5;i++)
			{	
				chr = CharacterFromID("FL_our_sold_"+i);
				ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1_back");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
				//LAi_warrior_SetCommander(chr, pchar);
			}

			for(i=1;i<3;i++)
			{
				chr = CharacterFromID("FL_indian_"+i);
				ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1_back");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
				//LAi_warrior_SetCommander(chr, pchar);
			}

			LAi_group_Register("FL_EnemyGroup");
			LAi_group_SetLookRadius("FL_EnemyGroup", 17.0);
            LAi_group_SetHearRadius("FL_EnemyGroup", 17.0);
            LAi_group_SetSayRadius("FL_EnemyGroup", 17.0);
			
			// Испанские мушкетеры (3)
			for(i=9;i<12;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("mushketer", SPAIN, MAN, -1));
				FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 60, 60, "", "", 0);
				ChangeCharacterAddressGroup(chr, pchar.location, "soldiers", "soldier"+i);
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_warrior_SetStay(chr, true);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			}

			// Испанские солдаты
			for(i=0;i<20;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("soldier", SPAIN, MAN, -1));
				FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 80, 80, "", "", 200.0);
				PlaceCharacter(chr, "soldiers", "random_must_be_near");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_warrior_SetStay(chr, true);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			}

			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheck("FL_EnemyFight", "FL7_s8");
		break;

		case "FL7_s8":
			Delay_DeleteGroup("FL_EnemyFight");
			
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, 0));
			chr.dialog.filename = "Quest\FranceLine\CumanaOfficer.c";
			chr.greeting = "vi_pobedili";
			PlaceCharacter(chr, "goto", "random_must_be");
			LAi_SetActorType(chr);
			LAi_SetImmortal(chr, true);
			LAi_ActorDialog(chr, pchar, "FL7_s9", -1, 0);
		break;

		case "FL7_s9":
			chr = characterFromID("Cumana Fort Commander");
			chr.Fort.Mode = FORT_DEAD;
	
			chr.Fort.DieTime.Year = GetDataYear();
			chr.Fort.DieTime.Month = GetDataMonth();
			chr.Fort.DieTime.Day = GetDataDay();
			chr.Fort.DieTime.Time = GetTime();
			Event(FORT_DESTROYED, "l", sti(chr.index));

			SetTownCapturedState("Cumana", true);
			pchar.NoExplose = true;

			i = FindLocation(pchar.location);
			locations[i].reload.l1.name = "reload1_back";
			locations[i].reload.l1.go = "Cumana_town";
			locations[i].reload.l1.emerge = "gate_back";
			locations[i].reload.l1.autoreload = "1";
			locations[i].locators_radius.reload.reload1_back = 2.0;
			
			pchar.quest.FL7s9a.win_condition.l1 = "ExitFromLocation";
            pchar.quest.FL7s9a.win_condition.l1.location = pchar.location;
		    pchar.quest.FL7s9a.win_condition = "FL7_s10";

			pchar.quest.FL7s9.win_condition.l1 = "location";
			pchar.quest.FL7s9.win_condition.l1.location = "Cumana_townhall";
			pchar.quest.FL7s9.win_condition = "FL7_s11";

			AddQuestRecord("FL7", "3");
		break;

		case "FL7_s10":
			// остатки наших будут ошиваться у городских ворот и везде с нами
			for(i=1;i<5;i++)
			{	
				iChar = GetCharacterIndex("FL_our_sold_"+i);
				if(iChar != -1)
				{
					chr = &characters[iChar];
					LAi_LoginInCaptureTown(chr, true);
					PlaceCharacter(chr, "goto", "random_must_be");
					LAi_SetWarriorTypeNoGroup(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
				}
			}

			for(i=1;i<3;i++)
			{
				iChar = GetCharacterIndex("FL_indian_"+i);
				if(iChar != -1)
				{
					chr = &characters[iChar];
					LAi_LoginInCaptureTown(chr, true);
					PlaceCharacter(chr, "goto", "random_must_be");
					LAi_SetWarriorTypeNoGroup(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
				}
			}
		break;

		case "FL7_s11":
			chrDisableReloadTolocation = true;
			chr2 = CharacterFromID("Cumana_mayor");
			chr = GetCharacter(NPC_GeneratePhantomCharacter("citizen", SPAIN, MAN, 0));
			chr.id = "Cumana_mayor_phantom";
			chr.name = chr2.name;
			chr.lastname = chr2.lastname;
			chr.model = chr2.model;
			chr.model.animation = chr2.model.animation;
			chr.dialog.filename = "Quest\FranceLine\CumanaMayorPhantom.c";
			chr.greeting = "ya_vsegda_znal_chto_vi_nigodai";
			LAi_SetImmortal(chr, true);
			LAi_LoginInCaptureTown(chr, true);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "governor1");
			LAi_SetActorType(chr);

			// мушкетер охранник
			chr = GetCharacter(NPC_GeneratePhantomCharacter("mushketer", SPAIN, MAN, 0));
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 50, 90, "", "", 0);
			LAi_LoginInCaptureTown(chr, true);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto3");
			LAi_SetWarriorTypeNoGroup(chr);
			LAi_group_MoveCharacter(chr, "FL_EnemyFight");

			// офицер охранник
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, 0));
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 80, 80, "", "", 200.0);
			LAi_LoginInCaptureTown(chr, true);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto4");
			LAi_SetWarriorTypeNoGroup(chr);
			LAi_group_MoveCharacter(chr, "FL_EnemyFight");

			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("FL_EnemyFight", "FL7_s12");
		break;

		case "FL7_s12":
			Delay_DeleteGroup("FL_EnemyFight");
			LAi_SetStayType(CharacterFromID("Cumana_mayor_phantom"));
		break;

		case "FL7_s13":
			pchar.MainQuest = "FL7_s13";
			SetStoreGoods(&Stores[Cumana_STORE], GOOD_GOLD, 500);
			SetStoreGoods(&Stores[Cumana_STORE], GOOD_SILVER, 200);
			LaunchColonyCapture(GetColonyByIndex(FindColony("Cumana")));

			chrDisableReloadTolocation = false;

			pchar.quest.FL7s13.win_condition.l1 = "location";
			pchar.quest.FL7s13.win_condition.l1.location = "Cumana_town";
			pchar.quest.FL7s13.win_condition = "FL7_s14";
			LAi_SetActorType(CharacterFromID("Cumana_mayor_phantom"));
		break;

		case "FL7_s14":
			chrDisableReloadTolocation = true;
			chr = CharacterFromID("JozephFushe");
			LAi_LoginInCaptureTown(chr, true);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto17");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL7_s15", -1, 0);
		break;

		case "FL7_s15":
			chrDisableReloadTolocation = false;
			chr = CharacterFromID("JozephFushe");
			chr.location = "none";
			
			pchar.quest.FL7s15.win_condition.l1 = "location";
			pchar.quest.FL7s15.win_condition.l1.location = "Cumana_Jungle_01";
			pchar.quest.FL7s15.win_condition = "FL7_s16";
			AddQuestRecord("FL7", "4");
		break;

		case "FL7_s16":
			chrDisableReloadTolocation = true;
			FL7_Cumana("reload1_back");
			FL7_CumanaEnemy(3, "reload3_back");
			
			LAi_group_SetCheck("FL_EnemyFight", "FL7_s17");
		break;

		case "FL7_s17":
			Delay_DeleteGroup("FL_EnemyFight");
			chrDisableReloadTolocation = false;

			pchar.quest.FL7s17.win_condition.l1 = "location";
			pchar.quest.FL7s17.win_condition.l1.location = "Cumana_Jungle_02";
			pchar.quest.FL7s17.win_condition = "FL7_s18";
		break;

		case "FL7_s18":
			chrDisableReloadTolocation = true;
			FL7_Cumana("reload2_back");
			FL7_CumanaEnemy(5, "reload1_back");
			
			LAi_group_SetCheck("FL_EnemyFight", "FL7_s19");
		break;

		case "FL7_s19":
			Delay_DeleteGroup("FL_EnemyFight");
			chrDisableReloadTolocation = false;

			pchar.quest.FL7s19.win_condition.l1 = "location";
			pchar.quest.FL7s19.win_condition.l1.location = "Cumana_Jungle_03";
			pchar.quest.FL7s19.win_condition = "FL7_s20";
		break;

		case "FL7_s20":
			chrDisableReloadTolocation = true;
			FL7_Cumana("reload1_back");
			FL7_CumanaEnemy(7, "reload2_back");
			
			LAi_group_SetCheck("FL_EnemyFight", "FL7_s21");
		break;

		case "FL7_s21":
			Delay_DeleteGroup("FL_EnemyFight");
			chrDisableReloadTolocation = false;

			pchar.quest.FL7s21.win_condition.l1 = "location";
			pchar.quest.FL7s21.win_condition.l1.location = "Shore19";
			pchar.quest.FL7s21.win_condition = "FL7_s22";
		break;

		case "FL7_s22":
			for(i=1;i<5;i++)
			{	
				iChar = GetCharacterIndex("FL_our_sold_"+i);
				if(iChar != -1) SetLifeDay(&characters[iChar],0);
			}

			for(i=1;i<3;i++)
			{
				iChar = GetCharacterIndex("FL_indian_"+i);
				if(iChar != -1) SetLifeDay(&characters[iChar],0);
			}

			// логиним Фуше
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "sea");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL7_s23", -1, 0);
		break;

		case "FL7_s23":
			SetTownCapturedState("Cumana", false);
			DeleteAttribute(pchar, "NoExplose");
			DeleteAttribute(pchar, "EncountersGen");
			QuestOpenSeaExit();

			pchar.quest.FL7s23.win_condition.l1 = "location";
			pchar.quest.FL7s23.win_condition.l1.location = "Cumana";
			pchar.quest.FL7s23.win_condition = "FL7_s24";
			AddQuestRecord("FL7", "5");
		break;

		case "FL7_s24":
			ChangeCharacterAddressGroup(CharacterFromID("JozephFushe"), "none", "", "");
			bQuestDisableMapEnter = true;

			for(i=0;i<6;i++) 
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
				chr.id = "FL_spa_capitan_"+i;
				chr.rank = (sti(pchar.rank)+MOD_SKILL_ENEMY_RATE);
			}

			FantomMakeCoolSailor(CharacterFromID("FL_spa_capitan_0"), SHIP_WARSHIP, "Сан Грегорио", CANNON_TYPE_CANNON_LBS24, 90, 90, 90);
			FantomMakeCoolSailor(CharacterFromID("FL_spa_capitan_1"), SHIP_GALEON, "Эсмеральда", CANNON_TYPE_CANNON_LBS12, 80, 80, 80);
			FantomMakeCoolSailor(CharacterFromID("FL_spa_capitan_2"), SHIP_GALEON, "Ауроник", CANNON_TYPE_CANNON_LBS12, 80, 80, 80);
			FantomMakeCoolSailor(CharacterFromID("FL_spa_capitan_3"), SHIP_GALEON_H, "дель Хункаль", CANNON_TYPE_CANNON_LBS18, 70, 70, 70);
			FantomMakeCoolSailor(CharacterFromID("FL_spa_capitan_4"), SHIP_GALEON_H, "Конде де Регла", CANNON_TYPE_CANNON_LBS18, 70, 70, 70);
			FantomMakeCoolSailor(CharacterFromID("FL_spa_capitan_5"), SHIP_GALEON_L, "Сан Рафаэль", CANNON_TYPE_CANNON_LBS12, 60, 60, 60);
			
			sGroup = "FL_Spa_Attack";
			Group_FindOrCreateGroup(sGroup);
			Group_SetType(sGroup, "war");
			
			for(i=0;i<6;i++) Group_AddCharacter(sGroup, "FL_spa_capitan_"+i);
			
			Group_SetGroupCommander(sGroup, "FL_spa_capitan_0");
			Group_SetPursuitGroup(sGroup, PLAYER_GROUP);
			Group_SetTaskAttack(sGroup, PLAYER_GROUP);
			Group_SetAddress(sGroup, "Cumana", "", "");
			Group_LockTask(sGroup);

			pchar.quest.FL7s24.win_condition.l1 = "Group_Death";
			pchar.quest.FL7s24.win_condition.l1.group = sGroup;
			pchar.quest.FL7s24.win_condition = "FL7_s25";
		break;

		case "FL7_s25":
			bQuestDisableMapEnter = false;
			pchar.quest.FL7s25.win_condition.l1 = "MapEnter";
            pchar.quest.FL7s25.win_condition = "FL7_s26";
		break;

		case "FL7_s26":
			iChar = GetCharacterIndex("JozephFushe");
			if(iChar == -1)
			{
				Log_Info("Капитан Фуше погиб!!!");
				AddQuestRecord("FL7", "6");
				SetQuestHeaderColor("FL7", gray);
				CloseQuestHeader("FL7");
				break;
			}

			PostVideoAndQuest("storm", 100, "FL7_s27");
		break;

		case "FL7_s27":
			Pchar.GenQuest.Hunter2Pause = true;
			chrDisableReloadTolocation = true;
			pchar.location.from_sea = "Shore59";
			setCharacterShipLocation(pchar, "Shore59");
			DoQuestReloadToLocation("Shore59", "reload", "sea", "FL7_s28");
		break;

		case "FL7_s28":
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL7_s29", -1, 0);
		break;

		case "FL7_s29":
			DoQuestCheckDelay("FL7_s30", 0.5);
		break;

		case "FL7_s30":
			AddDataToCurrent(0,0,6);
			SetCurrentTime(7,18);
			RefreshLandTime();
			SetLaunchFrameFormParam("Прошло около недели...", "FL7_s31", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL7_s31":
			LAi_ActorDialog(CharacterFromID("JozephFushe"), pchar, "FL7_s32", -1, 0);
		break;

		case "FL7_s32":
			characters[GetCharacterIndex("JozephFushe")].location = "none";
			chrDisableReloadTolocation = false;

			pchar.quest.FL7s32.win_condition.l1 = "location";
			pchar.quest.FL7s32.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FL7s32.win_condition = "FL7_s33";
		break;

		case "FL7_s33":
			iChar = GetCharacterIndex("JozephFushe");
			if(iChar == -1)
			{
				Log_Info("Капитан Фуше погиб!!!");
				AddQuestRecord("FL7", "6");
				SetQuestHeaderColor("FL7", gray);
				CloseQuestHeader("FL7");
				break;
			}
			
			chr = GetCharacter(iChar);
			if(IsCompanion(chr)) RemoveCharacterCompanion(pchar, chr);
			RemovePassenger(pchar, chr);

			pchar.quest.FL7s33.win_condition.l1 = "location";
			pchar.quest.FL7s33.win_condition.l1.location = "FortFrance_store";
			pchar.quest.FL7s33.win_condition = "FL7_s34";
		break;

		case "FL7_s34":
			chr = CharacterFromID("FL_Mary");
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto3");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL7_s35", -1, 0);
		break;

		case "FL7_s35":
			DoQuestCheckDelay("FL7_s36", 0.5);
		break;

		case "FL7_s36":
			AddDataToCurrent(0,0,10);
			SetCurrentTime(11,21);
			RefreshLandTime();
			SetLaunchFrameFormParam("Прошло 10 дней...", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("FortFrance_church", "goto", "goto3", "FL7_s37");
			LaunchFrameForm();
		break;

		case "FL7_s37":
			StartQuestMovie(false, false, true);
			locCameraToPos(-8,3,3,0);
			

			LAi_SetActorType(pchar);
			chr = CharacterFromID("FL_Mary");
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto4");
			LAi_SetActorType(chr);

			chr = GetCharacter(NPC_GenerateCharacter("FL_priest", "priest", "man", "man_B", 1, FRANCE, 0, false));
			ChangeCharacterAddressGroup(chr, pchar.location, "barmen", "bar1");
			LAi_SetPriestType(chr);

			for(i=7; i<16; i++)FreeSitlocator("FortFrance_church", "sit"+i);

			chr = CharacterFromID("JozephFushe");
			chr.nonTable = true;
			ChangeCharacterAddressGroup(chr, pchar.location, "sit", "sit11");
			LAi_SetSitType(chr);

			chr = CharacterFromID("FL_granie");
			chr.nonTable = true;
			ChangeCharacterAddressGroup(chr, pchar.location, "sit", "sit12");
			LAi_SetSitType(chr);

			chr = CharacterFromID("FL_ElizabetBrulua");
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto1");
			LAi_SetStayType(chr);
			
			chr2 = CharacterFromID("FortFrance_trader");
			chr = GetCharacter(NPC_GeneratePhantomCharacter("citizen", FRANCE, MAN, 0));
			chr.model = chr2.model;
			chr.nonTable = true;
			ChangeCharacterAddressGroup(chr, pchar.location, "sit", "sit9");
			LAi_SetSitType(chr);

			chr2 = CharacterFromID("FortFrance_mayor");
			chr = GetCharacter(NPC_GeneratePhantomCharacter("citizen", FRANCE, MAN, 0));
			chr.nonTable = true;
			chr.model = chr2.model;
			ChangeCharacterAddressGroup(chr, pchar.location, "sit", "sit10");
			LAi_SetSitType(chr);

			DoQuestCheckDelay("FL7_s38", 15.0);
		break;

		case "FL7_s38":
			locCameraFollow();
			EndQuestMovie();
			LAi_SetPlayerType(pchar);

			ChangeCharacterAddressGroup(CharacterFromID("FL_granie"), "none", "", "");
			
			chr = CharacterFromID("JozephFushe");
			ChangeCharacterAddressGroup(chr, "Tortuga_houseF3", "barmen", "stay");
			LAi_SetBarmanType(chr);
			ChangeCharacterAddressGroup(CharacterFromID("FL_ElizabetBrulua"), "none", "", "");
			
			locations[FindLocation("FortFrance_town")].reload.l18.disable = 0;

			DoQuestReloadToLocation("FortFrance_houseS2", "goto", "goto4", "FL7_s39");
			pchar.MainQuest.FL_Maried = true;
		break;

		case "FL7_s39":
			DoQuestCheckDelay("FL7_s39a", 2.0);
		break;

		case "FL7_s39a":
			AddDataToCurrent(0,0,4);
			SetCurrentTime(16,41);
			RefreshLandTime();
			SetLaunchFrameFormParam("Через несколько дней...", "FL7_s40", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL7_s40":
			chr = CharacterFromID("FL_Mary");
			chr.lastname = "де Граммон";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto2");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL7_s41", -1, 0);
		break;

		case "FL7_s41":
			chr = CharacterFromID("FL_Mary");
			chr.location.locator = "stay";
			chr.location.group = "barmen";
			LAi_SetBarmanType(chr);

			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
			AddQuestRecord("FL7", "7");

			locations[FindLocation("FortFrance_houseS2")].NotSpawnItem = true;
			locations[FindLocation("FortFrance_houseS2_room")].NotSpawnItem = true;
			locations[FindLocation("FortFrance_houseS2_residence")].NotSpawnItem = true;

			locations[FindLocation("FortFrance_houseS2_room")].models.day.locators = "mediumhouse03_Plocators";
			locations[FindLocation("FortFrance_houseS2_room")].models.night.locators = "mediumhouse03_PNlocators";
		break;

//====================================================================================================================
//	Le bleu de France
//====================================================================================================================
		case "FL8_s1":
			DoQuestCheckDelay("FL8_s2", 0.5);
		break;

		case "FL8_s2":
			AddTimeToCurrent(1,11);
			SetLaunchFrameFormParam("Прошло около часа...", "FL8_s3", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL8_s3":
			chr = CharacterFromID("JozephFushe");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL8_s4", -1, 0);
		break;

		case "FL8_s4":
			DoReloadCharacterToLocation("Tortuga_town", "reload", "houseF3");
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 1;
			pchar.MainQuest = "FL8_s4";
			AddQuestRecord("FL7", "8");
		break;

		case "FL8_s5":
			pchar.MainQuest = "FL8_s5";
			SetQuestHeaderColor("FL7", gray);
			CloseQuestHeader("FL7");

			SetQuestHeader("FL8");
			SetQuestHeaderColor("FL8", yellow);
			AddQuestRecord("FL8", "1");

			chr = GetCharacter(NPC_GenerateCharacter("FL_CaptainHank", "officer_3", "man", "man", sti(pchar.rank), PIRATE, -1, true));
			chr.name = "Капитан";
			chr.lastname = "Хэнк";
			FantomMakeCoolSailor(chr, SHIP_CORVETTE_H, "Неустрашимый", CANNON_TYPE_CANNON_LBS12, 50, 50, 50);
			SetGoodsInitNull(chr);
			chr.Ship.Crew.Quantity = 0;
			chr.AlwaysFriend = true;
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;
			LAi_SetImmortal(chr, true);
			
			sGroup = "FL_CaptainHank";
			Group_FindOrCreateGroup(sGroup);
			Group_SetType(sGroup, "trade");
			Group_AddCharacter(sGroup, chr.id);
			Group_SetGroupCommander(sGroup, chr.id);
			Group_SetTaskNone(sGroup);
			Group_SetAddress(sGroup, "Caiman", "Quest_Ships", "Quest_ship_1");
			Group_LockTask(sGroup);
			
			SetCharacterRelationBoth(sti(chr.index), GetMainCharacterIndex(), RELATION_FRIEND);
		break;

		case "FL8_s6":
			LAi_Fade("", "");
			for(i=0;i<4;i++) LAi_KillCharacter(CharacterFromID("FL_dead_men_"+i));
		break;

		case "FL8_s7":
			chr = CharacterFromID("FL_granie");
			chr.dialog.currentnode = "63";
			LAi_SetActorType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto5");
			LAi_ActorDialog(chr, pchar, "FL8_s8", -1, 0);
		break;

		case "FL8_s8":
			pchar.MainQuest = "FL8_s8";
			DeleteAttribute(pchar, "MainQuest.FL8s5");

			chr = CharacterFromID("FL_granie");
			chr.location = "none";

			SetLifeDay(CharacterFromID("FL_CaptainHank"), 0);
			AddQuestRecord("FL8", "2");
		break;

		case "FL8_s9":
			pchar.MainQuest = "";
			AddQuestRecord("FL8", "3");

			pchar.quest.FL8s9.win_condition.l1 = "location";
			pchar.quest.FL8s9.win_condition.l1.location = "Havana_town";
			pchar.quest.FL8s9.win_condition = "FL8_s10";
		break;

		case "FL8_s10":
			chrDisableReloadTolocation = true;
			chr = CharacterFromID("FL_granie");
			LAi_LoginInCaptureTown(chr, true);
			LAi_SetActorType(chr);
			chr.dialog.currentnode = "74";
			ChangeCharacterAddressGroup(chr, "Havana_town", "goto", "goto21");
			LAi_ActorDialog(chr, pchar, "FL8_s11", -1, 0.0);
		break;

		case "FL8_s11":
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			chr = GetCharacter(NPC_GenerateCharacter("FL_Anna", "horse06", "woman", "towngirl", 3, SPAIN, -1, false));
			chr.name = "Анна";
			chr.lastname = characters[GetCharacterIndex("Havana_mayor")].lastname;
			LAi_SetActorType(chr);
			LAi_LoginInCaptureTown(chr, true);
			ChangeCharacterAddressGroup(chr, "Havana_town", "reload", "reload3_back");
			LAi_ActorFollow(chr, CharacterFromID("FL_granie"), "FL8_s12", -1);
		break;

		case "FL8_s12":
			chr = CharacterFromID("FL_granie");
			chr2 = CharacterFromID("FL_Anna");
			LAi_ActorTurnToCharacter(chr, chr2);
			LAi_ActorDialog(chr2, chr, "", -1, 0);
			LAi_ActorTurnToCharacter(pchar, chr2);

			pchar.name = "Девушка и Гранье";
			pchar.lastname = "";
			DoQuestCheckDelay("FL8_s13", 0.5);
		break;

		case "FL8_s13":
			pchar.dialog.currentnode = "FL8_1";
			LAi_ActorSelfDialog(pchar, "FL8_s14");
		break;

		case "FL8_s14":
			pchar.name = "Мишель";
			pchar.lastname = "де Граммон";
			chr = CharacterFromID("FL_Anna");
			LAi_SetActorType(chr);
			LAi_ActorRunToLocation(chr, "reload", "reload3_back", "none", "", "", "", -1);
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			chr = CharacterFromID("FL_granie");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL8_s15", 1, 0);
		break;

		case "FL8_s15":
			characters[GetCharacterIndex("FL_granie")].location = "none";
			chrDisableReloadTolocation = false;
			AddQuestRecord("FL8", "4");

			chr = GetCharacter(NPC_GenerateCharacter("FL_PedroSangre", "officer_5", "man", "man", 10, PIRATE, -1, true));
			FantomMakeCoolSailor(chr, SHIP_XEBEC, "Слепой пью", CANNON_TYPE_CANNON_LBS9, 50, 50, 50);
			chr.dialog.filename = "Quest\FranceLine\PedroSangre.c";
			chr.name = "Педро";
			chr.lastname = "Сангре";
			chr.DeckDialogNode = "first time";
			chr.AlwaysFriend = true;
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;
			LAi_SetImmortal(chr, true);

			sGroup = "Sea_FL_PedroSangre";
			Group_FindOrCreateGroup(sGroup);
			Group_SetType(sGroup, "trade");
			Group_AddCharacter(sGroup, chr.id);
			Group_SetGroupCommander(sGroup, chr.id);
			Group_SetTaskNone(sGroup);
			Group_SetAddress(sGroup, "Cuba2", "IslandShips1", "ship_1");
			Group_LockTask(sGroup);
		break;

		case "FL8_s16":
			chr = CharacterFromID("FL_granie");
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			LAi_SetActorType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto5");
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL8_s17", -1, 0);
		break;

		case "FL8_s17":
			AddQuestRecord("FL8", "5");
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			chr = CharacterFromID("FL_PedroSangre");
			chr.DeckDialogNode = "5";
			ChangeCharacterAddressGroup(CharacterFromID("FL_granie"), "none" , "", "");
			Return2SeaAfterCabin();
			
			pchar.quest.FL8s17.win_condition.l1 = "location";
			pchar.quest.FL8s17.win_condition.l1.location = "Cuba_CaveEntrance";
			pchar.quest.FL8s17.win_condition = "FL8_s18";
		break;

		case "FL8_s18":
			chrDisableReloadTolocation = true;
			for(i=4;i<7;i++)
			{
				chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 0));
				FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 90, 90, "", "", 200.0);
				ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload1_back");
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			}

			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("FL_EnemyFight", "FL8_s19");
		break;

		case "FL8_s19":
			Delay_DeleteGroup("FL_EnemyFight");
			chrDisableReloadTolocation = false;
			chr = GetCharacter(NPC_GenerateCharacter("FL_Garcia", "officer_18", "man", "man", 1, PIRATE, -1, false));
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 99, 99, "", "", 500.0);
			chr.name = "Хуан";
			chr.lastname = "Гарсиа";
			chr.dialog.filename = "Quest\FranceLine\Garcia.c";
			chr.greeting = "are_you_pirate";
			ChangeCharacterAddressGroup(chr, "Cuba_Grot", "monsters", "monster2");
			LAi_SetWarriorTypeNoGroup(chr);
			LAi_warrior_SetStay(chr, true);
			LAi_group_MoveCharacter(chr, "FL_Garcia_group");
			LAi_SetCheckMinHP(chr, 10.0, true, "FL8_s20");
		break;
		
		case "FL8_s19a": // это если решили поболтать с ним
			LAi_group_SetRelation("FL_Garcia_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_Garcia_group", LAI_GROUP_PLAYER, true);
		break;

		case "FL8_s20":
			chr = CharacterFromID("FL_Garcia");
			chr.dialog.currentnode = "2";
			chr.greeting = "vi_pobedili";
			LAi_SetActorType(chr);
			LAi_SetFightMode(pchar, false);
			LAi_ActorDialogNow(chr, pchar, "FL8_s21", 0);
		break;

		case "FL8_s21":
			GiveItem2Character(pchar, "BlueHope");
			AddQuestRecord("FL8", "6");
			SetLifeDay(CharacterFromID("FL_Garcia"), 0);
			SetLifeDay(CharacterFromID("FL_PedroSangre"), 0);
			pchar.MainQuest = "FL8_s21";
		break;

		case "FL8_s22":
			GiveItem2Character(pchar, "FQ_order");
			pchar.MainQuest = "FL8_s22";
			AddQuestRecord("FL8", "7");
		break;

		case "FL8_s23":
			pchar.MainQuest = "";
			chr = GetCharacter(NPC_GenerateCharacter("FL_Esteban", "pirate_10", "man", "man", 10, SPAIN, -1, false));
			chr.name = "Эстебан";
			chr.lastname = "";
			chr.dialog.filename = "Quest\FranceLine\Esteban.c";
			chr.greeting = "polojenie_beznadejno";
			LAi_SetStayType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto9");
		break;

		case "FL8_s24":
			LAi_Fade("","");
			chr = CharacterFromID("FL_Esteban");
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto23");
			LAi_SetActorType(chr);
			LAi_ActorFollowEverywhere(chr, "", -1);

			pchar.quest.FL8s24.win_condition.l1 = "location";
			pchar.quest.FL8s24.win_condition.l1.location = "Tortuga_exittown";
			pchar.quest.FL8s24.win_condition = "FL8_s25";
		break;

		case "FL8_s25":
			chrDisableReloadTolocation = true;
			LAi_ActorDialog(CharacterFromID("FL_Esteban"), pchar, "FL8_s26", -1, 0.5);
		break;

		case "FL8_s26":
			LAi_ActorRunToLocation(CharacterFromID("FL_Esteban"), "reload", "reload2_back", "none", "", "", "FL8_s27", -1);
		break;

		case "FL8_s27":
			chrDisableReloadTolocation = false;
			LAi_SetBarmanType(CharacterFromID("JozephFushe"));
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
			AddQuestRecord("FL8", "8");
		break;

		case "FL8_s28":
			DoReloadCharacterToLocation("Tortuga_town", "reload", "houseF3");
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 1;
			SetTimerConditionParamEx("FL8s28", "FL9_s1", 0, 2, 0);
			AddQuestRecord("FL8", "9");
		break;

//====================================================================================================================
//	Поход
//====================================================================================================================
		case "FL9_s1":
			pchar.quest.FL9s1.win_condition.l1 = "location";
			pchar.quest.FL9s1.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FL9s1.win_condition = "FL9_s2";
		break;

		case "FL9_s2":
			chrDisableReloadTolocation = true;
			chr = GetOurSailor("FL_tmp_Sailor");
			chr.dialog.filename = "Quest\FranceLine\sailor3.c";
			chr.greeting = "soobshenie";
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL9_s3", -1, 0);
		break;

		case "FL9_s3":
			LAi_ActorGoToLocation(CharacterFromID("FL_tmp_Sailor"), "reload", "reload4_back", "none", "", "", "", -1);
		break;

		case "FL9_s4":
			chrDisableReloadTolocation = false;
			pchar.quest.FL9s4.win_condition.l1 = "location";
			pchar.quest.FL9s4.win_condition.l1.location = "Tortuga_town";
			pchar.quest.FL9s4.win_condition = "FL9_s5";

			chr = CharacterFromID("Tortuga_mayor");
			chr.model = "huber_fra";
			chr.name = "Пьер-Поль Тарен";
			chr.lastname = "де Кюсси";
			chr.quest.meeting = 0;
		
			SetQuestHeaderColor("FL8", gray);
			CloseQuestHeader("FL8");
			SetQuestHeader("FL9");
			SetQuestHeaderColor("FL9", yellow);
			AddQuestRecord("FL9", "1");
		break;

		case "FL9_s5":
			chrDisableReloadTolocation = true;
			chr = CharacterFromID("FL_nikolas");
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL9_s6", -1, 0.5);
		break;

		case "FL9_s6":
			FreeSitLocator("Tortuga_tavern", "sit_base3");
			FreeSitLocator("Tortuga_tavern", "sit_front3");
			LAi_ActorRunToLocation(CharacterFromID("FL_nikolas"), "reload", "reload4_back", "Tortuga_tavern", "sit", "sit_base3", "FL9_s7", -1);
		break;

		case "FL9_s7":
			DoQuestReloadToLocation("Tortuga_tavern", "sit", "sit_front3", "FL9_s8");
		break;

		case "FL9_s8":
			chr = CharacterFromID("FL_nikolas");
			LAi_ActorSetSitMode(chr);
			LAi_SetSitType(pchar);
			LAi_ActorDialogNow(chr, pchar, "FL9_s9", 0.5)
		break;

		case "FL9_s9":
			LAi_Fade("","FL9_s10");
		break;

		case "FL9_s10":
			ChangeCharacterAddressGroup(CharacterFromID("FL_nikolas"), "none", "", "");
			ChangeCharacterAddressGroup(pchar, pchar.location, "tables", "stay2");
			LAi_SetPlayerType(pchar);

			AddQuestRecord("FL9", "2");
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
			chrDisableReloadTolocation = false;
		break;

		case "FL9_s11":
			DoQuestCheckDelay("FL9_s12", 0.5);
		break;

		case "FL9_s12":
			AddTimeToCurrent(1,0);
			SetLaunchFrameFormParam("Через час...", "FL9_s13", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL9_s13":
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, CharacterFromID("JozephFushe"), "FL9_s14", 0.5);
		break;

		case "FL9_s14":
			LAi_SetPlayerType(pchar);
			DoReloadCharacterToLocation("Tortuga_town", "reload", "houseF3");
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 1;
			SetTimerConditionParamEx("FL9s14", "FL9_s15", 0, 0, 14);
			AddQuestRecord("FL9", "3");
		break;

		case "FL9_s15":
			chr = CharacterFromID("FL_nikolas");
			FantomMakeCoolSailor(chr, SHIP_WARSHIP, "Phenix", CANNON_TYPE_CANNON_LBS24, 80, 70, 70);
			
			chr.AlwaysFriend = true;
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;
			LAi_SetImmortal(chr, true);
			ChangeCharacterAddressGroup(chr, "Shore34", "goto", "goto13");
			LAi_SetActorType(chr);
			ship = GetRealShip(sti(chr.ship.type));
			ship.ship.upgrades.hull = 4;
			
			chr = CharacterFromID("FL_LoranDeGraff");
			FantomMakeCoolSailor(chr, SHIP_FRIGATE_B, "Lune", CANNON_TYPE_CANNON_LBS24, 80, 70, 70);
			chr.ship.upgrades.hull = 2;
			chr.AlwaysFriend = true;
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;
			LAi_SetImmortal(chr, true);
			ChangeCharacterAddressGroup(chr, "Shore34", "goto", "goto14");
			LAi_SetActorType(chr);
			ship = GetRealShip(sti(chr.ship.type));
			ship.ship.upgrades.hull = 2;

			chr = GetCharacter(NPC_GenerateCharacter("FL_Capitan_1", "off_fra_2", "man", "man", sti(pchar.rank), FRANCE, -1, true));
			FantomMakeCoolSailor(chr, SHIP_FRIGATE, "Vengeur", CANNON_TYPE_CANNON_LBS18, 80, 70, 70);
			chr.ship.upgrades.hull = 1;
			chr.AlwaysFriend = true;
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;
			ChangeCharacterAddressGroup(chr, "Shore34", "goto", "goto7");
			LAi_SetActorType(chr);
			ship = GetRealShip(sti(chr.ship.type));
			ship.ship.upgrades.hull = 1;

			chr = GetCharacter(NPC_GenerateCharacter("FL_Capitan_2", "officer_9", "man", "man", sti(pchar.rank), FRANCE, -1, true));
			FantomMakeCoolSailor(chr, SHIP_CORVETTE_H, "Mort", CANNON_TYPE_CANNON_LBS12, 80, 70, 70);
			chr.ship.upgrades.hull = 1;
			chr.AlwaysFriend = true;
			chr.CompanionEnemyEnable = false;
			chr.Abordage.Enable = false;
			ship = GetRealShip(sti(chr.ship.type));
			ship.ship.upgrades.hull = 1;

			ChangeCharacterAddressGroup(chr, "Shore34", "goto", "goto5");
			LAi_SetActorType(chr);
			
			pchar.quest.FL9s15.win_condition.l1 = "location";
			pchar.quest.FL9s15.win_condition.l1.location = "Shore34";
			pchar.quest.FL9s15.win_condition = "FL9_s16";
		break;

		case "FL9_s16":
			chrDisableReloadTolocation = true;
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			chr = CharacterFromID("FL_nikolas");
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL9_s17", -1, 0.5);
		break;

		case "FL9_s17":
			chr2 = CharacterFromID("Tortuga_mayor");
			chr = GetOurSailor("FL_PhantomHuber");
			chr.model = chr2.model;
			chr.name = chr2.name;
			chr.lastname = chr2.lastname;
			chr.dialog.filename = "Quest\FranceLine\TortugaMayor.c";
			chr.greeting = "respect_hovernor";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto8");
			LAi_SetActorType(chr);
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL9_s18", -1, 0.5);
			chr2.quest.meeting = 1;
		break;

		case "FL9_s18":
			chr = CharacterFromID("FL_PhantomHuber");
			LAi_SetActorType(chr);
			LAi_ActorGoToLocation(chr, "goto", "goto8", "none", "", "", "", -1);
			chr = CharacterFromID("FL_nikolas");
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL9_s19", -1, 0.5);
		break;

		case "FL9_s19":
			chrDisableReloadTolocation = false;
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("FL9", "4");
			
			sGroup = "FL_Friends";
			Group_FindOrCreateGroup(sGroup);
			Group_SetType(sGroup, "war");
			
			chr = CharacterFromID("FL_nikolas");
			chr.location = "none";
			Group_AddCharacter(sGroup, chr.id);
			Group_SetGroupCommander(sGroup, chr.id);

			chr = CharacterFromID("FL_LoranDeGraff");
			chr.location = "none";
			Group_AddCharacter(sGroup, chr.id);

			chr = CharacterFromID("FL_Capitan_1");
			chr.location = "none";
			Group_AddCharacter(sGroup, chr.id);

			chr = CharacterFromID("FL_Capitan_2");
			chr.location = "none";
			Group_AddCharacter(sGroup, chr.id);
						
			Group_SetPursuitGroup(sGroup, PLAYER_GROUP);
			Group_SetAddress(sGroup, "SantaCatalina", "", "");
			
			// Испанский флот в водах Санта-Каталина (пока не оч. крутой)
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
			chr.id = "Spa_Cap_0";
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 99, 99, "", "", 500.0);
			FantomMakeCoolSailor(chr, SHIP_BATTLESHIP, "", CANNON_TYPE_CANNON_LBS24, 99, 99, 99);

			sGroup = "FL_SpaAttack";
			Group_FindOrCreateGroup(sGroup);
			Group_SetType(sGroup, "war");
			Group_AddCharacter(sGroup, chr.id);
			Group_SetGroupCommander(sGroup, chr.id);

			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
			chr.id = "Spa_Cap_1";
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 99, 99, "", "", 500.0);
			FantomMakeCoolSailor(chr, SHIP_GALEON, "", CANNON_TYPE_CANNON_LBS24, 99, 99, 99);
			Group_AddCharacter(sGroup, chr.id);

			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, -1));
			chr.id = "Spa_Cap_2";
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 99, 99, "", "", 500.0);
			FantomMakeCoolSailor(chr, SHIP_FRIGATE, "", CANNON_TYPE_CANNON_LBS18, 99, 99, 99);
			Group_AddCharacter(sGroup, chr.id);

			Group_SetPursuitGroup(sGroup, PLAYER_GROUP);
			Group_SetAddress(sGroup, "SantaCatalina", "", "");
			
			pchar.quest.FL9s19.win_condition.l1 = "location";
			pchar.quest.FL9s19.win_condition.l1.location = "SantaCatalina";
			pchar.quest.FL9s19.win_condition = "FL9_s20";
		break;

		case "FL9_s20":
			bQuestDisableMapEnter = true;
			Island_SetReloadEnableGlobal("SantaCatalina", false);

			Group_SetTaskAttack("FL_SpaAttack", PLAYER_GROUP);
			Group_LockTask("FL_SpaAttack");

			Group_SetTaskAttack("FL_Friends", "FL_SpaAttack");
			Group_LockTask("FL_Friends");

			pchar.quest.FL9s20.win_condition.l1 = "Group_Death";
			pchar.quest.FL9s20.win_condition.l1.group = "FL_SpaAttack";
			pchar.quest.FL9s20.win_condition = "FL9_s21";
		break;

		case "FL9_s21":
			i = GetCharacterIndex("FL_nikolas");
			characters[i].DeckDialogNode = "51";
			Sea_DeckBoatLoad(i);

			pchar.quest.FL9s21.win_condition.l1 = "location";
			pchar.quest.FL9s21.win_condition.l1.location = "Deck_Near_Ship";
			pchar.quest.FL9s21.win_condition = "FL9_s22";
		break;

		case "FL9_s22":
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, CharacterFromID("FL_nikolas"), "FL9_s23", -1, 0.5);
		break;

		case "FL9_s23":
			EndQuestMovie();
			chr = CharacterFromID("FL_nikolas");
			DeleteAttribute(chr, "DeckDialogNode");
			LAi_SetPlayerType(pchar);
			Return2SeaAfterCabin();
			DoQuestCheckDelay("FL9_s24", 1.0);
		break;

		case "FL9_s24":
			Group_SetTaskRunaway("FL_Friends", PLAYER_GROUP);
			Group_LockTask("FL_Friends");
			
			Island_SetReloadEnableGlobal("SantaCatalina", true);

			pchar.quest.FL9s24.win_condition.l1 = "Fort_destroy";
			pchar.quest.FL9s24.win_condition.l1.character = "SantaCatalina Fort Commander";
			pchar.quest.FL9s24.win_condition = "FL9_s25";
		break;

		case "FL9_s25":
			bQuestDisableMapEnter = false;
			pchar.MainQuest = "FL9_s25";
		break;

		case "FL9_s26":
			pchar.MainQuest = "FL9_s26";
			chr = CharacterFromID("SantaCatalina_mayor");
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, chr, "FL9_s27", 0.5);
		break;

		case "FL9_s27":
			pchar.MainQuest = "";
			LAi_SetPlayerType(pchar);
			
			pchar.quest.FL9s27.win_condition.l1 = "location";
			pchar.quest.FL9s27.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.FL9s27.win_condition = "FL9_s28";
		break;

		case "FL9_s28":
			chrDisableReloadTolocation = true;
			chr = CharacterFromID("FL_LoranDeGraff");
			chr.dialog.filename = "Quest\FranceLine\deGraf.c";
			chr.greeting = "spainsh_busters";
			LAi_LoginInCaptureTown(chr, true);
			LAi_SetActorType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto21");
			LAi_ActorDialog(chr, pchar, "FL9_s29", -1, 0.5);
		break;

		case "FL9_s29":
			DoQuestCheckDelay("FL9_s30", 0.5);
		break;

		case "FL9_s30":
			AddTimeToCurrent(2,0);
			RefreshLandTime();
			ChangeCharacterAddressGroup(CharacterFromID("FL_LoranDeGraff"), "none", "", "");
			SetLaunchFrameFormParam("Прошло 2 часа...", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", "goto24", "FL9_s32");
			LaunchFrameForm();
		break;

		case "FL9_s32":
			StartQuestMovie(false, false, true);
			LAi_SetActorType(pchar);

			chr = GetCharacter(NPC_GeneratePhantomCharacter("citizen", SPAIN, MAN, -1));
			chr.id = "FL_Espinosa";
			chr.model = "Espinosa";
			chr.name = "Диего";
			chr.lastname = "Эспиноза";
			chr.dialog.filename = "Quest\FranceLine\Espinosa.c";
			chr.greeting = "hellow";
			LAi_LoginInCaptureTown(chr, true);
			LAi_SetActorType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload7_back");
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL9_s33", -1, 0.5);

			chr2 = GetOurSailor("FL_OurSailor");
			LAi_LoginInCaptureTown(chr2, true);
			LAi_SetActorType(chr2);
			ChangeCharacterAddressGroup(chr2, pchar.location, "reload", "reload7_back");
			LAi_ActorFollow(chr2, chr, "", -1);
		break;

		case "FL9_s33":
			DoQuestCheckDelay("FL9_s34", 0.5);
		break;

		case "FL9_s34":
			EndQuestMovie();
			AddTimeToCurrent(1,0);
			RefreshLandTime();
			SetLaunchFrameFormParam("Через час...", "FL9_s35", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL9_s35":
			chr = CharacterFromID("FL_Espinosa");
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialogNow(chr, pchar, "FL9_s36", 0.5);
		break;

		case "FL9_s36":
			DoQuestCheckDelay("FL9_s36a", 0.5);
		break;

		case "FL9_s36a":
			AddMoneyToCharacter(pchar, 250000);
			ChangeCharacterAddressGroup(CharacterFromID("FL_Espinosa"), "none", "", "");
			ChangeCharacterAddressGroup(CharacterFromID("FL_OurSailor"), "none", "", "");
			AddDataToCurrent(0,0,2);
			SetCurrentTime(8,11);
			RefreshLandTime();
			SetLaunchFrameFormParam("Прошло 2 дня...", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "reload", "reload3", "FL9_s37");
			LaunchFrameForm();
		break;

		case "FL9_s37":
			LAi_SetPlayerType(pchar);
			chr = GetOurSailor("FL_OurSailor2");
			chr.dialog.filename = "Quest\FranceLine\sailor4.c";
			chr.greeting = "spainsh_busters";
			LAi_LoginInCaptureTown(chr, true);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto3");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL9_s38", -1, 0.5);
		break;

		case "FL9_s38":
			AddQuestRecord("FL9", "5");
			DoQuestCheckDelay("FL9_s39", 0.5);
		break;

		case "FL9_s39":
			ChangeCharacterAddressGroup(CharacterFromID("FL_OurSailor2"), "none", "", "");
			AddTimeToCurrent(1,0);
			RefreshLandTime();
			SetLaunchFrameFormParam("Прошёл час...", "FL9_s40", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL9_s40":
			chr2 = CharacterFromID("FL_LoranDeGraff");
			chr = CharacterFromID("FL_nikolas");
			LAi_LoginInCaptureTown(chr, true);

			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto2");
			ChangeCharacterAddressGroup(chr2, pchar.location, "goto", "goto2");
			LAi_SetActorType(chr);
			LAi_SetActorType(chr2);
			LAi_ActorDialog(chr, pchar, "FL9_s41", -1, 0.5);
			LAi_ActorFollow(chr2, chr, "", -1);
		break;

		case "FL9_s41":
			LAi_Fade("FL9_s42", "");
		break;

		case "FL9_s42":
			ChangeCharacterAddressGroup(CharacterFromID("FL_LoranDeGraff"), "none", "", "");
			ChangeCharacterAddressGroup(CharacterFromID("FL_nikolas"), "none", "", "");

			chr = CharacterFromID("FL_Espinosa");
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "houseS1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL9_s43", -1, 0.5);

			for(i=0;i<2;i++)
			{
				chr2 = GetCharacter(NPC_GeneratePhantomCharacter("citizen", SPAIN, MAN, 0));
				chr2.id = "FL_tmp_sit_"+i;
				LAi_LoginInCaptureTown(chr2, true);
				ChangeCharacterAddressGroup(chr2, pchar.location, "reload", "houseS1");
				LAi_SetActorType(chr2);
				LAi_ActorFollow(chr2, chr, "", -1);
			}
		break;

		case "FL9_s43":
			DoQuestCheckDelay("FL9_s44", 0.5);
		break;

		case "FL9_s44":
			AddTimeToCurrent(0,30);
			RefreshLandTime();
			SetLaunchFrameFormParam("Через 30 минут...", "FL9_s45", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL9_s45":
			chr = CharacterFromID("FL_Espinosa");
			LAi_ActorDialog(chr, pchar, "FL9_s46", -1, 0.5);
		break;

		case "FL9_s46":
			DoQuestCheckDelay("FL9_s47", 0.5);
		break;

		case "FL9_s47":
			AddTimeToCurrent(2,0);
			RefreshLandTime();
			SetLaunchFrameFormParam("Прошло 2 часа...", "FL9_s48", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL9_s48":
			chr = CharacterFromID("FL_nikolas");
			PlaceCharacter(chr, "reload", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL9_s49", -1, 0.5);
		break;

		case "FL9_s49":
			i = FindLocation("SantaCatalina_town");
			locations[i].models.always.locators = "SantaCatalinaFL_locators";
			locations[i].models.day.charactersPatch = "SantaCatalina_patch_dayFL";
			locations[i].models.night.charactersPatch = "SantaCatalina_patch_nightFL";
			locations[i].models.always.koster = "Koster";

			DoQuestCheckDelay("FL9_s50", 0.5);
		break;

		case "FL9_s50":
			chr = CharacterFromID("FL_Espinosa");
			ChangeCharacterAddressGroup(chr, "none","","");
			SetLifeDay(chr, 0);
			ChangeCharacterAddressGroup(CharacterFromID("FL_nikolas"), "none","","");
			for(i=0;i<2;i++) ChangeCharacterAddressGroup(CharacterFromID("FL_tmp_sit_"+i), "none","","");
			AddTimeToCurrent(2,0);
			RefreshLandTime();
			SetLaunchFrameFormParam("Прошло 2 часа...", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam(pchar.location, "goto", "goto21", "FL9_s51");
			LaunchFrameForm();
		break;

		case "FL9_s51":
			Log_Info("Добыча поделена");
			AddMoneyToCharacter(pchar, -660000);
			chr = GetOurSailor("FL_tmp_sailor");
			chr.dialog.filename = "Quest\FranceLine\sailor5.c";
			chr.greeting = "soobshenie";
			LAi_LoginInCaptureTown(chr, true);
			PlaceCharacter(chr, "goto", "random_must_be_near");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL9_s52", -1, 0.5);
		break;

		case "FL9_s52":
			AddQuestRecord("FL9", "6");
			chr = CharacterFromID("FL_nikolas");
			LAi_LoginInCaptureTown(chr, true);
			LAi_SetActorType(chr);
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto16");
			LAi_ActorSetLayMode(chr);

			chr2 = CharacterFromID("FL_LoranDeGraff");
			LAi_SetActorType(chr2);
			LAi_LoginInCaptureTown(chr2, true);
			ChangeCharacterAddressGroup(chr2, pchar.location, "reload", "reload4_back");
			LAi_ActorFollow(chr2, chr, "FL9_s53", -1);

			for(i=0;i<2;i++)
			{
				chr = GetOurSailor("FL_tmp_sailor_"+i);
				LAi_SetActorType(chr);
				LAi_LoginInCaptureTown(chr, true);
				ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto18");
				LAi_ActorFollow(chr, chr2, "", -1);
			}
		break;

		case "FL9_s53":
			LAi_SetStayType(CharacterFromID("FL_LoranDeGraff"));
		break;

		case "FL9_s54":
			DoQuestCheckDelay("FL9_s55", 0.5);
		break;

		case "FL9_s55":
			ChangeCharacterAddressGroup(pchar, pchar.location, "goto", "goto20");
			ChangeCharacterAddressGroup(CharacterFromID("FL_tmp_sailor"), "none", "", "");
			ChangeCharacterAddressGroup(CharacterFromID("FL_LoranDeGraff"), "none", "", "");
			ChangeCharacterAddressGroup(CharacterFromID("FL_nikolas"), "none", "", "");
			for(i=0;i<2;i++) ChangeCharacterAddressGroup(CharacterFromID("FL_tmp_sailor_"+i), "none", "", "");

			AddTimeToCurrent(1,12);
			RefreshLandTime();
			SetLaunchFrameFormParam("Прошло около часа...", "FL9_s56", 2.0, 3.0);
			LaunchFrameForm();
		break;

		case "FL9_s56":
			chr = CharacterFromID("FL_granie");
			chr.dialog.currentnode = "83";
			LAi_SetActorType(chr);
			LAi_LoginInCaptureTown(chr, true);
			ChangeCharacterAddressGroup(chr, pchar.location, "quest", "quest1");
			LAi_ActorDialog(chr, pchar, "FL9_s57", -1, 0.5);
		break;

		case "FL9_s57":
			LAi_ActorRunToLocation(CharacterFromID("FL_granie"), "reload", "reload1_back", "none", "", "", "FL9_s58", -1);
			chr = CharacterFromID("FL_nikolas");
			LAi_SetImmortal(chr, false);
			SetCompanionIndex(pchar, -1, sti(chr.index));
			SetShipRemovable(chr, true);
			chr.CompanionEnemyEnable = false;

			AddQuestRecord("FL9", "7");
		break;

		case "FL9_s58":
			chrDisableReloadTolocation = false;
			pchar.quest.FL9s58.win_condition.l1 = "location";
			pchar.quest.FL9s58.win_condition.l1.location = "SantaCatalina";
			pchar.quest.FL9s58.win_condition = "FL9_s59";
		break;

		case "FL9_s59":
			i = FindLocation("SantaCatalina_town");
			locations[i].models.always.locators = "SantaCatalina_locators";
			locations[i].models.day.charactersPatch = "SantaCatalina_patch_day";
			locations[i].models.night.charactersPatch = "SantaCatalina_patch_night";
			DeleteAttribute(&locations[i], "models.always.koster");
			
			// Испанцы
			// 1
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, 0));
			chr.id = "Spa_Cap_0";
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 99, 99, "", "", 1000.0);
			FantomMakeCoolSailor(chr, SHIP_MANOWAR, "", CANNON_TYPE_CANNON_LBS24, 99, 99, 99);

			sGroup = "FL_SpaAttack";
			Group_FindOrCreateGroup(sGroup);
			Group_SetType(sGroup, "war");
			Group_AddCharacter(sGroup, chr.id);
			Group_SetGroupCommander(sGroup, chr.id);
			
			// 2
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, 0));
			chr.id = "Spa_Cap_1";
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 99, 99, "", "", 500.0);
			FantomMakeCoolSailor(chr, SHIP_BATTLESHIP_L, "", CANNON_TYPE_CANNON_LBS24, 99, 99, 99);
			Group_AddCharacter(sGroup, chr.id);
			
			// 3
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, 0));
			chr.id = "Spa_Cap_2";
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 99, 99, "", "", 500.0);
			FantomMakeCoolSailor(chr, SHIP_GALEON, "", CANNON_TYPE_CANNON_LBS24, 99, 99, 99);
			Group_AddCharacter(sGroup, chr.id);

			// 4
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, 0));
			chr.id = "Spa_Cap_3";
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 99, 99, "", "", 500.0);
			FantomMakeCoolSailor(chr, SHIP_CORVETTE, "", CANNON_TYPE_CANNON_LBS12, 99, 99, 99);
			Group_AddCharacter(sGroup, chr.id);

			// 5
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", SPAIN, MAN, 0));
			chr.id = "Spa_Cap_4";
			FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 99, 99, "", "", 500.0);
			FantomMakeCoolSailor(chr, SHIP_GALEON_L, "", CANNON_TYPE_CANNON_LBS12, 99, 99, 99);
			Group_AddCharacter(sGroup, chr.id);

			Group_SetAddress(sGroup, "SantaCatalina", "IslandShips1", "ship_1");
			Group_SetTaskAttack(sGroup, PLAYER_GROUP);
			Group_LockTask(sGroup);

			// Наведем порядок с нашими
			Group_DeleteGroup("FL_Friends");

			chr = CharacterFromID("FL_LoranDeGraff");
			chr.CompanionEnemyEnable = false;
			LAi_SetImmortal(chr, false);

			sGroup = "FL_FraAttack";
			Group_FindOrCreateGroup(sGroup);
			Group_SetType(sGroup, "war");
			Group_AddCharacter(sGroup, chr.id);
			Group_SetGroupCommander(sGroup, chr.id);

			for(i = 1; i<3; i++)
			{
				iChar = GetCharacterIndex("FL_Capitan_"+i);
				if(iChar != -1)
				{
					Group_AddCharacter(sGroup, characters[iChar].id);
					characters[iChar].CompanionEnemyEnable = false;
				}
			}
		
			Group_SetPursuitGroup(sGroup, PLAYER_GROUP);
			Group_SetAddress(sGroup, "SantaCatalina", "", "");
			Group_SetTaskAttack(sGroup, "FL_SpaAttack");
			Group_LockTask(sGroup);

			pchar.quest.FL9s59.win_condition.l1 = "MapEnter";
            pchar.quest.FL9s59.win_condition = "FL9_s60";
		break;

		case "FL9_s60":
			SetNationRelationBoth(SPAIN, FRANCE, RELATION_NEUTRAL);

			AddQuestRecord("FL9", "8");

			SetLifeDay(CharacterFromID("FL_LoranDeGraff"), 0);
			for(i = 1; i<3; i++)
			{
				iChar = GetCharacterIndex("FL_Capitan_"+i);
				if(iChar != -1) SetLifeDay(&characters[iChar], 0);
			}

			pchar.quest.FL9s60.win_condition.l1 = "location";
			pchar.quest.FL9s60.win_condition.l1.location = "Tortuga_town";
			pchar.quest.FL9s60.win_condition = "FL9_s61";
		break;

		case "FL9_s61":
			chrDisableReloadTolocation = true;

			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", FRANCE, MAN, 0));
			chr.name = "Жан";
			chr.lastname = "Пуатье";
			chr.dialog.filename = "Quest\FranceLine\officer2.c";
			chr.greeting = "proshu_proshenia";
			ChangeCharacterAddressGroup(chr, pchar.location, "quest", "quest1");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL9_s62", -1, 0.5);

			for(i=0;i<2;i++)
			{
				chr2 = GetCharacter(NPC_GeneratePhantomCharacter("mushketer", FRANCE, MAN, 0));
				ChangeCharacterAddressGroup(chr2, pchar.location, "quest", "quest1");
				LAi_SetActorType(chr2);
				LAi_ActorFollow(chr2, chr, "", -1);
			}
		break;

		case "FL9_s62":
			DoQuestReloadToLocation("Tortuga_townhall", "goto", "goto2", "FL9_s63");
		break;

		case "FL9_s63":
			pchar.MainQuest = "FL9_s63";
			LAi_SetActorType(pchar);
			chr = CharacterFromID("Tortuga_mayor");
			chr.dialog.currentnode = "quests";
			LAi_ActorDialogNow(pchar, chr, "FL10_s1", 0.5);
		break;

//====================================================================================================================
//	Эпилог
//====================================================================================================================
		case "FL10_s1":
			LAi_SetPlayerType(pchar);
			SetQuestHeaderColor("FL9", gray);
			CloseQuestHeader("FL9");
			SetQuestHeader("FL10");
			SetQuestHeaderColor("FL10", yellow);
			AddQuestRecord("FL10", "1");
			chr = CharacterFromID("Tortuga_mayor");
			chr.dialog.currentnode = "First time";
			pchar.MainQuest = "";
			QuestCloseSeaExit();
			chrDisableReloadTolocation = false;
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
		break;

		case "FL10_s2":
			ChangeCharacterAddressGroup(CharacterFromID("JozephFushe"), "none", "", "");
			AddDataToCurrent(0,0,1);
			SetCurrentTime(7,24);
			RefreshLandTime();
			SetLaunchFrameFormParam("Утром следующего дня...", "FL10_s3", 2.0, 3.0);
			LaunchFrameForm();
			
		break;

		case "FL10_s3":
			locations[FindLocation("Tortuga_town")].reload.l17.disable = 0;
			AddQuestRecord("FL10", "2");
			QuestOpenSeaExit();

			pchar.quest.FL10s3.win_condition.l1 = "location";
			pchar.quest.FL10s3.win_condition.l1.location = "Tortuga";
			pchar.quest.FL10s3.win_condition = "FL10_s4";
		break;

		case "FL10_s4":
			DoQuestCheckDelay("FL10_s5", 1.0);
		break;

		case "FL10_s5":
			//AddDataToCurrent(0,2,0);
			locations[FindLocation("Louvre")].image = "loading\Louvre.tga";
			SetLaunchFrameFormParam("Через 2 месяца...", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("Louvre", "goto", "goto4", "FL10_s6");
			LaunchFrameForm();
		break;

		case "FL10_s6":
			chr = GetCharacter(NPC_GenerateCharacter("FR_King", "dOgeron", "man", "man", 10, FRANCE, 0, false));
			chr.name = "Людовик";
			chr.lastname = "XIV";
			chr.dialog.filename = "Quest\FranceLine\King.c";
			ChangeCharacterAddressGroup(chr, pchar.location, "sit", "sit1");
			LAi_SetActorType(chr);

			chr = GetCharacter(NPC_GenerateCharacter("FL_1", "citiz_1", "man", "man", 10, FRANCE, 0, true));
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto1");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto5");

			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", FRANCE, MAN, 0));
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto2");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto6");

			chr = GetCharacter(NPC_GenerateCharacter("FL_2", "citiz_2", "man", "man", 10, FRANCE, 0, true));
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto3");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto7");
			
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", FRANCE, MAN, 0));
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto5");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto1");

			chr = GetCharacter(NPC_GenerateCharacter("FL_3", "citiz_4", "man", "man", 10, FRANCE, 0, true));
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto6");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto2");

			chr = GetCharacter(NPC_GenerateCharacter("FL_4", "citiz_9", "man", "man", 10, FRANCE, 0, true));
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto7");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto3");

			chr2 = CharacterFromID("Tortuga_mayor");
			chr = GetCharacter(NPC_GeneratePhantomCharacter("citizen", FRANCE, MAN, 0));
			chr.id = "FL_TortugaMayor";
			chr.model = chr2.model;
			chr.name = chr2.name;
			chr.lastname = chr2.lastname;
			chr.dialog.filename = "Quest\FranceLine\TortugaMayor.c";
			ChangeCharacterAddressGroup(chr, pchar.location, "goto", "goto8");
			LAi_SetActorType(chr);
			LAi_ActorTurnToLocator(chr, "goto", "goto4");

			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto8");

			locCameraToPos(-2,4,3,0);
			StartQuestMovie(false, false, true);
			LAi_ActorFollow(CharacterFromID("FR_King"), CharacterFromID("FL_3"), "FL10_s7", -1);
		break;

		case "FL10_s7":
			DoQuestCheckDelay("FL10_s8", 5.0);
		break;

		case "FL10_s8":
			LAi_ActorFollow(CharacterFromID("FR_King"), CharacterFromID("FL_4"), "FL10_s9", -1);
		break;

		case "FL10_s9":
			DoQuestCheckDelay("FL10_s10", 5.0);
		break;

		case "FL10_s10":
			LAi_ActorFollow(CharacterFromID("FR_King"), CharacterFromID("FL_TortugaMayor"), "FL10_s11", -1);
		break;

		case "FL10_s11":
			pchar.name = "Людовик XIV";
			pchar.lastname = "и губернатор де Кюсси";
			pchar.dialog.currentnode = "FL10_1";
			LAi_ActorSelfDialog(pchar, "FL10_s12");
		break;

		case "FL10_s12":
			chr = CharacterFromID("FR_King");
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL10_s13", -1, 0.5);
		break;

		case "FL10_s13":
			LAi_ActorFollow(CharacterFromID("FR_King"), CharacterFromID("FL_TortugaMayor"), "FL10_s14", -1);
		break;

		case "FL10_s14":
			pchar.dialog.currentnode = "FL10_6";
			LAi_ActorSelfDialog(pchar, "FL10_s15");
		break;

		case "FL10_s15":
			LAi_ActorFollow(CharacterFromID("FR_King"), CharacterFromID("FL_1"), "", -1);
			chr = CharacterFromID("FL_TortugaMayor");
			chr.dialog.currentnode = "5";
			LAi_ActorWaitDialog(pchar, chr);
			LAi_ActorDialog(chr, pchar, "FL10_s16", -1, 0.5);

			pchar.name = "Мишель";
			pchar.lastname = "де Граммон";
		break;

		case "FL10_s16":
			LAi_SetPlayerType(pchar);
			locCameraFollow();
			EndQuestMovie();
			DoQuestCheckDelay("FL10_s17", 0.5);
		break;

		case "FL10_s17":
			SetLaunchFrameFormParam("Через 2 часа"+NewStr()+"Поместье полковника де Граммона", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("GrammonEstate", "goto", "goto5", "FL10_s18");
			LaunchFrameForm();
		break;

		case "FL10_s18":
			chr = GetCharacter(NPC_GeneratePhantomCharacter("officer", FRANCE, MAN, -1));
			chr.id = "FL_father";
			chr.name = "Полковник";
			chr.lastname = "де Граммон";
			chr.dialog.filename = "Quest\FranceLine\father.c";
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", "reload6");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL10_s19", -1, 0.5);

			LAi_ActorFollow(CharacterFromID("GrammonMother"), chr, "", -1);
			LAi_ActorFollow(CharacterFromID("GrammonSister"), chr, "", -1);
		break;

		case "FL10_s19":
			DoQuestCheckDelay("FL10_s20", 0.5);
		break;

		case "FL10_s20":
			SetLaunchFrameFormParam("Через две недели...", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("France_docks", "reload", "reload2", "FL10_s21");
			LaunchFrameForm();
		break;

		case "FL10_s21":
			chr = CharacterFromID("GrammonMother");
			chr.dialog.filename = "Quest\FranceLine\mother.c";
			chr.dialog.currentnode = "first time";
			LAi_SetActorType(chr);
			ChangeCharacterAddressGroup(chr, "France_docks", "goto", "goto8");
			LAi_ActorDialog(chr, pchar, "FL10_s22", -1, 0.5);
		break;

		case "FL10_s22":
			AddQuestRecord("FL10", "3");
			DoQuestCheckDelay("FL10_s23", 0.5);
		break;

		case "FL10_s23":
			AddDataToCurrent(0,2,14);
			SetLaunchFrameFormParam("Через 2 месяца...", "Reload_To_Location", 2.0, 3.0);
			SetLaunchFrameReloadLocationParam("PortPax_town", "reload", "reload1", "FL10_s24");
			LaunchFrameForm();
			ChangeCharacterAddressGroup(CharacterFromID("GrammonMother"), "none", "", "");
		break;

		case "FL10_s24":
			SetQuestHeaderColor("FL10", gray);
			CloseQuestHeader("FL01");

			chr = CharacterFromID("FL_Mary");
			SaveCurrentNpcQuestDateParam(chr, "last_speek");
			SaveCurrentNpcQuestDateParam(chr, "last_visit");
			ChangeCharacterAddressGroup(chr, "PortPax_townhall", "goto", "governor1");
			LAi_SetStayType(chr);

			// на всякий случай, вдруг был квест
			DeleteAttribute(chr, "QuestData");
			RemovePassenger(pchar, chr);
			DeleteAttribute(pchar, "MaryOnShip");
			// <-

			setCharacterShipLocation(pchar, GetCityFrom_Sea("PortPax"));
		    setWDMPointXZ(GetCityFrom_Sea("PortPax"));
			SetColonyToPCHAR("PortPax");
			GiveItem2Character(pchar, "Clothes38");
			Log_info("Мари де Граммон в резиденции");
			Log_info("Порт-о-Принс - ваша колония");

			// тут сделаем подмену французского порта на спальню резиденции, чтобы было где трахаться с Мари
			i = FindLocation("France_docks");
			chr = RelizeLocation(i);
				
			chr.id = "FL_Bedroom";
			chr.id.label = "Bedroom";
			chr.image = "loading\inside\Bedroom.tga";
			chr.Bedroom = true;
			//Town sack
			chr.townsack = "PortPax";
			chr.lockWeather = "Inside";
			//Sound
			chr.type = "house";
			chr.fastreload = "PortPax";
			chr.islandId = "Hispaniola";
			
			//Always
			chr.filespath.models = "locations\inside\bedRoom1";
			chr.models.always.bedRoom1 = "bedRoom1";
			chr.models.always.bedRoom1.level = 65538;
			chr.models.always.bedRoom1windows = "mediumhouse01_windows";
			chr.models.always.bedRoom1windows.tech = "LocationWindows";
			chr.models.always.bedRoom1windows.level = 65539;
			chr.models.always.back = "..\inside_back";
			chr.models.always.back.level = 65529;
			//Day
			chr.models.day.locators = "bedRoom1_locators";
			chr.models.day.bedRoom1rand = "bedRoom1_rand";
			chr.models.day.charactersPatch = "bedRoom1_patch";
			//Night
			chr.models.night.locators = "bedRoom1_Nlocators";
			chr.models.night.charactersPatch = "bedRoom1_patch";
			//Environment
			chr.environment.weather = "true";
			chr.environment.sea = "false";
			//Reload map
			chr.reload.l1.name = "reload1";
			chr.reload.l1.go = "PortPax_townhall";
			chr.reload.l1.emerge = "reload1";
			chr.reload.l1.autoreload = "0";
			chr.reload.l1.label = "Residence";
		break;

//====================================================================================================================
//	Семейная жизнь
//====================================================================================================================
		//---------------------------------------------------------------------------------------------------------------
		Квест-пасхалка
		case "FL_musket2x2":
			chr = GetCharacter(NPC_GenerateCharacter("FL_Wolf", "bigpirate", "man", "man", 30, PIRATE, -1, false));
			FantomMakeCoolSailor(chr, SHIP_WOLF, "Raven", CANNON_TYPE_CANNON_LBS24, 99, 99, 99);
			//FantomMakeCoolSailor(chr, SHIP_FRIGATE, "Raven", CANNON_TYPE_CANNON_LBS18, 99, 99, 99);
			FantomMakeCoolFighter(chr, 30, 99, 99, "", "", 1000.0);
			chr.ShipSails.gerald_name="ships\gerald\quest\wolf.tga";
			chr.name = "Wolf":
			chr.lastname = "";

			chr.mapEnc.type = "trade";
			chr.mapEnc.worldMapShip = "quest_ship";
			chr.mapEnc.Name = "Капитан Wolf";
			chr.wdm_speed = 1.0; // скорость на глобалке
			Map_CreateTrader("Shore_ship1", "PuertoPrincipe_town", "FL_Wolf", -1);	// С бермуд на Пуэрто-Принсипе
			chr.step = 0;
		break;

		case "FL_musket2x2_1":
			chr = CharacterFromID("FL_Wolf");
			chr.mapEnc.type = "trade";
			chr.mapEnc.worldMapShip = "quest_ship";
			chr.mapEnc.Name = "Капитан Wolf";
			chr.wdm_speed = 1.0; // скорость на глобалке

			switch(chr.step)
			{
				case "0": Map_CreateTrader("PuertoPrincipe_port", "LeFransua_port", "FL_Wolf", -1); break;
				case "1": Map_CreateTrader("LeFransua_port", "Shore_ship1", "FL_Wolf", -1); break;
				case "2": Map_CreateTrader("Shore_ship1", "PuertoPrincipe_port", "FL_Wolf", -1); break;
			}
			
			chr.step = (sti(chr.step)+1);
			if(sti(chr.step) > 2) chr.step = 0;
		break;
		
		//---------------------------------------------------------------------------------------------------------------
		//	Поездка к отцу
		case "FL_Father_visit_start":
			pchar.MaryOnShip = 0;
			
			chr = CharacterFromID("FL_Mary");
			chr.QuestData.location = chr.location;
			chr.QuestData.location.group = chr.location.group;
			chr.QuestData.location.locator = chr.location.locator;
			chr.QuestData.location.town = locations[FindLocation(chr.location)].fastreload + "_town";

			chr.location = "none";

			AddPassenger(pchar, chr, false);
			SetCharacterRemovable(chr, false);
			chr.description = "Мари попросила отвезти её к отцу, в Фор-де-Франс";
			
			pchar.quest.FLFathervisitstart.win_condition.l1 = "location";
			pchar.quest.FLFathervisitstart.win_condition.l1.location = "FortFrance_town";
			pchar.quest.FLFathervisitstart.win_condition = "FL_Father_visit";
		break;

		case "FL_Father_visit":
			chr = CharacterFromID("FL_Mary");
			chr.QuestData = "Father_visit_days";

			RemovePassenger(pchar, chr);
			chrDisableReloadTolocation = true;
			DeleteAttribute(pchar, "MaryOnShip");

			ChangeCharacterAddressGroup(chr, "FortFrance_houseS2", "barmen", "stay");
			DoQuestCheckDelay("FL_Father_visit_to_home", 0.5);
		break;

		case "FL_Father_visit_to_home":
			DoQuestReloadToLocation("FortFrance_houseS2", "reload", "reload1", "FL_Father_visit_in_home");
		break;

		case "FL_Father_visit_in_home":
			chr = CharacterFromID("FL_Mary");
			SaveCurrentNpcQuestDateParam(chr, "QuestData.StartDate");
			LAi_SetActorType(chr);
			LAi_ActorDialog(chr, pchar, "FL_Father_visit_wait", -1, 0.5);
		break;

		case "FL_Father_visit_wait":
			chrDisableReloadTolocation = false;
			LAi_SetBarmanType(CharacterFromID("FL_Mary"));
		break;

		case "FL_Father_visit_back":
			pchar.MaryOnShip = 0;
			chr = CharacterFromID("FL_Mary");
			AddPassenger(pchar, chr, false);
			SetCharacterRemovable(chr, false);
			chr.description = "Нужно отвезти супругу домой, в Порт-о-Принс";
			ChangeCharacterAddressGroup(chr, "none", "", "");

			pchar.quest.FLFathervisitback.win_condition.l1 = "location";
			pchar.quest.FLFathervisitback.win_condition.l1.location = "PortPax_town";
			pchar.quest.FLFathervisitback.win_condition = "FL_Father_visit_end";
		break;

		case "FL_Father_visit_end":
			DeleteAttribute(pchar, "MaryOnShip");
			chr = CharacterFromID("FL_Mary");
			Log_Info(""+GetFullName(chr)+" сошла на берег.");
			RemovePassenger(pchar, chr);

			ChangeCharacterAddressGroup(chr, chr.QuestData.location, chr.QuestData.location.group, chr.QuestData.location.locator);
			DeleteAttribute(chr, "QuestData");
			LAi_SetStayType(chr);
			
			SaveCurrentNpcQuestDateParam(chr, "last_speek");
			SaveCurrentNpcQuestDateParam(chr, "last_visit");
		break;


		//---------------------------------------------------------------------------------------------------------------
		//	Морская прогулка
		case "FL_sea_walk_start":
			pchar.MaryOnShip = 0;
			
			chr = CharacterFromID("FL_Mary");
			chr.QuestData.location = chr.location;
			chr.QuestData.location.group = chr.location.group;
			chr.QuestData.location.locator = chr.location.locator;
			chr.QuestData.location.town = locations[FindLocation(chr.location)].fastreload + "_town";

			chr.location = "none";

			AddPassenger(pchar, chr, false);
			SetCharacterRemovable(chr, false);
			chr.description = "Мари попросила взять её с собой на на "+FindDaysString(sti(chr.QuestData.days))+"";
			
			SetTimerConditionParamEx("FLSeawalkstart", "FL_sea_walk_finish", 0, 0, sti(chr.QuestData.days));
		break;

		case "FL_sea_walk_finish":
			chr = CharacterFromID("FL_Mary");
			pchar.quest.FLseawalkfinish.win_condition.l1 = "location";
			pchar.quest.FLseawalkfinish.win_condition.l1.location = chr.QuestData.location.town;
			pchar.quest.FLseawalkfinish.win_condition = "FL_sea_walk_end";
		break;

		case "FL_sea_walk_end":
			DeleteAttribute(pchar, "MaryOnShip");
			chr = CharacterFromID("FL_Mary");
			Log_Info(""+GetFullName(chr)+" сошла на берег.");
			RemovePassenger(pchar, chr);

			ChangeCharacterAddressGroup(chr, chr.QuestData.location, chr.QuestData.location.group, chr.QuestData.location.locator);
			DeleteAttribute(chr, "QuestData");
			
			SaveCurrentNpcQuestDateParam(chr, "last_speek");
			SaveCurrentNpcQuestDateParam(chr, "last_visit");
		break;



		//---------------------------------------------------------------------------------------------------------------
		//	Прогулки
		case "FL_go_walk":
			i = FindLocation(pchar.location);
			sStr = locations[i].fastreload;
			chrDisableReloadTolocation = true;
			pchar.EncountersGen = false;
			chr = CharacterFromID("FL_Mary");
			chr.QuestData.DestLocator = locations[FindLocation(sStr+"_town")].reload.gate.emerge;
			DoQuestReloadToLocation(sStr+"_exittown", "reload", chr.QuestData.DestLocator, "FL_start_walk");
		break;

		case "FL_start_walk":
			chr = CharacterFromID("FL_Mary");
			chr.QuestData.location = chr.location;
			chr.QuestData.location.group = chr.location.group;
			chr.QuestData.location.locator = chr.location.locator;
			chr.QuestData.walkCount = (5+rand(3));

			StartQuestMovie(false, false, true);
			LAi_SetActorType(chr);
			
			ChangeCharacterAddressGroup(chr, pchar.location, "reload", chr.QuestData.DestLocator);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, chr, "", -1);

			locator = LAi_FindRandomLocator("goto");
			LAi_ActorGoToLocator(chr, "goto", locator, "FL_process_walk", -1);
		break;

		case "FL_process_walk":
			chr = CharacterFromID("FL_Mary");
			if(sti(chr.QuestData.walkCount) > 0)
			{
				chr.QuestData.walkCount = (sti(chr.QuestData.walkCount)-1);
				
				locator = LAi_FindRandomLocator("goto");
				LAi_ActorGoToLocator(chr, "goto", locator, "FL_process_walk_continue", -1);
				break;
			}

			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			
			// Возможны проблемы
			if(rand(100) > 50)
			{
				locator = LAi_FindRandomLocator("reload");
				for(i=0;i<3;i++)
				{
					chr = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, -1));
					chr.id = "FL_PirateOnWalk_"+i;
					FantomMakeCoolFighter(chr, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE, 80, 80, "", "", 100.0);
					chr.dialog.filename = "Quest\FranceLine\PirateOnWalk.c";
					chr.greeting = "Enc_Raiders";
					ChangeCharacterAddressGroup(chr, pchar.location, "reload", locator);
					LAi_SetActorType(chr);
					LAi_SetImmortal(chr, true);
					if(i==0) LAi_ActorDialog(chr, pchar, "FL_walk_fight", -1, 0);
					else LAi_ActorFollow(chr, pchar, "", -1);
				}
				break;
			}

			chr.dialog.currentnode = "end_walk";
			LAi_ActorDialogNow(chr, pchar, "FL_end_walk", 0);
		break;

		case "FL_process_walk_continue":
			DoQuestCheckDelay("FL_process_walk", 0.5);
		break;

		case "FL_end_walk":
			chr = CharacterFromID("FL_Mary");
			ChangeCharacterAddressGroup(chr, chr.QuestData.location, chr.QuestData.location.group, chr.QuestData.location.locator);
			LAi_SetBarmanType(chr);
			DoReloadCharacterToLocation(chr.QuestData.location, "reload", "reload1");
			DeleteAttribute(chr, "QuestData");
			chrDisableReloadTolocation = false;
			DeleteAttribute(pchar, "EncountersGen");
		break;
		
		case "FL_walk_fight":
			for(i=0;i<3;i++)
			{
				chr = CharacterFromID("FL_PirateOnWalk_"+i);
				LAi_SetImmortal(chr, false);
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "FL_EnemyFight");
			}
			LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("FL_EnemyFight", "FL_end_walk_after_fight");
		break;

		case "FL_end_walk_after_fight":
			Delay_DeleteGroup("FL_EnemyFight");
			chr = CharacterFromID("FL_Mary");
			chr.dialog.currentnode = "end_walk_after_fight";
			LAi_SetStayType(chr);
		break;

		//---------------------------------------------------------------------------------------------------------------
		// Секс
		case "FL_goToRoom":
			chr = CharacterFromID("FL_Mary");
			
			if(chr.QuestData.location == "FortFrance_houseS2")
			{
				DoQuestReloadToLocation("FortFrance_houseS2_room", "barmen", "stay", "FL_goToRoom2");
				ChangeCharacterAddressGroup(chr, "FortFrance_houseS2_room", "barmen", "bar1");
			}

			if(chr.QuestData.location == "PortPax_townhall")
			{
				DoQuestReloadToLocation("FL_Bedroom", "barmen", "stay", "FL_goToRoom2");
				ChangeCharacterAddressGroup(chr, "FL_Bedroom", "goto", "goto5");
			}
		break;
		
		case "FL_goToRoom2":
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("PlaySex_1", 3.0);
		break;

		case "FL_FromRoom":
			chr = CharacterFromID("FL_Mary");
			if(chr.QuestData.location == "FortFrance_houseS2")
			{
				LAi_ActorGoToLocation(chr, "reload", "reload1", "FortFrance_houseS2", "barmen", "stay", "FL_FromRoom2", -1);
			}

			if(chr.QuestData.location == "PortPax_townhall")
			{
				LAi_ActorGoToLocation(chr, "reload", "reload1", "PortPax_townhall", "goto", "governor1", "FL_FromRoom2", -1);
			}
		break;

		case "FL_FromRoom2":
			chr = CharacterFromID("FL_Mary");
			if(chr.QuestData.location == "FortFrance_houseS2")
			{
				DeleteAttribute(chr, "QuestData");
				LAi_SetBarmanType(chr);
				chrDisableReloadTolocation = false;
			}
			if(chr.QuestData.location == "PortPax_townhall")
			{
				DeleteAttribute(chr, "QuestData");
				LAi_SetStayType(chr);
				chrDisableReloadTolocation = false;
			}
		break;
	}
}

//дом Фуше
//locations[FindLocation("Tortuga_town")].reload.l17.disable = 1; //houseF3

//CharacterFromID("FL_LoranDeGraff");
//CharacterFromID("FL_JerarDePuanie");
//CharacterFromID("FL_nikolas");
//CharacterFromID("FL_granie");
//CharacterFromID("JozephFushe");
//CharacterFromID("FL_Mary");

//bQuestDisableMapEnter = true;
//Island_SetReloadEnableGlobal("Terks", false);
//chrDisableReloadTolocation = false;
//bDisableFastReload = true;
//Pchar.GenQuest.Hunter2Pause = true;

/*
LAi_SetWarriorTypeNoGroup(chr);
LAi_group_MoveCharacter(chr, "FL_EnemyFight");
LAi_group_SetRelation("FL_EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
LAi_group_FightGroups("FL_EnemyFight", LAI_GROUP_PLAYER, true);
LAi_group_SetCheck("FL_EnemyFight", "DebtQuest_Kill_Complette");
*/

/*
chr = GetCharacter(NPC_GenerateCharacter("FL_fushe_sailor2", "pirat8", "man", "man_B", 1, FRANCE, -1, false));
chr.name = "Амильс";
chr.lastname = "Ньюль";
chr.dialog.filename = "Quest\FranceLine\ShipYarderPhantom.c";
chr.greeting = "spainsh_busters";
*/
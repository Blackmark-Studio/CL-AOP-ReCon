void LeBasqueQuestComplete(string sQuestName, string qname)
{
	// boal -->
	ref sld, npchar, itm;
	aref arOldMapPos, arAll, arPass;
	int iTemp, i, n, ShipType, Rank; // нужно для вычислений любых целых (нации)
	float locx, locy, locz, fTemp;
	string attrName, Model, Blade, Gun, sTemp, Ship, sld1; // любые строки для вычислений
	bool bOk;
	if (bQuestLogShow)
	{
		Log_Info("Quest completed : " + sQuestName + "  param = " + qname);
		trace("Quest completed : " + sQuestName + "  param = " + qname + " " + GetQuestBookDataDigit());
	}
	// boal <--
	switch (sQuestName)
	{

		case "Off_Interface":
			ChangeShowIntarface();
		break;

		case "Shadow_of_a_big_deal":
			pchar.questTemp.LeBasque.Started = true;
			DeleteQuestCondition("LeBasque_Start");
			sld = GetCharacter(NPC_GenerateCharacter("Startaper_1", "officer_15", "man", "man", 1, PIRATE, -1, false));
			FantomMakeCoolFighter(sld, 30, 100, 70, "blade32", "pistol5", 50);
			sld.dialog.filename = "Quest\Lebasque\Start_dialog.c";
			sld.greeting = "pirat_common";
			LAi_SetLoginTime(sld, 7.0, 23.0);
			LAi_SetCitizenType(sld);
			AddLandQuestmark_Main(sld, "Shadow_of_a_big_deal");
			AddMapQuestMark_Major("Tortuga_town", "Shadow_of_a_big_deal", ""); // метка острова
			ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto5");
		break;

		case "Shadow_of_a_big_deal_1":
			pchar.questTemp.LeBask_tavern.Room_close = "true"; // не пускать в комнату таверны
			AddLandQuestmark_Main(CharacterFromID("Tortuga_Tavernkeeper"), "Shadow_of_a_big_deal");
			pchar.quest.Shadow_of_a_big_deal = "Talk_Tavern";
		break;

		case "Shadow_of_a_big_deal_2":
			sld = characterFromId("Startaper_1");
			sld.lifeday = 0;
			LAi_SetActorType(pchar);
			sld = GetCharacter(NPC_GenerateCharacter("Etien_Marso", "Estienne_Marso", "man", "man", 30, PIRATE, -1, false));
			sld.Buccaneer = true;
			FantomMakeCoolFighter(sld, 30, 100, 70, "blade32", "pistol5", 50);
			sld.name = FindPersonalName("Etien_Marso_name");
			sld.lastname = FindPersonalName("Etien_Marso_lastname");
			sld.rank = 30;
			sld.dialog.filename = "Quest\Lebasque\Marso_dialog.c";
			sld.greeting = "Gr_OliverTrast";
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "goto", "bask");
			LAi_SetActorType(sld);
			DoQuestCheckDelay("Shadow_of_a_big_deal_3", 0.5);
		break;

		case "Shadow_of_a_big_deal_3":
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			locCameraToPos(-6.7, 2.7, -3.2, false);
			locCameraTarget(characterFromID("Etien_Marso"));
			sld = characterFromId("Etien_Marso");
			LAi_ActorFollow(sld, characterFromID("blaze"), "Shadow_of_a_big_deal_4", -1);
		break;

		case "Shadow_of_a_big_deal_4":
			locCameraResetState();
			locCameraTarget(pchar);
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Etien_Marso");
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Shadow_of_a_big_deal_5":
			sld = characterFromId("Etien_Marso");
			LAi_ActorGoToLocation(sld, "reload", "reload2_back", "Tortuga_tavern_upstairs", "goto", "goto2", "Shadow_of_a_big_deal_5_1", -1);
			LAi_SetActorType(pchar);
			sld = characterFromId("Tortuga_Tavernkeeper");
			sld.Dialog.CurrentNode = "Shadow_of_a_big_deal_4";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Shadow_of_a_big_deal_5_1":
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false); // открыть комнату наверху
		break;

		case "Shadow_of_a_big_deal_6":
			QuestPointerToLoc("Tortuga_tavern", "reload", "reload2_back"); // поставить поинт
			pchar.quest.Shadow_of_a_big_deal = "";
			StartBattleLandInterface(); // вкл интерфейс
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Tortuga_Tavernkeeper");
			sld.Dialog.CurrentNode = "First Time";
			RemoveLandQuestmark_Main(sld, "Shadow_of_a_big_deal");
			pchar.quest.Shadow_of_a_big_deal_tavern.win_condition.l1 = "location";
			pchar.quest.Shadow_of_a_big_deal_tavern.win_condition.l1.location = "Tortuga_tavern_upstairs";
			pchar.quest.Shadow_of_a_big_deal_tavern.win_condition = "Shadow_of_a_big_deal_7";
		break;

		case "Shadow_of_a_big_deal_7":
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "dialog_6";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Shadow_of_a_big_deal_8":
			QuestPointerDelLoc("Tortuga_tavern", "reload", "reload2_back"); // удалить поинт
			QuestPointerToLoc("Tortuga_town", "reload", "gate_back"); // поставить поинт
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true); // закрыть комнату наверху
			chrDisableReloadToLocation = false; // открыть локацию
			DoQuestReloadToLocation("Tortuga_tavern", "reload", "reload2_back", "Shadow_of_a_big_deal_8_1");
			DoQuestCheckDelay("Shadow_of_a_big_deal_CheckNightTime", 1.0);
			i = FindLocation("Tortuga_ExitTown");
			locations[i].DisableEncounters = true;
			locations[i].DisableOfficers = 1;
		break;

		case "Shadow_of_a_big_deal_8_1":
			AddQuestRecord("LeBasque", "1");
		break;

		case "Shadow_of_a_big_deal_CheckNightTime":
			if (CheckAttribute(pchar, "questTemp.Shadow_of_a_big_deal.NightEventStarted"))
			{
				DeleteAttribute(pchar, "GenQuest.CannotWait");
				break;
			}
			if (pchar.location == "Tortuga_ExitTown")
			{
				pchar.GenQuest.CannotWait = true;
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.CannotWait");
			}

			if (pchar.location == "Tortuga_ExitTown" && GetTime() >= 0.0 && GetTime() < 4.0)
			{
				chrDisableReloadToLocation = true; // закрыть локацию
				pchar.questTemp.Shadow_of_a_big_deal.NightEventStarted = true;
				DeleteAttribute(pchar, "GenQuest.CannotWait");
				DoQuestCheckDelay("Shadow_of_a_big_deal_9", 1);
			}
			else
			{
				DoQuestCheckDelay("Shadow_of_a_big_deal_CheckNightTime", 1.0);
			}
		break;

		case "Shadow_of_a_big_deal_9":
			pchar.Dialog.CurrentNode = "Shadow_of_a_big_deal_1";
			SelfDialog(pchar);
		break;

		case "Shadow_of_a_big_deal_10":
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			LAi_SetActorType(pchar);
			locCameraToPos(-29.1, 2, -0.8, false);
			LAi_ActorRunToLocator(pchar, "item", "item1", "Shadow_of_a_big_deal_11", -1);
		break;

		case "Shadow_of_a_big_deal_11":
			locCameraToPos(-29.1, 2, -0.8, false);
			LAi_ActorTurnToLocator(pchar, "rld", "aloc7");
			sld = GetCharacter(NPC_GenerateCharacter("Raul_Giom", "citiz_3", "man", "man", 1, PIRATE, -1, false));
			sld.name = FindPersonalName("Raul_Giom_name");
			sld.lastname = FindPersonalName("Raul_Giom_lastname");
			ChangeCharacterAddressGroup(sld, "Tortuga_ExitTown", "reload", "reload4");
			locCameraTarget(sld);
			DoQuestCheckDelay("Shadow_of_a_big_deal_12", 0.4);
		break;

		case "Shadow_of_a_big_deal_12":
			sld = characterFromId("Raul_Giom");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "rld", "aloc7", "Shadow_of_a_big_deal_13", -1);
		break;

		case "Shadow_of_a_big_deal_13":
			locCameraToPos(-26.7, 2, -8.3, false);
			sld = GetCharacter(NPC_GenerateCharacter("Diego_de_Vargas", "Diego_Vargas", "man", "man", 1, SPAIN, -1, false));
			sld.name = FindPersonalName("Diego_de_Vargas_name");
			sld.lastname = FindPersonalName("Diego_de_Vargas_lastname");
			FantomMakeCoolFighter(sld, 30, 100, 70, "BladeBone", "pistol5", 50);
			ChangeCharacterAddressGroup(sld, "Tortuga_ExitTown", "goto", "goto3");
			locCameraTarget(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "bask", "Shadow_of_a_big_deal_13_1", -1);
		break;

		case "Shadow_of_a_big_deal_13_1":
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			notification(StringFromKey("InfoMessages_225"), SKILL_Sneak);
			DoQuestCheckDelay("Shadow_of_a_big_deal_14", 0.5);
		break;

		case "Shadow_of_a_big_deal_14":
			locCameraToPos(-29.1, 2, -0.8, false);
			sld = characterFromId("Diego_de_Vargas");
			locCameraTarget(sld);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "rld", "aloc14", "Shadow_of_a_big_deal_15", -1);
		break;

		case "Shadow_of_a_big_deal_15":
			lai_fade("Shadow_of_a_big_deal_16", "");
		break;

		case "Shadow_of_a_big_deal_16":
			locCameraFromToPos(-32.6, 2, 6.9, true, -32.2, -2, -3.1);
			sld = characterFromId("Diego_de_Vargas");
			LAi_ActorTurnToCharacter(sld, characterFromID("Raul_Giom"));
			sld = characterFromId("Raul_Giom");
			LAi_ActorTurnToCharacter(sld, characterFromID("Diego_de_Vargas"));
			DoQuestCheckDelay("Shadow_of_a_big_deal_17", 1.5);
		break;

		case "Shadow_of_a_big_deal_17":
			QuestMovieUnLockPlayer(); // окаемки выкл
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Raul_Giom", StringFromKey("LeBasque_Raul_Giom_1"));
			AoP_NPCDialogAddLine("Diego_de_Vargas", StringFromKey("LeBasque_Diego_de_Vargas_1"));
			AoP_NPCDialogAddLine("Raul_Giom", StringFromKey("LeBasque_Raul_Giom_2"));
			AoP_NPCDialogAddLine("Diego_de_Vargas", StringFromKey("LeBasque_Diego_de_Vargas_2"));
			AoP_NPCDialogAddLine("Raul_Giom", StringFromKey("LeBasque_Raul_Giom_3"));
			AoP_NPCDialogAddLine("Diego_de_Vargas", StringFromKey("LeBasque_Diego_de_Vargas_3"));
			AoP_NPCDialogAddLine("Raul_Giom", StringFromKey("LeBasque_Raul_Giom_4"));
			AoP_NPCDialogAddLine("Diego_de_Vargas", StringFromKey("LeBasque_Diego_de_Vargas_4"));
			AoP_NPCDialogAddLine("Raul_Giom", StringFromKey("LeBasque_Raul_Giom_5"));
			AoP_NPCDialogAddLine("Diego_de_Vargas", StringFromKey("LeBasque_Diego_de_Vargas_5"));
			AoP_NPCDialogAddLine("Raul_Giom", StringFromKey("LeBasque_Raul_Giom_6"));
			AoP_NPCDialogAddLine("Diego_de_Vargas", StringFromKey("LeBasque_Diego_de_Vargas_6"));
			AoP_NPCDialogAddLine("Raul_Giom", StringFromKey("LeBasque_Raul_Giom_7"));
			AoP_NPCDialogAddLine("Diego_de_Vargas", StringFromKey("LeBasque_Diego_de_Vargas_7"));
			AoP_NPCDialogLaunch("Diego_de_Vargas", "Raul_Giom", "Shadow_of_a_big_deal_18");
		break;

		case "Shadow_of_a_big_deal_18":
			QuestPointerDelLoc("Tortuga_town", "reload", "gate_back"); // удалить поинт
			QuestMovieLockPlayer(); // окаемки вкл
			LAi_SetActorType(pchar);
			locCameraToPos(-32.6, 2, 6.9, false);
			sld = characterFromId("Diego_de_Vargas");
			locCameraTarget(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto3", "", -1);
			DoQuestCheckDelay("Shadow_of_a_big_deal_19", 2.5);
		break;

		case "Shadow_of_a_big_deal_19":
			locCameraToPos(-32.6, 2, 6.9, false);
			sld = characterFromId("Raul_Giom");
			locCameraTarget(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "Shadow_of_a_big_deal_20", -1);
			sld = characterFromId("Diego_de_Vargas");
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;

		case "Shadow_of_a_big_deal_20":
			lai_fade("Shadow_of_a_big_deal_21", "");
		break;

		case "Shadow_of_a_big_deal_21":
			StartBattleLandInterface(); // вкл интерфейс
			QuestMovieUnLockPlayer(); // окаемки выкл
			locCameraResetState();
			locCameraTarget(pchar);
			DoQuestCheckDelay("Shadow_of_a_big_deal_22", 1.5);
		break;

		case "Shadow_of_a_big_deal_22":
			pchar.Dialog.CurrentNode = "Shadow_of_a_big_deal_3";
			SelfDialog(pchar);
		break;

		case "Shadow_of_a_big_deal_23":
			LAi_SetPLayerType(pchar);
			i = FindLocation("Tortuga_ExitTown");
			DeleteAttribute(&locations[i], "DisableEncounters");
			DeleteAttribute(&locations[i], "DisableOfficers");
			chrDisableReloadToLocation = false; // открыть локацию
			sld = characterFromId("Tortuga_Tavernkeeper");
			sld.Dialog.CurrentNode = "Shadow_of_a_big_deal_7";
			AddLandQuestmark_Main(sld, "Shadow_of_a_big_deal");
		break;

		case "Shadow_of_a_big_deal_24":
			DeleteAttribute(pchar, "questTemp.LeBask_tavern.Room_close"); // пускать в комнату таверны
			sld = characterFromId("Tortuga_Tavernkeeper");
			sld.Dialog.CurrentNode = "First Time";
			RemoveLandQuestmark_Main(sld, "Shadow_of_a_big_deal");
			AddQuestRecord("LeBasque", "2");
			sld = characterFromId("Etien_Marso");
			AddLandQuestmark_Main(sld, "Shadow_of_a_big_deal");
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true;
			sld.Abordage.Enable = false;
			SetCharacterRemovable(sld, false);
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			//FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("Etien_Marso_ship"), CANNON_TYPE_CULVERINE_LBS24, 90, 90, 90);
			FantomMakeCoolSailor(sld, SHIP_CORVETTE, FindPersonalName("Etien_Marso_ship"), CANNON_TYPE_LBS_BY_SHIP, 82, 82, 82);
			SetCrewQuantityFull(sld);
			SetBaseShipData(sld);
			SetRandGeraldSail(sld, PIRATE);
			sld.Ship.Mode = "pirate";
			sld.ship.Crew.Morale = 80;
			sld.DeckDialogNode = "dialog_21";
			Group_FindOrCreateGroup("Marso_Ship");
			Group_AddCharacter("Marso_Ship", "Etien_Marso");
			Group_SetAddress("Marso_Ship", "Tortuga", "quest_ships", "quest_ship_1");
			Group_SetGroupCommander("Marso_Ship", "Etien_Marso");
		break;

		case "Shadow_of_a_big_deal_25":
			locations[FindLocation("Mayak6")].DisableEncounters = true;
			sld = characterFromId("Etien_Marso");
			RemoveLandQuestmark_Main(sld, "Shadow_of_a_big_deal");
			AddQuestRecord("LeBasque", "3");
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_268"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("Mayak6", "reload", "sea", "Shadow_of_a_big_deal_27_1");
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0); // мотаем время
			SetCurrentTime(00, 13);
		break;

		case "Shadow_of_a_big_deal_27_1":
			QuestPointerToLoc("Mayak6", "reload", "bask"); // поставить поинт
			chrDisableReloadToLocation = true; // закрыть локацию
			pchar.quest.go_shpion_locator.win_condition.l1 = "locator";
			pchar.quest.go_shpion_locator.win_condition.l1.location = "Mayak6";
			pchar.quest.go_shpion_locator.win_condition.l1.locator_group = "reload";
			pchar.quest.go_shpion_locator.win_condition.l1.locator = "bask";
			pchar.quest.go_shpion_locator.win_condition = "Shadow_of_a_big_deal_28";
		break;

		case "Shadow_of_a_big_deal_28":
			QuestPointerDelLoc("Mayak6", "reload", "bask"); // удалить поинт
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto23");
			DoQuestCheckDelay("Shadow_of_a_big_deal_31", 2.0);
		break;

		case "Shadow_of_a_big_deal_31":
			LAi_ActorTurnToLocator(pchar, "goto", "goto23");
			QuestMovieUnLockPlayer(); // окаемки выкл
			pchar.Dialog.CurrentNode = "Shadow_of_a_big_deal_5";
			SelfDialog(pchar);
		break;

		case "Shadow_of_a_big_deal_32":
			Group_DeleteGroup("Marso_Ship");
			LAi_SetActorType(pchar);
			WaitDate("", 0, 0, 0, 0, 30); // мотаем время
			RecalculateJumpTable();
			WeatherParams.Rain = true; // хочу тут дождь! хз всё ли это надо, но оставлю
			WeatherParams.Rain.ThisDay = true;
			WeatherParams.Rain.StartTime = GetTime();
			WeatherParams.Rain.Duration = 180;
			WeatherParams.Rain.Type = 1;
			WeatherParams.Rain.IsLightingActive = true;
			WeatherParams.Rain.year = GetDataYear();
			WeatherParams.Rain.month = GetDataMonth();
			WeatherParams.Rain.day = GetDataDay();
			WeatherParams.Rain.time = GetTime();
			i = FindLocation("Mayak6");
			if (i != -1)
			{
				Locations[i].QuestlockWeather = "Storm04_add"; // потемнее
				Locations[i].environment.weather.rain = true;
			}
			for (i = 1; i < 4; i++)
			{
			int iOfficer = GetOfficersIndex(pchar, i);
			if (iOfficer < 0) continue;

			Characters[iOfficer].location = "none";
			Characters[iOfficer].location.group = "";
			Characters[iOfficer].location.locator = "";
			}
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_269"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("Mayak6", "reload", "bask", "Shadow_of_a_big_deal_33");
			LaunchFrameForm();
			sld = characterFromId("Raul_Giom");
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade6", "pistol3", 50);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Mayak6", "goto", "bask1");
			sld = GetCharacter(NPC_GenerateCharacter("Mayak_Bandit_1", "officer_26", "man", "man", CB_Rank(), PIRATE, -1, false));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Mayak_Bandit_1_name");
			sld.lastname = FindPersonalName("Mayak_Bandit_1_lastname");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Mayak6", "goto", "goto18");
			sld = GetCharacter(NPC_GenerateCharacter("Mayak_Bandit_2", "Killer_2", "man", "man", CB_Rank(), PIRATE, -1, false));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade1", "pistol1", 10);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Mayak6", "goto", "goto18");
			sld = GetCharacter(NPC_GenerateCharacter("Mayak_Bandit_3", "Killer_3", "man", "man", CB_Rank(), PIRATE, -1, false));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade23", "pistol1", 10);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Mayak6", "goto", "goto18");
		break;

		case "Shadow_of_a_big_deal_33":
			QuestMovieLockPlayer(); // окаемки вкл
			sld = characterFromId("Raul_Giom");
			LAi_ActorTurnToLocator(sld, "goto", "bask2");
			bDisableCharacterMenu = true; // Ф2 отключить
			TEV.StopTimeScale = true; // запрет ускорения
			EndBattleLandInterface(); // откл интерфейс
			LAi_ActorTurnToLocator(pchar, "goto", "goto23");
			Whr_UpdateWeather();
			locCameraFlyToPositionLookToOffset(2.7, 30.0, -21.3, 2.7, 18.0, -21.3, -2.17, 0.0, 18.5, 1.0, 700);
			locCameraFlyLookFromToAngle(2.7, 18.0, -21.3, 0.0, -0.117, 0.0, -0.117, -1);
			DoQuestCheckDelay("Shadow_of_a_big_deal_34", 11.0);
		break;

		case "Shadow_of_a_big_deal_34":
			locCameraResetState();
			locCameraToPos(2.7, 18.0, -21.3, false);
			locCameraTarget(characterFromID("Mayak_Bandit_1"));
			sld = characterFromId("Mayak_Bandit_1");
			LAi_ActorRunToLocator(sld, "goto", "bask2", "Shadow_of_a_big_deal_35", -1);
			sld = characterFromId("Mayak_Bandit_2");
			LAi_ActorRunToLocator(sld, "goto", "bask3", "Shadow_of_a_big_deal_34_1", -1);
			sld = characterFromId("Mayak_Bandit_3");
			LAi_ActorRunToLocator(sld, "goto", "bask4", "Shadow_of_a_big_deal_34_2", -1);
		break;

		case "Shadow_of_a_big_deal_34_1":
			sld = characterFromId("Mayak_Bandit_2");
			LAi_ActorTurnToCharacter(sld, characterFromID("Raul_Giom"));
		break;

		case "Shadow_of_a_big_deal_34_2":
			sld = characterFromId("Mayak_Bandit_3");
			LAi_ActorTurnToCharacter(sld, characterFromID("Raul_Giom"));
		break;

		case "Shadow_of_a_big_deal_35":
			sld = characterFromId("Mayak_Bandit_1");
			LAi_ActorTurnToCharacter(sld, characterFromID("Raul_Giom"));
			lai_fade("Shadow_of_a_big_deal_36", "");
		break;

		case "Shadow_of_a_big_deal_36":
			locCameraFromToPos(-4.8, 18, -15.2, true, 6.8, 17, -18.3);
			DoQuestCheckDelay("Shadow_of_a_big_deal_37", 2.0);
		break;

		case "Shadow_of_a_big_deal_37":
			QuestMovieUnLockPlayer(); // окаемки вкл
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Raul_Giom", StringFromKey("LeBasque_Raul_Giom_8"));
			AoP_NPCDialogAddLine("Mayak_Bandit_1", StringFromKey("LeBasque_Mayak_Bandit_1_1"));
			AoP_NPCDialogAddLine("Raul_Giom", StringFromKey("LeBasque_Raul_Giom_9"));
			AoP_NPCDialogAddLine("Mayak_Bandit_1", StringFromKey("LeBasque_Mayak_Bandit_1_2"));
			AoP_NPCDialogAddLine("Raul_Giom", StringFromKey("LeBasque_Raul_Giom_10"));
			AoP_NPCDialogAddLine("Mayak_Bandit_1", StringFromKey("LeBasque_Mayak_Bandit_1_3"));
			AoP_NPCDialogAddLine("Raul_Giom", StringFromKey("LeBasque_Raul_Giom_11"));
			AoP_NPCDialogAddLine("Mayak_Bandit_1", StringFromKey("LeBasque_Mayak_Bandit_1_4"));
			AoP_NPCDialogLaunch("Raul_Giom", "Mayak_Bandit_1", "Shadow_of_a_big_deal_38");
		break;

		case "Shadow_of_a_big_deal_38":
			LAi_SetActorType(pchar);
			locCameraFromToPos(-4.8, 18, -15.2, true, 6.8, 17, -18.3);
			QuestMovieLockPlayer(); // окаемки вкл
			sld = characterFromId("Raul_Giom");
			LAi_ActorAttack(CharacterFromID("Raul_Giom"), CharacterFromID("Mayak_Bandit_1"), "");
			sld = characterFromID("Mayak_Bandit_1");
			LAi_ActorTurnToCharacter(sld, characterFromID("Raul_Giom"));
			LAi_ActorAnimation(sld, "Shot", "Shadow_of_a_big_deal_39", 1);
		break;

		case "Shadow_of_a_big_deal_39":
			sld = characterFromId("Raul_Giom");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Shadow_of_a_big_deal_40", 2.0);
		break;

		case "Shadow_of_a_big_deal_40":
			sld = characterFromId("Mayak_Bandit_1");
			LAi_ActorGoToLocator(sld, "goto", "bask1", "", -1);
			DoQuestCheckDelay("Shadow_of_a_big_deal_41", 3.0);
		break;

		case "Shadow_of_a_big_deal_41":
			PlaySound("Quest\LeBask\Bask1.mp3");
			DoQuestCheckDelay("Shadow_of_a_big_deal_42", 2.0);
		break;

		case "Shadow_of_a_big_deal_42":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Mayak_Bandit_1");
			LAi_ActorTurnToCharacter(sld, characterFromID("Mayak_Bandit_3"));
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			locCameraResetState();
			locCameraTarget(characterFromID("Mayak_Bandit_1"));
			sld = characterFromId("Mayak_Bandit_2");
			LAi_ActorFollow(sld, characterFromID("Mayak_Bandit_1"), "", -1);
			sld = characterFromId("Mayak_Bandit_3");
			LAi_ActorFollow(sld, characterFromID("Mayak_Bandit_1"), "", -1);
		break;

		case "Shadow_of_a_big_deal_43":
			sld = characterFromId("Mayak_Bandit_1");
			ChangeCharacterAddressGroup(sld, "none", "", ""); // чтобы пистолет из руки пропал, хз как еще
			LAi_SetActorType(pchar);
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			lai_fade("Shadow_of_a_big_deal_44", "");
		break;

		case "Shadow_of_a_big_deal_44":
			PlaySound("Quest\LeBask\Bask2.mp3");
			locCameraFromToPos(0.7, 18, 18.9, true, 0.7, 18, 2.9);
			sld = characterFromId("Mayak_Bandit_1");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Mayak6", "item", "flower9");
			LAi_ActorTurnToLocator(sld, "goto", "bask7");
			sld = characterFromId("Mayak_Bandit_2");
			ChangeCharacterAddressGroup(sld, "Mayak6", "goto", "bask5");
			LAi_ActorTurnToLocator(sld, "goto", "bask7");
			sld = characterFromId("Mayak_Bandit_3");
			ChangeCharacterAddressGroup(sld, "Mayak6", "goto", "bask6");
			LAi_ActorTurnToLocator(sld, "goto", "bask7");
			sld = GetCharacter(NPC_GenerateCharacter("Raul_Giom_fake", "citiz_3", "man", "man", 1, PIRATE, -1, false));
			FantomMakeCoolFighter(sld, 30, 100, 70, "blade6", "pistol3", 50);
			LAi_SetLayType(sld);
			ChangeCharacterAddressGroup(sld, "Mayak6", "goto", "bask7");
			DoQuestCheckDelay("Shadow_of_a_big_deal_45", 2.0);
		break;

		case "Shadow_of_a_big_deal_45":
			lai_fade("", "");
			DoQuestCheckDelay("Shadow_of_a_big_deal_46", 3.0);
			sld = characterFromId("Raul_Giom_fake");
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;

		case "Shadow_of_a_big_deal_46":
			sld = characterFromId("Raul_Giom");
			ChangeCharacterAddressGroup(sld, "none", "", ""); // труп убрать
			PlaySound("Quest\LeBask\Bask3.mp3");
			DoQuestCheckDelay("Shadow_of_a_big_deal_47", 1.0);
		break;

		case "Shadow_of_a_big_deal_47":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Mayak_Bandit_1");
			sld.Dialog.CurrentNode = "dialog_1";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Shadow_of_a_big_deal_48":
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			locCameraResetState();
			locCameraTarget(pchar);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "goto", "bask4", "Shadow_of_a_big_deal_48_1", -1);
			sld = characterFromId("Mayak_Bandit_1");
			LAi_ActorRunToLocator(sld, "goto", "bask3", "Shadow_of_a_big_deal_49", -1);
			sld = characterFromId("Mayak_Bandit_2");
			LAi_ActorFollow(sld, characterFromID("Mayak_Bandit_1"), "", -1);
			sld = characterFromId("Mayak_Bandit_3");
			LAi_ActorFollow(sld, characterFromID("Mayak_Bandit_1"), "", -1);
		break;

		case "Shadow_of_a_big_deal_48_1":
			LAi_ActorTurnToLocator(pchar, "goto", "bask3");
		break;

		case "Shadow_of_a_big_deal_49":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Mayak_Bandit_1");
			GiveItem2Character(sld, "letter_bask");
			sld.money = 5000;
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true;  // не убирать труп через 200с
			sld.Dialog.CurrentNode = "dialog_2";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			sld = characterFromId("Mayak_Bandit_2");
			LAi_ActorTurnToLocator(sld, "goto", "bask4");
			sld = characterFromId("Mayak_Bandit_3");
			LAi_ActorTurnToLocator(sld, "goto", "bask4");
		break;

		case "Shadow_of_a_big_deal_50":
			DoQuestFunctionDelay("MakeQuestAutoSaveDelay", 1.0);
			bDisableCharacterMenu = false; // Ф2 включить
			DeleteAttribute(&TEV, "StopTimeScale");
			for (i = 1; i <= 3; i++)
			{
				sld = characterFromId("Mayak_Bandit_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Shadow_Team_Group");
			}
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Shadow_Team_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Shadow_Team_Group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Shadow_Team_Group", "Shadow_of_a_big_deal_51");
		break;

		case "Shadow_of_a_big_deal_51":
			chrDisableReloadToLocation = false;

			if (CheckAttribute(pchar, "questTemp.Shadow_of_a_big_deal.LetterChecked")) break;

			if (CheckCharacterItem(pchar, "letter_bask"))
			{
				pchar.questTemp.Shadow_of_a_big_deal.LetterChecked = true;
				DoQuestCheckDelay("Shadow_of_a_big_deal_53", 0.1);
				break;
			}

			if (pchar.location != "Mayak6")
			{
				pchar.questTemp.Shadow_of_a_big_deal.LetterChecked = true;

				if (CheckCharacterItem(pchar, "letter_bask"))
				{
					TakeNItems(pchar, "letter_bask", -GetCharacterItem(pchar, "letter_bask"));
				}

				GiveItem2Character(pchar, "letter_bask");
				Log_Info(StringFromKey("InfoMessages_270"));

				DoQuestCheckDelay("Shadow_of_a_big_deal_53", 0.1);
				break;
			}

			DoQuestCheckDelay("Shadow_of_a_big_deal_51", 1.0);
		break;

		case "Shadow_of_a_big_deal_53":
			QuestPointerToLoc("Mayak6", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Tortuga_Graveyard", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("Tortuga_ExitTown", "reload", "reload4"); // поставить поинт
			QuestPointerToLoc("Tortuga_town", "reload", "reload4_back"); // поставить поинт
			AddQuestRecord("LeBasque", "5");
			DeleteAttribute(&locations[FindLocation("Mayak6")], "DisableEncounters");
			FreeSitLocator("Tortuga_tavern", "sit1");
			sld = characterFromId("Etien_Marso");
			LAi_SetSitType(sld);
			sld.Dialog.CurrentNode = "dialog_29";
			AddLandQuestmark_Main(sld, "Shadow_of_a_big_deal");
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit1");
			Pchar.quest.FreeSit_Tavern_LeBasque.win_condition.l1 = "location";
			Pchar.quest.FreeSit_Tavern_LeBasque.win_condition.l1.location = "Tortuga_tavern";
			Pchar.quest.FreeSit_Tavern_LeBasque.win_condition = "Shadow_of_a_big_deal_53_0";
		break;

		case "Shadow_of_a_big_deal_53_0":
			FreeSitLocator("Tortuga_tavern", "sit_base5");
			FreeSitLocator("Tortuga_tavern", "sit_front5");
			FreeSitLocator("Tortuga_tavern", "sit2");
		break;

		case "Shadow_of_a_big_deal_53_1":
			FreeSitLocator("Tortuga_tavern", "sit2");
			LAi_Fade("Shadow_of_a_big_deal_54", "");
		break;

		case "Shadow_of_a_big_deal_54":
			LAi_SetSitType(pchar);
			ChangeCharacterAddressGroup(pchar, "Tortuga_tavern", "sit", "sit2");
			sld = characterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "dialog_30";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Shadow_of_a_big_deal_55":
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = characterFromID("Etien_Marso");
			RemoveLandQuestmark_Main(sld, "Shadow_of_a_big_deal");
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "tables", "stay9");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "Shadow_of_a_big_deal_56", -1);
		break;

		case "Shadow_of_a_big_deal_56":
			QuestPointerDelLoc("Mayak6", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Tortuga_Graveyard", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("Tortuga_ExitTown", "reload", "reload4"); // удалить поинт
			QuestPointerDelLoc("Tortuga_town", "reload", "reload4_back"); // удалить поинт
			DeleteAttribute(&WeatherParams, "Rain");
			i = FindLocation("Mayak6");
			if (i != -1)
			{
				DeleteAttribute(&Locations[i], "QuestlockWeather");
				DeleteAttribute(&Locations[i], "environment.weather.rain");
			}
			Whr_UpdateWeather();
			log_info(StringFromKey("InfoMessages_271"));
			chrDisableReloadToLocation = false; // открыть локацию
			AddQuestRecord("LeBasque", "6");
			ChangeBuccaneerRelation(10.0); // +10 к отношениям с буканьерами
			CloseQuestHeader("LeBasque");
			SetTimerCondition("Old_campfire", 0, 0, 1, false);
			SetBuccaneerService(1);
			Achievment_Set(ACH_Shadow_of_a_big_deal);
		break;

		// Второй квест линейки ле Баска. Пепел старого костра.

		case "Old_campfire":
			sld = characterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "Old_campfire_1";
			AddLandQuestmark_Main(sld, "Old_campfire");
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto7");
		break;

		case "Old_campfire_1":
			EndBattleLandInterface(); // откл интерфейс
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, characterFromID("Etien_Marso"), "", -1);
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "gate_back", "", -1);
			RemoveLandQuestmark_Main(sld, "Old_campfire");
			DoQuestCheckDelay("Old_campfire_1_1", 2);
		break;

		case "Old_campfire_1_1":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "Old_campfire_function_1", "");
		break;

		case "Old_campfire_2":
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Etien_Marso");
			LAi_ActorTurnToCharacter(sld, characterFromID("Mishel_le_Bask"));
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Old_campfire_6";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_3":
			LAi_SetActorType(pchar);
			sld = characterFromId("Mishel_le_Bask");
			sld.Buccaneer = true;
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Old_campfire_4":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Old_campfire_7";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_4_1":
			LAi_SetActorType(pchar);
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "dialog_6";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Old_campfire_4_2":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Old_campfire_7_1";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_5":
			AddQuestRecord("Old_campfire", "0");
			DoReloadCharacterToLocation("Bucaneer_outpost", "reload", "reload6_back");
			fTemp = GetTime() + 0.5;
			iTemp = 0;
			if (fTemp >= 24.0)
			{
				fTemp = fTemp - 24.0; iTemp = 1;
			}
			pchar.quest.Old_campfire_Marso.win_condition.l1 = "Timer";
			pchar.quest.Old_campfire_Marso.win_condition.l1.date.hour = fTemp;
			pchar.quest.Old_campfire_Marso.win_condition.l1.date.day = GetAddingDataDay(0, 0, iTemp);
			pchar.quest.Old_campfire_Marso.win_condition.l1.date.month = GetAddingDataMonth(0, 0, iTemp);
			pchar.quest.Old_campfire_Marso.win_condition.l1.date.year = GetAddingDataYear(0, 0, iTemp);
			pchar.quest.Old_campfire_Marso.win_condition = "Old_campfire_6";
		break;

		case "Old_campfire_6":
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Old_campfire_8";
			LAi_SetStayType(sld);
			AddLandQuestmark_Main(sld, "Old_campfire");
			ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto14");
		break;

		case "Old_campfire_7":
			chrDisableReloadToLocation = true; // закрыть локацию
			AddQuestRecord("Old_campfire", "1");
			sld = characterFromId("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Old_campfire_8", -1);
		break;

		case "Old_campfire_8":
			RemoveMapQuestMark("Tortuga_town", "Shadow_of_a_big_deal"); // убрать метку острова
			AddMapQuestMark_Major("LaVega_town", "Old_campfire", ""); // метка острова
			chrDisableReloadToLocation = false; // открыть локацию
			sld = characterFromId("Etien_Marso");
			AddPassenger(pchar, sld, false);
			ChangeCharacterAddressGroup(sld, "LaVega_town", "quest", "quest1");
			pchar.quest.Old_campfire_LaVega.win_condition.l1 = "location";
			pchar.quest.Old_campfire_LaVega.win_condition.l1.location = "LaVega_town";
			pchar.quest.Old_campfire_LaVega.win_condition = "Old_campfire_9";
		break;

		case "Old_campfire_9":
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Old_campfire_9";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Old_campfire_10":
			pchar.quest.Old_campfire = "Talk_Tavern";
			sld = characterFromId("LaVega_tavernkeeper");
			AddLandQuestmark_Main(sld, "Old_campfire");
			QuestPointerToLoc("LaVega_town", "reload", "reload4_back"); // поставить поинт
			AddQuestRecord("Old_campfire", "2");
			sld = characterFromId("Etien_Marso");
			RemoveLandQuestmark_Main(sld, "Old_campfire");
			LAi_ActorRunToLocation(sld, "reload", "reload6_back", "none", "", "", "", -1);
		break;

		case "Old_campfire_11":
			QuestPointerDelLoc("LaVega_town", "reload", "reload4_back"); // удалить поинт
			sld = characterFromId("LaVega_tavernkeeper");
			RemoveLandQuestmark_Main(sld, "Old_campfire");
			pchar.quest.Old_campfire = "";
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Old_campfire_11";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Old_campfire_12":
			chrDisableReloadToLocation = true; // закрыть локацию, чтобы Марсо вышел
			QuestPointerToLoc("LaVega_town", "reload", "reload1_back"); // поставить поинт
			sld = characterFromId("Etien_Marso");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Shore32", "goto", "goto4", "Old_campfire_13", -1);
		break;

		case "Old_campfire_13":
			AddQuestRecord("Old_campfire", "3");
			chrDisableReloadToLocation = false; // открыть локацию
			pchar.quest.Old_campfire_Isabela.win_condition.l1 = "location";
			pchar.quest.Old_campfire_Isabela.win_condition.l1.location = "Shore32";
			pchar.quest.Old_campfire_Isabela.win_condition = "Old_campfire_14";
		break;

		case "Old_campfire_14":
			sld = characterFromID("Etien_Marso");
			LAi_SetStayType(sld);
			AddLandQuestmark_Main(sld, "Old_campfire");
			sld.dialog.currentnode = "Old_campfire_Isabela_Check";
		break;

		case "Old_campfire_15":
			chrDisableReloadToLocation = true; // закрыть локацию
			QuestPointerDelLoc("LaVega_town", "reload", "reload1_back"); // удалить поинт
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "officers", "sea_3", "none", "", "", "Old_campfire_16", -1);
			RemoveLandQuestmark_Main(sld, "Old_campfire");
		break;

		case "Old_campfire_16":
			AddMapQuestMark_Major("Shore59", "Old_campfire", ""); // метка острова
			AddQuestRecord("Old_campfire", "3.1");
			chrDisableReloadToLocation = false; // открыть локацию
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore59", "officers", "sea_1");
			pchar.quest.Go_To_Scarboro.win_condition.l1 = "location";
			pchar.quest.Go_To_Scarboro.win_condition.l1.location = "Shore59";
			pchar.quest.Go_To_Scarboro.win_condition = "Old_campfire_16_1";
		break;

		case "Old_campfire_16_1":
			DoQuestCheckDelay("Off_Interface", 0.2);
			QuestMovieLockPlayer(); // окаемки вкл
			chrDisableReloadToLocation = true; // закрыть локацию
			QuestPointerToLoc("Shore59", "reload", "reload2_back"); // поставить поинт
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "goto", "goto16", "Old_campfire_16_2", -1);
			sld = characterFromID("Etien_Marso");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
		break;

		case "Old_campfire_16_2":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPLayerType(pchar);
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Old_campfire_14";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Old_campfire_17":
			StartBattleLandInterface(); // вкл интерфейс
			chrDisableReloadToLocation = false; // открыть локацию
			LocatorReloadEnterDisable("Tobago_JungleHouse", "reload2_back", true); // закрыть дом
			sld = characterFromID("Etien_Marso");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.House_Rosh_1.win_condition.l1 = "locator";
			pchar.quest.House_Rosh_1.win_condition.l1.location = "Tobago_JungleHouse";
			pchar.quest.House_Rosh_1.win_condition.l1.locator_group = "reload";
			pchar.quest.House_Rosh_1.win_condition.l1.locator = "reload2_back";
			pchar.quest.House_Rosh_1.win_condition = "Old_campfire_18";
		break;

		case "Old_campfire_18":
			QuestPointerDelLoc("Shore59", "reload", "reload2_back"); // удалить поинт
			sld = characterFromID("Rimalier");
			sld.Buccaneer = true;
			sld.dialog.filename = "Quest\Lebasque\Rimalier_dialog.c";
			sld.Dialog.CurrentNode = "dialog_0";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tobago_JungleHouse", "quest", "mushketer");
			DoQuestCheckDelay("Old_campfire_19", 0.5);
		break;

		case "Old_campfire_19":
			LocatorReloadEnterDisable("Tobago_JungleHouse", "reload2_back", false);
			sld = characterFromID("Rimalier");
			LAi_ActorDialogNow(sld, pchar, "", -1);
			sld = GetCharacter(NPC_GenerateCharacter("Young_Boy_Bask", "Jacko", "man", "man", CB_Rank(), PIRATE, -1, false));
			sld.Buccaneer = true;
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Young_Boy_Bask_name");
			sld.lastname = "";
			sld.dialog.filename = "Quest\Lebasque\Jaco_dialog.c";
			sld.Dialog.CurrentNode = "Old_campfire_1";
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tobago_JungleHouse", "goto", "goto1");
		break;

		case "Old_campfire_20":
			LAi_SetActorType(pchar);
			EndBattleLandInterface(); // откл интерфейс
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorRunToLocator(sld, "rld", "loc0", "Old_campfire_22", -1);
			ChangeCharacterAddressGroup(pchar, "Tobago_JungleHouse", "officers", "reload2_2");
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tobago_JungleHouse", "officers", "reload2_3");
			DoQuestCheckDelay("Old_campfire_21", 0.1);
		break;

		case "Old_campfire_21":
			locCameraToPos(17.4, 4, -6.5, false);
			locCameraTarget(characterFromID("Young_Boy_Bask"));
			sld = characterFromID("Etien_Marso");
			LAi_ActorTurnToLocator(sld, "rld", "loc0");
		break;

		case "Old_campfire_22":
			sld = characterFromID("Rimalier");
			ChangeCharacterAddressGroup(sld, "Tobago_JungleHouse", "quest", "teleport");
			LAi_ActorTurnToLocator(sld, "rld", "loc0");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_23":
			sld = characterFromID("Rimalier");
			sld.Dialog.CurrentNode = "dialog_7";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorRunToLocator(sld, "quest", "officers2", "Old_campfire_23_1", -1);
		break;

		case "Old_campfire_23_1":
			sld = characterFromID("Young_Boy_Bask");
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;

		case "Old_campfire_24":
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "quest", "officers2", "Old_campfire_25", -1);
			sld = characterFromID("Rimalier");
			LAi_ActorRunToLocator(sld, "quest", "officers1", "", -1);
			sld = characterFromID("Etien_Marso");
			LAi_SetStayType(sld); // а то так и будет прилипать
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "officers3", "", -1);
		break;

		case "Old_campfire_25":
			pchar.questTemp.MainModel = pchar.model; // помним одёжку ГГ
			pchar.questTemp.MainAnimation = pchar.model.animation;
			pchar.model = "Diego_Vargas";
			pchar.model.animation = "man";
			bDisableCharacterMenu = true; // Ф2 отключить
			InterfaceStates.Buttons.Save.enable = 0;
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_272"), "Reload_To_Location", 0.1, 3.0);
			SetLaunchFrameReloadLocationParam("Tobago_Jungle_01", "goto", "goto7", "Old_campfire_26");
			LaunchFrameForm();
			i = FindLocation("Tobago_Jungle_01");
			Locations[i].models.always.mortirs = "jungle6_mort";
			Locations[i].models.always.mortirs.tech = "DLightModel";
			for (i = 1; i <= 8; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Spa_people_" + i, "killer_" + i, "man", "man", CB_Rank(), PIRATE, -1, false));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
				CB_Perks(sld);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Tobago_Jungle_01", "goto", "mort" + (2 + i));
			}
			sld = GetCharacter(NPC_GenerateCharacter("Spa_people_9", "officer_26", "man", "man", CB_Rank(), PIRATE, -1, false));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
			CB_Perks(sld);
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Spa_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tobago_Jungle_01", "goto", "goto1");
		break;

		case "Old_campfire_26":
			QuestMovieLockPlayer(); // окаемки вкл
			TEV.StopTimeScale = true; // запрет ускорения
			for (i = 1; i <= 8; i++)
			{
				sld = characterFromID("Spa_people_" + i);
				LAi_ActorTurnToLocator(sld, "item", "flower5");
			}
			ChangeShowIntarface();
			locCameraFlyToPositionLookToPoint(-5.3, 2.2, 8.7, -6.9, 2.2, 18.5, -6.7, 2.2, 0.4, -1.0, 500);
			pchar.FuncCameraFly = "Old_campfire_function_4";
		break;

		case "Old_campfire_27":
			QuestMovieUnLockPlayer(); // окаемки вкл
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Spa_people_9");
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_28":
			QuestMovieLockPlayer(); // окаемки вкл
			sld = characterFromID("Spa_people_9");
			LAi_ActorGoToLocator(sld, "goto", "goto5", "", -1);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "", -1);
			DoQuestCheckDelay("Old_campfire_29", 3);
		break;

		case "Old_campfire_29":
			locCameraFromToPos(3.6, 4, 0, true, -5.9, 1, 0.6);
			DoQuestCheckDelay("Old_campfire_30", 2);
		break;

		case "Old_campfire_30":
			QuestMovieUnLockPlayer(); // окаемки вкл
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Spa_people_9");
			sld.Dialog.CurrentNode = "Spa_5";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_31":
			SetCameraShake(0.5, 5.0, 3.0, 1.2, 0.5, true, false, CAM_EASING_CUBE);
			QuestMovieLockPlayer(); // окаемки вкл
			PlaySound("Sea Battles_01\cannon_fire_01.wav");
			CreateLocationParticlesXZ("Ship_cannon_fire", "goto", "mort2", -1.0, 0, 0, "");
			CreateLocationParticlesXZ("blast_inv", "goto", "mort2", -1.0, 0, 0, "");
			locCameraFromToPos(3.6, 4, 0, false, -5.9, 1, 0.6);
			DoQuestCheckDelay("Old_campfire_32", 3);
		break;

		case "Old_campfire_32":
			PlaySound("Quest\LeBask\Bask4.mp3");
			locCameraFromToPos(3.6, 4, 0, false, -2.3, 1, 20);
			for (i = 1; i <= 7; i++)
			{
				sld = characterFromID("Spa_people_" + (2 + i));
				LAi_ActorRunToLocation(sld, "reload", "reload3_back", "none", "", "", "", -1);
			}
			DoQuestCheckDelay("Old_campfire_33", 3);
		break;

		case "Old_campfire_33":
			LAi_FadeEx(2.0, 2.0, 0, "", "", "");
			DoQuestCheckDelay("Old_campfire_34", 3);
		break;

		case "Old_campfire_34":
			DeleteAttribute(&TEV, "StopTimeScale");
			bDisableCharacterMenu = false; // Ф2 включить
			InterfaceStates.Buttons.Save.enable = 1;
			LAi_SetActorType(pchar);
			pchar.model = pchar.questTemp.MainModel; // вернуть одёжку
			pchar.model.animation = pchar.questTemp.MainAnimation;
			DoQuestReloadToLocation("Tobago_JungleHouse", "quest", "officers2", "Old_campfire_35");
			sld = characterFromID("Rimalier");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Tobago_JungleHouse", "quest", "officers1");
			sld = characterFromID("Etien_Marso");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Tobago_JungleHouse", "quest", "officers3");
		break;

		case "Old_campfire_35":
			ChangeShowIntarface();
			locCameraFromToPos(7, 4, -3, false, 13.3, 3, -10.9);
			DoQuestCheckDelay("Old_campfire_36", 2);
		break;

		case "Old_campfire_36":
			PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
			SetCameraShake(0.5, 5.0, 3.0, 1.2, 0.5, true, false, CAM_EASING_CUBE);
			CreateParticleSystem("ShipExplode", 16.9, 3.5, -13, 0.0, 0.0, 0.0, 0);
			CreateParticleSystem("ShipExplode", 14, 4.5, -13, 0.0, 0.0, 0.0, 0);
			DoQuestCheckDelay("Old_campfire_37", 2);
		break;

		case "Old_campfire_37":
			CreateLocationParticlesLoopedSound("shipfire", "reload", "reload2_back", 0.0, 0.0, 0.0, "fortfire");
			CreateParticleSystem("shipfire", 16.9, 3.5, -13, 0.0, 0.0, 0.0, 0);
			CreateParticleSystem("shipfire", 14, 4.5, -13, 0.0, 0.0, 0.0, 0);
			DoQuestCheckDelay("Old_campfire_38", 2);
			sld = characterFromID("Rimalier");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "reload", "reload2_back");
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "reload", "reload2_back");
			LAi_ActorTurnToLocator(pchar, "reload", "reload2_back");

		break;

		case "Old_campfire_38":
			locCameraToPos(7, 4, -3, false);
			locCameraTarget(characterFromID("Rimalier"));
			DoQuestCheckDelay("Old_campfire_39", 2);
			for (i = 1; i <= 7; i++)
			{
				sld = characterFromID("Spa_people_" + (2 + i));
				ChangeCharacterAddressGroup(sld, "Tobago_JungleHouse", "rld", "loc4");
			}
		break;

		case "Old_campfire_39":
			QuestMovieUnLockPlayer(); // окаемки вкл
			locCameraToPos(7, 4, -3, false);
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Rimalier");
			sld.Dialog.CurrentNode = "dialog_11";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_40":
			chrDisableReloadToLocation = true; // закрыть локацию
			locCameraResetState();
			locCameraTarget(pchar);
			StartBattleLandInterface(); // вкл интерфейс
			sld = characterFromID("Rimalier");
			LAi_SetImmortal(sld, true);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromID("Etien_Marso");
			LAi_SetImmortal(sld, true);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i = 1; i <= 9; i++)
			{
				sld = characterFromID("Spa_people_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Spa_Jungle_Group");
			}
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Spa_Jungle_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Spa_Jungle_Group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Spa_Jungle_Group", "Old_campfire_41");
		break;

		case "Old_campfire_41":
			sld = characterFromId("Diego_de_Vargas");
			FantomMakeCoolSailor(sld, SHIP_MARGARITA, FindPersonalName("Diego_de_Vargas_ship"), CANNON_TYPE_CANNON_LBS36, 75, 65, 70);
			SetCharacterShipLocation(sld, "Shore59"); // корабль бухту
			LAi_group_Delete("Spa_Jungle_Group");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = characterFromID("Rimalier");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "dialog_13";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
		break;

		case "Old_campfire_41_1":
			i = FindLocation("Tobago_Jungle_01");
			locations[i].DisableOfficers = 1;
			sld = characterFromID("Rimalier");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			chrDisableReloadToLocation = false; // открыть локацию
			pchar.quest.tobago_jungle_mortir.win_condition.l1 = "location";
			pchar.quest.tobago_jungle_mortir.win_condition.l1.location = "Tobago_Jungle_01";
			pchar.quest.tobago_jungle_mortir.win_condition = "Old_campfire_42_2";
		break;

		case "Old_campfire_42_2":
			QuestMovieLockPlayer(); // окаемки вкл
			DoQuestCheckDelay("Off_Interface", 0.2);
			LAi_SetActorType(pchar);
			ChangeCharacterAddressGroup(pchar, "Tobago_Jungle_01", "rld", "loc4");
			LAi_ActorGoToLocator(pchar, "officers", "reload3_2", "", -1);
			sld = characterFromID("Rimalier");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tobago_Jungle_01", "rld", "loc0");
			LAi_ActorGoToLocator(sld, "officers", "reload3_back_2", "Old_campfire_42_3", -1);
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tobago_Jungle_01", "rld", "loc1");
			LAi_ActorGoToLocator(sld, "officers", "reload3_3", "", -1);
			sld = characterFromID("Spa_people_1");
			LAi_SetStayType(sld);
			sld = characterFromID("Spa_people_2");
			LAi_SetStayType(sld);
		break;

		case "Old_campfire_42_3":
			locCameraFromToPos(-5.6, 1.5, 31.7, false, -5.8, 0, 24.3);
			DoQuestCheckDelay("Old_campfire_42_4", 1);
		break;

		case "Old_campfire_42_4":
			sld = characterFromId("Rimalier");
			LAi_ActorTurnToCharacter(sld, characterFromID("Spa_people_2"));
			LAi_ActorAnimation(sld, "Shot", "Old_campfire_42_5", 1.5);
		break;

		case "Old_campfire_42_5":
			PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
			sld = characterFromId("Spa_people_1");
			LAi_KillCharacter(sld);
			sld = characterFromId("Spa_people_2");
			LAi_KillCharacter(sld);
			//CreateLocationParticlesLoopedSound("shipfire", "goto", "mort1", 0.0, 0.0, 0.0, "fortfire");
			SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
			CreateLocationParticlesXZ("ShipExplode", "goto", "mort1", 0, 0, 0, "");
			CreateLocationParticlesXZ("ShipExplode", "goto", "mort2", 0, 0, 0, "");
			//CreateLocationParticlesXZ("shipfire", "goto", "mort1", 0, 0, 0, "");
			//CreateLocationParticlesXZ("shipfire", "goto", "mort2", 0, 0, 0, "");
			locCameraFromToPos(-5.8, 3, 12.3, false, -6, 1, -2.4);
			DoQuestCheckDelay("Old_campfire_42_6", 3);
		break;

		case "Old_campfire_42_6":
			locCameraFromToPos(-7, 2, 20.7, true, -5.8, 1, 31.5);
			DoQuestCheckDelay("Old_campfire_42_7", 1);
		break;

		case "Old_campfire_42_7":
			sld = characterFromId("Etien_Marso");
			LAi_ActorTurnToCharacter(sld, characterFromID("Rimalier"));
			LAi_ActorTurnToCharacter(pchar, characterFromID("Rimalier"));
			DoQuestCheckDelay("Old_campfire_42_8", 1);
		break;

		case "Old_campfire_42_8":
			QuestMovieUnLockPlayer(); // окаемки выкл
			locCameraFromToPos(-7, 2, 20.7, true, -5.8, 1, 31.5);
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Joke_1";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_42_9":
			locCameraFromToPos(-7, 2, 20.7, true, -5.8, 1, 31.5);
			sld = characterFromId("Rimalier");
			sld.Dialog.CurrentNode = "Joke_1";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_42_10":
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			locCameraToPos(-7, 2, 20.7, false);
			locCameraTarget(characterFromID("Rimalier"));
			LAi_SetActorType(pchar);
			sld = characterFromId("Rimalier");
			LAi_ActorRunToLocator(sld, "item", "flower8", "Old_campfire_42_11", -1);
			sld = characterFromId("Etien_Marso");
			LAi_ActorFollow(sld, characterFromID("Rimalier"), "", -1);
			LAi_ActorFollow(pchar, characterFromID("Rimalier"), "", -1);
		break;

		case "Old_campfire_42_11":
			locCameraFromToPos(-5.8, 3, 12.3, false, -6, 1, -2.4);
			DoQuestCheckDelay("Old_campfire_42_12", 3);
		break;

		case "Old_campfire_42_12":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Rimalier");
			sld.Dialog.CurrentNode = "Joke_3";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_42":
			LAi_SetActorType(pchar);
			DoQuestReloadToLocation("Shore59", "officers", "sea_1", "Old_campfire_43");
			sld = characterFromID("Etien_Marso");
			LAi_SetStayType(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore59", "officers", "sea_2");
		break;

		case "Old_campfire_43":
			i = FindLocation("Tobago_Jungle_01");
			DeleteAttribute(&Locations[i], "models.always.mortirs");
			TEV.StopTimeScale = true; // запрет ускорения
			ChangeShowIntarface();
			locCameraFlyToPositionLookToPoint(-140, 5, 50.9, -17.3, 5, -6.1, -700.2, 2, 500.1, -1.0, 5000);
			pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Old_campfire_44", 8);
		break;

		case "Old_campfire_44":
			sld = characterFromID("Etien_Marso");
			LAi_ActorTurnToLocator(sld, "reload", "boat");
			LAi_ActorTurnToCharacter(pchar, characterFromID("Etien_Marso"));
			LAi_FadeEx(3.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Old_campfire_45", 4);
		break;

		case "Old_campfire_45":
			locCameraResetState();
			DoQuestCheckDelay("Old_campfire_46", 2);
		break;

		case "Old_campfire_46":
			DeleteAttribute(&TEV, "StopTimeScale");
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "Old_campfire_16";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_47":
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto15");
			sld = characterFromID("Rimalier");
			LAi_ActorFollow(sld, characterFromID("blaze"), "Old_campfire_48", -1);
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorFollow(sld, characterFromID("Rimalier"), "", -1);
		break;

		case "Old_campfire_48":
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Rimalier");
			sld.Dialog.CurrentNode = "dialog_16";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_49":
			AddQuestRecord("Old_campfire", "4");
			QuestPointerDelLoc("Shore59", "reload", "reload2_back"); // удалить поинт
			sld = characterFromId("Diego_de_Vargas");
			SetCharacterShipLocation(sld, "");
			StartBattleLandInterface(); // вкл интерфейс
			sld = characterFromID("Etien_Marso");
			LAi_ActorRunToLocation(sld, "officers", "sea_2", "none", "", "", "", -1);
			sld = characterFromID("Young_Boy_Bask");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorRunToLocation(sld, "officers", "sea_2", "none", "", "", "", -1);
			sld = characterFromID("Rimalier");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorRunToLocation(sld, "officers", "sea_2", "none", "", "", "", -1);
			pchar.quest.go_to_le_fransua_town.win_condition.l1 = "location";
			pchar.quest.go_to_le_fransua_town.win_condition.l1.location = "Martinique";
			pchar.quest.go_to_le_fransua_town.win_condition = "Old_campfire_49_1";
		break;

		case "Old_campfire_49_1":
			sld = characterFromID("Rimalier");
			TakeItemFromCharacter(sld, "mushket");
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			sld.model.animation = "man";
			Characters_RefreshModel(sld);
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "patrol", "patrol8");
			sld = characterFromID("Young_Boy_Bask");
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "patrol", "patrol8");
			sld = characterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "LeFransua_town", "patrol", "patrol8");
			pchar.quest.go_to_le_fransua_town_go_tavern.win_condition.l1 = "location";
			pchar.quest.go_to_le_fransua_town_go_tavern.win_condition.l1.location = "LeFransua_town";
			pchar.quest.go_to_le_fransua_town_go_tavern.win_condition = "Old_campfire_50";
		break;

		case "Old_campfire_50":
			sld = characterFromID("Etien_Marso");
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "Old_campfire_51", -1);
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "", -1);
			sld = characterFromID("Rimalier");
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "", -1);
		break;

		case "Old_campfire_51":
			FreeSitLocator("LeFransua_tavern", "sit2");
			FreeSitLocator("LeFransua_tavern", "sit3");
			FreeSitLocator("LeFransua_tavern", "sit_base1");
			FreeSitLocator("LeFransua_tavern", "sit_front1");
			sld = characterFromID("Etien_Marso");
			LAi_ActorSetSitMode(sld);
			ChangeCharacterAddressGroup(sld, "LeFransua_tavern", "sit", "sit2");
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorSetSitMode(sld);
			ChangeCharacterAddressGroup(sld, "LeFransua_tavern", "sit", "sit3");
			sld = characterFromID("Rimalier");
			LAi_ActorSetSitMode(sld);
			ChangeCharacterAddressGroup(sld, "LeFransua_tavern", "sit", "sit_base1");
			DoQuestReloadToLocation("LeFransua_tavern", "sit", "sit_front1", "Old_campfire_52");
		break;

		case "Old_campfire_52":
			sld = characterFromID("Rimalier");
			LAi_ActorTurnToLocator(sld, "sit", "sit_front1");
			LAi_ActorSetSitMode(sld);
			LAi_SetSitType(pchar);
			DoQuestCheckDelay("Old_campfire_53", 2);
		break;

		case "Old_campfire_53":
			sld = characterFromID("Rimalier");
			sld.Dialog.CurrentNode = "dialog_18";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
		break;

		case "Old_campfire_54":
			AddMapQuestMark_Major("LaVega_town", "Old_campfire", ""); // метка острова
			RemoveMapQuestMark("Shore59", "Old_campfire"); // убрать метку острова
			chrDisableReloadToLocation = false; // открыть локацию
			AddQuestRecord("Old_campfire", "5");
			log_info(StringFromKey("InfoMessages_271"));
			sld = characterFromID("Rimalier");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "LeFransua_tavern", "tables", "stay2");
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "LeFransua_tavern", "tables", "stay2");
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			Group_FindOrCreateGroup("Pirate_Attack_Martinique");
			Group_SetType("Pirate_Attack_Martinique", "trade");
			sld = GetCharacter(NPC_GenerateCharacter("Mansfelt_Capitan_Mart", "officer_2", "man", "man", CB_Rank(), PIRATE, -1, true));
			sld.DontRansackCaptain = true;
			FantomMakeCoolSailor(sld, SHIP_SLOOP, "", CANNON_TYPE_CANNON_LBS8, 70, 70, 70);
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade24", "pistol3", 60);
			CB_Perks(sld);
			Group_AddCharacter("Pirate_Attack_Martinique", "Mansfelt_Capitan_Mart");
			Group_SetGroupCommander("Pirate_Attack_Martinique", "Mansfelt_Capitan_Mart");
			Group_SetTaskAttack("Pirate_Attack_Martinique", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack_Martinique", "Martinique", "quest_ships", "quest_ship_6");
			Group_LockTask("Pirate_Attack_Martinique");
			pchar.quest.Sloop_Mart_Mans.win_condition.l1 = "location";
			pchar.quest.Sloop_Mart_Mans.win_condition.l1.location = "Martinique";
			pchar.quest.Sloop_Mart_Mans.win_condition = "Old_campfire_54_1";
		break;

		case "Old_campfire_54_1":
			AddQuestRecord("Old_campfire", "5.1");
			bQuestDisableMapEnter = true; // закрыть карту
			Island_SetReloadEnableGlobal("Martinique", false);
			pchar.quest.Mansfelt_Capitan_Mart_dead.win_condition.l1 = "NPC_death";
			pchar.quest.Mansfelt_Capitan_Mart_dead.win_condition.l1.character = "Mansfelt_Capitan_Mart";
			pchar.quest.Mansfelt_Capitan_Mart_dead.win_condition = "Old_campfire_54_2";
		break;

		case "Old_campfire_54_2":
			bQuestDisableMapEnter = false; // открыть карту
			Island_SetReloadEnableGlobal("Martinique", true); // на остров можно
			sld = characterFromID("Etien_Marso");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LaVega_town", "quest", "quest1");
			pchar.quest.Return_La_Vega.win_condition.l1 = "location";
			pchar.quest.Return_La_Vega.win_condition.l1.location = "LaVega_town";
			pchar.quest.Return_La_Vega.win_condition = "Old_campfire_54_3";
		break;

		case "Old_campfire_54_3":
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "La_Vega_1";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Old_campfire_56":
			QuestPointerToLoc("LaVega_tavern", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("LaVega_town", "reload", "reload2_back"); // поставить поинт
			sld = characterFromID("Etien_Marso");
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromID("Rimalier");
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "goto", "ass2");
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "goto", "ass3");
			locations[FindLocation("LaVega_ExitTown")].bonfire = true;
			pchar.quest.Old_campfire_fire_exittown.win_condition.l1 = "location";
			pchar.quest.Old_campfire_fire_exittown.win_condition.l1.location = "LaVega_ExitTown";
			pchar.quest.Old_campfire_fire_exittown.win_condition = "Old_campfire_57";
		break;

		case "Old_campfire_57":
			AoP_OfficersSetCitizen();
			TEV.StopTimeScale = true; // запрет ускорения
			InterfaceStates.Buttons.Save.enable = 0;
			QuestPointerDelLoc("LaVega_tavern", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("LaVega_town", "reload", "reload2_back"); // удалить поинт
			ChangeCharacterAddressGroup(pchar, "LaVega_ExitTown", "goto", "goto2");
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, characterFromID("Etien_Marso"), "", -1);
			sld = characterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "ass1", "", -1);
			locCameraFlyToPositionLookToPoint(-2.1, 2, -22.3, -4.4, 1, -15.4, 0, 2, -27.6, -1.0, 500);
			pchar.FuncCameraFly = "Old_campfire_function_5";
			DoQuestCheckDelay("Old_campfire_58", 0.3);
		break;

		case "Old_campfire_58":
			ChangeShowIntarface();
		break;

		case "Old_campfire_59":
			LAi_FadeEx(3.0, 2.0, 1.0, "", "", "");
			DoQuestCheckDelay("Old_campfire_60", 4);
		break;

		case "Old_campfire_60":
			sld = GetCharacter(NPC_GenerateCharacter("Fake_Etien_Marso", "Estienne_Marso", "man", "man", 30, PIRATE, -1, false));
			LAi_SetActorType(sld);
			sld.name = FindPersonalName("Etien_Marso_name");
			sld.lastname = FindPersonalName("Etien_Marso_lastname");
			sld.dialog.filename = "Quest\Lebasque\Marso_dialog.c";
			ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "goto", "goto3");
			locCameraFromToPos(2.8, 2, -22.8, true, -0.7, 0, -25.5);
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Ground_SitDown", "", -1);
			ChangeCharacterAddressGroup(pchar, "LaVega_ExitTown", "goto", "ass1");
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_SitDown", "", -1);
			ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "goto", "ass4");
			DoQuestCheckDelay("Old_campfire_61", 4);
		break;

		case "Old_campfire_61":
			LAi_SetGroundSitType(pchar);
			sld = characterFromID("Fake_Etien_Marso");
			sld.Dialog.CurrentNode = "Old_campfire_22";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_62":
			locCameraFromToPos(2.8, 2, -22.8, true, -0.7, 0, -25.5);
			sld = characterFromID("Fake_Etien_Marso");
			sld.name = FindPersonalName("Rimalier_name");
			sld.lastname = FindPersonalName("Rimalier_lastname");
			sld.Dialog.CurrentNode = "Old_campfire_25";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_63":
			locCameraFromToPos(2.8, 2, -22.8, true, -0.7, 0, -25.5);
			sld = characterFromID("Fake_Etien_Marso");
			sld.name = FindPersonalName("Young_Boy_Bask_name");
			sld.lastname = "";
			sld.Dialog.CurrentNode = "Old_campfire_26";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_64":
			locCameraFromToPos(2.8, 2, -22.8, true, -0.7, 0, -25.5);
			sld = characterFromID("Fake_Etien_Marso");
			sld.name = FindPersonalName("Etien_Marso_name");
			sld.lastname = FindPersonalName("Etien_Marso_lastname");
			sld.Dialog.CurrentNode = "Old_campfire_27";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Old_campfire_65":
			sld = characterFromID("Fake_Etien_Marso");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			locCameraFromToPos(2.8, 2, -22.8, true, -0.7, 0, -25.5);
			LAi_FadeEx(2.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Old_campfire_66", 3);
		break;

		case "Old_campfire_66":
			AoP_OfficersRestore();
			DeleteAttribute(&TEV, "StopTimeScale");
			InterfaceStates.Buttons.Save.enable = 1;
			DeleteAttribute(&locations[FindLocation("LaVega_ExitTown")], "DisableEncounters");
			locations[FindLocation("SantoDomingo_ExitTown")].DisableEncounters = true;
			StartBattleLandInterface(); // вкл интерфейс
			locCameraResetState();
			locations[FindLocation("LaVega_ExitTown")].bonfire = false;
			LAi_SetPLayerType(pchar);
			sld = characterFromID("Etien_Marso");
			LAi_SetFreeFighter(sld);
			LAi_CharacterDisableDialog(sld);
			sld = characterFromID("Rimalier");
			sld.model.animation = "mushketer";
			GiveItem2Character(sld, "mushket");
			EquipCharacterByItem(sld, "mushket");
			LAi_SetFreeFighter(sld);
			LAi_CharacterDisableDialog(sld);
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetFreeFighter(sld);
			LAi_CharacterDisableDialog(sld);
			QuestPointerToLoc("Hispaniola_Jungle_01", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Hispaniola_Jungle_02", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Hispaniola_Jungle_03", "reload", "reload5_back"); // поставить поинт
			QuestPointerToLoc("LaVega_ExitTown", "reload", "reload2_back"); // поставить поинт
			AddQuestRecord("Old_campfire", "6");
			pchar.quest.SantoDoming_change_form.win_condition.l1 = "location";
			pchar.quest.SantoDoming_change_form.win_condition.l1.location = "SantoDomingo_ExitTown";
			pchar.quest.SantoDoming_change_form.win_condition = "Old_campfire_67";
			LocatorReloadEnterDisable("SantoDomingo_ExitTown", "reload3_back", true);
			LocatorReloadEnterDisable("SantoDomingo_ExitTown", "reload2_back", true);
			LocatorReloadEnterDisable("Hispaniola_Jungle_01", "reload2_back", true);
			LocatorReloadEnterDisable("Hispaniola_Jungle_02", "reload2_back", true);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload3_back", true);
		break;

		case "Old_campfire_67":
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = characterFromID("Etien_Marso");
			LAi_CharacterEnableDialog(sld);
			ChangeCharacterAddressGroup(sld, "SantoDomingo_ExitTown", "rld", "loc0");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Old_campfire_28";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Old_campfire_69":
			sld = characterFromID("Etien_Marso");
			LAi_CharacterDisableDialog(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			chrDisableReloadToLocation = false; // открыть локацию
			QuestPointerToLoc("SantoDomingo_town", "reload", "reload_jail"); // поставить поинт
			QuestPointerDelLoc("Hispaniola_Jungle_01", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Hispaniola_Jungle_02", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Hispaniola_Jungle_03", "reload", "reload5_back"); // удалить поинт
			QuestPointerDelLoc("LaVega_ExitTown", "reload", "reload2_back"); // удалить поинт
			pchar.quest.prison_santo_domingo_campfire.win_condition.l1 = "location";
			pchar.quest.prison_santo_domingo_campfire.win_condition.l1.location = "SantoDomingo_prison";
			pchar.quest.prison_santo_domingo_campfire.win_condition = "Old_campfire_71";
			pchar.quest.jail_fightcheck = "active";
			DoQuestCheckDelay("Old_campfire_CheckJailFight", 3);
		break;

		case "Old_campfire_CheckJailFight": // проверка на боевой режим. Если бой - тюрьма закрыта. Мир - открыта.
			i = FindLocation("SantoDomingo_prison");
			locations[i].DisableOfficers = 1;
			if (!CheckAttribute(pchar, "quest.jail_fightcheck")) break;
			if (pchar.quest.jail_fightcheck != "active") break;
			bool bFight = LAi_group_IsActivePlayerAlarm();
			if (bFight)
			{
				LocatorReloadEnterDisable("SantoDomingo_town", "reload_jail", true);
			}
			else
			{
				LocatorReloadEnterDisable("SantoDomingo_town", "reload_jail", false);
			}
			DoQuestCheckDelay("Old_campfire_CheckJailFight", 1);
		break;

		case "Old_campfire_71":
			LAi_SetActorType(pchar);
			chrDisableReloadToLocation = true; // закрыть локацию
			ChangeCharacterAddressGroup(pchar, "SantoDomingo_prison", "reload", "reload1");
			sld = characterFromID("Etien_Marso");
			LAi_CharacterEnableDialog(sld);
			LAi_SetStayType(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantoDomingo_prison", "quest", "quest_jail");
			sld = characterFromID("Rimalier");
			LAi_SetStayType(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantoDomingo_prison", "goto", "goto17");
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetStayType(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantoDomingo_prison", "quest", "quest_jako");
			DoQuestCheckDelay("Old_campfire_72", 0.3);
		break;

		case "Old_campfire_72":
			pchar.quest.jail_fightcheck = "off";
			DeleteAttribute(pchar, "quest.jail_fightcheck");
			LocatorReloadEnterDisable("SantoDomingo_town", "reload_jail", false);
			TEV.StopTimeScale = true; // запрет ускорения
			ChangeShowIntarface();
			sld = characterFromID("Etien_Marso");
			LAi_ActorTurnToLocator(sld, "quest", "quest_bask");
			sld = characterFromID("Rimalier");
			LAi_ActorTurnToLocator(sld, "quest", "quest_bask");
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorTurnToLocator(sld, "quest", "quest_bask");
			locCameraToPos(10.4, 2.5, -9.9, false);
			locCameraTarget(characterFromID("Etien_Marso"));
			sld = characterFromID("Etien_Marso");
			LAi_ActorGoToLocator(sld, "quest", "quest_bask", "Old_campfire_72_1", -1);
		break;

		case "Old_campfire_73":
			sld = GetCharacter(NPC_GenerateCharacter("Off_Mansfelt", "officer_12", "man", "man", 1, PIRATE, -1, true));
			GiveItem2Character(sld, "unarmed");
			sld.equip.blade = "unarmed";
			sld.equip.gun = "";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SantoDomingo_prison", "goto", "goto19");
			DoQuestCheckDelay("Old_campfire_74", 0.1);
		break;

		case "Old_campfire_74":
			locCameraFromToPos(7.9, 2, -12.8, false, 11.9, -1, -9.8);
			LAi_SetActorType(pchar);
			sld = characterFromID("Off_Mansfelt");
			LAi_ActorGoToLocator(sld, "quest", "quest_jail", "Old_campfire_75", -1);
		break;

		case "Old_campfire_75":
			LAi_FadeEx(2.0, 2.0, 0, "", "Old_campfire_function_6", "");
		break;

		case "Old_campfire_72_1":
			sld = characterFromId("Etien_Marso");
			LAi_ActorTurnToCharacter(sld, characterFromID("SantoDomingoJailOff"));
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_1"));
			AoP_NPCDialogAddLine("SantoDomingoJailOff", StringFromKey("LeBasque_SantoDomingoJailOff_1"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_2"));
			AoP_NPCDialogAddLine("SantoDomingoJailOff", StringFromKey("LeBasque_SantoDomingoJailOff_2"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_3"));
			AoP_NPCDialogAddLine("SantoDomingoJailOff", StringFromKey("LeBasque_SantoDomingoJailOff_3"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_4"));
			AoP_NPCDialogAddLine("SantoDomingoJailOff", StringFromKey("LeBasque_SantoDomingoJailOff_4"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_5"));
			AoP_NPCDialogAddLine("SantoDomingoJailOff", StringFromKey("LeBasque_SantoDomingoJailOff_5"));
			AoP_NPCDialogLaunch("Etien_Marso", "SantoDomingoJailOff", "Old_campfire_72_2");
		break;

		case "Old_campfire_72_2":
			LAi_SetActorType(pchar);
			sld = characterFromID("SantoDomingoJailOff");
			sld.Dialog.CurrentNode = "Old_campfire_Jail_exit";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Old_campfire_77":
			LocatorReloadEnterDisable("SantoDomingo_ExitTown", "reload3_back", false);
			LocatorReloadEnterDisable("SantoDomingo_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("Hispaniola_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Hispaniola_Jungle_02", "reload2_back", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload3_back", false);
			DeleteAttribute(&TEV, "StopTimeScale");
			LAi_SetPlayerType(pchar);
			WaitDate("", 0, 0, 0, 1, 35); // мотаем время
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_273"), "Reload_To_Location", 0.1, 3.0);
			SetLaunchFrameReloadLocationParam("LaVega_ExitTown", "goto", "goto5", "Old_campfire_78");
			LaunchFrameForm();
			sld = characterFromID("Rimalier");
			sld.model = "Rimalier";
			ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "rld", "loc1");
			sld = characterFromID("Etien_Marso");
			sld.model = "Estienne_Marso";
			ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "goto", "goto6");
			sld = characterFromID("Young_Boy_Bask");
			GiveItem2Character(sld, "blade3");
			EquipCharacterByItem(sld, "blade3");
			GiveItem2Character(sld, "pistol2");
			EquipCharacterByItem(sld, "pistol2");
			ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "rld", "loc1");
			sld = characterFromID("Off_Mansfelt");
			ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "rld", "loc1");
		break;

		case "Old_campfire_78":
			i = FindLocation("SantoDomingo_prison");
			DeleteAttribute(&locations[i], "DisableOfficers");
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Old_campfire_33";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromID("Rimalier");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Etien_Marso"), "", -1);
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Etien_Marso"), "", -1);
			sld = characterFromID("Off_Mansfelt");
			LAi_ActorFollow(sld, characterFromID("Etien_Marso"), "", -1);
		break;

		case "Old_campfire_79":
			for (i = 1; i <= 6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Pirate_LaVega_ExitTown_" + i, "pirate_" + i, "man", "man", CB_Rank(), PIRATE, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
				CB_Perks(sld);
				sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "LaVega_ExitTown", "rld", "loc0");
			}
			DoQuestCheckDelay("Old_campfire_80", 0.5);
		break;

		case "Old_campfire_80":
			sld = characterFromID("Pirate_LaVega_ExitTown_1");
			sld.Dialog.CurrentNode = "Pirate_ExitTown_1";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i = 1; i <= 5; i++)
			{
				sld = characterFromID("Pirate_LaVega_ExitTown_" + (1 + i));
				LAi_ActorFollow(sld, characterFromID("Pirate_LaVega_ExitTown_1"), "", -1);
			}
			sld = characterFromID("Rimalier");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			sld = characterFromID("Etien_Marso");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
		break;

		case "Old_campfire_80_1":
			sld = characterFromID("Pirate_LaVega_ExitTown_1");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Old_campfire_80_2", -1);
		break;

		case "Old_campfire_80_2":
			for (i = 1; i <= 6; i++)
			{
				sld = characterFromID("Pirate_LaVega_ExitTown_" + i);
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Old_campfire_35";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Old_campfire_80_3":
			sld = characterFromID("Etien_Marso");
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Old_campfire_80_4", -1);
			sld = characterFromID("Rimalier");
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Etien_Marso"), "", -1);
			sld = characterFromID("Off_Mansfelt");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Etien_Marso"), "", -1);
			sld = characterFromID("Young_Boy_Bask");
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Etien_Marso"), "", -1);
		break;

		case "Old_campfire_80_4":
			sld = characterFromID("Rimalier");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromID("Off_Mansfelt");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromID("Young_Boy_Bask");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			chrDisableReloadToLocation = false; // открыть локацию
			AddQuestRecord("Old_campfire", "7");
			SetTimerCondition("Old_campfire_81", 0, 0, 1, false);
		break;

		case "Old_campfire_80_1_1":
			MakeQuestAutoSave();
			for (i = 1; i <= 6; i++)
			{
				sld = characterFromID("Pirate_LaVega_ExitTown_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Pirate_Jungle_Group_Campfire");
			}
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromID("Etien_Marso");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromID("Rimalier");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Pirate_Jungle_Group_Campfire", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Pirate_Jungle_Group_Campfire", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Pirate_Jungle_Group_Campfire", "Old_campfire_80_1_2");
		break;

		case "Old_campfire_80_1_2":
			LAi_group_Delete("Pirate_Jungle_Group_Campfire");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Old_campfire_36";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Old_campfire_81":
			sld = characterFromID("Etien_Marso");
			AddLandQuestmark_Main(sld, "Old_campfire");
			sld.Dialog.CurrentNode = "Old_campfire_37";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "LaVega_town", "quest", "quest1");
		break;

		case "Old_campfire_82":
			QuestPointerDelLoc("SantoDomingo_town", "reload", "reload_jail"); // удалить поинт
			RemoveMapQuestMark("LaVega_town", "Old_campfire"); // убрать метку острова
			chrDisableReloadToLocation = true; // закрыть локацию
			AddMapQuestMark_Major("Shore66", "Old_campfire", ""); // метка острова
			sld = characterFromID("Rimalier");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromID("Young_Boy_Bask");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Old_campfire_83", -1);
			AddQuestRecord("Old_campfire", "8");
		break;

		case "Old_campfire_83":
			DeleteAttribute(&locations[FindLocation("SantoDomingo_ExitTown")], "DisableEncounters");
			chrDisableReloadToLocation = false; // открыть локацию
			sld = characterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Shore66", "goto", "goto9");
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetStayType(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore66", "goto", "goto6");
			sld = characterFromID("Rimalier");
			LAi_SetStayType(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore66", "goto", "goto6");
			pchar.quest.Return_Tortuga_Campfire.win_condition.l1 = "location";
			pchar.quest.Return_Tortuga_Campfire.win_condition.l1.location = "Shore66";
			pchar.quest.Return_Tortuga_Campfire.win_condition = "Old_campfire_84";
		break;

		case "Old_campfire_84":
			sld = characterFromId("Rimalier");
			RemovePassenger(pchar, sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			sld = characterFromId("Young_Boy_Bask");
			RemovePassenger(pchar, sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			sld = characterFromId("Etien_Marso");
			RemovePassenger(pchar, sld);
			sld.Dialog.CurrentNode = "Old_campfire_39";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Old_campfire_85":
			RemoveMapQuestMark("Shore66", "Old_campfire"); // убрать метку острова
			sld = characterFromId("Etien_Marso");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Bucaneer_Outpost_Townhall", "goto", "goto_marso", "", -1);
			AddQuestRecord("Old_campfire", "9");
			ChangeBuccaneerRelation(10.0); // +10 к отношениям с буканьерами
			CloseQuestHeader("Old_campfire");
			SetTimerCondition("Hunting_huntsman_1", 0, 0, 1, false);
			SetBuccaneerService(2);
			Achievment_Set(ACH_Old_campfire);
		break;

		// Третий квест линейки ле Баска. Охота на гончих.
		case "Hunting_huntsman_1":
			LocatorReloadEnterDisable("Bucaneer_Outpost", "reload6_back", false); // открыть дом ле Баска
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Hunting_huntsman_1";
		break;

		case "Hunting_huntsman_2":
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Hunting_huntsman_1";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Hunting_huntsman_3":
			LAi_SetActorType(pchar);
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Hunting_huntsman_9";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Hunting_huntsman_4":
			AddMapQuestMark_Major("Havana_town", "Hunting_huntsman", ""); // метка острова
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Hunting_huntsman_second";
			AddQuestRecord("Hunting_huntsman", "0");
			LAi_SetPlayerType(pchar);
			sld = GetCharacter(NPC_GenerateCharacter("Gaspar_Leru", "trader_5", "man", "man", CB_Rank(), PIRATE, -1, true));
			sld.name = FindPersonalName("Gaspar_Leru_name");
			sld.lastname = FindPersonalName("Gaspar_Leru_lastname");
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Leru_1";
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Havana_tavern", "sit", "sit1");
		break;

		case "Hunting_huntsman_4_fail":
			LocatorReloadEnterDisable("Bucaneer_Outpost", "reload6_back", true); // закрыть дом ле Баска
			RemoveMapQuestMark("Havana_town", "Hunting_huntsman");
			sld = characterFromId("Etien_Marso");
			sld.lifeday = 0;
			sld = characterFromId("Gaspar_Leru");
			RemoveLandQuestmark_Main(sld, "Hunting_huntsman");
			sld.lifeday = 0;
			AddQuestRecord("Hunting_huntsman", "3");
			CloseQuestHeader("Hunting_huntsman");
			pchar.questTemp.AoP.LaPalomaOutcome = "sunk";
			pchar.quest.LaPaloma_ShipSink.over = "yes";
			Map_ReleaseQuestEncounter("Esteban_Molina");
			group_DeleteGroup("LaPaloma_Group");
			// снять квестовые локи с Рималье
			DeleteAttribute(pchar, "questTemp.Brides_Tortuga.RimalierDismissLocked");
			sld = characterFromId("Rimalier");
			SetCharacterRemovable(sld, true);
		break;

		case "Hunting_huntsman_5":
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Hunting_huntsman_12";

			sld = characterFromId("Esteban_Molina");
			RemovePassenger(pchar, sld);
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost_Townhall", "goto", "goto_marso");
			CharacterTurnToLoc(sld, "sit", "sit1");
		break;

		case "Hunting_huntsman_6":
			locations[FindLocation("Tortuga_Jungle_02")].locators_radius.quest.quest1 = 2;
			locations[FindLocation("Tortuga_Jungle_02")].DisableEncounters = true;
			QuestPointerDelLoc("Bucaneer_Outpost", "reload", "reload6_back"); // удалить поинт
			QuestPointerToLoc("Bucaneer_Outpost", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Tortuga_Jungle_02", "item", "hat"); // поставить поинт
			AddQuestRecord("Hunting_huntsman", "5");
			sld = ItemsFromID("Jako_hat");
			sld.shown = true;
			sld.startLocation = "Tortuga_Jungle_02";
			sld.startLocator = "hat";
			pchar.quest.Jako_hat.win_condition.l1 = "locator";
			pchar.quest.Jako_hat.win_condition.l1.location = "Tortuga_Jungle_02";
			pchar.quest.Jako_hat.win_condition.l1.locator_group = "quest";
			pchar.quest.Jako_hat.win_condition.l1.locator = "quest1";
			pchar.quest.Jako_hat.win_condition = "Hunting_huntsman_7";
		break;

		case "Hunting_huntsman_7":
			i = FindLocation("Tortuga_grot");
			locations[i].DisableOfficers = 1;
			pchar.Dialog.CurrentNode = "Hunting_huntsman_1";
			SelfDialog(pchar);
		break;

		case "Hunting_huntsman_8":
			QuestPointerDelLoc("Tortuga_Jungle_02", "item", "hat"); // удалить поинт
			QuestPointerToLoc("Tortuga_Jungle_02", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Tortuga_CaveEntrance", "reload", "reload1_back"); // поставить поинт
			sld = ItemsFromID("Jako_hat");
			sld.shown = false;
			sld = characterFromID("Young_Boy_Bask");
			GiveItem2Character(sld, "unarmed");
			sld.equip.blade = "unarmed";
			sld.equip.gun = "";
			sld.model = "Jacko_nohat";
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_grot", "goto", "goto1");
			sld = GetCharacter(NPC_GenerateCharacter("Hispan_Man_1", "officer_26", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(5) - 5, CB_Pistol() + rand(5) - 5, "blade22", "pistol2", 10);
			CB_Perks(sld);
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Spain_grot_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_grot", "monsters", "monster2");
			sld = GetCharacter(NPC_GenerateCharacter("Hispan_Man_2", "killer_1", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(5) - 5, CB_Pistol() + rand(5) - 5, "blade34", "pistol2", 10);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_grot", "item", "item1");
			sld = GetCharacter(NPC_GenerateCharacter("Hispan_Man_3", "killer_4", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(5) - 5, CB_Pistol() + rand(5) - 5, "blade15", "pistol2", 10);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_grot", "monsters", "monster1");
			pchar.quest.Tortuga_grot_huntsman.win_condition.l1 = "location";
			pchar.quest.Tortuga_grot_huntsman.win_condition.l1.location = "Tortuga_grot";
			pchar.quest.Tortuga_grot_huntsman.win_condition = "Hunting_huntsman_9";
		break;

		case "Hunting_huntsman_9":
			sld = characterFromId("Gaspar_Leru");
			sld.lifeday = 0;
			DeleteAttribute(&locations[FindLocation("Tortuga_Jungle_02")], "DisableEncounters");
			LAi_SetActorType(pchar);
			sld = characterFromID("Young_Boy_Bask");
			TeleportCharacterToPosAy(sld, 11.03, 0.57, 0.16, -1.50);
			sld = characterFromID("Hispan_Man_3");
			TeleportCharacterToPosAy(sld, 8.9, 0.49, 1.1, 2.80);
			sld = characterFromID("Hispan_Man_1");
			LAi_ActorTurnToCharacter(sld, characterFromID("Young_Boy_Bask"));
			DoQuestCheckDelay("Off_Interface", 0.2);
			locCameraFlyToPositionLookToPoint(0.1, 2, -0.7, 4.6, 2, -0.3, 11.03, 1.57, 0.16, -1.0, 2000);
			pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Hunting_huntsman_10", 2);
		break;

		case "Hunting_huntsman_10":
			ChangeShowIntarface();
			sld = characterFromID("Hispan_Man_1");
			LAi_ActorTurnToCharacter(sld, characterFromID("Young_Boy_Bask"));
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Hispan_Man_1", StringFromKey("LeBasque_Hispan_Man_1_1"));
			AoP_NPCDialogAddLine("Young_Boy_Bask", StringFromKey("LeBasque_Young_Boy_Bask_1"));
			AoP_NPCDialogLaunch("Young_Boy_Bask", "Hispan_Man_1", "Hunting_huntsman_11");
		break;

		case "Hunting_huntsman_11":
			LAi_FadeEx(1.0, 2.0, 1.0, "", "", "");
			DoQuestCheckDelay("Hunting_huntsman_12", 2);
		break;

		case "Hunting_huntsman_12":
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto1", "Hunting_huntsman_13", -1);
			locCameraResetState();
			sld = characterFromID("Hispan_Man_1");
			LAi_ActorTurnToCharacter(sld, characterFromID("blaze"));
			sld = characterFromID("Hispan_Man_2");
			LAi_ActorTurnToCharacter(sld, characterFromID("blaze"));
			sld = characterFromID("Hispan_Man_3");
			LAi_ActorTurnToCharacter(sld, characterFromID("blaze"));
		break;

		case "Hunting_huntsman_13":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Hispan_Man_1");
			sld.Dialog.CurrentNode = "Spain_grot_2";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Hunting_huntsman_14":
			DoQuestFunctionDelay("MakeQuestAutoSaveDelay", 1.0);
			chrDisableReloadToLocation = true; // закрыть локацию
			StartBattleLandInterface(); // вкл интерфейс
			for (i = 1; i <= 3; i++)
			{
				sld = characterFromId("Hispan_Man_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Tortuga_Grot_Team");
			}
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Tortuga_Grot_Team", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Tortuga_Grot_Team", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Tortuga_Grot_Team", "Hunting_huntsman_15");
		break;

		case "Hunting_huntsman_15":
			LAi_group_Delete("Tortuga_Grot_Team");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "", 3.5);
			DoQuestCheckDelay("Hunting_huntsman_16", 3.5);
		break;

		case "Hunting_huntsman_16":
			sld = characterFromID("Young_Boy_Bask");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Hunting_huntsman_1";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Hunting_huntsman_17":
			sld = characterFromID("Young_Boy_Bask");
			sld.model = "Jacko";
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost_townhall", "goto", "goto_marso");
			chrDisableReloadToLocation = false; // открыть локацию
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_274"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("Bucaneer_Outpost_townhall", "goto", "goto_gg", "Hunting_huntsman_18");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 40); // мотаем время
		break;

		case "Hunting_huntsman_18":
			i = FindLocation("Tortuga_grot");
			DeleteAttribute(&locations[i], "DisableOfficers");
			LAi_SetActorType(pchar);
			sld = characterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Hunting_huntsman_17";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Hunting_huntsman_19":
			AddQuestRecord("Hunting_huntsman", "6");
			QuestPointerDelLoc("Tortuga_Jungle_02", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Tortuga_CaveEntrance", "reload", "reload1_back"); // удалить поинт
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Young_Boy_Bask");
			GiveItem2Character(sld, "blade15");
			GiveItem2Character(sld, "pistol2");
			sld.equip.blade = "blade15";
			sld.equip.gun = "pistol2";
			AddPassenger(pchar, sld, false);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromID("Rimalier");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Go_Officer_1";
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_Jungle_02", "goto", "goto3");
		break;

		case "Hunting_huntsman_19_1":
			pchar.questTemp.Brides_Tortuga.RimalierDismissLocked = true;
			QuestPointerDelLoc("Bucaneer_Outpost", "reload", "reload1_back"); // удалить поинт
			AddQuestRecord("Hunting_huntsman", "6.1");
			SetTimerCondition("Hunting_huntsman_19_3", 0, 0, 1, false);
		break;

		case "Hunting_huntsman_19_2":
			QuestPointerDelLoc("Bucaneer_Outpost", "reload", "reload1_back"); // удалить поинт
			AddQuestRecord("Hunting_huntsman", "6.2");
			SetTimerCondition("Hunting_huntsman_19_3", 0, 0, 1, false);
		break;

		case "Hunting_huntsman_19_3":
			sld = characterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "Hunting_huntsman_3";
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost_townhall", "sit", "sit5");
		break;

		case "Hunting_huntsman_20":
			sld = characterFromID("Etien_Marso");
			FaceMaker(sld);
			//FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("Etien_Marso_ship"), CANNON_TYPE_CULVERINE_LBS24, 90, 90, 90);
			FantomMakeCoolSailor(sld, SHIP_CORVETTE, FindPersonalName("Etien_Marso_ship"), CANNON_TYPE_LBS_BY_SHIP, 82, 82, 82);
			SetCrewQuantityFull(sld);
			SetBaseShipData(sld);
			SetRandGeraldSail(sld, PIRATE);
			SetCharacterGoods(sld, GOOD_FOOD, 3500);
			SetCharacterGoods(sld, GOOD_BALLS, 500);
			SetCharacterGoods(sld, GOOD_GRAPES, 300);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 400);
			SetCharacterGoods(sld, GOOD_BOMBS, 1000);
			SetCharacterGoods(sld, GOOD_POWDER, 1500);
			SetCharacterGoods(sld, GOOD_PLANKS, 150);
			SetCharacterGoods(sld, GOOD_RUM, 800);
			SetCharacterGoods(sld, GOOD_WEAPON, 800);
			SetCharacterGoods(sld, GOOD_Medicament, 1000);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			Character_SetAbordageEnable(sld, false);
			sld.loyality = MAX_LOYALITY;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost_townhall", "goto", "goto5");
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			AddQuestRecord("Hunting_huntsman", "6.3");
			pchar.quest.Bermudes_huntsman.win_condition.l1 = "location";
			pchar.quest.Bermudes_huntsman.win_condition.l1.location = "Bermudes";
			pchar.quest.Bermudes_huntsman.win_condition = "Hunting_huntsman_21";
			pchar.quest.PuertoRico_huntsman.win_condition.l1 = "location";
			pchar.quest.PuertoRico_huntsman.win_condition.l1.location = "PuertoRico";
			pchar.quest.PuertoRico_huntsman.win_condition = "Hunting_huntsman_35";
			pchar.quest.Jamaica_huntsman.win_condition.l1 = "location";
			pchar.quest.Jamaica_huntsman.win_condition.l1.location = "Jamaica";
			pchar.quest.Jamaica_huntsman.win_condition = "Hunting_huntsman_71";
			AddMapQuestMark_Major("Bermudes", "Hunting_huntsman", ""); // метка острова
			AddMapQuestMark_Major("PuertoRico", "Hunting_huntsman", ""); // метка острова
			AddMapQuestMark_Major("Jamaica", "Hunting_huntsman", ""); // метка острова
		break;

		case "Hunting_huntsman_21":
			bQuestDisableMapEnter = true; // закрыть карту
			Island_SetReloadEnableGlobal("Bermudes", false); // на остров нельзя
			DoQuestCheckDelay("Hunting_huntsman_22", 2.5);
		break;

		case "Hunting_huntsman_22":
			MakeCloneShipDeck(pchar, true); // подмена палубы
			DoQuestReloadToLocation("Ship_deck", "goto", "goto5", "Hunting_huntsman_23");
			sld = CharacterFromID("Etien_Marso");
			LAi_SetStayType(sld);
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Hunting_huntsman_5";
			ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto6");
			for (i = 1; i <= 7; i++) //
			{
				sld = GetCharacter(NPC_GenerateCharacter("MainHero_Team" + i, "citiz_" + (39 - i), "man", "man", 5, PIRATE, 1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
				LAi_CharacterDisableDialog(sld);
				LAi_SetCitizenType(sld);
				ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto" + i);
			}
		break;

		case "Hunting_huntsman_23":
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Hunting_huntsman_24":
			SetCharacterShipLocation(pchar, "Pirates_town"); // корабль в порт
			setWDMPointXZ("Pirates_town"); // корабль в порт
			DoQuestReloadToLocation("Pirates_town", "reload", "reload1_back", "Hunting_huntsman_25");
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Pirates_town", "quest", "quest1");
		break;

		case "Hunting_huntsman_25":
			LocatorReloadEnterDisable("Pirates_town", "reload1_back", true); // закрыть выход в море
			sld = CharacterFromID("Pirates_tavernkeeper");
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			pchar.quest.Hunting_huntsman = "Talk_Tavern";
			sld = characterFromID("Etien_Marso");
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_SetOfficerType(sld);
			LAi_CharacterDisableDialog(sld);
			LAi_SetFreeFighter(sld);
		break;

		case "Hunting_huntsman_26":
			LocatorReloadEnterDisable("Pirates_town", "reload1_back", false); // открыть выход в море
			bQuestDisableMapEnter = false; // открыть карту
			Island_SetReloadEnableGlobal("Bermudes", true); // на остров можно
			pchar.quest.Hunting_huntsman = "";
			sld = GetCharacter(NPC_GenerateCharacter("Martin_Kesada_Officer", "portman_14", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "", 20);
			CB_Perks(sld);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship1", "goto", "goto5");
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			pchar.quest.Shore_ship1_huntsman.win_condition.l1 = "location";
			pchar.quest.Shore_ship1_huntsman.win_condition.l1.location = "Shore_ship1";
			pchar.quest.Shore_ship1_huntsman.win_condition = "Hunting_huntsman_27";
		break;

		case "Hunting_huntsman_27":
			sld = characterFromID("Martin_Kesada_Officer");
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Martin_Kesada_1";
			TeleportCharacterToPosAy(sld, 78.3, 1.8, 4.1, -1.80);
			LAi_SetStayType(sld);
		break;

		case "Hunting_huntsman_28":
			sld = characterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Hunting_huntsman_7";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Hunting_huntsman_29":
			LAi_SetActorType(pchar);
			sld = characterFromID("Etien_Marso");
			LAi_ActorTurnToCharacter(sld, characterFromID("Martin_Kesada_Officer"));
			LAi_ActorAnimation(sld, "Shot", "Hunting_huntsman_30", 1);
		break;

		case "Hunting_huntsman_30":
			sld = characterFromId("Martin_Kesada_Officer");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Hunting_huntsman_31", 2.0);
		break;

		case "Hunting_huntsman_31":
			LAi_SetPlayerType(pchar);

			sld = characterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "Hunting_huntsman_8";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Hunting_huntsman_32":
			AddQuestRecord("Hunting_huntsman", "7");
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = characterFromID("Etien_Marso");
			DeleteAttribute(sld, "FreeFighter");
			LAi_ActorRunToLocation(sld, "officers", "sea_1", "none", "", "", "Hunting_huntsman_33", -1);
		break;

		case "Hunting_huntsman_33":
			RemoveMapQuestMark("Bermudes", "Hunting_huntsman"); // убрать метку острова
			AddMapQuestMark_Major("Terks", "Hunting_huntsman", ""); // метка острова
			chrDisableReloadToLocation = false; // открыть локацию
			DoQuestFunctionDelay("Terks_Kesada", 0.0);
		break;

		case "Hunting_huntsman_34":
			StopMusic(0);
			KZ|MusicRandom("&Sea");
			RemoveMapQuestMark("Terks", "Hunting_huntsman"); // убрать метку острова
			AddQuestRecord("Hunting_huntsman", "8");
			pchar.questTemp.Hunting_huntsman.KesadaDead = true;
			if (CheckAttribute(pchar, "questTemp.Hunting_huntsman.KesadaDead") &&
			CheckAttribute(pchar, "questTemp.Hunting_huntsman.VelaDead") &&
			CheckAttribute(pchar, "questTemp.Hunting_huntsman.RojasDead"))
			{
				AddQuestRecord("Hunting_huntsman", "20");
				DoQuestCheckDelay("Hunting_huntsman_98", 0.5);
			}
		break;

		case "Hunting_huntsman_35":
			bQuestDisableMapEnter = true; // закрыть карту
			Island_SetReloadEnableGlobal("PuertoRico", false); // на остров нельзя
			DoQuestCheckDelay("Hunting_huntsman_36", 2.5);
		break;

		case "Hunting_huntsman_36":
			MakeCloneShipDeck(pchar, true); // подмена палубы
			DoQuestReloadToLocation("Ship_deck", "goto", "goto5", "Hunting_huntsman_37");
			sld = CharacterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "Hunting_huntsman_9";
			ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto6");
			sld = characterFromID("Young_Boy_Bask");
			ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto6");
			for (i = 1; i <= 7; i++) //
			{
				sld = GetCharacter(NPC_GenerateCharacter("MainHero_Team" + i, "citiz_" + (39 - i), "man", "man", 5, PIRATE, 1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
				LAi_CharacterDisableDialog(sld);
				LAi_SetCitizenType(sld);
				ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto" + i);
			}
		break;

		case "Hunting_huntsman_37":
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
		break;

		case "Hunting_huntsman_38":
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Hunting_huntsman_4";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Hunting_huntsman_39":
			sld = characterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "Hunting_huntsman_12";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Hunting_huntsman_40":
			SetCharacterShipLocation(pchar, "Shore45"); // корабль в бухту
			setWDMPointXZ("Shore45"); // корабль в порт
			DoQuestReloadToLocation("Shore45", "goto", "goto9", "Hunting_huntsman_41");
			LocatorReloadEnterDisable("Shore45", "boat", true); // закрыть корабль
			sld = characterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Shore45", "goto", "goto11");
			sld = characterFromID("Young_Boy_Bask");
			ChangeCharacterAddressGroup(sld, "Shore45", "goto", "goto11");
		break;

		case "Hunting_huntsman_41":
			AddQuestRecord("Hunting_huntsman", "9");
			sld = characterFromID("Etien_Marso");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			FreeSitLocator("SanJuan_Tavern", "sit_base1");
			sld = GetCharacter(NPC_GenerateCharacter("Bartolomeo_Huntsman", "trader_10", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Bartolomeo_Huntsman_name");
			sld.lastname = "";
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Bartolomeo_1";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "SanJuan_Tavern", "sit", "sit_base1");
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
		break;

		case "Hunting_huntsman_42":
			AddQuestRecord("Hunting_huntsman", "9.1");
			SetTimerCondition("Hunting_huntsman_42_1", 0, 0, 1, false);
		break;

		case "Hunting_huntsman_42_1":
			i = Findlocation("SanJuan_PortOffice");
			locations[i].locators_radius.item.item1 = 1.2;
			i = FindLocation("SanJuan_town");
			locations[i].reload.l10.close_for_night = 0;
			sld = characterFromID("SanJuan_Portman");
			LAi_SetLoginTime(sld, 6.0, 21.0);
			pchar.quest.SpawnBlank_SanJuan.win_condition.l1 = "location";
			pchar.quest.SpawnBlank_SanJuan.win_condition.l1.location = "SanJuan_PortOffice";
			pchar.quest.SpawnBlank_SanJuan.function = "CheckTimeForBlankSpawn";
		break;

		case "Hunting_huntsman_43":
			FreeSitLocator("SanJuan_tavern", "sit_front4");
			FreeSitLocator("SanJuan_tavern", "sit5");
			LAi_Fade("Hunting_huntsman_44", "");
		break;

		case "Hunting_huntsman_44":
			LAi_SetSitType(pchar);
			ChangeCharacterAddressGroup(pchar, "SanJuan_tavern", "sit", "sit5");
			sld = characterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "Hunting_huntsman_15";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SanJuan_tavern", "goto", "goto2");
		break;

		case "Hunting_huntsman_45":
			ChangeShowIntarface();
			locCameraFromToPos(-0.1, 2, 4.7, false, -2.5, 0, 6.3);
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorGoToLocator(sld, "tables", "stay5", "Hunting_huntsman_46", -1);
		break;

		case "Hunting_huntsman_46":
			LAi_FadeEx(1.0, 2.0, 1.0, "", "", "");
			DoQuestCheckDelay("Hunting_huntsman_47", 2);
		break;

		case "Hunting_huntsman_47":
			locCameraFromToPos(-3.6, 2, 2.6, false, -3.6, 0, 5.8);
			sld = characterFromID("Young_Boy_Bask");
			LAi_ActorSetSitMode(sld);
			ChangeCharacterAddressGroup(sld, "SanJuan_tavern", "sit", "sit_front4");
			DoQuestCheckDelay("Hunting_huntsman_48", 1.0);
		break;

		case "Hunting_huntsman_48":
			sld = characterFromID("Young_Boy_Bask");
			sld.Dialog.CurrentNode = "Hunting_huntsman_5";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Hunting_huntsman_49":
			AddQuestRecord("Hunting_huntsman", "11");
			log_info(StringFromKey("InfoMessages_271"));
			StartBattleLandInterface(); // вкл интерфейс
			sld = GetCharacter(NPC_GenerateCharacter("messenger_Huntsman", "usurer_9", "man", "man", CB_Rank() * 2, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank() * 2, CB_Fencing() * 2, CB_Pistol() * 2, "blade12", "pistol2", 20);
			CB_Perks(sld);
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Messenger_1";
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Shore45", "goto", "goto6");
			sld = GetCharacter(NPC_GenerateCharacter("Straj_Hunstman", "mush_ctz_6", "man", "mushketer", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
			CB_Perks(sld);
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Messenger_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore45", "goto", "goto7");
			pchar.quest.Shore45_hunting.win_condition.l1 = "location";
			pchar.quest.Shore45_hunting.win_condition.l1.location = "Shore45";
			pchar.quest.Shore45_hunting.win_condition = "Hunting_huntsman_49_1";
		break;

		case "Hunting_huntsman_49_1":
			sld = characterFromID("Straj_Hunstman");
			LAi_ActorTurnToCharacter(sld, characterFromID("messenger_Huntsman"));
		break;

		case "Hunting_huntsman_50":
			AddQuestRecord("Hunting_huntsman", "12");
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = characterFromID("messenger_Huntsman");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "", 3.5);
			DoQuestCheckDelay("Hunting_huntsman_51", 3.5);
		break;

		case "Hunting_huntsman_51":
			sld = characterFromID("messenger_Huntsman");
			LAi_ActorTurnToCharacter(sld, characterFromID("Straj_Hunstman"));
			LAi_ActorAnimation(sld, "Shot", "Hunting_huntsman_52", 1);
		break;

		case "Hunting_huntsman_52":
			sld = characterFromId("Straj_Hunstman");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Hunting_huntsman_53", 2.0);
		break;

		case "Hunting_huntsman_53":
			locCameraToPos(-3.7, 2.5, 7.1, false);
			locCameraTarget(characterFromID("messenger_Huntsman"));
			sld = characterFromID("messenger_Huntsman");
			sld.Dialog.CurrentNode = "Messenger_5";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Hunting_huntsman_54":
			sld = characterFromID("messenger_Huntsman");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "messenger_Huntsman_group");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("messenger_Huntsman_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("messenger_Huntsman_group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("messenger_Huntsman_group", "Hunting_huntsman_55");
		break;

		case "Hunting_huntsman_55":
			chrDisableReloadToLocation = false; // открыть локацию
			AddQuestRecord("Hunting_huntsman", "13");
			LAi_group_Delete("messenger_Huntsman_group");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = characterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromID("Young_Boy_Bask");
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			LAi_SetSitType(sld);
			sld.Dialog.CurrentNode = "Hunting_huntsman_9";
		break;

		case "Hunting_huntsman_56":
			i = Findlocation("SanJuan_Church");
			locations[i].locators_radius.barmen.stay = 0.5;
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SanJuan_tavern", "tables", "stay5");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			AddQuestRecord("Hunting_huntsman", "14");
			pchar.quest.church_go_night.win_condition.l1 = "location";
			pchar.quest.church_go_night.win_condition.l1.location = "SanJuan_Church";
			pchar.quest.church_go_night.win_condition = "Hunting_huntsman_57";
		break;

		case "Hunting_huntsman_57":
			pchar.GenQuest.CannotWait = true; // запрет ожидания
			TEV.StopTimeScale = true; // запрет ускорения
			chrDisableReloadToLocation = true; // закрыть локацию
			DoQuestCheckDelay("Hunting_huntsman_58", 1);
		break;

		case "Hunting_huntsman_58":
			sld = characterFromID("SanJuan_Priest");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_275"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("SanJuan_Church", "reload", "reload1", "Hunting_huntsman_59");
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0); // мотаем время
			SetCurrentTime(00, 00);
		break;

		case "Hunting_huntsman_59":
			DoQuestCheckDelay("Hunting_huntsman_60", 1.5);
		break;

		case "Hunting_huntsman_60":
			pchar.Dialog.CurrentNode = "Hunting_huntsman_2";
			SelfDialog(pchar);
		break;

		case "Hunting_huntsman_61":
			QuestPointerToLoc("SanJuan_Church", "barmen", "stay"); // поставить поинт
			pchar.quest.venez_cehin_church.win_condition.l1 = "locator";
			pchar.quest.venez_cehin_church.win_condition.l1.location = "SanJuan_Church";
			pchar.quest.venez_cehin_church.win_condition.l1.locator_group = "barmen";
			pchar.quest.venez_cehin_church.win_condition.l1.locator = "stay";
			pchar.quest.venez_cehin_church.win_condition = "Hunting_huntsman_62";
		break;

		case "Hunting_huntsman_62":
			QuestPointerDelLoc("SanJuan_Church", "barmen", "stay"); // удалить поинт
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload1");
			LAi_ActorAnimation(pchar, "Barman_idle", "", 3);
			DoQuestCheckDelay("Hunting_huntsman_63", 3);
		break;

		case "Hunting_huntsman_63":
			TakeNItemsNotification(pchar, "venezi_cehin", -1, "default", "", "");
			LAi_FadeEx(2.0, 2.0, 1.0, "", "", "");
			DoQuestCheckDelay("Hunting_huntsman_63_1", 4);
			DoQuestCheckDelay("Hunting_huntsman_64", 5);
		break;

		case "Hunting_huntsman_63_1":
			ref rItem = &Items[FindItem("letter_forged")];
			rItem.ItemType = "VARIETY";
			rItem.price = 69;
			sld = GetCharacter(NPC_GenerateCharacter("Ignasio_Vela", "Ignasio_Vella", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade12", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Ignasio_Vela_name");
			sld.lastname = FindPersonalName("Ignasio_Vela_lastname");
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Vela_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "SanJuan_Church", "barmen", "bar2");
			TeleportCharacterToPosAy(sld, 3.3, 0.13, -11.2, -1.80);
		break;

		case "Hunting_huntsman_64":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Ignasio_Vela");
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Hunting_huntsman_65":
			LAi_SetActorType(pchar);
			sld = characterFromId("Ignasio_Vela");
			LAi_ActorGoToLocator(sld, "goto", "goto_vela", "Hunting_huntsman_65_1", -1);
			LAi_ActorGoToLocator(pchar, "goto", "goto_gg_1", "Hunting_huntsman_65_2", -1);
		break;

		case "Hunting_huntsman_65_2":
			LAi_ActorFollow(pchar, characterFromID("Ignasio_Vela"), "Hunting_huntsman_66", -1);
		break;

		case "Hunting_huntsman_65_1":
			sld = characterFromId("Ignasio_Vela");
			LAi_ActorTurnToLocator(sld, "goto", "goto_gg");
		break;

		case "Hunting_huntsman_66":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Ignasio_Vela");
			sld.Dialog.CurrentNode = "Vela_2";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Hunting_huntsman_67":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			sld = characterFromId("Ignasio_Vela");
			sld.money = 3000;
			sld.DontClearDead = true;  // не убирать труп через 200с
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			Lai_SetHP(sld, 1.0, 1.0);
			LAi_SetStayType(sld);
			LAi_SetActorType(pchar);
			LAi_ActorAttack(pchar, sld, "Hunting_huntsman_68");
		break;

		case "Hunting_huntsman_68":
			DoQuestCheckDelay("Hunting_huntsman_69", 2);
		break;

		case "Hunting_huntsman_69":
			pchar.Dialog.CurrentNode = "Hunting_huntsman_3";
			SelfDialog(pchar);
		break;

		case "Hunting_huntsman_70":
			SetTimerCondition("Hunting_huntsman_70_1", 0, 0, 1, false);
			if (!CheckCharacterItem(pchar, "letter_forged"))
			{
				RemoveMapQuestMark("PuertoRico", "Hunting_huntsman"); // убрать метку острова
				LocatorReloadEnterDisable("Shore45", "boat", false); // открыть корабль
				bQuestDisableMapEnter = false; // открыть карту
				Island_SetReloadEnableGlobal("PuertoRico", true); // на остров можно
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); // запретить драться
				InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
				chrDisableReloadToLocation = false; // открыть локацию
				DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно ожидать
				DeleteAttribute(&TEV, "StopTimeScale"); // можно ускоряться
				Log_Info(StringFromKey("InfoMessages_276"));
				AddQuestRecord("Hunting_huntsman", "15");
				PostEvent("exitCancel", 100);
				sld = characterFromId("Ignasio_Vela");
				Dead_DelLoginedCharacter(sld); // больше нельзя обыскать его (чтобы не забрали письмо обратно, мало ли)
				pchar.questTemp.Hunting_huntsman.VelaDead = true;
				if (CheckAttribute(pchar, "questTemp.Hunting_huntsman.KesadaDead") &&
				CheckAttribute(pchar, "questTemp.Hunting_huntsman.VelaDead") &&
				CheckAttribute(pchar, "questTemp.Hunting_huntsman.RojasDead"))
				{
					AddQuestRecord("Hunting_huntsman", "20");
					DoQuestCheckDelay("Hunting_huntsman_98", 0.5);
				}
			}
			else
			{
				DoQuestCheckDelay("Hunting_huntsman_70", 0.5);
			}
		break;

		case "Hunting_huntsman_70_1":
			sld = characterFromID("SanJuan_Priest");
			ChangeCharacterAddressGroup(sld, "SanJuan_Church", "barmen", "stay");
		break;

		case "Hunting_huntsman_71":
			bQuestDisableMapEnter = true; // закрыть карту
			Island_SetReloadEnableGlobal("Jamaica", false); // на остров нельзя
			DoQuestCheckDelay("Hunting_huntsman_72", 2.5);
		break;

		case "Hunting_huntsman_72":
			LocatorReloadEnterDisable("Shore36", "boat", true); // закрыть корабль
			MakeCloneShipDeck(pchar, true); // подмена палубы
			DoQuestReloadToLocation("Ship_deck", "goto", "goto5", "Hunting_huntsman_73");
			sld = CharacterFromID("Etien_Marso");
			LAi_SetStayType(sld);
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Hunting_huntsman_17";
			ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto6");
			for (i = 1; i <= 7; i++) //
			{
				sld = GetCharacter(NPC_GenerateCharacter("MainHero_Team" + i, "citiz_" + (39 - i), "man", "man", 5, PIRATE, 1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
				LAi_CharacterDisableDialog(sld);
				LAi_SetCitizenType(sld);
				ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto" + i);
			}
		break;

		case "Hunting_huntsman_73":
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Hunting_huntsman_74":
			SetCharacterShipLocation(pchar, "Shore36"); // корабль в порт
			setWDMPointXZ("Shore36"); // корабль в порт
			DoQuestReloadToLocation("Shore36", "goto", "goto10", "Hunting_huntsman_75");
		break;

		case "Hunting_huntsman_75":
			AddQuestRecord("Hunting_huntsman", "16");
			QuestPointerToLoc("Shore36", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Jamaica_Jungle_02", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("Jamaica_Jungle_01", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("PortRoyal_ExitTown", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("PortRoyal_Fort", "reload", "reload2"); // поставить поинт
			sld = GetCharacter(NPC_GenerateCharacter("Captain_Hollis", "off_eng_6", "man", "man", CB_Rank(), ENGLAND, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade12", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Captain_Hollis_name");
			sld.lastname = FindPersonalName("Captain_Hollis_lastname");
			sld.dialog.filename = "Quest\Lebasque\Hollis_dialog.c";
			sld.Dialog.CurrentNode = "Hollis_friendly_1";
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_ammo", "goto", "goto5");
		break;

		case "Hunting_huntsman_76":
			AddQuestRecord("Hunting_huntsman", "18");
			QuestPointerDelLoc("Shore36", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Jamaica_Jungle_02", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("Jamaica_Jungle_01", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("PortRoyal_ExitTown", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("PortRoyal_Fort", "reload", "reload2"); // удалить поинт
			QuestPointerToLoc("Jamaica_Jungle_02", "reload", "reload3_back"); // поставить поинт
			QuestPointerToLoc("Jamaica_Jungle_01", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("PortRoyal_ExitTown", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("PortRoyal_Fort", "reload", "reload1_back"); // поставить поинт
			sld = CharacterFromID("Etien_Marso");
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			LAi_SetStayType(sld);
			sld.Dialog.CurrentNode = "Hunting_huntsman_24";
			ChangeCharacterAddressGroup(sld, "Shore36", "goto", "goto1");
		break;

		case "Hunting_huntsman_77":
			SetCharacterShipLocation(pchar, "Shore36"); // корабль в порт
			setWDMPointXZ("Shore36"); // корабль в порт
			DoQuestReloadToLocation("Shore36", "goto", "goto10", "Hunting_huntsman_78");
		break;

		case "Hunting_huntsman_78":
			AddQuestRecord("Hunting_huntsman", "17");
			QuestPointerToLoc("Shore36", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Jamaica_Jungle_02", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("Jamaica_Jungle_01", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("PortRoyal_ExitTown", "reload", "reload1_back"); // поставить поинт
			sld = GetCharacter(NPC_GenerateCharacter("Captain_Hollis", "off_eng_6", "man", "man", CB_Rank(), ENGLAND, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade12", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Captain_Hollis_name");
			sld.lastname = FindPersonalName("Captain_Hollis_lastname");
			sld.dialog.filename = "Quest\Lebasque\Hollis_dialog.c";
			sld.Dialog.CurrentNode = "Hollis_no_friendly_1";
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_Fort", "goto", "goto_captain");
		break;

		case "Hunting_huntsman_79":
			locations[FindLocation("Jamaica_Jungle_03")].DisableEncounters = true;
			locations[FindLocation("Jamaica_Jungle_02")].DisableEncounters = true;
			SetCurrentTime(23, 45);
			i = FindLocation("Jamaica_Jungle_03");
			if (i != -1)
			{
				Locations[i].QuestlockWeather = "Storm04_add";
				Locations[i].environment.weather.rain = true;
			}

			QuestPointerDelLoc("Jamaica_Jungle_02", "reload", "reload3_back"); // удалить поинт
			QuestPointerDelLoc("Jamaica_Jungle_01", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("PortRoyal_ExitTown", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("PortRoyal_Fort", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Shore36", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Jamaica_Jungle_02", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("Jamaica_Jungle_01", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("PortRoyal_ExitTown", "reload", "reload1_back"); // удалить поинт
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_277"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("Jamaica_Jungle_03", "rld", "aloc18", "Hunting_huntsman_80");
			LaunchFrameForm();
			WaitDate("", 0, 0, 1, 0, 0); // мотаем время
			string JLocat;
			int huntsman = 1;
			for (i = 1; i <= 8; i++)
			{
				JLocat = "goto" + (rand(9) + 1);

				sld = GetCharacter(NPC_GenerateCharacter("Mass_War_Friends_" + huntsman, "eng_mush_" + i, "man", "mushketer", CB_Rank(), ENGLAND, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_03", "goto", JLocat);

				huntsman++;
			}

			for (i = 1; i <= 10; i++)
			{
				JLocat = "goto" + (rand(9) + 1);

				sld = GetCharacter(NPC_GenerateCharacter("Mass_War_Friends_" + huntsman, "mush_ctz_" + i, "man", "mushketer", CB_Rank(), ENGLAND, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_03", "goto", JLocat);

				huntsman++;
			}

			for (i = 1; i <= 8; i++)
			{
				JLocat = "goto" + (rand(9) + 1);

				sld = GetCharacter(NPC_GenerateCharacter("Mass_War_Friends_" + huntsman, "citiz_" + (30 + i), "man", "man", CB_Rank(), ENGLAND, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				CB_Perks(sld);
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_03", "goto", JLocat);

				huntsman++;
			}

			for (i = 1; i <= 10; i++)
			{
				JLocat = "goto" + (rand(9) + 1);

				sld = GetCharacter(NPC_GenerateCharacter("Mass_War_Friends_" + huntsman, "pirate_" + i, "man", "man", CB_Rank(), ENGLAND, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade18", "pistol2", 20);
				CB_Perks(sld);
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_03", "goto", JLocat);

				huntsman++;
			}
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_03", "rld", "aloc17");
			sld = CharacterFromID("Rimalier");
			if (!IsOfficer(sld))
			{
				pchar.questTemp.AoP.RimalierForcedJamaicaBattle = true;
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_03", "rld", "aloc17");
			}
		break;

		case "Hunting_huntsman_80":
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			if (CheckAttribute(pchar, "questTemp.AoP.RimalierForcedJamaicaBattle"))
			{
				sld = CharacterFromID("Rimalier");
				if (!LAi_IsDead(sld))
				{
					LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
				}
			}
			sld = CharacterFromID("Captain_Hollis");
			LAi_CharacterEnableDialog(sld);
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			sld.Dialog.CurrentNode = "Hunting_huntsman_1";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_03", "rld", "aloc1");
		break;

		case "Hunting_huntsman_81":
			ChangeShowIntarface();
			locCameraFromToPos(-11.3, 31, -38.5, true, -10, 29, -61.7);
			for (i = 1; i <= 36; i++)
			{
				sld = CharacterFromID("Mass_War_Friends_" + i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			sld = CharacterFromID("Captain_Hollis");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "reload", "reload1_back", "none", "", "", "", -1);
			DoQuestCheckDelay("Hunting_huntsman_82", 1.5);
		break;

		case "Hunting_huntsman_82":
			PlaySound("Quest\LeBask\Bask4.mp3");
			DoQuestCheckDelay("Hunting_huntsman_83", 2.5);
		break;

		case "Hunting_huntsman_83":
			LAi_FadeEx(2.0, 2.0, 0, "", "", "");
			DoQuestCheckDelay("Hunting_huntsman_84", 3.5);
		break;

		case "Hunting_huntsman_84":
			DeleteAttribute(&WeatherParams, "Rain");
			i = FindLocation("Jamaica_jungle_03");
			if (i != -1)
			{
				DeleteAttribute(&Locations[i], "QuestlockWeather");
				DeleteAttribute(&Locations[i], "environment.weather.rain");
			}
			i = FindLocation("Jamaica_jungle_02");
			Locations[i].models.always.Spain_lager = "Pirate_Fort1";
			Locations[i].models.always.Pirate_Fort1.tech = "DLightModel";
			Locations[i].models.always.locators = "jungle2_locators_fort";
			Locations[i].models.always.grassPatch = "jungle3PirateFort_grass";
			locations[i].models.day.charactersPatch = "Pirate_Fort_Patch";
			locations[i].models.night.charactersPatch = "Pirate_Fort_Patch";
			Locations[i].QuestlockWeather = "Storm04_add";
			Locations[i].environment.weather.rain = true;
			DoQuestReloadToLocation("Jamaica_jungle_02", "rld", "loc1", "Hunting_huntsman_85");
			sld = GetCharacter(NPC_GenerateCharacter("Sebastian_Rohas", "elite_hol_1", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade12", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Sebastian_Rohas_name");
			sld.lastname = FindPersonalName("Sebastian_Rohas_lastname");
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Rohas_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Jamaica_jungle_02", "goto", "goto14");
			int enemyIdx = 1;
			for (i = 1; i <= 8; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mass_War_Enemy_" + enemyIdx, "spa_mush_" + (rand(7) + 1), "man", "mushketer", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 10);
				CB_Perks(sld);
				Lai_SetHP(sld, 190.0, 190.0);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "Mass_War_Hispan");
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "war" + i);
				enemyIdx++;
			}
			for (i = 1; i <= 8; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mass_War_Enemy_" + enemyIdx, "sold_spa_" + (8 + i), "man", "man", CB_Rank(), SPAIN, -1, true));
				CB_Perks(sld);
				Lai_SetHP(sld, 250.0, 250.0);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "Mass_War_Hispan");
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "war" + (6 + i));
				enemyIdx++;
			}
			for (i = 1; i <= 5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mass_War_Enemy_" + enemyIdx, "elite_hol_" + (1 + i), "man", "man", 30, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, 30, CB_Fencing() + rand(45), CB_Pistol() + rand(45), "blade28", "", 20);
				CB_Perks(sld);
				Lai_SetHP(sld, 600.0, 600.0);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "Mass_War_Hispan_1");
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "goto8");
				enemyIdx++;
			}
			for (i = 1; i <= 5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mass_War_Enemy_" + enemyIdx, "citiz_" + (50 + i), "man", "man", 20, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(30) - 5, CB_Pistol() + rand(30) - 5, "blade12", "pistol2", 20);
				CB_Perks(sld);
				Lai_SetHP(sld, 450.0, 450.0);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "Mass_War_Hispan_bunt");
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "goto9");
				enemyIdx++;
			}
			for (i = 1; i <= 8; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mass_War_Enemy_" + enemyIdx, "urban_spa_" + (rand(7) + 1), "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(25) - 5, CB_Pistol() + rand(25) - 5, "blade7", "pistol1", 20);
				CB_Perks(sld);
				Lai_SetHP(sld, 500.0, 500.0);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "Mass_War_Hispan_1");

				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "goto9");
				enemyIdx++;
			}
			for (i = 1; i <= 5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mass_War_Enemy_" + enemyIdx, "citiz_" + (50 + i), "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(25) - 5, CB_Pistol() + rand(25) - 5, "blade12", "pistol1", 20);
				CB_Perks(sld);
				Lai_SetHP(sld, 400.0, 400.0);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "Mass_War_Hispan_bunt");
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "goto8");
				enemyIdx++;
			}
			for (i = 1; i <= 16; i++)
			{
				sld = CharacterFromID("Mass_War_Friends_" + i);
				Lai_SetHP(sld, 250.0, 250.0);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "war" + (15 + i));
			}

			for (i = 1; i <= 10; i++)
			{
				sld = CharacterFromID("Mass_War_Friends_" + (16 + i));
				Lai_SetHP(sld, 250.0, 250.0);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "goto6");
			}
			for (i = 1; i <= 10; i++)
			{
				sld = CharacterFromID("Mass_War_Friends_" + (26 + i));
				Lai_SetHP(sld, 250.0, 250.0);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "goto18");
			}
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "goto20");
			sld = CharacterFromID("Captain_Hollis");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "goto20");
			sld = characterFromID("Young_Boy_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "goto20");
		break;

		case "Hunting_huntsman_85":
			PlaySound("People Fight\Boarding_People_01.wav");
			if (CheckAttribute(pchar, "questTemp.AoP.RimalierForcedJamaicaBattle"))
			{
				sld = CharacterFromID("Rimalier");
				if (!LAi_IsDead(sld))
				{
					LAi_SetActorType(sld);
					ChangeCharacterAddressGroup(sld, "Jamaica_Jungle_02", "goto", "goto5");
				}
			}
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorTurnToLocator(sld, "sound", "torch13");
			sld = CharacterFromID("Captain_Hollis");
			LAi_ActorTurnToLocator(sld, "sound", "torch13");
			sld = CharacterFromID("Young_Boy_Bask");
			LAi_ActorTurnToLocator(sld, "sound", "torch13");
			for (i = 1; i <= 6; i++)
			{
				sld = CharacterFromID("Mass_War_Enemy_" + i);
				LAi_ActorTurnToLocator(sld, "goto", "goto7");
			}
			for (i = 1; i <= 9; i++)
			{
				sld = CharacterFromID("Mass_War_Enemy_" + (6 + i));
				LAi_ActorTurnToLocator(sld, "sound", "torch13");
			}
			for (i = 1; i <= 16; i++)
			{
				sld = CharacterFromID("Mass_War_Friends_" + i);
				LAi_ActorTurnToLocator(sld, "sound", "torch13");
			}
			for (i = 16; i <= 25; i++)
			{
				sld = characterFromID("Mass_War_Enemy_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Mass_War_Hispan_1");
				sld = characterFromID("Mass_War_Enemy_" + (i + 10));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Mass_War_Hispan_bunt");
				LAi_group_SetRelation("Mass_War_Hispan_bunt", "Mass_War_Hispan_1", LAI_GROUP_ENEMY);
				LAi_group_FightGroups("Mass_War_Hispan_bunt", "Mass_War_Hispan_1", true);
			}
			pchar.quest.big_war_quest_3.win_condition.l1 = "location";
			pchar.quest.big_war_quest_3.win_condition.l1.location = "Jamaica_Jungle_02";
			pchar.quest.big_war_quest_3.function = "Hunting_huntsman_movie_1";
		break;

		case "Hunting_huntsman_86":
  		 	i = FindLocation(pchar.location);
    		Locations[i].AoP_HuntingFire4 = true;
    		PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
    		SetCameraShake(0.5, 5.0, 3.0, 1.2, 0.5, true, false, CAM_EASING_CUBE);
    		CreateLocationParticlesXZ("ShipExplode", "goto", "fire4", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
    		CreateLocationParticlesLoopedSound("shipfire", "goto", "fire4", 0.0, 0.0, 0.0, "fortfire");
    		DoQuestCheckDelay("Hunting_huntsman_87", 15.0);
		break;

		case "Hunting_huntsman_87":
    		i = FindLocation(pchar.location);
    		Locations[i].AoP_HuntingFire9 = true;
   			PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
  			SetCameraShake(0.5, 5.0, 3.0, 1.2, 0.5, true, false, CAM_EASING_CUBE);
  			CreateLocationParticlesXZ("ShipExplode", "goto", "fire9", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
   			CreateLocationParticlesLoopedSound("shipfire", "goto", "fire9", 0.0, 0.0, 0.0, "fortfire");
		break;

		case "Hunting_huntsman_88":
			LAi_group_Delete("MASS_WAR_JUNGLES");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = CharacterFromID("Sebastian_Rohas");
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "quest_rohas", "Hunting_huntsman_88_1", -1);
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "goto", "war3", "", -1);
			sld = CharacterFromID("Captain_Hollis");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "goto", "war4", "", -1);
			sld = CharacterFromID("Young_Boy_Bask");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "goto", "war5", "", -1);
			if (CheckAttribute(pchar, "questTemp.AoP.RimalierForcedJamaicaBattle"))
			{
				sld = CharacterFromID("Rimalier");
				if (!LAi_IsDead(sld))
				{
					LAi_SetActorType(sld);
					LAi_ActorRunToLocator(sld, "goto", "war6", "", -1);
				}
			}
			for (i = 1; i <= 36; i++)
			{
				int Live_Team = GetCharacterIndex("Mass_War_Friends_" + i);
				if (Live_Team != -1)
				{
					sld = &characters[Live_Team];
					if (!LAi_IsDead(sld))
					{
						LAi_SetCitizenType(sld);
						LAi_CharacterDisableDialog(sld);
					}
				}
			}
		break;

		case "Hunting_huntsman_88_1":
			sld = CharacterFromID("Sebastian_Rohas");
			LAi_ActorTurnToLocator(sld, "goto", "war4");
			DoQuestCheckDelay("Hunting_huntsman_88_2", 0.5);
		break;

		case "Hunting_huntsman_88_2":
			AoP_OfficersSetCitizen();
			sld = CharacterFromID("Sebastian_Rohas");
			LAi_SetStayType(sld);
		break;

		case "Hunting_huntsman_89":
			sld = CharacterFromID("Sebastian_Rohas");
			LAi_SetImmortal(sld, false);
			Lai_SetHP(sld, 400.0, 400.0);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "Sebastian_Rohas_Group");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Sebastian_Rohas_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Sebastian_Rohas_Group", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(sld, 10, true, "Hunting_huntsman_90"); // скрытое бессмертие
		break;

		case "Hunting_huntsman_90":
			LAi_group_Delete("Sebastian_Rohas_Group");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = CharacterFromID("Sebastian_Rohas");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Rohas_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Hunting_huntsman_91":
			ChangeShowIntarface();
			sld = CharacterFromID("Sebastian_Rohas");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Hunting_huntsman_93", 1.5);
		break;

		case "Hunting_huntsman_93":
			StartBattleLandInterface(); // вкл интерфейс
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Young_Boy_Bask");
			sld.Dialog.CurrentNode = "Hunting_huntsman_12";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Hunting_huntsman_94":
			sld = CharacterFromID("Young_Boy_Bask");
			LAi_ActorRunToLocator(sld, "goto", "war5", "", -1);
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Hunting_huntsman_28";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Hunting_huntsman_95":
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorRunToLocator(sld, "goto", "war3", "", -1);
			sld = characterFromId("Captain_Hollis");
			sld.Dialog.CurrentNode = "Hunting_huntsman_5";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Hunting_huntsman_96":
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			TEV.StopTimeScale = true; // запрет ускорения
			LAi_SetActorType(pchar);
			LAi_FadeEx(2.0, 2.0, 2.0, "", "Hunting_huntsman_movie_8", "");
			DoQuestCheckDelay("Hunting_huntsman_96_1", 3.0);
		break;

		case "Hunting_huntsman_96_1":
			ChangeCharacterAddressGroup(pchar, "Jamaica_jungle_02", "rld", "loc2");
			CreateLocationParticlesLoopedSound("shipfire", "goto", "fire1", 0.0, 0.0, 0, "fortfire");
			CreateLocationParticlesLoopedSound("shipfire", "goto", "fire2", 0.0, 0.0, 0, "fortfire");
			CreateLocationParticlesLoopedSound("shipfire", "goto", "fire3", 0.0, 0.0, 0, "fortfire");
			CreateLocationParticlesLoopedSound("shipfire", "goto", "fire5", 0.0, 0.0, 0, "fortfire");
			CreateLocationParticlesLoopedSound("shipfire", "goto", "fire6", 0.0, 0.0, 0, "fortfire");
			CreateLocationParticlesLoopedSound("shipfire", "goto", "fire7", 0.0, 0.0, 0, "fortfire");
			CreateLocationParticlesLoopedSound("shipfire", "goto", "fire8", 0.0, 0.0, 0, "fortfire");
			for (i = 1; i <= 36; i++)
			{
				int Live_Team_2 = GetCharacterIndex("Mass_War_Friends_" + i);
				if (Live_Team_2 != -1)
				{
					sld = &characters[Live_Team_2];
					if (!LAi_IsDead(sld))
					{
						sld.lifeday = 0;
						ChangeCharacterAddressGroup(sld, "none", "", "");
					}
				}
			}
			if (CheckAttribute(pchar, "questTemp.AoP.RimalierForcedJamaicaBattle"))
			{
				sld = CharacterFromID("Rimalier");
				ChangeCharacterAddressGroup(sld, "none", "", "");
				DeleteAttribute(pchar, "questTemp.AoP.RimalierForcedJamaicaBattle");
			}
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Captain_Hollis");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = CharacterFromID("Young_Boy_Bask");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			DeleteAttribute(&locations[FindLocation("Jamaica_Jungle_03")], "DisableEncounters");
			DeleteAttribute(&locations[FindLocation("Jamaica_Jungle_02")], "DisableEncounters");
		break;

		case "Hunting_huntsman_97":
			AoP_OfficersRestore();
			i = FindLocation("Jamaica_jungle_02");
			DeleteAttribute(&Locations[i], "models.always.Spain_lager");
			DeleteAttribute(&Locations[i], "AoP_HuntingFire4");
			DeleteAttribute(&Locations[i], "AoP_HuntingFire9");
			Locations[i].models.always.jungle = "jungle2";
			Locations[i].models.always.locators = "jungle2_locators";
			Locations[i].models.always.grassPatch = "jungle2_grass";
			locations[i].models.day.charactersPatch = "jungle2_patch";
			locations[i].models.night.charactersPatch = "jungle2_patch";
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Hunting_huntsman", "19");
			LocatorReloadEnterDisable("Shore36", "boat", false); // открыть корабль
			bQuestDisableMapEnter = false; // открыть карту
			Island_SetReloadEnableGlobal("Jamaica", true); // на остров можно
			RemoveMapQuestMark("Jamaica", "Hunting_huntsman"); // > убрать метку острова
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			DeleteAttribute(&TEV, "StopTimeScale"); // можно ускоряться
			pchar.questTemp.Hunting_huntsman.RojasDead = true;
			if (CheckAttribute(pchar, "questTemp.Hunting_huntsman.KesadaDead") &&
			CheckAttribute(pchar, "questTemp.Hunting_huntsman.VelaDead") &&
			CheckAttribute(pchar, "questTemp.Hunting_huntsman.RojasDead"))
			{
				AddQuestRecord("Hunting_huntsman", "20");
				DoQuestCheckDelay("Hunting_huntsman_98", 0.5);
			}
		break;

		case "Hunting_huntsman_98":
			sld = characterFromId("Young_Boy_Bask");
			sld.Dialog.CurrentNode = "Return_quest_3";
			RemovePassenger(pchar, sld);
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit4");
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Return_quest_3";
			RemoveCharacterCompanion(pchar, sld);
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit2");
			AddMapQuestMark_Major("Bucaneer_Outpost", "Hunting_huntsman", "");
			sld = characterFromId("Mishel_le_Bask");
			AddLandQuestmark_Main(sld, "Hunting_huntsman");
			sld.Dialog.CurrentNode = "Hunting_huntsman_24";
		break;

		case "Hunting_huntsman_99":
			AddQuestRecord("Hunting_huntsman", "21");
			ChangeBuccaneerRelation(10.0); // +10 к отношениям с буканьерами
			CloseQuestHeader("Hunting_huntsman");
			RemoveMapQuestMark("Bucaneer_Outpost", "Hunting_huntsman");
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Hunting_huntsman_28";
			SetTimerCondition("Brides_Tortuga_1", 0, 0, 7, false);
			SetTimerCondition("Hunting_huntsman_100", 0, 0, 3, false);
			SetBuccaneerService(3);
			Achievment_Set(ACH_Hunting_huntsman);
		break;

		case "Hunting_huntsman_100":
			sld = characterFromId("Young_Boy_Bask");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;

		// 4 квест
		case "Brides_Tortuga_1":
			sld = characterFromId("Mishel_le_Bask");
			AddLandQuestmark_Main(sld, "Brides_Tortuga");
			sld.Dialog.CurrentNode = "Brides_Tortuga_1";
		break;

		case "Brides_Tortuga_2":
			sld = characterFromId("fra_guber");
			AddLandQuestmark_Main(sld, "Brides_Tortuga");
			AddQuestRecord("Brides_Tortuga", "0");
			pchar.quest.Brides_Tortuga = "Talk_Guber";
		break;

		case "Brides_Tortuga_3":
			pchar.quest.Brides_Tortuga = "";
			QuestPointerToLoc("Tortuga_townhall", "reload", "reload3"); // поставить поинт
			sld = GetCharacter(NPC_GenerateCharacter("Henry_Tessie", "citiz_18", "man", "man", CB_Rank(), FRANCE, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "", "", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Henry_Tessie_name");
			sld.lastname = FindPersonalName("Henry_Tessie_lastname");
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Tessie_1";
			AddLandQuestmark_Main(sld, "Brides_Tortuga");
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_townhallRoom", "sit", "sit1");
		break;

		case "Brides_Tortuga_4":
			AddQuestRecord("Brides_Tortuga", "1");
			QuestPointerDelLoc("Tortuga_townhall", "reload", "reload3"); // удалить поинт
			sld = GetCharacter(NPC_GenerateCharacter("Old_Loren", "keeper_1", "man", "man", CB_Rank(), FRANCE, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "unarmed", "", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Old_Loren_name");
			sld.lastname = FindPersonalName("Old_Loren_lastname");
			sld.dialog.filename = "Quest\Lebasque\Loren_dialog.c";
			AddLandQuestmark_Main(sld, "Brides_Tortuga");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto25");
		break;

		case "Brides_Tortuga_5":
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = characterFromId("Kid_Brides");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Brides_Tortuga_6":
			AddQuestRecord("Brides_Tortuga", "2");
			DoQuestCheckDelay("Brides_Tortuga_7", 1.0);
		break;

		case "Brides_Tortuga_7":
			if (CheckAttribute(pchar, "questTemp.Brides_Tortuga.NightEventStarted"))
			{
				break;
			}
			if (pchar.location == "Tortuga_Graveyard" &&
			GetTime() >= 0.0 &&
			GetTime() < 4.0)
			{
				sld = CharacterFromID("Rimalier");
				if (IsOfficer(sld))
				{
					pchar.questTemp.AoP.RimalierWasOfficer = "1";
					sld.Dialog.CurrentNode = "Brides_Tortuga_Officer_1";
					LAi_SetActorType(sld);
				}
				else
				{
					pchar.questTemp.AoP.RimalierWasOfficer = "0";
					sld.Dialog.CurrentNode = "Brides_Tortuga_Officer_No_Officer_1";
					LAi_SetActorType(sld);
					ChangeCharacterAddressGroup(sld, "Tortuga_Graveyard", "officers", "reload2_3");
				}
				chrDisableReloadToLocation = true;
				pchar.questTemp.Brides_Tortuga.NightEventStarted = true;
				DoQuestCheckDelay("Brides_Tortuga_8", 1.0);
			}
			else
			{
				DoQuestCheckDelay("Brides_Tortuga_7", 1.0);
			}
		break;

		case "Brides_Tortuga_8":
			itm = ItemsFromID("strange_note");
			itm.price = 1;
			itm.ItemType = "VARIETY";
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = characterFromId("Henry_Tessie");
			sld.Dialog.CurrentNode = "Tessie_7";
			AddLandQuestmark_Main(sld, "Brides_Tortuga");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_Graveyard", "item", "read3");
			sld = characterFromId("Rimalier");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromId("Old_Loren");
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;

		case "Brides_Tortuga_9":
			ChangeShowIntarface();
			LAi_FadeEx(1.0, 2.0, 1.0, "", "", "");
			DoQuestCheckDelay("Brides_Tortuga_10", 2);
		break;

		case "Brides_Tortuga_10":
			LAi_SetActorType(pchar);
			TeleportCharacterToPosAy(pchar, -27.3, 3, 6.2, -1.50);
			LAi_ActorTurnToLocator(pchar, "goto", "goto9");
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			TEV.StopTimeScale = true; // запрет ускорения
			locCameraFlyToPositionLookToPoint(-9.4, 4, 8, -21.14, 4, -0.7, -3.9, 3.5, 13.8, -1.0, 900);
			pchar.FuncCameraFly = "Brides_Tortuga_1";
			sld = characterFromId("Assassins_Vargas_1");
			LAi_ActorGoToLocator(sld, "goto", "goto9", "", -1);
			sld = characterFromId("Assassins_Vargas_2");
			LAi_ActorFollow(sld, characterFromID("Assassins_Vargas_1"), "", -1);
			sld = characterFromId("Assassins_Vargas_3");
			LAi_ActorFollow(sld, characterFromID("Assassins_Vargas_1"), "", -1);
			sld = characterFromId("Assassins_Vargas_4");
			LAi_ActorGoToLocator(sld, "rld", "loc7", "", -1);
			sld = characterFromID("Rimalier");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_Graveyard", "reload", "reload4");
		break;

		case "Brides_Tortuga_11":
			for (i = 1; i <= 3; i++)
			{
				sld = characterFromId("Assassins_Vargas_" + i);
				LAi_ActorTurnToCharacter(sld, characterFromID("blaze"));
			}
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Henry_Tessie");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Tessie_11";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Brides_Tortuga_12":
			sld = characterFromId("Henry_Tessie");
			LAi_ActorAnimation(sld, "afraid", "", -1.0);
			locCameraToPos(-21.14, 4, -0.7, false);
			locCameraTarget(characterFromID("Rimalier"));
			sld = characterFromId("Rimalier");
			sld.Dialog.CurrentNode = "Brides_Tortuga_1";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Brides_Tortuga_13":
			LAi_SetActorType(pchar);
			locCameraFromToPos(-26.4, 5, -1, false, -10.8, 4, 9.8);
			sld = characterFromId("Rimalier");
			LAi_ActorRunToLocator(sld, "goto", "goto4", "Brides_Tortuga_14", -1);
		break;

		case "Brides_Tortuga_14":
			sld = characterFromID("Rimalier");
			LAi_ActorTurnToCharacter(sld, characterFromID("Assassins_Vargas_4"));
			LAi_ActorAnimation(sld, "Shot", "Brides_Tortuga_15", 1);
		break;

		case "Brides_Tortuga_15":
			sld = characterFromId("Assassins_Vargas_4");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Brides_Tortuga_16", 0.5);
		break;

		case "Brides_Tortuga_16":
			MakeQuestAutoSave();
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			DeleteAttribute(&TEV, "StopTimeScale"); // можно ускоряться
			locCameraResetState();
			locCameraTarget(pchar);
			StartBattleLandInterface(); // вкл интерфейс
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Rimalier");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i = 1; i <= 3; i++)
			{
				sld = characterFromId("Assassins_Vargas_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Assassins_Graveyard_Brides");
			}
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Assassins_Graveyard_Brides", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Assassins_Graveyard_Brides", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Assassins_Graveyard_Brides", "Brides_Tortuga_17");
		break;

		case "Brides_Tortuga_17":
			LAi_group_Delete("Assassins_Graveyard_Brides");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = characterFromId("Henry_Tessie");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Tessie_12";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = characterFromID("Rimalier");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
		break;

		case "Brides_Tortuga_18":
			sld = characterFromId("Henry_Tessie");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", -1);
			sld = characterFromID("Rimalier");
			sld.Dialog.CurrentNode = "Brides_Tortuga_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Brides_Tortuga_19":
			LocatorReloadEnterDisable("Shore58", "reload2_back", true); // закрыть вход через бухту
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			chrDisableReloadToLocation = false; // открыть локацию
			AddQuestRecord("Brides_Tortuga", "3");
			QuestPointerToLoc("Tortuga_Graveyard", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("Tortuga_ExitTown", "reload", "reload4"); // поставить поинт
			QuestPointerToLoc("Tortuga_Town", "reload", "basement1"); // поставить поинт
			sld = CharacterFromID("Rimalier");
			if (sti(pchar.questTemp.AoP.RimalierWasOfficer) == 1)
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.CurrentNode = "Hired";
				sld.Dialog.TempNode = "Hired";
			}
			else
			{
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.Dialog.CurrentNode = "Brides_Tortuga_Officer_No_Officer_3";
			}
			for (i = 1; i <= 12; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Fra_Sold_Brides_" + i, "sold_fra_" + i, "man", "man", CB_Rank(), PIRATE, -1, true));
				CB_Perks(sld);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, "VargasGuards_Group");
				ChangeCharacterAddressGroup(sld, "Tortuga_cave", "quest", "quest_" + i);
			}
			sld = GetCharacter(NPC_GenerateCharacter("Bucaneer_Girl_1", "Girl_5", "woman", "towngirl", 1, FRANCE, -1, false));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "bask2");
			sld = GetCharacter(NPC_GenerateCharacter("Bucaneer_Girl_2", "Girl_7", "woman", "towngirl", 1, FRANCE, -1, false));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "bask1");
			sld = GetCharacter(NPC_GenerateCharacter("Bucaneer_Girl_3", "Girl_8", "woman", "towngirl", 1, FRANCE, -1, false));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "bask3");
			sld = GetCharacter(NPC_GenerateCharacter("Bucaneer_Girl_4", "Girl_9", "woman", "towngirl", 1, FRANCE, -1, false));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "bask4");
			sld = GetCharacter(NPC_GenerateCharacter("Bucaneer_Girl_5", "Girl_11", "woman", "towngirl", 1, FRANCE, -1, false));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "bask5");
			sld = GetCharacter(NPC_GenerateCharacter("Bucaneer_Girl_6", "horse02", "woman", "towngirl", 1, FRANCE, -1, false));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "bask8");
			sld = GetCharacter(NPC_GenerateCharacter("Bertran_Waband", "monk_3", "man", "man_B", CB_Rank(), FRANCE, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "unarmed", "", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Bertran_Waband_lastname");
			sld.lastname = FindPersonalName("Bertran_Waband_name");
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Bertran_Waband_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "bask7");
			sld = GetCharacter(NPC_GenerateCharacter("Luc_Delacroix", "off_fra_3", "man", "man", CB_Rank(), FRANCE, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade10", "blade11", 150);
			CB_Perks(sld);
			sld.name = FindPersonalName("Luc_Delacroix_name");
			sld.lastname = FindPersonalName("Luc_Delacroix_lastname");
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Luc_Delacroix_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_cave", "goto", "bask6");
			locations[FindLocation("Tortuga_cave")].locators_radius.goto.bask9 = 2;
			pchar.quest.war_tortuga_cave.win_condition.l1 = "location";
			pchar.quest.war_tortuga_cave.win_condition.l1.location = "Tortuga_cave";
			pchar.quest.war_tortuga_cave.win_condition = "Brides_Tortuga_20";
		break;

		case "Brides_Tortuga_20":
			chrDisableReloadToLocation = true; // закрыть локацию
			for (i = 1; i <= 5; i++)
			{
				sld = characterFromID("Bucaneer_Girl_" + i);
				LAi_SetImmortal(sld, true);
				LAi_ActorTurnToLocator(sld, "monsters", "monster6");
			}
			sld = characterFromID("Bucaneer_Girl_6");
			LAi_ActorTurnToLocator(sld, "goto", "bask9");
			sld = characterFromID("Luc_Delacroix");
			LAi_ActorTurnToLocator(sld, "goto", "bask9");
			sld = characterFromID("Bertran_Waband");
			LAi_SetImmortal(sld, true);
			LAi_ActorTurnToLocator(sld, "goto", "bask9");
			LAi_group_SetRelation("VargasGuards_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheck("VargasGuards_Group", "Brides_Tortuga_21");
		break;

		case "Brides_Tortuga_21":
			LAi_group_Delete("VargasGuards_Group");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			QuestPointerToLoc("Tortuga_cave", "goto", "bask9"); // поставить поинт
			pchar.quest.Brides_locator_go.win_condition.l1 = "locator";
			pchar.quest.Brides_locator_go.win_condition.l1.location = "Tortuga_cave";
			pchar.quest.Brides_locator_go.win_condition.l1.locator_group = "goto";
			pchar.quest.Brides_locator_go.win_condition.l1.locator = "bask9";
			pchar.quest.Brides_locator_go.win_condition = "Brides_Tortuga_22";
		break;

		case "Brides_Tortuga_22":
			LAi_SetActorType(pchar);
			QuestPointerDelLoc("Tortuga_cave", "goto", "bask9"); // удалить поинт
			ChangeShowIntarface();
			sld = characterFromID("Luc_Delacroix");
			LAi_ActorFollow(sld, characterFromID("blaze"), "Brides_Tortuga_23", -1);
		break;

		case "Brides_Tortuga_23":
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Luc_Delacroix");
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Brides_Tortuga_24":
			StartBattleLandInterface(); // вкл интерфейс
			sld = characterFromID("Luc_Delacroix");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "Luc_Delacroix_group");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Luc_Delacroix_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Luc_Delacroix_group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Luc_Delacroix_group", "Brides_Tortuga_25");
		break;

		case "Brides_Tortuga_25":
			LAi_group_Delete("Luc_Delacroix_group");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = characterFromID("Bertran_Waband");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			for (i = 1; i <= 6; i++)
			{
				sld = characterFromID("Bucaneer_Girl_" + i);
				LAi_ActorFollow(sld, characterFromID("Bertran_Waband"), "", -1);
			}
		break;

		case "Brides_Tortuga_26":
			sld = CharacterFromID("Rimalier");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Brides_Tortuga_3";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Brides_Tortuga_27":
			sld = CharacterFromID("Bertran_Waband");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Bertran_Waband_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Brides_Tortuga_28":
			QuestPointerToLoc("Tortuga_cave", "reload", "reload2_back"); // поставить поинт
			LocatorReloadEnterDisable("Tortuga_cave", "reload1", true); // закрыть выход наверх
			AddQuestRecord("Brides_Tortuga", "4");
			sld = characterFromID("Bucaneer_Girl_6");
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "Brides_Tortuga_28_1", -1);
			for (i = 1; i <= 5; i++)
			{
				sld = characterFromID("Bucaneer_Girl_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromID("Bucaneer_Girl_6"), "", -1);
			}
			sld = characterFromID("Bertran_Waband");
			FantomMakeCoolSailor(sld, SHIP_SCHOONER, "", CANNON_TYPE_CANNON_LBS24, 75, 65, 70);
			SetCharacterShipLocation(sld, "Shore58"); // корабль бухту
			LAi_ActorFollow(sld, characterFromID("Bucaneer_Girl_6"), "", -1);
			sld = CharacterFromID("Rimalier");
			if (sti(pchar.questTemp.AoP.RimalierWasOfficer) == 1)
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.CurrentNode = "Hired";
				sld.Dialog.TempNode = "Hired";
			}
			else
			{
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.Dialog.CurrentNode = "Brides_Tortuga_Officer_No_Officer_3";
			}
		break;

		case "Brides_Tortuga_28_1":
			chrDisableReloadToLocation = false; // открыть локацию
			for (i = 1; i <= 5; i++)
			{
				sld = characterFromID("Bucaneer_Girl_" + i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			sld = characterFromID("Bertran_Waband");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			i = FindLocation("Shore58");
			locations[i].models.always.locators = "Shore04_locators_ship";
			locations[i].locators_radius.reload.reload_ship = 2.2;
			locations[i].models.day.charactersPatch = "shore04_patch_ship";
			locations[i].models.night.charactersPatch = "shore04_patch_ship";
			QuestPointerToLoc("Shore58", "quest", "point"); // поставить поинт
			pchar.quest.Go_To_Ship_swim.win_condition.l1 = "locator";
			pchar.quest.Go_To_Ship_swim.win_condition.l1.location = "Shore58";
			pchar.quest.Go_To_Ship_swim.win_condition.l1.locator_group = "reload";
			pchar.quest.Go_To_Ship_swim.win_condition.l1.locator = "reload_ship";
			pchar.quest.Go_To_Ship_swim.win_condition = "Brides_Tortuga_29";
			i = FindLocation("Deck_Death_1");
			Locations[i].models.always.deckBig = "deckBig_blood";
			Locations[i].models.always.deckBig.tech = "DLightModel";
			i = FindLocation("Deck_Death_2");
			Locations[i].models.always.deck2 = "deck2_blood";
			Locations[i].models.always.deck2.tech = "DLightModel";
		break;

		case "Brides_Tortuga_29":
			DoQuestReloadToLocation("Deck_Death_1", "goto", "goto6", "Brides_Tortuga_30");
			sld = characterFromID("Rimalier");
			ChangeCharacterAddressGroup(sld, "Deck_Death_1", "goto", "goto5");
		break;

		case "Brides_Tortuga_30":
			StopMusic(0);
			PlaySound("Music\Special\LSC\Inside\Prison\Bad_guy_recon.ogg");
			LAi_SetActorType(pchar);
			bDisableCharacterMenu = true; // Ф2 отключить
			TEV.StopTimeScale = true; // запрет ускорения
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			ChangeShowIntarface();
			locCameraFlyToPositionLookToPoint(-4.4, 6.5, 15.6, -0.1, 6.5, 4, 2, 4, -0.8, -1.0, 900);
			pchar.FuncCameraFly = "";
			DoQuestCheckDelay("Brides_Tortuga_31", 5);
		break;

		case "Brides_Tortuga_31":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Brides_Tortuga_32", 3);
		break;

		case "Brides_Tortuga_32":
			locCameraResetState();
			locCameraFlyToPositionLookToPoint(0, 8.5, -7, 2, 8.5, -2.5, -0.9, 6.8, -9.4, -1.0, 900);
			DoQuestCheckDelay("Brides_Tortuga_33", 5);
		break;

		case "Brides_Tortuga_33":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Brides_Tortuga_34", 3);
		break;

		case "Brides_Tortuga_34":
			TeleportCharacterToPosAy(pchar, -3, 5.8, 15.6, 3);
			sld = characterFromID("Rimalier");
			TeleportCharacterToPosAy(sld, -1.9, 5.8, 15.6, 3);
			locCameraResetState();
			locCameraFlyToPositionLookToOffset(-2.9, 6, -3.2, -2.6, 6, 12.4, 0.0, -2.0, 3.0, -1.0, 900);
			DoQuestCheckDelay("Brides_Tortuga_35", 6);
		break;

		case "Brides_Tortuga_35":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Brides_Tortuga_36", 3);
		break;

		case "Brides_Tortuga_36":
			locCameraResetState();
			locCameraFlyToPositionLookToPoint(-2.4, 8, 5.2, -2.4, 8, 9.96, -2.2, 7, 20.2, -1.0, 900);
			pchar.FuncCameraFly = "Brides_Tortuga_2";
			DoQuestCheckDelay("Brides_Tortuga_37", 5);
		break;

		case "Brides_Tortuga_37":
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Rimalier");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Brides_Tortuga_6";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Brides_Tortuga_38":
			DeleteAttribute(&TEV, "StopTimeScale");
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			bDisableCharacterMenu = false; // Ф2 включить
			locCameraResetState();
			QuestPointerToLoc("Deck_Death_1", "reload", "reload1"); // поставить поинт
			StartBattleLandInterface(); // вкл интерфейс
			sld = CharacterFromID("Rimalier");
			if (sti(pchar.questTemp.AoP.RimalierWasOfficer) == 1)
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.CurrentNode = "Hired";
				sld.Dialog.TempNode = "Hired";
			}
			else
			{
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.Dialog.CurrentNode = "Brides_Tortuga_Officer_No_Officer_3";
			}
			LocatorReloadEnterDisable("Tortuga_cave", "reload1", false); // открыть выход наверх
			LocatorReloadEnterDisable("Shore58", "reload2_back", false); // открыть вход через бухту
			pchar.quest.Rimalier_teleport_1.win_condition.l1 = "location";
			pchar.quest.Rimalier_teleport_1.win_condition.l1.location = "Deck_Death_2";
			pchar.quest.Rimalier_teleport_1.win_condition = "Brides_Tortuga_39";
		break;

		case "Brides_Tortuga_39":
			sld = CharacterFromID("Rimalier");
			ChangeCharacterAddressGroup(sld, "Deck_Death_2", "rld", "aloc3");
			sld = GetCharacter(NPC_GenerateCharacter("Esteban_Ruiz", "citiz_49", "man", "man", CB_Rank() * 2, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank() * 2, CB_Fencing() * 2, CB_Pistol() * 2, "blade10", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Esteban_Ruiz_name");
			sld.lastname = FindPersonalName("Esteban_Ruiz_lastname");
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Esteban_Ruiz_1";
			AddLandQuestmark_Main(sld, "Brides_Tortuga");
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Deck_Death_2", "goto", "goto8");
		break;

		case "Brides_Tortuga_40":
			QuestPointerDelLoc("Tortuga_Graveyard", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("Tortuga_ExitTown", "reload", "reload4"); // удалить поинт
			QuestPointerDelLoc("Tortuga_Town", "reload", "basement1"); // удалить поинт
			QuestPointerDelLoc("Tortuga_cave", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("Shore58", "quest", "point"); // удалить поинт
			QuestPointerDelLoc("Deck_Death_1", "reload", "reload1"); // удалить поинт
			LAi_SetPlayerType(pchar);
			DoQuestReloadToLocation("Shore58", "goto", "goto3", "Brides_Tortuga_41");
			sld = CharacterFromID("Rimalier");
			ChangeCharacterAddressGroup(sld, "Shore58", "goto", "goto14");
		break;

		case "Brides_Tortuga_41":
			sld = CharacterFromID("Rimalier");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Brides_Tortuga_8";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Brides_Tortuga_42":
			locations[FindLocation("Beliz_Mine")].locators_radius.goto.bask1 = 3.5;
			AddMapQuestMark_Major("Shore8", "Brides_Tortuga", ""); // метка острова
			AddQuestRecord("Brides_Tortuga", "5");
			pchar.quest.go_mine_beliz.win_condition.l1 = "location";
			pchar.quest.go_mine_beliz.win_condition.l1.location = "Beliz_mine";
			pchar.quest.go_mine_beliz.win_condition = "Brides_Tortuga_43";
			QuestPointerToLoc("Shore8", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Beliz_Jungle_03", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("Beliz_Jungle_05", "reload", "reload1_back"); // поставить поинт
		break;

		case "Brides_Tortuga_43":
			Locations[FindLocation("Beliz_Mine")].AoP.MusicTrack = "Quest\LeBask\Mine_beliz.mp3";
			PlayMusicQuest("Quest\LeBask\Mine_beliz.mp3", 0, true);
			LocatorReloadEnterDisable("Beliz_Mine", "gate_back", true); // закрыть выход с рудника
			LocatorReloadEnterDisable("Beliz_Mine", "reload_cave", true); // закрыть вход в шахту
			sld = CharacterFromID("Rimalier");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_mine", "reload", "gate_back");
			DoQuestCheckDelay("Brides_Tortuga_44", 0.5);
		break;

		case "Brides_Tortuga_44":
			sld = CharacterFromID("Rimalier");
			sld.Dialog.CurrentNode = "Brides_Tortuga_11";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Brides_Tortuga_45":
			QuestPointerToLoc("Beliz_mine", "goto", "bask1"); // поставить поинт
			sld = CharacterFromID("Rimalier");
			if (sti(pchar.questTemp.AoP.RimalierWasOfficer) == 1)
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.CurrentNode = "Hired";
				sld.Dialog.TempNode = "Hired";
			}
			else
			{
				LAi_ActorFollow(sld, pchar, "", -1);
				sld.Dialog.CurrentNode = "Brides_Tortuga_Officer_No_Officer_3";
				sld.FreeFighter = true;
			}
			pchar.quest.go_mine_beliz_1.win_condition.l1 = "locator";
			pchar.quest.go_mine_beliz_1.win_condition.l1.location = "Beliz_mine";
			pchar.quest.go_mine_beliz_1.win_condition.l1.locator_group = "goto";
			pchar.quest.go_mine_beliz_1.win_condition.l1.locator = "bask1";
			pchar.quest.go_mine_beliz_1.win_condition = "Brides_Tortuga_46";
		break;

		case "Brides_Tortuga_46":
			bDisableCharacterMenu = true; // Ф2 отключить
			TEV.StopTimeScale = true; // запрет ускорения
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			LAi_SetActorType(pchar);
			LAi_FadeEx(1.0, 1.0, 1.0, "", "", "");
			DoQuestCheckDelay("Brides_Tortuga_47", 1.5);
		break;

		case "Brides_Tortuga_47":
			EndBattleLandInterface(); // откл интерфейс
			locCameraFromToPos(-2.3, 10, 3.5, false, 26.3, 21, 7.7);
			QuestPointerDelLoc("Beliz_mine", "goto", "bask1"); // удалить поинт
			for (i = 1; i <= 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mine_Vargas_Team_" + i, "killer_" + i + "_mush", "man", "mushketer", CB_Rank() * 2, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank() * 2, CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Beliz_mine", "goto", "goto1");
			}
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mine_Vargas_Team_" + (10 + i), "spa_mush_" + i, "man", "mushketer", CB_Rank() * 2, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank() * 2, CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Beliz_mine", "goto", "goto1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("Officer_Vargas", "huber_26", "man", "man", CB_Rank() * 2, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank() * 2, CB_Fencing() * 2, CB_Pistol() * 2, "blade10", "pistol2", 20);
			CB_Perks(sld);
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Officer_Vargas_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_mine", "patrol", "patrol4");
			DoQuestCheckDelay("Brides_Tortuga_48", 0.5);
		break;

		case "Brides_Tortuga_48":
			sld = CharacterFromID("Mine_Vargas_Team_1");
			TeleportCharacterToPosAy(sld, 20.1, 19.5, 27, 3);
			sld = CharacterFromID("Mine_Vargas_Team_2");
			TeleportCharacterToPosAy(sld, 22, 19.5, 25.1, 3);
			sld = CharacterFromID("Mine_Vargas_Team_3");
			TeleportCharacterToPosAy(sld, 26.1, 19.4, 18.7, 3);
			sld = CharacterFromID("Mine_Vargas_Team_4");
			TeleportCharacterToPosAy(sld, 27.1, 19.5, 16.3, 3);
			sld = CharacterFromID("Mine_Vargas_Team_5");
			TeleportCharacterToPosAy(sld, 27.9, 19.5, 14.5, 3);
			sld = CharacterFromID("Mine_Vargas_Team_6");
			TeleportCharacterToPosAy(sld, 28.7, 19.48, 9.3, 3);
			sld = CharacterFromID("Mine_Vargas_Team_7");
			TeleportCharacterToPosAy(sld, 29.1, 19.4, 6.3, 3);
			sld = CharacterFromID("Mine_Vargas_Team_8");
			TeleportCharacterToPosAy(sld, 29.3, 19.3, 3.4, 3);
			sld = CharacterFromID("Mine_Vargas_Team_9");
			TeleportCharacterToPosAy(sld, 28.4, 19.4, -1.8, 3);
			sld = CharacterFromID("Mine_Vargas_Team_10");
			TeleportCharacterToPosAy(sld, 28.2, 19.4, -4.1, 3);
			sld = CharacterFromID("Mine_Vargas_Team_11");
			TeleportCharacterToPosAy(sld, 27.6, 19.4, -6.8, 3);
			sld = CharacterFromID("Mine_Vargas_Team_12");
			TeleportCharacterToPosAy(sld, 25.7, 19.4, -12.3, 3);
			sld = CharacterFromID("Mine_Vargas_Team_13");
			TeleportCharacterToPosAy(sld, 24.7, 19.4, -14.2, 3);
			DoQuestCheckDelay("Brides_Tortuga_49", 0.5);
		break;

		case "Brides_Tortuga_49":
			sld = CharacterFromID("Officer_Vargas");
			LAi_ActorGoToLocator(sld, "quest", "quest1", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_1");
			LAi_ActorGoToLocator(sld, "goto", "bask2", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_2");
			LAi_ActorGoToLocator(sld, "goto", "bask3", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_3");
			LAi_ActorGoToLocator(sld, "goto", "bask4", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_4");
			LAi_ActorGoToLocator(sld, "goto", "bask5", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_5");
			LAi_ActorGoToLocator(sld, "goto", "bask6", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_6");
			LAi_ActorGoToLocator(sld, "goto", "bask7", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_7");
			LAi_ActorGoToLocator(sld, "goto", "bask8", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_8");
			LAi_ActorGoToLocator(sld, "goto", "bask9", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_9");
			LAi_ActorGoToLocator(sld, "goto", "bask10", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_10");
			LAi_ActorGoToLocator(sld, "goto", "bask11", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_11");
			LAi_ActorGoToLocator(sld, "goto", "bask12", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_12");
			LAi_ActorGoToLocator(sld, "goto", "bask13", "", -1);
			sld = CharacterFromID("Mine_Vargas_Team_13");
			LAi_ActorGoToLocator(sld, "goto", "bask14", "Brides_Tortuga_49_1", -1);
		break;

		case "Brides_Tortuga_49_1":
			locCameraFromToPos(-2.3, 10, 3.5, false, 20.7, 21, -23.5);
			DoQuestCheckDelay("Brides_Tortuga_50", 0.8);
		break;

		case "Brides_Tortuga_50":
			locCameraFlyToPositionLookToPoint(-2.3, 10, 3.5, 15, 21.2, -15, 20.7, 21, -23.5, 1.0, 700);
			pchar.FuncCameraFly = "Brides_Tortuga_3";
			DoQuestCheckDelay("Brides_Tortuga_51", 3.5);
		break;

		case "Brides_Tortuga_51":
			for (i = 1; i <= 13; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bucaneers_Friend_" + i, "elite_fra_mush_" + (rand(2) + 1), "man", "mushketer", CB_Rank(), PIRATE, -1, true));
				sld.Buccaneer = true;
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() * 2, CB_Pistol() * 2, "unarmed", "mushket", 250);
				CB_Perks(sld);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Beliz_Mine", "goto", "goto6");
			}
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Officer_Vargas");
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Brides_Tortuga_52":
			sld = characterFromId("Etien_Marso");
			LAi_ActorTurnToLocator(sld, "quest", "quest1");
			LAi_SetActorType(pchar);
			locCameraResetState();
			locCameraFromToPosEx(15, 21, -15, true, 20.7, 21, -23.5, false);
			sld = characterFromId("Officer_Vargas");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Brides_Tortuga_53", 2.5);
			sld = CharacterFromID("Bucaneers_Friend_1");
			TeleportCharacterToPosAy(sld, 30.1, 19, 31.7, 3);
			sld = CharacterFromID("Bucaneers_Friend_2");
			TeleportCharacterToPosAy(sld, 30.8, 19.1, 29.6, 3);
			sld = CharacterFromID("Bucaneers_Friend_3");
			TeleportCharacterToPosAy(sld, 35.4, 19.3, 23.3, 3);
			sld = CharacterFromID("Bucaneers_Friend_4");
			TeleportCharacterToPosAy(sld, 36.8, 19.3, 20.7, 3);
			sld = CharacterFromID("Bucaneers_Friend_5");
			TeleportCharacterToPosAy(sld, 37.9, 19.3, 18.6, 3);
			sld = CharacterFromID("Bucaneers_Friend_6");
			TeleportCharacterToPosAy(sld, 39.7, 19.33, 12, 3);
			sld = CharacterFromID("Bucaneers_Friend_7");
			TeleportCharacterToPosAy(sld, 40.2, 19.3, 8.4, 3);
			sld = CharacterFromID("Bucaneers_Friend_8");
			TeleportCharacterToPosAy(sld, 41.6, 19.3, 2.8, 3);
			sld = CharacterFromID("Bucaneers_Friend_9");
			TeleportCharacterToPosAy(sld, 42.5, 19.2, -2.6, 3);
			sld = CharacterFromID("Bucaneers_Friend_10");
			TeleportCharacterToPosAy(sld, 41.7, 19.3, -6.2, 3);
			sld = CharacterFromID("Bucaneers_Friend_11");
			TeleportCharacterToPosAy(sld, 40.3, 19.3, -10.7, 3);
			sld = CharacterFromID("Bucaneers_Friend_12");
			TeleportCharacterToPosAy(sld, 41.9, 19.2, -15.7, 3);
			sld = CharacterFromID("Bucaneers_Friend_13");
			TeleportCharacterToPosAy(sld, 42.1, 19.2, -14.2, 3);
		break;

		case "Brides_Tortuga_53":
			locCameraToPos(15, 21, -15, false);
			locCameraTarget(characterFromID("Etien_Marso"));
			DoQuestCheckDelay("Brides_Tortuga_54", 1.5);
			sld = CharacterFromID("Bucaneers_Friend_1");
			LAi_ActorTurnToLocator(sld, "goto", "bask2");
			sld = CharacterFromID("Bucaneers_Friend_2");
			LAi_ActorTurnToLocator(sld, "goto", "bask3");
			sld = CharacterFromID("Bucaneers_Friend_3");
			LAi_ActorTurnToLocator(sld, "goto", "bask4");
			sld = CharacterFromID("Bucaneers_Friend_4");
			LAi_ActorTurnToLocator(sld, "goto", "bask5");
			sld = CharacterFromID("Bucaneers_Friend_5");
			LAi_ActorTurnToLocator(sld, "goto", "bask6");
			sld = CharacterFromID("Bucaneers_Friend_6");
			LAi_ActorTurnToLocator(sld, "goto", "bask7");
			sld = CharacterFromID("Bucaneers_Friend_7");
			LAi_ActorTurnToLocator(sld, "goto", "bask8");
			sld = CharacterFromID("Bucaneers_Friend_8");
			LAi_ActorTurnToLocator(sld, "goto", "bask9");
			sld = CharacterFromID("Bucaneers_Friend_9");
			LAi_ActorTurnToLocator(sld, "goto", "bask10");
			sld = CharacterFromID("Bucaneers_Friend_10");
			LAi_ActorTurnToLocator(sld, "goto", "bask11");
			sld = CharacterFromID("Bucaneers_Friend_11");
			LAi_ActorTurnToLocator(sld, "goto", "bask13");
			sld = CharacterFromID("Bucaneers_Friend_12");
			LAi_ActorTurnToLocator(sld, "goto", "bask13");
			sld = CharacterFromID("Bucaneers_Friend_13");
			LAi_ActorTurnToLocator(sld, "goto", "bask13");
		break;

		case "Brides_Tortuga_54":
			locCameraFromToPos(15, 21, -15, false, 29.6, 21, 18.1);
			for (i = 1; i <= 13; i++)
			{
				sld = CharacterFromID("Bucaneers_Friend_" + i);
				LAi_ActorAnimation(sld, "Shot", "", 4);
			}
			DoQuestCheckDelay("Brides_Tortuga_55", 1.0);
			for (i = 1; i <= 13; i++)
			{
				sld = CharacterFromID("Mine_Vargas_Team_" + i);
				LAi_ActorRunToLocator(sld, "goto", "goto25", "", -1);
			}
		break;

		case "Brides_Tortuga_55":
			for (i = 1; i <= 13; i++)
			{
				sld = CharacterFromID("Mine_Vargas_Team_" + i);
				LAi_KillCharacter(sld);
			}
			DoQuestCheckDelay("Brides_Tortuga_56", 2.5);
		break;

		case "Brides_Tortuga_56":
			locCameraToPos(15, 21, -15, false);
			sld = characterFromId("Etien_Marso");
			locCameraTarget(sld);
			LAi_ActorRunToLocator(sld, "goto", "goto_marso", "Brides_Tortuga_57", -1);
		break;

		case "Brides_Tortuga_57":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Brides_Tortuga_1";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			for (i = 1; i <= 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mine_Vargas_Team2_" + i, "killer_" + i, "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade10", "pistol2", 50);
				CB_Perks(sld);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Beliz_mine", "goto", "goto11");
			}
			for (i = 1; i <= 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mine_Vargas_Team2_" + (10 + i), "sold_spa_" + i, "man", "man", CB_Rank() * 2, SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade14", "pistol2", 100);
				CB_Perks(sld);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Beliz_mine", "goto", "goto6");
			}
		break;

		case "Brides_Tortuga_58":
			DeleteAttribute(&TEV, "StopTimeScale");
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			bDisableCharacterMenu = false; // Ф2 включить
			StartBattleLandInterface(); // вкл интерфейс
			locCameraResetState();
			for (i = 1; i <= 20; i++)
			{
				sld = CharacterFromID("Mine_Vargas_Team2_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "War_Mine_Brides");
			}
			for (i = 1; i <= 13; i++)
			{
				sld = CharacterFromID("Bucaneers_Friend_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			sld = characterFromId("Etien_Marso");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("Rimalier");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("War_Mine_Brides", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("War_Mine_Brides", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("War_Mine_Brides", "Brides_Tortuga_59");
		break;

		case "Brides_Tortuga_59":
			LAi_group_Delete("War_Mine_Brides");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Brides_Tortuga_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Brides_Tortuga_60":
			LocatorReloadEnterDisable("Beliz_Mine", "reload_cave", false); // открыть вход в шахту
			sld = CharacterFromID("Rimalier");
			if (sti(pchar.questTemp.AoP.RimalierWasOfficer) == 1)
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.CurrentNode = "Hired";
				sld.Dialog.TempNode = "Hired";
			}
			else
			{
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "gate_back", "none", "", "", "", -1);
				sld.Dialog.CurrentNode = "Brides_Tortuga_Officer_No_Officer_3";
				DeleteAttribute(sld, "FreeFighter");
			}
			QuestPointerToLoc("Beliz_mine", "reload", "reload_cave"); // поставить поинт
			AddQuestRecord("Brides_Tortuga", "6");
			sld = characterFromId("Etien_Marso");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			for (i = 1; i <= 13; i++)
			{
				int Live_Team_3 = GetCharacterIndex("Bucaneers_Friend_" + i);
				if (Live_Team_3 != -1)
				{
					sld = &characters[Live_Team_3];
					if (!LAi_IsDead(sld))
					{
						LAi_SetCitizenType(sld);
						LAi_CharacterDisableDialog(sld);
					}
				}
			}
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			sld = GetCharacter(NPC_GenerateCharacter("Mary_Belfler", "Mary_Belfler", "woman", "Beatrice", CB_Rank(), FRANCE, -1, false));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "unarmed", "", 20);
			sld.name = FindPersonalName("Mary_Belfler_name");
			sld.lastname = FindPersonalName("Mary_Belfler_lastname");
			sld.dialog.filename = "Quest\Lebasque\Mary_dialog.c";
			LAi_CharacterDisableDialog(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_LowerShaft", "goto", "goto_Mary");
			sld = characterFromId("Diego_de_Vargas");
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() * 2, CB_Pistol() * 2, "BladeBone", "pistol5", 10);
			Lai_SetHP(sld, 600.0, 600.0);
			AddLandQuestmark_Main(sld, "Brides_Tortuga");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_LowerShaft", "goto", "goto_Vargas");
			locations[FindLocation("Beliz_LowerShaft")].locators_radius.quest.quest_GG = 4;
			pchar.quest.go_cave_vargas.win_condition.l1 = "location";
			pchar.quest.go_cave_vargas.win_condition.l1.location = "Beliz_LowerShaft";
			pchar.quest.go_cave_vargas.win_condition = "Brides_Tortuga_60_1";
			pchar.GenQuestBox.Beliz_LowerShaft = true;
			pchar.GenQuestBox.Beliz_LowerShaft.box2.money = 15000;
			pchar.GenQuestBox.Beliz_LowerShaft.box2.items.potion1 = 6;
			pchar.GenQuestBox.Beliz_LowerShaft.box2.items.potion2 = 5;
			pchar.GenQuestBox.Beliz_LowerShaft.box2.items.potion3 = 10;
			pchar.GenQuestBox.Beliz_LowerShaft.box2.items.potionsangari = 1;
			pchar.GenQuestBox.Beliz_LowerShaft.box1.items.jewelry5 = 100;
			pchar.GenQuestBox.Beliz_LowerShaft.box1.items.jewelry17 = 150;
			pchar.GenQuestBox.Beliz_LowerShaft.box1.items.indian22 = 1;
		break;

		case "Brides_Tortuga_60_1":
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = characterFromId("Diego_de_Vargas");
			LAi_ActorAnimation(sld, "Ground_sitting", "", -1);
			pchar.quest.locator_stay_Vargas.win_condition.l1 = "locator";
			pchar.quest.locator_stay_Vargas.win_condition.l1.location = "Beliz_LowerShaft";
			pchar.quest.locator_stay_Vargas.win_condition.l1.locator_group = "quest";
			pchar.quest.locator_stay_Vargas.win_condition.l1.locator = "quest_GG";
			pchar.quest.locator_stay_Vargas.win_condition = "Brides_Tortuga_60_2";
		break;

		case "Brides_Tortuga_60_2":
			sld = characterFromId("Diego_de_Vargas");
			sld.dialog.filename = "Quest\Lebasque\Vargas_dialog.c";
			sld.Dialog.CurrentNode = "Vargas_1";
			LAi_ActorAnimation(sld, "Ground_StandUp", "", -1);
			DoQuestCheckDelay("Brides_Tortuga_60_3", 4);
		break;

		case "Brides_Tortuga_60_3":
			sld = characterFromId("Diego_de_Vargas");
			LAi_SetStayType(sld);
		break;

		case "Brides_Tortuga_61":
			LAi_group_Delete("Don_Vargas_Group");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = characterFromId("Diego_de_Vargas");
			sld.Dialog.CurrentNode = "Vargas_13";
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Brides_Tortuga_62":
			ChangeShowIntarface();
			pchar.GenQuest.CamShuttle = 4;
			LAi_UpdateAlcoholCamShuttleCamera();
			LAi_SetActorType(pchar);
			LAi_FadeEx(6.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Brides_Tortuga_63", 1.5);
		break;

		case "Brides_Tortuga_63":
			SetCharacterTask_Dead(pchar);
			DoQuestCheckDelay("Brides_Tortuga_64", 6);
		break;

		case "Brides_Tortuga_64":
			DeleteAttribute(pchar, "GenQuest.CamShuttle");
			LAi_UpdateAlcoholCamShuttleCamera();
			DoQuestReloadToLocation("Beliz_LowerShaft", "goto", "goto3", "Brides_Tortuga_65");
			sld = characterFromId("Diego_de_Vargas");
			ChangeCharacterAddressGroup(sld, "Beliz_Mine", "goto", "goto15");
			sld = characterFromId("Mary_Belfler");
			LAi_SetLayType(sld);
		break;

		case "Brides_Tortuga_65":
			ChangeShowIntarface();
			sld = characterFromId("Mary_Belfler");
			LAi_CharacterDisableDialog(sld);
			TeleportCharacterToPosAy(sld, 4.53, 2.51, -51.43, 3);
			LAi_ActorAnimation(pchar, "Ground_sitting", "", -1);
			DoQuestCheckDelay("Brides_Tortuga_66", 2);
		break;

		case "Brides_Tortuga_66":
			LAi_ActorAnimation(pchar, "Ground_StandUp", "", -1);
			DoQuestCheckDelay("Brides_Tortuga_67", 4);
		break;

		case "Brides_Tortuga_67":
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, characterFromID("Mary_Belfler"), "Brides_Tortuga_68", -1);
		break;

		case "Brides_Tortuga_68":
			pchar.Dialog.CurrentNode = "Brides_Tortuga_1";
			SelfDialog(pchar);
		break;

		case "Brides_Tortuga_69":
			AddQuestRecord("Brides_Tortuga", "7");
			LAi_LocationDisableOfficersGen("Beliz_Mine", true);
			sld = characterFromId("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			for (i = 1; i <= 13; i++)
			{
				int Live_Team_4 = GetCharacterIndex("Bucaneers_Friend_" + i);
				if (Live_Team_4 != -1)
				{
					sld = &characters[Live_Team_4];
					if (!LAi_IsDead(sld))
					{
						sld.lifeday = 0;
						ChangeCharacterAddressGroup(sld, "none", "", "");
					}
				}
			}
			StartBattleLandInterface(); // вкл интерфейс
			chrDisableReloadToLocation = false; // открыть локацию
			LAi_SetPlayerType(pchar);
			QuestPointerToLoc("Beliz_LowerShaft", "reload", "reload1_back"); // поставить поинт
			QuestPointerDelLoc("Beliz_Mine", "reload", "reload_cave"); // удалить поинт
			i = FindLocation("Beliz_Mine");
			if (i != -1)
			{
				Locations[i].QuestlockWeather = "Storm04_add";
				Locations[i].environment.weather.rain = true;
			}
			pchar.quest.run_vargas_run.win_condition.l1 = "location";
			pchar.quest.run_vargas_run.win_condition.l1.location = "Beliz_Mine";
			pchar.quest.run_vargas_run.win_condition = "Brides_Tortuga_70";
		break;

		case "Brides_Tortuga_70":
			LocatorReloadEnterDisable("Beliz_Mine", "reload_cave", true); // закрыть вход в шахту
			DoQuestCheckDelay("Off_Interface", 0.2);
			LAi_SetActorType(pchar);
			locCameraFlyToPositionLookToPoint(8.7, 21, -22.2, -12.62, 35.12, 16.82, 9.52, 43.62, 47.83, -1.0, 1200);
			sld = characterFromId("Diego_de_Vargas");
			LAi_ActorRunToLocator(sld, "goto", "goto_Vargas", "Brides_Tortuga_71", -1);
		break;

		case "Brides_Tortuga_71":
			sld = characterFromId("Diego_de_Vargas");
			LAi_ActorTurnToLocator(sld, "quest", "quest1");
			LAi_FadeEx(1.0, 2.0, 1.0, "", "", "");
			DoQuestCheckDelay("Brides_Tortuga_72", 2);
		break;

		case "Brides_Tortuga_72":
			locCameraResetState();
			locCameraToPos(13.9, 50, 68, false);
			locCameraTarget(characterFromID("Diego_de_Vargas"));
			DoQuestCheckDelay("Brides_Tortuga_73", 3);
		break;

		case "Brides_Tortuga_73":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Brides_Tortuga_74", 3);
		break;

		case "Brides_Tortuga_74":
			sld = characterFromId("Diego_de_Vargas");
			sld.Dialog.CurrentNode = "Vargas_16";
			LAi_SetStayType(sld);
			AddLandQuestmark_Main(sld, "Brides_Tortuga");
			StartBattleLandInterface(); // вкл интерфейс
			locCameraResetState();
			locCameraTarget(pchar);
			LAi_SetPlayerType(pchar);
		break;

		case "Brides_Tortuga_75":
			Delay_DeleteGroup("Don_Vargas_Group");
			LAi_SetActorType(pchar);
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			DoQuestCheckDelay("Brides_Tortuga_76", 1.5);
		break;

		case "Brides_Tortuga_76":
			pchar.Dialog.CurrentNode = "Brides_Tortuga_2";
			SelfDialog(pchar);
		break;

		case "Brides_Tortuga_77":
			pchar.questTemp.VargasWound = true;
			if (stf(pchar.Health.HP) > 11.0) AddCharacterHealth(pchar, 11.0 - stf(pchar.Health.HP));
			ChangeShowIntarface();
			pchar.GenQuest.CamShuttle = 4;
			LAi_UpdateAlcoholCamShuttleCamera();
			LAi_SetActorType(pchar);
			LAi_FadeEx(6.0, 2.0, 0.0, "", "", "");
			DoQuestCheckDelay("Brides_Tortuga_78", 1.5);
			DoQuestCheckDelay("Brides_Tortuga_79", 8.2);
		break;

		case "Brides_Tortuga_78":
			SetCharacterTask_Dead(pchar);
		break;

		case "Brides_Tortuga_79":
			DeleteAttribute(pchar, "GenQuest.CamShuttle");
			LAi_UpdateAlcoholCamShuttleCamera();
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_278"), "Brides_Tortuga_79_Sea", 0.1, 2.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 3, 0, 0); // мотаем время
			SetCurrentTime(19, 54);
			setWDMPointXZ("Shore16"); // корабль в бухту
		break;

		case "Brides_Tortuga_79_Sea":
			bQuestDisableMapEnter = true; // закрыть карту
			Island_SetReloadEnableGlobal("Caiman", false); // на остров нельзя
			QuestToSeaLogin_PrepareLoc("Caiman", "quest", "quest_ship_5", true);
			QuestToSeaLogin_Launch();
			DoQuestCheckDelay("Brides_Tortuga_79_Sea_1", 3);
		break;

		case "Brides_Tortuga_79_Sea_1":
			Set_My_Cabin();
			Sea_CabinStartNow();
			pchar.quest.Brides_Caiman_Cabin.win_condition.l1 = "location";
			pchar.quest.Brides_Caiman_Cabin.win_condition.l1.location = Get_My_Cabin();
			pchar.quest.Brides_Caiman_Cabin.win_condition = "Brides_Tortuga_80";
		break;

		case "Brides_Tortuga_80":
			LAi_ActorAnimation(pchar, "Ground_sitting", "", -1);
			DoQuestCheckDelay("Brides_Tortuga_81", 1.5);
		break;

		case "Brides_Tortuga_81":
			LAi_ActorAnimation(pchar, "Ground_StandUp", "", -1);
			DoQuestCheckDelay("Brides_Tortuga_82", 4);
		break;

		case "Brides_Tortuga_82":
			chrDisableReloadToLocation = true; // закрыть локацию
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Rimalier");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			DoQuestCheckDelay("Brides_Tortuga_83", 1);
		break;

		case "Brides_Tortuga_83":
			sld = CharacterFromID("Rimalier");
			sld.Dialog.CurrentNode = "Brides_Tortuga_15";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Brides_Tortuga_84":
			sld = characterFromID("Rimalier");
			if (IsOfficer(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.CurrentNode = "Hired";
				sld.Dialog.TempNode = "Hired";
			}
			i = FindLocation("Shore58");
			locations[i].models.always.locators = "Shore04_locators";
			locations[i].models.day.charactersPatch = "shore04_patch";
			locations[i].models.night.charactersPatch = "shore04_patch";
			RemoveMapQuestMark("Shore8", "Brides_Tortuga"); // убрать метку острова
			AddMapQuestMark_Major("Tortuga", "Brides_Tortuga", ""); // метка острова
			bQuestDisableMapEnter = false; // открыть карту
			Island_SetReloadEnableGlobal("Caiman", true); // на остров можно
			chrDisableReloadToLocation = false; // открыть локацию
			AddQuestRecord("Brides_Tortuga", "8");
			sld = characterFromId("Mishel_le_Bask");
			AddLandQuestmark_Main(sld, "Brides_Tortuga");
			sld.Dialog.CurrentNode = "Brides_Tortuga_10";
		break;

		case "Brides_Tortuga_BertranHeal":
			chrDisableReloadToLocation = true;
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_279"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("Bucaneer_Outpost_house_2", "goto", "goto1", "Brides_Tortuga_BertranHeal_1");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 3); // мотаем время
		break;

		case "Brides_Tortuga_BertranHeal_1":
			DeleteAttribute(pchar, "questTemp.VargasWound");
			AddCharacterHealth(pchar, stf(pchar.Health.maxHP) - stf(pchar.Health.HP));
			LAi_SetCurHPMax(pchar);
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Bertran_Waband");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost_house_2", "reload", "reload1");
			LAi_ActorFollow(sld, pchar, "Brides_Tortuga_BertranHeal_2", -1);
		break;

		case "Brides_Tortuga_BertranHeal_2":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Bertran_Waband");
			sld.Dialog.CurrentNode = "Bertran_Waband_AfterHeal";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Brides_Tortuga_BertranHeal_3":
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("Bertran_Waband");
			sld.Dialog.CurrentNode = "Bertran_Waband_Main";
			sld.Dialog.TempNode = "Bertran_Waband_Main";
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "Bucaneer_Outpost", "goto", "goto16", "Brides_Tortuga_BertranHeal_4", -1);
		break;

		case "Brides_Tortuga_BertranHeal_4":
			sld = CharacterFromID("Bertran_Waband");
			LAi_SetCitizenType(sld);
			sld.Dialog.CurrentNode = "Bertran_Waband_Main";
			sld.Dialog.TempNode = "Bertran_Waband_Main";
		break;

		case "Brides_Tortuga_85":
			AddQuestRecord("Brides_Tortuga", "9");
			ChangeBuccaneerRelation(10.0); // +10 к отношениям с буканьерами
			CloseQuestHeader("Brides_Tortuga");
			LAi_SetPlayerType(pchar);
			SetTimerCondition("Royal_jackpot_1", 0, 0, 1, false);
			SetBuccaneerService(4);
			Achievment_Set(ACH_Wind_rose);
		break;

		case "Brides_Tortuga_ReportTime":
			AddTimeToCurrent(2, 0);

			SetLaunchFrameFormParam(StringFromKey("InfoMessages_280"), "Brides_Tortuga_ReportContinue", 0.1, 3.0);
			LaunchFrameForm();
		break;

		case "Brides_Tortuga_ReportContinue":
			sld = CharacterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Brides_Tortuga_11";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_1":
		StopMusic(0);
		TEV.YoHoMusic = true;
			LocatorReloadEnterDisable("Bucaneer_outpost", "reload6_back", true); // закрыть вход в дом к ле баску
			pchar.questTemp.AoP.Holiday = true;
			pchar.questTemp.AoP.BucaneerGirlsSettled = true;
			pchar.quest.Bucaneers_holiday.win_condition.l1 = "location";
			pchar.quest.Bucaneers_holiday.win_condition.l1.location = "Bucaneer_Outpost";
			pchar.quest.Bucaneers_holiday.win_condition = "Royal_jackpot_2";
			i = FindLocation("Bucaneer_outpost");
			Locations[i].models.always.smugglerLairExit = "smugglerLairExit_happy";
			Locations[i].models.always.smugglerLairExit.tech = "DLightModel";
			Locations[i].models.always.smugglerLairExit.lights = 1;
			Locations[i].models.always.locators = "smugglerLairExit_locators_happy";
			locations[i].models.day.charactersPatch = "smugglerLairExit_patch_happy";
			locations[i].models.night.charactersPatch = "smugglerLairExit_patch_happy";
			Locations[i].models.always.grassPatch = "smugglerLairExit_grass_happy";
		break;

		case "Royal_jackpot_2":
		sld = GetCharacter(NPC_GenerateCharacter("Royal_Musicant_1", "flutist_4", "man", "musician", 1, HOLLAND, -1, false));
		ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "goto", "music_2");
		LAi_SetFlutistStayType(sld);
		sld = GetCharacter(NPC_GenerateCharacter("Royal_Musicant_2", "violinist_11", "man", "musician", 1, HOLLAND, -1, false));
		ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "goto", "music_3");
		LAi_SetViolinistStayType(sld);
		sld = GetCharacter(NPC_GenerateCharacter("Royal_Musicant_3", "woman_flutist_8", "woman", "woman_musician", 1, FRANCE, -1, false));
		LAi_SetFlutistStayType(sld);
		ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "music_1");
		for (i = 1; i <= 4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Massovka_royal_" + (24 + i), "drinker_"+i, "man", "man", -1, PIRATE, -1, false));
				LAi_SetDrinkerStayType(sld);
				LAi_CharacterDisableDialog(sld);
				MakeUnpushable(sld, true);
				ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "drinkerstay", "drinkerstay" + i);
			}
			sld = GetCharacter(NPC_GenerateCharacter("Massovka_royal_29", "drinker_5", "man", "man", 1, PIRATE, -1, false));
			LAi_SetDrinkerSitType(sld);
			LAi_CharacterDisableDialog(sld);
			MakeUnpushable(sld, true);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "drinkersit", "drinkersit1");
			AddQuestRecord("Royal_jackpot", "0.0");
			sld = characterFromID("Rimalier");
			AddLandQuestmark_Main(sld, "Royal_jackpot");
			if (IsOfficer(sld))
			{
				pchar.questTemp.AoP.RimalierWasOfficer = true;
				RemoveOfficersIndex(pchar, sti(sld.index));
				RemovePassenger(pchar, sld);
			}
			FreeSitLocator("Bucaneer_Outpost", "sit5");
			FreeSitLocator("Bucaneer_Outpost", "sit22");
			sld.Dialog.CurrentNode = "Holiday_Start";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "sit", "sit5");
			sld = characterFromID("Young_Boy_Bask");
			AddLandQuestmark_Main(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Holiday_Jako_Start";
			LAi_SetCitizenType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto15");
			sld = characterFromID("Etien_Marso");
			LAi_CharacterEnableDialog(sld);
			AddLandQuestmark_Main(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Holiday_Marso_Start";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto10");
			sld = characterFromId("Mary_Belfler");
			GiveItem2Character(sld, "blade3");
			EquipCharacterByItem(sld, "blade3");
			GiveItem2Character(sld, "pistol2");
			EquipCharacterByItem(sld, "pistol2");
			LAi_CharacterEnableDialog(sld);
			AddLandQuestmark_Main(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Holiday_Mary_Start";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "sit", "sit22");
		break;

		case "Royal_jackpot_3":
			LAi_FadeEx(1.0, 1.0, 2.0, "", "", "");
			DoQuestCheckDelay("Royal_jackpot_4", 1.5);
		break;

		case "Royal_jackpot_4":
			ChangeShowIntarface();
			QuestMovieLockPlayer(); // окаемки вкл
			sld = characterFromId("Mishel_le_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "reload", "reload6_back");
			locCameraToPos(7.1, 2.5, -6.8, false);
			locCameraTarget(characterFromID("Mishel_le_Bask"));
			DoQuestCheckDelay("Royal_jackpot_5", 0.5);
		break;

		case "Royal_jackpot_5":
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorGoToLocator(sld, "goto", "goto9", "", -1);
			DoQuestCheckDelay("Royal_jackpot_6", 3.5);
		break;

		case "Royal_jackpot_6":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Royal_jackpot_7", 3.5);
			for (i = 1; i <= 2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Massovka_royal_" + i, "mush_ctz_" + i, "man", "mushketer", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "reload", "reload2_back");
			}
			for (i = 1; i <= 7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Massovka_royal_" + (2 + i), "mush_ctz_" + i, "man", "mushketer", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto23");
			}
			for (i = 1; i <= 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Massovka_royal_" + (9 + i), "pirate_" + i, "man", "man", CB_Rank(), PIRATE, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto6");
			}
			sld = GetCharacter(NPC_GenerateCharacter("Massovka_royal_20", "Girl_5", "woman", "towngirl", 1, FRANCE, -1, false));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto8");
			sld = GetCharacter(NPC_GenerateCharacter("Massovka_royal_21", "Girl_7", "woman", "towngirl", 1, FRANCE, -1, false));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto8");
			sld = GetCharacter(NPC_GenerateCharacter("Massovka_royal_22", "Girl_8", "woman", "towngirl", 1, FRANCE, -1, false));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto6");
			sld = GetCharacter(NPC_GenerateCharacter("Massovka_royal_23", "Girl_9", "woman", "towngirl", 1, FRANCE, -1, false));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto6");
			sld = GetCharacter(NPC_GenerateCharacter("Massovka_royal_24", "Girl_11", "woman", "towngirl", 1, FRANCE, -1, false));
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto15");
			LAi_SetActorType(pchar);
			ChangeCharacterAddressGroup(pchar, "Bucaneer_Outpost", "goto", "goto15");
		break;

		case "Royal_jackpot_7":
		sld = CharacterFromID("Royal_Musicant_1");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = CharacterFromID("Royal_Musicant_2");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		sld = CharacterFromID("Royal_Musicant_3");
		ChangeCharacterAddressGroup(sld, "none", "", "");
			for (i = 1; i < MAX_CHARACTERS; i++)
			{
				if (CheckAttribute(&characters[i], "CityType") && characters[i].location == "Bucaneer_outpost")
				{
					ChangeCharacterAddressGroup(&characters[i], "none", "", "");
					characters[i].LifeDay = 0;
				}
			}
			for (n = 1; n <= 6; n++)
			{
				int Bucan_Girls = GetCharacterIndex("Bucaneer_Girl_" + n);
				if (Bucan_Girls >= 0)
				{
					if (characters[Bucan_Girls].location == "Bucaneer_outpost")
					{
						ChangeCharacterAddressGroup(&characters[Bucan_Girls], "none", "", "");
					}
				}
			}
			pchar.questTemp.Lebasque.OutpostEmpty = "true";
			locCameraFlyToPositionLookToPoint(29.16, 7.10, -12.28, 2.46, 4.10, 2.71, -6.57, 1.15, 4.91, -1.0, 3500);
			for (i = 1; i <= 9; i++)
			{
				sld = characterFromId("Massovka_royal_" + i);
				LAi_ActorGoToLocator(sld, "quest", "quest_mass_1", "", -1);
			}
			for (i = 1; i <= 10; i++)
			{
				sld = characterFromId("Massovka_royal_" + (9 + i));
				LAi_ActorGoToLocator(sld, "quest", "quest_mass_2", "", -1);
			}
			for (i = 1; i <= 5; i++)
			{
				sld = characterFromId("Massovka_royal_" + (19 + i));
				LAi_ActorGoToLocator(sld, "goto", "goto9", "", -1);
			}
			DoQuestCheckDelay("Royal_jackpot_8", 7.5);
		break;

		case "Royal_jackpot_8":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Royal_jackpot_9", 3);
		break;

		case "Royal_jackpot_9":
			locCameraResetState();
			locCameraToPos(-4.98, 3.5, -7.32, true);
			locCameraTarget(characterFromID("Mishel_le_Bask"));
			sld = characterFromId("Mishel_le_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "quest", "quest_bask");
			LAi_ActorTurnToLocator(sld, "goto", "goto21");
			for (i = 1; i <= 9; i++)
			{
				sld = characterFromId("Massovka_royal_" + i);
				ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "quest", "quest_mass_1");
				LAi_ActorTurnToLocator(sld, "quest", "quest_bask");
			}
			for (i = 1; i <= 10; i++)
			{
				sld = characterFromId("Massovka_royal_" + (9 + i));
				ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "quest", "quest_mass_2");
				LAi_ActorTurnToLocator(sld, "quest", "quest_bask");
			}
			for (i = 1; i <= 5; i++)
			{
				sld = characterFromId("Massovka_royal_" + (19 + i));
				ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto9");
				LAi_ActorTurnToLocator(sld, "quest", "quest_bask");
			}
			sld = characterFromId("Rimalier");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "quest", "quest_rimalier");
			LAi_ActorTurnToLocator(sld, "quest", "quest_bask");
			sld = characterFromId("Etien_Marso");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "quest", "quest_marso");
			LAi_ActorTurnToLocator(sld, "goto", "goto21");
			sld = characterFromId("Young_Boy_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "quest", "quest_jaco");
			LAi_ActorTurnToLocator(sld, "quest", "quest_bask");
			sld = characterFromId("Mary_Belfler");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "quest", "quest_mary");
			LAi_ActorTurnToLocator(sld, "quest", "quest_bask");
			ChangeCharacterAddressGroup(pchar, "Bucaneer_Outpost", "quest", "quest_hero");
			LAi_ActorTurnToLocator(pchar, "quest", "quest_bask");
			DoQuestCheckDelay("Royal_jackpot_10", 4);
		break;

		case "Royal_jackpot_10":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Royal_jackpot_1";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_11":
			LAi_FadeEx(1.0, 2.0, 1.0, "", "", "");
			DoQuestCheckDelay("Royal_jackpot_12", 2.5);
			sld = GetCharacter(NPC_GenerateCharacter("Fransua_Olone", "Fransua_Olone", "man", "man", CB_Rank() + 3, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank() + 3, CB_Fencing() + 10, CB_Pistol() + 10, "blade32", "pistol5", 80);
			sld.name = FindPersonalName("Fransua_Olone_name");
			sld.lastname = FindPersonalName("Fransua_Olone_lastname");
			sld.greeting = "pirat_common";
			sld.dialog.filename = "Quest\LeBasque\Olone_dialog.c";
			sld.Dialog.CurrentNode = "Royal_jackpot_1";
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "reload", "reload2_back");
			for (i = 1; i <= 6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Royal_Olone_Man_" + i, "pirate_"+i, "man", "man", CB_Rank(), PIRATE, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade10", "pistol2", 40);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "reload", "reload2_back");
			}
		break;

		case "Royal_jackpot_12":
			StopMusic(0);
			TEV.Music.QuestMusic = "Music\Colony\Inside\Governor\Pirate\Governor.ogg";
			PlayMusic(TEV.Music.QuestMusic, 1000);
			locCameraToPos(-3.4, 2.5, -7.3, false);
			locCameraTarget(characterFromID("Fransua_Olone"));
			LAi_SetActorType(pchar);
			int randLoc, temp, locators[39], count = 0;
			string locName;
			for (i = 1; i <= 48; i++)
			{
				if (i >= 31 && i <= 36) continue;
				if (i >= 40 && i <= 42) continue;

				locators[count] = i;
				count++;
			}
			for (i = 38; i >= 1; i--)
			{
				randLoc = rand(i);
				temp = locators[i];
				locators[i] = locators[randLoc];
				locators[randLoc] = temp;
			}
			for (i = 1; i <= 19; i++)
			{
				sld = characterFromId("Massovka_royal_" + i);
				LAi_SetSitType(sld);
				locName = "sit" + locators[i - 1];
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "sit", locName);
			}
			for (i = 1; i <= 5; i++)
			{
				sld = characterFromId("Massovka_royal_" + (19 + i));
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			sld = characterFromId("Mishel_le_Bask");
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto9");
			QuestMovieLockPlayer();
			sld = CharacterFromID("Fransua_Olone");
			TeleportCharacterToPosAy(sld, -20.13, -0.50, -3.22, 3);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest_mass_1", "Royal_jackpot_13", -1);
			for (i = 1; i <= 6; i++)
			{
				sld = characterFromId("Royal_Olone_Man_" + i);
				TeleportCharacterToPosAy(sld, -24.36, -0.56, -1.08, 3);
				LAi_ActorFollow(sld, characterFromID("Fransua_Olone"), "", -1);
			}
			sld = characterFromId("Rimalier");
			LAi_ActorTurnToLocator(sld, "goto", "goto12");
			sld = characterFromId("Etien_Marso");
			LAi_ActorTurnToLocator(sld, "goto", "goto12");
			sld = characterFromId("Young_Boy_Bask");
			LAi_ActorTurnToLocator(sld, "goto", "goto12");
			sld = characterFromId("Mary_Belfler");
			LAi_ActorTurnToLocator(sld, "goto", "goto12");
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorTurnToLocator(sld, "goto", "goto12");
			LAi_ActorTurnToLocator(pchar, "goto", "goto12");
		break;

		case "Royal_jackpot_13":
			QuestMovieUnLockPlayer();
			sld = characterFromId("Fransua_Olone");
			LAi_ActorTurnToCharacter(sld, characterFromID("Mishel_le_Bask"));
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorTurnToCharacter(sld, characterFromID("Fransua_Olone"));

			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_1"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_1"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_2"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_2"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_3"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_3"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_4"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_4"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_5"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_5"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_6"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_6"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_7"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_7"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_8"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_8"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_9"));
			AoP_NPCDialogLaunch("Fransua_Olone", "Mishel_le_Bask", "Royal_jackpot_20");
		break;

		case "Royal_jackpot_15":
			LAi_SetActorType(pchar);
			locCameraFromToPos(-1.24, 3, 1.38, false, -11, 0, 0.68);
			DoQuestCheckDelay("Royal_jackpot_16", 0.2);
		break;

		case "Royal_jackpot_16":
			sld = characterFromId("Etien_Marso");
			LAi_ActorTurnToCharacter(sld, characterFromID("Fransua_Olone"));
			sld = characterFromId("Fransua_Olone");
			LAi_ActorTurnToCharacter(sld, characterFromID("Etien_Marso"));
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_6"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_10"));
			AoP_NPCDialogLaunch("Fransua_Olone", "Etien_Marso", "Royal_jackpot_17");
		break;

		case "Royal_jackpot_17":
			QuestMovieLockPlayer();
			locCameraToPos(-12.40, 2, 4.21, false);
			locCameraTarget(characterFromID("Mary_Belfler"));
			sld = characterFromId("Mary_Belfler");
			LAi_ActorFollow(sld, characterFromID("Fransua_Olone"), "Royal_jackpot_18", -1);
		break;

		case "Royal_jackpot_18":
			LAi_FadeEx(1.0, 1.0, 1.0, "", "", "");
			DoQuestCheckDelay("Royal_jackpot_19", 3.5);
		break;

		case "Royal_jackpot_19":
			QuestMovieUnLockPlayer();
			sld = characterFromId("Mary_Belfler");
			LAi_ActorTurnToCharacter(sld, characterFromID("Fransua_Olone"));
			sld = characterFromId("Fransua_Olone");
			LAi_ActorTurnToCharacter(sld, characterFromID("Mary_Belfler"));
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mary_Belfler", StringFromKey("LeBasque_Mary_Belfler_1"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_11"));
			AoP_NPCDialogLaunch("Mary_Belfler", "Fransua_Olone", "Royal_jackpot_20");
		break;

		case "Royal_jackpot_20":
			locCameraResetState();
			locCameraTarget(pchar);
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Royal_jackpot_8";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_21":
			LAi_SetActorType(pchar);
			DoQuestReloadToLocation("Bucaneer_outpost_townhall", "goto", "goto_npc_1", "Royal_jackpot_22");
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit1");
			sld = CharacterFromID("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "goto", "goto_gg");
			sld = CharacterFromID("Fransua_Olone");
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "goto", "goto_marso");
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "goto", "goto4");
			sld = CharacterFromID("Rimalier");
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "goto", "goto_npc_3");
			sld = CharacterFromID("Young_Boy_Bask");
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "goto", "goto_npc_2");
			sld = CharacterFromID("Fake_Etien_Marso");
			LAi_SetStayType(sld);
			sld.name = FindPersonalName("Mishel_le_Bask_name");
			sld.lastname = FindPersonalName("Mishel_le_Bask_lastname");
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "reload", "reload2");
		break;

		case "Royal_jackpot_22":
			ChangeShowIntarface();
			locCameraToPos(2.31, 2, 1.71, false);
			locCameraTarget(characterFromID("Mishel_le_Bask"));
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorTurnToLocator(sld, "sit", "sit1");
			sld = CharacterFromID("Fransua_Olone");
			LAi_ActorTurnToLocator(sld, "sit", "sit1");
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorTurnToLocator(sld, "sit", "sit1");
			sld = CharacterFromID("Rimalier");
			LAi_ActorTurnToLocator(sld, "sit", "sit1");
			sld = CharacterFromID("Young_Boy_Bask");
			LAi_ActorTurnToLocator(sld, "sit", "sit1");
			LAi_ActorTurnToLocator(pchar, "reload", "reload2");
			DoQuestCheckDelay("Royal_jackpot_23", 1.5);
		break;

		case "Royal_jackpot_23":
			sld = CharacterFromID("Fake_Etien_Marso");
			sld.Dialog.CurrentNode = "Mass_dialog_1";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_24":
			locCameraToPos(2.31, 2, 1.71, false);
			locCameraTarget(characterFromID("Etien_Marso"));
			sld = CharacterFromID("Fake_Etien_Marso");
			sld.name = FindPersonalName("Etien_Marso_name");
			sld.lastname = FindPersonalName("Etien_Marso_lastname");
			sld.Dialog.CurrentNode = "Mass_dialog_2";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_25":
			locCameraToPos(2.31, 2, 1.71, false);
			locCameraTarget(characterFromID("Fransua_Olone"));
			sld = CharacterFromID("Fake_Etien_Marso");
			sld.name = FindPersonalName("Fransua_Olone_name");
			sld.lastname = FindPersonalName("Fransua_Olone_lastname");
			sld.Dialog.CurrentNode = "Mass_dialog_3";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_26":
			locCameraToPos(2.31, 2, 1.71, false);
			locCameraTarget(characterFromID("Mary_Belfler"));
			sld = CharacterFromID("Fake_Etien_Marso");
			sld.name = FindPersonalName("Mary_Belfler_name");
			sld.lastname = FindPersonalName("Mary_Belfler_lastname");
			sld.Dialog.CurrentNode = "Mass_dialog_4";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_27":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Mary_Belfler");
			sld.Dialog.CurrentNode = "Mass_dialog_5";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_28":
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorTurnToLocator(sld, "sit", "sit1");
			LAi_SetActorType(pchar);
			locCameraToPos(2.31, 2, 1.71, false);
			locCameraTarget(characterFromID("Fransua_Olone"));
			sld = CharacterFromID("Fake_Etien_Marso");
			sld.name = FindPersonalName("Fransua_Olone_name");
			sld.lastname = FindPersonalName("Fransua_Olone_lastname");
			sld.Dialog.CurrentNode = "Mass_dialog_5";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_29":
			locCameraToPos(2.31, 2, 1.71, false);
			locCameraTarget(characterFromID("Mishel_le_Bask"));
			sld = CharacterFromID("Fake_Etien_Marso");
			sld.name = FindPersonalName("Mishel_le_Bask_name");
			sld.lastname = FindPersonalName("Mishel_le_Bask_lastname");
			sld.Dialog.CurrentNode = "Mass_dialog_6";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_30":
			locCameraToPos(2.31, 2, 1.71, false);
			locCameraTarget(characterFromID("Fransua_Olone"));
			sld = CharacterFromID("Fake_Etien_Marso");
			sld.name = FindPersonalName("Fransua_Olone_name");
			sld.lastname = FindPersonalName("Fransua_Olone_lastname");
			sld.Dialog.CurrentNode = "Mass_dialog_7";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_31":
			locCameraToPos(2.31, 2, 1.71, false);
			locCameraTarget(characterFromID("Mishel_le_Bask"));
			sld = CharacterFromID("Fake_Etien_Marso");
			sld.name = FindPersonalName("Mishel_le_Bask_name");
			sld.lastname = FindPersonalName("Mishel_le_Bask_lastname");
			sld.Dialog.CurrentNode = "Mass_dialog_8";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_32":
			locCameraToPos(2.31, 2, 1.71, false);
			locCameraTarget(characterFromID("Fransua_Olone"));
			sld = CharacterFromID("Fake_Etien_Marso");
			sld.name = FindPersonalName("Fransua_Olone_name");
			sld.lastname = FindPersonalName("Fransua_Olone_lastname");
			sld.Dialog.CurrentNode = "Mass_dialog_9";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_32_1":
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetStayType(sld);
			sld.Dialog.CurrentNode = "Mass_dialog_10";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_33":
			sld = CharacterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Mass_dialog_11";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_34":
		sld = CharacterFromID("Royal_Musicant_1");
		ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "goto", "music_1");
		sld = CharacterFromID("Royal_Musicant_2");
		ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "goto", "music_2");
		sld = CharacterFromID("Royal_Musicant_3");
		ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "goto", "music_3");
			DeleteAttribute(pchar, "questTemp.Lebasque.OutpostEmpty");
			for (i = 1; i <= 19; i++)
			{
				sld = characterFromId("Massovka_royal_" + i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			for (i = 1; i <= 6; i++)
			{
				sld = characterFromId("Royal_Olone_Man_" + i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			DoQuestReloadToLocation("Bucaneer_outpost", "reload", "reload6_back", "Royal_jackpot_35");
			sld = characterFromID("Rimalier");

			if (CheckAttribute(pchar, "questTemp.AoP.RimalierWasOfficer") &&
			sti(pchar.questTemp.AoP.RimalierWasOfficer) == true)
			{
				Rimalier_OfficerHired("");
			}

			DeleteAttribute(pchar, "questTemp.AoP.RimalierWasOfficer");
			sld = CharacterFromID("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "goto", "goto13");
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "goto", "goto13");
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "goto", "goto13");
		break;

		case "Royal_jackpot_35":
			AddQuestRecord("Royal_jackpot", "0");
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Mary_Belfler");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", -1);
			sld = CharacterFromID("Fransua_Olone");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", -1);
			sld = CharacterFromID("Etien_Marso");
			AddPassenger(pchar, sld, false);
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", -1);
			pchar.quest.Tortuga_exit_island.win_condition.l1 = "location";
			pchar.quest.Tortuga_exit_island.win_condition.l1.location = "Tortuga";
			pchar.quest.Tortuga_exit_island.win_condition = "Royal_jackpot_36";
		break;

		case "Royal_jackpot_36":
			RemoveMapQuestMark("Tortuga", "Brides_Tortuga"); // убрать метку острова
			bQuestDisableMapEnter = true; // закрыть карту
			Island_SetReloadEnableGlobal("Tortuga", false); // на остров нельзя
			DoQuestCheckDelay("Royal_jackpot_37", 2.5);
		break;

		case "Royal_jackpot_37":
			Set_My_Cabin();
			Sea_CabinStartNow();
			pchar.quest.Tortuga_exit_island_2.win_condition.l1 = "location";
			pchar.quest.Tortuga_exit_island_2.win_condition.l1.location = Get_My_Cabin();
			pchar.quest.Tortuga_exit_island_2.win_condition = "Royal_jackpot_38";
		break;

		case "Royal_jackpot_38":
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = CharacterFromID("Etien_Marso");
			LAi_SetCitizenType(sld);
			sld.Dialog.CurrentNode = "Deck_royal_dialog_1";
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
			sld = characterFromID("Mary_Belfler");
			LAi_SetCitizenType(sld);
			sld.Dialog.CurrentNode = "Deck_royal_dialog_1";
			AddLandQuestmark_Main(sld, "Royal_jackpot");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetCitizenType(sld);
			sld.Dialog.CurrentNode = "Deck_royal_dialog_1";
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto2");
			for (i = 1; i <= 7; i++) //
			{
				sld = GetCharacter(NPC_GenerateCharacter("MainHero_Team" + i, "citiz_" + (39 - i), "man", "man", 5, PIRATE, 1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
				LAi_CharacterDisableDialog(sld);
				LAi_SetCitizenType(sld);
				ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto" + i);
			}
		break;

		case "Royal_jackpot_39":
			sld = GetCharacter(NPC_GenerateCharacter("Atauko", "Miskito_4", "man", "man", 1, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 1, 1, 1, "unarmed", "", 20);
			sld.name = FindPersonalName("Atauko_name");
			sld.lastname = "";
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Atauko_1";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			log_info(StringFromKey("InfoMessages_281"));
			bQuestDisableMapEnter = false; // открыть карту
			chrDisableReloadToLocation = false;
			Island_SetReloadEnableGlobal("Tortuga", true); // На остров можно
			pchar.quest.Cuba_2_island.win_condition.l1 = "location";
			pchar.quest.Cuba_2_island.win_condition.l1.location = "Cuba1";
			pchar.quest.Cuba_2_island.win_condition = "Royal_jackpot_40";
			sld = GetCharacter(NPC_GenerateCharacter("Royal_SanJacinto_Cap", "navy_off_spa_3", "man", "man", CB_Rank() + 2, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank() + 2, CB_Fencing() + 5, CB_Pistol() + 5, "blade16", "pistol2", 60);
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("Royal_SanJacinto_Cap_ship"), CANNON_TYPE_CULVERINE_LBS24, 60, 60, 60);
			sld.name = FindPersonalName("Royal_SanJacinto_Cap_name");
			sld.lastname = FindPersonalName("Royal_SanJacinto_Cap_lastname");
			sld.DontRansackCaptain = true;
			sld.AlwaysEnemy = true;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
			Group_FindOrCreateGroup("Royal_SanJacinto_Group");
			Group_SetType("Royal_SanJacinto_Group", "war");
			Group_AddCharacter("Royal_SanJacinto_Group", sld.id);
			Group_SetGroupCommander("Royal_SanJacinto_Group", sld.id);
			Group_SetTaskAttack("Royal_SanJacinto_Group", PLAYER_GROUP);
			Group_SetPursuitGroup("Royal_SanJacinto_Group", PLAYER_GROUP);
			Group_SetAddress("Royal_SanJacinto_Group", "Cuba1", "quest_ships", "quest_ship_3");
			Group_LockTask("Royal_SanJacinto_Group");
			pchar.quest.Royal_SanJacinto_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.Royal_SanJacinto_Sink.win_condition.l1.character = "Royal_SanJacinto_Cap";
			pchar.quest.Royal_SanJacinto_Sink.win_condition = "Royal_jackpot_41";
			pchar.quest.Royal_SanJacinto_Capture.win_condition.l1 = "Character_Capture";
			pchar.quest.Royal_SanJacinto_Capture.win_condition.l1.character = "Royal_SanJacinto_Cap";
			pchar.quest.Royal_SanJacinto_Capture.win_condition = "Royal_jackpot_44";
			pchar.questTemp.AoP.RoyalJackpot = "FindSanJacinto";
		break;

		case "Royal_jackpot_40":
			sld = CharacterFromID("Atauko");
			RemovePassenger(pchar, sld);
			pchar.questTemp.AoP.RoyalJackpot.HasPassword = 0;
			sld = CharacterFromID("Etien_Marso");
			RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
			sld = characterFromID("Mary_Belfler");
			LAi_SetImmortal(sld, true);
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetImmortal(sld, true);
			RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
			bQuestDisableMapEnter = true; // закрыть карту
			Island_SetReloadEnableGlobal("Cuba1", false); // на остров нельзя
			// AddQuestRecord("Royal_jackpot", "1");
			Notification(StringFromKey("InfoMessages_282"), "none");
			PlaySound("Interface\Ships_Bell.wav");
		break;

		case "Royal_jackpot_41":
			pchar.quest.Royal_SanJacinto_Capture.over = "yes";
			pchar.questTemp.AoP.RoyalJackpot.HasPassword = 0;
			pchar.questTemp.AoP.RoyalJackpot.SanJacintoCaptured = 0;
			AddQuestRecord("Royal_jackpot", "2");
			DoQuestCheckDelay("Royal_jackpot_56", 0.5);
		break;

		case "Royal_jackpot_42":
			LAi_EnableReload();
			DelEventHandler("Control Activation", "LAi_ActivateReload");
			Log_SetActiveAction("Nothing");
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_283"), "Royal_jackpot_43", 0.1, 5.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); // мотаем время
		break;

		case "Royal_jackpot_43":
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Deck_royal_dialog_4";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			DeleteAttribute(&TEV, "StopTimeScale");
		break;

		case "Royal_jackpot_44":
			pchar.quest.Royal_SanJacinto_Sink.over = "yes";
			pchar.questTemp.AoP.RoyalJackpot.SanJacintoCaptured = 1;
			AddQuestRecord("Royal_jackpot", "3");
			sld = GetCharacter(NPC_GenerateCharacter("Royal_Navigator", "q_spa_off_1", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "unarmed", "", 20);
			CB_Perks(sld);
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Royal_Navigator_1";
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "My_Deck", "rld", "aloc3");
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto5");
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto10");
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "My_Deck", "rld", "loc2");
			pchar.quest.Go_My_Deck_Royal.win_condition.l1 = "location";
			pchar.quest.Go_My_Deck_Royal.win_condition.l1.location = "My_deck";
			pchar.quest.Go_My_Deck_Royal.win_condition = "Royal_jackpot_45";
		break;

		case "Royal_jackpot_45":
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorTurnToLocator(sld, "rld", "aloc3");
			sld = CharacterFromID("Fransua_Olone");
			LAi_ActorTurnToLocator(sld, "rld", "aloc3");
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorTurnToLocator(sld, "rld", "aloc3");
			sld = CharacterFromID("Royal_Navigator");
			CharacterTurnToLoc(sld, "reload", "reload1");
			locCameraFromToPos(-1.36, 13.5, 0.57, false, 1.66, 12, -7.49);
			LAi_SetActorType(pchar);
			ChangeCharacterAddressGroup(pchar, "My_Deck", "goto", "goto7");
			DoQuestCheckDelay("Royal_jackpot_46", 0.8);
		break;

		case "Royal_jackpot_46":
			sld = characterFromId("Etien_Marso");
			LAi_ActorTurnToCharacter(sld, characterFromID("Fransua_Olone"));
			sld = characterFromId("Fransua_Olone");
			LAi_ActorTurnToCharacter(sld, characterFromID("Etien_Marso"));

			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_12"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_7"));
			AoP_NPCDialogLaunch("Fransua_Olone", "Etien_Marso", "Royal_jackpot_47");
		break;

		case "Royal_jackpot_47":
			locCameraFromToPos(-1.73, 13.5, -2.72, false, 2.03, 12, -2.36);
			DoQuestCheckDelay("Royal_jackpot_47_1", 0.3);
		break;

		case "Royal_jackpot_47_1":
			sld = characterFromId("Mary_Belfler");
			LAi_ActorTurnToCharacter(sld, characterFromID("Fransua_Olone"));
			sld = characterFromId("Fransua_Olone");
			LAi_ActorTurnToCharacter(sld, characterFromID("Mary_Belfler"));

			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mary_Belfler", StringFromKey("LeBasque_Mary_Belfler_2"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_13"));
			AoP_NPCDialogLaunch("Mary_Belfler", "Fransua_Olone", "Royal_jackpot_48");
		break;

		case "Royal_jackpot_48":
			locCameraResetState();
			locCameraTarget(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "aloc2", "Royal_jackpot_49", -1);
		break;

		case "Royal_jackpot_49":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Fransua_Olone");
			sld.Dialog.CurrentNode = "Deck_royal_dialog_4";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_50":
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Royal_Navigator");
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Royal_jackpot_51":
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Royal_Navigator");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "", -1);
			DoQuestCheckDelay("Royal_jackpot_52", 4);
		break;

		case "Royal_jackpot_52":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Royal_Navigator");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_Navigator_2";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_55":
			pchar.questTemp.AoP.RoyalJackpot.HasPassword = 1;
			sld = CharacterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "Royal_dialog_1";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_56":
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", true); // закрыть проход к заброшке
			if (CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.HasPassword") && sti(pchar.questTemp.AoP.RoyalJackpot.HasPassword) == 1) AddQuestRecord("Royal_jackpot", "4");
			if (CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.SanJacintoCaptured") && sti(pchar.questTemp.AoP.RoyalJackpot.SanJacintoCaptured) == 1)
			{
				StartBattleLandInterface(); // вкл интерфейс
				sld = CharacterFromID("Mary_Belfler");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);

				sld = CharacterFromID("Fransua_Olone");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);

				sld = CharacterFromID("Etien_Marso");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			}
			else
			{
				sld = CharacterFromID("Mary_Belfler");
				ChangeCharacterAddressGroup(sld, "none", "", "");

				sld = CharacterFromID("Fransua_Olone");
				ChangeCharacterAddressGroup(sld, "none", "", "");

				sld = CharacterFromID("Etien_Marso");
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			Island_SetReloadEnableGlobal("Cuba1", true); // на остров можно
			sld = GetCharacter(NPC_GenerateCharacter("Fishing_Guard", "off_spa_1", "man", "man", CB_Rank() + 3, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank() + 3, CB_Fencing() + 10, CB_Pistol() + 10, "blade32", "pistol5", 80);
			CB_Perks(sld);
			AddLandQuestMark_Main(sld, "Royal_jackpot");
			sld.dialog.filename = "Quest\LeBasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Patrol_Halt";
			LAi_SetStayType(sld);
			sld.talker = 10;
			ChangeCharacterAddressGroup(sld, "Cuba_Jungle_07", "quest", "quest_spa");
			for (i = 1; i <= 6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Fishing_Guard_Team_" + i, "milit_mush_spa_"+i, "man", "mushketer", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Cuba_Jungle_07", "reload", "reload2_back");
			}
			pchar.quest.Cuba_Jungle_07_quest.win_condition.l1 = "location";
			pchar.quest.Cuba_Jungle_07_quest.win_condition.l1.location = "Cuba_Jungle_07";
			pchar.quest.Cuba_Jungle_07_quest.win_condition = "Royal_jackpot_57";
			pchar.quest.go_shore_12_quest.win_condition.l1 = "location";
			pchar.quest.go_shore_12_quest.win_condition.l1.location = "Shore12";
			pchar.quest.go_shore_12_quest.win_condition = "Royal_jackpot_56_1";
			bQuestDisableMapEnter = false;
		break;

		case "Royal_jackpot_56_1":
			sld = CharacterFromID("Royal_Navigator");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			QuestPointerToLoc("Cuba_Jungle_06", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Shore12", "reload", "reload1_back"); // поставить поинт
			sld = CharacterFromID("Mary_Belfler");
			sld.Dialog.CurrentNode = "Mary_Bay_Walk";
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			ChangeCharacterAddressGroup(sld, "Shore12", "reload", "sea");
			AddPassenger(pchar, sld, false); // TODO: всем удалить, выше есть
			SetCharacterRemovable(sld, false);
			LAi_SetFreeFighter(sld);
			sld = CharacterFromID("Fransua_Olone");
			sld.Dialog.CurrentNode = "Olone_Bay_Walk";
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			ChangeCharacterAddressGroup(sld, "Shore12", "reload", "sea");
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			LAi_SetFreeFighter(sld);
			sld = CharacterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "Marso_Bay_Walk";
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			ChangeCharacterAddressGroup(sld, "Shore12", "reload", "sea");
			AddPassenger(pchar, sld, false);
			LAi_SetFreeFighter(sld);

			if (GetCharacterIndex("Tichingitu") != -1)
			{
				sld = CharacterFromID("Tichingitu");
				if (IsOfficer(sld))
				{
					sld.Dialog.CurrentNode = "RoyalJackpot_AtaukoFarewell_1";
					LAi_SetActorType(sld);
					LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
		break;

		case "Royal_jackpot_57":
			for (i = 1; i <= 6; i++)
			{
				sld = CharacterFromID("Fishing_Guard_Team_" + i);
				LAi_ActorFollow(sld, characterFromID("Fishing_Guard"), "", -1);
			}
		break;

		case "Royal_jackpot_57_good":
			pchar.questTemp.AoP.RoyalJackpot.VillageAlerted = 0;
			pchar.questTemp.AoP.RoyalJackpot.CordonResult = "password";
			sld = CharacterFromID("Fishing_Guard");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			for (i = 1; i <= 6; i++)
			{
				sld = CharacterFromID("Fishing_Guard_Team_" + i);
				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("Mary_Belfler");
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Mary_Bay_Walk_2";
			sld = CharacterFromID("Fransua_Olone");
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Olone_Bay_Walk_2";
			sld = CharacterFromID("Etien_Marso");
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Marso_Bay_Walk_2";
			DoQuestCheckDelay("Royal_jackpot_58", 0.3);
		break;

		case "Royal_jackpot_57_bad":
			pchar.questTemp.AoP.RoyalJackpot.VillageAlerted = 1;
			pchar.questTemp.AoP.RoyalJackpot.CordonResult = "fight";
			sld = CharacterFromID("Fishing_Guard");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "Fishing_Guard_Team_Group");
			for (i = 1; i <= 6; i++)
			{
				sld = CharacterFromID("Fishing_Guard_Team_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Fishing_Guard_Team_Group");
			}
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Fishing_Guard_Team_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Fishing_Guard_Team_Group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Fishing_Guard_Team_Group", "Royal_jackpot_57_bad_2");
		break;

		case "Royal_jackpot_57_ambush":
			PlaySound("People Fight\PistolFire.wav");
			sld = CharacterFromID("Fishing_Guard");
			LAi_KillCharacter(sld);
			pchar.questTemp.AoP.RoyalJackpot.VillageAlerted = 1;
			pchar.questTemp.AoP.RoyalJackpot.CordonResult = "ambush";
			sld = CharacterFromID("Fishing_Guard");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "Fishing_Guard_Team_Group");
			for (i = 1; i <= 6; i++)
			{
				sld = CharacterFromID("Fishing_Guard_Team_" + i);

				if (i <= 2)
				{
					LAi_SetImmortal(sld, true);
					LAi_SetActorType(sld);
				}
				else
				{
					LAi_SetWarriorType(sld);
				}

				LAi_group_MoveCharacter(sld, "Fishing_Guard_Team_Group");
			}
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Fishing_Guard_Team_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Fishing_Guard_Team_Group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Fishing_Guard_Team_Group", "Royal_jackpot_57_bad_2");
			DoQuestCheckDelay("Royal_jackpot_57_ambush_2", 2.0);
		break;

		case "Royal_jackpot_57_ambush_2":
			for (i = 1; i <= 2; i++)
			{
				sld = CharacterFromID("Fishing_Guard_Team_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Fishing_Guard_Team_Group");
			}

			LAi_group_SetRelation("Fishing_Guard_Team_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Fishing_Guard_Team_Group", LAI_GROUP_PLAYER, true);
		break;

		case "Royal_jackpot_57_bad_2":
			LAi_group_Delete("Fishing_Guard_Team_Group");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			DoQuestCheckDelay("Royal_jackpot_58", 0.3);
			sld = CharacterFromID("Mary_Belfler");
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Mary_Bay_Walk_1";
			sld = CharacterFromID("Fransua_Olone");
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Olone_Bay_Walk_1";
			sld = CharacterFromID("Etien_Marso");
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Marso_Bay_Walk_1";
		break;

		case "Royal_jackpot_58":
			QuestPointerToLoc("Cuba_Jungle_07", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("Cuba_Jungle_08", "reload", "reload1_back"); // поставить поинт
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false); // открыть проход к заброшке
			sld = GetCharacter(NPC_GenerateCharacter("Mateo_Serrano", "citiz_48", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Mateo_Serrano_name");
			sld.lastname = FindPersonalName("Mateo_Serrano_lastname");
			sld.dialog.filename = "Quest\LeBasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Mateo_Serrano_1";
			LAi_SetCitizenType(sld);
			LAi_SetWaterLimit(sld, 1, 1);
			ChangeCharacterAddressGroup(sld, "Fishing_village", "goto", "goto3");
			sld = GetCharacter(NPC_GenerateCharacter("Fishing_village_fisher_1", "fisherman_10", "man", "fisher", 1, FRANCE, -1, false));
			LAi_SetFisherSitType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Fishing_village", "goto", "fish_1");
			sld = GetCharacter(NPC_GenerateCharacter("Fishing_village_fisher_2", "fisherman_11", "man", "fisher", 1, FRANCE, -1, false));
			LAi_SetFisherStayType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Fishing_village", "goto", "fish_2");
			for (i = 1; i <= 5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Fishing_Villager_" + i, "citiz_" + (40+i), "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
				CB_Perks(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_SetCitizenType(sld);
				LAi_SetWaterLimit(sld, 1, 1);
				ChangeCharacterAddressGroup(sld, "Fishing_village", "goto", "goto" + i);
			}

			for (i = 1; i <= 2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Fishing_Soldier_" + i, "sold_spa_" + i, "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10), CB_Pistol() + rand(10), "blade10", "pistol2", 30);
				CB_Perks(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_SetCitizenType(sld);
				LAi_SetWaterLimit(sld, 1, 1);
				ChangeCharacterAddressGroup(sld, "Fishing_village", "goto", "goto" + i);
			}
			pchar.quest.Fishing_village_location.win_condition.l1 = "location";
			pchar.quest.Fishing_village_location.win_condition.l1.location = "Fishing_village";
			pchar.quest.Fishing_village_location.win_condition = "Royal_jackpot_59";
		break;

		case "Royal_jackpot_59":
			if (GetCharacterIndex("Fishing_Guard") >= 0)
			{
				sld = CharacterFromID("Fishing_Guard");
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			for (i = 1; i <= 6; i++)
			{
				if (GetCharacterIndex("Fishing_Guard_Team_" + i) < 0) continue;
				sld = CharacterFromID("Fishing_Guard_Team_" + i);
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}

			LocatorReloadEnterDisable("Fishing_village", "reload1_back", true); // закрыть выход с заброшки
			LocatorReloadEnterDisable("Fishing_village", "reload2_back", true); // закрыть проход в дом
			if (CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.VillageAlerted") && sti(pchar.questTemp.AoP.RoyalJackpot.VillageAlerted) == 1)
			{
				chrDisableReloadToLocation = true;
				sld = CharacterFromID("Mary_Belfler");
				RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
				sld = CharacterFromID("Fransua_Olone");
				RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
				sld = CharacterFromID("Etien_Marso");
				RemoveLandQuestMark_Gen(sld, "Royal_jackpot");

				sld = CharacterFromID("Mateo_Serrano");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Royal_Fishing_Village_Enemies");

				for (i = 1; i <= 5; i++)
				{
					sld = CharacterFromID("Fishing_Villager_" + i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "Royal_Fishing_Village_Enemies");
				}
				for (i = 1; i <= 2; i++)
				{
					sld = CharacterFromID("Fishing_Soldier_" + i);
					LAi_SetWarriorType(sld);
					LAi_group_MoveCharacter(sld, "Royal_Fishing_Village_Enemies");
				}

				LAi_SetFightMode(pchar, true);
				LAi_group_SetRelation("Royal_Fishing_Village_Enemies", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("Royal_Fishing_Village_Enemies", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("Royal_Fishing_Village_Enemies", "Royal_jackpot_59_fight_end");
				break;
			}
			sld = CharacterFromID("Mary_Belfler");
			sld.Dialog.CurrentNode = "Royal_jackpot_1";
			RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_1";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = CharacterFromID("Fransua_Olone");
			RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
			sld = CharacterFromID("Etien_Marso");
			RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
		break;

		case "Royal_jackpot_59_fight_end":
			LAi_group_Delete("Royal_Fishing_Village_Enemies");
			LAi_grp_alarmactive = false;
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			chrDisableReloadToLocation = false;
			DoQuestCheckDelay("Royal_jackpot_63", 0.5);
		break;

		case "Royal_jackpot_60":
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_1";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Royal_jackpot_61":
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_3";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Royal_jackpot_62":
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetWaterLimit(sld, 1, 1);
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("Etien_Marso");
			LAi_SetWaterLimit(sld, 1, 1);
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetWaterLimit(sld, 1, 1);
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("Mateo_Serrano");
			AddLandQuestMark_Main(sld, "Royal_jackpot");
		break;

		case "Royal_jackpot_63":
			LocatorReloadEnterDisable("Fishing_village", "reload2_back", false); // открыть проход в дом
			sld = CharacterFromID("Mateo_Serrano");
			RemoveLandQuestMark_Main(sld, "Royal_jackpot");
			LAi_CharacterDisableDialog(sld);
			QuestPointerToLoc("Fishing_Village", "reload", "reload2_back"); // поставить поинт
			i = FindLocation("Fishing_Village");
			locations[i].reload.l2.name = "reload2_back";
			locations[i].reload.l2.go = "CommonRoom_MH12";
			locations[i].reload.l2.emerge = "reload1";
			locations[i].reload.l2.autoreload = "0";
			locations[i].reload.l2.label = "house";
			locations[i].locators_radius.reload.reload2_back = 2.0;
			sld = GetCharacter(NPC_GenerateCharacter("Thomas_Arellano", "off_spa_4", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Thomas_Arellano_name");
			sld.lastname = FindPersonalName("Thomas_Arellano_lastname");
			sld.dialog.filename = "Quest\LeBasque\Arelano_dialog.c";
			sld.Dialog.CurrentNode = "Arellano_1";
			LAi_SetSitType(sld);
			sld.nonTable = true;
			AddLandQuestMark_Main(sld, "Royal_jackpot");
			if (CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.VillageAlerted") && sti(pchar.questTemp.AoP.RoyalJackpot.VillageAlerted) == 1)
			{
				sld.Dialog.CurrentNode = "Arellano_Alert_1";
				LAi_SetStayType(sld);
				ChangeCharacterAddressGroup(sld, "CommonRoom_MH12", "goto", "goto5");
			}
			else
			{
				sld.Dialog.CurrentNode = "Arellano_1";
				LAi_SetSitType(sld);
				sld.nonTable = true;
				ChangeCharacterAddressGroup(sld, "CommonRoom_MH12", "sit", "sit1");
			}
		break;

		case "Royal_jackpot_64":
			QuestPointerDelLoc("Fishing_Village", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("Cuba_Jungle_07", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("Cuba_Jungle_08", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Cuba_Jungle_06", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Shore12", "reload", "reload1_back"); // удалить поинт
			QuestPointerToLoc("Fishing_Village", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Cuba_Jungle_08", "reload", "reload3_back"); // поставить поинт
			QuestPointerToLoc("Cuba_Jungle_07", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Cuba_Jungle_06", "reload", "reload3_back"); // поставить поинт
			LocatorReloadEnterDisable("Fishing_village", "reload1_back", false); // открыть выход с заброшки
			if (CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.VillageAlerted") && sti(pchar.questTemp.AoP.RoyalJackpot.VillageAlerted) == 1)
				AddQuestRecord("Royal_jackpot", "5.1");
			else
				AddQuestRecord("Royal_jackpot", "5");
			sld = CharacterFromID("Thomas_Arellano");
			ChangeCharacterAddressGroup(sld, "CommonRoom_MH12", "goto", "goto5");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = CharacterFromID("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "Fishing_village", "goto", "goto3");
			sld = CharacterFromID("Fransua_Olone");
			ChangeCharacterAddressGroup(sld, "Fishing_village", "goto", "goto4");
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Fishing_village", "goto", "goto5");
			pchar.quest.Fish_house_banda.win_condition.l1 = "location";
			pchar.quest.Fish_house_banda.win_condition.l1.location = "Fishing_village";
			pchar.quest.Fish_house_banda.win_condition = "Royal_jackpot_65";
		break;

		case "Royal_jackpot_65":
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetFreeFighter(sld);
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetFreeFighter(sld);
			sld = CharacterFromID("Etien_Marso");
			LAi_SetFreeFighter(sld);
			pchar.quest.go_anyutka.win_condition.l1 = "location";
			pchar.quest.go_anyutka.win_condition.l1.location = "Shore12";
			pchar.quest.go_anyutka.win_condition = "Royal_jackpot_66";
		break;

		case "Royal_jackpot_66":
			AoP_OfficersSetCitizen();
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			TEV.StopTimeScale = true; // запрет ускорения
			DoQuestCheckDelay("Off_Interface", 0.2);
			QuestMovieLockPlayer(); // окаемки вкл
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = CharacterFromID("Thomas_Arellano");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "quest1", "", -1);
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "quest2", "", -1);
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "quest4", "", -1);
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "quest3", "", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, characterFromID("Thomas_Arellano"), "", -1);
			locCameraFlyToPositionLookToPoint(4.32, 6.6, -14.3, 7.76, 3.12, 6.84, 7.90, 5.6, -19.08, -1.0, 500);
			DoQuestCheckDelay("Royal_jackpot_68", 5.5);
		break;

		case "Royal_jackpot_68":
			LAi_FadeEx(1.0, 1.0, 1.0, "", "", "");
			DoQuestCheckDelay("Royal_jackpot_69", 1);
		break;

		case "Royal_jackpot_69":
			sld = CharacterFromID("Mary_Belfler");
			DeleteAttribute(sld, "FreeFighter");
			LAi_ActorTurnToLocator(sld, "quest", "quest1");
			sld = CharacterFromID("Etien_Marso");
			DeleteAttribute(sld, "FreeFighter");
			LAi_ActorTurnToLocator(sld, "quest", "quest1");
			sld = CharacterFromID("Fransua_Olone");
			DeleteAttribute(sld, "FreeFighter");
			LAi_ActorTurnToLocator(sld, "quest", "quest1");
			locCameraResetState();
			locCameraFromToPos(1.70, 2, 3.93, true, 9.53, 3, -4.67);
			DoQuestCheckDelay("Royal_jackpot_70", 2);
		break;

		case "Royal_jackpot_70":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Thomas_Arellano");
			if (CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.VillageAlerted") && sti(pchar.questTemp.AoP.RoyalJackpot.VillageAlerted) == 1)
				sld.Dialog.CurrentNode = "Arellano_Alert_Bay_1";
			else
				sld.Dialog.CurrentNode = "Arellano_6";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_71":
			ChangeShowIntarface();
			QuestMovieLockPlayer();
			LAi_SetActorType(pchar);

			string sTurnCharacters[4];
			sTurnCharacters[0] = pchar.id;
			sTurnCharacters[1] = "Mary_Belfler";
			sTurnCharacters[2] = "Etien_Marso";
			sTurnCharacters[3] = "Fransua_Olone";

			for (i = 0; i < 4; i++)
			{
				if (GetCharacterIndex(sTurnCharacters[i]) == -1) continue;
				sld = CharacterFromID(sTurnCharacters[i]);
				CharacterTurnAy(sld, 1.0);
			}
			DoQuestCheckDelay("Royal_jackpot_71_1", 0.2);
		break;

		case "Royal_jackpot_71_1":
			locCameraToPos(11.99, 5, -0.11, false);
			locCameraTarget(CharacterFromID("Thomas_Arellano"));

			sld = CharacterFromID("Thomas_Arellano");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "quest5", "Royal_jackpot_72", -1);
		break;

		case "Royal_jackpot_72":
			sld = CharacterFromID("Thomas_Arellano");
			LAi_ActorRunToLocator(sld, "goto", "goto4", "", -1);
			sld = characterFromID("Fransua_Olone");
			LAi_ActorTurnToLocator(sld, "quest", "quest5");
			LAi_ActorAnimation(sld, "Shot", "Royal_jackpot_73", 1);
		break;

		case "Royal_jackpot_73":
			sld = characterFromId("Thomas_Arellano");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			SetCharacterTask_Dead(sld);
			DoQuestCheckDelay("Royal_jackpot_74", 1);
		break;

		case "Royal_jackpot_74":
			LAi_ActorTurnToCharacter(pchar, characterFromID("Fransua_Olone"));
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorFollow(sld, characterFromID("Fransua_Olone"), "", -1);
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorFollow(sld, characterFromID("Fransua_Olone"), "Royal_jackpot_75", -1);
			locCameraFromToPos(9.22, 5.5, -8.30, false, 9.91, 3, 0.04);
		break;

		case "Royal_jackpot_75":
			QuestMovieUnLockPlayer();

			sld = CharacterFromID("Etien_Marso");
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Fransua_Olone"));

			sld = CharacterFromID("Fransua_Olone");
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Etien_Marso"));

			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_8"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_14"));
			AoP_NPCDialogLaunch("Etien_Marso", "Fransua_Olone", "Royal_jackpot_76");
		break;

		case "Royal_jackpot_76":
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Fransua_Olone"));

			sld = CharacterFromID("Fransua_Olone");
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Mary_Belfler"));

			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mary_Belfler", StringFromKey("LeBasque_Mary_Belfler_3"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_15"));
			AoP_NPCDialogLaunch("Mary_Belfler", "Fransua_Olone", "Royal_jackpot_77");
		break;

		case "Royal_jackpot_77":
			sld = characterFromId("Thomas_Arellano");
			ChangeCharacterAddressGroup(sld, "none", "", ""); // труп убрать
			sld = GetCharacter(NPC_GenerateCharacter("Thomas_Arellano_fake", "off_spa_4", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Thomas_Arellano_name");
			sld.lastname = FindPersonalName("Thomas_Arellano_lastname");
			sld.dialog.filename = "Quest\LeBasque\Arelano_dialog.c";
			if (CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.VillageAlerted") && sti(pchar.questTemp.AoP.RoyalJackpot.VillageAlerted) == 1)
				sld.Dialog.CurrentNode = "Arellano_Alert_Wounded_1";
			else
				sld.Dialog.CurrentNode = "Arellano_16";
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Shore12", "goto", "goto4");
			locCameraResetState();
			locCameraTarget(pchar);
			LAi_SetActorType(pchar);
			sld = characterFromId("Mary_Belfler");
			LAi_ActorFollow(sld, characterFromID("blaze"), "Royal_jackpot_78", -1);
		break;

		case "Royal_jackpot_78":
			AoP_OfficersRestore();
			sld = characterFromId("Thomas_Arellano_fake");
			LAi_CharacterDisableDialog(sld);
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Mary_Belfler");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_2";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_79":
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			DeleteAttribute(&TEV, "StopTimeScale"); // можно ускоряться
			sld = characterFromId("Thomas_Arellano_fake");
			AddLandQuestMark_Main(sld, "Royal_jackpot");
			LAi_CharacterEnableDialog(sld);
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorFollow(sld, characterFromID("Thomas_Arellano_fake"), "", -1);
		break;

		case "Royal_jackpot_80":
			PlayVoice("PEOPLE FIGHT\Death_NPC_02.wav")
			sld = characterFromId("Thomas_Arellano_fake");
			BeginChangeCharacterActions(sld);
			sld.actions.dead.d1 = "Ground_Death1";
			sld.actions.dead.d2 = "Ground_Death1";
			EndChangeCharacterActions(sld);
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Royal_jackpot_80_1", 1);
		break;

		case "Royal_jackpot_AnnaDeadline":
			if (CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.AnnaDebt") && sti(pchar.questTemp.AoP.RoyalJackpot.AnnaDebt) == 1)
			{
				DeleteAttribute(pchar, "questTemp.AoP.RoyalJackpot.AnnaDebt");
				pchar.questTemp.AoP.RoyalJackpot.AnnaFailed = true;
				ChangeCharacterReputation(pchar, -20);
				AddQuestRecord("Royal_jackpot_Anna", "2");
				CloseQuestHeader("Royal_jackpot_Anna");
			}
		break;

		case "Royal_jackpot_80_1":
			sld = CharacterFromID("Mary_Belfler");
			sld.Dialog.CurrentNode = "Royal_jackpot_3";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			sld = characterFromId("Fransua_Olone");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			sld = characterFromId("Etien_Marso");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
		break;

		case "Royal_jackpot_81":
			sld = characterFromId("Mary_Belfler");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			sld = CharacterFromID("Atauko");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore12", "reload", "reload1");
			DoQuestCheckDelay("Royal_jackpot_82", 0.3);
		break;

		case "Royal_jackpot_82":
			QuestPointerDelLoc("Fishing_Village", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Cuba_Jungle_08", "reload", "reload3_back"); // удалить  поинт
			QuestPointerDelLoc("Cuba_Jungle_07", "reload", "reload1_back"); // удалить  поинт
			QuestPointerDelLoc("Cuba_Jungle_06", "reload", "reload3_back"); // удалить  поинт
			sld = characterFromId("Atauko");
			sld.Dialog.CurrentNode = "Atauko_Royal_1";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Royal_jackpot_83":
			sld = characterFromId("Atauko");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			sld = characterFromId("Etien_Marso");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Royal_jackpot_84":
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			TEV.StopTimeScale = true; // запрет ускорения
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "sea", "", -1);
			sld = characterFromId("Etien_Marso");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			sld = characterFromId("Mary_Belfler");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			sld = characterFromId("Fransua_Olone");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			DoQuestCheckDelay("Royal_jackpot_85", 3);
		break;

		case "Royal_jackpot_85":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Royal_jackpot_86", 3);
		break;

		case "Royal_jackpot_86":
			locCameraFlyToPositionLookToPoint(4.65, 15, -13.72, 10.91, 15, 6.81, 8.32, 15, -24.54, -1.0, 2000);
			DoQuestCheckDelay("Royal_jackpot_87", 4);
		break;

		case "Royal_jackpot_87":
			CreateLocationParticlesXZ("large_smoke", "quest", "quest6", 0, 0, 0, "");
			DoQuestCheckDelay("Royal_jackpot_88", 5);
		break;

		case "Royal_jackpot_88":
			CreateLocationParticlesXZ("large_smoke", "quest", "quest7", 0, 0, 0, "");
			DoQuestCheckDelay("Royal_jackpot_89", 6);
		break;

		case "Royal_jackpot_89":
			chrDisableReloadToLocation = false; // открыть локацию
			sld = characterFromId("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Fransua_Olone");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			DeleteAttribute(&TEV, "StopTimeScale"); // можно ускоряться
			locCameraResetState();
			LAi_SetPlayerType(pchar);
			QuestMovieUnLockPlayer(); // окаемки выкл
			QuestToSeaLogin_PrepareLoc("Cuba1", "quest_ships", "quest_ship_13", true);
			QuestToSeaLogin_Launch();
			DoQuestCheckDelay("Royal_jackpot_90", 2);
		break;

		case "Royal_jackpot_90":
			AoP_AddMapMarkByCoords("Royal_jackpot_MeetingPoint", -79.83, 315.727);
			pchar.questTemp.AoP.RoyalJackpot.MeetingPoint = true;
			AddQuestRecord("Royal_jackpot", "6");
			bQuestDisableMapEnter = false; // открыть карту
		break;

		case "Royal_jackpot_91":
			TEV.StopTimeScale = true; // запрет ускорения
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_284"), "", 0.1, 4.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 2, 0, 0);
			SetCurrentTime(23, 45);
			Whr_UpdateWeather();
			float px = stf(pchar.Ship.Pos.x);
			float pz = stf(pchar.Ship.Pos.z);
			float pay = stf(pchar.Ship.Ang.y);

			float forwardX = sin(pay);
			float forwardZ = cos(pay);

			float sideX = cos(pay);
			float sideZ = -sin(pay);
			Group_DeleteGroup("RoyalJackpot_LeBasque_Group");
			Group_DeleteGroup("RoyalJackpot_Olone_Group");
			Group_DeleteGroup("RoyalJackpot_Marso_Group");
			Group_FindOrCreateGroup("RoyalJackpot_LeBasque_Group");
			Group_SetType("RoyalJackpot_LeBasque_Group", "war");
			sld = CharacterFromID("Mishel_le_Bask");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, FindPersonalName("Mishel_le_Bask_ship"), CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
			ref rRealShip = GetRealShip(sti(sld.Ship.Type));
			rRealShip.MaxCaliber = 48;
			rRealShip.Cannon = CANNON_TYPE_CANNON_LBS48;
			sld.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS48;
			SetCrewQuantityFull(sld);
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true;
			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false;
			sld.AoP_NoBoat = true;
			sld.ShipHideImmortal = 1000;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			Group_AddCharacter("RoyalJackpot_LeBasque_Group", "Mishel_le_Bask");
			Group_SetGroupCommander("RoyalJackpot_LeBasque_Group", "Mishel_le_Bask");
			Group_SetAddressNone("RoyalJackpot_LeBasque_Group");
			Group_SetXZ_AY("RoyalJackpot_LeBasque_Group",
					px + forwardX * 300.0 + sideX * 120.0,
					pz + forwardZ * 300.0 + sideZ * 120.0,
					pay + 3.14);
			Group_SetTaskNone("RoyalJackpot_LeBasque_Group");
			Group_LockTask("RoyalJackpot_LeBasque_Group");
			Sea_LoginGroup("RoyalJackpot_LeBasque_Group");
			Ship_SetSailState(sti(sld.index), 0.0);
			Ship_ClearImpulseStrength(sld);
			sld.Ship.Speed.x = 0.0;
			sld.Ship.Speed.y = 0.0;
			sld.Ship.Speed.z = 0.0;
			Ship_SetTaskDrift(PRIMARY_TASK, sti(sld.index));
			sld.ShipTaskLock = true;
			Group_FindOrCreateGroup("RoyalJackpot_Olone_Group");
			Group_SetType("RoyalJackpot_Olone_Group", "war");
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetImmortal(sld, false);
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			FantomMakeCoolSailor(sld, SHIP_CORVETTE, FindPersonalName("Fransua_Olone_ship_Fleo"), CANNON_TYPE_CANNON_LBS24, 90, 90, 90);
			SetCrewQuantityFull(sld);
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true;
			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false;
			sld.AoP_NoBoat = true;
			sld.ShipHideImmortal = 1000;
			SetCharacterRemovable(sld, false);
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			SetCharacterRelationBoth(sti(sld.index), GetCharacterIndex("Mishel_le_Bask"), RELATION_FRIEND);
			Group_AddCharacter("RoyalJackpot_Olone_Group", "Fransua_Olone");
			Group_SetGroupCommander("RoyalJackpot_Olone_Group", "Fransua_Olone");
			Group_SetAddressNone("RoyalJackpot_Olone_Group");
			Group_SetXZ_AY("RoyalJackpot_Olone_Group",
					px + forwardX * 350.0 - sideX * 120.0,
					pz + forwardZ * 350.0 - sideZ * 120.0,
					pay + 3.14);
			Group_SetTaskNone("RoyalJackpot_Olone_Group");
			Group_LockTask("RoyalJackpot_Olone_Group");
			Sea_LoginGroup("RoyalJackpot_Olone_Group");
			Ship_SetSailState(sti(sld.index), 0.0);
			Ship_ClearImpulseStrength(sld);
			sld.Ship.Speed.x = 0.0;
			sld.Ship.Speed.y = 0.0;
			sld.Ship.Speed.z = 0.0;
			Ship_SetTaskDrift(PRIMARY_TASK, sti(sld.index));
			sld.ShipTaskLock = true;

			Group_FindOrCreateGroup("RoyalJackpot_Marso_Group");
			Group_SetType("RoyalJackpot_Marso_Group", "war");
			sld = CharacterFromID("Etien_Marso");
			RemovePassenger(pchar, sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			if (!CheckAttribute(sld, "Ship.Type") || sti(sld.Ship.Type) == SHIP_NOTUSED) FantomMakeCoolSailor(sld, SHIP_CORVETTE, FindPersonalName("Etien_Marso_ship"), CANNON_TYPE_LBS_BY_SHIP, 82, 82, 82);
			SetCrewQuantityFull(sld);
			SetRandGeraldSail(sld, PIRATE);
			sld.nation = PIRATE;
			sld.Ship.Mode = "pirate";
			sld.Ship.Crew.Morale = 100;
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true;
			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false;
			sld.AoP_NoBoat = true;
			sld.ShipHideImmortal = 1000;
			SetCharacterRemovable(sld, false);
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);
			SetCharacterRelationBoth(sti(sld.index), GetCharacterIndex("Mishel_le_Bask"), RELATION_FRIEND);
			SetCharacterRelationBoth(sti(sld.index), GetCharacterIndex("Fransua_Olone"), RELATION_FRIEND);
			Group_AddCharacter("RoyalJackpot_Marso_Group", "Etien_Marso");
			Group_SetGroupCommander("RoyalJackpot_Marso_Group", "Etien_Marso");
			Group_SetAddressNone("RoyalJackpot_Marso_Group");
			Group_SetXZ_AY("RoyalJackpot_Marso_Group",
					px + forwardX * 420.0,
					pz + forwardZ * 420.0,
					pay + 3.14);
			Group_SetTaskNone("RoyalJackpot_Marso_Group");
			Group_LockTask("RoyalJackpot_Marso_Group");
			Sea_LoginGroup("RoyalJackpot_Marso_Group");
			Ship_SetSailState(sti(sld.index), 0.0);
			Ship_ClearImpulseStrength(sld);
			sld.Ship.Speed.x = 0.0;
			sld.Ship.Speed.y = 0.0;
			sld.Ship.Speed.z = 0.0;
			Ship_SetTaskDrift(PRIMARY_TASK, sti(sld.index));
			sld.ShipTaskLock = true;
			pchar.questTemp.AoP.RoyalJackpot.MarsoSeaReady = true;

			DoQuestCheckDelay("Royal_jackpot_92", 7);
		break;

		case "Royal_jackpot_92":
			sld = CharacterFromID("Mishel_le_Bask");
			Ship_SetLightsOff(sld, 0.0, true, true, true);
			sld = CharacterFromID("Fransua_Olone");
			Ship_SetLightsOff(sld, 0.0, true, true, true);
			sld = CharacterFromID("Etien_Marso");
			Ship_SetLightsOff(sld, 0.0, true, true, true);
			i = FindLocation("Ship_deck");
			Locations[i].models.always.locators = "deckBig_locators_bask";
			AoP_LeBasqueSignalShot();
			DoQuestCheckDelay("Royal_jackpot_93", 3);
		break;

		case "Royal_jackpot_93":
			PlayVoice("Abandon_0");
			DoQuestCheckDelay("Royal_jackpot_94", 2.5);
			sld = characterFromId("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Ship_deck", "reload", "reload1");
			sld = characterFromId("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "Ship_deck", "reload", "reload1");
			sld = characterFromId("Fransua_Olone");
			ChangeCharacterAddressGroup(sld, "Ship_deck", "reload", "reload1");
			sld = characterFromId("Mishel_le_Bask");
			AddLandQuestMark_Main(sld, "Royal_jackpot");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Ship_deck", "quest", "quest1");
			sld = characterFromId("Young_Boy_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Ship_deck", "quest", "quest2");
		break;

		case "Royal_jackpot_94":
			DeleteAttribute(&TEV, "StopTimeScale"); // можно ускоряться
			AoP_CreateLeBasqueDeckCrew();
			pchar.quest.Royal_jackpot_94.win_condition.l1 = "location";
			pchar.quest.Royal_jackpot_94.win_condition.l1.location = "Ship_deck";
			pchar.quest.Royal_jackpot_94.win_condition = "Royal_jackpot_95";
			sld = CharacterFromID("Mishel_le_Bask");
			Sea_DeckBoatLoad_ForQuest(sti(sld.index));
		break;

		case "Royal_jackpot_95":
			sld = characterFromId("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "quest4", "Royal_jackpot_95_1", -1);
			sld = characterFromId("Mary_Belfler");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "quest5", "Royal_jackpot_95_2", -1);
			sld = characterFromId("Fransua_Olone");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "quest", "quest6", "Royal_jackpot_96", -1);
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Royal_jackpot_10";
			LAi_ActorTurnToLocator(sld, "quest", "quest3");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Ship_deck", "quest", "quest1");
			sld = characterFromId("Young_Boy_Bask");
			LAi_ActorTurnToLocator(sld, "quest", "quest3");
		break;

		case "Royal_jackpot_95_1":
			sld = characterFromId("Etien_Marso");
			MakeUnpushable(sld, true);
			LAi_ActorTurnToLocator(sld, "quest", "quest1");
		break;

		case "Royal_jackpot_95_2":
			sld = characterFromId("Mary_Belfler");
			MakeUnpushable(sld, true);
			LAi_ActorTurnToLocator(sld, "quest", "quest1");
		break;

		case "Royal_jackpot_96":
			sld = characterFromId("Fransua_Olone");
			LAi_CharacterEnableDialog(sld);
			MakeUnpushable(sld, true);
			LAi_ActorTurnToLocator(sld, "quest", "quest1");
		break;

		case "Royal_jackpot_111":
			Return2SeaAfterCabin();
			DoQuestCheckDelay("Royal_jackpot_112", 4);
		break;

		case "Royal_jackpot_112":
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_285"), "", 0.1, 3.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 0);
			Whr_UpdateWeather();
			DoQuestCheckDelay("Royal_jackpot_113", 4);
		break;

		case "Royal_jackpot_113":
			PlayVoice("EvEnemy_1");
			DoQuestCheckDelay("Royal_jackpot_114", 2.0);
		break;

		case "Royal_jackpot_114":
			AddQuestRecord("Royal_jackpot", "7");
			sld = CharacterFromID("Mishel_le_Bask");
			Ship_SetLightsOn(sld, 0.0, true, true, true);
			sld = CharacterFromID("Fransua_Olone");
			Ship_SetLightsOn(sld, 0.0, true, true, true);
			sld = CharacterFromID("Etien_Marso");
			Ship_SetLightsOn(sld, 0.0, true, true, true);
			Ship_SetLightsOn(pchar, 0.0, true, true, true);
			AoP_RoyalCreateMargaritaBattle();
		break;

		case "Royal_jackpot_115":
			AoP_RoyalUnlockMargarita();
		break;

		case "Royal_jackpot_116":
			LAi_group_Delete("AoP_Margarita_Spanish");
			LAi_grp_alarmactive = false;
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			AoP_RoyalMargaritaSurvivorsWalk();
			sld = CharacterFromID("Mishel_le_Bask");
			AddLandQuestMark_Main(sld, "Royal_jackpot");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_deck_1";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Royal_jackpot_117":
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorRunToLocator(sld, "goto", "goto11", "", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, characterFromID("Mishel_le_Bask"), "", -1);
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			LAi_ActorFollow(pchar, characterFromID("Mishel_le_Bask"), "", -1);
			DoQuestCheckDelay("Royal_jackpot_118", 3);
		break;

		case "Royal_jackpot_118":
			LAi_FadeEx(2.0, 2.0, 1.0, "", "", "");
			DoQuestCheckDelay("Royal_jackpot_119", 3.5);
		break;

		case "Royal_jackpot_119":
			QuestMovieUnLockPlayer(); // окаемки выкл
			DoQuestReloadToLocation("Cabin_Huge_quest", "rld", "loc6", "Royal_jackpot_120");
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Cabin_Huge_quest", "rld", "loc5");
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Cabin_Huge_quest", "rld", "loc0");
			sld = CharacterFromID("Royal_Margarita_Cap");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Cabin_Huge_quest", "goto", "goto1");
		break;

		case "Royal_jackpot_120":
			sld = CharacterFromID("Royal_Margarita_Cap");
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Don_Alonso_1";
			LAi_ActorTurnToLocator(sld, "sit", "sit0");
			LAi_ActorAnimation(sld, "Barman_idle", "", 500);
			DoQuestCheckDelay("Royal_jackpot_121", 2);
		break;

		case "Royal_jackpot_121":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Royal_Margarita_Cap");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_122":
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorTurnToCharacter(sld, characterFromID("Royal_Margarita_Cap"));
			sld = CharacterFromID("Royal_Margarita_Cap");
			LAi_ActorTurnToCharacter(sld, characterFromID("Mary_Belfler"));
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mary_Belfler", StringFromKey("LeBasque_Mary_Belfler_4"));
			AoP_NPCDialogAddLine("Royal_Margarita_Cap", StringFromKey("LeBasque_Royal_Margarita_Cap_1"));
			AoP_NPCDialogAddLine("Mary_Belfler", StringFromKey("LeBasque_Mary_Belfler_5"));
			AoP_NPCDialogAddLine("Royal_Margarita_Cap", StringFromKey("LeBasque_Royal_Margarita_Cap_2"));
			AoP_NPCDialogLaunch("Royal_Margarita_Cap", "Mary_Belfler", "Royal_jackpot_123");
		break;

		case "Royal_jackpot_123":
			LAi_SetActorType(pchar);
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			sld = characterFromId("Royal_Margarita_Cap");
			LAi_ActorFollow(sld, characterFromID("Mary_Belfler"), "Royal_jackpot_124", -1);
		break;

		case "Royal_jackpot_124":
			sld = characterFromId("Royal_Margarita_Cap");
			LAi_ActorGoToLocator(sld, "goto", "goto1", "Royal_jackpot_125", -1);
		break;

		case "Royal_jackpot_125":
			QuestMovieUnLockPlayer(); // окаемки выкл
			DoQuestCheckDelay("Royal_jackpot_125_1", 0.2);
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Mary_Belfler");
			sld.Dialog.CurrentNode = "Royal_jackpot_9";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_125_1":
			sld = characterFromId("Royal_Margarita_Cap");
			LAi_ActorTurnToCharacter(sld, characterFromID("blaze"));
		break;

		case "Royal_jackpot_126":
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Royal_jackpot_33";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_127":
			QuestMovieLockPlayer(); // окаемки вкл
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto1");
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorGoToLocator(sld, "officers", "officer5", "Royal_jackpot_128", -1);
		break;

		case "Royal_jackpot_128":
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorTurnToLocator(sld, "sit", "sit0");
			DoQuestCheckDelay("Royal_jackpot_129", 2.5);
		break;

		case "Royal_jackpot_129":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Royal_jackpot_34";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_131":
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Royal_jackpot_35";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_132":
			sld = characterFromId("Royal_Margarita_Cap");
			sld.Dialog.CurrentNode = "Don_Alonso_4";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_133":
			sld = characterFromId("Royal_Margarita_Cap");
			LAi_ActorTurnToLocator(sld, "sit", "sit0");
			LAi_SetActorType(pchar);
			QuestMovieLockPlayer(); // окаемки вкл
			LAi_ActorFollow(pchar, characterFromID("Royal_Margarita_Cap"), "", -1);
			DoQuestCheckDelay("Royal_jackpot_134", 2);
		break;

		case "Royal_jackpot_134":
			LAi_SetActorType(pchar);
			sld = GetCharacter(NPC_GenerateCharacter("Royal_matros", "citiz_34", "man", "man", CB_Rank(), PIRATE, 1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Royal_matros_name");
			sld.dialog.filename = "Quest\LeBasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Matros_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Cabin_Huge_quest", "reload", "reload1");
			DoQuestCheckDelay("Royal_jackpot_135", 0.1);
		break;

		case "Royal_jackpot_135":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Royal_matros");
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_137":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorTurnToCharacter(sld, characterFromID("Royal_Margarita_Cap"));
			sld = CharacterFromID("Royal_Margarita_Cap");
			LAi_ActorTurnToCharacter(sld, characterFromID("Mishel_le_Bask"));
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_9"));
			AoP_NPCDialogAddLine("Royal_Margarita_Cap", StringFromKey("LeBasque_Royal_Margarita_Cap_3"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Royal_Margarita_Cap", "Royal_jackpot_138");
		break;

		case "Royal_jackpot_138":
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Royal_jackpot_35_1";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_139":
			sld = GetCharacter(NPC_GenerateCharacter("Spa_Fakel_Deck", "sold_spa_5", "man", "man", CB_Rank(), SPAIN, 1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
			CB_Perks(sld);
			sld.dialog.filename = "Quest\LeBasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Fakel_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "aop_deck2", "goto", "goto1");
			sld = CharacterFromID("Mishel_le_Bask");
			ChangeCharacterAddressGroup(sld, "aop_deck2", "rld", "aloc10");
			sld = CharacterFromID("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "aop_deck2", "rld", "aloc9");
			DoQuestReloadToLocation("aop_deck2", "rld", "aloc5", "Royal_jackpot_140");
		break;

		case "Royal_jackpot_140":
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			TEV.StopTimeScale = true; // запрет ускорения
			LAi_SetActorType(pchar);
			QuestMovieLockPlayer();
			EndBattleLandInterface();
			sld = CharacterFromID("Spa_Fakel_Deck");
			LAi_ActorTurnToLocator(sld, "rld", "aloc9");
			SendMessage(sld, "lslssl", MSG_CHARACTER_EX_MSG, "TieItem", 1, "HandsItems\Fakel", "Saber_hand", 1); // держит факел
			LAi_ActorAnimation(sld, "torch_stand", "", 1.8);
			locCameraFlyToPositionLookToPoint(-2.60, 14, 0.39, 0.14, 14, -6.69, 1.72, 13, -10.82, -1.0, 1000);
			DoQuestCheckDelay("Royal_jackpot_141", 5);
		break;

		case "Royal_jackpot_141":
			LAi_FadeEx(1.0, 1.0, 1.0, "", "", "");
			DoQuestCheckDelay("Royal_jackpot_142", 1.5);
		break;

		case "Royal_jackpot_142":
			locCameraResetState();
			locCameraFlyToPositionLookToPoint(2.28, 14, 9.30, 1.78, 14, -0.78, 1.38, 13, -8.11, -1.0, 600);
			LAi_ActorRunToLocator(pchar, "rld", "loc0", "", -1);
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorRunToLocator(sld, "rld", "loc4", "", -1);
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorRunToLocator(sld, "rld", "loc3", "", -1);
			DoQuestCheckDelay("Royal_jackpot_143", 3);
		break;

		case "Royal_jackpot_143":
			LAi_FadeEx(1.0, 1.0, 1.0, "", "", "");
			DoQuestCheckDelay("Royal_jackpot_144", 1.5);
		break;

		case "Royal_jackpot_144":
			LAi_ActorTurnToLocator(pchar, "goto", "goto1");
			locCameraResetState();
			locCameraTarget(pchar);
			DoQuestCheckDelay("Royal_jackpot_145", 1.5);
		break;

		case "Royal_jackpot_145":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Spa_Fakel_Deck");
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_146":
			LAi_SetActorType(pchar);
			ChangeShowIntarface();
			locCameraToPos(2.31, 14.5, -0.12, false);
			locCameraTarget(characterFromID("Spa_Fakel_Deck"));
			sld = characterFromID("Mary_Belfler");
			LAi_ActorTurnToLocator(sld, "goto", "goto1");
			LAi_tmpl_ani_PlayAnimation(sld, "Shot", -1.0);
			DoQuestCheckDelay("Royal_jackpot_147", 1.5);
		break;

		case "Royal_jackpot_147":
			sld = CharacterFromID("Mary_Belfler");
			LAi_tmpl_ani_EndAnimation(sld);
			sld = characterFromId("Spa_Fakel_Deck");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Royal_jackpot_148", 1.5);
		break;

		case "Royal_jackpot_148":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			locCameraFromToPos(1.37, 14, -9.4, false, 0.1, 12, -3);
			sld = characterFromId("Mary_Belfler");
			sld.Dialog.CurrentNode = "Royal_jackpot_11";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_149":
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Royal_jackpot_36";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Royal_jackpot_150":
			i = FindLocation("aop_deck2");
			DeleteAttribute(&Locations[i], "models.always.barricade");
			DeleteAttribute(&Locations[i], "box1.items");
			DeleteAttribute(&Locations[i], "box2.items");
			DeleteAttribute(&Locations[i], "box3.items");
			Locations[i].box1.items.jewelry5 = 500;
			Locations[i].box2.items.jewelry17 = 300;
			Locations[i].box2.items.indian8 = 20;
			Locations[i].box3.items.incas_collection = 3;
			Locations[i].box3.items.jewelry4 = 250;
			Locations[i].box3.items.jewelry3 = 250;
			Locations[i].box3.items.jewelry2 = 250;
			Locations[i].box3.items.jewelry1 = 250;
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_275"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("aop_deck2", "rld", "loc0", "Royal_jackpot_151");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 20); // мотаем время
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			DeleteAttribute(&TEV, "StopTimeScale"); // можно ускоряться
			sld = GetCharacter(NPC_GenerateCharacter("Loader_Royal_1", "worker_1", "man", "man", CB_Rank(), SPAIN, 1, true));
			sld.dialog.filename = "Quest\LeBasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Loader_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "aop_deck2", "goto", "goto1");
			sld = GetCharacter(NPC_GenerateCharacter("Loader_Royal_2", "worker_2", "man", "man", CB_Rank(), SPAIN, 1, true));
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "aop_deck2", "goto", "goto2");
			sld = GetCharacter(NPC_GenerateCharacter("Loader_Royal_3", "worker_3", "man", "man", CB_Rank(), SPAIN, 1, true));
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "aop_deck2", "goto", "goto3");
			sld = GetCharacter(NPC_GenerateCharacter("Loader_Royal_4", "worker_4", "man", "man", CB_Rank(), SPAIN, 1, true));
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			ChangeCharacterAddressGroup(sld, "aop_deck2", "goto", "goto4");
			sld = characterFromId("Mishel_le_Bask");
			ChangeCharacterAddressGroup(sld, "aop_deck2", "rld", "loc4");
			sld = characterFromId("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "aop_deck2", "rld", "loc3");
		break;

		case "Royal_jackpot_151":
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			sld = characterFromId("Mary_Belfler");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			sld = characterFromId("Loader_Royal_1");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Royal_jackpot_152":
			sld = characterFromId("Mishel_le_Bask");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_37";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Royal_jackpot_153":
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorRunToLocator(sld, "rld", "aloc4", "Royal_jackpot_153_1", -1);
			sld = characterFromId("Mary_Belfler");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_12";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Royal_jackpot_153_1":
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorTurnToLocator(sld, "rld", "aloc3");
		break;

		case "Royal_jackpot_154":
			sld = characterFromId("Mary_Belfler");
			LAi_ActorRunToLocator(sld, "rld", "aloc7", "Royal_jackpot_155", -1);
		break;

		case "Royal_jackpot_155":
			sld = characterFromId("Mishel_le_Bask");
			LAi_SetStayType(sld);
			AddLandQuestMark_Main(sld, "Royal_jackpot");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_38";
			sld = characterFromId("Mary_Belfler");
			LAi_ActorTurnToLocator(sld, "rld", "aloc1");
		break;

		case "Royal_jackpot_156":
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, characterFromID("Mishel_le_Bask"), "", -1);
			sld = characterFromId("Mary_Belfler");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			sld = characterFromId("Mishel_le_Bask");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Fransua_Olone"), "Royal_jackpot_157", -1);
			sld = characterFromId("Fransua_Olone");
			LAi_ActorFollow(sld, characterFromID("Mishel_le_Bask"), "", -1);
		break;

		case "Royal_jackpot_157":
			QuestMovieUnLockPlayer();

			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Fransua_Olone"));

			sld = CharacterFromID("Fransua_Olone");
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Mishel_le_Bask"));

			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_16"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_10"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_17"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_11"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_18"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_12"));
			AoP_NPCDialogLaunch("Fransua_Olone", "Mishel_le_Bask", "Royal_jackpot_158");
		break;

		case "Royal_jackpot_158":
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetStayType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_8";
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;

		case "Royal_jackpot_160":
			QuestMovieLockPlayer();
			EndBattleLandInterface();

			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1);
			LAi_ActorFollow(pchar, CharacterFromID("Fransua_Olone"), "", -1);

			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorFollow(sld, CharacterFromID("blaze"), "", -1);

			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorFollow(sld, CharacterFromID("blaze"), "", -1);

			DoQuestCheckDelay("Royal_jackpot_161", 4);
		break;

		case "Royal_jackpot_161":
			i = FindLocation("Cabin_Huge_quest");
			Locations[i].QuestlockWeather = "Storm04_add";
			sld = CharacterFromID("Royal_Margarita_Cap");
			sld.lifeday = 0;
			sld = CharacterFromID("Royal_matros");
			sld.lifeday = 0;
			QuestMovieUnLockPlayer(); // окаемки выкл
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_286"), "Reload_To_Location", 0.1, 5.0);
			SetLaunchFrameReloadLocationParam("Cabin_Huge_quest", "reload", "reload1", "Royal_jackpot_162");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 20); // мотаем время
		break;

		case "Royal_jackpot_162":
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Royal_jackpot_40";
			AddLandQuestMark_Main(sld, "Royal_jackpot");
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Cabin_Huge_quest", "sit", "sit0");
			sld = characterFromId("Etien_Marso");
			LAi_CharacterDisableDialog(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_8";
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Cabin_Huge_quest", "sit", "sit1");
		break;

		case "Royal_jackpot_163":
			sld = characterFromId("Mishel_le_Bask");
			LAi_CharacterDisableDialog(sld);
			sld = characterFromId("Etien_Marso");
			LAi_CharacterEnableDialog(sld);
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Royal_jackpot_12";
			QuestPointerToLoc("Cabin_Huge_quest", "reload", "reload1"); // поставить поинт
			pchar.quest.go_aguadilia.win_condition.l1 = "locator";
			pchar.quest.go_aguadilia.win_condition.l1.location = "Cabin_Huge_quest";
			pchar.quest.go_aguadilia.win_condition.l1.locator_group = "reload";
			pchar.quest.go_aguadilia.win_condition.l1.locator = "reload1";
			pchar.quest.go_aguadilia.win_condition = "Royal_jackpot_164";
		break;

		case "Royal_jackpot_164":
			sld = characterFromId("Mary_Belfler");
			RemovePassenger(pchar, sld);
			i = FindLocation("Cabin_Huge_quest");
			DeleteAttribute(&Locations[i], "QuestlockWeather");
			sld = CharacterFromID("Etien_Marso");
			RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
			chrDisableReloadToLocation = false;
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_287"), "Royal_jackpot_165", 0.1, 5.0);
			LaunchFrameForm();
			Whr_UpdateWeather();
			WaitDate("", 0, 0, 5, 2, 20);
			setWDMPointXZ("Shore44"); // корабль в бухту
		break;

		case "Royal_jackpot_165":
			bQuestDisableMapEnter = false;

			Group_DeleteGroup("Royal_Margarita_Group");
			Group_DeleteGroup("Royal_OloneChasers_Group");
			Group_DeleteGroup("Royal_MainEscort_Group");
			Group_DeleteGroup("RoyalJackpot_LeBasque_Group");
			Group_DeleteGroup("RoyalJackpot_Olone_Group");
			Group_DeleteGroup("RoyalJackpot_Marso_Group");

			DeleteAttribute(&questToSeaLoginer, "");
			QuestToSeaLogin_PrepareLoc("PuertoRico", "quest_ships", "quest_ship_11", true);
			QuestToSeaLogin_Launch();

			DoQuestCheckDelay("Royal_jackpot_166", 2);
		break;

		case "Royal_jackpot_166":
			DeleteAttribute(pchar, "questTemp.AoP.Holiday");
			sld = characterFromID("Rimalier");
			if (!IsOfficer(sld))
			{
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			AddMapQuestMark_Major("Tortuga_town", "Royal_jackpot", ""); // метка острова
			sld = characterFromId("Young_Boy_Bask");
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Royal_jackpot_final";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit2");
			sld = characterFromId("Mary_Belfler");
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Royal_jackpot_final";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit3");
			sld = characterFromId("Etien_Marso");
			AddLandQuestMark_Gen(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Royal_jackpot_final";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit4");
			sld = characterFromId("Mishel_le_Bask");
			LAi_CharacterEnableDialog(sld);
			AddLandQuestMark_Main(sld, "Royal_jackpot");
			sld.Dialog.CurrentNode = "Royal_jackpot_41";
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit1");
			LocatorReloadEnterDisable("Bucaneer_Outpost", "reload6_back", false); // открыть дом ле Баска
			i = FindLocation("Bucaneer_outpost");
			Locations[i].models.always.smugglerLairExit = "smugglerLairExit";
			DeleteAttribute(&Locations[i], "models.always.smugglerLairExit.tech");
			DeleteAttribute(&Locations[i], "models.always.smugglerLairExit.lights");
			Locations[i].models.always.locators = "smugglerLairExit_locators";
			Locations[i].models.day.charactersPatch = "smugglerLairExit_patch";
			Locations[i].models.night.charactersPatch = "smugglerLairExit_patch";
			Locations[i].models.always.grassPatch = "smugglerLairExit_grass";
			DeleteAttribute(&TEV, "YoHoMusic");
			bQuestDisableMapEnter = false; // открыть карту
			AddQuestRecord("Royal_jackpot", "8");
		break;

		case "Royal_jackpot_167":
			RemoveMapQuestMark("Tortuga", "Royal_jackpot"); // убрать метку острова
			sld = characterFromId("Mishel_le_Bask");
			LAi_CharacterDisableDialog(sld);
			AddMoneyToCharacter(pchar, 100000);
			SetBuccaneerService(5);
			AoP_BuccaneerStoreMargarita();
			AddQuestRecord("Royal_jackpot", "9");
			ChangeBuccaneerRelation(10.0); // +10 к отношениям с буканьерами
			CloseQuestHeader("Royal_jackpot");
			Achievment_Set(ACH_Royal_jackpot);
			pchar.quest.house_bask_out.win_condition.l1 = "ExitFromLocation";
			pchar.quest.house_bask_out.win_condition.l1.location = pchar.location;
			pchar.quest.house_bask_out.win_condition = "Royal_jackpot_168";
		break;

		case "Royal_jackpot_168":
			DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно ожидать
			pchar.questTemp.MaracaiboSiegeLock = true;
			if (CheckAttribute(&NullCharacter, "Siege.Colony") && NullCharacter.Siege.Colony == "Maracaibo") SiegeClear("");
			LocatorReloadEnterDisable("Bucaneer_Outpost", "reload6_back", true); // закрыть дом ле Баска
			SetTimerCondition("Keys_lagoon_1", 0, 0, 14, false);
		break;

		// шестой финальный квест
		case "Keys_lagoon_1":
			AddQuestRecord("Keys_lagoon", "0");
			i = FindLocation("Bucaneer_outpost_townhall");
			locations[i].models.always.house = "SmallResidence_sovet";
			locations[i].models.always.locators = "SmallResidence_sovet_locators";
			LocatorReloadEnterDisable("Bucaneer_Outpost", "reload6_back", false); // открыть дом ле Баска
			sld = characterFromId("Fransua_Olone");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit5");
			sld = characterFromId("Mishel_le_Bask");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit7");
			sld = characterFromId("Etien_Marso");
			RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
			sld = characterFromId("Mary_Belfler");
			RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
			sld = characterFromId("Young_Boy_Bask");
			RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("Rimalier");
			RemoveLandQuestMark_Gen(sld, "Royal_jackpot");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			for (i = 1; i <= 15; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mass_Officer_" + i, "officer_" + i, "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10), CB_Pistol() + rand(10), "blade10", "pistol2", 30);
				CB_Perks(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_SetCitizenType(sld);
				ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "goto", "goto" + (10 + i));
			}
			for (i = 1; i <= 15; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Mass_Officer_Mush_" + i, "mush_ctz_" + i, "man", "mushketer", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_SetCitizenType(sld);
				ChangeCharacterAddressGroup(sld, "Bucaneer_outpost", "goto", "goto" + (10 + i));
			}
			pchar.quest.Return_Bucaneer_Outpost.win_condition.l1 = "location";
			pchar.quest.Return_Bucaneer_Outpost.win_condition.l1.location = "Bucaneer_Outpost";
			pchar.quest.Return_Bucaneer_Outpost.win_condition = "Keys_lagoon_2";
		break;

		case "Keys_lagoon_2":
			AddQuestRecord("Keys_lagoon", "1");
			pchar.quest.Return_Bucaneer_Outpost_2.win_condition.l1 = "location";
			pchar.quest.Return_Bucaneer_Outpost_2.win_condition.l1.location = "Bucaneer_Outpost_townhall";
			pchar.quest.Return_Bucaneer_Outpost_2.win_condition = "Keys_lagoon_3";
		break;

		case "Keys_lagoon_3":
			bDisableCharacterMenu = true; // Ф2 отключить
			TEV.StopTimeScale = true; // запрет ускорения
			chrDisableReloadToLocation = true; // закрыть локацию
			DoQuestCheckDelay("Keys_lagoon_4", 0.1);
		break;

		case "Keys_lagoon_4":
			ChangeShowIntarface();
			locCameraToPos(-1.23, 2.24, -2.22, false);
			locCameraTarget(characterFromID("Mishel_le_Bask"));
			LAi_SetActorType(pchar);
			sld = characterFromId("Mishel_le_Bask");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_1";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_5":
			locCameraToPos(-1.23, 2.24, -2.22, false);
			locCameraTarget(characterFromID("Mishel_le_Bask"));
			LAi_FadeEx(1.0, 2.0, 1.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_6", 2.5);
		break;

		case "Keys_lagoon_6":
			DoQuestFunctionDelay("Keys_lagoon_camera_1", 0.0);
			LAi_ActorSetSitMode(pchar);
			ChangeCharacterAddressGroup(pchar, "Bucaneer_outpost_townhall", "sit", "sit6");
			sld = CharacterFromID("Rimalier");
			LAi_CharacterEnableDialog(sld);
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit2");
			DoQuestCheckDelay("Keys_lagoon_7", 2);
		break;

		case "Keys_lagoon_7":
			sld = characterFromID("Rimalier");
			sld.dialog.filename = "Quest\Lebasque\Rimalier_dialog.c";
			sld.Dialog.CurrentNode = "Keys_lagoon_1";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_8":
			sld = characterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_2";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_9":
			sld = characterFromID("Fransua_Olone");
			sld.Dialog.CurrentNode = "Keys_lagoon_1";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_10":
			sld = CharacterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_4";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_11":
			sld = characterFromID("Mary_Belfler");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_1";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_12":
			sld = characterFromID("Etien_Marso");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_1";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_13":
			sld = characterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_5";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_14":
			ChangeShowIntarface();
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_19"));
			AoP_NPCDialogLaunch("Fransua_Olone", "Mary_Belfler", "Keys_lagoon_14_1");
		break;

		case "Keys_lagoon_14_1":
			ChangeShowIntarface();
			sld = CharacterFromID("Mary_Belfler");
			sld.Dialog.CurrentNode = "Keys_lagoon_1_1";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_15":
			sld = characterFromID("Mary_Belfler");
			sld.Dialog.CurrentNode = "Keys_lagoon_2";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_16":
			sld = characterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_7";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_17":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_20"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_13"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_21"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_14"));
			AoP_NPCDialogLaunch("Fransua_Olone", "Mishel_le_Bask", "Keys_lagoon_18");
		break;

		case "Keys_lagoon_18":
			ChangeShowIntarface();
			sld = characterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_9";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_19":
			LAi_FadeEx(1.0, 2.0, 1.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_20", 2);
		break;

		case "Keys_lagoon_20":
			locCameraResetState();
			locCameraFromToPos(-1.214, 2.885, 2.290, true, -2.390, 1.1, 3.949);
			DoQuestCheckDelay("Keys_lagoon_21", 4);
		break;

		case "Keys_lagoon_21":
			PlayVoice("Types\Parrot0.mp3");
			DoQuestCheckDelay("Keys_lagoon_22", 1);
		break;

		case "Keys_lagoon_22":
			LAi_FadeEx(1.0, 1.0, 1.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_23", 1.5);
		break;

		case "Keys_lagoon_23":
			DeleteAttribute(&TEV, "StopTimeScale");
			bDisableCharacterMenu = false; // Ф2 включить
			LAi_SetPlayerType(pchar);
			DoQuestReloadToLocation("Bucaneer_Outpost", "reload", "reload6_back", "Keys_lagoon_24");
			sld = CharacterFromID("Rimalier");
			if (IsOfficer(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.CurrentNode = "Hired";
				sld.Dialog.TempNode = "Hired";
			}
			else
			{
				AddPassenger(pchar, sld, false);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto8");
			}
			sld = characterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			AddPassenger(pchar, sld, false);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost", "goto", "goto8");
		break;

		case "Keys_lagoon_24":
			chrDisableReloadToLocation = false; // открыть локацию
			AddMapQuestMark_Major("Aruba", "Keys_lagoon", ""); // метка острова
			AddQuestRecord("Keys_lagoon", "2");
			sld = characterFromID("Mary_Belfler");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", -1);
			sld = characterFromID("Rimalier");
			if (!IsOfficer(sld))
			{
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", -1);
			}
			pchar.quest.go_Aruba.win_condition.l1 = "location";
			pchar.quest.go_Aruba.win_condition.l1.location = "Aruba";
			pchar.quest.go_Aruba.win_condition = "Keys_lagoon_25";
		break;

		case "Keys_lagoon_25":
			n = FindLocation("Aruba_Outpost"); // TODO УДАЛИТЬ ОБЕ СТРОЧКИ!
			Locations[n].models.always.jungle.tech = "DLightModel";
			DeleteAttribute(&Locations[n], "models.always.rope");
			bQuestDisableMapEnter = true; // закрыть карту
			Island_SetReloadEnableGlobal("Aruba", false);
			DoQuestCheckDelay("Off_Interface", 0.2);
			DoQuestCheckDelay("Keys_lagoon_26", 3);
		break;

		case "Keys_lagoon_26":
			SetCharacterShipLocation(pchar, "Shore67"); // корабль в бухту
			DoQuestReloadToLocation("Shore67", "reload", "sea", "Keys_lagoon_27");
			sld = GetCharacter(NPC_GenerateCharacter("Indian_Chel", "Miskito_6", "man", "man", CB_Rank(), PIRATE, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10), CB_Pistol() + rand(10), "spear1", "", 30);
			CB_Perks(sld);
			sld.name = GetIndianName(MAN);
			sld.lastname = "";
			sld.dialog.filename = "Quest\LeBasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Indian_1";
			sld.HideNationIcon = true;
			LAi_CharacterDisableDialog(sld);
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Shore67", "goto", "goto10");
			sld = GetCharacter(NPC_GenerateCharacter("Alone_Bucaneer", "mush_ctz_2", "man", "mushketer", CB_Rank(), FRANCE, -1, true));
			sld.Buccaneer = true;
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
			CB_Perks(sld);
			sld.dialog.filename = "Quest\LeBasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Alone_Bucaneer_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore67", "goto", "goto3");
			sld = GetCharacter(NPC_GenerateCharacter("Alone_Bucaneer_2", "mush_ctz_6", "man", "mushketer", CB_Rank(), FRANCE, -1, true));
			sld.Buccaneer = true;
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore67", "goto", "goto3");
			sld = characterFromID("Mary_Belfler");
			LAi_SetFreeFighter(sld);
			sld = characterFromID("Rimalier");
			if (!IsOfficer(sld))
			{
				LAi_SetFreeFighter(sld);
			}
		break;

		case "Keys_lagoon_27":
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = characterFromID("Indian_Chel");
			CharacterTurnByChr(sld, pchar);
			sld = characterFromID("Alone_Bucaneer_2");
			LAi_ActorFollow(sld, characterFromID("Alone_Bucaneer"), "", -1);
			sld = characterFromID("Alone_Bucaneer");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_28":
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			LAi_SetActorType(pchar);
			sld = characterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Alone_Bucaneer"), "Keys_lagoon_29", -1);
			sld = characterFromID("Alone_Bucaneer_2");
			LAi_ActorRunToLocator(sld, "goto", "goto9", "", -1);
		break;

		case "Keys_lagoon_29":
			QuestMovieUnLockPlayer(); // окаемки выкл
			EndBattleLandInterface(); // откл интерфейс
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mary_Belfler", StringFromKey("LeBasque_Mary_Belfler_6"));
AoP_NPCDialogAddLine("Alone_Bucaneer", StringFromKey("LeBasque_Alone_Bucaneer_1"));
			AoP_NPCDialogAddLine("Mary_Belfler", StringFromKey("LeBasque_Mary_Belfler_7"));
AoP_NPCDialogAddLine("Alone_Bucaneer", StringFromKey("LeBasque_Alone_Bucaneer_2"));
			AoP_NPCDialogLaunch("Alone_Bucaneer", "Mary_Belfler", "Keys_lagoon_30");
		break;

		case "Keys_lagoon_30":
			LAi_SetPlayerType(pchar);
			sld = characterFromID("Alone_Bucaneer");
			sld.Dialog.CurrentNode = "Alone_Bucaneer_4";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_31":
			StartBattleLandInterface(); // вкл интерфейс
			sld = characterFromID("Alone_Bucaneer");
			LAi_ActorTurnToCharacter(sld, characterFromID("Indian_Chel"));
			sld = characterFromID("Indian_Chel");
			LAi_CharacterEnableDialog(sld);
			AddLandQuestmark_Main(sld, "Keys_lagoon");
		break;

		case "Keys_lagoon_32":
			sld = characterFromID("Alone_Bucaneer");
			sld.Dialog.CurrentNode = "Alone_Bucaneer_6";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_33":
			if (CheckCharacterItem(pchar, "potion4"))
			{
				pchar.questTemp.AoP.ArubaIndianHealedByPlayer = true;
				AddCharacterExpToSkill(PChar, SKILL_Leadership, 50);
				notification(StringFromKey("InfoMessages_225"), SKILL_Leadership);
				LAi_SetActorType(pchar);
				sld = CharacterFromID("Indian_Chel");
				sld.dialog.currentnode = "Indian_2";
				LAi_ActorDialogNow(pchar, sld, "", -1);
			}
			else
			{
				QuestMovieLockPlayer(); // окаемки вкл
				EndBattleLandInterface(); // откл интерфейс
				pchar.questTemp.AoP.ArubaIndianHealedByPlayer = false;
				LAi_SetActorType(pchar);
				sld = CharacterFromID("Mary_Belfler");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromID("blaze"), "Keys_lagoon_33_1", -1);
			}
		break;

		case "Keys_lagoon_33_1":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Mary_Belfler");
			sld.dialog.currentnode = "Keys_lagoon_4";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_34":
			PlaySound("Quest\LeBask\Bask8.mp3");
			LAi_Fade("Keys_lagoon_35", "");
		break;

		case "Keys_lagoon_35":
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Indian_Chel");
			sld.dialog.currentnode = "Indian_3";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_36":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Alone_Bucaneer");
			sld.dialog.currentnode = "Alone_Bucaneer_7";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_37":
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_275"), "Keys_lagoon_38", 0.1, 5.0);
			LaunchFrameForm();
			Whr_UpdateWeather();
			WaitDate("", 0, 0, 0, 0, 20);
			sld = CharacterFromID("Alone_Bucaneer_2");
			ChangeCharacterAddressGroup(sld, "Shore67", "goto", "goto8");
		break;

		case "Keys_lagoon_38":
			sld = CharacterFromID("Indian_Chel");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("Alone_Bucaneer_2");
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Alone_Bucaneer_8";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_39":
			AddQuestRecord("Keys_lagoon", "3");
			sld = CharacterFromID("Alone_Bucaneer");
			AddLandQuestmark_Main(sld, "Keys_lagoon");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Aruba_Jungle_03", "monsters", "monster3", "Keys_lagoon_40", -1);
			QuestPointerToLoc("Shore67", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Aruba_Jungle_03", "reload", "reload3_back"); // поставить поинт
			sld = CharacterFromID("Mary_Belfler");
			sld.Dialog.CurrentNode = "Keys_lagoon_neitral";
			LAi_SetFreeFighter(sld);
			sld = characterFromID("Rimalier");
			if (!IsOfficer(sld))
			{
				sld.Dialog.CurrentNode = "Keys_lagoon_neitral";
			}
		break;

		case "Keys_lagoon_40":
			chrDisableReloadToLocation = false; // открыть локацию
			string locators_blodd;
			n = FindLocation("Aruba_Jungle_03"); // TODO если миграция, то удалить.
			DeleteAttribute(&Locations[n], "models.always.rope"); // TODO если миграция, то удалить.
			Locations[n].models.always.spa_soldiers = "Jungle14_Body";
			Locations[n].models.always.spa_soldiers.tech = "DLightModel";
			Locations[n].models.always.spa_blood = "Jungle14_blood";
			Locations[n].models.always.spa_blood.tech = "DLightModel";
			Locations[n].models.always.locators = "jungle14_locators_body";
			Locations[n].models.always.grassPatch = "jungle14_grass_body";
			pchar.quest.go_Aruba_outpost.win_condition.l1 = "location";
			pchar.quest.go_Aruba_outpost.win_condition.l1.location = "Aruba_Jungle_03";
			pchar.quest.go_Aruba_outpost.win_condition = "Keys_lagoon_41";
		break;

		case "Keys_lagoon_41":
			sld = CharacterFromID("Alone_Bucaneer");
			LAi_ActorRunToLocation(sld, "reload", "reload3_back", "Aruba_outpost", "goto", "goto13", "Keys_lagoon_42", -1);
			DoQuestCheckDelay("Keys_lagoon_41_1", 8.5);
		break;

		case "Keys_lagoon_41_1":
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Rimalier"));
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			sld = characterFromId("Rimalier");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("blaze"), "Keys_lagoon_41_2", -1);
		break;

		case "Keys_lagoon_41_2":
			LAi_SetPlayerType(pchar);
			StartBattleLandInterface(); // вкл интерфейс
			QuestMovieUnLockPlayer(); // окаемки выкл
			sld = characterFromId("Rimalier");
			sld.Dialog.CurrentNode = "Keys_lagoon_2";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_42":
			sld = CharacterFromID("Alone_Bucaneer");
			LAi_SetStayType(sld);
			sld.Dialog.CurrentNode = "Alone_Bucaneer_9";
			sld.talker = 10;
			sld = GetCharacter(NPC_GenerateCharacter("Daniel_Monbar", "Daniel_Montbars", "man", "man", CB_Rank(), FRANCE, -1, true));
			sld.Buccaneer = true;
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10), CB_Pistol() + rand(10), "blade30", "pistol3", 30);
			AddLandQuestmark_Main(sld, "Keys_lagoon");
			CB_Perks(sld);
			sld.name = FindPersonalName("Daniel_Monbar_name");
			sld.lastname = FindPersonalName("Daniel_Monbar_lastname");
			sld.dialog.filename = "Quest\LeBasque\Monbar_dialog.c";
			sld.Dialog.CurrentNode = "Monbar_1";
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_Outpost", "quest", "quest5");
		break;

		case "Keys_lagoon_43":
			DoQuestFunctionDelay("CheckMontbarsDistance", 0.3);
		break;

		case "Keys_lagoon_44":
			sld = characterFromId("Daniel_Monbar");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Ground_StandUp", "", -1);
			DoQuestCheckDelay("Keys_lagoon_45", 4);
		break;

		case "Keys_lagoon_45":
			sld = characterFromId("Daniel_Monbar");
			LAi_SetStayType(sld);
		break;

		case "Keys_lagoon_46":
			AoP_OfficersSetCitizen();
			LAi_SetActorType(pchar);
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			LAi_FadeEx(1.0, 1.0, 1.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_47", 1.5);
		break;

		case "Keys_lagoon_47":
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			TEV.StopTimeScale = true; // запрет ускорения
			sld = characterFromId("Indian_Chel");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_outpost", "goto", "goto12");
			sld = characterFromId("Daniel_Monbar");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_outpost", "quest", "quest_monbar");
			locCameraFlyToPositionLookToPoint(11.578, 5.172, 8.344, -21.217, 3.729, 4.796, -21.688, 3.235, -6.317, -1.0, 1000);
			sld = characterFromId("Mary_Belfler");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Indian_Chel"));
			sld = characterFromId("Rimalier");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Indian_Chel"));
			LAi_ActorTurnToCharacter(pchar, characterFromID("Indian_Chel"));
			DoQuestCheckDelay("Keys_lagoon_48", 1);
			DoQuestCheckDelay("Keys_lagoon_49", 5);
		break;

		case "Keys_lagoon_48":
			sld = characterFromId("Daniel_Monbar");
			CharacterTurnByChr(sld, characterFromID("Indian_Chel"));
			sld = characterFromId("Indian_Chel");
			LAi_ActorRunToLocator(sld, "quest", "quest_indian", "", -1);
		break;

		case "Keys_lagoon_49":
			LAi_FadeEx(1.0, 1.0, 1.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_50", 1.5);
		break;

		case "Keys_lagoon_50":
			locCameraResetState();
			sld = characterFromId("Indian_Chel");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_outpost", "quest", "quest_indian");
			LAi_ActorTurnToCharacter(sld, characterFromID("Daniel_Monbar"));
			locCameraFromToPos(-21.217, 3.729, 4.796, true, -21.688, 1.7, -6.317);
			DoQuestCheckDelay("Keys_lagoon_51", 2.5);
		break;

		case "Keys_lagoon_51":
			sld = characterFromId("Daniel_Monbar");
			CharacterTurnByChr(sld, characterFromID("Indian_Chel"));
			ChangeShowIntarface();
			QuestMovieUnLockPlayer(); // окаемки выкл
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Indian_Chel", StringFromKey("LeBasque_Indian_Chel_1", GetFirstName(characterFromID("Indian_Chel"))));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_1"));
			AoP_NPCDialogAddLine("Indian_Chel", StringFromKey("LeBasque_Indian_Chel_2"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_2"));
			AoP_NPCDialogAddLine("Indian_Chel", StringFromKey("LeBasque_Indian_Chel_3", GetFirstName(characterFromID("Indian_Chel"))));
			AoP_NPCDialogLaunch("Indian_Chel", "Daniel_Monbar", "Keys_lagoon_52");
		break;

		case "Keys_lagoon_52":
			QuestMovieLockPlayer(); // окаемки вкл
			LAi_FadeEx(1.0, 1.0, 1.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_53", 1.5);
		break;

		case "Keys_lagoon_53":
			locCameraResetState();
			sld = characterFromId("Daniel_Monbar");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("blaze"), "Keys_lagoon_54", -1);
			ChangeCharacterAddressGroup(pchar, "Aruba_outpost", "quest", "quest5");
			LAi_ActorTurnToLocator(pchar, "quest", "quest_monbar");
			sld = CharacterFromID("Indian_Chel");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			sld = characterFromId("Mary_Belfler");
			MakeUnpushable(sld, false);
			LAi_SetFreeFighter(sld);
			sld = CharacterFromID("Rimalier");
			if (IsOfficer(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.CurrentNode = "Hired";
				sld.Dialog.TempNode = "Hired";
			}
			else
			{
				LAi_SetFreeFighter(sld);
				sld.Dialog.CurrentNode = "Keys_lagoon_neitral";
			}
		break;

		case "Keys_lagoon_54":
			LAi_SetPlayerType(pchar);
			StartBattleLandInterface(); // вкл интерфейс
			QuestMovieUnLockPlayer(); // окаемки выкл
			sld = characterFromId("Daniel_Monbar");
			sld.Dialog.CurrentNode = "Monbar_11";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_55":
			AoP_OfficersRestore();
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			DeleteAttribute(&TEV, "StopTimeScale"); // можно ускоряться
			pchar.questTemp.AoP.ArubaRightCorpse = "item_body_4";
			QuestPointerDelLoc("Shore67", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Aruba_Jungle_03", "reload", "reload3_back"); // удалить поинт
			QuestPointerToLoc("Aruba_outpost", "reload", "reload1_back"); // поставить поинт
			for (i = 1; i <= 13; i++)
			{
				QuestPointerToLoc("Aruba_Jungle_03", "quest", "item_body_" + i); // поставить поинт
			}
			AddQuestRecord("Keys_lagoon", "4");
			pchar.quest.Aruba_Jungle_03_search.win_condition.l1 = "location";
			pchar.quest.Aruba_Jungle_03_search.win_condition.l1.location = "Aruba_Jungle_03";
			pchar.quest.Aruba_Jungle_03_search.function = "AoP_ArubaFakeCorpsesAfterLoad";
			pchar.quest.ArubaLetterFound.win_condition.l1 = "item";
			pchar.quest.ArubaLetterFound.win_condition.l1.item = "letter_Aruba";
			pchar.quest.ArubaLetterFound.win_condition = "Keys_lagoon_57";;
		break;

		case "Keys_lagoon_55_1":
			sTemp = pchar.questTemp.AoP.ArubaLastSearchedCorpse;
			if (sTemp != pchar.questTemp.AoP.ArubaRightCorpse)
			{
				QuestPointerDelLoc("Aruba_Jungle_03", "quest", sTemp);
			}
		break;

		case "Keys_lagoon_57":
			for (i = 1; i <= 13; i++)
			{
				QuestPointerDelLoc("Aruba_Jungle_03", "quest", "item_body_" + i);
			}
			chrDisableReloadToLocation = false; // открыть локацию
			AddQuestRecord("Keys_lagoon", "5");
			pchar.questTemp.AoP.ArubaCommanderFound = true;
			QuestPointerDelLoc("Aruba_outpost", "reload", "reload1_back"); // удалить поинт
			QuestPointerToLoc("Aruba_Jungle_03", "reload", "reload3_back"); // поставить поинт
			sld = characterFromId("Daniel_Monbar");
			AddLandQuestmark_Main(sld, "Keys_lagoon");
			sld.Dialog.CurrentNode = "Monbar_18";
		break;

		case "Keys_lagoon_58":
			locations[FindLocation("Aruba_Jungle_01")].DisableEncounters = true;
			AddQuestRecord("Keys_lagoon", "6");
			QuestPointerDelLoc("Aruba_Jungle_03", "reload", "reload3_back"); // удалить поинт
			QuestPointerToLoc("Aruba_outpost", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Aruba_Jungle_03", "reload", "reload1_back"); // поставить поинт
			pchar.quest.Aruba_Jungle_01_war.win_condition.l1 = "location";
			pchar.quest.Aruba_Jungle_01_war.win_condition.l1.location = "Aruba_Jungle_01";
			pchar.quest.Aruba_Jungle_01_war.win_condition = "Keys_lagoon_59";
		break;

		case "Keys_lagoon_59":
			chrDisableReloadToLocation = true; // закрыть локацию
			DoQuestCheckDelay("Keys_lagoon_60", 2);
		break;

		case "Keys_lagoon_60":
			for (i = 1; i < 4; i++)
			{
			iOfficer = GetOfficersIndex(pchar, i);
			if (iOfficer < 0) continue;

			Characters[iOfficer].location = "none";
			Characters[iOfficer].location.group = "";
			Characters[iOfficer].location.locator = "";
			}
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_288"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("Aruba_Jungle_01", "goto", "goto_gg", "Keys_lagoon_61");
			Whr_UpdateWeather();
			LaunchFrameForm();
			SetCurrentTime(22, 44);
		break;

		case "Keys_lagoon_61":
			LAi_SetActorType(pchar);
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			TEV.StopTimeScale = true; // запрет ускорения
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			sld = characterFromID("Rimalier");
			ChangeCharacterAddressGroup(sld, "Aruba_Jungle_01", "goto", "goto_rimalie");
			sld = characterFromID("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "Aruba_Jungle_01", "goto", "goto_mary");
			pchar.questTemp.AoP.ArubaSpanishSpawnCount = 0;
			locCameraFlyToPositionLookToPoint(19.725, 31.605, -81.252, 39.065, 31.450, -63.482, 14.653, 30.996, -89.569, -1.0, 1400);
			DoQuestCheckDelay("Keys_lagoon_62", 5.5);
		break;

		case "Keys_lagoon_62":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "Keys_lagoon_camera_3", "");
			sld = CharacterFromId("Daniel_Monbar");
			sld.model = "Daniel_Montbars_mush";
			sld.model.animation = "mushketer";
			SetNewModelToChar(sld);
			SetCharacterPerk(sld, "MusketsTraining");
			SetCharacterPerk(sld, "GunProfessional");
			sld.MushketType = "mortar";
			sld.MushketBulletType = "grenade";
			GiveItem2Character(sld, "mortar");
			EquipCharacterByItem(sld, "mortar");
			TakeNItems(sld, "grenade", 5);
			TakeNItems(sld, "petard", 5);
			LAi_SetCharacterUseBullet(sld, MUSKET_ITEM_TYPE, "grenade");
			sld.MusketOutfit = true;
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_Jungle_01", "goto", "goto_monbar");
			LAi_ActorTurnToLocator(sld, "goto", "goto15");
			for (i = 1; i <= 7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bucaneers_Aruba_" + i, "mush_ctz_" + i, "man", "mushketer", CB_Rank(), PIRATE, 1, true));
				sld.Buccaneer = true;
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Aruba_Jungle_01", "goto", "goto14");
			}
		break;

		case "Keys_lagoon_63":
			locCameraResetState();
			locCameraFromToPos(61.980, 31.850, -84.779, false, 49.328, 30.937, -65.809);
			LAi_SetPlayerType(pchar);
			DoQuestCheckDelay("Keys_lagoon_64", 3.5);
		break;

		case "Keys_lagoon_64":
			PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
			SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
			CreateLocationParticlesXZ("ShipExplode", "goto", "goto_boom", 0, 0, 0, "");
			sld = characterFromId("ArubaSpanish_11");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			sld = characterFromId("ArubaSpanish_12");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			sld = characterFromId("ArubaSpanish_13");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			sld = characterFromId("ArubaSpanish_14");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Keys_lagoon_65", 2.5);
			for (i = 0; i <= 13; i++)
			{
				sld = characterFromId("ArubaSpanish_" + i);
				LAi_SetStayType(sld);
			}
		break;

		case "Keys_lagoon_65":
			locCameraFromToPos(41.741, 30.120, -29.352, false, 43.399, 27.229, -19.862);
			DoQuestCheckDelay("Keys_lagoon_66", 2.5);
		break;

		case "Keys_lagoon_66":
			StartBattleLandInterface(); // вкл интерфейс
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Daniel_Monbar");
			sld.Dialog.CurrentNode = "Monbar_27";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_67":
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			DeleteAttribute(&TEV, "StopTimeScale"); // можно ускоряться
			//locCameraResetState();
			locCameraFollowEx(true);
			for (i = 1; i <= 7; i++)
			{
				sld = CharacterFromID("Bucaneers_Aruba_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i = 0; i <= 10; i++)
			{
				sld = CharacterFromID("ArubaSpanish_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Spa_Jungle_Keys");
			}
			sld = characterFromId("Daniel_Monbar");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = characterFromId("ArubaSpanish_Officer");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "Spa_Jungle_Keys");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Spa_Jungle_Keys", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Spa_Jungle_Keys", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Spa_Jungle_Keys", "Keys_lagoon_68");
		break;

		case "Keys_lagoon_68":
			for (i = 1; i <= 7; i++)
			{
				int Live_Team_5 = GetCharacterIndex("Bucaneers_Aruba_" + i);
				if (Live_Team_5 != -1)
				{
					sld = &characters[Live_Team_5];
					if (!LAi_IsDead(sld))
					{
						LAi_SetCitizenType(sld);
						LAi_CharacterDisableDialog(sld);
					}
				}
			}
			LAi_group_Delete("Spa_Jungle_Keys");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = characterFromId("Daniel_Monbar");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Monbar_28";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_69":
			QuestPointerToLoc("Aruba_Jungle_02", "reload", "reload3_back"); // поставить поинт
			QuestPointerToLoc("Aruba_Jungle_01", "reload", "reload1_back"); // поставить поинт
			sld = characterFromId("Daniel_Monbar");
			MakeUnpushable(sld, true);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Aruba_IndianVillage", "goto", "goto17", "Keys_lagoon_69_1", -1);
			AddQuestRecord("Keys_lagoon", "7");
			sld = GetCharacter(NPC_GenerateCharacter("Yamai", "Canib", "man", "man", CB_Rank(), PIRATE, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10), CB_Pistol() + rand(10), "maquahuitl", "", 30);
			AddLandQuestmark_Main(sld, "Keys_lagoon");
			CB_Perks(sld);
			sld.HideNationIcon = true;
			sld.name = FindPersonalName("Yamai_name");
			sld.lastname = "";
			sld.greeting = "indiano";
			sld.dialog.filename = "Quest\LeBasque\Indian_dialog.c";
			sld.Dialog.CurrentNode = "Yamai_1";
			MakeUnpushable(sld, true);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_IndianVillage", "quest", "teleport1");
			string sWeapon;

			for (i = 0; i < 5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("ArubaIndianGuard_" + i, "miskito_" + (1 + rand(5)), "man", "man", CB_Rank(), PIRATE, -1, true));

				switch (rand(2))
				{
					case 0: sWeapon = "spear1"; break;
					case 1: sWeapon = "topor5"; break;
					case 2: sWeapon = "topor4"; break;
				}

				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10), CB_Pistol(), sWeapon, "", 30);
				CB_Perks(sld);
				sld.dialog.Filename = "ArubaIndian_dialog.c";
				sld.dialog.currentnode = "IndianMan";
				sld.indian = "1";
				sld.name = GetIndianName(MAN);
				sld.lastname = "";
				sld.greeting = "indiano";

				ChangeCharacterAddressGroup(sld, "Aruba_IndianVillage", "goto", "goto" + (5 + i));
				LAi_SetWarriorType(sld);
			}
		break;

		case "Keys_lagoon_69_1":
			chrDisableReloadToLocation = false; // открыть локацию
			pchar.quest.aruba_indianvillage_talk.win_condition.l1 = "location";
			pchar.quest.aruba_indianvillage_talk.win_condition.l1.location = "Aruba_IndianVillage";
			pchar.quest.aruba_indianvillage_talk.win_condition = "Keys_lagoon_70";
		break;

		case "Keys_lagoon_70":
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = characterFromId("Daniel_Monbar");
			LAi_ActorTurnToCharacter(sld, characterFromID("Yamai"));
			sld = characterFromId("Yamai");
			LAi_ActorTurnToCharacter(sld, characterFromID("Daniel_Monbar"));
			DoQuestFunctionDelay("CheckYamaiDistance", 0.3);
		break;

		case "Keys_lagoon_71":
			sld = characterFromId("Yamai");
			RemoveLandQuestmark_Main(sld, "Keys_lagoon");
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Yamai", StringFromKey("LeBasque_Yamai_1"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_3"));
			AoP_NPCDialogAddLine("Yamai", StringFromKey("LeBasque_Yamai_2"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_4"));
			AoP_NPCDialogAddLine("Yamai", StringFromKey("LeBasque_Yamai_3"));
			AoP_NPCDialogAddLine("Daniel_Monbar", GetSexPhrase(StringFromKey("LeBasque_Daniel_Monbar_5_m", GetFullName(pchar)), StringFromKey("LeBasque_Daniel_Monbar_5_f", GetFullName(pchar))));
			AoP_NPCDialogAddLine("Yamai", StringFromKey("LeBasque_Yamai_4", GetFullName(pchar)));
			AoP_NPCDialogAddLine("Blaze", StringFromKey("LeBasque_Blaze_1"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_6"));
			AoP_NPCDialogAddLine("Yamai", StringFromKey("LeBasque_Yamai_5", GetFullName(pchar)));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_7"));
			AoP_NPCDialogAddLine("Yamai", StringFromKey("LeBasque_Yamai_6"));
			AoP_NPCDialogLaunch("Daniel_Monbar", "Yamai", "Keys_lagoon_72");
		break;

		case "Keys_lagoon_72":
			sld = characterFromId("Daniel_Monbar");
			sld.Dialog.CurrentNode = "Monbar_31";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_73":
			QuestPointerDelLoc("Aruba_outpost", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Aruba_Jungle_03", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Aruba_Jungle_02", "reload", "reload3_back"); // удалить поинт
			QuestPointerDelLoc("Aruba_Jungle_01", "reload", "reload1_back"); // удалить поинт
			QuestPointerToLoc("Aruba_IndianVillage", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Aruba_Jungle_02", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("Aruba_Jungle_01", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("Aruba_Jungle_03", "reload", "reload3_back"); // поставить поинт
			AddQuestRecord("Keys_lagoon", "8");
			sld = characterFromId("Yamai");
			AddLandQuestMark_Gen(sld, "Keys_lagoon");
			LAi_SetCitizenType(sld);
			sld = characterFromId("Daniel_Monbar");
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "Aruba_outpost", "goto", "goto11", "Keys_lagoon_73_1", -1);
			for (i = 1; i <= 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bucaneers_Aruba_Outpost_" + i, "mush_ctz_" + i, "man", "mushketer", CB_Rank(), PIRATE, 2, true));
				sld.Buccaneer = true;
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Aruba_Outpost", "goto", "goto9");
			}
			for (i = 1; i <= 5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bucaneers_Aruba_Outpost_" + (10 + i), "mush_ctz_" + (10 + i), "man", "mushketer", CB_Rank(), PIRATE, -1, true));
				sld.Buccaneer = true;
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Aruba_Outpost", "goto", "goto10");
			}
		break;

		case "Keys_lagoon_73_1":
			chrDisableReloadToLocation = false; // открыть локацию
			pchar.quest.Aruba_Outpost_battle.win_condition.l1 = "location";
			pchar.quest.Aruba_Outpost_battle.win_condition.l1.location = "Aruba_outpost";
			pchar.quest.Aruba_Outpost_battle.win_condition = "Keys_lagoon_74";
		break;

		case "Keys_lagoon_74":
			for (i = 1; i <= 15; i++)
			{
				sld = characterFromId("Bucaneers_Aruba_Outpost_" + i);
				LAi_ActorFollow(sld, characterFromID("Daniel_Monbar"), "", -1);
			}
			sld = characterFromId("Daniel_Monbar");
			LAi_SetStayType(sld);
			sld.Dialog.CurrentNode = "Monbar_33";
			AddLandQuestMark_Main(sld, "Keys_lagoon");
		break;

		case "Keys_lagoon_75":
			sld = characterFromId("Daniel_Monbar");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			QuestPointerToLoc("Aruba_outpost", "reload", "reload2_back"); // поставить поинт
			locations[FindLocation("Aruba_deadlock")].DisableEncounters = true;
			locations[FindLocation("Aruba_deadlock")].locators_radius.goto.goto_rimalier = 15;
			pchar.quest.Aruba_deadlock_battle.win_condition.l1 = "location";
			pchar.quest.Aruba_deadlock_battle.win_condition.l1.location = "Aruba_deadlock";
			pchar.quest.Aruba_deadlock_battle.win_condition = "Keys_lagoon_76";
		break;

		case "Keys_lagoon_76":
			TEV.StopTimeScale = true; // запрет ускорения
			chrDisableReloadToLocation = true; // закрыть локацию
			for (i = 1; i <= 15; i++)
			{
				sld = characterFromId("Bucaneers_Aruba_Outpost_" + i);
				ChangeCharacterAddressGroup(sld, "Aruba_deadlock", "reload", "reload1_back");
			}
			sld = characterFromId("Daniel_Monbar");
			ChangeCharacterAddressGroup(sld, "Aruba_deadlock", "reload", "reload1_back");
			QuestPointerToLoc("Aruba_deadlock", "reload", "reload2_back"); // поставить поинт
			sld = GetCharacter(NPC_GenerateCharacter("Spain_Dozor", "sold_spa_5", "man", "man", CB_Rank(), SPAIN, 1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
			CB_Perks(sld);
			sld.dialog.filename = "Quest\LeBasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Dozor";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_deadlock", "goto", "goto_dozor");
			pchar.quest.alarm_jugle.win_condition.l1 = "locator";
			pchar.quest.alarm_jugle.win_condition.l1.location = "Aruba_deadlock";
			pchar.quest.alarm_jugle.win_condition.l1.locator_group = "goto";
			pchar.quest.alarm_jugle.win_condition.l1.locator = "goto_rimalier";
			pchar.quest.alarm_jugle.win_condition = "Keys_lagoon_77";
		break;

		case "Keys_lagoon_77":
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			LAi_SetActorType(pchar);
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			QuestPointerDelLoc("Aruba_deadlock", "reload", "reload2_back"); // удалить поинт
			locCameraFlyToPositionLookToPoint(-2.322, 3.061, -32.401, 3.686, 11.981, 10.252, 4.862, 14.366, 17.987, -1.0, 300);
			pchar.FuncCameraFly = "Keys_lagoon_camera_5";
		break;

		case "Keys_lagoon_78":
			EndBattleLandInterface(); // откл интерфейс
			QuestMovieLockPlayer(); // окаемки вкл
			locCameraFromToPosEx(3.686, 11.981, 10.252, true, 4.862, 14.366, 17.987, false);
			PlaySound("People Fight\MusketFire.wav");
			sld = characterFromId("Spain_Dozor");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			BeginChangeCharacterActions(sld);
			sld.actions.dead.d1 = "death_7";
			sld.actions.dead.d2 = "death_7";
			EndChangeCharacterActions(sld);
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Keys_lagoon_79", 3.5);
		break;

		case "Keys_lagoon_79":
			locCameraFromToPos(-3.868, 3.551, -14.477, false, -2.595, 2.767, -21.951);
			DoQuestCheckDelay("Keys_lagoon_80", 2.5);
		break;

		case "Keys_lagoon_80":
			StartBattleLandInterface(); // вкл интерфейс
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Rimalier");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_5";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_81":
			locCameraFollow();
			InterfaceStates.Buttons.Save.enable = 1;
			DeleteAttribute(&TEV, "StopTimeScale");

			sld = CharacterFromID("Rimalier");
			if (IsOfficer(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.CurrentNode = "Hired";
				sld.Dialog.TempNode = "Hired";
			}
			else
			{
				LAi_SetFreeFighter(sld);
				sld.Dialog.CurrentNode = "Keys_lagoon_neitral";
			}
			sld = CharacterFromID("Daniel_Monbar");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			for (i = 1; i <= 15; i++)
			{
				iTemp = GetCharacterIndex("Bucaneers_Aruba_Outpost_" + i);
				if (iTemp != -1)
				{
					sld = &characters[iTemp];
					if (!LAi_IsDead(sld))
					{
						LAi_SetWarriorType(sld);
						LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					}
				}
			}

			DoQuestCheckDelay("Keys_lagoon_82", 0.5);
		break;

		case "Keys_lagoon_82":
			for (i = 1; i <= 7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Keys_Mine_Spain_" + i, "sold_spa_" + (1 + rand(14)), "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				CB_Perks(sld);
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "Aruba_deadlock", "reload", "reload2_back");
				LAi_group_MoveCharacter(sld, "Keys_Mine_Spain");
			}

			for (i = 8; i <= 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Keys_Mine_Spain_" + i, "spa_mush_" + (1 + rand(7)), "man", "mushketer", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "Aruba_deadlock", "reload", "reload2_back");
				LAi_group_MoveCharacter(sld, "Keys_Mine_Spain");
			}

			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Keys_Mine_Spain", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Keys_Mine_Spain", LAI_GROUP_PLAYER, true);
			DoQuestCheckDelay("Keys_lagoon_83_Check", 0.2);
		break;

		case "Keys_lagoon_83_Check":
			n = 0;

			for (i = 1; i <= 10; i++)
			{
				iTemp = GetCharacterIndex("Keys_Mine_Spain_" + i);
				if (iTemp != -1)
				{
					sld = &characters[iTemp];
					if (!LAi_IsDead(sld)) n++;
				}
			}

			if (n <= 2)
			{
				DoQuestCheckDelay("Keys_lagoon_83", 0.1);
			}
			else
			{
				DoQuestCheckDelay("Keys_lagoon_83_Check", 0.2);
			}
		break;

		case "Keys_lagoon_83":
			for (i = 11; i <= 13; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Keys_Mine_Spain_" + i, "sold_spa_" + (1 + rand(14)), "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				CB_Perks(sld);
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "Aruba_deadlock", "reload", "reload2_back");
				LAi_group_MoveCharacter(sld, "Keys_Mine_Spain");
			}

			for (i = 14; i <= 15; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Keys_Mine_Spain_" + i, "spa_mush_" + (1 + rand(7)), "man", "mushketer", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "Aruba_deadlock", "reload", "reload2_back");
				LAi_group_MoveCharacter(sld, "Keys_Mine_Spain");
			}

			DoQuestCheckDelay("Keys_lagoon_84_Check", 0.2);
		break;

		case "Keys_lagoon_84_Check":
			n = 0;

			for (i = 1; i <= 15; i++)
			{
				iTemp = GetCharacterIndex("Keys_Mine_Spain_" + i);
				if (iTemp != -1)
				{
					sld = &characters[iTemp];
					if (!LAi_IsDead(sld)) n++;
				}
			}

			if (n <= 2)
			{
				DoQuestCheckDelay("Keys_lagoon_84", 0.1);
			}
			else
			{
				DoQuestCheckDelay("Keys_lagoon_84_Check", 0.2);
			}
		break;

		case "Keys_lagoon_84":
			for (i = 16; i <= 22; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Keys_Mine_Spain_" + i, "sold_spa_" + (1 + rand(14)), "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				CB_Perks(sld);
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "Aruba_deadlock", "reload", "reload2_back");
				LAi_group_MoveCharacter(sld, "Keys_Mine_Spain");
			}

			for (i = 23; i <= 25; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Keys_Mine_Spain_" + i, "spa_mush_" + (1 + rand(7)), "man", "mushketer", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				CB_Perks(sld);
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "Aruba_deadlock", "reload", "reload2_back");
				LAi_group_MoveCharacter(sld, "Keys_Mine_Spain");
			}

			LAi_group_SetCheck("Keys_Mine_Spain", "Keys_lagoon_85");
		break;

		case "Keys_lagoon_85":
			LAi_group_Delete("Keys_Mine_Spain");
			LAi_grp_alarmactive = false;
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			for (i = 1; i <= 15; i++)
			{
				int Live_Team_6 = GetCharacterIndex("Bucaneers_Aruba_Outpost_" + i);
				if (Live_Team_6 != -1)
				{
					sld = &characters[Live_Team_6];
					if (!LAi_IsDead(sld))
					{
						LAi_SetCitizenType(sld);
						LAi_CharacterDisableDialog(sld);
					}
				}
			}
			sld = characterFromId("Daniel_Monbar");
			MakeUnpushable(sld, false);
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Monbar_41";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_86":
			chrDisableReloadToLocation = false; // открыть локацию
			QuestPointerToLoc("Aruba_deadlock", "reload", "reload2_back"); // поставить поинт
			QuestPointerToLoc("Aruba_MinesEntrance", "reload", "reload1_back"); // поставить поинт
			AddQuestRecord("Keys_lagoon", "9");
			sld = GetCharacter(NPC_GenerateCharacter("Keys_Prisoner_1", "Miskito_1", "man", "man", 1, PIRATE, -1, false));
			LAi_SetImmortal(sld, true);
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_SaltMines", "quest", "prisoner1");
			sld = GetCharacter(NPC_GenerateCharacter("Keys_Prisoner_2", "Miskito_2", "man", "man", 1, PIRATE, -1, false));
			LAi_SetImmortal(sld, true);
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_SaltMines", "quest", "prisoner2");
			sld = GetCharacter(NPC_GenerateCharacter("Keys_Prisoner_3", "Miskito_3", "man", "man", 1, PIRATE, -1, false));
			LAi_SetImmortal(sld, true);
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_SaltMines", "quest", "prisoner3");
			sld = GetCharacter(NPC_GenerateCharacter("Keys_Prisoner_4", "Miskito_4", "man", "man", 1, PIRATE, -1, false));
			LAi_SetImmortal(sld, true);
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_SaltMines", "quest", "prisoner4");
			sld = GetCharacter(NPC_GenerateCharacter("Anakaona", "squaw_3", "woman", "woman_B", 1, PIRATE, -1, false));
			LAi_SetImmortal(sld, true);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_SaltMines", "goto", "goto4");

			sld = GetCharacter(NPC_GenerateCharacter("Inigo_Cabrera", "off_spa_9", "man", "man", CB_Rank(), SPAIN, 1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() * 1.5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
			CB_Perks(sld);
			sld.name = FindPersonalName("Inigo_Cabrera_name");
			sld.lastname = FindPersonalName("Inigo_Cabrera_lastname");
			sld.dialog.filename = "Quest\LeBasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Cabrera_1";
			LAi_SetStayType(sld);
			sld.talker = 10;
			ChangeCharacterAddressGroup(sld, "Aruba_SaltMines", "goto", "goto3");
			sld = GetCharacter(NPC_GenerateCharacter("Cabrera_Guard_1", "sold_spa_" + (1 + rand(14)), "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_SaltMines", "goto", "goto6");
			sld = GetCharacter(NPC_GenerateCharacter("Cabrera_Guard_2", "sold_spa_" + (1 + rand(14)), "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_SaltMines", "goto", "goto1");
			sld = GetCharacter(NPC_GenerateCharacter("Cabrera_Guard_3", "sold_spa_" + (1 + rand(14)), "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_SaltMines", "goto", "goto2");
			sld = GetCharacter(NPC_GenerateCharacter("Cabrera_Guard_4", "sold_spa_" + (1 + rand(14)), "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_SaltMines", "goto", "goto12");
			pchar.quest.Aruba_SaltMines_locator.win_condition.l1 = "locator";
			pchar.quest.Aruba_SaltMines_locator.win_condition.l1.location = "Aruba_SaltMines";
			pchar.quest.Aruba_SaltMines_locator.win_condition.l1.locator_group = "quest";
			pchar.quest.Aruba_SaltMines_locator.win_condition.l1.locator = "mushketer2";
			pchar.quest.Aruba_SaltMines_locator.win_condition = "Keys_lagoon_87";
		break;

		case "Keys_lagoon_87":
			sld = characterFromId("Inigo_Cabrera");
			AddLandQuestMark_Main(sld, "Keys_lagoon");
			CharacterTurnByChr(sld, pchar);
			sld = characterFromId("Anakaona");
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_ActorAnimation(sld, "afraid", "", -1.0);
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("Cabrera_Guard_" + i);
				LAi_ActorTurnToLocator(sld, "goto", "goto3");
			}
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromId("Keys_Prisoner_" + i);
				CharacterTurnByChr(sld, pchar);
			}
			sld = characterFromId("Inigo_Cabrera");
			CharacterTurnByChr(sld, pchar);
		break;

		case "Keys_lagoon_87_1":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_8"));
			AoP_NPCDialogAddLine("Inigo_Cabrera", StringFromKey("LeBasque_Inigo_Cabrera_1"));
			AoP_NPCDialogAddLine("Daniel_Monbar", GetSexPhrase(StringFromKey("LeBasque_Daniel_Monbar_9_m", pchar.name), StringFromKey("LeBasque_Daniel_Monbar_9_f", pchar.name)));
			AoP_NPCDialogAddLine("Inigo_Cabrera", StringFromKey("LeBasque_Inigo_Cabrera_2"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_10"));
			AoP_NPCDialogAddLine("Inigo_Cabrera", StringFromKey("LeBasque_Inigo_Cabrera_3"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_11"));
			AoP_NPCDialogLaunch("Daniel_Monbar", "Inigo_Cabrera", "Keys_lagoon_88");
		break;

		case "Keys_lagoon_88":
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromID("Cabrera_Guard_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Mines_Wars");
			}
			sld = characterFromId("Inigo_Cabrera");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "Mines_Wars");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Mines_Wars", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Mines_Wars", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Mines_Wars", "Keys_lagoon_89");
		break;

		case "Keys_lagoon_89":
			LAi_group_Delete("Mines_Wars");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = characterFromId("Daniel_Monbar");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Monbar_44";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_90":
			QuestPointerDelLoc("Aruba_IndianVillage", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Aruba_Jungle_02", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("Aruba_Jungle_01", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("Aruba_Jungle_03", "reload", "reload3_back"); // удалить поинт
			QuestPointerDelLoc("Aruba_deadlock", "reload", "reload2_back"); // удалить поинт
			QuestPointerDelLoc("Aruba_MinesEntrance", "reload", "reload1_back"); // удалить поинт
			QuestPointerDelLoc("Aruba_outpost", "reload", "reload2_back"); // удалить поинт
			for (i = 0; i < 5; i++)
			{
				sld = characterFromID("ArubaIndianGuard_" + i);
				sld.lifeday = 0;
			}
			DoQuestCheckDelay("Keys_lagoon_91", 1.5);
		break;

		case "Keys_lagoon_91":
			n = FindLocation("Aruba_IndianVillage");
			Locations[n].models.always.mushkets = "village_Mushkets";
			Locations[n].models.always.mushkets.tech = "DLightModel";
			locations[n].models.day.charactersPatch = "village_patch_mushkets";
			LAi_SetActorType(pchar);
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_289"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("Aruba_IndianVillage", "quest", "quest_gg", "Keys_lagoon_92");
			WaitDate("", 0, 0, 1, 0, 0); // мотаем время
			SetCurrentTime(14, 34);
			Whr_UpdateWeather();
			LaunchFrameForm();
			sld = characterFromId("Anakaona");
			LAi_SetActorType(sld);
			MakeUnpushable(sld, true);
			ChangeCharacterAddressGroup(sld, "Aruba_IndianVillage", "quest", "quest_anakaona");
			sld = characterFromId("Daniel_Monbar");
			DeleteAttribute(sld, "FreeFighter");
			MakeUnpushable(sld, true);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_IndianVillage", "quest", "quest_monbar");
			sld = characterFromId("Yamai");
			MakeUnpushable(sld, true);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_IndianVillage", "quest", "teleport1");
			sld = GetCharacter(NPC_GenerateCharacter("Bucaneers_Aruba_Outpost_16", "mush_ctz_7", "man", "mushketer", CB_Rank(), PIRATE, -1, true));
			sld.Buccaneer = true;
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
			MakeUnpushable(sld, true);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_IndianVillage", "goto", "goto16");
			sld = GetCharacter(NPC_GenerateCharacter("Bucaneers_Aruba_Outpost_17", "mush_ctz_9", "man", "mushketer", CB_Rank(), PIRATE, -1, true));
			sld.Buccaneer = true;
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
			MakeUnpushable(sld, true);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_IndianVillage", "soldiers", "protector1");
		break;

		case "Keys_lagoon_92":
			LAi_ActorTurnToLocator(pchar, "quest", "teleport1");
			sld = characterFromId("Bucaneers_Aruba_Outpost_16");
			LAi_ActorTurnToLocator(sld, "goto", "goto18");
			sld = characterFromId("Bucaneers_Aruba_Outpost_17");
			LAi_ActorTurnToLocator(sld, "quest", "quest_anakaona");
			sld = characterFromId("Yamai");
			LAi_ActorTurnToLocator(sld, "goto", "goto18");
			sld = characterFromId("Daniel_Monbar");
			LAi_ActorTurnToLocator(sld, "quest", "teleport1");
			sld = characterFromId("Anakaona");
			LAi_ActorTurnToLocator(sld, "quest", "quest_gg");
			DoQuestCheckDelay("Keys_lagoon_93", 2.5);
		break;

		case "Keys_lagoon_93":
			i = FindLocation("Aruba_Outpost");
			locations[i].DisableOfficers = 1;
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Yamai");
			sld.Dialog.CurrentNode = "Yamai_3";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_94":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_12"));
			AoP_NPCDialogAddLine("Yamai", StringFromKey("LeBasque_Yamai_7"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_13"));
			AoP_NPCDialogAddLine("Yamai", StringFromKey("LeBasque_Yamai_8"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_14"));
			AoP_NPCDialogAddLine("Yamai", StringFromKey("LeBasque_Yamai_9"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_15"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_16"));
			AoP_NPCDialogAddLine("Yamai", StringFromKey("LeBasque_Yamai_10"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_17"));
			AoP_NPCDialogLaunch("Daniel_Monbar", "Yamai", "Keys_lagoon_97");
		break;

		case "Keys_lagoon_97":
			sld = characterFromID("Rimalier");
			//if (!IsOfficer(sld))
			//{
				DeleteAttribute(sld, "FreeFighter");
			//}
			sld = characterFromId("Mary_Belfler");
			DeleteAttribute(sld, "FreeFighter");
			sld = CharacterFromID("Daniel_Monbar");
			sld.model = "Daniel_Montbars";
			sld.model.animation = "man";
			RemoveCharacterEquip(sld, MUSKET_ITEM_TYPE);
			TakeItemFromCharacter(sld, "mortar");
			Characters_RefreshModel(sld);
			DeleteAttribute(sld, "MushketType");
			DeleteAttribute(sld, "MushketBulletType");
			DeleteAttribute(sld, "MusketOutfit");
			GiveItem2Character(sld, "blade30");
			EquipCharacterByItem(sld, "blade30");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			LAi_SetGroundSitType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_outpost", "quest", "quest2");
			LAi_SetGroundSitType(pchar);
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_290"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("Aruba_outpost", "quest", "quest1", "Keys_lagoon_98");
			Whr_UpdateWeather();
			LaunchFrameForm();
			WaitDate("", 0, 0, 2, 0, 0); // мотаем время
			SetCurrentTime(2, 34);
		break;

		case "Keys_lagoon_98":
			sld = characterFromId("Fransua_Olone");
			MakeUnpushable(sld, false);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_outpost", "goto", "goto11");
			sld = characterFromId("Mishel_le_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_outpost", "goto", "goto11");
			sld = characterFromId("Etien_Marso");
			MakeUnpushable(sld, false);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Aruba_outpost", "goto", "goto11");
			locCameraFromToPos(-1.926, 2.975, -10.103, false, -5.085, 0.088, -6.407);
			StartInstantDialogNoType("Daniel_Monbar", "Monbar_49_1", "Quest\LeBasque\Monbar_dialog.c");
		break;

		case "Keys_lagoon_99":
			QuestMovieLockPlayer(); // окаемки вкл
			EndBattleLandInterface(); // откл интерфейс
			locCameraFromToPos(-1.926, 2.975, -10.103, false, -4.282, 0.088, -3.276);
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorFollow(sld, characterFromID("Daniel_Monbar"), "Keys_lagoon_100", -1);
			sld = characterFromId("Etien_Marso");
			LAi_ActorFollow(sld, characterFromID("Mishel_le_Bask"), "", -1);
			sld = characterFromId("Fransua_Olone");
			LAi_ActorFollow(sld, characterFromID("Mishel_le_Bask"), "", -1);
		break;

		case "Keys_lagoon_100":
			LAi_FadeEx(1.0, 1.0, 1.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_101", 1.5);
		break;

		case "Keys_lagoon_101":
			locCameraFollow();
			LAi_SetActorType(pchar);
			ChangeCharacterAddressGroup(pchar, "Aruba_outpost", "quest", "quest_gg");
			LAi_ActorTurnToCharacter(pchar, characterFromID("Mishel_le_Bask"));
			sld = characterFromId("Daniel_Monbar");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, characterFromID("Mishel_le_Bask"));
			DoQuestCheckDelay("Keys_lagoon_102", 1.6);
		break;

		case "Keys_lagoon_102":
			QuestMovieUnLockPlayer();
			StartBattleLandInterface();
			LAi_SetStayType(pchar);

			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_15"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Daniel_Monbar", "Keys_lagoon_103");
		break;

		case "Keys_lagoon_103":
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_Aruba";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_104":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_16"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_18"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_17"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Daniel_Monbar", "Keys_lagoon_105");
		break;

		case "Keys_lagoon_105":
			sld = characterFromId("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_Aruba_2";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_106":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_18"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Daniel_Monbar", "Keys_lagoon_107");
		break;

		case "Keys_lagoon_107":
			sld = characterFromId("Mishel_le_Bask");
			// LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_Aruba_4";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_116":
			i = FindLocation("Aruba_Outpost");
			DeleteAttribute(&locations[i], "DisableOfficers");
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = true; // закрыть локацию
			n = FindLocation("Aruba_Jungle_03");
			if (n != -1)
			{
				DeleteAttribute(&Locations[n], "models.always.spa_soldiers");
				DeleteAttribute(&Locations[n], "models.always.spa_blood");
				Locations[n].models.always.locators = "jungle14_locators";
				Locations[n].models.always.grassPatch = "jungle14_grass";
				Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
				Locations[n].models.day.charactersPatch = "jungle14_patch";
				Locations[n].models.night.charactersPatch = "jungle14_patch";
			}
			n = FindLocation("Aruba_IndianVillage");
			if (n != -1)
			{
				DeleteAttribute(&Locations[n], "models.always.mushkets");

				Locations[n].models.day.charactersPatch = "village_patch";
				Locations[n].models.night.charactersPatch = "village_patch";
			}

			sld = characterFromId("Mishel_le_Bask");
			LAi_CharacterDisableDialog(sld);
			FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, FindPersonalName("Mishel_le_Bask_ship"), CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
			SetCrewQuantityFull(sld);
			SetBaseShipData(sld);
			sld.nation = PIRATE;
			sld.Ship.Mode = "pirate";
			sld.Ship.Crew.Morale = 100;
			SetCharacterGoods(sld, GOOD_FOOD, 2500);
			SetCharacterGoods(sld, GOOD_BALLS, 4000);
			SetCharacterGoods(sld, GOOD_GRAPES, 1000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 400);
			SetCharacterGoods(sld, GOOD_BOMBS, 1000);
			SetCharacterGoods(sld, GOOD_POWDER, 4000);
			SetCharacterGoods(sld, GOOD_PLANKS, 150);
			SetCharacterGoods(sld, GOOD_RUM, 400);
			SetCharacterGoods(sld, GOOD_WEAPON, 500);
			SetCharacterGoods(sld, GOOD_Medicament, 600);
			SetCharacterRemovable(sld, false);
			SetCharacterShipLocation(sld, "Shore67");
			// LAi_SetCitizenType(sld);

			sld = characterFromId("Etien_Marso");
			LAi_CharacterDisableDialog(sld);
			if (!CheckAttribute(sld, "Ship.Type") || sti(sld.Ship.Type) == SHIP_NOTUSED)
			{
				FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("Etien_Marso_ship"), CANNON_TYPE_CULVERINE_LBS24, 90, 90, 90);
			}
			SetCrewQuantityFull(sld);
			SetBaseShipData(sld);
			sld.nation = PIRATE;
			sld.Ship.Mode = "pirate";
			sld.Ship.Crew.Morale = 100;
			SetCharacterGoods(sld, GOOD_FOOD, 2500);
			SetCharacterGoods(sld, GOOD_BALLS, 4000);
			SetCharacterGoods(sld, GOOD_GRAPES, 1000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 400);
			SetCharacterGoods(sld, GOOD_BOMBS, 1000);
			SetCharacterGoods(sld, GOOD_POWDER, 4000);
			SetCharacterGoods(sld, GOOD_PLANKS, 150);
			SetCharacterGoods(sld, GOOD_RUM, 400);
			SetCharacterGoods(sld, GOOD_WEAPON, 400);
			SetCharacterGoods(sld, GOOD_Medicament, 400);
			SetCharacterShipLocation(sld, "Shore67"); // корабль в бухту
			// LAi_SetCitizenType(sld);

			sld = CharacterFromID("Fransua_Olone");
			LAi_CharacterDisableDialog(sld);
			FantomMakeCoolSailor(sld, SHIP_GALEON_H, FindPersonalName("Fransua_Olone_ship_Soledad"), CANNON_TYPE_CANNON_LBS24, 90, 90, 90);
			SetCrewQuantityFull(sld);
			SetBaseShipData(sld);
			sld.nation = PIRATE;
			sld.Ship.Mode = "pirate";
			sld.Ship.Crew.Morale = 100;
			SetCharacterGoods(sld, GOOD_FOOD, 2500);
			SetCharacterGoods(sld, GOOD_BALLS, 4000);
			SetCharacterGoods(sld, GOOD_GRAPES, 1000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 500);
			SetCharacterGoods(sld, GOOD_BOMBS, 700);
			SetCharacterGoods(sld, GOOD_POWDER, 4000);
			SetCharacterGoods(sld, GOOD_PLANKS, 200);
			SetCharacterGoods(sld, GOOD_RUM, 400);
			SetCharacterGoods(sld, GOOD_WEAPON, 600);
			SetCharacterGoods(sld, GOOD_Medicament, 1000);
			SetCharacterShipLocation(sld, "Shore67");
			// LAi_SetCitizenType(sld);

			sld = CharacterFromID("Daniel_Monbar");
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("Daniel_Monbar_ship"), CANNON_TYPE_LBS_BY_SHIP, 90, 90, 90);
			SetCrewQuantityFull(sld);
			SetBaseShipData(sld);
			sld.nation = PIRATE;
			sld.Ship.Mode = "pirate";
			sld.Ship.Crew.Morale = 100;
			SetCharacterGoods(sld, GOOD_FOOD, 3500);
			SetCharacterGoods(sld, GOOD_BALLS, 3000);
			SetCharacterGoods(sld, GOOD_GRAPES, 1000);
			SetCharacterGoods(sld, GOOD_KNIPPELS, 400);
			SetCharacterGoods(sld, GOOD_BOMBS, 1000);
			SetCharacterGoods(sld, GOOD_POWDER, 3000);
			SetCharacterGoods(sld, GOOD_PLANKS, 150);
			SetCharacterGoods(sld, GOOD_RUM, 250);
			SetCharacterGoods(sld, GOOD_WEAPON, 600);
			SetCharacterGoods(sld, GOOD_Medicament, 400);
			SetCharacterShipLocation(sld, "Shore67");
			DoQuestCheckDelay("Keys_lagoon_118_1", 0.1);
		break;

		case "Keys_lagoon_117":
			SetCharacterShipLocation(pchar, "Shore67"); // корабль в бухту
			sld = CharacterFromID("Alone_Bucaneer_2");
			sld.lifeday = 0;
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_291"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("Shore67", "goto", "goto10", "Keys_lagoon_118");
			Whr_UpdateWeather();
			LaunchFrameForm();
			SetCurrentTime(9, 00);
			sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_Portman", "officer_12", "man", "man", 1, PIRATE, -1, false));
			sld.Buccaneer = true;
			FantomMakeCoolFighter(sld, 30, 100, 70, "blade32", "pistol5", 50);
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Keys_lagoon_ShipKeeper_1";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Shore67", "goto", "goto2");
			sld = characterFromId("Mishel_le_Bask");
			ChangeCharacterAddressGroup(sld, "Shore67", "goto", "goto1");
		break;

		case "Keys_lagoon_118_1":
			sld = characterFromId("Daniel_Monbar");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Monbar_60";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_118":
			sld = characterFromId("Mishel_le_Bask");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_Departure";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_119":
			AoP_AddMapMarkByCoords("Keys_lagoon", 223.552, -813.796);
			RemoveMapQuestMark("Aruba", "Keys_lagoon"); // убрать метку острова
			bQuestDisableMapEnter = false; // открыть карту
			Island_SetReloadEnableGlobal("Aruba", true); // на остров можно
			AddQuestRecord("Keys_lagoon", "10");
			chrDisableReloadToLocation = false; // открыть локацию
			pchar.questTemp.AoP.ForcePirateFlag = true;
			Flag_PIRATE();
			sld = CharacterFromID("Mishel_le_Bask");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, false);
			sld = CharacterFromID("Etien_Marso");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, false);
			sld = CharacterFromID("Fransua_Olone");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, false);
			sld = CharacterFromID("Daniel_Monbar");
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetCharacterRemovable(sld, false);
			pchar.quest.Maracaibo_fort_war.win_condition.l1 = "location";
			pchar.quest.Maracaibo_fort_war.win_condition.l1.location = "Maracaibo";
			pchar.quest.Maracaibo_fort_war.win_condition = "Keys_lagoon_120";
		break;

		case "Keys_lagoon_120":
			ClearIslandShips("Maracaibo");
			Colonies[FindColony("Maracaibo")].DontSetShipInPort = true;
			ClearIslandShips("Gibraltar");
			Colonies[FindColony("Gibraltar")].DontSetShipInPort = true;
			AoP_RemoveMapMarkByCoords("Keys_lagoon");
			DoQuestCheckDelay("Off_Interface", 0.2);
			DoQuestCheckDelay("Keys_lagoon_121", 3);
		break;

		case "Keys_lagoon_121":
			MakeCloneShipDeck(pchar, true); // подмена палубы
			DoQuestReloadToLocation("Ship_deck", "goto", "goto5", "Keys_lagoon_122");
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_11_1";
			ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto6");
			for (i = 1; i <= 7; i++) //
			{
				sld = GetCharacter(NPC_GenerateCharacter("MainHero_Team" + i, "citiz_" + (39 - i), "man", "man", 5, PIRATE, 1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade3", "pistol2", 20);
				LAi_CharacterDisableDialog(sld);
				LAi_SetCitizenType(sld);
				ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto" + i);
			}
		break;

		case "Keys_lagoon_122":
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_123":
			sld = characterFromId("Mary_Belfler");
			RemovePassenger(pchar, sld);
			pchar.TempPerks.QuestTroopers = true;
			pchar.questTemp.AoP.KeysLagoonFortAssault = true;
			pchar.quest.Keys_lagoon_FortCaptured.win_condition.l1 = "Fort_capture";
			pchar.quest.Keys_lagoon_FortCaptured.win_condition.l1.character = "Maracaibo Fort Commander";
			pchar.quest.Keys_lagoon_FortCaptured.win_condition = "Keys_lagoon_125";
			QuestToSeaLogin_PrepareLoc("Maracaibo", "quest_ships", "quest_ship_2", true);
			QuestToSeaLogin_Launch();
			DoQuestCheckDelay("Keys_lagoon_124", 2);
		break;

		case "Keys_lagoon_124":
			AddQuestRecord("Keys_lagoon", "11");
		break;

		case "Keys_lagoon_125":
			DeleteAttribute(pchar, "questTemp.AoP.KeysLagoonFortAssault");
			DeleteAttribute(pchar, "TempPerks.QuestTroopers");
			pchar.questTemp.AoP.KeysLagoonAfterFort = true;
		break;

		case "Keys_lagoon_126":
			SetCrewQuantity(pchar, 200);
			DeleteAttribute(pchar, "questTemp.AoP.KeysLagoonAfterFort");
			LocatorReloadEnterDisable("Maracaibo_town", "reload1_back", true); // закрыть путь на лодку
			LocatorReloadEnterDisable("Maracaibo_town", "reload2_back", true); // закрыть путь на лодку
			sld = CharacterFromID("Fransua_Olone");
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "Maracaibo_bankvault", "goto", "goto3");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Mary_Belfler");
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "Maracaibo_prison", "goto", "goto20");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Rimalier");
			LAi_LoginInCaptureTown(sld, true);
			PlaceCharacter(sld, "goto", "random_must_be_near");
			if (IsOfficer(sld))
				LAi_SetOfficerType(sld);
			else
				LAi_SetFreeFighter(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_neitral";
			sld = CharacterFromID("Daniel_Monbar");
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "goto", "goto5");
			LAi_SetActorType(sld);
			sld = CharacterFromID("Etien_Marso");
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "Maracaibo_store", "goto", "goto3");
			LAi_SetActorType(sld);
			for (i = 1; i <= 12; i++)
			{
				Model = LAi_GetBoardingModel(pchar, &sTemp);
				sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_MaracaiboSailor_" + i, Model, "man", sTemp, CB_Rank(), PIRATE, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade3", "pistol2", 30);
				LAi_CharacterDisableDialog(sld);
				LAi_LoginInCaptureTown(sld, true);
				PlaceCharacter(sld, "goto", "random_must_be_near");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i = 1; i <= 10; i++)
			{
				Model = LAi_GetBoardingModel(pchar, &sTemp);
				sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_MaracaiboSailor_Jungle_" + i, Model, "man", sTemp, CB_Rank(), PIRATE, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade3", "pistol2", 30);
				LAi_CharacterDisableDialog(sld);
				LAi_LoginInCaptureTown(sld, true);
				ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "goto", "goto" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}

			sld = CharacterFromID("Mishel_le_Bask");
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "Maracaibo_town", "goto", "goto9");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_29";
			LAi_ActorFollow(sld, pchar, "Keys_lagoon_127", -1);
		break;

		case "Keys_lagoon_127":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_128":
			AddQuestRecord("Keys_lagoon", "12");
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			TW_Init_KeysLagoon_Maracaibo();
			TW_Open("KeysLagoon_Maracaibo");
			pchar.quest.Keys_lagoon_CheckStore.win_condition.l1 = "location";
			pchar.quest.Keys_lagoon_CheckStore.win_condition.l1.location = "Maracaibo_store";
			pchar.quest.Keys_lagoon_CheckStore.win_condition = "Keys_lagoon_Store";
			pchar.quest.Keys_lagoon_CheckPrison.win_condition.l1 = "location";
			pchar.quest.Keys_lagoon_CheckPrison.win_condition.l1.location = "Maracaibo_prison";
			pchar.quest.Keys_lagoon_CheckPrison.win_condition = "Keys_lagoon_Prison";
			pchar.quest.Keys_lagoon_CheckVault.win_condition.l1 = "location";
			pchar.quest.Keys_lagoon_CheckVault.win_condition.l1.location = "Maracaibo_bankvault";
			pchar.quest.Keys_lagoon_CheckVault.win_condition = "Keys_lagoon_Vault";
			pchar.quest.Keys_lagoon_CheckJungle.win_condition.l1 = "location";
			pchar.quest.Keys_lagoon_CheckJungle.win_condition.l1.location = "Maracaibo_ExitTown";
			pchar.quest.Keys_lagoon_CheckJungle.win_condition = "Keys_lagoon_Jungle";
			QuestPointerToLoc("Maracaibo_town", "reload", "gate_back"); // поставить поинт
			QuestPointerToLoc("Maracaibo_town", "reload", "reload6_back"); // поставить поинт
			QuestPointerToLoc("Maracaibo_town", "reload", "reload_jail"); // поставить поинт
			QuestPointerToLoc("Maracaibo_town", "reload", "reload8_back"); // поставить поинт
			QuestPointerToLoc("Maracaibo_bank", "reload", "reload2"); // поставить поинт
			n = FindLocation("Maracaibo_town");
			locations[n].reload.l6.close_for_night = 0;
			locations[n].reload.l8.close_for_night = 0;
			locations[n].reload.l3.close_for_night = 0;
		break;

		case "Keys_lagoon_Store":
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Etien_Marso");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_Inspection_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_Prison":
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Mary_Belfler");
			sld.Dialog.CurrentNode = "Keys_lagoon_Inspection_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_Vault":
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Fransua_Olone");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_Inspection_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_Jungle":
			chrDisableReloadToLocation = true;
			sld = CharacterFromID("Daniel_Monbar");
			sld.Dialog.CurrentNode = "Keys_lagoon_Inspection_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_130":
			QuestPointerToLoc("Maracaibo_town", "reload", "reload3_back"); // поставить поинт
			pchar.quest.Maracaibo_townhall_go.win_condition.l1 = "location";
			pchar.quest.Maracaibo_townhall_go.win_condition.l1.location = "Maracaibo_townhall";
			pchar.quest.Maracaibo_townhall_go.win_condition = "Keys_lagoon_131";
		break;

		case "Keys_lagoon_131":
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload1_back", true);
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload2", true);
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload3", true);
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Maracaibo_townhall", "goto", "goto4");
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Maracaibo_townhall", "goto", "goto2");
			DoQuestCheckDelay("Keys_lagoon_132", 0.5);
		break;

		case "Keys_lagoon_132":
			sld = CharacterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "Keys_lagoon_2";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
		break;

		case "Keys_lagoon_133":
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_5";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_135":
			AddQuestRecord("Keys_lagoon", "13");
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload3", false);
			QuestPointerToLoc("Maracaibo_townhall", "reload", "reload3"); // поставить поинт
			QuestPointerToLoc("Maracaibo_townhallRoom", "reload", "reload2"); // поставить поинт
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetFreeFighter(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_townhall_repeat";
			sld = CharacterFromID("Etien_Marso");
			LAi_SetFreeFighter(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_townhall_repeat";
			sld = GetCharacter(NPC_GenerateCharacter("Bedroom_Officer", "off_spa_3", "man", "man", CB_Rank(), SPAIN, 1, true));
			FantomMakeCoolFighter(sld, CB_Rank() + 5, CB_Fencing() * 1.5, CB_Pistol() * 1.5, "blade3", "pistol2", 20);
			CB_Perks(sld);
			sld.dialog.filename = "Quest\LeBasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Bedroom_Spa_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "CommonBedroom", "goto", "goto_spa");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bedroom_Soldiers_" + i, "urban_spa_" + i, "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				CB_Perks(sld);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "CommonBedroom", "goto", "goto" + (4 + i));
			}
			pchar.quest.Maracaibo_townhall_bedroom.win_condition.l1 = "location";
			pchar.quest.Maracaibo_townhall_bedroom.win_condition.l1.location = "CommonBedroom";
			pchar.quest.Maracaibo_townhall_bedroom.win_condition = "Keys_lagoon_136";
		break;

		case "Keys_lagoon_136":
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = CharacterFromID("Bedroom_Officer");
			LAi_ActorDialogNow(sld, pchar, "", -1);
			sld = CharacterFromID("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "CommonBedroom", "goto", "goto4");
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "CommonBedroom", "goto", "goto4");
		break;

		case "Keys_lagoon_137":
			sld = CharacterFromID("Bedroom_Officer");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "bedroom_spa_group");
			for (i = 1; i <= 3; i++)
			{
				sld = characterFromId("Bedroom_Soldiers_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "bedroom_spa_group");
			}
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("bedroom_spa_group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("bedroom_spa_group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("bedroom_spa_group", "Keys_lagoon_138");
		break;

		case "Keys_lagoon_138":
			LAi_group_Delete("bedroom_spa_group");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_6";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
		break;

		case "Keys_lagoon_139":
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_5";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_140":
			sld = CharacterFromID("Mary_Belfler");
			sld.Dialog.CurrentNode = "Keys_lagoon_17";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_142":
			LAi_SetActorType(pchar);
			LAi_FadeEx(2.0, 3.0, 2.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_143", 4.5);
		break;

		case "Keys_lagoon_143":
			QuestPointerDelLoc("Maracaibo_townhall", "reload", "reload3"); // убрать поинт
			QuestPointerDelLoc("Maracaibo_townhallRoom", "reload", "reload2"); // убрать поинт
			QuestPointerDelLoc("Maracaibo_town", "reload", "reload3_back"); // убрать поинт
			chrDisableReloadToLocation = false; // открыть локацию
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload1_back", false);
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload2", false);
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Keys_lagoon", "14");
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetFreeFighter(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_townhall_repeat_2";
			sld = CharacterFromID("Etien_Marso");
			LAi_SetFreeFighter(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_townhall_repeat_2";
			sld = CharacterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_37";
			AddLandQuestMark_Main(sld, "Keys_lagoon");
			LAi_CharacterEnableDialog(sld);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Maracaibo_town", "goto", "goto2");
			QuestPointerToLoc("Maracaibo_town", "goto", "goto2"); // поставить поинт
			pchar.quest.return_maracaibo_town.win_condition.l1 = "location";
			pchar.quest.return_maracaibo_town.win_condition.l1.location = "Maracaibo_town";
			pchar.quest.return_maracaibo_town.win_condition = "Keys_lagoon_144";
		break;

		case "Keys_lagoon_144":
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Maracaibo_town", "patrol", "patrol7");
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Mishel_le_Bask"), "", -1);
			sld = CharacterFromID("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "Maracaibo_town", "patrol", "patrol7");
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Mishel_le_Bask"), "Keys_lagoon_144_1", -1);
		break;

		case "Keys_lagoon_144_1":
			sld = CharacterFromID("Mishel_le_Bask");
			CharacterTurnByLoc(sld, "goto", "goto23");
		break;

		case "Keys_lagoon_145":
		sld = CharacterFromID("Mishel_le_Bask");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, characterFromID("Etien_Marso"));
		sld = CharacterFromID("Mary_Belfler");
		LAi_ActorTurnToCharacter(sld, characterFromID("Etien_Marso"));
		sld = CharacterFromID("Etien_Marso");
		LAi_ActorTurnToCharacter(sld, characterFromID("Mary_Belfler"));
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_9"));
			AoP_NPCDialogAddLine("Mary_Belfler", StringFromKey("LeBasque_Mary_Belfler_8"));
			AoP_NPCDialogLaunch("Etien_Marso", "Mary_Belfler", "Keys_lagoon_146");
		break;

		case "Keys_lagoon_146":
			sld = CharacterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_39";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_147":
		sld = CharacterFromID("Mishel_le_Bask");
		LAi_ActorTurnToCharacter(sld, characterFromID("Etien_Marso"));
		sld = CharacterFromID("Etien_Marso");
		LAi_ActorTurnToCharacter(sld, characterFromID("Mishel_le_Bask"));
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_10"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_19"));
			AoP_NPCDialogLaunch("Etien_Marso", "Mishel_le_Bask", "Keys_lagoon_148");
		break;

		case "Keys_lagoon_148":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_41";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_149":
		sld = CharacterFromID("Mishel_le_Bask");
		LAi_ActorTurnToCharacter(sld, characterFromID("Mary_Belfler"));
		sld = CharacterFromID("Mary_Belfler");
		LAi_ActorTurnToCharacter(sld, characterFromID("Mishel_le_Bask"));
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mary_Belfler", StringFromKey("LeBasque_Mary_Belfler_9"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_20"));
			AoP_NPCDialogLaunch("Mary_Belfler", "Mishel_le_Bask", "Keys_lagoon_163");
		break;

		case "Keys_lagoon_163":
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_292"), "Reload_To_Location", 0.1, 3.0);
			SetLaunchFrameReloadLocationParam("Maracaibo_ExitTown", "reload", "reload3", "Keys_lagoon_164");
			Whr_UpdateWeather();
			LaunchFrameForm();
			SetCurrentTime(12, 00);
			WaitDate("", 0, 0, 1, 0, 0);
			sld = CharacterFromID("Mishel_le_Bask");
			ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "goto", "goto6");
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "goto", "goto6");
			sld = CharacterFromID("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "goto", "goto6");
			sld = CharacterFromID("Fransua_Olone");
			ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "goto", "goto6");
			sld = CharacterFromID("Rimalier");
			if (!IsOfficer(sld))
			{
				ChangeCharacterAddressGroup(sld, "Maracaibo_ExitTown", "goto", "goto6");
			}
		break;

		case "Keys_lagoon_164":
			chrDisableReloadToLocation = true; // закрыть локацию
			sld = CharacterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_59";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorFollow(sld, characterFromID("Mishel_le_Bask"), "", -1);
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorFollow(sld, characterFromID("Mishel_le_Bask"), "", -1);
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Mishel_le_Bask"), "", -1);
			sld = CharacterFromID("Daniel_Monbar");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Mishel_le_Bask"), "", -1);
			sld = characterFromID("Rimalier");
			if (!IsOfficer(sld))
			{
				DeleteAttribute(sld, "FreeFighter");
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromID("Mishel_le_Bask"), "", -1);
			}
		break;

		case "Keys_lagoon_165":
			QuestPointerToLoc("Maracaibo_ExitTown", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Maracaibo_jungle_01", "reload", "reload1_back"); // поставить поинт
			QuestPointerToLoc("Maracaibo_jungle_03", "reload", "reload3_back"); // поставить поинт
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = CharacterFromID("Daniel_Monbar");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			sld = characterFromID("Rimalier");
			if (!IsOfficer(sld))
			{
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			for (i = 1; i <= 10; i++)
			{
				sld = characterFromID("Keys_lagoon_MaracaiboSailor_Jungle_" + i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Keys_lagoon_GibraltarJungleBattle.win_condition.l1 = "location";
			pchar.quest.Keys_lagoon_GibraltarJungleBattle.win_condition.l1.location = "Gibraltar_Jungle_01";
			pchar.quest.Keys_lagoon_GibraltarJungleBattle.win_condition = "Keys_lagoon_166";
		break;

		case "Keys_lagoon_166":
			chrDisableReloadToLocation = true;

			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			sld = CharacterFromID("Etien_Marso");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			sld = CharacterFromID("Mary_Belfler");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			sld = CharacterFromID("Fransua_Olone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			sld = CharacterFromID("Daniel_Monbar");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			sld = CharacterFromID("Rimalier");
			if (!IsOfficer(sld))
			{
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}

			for (i = 1; i <= 10; i++)
			{
				sld = characterFromID("Keys_lagoon_MaracaiboSailor_Jungle_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i = 1; i <= 25; i++)
			{
				if (i == 5 || i == 9 || i == 13 || i == 17 || i == 21 || i == 25)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_GibraltarSpa_" + i, "spa_mush_" + (1 + rand(7)), "man", "mushketer", 30, SPAIN, -1, false));
					FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_GibraltarSpa_" + i, "sold_spa_" + (1 + rand(7)), "man", "man", 30, SPAIN, -1, false));
					FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				}

				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Gibraltar_Jungle_Spa_war");

				switch (i)
				{
					case 1:  ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto1"); break;
					case 2:  ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto2"); break;
					case 3:  ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto3"); break;
					case 4:  ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto4"); break;
					case 5:  ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto5"); break;
					case 6:  ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto6"); break;
					case 7:  ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto7"); break;
					case 8:  ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto8"); break;
					case 9:  ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto9"); break;
					case 10: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto10"); break;

					case 11: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto1"); break;
					case 12: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto2"); break;
					case 13: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto3"); break;
					case 14: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto4"); break;
					case 15: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto5"); break;
					case 16: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto6"); break;
					case 17: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto7"); break;
					case 18: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto8"); break;
					case 19: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto9"); break;
					case 20: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto10"); break;

					case 21: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto1"); break;
					case 22: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto3"); break;
					case 23: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto5"); break;
					case 24: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto7"); break;
					case 25: ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "goto", "goto9"); break;
				}
			}
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Gibraltar_Jungle_Spa_war", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Gibraltar_Jungle_Spa_war", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Gibraltar_Jungle_Spa_war", "Keys_lagoon_167");
		break;

		case "Keys_lagoon_167":
			for (i = 1; i <= 15; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_GibraltarMush_" + i, "spa_mush_" + i, "man", "mushketer", 30, SPAIN, -1, false));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Gibraltar_Jungle_Spa_war");
				ChangeCharacterAddressGroup(sld, "Gibraltar_Jungle_01", "reload", "reload3_back");
			}
			LAi_group_SetRelation("Gibraltar_Jungle_Spa_war", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Gibraltar_Jungle_Spa_war", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Gibraltar_Jungle_Spa_war", "Keys_lagoon_168");
		break;

		case "Keys_lagoon_168":
			LAi_group_Delete("Gibraltar_Jungle_Spa_war");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = CharacterFromID("Etien_Marso");
			LAi_CharacterDisableDialog(sld);
			LAi_SetGroundSitType(sld);
			sld = CharacterFromID("Fransua_Olone");
			SetCharacterShipLocation(sld, "Shore_ship3"); // корабль в бухту
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Etien_Marso"), "", -1);
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Etien_Marso"), "", -1);
			sld = CharacterFromID("Daniel_Monbar");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Etien_Marso"), "", -1);
			sld = CharacterFromID("Rimalier");
			if (!IsOfficer(sld))
			{
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromID("Etien_Marso"), "", -1);
			}
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_70";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_169":
			n = FindLocation("Shore_ship3");
			Locations[n].QuestlockWeather = "Storm03_add";
			Locations[n].models.always.locators = "ShoreShip1_lcommon_ships";
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_293"), "Reload_To_Location", 0.1, 3.0);
			SetLaunchFrameReloadLocationParam("Shore_ship3", "reload", "reload_gg", "Keys_lagoon_170");
			Whr_UpdateWeather();
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); // мотаем время
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "reload", "reload1");
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "reload", "reload1");
			sld = CharacterFromID("Daniel_Monbar");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "reload", "reload1");
			sld = CharacterFromID("Rimalier");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "reload", "reload1");
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "reload", "reload1");
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "goto", "goto_marso");
			for (i = 1; i <= 10; i++)
			{
				int Live_Team_7 = GetCharacterIndex("Keys_lagoon_MaracaiboSailor_Jungle_" + i);
				if (Live_Team_7 != -1)
				{
					sld = &characters[Live_Team_7];
					if (!LAi_IsDead(sld))
					{
						sld.lifeday = 0;
					}
				}
			}
			for (i = 1; i <= 5; i++)
			{
				Model = LAi_GetBoardingModel(pchar, &sTemp);
				sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_MaracaiboSailor_Shore_" + i, Model, "man", sTemp, CB_Rank(), PIRATE, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade3", "pistol2", 30);
				LAi_SetActorType(sld);
				ChangeCharacterAddressGroup(sld, "Shore_ship3", "reload", "reload1");
			}
			sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_MaracaiboSailor_Shore_6", "citiz_36", "man", sTemp, CB_Rank(), PIRATE, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade3", "pistol2", 30);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "goto", "goto_ohr1");
			sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_MaracaiboSailor_Shore_7", Model, "man", sTemp, CB_Rank(), PIRATE, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "blade3", "pistol2", 30);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "goto", "goto_ohr2");
		break;

		case "Keys_lagoon_170":
			TEV.Music.QuestMusic = "Music\Special\Quest\PDM\Fight_01.mp3";
			PlayMusic(TEV.Music.QuestMusic, 1000);
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			TEV.StopTimeScale = true; // запрет ускорения
			DoQuestCheckDelay("Off_Interface", 0.2);
			QuestMovieLockPlayer(); // окаемки вкл
			locCameraFromToPos(26.763, 4.196, -10.490, false, 22.485, 3.053, -22.230);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "goto", "goto1", "", -1);
			sld = CharacterFromID("Keys_lagoon_MaracaiboSailor_Shore_6");
			LAi_ActorTurnToLocator(sld, "goto", "goto_marso");
			sld = CharacterFromID("Keys_lagoon_MaracaiboSailor_Shore_7");
			LAi_ActorTurnToLocator(sld, "goto", "goto_marso");
			sld = CharacterFromID("Fransua_Olone");
			LAi_ActorRunToLocator(sld, "goto", "goto1", "", -1);
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorRunToLocator(sld, "goto", "goto1", "", -1);
			sld = CharacterFromID("Daniel_Monbar");
			LAi_ActorRunToLocator(sld, "goto", "goto1", "", -1);
			sld = CharacterFromID("Rimalier");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "goto", "goto1", "", -1);
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorRunToLocator(sld, "goto", "goto1", "", -1);
			for (i = 1; i <= 5; i++)
			{
				sld = CharacterFromID("Keys_lagoon_MaracaiboSailor_Shore_" + i);
				LAi_ActorRunToLocator(sld, "goto", "goto1", "", -1);
			}
			DoQuestCheckDelay("Keys_lagoon_171", 5);
		break;

		case "Keys_lagoon_171":
			for (i = 1; i <= 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Shore_Keys_Soldiers_" + i, "sold_spa_" + (1 + rand(14)), "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				ChangeCharacterAddressGroup(sld, "Shore_ship3", "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorAttack(sld, pchar, "");
			}
			DoQuestCheckDelay("Keys_lagoon_172", 3);
		break;

		case "Keys_lagoon_172":
			locCameraFromToPos(45.081, 5.637, 16.726, true, 12.811, 4.733, 105.585);
			DoQuestCheckDelay("Keys_lagoon_173", 1.5);
		break;

		case "Keys_lagoon_173":
			SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
			CreateLocationParticlesXZ("Ship_cannon_fire", "goto", "shot1", -1.0, 0, 0, "");
			CreateLocationParticlesXZ("blast_inv", "goto", "shot1", -1.0, 0, 0, "");
			PlaySound("Sea Battles\vistrel_orudiya_004.wav");
			for (i = 1; i <= 10; i++)
			{
				sld = CharacterFromID("Shore_Keys_Soldiers_" + i);
				ChangeCharacterAddressGroup(sld, "Shore_ship3", "reload", "reload1");
			}
			DoQuestCheckDelay("Keys_lagoon_174", 0.5);
		break;

		case "Keys_lagoon_174":
			locCameraFromToPos(41.392, 5.865, -4.561, true, 25.534, 3.790, -18.919);
			DoQuestCheckDelay("Keys_lagoon_175", 0.5);
		break;

		case "Keys_lagoon_175":
			PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
			SetCameraShake(0.5, 5.0, 3.0, 1.2, 0.5, true, false, CAM_EASING_CUBE);
			CreateLocationParticlesXZ("ShipExplode", "officers", "reload1_3", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
			for (i = 1; i <= 10; i++)
			{
				sld = CharacterFromID("Shore_Keys_Soldiers_" + i);
				LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
				LAi_KillCharacter(sld);
			}
			for (i = 1; i <= 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Shore_Keys_Soldier_" + i, "sold_spa_" + (1 + rand(14)), "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				ChangeCharacterAddressGroup(sld, "Shore_ship3", "reload", "reload1");
				LAi_SetActorType(sld);
				LAi_ActorAttack(sld, pchar, "");
			}
			for (i = 1; i <= 5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Shore_Keys_Soldier_" + (10 + i), "sold_spa_" + (1 + rand(14)), "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				ChangeCharacterAddressGroup(sld, "Shore_ship3", "reload", "reload_gg");
				LAi_SetActorType(sld);
				LAi_ActorAttack(sld, pchar, "");
			}
			DoQuestCheckDelay("Keys_lagoon_176", 1.5);
		break;

		case "Keys_lagoon_176":
			locCameraFromToPos(-36.499, 0.982, 88.005, true, -9.141, 4.099, 106.980);
			DoQuestCheckDelay("Keys_lagoon_177", 1);
		break;

		case "Keys_lagoon_177":
			CreateLocationParticlesXZ("Ship_cannon_fire", "goto", "shot2", -1.0, 0, 0, "");
			CreateLocationParticlesXZ("blast_inv", "goto", "shot2", -1.0, 0, 0, "");
			SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
			PlaySound("Sea Battles\vistrel_orudiya_004.wav");
			DoQuestCheckDelay("Keys_lagoon_178", 0.5);
		break;

		case "Keys_lagoon_178":
			CreateLocationParticlesXZ("Ship_cannon_fire", "goto", "shot3", -1.0, 0, 0, "");
			CreateLocationParticlesXZ("blast_inv", "goto", "shot3", -1.0, 0, 0, "");
			SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
			PlaySound("Sea Battles\vistrel_orudiya_004.wav");
			DoQuestCheckDelay("Keys_lagoon_179", 0.5);
			for (i = 1; i <= 15; i++)
			{
				sld = CharacterFromID("Shore_Keys_Soldier_" + i);
				ChangeCharacterAddressGroup(sld, "Shore_ship3", "reload", "reload_gg");
			}
		break;

		case "Keys_lagoon_179":
			locCameraFromToPos(29.569, 2.148, -7.130, true, 22.346, 3.755, -21.819);
			DoQuestCheckDelay("Keys_lagoon_180", 0.5);
		break;

		case "Keys_lagoon_180":
			PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
			SetCameraShake(0.5, 5.0, 3.0, 1.2, 0.5, true, false, CAM_EASING_CUBE);
			CreateLocationParticlesXZ("ShipExplode", "officers", "reload1_3", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
			CreateLocationParticlesXZ("ShipExplode", "reload", "reload_gg", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
			for (i = 1; i <= 15; i++)
			{
				sld = CharacterFromID("Shore_Keys_Soldier_" + i);
				LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
				LAi_KillCharacter(sld);
			}
			DoQuestCheckDelay("Keys_lagoon_181", 3.5);
		break;

		case "Keys_lagoon_181":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "", "");
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "goto", "goto_olone");
			LAi_ActorTurnToCharacter(sld, characterFromID("Etien_Marso"));
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "goto", "goto_mary");
			LAi_ActorTurnToCharacter(sld, characterFromID("Rimalier"));
			sld = CharacterFromID("Daniel_Monbar");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "goto", "goto_monbar");
			LAi_ActorTurnToCharacter(sld, characterFromID("Etien_Marso"));
			sld = CharacterFromID("Rimalier");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "goto", "goto_rimalier");
			LAi_ActorTurnToCharacter(sld, characterFromID("Mary_Belfler"));
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore_ship3", "goto", "goto_bask");
			LAi_ActorTurnToLocator(sld, "goto", "goto_gg");
			ChangeCharacterAddressGroup(pchar, "Shore_ship3", "goto", "goto_gg");
			LAi_ActorTurnToCharacter(pchar, characterFromID("Mishel_le_Bask"));
			DoQuestCheckDelay("Keys_lagoon_182", 3.5);
			for (i = 1; i <= 5; i++)
			{
				sld = CharacterFromID("Keys_lagoon_MaracaiboSailor_Shore_" + i);
				LAi_SetActorType(sld);
				LAi_ActorTurnToCharacter(sld, characterFromID("Etien_Marso"));
			}
		break;

		case "Keys_lagoon_182":
			locCameraFollow();
			DoQuestCheckDelay("Keys_lagoon_183", 1.5);
		break;

		case "Keys_lagoon_183":
			LAi_SetPlayerType(pchar);
			QuestMovieUnLockPlayer(); // окаемки выкл
			StartBattleLandInterface(); // вкл интерфейс
			sld = CharacterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_73";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_195":
			LAi_SetActorType(pchar);
			n = FindLocation("Gibraltar_ExitTown");
			Locations[n].models.always.barricaded = "TownExitN_Barricade";
			Locations[n].models.always.barricaded.tech = "DLightModel";
			locations[n].models.day.charactersPatch = "TownExitN_Patch_Barricade";
			Locations[n].QuestlockWeather = "Storm03_add";
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_294"), "Reload_To_Location", 0.1, 3.0);
			SetLaunchFrameReloadLocationParam("Gibraltar_ExitTown", "reload", "reload2_back", "Keys_lagoon_196");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 30); // мотаем время
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "rld", "loc0");
			sld = CharacterFromID("Daniel_Monbar");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "rld", "loc1");
			sld = CharacterFromID("Rimalier");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "rld", "loc3");
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "rld", "loc2");
			sld = GetCharacter(NPC_GenerateCharacter("Miskito_Mush_1", "Miskito_1_mush", "man", "mushketer", CB_Rank(), PIRATE, -1, false));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
			LAi_SetActorType(sld);
			Lai_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "item", "item13");
			sld = GetCharacter(NPC_GenerateCharacter("Miskito_Mush_2", "Miskito_2_mush", "man", "mushketer", CB_Rank(), PIRATE, -1, false));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
			LAi_SetActorType(sld);
			Lai_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "item", "item13");
			sld = GetCharacter(NPC_GenerateCharacter("Miskito_Mush_3", "Miskito_3_mush", "man", "mushketer", CB_Rank(), PIRATE, -1, false));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
			LAi_SetActorType(sld);
			Lai_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "item", "item13");
			sld = GetCharacter(NPC_GenerateCharacter("Miskito_Mush_4", "Miskito_4_mush", "man", "mushketer", CB_Rank(), PIRATE, -1, false));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
			LAi_SetActorType(sld);
			Lai_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "item", "item13");
			for (i = 1; i <= 11; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Officer_ExitTown_War_" + i, "officer_" + i, "man", "man", CB_Rank(), PIRATE, -1, true));
				sld.Buccaneer = true;
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "rld", "loc" + i);
				LAi_SetActorType(sld);
				Lai_SetHP(sld, 300.0, 300.0);
			}
			for (i = 1; i <= 16; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Defenders_Gibraltar_Spa_" + i, "sold_spa_" + i, "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				LAi_SetActorType(sld);
				Lai_SetHP(sld, 300.0, 300.0);
				ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "goto", "goto14");
			}
			for (i = 1; i <= 8; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Defenders_Gibraltar_Spa_" + (16 + i), "spa_mush_" + i, "man", "mushketer", 30, SPAIN, -1, false));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				LAi_SetActorType(sld);
				Lai_SetHP(sld, 300.0, 300.0);
				ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "goto", "goto14");
			}
			sld = GetCharacter(NPC_GenerateCharacter("Defenders_Gibraltar_Spa_26", "sold_spa_5", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
			LAi_SetActorType(sld);
			Lai_SetHP(sld, 300.0, 300.0);
			ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "goto", "goto14");
		break;

		case "Keys_lagoon_196":
			TEV.Music.QuestMusic = "Music\Special\Quest\PDM\Fight_01.mp3";
			PlayMusic(TEV.Music.QuestMusic, 1000);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_1");
			TeleportCharacterToPosAy(sld, -2.75, 0.28, -3.64, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_2");
			TeleportCharacterToPosAy(sld, -3.89, 0.15, -0.83, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_3");
			TeleportCharacterToPosAy(sld, -4.10, -0.16, 1.34, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_4");
			TeleportCharacterToPosAy(sld, -4.11, 0.09, 6.32, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_5");
			TeleportCharacterToPosAy(sld, -3.76, 0.04, 8.56, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_7");
			TeleportCharacterToPosAy(sld, 1.32, 0.04, 10.10, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_20");
			TeleportCharacterToPosAy(sld, 4.58, 0.04, 7.32, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_9");
			TeleportCharacterToPosAy(sld, 4.25, 0.04, 2.88, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_21");
			TeleportCharacterToPosAy(sld, 3.73, 0.04, 1.08, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_11");
			TeleportCharacterToPosAy(sld, 1.438, 3.183, 12.276, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_22");
			TeleportCharacterToPosAy(sld, 13.07, 4.40, 4.70, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_13");
			TeleportCharacterToPosAy(sld, 13.07, 4.40, 7.30, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_23");
			TeleportCharacterToPosAy(sld, 13.07, 4.40, 9.60, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_15");
			TeleportCharacterToPosAy(sld, 13.75, 4.40, -5.50, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_24");
			TeleportCharacterToPosAy(sld, 13.45, 4.40, -13.00, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_16");
			TeleportCharacterToPosAy(sld, 13.45, 4.40, -15.60, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_19");
			TeleportCharacterToPosAy(sld, 13.75, 4.40, -8.00, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_17");
			TeleportCharacterToPosAy(sld, -6.609, 3.283, 4.036, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_18");
			TeleportCharacterToPosAy(sld, 7.364, 3.183, -6.654, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_10");
			TeleportCharacterToPosAy(sld, -0.88, 0.08, -2.40, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_8");
			TeleportCharacterToPosAy(sld, -1.40, 0.04, 0.10, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_14");
			TeleportCharacterToPosAy(sld, -1.69, 0.04, 7.41, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_12");
			TeleportCharacterToPosAy(sld, 5.25, 0.04, 5.57, -1.50);
			sld = CharacterFromID("Defenders_Gibraltar_Spa_6");
			TeleportCharacterToPosAy(sld, 6.67, 0.04, -3.77, -1.50);
			sld = CharacterFromID("Miskito_Mush_1");
			TeleportCharacterToPosAy(sld, -22.40, 1.63, 24.38, -1.50);
			LAi_ActorTurnToLocator(sld, "rld", "aloc5");
			sld = CharacterFromID("Miskito_Mush_2");
			TeleportCharacterToPosAy(sld, -20.96, 1.40, 25.82, -1.50);
			LAi_ActorTurnToLocator(sld, "rld", "aloc5");
			sld = CharacterFromID("Miskito_Mush_3");
			TeleportCharacterToPosAy(sld, -19.45, 1.27, 27.42, -1.50);
			LAi_ActorTurnToLocator(sld, "rld", "aloc5");
			sld = CharacterFromID("Miskito_Mush_4");
			TeleportCharacterToPosAy(sld, -17.46, 1.07, 28.32, -1.50);
			LAi_ActorTurnToLocator(sld, "rld", "aloc5");
			sld = CharacterFromID("Daniel_Monbar");
			TeleportCharacterToPosAy(sld, -18.34, 1.16, 23.60, -1.50);
			LAi_ActorTurnToLocator(sld, "rld", "aloc5");
			DoQuestCheckDelay("Off_Interface", 0.2);
			QuestMovieLockPlayer(); // окаемки вкл
			locCameraFlyToPositionLookToPoint(-13.061, 2.513, -2.088, -10.817, 2.321, 13.972, 6.919, 1.519, 2.184, -1.0, 1200);
			DoQuestCheckDelay("Keys_lagoon_197", 10);
		break;

		case "Keys_lagoon_197":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_198", 3.5);
		break

		case "Keys_lagoon_198":
			locCameraResetState();
			locCameraFlyToPositionLookToPoint(-10.626, 2.286, 0.684, -39.450, 3.998, 1.810, 1.434, 1.828, 0.349, -1.0, 1200);
			DoQuestCheckDelay("Keys_lagoon_199", 10);
		break;

		case "Keys_lagoon_199":
			LAi_FadeEx(2.0, 2.0, 2.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_200", 3.5);
		break

		case "Keys_lagoon_200":
			locCameraResetState();
			locCameraFromToPos(-15.803, 4.002, 5.934, true, -7.201, 3.236, 4.026);
			DoQuestCheckDelay("Keys_lagoon_201", 2.5);
		break;

		case "Keys_lagoon_201":
			PlaySound("People Fight\MusketFire.wav");
			sld = characterFromId("Defenders_Gibraltar_Spa_11");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			BeginChangeCharacterActions(sld);
			sld.actions.dead.d1 = "death_7";
			sld.actions.dead.d2 = "death_7";
			EndChangeCharacterActions(sld);
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Keys_lagoon_202", 1);
		break;

		case "Keys_lagoon_202":
			PlaySound("People Fight\MusketFire.wav");
			sld = characterFromId("Defenders_Gibraltar_Spa_17");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Keys_lagoon_203", 1);
		break;

		case "Keys_lagoon_203":
			PlaySound("People Fight\MusketFire.wav");
			sld = characterFromId("Defenders_Gibraltar_Spa_18");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Keys_lagoon_204", 1);
		break;

		case "Keys_lagoon_204":
			locCameraFromToPos(-14.067, 3.316, 17.207, false, -18.472, 1.304, 23.870);
			DoQuestCheckDelay("Keys_lagoon_205", 1);
		break;

		case "Keys_lagoon_205":
			QuestMovieUnLockPlayer(); // окаемки выкл
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Daniel_Monbar");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Monbar_71";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_206":
			InterfaceStates.Buttons.Save.enable = 1; // можно сохраняться
			DeleteAttribute(&TEV, "StopTimeScale"); // можно ускоряться
			MakeQuestAutoSave();
			LAi_SetFightMode(pchar, true);
			locCameraFollowEx(true);
			StartBattleLandInterface(); // вкл интерфейс
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = CharacterFromID("Daniel_Monbar");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = CharacterFromID("Rimalier");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i = 1; i <= 4; i++)
			{
				sld = CharacterFromID("Miskito_Mush_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i = 1; i <= 11; i++)
			{
				sld = CharacterFromID("Officer_ExitTown_War_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}

			for (i = 1; i <= 26; i++)
			{
				if (i == 13 || i == 15 || i == 16 || i == 19 || i == 22 || i == 23 || i == 24 || i == 25) continue;

				sld = CharacterFromID("Defenders_Gibraltar_Spa_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Defenders_Gibraltar_Group");
			}
			LAi_group_SetRelation("Defenders_Gibraltar_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Defenders_Gibraltar_Group", LAI_GROUP_PLAYER, true);
			DoQuestCheckDelay("Keys_lagoon_211", 0.2);
			DoQuestCheckDelay("Keys_lagoon_207", 2);
		break;

		case "Keys_lagoon_207":
			CreateLocationParticles("cancloud_fire_big", "effect", "effect2", 0, -90, -10, "");
			SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
			PlaySound("Sea Battles\vistrel_orudiya_004.wav");
			CreateLocationParticlesXZ("ShipExplode", "rld", "loc11", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
			sld = characterFromId("Officer_ExitTown_War_6");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			sld = characterFromId("Officer_ExitTown_War_7");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			sld = characterFromId("Officer_ExitTown_War_10");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			sld = characterFromId("Officer_ExitTown_War_11");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Keys_lagoon_208", 2);
		break;

		case "Keys_lagoon_208":
			PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
			SetCameraShake(0.5, 5.0, 3.0, 1.2, 0.5, true, false, CAM_EASING_CUBE);
			CreateLocationParticlesXZ("ShipExplode", "effect", "effect1", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
			CreateLocationParticlesLoopedSound("shipfire", "effect", "effect1", 0.0, 0.0, 0, "fortfire");
			sld = characterFromId("Defenders_Gibraltar_Spa_22");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			sld = characterFromId("Defenders_Gibraltar_Spa_13");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Keys_lagoon_209", 2);
		break;

		case "Keys_lagoon_209":
			PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
			SetCameraShake(0.5, 5.0, 3.0, 1.2, 0.5, true, false, CAM_EASING_CUBE);
			CreateLocationParticlesXZ("ShipExplode", "effect", "effect2", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
			CreateLocationParticlesLoopedSound("shipfire", "effect", "effect2", 0.0, 0.0, 0, "fortfire");
			sld = characterFromId("Defenders_Gibraltar_Spa_23");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Keys_lagoon_210", 10);
			DoQuestCheckDelay("Keys_lagoon_209_1", 6);
		break;

		case "Keys_lagoon_209_1":
			PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
			CreateParticleSystem("ShipExplode", -6.143, 5.622, 3.993, 0.0, 0.0, 0.0, 0);
			CreateParticleSystem("shipfire", -6.143, 5.622, 3.993, 0.0, 0.0, 0.0, 0);
			SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
		break;

		case "Keys_lagoon_210":
			PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
			SetCameraShake(0.5, 5.0, 3.0, 1.2, 0.5, true, false, CAM_EASING_CUBE);
			CreateLocationParticlesXZ("ShipExplode", "effect", "effect3", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
			CreateLocationParticlesLoopedSound("shipfire", "effect", "effect3", 0.0, 0.0, 0, "fortfire");
			CreateLocationParticlesXZ("ShipExplode", "effect", "effect4", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");
			CreateLocationParticlesLoopedSound("shipfire", "effect", "effect4", 0.0, 0.0, 0, "fortfire");
			sld = characterFromId("Defenders_Gibraltar_Spa_15");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			sld = characterFromId("Defenders_Gibraltar_Spa_24");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			sld = characterFromId("Defenders_Gibraltar_Spa_16");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			sld = characterFromId("Defenders_Gibraltar_Spa_19");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Keys_lagoon_210_1", 4);
		break;

		case "Keys_lagoon_210_1":
			PlaySound("RMM\Gunsfire\vzriv_pogreb_005.wav");
			CreateParticleSystem("ShipExplode", 2.843, 1.388, 6.427, 0.0, 0.0, 0.0, 0);
			CreateParticleSystem("shipfire", 2.843, 1.388, 6.427, 0.0, 0.0, 0.0, 0);
			SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
		break;

		case "Keys_lagoon_211":
			iTemp = 0;

			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = &characters[i];
				if (!CheckAttribute(sld, "chr_ai.group")) continue;
				if (sld.chr_ai.group != "Defenders_Gibraltar_Group") continue;
				if (LAi_IsDead(sld)) continue;

				iTemp++;
			}

			if (iTemp > 3)
			{
				DoQuestCheckDelay("Keys_lagoon_211", 0.2);
				break;
			}

			if (CheckAttribute(pchar, "questTemp.AoP.KeysLagoonGibraltarVolley")) break;
			pchar.questTemp.AoP.KeysLagoonGibraltarVolley = true;

			DoQuestCheckDelay("Keys_lagoon_212", 0.1);
		break;

		case "Keys_lagoon_212":
			for (i = 1; i <= 6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Gibraltar_Volley_Spa_" + i, "sold_spa_" + i, "man", "man", CB_Rank(), SPAIN, -1, true));
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				LAi_SetActorType(sld);
				Lai_SetHP(sld, 300.0, 300.0);
				ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "reload", "reload1_back");
				LAi_group_MoveCharacter(sld, "Defenders_Gibraltar_Group");
			}

			DoQuestCheckDelay("Keys_lagoon_213", 0.4);
		break;

		case "Keys_lagoon_213":
			SetCameraShake(1.2, 15.0, 0.1, 0.1, 0.1, true, false, CAM_EASING_SMOOTH_STEP);
			PlaySound("Sea Battles\vistrel_orudiya_004.wav");
			CreateLocationParticlesXZ("ShipExplode", "reload", "reload1_back", 0, 0, 0, "Sea Battles\vistrel_orudiya_004.wav");

			for (i = 1; i <= 6; i++)
			{
				sld = CharacterFromID("Gibraltar_Volley_Spa_" + i);
				LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
				LAi_KillCharacter(sld);
			}

			DoQuestCheckDelay("Keys_lagoon_214", 5.0);
		break;

		case "Keys_lagoon_214":
			for (i = 1; i <= 8; i++)
			{
				if (i <= 5)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Gibraltar_Reinforce_Spa_" + i, "sold_spa_" + i, "man", "man", CB_Rank(), SPAIN, -1, true));
					FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Gibraltar_Reinforce_Spa_" + i, "spa_mush_" + (i - 5), "man", "mushketer", CB_Rank(), SPAIN, -1, false));
					FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				}

				Lai_SetHP(sld, 300.0, 300.0);
				ChangeCharacterAddressGroup(sld, "Gibraltar_ExitTown", "reload", "reload1_back");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Defenders_Gibraltar_Group");
			}
			LAi_group_SetCheck("Defenders_Gibraltar_Group", "Keys_lagoon_215");
		break;

		case "Keys_lagoon_215":
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = &characters[i];
				if (LAi_IsDead(sld)) continue;
				if (!CheckAttribute(sld, "location")) continue;
				if (sld.location != "Gibraltar_ExitTown") continue;
				if (!CheckAttribute(sld, "chr_ai.group")) continue;
				if (sld.chr_ai.group != LAI_GROUP_PLAYER) continue;
				if (sld.id == pchar.id) continue;

				sld.quest.AoP.KeysLagoonGibraltarAlly = true;

				if (sld.id == "Rimalier" && IsOfficer(sld))
				{
					LAi_SetOfficerType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					continue;
				}

				if (sld.id != "Mishel_le_Bask")
				{
					LAi_SetCitizenType(sld);
					LAi_CharacterDisableDialog(sld);
				}
			}
			LAi_group_Delete("Defenders_Gibraltar_Group");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_88";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_216":
			n = FindLocation("Gibraltar_Town");
			Locations[n].QuestlockWeather = "Storm03_add";
			SetLocationCapturedState("Gibraltar_town", true); // убрать всех
			chrDisableReloadToLocation = false; // открыть локацию
			LocatorReloadEnterDisable("Gibraltar_ExitTown", "reload2_back", true); // закрыть выход
			QuestPointerToLoc("Gibraltar_ExitTown", "reload", "reload1_back"); // поставить поинт
			pchar.quest.Keys_lagoon_GibraltarTownBattle.win_condition.l1 = "location";
			pchar.quest.Keys_lagoon_GibraltarTownBattle.win_condition.l1.location = "Gibraltar_town";
			pchar.quest.Keys_lagoon_GibraltarTownBattle.win_condition = "Keys_lagoon_217";
		break;

		case "Keys_lagoon_217":
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = &characters[i];
				if (!CheckAttribute(sld, "quest.AoP.KeysLagoonGibraltarAlly")) continue;

				if (sld.id == "Mishel_le_Bask")
				{
					DeleteAttribute(sld, "quest.AoP.KeysLagoonGibraltarAlly");
					continue;
				}
				if (sld.id == "Daniel_Monbar")
				{
					DeleteAttribute(sld, "quest.AoP.KeysLagoonGibraltarAlly");
					continue;
				}
				if (sld.id == "Fransua_Olone")
				{
					DeleteAttribute(sld, "quest.AoP.KeysLagoonGibraltarAlly");
					continue;
				}
				if (sld.id == "Rimalier")
				{
					DeleteAttribute(sld, "quest.AoP.KeysLagoonGibraltarAlly");
					continue;
				}

				ChangeCharacterAddressGroup(sld, "none", "", "");
				DeleteAttribute(sld, "quest.AoP.KeysLagoonGibraltarAlly");
			}

			chrDisableReloadToLocation = true;

			sld = CharacterFromID("Mishel_le_Bask");
			LAi_LoginInCaptureTown(sld, true);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "Gibraltar_town", "reload", "gate_back");

			sld = CharacterFromID("Fransua_Olone");
			LAi_LoginInCaptureTown(sld, true);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "Gibraltar_town", "reload", "gate_back");

			sld = CharacterFromID("Daniel_Monbar");
			LAi_LoginInCaptureTown(sld, true);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			ChangeCharacterAddressGroup(sld, "Gibraltar_town", "reload", "gate_back");

			sld = CharacterFromID("Rimalier");
			LAi_LoginInCaptureTown(sld, true);
			if (IsOfficer(sld))
			{
				LAi_SetOfficerType(sld);
			}
			else
			{
				LAi_SetWarriorType(sld);
				ChangeCharacterAddressGroup(sld, "Gibraltar_town", "reload", "gate_back");
			}
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			for (i = 1; i <= 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_GibraltarPirate_" + i, "pirate_" + i, "man", "man", CB_Rank(), PIRATE, -1, true));
				sld.Buccaneer = true;
				Lai_SetHP(sld, 350.0, 350.0);
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
				LAi_SetWarriorType(sld);
				LAi_LoginInCaptureTown(sld, true);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "Gibraltar_town", "goto", "goto" + i);
			}

			for (i = 1; i <= 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_GibraltarMush_" + i, "mush_ctz_" + i, "man", "mushketer", CB_Rank(), PIRATE, -1, false));
				sld.Buccaneer = true;
				FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
				Lai_SetHP(sld, 350.0, 350.0);
				LAi_SetWarriorType(sld);
				LAi_LoginInCaptureTown(sld, true);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "Gibraltar_town", "goto", "goto" + (10 + i));
			}

			for (i = 1; i <= 30; i++)
			{
				if (i <= 18)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_GibraltarTownSpa_" + i, "sold_spa_" + (1 + rand(7)), "man", "man", CB_Rank(), SPAIN, -1, true));
					FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
					Lai_SetHP(sld, 350.0, 350.0);
					LAi_LoginInCaptureTown(sld, true);
				}
				else
				{
					if (i <= 24)
					{
						sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_GibraltarTownSpa_" + i, "off_spa_" + (1 + rand(5)), "man", "man", CB_Rank() + 3, SPAIN, -1, true));
						FantomMakeCoolFighter(sld, CB_Rank() + 3, CB_Fencing() + 10, CB_Pistol() + 10, "blade10", "pistol2", 30);
						Lai_SetHP(sld, 350.0, 350.0);
						LAi_LoginInCaptureTown(sld, true);
					}
					else
					{
						sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_GibraltarTownSpa_" + i, "spa_mush_2", "man", "mushketer", CB_Rank(), SPAIN, -1, false));
						FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "unarmed", "mushket", 20);
						Lai_SetHP(sld, 350.0, 350.0);
						LAi_LoginInCaptureTown(sld, true);
					}
				}

				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "Gibraltar_Town_Spa_Group");

				if (i <= 24)
				{
					ChangeCharacterAddressGroup(sld, "Gibraltar_town", "goto", "goto" + i);
				}
				else
				{
					ChangeCharacterAddressGroup(sld, "Gibraltar_town", "patrol", "patrol" + (i - 24));
				}
			}

			LAi_group_SetRelation("Gibraltar_Town_Spa_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Gibraltar_Town_Spa_Group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Gibraltar_Town_Spa_Group", "Keys_lagoon_218");
		break;

		case "Keys_lagoon_218":
			sld = CharacterFromID("Mary_Belfler");
			ChangeCharacterAddressGroup(sld, "Gibraltar_town", "reload", "gate_back");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Etien_Marso"), "", -1);
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Gibraltar_town", "reload", "gate_back");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("blaze"), "", -1);
			LAi_group_Delete("Gibraltar_Town_Spa_Group");
			LAi_grp_alarmactive = false; // конец тревоги
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(pchar, false);
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = &characters[i];
				if (LAi_IsDead(sld)) continue;
				if (!CheckAttribute(sld, "location")) continue;
				if (sld.location != "Gibraltar_town") continue;
				if (!CheckAttribute(sld, "chr_ai.group")) continue;
				if (sld.chr_ai.group != LAI_GROUP_PLAYER) continue;
				if (sld.id == pchar.id) continue;
				if (sld.id == "Mishel_le_Bask") continue;

				if (sld.id == "Rimalier" && IsOfficer(sld))
				{
					LAi_SetOfficerType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					continue;
				}

				LAi_SetCitizenType(sld);
				LAi_CharacterDisableDialog(sld);
			}
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_93";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_219":
			sld = CharacterFromID("Etien_Marso");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_11";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
		break;

		case "Keys_lagoon_220":
			for (i = 0; i < MAX_LOCATIONS; i++)
			{
				if (CheckAttribute(&Locations[i], "townsack"))
				{
					if (Locations[i].townsack == "Gibraltar")
					{
						Locations[i].QuestlockWeather = "Storm03_add";
					}
				}

				if (CheckAttribute(&Locations[i], "fastreload"))
				{
					if (Locations[i].fastreload == "Gibraltar")
					{
						Locations[i].QuestlockWeather = "Storm03_add";
					}
				}
			}
			Whr_UpdateWeather();
			chrDisableReloadToLocation = false; // открыть локацию
			QuestPointerToLoc("Gibraltar_town", "reload", "reload3_back"); // поставить поинт
			sld = CharacterFromID("Etien_Marso");
			LAi_SetFreeFighter(sld);
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetFreeFighter(sld);
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("Maracaibo_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			LAi_SetImmortal(sld, false);
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Gibraltar_townhall", "sit", "sit1");

			sld = GetCharacter(NPC_GenerateCharacter("Defenders_Huber_1", "sold_spa_5", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
			LAi_SetActorType(sld);
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "Gibraltar_townhall", "goto", "goto2");
			sld = GetCharacter(NPC_GenerateCharacter("Defenders_Huber_2", "sold_spa_12", "man", "man", CB_Rank(), SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing() + rand(10) - 5, CB_Pistol() + rand(10) - 5, "blade10", "pistol2", 20);
			LAi_SetActorType(sld);
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "Gibraltar_townhall", "goto", "goto2");
			pchar.quest.gibraltar_townhall_final.win_condition.l1 = "location";
			pchar.quest.gibraltar_townhall_final.win_condition.l1.location = "Gibraltar_townhall";
			pchar.quest.gibraltar_townhall_final.win_condition = "Keys_lagoon_221";
		break;

		case "Keys_lagoon_221":
			InterfaceStates.Buttons.Save.enable = 0; // нельзя сохраняться
			TEV.StopTimeScale = true; // запрет ускорения
			DoQuestCheckDelay("Off_Interface", 0.2);
			QuestMovieLockPlayer(); // окаемки вкл
			sld = CharacterFromID("Defenders_Huber_1");
			TeleportCharacterToPosAy(sld, 2.42, 0.61, 1.37, -1.50);
			sld = CharacterFromID("Defenders_Huber_2");
			TeleportCharacterToPosAy(sld, 2.35, 0.61, -1.43, -1.50);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto_gg", "", -1);
			sld = CharacterFromID("Mishel_le_Bask");
			ChangeCharacterAddressGroup(sld, "Gibraltar_townhall", "goto", "goto_bask");
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "goto", "goto_bask2", "Keys_lagoon_221_bask_1", -1);
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Gibraltar_townhall", "goto", "goto_marso");
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "goto", "goto_marso2", "Keys_lagoon_221_marso_1", -1);
		break;

		case "Keys_lagoon_221_bask_1":
			sld = CharacterFromID("Defenders_Huber_1");
			LAi_ActorAttack(sld, pchar, "");
			sld = CharacterFromID("Defenders_Huber_2");
			LAi_ActorAttack(sld, pchar, "");
			sld = characterFromID("Mishel_le_Bask");
			LAi_ActorTurnToCharacter(sld, characterFromID("Defenders_Huber_1"));
			LAi_ActorAnimation(sld, "Shot", "Keys_lagoon_221_bask_2", 1);
		break;

		case "Keys_lagoon_221_bask_2":
			sld = characterFromId("Defenders_Huber_1");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
		break;

		case "Keys_lagoon_221_marso_1":
			sld = characterFromID("Etien_Marso");
			LAi_ActorTurnToCharacter(sld, characterFromID("Defenders_Huber_2"));
			LAi_ActorAnimation(sld, "Shot", "Keys_lagoon_221_marso_2", 1);
		break;

		case "Keys_lagoon_221_marso_2":
			sld = characterFromId("Defenders_Huber_2");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_KillCharacter(sld);
			DoQuestCheckDelay("Keys_lagoon_222", 2.0);
		break;

		case "Keys_lagoon_222":
			LAi_FadeEx(1.0, 1.0, 1.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_223", 1.5);
		break;

		case "Keys_lagoon_223":
			sld = characterFromID("Etien_Marso");
			LAi_CharacterEnableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Gibraltar_townhall", "goto", "goto_marso3");
			LAi_ActorTurnToCharacter(sld, characterFromID("Maracaibo_mayor"));
			sld = characterFromID("Mishel_le_Bask");
			LAi_CharacterEnableDialog(sld);
			ChangeCharacterAddressGroup(sld, "Gibraltar_townhall", "goto", "goto_bask3");
			LAi_ActorTurnToCharacter(sld, characterFromID("Maracaibo_mayor"));
			LAi_SetActorType(pchar);
			ChangeCharacterAddressGroup(pchar, "Gibraltar_townhall", "goto", "goto_gg");
			LAi_ActorTurnToCharacter(pchar, characterFromID("Maracaibo_mayor"));
			DoQuestCheckDelay("Keys_lagoon_224", 3);
		break;

		case "Keys_lagoon_224":
			QuestMovieUnLockPlayer();
			StartBattleLandInterface();
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Maracaibo_Mayor");
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_1"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_21"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_2"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_22"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_3"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_23", sld.name));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", "...");
			AoP_NPCDialogAddLine("Mishel_le_Bask", "...");
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_4"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_24"));
			AoP_NPCDialogLaunch("Maracaibo_Mayor", "Mishel_le_Bask", "Keys_lagoon_Res_Ransom");
		break;

		case "Keys_lagoon_228_8":
			LAi_SetActorType(pchar);
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_11"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_25"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Etien_Marso", "Keys_lagoon_228_9");
		break;

		case "Keys_lagoon_228_9":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_5"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_26"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Maracaibo_Mayor", "Keys_lagoon_228_10");
		break;

		case "Keys_lagoon_228_10":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_12"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_27"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Etien_Marso", "Keys_lagoon_228_11");
		break;

		case "Keys_lagoon_228_11":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_99";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_230":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_13"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_28"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_14"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Etien_Marso", "Keys_lagoon_231");
		break;

		case "Keys_lagoon_231":
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Maracaibo_Mayor");
			sld.Dialog.CurrentNode = "Keys_lagoon_3";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_237":
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Maracaibo_Mayor");
			sld.Dialog.CurrentNode = "Keys_lagoon_16";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_238_1":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_15"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_6"));
			AoP_NPCDialogLaunch("Maracaibo_Mayor", "Etien_Marso", "Keys_lagoon_239");
		break;

		case "Keys_lagoon_239":
			EndBattleLandInterface(); // откл интерфейс
			LAi_SetActorType(pchar);
			LAi_FadeEx(3.0, 2.0, 1.0, "", "", "");
			DoQuestCheckDelay("Keys_lagoon_240", 5);
		break;

		case "Keys_lagoon_240":
			chrDisableReloadToLocation = true; // закрыть локацию
			QuestPointerDelLoc("Gibraltar_town", "reload", "reload3_back"); // удалить поинт
			DoQuestReloadToLocation("Gibraltar_town", "goto", "goto9", "Keys_lagoon_240_1");
			sld = CharacterFromID("Mishel_le_Bask");
			ChangeCharacterAddressGroup(sld, "Gibraltar_town", "reload", "reload3_back");
			sld = CharacterFromID("Etien_Marso");
			ChangeCharacterAddressGroup(sld, "Gibraltar_town", "reload", "reload3_back");
		break;

		case "Keys_lagoon_240_1":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Keys_lagoon_104";
			LAi_ActorDialog(sld, pchar, "", -1, 0);

			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_240_2":
			sld = CharacterFromID("Etien_Marso");
			ref bask = CharacterFromID("Mishel_le_Bask");

			CharacterTurnByChr(sld, bask);
			CharacterTurnByChr(bask, sld);

			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_16", GetFullName(pchar)));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_29"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_17"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_30"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_18"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_31"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_32"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_19"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_33"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_34"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Etien_Marso", "Keys_lagoon_240_3");
		break;

		case "Keys_lagoon_240_3":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload1_back", "", 3.0);
			DoQuestCheckDelay("Keys_lagoon_240_4", 1.0);
		break;

		case "Keys_lagoon_240_4":
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_AfterVargas_1";
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Keys_lagoon_241":
			QuestPointerDelLoc("Maracaibo_ExitTown", "reload", "reload1_back");
			QuestPointerDelLoc("Maracaibo_jungle_01", "reload", "reload1_back");
			QuestPointerDelLoc("Maracaibo_jungle_03", "reload", "reload3_back");
			QuestPointerDelLoc("Gibraltar_ExitTown", "reload", "reload1_back");
			for (i = 0; i < MAX_LOCATIONS; i++)
			{
				if (CheckAttribute(&Locations[i], "townsack"))
				{
					if (Locations[i].townsack == "Gibraltar")
					{
						DeleteAttribute(&Locations[i], "QuestlockWeather");
					}
				}

				if (CheckAttribute(&Locations[i], "fastreload"))
				{
					if (Locations[i].fastreload == "Gibraltar")
					{
						DeleteAttribute(&Locations[i], "QuestlockWeather");
					}
				}
			}

			n = FindLocation("Shore_ship3");
			if (n != -1) DeleteAttribute(&Locations[n], "QuestlockWeather");

			n = FindLocation("Gibraltar_ExitTown");
			if (n != -1) DeleteAttribute(&Locations[n], "QuestlockWeather");

			n = FindLocation("Gibraltar_town");
			if (n != -1) DeleteAttribute(&Locations[n], "QuestlockWeather");

			Whr_UpdateWeather();

			AddMapQuestMark_Major("Tortuga_town", "Keys_lagoon", "");
			DeleteAttribute(pchar, "questTemp.AoP.ForcePirateFlag");
			LocatorReloadEnterDisable("Maracaibo_town", "reload1_back", false);
			LocatorReloadEnterDisable("Maracaibo_town", "reload2_back", false);
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload1_back", false);
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload2", false);
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload3", false);
			LocatorReloadEnterDisable("Gibraltar_ExitTown", "reload2_back", false);
			InterfaceStates.Buttons.Save.enable = 1;
			DeleteAttribute(&TEV, "StopTimeScale");
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Etien_Marso");
			RemoveCharacterCompanion(pchar, sld);
			DeleteAttribute(sld, "FreeFighter");
			ChangeCharacterAddressGroup(sld, "none", "", "");

			sld = CharacterFromID("Mishel_le_Bask");
			RemoveCharacterCompanion(pchar, sld);
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetHuberType(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_111";
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit1");

			sld = CharacterFromID("Daniel_Monbar");
			RemoveCharacterCompanion(pchar, sld);
			DeleteAttribute(sld, "FreeFighter");
			ChangeCharacterAddressGroup(sld, "none", "", "");

			sld = CharacterFromID("Fransua_Olone");
			RemoveCharacterCompanion(pchar, sld);
			DeleteAttribute(sld, "FreeFighter");
			ChangeCharacterAddressGroup(sld, "none", "", "");

			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = &characters[i];
				bOk = false;

				if (findsubstr(sld.id, "Keys_lagoon_MaracaiboSailor_", 0) == 0) bOk = true;
				if (findsubstr(sld.id, "Keys_lagoon_GibraltarPirate_", 0) == 0) bOk = true;
				if (findsubstr(sld.id, "Keys_lagoon_GibraltarMush_", 0) == 0) bOk = true;
				if (findsubstr(sld.id, "Miskito_Mush_", 0) == 0) bOk = true;
				if (findsubstr(sld.id, "Officer_ExitTown_War_", 0) == 0) bOk = true;
				if (CheckAttribute(sld, "quest.AoP.KeysLagoonGibraltarAlly")) bOk = true;
				if (sld.id == "Mishel_le_Bask") continue;
				if (sld.id == "Daniel_Monbar") continue;
				if (sld.id == "Fransua_Olone") continue;
				if (sld.id == "Rimalier") continue;

				if (!bOk) continue;

				DeleteAttribute(sld, "FreeFighter");
				DeleteAttribute(sld, "quest.AoP.KeysLagoonGibraltarAlly");
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_295"), "Keys_lagoon_242", 0.1, 2.0);
			LaunchFrameForm();
			WaitDate("", 0, 0, 2, 0, 0); // мотаем время
			SetCurrentTime(19, 54);
			Whr_UpdateWeather();
			setWDMPointXZ("Maracaibo_town"); // корабль к городу
		break;

		case "Keys_lagoon_242":
			for (i = 1; i <= 15; i++)
			{
				sld = CharacterFromID("Mass_Officer_" + i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			for (i = 1; i <= 15; i++)
			{
				sld = CharacterFromID("Mass_Officer_mush_" + i);
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}
			QuestToSeaLogin_PrepareLoc("Maracaibo", "quest", "quest_ship_1", true);
			QuestToSeaLogin_Launch();
			DoQuestCheckDelay("Keys_lagoon_243", 2);
		break;

		case "Keys_lagoon_243":
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = &characters[i];

				RemoveLandQuestMark_Main(sld, "Shadow_of_a_big_deal");
				RemoveLandQuestMark_Main(sld, "Old_campfire");
				RemoveLandQuestMark_Main(sld, "Hunting_huntsman");
				RemoveLandQuestMark_Main(sld, "Brides_Tortuga");
				RemoveLandQuestMark_Main(sld, "Royal_jackpot");
				RemoveLandQuestMark_Main(sld, "Keys_lagoon");
			}

			AddMapQuestMark_Major("Tortuga_town", "Keys_lagoon", "");
			AddQuestRecord("Keys_lagoon", "15");
			pchar.quest.Tortuga_return_in_final.win_condition.l1 = "location";
			pchar.quest.Tortuga_return_in_final.win_condition.l1.location = "Tortuga";
			pchar.quest.Tortuga_return_in_final.win_condition = "Keys_lagoon_244";
		break;

		case "Keys_lagoon_244":
			sld = CharacterFromID("Mishel_le_Bask");
			AddLandQuestMark_Main(sld, "Keys_lagoon");
			SetLocationCapturedState("Gibraltar_town", false); // вернуть всех
			DeleteAttribute(&Colonies[FindColony("Maracaibo")], "AoP.KeysLagoonEmpty");
			SetTownCapturedState("Maracaibo", false);
			for (i = 0; i < MAX_LOCATIONS; i++)
			{
				if (CheckAttribute(&Locations[i], "loadcapture"))
				{
					DeleteAttribute(&Locations[i], "loadcapture");
				}
				if (CheckAttribute(&Locations[i], "QuestlockWeather"))
				{
					DeleteAttribute(&Locations[i], "QuestlockWeather");
				}
				if (CheckAttribute(&Locations[i], "DisableEncounters"))
				{
					DeleteAttribute(&Locations[i], "DisableEncounters");
				}
			}
			Whr_UpdateWeather();

			n = FindLocation("Bucaneer_outpost_townhall");
			if (n != -1)
			{
				Locations[n].models.always.house = "SmallResidence";
				Locations[n].models.always.locators = "SmallResidence_locators";
			}

			n = FindLocation("Aruba_Jungle_03");
			if (n != -1)
			{
				DeleteAttribute(&Locations[n], "models.always.spa_soldiers");
				DeleteAttribute(&Locations[n], "models.always.spa_blood");
				Locations[n].models.always.locators = "jungle14_locators";
				Locations[n].models.always.grassPatch = "jungle14_grass";
				Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
				Locations[n].models.day.charactersPatch = "jungle14_patch";
				Locations[n].models.night.charactersPatch = "jungle14_patch";
			}

			n = FindLocation("Aruba_IndianVillage");
			if (n != -1)
			{
				DeleteAttribute(&Locations[n], "models.always.mushkets");
				Locations[n].models.day.charactersPatch = "village_patch";
				Locations[n].models.night.charactersPatch = "village_patch";
			}

			n = FindLocation("Shore_ship3");
			if (n != -1)
			{
				Locations[n].models.always.locators = "shoreShip1_lcommon";
			}

			n = FindLocation("Gibraltar_ExitTown");
			if (n != -1)
			{
				DeleteAttribute(&Locations[n], "models.always.barricaded");
				Locations[n].models.day.charactersPatch = "townExitN_patch";
				Locations[n].models.night.charactersPatch = "townExitN_patch";
			}

			n = FindLocation("Cuba_Jungle_01");
			if (n != -1 && !CheckAttribute(&Locations[n], "models.always.rope"))
			{
				Locations[n].models.always.rope = "Jungle13_Rope";
			}

			LocatorReloadEnterDisable("Bucaneer_Outpost", "reload6_back", false);
			LocatorReloadEnterDisable("Bucaneer_outpost", "reload6_back", false);
			LocatorReloadEnterDisable("Beliz_Mine", "gate_back", false);
			LocatorReloadEnterDisable("Beliz_Mine", "reload_cave", false);
			LocatorReloadEnterDisable("Maracaibo_town", "reload1_back", false);
			LocatorReloadEnterDisable("Maracaibo_town", "reload2_back", false);
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload1_back", false);
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload2", false);
			LocatorReloadEnterDisable("Maracaibo_townhall", "reload3", false);
			LocatorReloadEnterDisable("Gibraltar_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("Pirates_town", "reload1_back", false);
			LocatorReloadEnterDisable("Cuba_Jungle_07", "reload2_back", false);
			LocatorReloadEnterDisable("Fishing_village", "reload1_back", false);
			LocatorReloadEnterDisable("Fishing_village", "reload2_back", false);
			LocatorReloadEnterDisable("Shore36", "boat", false);
			LocatorReloadEnterDisable("Shore45", "boat", false);
			LocatorReloadEnterDisable("Shore58", "reload2_back", false);
			LocatorReloadEnterDisable("Tortuga_cave", "reload1", false);
			LocatorReloadEnterDisable("Tobago_JungleHouse", "reload2_back", false);
			LocatorReloadEnterDisable("SantoDomingo_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("SantoDomingo_ExitTown", "reload3_back", false);
			LocatorReloadEnterDisable("SantoDomingo_town", "reload_jail", false);
			LocatorReloadEnterDisable("Hispaniola_Jungle_01", "reload2_back", false);
			LocatorReloadEnterDisable("Hispaniola_Jungle_02", "reload2_back", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload3_back", false);

			sld = CharacterFromID("Maracaibo_Mayor");
			if (CheckAttribute(sld, "id"))
			{
				sld.name = FindPersonalName("Maracaibo_Mayor_name");
				sld.lastname = FindPersonalName("Maracaibo_Mayor_lastname");
				sld.model = "huber_18";
				sld.sex = "man";
				sld.nation = SPAIN;
				sld.City = "Maracaibo";
				sld.Dialog.Filename = "Common_Mayor.c";
				sld.Dialog.CurrentNode = "First Time";
				sld.greeting = "spa_gov_common";
				sld.quest.type = "hovernor";

				DeleteAttribute(sld, "FreeFighter");
				DeleteAttribute(sld, "quest.AoP.KeysLagoonGibraltarAlly");
				LAi_CharacterEnableDialog(sld);
				LAi_SetImmortal(sld, true);
				LAi_SetHuberType(sld);
				ChangeCharacterAddressGroup(sld, "Maracaibo_townhall", "sit", "sit1");
			}

			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = &characters[i];
				if (!CheckAttribute(sld, "id")) continue;
				bOk = false;

				if (findsubstr(sld.id, "Keys_lagoon_", 0) == 0)          bOk = true;
				if (findsubstr(sld.id, "Miskito_Mush_", 0) == 0)         bOk = true;
				if (findsubstr(sld.id, "Officer_ExitTown_War_", 0) == 0) bOk = true;
				if (findsubstr(sld.id, "Defenders_Huber_", 0) == 0)      bOk = true;
				if (findsubstr(sld.id, "Bucaneers_Aruba_Outpost_", 0) == 0) bOk = true;
				if (CheckAttribute(sld, "quest.AoP.KeysLagoonGibraltarAlly")) bOk = true;

				if (!bOk) continue;
				if (sld.id == "Keys_lagoon_Portman") continue;

				DeleteAttribute(sld, "FreeFighter");
				DeleteAttribute(sld, "quest.AoP.KeysLagoonGibraltarAlly");
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			n = FindLocation("Maracaibo_town");
			locations[n].reload.l6.close_for_night = 1;
			locations[n].reload.l8.close_for_night = 1;
			locations[n].reload.l3.close_for_night = 1;
			QuestPointerToLoc("Bucaneer_outpost", "reload", "reload6_back"); // поставить поинт
		break;

		case "Keys_lagoon_245":
			n = FindLocation("Bucaneer_outpost_townhall");
			locations[n].models.always.house = "SmallResidence_sovet";
			locations[n].models.always.locators = "SmallResidence_sovet_locators";
			locations[n].models.day.charactersPatch = "patch_table";
			locations[n].models.night.charactersPatch = "patch_table";
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_275"), "Reload_To_Location", 0.1, 2.0);
			SetLaunchFrameReloadLocationParam("Bucaneer_outpost_townhall", "sit", "sit6", "Keys_lagoon_246");
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 30); // мотаем время
			LAi_SetActorType(pchar);
			LAi_ActorSetSitMode(pchar);
			sld = characterFromId("Fransua_Olone");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit5");
			sld = characterFromId("Mishel_le_Bask");
			MakeUnpushable(sld, true);
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit7");
			sld = characterFromId("Etien_Marso");
			MakeUnpushable(sld, true);
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit4");
			sld = characterFromId("Rimalier");
			MakeUnpushable(sld, true);
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit2");
			sld = characterFromId("Daniel_Monbar");
			MakeUnpushable(sld, true);
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit3");
		break;

		case "Keys_lagoon_246":
			DoQuestFunctionDelay("Keys_lagoon_camera_1", 0.0);
			DoQuestCheckDelay("Keys_lagoon_247", 2);
		break;

		case "Keys_lagoon_247":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Quest\LeBasque\LeBasque_dialog.c";
			sld.Dialog.CurrentNode = "Keys_lagoon_114";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_248":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_19"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_35"));
			AoP_NPCDialogLaunch("Daniel_Monbar", "Mishel_le_Bask", "Keys_lagoon_249");
		break;

		case "Keys_lagoon_249":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Quest\LeBasque\LeBasque_dialog.c";
			sld.Dialog.CurrentNode = "Keys_lagoon_114_3";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_250":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_36"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_22"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_37"));
			AoP_NPCDialogAddLine("Fransua_Olone", StringFromKey("LeBasque_Fransua_Olone_23"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_38"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Fransua_Olone", "Keys_lagoon_266");
		break;

		case "Keys_lagoon_266":
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto3", "Keys_lagoon_267", 4);
		break;

		case "Keys_lagoon_267":
			sld = CharacterFromID("Fransua_Olone");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Keys_lagoon_268", -1);
		break;

		case "Keys_lagoon_268":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_39"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_20"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_40"));
			AoP_NPCDialogAddLine("Daniel_Monbar", StringFromKey("LeBasque_Daniel_Monbar_21"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_41"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Daniel_Monbar", "Keys_lagoon_272");
		break;

		case "Keys_lagoon_272":
			sld = CharacterFromID("Daniel_Monbar");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Quest\LeBasque\Monbar_dialog.c";
			sld.Dialog.CurrentNode = "Monbar_72_3";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_274":
			sld = CharacterFromID("Daniel_Monbar");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto_marso", "Keys_lagoon_275", 5);
		break;

		case "Keys_lagoon_275":
			sld = CharacterFromID("Daniel_Monbar");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Keys_lagoon_276", -1);
		break;

		case "Keys_lagoon_276":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Rimalier", StringFromKey("LeBasque_Rimalier_1"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_42"));
			AoP_NPCDialogAddLine("Rimalier", StringFromKey("LeBasque_Rimalier_2"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_43"));
			AoP_NPCDialogLaunch("Rimalier", "Mishel_le_Bask", "Keys_lagoon_277");
		break;

		case "Keys_lagoon_277":
			sld = CharacterFromID("Rimalier");
			if (IsOfficer(sld))
			{
				LAi_CharacterEnableDialog(sld);
				sld.Dialog.Filename = "Quest\LeBasque\Rimalier_dialog.c";
				sld.Dialog.CurrentNode = "Keys_lagoon_6_Officer";
				LAi_ActorDialogNow(pchar, sld, "", -1);
			}
			else
			{
				DoQuestCheckDelay("Keys_lagoon_278", 0.1);
			}
		break;

		case "Keys_lagoon_278":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Rimalier", StringFromKey("LeBasque_Rimalier_3"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_44"));
			AoP_NPCDialogAddLine("Rimalier", StringFromKey("LeBasque_Rimalier_4"));
			AoP_NPCDialogLaunch("Rimalier", "Mishel_le_Bask", "Keys_lagoon_280");
		break;

		case "Keys_lagoon_279":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_45"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Rimalier", "Keys_lagoon_282_Officer");
		break;

		case "Keys_lagoon_280":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Quest\LeBasque\LeBasque_dialog.c";
			sld.Dialog.CurrentNode = "Keys_lagoon_114_14";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_281":
			sld = CharacterFromID("Rimalier");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto_npc_1", "Keys_lagoon_282", 5);
		break;

		case "Keys_lagoon_282":
			sld = CharacterFromID("Rimalier");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Keys_lagoon_283", 5);
		break;

		case "Keys_lagoon_282_Officer":
			sld = CharacterFromID("Rimalier");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto_npc_1", "Keys_lagoon_282_Officer_Leave", 5);
		break;

		case "Keys_lagoon_282_Officer_Leave":
			sld = CharacterFromID("Rimalier");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Keys_lagoon_282_Officer_End", 5);
		break;

		case "Keys_lagoon_282_Officer_End":
			sld = CharacterFromID("Rimalier");
			LAi_SetOfficerType(sld);
			sld.Dialog.CurrentNode = "Hired";
			sld.Dialog.TempNode = "Hired";
			LAi_CharacterEnableDialog(sld);
			DoQuestCheckDelay("Keys_lagoon_283", 0.1);
		break;

		case "Keys_lagoon_283":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_46"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Etien_Marso", "Keys_lagoon_285");
		break;

		case "Keys_lagoon_285":
			sld = CharacterFromID("Etien_Marso");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Quest\LeBasque\Marso_dialog.c";
			sld.Dialog.CurrentNode = "Keys_lagoon_15";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_291":
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto1", "Keys_lagoon_292", 3);
		break;

		case "Keys_lagoon_292":
			sld = CharacterFromID("Etien_Marso");
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Keys_lagoon_293", 3);
		break;

		case "Keys_lagoon_293":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetSitTypeNoGroup(sld);

			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Quest\LeBasque\LeBasque_dialog.c";
			sld.Dialog.CurrentNode = "Keys_lagoon_114_17";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_294":
			LAi_SetPlayerType(pchar);
			chrDisableReloadToLocation = false;
			QuestPointerDelLoc("Bucaneer_outpost", "reload", "reload6_back");
			RemoveMapQuestMark("Tortuga_town", "Keys_lagoon");
			DoQuestReloadToLocation("Bucaneer_outpost", "reload", "reload6_back", "Keys_lagoon_295");
		break;

		case "Keys_lagoon_295":
			DeleteAttribute(pchar, "questTemp.MaracaiboSiegeLock");
			SetTimerCondition("Keys_lagoon_298", 0, 0, 7, false);
			LAi_SetPlayerType(pchar);
			locCameraResetState();
			AddQuestRecord("Keys_lagoon", "16");
			ChangeBuccaneerRelation(10.0); // +10 к отношениям с буканьерами
			CloseQuestHeader("Keys_lagoon");
			Achievment_Set(ACH_Keys_lagoon);
			sld = CharacterFromID("Rimalier");
			if (IsOfficer(sld))
			{
			DeleteAttribute(pchar, "questTemp.Brides_Tortuga.RimalierDismissLocked");
			SetCharacterRemovable(sld, true);
			LAi_SetImmortal(sld, false); //снимаем бессмертие
			sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
			sld.loyality = MAX_LOYALITY;
			SetCharacterPerk(sld, "LoyalOff"); 
			}
			sld = characterFromID("Mishel_le_Bask");
			sld.Dialog.CurrentNode = "Second_time";
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_outpost_townhall", "sit", "sit1");

			n = FindLocation("Bucaneer_outpost_townhall");
			if (n != -1)
			{
				Locations[n].models.always.house = "SmallResidence";
				Locations[n].models.always.locators = "SmallResidence_locators";
				locations[n].models.day.charactersPatch = "SmallResidence_patch";
				locations[n].models.night.charactersPatch = "SmallResidence_patch";
			}

			iTemp = 0;
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				sld = &characters[i];
				if (CheckAttribute(sld, "AoP.ArubaStoredShip")) iTemp++;
			}

			if (iTemp > 0)
			{
				sld = CharacterFromID("Keys_lagoon_Portman");
				LAi_CharacterEnableDialog(sld);
				LAi_SetStayType(sld);
				sld.Dialog.CurrentNode = "Keys_lagoon_ShipKeeper_Return_1";
				ChangeCharacterAddressGroup(sld, "Shore67", "goto", "goto2");
				AddMapQuestMark_Major("Aruba", "Keys_lagoon", "");
			}
			else
			{
				sld = CharacterFromID("Keys_lagoon_Portman");
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		break;

		case "Keys_lagoon_296":
			RemoveMapQuestMark("Aruba", "Keys_lagoon");
			sld = CharacterFromID("Keys_lagoon_Portman");
			LAi_CharacterDisableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Keys_lagoon_297", -1);
		break;

		case "Keys_lagoon_297":
			sld = CharacterFromID("Keys_lagoon_Portman");
			sld.lifeday = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
		break;

		case "Keys_lagoon_298":
			pchar.questTemp.AoP.KeysLagoon.PunitiveActive = true;
			Group_FindOrCreateGroup("Sea_Keys_lagoon_Punitive_Cap_1");
			Group_SetTaskAttackInMap("Sea_Keys_lagoon_Punitive_Cap_1", PLAYER_GROUP);
			Group_LockTask("Sea_Keys_lagoon_Punitive_Cap_1");

			sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_Punitive_Cap_1", "off_spa_1", "man", "man", CB_Rank() + 5, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank() + 5, 95, 95, "blade25", "pistol5", 80);
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("Keys_lagoon_Punitive_Cap_1_ship"), CANNON_TYPE_CANNON_LBS32, 95, 95, 95);
			SetCrewQuantityFull(sld);
			SetRandGeraldSail(sld, SPAIN);
			sld.Ship.Mode = "war";
			sld.AlwaysEnemy = true;
			sld.DontRansackCaptain = true;
			sld.Abordage.Enable = true;
			sld.mapEnc.type = "war";
			sld.mapEnc.worldMapShip = "quest_ship";
			sld.mapEnc.Name = FindPersonalName("Keys_lagoon_Punitive_mapEnc");
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
			npchar = CharacterFromID("Keys_lagoon_Punitive_Cap_1");

			sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_Punitive_Cap_2", "off_spa_2", "man", "man", CB_Rank() + 4, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank() + 4, 92, 92, "blade24", "pistol5", 75);
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("Keys_lagoon_Punitive_Cap_2_ship"), CANNON_TYPE_CANNON_LBS32, 92, 92, 92);
			SetCrewQuantityFull(sld);
			SetRandGeraldSail(sld, SPAIN);
			sld.Ship.Mode = "war";
			sld.AlwaysEnemy = true;
			sld.mapEnc.type = "war";
			sld.mapEnc.worldMapShip = "quest_ship";
			sld.mapEnc.Name = FindPersonalName("Keys_lagoon_Punitive_mapEnc");
			sld.DontRansackCaptain = true;
			sld.Abordage.Enable = true;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
			SetCompanionIndex(npchar, -1, sti(sld.index));

			sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_Punitive_Cap_3", "off_spa_3", "man", "man", CB_Rank() + 5, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank() + 5, 95, 95, "blade26", "pistol5", 80);
			FantomMakeCoolSailor(sld, SHIP_GALEON_H, FindPersonalName("Keys_lagoon_Punitive_Cap_3_ship"), CANNON_TYPE_CANNON_LBS32, 95, 95, 95);
			SetCrewQuantityFull(sld);
			SetRandGeraldSail(sld, SPAIN);
			sld.Ship.Mode = "war";
			sld.AlwaysEnemy = true;
			sld.mapEnc.type = "war";
			sld.mapEnc.worldMapShip = "quest_ship";
			sld.mapEnc.Name = FindPersonalName("Keys_lagoon_Punitive_mapEnc");
			sld.DontRansackCaptain = true;
			sld.Abordage.Enable = true;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
			SetCompanionIndex(npchar, -1, sti(sld.index));

			sld = GetCharacter(NPC_GenerateCharacter("Keys_lagoon_Punitive_Cap_4", "off_spa_4", "man", "man", CB_Rank() + 3, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank() + 3, 90, 90, "blade23", "pistol4", 70);
			FantomMakeCoolSailor(sld, SHIP_CORVETTE, FindPersonalName("Keys_lagoon_Punitive_Cap_4_ship"), CANNON_TYPE_CANNON_LBS24, 90, 90, 90);
			SetCrewQuantityFull(sld);
			SetRandGeraldSail(sld, SPAIN);
			sld.Ship.Mode = "war";
			sld.AlwaysEnemy = true;
			sld.mapEnc.type = "war";
			sld.mapEnc.worldMapShip = "quest_ship";
			sld.mapEnc.Name = FindPersonalName("Keys_lagoon_Punitive_mapEnc");
			sld.DontRansackCaptain = true;
			sld.Abordage.Enable = true;
			SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
			SetCompanionIndex(npchar, -1, sti(sld.index));
			Group_DeleteGroup("Keys_lagoon_Punitive_CheckGroup");
			Group_FindOrCreateGroup("Keys_lagoon_Punitive_CheckGroup");
			Group_AddCharacter("Keys_lagoon_Punitive_CheckGroup", "Keys_lagoon_Punitive_Cap_1");
			Group_AddCharacter("Keys_lagoon_Punitive_CheckGroup", "Keys_lagoon_Punitive_Cap_2");
			Group_AddCharacter("Keys_lagoon_Punitive_CheckGroup", "Keys_lagoon_Punitive_Cap_3");
			Group_AddCharacter("Keys_lagoon_Punitive_CheckGroup", "Keys_lagoon_Punitive_Cap_4");
			Map_CreateCoolWarrior("", "Keys_lagoon_Punitive_Cap_1", -1);
			pchar.quest.Keys_lagoon_Punitive_AllSunk.win_condition.l1 = "Group_Death";
			pchar.quest.Keys_lagoon_Punitive_AllSunk.win_condition.l1.group = "Keys_lagoon_Punitive_CheckGroup";
			pchar.quest.Keys_lagoon_Punitive_AllSunk.win_condition = "Keys_lagoon_299";
		break;

		case "Keys_lagoon_299":
			Group_DeleteGroup("Keys_lagoon_Punitive_CheckGroup");
			DeleteAttribute(pchar, "questTemp.AoP.KeysLagoon.PunitiveActive");
			DeleteAttribute(pchar, "questTemp.AoP.KeysLagoon.PunitiveLeader");
			Map_ReleaseQuestEncounter("Keys_lagoon_Punitive_Cap_1");
			Map_ReleaseQuestEncounter("Keys_lagoon_Punitive_Cap_2");
			Map_ReleaseQuestEncounter("Keys_lagoon_Punitive_Cap_3");
			Map_ReleaseQuestEncounter("Keys_lagoon_Punitive_Cap_4");
			AddQuestRecord("Keys_lagoon", "17");
			CloseQuestHeader("Keys_lagoon");
		break;

		case "Keys_lagoon_Res_Ransom":
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Maracaibo_Mayor");
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.Dialog.CurrentNode = "Keys_lagoon_Res_11";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_Res_Past_1":
			LAi_SetActorType(pchar);
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_7"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_47"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_8"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_48"));
			AoP_NPCDialogLaunch("Maracaibo_Mayor", "Mishel_le_Bask", "Keys_lagoon_Res_Past_2");
		break;

		case "Keys_lagoon_Res_Past_2":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_20"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_9"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_21"));
			AoP_NPCDialogLaunch("Etien_Marso", "Maracaibo_Mayor", "Keys_lagoon_Res_Past_3");
		break;

		case "Keys_lagoon_Res_Past_3":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_49"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_22"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Etien_Marso", "Keys_lagoon_Res_Past_4");
		break;

		case "Keys_lagoon_Res_Past_4":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_10"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_50"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_11"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_12"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_51"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_13"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_14"));
			AoP_NPCDialogLaunch("Maracaibo_Mayor", "Mishel_le_Bask", "Keys_lagoon_Res_Past_5");
		break;

		case "Keys_lagoon_Res_Past_5":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_23"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_15"));
			AoP_NPCDialogLaunch("Etien_Marso", "Maracaibo_Mayor", "Keys_lagoon_Res_Past_6");
		break;

		case "Keys_lagoon_Res_Past_6":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_24"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_52"));
			AoP_NPCDialogLaunch("Etien_Marso", "Mishel_le_Bask", "Keys_lagoon_Res_Past_6_1");
		break;

		case "Keys_lagoon_Res_Past_6_1":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_16"));
			AoP_NPCDialogLaunch("Maracaibo_Mayor", "Mishel_le_Bask", "Keys_lagoon_Res_Past_7");
		break;

		case "Keys_lagoon_Res_Past_7":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_25"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_17"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_18"));
			AoP_NPCDialogLaunch("Etien_Marso", "Maracaibo_Mayor", "Keys_lagoon_Res_Past_8");
		break;

		case "Keys_lagoon_Res_Past_8":
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_53"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_19"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Maracaibo_Mayor", "Keys_lagoon_Res_Familiar");
		break;

		case "Keys_lagoon_Res_Familiar":
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Maracaibo_Mayor");
			sld.Dialog.CurrentNode = "Keys_lagoon_Res_36";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_Res_Past_9":
			LAi_SetActorType(pchar);
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_20"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_21"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_54"));
			AoP_NPCDialogLaunch("Maracaibo_Mayor", "Mishel_le_Bask", "Keys_lagoon_Res_Alonso");
		break;

		case "Keys_lagoon_Res_10":
			sld = CharacterFromID("Maracaibo_Mayor");
			LAi_SetActorType(pchar);
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.Dialog.CurrentNode = "Keys_lagoon_Res_13";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_Res_11":
			sld = CharacterFromID("Maracaibo_Mayor");
			sld.Dialog.CurrentNode = "Keys_lagoon_Res_39";
			LAi_SetActorType(pchar);
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_Res_Alonso":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "Keys_lagoon_Res_38";
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "Keys_lagoon_Res_Quarrel":
			LAi_SetActorType(pchar);
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_26"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_55"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_27"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_56"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_28"));
			AoP_NPCDialogLaunch("Etien_Marso", "Mishel_le_Bask", "Keys_lagoon_Res_Diego");
		break;

		case "Keys_lagoon_Res_Diego":
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Maracaibo_Mayor");
			sld.Dialog.CurrentNode = "Keys_lagoon_Res_45";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_Res_Tortuga_1":
			LAi_SetActorType(pchar);
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_57"));
			AoP_NPCDialogAddLine("Maracaibo_Mayor", StringFromKey("LeBasque_Maracaibo_Mayor_22"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Maracaibo_Mayor", "Keys_lagoon_Res_Tortuga_2");
		break;

		case "Keys_lagoon_Res_Tortuga_2":
			LAi_SetActorType(pchar);
			sld = CharacterFromID("Maracaibo_Mayor");
			sld.Dialog.CurrentNode = "Keys_lagoon_Res_47";
			LAi_ActorDialogNow(pchar, sld, "", -1);
		break;

		case "Keys_lagoon_Res_Leaving":
			LAi_SetActorType(pchar);
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_58"));
			AoP_NPCDialogAddLine("Etien_Marso", StringFromKey("LeBasque_Etien_Marso_29"));
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_59"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Etien_Marso", "Keys_lagoon_Res_Ultimatum");
		break;

		case "Keys_lagoon_Res_Ultimatum":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorTurnToCharacter(sld, CharacterFromID("Maracaibo_Mayor"));
			AoP_NPCDialogClear();
			AoP_NPCDialogAddLine("Mishel_le_Bask", StringFromKey("LeBasque_Mishel_le_Bask_60"));
			AoP_NPCDialogLaunch("Mishel_le_Bask", "Maracaibo_Mayor", "Keys_lagoon_239");
		break;

	}
}

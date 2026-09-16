// Блад
void ProcessDialogEvent()
{
	ref NPChar, sld, loc;
	aref Link, NextDiag;
	string sLocator;
	int iTime, n;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		// --> Бишоп
		// ----------------------------------- Диалог первый - первая встреча
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_Away":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", Pchar.questTemp.CapBloodLine.sLocator, "none", "", "", "", sti(Pchar.questTemp.CapBloodLine.iTime));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Exit_RunAway":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorRunToLocation(npchar, "reload", Pchar.questTemp.CapBloodLine.sLocator, "none", "", "", "", sti(Pchar.questTemp.CapBloodLine.iTime));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "GFight":
			DialogExit();
			EndQuestMovie();
			MakeQuickSave();
			locCameraFollowEx(true);
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			for (n = 3; n <= 4; n++)
			{
				sld = &characters[GetCharacterIndex("Dragun_" + n)];
				LAi_SetNoTarget(sld, 3, 1, true);
			}
			sld = &characters[GetCharacterIndex("Dragun_2")];
			LAi_SetCheckMinHP(sld, 1, true, "Dragun_2_CheckMinHP");
			LAi_SetImmortal(sld, false);
			LAi_SetWarriorTypeNoGroup(sld);//fix
			LAi_warrior_DialogEnable(sld, false);//fix
			LAi_group_MoveCharacter(sld, "TmpEnemy");
			//LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			LAi_group_Attack(sld, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);//fix
			LAi_group_SetHearRadius("TmpEnemy", 3000.0); //fix
			AddDialogExitQuest("MainHeroFightModeOn");
			//LAi_ActorRunToLocation(NPChar, "goto", "goto6", "none", "", "", "", 20);
			LAi_ActorGoToLocator(NPChar, "goto", "goto6", "CapBloodLine_Kirk_10", -1);
		break;

		case "fight1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			Spain_spyDie("");
			AddQuestRecord("WeaponsForEscape", "5");
			AddLandQuestmark_Main(CharacterFromID("Griffin"), "CapBloodLine");

			chrDisableReloadToLocation = true;
			pchar.quest.CapBloodLine_Hells_Die.win_condition.l1 = "NPC_Death";
			pchar.quest.CapBloodLine_Hells_Die.win_condition.l1.character = "Hells";
			pchar.quest.CapBloodLine_Hells_Die.function = "CapBloodLine_Hells_Die";

			AddDialogExitQuestFunction("Tutorial_BloodPrologue_StartBarbadosFightTutorials_OnDialogExit");
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetWarriorType(NPChar);
			LAi_group_MoveCharacter(NPChar, "TmpEnemy");
			LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");

			sld = CharacterFromID("Griffin");
			sld.dialog.currentnode = "GRStep_14";
			LAi_CharacterDisableDialog(sld);
			chrDisableReloadToLocation = true;
			pchar.quest.CapBloodLine_SpainSpy_AfterFight.win_condition.l1 = "NPC_Death";
			pchar.quest.CapBloodLine_SpainSpy_AfterFight.win_condition.l1.character = "Spain_spy";
			pchar.quest.CapBloodLine_SpainSpy_AfterFight.function = "CapBloodLine_SpainSpy_AfterFight";
		break;

		case "Finish":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RestoreBridgetown();
			CincoLlagasCapture();
			DoReloadCharacterToLocation(Pchar.HeroParam.Location, Pchar.HeroParam.Group, Pchar.HeroParam.Locator);
		break;

		case "Man_FackYou":
			dialog.text = StringFromKey("Bishop_4", LinkRandPhrase(
						StringFromKey("Bishop_1"),
						StringFromKey("Bishop_2"),
						StringFromKey("Bishop_3")));
			link.l1 = StringFromKey("Bishop_8", LinkRandPhrase(
						StringFromKey("Bishop_5"),
						StringFromKey("Bishop_6"),
						StringFromKey("Bishop_7")));
			link.l1.go = "fight_owner";
		break;

		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			//if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NextQuest":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			DeleteAttribute(&TEV, "TutorialInfo.BloodPrologue_CameraControl");
		break;

		case "First time":
			dialog.text = StringFromKey("Bishop_9");
			link.l1 = "...";
			link.l1.go = "Exit";
			npchar.quest.meeting = "1";

			if (npchar.id == "Pitt")
			{
				if (bBettaTestMode)
				{
					link.l0 = StringFromKey("Bishop_10");
					link.l0.go = "Finish";
				}

				if (Pchar.questTemp.CapBloodLine.stat == "Begining")
				{
					dialog.text = StringFromKey("Bishop_11");
					link.l1 = StringFromKey("Bishop_12");
					link.l1.go = "Exit_Away";
					Pchar.questTemp.CapBloodLine.sLocator = "reload1";
					Pchar.questTemp.CapBloodLine.iTime = -1;
					if (bBettaTestMode)
					{
						link.l3 = StringFromKey("Bishop_13");
						link.l3.go = "NextQuest";
					}
					RemoveLandQuestmark_Main(npchar, "CapBloodLine");
					AddDialogExitQuestFunction("Tutorial_BloodPrologue_CameraControl_Delay");
					break;
				}

				if (Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
				{
					dialog.text = StringFromKey("Bishop_14");
					link.l1 = StringFromKey("Bishop_15");
					link.l1.go = "Exit";
					break;
				}
				if (Pchar.questTemp.CapBloodLine.stat == "WakerOfferComplited")
				{
					RemoveLandQuestmark_Main(npchar, "CapBloodLine");
					dialog.text = StringFromKey("Bishop_16");
					link.l1 = StringFromKey("Bishop_17");
					link.l1.go = "PStep_0";
					break;
				}
				dialog.text = StringFromKey("Bishop_18");
				link.l1 = StringFromKey("Bishop_19");
				link.l1.go = "Exit";
			}

			if (npchar.id == "Beyns")
			{
				dialog.text = StringFromKey("Bishop_20");
				link.l1 = StringFromKey("Bishop_21");
				link.l1.go = "EBStep_0";
			}

			if (npchar.id == "CapGobart")
			{
				dialog.text = StringFromKey("Bishop_22");
				link.l1 = StringFromKey("Bishop_23");
				link.l1.go = "CGStep_1";
				locCameraFromToPos(12.63, 8.91, -3.11, true, 9.83, 6.00, 1.05);
			}

			if (npchar.id == "Bridgetown_Mayor")
			{
				if (Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
				{
					dialog.text = StringFromKey("Bishop_24");
					link.l1 = StringFromKey("Bishop_25");
					link.l1.go = "SStep_0";
					link.l2 = StringFromKey("Bishop_26");
					link.l2.go = "SStep_1";
					break;
				}

				if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape3")
				{
					dialog.text = StringFromKey("Bishop_27");
					link.l1 = StringFromKey("Bishop_28");
					link.l1.go = "SStep_9";
					break;
				}
				dialog.text = StringFromKey("Bishop_29");
				link.l1 = StringFromKey("Bishop_30");
				link.l1.go = "Exit";
				NextDiag.TempNode = "First time";
			}

			if (npchar.id == "MisStid" && Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
			{
				dialog.text = StringFromKey("Bishop_31");
				link.l1 = StringFromKey("Bishop_32");
				link.l1.go = "MSStep_0";
			}

			if (npchar.id == "Nettl") // && Pchar.questTemp.CapBloodLine.stat == "CureMisStid"
			{
				dialog.text = StringFromKey("Bishop_33");
				if (Pchar.questTemp.CapBloodLine.stat == "needMoney")
				{
					link.l1 = StringFromKey("Bishop_34");
					link.l1.go = "NStep_6";
				}
				else
				{
					link.l1 = StringFromKey("Bishop_35");
					link.l1.go = "NStep_0";
				}
			}

			if (npchar.id == "Waker")
			{
				if (Pchar.questTemp.CapBloodLine.stat == "CureMisStid")
				{
					dialog.text = StringFromKey("Bishop_36");
					link.l1 = StringFromKey("Bishop_37");
					link.l1.go = "WStep_0";
					link.l2 = StringFromKey("Bishop_38");
					link.l2.go = "WStep_1";
				}

				if (Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
				{
					dialog.text = StringFromKey("Bishop_39");
					link.l1 = StringFromKey("Bishop_40");
					link.l1.go = "WStep_3";
				}
			}

			if (npchar.id == "Den")
			{
				dialog.text = StringFromKey("Bishop_41");
				link.l1 = StringFromKey("Bishop_42");
				link.l1.go = "DStep_0";
				if (GetCharacterItem(pchar, "migraine_potion") > 0)
				{
					link.l2 = StringFromKey("Bishop_43");
					link.l2.go = "DStep_1";
				}
				link.l3 = StringFromKey("Bishop_44");
				link.l3.go = "DStep_2";
			}

			if (npchar.id == "Griffin")
			{
				if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1")
				{
					dialog.text = StringFromKey("Bishop_45");
					link.l1 = StringFromKey("Bishop_46");
					link.l1.go = "GRStep_0";
					QuestPointerDelLoc("Bridgetown_town", "reload", "HouseSp2");
					QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_WeaponsForEscape");
					break;
				}

				if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape")
				{

					dialog.text = StringFromKey("Bishop_47");
					link.l1 = StringFromKey("Bishop_48");
					link.l1.go = "GRStep_10";
					QuestPointerDelLoc("Bridgetown_town", "reload", "HouseSp2");
					QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_WeaponsForEscape");
					break;
				}

				dialog.text = StringFromKey("Bishop_49");
				link.l1 = StringFromKey("Bishop_50");
				link.l1.go = "Exit";
			}

			if (npchar.id == "Hells")
			{
				if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1_1")
				{
					dialog.text = StringFromKey("Bishop_51");
					link.l1 = StringFromKey("Bishop_52");
					link.l1.go = "HStep_0";
					link.l2 = StringFromKey("Bishop_53");
					link.l2.go = "fight1";
					QuestPointerDelLoc("Bridgetown_town", "reload", "reload11_back");
					break;
				}

				if (Pchar.questTemp.CapBloodLine.stat == "needMoney" && !CheckAttribute(Pchar, "questTemp.CapBloodLine.fishplace"))
				{
					dialog.text = StringFromKey("Bishop_54");
					link.l1 = StringFromKey("Bishop_55");
					link.l1.go = "HStep_5";
					break;
				}

				dialog.text = StringFromKey("Bishop_56");
				link.l1 = StringFromKey("Bishop_57");
				link.l1.go = "Exit";
			}

			if (npchar.id == "Quest_Smuggler")
			{
				if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape" && sti(Pchar.reputation) >= 50)
				{
					PlayerRPGCheck_Reputation_NotifyPass(false, true);
					dialog.text = StringFromKey("Bishop_58");
					link.l1 = StringFromKey("Bishop_59");
					link.l1.go = "QSStep_0";
					break;
				}
				dialog.text = StringFromKey("Bishop_60");
				link.l1 = StringFromKey("Bishop_61");
				link.l1.go = "Exit";
			}

			if (npchar.id == "Spain_spy")
			{
				dialog.text = StringFromKey("Bishop_62");
				link.l1 = StringFromKey("Bishop_63");
				link.l1.go = "SSStep_0";
			}

			if (npchar.id == "Volverston")
			{
				if (Pchar.questTemp.CapBloodLine.statcrew == "find")
				{
					dialog.text = StringFromKey("Bishop_64");
					link.l1 = StringFromKey("Bishop_65");
					link.l1.go = "VLStep_0";
					break;
				}
				dialog.text = StringFromKey("Bishop_66");
				link.l1 = StringFromKey("Bishop_67");
				link.l1.go = "Exit";
			}

			if (npchar.id == "Hugtorp")
			{
				if (Pchar.questTemp.CapBloodLine.statcrew == "find")
				{
					dialog.text = StringFromKey("Bishop_68");
					link.l1 = StringFromKey("Bishop_69");
					link.l1.go = "HTStep_0";
					break;
				}
				dialog.text = StringFromKey("Bishop_70");
				link.l1 = StringFromKey("Bishop_71");
				link.l1.go = "Exit";

			}

			if (npchar.id == "Dieke")
			{
				if (Pchar.questTemp.CapBloodLine.statcrew == "find")
				{
					dialog.text = StringFromKey("Bishop_72");
					link.l1 = StringFromKey("Bishop_73");
					link.l1.go = "DKStep_0";
					break;
				}
				dialog.text = StringFromKey("Bishop_74");
				link.l1 = StringFromKey("Bishop_75");
				link.l1.go = "Exit";
			}

			if (npchar.id == "Ogl")
			{
				if (Pchar.questTemp.CapBloodLine.statcrew == "find")
				{
					dialog.text = StringFromKey("Bishop_76", TimeGreeting());
					link.l1 = StringFromKey("Bishop_77");
					link.l1.go = "OGLStep_0";
					break;
				}
				dialog.text = StringFromKey("Bishop_78", TimeGreeting());
				link.l1 = StringFromKey("Bishop_79");
				link.l1.go = "Exit";
			}
		break;

		case "Bishop On House":
			dialog.text = StringFromKey("Bishop_82");
			link.l1 = StringFromKey("Bishop_83");
			link.l1.go = "Andgree Bishop";
			NextDiag.TempNode = "Bishop On House";
		break;

		case "Andgree Bishop":
			DialogExit();
			DoQuestReloadToLocation("Bridgetown_plantation", "reload", "houseSp1", "");
			LocatorReloadEnterDisable("Bridgetown_plantation", "houseSp1", true);
		break;

		case "BStep":
			dialog.text = StringFromKey("Bishop_80");
			link.l1 = StringFromKey("Bishop_81");
			link.l1.go = "BStep_0";
		break;

		case "BStep_0":
			dialog.text = StringFromKey("Bishop_84");
			link.l1 = StringFromKey("Bishop_85");
			link.l1.go = "Bishop_Away";
			chrDisableReloadToLocation = false;
			NextDiag.TempNode = "Bishop On House";
			AddDialogExitQuestFunction("CapBloodLine_StartMissisStidQuest");
		break;

		case "BStep_1":
			dialog.text = StringFromKey("Bishop_86");
			link.l1 = StringFromKey("Bishop_87");
			link.l1.go = "Exit";
			NextDiag.TempNode = "BStep_Angree";
		break;

		case "BStep_Angree":
			DialogExit();
			DoQuestReloadToLocation("Bridgetown_Plantation", "reload", "houseSp1", "");
			LocatorReloadEnterDisable("Bridgetown_Plantation", "houseSp1", true);
		break;

		case "BStep_2":
			dialog.text = StringFromKey("Bishop_88");
			link.l1 = StringFromKey("Bishop_89");
			link.l1.go = "BStep_3";
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "BStep_3":
			dialog.text = StringFromKey("Bishop_90");
			link.l1 = StringFromKey("Bishop_91");
			link.l1.go = "BStep_4";
		break;

		case "BStep_4":
			dialog.text = StringFromKey("Bishop_92");
			link.l1 = StringFromKey("Bishop_93");
			link.l1.go = "BStep_5";
		break;

		case "BStep_5":
			dialog.text = StringFromKey("Bishop_94");
			link.l1 = StringFromKey("Bishop_95");
			link.l1.go = "BStep_6";
			NextDiag.TempNode = "BStep_1";
		break;

		case "BStep_6":
			DialogExit();
			sld = characterFromID("Quest_Habitue");
			sld.Dialog.CurrentNode = "QHStep_0";
			AddLandQuestmark_Main(sld, "CapBloodLine");

			chrDisableReloadToLocation = true;
			bDisableCharacterMenu = true;

			AddQuestRecord("DiekeQuest", "2");
			QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "DiekeQuest");
			QuestPointerDelLoc("Bridgetown_plantation", "reload", "houseSp1");
			DoQuestFunctionDelay("CapBloodLine_ReloadFromBishopsHouse", 1.0);
		break;

		case "Bishop_Away":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "none", "", "", "", -1);
			DialogExit();
		break;

		case "Bishop_Packhouse":
			dialog.text = StringFromKey("Bishop_597");
			link.l1 = StringFromKey("Bishop_598");
			link.l1.go = "Bishop_Packhouse_1";
		break;

		case "Bishop_Packhouse_1":
			dialog.text = StringFromKey("Bishop_599");
			link.l1 = StringFromKey("Bishop_600");
			link.l1.go = "Bishop_Packhouse_2";
		break;

		case "Bishop_Packhouse_2":
			dialog.text = StringFromKey("Bishop_601");
			link.l1 = StringFromKey("Bishop_602");
			link.l1.go = "Bishop_Packhouse_3";
		break;

		case "Bishop_Packhouse_3":
			dialog.text = StringFromKey("Bishop_603");
			link.l1 = StringFromKey("Bishop_604");
			link.l1.go = "Bishop_Packhouse_4";
		break;

		case "Bishop_Packhouse_4":
			dialog.text = StringFromKey("Bishop_605");
			link.l1 = StringFromKey("Bishop_606");
			link.l1.go = "Bishop_Packhouse_5";
		break;

		case "Bishop_Packhouse_5":
			dialog.text = StringFromKey("Bishop_607");
			link.l1 = StringFromKey("Bishop_608");
			link.l1.go = "Bishop_Packhouse_6";
		break;

		case "Bishop_Packhouse_6":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Bridgetown_Plantation_Sp1", "goto", "goto1", "BishopOnHouse", -1);
			NextDiag.CurrentNode = "Bishop On House";
			DialogExit();
		break;

		case "Bishop_Plantation": // На плантации
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			CharacterTurnByChr(CharacterFromID("CBL_Kent"), pchar);

			dialog.text = StringFromKey("Bishop_609");
			link.l1 = StringFromKey("Bishop_610");
			link.l1.go = "Bishop_Plantation_1";
		break;

		case "Bishop_Plantation_1":
			dialog.text = StringFromKey("Bishop_611");
			link.l1 = StringFromKey("Bishop_612");
			link.l1.go = "Bishop_Plantation_2";
		break;

		case "Bishop_Plantation_2":
			dialog.text = StringFromKey("Bishop_613");
			link.l1 = StringFromKey("Bishop_614");
			link.l1.go = "Bishop_Plantation_3";
		break;

		case "Bishop_Plantation_3":
			dialog.text = StringFromKey("Bishop_615");
			link.l1 = StringFromKey("Bishop_616");
			link.l1.go = "Bishop_Plantation_4";
		break;

		case "Bishop_Plantation_4":
			dialog.text = StringFromKey("Bishop_617");
			link.l1 = StringFromKey("Bishop_618");
			link.l1.go = "Bishop_Plantation_5";
		break;

		case "Bishop_Plantation_5":
			dialog.text = StringFromKey("Bishop_619");
			link.l1 = StringFromKey("Bishop_620");
			link.l1.go = "Bishop_Plantation_6";
		break;

		case "Bishop_Plantation_6":
			dialog.text = StringFromKey("Bishop_621");
			link.l1 = StringFromKey("Bishop_622");
			link.l1.go = "Bishop_Plantation_7";
		break;

		case "Bishop_Plantation_7":
			CharacterTurnByChr(npchar, CharacterFromID("CBL_Kent"));
			CharacterTurnByChr(CharacterFromID("CBL_Kent"), npchar);
			dialog.text = StringFromKey("Bishop_623");
			link.l1 = StringFromKey("Bishop_624");
			link.l1.go = "Bishop_Plantation_8";
		break;

		case "Bishop_Plantation_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LAi_SetCitizenType(npchar);

			sld = CharacterFromID("CBL_Kent");
			LAi_SetActorType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestFunctionDelay("CapBloodLine_ReloadToStid", 2.0);

			loc = &Locations[FindLocation("Bridgetown_Plantation")];
			loc.locators_radius.goto.goto19 = 0.5;
		break;

		case "Bishop_Plantation_9": // вторая встреча на плантации
			dialog.text = StringFromKey("Bishop_625");
			link.l1 = StringFromKey("Bishop_626");
			link.l1.go = "Bishop_Plantation_10";
			CapBloodLine_NeedToSavePitt_12();
		break;

		case "Bishop_Plantation_10":
			dialog.text = StringFromKey("Bishop_627");
			link.l1 = StringFromKey("Bishop_628");
			link.l1.go = "Bishop_Plantation_11";
		break;

		case "Bishop_Plantation_11":
			dialog.text = StringFromKey("Bishop_629");
			link.l1 = StringFromKey("Bishop_630");
			link.l1.go = "Bishop_Plantation_12";
		break;

		case "Bishop_Plantation_12":
			dialog.text = StringFromKey("Bishop_631");
			link.l1 = StringFromKey("Bishop_632");
			link.l1.go = "Bishop_Plantation_13";
		break;

		case "Bishop_Plantation_13":
			dialog.text = StringFromKey("Bishop_633");
			link.l1 = StringFromKey("Bishop_634");
			link.l1.go = "Bishop_Plantation_14";
		break;

		case "Bishop_Plantation_14":
			dialog.text = StringFromKey("Bishop_635");
			link.l1 = StringFromKey("Bishop_636");
			link.l1.go = "Bishop_Plantation_15";
		break;

		case "Bishop_Plantation_15":
			dialog.text = StringFromKey("Bishop_637");
			link.l1 = StringFromKey("Bishop_638");
			link.l1.go = "Bishop_Plantation_16";
			AddCharacterExpToSkill(PChar, SKILL_LEADERSHIP, 10);
		break;

		case "Bishop_Plantation_16":
			dialog.text = StringFromKey("Bishop_639");
			link.l1 = StringFromKey("Bishop_640");
			link.l1.go = "Bishop_Plantation_17";
		break;

		case "Bishop_Plantation_17":
			dialog.text = StringFromKey("Bishop_641");
			link.l1 = StringFromKey("Bishop_642");
			link.l1.go = "Bishop_Plantation_18";
		break;

		case "Bishop_Plantation_18":
			dialog.text = StringFromKey("Bishop_643");
			link.l1 = StringFromKey("Bishop_644");
			link.l1.go = "Bishop_Plantation_19";
		break;

		case "Bishop_Plantation_19":
			DialogExit();
			CharacterTurnAy(pchar, -3.2);
			locCameraFromToPos(23.05, 2.96, 109.74, true, 55.05, -21.55, 30.9);
			LAi_FadeEx(0.5, 1.0, 0.5, "", "CapBloodLine_NeedToSavePitt_14", "");
		break;

		case "Bishop_Plantation_20":
			CharacterTurnAy(pchar, 2.2);
			CharacterTurnAy(npchar, 2.2);
			PlaySound("Sea Battles_01\Cannonade_dense.wav");
			dialog.text = StringFromKey("Bishop_645");
			link.l1 = "...";
			link.l1.go = "Bishop_Plantation_21";
		break;

		case "Bishop_Plantation_21":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto18", "none", "", "", "CapBloodLine_ClearSoldier", -1);

			locCameraSleep(false);
			locCameraToPos(30.46, 3.42, 107.05, false);
			locCameraTarget(npchar);
			AddDialogExitQuestFunction("CapBloodLine_NeedToSavePitt_17");
		break;


		case "BishopOnLlagas_1":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);

			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_875");
			link.l1.go = "BishopOnLlagas_2";
		break;

		case "BishopOnLlagas_2":
			dialog.text = StringFromKey("Bishop_876");
			link.l1 = StringFromKey("Bishop_877");
			link.l1.go = "BishopOnLlagas_3";
		break;

		case "BishopOnLlagas_3":
			dialog.text = StringFromKey("Bishop_878");
			link.l1 = StringFromKey("Bishop_879");
			link.l1.go = "BishopOnLlagas_4";
		break;

		case "BishopOnLlagas_4":
			dialog.text = StringFromKey("Bishop_880");
			link.l1 = StringFromKey("Bishop_881");
			link.l1.go = "BishopOnLlagas_5";
		break;

		case "BishopOnLlagas_5":
			dialog.text = StringFromKey("Bishop_882");
			link.l1 = StringFromKey("Bishop_883");
			link.l1.go = "BishopOnLlagas_6";
		break;

		case "BishopOnLlagas_6":
			dialog.text = StringFromKey("Bishop_884");
			link.l1 = StringFromKey("Bishop_608");
			link.l1.go = "BishopOnLlagas_ToHugtorp_1";
		break;

		case "BishopOnLlagas_ToHugtorp_1":
			StartInstantDialogNow("Hugtorp", "BishopOnLlagas_Hugtorp_1", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "BishopOnLlagas_Hugtorp_1":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);

			dialog.text = StringFromKey("Bishop_885");
			link.l1 = StringFromKey("Bishop_608");
			link.l1.go = "BishopOnLlagas_BackToBishop_1";
		break;

		case "BishopOnLlagas_BackToBishop_1":
			StartInstantDialogNow("Bishop", "BishopOnLlagas_7", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "BishopOnLlagas_7":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);

			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_886");
			link.l1.go = "BishopOnLlagas_8";
		break;

		case "BishopOnLlagas_8":
			dialog.text = StringFromKey("Bishop_887");
			link.l1 = StringFromKey("Bishop_888");
			link.l1.go = "BishopOnLlagas_9";
		break;

		case "BishopOnLlagas_9":
			dialog.text = StringFromKey("Bishop_889");
			link.l1 = StringFromKey("Bishop_890");
			link.l1.go = "BishopOnLlagas_10";
		break;

		case "BishopOnLlagas_10":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_891");
			link.l1.go = "BishopOnLlagas_ToHugtorp_2";
		break;

		case "BishopOnLlagas_ToHugtorp_2":
			StartInstantDialogNow("Hugtorp", "BishopOnLlagas_Hugtorp_2", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "BishopOnLlagas_Hugtorp_2":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);

			dialog.text = StringFromKey("Bishop_892");
			link.l1 = StringFromKey("Bishop_608");
			link.l1.go = "BishopOnLlagas_BackToBishop_2";
		break;

		case "BishopOnLlagas_BackToBishop_2":
			StartInstantDialogNow("Bishop", "BishopOnLlagas_11", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "BishopOnLlagas_11":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);

			dialog.text = StringFromKey("Bishop_893");
			link.l1 = StringFromKey("Bishop_894");
			link.l1.go = "BishopOnLlagas_ToVolverston";
		break;

		case "BishopOnLlagas_ToVolverston":
			StartInstantDialogNow("Volverston", "BishopOnLlagas_Volverston_1", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "BishopOnLlagas_Volverston_1":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);

			dialog.text = StringFromKey("Bishop_895");
			link.l1 = StringFromKey("Bishop_896");
			link.l1.go = "BishopOnLlagas_Volverston_2";
		break;

		case "BishopOnLlagas_Volverston_2":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_897");
			link.l1.go = "BishopOnLlagas_12";
		break;

		case "BishopOnLlagas_12":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_898");
			link.l1.go = "BishopOnLlagas_13";
		break;

		case "BishopOnLlagas_13":
			StartInstantDialogNow("Bishop", "BishopOnLlagas_14", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "BishopOnLlagas_14":
			CharacterTurnByChr(CharacterFromID("Bishop"), pchar);
			CharacterTurnByChr(pchar, CharacterFromID("Bishop"));

			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_899");
			link.l1.go = "BishopOnLlagas_14_1";
		break;

		case "BishopOnLlagas_14_1":
			dialog.text = StringFromKey("Bishop_900");
			link.l1 = StringFromKey("Bishop_901");
			link.l1.go = "BishopOnLlagas_ToOfficer";
		break;

		case "BishopOnLlagas_ToOfficer":
			StartInstantDialogNow("CBL_OfficerBishop", "BishopOnLlagas_Officer_1", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "BishopOnLlagas_Officer_1":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_902");
			link.l1 = StringFromKey("Bishop_903");
			link.l1.go = "BishopOnLlagas_Officer_2";
		break;

		case "BishopOnLlagas_Officer_2":
			dialog.text = StringFromKey("Bishop_904");
			link.l1 = StringFromKey("Bishop_905");
			link.l1.go = "BishopOnLlagas_Officer_3";
		break;

		case "BishopOnLlagas_Officer_3":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_906");
			link.l1.go = "BishopOnLlagas_Officer_4";
		break;

		case "BishopOnLlagas_Officer_4":
			StartInstantDialogNow("Bishop", "BishopOnLlagas_15", "Quest\CapBloodLine\Bishop.c", true);

			sld = CharacterFromID("CBL_OfficerBishop");
			sld.lifeDay = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "quest", "quest20", "none", "", "", "", -1);

			sld = CharacterFromID("CBL_OfficerBishop_1");
			sld.lifeDay = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "quest", "quest19", "none", "", "", "", -1);
		break;

		case "BishopOnLlagas_15":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);

			dialog.text = StringFromKey("Bishop_907");
			link.l1 = StringFromKey("Bishop_908");
			link.l1.go = "BishopOnLlagas_16";
		break;

		case "BishopOnLlagas_16":
			StartInstantDialogNow("Volverston", "BishopOnLlagas_17", "Quest\CapBloodLine\Bishop.c", true);
		break;


		case "BishopOnLlagas_17":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);

			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_909");
			link.l1.go = "BishopOnLlagas_18";
		break;

		case "BishopOnLlagas_18":
			dialog.text = StringFromKey("Bishop_910");
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CapBloodLine_ToSeaAgain");
		break;

		case "BishopOnLlagas_After":
			dialog.text = StringFromKey("Bishop_911");
			link.l1 = StringFromKey("Bishop_912");
			link.l1.go = "exit";
			NextDiag.TempNode = "BishopOnLlagas_After";
		break;

		case "BishopOverboard_1":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			dialog.text = StringFromKey("Bishop_608");
			link.l1 = StringFromKey("Bishop_913");
			link.l1.go = "BishopOverboard_3";
		break;

		case "BishopOverboard_3":
			dialog.text = StringFromKey("Bishop_608");
			link.l1 = StringFromKey("Bishop_914");
			link.l1.go = "BishopOverboard_4";
		break;

		case "BishopOverboard_4":
			dialog.text = StringFromKey("Bishop_608");
			link.l1 = StringFromKey("Bishop_915");
			link.l1.go = "BishopOverboard_6";
		break;

		case "BishopOverboard_6":
			dialog.text = StringFromKey("Bishop_608");
			link.l1 = StringFromKey("Bishop_916");
			link.l1.go = "BishopOverboard_7";
		break;

		case "BishopOverboard_7":
			dialog.text = StringFromKey("Bishop_608");
			link.l1 = StringFromKey("Bishop_917");
			link.l1.go = "BishopOverboard_End";
		break;

		case "BishopOverboard_End":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuestFunction("CapBloodLine_BishopGoToSwiming");
		break;

		case "BishopOverboard_8":
			dialog.text = StringFromKey("Bishop_608");
			link.l1 = StringFromKey("Bishop_918");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CapBloodLine_BishopGoToSwiming_4");
		break;
		// < ---- Бишоп

		// ---> Арабелла
		case "ArabellaOnPlantation":
			dialog.text = StringFromKey("Bishop_553");
			link.l1 = StringFromKey("Bishop_554");
			link.l1.go = "ArabellaOnPlantation_1";
		break;

		case "ArabellaOnPlantation_1":
			dialog.text = StringFromKey("Bishop_555");
			link.l1 = StringFromKey("Bishop_556");
			link.l1.go = "ArabellaOnPlantation_2";
		break;

		case "ArabellaOnPlantation_2":
			dialog.text = StringFromKey("Bishop_557");
			link.l1 = StringFromKey("Bishop_558");
			link.l1.go = "ArabellaOnPlantation_3";
		break;

		case "ArabellaOnPlantation_3":
			dialog.text = StringFromKey("Bishop_559");
			link.l1 = StringFromKey("Bishop_560");
			link.l1.go = "ArabellaOnPlantation_4";
			CapBloodLine_ArabellaSlaveSitDown();
		break;

		case "ArabellaOnPlantation_4":
			dialog.text = "";
			link.l1 = StringFromKey("Bishop_561");
			link.l1.go = "ArabellaOnPlantation_5";
		break;

		case "ArabellaOnPlantation_5":
			dialog.text = StringFromKey("Bishop_562");
			link.l1 = StringFromKey("Bishop_563");
			link.l1.go = "ArabellaOnPlantation_6";
		break;

		case "ArabellaOnPlantation_6":
			dialog.text = StringFromKey("Bishop_564");
			link.l1 = StringFromKey("Bishop_565");
			link.l1.go = "ArabellaOnPlantation_7";
		break;

		case "ArabellaOnPlantation_7":
			dialog.text = StringFromKey("Bishop_566");
			link.l1 = StringFromKey("Bishop_567");
			link.l1.go = "ArabellaOnPlantation_8";
		break;

		case "ArabellaOnPlantation_8":
			dialog.text = StringFromKey("Bishop_568");
			link.l1 = StringFromKey("Bishop_569");
			link.l1.go = "ArabellaOnPlantation_9";
		break;

		case "ArabellaOnPlantation_9":
			dialog.text = StringFromKey("Bishop_570");
			link.l1 = StringFromKey("Bishop_571");
			link.l1.go = "ArabellaOnPlantation_10";
		break;

		case "ArabellaOnPlantation_10":
			dialog.text = StringFromKey("Bishop_572");
			link.l1 = StringFromKey("Bishop_573");
			link.l1.go = "ArabellaOnPlantation_11";
		break;

		case "ArabellaOnPlantation_11":
			dialog.text = StringFromKey("Bishop_574");
			link.l1 = StringFromKey("Bishop_575");
			link.l1.go = "ArabellaOnPlantation_12";
		break;

		case "ArabellaOnPlantation_12":
			dialog.text = StringFromKey("Bishop_576");
			link.l1 = StringFromKey("Bishop_577");
			link.l1.go = "ArabellaOnPlantation_13";
		break;

		case "ArabellaOnPlantation_13":
			dialog.text = StringFromKey("Bishop_578");
			link.l1 = StringFromKey("Bishop_579");
			link.l1.go = "ArabellaOnPlantation_14";
		break;

		case "ArabellaOnPlantation_14":
			dialog.text = StringFromKey("Bishop_580");
			link.l1 = StringFromKey("Bishop_581");
			link.l1.go = "ArabellaOnPlantation_15";
		break;

		case "ArabellaOnPlantation_15":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_582");
			link.l1.go = "ArabellaOnPlantation_16";
		break;

		case "ArabellaOnPlantation_16":
			dialog.text = StringFromKey("Bishop_583");
			link.l1 = StringFromKey("Bishop_584");
			link.l1.go = "ArabellaOnPlantation_17";
		break;

		case "ArabellaOnPlantation_17":
			dialog.text = StringFromKey("Bishop_585");
			link.l1 = StringFromKey("Bishop_586");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CapBloodLine_ArabellaGoHome");
		break;

		case "ArabellaOnPlantation_18": // второй заход на плантарь
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_647");
			link.l1.go = "ArabellaOnPlantation_19";
		break;

		case "ArabellaOnPlantation_19":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorMoveToPoint(pchar, false, -8.17, 3.43, -25.43, "", -1.0);
			locCameraFlyToPositionLookToPoint(-14.18, 4.81, -29.62, -11.46, 4.54, -22.92, -1.62, 5.10, -32.77, 1, 9550/GetDeltaTime());
			Pchar.FuncCameraFly = "CapBloodLine_OnPlantationAgain_3";
		break;

		case "ArabellaOnPlantation_20":
			dialog.text = StringFromKey("Bishop_649");
			link.l1 = StringFromKey("Bishop_650");
			link.l1.go = "ArabellaOnPlantation_21";
		break;

		case "ArabellaOnPlantation_21":
			dialog.text = StringFromKey("Bishop_651");
			link.l1 = StringFromKey("Bishop_652");
			link.l1.go = "ArabellaOnPlantation_22";
		break;

		case "ArabellaOnPlantation_22":
			dialog.text = StringFromKey("Bishop_653");
			link.l1 = StringFromKey("Bishop_654");
			link.l1.go = "ArabellaOnPlantation_23";
		break;

		case "ArabellaOnPlantation_23":
			dialog.text = StringFromKey("Bishop_655");
			link.l1 = StringFromKey("Bishop_656");
			link.l1.go = "ArabellaOnPlantation_24";
		break;

		case "ArabellaOnPlantation_24":
			dialog.text = StringFromKey("Bishop_657");
			link.l1 = StringFromKey("Bishop_658");
			link.l1.go = "ArabellaOnPlantation_25";
		break;

		case "ArabellaOnPlantation_25":
			dialog.text = StringFromKey("Bishop_659");
			link.l1 = StringFromKey("Bishop_660");
			link.l1.go = "ArabellaOnPlantation_26";
		break;

		case "ArabellaOnPlantation_26":
			dialog.text = StringFromKey("Bishop_661");
			link.l1 = StringFromKey("Bishop_662");
			link.l1.go = "ArabellaOnPlantation_27";
		break;

		case "ArabellaOnPlantation_27":
			dialog.text = StringFromKey("Bishop_663");
			link.l1 = StringFromKey("Bishop_664");
			link.l1.go = "ArabellaOnPlantation_28";
		break;

		case "ArabellaOnPlantation_28":
			dialog.text = StringFromKey("Bishop_665");
			link.l1 = StringFromKey("Bishop_666");
			link.l1.go = "ArabellaOnPlantation_29";
		break;

		case "ArabellaOnPlantation_29":
			dialog.text = StringFromKey("Bishop_667");
			link.l1 = StringFromKey("Bishop_668");
			link.l1.go = "ArabellaOnPlantation_30";
		break;

		case "ArabellaOnPlantation_30":
			dialog.text = StringFromKey("Bishop_669");
			link.l1 = StringFromKey("Bishop_670");
			link.l1.go = "ArabellaOnPlantation_31";
		break;

		case "ArabellaOnPlantation_31":
			dialog.text = StringFromKey("Bishop_671");
			link.l1 = StringFromKey("Bishop_672");
			link.l1.go = "ArabellaOnPlantation_32";
		break;

		case "ArabellaOnPlantation_32":
			dialog.text = StringFromKey("Bishop_673");
			link.l1 = StringFromKey("Bishop_674");
			link.l1.go = "ArabellaOnPlantation_33";
		break;

		case "ArabellaOnPlantation_33":
			dialog.text = StringFromKey("Bishop_675");
			link.l1 = StringFromKey("Bishop_676");
			link.l1.go = "ArabellaOnPlantation_34";
		break;

		case "ArabellaOnPlantation_34":
			dialog.text = StringFromKey("Bishop_677");
			link.l1 = StringFromKey("Bishop_678");
			link.l1.go = "ArabellaOnPlantation_35";
		break;

		case "ArabellaOnPlantation_35":
			dialog.text = StringFromKey("Bishop_679");
			link.l1 = StringFromKey("Bishop_680");
			link.l1.go = "ArabellaOnPlantation_36";
		break;

		case "ArabellaOnPlantation_36":
			dialog.text = StringFromKey("Bishop_681");
			link.l1 = StringFromKey("Bishop_682");
			link.l1.go = "ArabellaOnPlantation_37";
		break;

		case "ArabellaOnPlantation_37":
			DialogExit();
			LAi_FadeEx(1.0, 1.0, 1.0, "", "CapBloodLine_OnPlantationAgain_2", "");

			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto18", "", -1);

			sld = CharacterFromID("Arabella");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto18", "", -1);
		break;

		case "ArabellaOnPlantation_38":
			dialog.text = StringFromKey("Bishop_683");
			link.l1 = StringFromKey("Bishop_684");
			link.l1.go = "ArabellaOnPlantation_39";
		break;

		case "ArabellaOnPlantation_39":
			dialog.text = StringFromKey("Bishop_685");
			link.l1 = StringFromKey("Bishop_686");
			link.l1.go = "ArabellaOnPlantation_40";
		break;

		case "ArabellaOnPlantation_40":
			dialog.text = StringFromKey("Bishop_687");
			link.l1 = StringFromKey("Bishop_688");
			link.l1.go = "ArabellaOnPlantation_41";
		break;

		case "ArabellaOnPlantation_41":
			dialog.text = StringFromKey("Bishop_689");
			link.l1 = StringFromKey("Bishop_690");
			link.l1.go = "ArabellaOnPlantation_42";
		break;

		case "ArabellaOnPlantation_42":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetPlayerType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 8.0);
			ReturnToPlantation();
			EndQuestMovie();
			DeleteAttribute(&TEV, "StopTimeScale");
			AddQuestRecord("Arabella", "6");
			QuestPointerToLoc("Bridgetown_Plantation", "quest", "sit2");
		break;

		// В пакгаузе
		case "ArabellaOnPackhouse":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_692");
			link.l1.go = "ArabellaOnPackhouse_1";
		break;

		case "ArabellaOnPackhouse_1":
			dialog.text = StringFromKey("Bishop_693");
			link.l1 = StringFromKey("Bishop_694");
			link.l1.go = "ArabellaOnPackhouse_2";
		break;

		case "ArabellaOnPackhouse_2":
			dialog.text = StringFromKey("Bishop_695");
			link.l1 = StringFromKey("Bishop_696");
			link.l1.go = "ArabellaOnPackhouse_3";
		break;

		case "ArabellaOnPackhouse_3":
			dialog.text = StringFromKey("Bishop_697");
			link.l1 = StringFromKey("Bishop_698");
			link.l1.go = "ArabellaOnPackhouse_4";
		break;

		case "ArabellaOnPackhouse_4":
			dialog.text = StringFromKey("Bishop_699");
			link.l1 = StringFromKey("Bishop_700");
			link.l1.go = "ArabellaOnPackhouse_5";
		break;

		case "ArabellaOnPackhouse_5":
			dialog.text = StringFromKey("Bishop_701");
			link.l1 = StringFromKey("Bishop_702");
			link.l1.go = "ArabellaOnPackhouse_6";
		break;

		case "ArabellaOnPackhouse_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.CantRun");
			AddQuestRecord("Arabella", "3");
			LAi_SetActorType(npchar);
			LAi_SetPlayerType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);

			sld = CharacterFromID("Slave_Arabella_2");
			LAi_SetStayType(sld);// Если прокликать, будет баг, так что лучше так
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);

			sld = CharacterFromID("Slave_Arabella_3");
			LAi_SetStayType(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		break;

		case "ArabellaAndSlave":
			CharacterTurnByChr(CharacterFromID("Slave_Arabella_2"), CharacterFromID("Arabella"));
			CharacterTurnByChr(CharacterFromID("Slave_Arabella_3"), CharacterFromID("Arabella"));
			CharacterTurnByChr(CharacterFromID("Arabella"), CharacterFromID("Slave_Arabella_2"));
			dialog.text = StringFromKey("Bishop_703");
			link.l1 = StringFromKey("Bishop_704");
			link.l1.go = "ArabellaAndSlave_1";
		break;

		case "ArabellaAndSlave_1":
			DialogExit();
			sld = CharacterFromID("Slave_Arabella_2");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto6", "", -1);

			sld = CharacterFromID("Slave_Arabella_3");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto3", "", -1);

			sld = CharacterFromID("Arabella");
			CharacterTurnToLoc(sld, "goto", "goto5");
			LAi_SetStayType(sld);
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
		break;

		case "ArabellaOnPirs": // На пирсе
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_706");
			link.l1.go = "ArabellaOnPirs_1";
		break;

		case "ArabellaOnPirs_1":
			dialog.text = StringFromKey("Bishop_707");
			link.l1 = StringFromKey("Bishop_708");
			link.l1.go = "ArabellaOnPirs_2";
		break;

		case "ArabellaOnPirs_2":
			dialog.text = StringFromKey("Bishop_709");
			link.l1 = StringFromKey("Bishop_710");
			link.l1.go = "ArabellaOnPirs_3";
		break;

		case "ArabellaOnPirs_3":
			dialog.text = StringFromKey("Bishop_711");
			link.l1 = StringFromKey("Bishop_712");
			link.l1.go = "ArabellaOnPirs_4";
		break;

		case "ArabellaOnPirs_4":
			dialog.text = StringFromKey("Bishop_713");
			link.l1 = StringFromKey("Bishop_714");
			link.l1.go = "ArabellaOnPirs_5";
		break;

		case "ArabellaOnPirs_5":
			dialog.text = StringFromKey("Bishop_715");
			link.l1 = StringFromKey("Bishop_716");
			link.l1.go = "ArabellaOnPirs_6";
		break;

		case "ArabellaOnPirs_6":
			dialog.text = StringFromKey("Bishop_717");
			link.l1 = StringFromKey("Bishop_718");
			link.l1.go = "ArabellaOnPirs_7";
		break;

		case "ArabellaOnPirs_7":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "gate1_back", "none", "", "", "", 5);
			AddQuestRecord("Arabella", "5");

			sld = CharacterFromID("CBL_Kent");
			sld.dialog.currentnode = "Kent_OnCity";
			ChangeCharacterAddressGroup(sld, "Bridgetown_Town", "goto", "goto10");
			LAi_SetActorTypeNoGroup(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "ArabellaOnHouse":
			dialog.text = StringFromKey("Bishop_719");
			link.l1 = StringFromKey("Bishop_720");
			link.l1.go = "ArabellaOnHouse_1";
		break;

		case "ArabellaOnHouse_1":
			dialog.text = StringFromKey("Bishop_721");
			link.l1 = "...";
			link.l1.go = "ArabellaOnHouse_2";
		break;

		case "ArabellaOnHouse_2":
			StartInstantDialogNow("ArabelaService", "ArabellaOnHouse_3", "Quest\CapBloodLine\Bishop.c", false);
		break;

		case "ArabellaOnHouse_3":
			// locCameraFromToPos(14.72, 4.04, 102.83, true, -55.05, -39.55, 196.9);
			// CharacterTurnByChr(CharacterFromID("ArabelaService"), CharacterFromID("Arabella"));
			// CharacterTurnByChr(pchar, CharacterFromID("Arabella"));
			dialog.text = StringFromKey("Bishop_723");
			link.l1 = "";
			link.l1.go = "ArabellaOnHouse_4";
		break;

		case "ArabellaOnHouse_4":
			StartInstantDialogNow("Arabella", "ArabellaOnHouse_5", "Quest\CapBloodLine\Bishop.c", false);
		break;

		case "ArabellaOnHouse_5":
			locCameraFromToPos(14.72, 4.04, 102.83, true, -55.05, -39.55, 196.9);
			PlaySound("Interface\door_locked.wav");
			dialog.text = StringFromKey("Bishop_725");
			link.l1 = "";
			link.l1.go = "ArabellaOnHouse_6";
		break;

		case "ArabellaOnHouse_6":
			DialogExit();
			DoQuestReloadToLocation("Bridgetown_Plantation_Sp1", "goto", "goto1", "");
			SetFunctionLocationCondition("CapBloodLine_ArabellaInHouse_5", "Bridgetown_Plantation_Sp1", false);
		break;

		case "ArabellaOnHouse_7": // внутри дома
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_728");
			link.l1.go = "ArabellaOnHouse_8";
		break;

		case "ArabellaOnHouse_8":
			dialog.text = StringFromKey("Bishop_729");
			link.l1 = StringFromKey("Bishop_730");
			link.l1.go = "ArabellaOnHouse_9";
		break;

		case "ArabellaOnHouse_9":
			dialog.text = StringFromKey("Bishop_731");
			link.l1 = StringFromKey("Bishop_732");
			link.l1.go = "ArabellaOnHouse_10";
		break;

		case "ArabellaOnHouse_10":
			StartInstantDialogNow("ArabelaService", "ArabellaOnHouse_11", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "ArabellaOnHouse_11":
			CharacterTurnByChr(CharacterFromID("ArabelaService"), CharacterFromID("Arabella"));
			CharacterTurnByChr(CharacterFromID("Arabella"), CharacterFromID("ArabelaService"));
			dialog.text = StringFromKey("Bishop_733");
			link.l1 = "";
			link.l1.go = "ArabellaOnHouse_12";
		break;

		case "ArabellaOnHouse_12":
			StartInstantDialogNow("Arabella", "ArabellaOnHouse_13", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "ArabellaOnHouse_13":
			CharacterTurnByChr(CharacterFromID("ArabelaService"), CharacterFromID("Arabella"));
			CharacterTurnByChr(CharacterFromID("Arabella"), CharacterFromID("ArabelaService"));
			dialog.text = StringFromKey("Bishop_735");
			link.l1 = "...";
			link.l1.go = "ArabellaOnHouse_14";
		break;

		case "ArabellaOnHouse_14":
			CharacterTurnByChr(CharacterFromID("Arabella"), pchar);
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_738");
			link.l1.go = "ArabellaOnHouse_15";
		break;

		case "ArabellaOnHouse_15":
			dialog.text = StringFromKey("Bishop_739");
			link.l1 = StringFromKey("Bishop_740");
			link.l1.go = "ArabellaOnHouse_16";
		break;

		case "ArabellaOnHouse_16":
			StartInstantDialogNow("ArabelaService", "ArabellaOnHouse_17", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "ArabellaOnHouse_17":
			CharacterTurnByChr(CharacterFromID("ArabelaService"), CharacterFromID("Arabella"));
			CharacterTurnByChr(CharacterFromID("Arabella"), CharacterFromID("ArabelaService"));
			dialog.text = StringFromKey("Bishop_741");
			link.l1 = StringFromKey("Bishop_608");
			link.l1.go = "ArabellaOnHouse_18";
		break;

		case "ArabellaOnHouse_18":
			StartInstantDialogNow("Arabella", "ArabellaOnHouse_19", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "ArabellaOnHouse_19":
			dialog.text = StringFromKey("Bishop_743");
			link.l1 = StringFromKey("Bishop_744");
			link.l1.go = "ArabellaOnHouse_20";
		break;

		case "ArabellaOnHouse_20":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "", -1);

			DoQuestReloadToLocation("Bridgetown_Plantation", "goto", "goto1", "");
			Locations[FindLocation("Bridgetown_Plantation")].locators_radius.quest.detector3 = 1.7;
			SetFunctionLocationCondition("CapBloodLine_ArabellaInHouse_6", "Bridgetown_Plantation", false);
		break;

		case "ArabellaOnHouse_21":
			PlaySound("Voice\" + VoiceGetLanguage() + "\Gr_Woman_Citizen_1.wav");
			dialog.text = StringFromKey("Bishop_745");
			link.l1 = StringFromKey("Bishop_746");
			link.l1.go = "ArabellaOnHouse_22";
		break;

		case "ArabellaOnHouse_22":
			dialog.text = StringFromKey("Bishop_747");
			link.l1 = StringFromKey("Bishop_748");
			link.l1.go = "ArabellaOnHouse_23";
			CapBloodLine_ArabellaInHouse_7();
		break;

		case "ArabellaOnHouse_23":
			DialogExit();

			sld = CharacterFromID("Arabella");
			sld.dialog.currentnode = "ArabellaOnHouse_24";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "ArabellaOnHouse_24":
			dialog.text = StringFromKey("Bishop_749");
			link.l1 = StringFromKey("Bishop_750");
			link.l1.go = "ArabellaOnHouse_25";
		break;

		case "ArabellaOnHouse_25":
			StartInstantDialogNow("ArabelaService", "ArabellaOnHouse_26", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "ArabellaOnHouse_26":
			dialog.text = StringFromKey("Bishop_751");
			link.l1 = "";
			link.l1.go = "ArabellaOnHouse_27";
		break;

		case "ArabellaOnHouse_27":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "goto", "goto22", "none", "", "", "", -1);
			AddDialogExitQuestFunction("CapBloodLine_ArabellaInHouse_11");
		break;

		// <--- Арабелла
		// -->Эндрю Бейнс

		case "EBStep_0":
			dialog.text = StringFromKey("Bishop_96");
			link.l1 = StringFromKey("Bishop_97");
			link.l1.go = "Exit_RunAway";
			DeleteAttribute(npchar, "talker");
			Pchar.questTemp.CapBloodLine.sLocator = "Reload5";
			Pchar.questTemp.CapBloodLine.iTime = -1;
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerToLoc("Estate", "reload", "reload3");
			QuestPointerToLoc("EstateBadroom1", "quest", "quest1");
			LocatorReloadEnterDisable("Estate", "reload5", true);
		break;

		case "EBStep_1":
			dialog.text = StringFromKey("Bishop_98");
			link.l1 = StringFromKey("Bishop_99");
			link.l1.go = "Exit";
			NextDiag.TempNode = "EBStep_2";
			AddDialogExitQuestFunction("CureLordMovie");
		break;

		case "EBStep_2":
			dialog.text = StringFromKey("Bishop_100");
			link.l1 = StringFromKey("Bishop_101");
			link.l1.go = "Exit";
			NextDiag.TempNode = "EBStep_3";
			AddDialogExitQuestFunction("DragunInvansion");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "EBStep_3":
			dialog.text = StringFromKey("Bishop_102");
			link.l1 = StringFromKey("Bishop_103");
			link.l1.go = "Exit";
			NextDiag.TempNode = "EBStep_3";
		break;

		//--> капитан Гобард

		case "CGStep_1":
			dialog.text = StringFromKey("Bishop_104");
			link.l1 = StringFromKey("Bishop_105");
			link.l1.go = "CGStep_2";
		break;

		case "CGStep_2":
			dialog.text = StringFromKey("Bishop_106");
			link.l1 = StringFromKey("Bishop_107");
			link.l1.go = "CGStep_3";
		break;

		case "CGStep_3":
			dialog.text = StringFromKey("Bishop_108");
			link.l1 = StringFromKey("Bishop_109");
			link.l1.go = "CGStep_4";
		break;

		case "CGStep_4":
			dialog.text = StringFromKey("Bishop_110");
			link.l1 = StringFromKey("Bishop_111");
			link.l1.go = "CGStep_5";
		break;

		case "CGStep_5":
			dialog.text = StringFromKey("Bishop_112");
			link.l1 = StringFromKey("Bishop_113");
			link.l1.go = "CGStep_6";
		break;

		case "CGStep_6":
			dialog.text = StringFromKey("Bishop_114");
			link.l1 = StringFromKey("Bishop_115");
			link.l1.go = "CGStep_7";
		break;

		case "CGStep_7":
			dialog.text = StringFromKey("Bishop_116");
			link.l1 = StringFromKey("Bishop_117");
			link.l1.go = "CGStep_8";
		break;

		case "CGStep_8":
			dialog.text = StringFromKey("Bishop_118");
			link.l1 = StringFromKey("Bishop_119");
			link.l1.go = "GFight";
			NextDiag.TempNode = "CGStep_9";
		break;

		case "CGStep_9":
			dialog.text = StringFromKey("Bishop_123", LinkRandPhrase(
						StringFromKey("Bishop_120"),
						StringFromKey("Bishop_121"),
						StringFromKey("Bishop_122")));
			link.l1 = StringFromKey("Bishop_127", LinkRandPhrase(
						StringFromKey("Bishop_124"),
						StringFromKey("Bishop_125"),
						StringFromKey("Bishop_126")));
			link.l1.go = "Exit";
			AddDialogExitQuestFunction("CapGobartAttack");
			NextDiag.TempNode = "CGStep_9";
		break;

		// -->Стражник на входе
		case "First Guard":
			DeleteQuestCondition("CapBloodLine_ReturnCitizenDialogAgain");
			dialog.text = StringFromKey("Bishop_128");
			link.l1 = StringFromKey("Bishop_129");
			link.l1.go = "GStep_0";
			RemoveLandQuestMark_Main(npchar, "CapBloodLine");
		break;

		case "GStep_0":
			dialog.text = StringFromKey("Bishop_130");
			link.l1 = StringFromKey("Bishop_131");
			link.l1.go = "Exit";
			LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//отпираем резиденцию
			LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
			chrDisableReloadToLocation = false;

			//солдата на место
			// LAi_SetLoginTime(npchar, 6.0, 23.0);
			npchar.protector = false;
			npchar.protector.CheckAlways = 0;
			npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";
		break;

		case "GStep_1":
			dialog.text = StringFromKey("Bishop_132");
			if (GetCharacterItem(pchar, "migraine_potion") > 0)
			{
				link.l1 = StringFromKey("Bishop_133");
				link.l1.go = "Exit";
				LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//отпираем резиденцию
				LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
				//солдата на место
				npchar.protector = false;
				npchar.protector.CheckAlways = 0;
				npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			}
			else
			{
				link.l1 = StringFromKey("Bishop_134");
				link.l1.go = "GStep_2";
			}
		break;

		case "GStep_2":
			dialog.text = StringFromKey("Bishop_135");
			link.l1 = StringFromKey("Bishop_136");
			link.l1.go = "Exit";
			NextDiag.TempNode = "GStep_3";
			AddQuestRecord("WeaponsForEscape", "12");
		break;

		case "GStep_3":
			dialog.text = StringFromKey("Bishop_137");
			if (GetCharacterItem(pchar, "migraine_potion") > 0)
			{
				link.l1 = StringFromKey("Bishop_138");
				link.l1.go = "Exit";
				LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//отпираем резеденцию
				LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
				//солдата на место
				npchar.protector = false;
				npchar.protector.CheckAlways = 0;
				npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";
				NextDiag.TempNode = "First time";
			}
			else
			{
				link.l1 = StringFromKey("Bishop_139");
				link.l1.go = "Exit";
				NextDiag.TempNode = "GStep_3";
			}
		break;

		// --> Стид
		case "SStep_0":
			ChangeCharacterReputation(PChar, 5);
			dialog.text = StringFromKey("Bishop_140");
			link.l1 = StringFromKey("Bishop_141");
			link.l1.go = "SStep_1";
		break;

		case "SStep_1":
			dialog.text = StringFromKey("Bishop_142");
			link.l1 = StringFromKey("Bishop_143");
			link.l1.go = "SStep_2";
		break;

		case "SStep_2":
			dialog.text = StringFromKey("Bishop_144");
			link.l1.go = "Exit";
			NextDiag.TempNode = "SStep_3";
			//HardCoffee открыть двери в гостинную
			LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", false);
			LocatorReloadEnterDisable("Bridgetown_Townhall", "reload2", false);
			LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
			sld = GetCharacter(NPC_GenerateCharacter("MisStid", "AnnaDeLeiva", "woman", "towngirl2", 10, ENGLAND, 3, false));
			sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
			sld.name = FindPersonalName("MisStid_name");
			sld.lastname = FindPersonalName("MisStid_lastname");
			sld.greeting = "Gr_Dama";
			sTemp = GetNationNameByType(ENGLAND) + "_citizens";
			LAi_group_MoveCharacter(sld, sTemp);
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "CommonBedroom", "goto", "goto5");
			AddQuestRecord("CapBloodLine_q1", "2");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			AddLandQuestmark_Main(sld, "CapBloodLine");

			AddDialogExitQuestFunction("CapBloodLine_CureMisStid_AddQuestPointers_2");
		break;

		case "SStep_3":
			sld = &characters[GetCharacterIndex("MisStid")];
			if (sld.quest.meeting != "1")
			{
				dialog.text = StringFromKey("Bishop_145");
				link.l1 = StringFromKey("Bishop_146");
				link.l1.go = "Exit";
			}
			else
			{
				dialog.text = StringFromKey("Bishop_147");
				link.l1 = StringFromKey("Bishop_148");
				link.l1.go = "SStep_4";
				link.l2 = StringFromKey("Bishop_149");
				link.l2.go = "SStep_5";
			}
		break;

		case "SStep_4":
			if (!CheckAttribute(NPChar, "quest.SStep4_Enter"))
			{
				ChangeCharacterReputation(PChar, 5); // благородный ответ
				NPChar.quest.SStep4_Enter = true; // fix
			}
			dialog.text = StringFromKey("Bishop_150");
			link.l1 = StringFromKey("Bishop_151");
			link.l1.go = "Exit";
			NextDiag.TempNode = "SStep_4";
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "SStep_5":
			ChangeCharacterReputation(PChar, -2);
			dialog.text = StringFromKey("Bishop_152");
			link.l1 = StringFromKey("Bishop_153");
			link.l1.go = "SStep_6";
			link.l2 = StringFromKey("Bishop_154");
			link.l2.go = "SStep_7";
			link.l3 = StringFromKey("Bishop_155");
			link.l3.go = "SStep_8";
		break;

		case "SStep_6":
			AddMoneyToCharacter(pchar, 500);
			dialog.text = StringFromKey("Bishop_156");
			link.l1 = StringFromKey("Bishop_157");
			link.l1.go = "Exit";
			NextDiag.TempNode = "SStep_4";
			AddQuestRecord("CapBloodLine_q1", "4");
			AddQuestUserData("CapBloodLine_q1", "iMoney", FindMoneyString(500));
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "SStep_7":
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = StringFromKey("Bishop_158");
			link.l1 = StringFromKey("Bishop_159");
			link.l1.go = "Exit";
			NextDiag.TempNode = "SStep_4";
			AddQuestRecord("CapBloodLine_q1", "4");
			AddQuestUserData("CapBloodLine_q1", "iMoney", 1000);
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "SStep_8":
			AddCharacterExpToSkill(pchar, "Sneak", 25); // умение обманывать для скрытности тоже важно
			ChangeCharacterReputation(PChar, -5);
			AddMoneyToCharacter(pchar, 2500);
			dialog.text = StringFromKey("Bishop_160");
			link.l1 = StringFromKey("Bishop_161");
			link.l1.go = "Exit";
			NextDiag.TempNode = "SStep_4";
			AddQuestRecord("CapBloodLine_q1", "5");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "SStep_9":
			dialog.text = StringFromKey("Bishop_162");
			link.l1 = StringFromKey("Bishop_163");
			link.l1.go = "Exit";
			NextDiag.TempNode = "First time";
			LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", false);
			LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape3_1";
		break;

		case "Pride_Arrive":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			dialog.text = StringFromKey("Bishop_752");
			link.l1 = StringFromKey("Bishop_753");
			link.l1.go = "Pride_Arrive_1";
		break;

		case "Pride_Arrive_1":
			DialogExit();
			npchar.dialog.currentnode = "Pride_Arrive_Repeat";

			QuestPointerDelLoc("Bridgetown_Plantation", "reload", "reload1_back");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload3_back");
			QuestPointerToLoc("Bridgetown_town", "reload", "reload5_back");
			QuestPointerToLoc("Bridgetown_Townhall", "reload", "reload1_back");
			SetFunctionLocationCondition("CapBloodLine_InPackhouse", "Bridgetown_Packhouse", false);

			ref rloc = &Locations[FindLocation("Bridgetown_Packhouse")];
			rloc.models.always.rugs = "angar_rugs";
			rloc.models.always.rugs.level = 65538;
			rloc.models.day.charactersPatch = "angar_rug_patch";
			rloc.models.night.charactersPatch = "angar_rug_patch";

			aref arQuest;
			makearef(arQuest, rloc.locators_radius.quest);

			for (int i = 1; i <= 6; i++)
			{
				string sLoc = "quest0" + i;

				QuestPointerToLoc("Bridgetown_Packhouse", "quest", sLoc);
				arQuest.(sLoc) = 0.5;
			}
			sld = CharacterFromID("Bridgetown_Shipyarder");
			sld.questTemp.BloogGoToPackhouse = true;
			AddLandQuestmark_Main(sld, "CapBloodLine");
			AddQuestRecord("CapBloodLine_q1", "12");
			// LocatorReloadEnterDisable("Bridgetown_Shipyard", "reload2", false);
		break;

		case "Pride_Arrive_Repeat":
			if (!CheckAttribute(npchar, "questTemp.StidWarn"))
			{
				npchar.questTemp.StidWarn = 1;
			}
			else
			{
				if (sti(npchar.questTemp.StidWarn) < 3) npchar.questTemp.StidWarn = sti(npchar.questTemp.StidWarn) + 1;
			}

			switch (sti(npchar.questTemp.StidWarn))
			{
				case 1:
					dialog.text = StringFromKey("Bishop_754");
					link.l1 = StringFromKey("Bishop_755");
					link.l1.go = "exit";
				break;

				case 2:
					dialog.text = StringFromKey("Bishop_756");
					link.l1 = StringFromKey("Bishop_757");
					link.l1.go = "exit";
				break;

				case 3:
					dialog.text = StringFromKey("Bishop_758");
					link.l1 = StringFromKey("Bishop_759");
					link.l1.go = "Pride_Arrive_Threw_Out";
				break;
			}
			NextDiag.TempNode = "Pride_Arrive_Repeat";
		break;

		case "Pride_Arrive_Threw_Out":
			DialogExit();
			DoQuestReloadToLocation("Bridgetown_town", "reload", "reload3_back", "");
			LocatorReloadEnterDisable("Bridgetown_town", "reload3_back", true);
		break;

		case "StidOnBed":
			dialog.text = StringFromKey("Bishop_866");
			link.l1 = StringFromKey("Bishop_867");
			link.l1.go = "StidOnBed_1";
		break;

		case "StidOnBed_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Barman_idle", "CapBloodLine_InStidBedroom_2", 5);
			locCameraFromToPos(-3.50, 4.26, -2.88, true, 0.05, 0.55, -2.9);
		break;

		case "StidOnBed_8":
			locCameraFromToPos(-3.50, 4.26, -2.88, true, 0.05, 0.55, -2.9);
			dialog.text = StringFromKey("Bishop_760");
			link.l1 = StringFromKey("Bishop_761");
			link.l1.go = "StidOnBed_8_1";
		break;

		case "StidOnBed_8_1":
			dialog.text = StringFromKey("Bishop_762");
			link.l1 = StringFromKey("Bishop_763");
			link.l1.go = "StidOnBed_8_2";
		break;

		case "StidOnBed_8_2":
			dialog.text = StringFromKey("Bishop_764");
			link.l1 = StringFromKey("Bishop_765");
			link.l1.go = "StidOnBed_9";
		break;

		case "StidOnBed_9":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("EscapeFormBarbados", "7");

			sld = CharacterFromID("MisStid");
			sld.dialog.currentnode = "MissStid_InRoom_3";
			AddLandQuestmark_Main(sld, "CapBloodLine");
		break;

		case "StidOnBed_10": // На кровати - второй заход
			locCameraFromToPos(-3.50, 4.26, -2.88, true, 0.05, 0.55, -2.9);
			QuestPointerDelLoc("CommonBedroom", "goto", "goto6");
			dialog.text = StringFromKey("Bishop_766");
			link.l1 = StringFromKey("Bishop_767");
			link.l1.go = "StidOnBed_HelpDen";
			link.l2 = StringFromKey("Bishop_768");
			link.l2.go = "StidOnBed_11";
		break;

		case "StidOnBed_HelpDen":
			AddCharacterExpToSkill(PChar, SKILL_SNEAK, 10);
			dialog.text = StringFromKey("Bishop_769");
			link.l1 = StringFromKey("Bishop_770");
			link.l1.go = "StidOnBed_12";
		break;

		case "StidOnBed_11":
			AddCharacterExpToSkill(PChar, SKILL_FORTUNE, 10);
			dialog.text = StringFromKey("Bishop_771");
			link.l1 = StringFromKey("Bishop_772");
			link.l1.go = "StidOnBed_12";
		break;

		case "StidOnBed_12":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Barman_idle", "CapBloodLine_InStidBedroom_3", 5);
			locCameraFromToPos(-3.50, 4.26, -2.88, true, 0.05, 0.55, -2.9);
			Locations[FindLocation("Bridgetown_Plantation")].locators_radius.quest.detector1 = 15.0;
		break;

		case "StidOnBed_13":
			dialog.text = StringFromKey("Bishop_773");
			link.l1 = StringFromKey("Bishop_774");
			link.l1.go = "StidOnBed_14";
		break;

		case "StidOnBed_14":
			dialog.text = StringFromKey("Bishop_775");
			link.l1 = StringFromKey("Bishop_776");
			link.l1.go = "StidOnBed_14_1";
		break;

		case "StidOnBed_14_1":
			dialog.text = StringFromKey("Bishop_777");
			link.l1 = StringFromKey("Bishop_778");
			link.l1.go = "StidOnBed_15";
		break;

		case "StidOnBed_15":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_CharacterDisableDialog(npchar);
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
		break;

		case "StidOnBed_16":
			locCameraFromToPos(-3.50, 4.26, -2.88, true, 0.05, 0.55, -2.9);
			dialog.text = StringFromKey("Bishop_779");
			link.l1 = StringFromKey("Bishop_780");
			link.l1.go = "exit";
			NextDiag.TempNode = "StidOnBed_16";
		break;

		// Мисс Стид
		case "MSStep_0":
			dialog.text = StringFromKey("Bishop_164");
			link.l1 = StringFromKey("Bishop_165");
			link.l1.go = "Exit";
			NextDiag.TempNode = "MSStep_1";

			sld = GetCharacter(NPC_GenerateCharacter("Waker", "vrach_2", "man", "man", 7, ENGLAND, 3, false));
			sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
			sld.name = FindPersonalName("Waker_name");
			sld.lastname = FindPersonalName("Waker_lastname");
			sld.greeting = "Gr_medic";
			sTemp = GetNationNameByType(ENGLAND) + "_citizens";
			LAi_group_MoveCharacter(sld, sTemp);
			ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "goto", "goto6");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 2.0, 0);

			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			if (GetCharacterbyLocation("Bridgetown_town", "soldiers", "soldier2") >= 0)
			{
				RemoveLandQuestmark_Main(&characters[GetCharacterbyLocation("Bridgetown_town", "soldiers", "soldier2")], "CapBloodLine");
			}
			AddLandQuestmark_Main(sld, "CapBloodLine");
			AddLandQuestmark_Main(CharacterFromID("Bridgetown_Mayor"), "CapBloodLine");
			AddDialogExitQuestFunction("CapBloodLine_CureMisStid_AddQuestPointers_3");

			pchar.quest.CureMisStid.win_condition.l1 = "item";
			pchar.quest.CureMisStid.win_condition.l1.item = "migraine_potion";
			pchar.quest.CureMisStid.function = "CapBloodLine_q1_End";

			sld = ItemsFromID("migraine_potion");
			sld.shown = true;
			sld.startLocation = "CommonPirateHouse";
			sld.startLocator = "item1";

			AddQuestRecord("CapBloodLine_q1", "3");
		break;

		case "MSStep_1":
			dialog.text = StringFromKey("Bishop_166");
			if (Pchar.questTemp.CapBloodLine.stat == "CureMisStid_Complite")
			{
				link.l1 = StringFromKey("Bishop_167");
				link.l1.go = "MSStep_2";
				TakeItemFromCharacter(Pchar, "migraine_potion");
				RemoveLandQuestMark_Main(npchar, "CapBloodLine");
			}
			else
			{
				link.l1 = StringFromKey("Bishop_168");
				link.l1.go = "Exit";
			}
		break;

		case "MSStep_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			QuestPointerDelLoc("Bridgetown_Town", "reload", "reload3_back");
			QuestPointerDelLoc("Bridgetown_Townhall", "reload", "reload3");
			QuestPointerDelLoc("Bridgetown_TownhallRoom", "reload", "reload2");
			//Вывести экран в темноту, выполнить квест questFadeOut, вернуть всё обратно, выполнить квест questFadeIn
			//LAi_Fade("", "CapBloodLine_q1_Complited");

			chrDisableReloadToLocation = true;
			bDisableCharacterMenu = true;
			LAi_SetActorType(pchar);
			DoQuestFunctionDelay("CapBloodLine_q1_Complited", 1.5);
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");

			n = GetCharacterbyLocation("Bridgetown_town", "soldiers", "soldier2");
			if (n >= 0) LAi_SetLoginTime(&Characters[n], 6.0, 23.0);
			AddCharacterExpToSkill(PChar, SKILL_LEADERSHIP, 20);
		break;

		case "MSStep_3":
			dialog.text = StringFromKey("Bishop_169");
			link.l1 = StringFromKey("Bishop_170");
			link.l1.go = "MSStep_4";
			DeleteAttribute(npchar, "talker");
		break;

		case "MSStep_4":
			dialog.text = StringFromKey("Bishop_171");
			link.l1 = StringFromKey("Bishop_173");
			link.l1.go = "MSStep_5";
			link.l2 = StringFromKey("Bishop_172");
			link.l2.go = "MSStep_5";
		break;

		case "MSStep_5":
			dialog.text = StringFromKey("Bishop_174");
			link.l1 = StringFromKey("Bishop_175");
			link.l1.go = "MSStep_6";
		break;

		case "MSStep_6":
			dialog.text = StringFromKey("Bishop_176");
			link.l1 = StringFromKey("Bishop_177");
			link.l1.go = "MSStep_7";
		break;

		case "MSStep_7":
			dialog.text = StringFromKey("Bishop_178");
			link.l1 = StringFromKey("Bishop_179");
			TakeItemFromCharacter(Pchar, "migraine_potion");
			AddQuestRecord("WeaponsForEscape", "15");
			link.l1.go = "Exit";
			NextDiag.TempNode = "MSStep_8";
		break;

		case "MSStep_8":
			dialog.text = StringFromKey("Bishop_180");
			link.l1 = StringFromKey("Bishop_181");
			link.l1.go = "Exit";
			NextDiag.TempNode = "MSStep_8";
		break;

		case "MissStid_InRoom":
			dialog.text = StringFromKey("Bishop_781");
			link.l1 = StringFromKey("Bishop_782");
			link.l1.go = "MissStid_InRoom_1";
		break;

		case "MissStid_InRoom_1":
			DialogExit();
			npchar.dialog.currentnode = "MissStid_InRoom_Repeat";
			LAi_SetOwnerType(npchar);
			QuestPointerToLoc("CommonBedroom", "goto", "goto6");

			sld = CharacterFromID("Stid_Clone_1");
			sld.dialog.currentnode = "StidOnBed";
			LAi_CharacterEnableDialog(sld);
			AddLandQuestmark_Main(sld, "CapBloodLine");

			pchar.quest.CapBloodLine_InStidBedroom_1.win_condition.l1 = "locator";
			pchar.quest.CapBloodLine_InStidBedroom_1.win_condition.l1.location = "CommonBedroom";
			pchar.quest.CapBloodLine_InStidBedroom_1.win_condition.l1.locator_group = "goto";
			pchar.quest.CapBloodLine_InStidBedroom_1.win_condition.l1.locator = "goto6";
			pchar.quest.CapBloodLine_InStidBedroom_1.function = "CapBloodLine_InStidBedroom_1";
		break;

		case "MissStid_InRoom_Repeat":
			dialog.text = StringFromKey("Bishop_783");
			link.l1 = StringFromKey("Bishop_784");
			link.l1.go = "exit";
			NextDiag.TempNode = "MissStid_InRoom_Repeat";
		break;

		case "MissStid_InRoom_3":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			dialog.text = StringFromKey("Bishop_785");
			link.l1 = StringFromKey("Bishop_786");
			link.l1.go = "MissStid_InRoom_4";
		break;

		case "MissStid_InRoom_4":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);

			// превентивные меры, против срыва скрипта заставки
			TEV.StopTimeScale = true;
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;

			DoQuestFunctionDelay("CapBloodLine_InStidBedroom_2", 2.0);
		break;

		// ---> andre39966 Прибытие мистера Блада на Барбадос
		case "SOnSquere":
			dialog.text = StringFromKey("Bishop_526");
			link.l1 = StringFromKey("Bishop_527");
			link.l1.go = "SOnSquere_1";
		break;

		case "SOnSquere_1":
			dialog.text = StringFromKey("Bishop_528");
			link.l1 = "";
			link.l1.go = "SOnSquere_2";
		break;

		case "SOnSquere_2":
			dialog.text = StringFromKey("Bishop_529");
			link.l1 = StringFromKey("Bishop_530");
			link.l1.go = "SOnSquere_3";
			CharacterTurnByChr(CharacterFromID("Bishop_Clone"), CharacterFromID("Pitt_Clone"));
			CharacterTurnByChr(CharacterFromID("FluitCap"), CharacterFromID("Pitt_Clone"));
		break;

		case "SOnSquere_3":
			dialog.text = StringFromKey("Bishop_531");
			link.l1 = StringFromKey("Bishop_532");
			link.l1.go = "SOnSquere_4";
			CharacterTurnByChr(CharacterFromID("Bishop_Clone"), CharacterFromID("FluitCap"));
			CharacterTurnByChr(CharacterFromID("FluitCap"), CharacterFromID("Bishop_Clone"));
		break;

		case "SOnSquere_4":
			dialog.text = StringFromKey("Bishop_533");
			link.l1 = StringFromKey("Bishop_534");
			link.l1.go = "SOnSquere_5";
			CharacterTurnByChr(CharacterFromID("Stid_Clone"), CharacterFromID("Arabella"));
			CharacterTurnByChr(CharacterFromID("Arabella"), CharacterFromID("Stid_Clone"));
		break;

		case "SOnSquere_5":
			dialog.text = StringFromKey("Bishop_535");
			link.l1 = StringFromKey("Bishop_536");
			link.l1.go = "SOnSquere_6";
			sld = CharacterFromID("Stid_Clone");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto25", "CapBloodLine_StidAndArabellaLeave", -1);

			ref arabella = CharacterFromID("Arabella");
			LAi_SetActorType(arabella);
			LAi_ActorFollow(arabella, sld, "", -1);
		break;

		case "SOnSquere_6":
			DialogExit();
			sld = CharacterFromID("FluitCap");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest12", "CapBloodLine_FluitCapTurnToBishop", -1);

			sld = CharacterFromID("Bishop_Clone");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "quest", "quest11", "CapBloodLine_BishopStartDialog", -1);
			LAi_FadeEx(1.0, 1.0, 1.0, "", "CapBloodLine_SeaCameraWiew_7", "");
			locCameraFromToPos(0.25, 5.46, 5.94, true, -10.05, 0.05, 10.2);
		break;

		case "SOnSquere_7":
			dialog.text = StringFromKey("Bishop_537");
			link.l1 = StringFromKey("Bishop_538");
			link.l1.go = "SOnSquere_8";
		break;

		case "SOnSquere_8":
			dialog.text = StringFromKey("Bishop_539");
			link.l1 = StringFromKey("Bishop_540");
			link.l1.go = "SOnSquere_9";
		break;

		case "SOnSquere_9":
			CharacterTurnByChr(CharacterFromID("Bishop_Clone"), CharacterFromID("Arabella"));
			dialog.text = StringFromKey("Bishop_541");
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CapBloodLine_ArabellaWantBuyBlood");
		break;

		case "SOnSquere_10":
			CharacterTurnByChr(CharacterFromID("Bishop_Clone"), CharacterFromID("Arabella"));
			CharacterTurnByChr(CharacterFromID("Arabella"), CharacterFromID("Bishop_Clone"));
			dialog.text = StringFromKey("Bishop_542");
			link.l1 = StringFromKey("Bishop_543");
			link.l1.go = "SOnSquere_11";
		break;

		case "SOnSquere_11":
			DialogExit();
			locCameraFromToPos(-0.23, 5.44, 12.17, true, -13.05, -2.55, 0.2);
			LAi_FadeEx(1.0, 1.0, 1.0, "", "CapBloodLine_AllBandNearBlood", "");
		break;

		case "SOnSquere_12":
			dialog.text = StringFromKey("Bishop_544");
			link.l1 = "";
			link.l1.go = "SOnSquere_13";
		break;

		case "SOnSquere_13":
			CharacterTurnByChr(CharacterFromID("Bishop_Clone"), pchar);
			dialog.text = StringFromKey("Bishop_545");
			link.l1 = "";
			link.l1.go = "SOnSquere_14";
		break;

		case "SOnSquere_14":
			DialogExit();
			locCameraFromToPos(-5.21, 5.40, 8.11, true, 2.55, -0.55, 0.2);
			DoQuestFunctionDelay("CapBloodLine_AllBandNearBlood_2", 0.5);
		break;

		case "SOnSquere_15":
			CharacterTurnByChr(CharacterFromID("Bishop_Clone"), CharacterFromID("FluitCap"));
			CharacterTurnByChr(CharacterFromID("FluitCap"), CharacterFromID("Bishop_Clone"));
			dialog.text = "";
			link.l1 = StringFromKey("Bishop_546");
			link.l1.go = "SOnSquere_16";
		break;

		case "SOnSquere_16":
			dialog.text = "";
			link.l1 = StringFromKey("Bishop_547");
			link.l1.go = "SOnSquere_17";
		break;

		case "SOnSquere_17":
			DialogExit();
			locCameraFromToPos(-5.21, 5.40, 8.11, true, 2.55, -0.55, 0.2);
			DoQuestFunctionDelay("CapBloodLine_AllBandNearBlood_3", 0.5);
		break;

		case "SOnSquere_18":
			CharacterTurnByChr(CharacterFromID("Bishop_Clone"), CharacterFromID("Stid_Clone"));
			CharacterTurnByChr(CharacterFromID("Stid_Clone"), CharacterFromID("Bishop_Clone"));
			dialog.text = StringFromKey("Bishop_548");
			link.l1 = "";
			link.l1.go = "SOnSquere_19";
		break;

		case "SOnSquere_19":
			DialogExit();
			locCameraFromToPos(-5.21, 5.40, 8.11, true, 2.55, -0.55, 0.2);
			DoQuestFunctionDelay("CapBloodLine_AllBandNearBlood_4", 0.5);
		break;

		case "SOnSquere_20":
			CharacterTurnByChr(CharacterFromID("Bishop_Clone"), CharacterFromID("FluitCap"));
			CharacterTurnByChr(CharacterFromID("FluitCap"), CharacterFromID("Bishop_Clone"));
			dialog.text = StringFromKey("Bishop_549");
			link.l1 = StringFromKey("Bishop_550");
			link.l1.go = "SOnSquere_22";
		break;

		case "SOnSquere_22":
			dialog.text = StringFromKey("Bishop_551");
			link.l1 = StringFromKey("Bishop_552");
			link.l1.go = "SOnSquere_23";
		break;

		case "SOnSquere_23":
			DialogExit();
			locCameraFromToPos(-5.21, 5.40, 8.11, true, 2.55, -0.55, 0.2);
			AddQuestRecord("Arabella", "1");
			CapBloodLine_AllBishopsGroupGoAway();
			DoQuestFunctionDelay("CapBloodLine_AllBishopsGroupGoAway_1", 2.0);
		break;

		// Кент
		case "KentOnPlantation":
			dialog.text = StringFromKey("Bishop_587");
			link.l1 = StringFromKey("Bishop_586");
			link.l1.go = "KentOnPlantation_1";
		break;

		case "KentOnPlantation_1":
			dialog.text = StringFromKey("Bishop_588");
			link.l1 = StringFromKey("Bishop_589");
			link.l1.go = "KentOnPlantation_2";
		break;

		case "KentOnPlantation_2":
			dialog.text = StringFromKey("Bishop_590");
			link.l1 = StringFromKey("Bishop_586");
			link.l1.go = "KentOnPlantation_3";
		break;

		case "KentOnPlantation_3":
			// AddDialogExitQuestFunction("ChangePIRATES");
			DialogExit();
			LAi_SetCitizenType(NPChar);
			LAi_CharacterDisableDialog(npchar);
			AddQuestRecord("CapBloodLine_q1", "1");
			QuestPointerToLoc("Bridgetown_plantation", "reload", "reload1_back");
		break;

		case "KentOnPlantation_4":
			dialog.text = StringFromKey("Bishop_787");
			link.l1 = "";
			link.l1.go = "KentOnPlantation_5";
			CapBloodLine_NeedToSavePitt_21();
		break;

		case "KentOnPlantation_5":
			DialogExit();
			sld = CharacterFromID("CBL_Kent");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "goto", "goto10", "none", "", "", "", 5);
			CapBloodLine_NeedToSavePitt_22();
			locCameraFromToPos(20.22, 3.03, 109.78, true, 75.05, -13.55, 86.9);
		break;

		case "Kent_OnCity":
			dialog.text = StringFromKey("Bishop_919");
			link.l1 = StringFromKey("Bishop_920");
			link.l1.go = "Kent_OnCity_1";
		break;

		case "Kent_OnCity_1":
			dialog.text = StringFromKey("Bishop_921");
			link.l1 = "...";
			link.l1.go = "Kent_OnCity_2";
		break;

		case "Kent_OnCity_2":
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "gate1_back", "", -1);
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			bDisableCharacterMenu = true;
			DialogExit();
			DoQuestFunctionDelay("CapBloodLine_ReturnAtPlantation", 1.5);
		break;

		// <--- andre39966 Прибытие мистера Блада на Барбадос

		//--> Нэтталл
		case "NStep_0":
			dialog.text = StringFromKey("Bishop_182");
			link.l1 = StringFromKey("Bishop_183");
			link.l1.go = "Nettl_Away";
			NextDiag.TempNode = "NStep_1";
			Pchar.questTemp.CapBloodLine.TalkWithNettl = true;
		break;

		case "NStep_1":
			dialog.text = StringFromKey("Bishop_184");
			if (Pchar.questTemp.CapBloodLine.stat == "needMoney")
			{
				link.l1 = StringFromKey("Bishop_185");
				link.l1.go = "NStep_2";
			}
			else
			{
				link.l1 = StringFromKey("Bishop_186");
				link.l1.go = "Exit";
				NextDiag.TempNode = "NStep_1";
			}
		break;

		case "NStep_2":
			dialog.text = StringFromKey("Bishop_187");
			if (makeint(pchar.money) >= 25000)
			{
				link.l1 = StringFromKey("Bishop_188");
				link.l1.go = "NStep_3";
			}
			else
			{
				link.l1 = StringFromKey("Bishop_189");
				link.l1.go = "Exit";
				NextDiag.TempNode = "NStep_5";
				AddLandQuestmark_Main_WithCondition(NPChar, "CapBloodLine", "CapBloodLine_NeedMoney_Nettl_QuestMarkCondition");
			}
		break;

		case "NStep_3":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "CapBloodLine_q2");

			AddMoneyToCharacter(pchar, -25000);
			dialog.text = StringFromKey("Bishop_190");
			link.l1 = StringFromKey("Bishop_191");
			link.l1.go = "NStep_3_1";
		break;

		case "NStep_3_1":
			DialogExit();
			InterfaceStates.Buttons.Save.enable = false;
			bDisableFastReload = true;
			bDisableCharacterMenu = true;
			LAi_CharacterDisableDialog(npchar);
			chrDisableReloadToLocation = true;
			LAi_SetActorType(pchar);
			DoQuestFunctionDelay("CapBloodLine_q3_FinalPreparation", 2.0);
		break;

		case "NStep_4":
			dialog.text = StringFromKey("Bishop_192");
			link.l1 = StringFromKey("Bishop_193");
			link.l1.go = "Exit";
			NextDiag.TempNode = "NStep_4";
		break;

		case "NStep_5":
			dialog.text = StringFromKey("Bishop_194");
			if (makeint(pchar.money) >= 25000)
			{
				link.l1 = StringFromKey("Bishop_195");
				link.l1.go = "NStep_3";
			}
			else
			{
				link.l1 = StringFromKey("Bishop_196");
				link.l1.go = "Exit";
				NextDiag.TempNode = "NStep_5";
			}
		break;

		case "Nettl_Away":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NettlOnTavern", -1);
			SetFunctionExitFromLocationCondition("Nettl_Away_Force", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NStep_6":
			dialog.text = StringFromKey("Bishop_197");
			link.l1 = StringFromKey("Bishop_198");
			link.l1.go = "Nettl_Away";
			NextDiag.TempNode = "NStep_5";
			Pchar.questTemp.CapBloodLine.TalkWithNettl = true;
		break;

		case "NStep_7": // у верфи
			CloseQuestHeader("CapBloodLine_q2");
			dialog.text = StringFromKey("Bishop_593");
			link.l1 = StringFromKey("Bishop_594");
			link.l1.go = "NStep_8";
		break;

		case "NStep_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 4);
			chrDisableReloadToLocation = false;
			LAi_SetPlayerType(pchar);
			AddQuestRecord("EscapeFormBarbados", "6");
			AddCharacterExpToSkill(PChar, SKILL_SNEAK, 50);
			SetFunctionLocationCondition("CapBloodLine_BishopWaitBlood", "Bridgetown_plantation", false);
			SetFunctionLocationConditionDelay("CapBloodLine_ReturnCitizenDialogAgain", "Bridgetown_town", false, 0.2);
			SetFunctionTimerCondition("CapBloodLine_FailQuest", 0, 0, 1, false);
			QuestPointerToLoc("Bridgetown_Town", "reload", "gate1_back");

			loc = &Locations[FindLocation("Bridgetown_Plantation")];
			loc.locators_radius.goto.goto19 = 9.0;
		break;

		case "NettalTiredWait": // В таверне, после провала побега
			RemoveLandQuestMark_Main(npchar, "CapBloodLine");
			dialog.text = StringFromKey("Bishop_788");
			link.l1 = StringFromKey("Bishop_789");
			link.l1.go = "NettalTiredWait_1";
		break;

		case "NettalTiredWait_1":
			dialog.text = StringFromKey("Bishop_790");
			link.l1 = StringFromKey("Bishop_791");
			link.l1.go = "NettalTiredWait_2";
		break;

		case "NettalTiredWait_2":
			dialog.text = StringFromKey("Bishop_792");
			link.l1 = StringFromKey("Bishop_793");
			link.l1.go = "NettalTiredWait_3";
		break;

		case "NettalTiredWait_3":
			DialogExit();
			npchar.lifeDay = 0;
			npchar.dialog.currentnode = "NettalTiredWait_Return";
			LocatorReloadEnterDisable("Bridgetown_Town", "reload3_back", false);
			LocatorReloadEnterDisable("Bridgetown_Town", "reloadR1", false);
			QuestPointerDelLoc("Bridgetown_Town", "reload", "reload4_back");
			QuestPointerToLoc("Bridgetown_Town", "reload", "reload3_back");
			QuestPointerToLoc("Bridgetown_Town", "reload", "reloadR1");
			QuestPointerToLoc("Bridgetown_TownhallRoom", "reload", "reload2");
			QuestPointerToLoc("Bridgetown_Townhall", "reload", "reload3");
			AddQuestRecord("EscapeFormBarbados", "9");
			SetFunctionLocationCondition("CapBloodLine_InGuberRoomAgain", "CommonBedroom", false);
		break;

		case "NettalTiredWait_Return":
			dialog.text = StringFromKey("Bishop_794");
			link.l1 = StringFromKey("Bishop_795");
			link.l1.go = "exit";
			NextDiag.TempNode = "NettalTiredWait_Return";
		break;

		//--> Вакер

		case "WStep_0":
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			dialog.text = StringFromKey("Bishop_199");
			link.l1 = StringFromKey("Bishop_200");
			link.l1.go = "WStep_2";
		break;

		case "WStep_1":
			dialog.text = StringFromKey("Bishop_201");
			link.l1 = StringFromKey("Bishop_202");
			link.l1.go = "WStep_2";
		break;

		case "WStep_2":
			dialog.text = StringFromKey("Bishop_203");
			link.l1 = StringFromKey("Bishop_204");
			link.l1.go = "Exit_Away";
			Pchar.questTemp.CapBloodLine.sLocator = "reload1";
			Pchar.questTemp.CapBloodLine.iTime = 5;

			sld = GetCharacter(NPC_GenerateCharacter("Den", "vrach_1", "man", "man", 7, ENGLAND, 3, false));
			sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
			sld.name = FindPersonalName("Den_name");
			sld.lastname = FindPersonalName("Den_lastname");
			sld.greeting = "Gr_medic";
			sTemp = GetNationNameByType(ENGLAND) + "_citizens";
			LAi_group_MoveCharacter(sld, sTemp);
			ChangeCharacterAddressGroup(sld, "BridgeTown_town", "goto", "goto3");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 2.0, 0);
			AddQuestRecord("CapBloodLine_q2", "1");

			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			AddDialogExitQuestFunction("CapBloodLine_WateDen");
		break;

		//Предложение Вакера - вторая встреча
		case "WStep_3":
			dialog.text = StringFromKey("Bishop_205");
			link.l1 = StringFromKey("Bishop_206");
			link.l1.go = "WStep_4";
		break;

		case "WStep_4":
			dialog.text = StringFromKey("Bishop_207");
			link.l1 = StringFromKey("Bishop_208");
			link.l1.go = "WStep_5";
		break;

		case "WStep_5":
			dialog.text = StringFromKey("Bishop_209");
			link.l1 = StringFromKey("Bishop_210");
			link.l1.go = "WStep_6";
		break;

		case "WStep_6":
			dialog.text = StringFromKey("Bishop_211");
			link.l1 = StringFromKey("Bishop_212");
			link.l1.go = "WStep_7";
			link.l2 = StringFromKey("Bishop_213");
			link.l2.go = "WStep_8";
		break;

		case "WStep_7":
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			dialog.text = StringFromKey("Bishop_214");
			link.l1 = StringFromKey("Bishop_215");
			link.l1.go = "WStep_9";
		break;

		case "WStep_8":
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			dialog.text = StringFromKey("Bishop_216");
			link.l1 = StringFromKey("Bishop_217");
			link.l1.go = "WStep_9";
		break;

		case "WStep_9":
			dialog.text = StringFromKey("Bishop_218");
			link.l1 = StringFromKey("Bishop_219");
			link.l1.go = "Exit";
			n = FindLocation("Bridgetown_tavern");
			locations[n].reload.l2.disable = true;
			Pchar.questTemp.CapBloodLine.stat = "WakerOfferComplited";
			AddQuestRecord("CapBloodLine_q2", "4");
			NextDiag.TempNode = "WStep_10";
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");

			sld = CharacterFromID("Pitt");
			if (sld.location != "Bridgetown_Plantation")
			{
				ChangeCharacterAddressGroup(sld, "Bridgetown_Plantation", "goto", "goto" + (rand(17) + 1));
				LAi_SetLoginTime(sld, 6.0, 21.0);
			}
			AddLandQuestmark_Main(sld, "CapBloodLine");
			LAi_SetCitizenType(sld);

			QuestPointerToLoc("Bridgetown_town", "reload", "gate1_back");
			QuestPointerToLoc("Bridgetown_tavern", "reload", "reload1_back");
			QuestPointerToLoc("Bridgetown_tavern_upstairs", "reload", "reload1_back");
			QuestPointerDelLoc("Bridgetown_tavern", "reload", "reload2_back");
			AddCharacterExpToSkill(PChar, SKILL_FORTUNE, 30);
		break;

		case "WStep_10":
			dialog.text = StringFromKey("Bishop_220");
			link.l1 = StringFromKey("Bishop_221");
			link.l1.go = "Exit";
			NextDiag.TempNode = "WStep_10";
		break;

		//Предложение Вакера - заключение

		case "WStep_11":
			dialog.text = StringFromKey("Bishop_222");
			link.l1 = StringFromKey("Bishop_223");
			link.l1.go = "WStep_12";
		break;

		case "WStep_12":
			dialog.text = StringFromKey("Bishop_224");
			link.l1 = StringFromKey("Bishop_225");
			link.l1.go = "WStep_13";
			AddMoneyToCharacter(pchar, 18000);
		break;

		case "WStep_13":
			dialog.text = StringFromKey("Bishop_226");
			if (Pchar.questTemp.CapBloodLine.TalkWithNettl == false)
			{
				link.l1 = StringFromKey("Bishop_227");
				link.l1.go = "WStep_14";
			}
			else
			{
				link.l1 = StringFromKey("Bishop_228");
				link.l1.go = "WStep_15";
			}
			AddDialogExitQuestFunction("CapBloodLine_NeedMoney_AddQuestMarks");
			AddDialogExitQuestFunction("CapBloodLine_NeedMoney_AddQuestPointers");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload4_back");
			QuestPointerDelLoc("Bridgetown_tavern", "reload", "reload2_back");
		break;

		case "WStep_14":
			dialog.text = StringFromKey("Bishop_229");
			link.l1 = StringFromKey("Bishop_230");
			link.l1.go = "Exit";
			NextDiag.TempNode = "WStep_16";
			n = FindLocation("Bridgetown_tavern");
			locations[n].reload.l2.disable = true;
			Pchar.questTemp.CapBloodLine.stat = "needMoney";
			AddQuestRecord("CapBloodLine_q2", "7");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "WStep_15":
			dialog.text = StringFromKey("Bishop_231");
			link.l1 = StringFromKey("Bishop_232");
			link.l1.go = "Exit";
			NextDiag.TempNode = "WStep_16";
			n = FindLocation("Bridgetown_tavern");
			locations[n].reload.l2.disable = true;
			Pchar.questTemp.CapBloodLine.stat = "needMoney";
			AddQuestRecord("CapBloodLine_q2", "7");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "WStep_16":
			dialog.text = StringFromKey("Bishop_233");
			link.l1 = StringFromKey("Bishop_234");
			link.l1.go = "Exit";
			NextDiag.TempNode = "WStep_16";
		break;

		//--> Мистер Дэн

		case "DStep_0":
			if (GetCharacterItem(pchar, "migraine_potion") == 0) Pchar.questTemp.CapBloodLine.isNotPotion = true;
			if (GetCharacterItem(pchar, "migraine_potion") > 0) AddQuestRecord("CapBloodLine_q1", "8");
			dialog.text = StringFromKey("Bishop_235");
			link.l1 = StringFromKey("Bishop_236");
			link.l1.go = "DStep_6";
			GiveItem2Character(Pchar, "migraine_potion");
			Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
			Pchar.questTemp.CapBloodLine.iTime = -1;
		break;

		case "DStep_1":
			dialog.text = StringFromKey("Bishop_237");
			link.l1 = StringFromKey("Bishop_238");
			link.l1.go = "DStep_6";
			ChangeCharacterReputation(PChar, 5);
			Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
			Pchar.questTemp.CapBloodLine.iTime = -1;
		break;

		case "DStep_2":
			dialog.text = StringFromKey("Bishop_239");
			link.l1 = StringFromKey("Bishop_240");
			link.l1.go = "DStep_9";
			Pchar.questTemp.CapBloodLine.sLocator = "houseSp1";
			Pchar.questTemp.CapBloodLine.iTime = -1;

			if (Pchar.questTemp.CapBloodLine.stat != "CureMisStid_Complite")
			{
				QuestPointerToLoc("Bridgetown_town", "reload", "HouseSP1");
				QuestPointerToLoc("CommonPirateHouse", "item", "item1");
			}
		break;

		case "DStep_3":
			dialog.text = StringFromKey("Bishop_241");
			link.l1 = StringFromKey("Bishop_242");
			link.l1.go = "DStep_4";
		break;

		case "DStep_4":
			dialog.text = StringFromKey("Bishop_243");
			link.l1 = StringFromKey("Bishop_244");
			link.l1.go = "Exit";
			GiveItem2Character(Pchar, "migraine_potion");
			NextDiag.TempNode = "DStep_5";
			AddQuestRecord("WeaponsForEscape", "13");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "DStep_5":
			dialog.text = StringFromKey("Bishop_245");
			link.l1 = StringFromKey("Bishop_246");
			link.l1.go = "Exit";
			NextDiag.TempNode = "DStep_5";
		break;

		case "DStep_6":
			dialog.text = StringFromKey("Bishop_247");
			link.l1 = StringFromKey("Bishop_248");
			link.l1.go = "DStep_7";
		break;

		case "DStep_7":
			dialog.text = StringFromKey("Bishop_249");
			link.l1 = StringFromKey("Bishop_250");
			link.l1.go = "DStep_8";
			TakeNItemsNotification(pchar, "recipe_migraine_potion", 1, "default", "", "noSound");
		break;

		case "DStep_8":
			dialog.text = StringFromKey("Bishop_251");
			link.l1 = StringFromKey("Bishop_252");
			link.l1.go = "Exit_Away";
			TakeNItemsNotification(pchar, "lamp", 1, "default", "", "noSound");
			TakeNItemsNotification(pchar, "mortar_and_pestle", 1, "default", "", "noSound");
			AddDialogExitQuestFunction("Tutorial_BloodPrologue_Alchemy_Delay");

			QuestPointerToLoc("Bridgetown_Town", "reload", "reload3_back");
			QuestPointerToLoc("Bridgetown_Townhall", "reload", "reload3");
			QuestPointerToLoc("Bridgetown_TownhallRoom", "reload", "reload2");
		break;

		case "DStep_9":
			dialog.text = StringFromKey("Bishop_253");
			link.l1 = StringFromKey("Bishop_254");
			link.l1.go = "DStep_6";
		break;
		//<------ Мистер Дэн

		//--> Джереми Питт

		case "PStep_0":
			dialog.text = StringFromKey("Bishop_255");
			link.l1 = StringFromKey("Bishop_256");
			link.l1.go = "PStep_1";
		break;

		case "PStep_1":
			dialog.text = StringFromKey("Bishop_257");
			link.l1 = StringFromKey("Bishop_258");
			link.l1.go = "PStep_2";  //(+ небольшой % лидерства)
			link.l2 = StringFromKey("Bishop_259");
			link.l2.go = "PStep_3";
		break;

		case "PStep_2":
			dialog.text = StringFromKey("Bishop_260");
			link.l1 = StringFromKey("Bishop_261");
			link.l1.go = "Exit";
			AddCharacterExpToSkill(pchar, "LeaderShip", 50);
			NextDiag.TempNode = "PStep_4";
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape";
			Pchar.questTemp.CapBloodLine.statcrew = "find";
			Pchar.questTemp.CapBloodLine.Officer = 0;
			AddQuestRecord("CapBloodLine_q2", "5");
			AddQuestRecord("WeaponsForEscape", "1");
			AddLandQuestmark_Main_WithCondition(npchar, "CapBloodLine", "CapBloodLine_ReadyToEscape_Pitt_QuestMarkCondition");
			QuestPointerDelLoc("Bridgetown_town", "reload", "gate1_back");
			QuestPointerDelLoc("Bridgetown_Tavern_Upstairs", "reload", "reload1_back");
			QuestPointerDelLoc("Bridgetown_Tavern", "reload", "reload1_back");
			AddDialogExitQuestFunction("CapBloodLine_q2_PrepareToEscape_AddQuestMarks");
		break;

		case "PStep_3":
			dialog.text = StringFromKey("Bishop_262");
			link.l1 = StringFromKey("Bishop_263");
			link.l1.go = "Exit";
			NextDiag.TempNode = "PStep_4";
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape";
			Pchar.questTemp.CapBloodLine.statcrew = "find";
			AddQuestRecord("CapBloodLine_q2", "5");
			AddQuestRecord("WeaponsForEscape", "1");
			AddLandQuestmark_Main_WithCondition(npchar, "CapBloodLine", "CapBloodLine_ReadyToEscape_Pitt_QuestMarkCondition");
			QuestPointerDelLoc("Bridgetown_town", "reload", "gate1_back");
			QuestPointerDelLoc("Bridgetown_Tavern_Upstairs", "reload", "reload1_back");
			QuestPointerDelLoc("Bridgetown_Tavern", "reload", "reload1_back");
			AddDialogExitQuestFunction("CapBloodLine_q2_PrepareToEscape_AddQuestMarks");
		break;

		case "PStep_4":
			if (CheckAttribute(Pchar, "questTemp.CapBloodLine.Officer") && Pchar.questTemp.CapBloodLine.Officer == 4 && Pchar.questTemp.CapBloodLine.stat == "ReadyToEscape")
			{
				dialog.text = StringFromKey("Bishop_264");
				link.l1 = StringFromKey("Bishop_265");
				link.l1.go = "PStep_9";
				RemoveLandQuestmark_Main(npchar, "CapBloodLine");
				while (GetCharacterItem(pchar, "Weapon_for_escape") > 0)//homo fix 06/02/08 отбираем все квестовое оружие
				{
					TakeItemFromCharacter(Pchar, "Weapon_for_escape");
				}
				AddCharacterExpToSkill(PChar, SKILL_SNEAK, 20);
				AddCharacterExpToSkill(PChar, SKILL_FORTUNE, 50);
				//link.l10 = "Продолжить игру.";
				//link.l10.go = "finish";
				NextDiag.TempNode = "PStep_10";
				break;
			}
			dialog.text = StringFromKey("Bishop_266");
			link.l1 = StringFromKey("Bishop_267");
			link.l1.go = "Exit";
			NextDiag.TempNode = "PStep_4";
		break;

		case "PStep_5":
			dialog.text = StringFromKey("Bishop_268");
			link.l1 = StringFromKey("Bishop_269");
			link.l1.go = "PStep_6";
		//NextDiag.TempNode = "SStep_4";
		break;

		case "PStep_6":
			dialog.text = StringFromKey("Bishop_270");
			link.l1 = StringFromKey("Bishop_271");
			link.l1.go = "Exit_RunAway";
			//кладем ключ на стол
			sld = ItemsFromID("key3");
			sld.shown = true;
			sld.startLocation = "Estate";
			sld.startLocator = "item1";
			QuestPointerToLoc("Estate", "item", "item1");

			Pchar.questTemp.CapBloodLine.sLocator = "reload2";
			Pchar.questTemp.CapBloodLine.iTime = 5;
			AddDialogExitQuestFunction("DragunInvansion2");
		break;

		case "PStep_7":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			dialog.text = StringFromKey("Bishop_272");
			link.l1 = StringFromKey("Bishop_273");
			link.l1.go = "PStep_8";
		break;

		case "PStep_8":
			dialog.text = StringFromKey("Bishop_274");
			link.l1 = StringFromKey("Bishop_275");
			link.l1.go = "Exit_Away";
			Pchar.questTemp.CapBloodLine.sLocator = "reload1";
			Pchar.questTemp.CapBloodLine.iTime = -1;
			NextDiag.TempNode = "First time";
			chrDisableReloadToLocation = false;

			SetFunctionLocationCondition("CapBloodLine_BishopOnHouse", "Bridgetown_Plantation_Sp1", false);
			QuestPointerToLoc("Bridgetown_Plantation", "reload", "HouseSp1");
			QuestPointerToLoc("Bridgetown_Plantation_G6", "reload", "reload1");
			LocatorReloadEnterDisable("Bridgetown_Plantation", "reload1_back", true);
		break;

		case "PStep_9":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			CapBloodLine_q2_Complited();
		break;

		case "PStep_10":
			dialog.text = StringFromKey("Bishop_276");
			link.l1 = StringFromKey("Bishop_277");
			link.l1.go = "Exit";
			NextDiag.TempNode = "PStep_10";
		break;

		case "PStep_11":
			dialog.text = StringFromKey("Bishop_278");
			link.l1 = StringFromKey("Bishop_279");
			link.l1.go = "PStep_12";
		break;

		case "PStep_12":
			dialog.text = StringFromKey("Bishop_280");
			link.l1 = StringFromKey("Bishop_281");
			link.l1.go = "PStep_13";
		break;

		case "PStep_13":
			dialog.text = StringFromKey("Bishop_282");
			link.l1 = StringFromKey("Bishop_283");
			link.l1.go = "PStep_14";
		break;

		case "PStep_14":
			dialog.text = StringFromKey("Bishop_284");
			link.l1 = StringFromKey("Bishop_285");
			link.l1.go = "Exit";
			NextDiag.TempNode = "PStep_15";
			chrDisableReloadToLocation = false;
			LAi_group_SetHearRadius("TmpEnemy", LAI_GROUP_GRD_HEAR - 3);
			LAi_group_SetSayRadius("TmpEnemy", LAI_GROUP_GRD_SAY - 1);
			LAi_group_SetLookRadius("TmpEnemy", LAI_GROUP_GRD_LOOK - 1);
			AddQuestRecord("EscapeFormBarbados", "2");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerToLoc("BridgeTown_Plantation", "reload", "reload1_back");
		break;

		case "PStep_15":
			dialog.text = StringFromKey("Bishop_286");
			link.l1 = StringFromKey("Bishop_287");
			link.l1.go = "Exit";
			NextDiag.TempNode = "PStep_15";
		break;

		case "PStep_16":
			dialog.text = StringFromKey("Bishop_288");
			link.l1 = StringFromKey("Bishop_289");
			link.l1.go = "PStep_17";
		break;

		case "PStep_17":
			dialog.text = StringFromKey("Bishop_290");
			link.l1 = StringFromKey("Bishop_291");
			link.l1.go = "PStep_18";
		break;

		case "PStep_18":
			dialog.text = StringFromKey("Bishop_292");
			link.l1 = StringFromKey("Bishop_293");
			link.l1.go = "PStep_19";
		break;

		case "PStep_19":
			dialog.text = StringFromKey("Bishop_294");
			link.l1 = "";
			link.l1.go = "Exit_RunAway";
			Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
			Pchar.questTemp.CapBloodLine.iTime = 3;

			chrDisableReloadToLocation = false;
			NPChar.Money = 0;
			NPChar.Payment = true;
			NPChar.DontClearDead = true;

			AddPassenger(pchar, NPChar, false);

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

			n = FindLocation("Bridgetown_town");

			locations[n].reload.ship1.name = "reloadShip";
			locations[n].reload.ship1.go = "Barbados";
			locations[n].reload.ship1.emerge = "reload_1";
			locations[n].reload.ship1.autoreload = "0";
			locations[n].reload.ship1.label = "Sea";

			Pchar.location.from_sea = "Bridgetown_town";
			setWDMPointXZ("Bridgetown_town");

			string sQuest = "CapBloodLaspEpisode";
			pchar.quest.(sQuest).win_condition.l1 = "EnterToSea";
			pchar.quest.(sQuest).function = "CapBloodLaspEpisode";

			AddDialogExitQuestFunction("SpaCrewAtack");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "Pitt_lay":
			dialog.text = StringFromKey("Bishop_817");
			link.l1 = StringFromKey("Bishop_818");
			link.l1.go = "Pitt_lay_1";
		break;

		case "Pitt_lay_1":
			DialogExit();
			locCameraFromToPos(21.22, 2.90, 105.78, true, 75.05, -28.55, 195.9);
			LAi_SetActorType(pchar);
			LAi_ActorAnimation(pchar, "Barman_idle", "CapBloodLine_NeedToSavePitt_8", 5);
		break;

		case "Pitt_lay_2":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_819");
			link.l1.go = "Pitt_lay_3";
		break;

		case "Pitt_lay_3":
			dialog.text = StringFromKey("Bishop_820");
			link.l1 = StringFromKey("Bishop_821");
			link.l1.go = "Pitt_lay_4";
		break;

		case "Pitt_lay_4":
			dialog.text = StringFromKey("Bishop_822");
			link.l1 = StringFromKey("Bishop_823");
			link.l1.go = "Pitt_lay_5";
		break;

		case "Pitt_lay_5":
			dialog.text = StringFromKey("Bishop_824");
			link.l1 = "...";
			link.l1.go = "Pitt_lay_5_1";
		break;

		case "Pitt_lay_5_1":
			DialogExit();
			locCameraFromToPos(21.22, 2.90, 105.78, true, 75.05, -28.55, 195.9);
			LAi_FadeEx(0.5, 0.1, 0.5, "", "CapBloodLine_NeedToSavePitt_9", "");
		break;

		case "Pitt_lay_6":
			dialog.text = StringFromKey("Bishop_825");
			link.l1 = StringFromKey("Bishop_826");
			link.l1.go = "Pitt_lay_7";
		break;

		case "Pitt_lay_7":
			DialogExit();
			LAi_SetStayType(pchar);
			CharacterTurnAy(pchar, -1.5);
			locCameraFromToPos(20.22, 3.03, 109.78, true, 75.05, -13.55, 86.9);
		break;

		case "Pitt_In_Shack":
			dialog.text = StringFromKey("Bishop_827");
			link.l1 = StringFromKey("Bishop_828");
			link.l1.go = "exit";
			NextDiag.TempNode = "Pitt_In_Shack";
		break;

		//-->оружейние Гриффин

		case "GRStep_0":
			dialog.text = StringFromKey("Bishop_295");
			link.l1 = StringFromKey("Bishop_296");
			link.l1.go = "GRStep_1";
		break;

		case "GRStep_1":
			dialog.text = StringFromKey("Bishop_297");
			link.l1 = StringFromKey("Bishop_298");
			link.l1.go = "GRStep_2";
			link.l2 = StringFromKey("Bishop_299");
			link.l2.go = "GRStep_3";
		break;

		case "GRStep_2":
			AddQuestRecord("WeaponsForEscape", "4");
			dialog.text = StringFromKey("Bishop_300");
			link.l1.go = "Exit";
			pchar.quest.PrepareToEscape2.win_condition.l1 = "location";
			pchar.quest.PrepareToEscape2.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.PrepareToEscape2.function = "LoginSpain_spy";
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2";
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			RemoveLandQuestmark_Main(CharacterFromID("Bridgetown_tavernkeeper"), "CapBloodLine");
			RemoveLandQuestmark_Main(CharacterFromID("Quest_Smuggler"), "CapBloodLine");
		break;

		case "GRStep_3":
			dialog.text = StringFromKey("Bishop_301");
			link.l1 = StringFromKey("Bishop_302");
			link.l1.go = "GRStep_4";
			link.l2 = StringFromKey("Bishop_303");
			link.l2.go = "GRStep_2";
			NextDiag.TempNode = "GRStep_2";
		break;

		case "GRStep_4":
			dialog.text = StringFromKey("Bishop_304");
			link.l1 = StringFromKey("Bishop_305");
			link.l1.go = "GRStep_5";
		break;

		case "GRStep_5":
			dialog.text = StringFromKey("Bishop_306");
			link.l1 = StringFromKey("Bishop_307");
			link.l1.go = "GRStep_6";
		break;

		case "GRStep_6":
			dialog.text = StringFromKey("Bishop_308");
			link.l1 = StringFromKey("Bishop_309");
			link.l1.go = "GRStep_7_1";
			// Вариант торга доступен только при Charisma >= 4
			//			if (GetCharacterSPECIAL(pchar, SPECIAL_C) >= 4)
			if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 4))
			{
				link.l2 = StringFromKey("Bishop_310");
				link.l2.go = "GRStep_7_2";
			}

			sld = GetCharacter(NPC_GenerateCharacter("Spain_spy", "officer_27", "man", "man", 7, ENGLAND, -1, false));
			sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
			sld.name = "";
			sld.lastname = FindPersonalName("Spain_spy2_lastname");
			GiveItem2Character(sld, "Griffins_Weapon");
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true;
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorSetLayMode(sld);
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Bridgetown_Hut1", "goto", "goto2"); //к рыбаку отправлен

			sld = &characters[GetCharacterIndex("Hells")];
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
			QuestPointerToLoc("Bridgetown_town", "reload", "reload11_back"); //метку обновил
		break;

		case "GRStep_7_1":
			dialog.text = StringFromKey("Bishop_311");
			link.l1 = StringFromKey("Bishop_312");
			link.l1.go = "Exit";
			Pchar.questTemp.CapBloodLine.iMoney = 1500;
			NextDiag.TempNode = "GRStep_8";
			AddCharacterExpToSkill(pchar, "Commerce", 35); //торгуемся все же
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_1";
			AddQuestRecord("WeaponsForEscape", "3");
			AddQuestUserData("WeaponsForEscape", "iMoney", FindMoneyString(1500));
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			RemoveLandQuestmark_Main(CharacterFromID("Bridgetown_tavernkeeper"), "CapBloodLine");
			RemoveLandQuestmark_Main(CharacterFromID("Quest_Smuggler"), "CapBloodLine");
		break;

		case "GRStep_7_2":
			dialog.text = StringFromKey("Bishop_313");
			link.l1 = StringFromKey("Bishop_314");
			link.l1.go = "Exit";
			Pchar.questTemp.CapBloodLine.iMoney = 1000;
			NextDiag.TempNode = "GRStep_8";
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_1";
			AddQuestRecord("WeaponsForEscape", "3");
			AddQuestUserData("WeaponsForEscape", "iMoney", 1000);
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			RemoveLandQuestmark_Main(CharacterFromID("Bridgetown_tavernkeeper"), "CapBloodLine");
			RemoveLandQuestmark_Main(CharacterFromID("Quest_Smuggler"), "CapBloodLine");
		break;

		case "GRStep_8":
			dialog.text = StringFromKey("Bishop_315");
			if (GetCharacterItem(pchar, "Griffins_Weapon") > 0)
			{
				link.l1 = StringFromKey("Bishop_316");
				link.l1.go = "GRStep_9";
				TakeItemFromCharacter(Pchar, "Griffins_Weapon");
			}
			else
			{
				link.l1 = StringFromKey("Bishop_317");
				link.l1.go = "Exit";
				NextDiag.TempNode = "GRStep_8";
			}
		break;

		case "GRStep_9":
			dialog.text = StringFromKey("Bishop_318");
			if (makeint(pchar.money) >= sti(Pchar.questTemp.CapBloodLine.iMoney))
			{
				link.l1 = StringFromKey("Bishop_319");
				link.l1.go = "Exit";
				AddMoneyToCharacter(pchar, (-sti(Pchar.questTemp.CapBloodLine.iMoney)));
				Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_3";
				NextDiag.TempNode = "GRStep_12";
				RemoveLandQuestmark_Main(npchar, "CapBloodLine");
				AddLandQuestmark_Main_WithCondition(npchar, "CapBloodLine", "CapBloodLine_WaitWeapons_Griffin_QuestMarkCondition");
				AddDialogExitQuestFunction("CapBloodLine_GriffinWeapon_SkipTime");
			}
			else
			{
				link.l1 = StringFromKey("Bishop_320");
				link.l1.go = "Exit";
				NextDiag.TempNode = "GRStep_13";
				RemoveLandQuestmark_Main(npchar, "CapBloodLine");
				AddLandQuestmark_Main_WithCondition(npchar, "CapBloodLine", "CapBloodLine_WaitMoney_Griffin_QuestMarkCondition");
			}
			//Pchar.questTemp.CapBloodLine.GriffinTime = GetHour();
			SaveCurrentQuestDateParam("questTemp.CapBloodLine.GriffinTime");
			AddQuestRecord("WeaponsForEscape", "6");
		break;

		case "GRStep_10":
			dialog.text = StringFromKey("Bishop_321");
			link.l1 = StringFromKey("Bishop_322");
			link.l1.go = "GRStep_11";
		break;

		case "GRStep_11":
			dialog.text = StringFromKey("Bishop_323");
			link.l1 = "";
			link.l1.go = "Exit";
			pchar.quest.PrepareToEscape2.win_condition.l1 = "location";
			pchar.quest.PrepareToEscape2.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.PrepareToEscape2.function = "LoginSpain_spy";
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2";
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			RemoveLandQuestmark_Main(CharacterFromID("Bridgetown_tavernkeeper"), "CapBloodLine");
			RemoveLandQuestmark_Main(CharacterFromID("Quest_Smuggler"), "CapBloodLine");
		break;

		case "GRStep_12":
			if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape1_3" && GetQuestPastTimeParam("questTemp.CapBloodLine.GriffinTime") >= 1)
			{
				dialog.text = StringFromKey("Bishop_324");
				link.l1 = StringFromKey("Bishop_325");
				link.l1.go = "Exit";
				GiveItem2Character(Pchar, "Weapon_for_escape");
				NextDiag.TempNode = "First time";
				CloseQuestHeader("WeaponsForEscape");
				Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";
				RemoveLandQuestmark_Main(npchar, "CapBloodLine");
				RemoveLandQuestmarkToFantoms_Main("ItemTrader", "CapBloodLine");
				CapBloodLine_AddOfficerReady();
			}
			else
			{
				dialog.text = StringFromKey("Bishop_326");
				link.l1 = StringFromKey("Bishop_327");
				link.l1.go = "Exit";
				NextDiag.TempNode = "GRStep_12";

			}
		break;

		case "GRStep_13":
			dialog.text = StringFromKey("Bishop_328");
			if (makeint(pchar.money) >= sti(Pchar.questTemp.CapBloodLine.iMoney))
			{
				link.l1 = StringFromKey("Bishop_329");
				link.l1.go = "Exit";
				NextDiag.TempNode = "GRStep_12";
				AddMoneyToCharacter(pchar, (-sti(Pchar.questTemp.CapBloodLine.iMoney)));
				Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_3";
				AddDialogExitQuestFunction("CapBloodLine_GriffinWeapon_SkipTime");
			}
			else
			{
				link.l1 = StringFromKey("Bishop_330");
				link.l1.go = "Exit";
				NextDiag.TempNode = "GRStep_13";
			}
		break;

		case "GRStep_14":
			dialog.text = StringFromKey("Bishop_331");
			link.l1 = StringFromKey("Bishop_332");
			link.l1.go = "GRStep_15";
		break;

		case "GRStep_15":
			dialog.text = StringFromKey("Bishop_333");
			link.l1 = StringFromKey("Bishop_334");
			link.l1.go = "GRStep_16";
		break;

		case "GRStep_16":
			dialog.text = StringFromKey("Bishop_335");
			link.l1 = StringFromKey("Bishop_336");
			link.l1.go = "GRStep_17";
		break;

		case "GRStep_17":
			dialog.text = StringFromKey("Bishop_337");
			link.l1 = StringFromKey("Bishop_338");
			link.l1.go = "Exit";

			GiveItem2Character(Pchar, "Weapon_for_escape");
			AddQuestRecord("WeaponsForEscape", "9");
			CloseQuestHeader("WeaponsForEscape");
			Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";
			NextDiag.TempNode = "First time";
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			RemoveLandQuestmarkToFantoms_Main("ItemTrader", "CapBloodLine");
			CapBloodLine_AddOfficerReady();
		break;

		//-->рыбак Хелльс

		case "HStep_0":
			dialog.text = StringFromKey("Bishop_339");
			link.l1 = StringFromKey("Bishop_340");
			link.l1.go = "HStep_1";
		break;

		case "HStep_1":
			dialog.text = StringFromKey("Bishop_341");
			link.l1 = StringFromKey("Bishop_342");
			link.l1.go = "HStep_2";
		break;

		case "HStep_2":
			dialog.text = StringFromKey("Bishop_343");
			link.l1 = StringFromKey("Bishop_344");
			link.l1.go = "HStep_3";
		break;

		case "HStep_3":
			dialog.text = StringFromKey("Bishop_345");
			link.l1 = StringFromKey("Bishop_346");
			link.l1.go = "HStep_4";
			NextDiag.TempNode = "First time";
			AddQuestRecord("WeaponsForEscape", "5_1");
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1_2";
		break;

		case "HStep_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			sTemp = GetNationNameByType(ENGLAND) + "_citizens";
			LAi_group_MoveCharacter(NPChar, sTemp);
			LAi_SetOwnerTypeNoGroup(NPChar);
			DialogExit();
			Spain_spyDie("");
			AddLandQuestmark_Main(CharacterFromID("Griffin"), "CapBloodLine");

			chrDisableReloadToLocation = true;
			pchar.quest.CapBloodLine_Hells_GriffinWeaponTaken.win_condition.l1 = "item";
			pchar.quest.CapBloodLine_Hells_GriffinWeaponTaken.win_condition.l1.item = "Griffins_Weapon";
			pchar.quest.CapBloodLine_Hells_GriffinWeaponTaken.function = "CapBloodLine_Hells_GriffinWeaponTaken";

			DoQuestFunctionDelay("Tutorial_BloodPrologue_DeadSearch", 1.0);
		break;

		case "HStep_5":
			dialog.text = StringFromKey("Bishop_347");
			link.l1 = StringFromKey("Bishop_348");
			link.l1.go = "HStep_6";
		break;

		case "HStep_6":
			dialog.text = StringFromKey("Bishop_349");
			link.l1 = StringFromKey("Bishop_350");
			link.l1.go = "HStep_7";
			link.l2 = StringFromKey("Bishop_351");
			link.l2.go = "Exit";
			NextDiag.TempNode = "HStep_8";
		break;

		case "HStep_7":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			AddQuestRecord("FishermanQuest", "1");
			sld = &characters[GetCharacterIndex("Fisherman")];
			sld.dialog.currentnode = "FStep_1";
			AddLandQuestmark_Main(sld, "CapBloodLine");
			QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_FishermanQuest");

			NextDiag.TempNode = "HStep_9";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "HStep_8":
			dialog.text = StringFromKey("Bishop_352");
			link.l1 = StringFromKey("Bishop_353");
			link.l1.go = "HStep_7";
			link.l2 = StringFromKey("Bishop_354");
			link.l2.go = "Exit";
			NextDiag.TempNode = "HStep_8";
		break;

		case "HStep_9":
			dialog.text = StringFromKey("Bishop_355");
			if (CheckAttribute(Pchar, "questTemp.CapBloodLine.fishplace"))
			{
				link.l1 = StringFromKey("Bishop_356");
				link.l1.go = "HStep_10";
			}
			else
			{
				link.l1 = StringFromKey("Bishop_357");
				link.l1.go = "Exit";
				NextDiag.TempNode = "HStep_9";
			}
		break;

		case "HStep_10":
			dialog.text = StringFromKey("Bishop_358");
			link.l1 = StringFromKey("Bishop_359");//+Pchar.questTemp.CapBloodLine.fishplace;
			link.l1.go = "HStep_11";
		break;

		case "HStep_11":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload11_back");
			dialog.text = StringFromKey("Bishop_360");
			link.l1 = StringFromKey("Bishop_361");
			link.l1.go = "Exit";
			NextDiag.TempNode = "First time";
			AddMoneyToCharacter(pchar, 2000);
			CloseQuestHeader("FishermanQuest");
			LAi_SetAlcoholNormal(pchar);
			LAi_UpdateAlcoholCamShuttleCamera();
			if (CapBloodLine_CheckMoneyForNettl())
				QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "CapBloodLine_q2");

			sld = CharacterFromID("MoneySpy");
			if (sld.quest.meeting == 0)
				QuestPointerToLocEx("Bridgetown_town", "reload", "houseS1", "BloodLine_MoneySpy");
		break;

		//-->Испанский шпион

		case "SSStep_0":
			dialog.text = StringFromKey("Bishop_362");
			link.l1 = StringFromKey("Bishop_363");
			link.l1.go = "SSStep_1";
			link.l2 = StringFromKey("Bishop_364");
			link.l2.go = "SSStep_2";
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("BridgeTown_town", "houseSp2", true);
		break;

		case "SSStep_1":
			dialog.text = StringFromKey("Bishop_365");
			link.l1 = "";
			link.l1.go = "SS_Away";
			//            Pchar.questTemp.CapBloodLine.sLocator = "houseSp2";
			//            Pchar.questTemp.CapBloodLine.iTime = 20;
			AddQuestRecord("WeaponsForEscape", "7");
		break;

		case "SSStep_2":
			dialog.text = StringFromKey("Bishop_366");
			link.l1 = StringFromKey("Bishop_367");
			link.l1.go = "SS_Away";
			//            Pchar.questTemp.CapBloodLine.sLocator = "houseSp2";
			//            Pchar.questTemp.CapBloodLine.iTime = 20;
			AddQuestRecord("WeaponsForEscape", "7");
		break;

		case "SS_Away":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp2", "none", "", "", "SSOnHouse", 20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "SSStep_3":
			dialog.text = StringFromKey("Bishop_368");
			link.l1 = StringFromKey("Bishop_369");
			link.l1.go = "SSStep_4";
		break;

		case "SSStep_4":
			dialog.text = StringFromKey("Bishop_370");
			link.l1 = StringFromKey("Bishop_371");
			link.l1.go = "fight";
		break;

		//--> Контрабандист

		case "QSStep_0":
			dialog.text = StringFromKey("Bishop_372");
			link.l1 = StringFromKey("Bishop_373");
			link.l1.go = "QSStep_1";
		break;

		case "QSStep_1":
			dialog.text = StringFromKey("Bishop_374");
			link.l1 = StringFromKey("Bishop_375");
			link.l1.go = "QSStep_2";
		break;

		case "QSStep_2":
			dialog.text = StringFromKey("Bishop_376");
			link.l1 = StringFromKey("Bishop_377");
			link.l1.go = "QSStep_3";
		break;

		case "QSStep_3":
			dialog.text = StringFromKey("Bishop_378");
			link.l1 = StringFromKey("Bishop_379");
			link.l1.go = "QSStep_4";
		break;

		case "QSStep_4":
			dialog.text = StringFromKey("Bishop_380");
			link.l1 = StringFromKey("Bishop_381");
			link.l1.go = "QSStep_5";
		break;

		case "QSStep_5":
			dialog.text = StringFromKey("Bishop_382");
			link.l1 = StringFromKey("Bishop_383");
			link.l1.go = "Exit";
			NextDiag.TempNode = "QSStep_6";

			sld = &characters[GetCharacterbyLocation("Bridgetown_town", "soldiers", "soldier2")];
			sld.dialog.filename = "Quest\CapBloodLine\Bishop.c";
			sld.Dialog.CurrentNode = "GStep_1";
			sld.protector = true;
			sld.protector.CheckAlways = 1;
			LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", true);
			LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", true);
			LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", true);

			sld = characterFromID("MisStid");
			sld.Dialog.CurrentNode = "MSStep_3";
			LAi_CharacterEnableDialog(sld);
			sld.talker = 10;
			ChangeCharacterAddressGroup(sld, "Bridgetown_TownhallRoom", "barmen", "bar1");
			AddLandQuestmark_Main(sld, "CapBloodLine");

			sld = characterFromID("Den");
			LAi_SetCitizenTypeNoGroup(sld);
			//LAi_SetStayTypeNoGroup(sld);
			LAi_SetOwnerTypeNoGroup(sld);
			sld.Dialog.CurrentNode = "DStep_3";
			ChangeCharacterAddressGroup(sld, "CommonPirateHouse", "goto", "goto6");
			AddLandQuestmark_Main(sld, "CapBloodLine");

			sld = ItemsFromID("MsStid_ring");
			sld.shown = true;
			sld.startLocation = "Bridgetown_TownhallRoom";
			sld.startLocator = "item1";

			pchar.quest.PrepareToEscape3.win_condition.l1 = "location";
			pchar.quest.PrepareToEscape3.win_condition.l1.location = "Bridgetown_TownhallRoom";
			pchar.quest.PrepareToEscape3.function = "FindMsStid_ring";
			AddQuestRecord("WeaponsForEscape", "11");
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape3";

			AddLandQuestmark_Main_WithCondition(npchar, "CapBloodLine", "CapBloodLine_StidRing_QuestSmuggler_QuestMarkCondition");
			RemoveLandQuestmark_Main(CharacterFromID("Bridgetown_tavernkeeper"), "CapBloodLine");
			RemoveLandQuestmark_Main(CharacterFromID("Griffin"), "CapBloodLine");
			QuestPointerDelLoc("Bridgetown_town", "reload", "HouseSp2");
			QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_WeaponsForEscape");
		break;

		case "QSStep_6":
			if (GetCharacterItem(pchar, "MsStid_ring") > 0)
			{
				dialog.text = StringFromKey("Bishop_384");
				link.l1 = StringFromKey("Bishop_385");
				link.l1.go = "QSStep_7";
				link.l2 = StringFromKey("Bishop_386");
				link.l2.go = "QSStep_12";
			}
			else
			{
				dialog.text = StringFromKey("Bishop_387");
				link.l1 = StringFromKey("Bishop_388");
				link.l1.go = "Exit";
				NextDiag.TempNode = "QSStep_6";
			}
		break;

		case "QSStep_7":
			dialog.text = StringFromKey("Bishop_389");
			link.l1 = StringFromKey("Bishop_390");
			link.l1.go = "QSStep_8";
		break;

		case "QSStep_8":
			dialog.text = StringFromKey("Bishop_391");
			link.l1 = StringFromKey("Bishop_392");
			link.l1.go = "QSStep_10";
		break;

		case "QSStep_10":
			dialog.text = StringFromKey("Bishop_393");
			link.l1 = StringFromKey("Bishop_394");
			link.l1.go = "QSStep_11";
			TakeItemFromCharacter(Pchar, "MsStid_ring");
		break;

		case "QSStep_11":
			dialog.text = StringFromKey("Bishop_395");
			link.l1 = StringFromKey("Bishop_396");
			link.l1.go = "Exit";
			NextDiag.TempNode = "First time";
			GiveItem2Character(Pchar, "Weapon_for_escape");
			NextDiag.TempNode = "First time";
			CloseQuestHeader("WeaponsForEscape");
			AddMoneyToCharacter(pchar, 3000);
			AddQuestRecord("WeaponsForEscape", "16");
			CloseQuestHeader("WeaponsForEscape");
			Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			RemoveLandQuestmarkToFantoms_Main("ItemTrader", "CapBloodLine");
			CapBloodLine_AddOfficerReady();
		break;

		case "QSStep_12":
			dialog.text = StringFromKey("Bishop_397");
			link.l1 = StringFromKey("Bishop_398");
			link.l1.go = "Exit";
			NextDiag.TempNode = "First time";
			GiveItem2Character(Pchar, "Weapon_for_escape");
			NextDiag.TempNode = "First time";
			CloseQuestHeader("WeaponsForEscape");
			AddMoneyToCharacter(pchar, 3000);
			TakeItemFromCharacter(Pchar, "MsStid_ring");
			AddQuestRecord("WeaponsForEscape", "16");
			CloseQuestHeader("WeaponsForEscape");
			Pchar.questTemp.CapBloodLine.stat = "ReadyToEscape";
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			RemoveLandQuestmarkToFantoms_Main("ItemTrader", "CapBloodLine");
			CapBloodLine_AddOfficerReady();
		break;

		//--> Волверстон

		case "VLStep_0":
			dialog.text = StringFromKey("Bishop_399");
			link.l1 = StringFromKey("Bishop_400");
			link.l1.go = "Exit";
			NextDiag.TempNode = "VLStep_1";
			//Pchar.questTemp.CapBloodLine.Volverston = true;
			Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer) + 1;
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			SetCurrentQuestMark(characterFromId("Pitt"));
			CapBloodLine_AddOfficerReady();
		break;

		case "VLStep_1":
			dialog.text = StringFromKey("Bishop_401");
			link.l1 = StringFromKey("Bishop_402");
			link.l1.go = "Exit";
			NextDiag.TempNode = "VLStep_1";
		break;

		case "VLStep_10":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			dialog.text = StringFromKey("Bishop_420");
			link.l1 = StringFromKey("Bishop_421");
			link.l1.go = "Exit";
			AddDialogExitQuestFunction("CapBloodOfficers");
			// AddQuestRecord("EscapeFormBarbados", "4");
			// NextDiag.TempNode = "VLStep_10b";
		break;

		case "VLStep_10b":
			dialog.text = StringFromKey("Bishop_422");
			link.l1 = StringFromKey("Bishop_423");
			link.l1.go = "Exit";
			NextDiag.TempNode = "VLStep_10b";
			// AddDialogExitQuestFunction("CapBloodOfficers");
		break;

		case "VLStep_11":
			dialog.text = StringFromKey("Bishop_424");
			link.l1 = StringFromKey("Bishop_425");
			link.l1.go = "VLStep_12";
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "VLStep_12":
			dialog.text = StringFromKey("Bishop_426");
			link.l1 = StringFromKey("Bishop_427");
			link.l1.go = "VLStep_12_1";
		break;

		case "VLStep_12_1":
			DialogExit();
			npchar.dialog.currentnode = "VLStep_12_2";
			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, npchar, "", -1, 0);
		break;

		case "VLStep_12_2":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_868");
			link.l1.go = "VLStep_13";
		break;

		case "VLStep_13":
			dialog.text = StringFromKey("Bishop_428");
			link.l1 = StringFromKey("Bishop_429");
			link.l1.go = "VLStep_Exit";
		break;

		case "VLStep_Exit":
			DialogExit();
			DeleteAttribute(npchar, "SavedTeleportPos");
			LAi_SetActorType(npchar);
			LAi_SetPlayerType(pchar);
			LAi_ActorMoveToPoint(npchar, false, 23.01, 2.71, 98.88, "CapBloodLine_VolvTurn", -1.0);

			NPChar.Money = 0;
			NPChar.Payment = true;
			NPChar.DontClearDead = true;

			AddPassenger(pchar, NPChar, false);
			AddDialogExitQuestFunction("CapBloodLine_TalkOnDeck");
			CapBloodLine_OfficersCount();
			// AddDialogExitQuestFunction("VolverstonAdd");
		break;

		case "VLStep_Return":
			dialog.text = StringFromKey("Bishop_922");
			link.l1 = StringFromKey("Bishop_923");
			link.l1.go = "Exit";
			NextDiag.TempNode = "VLStep_Return";
		break;

		case "VolverstonNearPitt": // Возле Питта
			dialog.text = StringFromKey("Bishop_608");
			link.l1 = StringFromKey("Bishop_829");
			link.l1.go = "VolverstonNearPitt_1";
		break;

		case "VolverstonNearPitt_1":
			dialog.text = StringFromKey("Bishop_608");
			link.l1 = StringFromKey("Bishop_830");
			link.l1.go = "VolverstonNearPitt_2";
		break;

		case "VolverstonNearPitt_2":
			dialog.text = StringFromKey("Bishop_831");
			link.l1 = StringFromKey("Bishop_832");
			link.l1.go = "VolverstonNearPitt_3";
		break;

		case "VolverstonNearPitt_3":
			DialogExit();
			locCameraFromToPos(20.22, 3.03, 109.78, true, 75.05, -13.55, 86.9);
			DoQuestFunctionDelay("CapBloodLine_BladGoesToCity", 1.0);
			LocatorReloadEnterDisable("Bridgetown_Plantation", "reload1_back", true);
		break;

		case "VolverstonGiveWeapon": // у выхода из плантации
			dialog.text = StringFromKey("Bishop_833");
			link.l1 = StringFromKey("Bishop_834");
			link.l1.go = "VolverstonGiveWeapon_1";
		break;

		case "VolverstonGiveWeapon_1":
			dialog.text = StringFromKey("Bishop_835");
			link.l1 = StringFromKey("Bishop_836");
			link.l1.go = "VolverstonGiveWeapon_2";
		break;

		case "VolverstonGiveWeapon_2":
			dialog.text = StringFromKey("Bishop_837");
			link.l1 = StringFromKey("Bishop_838");
			link.l1.go = "VolverstonGiveWeapon_3";
			TakeNItemsNotification(pchar, "blade6", 1, "default", "", "noSound");
			TakeNItemsNotification(pchar, "potion2", 5, "default", "", "noSound");
		break;

		case "VolverstonGiveWeapon_3":
			DialogExit();
			AddQuestRecord("EscapeFormBarbados", "12");
			LAi_SetActorType(npchar);
			LAi_ActorGoTolocator(npchar, "quest", "detector3", "", -1);
			SetFunctionExitFromLocationCondition("CapBloodLine_BladGoesToCity_3", pchar.location, false);
			SetFunctionLocationCondition("StillShip", "Bridgetown_Town", false);
			SetFunctionLocatorCondition("CapBloodLine_CheckReadyToFight", "Bridgetown_Plantation", "reload", "reload1_back", true);
			LocatorReloadEnterDisable("Bridgetown_Plantation", "reload1_back", true);
			QuestPointerToLoc("Bridgetown_plantation", "reload", "reload1_back");
			pchar.questTemp.CapBloodLine.stat = "Mary";
			Pchar.questTemp.CapBloodLine.Escape = true;
			SetLocationCapturedState("Bridgetown_town", true);
			chrDisableReloadToLocation = false;
			SetShipInBridgetown();

			SetFunctionTimerCondition("CapBloodLine_FailTimer", 0, 0, 1, false);
		break;

		case "VolvInBarac":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			CapBloodLine_EsapeDialog();
			CharacterTurnByChr(npchar, pchar);
			DeleteQuestCondition("CapBloodLine_Esape");
			QuestPointerDelLoc("Bridgetown_Plantation", "quest", "detector3");

			dialog.text = StringFromKey("Bishop_839");
			link.l1 = StringFromKey("Bishop_840");
			link.l1.go = "VolvInBarac_1";
		break;

		case "VolvInBarac_1":
			dialog.text = StringFromKey("Bishop_841");
			link.l1 = StringFromKey("Bishop_842");
			link.l1.go = "VolvInBarac_2";
		break;

		case "VolvInBarac_2":
			dialog.text = StringFromKey("Bishop_843");
			link.l1 = StringFromKey("Bishop_844");
			link.l1.go = "VolvInBarac_3";
		break;

		case "VolvInBarac_3":
			dialog.text = StringFromKey("Bishop_845");
			link.l1 = StringFromKey("Bishop_846");
			link.l1.go = "VolvInBarac_4";
		break;

		case "VolvInBarac_4":
			dialog.text = StringFromKey("Bishop_847");
			link.l1 = StringFromKey("Bishop_608");
			link.l1.go = "VolvInBarac_5";
		break;

		case "VolvInBarac_5":
			StartInstantDialogNow("Slave_Quest", "VolvInBarac_6", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "VolvInBarac_6":
			CharacterTurnByChr(npchar, pchar);
			dialog.text = StringFromKey("Bishop_848");
			link.l1 = StringFromKey("Bishop_849");
			link.l1.go = "VolvInBarac_7";
		break;

		case "VolvInBarac_7":
			StartInstantDialogNow("Volverston", "VolvInBarac_8", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "VolvInBarac_8":
			dialog.text = "";
			link.l1 = StringFromKey("Bishop_850");
			link.l1.go = "VolvInBarac_9";
			CharacterTurnByChr(npchar, pchar);
		break;

		case "VolvInBarac_9":
			dialog.text = StringFromKey("Bishop_851");
			link.l1 = StringFromKey("Bishop_852");
			link.l1.go = "VolvInBarac_10";
		break;

		case "VolvInBarac_10":
			dialog.text = StringFromKey("Bishop_853");
			link.l1 = "";
			link.l1.go = "VolvInBarac_11";
		break;

		case "VolvInBarac_11":
			StartInstantDialogNow("Hugtorp", "HugtorpInBarac_12", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "HugtorpInBarac_12":
			CharacterTurnByChr(npchar, pchar);
			dialog.text = StringFromKey("Bishop_854");
			link.l1 = "";
			link.l1.go = "VolvInBarac_13";
		break;

		case "VolvInBarac_13":
			StartInstantDialogNow("Dieke", "DiekeInBarac_14", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "DiekeInBarac_14":
			CharacterTurnByChr(npchar, pchar);
			dialog.text = StringFromKey("Bishop_855");
			link.l1 = "";
			link.l1.go = "VolvInBarac_15";
		break;

		case "VolvInBarac_15":
			StartInstantDialogNow("Ogl", "OglInBarac_16", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "OglInBarac_16":
			CharacterTurnByChr(npchar, pchar);
			dialog.text = StringFromKey("Bishop_856");
			link.l1 = "";
			link.l1.go = "VolvInBarac_17";
		break;

		case "VolvInBarac_17":
			StartInstantDialogNow("Slave_Quest", "VolvInBarac_18", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "VolvInBarac_18":
			CharacterTurnByChr(CharacterFromID("Slave_Quest"), pchar);
			dialog.text = StringFromKey("Bishop_857");
			link.l1 = "";
			link.l1.go = "VolvInBarac_19";
		break;

		case "VolvInBarac_19":
			StartInstantDialogNow("Volverston", "VolvInBarac_20", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "VolvInBarac_20":
			CharacterTurnByChr(npchar, pchar);
			dialog.text = StringFromKey("Bishop_858");
			link.l1 = StringFromKey("Bishop_859");
			link.l1.go = "VolvInBarac_21";
		break;

		case "VolvInBarac_21":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.CBL.Shipyard");
			DeleteQuestCondition("CapBloodLine_FailTimer");
			DeleteQuestCondition("CapBloodLine_q2_Late");
			DeleteQuestCondition("CapBloodLine_BladGoesToCity_2");
			DeleteQuestCondition("CapBloodLine_BladGoesToCity_3");
			DeleteQuestCondition("CapBloodLine_InGuberRoomReturn");
			DeleteQuestCondition("CapBloodLine_ReturnCitizenDialogAgain");
			LocatorReloadEnterDisable("Bridgetown_Shipyard", "reload2", false);
			LocatorReloadEnterDisable("Bridgetown_Packhouse", "reload2", false);
			LAi_LocationFightDisable(&locations[FindLocation("Bridgetown_Plantation")], false);
			LAi_LocationFightDisable(&locations[FindLocation("Bridgetown_Packhouse")], false);
			LAi_LocationFightDisable(&locations[FindLocation("CommonBedroom")], false);

			loc = &locations[FindLocation("Bridgetown_town")];
			loc.models.day.charactersPatch = "Bridgetown_patchship_day";
			loc.models.night.charactersPatch = "Bridgetown_patchship_night";
			LAI_FadeEx(2.0, 1.0, 1.0, "", "CapBloodLine_Esape_2", "");
		break;

		case "VolcOnDeck":
			dialog.text = StringFromKey("Bishop_924");
			link.l1 = StringFromKey("Bishop_925");
			link.l1.go = "VolcOnDeck_1";
		break;

		case "VolcOnDeck_1":
			dialog.text = StringFromKey("Bishop_926");
			link.l1 = StringFromKey("Bishop_927");
			link.l1.go = "VolcOnDeck_2";
		break;

		case "VolcOnDeck_2":
			AddDialogExitQuestFunction("CapBloodLine_DiekeSeeBoat");
			DialogExit();
			DeleteAttribute(npchar, "GenQuest.CantRun");
			CharacterTurnByChr(pchar, npchar);
		break;

		case "Volverston_OfficerStub":
			dialog.text = StringFromKey("Bishop_928");
			link.l1 = StringFromKey("Bishop_929");
			link.l1.go = "exit";
			NextDiag.TempNode = "Volverston_OfficerNode";
		break;

		case "Volverston_OfficerNode":
			dialog.text = StringFromKey("Bishop_930");
			link.l1 = StringFromKey("Bishop_931");
			link.l1.go = "exit";
			NextDiag.TempNode = "Volverston_OfficerNode";
		break;
		// <--- Волверстон

		//--> Натаниэль Хагторп
		case "HTStep_0":
			dialog.text = StringFromKey("Bishop_430");
			link.l1 = StringFromKey("Bishop_431");
			link.l1.go = "HTStep_1";
		break;

		case "HTStep_1":
			dialog.text = StringFromKey("Bishop_432");
			link.l1 = StringFromKey("Bishop_433");
			link.l1.go = "HTStep_2";
		break;

		case "HTStep_2":
			dialog.text = StringFromKey("Bishop_434");
			link.l1 = StringFromKey("Bishop_435");
			link.l1.go = "HTStep_3";
		break;

		case "HTStep_3":
			dialog.text = StringFromKey("Bishop_436");
			link.l1 = StringFromKey("Bishop_437");
			link.l1.go = "HTStep_4";
		break;

		case "HTStep_4":
			dialog.text = StringFromKey("Bishop_438");
			link.l1 = StringFromKey("Bishop_439");
			link.l1.go = "HTStep_12";
			NextDiag.TempNode = "HTStep_9";
			link.l2 = StringFromKey("Bishop_440");
			link.l2.go = "HTStep_5";
		break;

		case "HTStep_5":
			dialog.text = StringFromKey("Bishop_441");
			link.l1 = StringFromKey("Bishop_442");
			link.l1.go = "HTStep_6";
		break;

		case "HTStep_6":
			dialog.text = StringFromKey("Bishop_443");
			link.l1 = StringFromKey("Bishop_444");
			link.l1.go = "HTStep_12";
			link.l2 = StringFromKey("Bishop_445");
			link.l2.go = "HTStep_7";
			NextDiag.TempNode = "HTStep_9";
		break;

		case "HTStep_7":
			dialog.text = StringFromKey("Bishop_446");
			//            if(GetCharacterSPECIAL(pchar, SPECIAL_C) >= 7)
			if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 7))
			{
				link.l0 = StringFromKey("Bishop_447");
				link.l0.go = "HTStep_8";
			}
			else
			{
				AddCharacterExpToSkill(pchar, "LeaderShip", 50);
			}
			link.l1 = StringFromKey("Bishop_448");
			link.l1.go = "HTStep_12";
		break;

		case "HTStep_8":
			dialog.text = StringFromKey("Bishop_449");
			link.l1 = StringFromKey("Bishop_450");
			link.l1.go = "Exit";
			AddCharacterExpToSkill(pchar, "LeaderShip", 150);
			NextDiag.TempNode = "HTStep_11";
			Pchar.questTemp.CapBloodLine.Hugtorp = true;
			Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer) + 1;
			AddQuestRecord("HugtorpTrouble", "2");
			CloseQuestHeader("HugtorpTrouble");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			SetCurrentQuestMark(characterFromId("Pitt"));
			CapBloodLine_AddOfficerReady();
		break;

		case "HTStep_9":
			dialog.text = StringFromKey("Bishop_451");
			if (GetCharacterItem(pchar, "HugtorpRing") > 0)
			{
				link.l1 = StringFromKey("Bishop_452");
				link.l1.go = "HTStep_10";
				TakeItemFromCharacter(Pchar, "HugtorpRing");
			}
			else
			{
				link.l1 = StringFromKey("Bishop_453");
				link.l1.go = "Exit";
				NextDiag.TempNode = "HTStep_9";
			}
		break;

		case "HTStep_10":
			dialog.text = StringFromKey("Bishop_454");
			link.l1 = StringFromKey("Bishop_455");
			link.l1.go = "Exit";
			NextDiag.TempNode = "HTStep_11";
			Pchar.questTemp.CapBloodLine.Hugtorp = true;
			Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer) + 1;
			AddQuestRecord("HugtorpTrouble", "5");
			CloseQuestHeader("HugtorpTrouble");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			SetCurrentQuestMark(characterFromId("Pitt"));
			CapBloodLine_AddOfficerReady();

			AddCharacterExpToSkill(PChar, SKILL_LEADERSHIP, 50);
		break;

		case "HTStep_11":
			dialog.text = StringFromKey("Bishop_456");
			link.l1 = StringFromKey("Bishop_457");
			link.l1.go = "Exit";
			NextDiag.TempNode = "HTStep_11";
		break;

		case "HTStep_12":
			LoginWinterwood();
			AddQuestRecord("HugtorpTrouble", "1");
			NextDiag.CurrentNode = "HTStep_9";
			DialogExit();
			AddLandQuestmark_Main_WithCondition(npchar, "CapBloodLine", "CapBloodLine_HugtorpTrouble_QuestMarkCondition");
		break;

		case "HTStep_13":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			dialog.text = StringFromKey("Bishop_458");
			link.l1 = StringFromKey("Bishop_459");
			link.l1.go = "HTStep_14";
		break;

		case "HTStep_14":
			dialog.text = StringFromKey("Bishop_460");
			link.l1 = StringFromKey("Bishop_461");
			link.l1.go = "Exit";

			NPChar.Money = 0;
			NPChar.Payment = true;
			NPChar.DontClearDead = true;

			AddPassenger(pchar, NPChar, false);
			NextDiag.TempNode = "Hugtorp_On_Deck";
			CapBloodLine_OfficersCount();
		break;

		case "Hugtorp_In_Shack":
			dialog.text = StringFromKey("Bishop_860");
			link.l1 = StringFromKey("Bishop_861");
			link.l1.go = "exit";
			NextDiag.TempNode = "Hugtorp_In_Shack";
		break;

		case "Hugtorp_On_Deck":
			dialog.text = StringFromKey("Bishop_873");
			link.l1 = StringFromKey("Bishop_874");
			link.l1.go = "exit";
			NextDiag.TempNode = "Hugtorp_On_Deck";
		break;

		case "Hugtorp_OfficerStub":
			dialog.text = StringFromKey("Bishop_932");
			link.l1 = StringFromKey("Bishop_933");
			link.l1.go = "exit";
			NextDiag.TempNode = "Hugtorp_OfficerStub";
		break;

		case "Hugtorp_OfficerNode":
			dialog.text = StringFromKey("Bishop_934");
			link.l1 = StringFromKey("Bishop_935");
			link.l1.go = "exit";
			NextDiag.TempNode = "Hugtorp_OfficerNode";
		break;

		// Заметил, что Диего мёртв
		case "Hugtorp_AboutDigo":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_936");
			link.l1.go = "Hugtorp_AboutDigo_0";
		break;

		case "Hugtorp_AboutDigo_0":
			dialog.text = StringFromKey("Bishop_937");
			link.l1 = "...";
			link.l1.go = "Hugtorp_AboutDigo_1";
		break;

		case "Hugtorp_AboutDigo_1":
			AddDialogExitQuestFunction("CapBloodLine_HugtorpSayDiegoDie");
			DialogExit();
		break;

		case "EstebanAfterEncarnacion_1":
			PlaySound("Voice\" + VoiceGetLanguage() + "\Gr_Ransack_2.wav");
			CharacterTurnByChr(npchar, CharacterFromID("Hugtorp"));
			CharacterTurnByChr(CharacterFromID("Hugtorp"), npchar);
			dialog.text = StringFromKey("Bishop_938");
			link.l1 = "...";
			link.l1.go = "EstebanAfterEncarnacion_ToHugtorp";
		break;

		case "EstebanAfterEncarnacion_ToHugtorp":
			StartInstantDialogNow("Hugtorp", "HugtorpAfterEncarnacion_1", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "HugtorpAfterEncarnacion_1":
			CharacterTurnByChr(npchar, CharacterFromID("Esteban_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Esteban_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_939");
			link.l1 = "...";
			link.l1.go = "HugtorpAfterEncarnacion_ToEsteban";
		break;

		case "HugtorpAfterEncarnacion_ToEsteban":
			StartInstantDialogNow("Esteban_Espinosa", "EstebanAfterEncarnacion_2", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "EstebanAfterEncarnacion_2":
			CharacterTurnByChr(npchar, CharacterFromID("Hugtorp"));
			CharacterTurnByChr(CharacterFromID("Hugtorp"), npchar);
			dialog.text = StringFromKey("Bishop_940");
			link.l1 = "...";
			link.l1.go = "EstebanAfterEncarnacion_ToHugtorp_2";
		break;

		case "EstebanAfterEncarnacion_ToHugtorp_2":
			StartInstantDialogNow("Hugtorp", "HugtorpAfterEncarnacion_2", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "HugtorpAfterEncarnacion_2":
			CharacterTurnByChr(npchar, CharacterFromID("Esteban_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Esteban_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_941");
			link.l1 = "...";
			link.l1.go = "HugtorpAfterEncarnacion_ToEstebanOutrage";
		break;

		case "HugtorpAfterEncarnacion_ToEstebanOutrage":
			StartInstantDialogNow("Esteban_Espinosa", "EstebanAfterEncarnacion_Outrage", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "EstebanAfterEncarnacion_Outrage":
			CharacterTurnByChr(npchar, CharacterFromID("Hugtorp"));
			CharacterTurnByChr(CharacterFromID("Hugtorp"), npchar);
			dialog.text = StringFromKey("Bishop_942");
			link.l1 = "...";
			link.l1.go = "EstebanAfterEncarnacion_ToHugtorpThreat";
		break;

		case "EstebanAfterEncarnacion_ToHugtorpThreat":
			StartInstantDialogNow("Hugtorp", "HugtorpAfterEncarnacion_Threat", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "HugtorpAfterEncarnacion_Threat":
			CharacterTurnByChr(npchar, CharacterFromID("Esteban_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Esteban_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_943");
			link.l1 = "...";
			link.l1.go = "HugtorpAfterEncarnacion_Threat_2";
		break;

		case "HugtorpAfterEncarnacion_Threat_2":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_944");
			link.l1.go = "HugtorpAfterEncarnacion_3";
		break;

		case "HugtorpAfterEncarnacion_3":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_945");
			link.l1 = StringFromKey("Bishop_946");
			link.l1.go = "HugtorpAfterEncarnacion_ToEsteban_2";
		break;

		case "HugtorpAfterEncarnacion_ToEsteban_2":
			StartInstantDialogNow("Esteban_Espinosa", "EstebanAfterEncarnacion_3", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "EstebanAfterEncarnacion_3":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_947");
			link.l1 = StringFromKey("Bishop_948");
			link.l1.go = "EstebanAfterEncarnacion_4";
		break;

		case "EstebanAfterEncarnacion_4":
			dialog.text = StringFromKey("Bishop_949");
			link.l1 = StringFromKey("Bishop_950");
			link.l1.go = "EstebanAfterEncarnacion_5";
		break;

		case "EstebanAfterEncarnacion_5":
			dialog.text = StringFromKey("Bishop_951");
			link.l1 = StringFromKey("Bishop_952");
			link.l1.go = "EstebanAfterEncarnacion_6";
		break;

		case "EstebanAfterEncarnacion_6":
			dialog.text = StringFromKey("Bishop_953");
			link.l1 = "...";
			link.l1.go = "EstebanAfterEncarnacion_7";
		break;

		case "EstebanAfterEncarnacion_7":
			StartInstantDialogNow("Hugtorp", "EstebanAfterEncarnacion_8", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "EstebanAfterEncarnacion_8":
			dialog.text = "...";
			if (sti(pchar.questTemp.CapBloodLine.DieGoGuardsAlive) > 0) link.l1 = StringFromKey("Bishop_954");
			else link.l1 = StringFromKey("Bishop_955");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CapBloodLine_HugtorpSayDiegoDie_2");
		break;

		// <--- Хагторп

		//--> Николас Дайк

		case "DKStep_0":
			dialog.text = StringFromKey("Bishop_462");
			link.l1 = StringFromKey("Bishop_463");
			link.l1.go = "DKStep_1";
		break;

		case "DKStep_1":
			dialog.text = StringFromKey("Bishop_464");
			link.l1 = StringFromKey("Bishop_465");
			link.l1.go = "exit";
			NextDiag.TempNode = "DKStep_2";
			SetFunctionLocationCondition("CapBloodLine_BishopInDiekeQuest", "Bridgetown_Plantation_Sp1", false);

			AddQuestRecord("DiekeQuest", "1");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");

			QuestPointerToLoc("Bridgetown_plantation", "reload", "houseSp1");
			LocatorReloadEnterDisable("Bridgetown_plantation", "houseSp1", false);
		break;

		case "DKStep_2":
			dialog.text = StringFromKey("Bishop_466");
			link.l1 = StringFromKey("Bishop_467");
			link.l1.go = "exit";
			NextDiag.TempNode = "DKStep_2";
		break;

		case "DKStep_3":
			dialog.text = StringFromKey("Bishop_468");
			link.l1 = StringFromKey("Bishop_469");
			link.l1.go = "exit";
			Pchar.questTemp.CapBloodLine.Dieke = true;
			Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer) + 1;
			NextDiag.TempNode = "DKStep_4";
			AddQuestRecord("DiekeQuest", "5");
			CloseQuestHeader("DiekeQuest");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			SetCurrentQuestMark(characterFromId("Pitt"));
			CapBloodLine_AddOfficerReady();

			AddCharacterExpToSkill(PChar, SKILL_LEADERSHIP, 50);
		break;

		case "DKStep_4":
			dialog.text = StringFromKey("Bishop_470");
			link.l1 = StringFromKey("Bishop_471");
			link.l1.go = "exit";
			NextDiag.TempNode = "DKStep_4";
		break;

		case "DKStep_5":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			dialog.text = StringFromKey("Bishop_472");
			link.l1 = StringFromKey("Bishop_473");
			link.l1.go = "DKStep_6";
		break;

		case "DKStep_6":
			dialog.text = StringFromKey("Bishop_474");
			link.l1 = StringFromKey("Bishop_475");
			link.l1.go = "Exit";

			NPChar.Money = 0;
			NPChar.Payment = true;
			NPChar.DontClearDead = true;

			AddPassenger(pchar, NPChar, false);
			NextDiag.TempNode = "Dieke_On_Deck";
			CapBloodLine_OfficersCount();
			// AddDialogExitQuestFunction("DiekeAdd");
		break;

		case "Dieke_In_Shack":
			dialog.text = StringFromKey("Bishop_862");
			link.l1 = StringFromKey("Bishop_863");
			link.l1.go = "exit";
			NextDiag.TempNode = "Dieke_In_Shack";
		break;

		case "Dieke_On_Deck":
			dialog.text = StringFromKey("Bishop_871");
			link.l1 = StringFromKey("Bishop_872");
			link.l1.go = "exit";
			NextDiag.TempNode = "Dieke_On_Deck";
		break;

		case "DiekeOnDeck_1":
			dialog.text = StringFromKey("Bishop_956");
			link.l1 = StringFromKey("Bishop_957");
			link.l1.go = "DiekeOnDeck_2";
		break;

		case "DiekeOnDeck_2":
			dialog.text = StringFromKey("Bishop_958");
			link.l1 = StringFromKey("Bishop_959");
			link.l1.go = "DiekeOnDeck_3";
		break;

		case "DiekeOnDeck_3":
			DialogExit();
			AddDialogExitQuestFunction("CapBloodLine_DiegoOnDeck");
			locCameraFromToPos(34.6, 6.09, 117.39, true, 25.32, 3.66, 114.02);
		break;

		case "DiekeOnDeck_4":
			dialog.text = StringFromKey("Bishop_960");
			link.l1 = StringFromKey("Bishop_961");
			link.l1.go = "DiekeOnDeck_5";
		break;

		case "DiekeOnDeck_5":
			dialog.text = StringFromKey("Bishop_962");
			link.l1 = StringFromKey("Bishop_963");
			link.l1.go = "DiekeOnDeck_6";
			link.l2 = StringFromKey("Bishop_964");
			link.l2.go = "DiekeOnDeck_7";
		break;

		case "DiekeOnDeck_6":
			dialog.text = StringFromKey("Bishop_965");
			link.l1 = StringFromKey("Bishop_966");
			link.l1.go = "DiekeOnDeck_StartSeaFightNow";
		break;

		case "DiekeOnDeck_7":
			dialog.text = StringFromKey("Bishop_967");
			link.l1 = StringFromKey("Bishop_968");
			link.l1.go = "DiekeOnDeck_StayOnDeck";
		break;

		case "DiekeOnDeck_StartSeaFightNow":
			DialogExit();
			LAi_SetPlayerType(pchar);
			DeleteAttribute(&TEV, "StopTimeScale");
			locCameraSleep(false);
			locCameraResetState();

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

			InterfaceStates.Buttons.Save.enable = true;
			DoQuestFunctionDelay("DiekeOnDeck_StartSeaFightNow_Exit", 1.0);
		break;

		case "DiekeOnDeck_StayOnDeck":
			AddDialogExitQuestFunction("CapBloodLine_SeaFightWait");
			DialogExit();
			locCameraSleep(false);
			locCameraResetState();
			InterfaceStates.Buttons.Save.enable = true;
		break;

		case "Dieke_OfficerStub":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_969");
			link.l1 = StringFromKey("Bishop_970");
			link.l1.go = "exit";
			NextDiag.TempNode = "Dieke_OfficerStub";
		break;

		case "DiekeOnShore":
			dialog.text = StringFromKey("Bishop_971");
			link.l1 = StringFromKey("Bishop_972");
			link.l1.go = "DiekeOnShore_1";
		break;

		case "DiekeOnShore_1":
			dialog.text = StringFromKey("Bishop_973");
			link.l1 = StringFromKey("Bishop_974");
			link.l1.go = "DiekeOnShore_2";
			link.l2 = StringFromKey("Bishop_975");
			link.l2.go = "exit";
			NextDiag.TempNode = "Dieke_OfficerNode";
			AddDialogExitQuestFunction("CapBloodLine_DiegoLie");
		break;

		case "DiekeOnShore_2":
			dialog.text = StringFromKey("Bishop_976");
			link.l1 = StringFromKey("Bishop_977");
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;

		case "Dieke_OfficerNode":
			dialog.text = StringFromKey("Bishop_978");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dieke_OfficerNode";
		break;

		case "Dieke_GiveGold":
			dialog.text = StringFromKey("Bishop_979");
			link.l1 = StringFromKey("Bishop_980");
			link.l1.go = "exit";
			NextDiag.TempNode = "Dieke_OfficerNode";
			TakeNItemsNotification(pchar, "chest", 4, "default", "", "");
			AddDialogExitQuestFunction("CapBloodLine_SonsTrable_8");
		break;
		// <--- Дайк

		//--> Нед Огл

		case "OGLStep_0":
			dialog.text = StringFromKey("Bishop_476");
			link.l1 = StringFromKey("Bishop_477");
			link.l1.go = "OGLStep_1";
		break;

		case "OGLStep_1":
			dialog.text = StringFromKey("Bishop_478");
			link.l1 = StringFromKey("Bishop_479");
			link.l1.go = "OGLStep_2";
		break;

		case "OGLStep_2":
			dialog.text = StringFromKey("Bishop_480");
			link.l1 = StringFromKey("Bishop_481");
			link.l1.go = "OGLStep_3";
		break;

		case "OGLStep_3":
			dialog.text = StringFromKey("Bishop_482");
			link.l1 = StringFromKey("Bishop_483");
			link.l1.go = "OGLStep_4";
		break;

		case "OGLStep_4":
			dialog.text = StringFromKey("Bishop_484");
			link.l1 = StringFromKey("Bishop_485");
			link.l1.go = "OGLStep_5";
		break;

		case "OGLStep_5":
			dialog.text = StringFromKey("Bishop_486");
			link.l1 = StringFromKey("Bishop_487");
			link.l1.go = "OGLStep_6";
		break;

		case "OGLStep_6":
			dialog.text = StringFromKey("Bishop_488");
			link.l1 = StringFromKey("Bishop_489");
			link.l1.go = "OGLStep_7";
		break;

		case "OGLStep_7":
			dialog.text = StringFromKey("Bishop_490");
			link.l1 = StringFromKey("Bishop_491");
			link.l1.go = "Exit";
			NextDiag.TempNode = "OGLStep_8";
			Pchar.questTemp.CapBloodLine.Ogl = false;
			AddQuestRecord("OglQuest", "1");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			AddLandQuestmark_Main(CharacterFromID("Bridgetown_usurer"), "CapBloodLine");
			QuestPointerDelLoc("Bridgetown_plantation", "reload", "houseS2");
			QuestPointerToLocEx("Bridgetown_town", "reload", "reload8_back", "OglQuest");
		break;

		case "OGLStep_8":
			if (CheckAttribute(Pchar, "questTemp.CapBloodLine.Ogl") && Pchar.questTemp.CapBloodLine.Ogl == true)
			{
				dialog.text = StringFromKey("Bishop_492");
				link.l1 = StringFromKey("Bishop_493");
				link.l1.go = "OGLStep_9";
			}
			else
			{
				NextDiag.TempNode = "OGLStep_8";
				dialog.text = StringFromKey("Bishop_494");
				link.l1 = StringFromKey("Bishop_495");
				link.l1.go = "Exit";
				NextDiag.TempNode = "OGLStep_8";
			}
		break;

		case "OGLStep_9":
			dialog.text = StringFromKey("Bishop_496");
			link.l1 = StringFromKey("Bishop_497");
			link.l1.go = "exit";
			QuestPointerDelLoc("Bridgetown_plantation", "reload", "houseS2");
			Pchar.questTemp.CapBloodLine.Ogl = true;
			Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer) + 1;
			NextDiag.TempNode = "OGLStep_10";
			AddQuestRecord("OglQuest", "3");
			CloseQuestHeader("OglQuest");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			SetCurrentQuestMark(characterFromId("Pitt"));
			CapBloodLine_AddOfficerReady();

			AddCharacterExpToSkill(PChar, SKILL_LEADERSHIP, 50);
			AddCharacterExpToSkill(PChar, SKILL_FORTUNE, 30);
		break;

		case "OGLStep_10":
			dialog.text = StringFromKey("Bishop_498");
			link.l1 = StringFromKey("Bishop_499");
			link.l1.go = "exit";
			NextDiag.TempNode = "OGLStep_10";
		break;

		case "OGLStep_11":
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			dialog.text = StringFromKey("Bishop_500");
			link.l1 = StringFromKey("Bishop_501");
			link.l1.go = "OGLStep_12";
		break;

		case "OGLStep_12":
			dialog.text = StringFromKey("Bishop_502");
			link.l1 = StringFromKey("Bishop_503");
			link.l1.go = "OGLStep_13";
		break;

		case "OGLStep_13":
			dialog.text = StringFromKey("Bishop_504");
			link.l1 = StringFromKey("Bishop_505");
			link.l1.go = "OGLStep_14";
		break;

		case "OGLStep_14":
			DialogExit();

			NPChar.Money = 0;
			NPChar.Payment = true;
			NPChar.DontClearDead = true;

			AddPassenger(pchar, NPChar, false);
			npchar.dialog.currentnode = "Ogl_On_Deck";
			CapBloodLine_OfficersCount();
			// AddDialogExitQuestFunction("OglAdd");

			DialogExit();
		break;

		case "Ogl_In_Shack":
			dialog.text = StringFromKey("Bishop_864");
			link.l1 = StringFromKey("Bishop_865");
			link.l1.go = "exit";
			NextDiag.TempNode = "Ogl_In_Shack";
		break;

		case "Ogl_On_Deck":
			dialog.text = StringFromKey("Bishop_869");
			link.l1 = StringFromKey("Bishop_870");
			link.l1.go = "exit";
			NextDiag.TempNode = "OGLStep_10";
		break;

		case "Ogl_OfficerStub":
			dialog.text = StringFromKey("Bishop_981");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Ogl_OfficerStub";
		break;

		case "Ogl_OfficerNode":
			dialog.text = StringFromKey("Bishop_982");
			link.l1 = StringFromKey("Bishop_983");
			link.l1.go = "exit";
			NextDiag.TempNode = "Ogl_OfficerNode";
		break;

		// Диалоги для туториала

		case "Pitt_GTutor_Cabin_1":
			if(CheckCharacterItem(Pchar, "map_normal") == 0) GiveItem2Character(Pchar, "map_normal");
			RefreshEquippedMaps(GetMainCharacter());

			dialog.text = StringFromKey("Bishop_506");
			link.l1 = StringFromKey("Bishop_507");
			link.l1.go = "Pitt_GTutor_Cabin_2";
		break;

		case "Pitt_GTutor_Cabin_2":
			dialog.text = StringFromKey("Bishop_508");
			link.l1 = StringFromKey("Bishop_509");
			link.l1.go = "Pitt_GTutor_Cabin_3";
		break;

		case "Pitt_GTutor_Cabin_3":
			dialog.text = StringFromKey("Bishop_510");
			link.l1 = "...";
			link.l1.go = "Pitt_GTutor_Cabin_Exit";
		break;

		case "Pitt_GTutor_Cabin_Exit":
			AddDialogExitQuestFunction("BloodLine_GlobalTutor_SetPittOffDialogs");
			DoQuestFunctionDelay("BloodLine_GlobalTutor_EndCabinDialog", 2.0);
			DialogExit();
		break;

		case "Pitt_GTutor_Tortuga1":
			dialog.text = StringFromKey("Bishop_511");
			link.l1 = StringFromKey("Bishop_512");
			link.l1.go = "Pitt_GTutor_Tortuga1_1";
		break;

		case "Pitt_GTutor_Tortuga1_1":
			dialog.text = StringFromKey("Bishop_513");
			link.l1 = StringFromKey("Bishop_514");
			link.l1.go = "Pitt_GTutor_Tortuga1_2";
		break;

		case "Pitt_GTutor_Tortuga1_2":
			dialog.text = StringFromKey("Bishop_515");
			link.l1 = StringFromKey("Bishop_516");
			link.l1.go = "Pitt_GTutor_Tortuga1_3";
		break;

		case "Pitt_GTutor_Tortuga1_3":
			n = sti(pchar.questTemp.BloodLine_GTutor.shipBuyMoney) +
				sti(pchar.questTemp.BloodLine_GTutor.shipGiveMoney) +
				sti(pchar.questTemp.BloodLine_GTutor.hireCrewMoney) *
				sti(pchar.questTemp.BloodLine_GTutor.hireCrewQty);
			AddMoneyToCharacter(pchar, n);

			dialog.text = StringFromKey("Bishop_517");
			link.l1 = StringFromKey("Bishop_518");
			link.l1.go = "Pitt_GTutor_Tortuga1_Exit";
		break;

		case "Pitt_GTutor_Tortuga1_Exit":
			DialogExit();
			CloseQuestHeader("Arabella"); // Временно уберём, чтобы не маячила
			CloseQuestHeader("CBL_Tortuga");

			LAi_ActorRunToLocation(NPChar, "reload", "reload4_back", "none", "", "", "BloodLine_GlobalTutor_EndTortuga1Dialog", 5.0);
			LAi_SetPlayerType(pchar);
		break;

		case "Pitt_GTutor_Tortuga2":
			dialog.text = StringFromKey("Bishop_519");
			link.l1 = StringFromKey("Bishop_520");
			link.l1.go = "Pitt_GTutor_Tortuga2_1";
		break;

		case "Pitt_GTutor_Tortuga2_1":
			dialog.text = StringFromKey("Bishop_521");
			link.l1 = StringFromKey("Bishop_522");
			link.l1.go = "Pitt_GTutor_Tortuga2_2";
		break;

		case "Pitt_GTutor_Tortuga2_2":
			dialog.text = StringFromKey("Bishop_523");
			link.l1 = "...";
			link.l1.go = "Pitt_GTutor_Tortuga2_Exit";

			NextDiag.TempNode = "Pitt_GTutor_Tortuga3";
		break;

		case "Pitt_GTutor_Tortuga2_Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			LAi_ActorRunToLocation(NPChar, "reload", "reload4_back", "none", "", "", "BloodLine_GlobalTutor_EndTortuga2Dialog", 10.0);
			LAi_SetPlayerType(pchar);
		break;

		case "Pitt_GTutor_Tortuga3":
			dialog.text = StringFromKey("Bishop_524");
			link.l1 = StringFromKey("Bishop_525");
			link.l1.go = "exit";
		break;

		// Обращение к команде
		case "BloodTalkWithCrew":
			dialog.text = "";
			link.l1 = StringFromKey("Bishop_984");
			link.l1.go = "BloodTalkWithCrew_1";
		break;

		case "BloodTalkWithCrew_1":
			dialog.text = "";
			link.l1 = StringFromKey("Bishop_985");
			link.l1.go = "BloodTalkWithCrew_2";
		break;

		case "BloodTalkWithCrew_2":
			AddDialogExitQuestFunction("CapBloodLine_MorningIsComming");
			DialogExit();
			locCameraFromToPos(19.22, 4.49, 102.1, true, 27.93, 1.34, 100.63);
		break;

		// Диего Эспиноса
		case "DiegoOnDeck":
			locCameraFromToPos(21.8, 4.35, 102.05, true, 25.76, 1.54, 110.25);
			dialog.text = StringFromKey("Bishop_986");
			link.l1 = "";
			link.l1.go = "DiegoOnDeck_1";
		break;

		case "DiegoOnDeck_1":
			locCameraFromToPos(21.8, 4.35, 102.35, true, 30.66, 1.44, 97.84);
			dialog.text = "";
			link.l1 = StringFromKey("Bishop_987");
			link.l1.go = "DiegoOnDeck_2";
		break;

		case "DiegoOnDeck_2":
			DialogExit();
			locCameraFromToPos(21.8, 4.35, 102.05, true, 25.76, 1.54, 110.25);

			sld = CharacterFromID("Hugtorp");
			CharacterTurnByChr(sld, CharacterFromID("Diego_Clone"));
			TeleportCharacterToPosAy(sld, 21.88, 2.65, 104.93, 2.9);
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "CBL_Normal_to_fight_fast", "CapBloodLine_HugtorpAttackDiego", 0.1);
			// LAi_ActorAnimation(sld, "attack_break_1", "CapBloodLine_HugtorpAttackDiego_1", 1.5);
		break;

		case "Diego_FirstTalk":
			if (VoiceGetLanguage() == "russian") PlaySound("Voice\Russian\FranceLine\horn.ogg");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_988");
			link.l1.go = "Diego_FirstTalk_1";
		break;

		case "Diego_FirstTalk_1":
			dialog.text = StringFromKey("Bishop_989");
			link.l1 = StringFromKey("Bishop_990");
			link.l1.go = "Diego_FirstTalk_2";
		break;

		case "Diego_FirstTalk_2":
			dialog.text = StringFromKey("Bishop_991");
			link.l1 = StringFromKey("Bishop_992");
			link.l1.go = "Diego_FirstTalk_3";
		break;

		case "Diego_FirstTalk_3":
			dialog.text = StringFromKey("Bishop_993");
			link.l1 = StringFromKey("Bishop_994");
			link.l1.go = "Diego_FirstTalk_4";
		break;

		case "Diego_FirstTalk_4":
			dialog.text = StringFromKey("Bishop_995");
			link.l1 = StringFromKey("Bishop_996");
			link.l1.go = "Diego_FirstTalk_5";
		break;

		case "Diego_FirstTalk_5":
			dialog.text = StringFromKey("Bishop_997");
			link.l1 = StringFromKey("Bishop_998");
			link.l1.go = "Diego_FirstTalk_6";
		break;

		case "Diego_FirstTalk_6":
			dialog.text = StringFromKey("Bishop_999");
			link.l1 = StringFromKey("Bishop_1000");
			link.l1.go = "Diego_FirstTalk_7";
		break;

		case "Diego_FirstTalk_7":
			dialog.text = StringFromKey("Bishop_1001");
			link.l1 = StringFromKey("Bishop_1002");
			link.l1.go = "Diego_FirstTalk_8";
		break;

		case "Diego_FirstTalk_8":
			dialog.text = StringFromKey("Bishop_1003");
			link.l1 = StringFromKey("Bishop_1004");
			link.l1.go = "Diego_FirstTalk_9";
		break;

		case "Diego_FirstTalk_9":
			dialog.text = StringFromKey("Bishop_1005");
			link.l1 = StringFromKey("Bishop_1006");
			link.l1.go = "Diego_FirstTalk_10";
		break;

		case "Diego_FirstTalk_10":
			dialog.text = StringFromKey("Bishop_1007");
			link.l1 = StringFromKey("Bishop_1008");
			link.l1.go = "Diego_FirstTalk_11";
		break;

		case "Diego_FirstTalk_11":
			dialog.text = StringFromKey("Bishop_1009");
			link.l1 = StringFromKey("Bishop_1010");
			link.l1.go = "Diego_FirstTalk_12";
		break;

		case "Diego_FirstTalk_12":
			dialog.text = StringFromKey("Bishop_1011");
			link.l1 = StringFromKey("Bishop_1012");
			link.l1.go = "Diego_FirstTalk_13";
		break;

		case "Diego_FirstTalk_13":
			dialog.text = StringFromKey("Bishop_1013");
			link.l1 = StringFromKey("Bishop_1014");
			link.l1.go = "Diego_FirstTalk_14";
		break;

		case "Diego_FirstTalk_14":
			dialog.text = StringFromKey("Bishop_1015");
			link.l1 = StringFromKey("Bishop_1016");
			link.l1.go = "Diego_FirstTalk_15";
		break;

		case "Diego_FirstTalk_15":
			dialog.text = StringFromKey("Bishop_1017");
			link.l1 = StringFromKey("Bishop_1018");
			link.l1.go = "Diego_FirstTalk_16";
		break;

		case "Diego_FirstTalk_16":
			dialog.text = StringFromKey("Bishop_1019");
			link.l1 = StringFromKey("Bishop_1020");
			link.l1.go = "Diego_FirstTalk_17";
		break;

		case "Diego_FirstTalk_17":
			dialog.text = StringFromKey("Bishop_1021");
			link.l1 = StringFromKey("Bishop_1022");
			link.l1.go = "Diego_FirstTalk_18";
		break;

		case "Diego_FirstTalk_18":
			dialog.text = StringFromKey("Bishop_1023");
			link.l1 = StringFromKey("Bishop_1024");
			link.l1.go = "Diego_FirstTalk_19";
		break;

		case "Diego_FirstTalk_19":
			dialog.text = StringFromKey("Bishop_1025");
			link.l1 = StringFromKey("Bishop_1026");
			link.l1.go = "Diego_FirstTalk_20";
		break;

		case "Diego_FirstTalk_20":
			dialog.text = StringFromKey("Bishop_1027");
			link.l1 = StringFromKey("Bishop_1028");
			link.l1.go = "Diego_FirstTalk_21";
		break;

		case "Diego_FirstTalk_21":
			dialog.text = StringFromKey("Bishop_1029");
			link.l1 = StringFromKey("Bishop_1030");
			link.l1.go = "Diego_FirstTalk_22";
		break;

		case "Diego_FirstTalk_22":
			dialog.text = StringFromKey("Bishop_1031");
			link.l1 = StringFromKey("Bishop_1032");
			link.l1.go = "Diego_FirstTalk_23";
		break;

		case "Diego_FirstTalk_23":
			dialog.text = StringFromKey("Bishop_1033");
			link.l1 = StringFromKey("Bishop_1034");
			link.l1.go = "Diego_FirstTalk_24";
		break;

		case "Diego_FirstTalk_24":
			dialog.text = StringFromKey("Bishop_1035");
			link.l1 = StringFromKey("Bishop_1036");
			link.l1.go = "Diego_FirstTalk_25";
		break;

		case "Diego_FirstTalk_25":
			dialog.text = StringFromKey("Bishop_1037");
			link.l1 = StringFromKey("Bishop_1038");
			link.l1.go = "Diego_FirstTalk_26";
		break;

		case "Diego_FirstTalk_26":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "Diego_FirstTalk_27";
		break;

		case "Diego_FirstTalk_27":
			dialog.text = StringFromKey("Bishop_1039");
			link.l1 = StringFromKey("Bishop_1040");
			link.l1.go = "Diego_FirstTalk_End";
			link.l2 = StringFromKey("Bishop_1041");
			link.l2.go = "Diego_FirstTalk_EndWait";
		break;

		case "Diego_FirstTalk_End":
			DialogExit();
			DoQuestFunctionDelay("CapBloodLine_RoadToEspaniola", 2.0);

			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Ground_StandUp_Fast", "CapBloodLine_RoadToEspaniola_2", 1.0);
		break;

		case "Diego_FirstTalk_EndWait":
			DialogExit();
			QuestPointerToLoc("My_Cabin_Quest", "reload", "reload1");
			SetFunctionLocatorCondition("CapBloodLine_RoadToEspaniola", "My_Cabin_Quest", "reload", "reload1", false);

			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Ground_StandUp_Fast", "CapBloodLine_RoadToEspaniola_2", 1.0);
		break;

		case "DiegoOnShore": // в бухте Самана
			if (LanguageGetLanguage() == "Russian") PlaySound("Voice\Russian\FranceLine\horn.ogg");
			dialog.text = StringFromKey("Bishop_1042");
			link.l1 = StringFromKey("Bishop_1043");
			link.l1.go = "DiegoOnShore_1";
		break;

		case "DiegoOnShore_1":
			dialog.text = StringFromKey("Bishop_1044");
			link.l1 = "...";
			link.l1.go = "DiegoOnShore_2";
		break;

		case "DiegoOnShore_2":
			StartInstantDialogNow("Hugtorp", "DiegoOnShore_3", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "DiegoOnShore_3":
			dialog.text = StringFromKey("Bishop_1045");
			link.l1 = "...";
			link.l1.go = "DiegoOnShore_4";
		break;

		case "DiegoOnShore_4":
			AddDialogExitQuestFunction("CapBloodLine_ReadySiguayo");
			DialogExit();
		break;

		case "DiegoOnShore_5": // Перед файтом на кулаках
			if (LanguageGetLanguage() == "Russian") PlaySound("Voice\Russian\FranceLine\demonplas.wav");
			RemoveLandQuestMark_Main(npchar, "CapBloodLine");
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1046");
			link.l1.go = "DiegoOnShore_6";
			CapBloodLine_PlaceOfficersBehindPchar();
		break;

		case "DiegoOnShore_6":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1047");
			link.l1.go = "DiegoOnShore_7";
		break;

		case "DiegoOnShore_7":
			dialog.text = StringFromKey("Bishop_1048");
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CapBloodLine_DiegoFistFightStart");
		break;

		case "DiegoOnShore_8_Win": // Победа
			dialog.text = StringFromKey("Bishop_608");
			link.l1 = StringFromKey("Bishop_1049");
			link.l1.go = "DiegoOnShore_9";
			CapBloodLine_PlaceOfficersBehindPchar();
		break;

		case "DiegoOnShore_9":
			dialog.text = StringFromKey("Bishop_1050");
			link.l1 = StringFromKey("Bishop_1051");
			link.l1.go = "DiegoOnShore_12";
		break;

		case "DiegoOnShore_8_Lose": // Поражение
			dialog.text = StringFromKey("Bishop_1052");
			link.l1 = StringFromKey("Bishop_1053");
			link.l1.go = "DiegoOnShore_12";
			CapBloodLine_PlaceOfficersBehindPchar();
		break;

		case "DiegoOnShore_12":
			dialog.text = StringFromKey("Bishop_1054");
			link.l1 = StringFromKey("Bishop_1055");
			link.l1.go = "DiegoOnShore_13";
		break;

		case "DiegoOnShore_13":
			dialog.text = StringFromKey("Bishop_1056");
			link.l1 = StringFromKey("Bishop_608");
			link.l1.go = "DiegoOnShore_14";
		break;

		case "DiegoOnShore_14":
			StartInstantDialogNow("Volverston", "DiegoOnShore_15", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "DiegoOnShore_15":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1057");
			link.l1 = StringFromKey("Bishop_1058");
			link.l1.go = "DiegoOnShore_16";
		break;

		case "DiegoOnShore_16":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1059");
			link.l1.go = "DiegoOnShore_17";
		break;

		case "DiegoOnShore_17":
			dialog.text = StringFromKey("Bishop_1060");
			link.l1 = StringFromKey("Bishop_1061");
			link.l1.go = "DiegoOnShore_19";
		break;

		case "DiegoOnShore_19":
			StartInstantDialogNow("Hugtorp", "DiegoOnShore_20", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "DiegoOnShore_20":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1062");
			link.l1 = StringFromKey("Bishop_1063");
			link.l1.go = "DiegoOnShore_21_1";
		break;

		case "DiegoOnShore_21_1":
			StartInstantDialogNow("Volverston", "DiegoOnShore_21", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "DiegoOnShore_21":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1064");
			link.l1 = StringFromKey("Bishop_1065");
			link.l1.go = "DiegoOnShore_22";
		break;

		case "DiegoOnShore_22":
			StartInstantDialogNow("Diego_Espinosa", "DiegoOnShore_23", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "DiegoOnShore_23":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1066");
			link.l1 = StringFromKey("Bishop_1067");
			link.l1.go = "DiegoOnShore_24";
		break;

		case "DiegoOnShore_24":
			StartInstantDialogNow("Volverston", "DiegoOnShore_25", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "DiegoOnShore_25":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1068");
			link.l1.go = "DiegoOnShore_26";
		break;

		case "DiegoOnShore_26":
			StartInstantDialogNow("Hugtorp", "DiegoOnShore_27", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "DiegoOnShore_27":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = "...";
			if (sti(pchar.questTemp.CapBloodLine.DiegoGuardsAlive) == 0) link.l1 = StringFromKey("Bishop_1069");
			else link.l1 = StringFromKey("Bishop_1070");
			link.l1.go = "DiegoOnShore_28";
		break;

		case "DiegoOnShore_28":
			StartInstantDialogNow("Dieke", "DiegoOnShore_29", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "DiegoOnShore_29":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1071");
			link.l1.go = "DiegoOnShore_30";
		break;

		case "DiegoOnShore_30":
			StartInstantDialogNow("Diego_Espinosa", "DiegoOnShore_31", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "DiegoOnShore_31":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1072");
			link.l1 = "...";
			link.l1.go = "DiegoOnShore_32";
		break;

		case "DiegoOnShore_32":
			AddDialogExitQuestFunction("CapBloodLine_OfficersAndDiegoToBoat");
			DialogExit();
		break;

		// Естебан Еспиноса
		case "EstebanFather_1":
			PlaySound("Voice\" + VoiceGetLanguage() + "\Gr_Ransack_2.wav");
			dialog.text = StringFromKey("Bishop_1073");
			link.l1 = StringFromKey("Bishop_608");
			link.l1.go = "EstebanFather_2";
		break;

		case "EstebanFather_2":
			dialog.text = StringFromKey("Bishop_1074");
			link.l1 = StringFromKey("Bishop_1075");
			link.l1.go = "EstebanEncarnacion_3";
		break;

		case "EstebanEncarnacion_3":
			dialog.text = StringFromKey("Bishop_1076");
			link.l1 = StringFromKey("Bishop_1077");
			link.l1.go = "EstebanEncarnacion_5";
		break;

		case "EstebanEncarnacion_5":
			dialog.text = StringFromKey("Bishop_1078");
			link.l1 = StringFromKey("Bishop_1079");
			link.l1.go = "EstebanEncarnacion_6";
		break;

		case "EstebanEncarnacion_6":
			dialog.text = StringFromKey("Bishop_1080");
			link.l1 = StringFromKey("Bishop_1081");
			link.l1.go = "EstebanEncarnacion_7";
		break;

		case "EstebanEncarnacion_7":
			dialog.text = StringFromKey("Bishop_1082");
			link.l1 = StringFromKey("Bishop_1083");
			link.l1.go = "EstebanEncarnacion_9";
		break;

		case "EstebanEncarnacion_9":
			dialog.text = StringFromKey("Bishop_1084");
			link.l1 = "...";
			pchar.questTemp.CapBloodLine.AliveDiegoGuard = CapBloodLine_GetAliveDiegoGuard();
			if (pchar.questTemp.CapBloodLine.AliveDiegoGuard != "") link.l1.go = "EstebanEncarnacion_10";
			else link.l1.go = "EstebanEncarnacion_11";
		break;

		case "EstebanEncarnacion_10":
			CharacterTurnByChr(npchar, CharacterFromID(pchar.questTemp.CapBloodLine.AliveDiegoGuard));
			CharacterTurnByChr(CharacterFromID(pchar.questTemp.CapBloodLine.AliveDiegoGuard), npchar);

			if (sti(pchar.questTemp.CapBloodLine.DieGoGuardsAlive) == 1) dialog.text = StringFromKey("Bishop_1085");
			else dialog.text = StringFromKey("Bishop_1086");
			link.l1 = "...";
			link.l1.go = "EstebanEncarnacion_11";
		break;

		case "EstebanEncarnacion_11":
			CharacterTurnByChr(npchar, pchar);
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1087");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CapBloodLine_SonsTrable_5");
		break;

		case "EstebanEncarnacion_12":
			CharacterTurnToLoc(pchar, "goto", "goto14");
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1088");
			link.l1.go = "exit";
		break;

		case "CapBloodLine_Tortuga_1":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1089");
			link.l1 = "...";
			link.l1.go = "CapBloodLine_Tortuga_2";
		break;

		case "CapBloodLine_Tortuga_2":
			StartInstantDialogNow("Ogl", "CapBloodLine_Tortuga_3", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "CapBloodLine_Tortuga_3":
			dialog.text = StringFromKey("Bishop_1090");
			link.l1 = "...";
			link.l1.go = "CapBloodLine_Tortuga_4";
		break;

		case "CapBloodLine_Tortuga_4":
			StartInstantDialogNow("Dieke", "CapBloodLine_Tortuga_5", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "CapBloodLine_Tortuga_5":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1091");
			link.l1 = StringFromKey("Bishop_1092");
			link.l1.go = "CapBloodLine_Tortuga_6";
		break;

		case "CapBloodLine_Tortuga_6":
			StartInstantDialogNow("Hugtorp", "CapBloodLine_Tortuga_7", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "CapBloodLine_Tortuga_7":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1093");
			link.l1 = StringFromKey("Bishop_1094");
			link.l1.go = "CapBloodLine_Tortuga_8";
		break;

		case "CapBloodLine_Tortuga_8":
			StartInstantDialogNow("Volverston", "CapBloodLine_Tortuga_9", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "CapBloodLine_Tortuga_9":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1095");
			link.l1 = "...";
			link.l1.go = "CapBloodLine_Tortuga_10";
		break;

		case "CapBloodLine_Tortuga_10":
			StartInstantDialogNow("Dieke", "CapBloodLine_Tortuga_11", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "CapBloodLine_Tortuga_11":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1096");
			link.l1 = StringFromKey("Bishop_1097");
			link.l1.go = "CapBloodLine_Tortuga_12";
		break;

		case "CapBloodLine_Tortuga_12":
			StartInstantDialogNow("Volverston", "CapBloodLine_Tortuga_13", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "CapBloodLine_Tortuga_13":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1098");
			link.l1 = "...";
			link.l1.go = "CapBloodLine_Tortuga_14";
		break;

		case "CapBloodLine_Tortuga_14":
			StartInstantDialogNow("Hugtorp", "CapBloodLine_Tortuga_15", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "CapBloodLine_Tortuga_15":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1099");
			link.l1 = StringFromKey("Bishop_1100");
			link.l1.go = "CapBloodLine_Tortuga_16";
		break;

		case "CapBloodLine_Tortuga_16":
			StartInstantDialogNow("Volverston", "CapBloodLine_Tortuga_17", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "CapBloodLine_Tortuga_17":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1101");
			link.l1 = "...";
			link.l1.go = "CapBloodLine_Tortuga_18";
		break;

		case "CapBloodLine_Tortuga_18":
			StartInstantDialogNow("Hugtorp", "CapBloodLine_Tortuga_19", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "CapBloodLine_Tortuga_19":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1102");
			link.l1 = StringFromKey("Bishop_1103");
			link.l1.go = "CapBloodLine_Tortuga_20";
		break;

		case "CapBloodLine_Tortuga_20":
			StartInstantDialogNow("Volverston", "CapBloodLine_Tortuga_21", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "CapBloodLine_Tortuga_21":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1104");
			link.l1 = StringFromKey("Bishop_1105");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CapBloodLine_FinalOfTheSecondStage");
		break;

		// Мигель Эспиноса на палубе
		case "MiguelEncarnacion":
			if (VoiceGetLanguage() == "russian") PlaySound("Voice\Russian\Gr_Commander_pir1.wav");
			RemoveLandQuestMark_Main(npchar, "CapBloodLine");
			TeleportCharacterToPosAy(CharacterFromID("Esteban_Espinosa"), 0.51, 4.06, 6.26, 0.0);
			CharacterTurnByChr(npchar, CharacterFromID("Esteban_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Esteban_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_1106");
			link.l1 = "...";
			link.l1.go = "MiguelEncarnacion_ToEstebanGreeting";
		break;

		case "MiguelEncarnacion_ToEstebanGreeting":
			StartInstantDialogNow("Esteban_Espinosa", "EstebanEncarnacion_Greeting", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "EstebanEncarnacion_Greeting":
			CharacterTurnByChr(npchar, CharacterFromID("Miguel_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Miguel_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_1107");
			link.l1 = "...";
			link.l1.go = "EstebanEncarnacion_ToMiguelIntroduction";
		break;

		case "EstebanEncarnacion_ToMiguelIntroduction":
			StartInstantDialogNow("Miguel_Espinosa", "MiguelEncarnacion_2", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "MiguelEncarnacion_2":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1108");
			link.l1 = StringFromKey("Bishop_1109");
			link.l1.go = "MiguelEncarnacion_ToMonk";
		break;

		case "MiguelEncarnacion_ToMonk":
			StartInstantDialogNow("Encarnacion_Priest", "Encarnacion_Monk_1", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "Encarnacion_Monk_1":
			PlaySound("Voice\" + VoiceGetLanguage() + "\Gr_Church_10.wav");
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1110");
			link.l1 = StringFromKey("Bishop_1111");
			link.l1.go = "Encarnacion_Monk_ToMiguel";
		break;

		case "Encarnacion_Monk_ToMiguel":
			StartInstantDialogNow("Miguel_Espinosa", "MiguelEncarnacion_AskAboutDiego", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "MiguelEncarnacion_AskAboutDiego":
			CharacterTurnByChr(npchar, CharacterFromID("Esteban_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Esteban_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_1112");
			link.l1 = "...";
			link.l1.go = "MiguelEncarnacion_ToEstebanAnswer";
		break;

		case "MiguelEncarnacion_ToEstebanAnswer":
			StartInstantDialogNow("Esteban_Espinosa", "EstebanEncarnacion_AboutDiego", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "EstebanEncarnacion_AboutDiego":
			CharacterTurnByChr(npchar, CharacterFromID("Miguel_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Miguel_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_1113");
			link.l1 = "...";
			link.l1.go = "EstebanEncarnacion_ToMiguelAttack";
		break;

		case "EstebanEncarnacion_ToMiguelAttack":
			StartInstantDialogNow("Miguel_Espinosa", "MiguelEncarnacion_3", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "MiguelEncarnacion_3":
			CharacterTurnByChr(npchar, CharacterFromID("Esteban_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Esteban_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_1114");
			link.l1 = "...";
			link.l1.go = "MiguelEncarnacion_3_1";
		break;

		case "MiguelEncarnacion_3_1":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1115");
			link.l1.go = "MiguelEncarnacion_4";
		break;

		case "MiguelEncarnacion_4":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1116");
			link.l1.go = "MiguelEncarnacion_5";
		break;

		case "MiguelEncarnacion_5":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1117");
			link.l1.go = "MiguelEncarnacion_6";
		break;

		case "MiguelEncarnacion_6":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1118");
			link.l1.go = "MiguelEncarnacion_7";
		break;

		case "MiguelEncarnacion_7":
			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1119");
			link.l1.go = "MiguelEncarnacion_8";
		break;

		case "MiguelEncarnacion_8":
			dialog.text = StringFromKey("Bishop_1120");

			if (GetCharacterItem(pchar, "chest") >= 4)
			{
				link.l1 = StringFromKey("Bishop_1121");
				link.l1.go = "MiguelEncarnacion_ToEstebanRansom";
			}
			else
			{
				Notification(StringFromKey("InfoMessages_260"), "BoxMinus");
				link.l1 = StringFromKey("Bishop_1122");
				link.l1.go = "MiguelEncarnacion_NoChests_1";
			}
		break;

		case "MiguelEncarnacion_NoChests_1":
			dialog.text = StringFromKey("Bishop_1123");
			link.l1 = "...";
			link.l1.go = "MiguelEncarnacion_NoChests_2";
		break;

		case "MiguelEncarnacion_NoChests_2":
			CharacterTurnByChr(npchar, CharacterFromID("Esteban_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Esteban_Espinosa"), npchar);

			dialog.text = StringFromKey("Bishop_1124");
			link.l1 = "...";
			link.l1.go = "MiguelEncarnacion_NoChests_ToEsteban";
		break;

		case "MiguelEncarnacion_NoChests_ToEsteban":
			StartInstantDialogNow("Esteban_Espinosa", "EstebanEncarnacion_NoChests_1", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "EstebanEncarnacion_NoChests_1":
			CharacterTurnByChr(npchar, CharacterFromID("Miguel_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Miguel_Espinosa"), npchar);

			dialog.text = StringFromKey("Bishop_1125");
			link.l1 = "...";
			link.l1.go = "EstebanEncarnacion_NoChests_ToMiguel";
		break;

		case "EstebanEncarnacion_NoChests_ToMiguel":
			StartInstantDialogNow("Miguel_Espinosa", "MiguelEncarnacion_NoChests_3", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "MiguelEncarnacion_NoChests_3":
			dialog.text = StringFromKey("Bishop_1126");
			link.l1 = "...";
			link.l1.go = "MiguelEncarnacion_NoChests_4";
		break;

		case "MiguelEncarnacion_NoChests_4":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);

			dialog.text = "...";
			link.l1 = StringFromKey("Bishop_1127");
			link.l1.go = "MiguelEncarnacion_NoChests_5";
		break;

		case "MiguelEncarnacion_NoChests_5":
			dialog.text = StringFromKey("Bishop_1128");
			link.l1 = StringFromKey("Bishop_1129");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CapBloodLine_EncarnacionFailure");
		break;

		case "MiguelEncarnacion_ToEstebanRansom":
			StartInstantDialogNow("Esteban_Espinosa", "EstebanEncarnacion_Ransom", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "EstebanEncarnacion_Ransom":
			CharacterTurnByChr(npchar, CharacterFromID("Miguel_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Miguel_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_1130");
			link.l1 = "...";
			link.l1.go = "EstebanEncarnacion_ToMiguelRansom";
			TakeNItemsNotification(pchar, "chest", -4, "default", "", "");
		break;

		case "EstebanEncarnacion_ToMiguelRansom":
			StartInstantDialogNow("Miguel_Espinosa", "MiguelEncarnacion_9", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "MiguelEncarnacion_9":
			CharacterTurnByChr(npchar, CharacterFromID("Esteban_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Esteban_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_1131");
			link.l1 = "...";
			link.l1.go = "MiguelEncarnacion_10";
		break;

		case "MiguelEncarnacion_10":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1132");
			link.l1 = StringFromKey("Bishop_1133");
			link.l1.go = "MiguelEncarnacion_ToEstebanDeparture";
		break;

		case "MiguelEncarnacion_ToEstebanDeparture":
			StartInstantDialogNow("Esteban_Espinosa", "EstebanEncarnacion_Departure", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "EstebanEncarnacion_Departure":
			CharacterTurnByChr(npchar, CharacterFromID("Miguel_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Miguel_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_1134");
			link.l1 = "...";
			link.l1.go = "EstebanEncarnacion_ToMiguelFarewell";
		break;

		case "EstebanEncarnacion_ToMiguelFarewell":
			StartInstantDialogNow("Miguel_Espinosa", "MiguelEncarnacion_FarewellEsteban", "Quest\CapBloodLine\Bishop.c", true);
		break;

		case "MiguelEncarnacion_FarewellEsteban":
			CharacterTurnByChr(npchar, CharacterFromID("Esteban_Espinosa"));
			CharacterTurnByChr(CharacterFromID("Esteban_Espinosa"), npchar);
			dialog.text = StringFromKey("Bishop_1135");
			link.l1 = "...";
			link.l1.go = "MiguelEncarnacion_Farewell_1";
		break;

		case "MiguelEncarnacion_Farewell_1":
			CharacterTurnByChr(npchar, pchar);
			CharacterTurnByChr(pchar, npchar);
			dialog.text = StringFromKey("Bishop_1136");
			link.l1 = StringFromKey("Bishop_1137");
			link.l1.go = "MiguelEncarnacion_Farewell_2";
		break;

		case "MiguelEncarnacion_Farewell_2":
			dialog.text = StringFromKey("Bishop_1138");
			link.l1 = StringFromKey("Bishop_1139");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CapBloodLine_EncarnacionFarewell");
		break;



	}
}

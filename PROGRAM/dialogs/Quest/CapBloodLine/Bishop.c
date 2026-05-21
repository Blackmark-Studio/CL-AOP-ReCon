// Блад
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLocator;
	int iTime, n;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	/*
		switch(Pchar.questTemp.CapBloodLine.stat)
		{
			  case "1":
				Dialog.CurrentNode = "First Bishop";
			break;

			case "2":
				Dialog.CurrentNode = "First Guard";
			break;

			case "3":
				Dialog.CurrentNode = "First Stid";
			break;

			case "4":
				Dialog.CurrentNode = "First MsStid";
			break;
		}
		*/

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
			locCameraFollowEx(true);
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
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
			Pchar.questTemp.CapBloodLine.stat = "";
			CapBloodLineInit("");
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

		case "First Bishop":
			if (NPChar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Bishop_80");
				link.l1 = StringFromKey("Bishop_81");
				link.l1.go = "BStep_0";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = StringFromKey("Bishop_82");
				link.l1 = StringFromKey("Bishop_83");
				link.l1.go = "Exit";
			}
		break;

		case "BStep_0":
			dialog.text = StringFromKey("Bishop_84");
			link.l1 = StringFromKey("Bishop_85");
			link.l1.go = "Bishop_Away";
			LAi_LockFightMode(pchar, false);
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(loadedLocation, false);
			//HardCoffee закрыть гостинную и аварийный выход
			LocatorReloadEnterDisable("Bridgetown_Townhall", "reload3", true);
			LocatorReloadEnterDisable("Bridgetown_Townhall", "reload2", true);
			LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", true);
			Pchar.questTemp.CapBloodLine.stat = "CureMisStid";
			NextDiag.TempNode = "First Bishop";
			//сроки 4 часа
			PChar.quest.CapBloodLineTimer_1.win_condition.l1 = "Timer";
			PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.hour = 4;
			PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			PChar.quest.CapBloodLineTimer_1.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			PChar.quest.CapBloodLineTimer_1.function = "CapBloodLine_q1_Late";
			AddQuestRecord("CapBloodLine_q1", "1");
			AddLandQuestmark_Main(CharacterFromID("Bridgetown_Mayor"), "CapBloodLine");
			AddDialogExitQuestFunction("CapBloodLine_CureMisStid_AddQuestPointers");
			AddDialogExitQuestFunction("Tutorial_BloodPrologue_TimeScale_Delay");
		break;

		case "BStep_1":
			dialog.text = StringFromKey("Bishop_86");
			link.l1 = StringFromKey("Bishop_87");
			link.l1.go = "Exit";
			NextDiag.TempNode = "BStep_1";
		break;

		case "BStep_2":
			dialog.text = StringFromKey("Bishop_88");
			link.l1 = StringFromKey("Bishop_89");
			link.l1.go = "BStep_3";
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
			link.l1.go = "Exit";
			NextDiag.TempNode = "BStep_1";
			sld = characterFromID("Quest_Habitue");
			sld.Dialog.CurrentNode = "QHStep_0";
			AddQuestRecord("DiekeQuest", "2");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			AddLandQuestmark_Main(sld, "CapBloodLine");
			QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "DiekeQuest");
			QuestPointerDelLoc("Bridgetown_plantation", "reload", "houseSp1");
		break;

		case "Bishop_Away":
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Bridgetown_Plantation_Sp1", "goto", "goto1", "BishopOnHouse", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

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
			dialog.text = StringFromKey("Bishop_128");
			link.l1 = StringFromKey("Bishop_129");
			link.l1.go = "GStep_0";
		break;

		case "GStep_0":
			dialog.text = StringFromKey("Bishop_130");
			link.l1 = StringFromKey("Bishop_131");
			link.l1.go = "Exit";
			LocatorReloadEnterDisable("BridgeTown_town", "reload3_back", false);//отпираем резиденцию
			LocatorReloadEnterDisable("BridgeTown_town", "reloadR1", false);
			//солдата на место
			LAi_SetLoginTime(npchar, 6.0, 23.0);
			npchar.protector = false;
			npchar.protector.CheckAlways = 0;
			npchar.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			RemoveLandQuestMark_Main(npchar, "CapBloodLine");
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

		//--> Миссис Стид

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
			//Вывести экран в темноту, выполнить квест questFadeOut, вернуть всё обратно, выполнить квест questFadeIn
			//LAi_Fade("", "CapBloodLine_q1_Complited");
			CapBloodLine_q1_Complited("");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
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
			link.l1.go = "Exit";
			NextDiag.TempNode = "NStep_4";
			NPChar.lifeDay = 0;
			CloseQuestHeader("CapBloodLine_q2");
			CapBloodLine_q3_Complited();
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
			AddLandQuestmark_Main(CharacterFromID("Pitt"), "CapBloodLine");
			QuestPointerToLoc("Bridgetown_town", "reload", "gate1_back");
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
			TakeNItemsNotification(pchar, "migraine_potion", 1, "", "migraine_potion", "");
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
			ClearActiveStageNotifications();
			TakeNItemsNotification(pchar, "recipe_migraine_potion", 1, "default", "Document", "noSound");
		break;

		case "DStep_8":
			dialog.text = StringFromKey("Bishop_251");
			link.l1 = StringFromKey("Bishop_252");
			link.l1.go = "Exit_Away";
			TakeNItemsNotification(pchar, "lamp", 1, "default", "", "");
			TakeNItemsNotification(pchar, "mortar_and_pestle", 1, "default", "", "noSound");
			AddDialogExitQuestFunction("Tutorial_BloodPrologue_Alchemy_Delay");
		break;

		case "DStep_9":
			dialog.text = StringFromKey("Bishop_253");
			link.l1 = StringFromKey("Bishop_254");
			link.l1.go = "DStep_6";
		break;

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
			AddDialogExitQuestFunction("CapBloodLine_q2_PrepareToEscape_AddQuestMarks");
		break;

		case "PStep_4":
			if (CheckAttribute(Pchar, "questTemp.CapBloodLine.Officer") && Pchar.questTemp.CapBloodLine.Officer == 4 && Pchar.questTemp.CapBloodLine.stat == "ReadyToEscape")
			{
				dialog.text = StringFromKey("Bishop_264");
				link.l1 = StringFromKey("Bishop_265");
				link.l1.go = "PStep_9";
				while (GetCharacterItem(pchar, "Weapon_for_escape") > 0)//homo fix 06/02/08 отбираем все квестовое оружие
				{
					TakeItemFromCharacter(Pchar, "Weapon_for_escape");
				}
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
			Pchar.questTemp.CapBloodLine.stat = "";
			chrDisableReloadToLocation = false;
			AddDialogExitQuestFunction("ChangePIRATES");
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
			// лочим локатор, пока не возьмем всех оффов
			LocatorReloadEnterDisable("BridgeTown_town", "reloadShip", true);
			AddDialogExitQuestFunction("CapBlood_CheckOfficersRecruit");
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
		break;

		case "VLStep_1":
			dialog.text = StringFromKey("Bishop_401");
			link.l1 = StringFromKey("Bishop_402");
			link.l1.go = "Exit";
			NextDiag.TempNode = "VLStep_1";
		break;

		case "VLStep_2":
			dialog.text = StringFromKey("Bishop_403");
			link.l1 = StringFromKey("Bishop_404");
			link.l1.go = "VLStep_3";
			chrDisableReloadToLocation = false;
		break;

		case "VLStep_3":
			dialog.text = StringFromKey("Bishop_405");
			link.l1 = StringFromKey("Bishop_406");
			link.l1.go = "VLStep_4";
		break;

		case "VLStep_4":
			dialog.text = StringFromKey("Bishop_407");
			link.l1 = StringFromKey("Bishop_408");
			link.l1.go = "VLStep_5";
		break;

		case "VLStep_5":
			dialog.text = StringFromKey("Bishop_409");
			link.l1 = StringFromKey("Bishop_410");
			link.l1.go = "Exit";
			AddDialogExitQuestFunction("ReturnToPlantation3");
			AddQuestRecord("EscapeFormBarbados", "1");
		break;

		case "VLStep_6":
			dialog.text = StringFromKey("Bishop_411");
			if (Pchar.questTemp.CapBloodLine.SpainInBridgetown == false)
			{
				link.l1 = StringFromKey("Bishop_412");
				link.l1.go = "VLStep_7";
			}
			else
			{
				link.l1 = StringFromKey("Bishop_413");
				link.l1.go = "VLStep_8";
			}
			CapBloodLine_ReachQuestPointer_Escape_ClearAll();
		break;

		case "VLStep_7":
			dialog.text = StringFromKey("Bishop_414");
			link.l1 = StringFromKey("Bishop_415");
			link.l1.go = "VLStep_8";
			AddQuestRecord("EscapeFormBarbados", "3");
		break;

		case "VLStep_8":
			dialog.text = StringFromKey("Bishop_416");
			link.l1 = StringFromKey("Bishop_417");
			link.l1.go = "VLStep_9";
		break;

		case "VLStep_9":
			dialog.text = StringFromKey("Bishop_418");
			link.l1 = StringFromKey("Bishop_419");
			link.l1.go = "VLStep_10";
		break;

		case "VLStep_10":
			dialog.text = StringFromKey("Bishop_420");
			link.l1 = StringFromKey("Bishop_421");
			link.l1.go = "Exit";
			AddDialogExitQuestFunction("CapBloodOfficers");
			AddQuestRecord("EscapeFormBarbados", "4");
			NextDiag.TempNode = "VLStep_10b";
		break;

		case "VLStep_10b":
			dialog.text = StringFromKey("Bishop_422");
			link.l1 = StringFromKey("Bishop_423");
			link.l1.go = "Exit";
			NextDiag.TempNode = "VLStep_10b";
//			AddDialogExitQuestFunction("CapBloodOfficers");
		break;

		case "VLStep_11":
			dialog.text = StringFromKey("Bishop_424");
			link.l1 = StringFromKey("Bishop_425");
			link.l1.go = "VLStep_12";
		break;

		case "VLStep_12":
			dialog.text = StringFromKey("Bishop_426");
			link.l1 = StringFromKey("Bishop_427");
			link.l1.go = "VLStep_13";
		break;

		case "VLStep_13":
			dialog.text = StringFromKey("Bishop_428");
			link.l1 = StringFromKey("Bishop_429");
			link.l1.go = "Exit_RunAway";
			Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
			Pchar.questTemp.CapBloodLine.iTime = 3;

			NPChar.Money = 0;
			NPChar.Payment = true;
			NPChar.DontClearDead = true;

			AddPassenger(pchar, NPChar, false);
			AddDialogExitQuestFunction("VolverstonAdd");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

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
			dialog.text = StringFromKey("Bishop_458");
			link.l1 = StringFromKey("Bishop_459");
			link.l1.go = "HTStep_14";
		break;

		case "HTStep_14":
			dialog.text = StringFromKey("Bishop_460");
			link.l1 = StringFromKey("Bishop_461");
			link.l1.go = "Exit_RunAway";
			Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
			Pchar.questTemp.CapBloodLine.iTime = 3;

			NPChar.Money = 0;
			NPChar.Payment = true;
			NPChar.DontClearDead = true;

			AddPassenger(pchar, NPChar, false);
			AddDialogExitQuestFunction("HugtorpAdd");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

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
			sld = characterFromID("Bishop");
			sld.Dialog.CurrentNode = "BStep_2";
			AddQuestRecord("DiekeQuest", "1");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			AddLandQuestmark_Main(CharacterFromID("Bishop"), "CapBloodLine");
			QuestPointerToLoc("Bridgetown_plantation", "reload", "houseSp1");
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
		break;

		case "DKStep_4":
			dialog.text = StringFromKey("Bishop_470");
			link.l1 = StringFromKey("Bishop_471");
			link.l1.go = "exit";
			NextDiag.TempNode = "DKStep_4";
		break;

		case "DKStep_5":
			dialog.text = StringFromKey("Bishop_472");
			link.l1 = StringFromKey("Bishop_473");
			link.l1.go = "DKStep_6";
		break;

		case "DKStep_6":
			dialog.text = StringFromKey("Bishop_474");
			link.l1 = StringFromKey("Bishop_475");
			link.l1.go = "Exit_RunAway";
			Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
			Pchar.questTemp.CapBloodLine.iTime = 3;

			NPChar.Money = 0;
			NPChar.Payment = true;
			NPChar.DontClearDead = true;

			AddPassenger(pchar, NPChar, false);
			AddDialogExitQuestFunction("DiekeAdd");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

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
			Pchar.questTemp.CapBloodLine.Ogl = true;
			Pchar.questTemp.CapBloodLine.Officer = sti(Pchar.questTemp.CapBloodLine.Officer) + 1;
			NextDiag.TempNode = "OGLStep_10";
			AddQuestRecord("OglQuest", "3");
			CloseQuestHeader("OglQuest");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			SetCurrentQuestMark(characterFromId("Pitt"));
		break;

		case "OGLStep_10":
			dialog.text = StringFromKey("Bishop_498");
			link.l1 = StringFromKey("Bishop_499");
			link.l1.go = "exit";
			NextDiag.TempNode = "OGLStep_10";
		break;

		case "OGLStep_11":
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
			link.l1.go = "Exit_RunAway";
			Pchar.questTemp.CapBloodLine.sLocator = "reloadShip";
			Pchar.questTemp.CapBloodLine.iTime = 3;

			NPChar.Money = 0;
			NPChar.Payment = true;
			NPChar.DontClearDead = true;

			AddPassenger(pchar, NPChar, false);
			AddDialogExitQuestFunction("OglAdd");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
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
	}
}

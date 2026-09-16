void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Exit_Fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar);
			for (i = 1; i <= 3; i++)
			{
				iTemp = GetCharacterIndex("GangMan_" + i);
				if (iTemp < 0) continue;
				sld = &characters[iTemp];
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");

			if (pchar.GenQuest.EncGirl == "RapersTreasure")
			{
				LAi_group_SetCheckFunction("EnemyFight", "EncGirl_RapersAfter");
			}
			else
			{
				LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");
				sld = CharacterFromID("CangGirl");
				LAi_SetActorType(sld);
				LAi_ActorAfraid(sld, npchar, true);
			}
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "exit_noFight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);
			for (i = 1; i <= 3; i++)
			{
				iTemp = GetCharacterIndex("GangMan_" + i);
				if (iTemp < 0) continue;
				sld = &characters[iTemp];
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, characterFromId("CangGirl"), "", -1);
				LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, false, "LandEnc_RapersBeforeDialog");
			}
			sld = CharacterFromID("CangGirl");
			LAi_SetActorType(sld);
			LAi_ActorAfraid(sld, npchar, true);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "First time":
			for (i = 1; i <= 3; i++)
			{
				iTemp = GetCharacterIndex("GangMan_" + i);
				if (iTemp < 0) continue;
				sld = &characters[iTemp];
				LAi_type_actor_Reset(sld);
				LAi_RemoveCheckMinHP(sld);
			}
			//			Diag.TempNode = "OnceAgain";
			if (pchar.GenQuest.EncGirl == "Begin_1")
			{
				dialog.text = StringFromKey("Rapers_4", LinkRandPhrase(
							StringFromKey("Rapers_1", pchar),
							StringFromKey("Rapers_2"),
							StringFromKey("Rapers_3", pchar)));
				link.l1 = StringFromKey("Rapers_8", LinkRandPhrase(
							StringFromKey("Rapers_5"),
							StringFromKey("Rapers_6"),
							StringFromKey("Rapers_7")));
				link.l1.go = "Node_Fight";
				link.l2 = StringFromKey("Rapers_11", RandPhraseSimple(
							StringFromKey("Rapers_9", pchar),
							StringFromKey("Rapers_10", pchar)));
				link.l2.go = "Exit_NoFight";
				pchar.GenQuest.EncGirl = "Begin_11";
			}
			if (pchar.GenQuest.EncGirl == "Begin_2")
			{
				if (sti(pchar.rank) < 10)
				{
					dialog.text = StringFromKey("Rapers_15", LinkRandPhrase(
								StringFromKey("Rapers_12", pchar),
								StringFromKey("Rapers_13"),
								StringFromKey("Rapers_14", pchar)));
					link.l1 = StringFromKey("Rapers_19", LinkRandPhrase(
								StringFromKey("Rapers_16"),
								StringFromKey("Rapers_17"),
								StringFromKey("Rapers_18")));
					link.l1.go = "Node_Fight";
					link.l2 = StringFromKey("Rapers_22", RandPhraseSimple(
								StringFromKey("Rapers_20", pchar),
								StringFromKey("Rapers_21", pchar)));
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_11";
				}
				else
				{
					dialog.text = StringFromKey("Rapers_25", RandPhraseSimple(
								StringFromKey("Rapers_23", pchar),
								StringFromKey("Rapers_24", pchar)));
					link.l1 = StringFromKey("Rapers_26");
					link.l1.go = "Node_3";
					link.l2 = StringFromKey("Rapers_29", RandPhraseSimple(
								StringFromKey("Rapers_27", pchar),
								StringFromKey("Rapers_28")));
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}
			if (pchar.GenQuest.EncGirl == "Begin_3")
			{
				if (sti(pchar.rank) < 20)
				{
					dialog.text = StringFromKey("Rapers_30", pchar);
					link.l1 = StringFromKey("Rapers_31");
					link.l1.go = "Node_5";
					pchar.GenQuest.EncGirl = "Begin_33";
				}
				else
				{
					dialog.text = StringFromKey("Rapers_34", RandPhraseSimple(
								StringFromKey("Rapers_32", pchar),
								StringFromKey("Rapers_33", pchar)));
					link.l1 = StringFromKey("Rapers_35");
					link.l1.go = "Node_3";
					link.l2 = StringFromKey("Rapers_38", RandPhraseSimple(
								StringFromKey("Rapers_36", pchar),
								StringFromKey("Rapers_37")));
					link.l2.go = "Exit_NoFight";
					pchar.GenQuest.EncGirl = "Begin_22";
				}
			}
		break;

		case "Node_Fight":
			dialog.text = StringFromKey("Rapers_41", RandPhraseSimple(
						StringFromKey("Rapers_39", pchar),
						StringFromKey("Rapers_40", pchar)));
			link.l1 = StringFromKey("Rapers_42");
			link.l1.go = "Exit_Fight";
			ChangeCharacterReputation(pchar, 5);
		break;

		case "Node_3":
			pchar.GenQuest.EncGirl.price = 1100 * (rand(4) + 5) + 200 * sti(pchar.rank);
			dialog.text = StringFromKey("Rapers_43", pchar, FindMoneyString(sti(pchar.GenQuest.EncGirl.price)));
			if (sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.price))
			{
				link.l1 = StringFromKey("Rapers_46", RandPhraseSimple(
							StringFromKey("Rapers_44"),
							StringFromKey("Rapers_45")));
				link.l1.go = "Node_4";
			}
			link.l2 = StringFromKey("Rapers_50", LinkRandPhrase(
						StringFromKey("Rapers_47"),
						StringFromKey("Rapers_48"),
						StringFromKey("Rapers_49")));
			link.l2.go = "Node_Fight";
		break;

		case "Node_4": // бандюки уходят, девица остаётся - ГГ её выкупил у бандюков
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.price)));
			ChangeCharacterReputation(pchar, 7);
			pchar.GenQuest.EncGirl.Saved_CangGirl = true;
			pchar.GenQuest.EncGirl.Ransom = true;
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			for (i = 1; i <= 3; i++)
			{
				iTemp = GetCharacterIndex("GangMan_" + i);
				if (iTemp < 0) continue;
				sld = &characters[iTemp];
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				if (i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;

		case "Node_5":
			dialog.text = StringFromKey("Rapers_51");
			link.l1 = StringFromKey("Rapers_54", RandPhraseSimple(
						StringFromKey("Rapers_52"),
						StringFromKey("Rapers_53")));
			link.l1.go = "Exit_NoFight";
			link.l2 = StringFromKey("Rapers_57", RandPhraseSimple(
						StringFromKey("Rapers_55"),
						StringFromKey("Rapers_56")));
			link.l2.go = "Node_6";
			link.l3 = StringFromKey("Rapers_58", pchar);
			link.l3.go = "Node_7";
		break;

		case "Node_6":
			dialog.text = StringFromKey("Rapers_59", pchar);
			link.l1 = StringFromKey("Rapers_60");
			link.l1.go = "Exit_Fight";
		break;

		case "Node_7":
			pchar.GenQuest.EncGirl.Saved_CangGirl = true;
			if (pchar.GenQuest.EncGirl.city == "Panama") i = drand(2);
			else if (pchar.GenQuest.EncGirl.city == "FortOrange") i = 0; //HardCoffee в Оранже только магазин
			else    i = drand(3);
			switch (i)
			{
				case 0:
					pchar.GenQuest.EncGirl.FatherNom = StringFromKey("Rapers_61");
					pchar.GenQuest.EncGirl.FatherGen = StringFromKey("Rapers_62");
					pchar.GenQuest.EncGirl.Father = "store_keeper";
				break;
				case 1:
					pchar.GenQuest.EncGirl.FatherNom = StringFromKey("Rapers_63");
					pchar.GenQuest.EncGirl.FatherGen = StringFromKey("Rapers_64");
					pchar.GenQuest.EncGirl.Father = "portman_keeper";
				break;
				case 2:
					pchar.GenQuest.EncGirl.FatherNom = StringFromKey("Rapers_65");
					pchar.GenQuest.EncGirl.FatherGen = StringFromKey("Rapers_66");
					pchar.GenQuest.EncGirl.Father = "fort_keeper";
				break;
				case 3:
					pchar.GenQuest.EncGirl.FatherNom = StringFromKey("Rapers_67");
					pchar.GenQuest.EncGirl.FatherGen = StringFromKey("Rapers_68");
					pchar.GenQuest.EncGirl.Father = "shipyard_keeper";
				break;
			}
			dialog.text = StringFromKey("Rapers_69", pchar.GenQuest.EncGirl.FatherNom, XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("Rapers_70");
			link.l1.go = "Node_12";
			pchar.GenQuest.EncGirl = "toParents";
		break;

		case "Node_12":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);
			pchar.quest.LandEnc_RapersBadExit.over = "yes";
			ChangeCharacterReputation(pchar, 5);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			for (i = 1; i <= 3; i++)
			{
				iTemp = GetCharacterIndex("GangMan_" + i);
				if (iTemp < 0) continue;
				sld = &characters[iTemp];
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, true);
				if (i == 1) LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", -1.0);
				else LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
				sld.lifeDay = 0;
			}
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_Saved");
		break;

		case "Node_8":
			dialog.text = StringFromKey("Rapers_71");
			link.l1 = StringFromKey("Rapers_72");
			link.l1.go = "Node_9";
		break;

		case "Node_9":
			if (drand(1) == 0)
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_NICK;
			}
			else
			{
				pchar.GenQuest.EncGirl.PirateName1 = "l" + rand(GetNamesCount(NAMETYPE_VIP) - 1);
				pchar.GenQuest.EncGirl.PirateIdx = NAMETYPE_VIP;
			}
			pchar.GenQuest.EncGirl.PirateName2 = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			switch (drand(4))
			{
				case 0:
					sTemp = StringFromKey("Rapers_73");
				break;
				case 1:
					sTemp = StringFromKey("Rapers_74");
				break;
				case 2:
					sTemp = StringFromKey("Rapers_75");
				break;
				case 3:
					sTemp = StringFromKey("Rapers_76");
				break;
				case 4:
					sTemp = StringFromKey("Rapers_77");
				break;
			}
			dialog.text = StringFromKey("Rapers_78", GetName(pchar.GenQuest.EncGirl.PirateIdx, pchar.GenQuest.EncGirl.PirateName1, NAME_GEN), GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.PirateName2, NAME_NOM), sTemp, GetName(pchar.GenQuest.EncGirl.PirateIdx, pchar.GenQuest.EncGirl.PirateName1, NAME_NOM));
			link.l1 = StringFromKey("Rapers_79", pchar);
			link.l1.go = "Node_10";
		break;

		case "Node_10":
			dialog.text = StringFromKey("Rapers_80");
			link.l1 = StringFromKey("Rapers_81");
			link.l1.go = "Node_11";
		break;

		case "Node_11":
			pchar.GenQuest.EncGirl = "RapersTreasure";
			dialog.text = StringFromKey("Rapers_82", pchar);
			link.l1 = StringFromKey("Rapers_83");
			link.l1.go = "exit_fight";
		break;

		case "EncGirl_Berglar":
			dialog.text = StringFromKey("Rapers_84", pchar);
			link.l1 = StringFromKey("Rapers_85");
			link.l1.go = "EncGirl_Berglar1";
		break;

		case "EncGirl_Berglar1":
			dialog.text = StringFromKey("Rapers_86", pchar);
			link.l1 = StringFromKey("Rapers_87");
			link.l1.go = "EncGirl_Berglar2";
		break;

		case "EncGirl_Berglar2":
			pchar.GenQuest.EncGirl.BerglarSum = makeint(sti(pchar.money) / 5) + 5000;
			if (sti(pchar.GenQuest.EncGirl.BerglarSum) > 250000) pchar.GenQuest.EncGirl.BerglarSum = 220000 + rand(30000);
			if (sti(pchar.GenQuest.EncGirl.BerglarSum) > 0)
			{
				dialog.text = StringFromKey("Rapers_88", sti(pchar.GenQuest.EncGirl.BerglarSum));
				if (sti(pchar.money) >= sti(pchar.GenQuest.EncGirl.BerglarSum))
				{
					link.l1 = StringFromKey("Rapers_89");
					link.l1.go = "EncGirl_Berglar3";
				}
				link.l2 = StringFromKey("Rapers_90");
				link.l2.go = "EncGirl_Berglar4";
			}
			else
			{
				dialog.text = StringFromKey("Rapers_91");
				link.l1 = StringFromKey("Rapers_92");
				link.l1.go = "EncGirl_Berglar3_1";
				link.l2 = StringFromKey("Rapers_93");
				link.l2.go = "EncGirl_Berglar4";
			}
		break;

		case "EncGirl_Berglar3":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.BerglarSum)));
			dialog.text = StringFromKey("Rapers_94");
			link.l1 = StringFromKey("Rapers_95");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoom");
		break;

		case "EncGirl_Berglar3_1":
			dialog.text = StringFromKey("Rapers_96", pchar);
			link.l1 = StringFromKey("Rapers_97", pchar);
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_outRoomRaped");
		break;

		case "EncGirl_Berglar4":
			dialog.text = StringFromKey("Rapers_98", pchar);
			link.l1 = StringFromKey("Rapers_99");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirlFack_fight");
		break;

		case "Node_2":
			dialog.text = StringFromKey("Rapers_100", pchar);
			Link.l1 = StringFromKey("Rapers_101");
			Link.l1.go = "Exit_Fight";
		break;

		case "OnceAgain":
			Diag.TempNode = "OnceAgain";
			dialog.text = StringFromKey("Rapers_102", pchar);
			Link.l1 = StringFromKey("Rapers_103");
			Link.l1.go = "Exit_NoFight";
			Link.l2 = StringFromKey("Rapers_104");
			Link.l2.go = "Node_2";
		break;
	}
}

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i, iRnd;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);
	//HardCoffee фиксы преждевременной смены локации, когда гг сопровождает блудницу домой -->
	chrDisableReloadToLocation = false; //до диалога был повешен лок на локацию для того, чтобы гг не убежал, когда к нему бежит нпс
	//снимаем проверку на боевой режим. Проверка вешается, когда гг заходит на локацию назначения и ждёт бегущую к нему нпс
	DelEventHandler("frame", "EncGirlFightMode");
	// 	<--
	switch (Dialog.CurrentNode)
	{
		case "exit_1":
			AddDialogExitQuest("LandEnc_RapersTalk");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "exit":
			if (CheckAttribute(NPChar, "QuestFollower"))
				LAi_ActorFollowEverywhere(npchar, "", -1);
			else
				LAi_SetCitizenTypeNoGroup(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "exit_stay":
			TurnNPCToPcharInit(NPChar);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Begin_1":
			LAi_RemoveCheckMinHP(npchar);
			for (i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = StringFromKey("RapersGirl_3", RandPhraseSimple(
						StringFromKey("RapersGirl_1", pchar),
						StringFromKey("RapersGirl_2", pchar)));
			link.l1 = StringFromKey("RapersGirl_9", LinkRandPhrase(
						StringFromKey("RapersGirl_4"),
						StringFromKey("RapersGirl_5"),
						StringFromKey("RapersGirl_8", RandPhraseSimple(
								StringFromKey("RapersGirl_6"),
								StringFromKey("RapersGirl_7")))));
			link.l1.go = "Begin_11";
		break;

		case "Begin_2":
			LAi_RemoveCheckMinHP(NPChar);
			for (i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = StringFromKey("RapersGirl_12", RandPhraseSimple(
						StringFromKey("RapersGirl_10", pchar),
						StringFromKey("RapersGirl_11", pchar)));
			link.l1 = StringFromKey("RapersGirl_18", LinkRandPhrase(
						StringFromKey("RapersGirl_13"),
						StringFromKey("RapersGirl_14"),
						StringFromKey("RapersGirl_17", RandPhraseSimple(
								StringFromKey("RapersGirl_15"),
								StringFromKey("RapersGirl_16")))));
			link.l1.go = "Begin_21";
		break;

		case "Begin_3":
			LAi_RemoveCheckMinHP(NPChar);
			for (i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = StringFromKey("RapersGirl_19", pchar);
			link.l1 = StringFromKey("RapersGirl_25", LinkRandPhrase(
						StringFromKey("RapersGirl_20"),
						StringFromKey("RapersGirl_21"),
						StringFromKey("RapersGirl_24", RandPhraseSimple(
								StringFromKey("RapersGirl_22"),
								StringFromKey("RapersGirl_23")))));
			link.l1.go = "Begin_31";
		break;

		case "Begin_11":
			dialog.text = StringFromKey("RapersGirl_28", RandPhraseSimple(
						StringFromKey("RapersGirl_26"),
						StringFromKey("RapersGirl_27")));
			link.l1 = StringFromKey("RapersGirl_29", pchar);
			link.l1.go = "exit_1";
		break;

		case "Begin_21":
			dialog.text = StringFromKey("RapersGirl_32", RandPhraseSimple(
						StringFromKey("RapersGirl_30", pchar),
						StringFromKey("RapersGirl_31", pchar)));
			link.l1 = StringFromKey("RapersGirl_33", pchar);
			link.l1.go = "exit_1";
		break;

		case "Begin_31":
			dialog.text = StringFromKey("RapersGirl_34");
			link.l1 = StringFromKey("RapersGirl_35", pchar);
			link.l1.go = "exit_1";
		break;

		case "First time":
			LAi_RemoveCheckMinHP(npchar);
			for (i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_type_actor_Reset(sld);
			}
			dialog.text = StringFromKey("RapersGirl_39", LinkRandPhrase(
						StringFromKey("RapersGirl_36"),
						StringFromKey("RapersGirl_37", pchar),
						StringFromKey("RapersGirl_38")));
			Link.l1 = StringFromKey("RapersGirl_43", LinkRandPhrase(
						StringFromKey("RapersGirl_40"),
						StringFromKey("RapersGirl_41"),
						StringFromKey("RapersGirl_42")));
			Link.l1.go = "Node_2";
		break;

		case "Node_2":
			dialog.text = StringFromKey("RapersGirl_47", LinkRandPhrase(
						StringFromKey("RapersGirl_44"),
						StringFromKey("RapersGirl_45"),
						StringFromKey("RapersGirl_46")));
			Link.l1 = StringFromKey("RapersGirl_48");
			Link.l1.go = "exit_1";
		break;

		case "ThanksForHelp":
			if (pchar.GenQuest.EncGirl == "Begin_11")
			{
				if (rand(1))
				{
					dialog.text = StringFromKey("RapersGirl_51", RandPhraseSimple(
								StringFromKey("RapersGirl_49", pchar),
								StringFromKey("RapersGirl_50")));
					link.l1 = StringFromKey("RapersGirl_52", pchar);
					link.l1.go = "Node_11";
				}
				else
				{
					dialog.text = StringFromKey("RapersGirl_53", pchar);
					link.l1 = StringFromKey("RapersGirl_54", pchar);
					link.l1.go = "Node_12";
				}
			}
			if (pchar.GenQuest.EncGirl == "Begin_22")
			{
				if (rand(1))
				{
					dialog.text = StringFromKey("RapersGirl_55", pchar);
					link.l1 = StringFromKey("RapersGirl_56", pchar);
					link.l1.go = "Node_12";
				}
				else
				{
					dialog.text = StringFromKey("RapersGirl_57");
					link.l1 = StringFromKey("RapersGirl_58");
					link.l1.go = "Node_22";
				}
			}
			if (pchar.GenQuest.EncGirl == "Begin_33")
			{
				dialog.text = StringFromKey("RapersGirl_59", pchar);
				link.l1 = StringFromKey("RapersGirl_60");
				link.l1.go = "Node_31";
			}
		break;

		case "Node_11":
			Diag.TempNode = "Node_1Next";
			addMoneyToCharacter(pchar, makeint((sti(pchar.rank)) * 25 + frand(2) * 500));
			dialog.text = StringFromKey("RapersGirl_61", pchar);
			link.l1 = StringFromKey("RapersGirl_62");
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "close";
			pchar.GenQuest.EncGirl.Saved_CangGirl = true;
			Diag.CurrentNode = Diag.TempNode;
		break;

		case "Node_12":
			dialog.text = StringFromKey("RapersGirl_63", pchar, XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("RapersGirl_66", RandPhraseSimple(
						StringFromKey("RapersGirl_64"),
						StringFromKey("RapersGirl_65")));
			link.l1.go = "Node_121Next";
			link.l2 = StringFromKey("RapersGirl_67");
			link.l2.go = "Node_3End";
		break;

		case "Node_22":
			dialog.text = StringFromKey("RapersGirl_68", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("RapersGirl_69");
			link.l1.go = "Node_122Next";
			link.l2 = StringFromKey("RapersGirl_70", pchar);
			link.l2.go = "Node_3End";
		break;

		case "Node_31":
			dialog.text = StringFromKey("RapersGirl_71");
			link.l1 = StringFromKey("RapersGirl_72");
			link.l1.go = "Node_32";
			link.l2 = StringFromKey("RapersGirl_73", pchar);
			link.l2.go = "Node_3End";
		break;

		case "Node_32":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = StringFromKey("RapersGirl_74", pchar.GenQuest.EncGirl.sLoverId, XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("RapersGirl_75");
			link.l1.go = "Node_12Next";
		break;

		case "Node_12Next":
			DeleteAttribute(pchar, "quest.LandEnc_RapersBadExit");
			Diag.TempNode = "Node_12End";
			Diag.CurrentNode = Diag.TempNode;
			pchar.GenQuest.EncGirl = "FindLover";
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "Node_121Next":
			DeleteAttribute(pchar, "quest.LandEnc_RapersBadExit");
			Diag.TempNode = "Node_253";
			pchar.GenQuest.EncGirl = "FindCoins";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "Node_122Next":
			DeleteAttribute(pchar, "quest.LandEnc_RapersBadExit");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.GenQuest.EncGirl.MeetSoldiers = 1;
			Diag.CurrentNode = Diag.TempNode;
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "Node_12End":
			Diag.TempNode = "Node_12End";
			dialog.text = StringFromKey("RapersGirl_78", RandPhraseSimple(
						StringFromKey("RapersGirl_76", pchar),
						StringFromKey("RapersGirl_77")));
			link.l1 = StringFromKey("RapersGirl_81", RandPhraseSimple(
						StringFromKey("RapersGirl_79"),
						StringFromKey("RapersGirl_80")));
			link.l1.go = "exit";
		break;

		case "Node_1Next":
			dialog.text = StringFromKey("RapersGirl_84", RandPhraseSimple(
						StringFromKey("RapersGirl_82", pchar),
						StringFromKey("RapersGirl_83", pchar)));
			link.l1 = StringFromKey("RapersGirl_87", RandPhraseSimple(
						StringFromKey("RapersGirl_85"),
						StringFromKey("RapersGirl_86")));
			link.l1.go = "Node_GoodEnd";
			link.l2 = StringFromKey("RapersGirl_88");
			link.l2.go = "Node_13";
		break;

		case "Node_3End":
			Diag.TempNode = "Node_3Final";
			EncGiglFleeAway(npchar, true);
			pchar.GenQuest.EncGirl = "close";
			pchar.GenQuest.EncGirl.Saved_CangGirl = true;
			ChangeCharacterReputation(pchar, -3);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Node_3Final":
			Diag.TempNode = "Node_3Final";
			dialog.text = StringFromKey("RapersGirl_91", RandPhraseSimple(
						StringFromKey("RapersGirl_89"),
						StringFromKey("RapersGirl_90")));
			link.l1 = StringFromKey("RapersGirl_94", RandPhraseSimple(
						StringFromKey("RapersGirl_92"),
						StringFromKey("RapersGirl_93")));
			link.l1.go = "exit";
		break;

		case "Node_13":
			pchar.GenQuest.EncGirl = "Begin_11";
			i = sti(pchar.GenQuest.EncGirl.variant);
			switch (i)
			{
				case 0:
					if (rand(1))
					{
						dialog.text = StringFromKey("RapersGirl_95");
						link.l1 = StringFromKey("RapersGirl_96", pchar);
						link.l1.go = "Node_GoodEnd";
					}
					else
					{
						dialog.text = StringFromKey("RapersGirl_97");
						link.l1 = StringFromKey("RapersGirl_98");
						link.l1.go = "Node_GoodEnd";
					}
				break;
				case 1:
					dialog.text = StringFromKey("RapersGirl_99");
					link.l1 = StringFromKey("RapersGirl_100");
					link.l1.go = "Node_131";
				break;
				case 2:
					dialog.text = StringFromKey("RapersGirl_101");
					link.l1 = StringFromKey("RapersGirl_102");
					link.l1.go = "Node_132";
				break;
			}
		break;

		case "Node_131":
			pchar.GenQuest.EncGirl.SmallCoins = rand(25) + 20;
			pchar.GenQuest.EncGirl.BigCoins = rand(15) + 5;
			dialog.text = StringFromKey("RapersGirl_103", sti(pchar.GenQuest.EncGirl.BigCoins), sti(pchar.GenQuest.EncGirl.SmallCoins));
			link.l1 = StringFromKey("RapersGirl_104");
			link.l1.go = "Node_131End";
			link.l2 = StringFromKey("RapersGirl_105");
			link.l2.go = "Node_133";
		break;

		case "Node_131End":
			EncGirlBecameCitizen(npchar, "close");
			ChangeCharacterReputation(pchar, -2);
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_132":
			pchar.GenQuest.EncGirl.mapOwner = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = StringFromKey("RapersGirl_106", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_PRE));
			link.l1 = StringFromKey("RapersGirl_107", pchar);
			link.l1.go = "Node_132_1";
		break;

		case "Node_132_1":
			dialog.text = StringFromKey("RapersGirl_108", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM));
			link.l1 = StringFromKey("RapersGirl_109");
			link.l1.go = "Node_132_2";
		break;

		case "Node_132_2":
			dialog.text = StringFromKey("RapersGirl_110");
			link.l1 = StringFromKey("RapersGirl_111");
			link.l1.go = "Node_132_2End";
			if (GetCharacterItem(pchar, "map_full") == 0)
			{
				link.l2 = StringFromKey("RapersGirl_112");
				link.l2.go = "Node_132_3";
			}
			link.l3 = StringFromKey("RapersGirl_113");
			link.l3.go = "Node_132_8";
		break;

		case "Node_132_2End":
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			pchar.GenQuest.EncGirl.Saved_CangGirl = true;
			EncGiglFleeAway(npchar, true);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_132_3":
			dialog.text = StringFromKey("RapersGirl_114");
			link.l1 = StringFromKey("RapersGirl_115");
			link.l1.go = "Node_132_4";
		break;

		case "Node_132_4":
			i = 20000 + 500 * sti(pchar.rank);
			pchar.GenQuest.EncGirl.mapPrice = i;
			dialog.text = StringFromKey("RapersGirl_116");
			link.l1 = StringFromKey("RapersGirl_117", FindMoneyString(i));
			link.l1.go = "Node_132_5";
		break;

		case "Node_132_5":
			if ((GetSummonSkillFromName(pchar, SKILL_COMMERCE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)) > (rand(220) + 100) && (makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
			{
				PlayerRPGCheck_Skill_NotifyPass(SKILL_COMMERCE);
				PlayerRPGCheck_Skill_NotifyPass(SKILL_LEADERSHIP);
				PlayerRPGCheck_Skill_NotifyPass(SKILL_FORTUNE);
				dialog.text = StringFromKey("RapersGirl_118", pchar);
				link.l1 = StringFromKey("RapersGirl_119");
				link.l1.go = "Node_132_6";
			}
			else
			{
				if ((makeint(pchar.money) >= sti(pchar.GenQuest.EncGirl.mapPrice)))
				{
					PlayerRPGCheck_Skill_NotifyFail(SKILL_COMMERCE, true);
					PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
					PlayerRPGCheck_Skill_NotifyFail(SKILL_FORTUNE, false);
				}
				dialog.text = StringFromKey("RapersGirl_120", pchar);
				link.l1 = StringFromKey("RapersGirl_121");
				link.l1.go = "Node_132_2End";
			}
		break;

		case "Node_132_6":
			AddMoneyToCharacter(pchar, -makeint(sti(pchar.GenQuest.EncGirl.mapPrice)));
			GiveItem2Character(pchar, "map_full");
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "close";
			pchar.GenQuest.EncGirl.Saved_CangGirl = true;
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_132_8":
			dialog.text = StringFromKey("RapersGirl_122");
			link.l1 = StringFromKey("RapersGirl_123");
			link.l1.go = "Node_132_9";
		break;

		case "Node_132_9":
			dialog.text = StringFromKey("RapersGirl_124", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("RapersGirl_125");
			link.l1.go = "Node_132_10";
		break;

		case "Node_132_10":
			EncGirl_GenQuest_GetChestPlaceName();
			dialog.text = StringFromKey("RapersGirl_126", XI_ConvertString(pchar.GenQuest.EncGirl.islandId + "Acc"), XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			link.l1 = StringFromKey("RapersGirl_127");
			link.l1.go = "Node_132_11";
		break;

		case "Node_132_11":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "4");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sPirateName", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sTreasureLoc", XI_ConvertString(pchar.GenQuest.EncGirl.islandId));
			AddQuestUserData("JungleGirl", "sShore", XI_ConvertString(pchar.GenQuest.EncGirl.shoreId + "Gen"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.quest.EncGirl_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_Death.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_Death.function = "EncGirl_Death";
			pchar.quest.EncGirl_FindChest.win_condition.l1 = "location";
			pchar.quest.EncGirl_FindChest.win_condition.l1.location = pchar.GenQuest.EncGirl.placeId;
			pchar.quest.EncGirl_FindChest.function = "EncGirl_FindChest";
			SetFunctionExitFromLocationCondition("EncGirl_AddPassenger", pchar.location, false);
			SetFunctionLocationCondition("EncGirl_DialogAtShore", pchar.GenQuest.EncGirl.shoreId, false);
			Diag.TempNode = "Node_12End";
			pchar.GenQuest.EncGirl = "GetChest";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_132_11_1":
			dialog.text = StringFromKey("RapersGirl_128");
			link.l1 = StringFromKey("RapersGirl_129");
			link.l1.go = "exit";
			Diag.TempNode = "Node_132_11_2";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;

		case "Node_132_11_2":
			Diag.TempNode = "Node_132_11_2";
			dialog.text = StringFromKey("RapersGirl_130");
			link.l1 = StringFromKey("RapersGirl_131");
			link.l1.go = "exit";
		break;

		case "Node_132_12":
			DeleteAttribute(NPChar, "QuestFollower");
			dialog.text = StringFromKey("RapersGirl_132");
			link.l1 = StringFromKey("RapersGirl_133");
			link.l1.go = "Node_132_13";
		break;

		case "Node_132_13":
			dialog.text = StringFromKey("RapersGirl_134");
			link.l1 = StringFromKey("RapersGirl_135");
			link.l1.go = "Node_132_15";
		break;

		case "Node_132_15":
			dialog.text = StringFromKey("RapersGirl_136");
			link.l1 = StringFromKey("RapersGirl_137", pchar);
			link.l1.go = "Node_132_16";
		break;

		case "Node_132_16":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			PChar.quest.EncGirl_DialogAtShore.over = "yes"; // Лесник (Slayer). Снял прерывание, если не с той бухты зашел
			LAi_LocationDisableMonstersGen(pchar.location, false);
			LogSound_WithNotify(StringFromKey("InfoMessages_197"), "Important_item", "ICollection");
			TakeNItems(pchar, "incas_collection", 1 + drand(1));
			TakeNItems(pchar, "chest", 2 + drand(6));
			TakeNItems(pchar, "jewelry1", 30 + drand(15));
			TakeNItems(pchar, "jewelry2", 30 + drand(15));
			TakeNItems(pchar, "jewelry3", 30 + drand(15));
			TakeNItems(pchar, "jewelry11", 30 + drand(15));
			TakeNItems(pchar, "jewelry5", 30 + rand(10));
			TakeNItems(pchar, "jewelry15", 10 + rand(10));
			TakeNItems(pchar, "jewelry18", 20 + rand(10));
			TakeNItems(pchar, "jewelry14", 30 + rand(10));
			TakeNItems(pchar, "jewelry7", 50 + rand(20));
			AddQuestRecord("JungleGirl", "6");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("JungleGirl", "sPirateName", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			pchar.GenQuest.EncGirl = "ChestGetted";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_town";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1 = "NPC_Death";
			pchar.quest.EncGirl_DeathAgain.win_condition.l1.character = npchar.id;
			pchar.quest.EncGirl_DeathAgain.function = "EncGirl_DeathAgain";
			Diag.TempNode = "Node_132_17";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
		break;

		case "Node_132_17":
			Diag.TempNode = "Node_132_17";
			dialog.text = StringFromKey("RapersGirl_138");
			link.l1 = StringFromKey("RapersGirl_139", pchar);
			link.l1.go = "exit";
		break;

		case "Node_132_18":
			dialog.text = StringFromKey("RapersGirl_140");
			link.l1 = StringFromKey("RapersGirl_141");
			link.l1.go = "Node_132_19";
		break;

		case "Node_132_19":
			dialog.text = StringFromKey("RapersGirl_142");
			link.l1 = StringFromKey("RapersGirl_143");
			link.l1.go = "Node_132_20";
		break;

		case "Node_132_20":
			dialog.text = StringFromKey("RapersGirl_144");
			link.l1 = StringFromKey("RapersGirl_145", pchar);
			link.l1.go = "Node_132_21";
		break;

		case "Node_132_21":
		//chrDisableReloadToLocation = false; //HardCoffee
			RemovePassenger(pchar, npchar);
			AddItemLog(pchar, pchar.GenQuest.EncGirl.item, "1", StringFromKey("InfoMessages_135", GetItemName(pchar.GenQuest.EncGirl.item)), "Took_item");
			AddQuestRecord("JungleGirl", "8");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
			EncGiglFleeAway(npchar, true);
			pchar.quest.EncGirl_EnterToSea.over = "yes";    // Лесник (Slayer). Снял прерывание, если не с той бухты зашёл
			PChar.quest.EncGirl_DialogAtShore.over = "yes";    // Лесник (Slayer). Снял прерывание, если не с той бухты зашёл
		break;

		case "Node_133":
			dialog.text = StringFromKey("RapersGirl_146");
			link.l1 = StringFromKey("RapersGirl_147", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1.go = "Node_133_1";
			if (sti(pchar.money) >= 15000)
			{
				link.l2 = StringFromKey("RapersGirl_148");
				link.l2.go = "Node_135";
			}
		break;

		case "Node_133_1":
			pchar.GenQuest.EncGirl = "GetCoins";
			pchar.quest.EncGirl_Coins.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_Coins.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_Coins.function = "EncGirl_toChurch";
			pchar.quest.EncGirl_GetCoins.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			pchar.quest.EncGirl_GetCoins.function = "EncGirl_GenQuest_GetCoins";
			LAi_SetActorType(npchar);
			if (CheckAttribute(loadedlocation, "locators.reload.reload7_back"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload7_back", "none", "", "", "OpenTheDoors", 30.0);
			}
			else
			{
				sTemp = LAi_FindNearestFreeLocator2Pchar("reload");// Лесник (Slayer). Девица убегает, если ГГ сказал ждать в цервки
				LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "OpenTheDoors", 30.0);
			}
			Diag.TempNode = "Node_134";
			Diag.CurrentNode = Diag.TempNode;
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "1");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sText1", sti(pchar.GenQuest.EncGirl.BigCoins));
			AddQuestUserData("JungleGirl", "sText2", sti(pchar.GenQuest.EncGirl.SmallCoins));
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_134":
			dialog.text = StringFromKey("RapersGirl_151", RandPhraseSimple(
						StringFromKey("RapersGirl_149", pchar),
						StringFromKey("RapersGirl_150")));
			if (GetCharacterItem(pchar, "jewelry11") >= sti(pchar.GenQuest.EncGirl.BigCoins) && GetCharacterItem(pchar, "jewelry12") >= sti(pchar.GenQuest.EncGirl.SmallCoins))
			{
				link.l1 = StringFromKey("RapersGirl_152");
				link.l1.go = "Node_134_1";
			}
			else
			{
				link.l1 = StringFromKey("RapersGirl_153");
				link.l1.go = "Node_134_2";
			}
		break;

		case "Node_134_1":
			TakeNItems(pchar, "jewelry11", -sti(pchar.GenQuest.EncGirl.BigCoins));
			TakeNItems(pchar, "jewelry12", -sti(pchar.GenQuest.EncGirl.SmallCoins));
			pchar.quest.EncGirl_GetCoins.over = "yes";
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			dialog.text = StringFromKey("RapersGirl_154", pchar);
			link.l1 = StringFromKey("RapersGirl_155", pchar);
			link.l1.go = "Node_134_End";
		break;

		case "Node_134_2":
			dialog.text = StringFromKey("RapersGirl_156", pchar);
			link.l1 = StringFromKey("RapersGirl_157");
			link.l1.go = "exit_stay";
		break;

		case "Node_134_End":
			AddItemLog(pchar, pchar.GenQuest.EncGirl.item, "1", StringFromKey("InfoMessages_135", GetItemName(pchar.GenQuest.EncGirl.item)), "Took_item"); //items_update, TODO: как правило, это никакой не амулет
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "2");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			EncGirlBecameCitizen(npchar, "revard");
			EncGiglFleeAway(npchar, true);
			DialogExit();
		break;

		case "Node_135":
			AddMoneyToCharacter(pchar, -15000);
			ChangeCharacterReputation(pchar, 10);
			dialog.text = StringFromKey("RapersGirl_158", pchar);
			link.l1 = StringFromKey("RapersGirl_159");
			link.l1.go = "Node_GoodEnd";
		break;

		case "ThanksForSave":
			if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga" || npchar.city == "Providencia")
			{
				if (CheckAttribute(pchar, "GenQuest.EncGirl.Horse"))
				{
					iRnd = 2;
					pchar.GenQuest.EncGirl.BrothelCity = true;
				}
				else
				{
					iRnd = 1;
				}
			}
			else
			{
				iRnd = 1;
			}
			switch (rand(iRnd))
			{
				case 0:
					dialog.text = StringFromKey("RapersGirl_162", RandPhraseSimple(
								StringFromKey("RapersGirl_160"),
								StringFromKey("RapersGirl_161")));
					link.l1 = StringFromKey("RapersGirl_163");
					link.l1.go = "Node_200";
				break;
				case 1:
					dialog.text = StringFromKey("RapersGirl_164", pchar);
					link.l1 = StringFromKey("RapersGirl_165");
					link.l1.go = "Node_210";
					link.l2 = StringFromKey("RapersGirl_166", pchar);
					link.l2.go = "Node_211";
				break;
				case 2:
					dialog.text = StringFromKey("RapersGirl_167");
					link.l1 = StringFromKey("RapersGirl_168");
					link.l1.go = "Node_220";
				break;
			}
		break;

		case "Node_200":
			if (rand(1))
			{
				dialog.text = StringFromKey("RapersGirl_169");
				link.l1 = StringFromKey("RapersGirl_170");
				link.l1.go = "Node_200End";
				link.l2 = StringFromKey("RapersGirl_171");
				link.l2.go = "Node_201";
			}
			else
			{
				dialog.text = StringFromKey("RapersGirl_172", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
				link.l1 = StringFromKey("RapersGirl_173");
				link.l1.go = "Node_200End";
				link.l2 = StringFromKey("RapersGirl_176", RandPhraseSimple(
							StringFromKey("RapersGirl_174"),
							StringFromKey("RapersGirl_175")));
				link.l2.go = "Node_121Next";
			}
		break;

		case "Node_201":
			dialog.text = StringFromKey("RapersGirl_177");
			link.l1 = StringFromKey("RapersGirl_178");
			link.l1.go = "Node_202";
		break;

		case "Node_202":
			dialog.text = StringFromKey("RapersGirl_179");
			link.l1 = StringFromKey("RapersGirl_180");
			link.l1.go = "Node_203";
		break;

		case "Node_203":
			dialog.text = StringFromKey("RapersGirl_181");
			link.l1 = StringFromKey("RapersGirl_182");
			link.l1.go = "Node_200End";
			link.l2 = StringFromKey("RapersGirl_183");
			link.l2.go = "Node_204";
		break;

		case "Node_204":
			dialog.text = StringFromKey("RapersGirl_184");
			link.l1 = StringFromKey("RapersGirl_185");
			link.l1.go = "Node_205";
		break;

		case "Node_205":
			Diag.TempNode = "Node_206";
			EncGirl_GenerateChest(npchar);
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "Node_206":
			dialog.text = StringFromKey("RapersGirl_186");
			link.l1 = StringFromKey("RapersGirl_187");
			link.l1.go = "exit";
		break;

		case "Node_207":
			DeleteAttribute(NPChar, "QuestFollower");
			dialog.text = StringFromKey("RapersGirl_188");
			link.l1 = StringFromKey("RapersGirl_189");
			link.l1.go = "Node_208";
		break;

		case "Node_208":
			dialog.text = StringFromKey("RapersGirl_190", pchar);
			link.l1 = StringFromKey("RapersGirl_191");
			link.l1.go = "Node_209";
		break;

		case "Node_209":
			LAi_LocationDisableMonstersGen(pchar.location, false);
			i = makeint(sti(pchar.GenQuest.EncGirl.price) * 0.01);
			TakeNItems(pchar, "jewelry17", i);
			PlaySound("Took_item");
			EncGiglFleeAway(npchar, false);
			pchar.quest.EncGirl_RapersExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_RapersExit.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_RapersExit.function = "EncGirl_MeetRapers";
			DialogExit();
		break;

		case "Node_200End": //Откупились от бандитов
			ChangeCharacterReputation(pchar, -3);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DeleteAttribute(pchar, "quest.LandEnc_RapersBadExit");
			EncGiglFleeAway(npchar, true);
			DialogExit();
		break;

		case "Node_210":
			dialog.text = StringFromKey("RapersGirl_192", pchar);
			link.l1 = StringFromKey("RapersGirl_193", pchar);
			link.l1.go = "Node_CloseEnd";
		break;

		case "Node_211":
			dialog.text = StringFromKey("RapersGirl_194", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("RapersGirl_195");
			link.l1.go = "Node_122Next";
			ChangeCharacterReputation(pchar, 1);
		break;

		case "Node_220":
			dialog.text = StringFromKey("RapersGirl_196", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("RapersGirl_197");
			link.l1.go = "Node_221";
			link.l2 = StringFromKey("RapersGirl_198");
			link.l2.go = "Node_222";
		break;

		case "Node_221":
			pchar.quest.EncGirl_DeathSimple.over = "yes";
			ChangeCharacterReputation(pchar, -2);
			EncGiglFleeAway(npchar, true);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_222":
			dialog.text = StringFromKey("RapersGirl_199");
			link.l1 = StringFromKey("RapersGirl_200");
			link.l1.go = "Node_223";
		break;

		case "Node_223":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_224":
			dialog.text = StringFromKey("RapersGirl_201", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("RapersGirl_204", RandPhraseSimple(
						StringFromKey("RapersGirl_202"),
						StringFromKey("RapersGirl_203")));
			link.l1.go = "exit";
		break;

		case "Node_225":
		//chrDisableReloadToLocation = false; //HardCoffee
			DeleteAttribute(NPChar, "QuestFollower");
			if (PChar.sex != "woman")
			{
				dialog.text = StringFromKey("RapersGirl_205");
				link.l1 = StringFromKey("RapersGirl_209", LinkRandPhrase(
							StringFromKey("RapersGirl_206"),
							StringFromKey("RapersGirl_207"),
							StringFromKey("RapersGirl_208")));
				link.l1.go = "Node_226";
				link.l2 = StringFromKey("RapersGirl_210");
				link.l2.go = "Node_227";
			}
			else
			{
				dialog.text = StringFromKey("RapersGirl_211");
				link.l1 = StringFromKey("RapersGirl_212");
				link.l1.go = "Node_226_1";
			}
		break;

		case "Node_226":
			ChangeCharacterReputation(pchar, -1);
			EncGiglFleeAway(npchar, true);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_226_1":
			ChangeCharacterReputation(pchar, 3);
			EncGiglFleeAway(npchar, true);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_227":
			pchar.GenQuest.EncGirl = "EncGirl_ToTavern";
			pchar.quest.EncGirl_inRoom.win_condition.l1 = "location";
			pchar.quest.EncGirl_inRoom.win_condition.l1.location = npchar.city + "_tavern_upstairs";
			pchar.quest.EncGirl_inRoom.function = "EncGirl_SpeakInRoom";
			//			chrDisableReloadToLocation = true;
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_228":
			LAi_LockFightMode(pchar, false);
			if (CheckAttribute(pchar, "GenQuest.EncGirl.Horse") && CheckAttribute(pchar, "GenQuest.EncGirl.BrothelCity") && sti(pchar.rank) > 15) // душещипательная история о невинной девочке попавшей в бордель
			{
				DeleteAttribute(pchar, "GenQuest.EncGirl.BrothelCity");
				dialog.text = StringFromKey("RapersGirl_213");
				link.l1 = StringFromKey("RapersGirl_214");
				link.l1.go = "Node_CloseEnd";
				link.l2 = StringFromKey("RapersGirl_215");
				link.l2.go = "Node_233";
			}
			else
			{
				dialog.text = StringFromKey("RapersGirl_216");
				link.l1 = StringFromKey("RapersGirl_217");
				link.l1.go = "Node_229"; // ГГ допрыгался - щас его попросту трахнут
				link.l2 = StringFromKey("RapersGirl_218");
				link.l2.go = "Node_230"; // Послал в пешее эротическое путешествие
			}
		break;

		case "Node_229":
			dialog.text = StringFromKey("RapersGirl_219");
			link.l1 = StringFromKey("RapersGirl_220");
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "EncGirl_facking";
			AddDialogExitQuest("PlaySex_1");
		break;

		case "Node_230":
			dialog.text = StringFromKey("RapersGirl_221");
			link.l1 = StringFromKey("RapersGirl_222");
			link.l1.go = "Node_231";
		break;

		case "Node_231":
			dialog.text = StringFromKey("RapersGirl_223");
			link.l1 = StringFromKey("RapersGirl_224");
			link.l1.go = "Node_231_1";
		break;

		case "Node_231_1":
			LAi_LockFightMode(pchar, true);
			ChangeCharacterReputation(pchar, 1);
			EncGiglFleeAway(npchar, false);
			DoQuestFunctionDelay("EncGirl_SetBerglar", 5.0); //TODO: каждый раз их запускать - бред
			DialogExit();
		break;

		case "Node_233":
			pchar.GenQuest.EncGirl.Parents_City = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			dialog.text = StringFromKey("RapersGirl_225", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			link.l1 = StringFromKey("RapersGirl_226");
			link.l1.go = "Node_234";
		break;

		case "Node_234":
			dialog.text = StringFromKey("RapersGirl_227");
			link.l1 = StringFromKey("RapersGirl_228");
			link.l1.go = "Node_235";
			link.l2 = StringFromKey("RapersGirl_229");
			link.l2.go = "Node_236";
			if (sti(pchar.money) >= 5000)
			{
				link.l3 = StringFromKey("RapersGirl_230");
				link.l3.go = "Node_237";
			}
		break;

		case "Node_235":
			dialog.text = StringFromKey("RapersGirl_231");
			link.l1 = StringFromKey("RapersGirl_232");
			link.l1.go = "Node_240";
		break;

		case "Node_240":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "20");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			AddQuestUserData("JungleGirl", "sBrothelCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city + "Gen"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			OfficersReaction("bad");
			//chrDisableReloadToLocation = false; //HardCoffee TODO: открывашка была повешена в начале диалога. Если после тестов всё будет норм - не забыть это убрать
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 3.0);
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveToParents.win_condition.l1.location = pchar.GenQuest.EncGirl.Parents_City + "_town";
			pchar.quest.EncGirl_DeliveToParents.function = "EncGirl_DeliveToParents";
			DialogExit();
		break;

		case "Node_236":
			dialog.text = StringFromKey("RapersGirl_233");
			link.l1 = StringFromKey("RapersGirl_234");
			link.l1.go = "Node_239";
		break;

		case "Node_239":
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "21");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			pchar.quest.EncGirl_GenerateBag.win_condition.l1 = "location";
			if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > rand(100))
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoomUp";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_Brothel_room";
			}
			else
			{
				pchar.GenQuest.EncGirl = "Bag_BrothelRoom";
				pchar.quest.EncGirl_GenerateBag.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_SecBrRoom";
			}
			pchar.quest.EncGirl_GenerateBag.function = "EncGirl_GenerateLeatherBag";

			pchar.quest.EncGirl_GetBagFail.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.EncGirl_GetBagFail.function = "EncGirl_GenQuest_GetBag";

			pchar.quest.EncGirl_ExitRoom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitRoom.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitRoom.function = "EncGirl_ExitTavernRoom";

			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;

		case "Node_240_1":
			pchar.quest.EncGirl_GetBagFail.over = "yes";
			dialog.text = StringFromKey("RapersGirl_235");
			if (CheckCharacterItem(pchar, "leather_bag"))
			{
				link.l1 = StringFromKey("RapersGirl_236");
				link.l1.go = "Node_241";
			}
			else
			{
				link.l1 = StringFromKey("RapersGirl_237", pchar);
				link.l1.go = "Node_242";
			}
		break;

		case "Node_241":
			TakeNItems(pchar, "leather_bag", -1);
			dialog.text = StringFromKey("RapersGirl_238", pchar);
			link.l1 = StringFromKey("RapersGirl_239");
			link.l1.go = "Node_243";
		break;

		case "Node_242":
			dialog.text = StringFromKey("RapersGirl_240");
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = StringFromKey("RapersGirl_241");
				link.l1.go = "Node_237";
			}
			link.l2 = StringFromKey("RapersGirl_242");
			link.l2.go = "Node_244";
		break;

		case "Node_243":
			EncGiglFleeAway(npchar, true);
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("", "а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, 1);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_244":
			EncGiglFleeAway(npchar, true);
			AddQuestRecord("JungleGirl", "23");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
			ChangeCharacterReputation(pchar, -5);
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_245":
			dialog.text = StringFromKey("RapersGirl_243");
			link.l1 = StringFromKey("RapersGirl_244", pchar);
			link.l1.go = "Node_246";
		break;

		case "Node_246":
			dialog.text = StringFromKey("RapersGirl_245");
			link.l1 = StringFromKey("RapersGirl_246");
			link.l1.go = "Node_247";
		//			link.l2 = "Ты действительно думаешь, что это необходимо?";
		//			link.l2.go = "Node_248"
		break;

		case "Node_247":
			EncGiglFleeAway(npchar, false);
			TakeNItems(pchar, pchar.GenQuest.EncGirl.item, 1);
			AddQuestRecord("JungleGirl", "24");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.Parents_City));
			CloseQuestHeader("JungleGirl");
			npchar.lifeDay = 0;
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_248":
		break;

		case "Node_237":
			dialog.text = StringFromKey("RapersGirl_247");
			if (makeint(pchar.money) >= 5000)
			{
				link.l1 = StringFromKey("RapersGirl_248");
				link.l1.go = "Node_237_1";
			}
			if (makeint(pchar.money) >= 25000)
			{
				link.l2 = StringFromKey("RapersGirl_249");
				link.l2.go = "Node_237_2";
			}
			if (makeint(pchar.money) >= 35000)
			{
				link.l3 = StringFromKey("RapersGirl_250");
				link.l3.go = "Node_237_3";
			}
		break;

		case "Node_237_1":
			AddMoneyToCharacter(pchar, -5000);
			ChangeCharacterReputation(pchar, -5);
			dialog.text = StringFromKey("RapersGirl_251", pchar);
			link.l1 = StringFromKey("RapersGirl_252");
			link.l1.go = "Node_238";
			pchar.GenQuest.EncGirl = "EncGirlFack_GetMoney";
		break;

		case "Node_237_2":
			AddMoneyToCharacter(pchar, -25000);
			ChangeCharacterReputation(pchar, 1);
			dialog.text = StringFromKey("RapersGirl_253", pchar);
			link.l1 = StringFromKey("RapersGirl_254");
			link.l1.go = "Node_238";
		break;

		case "Node_237_3":
			AddMoneyToCharacter(pchar, -35000);
			ChangeCharacterReputation(pchar, 2);
			dialog.text = StringFromKey("RapersGirl_255", pchar);
			link.l1 = StringFromKey("RapersGirl_256");
			link.l1.go = "Node_238";
		break;

		case "Node_238":
			EncGiglFleeAway(npchar, false);
			if (pchar.GenQuest.EncGirl == "EncGirlFack_GetMoney")
			{
				AddSimpleRumour(
							StringFromKey("RapersGirl_259", RandPhraseSimple(
									StringFromKey("RapersGirl_257"),
									StringFromKey("RapersGirl_258"))), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			DialogExit();
		break;

		case "Node_250":
			dialog.text = StringFromKey("RapersGirl_260");
			link.l1 = StringFromKey("RapersGirl_261", pchar);
			link.l1.go = "Node_251";
		break;

		case "Node_251":
			pchar.GenQuest.EncGirl.sLoverId = GenerateRandomName(sti(npchar.nation), "man");
			dialog.text = StringFromKey("RapersGirl_262", pchar.GenQuest.EncGirl.sLoverId, XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("RapersGirl_263");
			link.l1.go = "Node_252";
		break;

		case "Node_252":
			Diag.TempNode = "Node_253";
			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "9");
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherGen);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sLover", pchar.GenQuest.EncGirl.sLoverId);
			pchar.GenQuest.EncGirl.MeetSoldiers = 2;
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
		break;

		case "Node_253":
			dialog.text = StringFromKey("RapersGirl_264", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			link.l1 = StringFromKey("RapersGirl_267", RandPhraseSimple(
						StringFromKey("RapersGirl_265"),
						StringFromKey("RapersGirl_266")));
			link.l1.go = "exit";
		break;

		case "Node_260":
			DeleteAttribute(NPChar, "QuestFollower");
			if (rand(1))
			{
				dialog.text = StringFromKey("RapersGirl_270", RandPhraseSimple(
							StringFromKey("RapersGirl_268", pchar),
							StringFromKey("RapersGirl_269", pchar)));
				link.l1 = StringFromKey("RapersGirl_273", RandPhraseSimple(
							StringFromKey("RapersGirl_271"),
							StringFromKey("RapersGirl_272")));
				link.l1.go = "Node_GoodEnd";
				link.l2 = StringFromKey("RapersGirl_274");
				link.l2.go = "Node_13";
			}
			else
			{
				dialog.text = StringFromKey("RapersGirl_275", pchar);
				link.l1 = StringFromKey("RapersGirl_276", pchar);
				link.l1.go = "Node_261";
			}
		break;

		case "Node_261":
			dialog.text = StringFromKey("RapersGirl_277");
			link.l1 = StringFromKey("RapersGirl_278", pchar);
			link.l1.go = "Node_CloseEnd";
			link.l2 = StringFromKey("RapersGirl_279", pchar);
			link.l2.go = "Node_263";
		break;

		case "Node_263":
			Diag.TempNode = "Node_224";
			pchar.GenQuest.EncGirl = "HorseToTavern";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1 = "location";
			pchar.quest.EncGirl_DeliveBack.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
			pchar.quest.EncGirl_DeliveBack.function = "EncGirl_DeliveBack";
			Diag.CurrentNode = Diag.TempNode;
			AddDialogExitQuestFunction("EncGirl_GirlFollow");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "ThanksForHelp_1":
			Diag.TempNode = "ThanksAgain";
			if (makeint(Pchar.reputation) >= 80)
			{
				dialog.text = StringFromKey("RapersGirl_280");
				Link.l1 = StringFromKey("RapersGirl_281");
				Link.l1.go = "exit";
			}
			else
			{
				if (drand(1) == 0)
				{
					dialog.text = StringFromKey("RapersGirl_282", pchar);
					Link.l1 = StringFromKey("RapersGirl_283");
					Link.l1.go = "exit";
				}
				else
				{
					addMoneyToCharacter(Pchar, makeint(PChar.rank) * 100);
					dialog.text = StringFromKey("RapersGirl_284");
					Link.l1 = StringFromKey("RapersGirl_285");
					Link.l1.go = "exit";
				}
			}
		break;

		case "ThanksAgain":
			Diag.TempNode = "ThanksAgain";
			dialog.text = StringFromKey("RapersGirl_286", pchar);
			Link.l1 = StringFromKey("RapersGirl_287");
			Link.l1.go = "exit";
		break;

		case "Node_CloseEnd":
			EncGirlBecameCitizen(npchar, "close");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;

		case "Node_GoodEnd":
			EncGirlBecameCitizen(npchar, "revard");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;
	}
}

void EncGiglFleeAway(ref rChr, bool bRun) //HardCoffee
{
	string sTemp = "";
	float locx, locy, locz;
	GetCharacterPos(rChr, &locx, &locy, &locz);
	sTemp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
	if (sTemp == "") sTemp = LAi_FindNearestFreeLocator("reload1_back", locx, locy, locz);
	if (sTemp == "") LAi_SetCitizenType(rChr);
	else
	{
		LAi_SetActorType(rChr);
		if (bRun) LAi_ActorRunToLocation(rChr, "reload", sTemp, "none", "", "", "OpenTheDoors", 30.0);
		else LAi_ActorGoToLocation(rChr, "reload", sTemp, "none", "", "", "OpenTheDoors", 60.0);
	}
	rChr.lifeDay = "1";
	rChr.location = "";
	rChr.chr_ai.disableDlg = "1";
}

void EncGirlBecameCitizen(ref rChr, string sCondition)
{
	LAi_SetCitizenType(rChr);
	rChr.lifeDay = "1";
	rChr.location = "";

	//rChr.chr_ai.disableDlg = "1";
	rChr.Dialog.TempNode = "Node_12End";
	rChr.Dialog.CurrentNode = rChr.Dialog.TempNode;

	//sCondition == "close" не повышать репу и не давать слухи
	pchar.GenQuest.EncGirl = sCondition;
	pchar.GenQuest.EncGirl.Saved_CangGirl = true;
	pchar.quest.LandEnc_RapersBadExit.win_condition.l1 = "ExitFromLocation";
	pchar.quest.LandEnc_RapersBadExit.win_condition.l1.location = pchar.location;
	pchar.quest.LandEnc_RapersBadExit.win_condition = "LandEnc_RapersBadExit";
}

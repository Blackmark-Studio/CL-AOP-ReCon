void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
        
		case "First time":
			dialog.text = StringFromKey("LeBasque_dialog_1");
			link.l1 = StringFromKey("LeBasque_dialog_2");
			link.l1.go = "dialog_sneak";
			link.l2 = StringFromKey("LeBasque_dialog_3");
			link.l2.go = "dialog_fortune";
		break;

		case "dialog_sneak":
			AddCharacterExpToSkill(PChar, SKILL_Fortune, 50);
			notification(StringFromKey("InfoMessages_225"), SKILL_FORTUNE);
			dialog.text = StringFromKey("LeBasque_dialog_4");
			link.l1 = StringFromKey("LeBasque_dialog_5");
			link.l1.go = "dialog_1";
		break;

		case "dialog_fortune":
			AddCharacterExpToSkill(PChar, SKILL_SNEAK, 50);
			notification(StringFromKey("InfoMessages_225"), SKILL_SNEAK);
			dialog.text = StringFromKey("LeBasque_dialog_6");
			link.l1 = StringFromKey("LeBasque_dialog_7");
			link.l1.go = "dialog_1";
		break;

		case "dialog_1":
			dialog.text = StringFromKey("LeBasque_dialog_8");
			link.l1 = StringFromKey("LeBasque_dialog_9");
			link.l1.go = "dialog_2";
		break;

		case "dialog_2":
			dialog.text = StringFromKey("LeBasque_dialog_10");
			link.l1 = StringFromKey("LeBasque_dialog_11");
			link.l1.go = "dialog_3";
		break;

		case "dialog_3":
			dialog.text = StringFromKey("LeBasque_dialog_12");
			link.l1 = StringFromKey("LeBasque_dialog_13");
			link.l1.go = "dialog_5";
		break;

		case "dialog_5":
			dialog.text = StringFromKey("LeBasque_dialog_14");
			link.l1 = "...";
			link.l1.go = "dialog_5_exit";
		break;

		case "dialog_5_exit":
			AddDialogExitQuest("Old_campfire_4");
			dialogexit();
		break;

		case "dialog_6":
			dialog.text = StringFromKey("LeBasque_dialog_15");
			link.l1 = "...";
			link.l1.go = "dialog_6_exit";
		break;

		case "dialog_6_exit":
			AddDialogExitQuest("Old_campfire_4_2");
			dialogexit();
		break;

		case "Hunting_huntsman_1":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = StringFromKey("LeBasque_dialog_16", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("LeBasque_dialog_17");
			link.l1.go = "Hunting_huntsman_2";
		break;

		case "Hunting_huntsman_2":
			GiveItem2Character(pchar, "recipe_dried_meat");
			LogSound_WithNotify(StringFromKey("InfoMessages_240", GetItemName("recipe_dried_meat"), 1), "Important_item", "Notebook_1");
			dialog.text = StringFromKey("LeBasque_dialog_18");
			link.l1 = StringFromKey("LeBasque_dialog_19");
			link.l1.go = "Hunting_huntsman_3";
		break;

		case "Hunting_huntsman_3":
			dialog.text = StringFromKey("LeBasque_dialog_20");
			link.l1 = StringFromKey("LeBasque_dialog_21");
			link.l1.go = "Hunting_huntsman_4";
		break;

		case "Hunting_huntsman_4":
			dialog.text = StringFromKey("LeBasque_dialog_22");
			link.l1 = "...";
			link.l1.go = "Hunting_huntsman_4_exit";
		break;

		case "Hunting_huntsman_4_exit":
			AddDialogExitQuest("Hunting_huntsman_2");
			dialogexit();
		break;

		case "Hunting_huntsman_9":
			dialog.text = StringFromKey("LeBasque_dialog_23");
			link.l1 = StringFromKey("LeBasque_dialog_24");
			link.l1.go = "Hunting_huntsman_10";
		break;

		case "Hunting_huntsman_10":
			dialog.text = StringFromKey("LeBasque_dialog_25");
			link.l1 = StringFromKey("LeBasque_dialog_26");
			link.l1.go = "Hunting_huntsman_10_1";
		break;

		case "Hunting_huntsman_10_1":
			dialog.text = StringFromKey("LeBasque_dialog_27");
			link.l1 = StringFromKey("LeBasque_dialog_28");
			link.l1.go = "Hunting_huntsman_10_2";
		break;

		case "Hunting_huntsman_10_2":
			dialog.text = StringFromKey("LeBasque_dialog_29");
			link.l1 = StringFromKey("LeBasque_dialog_30");
			link.l1.go = "Hunting_huntsman_10_3";
		break;

		case "Hunting_huntsman_10_3":
			dialog.text = StringFromKey("LeBasque_dialog_31", pchar);
			link.l1 = StringFromKey("LeBasque_dialog_32");
			link.l1.go = "Hunting_huntsman_10_5";
		break;

		case "Hunting_huntsman_10_5":
			dialog.text = StringFromKey("LeBasque_dialog_33");
			link.l1 = StringFromKey("LeBasque_dialog_34");
			link.l1.go = "Hunting_huntsman_11";
		break;

		case "Hunting_huntsman_11":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = StringFromKey("LeBasque_dialog_35");
				link.l1 = StringFromKey("LeBasque_dialog_36");
				link.l1.go = "Hunting_huntsman_11_exit";
			}
			else
			{
				GiveNationLicence(SPAIN, 30);
				LogSound_WithNotify(StringFromKey("InfoMessages_240", GetItemName("SpaTradeLicence"), 1), "Important_item", "spahunter");
				dialog.text = StringFromKey("LeBasque_dialog_37");
				link.l1 = StringFromKey("LeBasque_dialog_38");
				link.l1.go = "Hunting_huntsman_11_exit";
			}
		break;

		case "Hunting_huntsman_11_exit":
			sld = characterFromId("Etien_Marso");
			sld.Dialog.CurrentNode = "Hunting_huntsman_2";
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Bucaneer_Outpost_Townhall", "sit", "sit2");

			AddDialogExitQuest("Hunting_huntsman_4");
			dialogexit();
		break;

		case "Hunting_huntsman_second":
			dialog.text = StringFromKey("LeBasque_dialog_39");
			link.l1 = StringFromKey("LeBasque_dialog_40");
			link.l1.go = "Hunting_huntsman_second_exit";
		break;

		case "Hunting_huntsman_second_exit":
			dialogexit();
		break;

		case "Hunting_huntsman_12":
			dialog.text = StringFromKey("LeBasque_dialog_41", GetFullName(pchar));
			link.l1 = StringFromKey("LeBasque_dialog_42");
			link.l1.go = "Hunting_huntsman_13";
		break;

		case "Hunting_huntsman_13":
			TakeItemFromCharacter(pchar, "casket");
			dialog.text = StringFromKey("LeBasque_dialog_43");
			link.l1 = StringFromKey("LeBasque_dialog_44");
			link.l1.go = "Hunting_huntsman_14";
		break;

		case "Hunting_huntsman_14":
			dialog.text = StringFromKey("LeBasque_dialog_45");
			link.l1 = StringFromKey("LeBasque_dialog_46", pchar);
			link.l1.go = "Hunting_huntsman_15";
		break;

		case "Hunting_huntsman_15":
			sld = CharacterFromID("Esteban_Molina");
			ChangeCharacterAddressGroup(sld, "none", "", "");

			dialog.text = StringFromKey("LeBasque_dialog_47");
			link.l1 = StringFromKey("LeBasque_dialog_48");
			link.l1.go = "Hunting_huntsman_16";
		break;

		case "Hunting_huntsman_16":
			dialog.text = StringFromKey("LeBasque_dialog_49");
			link.l1 = StringFromKey("LeBasque_dialog_50");
			link.l1.go = "Hunting_huntsman_16_1";
		break;

		case "Hunting_huntsman_16_1":
			dialog.text = StringFromKey("LeBasque_dialog_51");
			link.l1 = StringFromKey("LeBasque_dialog_52");
			link.l1.go = "Hunting_huntsman_16_exit";
		break;

		case "Hunting_huntsman_16_exit":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = "Hunting_huntsman_second";
			AddDialogExitQuest("Hunting_huntsman_6");
			dialogexit();
		break;

		case "Hunting_huntsman_17":
			dialog.text = StringFromKey("LeBasque_dialog_53");
			link.l1 = StringFromKey("LeBasque_dialog_54");
			link.l1.go = "Hunting_huntsman_18";
		break;

		case "Hunting_huntsman_18":
			dialog.text = StringFromKey("LeBasque_dialog_55");
			link.l1 = StringFromKey("LeBasque_dialog_56");
			link.l1.go = "Hunting_huntsman_20";
		break;

		case "Hunting_huntsman_20":
			dialog.text = StringFromKey("LeBasque_dialog_57");
			link.l1 = StringFromKey("LeBasque_dialog_58");
			link.l1.go = "Hunting_huntsman_21";
		break;

		case "Hunting_huntsman_21":
			dialog.text = StringFromKey("LeBasque_dialog_59");
			link.l1 = StringFromKey("LeBasque_dialog_60");
			link.l1.go = "Hunting_huntsman_22";
		break;

		case "Hunting_huntsman_22":
			dialog.text = StringFromKey("LeBasque_dialog_61", pchar);
			link.l1 = StringFromKey("LeBasque_dialog_62");
			link.l1.go = "Hunting_huntsman_23";
		break;

		case "Hunting_huntsman_23":
			dialog.text = StringFromKey("LeBasque_dialog_63", pchar.lastname);
			link.l1 = StringFromKey("LeBasque_dialog_64");
			link.l1.go = "Hunting_huntsman_23_exit";
		break;

		case "Hunting_huntsman_23_exit":
			NextDiag.CurrentNode = "Hunting_huntsman_second";
			AddDialogExitQuest("Hunting_huntsman_19");
			dialogexit();
		break;

		case "Hunting_huntsman_24":
			RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
			dialog.text = StringFromKey("LeBasque_dialog_65");
			link.l1 = StringFromKey("LeBasque_dialog_66");
			link.l1.go = "Hunting_huntsman_25";
		break;

		case "Hunting_huntsman_25":
			dialog.text = StringFromKey("LeBasque_dialog_67");
			link.l1 = StringFromKey("LeBasque_dialog_68");
			link.l1.go = "Hunting_huntsman_26";
		break;

		case "Hunting_huntsman_26":
			AddMoneyToCharacter(pchar, 50000);
			dialog.text = StringFromKey("LeBasque_dialog_69");
			link.l1 = StringFromKey("LeBasque_dialog_70");
			link.l1.go = "Hunting_huntsman_27";
		break;

		case "Hunting_huntsman_27":
			dialog.text = StringFromKey("LeBasque_dialog_71");
			link.l1 = StringFromKey("LeBasque_dialog_72");
			link.l1.go = "Hunting_huntsman_27_exit";
		break;

		case "Hunting_huntsman_27_exit":
			AddDialogExitQuest("Hunting_huntsman_99");
			dialogexit();
		break;

		case "Hunting_huntsman_28":
			dialog.text = StringFromKey("LeBasque_dialog_73", pchar.lastname);
			link.l1 = StringFromKey("LeBasque_dialog_74", pchar);
			link.l1.go = "Hunting_huntsman_28_exit";
		break;

		case "Hunting_huntsman_28_exit":
			NextDiag.CurrentNode = "Hunting_huntsman_28";
			dialogexit();
		break;

		// 4 квест
		case "Brides_Tortuga_1":
			RemoveLandQuestmark_Main(npchar, "Brides_Tortuga");
			dialog.text = StringFromKey("LeBasque_dialog_75");
			link.l1 = StringFromKey("LeBasque_dialog_76");
			link.l1.go = "Brides_Tortuga_2";
		break;

		case "Brides_Tortuga_2":
			dialog.text = StringFromKey("LeBasque_dialog_77", pchar);
			link.l1 = StringFromKey("LeBasque_dialog_78");
			link.l1.go = "Brides_Tortuga_3";
		break;

		case "Brides_Tortuga_3":
			dialog.text = StringFromKey("LeBasque_dialog_79");
			link.l1 = StringFromKey("LeBasque_dialog_80", pchar);
			link.l1.go = "Brides_Tortuga_4";
		break;

		case "Brides_Tortuga_4":
			dialog.text = StringFromKey("LeBasque_dialog_81");
			link.l1 = StringFromKey("LeBasque_dialog_82");
			link.l1.go = "Brides_Tortuga_5";
		break;

		case "Brides_Tortuga_5":
			dialog.text = StringFromKey("LeBasque_dialog_83");
			link.l1 = StringFromKey("LeBasque_dialog_84");
			link.l1.go = "Brides_Tortuga_6";
		break;

		case "Brides_Tortuga_6":
			dialog.text = StringFromKey("LeBasque_dialog_85");
			link.l1 = StringFromKey("LeBasque_dialog_86", pchar);
			link.l1.go = "Brides_Tortuga_7";
		break;

		case "Brides_Tortuga_7":
			dialog.text = StringFromKey("LeBasque_dialog_87");
			link.l1 = StringFromKey("LeBasque_dialog_88");
			link.l1.go = "Brides_Tortuga_8";
		break;

		case "Brides_Tortuga_8":
			dialog.text = StringFromKey("LeBasque_dialog_89");
			link.l1 = StringFromKey("LeBasque_dialog_90");
			link.l1.go = "Brides_Tortuga_9";
		break;

		case "Brides_Tortuga_9":
			dialog.text = StringFromKey("LeBasque_dialog_91");
			link.l1 = StringFromKey("LeBasque_dialog_92");
			link.l1.go = "Brides_Tortuga_9_1";
		break;

		case "Brides_Tortuga_9_1":
			dialog.text = StringFromKey("LeBasque_dialog_93");
			link.l1 = StringFromKey("LeBasque_dialog_94");
			link.l1.go = "Brides_Tortuga_9_2";
		break;

		case "Brides_Tortuga_9_2":
			dialog.text = StringFromKey("LeBasque_dialog_95");
			link.l1 = StringFromKey("LeBasque_dialog_96");
			link.l1.go = "Brides_Tortuga_9_3";
		break;

		case "Brides_Tortuga_9_3":
			dialog.text = StringFromKey("LeBasque_dialog_97");
			link.l1 = StringFromKey("LeBasque_dialog_98");
			link.l1.go = "Brides_Tortuga_9_4";
		break;

		case "Brides_Tortuga_9_4":
			dialog.text = StringFromKey("LeBasque_dialog_99");
			link.l1 = StringFromKey("LeBasque_dialog_100");
			link.l1.go = "Brides_Tortuga_9_5";
		break;

		case "Brides_Tortuga_9_5":
			dialog.text = StringFromKey("LeBasque_dialog_101");
			link.l1 = StringFromKey("LeBasque_dialog_102");
			link.l1.go = "Brides_Tortuga_9_exit";
		break;

		case "Brides_Tortuga_9_exit":
			AddDialogExitQuest("Brides_Tortuga_2");
			NextDiag.CurrentNode = "Brides_Tortuga_Second";
			dialogexit();
		break;

		case "Brides_Tortuga_Second":
			dialog.text = StringFromKey("LeBasque_dialog_103", pchar);
			link.l1 = StringFromKey("LeBasque_dialog_104");
			link.l1.go = "Brides_Tortuga_Second_exit";
		break;

		case "Brides_Tortuga_Second_exit":
			NextDiag.CurrentNode = "Brides_Tortuga_Second";
			dialogexit();
		break;

		case "Brides_Tortuga_10":
			RemoveLandQuestmark_Main(npchar, "Brides_Tortuga");

			dialog.text = StringFromKey("LeBasque_dialog_105");
			link.l1 = StringFromKey("LeBasque_dialog_106");
			link.l1.go = "Brides_Tortuga_10_exit";
		break;

		case "Brides_Tortuga_10_exit":
			NextDiag.CurrentNode = "Brides_Tortuga_11";
			AddDialogExitQuest("Brides_Tortuga_ReportTime");
			DialogExit();
		break;

		case "Brides_Tortuga_11":
			dialog.text = StringFromKey("LeBasque_dialog_107");
			link.l1 = StringFromKey("LeBasque_dialog_108");
			link.l1.go = "Brides_Tortuga_12";
		break;

		case "Brides_Tortuga_12":
			dialog.text = StringFromKey("LeBasque_dialog_109", pchar);
			link.l1 = StringFromKey("LeBasque_dialog_110");
			link.l1.go = "Brides_Tortuga_13";
		break;

		case "Brides_Tortuga_13":
			dialog.text = StringFromKey("LeBasque_dialog_111");
			link.l1 = StringFromKey("LeBasque_dialog_112");
			link.l1.go = "Brides_Tortuga_14";
		break;

		case "Brides_Tortuga_14":
			dialog.text = StringFromKey("LeBasque_dialog_113");
			link.l1 = StringFromKey("LeBasque_dialog_114");
			link.l1.go = "Brides_Tortuga_15";
		break;

		case "Brides_Tortuga_15":
			dialog.text = StringFromKey("LeBasque_dialog_115");
			link.l1 = StringFromKey("LeBasque_dialog_116");
			link.l1.go = "Brides_Tortuga_17_exit";
			link.l2 = StringFromKey("LeBasque_dialog_117");
			link.l2.go = "Brides_Tortuga_17_exit";
		break;

		case "Brides_Tortuga_17_exit":
			AddMoneyToCharacter(pchar, 50000);
			AddCharacterExpToSkill(PChar, "Leadership", 2000);
			AddCharacterExpToSkill(PChar, "Sailing", 2000);
			AddCharacterExpToSkill(PChar, "Accuracy", 1000);
			AddCharacterExpToSkill(PChar, "Cannons", 1000);
			AddCharacterExpToSkill(PChar, "Repair", 1000);
			AddCharacterExpToSkill(PChar, "Defence", 1000);
			AddCharacterExpToSkill(PChar, "Sneak", 500);
			AddCharacterExpToSkill(Pchar, "Fortune", 1500);
			AddCharacterExpToSkill(pchar, "Pistol", 1500);
			AddDialogExitQuest("Brides_Tortuga_85");
			NextDiag.CurrentNode = "Brides_Tortuga_After";
			DialogExit();
		break;

		case "Brides_Tortuga_After":
			dialog.text = StringFromKey("LeBasque_dialog_118");
			link.l1 = StringFromKey("LeBasque_dialog_119");
			link.l1.go = "Brides_Tortuga_After_exit";
		break;

		case "Brides_Tortuga_After_exit":
			NextDiag.CurrentNode = "Brides_Tortuga_After";
			DialogExit();
		break;

		case "Royal_jackpot_1":
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorTurnToLocator(sld, "goto", "goto21");
			dialog.text = StringFromKey("LeBasque_dialog_120");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_2";
		break;

		case "Royal_jackpot_2":
			dialog.text = StringFromKey("LeBasque_dialog_121");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_3";
		break;

		case "Royal_jackpot_3":
			locCameraToPos(5.5, 2.5, 7.27, false);
			dialog.text = StringFromKey("LeBasque_dialog_122");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_4";
		break;

		case "Royal_jackpot_4":
			dialog.text = StringFromKey("LeBasque_dialog_123");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_5";
		break;

		case "Royal_jackpot_5":
			locCameraToPos(-12.5, 3.5, 8, false);
			dialog.text = StringFromKey("LeBasque_dialog_124", GetFullName(pchar));
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_6";
		break;

		case "Royal_jackpot_6":
			dialog.text = StringFromKey("LeBasque_dialog_125");
			link.l1 = StringFromKey("LeBasque_dialog_126");
			link.l1.go = "Royal_jackpot_Toast_exit";
		break;

		case "Royal_jackpot_Toast_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_11");
		break;

		case "Royal_jackpot_7":
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorTurnToLocator(sld, "quest", "quest_mass_1");
			dialog.text = StringFromKey("LeBasque_dialog_127");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_8";
		break;

		case "Royal_jackpot_8":
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorTurnToLocator(sld, "sit", "sit30");
			dialog.text = StringFromKey("LeBasque_dialog_128");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_9";
		break;

		case "Royal_jackpot_9":
			sld = characterFromId("Mishel_le_Bask");
			LAi_ActorTurnToLocator(sld, "quest", "quest_hero");
			dialog.text = StringFromKey("LeBasque_dialog_129");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_9_exit";
		break;

		case "Royal_jackpot_9_exit":
			AddDialogExitQuest("Royal_jackpot_21");
			dialogexit();
		break;

		case "Mass_dialog_11":
			dialog.text = StringFromKey("LeBasque_dialog_130");
			link.l1 = StringFromKey("LeBasque_dialog_131");
			link.l1.go = "Mass_dialog_12";
		break;

		case "Mass_dialog_12":
			dialog.text = StringFromKey("LeBasque_dialog_132");
			link.l1 = StringFromKey("LeBasque_dialog_133");
			link.l1.go = "Mass_dialog_14";
		break;

		case "Mass_dialog_14":
			dialog.text = StringFromKey("LeBasque_dialog_134");
			link.l1 = StringFromKey("LeBasque_dialog_135");
			link.l1.go = "Mass_dialog_14_exit";
		break;

		case "Mass_dialog_14_exit":
			AddDialogExitQuest("Royal_jackpot_34");
			dialogexit();
		break;

		case "Royal_jackpot_10":
			RemoveLandQuestMark_Main(npchar, "Royal_jackpot");
			AoP_RoyalDeckDialogTurn("Mishel_le_Bask", pchar.id);
			dialog.text = StringFromKey("LeBasque_dialog_136");
			link.l1 = StringFromKey("LeBasque_dialog_137", pchar);
			link.l1.go = "Royal_jackpot_11";
		break;
		
		case "Royal_jackpot_11":
			AoP_RoyalDeckDialogTurn("Mishel_le_Bask", pchar.id);
			dialog.text = StringFromKey("LeBasque_dialog_138");
			link.l1 = StringFromKey("LeBasque_dialog_139");
			link.l1.go = "Royal_jackpot_11_exit";
		break;

		case "Royal_jackpot_11_exit":
			sld = CharacterFromID("Mary_Belfler");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_5";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			DialogExit();
		break;

		case "Royal_jackpot_12":
			AoP_RoyalDeckDialogTurn("Mishel_le_Bask", "Etien_Marso");
			dialog.text = StringFromKey("LeBasque_dialog_140");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_12_exit";
		break;

		case "Royal_jackpot_12_exit":
			sld = CharacterFromID("Etien_Marso");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_8";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			DialogExit();
		break;

		case "Royal_jackpot_17":
			AoP_RoyalDeckDialogTurn("Mishel_le_Bask", "Fransua_Olone");
			dialog.text = StringFromKey("LeBasque_dialog_141");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_17_exit";
		break;

		case "Royal_jackpot_17_exit":
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_6";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			DialogExit();
		break;

		case "Royal_jackpot_18":
			AoP_RoyalDeckDialogTurn("Mishel_le_Bask", "Fransua_Olone");
			dialog.text = StringFromKey("LeBasque_dialog_142");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_18_exit";
		break;

		case "Royal_jackpot_18_exit":
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_7";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			DialogExit();
		break;

		case "Royal_jackpot_23":
			AoP_RoyalDeckDialogTurn("Mishel_le_Bask", pchar.id);
			dialog.text = StringFromKey("LeBasque_dialog_143", pchar, pchar.name);
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_24";
		break;

		case "Royal_jackpot_24":
			AoP_RoyalDeckDialogTurn("Mishel_le_Bask", "Young_Boy_Bask");
			dialog.text = StringFromKey("LeBasque_dialog_144");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_25";
		break;

		case "Royal_jackpot_25":
			AoP_RoyalDeckDialogTurn("Mishel_le_Bask", "Mary_Belfler");
			dialog.text = StringFromKey("LeBasque_dialog_145", pchar.ship.name);
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_26";
		break;

		case "Royal_jackpot_26":
			AoP_RoyalDeckDialogTurn("Mishel_le_Bask", "Etien_Marso");
			dialog.text = StringFromKey("LeBasque_dialog_146");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_27";
		break;

		case "Royal_jackpot_27":
			AoP_RoyalDeckDialogTurn("Mishel_le_Bask", pchar.id);
			dialog.text = StringFromKey("LeBasque_dialog_147");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_27_exit";
		break;

		case "Royal_jackpot_27_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_111");
		break;

		case "Royal_jackpot_deck_1":
			RemoveLandQuestmark_Main(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("LeBasque_dialog_148");
			link.l1 = StringFromKey("LeBasque_dialog_149");
			link.l1.go = "Royal_jackpot_deck_2";
		break;

		case "Royal_jackpot_deck_2":
			dialog.text = StringFromKey("LeBasque_dialog_150");
			link.l1 = StringFromKey("LeBasque_dialog_151");
			link.l1.go = "Royal_jackpot_deck_3_exit";
		break;

		case "Royal_jackpot_deck_3_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_117");
		break;

		case "Royal_jackpot_33":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorTurnToCharacter(sld, characterFromID("Royal_Margarita_Cap"));
			dialog.text = StringFromKey("LeBasque_dialog_152");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_33_exit";
		break;

		case "Royal_jackpot_33_exit":
			AddDialogExitQuest("Royal_jackpot_127");
			DialogExit();
		break;

		case "Royal_jackpot_34":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorTurnToCharacter(sld, characterFromID("Royal_Margarita_Cap"));
			dialog.text = StringFromKey("LeBasque_dialog_153");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_34_exit";
		break;

		case "Royal_jackpot_34_exit":
			sld = CharacterFromID("Royal_Margarita_Cap");
			sld.Dialog.CurrentNode = "Don_Alonso_5";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			DialogExit();
		break;

		case "Royal_jackpot_35":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_ActorTurnToCharacter(sld, characterFromID("Royal_Margarita_Cap"));
			dialog.text = StringFromKey("LeBasque_dialog_154");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_35_exit";
		break;

		case "Royal_jackpot_35_exit":
			AddDialogExitQuest("Royal_jackpot_132");
			dialogexit();
		break;

		case "Royal_jackpot_35_1":
			AoP_RoyalDeckDialogTurn("Mishel_le_Bask", "Royal_matros");
			dialog.text = StringFromKey("LeBasque_dialog_155");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_35_1_exit";
		break;

		case "Royal_jackpot_35_1_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_139");
		break;

		case "Royal_jackpot_36":
			locCameraFromToPos(1.37, 14, -9.4, false, 0.1, 12, -3);
			dialog.text = StringFromKey("LeBasque_dialog_156", pchar.name);
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_36_exit";
		break;

		case "Royal_jackpot_36_exit":
			AddDialogExitQuest("Royal_jackpot_150");
			DialogExit();
		break;

		case "Royal_jackpot_37":
			dialog.text = StringFromKey("LeBasque_dialog_157", pchar.name);
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_37_exit";
		break;

		case "Royal_jackpot_37_exit":
			AddDialogExitQuest("Royal_jackpot_153");
			DialogExit();
		break;

		case "Royal_jackpot_38":
			dialog.text = StringFromKey("LeBasque_dialog_158");
			link.l1 = StringFromKey("LeBasque_dialog_159", pchar);
			link.l1.go = "Royal_jackpot_38_1";
		break;

		case "Royal_jackpot_38_1":
			dialog.text = StringFromKey("LeBasque_dialog_160");
			link.l1 = StringFromKey("LeBasque_dialog_161");
			link.l1.go = "Royal_jackpot_38_1_exit";
			link.l2 = StringFromKey("LeBasque_dialog_162");
			link.l2.go = "Royal_jackpot_39_exit";
		break;

		case "Royal_jackpot_38_1_exit":
			RemoveLandQuestMark_Main(npchar, "Royal_jackpot");
			NextDiag.CurrentNode = "Royal_jackpot_38_1";
			DialogExit();
		break;

		case "Royal_jackpot_39_exit":
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddDialogExitQuest("Royal_jackpot_156");
			DialogExit();
		break;

		case "Royal_jackpot_39":
			RemoveLandQuestmark_Main(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("LeBasque_dialog_163");
			link.l1 = StringFromKey("LeBasque_dialog_164");
			link.l1.go = "Royal_jackpot_39_exit";
		break;

		case "Royal_jackpot_39_exit":
			sld = CharacterFromID("Fransua_Olone");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			AddDialogExitQuest("Royal_jackpot_156");
			dialogexit();
		break;

		case "Royal_jackpot_40":
			RemoveLandQuestmark_Main(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("LeBasque_dialog_165");
			link.l1 = StringFromKey("LeBasque_dialog_166", pchar);
			link.l1.go = "Royal_jackpot_40_1";
		break;

		case "Royal_jackpot_40_1":
			dialog.text = StringFromKey("LeBasque_dialog_167");
			link.l1 = StringFromKey("LeBasque_dialog_168");
			link.l1.go = "Royal_jackpot_40_2";
		break;

		case "Royal_jackpot_40_2":
			dialog.text = StringFromKey("LeBasque_dialog_169");
			link.l1 = StringFromKey("LeBasque_dialog_170");
			link.l1.go = "Royal_jackpot_40_3";
		break;

		case "Royal_jackpot_40_3":
			dialog.text = StringFromKey("LeBasque_dialog_171", pchar);
			link.l1 = StringFromKey("LeBasque_dialog_172", pchar);
			link.l1.go = "Royal_jackpot_40_4";
		break;

		case "Royal_jackpot_40_4":
			dialog.text = StringFromKey("LeBasque_dialog_173");
			link.l1 = StringFromKey("LeBasque_dialog_174");
			link.l1.go = "Royal_jackpot_40_exit";
		break;

		case "Royal_jackpot_40_exit":
			AddDialogExitQuest("Royal_jackpot_163");
			DialogExit();
		break;

		case "Royal_jackpot_41":
			RemoveLandQuestmark_Main(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("LeBasque_dialog_175", pchar.name);
			link.l1 = StringFromKey("LeBasque_dialog_176");
			link.l1.go = "Royal_jackpot_41_1";
		break;

		case "Royal_jackpot_41_1":
			dialog.text = StringFromKey("LeBasque_dialog_177");
			link.l1 = StringFromKey("LeBasque_dialog_178");
			link.l1.go = "Royal_jackpot_41_2";
		break;

		case "Royal_jackpot_41_2":
			dialog.text = StringFromKey("LeBasque_dialog_179");
			link.l1 = StringFromKey("LeBasque_dialog_180", pchar);
			link.l1.go = "Royal_jackpot_42";
		break;

		case "Royal_jackpot_42":
			dialog.text = StringFromKey("LeBasque_dialog_181");
			link.l1.go = "Royal_jackpot_42_1";
		break;

		case "Royal_jackpot_42_1":
			dialog.text = StringFromKey("LeBasque_dialog_182", pchar, pchar.name);
			link.l1 = StringFromKey("LeBasque_dialog_183", pchar);
			link.l1.go = "Royal_jackpot_43";
		break;

		case "Royal_jackpot_43":
			dialog.text = StringFromKey("LeBasque_dialog_184");
			link.l1 = StringFromKey("LeBasque_dialog_185");
			link.l1.go = "Royal_jackpot_44";
		break;

		case "Royal_jackpot_44":
			dialog.text = StringFromKey("LeBasque_dialog_186");
			link.l1 = StringFromKey("LeBasque_dialog_187");
			link.l1.go = "Royal_jackpot_44_1";
		break;

		case "Royal_jackpot_44_1":
			dialog.text = StringFromKey("LeBasque_dialog_188", pchar);
			link.l1 = StringFromKey("LeBasque_dialog_189", pchar);
			link.l1.go = "Royal_jackpot_44_1_vauban";
		break;

		case "Royal_jackpot_44_1_vauban":
			dialog.text = StringFromKey("LeBasque_dialog_312");
			link.l1 = StringFromKey("LeBasque_dialog_313" + GetSexPhrase("_m", "_f"));
			link.l1.go = "Royal_jackpot_44_2";
		break;

		case "Royal_jackpot_44_2":
			dialog.text = StringFromKey("LeBasque_dialog_190");
			link.l1 = StringFromKey("LeBasque_dialog_191");
			link.l1.go = "Royal_jackpot_44_3";
		break;

		case "Royal_jackpot_44_3":
			dialog.text = StringFromKey("LeBasque_dialog_192");
			link.l1 = StringFromKey("LeBasque_dialog_193");
			link.l1.go = "Royal_jackpot_44_exit";
		break;

		case "Royal_jackpot_44_exit":
			AddDialogExitQuest("Royal_jackpot_167");
			DialogExit();
		break;

		case "Keys_lagoon_1":
			dialog.text = StringFromKey("LeBasque_dialog_194", pchar.name);
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_1_exit";
		break;

		case "Keys_lagoon_1_exit":
			AddDialogExitQuest("Keys_lagoon_5");
			dialogexit();
		break;

		case "Keys_lagoon_2":
			dialog.text = StringFromKey("LeBasque_dialog_195");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_2_exit";
		break;

		case "Keys_lagoon_2_exit":
			StartInstantDialogNow("Fransua_Olone", "Keys_lagoon_1", "Quest\LeBasque\Olone_dialog.c", true);
		break;

		case "Keys_lagoon_4":
			dialog.text = StringFromKey("LeBasque_dialog_196");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_4_exit";
		break;

		case "Keys_lagoon_4_exit":
			AddDialogExitQuest("Keys_lagoon_11");
			DialogExit();
		break;

		case "Keys_lagoon_5":
			dialog.text = StringFromKey("LeBasque_dialog_197");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_6";
		break;

		case "Keys_lagoon_6":
			dialog.text = StringFromKey("LeBasque_dialog_198");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_6_exit";
		break;

		case "Keys_lagoon_6_exit":
			AddDialogExitQuest("Keys_lagoon_15");
			dialogexit();
		break;

		case "Keys_lagoon_7":
			dialog.text = StringFromKey("LeBasque_dialog_199");
			link.l1 = StringFromKey("LeBasque_dialog_200");
			link.l1.go = "Keys_lagoon_8";
		break;

		case "Keys_lagoon_8":
			dialog.text = StringFromKey("LeBasque_dialog_201", pchar.name);
			link.l1 = StringFromKey("LeBasque_dialog_202");
			link.l1.go = "Keys_lagoon_8_exit";
		break;

		case "Keys_lagoon_8_exit":
			AddDialogExitQuest("Keys_lagoon_17");
			dialogexit();
		break;

		case "Keys_lagoon_9":
			dialog.text = StringFromKey("LeBasque_dialog_203", pchar.name);
			link.l1 = StringFromKey("LeBasque_dialog_204", pchar);
			link.l1.go = "Keys_lagoon_10";
		break;

		case "Keys_lagoon_10":
			dialog.text = StringFromKey("LeBasque_dialog_205");
			link.l1 = StringFromKey("LeBasque_dialog_206");
			link.l1.go = "Keys_lagoon_ToOlone_1";
		break;

		case "Keys_lagoon_ToOlone_1":
			StartInstantDialogNow("Fransua_Olone", "Keys_lagoon_1_1", "Quest\Lebasque\Olone_dialog.c", true);
		break;

		case "Keys_lagoon_11":
			dialog.text = StringFromKey("LeBasque_dialog_207");
			link.l1 = StringFromKey("LeBasque_dialog_208");
			link.l1.go = "Keys_lagoon_11_exit";
		break;

		case "Keys_lagoon_11_exit":
			AddDialogExitQuest("Keys_lagoon_19");
			DialogExit();
		break;

		case "Keys_lagoon_Aruba":
			dialog.text = "...";
			link.l1 = StringFromKey("LeBasque_dialog_209", pchar);
			link.l1.go = "Keys_lagoon_Aruba_Exit";
		break;

		case "Keys_lagoon_Aruba_Exit":
			AddDialogExitQuest("Keys_lagoon_104");
			DialogExit();
		break;

		case "Keys_lagoon_Aruba_2":
			dialog.text = "...";
			link.l1 = StringFromKey("LeBasque_dialog_210");
			link.l1.go = "Keys_lagoon_Aruba_3";
		break;
		case "Keys_lagoon_Aruba_3":
			dialog.text = StringFromKey("LeBasque_dialog_211");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_Aruba_3_Exit";
		break;

		case "Keys_lagoon_Aruba_3_Exit":
			AddDialogExitQuest("Keys_lagoon_116");
			DialogExit();
		break;

		case "Keys_lagoon_Aruba_4":
			dialog.text = StringFromKey("LeBasque_dialog_212");
			link.l1 = StringFromKey("LeBasque_dialog_213");
			link.l1.go = "Keys_lagoon_Aruba_5";
		break;

		case "Keys_lagoon_Aruba_5":
			dialog.text = StringFromKey("LeBasque_dialog_214");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_Aruba_5_Exit";
		break;

		case "Keys_lagoon_Aruba_5_Exit":
			StartInstantDialogNow("Daniel_Monbar", "Monbar_Tost", "Quest\Lebasque\Monbar_dialog.c", true);
		break;

		case "Keys_lagoon_Aruba_6":
			dialog.text = "...";
			link.l1 = StringFromKey("LeBasque_dialog_215");
			link.l1.go = "Keys_lagoon_Aruba_7_Exit";
		break;

		case "Keys_lagoon_Aruba_7_Exit":
			AddDialogExitQuest("Keys_lagoon_117");
			DialogExit();
		break;

		case "Keys_lagoon_Departure":
			dialog.text = StringFromKey("LeBasque_dialog_216", pchar);
			link.l1 = StringFromKey("LeBasque_dialog_217", pchar);
			link.l1.go = "Keys_lagoon_Departure_1";
		break;

		case "Keys_lagoon_Departure_1":
			dialog.text = StringFromKey("LeBasque_dialog_218");
			link.l1 = StringFromKey("LeBasque_dialog_219", pchar);
			link.l1.go = "Keys_lagoon_Departure_2";
		break;

		case "Keys_lagoon_Departure_2":
			dialog.text = StringFromKey("LeBasque_dialog_220", pchar);
			link.l1 = StringFromKey("LeBasque_dialog_221");
			link.l1.go = "Keys_lagoon_Departure_3";
		break;

		case "Keys_lagoon_Departure_3":
			dialog.text = StringFromKey("LeBasque_dialog_222");
			link.l1 = StringFromKey("LeBasque_dialog_223");

			if (GetCompanionQuantity(pchar) > 1)
			{
				link.l1.go = "Keys_lagoon_Departure_Ships";
			}
			else
			{
				link.l1.go = "Keys_lagoon_Departure_Ready";
			}
		break;

		case "Keys_lagoon_Departure_Ships":
			dialog.text = StringFromKey("LeBasque_dialog_224");
			link.l1 = StringFromKey("LeBasque_dialog_225");
			link.l1.go = "Keys_lagoon_Departure_Ships_exit";
		break;

		case "Keys_lagoon_Departure_Ships_exit":
			pchar.questTemp.AoP.LagoonShipsAsked = true;
			LAi_SetStayType(npchar);
			NextDiag.CurrentNode = "Keys_lagoon_Departure_Check";
			DialogExit();
		break;

		case "Keys_lagoon_Departure_Check":
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = StringFromKey("LeBasque_dialog_226");
				link.l1 = StringFromKey("LeBasque_dialog_227");
				link.l1.go = "Keys_lagoon_Departure_Ships_exit";
			}
			else
			{
				dialog.text = StringFromKey("LeBasque_dialog_228");
				link.l1 = StringFromKey("LeBasque_dialog_229");
				link.l1.go = "Keys_lagoon_Departure_Ready_exit";
			}
		break;

		case "Keys_lagoon_Departure_Ready":
			dialog.text = StringFromKey("LeBasque_dialog_230");
			link.l1 = StringFromKey("LeBasque_dialog_231");
			link.l1.go = "Keys_lagoon_Departure_Ready_exit";
		break;

		case "Keys_lagoon_Departure_Ready_exit":
			AddDialogExitQuest("Keys_lagoon_119");
			DialogExit();

			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "officers", "sea_1", "none", "", "", "", -1);
		break;

		case "Keys_lagoon_11_1":
			dialog.text = StringFromKey("LeBasque_dialog_232");
			link.l1 = StringFromKey("LeBasque_dialog_233");
			link.l1.go = "Keys_lagoon_12";
		break;

		case "Keys_lagoon_12":
			dialog.text = StringFromKey("LeBasque_dialog_234");
			link.l1 = StringFromKey("LeBasque_dialog_235");
			link.l1.go = "Keys_lagoon_12_Exit";
		break;

		case "Keys_lagoon_12_Exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_123");
		break;

		case "Keys_lagoon_29":
			dialog.text = StringFromKey("LeBasque_dialog_236");
			link.l1 = StringFromKey("LeBasque_dialog_237");
			link.l1.go = "Keys_lagoon_30";
		break;

		case "Keys_lagoon_30":
			dialog.text = StringFromKey("LeBasque_dialog_238");
			link.l1 = StringFromKey("LeBasque_dialog_239");
			link.l1.go = "Keys_lagoon_31";
		break;

		case "Keys_lagoon_31":
			dialog.text = StringFromKey("LeBasque_dialog_240");
			link.l1 = StringFromKey("LeBasque_dialog_241");
			link.l1.go = "Keys_lagoon_31_Exit";
		break;

		case "Keys_lagoon_31_Exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_128");
		break;

		case "Keys_lagoon_37":
			RemoveLandQuestMark_Gen(npchar, "Keys_lagoon");
			QuestPointerDelLoc("Maracaibo_town", "goto", "goto2");
			dialog.text = "...";
			link.l1 = StringFromKey("LeBasque_dialog_242");
			link.l1.go = "Keys_lagoon_38";
		break;

		case "Keys_lagoon_38":
			dialog.text = StringFromKey("LeBasque_dialog_243");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_38_Exit";
		break;

		case "Keys_lagoon_38_Exit":
			AddDialogExitQuest("Keys_lagoon_145");
			DialogExit();
		break;

		case "Keys_lagoon_39":
			dialog.text = StringFromKey("LeBasque_dialog_244");
			link.l1 = StringFromKey("LeBasque_dialog_245");
			link.l1.go = "Keys_lagoon_40";
		break;

		case "Keys_lagoon_40":
			dialog.text = StringFromKey("LeBasque_dialog_246");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_40_Exit";
		break;

		case "Keys_lagoon_40_Exit":
			AddDialogExitQuest("Keys_lagoon_147");
			DialogExit();
		break;

		case "Keys_lagoon_41":
			dialog.text = "...";
			link.l1 = StringFromKey("LeBasque_dialog_247");
			link.l1.go = "Keys_lagoon_42";
		break;

		case "Keys_lagoon_42":
			dialog.text = StringFromKey("LeBasque_dialog_248");
			link.l1 = StringFromKey("LeBasque_dialog_249");
			link.l1.go = "Keys_lagoon_43";
		break;

		case "Keys_lagoon_43":
			dialog.text = StringFromKey("LeBasque_dialog_250");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_43_Exit";
		break;

		case "Keys_lagoon_43_Exit":
			AddDialogExitQuest("Keys_lagoon_149");
			DialogExit();
		break;

		case "Keys_lagoon_59":
			dialog.text = StringFromKey("LeBasque_dialog_251");
			link.l1 = StringFromKey("LeBasque_dialog_252");
			link.l1.go = "Keys_lagoon_60";
		break;

		case "Keys_lagoon_60":
			dialog.text = StringFromKey("LeBasque_dialog_253");
			link.l1 = StringFromKey("LeBasque_dialog_254");
			link.l1.go = "Keys_lagoon_61";
		break;

		case "Keys_lagoon_61":
			dialog.text = StringFromKey("LeBasque_dialog_255");
			link.l1 = StringFromKey("LeBasque_dialog_256");
			link.l1.go = "Keys_lagoon_62";
		break;

		case "Keys_lagoon_62":
			dialog.text = StringFromKey("LeBasque_dialog_257", pchar.name);
			link.l1 = StringFromKey("LeBasque_dialog_258");
			link.l1.go = "Keys_lagoon_63";
		break;

		case "Keys_lagoon_63":
			dialog.text = StringFromKey("LeBasque_dialog_259");
			link.l1 = StringFromKey("LeBasque_dialog_260");
			link.l1.go = "Keys_lagoon_69_exit";
		break;

		case "Keys_lagoon_69_exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_165");
		break;

		case "Keys_lagoon_70":
			dialog.text = StringFromKey("LeBasque_dialog_261");
			link.l1 = StringFromKey("LeBasque_dialog_262");
			link.l1.go = "Keys_lagoon_71";
		break;

		case "Keys_lagoon_71":
			dialog.text = StringFromKey("LeBasque_dialog_263");
			link.l1 = StringFromKey("LeBasque_dialog_264");
			link.l1.go = "Keys_lagoon_72_exit";
		break;

		case "Keys_lagoon_72_exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_169");
		break;

		case "Keys_lagoon_73":
			dialog.text = StringFromKey("LeBasque_dialog_265");
			link.l1 = StringFromKey("LeBasque_dialog_266");
			link.l1.go = "Keys_lagoon_74";
		break;

		case "Keys_lagoon_74":
			dialog.text = StringFromKey("LeBasque_dialog_267");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_74_exit";
		break;

		case "Keys_lagoon_74_exit":
			StartInstantDialogNow("Fransua_Olone", "Keys_lagoon_2", "Quest\LeBasque\Olone_dialog.c", true);
		break;

		case "Keys_lagoon_75":
			dialog.text = "...";
			link.l1 = StringFromKey("LeBasque_dialog_268");
			link.l1.go = "Keys_lagoon_76";
		break;

		case "Keys_lagoon_76":
			dialog.text = StringFromKey("LeBasque_dialog_269");
			link.l1 = StringFromKey("LeBasque_dialog_270");
			link.l1.go = "Keys_lagoon_77";
		break;

		case "Keys_lagoon_77":
			dialog.text = StringFromKey("LeBasque_dialog_271");
			link.l1 = StringFromKey("LeBasque_dialog_272");
			link.l1.go = "Keys_lagoon_78";
		break;

		case "Keys_lagoon_78":
			dialog.text = StringFromKey("LeBasque_dialog_273");
			link.l1 = StringFromKey("LeBasque_dialog_274");
			link.l1.go = "Keys_lagoon_79";
		break;

		case "Keys_lagoon_79":
			dialog.text = StringFromKey("LeBasque_dialog_275");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_79_exit";
		break;

		case "Keys_lagoon_79_exit":
			StartInstantDialogNow("Fransua_Olone", "Keys_lagoon_3", "Quest\LeBasque\Olone_dialog.c", true);
		break;

		case "Keys_lagoon_80":
			dialog.text = StringFromKey("LeBasque_dialog_276");
			link.l1 = StringFromKey("LeBasque_dialog_277");
			link.l1.go = "Keys_lagoon_80_Exit";
		break;

		case "Keys_lagoon_80_Exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_195");
		break;

		case "Keys_lagoon_88":
			dialog.text = StringFromKey("LeBasque_dialog_278");
			link.l1 = StringFromKey("LeBasque_dialog_279");
			link.l1.go = "Keys_lagoon_89";
		break;

		case "Keys_lagoon_89":
			dialog.text = StringFromKey("LeBasque_dialog_280");
			link.l1 = StringFromKey("LeBasque_dialog_281");
			link.l1.go = "Keys_lagoon_90";
		break;

		case "Keys_lagoon_90":
			dialog.text = StringFromKey("LeBasque_dialog_282");
			link.l1 = StringFromKey("LeBasque_dialog_283");
			link.l1.go = "Keys_lagoon_92_exit";
		break;

		case "Keys_lagoon_92_exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_216");
		break;

		case "Keys_lagoon_93":
			dialog.text = StringFromKey("LeBasque_dialog_284");
			link.l1 = StringFromKey("LeBasque_dialog_285");
			link.l1.go = "Keys_lagoon_94";
		break;

		case "Keys_lagoon_94":
			dialog.text = StringFromKey("LeBasque_dialog_286");
			link.l1 = StringFromKey("LeBasque_dialog_287");
			link.l1.go = "Keys_lagoon_96_exit";
		break;

		case "Keys_lagoon_96_exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_219");
		break;

		case "Keys_lagoon_111":
			RemoveLandQuestMark_Main(npchar, "Keys_lagoon");
			dialog.text = StringFromKey("LeBasque_dialog_288", pchar, pchar.name);
			link.l1 = StringFromKey("LeBasque_dialog_289", pchar);
			link.l1.go = "Keys_lagoon_112";
		break;

		case "Keys_lagoon_112":
			dialog.text = StringFromKey("LeBasque_dialog_290");
			link.l1 = StringFromKey("LeBasque_dialog_291");
			link.l1.go = "Keys_lagoon_113";
		break;

		case "Keys_lagoon_113":
			dialog.text = StringFromKey("LeBasque_dialog_292");
			link.l1 = StringFromKey("LeBasque_dialog_293", pchar);
			link.l1.go = "Keys_lagoon_113_exit";
		break;

		case "Keys_lagoon_113_exit":
			AddDialogExitQuest("Keys_lagoon_245");
			DialogExit();
		break;

		case "Keys_lagoon_104":
			dialog.text = "...";
			link.l1 = StringFromKey("LeBasque_dialog_294");
			link.l1.go = "Keys_lagoon_104_Exit";
		break;

		case "Keys_lagoon_104_Exit":
			AddDialogExitQuest("Keys_lagoon_240_2");
			dialogexit();
		break;

		case "Keys_lagoon_114":
			dialog.text = StringFromKey("LeBasque_dialog_295");
			link.l1 = StringFromKey("LeBasque_dialog_296");
			link.l1.go = "Keys_lagoon_114_1";
		break;

		case "Keys_lagoon_114_1":
			dialog.text = StringFromKey("LeBasque_dialog_297");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_114_1_Exit";
		break;

		case "Keys_lagoon_114_1_Exit":
			AddDialogExitQuest("Keys_lagoon_248");
			DialogExit();
		break;

		case "Keys_lagoon_114_3":
			dialog.text = StringFromKey("LeBasque_dialog_298", pchar.name);
			link.l1 = StringFromKey("LeBasque_dialog_299", pchar);
			link.l1.go = "Keys_lagoon_114_4";
		break;

		case "Keys_lagoon_114_4":
			if (!CheckAttribute(pchar, "questTemp.AoP.KeysLagoon.FinalSharePaid"))
			{
				AddMoneyToCharacter(pchar, 250000);
				pchar.questTemp.AoP.KeysLagoon.FinalSharePaid = true;
			}
			dialog.text = StringFromKey("LeBasque_dialog_300");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_114_4_Exit";
		break;

		case "Keys_lagoon_114_4_Exit":
			AddDialogExitQuest("Keys_lagoon_250");
			DialogExit();
		break;

		case "Keys_lagoon_114_14":
			dialog.text = StringFromKey("LeBasque_dialog_301");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_114_14_Exit";
		break;

		case "Keys_lagoon_114_14_Exit":
			StartInstantDialogNow("Rimalier", "Keys_lagoon_6_NoOfficer", "Quest\LeBasque\Rimalier_dialog.c", true);
		break;

		case "Keys_lagoon_114_17":
			dialog.text = "...";
			link.l1 = StringFromKey("LeBasque_dialog_302", pchar);
			link.l1.go = "Keys_lagoon_114_18";
		break;

		case "Keys_lagoon_114_18":
			dialog.text = StringFromKey("LeBasque_dialog_303", pchar);
			link.l1 = StringFromKey("LeBasque_dialog_304");
			link.l1.go = "Keys_lagoon_114_19";
		break;

		case "Keys_lagoon_114_19":
			dialog.text = StringFromKey("LeBasque_dialog_305", pchar);
			link.l1 = StringFromKey("LeBasque_dialog_306");
			link.l1.go = "Keys_lagoon_114_20";
		break;

		case "Keys_lagoon_114_20":
			dialog.text = StringFromKey("LeBasque_dialog_307");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_114_20_Exit";
		break;

		case "Keys_lagoon_114_20_Exit":
			AddDialogExitQuest("Keys_lagoon_294");
			DialogExit();
		break;

		case "Second_time":
			dialog.text = StringFromKey("LeBasque_dialog_308", pchar, pchar.name);
			link.l1 = StringFromKey("LeBasque_dialog_309", pchar);
			link.l1.go = "Second_time_exit";
		break;

		case "Second_time_exit":
			NextDiag.CurrentNode = "Second_time";
			DialogExit();
		break;

		case "Keys_lagoon_Res_12":
			dialog.text = "...";
			link.l1 = StringFromKey("LeBasque_dialog_310");
			link.l1.go = "Keys_lagoon_Res_12_Exit";
		break;

		case "Keys_lagoon_Res_12_Exit":
			LAi_SetStayType(pchar);
			StartInstantDialogNow("Maracaibo_Mayor", "Keys_lagoon_Res_13", "Mayor\Maracaibo_Mayor.c", true);
		break;

		case "Keys_lagoon_Res_38":
			dialog.text = "...";
			link.l1 = StringFromKey("LeBasque_dialog_311");
			link.l1.go = "Keys_lagoon_Res_38_Exit";
		break;

		case "Keys_lagoon_Res_38_Exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_Res_11");
		break;

		case "Exit":
			 NextDiag.CurrentNode = "first time";
			 DialogExit();
		break;
}
}

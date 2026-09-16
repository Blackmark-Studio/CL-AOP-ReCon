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

		case "Monbar_1":
			RemoveLandQuestmark_Main(npchar, "Keys_lagoon");
			dialog.text = StringFromKey("Monbar_dialog_1", GetLastName(pchar));
			link.l1 = StringFromKey("Monbar_dialog_2", pchar);
			link.l1.go = "Monbar_2";
		break;

		case "Monbar_2":
			dialog.text = StringFromKey("Monbar_dialog_3");
			link.l1 = StringFromKey("Monbar_dialog_4");
			link.l1.go = "Monbar_3";
		break;

		case "Monbar_3":
			dialog.text = StringFromKey("Monbar_dialog_5");
			link.l1 = StringFromKey("Monbar_dialog_6");
			link.l1.go = "Monbar_4";
		break;

		case "Monbar_4":
			dialog.text = StringFromKey("Monbar_dialog_7");
			link.l1 = StringFromKey("Monbar_dialog_8");
			link.l1.go = "Monbar_5";
		break;

		case "Monbar_5":
			dialog.text = StringFromKey("Monbar_dialog_9");
			link.l1 = StringFromKey("Monbar_dialog_10");
			link.l1.go = "Monbar_6";
		break;

		case "Monbar_6":
			dialog.text = StringFromKey("Monbar_dialog_11");
			link.l1 = StringFromKey("Monbar_dialog_12");
			link.l1.go = "Monbar_7";
		break;

		case "Monbar_7":
			dialog.text = StringFromKey("Monbar_dialog_13");
			link.l1 = StringFromKey("Monbar_dialog_14", pchar);
			link.l1.go = "Monbar_8";
		break;

		case "Monbar_8":
			dialog.text = StringFromKey("Monbar_dialog_15");
			link.l1 = StringFromKey("Monbar_dialog_16");
			link.l1.go = "Monbar_9";
		break;

		case "Monbar_9":
			dialog.text = StringFromKey("Monbar_dialog_17");
			link.l1 = StringFromKey("Monbar_dialog_18");
			link.l1.go = "Monbar_10";
		break;

		case "Monbar_10":
			AddDialogExitQuest("Keys_lagoon_46");
			dialogexit();
		break;

		case "Monbar_11":
			dialog.text = StringFromKey("Monbar_dialog_19");
			link.l1 = StringFromKey("Monbar_dialog_20");
			link.l1.go = "Monbar_12";
		break;

		case "Monbar_12":
			dialog.text = StringFromKey("Monbar_dialog_21");
			link.l1 = StringFromKey("Monbar_dialog_22");
			link.l1.go = "Monbar_13";
		break;

		case "Monbar_13":
			dialog.text = StringFromKey("Monbar_dialog_23");
			link.l1 = StringFromKey("Monbar_dialog_24");
			link.l1.go = "Monbar_14";
		break;

		case "Monbar_14":
			if (sti(pchar.questTemp.AoP.ArubaIndianHealedByPlayer) == 1)
			{
				dialog.text = StringFromKey("Monbar_dialog_25");
				link.l1 = StringFromKey("Monbar_dialog_26", pchar);
			}
			else
			{
				dialog.text = StringFromKey("Monbar_dialog_27");
				link.l1 = StringFromKey("Monbar_dialog_28");
			}

			link.l1.go = "Monbar_14_exit";
		break;

		case "Monbar_14_exit":
			LAi_SetCitizenType(npchar);
			NextDiag.CurrentNode = "Monbar_second";
			AddDialogExitQuest("Keys_lagoon_55");
			dialogexit();
		break;

		case "Monbar_second":
			dialog.text = StringFromKey("Monbar_dialog_29");
			link.l1 = StringFromKey("Monbar_dialog_30");
			link.l1.go = "Monbar_second_exit";
		break;

		case "Monbar_second_exit":
			NextDiag.CurrentNode = "Monbar_second";
			dialogexit();
		break;

		case "Monbar_18":
			RemoveLandQuestmark_Main(npchar, "Keys_lagoon");
			dialog.text = StringFromKey("Monbar_dialog_31");
			link.l1 = StringFromKey("Monbar_dialog_32");
			link.l1.go = "Monbar_19";
		break;

		case "Monbar_19":
			TakeItemFromCharacter(pchar, "letter_Aruba");
			dialog.text = StringFromKey("Monbar_dialog_33");
			link.l1 = StringFromKey("Monbar_dialog_34");
			link.l1.go = "Monbar_20";
		break;

		case "Monbar_20":
			dialog.text = StringFromKey("Monbar_dialog_35");
			link.l1 = StringFromKey("Monbar_dialog_36");
			link.l1.go = "Monbar_21";
		break;

		case "Monbar_21":
			dialog.text = StringFromKey("Monbar_dialog_37");
			link.l1 = StringFromKey("Monbar_dialog_38");
			link.l1.go = "Monbar_22";
		break;

		case "Monbar_22":
			dialog.text = StringFromKey("Monbar_dialog_39");
			link.l1 = StringFromKey("Monbar_dialog_40");
			link.l1.go = "Monbar_23";
		break;

		case "Monbar_23":
			dialog.text = StringFromKey("Monbar_dialog_41");
			link.l1 = StringFromKey("Monbar_dialog_42");
			link.l1.go = "Monbar_24";
		break;

		case "Monbar_24":
			dialog.text = StringFromKey("Monbar_dialog_43");
			link.l1 = StringFromKey("Monbar_dialog_44");
			link.l1.go = "Monbar_25";
		break;

		case "Monbar_25":
			dialog.text = StringFromKey("Monbar_dialog_45");
			link.l1 = StringFromKey("Monbar_dialog_46");
			link.l1.go = "Monbar_26_Exit";
		break;

		case "Monbar_26_Exit":
			NextDiag.CurrentNode = "Monbar_second_2";
			AddDialogExitQuest("Keys_lagoon_58");
			dialogexit();
		break;

		case "Monbar_second_2":
			dialog.text = StringFromKey("Monbar_dialog_47");
			link.l1 = StringFromKey("Monbar_dialog_48", pchar);
			link.l1.go = "Monbar_second_2_exit";
		break;

		case "Monbar_second_2_exit":
		NextDiag.CurrentNode = "Monbar_second_2";
		dialogexit();
		break;

		case "Monbar_27":
			dialog.text = StringFromKey("Monbar_dialog_49");
			link.l1 = "...";
			link.l1.go = "Monbar_27_exit";
		break;

		case "Monbar_27_exit":
		AddDialogExitQuest("Keys_lagoon_67");
			dialogexit();
		break;

		case "Monbar_28":
			dialog.text = StringFromKey("Monbar_dialog_50", pchar, GetFirstName(pchar));
			link.l1 = StringFromKey("Monbar_dialog_51", pchar);
			link.l1.go = "Monbar_29";
		break;

		case "Monbar_29":
			dialog.text = StringFromKey("Monbar_dialog_52", pchar);
			link.l1 = StringFromKey("Monbar_dialog_53", pchar);
			link.l1.go = "Monbar_30";
		break;

		case "Monbar_30":
			dialog.text = StringFromKey("Monbar_dialog_54", pchar);
			link.l1 = StringFromKey("Monbar_dialog_55");
			link.l1.go = "Monbar_30_exit";
		break;

		case "Monbar_30_exit":
			AddDialogExitQuest("Keys_lagoon_69");
			dialogexit();
		break;

		case "Monbar_31":
			dialog.text = StringFromKey("Monbar_dialog_56", pchar);
			link.l1 = StringFromKey("Monbar_dialog_57");
			link.l1.go = "Monbar_32_Exit";
		break;

		case "Monbar_32_Exit":
			AddDialogExitQuest("Keys_lagoon_73");
			DialogExit();
		break;

		case "Monbar_33":
			RemoveLandQuestmark_Main(npchar, "Keys_lagoon");
			dialog.text = StringFromKey("Monbar_dialog_58");
			link.l1 = StringFromKey("Monbar_dialog_59");
			link.l1.go = "Monbar_34";
		break;

		case "Monbar_34":
			dialog.text = StringFromKey("Monbar_dialog_60");
			link.l1 = StringFromKey("Monbar_dialog_61");
			link.l1.go = "Monbar_40_exit";
		break;

		case "Monbar_40_exit":
			AddDialogExitQuest("Keys_lagoon_75");
			dialogexit();
		break;

		case "Monbar_41":
			dialog.text = StringFromKey("Monbar_dialog_62");
			link.l1 = StringFromKey("Monbar_dialog_63");
			link.l1.go = "Monbar_42";
		break;

		case "Monbar_42":
			dialog.text = StringFromKey("Monbar_dialog_64");
			link.l1 = StringFromKey("Monbar_dialog_65");
			link.l1.go = "Monbar_43_exit";
		break;

		case "Monbar_43_exit":
			LAi_SetFreeFighter(npchar);
			NextDiag.CurrentNode = "Monbar_second_3";
			AddDialogExitQuest("Keys_lagoon_86");
			DialogExit();
		break;

		case "Monbar_second_3":
			dialog.text = StringFromKey("Monbar_dialog_66");
			link.l1 = StringFromKey("Monbar_dialog_67");
			link.l1.go = "Monbar_second_3_exit";
		break;

		case "Monbar_second_3_exit":
		NextDiag.CurrentNode = "Monbar_second_3";
		dialogexit();
		break;

		case "Monbar_44":
			dialog.text = "";
			link.l1 = StringFromKey("Monbar_dialog_68");
			link.l1.go = "Monbar_45";
		break;

		case "Monbar_45":
			dialog.text = StringFromKey("Monbar_dialog_69");
			link.l1 = StringFromKey("Monbar_dialog_70");
			link.l1.go = "Monbar_45_Exit";
		break;

		case "Monbar_45_Exit":
			AddDialogExitQuest("Keys_lagoon_90");
			DialogExit();
		break;

		case "Monbar_48":
			dialog.text = StringFromKey("Monbar_dialog_71");
			link.l1 = StringFromKey("Monbar_dialog_72");
			link.l1.go = "Monbar_49";
		break;

		case "Monbar_49":
			dialog.text = StringFromKey("Monbar_dialog_73");
			link.l1 = "...";
			link.l1.go = "Monbar_49_exit";
		break;

		case "Monbar_49_exit":
			AddDialogExitQuest("Keys_lagoon_97");
			dialogexit();
		break;

		case "Monbar_49_1":
			dialog.text = "...";
			link.l1 = StringFromKey("Monbar_dialog_74");
			link.l1.go = "Monbar_50";
		break;

		case "Monbar_50":
			dialog.text = StringFromKey("Monbar_dialog_75");
			link.l1 = StringFromKey("Monbar_dialog_76");
			link.l1.go = "Monbar_51";
		break;

		case "Monbar_51":
			dialog.text = StringFromKey("Monbar_dialog_77", pchar);
			link.l1 = StringFromKey("Monbar_dialog_78");
			link.l1.go = "Monbar_52";
		break;

		case "Monbar_52":
			dialog.text = StringFromKey("Monbar_dialog_79", pchar);
			link.l1 = StringFromKey("Monbar_dialog_80");
			link.l1.go = "Monbar_53";
		break;

		case "Monbar_53":
			dialog.text = StringFromKey("Monbar_dialog_81");
			link.l1 = StringFromKey("Monbar_dialog_82");
			link.l1.go = "Monbar_54";
		break;

		case "Monbar_54":
			dialog.text = StringFromKey("Monbar_dialog_83");
			link.l1 = StringFromKey("Monbar_dialog_84");
			link.l1.go = "Monbar_55";
		break;

		case "Monbar_55":
			dialog.text = StringFromKey("Monbar_dialog_85");
			link.l1 = StringFromKey("Monbar_dialog_86", pchar);
			link.l1.go = "Monbar_56";
		break;

		case "Monbar_56":
			dialog.text = StringFromKey("Monbar_dialog_87");
			link.l1 = StringFromKey("Monbar_dialog_88");
			link.l1.go = "Monbar_56_Exit";
		break;

		case "Monbar_56_Exit":
			AddDialogExitQuest("Keys_lagoon_99");
			DialogExit();
		break;

		case "Monbar_60":
			dialog.text = StringFromKey("Monbar_dialog_89");
			link.l1 = StringFromKey("Monbar_dialog_90");
			link.l1.go = "Monbar_61";
		break;

		case "Monbar_61":
			dialog.text = StringFromKey("Monbar_dialog_91");
			link.l1 = StringFromKey("Monbar_dialog_92");
			link.l1.go = "Monbar_62";
		break;

		case "Monbar_62":
			TakeNItemsNotification(pchar, "mortar", 1, "default", "", "");

			dialog.text = StringFromKey("Monbar_dialog_93");
			link.l1 = StringFromKey("Monbar_dialog_94");
			link.l1.go = "Monbar_63";
		break;

		case "Monbar_63":
			dialog.text = StringFromKey("Monbar_dialog_95");
			link.l1 = StringFromKey("Monbar_dialog_96");
			link.l1.go = "Monbar_64";
		break;

		case "Monbar_64":
			TakeNItemsNotification(pchar, "grenade", 5, "default", "", "");
			TakeNItemsNotification(pchar, "petard", 5, "default", "", "");

			dialog.text = StringFromKey("Monbar_dialog_97");
			link.l1 = StringFromKey("Monbar_dialog_98", pchar);
			link.l1.go = "Monbar_65";
		break;

		case "Monbar_65":
			TakeNItemsNotification(pchar, "recipe_grenade", 1, "default", "", "");
			TakeNItemsNotification(pchar, "recipe_petard", 1, "default", "", "");

			dialog.text = StringFromKey("Monbar_dialog_99", pchar);
			link.l1 = StringFromKey("Monbar_dialog_100", pchar);
			link.l1.go = "Monbar_66";
		break;

		case "Monbar_66":
			dialog.text = StringFromKey("Monbar_dialog_101");
			link.l1 = "...";
			link.l1.go = "Monbar_66_Exit";
		break;

		case "Monbar_66_Exit":
			AddDialogExitQuest("Keys_lagoon_107");
			DialogExit();
		break;

		case "Monbar_Tost":
			CharacterTurnByChr(npchar, pchar);
			dialog.text = StringFromKey("Monbar_dialog_102");
			link.l1 = "...";
			link.l1.go = "Monbar_Tost_Exit";
		break;

		case "Monbar_Tost_Exit":
			StartInstantDialogNow("Etien_Marso", "Marso_Tost", "Quest\LeBasque\Marso_dialog.c", true);
		break;

		case "Keys_lagoon_Inspection_1":
			dialog.text = StringFromKey("Monbar_dialog_103", pchar.name);
			link.l1 = StringFromKey("Monbar_dialog_104");
			link.l1.go = "Keys_lagoon_Inspection_2";
		break;

		case "Keys_lagoon_Inspection_2":
			dialog.text = StringFromKey("Monbar_dialog_105");
			link.l1 = StringFromKey("Monbar_dialog_106");
			link.l1.go = "Keys_lagoon_Inspection_3";
		break;

		case "Keys_lagoon_Inspection_3":
			dialog.text = StringFromKey("Monbar_dialog_107");
			link.l1 = StringFromKey("Monbar_dialog_108");
			link.l1.go = "Keys_lagoon_Inspection_4";
		break;

		case "Keys_lagoon_Inspection_4":
			dialog.text = StringFromKey("Monbar_dialog_109");
			link.l1 = StringFromKey("Monbar_dialog_110", pchar);
			link.l1.go = "Keys_lagoon_Inspection_5";
		break;

		case "Keys_lagoon_Inspection_5":
			dialog.text = StringFromKey("Monbar_dialog_111");
			link.l1 = StringFromKey("Monbar_dialog_112");
			link.l1.go = "Keys_lagoon_Inspection_5_Exit";
		break;

		case "Keys_lagoon_Inspection_5_Exit":
			DialogExit();
			QuestPointerDelLoc("Maracaibo_town", "reload", "gate_back");
			pchar.questTemp.AoP.KeysLagoonMaracaibo.Jungle = true;
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Monbar_67":
			dialog.text = StringFromKey("Monbar_dialog_113");
			link.l1 = "...";
			link.l1.go = "Monbar_67_Exit";
		break;

		case "Monbar_67_Exit":
			StartInstantDialogNow("Mishel_le_Bask", "Keys_lagoon_80", "Quest\LeBasque\LeBasque_dialog.c", true);
		break;

		case "Monbar_71":
			sld = CharacterFromID("Daniel_Monbar");
			LAi_ActorTurnToLocator(sld, "rld", "aloc5");
			dialog.text = StringFromKey("Monbar_dialog_114");
			link.l1 = "...";
			link.l1.go = "Monbar_71_exit";
		break;

		case "Monbar_71_exit":
			AddDialogExitQuest("Keys_lagoon_206");
			dialogexit();
		break;

		case "Monbar_72_3":
			dialog.text = "...";
			link.l1 = StringFromKey("Monbar_dialog_115");
			link.l1.go = "Monbar_72_3_Exit";
		break;

		case "Monbar_72_3_Exit":
			AddDialogExitQuest("Keys_lagoon_274");
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = "first time";
			DialogExit();
		break;

	}
}
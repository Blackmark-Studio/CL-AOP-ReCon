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
        case "Royal_jackpot_1":
            dialog.text = "...";
            link.l1 = StringFromKey("Olone_dialog_1");
            link.l1.go = "Royal_jackpot_2";
        break;

        case "Royal_jackpot_2":
            dialog.text = StringFromKey("Olone_dialog_2");
            link.l1 = "...";
            link.l1.go = "Royal_jackpot_2_exit";
        break;

        case "Royal_jackpot_2_exit":
        AddDialogExitQuest("Royal_jackpot_15");
        dialogexit();
        break;

        case "Mass_dialog_10":
			dialog.text = "...";
			link.l1 = StringFromKey("Olone_dialog_3");
			link.l1.go = "Mass_dialog_11";
		break;

		case "Mass_dialog_11":
            dialog.text = StringFromKey("Olone_dialog_4");
            link.l1 = "...";
            link.l1.go = "Mass_dialog_11_exit";
        break;

        case "Mass_dialog_11_exit":
			AddDialogExitQuest("Royal_jackpot_33");
			dialogexit();
		break;

		case "Deck_royal_dialog_1":
			RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("Olone_dialog_5");
			link.l1 = StringFromKey("Olone_dialog_6");
			link.l1.go = "Deck_royal_dialog_2";
		break;

		case "Deck_royal_dialog_2":
			dialog.text = StringFromKey("Olone_dialog_7");
			link.l1 = StringFromKey("Olone_dialog_8");
			link.l1.go = "Deck_royal_dialog_2_exit";
		break;

        case "Deck_royal_dialog_2_exit":
        	NextDiag.CurrentNode = "Deck_royal_dialog_second";
			dialogexit();
		break;

        case "Deck_royal_dialog_second":
			dialog.text = StringFromKey("Olone_dialog_9");
			link.l1 = StringFromKey("Olone_dialog_10");
			link.l1.go = "Deck_royal_dialog_2_exit";
		break;

		case "Deck_royal_dialog_4":
			dialog.text = "...";
			link.l1 = StringFromKey("Olone_dialog_11");
			link.l1.go = "Deck_royal_dialog_4_exit";
		break;

        case "Deck_royal_dialog_4_exit":
			AddDialogExitQuest("Royal_jackpot_50");
			dialogexit();
		break;

		case "Olone_Bay_Walk":
			RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("Olone_dialog_12");
			link.l1 = StringFromKey("Olone_dialog_13");
			link.l1.go = "Olone_Bay_Walk_exit";
		break;

		case "Olone_Bay_Walk_exit":
			NextDiag.CurrentNode = "Olone_Bay_Walk";
			dialogexit();
		break;

		case "Olone_Bay_Walk_1":
			RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("Olone_dialog_14");
			link.l1 = StringFromKey("Olone_dialog_15");
			link.l1.go = "Olone_Bay_Walk_1_exit";
		break;

		case "Olone_Bay_Walk_1_exit":
			NextDiag.CurrentNode = "Olone_Bay_Walk_1";
			DialogExit();
		break;

		case "Olone_Bay_Walk_2":
			RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("Olone_dialog_16", pchar.lastname);
			link.l1 = StringFromKey("Olone_dialog_17");
			link.l1.go = "Olone_Bay_Walk_2_exit";
		break;

		case "Olone_Bay_Walk_2_exit":
			NextDiag.CurrentNode = "Olone_Bay_Walk_2";
			DialogExit();
		break;

		case "Royal_jackpot_3":
			dialog.text = StringFromKey("Olone_dialog_18");
			link.l1 = StringFromKey("Olone_dialog_19");
			link.l1.go = "Royal_jackpot_4_exit";
		break;

		case "Royal_jackpot_4_exit":
			AddDialogExitQuest("Royal_jackpot_62");
			DialogExit();
		break;

		case "Royal_jackpot_5":
			AoP_RoyalDeckDialogTurn("Fransua_Olone", "Mishel_le_Bask");
			dialog.text = StringFromKey("Olone_dialog_20");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_5_exit";
		break;

		case "Royal_jackpot_5_exit":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_17";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			DialogExit();
		break;

		case "Royal_jackpot_6":
			AoP_RoyalDeckDialogTurn("Fransua_Olone", "Mishel_le_Bask");
			dialog.text = StringFromKey("Olone_dialog_21");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_6_exit";
		break;

		case "Royal_jackpot_6_exit":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_18";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			DialogExit();
		break;

		case "Royal_jackpot_7":
			AoP_RoyalDeckDialogTurn("Fransua_Olone", "Mishel_le_Bask");
			dialog.text = StringFromKey("Olone_dialog_22");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_7_exit";
		break;

		case "Royal_jackpot_7_exit":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_23";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			DialogExit();
		break;

		case "Royal_jackpot_8":
			dialog.text = "...";
			link.l1 = StringFromKey("Olone_dialog_23");
			link.l1.go = "Royal_jackpot_9";
		break;

		case "Royal_jackpot_9":
			dialog.text = StringFromKey("Olone_dialog_24");
			link.l1 = StringFromKey("Olone_dialog_25");
			link.l1.go = "Royal_jackpot_10";
		break;

		case "Royal_jackpot_10":
			dialog.text = StringFromKey("Olone_dialog_26");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_10_exit";
		break;

		case "Royal_jackpot_10_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_160");
		break;

        case "Keys_lagoon_1":
			dialog.text = StringFromKey("Olone_dialog_27");
			link.l1 = StringFromKey("Olone_dialog_28");
			link.l1.go = "Keys_lagoon_ToLeBasque_1";
		break;

		case "Keys_lagoon_ToLeBasque_1":
			StartInstantDialogNow("Mishel_le_Bask", "Keys_lagoon_4", "Quest\Lebasque\LeBasque_dialog.c", true);
		break;

		case "Keys_lagoon_1_1":
			dialog.text = StringFromKey("Olone_dialog_29");
			link.l1 = StringFromKey("Olone_dialog_30");
			link.l1.go = "Keys_lagoon_ToLeBasque_2";
		break;

		case "Keys_lagoon_ToLeBasque_2":
			StartInstantDialogNow("Mishel_le_Bask", "Keys_lagoon_11", "Quest\Lebasque\LeBasque_dialog.c", true);
		break;

		case "Keys_lagoon_Inspection_1":
			dialog.text = StringFromKey("Olone_dialog_31");
			link.l1 = StringFromKey("Olone_dialog_32");
			link.l1.go = "Keys_lagoon_Inspection_2";
		break;

		case "Keys_lagoon_Inspection_2":
			dialog.text = StringFromKey("Olone_dialog_33", pchar.lastname);
			link.l1 = StringFromKey("Olone_dialog_34");
			link.l1.go = "Keys_lagoon_Inspection_3";
		break;

		case "Keys_lagoon_Inspection_3":
			dialog.text = StringFromKey("Olone_dialog_35");
			link.l1 = StringFromKey("Olone_dialog_36");
			link.l1.go = "Keys_lagoon_Inspection_3_Exit";
		break;

		case "Keys_lagoon_Inspection_3_Exit":
			DialogExit();
			QuestPointerDelLoc("Maracaibo_town", "reload", "reload8_back");
			QuestPointerDelLoc("Maracaibo_bank", "reload", "reload2");
			pchar.questTemp.AoP.KeysLagoonMaracaibo.Vault = true;
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Olone_Tost":
			CharacterTurnByChr(npchar, pchar);
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "Olone_Tost_Exit";
		break;

		case "Olone_Tost_Exit":
			StartInstantDialogNow("Mishel_le_Bask", "Keys_lagoon_Aruba_6", "Quest\LeBasque\LeBasque_dialog.c", true);
		break;

		case "Keys_lagoon_2":
			dialog.text = StringFromKey("Olone_dialog_37");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_2_Exit";
		break;

		case "Keys_lagoon_2_Exit":
			StartInstantDialogNow("Mishel_le_Bask", "Keys_lagoon_75", "Quest\LeBasque\LeBasque_dialog.c", true);
		break;

		case "Keys_lagoon_3":
			dialog.text = StringFromKey("Olone_dialog_38");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_3_exit";
		break;

		case "Keys_lagoon_3_exit":
			StartInstantDialogNow("Daniel_Monbar", "Monbar_67", "Quest\LeBasque\Monbar_dialog.c", true);
		break;

		case "Keys_lagoon_4":
			dialog.text = StringFromKey("Olone_dialog_39");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_4_Exit";
		break;

		case "Keys_lagoon_4_Exit":
			StartInstantDialogNow("Mishel_le_Bask", "Keys_lagoon_114_6", "Quest\LeBasque\LeBasque_dialog.c", true);
		break;

		case "Keys_lagoon_4_1":
			dialog.text = StringFromKey("Olone_dialog_40");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_4_1_Exit";
		break;

		case "Keys_lagoon_4_1_Exit":
			StartInstantDialogNow("Mishel_le_Bask", "Keys_lagoon_114_7", "Quest\LeBasque\LeBasque_dialog.c", true);
		break;

        case "Exit":
            NextDiag.CurrentNode = "First time";
            DialogExit();
        break;
    }
}

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

		case "Holiday_Mary_Start":
			RemoveLandQuestmark_Main(npchar, "Royal_jackpot");
			pchar.questTemp.AoP.HolidayTalk.Mary = true;
			dialog.text = StringFromKey("Mary_dialog_1");
			link.l1 = StringFromKey("Mary_dialog_2");
			link.l1.go = "Holiday_Mary_2";
		break;

		case "Holiday_Mary_2":
			dialog.text = StringFromKey("Mary_dialog_3");
			link.l1 = StringFromKey("Mary_dialog_4");
			link.l1.go = "Holiday_Mary_3";
		break;

		case "Holiday_Mary_3":
			dialog.text = StringFromKey("Mary_dialog_5");
			link.l1 = StringFromKey("Mary_dialog_6");
			link.l1.go = "Holiday_Mary_4";
		break;

		case "Holiday_Mary_4":
			dialog.text = StringFromKey("Mary_dialog_7", pchar.name);
			link.l1 = "...";
			link.l1.go = "Holiday_Mary_Exit";
		break;

		case "Holiday_Mary_Exit":
			if (CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Rimalier") && CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Jako") && CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Marso") && CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Mary"))
			{
				LAi_SetActorType(pchar);
				DeleteAttribute(pchar, "questTemp.AoP.HolidayTalk");
				DoQuestCheckDelay("Royal_jackpot_3", 1.0); 
			}
			NextDiag.CurrentNode = "second"; 
			DialogExit();
		break;

		case "second":
			dialog.text = StringFromKey("Mary_dialog_8");
			link.l1 = StringFromKey("Mary_dialog_9");
			link.l1.go = "Holiday_Mary_Exit";
		break;

		case "Mass_dialog_5":
			dialog.text = StringFromKey("Mary_dialog_10");
			link.l1 = StringFromKey("Mary_dialog_11");
			link.l1.go = "Mass_dialog_6";
		break;

		case "Mass_dialog_6":
			dialog.text = StringFromKey("Mary_dialog_12");
			link.l1 = "...";
			link.l1.go = "Mass_dialog_6_exit";
		break;

		case "Mass_dialog_6_exit":
			AddDialogExitQuest("Royal_jackpot_28");
			dialogexit();
		break;

		case "Deck_royal_dialog_1":
			RemoveLandQuestmark_Main(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("Mary_dialog_13");
			link.l1 = StringFromKey("Mary_dialog_14");
			link.l1.go = "Deck_royal_dialog_2";
		break;

        case "Deck_royal_dialog_2":
			dialog.text = StringFromKey("Mary_dialog_15");
			link.l1 = StringFromKey("Mary_dialog_16");
			link.l1.go = "Deck_royal_dialog_3";
		break;

		case "Deck_royal_dialog_3":
			dialog.text = StringFromKey("Mary_dialog_17");

			link.l1 = StringFromKey("Mary_dialog_18");
			link.l1.go = "Deck_royal_dialog_3_leadership_exit";

			link.l2 = StringFromKey("Mary_dialog_19");
			link.l2.go = "Deck_royal_dialog_3_fortune_exit";
		break;

		case "Deck_royal_dialog_3_leadership_exit":
			AddCharacterExpToSkill(pchar, "Leadership", 10);
			AddDialogExitQuest("Royal_jackpot_39");
			NextDiag.CurrentNode = "Deck_royal_dialog_second";
			dialogexit();
		break;

		case "Deck_royal_dialog_3_fortune_exit":
			AddCharacterExpToSkill(pchar, "Fortune", 10);
			AddDialogExitQuest("Royal_jackpot_39");
			NextDiag.CurrentNode = "Deck_royal_dialog_second";
			dialogexit();
		break;

        case "Deck_royal_dialog_second":
			dialog.text = StringFromKey("Mary_dialog_20");
			link.l1 = "...";
			link.l1.go = "Deck_royal_dialog_second_exit";
		break;

		case "Deck_royal_dialog_second_exit":
			dialogexit();
		break;

		case "Mary_Bay_Walk":
			RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("Mary_dialog_21");
			link.l1 = StringFromKey("Mary_dialog_22");
			link.l1.go = "Mary_Bay_Walk_exit";
		break;

		case "Mary_Bay_Walk_exit":
			NextDiag.CurrentNode = "Mary_Bay_Walk";
			dialogexit();
		break;

		case "Mary_Bay_Walk_1":
			RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("Mary_dialog_23");
			link.l1 = StringFromKey("Mary_dialog_24");
			link.l1.go = "Mary_Bay_Walk_1_exit";
		break;

		case "Mary_Bay_Walk_1_exit":
			NextDiag.CurrentNode = "Mary_Bay_Walk_1";
			DialogExit();
		break;

		case "Mary_Bay_Walk_2":
			RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("Mary_dialog_25");
			link.l1 = StringFromKey("Mary_dialog_26");
			link.l1.go = "Mary_Bay_Walk_2_exit";
		break;
		
		case "Mary_Bay_Walk_2_exit":
			NextDiag.CurrentNode = "Mary_Bay_Walk_2";
			DialogExit();
		break;

		case "Royal_jackpot_1":
			dialog.text = StringFromKey("Mary_dialog_27");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_1_exit";
		break;

		case "Royal_jackpot_1_exit":
			AddDialogExitQuest("Royal_jackpot_60");
			DialogExit();
		break;

		case "Royal_jackpot_1_exit":
			AddDialogExitQuest("Royal_jackpot_60");
			dialogexit();
		break;

		case "Royal_jackpot_2":
			dialog.text = StringFromKey("Mary_dialog_28");
			link.l1 = StringFromKey("Mary_dialog_29");
			link.l1.go = "Royal_jackpot_2_exit";
		break;

		case "Royal_jackpot_2_exit":
			AddDialogExitQuest("Royal_jackpot_79");
			DialogExit();
		break;

		case "Royal_jackpot_3":
			dialog.text = StringFromKey("Mary_dialog_30");
			link.l1 = StringFromKey("Mary_dialog_31");
			link.l1.go = "Royal_jackpot_4";
		break;

		case "Royal_jackpot_4":
			dialog.text = StringFromKey("Mary_dialog_32");
			link.l1 = StringFromKey("Mary_dialog_33");
			link.l1.go = "Royal_jackpot_4_exit";
		break;

		case "Royal_jackpot_4_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_81");
		break;

		case "Royal_jackpot_5":
			AoP_RoyalDeckDialogTurn("Mary_Belfler", "Mishel_le_Bask");
			dialog.text = StringFromKey("Mary_dialog_34");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_5_exit";
		break;

		case "Royal_jackpot_5_exit":
			sld = CharacterFromID("Mishel_le_Bask");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "Royal_jackpot_12";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			DialogExit();
		break;

		case "Royal_jackpot_9":
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorTurnToCharacter(sld, characterFromID("Royal_Margarita_Cap"));
			dialog.text = StringFromKey("Mary_dialog_35");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_9_exit";
		break;

		case "Royal_jackpot_9_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_126");
		break;

		case "Royal_jackpot_10":
			sld = CharacterFromID("Mary_Belfler");
			LAi_ActorTurnToCharacter(sld, characterFromID("Royal_Margarita_Cap"));
			dialog.text = StringFromKey("Mary_dialog_36");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_10_exit";
		break;

		case "Royal_jackpot_10_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_131");
		break;

		case "Royal_jackpot_11":
			dialog.text = StringFromKey("Mary_dialog_37");
			link.l1 = StringFromKey("Mary_dialog_38");
			link.l1.go = "Royal_jackpot_11_1";
		break;

		case "Royal_jackpot_11_1":
			dialog.text = StringFromKey("Mary_dialog_39");
			link.l1 = "...";
			link.l1.go = "Royal_jackpot_11_exit";
		break;

		case "Royal_jackpot_11_exit":
			AddDialogExitQuest("Royal_jackpot_149");
			DialogExit();
		break;

		case "Royal_jackpot_12":
			dialog.text = StringFromKey("Mary_dialog_40");
			link.l1 = StringFromKey("Mary_dialog_41");
			link.l1.go = "Royal_jackpot_12_exit";
		break;

		case "Royal_jackpot_12_exit":
			AddDialogExitQuest("Royal_jackpot_154");
			DialogExit();
		break;

		case "Royal_jackpot_final":
			dialog.text = StringFromKey("Mary_dialog_42");
			link.l1 = StringFromKey("Mary_dialog_43");
			link.l1.go = "Royal_jackpot_final_exit";
		break;

		case "Royal_jackpot_final_exit":
			LAi_CharacterDisableDialog(npchar);
			RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
			DialogExit();
		break;

		case "Keys_lagoon_1":
			dialog.text = StringFromKey("Mary_dialog_44");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_1_exit";
		break;

		case "Keys_lagoon_1_exit":
		AddDialogExitQuest("Keys_lagoon_14");
			dialogexit();
		break;

		case "Keys_lagoon_1_1":
			dialog.text = StringFromKey("Mary_dialog_45");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_1_1_exit";
		break;

		case "Keys_lagoon_1_1_exit":
			AddDialogExitQuest("Keys_lagoon_13");
			dialogexit();
		break;

		case "Keys_lagoon_2":
			dialog.text = StringFromKey("Mary_dialog_46");
			link.l1 = StringFromKey("Mary_dialog_47");
			link.l1.go = "Keys_lagoon_3_exit";
		break;

		case "Keys_lagoon_3_exit":
		AddDialogExitQuest("Keys_lagoon_16");
			dialogexit();
		break;

		case "Keys_lagoon_4":
			dialog.text = StringFromKey("Mary_dialog_48");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_4_exit";
		break;

		case "Keys_lagoon_4_exit":
		AddDialogExitQuest("Keys_lagoon_34");
			dialogexit();
		break;

		case "Keys_lagoon_neitral":
			dialog.text = StringFromKey("Mary_dialog_49");
			link.l1 = StringFromKey("Mary_dialog_50");
			link.l1.go = "Keys_lagoon_neitral_exit";
		break;

		case "Keys_lagoon_neitral_exit":
		NextDiag.CurrentNode = "Keys_lagoon_neitral";
			dialogexit();
		break;

		case "Keys_lagoon_Inspection_1":
			dialog.text = StringFromKey("Mary_dialog_51", pchar.lastname);
			link.l1 = StringFromKey("Mary_dialog_52");
			link.l1.go = "Keys_lagoon_Inspection_2";
		break;

		case "Keys_lagoon_Inspection_2":
			dialog.text = StringFromKey("Mary_dialog_53");
			link.l1 = StringFromKey("Mary_dialog_54");
			link.l1.go = "Keys_lagoon_Inspection_3";
		break;

		case "Keys_lagoon_Inspection_3":
			dialog.text = StringFromKey("Mary_dialog_55");
			link.l1 = StringFromKey("Mary_dialog_56", pchar);
			link.l1.go = "Keys_lagoon_Inspection_4";
		break;

		case "Keys_lagoon_Inspection_4":
			dialog.text = StringFromKey("Mary_dialog_57");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_Inspection_4_Exit";
		break;

		case "Keys_lagoon_Inspection_4_Exit":
			DialogExit();
			QuestPointerDelLoc("Maracaibo_town", "reload", "reload_jail");
			pchar.questTemp.AoP.KeysLagoonMaracaibo.Prison = true;
			chrDisableReloadToLocation = false;
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Keys_lagoon_5":
			dialog.text = StringFromKey("Mary_dialog_58");
			link.l1 = StringFromKey("Mary_dialog_59");
			link.l1.go = "Keys_lagoon_5_exit";
		break;

		case "Keys_lagoon_5_exit":
			NextDiag.CurrentNode = "Keys_lagoon_townhall_repeat";
			AddDialogExitQuest("Keys_lagoon_135");
			DialogExit();
		break;

		case "Keys_lagoon_townhall_repeat":
			dialog.text = StringFromKey("Mary_dialog_60");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_townhall_repeat_exit";
		break;

		case "Keys_lagoon_townhall_repeat_exit":
			NextDiag.CurrentNode = "Keys_lagoon_townhall_repeat";
			dialogexit();
		break;

		case "Keys_lagoon_6":
			dialog.text = StringFromKey("Mary_dialog_61");
			link.l1 = StringFromKey("Mary_dialog_62");
			link.l1.go = "Keys_lagoon_7";
		break;

		case "Keys_lagoon_7":
			dialog.text = StringFromKey("Mary_dialog_63");
			link.l1 = StringFromKey("Mary_dialog_64");
			link.l1.go = "Keys_lagoon_8";
		break;

		case "Keys_lagoon_8":
			dialog.text = StringFromKey("Mary_dialog_65");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_9";
		break;

		case "Keys_lagoon_9":
			dialog.text = StringFromKey("Mary_dialog_66");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_9_exit";
		break;

		case "Keys_lagoon_9_exit":
			AddDialogExitQuest("Keys_lagoon_139");
			dialogexit();
		break;

		case "Keys_lagoon_17":
			dialog.text = StringFromKey("Mary_dialog_67");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_17_exit";
		break;

		case "Keys_lagoon_17_exit":
			NextDiag.CurrentNode = "Keys_lagoon_townhall_repeat_2";
			AddDialogExitQuest("Keys_lagoon_142");
			dialogexit();
		break;

		case "Keys_lagoon_townhall_repeat_2":
			dialog.text = StringFromKey("Mary_dialog_68");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_townhall_repeat_2_exit";
		break;

		case "Keys_lagoon_townhall_repeat_2_exit":
			NextDiag.CurrentNode = "Keys_lagoon_townhall_repeat_2";
			dialogexit();
		break;

		case "Exit":
			NextDiag.CurrentNode = "first time";
			DialogExit();
		break;

	}
}

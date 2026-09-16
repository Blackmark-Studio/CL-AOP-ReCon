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
		// Если нейтральны к Англии
		case "Hollis_friendly_1":
			RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
			dialog.text = StringFromKey("Hollis_dialog_1", pchar.lastname);
			link.l1 = StringFromKey("Hollis_dialog_2");
			link.l1.go = "Hollis_friendly_2";
		break;

		case "Hollis_friendly_2":
			TakeItemFromCharacter(pchar, "spa_lager");
			dialog.text = StringFromKey("Hollis_dialog_3");
			link.l1 = StringFromKey("Hollis_dialog_4");
			link.l1.go = "Hollis_friendly_3";
		break;

		case "Hollis_friendly_3":
			dialog.text = StringFromKey("Hollis_dialog_5");
			link.l1 = StringFromKey("Hollis_dialog_6", pchar);
			link.l1.go = "Hollis_friendly_4";
		break;

		case "Hollis_friendly_4":
			dialog.text = StringFromKey("Hollis_dialog_7");
			link.l1 = StringFromKey("Hollis_dialog_8");
			link.l1.go = "Hollis_friendly_5";
		break;

		case "Hollis_friendly_5":
			dialog.text = StringFromKey("Hollis_dialog_9");
			link.l1 = StringFromKey("Hollis_dialog_10");
			link.l1.go = "Hollis_friendly_5_exit";
		break;

		case "Hollis_friendly_5_exit":
			AddDialogExitQuest("Hunting_huntsman_76");
			LAi_CharacterDisableDialog(npchar);
			dialogexit();
		break;

		// Если вражда с Англией
		case "Hollis_no_friendly_1":
			RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
			dialog.text = StringFromKey("Hollis_dialog_11", pchar);
			link.l1 = StringFromKey("Hollis_dialog_12");
			link.l1.go = "Hollis_no_friendly_2";
		break;

		case "Hollis_no_friendly_2":
			TakeItemFromCharacter(pchar, "spa_lager");
			dialog.text = StringFromKey("Hollis_dialog_13");
			link.l1 = StringFromKey("Hollis_dialog_14");
			link.l1.go = "Hollis_no_friendly_3";
		break;

		case "Hollis_no_friendly_3":
			dialog.text = StringFromKey("Hollis_dialog_15");
			link.l1 = StringFromKey("Hollis_dialog_16");
			link.l1.go = "Hollis_no_friendly_4";
		break;

		case "Hollis_no_friendly_4":
			dialog.text = StringFromKey("Hollis_dialog_17");
			link.l1 = StringFromKey("Hollis_dialog_18");
			link.l1.go = "Hollis_no_friendly_5";
		break;

		case "Hollis_no_friendly_5":
			dialog.text = StringFromKey("Hollis_dialog_19");
			link.l1 = StringFromKey("Hollis_dialog_20");
			link.l1.go = "Hollis_no_friendly_5_exit";
		break;

		case "Hollis_no_friendly_5_exit":
			AddDialogExitQuest("Hunting_huntsman_76");
			LAi_CharacterDisableDialog(npchar);
			dialogexit();
		break;

		case "Hunting_huntsman_1":
			RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
			dialog.text = StringFromKey("Hollis_dialog_21");
			link.l1 = StringFromKey("Hollis_dialog_22");
			link.l1.go = "Hunting_huntsman_2";
		break;

		case "Hunting_huntsman_2":
			dialog.text = StringFromKey("Hollis_dialog_23");
			link.l1 = StringFromKey("Hollis_dialog_24");
			link.l1.go = "Hunting_huntsman_3";
		break;

		case "Hunting_huntsman_3":
			PlaySound("People Fight\MusketFire2.wav");
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "Hunting_huntsman_4";
		break;

		case "Hunting_huntsman_4":
			PlaySound("People Fight\Boarding_People_01.wav");
			dialog.text = StringFromKey("Hollis_dialog_25");
			link.l1 = StringFromKey("Hollis_dialog_26");
			link.l1.go = "Hunting_huntsman_4_exit";
		break;

		case "Hunting_huntsman_4_exit":
			AddDialogExitQuest("Hunting_huntsman_81");
			dialogexit();
		break;

		case "Hunting_huntsman_5":
			dialog.text = StringFromKey("Hollis_dialog_27");
			link.l1 = StringFromKey("Hollis_dialog_28");
			link.l1.go = "Hunting_huntsman_6";
		break;

		case "Hunting_huntsman_6":
			dialog.text = StringFromKey("Hollis_dialog_29");
			link.l1 = StringFromKey("Hollis_dialog_30");
			link.l1.go = "Hunting_huntsman_6_exit";
		break;

		case "Hunting_huntsman_6_exit":
			AddDialogExitQuest("Hunting_huntsman_96");
			dialogexit();
		break;

		case "Exit":
			NextDiag.CurrentNode = "first time";
			DialogExit();
		break;

	}
}
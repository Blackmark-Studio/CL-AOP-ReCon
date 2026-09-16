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
			dialog.text = StringFromKey("Start_dialog_9");
			link.l1 = StringFromKey("Start_dialog_10");
			link.l1.go = "dialog_1";
		break;

		case "dialog_1":
			dialog.text = StringFromKey("Start_dialog_11");
			link.l1 = StringFromKey("Start_dialog_12");
			link.l1.go = "dialog_2";
		break;

		case "dialog_2":
			dialog.text = StringFromKey("Start_dialog_13");
			link.l1 = StringFromKey("Start_dialog_14");
			link.l1.go = "dialog_3";
		break;

		case "dialog_3":
			dialog.text = StringFromKey("Start_dialog_15");
			link.l1 = StringFromKey("Start_dialog_16");
			link.l1.go = "dialog_4";
		break;

		case "dialog_4":
			dialog.text = StringFromKey("Start_dialog_17");
			link.l1 = "...";
			link.l1.go = "dialog_4_exit";
		break;

		case "dialog_4_exit":
			sld = characterFromId("Startaper_1");
			LAi_SetActorType(sld);
			RemoveLandQuestmark_Main(sld, "Shadow_of_a_big_deal");
			LAi_ActorRunToLocation(sld, "reload", "reload5_back", "none", "", "", "", -1);
			AddQuestRecord("LeBasque", "0");
			AddDialogExitQuest("Shadow_of_a_big_deal_1");
			dialogexit();
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "Exit":
			NextDiag.CurrentNode = "first time";
			DialogExit();
		break;

	}
}
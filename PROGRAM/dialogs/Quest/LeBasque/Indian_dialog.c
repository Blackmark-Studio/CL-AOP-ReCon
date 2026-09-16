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

		case "Yamai_1":
		RemoveLandQuestmark_Gen(npchar, "Keys_lagoon");
			dialog.text = StringFromKey("Indian_dialog_1");
			link.l1 = StringFromKey("Indian_dialog_2");
			link.l1.go = "Yamai_2";
		break;

		case "Yamai_2":
			dialog.text = StringFromKey("Indian_dialog_3");
			link.l1 = StringFromKey("Indian_dialog_4");
			link.l1.go = "Yamai_2_exit";
		break;

		case "Yamai_Repeat":
			dialog.text = StringFromKey("Indian_dialog_5");
			link.l1 = StringFromKey("Indian_dialog_6");
			link.l1.go = "Yamai_2_exit";
		break;

		case "Yamai_2_exit":
		NextDiag.CurrentNode = "Yamai_Repeat";
			dialogexit();
		break;

		case "Yamai_3":
			dialog.text = StringFromKey("Indian_dialog_7", GetFullName(pchar));
			link.l1 = StringFromKey("Indian_dialog_8", pchar);
			link.l1.go = "Yamai_4";
		break;

		case "Yamai_4":
			dialog.text = StringFromKey("Indian_dialog_9");
			link.l1 = StringFromKey("Indian_dialog_10");
			link.l1.go = "Yamai_4_Exit";
		break;

		case "Yamai_4_Exit":
			AddDialogExitQuest("Keys_lagoon_94");
			dialogexit();
		break;

		case "Exit":
			NextDiag.CurrentNode = "first time";
			DialogExit();
		break;

	}
}
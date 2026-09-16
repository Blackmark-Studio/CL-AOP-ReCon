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
			RemoveLandQuestmark_Main(npchar, "Brides_Tortuga");
			dialog.text = StringFromKey("Loren_dialog_1", pchar.lastname);
			link.l1 = StringFromKey("Loren_dialog_2");
			link.l1.go = "dialog_1";
		break;

		case "dialog_1":
			dialog.text = StringFromKey("Loren_dialog_3");
			link.l1 = StringFromKey("Loren_dialog_4", pchar);
			link.l1.go = "dialog_2";
		break;

		case "dialog_2":
			dialog.text = StringFromKey("Loren_dialog_5");
			link.l1 = StringFromKey("Loren_dialog_6");
			link.l1.go = "dialog_3";
		break;

		case "dialog_3":
			dialog.text = StringFromKey("Loren_dialog_7");
			link.l1 = StringFromKey("Loren_dialog_8");
			link.l1.go = "dialog_4";
		break;

		case "dialog_4":
			dialog.text = StringFromKey("Loren_dialog_9");
			link.l1 = StringFromKey("Loren_dialog_10");
			link.l1.go = "dialog_5";
		break;

		case "dialog_5":
			dialog.text = StringFromKey("Loren_dialog_11");
			link.l1 = "...";
			link.l1.go = "dialog_5_exit";
		break;

		case "dialog_5_exit":
			LAi_CharacterDisableDialog(npchar);
			LAi_SetCitizenType(npchar);
			sld = GetCharacter(NPC_GenerateCharacter("Kid_Brides", "Youngman_2", "man", "man", CB_Rank(), FRANCE, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing(), CB_Pistol(), "unarmed", "", 20);
			CB_Perks(sld);
			sld.dialog.filename = "Quest\Lebasque\Other_dialog.c";
			sld.Dialog.CurrentNode = "Kid_1";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto23");
			AddDialogExitQuest("Brides_Tortuga_5");
			dialogexit();
		break;
	}
}
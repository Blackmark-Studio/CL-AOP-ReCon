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

		case "Vargas_1":
			RemoveLandQuestmark_Main(npchar, "Brides_Tortuga");
			dialog.text = StringFromKey("Vargas_dialog_1", GetFullName(pchar));
			link.l1 = StringFromKey("Vargas_dialog_2");
			link.l1.go = "Vargas_2";
		break;

		case "Vargas_2":
			dialog.text = StringFromKey("Vargas_dialog_3");
			link.l1 = StringFromKey("Vargas_dialog_4");
			link.l1.go = "Vargas_3";
		break;

		case "Vargas_3":
			dialog.text = StringFromKey("Vargas_dialog_5", pchar);
			link.l1 = StringFromKey("Vargas_dialog_6");
			link.l1.go = "Vargas_12_exit";
		break;

		case "Vargas_12_exit":
			dialogexit();
			MakeQuestAutoSave();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "Don_Vargas_Group");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Don_Vargas_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Don_Vargas_Group", LAI_GROUP_PLAYER, true);
			LAi_SetCheckMinHP(npchar, 10, true, "Brides_Tortuga_61"); // скрытое бессмертие
		break;

		case "Vargas_13":
			dialog.text = StringFromKey("Vargas_dialog_7", pchar);
			link.l1 = StringFromKey("Vargas_dialog_8");
			link.l1.go = "Vargas_14";
		break;

		case "Vargas_14":
			dialog.text = StringFromKey("Vargas_dialog_9", pchar);
			link.l1 = StringFromKey("Vargas_dialog_10");
			link.l1.go = "Vargas_14_exit";
		break;

		case "Vargas_14_exit":
			AddDialogExitQuest("Brides_Tortuga_62");
			dialogexit();
		break;

		case "Vargas_16":
			RemoveLandQuestmark_Main(npchar, "Brides_Tortuga");
			dialog.text = StringFromKey("Vargas_dialog_11", pchar);
			link.l1 = StringFromKey("Vargas_dialog_12");
			link.l1.go = "Vargas_17";
		break;

		case "Vargas_17":
			dialog.text = StringFromKey("Vargas_dialog_13", GetFullName(pchar));
			link.l1 = StringFromKey("Vargas_dialog_14");
			link.l1.go = "Vargas_17_exit";
		break;

		case "Vargas_17_exit":
			dialogexit();
			MakeQuestAutoSave();
			LAi_SetImmortal(npchar, false);
			Lai_SetHP(npchar, 250.0, 250.0);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "Don_Vargas_Group");
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("Don_Vargas_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("Don_Vargas_Group", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("Don_Vargas_Group", "Brides_Tortuga_75");
		break;

	}
}
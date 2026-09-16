void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	ref _location;
	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
////////////////////////////////////////////////////////////////////////////////////////////////
// Эммануэль Пардаль: "Первые шаги"			Авторы: Nikk и Sinistra
////////////////////////////////////////////////////////////////////////////////////////////////

		case "First time":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_1");
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "EPL_TFS_Sandro_1":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_21", GetFullName(pchar));
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_22");
			link.l1.go = "EPL_TFS_Sandro_2";
		break;
		
		case "EPL_TFS_Sandro_2":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_23", GetFullName(pchar));
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_24");
			link.l1.go = "EPL_TFS_Sandro_3";
		break;
		
		case "EPL_TFS_Sandro_3":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_25");
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_26");
			link.l1.go = "EPL_TFS_Sandro_Finish";
		break;
		
		case "EPL_TFS_Sandro_Finish":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_27", GetFullName(pchar));
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_28");
			link.l1.go = "EPL_TFS_Sandro_Finish_DlgExit";
			link.l2 = StringFromKey("StartGame_dialog_36");	//переход на советы
			link.l2.go = "Advice_1";
		break;
		
		//советы -->
		case "Advice_1":
			dialog.text = StringFromKey("StartGame_dialog_37");
			link.l1 = StringFromKey("StartGame_dialog_38");
			link.l1.go = "Advice_2";
			link.l2 = StringFromKey("Smuggler_Ship_dialog_5");
			link.l2.go = "EPL_TFS_Sandro_Finish_DlgExit";
		break;

		case "Advice_2":
			dialog.text = StringFromKey("StartGame_dialog_40");
			link.l1 = StringFromKey("StartGame_dialog_41");
			link.l1.go = "Advice_3";
			link.l2 = StringFromKey("Smuggler_Ship_dialog_5");
			link.l2.go = "EPL_TFS_Sandro_Finish_DlgExit";
		break;

		case "Advice_3":
			dialog.text = StringFromKey("StartGame_dialog_43");
			link.l1 = StringFromKey("StartGame_dialog_44");
			link.l1.go = "Advice_4";
			link.l2 = StringFromKey("Smuggler_Ship_dialog_5");
			link.l2.go = "EPL_TFS_Sandro_Finish_DlgExit";
		break;

		case "Advice_4":
			dialog.text = StringFromKey("StartGame_dialog_46");
			link.l1 = StringFromKey("StartGame_dialog_47");
			link.l1.go = "Advice_5";
			link.l2 = StringFromKey("Smuggler_Ship_dialog_5");
			link.l2.go = "EPL_TFS_Sandro_Finish_DlgExit";
		break;

		case "Advice_5":
			dialog.text = StringFromKey("StartGame_dialog_49");
			link.l1 = StringFromKey("StartGame_dialog_50");
			link.l1.go = "Advice_6";
			link.l2 = StringFromKey("Smuggler_Ship_dialog_5");
			link.l2.go = "EPL_TFS_Sandro_Finish_DlgExit";
		break;

		case "Advice_6":
			dialog.text = StringFromKey("StartGame_dialog_52");
			link.l1 = StringFromKey("StartGame_dialog_53");
			link.l1.go = "Advice_7";
			link.l2 = StringFromKey("Smuggler_Ship_dialog_5");
			link.l2.go = "EPL_TFS_Sandro_Finish_DlgExit";
		break;

		case "Advice_7":
			dialog.text = StringFromKey("StartGame_dialog_55");
			link.l1 = StringFromKey("StartGame_dialog_56");
			link.l1.go = "Advice_8";
			link.l2 = StringFromKey("Smuggler_Ship_dialog_5");
			link.l2.go = "EPL_TFS_Sandro_Finish_DlgExit";
		break;

		case "Advice_8":
			dialog.text = StringFromKey("StartGame_dialog_58");
			link.l1 = StringFromKey("StartGame_dialog_59");
			link.l1.go = "Advice_9";
			link.l2 = StringFromKey("Smuggler_Ship_dialog_5");
			link.l2.go = "EPL_TFS_Sandro_Finish_DlgExit";
		break;

		case "Advice_9":
			dialog.text = StringFromKey("StartGame_dialog_61");
			link.l1 = StringFromKey("StartGame_dialog_62");
			link.l1.go = "Advice_10";
			link.l2 = StringFromKey("Smuggler_Ship_dialog_5");
			link.l2.go = "EPL_TFS_Sandro_Finish_DlgExit";
		break;

		case "Advice_10":
			dialog.text = StringFromKey("StartGame_dialog_64");
			link.l1 = StringFromKey("Smuggler_Ship_dialog_5");
			link.l1.go = "EPL_TFS_Sandro_Finish_DlgExit";
		break;
		//советы <--
		
		case "EPL_TFS_Sandro_Finish_DlgExit":
			DialogExit();
			AddDialogExitQuestFunction("EPL_TFS_Sandro_DlgExit");
		break;
		
		case "EPL_TFS_Mansfield":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_2");
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_3", GetFullName(pchar));
			link.l1.go = "EPL_TFS_Mansfield_2";
			RemoveLandQuestMark_Main(CharacterFromID("Edward Mansfield"), "EPL_TheFirstSteps");
			RemoveMapQuestMark("LaVega_town", "EPL_TheFirstSteps");
		break;
		
		case "EPL_TFS_Mansfield_2":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_4");
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_5");
			link.l1.go = "EPL_TFS_Mansfield_3";
		break;
		
		case "EPL_TFS_Mansfield_3":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_6");
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_7");
			link.l1.go = "EPL_TFS_Mansfield_4";
		break;
		
		case "EPL_TFS_Mansfield_4":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_8");
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_9");
			link.l1.go = "EPL_TFS_Mansfield_5";
		break;
		
		case "EPL_TFS_Mansfield_5":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_10");
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_11");
			link.l1.go = "EPL_TFS_Mansfield_6";
		break;
		
		case "EPL_TFS_Mansfield_6":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_12");
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_13");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_TFS_TalkedToMansfield");
		break;
		
		case "EPL_TFS_OregonGaskon":
			dialog.text = "";
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_14");
			link.l1.go = "EPL_TFS_OregonGaskon_2";
			TakeItemFromCharacter(pchar, "EPL_TFS_letter");
			RemoveLandQuestMark_Main(CharacterFromID("spa_guber"), "EPL_TheFirstSteps");
			RemoveMapQuestMark("Havana_town", "EPL_TheFirstSteps");
		break;
		
		case "EPL_TFS_OregonGaskon_2":
			sld = CharacterFromID("SantoDomingo_Mayor");
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_15");
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_16", GetFullName(sld));
			link.l1.go = "EPL_TFS_OregonGaskon_3";
			AddMoneyToCharacter(pchar, 5000);
		break;
		
		case "EPL_TFS_OregonGaskon_3":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_17");
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_18");
			link.l1.go = "EPL_TFS_OregonGaskon_5";
		break;
		
		case "EPL_TFS_OregonGaskon_5":
			dialog.text = StringFromKey("EPL_3_TheFirstSteps_dialog_19");
			link.l1 = StringFromKey("EPL_3_TheFirstSteps_dialog_20");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_TFS_TalkedToOregonGaskon");
		break;
	}
}

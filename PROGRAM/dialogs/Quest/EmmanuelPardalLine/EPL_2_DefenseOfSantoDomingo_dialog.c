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
// Эммануэль Пардаль: "Оборона Санто-Доминго"			Авторы: Nikk и Sinistra
////////////////////////////////////////////////////////////////////////////////////////////////

		case "First time":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_1");
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "EPL_DOSD_Officer_u_rezidenta":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_2");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_3");
			link.l1.go = "EPL_DOSD_Officer_u_rezidenta_2";
			RemoveLandQuestmark_Main(npchar, "EPL_Prologue");
		break;
		
		case "EPL_DOSD_Officer_u_rezidenta_2":
			sld = CharacterFromID("SantoDomingo_Mayor");
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_4", GetFullName(sld));
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_5");
			link.l1.go = "EPL_DOSD_Officer_u_rezidenta_3";
		break;
		
		case "EPL_DOSD_Officer_u_rezidenta_3":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_6");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_7");
			link.l1.go = "exit";
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			pchar.questTemp.EPL_DOSD = "Admiralty";
			AddLandQuestMark_Main(CharacterFromID("SantoDomingo_Admiralty"), "EPL_Prologue");
			QuestPointerToLoc("SantoDomingo_town", "reload", "houseA_1");
		break;
		
		case "EPL_DOSD_Gubernator_1":
			dialog.text = "";
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_8");
			link.l1.go = "EPL_DOSD_Gubernator_2";
			RemoveLandQuestmark_Main(npchar, "EPL_Prologue");
		break;
		
		case "EPL_DOSD_Gubernator_2":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_9");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_10");
			link.l1.go = "EPL_DOSD_Gubernator_3";
		break;
		
		case "EPL_DOSD_Gubernator_3":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_11");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_12");
			link.l1.go = "EPL_DOSD_Gubernator_4";
		break;
		
		case "EPL_DOSD_Gubernator_4":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_13");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_14");
			link.l1.go = "EPL_DOSD_Gubernator_5";
		break;
		
		case "EPL_DOSD_Gubernator_5":
			DialogExit();
			StartInstantDialog("EPL_DOSD_Off_Guber_2", "EPL_DOSD_Gubernator_6", "Quest\EmmanuelPardalLine\EPL_2_DefenseOfSantoDomingo_dialog.c");
		break;
		
		case "EPL_DOSD_Gubernator_6":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_15");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_16");
			link.l1.go = "EPL_DOSD_Gubernator_7";
		break;
		
		case "EPL_DOSD_Gubernator_7":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_17");
			link.l1 = "";
			link.l1.go = "EPL_DOSD_Gubernator_8";
			LAi_SetActorType(npchar);
		break;
		
		case "EPL_DOSD_Gubernator_8":
			DialogExit();
			StartInstantDialog("SantoDomingo_Mayor_Clone", "EPL_DOSD_Gubernator_9", "Quest\EmmanuelPardalLine\EPL_2_DefenseOfSantoDomingo_dialog.c");
		break;
		
		case "EPL_DOSD_Gubernator_9":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_18");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_19");
			link.l1.go = "EPL_DOSD_Gubernator_10";
		break;
		
		case "EPL_DOSD_Gubernator_10":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_20");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_21");
			link.l1.go = "EPL_DOSD_Gubernator_11";
		break;
		
		case "EPL_DOSD_Gubernator_11":
			DialogExit();
			StartInstantDialog("EPL_DOSD_Off_Guber_1", "EPL_DOSD_Gubernator_12", "Quest\EmmanuelPardalLine\EPL_2_DefenseOfSantoDomingo_dialog.c");
		break;
		
		case "EPL_DOSD_Gubernator_12":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_22");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_23");
			link.l1.go = "EPL_DOSD_Gubernator_13";
			LAi_SetActorType(npchar);
		break;
		
		case "EPL_DOSD_Gubernator_13":
			DialogExit();
			StartInstantDialog("SantoDomingo_Mayor_Clone", "EPL_DOSD_Gubernator_14", "Quest\EmmanuelPardalLine\EPL_2_DefenseOfSantoDomingo_dialog.c");
		break;
		
		case "EPL_DOSD_Gubernator_14":
			dialog.text = "";
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_24");
			link.l1.go = "EPL_DOSD_Gubernator_15";
		break;
		
		case "EPL_DOSD_Gubernator_15":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_25");
			link.l1 = "";
			link.l1.go = "EPL_DOSD_Gubernator_16";
			LAi_SetActorType(npchar);
		break;
		
		case "EPL_DOSD_Gubernator_16":
			DialogExit();
			
			PChar.quest.EPL_DOSD_OboronaSD.win_condition.l1 = "location";
			PChar.quest.EPL_DOSD_OboronaSD.win_condition.l1.location = "SantoDomingo_ExitTown";
			PChar.quest.EPL_DOSD_OboronaSD.function = "EPL_DOSD_OboronaSD";
			
			AddQuestRecord("EPL_Prologue", "12");
			
			QuestPointerDelLoc("SantoDomingo_town", "reload", "houseA_1");
			QuestPointerToLoc("SantoDomingo_Admiralty", "reload", "reload1_back");
			QuestPointerToLoc("SantoDomingo_town", "reload", "gate_back");
		break;
		
		case "EPL_DOSD_Koten_1":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_26");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_27");
			link.l1.go = "EPL_DOSD_Koten_2";
			RemoveLandQuestmark_Main(npchar, "EPL_Prologue");
		break;
		
		case "EPL_DOSD_Koten_2":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_28");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_29");
			link.l1.go = "EPL_DOSD_Koten_3";
		break;
		
		case "EPL_DOSD_Koten_3":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_30");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_31");
			link.l1.go = "EPL_DOSD_Koten_4";
		break;
		
		case "EPL_DOSD_Koten_4":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_32");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_33");
			link.l1.go = "EPL_DOSD_Koten_5";
		break;
		
		case "EPL_DOSD_Koten_5":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_34");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_35");
			link.l1.go = "EPL_DOSD_Koten_6";
		break;
		
		case "EPL_DOSD_Koten_6":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_36");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_37");
			link.l1.go = "EPL_DOSD_Koten_7";
		break;
		
		case "EPL_DOSD_Koten_7":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_38");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_39");
			link.l1.go = "EPL_DOSD_Koten_8";
		break;
		
		case "EPL_DOSD_Koten_8":
			LAi_Fade("", "");
			dialog.text = "";
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_40");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_DOSD_TalkedToMan");
		break;
		
		case "EPL_DOSD_Gubernator_20":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_41");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_42");
			link.l1.go = "EPL_DOSD_Gubernator_21";
		break;
		
		case "EPL_DOSD_Gubernator_21":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_43");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_44");
			link.l1.go = "EPL_DOSD_Gubernator_22";
		break;
		
		case "EPL_DOSD_Gubernator_22":
			AddMoneyToCharacter(pchar, 30000);
			GiveItem2Character(PChar, "EPL_TFS_letter");
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_45");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_46");
			link.l1.go = "EPL_DOSD_Gubernator_23";
		break;
		
		case "EPL_DOSD_Gubernator_23":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_47");
			link.l1 = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_48");
			link.l1.go = "EPL_DOSD_Gubernator_24";
		break;
		
		case "EPL_DOSD_Gubernator_24":
			dialog.text = StringFromKey("EPL_2_DefenseOfSantoDomingo_dialog_49");
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_TFS_TalkedToHovernorSD");
		break;
	}
}

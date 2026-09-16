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
// Эммануэль Пардаль: "Портниха знатной дамы"			Авторы: Nikk и Sinistra
////////////////////////////////////////////////////////////////////////////////////////////////		
		
		case "First time":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_1");
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		case "EPL_PZD_Pilar_1_1":
			dialog.text = "";
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_2");
			link.l1.go = "EPL_PZD_Pilar_1_2";
			DeleteAttribute(npchar, "talker");
		break;

		case "EPL_PZD_Pilar_1_2":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_3");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_4");
			link.l1.go = "EPL_PZD_Pilar_1_3";
		break;

		case "EPL_PZD_Pilar_1_3":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_5");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_6");
			link.l1.go = "EPL_PZD_Pilar_1_4";
		break;

		case "EPL_PZD_Pilar_1_4":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_7");
			link.l1 = "";
			link.l1.go = "EPL_PZD_Pilar_1_5";
		break;

		case "EPL_PZD_Pilar_1_5":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_8");
			link.l1 = "";
			link.l1.go = "EPL_PZD_Pilar_1_6";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("EPL_PZD_Herineldo"));
		break;

		case "EPL_PZD_Pilar_1_6":
			DialogExit();
			StartInstantDialog("EPL_PZD_Herineldo", "EPL_PZD_Pilar_1_7", "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c");
			sld = CharacterFromID("EPL_PZD_Pilar");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);			
		break;

		case "EPL_PZD_Pilar_1_7":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_9", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_10");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_PZD_PilarDlgExit");
		break;
		
		case "EPL_PZD_MatrosUKostra_1":
			locCameraFromToPos(43.47, 3.58, -6.19, true, 32.50, 0.20, 0.00);
			TeleportCharacterToPosAy(pchar, 39.58, 0.00, -4.80, -0.40);
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_11");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_12");
			link.l1.go = "EPL_PZD_MatrosUKostra_2";
		break;
		
		case "EPL_PZD_MatrosUKostra_2":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_13");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_14");
			link.l1.go = "EPL_PZD_MatrosUKostra_3";
		break;
		
		case "EPL_PZD_MatrosUKostra_3":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_15");
			if (sti(pchar.Money) >= 2000)
			{
				link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_16");
				link.l1.go = "EPL_PZD_MatrosUKostra_4";
			}
			link.l2 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_17");
			link.l2.go = "EPL_PZD_MatrosUKostra_3_0";
		break;
		
		case "EPL_PZD_MatrosUKostra_3_0":
			DialogExit();
			
			sld = CharacterFromID("EPL_PZD_Matros_2");
			sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_4_DressmakerNobleLady_dialog.c";
			sld.dialog.currentnode = "EPL_PZD_MatrosUKostra_3_1";
		break;
		
		case "EPL_PZD_MatrosUKostra_3_1":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_18");
			if (sti(pchar.Money) >= 2000)
			{
				link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_19");
				link.l1.go = "EPL_PZD_MatrosUKostra_4";
			}
			link.l2 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_20");
			link.l2.go = "exit";
			NextDiag.TempNode = "EPL_PZD_MatrosUKostra_3_1";
		break;
		
		case "EPL_PZD_MatrosUKostra_4":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_21");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_22");
			link.l1.go = "EPL_PZD_MatrosUKostra_5";
			RemoveLandQuestmark_Main(npchar, "EPL_PZD");
		break;
		
		case "EPL_PZD_MatrosUKostra_5":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_23");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_24");
			link.l1.go = "EPL_PZD_MatrosUKostra_6";
		break;
		
		case "EPL_PZD_MatrosUKostra_6":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_25");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_26");
			link.l1.go = "EPL_PZD_MatrosUKostra_7";
		break;
		case "EPL_PZD_MatrosUKostra_7":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_27");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_28");
			link.l1.go = "EPL_PZD_MatrosUKostra_8";
		break;
		case "EPL_PZD_MatrosUKostra_8":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_29");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_30");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_PZD_MatrosUKostra_DlgExit");
		break;
		
		case "EPL_PZD_ManBal5":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_31");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_32");
			link.l1.go = "EPL_PZD_ManBal5_2";
		break;
		case "EPL_PZD_ManBal5_2":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_33");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_34");
			link.l1.go = "exit";
			NextDiag.TempNode = "EPL_PZD_ManBal5";
		break;
		
		case "EPL_PZD_WomanBal1":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToAngle(-10.25, 5.49, 36.90, true, 0.20, -1.86);
			TeleportCharacterToPosAy(pchar, -8.28, 3.75, 37.45, -1.75);
			DoQuestFunctionDelay("EPL_PZD_WomanBal_MultiDialog", 0.01);
		break;
		
		case "EPL_PZD_DochGubera":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToAngle(-2.96, 5.46, 37.79, true, 0.14, -0.54);
			TeleportCharacterToPosAy(pchar, -4.35, 3.75, 38.87, 0.40);
			DoQuestFunctionDelay("EPL_PZD_DochGubera_Dialog", 0.01);
		break;

		case "EPL_PZD_ChattyMan":
			DialogExit();
			StartQuestMovie(true, false, true);
			locCameraFromToAngle(0.02, 5.63, 42.73, true, 0.21, 2.67);
			TeleportCharacterToPosAy(pchar, -1.66, 3.75, 38.78, 0.70);
			DoQuestFunctionDelay("EPL_PZD_ChattyMan_MultiDialog", 0.01);
		break;
		
		case "EPL_PZD_IgraVKosti":
			dialog.text = "";
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_35");
			link.l1.go = "EPL_PZD_IgraVKosti_2";
			RemoveLandQuestmark_Main(npchar, "EPL_PZD");
		break;
		
		case "EPL_PZD_IgraVKosti_2":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_36");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_37");
			link.l1.go = "EPL_PZD_IgraVKosti_3";
		break;
		
		case "EPL_PZD_IgraVKosti_3":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_38");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_39");
			link.l1.go = "EPL_PZD_IgraVKosti_4";
		break;
		
		case "EPL_PZD_IgraVKosti_4":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_40");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_41");
			link.l1.go = "EPL_PZD_IgraVKosti_5";
			npchar.money = 10000;
			
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate     = 0;
            pchar.GenQuest.Dice.SitType   = true;			
		break;
		
		case "EPL_PZD_IgraVKosti_5":
			DialogExit();
			LaunchDiceGame();
			
			LAi_CharacterDisableDialog(npchar);
			DoQuestFunctionDelay("EPL_PZD_UbiliVremya", 60.0);
		break;
		
		case "EPL_PZD_GabrielDeSeguensa_11":
			dialog.text = "";
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_42");
			link.l1.go = "EPL_PZD_GabrielDeSeguensa_12";
			RemoveLandQuestmark_Main(npchar, "EPL_PZD");
		break;
		
		case "EPL_PZD_GabrielDeSeguensa_12":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_43");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_44");
			link.l1.go = "EPL_PZD_GabrielDeSeguensa_13";
		break;
		
		case "EPL_PZD_GabrielDeSeguensa_13":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_45");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_46");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_PZD_VGorod");
		break;
		
		case "EPL_PZD_GabrielDeSeguensa_15":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_47");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_48");
			link.l1.go = "EPL_PZD_GabrielDeSeguensa_16";
			notification(StringFromKey("EPL_4_DressmakerNobleLady_dialog_64"), "none");
			locCameraFromToPos(-22.80, 4.61, -68.21, true, -19.10, 2.25, -70.51);
		break;
		
		case "EPL_PZD_GabrielDeSeguensa_16":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_49", pchar.name);
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_50");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_PZD_GabrielDeSeguensa_DlgExit");
		break;
		
		case "EPL_PZD_Sofia_1":
			dialog.text = "";
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_51");
			link.l1.go = "EPL_PZD_Sofia_2";
			RemoveLandQuestmark_Main(npchar, "EPL_PZD");
		break;
		
		case "EPL_PZD_Sofia_2":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_52", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_53");
			link.l1.go = "EPL_PZD_Sofia_3";
		break;
		
		case "EPL_PZD_Sofia_3":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_54");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_55");
			link.l1.go = "EPL_PZD_Sofia_4";
		break;
		
		case "EPL_PZD_Sofia_4":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_56");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_57");
			link.l1.go = "EPL_PZD_Sofia_5";
		break;
		
		case "EPL_PZD_Sofia_5":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_58");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_59");
			link.l1.go = "EPL_PZD_Sofia_6";
		break;
		
		case "EPL_PZD_Sofia_6":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_60");
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_61");
			link.l1.go = "EPL_PZD_Sofia_7";
		break;
		
		case "EPL_PZD_Sofia_7":
			dialog.text = StringFromKey("EPL_4_DressmakerNobleLady_dialog_62", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("EPL_4_DressmakerNobleLady_dialog_63");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_PZD_Final");
		break;

	}
}

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

		case "Arellano_1":
			RemoveLandQuestMark_Main(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("Arelano_dialog_1", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Arelano_dialog_2", pchar);
			link.l1.go = "Arellano_2";
		break;

		case "Arellano_2":
			dialog.text = StringFromKey("Arelano_dialog_3");
			link.l1 = StringFromKey("Arelano_dialog_4");
			link.l1.go = "Arellano_3";
		break;

		case "Arellano_3":
			dialog.text = StringFromKey("Arelano_dialog_5");
			link.l1 = StringFromKey("Arelano_dialog_6");
			link.l1.go = "Arellano_4";
		break;

		case "Arellano_4":
			dialog.text = StringFromKey("Arelano_dialog_7");
			link.l1 = StringFromKey("Arelano_dialog_8");
			link.l1.go = "Arellano_5_exit";
		break;

		case "Arellano_5_exit":
			AddDialogExitQuest("Royal_jackpot_64");
			DialogExit();
		break;

		case "Arellano_Alert_1":
			RemoveLandQuestMark_Main(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("Arelano_dialog_9");
			link.l1 = StringFromKey("Arelano_dialog_10");
			link.l1.go = "Arellano_Alert_2";
		break;

		case "Arellano_Alert_2":
			dialog.text = StringFromKey("Arelano_dialog_11");
			link.l1 = StringFromKey("Arelano_dialog_12");
			link.l1.go = "Arellano_Alert_3";
		break;

		case "Arellano_Alert_3":
			dialog.text = StringFromKey("Arelano_dialog_13");
			link.l1 = StringFromKey("Arelano_dialog_14");
			link.l1.go = "Arellano_Alert_exit";
		break;

		case "Arellano_Alert_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_64");
		break;

		case "Arellano_Alert_Bay_1":
			dialog.text = StringFromKey("Arelano_dialog_15");
			link.l1 = StringFromKey("Arelano_dialog_16");
			link.l1.go = "Arellano_Alert_Bay_2";
		break;

		case "Arellano_Alert_Bay_2":
			dialog.text = StringFromKey("Arelano_dialog_17");
			link.l1 = "...";
			link.l1.go = "Arellano_2_exit";
		break;

		case "Arellano_2_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_71");
		break;

		case "Arellano_6":
			if (CheckAttribute(pchar, "ship.name") && pchar.ship.name == FindPersonalName("Royal_SanJacinto_Cap_ship"))  // To Do - переделать, когда будет пойдут локализации
			{
				dialog.text = StringFromKey("Arelano_dialog_18");
				link.l1 = StringFromKey("Arelano_dialog_19");
			}
			else
			{
				dialog.text = StringFromKey("Arelano_dialog_20", pchar);
				link.l1 = StringFromKey("Arelano_dialog_21");
			}
			link.l1.go = "Arellano_7";
		break;

		case "Arellano_7":
			dialog.text = StringFromKey("Arelano_dialog_22");
			link.l1 = StringFromKey("Arelano_dialog_23");
			link.l1.go = "Arellano_8";
		break;

		case "Arellano_8":
			dialog.text = StringFromKey("Arelano_dialog_24");
			link.l1 = "...";
			link.l1.go = "Arellano_8_exit";
		break;

		case "Arellano_8_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_71");
		break;

		case "Arellano_Alert_Wounded_1":
			RemoveLandQuestMark_Main(npchar, "Royal_jackpot");
			locCameraToPos(2.79, 3.6, -18.9, false);
			locCameraTarget(CharacterFromID("Thomas_Arellano_fake"));
			dialog.text = StringFromKey("Arelano_dialog_25");
			link.l1 = StringFromKey("Arelano_dialog_26");
			link.l1.go = "Arellano_Alert_Wounded_2";
		break;

		case "Arellano_Alert_Wounded_2":
			dialog.text = StringFromKey("Arelano_dialog_27");
			link.l1 = StringFromKey("Arelano_dialog_28");
			link.l1.go = "Arellano_Alert_Wounded_3";
		break;

		case "Arellano_Alert_Wounded_3":
			dialog.text = StringFromKey("Arelano_dialog_29");
			link.l1 = StringFromKey("Arelano_dialog_30");
			link.l1.go = "Arellano_Alert_Wounded_4";
		break;

		case "Arellano_Alert_Wounded_4":
			dialog.text = StringFromKey("Arelano_dialog_31");
			link.l1 = StringFromKey("Arelano_dialog_32");
			link.l1.go = "Arellano_20";
		break;

		case "Arellano_16":
			RemoveLandQuestMark_Main(npchar, "Royal_jackpot");
			locCameraToPos(2.79, 3.6, -18.9, false);
			locCameraTarget(CharacterFromID("Thomas_Arellano_fake"));
			dialog.text = StringFromKey("Arelano_dialog_33");
			link.l1 = StringFromKey("Arelano_dialog_34");
			link.l1.go = "Arellano_17";
		break;

		case "Arellano_17":
			dialog.text = StringFromKey("Arelano_dialog_35");
			link.l1 = StringFromKey("Arelano_dialog_36");
			link.l1.go = "Arellano_18";
		break;

		case "Arellano_18":
			dialog.text = StringFromKey("Arelano_dialog_37");
			link.l1 = StringFromKey("Arelano_dialog_38");
			link.l1.go = "Arellano_19";
		break;

		case "Arellano_19":
			dialog.text = StringFromKey("Arelano_dialog_39");
			link.l1 = StringFromKey("Arelano_dialog_40");
			link.l1.go = "Arellano_20";
		break;

		case "Arellano_20":
			dialog.text = StringFromKey("Arelano_dialog_41");
			link.l1 = "...";
			link.l1.go = "Arellano_21";
		break;

		case "Arellano_21":
			dialog.text = StringFromKey("Arelano_dialog_42");
			link.l1 = StringFromKey("Arelano_dialog_43");
			link.l1.go = "Arellano_22";
		break;

		case "Arellano_22":
			if (!CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.AnnaDebt") &&
			!CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.AnnaPaid"))
			{
				pchar.questTemp.AoP.RoyalJackpot.AnnaDebt = 1;
				SetTimerCondition("Royal_jackpot_AnnaDeadline", 0, 3, 0, false);
				AddQuestRecord("Royal_jackpot_Anna", "0");
			}

			dialog.text = StringFromKey("Arelano_dialog_44");
			link.l1 = StringFromKey("Arelano_dialog_45");
			link.l1.go = "Arellano_23";
		break;

		case "Arellano_23":
			dialog.text = StringFromKey("Arelano_dialog_46");
			link.l1 = StringFromKey("Arelano_dialog_47");
			link.l1.go = "Arellano_24";
		break;

		case "Arellano_24":
			dialog.text = StringFromKey("Arelano_dialog_48");
			link.l1 = StringFromKey("Arelano_dialog_49");
			link.l1.go = "Arellano_25";
		break;

		case "Arellano_25":
			dialog.text = StringFromKey("Arelano_dialog_50");
			link.l1 = "...";
			link.l1.go = "Arellano_26_exit";
		break;

		case "Arellano_26_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_80");
		break;

		case "Exit":
			NextDiag.CurrentNode = "first time";
			DialogExit();
		break;

	}
}

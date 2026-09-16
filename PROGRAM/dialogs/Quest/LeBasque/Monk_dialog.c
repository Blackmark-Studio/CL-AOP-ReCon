void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "Bertran_Waband_First":
			RemoveLandQuestmark_Main(npchar, "Brides_Tortuga");
			dialog.text = StringFromKey("Monk_dialog_1");
			link.l1 = StringFromKey("Monk_dialog_2");
			link.l1.go = "Bertran_Waband_First_2";
		break;

		case "Bertran_Waband_First_2":
			dialog.text = StringFromKey("Monk_dialog_3");
			link.l1 = StringFromKey("Monk_dialog_4");
			link.l1.go = "Bertran_Waband_First_3";
		break;

		case "Bertran_Waband_First_3":
			dialog.text = StringFromKey("Monk_dialog_5");
			npchar.Dialog.CurrentNode = "Bertran_Waband_Main";
			npchar.Dialog.TempNode = "Bertran_Waband_Main";
			if (CheckAttribute(pchar, "questTemp.VargasWound"))
			{
				link.l1 = StringFromKey("Monk_dialog_6");
				link.l1.go = "Bertran_Waband_Heal_1";
				link.l2 = StringFromKey("Monk_dialog_7");
				link.l2.go = "exit";
			}
			else
			{
				link.l1 = StringFromKey("Monk_dialog_8");
				link.l1.go = "exit";
			}
		break;

		case "Bertran_Waband_Main":
			dialog.text = StringFromKey("Monk_dialog_9");
			if (CheckAttribute(pchar, "questTemp.VargasWound"))
			{
				link.l1 = StringFromKey("Monk_dialog_10");
				link.l1.go = "Bertran_Waband_Heal_1";
				link.l2 = StringFromKey("Monk_dialog_11");
				link.l2.go = "Bertran_Waband_Talk_1";
				link.l3 = StringFromKey("Monk_dialog_12");
				link.l3.go = "exit";
			}
			else
			{
				link.l1 = StringFromKey("Monk_dialog_13");
				link.l1.go = "Bertran_Waband_Talk_1";
				link.l2 = StringFromKey("Monk_dialog_14");
				link.l2.go = "exit";
			}
			if (!CheckAttribute(NPChar, "HerbInfo"))
			{
				link.l4 = StringFromKey("Monk_dialog_25");
				link.l4.go = "Bertran_Waband_Talk_Herb_1stTime_1";
			}
			else
			{
				link.l4 = StringFromKey("Monk_dialog_26");
				link.l4.go = "Bertran_Waband_Talk_Herb_1";
			}
		break;

		case "Bertran_Waband_Talk_Herb_1stTime_1":
			NPChar.HerbInfo = "";
			dialog.text = StringFromKey("Monk_dialog_27");
			link.l1 = StringFromKey("Monk_dialog_28");
			link.l1.go = "Bertran_Waband_Talk_Herb_1";
			link.l2 = StringFromKey("Monk_dialog_29");
			link.l2.go = "exit";
		break;

		case "Bertran_Waband_Talk_Herb_1":
			if (CheckAttribute(&TEV, "Bertran_Waband.Herb"))
			{
				dialog.text = StringFromKey("Monk_dialog_30");
				link.l1 = StringFromKey("Monk_dialog_31");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Monk_dialog_32");
				link.l1 = StringFromKey("Monk_dialog_33");
				link.l1.go = "Bertran_Waband_Talk_Herb_Matricaria";
				link.l2 = StringFromKey("Monk_dialog_34");
				link.l2.go = "Bertran_Waband_Talk_Herb_Ginseng";
				link.l3 = StringFromKey("Monk_dialog_35");
				link.l3.go = "Bertran_Waband_Talk_Herb_Zingiber";
				link.l4 = StringFromKey("Monk_dialog_36");
				link.l4.go = "Bertran_Waband_Talk_Herb_All";
				link.l5 = StringFromKey("Monk_dialog_37");
				link.l5.go = "exit";
			}
		break;

		case "Bertran_Waband_Talk_Herb_Matricaria":
			HerbResult("herb_matricaria:10");
		break;

		case "Bertran_Waband_Talk_Herb_Ginseng":
			HerbResult("herb_ginseng:10");
		break;

		case "Bertran_Waband_Talk_Herb_Zingiber":
			HerbResult("herb_zingiber:10");
		break;

		case "Bertran_Waband_Talk_Herb_All":
			HerbResult("herb_matricaria:" + (3 + rand(1)) + ",herb_ginseng:" + (3 + rand(1)) + ",herb_zingiber:" + (3 + rand(1)));
		break;

		case "Bertran_Waband_Talk_1":
			dialog.text = StringFromKey("Monk_dialog_15");
			link.l1 = StringFromKey("Monk_dialog_16");
			link.l1.go = "Bertran_Waband_Talk_2";
		break;

		case "Bertran_Waband_Talk_2":
			dialog.text = StringFromKey("Monk_dialog_17");
			link.l1 = StringFromKey("Monk_dialog_18");
			link.l1.go = "Bertran_Waband_Talk_2_exit";
		break;

		case "Bertran_Waband_Talk_2_exit":
			npchar.Dialog.CurrentNode = "Bertran_Waband_Main";
			dialogexit();
		break;

		case "Bertran_Waband_Heal_1":
			dialog.text = StringFromKey("Monk_dialog_19");
			link.l1 = StringFromKey("Monk_dialog_20");
			link.l1.go = "Bertran_Waband_Heal_2";
		break;

		case "Bertran_Waband_Heal_2":
			dialog.text = StringFromKey("Monk_dialog_21");
			link.l1 = StringFromKey("Monk_dialog_22");
			link.l1.go = "Bertran_Waband_Heal_3";
		break;

		case "Bertran_Waband_Heal_3":
			npchar.Dialog.CurrentNode = "Bertran_Waband_Main";
			npchar.Dialog.TempNode = "Bertran_Waband_Main";
			AddDialogExitQuest("Brides_Tortuga_BertranHeal");
			DialogExit();
		break;

		case "Bertran_Waband_AfterHeal":
			dialog.text = StringFromKey("Monk_dialog_23");
			link.l1 = StringFromKey("Monk_dialog_24");
			link.l1.go = "Bertran_Waband_AfterHeal_exit";
		break;

		case "Bertran_Waband_AfterHeal_exit":
			npchar.Dialog.CurrentNode = "Bertran_Waband_Main";
			npchar.Dialog.TempNode = "Bertran_Waband_Main";
			AddDialogExitQuest("Brides_Tortuga_BertranHeal_3");
			DialogExit();
		break;

		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void HerbResult(string _sResult)
{
	DialogExit();
	TEV.Bertran_Waband.Herb = _sResult;
	SetTimerFunction("Bertran_Waband_Herb_Result", 0, 0, 5 + rand(3));
}
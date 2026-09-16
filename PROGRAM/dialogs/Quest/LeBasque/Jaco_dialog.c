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
        
		case "Old_campfire_1":
			sld = characterFromId("Young_Boy_Bask");
			LAi_ActorTurnToCharacter(sld, characterFromID("Rimalier"));
			dialog.text = StringFromKey("Jaco_dialog_1");
			link.l1 = "...";
			link.l1.go = "Old_campfire_1_exit";
		break;

		case "Old_campfire_1_exit":
			sld = characterFromID("Rimalier");
			sld.Dialog.CurrentNode = "dialog_6";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			dialogexit();
		break;

		case "Old_campfire_2":
			dialog.text = StringFromKey("Jaco_dialog_2");
			link.l1 = StringFromKey("Jaco_dialog_3");
			link.l1.go = "Old_campfire_3";
		break;

		case "Old_campfire_3":
			dialog.text = StringFromKey("Jaco_dialog_4");
			link.l1 = StringFromKey("Jaco_dialog_5");
			link.l1.go = "Old_campfire_4";
		break;

		case "Old_campfire_4":
			dialog.text = StringFromKey("Jaco_dialog_6");
			link.l1 = StringFromKey("Jaco_dialog_7");
			link.l1.go = "Old_campfire_5";
		break;

		case "Old_campfire_5":
			dialog.text = StringFromKey("Jaco_dialog_8");
			link.l1 = StringFromKey("Jaco_dialog_9");
			link.l1.go = "Old_campfire_6";
		break;

		case "Old_campfire_6":
			dialog.text = StringFromKey("Jaco_dialog_10");
			link.l1 = StringFromKey("Jaco_dialog_11");
			link.l1.go = "Old_campfire_7";
		break;

		case "Old_campfire_7":
			dialog.text = StringFromKey("Jaco_dialog_12");
			link.l1 = StringFromKey("Jaco_dialog_13");
			link.l1.go = "Old_campfire_8";
		break;

		case "Old_campfire_8":
			dialog.text = StringFromKey("Jaco_dialog_14");
			link.l1 = StringFromKey("Jaco_dialog_15");
			link.l1.go = "Old_campfire_9";
		break;

		case "Old_campfire_9":
			dialog.text = StringFromKey("Jaco_dialog_16");
			link.l1 = StringFromKey("Jaco_dialog_17");
			link.l1.go = "Old_campfire_10";
		break;

		case "Old_campfire_10":
			dialog.text = StringFromKey("Jaco_dialog_18");
			link.l1 = StringFromKey("Jaco_dialog_19");
			link.l1.go = "Old_campfire_11";
		break;

		case "Old_campfire_11":
			dialog.text = StringFromKey("Jaco_dialog_20");
			link.l1 = "...";
			link.l1.go = "Old_campfire_11_exit";
		break;

		case "Old_campfire_11_exit":
			sld = characterFromID("Rimalier");
			sld.Dialog.CurrentNode = "dialog_24_2";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			dialogexit();
		break;

		case "Old_campfire_12":
			dialog.text = StringFromKey("Jaco_dialog_21");
			link.l1 = StringFromKey("Jaco_dialog_22");
			link.l1.go = "Old_campfire_12_exit";
		break;

		case "Old_campfire_12_exit":
			sld = characterFromID("Etien_Marso");
			sld.Dialog.CurrentNode = "Old_campfire_19";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			dialogexit();
		break;

		case "Hunting_huntsman_1":
			dialog.text = StringFromKey("Jaco_dialog_23");
			link.l1 = StringFromKey("Jaco_dialog_24");
			link.l1.go = "Hunting_huntsman_2";
		break;

		case "Hunting_huntsman_2":
			dialog.text = StringFromKey("Jaco_dialog_25");
			link.l1 = StringFromKey("Jaco_dialog_26");
			link.l1.go = "Hunting_huntsman_3";
		break;

		case "Hunting_huntsman_3":
			dialog.text = StringFromKey("Jaco_dialog_27");
			link.l1 = StringFromKey("Jaco_dialog_28");
			link.l1.go = "Hunting_huntsman_3_exit";
		break;

		case "Hunting_huntsman_3_exit":
			AddDialogExitQuest("Hunting_huntsman_17");
			dialogexit();
		break;

		case "Hunting_huntsman_4":
			sld = characterFromId("Young_Boy_Bask");
			LAi_ActorTurnToCharacter(sld, characterFromID("Etien_Marso"));
			dialog.text = StringFromKey("Jaco_dialog_29");
			link.l1 = "...";
			link.l1.go = "Hunting_huntsman_4_exit";
		break;

		case "Hunting_huntsman_4_exit":
			AddDialogExitQuest("Hunting_huntsman_39");
			dialogexit();
		break;

		case "Hunting_huntsman_5":
			dialog.text = StringFromKey("Jaco_dialog_30", pchar.lastname);
			link.l1 = StringFromKey("Jaco_dialog_31");
			link.l1.go = "Hunting_huntsman_6";
		break;

		case "Hunting_huntsman_6":
			dialog.text = StringFromKey("Jaco_dialog_32");
			link.l1 = StringFromKey("Jaco_dialog_33");
			link.l1.go = "Hunting_huntsman_7";
		break;

		case "Hunting_huntsman_7":
			dialog.text = StringFromKey("Jaco_dialog_34");
			link.l1 = StringFromKey("Jaco_dialog_35");
			link.l1.go = "Hunting_huntsman_8";
		break;

		case "Hunting_huntsman_8":
			dialog.text = StringFromKey("Jaco_dialog_36");
			link.l1 = StringFromKey("Jaco_dialog_37");
			link.l1.go = "Hunting_huntsman_8_exit";
		break;

		case "Hunting_huntsman_8_exit":
			AddDialogExitQuest("Hunting_huntsman_49");
			dialogexit();
		break;

		case "Hunting_huntsman_9":
			RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
			dialog.text = StringFromKey("Jaco_dialog_38");
			link.l1 = StringFromKey("Jaco_dialog_39");
			link.l1.go = "Hunting_huntsman_10";
		break;

		case "Hunting_huntsman_10":
			GiveItem2Character(pchar, "letter_forged");
			dialog.text = StringFromKey("Jaco_dialog_40");
			link.l1 = StringFromKey("Jaco_dialog_41");
			link.l1.go = "Hunting_huntsman_11";
		break;

		case "Hunting_huntsman_11":
			dialog.text = StringFromKey("Jaco_dialog_42");
			link.l1 = StringFromKey("Jaco_dialog_43");
			link.l1.go = "Hunting_huntsman_11_exit";
		break;

		case "Hunting_huntsman_11_exit":
			AddDialogExitQuest("Hunting_huntsman_56");
			dialogexit();
		break;

		case "Hunting_huntsman_12":
			dialog.text = StringFromKey("Jaco_dialog_44", pchar);
			link.l1 = StringFromKey("Jaco_dialog_45");
			link.l1.go = "Hunting_huntsman_13";
		break;

		case "Hunting_huntsman_13":
			dialog.text = StringFromKey("Jaco_dialog_46");
			link.l1 = StringFromKey("Jaco_dialog_47");
			link.l1.go = "Hunting_huntsman_13_exit";
		break;

		case "Hunting_huntsman_13_exit":
			AddDialogExitQuest("Hunting_huntsman_94");
			dialogexit();
		break;

		case "Return_quest_3":
			dialog.text = StringFromKey("Jaco_dialog_48");
			link.l1 = StringFromKey("Jaco_dialog_49");
			link.l1.go = "Return_quest_3_exit";
		break;

		case "Return_quest_3_exit":
			NextDiag.CurrentNode = "Return_quest_3";
			dialogexit();
		break;

		case "Holiday_Jako_Start":
			RemoveLandQuestmark_Main(npchar, "Royal_jackpot");
			pchar.questTemp.AoP.HolidayTalk.Jako = true;
			dialog.text = StringFromKey("Jaco_dialog_50");
			link.l1 = StringFromKey("Jaco_dialog_51");
			link.l1.go = "Holiday_Jako_2";
		break;

		case "Holiday_Jako_2":
			dialog.text = StringFromKey("Jaco_dialog_52");
			link.l1 = StringFromKey("Jaco_dialog_53");
			link.l1.go = "Holiday_Jako_3";
		break;

		case "Holiday_Jako_3":
			dialog.text = StringFromKey("Jaco_dialog_54");
			link.l1 = StringFromKey("Jaco_dialog_55");
			link.l1.go = "Holiday_Jako_Exit";
		break;

		case "Holiday_Jako_Exit":
			if (CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Rimalier") &&
				CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Jako") && 
				CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Marso") && 
				CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Mary"))
			{
				LAi_SetActorType(pchar);
				DeleteAttribute(pchar, "questTemp.AoP.HolidayTalk");
				DoQuestCheckDelay("Royal_jackpot_3", 1.0); 
			}
			NextDiag.CurrentNode = "Holiday_Jako_Second"; 
			DialogExit();
		break;

		case "Holiday_Jako_Second":
			dialog.text = StringFromKey("Jaco_dialog_56");
			link.l1 = StringFromKey("Jaco_dialog_57");
			link.l1.go = "Holiday_Jako_Exit";
		break;

		case "Royal_jackpot_final":
			dialog.text = StringFromKey("Jaco_dialog_58");
			link.l1 = StringFromKey("Jaco_dialog_59");
			link.l1.go = "Royal_jackpot_final_exit";
		break;

		case "Royal_jackpot_final_exit":
			LAi_CharacterDisableDialog(npchar);
			RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
			DialogExit();
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

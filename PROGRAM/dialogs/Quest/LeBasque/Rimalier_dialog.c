#include "DIALOGS\Officer_Common.c"

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessBaseOfficerEvent(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{

	case "dialog_0":
		dialog.text = StringFromKey("Rimalier_dialog_1");
		link.l1 = StringFromKey("Rimalier_dialog_2");
		link.l1.go = "dialog_1";
	break;

	case "dialog_1":
		dialog.text = StringFromKey("Rimalier_dialog_3");
		link.l1 = StringFromKey("Rimalier_dialog_4");
		link.l1.go = "dialog_3";
	break;

	case "dialog_3":
		dialog.text = StringFromKey("Rimalier_dialog_5");
		link.l1 = "...";
		link.l1.go = "dialog_3_exit";
	break;

	case "dialog_3_exit":
		sld = characterFromID("Etien_Marso");
		sld.Dialog.CurrentNode = "Old_campfire_15";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		dialogexit();
	break;

	case "dialog_4":
		dialog.text = StringFromKey("Rimalier_dialog_6");
		link.l1 = StringFromKey("Rimalier_dialog_7");
		link.l1.go = "dialog_5";
	break;

	case "dialog_5":
		dialog.text = StringFromKey("Rimalier_dialog_8");
		link.l1 = "...";
		link.l1.go = "dialog_5_exit";
	break;

	case "dialog_5_exit":
		AddDialogExitQuest("Old_campfire_20");
		dialogexit();
	break;

	case "dialog_6":
		sld = characterFromId("Rimalier");
		LAi_ActorTurnToCharacter(sld, characterFromID("Young_Boy_Bask"));
		dialog.text = StringFromKey("Rimalier_dialog_9");
		link.l1 = "...";
		link.l1.go = "dialog_6_exit";
	break;

	case "dialog_6_exit":
		AddDialogExitQuest("Old_campfire_23");
		dialogexit();
	break;

	case "dialog_7":
		dialog.text = StringFromKey("Rimalier_dialog_10");
		link.l1 = StringFromKey("Rimalier_dialog_11");
		link.l1.go = "dialog_8";
	break;

	case "dialog_8":
		dialog.text = StringFromKey("Rimalier_dialog_12");
		link.l1 = "...";
		link.l1.go = "dialog_10_exit";
	break;

	case "dialog_10_exit":
		AddDialogExitQuest("Old_campfire_24");
		dialogexit();
	break;

	case "dialog_11":
		dialog.text = StringFromKey("Rimalier_dialog_13");
		link.l1 = StringFromKey("Rimalier_dialog_14");
		link.l1.go = "dialog_12";
	break;

	case "dialog_12":
		dialog.text = StringFromKey("Rimalier_dialog_15");
		link.l1 = "...";
		link.l1.go = "dialog_12_exit";
	break;

	case "dialog_12_exit":
		AddDialogExitQuest("Old_campfire_40");
		dialogexit();
		DoQuestFunctionDelay("MakeQuestAutoSaveDelay", 0.5);
	break;

	case "dialog_13":
		dialog.text = StringFromKey("Rimalier_dialog_16");
		link.l1 = StringFromKey("Rimalier_dialog_17", pchar);
		link.l1.go = "dialog_14";
	break;

	case "dialog_14":
		dialog.text = StringFromKey("Rimalier_dialog_18");
		link.l1 = "...";
		link.l1.go = "dialog_15_exit";
	break;

	case "dialog_15_exit":
		AddDialogExitQuest("Old_campfire_41_1");
		dialogexit();
	break;

	case "Joke_1":
		dialog.text = StringFromKey("Rimalier_dialog_19");
		link.l1 = "...";
		link.l1.go = "Joke_2_exit";
	break;

	case "Joke_2_exit":
		AddDialogExitQuest("Old_campfire_42_10");
		dialogexit();
	break;

	case "Joke_3":
		dialog.text = StringFromKey("Rimalier_dialog_20");
		link.l1 = "...";
		link.l1.go = "Joke_3_exit";
	break;

	case "Joke_3_exit":
		sld = characterFromID("Etien_Marso");
		sld.Dialog.CurrentNode = "Joke_3";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		dialogexit();
	break;

	case "Joke_4":
		dialog.text = StringFromKey("Rimalier_dialog_21");
		link.l1 = StringFromKey("Rimalier_dialog_22");
		link.l1.go = "Joke_4_exit";
	break;

	case "Joke_4_exit":
		sld = characterFromID("Etien_Marso");
		sld.Dialog.CurrentNode = "Joke_4";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		dialogexit();
	break;

	case "Joke_4_1":
		dialog.text = StringFromKey("Rimalier_dialog_23");
		link.l1 = StringFromKey("Rimalier_dialog_24");
		link.l1.go = "Joke_5";
	break;

	case "Joke_5":
		dialog.text = StringFromKey("Rimalier_dialog_25");
		link.l1 = StringFromKey("Rimalier_dialog_26");
		link.l1.go = "Joke_6";
	break;

	case "Joke_6":
		dialog.text = StringFromKey("Rimalier_dialog_27");
		link.l1 = StringFromKey("Rimalier_dialog_28");
		link.l1.go = "Joke_6_exit";
	break;

	case "Joke_6_exit":
		AddDialogExitQuest("Old_campfire_42");
		dialogexit();
	break;

	case "dialog_16":
		dialog.text = StringFromKey("Rimalier_dialog_29");
		link.l1 = "...";
		link.l1.go = "dialog_16_exit";
	break;

	case "dialog_16_exit":
		sld = characterFromID("Etien_Marso");
		sld.Dialog.CurrentNode = "Old_campfire_18_1";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		dialogexit();
	break;

	case "dialog_17":
		dialog.text = StringFromKey("Rimalier_dialog_30");
		link.l1 = StringFromKey("Rimalier_dialog_31");
		link.l1.go = "dialog_17_exit";
	break;

	case "dialog_17_exit":
		AddDialogExitQuest("Old_campfire_49");
		dialogexit();
	break;

	case "dialog_18":
		dialog.text = StringFromKey("Rimalier_dialog_32");
		link.l1 = StringFromKey("Rimalier_dialog_33");
		link.l1.go = "dialog_19";
	break;

	case "dialog_19":
		dialog.text = StringFromKey("Rimalier_dialog_34");
		link.l1 = StringFromKey("Rimalier_dialog_35");
		link.l1.go = "dialog_20";
	break;

	case "dialog_20":
		dialog.text = StringFromKey("Rimalier_dialog_36");
		link.l1 = StringFromKey("Rimalier_dialog_37");
		link.l1.go = "dialog_21";
	break;

	case "dialog_21":
		dialog.text = StringFromKey("Rimalier_dialog_38");
		link.l1 = StringFromKey("Rimalier_dialog_39");
		link.l1.go = "dialog_22";
	break;

	case "dialog_22":
		dialog.text = StringFromKey("Rimalier_dialog_40");
		link.l1 = StringFromKey("Rimalier_dialog_41");
		link.l1.go = "dialog_23";
	break;

	case "dialog_23":
		dialog.text = StringFromKey("Rimalier_dialog_42");
		link.l1 = StringFromKey("Rimalier_dialog_43");
		link.l1.go = "dialog_24";
	break;

	case "dialog_24":
		dialog.text = StringFromKey("Rimalier_dialog_44");
		link.l1 = StringFromKey("Rimalier_dialog_45");
		link.l1.go = "dialog_24_1";
	break;

	case "dialog_24_1":
		dialog.text = StringFromKey("Rimalier_dialog_46");
		link.l1 = "...";
		link.l1.go = "dialog_24_1_exit";
	break;

	case "dialog_24_1_exit":
		sld = characterFromID("Young_Boy_Bask");
		sld.Dialog.CurrentNode = "Old_campfire_2";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		dialogexit();
	break;

	case "dialog_24_2":
		dialog.text = StringFromKey("Rimalier_dialog_47");
		link.l1 = StringFromKey("Rimalier_dialog_48");
		link.l1.go = "dialog_24_2_exit";
	break;

	case "dialog_24_2_exit":
		sld = characterFromID("Young_Boy_Bask");
		sld.Dialog.CurrentNode = "Old_campfire_12";
		LAi_ActorDialogNow(sld, pchar, "", -1);
		dialogexit();
	break;

	case "dialog_25":
		dialog.text = StringFromKey("Rimalier_dialog_49");
		link.l1 = "...";
		link.l1.go = "dialog_25_exit";
	break;

	case "dialog_25_exit":
		AddDialogExitQuest("Old_campfire_54");
		dialogexit();
	break;

	case "Go_Officer_1":
		RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
		dialog.text = StringFromKey("Rimalier_dialog_50");
		link.l1 = StringFromKey("Rimalier_dialog_51");
		link.l1.go = "Go_Officer_2";
	break;

	case "Go_Officer_2":
		dialog.text = StringFromKey("Rimalier_dialog_52");
		link.l1 = StringFromKey("Rimalier_dialog_53");
		link.l1.go = "Go_Officer_2_Accept";
		link.l2 = StringFromKey("Rimalier_dialog_54");
		link.l2.go = "Go_Officer_2_Refuse";
	break;

	case "Go_Officer_2_Accept":
		AddMoneyToCharacter(pchar, 5000);
		dialog.text = StringFromKey("Rimalier_dialog_55");
		link.l1 = StringFromKey("Rimalier_dialog_56");
		link.l1.go = "Go_Officer_3";
	break;

	case "Go_Officer_2_Refuse":
		GiveItem2Character(pchar, "recipe_rimalye");
		LogSound_WithNotify(StringFromKey("InfoMessages_240", GetItemName("recipe_rimalye"), 1), "Important_item", "Notebook_1");
		dialog.text = StringFromKey("Rimalier_dialog_57", pchar);
		link.l1 = StringFromKey("Rimalier_dialog_58");
		link.l1.go = "Go_Officer_3";
	break;

	case "Go_Officer_3":
		dialog.text = StringFromKey("Rimalier_dialog_59");
		link.l1 = StringFromKey("Rimalier_dialog_60");
		link.l1.go = "Go_Officer_4";
	break;

	case "Go_Officer_4":
		dialog.text = StringFromKey("Rimalier_dialog_61");
		link.l1 = StringFromKey("Rimalier_dialog_62");
		link.l1.go = "Go_Officer_5";
		link.l2 = StringFromKey("Rimalier_dialog_63", pchar);
		link.l2.go = "No_Officer_1";
	break;

	case "Go_Officer_5":
		dialog.text = StringFromKey("Rimalier_dialog_64");
		link.l1 = StringFromKey("Rimalier_dialog_65");
		link.l1.go = "Go_Officer_6";
	break;

	case "Go_Officer_6":
		dialog.text = StringFromKey("Rimalier_dialog_66");
		link.l1 = StringFromKey("Rimalier_dialog_67");
		link.l1.go = "Go_Officer_6_exit";
		link.l2 = StringFromKey("Rimalier_dialog_68", pchar);
		link.l2.go = "No_Officer_1";
	break;

	case "No_Officer_1":
		dialog.text = StringFromKey("Rimalier_dialog_69");
		link.l1 = StringFromKey("Rimalier_dialog_70");
		link.l1.go = "No_Officer_2";
	break;

	case "No_Officer_2":
		dialog.text = StringFromKey("Rimalier_dialog_71");
		link.l1 = StringFromKey("Rimalier_dialog_72");
		link.l1.go = "No_Officer_3";
	break;

	case "No_Officer_3":
		dialog.text = StringFromKey("Rimalier_dialog_73");
		link.l1 = StringFromKey("Rimalier_dialog_74");
		link.l1.go = "No_Officer_3_exit";
	break;

	case "No_Officer_3_exit":
		AddPassenger(pchar, npchar, false);
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
		AddDialogExitQuest("Hunting_huntsman_19_2");
		dialogexit();
	break;

	case "Go_Officer_6_exit":
		AddDialogExitQuest("Hunting_huntsman_19_1");
		SetCharacterRemovable(npchar, false);
		ChangeCharacterReputation(npchar, 40);
		npchar.AllowedPosts = "fighter";
		npchar.MusketerDistance = 10;
		npchar.loyality = MAX_LOYALITY;
		npchar.CompanionDisable = true;
		TakeNItems(npchar, "Mineral7", 1);
		TakeNItems(npchar, "indian17", 1);
		TakeNItems(npchar, "potionwine", 1);
		AddDialogExitQuestFunction("Rimalier_OfficerHired");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
	break;

		case "Brides_Tortuga_Officer_1":
			dialog.text = StringFromKey("Rimalier_dialog_75");
			link.l1 = StringFromKey("Rimalier_dialog_76");
			link.l1.go = "Brides_Tortuga_Officer_2";
		break;

		case "Brides_Tortuga_Officer_2":
			dialog.text = StringFromKey("Rimalier_dialog_77");
			link.l1 = "...";
			link.l1.go = "Brides_Tortuga_Officer_2_exit";
		break;

		case "Brides_Tortuga_Officer_2_exit":
			LAi_SetOfficerType(npchar);
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialogexit();
		break;

		case "Brides_Tortuga_Officer_No_Officer_1":
			dialog.text = StringFromKey("Rimalier_dialog_78");
			link.l1 = StringFromKey("Rimalier_dialog_79", pchar);
			link.l1.go = "Brides_Tortuga_Officer_No_Officer_2";
		break;

		case "Brides_Tortuga_Officer_No_Officer_2":
			dialog.text = StringFromKey("Rimalier_dialog_80");
			link.l1 = StringFromKey("Rimalier_dialog_81");
			link.l1.go = "Brides_Tortuga_Officer_No_Officer_2_exit";
		break;

		case "Brides_Tortuga_Officer_No_Officer_2_exit":
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			npchar.FreeFighter = true;
			dialogexit();
		break;

		case "Brides_Tortuga_1":
			dialog.text = StringFromKey("Rimalier_dialog_82");
			link.l1 = "...";
			link.l1.go = "Brides_Tortuga_1_exit";
		break;

		case "Brides_Tortuga_1_exit":
			AddDialogExitQuest("Brides_Tortuga_13");
			dialogexit();
		break;

		case "Brides_Tortuga_2":
			dialog.text = StringFromKey("Rimalier_dialog_83");
			link.l1 = StringFromKey("Rimalier_dialog_84");
			link.l1.go = "Brides_Tortuga_2_exit";
		break;

		case "Brides_Tortuga_2_exit":
			AddDialogExitQuest("Brides_Tortuga_19");
			dialogexit();
		break;

		case "Brides_Tortuga_Officer_No_Officer_3":
			dialog.text = StringFromKey("Rimalier_dialog_85");
			link.l1 = StringFromKey("Rimalier_dialog_86");
			link.l1.go = "Brides_Tortuga_Officer_No_Officer_3_exit";
		break;

		case "Brides_Tortuga_Officer_No_Officer_3_exit":
			dialogexit();
		break;

		case "Brides_Tortuga_3":
			dialog.text = "...";
			link.l1 = StringFromKey("Rimalier_dialog_87");
			link.l1.go = "Brides_Tortuga_4";
		break;

		case "Brides_Tortuga_4":
			dialog.text = StringFromKey("Rimalier_dialog_88");
			link.l1 = StringFromKey("Rimalier_dialog_89");
			link.l1.go = "Brides_Tortuga_5";
		break;

		case "Brides_Tortuga_5":
			dialog.text = StringFromKey("Rimalier_dialog_90");
			link.l1 = StringFromKey("Rimalier_dialog_91");
			link.l1.go = "Brides_Tortuga_5_exit";
		break;

		case "Brides_Tortuga_5_exit":
			AddDialogExitQuest("Brides_Tortuga_27");
			dialogexit();
		break;

		case "Brides_Tortuga_6":
			dialog.text = StringFromKey("Rimalier_dialog_92");
			link.l1 = StringFromKey("Rimalier_dialog_93");
			link.l1.go = "Brides_Tortuga_7";
		break;

		case "Brides_Tortuga_7":
			dialog.text = StringFromKey("Rimalier_dialog_94");
			link.l1 = StringFromKey("Rimalier_dialog_95");
			link.l1.go = "Brides_Tortuga_7_exit";
		break;

		case "Brides_Tortuga_7_exit":
			AddDialogExitQuest("Brides_Tortuga_38");
			dialogexit();
		break;

		case "Brides_Tortuga_8":
			dialog.text = StringFromKey("Rimalier_dialog_96");
			link.l1 = StringFromKey("Rimalier_dialog_97");
			link.l1.go = "Brides_Tortuga_9";
		break;

		case "Brides_Tortuga_9":
			dialog.text = StringFromKey("Rimalier_dialog_98");
			link.l1 = StringFromKey("Rimalier_dialog_99", pchar);
			link.l1.go = "Brides_Tortuga_10";
		break;

		case "Brides_Tortuga_10":
			dialog.text = StringFromKey("Rimalier_dialog_100");
			link.l1 = StringFromKey("Rimalier_dialog_101");
			link.l1.go = "Brides_Tortuga_10_exit";
		break;

		case "Brides_Tortuga_10_exit":
			AddDialogExitQuest("Brides_Tortuga_42");
			if (sti(pchar.questTemp.AoP.RimalierWasOfficer) == 1)
			{
			LAi_SetOfficerType(npchar);
			npchar.Dialog.CurrentNode = "Hired";
			npchar.Dialog.TempNode = "Hired";
			}
			else
			{
			DeleteAttribute(npchar, "FreeFighter");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			dialogexit();
		break;

		case "Brides_Tortuga_11":
			dialog.text = StringFromKey("Rimalier_dialog_102");
			link.l1 = StringFromKey("Rimalier_dialog_103");
			link.l1.go = "Brides_Tortuga_12";
		break;

		case "Brides_Tortuga_12":
			dialog.text = StringFromKey("Rimalier_dialog_104");
			link.l1 = StringFromKey("Rimalier_dialog_105");
			link.l1.go = "Brides_Tortuga_13";
		break;

		case "Brides_Tortuga_13":
			dialog.text = StringFromKey("Rimalier_dialog_106");
			link.l1 = StringFromKey("Rimalier_dialog_107", pchar);
			link.l1.go = "Brides_Tortuga_14";
		break;

		case "Brides_Tortuga_14":
			dialog.text = StringFromKey("Rimalier_dialog_108");
			link.l1 = StringFromKey("Rimalier_dialog_109");
			link.l1.go = "Brides_Tortuga_14_exit";
		break;

		case "Brides_Tortuga_14_exit":
			AddDialogExitQuest("Brides_Tortuga_45");
			dialogexit();
		break;

		case "Brides_Tortuga_15":
			dialog.text = StringFromKey("Rimalier_dialog_110", pchar.lastname);
			link.l1 = StringFromKey("Rimalier_dialog_111");
			link.l1.go = "Brides_Tortuga_16";
		break;

		case "Brides_Tortuga_16":
			dialog.text = StringFromKey("Rimalier_dialog_112");
			link.l1 = StringFromKey("Rimalier_dialog_113");
			link.l1.go = "Brides_Tortuga_17";
		break;

		case "Brides_Tortuga_17":
			dialog.text = StringFromKey("Rimalier_dialog_114");
			link.l1 = StringFromKey("Rimalier_dialog_115");
			link.l1.go = "Brides_Tortuga_18_1";
		break;

		case "Brides_Tortuga_18_1":
			dialog.text = StringFromKey("Rimalier_dialog_116");
			link.l1 = StringFromKey("Rimalier_dialog_117");
			link.l1.go = "Brides_Tortuga_18";
		break;

		case "Brides_Tortuga_18":
			dialog.text = StringFromKey("Rimalier_dialog_118");
			link.l1 = StringFromKey("Rimalier_dialog_119");
			link.l1.go = "Brides_Tortuga_19";
		break;

		case "Brides_Tortuga_19":
			dialog.text = StringFromKey("Rimalier_dialog_120");
			link.l1 = StringFromKey("Rimalier_dialog_121", pchar);
			link.l1.go = "Brides_Tortuga_20";
		break;

		case "Brides_Tortuga_20":
			dialog.text = StringFromKey("Rimalier_dialog_122");
			link.l1 = StringFromKey("Rimalier_dialog_123", pchar);
			link.l1.go = "Brides_Tortuga_21";
			link.l2 = StringFromKey("Rimalier_dialog_124");
			link.l2.go = "Brides_Tortuga_Sword";
		break;

		case "Brides_Tortuga_21":
			dialog.text = StringFromKey("Rimalier_dialog_125");
			link.l1 = StringFromKey("Rimalier_dialog_126");
			link.l1.go = "Brides_Tortuga_Sword";
		break;

		case "Brides_Tortuga_Sword":
			TakeNItemsNotification(pchar, "BladeBone", 1, "default", "", ""); 
			dialog.text = StringFromKey("Rimalier_dialog_127");
			link.l1 = StringFromKey("Rimalier_dialog_128");
			link.l1.go = "Brides_Tortuga_22";
		break;

		case "Brides_Tortuga_22":
			dialog.text = StringFromKey("Rimalier_dialog_129");
			link.l1 = StringFromKey("Rimalier_dialog_130");
			link.l1.go = "Brides_Tortuga_23_exit";
		break;

		case "Brides_Tortuga_23_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Brides_Tortuga_84", -1);
		break;

		case "Holiday_Start":
			RemoveLandQuestmark_Main(npchar, "Royal_jackpot");
			pchar.questTemp.AoP.HolidayTalk.Rimalier = true;
			if (CheckAttribute(pchar, "questTemp.AoP.RimalierWasOfficer"))
			{
				dialog.text = StringFromKey("Rimalier_dialog_131");
				link.l1 = StringFromKey("Rimalier_dialog_132");
				link.l1.go = "Rimalier_Holiday_Officer_2";
			}
			else
			{
				dialog.text = StringFromKey("Rimalier_dialog_133");
				link.l1 = StringFromKey("Rimalier_dialog_134");
				link.l1.go = "Rimalier_Holiday_2";
			}
		break;

		case "Rimalier_Holiday_2":
			dialog.text = StringFromKey("Rimalier_dialog_135");
			link.l1 = StringFromKey("Rimalier_dialog_136");
			link.l1.go = "Rimalier_Holiday_Common_exit";
		break;

		case "Rimalier_Holiday_Officer_2":
			dialog.text = StringFromKey("Rimalier_dialog_137");
			link.l1 = StringFromKey("Rimalier_dialog_138");
			link.l1.go = "Rimalier_Holiday_Common_exit";
		break;

		case "Rimalier_Holiday_3_exit":
			NextDiag.CurrentNode = "Rimalier_Holiday_second";
			dialogexit();
		break;

		case "Rimalier_Holiday_Common_exit":
			if (CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Rimalier") &&
				CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Jako") &&
				CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Marso") &&
				CheckAttribute(pchar, "questTemp.AoP.HolidayTalk.Mary"))
			{
				LAi_SetActorType(pchar);
				DeleteAttribute(pchar, "questTemp.AoP.HolidayTalk");
				DoQuestCheckDelay("Royal_jackpot_3", 1.0);
			}
			NextDiag.CurrentNode = "Rimalier_Holiday_second";
			DialogExit();
		break;

		case "Rimalier_Holiday_second":
			dialog.text = StringFromKey("Rimalier_dialog_139");
			link.l1 = StringFromKey("Rimalier_dialog_140");
			link.l1.go = "Rimalier_Holiday_3_exit";
		break;

		case "Rimalier_Holiday_Officer_2":
			dialog.text = StringFromKey("Rimalier_dialog_141");
			link.l1 = StringFromKey("Rimalier_dialog_142");
			link.l1.go = "Rimalier_Holiday_Officer_3";
		break;

		case "Rimalier_Holiday_Officer_3":
			dialog.text = StringFromKey("Rimalier_dialog_143");
			link.l1 = StringFromKey("Rimalier_dialog_144");
			link.l1.go = "Rimalier_Holiday_Common_exit";
		break;

		case "Keys_lagoon_1":
			dialog.text = StringFromKey("Rimalier_dialog_145");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_1_exit";
		break;

		case "Keys_lagoon_1_exit":
			AddDialogExitQuest("Keys_lagoon_8");
			dialogexit();
		break;

		case "Royal_jackpot_final":
			dialog.text = StringFromKey("Rimalier_dialog_146");
			link.l1 = StringFromKey("Rimalier_dialog_147");
			link.l1.go = "Royal_jackpot_final_exit";
		break;

		case "Royal_jackpot_final_exit":
			LAi_CharacterDisableDialog(npchar);
			RemoveLandQuestMark_Gen(npchar, "Royal_jackpot");
			dialogexit();
		break;

		case "Keys_lagoon_neitral":
			dialog.text = StringFromKey("Rimalier_dialog_148");
			link.l1 = StringFromKey("Rimalier_dialog_149");
			link.l1.go = "Keys_lagoon_neitral_exit";
		break;

		case "Keys_lagoon_neitral_exit":
			NextDiag.CurrentNode = "Keys_lagoon_neitral";
			dialogexit();
		break;

		case "Keys_lagoon_2":
			dialog.text = StringFromKey("Rimalier_dialog_150");
			link.l1 = StringFromKey("Rimalier_dialog_151");
			link.l1.go = "Keys_lagoon_3";
		break;

		case "Keys_lagoon_3":
			dialog.text = StringFromKey("Rimalier_dialog_152");
			link.l1 = StringFromKey("Rimalier_dialog_153");
			link.l1.go = "Keys_lagoon_4";
		break;

		case "Keys_lagoon_4":
			dialogexit();

			sld = CharacterFromID("Rimalier");

			if (IsOfficer(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.CurrentNode = "Hired";
				sld.Dialog.TempNode = "Hired";
			}
			else
			{
				LAi_SetFreeFighter(sld);
				sld.Dialog.CurrentNode = "Keys_lagoon_neitral";
			}
		break;

		case "Keys_lagoon_5":
			LAi_ActorTurnToLocator(npchar, "goto", "goto_dozor");
			dialog.text = StringFromKey("Rimalier_dialog_154");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_5_exit";
		break;

		case "Keys_lagoon_5_exit":
			AddDialogExitQuest("Keys_lagoon_81");
			dialogexit();
		break;

		case "Keys_lagoon_6_Officer":
			dialog.text = StringFromKey("Rimalier_dialog_155");
			link.l1 = StringFromKey("Rimalier_dialog_156");
			link.l1.go = "Keys_lagoon_6_Officer_Exit";
		break;

		case "Keys_lagoon_6_Officer_Exit":
			AddDialogExitQuest("Keys_lagoon_279");
			DialogExit();
		break;

		case "Keys_lagoon_6_NoOfficer":
			dialog.text = "...";
			link.l1 = StringFromKey("Rimalier_dialog_157");
			link.l1.go = "Keys_lagoon_6_NoOfficer_Exit";
		break;

		case "Keys_lagoon_6_NoOfficer_Exit":
			AddDialogExitQuest("Keys_lagoon_281");
			DialogExit();
		break;

		case "Exit":
			if (CheckAttribute(NPChar, "Payment"))
			{
				NextDiag.TempNode = "Hired";
				NextDiag.CurrentNode = "Hired";
			}
			else
			{
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			DialogExit();
		break;


}
}

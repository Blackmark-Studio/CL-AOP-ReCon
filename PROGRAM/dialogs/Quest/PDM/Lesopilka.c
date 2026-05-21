
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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

		case "First time":
			dialog.text = StringFromKey("Lesopilka_1");
			link.l1 = StringFromKey("Lesopilka_2");
			link.l1.go = "Nachalo_1";
		break;

		case "Nachalo_1":
            dialog.text = StringFromKey("Lesopilka_3");
            link.l1 = StringFromKey("Lesopilka_4");
			link.l1.go = "Slushau_1";
			link.l2 = StringFromKey("Lesopilka_5");
			link.l2.go = "QuestLater";
		break;

		case "Slushau_1":
            dialog.text = StringFromKey("Lesopilka_6", pchar);
			if (!CheckAttribute(npchar, "PDM_NR_Bratstvo"))
			{
				link.l1 = StringFromKey("Lesopilka_7");
				link.l1.go = "Davai_Pomogu_Bratstvo";
			}
			if (!CheckAttribute(npchar, "PDM_NR_GVIK"))
			{
				link.l2 = StringFromKey("Lesopilka_8");
				link.l2.go = "Davai_Pomogu_GVIK";
			}
			link.l3 = StringFromKey("Lesopilka_9");
			link.l3.go = "QuestLater";
		break;

		case "Davai_Pomogu_Bratstvo":
            dialog.text = StringFromKey("Lesopilka_10", pchar);
			if (!CheckAttribute(npchar, "PDM_NR_GVIK"))
			{
				link.l1 = StringFromKey("Lesopilka_11");
				link.l1.go = "Davai_Pomogu_GVIK";
			}
			link.l2 = StringFromKey("Lesopilka_12");
			link.l2.go = "QuestLater";
			npchar.PDM_NR_Bratstvo = true;
		break;
		
		case "Davai_Pomogu_GVIK":
            dialog.text = StringFromKey("Lesopilka_13");
			link.l1 = StringFromKey("Lesopilka_14");
			link.l1.go = "Davai_Pomogu_GVIK_3";
			npchar.PDM_NR_GVIK = true;
		break;
		
		case "QuestLater":
			DialogExit();
            NextDiag.CurrentNode = "First time";
		break;

		case "Davai_Pomogu_GVIK_3":
            dialog.text = StringFromKey("Lesopilka_15", pchar);
			link.l1 = StringFromKey("Lesopilka_16", pchar);
			link.l1.go = "Davai_Pomogu_GVIK_4";
            link.l2 = StringFromKey("Lesopilka_17");
			link.l2.go = "Otkazal";
		break;
		
		case "Otkazal":
            dialog.text = StringFromKey("Lesopilka_18", pchar);
            link.l1 = StringFromKey("Lesopilka_19");
			link.l1.go = "exit";
			NextDiag.TempNode = "Davai_Pomogu_GVIK_3";
		break;

		case "Davai_Pomogu_GVIK_4":
            dialog.text = StringFromKey("Lesopilka_20");
            link.l1 = StringFromKey("Lesopilka_21", pchar);
			link.l1.go = "Davai_Pomogu_GVIK_5";
			link.l2 = StringFromKey("Lesopilka_22");
			link.l2.go = "Otkazal";
		break;

		case "Davai_Pomogu_GVIK_5":
            dialog.text = StringFromKey("Lesopilka_23");
            link.l1 = StringFromKey("Lesopilka_24");
			link.l1.go = "RoadToVillemstad";
		break;

		case "Jugo_PodhodimSnova":
			sld = CharacterFromID("HWIC_head");
            dialog.text = StringFromKey("Lesopilka_25", pchar, pchar.name);
			if (CheckAttribute(pchar, "questTemp.PDM_Lesopilka_GVIK") && pchar.questTemp.PDM_Lesopilka_GVIK == "LaVega")
			{
				link.l1 = StringFromKey("Lesopilka_26", GetFullName(sld));
				link.l1.go = "Davai_Pomogu_GVIK_Document_1";
			}
            link.l2 = StringFromKey("Lesopilka_27");
			link.l2.go = "exit";
			NextDiag.TempNode = "Jugo_PodhodimSnova";
		break;

		case "RoadToVillemstad":
			DialogExit();
			NextDiag.CurrentNode = "Jugo_PodhodimSnova";
			AddDialogExitQuestFunction("PDM_Lesopilka_GVIK_InviteHugo");
		break;

		case "Davai_Pomogu_GVIK_Document_1":
			sld = CharacterFromID("HWIC_head");
            dialog.text = StringFromKey("Lesopilka_28", pchar, GetFullName(sld));
            link.l1 = StringFromKey("Lesopilka_29");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_Lesopilka_GVIK_HugoHappy");
			NextDiag.TempNode = "Podhodim_SNOVA_vipemromu";
			AddMoneyToCharacter(pchar, 10000);
			TakeItemFromCharacter(pchar, "LesopilkaDoc");
		break;

		case "Podhodim_SNOVA_vipemromu":
            dialog.text = StringFromKey("Lesopilka_30", pchar);
            link.l1 = StringFromKey("Lesopilka_31");
			link.l1.go = "exit";
			NextDiag.TempNode = "Podhodim_SNOVA_vipemromu";
		break;

		case "Novoe_Zadanie_1":
            dialog.text = StringFromKey("Lesopilka_32", pchar.name);
            link.l1 = StringFromKey("Lesopilka_33");
			link.l1.go = "Novoe_Zadanie_2";
		break;

		case "Novoe_Zadanie_2":
            dialog.text = StringFromKey("Lesopilka_34", pchar, pchar.name, pchar.name);
            link.l1 = StringFromKey("Lesopilka_35");
			link.l1.go = "Novoe_Zadanie_3";
		break;

		case "Novoe_Zadanie_3":
            dialog.text = StringFromKey("Lesopilka_36", pchar.name);
            link.l1 = StringFromKey("Lesopilka_37");
			link.l1.go = "Novoe_Zadanie_4";
		break;

		case "Novoe_Zadanie_4":
            dialog.text = StringFromKey("Lesopilka_38");
            link.l1 = StringFromKey("Lesopilka_39");
			link.l1.go = "Novoe_Zadanie_5";
		break;

		case "Novoe_Zadanie_5":
            dialog.text = StringFromKey("Lesopilka_40", pchar);
			link.l1 = StringFromKey("Lesopilka_41");
			link.l1.go = "Novoe_Zadanie_6";
		break;
		
		case "Novoe_Zadanie_6":
            dialog.text = StringFromKey("Lesopilka_42");
			link.l1 = StringFromKey("Lesopilka_43");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_Lesopilka_Treasures_NewQuest");
			NextDiag.TempNode = "Novoe_Zadanie_PodhodimSnova_1";
		break;

		case "Novoe_Zadanie_PodhodimSnova_1":
            dialog.text = StringFromKey("Lesopilka_44", pchar.name);
            link.l1 = StringFromKey("Lesopilka_45");
			link.l1.go = "Novoe_Zadanie_PodhodimSnova_2";
		break;

		case "Novoe_Zadanie_PodhodimSnova_2":
            dialog.text = StringFromKey("Lesopilka_46", pchar);
            link.l1 = StringFromKey("Lesopilka_47");
			link.l1.go = "exit";
			NextDiag.TempNode = "Novoe_Zadanie_PodhodimSnova_1";
		break;
		
		case "WinOnJungle_1":
            dialog.text = StringFromKey("Lesopilka_48", pchar);
            link.l1 = StringFromKey("Lesopilka_49");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_Lesopilka_Treasures_GoToGrot");
		break;
		
		case "InCabin_1":
            dialog.text = StringFromKey("Lesopilka_50", pchar);
            link.l1 = StringFromKey("Lesopilka_51", FindPersonalName("Stormbreaker_ship"));
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_Lesopilka_Treasures_InCabin_DlgExit");
			GiveItem2Character(PChar, "LesopilkaLog");
		break;

		case "InGrot_1":
			dialog.text = StringFromKey("Lesopilka_52", pchar);
			link.l1 = StringFromKey("Lesopilka_53");
			link.l1.go = "InGrot_2";
		break;

		case "InGrot_2":
			dialog.text = StringFromKey("Lesopilka_54", pchar);
			link.l1 = StringFromKey("Lesopilka_55");
			link.l1.go = "InGrot_3";
		break;

		case "InGrot_3":
			dialog.text = StringFromKey("Lesopilka_56");
			link.l1 = StringFromKey("Lesopilka_57");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_Lesopilka_Treasures_InGrot_6");
		break;

		case "InGrot_11":
			dialog.text = StringFromKey("Lesopilka_58");
			link.l1 = StringFromKey("Lesopilka_59");
			link.l1.go = "InGrot_12";
		break;

		case "InGrot_12":
			dialog.text = StringFromKey("Lesopilka_60", pchar);
			link.l1 = StringFromKey("Lesopilka_61");
			link.l1.go = "InGrot_13";
		break;

		case "InGrot_13":
			dialog.text = StringFromKey("Lesopilka_62");
			link.l1 = StringFromKey("Lesopilka_63");
			link.l1.go = "InGrot_14";
		break;

		case "InGrot_14":
			dialog.text = StringFromKey("Lesopilka_64", pchar);
			link.l1 = StringFromKey("Lesopilka_65");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_Lesopilka_Treasures_InGrot_10");
			AddQuestRecord("PDM_Lesopilka", "11");
		break;

		case "Final_1":
            dialog.text = StringFromKey("Lesopilka_66", pchar);
            link.l1 = StringFromKey("Lesopilka_67");
			link.l1.go = "Final_2";
		break;

		case "Final_2":
            dialog.text = StringFromKey("Lesopilka_68", pchar.name);
            link.l1 = StringFromKey("Lesopilka_69");
			link.l1.go = "exit";
			NextDiag.TempNode = "Final_Again";
			AddDialogExitQuestFunction("PDM_Lesopilka_Treasures_Final_2");
			ChangeCharacterReputation(pchar, 2);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddCharacterExpToSkill(PChar, "Leadership", 200);
			AddCharacterExpToSkill(PChar, "Sailing", 250);
			AddCharacterExpToSkill(PChar, "Accuracy", 200);
			AddCharacterExpToSkill(PChar, "Cannons", 200);
			AddCharacterExpToSkill(PChar, "Defence", 200);
			AddCharacterExpToSkill(PChar, "Sneak", 200);
			Achievment_Set(ACH_Lesopilka);
			AddQuestRecord("PDM_Lesopilka", "12");
		break;

		case "Final_Again":
            dialog.text = StringFromKey("Lesopilka_70", pchar.name);
            link.l1 = StringFromKey("Lesopilka_71");
			link.l1.go = "exit";
			NextDiag.TempNode = "Final_Again";
		break;


	}
}

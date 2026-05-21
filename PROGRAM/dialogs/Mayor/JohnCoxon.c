// Коксон в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	bool bOk;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			dialog.text = StringFromKey("JohnCoxon_1");
			link.l1 = StringFromKey("JohnCoxon_2");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		case "I_know_you_good":
			dialog.text = StringFromKey("JohnCoxon_3", pchar);
			link.l1 = StringFromKey("JohnCoxon_4");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "takeRumour"))
			{
				link.l1 = StringFromKey("JohnCoxon_5", pchar);
				link.l1.go = "SharpPearl_1";
			}
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = StringFromKey("JohnCoxon_6");
			link.l1 = StringFromKey("JohnCoxon_7");
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
			SeaPearl_PiratesBaron_DelQuestMarks();
			SeaPearl_Hostess_AddQuestMarks();
		break;
		case "SharpPearl_2":
			AddQuestRecord("SharpPearl", "16");
			AddQuestUserData("SharpPearl", "sName", GetFullName(NPChar));

			dialog.text = StringFromKey("JohnCoxon_8");
			link.l1 = StringFromKey("JohnCoxon_9");
			link.l1.go = "exit";
		break;

		//********************* ГПК *********************
		case "TheStarsAlignedLSC":
			dialog.text = StringFromKey("JohnCoxon_10");
			link.l1 = StringFromKey("JohnCoxon_11");
			link.l1.go = "StarsAlignedCompanion_1";
		break;
		case "StarsAlignedCompanion_1":
			dialog.text = StringFromKey("JohnCoxon_12", GetFullName(pchar));
			link.l1 = StringFromKey("JohnCoxon_13");
			link.l1.go = "StarsAlignedCompanion_2";
		break;
		case "StarsAlignedCompanion_2":
			dialog.text = StringFromKey("JohnCoxon_14");
			link.l1 = StringFromKey("JohnCoxon_15");
			link.l1.go = "StarsAlignedCompanion_3";
		break;
		case "StarsAlignedCompanion_3":
			dialog.text = StringFromKey("JohnCoxon_16");
			link.l1 = StringFromKey("JohnCoxon_17");
			link.l1.go = "StarsAlignedCompanion_4";
			link.l2 = StringFromKey("JohnCoxon_18");
			link.l2.go = "StarsAlignedCompanion_4";
			link.l3 = StringFromKey("JohnCoxon_19");
			link.l3.go = "StarsAlignedCompanion_4";
		break;
		case "StarsAlignedCompanion_4":
			bOk = false;
			dialog.text = StringFromKey("JohnCoxon_20", GetFullName(pchar));
			link.l1 = StringFromKey("JohnCoxon_21");
			link.l1.go = "StarsAlignedCompanion_11";
			if (CheckCharacterPerk(pchar, "SeaDogProfessional"))
			{
				PlayerRPGCheck_Perk_NotifyPass("SeaDogProfessional");
				bOk = true;
			}
			else if (sti(pchar.reputation) < 11)
			{
				bOk = true;
			}
			if (bOk)
			{
				link.l2 = StringFromKey("JohnCoxon_22");
				link.l2.go = "StarsAlignedCompanion_5";
			}
			if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 7))
			{
				link.l3 = StringFromKey("JohnCoxon_23");
				link.l3.go = "StarsAlignedCompanion_6";
			}
		break;
		case "StarsAlignedCompanion_5":
			dialog.text = StringFromKey("JohnCoxon_24");
			link.l1 = StringFromKey("JohnCoxon_25");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_7");
		break;
		case "StarsAlignedCompanion_6":
			dialog.text = StringFromKey("JohnCoxon_26");
			link.l1 = StringFromKey("JohnCoxon_27");
			link.l1.go = "StarsAlignedCompanion_7";
		break;
		case "StarsAlignedCompanion_7":
			dialog.text = StringFromKey("JohnCoxon_28");
			link.l1 = StringFromKey("JohnCoxon_29");
			link.l1.go = "StarsAlignedCompanion_8";
		break;
		case "StarsAlignedCompanion_8":
			dialog.text = StringFromKey("JohnCoxon_30");
			link.l1 = StringFromKey("JohnCoxon_31");
			link.l1.go = "StarsAlignedCompanion_9";
		break;
		case "StarsAlignedCompanion_9":
			dialog.text = StringFromKey("JohnCoxon_32");
			link.l1 = StringFromKey("JohnCoxon_33");
			link.l1.go = "StarsAlignedCompanion_10";
		break;
		case "StarsAlignedCompanion_10":
			dialog.text = StringFromKey("JohnCoxon_34");
			link.l1 = StringFromKey("JohnCoxon_35");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_7");
		break;
		case "StarsAlignedCompanion_11":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("TheStarsAlignedLSC_5");
		break;

		case "JungleManAndCoxonDialog":
			sld = CharacterFromID("JungleManLSC");
			LAi_ActorTurnToCharacter(sld, npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			dialog.text = StringFromKey("JohnCoxon_36");
			link.l1 = StringFromKey("JohnCoxon_37");
			link.l1.go = "JungleManAndCoxonDialog_1";
		break;
		case "JungleManAndCoxonDialog_1":
			dialog.text = StringFromKey("JohnCoxon_38");
			link.l1 = StringFromKey("JohnCoxon_39");
			link.l1.go = "JungleManAndCoxonDialog_2";
		break;
		case "JungleManAndCoxonDialog_2":
			dialog.text = StringFromKey("JohnCoxon_40");
			if (CheckAttribute(pchar, "questTemp.piratesLine") && pchar.questTemp.piratesLine == "over")
				link.l1 = StringFromKey("JohnCoxon_42", GetFullName(CharacterFromID("JungleManLSC")));
			else
				link.l1 = StringFromKey("JohnCoxon_41", GetFullName(CharacterFromID("JungleManLSC")));
			link.l1.go = "JungleManAndCoxonDialog_3";
		break;
		case "JungleManAndCoxonDialog_3":
			dialog.text = StringFromKey("JohnCoxon_43");
			link.l1 = StringFromKey("JohnCoxon_44");
			link.l1.go = "JungleManAndCoxonDialog_4";
		break;
		case "JungleManAndCoxonDialog_4":
			dialog.text = StringFromKey("JohnCoxon_45");
			link.l1 = StringFromKey("JohnCoxon_46");
			link.l1.go = "JungleManAndCoxonDialog_5";
		break;
		case "JungleManAndCoxonDialog_5":
			dialog.text = StringFromKey("JohnCoxon_47");
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_11");
		break;

		case "JungleManAndCoxonDialog2":
			sld = CharacterFromID("JungleManLSC");
			LAi_ActorTurnToCharacter(sld, npchar);
			LAi_ActorTurnToCharacter(npchar, sld);
			dialog.text = StringFromKey("JohnCoxon_48");
			link.l1 = StringFromKey("JohnCoxon_49");
			link.l1.go = "JungleManAndCoxonDialog2_1";
		break;
		case "JungleManAndCoxonDialog2_1":
			dialog.text = StringFromKey("JohnCoxon_50");
			link.l1 = StringFromKey("JohnCoxon_51", GetFullName(CharacterFromID("JungleManLSC")));
			link.l1.go = "JungleManAndCoxonDialog2_2";
		break;
		case "JungleManAndCoxonDialog2_2":
			dialog.text = StringFromKey("JohnCoxon_52");
			link.l1 = StringFromKey("JohnCoxon_53");
			link.l1.go = "JungleManAndCoxonDialog2_3";
		break;
		case "JungleManAndCoxonDialog2_3":
			dialog.text = StringFromKey("JohnCoxon_54");
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_13");
		break;

		case "JungleCoxonDialog":
			dialog.text = StringFromKey("JohnCoxon_55");
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_15");
		break;

		case "FirstWaves":
			dialog.text = StringFromKey("JohnCoxon_56");
			link.l1 = StringFromKey("JohnCoxon_57");
			link.l1.go = "FirstWaves_1";
		break;
		case "FirstWaves_1":
			dialog.text = StringFromKey("JohnCoxon_58");
			if (CheckAttribute(&TEV, "QuestTemp.deadHoum"))
			{
				link.l1 = StringFromKey("JohnCoxon_59");
				link.l1.go = "FirstWaves_2";
			}
			else
			{
				link.l1 = StringFromKey("JohnCoxon_60");
				link.l1.go = "FirstWaves_2";
			}
		break;
		case "FirstWaves_2":
			dialog.text = StringFromKey("JohnCoxon_61");
			link.l1 = StringFromKey("JohnCoxon_62");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_24");
		break;

		case "SecondWaves":
			dialog.text = StringFromKey("JohnCoxon_63");
			link.l1 = StringFromKey("JohnCoxon_64");
			link.l1.go = "SecondWaves_1";
		break;
		case "SecondWaves_1":
			sld = CharacterFromID("JungleManLSC");
			dialog.text = StringFromKey("JohnCoxon_65");
			link.l1 = StringFromKey("JohnCoxon_66", sld.name);
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_28");
		break;

		case "CoxonReturn":
			sld = CharacterFromID("JungleManLSC");
			dialog.text = StringFromKey("JohnCoxon_67", sld.name);
			link.l1 = StringFromKey("JohnCoxon_68");
			link.l1.go = "CoxonReturn_1";
		break;
		case "CoxonReturn_1":
			dialog.text = StringFromKey("JohnCoxon_69");
			link.l1 = StringFromKey("JohnCoxon_70");
			link.l1.go = "exit";
			AddDialogExitQuest("TheStarsAlignedLSC_38");
		break;
	}
}

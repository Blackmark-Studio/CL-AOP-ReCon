// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Maracaibo_Mayor_3", RandPhraseSimple(
								StringFromKey("Maracaibo_Mayor_1"),
								StringFromKey("Maracaibo_Mayor_2"))),
						StringFromKey("Maracaibo_Mayor_4"),
						StringFromKey("Maracaibo_Mayor_5"),
						StringFromKey("Maracaibo_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Maracaibo_Mayor_9", RandPhraseSimple(
								StringFromKey("Maracaibo_Mayor_7", pchar),
								StringFromKey("Maracaibo_Mayor_8"))),
						StringFromKey("Maracaibo_Mayor_10"),
						StringFromKey("Maracaibo_Mayor_11"),
						StringFromKey("Maracaibo_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//==> Проверка на стейт квестов
			if (pchar.questTemp.State == "Sp10Maracaibo_toMaracaibo")
			{
				dialog.text = StringFromKey("Maracaibo_Mayor_13");
				link.l1 = StringFromKey("Maracaibo_Mayor_14", pchar);
				link.l1.go = "Step_S10_1";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_toGovernor")
			{
				dialog.text = StringFromKey("Maracaibo_Mayor_15");
				link.l1 = StringFromKey("Maracaibo_Mayor_16");
				link.l1.go = "Step_S10_4";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_toBattle")
			{
				dialog.text = StringFromKey("Maracaibo_Mayor_17");
				link.l1 = StringFromKey("Maracaibo_Mayor_18");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.State == "Sp10Maracaibo_GoodWork")
			{
				dialog.text = StringFromKey("Maracaibo_Mayor_19", pchar);
				link.l1 = StringFromKey("Maracaibo_Mayor_20");
				link.l1.go = "Step_S10_5";
			}
		//<== Проверка на стейт квестов
		break;
		//************************** Квестовые штрумы ************************
		case "Cupture_after":
			dialog.text = StringFromKey("Maracaibo_Mayor_23", RandPhraseSimple(
						StringFromKey("Maracaibo_Mayor_21"),
						StringFromKey("Maracaibo_Mayor_22")));
			link.l1 = StringFromKey("Maracaibo_Mayor_26", RandPhraseSimple(
						StringFromKey("Maracaibo_Mayor_24"),
						StringFromKey("Maracaibo_Mayor_25", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;

		//==> Двенадцатый квест голл. линейки. Захват Маракайбо.
		case "HolLine12Quest_Occupy":
			dialog.text = StringFromKey("Maracaibo_Mayor_27");
			link.l1 = StringFromKey("Maracaibo_Mayor_28");
			link.l1.go = "Step_H12_1";
			AfterTownBattle();
		break;
		case "Step_H12_1":
			dialog.text = StringFromKey("Maracaibo_Mayor_29");
			link.l1 = StringFromKey("Maracaibo_Mayor_30");
			link.l1.go = "Step_H12_2";
		break;
		case "Step_H12_2":
			dialog.text = StringFromKey("Maracaibo_Mayor_31");
			link.l1 = StringFromKey("Maracaibo_Mayor_32");
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_12_OccupyMaracaibo", "2");
			pchar.questTemp.State = "OccupyMaracaibo_toWeWon";
			NextDiag.TempNode = "Cupture_after";
			PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
			PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
			SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
			DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
			UpdateRelations();
			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
			Achievement_AddStats_SturmColonies();
			SetReturn_Gover_Dialog_Exit(NPChar);
			chrDisableReloadToLocation = false;
			AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;
		//==> Десятый квест испанки. Защита Маракайбо.
		case "Step_S10_1":
			dialog.text = StringFromKey("Maracaibo_Mayor_33");
			link.l1 = StringFromKey("Maracaibo_Mayor_34");
			link.l1.go = "Step_S10_2";
		break;
		case "Step_S10_2":
			dialog.text = StringFromKey("Maracaibo_Mayor_35");
			link.l1 = StringFromKey("Maracaibo_Mayor_36", pchar);
			link.l1.go = "Step_S10_3";
		break;
		case "Step_S10_3":
			dialog.text = StringFromKey("Maracaibo_Mayor_37");
			link.l1 = StringFromKey("Maracaibo_Mayor_38", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp10Maracaibo_TalkWithOfficer";
			Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition.l1 = "location";
			Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition.l1.location = "Maracaibo_town";
			Pchar.quest.Sp10Maracaibo_TalkWithOfficer.win_condition = "Sp10Maracaibo_TalkWithOfficer";
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_S10_4":
			dialog.text = StringFromKey("Maracaibo_Mayor_39");
			link.l1 = StringFromKey("Maracaibo_Mayor_40");
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Maracaibo_town", "gate_back", false);
			LocatorReloadEnterDisable("Maracaibo_town", "reload1_back", false);
			LocatorReloadEnterDisable("Maracaibo_town", "boat", false);
			pchar.questTemp.State = "Sp10Maracaibo_toBattle";
			Pchar.quest.Sp10Maracaibo_Battle.win_condition.l1 = "location";
			Pchar.quest.Sp10Maracaibo_Battle.win_condition.l1.location = "Maracaibo";
			Pchar.quest.Sp10Maracaibo_Battle.win_condition = "Sp10Maracaibo_Battle";
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_S10_5":
			dialog.text = StringFromKey("Maracaibo_Mayor_41");
			link.l1 = StringFromKey("Maracaibo_Mayor_42");
			link.l1.go = "Step_S10_6";
		break;
		case "Step_S10_6":
			dialog.text = StringFromKey("Maracaibo_Mayor_43");
			link.l1 = StringFromKey("Maracaibo_Mayor_44");
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp10Maracaibo_2GoodWork";
			AddMoneyToCharacter(pchar, 70000);
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;

		case "Keys_lagoon_Res_11":
			dialog.text = StringFromKey("Maracaibo_Mayor_45");
			link.l1 = StringFromKey("Maracaibo_Mayor_46");
			link.l1.go = "Keys_lagoon_Res_12";
		break;

		case "Keys_lagoon_Res_12":
			dialog.text = StringFromKey("Maracaibo_Mayor_47");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_Res_12_Exit";
		break;

		case "Keys_lagoon_Res_12_Exit":
			AddDialogExitQuest("Keys_lagoon_Res_10");
			DialogExit();
		break;

		case "Keys_lagoon_Res_13":
			dialog.text = StringFromKey("Maracaibo_Mayor_48");
			link.l1 = StringFromKey("Maracaibo_Mayor_49");
			link.l1.go = "Keys_lagoon_Res_13_Exit";
		break;

		case "Keys_lagoon_Res_13_Exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_Res_Past_1");
		break;

		case "Keys_lagoon_Res_36":
			dialog.text = "...";
			link.l1 = StringFromKey("Maracaibo_Mayor_50");
			link.l1.go = "Keys_lagoon_Res_36_Exit";
		break;

		case "Keys_lagoon_Res_36_Exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_Res_Past_9");
		break;

		case "Keys_lagoon_Res_39":
			dialog.text = StringFromKey("Maracaibo_Mayor_51", GetFullName(npchar));
			link.l1 = StringFromKey("Maracaibo_Mayor_52");
			link.l1.go = "Keys_lagoon_Res_39_Exit";
		break;

		case "Keys_lagoon_Res_39_Exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_Res_Quarrel");
		break;

		case "Keys_lagoon_Res_45":
			dialog.text = StringFromKey("Maracaibo_Mayor_53");
			link.l1 = StringFromKey("Maracaibo_Mayor_54");
			link.l1.go = "Keys_lagoon_Res_45_Exit";
		break;

		case "Keys_lagoon_Res_45_Exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_Res_Tortuga_1");
		break;

		case "Keys_lagoon_Res_47":
			dialog.text = "...";
			link.l1 = StringFromKey("Maracaibo_Mayor_55");
			link.l1.go = "Keys_lagoon_Res_48";
		break;

		case "Keys_lagoon_Res_48":
			dialog.text = StringFromKey("Maracaibo_Mayor_56");
			link.l1 = StringFromKey("Maracaibo_Mayor_57");
			link.l1.go = "Keys_lagoon_Res_48_Exit";
		break;

		case "Keys_lagoon_Res_48_Exit":
			DialogExit();
			AddDialogExitQuest("Keys_lagoon_Res_Leaving");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


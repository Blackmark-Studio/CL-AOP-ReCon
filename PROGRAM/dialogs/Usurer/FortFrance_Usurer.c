// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Usurer_3", RandPhraseSimple(
								StringFromKey("FortFrance_Usurer_1"),
								StringFromKey("FortFrance_Usurer_2"))),
						StringFromKey("FortFrance_Usurer_4"),
						StringFromKey("FortFrance_Usurer_5"),
						StringFromKey("FortFrance_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Usurer_9", RandPhraseSimple(
								StringFromKey("FortFrance_Usurer_7", pchar),
								StringFromKey("FortFrance_Usurer_8"))),
						StringFromKey("FortFrance_Usurer_10"),
						StringFromKey("FortFrance_Usurer_11"),
						StringFromKey("FortFrance_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.piratesLine") && pchar.questTemp.piratesLine == "KillLoy_toSeek")
			{
				link.l1 = StringFromKey("FortFrance_Usurer_13");
				link.l1.go = "PL_Q3_1";
			}
			// французский сюжет - потопили капитана Black Twister
			if (CheckAttribute(pchar, "MainQuest.usurer") && pchar.MainQuest.usurer == "FL_BlackTwister_dead")
			{
				link.l2 = StringFromKey("FortFrance_Usurer_14");
				link.l2.go = "FL2";
			}
		break;
		// пиратская линейка
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Usurer_15"),
						StringFromKey("FortFrance_Usurer_16"),
						StringFromKey("FortFrance_Usurer_17"),
						StringFromKey("FortFrance_Usurer_18"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Usurer_19"),
						StringFromKey("FortFrance_Usurer_20"),
						StringFromKey("FortFrance_Usurer_21"),
						StringFromKey("FortFrance_Usurer_22"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = StringFromKey("FortFrance_Usurer_23");
			link.l1 = StringFromKey("FortFrance_Usurer_24");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "5");
			AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
		// Линейка Граммона
		case "FL2":
			DeleteAttribute(pchar, "MainQuest.usurer");
			dialog.text = StringFromKey("FortFrance_Usurer_25");
			link.l1 = StringFromKey("FortFrance_Usurer_26");
			link.l1.go = "FL2_1";
		break;

		case "FL2_1":
			dialog.text = StringFromKey("FortFrance_Usurer_27");
			link.l1 = StringFromKey("FortFrance_Usurer_28");
			link.l1.go = "FL2_2";
		break;

		case "FL2_2":
			dialog.text = StringFromKey("FortFrance_Usurer_29");
			link.l1 = StringFromKey("FortFrance_Usurer_30");
			link.l1.go = "FL2_3";
		break;

		case "FL2_3":
			dialog.text = StringFromKey("FortFrance_Usurer_31");
			link.l1 = StringFromKey("FortFrance_Usurer_32");
			link.l1.go = "FL2_4";
		break;

		case "FL2_4":
			dialog.text = StringFromKey("FortFrance_Usurer_33");
			link.l1 = StringFromKey("FortFrance_Usurer_34");
			link.l1.go = "FL2_5";
		break;

		case "FL2_5":
			dialog.text = StringFromKey("FortFrance_Usurer_35");
			link.l1 = StringFromKey("FortFrance_Usurer_36");
			link.l1.go = "exit";

			AddDialogExitQuest("FL2_s32");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

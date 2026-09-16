// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_PortMan_3", RandPhraseSimple(
								StringFromKey("PortRoyal_PortMan_1"),
								StringFromKey("PortRoyal_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("PortRoyal_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("PortRoyal_PortMan_5"),
						StringFromKey("PortRoyal_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_PortMan_9", RandPhraseSimple(
								StringFromKey("PortRoyal_PortMan_7", pchar),
								StringFromKey("PortRoyal_PortMan_8"))),
						StringFromKey("PortRoyal_PortMan_10"),
						StringFromKey("PortRoyal_PortMan_11"),
						StringFromKey("PortRoyal_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> квест №6 англ.линейки, базар о пинасе
			if (pchar.questTemp.State == "MorrisWillams_SeekSpanishGoods")
			{
				link.l1 = StringFromKey("PortRoyal_PortMan_13");
				link.l1.go = "Step_E6_1";
			}

			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
			{
				link.l1 = StringFromKey("PortRoyal_PortMan_14", pchar.questTemp.Slavetrader.ShipName);
				link.l1.go = "Jamaica_ratPP_1";
			}

		break;
		//************************************* Диалоги по англ.линейке *******************************
		case "Step_E6_1":
			dialog.text = StringFromKey("PortRoyal_PortMan_15");
			link.l1 = StringFromKey("PortRoyal_PortMan_16");
			link.l1.go = "Step_E6_2";
		break;

		case "Step_E6_2":
			dialog.text = StringFromKey("PortRoyal_PortMan_17");
			link.l1 = StringFromKey("PortRoyal_PortMan_18");
			link.l1.go = "Step_E6_3";
		break;

		case "Step_E6_3":
			dialog.text = StringFromKey("PortRoyal_PortMan_19");
			link.l1 = StringFromKey("PortRoyal_PortMan_20");
			link.l1.go = "Step_E6_4";
		break;

		case "Step_E6_4":
			dialog.text = StringFromKey("PortRoyal_PortMan_21");
			link.l1 = StringFromKey("PortRoyal_PortMan_22");
			link.l1.go = "exit";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "9");
			pchar.questTemp.State = "MorrisWillams_CatchUpPinnace";
			SaveCurrentQuestDateParam("questTemp");
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition.l1 = "location";
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition.l1.location = "Jamaica";
			pchar.quest.MorrisWillams_CheckTimeForForward.win_condition = "MorrisWillams_CheckTimeForForward";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;

		case "Jamaica_ratPP_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_PortMan_23", pchar.questTemp.Slavetrader.ShipName),
						StringFromKey("PortRoyal_PortMan_24"),
						StringFromKey("PortRoyal_PortMan_25"),
						StringFromKey("PortRoyal_PortMan_26"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_PortMan_27"),
						StringFromKey("PortRoyal_PortMan_28"),
						StringFromKey("PortRoyal_PortMan_29", pchar),
						StringFromKey("PortRoyal_PortMan_30", npchar.name), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

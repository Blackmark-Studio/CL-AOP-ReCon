// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
		if (CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.AnnaDebt") && sti(pchar.questTemp.AoP.RoyalJackpot.AnnaDebt) == 1)
			{
				dialog.text = StringFromKey("Cumana_Usurer_13");
				link.l1 = StringFromKey("Cumana_Usurer_14");
				link.l1.go = "RoyalJackpot_Anna_1";
				link.l2 = StringFromKey("Cumana_Usurer_15");
				link.l2.go = "exit";
				break;
			}
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cumana_Usurer_3", RandPhraseSimple(
								StringFromKey("Cumana_Usurer_1"),
								StringFromKey("Cumana_Usurer_2"))),
						StringFromKey("Cumana_Usurer_4"),
						StringFromKey("Cumana_Usurer_5"),
						StringFromKey("Cumana_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cumana_Usurer_9", RandPhraseSimple(
								StringFromKey("Cumana_Usurer_7", pchar),
								StringFromKey("Cumana_Usurer_8"))),
						StringFromKey("Cumana_Usurer_10"),
						StringFromKey("Cumana_Usurer_11"),
						StringFromKey("Cumana_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;


		case "RoyalJackpot_Anna_1":
			dialog.text = StringFromKey("Cumana_Usurer_16");
			link.l1 = StringFromKey("Cumana_Usurer_17");
			link.l1.go = "RoyalJackpot_Anna_2";
		break;

		case "RoyalJackpot_Anna_2":
			dialog.text = StringFromKey("Cumana_Usurer_18");

			if (sti(pchar.money) >= 20000)
			{
				link.l1 = StringFromKey("Cumana_Usurer_19");
				link.l1.go = "RoyalJackpot_Anna_Pay";
			}
			else
			{
				link.l1 = StringFromKey("Cumana_Usurer_20");
				link.l1.go = "exit";
			}
		break;

		case "RoyalJackpot_Anna_Pay":
			ChangeCharacterReputation(pchar, 20);
			AddMoneyToCharacter(pchar, -20000);

			if (CheckAttribute(pchar, "quest.Royal_jackpot_AnnaDeadline"))
			{
				pchar.quest.Royal_jackpot_AnnaDeadline.over = "yes";
			}

			DeleteAttribute(pchar, "questTemp.AoP.RoyalJackpot.AnnaDebt");
			pchar.questTemp.AoP.RoyalJackpot.AnnaPaid = true;

			AddQuestRecord("Royal_jackpot_Anna", "1");
			CloseQuestHeader("Royal_jackpot_Anna");

			dialog.text = StringFromKey("Cumana_Usurer_21");
			link.l1 = StringFromKey("Cumana_Usurer_22");
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

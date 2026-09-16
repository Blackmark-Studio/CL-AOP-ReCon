// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Gibraltar_Usurer_3", RandPhraseSimple(
								StringFromKey("Gibraltar_Usurer_1"),
								StringFromKey("Gibraltar_Usurer_2"))),
						StringFromKey("Gibraltar_Usurer_4"),
						StringFromKey("Gibraltar_Usurer_5"),
						StringFromKey("Gibraltar_Usurer_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Gibraltar_Usurer_9", RandPhraseSimple(
								StringFromKey("Gibraltar_Usurer_7", pchar),
								StringFromKey("Gibraltar_Usurer_8"))),
						StringFromKey("Gibraltar_Usurer_10"),
						StringFromKey("Gibraltar_Usurer_11"),
						StringFromKey("Gibraltar_Usurer_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

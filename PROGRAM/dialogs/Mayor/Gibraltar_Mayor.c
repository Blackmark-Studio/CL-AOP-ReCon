// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Gibraltar_Mayor_3", RandPhraseSimple(
								StringFromKey("Gibraltar_Mayor_1"),
								StringFromKey("Gibraltar_Mayor_2"))),
						StringFromKey("Gibraltar_Mayor_4"),
						StringFromKey("Gibraltar_Mayor_5"),
						StringFromKey("Gibraltar_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Gibraltar_Mayor_9", RandPhraseSimple(
								StringFromKey("Gibraltar_Mayor_7", pchar),
								StringFromKey("Gibraltar_Mayor_8"))),
						StringFromKey("Gibraltar_Mayor_10"),
						StringFromKey("Gibraltar_Mayor_11"),
						StringFromKey("Gibraltar_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Gibraltar_Shipyard_3", RandPhraseSimple(
								StringFromKey("Gibraltar_Shipyard_1"),
								StringFromKey("Gibraltar_Shipyard_2"))),
						StringFromKey("Gibraltar_Shipyard_4"),
						StringFromKey("Gibraltar_Shipyard_5"),
						StringFromKey("Gibraltar_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Gibraltar_Shipyard_9", RandPhraseSimple(
								StringFromKey("Gibraltar_Shipyard_7", pchar),
								StringFromKey("Gibraltar_Shipyard_8"))),
						StringFromKey("Gibraltar_Shipyard_10"),
						StringFromKey("Gibraltar_Shipyard_11"),
						StringFromKey("Gibraltar_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


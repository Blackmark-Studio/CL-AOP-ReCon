// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Gibraltar_Store_1"),
						StringFromKey("Gibraltar_Store_2"),
						StringFromKey("Gibraltar_Store_3"),
						StringFromKey("Gibraltar_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Gibraltar_Store_5", NPChar.name),
						StringFromKey("Gibraltar_Store_6", pchar),
						StringFromKey("Gibraltar_Store_7"),
						StringFromKey("Gibraltar_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

// KZ FreeStores > общий дополнительный диалог свободных магазинов без колонии
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int    iStore   = GetTraderFreeStore(NPChar);
	string sStoreId = "";
	if (iStore >= 0) sStoreId = Stores[iStore].id;

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Free_Store_1"),
						StringFromKey("Free_Store_2"),
						StringFromKey("Free_Store_3"),
						StringFromKey("Free_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Free_Store_5", NPChar.name),
						StringFromKey("Free_Store_6", pchar),
						StringFromKey("Free_Store_7"),
						StringFromKey("Free_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

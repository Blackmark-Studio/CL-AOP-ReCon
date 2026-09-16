// KZ FreeStores > общий дополнительный диалог верфиста без колонии
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int    iStore   = GetTraderFreeStore(NPChar);
	string sStoreId = "";
	if (iStore >= 0) sStoreId = Stores[iStore].id;

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Free_Shipyard_3", RandPhraseSimple(
								StringFromKey("Free_Shipyard_1"),
								StringFromKey("Free_Shipyard_2"))),
						StringFromKey("Free_Shipyard_4"),
						StringFromKey("Free_Shipyard_5"),
						StringFromKey("Free_Shipyard_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Free_Shipyard_9", RandPhraseSimple(
								StringFromKey("Free_Shipyard_7", pchar),
								StringFromKey("Free_Shipyard_8"))),
						StringFromKey("Free_Shipyard_10"),
						StringFromKey("Free_Shipyard_11"),
						StringFromKey("Free_Shipyard_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

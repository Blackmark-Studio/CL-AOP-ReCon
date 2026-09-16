// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	bool bOk;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Pirates_Store_1"),
						StringFromKey("Pirates_Store_2"),
						StringFromKey("Pirates_Store_3"),
						StringFromKey("Pirates_Store_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Pirates_Store_5", NPChar.name),
						StringFromKey("Pirates_Store_6", pchar),
						StringFromKey("Pirates_Store_7"),
						StringFromKey("Pirates_Store_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.BlueBird == "toBermudes")
			{
				link.l1 = StringFromKey("Pirates_Store_9", pchar);
				link.l1.go = "BlueBird_1";
			}
			bOk = pchar.questTemp.BlueBird == "weWon" || pchar.questTemp.BlueBird == "returnMoney" || pchar.questTemp.BlueBird == "over" || pchar.questTemp.BlueBird == "finish";
			if (bOk && !CheckAttribute(pchar, "questTemp.BlueBird.speakWon") && GetFirstName(NPChar) != FindPersonalName("Pirates_trader_name")) // != "Паскаль Вуазье"
			{
				link.l1 = StringFromKey("Pirates_Store_10");
				link.l1.go = "BlueBird_3";
			}
			if (bBettaTestMode)
			{
				link.l5 = StringFromKey("Pirates_Store_11");
				link.l5.go = "storage_rent1";
			}
		break;
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Pirates_Store_12"),
						StringFromKey("Pirates_Store_13"),
						StringFromKey("Pirates_Store_14"),
						StringFromKey("Pirates_Store_15"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Pirates_Store_16"),
						StringFromKey("Pirates_Store_17"),
						StringFromKey("Pirates_Store_18"),
						StringFromKey("Pirates_Store_19"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;
		case "BlueBird_2":
			dialog.text = StringFromKey("Pirates_Store_20");
			link.l1 = StringFromKey("Pirates_Store_21", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "2");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("ся", "ась"));
			RemoveLandQuestMark_Main(npchar, "Xebeca_BlueBird");
		break;

		case "BlueBird_3":
			if (sti(pchar.Ship.Type) == SHIP_NOTUSED || pchar.location.from_sea != "Pirates_town")
			{
				dialog.text = StringFromKey("Pirates_Store_22");
				link.l1 = StringFromKey("Pirates_Store_23");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Store_24");
				link.l1 = StringFromKey("Pirates_Store_25");
				link.l1.go = "storage_rent";
			}
			pchar.questTemp.BlueBird.speakWon = true;
			RemoveLandQuestMark_Main(npchar, "Xebeca_BlueBird");
		break;

		case "storage_rent":
			dialog.text = StringFromKey("Pirates_Store_26");
			link.l1 = StringFromKey("Pirates_Store_27");
			link.l1.go = "storage_rent1";
		break;

		case "storage_rent1":
			NPChar.MoneyForStorage = GetStoragePrice(NPChar, 15000);
			dialog.text = StringFromKey("Pirates_Store_28", FindMoneyString(sti(NPChar.MoneyForStorage)));
			link.l1 = StringFromKey("Pirates_Store_29");
			link.l1.go = "storage_rent2";
			link.l2 = StringFromKey("Pirates_Store_30");
			link.l2.go = "storage_rent3";
		break;

		case "storage_rent2":
			dialog.text = StringFromKey("Pirates_Store_31");
			if (sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = StringFromKey("Pirates_Store_32");
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = StringFromKey("Pirates_Store_33");
				link.l1.go = "exit";
			}
		break;

		case "storage_rent3":
			dialog.text = StringFromKey("Pirates_Store_34");
			link.l1 = StringFromKey("Pirates_Store_35");
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LaVega_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("LaVega_Tavern_2"),
						StringFromKey("LaVega_Tavern_3"),
						StringFromKey("LaVega_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LaVega_Tavern_5", NPChar.name),
						StringFromKey("LaVega_Tavern_6", pchar),
						StringFromKey("LaVega_Tavern_7"),
						StringFromKey("LaVega_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//пиратка, квест №7
			if (pchar.questTemp.piratesLine == "Soukins_toLaVega")
			{
				link.l2 = StringFromKey("LaVega_Tavern_9");
				link.l2.go = "PL_Q7_1";
			}
			// Ле Баск. Квест №2
			if (CheckAttrValue(pchar, "quest.Old_campfire", "Talk_Tavern"))
			{
				if (CheckAttribute(pchar, "questTemp.Old_campfire.TavernNeedMoney"))
				{
					link.l3 = StringFromKey("LaVega_Tavern_12");
					link.l3.go = "Old_campfire_Repeat";
				}
				else
				{
					link.l3 = StringFromKey("LaVega_Tavern_13");
					link.l3.go = "Old_campfire_1";
				}
			}
		break;
		case "PL_Q7_1":
			dialog.text = StringFromKey("LaVega_Tavern_10");
			link.l1 = StringFromKey("LaVega_Tavern_11");
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "Soukins_toLaVegaSea";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			AddQuestRecord("Pir_Line_7_Soukins", "2");
			pchar.quest.PQ7_FriendLinney.win_condition.l1 = "location";
			pchar.quest.PQ7_FriendLinney.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PQ7_FriendLinney.function = "PQ7_FriendLinney";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;

		// Ле Баск. Квест №2.
		case "Old_campfire_1":
			dialog.text = StringFromKey("LaVega_Tavern_14");
			link.l1 = StringFromKey("LaVega_Tavern_15");
			link.l1.go = "Old_campfire_2";
		break;

		case "Old_campfire_2":
			if (sti(pchar.reputation) >= 30)
			{
				dialog.text = StringFromKey("LaVega_Tavern_16");
				link.l1 = StringFromKey("LaVega_Tavern_17");
				link.l1.go = "Old_campfire_3";
			}
			else
			{
				dialog.text = StringFromKey("LaVega_Tavern_18");

				if (sti(pchar.money) >= 1000)
				{
					link.l1 = StringFromKey("LaVega_Tavern_19");
					link.l1.go = "Old_campfire_2_paid";
				}
				else
				{
					link.l1 = StringFromKey("LaVega_Tavern_20");
					link.l1.go = "Old_campfire_2_no_money";
				}

				link.l2 = StringFromKey("LaVega_Tavern_21");
				link.l2.go = "Old_campfire_2_refuse";
			}
		break;

		case "Old_campfire_2_paid":
			AddMoneyToCharacter(pchar, -1000);
			DeleteAttribute(pchar, "questTemp.Old_campfire.TavernNeedMoney");
			dialog.text = StringFromKey("LaVega_Tavern_22");
			link.l1 = StringFromKey("LaVega_Tavern_23");
			link.l1.go = "Old_campfire_3";
		break;

		case "Old_campfire_2_no_money":
			pchar.questTemp.Old_campfire.TavernNeedMoney = true;
			NPChar.dialog.currentnode = "Old_campfire_Repeat";
			dialog.text = StringFromKey("LaVega_Tavern_24");
			link.l1 = StringFromKey("LaVega_Tavern_25");
			link.l1.go = "exit";
		break;

		case "Old_campfire_2_refuse":
			pchar.questTemp.Old_campfire.TavernNeedMoney = true;
			NPChar.dialog.currentnode = "Old_campfire_Repeat";
			dialog.text = StringFromKey("LaVega_Tavern_26");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		case "Old_campfire_Repeat":
			if (sti(pchar.reputation) >= 40)
			{
				DeleteAttribute(pchar, "questTemp.Old_campfire.TavernNeedMoney");
				dialog.text = StringFromKey("LaVega_Tavern_27");
				link.l1 = StringFromKey("LaVega_Tavern_28");
				link.l1.go = "Old_campfire_3";
			}
			else
			{
				dialog.text = StringFromKey("LaVega_Tavern_29");

				if (sti(pchar.money) >= 1000)
				{
					link.l1 = StringFromKey("LaVega_Tavern_30");
					link.l1.go = "Old_campfire_2_paid";
				}
				else
				{
					link.l1 = StringFromKey("LaVega_Tavern_31");
					link.l1.go = "Old_campfire_2_no_money";
				}

				link.l2 = StringFromKey("LaVega_Tavern_32");
				link.l2.go = "exit";
			}
		break;

		case "Old_campfire_3":
			dialog.text = StringFromKey("LaVega_Tavern_33");
			link.l1 = StringFromKey("LaVega_Tavern_34");
			link.l1.go = "Old_campfire_4";
		break;

		case "Old_campfire_4":
			dialog.text = StringFromKey("LaVega_Tavern_35");
			link.l1 = StringFromKey("LaVega_Tavern_36");
			link.l1.go = "Old_campfire_5";
		break;

		case "Old_campfire_5":
			dialog.text = StringFromKey("LaVega_Tavern_37");
			link.l1 = StringFromKey("LaVega_Tavern_38");
			link.l1.go = "Old_campfire_5_exit";
		break;

		case "Old_campfire_5_exit":
			ref sld;
			sld = characterFromId("Etien_Marso");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "LaVega_tavern", "reload", "reload1_back");
			DeleteAttribute(pchar, "questTemp.Old_campfire.TavernNeedMoney");
			AddDialogExitQuest("Old_campfire_11");
			DialogExit();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

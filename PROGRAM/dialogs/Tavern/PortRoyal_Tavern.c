// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("PortRoyal_Tavern_2"),
						StringFromKey("PortRoyal_Tavern_3"),
						StringFromKey("PortRoyal_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_Tavern_5", NPChar.name),
						StringFromKey("PortRoyal_Tavern_6"),
						StringFromKey("PortRoyal_Tavern_7"),
						StringFromKey("PortRoyal_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Шестой квест английки, Моррис Уильямс
			if (pchar.questTemp.State == "MorrisWillams_ArrestedSeekInfo")
			{
				link.l1 = StringFromKey("PortRoyal_Tavern_9");
				link.l1.go = "Step_E6_1";
			}
			// ==> Восьмой квест фр.линейки, отговорить трёх корсаров
			if (pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek")
			{
				link.l1 = StringFromKey("PortRoyal_Tavern_10");
				link.l1.go = "Step_F8_1";
			}
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
			{
				link.l1 = StringFromKey("PortRoyal_Tavern_11");
				link.l1.go = "Jamaica_ratP_1";
			}
		break;
		//********************** Английская линейка **********************
		case "Step_E6_1":
			dialog.text = StringFromKey("PortRoyal_Tavern_12");
			link.l1 = StringFromKey("PortRoyal_Tavern_13");
			link.l1.go = "Step_E6_2";
		break;
		case "Step_E6_2":
			dialog.text = StringFromKey("PortRoyal_Tavern_14");
			link.l1 = StringFromKey("PortRoyal_Tavern_15");
			link.l1.go = "Step_E6_3";
		break;
		case "Step_E6_3":
			dialog.text = StringFromKey("PortRoyal_Tavern_16");
			link.l1 = StringFromKey("PortRoyal_Tavern_17");
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_ArrestedSeekInfoFather";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;
		//********************** Французская линейка **********************
		case "Step_F8_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_Tavern_18"),
						StringFromKey("PortRoyal_Tavern_19"),
						StringFromKey("PortRoyal_Tavern_20"),
						StringFromKey("PortRoyal_Tavern_21", UpperFirst(GetAddress_Form(NPChar))), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_Tavern_22"),
						StringFromKey("PortRoyal_Tavern_23", pchar),
						StringFromKey("PortRoyal_Tavern_24"),
						StringFromKey("PortRoyal_Tavern_25"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;

		case "Jamaica_ratP_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortRoyal_Tavern_26"),
						StringFromKey("PortRoyal_Tavern_27", pchar),
						StringFromKey("PortRoyal_Tavern_28", pchar),
						StringFromKey("PortRoyal_Tavern_29"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortRoyal_Tavern_30"),
						StringFromKey("PortRoyal_Tavern_31"),
						StringFromKey("PortRoyal_Tavern_32", pchar),
						StringFromKey("PortRoyal_Tavern_33", npchar.name), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

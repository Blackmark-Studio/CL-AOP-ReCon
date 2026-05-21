// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Providencia_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("Providencia_Tavern_2"),
						StringFromKey("Providencia_Tavern_3"),
						StringFromKey("Providencia_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Providencia_Tavern_5", NPChar.name),
						StringFromKey("Providencia_Tavern_6", pchar),
						StringFromKey("Providencia_Tavern_7"),
						StringFromKey("Providencia_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Квест "Остепенившийся пират" -->
			if (CheckAttribute(pchar, "questTemp.PDM_Lesopilka_GVIK") && pchar.questTemp.PDM_Lesopilka_GVIK == "TookDocument")
			{
				link.l1 = StringFromKey("Providencia_Tavern_9");
				link.l1.go = "PDM_Lesopilka_1";
			}
			// Квест "Остепенившийся пират" <--
		break;
		
		// Квест "Остепенившийся пират" -->
		case "PDM_Lesopilka_1":
			dialog.text = StringFromKey("Providencia_Tavern_10");
			link.l1 = StringFromKey("Providencia_Tavern_11");
			link.l1.go = "PDM_Lesopilka_2";
		break;

		case "PDM_Lesopilka_2":
			dialog.text = StringFromKey("Providencia_Tavern_12");
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = StringFromKey("Providencia_Tavern_13");
				link.l1.go = "PDM_Lesopilka_3";
			}
			link.l2 = StringFromKey("Providencia_Tavern_14");
			link.l2.go = "exit";
		break;

		case "PDM_Lesopilka_3":
			dialog.text = StringFromKey("Providencia_Tavern_15");
			link.l1 = StringFromKey("Providencia_Tavern_16");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_Lesopilka_GVIK_RoadToLaVega");
			AddMoneyToCharacter(pchar, -1000);
		break;
		// Квест "Остепенившийся пират" <--
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

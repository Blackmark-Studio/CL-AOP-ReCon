// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Cartahena_PortMan_3", RandPhraseSimple(
								StringFromKey("Cartahena_PortMan_1"),
								StringFromKey("Cartahena_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("Cartahena_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("Cartahena_PortMan_5"),
						StringFromKey("Cartahena_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Cartahena_PortMan_9", RandPhraseSimple(
								StringFromKey("Cartahena_PortMan_7", pchar),
								StringFromKey("Cartahena_PortMan_8"))),
						StringFromKey("Cartahena_PortMan_10"),
						StringFromKey("Cartahena_PortMan_11"),
						StringFromKey("Cartahena_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//ОЗГ, Крыса
			if (CheckAttrValue(pchar, "questTemp.Headhunter", "Rat") && pchar.questTemp.Headhunter.countC == 0)
			{
				link.l1 = StringFromKey("Cartahena_PortMan_13", pchar);
				link.l1.go = "Rat_portmanC";
			}
		break;

		//ОЗГ, Крыса
		case "Rat_portmanC":
			dialog.text = StringFromKey("Cartahena_PortMan_14");
			link.l1 = StringFromKey("Cartahena_PortMan_15");
			link.l1.go = "Rat_portmanC_1";
		break;

		case "Rat_portmanC_1":
			dialog.text = StringFromKey("Cartahena_PortMan_16");
			link.l1 = StringFromKey("Cartahena_PortMan_17");
			link.l1.go = "CheckC";
			pchar.questTemp.Headhunter.count = sti(pchar.questTemp.Headhunter.count) + 1;
			pchar.questTemp.Headhunter.countC = 1;
		break;

		case "CheckC":
			if (pchar.questTemp.Headhunter.count == 3)
			{
				pchar.questTemp.Headhunter = "Rat_Tavern";
				pchar.questTemp.Headhunter.Ratrumcity = npchar.city;
				AddQuestRecord("Headhunt", "13");
				AddLandQuestMarkToFantoms_Main("habitue", "Headhunt", "Headhunt_Rat_Habitues_QuestMarkCondition");
			}
			else
			{
				AddQuestRecord("Headhunt", "12_1");
			}
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			DialogExit();
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PortSpein_PortMan_3", RandPhraseSimple(
								StringFromKey("PortSpein_PortMan_1"),
								StringFromKey("PortSpein_PortMan_2", GetAddress_Form(NPChar)))),
						StringFromKey("PortSpein_PortMan_4", GetAddress_Form(NPChar)),
						StringFromKey("PortSpein_PortMan_5"),
						StringFromKey("PortSpein_PortMan_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PortSpein_PortMan_9", RandPhraseSimple(
								StringFromKey("PortSpein_PortMan_7", pchar),
								StringFromKey("PortSpein_PortMan_8"))),
						StringFromKey("PortSpein_PortMan_10"),
						StringFromKey("PortSpein_PortMan_11"),
						StringFromKey("PortSpein_PortMan_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//ОЗГ, Крыса
			if (CheckAttrValue(pchar, "questTemp.Headhunter", "Rat") && pchar.questTemp.Headhunter.countP == 0)
			{
				link.l1 = StringFromKey("PortSpein_PortMan_13");
				link.l1.go = "Rat_portmanP";
			}
		break;

		//ОЗГ, Крыса
		case "Rat_portmanP":
			dialog.text = StringFromKey("PortSpein_PortMan_14");
			link.l1 = StringFromKey("PortSpein_PortMan_15");
			link.l1.go = "Rat_portmanP_1";
		break;

		case "Rat_portmanP_1":
			dialog.text = StringFromKey("PortSpein_PortMan_16");
			link.l1 = StringFromKey("PortSpein_PortMan_17");
			link.l1.go = "CheckP";
			pchar.questTemp.Headhunter.count = sti(pchar.questTemp.Headhunter.count) + 1;
			pchar.questTemp.Headhunter.countP = 1;
		break;

		case "CheckP":
			if (pchar.questTemp.Headhunter.count == 3)
			{
				pchar.questTemp.Headhunter = "Rat_Tavern";
				pchar.questTemp.Headhunter.Ratrumcity = npchar.city;
				AddQuestRecord("Headhunt", "13");
				AddLandQuestMarkToFantoms_Main("habitue", "Headhunt", "Headhunt_Rat_Habitues_QuestMarkCondition");
			}
			else
			{
				AddQuestRecord("Headhunt", "12_2");
			}
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			DialogExit();
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Beliz_Waitress_3", RandPhraseSimple(
								StringFromKey("Beliz_Waitress_1", GetAddress_Form(NPChar)),
								StringFromKey("Beliz_Waitress_2", GetAddress_Form(NPChar)))),
						StringFromKey("Beliz_Waitress_4", pchar),
						StringFromKey("Beliz_Waitress_5", pchar),
						StringFromKey("Beliz_Waitress_6", GetAddress_Form(NPChar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Beliz_Waitress_9", RandPhraseSimple(
								StringFromKey("Beliz_Waitress_7", pchar),
								StringFromKey("Beliz_Waitress_8"))),
						StringFromKey("Beliz_Waitress_10"),
						StringFromKey("Beliz_Waitress_11"),
						StringFromKey("Beliz_Waitress_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Oficiantka_Beliz"))
			{
				link.l1 = StringFromKey("Beliz_Waitress_13");
				link.l1.go = "PDM_ONV_WOMAN";
			}
		break;
		
//========================== Квест "Прокажённая" ==================================
		case "PDM_ONV_WOMAN":
			dialog.text = StringFromKey("Beliz_Waitress_14");
			link.l1 = StringFromKey("Beliz_Waitress_15");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Oficiantka_Beliz");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

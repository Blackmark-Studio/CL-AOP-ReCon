// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_ItemTrader_3", RandPhraseSimple(
								StringFromKey("Villemstad_ItemTrader_1"),
								StringFromKey("Villemstad_ItemTrader_2", GetAddress_Form(NPChar)))),
						StringFromKey("Villemstad_ItemTrader_4", GetAddress_Form(NPChar)),
						StringFromKey("Villemstad_ItemTrader_5", GetAddress_Form(NPChar)),
						StringFromKey("Villemstad_ItemTrader_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_ItemTrader_9", RandPhraseSimple(
								StringFromKey("Villemstad_ItemTrader_7"),
								StringFromKey("Villemstad_ItemTrader_8"))),
						StringFromKey("Villemstad_ItemTrader_10"),
						StringFromKey("Villemstad_ItemTrader_11"),
						StringFromKey("Villemstad_ItemTrader_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Эммануэль Пардаль: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.EPL_PZD_Lavochniki") && !CheckAttribute(npchar, "EPL_PZD_Vopros"))
			{
				link.l1 = StringFromKey("Villemstad_ItemTrader_13");
				link.l1.go = "EPL_PZD_Lavochniki_1";
				DeleteAttribute(pchar, "questTemp.EPL_PZD_Lavochniki");
			}
            if(CheckAttribute(pchar, "questTemp.EPL_PZD_Lavochniki_2") && !CheckAttribute(npchar, "EPL_PZD_Vopros"))
            {
				link.l1 = StringFromKey("Villemstad_ItemTrader_14");
				link.l1.go = "EPL_PZD_Lavochniki_2";
				DeleteAttribute(pchar, "questTemp.EPL_PZD_Lavochniki_2");
			}
			if(CheckAttribute(pchar, "questTemp.EPL_PZD_Lavochniki_3") && !CheckAttribute(npchar, "EPL_PZD_Vopros"))
            {
				link.l1 = StringFromKey("Villemstad_ItemTrader_15");
				link.l1.go = "EPL_PZD_Lavochniki_3";
				DeleteAttribute(pchar, "questTemp.EPL_PZD_Lavochniki_3");
			}
			// <== Эммануэль Пардаль: Портниха знатной дамы
		break;
		
		// ==> Эммануэль Пардаль: Портниха знатной дамы
		case "EPL_PZD_Lavochniki_1":
    		dialog.text = StringFromKey("Villemstad_ItemTrader_16");
    		link.l1 = StringFromKey("Villemstad_ItemTrader_17");
    		link.l1.go = "exit";
			pchar.questTemp.EPL_PZD_Lavochniki_2 = true;
			npchar.EPL_PZD_Vopros;
 		break;
		
		case "EPL_PZD_Lavochniki_2":
    		dialog.text = StringFromKey("Villemstad_ItemTrader_18");
    		link.l1 = StringFromKey("Villemstad_ItemTrader_19");
    		link.l1.go = "exit";
			pchar.questTemp.EPL_PZD_Lavochniki_3 = true;
			npchar.EPL_PZD_Vopros;
 		break;
		
		case "EPL_PZD_Lavochniki_3":
    		dialog.text = StringFromKey("Villemstad_ItemTrader_20");
    		link.l1 = StringFromKey("Villemstad_ItemTrader_21");
    		link.l1.go = "EPL_PZD_Lavochniki_3_1";
 		break;
		
		case "EPL_PZD_Lavochniki_3_1":
    		dialog.text = StringFromKey("Villemstad_ItemTrader_22");
    		link.l1 = StringFromKey("Villemstad_ItemTrader_23");
    		link.l1.go = "exit";
 		break;
		// <== Эммануэль Пардаль: Портниха знатной дамы
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


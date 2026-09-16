// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Villemstad_Brothel_3", RandPhraseSimple(
								StringFromKey("Villemstad_Brothel_1", pchar),
								StringFromKey("Villemstad_Brothel_2", pchar))),
						StringFromKey("Villemstad_Brothel_4"),
						StringFromKey("Villemstad_Brothel_5"),
						StringFromKey("Villemstad_Brothel_6", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Villemstad_Brothel_9", RandPhraseSimple(
								StringFromKey("Villemstad_Brothel_7", pchar),
								StringFromKey("Villemstad_Brothel_8"))),
						StringFromKey("Villemstad_Brothel_10"),
						StringFromKey("Villemstad_Brothel_11"),
						StringFromKey("Villemstad_Brothel_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// ==> Эммануэль Пардаль: Портниха знатной дамы
			if(CheckAttribute(pchar, "questTemp.EPL_PZD_Bordel"))
			{
				DeleteAttribute(pchar, "questTemp.EPL_PZD_Bordel");
				link.l1 = StringFromKey("Villemstad_Brothel_13");
				link.l1.go = "EPL_PZD_Bordel_1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.EPL_PZD_Bordel_2"))
			{
				link.l1 = StringFromKey("Villemstad_Brothel_14");
				link.l1.go = "EPL_PZD_Bordel_6";
				break;
			}
			// <== Эммануэль Пардаль: Портниха знатной дамы
		break;
		
		// ==> Эммануэль Пардаль: Портниха знатной дамы
		case "EPL_PZD_Bordel_1":
    		dialog.text = StringFromKey("Villemstad_Brothel_15");
    		link.l1 = StringFromKey("Villemstad_Brothel_16");
    		link.l1.go = "EPL_PZD_Bordel_2";
 		break;
		case "EPL_PZD_Bordel_2":
    		dialog.text = StringFromKey("Villemstad_Brothel_17");
			link.l1 = StringFromKey("Villemstad_Brothel_18");
    		link.l1.go = "EPL_PZD_Bordel_3";
 		break;
		case "EPL_PZD_Bordel_3":
    		dialog.text = StringFromKey("Villemstad_Brothel_19");
			link.l1 = StringFromKey("Villemstad_Brothel_20");
    		link.l1.go = "EPL_PZD_Bordel_4";
 		break;
		case "EPL_PZD_Bordel_4":
    		dialog.text = StringFromKey("Villemstad_Brothel_21");
			if (sti(pchar.Money) >= 65000)
			{
				link.l1 = StringFromKey("Villemstad_Brothel_22");
				link.l1.go = "EPL_PZD_Bordel_5";
			}
			link.l2 = StringFromKey("Villemstad_Brothel_23");
    		link.l2.go = "EPL_PZD_Bordel_4_1";
 		break;
		case "EPL_PZD_Bordel_4_1":
    		DialogExit();
			pchar.questTemp.EPL_PZD_Bordel_2 = true;
 		break;
		case "EPL_PZD_Bordel_6":
    		dialog.text = StringFromKey("Villemstad_Brothel_24");
			if (sti(pchar.Money) >= 65000)
			{
				link.l1 = StringFromKey("Villemstad_Brothel_25");
				link.l1.go = "EPL_PZD_Bordel_5";
			}
			link.l2 = StringFromKey("Villemstad_Brothel_26");
    		link.l2.go = "EPL_PZD_Bordel_4_1";
 		break;		
		case "EPL_PZD_Bordel_5":
			LAi_Fade("", "");
			notification(StringFromKey("Villemstad_Brothel_27"), "none");
			AddMoneyToCharacter(pchar, -65000);
			PlaySound("Interface\important_item.wav");
			GiveItem2Character(PChar, "suit_3");
			EquipCharacterByItem(PChar, "suit_3");
			RemoveLandQuestmark_Main(CharacterFromID("Villemstad_usurer"), "EPL_PZD");
			RemoveLandQuestmark_Main(CharacterFromID("Villemstad_hostess"), "EPL_PZD");
			DeleteAttribute(pchar, "questTemp.EPL_PZD_Bordel_2");
			
    		dialog.text = StringFromKey("Villemstad_Brothel_28");
			link.l1 = StringFromKey("Villemstad_Brothel_29");
    		link.l1.go = "EPL_PZD_Bordel_8";
 		break;
		case "EPL_PZD_Bordel_8":
    		dialog.text = StringFromKey("Villemstad_Brothel_30");
			link.l1 = StringFromKey("Villemstad_Brothel_31");
    		link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_PZD_BrothelDlgExit");
 		break;
		// <== Эммануэль Пардаль: Портниха знатной дамы
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

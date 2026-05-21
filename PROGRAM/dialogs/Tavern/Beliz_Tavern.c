// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Beliz_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("Beliz_Tavern_2"),
						StringFromKey("Beliz_Tavern_3"),
						StringFromKey("Beliz_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Beliz_Tavern_5", NPChar.name),
						StringFromKey("Beliz_Tavern_6", pchar),
						StringFromKey("Beliz_Tavern_7"),
						StringFromKey("Beliz_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr7RockBras_toSeekPlace")
			{
				dialog.text = StringFromKey("Beliz_Tavern_9", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Beliz_Tavern_10", pchar);
				link.l1.go = "Step_F7_1";
			}
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Tavern_NET"))
            {
                link.l1 = StringFromKey("Beliz_Tavern_23");
                link.l1.go = "PDM_ONV_Sprashivaem_Pro_Karlu_NeZnaet";
            }
			if(CheckAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Tavern_DA"))
            {
                link.l1 = StringFromKey("Beliz_Tavern_24");
                link.l1.go = "PDM_ONV_Sprashivaem_Pro_Karlu";
            }
		break;
		//******************** Фр.линейка, квест №7. Спасение Рока Бразильца ******************
		case "Step_F7_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Beliz_Tavern_11", GetAddress_Form(NPChar)),
						StringFromKey("Beliz_Tavern_12"),
						StringFromKey("Beliz_Tavern_13"),
						StringFromKey("Beliz_Tavern_14"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Beliz_Tavern_15"),
						StringFromKey("Beliz_Tavern_16", pchar),
						StringFromKey("Beliz_Tavern_17", pchar),
						StringFromKey("Beliz_Tavern_18"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F7_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_F7_2":
			dialog.text = StringFromKey("Beliz_Tavern_19", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Beliz_Tavern_20");
			link.l1.go = "Step_F7_3";
		break;
		case "Step_F7_3":
			dialog.text = StringFromKey("Beliz_Tavern_21", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Beliz_Tavern_22");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		//******************** Квест "Прокажённая" ******************
		case "PDM_ONV_Sprashivaem_Pro_Karlu_NeZnaet":
			dialog.text = StringFromKey("Beliz_Tavern_25");
			Link.l1 = StringFromKey("Beliz_Tavern_26");
			Link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Tavern_NET");
			AddQuestRecord("PDM_Ohota_na_vedmu", "6");
			AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.PDM_ONV_Detectiv_Jiteli_Beliz = true;
			pchar.questTemp.PDM_ONV_Detectiv_Oficiantka_Beliz = true;
			RemoveLandQuestmark_Main(CharacterFromID("Beliz_tavernkeeper"), "PDM_Ohota_na_vedmu");
		break;

		case "PDM_ONV_Sprashivaem_Pro_Karlu":
			dialog.text = StringFromKey("Beliz_Tavern_27");
			Link.l1 = StringFromKey("Beliz_Tavern_28");
			Link.l1.go = "PDM_ONV_SPKarlu_2";
			RemoveLandQuestmark_Main(CharacterFromID("Beliz_tavernkeeper"), "PDM_Ohota_na_vedmu");
		break;

		case "PDM_ONV_SPKarlu_2":
			dialog.text = StringFromKey("Beliz_Tavern_29", GetAddress_Form(NPChar));
			Link.l1 = StringFromKey("Beliz_Tavern_30");
			Link.l1.go = "PDM_ONV_SPKarlu_3";
			Link.l2 = StringFromKey("Beliz_Tavern_31");
			Link.l2.go = "PDM_ONV_SPKarlu_5";
		break;

		case "PDM_ONV_SPKarlu_3":
			dialog.text = StringFromKey("Beliz_Tavern_32", GetAddress_Form(NPChar));
			Link.l1 = StringFromKey("Beliz_Tavern_33");
			Link.l1.go = "PDM_ONV_SPKarlu_5";
			Link.l2 = StringFromKey("Beliz_Tavern_34");
			Link.l2.go = "PDM_ONV_SPKarlu_4";
		break;

		case "PDM_ONV_SPKarlu_4":
			dialog.text = StringFromKey("Beliz_Tavern_35");
			Link.l1 = StringFromKey("Beliz_Tavern_36");
			Link.l1.go = "PDM_ONV_SPKarlu_5";
			ChangeCharacterReputation(pchar, -2);
			AddMoneyToCharacter(pchar, 2000);
		break;

		case "PDM_ONV_SPKarlu_5":
			dialog.text = StringFromKey("Beliz_Tavern_37", pchar);
			Link.l1 = StringFromKey("Beliz_Tavern_38");
			Link.l1.go = "PDM_ONV_SPKarlu_6";
		break;

		case "PDM_ONV_SPKarlu_6":
			dialog.text = StringFromKey("Beliz_Tavern_39", GetAddress_Form(NPChar));
			Link.l1 = StringFromKey("Beliz_Tavern_40");
			Link.l1.go = "PDM_ONV_SPKarlu_7";
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Detectiv_Tavern_DA");
		break;

		case "PDM_ONV_SPKarlu_7":
			dialog.text = StringFromKey("Beliz_Tavern_41");
			Link.l1 = StringFromKey("Beliz_Tavern_42");
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_ONW_SilinoSpawn");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

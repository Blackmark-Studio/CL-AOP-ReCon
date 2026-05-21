// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Beliz_Mayor_3", RandPhraseSimple(
								StringFromKey("Beliz_Mayor_1"),
								StringFromKey("Beliz_Mayor_2"))),
						StringFromKey("Beliz_Mayor_4"),
						StringFromKey("Beliz_Mayor_5"),
						StringFromKey("Beliz_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Beliz_Mayor_9", RandPhraseSimple(
								StringFromKey("Beliz_Mayor_7", pchar),
								StringFromKey("Beliz_Mayor_8"))),
						StringFromKey("Beliz_Mayor_10"),
						StringFromKey("Beliz_Mayor_11"),
						StringFromKey("Beliz_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Квест "Прокажённая" -->
			if (CheckAttribute(pchar, "questTemp.PDM_ONV_VedmaKaznena"))
			{
				link.l1 = StringFromKey("Beliz_Mayor_29");
				link.l1.go = "PDM_ONV_VedmaKaznena";
			}
			// Квест "Прокажённая" <--
		break;

		case "Cupture_after":
			dialog.text = StringFromKey("Beliz_Mayor_15", RandPhraseSimple(
						StringFromKey("Beliz_Mayor_13"),
						StringFromKey("Beliz_Mayor_14")));
			link.l1 = StringFromKey("Beliz_Mayor_18", RandPhraseSimple(
						StringFromKey("Beliz_Mayor_16"),
						StringFromKey("Beliz_Mayor_17", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;
		//************************** Квестовые штрумы ************************
		//==> Третий квест англ.линейки: нападение на Белиз.
		case "EngLine3Quest_BelizAttack":
			dialog.text = StringFromKey("Beliz_Mayor_19", pchar);
			link.l1 = StringFromKey("Beliz_Mayor_20");
			link.l1.go = "Step_E3_1";
			AfterTownBattle();
		break;

		case "Step_E3_1":
			dialog.text = StringFromKey("Beliz_Mayor_21");
			link.l1 = StringFromKey("Beliz_Mayor_22");
			link.l1.go = "Step_E3_2";
		break;

		case "Step_E3_2":
			dialog.text = StringFromKey("Beliz_Mayor_23");
			link.l1 = StringFromKey("Beliz_Mayor_24");
			link.l1.go = "Step_E3_3";
		break;

		case "Step_E3_3":
			dialog.text = StringFromKey("Beliz_Mayor_25");
			link.l1 = StringFromKey("Beliz_Mayor_26");
			link.l1.go = "Step_E3_4";
		break;

		case "Step_E3_4":
			dialog.text = StringFromKey("Beliz_Mayor_27");
			link.l1 = StringFromKey("Beliz_Mayor_28");
			link.l1.go = "Step_E3_5";
		break;

		case "Step_E3_5":
			NextDiag.CurrentNode = "Cupture_after";
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			SetReturn_Gover_Dialog_Exit(NPChar);
			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
			Achievement_AddStats_SturmColonies();
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("Henry Morgan")], true);
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("Jackman")], true);
			LAi_LoginInCaptureTown(&characters[GetCharacterIndex("John Morris")], true);
			DoReloadCharacterToLocation("Beliz_fort", "goto", "goto61");
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "Beliz_fort", "goto", "goto13");
			LAi_SetStayType(characterFromID("Henry Morgan"));
			characters[GetCharacterIndex("Henry Morgan")].dialog.currentnode = "Gold_found_in_fort";
			AddLandQuestmark_Main(characterFromID("Henry Morgan"), "Eng_Line");
			if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))   // Эта фигня нужна для определения, взял ли ГГ этих перцев на дело. Если нет, то и их в форте не будет.
			{
				ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Beliz_fort", "goto", "goto72");
				LAi_SetStayType(characterFromID("Jackman"));
				characters[GetCharacterIndex("Jackman")].dialog.currentnode = "Gold_found_in_fort";
				AddLandQuestmark_Main(characterFromID("Jackman"), "Eng_Line");
			}
			if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
			{
				ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "Beliz_fort", "goto", "goto01");
				LAi_SetStayType(characterFromID("John Morris"));
				characters[GetCharacterIndex("John Morris")].dialog.currentnode = "Gold_found_in_fort";
				AddLandQuestmark_Main(characterFromID("John Morris"), "Eng_Line");
			}
			LAi_LocationFightDisable(&Locations[FindLocation("Beliz_fort")], true);
			// ==> Дележ золота. Можно не брать Джекмена и Джона Морриса вообще в эскадру.
			// === Квест будет выполнен, а золото поделено соответственно.
			pchar.questTemp.BelizGoldQty = 3300 / sti(pchar.questTemp.CompanionQuantity);   // Нужно для контроля продаж золота Моргану, чтоб не продавать возможно уже существующее у ГГ золото.
			// грузим ГГ и его эскадру (не квестовые)
			SetCharacterGoods(pchar, GOOD_GOLD, GetCargoGoods(pchar, GOOD_GOLD) + sti(pchar.questTemp.BelizGoldQty));// перегруз
			if (IsCompanion(characterFromID("Henry Morgan")))
			{
				AddCharacterGoodsSimple(characterFromID("Henry Morgan"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));
			}
			if (IsCompanion(characterFromID("Jackman")))
			{
				AddCharacterGoodsSimple(characterFromID("Jackman"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));
			}
			if (IsCompanion(characterFromID("John Morris")))
			{
				AddCharacterGoodsSimple(characterFromID("John Morris"), GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));
			}
			Log_SetStringToLog(StringFromKey("InfoMessages_186"));
			InterfaceStates.Buttons.Save.enable = false;
			chrDisableReloadToLocation = true;
		break;
		
		// Квест "Прокажённая" -->
		case "PDM_ONV_VedmaKaznena":
            dialog.text = StringFromKey("Beliz_Mayor_30");
            link.l1 = StringFromKey("Beliz_Mayor_31");
            link.l1.go = "PDM_ONV_Nagrada";
			AddMoneyToCharacter(pchar, 15000);
        break;

		case "PDM_ONV_Nagrada":
			DialogExit();
			
			AddQuestRecord("PDM_Ohota_na_vedmu", "15");
			if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("PDM_Ohota_na_vedmu");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_VedmaKaznena");
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 15);
			AddSimpleRumour(StringFromKey("Beliz_Mayor_32"),SPAIN,7,1);
			RemoveLandQuestmark_Main(CharacterFromID("Beliz_Mayor"), "PDM_Ohota_na_vedmu");
			RemoveMapQuestMark("Beliz_town", "PDM_Ohota_na_vedmu");
			pchar.questTemp.PDM_ONW_Completed = "Spain";
			Achievment_Set(ACH_Ohota_na_vedmu);
        break;
		// Квест "Прокажённая" <--

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


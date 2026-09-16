// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Santiago_Mayor_3", RandPhraseSimple(
								StringFromKey("Santiago_Mayor_1"),
								StringFromKey("Santiago_Mayor_2"))),
						StringFromKey("Santiago_Mayor_4"),
						StringFromKey("Santiago_Mayor_5"),
						StringFromKey("Santiago_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Santiago_Mayor_9", RandPhraseSimple(
								StringFromKey("Santiago_Mayor_7", pchar),
								StringFromKey("Santiago_Mayor_8"))),
						StringFromKey("Santiago_Mayor_10"),
						StringFromKey("Santiago_Mayor_11"),
						StringFromKey("Santiago_Mayor_12", GetAddress_FormToNPC(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//===> Проверка состояния текущего квеста
			if (pchar.questTemp.State == "Sp5LaVegaAttack_toSantiago")
			{
				dialog.text = StringFromKey("Santiago_Mayor_13", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Santiago_Mayor_14", pchar);
				link.l1.go = "Step_S5_1";
			}
			if (pchar.questTemp.State == "Sp5LaVegaAttack_WeWon")
			{
				dialog.text = StringFromKey("Santiago_Mayor_15");
				link.l1 = StringFromKey("Santiago_Mayor_16");
				link.l1.go = "Step_S5_6";
			}
		//<=== Проверка состояния текущего квеста
		break;

		case "Cupture_after":
			dialog.text = StringFromKey("Santiago_Mayor_19", RandPhraseSimple(
						StringFromKey("Santiago_Mayor_17"),
						StringFromKey("Santiago_Mayor_18")));
			link.l1 = StringFromKey("Santiago_Mayor_22", RandPhraseSimple(
						StringFromKey("Santiago_Mayor_20"),
						StringFromKey("Santiago_Mayor_21", pchar)));
			link.l1.go = "exit";
			NextDiag.TempNode = "Cupture_after";
		break;

		//********************** Девятый квест англ.линейки: нападение на Сантьяго ************************
		case "EL9_SantiagoAttack":
			dialog.text = StringFromKey("Santiago_Mayor_23", pchar);
			link.l1 = StringFromKey("Santiago_Mayor_24", pchar);
			link.l1.go = "Step_E9_1";
			AfterTownBattle();
		break;
		case "Step_E9_1":
			dialog.text = StringFromKey("Santiago_Mayor_25");
			link.l1 = StringFromKey("Santiago_Mayor_26");
			link.l1.go = "Step_E9_2";
		break;
		case "Step_E9_2":
			dialog.text = StringFromKey("Santiago_Mayor_27");
			link.l1 = StringFromKey("Santiago_Mayor_28", pchar);
			link.l1.go = "Step_E9_3";
		break;
		case "Step_E9_3":
			dialog.text = StringFromKey("Santiago_Mayor_29");
			link.l1 = StringFromKey("Santiago_Mayor_30");
			link.l1.go = "Step_E9_4";
		break;
		case "Step_E9_4":
			Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1); // статистика
			Achievement_AddStats_SturmColonies();
			AddQuestRecord("Eng_Line_9_AttackSantiago", "2");
			chrDisableReloadToLocation = false;
			Pchar.quest.AttackSantiago_FightWithPardal.win_condition.l1 = "location";
			Pchar.quest.AttackSantiago_FightWithPardal.win_condition.l1.location = "Cuba1";
			Pchar.quest.AttackSantiago_FightWithPardal.win_condition = "AttackSantiago_FightWithPardal";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			// ==> Меняем имя и модель у губера,
			npchar.model = "usurer_3";
			npchar.name = FindPersonalName("AttackSantiago_name");
			npchar.lastname = FindPersonalName("AttackSantiago_lastname");
			SendMessage(npchar, "lss", MSG_CHARACTER_SETMODEL, npchar.model, npchar.model.animation);
			FaceMaker(npchar);
			// ==> а пленным делаем Альбермаля.
			sld = GetCharacter(NPC_GenerateCharacter("Himenes", "huber_spa", "man", "man", 10, SPAIN, -1, false));
			LAi_SetStayTypeNoGroup(sld);
			sld.name = FindPersonalName("Himenes_name");
			sld.lastname = FindPersonalName("Himenes_lastname");
			SetCharacterRemovable(sld, false);
			AddPassenger(pchar, sld, true);
			SetReturn_Gover_Dialog_Exit(NPChar);
			DoReloadCharacterToLocation("Santiago_town", "reload", "reload3");
			NextDiag.CurrentNode = "Cupture_after";
			chrDisableReloadToLocation = false;
			DialogExit();
		break;
		//********************** Квест №5, Нападение на Ла Вегу. ************************
		case "Step_S5_1":
			dialog.text = StringFromKey("Santiago_Mayor_31");
			link.l1 = StringFromKey("Santiago_Mayor_32", pchar);
			link.l1.go = "Step_S5_2";
		break;
		case "Step_S5_2":
			dialog.text = StringFromKey("Santiago_Mayor_33");
			link.l1 = StringFromKey("Santiago_Mayor_34", pchar);
			link.l1.go = "Step_S5_3";
		break;
		case "Step_S5_3":
			dialog.text = StringFromKey("Santiago_Mayor_35");
			link.l1 = StringFromKey("Santiago_Mayor_36");
			link.l1.go = "Step_S5_4";
		break;
		case "Step_S5_4":
			dialog.text = StringFromKey("Santiago_Mayor_37");
			link.l1 = StringFromKey("Santiago_Mayor_38");
			link.l1.go = "Step_S5_5";
		break;
		case "Step_S5_5":
			dialog.text = StringFromKey("Santiago_Mayor_39");
			link.l1 = StringFromKey("Santiago_Mayor_40");
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp5LaVegaAttack_AttackLaVega";
			AddQuestRecord("Spa_Line_5_LaVegaAttack", "2");
			Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition.l1 = "location";
			Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition.l1.location = "LaVega_town";    // Sinistra Теперь сражение происходит сразу в городе из-за новой локации
			Pchar.quest.Sp5LaVegaAttack_AttackGoOn.win_condition = "Sp5LaVegaAttack_AttackGoOn";
			pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry3 = Rand(7) + 1;
			pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry4 = Rand(7) + 1;
			pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry5 = Rand(7) + 1;
			pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry7 = Rand(7) + 1;
			pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry8 = Rand(7) + 1;
			pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry10 = Rand(7) + 1;
			pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry14 = Rand(7) + 1;
			pchar.GenQuestBox.LaVega_townhall.box1.items.jewelry17 = Rand(7) + 1;
			pchar.GenQuestBox.LaVega_townhall.box1.items.cirass4 = 1;
			sld = characterFromId("Edward Mansfield");
			sld.Default.Crew.Quantity = 1700;
			sld.Default.Crew.MinQuantity = 1100;
			sld.from_sea = ""; // для захвата с суши
			sld.Default = "LaVega_townhall";  // чтоб сухопутные города вернули население; TODO: ???
			sld.Default.BoardLocation = "LaVega_town";
			SetLocationCapturedState("Lavega_town", true);
			//огонь и пламень
			locations[FindLocation("LaVega_town")].models.always.locatorsl2 = "LaVega_1_quest";
			locations[FindLocation("LaVega_town")].models.always.locatorsl3 = "LaVega_locators_quest";
			locations[FindLocation("LaVega_town")].models.day.charactersPatch = "LaVega_patch_day_quest";
			locations[FindLocation("LaVega_town")].models.night.charactersPatch = "LaVega_patch_night_quest";
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_S5_6":
			dialog.text = StringFromKey("Santiago_Mayor_41", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Santiago_Mayor_42", pchar);
			link.l1.go = "Step_S5_7";
		break;
		case "Step_S5_7":
			dialog.text = StringFromKey("Santiago_Mayor_43");
			link.l1 = StringFromKey("Santiago_Mayor_44");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 125000);
			pchar.questTemp.State = "Sp5LaVegaAttack_BackToHavana";
			AddQuestRecord("Spa_Line_5_LaVegaAttack", "4");
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}


// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Tavern_3", RandPhraseSimple(
								StringFromKey("FortFrance_Tavern_1"),
								StringFromKey("FortFrance_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("FortFrance_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("FortFrance_Tavern_5"),
						StringFromKey("FortFrance_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Tavern_9", RandPhraseSimple(
								StringFromKey("FortFrance_Tavern_7", pchar),
								StringFromKey("FortFrance_Tavern_8"))),
						StringFromKey("FortFrance_Tavern_10"),
						StringFromKey("FortFrance_Tavern_11"),
						StringFromKey("FortFrance_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.piratesLine == "BlackLabel_toLaVega")
			{
				link.l1 = StringFromKey("FortFrance_Tavern_13");
				link.l1.go = "PL_Q2_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_KV"))    //Квест ***Невыносимая жара***		(Вино)
			{
				link.l1 = StringFromKey("FortFrance_Tavern_14", pchar);
				link.l1.go = "PDM_PJ_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_KR"))    //Квест ***Невыносимая жара***		(Ром)
			{
				link.l1 = StringFromKey("FortFrance_Tavern_15");
				link.l1.go = "PDM_PJ_Rom_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_KV") && pchar.questTemp.PDM_PJ_KV == "Sangari_Jerome_Talk")
			{
				link.l1 = StringFromKey("FortFrance_Tavern_42");
				link.l1.go = "Sangari_Jerome_1";
			}
		break;
		case "PL_Q2_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("FortFrance_Tavern_16"),
						StringFromKey("FortFrance_Tavern_17", pchar),
						StringFromKey("FortFrance_Tavern_18"),
						StringFromKey("FortFrance_Tavern_19"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("FortFrance_Tavern_20"),
						StringFromKey("FortFrance_Tavern_21", pchar),
						StringFromKey("FortFrance_Tavern_22"), "...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

		case "PDM_PJ_1":
			dialog.text = StringFromKey("FortFrance_Tavern_23");
			link.l1 = StringFromKey("FortFrance_Tavern_24");
			link.l1.go = "PDM_PJ_2";
		break;

		case "PDM_PJ_2":
			dialog.text = StringFromKey("FortFrance_Tavern_25", GetAddress_Form(NPChar));
			// 1. Вариант со скидкой (Цена 450) — показываем ПЛЮСОМ к остальным, если пройдена проверка
			if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 4) && sti(pchar.money) >= 450)
			{
				link.l1 = StringFromKey("FortFrance_Tavern_43");
				link.l1.go = "PDM_PJ_Vino_Discount";
			}
			// 2. Стандартные варианты (Цена 700) — показываем, если есть деньги
			if (sti(pchar.money) >= 700)
			{
				link.l2 = StringFromKey("FortFrance_Tavern_26", npchar.name);
				link.l2.go = "PDM_PJ_Beru_1";

				link.l3 = StringFromKey("FortFrance_Tavern_27");
				link.l3.go = "PDM_PJ_Beru_2";
			}
			// 3. Реплика при нехватке денег — если денег меньше 450
			if (sti(pchar.money) < 450)
			{
				link.l4 = StringFromKey("FortFrance_Tavern_44");
				link.l4.go = "exit";
			}
			// 4. Обычный отказ (всегда доступен)
			link.l5 = StringFromKey("FortFrance_Tavern_28");
			link.l5.go = "exit";
		break;

		case "PDM_PJ_Vino_Discount":
			dialog.text = StringFromKey("FortFrance_Tavern_45");
				link.l1 = StringFromKey("FortFrance_Tavern_46");
				link.l1.go = "PDM_PJ_Beru_3";
				AddMoneyToCharacter(pchar, -450);
				AddCharacterExpToSkill(pchar, "Commerce", 10);
		break;

		case "PDM_PJ_Beru_1":
			dialog.text = StringFromKey("FortFrance_Tavern_29", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortFrance_Tavern_30", npchar.name);
			AddMoneyToCharacter(pchar, -700);
			link.l1.go = "PDM_PJ_Beru_3";
		break;

		case "PDM_PJ_Beru_2":
			dialog.text = StringFromKey("FortFrance_Tavern_31", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortFrance_Tavern_32");
			link.l1.go = "PDM_PJ_Beru_3";
			AddMoneyToCharacter(pchar, -700);
		break;

		case "PDM_PJ_Beru_3":
			DialogExit();

			AddCharacterExpToSkill(pchar, "Commerce", 5);
			AddQuestRecord("PDM_Proklyataya_Jara", "2");
			GiveItem2Character(PChar, "PDM_PJ_Vino");
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KV");
			DeleteAttribute(pchar, "questTemp.PDM_PJ_SS");
			sld = CharacterFromID("PDM_PJ_Strajnik_1");
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Prines_Vino_1";
			AddLandQuestMark_Main(sld, "PDM_Proklyataya_Jara");

			RemoveLandQuestMark_Main(npchar, "PDM_Proklyataya_Jara");
			RemoveLandQuestMarkToFantoms_Main("Maltie_officer", "PDM_Proklyataya_Jara");
		break;

		case "PDM_PJ_Rom_1":
			dialog.text = StringFromKey("FortFrance_Tavern_33", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortFrance_Tavern_34", npchar.name);
			link.l1.go = "PDM_PJ_Rom_2";
		break;

		case "PDM_PJ_Rom_2":
			dialog.text = StringFromKey("FortFrance_Tavern_35", pchar, GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortFrance_Tavern_36");
			link.l1.go = "PDM_PJ_Rom_3";
		break;

		case "PDM_PJ_Rom_3":
			dialog.text = StringFromKey("FortFrance_Tavern_37");
			// 2. Стандартный вариант (Цена 300) — показываем, если есть деньги
			if (sti(pchar.money) >= 300)
			{
				link.l1 = StringFromKey("FortFrance_Tavern_39");
				link.l1.go = "PDM_PJ_Rom_4";
			}
			// 3. Реплика при нехватке денег — если денег меньше 450
			if (sti(pchar.money) < 300)
			{
				link.l2 = StringFromKey("FortFrance_Tavern_47");
				link.l2.go = "exit";
			}
			link.l3 = StringFromKey("FortFrance_Tavern_38", npchar.name);
			link.l3.go = "exit";
		break;

		case "PDM_PJ_Rom_4":
			dialog.text = StringFromKey("FortFrance_Tavern_40", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FortFrance_Tavern_41", npchar.name);
			link.l1.go = "PDM_PJ_Rom_5";
			AddMoneyToCharacter(pchar, -300);
		break;

		case "PDM_PJ_Rom_5":
			DialogExit();

			GiveItem2Character(PChar, "PDM_PJ_Rom");
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KR");
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Prines_Rom_1";
			AddQuestRecord("PDM_Proklyataya_Jara", "4");
			AddLandQuestMark_Main(sld, "PDM_Proklyataya_Jara");
			AddCharacterExpToSkill(pchar, "Commerce", 3);

			sld = CharacterFromID("PDM_PJ_Strajnik_1");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "drunk", "", 1.0);

			RemoveLandQuestMark_Main(npchar, "PDM_Proklyataya_Jara");
		break;

		// --- Продолжение: Диалог с Жеромом ---
		case "Sangari_Jerome_1":
			dialog.text = StringFromKey("FortFrance_Tavern_48");
			link.l1 = StringFromKey("FortFrance_Tavern_49");
			link.l1.go = "Sangari_Jerome_2";
		break;

		case "Sangari_Jerome_2":
			dialog.text = StringFromKey("FortFrance_Tavern_50");
			link.l1 = StringFromKey("FortFrance_Tavern_51");
			link.l1.go = "Sangari_Recipe_Good";
			link.l2 = StringFromKey("FortFrance_Tavern_52");
			link.l2.go = "Sangari_Recipe_Bad";
		break;

		case "Sangari_Recipe_Good":
			dialog.text = StringFromKey("FortFrance_Tavern_53");
			link.l1 = StringFromKey("FortFrance_Tavern_54");
			link.l1.go = "Sangari_Final_Exit";
			AddQuestRecord("PDM_Proklyataya_Jara", "7"); // мирно
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			GiveItem2Character(pchar, "recipe_potionsangari"); // Выдача рецепта
			Log_info(StringFromKey("InfoMessages_153"));
		break;

		case "Sangari_Recipe_Bad":
			dialog.text = StringFromKey("FortFrance_Tavern_55");
			link.l1 = StringFromKey("FortFrance_Tavern_56");
			link.l1.go = "Sangari_Final_Exit";
			AddQuestRecord("PDM_Proklyataya_Jara", "8"); // угрожаем
			AddCharacterExpToSkill(pchar, "Leadership", 130);
			AddCharacterExpToSkill(pchar, "Fortune", 130);
			ChangeCharacterReputation(pchar, -5);
			AddMoneyToCharacter(pchar, 1000); // Возвращаем деньги (примерно 1000 золотых за вино и ром)
			GiveItem2Character(pchar, "recipe_potionsangari");
			Log_Info("");
			Log_info(StringFromKey("InfoMessages_153"));
		break;

		case "Sangari_Final_Exit":
			DialogExit();
			CloseQuestHeader("PDM_Proklyataya_Jara");
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KV");
			RemoveLandQuestMark_Main(npchar, "PDM_Proklyataya_Jara");
			Achievment_Set(ACH_Proklyataya_zhara);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

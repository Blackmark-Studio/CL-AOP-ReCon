// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Tavern_1", GetCityName(npchar.city)),
						StringFromKey("Tortuga_Tavern_2"),
						StringFromKey("Tortuga_Tavern_3"),
						StringFromKey("Tortuga_Tavern_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Tavern_5", NPChar.name),
						StringFromKey("Tortuga_Tavern_6", pchar),
						StringFromKey("Tortuga_Tavern_7"),
						StringFromKey("Tortuga_Tavern_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (pchar.questTemp.Slavetrader == "FindRatTortuga")
			{
				link.l1 = StringFromKey("Tortuga_Tavern_9");
				link.l1.go = "Tortuga_ratT_1";
			}
			// Линейка Ле Баска. Начало.
			if (CheckAttrValue(pchar, "quest.Shadow_of_a_big_deal", "Talk_Tavern"))
			{
                link.l3 = StringFromKey("Tortuga_Tavern_92");
                link.l3.go = "Shadow_of_a_big_deal_1";
            }
			// ==> Проверяем поле состояния квестов.
			switch (pchar.questTemp.State)
			{
				case "WormEnglPlans_WormPicarder": //Голландская линейка, квест №3. узнаем о Пеьере Пикардийце.
					link.l1 = StringFromKey("Tortuga_Tavern_10");
					link.l1.go = "Step_H3_1";
				break;
				case "DelivLettTortuga_toStranger": //Голландская линейка, квест №7. узнаем о ожидающем ГГ человеке.
					link.l1 = StringFromKey("Tortuga_Tavern_11", pchar);
					link.l1.go = "Step_H7_1";
				break;
				case "DelivLettTortuga_AfterRape": //Голландская линейка, квест №7. пытаемся узнать, кто был грабитель.
					link.l1 = StringFromKey("Tortuga_Tavern_12");
					link.l1.go = "Step_H7_2";
				break;
				case "SeekBible_toTavern": //Голландская линейка, квест №8. узнаем, где Лоран де Граф.
					link.l1 = StringFromKey("Tortuga_Tavern_13");
					link.l1.go = "Step_H8_1";
				break;
				case "TakeRockBras_toTortuga": //Испанская линейка, квест №3. узнаем, где Рок Бразилец.
					link.l1 = StringFromKey("Tortuga_Tavern_14");
					link.l1.go = "Step_S3_1";
				break;
				case "Sp4Detection_toTortuga": //Испанская линейка, квест №4. узнаем о донне Анне.
					link.l1 = StringFromKey("Tortuga_Tavern_15");
					link.l1.go = "Step_S4_1";
				break;
				case "Sp6TakeMess_toTotuga": //Испанская линейка, квест №6. узнаем о вестовом
					link.l1 = StringFromKey("Tortuga_Tavern_16");
					link.l1.go = "Step_S6_1";
				break;
				case "Sp6TakeMess_waitMessanger": //Испанская линейка, квест №6. узнаем о вестовом
					link.l1 = StringFromKey("Tortuga_Tavern_17");
					link.l1.go = "Step_S6_1";
				break;
			}
		// <== Проверяем поле состояния квестов.
		break;

		// Ле Баск. Начало.
		case "Shadow_of_a_big_deal_1":
			dialog.text = StringFromKey("Tortuga_Tavern_93");
			link.l1 = StringFromKey("Tortuga_Tavern_94", pchar);
			link.l1.go = "Shadow_of_a_big_deal_2";
		break;

		case "Shadow_of_a_big_deal_2":
			dialog.text = StringFromKey("Tortuga_Tavern_95");
			link.l1 = StringFromKey("Tortuga_Tavern_96");
			link.l1.go = "Shadow_of_a_big_deal_3";
		break;

		case "Shadow_of_a_big_deal_3":
			dialog.text = StringFromKey("Tortuga_Tavern_97");
			link.l1 = "...";
			link.l1.go = "Shadow_of_a_big_deal_3_exit";
		break;

		case "Shadow_of_a_big_deal_3_exit":
			AddDialogExitQuest("Shadow_of_a_big_deal_2");
			dialogexit();
		break;

		case "Shadow_of_a_big_deal_4":
			dialog.text = StringFromKey("Tortuga_Tavern_98");
			link.l1 = StringFromKey("Tortuga_Tavern_99");
			link.l1.go = "Shadow_of_a_big_deal_5";
		break;

		case "Shadow_of_a_big_deal_5":
			dialog.text = StringFromKey("Tortuga_Tavern_100");
			link.l1 = StringFromKey("Tortuga_Tavern_101");
			link.l1.go = "Shadow_of_a_big_deal_6_exit";
		break;

		case "Shadow_of_a_big_deal_6_exit":
			AddDialogExitQuest("Shadow_of_a_big_deal_6");
			dialogexit();
		break;

		case "Shadow_of_a_big_deal_7":
			dialog.text = StringFromKey("Tortuga_Tavern_102");
			link.l1 = StringFromKey("Tortuga_Tavern_103");
			link.l1.go = "Shadow_of_a_big_deal_8";
		break;

		case "Shadow_of_a_big_deal_8":
			dialog.text = StringFromKey("Tortuga_Tavern_104");
			link.l1 = StringFromKey("Tortuga_Tavern_105");
			link.l1.go = "Shadow_of_a_big_deal_10_exit";
		break;

		case "Shadow_of_a_big_deal_10_exit":
			AddDialogExitQuest("Shadow_of_a_big_deal_24");
			dialogexit();
		break;

case "":
dialog.text = "";
link.l1 = "";
link.l1.go = "";
break;


		//===================================== Голл. линейка, квест №3 =========================================
		case "Step_H3_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Tavern_18"),
						StringFromKey("Tortuga_Tavern_19", pchar),
						StringFromKey("Tortuga_Tavern_20"),
						StringFromKey("Tortuga_Tavern_21"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Tavern_22"),
						StringFromKey("Tortuga_Tavern_23", pchar),
						StringFromKey("Tortuga_Tavern_24"),
						StringFromKey("Tortuga_Tavern_25", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H3_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_H3_2":
			dialog.text = StringFromKey("Tortuga_Tavern_26");
			link.l1 = StringFromKey("Tortuga_Tavern_27");
			link.l1.go = "Step_H3_3";
		break;
		case "Step_H3_3":
			dialog.text = StringFromKey("Tortuga_Tavern_28");
			link.l1 = StringFromKey("Tortuga_Tavern_29");
			link.l1.go = "exit";
			pchar.questTemp.Hol_Line_AboutWorm.Tavern = true;
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "7");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
		//============================ Голл. линейка, квест №7. узнаем о ожидающем ГГ челе =======================
		case "Step_H7_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Tavern_30"),
						StringFromKey("Tortuga_Tavern_31", pchar),
						StringFromKey("Tortuga_Tavern_32"),
						StringFromKey("Tortuga_Tavern_33"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Tavern_34"),
						StringFromKey("Tortuga_Tavern_35", pchar),
						StringFromKey("Tortuga_Tavern_36"),
						StringFromKey("Tortuga_Tavern_37"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "none", "none", "none", npchar, Dialog.CurrentNode);
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
		case "Step_H7_2":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Tavern_38"),
						StringFromKey("Tortuga_Tavern_39", pchar),
						StringFromKey("Tortuga_Tavern_40"),
						StringFromKey("Tortuga_Tavern_41"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Tavern_42"),
						StringFromKey("Tortuga_Tavern_43", pchar),
						StringFromKey("Tortuga_Tavern_44"),
						StringFromKey("Tortuga_Tavern_45"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_H7_3", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_H7_3":
			dialog.text = StringFromKey("Tortuga_Tavern_46");
			link.l1 = StringFromKey("Tortuga_Tavern_47");
			link.l1.go = "Step_H7_4";
		break;
		case "Step_H7_4":
			dialog.text = StringFromKey("Tortuga_Tavern_48");
			link.l1 = StringFromKey("Tortuga_Tavern_49");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
		//============================ Голл. линейка, квест №8. узнаем о Лоране де Графе =======================
		case "Step_H8_1":
			dialog.text = StringFromKey("Tortuga_Tavern_50");
			link.l1 = StringFromKey("Tortuga_Tavern_51");
			link.l1.go = "Step_H8_2";
		break;
		case "Step_H8_2":
			dialog.text = StringFromKey("Tortuga_Tavern_52");
			link.l1 = StringFromKey("Tortuga_Tavern_53");
			link.l1.go = "Step_H8_3";
		break;
		case "Step_H8_3":
			dialog.text = StringFromKey("Tortuga_Tavern_54");
			link.l1 = StringFromKey("Tortuga_Tavern_55", pchar);
			link.l1.go = "Step_H8_4";
		break;
		case "Step_H8_4":
			dialog.text = StringFromKey("Tortuga_Tavern_56");
			link.l1 = StringFromKey("Tortuga_Tavern_57");
			link.l1.go = "exit";
			pchar.questTemp.State = "SeekBible_toDeGraf";
			AddQuestRecord("Hol_Line_8_SeekBible", "5");
			Pchar.quest.SeekBible_SaveDeGraf.win_condition.l1 = "location";
			Pchar.quest.SeekBible_SaveDeGraf.win_condition.l1.location = "Cartahena";
			Pchar.quest.SeekBible_SaveDeGraf.win_condition = "SeekBible_SaveDeGraf";
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
		//============================ Исп. линейка, квест №3. узнаем о Роке Бразильце =======================
		case "Step_S3_1":
			dialog.text = StringFromKey("Tortuga_Tavern_58");
			link.l1 = StringFromKey("Tortuga_Tavern_59");
			link.l1.go = "Step_S3_2";
		break;
		case "Step_S3_2":
			dialog.text = StringFromKey("Tortuga_Tavern_60");
			link.l1 = StringFromKey("Tortuga_Tavern_61");
			link.l1.go = "Step_S3_3";
		break;
		case "Step_S3_3":
			dialog.text = StringFromKey("Tortuga_Tavern_62");
			link.l1 = StringFromKey("Tortuga_Tavern_63");
			link.l1.go = "exit";
			pchar.questTemp.State = "TakeRockBras_toNearestMaracaibo";
			AddQuestRecord("Spa_Line_3_RockBrasilian", "2");
			pchar.quest.TakeRockBras_toRock.win_condition.l1 = "location";
			pchar.quest.TakeRockBras_toRock.win_condition.l1.location = "Maracaibo";
			pchar.quest.TakeRockBras_toRock.win_condition = "TakeRockBras_toRock";
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		//============================ Испанская линейка, квест №4. узнаем о донне Анне. =======================
		case "Step_S4_1":
			dialog.text = StringFromKey("Tortuga_Tavern_64");
			link.l1 = StringFromKey("Tortuga_Tavern_65");
			link.l1.go = "Step_S4_2";
		break;
		case "Step_S4_2":
			dialog.text = StringFromKey("Tortuga_Tavern_66");
			link.l1 = StringFromKey("Tortuga_Tavern_67");
			link.l1.go = "Step_S4_3";
		break;
		case "Step_S4_3":
			dialog.text = StringFromKey("Tortuga_Tavern_68");
			link.l1 = StringFromKey("Tortuga_Tavern_69");
			link.l1.go = "Step_S4_4";
		break;
		case "Step_S4_4":
			dialog.text = StringFromKey("Tortuga_Tavern_70");
			link.l1 = StringFromKey("Tortuga_Tavern_71");
			link.l1.go = "Step_S4_5";
		break;
		case "Step_S4_5":
			dialog.text = StringFromKey("Tortuga_Tavern_72");
			link.l1 = StringFromKey("Tortuga_Tavern_73", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp4Detection_toDEstre";
			AddQuestRecord("Spa_Line_4_MirderDetection", "5");
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("ServantDEstre"), "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;
		//============================ Испанская линейка, квест №6. перехватить вестового. =======================
		case "Step_S6_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Tortuga_Tavern_74"),
						StringFromKey("Tortuga_Tavern_75"),
						StringFromKey("Tortuga_Tavern_76"),
						StringFromKey("Tortuga_Tavern_77"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Tortuga_Tavern_78"),
						StringFromKey("Tortuga_Tavern_79"),
						StringFromKey("Tortuga_Tavern_80"),
						StringFromKey("Tortuga_Tavern_81"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S6_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_S6_2":
			dialog.text = StringFromKey("Tortuga_Tavern_82");
			link.l1 = StringFromKey("Tortuga_Tavern_83");
			link.l1.go = "Step_S6_3";
		break;
		case "Step_S6_3":
			dialog.text = StringFromKey("Tortuga_Tavern_84", pchar);
			link.l1 = StringFromKey("Tortuga_Tavern_85");
			link.l1.go = "exit";
			pchar.questTemp.State.Open = 1;
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false);
			AddMoneyToCharacter(pchar, -100);
			if (CheckAttribute(pchar, "questTemp.State.Sp6Ok"))
			{
				SetTimerCondition("Sp6TakeMess_waitingBoy", 0, 0, rand(7) + 1, false);
				DeleteAttribute(pchar, "questTemp.State.Sp6Ok");
			}
			else
			{
				pchar.questTemp.State.Sp6Ok = 1;
			}
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;

		case "Tortuga_ratT_1":
			dialog.text = StringFromKey("Tortuga_Tavern_86");
			link.l1 = StringFromKey("Tortuga_Tavern_87", pchar.questTemp.Slavetrader.ShipName);
			link.l1.go = "Tortuga_ratT_2";
		break;

		case "Tortuga_ratT_2":
			dialog.text = StringFromKey("Tortuga_Tavern_88", pchar);
			link.l1 = StringFromKey("Tortuga_Tavern_89");
			link.l1.go = "Tortuga_ratT_3";
		break;

		case "Tortuga_ratT_3":
			dialog.text = StringFromKey("Tortuga_Tavern_90", pchar);
			link.l1 = StringFromKey("Tortuga_Tavern_91", npchar.name);
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_8");
			//pchar.questTemp.Slavetrader = "wait1";//затычка // < Затирает FindRatTortuga и херит подсказку Tortuga_PortMan

			RemoveLandQuestmark_Main(npchar, "Slavetrader");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

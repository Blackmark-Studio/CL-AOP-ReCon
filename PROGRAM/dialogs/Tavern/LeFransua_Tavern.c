// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LeFransua_Tavern_3", RandPhraseSimple(
								StringFromKey("LeFransua_Tavern_1"),
								StringFromKey("LeFransua_Tavern_2", GetAddress_Form(NPChar)))),
						StringFromKey("LeFransua_Tavern_4", GetAddress_Form(NPChar)),
						StringFromKey("LeFransua_Tavern_5"),
						StringFromKey("LeFransua_Tavern_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LeFransua_Tavern_9", RandPhraseSimple(
								StringFromKey("LeFransua_Tavern_7", pchar),
								StringFromKey("LeFransua_Tavern_8"))),
						StringFromKey("LeFransua_Tavern_10"),
						StringFromKey("LeFransua_Tavern_11"),
						StringFromKey("LeFransua_Tavern_12"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";

			// Dolphin. Францущский сюжет. Поиски Гранье
			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL2_s4")
			{
				link.l3 = StringFromKey("LeFransua_Tavern_13");
				link.l3.go = "FL2_1";
			}

			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL2_s4a" && sti(pchar.money) >= 500)
			{
				link.l3 = StringFromKey("LeFransua_Tavern_14");
				link.l3.go = "FL2_3";
			}
			// Эдвард Лоу
			string sPL = "";
			if (CheckAttribute(pchar, "questTemp.piratesLine"))
				sPL = pchar.questTemp.piratesLine;

			if (sPL != "")
			{
				if (sPL == "BlackLabel_toLaVega")
				{
					link.l2 = StringFromKey("LeFransua_Tavern_15");
					link.l2.go = "PL_Q2_1";
				}
				else if (sPL == "KillLoy_toSeek")
				{
					link.l2 = StringFromKey("LeFransua_Tavern_16");
					link.l2.go = "PL_Q3_1";
				}
			}

			//-->ОЗГ Кондотьер BMS
			string sHH = "";
			if (CheckAttribute(pchar, "questTemp.Headhunter"))
				sHH = pchar.questTemp.Headhunter;

			if (sHH != "")
			{
				if (sHH == "vector_barmen") // && Pchar.BaseNation == PIRATE теперь все могут брать. Konstrush
				{
					link.l1 = StringFromKey("LeFransua_Tavern_17");
					link.l1.go = "Barmen_check";
				}

				if (npchar.city == "LeFransua" && sHH == "barmen_wait")    // && Pchar.BaseNation == PIRATE теперь все могут брать Konstrush
				{
					link.l1 = StringFromKey("LeFransua_Tavern_18", npchar.name);
					link.l1.go = "Barmen_check";
				}
				if (sHH == "hunt_carlos_yes")
				{
					link.l1 = StringFromKey("LeFransua_Tavern_19", npchar.name);
					link.l1.go = "Endtaskhunt_1";
				}
				if (sHH == "next_task_2" && GetQuestPastDayParam("pchar.questTemp.Headhunter_next_task_2") > 9)
				{
					link.l1 = StringFromKey("LeFransua_Tavern_20", pchar, npchar.name);
					link.l1.go = "Givetaskhunt_2";
				}
				if (sHH == "hunt_houm_yes")
				{
					link.l1 = StringFromKey("LeFransua_Tavern_21", npchar.name);
					link.l1.go = "Endtaskhunt_2";
				}
				if (sHH == "next_task_3" && GetQuestPastDayParam("pchar.questTemp.Headhunter_next_task_3") > 14)
				{
					link.l1 = StringFromKey("LeFransua_Tavern_22", npchar.name);
					link.l1.go = "Givetaskhunt_3";
				}
				if (sHH == "hunt_rat_yes1")
				{
					link.l1 = StringFromKey("LeFransua_Tavern_23", pchar, npchar.name);
					link.l1.go = "Endtaskhunt_3";
				}
				if (sHH == "hunt_rat_yes2")
				{
					link.l1 = StringFromKey("LeFransua_Tavern_24", pchar, npchar.name);
					link.l1.go = "Endtaskhunt_3";
				}
				if (sHH == "next_task_4" && GetQuestPastDayParam("pchar.questTemp.Headhunter_next_task_4") > 17)
				{
					link.l1 = StringFromKey("LeFransua_Tavern_25", npchar.name);
					link.l1.go = "Givetaskhunt_4";
				}
				if (sHH == "hunt_halen_yes")
				{
					link.l1 = StringFromKey("LeFransua_Tavern_26", npchar.name);
					link.l1.go = "Endtaskhunt_4";
				}
				if (sHH == "hunt_ja_yes")
				{
					link.l1 = StringFromKey("LeFransua_Tavern_27", npchar.name);
					link.l1.go = "Endtaskhunt_5";
				}
			}
		break;

		// Dolphin. Францущский сюжет. Поиски Гранье ->
		case "FL2_1":
			dialog.text = StringFromKey("LeFransua_Tavern_28");
			link.l1 = StringFromKey("LeFransua_Tavern_29");
			link.l1.go = "FL2_2";
		break;

		case "FL2_2":
			dialog.text = StringFromKey("LeFransua_Tavern_30");
			link.l1 = StringFromKey("LeFransua_Tavern_31");
			link.l1.go = "exit";

			pchar.MainQuest = "FL2_s4a";

			if (sti(pchar.money) >= 500)
			{
				link.l2 = StringFromKey("LeFransua_Tavern_32");
				link.l2.go = "FL2_3";
			}
		break;

		case "FL2_3":
			AddMoneyToCharacter(pchar, -500);
			dialog.text = StringFromKey("LeFransua_Tavern_33");
			link.l1 = StringFromKey("LeFransua_Tavern_34");
			link.l1.go = "FL2_4";
		break;

		case "FL2_4":
			dialog.text = StringFromKey("LeFransua_Tavern_35");
			link.l1 = StringFromKey("LeFransua_Tavern_36");
			link.l1.go = "FL2_5";
		break;

		case "FL2_5":
			dialog.text = StringFromKey("LeFransua_Tavern_37");
			link.l1 = StringFromKey("LeFransua_Tavern_38");
			link.l1.go = "exit";

			AddDialogExitQuest("FL2_s5");
		break;
		// Dolphin. Францущский сюжет. Поиски Гранье <-

		//пиратка, квест №2, черная метка для Лоу
		case "PL_Q2_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LeFransua_Tavern_39"),
						StringFromKey("LeFransua_Tavern_40"),
						StringFromKey("LeFransua_Tavern_41"),
						StringFromKey("LeFransua_Tavern_42", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LeFransua_Tavern_43"),
						StringFromKey("LeFransua_Tavern_44", pchar),
						StringFromKey("LeFransua_Tavern_45", pchar), "...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q2_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q2_2":
			dialog.text = StringFromKey("LeFransua_Tavern_46", pchar);
			link.l1 = StringFromKey("LeFransua_Tavern_47");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_2_BlackLabel", "2");
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
		//пиратка, квест №3, поиски Лоу
		case "PL_Q3_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LeFransua_Tavern_48", pchar),
						StringFromKey("LeFransua_Tavern_49"),
						StringFromKey("LeFransua_Tavern_50"),
						StringFromKey("LeFransua_Tavern_51", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LeFransua_Tavern_52"),
						StringFromKey("LeFransua_Tavern_53"),
						StringFromKey("LeFransua_Tavern_54", pchar),
						StringFromKey("LeFransua_Tavern_55", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("PL_Q3_2", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "PL_Q3_2":
			dialog.text = StringFromKey("LeFransua_Tavern_56");
			link.l1 = StringFromKey("LeFransua_Tavern_57");
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = StringFromKey("LeFransua_Tavern_58");
			link.l1 = StringFromKey("LeFransua_Tavern_59");
			link.l1.go = "exit";
		break;

		case "Barmen_check":
			if (CheckPatents(pchar))
			{
				dialog.text = StringFromKey("LeFransua_Tavern_60");
				link.l1 = StringFromKey("LeFransua_Tavern_61");
				link.l1.go = "exit";
				CloseQuestHeader("Headhunt");
				Headhunter_CleanupAll("end_quest");
				RemoveLandQuestMark_Main(npchar, "Headhunt");
				RemoveMapQuestMark("LeFransua_town", "Headhunt");
				break;
			}
			if (sti(Pchar.Rank) < 5)
			{
				dialog.text = StringFromKey("LeFransua_Tavern_62");
				link.l1 = StringFromKey("LeFransua_Tavern_63");
				link.l1.go = "exit";
				pchar.questTemp.Headhunter = "barmen_wait";
				break;
			}
			if (sti(Pchar.Rank) > 40)
			{
				dialog.text = StringFromKey("LeFransua_Tavern_64");
				link.l1 = StringFromKey("LeFransua_Tavern_65");
				link.l1.go = "exit";
				CloseQuestHeader("Headhunt");
				Headhunter_CleanupAll("end_quest");
				RemoveLandQuestMark_Main(npchar, "Headhunt");
				RemoveMapQuestMark("LeFransua_town", "Headhunt");
				break;
			}
			dialog.text = StringFromKey("LeFransua_Tavern_66", pchar);
			link.l1 = StringFromKey("LeFransua_Tavern_67", npchar.name);
			link.l1.go = "barmen_history";
		break;

		case "barmen_history":
			dialog.text = StringFromKey("LeFransua_Tavern_68");
			link.l1 = StringFromKey("LeFransua_Tavern_69");
			link.l1.go = "barmen_history_1";
		break;

		case "barmen_history_1":
			dialog.text = StringFromKey("LeFransua_Tavern_70", pchar);
			link.l1 = StringFromKey("LeFransua_Tavern_71");
			link.l1.go = "barmen_history_2";
		break;

		case "barmen_history_2":
			dialog.text = StringFromKey("LeFransua_Tavern_72");
			link.l1 = StringFromKey("LeFransua_Tavern_73", pchar);
			link.l1.go = "barmen_history_3";
		break;

		case "barmen_history_3":
			dialog.text = StringFromKey("LeFransua_Tavern_74");
			link.l1 = StringFromKey("LeFransua_Tavern_75");
			link.l1.go = "barmen_history_4";
		break;

		case "barmen_history_4":
			dialog.text = StringFromKey("LeFransua_Tavern_76");
			link.l1 = StringFromKey("LeFransua_Tavern_77");
			link.l1.go = "barmen_history_5";
			link.l2 = StringFromKey("LeFransua_Tavern_78", pchar);
			link.l2.go = "exit_quest";
		break;

		case "exit_quest":
			dialog.text = StringFromKey("LeFransua_Tavern_79");
			link.l1 = StringFromKey("LeFransua_Tavern_80");
			link.l1.go = "exit";
			Headhunter_CleanupAll("end_quest");
			CloseQuestHeader("Headhunt");
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			RemoveMapQuestMark("LeFransua_town", "Headhunt");
		break;

		case "barmen_history_5":
			dialog.text = StringFromKey("LeFransua_Tavern_81");
			link.l1 = StringFromKey("LeFransua_Tavern_82");
			link.l1.go = "barmen_history_6";
		break;

		case "barmen_history_6":
			dialog.text = StringFromKey("LeFransua_Tavern_83");
			link.l1 = StringFromKey("LeFransua_Tavern_84");
			link.l1.go = "barmen_history_7";
		break;

		case "barmen_history_7":
			dialog.text = StringFromKey("LeFransua_Tavern_85");
			link.l1 = StringFromKey("LeFransua_Tavern_86");
			link.l1.go = "Givetaskhunt_1";
		break;

		case "Givetaskhunt_1":
			SelectCarlosCity();
			dialog.text = StringFromKey("LeFransua_Tavern_87", pchar.questTemp.Headhunter.Cityname);
			link.l1 = StringFromKey("LeFransua_Tavern_88");
			link.l1.go = "Givetaskhunt_1_1";
			pchar.questTemp.Headhunter = "hunt_carlos";
			pchar.questTemp.Headhunter.Chance = rand(1);
			CreateCarlos();
		break;

		case "Givetaskhunt_1_1":
			dialog.text = StringFromKey("LeFransua_Tavern_89");
			link.l1 = StringFromKey("LeFransua_Tavern_90", pchar, npchar.name);
			link.l1.go = "exit";
			AddQuestRecord("Headhunt", "1");
			AddQuestUserData("Headhunt", "sCity", pchar.questTemp.Headhunter.Cityname);
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			RemoveMapQuestMark("LeFransua_town", "Headhunt");
		break;

		case "Endtaskhunt_1":
			dialog.text = StringFromKey("LeFransua_Tavern_91");
			link.l1 = StringFromKey("LeFransua_Tavern_92");
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "next_task_2";
			SaveCurrentQuestDateParam("pchar.questTemp.Headhunter_next_task_2");
			AddMoneyToCharacter(pchar, 5000);
			AddItemLog(pchar, "chest", "1", StringFromKey("InfoMessages_136"), "Important_item");
			AddQuestRecord("Headhunt", "3");
		break;

		case "Givetaskhunt_2":
			if (CheckPatents(pchar))
			{
				dialog.text = StringFromKey("LeFransua_Tavern_93");
				link.l1 = StringFromKey("LeFransua_Tavern_94");
				link.l1.go = "exit";
				CloseQuestHeader("Headhunt");
				Headhunter_CleanupAll("end_quest");
				RemoveLandQuestMark_Main(npchar, "Headhunt");
				break;
			}
			pchar.questTemp.Headhunter.Chance = rand(4);
			pchar.questTemp.Headhunter.Chance1 = rand(1);
			SelectHoumCity();
			dialog.text = StringFromKey("LeFransua_Tavern_95");
			link.l1 = StringFromKey("LeFransua_Tavern_96");
			link.l1.go = "Givetaskhunt_2_1";
		break;

		case "Givetaskhunt_2_1":
			pchar.questTemp.Headhunter = "Houm";
			AddQuestRecord("Headhunt", "4");
			Log_TestInfo("Дом находится в " + pchar.questTemp.Headhunter.Cityname + "");
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			AddLandQuestMark_Main(CharacterFromID(pchar.questTemp.Headhunter.City + "_PortMan"), "Headhunt");
			DialogExit();
		break;

		case "Endtaskhunt_2":
			dialog.text = StringFromKey("LeFransua_Tavern_97");
			link.l1 = StringFromKey("LeFransua_Tavern_98");
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "next_task_3";
			SaveCurrentQuestDateParam("pchar.questTemp.Headhunter_next_task_3");
			AddMoneyToCharacter(pchar, 10000);
			AddItemLog(pchar, "chest", "2", StringFromKey("InfoMessages_134"), "Important_item");
			AddQuestRecord("Headhunt", "9");
		break;

		case "Givetaskhunt_3":
			dialog.text = StringFromKey("LeFransua_Tavern_99", pchar.name);
			link.l1 = StringFromKey("LeFransua_Tavern_100", pchar);
			link.l1.go = "Givetaskhunt_3_1";
		break;

		case "Givetaskhunt_3_1":
			if (CheckPatents(pchar))
			{
				dialog.text = StringFromKey("LeFransua_Tavern_101");
				link.l1 = StringFromKey("LeFransua_Tavern_102");
				link.l1.go = "exit";
				CloseQuestHeader("Headhunt");
				Headhunter_CleanupAll("end_quest");
				RemoveLandQuestMark_Main(npchar, "Headhunt");
				break;
			}
			dialog.text = StringFromKey("LeFransua_Tavern_103");
			link.l1 = StringFromKey("LeFransua_Tavern_104");
			link.l1.go = "Givetaskhunt_3_2";
		break;

		case "Givetaskhunt_3_2":
			dialog.text = StringFromKey("LeFransua_Tavern_105");
			link.l1 = StringFromKey("LeFransua_Tavern_106");
			link.l1.go = "Givetaskhunt_3_3";
		break;

		case "Givetaskhunt_3_3":
			dialog.text = StringFromKey("LeFransua_Tavern_107");
			link.l1 = StringFromKey("LeFransua_Tavern_108");
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "Rat";
			pchar.questTemp.Headhunter.count = 0;
			pchar.questTemp.Headhunter.countC = 0;
			pchar.questTemp.Headhunter.countV = 0;
			pchar.questTemp.Headhunter.countP = 0;
			AddQuestRecord("Headhunt", "11");
			AddItemLog(pchar, "suit_1", "1", StringFromKey("InfoMessages_171"), "Important_item");
			RemoveLandQuestMark_Main(npchar, "Headhunt");

			AddLandQuestMark_Main(CharacterFromID("Cartahena_PortMan"), "Headhunt");
			AddLandQuestMark_Main(CharacterFromID("PortSpein_PortMan"), "Headhunt");
			AddLandQuestMark_Main(CharacterFromID("Villemstad_PortMan"), "Headhunt");
		break;

		case "Endtaskhunt_3":
			dialog.text = StringFromKey("LeFransua_Tavern_109", pchar.name);
			link.l1 = StringFromKey("LeFransua_Tavern_110");
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "next_task_4";
			SaveCurrentQuestDateParam("pchar.questTemp.Headhunter_next_task_4");
			AddMoneyToCharacter(pchar, 20000);
			string sTotem2 = "Totem_" + (rand(9) + 1);
			AddItemLog(pchar, "chest," + sTotem2, "2,1", StringFromKey("InfoMessages_134") + " " + XI_ConvertString("NationLegendText_4") + " " + GetItemName(sTotem2), "Important_item");
			AddQuestRecord("Headhunt", "25");
			AddLandQuestMark_Main_WithCondition(npchar, "Headhunt", "Headhunt_Halen_Begin_QuestMarkCondition");
		break;

		case "Givetaskhunt_4":
			if (CheckPatents(pchar))
			{
				dialog.text = StringFromKey("LeFransua_Tavern_111");
				link.l1 = StringFromKey("LeFransua_Tavern_112");
				link.l1.go = "exit";
				CloseQuestHeader("Headhunt");
				Headhunter_CleanupAll("end_quest");
				RemoveLandQuestMark_Main(npchar, "Headhunt");
				break;
			}
			dialog.text = StringFromKey("LeFransua_Tavern_113");
			link.l1 = StringFromKey("LeFransua_Tavern_114");
			link.l1.go = "Givetaskhunt_4_1";
		break;

		case "Givetaskhunt_4_1":
			dialog.text = StringFromKey("LeFransua_Tavern_115");
			link.l1 = StringFromKey("LeFransua_Tavern_116", npchar.name);
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "hunt_halen";
			AddQuestRecord("Headhunt", "26");
			SetFunctionTimerCondition("Headhunter_HalenOver", 0, 0, 10, false);
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			AddLandQuestMark_Main(CharacterFromID("Villemstad_tavernkeeper"), "Headhunt");
		break;

		case "Endtaskhunt_4":
			dialog.text = StringFromKey("LeFransua_Tavern_117", pchar.name);
			link.l1 = StringFromKey("LeFransua_Tavern_118", npchar.name);
			link.l1.go = "Endtaskhunt_4_1";
			if (!CheckAttribute(pchar, "questTemp.Headhunter.paid4"))
			{
				pchar.questTemp.Headhunter.paid4 = true;
				AddMoneyToCharacter(pchar, 25000);
				string sTotem1 = "Totem_" + (rand(9) + 1);
				AddItemLog(pchar, "chest," + sTotem1, "2,1", StringFromKey("InfoMessages_134") + " " + XI_ConvertString("NationLegendText_4") + " " + GetItemName(sTotem1), "Important_item");
			}
		break;

		case "Endtaskhunt_4_1":
			dialog.text = StringFromKey("LeFransua_Tavern_119");
			link.l1 = StringFromKey("LeFransua_Tavern_120");
			link.l1.go = "Endtaskhunt_4_2";
		break;

		case "Endtaskhunt_4_2":
			dialog.text = StringFromKey("LeFransua_Tavern_121");
			link.l1 = StringFromKey("LeFransua_Tavern_122", npchar.name);
			link.l1.go = "Endtaskhunt_4_3";
		break;

		case "Endtaskhunt_4_3":
			dialog.text = StringFromKey("LeFransua_Tavern_123");
			link.l1 = StringFromKey("LeFransua_Tavern_124");
			link.l1.go = "Endtaskhunt_4_4";
		break;

		case "Endtaskhunt_4_4":
			dialog.text = StringFromKey("LeFransua_Tavern_125");
			link.l1 = StringFromKey("LeFransua_Tavern_126", npchar.name);
			link.l1.go = "Givetaskhunt_5";
		break;

		case "Givetaskhunt_5":
			dialog.text = StringFromKey("LeFransua_Tavern_127");
			link.l1 = StringFromKey("LeFransua_Tavern_128", npchar.name);
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "hunt_miko";
			AddQuestRecord("Headhunt", "33");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("ен", "на"));
			CreateMiko();
			RemoveLandQuestMark_Main(npchar, "Headhunt");
		break;

		case "Endtaskhunt_5":
			dialog.text = StringFromKey("LeFransua_Tavern_129", pchar.name);
			link.l1 = StringFromKey("LeFransua_Tavern_130", pchar, npchar.name);
			link.l1.go = "Endtaskhunt_5_1";
			if (!CheckAttribute(pchar, "questTemp.Headhunter.paid5"))
			{
				pchar.questTemp.Headhunter.paid5 = true;
				AddMoneyToCharacter(pchar, 100000);
				AddItemLog(pchar, "blade28,mushket,spyglass5,cirass3,indian11", "1", StringFromKey("InfoMessages_172"), "Important_item");
			}
		break;

		case "Endtaskhunt_5_1":
			dialog.text = StringFromKey("LeFransua_Tavern_131", pchar.name);
			link.l1 = StringFromKey("LeFransua_Tavern_132", npchar.name);
			link.l1.go = "exit";
			AddQuestRecord("Headhunt", "39");
			AddQuestUserData("Headhunt", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Headhunt");
			Headhunter_CleanupAll("end_quest_full");
			RemoveLandQuestMark_Main(npchar, "Headhunt");
			Achievment_Set(ACH_Nayomnik);
		break;
		//<--ОЗГ
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

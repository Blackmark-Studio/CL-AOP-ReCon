// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	string sTemp;
	int i, iTemp, iMoney, ShipType, Rank;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("spa_Governor_3", RandPhraseSimple(
						StringFromKey("spa_Governor_1"),
						StringFromKey("spa_Governor_2")));
			if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "Sharp_Prisoner"))
			{
				link.l1 = StringFromKey("spa_Governor_4", pchar);
				link.l1.go = "Sharp_Prisoner_SpaGovernor";
			}

			link.l99 = StringFromKey("spa_Governor_7", RandPhraseSimple(
						StringFromKey("spa_Governor_5", pchar),
						StringFromKey("spa_Governor_6")));
			link.l99.go = "exit";
		break;

		case "work_1":  // работа на благо короны - линейка нации
		// сюда вход только с патентом, проверка выше
			dialog.text = StringFromKey("spa_Governor_11", LinkRandPhrase(
						StringFromKey("spa_Governor_8"),
						StringFromKey("spa_Governor_9"),
						StringFromKey("spa_Governor_10")));
			link.l1 = StringFromKey("spa_Governor_14", RandPhraseSimple(
						StringFromKey("spa_Governor_12"),
						StringFromKey("spa_Governor_13")));
			link.l1.go = "exit";

			switch (pchar.questTemp.State)   // что делаем в данный момент
			{
				case "empty":   // Нет взятых квестов
					if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
					{
						dialog.text = StringFromKey("spa_Governor_18", LinkRandPhrase(
									StringFromKey("spa_Governor_15"),
									StringFromKey("spa_Governor_16"),
									StringFromKey("spa_Governor_17")));
						link.l1 = StringFromKey("spa_Governor_19");
						link.l1.go = "exit";
					}
					else
					{
						switch (pchar.questTemp.CurQuestNumber)   // Взятие квестов начиная со второго
						{
							case "2":
								dialog.text = StringFromKey("spa_Governor_20", pchar.name);
								link.l1 = StringFromKey("spa_Governor_21");
								link.l1.go = "Step_2_1";
							break;
							case "3":
								dialog.text = StringFromKey("spa_Governor_22", pchar);
								link.l1 = StringFromKey("spa_Governor_23", pchar);
								link.l1.go = "Step_3_1";
							break;
							case "4":
								dialog.text = StringFromKey("spa_Governor_24");
								link.l1 = StringFromKey("spa_Governor_25");
								link.l1.go = "Step_4_1";
							break;
							case "5":
								dialog.text = StringFromKey("spa_Governor_26");
								link.l1 = StringFromKey("spa_Governor_27", pchar);
								link.l1.go = "Step_5_1";
							break;
							case "6":
								dialog.text = StringFromKey("spa_Governor_28");
								link.l1 = StringFromKey("spa_Governor_29");
								link.l1.go = "Step_6_1";
							break;
							case "7":
								dialog.text = StringFromKey("spa_Governor_30");
								link.l1 = StringFromKey("spa_Governor_31", pchar);
								link.l1.go = "exit";
								pchar.questTemp.State = "Sp7SavePardal_toAntigua";
								AddQuestRecord("Spa_Line_7_SavePardal", "1");
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition.l1 = "location";
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition.l1.location = "Antigua";
								Pchar.quest.Sp7SavePardal_FightNearAntigua.win_condition = "Sp7SavePardal_FightNearAntigua";
								RemoveLandQuestmark_Main(npchar, "Spa_Line");
							break;
							case "8":
								dialog.text = StringFromKey("spa_Governor_32");
								link.l1 = StringFromKey("spa_Governor_33");
								link.l1.go = "Step_8_1";
							break;
							case "9":
								dialog.text = StringFromKey("spa_Governor_34");
								link.l1 = StringFromKey("spa_Governor_35");
								link.l1.go = "Step_9_1";
							break;
							case "10":
								dialog.text = StringFromKey("spa_Governor_36");
								link.l1 = StringFromKey("spa_Governor_37");
								link.l1.go = "Step_10_1";
							break;
							case "11":
								dialog.text = StringFromKey("spa_Governor_38");
								link.l1 = StringFromKey("spa_Governor_39", pchar);
								link.l1.go = "Step_11_1";
							break;
							case "12":
								dialog.text = StringFromKey("spa_Governor_40");
								link.l1 = StringFromKey("spa_Governor_41");
								link.l1.go = "Step_12_1";
							break;
						}
					}
				break;

				case "":           // Квест №1, Спасти горожан от Моргана.
					dialog.text = StringFromKey("spa_Governor_42");
					link.l1 = StringFromKey("spa_Governor_43", pchar);
					link.l1.go = "Step_1_1";
				break;
				case "SaveFromMorgan_OutOfPrison":
					dialog.text = StringFromKey("spa_Governor_44");
					link.l1 = StringFromKey("spa_Governor_45");
					link.l1.go = "Step_1_7";
				break;
				case "Inquisition_backBad":
					dialog.text = StringFromKey("spa_Governor_46");
					link.l1 = StringFromKey("spa_Governor_47");
					link.l1.go = "Step_2_3";
				break;
				case "Inquisition_backPartGood":
					dialog.text = StringFromKey("spa_Governor_48");
					link.l1 = StringFromKey("spa_Governor_49");
					link.l1.go = "Step_2_3";
				break;
				case "Inquisition_backAllGood":
					dialog.text = StringFromKey("spa_Governor_50");
					link.l1 = StringFromKey("spa_Governor_51");
					link.l1.go = "Step_2_3";
				break;
				case "TakeRockBras_RockSink":
					dialog.text = StringFromKey("spa_Governor_52");
					link.l1 = StringFromKey("spa_Governor_53", pchar);
					link.l1.go = "Step_3_6";
				break;
				case "TakeRockBras_DieHardRock":
					dialog.text = StringFromKey("spa_Governor_54");
					link.l1 = StringFromKey("spa_Governor_55", pchar);
					link.l1.go = "Step_3_6";
				break;
				case "TakeRockBras_RockTaken":
					dialog.text = StringFromKey("spa_Governor_56");
					link.l1 = StringFromKey("spa_Governor_57");
					link.l1.go = "Step_3_7";
				break;
				case "TakeRockBras_RockGiven":
					dialog.text = StringFromKey("spa_Governor_58");
					link.l1 = StringFromKey("spa_Governor_59", pchar);
					link.l1.go = "Step_3_8";
				break;
				case "TakeRockBras_WaitTwoDays":
					if (GetQuestPastDayParam("questTemp") > 2)
					{
						dialog.text = StringFromKey("spa_Governor_60");
						link.l1 = StringFromKey("spa_Governor_61");
						link.l1.go = "Step_3_9";
					}
					else
					{
						dialog.text = StringFromKey("spa_Governor_62");
						link.l1 = StringFromKey("spa_Governor_63");
						link.l1.go = "exit";
					}
				break;
				case "TakeRockBras_SeekRocksMoney":
					dialog.text = StringFromKey("spa_Governor_64");
					link.l1 = StringFromKey("spa_Governor_65");
					link.l1.go = "exit";
					if (sti(pchar.money) > 500000)
					{
						link.l2 = StringFromKey("spa_Governor_66", pchar);
						link.l2.go = "Step_3_10";
					}
				break;
				case "Sp4Detection_toMirderPlace":
					dialog.text = StringFromKey("spa_Governor_67");
					link.l1 = StringFromKey("spa_Governor_68");
					link.l1.go = "exit";
				break;
				case "Sp4Detection_toGovernor":
					dialog.text = StringFromKey("spa_Governor_69");
					link.l1 = StringFromKey("spa_Governor_70");
					link.l1.go = "Step_4_6";
				break;
				case "Sp4Detection_toDEstre":
					dialog.text = StringFromKey("spa_Governor_71");
					link.l1 = StringFromKey("spa_Governor_72", pchar);
					link.l1.go = "Step_4_9";
				break;
				case "Sp4Detection_toDEstre_1":
					dialog.text = StringFromKey("spa_Governor_73");
					link.l1 = StringFromKey("spa_Governor_74", pchar);
					link.l1.go = "Step_4_9";
				break;
				case "Sp4Detection_toDEstre_2":
					dialog.text = StringFromKey("spa_Governor_75");
					link.l1 = StringFromKey("spa_Governor_76");
					link.l1.go = "Step_4_10";
				break;
				case "Sp4Detection_DEstreIsDead":
					dialog.text = StringFromKey("spa_Governor_77");
					link.l1 = StringFromKey("spa_Governor_78", pchar);
					link.l1.go = "Step_4_14";
				break;
				case "Sp5LaVegaAttack_BackToHavana":
					dialog.text = StringFromKey("spa_Governor_79");
					link.l1 = StringFromKey("spa_Governor_80");
					link.l1.go = "Step_5_3";
				break;
				case "Sp6TakeMess_waitMessanger":
					dialog.text = StringFromKey("spa_Governor_81", pchar);
					link.l1 = StringFromKey("spa_Governor_82", pchar);
					link.l1.go = "Step_6_4";
				break;
				case "Sp6TakeMess_Action":
					dialog.text = StringFromKey("spa_Governor_83", pchar);
					link.l1 = StringFromKey("spa_Governor_84", pchar);
					link.l1.go = "Step_6_4";
				break;
				case "Sp7SavePardal_PardalIsSink":
					dialog.text = StringFromKey("spa_Governor_85");
					link.l1 = StringFromKey("spa_Governor_86", pchar);
					link.l1.go = "Step_7_1";
				break;
				case "Sp7SavePardal_GoodWork":
					dialog.text = StringFromKey("spa_Governor_87");
					link.l1 = StringFromKey("spa_Governor_88", pchar);
					link.l1.go = "Step_7_3";
				break;
				case "Sp7SavePardal_2GoodWork":
					dialog.text = StringFromKey("spa_Governor_89");
					link.l1 = StringFromKey("spa_Governor_90", pchar);
					link.l1.go = "Step_7_3";
				break;
				case "Sp7SavePardal_DieHard":
					dialog.text = StringFromKey("spa_Governor_91");
					link.l1 = StringFromKey("spa_Governor_92", pchar);
					link.l1.go = "Step_7_6";
				break;
				case "Sp8SaveCumana_YouLate":
					dialog.text = StringFromKey("spa_Governor_93");
					link.l1 = StringFromKey("spa_Governor_94", pchar);
					link.l1.go = "Step_8_5";
					pchar.questTemp.Waiting_time = "20";
				break;
				case "Sp8SaveCumana_DieHard":
					dialog.text = StringFromKey("spa_Governor_95");
					link.l1 = StringFromKey("spa_Governor_96", pchar);
					link.l1.go = "Step_8_5";
					pchar.questTemp.Waiting_time = "40";
				break;
				case "Sp8SaveCumana_GoodWork":
					dialog.text = StringFromKey("spa_Governor_97");
					link.l1 = StringFromKey("spa_Governor_98");
					link.l1.go = "Step_8_6";
				break;
				case "Sp9SaveCumana_BackHavana":
					dialog.text = StringFromKey("spa_Governor_99");
					link.l1 = StringFromKey("spa_Governor_100", pchar);
					link.l1.go = "Step_9_2";
				break;
				case "Sp10Maracaibo_DieHard":
					dialog.text = StringFromKey("spa_Governor_101");
					link.l1 = StringFromKey("spa_Governor_102");
					link.l1.go = "Step_10_6";
				break;
				case "Sp10Maracaibo_GoodWork":
					dialog.text = StringFromKey("spa_Governor_103");
					link.l1 = StringFromKey("spa_Governor_104");
					link.l1.go = "Step_10_11";
				break;
				case "Sp10Maracaibo_2GoodWork":
					dialog.text = StringFromKey("spa_Governor_105");
					link.l1 = StringFromKey("spa_Governor_106");
					link.l1.go = "Step_10_9";
				break;
				case "DestrHolland_GoOn":
					dialog.text = StringFromKey("spa_Governor_107");
					link.l1 = StringFromKey("spa_Governor_108");
					link.l1.go = "exit";
					if (CheckAttribute(pchar, "questTemp.Q11_Villemstad"))
					{
						dialog.text = StringFromKey("spa_Governor_109");
						link.l1 = StringFromKey("spa_Governor_110");
						link.l1.go = "exit";
					}
					if (CheckAttribute(pchar, "questTemp.Q11_Marigo"))
					{
						dialog.text = StringFromKey("spa_Governor_111");
						link.l1 = StringFromKey("spa_Governor_112");
						link.l1.go = "exit";
					}
					if (CheckAttribute(pchar, "questTemp.Q11_Villemstad") && CheckAttribute(pchar, "questTemp.Q11_Marigo"))
					{
						dialog.text = StringFromKey("spa_Governor_113", GetFullName(pchar));
						link.l1 = StringFromKey("spa_Governor_114");
						link.l1.go = "Step_11_3";
					}
				break;
				case "OccupyPortPax_WeWin":
					dialog.text = StringFromKey("spa_Governor_115");
					link.l1 = StringFromKey("spa_Governor_116");
					link.l1.go = "Step_12_4";
				break;
				case "QuestLineBreake":
					dialog.text = StringFromKey("spa_Governor_117");
					link.l1 = "...";
					link.l1.go = "exit";
					bWorldAlivePause = false; // Конец линейки
					RemoveLandQuestmark_Main(npchar, "Spa_Line");
					RemoveMapQuestmark("Havana_town", "Spa_Line");
				break;
				case "EndOfQuestLine":
					dialog.text = StringFromKey("spa_Governor_118", pchar, pchar.name);
					link.l1 = StringFromKey("spa_Governor_119");
					link.l1.go = "exit";
					bWorldAlivePause = false; // Конец линейки
					RemoveLandQuestmark_Main(npchar, "Spa_Line");
					RemoveMapQuestmark("Havana_town", "Spa_Line");
				break;
			}
		break;
		//********************** Квест №1, Спасти горожан от Моргана. ************************
		case "Step_1_1":
			dialog.text = StringFromKey("spa_Governor_120");
			link.l1 = StringFromKey("spa_Governor_121");
			link.l1.go = "Step_1_2";
		break;
		case "Step_1_2":
			dialog.text = StringFromKey("spa_Governor_122");
			link.l1 = StringFromKey("spa_Governor_123");
			link.l1.go = "Step_1_3";
		break;
		case "Step_1_3":
			dialog.text = StringFromKey("spa_Governor_124", pchar);
			link.l1 = StringFromKey("spa_Governor_125", pchar);
			link.l1.go = "Step_1_4";
		break;
		case "Step_1_4":
			dialog.text = StringFromKey("spa_Governor_126");
			link.l1 = StringFromKey("spa_Governor_127");
			link.l1.go = "Step_1_5";
		break;
		case "Step_1_5":
			dialog.text = StringFromKey("spa_Governor_128");
			link.l1 = StringFromKey("spa_Governor_129");
			link.l1.go = "Step_1_6";
		break;
		case "Step_1_6":
			SaveCurrentQuestDateParam("questTemp");
			// остальные линейки в сад -->
			pchar.questTemp.NationQuest = SPAIN;
			DeleteAttribute(&colonies[FindColony("PortoBello")], "notCaptured");
			DeleteAttribute(&colonies[FindColony("Panama")], "notCaptured");
			StateLines_Begin_DelQuestMarks();
			// остальные линейки в сад <--
			pchar.questTemp.State = "SaveFromMorgan_toPrison";
			AddQuestRecord("Spa_Line_1_SaveCitizens", "1");
			for (i = 1; i <= 3; i++)
			{
				switch (i)
				{
					case 1: sTemp = "merch_8"; break;
					case 2: sTemp = "merch_7"; break;
					case 3: sTemp = "merch_6"; break;
				}
				sld = GetCharacter(NPC_GenerateCharacter("SpaPrisoner" + i, sTemp, "man", "man", 10, SPAIN, -1, false));
				sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
				LAi_SetCitizenType(sld);
				LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
				ChangeCharacterAddressGroup(sld, "PortRoyal_Prison", "goto", "goto9");
				AddLandQuestmark_Main(sld, "Spa_Line");
			}
			AddLandQuestmarkToFantoms_Main("JailOff", "Spa_Line", "PortRoyal_JailOff_QuestMarkCondition");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Step_1_7":
			dialog.text = StringFromKey("spa_Governor_130");
			link.l1 = StringFromKey("spa_Governor_131");
			link.l1.go = "Step_1_8";
		break;
		case "Step_1_8":
			dialog.text = StringFromKey("spa_Governor_132");
			link.l1 = StringFromKey("spa_Governor_133");
			link.l1.go = "Step_1_9";
		break;
		case "Step_1_9":
			dialog.text = StringFromKey("spa_Governor_134");
			link.l1 = StringFromKey("spa_Governor_135");
			link.l1.go = "Step_1_10";
		break;
		case "Step_1_10":
			dialog.text = StringFromKey("spa_Governor_136");
			link.l1 = StringFromKey("spa_Governor_137");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "2";
			pchar.questTemp.Waiting_time = "7";
			CloseQuestHeader("Spa_Line_1_SaveCitizens");
			AddMoneyToCharacter(pchar, 50000);
			for (i = 1; i <= 3; i++)
			{
				sld = characterFromId("SpaPrisoner" + i);
				RemovePassenger(pchar, sld);
				sld.LifeDay = 0; // уберем нпс
			}
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			AddCharacterExpToSkill(pchar, "Grappling", 120);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_138", GetMainCharacterNameGen()), SPAIN, 5, 1);
		break;
		//********************** Квест №2, задания Инквизиции. ************************
		case "Step_2_1":
			dialog.text = StringFromKey("spa_Governor_139");
			link.l1 = StringFromKey("spa_Governor_140");
			link.l1.go = "Step_2_2";
		break;
		case "Step_2_2":
			dialog.text = StringFromKey("spa_Governor_141");
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.State = "Inquisition_toDeSouza";
			AddQuestRecord("Spa_Line_2_Inquisition", "1");
			SaveCurrentQuestDateParam("questTemp");
			AddLandQuestmark_Main(CharacterFromID("Santiago_Inquisitor"), "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Santiago_Priest"), "Spa_Line");
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_2_3":
			dialog.text = StringFromKey("spa_Governor_142");
			link.l1 = StringFromKey("spa_Governor_143");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "3";
			pchar.questTemp.Waiting_time = "15";
			CloseQuestHeader("Spa_Line_2_Inquisition");
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_144", GetFullName(pchar)), SPAIN, 5, 1);
		break;
		//********************** Квест №3, захватить Рока Бразица. ************************
		case "Step_3_1":
			dialog.text = StringFromKey("spa_Governor_145");
			link.l1 = StringFromKey("spa_Governor_146");
			link.l1.go = "Step_3_2";
		break;
		case "Step_3_2":
			dialog.text = StringFromKey("spa_Governor_147");
			link.l1 = StringFromKey("spa_Governor_148");
			link.l1.go = "Step_3_3";
		break;
		case "Step_3_3":
			dialog.text = StringFromKey("spa_Governor_149", GetAddress_Form(NPChar), pchar.name);
			link.l1 = StringFromKey("spa_Governor_150");
			link.l1.go = "Step_3_4";
		break;
		case "Step_3_4":
			dialog.text = StringFromKey("spa_Governor_151");
			link.l1 = StringFromKey("spa_Governor_152");
			link.l1.go = "Step_3_5";
		break;
		case "Step_3_5":
			dialog.text = StringFromKey("spa_Governor_153");
			link.l1 = StringFromKey("spa_Governor_154");
			link.l1.go = "exit";
			pchar.questTemp.State = "TakeRockBras_toTortuga";
			AddQuestRecord("Spa_Line_3_RockBrasilian", "1");
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_tavernkeeper"), "Spa_Line");
		break;
		case "Step_3_6":
			dialog.text = StringFromKey("spa_Governor_155");
			link.l1 = StringFromKey("spa_Governor_156", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "4";
			pchar.questTemp.Waiting_time = "30";
			CloseQuestHeader("Spa_Line_3_RockBrasilian");
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_157", pchar, GetFullName(pchar)), SPAIN, 5, 1);
		break;
		case "Step_3_7":
			dialog.text = StringFromKey("spa_Governor_158");
			link.l1 = StringFromKey("spa_Governor_159");
			link.l1.go = "exit";
		break;
		case "Step_3_8":
			dialog.text = StringFromKey("spa_Governor_160");
			link.l1 = StringFromKey("spa_Governor_161");
			link.l1.go = "exit";
			AddQuestRecord("Spa_Line_3_RockBrasilian", "9");
			pchar.questTemp.State = "TakeRockBras_WaitTwoDays";
			SaveCurrentQuestDateParam("questTemp");
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "SpaLine_3_WaitTwoDays_QuestMarkCondition");
		break;
		case "Step_3_9":
			dialog.text = StringFromKey("spa_Governor_162");
			link.l1 = StringFromKey("spa_Governor_163");
			link.l1.go = "Step_3_13";
		break;
		case "Step_3_13":
			dialog.text = StringFromKey("spa_Governor_164");
			link.l1 = StringFromKey("spa_Governor_165");
			link.l1.go = "Step_3_14";
		break;
		case "Step_3_14":
			dialog.text = StringFromKey("spa_Governor_166");
			link.l1 = StringFromKey("spa_Governor_167");
			link.l1.go = "Step_3_15";
		break;
		case "Step_3_15":
			dialog.text = StringFromKey("spa_Governor_168");
			link.l1 = StringFromKey("spa_Governor_169");
			link.l1.go = "exit";
			pchar.GenQuestBox.Cuba_Grot = true;
			pchar.GenQuestBox.Cuba_Grot.box1.items.gold = 150000;
			pchar.GenQuestBox.Cuba_Grot.box1.items.indian17 = 1;
			pchar.GenQuestBox.Cuba_Grot.box1.items.indian10 = 1;
			pchar.GenQuestBox.Cuba_Grot.box1.items.indian18 = 1;
			pchar.GenQuestBox.Hispaniola_Cave = true;
			pchar.GenQuestBox.Hispaniola_Cave.box2.items.gold = 150000;
			pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry5 = 250;
			pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry14 = 10;
			pchar.GenQuestBox.Hispaniola_Cave.box2.items.potion3 = 5;
			pchar.GenQuestBox.Hispaniola_Cave.box2.items.mineral8 = 1;
			pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry7 = 5;
			pchar.GenQuestBox.Hispaniola_Cave.box2.items.jewelry2 = 20;
			pchar.GenQuestBox.Beliz_Cave = true;
			pchar.GenQuestBox.Beliz_Cave.box1.items.gold = 50000;
			pchar.GenQuestBox.Beliz_Cave.box1.items.indian6 = 1;
			pchar.GenQuestBox.Beliz_Cave.box1.items.indian11 = 1;
			pchar.GenQuestBox.Beliz_Cave.box1.items.indian15 = 1;
			pchar.GenQuestBox.Beliz_Cave.box1.items.indian12 = 1;
			pchar.GenQuestBox.Beliz_Cave.box2.items.gold = 150000;
			pchar.GenQuestBox.Beliz_Cave.box2.items.potion5 = 10;
			pchar.GenQuestBox.Beliz_Cave.box2.items.potionrum = 2;
			pchar.GenQuestBox.Beliz_Cave.box2.items.potion4 = 10;
			pchar.questTemp.State = "TakeRockBras_SeekRocksMoney";
			AddQuestRecord("Spa_Line_3_RockBrasilian", "8");
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "SpaLine_3_SeekRocksMoney_QuestMarkCondition");
		break;
		case "Step_3_10":
			dialog.text = StringFromKey("spa_Governor_170");
			link.l1 = StringFromKey("spa_Governor_171");
			link.l1.go = "Step_3_11";
		break;
		case "Step_3_11":
			dialog.text = StringFromKey("spa_Governor_172");
			link.l1 = StringFromKey("spa_Governor_173");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -400000);
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "4";
			pchar.questTemp.Waiting_time = "5";
			CloseQuestHeader("Spa_Line_3_RockBrasilian");
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_174", pchar, GetFullName(pchar)), SPAIN, 5, 1);
		break;
		//********************** Квест №4, расследование убийства. ************************
		case "Step_4_1":
			dialog.text = StringFromKey("spa_Governor_175");
			link.l1 = StringFromKey("spa_Governor_176");
			link.l1.go = "Step_4_2";
		break;
		case "Step_4_2":
			dialog.text = StringFromKey("spa_Governor_177");
			link.l1 = StringFromKey("spa_Governor_178");
			link.l1.go = "Step_4_3";
		break;
		case "Step_4_3":
			dialog.text = StringFromKey("spa_Governor_179");
			link.l1 = StringFromKey("spa_Governor_180");
			link.l1.go = "Step_4_4";
		break;
		case "Step_4_4":
			dialog.text = StringFromKey("spa_Governor_181");
			link.l1 = StringFromKey("spa_Governor_182");
			link.l1.go = "Step_4_5";
		break;
		case "Step_4_5":
			dialog.text = StringFromKey("spa_Governor_183");
			link.l1 = StringFromKey("spa_Governor_184");
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp4Detection_toMirderPlace";
			AddQuestRecord("Spa_Line_4_MirderDetection", "1");
			AddQuestUserData("Spa_Line_4_MirderDetection", "sSex", GetSexPhrase("", "а"));
			pchar.GenQuestBox.Havana_houseS1Bedroom = true;
			pchar.GenQuestBox.Havana_houseS1Bedroom.box2.items.letter_notes = 1;
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_4_6":
			dialog.text = StringFromKey("spa_Governor_185");
			link.l1 = StringFromKey("spa_Governor_186", pchar);
			link.l1.go = "Step_4_7";
		break;
		case "Step_4_7":
			dialog.text = StringFromKey("spa_Governor_187");
			link.l1 = StringFromKey("spa_Governor_188");
			link.l1.go = "Step_4_8";
			TakeItemFromCharacter(pchar, "letter_notes");
		break;
		case "Step_4_8":
			dialog.text = StringFromKey("spa_Governor_189");
			link.l1 = StringFromKey("spa_Governor_190");
			link.l1.go = "exit";
			GiveNationLicence(FRANCE, 50);
			pchar.questTemp.State = "Sp4Detection_toTortuga";
			AddQuestRecord("Spa_Line_4_MirderDetection", "4");
			sld = GetCharacter(NPC_GenerateCharacter("ServantDEstre", "Barmen_13", "man", "man", 10, FRANCE, -1, false));
			sld.name = FindPersonalName("ServantDEstre_name");
			sld.lastname = "";
			sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Tortuga_houseS2", "goto", "goto2");
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_tavernkeeper"), "Spa_Line");
		break;
		case "Step_4_9":
			dialog.text = StringFromKey("spa_Governor_191");
			link.l1 = StringFromKey("spa_Governor_192");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "5";
			pchar.questTemp.Waiting_time = "30";
			CloseQuestHeader("Spa_Line_4_MirderDetection");
			TakeNationLicence(FRANCE);
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			RemoveLandQuestmark_Main(CharacterFromID("ServantDEstre"), "Spa_Line");
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_193", pchar, GetMainCharacterNameDat()), SPAIN, 5, 1);
		break;
		case "Step_4_10":
			dialog.text = StringFromKey("spa_Governor_194");
			link.l1 = StringFromKey("spa_Governor_195", pchar);
			link.l1.go = "Step_4_11";
		break;
		case "Step_4_11":
			dialog.text = StringFromKey("spa_Governor_196");
			link.l1 = StringFromKey("spa_Governor_197");
			link.l1.go = "Step_4_12";
		break;
		case "Step_4_12":
			dialog.text = StringFromKey("spa_Governor_198");
			link.l1 = StringFromKey("spa_Governor_199");
			link.l1.go = "Step_4_13";
		break;
		case "Step_4_13":
			dialog.text = StringFromKey("spa_Governor_200");
			link.l1 = StringFromKey("spa_Governor_201");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "5";
			pchar.questTemp.Waiting_time = "10";
			CloseQuestHeader("Spa_Line_4_MirderDetection");
			AddMoneyToCharacter(pchar, 3000);
			TakeNationLicence(FRANCE);
			AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Grappling", 100);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 120);
			ChangeCharacterReputation(pchar, 2);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_202", pchar, GetMainCharacterNameDat()), SPAIN, 5, 1);
		break;
		case "Step_4_14":
			dialog.text = StringFromKey("spa_Governor_203");
			link.l1 = StringFromKey("spa_Governor_204");
			link.l1.go = "Step_4_15";
		break;
		case "Step_4_15":
			dialog.text = StringFromKey("spa_Governor_205");
			link.l1 = StringFromKey("spa_Governor_206");
			link.l1.go = "Step_4_16";
		break;
		case "Step_4_16":
			dialog.text = StringFromKey("spa_Governor_207");
			link.l1 = StringFromKey("spa_Governor_208", pchar);
			link.l1.go = "Step_4_17";
		break;
		case "Step_4_17":
			dialog.text = StringFromKey("spa_Governor_209");
			link.l1 = StringFromKey("spa_Governor_210");
			link.l1.go = "Step_4_18";
		break;
		case "Step_4_18":
			dialog.text = StringFromKey("spa_Governor_211");
			link.l1 = StringFromKey("spa_Governor_212");
			link.l1.go = "Step_4_19";
		break;
		case "Step_4_19":
			dialog.text = StringFromKey("spa_Governor_213");
			link.l1 = StringFromKey("spa_Governor_214");
			link.l1.go = "Step_4_20";
		break;
		case "Step_4_20":
			dialog.text = StringFromKey("spa_Governor_215");
			link.l1 = StringFromKey("spa_Governor_216");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "5";
			pchar.questTemp.Waiting_time = "4";
			CloseQuestHeader("Spa_Line_4_MirderDetection");
			AddMoneyToCharacter(pchar, 120000);
			TakeNationLicence(FRANCE);
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_217", pchar, GetMainCharacterNameDat()), SPAIN, 5, 1);
		break;
		//********************** Квест №5, Нападение на Ла Вегу. ************************
		case "Step_5_1":
			dialog.text = StringFromKey("spa_Governor_218");
			link.l1 = StringFromKey("spa_Governor_219");
			link.l1.go = "Step_5_2";
		break;
		case "Step_5_2":
			dialog.text = StringFromKey("spa_Governor_220");
			link.l1 = StringFromKey("spa_Governor_221");
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp5LaVegaAttack_toSantiago";
			AddQuestRecord("Spa_Line_5_LaVegaAttack", "1");
			AddQuestUserData("Spa_Line_5_LaVegaAttack", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Santiago_Mayor"), "Spa_Line");
		break;
		case "Step_5_3":
			dialog.text = StringFromKey("spa_Governor_222");
			link.l1 = StringFromKey("spa_Governor_223");
			link.l1.go = "Step_5_4";
		break;
		case "Step_5_4":
			dialog.text = StringFromKey("spa_Governor_224");
			link.l1 = StringFromKey("spa_Governor_225");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "6";
			pchar.questTemp.Waiting_time = "7";
			CloseQuestHeader("Spa_Line_5_LaVegaAttack");
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");

			//убираем огонь и пламень 
			locations[FindLocation("LaVega_town")].models.always.town = "LaVega";
			locations[FindLocation("LaVega_town")].models.always.locatorsl2 = "LaVega_1";
			locations[FindLocation("LaVega_town")].models.always.locatorsl3 = "LaVega_locators";
			locations[FindLocation("LaVega_town")].models.day.charactersPatch = "LaVega_patch_day";
			locations[FindLocation("LaVega_town")].models.night.charactersPatch = "LaVega_patch_night";

			//Капитан Купер with Rosarak fixes -->
			sld = characterFromID("Edward Mansfield");
			sld.name = FindPersonalName("EdwardMansfield_name");
			sld.lastname = FindPersonalName("EdwardMansfield_lastname");
			sld.sex = "man";
			sld.model.animation = "man";
			sld.model = "officer_28";
			sld.City = "LaVega";
			sld.greeting = "spa_gov_common";
			sld.nation = SPAIN;
			sld.quest.type = "hovernor";
			sld.quest.meeting = "0";
			sld.id = "LaVega_Mayor";
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.Mayor = true;
			sld.from_sea = "LaVega_town";
			sld.Default.nation = SPAIN;
			sld.Default.BoardLocation = "LaVega_ExitTown";
			sld.watchBoxes = true;
			sld.standUp = true; //вставать и нападать на врага
			LAi_SetHuberType(sld);
			LAi_RemoveLoginTime(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.Dialog.CurrentNode = "First time";
			DeleteAttribute(sld, "Dialog.TempNode");
			sld.Sp5LaVegaAttackDone = "1";
			FaceMaker(sld);
			ChangeCharacterAddressGroup(sld, "LaVega_townhall", "sit", "sit1");
			AddTitleNextRate(sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "FencingLight", 350);
			AddCharacterExpToSkill(pchar, "Fencing", 350);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 320);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 11);
			SetLocationCapturedState("LaVega_town", false);
			//<-- Капитан Купер with Rosarak fixes

			//Rosarak New LaVega fixes -->
			sld = GetColonyRefByID("LaVega");
			sld.Default.BoardLocation = "LaVega_ExitTown";
			sld.from_sea = "LaVega_town";
			//Появляется контрик
			sld = GetCharacter(NPC_GenerateCharacter("LaVega_Smuggler", "citiz_21", "man", "man", 10, SPAIN, -1, false));
			sld.name = UpperFirst(XI_ConvertString("WhoSmuggler"));
			sld.lastname = "";
			sld.sex = "man";
			LAi_SetLoginTime(sld, 0.0, 24.0);
			GiveItem2Character(sld, BLADE_SABER);
			sld.equip.blade = BLADE_SABER;
			sld.Dialog.Filename = "Smuggler_Agent_dialog.c";
			LAi_SetSitType(sld);
			LAi_SetHP(sld, 80.0, 80.0);
			sld.greeting = "Gr_Smuggler Agent";
			//<-- Rosarak New LaVega fixes

			AddSimpleRumour(StringFromKey("spa_Governor_226"), SPAIN, 5, 1);
		break;
		//********************** Квест №6, Разведка на Тортуге. ************************
		case "Step_6_1":
			dialog.text = StringFromKey("spa_Governor_227");
			link.l1 = StringFromKey("spa_Governor_228", pchar);
			link.l1.go = "Step_6_2";
		break;
		case "Step_6_2":
			dialog.text = StringFromKey("spa_Governor_229");
			link.l1 = StringFromKey("spa_Governor_230");
			link.l1.go = "Step_6_3";
		break;
		case "Step_6_3":
			dialog.text = StringFromKey("spa_Governor_231");
			link.l1 = StringFromKey("spa_Governor_232");
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp6TakeMess_toTotuga";
			AddQuestRecord("Spa_Line_6_TakeMessangeer", "1");
			GiveNationLicence(FRANCE, 60);
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_tavernkeeper"), "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_PortMan"), "Spa_Line");
		break;
		case "Step_6_4":
			dialog.text = StringFromKey("spa_Governor_233");
			if (CheckCharacterItem(pchar, "letter_HolLineQ7_1"))
			{
				link.l1 = StringFromKey("spa_Governor_234");
				link.l1.go = "Step_6_6";
			}
			else
			{
				link.l1 = StringFromKey("spa_Governor_235", pchar);
				link.l1.go = "Step_6_5";
			}
		break;
		case "Step_6_5":
			dialog.text = StringFromKey("spa_Governor_236");
			link.l1 = StringFromKey("spa_Governor_237");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "7";
			pchar.questTemp.Waiting_time = "40";
			CloseQuestHeader("Spa_Line_6_TakeMessangeer");
			TakeNationLicence(FRANCE);
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
			DeleteAttribute(pchar, "questTemp.State.Open");
			LAi_group_SetLookRadius("FRANCE_CITIZENS", LAI_GROUP_DEF_LOOK);
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_238", pchar, GetMainCharacterNameGen()), SPAIN, 5, 1);
		break;
		case "Step_6_6":
			dialog.text = StringFromKey("spa_Governor_239", pchar.name);
			link.l1 = StringFromKey("spa_Governor_240");
			link.l1.go = "Step_6_7";
		break;
		case "Step_6_7":
			dialog.text = StringFromKey("spa_Governor_241");
			link.l1 = StringFromKey("spa_Governor_242");
			link.l1.go = "Step_6_8";
		break;
		case "Step_6_8":
			dialog.text = StringFromKey("spa_Governor_243");
			link.l1 = StringFromKey("spa_Governor_244");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 50000);
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "7";
			pchar.questTemp.Waiting_time = "9";
			CloseQuestHeader("Spa_Line_6_TakeMessangeer");
			TakeItemFromCharacter(pchar, "letter_HolLineQ7_1");
			TakeNationLicence(FRANCE);
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", true);
			DeleteAttribute(pchar, "questTemp.State.Open");
			LAi_group_SetLookRadius("FRANCE_CITIZENS", LAI_GROUP_DEF_LOOK);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_245", pchar, GetFullName(pchar)), SPAIN, 5, 1);
		break;
		//********************** Квест №7, Спасти Пардаля. ************************
		case "Step_7_1":
			dialog.text = StringFromKey("spa_Governor_246");
			link.l1 = StringFromKey("spa_Governor_247", pchar);
			link.l1.go = "Step_7_2";
		break;
		case "Step_7_2":
			dialog.text = StringFromKey("spa_Governor_248");
			link.l1 = StringFromKey("spa_Governor_249");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "8";
			pchar.questTemp.Waiting_time = "20";
			CloseQuestHeader("Spa_Line_7_SavePardal");
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
		break;
		case "Step_7_3":
			dialog.text = StringFromKey("spa_Governor_250", GetFullName(pchar));
			link.l1 = StringFromKey("spa_Governor_251");
			link.l1.go = "Step_7_4";
		break;
		case "Step_7_4":
			dialog.text = StringFromKey("spa_Governor_252");
			link.l1 = StringFromKey("spa_Governor_253");
			link.l1.go = "Step_7_5";
		break;
		case "Step_7_5":
			dialog.text = StringFromKey("spa_Governor_254");
			link.l1 = StringFromKey("spa_Governor_255");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 25000);
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "8";
			pchar.questTemp.Waiting_time = "5";
			CloseQuestHeader("Spa_Line_7_SavePardal");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sneak", 250);
			AddCharacterExpToSkill(pchar, "Sailing", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_256", pchar), SPAIN, 5, 1);
		break;
		case "Step_7_6":
			dialog.text = StringFromKey("spa_Governor_257");
			link.l1 = StringFromKey("spa_Governor_258");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "8";
			pchar.questTemp.Waiting_time = "40";
			CloseQuestHeader("Spa_Line_7_SavePardal");
			ChangeCharacterReputation(pchar, -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_259", pchar, GetAddress_Form(NPChar)), SPAIN, 5, 1);
		break;
		//********************** Квест №8, Отбить нападение на Куману. ************************
		case "Step_8_1":
			dialog.text = StringFromKey("spa_Governor_260");
			link.l1 = StringFromKey("spa_Governor_261");
			link.l1.go = "Step_8_2";
		break;
		case "Step_8_2":
			dialog.text = StringFromKey("spa_Governor_262", pchar);
			link.l1 = StringFromKey("spa_Governor_263");
			link.l1.go = "Step_8_3";
		break;
		case "Step_8_3":
			dialog.text = StringFromKey("spa_Governor_264");
			link.l1 = StringFromKey("spa_Governor_265", pchar);
			link.l1.go = "Step_8_4";
		break;
		case "Step_8_4":
			dialog.text = StringFromKey("spa_Governor_266");
			link.l1 = StringFromKey("spa_Governor_267");
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp8SaveCumana_toCumana";
			AddQuestRecord("Spa_Line_8_SaveCumana", "1");
			SetTimerCondition("Sp8SaveCumana_RescueTimeOver", 0, 0, 20, false);
			Pchar.quest.Sp8SaveCumana_Battle.win_condition.l1 = "location";
			Pchar.quest.Sp8SaveCumana_Battle.win_condition.l1.location = "Cumana";
			Pchar.quest.Sp8SaveCumana_Battle.win_condition = "Sp8SaveCumana_Battle";
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_8_5":
			dialog.text = StringFromKey("spa_Governor_268");
			link.l1 = StringFromKey("spa_Governor_269", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "9";
			CloseQuestHeader("Spa_Line_8_SaveCumana");
			SetLocationCapturedState("Cumana_town", false);
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -260);
			AddCharacterExpToSkill(pchar, "Cannons", -300);
			AddCharacterExpToSkill(pchar, "FencingLight", -270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -250);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_270", pchar, GetFullName(pchar)), SPAIN, 5, 1);
		break;
		case "Step_8_6":
			dialog.text = StringFromKey("spa_Governor_271");
			link.l1 = StringFromKey("spa_Governor_272");
			link.l1.go = "Step_8_7";
		break;
		case "Step_8_7":
			dialog.text = StringFromKey("spa_Governor_273", pchar);
			link.l1 = StringFromKey("spa_Governor_274", pchar);
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "7";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "9";
			CloseQuestHeader("Spa_Line_8_SaveCumana");
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddTitleNextRate(sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_275", GetAddress_Form(NPChar)), SPAIN, 5, 1);
		break;
		//********************** Квест №9, Четыре золотых галеона. ************************
		case "Step_9_1":
			dialog.text = StringFromKey("spa_Governor_276");
			link.l1 = StringFromKey("spa_Governor_277", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp9SaveCumana_toPortoBello";
			AddQuestRecord("Spa_Line_9_FourGolgGaleons", "1");
			AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("", "а"));
			GiveItem2Character(pchar, "letter_SpaLineQ10");
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("PortoBello_Mayor"), "Spa_Line");
		break;
		case "Step_9_2":
			dialog.text = StringFromKey("spa_Governor_278");
			link.l1 = StringFromKey("spa_Governor_279");
			link.l1.go = "Step_9_3";
		break;
		case "Step_9_3":
			dialog.text = StringFromKey("spa_Governor_280");
			link.l1 = StringFromKey("spa_Governor_281");
			link.l1.go = "Step_9_4";
		break;
		case "Step_9_4":
			dialog.text = StringFromKey("spa_Governor_282");
			link.l1 = StringFromKey("spa_Governor_283");
			link.l1.go = "Step_9_5";
		break;
		case "Step_9_5":
			dialog.text = StringFromKey("spa_Governor_284");
			iTemp = 0;
			iMoney = 0;
			for (i = 1; i <= COMPANION_MAX; i++)
			{
				ShipType = GetCompanionIndex(pchar, i);
				if (ShipType != -1)
				{
					sld = GetCharacter(ShipType);
					ShipType = sti(sld.ship.type);
					Rank = sti(RealShips[ShipType].basetype);
					if (Rank == SHIP_GALEON_L)
					{
						iTemp++;
						iMoney = iMoney + sti(sld.Ship.Cargo.Goods.Gold);
					}
				}
			}
			npchar.quest.money = iMoney;
			if (iTemp < 4 && iTemp > 0)
			{
				if (iTemp == 1)
				{
					link.l1 = StringFromKey("spa_Governor_285");
					link.l1.go = "Step_9_6";
				}
				else
				{
					link.l1 = StringFromKey("spa_Governor_286", iTemp);
					link.l1.go = "Step_9_6";
				}
			}
			else
			{
				if (iTemp == 0)
				{
					link.l1 = StringFromKey("spa_Governor_287", pchar);
					link.l1.go = "Step_9_8";
				}
				else
				{
					link.l1 = StringFromKey("spa_Governor_288");
					link.l1.go = "Step_9_11";
				}
			}
		break;
		case "Step_9_6":
			dialog.text = StringFromKey("spa_Governor_289", pchar);
			link.l1 = StringFromKey("spa_Governor_290", pchar);
			link.l1.go = "Step_9_7";
		break;
		case "Step_9_7":
			dialog.text = StringFromKey("spa_Governor_291");
			link.l1 = StringFromKey("spa_Governor_292");
			link.l1.go = "Step_9_71";
		break;
		case "Step_9_71":
			if (sti(npchar.quest.money) < (iTemp * 1200))
			{
				dialog.text = StringFromKey("spa_Governor_293");
				link.l1 = StringFromKey("spa_Governor_294");
				link.l1.go = "Step_9_exit";
				pchar.questTemp.Waiting_time = "20";
				pchar.questTemp.State = "empty";
				SaveCurrentQuestDateParam("questTemp");
				pchar.questTemp.CurQuestNumber = "10";
				AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
				AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			}
			else
			{
				dialog.text = StringFromKey("spa_Governor_295", pchar);
				link.l1 = StringFromKey("spa_Governor_296");
				link.l1.go = "Step_9_exit";
				pchar.questTemp.State = "QuestLineBreake";
				ChangeCharacterReputation(pchar, -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
				AddCharacterExpToSkill(pchar, "Sailing", -300);
				AddCharacterExpToSkill(pchar, "Leadership", -300);
				AddCharacterExpToSkill(pchar, "Commerce", -300);
				AddCharacterExpToSkill(pchar, "Pistol", -300);
				RemoveLandQuestmark_Main(npchar, "Spa_Line");
				//слухи
				AddSimpleRumour(
					StringFromKey("spa_Governor_297"), SPAIN, 5, 1);
			}
		break;
		case "Step_9_8":
			dialog.text = StringFromKey("spa_Governor_298", pchar);
			link.l1 = StringFromKey("spa_Governor_299", pchar);
			link.l1.go = "Step_9_10";
		break;
		case "Step_9_10":
			dialog.text = StringFromKey("spa_Governor_300", pchar);
			link.l1 = StringFromKey("spa_Governor_301");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "60";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "10";
			CloseQuestHeader("Spa_Line_9_FourGolgGaleons");
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
		break;
		case "Step_9_11":
			dialog.text = StringFromKey("spa_Governor_302");
			if (sti(npchar.quest.money) >= 5000)
			{
				link.l1 = StringFromKey("spa_Governor_303");
				link.l1.go = "Step_9_12";
			}
			else
			{
				if (sti(npchar.quest.money) > 4800)
				{
					link.l1 = StringFromKey("spa_Governor_304", FindQtyString(sti(npchar.quest.money)));
					link.l1.go = "Step_9_14";
				}
				else
				{
					link.l1 = StringFromKey("spa_Governor_305", FindQtyString(sti(npchar.quest.money)));
					link.l1.go = "Step_9_16";
				}
			}
		break;
		case "Step_9_12":
			dialog.text = StringFromKey("spa_Governor_306");
			link.l1 = StringFromKey("spa_Governor_307", pchar);
			link.l1.go = "Step_9_13";
		break;
		case "Step_9_13":
			dialog.text = StringFromKey("spa_Governor_308");
			link.l1 = StringFromKey("spa_Governor_309");
			link.l1.go = "Step_9_exit";
			pchar.questTemp.Waiting_time = "7";
			pchar.questTemp.State = "empty";
			AddMoneyToCharacter(pchar, 220000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_310"), SPAIN, 5, 1);
		break;
		case "Step_9_14":
			dialog.text = StringFromKey("spa_Governor_311");
			link.l1 = StringFromKey("spa_Governor_312", pchar);
			link.l1.go = "Step_9_15";
		break;
		case "Step_9_15":
			dialog.text = StringFromKey("spa_Governor_313");
			link.l1 = StringFromKey("spa_Governor_314");
			link.l1.go = "Step_9_exit";
			pchar.questTemp.Waiting_time = "12";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			AddMoneyToCharacter(pchar, 200000);
			AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 190);
			AddCharacterExpToSkill(pchar, "Leadership", 70);
			AddCharacterExpToSkill(pchar, "Commerce", 150);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_315"), SPAIN, 5, 1);
		break;
		case "Step_9_16":
			dialog.text = StringFromKey("spa_Governor_316", FindQtyString(5000 - sti(npchar.quest.money)));
			link.l1 = StringFromKey("spa_Governor_317", pchar);
			link.l1.go = "Step_9_17";
		break;
		case "Step_9_17":
			dialog.text = StringFromKey("spa_Governor_318");
			link.l1 = StringFromKey("spa_Governor_319");
			link.l1.go = "Step_9_exit";
			pchar.questTemp.State = "QuestLineBreake";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -300);
			AddCharacterExpToSkill(pchar, "Leadership", -300);
			AddCharacterExpToSkill(pchar, "Commerce", -300);
			AddCharacterExpToSkill(pchar, "Pistol", -300);
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_320"), SPAIN, 5, 1);
		break;
		case "Step_9_exit":
			pchar.questTemp.CurQuestNumber = "10";
			CloseQuestHeader("Spa_Line_9_FourGolgGaleons");
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromID("Captain_" + i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
			}
			DialogExit();
		break;
		//********************** Квест №10, Защита Маракайбо ************************
		case "Step_10_1":
			dialog.text = StringFromKey("spa_Governor_321");
			link.l1 = StringFromKey("spa_Governor_322", pchar);
			link.l1.go = "Step_10_2";
		break;
		case "Step_10_2":
			dialog.text = StringFromKey("spa_Governor_323");
			link.l1 = StringFromKey("spa_Governor_324");
			link.l1.go = "Step_10_3";
		break;
		case "Step_10_3":
			dialog.text = StringFromKey("spa_Governor_325");
			link.l1 = StringFromKey("spa_Governor_326");
			link.l1.go = "Step_10_4";
		break;
		case "Step_10_4":
			dialog.text = StringFromKey("spa_Governor_327");
			link.l1 = StringFromKey("spa_Governor_328", pchar);
			link.l1.go = "Step_10_5";
		break;
		case "Step_10_5":
			dialog.text = StringFromKey("spa_Governor_329");
			link.l1 = StringFromKey("spa_Governor_330");
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp10Maracaibo_toMaracaibo";
			AddQuestRecord("Spa_Line_10_Maracaibo", "1");
			AddQuestUserData("Spa_Line_10_Maracaibo", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Maracaibo_Mayor"), "Spa_Line");
		break;
		case "Step_10_6":
			dialog.text = StringFromKey("spa_Governor_331");
			link.l1 = StringFromKey("spa_Governor_332", pchar);
			link.l1.go = "Step_10_7";
		break;
		case "Step_10_7":
			dialog.text = StringFromKey("spa_Governor_333");
			link.l1 = StringFromKey("spa_Governor_334");
			link.l1.go = "Step_10_8";
		break;
		case "Step_10_8":
			dialog.text = StringFromKey("spa_Governor_335");
			link.l1 = "...";
			link.l1.go = "exit";
			CloseQuestHeader("Spa_Line_10_Maracaibo");
			DeleteAttribute(pchar, "questTemp.CurQuestNumber");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause = false; // Конец линейки
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Pistol", -430);
			AddCharacterExpToSkill(pchar, "Fortune", -460);
			AddCharacterExpToSkill(pchar, "Accuracy", -420);
			AddCharacterExpToSkill(pchar, "Grappling", -450);
			AddCharacterExpToSkill(pchar, "Sailing", -300);
			AddCharacterExpToSkill(pchar, "Leadership", -300);
			AddCharacterExpToSkill(pchar, "Commerce", -300);
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			RemoveMapQuestmark("Havana_town", "Spa_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_336"), SPAIN, 5, 1);
		break;
		case "Step_10_9":
			dialog.text = StringFromKey("spa_Governor_337");
			link.l1 = StringFromKey("spa_Governor_338", Characters[GetCharacterIndex("Maracaibo_Mayor")].name);
			link.l1.go = "Step_10_10";
		break;
		case "Step_10_10":
			dialog.text = StringFromKey("spa_Governor_339");
			link.l1 = StringFromKey("spa_Governor_340");
			link.l1.go = "Step_10_11";
		break;
		case "Step_10_11":
			dialog.text = StringFromKey("spa_Governor_341");
			link.l1 = StringFromKey("spa_Governor_342");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "15";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "11";
			CloseQuestHeader("Spa_Line_10_Maracaibo");
			ChangeCharacterReputation(pchar, 5);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			RemoveLandQuestmark_Main(CharacterFromID("Maracaibo_Mayor"), "Spa_Line");
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_343", GetAddress_Form(NPChar)), SPAIN, 5, 1);
		break;
		//********************** Квест №11, Нападение на Кюрасао и Сан Мартин ************************
		case "Step_11_1":
			dialog.text = StringFromKey("spa_Governor_344");
			link.l1 = StringFromKey("spa_Governor_345", pchar);
			link.l1.go = "Step_11_2";
		break;
		case "Step_11_2":
			dialog.text = StringFromKey("spa_Governor_346");
			link.l1 = StringFromKey("spa_Governor_347");
			link.l1.go = "exit";
			SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY); //ссорим ГГ и голландцев.
			SetNationRelationBoth(HOLLAND, SPAIN, RELATION_ENEMY);
			SetQuestHeader("Spa_Line_11_DestrHolland");
			AddQuestRecord("Spa_Line_11_DestrHolland", "1");
			AddQuestUserData("Spa_Line_11_DestrHolland", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.State = "DestrHolland_GoOn";
			characters[GetCharacterIndex("Villemstad_Mayor")].dialog.captureNode = "SpaLine11Quest_DestrHol"; //капитулянтская нода мэра
			characters[GetCharacterIndex("Marigo_Mayor")].dialog.captureNode = "SpaLine11Quest_DestrHol"; //капитулянтская нода мэра
			AddLandQuestmark_Main_WithCondition(CharacterFromID("Villemstad_Mayor"), "Spa_Line", "StateLines_CaptureCity_QuestMarkCondition");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("Marigo_Mayor"), "Spa_Line", "StateLines_CaptureCity_QuestMarkCondition");
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "SpaLine_11_Guber_QuestMarkCondition");
		break;
		case "Step_11_3":
			dialog.text = StringFromKey("spa_Governor_348");
			link.l1 = StringFromKey("spa_Governor_349");
			link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 2);
			DeleteAttribute(pchar, "questTemp.Q11_Villemstad");
			DeleteAttribute(pchar, "questTemp.Q11_Marigo");
			pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "30";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "12";
			CloseQuestHeader("Spa_Line_11_DestrHolland");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
			AddLandQuestmark_Main_WithCondition(npchar, "Spa_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Havana_town", "Spa_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_350"), SPAIN, 5, 5);
		break;
		//********************** Квест №12, Захват Порт-о-Принса ************************
		case "Step_12_1":
			dialog.text = StringFromKey("spa_Governor_351");
			link.l1 = StringFromKey("spa_Governor_352");
			link.l1.go = "Step_12_2";
		break;
		case "Step_12_2":
			dialog.text = StringFromKey("spa_Governor_353");
			link.l1 = StringFromKey("spa_Governor_354", pchar);
			link.l1.go = "Step_12_3";
		break;
		case "Step_12_3":
			dialog.text = StringFromKey("spa_Governor_355");
			link.l1 = StringFromKey("spa_Governor_356");
			link.l1.go = "exit";
			SetQuestHeader("Spa_Line_12_OccupyPortPax");
			AddQuestRecord("Spa_Line_12_OccupyPortPax", "1");
			AddQuestUserData("Spa_Line_12_OccupyPortPax", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.State = "OccupyPortPax_GoOn";
			characters[GetCharacterIndex("PortPax_Mayor")].dialog.captureNode = "SpaLine12Quest_PortPax"; //капитулянтская нода мэра
			AddLandQuestmark_Main_WithCondition(CharacterFromID("PortPax_Mayor"), "Spa_Line", "StateLines_CaptureCity_QuestMarkCondition");
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_12_4":
			dialog.text = StringFromKey("spa_Governor_357");
			link.l1 = StringFromKey("spa_Governor_358");
			link.l1.go = "Step_12_5";
		break;
		case "Step_12_5":
			dialog.text = StringFromKey("spa_Governor_359", GetFullName(pchar));
			link.l1 = StringFromKey("spa_Governor_360");
			link.l1.go = "Step_12_6";
		break;
		case "Step_12_6":
			dialog.text = StringFromKey("spa_Governor_361");
			link.l1 = StringFromKey("spa_Governor_362");
			link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 4);
			DeleteAttribute(pchar, "questTemp.CurQuestNumber");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			pchar.questTemp.State = "EndOfQuestLine";
			bWorldAlivePause = false; // Конец линейки
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			CloseQuestHeader("Spa_Line_12_OccupyPortPax");
			AddCharacterExpToSkill(pchar, "Repair", 630);
			AddCharacterExpToSkill(pchar, "Sneak", 490);
			AddCharacterExpToSkill(pchar, "FencingLight", 530);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 530);
			AddCharacterExpToSkill(pchar, "Fencing", 530);
			AddCharacterExpToSkill(pchar, "Pistol", 530);
			AddCharacterExpToSkill(pchar, "Fortune", 660);
			AddCharacterExpToSkill(pchar, "Accuracy", 520);
			AddCharacterExpToSkill(pchar, "Grappling", 750);
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			RemoveMapQuestmark("Havana_town", "Spa_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("spa_Governor_363"), SPAIN, 5, 1);
			Achievment_Set(ACH_Na_sluzhbe_Ispanii);
		break;

		// Квест Шарпа
		case "Sharp_Prisoner_SpaGovernor":
			sTemp = StringFromKey("spa_Governor_364");
			if (!isMainCharacterPatented())
			{
				sTemp = StringFromKey("spa_Governor_365");
			}

			dialog.text = StringFromKey("spa_Governor_366", sTemp);
			if (!isMainCharacterPatented())
			{
				link.l1 = StringFromKey("spa_Governor_367", pchar);
				link.l1.go = "Sharp_Prisoner_SpaGovernor_TakePatent";
				link.l2 = StringFromKey("spa_Governor_368", pchar);
				link.l2.go = "Sharp_Prisoner_SpaGovernor_DenyPatent";
			}
			else
			{
				link.l1 = StringFromKey("spa_Governor_369");
				link.l1.go = "Sharp_Prisoner_SpaGovernor_TakeMoney";
			}

		break;
		case "Sharp_Prisoner_SpaGovernor_TakePatent":
			dialog.text = StringFromKey("spa_Governor_370", GetFullName(pchar));
			link.l1 = StringFromKey("spa_Governor_371");
			link.l1.go = "Exit_Sharp_Prisoner_SpaGovernor_TakePatent";
		break;
		case "Exit_Sharp_Prisoner_SpaGovernor_TakePatent":
			AddDialogExitQuestFunction("SeaPearl_SharpPrisoner_BetraySharpToSpainGovernor");

			DialogExit();
		break;

		case "Sharp_Prisoner_SpaGovernor_DenyPatent":
			dialog.text = StringFromKey("spa_Governor_372", GetFullName(pchar));

			link.l1 = StringFromKey("spa_Governor_373");
			link.l1.go = "Sharp_Prisoner_SpaGovernor_TakeMoney";
		break;

		case "Sharp_Prisoner_SpaGovernor_TakeMoney":
			dialog.text = StringFromKey("spa_Governor_374");

			link.l1 = StringFromKey("spa_Governor_375");
			link.l1.go = "Exit_Sharp_Prisoner_SpaGovernor_DenyPatent";
		break;

		case "Exit_Sharp_Prisoner_SpaGovernor_DenyPatent":
			AddDialogExitQuestFunction("SeaPearl_SharpPrisoner_BetraySharpToSpainGovernor_DenyPatent");

			DialogExit();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

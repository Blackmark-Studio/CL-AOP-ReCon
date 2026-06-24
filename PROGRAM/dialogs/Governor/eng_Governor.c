// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	int i;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("eng_Governor_3", RandPhraseSimple(
						StringFromKey("eng_Governor_1"),
						StringFromKey("eng_Governor_2")));
			link.l1 = StringFromKey("eng_Governor_6", RandPhraseSimple(
						StringFromKey("eng_Governor_4", pchar),
						StringFromKey("eng_Governor_5")));
			link.l1.go = "exit";
		break;

		case "work_1":  // работа на благо короны - линейка нации
			if (CheckAttribute(npchar, "notQuestLine"))
			{
				dialog.text = StringFromKey("eng_Governor_7");
				link.l1 = StringFromKey("eng_Governor_8");
				link.l1.go = "exit";
				break;
			}
			// сюда вход только с патентом, проверка выше
			dialog.text = StringFromKey("eng_Governor_12", LinkRandPhrase(
						StringFromKey("eng_Governor_9"),
						StringFromKey("eng_Governor_10"),
						StringFromKey("eng_Governor_11")));
			link.l1 = StringFromKey("eng_Governor_15", RandPhraseSimple(
						StringFromKey("eng_Governor_13"),
						StringFromKey("eng_Governor_14")));
			link.l1.go = "exit";

			switch (pchar.questTemp.State)   // что делаем в данный момент
			{
				case "empty":   // Нет взятых квестов
					if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
					{
						dialog.text = StringFromKey("eng_Governor_19", LinkRandPhrase(
									StringFromKey("eng_Governor_16"),
									StringFromKey("eng_Governor_17"),
									StringFromKey("eng_Governor_18")));
						link.l1 = StringFromKey("eng_Governor_20");
						link.l1.go = "exit";
					}
					else
					{
						switch (pchar.questTemp.CurQuestNumber)   // Взятие квестов начиная со второго
						{
							case "2":
								dialog.text = StringFromKey("eng_Governor_21");
								link.l1 = StringFromKey("eng_Governor_22", pchar);
								link.l1.go = "Step_2_1";
							break;
							case "3":   // раньше тройки не было, теперь нужно для того, чтобы ГГ мог взять квест №4 без квеста №3.
								dialog.text = StringFromKey("eng_Governor_23");
								link.l1 = StringFromKey("eng_Governor_24");
								link.l1.go = "exit";
								pchar.questTemp.Waiting_time = "2";
								SaveCurrentQuestDateParam("questTemp");
								pchar.questTemp.CurQuestNumber = "4";
								SetCurrentQuestMark(npchar); // обновим метку
							break;
							case "4":
								dialog.text = StringFromKey("eng_Governor_25");
								link.l1 = StringFromKey("eng_Governor_26", pchar);
								link.l1.go = "Step_4_0";
							break;
							case "5":
								dialog.text = StringFromKey("eng_Governor_27");
								link.l1 = StringFromKey("eng_Governor_28");
								link.l1.go = "Step_5_1";
							break;
							case "6":
								dialog.text = StringFromKey("eng_Governor_29");
								link.l1 = StringFromKey("eng_Governor_30");
								link.l1.go = "Step_6_1";
							break;
							case "7":
								dialog.text = StringFromKey("eng_Governor_31");
								link.l1 = StringFromKey("eng_Governor_32");
								link.l1.go = "Step_7_1";
								// ==> Убираем Морриса Уильямса
								sld = characterFromID("Morris_Willams");
								sld.LifeDay = 1; // уберем нпс на след.день.
								SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
							break;
							case "8":
								dialog.text = StringFromKey("eng_Governor_33", GetFullName(pchar));
								link.l1 = StringFromKey("eng_Governor_34", pchar);
								link.l1.go = "Step_8_1";
							break;
							case "9":
								dialog.text = StringFromKey("eng_Governor_35");
								link.l1 = StringFromKey("eng_Governor_36", pchar);
								link.l1.go = "Step_9_1";
								link.l2 = StringFromKey("eng_Governor_37");
								link.l2.go = "exit";
							break;
							case "10":
								dialog.text = StringFromKey("eng_Governor_38");
								link.l1 = StringFromKey("eng_Governor_39");
								link.l1.go = "exit";
								pchar.questTemp.State = "SpanishAttack_ShipsInShore";
								SetQuestHeader("Eng_Line_10_SpanishAttack");
								AddQuestRecord("Eng_Line_10_SpanishAttack", "1");
								Pchar.quest.SpanishAttack_Battle.win_condition.l1 = "location";
								Pchar.quest.SpanishAttack_Battle.win_condition.l1.location = "Jamaica";
								Pchar.quest.SpanishAttack_Battle.win_condition = "SpanishAttack_Battle";
								ChangeCharacterAddress(characterFromID("Henry Morgan"), "None", "");
								RemoveLandQuestmark_Main(npchar, "Eng_Line");
							break;
							case "11":
								dialog.text = StringFromKey("eng_Governor_40");
								link.l1 = StringFromKey("eng_Governor_41");
								link.l1.go = "Step_11_1";
							break;
							case "12":
								dialog.text = StringFromKey("eng_Governor_42", GetFullName(pchar));
								link.l1 = StringFromKey("eng_Governor_43");
								link.l1.go = "Step_12_1";
							break;
							case "13":
								dialog.text = StringFromKey("eng_Governor_44");
								link.l1 = StringFromKey("eng_Governor_45");
								link.l1.go = "Step_12_5";
							break;
						}
					}
				break;

				case "":           // Квест №1 - сопровождение Альбермаля
					dialog.text = StringFromKey("eng_Governor_46");
					link.l1 = StringFromKey("eng_Governor_47", pchar);
					link.l1.go = "Step_1_1";
					link.l2 = StringFromKey("eng_Governor_48");
					link.l2.go = "exit";
				break;
				case "Albermal_good_time":                  // Геймер успел доставить Альбермаля за неделю.
					dialog.text = StringFromKey("eng_Governor_49");
					link.l1 = StringFromKey("eng_Governor_50");
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, 50000);
					ChangeCharacterReputation(pchar, 5);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
					AddCharacterExpToSkill(pchar, "Defence", 100);
					AddTitleNextRate(sti(NPChar.nation), 1);
					CloseQuestHeader("Eng_Line_1_Albermal");
					pchar.questTemp.State = "empty";
					SaveCurrentQuestDateParam("questTemp");
					TakeItemFromCharacter(pchar, "letter_Albermal");
					//слухи
					AddSimpleRumour(
						StringFromKey("eng_Governor_51", pchar, GetMainCharacterNameGen()), ENGLAND, 5, 1);
					AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
					AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
				break;
				case "Albermal_late":  // Геймер не успел за неделю доставить Альбермаля.
					dialog.text = StringFromKey("eng_Governor_52");
					link.l1 = StringFromKey("eng_Governor_53");
					link.l1.go = "Step_1_4";
				break;
				case "after_talks_with_pirates":  // После опроса пиратов
					dialog.text = StringFromKey("eng_Governor_54");
					link.l1 = StringFromKey("eng_Governor_55");
					link.l1.go = "Step_2_3";
				break;
				case "Intelligence_Curacao_Sink":  // Голландский флейт с инфой на борту был потоплен, провал миссии
					dialog.text = StringFromKey("eng_Governor_56");
					link.l1 = StringFromKey("eng_Governor_57", pchar);
					link.l1.go = "Step_4_1";
				break;
				case "Intelligence_Curacao_Boarding":  // Миссия выполнена, голландский флейт взят на абордаж
					dialog.text = StringFromKey("eng_Governor_58");
					link.l1 = StringFromKey("eng_Governor_59");
					link.l1.go = "Step_4_2";
				break;
				case "Intelligence_Curacao_BoardingNotFoundLetter":  // Миссия провалена, голландский флейт взят на абордаж, но письмо не найдено
					dialog.text = StringFromKey("eng_Governor_60");
					link.l1 = StringFromKey("eng_Governor_61", pchar);
					link.l1.go = "Step_4_1";
				break;
				case "Intelligence_Curacao_OutPrison":  // Миссия провалена, ГГ побывал в тюрьме
					dialog.text = StringFromKey("eng_Governor_62");
					link.l1 = StringFromKey("eng_Governor_63", pchar);
					link.l1.go = "Step_4_4";
				break;
				case "Intelligence_Curacao_FightGard": // Миссия провалена, ГГ дрался и ушёл из города ни с чем
					dialog.text = StringFromKey("eng_Governor_64");
					link.l1 = StringFromKey("eng_Governor_65", pchar);
					link.l1.go = "Step_4_5";
				break;
				case "AttackFortOrange_WeWin":   // Форт Оранж взят.
					dialog.text = StringFromKey("eng_Governor_66", pchar);
					link.l1 = StringFromKey("eng_Governor_67");
					link.l1.go = "Step_5_2";
				break;
				case "MorrisWillams_AfterFirstTalkingWithMorris": // Получено согласие Морриса Уильямса зайти в Порт-Ройал.
					dialog.text = StringFromKey("eng_Governor_68", GetFullName(pchar));
					link.l1 = StringFromKey("eng_Governor_69");
					link.l1.go = "Step_6_2";
				break;
				case "MorrisWillams_ToModifordForCoolTalking": // На разборки после разговора с Уильямсом в таверне
					dialog.text = StringFromKey("eng_Governor_70", GetFullName(pchar));
					link.l1 = StringFromKey("eng_Governor_71");
					link.l1.go = "Step_6_3";
				break;
				case "MorrisWillams_ArrestedToModiford": // На разборки после разговора с начальником тюрьмы
					dialog.text = StringFromKey("eng_Governor_72", GetFullName(pchar));
					link.l1 = StringFromKey("eng_Governor_73");
					link.l1.go = "Step_6_6";
				break;
				case "MorrisWillams_ModifordGood5000":
					dialog.text = StringFromKey("eng_Governor_74");
					link.l1 = StringFromKey("eng_Governor_75", pchar);
					link.l1.go = "exit";
				break;
				case "MorrisWillams_ModifordPolitic":
					dialog.text = StringFromKey("eng_Governor_76");
					link.l1 = StringFromKey("eng_Governor_77");
					link.l1.go = "exit";
				break;
				case "MorrisWillams_SeekSpanishGoods":
					dialog.text = StringFromKey("eng_Governor_78", GetFullName(pchar));
					link.l1 = StringFromKey("eng_Governor_79");
					link.l1.go = "exit";
				break;
				case "MorrisWillams_PinnaceBoard":
					dialog.text = StringFromKey("eng_Governor_80");
					link.l1 = StringFromKey("eng_Governor_81");
					link.l1.go = "exit";
				break;
				case "MorrisWillams_PinnaceBoardNotFoundMoney":
					dialog.text = StringFromKey("eng_Governor_82");
					link.l1 = StringFromKey("eng_Governor_83");
					link.l1.go = "exit";
				break;
				case "MorrisWillams_PinnaceSink":
					dialog.text = StringFromKey("eng_Governor_84");
					link.l1 = StringFromKey("eng_Governor_85");
					link.l1.go = "exit";
				break;
				case "MorrisWillams_DieHard":
					dialog.text = StringFromKey("eng_Governor_86");
					link.l1 = StringFromKey("eng_Governor_87", pchar);
					link.l1.go = "exit";
				break;
				case "SevenTreasures_GoOn":
					dialog.text = StringFromKey("eng_Governor_88");
					link.l1 = StringFromKey("eng_Governor_89");
					link.l1.go = "exit";
					if (CheckCharacterItem(pchar, "jewelry5"))
					{
						link.l1 = StringFromKey("eng_Governor_90");
						link.l1.go = "Step_7_4";
					}
					link.l2 = StringFromKey("eng_Governor_91");
					link.l2.go = "Step_7_10";
				break;
				case "ToMansfield_CatchToPardal":
					dialog.text = StringFromKey("eng_Governor_92");
					link.l1 = StringFromKey("eng_Governor_93");
					link.l1.go = "Step_8_3";
				break;
				case "ToMansfield_NotFoundGaleon":
					dialog.text = StringFromKey("eng_Governor_94");
					link.l1 = StringFromKey("eng_Governor_95", pchar);
					if (CheckAttribute(npchar, "TempQuest.KnowAboutModiford"))
					{
						dialog.text = StringFromKey("eng_Governor_96");
						link.l1 = StringFromKey("eng_Governor_97", pchar);
					}
					link.l1.go = "Step_8_5";
				break;
				case "ToMansfield_Boarding":
					dialog.text = StringFromKey("eng_Governor_98");
					link.l1 = StringFromKey("eng_Governor_99", pchar);
					if (CheckAttribute(npchar, "TempQuest.KnowAboutModiford"))
					{
						dialog.text = StringFromKey("eng_Governor_100");
						link.l1 = StringFromKey("eng_Governor_101", pchar);
					}
					link.l1.go = "Step_8_5";
					npchar.TempQuest.KindResult = 1; // признак результата завершения квеста, 1 == было захвачено письмо
					AddCharacterExpToSkill(pchar, "Cannons", 600);
					AddCharacterExpToSkill(pchar, "Sailing", 750);
					AddCharacterExpToSkill(pchar, "Defence", 550);
					AddCharacterExpToSkill(pchar, "Accuracy", 700);
					AddTitleNextRate(sti(NPChar.nation), 1);
				break;
				case "ToMansfield_BoardingNotFoundLetter":
					dialog.text = StringFromKey("eng_Governor_102");
					link.l1 = StringFromKey("eng_Governor_103");
					if (CheckAttribute(npchar, "TempQuest.KnowAboutModiford"))
					{
						dialog.text = StringFromKey("eng_Governor_104");
						link.l1 = StringFromKey("eng_Governor_105", pchar);
					}
					link.l1.go = "Step_8_5";
					AddCharacterExpToSkill(pchar, "Repair", 40);
					AddCharacterExpToSkill(pchar, "Commerce", 50);
					AddCharacterExpToSkill(pchar, "Defence", 20);
					AddCharacterExpToSkill(pchar, "Leadership", 10);
					AddTitleNextRate(sti(NPChar.nation), 0.5);
				break;
				case "ToMansfield_GaleonSink":
					dialog.text = StringFromKey("eng_Governor_106");
					link.l1 = StringFromKey("eng_Governor_107");
					if (CheckAttribute(npchar, "TempQuest.KnowAboutModiford"))
					{
						dialog.text = StringFromKey("eng_Governor_108");
						link.l1 = StringFromKey("eng_Governor_109", pchar);
					}
					link.l1.go = "Step_8_5";
					AddCharacterExpToSkill(pchar, "Repair", 5);
					AddCharacterExpToSkill(pchar, "Commerce", 10);
					AddCharacterExpToSkill(pchar, "Cannons", -50);
					AddCharacterExpToSkill(pchar, "Accuracy", -70);
					AddCharacterExpToSkill(pchar, "Fencing", -100);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
				break;
				case "ToMansfield_DidNotFindBecaners":
					dialog.text = StringFromKey("eng_Governor_110");
					link.l1 = StringFromKey("eng_Governor_111", pchar);
					link.l1.go = "Step_8_5";
					npchar.TempQuest.KindResult = 2; // признак результата завершения квеста, 2 == вообще не в курсе, что произошло
					AddCharacterExpToSkill(pchar, "Cannons", 10);
					AddCharacterExpToSkill(pchar, "Pistol", -200);
					AddCharacterExpToSkill(pchar, "Defence", -100);
					AddCharacterExpToSkill(pchar, "Accuracy", -210);
					AddCharacterExpToSkill(pchar, "Fencing", -400);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
				break;
				case "AttackSantiago_GoodWork":
					dialog.text = StringFromKey("eng_Governor_112", GetFullName(pchar));
					link.l1 = StringFromKey("eng_Governor_113");
					link.l1.go = "Step_9_4";
				break;
				case "SpanishAttack_GoodWork":
					dialog.text = StringFromKey("eng_Governor_114");
					link.l1 = StringFromKey("eng_Governor_115", pchar);
					link.l1.go = "Step_10_1";
				break;
				case "OccupyMein_GoOn":
					dialog.text = StringFromKey("eng_Governor_116");
					link.l1 = StringFromKey("eng_Governor_117");
					link.l1.go = "exit";
					if (CheckAttribute(pchar, "questTemp.Q11_Caracas"))
					{
						dialog.text = StringFromKey("eng_Governor_118", GetFullName(pchar));
						link.l1 = StringFromKey("eng_Governor_119");
						link.l1.go = "exit";
					}
					if (CheckAttribute(pchar, "questTemp.Q11_Cumana"))
					{
						dialog.text = StringFromKey("eng_Governor_120", GetFullName(pchar));
						link.l1 = StringFromKey("eng_Governor_121");
						link.l1.go = "exit";
					}
					if (CheckAttribute(pchar, "questTemp.Q11_Caracas") && CheckAttribute(pchar, "questTemp.Q11_Cumana"))
					{
						dialog.text = StringFromKey("eng_Governor_122");
						link.l1 = StringFromKey("eng_Governor_123");
						link.l1.go = "Step_11_2";
					}
				break;
				case "ColonelLinch_ArrestModiford":
					dialog.text = StringFromKey("eng_Governor_124");
					link.l1 = StringFromKey("eng_Governor_125", pchar);
					link.l1.go = "Step_12_2";
				break;
				case "ColonelLinch_ModifordArrested":
					dialog.text = StringFromKey("eng_Governor_126");
					link.l1 = StringFromKey("eng_Governor_127");
					link.l1.go = "exit";
					pchar.questTemp.State = "empty";
					SaveCurrentQuestDateParam("questTemp");
					pchar.questTemp.CurQuestNumber = "13";
					pchar.questTemp.Waiting_time = "30";
					CloseQuestHeader("Eng_Line_12_ColonelLinch");
					AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
					AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
				break;
				case "QuestLineBreake":
					dialog.text = StringFromKey("eng_Governor_128");
					link.l1 = "...";
					link.l1.go = "exit";
					bWorldAlivePause = false; // Конец линейки
					RemoveLandQuestmark_Main(npchar, "Eng_Line");
					RemoveMapQuestmark("PortRoyal_town", "Eng_Line");
				break;
				case "EndOfQuestLine":
					dialog.text = StringFromKey("eng_Governor_129", UpperFirst(GetAddress_Form(NPChar)));
					link.l1 = StringFromKey("eng_Governor_130", pchar);
					link.l1.go = "exit";
					bWorldAlivePause = false; // Конец линейки
					RemoveLandQuestmark_Main(npchar, "Eng_Line");
					RemoveMapQuestmark("PortRoyal_town", "Eng_Line");
				break;
			}
		break;

		case "Step_1_1":
			LockQuestLine(characterFromId("Jackman")); // лочим пиратскую линейку
			RemoveLandQuestmark_Main(characterFromId("Jackman"), "Pir_Line");
			RemoveMapQuestMark("Pirates_town", "Pir_Line");
			dialog.text = StringFromKey("eng_Governor_131");
			link.l1 = StringFromKey("eng_Governor_132");
			link.l1.go = "Step_1_2";
		break;

		case "Step_1_2":
			dialog.text = StringFromKey("eng_Governor_133");
			link.l1 = StringFromKey("eng_Governor_134");
			link.l1.go = "Step_1_3";
		break;

		case "Step_1_3":
			dialog.text = StringFromKey("eng_Governor_135");
			link.l1 = StringFromKey("eng_Governor_136", pchar);
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp");
			// остальные линейки в сад -->
			pchar.questTemp.NationQuest = ENGLAND;
			DeleteAttribute(&colonies[FindColony("PortoBello")], "notCaptured");
			DeleteAttribute(&colonies[FindColony("Panama")], "notCaptured");
			StateLines_Begin_DelQuestMarks();
			// остальные линейки в сад <--
			pchar.questTemp.State = "to_Albermal";               // переменная состояния квеста для линеек
			sld = GetCharacter(NPC_GenerateCharacter("Albermal", "Albermal", "man", "man", 10, ENGLAND, -1, false));
			sld.name = FindPersonalName("Albermal_name");
			sld.lastname = FindPersonalName("Albermal_lastname");
			sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
			sld.greeting = "Gr_QuestMan";
			LAi_SetHuberStayType(sld);
			LAi_group_MoveCharacter(sld, "ENGLAND_CITIZENS");
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Albermal")], "PortRoyal_RoomTownhall", "goto", "goto3");
			AddQuestRecord("Eng_Line_1_Albermal", "1");
			AddLandQuestmark_Main(sld, "Eng_Line");
		break;

		case "Step_1_4":
			dialog.text = StringFromKey("eng_Governor_137");
			link.l1 = StringFromKey("eng_Governor_138", pchar);
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			pchar.questTemp.Waiting_time = 10;
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			CloseQuestHeader("Eng_Line_1_Albermal");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			TakeItemFromCharacter(pchar, "letter_Albermal");
			AddCharacterExpToSkill(pchar, "Leadership", -70);
			//слухи			
			AddSimpleRumour(
				StringFromKey("eng_Governor_139", pchar, GetFullName(pchar)), ENGLAND, 5, 1);
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
		break;

		case "Step_2_1":
			dialog.text = StringFromKey("eng_Governor_140");
			link.l1 = StringFromKey("eng_Governor_141");
			link.l1.go = "Step_2_2";
		break;

		case "Step_2_2":
			dialog.text = StringFromKey("eng_Governor_142");
			link.l1 = StringFromKey("eng_Governor_143");
			link.l1.go = "Step_2_21";
		break;

		case "Step_2_21":
			dialog.text = StringFromKey("eng_Governor_144");
			link.l1 = StringFromKey("eng_Governor_145", pchar);
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "go_talks_with_pirates";          // переменная состояния квеста для линеек
			AddQuestRecord("Eng_Line_2_Talking", "1");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			// ==>  Помещаем Моргана на Антигуа и даем ноду доступа к квестам
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
			//HardCoffee реф диалогов Моргана
			//QuestSetCurrentNode("Henry Morgan", "EngLine_quests");
			pchar.QuestTemp.EngLine_Morgan_task = "EngLine_begin";
			sld = characterFromID("Henry Morgan");
			LAi_SetHuberStayType(sld);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			AddLandQuestmark_Main(sld, "Eng_Line");
			// ==>  Генерим и помещаем Джона Морриса в Порт оф Спейн и даем ноду доступа к квестам
			sld = GetCharacter(NPC_GenerateCharacter("John Morris", "John_Morris", "man", "man", 38, PIRATE, -1, false));
			sld.name = FindPersonalName("JohnMorris_name");
			sld.lastname = FindPersonalName("JohnMorris_lastname");
			sld.Dialog.Filename = "Quest\JohnMorris.c";
			FantomMakeCoolSailor(sld, SHIP_GALEON_H, FindPersonalName("JohnMorris_ship"), CANNON_TYPE_CANNON_LBS32, 90, 90, 90);
			FantomMakeCoolFighter(sld, 35, 90, 50, BLADE_LONG, "pistol3", 150);
			sld.greeting = "Gr_HeadPirates";
			LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			sld.RebirthPhantom = true; //не тереть фантома после смерти.  
			LAi_SetHuberType(sld);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetHP(sld, 180.0, 180.0);
			ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "sit", "sit1");
			LAi_LocationFightDisable(&Locations[FindLocation("PortSpein_houseF2")], true);
			TEV.JohnMorrisIsLifeInHouse = true;
			AddLandQuestmark_Main(sld, "Eng_Line");
			// ==>  Даем ноду доступа к квестам Джону Моррису
			QuestSetCurrentNode("John Morris", "EngLine_quests");
			//HardCoffee ref Jackman's dialogue
			pchar.QuestTemp.EngLine_Jackman_task = "EngLine_begin";
			// QuestSetCurrentNode("Jackman", "EngLine_quests");
			AddLandQuestmark_Main(CharacterFromID("Jackman"), "Eng_Line");
			//ref Mansfields's dialogue
			pchar.QuestTemp.EngLine_Mansfield_task = "EngLine_begin";
			//QuestSetCurrentNode("Edward Mansfield", "EngLine_quests");
			AddLandQuestmark_Main(CharacterFromID("Edward Mansfield"), "Eng_Line");
			// ==>  Оформляем счетчик посещения корсаров, в итоге должен == 4
			pchar.questTemp.Count = "0";
		break;

		case "Step_2_3":
			dialog.text = StringFromKey("eng_Governor_146");
			link.l1 = StringFromKey("eng_Governor_147");
			link.l1.go = "Step_2_4";
		break;

		case "Step_2_4":
			if (GetQuestPastDayParam("questTemp") < 35)
			{
				dialog.text = StringFromKey("eng_Governor_148");
				link.l1 = StringFromKey("eng_Governor_149", pchar);
				AddMoneyToCharacter(pchar, 15000);
				ChangeCharacterReputation(pchar, 3);
				AddCharacterExpToSkill(pchar, "Repair", 150);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddTitleNextRate(sti(NPChar.nation), 2);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			}
			else
			{
				dialog.text = StringFromKey("eng_Governor_150", GetQuestPastDayParam("questTemp"));
				link.l1 = StringFromKey("eng_Governor_151");
				AddMoneyToCharacter(pchar, 800);
				ChangeCharacterReputation(pchar, 1);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			}
			link.l1.go = "exit";
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_152", pchar, GetFullName(pchar)), ENGLAND, 5, 1);
			DeleteAttribute(pchar, "questTemp.Count");
			pchar.questTemp.State = "empty";
			AddQuestRecord("Eng_Line_2_Talking", "6");
			AddQuestUserData("Eng_Line_2_Talking", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Eng_Line_2_Talking");
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "3";
			pchar.questTemp.Waiting_time = "70";    // Чтобы Мэдифорд дал квест №4 через 70 дней, даже если ГГ не зашёл к Моргану
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			// ==> Моргана - в резиденцию на Ямайке
			sld = characterFromID("Henry Morgan");
			LAi_SetHuberType(sld);
			//HardCoffee реф диалогов Моргана
			//QuestSetCurrentNode("Henry Morgan", "hot_business");
			pchar.QuestTemp.EngLine_Morgan_task = "hot_business";
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
			AddLandQuestmark_Main(sld, "Eng_Line");
		break;

		case "Step_4_0":
			dialog.text = StringFromKey("eng_Governor_153");
			link.l1 = StringFromKey("eng_Governor_154");
			link.l1.go = "exit";
			GiveNationLicence(HOLLAND, 20);
			pchar.questTemp.State = "Intelligence_Curacao_tavern";
			SetQuestHeader("Eng_Line_4_Intelligence_Curacao");
			AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "1");
			AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex1", GetSexPhrase("к", "ца"));
			SaveCurrentQuestDateParam("questTemp");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main(CharacterFromID("Villemstad_tavernkeeper"), "Eng_Line");
		break;

		case "Step_4_1":
			dialog.text = StringFromKey("eng_Governor_155");
			link.l1 = StringFromKey("eng_Governor_156", pchar);
			link.l1.go = "exit";
			TakeNationLicence(HOLLAND);
			CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
			pchar.questTemp.State = "empty";
			pchar.questTemp.CurQuestNumber = "5";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.Waiting_time = "30";    //только через месяц следующий квест, т.к. Мэдифорд будет добывать инфу без участия ГГ
			AddCharacterExpToSkill(pchar, "Sailing", -140);
			AddCharacterExpToSkill(pchar, "Sneak", -180);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_157"), ENGLAND, 5, 1);
		break;

		case "Step_4_2":
			dialog.text = StringFromKey("eng_Governor_158");
			link.l1 = StringFromKey("eng_Governor_159");
			link.l1.go = "Step_4_3";
		break;

		case "Step_4_3":
			dialog.text = StringFromKey("eng_Governor_160");
			link.l1 = StringFromKey("eng_Governor_161");
			link.l1.go = "exit";
			AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "10");
			AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
			pchar.questTemp.State = "empty";
			pchar.questTemp.CurQuestNumber = "5";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.Waiting_time = "2";
			AddMoneyToCharacter(pchar, 110000);
			AddCharacterExpToSkill(pchar, "Sailing", 250);
			AddCharacterExpToSkill(pchar, "Sneak", 170);
			AddCharacterExpToSkill(pchar, "Grappling", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			TakeItemFromCharacter(pchar, "letter_open_EngLineQ4");
			TakeNationLicence(HOLLAND);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_162"), ENGLAND, 5, 1);
		break;

		case "Step_4_4":
			dialog.text = StringFromKey("eng_Governor_163");
			link.l1 = StringFromKey("eng_Governor_164", pchar);
			link.l1.go = "exit";
			CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
			pchar.questTemp.State = "empty";
			pchar.questTemp.CurQuestNumber = "5";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.Waiting_time = "30";    // только через месяц следующий квест, т.к. Мэдифорд будет добывать инфу без участия ГГ
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "Leadership", -150);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_165"), ENGLAND, 5, 1);
		break;

		case "Step_4_5":
			dialog.text = StringFromKey("eng_Governor_166");
			link.l1 = StringFromKey("eng_Governor_167", pchar);
			link.l1.go = "exit";
			CloseQuestHeader("Eng_Line_4_Intelligence_Curacao");
			pchar.questTemp.State = "empty";
			pchar.questTemp.CurQuestNumber = "5";
			SaveCurrentQuestDateParam("questTemp");
			TakeNationLicence(HOLLAND);
			pchar.questTemp.Waiting_time = "30";    // только через месяц следующий квест, т.к. Мэдифорд будет добывать инфу без участия ГГ
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "Fencing", -300);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_168"), ENGLAND, 5, 1);
		break;

		case "Step_5_1":
			dialog.text = StringFromKey("eng_Governor_169");
			link.l1 = StringFromKey("eng_Governor_170");
			link.l1.go = "exit";
			pchar.GenQuestBox.Trinidad_Cave = true;
			pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry3 = Rand(5) + 1;
			pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry4 = Rand(5) + 1;
			pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry5 = Rand(5) + 1;
			pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry7 = Rand(5) + 1;
			pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry8 = Rand(5) + 1;
			pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry10 = Rand(5) + 1;
			pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry14 = Rand(5) + 1;
			pchar.GenQuestBox.FortOrange_townhall.box1.items.jewelry17 = Rand(5) + 1;
			pchar.GenQuestBox.FortOrange_townhall.box1.items.cirass4 = 1;
			locations[FindLocation("FortOrange_townhall")].models.day.charactersPatch = "SmallResidence_BoxPatch";
			pchar.questTemp.State = "AttackFortOrange_GoToFort";
			SetQuestHeader("Eng_Line_5_AttackFortOrange");
			AddQuestRecord("Eng_Line_5_AttackFortOrange", "1");
			LAi_LocationFightDisable(&Locations[FindLocation("FortOrange_townhall")], false);
			Pchar.quest.AttackFortOrange_GoToFort.win_condition.l1 = "location";
			Pchar.quest.AttackFortOrange_GoToFort.win_condition.l1.location = "FortOrange_ExitTown";
			Pchar.quest.AttackFortOrange_GoToFort.win_condition = "AttackFortOrange_GoToFort";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;

		case "Step_5_2":
			dialog.text = StringFromKey("eng_Governor_171", GetFullName(pchar));
			link.l1 = StringFromKey("eng_Governor_172");
			link.l1.go = "Step_5_3";
		break;

		case "Step_5_3":
			dialog.text = StringFromKey("eng_Governor_173", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("eng_Governor_174");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			CloseQuestHeader("Eng_Line_5_AttackFortOrange");
			pchar.questTemp.CurQuestNumber = "6";
			pchar.questTemp.Waiting_time = "30"; // По идее геймер должен испытывать угрызения совести после этого задания. Пусть поболтается просто так с месяц.
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			// ==> вертаем разграбленному форту Оранж нормальную жизнь.
			SetLocationCapturedState("FortOrange_town", false);
			LAi_LocationFightDisable(&Locations[FindLocation("FortOrange_townhall")], true);
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");
			//<-- огонь и пламень
			locations[FindLocation("FortOrange_townhall")].models.day.charactersPatch = "SmallResidence_patch";
			AddCharacterExpToSkill(pchar, "Pistol", 250);
			AddCharacterExpToSkill(pchar, "Leadership", 250);
			AddCharacterExpToSkill(pchar, "Repair", 350);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_175"), ENGLAND, 5, 1);
		break;

		case "Step_6_1":
			dialog.text = StringFromKey("eng_Governor_176");
			link.l1 = StringFromKey("eng_Governor_177");
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_GoToMorrisBegin";
			SetQuestHeader("Eng_Line_6_MorrisWillams");
			AddQuestRecord("Eng_Line_6_MorrisWillams", "1");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");

			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1 = "location";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1.location = "Jamaica";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition = "MorrisWillams_ShipToPort";
		break;

		case "Step_6_2":
			dialog.text = StringFromKey("eng_Governor_178");
			link.l1 = StringFromKey("eng_Governor_179");
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_ModifordGood5000";
			AddMoneyToCharacter(pchar, 5000);
			AddTitleNextRate(sti(NPChar.nation), 0.5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddQuestRecord("Eng_Line_6_MorrisWillams", "3");
			group_DeleteGroup("Willams_Group");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");

			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1 = "location";
			Pchar.quest.MorrisWillams_ShipToPort.win_condition.l1.location = Pchar.location.from_sea;
			Pchar.quest.MorrisWillams_ShipToPort.win_condition = "MorrisWillams_MeetWithManFromWillams";
		break;

		case "Step_6_3":
			dialog.text = StringFromKey("eng_Governor_180");
			link.l1 = StringFromKey("eng_Governor_181", pchar);
			link.l1.go = "Step_6_4";
		break;

		case "Step_6_4":
			dialog.text = StringFromKey("eng_Governor_182");
			link.l1 = StringFromKey("eng_Governor_183");
			link.l1.go = "Step_6_5";
		break;

		case "Step_6_5":
			dialog.text = StringFromKey("eng_Governor_184");
			link.l1 = StringFromKey("eng_Governor_185");
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_ModifordPolitic";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "5");
			QuestSetCurrentNode("Morris_Willams", "First time");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main(characterFromID("Morris_Willams"), "Eng_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_186"), ENGLAND, 5, 1);
		break;

		case "Step_6_6":
			dialog.text = StringFromKey("eng_Governor_187", GetFullName(pchar));
			link.l1 = StringFromKey("eng_Governor_188");
			link.l1.go = "Step_6_7";
		break;

		case "Step_6_7":
			dialog.text = StringFromKey("eng_Governor_189");
			link.l1 = StringFromKey("eng_Governor_190");
			link.l1.go = "exit";
			pchar.questTemp.State = "MorrisWillams_ArrestedToUsurer";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "17");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main(characterFromID("PortRoyal_usurer"), "Eng_Line");
		break;

		case "Step_7_1":
			dialog.text = StringFromKey("eng_Governor_191");
			link.l1 = StringFromKey("eng_Governor_192");
			link.l1.go = "Step_7_3";
			link.l2 = StringFromKey("eng_Governor_193");
			link.l2.go = "Step_7_2";
		break;

		case "Step_7_2":
			dialog.text = StringFromKey("eng_Governor_194");
			link.l1 = StringFromKey("eng_Governor_195");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 3);
			pchar.questTemp.State = "empty";
			pchar.questTemp.CurQuestNumber = "8";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.Waiting_time = "35";
			AddCharacterExpToSkill(pchar, "Leadership", -500);
			AddCharacterExpToSkill(pchar, "Cannons", -300);
			AddCharacterExpToSkill(pchar, "Sneak", -350);
			SetCurrentQuestMark(npchar); // обновим метку
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_196", pchar, GetFullName(pchar)), ENGLAND, 5, 1);
		break;

		case "Step_7_3":
			dialog.text = StringFromKey("eng_Governor_197");
			link.l1 = StringFromKey("eng_Governor_198");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -4);
			pchar.questTemp.State = "SevenTreasures_GoOn";
			pchar.questTemp.GoldQtyGaveModiford = "0"; // кол-во сданное Мэдифорду
			pchar.questTemp.GoldQtyForSeek = "2100"; // кол-во, которое ещё нужно разыскать
			SaveCurrentQuestDateParam("questTemp");
			SetQuestHeader("Eng_Line_7_SevenTresures");
			AddQuestRecord("Eng_Line_7_SevenTresures", "1");
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "EngLine_SevenTreasures_QuestMarkCondition");
			// ==> клад Томаса Уитсона в пещере близ Картахены.
			pchar.GenQuestBox.Cartahena_Cave = true;
			pchar.GenQuestBox.Cartahena_Cave.box1.items.jewelry5 = 300;
			pchar.GenQuestBox.Cartahena_Cave.box1.items.jewelry1 = 110;
			pchar.GenQuestBox.Cartahena_Cave.box1.items.statue1 = 1;
			pchar.GenQuestBox.Cartahena_Cave.box1.items.indian17 = 1;
			pchar.GenQuestBox.Cartahena_Cave.box1.items.pistol2 = 1;
			pchar.GenQuestBox.Cartahena_Cave.box1.items.incas_collection = 1;
			// ==> клад Адриана Сварта на Тринидаде.
			pchar.GenQuestBox.Trinidad_Grot = true;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.jewelry5 = 450;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.blade5 = 1;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.potion2 = 10;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.potionwine = 3;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.jewelry2 = 90;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.indian6 = 1;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.indian11 = 1;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.indian15 = 1;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.indian12 = 1;
			pchar.GenQuestBox.Trinidad_Grot.box1.items.chest = 1;
			// ==> клад Капитана Грея в гроте на Терксе.
			pchar.GenQuestBox.Terks_Grot = true;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry5 = 250;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry3 = 85;
			pchar.GenQuestBox.Terks_Grot.box1.items.blade10 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.potion2 = 5;
			pchar.GenQuestBox.Terks_Grot.box1.items.indian18 = 1;
			pchar.GenQuestBox.Terks_Grot.box1.items.jewelry7 = 5;
			// ==> клад Капитана Купера на Домнинике.
			pchar.GenQuestBox.Dominica_Grot = true;
			pchar.GenQuestBox.Dominica_Grot.box1.items.jewelry5 = 150;
			pchar.GenQuestBox.Dominica_Grot.box1.items.jewelry4 = 75;
			pchar.GenQuestBox.Dominica_Grot.box1.items.pistol4 = 1;
			pchar.GenQuestBox.Dominica_Grot.box1.items.potion1 = 5;
			pchar.GenQuestBox.Dominica_Grot.box1.items.potionrum = 2;
			pchar.GenQuestBox.Dominica_Grot.box1.items.chest = 1;
			// ==> клад Джоржа Бренинхема на Каймане.
			pchar.GenQuestBox.Caiman_Grot = true;
			pchar.GenQuestBox.Caiman_Grot.box1.items.jewelry5 = 350;
			pchar.GenQuestBox.Caiman_Grot.box1.items.jewelry17 = 250;
			pchar.GenQuestBox.Caiman_Grot.box1.items.blade2 = 1;
			pchar.GenQuestBox.Caiman_Grot.box1.items.potion5 = 10;
			pchar.GenQuestBox.Caiman_Grot.box1.items.indian18 = 1;
			// ==> клад капитана Гудли на Кубе.
			pchar.GenQuestBox.Cuba_Grot = true;
			pchar.GenQuestBox.Cuba_Grot.box1.items.jewelry5 = 350;
			pchar.GenQuestBox.Cuba_Grot.box1.items.jewelry17 = 150;
			pchar.GenQuestBox.Cuba_Grot.box1.items.topor2 = 1;
			pchar.GenQuestBox.Cuba_Grot.box1.items.potion2 = 5;
			pchar.GenQuestBox.Cuba_Grot.box1.items.indian10 = 1;
			pchar.GenQuestBox.Cuba_Grot.box1.items.chest = 3;
			// ==> клад Абрахама Блаувельта в катакомбах Гаити рядом с городом.
			pchar.GenQuestBox.Guadeloupe_Cave = true;
			pchar.GenQuestBox.Guadeloupe_Cave.box1.items.jewelry5 = 250;
			pchar.GenQuestBox.Guadeloupe_Cave.box1.items.jewelry17 = 100;
			pchar.GenQuestBox.Guadeloupe_Cave.box1.items.jewelry14 = 10;
			pchar.GenQuestBox.Guadeloupe_Cave.box1.items.potion3 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box1.items.mineral8 = 1;
			pchar.GenQuestBox.Guadeloupe_Cave.box4.items.jewelry5 = 250;
			pchar.GenQuestBox.Guadeloupe_Cave.box4.items.jewelry2 = 50;
			pchar.GenQuestBox.Guadeloupe_Cave.box4.items.jewelry14 = 10;
			pchar.GenQuestBox.Guadeloupe_Cave.box4.items.potion3 = 5;
			pchar.GenQuestBox.Guadeloupe_Cave.box4.items.mineral8 = 1;
		break;

		case "Step_7_4":
			dialog.text = StringFromKey("eng_Governor_199");
			link.l1 = StringFromKey("eng_Governor_200", pchar, pchar.items.jewelry5);
			link.l1.go = "Step_7_5";
			link.l2 = StringFromKey("eng_Governor_201", pchar, pchar.items.jewelry5);
			link.l2.go = "Step_7_7";
		break;

		case "Step_7_5":
			if ((sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5)) <= 2100)
			{
				pchar.questTemp.GoldQtyGaveModiford = sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5);
				pchar.questTemp.GoldQtyForSeek = 2100 - sti(pchar.questTemp.GoldQtyGaveModiford);
				if (pchar.questTemp.GoldQtyForSeek != "0")
				{
					dialog.text = StringFromKey("eng_Governor_202", pchar.items.jewelry5, pchar.questTemp.GoldQtyGaveModiford, pchar.questTemp.GoldQtyForSeek);
					link.l1 = StringFromKey("eng_Governor_203", pchar);
					link.l1.go = "exit";
					AddQuestRecord("Eng_Line_7_SevenTresures", "3");
					AddQuestUserData("Eng_Line_7_SevenTresures", "GoldQtyGaveModiford", pchar.questTemp.GoldQtyGaveModiford);
					AddQuestUserData("Eng_Line_7_SevenTresures", "GoldQtyForSeek", pchar.questTemp.GoldQtyForSeek);
				}
				else
				{
					dialog.text = StringFromKey("eng_Governor_204");
					link.l1 = StringFromKey("eng_Governor_205");
					link.l1.go = "Step_7_6";
				}
				DeleteAttribute(pchar, "items.jewelry5");
				SetCurrentQuestMark(npchar); // обновим метку
			}
			else
			{
				pchar.questTemp.GoldQtyForSeek = sti(pchar.questTemp.GoldQtyGaveModiford) + sti(pchar.items.jewelry5) - 2100;
				dialog.text = StringFromKey("eng_Governor_206", pchar.items.jewelry5, pchar.questTemp.GoldQtyGaveModiford, pchar.questTemp.GoldQtyForSeek);
				link.l1 = StringFromKey("eng_Governor_207");
				link.l1.go = "Step_7_6";
				pchar.items.jewelry5 = pchar.questTemp.GoldQtyForSeek;
			}
		break;

		case "Step_7_6":
			dialog.text = StringFromKey("eng_Governor_208");
			link.l1 = StringFromKey("eng_Governor_209");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 70000);
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "8";
			pchar.questTemp.Waiting_time = "2";
			AddQuestRecord("Eng_Line_7_SevenTresures", "2");
			CloseQuestHeader("Eng_Line_7_SevenTresures");
			DeleteQuestHeader("Eng_Line_7_Second");
			DeleteAttribute(pchar, "questTemp.GoldQtyGaveModiford");
			DeleteAttribute(pchar, "questTemp.GoldQtyForSeek");
			AddCharacterExpToSkill(pchar, "Repair", 500);
			AddCharacterExpToSkill(pchar, "Commerce", 550);
			AddCharacterExpToSkill(pchar, "Defence", 450);
			AddCharacterExpToSkill(pchar, "Leadership", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_210"), ENGLAND, 5, 1);
		break;

		case "Step_7_7":
			dialog.text = StringFromKey("eng_Governor_213", RandPhraseSimple(
						StringFromKey("eng_Governor_211"),
						StringFromKey("eng_Governor_212")));
			link.l1 = StringFromKey("eng_Governor_214", pchar);
			link.l1.go = "exit";
		break;

		case "Step_7_10":
			dialog.text = StringFromKey("eng_Governor_215");
			link.l1 = StringFromKey("eng_Governor_216", pchar);
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuestBox.Cartahena_Cave");
			DeleteAttribute(pchar, "GenQuestBox.Trinidad_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Terks_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Dominica_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Caiman_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Cuba_Grot");
			DeleteAttribute(pchar, "GenQuestBox.Guadeloupe_Cave");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "8";
			pchar.questTemp.Waiting_time = "20";
			AddQuestRecord("Eng_Line_7_SevenTresures", "4");
			AddQuestUserData("Eng_Line_7_SevenTresures", "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("Eng_Line_7_SevenTresures");
			DeleteQuestHeader("Eng_Line_7_Second");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			ChangeCharacterReputation(pchar, -5);
			AddMoneyToCharacter(pchar, -150000);
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
		break;

		case "Step_8_1":
			dialog.text = StringFromKey("eng_Governor_217");
			link.l1 = StringFromKey("eng_Governor_218", pchar);
			link.l1.go = "Step_8_2";
		break;

		case "Step_8_2":
			dialog.text = StringFromKey("eng_Governor_219");
			link.l1 = StringFromKey("eng_Governor_220", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "ToMansfield_GoOn";
			SetQuestHeader("Eng_Line_8_ToMansfield");
			AddQuestRecord("Eng_Line_8_ToMansfield", "1");
			Pchar.quest.ToMansfield_IntoTheTown.win_condition.l1 = "location";
			Pchar.quest.ToMansfield_IntoTheTown.win_condition.l1.location = "LaVega_town";
			Pchar.quest.ToMansfield_IntoTheTown.win_condition = "ToMansfield_IntoTheTown";
			SetLocationCapturedState("LaVega_town", true);
			//--> огонь и пламень
			i = FindLocation("LaVega_town");
			locations[i].models.always.town = "LaVega_quest";
			locations[i].models.always.locatorsl2 = "LaVega_1_quest";
			locations[i].models.always.locatorsl3 = "LaVega_locators_quest";
			locations[i].models.day.charactersPatch = "LaVega_patch_day_quest";
			locations[i].models.night.charactersPatch = "LaVega_patch_night_quest";
			//<-- огонь и пламень
			Log_QuestInfo("Форт буканьеров пуст и горит.");
		break;

		case "Step_8_3":
			dialog.text = StringFromKey("eng_Governor_221");
			link.l1 = StringFromKey("eng_Governor_222");
			link.l1.go = "Step_8_4";
		break;

		case "Step_8_4":
			dialog.text = StringFromKey("eng_Governor_223");
			link.l1 = StringFromKey("eng_Governor_224");
			link.l1.go = "exit";
			npchar.TempQuest.KnowAboutModiford = 1;
		break;

		case "Step_8_5":
			dialog.text = StringFromKey("eng_Governor_225");
			link.l1 = StringFromKey("eng_Governor_226");
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "letter_open_EngLineQ8");
			DeleteAttribute(npchar, "TempQuest.KnowAboutModiford");
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "empty";
			pchar.questTemp.CurQuestNumber = "9";
			pchar.questTemp.Waiting_time = "10";
			CloseQuestHeader("Eng_Line_8_ToMansfield");
			SetLocationCapturedState("LaVega_town", false);
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//--> огонь и пламень убираем
			i = FindLocation("LaVega_town");
			locations[i].models.always.town = "LaVega";
			locations[i].models.always.locatorsl2 = "LaVega_1";
			locations[i].models.always.locatorsl3 = "LaVega_locators";
			locations[i].models.day.charactersPatch = "LaVega_patch_day";
			locations[i].models.night.charactersPatch = "LaVega_patch_night";
			//<-- огонь и пламень
			// ==> Мэнсфилд убит, теперь он будет Алистером Гудом.
			sld = characterFromID("Edward Mansfield");
			sld.model = "DEDnoName";
			sld.name = FindPersonalName("Edward_Mansfield2_name");
			sld.lastname = FindPersonalName("Edward_Mansfield2_lastname");
			SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
			FaceMaker(sld);

			sld.greeting = "Gr_HeadPirates";
			sld.nation = PIRATE;
			sld.quest.type = "hovernor";
			SetRandSPECIAL(sld);
			SetSelfSkill(sld, 90, 90, 90, 60, 70);
			sld.watchBoxes = true;
			sld.standUp = true; //вставать и нападать на врага
			LAi_SetHuberType(sld);
			LAi_RemoveLoginTime(sld);
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			LAi_SetImmortal(sld, true);
			DeleteAttribute(sld, "Dialog.TempNode");

			QuestSetCurrentNode("Edward Mansfield", "No_Mansfield_first_time");
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Edward Mansfield")], "LaVega_townhall", "sit", "sit1");
			AddCharacterExpToSkill(pchar, "Fortune", 500);
			AddCharacterExpToSkill(pchar, "Sailing", 550);
			AddCharacterExpToSkill(pchar, "FencingLight", 450);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 400);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_227"), ENGLAND, 5, 1);
		break;

		case "Step_9_1":
			pchar.questTemp.State = "AttackSantiago_GoOn";
			if (!CheckAttribute(npchar, "TempQuest.KindResult")) // письмо не получено, но в курсе нападения испанцев
			{
				dialog.text = StringFromKey("eng_Governor_228");
				link.l1 = StringFromKey("eng_Governor_229");
				link.l1.go = "Step_9_2";
			}
			else if (npchar.TempQuest.KindResult == 2) // признак результата завершения квеста, 2 == вообще не в курсе, что произошло
			{
				dialog.text = StringFromKey("eng_Governor_230");
				link.l1 = StringFromKey("eng_Governor_231");
				link.l1.go = "Step_9_2";
			}
			else // признак результата завершения квеста, 1 == было захвачено письмо
			{
				dialog.text = StringFromKey("eng_Governor_232");
				link.l1 = StringFromKey("eng_Governor_233", pchar);
				link.l1.go = "Step_9_2";
			}
			Log_QuestInfo("Задание получено.");
			DeleteAttribute(npchar, "TempQuest.KindResult");
			characters[GetCharacterIndex("Santiago_Mayor")].dialog.captureNode = "EL9_SantiagoAttack"; //капитулянтская нода мэра
		break;

		case "Step_9_2":
			dialog.text = StringFromKey("eng_Governor_234");
			link.l1 = StringFromKey("eng_Governor_235");
			link.l1.go = "Step_9_3";
		break;

		case "Step_9_3":
			dialog.text = StringFromKey("eng_Governor_236");
			link.l1 = StringFromKey("eng_Governor_237", pchar);
			link.l1.go = "exit";
			SetQuestHeader("Eng_Line_9_AttackSantiago");
			AddQuestRecord("Eng_Line_9_AttackSantiago", "1");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("Santiago_Mayor"), "Eng_Line", "StateLines_CaptureCity_QuestMarkCondition");
		break;

		case "Step_9_4":
			dialog.text = StringFromKey("eng_Governor_238", pchar.name);
			link.l1 = StringFromKey("eng_Governor_239");
			link.l1.go = "Step_9_5";
			QuestSetCurrentNode("Santiago_Mayor", "First time");
		break;

		case "Step_9_5":
			dialog.text = StringFromKey("eng_Governor_240");
			link.l1 = StringFromKey("eng_Governor_241");
			link.l1.go = "exit";
			//HardCoffee реф диалогов с Морганом
			//QuestSetCurrentNode("Henry Morgan", "Give_blade");
			pchar.QuestTemp.EngLine_Morgan_task = "Give_blade";
			AddLandQuestmark_Main(CharacterFromID("Henry Morgan"), "Eng_Line");
			sld = characterFromID("Himenes");
			RemovePassenger(pchar, sld);
			sld.LifeDay = 1; // уберем нпс на след.день.
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "10";
			pchar.questTemp.Waiting_time = "20";
			CloseQuestHeader("Eng_Line_9_AttackSantiago");
			AddCharacterExpToSkill(pchar, "Repair", 550);
			AddCharacterExpToSkill(pchar, "Cannons", 760);
			AddCharacterExpToSkill(pchar, "Defence", 450);
			AddCharacterExpToSkill(pchar, "Pistol", 300);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_242", pchar), ENGLAND, 5, 1);
		break;

		case "Step_10_1":
			dialog.text = StringFromKey("eng_Governor_243");
			link.l1 = StringFromKey("eng_Governor_244");
			link.l1.go = "Step_10_2";
		break;

		case "Step_10_2":
			dialog.text = StringFromKey("eng_Governor_245", GetFullName(pchar));
			link.l1 = StringFromKey("eng_Governor_246");
			link.l1.go = "exit";
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "PortRoyal_houseS1", "sit", "sit2");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "11";
			pchar.questTemp.Waiting_time = "7";
			CloseQuestHeader("Eng_Line_10_SpanishAttack");
			AddCharacterExpToSkill(pchar, "Repair", 600);
			AddCharacterExpToSkill(pchar, "Leadership", 550);
			AddCharacterExpToSkill(pchar, "Commerce", 600);
			AddCharacterExpToSkill(pchar, "Accuracy", 400);
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddMoneyToCharacter(pchar, 80000);
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_247"), ENGLAND, 10, 6);
		break;

		case "Step_11_1":
			dialog.text = StringFromKey("eng_Governor_248");
			link.l1 = StringFromKey("eng_Governor_249", pchar);
			link.l1.go = "exit";
			SetQuestHeader("Eng_Line_11_OccupyMein");
			AddQuestRecord("Eng_Line_11_OccupyMein", "1");
			pchar.questTemp.State = "OccupyMein_GoOn";
			characters[GetCharacterIndex("Cumana_Mayor")].dialog.captureNode = "EngLine11Quest_OccupyMein"; //капитулянтская нода мэра
			characters[GetCharacterIndex("Caracas_Mayor")].dialog.captureNode = "EngLine11Quest_OccupyMein"; //капитулянтская нода мэра
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "EngLine_11_Guber_QuestMarkCondition");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("Cumana_Mayor"), "Eng_Line", "StateLines_CaptureCity_QuestMarkCondition");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("Caracas_Mayor"), "Eng_Line", "StateLines_CaptureCity_QuestMarkCondition");
		break;

		case "Step_11_2":
			dialog.text = StringFromKey("eng_Governor_250", GetFullName(pchar));
			link.l1 = StringFromKey("eng_Governor_251");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Q11_Cumana");
			DeleteAttribute(pchar, "questTemp.Q11_Caracas");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "12";
			pchar.questTemp.Waiting_time = "30";
			CloseQuestHeader("Eng_Line_11_OccupyMein");
			AddCharacterExpToSkill(pchar, "Repair", 1000);
			AddCharacterExpToSkill(pchar, "Commerce", 1600);
			AddCharacterExpToSkill(pchar, "Accuracy", 1000);
			AddCharacterExpToSkill(pchar, "Defence", 1100);
			AddCharacterExpToSkill(pchar, "Cannons", 1300);
			AddCharacterExpToSkill(pchar, "Sailing", 1200);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddLandQuestmark_Main_WithCondition(npchar, "Eng_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Eng_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_252", pchar, pchar.name), ENGLAND, 5, 1);
		break;

		case "Step_12_1":
			dialog.text = StringFromKey("eng_Governor_253");
			link.l1 = StringFromKey("eng_Governor_254");
			link.l1.go = "exit";
			SetQuestHeader("Eng_Line_12_ColonelLinch");
			AddQuestRecord("Eng_Line_12_ColonelLinch", "1");
			pchar.questTemp.State = "ColonelLinch_GoToKingstown";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");

			Pchar.quest.ColonelLinch_IntoTheResidence.win_condition.l1 = "location";
			Pchar.quest.ColonelLinch_IntoTheResidence.win_condition.l1.location = "SentJons_townhall";
			Pchar.quest.ColonelLinch_IntoTheResidence.win_condition = "ColonelLinch_IntoTheResidence";
		break;

		case "Step_12_2":
			dialog.text = StringFromKey("eng_Governor_255");
			link.l1 = StringFromKey("eng_Governor_256");
			link.l1.go = "Step_12_3";
		break;

		case "Step_12_3":
			dialog.text = StringFromKey("eng_Governor_257");
			link.l1 = StringFromKey("eng_Governor_258");
			link.l1.go = "Step_12_4";
		break;

		case "Step_12_4":
			pchar.nation = PIRATE;
			LAi_SetImmortal(npchar, true);
			LAi_SetImmortal(characterFromID("PortRoyal_Mayor"), true);
			bDisableFastReload = true; // закрыть переходы.
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_NoRebirthEnable(npchar);
			//LAi_SetActorType(npchar);
			//LAi_ActorAfraid(npchar, pchar, false);
			TEV.ResidenceFightTemp = true; // при save/load сохранять состаяние в LAi_LocationFightDisable

			LAi_group_Register("EnemyFight");
			float locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			//поставим стражников во враждебную группу
			int num = FindNearCharacters(pchar, 20.0, -1.0, -1.0, 0.01, true, true);
			if (num > 0)
			{
				for (i = 0; i < num; i++)
				{
					int idx = sti(chrFindNearCharacters[i].index);
					sld = &Characters[idx];
					if (sld.chr_ai.type == "guardian")
					{
						DeleteAttribute(sld, "City"); // fix
						LAi_NoRebirthEnable(sld);
						LAi_CharacterReincarnation(sld, false, false);
						LAi_group_MoveCharacter(sld, "EnemyFight");
					}
				}
			}
			//добавим солдат для хардокора
			string SModel;
			for (i = 1; i <= 3; i++)
			{
				SModel = "guard_eng_" + i;
				if (i == 3) SModel = "off_eng_6";
				sld = GetCharacter(NPC_GenerateCharacter("EngSolder" + i, SModel, "man", "man", 30, ENGLAND, 0, true));
				FantomMakeCoolFighter(sld, 30, 100, 100, "topor1", "pistol3", 250);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "PortRoyal_townhall", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "ColonelLinch_AfterFight");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("eng_Governor_259"), ENGLAND, 5, 1);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Step_12_5":
			dialog.text = StringFromKey("eng_Governor_260", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("eng_Governor_261", pchar);
			link.l1.go = "Step_12_6";
		break;

		case "Step_12_6":
			dialog.text = StringFromKey("eng_Governor_262", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("eng_Governor_263", pchar);
			link.l1.go = "exit";
			pchar.name = GetAddress_Form(NPChar) + " " + pchar.name;
			SetCharacterPerk(pchar, "Nobleman");
			AddMoneyToCharacter(pchar, 300000);
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			SetNationRelationBoth(SPAIN, ENGLAND, RELATION_NEUTRAL);
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			pchar.questTemp.State = "EndOfQuestLine";
			bWorldAlivePause = false; // Конец линейки
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			RemoveMapQuestmark("PortRoyal_town", "Eng_Line");
			Achievment_Set(ACH_Na_sluzhbe_Anglii);
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

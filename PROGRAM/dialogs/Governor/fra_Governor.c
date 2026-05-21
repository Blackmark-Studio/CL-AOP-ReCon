// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("fra_Governor_3", RandPhraseSimple(
						StringFromKey("fra_Governor_1"),
						StringFromKey("fra_Governor_2")));
			link.l1 = StringFromKey("fra_Governor_6", RandPhraseSimple(
						StringFromKey("fra_Governor_4"),
						StringFromKey("fra_Governor_5")));
			link.l1.go = "exit";

			//******************** голландская линейка ***************************
			switch (pchar.questTemp.State)   // что делаем в данный момент
			{
				case "DelivLettTortuga_toDOjeron": // Квест №7 голл. линейки. Письмо от Стэвезанта
					link.l1 = StringFromKey("fra_Governor_7", pchar);
					link.l1.go = "Step_H7_1";
				break;
				case "DelivLettTortuga_WaitTwoHours":
					if (GetQuestPastTimeParam("questTemp") > 1)
					{
						link.l1 = StringFromKey("fra_Governor_8", pchar);
						link.l1.go = "Step_H7_3";
					}
					else
					{
						dialog.text = StringFromKey("fra_Governor_9");
						link.l1 = StringFromKey("fra_Governor_10", pchar);
						link.l1.go = "exit";
					}
				break;
				case "DelivLettTortuga_AfterRape": //Голландская линейка, квест №7. после грабежа.
					link.l1 = StringFromKey("fra_Governor_11");
					link.l1.go = "Step_H7_5";
				break;
			}
		break;
		//******************** французская линейка ***************************
		case "work_1":  // работа на благо короны - линейка нации
		// сюда вход только с патентом, проверка выше
			dialog.text = StringFromKey("fra_Governor_15", LinkRandPhrase(
						StringFromKey("fra_Governor_12"),
						StringFromKey("fra_Governor_13"),
						StringFromKey("fra_Governor_14")));
			link.l1 = StringFromKey("fra_Governor_18", RandPhraseSimple(
						StringFromKey("fra_Governor_16"),
						StringFromKey("fra_Governor_17")));
			link.l1.go = "exit";

			switch (pchar.questTemp.State)   // что делаем в данный момент
			{
				case "empty":   // Нет взятых квестов
					if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
					{
						dialog.text = StringFromKey("fra_Governor_22", LinkRandPhrase(
									StringFromKey("fra_Governor_19"),
									StringFromKey("fra_Governor_20"),
									StringFromKey("fra_Governor_21")));
						link.l1 = StringFromKey("fra_Governor_23");
						link.l1.go = "exit";
					}
					else
					{
						switch (pchar.questTemp.CurQuestNumber)   // Взятие квестов начиная со второго
						{
							case "2":
								dialog.text = StringFromKey("fra_Governor_24");
								link.l1 = StringFromKey("fra_Governor_25");
								link.l1.go = "Step_2_1";
							break;
							case "3":
								dialog.text = StringFromKey("fra_Governor_26", pchar);
								link.l1 = StringFromKey("fra_Governor_27");
								link.l1.go = "Step_3_1";
							break;
							case "4":
								dialog.text = StringFromKey("fra_Governor_28", pchar);
								link.l1 = StringFromKey("fra_Governor_29");
								link.l1.go = "Step_4_1";
							break;
							case "5":
								dialog.text = StringFromKey("fra_Governor_30", pchar);
								link.l1 = StringFromKey("fra_Governor_31");
								link.l1.go = "exit";
								LAi_group_Delete("PeaceGroup");
								pchar.questTemp.State = "Fr5AnnaHant_toAnna";
								AddQuestRecord("Fra_Line_5_KillAnnaHanters", "1");
								sld = GetCharacter(NPC_GenerateCharacter("AnnaDeLeiva", "AnnaDeLeiva", "woman", "towngirl2", 10, SPAIN, -1, false));
								sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
								sld.name = FindPersonalName("AnnaDeLeiva_name");
								sld.lastname = FindPersonalName("AnnaDeLeiva_lastname");
								LAi_SetStayType(sld);
								LAi_group_MoveCharacter(sld, "PeaceGroup");
								ChangeCharacterAddressGroup(sld, "Tortuga_townhallRoom", "goto", "goto2");
								AddLandQuestmark_Main(sld, "Fra_Line");
								RemoveLandQuestmark_Main(npchar, "Fra_Line");
							break;
							case "6":
								dialog.text = StringFromKey("fra_Governor_32", pchar);
								link.l1 = StringFromKey("fra_Governor_33");
								link.l1.go = "Step_6_1";
							break;
							case "7":
								dialog.text = StringFromKey("fra_Governor_34");
								link.l1 = StringFromKey("fra_Governor_35");
								link.l1.go = "Step_7_1";
							break;
							case "8":
								dialog.text = StringFromKey("fra_Governor_36", pchar);
								link.l1 = StringFromKey("fra_Governor_37");
								link.l1.go = "Step_8_1";
							break;
							case "9":
								dialog.text = StringFromKey("fra_Governor_38", pchar);
								link.l1 = StringFromKey("fra_Governor_39");
								link.l1.go = "Step_9_1";
							break;
							case "10":
								dialog.text = StringFromKey("fra_Governor_40", pchar);
								link.l1 = StringFromKey("fra_Governor_41");
								link.l1.go = "Step_10_1";
							break;
							case "11":
								dialog.text = StringFromKey("fra_Governor_42", pchar);
								link.l1 = StringFromKey("fra_Governor_43");
								link.l1.go = "Step_11_1";
							break;
							case "12":
								dialog.text = StringFromKey("fra_Governor_44", pchar);
								link.l1 = StringFromKey("fra_Governor_45");
								link.l1.go = "Step_12_1";
							break;
						}
					}
				break;
				case "":           // Квест №1, Охрана пирата Леграна.
					dialog.text = StringFromKey("fra_Governor_46", pchar);
					link.l1 = StringFromKey("fra_Governor_47");
					link.l1.go = "Step_1_1";
				break;
				case "Fr1Legran_backGovernor":
					dialog.text = StringFromKey("fra_Governor_48");
					link.l1 = StringFromKey("fra_Governor_49");
					link.l1.go = "Step_1_2";
				break;
				case "Fr1Legran_LegranKilled":
					dialog.text = StringFromKey("fra_Governor_50");
					link.l1 = StringFromKey("fra_Governor_51", pchar);
					link.l1.go = "Step_1_3";
				break;
				case "Fr1Legran_LegranIsDead":
					dialog.text = StringFromKey("fra_Governor_52");
					link.l1 = StringFromKey("fra_Governor_53");
					link.l1.go = "Step_1_5";
				break;
				case "Fr2Letter_SeekProblems":
					dialog.text = StringFromKey("fra_Governor_54");
					link.l1 = StringFromKey("fra_Governor_55");
					link.l1.go = "Step_2_3";
				break;
				case "Fr2Letter_NiceResult":
					dialog.text = StringFromKey("fra_Governor_56");
					link.l1 = StringFromKey("fra_Governor_57", pchar);
					link.l1.go = "Step_2_6";
				break;
				case "Fr3TakeAnna_BadResult":
					dialog.text = StringFromKey("fra_Governor_58", GetAddress_Form(NPChar));
					link.l1 = StringFromKey("fra_Governor_59", pchar);
					link.l1.go = "Step_3_5";
				break;
				case "Fr3TakeAnna_NiceResult":
					dialog.text = StringFromKey("fra_Governor_60", pchar);
					link.l1 = StringFromKey("fra_Governor_61");
					link.l1.go = "Step_3_7";
				break;
				case "Fr4SoleiRoyal_DieHard":
					dialog.text = StringFromKey("fra_Governor_62", pchar);
					link.l1 = StringFromKey("fra_Governor_63", pchar);
					link.l1.go = "Step_4_7";
				break;
				case "Fr4SoleiRoyal_SoleiRoyalSunk":
					dialog.text = StringFromKey("fra_Governor_64", pchar);
					link.l1 = StringFromKey("fra_Governor_65", pchar);
					link.l1.go = "Step_4_9";
				break;
				case "Fr4SoleiRoyal_backTortuga":
					dialog.text = StringFromKey("fra_Governor_66", pchar);
					link.l1 = StringFromKey("fra_Governor_67", pchar);
					link.l1.go = "Step_4_11";
				break;
				case "Fr5AnnaHant_GoodWork":
					dialog.text = StringFromKey("fra_Governor_68", pchar);
					link.l1 = StringFromKey("fra_Governor_69");
					link.l1.go = "exit";
					DeleteAttribute(&locations[FindLocation("Mayak10")], "DisableEncounters"); //откроем энканутеры
					pchar.questTemp.State = "empty";
					SaveCurrentQuestDateParam("questTemp");
					pchar.questTemp.CurQuestNumber = "6";
					pchar.questTemp.Waiting_time = "7";
					CloseQuestHeader("Fra_Line_5_KillAnnaHanters");
					AddMoneyToCharacter(pchar, 5000);
					AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
					AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
				break;
				case "Fr6Olone_OloneIsDead":
					dialog.text = StringFromKey("fra_Governor_70");
					link.l1 = StringFromKey("fra_Governor_71");
					link.l1.go = "Step_6_3";
				break;
				case "Fr6Olone_OloneIsLive":
					dialog.text = StringFromKey("fra_Governor_72");
					link.l1 = StringFromKey("fra_Governor_73");
					link.l1.go = "Step_6_7";
				break;
				case "Fr6Olone_TakeMoney":
					dialog.text = StringFromKey("fra_Governor_74");
					link.l1 = StringFromKey("fra_Governor_75");
					link.l1.go = "Step_6_9";
				break;
				case "Fr7RockBras_toSeekPlace":
					dialog.text = StringFromKey("fra_Governor_76");
					link.l1 = StringFromKey("fra_Governor_77", pchar);
					link.l1.go = "exit";
					link.l2 = StringFromKey("fra_Governor_78", pchar);
					link.l2.go = "Step_7_6";
				break;
				case "Fr7RockBras_RockIsDead":
					dialog.text = StringFromKey("fra_Governor_79");
					link.l1 = StringFromKey("fra_Governor_80");
					link.l1.go = "Step_7_7";
				break;
				case "Fr7RockBras_RockIsSaved":
					dialog.text = StringFromKey("fra_Governor_81");
					link.l1 = StringFromKey("fra_Governor_82");
					link.l1.go = "Step_7_8";
				break;
				case "Fr7RockBras_RockIsAgony":
					dialog.text = StringFromKey("fra_Governor_83");
					link.l1 = StringFromKey("fra_Governor_84");
					link.l1.go = "Step_7_7";
				break;
				case "Fr8ThreeCorsairs_backGovernor":
					dialog.text = StringFromKey("fra_Governor_85", pchar, GetFullName(pchar));
					link.l1 = StringFromKey("fra_Governor_86");
					link.l1.go = "Step_8_2";
				break;
				case "Fr9GuardPP_GoodWork":
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						dialog.text = StringFromKey("fra_Governor_87", pchar);
						link.l1 = StringFromKey("fra_Governor_88", pchar);
						link.l1.go = "Step_9_4";
					}
					else
					{
						dialog.text = StringFromKey("fra_Governor_89", pchar);
						link.l1 = StringFromKey("fra_Governor_90");
						link.l1.go = "Step_9_2";
					}
				break;
				case "Fr9GuardPP_SoleiRoyalSunk":
					dialog.text = StringFromKey("fra_Governor_91", pchar);
					link.l1 = StringFromKey("fra_Governor_92", pchar);
					link.l1.go = "Step_9_4";
				break;
				case "Fr9GuardPP_DieHard":
					dialog.text = StringFromKey("fra_Governor_93", pchar);
					link.l1 = StringFromKey("fra_Governor_94");
					link.l1.go = "Step_9_6";
				break;
				case "Fr9GuardPP_Late":
					dialog.text = StringFromKey("fra_Governor_95", pchar);
					link.l1 = StringFromKey("fra_Governor_96", pchar);
					link.l1.go = "Step_9_7";
				break;
				case "Fr10OccupySD_toWeWon":
					dialog.text = StringFromKey("fra_Governor_97", pchar);
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						link.l1 = StringFromKey("fra_Governor_98", pchar);
						link.l1.go = "Step_10_4";
					}
					else
					{
						link.l1 = StringFromKey("fra_Governor_99", pchar);
						link.l1.go = "Step_10_6";
					}
				break;
				case "Fr11OccupySC_toWeWon":
					dialog.text = StringFromKey("fra_Governor_100", pchar);
					if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
					{
						link.l1 = StringFromKey("fra_Governor_101", pchar);
						link.l1.go = "Step_11_3";
					}
					else
					{
						link.l1 = StringFromKey("fra_Governor_102");
						link.l1.go = "Step_11_5";
					}
				break;
				case "QuestLineBreake":
					dialog.text = StringFromKey("fra_Governor_103");
					link.l1 = "...";
					link.l1.go = "exit";
					bWorldAlivePause = false; // Конец линейки
					RemoveLandQuestmark_Main(npchar, "Fra_Line");
					RemoveMapQuestmark("Tortuga_town", "Fra_Line");
				break;
				case "EndOfQuestLine":
					dialog.text = StringFromKey("fra_Governor_104", pchar);
					link.l1 = StringFromKey("fra_Governor_105");
					link.l1.go = "exit";
					bWorldAlivePause = false; // Конец линейки
					RemoveLandQuestmark_Main(npchar, "Fra_Line");
					RemoveMapQuestmark("Tortuga_town", "Fra_Line");
				break;
			}
		break;
		//********************** Квест №7 голландки, Доставка письма д'Ожерону от Стэвезанта ************************
		case "Step_H7_1":
			dialog.text = StringFromKey("fra_Governor_106");
			link.l1 = StringFromKey("fra_Governor_107");
			link.l1.go = "Step_H7_2";
			TakeItemFromCharacter(pchar, "letter_HolLineQ7_2");
		break;
		case "Step_H7_2":
			dialog.text = StringFromKey("fra_Governor_108");
			link.l1 = StringFromKey("fra_Governor_109", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "2");
			pchar.questTemp.State = "DelivLettTortuga_WaitTwoHours";
			SaveCurrentQuestDateParam("questTemp");
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "HolLine_7_WaitTwoHours_QuestMarkCondition");
		break;
		case "Step_H7_3":
			dialog.text = StringFromKey("fra_Governor_110");
			link.l1 = StringFromKey("fra_Governor_111");
			link.l1.go = "Step_H7_4";
		break;
		case "Step_H7_4":
			dialog.text = StringFromKey("fra_Governor_112");
			link.l1 = StringFromKey("fra_Governor_113", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "3");
			AddQuestUserData("Hol_Line_7_DelivLettTortuga", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.State = "DelivLettTortuga_SnapMeeting";
			GiveItem2Character(pchar, "letter_HolLineQ7_1");
			LocatorReloadEnterDisable("Tortuga_town", "gate_back", true);
			LocatorReloadEnterDisable("Tortuga_town", "reload1_back", true);
			LocatorReloadEnterDisable("Tortuga_town", "reload2_back", true);
			LocatorReloadEnterDisable("Tortuga_town", "boat", true);
			LocatorReloadEnterDisable("Tortuga_tavern", "reload2_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], true);
			Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition.l1 = "location";
			Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition.l1.location = "Tortuga_town";
			Pchar.quest.DelivLettTortuga_SnapMeeting.win_condition = "DelivLettTortuga_SnapMeeting";
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
		case "Step_H7_5":
			dialog.text = StringFromKey("fra_Governor_114");
			link.l1 = StringFromKey("fra_Governor_115", pchar);
			link.l1.go = "Step_H7_6";
		break;
		case "Step_H7_6":
			dialog.text = StringFromKey("fra_Governor_116");
			link.l1 = StringFromKey("fra_Governor_117", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "DelivLettTortuga_toPortMan";
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_PortMan"), "Hol_Line");
		break;
		//********************** Квест №1 французской линейки, охрана Леграна ************************
		case "Step_1_1":
			dialog.text = StringFromKey("fra_Governor_118", pchar);
			link.l1 = StringFromKey("fra_Governor_119");
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp");
			// остальные линейки в сад -->
			pchar.questTemp.NationQuest = FRANCE;
			DeleteAttribute(&colonies[FindColony("PortoBello")], "notCaptured");
			DeleteAttribute(&colonies[FindColony("Panama")], "notCaptured");
			StateLines_Begin_DelQuestMarks();
			// остальные линейки в сад <--
			pchar.questTemp.State = "Fr1Legran_toTavern";
			AddQuestRecord("Fra_Line_1_LegranDis", "1");
			sld = GetCharacter(NPC_GenerateCharacter("Legran", "citiz_1", "man", "man", 40, FRANCE, -1, false)); //watch_quest_moment
			FantomMakeCoolFighter(sld, 40, 90, 40, "blade28", "pistol4", 120);
			sld.name = FindPersonalName("Legran_name");
			sld.lastname = FindPersonalName("Legran_lastname");
			sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			sld.money = 1000000;
			sld.items.jewelry5 = 30;
			sld.items.indian6 = 1;
			sld.items.jewelry14 = 12;
			sld.items.indian2 = 1;
			sld.items.indian8 = 1;
			sld.items.indian7 = 1;
			sld.items.indian12 = 1;
			sld.items.jewelry2 = 20;
			sld.greeting = "Gr_MiddPirate";
			GiveItem2Character(sld, "cirass4");
			FreeSitLocator("Tortuga_tavern", "sit3");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit3");
			AddLandQuestmark_Main(sld, "Fra_Line");
		break;
		case "Step_1_2":
			dialog.text = StringFromKey("fra_Governor_120");
			link.l1 = StringFromKey("fra_Governor_121");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "2";
			pchar.questTemp.Waiting_time = "7";
			CloseQuestHeader("Fra_Line_1_LegranDis");
			AddTitleNextRate(sti(NPChar.nation), 2);
			AddCharacterExpToSkill(pchar, "Sneak", -170);
			AddCharacterExpToSkill(pchar, "Commerce", 90);
			AddCharacterExpToSkill(pchar, "Fencing", 80);
			AddCharacterExpToSkill(pchar, "Fortune", 70);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
		break;
		case "Step_1_3":
			dialog.text = StringFromKey("fra_Governor_122");
			link.l1 = StringFromKey("fra_Governor_123");
			link.l1.go = "Step_1_4";
		break;
		case "Step_1_4":
			dialog.text = StringFromKey("fra_Governor_124", pchar);
			link.l1 = StringFromKey("fra_Governor_125", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_1_LegranDis");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -3);
			bWorldAlivePause = false; // Конец линейки
			ChangeCharacterReputation(pchar, -10);
			AddCharacterExpToSkill(pchar, "Sneak", -170);
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			RemoveMapQuestmark("Tortuga_town", "Fra_Line");
			//слухи			
			AddSimpleRumour(
				StringFromKey("fra_Governor_126", pchar, GetMainCharacterNameGen()), FRANCE, 5, 1);
		break;
		case "Step_1_5":
			dialog.text = StringFromKey("fra_Governor_127");
			link.l1 = StringFromKey("fra_Governor_128", pchar);
			link.l1.go = "Step_1_6";
		break;
		case "Step_1_6":
			dialog.text = StringFromKey("fra_Governor_129", GetAddress_Form(NPChar), pchar.lastname);
			link.l1 = StringFromKey("fra_Governor_130");
			link.l1.go = "Step_1_7";
		break;
		case "Step_1_7":
			dialog.text = StringFromKey("fra_Governor_131", pchar);
			link.l1 = StringFromKey("fra_Governor_132");
			link.l1.go = "Step_1_8";
		break;
		case "Step_1_8":
			dialog.text = StringFromKey("fra_Governor_133");
			link.l1 = StringFromKey("fra_Governor_134");
			link.l1.go = "Step_1_9";
		break;
		case "Step_1_9":
			dialog.text = StringFromKey("fra_Governor_135");
			link.l1 = StringFromKey("fra_Governor_136");
			link.l1.go = "Step_1_10";
		break;
		case "Step_1_10":
			dialog.text = StringFromKey("fra_Governor_137");
			if (sti(pchar.money) >= 1200000)
			{
				link.l1 = StringFromKey("fra_Governor_138");
				link.l1.go = "Step_1_11";
				AddMoneyToCharacter(pchar, -1200000);
				NextDiag.TempNode = "First time";
			}
			else
			{
				link.l1 = StringFromKey("fra_Governor_139");
				link.l1.go = "exit";
				NextDiag.TempNode = "Step_1_10";
			}
		break;

		case "Step_1_11":
			dialog.text = StringFromKey("fra_Governor_140", pchar);
			link.l1 = StringFromKey("fra_Governor_141");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "2";
			pchar.questTemp.Waiting_time = "15";
			CloseQuestHeader("Fra_Line_1_LegranDis");
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Pistol", 150);
			AddCharacterExpToSkill(pchar, "Grappling", 120);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_142", pchar, GetFullName(pchar)), FRANCE, 5, 1);
		break;
		//********************** Квест №2 доставка письма на Кюрасао ************************
		case "Step_2_1":
			dialog.text = StringFromKey("fra_Governor_143");
			link.l1 = StringFromKey("fra_Governor_144", pchar);
			link.l1.go = "Step_2_2";
		break;
		case "Step_2_2":
			dialog.text = StringFromKey("fra_Governor_145", pchar);
			link.l1 = StringFromKey("fra_Governor_146");
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "Fr2Letter_toCuracao";
			AddQuestRecord("Fra_Line_2_DelivLetter", "1");
			GiveItem2Character(pchar, "letter_FraLineQ1");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Fra_Line");
		break;
		case "Step_2_3":
			dialog.text = StringFromKey("fra_Governor_147");
			link.l1 = StringFromKey("fra_Governor_148");
			link.l1.go = "Step_2_4";
		break;
		case "Step_2_4":
			dialog.text = StringFromKey("fra_Governor_149");
			link.l1 = StringFromKey("fra_Governor_150");
			link.l1.go = "Step_2_5";
		break;
		case "Step_2_5":
			dialog.text = StringFromKey("fra_Governor_151");
			link.l1 = StringFromKey("fra_Governor_152");
			link.l1.go = "exit";
			group_DeleteGroup("Spa_Attack");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "3";
			pchar.questTemp.Waiting_time = "20";
			CloseQuestHeader("Fra_Line_2_DelivLetter");
			DeleteAttribute(pchar, "questTemp.Out");
			DeleteAttribute(pchar, "questTemp.shore");
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Accuracy", 200);
			ChangeCharacterReputation(pchar, -1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			RemoveLandQuestmark_Main(CharacterFromID("Villemstad_tavernkeeper"), "Fra_Line");
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_153", pchar, GetFullName(pchar)), FRANCE, 5, 1);
		break;
		case "Step_2_6":
			dialog.text = StringFromKey("fra_Governor_154", pchar);
			link.l1 = StringFromKey("fra_Governor_155");
			link.l1.go = "Step_2_7";
		break;
		case "Step_2_7":
			dialog.text = StringFromKey("fra_Governor_156", pchar);
			link.l1 = StringFromKey("fra_Governor_157", pchar);
			link.l1.go = "Step_2_8";
		break;
		case "Step_2_8":
			dialog.text = StringFromKey("fra_Governor_158", pchar);
			link.l1 = StringFromKey("fra_Governor_159");
			link.l1.go = "exit";
			group_DeleteGroup("Spa_Attack");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "3";
			pchar.questTemp.Waiting_time = "10";
			CloseQuestHeader("Fra_Line_2_DelivLetter");
			DeleteAttribute(pchar, "questTemp.Out");
			DeleteAttribute(pchar, "questTemp.shore");
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_160", pchar, GetFullName(pchar)), FRANCE, 5, 1);
		break;
		//********************** Квест №3 похищение донны Анны ************************
		case "Step_3_1":
			dialog.text = StringFromKey("fra_Governor_161", pchar);
			link.l1 = StringFromKey("fra_Governor_162", pchar);
			link.l1.go = "Step_3_2";
		break;
		case "Step_3_2":
			dialog.text = StringFromKey("fra_Governor_163");
			link.l1 = StringFromKey("fra_Governor_164");
			link.l1.go = "Step_3_3";
		break;
		case "Step_3_3":
			dialog.text = StringFromKey("fra_Governor_165", pchar);
			link.l1 = StringFromKey("fra_Governor_166", pchar);
			link.l1.go = "Step_3_4";
		break;
		case "Step_3_4":
			dialog.text = StringFromKey("fra_Governor_167");
			link.l1 = StringFromKey("fra_Governor_168", pchar);
			link.l1.go = "exit";
			GiveNationLicence(SPAIN, 60);
			GiveItem2Character(pchar, "DOjeronRing");
			pchar.questTemp.State = "Fr3TakeAnna_toHavana";
			AddQuestRecord("Fra_Line_3_TakeAnna", "1");
			AddQuestUserData("Fra_Line_3_TakeAnna", "sSex", GetSexPhrase("", "а"));
			LocatorReloadEnterDisable("Havana_town", "houseS1", true);
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("Havana_waitress"), "Fra_Line");
		break;
		case "Step_3_5":
			dialog.text = StringFromKey("fra_Governor_169");
			link.l1 = StringFromKey("fra_Governor_170", pchar);
			link.l1.go = "Step_3_6";
		break;
		case "Step_3_6":
			dialog.text = StringFromKey("fra_Governor_171");
			link.l1 = StringFromKey("fra_Governor_172");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "4";
			pchar.questTemp.Waiting_time = "20";
			CloseQuestHeader("Fra_Line_3_TakeAnna");
			TakeItemFromCharacter(pchar, "letter_FraLineQ3");
			TakeNationLicence(SPAIN);
			ChangeCharacterReputation(pchar, 10);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_173", pchar, GetFullName(pchar)), FRANCE, 5, 1);
		break;
		case "Step_3_7":
			dialog.text = StringFromKey("fra_Governor_174");
			link.l1 = StringFromKey("fra_Governor_175");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "4";
			pchar.questTemp.Waiting_time = "40";
			CloseQuestHeader("Fra_Line_3_TakeAnna");
			TakeItemFromCharacter(pchar, "letter_FraLineQ3");
			TakeNationLicence(SPAIN);
			AddMoneyToCharacter(pchar, 25000);
			sld = characterFromId("AnnaDeLeiva");
			RemovePassenger(pchar, sld);
			DeleteAttribute(sld, "RebirthPhantom");
			sld.LifeDay = 0; // уберем нпс
			pchar.questTemp.AnnaIsLife = true; //но оставим флаг на пятый квест
			//==> вешаем прерывание на узнавание в таверне.
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition.l1 = "location";
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition.l1.location = "Havana_tavern";
			Pchar.quest.Fr3_AfterAnna_IKnowYou.win_condition = "Fr3_AfterAnna_IKnowYou";
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_176", pchar, GetFullName(pchar)), FRANCE, 5, 1);
		break;

		//********************** Квест №4  Солей Руаяль ************************
		case "Step_4_1":
			dialog.text = StringFromKey("fra_Governor_177", pchar);
			link.l1 = StringFromKey("fra_Governor_178");
			link.l1.go = "Step_4_2";
		break;
		case "Step_4_2":
			dialog.text = StringFromKey("fra_Governor_179");
			link.l1 = StringFromKey("fra_Governor_180");
			link.l1.go = "Step_4_3";
		break;
		case "Step_4_3":
			dialog.text = StringFromKey("fra_Governor_181", pchar);
			link.l1 = StringFromKey("fra_Governor_182", pchar);
			link.l1.go = "Step_4_4";
		break;
		case "Step_4_4":
			dialog.text = StringFromKey("fra_Governor_183");
			link.l1 = StringFromKey("fra_Governor_184");
			link.l1.go = "Step_4_5";
		break;
		case "Step_4_5":
			dialog.text = StringFromKey("fra_Governor_185", GetFullName(characterFromId("BasTer_Mayor")));
			link.l1 = StringFromKey("fra_Governor_186", pchar);
			link.l1.go = "Step_4_6";
		break;
		case "Step_4_6":
			dialog.text = StringFromKey("fra_Governor_187");
			link.l1 = StringFromKey("fra_Governor_188");
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr4SoleiRoyal_toPortMan";
			AddQuestRecord("Fra_Line_4_SoleiRoyal", "1");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_PortMan"), "Fra_Line");
		break;
		case "Step_4_7":
			dialog.text = StringFromKey("fra_Governor_189", pchar);
			link.l1 = StringFromKey("fra_Governor_190");
			link.l1.go = "Step_4_8";
		break;
		case "Step_4_8":
			dialog.text = StringFromKey("fra_Governor_191", pchar);
			link.l1 = StringFromKey("fra_Governor_192", pchar);
			link.l1.go = "Step_4_check";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause = false; // Конец линейки
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			RemoveMapQuestmark("Tortuga_town", "Fra_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_193"), FRANCE, 5, 1);
		break;
		case "Step_4_9":
			dialog.text = StringFromKey("fra_Governor_194");
			link.l1 = StringFromKey("fra_Governor_195", pchar);
			link.l1.go = "Step_4_10";
		break;
		case "Step_4_10":
			dialog.text = StringFromKey("fra_Governor_196");
			link.l1 = StringFromKey("fra_Governor_197");
			link.l1.go = "Step_4_check";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause = false; // Конец линейки
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			RemoveMapQuestmark("Tortuga_town", "Fra_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_198"), FRANCE, 5, 1);
		break;
		case "Step_4_11":
			dialog.text = StringFromKey("fra_Governor_199", pchar);
			link.l1 = StringFromKey("fra_Governor_200");
			link.l1.go = "Step_4_12";
		break;
		case "Step_4_12":
			dialog.text = StringFromKey("fra_Governor_201");
			link.l1 = StringFromKey("fra_Governor_202");
			link.l1.go = "Step_4_check";
			AddMoneyToCharacter(pchar, 28000);
			pchar.questTemp.Waiting_time = "8";
		break;
		case "Step_4_check":
			if (CheckAttribute(pchar, "questTemp.AnnaIsLife"))
			{
				pchar.questTemp.CurQuestNumber = "5";
				DeleteAttribute(pchar, "questTemp.AnnaIsLife");
			}
			else pchar.questTemp.CurQuestNumber = "6";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "empty";
			CloseQuestHeader("Fra_Line_4_SoleiRoyal");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			if (CheckAttribute(pchar, "questTemp.Waiting_time"))
			{
				AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
				AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			}
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_203", pchar), FRANCE, 5, 1);
			DialogExit();
		break;
		//********************** Квест №6. Доставка письма Олоне ************************
		case "Step_6_1":
			dialog.text = StringFromKey("fra_Governor_204");
			link.l1 = StringFromKey("fra_Governor_205");
			link.l1.go = "Step_6_2";
		break;
		case "Step_6_2":
			dialog.text = StringFromKey("fra_Governor_206");
			link.l1 = StringFromKey("fra_Governor_207");
			link.l1.go = "exit";
			LAi_group_Delete("PeaceGroup");
			pchar.questTemp.State = "Fr5Olone_toGuadeloupe";
			AddQuestRecord("Fra_Line_6_Olone", "1");
			GiveItem2Character(pchar, "letter_FraLineQ6");
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition.l1 = "location";
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition.l1.location = "Guadeloupe";
			Pchar.quest.Fr6Olone_GuadeloupeBattle.win_condition = "Fr6Olone_GuadeloupeBattle";
			//==> Олоне
			sld = GetCharacter(NPC_GenerateCharacter("Olone", "BigPirate", "man", "man", 45, FRANCE, -1, false));
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("Olone_ship"), CANNON_TYPE_CULVERINE_LBS24, 85, 80, 80);
			FantomMakeCoolFighter(sld, 45, 90, 80, "blade28", "pistol5", 130);
			sld.name = FindPersonalName("Olone_name");
			sld.lastname = FindPersonalName("Olone_lastname");
			sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			sld.RebirthPhantom = true;
			sld.greeting = "Gr_EvilPirate";
			ChangeCharacterReputation(sld, -100);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
			ChangeCharacterAddressGroup(sld, "BasTer_houseF1", "goto", "goto5");
			AddLandQuestmark_Main(sld, "Fra_Line");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		case "Step_6_3":
			dialog.text = StringFromKey("fra_Governor_208");
			link.l1 = StringFromKey("fra_Governor_209");
			link.l1.go = "Step_6_4";
		break;
		case "Step_6_4":
			dialog.text = StringFromKey("fra_Governor_210");
			link.l1 = StringFromKey("fra_Governor_211", pchar);
			link.l1.go = "Step_6_5";
		break;
		case "Step_6_5":
			dialog.text = StringFromKey("fra_Governor_212", pchar);
			link.l1 = StringFromKey("fra_Governor_213");
			link.l1.go = "Step_6_6";
		break;
		case "Step_6_6":
			dialog.text = StringFromKey("fra_Governor_214");
			link.l1 = StringFromKey("fra_Governor_215");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "7";
			pchar.questTemp.Waiting_time = "30";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", 170);
			AddCharacterExpToSkill(pchar, "Sneak", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_216", pchar), FRANCE, 5, 1);
		break;
		case "Step_6_7":
			dialog.text = StringFromKey("fra_Governor_217", pchar);
			link.l1 = StringFromKey("fra_Governor_218");
			link.l1.go = "Step_6_8";
		break;
		case "Step_6_8":
			dialog.text = StringFromKey("fra_Governor_219");
			link.l1 = StringFromKey("fra_Governor_220");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "7";
			pchar.questTemp.Waiting_time = "7";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 6);
			AddCharacterExpToSkill(pchar, "Grappling", 220);
			AddCharacterExpToSkill(pchar, "Sneak", 160);
			AddCharacterExpToSkill(pchar, "Defence", 280);
			AddCharacterExpToSkill(pchar, "Accuracy", 190);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "Fortune", 250);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_221"), FRANCE, 5, 1);
		break;
		case "Step_6_9":
			dialog.text = StringFromKey("fra_Governor_222");
			link.l1 = StringFromKey("fra_Governor_223", pchar);
			link.l1.go = "Step_6_10";
		break;
		case "Step_6_10":
			dialog.text = StringFromKey("fra_Governor_224", pchar);
			link.l1 = StringFromKey("fra_Governor_225");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "7";
			pchar.questTemp.Waiting_time = "15";
			CloseQuestHeader("Fra_Line_6_Olone");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 2);
			AddCharacterExpToSkill(pchar, "Sneak", 190);
			AddCharacterExpToSkill(pchar, "Defence", 150);
			AddCharacterExpToSkill(pchar, "Accuracy", 220);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
		break;
		//********************** Квест №7. Вызволение из тюрьмы Рока Бральзильца ************************
		case "Step_7_1":
			dialog.text = StringFromKey("fra_Governor_226");
			link.l1 = StringFromKey("fra_Governor_227");
			link.l1.go = "Step_7_2";
		break;
		case "Step_7_2":
			dialog.text = StringFromKey("fra_Governor_228");
			link.l1 = StringFromKey("fra_Governor_229");
			link.l1.go = "Step_7_3";
		break;
		case "Step_7_3":
			dialog.text = StringFromKey("fra_Governor_230");
			link.l1 = StringFromKey("fra_Governor_231");
			link.l1.go = "Step_7_4";
		break;
		case "Step_7_4":
			dialog.text = StringFromKey("fra_Governor_232");
			link.l1 = StringFromKey("fra_Governor_233");
			link.l1.go = "Step_7_5";
		break;
		case "Step_7_5":
			dialog.text = StringFromKey("fra_Governor_234");
			link.l1 = StringFromKey("fra_Governor_235");
			link.l1.go = "exit";
			LAi_group_Delete("PeaceGroup");
			GiveNationLicence(SPAIN, 20);
			SetNationRelation2MainCharacter(SPAIN, RELATION_NEUTRAL);
			pchar.questTemp.State = "Fr7RockBras_toSeekPlace";
			AddQuestRecord("Fra_Line_7_RockBras", "1");
			SaveCurrentQuestDateParam("questTemp");
			//==> Бразильца - в инквизицию. 
			sld = GetCharacter(NPC_GenerateCharacter("RockBrasilian", "Roche", "man", "man", 30, PIRATE, -1, false));
			FantomMakeCoolFighter(sld, 30, 90, 90, "", "", 80);
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			sld.RebirthPhantom = true;
			sld.name = FindPersonalName("RockBrasilian_name");
			sld.lastname = FindPersonalName("RockBrasilian_lastname");
			LAi_LoginInCaptureTown(sld, true);
			LAi_NoRebirthEnable(sld);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetGroundSitType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
			ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "prison", "prison9");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(sld, "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("Santiago_Priest"), "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("Beliz_tavernkeeper"), "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("Havana_tavernkeeper"), "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("SantoDomingo_tavernkeeper"), "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("Santiago_tavernkeeper"), "Fra_Line");
		break;
		case "Step_7_6":
			dialog.text = StringFromKey("fra_Governor_236", pchar, GetAddress_Form(NPChar));
			link.l1 = StringFromKey("fra_Governor_237");
			link.l1.go = "Step_7_exit";
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_238", pchar, GetFullName(pchar)), FRANCE, 5, 1);
			pchar.questTemp.Waiting_time = "35";
		break;
		case "Step_7_7":
			dialog.text = StringFromKey("fra_Governor_239");
			link.l1 = StringFromKey("fra_Governor_240");
			link.l1.go = "Step_7_exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 100);
			AddCharacterExpToSkill(pchar, "Defence", 100);
			AddCharacterExpToSkill(pchar, "Cannons", 100);
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_241", pchar, GetFullName(pchar)), FRANCE, 5, 1);
			pchar.questTemp.Waiting_time = "15";
		break;
		case "Step_7_exit":
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "8";
			CloseQuestHeader("Fra_Line_7_RockBras");
			TakeNationLicence(SPAIN);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			sld = characterFromId("RockBrasilian");
			DeleteAttribute(sld, "RebirthPhantom");
			sld.LifeDay = 0; // уберем нпс
			DialogExit();
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
		break;
		case "Step_7_8":
			dialog.text = StringFromKey("fra_Governor_242");
			link.l1 = StringFromKey("fra_Governor_243");
			link.l1.go = "Step_7_9";
		break;
		case "Step_7_9":
			dialog.text = StringFromKey("fra_Governor_244");
			link.l1 = StringFromKey("fra_Governor_245");
			link.l1.go = "Step_7_Rock";
			AddMoneyToCharacter(pchar, 30000);
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "8";
			CloseQuestHeader("Fra_Line_7_RockBras");
			TakeNationLicence(SPAIN);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_246", pchar, GetFullName(pchar)), FRANCE, 5, 1);
		break;
		case "Step_7_Rock":
			sld = characterFromId("RockBrasilian");
			RemovePassenger(PChar, sld);
			LAi_SetActorType(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			DialogExit();
		break;
		//********************** Квест №8. Встреча с тремя корсарами ************************
		case "Step_8_1":
			dialog.text = StringFromKey("fra_Governor_247");
			link.l1 = StringFromKey("fra_Governor_248");
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr8ThreeCorsairs_toBonrepo";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "1");
			//==> маркиз Бонрепо.
			sld = GetCharacter(NPC_GenerateCharacter("Bonrepo", "huber_fra", "man", "man", 20, FRANCE, -1, false));
			sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
			sld.name = FindPersonalName("Bonrepo_name");
			sld.lastname = FindPersonalName("Bonrepo_lastname");
			sld.greeting = "Gr_QuestMan";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "BasTer_townhall", "goto", "governor1");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(sld, "Fra_Line");
		break;
		case "Step_8_2":
			dialog.text = StringFromKey("fra_Governor_249");
			link.l1 = StringFromKey("fra_Governor_250");
			link.l1.go = "Step_8_3";
		break;
		case "Step_8_3":
			dialog.text = StringFromKey("fra_Governor_251");
			link.l1 = StringFromKey("fra_Governor_252", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "12";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "9";
			CloseQuestHeader("Fra_Line_8_ThreeCorsairs");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 5);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", -100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_253", pchar, GetMainCharacterNameDat()), FRANCE, 5, 1);
		break;
		//********************** Квест №9. Отбить нападение на Порт-о-Принс ************************
		case "Step_9_1":
			dialog.text = StringFromKey("fra_Governor_254", pchar);
			link.l1 = StringFromKey("fra_Governor_255", pchar);
			link.l1.go = "Step_9_11";
		break;
		case "Step_9_11":
			dialog.text = StringFromKey("fra_Governor_256");
			link.l1 = StringFromKey("fra_Governor_257");
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr9GuardPP_toPortPax";
			AddQuestRecord("Fra_Line_9_GuardPortPax", "1");
			sld = GetCharacter(NPC_GenerateCharacter("SoleiRoyalCaptain", "navy_off_fra_5", "man", "man", 52, FRANCE, -1, true));
			sld.Ship.Type = CreateBaseShip(SHIP_SOLEYRU);
			sld.Ship.Name = FindPersonalName("SoleiRoyalCaptain_mapEnc");
			SetBaseShipData(sld);
			ResetShipCannonsDamages(sld);
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");
			FantomMakeCoolFighter(sld, 55, 80, 70, BLADE_LONG, "pistol3", 100);
			sld.CompanionEnemyEnable = false;
			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			SetCompanionIndex(pchar, -1, sti(sld.index));
			SetShipRemovable(sld, false);
			pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
			SetTimerCondition("Fr9GuardPP_Late", 0, 0, 5, false);
			Pchar.quest.Fr9GuardPP_Fight.win_condition.l1 = "location";
			Pchar.quest.Fr9GuardPP_Fight.win_condition.l1.location = "Hispaniola2";
			Pchar.quest.Fr9GuardPP_Fight.win_condition = "Fr9GuardPP_Fight";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		case "Step_9_2":
			dialog.text = StringFromKey("fra_Governor_258", pchar);
			link.l1 = StringFromKey("fra_Governor_259");
			link.l1.go = "Step_9_3";
		break;
		case "Step_9_3":
			dialog.text = StringFromKey("fra_Governor_260", pchar);
			link.l1 = StringFromKey("fra_Governor_261", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "18";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "10";
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_262", pchar, GetFullName(pchar)), FRANCE, 5, 1);
		break;
		case "Step_9_4":
			dialog.text = StringFromKey("fra_Governor_263");
			link.l1 = StringFromKey("fra_Governor_264", pchar);
			link.l1.go = "Step_9_5";
		break;
		case "Step_9_5":
			dialog.text = StringFromKey("fra_Governor_265", pchar);
			link.l1 = StringFromKey("fra_Governor_266", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause = false; // Конец линейки
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			RemoveMapQuestmark("Tortuga_town", "Fra_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_267"), FRANCE, 5, 1);
		break;
		case "Step_9_6":
			dialog.text = StringFromKey("fra_Governor_268", pchar);
			link.l1 = StringFromKey("fra_Governor_269");
			link.l1.go = "exit";
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause = false; // Конец линейки
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			RemoveMapQuestmark("Tortuga_town", "Fra_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_270"), FRANCE, 5, 1);
		break;
		case "Step_9_7":
			dialog.text = StringFromKey("fra_Governor_271", pchar);
			link.l1 = StringFromKey("fra_Governor_272");
			link.l1.go = "exit";
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			sld.LifeDay = 0;
			pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			bWorldAlivePause = false; // Конец линейки
			CloseQuestHeader("Fra_Line_9_GuardPortPax");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -200);
			AddCharacterExpToSkill(pchar, "FencingLight", -230);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -230);
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			RemoveMapQuestmark("Tortuga_town", "Fra_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_273"), FRANCE, 5, 1);
		break;
		//********************** Квест №10. Захват Санто-Доминго ************************
		case "Step_10_1":
			dialog.text = StringFromKey("fra_Governor_274");
			link.l1 = StringFromKey("fra_Governor_275");
			link.l1.go = "Step_10_2";
		break;
		case "Step_10_2":
			dialog.text = StringFromKey("fra_Governor_276", pchar);
			link.l1 = StringFromKey("fra_Governor_277");
			link.l1.go = "Step_10_3";
		break;
		case "Step_10_3":
			dialog.text = StringFromKey("fra_Governor_278");
			link.l1 = StringFromKey("fra_Governor_279");
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr10OccupySD_toSantoDomingo";
			AddQuestRecord("Fra_Line_10_OccupySantoDomingo", "1");
			CloseQuestHeader("Fra_Line_12_EndOfWar");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			characters[GetCharacterIndex("SantoDomingo_Mayor")].dialog.captureNode = "FraLine10Quest_OccupySD"; //капитулянтская нода мэра
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("SantoDomingo_Mayor"), "Fra_Line", "StateLines_CaptureCity_QuestMarkCondition");
		break;
		case "Step_10_4":
			dialog.text = StringFromKey("fra_Governor_280");
			link.l1 = StringFromKey("fra_Governor_281");
			link.l1.go = "Step_10_5";
		break;
		case "Step_10_5":
			dialog.text = StringFromKey("fra_Governor_282");
			link.l1 = StringFromKey("fra_Governor_283");
			link.l1.go = "exit";
			CloseQuestHeader("Fra_Line_10_OccupySantoDomingo");
			pchar.questTemp.State = "QuestLineBreake";
			CloseQuestHeader("Fra_Line_12_EndOfWar");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			bWorldAlivePause = false; // Конец линейки
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "FencingLight", -130);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -130);
			AddCharacterExpToSkill(pchar, "Fencing", -130);
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			RemoveMapQuestmark("Tortuga_town", "Fra_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_284"), FRANCE, 5, 1);
		break;
		case "Step_10_6":
			dialog.text = StringFromKey("fra_Governor_285", pchar);
			link.l1 = StringFromKey("fra_Governor_286");
			link.l1.go = "Step_10_7";
		break;
		case "Step_10_7":
			dialog.text = StringFromKey("fra_Governor_287", pchar);
			link.l1 = StringFromKey("fra_Governor_288");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 40000);
			pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "30";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "11";
			CloseQuestHeader("Fra_Line_10_OccupySantoDomingo");
			AddTitleNextRate(sti(NPChar.nation), 3);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 330);
			AddCharacterExpToSkill(pchar, "Fortune", 360);
			AddCharacterExpToSkill(pchar, "Accuracy", 320);
			AddCharacterExpToSkill(pchar, "Grappling", 350);
			AddCharacterExpToSkill(pchar, "Defence", 350);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_289"), FRANCE, 5, 1);
		break;
		//********************** Квест №11. Захват Санта-Каталины ************************
		case "Step_11_1":
			dialog.text = StringFromKey("fra_Governor_290", pchar);
			link.l1 = StringFromKey("fra_Governor_291");
			link.l1.go = "Step_11_2";
		break;
		case "Step_11_2":
			dialog.text = StringFromKey("fra_Governor_292");
			link.l1 = StringFromKey("fra_Governor_293", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr11OccupySC_toSantaCatalina";
			AddQuestRecord("Fra_Line_11_OccupySantaCatalina", "1");
			characters[GetCharacterIndex("SantaCatalina_Mayor")].dialog.captureNode = "FraLine11Quest_OccupySC"; //капитулянтская нода мэра
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("SantaCatalina_Mayor"), "Fra_Line", "StateLines_CaptureCity_QuestMarkCondition");
		break;
		case "Step_11_3":
			dialog.text = StringFromKey("fra_Governor_294");
			link.l1 = StringFromKey("fra_Governor_295");
			link.l1.go = "Step_11_4";
		break;
		case "Step_11_4":
			dialog.text = StringFromKey("fra_Governor_296");
			link.l1 = StringFromKey("fra_Governor_297");
			link.l1.go = "Step_11_2";
			CloseQuestHeader("Fra_Line_11_OccupySantaCatalina");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			pchar.questTemp.State = "QuestLineBreake";
			bWorldAlivePause = false; // Конец линейки
			DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //снятия перка квестового десанта
			AddCharacterExpToSkill(pchar, "Repair", -550);
			AddCharacterExpToSkill(pchar, "Pistol", -530);
			AddCharacterExpToSkill(pchar, "Fortune", -560);
			AddCharacterExpToSkill(pchar, "Accuracy", -520);
			AddCharacterExpToSkill(pchar, "Grappling", -550);
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			RemoveMapQuestmark("Tortuga_town", "Fra_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_298"), FRANCE, 5, 1);
		break;
		case "Step_11_5":
			dialog.text = StringFromKey("fra_Governor_299");
			link.l1 = StringFromKey("fra_Governor_300");
			link.l1.go = "Step_11_6";
		break;
		case "Step_11_6":
			dialog.text = StringFromKey("fra_Governor_301");
			link.l1 = StringFromKey("fra_Governor_302", pchar);
			link.l1.go = "Step_11_7";
		break;
		case "Step_11_7":
			dialog.text = StringFromKey("fra_Governor_303", pchar);
			link.l1 = StringFromKey("fra_Governor_304");
			link.l1.go = "Step_11_8";
		break;
		case "Step_11_8":
			dialog.text = StringFromKey("fra_Governor_305", pchar);
			link.l1 = StringFromKey("fra_Governor_306");
			link.l1.go = "exit";
			pchar.questTemp.State = "empty";
			pchar.questTemp.Waiting_time = "10";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "12";
			DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //снятия перка квестового десанта
			CloseQuestHeader("Fra_Line_11_OccupySantaCatalina");
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Tortuga_town", "Fra_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("fra_Governor_307"), FRANCE, 5, 1);
		break;
		//********************** Квест №12. Завершение линейки ************************
		case "Step_12_1":
			dialog.text = StringFromKey("fra_Governor_308");
			link.l1 = StringFromKey("fra_Governor_309", pchar);
			link.l1.go = "Step_12_2";
		break;
		case "Step_12_2":
			dialog.text = StringFromKey("fra_Governor_310");
			link.l1 = StringFromKey("fra_Governor_311");
			link.l1.go = "Step_12_3";
		break;
		case "Step_12_3":
			dialog.text = StringFromKey("fra_Governor_312");
			link.l1 = StringFromKey("fra_Governor_313");
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr12EndWar_toBorepo";
			AddQuestRecord("Fra_Line_12_EndOfWar", "1");
			//==> маркиз Бонрепо.
			sld = GetCharacter(NPC_GenerateCharacter("Bonrepo", "huber_fra", "man", "man", 20, FRANCE, -1, false));
			sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
			sld.name = FindPersonalName("Bonrepo_name");
			sld.lastname = FindPersonalName("Bonrepo_lastname");
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			ChangeCharacterAddressGroup(sld, "BasTer_townhall", "goto", "governor1");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(sld, "Fra_Line");
			RemoveMapQuestmark("Tortuga_town", "Fra_Line");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

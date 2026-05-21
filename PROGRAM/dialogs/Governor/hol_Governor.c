// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	ref sld;
	int i, tempQty, chComp, iShip, iBaseType;
	string tempStr;
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = StringFromKey("hol_Governor_3", RandPhraseSimple(
						StringFromKey("hol_Governor_1"),
						StringFromKey("hol_Governor_2")));
			link.l1 = StringFromKey("hol_Governor_6", RandPhraseSimple(
						StringFromKey("hol_Governor_4", pchar),
						StringFromKey("hol_Governor_5")));
			link.l1.go = "exit";
			if (pchar.questTemp.State == "Fr2Letter_toCuracao")
			{
				dialog.text = StringFromKey("hol_Governor_7");
				link.l1 = StringFromKey("hol_Governor_8");
				link.l1.go = "Step_F2_1";
			}
			if (pchar.questTemp.State == "Fr2Letter_NiceResult")
			{
				dialog.text = StringFromKey("hol_Governor_9");
				link.l1 = StringFromKey("hol_Governor_10", GetAddress_FormToNPC(NPChar));
				link.l1.go = "Step_F2_4";
			}
			if (pchar.questTemp.LSC == "toTalkStuvesant")
			{
				link.l1 = StringFromKey("hol_Governor_11");
				link.l1.go = "TizerFind";
			}
		break;

		case "work_1":  // работа на благо короны - линейка нации
		// сюда вход только с патентом, проверка выше
			dialog.text = StringFromKey("hol_Governor_15", LinkRandPhrase(
						StringFromKey("hol_Governor_12"),
						StringFromKey("hol_Governor_13"),
						StringFromKey("hol_Governor_14")));
			link.l1 = StringFromKey("hol_Governor_18", RandPhraseSimple(
						StringFromKey("hol_Governor_16"),
						StringFromKey("hol_Governor_17")));
			link.l1.go = "exit";

			switch (pchar.questTemp.State)   // что делаем в данный момент
			{
				case "empty":   // Нет взятых квестов
					if (GetQuestPastDayParam("questTemp") < sti(pchar.questTemp.Waiting_time))
					{
						dialog.text = StringFromKey("hol_Governor_22", LinkRandPhrase(
									StringFromKey("hol_Governor_19"),
									StringFromKey("hol_Governor_20"),
									StringFromKey("hol_Governor_21")));
						link.l1 = StringFromKey("hol_Governor_23");
						link.l1.go = "exit";
					}
					else
					{
						switch (pchar.questTemp.CurQuestNumber)   // Взятие квестов начиная со второго
						{
							case "2":
								dialog.text = StringFromKey("hol_Governor_24");
								link.l1 = StringFromKey("hol_Governor_25");
								link.l1.go = "Step_2_1";
							break;
							case "3":
								dialog.text = StringFromKey("hol_Governor_26");
								link.l1 = StringFromKey("hol_Governor_27");
								link.l1.go = "Step_3_1";
							break;
							case "4":
								if (CheckAttribute(pchar, "questTemp.GoodWormRusult"))
								{
									dialog.text = StringFromKey("hol_Governor_28");
									link.l1 = StringFromKey("hol_Governor_29");
									link.l1.go = "Step_4_1";
								}
								else
								{
									dialog.text = StringFromKey("hol_Governor_30");
									link.l1 = StringFromKey("hol_Governor_31");
									link.l1.go = "Step_4_1";
								}
							break;
							case "5":
								dialog.text = StringFromKey("hol_Governor_32");
								link.l1 = StringFromKey("hol_Governor_33", pchar);
								link.l1.go = "Step_5_1";
							break;
							case "6":
								dialog.text = StringFromKey("hol_Governor_34");
								link.l1 = StringFromKey("hol_Governor_35");
								link.l1.go = "Step_6_1";
							break;
							case "7":
								dialog.text = StringFromKey("hol_Governor_36");
								link.l1 = StringFromKey("hol_Governor_37", pchar);
								link.l1.go = "Step_7_1";
							break;
							case "8":
								dialog.text = StringFromKey("hol_Governor_38");
								link.l1 = StringFromKey("hol_Governor_39", pchar);
								link.l1.go = "exit";
								pchar.questTemp.State = "SeekBible_toAaron";
								AddQuestRecord("Hol_Line_8_SeekBible", "1");
								AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("", "а"));
								SaveCurrentQuestDateParam("questTemp");
								sld = characterFromId("Chumakeiro");
								LAi_SetStayTypeNoGroup(sld);
								ChangeCharacterAddressGroup(sld, "Villemstad_houseS3", "goto", "goto1");
								RemoveLandQuestmark_Main(npchar, "Hol_Line");
								AddLandQuestmark_Main(sld, "Hol_Line");
							break;
							case "9":
								dialog.text = StringFromKey("hol_Governor_40");
								link.l1 = StringFromKey("hol_Governor_41");
								link.l1.go = "Step_9_1";
							break;
							case "10":
								dialog.text = StringFromKey("hol_Governor_42", pchar.name);
								link.l1 = StringFromKey("hol_Governor_43");
								link.l1.go = "Step_10_1";
							break;
							case "11":
								dialog.text = StringFromKey("hol_Governor_44");
								link.l1 = StringFromKey("hol_Governor_45");
								link.l1.go = "Step_11_1";
							break;
							case "12":
								dialog.text = StringFromKey("hol_Governor_46");
								link.l1 = StringFromKey("hol_Governor_47");
								link.l1.go = "Step_12_1";
							break;
						}
					}
				break;

				case "":           // Квест №1, доставка главы янсенистов мистера Аарона.
					dialog.text = StringFromKey("hol_Governor_48");
					link.l1 = StringFromKey("hol_Governor_49");
					link.l1.go = "Step_1_1";
				break;
				case "SeekChumakeiro_GoToVillemstad":
					dialog.text = StringFromKey("hol_Governor_50", GetAddress_Form(NPChar));
					link.l1 = StringFromKey("hol_Governor_51");
					link.l1.go = "exit";
					pchar.questTemp.State = "empty";
					SaveCurrentQuestDateParam("questTemp");
					pchar.questTemp.CurQuestNumber = "2";
					pchar.questTemp.Waiting_time = "7";
					CloseQuestHeader("Hol_Line_1_Chumakeiro");
					AddTitleNextRate(sti(NPChar.nation), 1);
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(pchar, "Pistol", 150);
					AddCharacterExpToSkill(pchar, "Grappling", 120);
					ChangeCharacterReputation(pchar, 5);
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
					AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
					AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
					//слухи
					AddSimpleRumour(
						StringFromKey("hol_Governor_52", GetMainCharacterNameGen()), HOLLAND, 5, 1);
				break;
				case "TakeFoodCuracao_toOrangeStore":
					dialog.text = StringFromKey("hol_Governor_53");
					link.l1 = StringFromKey("hol_Governor_54");
					if (GetQuestPastDayParam("questTemp") > 60)
					{
						dialog.text = StringFromKey("hol_Governor_55");
						link.l1 = StringFromKey("hol_Governor_56", pchar);
					}
					link.l1.go = "Step_2_5";
				break;
				case "WormEnglPlans_SurrenderWorkMorgan":
					dialog.text = StringFromKey("hol_Governor_57");
					link.l1 = StringFromKey("hol_Governor_58");
					link.l1.go = "Step_3_3";
				break;
				case "WormEnglPlans_SaveOfficer":
					dialog.text = StringFromKey("hol_Governor_59");
					link.l1 = StringFromKey("hol_Governor_60");
					link.l1.go = "Step_3_3";
				break;
				case "WormEnglPlans_GoodRusultWorm":
					dialog.text = StringFromKey("hol_Governor_61");
					link.l1 = StringFromKey("hol_Governor_62");
					link.l1.go = "Step_3_7";
				break;
				case "DefenceOrange_LateRiseOrange":
					dialog.text = StringFromKey("hol_Governor_63");
					link.l1 = StringFromKey("hol_Governor_64", pchar);
					link.l1.go = "Step_4_2";
				break;
				case "DefenceOrange_DieHard":
					dialog.text = StringFromKey("hol_Governor_65");
					link.l1 = StringFromKey("hol_Governor_66", pchar);
					link.l1.go = "Step_4_2";
				break;
				case "DefenceOrange_LandingDestroyed":
					dialog.text = StringFromKey("hol_Governor_67");
					link.l1 = StringFromKey("hol_Governor_68");
					link.l1.go = "Step_4_4";
				break;
				case "DefenceOrange_SquadronDestroyed":
					dialog.text = StringFromKey("hol_Governor_69");
					link.l1 = StringFromKey("hol_Governor_70", pchar);
					link.l1.go = "Step_4_5";
				break;
				case "ThreeFleutes_DieHard":
					dialog.text = StringFromKey("hol_Governor_71");
					link.l1 = StringFromKey("hol_Governor_72");
					link.l1.go = "Step_5_3";
				break;
				case "ThreeFleutes_AllFleuts":
					dialog.text = StringFromKey("hol_Governor_73");
					link.l1 = StringFromKey("hol_Governor_74", pchar);
					link.l1.go = "Step_5_4";
				break;
				case "ThreeFleutes_LostFleuts":
					dialog.text = StringFromKey("hol_Governor_75");
					link.l1 = StringFromKey("hol_Governor_76");
					link.l1.go = "Step_5_9";
				break;
				case "RevengeMansfield_FromMorganWithResult":
					dialog.text = StringFromKey("hol_Governor_77");
					link.l1 = StringFromKey("hol_Governor_78");
					link.l1.go = "Step_6_2";
				break;
				case "DelivLettTortuga_NotFoundLetter":
					dialog.text = StringFromKey("hol_Governor_79");
					link.l1 = StringFromKey("hol_Governor_80", pchar);
					link.l1.go = "Step_7_2";
				break;
				case "DelivLettTortuga_LetterFound":
					dialog.text = StringFromKey("hol_Governor_81");
					link.l1 = StringFromKey("hol_Governor_82", pchar);
					link.l1.go = "Step_7_8";
				break;
				case "DelivLettTortuga_WaitingNews":
					if (GetQuestPastDayParam("questTemp") > 30)
					{
						dialog.text = StringFromKey("hol_Governor_83");
						link.l1 = StringFromKey("hol_Governor_84");
						link.l1.go = "Step_7_20";
					}
					else
					{
						dialog.text = StringFromKey("hol_Governor_85");
						link.l1 = StringFromKey("hol_Governor_86");
						link.l1.go = "exit";
					}
				break;
				case "SeekBible_BadResult":
					dialog.text = StringFromKey("hol_Governor_87");
					link.l1 = StringFromKey("hol_Governor_88", pchar);
					link.l1.go = "Step_8_1";
				break;
				case "SeekBible_GoodResult":
					dialog.text = StringFromKey("hol_Governor_89", pchar);
					link.l1 = StringFromKey("hol_Governor_90", pchar);
					link.l1.go = "Step_8_2";
				break;
				case "TakeThreeShips_toAbordage":
					dialog.text = StringFromKey("hol_Governor_91");
					tempQty = 0;
					for (i = 1; i <= COMPANION_MAX; i++)
					{
						chComp = GetCompanionIndex(pchar, i);
						if (chComp != -1)
						{
							sld = GetCharacter(chComp);
							iShip = sti(sld.ship.type);
							iBaseType = sti(RealShips[iShip].basetype);
							if (iBaseType == SHIP_MANOWAR)
							{
								tempQty++;
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
								pchar.questTemp.QtyShips = sti(pchar.questTemp.QtyShips) - 1;
								if (sti(pchar.questTemp.QtyShips) < 1)
									break;
							}
						}
					}
					if (tempQty == 0)
					{
						link.l1 = StringFromKey("hol_Governor_92");
						link.l1.go = "exit";
					}
					else
					{
						if (sti(pchar.questTemp.QtyShips) > 0)
						{
							if (tempQty > 1)
							{
								link.l1 = StringFromKey("hol_Governor_93", pchar, tempQty);
							}
							else
							{
								link.l1 = StringFromKey("hol_Governor_94", pchar);
							}
							link.l1.go = "Step_9_5";
							AddQuestRecord("Hol_Line_9_TakeThreeShips", "2");
							AddQuestUserData("Hol_Line_9_TakeThreeShips", "QtyTook", tempQty);
							AddQuestUserData("Hol_Line_9_TakeThreeShips", "QtyElse", pchar.questTemp.QtyShips);
						}
						else
						{
							AddQuestRecord("Hol_Line_9_TakeThreeShips", "3");
							link.l1 = StringFromKey("hol_Governor_95");
							link.l1.go = "Step_9_6";
							DeleteAttribute(pchar, "questTemp.QtyShips");
						}
						AddMoneyToCharacter(pchar, makeint(200000 * tempQty));
					}
				break;
				case "SpaAttackCuracao_GoodWork":
					dialog.text = StringFromKey("hol_Governor_96");
					link.l1 = StringFromKey("hol_Governor_97");
					link.l1.go = "Step_10_3";
				break;
				case "SpaAttackSentMartin_Late":
					dialog.text = StringFromKey("hol_Governor_98");
					link.l1 = StringFromKey("hol_Governor_99", pchar);
					link.l1.go = "Step_11_5";
				break;
				case "SpaAttackSentMartin_GoodWork":
					dialog.text = StringFromKey("hol_Governor_100");
					link.l1 = StringFromKey("hol_Governor_101", pchar);
					link.l1.go = "Step_11_8";
				break;
				case "OccupyMaracaibo_toWeWon":
					dialog.text = StringFromKey("hol_Governor_102");
					link.l1 = StringFromKey("hol_Governor_103");
					link.l1.go = "Step_12_3";
				break;
				case "QuestLineBreake":
					dialog.text = StringFromKey("hol_Governor_104");
					link.l1 = "...";
					link.l1.go = "exit";
					bWorldAlivePause = false; // Конец линейки
					RemoveLandQuestmark_Main(npchar, "Hol_Line");
					RemoveMapQuestmark("Villemstad_town", "Hol_Line");
				break;
				case "EndOfQuestLine":
					dialog.text = StringFromKey("hol_Governor_105");
					link.l1 = StringFromKey("hol_Governor_106");
					link.l1.go = "exit";
					bWorldAlivePause = false; // Конец линейки
					RemoveLandQuestmark_Main(npchar, "Hol_Line");
					RemoveMapQuestmark("Villemstad_town", "Hol_Line");
				break;
			}
		break;
		//********************** Квест №1, доставка главы янсенистов мистера Аарона. ************************
		case "Step_1_1":
			dialog.text = StringFromKey("hol_Governor_107");
			link.l1 = StringFromKey("hol_Governor_108", pchar);
			link.l1.go = "Step_1_2";
			link.l2 = StringFromKey("hol_Governor_109", pchar);
			link.l2.go = "exit";
		break;
		case "Step_1_2":
			SaveCurrentQuestDateParam("questTemp");
			// остальные линейки в сад -->
			pchar.questTemp.NationQuest = HOLLAND;
			DeleteAttribute(&colonies[FindColony("PortoBello")], "notCaptured");
			DeleteAttribute(&colonies[FindColony("Panama")], "notCaptured");
			StateLines_Begin_DelQuestMarks();
			// остальные линейки в сад <--
			pchar.questTemp.State = "SeekChumakeiro_ToAaronHouse";
			sld = GetCharacter(NPC_GenerateCharacter("Chumakeiro", "merch_4", "man", "man", 10, HOLLAND, -1, false));
			sld.name = FindPersonalName("Chumakeiro_name");
			sld.lastname = FindPersonalName("Chumakeiro_lastname");
			sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
			sld.greeting = "Gr_padre";
			LAi_SetHuberStayType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Marigo_RoomHouseF1", "goto", "goto1");
			AddQuestRecord("Hol_Line_1_Chumakeiro", "1");
			AddQuestUserData("Hol_Line_1_Chumakeiro", "sSex", GetSexPhrase("", "а"));
			Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition.l1 = "location";
			Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition.l1.location = "Marigo_houseF1";
			Pchar.quest.SeekChumakeiro_intoMarigoHouse.win_condition = "SeekChumakeiro_intoMarigoHouse";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddLandQuestmark_Main(sld, "Hol_Line");
			AddLandQuestmark_Main(characterFromID("Marigo_tavernkeeper"), "Hol_Line");
		break;
		//********************** Квест №2, закупка и доставка товара из форта Оранж. ************************
		case "Step_2_1":
			dialog.text = StringFromKey("hol_Governor_110");
			link.l1 = StringFromKey("hol_Governor_111");
			link.l1.go = "Step_2_2";
		break;
		case "Step_2_2":
			dialog.text = StringFromKey("hol_Governor_112");
			link.l1 = StringFromKey("hol_Governor_113", pchar);
			link.l1.go = "Step_2_3";
		break;
		case "Step_2_3":
			dialog.text = StringFromKey("hol_Governor_114", pchar);
			link.l1 = StringFromKey("hol_Governor_115");
			link.l1.go = "Step_2_4";
		break;
		case "Step_2_4":
			dialog.text = StringFromKey("hol_Governor_116");
			link.l1 = StringFromKey("hol_Governor_117");
			link.l1.go = "exit";
			pchar.questTemp.State = "TakeFoodCuracao_toOrangeMayor";
			AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "1");
			GiveItem2Character(pchar, "Trust_HolLineQ2");
			AddMoneyToCharacter(pchar, 17700);
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.EbonyQtyElseNeed = 400;
			pchar.questTemp.CoffeeQtyElseNeed = 400;
			pchar.questTemp.MahoganyQtyElseNeed = 400;
			pchar.questTemp.SandalQtyElseNeed = 400;
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(characterFromID("FortOrange_Mayor"), "Hol_Line");
		break;
		case "Step_2_5":
			if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) pchar.questTemp.EbonyQty = pchar.Ship.Cargo.Goods.Ebony;
			if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) pchar.questTemp.CoffeeQty = pchar.Ship.Cargo.Goods.Coffee;
			if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) pchar.questTemp.MahoganyQty = pchar.Ship.Cargo.Goods.Mahogany;
			if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) pchar.questTemp.SandalQty = pchar.Ship.Cargo.Goods.Sandal;
			for (i = 1; i <= COMPANION_MAX; i++)
			{
				chComp = GetCompanionIndex(pchar, i);
				if (chComp != -1)
				{
					sld = GetCharacter(chComp);
					if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) pchar.questTemp.EbonyQty = sti(pchar.questTemp.EbonyQty) + sti(sld.Ship.Cargo.Goods.Ebony);
					if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) pchar.questTemp.CoffeeQty = sti(pchar.questTemp.CoffeeQty) + sti(sld.Ship.Cargo.Goods.Coffee);
					if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) pchar.questTemp.MahoganyQty = sti(pchar.questTemp.MahoganyQty) + sti(sld.Ship.Cargo.Goods.Mahogany);
					if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) pchar.questTemp.SandalQty = sti(pchar.questTemp.SandalQty) + sti(sld.Ship.Cargo.Goods.Sandal);
				}
			}
			tempStr = StringFromKey("hol_Governor_118", pchar);
			tempQty = 1;
			if (CheckAttribute(pchar, "questTemp.EbonyQty"))
			{
				if (sti(pchar.questTemp.EbonyQty > 0))
				{
					tempStr = StringFromKey("hol_Governor_119", tempStr, pchar.questTemp.EbonyQty);
					tempQty = 0;
				}
			}
			if (CheckAttribute(pchar, "questTemp.CoffeeQty"))
			{
				if (sti(pchar.questTemp.CoffeeQty > 0))
				{
					tempStr = StringFromKey("hol_Governor_120", tempStr, pchar.questTemp.CoffeeQty);
					tempQty = 0;
				}
			}
			if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed"))
			{
				if (sti(pchar.questTemp.MahoganyQty > 0))
				{
					tempStr = StringFromKey("hol_Governor_121", tempStr, pchar.questTemp.MahoganyQty);
					tempQty = 0;
				}
			}
			if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
			{
				if (sti(pchar.questTemp.SandalQty > 0))
				{
					tempStr = StringFromKey("hol_Governor_122", tempStr, pchar.questTemp.SandalQty);
					tempQty = 0;
				}
			}
			dialog.text = StringFromKey("hol_Governor_123");
			link.l1 = tempStr;
			link.l1.go = "Step_2_6";
			if (tempQty)
			{
				link.l1 = StringFromKey("hol_Governor_124", pchar);
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.EbonyQty");
				DeleteAttribute(pchar, "questTemp.CoffeeQty");
				DeleteAttribute(pchar, "questTemp.MahoganyQty");
				DeleteAttribute(pchar, "questTemp.SandalQty");
			}
		break;
		case "Step_2_6":
			tempStr = StringFromKey("hol_Governor_125");
			if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed"))
			{
				HolLine2_NullGoods();
				if (sti(pchar.questTemp.EbonyQty) >= sti(pchar.questTemp.EbonyQtyElseNeed))
				{
					tempStr = StringFromKey("hol_Governor_126", tempStr);
					HolLine2_NullGoods();
					AddCharacterGoods(pchar, GOOD_EBONY, sti(pchar.questTemp.EbonyQty) - sti(pchar.questTemp.EbonyQtyElseNeed));
					DeleteAttribute(pchar, "questTemp.EbonyQtyElseNeed");
				}
				else
				{
					if (sti(pchar.questTemp.EbonyQty > 0))
					{
						tempStr = StringFromKey("hol_Governor_127", tempStr, pchar.questTemp.EbonyQty);
						pchar.questTemp.EbonyQtyElseNeed = sti(pchar.questTemp.EbonyQtyElseNeed) - sti(pchar.questTemp.EbonyQty);
						HolLine2_NullGoods();
					}
				}
			}
			if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed"))
			{
				if (sti(pchar.questTemp.CoffeeQty) >= sti(pchar.questTemp.CoffeeQtyElseNeed))
				{
					tempStr = StringFromKey("hol_Governor_128", tempStr);
					HolLine2_NullGoods();
					AddCharacterGoods(pchar, GOOD_COFFEE, sti(pchar.questTemp.CoffeeQty) - sti(pchar.questTemp.CoffeeQtyElseNeed));
					DeleteAttribute(pchar, "questTemp.CoffeeQtyElseNeed");
				}
				else
				{
					if (sti(pchar.questTemp.CoffeeQty > 0))
					{
						tempStr = StringFromKey("hol_Governor_129", tempStr, pchar.questTemp.CoffeeQty);
						pchar.questTemp.CoffeeQtyElseNeed = sti(pchar.questTemp.CoffeeQtyElseNeed) - sti(pchar.questTemp.CoffeeQty);
						HolLine2_NullGoods();
					}
				}
			}
			if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed"))
			{
				if (sti(pchar.questTemp.MahoganyQty) >= sti(pchar.questTemp.MahoganyQtyElseNeed))
				{
					tempStr = StringFromKey("hol_Governor_130", tempStr);
					HolLine2_NullGoods();
					AddCharacterGoods(pchar, GOOD_MAHOGANY, sti(pchar.questTemp.MahoganyQty) - sti(pchar.questTemp.MahoganyQtyElseNeed));
					DeleteAttribute(pchar, "questTemp.MahoganyQtyElseNeed");
				}
				else
				{
					if (sti(pchar.questTemp.MahoganyQty > 0))
					{
						tempStr = StringFromKey("hol_Governor_131", tempStr, pchar.questTemp.MahoganyQty);
						pchar.questTemp.MahoganyQtyElseNeed = sti(pchar.questTemp.MahoganyQtyElseNeed) - sti(pchar.questTemp.MahoganyQty);
						HolLine2_NullGoods();
					}
				}
			}
			if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
			{
				if (sti(pchar.questTemp.SandalQty) >= sti(pchar.questTemp.SandalQtyElseNeed))
				{
					tempStr = StringFromKey("hol_Governor_132", tempStr);
					HolLine2_NullGoods();
					AddCharacterGoods(pchar, GOOD_SANDAL, sti(pchar.questTemp.SandalQty) - sti(pchar.questTemp.SandalQtyElseNeed));
					DeleteAttribute(pchar, "questTemp.SandalQtyElseNeed");
				}
				else
				{
					if (sti(pchar.questTemp.SandalQty > 0))
					{
						tempStr = StringFromKey("hol_Governor_133", tempStr, pchar.questTemp.SandalQty);
						pchar.questTemp.SandalQtyElseNeed = sti(pchar.questTemp.SandalQtyElseNeed) - sti(pchar.questTemp.SandalQty);
						HolLine2_NullGoods();
					}
				}
			}
			DeleteAttribute(pchar, "questTemp.EbonyQty");
			DeleteAttribute(pchar, "questTemp.CoffeeQty");
			DeleteAttribute(pchar, "questTemp.MahoganyQty");
			DeleteAttribute(pchar, "questTemp.SandalQty");
			dialog.text = tempStr;
			link.l1 = StringFromKey("hol_Governor_134");
			link.l1.go = "Step_2_7";
		break;
		case "Step_2_7":
			tempStr = "";
			if (!CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed") && !CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed") && !CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed") && !CheckAttribute(pchar, "questTemp.SandalQtyElseNeed"))
			{
				if (GetQuestPastDayParam("questTemp") > 60)
				{
					dialog.text = StringFromKey("hol_Governor_135");
					link.l1 = StringFromKey("hol_Governor_136");
					link.l1.go = "Step_2_8";
				}
				else
				{
					dialog.text = StringFromKey("hol_Governor_137");
					link.l1 = StringFromKey("hol_Governor_138", pchar);
					link.l1.go = "Step_2_11";
				}
			}
			else
			{
				dialog.text = StringFromKey("hol_Governor_139");
				link.l1 = StringFromKey("hol_Governor_140");
				link.l1.go = "exit";
				AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "3");
				if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "EbonyQtyElseNeed", pchar.questTemp.EbonyQtyElseNeed);
				else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "EbonyQtyElseNeed", "выполнено");
				if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "CoffeeQtyElseNeed", pchar.questTemp.CoffeeQtyElseNeed);
				else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "CoffeeQtyElseNeed", "выполнено");
				if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "MahoganyQtyElseNeed", pchar.questTemp.MahoganyQtyElseNeed);
				else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "MahoganyQtyElseNeed", "выполнено");
				if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "SandalQtyElseNeed", pchar.questTemp.SandalQtyElseNeed);
				else AddQuestUserData("Hol_Line_2_TakeFoodCuracao", "SandalQtyElseNeed", "выполнено");
			}
		break;
		case "Step_2_8":
			dialog.text = StringFromKey("hol_Governor_141");
			link.l1 = StringFromKey("hol_Governor_142");
			link.l1.go = "Step_2_9";
		break;
		case "Step_2_9":
			dialog.text = StringFromKey("hol_Governor_143");
			link.l1 = StringFromKey("hol_Governor_144");
			link.l1.go = "Step_2_10";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.Waiting_time = "30";
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 1);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_145", pchar, GetFullName(pchar)), HOLLAND, 5, 1);
		break;
		case "Step_2_10":
			AddQuestRecord("Hol_Line_2_TakeFoodCuracao", "4");
			CloseQuestHeader("Hol_Line_2_TakeFoodCuracao");
			DeleteAttribute(pchar, "GenQuest.HL2_AgainDiscount");  //сносим дисконтные цены
			pchar.GenQuest.StoreGoods.StoreIdx = FortOrange_STORE; //восстанавливаем старые цены и кол-во
			pchar.GenQuest.StoreGoods.HL2_QtyPriceIsBack = true;
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "3";
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveLandQuestmark_Main(characterFromID("FortOrange_trader"), "Hol_Line");
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			DialogExit();
		break;
		case "Step_2_11":
			dialog.text = StringFromKey("hol_Governor_146");
			link.l1 = StringFromKey("hol_Governor_147");
			link.l1.go = "Step_2_12";
		break;
		case "Step_2_12":
			dialog.text = StringFromKey("hol_Governor_148");
			link.l1 = StringFromKey("hol_Governor_149");
			link.l1.go = "Step_2_10";
			AddMoneyToCharacter(pchar, 75000);
			pchar.questTemp.Waiting_time = "2";
			AddCharacterExpToSkill(pchar, "Sneak", 150);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "FencingLight", 150);
			AddCharacterExpToSkill(pchar, "Fencing", 150);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 2);
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_150", pchar, GetFullName(pchar)), HOLLAND, 5, 1);
		break;
		//********************** Квест №3, Узнать о планах англичан в связи с торговой войной ************************
		case "Step_3_1":
			dialog.text = StringFromKey("hol_Governor_151");
			link.l1 = StringFromKey("hol_Governor_152");
			link.l1.go = "Step_3_2";
		break;
		case "Step_3_2":
			dialog.text = StringFromKey("hol_Governor_153");
			link.l1 = StringFromKey("hol_Governor_154", pchar);
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "WormEnglPlans_toMansfield";
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "1");
			GiveItem2Character(pchar, "letter_HolLineQ3");
			//HardCoffee ref Mansfields's dialogue
			pchar.QuestTemp.HolLine_Mansfield_task = "WormEngPlans";
			//QuestSetCurrentNode("Edward Mansfield", "HolLine3_WormEngPlans");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(characterFromID("Edward Mansfield"), "Hol_Line");
		break;
		case "Step_3_3":
			dialog.text = StringFromKey("hol_Governor_155");
			link.l1 = StringFromKey("hol_Governor_156");
			link.l1.go = "Step_3_4";
		break;
		case "Step_3_4":
			dialog.text = StringFromKey("hol_Governor_157");
			link.l1 = StringFromKey("hol_Governor_158");
			link.l1.go = "Step_3_5";
		break;
		case "Step_3_5":
			dialog.text = StringFromKey("hol_Governor_159");
			link.l1 = StringFromKey("hol_Governor_160");
			link.l1.go = "Step_3_6";
		break;
		case "Step_3_6":
			dialog.text = StringFromKey("hol_Governor_161");
			link.l1 = StringFromKey("hol_Governor_162");
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "5");
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex1", GetSexPhrase(StringFromKey("SexPhrase_1"), StringFromKey("SexPhrase_2")));
			CloseQuestHeader("Hol_Line_3_WormEnglishPlans");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "4";
			pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sneak", -100);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			RemoveLandQuestmarkToFantoms_Main("JailOff", "Hol_Line");
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_163", pchar, GetFullName(pchar)), HOLLAND, 5, 1);
		break;
		case "Step_3_7":
			dialog.text = StringFromKey("hol_Governor_164");
			link.l1 = StringFromKey("hol_Governor_165");
			link.l1.go = "exit";
			CloseQuestHeader("Hol_Line_3_WormEnglishPlans");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "4";
			pchar.questTemp.Waiting_time = "3";
			pchar.questTemp.GoodWormRusult = true;
			AddMoneyToCharacter(pchar, 50000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sailing", 150);
			AddCharacterExpToSkill(pchar, "Repair", 250);
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_166", pchar, GetFullName(pchar)), HOLLAND, 5, 1);
		break;
		//********************** Квест №4, Защитить форт Оранж ************************
		case "Step_4_1":
			dialog.text = StringFromKey("hol_Governor_167");
			if (CheckAttribute(pchar, "questTemp.GoodWormRusult"))
			{
				link.l1 = StringFromKey("hol_Governor_168", pchar);
			}
			else
			{
				link.l1 = StringFromKey("hol_Governor_169", pchar);
			}
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.GoodWormRusult");
			AddQuestRecord("Hol_Line_4_DefenceOrange", "1");
			AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex", GetSexPhrase("", "а"));
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "DefenceOrange_toFortOrange";
			Pchar.quest.DefenceOrange_FightNearJamaica.win_condition.l1 = "location";
			Pchar.quest.DefenceOrange_FightNearJamaica.win_condition.l1.location = "Jamaica";
			Pchar.quest.DefenceOrange_FightNearJamaica.win_condition = "DefenceOrange_FightNearJamaica";
			locations[FindLocation("Shore35")].DisableEncounters = true;
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
		case "Step_4_2":
			dialog.text = StringFromKey("hol_Governor_170");
			link.l1 = StringFromKey("hol_Governor_171", pchar);
			link.l1.go = "Step_4_3";
		break;
		case "Step_4_3":
			dialog.text = StringFromKey("hol_Governor_172");
			link.l1 = StringFromKey("hol_Governor_173");
			link.l1.go = "exit";
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");
			//<-- огонь и пламень
			DeleteAttribute(&locations[FindLocation("Shore35")], "DisableEncounters"); //энкаутеры вернём
			CloseQuestHeader("Hol_Line_4_DefenceOrange");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "5";
			pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_174"), HOLLAND, 5, 1);
		break;
		case "Step_4_4":
			dialog.text = StringFromKey("hol_Governor_175");
			link.l1 = StringFromKey("hol_Governor_176");
			link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddMoneyToCharacter(pchar, 100000);
			CloseQuestHeader("Hol_Line_4_DefenceOrange");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "5";
			pchar.questTemp.Waiting_time = "5";
			//==> на всякий случай дублируем снятие восторгов.
			QuestSetCurrentNode("FortOrange_Mayor", "First time");
			QuestSetCurrentNode("FortOrange_waitress", "First time");
			QuestSetCurrentNode("FortOrange_tavernkeeper", "First time");
			QuestSetCurrentNode("FortOrange_trader", "First time");
			DeleteAttribute(&locations[FindLocation("Shore35")], "DisableEncounters"); //энкаутеры вернём
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_177"), HOLLAND, 5, 1);
		break;
		case "Step_4_5":
			dialog.text = StringFromKey("hol_Governor_178");
			link.l1 = StringFromKey("hol_Governor_179");
			link.l1.go = "Step_4_6";
		break;
		case "Step_4_6":
			dialog.text = StringFromKey("hol_Governor_180");
			link.l1 = StringFromKey("hol_Governor_181", pchar);
			link.l1.go = "exit";
			//--> огонь и пламень убираем
			DeleteAttribute(&locations[FindLocation("FortOrange_town")], "hidden_effects");
			DeleteAttribute(&locations[FindLocation("FortOrange_ExitTown")], "hidden_effects");
			//<-- огонь и пламень
			DeleteAttribute(&locations[FindLocation("Shore35")], "DisableEncounters"); //энкаутеры вернём
			CloseQuestHeader("Hol_Line_4_DefenceOrange");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "5";
			pchar.questTemp.Waiting_time = "15";
			ChangeCharacterReputation(pchar, -4);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Grappling", -150);
			AddCharacterExpToSkill(pchar, "Defence", -150);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			Pchar.quest.DefenceOrange_FightInShore.over = "yes";
			Pchar.quest.DefenceOrange_FightInExitTown.over = "yes";
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_182"), HOLLAND, 5, 1);
		break;

		//********************** Квест №5, Сопроводить три флейта к Мэнсфилду ************************
		case "Step_5_1":
			dialog.text = StringFromKey("hol_Governor_183");
			link.l1 = StringFromKey("hol_Governor_184");
			link.l1.go = "Step_5_2";
		break;
		case "Step_5_2":
			dialog.text = StringFromKey("hol_Governor_185");
			link.l1 = StringFromKey("hol_Governor_186");
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_5_ThreeFleutes", "1");
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "ThreeFleutes_toPortMan";
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("Villemstad_PortMan"), "Hol_Line");
		break;
		case "Step_5_3":
			dialog.text = StringFromKey("hol_Governor_187", pchar);
			link.l1 = StringFromKey("hol_Governor_188");
			link.l1.go = "Step_5_10";
			pchar.questTemp.Waiting_time = "100";
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_189"), HOLLAND, 5, 1);
		break;

		case "Step_5_4":
			tempQty = sti(pchar.Ship.Cargo.Goods.Food);
			for (i = 1; i <= COMPANION_MAX; i++)
			{
				chComp = GetCompanionIndex(pchar, i);
				if (chComp != -1)
				{
					sld = GetCharacter(chComp);
					iShip = sti(sld.ship.type);
					iBaseType = sti(RealShips[iShip].basetype);
					if (iBaseType == SHIP_FLEUT) tempQty = tempQty + sti(sld.Ship.Cargo.Goods.Food); //считаем только у флейтов
				}
			}
			tempQty = tempQty / 10; //вес от кол-ва
			dialog.text = StringFromKey("hol_Governor_190");
			if (tempQty >= 7000)
			{
				link.l1 = StringFromKey("hol_Governor_191");
				link.l1.go = "Step_5_5";
			}
			else
			{
				link.l1 = StringFromKey("hol_Governor_192", pchar, tempQty);
				link.l1.go = "Step_5_8";
			}
		break;
		case "Step_5_5":
			dialog.text = StringFromKey("hol_Governor_193", pchar);
			link.l1 = StringFromKey("hol_Governor_194");
			link.l1.go = "Step_5_6";
			tempQty = sti(pchar.Ship.Cargo.Goods.Food);
			for (i = 1; i <= 3; i++)
			{
				sld = characterFromID("Captain_" + i);
				if (sld.id != "none")
				{
					tempQty = tempQty + sti(sld.Ship.Cargo.Goods.Food);
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
			}
			pchar.Ship.Cargo.Goods.Food = tempQty - 70000; //в пачке - 10 шт.
			AddMoneyToCharacter(pchar, 60000);
			pchar.questTemp.Waiting_time = "2";
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 180);
			AddCharacterExpToSkill(pchar, "Grappling", 200);
			AddCharacterExpToSkill(pchar, "Defence", 170);
			AddCharacterExpToSkill(pchar, "Cannons", 220);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
		break;
		case "Step_5_6":
			dialog.text = StringFromKey("hol_Governor_195");
			link.l1 = StringFromKey("hol_Governor_196", pchar);
			link.l1.go = "Step_5_7";
		break;
		case "Step_5_7":
			dialog.text = StringFromKey("hol_Governor_197", pchar);
			link.l1 = StringFromKey("hol_Governor_198");
			link.l1.go = "exit";
			CloseQuestHeader("Hol_Line_5_ThreeFleutes");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "6";
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
		break;
		case "Step_5_8":
			if (tempQty > 4000)
			{
				dialog.text = StringFromKey("hol_Governor_199", pchar);
				link.l1 = StringFromKey("hol_Governor_200");
				AddMoneyToCharacter(pchar, 20000);
				AddTitleNextRate(sti(NPChar.nation), 3);
			}
			else
			{
				dialog.text = StringFromKey("hol_Governor_201", pchar);
				link.l1 = StringFromKey("hol_Governor_202", pchar);
			}
			link.l1.go = "Step_5_6";
			for (i = 1; i <= 3; i++)
			{
				sld = characterFromID("Captain_" + i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
			}
			pchar.Ship.Cargo.Goods.Food = 0;
			pchar.questTemp.Waiting_time = "7";
			ChangeCharacterReputation(pchar, -5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Sailing", -250);
			AddCharacterExpToSkill(pchar, "Grappling", -250);
			AddCharacterExpToSkill(pchar, "Defence", -250);
			AddCharacterExpToSkill(pchar, "Cannons", -250);
		break;
		case "Step_5_9":
			dialog.text = StringFromKey("hol_Governor_203");
			link.l1 = StringFromKey("hol_Governor_204");
			link.l1.go = "Step_5_10";
			pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Sailing", -150);
			AddCharacterExpToSkill(pchar, "Grappling", -150);
			AddCharacterExpToSkill(pchar, "Defence", -150);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			for (i = 1; i <= COMPANION_MAX; i++)
			{
				chComp = GetCompanionIndex(pchar, i);
				if (chComp != -1)
				{
					sld = GetCharacter(chComp);
					tempStr = sld.id;
					if (HasSubStr(tempStr, "Captain_"))
					{
						RemoveCharacterCompanion(pchar, sld);
						sld.LifeDay = 0;
					}
				}
			}
		break;
		case "Step_5_10":
			dialog.text = StringFromKey("hol_Governor_205");
			link.l1 = StringFromKey("hol_Governor_206", pchar);
			link.l1.go = "Step_5_11";
		break;
		case "Step_5_11":
			dialog.text = StringFromKey("hol_Governor_207");
			link.l1 = StringFromKey("hol_Governor_208");
			link.l1.go = "exit";
			CloseQuestHeader("Hol_Line_5_ThreeFleutes");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "6";
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_209"), HOLLAND, 5, 1);
		break;
		//********************** Квест №6, узнать о планах мщения за Мэнсфилда ************************
		case "Step_6_1":
			dialog.text = StringFromKey("hol_Governor_210");
			link.l1 = StringFromKey("hol_Governor_211");
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_6_RevengeMansfield", "1");
			AddQuestUserData("Hol_Line_6_RevengeMansfield", "sSex", GetSexPhrase("ен", "на"));
			pchar.questTemp.State = "RevengeMansfield_toMorgan";
			//HardCoffee реф диалогов Моргана
			//QuestSetCurrentNode("Henry Morgan", "HolLine6_fromStuvesant");
			pchar.QuestTemp.HolLine_quests_task = "fromStuvesant";
			SaveCurrentQuestDateParam("questTemp");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(characterFromID("Henry Morgan"), "Hol_Line");
		break;
		case "Step_6_2":
			dialog.text = StringFromKey("hol_Governor_212");
			link.l1 = StringFromKey("hol_Governor_213", pchar);
			link.l1.go = "Step_6_3";
		break;
		case "Step_6_3":
			dialog.text = StringFromKey("hol_Governor_214");
			link.l1 = StringFromKey("hol_Governor_215");
			link.l1.go = "Step_6_4";
		break;
		case "Step_6_4":
			dialog.text = StringFromKey("hol_Governor_216");
			link.l1 = StringFromKey("hol_Governor_217", pchar);
			link.l1.go = "Step_6_5";
		break;
		case "Step_6_5":
			dialog.text = StringFromKey("hol_Governor_218");
			link.l1 = StringFromKey("hol_Governor_219");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			CloseQuestHeader("Hol_Line_6_RevengeMansfield");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "7";
			pchar.questTemp.Waiting_time = "4";
			AddCharacterExpToSkill(pchar, "FencingLight", 350);
			AddCharacterExpToSkill(pchar, "Fencing", 350);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 320);
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_220"), HOLLAND, 5, 1);
		break;
		//********************** Квест №7, Доставка письма д'Ожерону ************************
		case "Step_7_1":
			dialog.text = StringFromKey("hol_Governor_221");
			link.l1 = StringFromKey("hol_Governor_222");
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "1");
			pchar.questTemp.State = "DelivLettTortuga_toDOjeron";
			SaveCurrentQuestDateParam("questTemp");
			GiveItem2Character(pchar, "letter_HolLineQ7_2");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(characterFromID("fra_guber"), "Hol_Line");
		break;
		case "Step_7_2":
			dialog.text = StringFromKey("hol_Governor_223");
			link.l1 = StringFromKey("hol_Governor_224");
			link.l1.go = "Step_7_3";
		break;
		case "Step_7_3":
			dialog.text = StringFromKey("hol_Governor_225");
			tempStr = StringFromKey("hol_Governor_226");
			switch (pchar.questTemp.State.KingResult)
			{
				case "BrigNotFound":
					tempStr = StringFromKey("hol_Governor_227", pchar, tempStr);
				break;
				case "BrigSunk":
					tempStr = StringFromKey("hol_Governor_228", pchar, tempStr);
				break;
				case "BrigAborded":
					tempStr = StringFromKey("hol_Governor_229", pchar, tempStr);
				break;
				case "WarshipSunk":
					tempStr = StringFromKey("hol_Governor_230", pchar, tempStr);
				break;
			}
			link.l1 = tempStr;
			link.l1.go = "Step_7_4";
		break;
		case "Step_7_4":
			dialog.text = StringFromKey("hol_Governor_231");
			link.l1 = StringFromKey("hol_Governor_232");
			link.l1.go = "Step_7_5";
		break;
		case "Step_7_5":
			dialog.text = StringFromKey("hol_Governor_233");
			link.l1 = StringFromKey("hol_Governor_234");
			link.l1.go = "Step_7_6";
		break;
		case "Step_7_6":
			dialog.text = StringFromKey("hol_Governor_235");
			link.l1 = StringFromKey("hol_Governor_236", pchar);
			link.l1.go = "Step_7_7";
		break;
		case "Step_7_7":
			dialog.text = StringFromKey("hol_Governor_237");
			link.l1 = StringFromKey("hol_Governor_238");
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.State = "DelivLettTortuga_WaitingNews";
			DeleteAttribute(pchar, "questTemp.State.KingResult");
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "HolLine_7_DelivLettTortuga_WaitingNews_QuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_239", pchar, GetFullName(pchar)), HOLLAND, 5, 1);
		break;

		case "Step_7_20":
			dialog.text = StringFromKey("hol_Governor_240");
			link.l1 = StringFromKey("hol_Governor_241");
			link.l1.go = "exit";
			CloseQuestHeader("Hol_Line_7_DelivLettTortuga");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "8";
			pchar.questTemp.Waiting_time = "40";
			ChangeCharacterReputation(pchar, -3);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -2);
			AddCharacterExpToSkill(pchar, "Repair", -170);
			AddCharacterExpToSkill(pchar, "Defence", -130);
			AddCharacterExpToSkill(pchar, "Cannons", -150);
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
		break;

		case "Step_7_8":
			dialog.text = StringFromKey("hol_Governor_242");
			link.l1 = StringFromKey("hol_Governor_243");
			link.l1.go = "Step_7_9";
		break;
		case "Step_7_9":
			dialog.text = StringFromKey("hol_Governor_244");
			link.l1 = StringFromKey("hol_Governor_245");
			link.l1.go = "Step_7_10";
		break;
		case "Step_7_10":
			dialog.text = StringFromKey("hol_Governor_246");
			link.l1 = StringFromKey("hol_Governor_247");
			link.l1.go = "Step_7_11";
		break;
		case "Step_7_11":
			dialog.text = StringFromKey("hol_Governor_248");
			link.l1 = StringFromKey("hol_Governor_249");
			link.l1.go = "Step_7_12";
			TakeItemFromCharacter(pchar, "letter_HolLineQ7_1");
		break;
		case "Step_7_12":
			dialog.text = StringFromKey("hol_Governor_250");
			link.l1 = StringFromKey("hol_Governor_251");
			link.l1.go = "Step_7_13";
		break;
		case "Step_7_13":
			dialog.text = StringFromKey("hol_Governor_252");
			link.l1 = StringFromKey("hol_Governor_253");
			link.l1.go = "exit";
			CloseQuestHeader("Hol_Line_7_DelivLettTortuga");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "8";
			pchar.questTemp.Waiting_time = "10";
			DeleteAttribute(pchar, "questTemp.State.KingResult");
			AddMoneyToCharacter(pchar, 150000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 200);
			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Cannons", 250);
			AddCharacterExpToSkill(pchar, "Accuracy", 350);
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_254", pchar, GetFullName(pchar)), HOLLAND, 5, 1);
		break;
		//********************** Квест №8, Поиски Евангелие для Аарона ************************
		case "Step_8_1":
			dialog.text = StringFromKey("hol_Governor_255");
			link.l1 = StringFromKey("hol_Governor_256");
			link.l1.go = "exit";
			CloseQuestHeader("Hol_Line_8_SeekBible");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "9";
			pchar.questTemp.Waiting_time = "30";
			ChangeCharacterReputation(pchar, -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
			AddCharacterExpToSkill(pchar, "Repair", -270);
			AddCharacterExpToSkill(pchar, "Sneak", -260);
			AddCharacterExpToSkill(pchar, "Cannons", -300);
			AddCharacterExpToSkill(pchar, "FencingLight", -270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", -230);
			AddCharacterExpToSkill(pchar, "Fencing", -250);
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_257", pchar, GetFullName(pchar)), HOLLAND, 5, 1);
		break;
		case "Step_8_2":
			dialog.text = StringFromKey("hol_Governor_258");
			link.l1 = StringFromKey("hol_Governor_259");
			link.l1.go = "Step_8_3";
		break;
		case "Step_8_3":
			dialog.text = StringFromKey("hol_Governor_260");
			link.l1 = StringFromKey("hol_Governor_261");
			link.l1.go = "exit";
			CloseQuestHeader("Hol_Line_8_SeekBible");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "9";
			pchar.questTemp.Waiting_time = "2";
			TakeItemFromCharacter(pchar, "LegransMap");
			ChangeCharacterReputation(pchar, 2);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_262", GetFullName(pchar)), HOLLAND, 5, 1);
		break;
		//********************** Квест №9, Захват линейных кораблей. ************************
		case "Step_9_1":
			dialog.text = StringFromKey("hol_Governor_263");
			link.l1 = StringFromKey("hol_Governor_264");
			link.l1.go = "Step_9_2";
		break;
		case "Step_9_2":
			dialog.text = StringFromKey("hol_Governor_265");
			link.l1 = StringFromKey("hol_Governor_266");
			link.l1.go = "Step_9_3";
		break;
		case "Step_9_3":
			dialog.text = StringFromKey("hol_Governor_267");
			link.l1 = StringFromKey("hol_Governor_268");
			link.l1.go = "Step_9_4";
		break;
		case "Step_9_4":
			dialog.text = StringFromKey("hol_Governor_269");
			link.l1 = StringFromKey("hol_Governor_270");
			link.l1.go = "exit";
			pchar.questTemp.QtyShips = 4;
			pchar.questTemp.State = "TakeThreeShips_toAbordage";
			AddQuestRecord("Hol_Line_9_TakeThreeShips", "1");
			SaveCurrentQuestDateParam("questTemp");
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "HolLine_9_TakeThreeShips_toAbordage_QuestMarkCondition");
		break;
		case "Step_9_5":
			if (sti(pchar.questTemp.QtyShips) > 1)
			{
				dialog.text = StringFromKey("hol_Governor_271", pchar.questTemp.QtyShips);
			}
			else
			{
				dialog.text = StringFromKey("hol_Governor_272");
			}
			link.l1 = StringFromKey("hol_Governor_273");
			link.l1.go = "exit";
			SetCurrentQuestMark(npchar); // обновим метку
		break;
		case "Step_9_6":
			dialog.text = StringFromKey("hol_Governor_274");
			link.l1 = StringFromKey("hol_Governor_275");
			link.l1.go = "Step_9_7";
		break;
		case "Step_9_7":
			dialog.text = StringFromKey("hol_Governor_276");
			link.l1 = StringFromKey("hol_Governor_277", pchar);
			link.l1.go = "Step_9_8";
		break;
		case "Step_9_8":
			dialog.text = StringFromKey("hol_Governor_278");
			link.l1 = StringFromKey("hol_Governor_279");
			link.l1.go = "Step_9_9";
		break;
		case "Step_9_9":
			dialog.text = StringFromKey("hol_Governor_280");
			link.l1 = StringFromKey("hol_Governor_281");
			link.l1.go = "Step_9_10";
		break;
		case "Step_9_10":
			dialog.text = StringFromKey("hol_Governor_282");
			link.l1 = StringFromKey("hol_Governor_283", pchar);
			link.l1.go = "Step_9_11";
		break;
		case "Step_9_11":
			dialog.text = StringFromKey("hol_Governor_284");
			link.l1 = StringFromKey("hol_Governor_285");
			link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
			CloseQuestHeader("Hol_Line_9_TakeThreeShips");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "10";
			pchar.questTemp.Waiting_time = "20";
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Sailing", 290);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Commerce", 250);
			AddCharacterExpToSkill(pchar, "Pistol", 350);
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_286"), HOLLAND, 5, 1);
		break;
		//********************** Квест №10, Оборона Кюрасао. ************************
		case "Step_10_1":
			dialog.text = StringFromKey("hol_Governor_287");
			link.l1 = StringFromKey("hol_Governor_288");
			link.l1.go = "Step_10_2";
		break;
		case "Step_10_2":
			dialog.text = StringFromKey("hol_Governor_289");
			link.l1 = StringFromKey("hol_Governor_290");
			link.l1.go = "exit";
			pchar.questTemp.State = "SpaAttackCuracao_toBattle";
			AddQuestRecord("Hol_Line_10_SpaAttackCuracao", "1");
			AddQuestUserData("Hol_Line_10_SpaAttackCuracao", "sSex", GetSexPhrase("ен", "на"));
			SaveCurrentQuestDateParam("questTemp");
			Pchar.quest.SpaAttackCuracao_Battle.win_condition.l1 = "location";
			Pchar.quest.SpaAttackCuracao_Battle.win_condition.l1.location = "Curacao";
			Pchar.quest.SpaAttackCuracao_Battle.win_condition = "SpaAttackCuracao_Battle";
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
		case "Step_10_3":
			dialog.text = StringFromKey("hol_Governor_291");
			link.l1 = StringFromKey("hol_Governor_292");
			link.l1.go = "Step_10_4";
		break;
		case "Step_10_4":
			dialog.text = StringFromKey("hol_Governor_293");
			link.l1 = StringFromKey("hol_Governor_294");
			link.l1.go = "exit";
			AddTitleNextRate(sti(NPChar.nation), 1);
			AddMoneyToCharacter(pchar, 200000);
			CloseQuestHeader("Hol_Line_10_SpaAttackCuracao");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "11";
			pchar.questTemp.Waiting_time = "3";
			AddTitleNextRate(sti(NPChar.nation), 1);
			ChangeCharacterReputation(pchar, 7);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Repair", 270);
			AddCharacterExpToSkill(pchar, "Sneak", 260);
			AddCharacterExpToSkill(pchar, "Cannons", 300);
			AddCharacterExpToSkill(pchar, "FencingLight", 270);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 230);
			AddCharacterExpToSkill(pchar, "Fencing", 250);
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_295"), HOLLAND, 5, 5);
		break;
		//********************** Квест №11, Спасение Мариго от испанцев. ************************
		case "Step_11_1":
			dialog.text = StringFromKey("hol_Governor_296");
			link.l1 = StringFromKey("hol_Governor_297");
			link.l1.go = "Step_11_2";
		break;
		case "Step_11_2":
			dialog.text = StringFromKey("hol_Governor_298");
			link.l1 = StringFromKey("hol_Governor_299");
			link.l1.go = "Step_11_3";
		break;
		case "Step_11_3":
			dialog.text = StringFromKey("hol_Governor_300");
			link.l1 = StringFromKey("hol_Governor_301");
			link.l1.go = "Step_11_4";
		break;
		case "Step_11_4":
			dialog.text = StringFromKey("hol_Governor_302");
			link.l1 = StringFromKey("hol_Governor_303");
			link.l1.go = "exit";
			pchar.questTemp.State = "SpaAttackSentMartin_toBattle";
			AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "1");
			SaveCurrentQuestDateParam("questTemp");
			Pchar.quest.SpaAttackSentMartin_Battle.win_condition.l1 = "location";
			Pchar.quest.SpaAttackSentMartin_Battle.win_condition.l1.location = "SentMartin";
			Pchar.quest.SpaAttackSentMartin_Battle.win_condition = "SpaAttackSentMartin_Battle";
			SetTimerCondition("SpaAttackSentMartin_YouLate", 0, 0, 10, false);
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
		break;
		case "Step_11_5":
			dialog.text = StringFromKey("hol_Governor_304");
			link.l1 = StringFromKey("hol_Governor_305");
			link.l1.go = "Step_11_6";
		break;
		case "Step_11_6":
			dialog.text = StringFromKey("hol_Governor_306");
			link.l1 = StringFromKey("hol_Governor_307");
			link.l1.go = "Step_11_7";
		break;
		case "Step_11_7":
			dialog.text = StringFromKey("hol_Governor_308");
			link.l1 = StringFromKey("hol_Governor_309", pchar);
			link.l1.go = "exit";
			CloseQuestHeader("Hol_Line_11_SpaAttackSentMartin");
			pchar.questTemp.State = "empty";
			SaveCurrentQuestDateParam("questTemp");
			pchar.questTemp.CurQuestNumber = "12";
			pchar.questTemp.Waiting_time = "30";
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "StateLines_Waiting_QuestMarkCondition");
			AddMapQuestMark_Major("Villemstad_town", "Hol_Line", "StateLines_Waiting_WDMQuestMarkCondition");
		break;
		case "Step_11_8":
			dialog.text = StringFromKey("hol_Governor_310", GetFullName(pchar));
			link.l1 = StringFromKey("hol_Governor_311", pchar);
			link.l1.go = "Step_11_9";
		break;
		case "Step_11_9":
			dialog.text = StringFromKey("hol_Governor_312");
			link.l1 = StringFromKey("hol_Governor_313");
			link.l1.go = "Step_11_10";
			AddMoneyToCharacter(pchar, 200000);
			AddTitleNextRate(sti(NPChar.nation), 2);
			ChangeCharacterReputation(pchar, 6);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
			AddCharacterExpToSkill(pchar, "Pistol", 430);
			AddCharacterExpToSkill(pchar, "Fortune", 460);
			AddCharacterExpToSkill(pchar, "Accuracy", 420);
			AddCharacterExpToSkill(pchar, "Grappling", 450);
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_314"), HOLLAND, 5, 1);
		break;
		case "Step_11_10":
			dialog.text = StringFromKey("hol_Governor_315");
			link.l1 = StringFromKey("hol_Governor_316");
			link.l1.go = "Step_11_7";
		break;
		//********************** Квест №12, Захват Венесуэллы. ************************
		case "Step_12_1":
			dialog.text = StringFromKey("hol_Governor_317");
			link.l1 = StringFromKey("hol_Governor_318", pchar);
			link.l1.go = "Step_12_2";
		break;
		case "Step_12_2":
			dialog.text = StringFromKey("hol_Governor_319");
			link.l1 = StringFromKey("hol_Governor_320");
			link.l1.go = "exit";
			pchar.questTemp.State = "OccupyMaracaibo_toFight";
			AddQuestRecord("Hol_Line_12_OccupyMaracaibo", "1");
			SaveCurrentQuestDateParam("questTemp");
			characters[GetCharacterIndex("Maracaibo_Mayor")].dialog.captureNode = "HolLine12Quest_Occupy"; //капитулянтская нода мэра
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("Maracaibo_Mayor"), "Hol_Line", "StateLines_CaptureCity_QuestMarkCondition");
		break;
		case "Step_12_3":
			dialog.text = StringFromKey("hol_Governor_321");
			link.l1 = StringFromKey("hol_Governor_322");
			link.l1.go = "Step_12_4";
		break;
		case "Step_12_4":
			dialog.text = StringFromKey("hol_Governor_323", pchar);
			link.l1 = StringFromKey("hol_Governor_324");
			link.l1.go = "Step_12_5";
			AddMoneyToCharacter(pchar, 300000);
		break;
		case "Step_12_5":
			dialog.text = StringFromKey("hol_Governor_325");
			link.l1 = StringFromKey("hol_Governor_326");
			link.l1.go = "Step_12_6";
		break;
		case "Step_12_6":
			dialog.text = StringFromKey("hol_Governor_327");
			link.l1 = StringFromKey("hol_Governor_328");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			pchar.questTemp.State = "EndOfQuestLine";
			CloseQuestHeader("Hol_Line_12_OccupyMaracaibo");
			bWorldAlivePause = false; // Конец линейки
			AddTitleNextRate(sti(NPChar.nation), 4);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			AddCharacterExpToSkill(pchar, "Repair", 630);
			AddCharacterExpToSkill(pchar, "Sneak", 490);
			AddCharacterExpToSkill(pchar, "FencingLight", 530);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 530);
			AddCharacterExpToSkill(pchar, "Fencing", 530);
			AddCharacterExpToSkill(pchar, "Pistol", 530);
			AddCharacterExpToSkill(pchar, "Fortune", 660);
			AddCharacterExpToSkill(pchar, "Accuracy", 520);
			AddCharacterExpToSkill(pchar, "Grappling", 750);
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			RemoveMapQuestmark("Villemstad_town", "Hol_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("hol_Governor_329"), HOLLAND, 5, 1);
			Achievment_Set(ACH_Na_sluzhbe_Gollandii);
		break;

		//********************** Французская линейка. Квест №2, доставка письма д'Ожерона. ************************
		case "Step_F2_1":
			dialog.text = StringFromKey("hol_Governor_330");
			link.l1 = StringFromKey("hol_Governor_331", pchar);
			link.l1.go = "Step_F2_2";
			TakeItemFromCharacter(pchar, "letter_FraLineQ1");
		break;
		case "Step_F2_2":
			dialog.text = StringFromKey("hol_Governor_332", pchar);
			link.l1 = StringFromKey("hol_Governor_333", GetAddress_FormToNPC(NPChar));
			link.l1.go = "Step_F2_3";
		break;
		case "Step_F2_3":
			pchar.questTemp.State = "Fr2Letter_Arrest";
			for (i = 1; i <= 3; i++)
			{
				tempStr = "guard_hol_" + i;
				if (i == 3) tempStr = "off_hol_7"; //watch_quest_moment
				sld = GetCharacter(NPC_GenerateCharacter("Guard_" + i, tempStr, "man", "man", 30, HOLLAND, 0, true));
				sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
				FantomMakeCoolFighter(sld, 30, 70, 60, "blade34", "pistol2", 70);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1_back");
				LAi_SetWarriorType(sld);
			}
			LAi_tmpl_SetFollow(CharacterFromID("Guard_1"), sld, -1.0);
			LAi_tmpl_SetFollow(CharacterFromID("Guard_2"), sld, -1.0);
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		case "Step_F2_4":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("hol_Governor_334"),
						StringFromKey("hol_Governor_335"),
						StringFromKey("hol_Governor_336"),
						StringFromKey("hol_Governor_337"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("hol_Governor_338", UpperFirst(GetAddress_FormToNPC(NPChar))),
						StringFromKey("hol_Governor_339"),
						StringFromKey("hol_Governor_340"),
						StringFromKey("hol_Governor_341"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_F2_5", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_F2_5":
			dialog.text = StringFromKey("hol_Governor_342");
			link.l1 = StringFromKey("hol_Governor_343");
			link.l1.go = "Step_F2_6";
		break;
		case "Step_F2_6":
			dialog.text = StringFromKey("hol_Governor_344");
			link.l1 = StringFromKey("hol_Governor_345", pchar);
			link.l1.go = "Step_F2_7";
		break;
		case "Step_F2_7":
			dialog.text = StringFromKey("hol_Governor_346");
			link.l1 = StringFromKey("hol_Governor_347", pchar, GetAddress_FormToNPC(NPChar));
			link.l1.go = "Step_F2_8";
		break;
		case "Step_F2_8":
			dialog.text = StringFromKey("hol_Governor_348");
			link.l1 = StringFromKey("hol_Governor_349");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 20000);
			AddQuestRecord("Fra_Line_2_DelivLetter", "6");
			AddQuestUserData("Fra_Line_2_DelivLetter", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		// --------------------- линейка ГПК, вопрос о Тизере ---------------------
		case "TizerFind":
			dialog.text = StringFromKey("hol_Governor_350");
			link.l1 = StringFromKey("hol_Governor_351");
			link.l1.go = "TizerFind_1";
		break;
		case "TizerFind_1":
			dialog.text = StringFromKey("hol_Governor_352");
			link.l1 = StringFromKey("hol_Governor_353");
			link.l1.go = "TizerFind_2";
		break;
		case "TizerFind_2":
			dialog.text = StringFromKey("hol_Governor_354");
			link.l1 = StringFromKey("hol_Governor_355");
			link.l1.go = "TizerFind_3";
		break;
		case "TizerFind_3":
			dialog.text = StringFromKey("hol_Governor_356");
			link.l1 = StringFromKey("hol_Governor_357", pchar);
			link.l1.go = "TizerFind_4";
		break;
		case "TizerFind_4":
			dialog.text = StringFromKey("hol_Governor_358");
			link.l1 = StringFromKey("hol_Governor_359");
			link.l1.go = "TizerFind_5";
		break;
		case "TizerFind_5":
			dialog.text = StringFromKey("hol_Governor_360");
			link.l1 = StringFromKey("hol_Governor_361");
			link.l1.go = "TizerFind_6";
		break;
		case "TizerFind_6":
			dialog.text = StringFromKey("hol_Governor_362");
			link.l1 = StringFromKey("hol_Governor_363", pchar);
			link.l1.go = "TizerFind_7";
		break;
		case "TizerFind_7":
			dialog.text = StringFromKey("hol_Governor_364");
			link.l1 = StringFromKey("hol_Governor_365");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toLicencer";
			AddQuestRecord("ISS_PoorsMurder", "9");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("ISS_PoorsMurder", "sSex1", GetSexPhrase("", "а"));

			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			RemoveLandQuestMark_Main(CharacterFromId("Villemstad_tavernkeeper"), "ISS_PoorsMurder");
			AddLandQuestMarkToFantoms_Main("diplomat", "ISS_PoorsMurder", "");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

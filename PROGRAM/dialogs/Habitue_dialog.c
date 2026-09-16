#include "DIALOGS\Common_Duel.c" //navy
#include "DIALOGS\Rumours\Simple_rumors.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle;
	int DonationSize;

	// Warship 18.05.08
	int iLa_Puesta; // La puesta - это ставка по-испански

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, Diag);//homo 25/06/06
	ProcessDuelDialog(NPChar, Link, Diag); //navy

	int iEnemyDice, iPCDice;
	// boal 13.03.2004 -->
	int d1, d2, d3, d4;
	bool ok;
	// boal 13.03.2004 <--
	ref sld;

	if (npchar.quest.Meeting != LastSpeakDate())
	{
		//		npchar.quest.last_theme = rand(1); // перенос в генерацию
		//		npchar.quest.last_theme_game = rand(1);
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
		if (bBettaTestMode)
		{
			Dialog.CurrentNode = "Beta_test";
		}
	}

	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча

		case "exit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		break;

		case "Beta_test":
			dialog.text = StringFromKey("Habitue_dialog_1");
			link.l1 = StringFromKey("Habitue_dialog_2");
			link.l1.go = "Beta_test_alc";
			link.l2 = StringFromKey("Habitue_dialog_3");
			link.l2.go = "Beta_test_card";
			link.l3 = StringFromKey("Habitue_dialog_4");
			link.l3.go = "Beta_test_dice";
		break;

		case "Beta_test_alc":
			dialog.text = StringFromKey("Habitue_dialog_5");
			link.l1 = StringFromKey("Habitue_dialog_6");
			link.l1.go = "First time";
			npchar.quest.last_theme = 0;
			npchar.quest.last_theme_game = 0;
		break;

		case "Beta_test_card":
			dialog.text = StringFromKey("Habitue_dialog_7");
			link.l1 = StringFromKey("Habitue_dialog_8");
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
			npchar.quest.last_theme_game = 0;
		break;

		case "Beta_test_dice":
			dialog.text = StringFromKey("Habitue_dialog_9");
			link.l1 = StringFromKey("Habitue_dialog_10");
			link.l1.go = "First time";
			npchar.quest.last_theme = 1;
			npchar.quest.last_theme_game = 1;
		break;

		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = StringFromKey("Habitue_dialog_14", LinkRandPhrase(
							StringFromKey("Habitue_dialog_11"),
							StringFromKey("Habitue_dialog_12"),
							StringFromKey("Habitue_dialog_13", pchar)));
				link.l1 = StringFromKey("Habitue_dialog_17", RandPhraseSimple(
							StringFromKey("Habitue_dialog_15"),
							StringFromKey("Habitue_dialog_16")));
				link.l1.go = "exit";
				break;
			}

			bool ok1 = CheckCharacterPerk(pchar, "Bully") && !CheckAttribute(npchar, "habitue_notscared");
			bool ok2 = CheckAttribute(npchar, "habitue_scared");
			if (ok1 && !ok2) ok1 = idRand(npchar.id + "habitue", 1);
			if (ok1 || ok2) // если дуэлянт то каждый второй посылает куда подальше
			{
				npchar.habitue_scared = "";
				dialog.text = StringFromKey("Habitue_dialog_18", pchar);
				link.l1 = StringFromKey("Habitue_dialog_22", LinkRandPhrase(
							StringFromKey("Habitue_dialog_19"),
							StringFromKey("Habitue_dialog_20", pchar),
							StringFromKey("Habitue_dialog_21")));
				link.l1.go = "exit";
				link.l2 = StringFromKey("Habitue_dialog_23", pchar);
				link.l2.go = "talk_habitue_duel";
				break;
			}

			npchar.habitue_notscared = ""; //если хоть раз был готов выпить, то потом не начнёт бояться дуэлянта
			ok = CheckFreeSitFront(npchar); // есть куда сесть

			dialog.text = StringFromKey("Habitue_dialog_24");
			link.l1 = StringFromKey("Habitue_dialog_25", pchar);
			link.l1.go = "exit";
			if (GetGlobalTutor())
			{
				break;
			}
			if (!chrDisableReloadToLocation)
			{
				switch (npchar.quest.last_theme)
				{
					case "0": //пьяный.
						dialog.text = StringFromKey("Habitue_dialog_26", pchar);
						link.l1 = StringFromKey("Habitue_dialog_27", pchar);
						link.l1.go = "exit";
						//--> Эммануэль Пардаль
						if (CheckAttribute(pchar, "questTemp.EPL_Prologue"))
						{
							dialog.text = StringFromKey("Habitue_dialog_296");
							link.l1 = StringFromKey("Habitue_dialog_297");
							link.l1.go = "exit";
							break;
						}
						//<-- Эммануэль Пардаль

						if (makeint(pchar.money) >= 100 && ok)
						{
							link.l2 = StringFromKey("Habitue_dialog_28", pchar);
							link.l2.go = "talk_with_alchogol";
						}
						else
						{
							link.l2 = StringFromKey("Habitue_dialog_29");
							link.l2.go = "talk_with_alchogol_song";
						}
					break;

					case "1":
						if (sti(NPChar.Money) < 300)
						{
							Dialog.text = StringFromKey("Habitue_dialog_30");
							link.l1 = StringFromKey("Habitue_dialog_31");
							link.l1.go = "exit";
							break;
						}
						if (checkAttribute(npchar, "game_over"))
						{
							Dialog.text = StringFromKey("Habitue_dialog_32");
							link.l1 = StringFromKey("Habitue_dialog_33");
							link.l1.go = "exit";
							break;
						}
						if (rand(3) != 1 && ok)
						{
							switch (sti(npchar.quest.last_theme_game))
							{
								case 0 :
								// Игра в карты boal 20/05/05 -->
									if (CheckNPCQuestDate(npchar, "Card_date_begin"))
									{
										Dialog.text = StringFromKey("Habitue_dialog_36", RandPhraseSimple(
													StringFromKey("Habitue_dialog_34"),
													StringFromKey("Habitue_dialog_35")));
										link.l1 = StringFromKey("Habitue_dialog_37");
										link.l1.go = "Cards_begin";
										link.l2 = StringFromKey("Habitue_dialog_38");
										link.l2.go = "Cards_Rule";
										link.l3 = StringFromKey("Habitue_dialog_39");
										link.l3.go = "exit";
										//--> Эммануэль Пардаль
										if (CheckAttribute(pchar, "questTemp.EPL_Prologue"))
										{
											DeleteAttribute(link, "l1");
											DeleteAttribute(link, "l2");
										}
										//<-- Эммануэль Пардаль
									}
									else
									{
										Dialog.text = StringFromKey("Habitue_dialog_40");
										link.l1 = StringFromKey("Habitue_dialog_41");
										link.l1.go = "exit";
									}
								// Игра в карты boal 20/05/05 <--
								break;

								case 1:
								// кости
								// Игра в кости boal 13/07/05 -->
									if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
									{
										Dialog.text = StringFromKey("Habitue_dialog_44", RandPhraseSimple(
													StringFromKey("Habitue_dialog_42"),
													StringFromKey("Habitue_dialog_43")));
										link.l1 = StringFromKey("Habitue_dialog_45");
										link.l1.go = "Dice_begin";
										link.l2 = StringFromKey("Habitue_dialog_46");
										link.l2.go = "Dice_Rule";
										link.l3 = StringFromKey("Habitue_dialog_47");
										link.l3.go = "exit";
										//--> Эммануэль Пардаль
										if (CheckAttribute(pchar, "questTemp.EPL_Prologue"))
										{
											DeleteAttribute(link, "l1");
											DeleteAttribute(link, "l2");
										}
										//<-- Эммануэль Пардаль
									}
									else
									{
										Dialog.text = StringFromKey("Habitue_dialog_48");
										link.l1 = StringFromKey("Habitue_dialog_49");
										link.l1.go = "exit";
									}
									// Игра в кости boal 13/07/05 <--
									//navy --> Дуэли
									if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1) // && sti(NPChar.Quest.HeroLose))
									{
										link.l9 = StringFromKey("Habitue_dialog_50", RandSwear());
										link.l9.go = "outraged";
									}
								//navy <--
								break;
							} //switch
						}
						else
						{
							dialog.text = StringFromKey("Habitue_dialog_53", RandPhraseSimple(
										StringFromKey("Habitue_dialog_51"),
										StringFromKey("Habitue_dialog_52")));
							link.l1 = StringFromKey("Habitue_dialog_56", RandPhraseSimple(
										StringFromKey("Habitue_dialog_54"),
										StringFromKey("Habitue_dialog_55")));
							link.l1.go = "exit";
							link.l2 = StringFromKey("Habitue_dialog_59", RandPhraseSimple(
										StringFromKey("Habitue_dialog_57"),
										StringFromKey("Habitue_dialog_58")));
							link.l2.go = "tavern_keeper";
							//--> Эммануэль Пардаль
							if (CheckAttribute(pchar, "questTemp.EPL_Prologue"))
							{
								DeleteAttribute(link, "l2");
							}
							//<-- Эммануэль Пардаль
						}
					break;
				}
			}
			Diag.TempNode = "First time";
		break;

		case "talk_habitue_duel":
			dialog.text = StringFromKey("Habitue_dialog_60", pchar);
			link.l1 = StringFromKey("Habitue_dialog_61");
			link.l1.go = "exit";
		break;

		// карты -->
		case "Cards_Rule":
			dialog.text = GlobalStringConvert("CARDS_RULE");
			link.l1 = StringFromKey("Habitue_dialog_62");
			link.l1.go = "Cards_begin";
			link.l3 = StringFromKey("Habitue_dialog_63");
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Diag.tempnode = "Cards_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Cards_Node":
			Diag.tempNode = "first time";

			Dialog.text = StringFromKey("Habitue_dialog_64");
			link.l1 = "100";
			Link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l3 = StringFromKey("Habitue_dialog_65");
			link.l3.go = "exit_sit";
		break;

		case "Cards_Node_2":
			iLa_Puesta = sti(StrReplaceAll(dialogEditStrings[1], " ", ""));
			if (!CheckCardsGameSmallRate())
			{
				dialog.text = StringFromKey("Habitue_dialog_66");
				link.l1 = StringFromKey("Habitue_dialog_67");
				link.l1.go = "exit_sit";
				break;
			}

			if (sti(PCHar.Money) < sti(iLa_Puesta) * 3)
			{
				dialog.text = StringFromKey("Habitue_dialog_68", pchar);
				link.l1 = StringFromKey("Habitue_dialog_69");
				link.l1.go = "exit_sit";
				break;
			}

			if (sti(NPChar.Money) < sti(iLa_Puesta) * 3)
			{
				dialog.text = StringFromKey("Habitue_dialog_70");
				link.l1 = StringFromKey("Habitue_dialog_71");
				link.l1.go = "Cards_begin_2";
				link.l2 = StringFromKey("Habitue_dialog_72", pchar);
				link.l2.go = "exit_sit";
				break;
			}
			else
			{
				if (sti(iLa_Puesta) < 50)
				{
					dialog.text = StringFromKey("Habitue_dialog_73", FindMoneyString(sti(iLa_Puesta)));
					link.l1 = StringFromKey("Habitue_dialog_74");
					link.l1.go = "Cards_begin_2";
					link.l2 = StringFromKey("Habitue_dialog_75", pchar);
					link.l2.go = "exit_sit";
					break;
				}

				if (sti(iLa_Puesta) > 1000)
				{
					dialog.text = StringFromKey("Habitue_dialog_76");
					link.l1 = StringFromKey("Habitue_dialog_77");
					link.l1.go = "Cards_begin_2";
					link.l2 = StringFromKey("Habitue_dialog_78", pchar);
					link.l2.go = "exit_sit";
					break;
				}
				dialog.text = StringFromKey("Habitue_dialog_79", iLa_Puesta);
				link.l1 = StringFromKey("Habitue_dialog_80");
				link.l1.go = "Cards_begin_go";
				pchar.GenQuest.Cards.npcharIdx = npchar.index;
				pchar.GenQuest.Cards.iRate = sti(iLa_Puesta);
				pchar.GenQuest.Cards.SitType = true;
			}
		break;

		case "Cards_begin_2":
			dialog.text = StringFromKey("Habitue_dialog_81");
			link.l1 = "100";
			Link.l1.edit = 1;
			link.l1.go = "Cards_Node_2";
			link.l2 = StringFromKey("Habitue_dialog_82");
			link.l2.go = "exit_sit";
		break;

		case "Cards_begin_go":
		// анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		// карты <--

		// КОСТИ -->
		case "Dice_Rule":
			dialog.text = GlobalStringConvert("DICE_RULE");
			link.l1 = StringFromKey("Habitue_dialog_83");
			link.l1.go = "Dice_begin";
			link.l3 = StringFromKey("Habitue_dialog_84");
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Diag.tempnode = "Dice_Node";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "Dice_Node":
			Diag.tempNode = "first time";

			Dialog.text = StringFromKey("Habitue_dialog_85");
			link.l1 = "50";
			Link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			//	link.l2 = "Давай по 200 золотых за кубик";
			//	link.l2.go = "Dice_Node_500";
			link.l3 = StringFromKey("Habitue_dialog_86");
			link.l3.go = "exit_sit";
		break;

		case "Dice_Node_2":
			iLa_Puesta = sti(StrReplaceAll(dialogEditStrings[1], " ", ""));
			if (!CheckDiceGameSmallRate())
			{
				dialog.text = StringFromKey("Habitue_dialog_87");
				link.l1 = StringFromKey("Habitue_dialog_88");
				link.l1.go = "exit_sit";
				break;
			}

			if (sti(pchar.Money) < sti(iLa_Puesta) * 6)
			{
				dialog.text = StringFromKey("Habitue_dialog_89", pchar);
				link.l1 = StringFromKey("Habitue_dialog_90");
				link.l1.go = "exit_sit";
				break;
			}

			if (sti(npchar.Money) < sti(iLa_Puesta) * 6)
			{
				dialog.text = StringFromKey("Habitue_dialog_91");
				link.l1 = StringFromKey("Habitue_dialog_92");
				link.l1.go = "Dice_begin_2";
				link.l2 = StringFromKey("Habitue_dialog_93", pchar);
				link.l2.go = "exit_sit";
				break;
			}
			else
			{
				if (sti(iLa_Puesta) < 50)
				{
					dialog.text = StringFromKey("Habitue_dialog_94", FindMoneyString(sti(iLa_Puesta)));
					link.l1 = StringFromKey("Habitue_dialog_95");
					link.l1.go = "Dice_begin_2";
					link.l2 = StringFromKey("Habitue_dialog_96", pchar);
					link.l2.go = "exit_sit";
					break;
				}

				if (sti(iLa_Puesta) > 1000)
				{
					dialog.text = StringFromKey("Habitue_dialog_97");
					link.l1 = StringFromKey("Habitue_dialog_98");
					link.l1.go = "Dice_begin_2";
					link.l2 = StringFromKey("Habitue_dialog_99", pchar);
					link.l2.go = "exit_sit";
					break;
				}
				dialog.text = StringFromKey("Habitue_dialog_100", iLa_Puesta);
				link.l1 = StringFromKey("Habitue_dialog_101");
				link.l1.go = "Dice_begin_go";
				pchar.GenQuest.Dice.npcharIdx = npchar.index;
				pchar.GenQuest.Dice.iRate = sti(iLa_Puesta);
				pchar.GenQuest.Dice.SitType = true;
			}
		break;

		case "Dice_begin_2":
			dialog.text = StringFromKey("Habitue_dialog_102");
			link.l1 = "50";
			Link.l1.edit = 1;
			link.l1.go = "Dice_Node_2";
			link.l2 = StringFromKey("Habitue_dialog_103");
			link.l2.go = "exit_sit";
		break;

		/*	case "Dice_Node_500":
				if (!CheckDiceGameSmallRate())
				{
					dialog.text = "О тебе ходит слава непревзойдённого шулера. Я не буду с тобой играть в кости вообще.";
					link.l1 = "Все врут! Ну и не нужно.";
					link.l1.go = "exit_sit";
					break;
				}
				if (!CheckDiceGameBigRate())
				{
					dialog.text = "Я слышал, что ты очень хорошо играешь. Я не буду играть с тобой по таким большим ставкам.";
					link.l1 = "Давай по более низким?";
					link.l1.go = "Dice_Node_100";
					link.l2 = "Ну и не нужно.";
					link.l2.go = "exit_sit";
					break;
				}

				if (sti(pchar.Money) < 1500)
				{
					dialog.text = "Да ты, "+ GetSexPhrase("дружок","дорогуша") +", на мели. Приходи, когда разбогатеешь.";
					link.l1 = "Ладно.";
					link.l1.go = "exit_sit";
					break;
				}
				if (sti(npchar.Money) < 1500)
				{
					dialog.text = "Я уже проигрался для таких больших ставок, явно не мой день.";
					link.l1 = "Жаль.";
					link.l1.go = "exit_sit";
					break;
				}
				dialog.text = "Хорошо, играем по 200 монет.";
				link.l1 = "Поехали!";
				link.l1.go = "Dice_begin_go";
				pchar.GenQuest.Dice.npcharIdx = npchar.index;
				pchar.GenQuest.Dice.iRate     = 200;
				pchar.GenQuest.Dice.SitType   = true;
			break;*/

		case "Dice_begin_go":
		// анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			LaunchDiceGame();
		break;
		// КОСТИ <--
		// homo 01/08/06 to_del
		// наводка на товар - перенес в слухи
		//case "Find_Merchant_1":
		//if (pchar.GenQuest.Find_Merchant.lastspeak_date == LastSpeakDate())
		//{
		//    dialog.text = "А че это ты интересуешся? И-ик! Уж не пират ли ты?";
		//	link.l1 = "Забудь! Тебе послышалось.";
		//		link.l1.go = "exit_sit";
		/*}    // TODO
		else
		{
			pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
			MerchantOnMap();
			sld = characterFromID("Quest_Merchant");
			dialog.text = "Слыхал я, один " + RandPhraseSimple("торгаш", "купец") + " на корабле '" + sld.Ship.Name +
						  "' под флагом " + NationNameGenitive(sti(sld.nation)) + " везет полный трюм " + GetGoodsNameAlt(sti(sld.QuestGoodsIdx)) + ".";
			link.l1 = "Спасибо, браток! Пора мне в море, засидел"+ GetSexPhrase("ся","ась") +" я тут.";
			link.l1.go = "exit_sit";
		} */
		//break;
		//////  1
		case "GhostShip_Speak_1":
			npchar.GhostShip_Speak_Yet = true;
			pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();
			dialog.text = StringFromKey("Habitue_dialog_104");
			link.l1 = StringFromKey("Habitue_dialog_105");
			link.l1.go = "GhostShip_Speak_1_2";
		break;

		case "GhostShip_Speak_1_2":
			dialog.text = StringFromKey("Habitue_dialog_106");
			link.l1 = StringFromKey("Habitue_dialog_107");
			link.l1.go = "GhostShip_Speak_1_3";
		break;

		case "GhostShip_Speak_1_3":
			dialog.text = StringFromKey("Habitue_dialog_108", pchar);
			link.l1 = StringFromKey("Habitue_dialog_109");
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "1";
			AddQuestRecord("GhostShipQuest", "1");
			SetCurrentQuestMarkToFantoms("habitue");
		break;
		//////  2
		case "GhostShip_Speak_2":
			npchar.GhostShip_Speak_Yet = true;
			pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();
			dialog.text = StringFromKey("Habitue_dialog_110");
			link.l1 = StringFromKey("Habitue_dialog_111");
			link.l1.go = "GhostShip_Speak_2_2";
		break;

		case "GhostShip_Speak_2_2":
			dialog.text = StringFromKey("Habitue_dialog_112");
			link.l1 = StringFromKey("Habitue_dialog_113");
			link.l1.go = "GhostShip_Speak_2_3";
		break;

		case "GhostShip_Speak_2_3":
			dialog.text = StringFromKey("Habitue_dialog_114");
			link.l1 = StringFromKey("Habitue_dialog_115");
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "2";
			AddQuestRecord("GhostShipQuest", "2");
			SetCurrentQuestMarkToFantoms("habitue");
		break;
		//////  3
		case "GhostShip_Speak_3":
			npchar.GhostShip_Speak_Yet = true;
			pchar.GenQuest.GhostShip.lastspeak_date = LastSpeakDate();

			if (!CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle") &&
			CheckAttribute(pchar, "GenQuest.GhostShip.NeedCoins") &&
			!CheckAttribute(npchar, "quest.GhostShipHelp") &&
			!CheckAttribute(pchar, "GenQuest.GhostShipWorkId") &&
			rand(2) == 1)
			{
				dialog.text = StringFromKey("Habitue_dialog_116");
				link.l1 = StringFromKey("Habitue_dialog_117");
				link.l1.go = "exit_sit";
				break;
			}

			dialog.text = StringFromKey("Habitue_dialog_118");
			if (sti(PChar.GenQuest.GhostShip.KillMe) > 0 || sti(PChar.GenQuest.GhostShip.DeadByMe) > 0)
			{
				link.l1 = StringFromKey("Habitue_dialog_119", pchar);
			}
			else
			{
				link.l1 = StringFromKey("Habitue_dialog_120");
			}
			link.l1.go = "GhostShip_Speak_3_2";
			SetCurrentQuestMarkToFantoms("habitue");
		break;

		case "GhostShip_Speak_3_2":
			dialog.text = StringFromKey("Habitue_dialog_121");
			link.l1 = StringFromKey("Habitue_dialog_122");
			link.l1.go = "GhostShip_Speak_3_3";
		break;

		case "GhostShip_Speak_3_3":
			dialog.text = StringFromKey("Habitue_dialog_123");
			if (sti(PChar.GenQuest.GhostShip.KillMe) > 0 || sti(PChar.GenQuest.GhostShip.DeadByMe) > 0)
			{
				link.l1 = StringFromKey("Habitue_dialog_124");
			}
			else
			{
				link.l1 = StringFromKey("Habitue_dialog_125");
			}
			link.l1.go = "exit_sit";
			pchar.GenQuest.GhostShip.AskAbout = "2";// вечный генератор
			AddQuestRecord("GhostShipQuest", "3");
			GhostShipOnMap();
		break;
		/////////////////////////////////////////////
		case "talk_with_alchogol_song":
			dialog.text = StringFromKey("Habitue_dialog_126");
			link.l1 = StringFromKey("Habitue_dialog_127");
			link.l1.go = "talk_with_alchogol_song_2";
			link.l2 = StringFromKey("Habitue_dialog_128");
			link.l2.go = "exit";
		break;

		case "talk_with_alchogol_song_2":
			dialog.text = StringFromKey("Habitue_dialog_129");
			link.l1 = StringFromKey("Habitue_dialog_130");
			link.l1.go = "talk_with_alchogol_song_3";
			link.l2 = StringFromKey("Habitue_dialog_131");
			link.l2.go = "exit";
		break;

		case "talk_with_alchogol_song_3":
			dialog.text = StringFromKey("Habitue_dialog_132");
			link.l1 = StringFromKey("Habitue_dialog_133");
			link.l1.go = "exit";
		break;

		case "talk_with_alchogol":
			Diag.TempNode = "begin_sit";
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("alc");
		break;

		case "begin_sit":
			Diag.TempNode = "first time";
			dialog.text = StringFromKey("Habitue_dialog_137", LinkRandPhrase(
						StringFromKey("Habitue_dialog_134"),
						StringFromKey("Habitue_dialog_135", GetAddress_Form(npchar)),
						StringFromKey("Habitue_dialog_136", pchar)));
			link.l1 = StringFromKey("Habitue_dialog_138");
			link.l1.go = "sit_2";
		break;

		// Церковный генератор. Квест №2 -->
		case "Alcogol_GenQuest_Church_2_1":
			dialog.text = StringFromKey("Habitue_dialog_139", pchar);
			link.l1 = StringFromKey("Habitue_dialog_140");
			link.l1.go = "Alcogol_GenQuest_Church_2_2";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
		break;

		case "Alcogol_GenQuest_Church_2_2":
			dialog.text = StringFromKey("Habitue_dialog_141");
			link.l1 = StringFromKey("Habitue_dialog_142");
			link.l1.go = "Alcogol_GenQuest_Church_2_3";
		break;

		case "Alcogol_GenQuest_Church_2_3":
			dialog.text = StringFromKey("Habitue_dialog_143");
			link.l1 = StringFromKey("Habitue_dialog_144");
			link.l1.go = "Alcogol_GenQuest_Church_2_4";
		break;

		case "Alcogol_GenQuest_Church_2_4":
			dialog.text = StringFromKey("Habitue_dialog_145");
			link.l1 = StringFromKey("Habitue_dialog_146");
			link.l1.go = "Alcogol_GenQuest_Church_2_5";
		break;

		case "Alcogol_GenQuest_Church_2_5":
			dialog.text = StringFromKey("Habitue_dialog_147");
			link.l1 = StringFromKey("Habitue_dialog_148");
			link.l1.go = "Alcogol_GenQuest_Church_2_6";
		break;

		case "Alcogol_GenQuest_Church_2_6":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
			string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
			PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			if (rand(1))    // evganat - развилка
			{
				PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // Нужно для проверки при убийстве банды
				Log_TestInfo("Сгенерилась первая ветка квеста");
			}
			else
			{
				Log_TestInfo("Сгенерилась вторая ветка квеста");
			}
			SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
			Log_TestInfo("Бандюганы, что обнесли церковь, будут в локации - " + sGenLocation + " Времени на их поиск - 1 день");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
		break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
		case "Jamaica_ratH_1":
			dialog.text = StringFromKey("Habitue_dialog_149");
			link.l1 = StringFromKey("Habitue_dialog_150");
			link.l1.go = "exit_sit";
			pchar.questTemp.Slavetrader = "FindRatJamaica_W";

			RemoveLandQuestmarkToFantoms_Main("habitue", "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("FortOrange_waitress"), "Slavetrader");
		break;

		case "EscapeSlave_Villemstad_H1":
			dialog.text = StringFromKey("Habitue_dialog_151");
			link.l1 = StringFromKey("Habitue_dialog_152");
			link.l1.go = "EscapeSlave_Villemstad_H2";
		break;

		case "EscapeSlave_Villemstad_H2":
			dialog.text = StringFromKey("Habitue_dialog_153", pchar);
			link.l1 = StringFromKey("Habitue_dialog_154");
			link.l1.go = "EscapeSlave_Villemstad_H3";
		break;

		case "EscapeSlave_Villemstad_H3":
			dialog.text = StringFromKey("Habitue_dialog_155", pchar);
			link.l1 = StringFromKey("Habitue_dialog_156", pchar);
			link.l1.go = "EscapeSlave_Villemstad_H4";
		break;

		case "EscapeSlave_Villemstad_H4":
			dialog.text = StringFromKey("Habitue_dialog_157", pchar.questTemp.SlavetraderAreal.add);
			link.l1 = StringFromKey("Habitue_dialog_158");
			link.l1.go = "EscapeSlave_Villemstad_H5";
		break;

		case "EscapeSlave_Villemstad_H5":
			dialog.text = StringFromKey("Habitue_dialog_159", pchar.questTemp.Slavetrader.ShipName);
			link.l1 = StringFromKey("Habitue_dialog_160");
			link.l1.go = "EscapeSlave_Villemstad_H6";
		break;

		case "EscapeSlave_Villemstad_H6":
			dialog.text = StringFromKey("Habitue_dialog_161");
			link.l1 = StringFromKey("Habitue_dialog_162");
			link.l1.go = "exit_sit";
			Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
			Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
			Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
			AddQuestRecord("Slavetrader", "22_4");
			AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
			pchar.questTemp.Slavetrader = "FindMayak";
			RemoveLandQuestMarkToFantoms_Main("habitue", "Slavetrader");
		break;

		//ОЗГ, Крыса
		case "Rat_Tavern_1":
			dialog.text = StringFromKey("Habitue_dialog_163");
			link.l1 = StringFromKey("Habitue_dialog_164", pchar);
			link.l1.go = "Rat_Tavern_2";
		break;

		case "Rat_Tavern_2":
			dialog.text = StringFromKey("Habitue_dialog_165");
			link.l1 = StringFromKey("Habitue_dialog_166");
			link.l1.go = "exit_sit";
			CreateRatOfficer();
			Pchar.quest.Headhunter_Rattortuga.win_condition.l1 = "location";
			Pchar.quest.Headhunter_Rattortuga.win_condition.l1.location = "Tortuga";
			Pchar.quest.Headhunter_Rattortuga.function = "Headhunter_CreateRatpinasse";
			pchar.questTemp.Headhunter = "Rat_tortuga";
			SetFunctionTimerCondition("Headhunter_PinasseOver", 0, 0, 30, false);
			AddQuestRecord("Headhunt", "14");
			RemoveLandQuestMarkToFantoms_Main("habitue", "Headhunt");
		break;

		//Поиск ловцов жемчуга, Шарп
		case "SeekSharp_Tavern_1":
			dialog.text = StringFromKey("Habitue_dialog_167");
			link.l1 = StringFromKey("Habitue_dialog_168");
			link.l1.go = "exit_sit";
			pchar.questTemp.Sharp = "takeRumour";
			AddQuestRecord("SharpPearl", "14");
			RemoveLandQuestmarkToFantoms_Main("habitue", "SharpPearl");
			RemoveMapQuestMark("Shore9", "SharpPearl");
			RemoveMapQuestMark("Shore55", "SharpPearl");
			SeaPearl_PiratesBaron_AddQuestMarks();
		break;
		//<--Поиск ловцов жемчуга, Шарп

		case "sit_2":
			AddMoneyToCharacter(pchar, -2);
			WaitDate("", 0, 0, 0, 0, 30);
			//navy --> Alcohol - rum count;
			LAi_UpAlcoholState();
			//<-- navy
			dialog.text = StringFromKey("Habitue_dialog_172", LinkRandPhrase(
						StringFromKey("Habitue_dialog_169", pchar),
						StringFromKey("Habitue_dialog_170"),
						StringFromKey("Habitue_dialog_171")));
			link.l1 = StringFromKey("Habitue_dialog_173");
			link.l1.go = "exit_sit";
			if (makeint(pchar.money) >= 2)
			{
				link.l2 = StringFromKey("Habitue_dialog_174");
				link.l2.go = "sit_3";
			}
			// homo 01/08/06 to_del
			// наводка на товар - перенес в слухи
			//if (sti(pchar.reputation) < 41)
			//{
			//    link.l3 = "Что интересного можешь сказать про 'честных' купцов в этих водах?";
			//	link.l3.go = "Find_Merchant_1";
			//}
			//homo 15/06/06 слухи
			link.l4 = StringFromKey("Habitue_dialog_178", LinkRandPhrase(
						StringFromKey("Habitue_dialog_175", pchar),
						StringFromKey("Habitue_dialog_176"),
						StringFromKey("Habitue_dialog_177")));
			link.l4.go = "rumours_habitue";
		//homo
		break;

		case "sit_3":
			int iSituation = rand(6);
			switch (iSituation)
			{
				case 0:
					dialog.text = StringFromKey("Habitue_dialog_179");
					link.l1 = StringFromKey("Habitue_dialog_180");
					link.l1.go = "sit_2";
				break;

				case 1:
					if (rand(1))
					{
						dialog.text = StringFromKey("Habitue_dialog_183", RandPhraseSimple(
									StringFromKey("Habitue_dialog_181", pchar, GetAddress_Form(NPChar)),
									StringFromKey("Habitue_dialog_182", pchar)));
						link.l1 = StringFromKey("Habitue_dialog_184");
						link.l1.go = "exit_sit";
						link.l2 = StringFromKey("Habitue_dialog_185");
						link.l2.go = "sit_case_2_enemy";
						link.l3 = StringFromKey("Habitue_dialog_186");
						link.l3.go = "sit_case_2_enemy2";
					}
					else
					{
						dialog.text = StringFromKey("Habitue_dialog_189", RandPhraseSimple(
									StringFromKey("Habitue_dialog_187", pchar),
									StringFromKey("Habitue_dialog_188")));
						link.l1 = StringFromKey("Habitue_dialog_190");
						link.l1.go = "exit_sit";
						link.l2 = StringFromKey("Habitue_dialog_191");
						link.l2.go = "sit_case_2_enemy1";
						link.l3 = StringFromKey("Habitue_dialog_192");
						link.l3.go = "sit_case_2_enemy2";
					}
					link.l4 = StringFromKey("Habitue_dialog_193");
					link.l4.go = "sit_case_2_friend";
				break;

				case 2:
					dialog.text = StringFromKey("Habitue_dialog_194");
					link.l1 = StringFromKey("Habitue_dialog_195");
					link.l1.go = "exit_sit";
					link.l2 = StringFromKey("Habitue_dialog_196");
					link.l2.go = "sit_case_3";
				break;

				case 3:
					if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110))
					{
						dialog.text = StringFromKey("Habitue_dialog_197");
						link.l1 = StringFromKey("Habitue_dialog_198");
						link.l1.go = "sit_2";
					}
					else
					{
						dialog.text = StringFromKey("Habitue_dialog_199");
						link.l1 = StringFromKey("Habitue_dialog_200");
						link.l1.go = "sit_case_4_exit";
					}
				break;

				case 4:
					dialog.text = StringFromKey("Habitue_dialog_201");
					link.l1 = StringFromKey("Habitue_dialog_202");
					link.l1.go = "sit_2";// TODO "sit_case_5_exit";
				break;

				case 5:
					if (!CheckAttribute(pchar, "GenQuest.GhostShip.LastBattleEnd") && !checkAttribute(npchar, "GhostShip_Speak_Yet") && pchar.GenQuest.GhostShip.lastspeak_date != LastSpeakDate())
					{
						dialog.text = StringFromKey("Habitue_dialog_203");
						link.l1 = StringFromKey("Habitue_dialog_204");
						link.l1.go = "exit_sit";
						switch (sti(pchar.GenQuest.GhostShip.AskAbout))
						{
							case 0 :
								link.l2 = StringFromKey("Habitue_dialog_205");
								link.l2.go = "GhostShip_Speak_1";
							break;

							case 1 :
								link.l2 = StringFromKey("Habitue_dialog_206");
								link.l2.go = "GhostShip_Speak_2";
							break;

							case 2 :
								link.l2 = StringFromKey("Habitue_dialog_207");
								link.l2.go = "GhostShip_Speak_3";
							break;
						}
					}
					else
					{
						dialog.text = StringFromKey("Habitue_dialog_208");
						link.l1 = StringFromKey("Habitue_dialog_209");
						link.l1.go = "sit_2";
					}
				break;
				case 6:
				// Dolphin Французский сюжет. Поиск отца Мари ->
					if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL6_8" && pchar.location == "PortPax_tavern")
					{
						dialog.text = StringFromKey("Habitue_dialog_210");
						link.l1 = StringFromKey("Habitue_dialog_211");
						link.l1.go = "exit_sit";

						link.l2 = StringFromKey("Habitue_dialog_212");
						link.l2.go = "FL6_1";
						break;
					}
					// Dolphin Французский сюжет. Поиск отца Мари <-

					// Dolphin Французский сюжет. Поиск Гранье ->
					if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL2_s2" && pchar.location == "FortFrance_tavern")
					{
						dialog.text = StringFromKey("Habitue_dialog_213");
						link.l1 = StringFromKey("Habitue_dialog_214");
						link.l1.go = "exit_sit";

						link.l2 = StringFromKey("Habitue_dialog_215");
						link.l2.go = "FL2_1";
						break;
					}
					// Dolphin Французский сюжет. Поиск Гранье <-

					// Dolphin Французский сюжет. Поиск Фуше ->
					if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL3_s1" && pchar.location == "Tortuga_tavern")
					{
						dialog.text = StringFromKey("Habitue_dialog_216");
						link.l1 = StringFromKey("Habitue_dialog_217");
						link.l1.go = "exit_sit";

						link.l2 = StringFromKey("Habitue_dialog_218");
						link.l2.go = "FL3_1";
						break;
					}
					// Dolphin Французский сюжет. Поиск Фуше <-

					dialog.text = StringFromKey("Habitue_dialog_219");
					link.l1 = StringFromKey("Habitue_dialog_220");
					link.l1.go = "sit_2";
				break;
			}
		break;

		//==============================================================================
		// Французский сюжет. Поиск ГРанье
		case "FL2_1":
			dialog.text = StringFromKey("Habitue_dialog_221");
			link.l1 = StringFromKey("Habitue_dialog_222");
			link.l1.go = "FL2_2";
		break;

		case "FL2_2":
			dialog.text = StringFromKey("Habitue_dialog_223");
			link.l1 = StringFromKey("Habitue_dialog_224");
			link.l1.go = "FL2_3";
		break;

		case "FL2_3":
			dialog.text = StringFromKey("Habitue_dialog_225");
			link.l1 = StringFromKey("Habitue_dialog_226");
			link.l1.go = "exit_sit";

			AddDialogExitQuest("FL2_s3");
		break;

		//==============================================================================
		// Французский сюжет. Поиск Фуше
		case "FL3_1":
			dialog.text = StringFromKey("Habitue_dialog_227");
			link.l1 = StringFromKey("Habitue_dialog_228");
			link.l1.go = "FL3_2";
		break;

		case "FL3_2":
			dialog.text = StringFromKey("Habitue_dialog_229");
			link.l1 = StringFromKey("Habitue_dialog_230");
			link.l1.go = "exit_sit";

		//AddDialogExitQuest("FL3_s2");
		break;

		//==============================================================================
		// Французский сюжет. Поиск Отца мари
		case "FL6_1":
			dialog.text = StringFromKey("Habitue_dialog_231");
			link.l1 = StringFromKey("Habitue_dialog_232");
			link.l1.go = "FL6_2";
		break;

		case "FL6_2":
			dialog.text = StringFromKey("Habitue_dialog_233");
			link.l1 = StringFromKey("Habitue_dialog_234");
			link.l1.go = "FL6_3";
		break;

		case "FL6_3":
			dialog.text = StringFromKey("Habitue_dialog_235");
			link.l1 = "...";
			link.l1.go = "exit_sit";
		//AddDialogExitQuest("FL6_9");
		break;

		case "FL6_4":
			dialog.text = StringFromKey("Habitue_dialog_236");
			link.l1 = StringFromKey("Habitue_dialog_237");
			link.l1.go = "FL6_5";
		break;

		case "FL6_5":
			dialog.text = StringFromKey("Habitue_dialog_238");
			link.l1 = StringFromKey("Habitue_dialog_239");
			link.l1.go = "FL6_6";
		break;

		case "FL6_6":
			dialog.text = StringFromKey("Habitue_dialog_240");
			link.l1 = StringFromKey("Habitue_dialog_241");
			link.l1.go = "FL6_7";
		break;

		case "FL6_7":
			dialog.text = StringFromKey("Habitue_dialog_242");
			link.l1 = StringFromKey("Habitue_dialog_243");
			link.l1.go = "FL6_8";
		break;

		case "FL6_8":
			dialog.text = StringFromKey("Habitue_dialog_244");
			link.l1 = StringFromKey("Habitue_dialog_245");
			link.l1.go = "FL6_9";
		break;

		case "FL6_9":
			dialog.text = StringFromKey("Habitue_dialog_246");
			link.l1 = StringFromKey("Habitue_dialog_247");
			link.l1.go = "FL6_10";
		break;

		case "FL6_10":
			dialog.text = StringFromKey("Habitue_dialog_248");
			link.l1 = StringFromKey("Habitue_dialog_249");
			link.l1.go = "FL6_11";
		break;

		case "FL6_11":
			dialog.text = StringFromKey("Habitue_dialog_250");
			link.l1 = StringFromKey("Habitue_dialog_251");
			link.l1.go = "exit";

		//AddDialogExitQuest("FL6_10");
		break;

		case "sit_case_5_exit": // дуэль
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
		//AddDialogExitQuest("fighting");
		break;

		case "sit_case_4_exit":
			PlayerRPGCheck_Skill_NotifyFail(SKILL_SNEAK, false);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			pchar.questTemp.friend_in_tavern = npchar.id;
			AddDialogExitQuest("without_memory");
		break;

		case "sit_case_3":
			dialog.text = StringFromKey("Habitue_dialog_252");
			link.l1 = StringFromKey("Habitue_dialog_253");
			link.l1.go = "exit_sit";
			link.l2 = StringFromKey("Habitue_dialog_254");
			link.l2.go = "sit_2";
		break;

		case "sit_case_2_friend":
			dialog.text = StringFromKey("Habitue_dialog_255");
			link.l1 = StringFromKey("Habitue_dialog_256");
			link.l1.go = "exit_sit";
			link.l2 = StringFromKey("Habitue_dialog_257");
			link.l2.go = "sit_case_2_friend_2";
		break;

		case "sit_case_2_friend_2":
			dialog.text = StringFromKey("Habitue_dialog_258", pchar);
			link.l1 = StringFromKey("Habitue_dialog_259");
			link.l1.go = "tavern_keeper";
		break;

		case "sit_case_2_enemy":
			dialog.text = StringFromKey("Habitue_dialog_260");
			link.l1 = StringFromKey("Habitue_dialog_261");
			link.l1.go = "exit_sit1";
			link.l2 = StringFromKey("Habitue_dialog_262");
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy1":
			dialog.text = StringFromKey("Habitue_dialog_263");
			link.l1 = StringFromKey("Habitue_dialog_264");
			link.l1.go = "exit_sit1";
			link.l2 = StringFromKey("Habitue_dialog_265", RandSwear());
			link.l2.go = "sit_case_2_enemy3";
		break;

		case "sit_case_2_enemy2":
			ChangeCharacterReputation(pchar, -2);
			if (rand(1))
			{
				dialog.text = StringFromKey("Habitue_dialog_269", LinkRandPhrase(
							StringFromKey("Habitue_dialog_266"),
							StringFromKey("Habitue_dialog_267", RandSwear()),
							StringFromKey("Habitue_dialog_268", pchar)));
				link.l1 = StringFromKey("Habitue_dialog_276", RandPhraseSimple(
							StringFromKey("Habitue_dialog_272", RandPhraseSimple(
									StringFromKey("Habitue_dialog_270"),
									StringFromKey("Habitue_dialog_271"))),
							StringFromKey("Habitue_dialog_275", RandPhraseSimple(
									StringFromKey("Habitue_dialog_273"),
									StringFromKey("Habitue_dialog_274")))));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = StringFromKey("Habitue_dialog_277");
				link.l1 = StringFromKey("Habitue_dialog_280", RandPhraseSimple(
							StringFromKey("Habitue_dialog_278", RandSwear()),
							StringFromKey("Habitue_dialog_279")));
				link.l1.go = "fight_right_now_1";
			}
		break;

		case "sit_case_2_enemy3":
			ChangeCharacterReputation(pchar, 2);
			if (rand(1))
			{
				dialog.text = StringFromKey("Habitue_dialog_284", LinkRandPhrase(
							StringFromKey("Habitue_dialog_281"),
							StringFromKey("Habitue_dialog_282", RandSwear()),
							StringFromKey("Habitue_dialog_283", pchar)));
				link.l1 = StringFromKey("Habitue_dialog_291", RandPhraseSimple(
							StringFromKey("Habitue_dialog_287", RandPhraseSimple(
									StringFromKey("Habitue_dialog_285"),
									StringFromKey("Habitue_dialog_286"))),
							StringFromKey("Habitue_dialog_290", RandPhraseSimple(
									StringFromKey("Habitue_dialog_288"),
									StringFromKey("Habitue_dialog_289")))));
				link.l1.go = "fight_right_now";
			}
			else
			{
				dialog.text = StringFromKey("Habitue_dialog_292");
				link.l1 = StringFromKey("Habitue_dialog_295", RandPhraseSimple(
							StringFromKey("Habitue_dialog_293", RandSwear()),
							StringFromKey("Habitue_dialog_294")));
				link.l1.go = "fight_right_now_1";
			}
		break;

		case "exit_sit":
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "exit_sit1":
			ChangeCharacterReputationToNeutral(pchar, 2.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;

		case "tavern_keeper":
		//ChangeCharacterReputationABS(pchar, 2.0);
			Diag.CurrentNode = Diag.TempNode;
			DialogExit();
			AddDialogExitQuest("tavern_keeper");
		break;
	}
}

#include "DIALOGS\Rumours\Simple_rumors.c"

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag, arCapBase, arCapLocal;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// доп повека
	if (!CheckAttribute(NPChar, "Portman")) NPChar.Portman = 0;
	if (!CheckAttribute(NPChar, "PortManPrice")) NPChar.PortManPrice = (0.06 + frnd() * 0.1);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\PortMan\" + NPChar.City + "_PortMan.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	int i, cn;
	ref chref;
	ref rRealShip;
	string attrL, sTitle, sCapitainId, s1;
	string sColony;
	int nShipStock = 3;

	string sLastSpeakDate = LastSpeakDate();

	// Warship 25.07.09 Генер "Сгоревшее судно". Даты отказа ГГ - если отказал, то предложит снова только на след сутки
	if (CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate") && NPChar.Quest.BurntShip.LastQuestDate != sLastSpeakDate)
	{
		DeleteAttribute(NPChar, "Quest.BurntShip");
	}

	if (CheckAttribute(npchar, "storeShipsNum")) nShipStock = sti(npchar.storeShipsNum);

	bool ok;
	int iTest = FindColony(NPChar.City); // город магазина
	ref rColony;
	string sFrom_sea = "";
	npchar.quest.qty = CheckCapitainsList(npchar); //для списка кэпов

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
		sFrom_sea = rColony.from_sea;
	}

	attrL = Dialog.CurrentNode;

	if (HasSubStr(attrL, "BurntShip19_"))
	{
		i = findsubstr(attrL, "_", 0);
		NPChar.Quest.BurntShip.ShipCompanionIndex = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
		Dialog.CurrentNode = "BurntShip19";
	}

	// evganat - оптимизация поиска капитанов
	if (HasSubStr(attrL, "CapList_l"))
	{
		i = findsubstr(attrL, "_l", 0);
		npchar.temp.caplist_num = strcut(attrL, i + 2, strlen(attrL) - 1); // индекс в конце
		Dialog.CurrentNode = "CapList_Check";
	}

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Portman_4", LinkRandPhrase(
								StringFromKey("Common_Portman_1"),
								StringFromKey("Common_Portman_2"),
								StringFromKey("Common_Portman_3"))),
						StringFromKey("Common_Portman_8", LinkRandPhrase(
								StringFromKey("Common_Portman_5", pchar),
								StringFromKey("Common_Portman_6", pchar),
								StringFromKey("Common_Portman_7", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Portman_11", RandPhraseSimple(
								StringFromKey("Common_Portman_9"),
								StringFromKey("Common_Portman_10"))),
						StringFromKey("Common_Portman_14", RandPhraseSimple(
								StringFromKey("Common_Portman_12", GetWorkTypeOfMan(npchar, "")),
								StringFromKey("Common_Portman_13", GetWorkTypeOfMan(npchar, "")))));
				link.l1.go = "fight";
				break;
			}

			//homo Линейка Блада
			if (Pchar.questTemp.CapBloodLine == true)
			{
				dialog.Text = StringFromKey("Common_Portman_18", LinkRandPhrase(
							StringFromKey("Common_Portman_15", TimeGreeting()),
							StringFromKey("Common_Portman_16", GetFullName(pchar)),
							StringFromKey("Common_Portman_17", GetFullName(pchar))));
				Link.l1 = StringFromKey("Common_Portman_19", NPChar.name);
				Link.l1.go = "exit";
				if (CheckAttribute(Pchar, "questTemp.CapBloodLine.ShipForJack") && Pchar.questTemp.CapBloodLine.ShipForJack == true)
				{
					Link.l2 = StringFromKey("Common_Portman_20");
					Link.l2.go = "Blood_Portman1";
				}
				break;
			}

			//homo

			if (NPChar.quest.meeting == "0")
			{
				NPChar.quest.meeting = "1";
				dialog.text = StringFromKey("Common_Portman_21", GetAddress_Form(NPChar), GetFullName(npchar));

				if (pchar.ship.type == SHIP_NOTUSED)
					Link.l1 = StringFromKey("Common_Portman_22", GetFullName(NPChar), GetFullName(pchar));
				else
					Link.l1 = StringFromKey("Common_Portman_23", GetFullName(NPChar), GetFullName(pchar), pchar.ship.name);
				// Французский сюжет ->
				if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL1_s42")
					Link.l1 = StringFromKey("Common_Portman_24", GetFullName(NPChar), GetFullName(pchar));
			}
			else
			{
				s1 = StringFromKey("Common_Portman_25");
				ok = (sFrom_sea == "") || (pchar.location.from_sea == sFrom_sea);

				if (sti(pchar.ship.type) != SHIP_NOTUSED && ok)
					s1 = StringFromKey("Common_Portman_26");

				dialog.text = StringFromKey("Common_Portman_30", LinkRandPhrase(
							StringFromKey("Common_Portman_27", GetAddress_Form(NPChar)),
							StringFromKey("Common_Portman_28", GetFullName(Pchar), s1),
							StringFromKey("Common_Portman_29", GetFullName(Pchar))));
				Link.l1 = StringFromKey("Common_Portman_31", GetFullName(NPChar));
			}
			Link.l1.go = "node_2";
		break;

		case "node_2":
		// Церковный генератор 1
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan") && PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony == NPChar.city)
			{
				dialog.text = StringFromKey("Common_Portman_32", GetFullName(PChar));
				if (!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapFullInfo"))    // Получаем полную инфу
				{
					if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
					{
						dialog.text = StringFromKey("Common_Portman_33");
						if (sti(PChar.Money) >= 1000)
						{
							link.l1 = StringFromKey("Common_Portman_34", pchar);
							link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
						}
						else
						{
							link.l1 = StringFromKey("Common_Portman_38", LinkRandPhrase(
										StringFromKey("Common_Portman_35", pchar),
										StringFromKey("Common_Portman_36"),
										StringFromKey("Common_Portman_37", pchar)));
							link.l1.go = "exit";
						}
					}
					else
					{
						link.l1 = StringFromKey("Common_Portman_39", pchar, PChar.GenQuest.ChurchQuest_1.CapFullName);
						link.l1.go = "Church_GenQuest1_Node_FillFullInfo";
					}
				}
				else    // Полная инфа уже есть
				{
					link.l1 = StringFromKey("Common_Portman_40", PChar.GenQuest.ChurchQuest_1.CapShipName, PChar.GenQuest.ChurchQuest_1.CapFullName);
					if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NextColonyIsLast")) // Он здесь, в этой колонии!
						link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_1";
					else // Отправляет в рандомную колонию
						link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_1";
				}
				break;
			}

			dialog.text = StringFromKey("Common_Portman_41", GetFullName(PChar));
			if (sti(pchar.ship.type) != SHIP_NOTUSED)
			{
				if (GetGlobalTutor())
				{
					goto skipToShipStock_Common;
				}
				Link.l2 = StringFromKey("Common_Portman_42");
				Link.l2.go = "node_4";
				Link.l13 = StringFromKey("Common_Portman_46", LinkRandPhrase(
							StringFromKey("Common_Portman_43"),
							StringFromKey("Common_Portman_44"),
							StringFromKey("Common_Portman_45")));
				Link.l13.go = "work_PU";
				skipToShipStock_Common:
				Link.l3 = StringFromKey("Common_Portman_47");
				Link.l3.go = "ShipStock_1";
				if (GetGlobalTutor())
				{
					goto Common_Portman_skipToExit_Common;
				}
			}
			if (sti(NPChar.Portman) > 0)
			{
				Link.l4 = StringFromKey("Common_Portman_48");
				Link.l4.go = "ShipStockReturn_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = StringFromKey("Common_Portman_49");
				link.l5.go = "LoanForAll";//(перессылка в кредитный генератор)	
			}
			if (CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = StringFromKey("Common_Portman_52", RandPhraseSimple(
							StringFromKey("Common_Portman_50", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))),
							StringFromKey("Common_Portman_51", pchar, GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)))));
				link.l7.go = "IntelligenceForAll";
			}
			link.l6 = StringFromKey("Common_Portman_53");
			link.l6.go = "CapitainList";
			//ОЗГ
			if (CheckAttribute(pchar, "questTemp.Headhunter"))
			{
				if (pchar.questTemp.Headhunter == "Houm" && npchar.nation == ENGLAND)
				{
					link.l12 = StringFromKey("Common_Portman_54");
					link.l12.go = "Houm_portman_1";
				}
			}

			link.l8 = StringFromKey("Common_Portman_55");
			// Warship 26.07.09 Генер "Сгоревшее судно"
			if (CheckAttribute(NPChar, "Quest.BurntShip") && !CheckAttribute(NPChar, "Quest.BurntShip.LastQuestDate"))
			{
				if (CheckAttribute(NPChar, "Quest.BurntShip.TimeIsOver")) // Просрочено
				{
					link.l8.go = "BurntShip10";
				}
				else
				{
					if (CheckAttribute(NPChar, "Quest.BurntShip.TwoDaysWait"))
					{
						if (GetNpcQuestPastDayParam(NPChar, "Quest.BurntShip.TwoDaysWait") >= 2)
						{
							link.l8.go = "BurntShip17";
						}
						else
						{
							link.l8.go = "quests";
						}
					}
					else
					{
						link.l8.go = "BurntShip12";
					}
				}
			}
			else
			{
				link.l8.go = "quests";
			}
			if (CheckAttribute(pchar, "GenQuest.EncGirl"))
			{
				if (pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "portman_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = StringFromKey("Common_Portman_56", pchar);
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if (pchar.GenQuest.EncGirl.Father == "portman_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = StringFromKey("Common_Portman_57");
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook"))
			{
				if (pchar.questTemp.different == "free")
				{
					link.l10 = StringFromKey("Common_Portman_58", pchar);
					link.l10.go = "ShipLetters_out1";
				}
				else
				{
					if (pchar.questTemp.different.GiveShipLetters.city == npchar.city)
					{
						link.l10 = StringFromKey("Common_Portman_59", pchar);
						if (!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakPortman"))
						{
							link.l10.go = "ShipLetters_Portman1_1";
						}
						else
						{
							link.l10.go = "ShipLetters_Portman2";
						}
					}
				}
			}
			// evganat - энциклопедия
			if (!ENCYCLOPEDIA_DISABLED)
			{
				if (CheckAttribute(npchar, "encyclopedia.tome"))
				{
					link.l14 = StringFromKey("Common_Portman_60", pchar);
					link.l14.go = "Encyclopedia_Return";
				}
				else
				{
					if (GetPortmanDisposition() > 3)
					{
						if (!CheckAttribute(npchar, "encyclopedia"))
						{
							link.l14 = StringFromKey("Common_Portman_61", pchar);
							link.l14.go = "Encyclopedia_FirstTime";
						}
						else
						{
							link.l14 = StringFromKey("Common_Portman_62");
							link.l14.go = "Encyclopedia_Check";
						}
					}
				}
			}
			Common_Portman_skipToExit_Common:
			Link.l15 = StringFromKey("Common_Portman_63");
			Link.l15.go = "exit";
		break;

		case "Church_GenQuest1_Node_FillFullInfo":
			dialog.text = StringFromKey("Common_Portman_64");
			link.l1 = StringFromKey("Common_Portman_65");
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_2";
		break;

		case "Church_GenQuest1_Node_FillFullInfo_2":
			dialog.text = StringFromKey("Common_Portman_66");
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = StringFromKey("Common_Portman_67", pchar, GetFullName(NPChar));
				link.l1.go = "Church_GenQuest1_Node_FillFullInfo_3";
			}
			else
			{
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.CurPortManColony"); // Можно будет спросить.
				link.l1 = StringFromKey("Common_Portman_68");
				link.l1.go = "exit";
			}
		break;

		case "Church_GenQuest1_Node_FillFullInfo_3":
			sColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = sColony;
			if (CheckAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan"))
			{
				dialog.text = StringFromKey("Common_Portman_69", PChar.GenQuest.ChurchQuest_1.CapShipName, PChar.GenQuest.ChurchQuest_1.CapFullName, XI_ConvertString("Colony" + sColony + "Gen"));
				DeleteAttribute(pchar, "GenQuest.ChurchQuest_1.NoMoneyToPortMan");
			}
			else
				dialog.text = StringFromKey("Common_Portman_70", PChar.GenQuest.ChurchQuest_1.CapShipName, PChar.GenQuest.ChurchQuest_1.CapFullName, XI_ConvertString("Colony" + sColony + "Gen"));
			link.l1 = StringFromKey("Common_Portman_71");
			link.l1.go = "Church_GenQuest1_Node_FillFullInfo_4";
			AddMoneyToCharacter(pchar, -1000);
		break;

		case "Church_GenQuest1_Node_FillFullInfo_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ен", "на"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Gen"));
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true;
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_1":
			dialog.text = StringFromKey("Common_Portman_72");
			link.l1 = StringFromKey("Common_Portman_73");
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_2";
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_2":
			PChar.GenQuest.ChurchQuest_1.CapGoToColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			dialog.text = StringFromKey("Common_Portman_74");
			link.l1 = StringFromKey("Common_Portman_75");
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_3";
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_3":
			dialog.text = StringFromKey("Common_Portman_76", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Acc"));
			link.l1 = StringFromKey("Common_Portman_77");
			link.l1.go = "Church_GenQuest1_Node_FillInfoOfCapColony_4";
		break;

		case "Church_GenQuest1_Node_FillInfoOfCapColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "5");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapGoToColony + "Pre"));
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = PChar.GenQuest.ChurchQuest_1.CapGoToColony; // Спрашиваем портмана в колонии, куда отправился кэп.
			if (rand(2) == 1)
			{
				Log_TestInfo("Следующая колония - последняя");
				PChar.GenQuest.ChurchQuest_1.NextColonyIsLast = true; // Флаг - следующая колония будет последней
			}
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_1":
			dialog.text = StringFromKey("Common_Portman_78", pchar, GetFullName(PChar));
			link.l1 = StringFromKey("Common_Portman_79");
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_2";
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_2":
			dialog.text = StringFromKey("Common_Portman_80");
			link.l1 = StringFromKey("Common_Portman_81");
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_3";
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_3":
			dialog.text = StringFromKey("Common_Portman_82", pchar);
			link.l1 = StringFromKey("Common_Portman_83", NPChar.Name);
			link.l1.go = "Church_GenQuest1_Node_CapOnThisColony_4";
		break;

		case "Church_GenQuest1_Node_CapOnThisColony_4":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "6");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			//			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithSailors = true; // Спрашиваем моряков
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithCap = true; // Говорим с капитаном
			//			SetFunctionLocationCondition("Church_GenQuest1_ChangeCapitanLocation", "Deck_Near_Ship", true);
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = NPChar.city;
			Group_SetAddress("ChurchGenQuest1_CapGroup", colonies[FindColony(NPChar.City)].Island, "IslandShips1", "Ship_1"); // Ставим кэпа в порту колонии; TODO: а если локатор уже занят?
			Characters[GetCharacterIndex("ChurchGenQuest1_Cap")].Nation = sti(NPChar.Nation); // Сменим нацию, чтоб вражды не было
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskPortMan"); // Больше не спрашиваем
			//			if(rand(1) == 0) PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
			sld = CharacterFromID("ChurchGenQuest1_Cap");
			sld.DeckDialogNode = "ChurchGenQuest_1_DeckDialog_1";
		break;

		case "ShipLetters_out1":
		// evganat - можно вставить отношение сюда
			IncreasePortmanDisposition(2);
			dialog.text = StringFromKey("Common_Portman_84");
			link.l1 = StringFromKey("Common_Portman_85");
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "CaptainBook");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "10");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ShipLetters_Portman1_1":
			pchar.questTemp.different.GiveShipLetters.speakPortman = true;
			s1 = StringFromKey("Common_Portman_86");
			s1 = StringFromKey("Common_Portman_87", s1);
			dialog.text = StringFromKey("Common_Portman_88", s1, FindMoneyString(sti(pchar.questTemp.different.GiveShipLetters.price1)));
			link.l1 = StringFromKey("Common_Portman_89");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Common_Portman_90", npchar.name);
			link.l2.go = "ShipLetters_Portman1_2";
		break;

		case "ShipLetters_Portman1_2" :
		// evganat - можно вставить отношение сюда
			IncreasePortmanDisposition(2);
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "5");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ShipLetters_Portman2":
			dialog.text = StringFromKey("Common_Portman_91");
			link.l1 = StringFromKey("Common_Portman_92");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Common_Portman_93", pchar);
			link.l2.go = "ShipLetters_Portman2_1";
		break;

		case "ShipLetters_Portman2_1":
		// evganat - можно вставить отношение сюда
			IncreasePortmanDisposition(2);
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "6");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = StringFromKey("Common_Portman_94");
			link.l1 = StringFromKey("Common_Portman_95", pchar);
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
		// evganat - можно вставить отношение сюда
			IncreasePortmanDisposition(4);
			dialog.text = StringFromKey("Common_Portman_96");
			link.l1 = StringFromKey("Common_Portman_97", pchar);
			link.l1.go = "EncGirl_3";
		break;

		case "EncGirl_3":
			dialog.text = StringFromKey("Common_Portman_98");
			link.l1 = StringFromKey("Common_Portman_99");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;

		case "EncGirl_4":
			if (sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = StringFromKey("Common_Portman_100", pchar);
				link.l1 = StringFromKey("Common_Portman_101", pchar);
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = StringFromKey("Common_Portman_102", pchar);
				link.l1 = StringFromKey("Common_Portman_103");
				link.l1.go = "EncGirl_6";
			}
		break;

		case "EncGirl_5":
		// evganat - можно вставить отношение сюда
			IncreasePortmanDisposition(3);
			dialog.text = StringFromKey("Common_Portman_104");
			link.l1 = StringFromKey("Common_Portman_105");
			link.l1.go = "EncGirl_5_1";
		break;

		case "EncGirl_6":
		// evganat - можно вставить отношение сюда
			IncreasePortmanDisposition(-2);
			dialog.text = StringFromKey("Common_Portman_106");
			link.l1 = StringFromKey("Common_Portman_107");
			link.l1.go = "EncGirl_6_1";
		break;

		case "EncGirl_5_1":
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
			GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
			AddQuestRecord("JungleGirl", "18");
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_6_1":
			dialog.text = StringFromKey("Common_Portman_108");
			link.l1 = StringFromKey("Common_Portman_109");
			link.l1.go = "EncGirl_6_2";
		break;

		case "EncGirl_6_2":
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ел", "ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("", "а"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "node_4":
		//--> проверка миниквестов начальника порта.
			if (npchar.id == "Providencia_PortMan")
			{
				dialog.text = StringFromKey("Common_Portman_110", GetFullName(pchar));
				link.l1 = StringFromKey("Common_Portman_111", pchar);
				link.l1.go = "exit";
				break;
			}
			if (npchar.quest == "PortmansJornal") //взят квест на судовой журнал
			{
				dialog.text = StringFromKey("Common_Portman_112", npchar.quest.PortmansJornal.capName);
				link.l1 = StringFromKey("Common_Portman_113");
				link.l1.go = "PortmanQuest_NF";
				break;
			}
			if (npchar.quest == "PortmansSeekShip" || npchar.quest == "SeekShip_sink") //взят квест на поиски украденного корабля
			{
				dialog.text = StringFromKey("Common_Portman_114", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)), npchar.quest.PortmansSeekShip.shipName);
				link.l1 = StringFromKey("Common_Portman_115");
				link.l1.go = "exit";
				link.l2 = StringFromKey("Common_Portman_116");
				link.l2.go = "SeekShip_break";
				break;
			}
			if (npchar.quest == "SeekShip_success") //украденный корабль взят на абордаж
			{
				dialog.text = StringFromKey("Common_Portman_117", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)), npchar.quest.PortmansSeekShip.shipName);
				bool bOk = false;
				for (i = 0; i <= COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(pchar, i);
					if (cn != -1)
					{
						sld = &characters[cn];
						if (sld.ship.name == npchar.quest.PortmansSeekShip.shipName &&
						RealShips[sti(sld.ship.type)].BaseName == npchar.quest.PortmansSeekShip.shipTapeName &&
						RealShips[sti(sld.Ship.Type)].basetype == npchar.quest.PortmansSeekShip.shipTape)
						{
							if (i == 0)
							{
								//если нужный корабль - у ГГ
								sld.Ship.Type = GenerateShip(SHIP_TARTANE, true);
								SetBaseShipData(sld);
								SetCrewQuantityFull(sld);
							}
							else
							{
								RemoveCharacterCompanion(pchar, sld);
								AddPassenger(pchar, sld, false);
							}
							bOk = true;
						}
					}
				}
				if (bOk)
				{
					link.l1 = StringFromKey("Common_Portman_118", pchar);
					link.l1.go = "SeekShip_good";
				}
				else
				{
					link.l1 = StringFromKey("Common_Portman_119");
					link.l1.go = "exit";
				}
				link.l2 = StringFromKey("Common_Portman_120");
				link.l2.go = "SeekShip_break";
				break;
			}
			//<-- проверка миниквестов начальника порта. 

			//--> дача миниквестов начальника порта.	
			i = idRand(NPChar.id + "quest", 4); //HardCoffee пример использования нового idRand
			if (i < 3 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "quest.meeting") > 7)
			{
				dialog.text = StringFromKey("Common_Portman_124", LinkRandPhrase(
							StringFromKey("Common_Portman_121"),
							StringFromKey("Common_Portman_122"),
							StringFromKey("Common_Portman_123")));
				link.l1 = StringFromKey("Common_Portman_125", GetAddress_FormToNPC(NPChar));
				link.l1.go = "PortmanQuest";
				SaveCurrentNpcQuestDateParam(npchar, "quest.meeting");
				break;
			}
			else if (i == 3 && !CheckAttribute(NPChar, "Quest.BurntShip"))
			// Warship 25.07.09 Генер "Сгоревшее судно"
			{
				dialog.text = StringFromKey("Common_Portman_126", GetFullName(PChar));
				link.l1 = StringFromKey("Common_Portman_127");
				link.l1.go = "BurntShip4";
				link.l2 = StringFromKey("Common_Portman_128", pchar);
				link.l2.go = "BurntShip2";
				break;
			}
			//<-- дача миниквестов начальника порта.

			dialog.text = StringFromKey("Common_Portman_129");
			Link.l1 = StringFromKey("Common_Portman_130");
			Link.l1.go = "node_2";
			Link.l2 = StringFromKey("Common_Portman_131");
			Link.l2.go = "exit";
		break;

		/////////////////////////////////////////////////////////==========================/////////////////////////////////////////////////////
		//эскорт-пассажиры
		case "work_PU":
			if (npchar.id == "Providencia_PortMan")
			{
				dialog.text = StringFromKey("Common_Portman_132", GetFullName(pchar));
				link.l1 = StringFromKey("Common_Portman_133", pchar);
				link.l1.go = "exit";
				break;
			}
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			if (CheckShipMooredInColony(rColony))
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = StringFromKey("Common_Portman_136", RandPhraseSimple(
								StringFromKey("Common_Portman_134", NationNameGenitive(sti(pchar.nation))),
								StringFromKey("Common_Portman_135", NationNameInstrumental(sti(pchar.nation)))));
					link.l1 = StringFromKey("Common_Portman_139", RandPhraseSimple(
								StringFromKey("Common_Portman_137"),
								StringFromKey("Common_Portman_138")));
					link.l1.go = "exit";
					break;
				}
				//				if (isBadReputation(pchar, 40))
				if (PlayerRPGCheck_BadReputation(40, false))
				{
					dialog.text = StringFromKey("Common_Portman_142", RandPhraseSimple(
								StringFromKey("Common_Portman_140"),
								StringFromKey("Common_Portman_141")));
					link.l1 = StringFromKey("Common_Portman_146", LinkRandPhrase(
								StringFromKey("Common_Portman_143"),
								StringFromKey("Common_Portman_144"),
								StringFromKey("Common_Portman_145")));
					link.l1.go = "exit";
					break;
				}
				dialog.text = StringFromKey("Common_Portman_147");
				link.l1 = StringFromKey("Common_Portman_148");
				link.l1.go = "work_PU_1";
				link.l2 = StringFromKey("Common_Portman_149");
				link.l2.go = "work_PU_2";
			}
			else
			{
				dialog.text = StringFromKey("Common_Portman_150");
				link.l1 = StringFromKey("Common_Portman_151");
				link.l1.go = "exit";
			}
		break;

		case "work_PU_1"://конвой
			if (!CheckAttribute(&TEV, "ArtOfDeals.PortOffice.Convoy"))
				TEV.ArtOfDeals.PortOffice.Convoy = "0";

			if (CheckQuestAttribute("generate_convoy_quest_progress", "begin"))
			{
				dialog.text = StringFromKey("Common_Portman_152");
				link.l1 = StringFromKey("Common_Portman_155", RandPhraseSimple(
							StringFromKey("Common_Portman_153"),
							StringFromKey("Common_Portman_154")));
				link.l1.go = "exit";
				break;
			}

			if (and(CheckOfficersPerk(pchar, "ArtOfDeals") && sti(TEV.ArtOfDeals.PortOffice.Convoy) < 2, true) || !CheckAttribute(npchar, "work_date_PU") || GetNpcQuestPastDayParam(npchar, "work_date_PU") >= 2 || bBettaTestMode)
			{
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7 - sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1)//при низком лидерствое и на 7 класс не даем
				{
					dialog.text = StringFromKey("Common_Portman_156");
					link.l1 = StringFromKey("Common_Portman_157");
					link.l1.go = "exit";
					break;
				}

				if (GetCompanionQuantity(PChar) == COMPANION_MAX)
				{
					dialog.text = StringFromKey("Common_Portman_158");
					link.l1 = StringFromKey("Common_Portman_159", pchar);
					link.l1.go = "exit";
				}
				else
				{
					if (idRand(npchar.id + "generate_convoy_portman", 6) > 1)
					{
						dialog.text = StringFromKey("Common_Portman_160");
						link.l1 = StringFromKey("Common_Portman_163", RandPhraseSimple(
									StringFromKey("Common_Portman_161"),
									StringFromKey("Common_Portman_162")));
						link.l1.go = "ConvoyAreYouSure_PU";

					}
					else
					{
						dialog.text = StringFromKey("Common_Portman_164");
						link.l1 = StringFromKey("Common_Portman_167", RandPhraseSimple(
									StringFromKey("Common_Portman_165"),
									StringFromKey("Common_Portman_166")));
						link.l1.go = "exit";
					}
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Portman_168");
				link.l1 = StringFromKey("Common_Portman_169");
				link.l1.go = "exit";
			}
		break;

		case "work_PU_2": // пассажир
			if (!CheckAttribute(&TEV, "ArtOfDeals.PortOffice.Passenger"))
				TEV.ArtOfDeals.PortOffice.Passenger = "0";

			if (and(CheckOfficersPerk(pchar, "ArtOfDeals") && sti(TEV.ArtOfDeals.PortOffice.Passenger) < 2, true) || !CheckAttribute(npchar, "work_date_PU") || GetNpcQuestPastDayParam(npchar, "work_date_PU") >= 2 || bBettaTestMode)
			{
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7 - sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1)//при низком лидерствое и на 7 класс не даем
				{
					dialog.text = StringFromKey("Common_Portman_170");
					link.l1 = StringFromKey("Common_Portman_171");
					link.l1.go = "exit";
					break;
				}

				if (idRand(npchar.id + "generate_passenger_portman", 6) > 1)
				{
					dialog.Text = StringFromKey("Common_Portman_172");
					link.l1 = StringFromKey("Common_Portman_175", RandPhraseSimple(
								StringFromKey("Common_Portman_173"),
								StringFromKey("Common_Portman_174")));
					Link.l1.go = "PassangerAreYouSure_PU";
				}
				else
				{
					dialog.text = StringFromKey("Common_Portman_176");
					link.l1 = StringFromKey("Common_Portman_179", RandPhraseSimple(
								StringFromKey("Common_Portman_177"),
								StringFromKey("Common_Portman_178")));
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Portman_180");
				link.l1 = StringFromKey("Common_Portman_181");
				link.l1.go = "exit";
			}
		break;

		case "ConvoyAreYouSure_PU":
			CommonGenerator("QuestTrader");
			dialog.text = StringFromKey("Common_Portman_184", RandPhraseSimple(
						StringFromKey("Common_Portman_182"),
						StringFromKey("Common_Portman_183")));
			Link.l1 = StringFromKey("Common_Portman_185");
			Link.l1.go = "exit";
			pchar.quest.destination = FindDestinationCity(npchar, sti(TEV.ArtOfDeals.PortOffice.Convoy) + 1);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date_PU");
		break;

		case "PassangerAreYouSure_PU":
			CommonGenerator("QuestPassanger");
			dialog.text = StringFromKey("Common_Portman_188", RandPhraseSimple(
						StringFromKey("Common_Portman_186"),
						StringFromKey("Common_Portman_187")));
			Link.l1 = StringFromKey("Common_Portman_189");
			Link.l1.go = "exit";
			TEV.GenQuest_DestinationCity = FindDestinationCity(npchar, sti(TEV.ArtOfDeals.PortOffice.Passenger) + 1);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date_PU");
		break;

		case "PortmanQuest_NF":
			dialog.text = StringFromKey("Common_Portman_190");
			link.l1 = StringFromKey("Common_Portman_191", pchar);
			link.l1.go = "node_2";
		break;

		// Warship 25.07.09 Генер "Сгоревшее судно"
		/*case "BurntShip1":
			dialog.text = "Вы правы, капитан, но тут дело такое, что и надежды-то на помощь мало... У нас на рейде сгорело судно, оставленное на попечение портового управления! По недосмотру охранной команды сгорело... По самую ватерлинию\n" +
				"Господи, за что же мне такое наказание-то? Ведь столько лет верой и правдой...";
			link.l1 = "Так, милейший, давайте всё по порядку, иначе мы ни о чём не договоримся.";
			link.l1.go = "BurntShip3";
			link.l2 = "С такими вопросами вам за помощью на верфь нужно, а не ко мне. За пару месяцев вам хоть старое восстановят, хоть новое соорудят. Я не судостроитель"+ GetSexPhrase("","ница") +", так что извините, не по адресу...";
			link.l2.go = "BurntShip2";
		break;*/

		case "BurntShip2":
			dialog.text = StringFromKey("Common_Portman_192");
			link.l1 = StringFromKey("Common_Portman_193");
			link.l1.go = "exit";
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;
		break;

		/*case "BurntShip3":
			dialog.text = "Да, да, капитан. В общем, несчастье страшное... За всю мою долгую карьеру ничего подобного не случалось. Нас может спасти только Провидение и ваша добрая воля.";
			link.l1 = "Хм, эка невидаль - судно сгорело. А страховые договора на что? Или вы его не застраховали?.. В целях экономии, так сказать. А теперь рады бы локоток укусить, да?..";
			link.l1.go = "BurntShip4";
		break;*/

		case "BurntShip4":
			dialog.text = StringFromKey("Common_Portman_194");
			link.l1 = StringFromKey("Common_Portman_195");
			link.l1.go = "BurntShip5";
		break;

		case "BurntShip5":
			sCapitainId = GenerateRandomName(sti(NPChar.nation), "man");

			dialog.text = StringFromKey("Common_Portman_196", sCapitainId);
			link.l1 = StringFromKey("Common_Portman_197");
			link.l1.go = "BurntShip6";

			NPChar.Quest.BurntShip.ShipOwnerName = sCapitainId;
		break;

		case "BurntShip6":
			BurntShipQuest_FillStartParams(NPChar);

			attrL = NPChar.Quest.BurntShip.ShipAttribute;
			iTest = sti(NPChar.Quest.BurntShip.ShipType);

			switch (attrL)
			{
				case "speedrate":
					attrL = StringFromKey("Common_Portman_198", GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")), NPChar.Quest.BurntShip.ShipNeededValue);
				break;

				case "turnrate":
					attrL = StringFromKey("Common_Portman_199", GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")), NPChar.Quest.BurntShip.ShipNeededValue);
				break;

				case "capacity":
					attrL = StringFromKey("Common_Portman_200", GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].Name + "Acc")), NPChar.Quest.BurntShip.ShipNeededValue);
				break;
			}

			dialog.text = attrL;
			link.l1 = StringFromKey("Common_Portman_201");
			link.l1.go = "BurntShip7";
		break;

		case "BurntShip7":
			dialog.text = StringFromKey("Common_Portman_202");
			link.l1 = StringFromKey("Common_Portman_203");
			link.l1.go = "BurntShip8";
			link.l2 = StringFromKey("Common_Portman_204");
			link.l2.go = "BurntShip2";
		break;

		case "BurntShip8":
			dialog.text = StringFromKey("Common_Portman_205");
			link.l1 = StringFromKey("Common_Portman_206");
			link.l1.go = "BurntShip9";
		break;

		case "BurntShip9":
			dialog.text = StringFromKey("Common_Portman_207");
			link.l1 = StringFromKey("Common_Portman_208");
			link.l1.go = "BurntShip9_exit";
		break;

		case "BurntShip9_exit":
			attrL = "BurntShipQuest_TimeIsOver_" + NPChar.Id;
			PChar.Quest.(attrL).win_condition.l1 = "Timer";
			PChar.Quest.(attrL).win_condition.l1.date.day = GetAddingDataDay(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.month = GetAddingDataMonth(0, 6, 0);
			PChar.Quest.(attrL).win_condition.l1.date.year = GetAddingDataYear(0, 6, 0);
			PChar.Quest.(attrL).function = "BurntShipQuest_TimeIsOver";
			PChar.Quest.(attrL).PortmanId = NPChar.id;

			attrL = NPChar.Quest.BurntShip.ShipAttribute;

			iTest = sti(NPChar.Quest.BurntShip.ShipType);

			switch (attrL)
			{
				case "speedrate":
					attrL = StringFromKey("Common_Portman_209", GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Acc")), NPChar.Quest.BurntShip.ShipNeededValue);
				break;

				case "turnrate":
					attrL = StringFromKey("Common_Portman_210", GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Acc")), NPChar.Quest.BurntShip.ShipNeededValue);
				break;

				case "capacity":
					attrL = StringFromKey("Common_Portman_211", GetStrSmallRegister(XI_ConvertString(ShipsTypes[iTest].name + "Acc")), NPChar.Quest.BurntShip.ShipNeededValue);
				break;
			}

			sTitle = "BurntShipQuest" + NPChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "BurntShipQuest", "1");
			AddQuestUserDataForTitle(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Pre"));
			AddQuestUserData(sTitle, "portmanName", GetFullName(NPChar));
			AddQuestUserData(sTitle, "cityName", XI_ConvertString("Colony" + NPChar.city + "Gen"));
			AddQuestUserData(sTitle, "text", attrL);

			NPChar.Quest.BurntShip.LastPortmanName = GetFullName(NPChar); // Запомнм имя

			DialogExit();
		break;

		// Вариант, когда не уложились в сроки
		case "BurntShip10":
			dialog.text = StringFromKey("Common_Portman_212");
			link.l1 = StringFromKey("Common_Portman_213", NPChar.Quest.BurntShip.LastPortmanName);
			link.l1.go = "BurntShip11";
		break;

		case "BurntShip11":
			dialog.text = StringFromKey("Common_Portman_214");
			link.l1 = StringFromKey("Common_Portman_215");
			link.l1.go = "BurntShip11_exit";
		break;

		case "BurntShip11_exit":
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "2");
			AddQuestUserData(sTitle, "portmanName", NPChar.Quest.BurntShip.LastPortmanName);
			CloseQuestHeader(sTitle);

			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		// Не просрочено - проверяем корабль
		case "BurntShip12":
			dialog.text = StringFromKey("Common_Portman_216");
			link.l1 = StringFromKey("Common_Portman_217", pchar);
			link.l1.go = "BurntShip14";
			link.l2 = StringFromKey("Common_Portman_218", pchar, GetFullName(NPChar));
			link.l2.go = "BurntShip13";
		break;

		case "BurntShip13":
		// evganat - можно вставить отношение сюда
			IncreasePortmanDisposition(-2);
			dialog.text = StringFromKey("Common_Portman_219");
			link.l1 = StringFromKey("Common_Portman_220");
			link.l1.go = "BurntShip13_exit";
		break;

		case "BurntShip13_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			CloseQuestHeader(sTitle);

			ChangeCharacterReputation(PChar, -5);
			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		case "BurntShip14":
			dialog.text = StringFromKey("Common_Portman_221");

			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);

			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);

					if (cn > 0)
					{
						chref = GetCharacter(cn);

						sld = &RealShips[sti(chref.ship.type)];

						if (GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
						stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip15";
						}
					}
				}
			}

			link.l99 = StringFromKey("Common_Portman_222");
			link.l99.go = "exit";
		break;

		case "BurntShip15":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			dialog.text = StringFromKey("Common_Portman_223", pchar);
			link.l99 = StringFromKey("Common_Portman_224", pchar);
			link.l99.go = "BurntShip16";
		break;

		case "BurntShip16":
			dialog.text = StringFromKey("Common_Portman_225");
			link.l1 = StringFromKey("Common_Portman_226");
			link.l1.go = "BurntShip16_exit";
		break;

		case "BurntShip16_exit":
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "3");

			NPChar.Quest.BurntShip.TwoDaysWait = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Quest.BurntShip.TwoDaysWait"); // Запомним дату

			sTitle = "BurntShipQuest" + NPChar.Id;
			PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время

			DialogExit();
		break;

		case "BurntShip17":
			dialog.text = StringFromKey("Common_Portman_227");
			link.l1 = StringFromKey("Common_Portman_228", pchar);
			link.l1.go = "BurntShip18";
		break;

		case "BurntShip18":
			dialog.text = StringFromKey("Common_Portman_229");

			sTitle = NPChar.Quest.BurntShip.ShipAttribute;
			ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);

			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
				for (i = 1; i < COMPANION_MAX; i++)
				{
					cn = GetCompanionIndex(PChar, i);

					if (cn > 0)
					{
						chref = GetCharacter(cn);

						sld = &RealShips[sti(chref.ship.type)];

						if (GetRemovable(chref) && sti(sld.basetype) == sti(NPchar.Quest.BurntShip.ShipType) &&
						stf(sld.(sTitle)) >= stf(NPChar.Quest.BurntShip.ShipNeededValue))
						{
							attrL = "l" + i;
							Link.(attrL) = chref.Ship.Name;
							Link.(attrL).go = "BurntShip19_" + i;
						}
					}
				}
			}

			link.l99 = StringFromKey("Common_Portman_230");
			link.l99.go = "exit";
		break;

		case "BurntShip19":
			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			cn = GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_Portmaner")) * 2;
			rRealShip = GetRealShip(GetCharacterShipType(sld));
			if (sti(rRealShip.Stolen)) cn *= 3;

			dialog.text = StringFromKey("Common_Portman_231", FindMoneyString(cn));
			link.l1 = StringFromKey("Common_Portman_232", pchar);
			link.l1.go = "BurntShip21";
			link.l2 = StringFromKey("Common_Portman_233", pchar);
			link.l2.go = "BurntShip20_exit";

			NPChar.Quest.BurntShip.Money = cn;

		//sTitle = "BurntShipQuest" + NPChar.location;
		//PChar.Quest.(sTitle).over = "yes"; // Завершаем прерывание на время
		break;

		case "BurntShip20_exit":
		// evganat - можно вставить отношение сюда
			IncreasePortmanDisposition(4);
			AddItemLog(pchar, "chest", its(makeint(sti(NPChar.Quest.BurntShip.Money) / 12000)), StringFromKey("InfoMessages_134"), "Important_item");
			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sTitle, "money", FindMoneyString(sti(NPChar.Quest.BurntShip.Money)));
			CloseQuestHeader(sTitle);

			ChangeCharacterReputation(PChar, 3);

			sld = &Characters[GetCompanionIndex(PChar, sti(NPChar.Quest.BurntShip.ShipCompanionIndex))];
			RemoveCharacterCompanion(PChar, sld);
			AddPassenger(PChar, sld, false);

			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		case "BurntShip21":
		// evganat - можно вставить отношение сюда
			IncreasePortmanDisposition(-2);
			dialog.text = StringFromKey("Common_Portman_234");
			link.l1 = StringFromKey("Common_Portman_235");
			link.l1.go = "BurntShip21_exit";
		break;

		case "BurntShip21_exit":
			ChangeCharacterReputation(PChar, -5);

			sTitle = "BurntShipQuest" + NPChar.location;
			AddQuestRecordEx(sTitle, "BurntShipQuest", "5");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sTitle, "money", FindMoneyString(sti(NPChar.Quest.BurntShip.Money)));
			CloseQuestHeader(sTitle);

			DeleteAttribute(NPChar, "Quest.BurntShip");
			NPChar.Quest.BurntShip.LastQuestDate = sLastSpeakDate;

			DialogExit();
		break;

		//--> миниквесты портмана
		case "PortmanQuest":
		//HardCoffee пример использования нового dRand
			if (idRand(npchar.id + "shipLog", 2) == 2)
			{
				//квест догнать и передать судовой журнал
				dialog.text = StringFromKey("Common_Portman_236");
				link.l1 = StringFromKey("Common_Portman_237");
				link.l1.go = "PortmanQuest_1";
				link.l2 = StringFromKey("Common_Portman_238");
				link.l2.go = "node_2";
			}
			else
			{
				//квест разыскать украденный корабль
				dialog.text = StringFromKey("Common_Portman_239");
				link.l1 = StringFromKey("Common_Portman_240", pchar);
				link.l1.go = "SeekShip_1";
				link.l2 = StringFromKey("Common_Portman_241");
				link.l2.go = "node_2";
			}
		break;
		// -------------------------------- квест доставки судового журнала до рассеяного кэпа --------------------------
		case "PortmanQuest_1":
		// evganat - можно вставить отношение сюда
			IncreasePortmanDisposition(2);
			dialog.text = StringFromKey("Common_Portman_242");
			link.l1 = StringFromKey("Common_Portman_243");
			link.l1.go = "PortmanQuest_2";
			pchar.questTemp.different = "PortmansJornal";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetJornalCapParam(npchar);
			GiveItem2Character(pchar, "PortmansBook");
			pchar.questTemp.PortmansJornal.gem = GenQuestPortman_GenerateGem();
		break;
		case "PortmanQuest_2":
			dialog.text = StringFromKey("Common_Portman_244", npchar.quest.PortmansJornal.capName, GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Acc")), npchar.quest.PortmansJornal.shipName, XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			link.l1 = StringFromKey("Common_Portman_245");
			link.l1.go = "PortmanQuest_3";
		break;
		case "PortmanQuest_3":
			dialog.text = StringFromKey("Common_Portman_246", npchar.quest.PortmansJornal.capName);
			link.l1 = StringFromKey("Common_Portman_247", pchar);
			link.l1.go = "exit";
			sTitle = npchar.id + "PortmansBook_Delivery";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PortmansBook_Delivery", "1");
			AddQuestUserDataForTitle(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName + "Acc")));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansJornal.shipName);
			AddQuestUserData(sTitle, "sCapName", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sCapName2", npchar.quest.PortmansJornal.capName);
			AddQuestUserData(sTitle, "sTargetCity", XI_ConvertString("Colony" + npchar.quest.PortmansJornal.city + "Acc"));
			if (GetIslandNameByCity(npchar.quest.PortmansJornal.city) != npchar.quest.PortmansJornal.city)
			{
				AddQuestUserData(sTitle, "sAreal", StringFromKey("InfoMessages_6", XI_ConvertString(GetIslandNameByCity(npchar.quest.PortmansJornal.city) + "Pre")));
			}
		break;
		// -------------------------------- квест розыска украденного корабля ----------------------------------
		case "SeekShip_1":
			dialog.text = StringFromKey("Common_Portman_248");
			link.l1 = StringFromKey("Common_Portman_249");
			link.l1.go = "SeekShip_2";
			pchar.questTemp.different = "PortmansSeekShip";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			SetSeekShipCapParam(npchar);
		break;
		case "SeekShip_2":
			dialog.text = StringFromKey("Common_Portman_250", XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName), npchar.quest.PortmansSeekShip.shipName, FindDaysString(rand(5) + 10));
			link.l1 = StringFromKey("Common_Portman_251");
			link.l1.go = "SeekShip_3";
		break;
		case "SeekShip_3":
			dialog.text = StringFromKey("Common_Portman_252");
			link.l1 = StringFromKey("Common_Portman_253");
			link.l1.go = "exit";
			sTitle = npchar.id + "Portmans_SeekShip";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName)));
			AddQuestUserData(sTitle, "sShipName", npchar.quest.PortmansSeekShip.shipName);
		break;

		case "SeekShip_break":
		// evganat - можно вставить отношение сюда
			IncreasePortmanDisposition(-1);
			dialog.text = StringFromKey("Common_Portman_254");
			link.l1 = StringFromKey("Common_Portman_255");
			link.l1.go = "SeekShip_break_1";
		break;
		case "SeekShip_break_1":
			dialog.text = StringFromKey("Common_Portman_256");
			link.l1 = StringFromKey("Common_Portman_257");
			link.l1.go = "exit";
			sTemp = "SeekShip_checkAbordage" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на абордаж
			cn = GetCharacterIndex("SeekCap_" + npchar.index);
			//если кэп-вор ещё жив - убираем его
			if (cn > 0)
			{
				characters[cn].LifeDay = 0;
				Map_ReleaseQuestEncounter(characters[cn].id);
				group_DeleteGroup("SeekCapShip_" + characters[cn].index);
			}
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "7");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
			ChangeCharacterReputation(pchar, -7);
		break;

		case "SeekShip_good":
			if (npchar.quest == "SeekShip_sink")
			{
				// evganat - можно вставить отношение сюда
				IncreasePortmanDisposition(2);
				dialog.text = StringFromKey("Common_Portman_258");
				link.l1 = StringFromKey("Common_Portman_259");
				//npchar.quest.money = makeint(sti(npchar.quest.money) / 4); //снижаем оплату
				ChangeCharacterReputation(pchar, 5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 50);
				AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 20);
			}
			else
			{
				// evganat - можно вставить отношение сюда
				IncreasePortmanDisposition(3);
				dialog.text = StringFromKey("Common_Portman_260");
				link.l1 = StringFromKey("Common_Portman_261");
				ChangeCharacterReputation(pchar, 10);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
				AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 100);
				AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 150);
				AddCharacterExpToSkill(GetMainCharacter(), "Grappling", 100);
			}
			link.l1.go = "SeekShip_good_1";
		break;
		case "SeekShip_good_1":
			dialog.text = StringFromKey("Common_Portman_262", FindMoneyString(makeint(sti(npchar.quest.chest) * 15000)));
			link.l1 = StringFromKey("Common_Portman_263");
			link.l1.go = "exit";
			//AddMoneyToCharacter(pchar, sti(npchar.quest.money));
			TakeNItems(pchar, "chest", sti(npchar.quest.chest));
			sTitle = npchar.id + "Portmans_SeekShip";
			AddQuestRecordEx(sTitle, "Portmans_SeekShip", "6");
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.PortmansSeekShip");
			npchar.quest = ""; //освобождаем личный флаг квеста для портмана
		break;

		//------------------------------> инфа по базе квествых кэпов
		//ВНИМАНИЕ. в квестбук должна заносится типовая строка по примеру   PortmansBook_Delivery  #TEXT   5
		//в список портмана заносим тайтл, заголовок и номер строки из quest_text.txt
		//ПРИМЕР: в конце метода  void SetCapitainFromCityToSea(string qName)
		case "CapitainList":
			if (sti(npchar.quest.qty) > 0)
			{
				dialog.text = StringFromKey("Common_Portman_264");
				makearef(arCapBase, npchar.quest.capitainsList);
				int qCaps = 0;
				for (i = 0; i < sti(npchar.quest.qty); i++)
				{
					arCapLocal = GetAttributeN(arCapBase, i);
					sCapitainId = GetAttributeName(arCapLocal);
					if (!CheckAttribute(&NullCharacter, "capitainBase." + sCapitainId))    // evganat - не выводим закрытые квесты
						continue;
					qCaps++;
					sld = characterFromId(sCapitainId);
					attrL = "l" + i;
					link.(attrL) = StringFromKey("Common_Portman_265", GetFullName(sld), GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Acc")), sld.Ship.name);
					link.(attrL).go = "CapList_" + attrL;
				}
				if (qCaps == 0)
				{
					dialog.text = StringFromKey("Common_Portman_266");
					link.l1 = StringFromKey("Common_Portman_267");
					link.l1.go = "node_2";
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Portman_268");
				link.l1 = StringFromKey("Common_Portman_269");
				link.l1.go = "node_2";
			}
		break;
		// evganat - оптимизация поиска капитанов
		case "CapList_Check":
			makearef(arCapBase, npchar.quest.capitainsList);
			arCapLocal = GetAttributeN(arCapBase, sti(npchar.temp.caplist_num));
			sCapitainId = GetAttributeName(arCapLocal);
			sld = characterFromId(sCapitainId);
			dialog.text = StringFromKey("Common_Portman_273", LinkRandPhrase(
						StringFromKey("Common_Portman_270"),
						StringFromKey("Common_Portman_271"),
						StringFromKey("Common_Portman_272")), GetFullName(sld), arCapLocal.date, XI_ConvertString("Colony" + arCapLocal + "Acc"));
			link.l1 = StringFromKey("Common_Portman_274");
			link.l1.go = "CapitainList";
			link.l2 = StringFromKey("Common_Portman_275");
			link.l2.go = "node_2";
			//заносим запись в СЖ
			AddQuestRecordEx(arCapLocal.QBString1, arCapLocal.QBString2, arCapLocal.QBQty);
			AddQuestUserData(arCapLocal.QBString1, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(arCapLocal.QBString1, "sCapName", GetFullName(sld));
			AddQuestUserData(arCapLocal.QBString1, "sShipTypeName", GetStrSmallRegister(XI_ConvertString(RealShips[sti(sld.Ship.Type)].BaseName + "Pre")));
			AddQuestUserData(arCapLocal.QBString1, "sShipName", sld.Ship.name);
			AddQuestUserData(arCapLocal.QBString1, "sDate", arCapLocal.date);
			AddQuestUserData(arCapLocal.QBString1, "sTargetCity", XI_ConvertString("Colony" + arCapLocal + "Acc"));
			if (GetIslandNameByCity(arCapBase.(sCapitainId)) != arCapBase.(sCapitainId))
			{
				AddQuestUserData(arCapLocal.QBString1, "sAreal", StringFromKey("InfoMessages_6", XI_ConvertString(GetIslandNameByCity(arCapBase.(sCapitainId)) + "Pre")));
			}
			//убираем из списка
			DeleteAttribute(arCapBase, sCapitainId);
		break;
		//<--------------------------- инфа по базе квествых кэпов

		case "ShipStock_1":
			if (CheckAttribute(npchar, "dontGive"))
			{
				dialog.text = StringFromKey("Common_Portman_276", GetFullName(pchar));
				link.l1 = StringFromKey("Common_Portman_277", pchar);
				link.l1.go = "exit";
				break;
			}
			if (sti(NPChar.Portman) >= nShipStock)
			{
				dialog.text = StringFromKey("Common_Portman_278");
				Link.l1 = StringFromKey("Common_Portman_279");
				Link.l1.go = "exit";
			}
			else
			{
				ok = (sFrom_sea == "") || (Pchar.location.from_sea == sFrom_sea);
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchPortman(npchar);
				}
				else
				{
					dialog.text = StringFromKey("Common_Portman_280");
					Link.l1 = StringFromKey("Common_Portman_281", pchar);
					Link.l1.go = "exit";
				}
			}
		break;

		case "ShipStock_3":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForShip));
			chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
			chref.ShipInStockMan = NPChar.id;
			// Warship 22.03.09 fix Не перенеслось с КВЛ 1.2.3
			chref.ShipInStockMan.MoneyForShip = NPChar.MoneyForShip;
			chref.ShipInStockMan.AltDate = GetQuestBookDataDigit(); // для печати
			SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date"); // для расчёта
			// chref.Ship.Crew.Quantity  = 0;
			RemoveCharacterCompanion(pchar, chref);
			chref.location = "";
			chref.location.group = "";
			chref.location.locator = "";

			NPChar.Portman = sti(NPChar.Portman) + 1;
			pchar.ShipInStock = sti(pchar.ShipInStock) + 1;

			// evganat - можно вставить отношение сюда
			if (sti(NPChar.Portman) == 1)
				IncreasePortmanDisposition(1);

			dialog.text = StringFromKey("Common_Portman_282");
			Link.l1 = StringFromKey("Common_Portman_283");
			Link.l1.go = "exit";
		break;

		case "ShipStockReturn_1":
			if (sFrom_sea == "" || Pchar.location.from_sea == sFrom_sea || sti(Pchar.Ship.Type) == SHIP_NOTUSED)
			{
				if (GetCompanionQuantity(pchar) < COMPANION_MAX)
				{
					NextDiag.CurrentNode = NextDiag.TempNode;
					DialogExit();
					LaunchPortman(npchar);
				}
				else
				{
					dialog.text = StringFromKey("Common_Portman_284");
					Link.l1 = StringFromKey("Common_Portman_285");
					Link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Portman_286");
				Link.l1 = StringFromKey("Common_Portman_287");
				Link.l1.go = "exit";
			}
		break;

		//ОЗГ, Хоум
		case "Houm_portman_1":
			if (pchar.questTemp.Headhunter.City == npchar.city)
			{
				dialog.text = StringFromKey("Common_Portman_288");
				link.l1 = StringFromKey("Common_Portman_289");
				link.l1.go = "Houm_portman_yes";
			}
			else
			{
				dialog.text = StringFromKey("Common_Portman_290");
				link.l1 = StringFromKey("Common_Portman_291");
				link.l1.go = "exit";
			}
		break;

		case "Houm_portman_yes":
			pchar.questTemp.Headhunter = "houm_tavern";
			CreateHoum();
			AddQuestRecord("Headhunt", "5");
			AddQuestUserData("Headhunt", "sCity", pchar.questTemp.Headhunter.Cityname);
			DialogExit();
			RemoveLandQuestMark_Main(npchar, "Headhunt");
		break;
		//ОЗГ, Хоум

		// evganat - энциклопедия
		case "Encyclopedia_FirstTime":
			dialog.text = StringFromKey("Common_Portman_292");
			link.l1 = StringFromKey("Common_Portman_293");
			link.l1.go = "Encyclopedia_FT2";
		break;

		case "Encyclopedia_FT2":
			if (CheckRandomPage("portman", npchar.city, sti(npchar.nation)))
			{
				npchar.encyclopedia.tome = GetRandomTome();
				npchar.encyclopedia.page = 4;
				dialog.text = StringFromKey("Common_Portman_294");
				link.l1 = StringFromKey("Common_Portman_295");
				link.l1.go = "Encyclopedia_Price";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(npchar, "encyclopedia.last_date");
				dialog.text = StringFromKey("Common_Portman_296");
				link.l1 = StringFromKey("Common_Portman_297");
				link.l1.go = "exit";
			}
		break;

		case "Encyclopedia_Price":
			bool bDispG = (GetPortmanDisposition() >= 7);    // отношение
			bool bRepG = (sti(pchar.reputation) > 60);        // репутация "честный капитан" и выше
			bool bRepB = (sti(pchar.reputation) <= 20);        // репутация "негодяй" и ниже
			bool bLeadG = (GetCharacterSkill(pchar, SKILL_LEADERSHIP) >= 50);    // лидерство
			bool bLeadB = (GetCharacterSkill(pchar, SKILL_LEADERSHIP) <= 20);
			bool bSailG = (GetCharacterSkill(pchar, SKILL_SAILING) >= 50);    // навигация
			bool bSailB = (GetCharacterSkill(pchar, SKILL_SAILING) <= 20);
			int iScore = bDispG + bDispG + bRepG - bRepB + bLeadG - bLeadB + bSailG - bSailB;
			if (bRepB)
			{
				PlayerRPGCheck_Reputation_NotifyFail("good");
			}
			if (bLeadB)
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
			}
			if (bSailB)
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_SAILING, false);
			}

			int iPrice;
			if (iScore == 5)    // всё идеально, бесплатно
			{
				iPrice = 0;
				dialog.text = StringFromKey("Common_Portman_298");
				link.l1 = StringFromKey("Common_Portman_299", pchar);
				link.l1.go = "Encyclopedia_AddPage";
				break;
			}

			if (iScore >= -1)
			{
				iPrice = 16000;
				dialog.text = StringFromKey("Common_Portman_300", FindMoneyString(iPrice));
			}

			if (iScore >= 1)    // так себе, по минимуму, цена 12000
			{
				iPrice = 8000;
				dialog.text = StringFromKey("Common_Portman_301", FindMoneyString(iPrice));
			}

			if (iScore >= 3)    // неидеально, но плюсов больше, цена 4000
			{
				iPrice = 4000;
				dialog.text = StringFromKey("Common_Portman_302", FindMoneyString(iPrice));
			}

			if (iScore < -1)    // ужас, 36000
			{
				iPrice = 32000;
				dialog.text = StringFromKey("Common_Portman_303", FindMoneyString(iPrice));
			}
			npchar.encyclopedia.curPrice = iPrice;
			if (sti(pchar.money) >= iPrice)
			{
				link.l1 = StringFromKey("Common_Portman_304");
				link.l1.go = "Encyclopedia_Buy";
			}
			link.l2 = StringFromKey("Common_Portman_305");
			link.l2.go = "exit";
		break;

		////////////////////////////////////////////////homo линейка Блада/////////////////////////////////////////
		case "Blood_Portman1":
			dialog.text = StringFromKey("Common_Portman_306");
			link.l1 = StringFromKey("Common_Portman_307");
			link.l1.go = "Blood_Portman2";
			link.l2 = StringFromKey("Common_Portman_308");
			link.l2.go = "Blood_Portman3";
			link.l3 = StringFromKey("Common_Portman_309");
			link.l3.go = "Blood_Portman4";
		break;

		case "Blood_Portman2":
			dialog.text = StringFromKey("Common_Portman_310");
			link.l1 = StringFromKey("Common_Portman_311");
			link.l1.go = "Blood_Portman5";
		break;

		case "Blood_Portman3":
		//			if (GetCharacterSPECIAL(pchar, SPECIAL_C) >= 9)
			if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 9))
			{
				dialog.text = StringFromKey("Common_Portman_312");
				link.l1 = StringFromKey("Common_Portman_313");
				link.l1.go = "Blood_Portman9";
			}
			else
			{
				dialog.text = StringFromKey("Common_Portman_314");
				link.l1 = StringFromKey("Common_Portman_315");
				link.l1.go = "Exit";
				AddQuestRecord("PirateQuest", "6");
				CloseQuestHeader("PirateQuest");  // Провал квеста
				Pchar.questTemp.CapBloodLine.ShipForJack = false;
				RemoveLandQuestmark_Main(npchar, "CapBloodLine");
				QuestPointerDelLoc("Bridgetown_town", "reload", "reload10_back");

				if (!CheckAttribute(PChar, "questTemp.CapBloodLine.QuestRaff"))
					QuestPointerToLocEx("Bridgetown_town", "reload", "reload8_back", "BloodLine_UsurerQuest");
			}
		break;

		case "Blood_Portman4":
			dialog.text = StringFromKey("Common_Portman_316");
			link.l1 = StringFromKey("Common_Portman_317");
			link.l1.go = "Blood_Portman6";
		break;

		case "Blood_Portman5":
		// Проверка харизмы: если ≥5 - успех, если нет - провал
		//			if (GetCharacterSPECIAL(pchar, SPECIAL_C) >= 5)
			if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 5))
			{
				dialog.text = StringFromKey("Common_Portman_318");
				link.l1 = StringFromKey("Common_Portman_319");
				link.l1.go = "Exit";
				LoginMainer();  // Запускаем следующую часть квеста
				AddQuestRecord("PirateQuest", "2");
				AddCharacterExpToSkill(pchar, "Sneak", 70);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
				RemoveLandQuestmark_Main(npchar, "CapBloodLine");
				QuestPointerDelLoc("Bridgetown_town", "reload", "reload10_back");
			}
			else
			{
				dialog.text = StringFromKey("Common_Portman_320");
				link.l1 = StringFromKey("Common_Portman_321");
				link.l1.go = "exit";
				AddQuestRecord("PirateQuest", "6");
				CloseQuestHeader("PirateQuest");  // Провал квеста
				Pchar.questTemp.CapBloodLine.ShipForJack = false;
				RemoveLandQuestmark_Main(npchar, "CapBloodLine");
				QuestPointerDelLoc("Bridgetown_town", "reload", "reload10_back");

				if (!CheckAttribute(PChar, "questTemp.CapBloodLine.QuestRaff"))
					QuestPointerToLocEx("Bridgetown_town", "reload", "reload8_back", "BloodLine_UsurerQuest");
			}
		break;

		case "Blood_Portman6":
			dialog.text = StringFromKey("Common_Portman_322");
			link.l1 = StringFromKey("Common_Portman_323");
			link.l1.go = "Blood_Portman7";
		break;

		case "Blood_Portman7":
			dialog.text = StringFromKey("Common_Portman_324");
			link.l1 = StringFromKey("Common_Portman_325");
			link.l1.go = "Blood_Portman8";
		break;

		case "Blood_Portman8":
			dialog.text = StringFromKey("Common_Portman_326");
			link.l1 = StringFromKey("Common_Portman_327");
			link.l1.go = "Blood_Portman10";
			link.l2 = StringFromKey("Common_Portman_328");
			link.l2.go = "Blood_Portman12";
		break;

		case "Blood_Portman9":
			dialog.text = StringFromKey("Common_Portman_329");
			link.l1 = StringFromKey("Common_Portman_330");
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "2");
			AddCharacterExpToSkill(pchar, "Sneak", 120);
			AddCharacterExpToSkill(PChar, "Sailing", 120);
			AddCharacterExpToSkill(PChar, "Accuracy", 120);
			AddCharacterExpToSkill(PChar, "Cannons", 120);
			AddCharacterExpToSkill(PChar, "Repair", 120);
			AddCharacterExpToSkill(PChar, "Defence", 120);
			AddCharacterExpToSkill(PChar, "Sneak", 120);
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload10_back");
		break;

		case "Blood_Portman10":
			dialog.text = StringFromKey("Common_Portman_331");
			link.l1 = StringFromKey("Common_Portman_332");
			link.l1.go = "Blood_Portman11";
		break;

		case "Blood_Portman11":
			dialog.text = StringFromKey("Common_Portman_333");
			link.l1 = StringFromKey("Common_Portman_334");
			link.l1.go = "Blood_Portman12";
		break;

		case "Blood_Portman12":
			dialog.text = StringFromKey("Common_Portman_335");
			link.l1 = StringFromKey("Common_Portman_336");
			link.l1.go = "Exit";
			LoginMainer();
			AddQuestRecord("PirateQuest", "3");
			AddCharacterExpToSkill(PChar, "Sailing", 40);
			AddCharacterExpToSkill(PChar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 40);
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload10_back");
		break;
		///

		case "Encyclopedia_Buy":
			AddMoneyToCharacter(pchar, -sti(npchar.encyclopedia.curPrice));
			DeleteAttribute(npchar, "encyclopedia.curPrice");
			dialog.text = StringFromKey("Common_Portman_337");
			link.l1 = StringFromKey("Common_Portman_338");
			link.l1.go = "Encyclopedia_AddPage";
		break;

		case "Encyclopedia_AddPage":
			GetPage(npchar.encyclopedia.tome, sti(npchar.encyclopedia.page));
			DeleteAttribute(npchar, "encyclopedia.tome");
			DeleteAttribute(npchar, "encyclopedia.page");
			SaveCurrentNpcQuestDateParam(npchar, "encyclopedia.last_date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Encyclopedia_Return":
			dialog.text = StringFromKey("Common_Portman_339", FindMoneyString(sti(npchar.encyclopedia.curPrice)));
			if (sti(pchar.money) >= sti(npchar.encyclopedia.curPrice))
			{
				link.l1 = StringFromKey("Common_Portman_340");
				link.l1.go = "Encyclopedia_Buy";
			}
			link.l2 = StringFromKey("Common_Portman_341");
			link.l2.go = "exit";
		break;

		case "Encyclopedia_Check":
			if (CheckAttribute(pchar, "encyclopedia.gen.portman.colonies." + npchar.city) && sti(pchar.encyclopedia.gen.portman.colonies) < 10)
			{
				dialog.text = StringFromKey("Common_Portman_342");
				link.l1 = StringFromKey("Common_Portman_343");
				link.l1.go = "exit";
				break;
			}

			if (GetNpcQuestPastDayParam(npchar, "encyclopedia.last_date") < 7)
			{
				dialog.text = StringFromKey("Common_Portman_344");
				link.l1 = StringFromKey("Common_Portman_345", pchar);
				link.l1.go = "exit";
			}
			else
			{
				if (CheckRandomPage("portman", npchar.city, sti(npchar.nation)))
				{
					npchar.encyclopedia.tome = GetRandomTome();
					npchar.encyclopedia.page = 4;
					dialog.text = StringFromKey("Common_Portman_346");
					link.l1 = StringFromKey("Common_Portman_347", pchar);
					link.l1.go = "Encyclopedia_Price";
				}
				else
				{
					SaveCurrentNpcQuestDateParam(npchar, "encyclopedia.last_date");
					dialog.text = StringFromKey("Common_Portman_348");
					link.l1 = StringFromKey("Common_Portman_349");
					link.l1.go = "exit";
				}
			}
		break;
	}
}

float BurntShipQuest_GetMaxNeededValue(int iShipType, string _param)
{
	float NeededValue = makefloat(GetBaseShipParamFromType(iShipType, _param));
	switch (_param)
	{
		case "speedrate":
			NeededValue += ((0.79 + frandSmall(0.32)) * (NeededValue / 10.0));
		break;
		case "turnrate":
			NeededValue += ((0.79 + frandSmall(0.32)) * (NeededValue / 10.0));
		break;
		case "capacity":
			NeededValue += ((0.79 + frandSmall(0.32)) * (NeededValue / 8.0));
		break;
	}
	return NeededValue;
}

// Warship 25.07.09 Генер "Сгоревшее судно". Начальные иниты для портмана - тип разыскиваемого судна, выдающаяся характеристика и т.д.
void BurntShipQuest_FillStartParams(ref _npchar)
{
	int rank = sti(PChar.rank);
	int shipType, temp;
	float neededValue;
	string shipAttribute;

	// TODO Пересмотреть зависимость от ранга
	// Rosarak: fix с адаптацией под новый ship.h, нужно в каждом кейсе shipType указывать из-за новых кораблей между старыми типами
	if (rank <= 5)
	{
		switch (rand(1))
		{
			case 0:
				shipType = SHIP_LUGGER;
				shipAttribute = "speedrate";
			//				neededValue = 16.74 + fRandSmall(0.15);
			break;

			case 1:
				shipType = SHIP_LUGGER;
				temp = rand(2);

				if (temp == 2)
				{
					//					neededValue = 14.9 + fRandSmall(0.14);
					shipAttribute = "speedrate";
				}
				else
				{
					if (temp == 1)
					{
						//						neededValue = 42.12 + fRandSmall(0.4);
						shipAttribute = "turnrate";
					}
					else
					{
						//						neededValue = 864 + rand(8);
						shipAttribute = "capacity";
					}
				}
			break;
		}
	}

	if (rank > 5 && rank <= 15)
	{
		switch (rand(2))
		{
			case 0:
				shipType = SHIP_SCHOONER;
				if (rand(1) == 0)
				{
					//					neededValue = 14.04 + fRandSmall(0.13);
					shipAttribute = "speedrate";
				}
				else
				{
					//					neededValue = 37.8 + fRandSmall(0.35);
					shipAttribute = "turnrate";
				}
			break;

			case 1:
				shipType = SHIP_BARQUE;
				//				neededValue = 1836 + rand(170);
				shipAttribute = "capacity";
			break;

			case 2:
				shipType = SHIP_CARAVEL;
				//				neededValue = 3240 + rand(30);
				shipAttribute = "capacity";
			break;
		}
	}

	if (rank > 15 && rank <= 25)
	{
		switch (rand(4))
		{
			case 0:
				shipType = SHIP_BARKENTINE;
				//				neededValue = 43.2 + fRandSmall(0.4);
				shipAttribute = "turnrate";
			break;

			case 1:
				shipType = SHIP_BRIGANTINE;
				if (rand(1) == 1)
				{
					//					neededValue = 16.74 + fRandSmall(0.16);
					shipAttribute = "speedrate";
				}
				else
				{
					//					neededValue = 54.0 + fRandSmall(0.5);
					shipAttribute = "turnrate";
				}
			break;

			case 2:
				shipType = SHIP_FLEUT;
				//				neededValue = 3240 + rand(30);
				shipAttribute = "capacity";
			break;

			case 3:
				shipType = SHIP_BRIG;
				if (rand(1) == 1)
				{
					//					neededValue = 15.66 + fRandSmall(0.15);
					shipAttribute = "speedrate";
				}
				else
				{
					//					neededValue = 48.6 + fRandSmall(0.45);
					shipAttribute = "turnrate";
				}
			break;

			case 4:
				shipType = SHIP_GALEON_L;
				//				neededValue = 3672 + rand(34);
				shipAttribute = "capacity";
			break;
		}
	}

	if (rank > 25 && rank <= 35)
	{
		switch (rand(2))
		{
			case 0:
				shipType = SHIP_CORVETTE;
				if (rand(1) == 1)
				{
					//					neededValue = 17.5 + fRandSmall(0.16);
					shipAttribute = "speedrate";
				}
				else
				{
					//					neededValue = 59.4 + fRandSmall(0.55);
					shipAttribute = "turnrate";
				}
			break;

			case 1:
				shipType = SHIP_GALEON_H;
				//				neededValue = 5022 + rand(47);
				shipAttribute = "capacity";
			break;

			case 2:
				shipType = SHIP_PINNACE;
				if (rand(1) == 1)
				{
					//					neededValue = 14.04 + fRandSmall(0.13);
					shipAttribute = "speedrate";
				}
				else
				{
					//					neededValue = 4320 + rand(40);
					shipAttribute = "capacity";
				}
			break;
		}
	}

	if (rank > 35)
	{
		switch (rand(1))
		{
			case 0:
				shipType = SHIP_FRIGATE;
				temp = rand(2);

				if (temp == 0)
				{
					//					neededValue = 15.44 + fRandSmall(0.14);
					shipAttribute = "speedrate";
				}
				else
				{
					if (temp == 1)
					{
						//						neededValue = 41.04 + fRandSmall(0.38);
						shipAttribute = "turnrate";
					}
					else
					{
						//						neededValue = 3240 + rand(30);
						shipAttribute = "capacity";
					}
				}
			break;

			// Это варшип
			case 1:
				shipType = SHIP_LINESHIP;
				//				neededValue = 38.88 + fRandSmall(0.36);
				shipAttribute = "turnrate";
			break;
		}
	}

	neededValue = BurntShipQuest_GetMaxNeededValue(shipType, shipAttribute);

	Log_TestInfo("shipType == " + shipType);
	Log_TestInfo("ShipAttribute == " + shipAttribute);
	Log_TestInfo("ShipNeededValue == " + neededValue);

	_npchar.Quest.BurntShip.ShipType = shipType;
	_npchar.Quest.BurntShip.ShipAttribute = shipAttribute;

	if (shipAttribute != "capacity") // Чтобы трюм с десятичными не писался
	{
		_npchar.Quest.BurntShip.ShipNeededValue = FloatToString(neededValue, 2);
	}
	else
	{
		_npchar.Quest.BurntShip.ShipNeededValue = MakeInt(neededValue);
	}
}

void SetJornalCapParam(ref npchar)
{
	//созадем рассеянного кэпа
	ref sld = GetCharacter(NPC_GenerateCharacter("PortmansCap_" + npchar.index, "", "man", "man", 20, sti(npchar.nation), -1, true));
	SetCaptanModelByEncType(sld, "trade");
	SetShipToFantom(sld, "trade", true);
	sld.Ship.Mode = "trade";
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "PortmansCap";
	sld.DeckDialogNode = "PortmansCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "ShipTurnRateUp");
	LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
	//в морскую группу кэпа
	string sGroup = "PorpmansShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetType(sGroup, "trade");
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansJornal"; //личный флаг квеста для портмана
	npchar.quest.PortmansJornal.capName = GetFullName(sld); //имя кэпа
	npchar.quest.PortmansJornal.shipName = sld.Ship.name; //имя корабля
	npchar.quest.PortmansJornal.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название корабля
	npchar.quest.PortmansJornal.city = SelectNotEnemyColony(npchar); //определим колонию, куда ушёл кэп
	sld.quest = "InMap"; //личный флаг рассеянного кэпа
	sld.quest.targetCity = npchar.quest.PortmansJornal.city; //продублируем колонию-цель в структуру кэпа
	sld.quest.firstCity = npchar.city; //капитану знать откуда вышел в самом начале
	sld.quest.stepsQty = 1; //количество выходов в море
	sld.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype) + 1) * 150) + (sti(pchar.rank) * 150); //вознаграждение
	Log_TestInfo("Рассеянный кэп " + sld.id + " направился в: " + sld.quest.targetCity);
	//определим бухту, куда ставить энкаунтер. чтобы сразу не генерился перед ГГ у города
	string sTemp = GetArealByCityName(npchar.city);
	sld.quest.baseShore = GetIslandRandomShoreId(sTemp);
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "ranger";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansJornal.shipTapeName) + " '" + npchar.quest.PortmansJornal.shipName + "'";
	int daysQty = GetMaxDaysFromColony2Colony(npchar.city, sld.quest.targetCity) + 5; //дней доехать даем с запасом
	Map_CreateTrader(sld.quest.baseShore, sld.quest.targetCity, sld.id, daysQty);
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "jornal"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "PortmansBook_Delivery"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "PortmansBook_Delivery"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
	// квест-метка
	AddLandQuestMark_Gen(sld, "PortmansBook_Delivery");
}
//проверить список отметившихся квестовых кэпов
int CheckCapitainsList(ref npchar)
{
	int bResult = 0;
	if (!CheckAttribute(npchar, "quest.capitainsList")) return bResult;
	aref arCapBase, arCapLocal;
	makearef(arCapBase, npchar.quest.capitainsList);
	int Qty = GetAttributesNum(arCapBase);
	if (Qty < 1) return bResult;
	string sCapitainId;
	for (int i = 0; i < Qty; i++)
	{
		arCapLocal = GetAttributeN(arCapBase, i);
		sCapitainId = GetAttributeName(arCapLocal);
		if (GetCharacterIndex(sCapitainId) > 0) //если ещё жив
		{
			bResult++;
		}
		else
		{
			DeleteAttribute(arCapBase, sCapitainId);
			i--;
			Qty--;
		}
	}
	if (bResult > 5) bResult = 5;
	return bResult;
}

void SetSeekShipCapParam(ref npchar)
{
	//создаем кэпа-вора
	int Rank = sti(pchar.rank) + 5;
	if (Rank > 30) Rank = 30;
	ref sld = GetCharacter(NPC_GenerateCharacter("SeekCap_" + npchar.index, "", "man", "man", Rank, PIRATE, -1, true));
	SetCaptanModelByEncType(sld, "pirate");
	SetShipToFantom(sld, "pirate", true);
	sld.Ship.Mode = "pirate";
	sld.dialog.filename = "Quest\ForAll_dialog.c";
	sld.dialog.currentnode = "SeekCap";
	sld.DeckDialogNode = "SeekCap_inDeck";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	SetCharacterPerk(sld, "FastReload");
	SetCharacterPerk(sld, "HullDamageUp");
	SetCharacterPerk(sld, "SailsDamageUp");
	SetCharacterPerk(sld, "CrewDamageUp");
	SetCharacterPerk(sld, "CriticalShoot");
	SetCharacterPerk(sld, "LongRangeShoot");
	SetCharacterPerk(sld, "CannonProfessional");
	SetCharacterPerk(sld, "ShipDefenseProfessional");
	SetCharacterPerk(sld, "ShipTurnRateUp");
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	//в морскую группу кэпа
	string sGroup = "SeekCapShip_" + sld.index;
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	//записываем данные в структуры портмана и кэпа
	npchar.quest = "PortmansSeekShip"; //личный флаг квеста для портмана
	npchar.quest.PortmansSeekShip.capName = GetFullName(sld); //имя кэпа-вора
	npchar.quest.PortmansSeekShip.shipName = sld.Ship.name; //имя украденного корабля
	npchar.quest.PortmansSeekShip.shipTapeName = RealShips[sti(sld.Ship.Type)].BaseName; //название украденного корабля
	npchar.quest.PortmansSeekShip.shipTape = RealShips[sti(sld.Ship.Type)].basetype; //тип украденного корабля
	//npchar.quest.money = ((sti(RealShips[sti(sld.Ship.Type)].basetype)+1) * 1000) + (sti(pchar.rank)*500); //вознаграждение
	npchar.quest.chest = 7 - sti(RealShips[sti(sld.Ship.Type)].Class); //в сундуках
	sld.quest = "InMap"; //личный флаг кэпа-вора
	sld.city = SelectAnyColony(npchar.city); //определим колонию, откуда кэп-вор выйдет
	sld.quest.targetCity = SelectAnyColony2(npchar.city, sld.city); //определим колонию, куда он придет
	Log_TestInfo("Кэп-вор " + sld.id + " вышел из: " + sld.city + " и направился в: " + sld.quest.targetCity + "");
	sld.quest.cribCity = npchar.city; //город, откуда кэп-вор спер корабль
	//на карту
	sld.mapEnc.type = "trade";
	sld.mapEnc.worldMapShip = "Galleon_red";
	sld.mapEnc.Name = XI_ConvertString(npchar.quest.PortmansSeekShip.shipTapeName) + " '" + npchar.quest.PortmansSeekShip.shipName + "'";
	int daysQty = GetMaxDaysFromColony2Colony(sld.quest.targetCity, sld.city) + 3; //дней доехать даем с запасом
	Map_CreateTrader(sld.city, sld.quest.targetCity, sld.id, daysQty);
	//прерывание на абордаж
	string sTemp = "SeekShip_checkAbordage" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_Capture";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkAbordage";
	pchar.quest.(sTemp).CapId = sld.id;
	//прерывание на потопление без абордажа
	sTemp = "SeekShip_checkSink" + npchar.index;
	pchar.quest.(sTemp).win_condition.l1 = "Character_sink";
	pchar.quest.(sTemp).win_condition.l1.character = sld.id;
	pchar.quest.(sTemp).function = "SeekShip_checkSink";
	pchar.quest.(sTemp).CapId = sld.id;
	//заносим Id кэпа в базу нпс-кэпов
	sTemp = sld.id;
	NullCharacter.capitainBase.(sTemp).quest = "robber"; //идентификатор квеста
	NullCharacter.capitainBase.(sTemp).questGiver = "none"; //запомним Id квестодателя для затирки в случае чего
	NullCharacter.capitainBase.(sTemp).Tilte1 = npchar.id + "Portmans_SeekShip"; //заголовок квестбука
	NullCharacter.capitainBase.(sTemp).Tilte2 = "Portmans_SeekShip"; //имя квеста в квестбуке
	NullCharacter.capitainBase.(sTemp).checkTime = daysQty + 5;
	NullCharacter.capitainBase.(sTemp).checkTime.control_day = GetDataDay();
	NullCharacter.capitainBase.(sTemp).checkTime.control_month = GetDataMonth();
	NullCharacter.capitainBase.(sTemp).checkTime.control_year = GetDataYear();
}

string GenQuestPortman_GenerateGem() // камни
{
	string itemID;
	switch (rand(5))
	{
		case 0:
			itemID = "jewelry1";
		break;
		case 1:
			itemID = "jewelry2";
		break;
		case 2:
			itemID = "jewelry3";
		break;
		case 3:
			itemID = "jewelry3";
		break;
		case 4:
			itemID = "jewelry5";
		break;
		case 5:
			itemID = "jewelry17";
		break;
	}
	return itemID;
}

void CommonGenerator(string sCharID)
{
	dialogDisable = true;
	ref chr = characterFromID(sCharID);

	if (GetCharacterIndex(chr.id) >= 0)
		ChangeCharacterAddressGroup(characterFromID(sCharID), "none", "", "");
}

// evganat - отношение портмана
void IncreasePortmanDisposition(int add)
{
	IncreaseNPCDisposition(CharacterRef, add);
}

int GetPortmanDisposition()
{
	return GetNPCDisposition(CharacterRef);
}

/*
	Отношение:
	+2 передача документов
	+4 возвращение дочери
	+3 блудный сын, благодарность
	-2 блудный сын, неблагодарность
	-2 отказ от задания со сгоревшим судном
	+4 выполнение задания со сгоревшим судном
	+2 взял задание на доставку журнала
	-1 отказ от задания с украденным кораблём
	+2 выполнение задания с украденным кораблём, вернул другой
	+3 выполнение задания с украденным кораблём
	+1, если хранятся корабли (любое количество)
	
	Нужно от 4
*/
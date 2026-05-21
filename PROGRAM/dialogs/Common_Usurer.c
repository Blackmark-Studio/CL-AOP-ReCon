// boal 25/04/04 общий диалог Usurer
#include "DIALOGS\Rumours\Simple_rumors.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, chr, sld;
	aref Link, NextDiag, aItems;
	string NPC_Area, sTemp, sTitle;
	int LoanSum, LoanInterest, LoanPeriod, LoanResult, iPastMonths, DepositSum, DepositInterest, DepositResult, iNum, iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, s1;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	NPC_Area = Npchar.City;

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Usurer\" + NPChar.City + "_Usurer.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	if (!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}

	if (!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	}

	if (!CheckAttribute(npchar, "quest.FindCitizenNoShip"))
	{
		npchar.quest.FindCitizenNoShip = 0;
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
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				if (pchar.questTemp.Slavetrader == "After_enterSoldiers" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
				{
					dialog.text = StringFromKey("Common_Usurer_1", pchar.name);
					link.l1 = StringFromKey("Common_Usurer_2");
					link.l1.go = "exit";
					break;
				}
				//работорговец
				//проклятый идол
				if (CheckAttribute(pchar, "questTemp.PDM_CI_RostBlago"))
				{
					// evganat - можно вставить отношение сюда
					IncreaseUsurerDisposition(2);
					dialog.text = StringFromKey("Common_Usurer_3", pchar.name);
					link.l1 = StringFromKey("Common_Usurer_4");
					link.l1.go = "exit";
					break;
				}

				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Usurer_8", LinkRandPhrase(
								StringFromKey("Common_Usurer_5"),
								StringFromKey("Common_Usurer_6"),
								StringFromKey("Common_Usurer_7", pchar))),
						StringFromKey("Common_Usurer_12", LinkRandPhrase(
								StringFromKey("Common_Usurer_9", pchar),
								StringFromKey("Common_Usurer_10", pchar),
								StringFromKey("Common_Usurer_11", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Usurer_15", RandPhraseSimple(
								StringFromKey("Common_Usurer_13"),
								StringFromKey("Common_Usurer_14"))),
						StringFromKey("Common_Usurer_18", RandPhraseSimple(
								StringFromKey("Common_Usurer_16", GetWorkTypeOfMan(npchar, "")),
								StringFromKey("Common_Usurer_17", GetWorkTypeOfMan(npchar, "")))));
				link.l1.go = "fight";
				break;
			}

			//homo Линейка Блада
			if (Pchar.questTemp.CapBloodLine == true)
			{
				if (Pchar.questTemp.CapBloodLine.stat == "needMoney" && !CheckAttribute(pchar, "questTemp.CapBloodLine.QuestRaff"))
				{
					dialog.text = StringFromKey("Common_Usurer_19");
					Link.l1 = StringFromKey("Common_Usurer_20");
					Link.l1.go = "CapBloodUsurer_5";
					break;
				}
				dialog.Text = StringFromKey("Common_Usurer_24", LinkRandPhrase(
							StringFromKey("Common_Usurer_21", TimeGreeting()),
							StringFromKey("Common_Usurer_22"),
							StringFromKey("Common_Usurer_23", GetFullName(pchar))));
				Link.l1 = StringFromKey("Common_Usurer_25", NPChar.name);
				Link.l1.go = "exit";
				if (CheckAttribute(Pchar, "questTemp.CapBloodLine.Ogl") && Pchar.questTemp.CapBloodLine.Ogl == false)//homo линейка Блада
				{
					Link.l2 = StringFromKey("Common_Usurer_26");
					Link.l2.go = "CapBloodUsurer_1";
				}
				break;
			}
			//пиратка, квест №5, заглушка на возврат бабла -->
			if (CheckAttribute(npchar, "PLQ5Money"))
			{
				dialog.text = StringFromKey("Common_Usurer_27");
				link.l1 = StringFromKey("Common_Usurer_28");
				link.l1.go = "exit";
				link.l2 = StringFromKey("Common_Usurer_29", pchar);
				link.l2.go = "StepPL5End_close";
				if (sti(pchar.money) >= 50000)
				{
					link.l3 = StringFromKey("Common_Usurer_30", pchar);
					link.l3.go = "StepPL5End_1";
				}
				break;
			}
			//<--пиратка, квест №5, заглушка на возврат бабла

			//-->работорговец
			if (pchar.questTemp.Slavetrader == "canTakeQuest" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = StringFromKey("Common_Usurer_31", pchar);
				Link.l1 = StringFromKey("Common_Usurer_32");
				Link.l1.go = "GiveTaskSlave";
				npchar.quest.slave = "current";//чтобы камнем не долбил
				break;
			}

			if (pchar.questTemp.Slavetrader == "TakeShoreCap_end" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = "...";
				Link.l1 = StringFromKey("Common_Usurer_33", pchar);
				Link.l1.go = "Slaveshore_5";
				break;
			}
			if (pchar.questTemp.Slavetrader == "Win_HavanaFort" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = StringFromKey("Common_Usurer_34");
				Link.l1 = StringFromKey("Common_Usurer_35", pchar);
				Link.l1.go = "Win_Havana_Fort";
				break;
			}
			if (pchar.questTemp.Slavetrader == "Havana_seekslaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = StringFromKey("Common_Usurer_36");
				if (GetSquadronGoods(Pchar, GOOD_SLAVES) >= 5000)
				{
					Link.l1 = StringFromKey("Common_Usurer_37", pchar);
					Link.l1.go = "Havana_Fort_yesA";
				}
				else
				{
					Link.l1 = StringFromKey("Common_Usurer_38");
					Link.l1.go = "exit";
				}
				break;
			}

			if (pchar.questTemp.Slavetrader == "End_quest_bad" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(-20);
				dialog.Text = StringFromKey("Common_Usurer_39");
				link.l1 = StringFromKey("Common_Usurer_40");
				link.l1.go = "exit";
				LAi_group_Attack(NPChar, Pchar);
				break;
			}

			if (pchar.questTemp.Slavetrader == "wait_6" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_6") > 6 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				dialog.Text = StringFromKey("Common_Usurer_41", GetFullName(npchar));
				link.l1 = StringFromKey("Common_Usurer_42");
				link.l1.go = "Usurer_Escape";
				break;
			}
			//<--работорговец

			//-->> дача квеста найти потерянный драгоценный камень
			//HardCoffee пример использования нового idRand. В качестве уникального идентификатора взят id персонажа, с дополнительной припиской "gem" - то есть, квест на поиск камня
			if (idRand(npchar.id + "gem", 1) && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.usurersJewel") && GetNpcQuestPastDayWOInit(npchar, "usurersJewel") > 7 && !CheckAttribute(pchar, "questTemp.different.SeekUsurersJewel") && !CheckAttrValue(npchar, "City", "Charles") && !CheckAttribute(npchar, "quest.slave"))
			{
				dialog.text = StringFromKey("Common_Usurer_43");
				link.l1 = StringFromKey("Common_Usurer_44");
				link.l1.go = "usurersJewel_1";
				npchar.quest.usurersJewel = "inSeek"; //личный флаг ростовщика на взятый квест
				SaveCurrentNpcQuestDateParam(npchar, "usurersJewel");
				break;
			}
			//<<-- дача квеста найти потерянный драгоценный камень
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Common_Usurer_45", GetAddress_Form(npchar)),
						StringFromKey("Common_Usurer_46", GetAddress_Form(npchar)),
						StringFromKey("Common_Usurer_47", GetAddress_Form(npchar)),
						StringFromKey("Common_Usurer_48", GetAddress_Form(npchar)), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Common_Usurer_49", pchar),
						StringFromKey("Common_Usurer_50", pchar),
						StringFromKey("Common_Usurer_51", pchar),
						StringFromKey("Common_Usurer_52", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			link.l2 = StringFromKey("Common_Usurer_53");
			link.l2.go = "LoanUsurer";//(на кредитный генератор)
			link.l3 = StringFromKey("Common_Usurer_54");
			link.l3.go = "quests";//(перессылка в файл города)
			link.l4 = StringFromKey("Common_Usurer_57", RandPhraseSimple(
						StringFromKey("Common_Usurer_55"),
						StringFromKey("Common_Usurer_56")));
			link.l4.go = "items";
			//HardCoffee обмен молюсков -->
			if (GetSquadronGoods(pchar, GOOD_PINCTADA) > sti(Goods[GOOD_PINCTADA].Units))
			{
				if (CheckAttribute(NPChar, "pinctadosMakeADeal"))
				{
					link.GetRidOfPinctados = StringFromKey("Common_Usurer_700", LinkRandPhrase(
						StringFromKey("Common_Usurer_691", pchar, GetFirstName(NPChar)),
						StringFromKey("Common_Usurer_692"),
						StringFromKey("Common_Usurer_693", pchar)));
					link.GetRidOfPinctados.go = "pinctadosAgain";
				}
				else
				{
					link.GetRidOfPinctados = StringFromKey("Common_Usurer_680");
					link.GetRidOfPinctados.go = "pinctadosOffer";
				}
			}
			// обмен молюсков <--
			//линейка ГПК, закладка миллиона на депозит
			if (CheckAttribute(pchar, "questTemp.LSC.usurerId") && pchar.questTemp.LSC.usurerId == npchar.id)
			{
				if (pchar.questTemp.LSC == "SignOnPoorMurder")
				{
					link.l7 = StringFromKey("Common_Usurer_58");
					link.l7.go = "ISS_deposit";
				}
				if (pchar.questTemp.LSC == "PoorMurderExecute")
				{
					link.l7 = StringFromKey("Common_Usurer_59");
					link.l7.go = "ISS_takeDeposit";
				}
			}
			//квесты мэра, проникновение во враждебный город
			if (CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l9 = StringFromKey("Common_Usurer_62", RandPhraseSimple(
							StringFromKey("Common_Usurer_60", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))),
							StringFromKey("Common_Usurer_61", pchar, GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)))));
				link.l9.go = "IntelligenceForAll";
			}
			//<<<<---------------- пиратка, квест №5. --------------------
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_1") && npchar.city == pchar.questTemp.piratesLine.Q5.city_1)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFirstUsurer")
				{
					link.l5 = StringFromKey("Common_Usurer_63");
					link.l5.go = "StepPL5First_1";
				}
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFirst")
				{
					link.l5 = StringFromKey("Common_Usurer_64");
					link.l5.go = "StepPL5First_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_2") && npchar.city == pchar.questTemp.piratesLine.Q5.city_2)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toSecondUsurer")
				{
					link.l5 = StringFromKey("Common_Usurer_65");
					link.l5.go = "StepPL5Second_0";
				}
				if (pchar.questTemp.piratesLine == "PL5Hunter_toSecond")
				{
					link.l5 = StringFromKey("Common_Usurer_66");
					link.l5.go = "StepPL5Second_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_3") && npchar.city == pchar.questTemp.piratesLine.Q5.city_3)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toThirdUsurer" || pchar.questTemp.piratesLine == "PL5Hunter_toThird")
				{
					link.l5 = StringFromKey("Common_Usurer_67");
					link.l5.go = "StepPL5Third_1";
				}
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.Q5.city_4") && npchar.city == pchar.questTemp.piratesLine.Q5.city_4)
			{
				if (pchar.questTemp.piratesLine == "PL5Hunter_toFourth")
				{
					link.l5 = StringFromKey("Common_Usurer_68", pchar);
					link.l5.go = "StepPL5Four_1";
				}
			}
			//-------------------- пиратка, квест №5. ---------------->>>>
			//-->> сдача квеста найти потерянный драгоценный камень
			if (CheckCharacterItem(pchar, "UsurersJew") && CheckAttribute(npchar, "quest.usurersJewel.type"))
			{
				link.l6 = StringFromKey("Common_Usurer_69", pchar, npchar.quest.usurersJewel.type);
				link.l6.go = "usurersJewel_R1";
			}
			//<<-- сдача квеста найти потерянный драгоценный камень
			if (CheckAttribute(pchar, "GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "usurer_keeper")
			{
				link.l10 = StringFromKey("Common_Usurer_70", pchar);
				link.l10.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer"))
			{
				link.l11 = StringFromKey("Common_Usurer_71");
				link.l11.go = "ShipLetters_Usurer1";
			}
			//--> семейная реликвия
			if (CheckAttribute(pchar, "GenQuest.Noblelombard") && npchar.city == pchar.GenQuest.Noblelombard.City && !CheckAttribute(pchar, "questTemp.noblelombard"))
			{
				link.l12 = StringFromKey("Common_Usurer_72", pchar.GenQuest.Noblelombard.Name);
				link.l12.go = "Noblelombard";
			}
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Giveregard") && npchar.city == pchar.GenQuest.Noblelombard.City)
			{
				link.l12 = StringFromKey("Common_Usurer_73", pchar.GenQuest.Noblelombard.Name, FindMoneyString(sti(pchar.GenQuest.Noblelombard.Regard)));
				link.l12.go = "Noblelombard_5";
			}
			//<-- семейная реликвия

			//-->работорговец
			if (pchar.questTemp.Slavetrader == "Seek_slaves" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_74");
				link.l8.go = "Checkslaves";
				break;
			}
			if (pchar.questTemp.Slavetrader == "goaway" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_75", NPChar.name);
				link.l8.go = "Takeslaves_4_lose";
				break;
			}
			if (pchar.questTemp.Slavetrader == "goaway_pinas" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_76", NPChar.name);
				link.l8.go = "Pinas_lose";
				break;
			}
			if (pchar.questTemp.Slavetrader == "died" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_77", NPChar.name);
				link.l8.go = "Takeslaves_4_win";
				break;
			}
			if (pchar.questTemp.Slavetrader == "wait" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait") > 20 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_78", pchar);
				link.l8.go = "Takeslaves_3";
				break;
			}
			if (pchar.questTemp.Slavetrader == "waitship" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_79", pchar);
				link.l8.go = "Takeslaves_3";
				break;
			}
			if (pchar.questTemp.Slavetrader == "wait_1" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_1") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_80", npchar.name);
				link.l8.go = "EscapeSlave";
				break;
			}
			if (pchar.questTemp.Slavetrader == "escapeslave_win" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_81");
				link.l8.go = "Escape_slaves_win";
				break;
			}
			if (pchar.questTemp.Slavetrader == "wait_2" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_2") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_82", pchar, npchar.name);
				link.l8.go = "Slaveshore";
				break;
			}

			if (pchar.questTemp.Slavetrader == "goodbye" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_83", npchar.name);
				link.l8.go = "Brig_lose";
				break;
			}
			if (pchar.questTemp.Slavetrader == "goodbye_1" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_84", pchar, npchar.name);
				link.l8.go = "Letter_lose";
				break;
			}
			if (pchar.questTemp.Slavetrader == "winbrig" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_85", npchar.name);
				link.l8.go = "Brig_win";
				break;
			}
			if (pchar.questTemp.Slavetrader == "wait_3" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_3") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_86", npchar.name);
				link.l8.go = "SlaveGalleon";
				break;
			}
			if (pchar.questTemp.Slavetrader == "wingalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_87", npchar.name);
				link.l8.go = "Wingalleon";
				break;
			}
			if (pchar.questTemp.Slavetrader == "lostgalleon" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_88", pchar, npchar.name);
				link.l8.go = "Lostgalleon";
				break;
			}
			if (pchar.questTemp.Slavetrader == "wait_4" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_4") > 4 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_89", pchar, npchar.name);
				link.l8.go = "FindRat";
				break;
			}
			if (pchar.questTemp.Slavetrader == "wincorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_90", npchar.name);
				link.l8.go = "Wincorvette";
				break;
			}
			if (pchar.questTemp.Slavetrader == "lostcorvette" && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_91", pchar, npchar.name);
				link.l8.go = "lostcorvette";
				break;
			}
			if (pchar.questTemp.Slavetrader == "wait_5" && GetQuestPastDayParam("pchar.questTemp.Slavetrader_wait_5") > 30 && pchar.questTemp.Slavetrader.UsurerId == npchar.id)
			{
				link.l8 = StringFromKey("Common_Usurer_92", npchar.name);
				link.l8.go = "Havana_fort";
				break;
			}
			//<--работорговец
			// evganat - энциклопедия
			if (!ENCYCLOPEDIA_DISABLED)
			{
				if (CheckAttribute(npchar, "encyclopedia.tome"))
				{
					link.l13 = StringFromKey("Common_Usurer_93", pchar);
					link.l13.go = "Encyclopedia_Return";
				}
				else
				{
					if (GetUsurerDisposition() > 3)
					{
						if (!CheckAttribute(npchar, "encyclopedia"))
						{
							link.l13 = StringFromKey("Common_Usurer_94", pchar);
							link.l13.go = "Encyclopedia_FirstTime";
						}
						else
						{
							link.l13 = StringFromKey("Common_Usurer_95");
							link.l13.go = "Encyclopedia_Check";
						}
					}
				}
			}
			NextDiag.TempNode = "First time";
		break;

		//<<<<----------генератор -"Судовые документы". ------		
		case "ShipLetters_Usurer1":
			pchar.questTemp.different.GiveShipLetters.speakUsurer = true;
			dialog.text = StringFromKey("Common_Usurer_96");
			link.l1 = StringFromKey("Common_Usurer_97", FindMoneyString(sti(pchar.questTemp.different.GiveShipLetters.price1)));
			link.l1.go = "ShipLetters_Usurer2";
			link.l2 = StringFromKey("Common_Usurer_98");
			link.l2.go = "exit";
		break;

		case "ShipLetters_Usurer2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.GiveShipLetters.price1));
			pchar.questTemp.different.GiveShipLetters.speakUsurer_1 = true;
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = StringFromKey("Common_Usurer_99");
				link.l1 = StringFromKey("Common_Usurer_100");
				link.l1.go = "ShipLetters_Usurer2_1";
			}
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				s1 = StringFromKey("Common_Usurer_101");
				dialog.text = StringFromKey("Common_Usurer_102", s1);
				link.l1 = StringFromKey("Common_Usurer_103");
				link.l1.go = "ShipLetters_Usurer2_2";
			}
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				s1 = StringFromKey("Common_Usurer_104");
				dialog.text = StringFromKey("Common_Usurer_105", s1);
				link.l1 = StringFromKey("Common_Usurer_106");
				link.l1.go = "ShipLetters_Usurer2_3";
			}
		break;

		case "ShipLetters_Usurer2_1":
			dialog.text = StringFromKey("Common_Usurer_107");
			link.l1 = StringFromKey("Common_Usurer_108");
			link.l1.go = "exit";
		break;

		case "ShipLetters_Usurer2_2":
			dialog.text = StringFromKey("Common_Usurer_109");
			link.l1 = StringFromKey("Common_Usurer_110");
			link.l1.go = "exit";
		break;

		case "ShipLetters_Usurer2_3":
			s1 = StringFromKey("Common_Usurer_111");
			dialog.text = StringFromKey("Common_Usurer_112", s1);
			link.l1 = StringFromKey("Common_Usurer_113");
			link.l1.go = "exit";
		break;

		case "EncGirl_4":
			if (sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = StringFromKey("Common_Usurer_114", pchar);
				link.l1 = StringFromKey("Common_Usurer_115", pchar);
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = StringFromKey("Common_Usurer_116", pchar);
				link.l1 = StringFromKey("Common_Usurer_117");
				link.l1.go = "EncGirl_6";
			}
		break;

		case "EncGirl_5":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(3);
			dialog.text = StringFromKey("Common_Usurer_118");
			link.l1 = StringFromKey("Common_Usurer_119");
			link.l1.go = "EncGirl_5_1";
		break;

		case "EncGirl_6":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-2);
			dialog.text = StringFromKey("Common_Usurer_120");
			link.l1 = StringFromKey("Common_Usurer_121");
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
			dialog.text = StringFromKey("Common_Usurer_122");
			link.l1 = StringFromKey("Common_Usurer_123");
			link.l1.go = "EncGirl_6_2";
		break;

		case "EncGirl_6_2":
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("JungleGirl", "19");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ёл", "ла"));
			AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("", "а"));
			CloseQuestHeader("JungleGirl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//<<<<---------------- пиратка, квест №5. --------------------
		case "StepPL5First_1":
			dialog.text = StringFromKey("Common_Usurer_124");
			link.l1 = StringFromKey("Common_Usurer_125");
			link.l1.go = "StepPL5First_2";
		break;
		case "StepPL5First_2":
			dialog.text = StringFromKey("Common_Usurer_126");
			link.l1 = StringFromKey("Common_Usurer_127");
			link.l1.go = "StepPL5First_3";
		break;
		case "StepPL5First_3":
			pchar.questTemp.piratesLine.Q5.city_2 = GetQuestNationsCity(SPAIN);
			dialog.text = StringFromKey("Common_Usurer_128", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Pre"));
			link.l1 = StringFromKey("Common_Usurer_129", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "4");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity1", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Acc"));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandNameByCity(pchar.questTemp.piratesLine.Q5.city_2) + "Pre"));
			pchar.questTemp.piratesLine = "PL5Hunter_toSecond";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.piratesLine.Q5.city_2 + "_usurer"), "Pir_Line");
			AddLandQuestMarkToFantoms_Main("habitue", "Pir_Line", "PL5Hunter_toSecond_Habitues_QuestMarkCondition");
		break;

		case "StepPL5Second_0":
			dialog.text = StringFromKey("Common_Usurer_130");
			link.l1 = StringFromKey("Common_Usurer_131");
			link.l1.go = "StepPL5Second_1";
		break;
		case "StepPL5Second_1":
			dialog.text = StringFromKey("Common_Usurer_132");
			link.l1 = StringFromKey("Common_Usurer_133");
			link.l1.go = "StepPL5Second_2";
		break;
		case "StepPL5Second_2":
			pchar.questTemp.piratesLine.Q5.city_3 = GetQuestNationsCity(FRANCE);
			dialog.text = StringFromKey("Common_Usurer_134");
			link.l1 = StringFromKey("Common_Usurer_135");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "6");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandNameByCity(pchar.questTemp.piratesLine.Q5.city_3) + "Pre"));
			pchar.questTemp.piratesLine = "PL5Hunter_toThird";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.piratesLine.Q5.city_3 + "_usurer"), "Pir_Line");
			AddLandQuestMarkToFantoms_Main("habitue", "Pir_Line", "PL5Hunter_toThird_Habitues_QuestMarkCondition");
		break;

		case "StepPL5Third_1":
			dialog.text = StringFromKey("Common_Usurer_136");
			link.l1 = StringFromKey("Common_Usurer_137");
			link.l1.go = "StepPL5Third_2";
		break;
		case "StepPL5Third_2":
			dialog.text = StringFromKey("Common_Usurer_138");
			link.l1 = StringFromKey("Common_Usurer_139");
			link.l1.go = "StepPL5Third_3";
		break;
		case "StepPL5Third_3":
			pchar.questTemp.piratesLine.Q5.city_4 = GetQuestNationsCity(HOLLAND);
			dialog.text = StringFromKey("Common_Usurer_140", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4));
			link.l1 = StringFromKey("Common_Usurer_141");
			link.l1.go = "StepPL5Third_4";
		break;
		case "StepPL5Third_4":
			dialog.text = StringFromKey("Common_Usurer_142", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Pre"));
			link.l1 = StringFromKey("Common_Usurer_143", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "8");
			AddQuestUserData("Pir_Line_5_Hunter", "sCity1", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_4 + "Gen"));
			AddQuestUserData("Pir_Line_5_Hunter", "sIsland", XI_ConvertString(GetIslandNameByCity(pchar.questTemp.piratesLine.Q5.city_4) + "Pre"));
			pchar.questTemp.piratesLine = "PL5Hunter_toFourth";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			RemoveLandQuestMarkToFantoms_Main("habitue", "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.piratesLine.Q5.city_4 + "_usurer"), "Pir_Line");
		break;

		case "StepPL5Four_1":
			dialog.text = StringFromKey("Common_Usurer_144", pchar);
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "StepPL5Four_2";
		break;
		case "StepPL5Four_2":
			dialog.text = StringFromKey("Common_Usurer_145");
			link.l1 = StringFromKey("Common_Usurer_146");
			link.l1.go = "StepPL5Four_3";
		break;
		case "StepPL5Four_3":
			dialog.text = StringFromKey("Common_Usurer_147");
			link.l1 = StringFromKey("Common_Usurer_148");
			link.l1.go = "StepPL5Four_4";
		break;
		case "StepPL5Four_4":
			dialog.text = StringFromKey("Common_Usurer_149");
			link.l1 = StringFromKey("Common_Usurer_150");
			link.l1.go = "StepPL5Four_5";
		break;
		case "StepPL5Four_5":
			dialog.text = StringFromKey("Common_Usurer_151");
			link.l1 = StringFromKey("Common_Usurer_152");
			link.l1.go = "StepPL5Four_6";
		break;
		case "StepPL5Four_6":
			dialog.text = StringFromKey("Common_Usurer_153");
			link.l1 = StringFromKey("Common_Usurer_154");
			link.l1.go = "StepPL5Four_7";
		break;
		case "StepPL5Four_7":
			dialog.text = StringFromKey("Common_Usurer_155");
			link.l1 = StringFromKey("Common_Usurer_156");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_5_Hunter", "9");
			pchar.questTemp.piratesLine = "PL5Hunter_toBermudes";
			npchar.PLQ5Money = true; //метка на ростовщика, которому должен бабла
			//здесь ставим прерывание на вход в дом Орри на Бермудах
			Pchar.quest.PQ5_inOrryHouse.win_condition.l1 = "location";
			Pchar.quest.PQ5_inOrryHouse.win_condition.l1.location = "Pirates_houseS1";
			Pchar.quest.PQ5_inOrryHouse.function = "PQ5_inOrryHouse";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID("Pirates_tavernkeeper"), "Pir_Line");
		break;

		case "StepPL5End_close":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-5);
			dialog.text = StringFromKey("Common_Usurer_157");
			link.l1 = StringFromKey("Common_Usurer_158");
			link.l1.go = "exit";
			DeleteAttribute(npchar, "PLQ5Money");
			ChangeCharacterReputation(pchar, -50);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -20);
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;

		case "StepPL5End_1":
			dialog.text = StringFromKey("Common_Usurer_159");
			link.l1 = StringFromKey("Common_Usurer_160");
			link.l1.go = "StepPL5End_2";
		break;
		case "StepPL5End_2":
			dialog.text = StringFromKey("Common_Usurer_161");
			link.l1 = StringFromKey("Common_Usurer_162");
			link.l1.go = "StepPL5End_3";
		break;
		case "StepPL5End_3":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(4);
			dialog.text = StringFromKey("Common_Usurer_163");
			link.l1 = StringFromKey("Common_Usurer_164");
			link.l1.go = "StepPL5End_4";
			DeleteAttribute(npchar, "PLQ5Money");
			AddMoneyToCharacter(pchar, -45000);
			ChangeCharacterReputation(pchar, 10);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
		case "StepPL5End_4":
			dialog.text = StringFromKey("Common_Usurer_165", pchar);
			link.l1 = StringFromKey("Common_Usurer_166");
			link.l1.go = "exit";
		break;
		//-------------------- пиратка, квест №5. ---------------->>>>

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////		Кредитный генератор Loan
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanUsurer":
			dialog.text = StringFromKey("Common_Usurer_167");
			link.l1 = StringFromKey("Common_Usurer_168");
			link.l1.go = "Loan_GiveWork";
			//найти должника
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && pchar.GenQuest.Loan.FindCitizenNpcharId == NPChar.id)
			{
				link.l2 = StringFromKey("Common_Usurer_169");
				link.l2.go = "FindCitizen_1";
			}
			//доставить сундук
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && pchar.GenQuest.LoanChest.ChestNpcharId == NPChar.id)
			{
				link.l3 = StringFromKey("Common_Usurer_170");
				link.l3.go = "TakeChest_1";
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l4 = StringFromKey("Common_Usurer_171", pchar);
				link.l4.go = "TakeChest_2";
			}
			//кредиты
			if (CheckAttribute(Pchar, "Quest.Loans." + (NPC_Area)) && makeint(Pchar.Quest.Loans.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear), makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth), makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(), getDataMonth(), GetDataDay(), GetTime());
				Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum) / 100) * makeint(Pchar.Quest.Loans.(NPC_Area).Interest)) * (iPastMonths + 1);// boal 23.01.2004
				if (makeint(PChar.money) >= makeint(Pchar.Quest.Loans.(NPC_Area).Result))
				{
					Link.l5 = StringFromKey("Common_Usurer_175", pchar, FindMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)), LinkRandPhrase(
								StringFromKey("Common_Usurer_172", pchar),
								StringFromKey("Common_Usurer_173"),
								StringFromKey("Common_Usurer_174")));
					Link.l5.go = "loan_return";
					sTemp = "credit";
				}
			}
			else
			{
				Link.l6 = StringFromKey("Common_Usurer_179", LinkRandPhrase(
							StringFromKey("Common_Usurer_176"),
							StringFromKey("Common_Usurer_177"),
							StringFromKey("Common_Usurer_178")));
				Link.l6.go = "loan";
				if (makeint(Pchar.money) >= 100)
				{
					Link.l7 = StringFromKey("Common_Usurer_183", LinkRandPhrase(
								StringFromKey("Common_Usurer_180", pchar),
								StringFromKey("Common_Usurer_181"),
								StringFromKey("Common_Usurer_182")));
					Link.l7.go = "deposit";
				}
			}
			if (CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area)) && makeint(Pchar.Quest.Deposits.(NPC_Area)) == true)
			{
				iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Deposits.(NPC_Area).StartYear), makeint(Pchar.Quest.Deposits.(NPC_Area).StartMonth), makeint(Pchar.Quest.Deposits.(NPC_Area).StartDay), makefloat(Pchar.Quest.Deposits.(NPC_Area).StartTime), getDataYear(), getDataMonth(), GetDataDay(), GetTime());
				Pchar.Quest.Deposits.(NPC_Area).Result = makeint(Pchar.Quest.Deposits.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Deposits.(NPC_Area).Sum) / 100) * makeint(Pchar.Quest.Deposits.(NPC_Area).Interest)) * iPastMonths;
				Link.l8 = StringFromKey("Common_Usurer_187", LinkRandPhrase(
							StringFromKey("Common_Usurer_184"),
							StringFromKey("Common_Usurer_185"),
							StringFromKey("Common_Usurer_186")));
				Link.l8.go = "Deposit_return";
			}
			//выход
			if (sTemp == "credit")
			{
				link.l69 = StringFromKey("Common_Usurer_191", LinkRandPhrase(
							StringFromKey("Common_Usurer_188", pchar),
							StringFromKey("Common_Usurer_189", pchar),
							StringFromKey("Common_Usurer_190", pchar)));
				link.l69.go = "Loan_Remind";
			}
			else
			{
				link.l69 = StringFromKey("Common_Usurer_192", pchar);
				link.l69.go = "exit";
			}
		break;
		//=============================  даем или не даем работу - сундуки и должники
		case "Loan_GiveWork":
		// проверка на проф пригодность -->
		//            if (isBadReputation(pchar, 40))
			if (PlayerRPGCheck_BadReputation(40, false))
			{
				dialog.text = StringFromKey("Common_Usurer_195", RandSwear(), GetFullName(pchar), RandPhraseSimple(
							StringFromKey("Common_Usurer_193"),
							StringFromKey("Common_Usurer_194")));
				link.l1 = StringFromKey("Common_Usurer_198", RandPhraseSimple(
							StringFromKey("Common_Usurer_196"),
							StringFromKey("Common_Usurer_197", RandSwear())));
				link.l1.go = "exit";
				break;
			}
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 26)//при низком лидерстве не даем
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
				dialog.text = StringFromKey("Common_Usurer_199");
				link.l9 = StringFromKey("Common_Usurer_200");
				link.l9.go = "exit";
				break;
			}
			// проверка на проф пригодность <--
			dialog.text = StringFromKey("Common_Usurer_201");

			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				iNum = rand(1);
				if (sti(Pchar.Ship.Type) == SHIP_NOTUSED)
				{
					iNum = 0; // всегда первый
				}
				switch (iNum)
				{
					case 0 : // найти должника
						if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen")) break;

						if (sti(Pchar.Ship.Type) == SHIP_NOTUSED && sti(npchar.quest.FindCitizenNoShip) < 2)
						{
							iNum = findCitizenMan(Npchar, true);
							npchar.quest.FindCitizenNoShip = sti(npchar.quest.FindCitizenNoShip) + 1; // значит на суше без корабля
						}
						else
						{
							iNum = findCitizenMan(Npchar, false);
						}
						if (iNum > 0)
						{
							chr = &Characters[iNum];
							pchar.GenQuest.Loan.FindCitizenMoney = (7 + idRand(npchar.id, sti(PChar.rank))) * 1000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + idRand(npchar.id, 20) * 200 * GetCharacterSPECIALSimple(PChar, SPECIAL_L);
							pchar.GenQuest.Loan.FindCitizenPercent = makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) / (3 + rand(2)));
							pchar.GenQuest.Loan.FindCitizenIdx = iNum;
							pchar.GenQuest.Loan.FindCitizenChance1 = rand(2);
							pchar.GenQuest.Loan.FindCitizenChance2 = rand(1);
							pchar.GenQuest.Loan.FindCitizenChance3 = rand(1);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = StringFromKey("Common_Usurer_202", XI_ConvertString(GetIslandNameByCity(chr.city) + "Pre"));
							}
							dialog.text = StringFromKey("Common_Usurer_203", GetFullName(chr), XI_ConvertString("Colony" + chr.city + "Pre"), sTemp, FindMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)), FindMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
							link.l1 = StringFromKey("Common_Usurer_204");
							link.l1.go = "LoanUsurer_GiveWork_1";
						}
					break;

					case 1: // доставить сундуки
						if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest")) break;

						iNum = findChestMan(Npchar);
						if (iNum > 0)
						{
							chr = &Characters[iNum];
							pchar.GenQuest.LoanChest.Chest = 2 + drand(2);
							pchar.GenQuest.LoanChest.Money = (3 + idRand(npchar.id, sti(pchar.GenQuest.LoanChest.Chest))) * 400 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) + idRand(npchar.id, 20) * 250;
							pchar.GenQuest.LoanChest.TargetIdx = iNum;
							pchar.GenQuest.LoanChest.Time = 20 + rand(15);
							sTemp = "";
							if (npchar.city != chr.city)
							{
								sTemp = StringFromKey("Common_Usurer_205", XI_ConvertString(GetIslandNameByCity(chr.city) + "Pre"));
							}
							dialog.text = StringFromKey("Common_Usurer_206", pchar.GenQuest.LoanChest.Chest, XI_ConvertString("Colony" + chr.city + "Acc"), sTemp, GetFullName(chr), GetWorkTypeOfMan(chr, ""), FindMoneyString(sti(pchar.GenQuest.LoanChest.Money)), FindDaysString(sti(pchar.GenQuest.LoanChest.Time)));
							link.l1 = StringFromKey("Common_Usurer_207", pchar);
							link.l1.go = "LoanUsurer_ChestWork_1";
						}
					break;
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Usurer_208");
			}
			link.l9 = StringFromKey("Common_Usurer_209");
			link.l9.go = "exit";
		break;
		//============== boal нахождение должника ===============
		case "LoanUsurer_GiveWork_1":
			pchar.GenQuest.Loan.FindCitizen = true;
			pchar.GenQuest.Loan.FindCitizenNpcharId = Npchar.id;
			dialog.text = StringFromKey("Common_Usurer_210");
			link.l9 = StringFromKey("Common_Usurer_211");
			link.l9.go = "exit";
			chr = &Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)];
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = StringFromKey("Common_Usurer_212", XI_ConvertString(GetIslandNameByCity(chr.city) + "Pre"));
			}
			ReOpenQuestHeader("Gen_LoanFindCitizen");
			AddQuestRecord("Gen_LoanFindCitizen", "1");
			AddQuestUserData("Gen_LoanFindCitizen", "sName", GetFullName(chr));
			AddQuestUserData("Gen_LoanFindCitizen", "sCity", XI_ConvertString("Colony" + chr.city + "Pre") + sTemp);
			AddQuestUserData("Gen_LoanFindCitizen", "sFromCity", XI_ConvertString("Colony" + Npchar.city + "Gen"));
			AddQuestUserData("Gen_LoanFindCitizen", "sMoney", FindMoneyString(sti(pchar.GenQuest.Loan.FindCitizenMoney)));
			AddQuestUserData("Gen_LoanFindCitizen", "sMyMoney", FindMoneyString(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
		break;

		case "FindCitizen_1": //проверка выполнения квеста
			dialog.text = StringFromKey("Common_Usurer_213");
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone"))
			{
				link.l1 = StringFromKey("Common_Usurer_214");
				link.l1.go = "finish_work";
				link.l2 = StringFromKey("Common_Usurer_215");
				//if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= rand(11))
				// {
				//    link.l2.go = "finish_work_bad";
				//}
				// else
				// {
				link.l2.go = "finish_work_lie";
				//  }
			}

			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
			{
				link.l1 = StringFromKey("Common_Usurer_216");
				link.l1.go = "finish_work_bad";
			}
			link.l3 = StringFromKey("Common_Usurer_217", pchar);
			link.l3.go = "finish_work_cancel";
		//link.l9 = "Нет. Ничего.";
		//link.l9.go = "exit";
		break;

		case "finish_work":
			if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(3);
				dialog.text = StringFromKey("Common_Usurer_218");
				link.l9 = StringFromKey("Common_Usurer_219");
				link.l9.go = "exit";
				AddMoneyToCharacter(Pchar, -1 * sti(pchar.GenQuest.Loan.FindCitizenMoney));
				DeleteAttribute(pchar, "GenQuest.Loan");
				DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
				AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.rank) * 3);
				AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.rank) * 6);
				ChangeCharacterReputation(pchar, 1);
				OfficersReaction("good");
				AddQuestRecord("Gen_LoanFindCitizen", "4");
				CloseQuestHeader("Gen_LoanFindCitizen");
			}
			else
			{
				dialog.text = StringFromKey("Common_Usurer_220");
				link.l9 = StringFromKey("Common_Usurer_221");
				link.l9.go = "exit";
			}
		break;

		case "finish_work_bad":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-2);
			dialog.text = StringFromKey("Common_Usurer_222");
			link.l9 = StringFromKey("Common_Usurer_223");
			link.l9.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Loan");
			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
			ChangeCharacterReputation(pchar, -1);
			AddQuestRecord("Gen_LoanFindCitizen", "5");
			AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("Gen_LoanFindCitizen");
		break;

		case "finish_work_cancel":
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") || CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(-1);
				dialog.text = StringFromKey("Common_Usurer_224");
				link.l1 = StringFromKey("Common_Usurer_225");
				link.l1.go = "finish_work";
				link.l2 = StringFromKey("Common_Usurer_226");
				if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
				{
					link.l2.go = "finish_work_bad";
				}
				else
				{
					link.l2.go = "finish_work_bad_2";
				}
				//link.l9 = "Мне сейчас некогда. Я зайду позже.";
				//link.l9.go = "exit";
				//ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(-1);
				ChangeCharacterReputation(pchar, -1);
				dialog.text = StringFromKey("Common_Usurer_227");
				link.l1 = StringFromKey("Common_Usurer_228");
				link.l1.go = "exit";
				DeleteAttribute(pchar, "GenQuest.Loan");
				DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
				AddQuestRecord("Gen_LoanFindCitizen", "6");
				AddQuestUserData("Gen_LoanFindCitizen", "sSex", GetSexPhrase("ся", "ась"));
				CloseQuestHeader("Gen_LoanFindCitizen");
			}
		break;

		case "finish_work_bad_2":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-2);
			ChangeCharacterReputation(pchar, -3);
			dialog.text = StringFromKey("Common_Usurer_229");
			link.l1 = StringFromKey("Common_Usurer_230");
			link.l1.go = "finish_work_hanter";
			if (sti(pchar.Money) >= sti(pchar.GenQuest.Loan.FindCitizenMoney))
			{
				link.l2 = StringFromKey("Common_Usurer_231");
				link.l2.go = "finish_work";
			}
		break;

		case "finish_work_lie":
			dialog.text = StringFromKey("Common_Usurer_232");
			link.l1 = StringFromKey("Common_Usurer_233");
			link.l1.go = "finish_work_cancel";
		break;

		case "finish_work_hanter":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-3);
			dialog.text = StringFromKey("Common_Usurer_234");
			link.l1 = StringFromKey("Common_Usurer_235");
			link.l1.go = "exit";
			ChangeCharacterHunterScore(pchar, NationShortName(sti(npchar.Nation)) + "hunter", 40);
			DeleteAttribute(pchar, "GenQuest.Loan");
			DeleteAttribute(Pchar, "quest.LoanFindCitizenTimer");
			AddQuestRecord("Gen_LoanFindCitizen", "7");
			CloseQuestHeader("Gen_LoanFindCitizen");
		break;

		//============== boal доставка сундуков ===============
		case "LoanUsurer_ChestWork_1":
			pchar.GenQuest.LoanChest.TakeChest = true;
			pchar.GenQuest.LoanChest.ChestNpcharId = Npchar.id;
			dialog.text = StringFromKey("Common_Usurer_236");
			link.l9 = StringFromKey("Common_Usurer_237");
			link.l9.go = "exit";
			TakeNItems(pchar, "Chest", sti(pchar.GenQuest.LoanChest.Chest));
			SetTimerCondition("LoanChestTimer", 0, 0, sti(pchar.GenQuest.LoanChest.Time), false);
			// немного веселой жизни
			TraderHunterOnMap();
			chr = &Characters[sti(pchar.GenQuest.LoanChest.TargetIdx)];
			sTemp = "";
			if (npchar.city != chr.city)
			{
				sTemp = StringFromKey("Common_Usurer_238", XI_ConvertString(GetIslandNameByCity(chr.city) + "Pre"));
			}
			ReOpenQuestHeader("Gen_LoanTakeChest");
			AddQuestRecord("Gen_LoanTakeChest", "1");
			AddQuestUserData("Gen_LoanTakeChest", "sFromCity", XI_ConvertString("Colony" + Npchar.city + "Gen"));
			AddQuestUserData("Gen_LoanTakeChest", "sQty", GetTextChestsQuantity(sti(pchar.GenQuest.LoanChest.Chest)));
			AddQuestUserData("Gen_LoanTakeChest", "sCity", XI_ConvertString("Colony" + chr.city + "Acc") + sTemp);
			AddQuestUserData("Gen_LoanTakeChest", "sName", GetFullName(chr));
			AddQuestUserData("Gen_LoanTakeChest", "sType", GetWorkTypeOfMan(chr, ""));
			AddQuestUserData("Gen_LoanTakeChest", "sMoney", FindMoneyString(sti(pchar.GenQuest.LoanChest.Money)));
			AddQuestUserData("Gen_LoanTakeChest", "sDay", FindDaysString(sti(pchar.GenQuest.LoanChest.Time)));
		break;

		case "TakeChest_1":
			dialog.text = StringFromKey("Common_Usurer_239");
			link.l1 = StringFromKey("Common_Usurer_240", pchar);
			link.l1.go = "TakeChestFinish_work_cancel";
			link.l9 = StringFromKey("Common_Usurer_241");
			link.l9.go = "exit";
		break;

		case "TakeChestFinish_work_cancel":
			if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(-1);
				ChangeCharacterReputation(pchar, -1);
				dialog.text = StringFromKey("Common_Usurer_242");
				link.l1 = StringFromKey("Common_Usurer_243");
				link.l1.go = "exit";
				TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));
				DeleteAttribute(pchar, "GenQuest.LoanChest");
				DeleteAttribute(Pchar, "quest.LoanChestTimer");
				AddQuestRecord("Gen_LoanTakeChest", "5");
				AddQuestUserData("Gen_LoanTakeChest", "sSex", GetSexPhrase("ся", "ась"));
				CloseQuestHeader("Gen_LoanTakeChest");
			}
			else
			{
				dialog.text = StringFromKey("Common_Usurer_244");
				link.l1 = StringFromKey("Common_Usurer_245");
				link.l1.go = "Exit";
			}
		break;
		//============== кредиты ===============
		case "loan":
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = StringFromKey("Common_Usurer_246");
				if (makeint(Pchar.money) >= 100)
				{
					Link.l1 = StringFromKey("Common_Usurer_247");
					Link.l1.go = "deposit";
				}
				Link.l2 = StringFromKey("Common_Usurer_248");
				link.l2.go = "exit";
				break;
			}
			// проверка на проф пригодность -->
			//            if (isBadReputation(pchar, 40))
			if (PlayerRPGCheck_BadReputation(40, false))
			{
				dialog.text = StringFromKey("Common_Usurer_251", RandSwear(), GetFullName(pchar), RandPhraseSimple(
							StringFromKey("Common_Usurer_249"),
							StringFromKey("Common_Usurer_250")));
				link.l1 = StringFromKey("Common_Usurer_254", RandPhraseSimple(
							StringFromKey("Common_Usurer_252"),
							StringFromKey("Common_Usurer_253", RandSwear())));
				link.l1.go = "exit";
				break;
			}
			// проверка на проф пригодность <--
			dialog.text = StringFromKey("Common_Usurer_255");
			Link.l1 = StringFromKey("Common_Usurer_256");
			Link.l1.go = "Small";
			Link.l2 = StringFromKey("Common_Usurer_257");
			Link.l2.go = "Medium";
			Link.l3 = StringFromKey("Common_Usurer_258");
			Link.l3.go = "Large";
		break;

		case "small":
			Pchar.Quest.Loans.(NPC_Area).Sum = 500 * makeint(Pchar.rank);
			dialog.text = StringFromKey("Common_Usurer_259", FindMoneyString(sti(Pchar.Quest.loans.(NPC_Area).sum)));
			Link.l1 = StringFromKey("Common_Usurer_260");
			Link.l1.go = "Interest";
			Link.l2 = StringFromKey("Common_Usurer_261");
			Link.l2.go = "Loan";
			Link.l3 = StringFromKey("Common_Usurer_262");
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 22 - makeint((GetSummonSkillFromName(pchar, "Commerce") + GetSummonSkillFromName(pchar, "Leadership")) / 10);
		break;

		case "Medium":
			Pchar.Quest.Loans.(NPC_Area).Sum = 1500 * makeint(Pchar.rank);
			dialog.text = StringFromKey("Common_Usurer_263", FindMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)));
			Link.l1 = StringFromKey("Common_Usurer_264");
			Link.l1.go = "Interest";
			Link.l2 = StringFromKey("Common_Usurer_265");
			Link.l2.go = "Loan";
			Link.l3 = StringFromKey("Common_Usurer_266");
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 27 - makeint((GetSummonSkillFromName(pchar, "Commerce") + GetSummonSkillFromName(pchar, "Leadership")) / 10);
		break;

		case "Large":
			Pchar.Quest.Loans.(NPC_Area).Sum = 4000 * makeint(Pchar.rank);
			dialog.text = StringFromKey("Common_Usurer_267", FindMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).sum)));
			Link.l1 = StringFromKey("Common_Usurer_268");
			Link.l1.go = "Interest";
			Link.l2 = StringFromKey("Common_Usurer_269");
			Link.l2.go = "Loan";
			Link.l3 = StringFromKey("Common_Usurer_270");
			Link.l3.go = "ExitDelLoan1";
			Pchar.Quest.Loans.(NPC_Area).Interest = 37 - makeint((GetSummonSkillFromName(pchar, "Commerce") + GetSummonSkillFromName(pchar, "Leadership")) / 10);
		break;

		case "Interest":
		//Pchar.Quest.Loans.(NPC_Area).Interest = 16 - makeint(Pchar.skill.commerce);
			dialog.text = StringFromKey("Common_Usurer_271", Pchar.Quest.Loans.(NPC_Area).Interest);
			Link.l1 = StringFromKey("Common_Usurer_272");
			Link.l1.go = "Period";
			Link.l3 = StringFromKey("Common_Usurer_273");
			Link.l3.go = "ExitDelLoan1";
		break;

		case "Period":
			Pchar.Quest.Loans.(NPC_Area).Period = makeint(makeint(Pchar.reputation) / 20) + 1;
			dialog.text = StringFromKey("Common_Usurer_274", Pchar.name, FindMonthString(sti(Pchar.Quest.Loans.(NPC_Area).Period)));
			Link.l1 = StringFromKey("Common_Usurer_275");
			Link.l1.go = "LoanGranted";
			Link.l3 = StringFromKey("Common_Usurer_276");
			Link.l3.go = "ExitDelLoan1";
		break;

		case "LoanGranted":
			dialog.text = StringFromKey("Common_Usurer_277");
			Link.l1 = StringFromKey("Common_Usurer_278");
			Link.l1.go = "LoanGranted_exit";
		break;

		case "Loan_Remind":
			dialog.text = StringFromKey("Common_Usurer_279");
			Link.l1 = StringFromKey("Common_Usurer_280");
			Link.l1.go = "exit";
		break;

		case "loan_return":
			addMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Loans.(NPC_Area).Result)));
			// boal 27.01.2004 -->
			if (npchar.quest.trade_date != lastspeak_date) // дыра с прокачкой была
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(1);
				AddCharacterExpToSkill(Pchar, "Commerce", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 350);
				AddCharacterExpToSkill(Pchar, "Leadership", makeint(Pchar.Quest.Loans.(NPC_Area).Result) / 700);
			}
			// boal 27.01.2004 <--
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area); // bug fix
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			dialog.text = StringFromKey("Common_Usurer_284", LinkRandPhrase(
						StringFromKey("Common_Usurer_281"),
						StringFromKey("Common_Usurer_282"),
						StringFromKey("Common_Usurer_283", GetAddress_Form(NPChar))));
			Link.l1 = StringFromKey("Common_Usurer_288", LinkRandPhrase(
						StringFromKey("Common_Usurer_285"),
						StringFromKey("Common_Usurer_286"),
						StringFromKey("Common_Usurer_287")));
			Link.l1.go = "loan";
			if (makeint(PChar.money) >= 100)
			{
				Link.l2 = StringFromKey("Common_Usurer_292", LinkRandPhrase(
							StringFromKey("Common_Usurer_289", pchar),
							StringFromKey("Common_Usurer_290"),
							StringFromKey("Common_Usurer_291")));
				Link.l2.go = "deposit";
			}
			Link.l3 = StringFromKey("Common_Usurer_293", NPchar.name);
			Link.l3.go = "ExitDelLoan1";
		break;

		case "deposit":
			dialog.text = StringFromKey("Common_Usurer_297", LinkRandPhrase(
						StringFromKey("Common_Usurer_294"),
						StringFromKey("Common_Usurer_295"),
						StringFromKey("Common_Usurer_296")));
			Link.l1.edit = 3;
			link.l1 = "";
			Link.l1.go = "result";
		break;

		case "result":
			Pchar.QuestTemp.Deposits.(NPC_Area).Interest = its(1 + makeint(CheckOfficersPerk(pchar, "Investor")) + makeint((GetSummonSkillFromName(pchar, "Commerce") / 100.0 + GetCharacterSPECIAL(pchar, SPECIAL_C) / 10.0) * sqrt((GetNPCDisposition(npchar) + 100) / 100.0))); //новая формула вкладов в базе 1 и зависит от перка, коммерции, обаяния и отношения.
			Pchar.QuestTemp.Deposits.(NPC_Area).Sum = stripblank(dialogEditStrings[3]);
			iTemp = sti(stripblank(dialogEditStrings[3]));
			if (iTemp <= 0)
			{
				dialog.text = StringFromKey("Common_Usurer_298");
				link.l1 = StringFromKey("Common_Usurer_299");
				link.l1.go = "exit";
				break;
			}
			if (iTemp > sti(pchar.money))
			{
				dialog.text = StringFromKey("Common_Usurer_300");
				link.l1 = StringFromKey("Common_Usurer_301");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Common_Usurer_302", Pchar.QuestTemp.Deposits.(NPC_Area).Interest);
			Link.l1 = StringFromKey("Common_Usurer_303");
			Link.l1.go = "Deposit_placed";
			Link.l2 = StringFromKey("Common_Usurer_304");
			Link.l2.go = "Deposit";
			Link.l3 = StringFromKey("Common_Usurer_305");
			Link.l3.go = "Exit";
		break;

		case "Deposit_placed":
			if (!CheckAttribute(Pchar, "Quest.Deposits." + (NPC_Area) + ".Result"))
			{
				Pchar.Quest.Deposits.(NPC_Area).Result = 0;//fix
			}
			// boal limit
			if ((sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum)) > sti(NPChar.UsurerDeposit) * 1000)
			{
				dialog.text = StringFromKey("Common_Usurer_306", FindMoneyString(MakeMoneyShow(sti(NPChar.UsurerDeposit) * 1000, MONEY_SIGN, MONEY_DELIVER)));
				Link.l1 = StringFromKey("Common_Usurer_307");
				Link.l1.go = "Exit";
			}
			else
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(1);
				dialog.text = StringFromKey("Common_Usurer_308");
				Link.l1 = StringFromKey("Common_Usurer_309");
				Link.l1.go = "Deposit_Exit";
			}
		break;

		case "Deposit_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			Pchar.Quest.Deposits.(NPC_Area).Interest = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Interest);
			Pchar.Quest.Deposits.(NPC_Area).Sum = sti(Pchar.QuestTemp.Deposits.(NPC_Area).Sum);

			AddMoneyToCharacter(Pchar, -(makeint(Pchar.Quest.Deposits.(NPC_Area).Sum)));
			// общий долг
			Pchar.Quest.Deposits.(NPC_Area).Sum = sti(Pchar.Quest.Deposits.(NPC_Area).Result) + sti(Pchar.Quest.Deposits.(NPC_Area).Sum);
			Pchar.Quest.Deposits.(NPC_Area) = true;
			Pchar.Quest.Deposits.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Deposits.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Deposits.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Deposits.(NPC_Area).StartTime = getTime();
			DialogExit();
		break;

		case "Deposit_return":
			dialog.text = StringFromKey("Common_Usurer_310", FindMoneyString(sti(Pchar.Quest.Deposits.(NPC_Area).Result)));
			Link.l1 = StringFromKey("Common_Usurer_311");
			Link.l1.go = "Deposit_return_1";
			Link.l2 = StringFromKey("Common_Usurer_312");
			Link.l2.go = "Exit";
		break;

		case "Deposit_return_1":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-1);
			addMoneyToCharacter(Pchar, makeint(Pchar.Quest.Deposits.(NPC_Area).Result));
			dialog.text = StringFromKey("Common_Usurer_313");
			Link.l1 = StringFromKey("Common_Usurer_314");
			Link.l1.go = "Exit";
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;

		case "DeadMotherfucker":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-5);
			Dialog.TempNode = "DeadMotherFucker_1";
			dialog.text = StringFromKey("Common_Usurer_315");
			Link.l1 = StringFromKey("Common_Usurer_316");
			Link.l1.go = "LoanRestore_1";
			Link.l2 = StringFromKey("Common_Usurer_320", LinkRandPhrase(
						StringFromKey("Common_Usurer_317"),
						StringFromKey("Common_Usurer_318"),
						StringFromKey("Common_Usurer_319")));
			Link.l2.go = "ExitDelLoan2";
		break;

		case "DeadMotherFucker_1":
			dialog.text = StringFromKey("Common_Usurer_321");
			Link.l1 = "...";
			Link.l1.go = "ExitDelLoan2";
			Dialog.TempNode = "DeadMotherFucker_1";
		break;
		// boal обратимость факапства -->
		case "LoanRestore_1":
			iPastMonths = GetPastTime("Month", makeint(Pchar.Quest.Loans.(NPC_Area).StartYear), makeint(Pchar.Quest.Loans.(NPC_Area).StartMonth), makeint(Pchar.Quest.Loans.(NPC_Area).StartDay), makefloat(Pchar.Quest.Loans.(NPC_Area).StartTime), getDataYear(), getDataMonth(), GetDataDay(), GetTime());
			Pchar.Quest.Loans.(NPC_Area).Result = makeint(Pchar.Quest.Loans.(NPC_Area).Sum) + ((makeint(Pchar.Quest.Loans.(NPC_Area).Sum) / 100) * makeint(Pchar.Quest.Loans.(NPC_Area).Interest)) * (iPastMonths + 1);
			dialog.text = StringFromKey("Common_Usurer_322");
			Link.l1 = StringFromKey("Common_Usurer_323", pchar, FindMoneyString(sti(Pchar.Quest.Loans.(NPC_Area).Result)));
			Link.l1.go = "DeadMotherFucker_1";
			if (sti(Pchar.Money) >= 2 * sti(Pchar.Quest.Loans.(NPC_Area).Result))
			{
				Link.l2 = StringFromKey("Common_Usurer_324", FindMoneyString(2 * sti(Pchar.Quest.Loans.(NPC_Area).Result)));
				Link.l2.go = "LoanRestore_2";
			}
		break;

		case "LoanRestore_2":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(6);
			dialog.text = StringFromKey("Common_Usurer_325");
			Link.l1 = StringFromKey("Common_Usurer_326");
			Link.l1.go = "ExitDelLoan2";
			NextDiag.TempNode = "First time";
			addMoneyToCharacter(Pchar, -2 * sti(Pchar.Quest.Loans.(NPC_Area).Result));
			DeleteAttribute(PChar, "quest.Loans_" + NPC_Area);
			DeleteAttribute(PChar, "quest.Loans." + NPC_Area);
			ChangeCharacterHunterScore(PChar, NationShortName(sti(NPChar.nation)) + "hunter", -30);
			ChangeCharacterReputation(pchar, 2);
		break;

		case "ExitDelLoan1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
		break;

		case "ExitDelLoan2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(Pchar, "quest.Loans." + (NPC_Area));
			DeleteAttribute(Pchar, "quest.Deposits." + (NPC_Area));
		break;

		case "LoanGranted_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;

			AddMoneyToCharacter(Pchar, makeint(Pchar.Quest.Loans.(NPC_Area).Sum));
			Pchar.Quest.Loans.(NPC_Area) = true;
			Pchar.Quest.Loans.(NPC_Area).StartDay = getDataDay();
			Pchar.Quest.Loans.(NPC_Area).StartMonth = getDataMonth();
			Pchar.Quest.Loans.(NPC_Area).StartYear = getDataYear();
			Pchar.Quest.Loans.(NPC_Area).StartTime = getTime();

			sTemp = "Loans_" + NPC_Area;
			SetTimerCondition(sTemp, 0, makeint(Pchar.Quest.Loans.(NPC_Area).Period), 0, false);
			pchar.quest.(sTemp).CityId = NPC_Area;
			pchar.quest.(sTemp).win_condition = "LoansForAll";

			DialogExit();
			npchar.quest.trade_date = lastspeak_date; // дыра с прокачкой была
		break;
		//поиски драгоценного камня за гордом
		case "usurersJewel_1":
			sld = ItemsFromID("UsurersJew");
			switch (rand(3))
			{
				case 0:
					sld.JewelType = StringFromKey("Common_Usurer_327");
					sld.model = "DiamondA";
					sld.picIndex = 2;
					sld.Jewel = "jewelry5";
				break;
				case 1:
					sld.JewelType = StringFromKey("Common_Usurer_328");
					sld.model = "RubyA";
					sld.picIndex = 3;
					sld.Jewel = "jewelry5";
				break;
				case 2:
					sld.JewelType = StringFromKey("Common_Usurer_329");
					sld.model = "EmeraldA";
					sld.picIndex = 4;
					sld.Jewel = "jewelry5";
				break;
				case 3:
					sld.JewelType = StringFromKey("Common_Usurer_330");
					sld.model = "SapphireA";
					sld.picIndex = 1;
					sld.Jewel = "jewelry5";
				break;
			}
			dialog.text = StringFromKey("Common_Usurer_331", sld.JewelType);
			link.l1 = StringFromKey("Common_Usurer_332", sld.JewelType);
			link.l1.go = "usurersJewel_2";
			npchar.quest.usurersJewel.type = sld.JewelType; //тип камня
			npchar.quest.usurersJewel.money = (dRand(6) + 2) * 500 + 1000; //вознаграждение
			npchar.quest.usurersJewel.jewel = sld.Jewel;//камешек
		break;
		case "usurersJewel_2":
			dialog.text = StringFromKey("Common_Usurer_333", npchar.quest.usurersJewel.type);
			link.l1 = StringFromKey("Common_Usurer_334");
			link.l1.go = "usurersJewel_3";
		break;
		case "usurersJewel_3":
			dialog.text = StringFromKey("Common_Usurer_335", npchar.quest.usurersJewel.type);
			link.l1 = StringFromKey("Common_Usurer_336");
			link.l1.go = "usurersJewel_4";
		break;
		case "usurersJewel_4":
			dialog.text = StringFromKey("Common_Usurer_337");
			link.l1 = StringFromKey("Common_Usurer_338", pchar);
			link.l1.go = "usurersJewel_out";
			link.l2 = StringFromKey("Common_Usurer_339", pchar);
			link.l2.go = "usurersJewel_5";
		break;

		case "usurersJewel_out":
			dialog.text = StringFromKey("Common_Usurer_340");
			link.l1 = StringFromKey("Common_Usurer_341");
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.usurersJewel");
		//IncreaseUsurerDisposition(-1);
		break;
		case "usurersJewel_5":
			dialog.text = StringFromKey("Common_Usurer_342", npchar.quest.usurersJewel.type);
			link.l1 = StringFromKey("Common_Usurer_343");
			link.l1.go = "exit";
			pchar.questTemp.different = "SeekUsurersJewel";
			pchar.questTemp.different.SeekUsurersJewel = true;
			//кладём камень
			sld = ItemsFromID("UsurersJew");
			sld.shown = true;
			sld.startLocation = npchar.city + "_ExitTown";
			sld.startLocator = GetFreeRandomItemLocator(sld.startLocation);
			sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
			sld.JevelType = npchar.quest.usurersJewel.type;

			Log_QuestInfo("Камень находится в локаторе " + sld.startLocator + "");
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			sTitle = npchar.city + "UsurersJewel";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "SeekUsurersJewel", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sJewType", npchar.quest.usurersJewel.type);
		break;

		case "usurersJewel_R1":
			IncreaseUsurerDisposition(2);
			dialog.text = StringFromKey("Common_Usurer_344", npchar.quest.usurersJewel.type);
			link.l1 = StringFromKey("Common_Usurer_345");
			link.l1.go = "usurersJewel_R2";
			TakeItemFromCharacter(pchar, "UsurersJew");
		break;
		case "usurersJewel_R2":
			dialog.text = StringFromKey("Common_Usurer_346");
			link.l1 = StringFromKey("Common_Usurer_347");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 2);
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Leadership", 15);
			AddCharacterExpToSkill(pchar, "Fortune", 25);
			AddMoneyToCharacter(pchar, sti(npchar.quest.usurersJewel.money));
			AddItemLog(pchar, npchar.quest.usurersJewel.jewel, "1", StringFromKey("InfoMessages_164"), "Important_item");
			DeleteAttribute(pchar, "questTemp.different.SeekUsurersJewel");
			sTitle = npchar.city + "UsurersJewel";
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.usurersJewel");
		break;

		//============== Линейка Блада =============== homo

		case "CapBloodUsurer_1":
			dialog.text = StringFromKey("Common_Usurer_348");
			link.l1 = StringFromKey("Common_Usurer_349");
			link.l1.go = "CapBloodUsurer_2";
		break;

		case "CapBloodUsurer_2":
			dialog.text = StringFromKey("Common_Usurer_350");
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = StringFromKey("Common_Usurer_351");
				link.l1.go = "CapBloodUsurer_3";
			}
			else
			{
				link.l1 = StringFromKey("Common_Usurer_352");
				link.l1.go = "CapBloodUsurer_4";
			}
		break;

		case "CapBloodUsurer_3":
			AddMoneyToCharacter(pchar, -5000);
			Pchar.questTemp.CapBloodLine.Ogl = true;
			AddQuestRecord("OglQuest", "2");
			dialog.text = StringFromKey("Common_Usurer_353");
			link.l1 = StringFromKey("Common_Usurer_354");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			AddLandQuestmark_Main(CharacterFromID("Ogl"), "CapBloodLine");
			QuestPointerDelLocEx("Bridgetown_town", "reload", "reload8_back", "OglQuest");
		break;

		case "CapBloodUsurer_4":
			dialog.text = StringFromKey("Common_Usurer_355");
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = StringFromKey("Common_Usurer_356");
				link.l1.go = "CapBloodUsurer_3";
			}
			else
			{
				link.l1 = StringFromKey("Common_Usurer_357");
				link.l1.go = "Exit";
				NextDiag.TempNode = "CapBloodUsurer_4";
			}
		break;

		case "CapBloodUsurer_5":
			dialog.text = StringFromKey("Common_Usurer_358");
			link.l1 = StringFromKey("Common_Usurer_359");
			link.l1.go = "CapBloodUsurer_6";
		break;

		case "CapBloodUsurer_6":
			dialog.text = StringFromKey("Common_Usurer_360");
			link.l1 = StringFromKey("Common_Usurer_361");
			link.l1.go = "CapBloodUsurer_7";
			link.l2 = StringFromKey("Common_Usurer_362");
			link.l2.go = "Exit";
			NextDiag.TempNode = "First time";
			PChar.questTemp.CapBloodLine.QuestRaff = false;
			AddDialogExitQuestFunction("CapBloodLine_NeedMoney_Raff_DelQuestMarks");
			AddDialogExitQuestFunction("CapBloodLine_NeedMoney_DenyRaff_SetQuestPointers");
			QuestPointerDelLoc("Bridgetown_town", "reload", "reload8_back");
		break;

		case "CapBloodUsurer_7":
			AddLandQuestmark_Main(characterFromID("Bridgetown_tavernkeeper"), "CapBloodLine");
			QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_UsurerQuest");
			AddQuestRecord("UsurerQuest", "1");
			PChar.questTemp.CapBloodLine.QuestRaff = true;
			NextDiag.CurrentNode = "CapBloodUsurer_8";
			DialogExit();
		break;

		case "CapBloodUsurer_8":
			dialog.text = StringFromKey("Common_Usurer_363");
			if (sti(pchar.money) >= 27000)
			{
				link.l1 = StringFromKey("Common_Usurer_364");
				link.l1.go = "exit";
				AddMoneyToCharacter(pchar, -27000);
				Pchar.quest.QUsurer.over = "yes";
				NextDiag.TempNode = "First time"; // fix многократной отдачи денег
				CloseQuestHeader("UsurerQuest");
				RemoveLandQuestmark_Main(npchar, "CapBloodLine");
				QuestPointerDelLoc("Bridgetown_town", "reload", "reload8_back");

				if (CapBloodLine_CheckMoneyForNettl())
					QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "CapBloodLine_q2");
				if (CapBloodLine_NeedMoney_CheckHellsForQuest())
				{
					QuestPointerToLocEx("Bridgetown_town", "reload", "reload11_back", "BloodLine_FishermanQuest");
				}
				else
				{
					sld = CharacterFromID("MoneySpy");
					if (sld.quest.meeting == 0)
						QuestPointerToLocEx("Bridgetown_town", "reload", "houseS1", "BloodLine_MoneySpy");
				}
			}
			else
			{
				link.l1 = StringFromKey("Common_Usurer_365");
				link.l1.go = "Exit";
				NextDiag.TempNode = "CapBloodUsurer_8";
			}
		break;
		//работорговец
		int iSlaveMoney;
		int amount;
		case "GiveTaskSlave":
			pchar.questTemp.Slavetrader.iSlaveQuantity = 300 + rand(100);
			pchar.questTemp.Slavetrader.iSlaveMoney = sti(pchar.questTemp.Slavetrader.iSlaveQuantity) * 250;

			dialog.Text = StringFromKey("Common_Usurer_366");
			Link.l1 = StringFromKey("Common_Usurer_367");
			Link.l1.go = "GiveTaskSlave_1";
		break;

		case "GiveTaskSlave_1":
			dialog.Text = StringFromKey("Common_Usurer_368", pchar.questTemp.Slavetrader.iSlaveQuantity, FindMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)));
			Link.l1 = StringFromKey("Common_Usurer_369");
			Link.l1.go = "exit_slaves";
			Link.l2 = StringFromKey("Common_Usurer_370", pchar);
			Link.l2.go = "GiveTaskSlave_2";
		break;

		case "exit_slaves":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-4);
			dialog.Text = StringFromKey("Common_Usurer_371");
			Link.l1 = StringFromKey("Common_Usurer_372");
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			DeleteAttribute(npchar, "quest.slave");
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
		break;

		case "GiveTaskSlave_2":
			dialog.Text = StringFromKey("Common_Usurer_373");
			Link.l1 = StringFromKey("Common_Usurer_374");
			Link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "Seek_slaves"; // это ввод имени квеста и состояния квеста
			AddQuestRecord("Slavetrader", "1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Slavetrader", "sQty", FindSlavesWithCaseString(makeint(pchar.questTemp.Slavetrader.iSlaveQuantity), "Acc"));
			AddQuestUserData("Slavetrader", "sSum", FindMoneyString(makeint(pchar.questTemp.Slavetrader.iSlaveMoney)));
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_CheckSlaves_Usurer_QuestMarkCondition");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
		break;

		case "Checkslaves":
			amount = GetSquadronGoods(Pchar, GOOD_SLAVES) - sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = StringFromKey("Common_Usurer_375");
			if (amount < 0)
			{
				Link.l1 = StringFromKey("Common_Usurer_376", pchar);
				Link.l1.go = "exit";
			}
			else
			{
				Link.l1 = StringFromKey("Common_Usurer_377");
				Link.l1.go = "Takeslaves";
			}
		break;

		case "Takeslaves":
			amount = sti(pchar.questTemp.Slavetrader.iSlaveQuantity);
			dialog.Text = StringFromKey("Common_Usurer_378");
			Link.l1 = StringFromKey("Common_Usurer_379");
			Link.l1.go = "Takeslaves_1";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, amount);
		break;

		case "Takeslaves_1":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(3);
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.Text = StringFromKey("Common_Usurer_380");
			Link.l1 = StringFromKey("Common_Usurer_381");
			Link.l1.go = "Takeslaves_2";
		break;

		case "Takeslaves_2":
			dialog.Text = StringFromKey("Common_Usurer_382");
			Link.l1 = StringFromKey("Common_Usurer_383");
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "2");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "wait";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait");//запомнить дату
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_Wait_Usurer_QuestMarkCondition");
			AddMapQuestMark_Major(npchar.city + "_town", "Slavetrader", "Slavetrader_WaitQuest_WDMQuestMarkCondition");
		break;

		case "Takeslaves_3":
			if (4 - sti(RealShips[sti(pchar.ship.type)].Class) < 0)//проверка класса корабля
			{
				dialog.Text = StringFromKey("Common_Usurer_384");
				Link.l1 = StringFromKey("Common_Usurer_385");
				Link.l1.go = "Takeslaves_3_smallship";
			}
			else
			{
				dialog.Text = StringFromKey("Common_Usurer_386");
				Link.l1 = StringFromKey("Common_Usurer_387", pchar);
				Link.l1.go = "Takeslaves_4";
			}
		break;

		case "Takeslaves_3_smallship":
			pchar.questTemp.Slavetrader = "waitship";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Takeslaves_4":
			Slavetrader_GetRandomShore();//выбор бухты
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = StringFromKey("Common_Usurer_388", GetName(NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM), XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen"), XI_ConvertString(pchar.questTemp.Slavetrader.Island), pchar.questTemp.Slavetrader.ShipName);
			link.l1 = StringFromKey("Common_Usurer_389");
			link.l1.go = "Takeslaves_5";
		break;

		case "Takeslaves_5":
			dialog.Text = StringFromKey("Common_Usurer_390", GetName(NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM));
			Link.l1 = StringFromKey("Common_Usurer_391");
			Link.l1.go = "Takeslaves_6";
			Link.l2 = StringFromKey("Common_Usurer_392");
			Link.l2.go = "exit_slaves_1";
		break;

		case "exit_slaves_1":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-3);
			dialog.Text = StringFromKey("Common_Usurer_393", pchar.questTemp.Slavetrader.ShipName);
			Link.l1 = StringFromKey("Common_Usurer_394");
			Link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";//конец квеста, зачищать атрибут нельзя
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
		break;

		case "Takeslaves_6":
			dialog.Text = StringFromKey("Common_Usurer_395");
			Link.l1 = StringFromKey("Common_Usurer_396");
			Link.l1.go = "Takeslaves_7";
			Link.l2 = StringFromKey("Common_Usurer_397");
			Link.l2.go = "exit_slaves_1";
		break;

		case "Takeslaves_7":
			dialog.text = StringFromKey("Common_Usurer_398");
			link.l1 = StringFromKey("Common_Usurer_399");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "3");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sShoreName", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Dat"));
			AddQuestUserData("Slavetrader", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetrader.Island) + "Pre"));
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1 = "location";
			pchar.quest.Slavetrader_ShipsAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
			pchar.quest.Slavetrader_ShipsAttack.function = "Slavetrader_CreateSlaveShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_SlaveShipsOver", 0, 0, 15, false);    //таймер
			pchar.questTemp.Slavetrader = "wait1";    //это заглушка
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
		break;

		case "Takeslaves_4_lose":
			dialog.text = StringFromKey("Common_Usurer_400", GetFullName(pchar));
			link.l1 = StringFromKey("Common_Usurer_401", pchar);
			link.l1.go = "Takeslaves_5_lose";
		break;

		case "Takeslaves_4_win":
			dialog.text = StringFromKey("Common_Usurer_402", GetFullName(pchar), GetName(NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM));
			link.l1 = StringFromKey("Common_Usurer_403", pchar, GetName(NAMETYPE_ORIG, pchar.questTemp.Slavetrader.UnknownPirateName, NAME_NOM));
			link.l1.go = "Takeslaves_5_win";
		break;

		case "Takeslaves_5_lose":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-4);
			dialog.text = StringFromKey("Common_Usurer_404", pchar);
			link.l1 = StringFromKey("Common_Usurer_405");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "5_5");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
		break;

		case "Takeslaves_5_win":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 1600 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp) * 200;
			if (amount < 0)
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(5);
				dialog.text = StringFromKey("Common_Usurer_406", pchar);
				link.l1 = StringFromKey("Common_Usurer_407", npchar.name);
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, 320000);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, 1600);
				AddQuestRecord("Slavetrader", "6_1");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				break;
			}
			if (amount >= 0 && amount < 200)
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(4);
				dialog.text = StringFromKey("Common_Usurer_408", pchar, FindSlavesWithCaseString(sti(sTemp), "Acc"), FindMoneyString(iSlaveMoney));
				link.l1 = StringFromKey("Common_Usurer_409", npchar.name);
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, iSlaveMoney);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", FindSlavesString(sti(sTemp)));
				AddQuestUserData("Slavetrader", "sMoney", FindMoneyString(iSlaveMoney));
				break;
			}
			if (amount >= 200 && amount < 600)
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(3);
				dialog.text = StringFromKey("Common_Usurer_410", FindSlavesWithCaseString(sti(sTemp), "Acc"), FindMoneyString(iSlaveMoney));
				link.l1 = StringFromKey("Common_Usurer_411", npchar.name);
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, iSlaveMoney);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", FindSlavesString(sti(sTemp)));
				AddQuestUserData("Slavetrader", "sMoney", FindMoneyString(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(2);
				dialog.text = StringFromKey("Common_Usurer_412", FindSlavesWithCaseString(sti(sTemp), "Acc"), FindMoneyString(iSlaveMoney));
				link.l1 = StringFromKey("Common_Usurer_413", npchar.name);
				link.l1.go = "Takeslaves_6_win";
				AddMoneyToCharacter(pchar, iSlaveMoney);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", FindSlavesString(sti(sTemp)));
				AddQuestUserData("Slavetrader", "sMoney", FindMoneyString(iSlaveMoney));
				break;
			}
			if (amount >= 1100 && amount < 1600)
			{
				dialog.text = StringFromKey("Common_Usurer_414", pchar, FindSlavesWithCaseString(sti(sTemp), "Acc"));
				link.l1 = StringFromKey("Common_Usurer_415");
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = StringFromKey("Common_Usurer_416", pchar);
			link.l1 = StringFromKey("Common_Usurer_417");
			link.l1.go = "node_hanter_1";
		break;

		case "node_hanter_1":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-10);
			dialog.text = StringFromKey("Common_Usurer_418");
			link.l1 = StringFromKey("Common_Usurer_419");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 30);
			pchar.questTemp.Slavetrader = "End_quest";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
		break;

		case "Takeslaves_6_win":
			dialog.text = StringFromKey("Common_Usurer_420", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_421");
			link.l1.go = "Takeslaves_7_win";
		break;

		case "Takeslaves_7_win":
			dialog.text = StringFromKey("Common_Usurer_422", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_423");
			link.l1.go = "Nostatue";
			if (CheckCharacterItem(pchar, "statue1"))
			{
				link.l2 = StringFromKey("Common_Usurer_424");
				link.l2.go = "Yestatue";
			}
		break;

		case "Nostatue":
			dialog.text = StringFromKey("Common_Usurer_425");
			link.l1 = StringFromKey("Common_Usurer_426", npchar.name);
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_Wait_1_Usurer_QuestMarkCondition");
		break;

		case "Yestatue":
			dialog.text = StringFromKey("Common_Usurer_427");
			link.l1 = StringFromKey("Common_Usurer_428");
			link.l1.go = "Yestatue_1";
		break;

		case "Yestatue_1":
			AddItemLog(pchar, "statue1", "-1", StringFromKey("InfoMessages_165"), "Important_item");
			dialog.text = StringFromKey("Common_Usurer_429", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_430", pchar);
			link.l1.go = "Buystatue";
			link.l2 = StringFromKey("Common_Usurer_431");
			link.l2.go = "Nobuystatue";
		break;

		case "Buystatue":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(2);
			dialog.text = StringFromKey("Common_Usurer_432");
			link.l1 = StringFromKey("Common_Usurer_433", npchar.name);
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 100000);
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_Wait_1_Usurer_QuestMarkCondition");
		break;

		case "Nobuystatue":
			dialog.text = StringFromKey("Common_Usurer_434", pchar);
			link.l1 = StringFromKey("Common_Usurer_435", pchar);
			link.l1.go = "Nobuystatue_yes";
			link.l2 = StringFromKey("Common_Usurer_436");
			link.l2.go = "Nobuystatue_no";
		break;

		case "Nobuystatue_yes":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(3);
			dialog.text = StringFromKey("Common_Usurer_437");
			link.l1 = StringFromKey("Common_Usurer_438", npchar.name);
			link.l1.go = "exit";
			AddItemLog(pchar, "suit_3", "1", StringFromKey("InfoMessages_166"), "Important_item");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_Wait_1_Usurer_QuestMarkCondition");
		break;

		case "Nobuystatue_no":
			dialog.text = StringFromKey("Common_Usurer_439");
			link.l1 = StringFromKey("Common_Usurer_440");
			link.l1.go = "exit";
			AddItemLog(pchar, "statue1", "1", StringFromKey("InfoMessages_167"), "Important_item");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_1");
			pchar.questTemp.Slavetrader = "wait_1";
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_Wait_1_Usurer_QuestMarkCondition");
		break;

		case "EscapeSlave":
			dialog.text = StringFromKey("Common_Usurer_441", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_442", pchar);
			link.l1.go = "EscapeSlave_1";
		break;

		case "EscapeSlave_1":
			dialog.text = StringFromKey("Common_Usurer_443");
			link.l1 = StringFromKey("Common_Usurer_444");
			link.l1.go = "EscapeSlave_2";
		break;

		case "EscapeSlave_2":
			dialog.text = StringFromKey("Common_Usurer_445");
			link.l1 = StringFromKey("Common_Usurer_446");
			link.l1.go = "EscapeSlave_3";
		break;

		case "EscapeSlave_3":
			dialog.text = StringFromKey("Common_Usurer_447");
			link.l1 = StringFromKey("Common_Usurer_448");
			link.l1.go = "EscapeSlave_yes";
			link.l2 = StringFromKey("Common_Usurer_449");
			link.l2.go = "EscapeSlave_no";
		break;

		case "EscapeSlave_no":
			dialog.text = StringFromKey("Common_Usurer_450");
			link.l1 = StringFromKey("Common_Usurer_451");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
		break;

		case "EscapeSlave_yes":
			Slavetrader_GetEscapeShore();
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(HOLLAND);
			pchar.questTemp.Slavetrader = "EscapeSlave_Villemstad";
			AddQuestRecord("Slavetrader", "22_1");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("Villemstad_Tavernkeeper"), "Slavetrader");
		break;

		case "Escape_slaves_win":
			int iSlaveMoneyH;
			string sNum;
			amount = 1100 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp) * 300;
			sNum = GetSquadronGoods(Pchar, GOOD_SLAVES) - 1100;
			iSlaveMoneyH = makeint(sNum) * 100;
			if (amount < 0)
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(5);
				dialog.text = StringFromKey("Common_Usurer_452", FindSlavesWithCaseString(sti(sTemp), "Acc"), sNum, FindMoneyString(iSlaveMoneyH));
				link.l1 = StringFromKey("Common_Usurer_453", pchar, npchar.name);
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, 330000);
				AddMoneyToCharacter(pchar, iSlaveMoneyH);
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_5");
				AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", FindSlavesWithCaseString(sti(sTemp), "Acc"));
				AddQuestUserData("Slavetrader", "sMoney", iSlaveMoneyH);
				break;
			}
			if (amount < 101 && amount >= 0)
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(4);
				dialog.text = StringFromKey("Common_Usurer_454", FindSlavesWithCaseString(sti(sTemp), "Acc"), FindMoneyString(iSlaveMoney));
				link.l1 = StringFromKey("Common_Usurer_455", npchar.name);
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", FindSlavesWithCaseString(sti(sTemp), "Acc"));
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 100 && amount < 600)
			{
				// evganat - можно вставить отношение сюда
				IncreaseUsurerDisposition(3);
				dialog.text = StringFromKey("Common_Usurer_456", FindSlavesWithCaseString(sti(sTemp), "Acc"), FindMoneyString(iSlaveMoney));
				link.l1 = StringFromKey("Common_Usurer_457", npchar.name);
				link.l1.go = "Escape_slaves_win_1";
				AddMoneyToCharacter(pchar, makeint(iSlaveMoney));
				RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
				AddQuestRecord("Slavetrader", "22_6");
				AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
				AddQuestUserData("Slavetrader", "sQty", FindSlavesWithCaseString(sti(sTemp), "Acc"));
				AddQuestUserData("Slavetrader", "sMoney", makeint(iSlaveMoney));
				break;
			}
			if (amount >= 600 && amount < 1100)
			{
				dialog.text = StringFromKey("Common_Usurer_458", FindSlavesWithCaseString(sti(sTemp), "Acc"));
				link.l1 = StringFromKey("Common_Usurer_459");
				link.l1.go = "node_hanter_1";
				break;
			}
			dialog.text = StringFromKey("Common_Usurer_460");
			link.l1 = StringFromKey("Common_Usurer_461");
			link.l1.go = "node_hanter_1";
		break;

		case "Escape_slaves_win_1":
			dialog.text = StringFromKey("Common_Usurer_462", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_463", pchar, npchar.name);
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_2");
			pchar.questTemp.Slavetrader = "wait_2";
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_Wait_2_Usurer_QuestMarkCondition");
		break;

		case "Slaveshore":
			dialog.text = StringFromKey("Common_Usurer_464", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_465");
			link.l1.go = "Slaveshore_1";
		break;

		case "Slaveshore_1":
			pchar.questTemp.Slavetrader.Island = Islands[GetCharacterCurrentIsland(pchar)].id;
			pchar.questTemp.Slavetrader.Island.Shore = GetIslandRandomShoreId(pchar.questTemp.Slavetrader.Island);
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = StringFromKey("Common_Usurer_466", XI_ConvertString(pchar.questTemp.Slavetrader.Island.Shore + "Gen"), pchar.questTemp.Slavetrader.ShipName, NationNameGenitive(sti(npchar.nation)));
			link.l1 = StringFromKey("Common_Usurer_467");
			link.l1.go = "Slaveshore_2";
		break;

		case "Slaveshore_2":
			dialog.text = StringFromKey("Common_Usurer_468", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_469");
			link.l1.go = "Slaveshore_3_yes";
			link.l2 = StringFromKey("Common_Usurer_470", pchar, NationNameInstrumental(sti(npchar.nation)));
			link.l2.go = "Slaveshore_3_no";
		break;

		case "Slaveshore_3_no":
			dialog.text = StringFromKey("Common_Usurer_471");
			link.l1 = StringFromKey("Common_Usurer_472", npchar.name);
			link.l1.go = "node_hanter_1";
		break;

		case "Slaveshore_3_yes":
			dialog.text = StringFromKey("Common_Usurer_473");
			link.l1 = StringFromKey("Common_Usurer_474", npchar.name);
			link.l1.go = "Slaveshore_4";
		break;

		case "Slaveshore_4":
			dialog.text = StringFromKey("Common_Usurer_475", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_476");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "10");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1 = "location";
			pchar.quest.Slavetrader_ShoreAttack.win_condition.l1.location = pchar.questTemp.Slavetrader.Island;//отправляем в локацию
			pchar.quest.Slavetrader_ShoreAttack.function = "Slavetrader_CreateShoreShips";//создание кораблей
			SetFunctionTimerCondition("Slavetrader_ShoreShipsOver", 0, 0, 1, false);    //таймер
			pchar.questTemp.Slavetrader = "wait1";    //заглушка
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
		break;

		case "Pinas_lose":
			dialog.text = StringFromKey("Common_Usurer_477", GetFullName(pchar));
			link.l1 = StringFromKey("Common_Usurer_478", pchar);
			link.l1.go = "Takeslaves_5_lose";
		break;

		case "Slaveshore_5":
			dialog.text = StringFromKey("Common_Usurer_479", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_480", pchar);
			link.l1.go = "Slaveshore_6";
		break;

		case "Slaveshore_6":
			dialog.text = StringFromKey("Common_Usurer_481", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_482");
			link.l1.go = "Slaveshore_7";
		break;

		case "Slaveshore_7": //выбор острова, куда бригантина пойдет
			switch (sti(NPChar.nation))
			{
				case HOLLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Curacao";
				break;
				case FRANCE :
					pchar.questTemp.Slavetraderbrig.Island = "Tortuga";
				break;
				case SPAIN :
					pchar.questTemp.Slavetraderbrig.Island = "Cuba2";
				break;
				case ENGLAND :
					pchar.questTemp.Slavetraderbrig.Island = "Jamaica";
				break;
			}
			pchar.questTemp.Slavetraderbrig.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));//имя бригантины
			pchar.questTemp.Slavetrader.Nation = NPChar.nation;
			dialog.text = StringFromKey("Common_Usurer_483", pchar.questTemp.Slavetraderbrig.ShipName, XI_ConvertString(pchar.questTemp.Slavetraderbrig.Island));
			link.l1 = StringFromKey("Common_Usurer_484");
			link.l1.go = "Slaveshore_8";
			AddQuestRecord("Slavetrader", "14");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetraderbrig.ShipName);
			AddQuestUserData("Slavetrader", "sIsland", XI_ConvertString(GetIslandByArealName(pchar.questTemp.Slavetraderbrig.Island)));
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1 = "location";
			pchar.quest.Slavetrader_BrigAttack.win_condition.l1.location = pchar.questTemp.Slavetraderbrig.Island;//отправляем в локацию
			pchar.quest.Slavetrader_BrigAttack.function = "Slavetrader_CreateBrig";//создание бригантины
			SetFunctionTimerCondition("Slavetrader_BrigOver", 0, 0, 15, false);    //таймер
			pchar.questTemp.Slavetrader = "wait1";    //это нода ожидания, пустая
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
		break;

		case "Slaveshore_8":
			dialog.text = StringFromKey("Common_Usurer_485", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_486");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Slavetrader_enterSoldiers");
		break;

		case "Brig_lose":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-10);
			dialog.text = StringFromKey("Common_Usurer_487", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_488", npchar.name);
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader = "End_quest";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
		break;

		case "Letter_lose":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-6);
			dialog.text = StringFromKey("Common_Usurer_489");
			link.l1 = StringFromKey("Common_Usurer_490", npchar.name);
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
		break;

		case "Brig_win":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(10);
			dialog.text = StringFromKey("Common_Usurer_491", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_492");
			link.l1.go = "Brig_win_1";
		break;

		case "Brig_win_1":
			RemoveItems(PChar, "letter_1", 1);
			dialog.text = StringFromKey("Common_Usurer_493");
			link.l1 = StringFromKey("Common_Usurer_494");
			link.l1.go = "Brig_win_2";
		break;

		case "Brig_win_2":
			dialog.text = StringFromKey("Common_Usurer_495", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_496");
			link.l1.go = "Brig_win_3";
		break;

		case "Brig_win_3":
			dialog.text = StringFromKey("Common_Usurer_497", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_498");
			link.l1.go = "Brig_win_4";
		break;

		case "Brig_win_4":
			dialog.text = StringFromKey("Common_Usurer_499", pchar);
			link.l1 = StringFromKey("Common_Usurer_500");
			link.l1.go = "Brig_win_5";
		break;

		case "Brig_win_5":
			dialog.text = StringFromKey("Common_Usurer_501", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_502", npchar.name);
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_3");
			pchar.questTemp.Slavetrader = "wait_3";
			pchar.GenQuestRandItem.Shore18 = true;
			pchar.GenQuestRandItem.Shore18.randitem1 = "sculMa1";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1 = "location";
			Pchar.quest.Slavetrader_Bonanza.win_condition.l1.location = "Shore18";
			Pchar.quest.Slavetrader_Bonanza.function = "Slavetrader_Bonanza";
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_Wait_3_Usurer_QuestMarkCondition");
		break;

		case "SlaveGalleon":
			dialog.text = StringFromKey("Common_Usurer_503", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_504", pchar, npchar.name);
			link.l1.go = "SlaveGalleon_1";
		break;

		case "SlaveGalleon_end":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-10);
			dialog.text = StringFromKey("Common_Usurer_505");
			link.l1 = StringFromKey("Common_Usurer_506");
			link.l1.go = "node_hanter_1";
		break;

		case "SlaveGalleon_1":
			dialog.text = StringFromKey("Common_Usurer_507", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_508");
			link.l1.go = "SlaveGalleon_2";
		break;

		case "SlaveGalleon_2":
			dialog.text = StringFromKey("Common_Usurer_509");
			link.l1 = StringFromKey("Common_Usurer_510");
			link.l1.go = "SlaveGalleon_3";
		break;

		case "SlaveGalleon_3":
			dialog.text = StringFromKey("Common_Usurer_511");
			link.l1 = StringFromKey("Common_Usurer_512", npchar.name);
			link.l1.go = "SlaveGalleon_4";
		break;

		case "SlaveGalleon_4":
			Slavetrader_GetHispanShore();
			sTemp = pchar.questTemp.SlavetraderAreal.add;
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			dialog.text = StringFromKey("Common_Usurer_513", sTemp, pchar.questTemp.Slavetrader.ShipName);
			link.l1 = StringFromKey("Common_Usurer_514", pchar);
			link.l1.go = "SlaveGalleon_5";
			link.l2 = StringFromKey("Common_Usurer_515");
			link.l2.go = "SlaveGalleon_end";
		break;

		case "SlaveGalleon_5":
			sTemp = pchar.questTemp.SlavetraderAreal.add;
			dialog.text = StringFromKey("Common_Usurer_516", sTemp);
			link.l1 = StringFromKey("Common_Usurer_517", pchar);
			link.l1.go = "exit";
			SlavetraderGalleonInWorld();
			SetFunctionTimerCondition("Slavetrader_SlaveGalleonOver", 0, 0, 21, false);
			pchar.questTemp.Slavetrader = "wait1";
			AddQuestRecord("Slavetrader", "18");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ым", "ой"));
			AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
			AddQuestUserData("Slavetrader", "sAreal", sTemp);
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
		break;

		case "Lostgalleon":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-7);
			dialog.text = StringFromKey("Common_Usurer_518", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_519", npchar.name);
			link.l1.go = "exit";
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
		break;

		case "Wingalleon":
			pchar.questTemp.Slavetrader.Nation = npchar.nation;
			amount = 3000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp) * 200;
			if (amount < 1)
			{
				dialog.text = StringFromKey("Common_Usurer_520");
				link.l1 = StringFromKey("Common_Usurer_521", pchar, FindSlavesWithCaseString(sti(sTemp), "Acc"), FindMoneyString(iSlaveMoney));
				link.l1.go = "Wingalleon_1";
			}
			else
			{
				dialog.text = StringFromKey("Common_Usurer_522", NationNameGenitive(sti(npchar.nation)));
				link.l1 = StringFromKey("Common_Usurer_523");
				link.l1.go = "Wingalleon_goaway";
			}
		break;

		case "Wingalleon_goaway":
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
			DialogExit();
		break;

		case "Wingalleon_1":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(5);
			dialog.text = StringFromKey("Common_Usurer_524", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_525", pchar);
			link.l1.go = "Wingalleon_yes";
			link.l2 = StringFromKey("Common_Usurer_526", npchar.name);
			link.l2.go = "Wingalleon_no";
		break;

		case "Wingalleon_no":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(-10);
			dialog.text = StringFromKey("Common_Usurer_527", npchar.name, NationNameGenitive(sti(npchar.nation)));
			link.l1 = StringFromKey("Common_Usurer_528");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "9");
			CloseQuestHeader("Slavetrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(pchar.questTemp.Slavetrader.Nation)) + "hunter", 70);
			pchar.questTemp.Slavetrader = "End_quest";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
		break;

		case "Wingalleon_yes":
			dialog.text = StringFromKey("Common_Usurer_529", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_530", npchar.name);
			link.l1.go = "Wingalleon_yes_1";
		break;

		case "Wingalleon_yes_1":
			AddItemLog(pchar, "chest", "15", StringFromKey("InfoMessages_134"), "Important_item");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_4");
			pchar.questTemp.Slavetrader = "wait_4";
			AddQuestRecord("Slavetrader", "20");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			pchar.questTemp.Slavetrader.iSlaveMoney = makeint(sTemp) * 200 - 120000;
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
			DialogExit();
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_Wait_4_Usurer_QuestMarkCondition");
		break;

		case "FindRat":
			dialog.text = StringFromKey("Common_Usurer_531", pchar.name, FindMoneyString(sti(pchar.questTemp.Slavetrader.iSlaveMoney)));
			link.l1 = StringFromKey("Common_Usurer_532", npchar.name);
			link.l1.go = "FindRat_1";
		break;

		case "FindRat_1":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Slavetrader.iSlaveMoney));
			dialog.text = StringFromKey("Common_Usurer_533", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_534");
			link.l1.go = "FindRat_2";
		break;

		case "FindRat_2":
			if (CheckCharacterItem(pchar, "indian15"))
			{
				dialog.text = StringFromKey("Common_Usurer_535");
				link.l1 = StringFromKey("Common_Usurer_536");
				link.l1.go = "BG_money";
				link.l2 = StringFromKey("Common_Usurer_537");
				link.l2.go = "BG_change";
				link.l3 = StringFromKey("Common_Usurer_538");
				link.l3.go = "BG_no";
			}
			else
			{
				dialog.text = StringFromKey("Common_Usurer_539");
				link.l1 = StringFromKey("Common_Usurer_540");
				link.l1.go = "BG_PF";
			}
		break;

		case "BG_money":
			dialog.text = StringFromKey("Common_Usurer_541");
			link.l1 = StringFromKey("Common_Usurer_542");
			link.l1.go = "BG_PF";
			AddMoneyToCharacter(pchar, 30000);
			AddItemLog(pchar, "indian15", "-1", StringFromKey("InfoMessages_140"), "Important_item");
		break;

		case "BG_change":
			dialog.text = StringFromKey("Common_Usurer_543");
			link.l1 = StringFromKey("Common_Usurer_544");
			link.l1.go = "BG_PF";
			AddItemLog(pchar, "indian19,indian15", "1,-1", StringFromKey("InfoMessages_139"), "Important_item");
			Log_Info(StringFromKey("InfoMessages_140"));
		break;

		case "BG_no":
			dialog.text = StringFromKey("Common_Usurer_545");
			link.l1 = StringFromKey("Common_Usurer_546");
			link.l1.go = "BG_PF";
		break;

		case "BG_PF":
			dialog.text = StringFromKey("Common_Usurer_547");
			link.l1 = StringFromKey("Common_Usurer_548");
			link.l1.go = "PF_check";
		break;

		case "PF_check":
			if (CheckCharacterItem(pchar, "indian2"))
			{
				dialog.text = StringFromKey("Common_Usurer_549");
				link.l1 = StringFromKey("Common_Usurer_550");
				link.l1.go = "PF_money";
				link.l2 = StringFromKey("Common_Usurer_551");
				link.l2.go = "PF_change";
				link.l3 = StringFromKey("Common_Usurer_552");
				link.l3.go = "PF_no";
			}
			else
			{
				dialog.text = StringFromKey("Common_Usurer_553");
				link.l1 = StringFromKey("Common_Usurer_554");
				link.l1.go = "FindRat_3";
			}
		break;

		case "PF_money":
			dialog.text = StringFromKey("Common_Usurer_555");
			link.l1 = StringFromKey("Common_Usurer_556");
			link.l1.go = "FindRat_3";
			AddMoneyToCharacter(pchar, 20000);
			AddItemLog(pchar, "indian2", "-1", StringFromKey("InfoMessages_159"), "Important_item");
		break;

		case "PF_change":
			dialog.text = StringFromKey("Common_Usurer_557");
			link.l1 = StringFromKey("Common_Usurer_558");
			link.l1.go = "FindRat_3";
			AddItemLog(pchar, "indian6,indian2", "1,-1", StringFromKey("InfoMessages_160"), "Important_item");
			Log_Info(StringFromKey("InfoMessages_159"));
		break;

		case "PF_no":
			dialog.text = StringFromKey("Common_Usurer_559");
			link.l1 = StringFromKey("Common_Usurer_560", pchar);
			link.l1.go = "FindRat_3";
		break;

		case "FindRat_3":
			dialog.text = StringFromKey("Common_Usurer_561", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_562", pchar);
			link.l1.go = "FindRat_4";
		break;

		case "FindRat_4":
			dialog.text = StringFromKey("Common_Usurer_563");
			link.l1 = StringFromKey("Common_Usurer_564");
			link.l1.go = "FindRat_5";
		break;

		case "FindRat_5":
			dialog.text = StringFromKey("Common_Usurer_565");
			link.l1 = StringFromKey("Common_Usurer_566");
			link.l1.go = "FindRat_6";
		break;

		case "FindRat_6":
			dialog.text = StringFromKey("Common_Usurer_567");
			link.l1 = StringFromKey("Common_Usurer_568");
			link.l1.go = "FindRat_7";
		break;

		case "FindRat_7":
			dialog.text = StringFromKey("Common_Usurer_569");
			link.l1 = StringFromKey("Common_Usurer_570");
			link.l1.go = "FindRat_8";
		break;

		case "FindRat_8":
			dialog.text = StringFromKey("Common_Usurer_571");
			link.l1 = StringFromKey("Common_Usurer_572");
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.ShipName = GenerateRandomNameToShip(SPAIN);
			AddQuestRecord("Slavetrader", "21");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.questTemp.Slavetrader = "FindRatPanama";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			AddLandQuestmark_Main(CharacterFromID("Panama_tavernkeeper"), "Slavetrader");
		break;

		case "Wincorvette":
		// evganat - можно вставить отношение сюда
			IncreaseUsurerDisposition(7);
			dialog.text = StringFromKey("Common_Usurer_573", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_574", npchar.name);
			link.l1.go = "Wincorvette_1";
		break;

		case "Wincorvette_1":
			dialog.text = StringFromKey("Common_Usurer_575");
			link.l1 = StringFromKey("Common_Usurer_576");
			link.l1.go = "Wincorvette_2";
		break;

		case "Wincorvette_2":
			dialog.text = StringFromKey("Common_Usurer_577");
			link.l1 = StringFromKey("Common_Usurer_578", npchar.name);
			link.l1.go = "Wincorvette_3";
			AddItemLog(pchar, "indian18", "1", StringFromKey("InfoMessages_168"), "Important_item");
		break;

		case "Wincorvette_3":
			dialog.text = StringFromKey("Common_Usurer_579");
			link.l1 = StringFromKey("Common_Usurer_580", npchar.name);
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 150000);
			AddQuestRecord("Slavetrader", "21_13");
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_Wait_5_Usurer_QuestMarkCondition");
		break;

		case "Lostcorvette":
			dialog.text = StringFromKey("Common_Usurer_581", pchar);
			link.l1 = StringFromKey("Common_Usurer_582", npchar.name);
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_14");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_5");
			pchar.questTemp.Slavetrader = "wait_5";
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_Wait_5_Usurer_QuestMarkCondition");
		break;

		case "Havana_fort":
			dialog.text = StringFromKey("Common_Usurer_583", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_584", npchar.name);
			link.l1.go = "Havana_fort_1";
		break;

		case "Havana_fort_1":
			dialog.text = StringFromKey("Common_Usurer_585");
			link.l1 = StringFromKey("Common_Usurer_586");
			link.l1.go = "Havana_fort_2";
		break;

		case "Havana_fort_2":
			dialog.text = StringFromKey("Common_Usurer_587", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_588", pchar, npchar.name, RandSwear());
			link.l1.go = "Havana_fort_3";
			link.l2 = StringFromKey("Common_Usurer_589", npchar.name);
			link.l2.go = "Havana_fort_not";
		break;

		case "Havana_fort_not":
			dialog.text = StringFromKey("Common_Usurer_590", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_591", npchar.name);
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "8");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "End_quest";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
		break;

		case "Havana_fort_3":
			dialog.text = StringFromKey("Common_Usurer_592");
			link.l1 = StringFromKey("Common_Usurer_593");
			link.l1.go = "Havana_fort_4";
		break;

		case "Havana_fort_4":
			dialog.text = StringFromKey("Common_Usurer_594");
			link.l1 = StringFromKey("Common_Usurer_595");
			link.l1.go = "Havana_fort_5";
		break;

		case "Havana_fort_5":
			dialog.text = StringFromKey("Common_Usurer_596", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_597", npchar.name);
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "24");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Slavetrader", "sName", GetFullName(npchar));
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1 = "location";
			pchar.quest.Slavetrader_HavanaAttack.win_condition.l1.location = "Cuba2";//отправляем в локацию
			pchar.quest.Slavetrader_HavanaAttack.function = "Slavetrader_CreateLineShips";//создание линейных кораблей
			SetFunctionTimerCondition("Slavetrader_HavanaOver", 0, 0, 20, false);    //таймер
			characters[GetCharacterIndex("Havana_Mayor")].dialog.captureNode = "Slavetrader_HavanaAttack"; //капитулянтская нода мэра
			pchar.questTemp.Slavetrader = "wait1";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
		break;

		case "Win_Havana_Fort":
			pchar.quest.Slavetrader_FiveTSlavesOver.over = "yes";
			amount = 5000 - GetSquadronGoods(Pchar, GOOD_SLAVES);
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			if (amount < 1)
			{
				dialog.text = StringFromKey("Common_Usurer_598");
				link.l1 = StringFromKey("Common_Usurer_599", FindSlavesString(sti(sTemp)));
				link.l1.go = "Havana_Fort_yes";
				break;
			}
			if (amount < 4500 && amount >= 1)
			{
				dialog.text = StringFromKey("Common_Usurer_600", sTemp);
				link.l1 = StringFromKey("Common_Usurer_601");
				link.l1.go = "Havana_Fort_no";
				break;
			}
			dialog.text = StringFromKey("Common_Usurer_602");
			link.l1 = StringFromKey("Common_Usurer_603");
			link.l1.go = "Havana_Fort_no";
		break;

		case "Havana_Fort_no":
			dialog.text = StringFromKey("Common_Usurer_604");
			link.l1 = StringFromKey("Common_Usurer_605");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "29");
			SetFunctionTimerCondition("Slavetrader_HavanaSeekOver", 0, 0, 7, false);
			pchar.questTemp.Slavetrader = "Havana_seekslaves";
		break;

		case "Havana_Fort_yes":
			dialog.text = StringFromKey("Common_Usurer_606");
			link.l1 = StringFromKey("Common_Usurer_607", pchar);
			link.l1.go = "Havana_Fort_yes_1";
		break;

		case "Havana_Fort_yesA":
			dialog.text = StringFromKey("Common_Usurer_608");
			link.l1 = StringFromKey("Common_Usurer_609");
			link.l1.go = "Havana_Fort_yes_1";
			pchar.quest.Slavetrader_HavanaSeekOver.over = "yes";
		break;

		case "Havana_Fort_yes_1":
			sTemp = GetSquadronGoods(Pchar, GOOD_SLAVES);
			iSlaveMoney = makeint(sTemp) * 200;
			dialog.text = StringFromKey("Common_Usurer_610", sTemp, FindMoneyString(iSlaveMoney));
			link.l1 = StringFromKey("Common_Usurer_611", npchar.name);
			link.l1.go = "Havana_Fort_yes_2";
			RemoveCharacterGoods(Pchar, GOOD_SLAVES, sTemp);
		break;

		case "Havana_Fort_yes_2":
			dialog.text = StringFromKey("Common_Usurer_612", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_613");
			link.l1.go = "Havana_Fort_yes_3";
		break;

		case "Havana_Fort_yes_3":
			dialog.text = StringFromKey("Common_Usurer_614", pchar.name);
			link.l1 = StringFromKey("Common_Usurer_615", npchar.name);
			link.l1.go = "Havana_Fort_yes_4";
		break;

		case "Havana_Fort_yes_4":
			dialog.text = StringFromKey("Common_Usurer_616");
			link.l1 = StringFromKey("Common_Usurer_617");
			link.l1.go = "Havana_Fort_yes_5";
		break;

		case "Havana_Fort_yes_5":
			dialog.text = StringFromKey("Common_Usurer_618");
			link.l1 = StringFromKey("Common_Usurer_619", npchar.name);
			link.l1.go = "exit";
			pchar.questTemp.Slavetrader.Name = npchar.name;
			AddQuestRecord("Slavetrader", "32");
			SaveCurrentQuestDateParam("pchar.questTemp.Slavetrader_wait_6");
			SetFunctionTimerCondition("Slavetrader_UsurerEscape", 0, 0, 8, false);
			pchar.questTemp.Slavetrader = "wait_6";
			pchar.questTemp.Slavetrader.Cityname = npchar.city + "_town";
			LocatorReloadEnterDisable(npchar.city + "_town", "reload8_back", true);//чтобы не ходил неделю сюда вообще
			AddLandQuestmark_Main_WithCondition(npchar, "Slavetrader", "Slavetrader_Wait_6_Usurer_QuestMarkCondition");
		break;

		case "Usurer_Escape":
			dialog.text = StringFromKey("Common_Usurer_620");
			link.l1 = StringFromKey("Common_Usurer_621", pchar.questTemp.Slavetrader.Name);
			link.l1.go = "Usurer_Escape_1";
		break;

		case "Usurer_Escape_1":
			dialog.text = StringFromKey("Common_Usurer_622");
			link.l1 = StringFromKey("Common_Usurer_623");
			link.l1.go = "Usurer_Escape_2";
		break;

		case "Usurer_Escape_2":
			dialog.text = StringFromKey("Common_Usurer_624");
			link.l1 = StringFromKey("Common_Usurer_625");
			link.l1.go = "Usurer_Escape_3";
		break;

		case "Usurer_Escape_3":
			dialog.text = StringFromKey("Common_Usurer_626");
			link.l1 = StringFromKey("Common_Usurer_627");
			link.l1.go = "Usurer_Escape_4";
		break;

		case "Usurer_Escape_4":
			dialog.text = StringFromKey("Common_Usurer_628");
			link.l1 = StringFromKey("Common_Usurer_629", pchar, npchar.name);
			link.l1.go = "Usurer_Escape_5";
		break;

		case "Usurer_Escape_5":
			string sColony;
			sColony = npchar.city;
			SetNull2Deposit(sColony);
			dialog.text = StringFromKey("Common_Usurer_630");
			link.l1 = StringFromKey("Common_Usurer_631");
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "33");
			SetCharacterPerk(pchar, "SlaveTraderTrait");
			AddQuestUserData("Slavetrader", "sSex", GetSexPhrase("ёл", "ла"));
			CloseQuestHeader("Slavetrader");
			pchar.questTemp.Slavetrader = "wait1";
			RemoveLandQuestmark_Main(npchar, "Slavetrader");
			RemoveMapQuestMark(npchar.city + "_town", "Slavetrader");
			Achievment_Set(ACH_Rabotorgovets);
		break;

		//<--работорговец

		//--> семейная реликвия
		case "Noblelombard":
			dialog.text = StringFromKey("Common_Usurer_632", pchar.GenQuest.Noblelombard.Name, FindMoneyString(sti(pchar.GenQuest.Noblelombard.Summ)), FindMoneyString(sti(pchar.GenQuest.Noblelombard.Money)), FindMoneyString(sti(pchar.GenQuest.Noblelombard.Percent)));
			if (sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Summ))
			{
				link.l1 = StringFromKey("Common_Usurer_633", FindMoneyString(sti(pchar.GenQuest.Noblelombard.Summ)));
				link.l1.go = "Noblelombard_1";
			}
			if (sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent) * 2)
			{
				link.l2 = StringFromKey("Common_Usurer_634", FindMoneyString(sti(pchar.GenQuest.Noblelombard.Percent) * 2));
				link.l2.go = "Noblelombard_2";
			}
			if (sti(pchar.money) >= sti(pchar.GenQuest.Noblelombard.Percent))
			{
				link.l3 = StringFromKey("Common_Usurer_635");
				link.l3.go = "Noblelombard_3";
			}
			link.l4 = StringFromKey("Common_Usurer_636");
			link.l4.go = "Noblelombard_4";
			pchar.questTemp.noblelombard = "true";
			RemoveLandQuestMark_Gen(npchar, "Noblelombard");
		break;

		case "Noblelombard_1":
			dialog.text = StringFromKey("Common_Usurer_637", pchar.GenQuest.Noblelombard.Name);
			link.l1 = StringFromKey("Common_Usurer_638", npchar.name);
			link.l1.go = "exit";
			IncreaseUsurerDisposition(2);
			pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Summ) * 2;
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Summ));
			pchar.GenQuest.Noblelombard = "full";
			AddCharacterExpToSkill(pchar, "Leadership", 150);
		break;

		case "Noblelombard_2":
			if (sti(pchar.GenQuest.Noblelombard.Chance) < 7)
			{
				dialog.text = StringFromKey("Common_Usurer_639", pchar.GenQuest.Noblelombard.Name);
				link.l1 = StringFromKey("Common_Usurer_640");
				link.l1.go = "exit";
				IncreaseUsurerDisposition(1);
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent) * 4;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent) * 2);
				pchar.GenQuest.Noblelombard = "maxpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 70);

			}
			else
			{
				dialog.text = StringFromKey("Common_Usurer_641");
				link.l1 = StringFromKey("Common_Usurer_642");
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 30);

			}
		break;

		case "Noblelombard_3":
			if (sti(pchar.GenQuest.Noblelombard.Chance) < 3)
			{
				dialog.text = StringFromKey("Common_Usurer_643", pchar.GenQuest.Noblelombard.Name);
				link.l1 = StringFromKey("Common_Usurer_644");
				link.l1.go = "exit";
				pchar.GenQuest.Noblelombard.Regard = sti(pchar.GenQuest.Noblelombard.Percent) * 2;
				AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Noblelombard.Percent));
				pchar.GenQuest.Noblelombard = "minpercent";
				AddCharacterExpToSkill(pchar, "Leadership", 50);
				AddCharacterExpToSkill(pchar, "Fortune", 150);
			}
			else
			{
				dialog.text = StringFromKey("Common_Usurer_645");
				link.l1 = StringFromKey("Common_Usurer_646");
				link.l1.go = "Noblelombard_4";
				AddCharacterExpToSkill(pchar, "Fortune", 60);

			}
		break;

		case "Noblelombard_4":
			DialogExit();
			pchar.GenQuest.Noblelombard = "fail";
		break;

		case "Noblelombard_5":
			if (sti(pchar.GenQuest.Noblelombard.Chance) == 9)
			{
				dialog.text = StringFromKey("Common_Usurer_647", pchar.GenQuest.Noblelombard.Name);
				link.l1 = StringFromKey("Common_Usurer_648");
				link.l1.go = "Noblelombard_6";
			}
			else
			{
				dialog.text = StringFromKey("Common_Usurer_649", pchar.GenQuest.Noblelombard.Name);
				link.l1 = StringFromKey("Common_Usurer_650", npchar.name);
				link.l1.go = "Noblelombard_9";
			}
		break;

		case "Noblelombard_6":
			dialog.text = StringFromKey("Common_Usurer_651", pchar.GenQuest.Noblelombard.Name);
			link.l1 = StringFromKey("Common_Usurer_652", npchar.name);
			link.l1.go = "Noblelombard_7";
		break;

		case "Noblelombard_7":
			DialogExit();
			AddQuestRecord("Noblelombard", "6");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "questTemp.noblelombard");
			RemoveLandQuestMark_Gen(npchar, "Noblelombard");
		break;

		case "Noblelombard_9":
			DialogExit();
			iTemp = sti(pchar.GenQuest.Noblelombard.Regard);
			AddMoneyToCharacter(pchar, iTemp);
			AddQuestRecord("Noblelombard", "7");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			DeleteAttribute(Pchar, "questTemp.noblelombard");
			RemoveLandQuestMark_Gen(npchar, "Noblelombard");
		break;
		//<-- семейная реликвия		

		// > торговля
		case "items":
			if (npchar.quest.item_date != lastspeak_date)
			{
				GiveItemToTrader(npchar);
				npchar.quest.item_date = lastspeak_date;
			}

			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
			LaunchItemsTrade(NPChar);
		break;
		// < торговля

		// evganat - энциклопедия
		case "Encyclopedia_FirstTime":
			dialog.text = StringFromKey("Common_Usurer_653");
			link.l1 = StringFromKey("Common_Usurer_654");
			link.l1.go = "Encyclopedia_FT2";
		break;

		case "Encyclopedia_FT2":
			if (CheckRandomPage("usurer", npchar.city, sti(npchar.nation)))
			{
				npchar.encyclopedia.tome = GetRandomTome();
				npchar.encyclopedia.page = 4;
				dialog.text = StringFromKey("Common_Usurer_655");
				link.l1 = StringFromKey("Common_Usurer_656");
				link.l1.go = "Encyclopedia_Price";
			}
			else
			{
				SaveCurrentNpcQuestDateParam(npchar, "encyclopedia.last_date");
				dialog.text = StringFromKey("Common_Usurer_657");
				link.l1 = StringFromKey("Common_Usurer_658");
				link.l1.go = "exit";
			}
		break;

		case "Encyclopedia_Price":
			bool bDispG = (GetUsurerDisposition() >= 7);    // отношение
			bool bRepG = (sti(pchar.reputation) > 60);        // репутация "честный капитан" и выше
			bool bRepB = (sti(pchar.reputation) <= 20);        // репутация "негодяй" и ниже
			bool bLeadG = (GetCharacterSkill(pchar, SKILL_LEADERSHIP) >= 50);    // лидерство
			bool bLeadB = (GetCharacterSkill(pchar, SKILL_LEADERSHIP) <= 20);
			bool bComG = (GetCharacterSkill(pchar, SKILL_COMMERCE) >= 50);    // торговля
			bool bComB = (GetCharacterSkill(pchar, SKILL_COMMERCE) <= 20);
			int iScore = bDispG + bDispG + bRepG - bRepB + bLeadG - bLeadB + bComG - bComB;
			if (bRepB)
			{
				PlayerRPGCheck_Reputation_NotifyFail("good");
			}
			if (bLeadB)
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
			}
			if (bComB)
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_COMMERCE, false);
			}

			int iPrice;
			if (iScore == 5)    // всё идеально, бесплатно
			{
				iPrice = 0;
				dialog.text = StringFromKey("Common_Usurer_659");
				link.l1 = StringFromKey("Common_Usurer_660", pchar);
				link.l1.go = "Encyclopedia_AddPage";
				break;
			}

			if (iScore >= -1)
			{
				iPrice = 16000;
				dialog.text = StringFromKey("Common_Usurer_661", FindMoneyString(iPrice));
			}

			if (iScore >= 1)    // так себе, по минимуму, цена 12000
			{
				iPrice = 8000;
				dialog.text = StringFromKey("Common_Usurer_662", FindMoneyString(iPrice));
			}

			if (iScore >= 3)    // неидеально, но плюсов больше, цена 4000
			{
				iPrice = 4000;
				dialog.text = StringFromKey("Common_Usurer_663", FindMoneyString(iPrice));
			}

			if (iScore < -1)    // ужас, 36000
			{
				iPrice = 32000;
				dialog.text = StringFromKey("Common_Usurer_664", FindMoneyString(iPrice));
			}
			npchar.encyclopedia.curPrice = iPrice;
			if (sti(pchar.money) >= iPrice)
			{
				link.l1 = StringFromKey("Common_Usurer_665");
				link.l1.go = "Encyclopedia_Buy";
			}
			link.l2 = StringFromKey("Common_Usurer_666");
			link.l2.go = "exit";
		break;

		case "Encyclopedia_Buy":
			AddMoneyToCharacter(pchar, -sti(npchar.encyclopedia.curPrice));
			DeleteAttribute(npchar, "encyclopedia.curPrice");
			dialog.text = StringFromKey("Common_Usurer_667");
			link.l1 = StringFromKey("Common_Usurer_668");
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
			dialog.text = StringFromKey("Common_Usurer_669", FindMoneyString(sti(npchar.encyclopedia.curPrice)));
			if (sti(pchar.money) >= sti(npchar.encyclopedia.curPrice))
			{
				link.l1 = StringFromKey("Common_Usurer_670");
				link.l1.go = "Encyclopedia_Buy";
			}
			link.l2 = StringFromKey("Common_Usurer_671");
			link.l2.go = "exit";
		break;

		case "Encyclopedia_Check":
			if (CheckAttribute(pchar, "encyclopedia.gen.usurer.colonies." + npchar.city) && sti(pchar.encyclopedia.gen.usurer.colonies) < 8)
			{
				dialog.text = StringFromKey("Common_Usurer_672");
				link.l1 = StringFromKey("Common_Usurer_673");
				link.l1.go = "exit";
				break;
			}

			if (GetNpcQuestPastDayParam(npchar, "encyclopedia.last_date") < 7)
			{
				dialog.text = StringFromKey("Common_Usurer_674");
				link.l1 = StringFromKey("Common_Usurer_675", pchar);
				link.l1.go = "exit";
			}
			else
			{
				if (CheckRandomPage("usurer", npchar.city, sti(npchar.nation)))
				{
					npchar.encyclopedia.tome = GetRandomTome();
					npchar.encyclopedia.page = 4;
					dialog.text = StringFromKey("Common_Usurer_676");
					link.l1 = StringFromKey("Common_Usurer_677", pchar);
					link.l1.go = "Encyclopedia_Price";
				}
				else
				{
					SaveCurrentNpcQuestDateParam(npchar, "encyclopedia.last_date");
					dialog.text = StringFromKey("Common_Usurer_678");
					link.l1 = StringFromKey("Common_Usurer_679");
					link.l1.go = "exit";
				}
			}
		break;
		//HardCoffee обмен молюсков -->
		case "pinctadosOffer":
			dialog.text = StringFromKey("Common_Usurer_681");
			link.l1 = StringFromKey("Common_Usurer_682");
			link.l1.go = "pinctadosDaze";
		break;
		case "pinctadosDaze":
			dialog.text = StringFromKey("Common_Usurer_683");
			link.l1 = StringFromKey("Common_Usurer_684");
			link.l1.go = "pinctadosNegation";
		break;
		case "pinctadosNegation":
			dialog.text = StringFromKey("Common_Usurer_685");
			link.l1 = StringFromKey("Common_Usurer_686");
			link.l1.go = "pinctadosBargain";
		break;
		case "pinctadosBargain":
			dialog.text = StringFromKey("Common_Usurer_687");
			link.l1 = StringFromKey("Common_Usurer_688");
			link.l1.go = "pinctadosAccept";
		break;
		case "pinctadosAccept":
			dialog.text = StringFromKey("Common_Usurer_689");
			link.l1 = StringFromKey("Common_Usurer_690");
			link.l1.go = "pinctadosMakeADeal";
		break;
		case "pinctadosMakeADeal":
			NPChar.pinctadosMakeADeal = "1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			int iTime = GetSquadronGoods(pchar, GOOD_PINCTADA) / sti(Goods[GOOD_PINCTADA].Units);
			if (GetOfficersPerkUsing(pchar, "QuickCalculation", false)) iTime /= 2;
			if (iTime < 1) iTime = 1;
			int iSmall = 0;
			int iBig = 0;
			ConvertPinctadaToPearlItems(pchar, &iSmall, &iBig);
			makefloat(&iSmall);
			makefloat(&iBig);
			iSmall *= 0.8; //Чтобы имел смысл сдавать их контрабандистам
			iBig *= 0.8;
			iTemp = 10 - GetCharacterSPECIAL(pchar, "Charisma");
			if (iTemp > 4) iTemp = 4;
			float fraud = 0.1 * makefloat(idRand(NPChar.id, iTemp)); //на сколько жемчужин банкир облапошит гг
			iSmall = iSmall - iSmall * fraud;
			iBig = iBig - iBig * fraud;
			makeint(&iSmall);
			makeint(&iBig);
			TEV.CrackPinctadosSmall = iSmall;
			TEV.CrackPinctadosBig = iBig;

			DialogExit();

			if (iTime < 2)
				SetLaunchFrameFormParam(StringFromKey("InfoMessages_250"), "CrackPinctados", 0, 3);
			else
				SetLaunchFrameFormParam(StringFromKey("InfoMessages_23"), "CrackPinctados", 0, 3);

			LAi_MethodDelay("LaunchFrameForm", 0.2);
			WaitDate("", 0, 0, 0, iTime, 0);
			RefreshLandTime();
			RecalculateJumpTable();
		break;
		case "pinctadosAgain":
			dialog.Text = StringFromKey("Common_Usurer_700", LinkRandPhrase(
				StringFromKey("Common_Usurer_694"),
				StringFromKey("Common_Usurer_695"),
				StringFromKey("Common_Usurer_696")));
			link.l1 = StringFromKey("Common_Usurer_700", LinkRandPhrase(
				StringFromKey("Common_Usurer_697"),
				StringFromKey("Common_Usurer_698"),
				StringFromKey("Common_Usurer_699")));
			link.l1.go = "pinctadosMakeADeal";
		break;
		//обмен молюсков <-
	}
}

int findCitizenMan(ref NPChar, bool bCity)
{
	ref ch;
	int n, nation;
	int storeArray[MAX_COLONIES];
	int howStore = 0;

	if (bCity && sti(Pchar.Ship.Type) == SHIP_NOTUSED)
	{
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", RandCitizenModel(), "man", "man", 10, sti(npchar.nation), -1, false));
		ch.dialog.filename = "Common_Citizen.c";
		ch.city = npchar.city;
		ch.RebirthPhantom = true;
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(npchar.nation)) + "_citizens");
		PlaceCharacter(ch, "goto", npchar.city + "_town");
	}
	else
	{
		for (n = 0; n < MAX_COLONIES; n++)
		{
			nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
			if (nation != RELATION_ENEMY && colonies[n].nation != "none")
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
		if (howStore == 0) return -1;
		nation = storeArray[idRand("findCitizenMan_" + NPChar.id, howStore - 1)];
		ch = GetCharacter(NPC_GenerateCharacter("LoanFindingMan", RandCitizenModel(), "man", "man", 10, sti(colonies[nation].nation), -1, false));
		ch.dialog.filename = "Common_Citizen.c";
		ch.city = colonies[nation].id;
		ch.RebirthPhantom = true;
		LAi_NoRebirthDisable(ch);
		LAi_SetCitizenType(ch);
		LAi_group_MoveCharacter(ch, GetNationNameByType(sti(colonies[nation].nation)) + "_citizens");
		PlaceCharacter(ch, "goto", colonies[nation].id + "_town");
	}
	return sti(ch.index);
}

int findChestMan(ref NPChar)
{
	ref ch;
	int n;
	int storeArray[TOTAL_CHARACTERS];
	int howStore = 0;
	string sTemp, sCity;

	for (n = 2; n < MAX_CHARACTERS; n++)
	{
		makeref(ch, Characters[n]);
		sTemp = ch.id;
		if (CheckAttribute(ch, "City") && ch.id != "Jackman") sCity = ch.City;
		else continue;
		sTemp = strcut(sTemp, strlen(sCity) + 1, strlen(sTemp) - 1);
		// магазины
		if (sTemp == "trader")
		{
			if (NPChar.city == ch.city) continue;
			if (ch.location == "none") continue;
			storeArray[howStore] = n;
			howStore++;
		}
		// мэры
		if (sTemp == "Mayor")
		{
			if (NPChar.city == ch.city) continue;
			if (sti(ch.nation) == PIRATE) continue; // пираты не имеют реплик
			if (ch.location == "none") continue;
			if (ch.location != ch.Default) continue; //захвачанных мэров не надо
			storeArray[howStore] = n;
			howStore++;
		}
		// верфисты
		if (sTemp == "shipyarder")
		{
			if (NPChar.city == ch.city) continue;
			if (ch.location == "none") continue;
			storeArray[howStore] = n;
			howStore++;
		}
		// тавернщики
		if (sTemp == "tavernkeeper")
		{
			if (NPChar.city == ch.city) continue;
			if (ch.location == "none") continue;
			storeArray[howStore] = n;
			howStore++;
		}
		// церковники
		if (sTemp == "Priest")
		{
			if (NPChar.city == ch.city) continue;
			if (ch.location == "none") continue;
			storeArray[howStore] = n;
			howStore++;
		}
		// ростовщики
		if (sTemp == "usurer")
		{
			if (NPChar.city == ch.city) continue;
			if (ch.location == "none") continue;
			storeArray[howStore] = n;
			howStore++;
		}
		// начальники портов
		if (sTemp == "PortMan")
		{
			if (NPChar.city == ch.city) continue;
			if (ch.location == "none") continue;
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0)
	{
		return -1;
	}
	else
	{
		return storeArray[idRand("findChestMan_" + NPChar.id, howStore - 1)];
	}
}

void SlavetraderGalleonInWorld()
{
	//создаем галеон с рабами
	ref sld;
	string sName;
	sName = pchar.questTemp.Slavetrader.ShipName;
	sld = GetCharacter(NPC_GenerateCharacter("GaleonCap", "navy_off_spa_1", "man", "man", 45, SPAIN, -1, true));
	SetCaptanModelByEncType(sld, "war");
	FantomMakeCoolSailor(sld, SHIP_WARSHIP, sName, CANNON_TYPE_CANNON_LBS32, 100, 100, 100);
	FantomMakeCoolFighter(sld, 45, 100, 100, "blade28", "pistol5", 100);//создание фантома кэпа	
	sld.Ship.Mode = "war";
	DeleteAttribute(sld, "SinkTenPercent");
	DeleteAttribute(sld, "SaveItemsForDead");
	DeleteAttribute(sld, "DontClearDead");
	DeleteAttribute(sld, "AboardToFinalDeck");
	DeleteAttribute(sld, "DontRansackCaptain");
	sld.AlwaysSandbankManeuver = true;
	sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	sld.DontRansackCaptain = true; //не сдаваться
	sld.WatchFort = true; //видеть форты
	sld.AlwaysEnemy = true;
	sld.SuperShooter = true;
	SetCharacterPerk(sld, "StormProfessional");
	SetCharacterPerk(sld, "SwordplayProfessional");
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "CriticalHit");
	SetCharacterPerk(sld, "MusketsShoot");
	SetCharacterPerk(sld, "Sliding");
	SetCharacterPerk(sld, "Tireless");
	SetCharacterPerk(sld, "HardHitter");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterGoods(sld, GOOD_SLAVES, 3000 + rand(200));//положить в трюм рабов
	sld.ship.Crew.Morale = 100;
	ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);
	//в морскую группу кэпа
	string sGroup = "SlaveGalleon";
	Group_FindOrCreateGroup(sGroup);
	Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
	Group_LockTask(sGroup);
	Group_AddCharacter(sGroup, sld.id);
	Group_SetGroupCommander(sGroup, sld.id);
	SetRandGeraldSail(sld, sti(sld.Nation));
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1 = "Group_Death";//условие победы
	pchar.quest.SlaveHalleon_AfterBattle.win_condition.l1.group = "SlaveGalleon";//какую группу уничтожить
	pchar.quest.SlaveHalleon_AfterBattle.function = "Slavetrader_SlaveHalleon_AfterBattle";//это победа
	sld.city = pchar.questTemp.Slavetrader.Island; //определим колонию, из бухты которой выйдет
	sld.cityShore = pchar.questTemp.Slavetrader.Island.Shore;
	sld.quest.targetCity = "Santiago"; //определим колонию, в бухту которой он придет
	sld.quest.targetShore = GetIslandRandomShoreId(GetArealByCityName(sld.quest.targetCity));
	Log_TestInfo("Кэп галеона вышел из: " + sld.city + " и направился в: " + sld.quest.targetShore + "");
	//==> на карту
	sld.mapEnc.type = "trade";
	//выбор типа кораблика на карте
	sld.mapEnc.worldMapShip = "quest_ship";
	sld.mapEnc.Name = XI_ConvertString("Galeon") + " '" + sName + "'";
	int daysQty = 20; //дней доехать даем с запасом
	Map_CreateTrader(sld.cityShore, sld.quest.targetShore, sld.id, daysQty);//вот он, сам запуск энкаунтера
	sld.lifeDay = 20;
}

// evganat - отношение ростовщика
void IncreaseUsurerDisposition(int add)
{
	IncreaseNPCDisposition(CharacterRef, add);
}

int GetUsurerDisposition()
{
	return GetNPCDisposition(CharacterRef);
}

/*
	Отношение:
	+2 проклятый идол
	+3 блудный сын, благодарность
	-2 блудный сын, неблагодарность
	+3 успешно выбил долг
	-1 отмена задания с должником
	-2 провал задания с должником
	-1/2/3 каждая попытка обмана
	+3 успешно доставил сундуки
	-2 просрочка доставки сундуков
	+3 доставил сундуки с опозданием
	-1 отмена доставки сундуков
	+1 возврат кредита
	-5 просрочка кредита
	+6 двукратное возмещение после просрочки кредита
	+1, если есть вклад
	+2 задание с драгоценным камнем
	+2/1 оплата долга/процентов за семейную реликвию
	
	Нужно от 4
*/
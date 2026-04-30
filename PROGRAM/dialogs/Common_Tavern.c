#include "DIALOGS\Rumours\Simple_rumors.c"  //homo 25/06/06
#include "interface\ship.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Tavern\" + NPChar.City + "_Tavern.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	int iTest, iTemp;
	string sTemp;
	iTest = FindColony(NPChar.City); // город
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	bool ok;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Tavern_4", LinkRandPhrase(
								StringFromKey("Common_Tavern_1"),
								StringFromKey("Common_Tavern_2"),
								StringFromKey("Common_Tavern_3", pchar))),
						StringFromKey("Common_Tavern_8", LinkRandPhrase(
								StringFromKey("Common_Tavern_5", pchar),
								StringFromKey("Common_Tavern_6", pchar),
								StringFromKey("Common_Tavern_7", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Tavern_11", RandPhraseSimple(
								StringFromKey("Common_Tavern_9"),
								StringFromKey("Common_Tavern_10"))),
						StringFromKey("Common_Tavern_14", RandPhraseSimple(
								StringFromKey("Common_Tavern_12", GetWorkTypeOfMan(npchar, "")),
								StringFromKey("Common_Tavern_13", GetWorkTypeOfMan(npchar, "")))));
				link.l1.go = "exit";
				break;
			}

			// homo линейка капитана Блада
			if (Pchar.questTemp.CapBloodLine == true)
			{
				dialog.Text = StringFromKey("Common_Tavern_18", LinkRandPhrase(
							StringFromKey("Common_Tavern_15", TimeGreeting()),
							StringFromKey("Common_Tavern_16"),
							StringFromKey("Common_Tavern_17", GetFullName(pchar))));
				Link.l1 = StringFromKey("Common_Tavern_19", NPChar.name);
				Link.l1.go = "exit";

				if (Pchar.questTemp.CapBloodLine.stat == "WakerOffer")
				{
					link.l2 = StringFromKey("Common_Tavern_20", NPChar.name);
					link.l2.go = "TStep_0";
				}

				if (Pchar.questTemp.CapBloodLine.stat == "PrepareToEscape")
				{
					link.l2 = StringFromKey("Common_Tavern_21");
					link.l2.go = "TStep_1";
				}

				if (Pchar.questTemp.CapBloodLine.stat == "needMoney" && CheckAttribute(pchar, "questTemp.CapBloodLine.QuestRaff") && pchar.questTemp.CapBloodLine.QuestRaff == true)
				{
					link.l2 = StringFromKey("Common_Tavern_22");
					link.l2.go = "TStep_5";
				}
				break;
			}

			//зачарованный город -->
			if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
			{
				dialog.text = StringFromKey("Common_Tavern_23");
				link.l1 = StringFromKey("Common_Tavern_24");
				link.l1.go = "MCTavern";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasWervolf" && npchar.city == "Caracas")
			{
				dialog.text = StringFromKey("Common_Tavern_25");
				link.l1 = StringFromKey("Common_Tavern_26");
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				dialog.text = StringFromKey("Common_Tavern_27");
				link.l1 = StringFromKey("Common_Tavern_28", pchar);
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasTavern" && npchar.city == "Caracas")
			{
				dialog.text = StringFromKey("Common_Tavern_29");
				link.l1 = StringFromKey("Common_Tavern_30");
				link.l1.go = "MCCaracasAfter";
				break;
			}
			//<-- зачарованный город 

			if (NPChar.quest.meeting == "0")
			{
				if (npchar.city == "Pirates")
				{
					dialog.Text = StringFromKey("Common_Tavern_31", pchar);
					Link.l1 = StringFromKey("Common_Tavern_32", pchar);
					Link.l1.go = "Pirates_1";
					NPChar.quest.meeting = "1";
					break;
				}
				if (npchar.city == "Charles")
				{
					dialog.Text = StringFromKey("Common_Tavern_33", GetAddress_Form(NPChar), GetFullName(npchar));
					Link.l1 = StringFromKey("Common_Tavern_34", pchar);
					Link.l1.go = "Charles_1";
					NPChar.quest.meeting = "1";
					break;
				}
				if (npchar.city == "Portobello")
				{
					dialog.Text = StringFromKey("Common_Tavern_35", GetAddress_Form(NPChar), GetFullName(npchar));
					Link.l1 = StringFromKey("Common_Tavern_36", pchar);
					Link.l1.go = "Portobello_1";
					NPChar.quest.meeting = "1";
					break;
				}
				if (npchar.city == "FortFrance")
				{
					dialog.Text = StringFromKey("Common_Tavern_37", GetAddress_Form(NPChar), GetFullName(NPChar));
					Link.l1 = StringFromKey("Common_Tavern_38", npchar.name);
					Link.l1.go = "FortFrance_1";
					NPChar.quest.meeting = "1";
					break;
				}

				if (CheckAttribute(loadedlocation, "tavern_name"))
				{
					dialog.Text = StringFromKey("Common_Tavern_39", FindStringAfterSubStr(GetConvertStr(loadedlocation.tavern_name, "LocLables.txt"), " "), GetAddress_Form(NPChar));
				}
				else dialog.Text = StringFromKey("Common_Tavern_40", GetAddress_Form(NPChar));
				Link.l1 = StringFromKey("Common_Tavern_41", GetFullName(pchar));
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				// Квестовый генератор священника. Квест №1. Warship -->
				if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
				{
					if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NoMoneyToBarmen"))
					{
						iTemp = sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen);
						dialog.Text = StringFromKey("Common_Tavern_42", FindMoneyString(iTemp));
						if (sti(PChar.Money) >= iTemp)
						{
							link.l1 = StringFromKey("Common_Tavern_43", pchar);
							link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
						}
						else
						{
							link.l1 = StringFromKey("Common_Tavern_44", pchar);
							link.l1.go = "exit";
						}
					}
					else
					{
						dialog.Text = StringFromKey("Common_Tavern_45", pchar);
						link.l1 = StringFromKey("Common_Tavern_46");
						link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
					}
					break;
				}
				// <-- Квестовый генератор священника. Квест №1.

				dialog.Text = StringFromKey("Common_Tavern_50", LinkRandPhrase(
							StringFromKey("Common_Tavern_47", GetAddress_Form(NPChar), PChar.name, TimeGreeting()),
							StringFromKey("Common_Tavern_48", GetAddress_Form(NPChar), PChar.name),
							StringFromKey("Common_Tavern_49", GetFullName(pchar))));
				Link.l1 = StringFromKey("Common_Tavern_51");
				Link.l1.go = "crew hire";
				if (GetGlobalTutor())
				{
					goto Common_Tavern_skipToExit_Common;
				}
				Link.l2 = StringFromKey("Common_Tavern_52");
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = StringFromKey("Common_Tavern_53");
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}

				// Квестовый генератор священника. Квест №2. Warship -->
				if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = StringFromKey("Common_Tavern_57", LinkRandPhrase(
								StringFromKey("Common_Tavern_54"),
								StringFromKey("Common_Tavern_55"),
								StringFromKey("Common_Tavern_56")));
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.

				//Jason --> захват пассажиров
				if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity + "_tavern")
				{
					link.l20 = StringFromKey("Common_Tavern_58", pchar, pchar.GenQuest.Marginpassenger.q2Name);
					link.l20.go = "Marginpassenger";
				}
				// <-- захват пассажиров

				link.l3 = pcharrepphrase(
							StringFromKey("Common_Tavern_59"),
							StringFromKey("Common_Tavern_60", pchar));
				link.l3.go = "room";
				Common_Tavern_skipToExit_Common:
				Link.l4 = StringFromKey("Common_Tavern_61", NPChar.name);
				Link.l4.go = "exit";
			}
		break;

		case "Meeting":
		// Квестовый генератор священника. Квест №1. Warship -->
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_1.CurPortManColony + "_tavern")
			{
				dialog.Text = StringFromKey("Common_Tavern_62", pchar);
				link.l1 = StringFromKey("Common_Tavern_63");
				link.l1.go = "Tavern_ChurchGenQuest1_Node_1";
				break;
			}
			// <-- Квестовый генератор священника. Квест №1.
			if (npchar.city == "Pirates")
			{
				dialog.Text = StringFromKey("Common_Tavern_64", GetAddress_Form(NPChar));
				Link.l1 = StringFromKey("Common_Tavern_65", NPChar.name);
				Link.l1.go = "crew hire";
				Link.l2 = StringFromKey("Common_Tavern_66", NPChar.name);
				Link.l2.go = "int_quests";

				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = StringFromKey("Common_Tavern_67");
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}

				// Квестовый генератор священника. Квест №2. Warship -->
				if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = StringFromKey("Common_Tavern_71", LinkRandPhrase(
								StringFromKey("Common_Tavern_68"),
								StringFromKey("Common_Tavern_69"),
								StringFromKey("Common_Tavern_70")));
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}

				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase(
							StringFromKey("Common_Tavern_72"),
							StringFromKey("Common_Tavern_73", pchar));
				link.l3.go = "room";
				Link.l4 = StringFromKey("Common_Tavern_74");
				Link.l4.go = "exit";
				break;
			}

			if (npchar.city == "Charles")
			{
				dialog.Text = StringFromKey("Common_Tavern_75", GetAddress_Form(NPChar));
				Link.l1 = StringFromKey("Common_Tavern_76", NPChar.name);
				Link.l1.go = "crew hire";
				Link.l2 = StringFromKey("Common_Tavern_77", NPChar.name);
				Link.l2.go = "int_quests";
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = StringFromKey("Common_Tavern_78");
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				// Квестовый генератор священника. Квест №2. Warship -->
				if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = StringFromKey("Common_Tavern_82", LinkRandPhrase(
								StringFromKey("Common_Tavern_79"),
								StringFromKey("Common_Tavern_80"),
								StringFromKey("Common_Tavern_81")));
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}
				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase(
							StringFromKey("Common_Tavern_83"),
							StringFromKey("Common_Tavern_84", pchar));
				link.l3.go = "room";
				Link.l4 = StringFromKey("Common_Tavern_85");
				Link.l4.go = "exit";
				break;
			}

			if (npchar.city == "Portobello")
			{
				dialog.Text = StringFromKey("Common_Tavern_86", GetAddress_Form(NPChar));
				Link.l1 = StringFromKey("Common_Tavern_87", NPChar.name);
				Link.l1.go = "crew hire";
				Link.l2 = StringFromKey("Common_Tavern_88", NPChar.name);
				Link.l2.go = "int_quests";

				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = StringFromKey("Common_Tavern_89");
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				// Квестовый генератор священника. Квест №2. Warship -->
				if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = StringFromKey("Common_Tavern_93", LinkRandPhrase(
								StringFromKey("Common_Tavern_90"),
								StringFromKey("Common_Tavern_91"),
								StringFromKey("Common_Tavern_92")));
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}

				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase(
							StringFromKey("Common_Tavern_94"),
							StringFromKey("Common_Tavern_95", pchar));
				link.l3.go = "room";
				Link.l4 = StringFromKey("Common_Tavern_96");
				Link.l4.go = "exit";
				break;
			}

			if (npchar.city == "FortFrance")
			{
				dialog.Text = StringFromKey("Common_Tavern_97", pchar);
				Link.l1 = StringFromKey("Common_Tavern_98", NPChar.name);
				Link.l1.go = "crew hire";
				Link.l2 = StringFromKey("Common_Tavern_99", NPChar.name);
				Link.l2.go = "int_quests";

				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l21 = StringFromKey("Common_Tavern_100");
					link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
				}
				// Квестовый генератор священника. Квест №2. Warship -->
				if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					link.l10 = StringFromKey("Common_Tavern_104", LinkRandPhrase(
								StringFromKey("Common_Tavern_101"),
								StringFromKey("Common_Tavern_102"),
								StringFromKey("Common_Tavern_103")));
					link.l10.go = "Tavern_GenQuest_Church_2_1";
				}

				// <-- Квестовый генератор священника. Квест №2.
				link.l3 = pcharrepphrase(
							StringFromKey("Common_Tavern_105"),
							StringFromKey("Common_Tavern_106", pchar));
				link.l3.go = "room";
				Link.l4 = StringFromKey("Common_Tavern_107");
				Link.l4.go = "exit";
				break;
			}
			dialog.Text = StringFromKey("Common_Tavern_108", GetAddress_Form(NPChar), GetFullName(npchar));
			Link.l1 = StringFromKey("Common_Tavern_109", NPChar.name);
			Link.l1.go = "crew hire";
			if (GetGlobalTutor())
			{
				goto Common_Tavern_skipToExit;
			}
			Link.l2 = StringFromKey("Common_Tavern_110", NPChar.name);
			Link.l2.go = "int_quests";

			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l21 = StringFromKey("Common_Tavern_111");
				link.l21.go = "LoanForAll";//(перессылка в кредитный генератор)
			}

			// Квестовый генератор священника. Квест №2. Warship -->
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				link.l10 = StringFromKey("Common_Tavern_115", LinkRandPhrase(
							StringFromKey("Common_Tavern_112"),
							StringFromKey("Common_Tavern_113"),
							StringFromKey("Common_Tavern_114")));
				link.l10.go = "Tavern_GenQuest_Church_2_1";
			}
			// <-- Квестовый генератор священника. Квест №2.

			//Jason --> захват пассажиров
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "take" && NPChar.location == pchar.GenQuest.Marginpassenger.Targetcity + "_tavern")
			{
				link.l20 = StringFromKey("Common_Tavern_116", pchar, pchar.GenQuest.Marginpassenger.q2Name);
				link.l20.go = "Marginpassenger";
			}
			// <-- захват пассажиров

			link.l3 = pcharrepphrase(
						StringFromKey("Common_Tavern_117"),
						StringFromKey("Common_Tavern_118", pchar));
			link.l3.go = "room";
			Common_Tavern_skipToExit:
			Link.l4 = StringFromKey("Common_Tavern_119");
			Link.l4.go = "exit";
		break;

		case "crew hire":
			ok = CheckShipMooredInColony(rColony);
			if (!ok)
			{
				Dialog.text = StringFromKey("Common_Tavern_120");
				link.l1 = StringFromKey("Common_Tavern_123", RandPhraseSimple(
							StringFromKey("Common_Tavern_121", pchar),
							StringFromKey("Common_Tavern_122", pchar)));
				link.l1.go = "exit";
				break;
			}

			if (makeint(environment.time) > 22.0 || makeint(environment.time) < 7.0)
			{
				Dialog.text = StringFromKey("Common_Tavern_124");
				link.l1 = StringFromKey("Common_Tavern_125");
				link.l1.go = "room";
				link.l2 = StringFromKey("Common_Tavern_126");
				link.l2.go = "exit";
			}
			else
			{
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
				{
					Dialog.text = StringFromKey("Common_Tavern_127");
					link.l1 = StringFromKey("Common_Tavern_128");
					link.l1.go = "exit";
				}
				else
				{
					if (CheckAttribute(NPChar, "CrewHired.PGGId") && GetNpcQuestPastDayParam(NPChar, "CrewHired") < 3 && GetCrewQuantity(rColony) == 0)
					{
						Dialog.text = StringFromKey("Common_Tavern_129", GetFullName(CharacterFromID(NPChar.CrewHired.PGGId)));
						link.l1 = StringFromKey("Common_Tavern_130");
						link.l1.go = "exit";
						link.l2 = StringFromKey("Common_Tavern_432");
						link.l2.go = "hirecrew";
					}
					else
					{
						if ((Partition_GetSetting("Part_Crew") == 0) || GetPartitionAmount("CrewPayment") > 0)
						{
							dialog.text = StringFromKey("Common_Tavern_131");
							link.l1 = StringFromKey("Common_Tavern_132");
							link.l1.go = "exit";
						}
						else
						{
							DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
							NextDiag.CurrentNode = NextDiag.TempNode;
							DialogExit();
							LaunchHireCrew();
						}
					}
				}
			}
		break;

		case "hirecrew":
			DeleteAttribute(NPChar, "CrewHired"); //на всяк случай.
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchHireCrew();
		break;

		////////////////////////////////////////////////////////=============================================///////////////////////////////////////////////////////
		case "int_quests":
			dialog.text = StringFromKey("Common_Tavern_133");
			link.l1 = StringFromKey("Common_Tavern_134");
			link.l1.go = "work";
			//homo 15/06/06 слухи
			link.l2 = StringFromKey("Common_Tavern_138", LinkRandPhrase(
						StringFromKey("Common_Tavern_135"),
						StringFromKey("Common_Tavern_136"),
						StringFromKey("Common_Tavern_137")));
			link.l2.go = "rumours_tavern";
			//homo
			link.l3 = StringFromKey("Common_Tavern_139");
			link.l3.go = "quests";
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City")) //квест мэра по поиску шпиона
			{
				link.l4 = StringFromKey("Common_Tavern_140");
				if (pchar.GenQuest.SeekSpy.City == "0")
				{
					link.l4.go = "SeekSpy_Seen";
				}
				else
				{
					link.l4.go = "SeekSpy_NotSeen";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.EncGirl"))
			{
				if (pchar.GenQuest.EncGirl == "EncGirlFack_fighted")
				{
					link.l5 = StringFromKey("Common_Tavern_141", pchar.GenQuest.EncGirl.name);
					link.l5.go = "EncGirl_1";
				}
				if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					link.l6 = StringFromKey("Common_Tavern_142", pchar.GenQuest.EncGirl.sLoverId);
					link.l6.go = "EncGirl_3";
				}
				if (pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "tavern_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = StringFromKey("Common_Tavern_143", pchar);
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
			}
			if (CheckAttribute(pchar, "QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek"))
			{
				link.l8 = StringFromKey("Common_Tavern_144");
				link.l8.go = "Andre_Abel_Quest_TavernOwner_Dialog_1";
			}
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.City") && NPChar.city == pchar.GenQuest.CaptainComission.City && CheckAttribute(pchar, "GenQuest.CaptainComission.Speak_Tavern"))
			{
				if (pchar.GenQuest.CaptainComission.variant == "A0")
				{
					if (pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = StringFromKey("Common_Tavern_145", pchar.GenQuest.CaptainComission.Name);
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = StringFromKey("Common_Tavern_146", pchar.GenQuest.CaptainComission.Name);
						link.l9.go = "CaptainComission_1";
					}
				}

				if (pchar.GenQuest.CaptainComission.variant == "A2" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					link.l9 = StringFromKey("Common_Tavern_147", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.Name);
					link.l9.go = "CaptainComission_Tavern7";
				}
				if (pchar.GenQuest.CaptainComission.variant == "A3" && pchar.GenQuest.CaptainComission == "Begin_1")
				{
					if (pchar.GenQuest.CaptainComission.Speak_Tavern == true)
					{
						link.l9 = StringFromKey("Common_Tavern_148", GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
						link.l9.go = "CaptainComission_3";
					}
					else
					{
						link.l9 = StringFromKey("Common_Tavern_149", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.Name);
						link.l9.go = "CaptainComission_Tavern1";
						if (!CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour"))
						{
							pchar.GenQuest.CaptainComission.GetRumour = true;
							SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
						}
					}
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Hold_GenQuest") && NPChar.city == pchar.GenQuest.Hold_GenQuest.City && pchar.GenQuest.Hold_GenQuest.Speak_Tavern == false)
			{
				link.l10 = StringFromKey("Common_Tavern_150", pchar.GenQuest.Hold_GenQuest.Name);
				link.l10.go = "hold_genquest1";
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakTavern") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l11 = StringFromKey("Common_Tavern_151", pchar);
				link.l11.go = "ShipLetters_4";
			}

			//ОЗГ
			if (CheckAttribute(pchar, "questTemp.Headhunter"))
			{
				if (pchar.questTemp.Headhunter == "hunt_carlos" && npchar.city == pchar.questTemp.Headhunter.City)
				{
					link.l12 = StringFromKey("Common_Tavern_152");
					link.l12.go = "Seek_Carlos";
				}
			}

			//AlexBlade добавлена отдельная проверка для Эспаньолы
			//zagolski. начальный квест пирата
			if (CheckAttribute(pchar, "questTemp.pirateStartQuest") &&
			pchar.questTemp.pirateStartQuest == "1" &&
			or(GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal, StrStartsWith(pchar.questTemp.pirateStartQuest.Areal, "Hispaniola")) &&
			npchar.city != pchar.questTemp.pirateStartQuest.City)
			{
				if (!CheckAttribute(pchar, "questTemp.pirateStartQuest.TavernInfo"))
				{
					link.l12 = StringFromKey("Common_Tavern_153");
					link.l12.go = "pirateStartQuest_Tavern";
				}
				else
				{
					if (sti(pchar.money) >= 1000)
					{
						link.l12 = StringFromKey("Common_Tavern_154");
						link.l12.go = "pirateStartQuest_Tavern_2";
					}
				}
			}

			link.l15 = StringFromKey("Common_Tavern_155");
			link.l15.go = "exit";
		break;

		//-------------------------------------------
		case "pirateStartQuest_Tavern":
			dialog.text = StringFromKey("Common_Tavern_156", pchar);
			link.l1 = StringFromKey("Common_Tavern_157", pchar);
			link.l1.go = "pirateStartQuest_Tavern_1";
		break;
		case "pirateStartQuest_Tavern_1":
			dialog.text = StringFromKey("Common_Tavern_158");
			if (sti(pchar.money) >= 1000)
			{
				link.l1 = StringFromKey("Common_Tavern_159");
				link.l1.go = "pirateStartQuest_Tavern_2";
			}
			else
			{
				link.l1 = StringFromKey("Common_Tavern_160");
				link.l1.go = "exit";
				pchar.questTemp.pirateStartQuest.TavernInfo = "";
			}
		break;
		case "pirateStartQuest_Tavern_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = StringFromKey("Common_Tavern_161");
			link.l1 = StringFromKey("Common_Tavern_162");
			link.l1.go = "pirateStartQuest_Tavern_3";
		break;
		case "pirateStartQuest_Tavern_3":
			dialog.text = StringFromKey("Common_Tavern_163");
			link.l1 = StringFromKey("Common_Tavern_164");
			link.l1.go = "exit";

			PChar.questTemp.pirateStartQuest = "2";
			pchar.questTemp.pirateStartQuest.City2 = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(npchar.city); // ставим новый Ареал
			DeleteAttribute(pchar, "questTemp.pirateStartQuest.TavernInfo");
			AddQuestRecord("pSQ", "2");
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
			if (StrStartsWith(pchar.questTemp.pirateStartQuest.Areal, "Hispaniola"))
			{
				RemoveLandQuestMark_Main(CharacterFromID("SantoDomingo_tavernkeeper"), "pSQ");
				RemoveLandQuestMark_Main(CharacterFromID("PortPax_tavernkeeper"), "pSQ");
			}
			RemoveLandQuestMark_Main(npchar, "pSQ");
			AddLandQuestMark_Main(CharacterFromID(pchar.questTemp.pirateStartQuest.City2 + "_Smuggler"), "pSQ");
		break;

		case "hold_genquest1":
			switch (sti(pchar.GenQuest.Hold_GenQuest.TavernVariant))
			{
				case 0:
					dialog.text = StringFromKey("Common_Tavern_168", LinkRandPhrase(
								StringFromKey("Common_Tavern_165", pchar.GenQuest.Hold_GenQuest.Name),
								StringFromKey("Common_Tavern_166"),
								StringFromKey("Common_Tavern_167")));
					link.l1 = StringFromKey("Common_Tavern_169");
					link.l1.go = "hold_genquest2";
				break;

				case 1:
					switch (idRand(npchar.id + "hold_genquest1", 3))
					{
						case 0:
							pchar.GenQuest.Hold_GenQuest.foundStr = StringFromKey("Common_Tavern_170");
							pchar.GenQuest.Hold_GenQuest.found = "church";
						break;
						case 1:
							if (npchar.city != "Panama")
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = StringFromKey("Common_Tavern_171");
								pchar.GenQuest.Hold_GenQuest.found = "shipyard";
							}
							else
							{
								pchar.GenQuest.Hold_GenQuest.foundStr = StringFromKey("Common_Tavern_172");
								pchar.GenQuest.Hold_GenQuest.found = "church";
							}
						break;
						case 2:
							pchar.GenQuest.Hold_GenQuest.foundStr = StringFromKey("Common_Tavern_173");
							pchar.GenQuest.Hold_GenQuest.found = "bank";
						break;
						case 3:
							pchar.GenQuest.Hold_GenQuest.foundStr = StringFromKey("Common_Tavern_174");
							pchar.GenQuest.Hold_GenQuest.found = "store";
						break;
					}
					dialog.text = StringFromKey("Common_Tavern_175", pchar.GenQuest.Hold_GenQuest.foundStr);
					link.l1 = StringFromKey("Common_Tavern_176");
					link.l1.go = "hold_genquest3";
				break;

				case 2:
					dialog.text = StringFromKey("Common_Tavern_184", LinkRandPhrase(
								StringFromKey("Common_Tavern_179", RandPhraseSimple(
										StringFromKey("Common_Tavern_177", pchar.GenQuest.Hold_GenQuest.Name),
										StringFromKey("Common_Tavern_178"))),
								StringFromKey("Common_Tavern_182", RandPhraseSimple(
										StringFromKey("Common_Tavern_180"),
										StringFromKey("Common_Tavern_181"))),
								StringFromKey("Common_Tavern_183", pchar.GenQuest.Hold_GenQuest.Name)));
					link.l1 = StringFromKey("Common_Tavern_185");
					link.l1.go = "hold_genquest4";
				break;

				case 3:
					dialog.text = StringFromKey("Common_Tavern_186");
					link.l1 = StringFromKey("Common_Tavern_187");
					link.l1.go = "hold_genquest5";
				break;
			}
			pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;
		break;

		case "hold_genquest2":
			dialog.text = StringFromKey("Common_Tavern_188");
			link.l1 = StringFromKey("Common_Tavern_189");
			link.l1.go = "exit";
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			AddQuestRecord("HoldQuest", "7");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;

		case "hold_genquest3":
			Hold_GenQuest_GenerateChar();
			AddQuestRecord("HoldQuest", "8");
			AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Gen"));
			AddQuestUserData("HoldQuest", "sFoundChar", pchar.GenQuest.Hold_GenQuest.foundStr);
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			SetFunctionTimerConditionParam("Hold_GenQuest_FindCharTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
		break;

		case "hold_genquest4":
			AddQuestRecord("HoldQuest", "13");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("ёл", "ла"));
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
			DialogExit();
		break;

		case "hold_genquest5":
			SetFunctionTimerConditionParam("Hold_GenQuest_GetMapTimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_GenerateMapChar");
		break;

		case "CaptainComission_1":
			dialog.text = StringFromKey("Common_Tavern_193", LinkRandPhrase(
						StringFromKey("Common_Tavern_190"),
						StringFromKey("Common_Tavern_191"),
						StringFromKey("Common_Tavern_192")));
			link.l1 = StringFromKey("Common_Tavern_194");
			link.l1.go = "CaptainComission_2";
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
		break;

		case "CaptainComission_2":
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_ExitFromTavern.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_ExitFromTavern.function = "CaptainComission_GenerateChar";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CaptainComission_3":
			dialog.text = StringFromKey("Common_Tavern_195");
			link.l1 = StringFromKey("Common_Tavern_196");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.CaptainComission.Speak_Tavern");
		break;

		case "CaptainComission_Tavern1":
			pchar.GenQuest.CaptainComission.Speak_Tavern = true;
			dialog.text = StringFromKey("Common_Tavern_197");
			link.l1 = StringFromKey("Common_Tavern_198");
			link.l1.go = "CaptainComission_Tavern2";
		break;

		case "CaptainComission_Tavern2":
			dialog.text = StringFromKey("Common_Tavern_199");
			link.l1 = StringFromKey("Common_Tavern_200");
			link.l1.go = "CaptainComission_Tavern3";
		break;

		case "CaptainComission_Tavern3":
			dialog.text = StringFromKey("Common_Tavern_201", pchar.GenQuest.CaptainComission.Name);
			link.l1 = StringFromKey("Common_Tavern_202");
			link.l1.go = "CaptainComission_Tavern4";
		break;

		case "CaptainComission_Tavern4":
			dialog.text = StringFromKey("Common_Tavern_203", pchar.GenQuest.CaptainComission.Name);
			link.l1 = StringFromKey("Common_Tavern_204");
			link.l1.go = "CaptainComission_Tavern5";
		break;

		case "CaptainComission_Tavern5":
			pchar.GenQuest.CaptainComission.CanoneerName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = StringFromKey("Common_Tavern_205", GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			link.l1 = StringFromKey("Common_Tavern_206");
			link.l1.go = "CaptainComission_Tavern6";
		break;

		case "CaptainComission_Tavern6":
			AddQuestRecord("CaptainComission2", "39");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCharName", GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_INS));
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			SetFunctionExitFromLocationCondition("CaptainComission_GenerateCanoneer", pchar.location, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "CaptainComission_Tavern7":
			DeleteAttribute(pchar, "GenQuest.CaptainComission.Speak_Tavern");
			dialog.text = StringFromKey("Common_Tavern_207");
			link.l1 = StringFromKey("Common_Tavern_208");
			link.l1.go = "CaptainComission_Tavern8";
		break;

		case "CaptainComission_Tavern8":
			dialog.text = StringFromKey("Common_Tavern_209", GetAddress_Form(pchar), pchar.GenQuest.CaptainComission.Name);
			link.l1 = StringFromKey("Common_Tavern_210");
			link.l1.go = "CaptainComission_Tavern9";
		break;

		case "CaptainComission_Tavern9":
			dialog.text = StringFromKey("Common_Tavern_211", pchar.GenQuest.CaptainComission.CapName, GetAddress_Form(pchar));
			link.l1 = StringFromKey("Common_Tavern_212");
			link.l1.go = "CaptainComission_Tavern10";
		break;

		case "CaptainComission_Tavern10":
			if (!CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour"))
			{
				pchar.GenQuest.CaptainComission.GetRumour = true;
				SaveCurrentQuestDateParam("GenQuest.CaptainComission.GetRumour");
				SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 2, MakeInt(24 - GetHour()), false);
				AddQuestRecord("CaptainComission2", "19");
				AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
				AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			}
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = StringFromKey("Common_Tavern_213");
			link.l1 = StringFromKey("Common_Tavern_214");
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
			dialog.text = StringFromKey("Common_Tavern_215");
			link.l1 = StringFromKey("Common_Tavern_216", pchar);
			link.l1.go = "exit";
			pchar.quest.EncGirl_SpeakTavernKeeper.over = "yes";
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;

		case "EncGirl_3":
			dialog.text = StringFromKey("Common_Tavern_217");
			link.l1 = StringFromKey("Common_Tavern_218");
			link.l1.go = "exit";
			pchar.GenQuest.EncGirl = "FindingLover";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1 = "ExitFromLocation";
			pchar.quest.EncGirl_ExitTavern.win_condition.l1.location = pchar.location;
			pchar.quest.EncGirl_ExitTavern.function = "EncGirl_GenerateLover";
		break;

		case "EncGirl_4":
			if (sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = StringFromKey("Common_Tavern_219", pchar);
				link.l1 = StringFromKey("Common_Tavern_220", pchar);
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = StringFromKey("Common_Tavern_221", pchar);
				link.l1 = StringFromKey("Common_Tavern_222");
				link.l1.go = "EncGirl_6";
			}
		break;

		case "EncGirl_5":
			dialog.text = StringFromKey("Common_Tavern_223");
			link.l1 = StringFromKey("Common_Tavern_224");
			link.l1.go = "EncGirl_5_1";
		break;

		case "EncGirl_6":
			dialog.text = StringFromKey("Common_Tavern_225");
			link.l1 = StringFromKey("Common_Tavern_226");
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
			dialog.text = StringFromKey("Common_Tavern_227");
			link.l1 = StringFromKey("Common_Tavern_228");
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

		case "ShipLetters_4":
			pchar.questTemp.different.GiveShipLetters.speakTavern = true;
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = StringFromKey("Common_Tavern_229");
				link.l1 = StringFromKey("Common_Tavern_230");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_Tavern_231");
				link.l1 = StringFromKey("Common_Tavern_232");
				link.l1.go = "exit";
				link.l2 = StringFromKey("Common_Tavern_233", pchar);
				link.l2.go = "ShipLetters_end";
			}
		break;

		case "ShipLetters_end":
			TakeItemFromCharacter(pchar, "CaptainBook");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "3");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//эскорт-пассажиры
		case "work":
			if (CheckShipMooredInColony(rColony))
			{
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = StringFromKey("Common_Tavern_236", RandPhraseSimple(
								StringFromKey("Common_Tavern_234", pchar, NationNameGenitive(sti(pchar.nation))),
								StringFromKey("Common_Tavern_235", NationNameInstrumental(sti(pchar.nation)))));
					link.l1 = StringFromKey("Common_Tavern_239", RandPhraseSimple(
								StringFromKey("Common_Tavern_237"),
								StringFromKey("Common_Tavern_238")));
					link.l1.go = "exit";
					break;
				}
				//				if (isBadReputation(pchar, 40))
				if (PlayerRPGCheck_BadReputation(40, false))
				{
					dialog.text = StringFromKey("Common_Tavern_242", RandPhraseSimple(
								StringFromKey("Common_Tavern_240"),
								StringFromKey("Common_Tavern_241")));
					link.l1 = StringFromKey("Common_Tavern_246", LinkRandPhrase(
								StringFromKey("Common_Tavern_243"),
								StringFromKey("Common_Tavern_244"),
								StringFromKey("Common_Tavern_245")));
					link.l1.go = "exit";
					break;
				}
				dialog.text = StringFromKey("Common_Tavern_247");
				link.l1 = StringFromKey("Common_Tavern_248", pchar);
				link.l1.go = "work_1";
				link.l2 = StringFromKey("Common_Tavern_249");
				link.l2.go = "work_2";
				link.l3 = StringFromKey("Common_Tavern_250");
				link.l3.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_Tavern_251");
				link.l1 = StringFromKey("Common_Tavern_252");
				link.l1.go = "exit";
			}
		break;

		case "work_1": //конвой
			if (!CheckAttribute(&TEV, "ArtOfDeals.Tavern.Convoy"))
				TEV.ArtOfDeals.Tavern.Convoy = "0";
			if (CheckQuestAttribute("generate_convoy_quest_progress", "begin"))
			{
				dialog.text = StringFromKey("Common_Tavern_253", pchar);
				link.l1 = StringFromKey("Common_Tavern_256", RandPhraseSimple(
							StringFromKey("Common_Tavern_254"),
							StringFromKey("Common_Tavern_255", pchar)));
				link.l1.go = "exit";
				break;
			}

			if (and(CheckOfficersPerk(pchar, "ArtOfDeals"), sti(TEV.ArtOfDeals.Tavern.Convoy) < 2) || !CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
			{
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7 - sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1)//при низком лидерстве и на 7 класс не даем
				{
					dialog.text = StringFromKey("Common_Tavern_257");
					link.l1 = StringFromKey("Common_Tavern_258");
					link.l1.go = "exit";
					break;
				}

				if (GetCompanionQuantity(PChar) == COMPANION_MAX)
				{
					dialog.text = StringFromKey("Common_Tavern_259");
					link.l1 = StringFromKey("Common_Tavern_260");
					link.l1.go = "exit";
				}
				else
				{
					if (!CheckAttribute(PChar, "QuestTemp.AndreAbelQuest_StartQuest") && PChar.location == "FortFrance_tavern")
					{
						dialog.text = StringFromKey("Common_Tavern_261");
						link.l1 = StringFromKey("Common_Tavern_264", RandPhraseSimple(
									StringFromKey("Common_Tavern_262"),
									StringFromKey("Common_Tavern_263", pchar)));
						link.l1.go = "exit";
						PChar.QuestTemp.AndreAbelQuest_StartQuest = true;

						if (!CheckAttribute(PChar, "QuestTemp.AndreAbelQuest")) // если Абель не сгенерился - пробуем заново
						{
							CreateAbel();
							pchar.quest.Andre_Abel_Quest_Start.over = "yes";
							pchar.quest.Andre_Abel_Quest_Start_1.over = "yes";
						}
					}
					else
					{
						if (idRand(npchar.id + "generate_convoy_tavern", 5) > 1)
						{
							dialog.text = StringFromKey("Common_Tavern_265");
							link.l1 = StringFromKey("Common_Tavern_268", RandPhraseSimple(
										StringFromKey("Common_Tavern_266"),
										StringFromKey("Common_Tavern_267")));
							link.l1.go = "ConvoyAreYouSure";
						}
						else
						{
							dialog.text = StringFromKey("Common_Tavern_269");
							link.l1 = StringFromKey("Common_Tavern_272", RandPhraseSimple(
										StringFromKey("Common_Tavern_270"),
										StringFromKey("Common_Tavern_271")));
							link.l1.go = "exit";
						}
					}
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Tavern_273");
				link.l1 = StringFromKey("Common_Tavern_274");
				link.l1.go = "exit";
			}
		break;

		case "work_2": // пассажир
			if (!CheckAttribute(&TEV, "ArtOfDeals.Tavern.Passenger"))
				TEV.ArtOfDeals.Tavern.Passenger = "0";

			if (and(CheckOfficersPerk(pchar, "ArtOfDeals"), sti(TEV.ArtOfDeals.Tavern.Passenger) < 2) || !CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") >= 2 || bBettaTestMode)
			{
				if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7 - sti(RealShips[sti(Pchar.Ship.Type)].Class)) < 1) // при низком лидерстве и на 7 класс не даем
				{
					dialog.text = StringFromKey("Common_Tavern_275");
					link.l1 = StringFromKey("Common_Tavern_276");
					link.l1.go = "exit";
					break;
				}

				if (idRand(npchar.id + "generate_passenger_tavern", 6) > 1)
				{
					dialog.Text = StringFromKey("Common_Tavern_277");
					link.l1 = StringFromKey("Common_Tavern_280", RandPhraseSimple(
								StringFromKey("Common_Tavern_278"),
								StringFromKey("Common_Tavern_279")));
					Link.l1.go = "PassangerAreYouSure";
				}
				else
				{
					dialog.text = StringFromKey("Common_Tavern_281");
					link.l1 = StringFromKey("Common_Tavern_284", RandPhraseSimple(
								StringFromKey("Common_Tavern_282"),
								StringFromKey("Common_Tavern_283")));
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Tavern_285");
				link.l1 = StringFromKey("Common_Tavern_286");
				link.l1.go = "exit";
			}
		break;

		case "ConvoyAreYouSure":
			CommonGenerator("QuestTrader");
			dialog.text = StringFromKey("Common_Tavern_290", LinkRandPhrase(
						StringFromKey("Common_Tavern_287", pchar),
						StringFromKey("Common_Tavern_288", pchar),
						StringFromKey("Common_Tavern_289", pchar)));
			Link.l1 = StringFromKey("Common_Tavern_291");
			Link.l1.go = "exit";
			pchar.quest.destination = FindDestinationCity(npchar, sti(TEV.ArtOfDeals.Tavern.Convoy) + 1);
			pchar.ConvoyQuest.City = npchar.city;
			AddDialogExitQuest("prepare_for_convoy_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;

		case "PassangerAreYouSure":
			CommonGenerator("QuestPassanger");
			dialog.text = StringFromKey("Common_Tavern_295", LinkRandPhrase(
						StringFromKey("Common_Tavern_292", pchar),
						StringFromKey("Common_Tavern_293", pchar),
						StringFromKey("Common_Tavern_294", pchar)));
			Link.l1 = StringFromKey("Common_Tavern_296");
			Link.l1.go = "exit";
			TEV.GenQuest_DestinationCity = FindDestinationCity(npchar, sti(TEV.ArtOfDeals.Tavern.Passenger) + 1);
			pchar.GenQuest.GetPassenger_City = npchar.city;
			AddDialogExitQuest("prepare_for_passenger_quest");
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "room":
			if (chrDisableReloadToLocation || CheckAttribute(pchar, "questTemp.different.Church_NightGuard")) //кто-то должен подойти к ГГ
			{
				dialog.text = StringFromKey("Common_Tavern_297", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_Tavern_298");
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.State.Open") && npchar.id == "Tortuga_tavernkeeper")//исп.линейка, квест №6, блокировка спать в комнате
			{
				dialog.text = StringFromKey("Common_Tavern_299");
				link.l1 = StringFromKey("Common_Tavern_300");
				link.l1.go = "exit";
				break;
			}
			//-->> квест официантки	
			if (pchar.questTemp.different == "FackWaitress_toRoom")
			{
				dialog.text = StringFromKey("Common_Tavern_301");
				if (sti(pchar.money) >= 100)
				{
					link.l1 = StringFromKey("Common_Tavern_302");
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -100);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
					pchar.questTemp.different = "FackWaitress_toRoomUp";
				}
				else
				{
					link.l1 = StringFromKey("Common_Tavern_303");
					link.l1.go = "exit";
				}
				break;
			}
			if (pchar.questTemp.different == "FackWaitress_toRoomUp")//квест официантки
			{
				dialog.text = StringFromKey("Common_Tavern_304");
				link.l1 = StringFromKey("Common_Tavern_305");
				link.l1.go = "exit";
				break;
			}
			//<<-- квест официантки

			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL1_s50") // или какое у тебя там значение
			{
				dialog.text = StringFromKey("Common_Tavern_306");
				if (sti(pchar.money) >= 10)
				{
					link.l1 = StringFromKey("Common_Tavern_307");
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, -10);
					LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
				}
				else
				{
					link.l1 = StringFromKey("Common_Tavern_308");
					link.l1.go = "exit";
				}
				break;
			}

			// --> квест "Девица в джунглях"
			if (CheckAttribute(pchar, "GenQuest.EncGirl") && npchar.city == pchar.GenQuest.EncGirl.city)
			{
				if (pchar.GenQuest.EncGirl == "EncGirl_ToTavern")
				{
					dialog.text = StringFromKey("Common_Tavern_309");
					if (sti(pchar.money) >= 100)
					{
						link.l1 = StringFromKey("Common_Tavern_310");
						link.l1.go = "exit";
						AddMoneyToCharacter(pchar, -100);
						LocatorReloadEnterDisable(npchar.city + "_tavern", "reload2_back", false);
						pchar.GenQuest.EncGirl = "EncGirl_toRoomUp";
					}
					else
					{
						link.l1 = StringFromKey("Common_Tavern_311");
						link.l1.go = "exit";
					}
					break;
				}
				if (pchar.GenQuest.EncGirl == "EncGirl_toRoomUp") //квест  по спасению тетки в пампасах
				{
					dialog.text = StringFromKey("Common_Tavern_312");
					link.l1 = StringFromKey("Common_Tavern_313");
					link.l1.go = "exit";
					break;
				}
			}
			// <-- квест "Девица в джунглях"

			dialog.text = StringFromKey("Common_Tavern_314");
			if (!isDay())
			{
				link.l1 = StringFromKey("Common_Tavern_315");
				link.l1.go = "room_day";
			}
			else
			{
				link.l1 = StringFromKey("Common_Tavern_316");
				link.l1.go = "room_night";
				link.l2 = StringFromKey("Common_Tavern_317");
				link.l2.go = "room_day_next";
				link.l3 = StringFromKey("Common_Tavern_318");
				link.l3.go = "int_quests";
			}
		break;

		case "room_day":
			dialog.text = StringFromKey("Common_Tavern_319");
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = StringFromKey("Common_Tavern_320");
				link.l1.go = "room_day_wait";
			}
			link.l2 = pcharrepphrase(
						StringFromKey("Common_Tavern_321"),
						StringFromKey("Common_Tavern_322"));
			link.l2.go = "hall_day_wait";
			link.l3 = StringFromKey("Common_Tavern_323");
			link.l3.go = "int_quests";
		break;

		case "room_day_next":
			dialog.text = StringFromKey("Common_Tavern_324");
			if (makeint(pchar.money) >= 10)
			{
				link.l1 = StringFromKey("Common_Tavern_325");
				link.l1.go = "room_day_wait_next";
			}
			link.l2 = pcharrepphrase(
						StringFromKey("Common_Tavern_326"),
						StringFromKey("Common_Tavern_327"));
			link.l2.go = "hall_day_wait";
			link.l3 = StringFromKey("Common_Tavern_328");
			link.l3.go = "int_quests";
		break;

		case "room_night":
			dialog.text = StringFromKey("Common_Tavern_329");
			if (makeint(pchar.money) >= 5)
			{
				link.l1 = StringFromKey("Common_Tavern_330");
				link.l1.go = "room_night_wait";
			}
			link.l2 = pcharrepphrase(
						StringFromKey("Common_Tavern_331"),
						StringFromKey("Common_Tavern_332"));
			link.l2.go = "hall_night_wait";
			link.l3 = StringFromKey("Common_Tavern_333");
			link.l3.go = "int_quests";
		break;

		case "room_night_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_night");
		break;

		case "hall_night_wait":
			if (idRand(npchar.id + "hall_night_wait", 3) == 1)
			{
				Dialog.text = StringFromKey("Common_Tavern_334", pchar);
				link.l1 = StringFromKey("Common_Tavern_335");
				link.l1.go = "exit";
			}
			else
			{
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_night");
			}
		break;

		case "room_day_wait":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -5);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "room_day_wait_next":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(pchar, -10);
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;

		case "hall_day_wait":
			if (idRand(npchar.id + "hall_day_wait", 1) == 1)
			{
				Dialog.text = StringFromKey("Common_Tavern_336", pchar);
				link.l1 = StringFromKey("Common_Tavern_337");
				link.l1.go = "exit";
			}
			else
			{
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				TavernWaitDate("wait_day");
			}
		break;

		case "tavern_keeper":
			NextDiag.TempNode = "First time";

			dialog.text = StringFromKey("Common_Tavern_338");
			link.l1 = StringFromKey("Common_Tavern_339");
			link.l1.go = "exit_sit";
		break;

		case "exit_sit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("exit_sit");
		break;
		//==> eddy. квест мэра, вопросы не замечал ли шпиона
		case "SeekSpy_Seen":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Common_Tavern_340"),
						StringFromKey("Common_Tavern_341"),
						StringFromKey("Common_Tavern_342"),
						StringFromKey("Common_Tavern_343"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Common_Tavern_344"),
						StringFromKey("Common_Tavern_345"),
						StringFromKey("Common_Tavern_346"),
						StringFromKey("Common_Tavern_347"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "SeekSpy_NotSeen":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Common_Tavern_348"),
						StringFromKey("Common_Tavern_349"),
						StringFromKey("Common_Tavern_350"),
						StringFromKey("Common_Tavern_351"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Common_Tavern_352"),
						StringFromKey("Common_Tavern_353"),
						StringFromKey("Common_Tavern_354"),
						StringFromKey("Common_Tavern_355"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;

		//==> homo линейка Блада
		case "TStep_0":
			dialog.text = StringFromKey("Common_Tavern_356");
			link.l1 = StringFromKey("Common_Tavern_357");
			link.l1.go = "Exit";
			int n= FindLocation("Bridgetown_tavern");
			locations[n].reload.l2.disable = false;
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
		break;

		case "TStep_1":
			dialog.text = StringFromKey("Common_Tavern_358");
			link.l1 = StringFromKey("Common_Tavern_359");
			link.l1.go = "TStep_2";
		break;

		case "TStep_2":
			dialog.text = StringFromKey("Common_Tavern_360");
			link.l1 = StringFromKey("Common_Tavern_361");
			link.l1.go = "TStep_3";
			if (makeint(pchar.money) >= 2500)
			{
				link.l1 = StringFromKey("Common_Tavern_362");
				link.l1.go = "TStep_4";
			}
		break;

		case "TStep_3":
			dialog.text = StringFromKey("Common_Tavern_363");
			link.l1 = StringFromKey("Common_Tavern_364");
			link.l1.go = "exit";
		break;

		case "TStep_4":
			dialog.text = StringFromKey("Common_Tavern_365");
			link.l1 = StringFromKey("Common_Tavern_366");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000);
			Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape1";
			AddQuestRecord("WeaponsForEscape", "2");
			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerToLocEx("Bridgetown_town", "reload", "HouseSp2", "BloodLine_WeaponsForEscape");
			QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_WeaponsForEscape");
		break;

		case "TStep_5":
			pchar.questTemp.CapBloodLine.QuestRaff = false;
			dialog.text = StringFromKey("Common_Tavern_367");
			if (makeint(pchar.money) >= 500)
			{
				link.l1 = StringFromKey("Common_Tavern_368");
				link.l1.go = "TStep_6";
			}
			link.l2 = StringFromKey("Common_Tavern_369");
			link.l2.go = "TStep_7";
		break;

		case "TStep_6":
			AddMoneyToCharacter(pchar, -500);
			dialog.text = StringFromKey("Common_Tavern_370");
			link.l1 = StringFromKey("Common_Tavern_371");
			link.l1.go = "TStep_8";
		break;

		case "TStep_7":
			dialog.text = StringFromKey("Common_Tavern_372");
			link.l1 = StringFromKey("Common_Tavern_373");
			link.l1.go = "TStep_10";
		break;

		case "TStep_8":
			dialog.text = StringFromKey("Common_Tavern_374");
			link.l1 = StringFromKey("Common_Tavern_375");
			link.l1.go = "TStep_9";
		break;

		case "TStep_9":
			AddQuestRecord("UsurerQuest", "2");
			sld = GetCharacter(NPC_GenerateCharacter("QStranger", "citiz_11", "man", "man", 10, ENGLAND, 1, false));
			sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			sld.greeting = "Gr_bankeer";
			sld.name = FindPersonalName("QStranger_name");      //fix имени
			sld.lastname = FindPersonalName("QStranger_lastname");
			sTemp = GetNationNameByType(ENGLAND) + "_citizens";
			LAi_group_MoveCharacter(sld, sTemp);
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Bridgetown_Shipyard", "goto", "goto1");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_UsurerQuest");
			AddLandQuestmark_Main(sld, "CapBloodLine");
			QuestPointerToLocEx("Bridgetown_town", "reload", "reload5_back", "BloodLine_UsurerQuest");
		break;

		case "TStep_10":
			sld = GetCharacter(NPC_GenerateCharacter("QStranger", "citiz_11", "man", "man", 10, ENGLAND, 1, false));
			sld.dialog.filename = "Quest\CapBloodLine\questNPC.c";
			sld.greeting = "Gr_bankeer";
			sld.name = FindPersonalName("QStranger_name");      //fix имени
			sld.lastname = FindPersonalName("QStranger_lastname");
			sTemp = GetNationNameByType(ENGLAND) + "_citizens";
			LAi_group_MoveCharacter(sld, sTemp);
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Bridgetown_church", "goto", "goto1"); //раньше был дом, но его можно было там прирезать кинжалом и засофтлочить квест konstrush CommonRoom_MH7
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

			RemoveLandQuestmark_Main(npchar, "CapBloodLine");
			QuestPointerDelLocEx("Bridgetown_town", "reload", "reload4_back", "BloodLine_UsurerQuest");
			AddLandQuestmark_Main(sld, "CapBloodLine");
//			QuestPointerToLocEx("Bridgetown_town", "reload", "reload7_back", "BloodLine_UsurerQuest"); // Пущай сам поищет =)
		break;
		//зачарованный город
		case "MCTavern":
			dialog.text = StringFromKey("Common_Tavern_376", pchar);
			link.l1 = StringFromKey("Common_Tavern_377");
			link.l1.go = "exit";
			LAi_group_Delete("EnemyFight");
			pchar.questTemp.MC = "toCaracasWervolf";
			DeleteAttribute(&locations[reload_location_index], "reload.l2.disable");
			sld = GetCharacter(NPC_GenerateCharacter("CaracasWervolf", "trader_14", "man", "man", 10, PIRATE, -1, true));
			sld.dialog.filename = "Quest\MagicCity.c";
			//sld.greeting = "cit_common";
			sld.dialog.currentnode = "CaracasWervolf";
			sld.location = "Caracas_tavern_upstairs";
			sld.location.group = "goto";
			sld.location.locator = "goto1";
			sld.BreakTmplAndFight = true;
			sld.reactionOnFightModeOn = true;
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(sld, pchar);
			LAi_group_MoveCharacter(sld, "EnemyFight");

			AddLandQuestMark_Main(sld, "MagicCity");
			RemoveLandQuestMark_Main(npchar, "MagicCity");
		break;

		case "MCCaracasAfter":
			dialog.text = StringFromKey("Common_Tavern_378");
			link.l1 = StringFromKey("Common_Tavern_379");
			link.l1.go = "MCCaracasAfter_1";
		break;
		case "MCCaracasAfter_1":
			dialog.text = StringFromKey("Common_Tavern_380", pchar);
			link.l1 = StringFromKey("Common_Tavern_381");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("MC_endCaracas");
			RemoveLandQuestMark_Main(npchar, "MagicCity");
		break;

		//*************************** Квест "Сопровождение флейта "Орион"" **********************
		case "Andre_Abel_Quest_TavernOwner_Dialog_1":
			dialog.text = StringFromKey("Common_Tavern_382", GetFullName(pchar));
			link.l1 = StringFromKey("Common_Tavern_383", pchar);
			link.l1.go = "Andre_Abel_Quest_TavernOwner_Dialog_2";
		break;

		case "Andre_Abel_Quest_TavernOwner_Dialog_2":
			DialogExit();
			AddQuestRecord("Andre_Abel_Quest", "13");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("", "а"));
			CloseQuestheader("Andre_Abel_Quest");
			DeleteAttribute(pchar, "QuestTemp.AndreAbelQuest");
			DeleteAttribute(PChar, "QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek");

			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
		break;

		//******************* ноды квеста священника. поиск грабителей (квест № 2)**********************
		case "Tavern_GenQuest_Church_2_1":
			dialog.text = StringFromKey("Common_Tavern_384");
			link.l1 = StringFromKey("Common_Tavern_385");
			link.l1.go = "exit";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		break;

		//******************* ноды квеста священника. вернуть рукописи (квест № 1)**********************
		case "Tavern_ChurchGenQuest1_Node_1":
			dialog.text = StringFromKey("Common_Tavern_386", pchar);
			link.l1 = StringFromKey("Common_Tavern_387", pchar);
			link.l1.go = "Tavern_ChurchGenQuest1_Node_2";
		break;

		case "Tavern_ChurchGenQuest1_Node_2":
			dialog.text = StringFromKey("Common_Tavern_388", pchar);
			link.l1 = StringFromKey("Common_Tavern_389");
			link.l1.go = "Tavern_ChurchGenQuest1_Node_3";
		break;

		case "Tavern_ChurchGenQuest1_Node_3":
			iTemp = (rand(3) + 1) * 100;
			PChar.GenQuest.ChurchQuest_1.MoneyToBarmen = iTemp;
			if (rand(1) == 0) // "Если он простой и сразу отдаёт"
			{
				dialog.text = StringFromKey("Common_Tavern_390", pchar, FindMoneyString(iTemp));
				if (sti(PChar.money) >= iTemp)
				{
					link.l1 = StringFromKey("Common_Tavern_391");
					link.l1.go = "Tavern_ChurchGenQuest1_Node_4_1";
				}
				else
				{
					link.l1 = StringFromKey("Common_Tavern_392");
					link.l1.go = "exit";
					PChar.GenQuest.ChurchQuest_1.NoMoneyToBarmen = true;
				}
			}
			else // "Если он не простой"
			{
				dialog.text = StringFromKey("Common_Tavern_393", pchar, FindMoneyString(iTemp));
				link.l1 = StringFromKey("Common_Tavern_394");
				link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2";
			}
		break;

		case "Tavern_ChurchGenQuest1_Node_4_1":
			DialogExit();
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			AddItems(PChar, "ChurchManuscript", 1);    // Даем рукописи
			items[FindItem("ChurchManuscript")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "8");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", GetFullName(CharacterFromID("ChurchGenQuest1_Cap")));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2":
			dialog.text = StringFromKey("Common_Tavern_395", pchar);
			link.l1 = StringFromKey("Common_Tavern_396", pchar);
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_1";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_1":
			dialog.text = StringFromKey("Common_Tavern_397", pchar);
			link.l1 = StringFromKey("Common_Tavern_398");
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_2";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_2":
			dialog.text = StringFromKey("Common_Tavern_399", pchar, PChar.GenQuest.ChurchQuest_1.CapFullName);
			link.l1 = StringFromKey("Common_Tavern_400", pchar);
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_3";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_3":
			dialog.text = StringFromKey("Common_Tavern_401", pchar);
			link.l1 = StringFromKey("Common_Tavern_402");
			link.l1.go = "Tavern_ChurchGenQuest1_Node_4_2_4";
		break;

		case "Tavern_ChurchGenQuest1_Node_4_2_4":
			DialogExit();
			AddItems(PChar, "ChurchManuscript", 1);    // Даем рукописи
			items[FindItem("ChurchManuscript")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_1.MoneyToBarmen));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithBarmen");
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "9");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc"));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 2, false);
		break;

		//Jason --> захват пассажиров
		case "Marginpassenger":
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger.lose"))
			{
				dialog.text = StringFromKey("Common_Tavern_409", pchar.GenQuest.Marginpassenger.q2Name, LinkRandPhrase(
							StringFromKey("Common_Tavern_403"),
							StringFromKey("Common_Tavern_404"),
							StringFromKey("Common_Tavern_405")), LinkRandPhrase(
							StringFromKey("Common_Tavern_406"),
							StringFromKey("Common_Tavern_407"),
							StringFromKey("Common_Tavern_408")));
				link.l1 = StringFromKey("Common_Tavern_410", npchar.name);
				link.l1.go = "Marginpassenger_1";
			}
			else
			{
				dialog.text = StringFromKey("Common_Tavern_411", pchar.GenQuest.Marginpassenger.q2Name);
				link.l1 = StringFromKey("Common_Tavern_412");
				link.l1.go = "Marginpassenger_2";
			}
		break;

		case "Marginpassenger_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "7");
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City + "Acc"));
			AddQuestUserData("Marginpassenger", "sBaron", "в Ле Франсуа, к Бартоломью Роджерсу"); //TODO: ветвление, если будет доступно смещение Роджерса
			pchar.GenQuest.Marginpassenger = "cabin";
		break;

		case "Marginpassenger_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "8");
			AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			pchar.GenQuest.Marginpassenger = "street";
		break;
		//<-- захват пассажиров

		case "Pirates_1":
			dialog.text = StringFromKey("Common_Tavern_413", pchar);
			link.l1 = StringFromKey("Common_Tavern_414", pchar);
			link.l1.go = "Pirates_2";
		break;
		case "Pirates_2":
			dialog.text = StringFromKey("Common_Tavern_415", pchar);
			link.l1 = StringFromKey("Common_Tavern_416");
			link.l1.go = "meeting";
		break;

		case "Charles_1":
			dialog.text = StringFromKey("Common_Tavern_417");
			link.l1 = StringFromKey("Common_Tavern_418");
			link.l1.go = "meeting";
		break;

		case "Portobello_1":
			dialog.text = StringFromKey("Common_Tavern_419", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Common_Tavern_420");
			link.l1.go = "Portobello_2";
		break;

		case "Portobello_2":
			dialog.text = StringFromKey("Common_Tavern_421", pchar);
			link.l1 = StringFromKey("Common_Tavern_422", npchar.name);
			link.l1.go = "meeting";
		break;

		case "FortFrance_1":
			dialog.text = StringFromKey("Common_Tavern_423");
			link.l1 = StringFromKey("Common_Tavern_424", npchar.name);
			link.l1.go = "FortFrance_2";
		break;

		case "FortFrance_2":
			dialog.text = StringFromKey("Common_Tavern_425");
			link.l1 = StringFromKey("Common_Tavern_426", pchar);
			link.l1.go = "FortFrance_3";
		break;

		case "FortFrance_3":
			dialog.text = StringFromKey("Common_Tavern_427", pchar);
			link.l1 = StringFromKey("Common_Tavern_428", npchar.name);
			link.l1.go = "meeting";
		break;

		//ОЗГ
		case "Seek_Carlos":
			if (pchar.questTemp.Headhunter.Chance == 1)
			{
				dialog.text = StringFromKey("Common_Tavern_429");
			}
			else
			{
				dialog.text = StringFromKey("Common_Tavern_430");
			}
			link.l1 = StringFromKey("Common_Tavern_431");
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "hunt_carlos_fight";
		break;
		//ОЗГ
	}
}

void CommonGenerator(string sCharID)
{
	dialogDisable = true;
	ref chr;

	if (GetCharacterIndex(sCharID) >= 0)
	{
		chr = characterFromID(sCharID);
		ChangeCharacterAddressGroup(chr, "none", "", "");
	}
}

// boal 25/04/04 общий диалог церковь
#include "DIALOGS\Rumours\Simple_rumors.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Church\" + NPChar.City + "_Church.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	string iDay, iMonth, lastspeak_date;
	string sTemp, sTitle;
	bool bChurch1Offered = false;

	iDay = environment.date.day;
	iMonth = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
	{
		npchar.quest.HealthMonth = "";
	}

	if (!CheckAttribute(npchar, "quest.BadMeeting"))
	{

		npchar.quest.BadMeeting = "";
	}
	if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
	{
		npchar.quest.GhostShipMonth = "";
	}

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
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
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_church_4", LinkRandPhrase(
								StringFromKey("Common_church_1", pchar),
								StringFromKey("Common_church_2", pchar),
								StringFromKey("Common_church_3", pchar))),
						StringFromKey("Common_church_8", LinkRandPhrase(
								StringFromKey("Common_church_5", pchar),
								StringFromKey("Common_church_6", pchar),
								StringFromKey("Common_church_7"))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_church_11", RandPhraseSimple(
								StringFromKey("Common_church_9"),
								StringFromKey("Common_church_10"))),
						StringFromKey("Common_church_15", LinkRandPhrase(
								StringFromKey("Common_church_12"),
								StringFromKey("Common_church_13"),
								StringFromKey("Common_church_14"))));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.BadMeeting != lastspeak_date)
			{
				if (Pchar.questTemp.CapBloodLine == false)
				{
					bool bIsActiveMC = pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern";
					bIsActiveMC = npchar.city == "Caracas" && bIsActiveMC;
					if (!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && !bIsActiveMC && idRand(npchar.id + "ChurchQuest_2", 5) == 1)
					{
						dialog.text = StringFromKey("Common_church_16");
						link.l1 = StringFromKey("Common_church_19", RandPhraseSimple(
									StringFromKey("Common_church_17", pchar),
									StringFromKey("Common_church_18")));
						link.l1.go = "GenQuest_Church_2_Start_1";
						NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
						break;
					}

					if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
					{
						Dialog.Text = StringFromKey("Common_church_20", pchar);
						link.l1 = StringFromKey("Common_church_21", pchar, NPChar.name);
						link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
						break;
					}

					if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						Dialog.Text = StringFromKey("Common_church_22", pchar);
						link.l1 = StringFromKey("Common_church_25", pchar, RandPhraseSimple(
									StringFromKey("Common_church_23"),
									StringFromKey("Common_church_24")));
						link.l1.go = "GenQuest_Church_1_Complete_1";
						break;
					}
				}
				Dialog.Text = StringFromKey("Common_church_26", pchar);
				link.l1 = StringFromKey("Common_church_27");
				link.l1.go = "node_3";
				Link.l2 = StringFromKey("Common_church_28");
				Link.l2.go = "node_2";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date;    // Если не дал сегодня, то токо на след день.
			}
			else
			{
				Dialog.Text = StringFromKey("Common_church_29", pchar);
				Link.l1 = StringFromKey("Common_church_30");
				Link.l1.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "node_2":
			dialog.text = StringFromKey("Common_church_31", pchar);
			link.l1 = StringFromKey("Common_church_32", pchar);
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -0.25);
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "node_3":
			dialog.text = StringFromKey("Common_church_33");

			//зачарованный город
			if (pchar.questTemp.MC == "toCaracasPadre" && npchar.city == "Caracas")
			{
				link.l1 = StringFromKey("Common_church_34", pchar);
				link.l1.go = "MC_CaracasChirch";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasTavern" && npchar.city == "Caracas")
			{
				dialog.text = StringFromKey("Common_church_35");
				link.l1 = StringFromKey("Common_church_36", pchar);
				link.l1.go = "exit";
				break;
			}

			//homo Линейка Блада
			if (Pchar.questTemp.CapBloodLine != true)
			{
				link.l1 = StringFromKey("Common_church_39", RandPhraseSimple(
							StringFromKey("Common_church_37"),
							StringFromKey("Common_church_38")));
				link.l1.go = "donation";
				link.l2 = StringFromKey("Common_church_44", RandPhraseSimple(
							StringFromKey("Common_church_40"),
							StringFromKey("Common_church_43", RandPhraseSimple(
									StringFromKey("Common_church_41"),
									StringFromKey("Common_church_42")))));
				link.l2.go = "ispoved";
				link.l3 = StringFromKey("Common_church_51", RandPhraseSimple(
							StringFromKey("Common_church_47", RandPhraseSimple(
									StringFromKey("Common_church_45"),
									StringFromKey("Common_church_46"))),
							StringFromKey("Common_church_50", pchar, RandPhraseSimple(
									StringFromKey("Common_church_48"),
									StringFromKey("Common_church_49")))));
				link.l3.go = "work";//"quest lines";
			}

			// Warship, 30.05.11. "Дело чести" ветка "Божий суд"
			if (CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
			NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
			{
				link.l5 = StringFromKey("Common_church_52");
				link.l5.go = "AffairOfHonor_GodJudgement_1";
			}

			link.l6 = StringFromKey("Common_church_53");
			link.l6.go = "exit";
		break;

		case "AffairOfHonor_GodJudgement_1":
			dialog.text = StringFromKey("Common_church_54", pchar);
			Link.l1 = StringFromKey("Common_church_55");
			Link.l1.go = "exit";
			AddItemLog(pchar, "jewelry9", "1", StringFromKey("InfoMessages_135", GetItemName("jewelry9")), "Important_item"); //TODO: другую уникальную дребедень или эликсир из медицины
			DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

		// Church GenQuest_2 -->
		case "GenQuest_Church_2_Start_1":
			dialog.text = StringFromKey("Common_church_56");
			link.l1 = StringFromKey("Common_church_60", LinkRandPhrase(
						StringFromKey("Common_church_57"),
						StringFromKey("Common_church_58"),
						StringFromKey("Common_church_59")));
			link.l1.go = "GenQuest_Church_2_Start_2";
			link.l2 = StringFromKey("Common_church_63", RandPhraseSimple(
						StringFromKey("Common_church_61"),
						StringFromKey("Common_church_62")));
			link.l2.go = "exit";
		break;

		case "GenQuest_Church_2_Start_2":
			dialog.text = StringFromKey("Common_church_64", pchar);
			link.l1 = StringFromKey("Common_church_65");
			link.l1.go = "GenQuest_Church_2_Start_3";
			link.l2 = StringFromKey("Common_church_69", LinkRandPhrase(
						StringFromKey("Common_church_66"),
						StringFromKey("Common_church_67"),
						StringFromKey("Common_church_68")));
			link.l2.go = "exit";
		break;

		case "GenQuest_Church_2_Start_3":
			dialog.text = StringFromKey("Common_church_70");
			link.l1 = StringFromKey("Common_church_71");
			link.l1.go = "GenQuest_Church_2_Start_4";
		break;

		case "GenQuest_Church_2_Start_4":
			dialog.text = StringFromKey("Common_church_72");
			link.l1 = StringFromKey("Common_church_73", pchar);
			link.l1.go = "GenQuest_Church_2_Start_5";
		break;

		case "GenQuest_Church_2_Start_5":
			dialog.text = StringFromKey("Common_church_74", pchar);
			link.l1 = StringFromKey("Common_church_77", RandPhraseSimple(
						StringFromKey("Common_church_75", pchar),
						StringFromKey("Common_church_76", pchar)));
			link.l1.go = "exit";
			link.l2 = StringFromKey("Common_church_81", pchar, LinkRandPhrase(
						StringFromKey("Common_church_78"),
						StringFromKey("Common_church_79"),
						StringFromKey("Common_church_80")));
			link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;
		case "GenQuest_Church_2_Start_5_1": //выше - выход из диалога без подтверждения - странно, однако
			dialog.text = StringFromKey("Common_church_82", pchar);
			link.l1 = StringFromKey("Common_church_85", RandPhraseSimple(
						StringFromKey("Common_church_83"),
						StringFromKey("Common_church_84")));
			link.l1.go = "GenQuest_Church_2_Start_6";
		break;

		case "GenQuest_Church_2_Start_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_2.StartQuest = true;
			PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City;    // Город, в котором спрашиваем
			PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
			PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_2.AskPeople = true;
			PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
			PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
			PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank) + 8) * 543 + 3210;
			PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount) / 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			//	AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;

		case "GenQuest_Church_2_Thief_2":
			dialog.text = StringFromKey("Common_church_86");
			link.l1 = StringFromKey("Common_church_87");
			link.l1.go = "GenQuest_Church_2_Thief_3";
		break;

		case "GenQuest_Church_2_Thief_3":
			if (idRand(npchar.id + "GenQuest_Church_2", 1) == 0) // Священник искренне раскаивается...
			{
				dialog.text = StringFromKey("Common_church_88");
				link.l1 = StringFromKey("Common_church_89");
				link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
			}
			else
			{
				dialog.text = StringFromKey("Common_church_90");
				link.l1 = StringFromKey("Common_church_91");
				link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
			}
		break;

		case "GenQuest_Church_2_Thief_4_1_1":
			dialog.text = StringFromKey("Common_church_92", pchar);
			link.l1 = StringFromKey("Common_church_96", pchar, LinkRandPhrase(
						StringFromKey("Common_church_93"),
						StringFromKey("Common_church_94"),
						StringFromKey("Common_church_95")));
			link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;

		case "GenQuest_Church_2_Thief_4_1_2":
			dialog.text = StringFromKey("Common_church_97");
			link.l1 = StringFromKey("Common_church_98");
			link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;

		case "GenQuest_Church_2_Thief_4_1_3":
			if (idRand(npchar.id + "GenQuest_Church_2", 1) == 0) // Священник хочет всучить ГГ бабло
			{
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = StringFromKey("Common_church_99", pchar, FindMoneyString(iMoneyToCharacter));
				// ГГ не берёт деньги. Плюсанем репу
				link.l1 = StringFromKey("Common_church_100", pchar, NPChar.name);
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				// ГГ берёт деньги
				link.l2 = StringFromKey("Common_church_104", LinkRandPhrase(
							StringFromKey("Common_church_101"),
							StringFromKey("Common_church_102"),
							StringFromKey("Common_church_103")));
				link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
			}
			else
			{
				dialog.text = StringFromKey("Common_church_105", pchar);
				link.l1 = StringFromKey("Common_church_109", LinkRandPhrase(
							StringFromKey("Common_church_106"),
							StringFromKey("Common_church_107"),
							StringFromKey("Common_church_108")));
				link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
				link.l2 = StringFromKey("Common_church_110", pchar);
				link.l2.go = "GenQuest_Church_2_Thief_4_1_6";
			}

			// Если будет чаша - здесь её отбирать!
			ChurchGenQuest2_RemoveCup();
		break;

		case "GenQuest_Church_2_Thief_4_1_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			DialogExit();
		break;

		case "GenQuest_Church_2_Thief_4_1_5":
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChangeCharacterReputation(PChar, -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			DialogExit();
		break;

		case "GenQuest_Church_2_Thief_4_1_6":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = StringFromKey("Common_church_111", FindMoneyString(iMoneyToCharacter));
			link.l1 = StringFromKey("Common_church_115", LinkRandPhrase(
						StringFromKey("Common_church_112"),
						StringFromKey("Common_church_113"),
						StringFromKey("Common_church_114")));
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;

		case "GenQuest_Church_2_Thief_4_1_6_1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			DialogExit();
		break;

		case "GenQuest_Church_2_Thief_4_2_1":
			dialog.text = StringFromKey("Common_church_116", pchar);
			link.l1 = StringFromKey("Common_church_117", pchar);
			link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;

		case "GenQuest_Church_2_Thief_4_2_2":
			dialog.text = StringFromKey("Common_church_118");
			link.l1 = StringFromKey("Common_church_119");
			link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;

		case "GenQuest_Church_2_Thief_4_2_3":
			if (rand(1) == 0) // Просто несколько разные варианты диалога
			{
				dialog.text = StringFromKey("Common_church_120", pchar);
				link.l1 = StringFromKey("Common_church_121", pchar);
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
			}
			else
			{
				dialog.text = StringFromKey("Common_church_122");
				link.l1 = StringFromKey("Common_church_123", NPChar.name);
				link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
				link.l2 = StringFromKey("Common_church_124");
				link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
			}
		break;

		case "GenQuest_Church_2_Thief_4_2_4_1":
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = StringFromKey("Common_church_125", pchar, PChar.name, FindMoneyString(iMoneyToCharacter));
			// При этом варианте репу плюсуем
			link.l1 = StringFromKey("Common_church_126");
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
			// При этом - минусуем
			link.l2 = StringFromKey("Common_church_127", pchar);
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_1";

		// Если будет чаша - здесь её отбирать!
		break;

		case "GenQuest_Church_2_Thief_4_2_4_1_1":
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ен", "на"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("", "а"));
			AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("", "ла"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sMoney", FindMoneyString(iMoneyToCharacter));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			DialogExit();
		break;

		case "GenQuest_Church_2_Thief_4_2_4_1_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 3);
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			DialogExit();
		break;

		case "GenQuest_Church_2_Thief_4_2_4_2_1":
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			ChangeCharacterReputation(PChar, 3);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ен", "на"));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("", "а"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			DialogExit();
		break;

		case "GenQuest_Church_2_Thief_4_2_4_2_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_RemoveCup();
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			DialogExit();
		break;

		case "GenQuest_Church_2_Finally_Complete_1":

		// ничего не принесли священнику.
			bool ok = !CheckCharacterItem(pchar, "ChurchCup") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant");
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All") || ok)
			{
				link.l1 = StringFromKey("Common_church_131", LinkRandPhrase(
							StringFromKey("Common_church_128"),
							StringFromKey("Common_church_129"),
							StringFromKey("Common_church_130")));
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
				break;
			}

			// Принесли священнику только чашу.
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
			{
				link.l1 = StringFromKey("Common_church_135", LinkRandPhrase(
							StringFromKey("Common_church_132"),
							StringFromKey("Common_church_133"),
							StringFromKey("Common_church_134")));
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
				break;
			}

			// Принесли священнику и деньги и чашу.
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
			{
				if (sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = StringFromKey("Common_church_136", pchar);
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}
				// Деньги можно заныкать.
				link.l2 = StringFromKey("Common_church_140", pchar, LinkRandPhrase(
							StringFromKey("Common_church_137"),
							StringFromKey("Common_church_138"),
							StringFromKey("Common_church_139")));
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
				break;
			}

			// Священник - вор.
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
			{
				dialog.text = StringFromKey("Common_church_141", pchar);
				link.l1 = StringFromKey("Common_church_142");
				link.l1.go = "GenQuest_Church_2_Thief_2";
				break;
			}

			// Короткий вариант прохождения квеста.
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
			{
				if (sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
				{
					link.l1 = StringFromKey("Common_church_143", pchar);
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
				}

				// Деньги можно заныкать.
				link.l2 = StringFromKey("Common_church_147", pchar, LinkRandPhrase(
							StringFromKey("Common_church_144"),
							StringFromKey("Common_church_145"),
							StringFromKey("Common_church_146")));
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			}
		break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
			ChurchGenQuest2_RemoveCup();
			if (idRand(npchar.id + "GenQuest_ChurchFinally", 1) == 0)    // Священник верит ГГ но не даёт денег...
			{
				if (idRand(npchar.id + "GenQuest_ChurchFinally", 4) == 3) // Более "мягкий" исход событий.
				{
					dialog.text = StringFromKey("Common_church_148", pchar);
					link.l1 = StringFromKey("Common_church_149");
					link.l1.go = "exit";
					sQuestTitle = NPChar.City + "ChurchGenQuest2";
					AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
					AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
					CloseQuestHeader(sQuestTitle);
					ChangeCharacterReputation(PChar, -2);
					DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
					NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
				}
				else
				{
					dialog.text = StringFromKey("Common_church_150", pchar);
					link.l1 = StringFromKey("Common_church_151");
					link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
				}
			}
			else
			{
				// Священник даёт деньги ГГ...
				iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
				dialog.text = StringFromKey("Common_church_152", pchar, FindMoneyString(iMoneyToCharacter));
				link.l1 = StringFromKey("Common_church_153");
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
				link.l2 = StringFromKey("Common_church_157", LinkRandPhrase(
							StringFromKey("Common_church_154"),
							StringFromKey("Common_church_155"),
							StringFromKey("Common_church_156")));
				link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
			}
		break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
			if (idRand(npchar.id + "GenQuest_ChurchFinally", 6) == 3)
			{
				dialog.text = StringFromKey("Common_church_158", pchar);
				link.l1 = StringFromKey("Common_church_159");
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1";
				break;
			}
			dialog.text = StringFromKey("Common_church_160", pchar);
			link.l1 = StringFromKey("Common_church_161");
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
		break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader(sQuestTitle);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			ChangeCharacterReputation(PChar, -3);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader(sQuestTitle);
			ChangeCharacterReputation(PChar, -6);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddCharacterExpToSkill(PChar, "Fortune", -70);
			AddCharacterExpToSkill(PChar, "Sneak", 20);
			DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
			npchar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

		case "GenQuest_Church_2_Finally_Complete_1_4_1":
			ChurchGenQuest2_RemoveCup();
			if (idRand(npchar.id + "GenQuest_ChurchFinally", 1) == 0) // Поверил.
			{
				dialog.text = StringFromKey("Common_church_162", pchar);
				link.l1 = StringFromKey("Common_church_163");
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
			}
			else
			{
				dialog.text = StringFromKey("Common_church_164", pchar);
				link.l1 = StringFromKey("Common_church_165", pchar, NPChar.name);
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
			}
		break;

		case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
			dialog.text = StringFromKey("Common_church_166", pchar);
			link.l1 = StringFromKey("Common_church_170", LinkRandPhrase(
						StringFromKey("Common_church_167"),
						StringFromKey("Common_church_168"),
						StringFromKey("Common_church_169")));
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;

		case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -5);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.quest.BadMeeting = lastspeak_date;
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
			DialogExit();
			iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			AddMoneyToCharacter(PChar, iMoneyToCharacter);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

		case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -1);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

		case "GenQuest_Church_2_Finally_Complete_1_1_1":
			dialog.text = StringFromKey("Common_church_171", pchar);
			link.l1 = StringFromKey("Common_church_172");
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;

		case "GenQuest_Church_2_Finally_Complete_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, -2);
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

		case "GenQuest_Church_2_Finally_Complete_1_2_1":
			ChurchGenQuest2_RemoveCup();
			dialog.text = StringFromKey("Common_church_173");
			link.l1 = StringFromKey("Common_church_174");
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;

		case "GenQuest_Church_2_Finally_Complete_1_2_2":
			dialog.text = StringFromKey("Common_church_175", pchar);
			link.l1 = StringFromKey("Common_church_176");
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;

		case "GenQuest_Church_2_Finally_Complete_1_2_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChangeCharacterReputation(PChar, 5);
			AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
			sQuestTitle = NPChar.City + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

		//================================================================================================================

		case "donation":
			dialog.Text = StringFromKey("Common_church_177", pchar);
			Link.l1 = StringFromKey("Common_church_178");
			Link.l1.go = "No donation";
			if (makeint(PChar.money) >= 100)
			{
				Link.l2 = StringFromKey("Common_church_179");
				Link.l2.go = "donation paid_100";
			}
			if (makeint(PChar.money) >= 1000)
			{
				Link.l3 = StringFromKey("Common_church_180");
				Link.l3.go = "donation paid_1000";
			}
			if (makeint(PChar.money) >= 5000)
			{
				Link.l4 = StringFromKey("Common_church_181");
				Link.l4.go = "donation paid_5000";
			}
			//-->> квест пожертвования хозяйки борделя
			if (pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
			{
				Link.l5 = StringFromKey("Common_church_182");
				Link.l5.go = "HostessChurch";
			}
		//<<-- квест пожертвования хозяйки борделя
		break;

		case "No donation":
			dialog.Text = StringFromKey("Common_church_183");
			Link.l1 = StringFromKey("Common_church_184");
			Link.l1.go = "node_3";
			Link.l2 = StringFromKey("Common_church_185");
			Link.l2.go = "exit";
		break;

		case "donation paid_100":
			AddMoneyToCharacter(pchar, -100);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
			dialog.Text = StringFromKey("Common_church_186", pchar);
			Link.l1 = StringFromKey("Common_church_187");
			Link.l1.go = "node_3";
			Link.l2 = StringFromKey("Common_church_188");
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_1000":
			AddMoneyToCharacter(pchar, -1000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
			dialog.Text = StringFromKey("Common_church_189", pchar);
			Link.l1 = StringFromKey("Common_church_190");
			Link.l1.go = "node_3";
			Link.l2 = StringFromKey("Common_church_191");
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "donation paid_5000":
			AddMoneyToCharacter(pchar, -5000);
			pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
			dialog.Text = StringFromKey("Common_church_192", pchar);
			Link.l1 = StringFromKey("Common_church_193");
			Link.l1.go = "node_3";
			Link.l2 = StringFromKey("Common_church_194");
			Link.l2.go = "exit";
			AddDialogExitQuest("donation");
		break;

		case "ispoved":
			dialog.text = StringFromKey("Common_church_195", pchar);
			link.l1 = StringFromKey("Common_church_196", pchar);
			link.l1.go = "exit";
			link.l2 = StringFromKey("Common_church_197", pchar);
			link.l2.go = "ispoved_1";
		break;

		case "ispoved_1":
			dialog.text = StringFromKey("Common_church_198");
			link.l1 = StringFromKey("Common_church_199", pchar);
			link.l1.go = "ispoved_2";
		break;

		case "ispoved_2":
			dialog.text = StringFromKey("Common_church_200", NationNameGenitive(sti(NPChar.nation)));
			link.l1 = StringFromKey("Common_church_201");
			link.l1.go = "ispoved_3";
			link.l2 = StringFromKey("Common_church_202");
			link.l2.go = "ispoved_4";
		break;

		case "ispoved_3":
			dialog.text = StringFromKey("Common_church_203");
			link.l1 = StringFromKey("Common_church_204");
			link.l1.go = "exit";
		break;

		case "ispoved_4":
			dialog.text = StringFromKey("Common_church_205");
			link.l1 = StringFromKey("Common_church_206");
			link.l1.go = "exit";
			npchar.quest.BadMeeting = lastspeak_date;
		break;

		case "work":
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
			{
				dialog.text = StringFromKey("Common_church_207", pchar);
				link.l1 = StringFromKey("Common_church_210", RandPhraseSimple(
							StringFromKey("Common_church_208"),
							StringFromKey("Common_church_209")), PChar.GenQuest.ChurchQuest_1.PriestName, XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
				link.l1.go = "GenQuest_Church_1_Dialog_1";
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
				break;
			}
			dialog.text = StringFromKey("Common_church_211", pchar);
			link.l1 = StringFromKey("Common_church_212", pchar);
			link.l1.go = "quests"; // ссылка к НПС
			link.l2 = StringFromKey("Common_church_215", RandPhraseSimple(
						StringFromKey("Common_church_213", NationNameGenitive(sti(NPChar.nation))),
						StringFromKey("Common_church_214")));
			link.l2.go = "prihod";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = StringFromKey("Common_church_218", pchar, RandPhraseSimple(
							StringFromKey("Common_church_216"),
							StringFromKey("Common_church_217"))); //(пересылка в кредиты)
				link.l3.go = "LoanForAll";
			}
			// -->
			if (stf(pchar.Health.HP) < 60.0)
			{
				link.l4 = StringFromKey("Common_church_219");
				link.l4.go = "healthAdd_1";
			}
			//==> Вставка Эдди, квест Аззи, возможность сдачи лампы.
			if (CheckCharacterItem(pchar, "Azzy_bottle"))
			{
				link.l6 = StringFromKey("Common_church_220");
				link.l6.go = "GiveLamp";
			}
			//<== Вставка Эдди, квест Аззи возможность сдачи лампы.
			//квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
				link.l7 = StringFromKey("Common_church_223", RandPhraseSimple(
							StringFromKey("Common_church_221"),
							StringFromKey("Common_church_222")), GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
				link.l7.go = "IntelligenceForAll";
			}
			//==> успокоить нечисть в пещерах
			if (CheckAttribute(npchar, "quest.DestroyGhost") && npchar.quest.DestroyGhost == "GoodResult")
			{
				sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
				switch (sld.id.label)
				{
					case "Cave": sTemp = StringFromKey("Common_church_224"); break;
					case "Grot": sTemp = StringFromKey("Common_church_225"); break;
					case "Dungeon": sTemp = StringFromKey("Common_church_226"); break;
				}
				sTemp += " ";
				if (pchar.questTemp.GhostType == "indians")
				{
					sTemp += StringFromKey("Common_church_227");
				}    // EvgAnat - дикие карибы
				else
				{
					sTemp += StringFromKey("Common_church_228");
				}
				link.l5 = StringFromKey("Common_church_229", sTemp);
				link.l5.go = "GhostShip_S1";
			}
			//==> ночной сторож в церкви
			if (CheckAttribute(pchar, "questTemp.different.Church_NightGuard") && pchar.questTemp.different.Church_NightGuard == npchar.location)
			{
				link.l8 = StringFromKey("Common_church_232", RandPhraseSimple(
							StringFromKey("Common_church_230"),
							StringFromKey("Common_church_231")));
				link.l8.go = "NightGuard_result";
			}
			//<== ночной сторож в церкви
			//--> Jason Церковная депеша
			if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
			{
				link.l9 = StringFromKey("Common_church_233", XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.StartCity));
				link.l9.go = "Monkletter";
			}
			//<-- Церковная депеша
			//--> Jason Доставка молитвенников
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
			{
				link.l10 = StringFromKey("Common_church_234", XI_ConvertString("Colony" + pchar.GenQuest.Churchbooks.StartCity));
				link.l10.go = "Churchbooks";
			}
			if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
			{
				link.l10 = StringFromKey("Common_church_235");
				link.l10.go = "Churchbooks_2";
			}
			//<-- Доставка молитвенников
			link.l99 = StringFromKey("Common_church_236", pchar);
			link.l99.go = "exit";
		break;

		case "prihod":
		//упокоение нечисти
			if (idRand(npchar.id + "DestroyGhost", 2) == 1 && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.DestroyGhost") && GetNpcQuestPastDayWOInit(npchar, "Ghost") > 7)
			{
				if (CheckCharacterPerk(pchar, "WildCaribbean"))    // EvgAnat - дикие карибы
				{
					dialog.text = StringFromKey("Common_church_237");
					pchar.questTemp.GhostType = "skeletons";
				}
				else
				{
					dialog.text = StringFromKey("Common_church_238");
					pchar.questTemp.GhostType = "indians";
				}
				link.l1 = StringFromKey("Common_church_241", RandPhraseSimple(
							StringFromKey("Common_church_239"),
							StringFromKey("Common_church_240")));
				link.l1.go = "DestroyGhost_1";
				SaveCurrentNpcQuestDateParam(npchar, "Ghost");
				npchar.quest.add = true;
				break;
			}
			//караулить церковь ночью
			if (!CheckAttribute(npchar, "quest.add") && idRand(npchar.id + "NightChurch", 4) == 1 && pchar.questTemp.different == "free" && !CheckAttribute(npchar, "quest.GuardNightChurch") && !CheckAttribute(pchar, "questTemp.different.Church_NightGuard") && GetNpcQuestPastDayWOInit(npchar, "NightChurch") > 60 && GetHour() < 23)
			{
				dialog.text = StringFromKey("Common_church_242", pchar);
				link.l1 = StringFromKey("Common_church_243");
				link.l1.go = "NightChurch_1";
				SaveCurrentNpcQuestDateParam(npchar, "NightChurch");
				break;
			}
			if (!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && idRand(npchar.id + "ChurchQuest", 5) == 1)
			{
				dialog.text = StringFromKey("Common_church_244", pchar);
				link.l1 = StringFromKey("Common_church_248", pchar, LinkRandPhrase(
							StringFromKey("Common_church_245"),
							StringFromKey("Common_church_246"),
							StringFromKey("Common_church_247")));
				link.l1.go = "GenQuest_Church_1_Start_1";
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
				bChurch1Offered = true; // > чтобы ниже не затереть текст предложения квеста
			}
			else
			{
				NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;    // Если не дал сегодня, то токо на след день.
			}
			if (!bChurch1Offered) dialog.text = StringFromKey("Common_church_249", pchar); // > было безусловно - текст Common_church_244 никогда не показывался
			link.l2 = StringFromKey("Common_church_250");
			link.l2.go = "exit";
			DeleteAttribute(npchar, "quest.add");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date;    // Если не дал сегодня, то токо на след день.
		break;

		// Church GenQuest_1 -->
		case "GenQuest_Church_1_Start_1":
			dialog.text = StringFromKey("Common_church_251");
			link.l1 = StringFromKey("Common_church_255", pchar, LinkRandPhrase(
						StringFromKey("Common_church_252"),
						StringFromKey("Common_church_253"),
						StringFromKey("Common_church_254")));
			link.l1.go = "GenQuest_Church_1_Start_2";
		break;

		case "GenQuest_Church_1_Start_2":
			PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
			Church_GenQuest1_InitStartParam(NPChar);
			dialog.text = StringFromKey("Common_church_256", PChar.GenQuest.ChurchQuest_1.ToName, XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"), XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland + "Pre"));
			link.l1 = StringFromKey("Common_church_260", LinkRandPhrase(
						StringFromKey("Common_church_257"),
						StringFromKey("Common_church_258"),
						StringFromKey("Common_church_259")));
			link.l1.go = "exit";
			link.l2 = StringFromKey("Common_church_264", LinkRandPhrase(
						StringFromKey("Common_church_261"),
						StringFromKey("Common_church_262"),
						StringFromKey("Common_church_263")));
			link.l2.go = "GenQuest_Church_1_Start_3";
		break;

		case "GenQuest_Church_1_Start_3":    // Квест взят
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.StartQuest = true;
			PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
			PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
			PChar.GenQuest.ChurchQuest_1.AskOwner = true;
			SetFunctionTimerCondition("Church_GenQuest1_Timer", 0, 0, 60, false); // > провал по таймауту (60 дней)
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			ReOpenQuestHeader(sQuestTitle);
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
			AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData(sQuestTitle, "sName", NPChar.name);
			AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;

		case "GenQuest_Church_1_Dialog_1":
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene"))    // Сцена 2а
			{
				dialog.text = StringFromKey("Common_church_265", pchar);
				link.l1 = StringFromKey("Common_church_269", LinkRandPhrase(
							StringFromKey("Common_church_266"),
							StringFromKey("Common_church_267"),
							StringFromKey("Common_church_268")), PChar.GenQuest.ChurchQuest_1.PriestName);
				link.l1.go = "GenQuest_Church_1_Dialog_1_1";
			}
			else    // Сцена 2б-а и 2б-б
			{
				dialog.text = StringFromKey("Common_church_270", pchar);
				link.l1 = StringFromKey("Common_church_273", RandPhraseSimple(
							StringFromKey("Common_church_271"),
							StringFromKey("Common_church_272")), PChar.GenQuest.ChurchQuest_1.PriestName);
				link.l1.go = "GenQuest_Church_1_Dialog_1_2";
			}
		break;

		case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
			dialog.text = StringFromKey("Common_church_274", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
			link.l1 = StringFromKey("Common_church_275", pchar, PChar.GenQuest.ChurchQuest_1.PriestName);
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;

		case "GenQuest_Church_1_Dialog_1_1_1":
			dialog.text = StringFromKey("Common_church_276", pchar, PChar.GenQuest.ChurchQuest_1.PriestName);
			link.l1 = StringFromKey("Common_church_280", LinkRandPhrase(
						StringFromKey("Common_church_277"),
						StringFromKey("Common_church_278"),
						StringFromKey("Common_church_279")));
			link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;

		case "GenQuest_Church_1_Dialog_1_1_2":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			// Предмет "рукопись" -->
			AddItems(PChar, "ChurchManuscript", 1);    // Даем рукописи
			items[FindItem("ChurchManuscript")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
		// <-- Предмет "рукопись"
		break;

		case "GenQuest_Church_1_Dialog_1_2":    // Сцена 2б-а и 2б-б
		// Генерим кэпа -->
			sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "officer_" + (rand(27) + 1), "man", "man", 15, NPChar.nation, -1, true)); //watch_quest_moment
			FantomMakeCoolFighter(sld, 35, 40, 35, "blade24", "pistol3", 30);
			FantomMakeCoolSailor(sld, SHIP_BARKENTINE + rand(SHIP_FLEUT - SHIP_BARKENTINE), "", CANNON_TYPE_LBS_BY_SHIP, 75, 70, 65);
			sld.Abordage.Enable = false;
			sld.ShipEnemyDisable = true; // флаг не обижаться на выстрелы
			LAi_SetImmortal(sld, true);
			sld.Dialog.FileName = "Quest\GenQuests_dialog.c";
			sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
			Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetType("ChurchGenQuest1_CapGroup", "trade");
			Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
			Group_SetTaskNone("ChurchGenQuest1_CapGroup");
			Group_LockTask("ChurchGenQuest1_CapGroup");
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
			PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
			PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
			PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
			// <-- Генерим кэпа

			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
			{
				dialog.text = StringFromKey("Common_church_281", pchar, sld.Ship.Name, GetFullName(sld), XI_ConvertString("Colony" + GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown) + "Acc"), XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
				link.l1 = StringFromKey("Common_church_282");
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
			}
			else // Сцена 2б-б
			{
				dialog.text = StringFromKey("Common_church_283", pchar, PChar.GenQuest.ChurchQuest_1.PriestName, PChar.GenQuest.ChurchQuest_1.CapFullName, XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapColony + "Acc"), XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"));
				link.l1 = StringFromKey("Common_church_287", pchar, LinkRandPhrase(
							StringFromKey("Common_church_284"),
							StringFromKey("Common_church_285"),
							StringFromKey("Common_church_286")));
				link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
			}
		break;

		case "GenQuest_Church_1_Dialog_1_2_1":    // 2б-а
			dialog.text = StringFromKey("Common_church_288", pchar);
			link.l1 = StringFromKey("Common_church_289");
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;

		case "GenQuest_Church_1_Dialog_1_2_1_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
			AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;

		case "GenQuest_Church_1_Dialog_1_2_2_1":
			dialog.text = StringFromKey("Common_church_290", pchar);
			link.l1 = StringFromKey("Common_church_291");
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;

		case "GenQuest_Church_1_Dialog_1_2_2_2":
			dialog.text = StringFromKey("Common_church_292", pchar, PChar.GenQuest.ChurchQuest_1.CapFullName);
			link.l1 = StringFromKey("Common_church_296", pchar, LinkRandPhrase(
						StringFromKey("Common_church_293"),
						StringFromKey("Common_church_294"),
						StringFromKey("Common_church_295")));
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;

		case "GenQuest_Church_1_Dialog_1_2_2_3":
			dialog.text = StringFromKey("Common_church_297", pchar, PChar.GenQuest.ChurchQuest_1.CapFullName);
			link.l1 = StringFromKey("Common_church_301", pchar, LinkRandPhrase(
						StringFromKey("Common_church_298"),
						StringFromKey("Common_church_299"),
						StringFromKey("Common_church_300")), PChar.GenQuest.ChurchQuest_1.CapFullName);
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;

		case "GenQuest_Church_1_Dialog_1_2_2_4":
			dialog.text = StringFromKey("Common_church_302", pchar);
			link.l1 = StringFromKey("Common_church_305", RandPhraseSimple(
						StringFromKey("Common_church_303"),
						StringFromKey("Common_church_304")));
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;

		case "GenQuest_Church_1_Dialog_1_2_2_5":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
			PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
			AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;

		case "GenQuest_Church_1_Complete_1":
			dialog.text = StringFromKey("Common_church_306", pchar);
			link.l1 = StringFromKey("Common_church_309", RandPhraseSimple(
						StringFromKey("Common_church_307"),
						StringFromKey("Common_church_308")));
			link.l1.go = "GenQuest_Church_1_Complete_2";
		break;

		case "GenQuest_Church_1_Complete_2":
			dialog.text = StringFromKey("Common_church_310", pchar);
			link.l1 = StringFromKey("Common_church_314", LinkRandPhrase(
						StringFromKey("Common_church_311"),
						StringFromKey("Common_church_312"),
						StringFromKey("Common_church_313")));
			link.l1.go = "GenQuest_Church_1_Complete_3";
		break;

		case "GenQuest_Church_1_Complete_3":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			//PChar.GenQuest.ChurchQuest_1.AwardSumm = (rand(8) + 2) * 500;
			RemoveItems(PChar, "ChurchManuscript", 1);
			DeleteAttribute(&items[FindItem("ChurchManuscript")], "City");
			ChangeCharacterReputation(PChar, 5);
			AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в лидерство
			AddCharacterExpToSkill(PChar, "Fortune", 50); // Бонус в удачу
			AddItemLog(pchar, "chest", its((3 + drand(1))), StringFromKey("InfoMessages_134"), "Important_item");
			sQuestTitle = NPChar.City + "ChurchGenQuest1";
			// Трем кэпа
			if (GetCharacterIndex("ChurchGenQuest1_Cap") != -1) characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
			Group_DeleteGroup("ChurchGenQuest1_CapGroup");
			PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = "yes";
			PChar.Quest.Church_GenQuest1_Timer.over = "yes"; // > снять таймер провала при успешной сдаче
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
			//			AddQuestUserData(sQuestTitle, "sSumm", FindMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm))); деньги из квеста еще в 1.2.0+ убрали, а эту строку не потерли
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
		break;
		// <-- Church GenQuest_1

		//--->> успокоить нечисть
		case "DestroyGhost_1":
			npchar.quest.DestroyGhost = "toCave"; //личный флаг священника на взятый квест
			//получим пещеру для чистки
			sTemp = GetArealByCityName(npchar.city);
			if (sTemp == "Cuba2") sTemp = "Cuba1";
			if (sTemp == "Hispaniola2") sTemp = "Hispaniola1";
			aref aPlace, aPlace_2;
			makearef(aPlace, NullCharacter.TravelMap.Islands.(sTemp).Treasure);
			int iQty = GetAttributesNum(aPlace) - 1;
			aPlace_2 = GetAttributeN(aPlace, rand(iQty));
			npchar.quest.DestroyGhost.locationId = GetAttributeName(aPlace_2); //Id целевой пещеры
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			npchar.quest.DestroyGhost.label = GetConvertStr(sld.id.label, "LocLables.txt"); //тип подземелья для диалогов
			switch (sld.id.label)
			{
				case "Cave":    sTemp = StringFromKey("Common_church_315") + " "; break;
				case "Grot":    sTemp = StringFromKey("Common_church_316") + " "; break;
				case "Dungeon": sTemp = StringFromKey("Common_church_317") + " "; break;
			}
			// EvgAnat - дикие карибы
			if (pchar.questTemp.GhostType == "indians")
			{
				sTemp += StringFromKey("Common_church_318");
			}
			else
			{
				sTemp += StringFromKey("Common_church_319");
			}
			dialog.text = StringFromKey("Common_church_320", sTemp);
			link.l1 = StringFromKey("Common_church_321");
			link.l1.go = "DestroyGhost_2";
		break;
		case "DestroyGhost_2":
		// EvgAnat - дикие карибы
			if (pchar.questTemp.GhostType == "indians")
			{
				sTemp = StringFromKey("Common_church_322");
			}
			else
			{
				sTemp = StringFromKey("Common_church_323");
			}
			dialog.text = StringFromKey("Common_church_324", pchar, sTemp);
			link.l1 = StringFromKey("Common_church_325", pchar);
			link.l1.go = "DestroyGhost_3";
			link.l2 = StringFromKey("Common_church_326");
			link.l2.go = "DestroyGhost_out";
		break;
		case "DestroyGhost_out":
			dialog.text = StringFromKey("Common_church_327", pchar);
			link.l1 = StringFromKey("Common_church_328");
			link.l1.go = "exit";
			DeleteAttribute(npchar, "quest.DestroyGhost");
			DeleteAttribute(pchar, "questTemp.GhostType");    // EvgAnat - дикие карибы
			ChangeCharacterReputation(pchar, -3);
		break;
		case "DestroyGhost_3":
			dialog.text = StringFromKey("Common_church_329", pchar);
			link.l1 = StringFromKey("Common_church_330");
			link.l1.go = "exit";
			pchar.questTemp.different = "DestroyGhost";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			//флаг квеста на локацию, сюда же пишем индекс дающего священника
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			sld.DestroyGhost = npchar.index;
			LAi_LocationResetMonGenTimer(sld.id);
			sTitle = npchar.location + "Church_DestroyGhost";
			ReOpenQuestHeader(sTitle);
			if (pchar.questTemp.GhostType == "indians")    // EvgAnat - дикие карибы
			{
				string sDestroyGhost = "DestroyGhost_" + npchar.id;
				AddQuestRecordEx(sTitle, "Church_DestroyGhost", "4");
				pchar.quest.(sDestroyGhost).win_condition.l1 = "location";
				pchar.quest.(sDestroyGhost).win_condition.l1.location = npchar.quest.DestroyGhost.locationId;
				pchar.quest.(sDestroyGhost).function = "SetIndiansToLocation";
			}
			else
			{
				AddQuestRecordEx(sTitle, "Church_DestroyGhost", "1");
			}
			switch (sld.id.label)
			{
				case "Cave":    sTemp = StringFromKey("Common_church_337"); break;
				case "Grot":    sTemp = StringFromKey("Common_church_338"); break;
				case "Dungeon": sTemp = StringFromKey("Common_church_339"); break;
			}
			pchar.questTemp.GhostType.title = npchar.location;
			AddQuestUserDataForTitle(sTitle, "sLocation", sTemp);
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sLocation", LowerFirst(npchar.quest.DestroyGhost.label));
		break;

		case "GhostShip_S1":
			dialog.text = StringFromKey("Common_church_331", pchar, NationNameGenitive(sti(NPChar.nation)));
			link.l1 = StringFromKey("Common_church_332", pchar);
			link.l1.go = "GhostShip_S2";
		break;
		case "GhostShip_S2":
			dialog.text = StringFromKey("Common_church_333", pchar);
			link.l1 = StringFromKey("Common_church_334");
			link.l1.go = "exit";
			if (pchar.questTemp.GhostType == "indians")
			{
				sTemp = StringFromKey("Common_church_335");
			}    // EvgAnat - дикие карибы
			else
			{
				sTemp = StringFromKey("Common_church_336");
			}
			sTemp += " ";
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			switch (sld.id.label)
			{
				case "Cave": sTemp += StringFromKey("Common_church_337"); break;
				case "Grot": sTemp += StringFromKey("Common_church_338"); break;
				case "Dungeon": sTemp += StringFromKey("Common_church_339"); break;
			}
			AddSimpleRumourCity(
						StringFromKey("Common_church_343", LinkRandPhrase(
								StringFromKey("Common_church_340", GetFullName(npchar), sTemp),
								StringFromKey("Common_church_341", pchar, sTemp),
								StringFromKey("Common_church_342", pchar, sTemp))), npchar.city, 10, 1, "");    // EvgAnat - дикие карибы
			ChangeCharacterReputation(pchar, 5);
			OfficersReaction("good");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			sld = &locations[FindLocation(npchar.quest.DestroyGhost.locationId)];
			sTitle = npchar.location + "Church_DestroyGhost";
			AddQuestRecordEx(sTitle, "Church_DestroyGhost", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader(sTitle);
			DeleteAttribute(npchar, "quest.DestroyGhost");
			DeleteAttribute(pchar, "questTemp.GhostType"); // EvgAnat - дикие карибы
		break;
		//<<--- успокоить нечисть
		//--->> ночной сторож
		case "NightChurch_1":
			dialog.text = StringFromKey("Common_church_344", pchar);
			link.l1 = StringFromKey("Common_church_345");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Common_church_346", pchar);
			link.l2.go = "NightChurch_2";
		break;
		case "NightChurch_2":
			dialog.text = StringFromKey("Common_church_347");
			link.l1 = StringFromKey("Common_church_348", pchar);
			link.l1.go = "NightChurch_3";
		break;
		case "NightChurch_3":
			dialog.text = StringFromKey("Common_church_349", pchar);
			link.l1 = StringFromKey("Common_church_350");
			link.l1.go = "exit";
			pchar.questTemp.different = "Church_NightGuard";
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты
			pchar.questTemp.different.Church_NightGuard = npchar.location; //флаг срабатывания нуля часов

			//по умолчанию в квесте был rand(3) и NightQty = 0. Что давало баги:
			//1. rand(3) и NightQty=0 == 0,1,2,3, получается 4 ночи, а нам надо 3.
			//2. Первая ночь была без оповещения
			//В текущей реализации если выпадет 0, то грабителей не будет, шанс 25%.
			pchar.questTemp.different.Church_NightGuard.NightQty = 1; //кол-вот отработанных ночей
			pchar.questTemp.different.Church_NightGuard.chance = rand(3); //рендом на появление грабителей

			pchar.questTemp.different.Church_NightGuard.fight = false; //флаг боевки
			SaveCurrentQuestDateParam("questTemp.different.Church_NightGuard"); //запишем дату
			sTitle = npchar.location + "Church_NightGuard";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Church_NightGuard", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		break;

		case "NightGuard_result":
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) == 0)
			{
				dialog.text = StringFromKey("Common_church_351", pchar);
				link.l1 = StringFromKey("Common_church_352");
				link.l1.go = "exit";
			}
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) > 0 && sti(pchar.questTemp.different.Church_NightGuard.NightQty) < 3)
			{
				dialog.text = StringFromKey("Common_church_353", pchar);
				link.l1 = StringFromKey("Common_church_354");
				link.l1.go = "exit";
			}
			if (sti(pchar.questTemp.different.Church_NightGuard.NightQty) >= 3)
			{
				if (sti(pchar.questTemp.different.Church_NightGuard.fight))
				{
					dialog.text = StringFromKey("Common_church_355", pchar);
					link.l1 = StringFromKey("Common_church_356");
					link.l1.go = "NightGuard_fight";
				}
				else
				{
					dialog.text = StringFromKey("Common_church_357", pchar);
					link.l1 = StringFromKey("Common_church_358", pchar);
					link.l1.go = "NightGuard_noLook";
				}
			}
		break;

		case "NightGuard_noLook":
			dialog.text = StringFromKey("Common_church_359", NationNameInstrumental(sti(npchar.nation)));
			link.l1 = StringFromKey("Common_church_360");
			link.l1.go = "exit";
			sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			CloseQuestHeader(sTitle);
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			OfficersReaction("good");
			AddSimpleRumourCity(
						StringFromKey("Common_church_364", LinkRandPhrase(
								StringFromKey("Common_church_361"),
								StringFromKey("Common_church_362"),
								StringFromKey("Common_church_363", GetFullName(npchar)))), npchar.city, 10, 1, "");
		break;
		case "NightGuard_fight":
			dialog.text = StringFromKey("Common_church_365", NationNameInstrumental(sti(npchar.nation)));
			link.l1 = StringFromKey("Common_church_366");
			link.l1.go = "exit";
			sTitle = pchar.questTemp.different.Church_NightGuard + "Church_NightGuard";
			CloseQuestHeader(sTitle);
			DeleteAttribute(pchar, "questTemp.different.Church_NightGuard");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 5);
			OfficersReaction("good");
			AddCharacterMaxHealth(pchar, 2);
			AddSimpleRumourCity(
						StringFromKey("Common_church_370", LinkRandPhrase(
								StringFromKey("Common_church_367"),
								StringFromKey("Common_church_368"),
								StringFromKey("Common_church_369", GetFullName(npchar)))), npchar.city, 10, 1, "");
		break;

		//<<--- ночной сторож

		case "healthAdd_1":
			if (sti(pchar.Health.maxHP) == 60.0) // отлично
			{
				dialog.text = StringFromKey("Common_church_371", GetHealthNameMaxSmall(pchar));
				link.l1 = StringFromKey("Common_church_372");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_church_373", GetHealthNameMaxSmall(pchar));
				link.l1 = StringFromKey("Common_church_374");
				link.l1.go = "healthAdd_2";
			}
			link.l2 = StringFromKey("Common_church_375");
			link.l2.go = "healthAdd_info";
		break;

		case "healthAdd_info":
			dialog.text = StringFromKey("Common_church_376", pchar);
			link.l1 = StringFromKey("Common_church_377");
			link.l1.go = "exit";
		break;

		case "healthAdd_2":
			dialog.text = StringFromKey("Common_church_378", pchar);
			link.l1 = StringFromKey("Common_church_379");
			link.l1.go = "healthAdd_3";
			link.l2 = StringFromKey("Common_church_380");
			link.l2.go = "exit";
		break;

		case "healthAdd_3":
			if (npchar.quest.HealthMonth != iMonth)
			{
				dialog.text = StringFromKey("Common_church_381");
				link.l1 = pcharrepphrase(
							StringFromKey("Common_church_382"),
							StringFromKey("Common_church_383"));
				link.l1.go = "healthAdd_4";
				link.l2 = StringFromKey("Common_church_384", pchar);
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_church_385", pchar);
				link.l1 = StringFromKey("Common_church_388", RandPhraseSimple(
							StringFromKey("Common_church_386"),
							StringFromKey("Common_church_387")));
				link.l1.go = "exit";
			}
		break;

		case "healthAdd_4":
			dialog.text = StringFromKey("Common_church_389");
			link.l1 = pcharrepphrase(
						StringFromKey("Common_church_390"),
						StringFromKey("Common_church_391"));
			link.l1.go = "exit";
			if (sti(pchar.Money) >= 100000)
			{
				link.l2 = StringFromKey("Common_church_392", pchar);
				link.l2.go = "healthAdd_5";
			}
		break;

		case "healthAdd_5":
			AddMoneyToCharacter(pchar, -100000);
			AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
			npchar.quest.HealthMonth = iMonth;
			dialog.text = StringFromKey("Common_church_393");
			link.l1 = StringFromKey("Common_church_394");
			link.l1.go = "exit";
		break;
		// диалог для капелата из тюряги
		case "Prison_Temp":
			NextDiag.TempNode = "Prison_Temp";
			dialog.text = StringFromKey("Common_church_395");
			link.l1 = StringFromKey("Common_church_396");
			link.l1.go = "Exit";
		break;

		case "Prison_Cell":
			NextDiag.TempNode = "Prison_Temp";
			dialog.text = StringFromKey("Common_church_397");
			link.l1 = StringFromKey("Common_church_398");
			link.l1.go = "Prison_Cell_Info";
			link.l2 = StringFromKey("Common_church_399");
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = StringFromKey("Common_church_400");
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Info":
			dialog.text = StringFromKey("Common_church_401");
			link.l1 = StringFromKey("Common_church_402");
			link.l1.go = "Prison_Cell_Info_2";
			link.l2 = StringFromKey("Common_church_403", pchar);
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = StringFromKey("Common_church_404", pchar);
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Info_2":
			dialog.text = StringFromKey("Common_church_405", pchar);
			link.l2 = StringFromKey("Common_church_406", pchar);
			link.l2.go = "Prison_Cell_Talk";
			link.l3 = StringFromKey("Common_church_407", pchar);
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_None":
			dialog.text = StringFromKey("Common_church_408");
			link.l1 = StringFromKey("Common_church_409");
			link.l1.go = "Prison_Cell_death";//"Exit";
		//AddDialogExitQuest("MoveToPrison_Cell");
		break;

		case "Prison_Cell_Talk":
			dialog.text = StringFromKey("Common_church_410", pchar);
			link.l2 = StringFromKey("Common_church_411", pchar);
			link.l2.go = "Prison_Cell_Talk_2";
			link.l3 = StringFromKey("Common_church_412", pchar);
			link.l3.go = "Prison_Cell_None";
		break;

		case "Prison_Cell_Talk_2":
			dialog.text = StringFromKey("Common_church_413");
			link.l1 = StringFromKey("Common_church_414");
			link.l1.go = "Prison_Cell_death";
		break;

		case "Prison_Cell_death":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			sld = &Characters[sti(PChar.GenQuest.ToPrisonCmdIdx)];
		break;
		//квест пожертвования хозяйки борделя
		case "HostessChurch":
			dialog.text = StringFromKey("Common_church_415");
			link.l1 = StringFromKey("Common_church_416");
			link.l1.go = "HostessChurch_call";
			link.l2 = StringFromKey("Common_church_417", pchar);
			link.l2.go = "HostessChurch_notCall";
			pchar.questTemp.different = "HostessChurch_return"; //флаг на возвращение
		break;
		case "HostessChurch_call":
		//			if (isBadReputation(pchar, 5))
			if (PlayerRPGCheck_BadReputation(5, true))
			{
				//				if (idRand(npchar.id + "Fortune", 100) < GetCharacterSkill(pchar, "Fortune")) //рендом вешаем на удачу
				if (PlayerRPGCheck_Skill("Fortune", idRand(npchar.id + "Fortune", 100), false)) //рендом вешаем на удачу
				{
					dialog.text = StringFromKey("Common_church_418", pchar);
					link.l1 = StringFromKey("Common_church_419");
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = StringFromKey("Common_church_420");
					link.l1 = StringFromKey("Common_church_421");
					link.l1.go = "HostessChurch_bad";
				}
			}
			else
			{
				//				if (idRand(npchar.id + "Charisma", 10) < GetCharacterSPECIAL(pchar, "Charisma")) //рендом вешаем на харизму
				if (PlayerRPGCheck_SPECIAL("Charisma", idRand(npchar.id + "Charisma", 10))) //рендом вешаем на харизму
				{
					dialog.text = StringFromKey("Common_church_422");
					link.l1 = StringFromKey("Common_church_423");
					link.l1.go = "HostessChurch_ok";
				}
				else
				{
					dialog.text = StringFromKey("Common_church_424", pchar);
					link.l1 = StringFromKey("Common_church_425");
					link.l1.go = "HostessChurch_bad_1";
				}
			}
		break;
		case "HostessChurch_notCall":
		//			if (idRand(npchar.id + "Charisma", 10) < GetCharacterSPECIAL(pchar, "Charisma"))
			if (PlayerRPGCheck_SPECIAL("Charisma", idRand(npchar.id + "Charisma", 10)))
			{
				dialog.text = StringFromKey("Common_church_426");
				link.l1 = StringFromKey("Common_church_427");
				link.l1.go = "HostessChurch_ok_1";
			}
			else
			{
				dialog.text = StringFromKey("Common_church_428", pchar);
				link.l1 = StringFromKey("Common_church_429");
				link.l1.go = "HostessChurch_bad_2";
			}
		break;

		case "HostessChurch_ok":
			dialog.text = StringFromKey("Common_church_430", pchar);
			link.l1 = StringFromKey("Common_church_431");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		case "HostessChurch_ok_1":
			dialog.text = StringFromKey("Common_church_432", pchar);
			link.l1 = StringFromKey("Common_church_433");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
			AddCharacterExpToSkill(pchar, "Fortune", 20);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;
		case "HostessChurch_bad":
			dialog.text = StringFromKey("Common_church_434");
			link.l1 = StringFromKey("Common_church_435");
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		case "HostessChurch_bad_1":
			dialog.text = StringFromKey("Common_church_436", pchar);
			link.l1 = StringFromKey("Common_church_437");
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		case "HostessChurch_bad_2":
			dialog.text = StringFromKey("Common_church_438", pchar);
			link.l1 = StringFromKey("Common_church_439");
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			npchar.quest.BadMeeting = lastspeak_date;
			//флаг удачная или неудачная попытка дачи
			characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;
		//зачарованный город. базар падре в Каракасе
		case "MC_CaracasChirch":
			dialog.text = StringFromKey("Common_church_440", pchar);
			link.l1 = StringFromKey("Common_church_441");
			link.l1.go = "MC_CaracasChirch_1";
		break;
		case "MC_CaracasChirch_1":
			dialog.text = StringFromKey("Common_church_442", pchar);
			link.l1 = StringFromKey("Common_church_443");
			link.l1.go = "exit";
			pchar.questTemp.MC = "toCaracasTavern";
			for (int i = 1; i <= 12; i++)
			{
				sld = characterFromId("CaracasCit_" + i);
				sld.lifeDay = 0;
			}
			//дым от костра
			locations[FindLocation("Caracas_town")].hidden_effects = true;

			RemoveLandQuestMark_Main(npchar, "MagicCity");
			AddLandQuestMark_Main(characterFromId("Caracas_tavernkeeper"), "MagicCity");
		break;
		//--> Jason Церковная депеша
		case "Monkletter":
			if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
			{
				dialog.text = StringFromKey("Common_church_444");
				link.l1 = StringFromKey("Common_church_445");
				link.l1.go = "Monkletter_1";
			}
			else
			{
				dialog.text = StringFromKey("Common_church_446");
				link.l1 = StringFromKey("Common_church_447");
				link.l1.go = "Monkletter_3";
			}
		break;

		case "Monkletter_1":
			dialog.text = StringFromKey("Common_church_448");
			link.l1 = StringFromKey("Common_church_449");
			link.l1.go = "Monkletter_2";
		break;

		case "Monkletter_2":
			DialogExit();
			pchar.quest.Monkletter_Failed.over = "yes"; //снять таймер
			RemoveItems(PChar, "letter_church", 1);
			AddQuestRecord("Monkletter", "2");
			CloseQuestHeader("Monkletter");
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;

		case "Monkletter_3":
			dialog.text = StringFromKey("Common_church_450");
			link.l1 = StringFromKey("Common_church_451");
			link.l1.go = "Monkletter_4";
		break;

		case "Monkletter_4":
			pchar.quest.Monkletter_Over.over = "yes"; //снять таймер
			DialogExit();
			RemoveItems(PChar, "letter_church", 1);
			AddQuestRecord("Monkletter", "3");
			AddQuestUserData("Monkletter", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Monkletter");
			GiveGoldOnAmount(1200 + idRand(npchar.id + "Monkletter", 5) * 100);
			ChangeCharacterReputation(pchar, 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;
		//<-- Церковная депеша

		//--> Jason Доставить молитвенники
		case "Churchbooks":
			dialog.text = StringFromKey("Common_church_452", XI_ConvertString("Colony" + pchar.GenQuest.Churchbooks.StartCity + "Gen"));
			link.l1 = StringFromKey("Common_church_453");
			link.l1.go = "Churchbooks_1";
		break;

		case "Churchbooks_1":
			dialog.text = StringFromKey("Common_church_454");
			link.l1 = "...";
			link.l1.go = "exit";
			AddQuestRecord("Churchbooks", "2");
			pchar.GenQuest.Churchbooks = "return";
			GiveItem2Character(pchar, "prayer_book");
		break;

		case "Churchbooks_2":
			if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
			{
				dialog.text = StringFromKey("Common_church_455");
				link.l1 = StringFromKey("Common_church_456");
				link.l1.go = "Churchbooks_3";
			}
			else
			{
				dialog.text = StringFromKey("Common_church_457");
				link.l1 = StringFromKey("Common_church_458");
				link.l1.go = "Churchbooks_4";
			}
		break;

		case "Churchbooks_3":
			dialog.text = StringFromKey("Common_church_459");
			link.l1 = StringFromKey("Common_church_460");
			link.l1.go = "exit";
			RemoveItems(PChar, "prayer_book", 1);
			AddQuestRecord("Churchbooks", "3");
			CloseQuestHeader("Churchbooks");
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks_4":
			dialog.text = StringFromKey("Common_church_461");
			link.l1 = StringFromKey("Common_church_462");
			link.l1.go = "Churchbooks_5";
		break;

		case "Churchbooks_5":
			pchar.quest.Churchbooks_Over.over = "yes";
			DialogExit();
			RemoveItems(PChar, "prayer_book", 1);
			AddItemLog(pchar, pchar.GenQuest.Churchbooks.Item, "1", StringFromKey("InfoMessages_135", GetItemName(pchar.GenQuest.Churchbooks.Item)), "Important_item"); //TODO: заменить на медицинские флаконы?
			AddQuestRecord("Churchbooks", "4");
			CloseQuestHeader("Churchbooks");
			ChangeCharacterReputation(pchar, 2);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "ChurchCup", 1);
	ref rItem = ItemsFromID("ChurchCup");
	DeleteAttribute(rItem, "City");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr);
	if (sColony == "none") sColony = SelectAnyColony(chr.city);
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	if (FindColony(sColony) != -1) PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	if (GetCharacterIndex(sColony + "_Priest") != -1) PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;

	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch (iRand)
	{
		case "0":
			PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
			Log_TestInfo("Церковный генератор 1: ключевая сцена - 2А (просто забрать у священника рукописи).");
		break;

		case "1":
			PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
			Log_TestInfo("Церковный генератор 1: ключевая сцена - 2Б-А (поиск кэпа. О нём есть полная информация).");
		break;

		case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
			PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
			Log_TestInfo("Церковный генератор 1: ключевая сцена - 2Б-Б (поиск кэпа. Название шипа неизвестно.)");
		break;
	}
}

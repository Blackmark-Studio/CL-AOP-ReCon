#include "DIALOGS\Common_Duel.c"

#define MAX_PGG_STORIES        9
#define MAX_PGG_QUEST_STORIES    3
#define MAX_PGG_MEET_REP        5

string PGG_Stories(ref NPChar, int index)
{
	string sPGG_Stories[MAX_PGG_STORIES];
	sPGG_Stories[0] = StringFromKey("pgg_dialog_1");
	sPGG_Stories[1] = StringFromKey("pgg_dialog_2");
	sPGG_Stories[2] = StringFromKey("pgg_dialog_3");
	sPGG_Stories[3] = StringFromKey("pgg_dialog_4");
	sPGG_Stories[4] = StringFromKey("pgg_dialog_5", npchar);
	sPGG_Stories[5] = StringFromKey("pgg_dialog_6", npchar);
	sPGG_Stories[6] = StringFromKey("pgg_dialog_7", npchar);
	sPGG_Stories[7] = StringFromKey("pgg_dialog_8", npchar);
	sPGG_Stories[8] = StringFromKey("pgg_dialog_9");

	return sPGG_Stories[index];
}

string PGG_QuestStories(ref NPChar, int index)
{
	string sPGG_QuestStories[MAX_PGG_QUEST_STORIES];
	sPGG_QuestStories[0] = StringFromKey("pgg_dialog_10", npchar, pchar);
	sPGG_QuestStories[1] = StringFromKey("pgg_dialog_11", npchar);
	sPGG_QuestStories[2] = StringFromKey("pgg_dialog_12", pchar);

	return sPGG_QuestStories[index];
}

string PGG_Meet_GoodRep(ref NPChar, int index)
{
	string sPGG_Meet_GoodRep[MAX_PGG_MEET_REP];
	sPGG_Meet_GoodRep[0] = StringFromKey("pgg_dialog_13");
	sPGG_Meet_GoodRep[1] = StringFromKey("pgg_dialog_14");
	sPGG_Meet_GoodRep[2] = StringFromKey("pgg_dialog_15");
	sPGG_Meet_GoodRep[3] = StringFromKey("pgg_dialog_16", pchar);
	sPGG_Meet_GoodRep[4] = StringFromKey("pgg_dialog_17", pchar);

	return sPGG_Meet_GoodRep[index];
}

string PGG_Meet_BadRep(ref NPChar, int index)
{
	string sPGG_Meet_BadRep[MAX_PGG_MEET_REP];
	sPGG_Meet_BadRep[0] = StringFromKey("pgg_dialog_18", pchar);
	sPGG_Meet_BadRep[1] = StringFromKey("pgg_dialog_19", pchar);
	sPGG_Meet_BadRep[2] = StringFromKey("pgg_dialog_20");
	sPGG_Meet_BadRep[3] = StringFromKey("pgg_dialog_21", pchar);
	sPGG_Meet_BadRep[4] = StringFromKey("pgg_dialog_22", pchar);

	return sPGG_Meet_BadRep[index];
}

void ProcessDialogEvent()
{
	int i, n;
	int iRnd = -1;
	int iAns;
	bool bOk;
	float locx, locy, locz;
	string sTmp, sLoc;
	ref NPChar, sld;
	aref link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessDuelDialog(NPChar, link, NextDiag);

	if (Dialog.CurrentNode == "First time" && CheckAttribute(NPChar, "meeting")) Dialog.CurrentNode = "Second time";
	switch (Dialog.CurrentNode)
	{
		//	Dialog.Text = "Вы видите баг... сообщите о нём АТ, для Navy.";
		//	link.l1 = "Обязательно!";
		//	link.l1.go = "exit.";
		case "First time":
			if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
			{
				Dialog.text = StringFromKey("pgg_dialog_23");
				link.l1 = StringFromKey("pgg_dialog_26", RandPhraseSimple(
							StringFromKey("pgg_dialog_24"),
							StringFromKey("pgg_dialog_25")));
				link.l1.go = "Exit_Smugglers_Fight";
				link.l2 = StringFromKey("pgg_dialog_27");
				link.l2.go = "Exit";
				break;
			}
			//		Dialog.Text = "Добрый день, меня зовут " + GetFullName(NPChar) + ", а вас?";
			if (rand(10) == 3)
			{
				iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
				Dialog.Text = PGG_QuestStories(NPChar, iRnd);
			}
			else
			{
				iRnd = rand(MAX_PGG_STORIES - 1);
				iAns = rand(MAX_PGG_MEET_REP - 1);
				Dialog.Text = PGG_Stories(NPChar, iRnd) + PCharRepPhrase(PGG_Meet_GoodRep(NPChar, iAns), PGG_Meet_BadRep(NPChar, iAns));
			}
			//		link.l1 = "А меня " + GetFullName(pchar) + ".";
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED)
			{
				link.l1 = PCharRepPhrase(
							StringFromKey("pgg_dialog_30", RandSwear(), RandPhraseSimple(
									StringFromKey("pgg_dialog_28", GetFullName(pchar)),
									StringFromKey("pgg_dialog_29", PChar.Ship.Name, GetFullName(pchar)))),
							StringFromKey("pgg_dialog_33", RandPhraseSimple(
									StringFromKey("pgg_dialog_31", GetFullName(pchar)),
									StringFromKey("pgg_dialog_32", pchar, PChar.Ship.Name, NationNameGenitive(sti(PChar.nation)), GetFullName(pchar)))));
			}
			else
			{
				link.l1 = PCharRepPhrase(
							StringFromKey("pgg_dialog_36", RandSwear(), RandPhraseSimple(
									StringFromKey("pgg_dialog_34", GetFullName(pchar)),
									StringFromKey("pgg_dialog_35", pchar, GetFullName(pchar)))),
							StringFromKey("pgg_dialog_39", RandPhraseSimple(
									StringFromKey("pgg_dialog_37", GetFullName(pchar)),
									StringFromKey("pgg_dialog_38", pchar, NationNameGenitive(sti(PChar.nation)), GetFullName(pchar)))));
			}
			link.l1.go = "Meeting";
		break;

		case "Meeting":
			Dialog.Text = StringFromKey("pgg_dialog_40", npchar, GetFullName(NPChar));
			link.l1 = StringFromKey("pgg_dialog_43", RandPhraseSimple(
						StringFromKey("pgg_dialog_41"),
						StringFromKey("pgg_dialog_42")));
			link.l1.go = "quest";
			if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
			{
				sld = GetRealShip(sti(NPChar.Ship.Type));

				Dialog.Text = StringFromKey("pgg_dialog_44", GetFullName(NPChar), GetStrSmallRegister(xiStr(sld.BaseName + "Acc")), NPChar.Ship.Name);
				link.l2 = StringFromKey("pgg_dialog_45", pchar);
				link.l2.go = "companion";
			}
			if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
			{
				link.l3 = StringFromKey("pgg_dialog_48", RandPhraseSimple(
							StringFromKey("pgg_dialog_46"),
							StringFromKey("pgg_dialog_47", npchar)));
				link.l3.go = "officer";
			}
			link.l9 = StringFromKey("pgg_dialog_49");
			link.l9.go = "exit";
			NextDiag.TempNode = "Second time";
			NPChar.meeting = true;
		break;

		case "Second time":
			if (CheckAttribute(NPChar, "PGGAi.location.town.back") && CheckAttribute(pchar, "questTemp.PGGContra.Know"))
			{
				Dialog.text = StringFromKey("pgg_dialog_50");
				link.l1 = StringFromKey("pgg_dialog_53", RandPhraseSimple(
							StringFromKey("pgg_dialog_51"),
							StringFromKey("pgg_dialog_52")));
				link.l1.go = "Exit_Smugglers_Fight";
				link.l2 = StringFromKey("pgg_dialog_54");
				link.l2.go = "Exit";
				break;
			}

			if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
			{
				Dialog.Text = StringFromKey("pgg_dialog_55", npchar);
				link.l1 = StringFromKey("pgg_dialog_56");
				link.l1.go = "exit";
				break;
			}
			if (bBettaTestMode)
			{
				link.l7 = StringFromKey("pgg_dialog_57");
				link.l7.go = "BT_Quest";
				link.l8 = StringFromKey("pgg_dialog_58");
				link.l8.go = "outraged";
			}
			Dialog.text = StringFromKey("pgg_dialog_61", RandPhraseSimple(
						StringFromKey("pgg_dialog_59", GetFullName(pchar)),
						StringFromKey("pgg_dialog_60")));
			link.l1 = StringFromKey("pgg_dialog_64", RandPhraseSimple(
						StringFromKey("pgg_dialog_62"),
						StringFromKey("pgg_dialog_63")));
			link.l1.go = "quest";

			if (PGG_ChangeRelation2MainCharacter(NPChar, 0) > 49)
			{
				//			Dialog.Text = RandPhraseSimple("Кого я вижу?!! Да это же " + GetFullName(pchar) + ". Что новенького?", "Как поживаете? Могу я быть чем-нибудь полезен?");
				if (rand(10) == 3)
				{
					iRnd = rand(MAX_PGG_QUEST_STORIES - 1);
					Dialog.Text = StringFromKey("pgg_dialog_67", PGG_QuestStories(NPChar, iRnd)) + " " + PCharRepPhrase(
								StringFromKey("pgg_dialog_65"),
								StringFromKey("pgg_dialog_66"));
				}
				else
				{
					iRnd = rand(MAX_PGG_STORIES - 1);
					iAns = rand(MAX_PGG_MEET_REP - 1);
					Dialog.Text = StringFromKey("pgg_dialog_70", PGG_Stories(NPChar, iRnd), PGG_Meet_GoodRep(NPChar, iAns)) + " " + PCharRepPhrase(
								StringFromKey("pgg_dialog_68"),
								StringFromKey("pgg_dialog_69"));
				}
				if (sti(pchar.Ship.Type) != SHIP_NOTUSED && sti(NPChar.Ship.Type) != SHIP_NOTUSED)
				{
					link.l2 = StringFromKey("pgg_dialog_73", RandPhraseSimple(
								StringFromKey("pgg_dialog_71", pchar),
								StringFromKey("pgg_dialog_72")));
					link.l2.go = "companion";
				}
				if (sti(NPChar.Ship.Type) == SHIP_NOTUSED)
				{
					Dialog.Text = StringFromKey("pgg_dialog_76", RandPhraseSimple(
								StringFromKey("pgg_dialog_74"),
								StringFromKey("pgg_dialog_75", npchar)));
					link.l3 = StringFromKey("pgg_dialog_79", RandPhraseSimple(
								StringFromKey("pgg_dialog_77"),
								StringFromKey("pgg_dialog_78")));
					link.l3.go = "exit";
					if (FindFreeRandomOfficer() > 0)
					{
						link.l3 = StringFromKey("pgg_dialog_82", RandPhraseSimple(
									StringFromKey("pgg_dialog_80"),
									StringFromKey("pgg_dialog_81")));
						link.l3.go = "officer";
					}
				}
				//			link.l4 = "Что нового слышно?";
				//			link.l4.go = "rumours_capitan";
			}
			if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 20 || bBettaTestMode)
			{
				link.l8 = PCharRepPhrase(
							StringFromKey("pgg_dialog_83"),
							StringFromKey("pgg_dialog_84", pchar));
				link.l8.go = "outraged";
			}
			link.l9 = StringFromKey("pgg_dialog_85");
			link.l9.go = "exit";
			NextDiag.TempNode = "Second time";
		break;

		case "no_ship":
		break;

		//==================================================
		// Officer
		//==================================================
		case "officer":
		//раз в день.
			if (CheckAttribute(NPChar, "Officer_Talk") && GetNpcQuestPastDayParam(NPChar, "Officer_Talk") < 1 && !bPGGLogShow)
			{
				Dialog.Text = StringFromKey("pgg_dialog_88", RandPhraseSimple(
							StringFromKey("pgg_dialog_86", npchar),
							StringFromKey("pgg_dialog_87")));
				link.l1 = StringFromKey("pgg_dialog_91", RandPhraseSimple(
							StringFromKey("pgg_dialog_89", pchar),
							StringFromKey("pgg_dialog_90")));
				link.l1.go = "exit";
				break;
			}
			//если уже был офицером, то посылает нафиг.
			if (CheckAttribute(NPChar, "PGGAi.Officer"))
			{
				Dialog.Text = StringFromKey("pgg_dialog_94", RandPhraseSimple(
							StringFromKey("pgg_dialog_92"),
							StringFromKey("pgg_dialog_93")));
				link.l1 = StringFromKey("pgg_dialog_97", RandPhraseSimple(
							StringFromKey("pgg_dialog_95"),
							StringFromKey("pgg_dialog_96")));
				link.l1.go = "exit";
				break;
			}
			//если отношение ниже 70, то в 70% случаев откажет...
			if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && idRand(npchar.id, 99) < 70)
			{
				Dialog.Text = StringFromKey("pgg_dialog_100", RandPhraseSimple(
							StringFromKey("pgg_dialog_98"),
							StringFromKey("pgg_dialog_99")));
				link.l1 = StringFromKey("pgg_dialog_103", RandPhraseSimple(
							StringFromKey("pgg_dialog_101"),
							StringFromKey("pgg_dialog_102")));
				link.l1.go = "exit";
				SaveCurrentNpcQuestDateParam(NPChar, "Officer_Talk");
				break;
			}
			//Проверка на ПИРАТЕС, не было! //navy 04.04.07
			if (FindFreeRandomOfficer() < 1)
			{
				Dialog.Text = StringFromKey("pgg_dialog_106", RandPhraseSimple(
							StringFromKey("pgg_dialog_104"),
							StringFromKey("pgg_dialog_105", pchar)));
				link.l1 = StringFromKey("pgg_dialog_109", RandPhraseSimple(
							StringFromKey("pgg_dialog_107"),
							StringFromKey("pgg_dialog_108")));
				link.l1.go = "exit";
				break;
			}
			if (!CheckAttribute(NPChar, "Quest.Officer.Price"))
			{
				NPChar.Quest.Officer.Price = 10000 + sti(NPChar.rank) * 500 * MOD_SKILL_ENEMY_RATE - MakeInt(GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE) * 1000);
			}
			Dialog.Text = NPCharRepPhrase(NPChar,
					StringFromKey("pgg_dialog_112", RandSwear(), RandPhraseSimple(
							StringFromKey("pgg_dialog_110", FindMoneyString(sti(NPChar.Quest.Officer.Price))),
							StringFromKey("pgg_dialog_111", pchar, FindMoneyString(sti(NPChar.Quest.Officer.Price))))),
					StringFromKey("pgg_dialog_116", LinkRandPhrase(
							StringFromKey("pgg_dialog_113", npchar, FindMoneyString(sti(NPChar.Quest.Officer.Price))),
							StringFromKey("pgg_dialog_114", pchar, FindMoneyString(sti(NPChar.Quest.Officer.Price))),
							StringFromKey("pgg_dialog_115", FindMoneyString(sti(NPChar.Quest.Officer.Price))))));

			MakeRandomLinkOrderTwo(link,
					PCharRepPhrase(
							StringFromKey("pgg_dialog_119", RandSwear(), RandPhraseSimple(
									StringFromKey("pgg_dialog_117"),
									StringFromKey("pgg_dialog_118"))),
							StringFromKey("pgg_dialog_123", LinkRandPhrase(
									StringFromKey("pgg_dialog_120", pchar, npchar),
									StringFromKey("pgg_dialog_121", pchar),
									StringFromKey("pgg_dialog_122")))), "officer_hired",
					PCharRepPhrase(
							StringFromKey("pgg_dialog_126", RandSwear(), RandPhraseSimple(
									StringFromKey("pgg_dialog_124"),
									StringFromKey("pgg_dialog_125", pchar))),
							StringFromKey("pgg_dialog_130", LinkRandPhrase(
									StringFromKey("pgg_dialog_127"),
									StringFromKey("pgg_dialog_128"),
									StringFromKey("pgg_dialog_129")))), "exit");
			link.l3 = StringFromKey("pgg_dialog_131");
			link.l3.go = "Exit_ShowParam";
		break;

		case "officer_hired":
			if (sti(pchar.money) < sti(NPChar.Quest.Officer.Price))
			{
				Dialog.Text = StringFromKey("pgg_dialog_132");
				link.l1 = StringFromKey("pgg_dialog_133");
				link.l1.go = "exit";
				break;
			}
			pchar.questTemp.HiringOfficerIDX = NPChar.index;
			AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Officer.Price)));
			AddDialogExitQuestFunction("PGG_BecomeHiredOfficer");
			NPChar.loyality = MakeInt(PGG_ChangeRelation2MainCharacter(NPChar, 0) * 0.3);

			DeleteAttribute(NPChar, "Quest.Officer");
			DeleteAttribute(NPChar, "PGGAi.Task");
			DeleteAttribute(NPChar, "PGGAi.LockService");

			Dialog.Text = StringFromKey("pgg_dialog_136", RandPhraseSimple(
						StringFromKey("pgg_dialog_134"),
						StringFromKey("pgg_dialog_135", npchar)));
			link.l1 = StringFromKey("pgg_dialog_137");
			link.l1.go = "exit";
		break;

		//==================================================
		// Companion
		//==================================================
		case "companion":
			Dialog.Text = StringFromKey("pgg_dialog_138");
			link.l1 = StringFromKey("pgg_dialog_139");
			link.l1.go = "exit";
			//раз в день.
			if (CheckAttribute(NPChar, "Companion_Talk") && GetNpcQuestPastDayParam(NPChar, "Companion_Talk") < 1 && !bPGGLogShow)
			{
				Dialog.Text = StringFromKey("pgg_dialog_142", RandPhraseSimple(
							StringFromKey("pgg_dialog_140", npchar),
							StringFromKey("pgg_dialog_141")));
				link.l1 = StringFromKey("pgg_dialog_145", RandPhraseSimple(
							StringFromKey("pgg_dialog_143", pchar),
							StringFromKey("pgg_dialog_144")));
				link.l1.go = "exit";
				break;
			}
			//разница в один класс.. нефиг халявить
			if (GetCharacterShipClass(NPChar) < GetCharacterShipClass(PChar) - 1)
			{
				Dialog.Text = StringFromKey("pgg_dialog_148", RandPhraseSimple(
							StringFromKey("pgg_dialog_146"),
							StringFromKey("pgg_dialog_147")));
				link.l1 = StringFromKey("pgg_dialog_151", RandPhraseSimple(
							StringFromKey("pgg_dialog_149"),
							StringFromKey("pgg_dialog_150")));
				link.l1.go = "exit";
				SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
				break;
			}
			//если отношение ниже 70, то в 70% случаев откажет...
			if (PGG_ChangeRelation2MainCharacter(NPChar, 0) < 70 && idRand(npchar.id, 99) < 70)
			{
				Dialog.Text = StringFromKey("pgg_dialog_154", RandPhraseSimple(
							StringFromKey("pgg_dialog_152"),
							StringFromKey("pgg_dialog_153")));
				link.l1 = StringFromKey("pgg_dialog_157", RandPhraseSimple(
							StringFromKey("pgg_dialog_155"),
							StringFromKey("pgg_dialog_156")));
				link.l1.go = "exit";
				SaveCurrentNpcQuestDateParam(NPChar, "Companion_Talk");
				break;
			}
			//есть ли место для компаньона.
			if (SetCompanionIndex(pchar, -1, sti(NPChar.index)) != -1)
			{
				Dialog.Text = NPCharRepPhrase(NPChar,
						StringFromKey("pgg_dialog_160", RandSwear(), RandPhraseSimple(
								StringFromKey("pgg_dialog_158"),
								StringFromKey("pgg_dialog_159", pchar))),
						StringFromKey("pgg_dialog_164", LinkRandPhrase(
								StringFromKey("pgg_dialog_161", npchar),
								StringFromKey("pgg_dialog_162"),
								StringFromKey("pgg_dialog_163"))));
				link.l1 = StringFromKey("pgg_dialog_167", RandPhraseSimple(
							StringFromKey("pgg_dialog_165"),
							StringFromKey("pgg_dialog_166")));
				link.l1.go = "exit";
				NPChar.PGGAi.IsPGG = false;
				NPChar.PGGAi.location.town = "none";
				NPChar.Dialog.TempNode = "hired";
				NPChar.Dialog.FileName = "Officer_Man.c";
				NPChar.Payment = true;
				NPChar.Money = 0;

				SetBaseShipData(NPChar);
				ShipOverhaul(NPChar);

				Fantom_SetCannons(NPChar, "pirate");
				Fantom_SetBalls(NPChar, "pirate");

				DeleteAttribute(NPChar, "PGGAi.Task");
				DeleteAttribute(NPChar, "PGGAi.LockService");
				SetCharacterRemovable(NPChar, true);
				SaveCurrentNpcQuestDateParam(NPChar, "Companion.CheckRelation");
			}
			else
			{
				Dialog.Text = StringFromKey("pgg_dialog_170", RandPhraseSimple(
							StringFromKey("pgg_dialog_168"),
							StringFromKey("pgg_dialog_169")));
				link.l1 = StringFromKey("pgg_dialog_171", npchar);
				link.l1.go = "exit";
			}
		break;

		case "companion_leave":
			Dialog.Text = StringFromKey("pgg_dialog_178", RandSwear()) + NPCharRepPhrase(NPChar,
					StringFromKey("pgg_dialog_174", RandPhraseSimple(
							StringFromKey("pgg_dialog_172", pchar),
							StringFromKey("pgg_dialog_173"))),
					StringFromKey("pgg_dialog_177", RandPhraseSimple(
							StringFromKey("pgg_dialog_175", npchar),
							StringFromKey("pgg_dialog_176"))));
			link.l1 = PCharRepPhrase(
						StringFromKey("pgg_dialog_181", RandPhraseSimple(
								StringFromKey("pgg_dialog_179"),
								StringFromKey("pgg_dialog_180"))),
						StringFromKey("pgg_dialog_184", RandPhraseSimple(
								StringFromKey("pgg_dialog_182"),
								StringFromKey("pgg_dialog_183"))));
			link.l1.go = "Exit_Companion_Leave";
			link.l2 = PCharRepPhrase(
						StringFromKey("pgg_dialog_187", RandPhraseSimple(
								StringFromKey("pgg_dialog_185"),
								StringFromKey("pgg_dialog_186", pchar))),
						StringFromKey("pgg_dialog_190", RandPhraseSimple(
								StringFromKey("pgg_dialog_188"),
								StringFromKey("pgg_dialog_189"))));
			link.l2.go = "companion_stay";
		break;

		case "companion_stay":
			if (CheckAttribute(NPChar, "Quest.Companion"))
			{
				Dialog.Text = StringFromKey("pgg_dialog_193", RandPhraseSimple(
							StringFromKey("pgg_dialog_191"),
							StringFromKey("pgg_dialog_192")));
				link.l1 = StringFromKey("pgg_dialog_196", RandPhraseSimple(
							StringFromKey("pgg_dialog_194"),
							StringFromKey("pgg_dialog_195", pchar)));
				link.l1.go = "Exit_Companion_Leave";
				break;
			}
			NPChar.Quest.Companion.Price = 2 * GetSalaryForShip(NPChar);
			Dialog.Text = StringFromKey("pgg_dialog_203", RandSwear()) + NPCharRepPhrase(NPChar,
					StringFromKey("pgg_dialog_199", RandPhraseSimple(
							StringFromKey("pgg_dialog_197", FindMoneyString(sti(NPChar.Quest.Companion.Price))),
							StringFromKey("pgg_dialog_198", FindMoneyString(sti(NPChar.Quest.Companion.Price))))),
					StringFromKey("pgg_dialog_202", RandPhraseSimple(
							StringFromKey("pgg_dialog_200", npchar, FindMoneyString(sti(NPChar.Quest.Companion.Price))),
							StringFromKey("pgg_dialog_201", FindMoneyString(sti(NPChar.Quest.Companion.Price))))));
			link.l1 = PCharRepPhrase(
						StringFromKey("pgg_dialog_206", RandPhraseSimple(
								StringFromKey("pgg_dialog_204"),
								StringFromKey("pgg_dialog_205"))),
						StringFromKey("pgg_dialog_209", RandPhraseSimple(
								StringFromKey("pgg_dialog_207", pchar),
								StringFromKey("pgg_dialog_208"))));
			link.l1.go = "Exit_Companion_Leave";
			if (sti(pchar.money) >= sti(NPChar.Quest.Companion.Price))
			{
				link.l2 = PCharRepPhrase(
							StringFromKey("pgg_dialog_212", RandPhraseSimple(
									StringFromKey("pgg_dialog_210"),
									StringFromKey("pgg_dialog_211", pchar))),
							StringFromKey("pgg_dialog_215", RandPhraseSimple(
									StringFromKey("pgg_dialog_213", pchar),
									StringFromKey("pgg_dialog_214"))));
				link.l2.go = "Exit_Companion_Stay";
			}
		break;

		case "Exit_Companion_Leave":
			chrDisableReloadToLocation = false;
			RemoveCharacterCompanion(pchar, NPChar);

			NPChar.PGGAi.IsPGG = true;
			NPChar.RebirthPhantom = true;
			NPChar.PGGAi.location.town = GetCurrentTown();

			LAi_SetWarriorTypeNoGroup(NPChar);
			NextDiag.CurrentNode = "Second Time";
			DialogExit();
		break;

		case "Exit_Companion_Stay":
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
			LAi_ActorGoToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

			AddMoneyToCharacter(pchar, -(makeint(NPChar.Quest.Companion.Price)));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//==================================================
		// Quests
		//==================================================
		//==== BETTA_TEST ====
		case "BT_Quest":
			Dialog.Text = StringFromKey("pgg_dialog_216");
			link.l1 = StringFromKey("pgg_dialog_217");
			link.l1.go = "BT_Quest_1";
			link.l2 = StringFromKey("pgg_dialog_218");
			link.l2.go = "BT_Quest_2";
		break;

		case "BT_Quest_1":
			NPChar.PGGAi.ActiveQuest.QstNumber = 0;
			NPChar.PGGAi.ActiveQuest.QstNumber.Template = 1;
			Dialog.Text = StringFromKey("pgg_dialog_219");
			link.l1 = StringFromKey("pgg_dialog_220");
			link.l1.go = "quest";
		break;
		case "BT_Quest_2":
			NPChar.PGGAi.ActiveQuest.QstNumber = 0;
			NPChar.PGGAi.ActiveQuest.QstNumber.Template = 0;
			Dialog.Text = StringFromKey("pgg_dialog_221");
			link.l1 = StringFromKey("pgg_dialog_222");
			link.l1.go = "quest";
		break;
		//==== BETTA_TEST ====

		case "quest":
			chrDisableReloadToLocation = false;
			if (CheckAttribute(NPChar, "QuestTalk") && GetNpcQuestPastDayParam(NPChar, "QuestTalk") < 1)
			{
				Dialog.Text = StringFromKey("pgg_dialog_223", npchar);
				link.l1 = StringFromKey("pgg_dialog_224");
				link.l1.go = "exit";
				break;
			}
			Dialog.Text = StringFromKey("pgg_dialog_227", RandPhraseSimple(
						StringFromKey("pgg_dialog_225"),
						StringFromKey("pgg_dialog_226")));
			link.l1 = StringFromKey("pgg_dialog_228");
			link.l1.go = "exit";
			if (!PGG_IsQuestAvaible()) break; //квест нельзя брать.
			//if (!CheckAttribute(NPChar, "PGGAi.ActiveQuest") && !bBettaTestMode) break; //для релиза возможно надо будет закрыть. если закоментить, то ГГ сам может предложить дело
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber")) iRnd = sti(NPChar.PGGAi.ActiveQuest.QstNumber); //тип квеста, который хочет от нас ПГГ
			if (iRnd == -1 && !CheckAttribute(pchar, "GenQuest.PGG_Quest")) iRnd = rand(1); // может и не быть
			switch (iRnd)
			{
				case 0:
					if (sti(NPChar.Ship.Type) != SHIP_NOTUSED && sti(PChar.Ship.Type) != SHIP_NOTUSED && GetCharacterShipClass(PChar) <= 4 && GetCompanionQuantity(PChar) < COMPANION_MAX)
					{
						//квест от ПГГ
						/*if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
						{ */
						if (!CheckAttribute(pchar, "GenQuest.PGG_Quest"))
						{
							// не занят другими квестами ПГГ
							Dialog.Text = StringFromKey("pgg_dialog_229");
							link.l1 = StringFromKey("pgg_dialog_230");
							link.l1.go = "Quest_1_Work";
							NPChar.PGGAi.ActiveQuest = 1; // чтоб говорил от своего имени
							PChar.GenQuest.PGG_Quest = 1; // чтоб не достовали другие ПГГ
						}
						/* }
						//квест от ГГ
						else
						{
							if ()
							{
								Log_TestInfo("Пошло тестовое предложение самого ГГ");

								Dialog.Text = LinkRandPhrase("... только я и дьявол знаем это место и последний, кто останется в живых, заберёт себе всё!...",
									 "... а Мейнард ответил: 'Я не жду от тебя пощады, и ты тоже не дождешься её от меня'",
									 "... однажды в море, будучи немного пьяным, он предложил: 'Давайте здесь сейчас устроим себе сами ад и посмотрим, кто дольше выдержит'.") +
									 PCharRepPhrase(LinkRandPhrase("А вот и ещё один пират!",
											"Джентльмены, у нашего стола джентльмен удачи, я полагаю.",
											"Запахло порохом и кровью, флибустьер справа по борту!"),
										LinkRandPhrase("Редко встретишь порядочного капитана в этих морях.",
											"Благородство не в моде в наше время.",
											"А вот и честный капитан, не чета вам, головорезы! Хе-хе!"));
								link.l1 = "Я не ору, а говорю - дело есть! Прибыльное!";
								link.l1.go = "Quest_1_Work";
							}
						}  /**/
					}
				break;
			}
			SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

		case "quest_onStay": // ПГГ сам подходит
			chrDisableReloadToLocation = false;
			Dialog.Text = StringFromKey("pgg_dialog_231", npchar, GetFullName(PChar));
			if (!CheckAttribute(NPChar, "meeting") || !sti(NPChar.meeting))
			{
				if (sti(pchar.Ship.Type) != SHIP_NOTUSED)
				{
					link.l1 = PCharRepPhrase(
								StringFromKey("pgg_dialog_234", RandSwear(), RandPhraseSimple(
										StringFromKey("pgg_dialog_232", GetFullName(pchar)),
										StringFromKey("pgg_dialog_233", PChar.Ship.Name, GetFullName(pchar)))),
								StringFromKey("pgg_dialog_237", RandPhraseSimple(
										StringFromKey("pgg_dialog_235", GetFullName(pchar)),
										StringFromKey("pgg_dialog_236", pchar, PChar.Ship.Name, NationNameGenitive(sti(PChar.nation)), GetFullName(pchar)))));
				}
				else
				{
					link.l1 = PCharRepPhrase(
								StringFromKey("pgg_dialog_240", RandSwear(), RandPhraseSimple(
										StringFromKey("pgg_dialog_238", GetFullName(pchar)),
										StringFromKey("pgg_dialog_239", GetFullName(pchar)))),
								StringFromKey("pgg_dialog_243", RandPhraseSimple(
										StringFromKey("pgg_dialog_241", GetFullName(pchar)),
										StringFromKey("pgg_dialog_242", pchar, NationNameGenitive(sti(PChar.nation)), GetFullName(pchar)))));
				}
				link.l1.go = "Quest_1_Meeting";
			}
			else
			{
				link.l1 = StringFromKey("pgg_dialog_244", GetFullName(NPChar));
				link.l1.go = "Quest_1_Work";
			}
			SaveCurrentNpcQuestDateParam(NPChar, "QuestTalk");
		break;

		//=========== Первый квест ==========
		case "Quest_1_Meeting":
			sld = GetRealShip(sti(NPChar.Ship.Type));
			Dialog.Text = StringFromKey("pgg_dialog_247", GetFullName(NPChar), xiStr(sld.BaseName + "Acc"), NPChar.Ship.Name) + " " + NPCharRepPhrase(NPChar,
					StringFromKey("pgg_dialog_245", npchar),
					StringFromKey("pgg_dialog_246"));
			link.l1 = StringFromKey("pgg_dialog_248");
			link.l1.go = "Quest_1_Work";
			NPChar.meeting = true;
		break;

		case "Quest_1_Work":
			iRnd = rand(3);
			PChar.GenQuest.PGG_Quest.Template = rand(1);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest.QstNumber.Template"))
			{
				PChar.GenQuest.PGG_Quest.Template = NPChar.PGGAi.ActiveQuest.QstNumber.Template;
			}
			PChar.GenQuest.PGG_Quest.Parts = GetCompanionQuantity(PChar) + 1;
			PChar.GenQuest.PGG_Quest.Nation = iRnd;
			PChar.GenQuest.PGG_Quest.Island = GetRandomIslandExcept("Panama,Pearl,Tenotchitlan");
			while(PChar.GenQuest.PGG_Quest.Island == Islands[GetCharacterCurrentIsland(pchar)].id)
			{
				PChar.GenQuest.PGG_Quest.Island = GetRandomIslandExcept("Panama,Pearl,Tenotchitlan");
			}
			PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomFreeShoreId(PChar.GenQuest.PGG_Quest.Island);
			while(PChar.GenQuest.PGG_Quest.Island.Shore == "")
			{
				PChar.GenQuest.PGG_Quest.Island = GetRandomIslandExcept("Panama,Pearl,Tenotchitlan");
				PChar.GenQuest.PGG_Quest.Island.Shore = GetIslandRandomFreeShoreId(PChar.GenQuest.PGG_Quest.Island);
				if (sti(PChar.GenQuest.PGG_Quest.Template))
				{
					if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
				}
				else
				{
					if (!isLocationFreeForQuests(PChar.GenQuest.PGG_Quest.Island.Shore)) PChar.GenQuest.PGG_Quest.Island.Shore = "";
				}
			}
			//Rosarak. Город берём по ареалу бухты (может быть и "none")
			PChar.GenQuest.PGG_Quest.Island.Town = GetCityNameByLocation(&locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)]);
			PChar.GenQuest.PGG_Quest.Days = 3 + GetMaxDaysFromColony2Island(GetCurrentTown(), PChar.GenQuest.PGG_Quest.Island);
			PChar.GenQuest.PGG_Quest.Goods = GOOD_SLAVES + rand(2);
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				//			Dialog.Text = "Дело у меня к тебе, "+ GetSexPhrase("приятель","подруга") +". Знаю, можно тебе довериться, но в таверне обсуждать не возьмусь, ушей много лишних. Жду тебя у меня на борту. Помнишь, моя посудина зовется '" + NPChar.Ship.Name + "'.";
				//			link.l1 = "Выкладывай сейчас, некогда мне по гостям расхаживать.";
				Dialog.Text = PCharRepPhrase(
							StringFromKey("pgg_dialog_251", RandPhraseSimple(
									StringFromKey("pgg_dialog_249"),
									StringFromKey("pgg_dialog_250"))),
							StringFromKey("pgg_dialog_254", RandPhraseSimple(
									StringFromKey("pgg_dialog_252"),
									StringFromKey("pgg_dialog_253")))) + " " + StringFromKey("pgg_dialog_257", RandPhraseSimple(
							StringFromKey("pgg_dialog_255", NPChar.Ship.Name),
							StringFromKey("pgg_dialog_256", NPChar.Ship.Name)));
				link.l1 = PCharRepPhrase(
							StringFromKey("pgg_dialog_260", RandSwear(), RandPhraseSimple(
									StringFromKey("pgg_dialog_258"),
									StringFromKey("pgg_dialog_259"))),
							StringFromKey("pgg_dialog_263", RandPhraseSimple(
									StringFromKey("pgg_dialog_261"),
									StringFromKey("pgg_dialog_262"))));
			}
			else
			{
				PChar.GenQuest.PGG_Quest.Nation = FindEnemyNation2NationWithoutPirates(sti(PChar.Nation));
				Dialog.Text = StringFromKey("pgg_dialog_264", NPChar.Ship.Name);
				link.l1 = StringFromKey("pgg_dialog_265");
			}
			link.l1.go = "Quest_1_Work_1";
			link.l2 = PCharRepPhrase(
						StringFromKey("pgg_dialog_268", RandPhraseSimple(
								StringFromKey("pgg_dialog_266"),
								StringFromKey("pgg_dialog_267", RandSwear()))),
						StringFromKey("pgg_dialog_271", RandPhraseSimple(
								StringFromKey("pgg_dialog_269"),
								StringFromKey("pgg_dialog_270"))));
			link.l2.go = "Exit_Quest_1_AfterTavernTalk";
		break;

		case "Quest_1_Work_1":
			Dialog.Text = PCharRepPhrase(
						StringFromKey("pgg_dialog_274", RandPhraseSimple(
								StringFromKey("pgg_dialog_272"),
								StringFromKey("pgg_dialog_273", pchar))),
						StringFromKey("pgg_dialog_277", RandPhraseSimple(
								StringFromKey("pgg_dialog_275"),
								StringFromKey("pgg_dialog_276"))));
			link.l1 = PCharRepPhrase(
						StringFromKey("pgg_dialog_280", RandPhraseSimple(
								StringFromKey("pgg_dialog_278"),
								StringFromKey("pgg_dialog_279"))),
						StringFromKey("pgg_dialog_283", RandPhraseSimple(
								StringFromKey("pgg_dialog_281", pchar),
								StringFromKey("pgg_dialog_282", pchar))));
			link.l1.go = "Exit_Quest_1_AfterTavernTalk";
			link.l2 = PCharRepPhrase(
						StringFromKey("pgg_dialog_286", RandPhraseSimple(
								StringFromKey("pgg_dialog_284"),
								StringFromKey("pgg_dialog_285"))),
						StringFromKey("pgg_dialog_289", RandPhraseSimple(
								StringFromKey("pgg_dialog_287", pchar),
								StringFromKey("pgg_dialog_288", GetFullName(NPChar)))));
			link.l2.go = "Quest_1_NotWork";
		break;

		case "Quest_1_NotWork":
			Dialog.Text = PCharRepPhrase(
						StringFromKey("pgg_dialog_292", RandPhraseSimple(
								StringFromKey("pgg_dialog_290"),
								StringFromKey("pgg_dialog_291"))),
						StringFromKey("pgg_dialog_295", RandPhraseSimple(
								StringFromKey("pgg_dialog_293", npchar),
								StringFromKey("pgg_dialog_294"))));
			link.l1 = RandSwear();
			link.l1.go = "exit_2";
		break;

		case "Quest_1_Work_2":
			Dialog.Text = StringFromKey("pgg_dialog_296", npchar);
			link.l1 = StringFromKey("pgg_dialog_297");
			link.l1.go = "exit";
			NextDiag.TempNode = "Quest_1_Work_2";
		break;

		case "Exit_Quest_1_AfterTavernTalk":
			PChar.GenQuest.PGG_Quest = 1;
			PChar.GenQuest.PGG_Quest.Stage = 0;
			PChar.GenQuest.PGG_Quest.PGGid = NPChar.id;

			Group_DeleteGroup("PGGQuest");
			Group_AddCharacter("PGGQuest", NPChar.id);
			Group_SetGroupCommander("PGGQuest", NPChar.id);
			Group_SetAddress("PGGQuest", Islands[GetCharacterCurrentIsland(PChar)].id, "Quest_Ships", "Quest_Ship_1");
			Group_SetTaskNone("PGGQuest");

			// туториал -->
			pchar.quest.PGGQuest_LaunchBoatTutor.win_condition.l1 = "EnterToSea";
			pchar.quest.PGGQuest_LaunchBoatTutor.function = "PGGQuest_LaunchBoatTutor";
			// <--
			SetTimerConditionParamFunction("PGGQuest1_RemoveShip_Timer", "PGG_Q1RemoveShip", 0, 0, 0, MakeInt(GetHour() + 6), false);

			NPChar.Ship.Mode = "Pirate";
			NPChar.DeckDialogNode = "Quest_1_Ship";
			NPChar.Nation.Bak = NPChar.Nation;
			NPChar.Nation = GetCityNation(GetCurrentTown());
			NPChar.AlwaysFriend = true;
			NPChar.Abordage.Enable = false; //нельзя брать на абордаж
			SetCharacterRelationBoth(sti(PChar.index), sti(NPChar.index), RELATION_FRIEND);

			ReOpenQuestHeader("Gen_PGGQuest1");
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				AddQuestRecord("Gen_PGGQuest1", "q1_Tavern");
			}
			else
			{
				AddQuestRecord("Gen_PGGQuest1", "q1_Tavern_1");
				AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("", "а"));
			}
			AddQuestUserData("Gen_PGGQuest1", "sShipName", NPChar.Ship.Name);

			NextDiag.CurrentNode = "Quest_1_Work_2";
			DialogExit();
			if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Quest_1_Ship":
			PChar.Quest.PGGQuest1_RemoveShip_Timer.Over = "yes";
			if (GetCompanionQuantity(PChar) == COMPANION_MAX)
			{
				Dialog.Text = StringFromKey("pgg_dialog_300", RandPhraseSimple(
							StringFromKey("pgg_dialog_298", pchar),
							StringFromKey("pgg_dialog_299")));
				link.l1 = StringFromKey("pgg_dialog_303", RandPhraseSimple(
							StringFromKey("pgg_dialog_301"),
							StringFromKey("pgg_dialog_302")));
				link.l1.go = "Exit";
				PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1 = "ExitFromLocation";
				PChar.Quest.PGGQuest1_RemoveEnd.win_condition.l1.Location = PChar.location;
				PChar.Quest.PGGQuest1_RemoveEnd.function = "PGG_Q1RemoveShip";
				break;
			}
			PChar.GenQuest.PGG_Quest.Stage = 1;
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = StringFromKey("pgg_dialog_306", RandPhraseSimple(
							StringFromKey("pgg_dialog_304"),
							StringFromKey("pgg_dialog_305", npchar)));
				link.l1 = StringFromKey("pgg_dialog_309", RandPhraseSimple(
							StringFromKey("pgg_dialog_307"),
							StringFromKey("pgg_dialog_308", npchar)));
			}
			else
			{
				Dialog.Text = StringFromKey("pgg_dialog_310", npchar);
				link.l1 = StringFromKey("pgg_dialog_311");
			}
			link.l1.go = "Quest_1_Ship_1";
		break;

		case "Quest_1_Ship_1":
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = StringFromKey("pgg_dialog_314", RandPhraseSimple(
							StringFromKey("pgg_dialog_312"),
							StringFromKey("pgg_dialog_313")));
				link.l1 = PCharRepPhrase(
							StringFromKey("pgg_dialog_317", RandSwear(), RandPhraseSimple(
									StringFromKey("pgg_dialog_315"),
									StringFromKey("pgg_dialog_316"))),
							StringFromKey("pgg_dialog_320", RandPhraseSimple(
									StringFromKey("pgg_dialog_318"),
									StringFromKey("pgg_dialog_319"))));
				link.l1.go = "Quest_1_Ship_Detail";
				link.l2 = PCharRepPhrase(
							StringFromKey("pgg_dialog_323", RandPhraseSimple(
									StringFromKey("pgg_dialog_321"),
									StringFromKey("pgg_dialog_322", pchar))),
							StringFromKey("pgg_dialog_326", RandPhraseSimple(
									StringFromKey("pgg_dialog_324", pchar),
									StringFromKey("pgg_dialog_325"))));
				link.l2.go = "Quest_1_Ship_Refuse";
			}
			else
			{
				Dialog.Text = StringFromKey("pgg_dialog_327");
				link.l1 = StringFromKey("pgg_dialog_328");
				link.l1.go = "Quest_1_Ship_Detail";
			}
		break;

		case "Quest_1_Ship_Detail":
			sTmp = StringFromKey("pgg_dialog_329", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation))) + " ";
			if (sti(PChar.GenQuest.PGG_Quest.Goods) == GOOD_SLAVES)
			{
				sTmp += LowerFirst(StringFromKey("pgg_dialog_330"));
				PChar.GenQuest.PGG_Quest.Goods.Text = LowerFirst(StringFromKey("pgg_dialog_331"));
			}
			else
			{
				sTmp += LowerFirst(XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name));
				PChar.GenQuest.PGG_Quest.Goods.Text = LowerFirst(XI_ConvertString(Goods[sti(PChar.GenQuest.PGG_Quest.Goods)].Name));
			}

			if (PChar.GenQuest.PGG_Quest.Island.Town == "none")
			{
				sLoc = XI_ConvertString(PChar.GenQuest.PGG_Quest.Island + "Gen");
			}
			else
			{
				sLoc = XI_ConvertString("Colony" + PChar.GenQuest.PGG_Quest.Island.Town + "Gen");
			}

			if (sti(PChar.GenQuest.PGG_Quest.Template))
			{
				sTmp += StringFromKey("pgg_dialog_332", sLoc, GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
			}
			else
			{
				sTmp += StringFromKey("pgg_dialog_333", sLoc, GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
			}

			Dialog.Text = sTmp;
			link.l1 = PCharRepPhrase(
						StringFromKey("pgg_dialog_336", RandSwear(), RandPhraseSimple(
								StringFromKey("pgg_dialog_334"),
								StringFromKey("pgg_dialog_335", pchar))),
						StringFromKey("pgg_dialog_339", RandPhraseSimple(
								StringFromKey("pgg_dialog_337"),
								StringFromKey("pgg_dialog_338", pchar))));
			link.l1.go = "Quest_1_Ship_Detail_1";

			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				link.l2 = PCharRepPhrase(
							StringFromKey("pgg_dialog_342", RandPhraseSimple(
									StringFromKey("pgg_dialog_340", NationNameInstrumental(sti(PChar.GenQuest.PGG_Quest.Nation))),
									StringFromKey("pgg_dialog_341"))),
							StringFromKey("pgg_dialog_345", RandPhraseSimple(
									StringFromKey("pgg_dialog_343", NationNameInstrumental(sti(PChar.GenQuest.PGG_Quest.Nation))),
									StringFromKey("pgg_dialog_344", NationNameInstrumental(sti(PChar.GenQuest.PGG_Quest.Nation))))));
				link.l2.go = NPCharRepPhrase(NPChar, "Quest_1_Ship_BadWay", "Quest_1_Ship_Refuse");
			}
			else
			{
				Dialog.Text = StringFromKey("pgg_dialog_346");
				link.l1 = sTmp;
			}
			if (sti(PChar.GenQuest.PGG_Quest.Template))
			{
				AddQuestRecord("Gen_PGGQuest1", "q1_Detail_A");
			}
			else
			{
				AddQuestRecord("Gen_PGGQuest1", "q1_Detail_B");
			}
			AddQuestUserData("Gen_PGGQuest1", "sNation", NationNameGenitive(sti(PChar.GenQuest.PGG_Quest.Nation)));
			AddQuestUserData("Gen_PGGQuest1", "sGoods", PChar.GenQuest.PGG_Quest.Goods.Text);
			AddQuestUserData("Gen_PGGQuest1", "sColony", sLoc);
			AddQuestUserData("Gen_PGGQuest1", "sShore", GetConvertStr(PChar.GenQuest.PGG_Quest.Island.Shore, "LocLables.txt"));
		break;

		case "Quest_1_Ship_Detail_1":
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = PCharRepPhrase(
							StringFromKey("pgg_dialog_349", RandPhraseSimple(
									StringFromKey("pgg_dialog_347", FindDaysString(sti(PChar.GenQuest.PGG_Quest.Days))),
									StringFromKey("pgg_dialog_348", FindDaysString(sti(PChar.GenQuest.PGG_Quest.Days))))),
							StringFromKey("pgg_dialog_352", RandPhraseSimple(
									StringFromKey("pgg_dialog_350", FindDaysString(sti(PChar.GenQuest.PGG_Quest.Days))),
									StringFromKey("pgg_dialog_351", PChar.Name, FindDaysString(sti(PChar.GenQuest.PGG_Quest.Days))))));
				link.l1 = StringFromKey("pgg_dialog_355", RandPhraseSimple(
							StringFromKey("pgg_dialog_353"),
							StringFromKey("pgg_dialog_354")));
				link.l1.go = "Exit_Quest_1_Accept";
				AddQuestRecord("Gen_PGGQuest1", "q1_Accept");
			}
			else
			{
				Dialog.Text = StringFromKey("pgg_dialog_356");
				link.l1 = StringFromKey("pgg_dialog_357", FindDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
				link.l1.go = "Quest_1_Ship_Accept";
				AddQuestRecord("Gen_PGGQuest1", "q1_Accept_1");
			}
			AddQuestUserData("Gen_PGGQuest1", "nDays", FindDaysString(sti(PChar.GenQuest.PGG_Quest.Days)));
		break;

		case "Quest_1_Ship_Accept":
			Dialog.Text = StringFromKey("pgg_dialog_358");
			link.l1 = StringFromKey("pgg_dialog_359");
			link.l1.go = "Exit_Quest_1_Accept";
		break;

		case "Exit_Quest_1_Accept":
			if (sti(PChar.GenQuest.PGG_Quest.Stage) < 2)
			{
				PChar.GenQuest.PGG_Quest.Stage = 2;
				Group_SetAddress("PGGQuest", "None", "", "");
				Group_DelCharacter("PGGQuest", NPChar.id);
				DeleteAttribute(NPChar, "DeckDialogNode");

				if (sti(PChar.GenQuest.PGG_Quest.Template))
				{
					PGG_Q1PlaceShipsNearIsland();
				}
				else
				{
					Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = true;

					PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1 = "Location";
					PChar.Quest.PGGQuest1_CheckStartState.win_condition.l1.Location = PChar.GenQuest.PGG_Quest.Island.Shore;
					PChar.Quest.PGGQuest1_CheckStartState.function = "PGG_Q1CheckStartState";
				}
				PChar.Quest.PGGQuest1_PGGDead.win_condition.l1 = "NPC_Death";
				PChar.Quest.PGGQuest1_PGGDead.win_condition.l1.Character = PChar.GenQuest.PGG_Quest.PGGid;
				PChar.Quest.PGGQuest1_PGGDead.function = "PGG_Q1PGGDead";

				SetTimerCondition("PGGQuest1_Time2Late", 0, 0, sti(PChar.GenQuest.PGG_Quest.Days), false);
				PChar.Quest.PGGQuest1_Time2Late.function = "PGG_Q1Time2Late";

				NPChar.PGGAi.IsPGG = false;
				NPChar.PGGAi.location.town = "none";
				DeleteAttribute(NPChar, "PGGAi.Task");
				DeleteAttribute(NPChar, "PGGAi.LockService");
				DeleteAttribute(NPChar, "AlwaysFriend");

				SetCompanionIndex(PChar, -1, sti(NPChar.index));
				SetCharacterRemovable(NPChar, false);

				SetBaseShipData(NPChar);
				ShipOverhaul(NPChar);

				Fantom_SetCannons(NPChar, "pirate");
				Fantom_SetBalls(NPChar, "pirate");
			}
			NextDiag.CurrentNode = "Quest_1_Ship_Accept";
			DialogExit();
		break;

		case "Quest_1_Ship_Refuse":
			Dialog.Text = StringFromKey("pgg_dialog_362", RandSwear(), RandPhraseSimple(
						StringFromKey("pgg_dialog_360"),
						StringFromKey("pgg_dialog_361")));
			link.l1 = PCharRepPhrase(
						StringFromKey("pgg_dialog_365", RandPhraseSimple(
								StringFromKey("pgg_dialog_363"),
								StringFromKey("pgg_dialog_364"))),
						StringFromKey("pgg_dialog_368", RandPhraseSimple(
								StringFromKey("pgg_dialog_366"),
								StringFromKey("pgg_dialog_367"))));
			link.l1.go = "Exit_Quest_1_Refuse";
		break;

		case "Exit_Quest_1_Refuse":
			if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
			{
				PChar.GenQuest.PGG_Quest.Stage = -1;
				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromLocation";
				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1.Location = PChar.location;
				PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";

				AddQuestRecord("Gen_PGGQuest1", "q1_Close");
				AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("ся", "ась"));
				CloseQuestHeader("Gen_PGGQuest1");
				DeleteAttribute(NPChar, "AlwaysFriend");
			}
			NPChar.Dialog.CurrentNode = "Quest_1_Ship_Refuse";
			NPChar.DeckDialogNode = "Quest_1_Ship_Refuse";
			DialogExit();
		break;

		case "Quest_1_Ship_BadWay":
			Dialog.Text = PCharRepPhrase(
						StringFromKey("pgg_dialog_371", RandPhraseSimple(
								StringFromKey("pgg_dialog_369"),
								StringFromKey("pgg_dialog_370", pchar))),
						StringFromKey("pgg_dialog_374", RandPhraseSimple(
								StringFromKey("pgg_dialog_372"),
								StringFromKey("pgg_dialog_373"))));
			link.l1 = PCharRepPhrase(
						StringFromKey("pgg_dialog_377", RandSwear(), RandPhraseSimple(
								StringFromKey("pgg_dialog_375", GetFullName(PChar)),
								StringFromKey("pgg_dialog_376"))),
						StringFromKey("pgg_dialog_380", RandPhraseSimple(
								StringFromKey("pgg_dialog_378"),
								StringFromKey("pgg_dialog_379"))));
			link.l1.go = "Quest_1_Ship_BadWay_1";
		break;

		case "Quest_1_Ship_BadWay_1":
			Dialog.Text = StringFromKey("pgg_dialog_387", RandSwear()) + PCharRepPhrase(
						StringFromKey("pgg_dialog_383", RandPhraseSimple(
								StringFromKey("pgg_dialog_381", pchar),
								StringFromKey("pgg_dialog_382", pchar))),
						StringFromKey("pgg_dialog_386", RandPhraseSimple(
								StringFromKey("pgg_dialog_384"),
								StringFromKey("pgg_dialog_385"))));
			link.l1 = PCharRepPhrase(
						StringFromKey("pgg_dialog_390", RandPhraseSimple(
								StringFromKey("pgg_dialog_388", GetFullName(NPChar)),
								StringFromKey("pgg_dialog_389"))),
						StringFromKey("pgg_dialog_393", RandPhraseSimple(
								StringFromKey("pgg_dialog_391"),
								StringFromKey("pgg_dialog_392"))));
			link.l1.go = "Exit_Quest_1_DeckFight";
		break;

		case "Exit_Quest_1_DeckFight":
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			DeleteAttribute(NPChar, "AlwaysFriend");
			sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
			LAi_SetImmortal(NPChar, true);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", sTmp, "none", "", "", "", 5.0);

			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			//группа может быть занята, а проверок по группам у нас нет...
			if (!CheckAttribute(pchar, "questTemp.PGGContra.Know"))
			{
				sTmp = "PGGTmp";
			}
			else
			{
				sTmp = "PGGQst";
			}
			PChar.GenQuest.PGG_Quest.GrpID = sTmp;

			for (i = 1; i < 5; i++)
			{
				sld = CharacterFromID("saylor_0" + i);
				LAi_group_MoveCharacter(sld, sTmp);
			}
			LAi_group_FightGroups(LAI_GROUP_PLAYER, sTmp, true);
			LAi_group_SetCheck(sTmp, "PGG_Q1AfterDeckFight");
			chrDisableReloadToLocation = true;

			PGG_ChangeRelation2MainCharacter(NPChar, -20);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetFightMode(pchar, true);
		break;

		case "Quest_1_Time2Late":
			chrDisableReloadToLocation = false;
			LAi_LockFightMode(pchar, false);

			//перенес сюда.. х.з. вроде будет лучше (Баг Изгоя.)
			PChar.Quest.PGGQuest1_PGGDead.Over = "Yes";
			PChar.Quest.PGGQuest1_GroupDead.Over = "Yes";
			PChar.Quest.PGGQuest1_CheckStartState.Over = "Yes";

			Dialog.Text = PCharRepPhrase(
						StringFromKey("pgg_dialog_396", RandPhraseSimple(
								StringFromKey("pgg_dialog_394", GetFullName(PChar)),
								StringFromKey("pgg_dialog_395", npchar, GetFullName(PChar)))),
						StringFromKey("pgg_dialog_399", RandPhraseSimple(
								StringFromKey("pgg_dialog_397", GetFullName(PChar)),
								StringFromKey("pgg_dialog_398"))));
			link.l1 = PCharRepPhrase(
						StringFromKey("pgg_dialog_402", RandPhraseSimple(
								StringFromKey("pgg_dialog_400"),
								StringFromKey("pgg_dialog_401"))),
						StringFromKey("pgg_dialog_405", RandPhraseSimple(
								StringFromKey("pgg_dialog_403"),
								StringFromKey("pgg_dialog_404"))));
			link.l1.go = "Exit_Quest_1_2Late";

			AddQuestRecord("Gen_PGGQuest1", "q1_Time2Late");
			CloseQuestHeader("Gen_PGGQuest1");
		break;

		case "Exit_Quest_1_2Late":
			LAi_SetPlayerType(PChar);
			if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
			{
				PChar.GenQuest.PGG_Quest.Stage = -1;
				RemoveCharacterCompanion(pchar, NPChar);

				NPChar.PGGAi.IsPGG = true;
				NPChar.RebirthPhantom = true;

				LAi_SetWarriorTypeNoGroup(NPChar);
				LAi_group_MoveCharacter(NPChar, "GroupDeck");

				PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromLocation";
				PChar.Quest.PGGQuest1_Clear.win_condition.l1.Location = PChar.location;
				if (PChar.location == "Ship_deck")
				{
					/*				PChar.Quest.PGGQuest1_RemoveShip.win_condition.l1 = "ExitFromSea";
									PChar.Quest.PGGQuest1_RemoveShip.function = "PGG_Q1RemoveShip";
									PChar.Quest.PGGQuest1_Clear.win_condition.l1 = "ExitFromSea";
					*/                PChar.quest.Munity = "Deads";
				}
				PChar.Quest.PGGQuest1_Clear.function = "PGG_Q1EndClear";
			}
			NextDiag.CurrentNode = "Quest_1_Failed";
			DialogExit();
		break;

		case "Quest_1_CheckResult":
			if (PChar.location == PChar.GenQuest.PGG_Quest.Island.Shore)
			{
				Locations[FindLocation(PChar.GenQuest.PGG_Quest.Island.Shore)].DisableEncounters = false;
			}
			else
			{
				PChar.quest.Munity = "Deads";
			}
			chrDisableReloadToLocation = false;
			LAi_LockFightMode(pchar, false);

			//не взяли груз...
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				PChar.GenQuest.PGG_Quest.FailedPaySum = sti(PChar.GenQuest.PGG_Quest.Days) * 10000;
				//			Dialog.Text = "Н-да, связался я с тобой. Всё погубил" + GetSexPhrase("","а") + ". Ты теперь мне долж" + GetSexPhrase("ен","на") + " неустойку в размере " + FindMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)) + ".";
				Dialog.Text = PCharRepPhrase(
							StringFromKey("pgg_dialog_408", RandPhraseSimple(
									StringFromKey("pgg_dialog_406", pchar, FindMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))),
									StringFromKey("pgg_dialog_407", pchar, FindMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))))),
							StringFromKey("pgg_dialog_411", RandPhraseSimple(
									StringFromKey("pgg_dialog_409", FindMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))),
									StringFromKey("pgg_dialog_410", FindMoneyString(sti(PChar.GenQuest.PGG_Quest.FailedPaySum))))));
				link.l1 = PCharRepPhrase(
							StringFromKey("pgg_dialog_414", RandPhraseSimple(
									StringFromKey("pgg_dialog_412", npchar),
									StringFromKey("pgg_dialog_413", npchar))),
							StringFromKey("pgg_dialog_417", RandPhraseSimple(
									StringFromKey("pgg_dialog_415"),
									StringFromKey("pgg_dialog_416"))));
				link.l1.go = "Quest_1_NotPay";
				if (sti(pchar.money) >= sti(PChar.GenQuest.PGG_Quest.FailedPaySum))
				{
					link.l2 = PCharRepPhrase(
								StringFromKey("pgg_dialog_420", RandPhraseSimple(
										StringFromKey("pgg_dialog_418"),
										StringFromKey("pgg_dialog_419", pchar))),
								StringFromKey("pgg_dialog_423", RandPhraseSimple(
										StringFromKey("pgg_dialog_421"),
										StringFromKey("pgg_dialog_422", pchar))));
					link.l2.go = "Exit_Quest_1_Failed";
				}
			}
			else
			{
				PChar.GenQuest.PGG_Quest.Stage = -1;
				Dialog.Text = StringFromKey("pgg_dialog_424", npchar, pchar);
				link.l1 = StringFromKey("pgg_dialog_425", npchar);
				link.l1.go = "Exit_Quest_1_Failed";
			}

			//минимум треть если взял, то гуд!
			if (sti(PChar.GenQuest.PGG_Quest.Goods.Taken) > MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Qty) / 3))
			{
				PChar.GenQuest.PGG_Quest.Ok = 1;
				Dialog.Text = PCharRepPhrase(
							StringFromKey("pgg_dialog_426", PChar.GenQuest.PGG_Quest.Goods.Taken, PChar.GenQuest.PGG_Quest.Goods.Text),
							StringFromKey("pgg_dialog_427", PChar.GenQuest.PGG_Quest.Goods.Taken, PChar.GenQuest.PGG_Quest.Goods.Text));
				i = sti(PChar.GenQuest.PGG_Quest.Parts);
				PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
				if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
				{
					Dialog.Text = StringFromKey("pgg_dialog_430", Dialog.Text) + " " + PCharRepPhrase(
								StringFromKey("pgg_dialog_428"),
								StringFromKey("pgg_dialog_429"));
				}
				else
				{
					Dialog.Text = StringFromKey("pgg_dialog_431", Dialog.Text);
				}
				Dialog.Text = Dialog.Text + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
				link.l1 = PCharRepPhrase(
							StringFromKey("pgg_dialog_434", RandPhraseSimple(
									StringFromKey("pgg_dialog_432"),
									StringFromKey("pgg_dialog_433"))),
							StringFromKey("pgg_dialog_437", RandPhraseSimple(
									StringFromKey("pgg_dialog_435", pchar),
									StringFromKey("pgg_dialog_436"))));
				link.l1.go = "Exit_Quest_1_End";
				link.l2 = PCharRepPhrase(
							StringFromKey("pgg_dialog_440", RandPhraseSimple(
									StringFromKey("pgg_dialog_438"),
									StringFromKey("pgg_dialog_439"))),
							StringFromKey("pgg_dialog_443", RandPhraseSimple(
									StringFromKey("pgg_dialog_441"),
									StringFromKey("pgg_dialog_442"))));
				link.l2.go = "Quest_1_NotPay";
			}
			else
			{
				AddQuestRecord("Gen_PGGQuest1", "q1_Fail");
			}
		break;

		case "Quest_1_NotPay":
			Dialog.Text = PCharRepPhrase(
						StringFromKey("pgg_dialog_446", RandPhraseSimple(
								StringFromKey("pgg_dialog_444"),
								StringFromKey("pgg_dialog_445"))),
						StringFromKey("pgg_dialog_449", RandPhraseSimple(
								StringFromKey("pgg_dialog_447"),
								StringFromKey("pgg_dialog_448"))));
			link.l1 = PCharRepPhrase(
						StringFromKey("pgg_dialog_452", RandPhraseSimple(
								StringFromKey("pgg_dialog_450"),
								StringFromKey("pgg_dialog_451"))),
						StringFromKey("pgg_dialog_455", RandPhraseSimple(
								StringFromKey("pgg_dialog_453"),
								StringFromKey("pgg_dialog_454"))));
			link.l1.go = "Exit_Quest_1_Failed";
			PChar.GenQuest.PGG_Quest.Stage = -1;

			bOk = makeint(NPChar.reputation) < 41 && PGG_ChangeRelation2MainCharacter(NPChar, 0) < 75;
			if (bOk || CheckAttribute(PChar, "GenQuest.PGG_Quest.Ok"))
			{
				PChar.GenQuest.PGG_Quest.Stage = 4;
				Dialog.Text = PCharRepPhrase(
							StringFromKey("pgg_dialog_458", RandPhraseSimple(
									StringFromKey("pgg_dialog_456", pchar),
									StringFromKey("pgg_dialog_457"))),
							StringFromKey("pgg_dialog_461", RandPhraseSimple(
									StringFromKey("pgg_dialog_459"),
									StringFromKey("pgg_dialog_460", GetFullName(PChar)))));
				link.l1 = PCharRepPhrase(
							StringFromKey("pgg_dialog_464", RandPhraseSimple(
									StringFromKey("pgg_dialog_462"),
									StringFromKey("pgg_dialog_463", GetFullName(PChar)))),
							StringFromKey("pgg_dialog_467", RandPhraseSimple(
									StringFromKey("pgg_dialog_465"),
									StringFromKey("pgg_dialog_466"))));
				link.l1.go = "Exit_Quest_1_FailedFight";
			}
		break;

		case "Exit_Quest_1_Failed":
			if (sti(PChar.GenQuest.PGG_Quest.Stage) != -1)
			{
				sld = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
				AddMoneyToCharacter(PChar, -(sti(PChar.GenQuest.PGG_Quest.FailedPaySum)));
				AddQuestRecord("Gen_PGGQuest1", "q1_FailPay");
				AddQuestUserData("Gen_PGGQuest1", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("Gen_PGGQuest1", "sSex1", GetSexPhrase("ен", "на"));
				AddQuestUserData("Gen_PGGQuest1", "sPsName", GetFullName(sld));
			}
			CloseQuestHeader("Gen_PGGQuest1");
			RemoveCharacterCompanion(pchar, NPChar);

			if (PChar.Location == "Ship_deck")
			{
				PChar.Quest.PGGQuest1_FailedExitSea.win_condition.l1 = "ExitFromSea";
				PChar.Quest.PGGQuest1_FailedExitSea.function = "PGG_Q1EndClear";
			}
			else
			{
				PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1 = "ExitFromLocation";
				PChar.Quest.PGGQuest1_FailedExitLoc.win_condition.l1.Location = PChar.location;
				PChar.Quest.PGGQuest1_FailedExitLoc.function = "PGG_Q1EndClear";
			}
			PGG_ChangeRelation2MainCharacter(NPChar, -5);

			LAi_SetImmortal(NPChar, true);
			//что б не били сопровождение.
			for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
			{
				sld = CharacterFromID("pirate_" + i);
				LAi_SetImmortal(sld, true);
			}

			NextDiag.CurrentNode = "Quest_1_Failed";
			DialogExit();
			if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Quest_1_Failed":
			Dialog.Text = StringFromKey("pgg_dialog_468");
			link.l1 = StringFromKey("pgg_dialog_469");
			link.l1.go = "Exit";
			NextDiag.TempNode = "Quest_1_Failed";
		break;

		case "Quest_1_End":
			Dialog.Text = StringFromKey("pgg_dialog_470");
			link.l1 = StringFromKey("pgg_dialog_471");
			link.l1.go = "Exit";
			NextDiag.TempNode = "Quest_1_End";
		break;

		case "Exit_Quest_1_FailedFight":
			RemoveCharacterCompanion(pchar, NPChar);

			LAi_LockFightMode(pchar, false);
			LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
			LAi_group_SetRelation("PGGTmp", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
			LAi_group_SetCheck("PGGTmp", "PGG_Q1AfterDeckFight");

			PChar.GenQuest.PGG_Quest.GrpID = "PGGTmp";
			chrDisableReloadToLocation = true;

			Group_DeleteGroup("PGGQuest");
			Group_AddCharacter("PGGQuest", NPChar.id);
			Group_SetGroupCommander("PGGQuest", NPChar.id);
			Group_SetAddress("PGGQuest", PChar.GenQuest.PGG_Quest.GrpLocation, "Quest_Ships", PChar.GenQuest.PGG_Quest.GrpLoc);
			Group_SetTaskNone("PGGQuest");

			PGG_ChangeRelation2MainCharacter(NPChar, -15);

			GetCharacterPos(NPChar, &locx, &locy, &locz);
			sTmp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
			NextDiag.CurrentNode = "Second Time";
			DialogExit();

			Log_TestInfo("go to loc " + sTmp + " " + NPChar.location);
			NPChar.location = PChar.location;
			if (PChar.location != "Ship_Deck") sTmp = "reload1";
			if (PChar.location != "Ship_Deck")sTmp = "reload1";

			PChar.questTemp.Chr2Remove = NPChar.id;
			LAi_ActorRunToLocator(NPChar, "reload", sTmp, "RemoveCharacterFromLocation", -1.0);

			LAi_SetImmortal(NPChar, true);
			LAi_SetFightMode(pchar, true);
		break;

		case "Exit_Quest_1_End":
			RemoveCharacterCompanion(PChar, NPChar);

			i = sti(PChar.GenQuest.PGG_Quest.Goods.Part);
			/*		i *= (sti(PChar.GenQuest.PGG_Quest.Parts)-1);
					i += sti(PChar.GenQuest.PGG_Quest.StartGoods);
					n = GetCompanionQuantity(PChar);
					SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
					for (i = 1; i < n; i++)
					{
						iRnd = GetCompanionIndex(PChar, i);
						if (iRnd != -1)
						{
							sld = GetCharacter(iRnd);
							if (GetRemovable(sld))
							{
								Log_TestInfo(sld.id);
								SetCharacterGoods(sld, sti(PChar.GenQuest.PGG_Quest.Goods), 0);
							}
						}
					}
			*/
			RemoveCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), i);
			/*		if (PChar.Location == "Ship_deck")
					{
						PChar.Quest.PGGQuest1_EndExitSea.win_condition.l1 = "ExitFromSea";
						PChar.Quest.PGGQuest1_EndExitSea.function = "PGG_Q1EndClear";
					}
					else
					{*/
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PGGQuest1_EndExitLoc.win_condition.l1.Location = PChar.location;
			PChar.Quest.PGGQuest1_EndExitLoc.function = "PGG_Q1EndClear";
			//}
			AddQuestRecord("Gen_PGGQuest1", "q1_OkShare");
			CloseQuestHeader("Gen_PGGQuest1");

			//что б не били сопровождение.
			for (i = 1; i < sti(PChar.GenQuest.PGG_Quest.GrpID.Qty); i++)
			{
				sld = CharacterFromID("pirate_" + i);
				LAi_SetImmortal(sld, true);
			}

			LAi_SetImmortal(NPChar, true);
			NextDiag.CurrentNode = "Quest_1_End";
			DialogExit();
			LAi_SetWarriorType(NPChar); // сброс группы ГГ
			LAi_group_MoveCharacter(NPChar, LAI_GROUP_PLAYER);
		break;

		case "Quest_1_SharePrise":
			chrDisableReloadToLocation = false;
			Dialog.Text = PCharRepPhrase(
						StringFromKey("pgg_dialog_472", PChar.GenQuest.PGG_Quest.Goods.Taken, PChar.GenQuest.PGG_Quest.Goods.Text),
						StringFromKey("pgg_dialog_473", PChar.GenQuest.PGG_Quest.Goods.Taken, PChar.GenQuest.PGG_Quest.Goods.Text));

			i = sti(PChar.GenQuest.PGG_Quest.Parts);
			PChar.GenQuest.PGG_Quest.Goods.Part = MakeInt(sti(PChar.GenQuest.PGG_Quest.Goods.Taken) / i);
			SetCharacterGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods), sti(PChar.GenQuest.PGG_Quest.Goods.Taken) + GetCargoGoods(PChar, sti(PChar.GenQuest.PGG_Quest.Goods)));
			if (CheckAttribute(NPChar, "PGGAi.ActiveQuest"))
			{
				Dialog.Text = StringFromKey("pgg_dialog_474", Dialog.Text);
			}
			else
			{
				Dialog.Text = StringFromKey("pgg_dialog_475", Dialog.Text);
			}
			Dialog.Text = Dialog.Text + " " + PChar.GenQuest.PGG_Quest.Goods.Part + ".";
			link.l1 = PCharRepPhrase(
						StringFromKey("pgg_dialog_478", RandPhraseSimple(
								StringFromKey("pgg_dialog_476"),
								StringFromKey("pgg_dialog_477"))),
						StringFromKey("pgg_dialog_481", RandPhraseSimple(
								StringFromKey("pgg_dialog_479", pchar),
								StringFromKey("pgg_dialog_480"))));
			link.l1.go = "Exit_Quest_1_End";
		break;
		//===================================
		//              Exits
		//===================================
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Exit_2":
			if (CheckAttribute(pchar, "GenQuest.PGG_Quest")) DeleteAttribute(pchar, "GenQuest.PGG_Quest"); //fix
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			if (NPChar.Chr_Ai.Type == "actor") LAi_SetWarriorTypeNoGroup(NPChar);
		break;

		case "Exit_Smugglers_Fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			LAi_group_FightGroups(LAI_GROUP_PLAYER, "PGGTmp", true);
			LAi_SetFightMode(pchar, true);
		break;

		case "Exit_ShowParam":
			NextDiag.CurrentNode = "Second Time";
			//		NPChar.quest.meeting = true;
			DialogExit();
			LaunchCharacter(NPChar);
		break;
	}
}

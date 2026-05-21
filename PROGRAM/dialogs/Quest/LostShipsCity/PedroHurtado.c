#include "DIALOGS\Rumours\Simple_rumors.c"
#include "DIALOGS\Quest\LostShipsCity\SeekLSCCitizen_CN.c"

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iMoney;
	string sMoney, sTotalTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	ProcessDialog_SeekLSCCitizenCN(NPChar, Link, NextDiag);

	string NodeName = Dialog.CurrentNode;
	string NodePrevName = "";
	if (CheckAttribute(NextDiag, "PrevNode")) NodePrevName = NextDiag.PrevNode;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = StringFromKey("PedroHurtado_1", pchar, GetFullName(npchar));
					link.l1 = StringFromKey("PedroHurtado_2", GetFullName(pchar));
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("PedroHurtado_3", GetFullName(npchar));
					link.l1 = StringFromKey("PedroHurtado_4", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
			}
			else
			{
				//квест проникновения в дом хозяина магазина			
				if (pchar.questTemp.LSC != "AdmiralIsWaiting" && !CheckAttribute(npchar, "quest.store"))
				{
					dialog.text = StringFromKey("PedroHurtado_5", pchar);
					link.l1 = StringFromKey("PedroHurtado_6");
					link.l1.go = "StBegin_1";
					break;
				}
				// --> пей до дна
				if (pchar.questTemp.LSC == "waitInterceptionResult" && !CheckAttribute(npchar, "quest.drink"))
				{
					dialog.text = StringFromKey("PedroHurtado_7", pchar);
					link.l1 = StringFromKey("PedroHurtado_8");
					link.l1.go = "drink";
					break;
				}
				// <-- пей до дна
				// <-- квесты
				dialog.text = StringFromKey("PedroHurtado_9", pchar);
				link.l1 = StringFromKey("PedroHurtado_10");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("PedroHurtado_11");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("PedroHurtado_15", LinkRandPhrase(
							StringFromKey("PedroHurtado_12"),
							StringFromKey("PedroHurtado_13"),
							StringFromKey("PedroHurtado_14", pchar)));
				link.l3.go = "rumours_LSC";
				if (CheckAttribute(npchar, "quest.store") && npchar.quest.store == "waiting" && npchar.chr_ai.type == LAI_TYPE_STAY)
				{
					link.l4 = StringFromKey("PedroHurtado_16", pchar);
					link.l4.go = "StStart_1";
				}
				//поиск товаров на корвет
				if (pchar.questTemp.LSC == "toSeekGoods")
				{
					link.l8 = StringFromKey("PedroHurtado_17");
					link.l8.go = "SeekGoods";
				}
				//подсказка
				if (pchar.questTemp.LSC == "toKillOneNarval" && !CheckAttribute(npchar, "quest.goToVelasco"))
				{
					link.l8 = StringFromKey("PedroHurtado_18");
					link.l8.go = "goToVelasco";
				}
				//поиски команды на корвет
				if (CheckAttribute(pchar, "questTemp.LSC.crew"))
				{
					if (pchar.questTemp.LSC == "toSeekCrewInTavern") dialog.text = StringFromKey("PedroHurtado_19"); //сбор в таверне
					link.l8 = StringFromKey("PedroHurtado_20");
					link.l8.go = "SeekCrew";
				}
				link.l10 = StringFromKey("PedroHurtado_21");
				link.l10.go = "exit";
			}
		break;

		case "FS_1":
			dialog.text = StringFromKey("PedroHurtado_22", pchar);
			link.l1 = StringFromKey("PedroHurtado_23");
			link.l1.go = "exit";
		break;
		case "FT_1":
			dialog.text = StringFromKey("PedroHurtado_24");
			link.l1 = StringFromKey("PedroHurtado_25");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = StringFromKey("PedroHurtado_29", LinkRandPhrase(
						StringFromKey("PedroHurtado_26", pchar),
						StringFromKey("PedroHurtado_27", pchar),
						StringFromKey("PedroHurtado_28", pchar)));
			link.l1 = StringFromKey("PedroHurtado_30");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("PedroHurtado_31");
			link.l1 = StringFromKey("PedroHurtado_32");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("PedroHurtado_36", LinkRandPhrase(
						StringFromKey("PedroHurtado_33"),
						StringFromKey("PedroHurtado_34"),
						StringFromKey("PedroHurtado_35", pchar)));
			link.l1 = StringFromKey("PedroHurtado_40", LinkRandPhrase(
						StringFromKey("PedroHurtado_37"),
						StringFromKey("PedroHurtado_38"),
						StringFromKey("PedroHurtado_39")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("PedroHurtado_41", npchar);
				link.l1 = StringFromKey("PedroHurtado_45", LinkRandPhrase(
							StringFromKey("PedroHurtado_42"),
							StringFromKey("PedroHurtado_43"),
							StringFromKey("PedroHurtado_44")));
			}
			else
			{
				dialog.text = StringFromKey("PedroHurtado_46", npchar);
				link.l1 = StringFromKey("PedroHurtado_49", RandPhraseSimple(
							StringFromKey("PedroHurtado_47", pchar),
							StringFromKey("PedroHurtado_48")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("PedroHurtado_50");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("PedroHurtado_51");
				Link.l1 = StringFromKey("PedroHurtado_52");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("PedroHurtado_53", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("PedroHurtado_54");
					link.l1 = StringFromKey("PedroHurtado_55", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("PedroHurtado_56", GetFullName(sld));
					Link.l1 = StringFromKey("PedroHurtado_57");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("PedroHurtado_58");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("PedroHurtado_59", GetFullName(sld));
					Link.l1 = StringFromKey("PedroHurtado_60");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("PedroHurtado_61");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("PedroHurtado_62");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("PedroHurtado_63");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;

		case "SeekCitizen_agree":
			sld = &characters[sti(npchar.quest.seekIdx)];
			npchar.quest.seekIdx.where = WhereLSCCitizen(sld);
			if (npchar.quest.seekIdx.where == "none")
			{
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("PedroHurtado_67", LinkRandPhrase(
								StringFromKey("PedroHurtado_64"),
								StringFromKey("PedroHurtado_65"),
								StringFromKey("PedroHurtado_66")));
					link.l1 = StringFromKey("PedroHurtado_70", RandPhraseSimple(
								StringFromKey("PedroHurtado_68"),
								StringFromKey("PedroHurtado_69")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("PedroHurtado_74", LinkRandPhrase(
								StringFromKey("PedroHurtado_71"),
								StringFromKey("PedroHurtado_72"),
								StringFromKey("PedroHurtado_73")));
					link.l1 = StringFromKey("PedroHurtado_77", RandPhraseSimple(
								StringFromKey("PedroHurtado_75"),
								StringFromKey("PedroHurtado_76")));
					link.l1.go = "exit";
				}
			}
			else
			{
				if (sld.sex == "man")
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str1 = npchar.location.locator;
						string Str2 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str1, 0, 5) == strcut(Str2, 0, 5))
						{
							dialog.text = StringFromKey("PedroHurtado_81", LinkRandPhrase(
										StringFromKey("PedroHurtado_78"),
										StringFromKey("PedroHurtado_79"),
										StringFromKey("PedroHurtado_80", pchar)));
						}
						else
						{
							dialog.text = StringFromKey("PedroHurtado_85", LinkRandPhrase(
										StringFromKey("PedroHurtado_82", npchar.quest.seekIdx.where),
										StringFromKey("PedroHurtado_83", npchar.quest.seekIdx.where),
										StringFromKey("PedroHurtado_84", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("PedroHurtado_89", LinkRandPhrase(
										StringFromKey("PedroHurtado_86", npchar.quest.seekIdx.where),
										StringFromKey("PedroHurtado_87"),
										StringFromKey("PedroHurtado_88")));
						}
						else
						{
							dialog.text = StringFromKey("PedroHurtado_93", LinkRandPhrase(
										StringFromKey("PedroHurtado_90", npchar.quest.seekIdx.where),
										StringFromKey("PedroHurtado_91", npchar.quest.seekIdx.where),
										StringFromKey("PedroHurtado_92", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("PedroHurtado_96", RandPhraseSimple(
								StringFromKey("PedroHurtado_94"),
								StringFromKey("PedroHurtado_95")));
					link.l1.go = "exit";
				}
				else
				{
					if (sld.location == "LostShipsCity_town")
					{
						string Str3 = npchar.location.locator;
						string Str4 = sld.location.locator;
						if (npchar.location == sld.location && strcut(Str3, 0, 5) == strcut(Str4, 0, 5))
						{
							dialog.text = StringFromKey("PedroHurtado_100", LinkRandPhrase(
										StringFromKey("PedroHurtado_97"),
										StringFromKey("PedroHurtado_98"),
										StringFromKey("PedroHurtado_99", pchar)));
						}
						else
						{
							dialog.text = StringFromKey("PedroHurtado_104", LinkRandPhrase(
										StringFromKey("PedroHurtado_101", npchar.quest.seekIdx.where),
										StringFromKey("PedroHurtado_102", npchar.quest.seekIdx.where),
										StringFromKey("PedroHurtado_103", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("PedroHurtado_108", LinkRandPhrase(
										StringFromKey("PedroHurtado_105", npchar.quest.seekIdx.where),
										StringFromKey("PedroHurtado_106"),
										StringFromKey("PedroHurtado_107")));
						}
						else
						{
							dialog.text = StringFromKey("PedroHurtado_112", LinkRandPhrase(
										StringFromKey("PedroHurtado_109", npchar.quest.seekIdx.where),
										StringFromKey("PedroHurtado_110", npchar.quest.seekIdx.where),
										StringFromKey("PedroHurtado_111", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("PedroHurtado_115", RandPhraseSimple(
								StringFromKey("PedroHurtado_113"),
								StringFromKey("PedroHurtado_114")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("PedroHurtado_116");
			if (!CheckAttribute(NextDiag, NodeName + ".l5"))
			{
				link.l5 = StringFromKey("PedroHurtado_117");
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("PedroHurtado_118");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("PedroHurtado_119");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("PedroHurtado_120");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4"))
			{
				link.l4 = StringFromKey("PedroHurtado_121", pchar);
				link.l4.go = "ansewer_4";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l6") && pchar.questTemp.LSC == "toSeekOldCitizen")
			{
				link.l6 = StringFromKey("PedroHurtado_122");
				link.l6.go = "ansewer_6";
			}
			link.l10 = StringFromKey("PedroHurtado_123");
			link.l10.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = StringFromKey("PedroHurtado_124", pchar);
			if (pchar.questTemp.LSC == "AdmiralIsWaiting") link.l1 = StringFromKey("PedroHurtado_125");
			else link.l1 = StringFromKey("PedroHurtado_126");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("PedroHurtado_127", pchar);
			link.l1 = StringFromKey("PedroHurtado_128");
			link.l1.go = "ansewer_1_1";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_1_1":
			dialog.text = StringFromKey("PedroHurtado_129");
			link.l1 = StringFromKey("PedroHurtado_130");
			link.l1.go = "ansewer_1_2";
		break;
		case "ansewer_1_2":
			dialog.text = StringFromKey("PedroHurtado_131");
			link.l1 = StringFromKey("PedroHurtado_132");
			link.l1.go = "ansewer_1_3";
		break;
		case "ansewer_1_3":
			dialog.text = StringFromKey("PedroHurtado_133", pchar);
			link.l1 = StringFromKey("PedroHurtado_134");
			link.l1.go = "int_quests";
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("PedroHurtado_135", pchar);
			link.l1 = StringFromKey("PedroHurtado_136");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("PedroHurtado_137", pchar);
			link.l1 = StringFromKey("PedroHurtado_138");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("PedroHurtado_139", pchar);
			link.l1 = StringFromKey("PedroHurtado_140");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l4 = true;
		break;
		case "ansewer_6":
			dialog.text = StringFromKey("PedroHurtado_141");
			link.l1 = StringFromKey("PedroHurtado_142");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l6 = true;
		break;
		//квест проникновения в кабинет хозяина магазина
		case "StBegin_1":
			dialog.text = StringFromKey("PedroHurtado_143");
			link.l1 = StringFromKey("PedroHurtado_144");
			link.l1.go = "StBegin_2";
		break;
		case "StBegin_2":
			dialog.text = StringFromKey("PedroHurtado_145");
			link.l1 = StringFromKey("PedroHurtado_146");
			link.l1.go = "StBegin_3";
		break;
		case "StBegin_3":
			dialog.text = StringFromKey("PedroHurtado_147");
			link.l1 = StringFromKey("PedroHurtado_148");
			link.l1.go = "StBegin_4";
		break;
		case "StBegin_4":
			dialog.text = StringFromKey("PedroHurtado_149");
			link.l1 = StringFromKey("PedroHurtado_150");
			link.l1.go = "StBegin_5";
		break;
		case "StBegin_5":
			dialog.text = StringFromKey("PedroHurtado_151", pchar);
			link.l1 = StringFromKey("PedroHurtado_152");
			link.l1.go = "StBegin_6";
			link.l2 = StringFromKey("PedroHurtado_153");
			link.l2.go = "StBegin_not";
		break;
		case "StBegin_not":
			dialog.text = StringFromKey("PedroHurtado_154", pchar);
			link.l1 = StringFromKey("PedroHurtado_155");
			link.l1.go = "exit";
			npchar.quest.store = "cancel";
			pchar.questTemp.LSC.takeStoreMoney = "over";
			CloseQuestHeader("ISS_takeStoreMoney");
			RemoveLandQuestMark_Main(npchar, "ISS_takeStoreMoney");
			LSC_CheckReadyMainLine(); //проверка все ли готово для продолжения основной линейки
		break;
		case "StBegin_6":
			dialog.text = StringFromKey("PedroHurtado_156", pchar);
			link.l1 = StringFromKey("PedroHurtado_157");
			link.l1.go = "exit";
			pchar.quest.LCS_SetPedroHurtado.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LCS_SetPedroHurtado.win_condition.l1.location = pchar.location;
			pchar.quest.LCS_SetPedroHurtado.function = "LCS_SetPedroHurtado";
			npchar.quest.store = "waiting";
			AddQuestRecord("ISS_takeStoreMoney", "1");
			RemoveLandQuestMark_Main(npchar, "ISS_takeStoreMoney");
		break;
		case "StStart_1":
			dialog.text = StringFromKey("PedroHurtado_158");
			link.l1 = StringFromKey("PedroHurtado_159");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_PedroRunOpenDoor");
		break;
		case "StStart_Opened":
			dialog.text = StringFromKey("PedroHurtado_160");
			link.l1 = StringFromKey("PedroHurtado_161");
			link.l1.go = "StStart_3";
		break;
		case "StStart_3":
			dialog.text = StringFromKey("PedroHurtado_162");
			link.l1 = StringFromKey("PedroHurtado_163");
			link.l1.go = "exit";
			NextDiag.TempNode = "StResult";
			npchar.quest.store.money = pchar.money;
			AddQuestRecord("ISS_takeStoreMoney", "2");
			AddQuestUserData("ISS_takeStoreMoney", "sSex", GetSexPhrase("ся", "ась"));
			AddDialogExitQuestFunction("LSC_PedroGoWaiting");
			RemoveLandQuestMark_Main(npchar, "ISS_takeStoreMoney");
		break;
		case "StResult":
			dialog.text = StringFromKey("PedroHurtado_164", pchar);
			link.l1 = StringFromKey("PedroHurtado_165", pchar);
			link.l1.go = "StResult_1";
			npchar.location.group = "goto";
			npchar.location.locator = "goto06_1";
		break;
		case "StResult_1":
			dialog.text = StringFromKey("PedroHurtado_166", pchar);
			if (sti(pchar.money) <= sti(npchar.quest.store.money))
			{
				link.l1 = StringFromKey("PedroHurtado_167", pchar);
				link.l1.go = "StResult_2";
			}
			else
			{
				npchar.quest.store.money = sti(pchar.money) - sti(npchar.quest.store.money); //чистая выручка
				link.l1 = StringFromKey("PedroHurtado_168", pchar, FindMoneyString(sti(npchar.quest.store.money)));
				link.l1.go = "StResult_3";
			}
		break;
		case "StResult_2":
			dialog.text = StringFromKey("PedroHurtado_169");
			link.l1 = StringFromKey("PedroHurtado_170");
			link.l1.go = "StResult_4";
			npchar.quest.store = "fail"; //флаг этого миниквеста
			AddQuestRecord("ISS_takeStoreMoney", "3");
			AddQuestUserData("ISS_takeStoreMoney", "sSex", GetSexPhrase("ёл", "ла"));
		break;
		case "StResult_3":
			dialog.text = StringFromKey("PedroHurtado_171", pchar);
			link.l1 = StringFromKey("PedroHurtado_172");
			link.l1.go = "StResult_4";
			npchar.quest.store = "over"; //флаг этого миниквеста
			AddMoneyToCharacter(pchar, -makeint(sti(npchar.quest.store.money) / 2));
			AddQuestRecord("ISS_takeStoreMoney", "4");
		break;
		case "StResult_4":
			CloseQuestHeader("ISS_takeStoreMoney");
			npchar.cityTape = "citizen";
			pchar.questTemp.LSC.takeStoreMoney = "over";
			RemoveLandQuestMark_Main(npchar, "ISS_takeStoreMoney");
			LAi_SetLoginTime(npchar, 6.0, 21.99);
			LAi_SetLSCoutType(npchar);
			LAi_group_MoveCharacter(npchar, "TmpEnemy");
			LAI_TYPE_LSCout_Goto(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "location");
			LSC_CheckReadyMainLine(); //проверка все ли готово для продолжения основной линейки
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// --> пей до дна
		case "drink":
			dialog.text = StringFromKey("PedroHurtado_173");
			if (CheckAttribute(npchar, "quest.store") && npchar.quest.store != "cancel") dialog.text = StringFromKey("PedroHurtado_174");
			link.l1 = StringFromKey("PedroHurtado_175");
			link.l1.go = "drink_1";
			npchar.quest.drink = "true";
		break;

		case "drink_1":
			dialog.text = StringFromKey("PedroHurtado_176", pchar);
			link.l1 = StringFromKey("PedroHurtado_177");
			link.l1.go = "drink_2";
		break;

		case "drink_2":
			dialog.text = StringFromKey("PedroHurtado_178");
			link.l1 = StringFromKey("PedroHurtado_179");
			link.l1.go = "drink_3";
		break;

		case "drink_3":
			dialog.text = StringFromKey("PedroHurtado_180", pchar);
			link.l1 = StringFromKey("PedroHurtado_181");
			link.l1.go = "drink_4";
			link.l2 = StringFromKey("PedroHurtado_182");
			link.l2.go = "drink_exit";
			link.l3 = StringFromKey("PedroHurtado_183");
			link.l3.go = "drink_exit";
		break;

		case "drink_exit":
			dialog.text = StringFromKey("PedroHurtado_184");
			link.l1 = StringFromKey("PedroHurtado_185");
			link.l1.go = "exit";
			CloseQuestHeader("LSC_Drink");
			RemoveLandQuestMark_Main(npchar, "LSC_Drink");
		break;

		case "drink_4":
			dialog.text = StringFromKey("PedroHurtado_186", pchar);
			link.l1 = StringFromKey("PedroHurtado_187");
			link.l1.go = "drink_5";
		break;

		case "drink_5":
			dialog.text = StringFromKey("PedroHurtado_188", pchar);
			link.l1 = StringFromKey("PedroHurtado_189");
			link.l1.go = "drink_6";
			link.l2 = StringFromKey("PedroHurtado_190");
			link.l2.go = "drink_exit";
		break;

		case "drink_6":
			dialog.text = StringFromKey("PedroHurtado_191", pchar);
			link.l1 = StringFromKey("PedroHurtado_192");
			link.l1.go = "drink_7";
		break;

		case "drink_7":
			DialogExit();
			NextDiag.CurrentNode = "drink_wait";
			pchar.questTemp.LSC.Drink = "begin";
			//pchar.questTemp.LSC.Drink.Chance = rand(100); // итог бухалова

			SetFunctionTimerCondition("LSC_DrinkOver", 0, 0, 3, false); // 3 дня
			AddQuestRecord("LSC_Drink", "1");
			RemoveLandQuestMark_Main(npchar, "LSC_Drink");
			AddLandQuestMark_Main(CharacterFromID("MalcolmFawn"), "LSC_Drink");
		break;

		case "drink_wait":
			dialog.text = StringFromKey("PedroHurtado_193", pchar);
			link.l1 = StringFromKey("PedroHurtado_194");
			link.l1.go = "exit";
			NextDiag.TempNode = "drink_wait";
		break;

		case "result_1":
			dialog.text = StringFromKey("PedroHurtado_195", pchar);
			link.l1 = StringFromKey("PedroHurtado_196", pchar);
			link.l1.go = "result_win";
		break;

		case "result_2":
			dialog.text = StringFromKey("PedroHurtado_197", pchar);
			link.l1 = StringFromKey("PedroHurtado_198");
			link.l1.go = "result_fail";
		break;

		case "result_win":
			dialog.text = StringFromKey("PedroHurtado_199");
			link.l1 = StringFromKey("PedroHurtado_200");
			link.l1.go = "result_win_1";
		break;

		case "result_win_1":
			DialogExit();
			NextDiag.CurrentNode = "result_win_2";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "LostShipsCity_town", "reload", "reload38", "LSC_DrinkGotoVelasco", -1);
			AddQuestRecord("LSC_Drink", "3");
		break;

		case "result_win_2":
			pchar.quest.LSC_Drink1.over = "yes"; //снять таймер
			dialog.text = StringFromKey("PedroHurtado_201");
			link.l1 = StringFromKey("PedroHurtado_202");
			link.l1.go = "result_win_3";
		break;

		case "result_win_3":
			DialogExit();
			GiveItem2Character(pchar, "key_drinkQ");
			NextDiag.CurrentNode = "result_grabbing";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "reload", "reload68", "LSC_DrinkGotoVelasco_3", -1);
		break;

		case "result_grabbing":
		// считаем деньги взятые из сундука
			iMoney = sti(pchar.money) - sti(pchar.questTemp.LSC.Drink.Money);
			if (iMoney <= 0) sMoney = StringFromKey("PedroHurtado_203");
			else sMoney = FindMoneyString(iMoney);
			if (iMoney <= 10000) sTotalTemp = StringFromKey("PedroHurtado_204");
			else
			{
				if (iMoney <= 50000) sTotalTemp = StringFromKey("PedroHurtado_205", pchar);
				else
				{
					if (iMoney <= 100000) sTotalTemp = StringFromKey("PedroHurtado_206");
					else
					{
						if (iMoney <= 150000) sTotalTemp = StringFromKey("PedroHurtado_207", pchar);
						else sTotalTemp = StringFromKey("PedroHurtado_208", pchar);
					}
				}
			}
			dialog.text = StringFromKey("PedroHurtado_209");
			if (iMoney <= 0)
			{
				link.l1 = StringFromKey("PedroHurtado_210");
				link.l1.go = "grabbing_0";
			}
			else
			{
				link.l1 = StringFromKey("PedroHurtado_211", pchar, sMoney);
				link.l1.go = "grabbing_1";
			}
		break;

		case "grabbing_0":
			dialog.text = StringFromKey("PedroHurtado_212", pchar);
			link.l1 = "...";
			link.l1.go = "grabbing_exit";
			AddQuestRecord("LSC_Drink", "6");
			AddQuestUserData("LSC_Drink", "sSex", GetSexPhrase("", "ла"));
			AddQuestUserData("LSC_Drink", "sSex2", GetSexPhrase("", "а"));
			npchar.location.group = "goto";
			npchar.location.locator = "goto06_1";
		break;

		case "grabbing_1":
			dialog.text = sTotalTemp;
			link.l1 = StringFromKey("PedroHurtado_213");
			link.l1.go = "grabbing_part";
		break;

		case "grabbing_part":
			iMoney = makeint((sti(pchar.money) - sti(pchar.questTemp.LSC.Drink.Money)) / 2);
			AddMoneyToCharacter(pchar, -iMoney);
			PlaySound("Important_item");
			dialog.text = StringFromKey("PedroHurtado_214", pchar);
			link.l1 = StringFromKey("PedroHurtado_215");
			link.l1.go = "grabbing_exit";
			AddSimpleRumourCityTip(
				StringFromKey("PedroHurtado_216"), "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip(
				StringFromKey("PedroHurtado_217"), "LostShipsCity", 3, 1, "LSC", "");
			AddSimpleRumourCityTip(
				StringFromKey("PedroHurtado_218"), "LostShipsCity", 3, 2, "LSC", "");
			AddQuestRecord("LSC_Drink", "5");
			AddQuestUserData("LSC_Drink", "sSex", GetSexPhrase("", "ла"));
			AddQuestUserData("LSC_Drink", "sSex2", GetSexPhrase("", "а"));
			npchar.location.group = "goto";
			npchar.location.locator = "goto06_1";
		break;

		case "grabbing_exit":
			DialogExit();
			RemoveItems(pchar, "key_drinkQ", 1);
			RemoveItems(pchar, "key_drink", 1);
			int n = Findlocation("VelascoBank");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("LostShipsCity_town", "reload75", true); // дверку закрываем
			LAi_SetActorType(npchar);
			LAI_TYPE_LSCout_Goto(npchar);
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour = sti(GetTime() + 5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			CloseQuestHeader("LSC_Drink");
		break;

		case "result_fail":
			DialogExit();
			LAi_SetActorType(npchar);
			LAI_TYPE_LSCout_Goto(npchar);
			chrDisableReloadToLocation = false;//открыть локацию
			pchar.quest.LSC_Drink4.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink4.win_condition.l1.date.hour = sti(GetTime() + 5);
			pchar.quest.LSC_Drink4.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink4.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink4.function = "LSC_DrinkDelete";
			AddQuestRecord("LSC_Drink", "4");
			AddQuestUserData("LSC_Drink", "sSex", GetSexPhrase("", "ла"));
			AddQuestUserData("LSC_Drink", "sSex2", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("LSC_Drink");
		break;
		// <-- пей до дна

		//как пройти в Веласко
		case "goToVelasco":
			if (CheckAttribute(npchar, "quest.waitMoney"))
			{
				dialog.text = StringFromKey("PedroHurtado_219");
				if (sti(pchar.money) < sti(npchar.quest.waitMoney))
				{
					link.l1 = StringFromKey("PedroHurtado_220");
					link.l1.go = "goToVelasco_2";
				}
				else
				{
					link.l1 = StringFromKey("PedroHurtado_221");
					link.l1.go = "goToVelasco_1";
				}
				break;
			}
			if (npchar.quest.store == "over")
			{
				dialog.text = StringFromKey("PedroHurtado_222");
				link.l1 = StringFromKey("PedroHurtado_223");
				link.l1.go = "goToVelasco_1";
			}
			else
			{
				//int iTemp;
				if (npchar.quest.store == "fail") iMoney = 25000;
				else iMoney = 50000;
				dialog.text = StringFromKey("PedroHurtado_224", FindMoneyString(iMoney));
				npchar.quest.waitMoney = iMoney;
				if (sti(pchar.money) < iMoney)
				{
					link.l1 = StringFromKey("PedroHurtado_225");
					link.l1.go = "goToVelasco_2";
				}
				else
				{
					link.l1 = StringFromKey("PedroHurtado_226");
					link.l1.go = "goToVelasco_1";
				}
				link.l2 = StringFromKey("PedroHurtado_227");
				link.l2.go = "exit";
			}
		break;
		case "goToVelasco_1":
			dialog.text = StringFromKey("PedroHurtado_228");
			link.l1 = StringFromKey("PedroHurtado_229");
			link.l1.go = "goToVelasco_3";
		break;
		case "goToVelasco_2":
			dialog.text = StringFromKey("PedroHurtado_230");
			link.l1 = StringFromKey("PedroHurtado_231");
			link.l1.go = "exit";
		break;
		case "goToVelasco_3":
			dialog.text = StringFromKey("PedroHurtado_232");
			link.l1 = StringFromKey("PedroHurtado_233");
			link.l1.go = "goToVelasco_4";
		break;
		case "goToVelasco_4":
			dialog.text = StringFromKey("PedroHurtado_234");
			link.l1 = StringFromKey("PedroHurtado_235");
			link.l1.go = "goToVelasco_5";
		break;
		case "goToVelasco_5":
			dialog.text = StringFromKey("PedroHurtado_236");
			link.l1 = "...";
			link.l1.go = "goToVelasco_6";
		break;
		case "goToVelasco_6":
			dialog.text = StringFromKey("PedroHurtado_237");
			link.l1 = StringFromKey("PedroHurtado_238");
			link.l1.go = "goToVelasco_7";
			link.l2 = StringFromKey("PedroHurtado_239");
			link.l2.go = "goToVelasco_11";
		break;
		case "goToVelasco_7":
			dialog.text = StringFromKey("PedroHurtado_240");
			link.l1 = StringFromKey("PedroHurtado_241");
			link.l1.go = "goToVelasco_8";
			link.l2 = StringFromKey("PedroHurtado_242");
			link.l2.go = "goToVelasco_11";
		break;
		case "goToVelasco_8":
			dialog.text = StringFromKey("PedroHurtado_243");
			link.l1 = StringFromKey("PedroHurtado_244");
			link.l1.go = "goToVelasco_9";
			link.l2 = StringFromKey("PedroHurtado_245");
			link.l2.go = "goToVelasco_11";
		break;
		case "goToVelasco_9":
			dialog.text = StringFromKey("PedroHurtado_246");
			link.l1 = StringFromKey("PedroHurtado_247");
			link.l1.go = "goToVelasco_10";
			link.l2 = StringFromKey("PedroHurtado_248");
			link.l2.go = "goToVelasco_11";
		break;
		case "goToVelasco_10":
			dialog.text = StringFromKey("PedroHurtado_249");
			link.l1 = StringFromKey("PedroHurtado_250");
			link.l1.go = "goToVelasco_11";
		break;
		case "goToVelasco_11":
			dialog.text = StringFromKey("PedroHurtado_251");
			link.l1 = StringFromKey("PedroHurtado_252");
			link.l1.go = "exit";
			if (CheckAttribute(npchar, "quest.waitMoney")) AddMoneyToCharacter(pchar, -sti(npchar.quest.waitMoney));
			npchar.quest.goToVelasco = true;
			AddQuestRecord("ISS_MainLine", "72");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;

		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("PedroHurtado_253"),
						StringFromKey("PedroHurtado_254", pchar),
						StringFromKey("PedroHurtado_255", pchar),
						StringFromKey("PedroHurtado_256"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("PedroHurtado_257"),
						StringFromKey("PedroHurtado_258", pchar),
						StringFromKey("PedroHurtado_259"),
						StringFromKey("PedroHurtado_260", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("PedroHurtado_261");
			link.l1 = StringFromKey("PedroHurtado_262");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("PedroHurtado_263");
			link.l1 = StringFromKey("PedroHurtado_264");
			link.l1.go = "exit";
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = StringFromKey("PedroHurtado_265");
			link.l1 = StringFromKey("PedroHurtado_266");
			link.l1.go = "SeekCrew_1";
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("PedroHurtado_267");
			link.l1 = StringFromKey("PedroHurtado_268");
			link.l1.go = "SeekCrew_1_1";
			link.l2 = StringFromKey("PedroHurtado_269");
			link.l2.go = "SeekCrew_2";
		break;
		case "SeekCrew_1_1":
			dialog.text = StringFromKey("PedroHurtado_270");
			link.l1 = StringFromKey("PedroHurtado_271");
			link.l1.go = "SeekCrew_1_2";
		break;
		case "SeekCrew_1_2":
			dialog.text = StringFromKey("PedroHurtado_272");
			link.l1 = StringFromKey("PedroHurtado_273");
			link.l1.go = "SeekCrew_1_3";
			link.l2 = StringFromKey("PedroHurtado_274");
			link.l2.go = "SeekCrew_1_4";
			link.l3 = StringFromKey("PedroHurtado_275");
			link.l3.go = "SeekCrew_1_4";
			link.l4 = StringFromKey("PedroHurtado_276");
			link.l4.go = "SeekCrew_2";
			link.l5 = StringFromKey("PedroHurtado_277");
			link.l5.go = "SeekCrew_2";
		break;
		case "SeekCrew_1_3":
			dialog.text = StringFromKey("PedroHurtado_278");
			link.l1 = "...";
			link.l1.go = "SeekCrew_1_2";
		break;
		case "SeekCrew_1_4":
			dialog.text = StringFromKey("PedroHurtado_279");
			link.l1 = StringFromKey("PedroHurtado_280");
			link.l1.go = "SeekCrew_1_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("PedroHurtado_281");
			link.l1 = StringFromKey("PedroHurtado_282");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("PedroHurtado_283");
			link.l1 = StringFromKey("PedroHurtado_284");
			link.l1.go = "SeekCrew_all";
		break;
		//финальная реплика
		case "GoodBye":
			dialog.text = StringFromKey("PedroHurtado_285", pchar);
			link.l1 = StringFromKey("PedroHurtado_286");
			link.l1.go = "GoodBye_0";
		break;
		case "GoodBye_0":
			dialog.text = StringFromKey("PedroHurtado_287");
			link.l1 = StringFromKey("PedroHurtado_288");
			link.l1.go = "GoodBye_1";
			link.l2 = StringFromKey("PedroHurtado_289");
			link.l2.go = "GoodBye_4";
		break;
		case "GoodBye_1":
			dialog.text = StringFromKey("PedroHurtado_290");
			link.l1 = StringFromKey("PedroHurtado_291");
			link.l1.go = "GoodBye_2";
		break;
		case "GoodBye_2":
			dialog.text = StringFromKey("PedroHurtado_292");
			link.l1 = StringFromKey("PedroHurtado_293");
			link.l1.go = "GoodBye_3";
		break;
		case "GoodBye_3":
			dialog.text = StringFromKey("PedroHurtado_294", pchar);
			link.l1 = StringFromKey("PedroHurtado_295");
			link.l1.go = "GoodBye_4";
		break;
		case "GoodBye_4":
			dialog.text = StringFromKey("PedroHurtado_296");
			link.l1 = StringFromKey("PedroHurtado_297");
			link.l1.go = "GoodBye_5";
		break;
		case "GoodBye_5":
			dialog.text = StringFromKey("PedroHurtado_298");
			link.l1 = StringFromKey("PedroHurtado_299");
			link.l1.go = "Exit_GoodBye";
			AddMoneyToCharacter(pchar, 1);
		break;
	}
	NextDiag.PrevNode = NodeName;
}

#include "DIALOGS\Rumours\Simple_rumors.c"
#include "DIALOGS\Quest\LostShipsCity\SeekLSCCitizen_CN.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06
	ProcessDialog_SeekLSCCitizenCN(NPChar, Link, NextDiag); // для CN языка - поисковик жителей

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
					dialog.text = StringFromKey("AndreLabor_1", GetFullName(npchar));
					link.l1 = StringFromKey("AndreLabor_2", GetFullName(pchar), npchar.lastname);
					link.l1.go = "FS_1";
				}
				else
				{
					dialog.text = StringFromKey("AndreLabor_3", GetFullName(npchar));
					link.l1 = StringFromKey("AndreLabor_4", GetFullName(pchar), npchar.lastname);
					link.l1.go = "FT_1";
				}
			}
			else
			{
				dialog.text = StringFromKey("AndreLabor_5", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("AndreLabor_6");
				link.l1.go = "SeekCitizen";
				link.l2 = StringFromKey("AndreLabor_7");
				link.l2.go = "int_quests";
				link.l3 = StringFromKey("AndreLabor_11", LinkRandPhrase(
							StringFromKey("AndreLabor_8"),
							StringFromKey("AndreLabor_9"),
							StringFromKey("AndreLabor_10", pchar)));
				link.l3.go = "rumours_LSC";
				link.l4 = StringFromKey("AndreLabor_12");
				link.l4.go = "exit";
				if (pchar.questTemp.LSC == "toAndreLabor")
				{
					link.l5 = StringFromKey("AndreLabor_13");
					link.l5.go = "Tizer_1";
				}

			}
		break;
		case "FS_1":
			dialog.text = StringFromKey("AndreLabor_14", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("AndreLabor_15");
			link.l1.go = "FT_1";
		break;
		case "FT_1":
			dialog.text = StringFromKey("AndreLabor_16");
			link.l1 = StringFromKey("AndreLabor_17");
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("AndreLabor_18", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("AndreLabor_19");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("AndreLabor_20");
			link.l1 = StringFromKey("AndreLabor_21");
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("AndreLabor_22");
			link.l1 = StringFromKey("AndreLabor_23");
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = StringFromKey("AndreLabor_24", pchar);
			link.l1 = StringFromKey("AndreLabor_25", npchar.name);
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
			dialog.text = StringFromKey("AndreLabor_29", LinkRandPhrase(
						StringFromKey("AndreLabor_26", pchar),
						StringFromKey("AndreLabor_27", pchar),
						StringFromKey("AndreLabor_28", pchar)));
			link.l1 = StringFromKey("AndreLabor_30");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("AndreLabor_31");
			link.l1 = StringFromKey("AndreLabor_32");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("AndreLabor_36", LinkRandPhrase(
						StringFromKey("AndreLabor_33"),
						StringFromKey("AndreLabor_34"),
						StringFromKey("AndreLabor_35", pchar)));
			link.l1 = StringFromKey("AndreLabor_40", LinkRandPhrase(
						StringFromKey("AndreLabor_37"),
						StringFromKey("AndreLabor_38"),
						StringFromKey("AndreLabor_39")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("AndreLabor_41", npchar);
				link.l1 = StringFromKey("AndreLabor_45", LinkRandPhrase(
							StringFromKey("AndreLabor_42"),
							StringFromKey("AndreLabor_43"),
							StringFromKey("AndreLabor_44")));
			}
			else
			{
				dialog.text = StringFromKey("AndreLabor_46", npchar);
				link.l1 = StringFromKey("AndreLabor_49", RandPhraseSimple(
							StringFromKey("AndreLabor_47", pchar),
							StringFromKey("AndreLabor_48")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		//ищем человека
		case "SeekCitizen":
			dialog.text = StringFromKey("AndreLabor_50");
			Link.l1.edit = 3;
			Link.l1 = "";
			Link.l1.go = "SeekCitizen_Choice_1";
			SeekLSCCitizen_ChineseWrapper(Npchar, Link);
		break;
		case "SeekCitizen_Choice_1":
			sld = CheckLSCCitizen();
			if (sld.id == "none")
			{
				dialog.text = StringFromKey("AndreLabor_51");
				Link.l1 = StringFromKey("AndreLabor_52");
				Link.l1.go = "SeekCitizen_Choice_2";
				Link.l2 = StringFromKey("AndreLabor_53", pchar);
				Link.l2.go = "exit";
			}
			else
			{
				if (sld.id == npchar.id)
				{
					dialog.text = StringFromKey("AndreLabor_54");
					link.l1 = StringFromKey("AndreLabor_55", pchar);
					link.l1.go = "exit";
					break;
				}
				if (sld.sex == "man")
				{
					dialog.text = StringFromKey("AndreLabor_56", GetFullName(sld));
					Link.l1 = StringFromKey("AndreLabor_57");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("AndreLabor_58");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				else
				{
					dialog.text = StringFromKey("AndreLabor_59", GetFullName(sld));
					Link.l1 = StringFromKey("AndreLabor_60");
					Link.l1.go = "SeekCitizen_agree";
					Link.l2 = StringFromKey("AndreLabor_61");
					Link.l2.go = "SeekCitizen_Choice_2";
				}
				Link.l3 = StringFromKey("AndreLabor_62");
				Link.l3.go = "exit";
				npchar.quest.seekIdx = sld.index;
			}
		break;
		case "SeekCitizen_Choice_2":
			dialog.text = StringFromKey("AndreLabor_63");
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
					dialog.text = StringFromKey("AndreLabor_67", LinkRandPhrase(
								StringFromKey("AndreLabor_64"),
								StringFromKey("AndreLabor_65"),
								StringFromKey("AndreLabor_66")));
					link.l1 = StringFromKey("AndreLabor_70", RandPhraseSimple(
								StringFromKey("AndreLabor_68"),
								StringFromKey("AndreLabor_69")));
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = StringFromKey("AndreLabor_74", LinkRandPhrase(
								StringFromKey("AndreLabor_71"),
								StringFromKey("AndreLabor_72"),
								StringFromKey("AndreLabor_73")));
					link.l1 = StringFromKey("AndreLabor_77", RandPhraseSimple(
								StringFromKey("AndreLabor_75"),
								StringFromKey("AndreLabor_76")));
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
							dialog.text = StringFromKey("AndreLabor_81", LinkRandPhrase(
										StringFromKey("AndreLabor_78"),
										StringFromKey("AndreLabor_79"),
										StringFromKey("AndreLabor_80")));
						}
						else
						{
							dialog.text = StringFromKey("AndreLabor_85", LinkRandPhrase(
										StringFromKey("AndreLabor_82", npchar.quest.seekIdx.where),
										StringFromKey("AndreLabor_83", npchar.quest.seekIdx.where),
										StringFromKey("AndreLabor_84", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("AndreLabor_89", LinkRandPhrase(
										StringFromKey("AndreLabor_86", npchar.quest.seekIdx.where),
										StringFromKey("AndreLabor_87"),
										StringFromKey("AndreLabor_88")));
						}
						else
						{
							dialog.text = StringFromKey("AndreLabor_93", LinkRandPhrase(
										StringFromKey("AndreLabor_90", npchar.quest.seekIdx.where),
										StringFromKey("AndreLabor_91", npchar.quest.seekIdx.where),
										StringFromKey("AndreLabor_92", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("AndreLabor_96", RandPhraseSimple(
								StringFromKey("AndreLabor_94"),
								StringFromKey("AndreLabor_95")));
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
							dialog.text = StringFromKey("AndreLabor_100", LinkRandPhrase(
										StringFromKey("AndreLabor_97"),
										StringFromKey("AndreLabor_98"),
										StringFromKey("AndreLabor_99")));
						}
						else
						{
							dialog.text = StringFromKey("AndreLabor_104", LinkRandPhrase(
										StringFromKey("AndreLabor_101", npchar.quest.seekIdx.where),
										StringFromKey("AndreLabor_102", npchar.quest.seekIdx.where),
										StringFromKey("AndreLabor_103", npchar.quest.seekIdx.where)));
						}
					}
					else
					{
						if (npchar.location == sld.location)
						{
							dialog.text = StringFromKey("AndreLabor_108", LinkRandPhrase(
										StringFromKey("AndreLabor_105", npchar.quest.seekIdx.where),
										StringFromKey("AndreLabor_106"),
										StringFromKey("AndreLabor_107")));
						}
						else
						{
							dialog.text = StringFromKey("AndreLabor_112", LinkRandPhrase(
										StringFromKey("AndreLabor_109", npchar.quest.seekIdx.where),
										StringFromKey("AndreLabor_110", npchar.quest.seekIdx.where),
										StringFromKey("AndreLabor_111", npchar.quest.seekIdx.where)));
						}
					}
					link.l1 = StringFromKey("AndreLabor_115", RandPhraseSimple(
								StringFromKey("AndreLabor_113", GetAddress_FormToNPC(NPChar)),
								StringFromKey("AndreLabor_114")));
					link.l1.go = "exit";
				}
			}
		break;
		//вопросы
		case "int_quests":
			dialog.text = StringFromKey("AndreLabor_116", pchar);
			if (!CheckAttribute(NextDiag, NodeName + ".l5"))
			{
				link.l5 = StringFromKey("AndreLabor_117");
				link.l5.go = "ansewer_5";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l1"))
			{
				link.l1 = StringFromKey("AndreLabor_118");
				link.l1.go = "ansewer_1";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l2"))
			{
				link.l2 = StringFromKey("AndreLabor_119");
				link.l2.go = "ansewer_2";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l3"))
			{
				link.l3 = StringFromKey("AndreLabor_120");
				link.l3.go = "ansewer_3";
			}
			if (!CheckAttribute(NextDiag, NodeName + ".l4"))
			{
				link.l4 = StringFromKey("AndreLabor_121");
				link.l4.go = "ansewer_4";
			}
			link.l10 = StringFromKey("AndreLabor_122");
			link.l10.go = "exit";
		break;
		case "ansewer_5":
			dialog.text = StringFromKey("AndreLabor_123");
			link.l1 = StringFromKey("AndreLabor_124");
			link.l1.go = "ansewer_5_1";
		break;
		case "ansewer_5_1":
			dialog.text = StringFromKey("AndreLabor_125");
			link.l1 = StringFromKey("AndreLabor_126");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l5 = true;
		break;
		case "ansewer_1":
			dialog.text = StringFromKey("AndreLabor_127");
			link.l1 = StringFromKey("AndreLabor_128");
			link.l1.go = "int_quests";
			NextDiag.(NodePrevName).l1 = true;
		break;
		case "ansewer_2":
			dialog.text = StringFromKey("AndreLabor_129");
			link.l1 = StringFromKey("AndreLabor_130");
			link.l1.go = "ansewer_2_1";
			NextDiag.(NodePrevName).l2 = true;
		break;
		case "ansewer_2_1":
			dialog.text = StringFromKey("AndreLabor_131");
			link.l1 = StringFromKey("AndreLabor_132");
			link.l1.go = "int_quests";
		break;
		case "ansewer_3":
			dialog.text = StringFromKey("AndreLabor_133");
			link.l1 = StringFromKey("AndreLabor_134");
			link.l1.go = "ansewer_3_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_3_1":
			dialog.text = StringFromKey("AndreLabor_135", pchar);
			link.l1 = StringFromKey("AndreLabor_136");
			link.l1.go = "int_quests";
		break;
		case "ansewer_4":
			dialog.text = StringFromKey("AndreLabor_137");
			link.l1 = StringFromKey("AndreLabor_138");
			link.l1.go = "ansewer_4_1";
			NextDiag.(NodePrevName).l3 = true;
		break;
		case "ansewer_4_1":
			dialog.text = StringFromKey("AndreLabor_139");
			link.l1 = StringFromKey("AndreLabor_140");
			link.l1.go = "ansewer_4_2";
		break;
		case "ansewer_4_2":
			dialog.text = StringFromKey("AndreLabor_141");
			link.l1 = StringFromKey("AndreLabor_142");
			link.l1.go = "int_quests";
		break;
		//квестовые диалоги
		case "Tizer_1":
			dialog.text = StringFromKey("AndreLabor_143");
			link.l1 = StringFromKey("AndreLabor_144");
			link.l1.go = "Tizer_2";
		break;
		case "Tizer_2":
			dialog.text = StringFromKey("AndreLabor_145");
			link.l1 = StringFromKey("AndreLabor_146");
			link.l1.go = "Tizer_3";
		break;
		case "Tizer_3":
			dialog.text = StringFromKey("AndreLabor_147", pchar);
			link.l1 = StringFromKey("AndreLabor_148");
			link.l1.go = "Tizer_4";
		break;
		case "Tizer_4":
			dialog.text = StringFromKey("AndreLabor_149");
			link.l1 = StringFromKey("AndreLabor_150");
			link.l1.go = "Tizer_5";
		break;
		case "Tizer_5":
			dialog.text = StringFromKey("AndreLabor_151");
			link.l1 = StringFromKey("AndreLabor_152");
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "9");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ёл", "ла"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("", "а"));
			pchar.questTemp.LSC = "toProtector";
			pchar.quest.LSC_enterToProtector.win_condition.l1 = "location";
			pchar.quest.LSC_enterToProtector.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_enterToProtector.function = "LSC_enterToProtector";
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;

	}
	NextDiag.PrevNode = NodeName;
}

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "first time":
			PlaySound("Voice\" + VoiceGetLanguage() + "\FranceLine\fushe_firsttime.ogg"); //салютмонами женеманжпасижу кринж убрал Konstrush

			dialog.text = StringFromKey("JozefFushe_1");
			link.l1 = StringFromKey("JozefFushe_2");
			link.l1.go = "1";
		break;

		case "1":
			dialog.text = StringFromKey("JozefFushe_3");
			link.l1 = StringFromKey("JozefFushe_4");
			link.l1.go = "exit";

			NextDiag.TempNode = "2";
		break;

		case "2":
			dialog.text = StringFromKey("JozefFushe_5");
			link.l1 = StringFromKey("JozefFushe_6");
			link.l1.go = "3";
		break;

		case "3":
			dialog.text = StringFromKey("JozefFushe_7");
			link.l1 = StringFromKey("JozefFushe_8");
			link.l1.go = "4";
		break;

		case "4":
			dialog.text = StringFromKey("JozefFushe_9");
			link.l1 = StringFromKey("JozefFushe_10");
			link.l1.go = "exit";

			AddDialogExitQuest("FL1_s26");
			NextDiag.TempNode = "5";
		break;

		case "5":
			dialog.text = StringFromKey("JozefFushe_11");
			link.l1 = StringFromKey("JozefFushe_12");
			link.l1.go = "6";
		break;

		case "6":
			dialog.text = StringFromKey("JozefFushe_13");
			link.l1 = StringFromKey("JozefFushe_14");
			link.l1.go = "7";
		break;

		case "7":
			dialog.text = StringFromKey("JozefFushe_15");
			link.l1 = StringFromKey("JozefFushe_16");
			link.l1.go = "exit";

			NextDiag.TempNode = "8";
		break;

		case "8":
			if (pchar.MainQuest == "FL1_s30_v1" || pchar.MainQuest == "FL1_s32_failed")
			//if(CheckAttribute(pchar, "MainQuest") && (pchar.MainQuest == "FL1_s30_v1" || pchar.MainQuest == "FL1_s32_failed"))
			{
				dialog.text = StringFromKey("JozefFushe_17");
				link.l1 = StringFromKey("JozefFushe_18");
				link.l1.go = "9";
			}
			else
			{
				dialog.text = StringFromKey("JozefFushe_19");
				link.l1 = StringFromKey("JozefFushe_20");
				link.l1.go = "10";
			}
		break;

		case "9":
			dialog.text = StringFromKey("JozefFushe_21");
			link.l1 = StringFromKey("JozefFushe_22");
			link.l1.go = "exit";

			AddDialogExitQuest("FL1_s31_end");
		break;

		case "10":
			dialog.text = StringFromKey("JozefFushe_23");
			link.l1 = StringFromKey("JozefFushe_24");
			link.l1.go = "11";
		break;

		case "11":
			dialog.text = StringFromKey("JozefFushe_25");
			link.l1 = StringFromKey("JozefFushe_26");
			link.l1.go = "12";
		break;

		case "12":
			dialog.text = StringFromKey("JozefFushe_27");
			link.l1 = StringFromKey("JozefFushe_28");
			link.l1.go = "13";
		break;

		case "13":
			dialog.text = StringFromKey("JozefFushe_29");
			link.l1 = StringFromKey("JozefFushe_30");
			link.l1.go = "exit";

			AddDialogExitQuest("FL1_s40");
			NextDiag.TempNode = "14";
		break;

		case "14":
			dialog.text = StringFromKey("JozefFushe_31");
			link.l1 = StringFromKey("JozefFushe_32");
			link.l1.go = "15";
		break;

		case "15":
			dialog.text = StringFromKey("JozefFushe_33");
			link.l1 = StringFromKey("JozefFushe_34");
			link.l1.go = "16";
		break;

		case "16":
			dialog.text = StringFromKey("JozefFushe_35");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "17";
		break;

		case "17":
			dialog.text = StringFromKey("JozefFushe_36");
			link.l1 = StringFromKey("JozefFushe_37");
			link.l1.go = "18";
		break;

		case "18":
			dialog.text = StringFromKey("JozefFushe_38");
			link.l1 = StringFromKey("JozefFushe_39");
			link.l1.go = "19";
		break;

		case "19":
			dialog.text = StringFromKey("JozefFushe_40");
			link.l1 = StringFromKey("JozefFushe_41");
			link.l1.go = "20";
		break;

		case "20":
			TakeItemFromCharacter(pchar, "FQ_letter1");
			dialog.text = StringFromKey("JozefFushe_42");
			link.l1 = StringFromKey("JozefFushe_43");
			link.l1.go = "21";
		break;

		case "21":
			dialog.text = StringFromKey("JozefFushe_44");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "22";
			AddDialogExitQuest("FL1_s54");
		break;

		case "22":
			dialog.text = StringFromKey("JozefFushe_45");
			link.l1 = StringFromKey("JozefFushe_46");
			link.l1.go = "23";
		break;

		case "23":
			dialog.text = StringFromKey("JozefFushe_47");
			link.l1 = StringFromKey("JozefFushe_48");
			link.l1.go = "24";
		break;

		case "24":
			dialog.text = StringFromKey("JozefFushe_49");
			link.l1 = StringFromKey("JozefFushe_50");
			link.l1.go = "25";
		break;

		case "25":
			dialog.text = StringFromKey("JozefFushe_51");
			link.l1 = StringFromKey("JozefFushe_52");
			link.l1.go = "26";
		break;

		case "26":
			dialog.text = StringFromKey("JozefFushe_53");
			link.l1 = StringFromKey("JozefFushe_54");
			link.l1.go = "27";
		break;

		case "27":
			dialog.text = StringFromKey("JozefFushe_55");
			link.l1 = StringFromKey("JozefFushe_56");
			link.l1.go = "28";
		break;

		case "28":
			dialog.text = StringFromKey("JozefFushe_57");
			link.l1 = StringFromKey("JozefFushe_58");
			link.l1.go = "29";
		break;

		case "29":
			dialog.text = StringFromKey("JozefFushe_59");
			link.l1 = "...";
			link.l1.go = "exit";

			AddDialogExitQuest("FL1_s57");
			NextDiag.TempNode = "30";
		break;

		/* диалог в каюте захваченного корабля */
		case "30":
			dialog.text = StringFromKey("JozefFushe_60");
			link.l1 = StringFromKey("JozefFushe_61");
			link.l1.go = "31";
		break;

		case "31":
			dialog.text = StringFromKey("JozefFushe_62");
			link.l1 = StringFromKey("JozefFushe_63");
			link.l1.go = "exit";

			NextDiag.TempNode = "32";
		break;

		/* Диалог на пирсе Тортуги. Вручение корабля. */
		case "32":
			dialog.text = StringFromKey("JozefFushe_64");
			link.l1 = StringFromKey("JozefFushe_65");
			link.l1.go = "exit";

			NextDiag.TempNode = "33";
		break;

		case "33":
			dialog.text = StringFromKey("JozefFushe_66");
			link.l1 = StringFromKey("JozefFushe_67");
			link.l1.go = "exit";

			NextDiag.TempNode = "34";
		break;

		case "34":
			dialog.text = StringFromKey("JozefFushe_68");
			link.l1 = StringFromKey("JozefFushe_69");
			link.l1.go = "35";
		break;

		case "35":
			dialog.text = StringFromKey("JozefFushe_70");
			link.l1 = StringFromKey("JozefFushe_71");
			link.l1.go = "36";
		break;

		case "36":
			dialog.text = StringFromKey("JozefFushe_72");
			link.l1 = StringFromKey("JozefFushe_73");
			link.l1.go = "37";
		break;

		case "37":
			dialog.text = StringFromKey("JozefFushe_74");
			link.l1 = StringFromKey("JozefFushe_75");
			link.l1.go = "38";
		break;

		case "38":
			dialog.text = StringFromKey("JozefFushe_76");
			link.l1 = StringFromKey("JozefFushe_77");
			link.l1.go = "39";
		break;

		case "39":
			dialog.text = StringFromKey("JozefFushe_78");
			link.l1 = StringFromKey("JozefFushe_79");
			link.l1.go = "40";
		break;

		case "40":
			dialog.text = StringFromKey("JozefFushe_80");
			link.l1 = StringFromKey("JozefFushe_81");
			link.l1.go = "First_man";
		break;

		case "41":
			dialog.text = StringFromKey("JozefFushe_82");
			link.l1 = StringFromKey("JozefFushe_83");
			link.l1.go = "42";
		break;

		case "42":
			dialog.text = StringFromKey("JozefFushe_84");
			link.l1 = StringFromKey("JozefFushe_85");
			link.l1.go = "exit";

			NextDiag.TempNode = "43";
		break;

		case "43":
			dialog.text = StringFromKey("JozefFushe_89", LinkRandPhrase(
						StringFromKey("JozefFushe_86"),
						StringFromKey("JozefFushe_87"),
						StringFromKey("JozefFushe_88")));
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "43";
		break;

		/* диалог в резиденции губернатора Гибралтара */
		case "44":
			dialog.text = StringFromKey("JozefFushe_90");
			link.l1 = StringFromKey("JozefFushe_91");
			link.l1.go = "45";
		break;

		case "45":
			dialog.text = StringFromKey("JozefFushe_92");
			link.l1 = StringFromKey("JozefFushe_93");
			link.l1.go = "exit";

			NextDiag.TempNode = "46";
		break;

		case "46":
			dialog.text = StringFromKey("JozefFushe_94");
			link.l1 = StringFromKey("JozefFushe_95");
			link.l1.go = "47";
		break;

		case "47":
			dialog.text = StringFromKey("JozefFushe_96");
			link.l1 = StringFromKey("JozefFushe_97");
			link.l1.go = "48";
		break;

		case "48":
			dialog.text = StringFromKey("JozefFushe_98");
			link.l1 = StringFromKey("JozefFushe_99");
			link.l1.go = "49";
		break;

		case "49":
			dialog.text = StringFromKey("JozefFushe_100");
			link.l1 = StringFromKey("JozefFushe_101");
			link.l1.go = "50";
		break;

		case "50":
			dialog.text = StringFromKey("JozefFushe_102");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "51";
		break;

		/* Диалог по выходу из верфи (возврат корабля Фуше) */
		case "51":
			dialog.text = StringFromKey("JozefFushe_103");
			link.l1 = StringFromKey("JozefFushe_104");
			link.l1.go = "52";
		break;

		case "52":
			dialog.text = StringFromKey("JozefFushe_105");
			link.l1 = StringFromKey("JozefFushe_106");
			link.l1.go = "53";
		break;

		case "53":
			dialog.text = StringFromKey("JozefFushe_107");
			link.l1 = StringFromKey("JozefFushe_108");
			link.l1.go = "exit";

			NextDiag.TempNode = "54";
		break;

		/* диалог по прибытию на Тортугу */
		case "54":
			dialog.text = StringFromKey("JozefFushe_109");
			link.l1 = StringFromKey("JozefFushe_110");
			link.l1.go = "55";
		break;

		case "55":
			dialog.text = StringFromKey("JozefFushe_111");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "56";
		break;

		/* диалог возле резиденции Тортуги */
		case "56":
			DeleteAttribute(npchar, "talker");
			dialog.text = StringFromKey("JozefFushe_112");
			link.l1 = StringFromKey("JozefFushe_113");
			link.l1.go = "57";
		break;

		case "57":
			dialog.text = StringFromKey("JozefFushe_114");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "58";
			AddDialogExitQuest("FL4_s5");
		break;

		/* диалог в порту Тортуги после плена */
		case "58":
			dialog.text = StringFromKey("JozefFushe_115");
			link.l1 = StringFromKey("JozefFushe_116");
			link.l1.go = "exit";

			NextDiag.TempNode = "59";
		break;

		/* диалог в доме Фуше */
		case "59":
			dialog.text = StringFromKey("JozefFushe_117");
			link.l1 = StringFromKey("JozefFushe_118");
			link.l1.go = "60";
		break;

		case "60":
			dialog.text = StringFromKey("JozefFushe_119");
			link.l1 = StringFromKey("JozefFushe_120");
			link.l1.go = "61";
		break;

		case "61":
			dialog.text = StringFromKey("JozefFushe_121");
			link.l1 = StringFromKey("JozefFushe_122");
			link.l1.go = "62";
		break;

		case "62":
			dialog.text = StringFromKey("JozefFushe_123");
			link.l1 = StringFromKey("JozefFushe_124");
			link.l1.go = "63";
		break;

		case "63":
			dialog.text = StringFromKey("JozefFushe_125");
			if (CheckCharacterItem(pchar, "FQ_letter4"))
			{
				link.l1 = StringFromKey("JozefFushe_126");
				link.l1.go = "64";
			}
			else
			/* недописанная ветка с письмом капитана*/
			{
				link.l1 = StringFromKey("JozefFushe_127");
				link.l1.go = "exit";
			}
		break;

		case "64":
			dialog.text = StringFromKey("JozefFushe_128");
			link.l1 = StringFromKey("JozefFushe_129");
			link.l1.go = "65";
		break;

		case "65":
			dialog.text = StringFromKey("JozefFushe_130");
			link.l1 = StringFromKey("JozefFushe_131");
			link.l1.go = "66";
		break;

		case "66":
			TakeItemFromCharacter(pchar, "FQ_letter4");

			dialog.text = StringFromKey("JozefFushe_132");
			link.l1 = StringFromKey("JozefFushe_133");
			link.l1.go = "67";
		break;

		case "67":
			dialog.text = StringFromKey("JozefFushe_134");
			link.l1 = StringFromKey("JozefFushe_135");
			link.l1.go = "68";
		break;

		case "68":
			dialog.text = StringFromKey("JozefFushe_136");
			link.l1 = StringFromKey("JozefFushe_137");
			link.l1.go = "69";
		break;

		case "69":
			dialog.text = StringFromKey("JozefFushe_138");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "70";
			AddDialogExitQuest("FL4_s44");
		break;

		/* -------------------------------------------------------------------- */
		case "70":
			dialog.text = StringFromKey("JozefFushe_139");
			link.l1 = StringFromKey("JozefFushe_140");
			link.l1.go = "71";
		break;

		case "71":
			dialog.text = StringFromKey("JozefFushe_141");
			link.l1 = StringFromKey("JozefFushe_142");
			link.l1.go = "72";
		break;

		case "72":
			dialog.text = StringFromKey("JozefFushe_143");
			link.l1 = StringFromKey("JozefFushe_144");
			link.l1.go = "73";
		break;

		case "73":
			dialog.text = StringFromKey("JozefFushe_145");
			link.l1 = StringFromKey("JozefFushe_146");
			link.l1.go = "74";
		break;

		case "74":
			dialog.text = StringFromKey("JozefFushe_147");
			link.l1 = StringFromKey("JozefFushe_148");
			link.l1.go = "75";
		break;

		case "75":
			dialog.text = StringFromKey("JozefFushe_149");
			link.l1 = StringFromKey("JozefFushe_150");
			link.l1.go = "76";
		break;

		case "76":
			dialog.text = StringFromKey("JozefFushe_151");
			link.l1 = StringFromKey("JozefFushe_152");
			link.l1.go = "77";
		break;

		case "77":
			dialog.text = StringFromKey("JozefFushe_153");
			link.l1 = StringFromKey("JozefFushe_154");
			link.l1.go = "78";
		break;

		case "78":
			dialog.text = StringFromKey("JozefFushe_155");
			link.l1 = StringFromKey("JozefFushe_156");
			link.l1.go = "79";
		break;

		case "79":
			dialog.text = StringFromKey("JozefFushe_157");
			link.l1 = StringFromKey("JozefFushe_158");
			link.l1.go = "80";
		break;

		case "80":
			dialog.text = StringFromKey("JozefFushe_159");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "81";
			AddDialogExitQuest("FL5_s1");
		break;

		/* -------------------------------------------------------------------- */
		case "81":
			dialog.text = StringFromKey("JozefFushe_160");
			link.l1 = StringFromKey("JozefFushe_161");
			link.l1.go = "82";
		break;

		case "82":
			dialog.text = StringFromKey("JozefFushe_162");
			link.l1 = StringFromKey("JozefFushe_163");
			link.l1.go = "83";
		break;

		case "83":
			dialog.text = StringFromKey("JozefFushe_164");
			link.l1 = StringFromKey("JozefFushe_165");
			link.l1.go = "84";
		break;

		case "84":
			dialog.text = StringFromKey("JozefFushe_166");
			link.l1 = StringFromKey("JozefFushe_167");
			link.l1.go = "85";
		break;

		case "85":
			dialog.text = StringFromKey("JozefFushe_168");
			link.l1 = StringFromKey("JozefFushe_169");
			link.l1.go = "86";
		break;

		case "86":
			dialog.text = StringFromKey("JozefFushe_170");
			link.l1 = StringFromKey("JozefFushe_171");
			link.l1.go = "87";
		break;

		case "87":
			dialog.text = StringFromKey("JozefFushe_172");
			link.l1 = StringFromKey("JozefFushe_173");
			link.l1.go = "88";
		break;

		case "88":
			dialog.text = StringFromKey("JozefFushe_174");
			link.l1 = StringFromKey("JozefFushe_175");
			link.l1.go = "89";
		break;

		case "89":
			dialog.text = StringFromKey("JozefFushe_176");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "90";
			AddDialogExitQuest("FL5_s9");
		break;

		/* -------------------------------------------------------------------- */
		case "90":
			dialog.text = StringFromKey("JozefFushe_177");
			link.l1 = StringFromKey("JozefFushe_178");
			link.l1.go = "91";
		break;

		case "91":
			dialog.text = StringFromKey("JozefFushe_179");
			link.l1 = StringFromKey("JozefFushe_180");
			link.l1.go = "92";
		break;

		case "92":
			dialog.text = StringFromKey("JozefFushe_181");
			link.l1 = StringFromKey("JozefFushe_182");
			link.l1.go = "93";
		break;

		case "93":
			dialog.text = StringFromKey("JozefFushe_183");
			link.l1 = StringFromKey("JozefFushe_184");
			link.l1.go = "94";
		break;

		case "94":
			dialog.text = StringFromKey("JozefFushe_185");
			link.l1 = StringFromKey("JozefFushe_186");
			link.l1.go = "95";
		break;

		case "95":
			dialog.text = StringFromKey("JozefFushe_187");
			link.l1 = StringFromKey("JozefFushe_188");
			link.l1.go = "96";
		break;

		case "96":
			dialog.text = StringFromKey("JozefFushe_189");
			link.l1 = StringFromKey("JozefFushe_190");
			link.l1.go = "97";
		break;

		case "97":
			dialog.text = StringFromKey("JozefFushe_191");
			link.l1 = StringFromKey("JozefFushe_192");
			link.l1.go = "98";
		break;

		case "98":
			dialog.text = StringFromKey("JozefFushe_193");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "99";
		break;

		/* -------------------------------------------------------------------- */
		case "99":
			dialog.text = "...";
			link.l1 = StringFromKey("JozefFushe_194");
			link.l1.go = "100";
		break;

		case "100":
			dialog.text = StringFromKey("JozefFushe_195");
			link.l1 = StringFromKey("JozefFushe_196");
			link.l1.go = "101";
		break;

		case "101":
			dialog.text = StringFromKey("JozefFushe_197");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		/* -------------------------------------------------------------------- */
		case "102":
			dialog.text = StringFromKey("JozefFushe_198");
			link.l1 = StringFromKey("JozefFushe_199");
			link.l1.go = "103";
		break;

		case "103":
			dialog.text = StringFromKey("JozefFushe_200");
			link.l1 = StringFromKey("JozefFushe_201");
			link.l1.go = "104";
		break;

		case "104":
			dialog.text = StringFromKey("JozefFushe_202");
			link.l1 = StringFromKey("JozefFushe_203");
			link.l1.go = "105";
		break;

		case "105":
			dialog.text = StringFromKey("JozefFushe_204");
			link.l1 = StringFromKey("JozefFushe_205");
			link.l1.go = "exit";
			AddDialogExitQuest("FL5_s31");

			NextDiag.TempNode = "106";
		break;

		/* -------------------------------------------------------------------- */
		case "106":
			if (CheckAttribute(pchar, "mainQuest.CapCount") && sti(pchar.mainQuest.CapCount) < 1)
			{
				dialog.text = StringFromKey("JozefFushe_206");
				link.l1 = StringFromKey("JozefFushe_207");
				link.l1.go = "Exit";

				AddDialogExitQuest("FL5_s42a");
				break;
			}

			dialog.text = StringFromKey("JozefFushe_208");
			link.l1 = StringFromKey("JozefFushe_209");
			link.l1.go = "107";
		break;

		case "107":
			dialog.text = StringFromKey("JozefFushe_210");
			link.l1 = StringFromKey("JozefFushe_211");
			link.l1.go = "exit";

			AddDialogExitQuest("FL5_s42");
			NextDiag.TempNode = "108";
		break;

		case "108":
			dialog.text = "...";
			link.l1 = StringFromKey("JozefFushe_212");
			link.l1.go = "109";
		break;

		case "109":
			dialog.text = StringFromKey("JozefFushe_213");
			link.l1 = StringFromKey("JozefFushe_214");
			link.l1.go = "110";
		break;

		case "110":
			dialog.text = StringFromKey("JozefFushe_215");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		/* -------------------------------------------------------------------- */
		case "111":
			dialog.text = StringFromKey("JozefFushe_216");
			link.l1 = StringFromKey("JozefFushe_217");
			link.l1.go = "112";
		break;

		case "112":
			dialog.text = StringFromKey("JozefFushe_218");
			link.l1 = StringFromKey("JozefFushe_219");
			link.l1.go = "113";
		break;

		case "113":
			dialog.text = StringFromKey("JozefFushe_220");
			link.l1 = StringFromKey("JozefFushe_221");
			link.l1.go = "114";
		break;

		case "114":
			dialog.text = StringFromKey("JozefFushe_222");
			link.l1 = StringFromKey("JozefFushe_223");
			link.l1.go = "exit";

			NextDiag.TempNode = "115";
		break;

		/* -------------------------------------------------------------------- */
		case "115":
			chrDisableReloadTolocation = true;

			dialog.text = StringFromKey("JozefFushe_224");
			link.l1 = StringFromKey("JozefFushe_225");
			link.l1.go = "116";
		break;

		case "116":
			dialog.text = StringFromKey("JozefFushe_226");
			link.l1 = StringFromKey("JozefFushe_227");
			link.l1.go = "117";
		break;

		case "117":
			dialog.text = StringFromKey("JozefFushe_228");
			link.l1 = StringFromKey("JozefFushe_229");
			link.l1.go = "118";
		break;

		case "118":
			dialog.text = StringFromKey("JozefFushe_230");
			link.l1 = StringFromKey("JozefFushe_231");
			link.l1.go = "119";
		break;

		case "119":
			dialog.text = StringFromKey("JozefFushe_232");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "120";
			AddDialogExitQuest("FL6_5");
		break;

		case "120":
			dialog.text = StringFromKey("JozefFushe_233");
			link.l1 = StringFromKey("JozefFushe_234");
			link.l1.go = "121";
		break;

		case "121":
			dialog.text = StringFromKey("JozefFushe_235");
			link.l1 = StringFromKey("JozefFushe_236");
			link.l1.go = "122";
		break;

		case "122":
			dialog.text = StringFromKey("JozefFushe_237");
			link.l1 = StringFromKey("JozefFushe_238");
			link.l1.go = "exit";

			NextDiag.TempNode = "123";
			AddDialogExitQuest("FL6_7");
		break;

		/* -------------------------------------------------------------------- */
		case "123":
			dialog.text = StringFromKey("JozefFushe_239");
			link.l1 = StringFromKey("JozefFushe_240");
			link.l1.go = "124";
		break;

		case "124":
			dialog.text = StringFromKey("JozefFushe_241");
			link.l1 = StringFromKey("JozefFushe_242");
			link.l1.go = "125";
		break;

		case "125":
			dialog.text = StringFromKey("JozefFushe_243");
			link.l1 = StringFromKey("JozefFushe_244");
			link.l1.go = "126";
		break;

		case "126":
			dialog.text = StringFromKey("JozefFushe_245");
			link.l1 = StringFromKey("JozefFushe_246");
			link.l1.go = "127";
		break;

		case "127":
			dialog.text = StringFromKey("JozefFushe_247");
			link.l1 = StringFromKey("JozefFushe_248");
			link.l1.go = "128";
		break;

		case "128":
			dialog.text = StringFromKey("JozefFushe_249");
			link.l1 = StringFromKey("JozefFushe_250");
			link.l1.go = "129";
		break;

		case "129":
			dialog.text = StringFromKey("JozefFushe_251");
			link.l1 = StringFromKey("JozefFushe_252");
			link.l1.go = "130";
		break;

		case "130":
			dialog.text = StringFromKey("JozefFushe_253");
			link.l1 = StringFromKey("JozefFushe_254");
			link.l1.go = "131";
		break;

		case "131":
			dialog.text = StringFromKey("JozefFushe_255");
			link.l1 = StringFromKey("JozefFushe_256");
			link.l1.go = "132";
		break;

		case "132":
			dialog.text = StringFromKey("JozefFushe_257");
			link.l1 = StringFromKey("JozefFushe_258");
			link.l1.go = "133";
		break;

		case "133":
			dialog.text = StringFromKey("JozefFushe_259");
			link.l1 = StringFromKey("JozefFushe_260");
			link.l1.go = "134";
		break;

		case "134":
			dialog.text = StringFromKey("JozefFushe_261");
			link.l1 = StringFromKey("JozefFushe_262");
			link.l1.go = "135";
		break;

		case "135":
			dialog.text = StringFromKey("JozefFushe_263");
			link.l1 = StringFromKey("JozefFushe_264");
			link.l1.go = "136";
		break;

		case "136":
			dialog.text = StringFromKey("JozefFushe_265");
			link.l1 = StringFromKey("JozefFushe_266");
			link.l1.go = "137";
		break;

		case "137":
			dialog.text = StringFromKey("JozefFushe_267");
			link.l1 = StringFromKey("JozefFushe_268");
			link.l1.go = "138";
		break;

		case "138":
			dialog.text = StringFromKey("JozefFushe_269");
			link.l1 = StringFromKey("JozefFushe_270");
			link.l1.go = "exit";

			NextDiag.TempNode = "139";
			AddDialogExitQuest("FL6_s32");
		break;

		/* -------------------------------------------------------------------- */
		case "139":
			dialog.text = StringFromKey("JozefFushe_271");
			link.l1 = StringFromKey("JozefFushe_272");
			link.l1.go = "exit";

			NextDiag.TempNode = "140";
			AddDialogExitQuest("FL7_s3");
		break;

		/* -------------------------------------------------------------------- */
		case "140":
			dialog.text = StringFromKey("JozefFushe_273");
			link.l1 = StringFromKey("JozefFushe_274");
			link.l1.go = "exit";

			NextDiag.TempNode = "141";
		break;

		/* -------------------------------------------------------------------- */
		case "141":
			dialog.text = StringFromKey("JozefFushe_275");
			link.l1 = StringFromKey("JozefFushe_276");
			link.l1.go = "142";
		break;

		case "142":
			dialog.text = StringFromKey("JozefFushe_277");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "143";
		break;

		/* -------------------------------------------------------------------- */
		case "143":
			dialog.text = StringFromKey("JozefFushe_278");
			link.l1 = StringFromKey("JozefFushe_279");
			link.l1.go = "144";
		break;

		case "144":
			dialog.text = StringFromKey("JozefFushe_280");
			link.l1 = StringFromKey("JozefFushe_281");
			link.l1.go = "145";
		break;

		case "145":
			dialog.text = StringFromKey("JozefFushe_282");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "146";
		break;

		/* -------------------------------------------------------------------- */
		case "146":
			dialog.text = StringFromKey("JozefFushe_283");
			link.l1 = StringFromKey("JozefFushe_284");
			link.l1.go = "147";
		break;

		case "147":
			dialog.text = StringFromKey("JozefFushe_285");
			link.l1 = StringFromKey("JozefFushe_286");
			link.l1.go = "exit";

			NextDiag.TempNode = "149";
		break;

		/* -------------------------------------------------------------------- */
		case "149":
			dialog.text = StringFromKey("JozefFushe_287");
			link.l1 = StringFromKey("JozefFushe_288");
			link.l1.go = "150";
		break;

		case "150":
			dialog.text = StringFromKey("JozefFushe_289");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "151";
			AddDialogExitQuest("FL8_s1");
		break;

		case "151":
			dialog.text = StringFromKey("JozefFushe_290");
			link.l1 = StringFromKey("JozefFushe_291");
			link.l1.go = "152";
		break;

		case "152":
			dialog.text = StringFromKey("JozefFushe_292");
			link.l1 = StringFromKey("JozefFushe_293");
			link.l1.go = "153";
		break;

		case "153":
			dialog.text = StringFromKey("JozefFushe_294");
			link.l1 = StringFromKey("JozefFushe_295");
			link.l1.go = "154";
		break;

		case "154":
			dialog.text = StringFromKey("JozefFushe_296");
			link.l1 = StringFromKey("JozefFushe_297");
			link.l1.go = "155";
		break;

		case "155":
			dialog.text = StringFromKey("JozefFushe_298");
			link.l1 = StringFromKey("JozefFushe_299");
			link.l1.go = "156";
		break;

		case "156":
			dialog.text = StringFromKey("JozefFushe_300");
			link.l1 = "...";
			link.l1.go = "exit";

			NextDiag.TempNode = "157";
		break;

		/* -------------------------------------------------------------------- */
		case "157":
			dialog.text = StringFromKey("JozefFushe_301");
			link.l1 = StringFromKey("JozefFushe_302");
			link.l1.go = "158";
		break;

		case "158":
			dialog.text = StringFromKey("JozefFushe_303");
			link.l1 = StringFromKey("JozefFushe_304");
			link.l1.go = "159";
		break;

		case "159":
			dialog.text = StringFromKey("JozefFushe_305");
			link.l1 = StringFromKey("JozefFushe_306");
			link.l1.go = "160";
		break;

		case "160":
			dialog.text = StringFromKey("JozefFushe_307");
			link.l1 = StringFromKey("JozefFushe_308");
			link.l1.go = "161";
		break;

		case "161":
			dialog.text = StringFromKey("JozefFushe_309");
			link.l1 = StringFromKey("JozefFushe_310");
			link.l1.go = "exit";

			NextDiag.TempNode = "162";
			AddDialogExitQuest("FL8_s28");
		break;

		/* -------------------------------------------------------------------- */
		case "162":
			TakeItemFromCharacter(pchar, "FQ_letter8");
			dialog.text = StringFromKey("JozefFushe_311");
			link.l1 = StringFromKey("JozefFushe_312");
			link.l1.go = "exit";
			NextDiag.TempNode = "163";
			AddDialogExitQuest("FL9_s11");
		break;

		case "163":
			dialog.text = StringFromKey("JozefFushe_313");
			link.l1 = StringFromKey("JozefFushe_314");
			link.l1.go = "164";
		break;

		case "164":
			dialog.text = StringFromKey("JozefFushe_315");
			link.l1 = StringFromKey("JozefFushe_316");
			link.l1.go = "165";
		break;

		case "165":
			dialog.text = StringFromKey("JozefFushe_317");
			link.l1 = StringFromKey("JozefFushe_318");
			link.l1.go = "166";
		break;

		case "166":
			dialog.text = StringFromKey("JozefFushe_319");
			link.l1 = StringFromKey("JozefFushe_320");
			link.l1.go = "exit";

			NextDiag.TempNode = "167";
		break;

		/* -------------------------------------------------------------------- */
		case "167":
			dialog.text = StringFromKey("JozefFushe_321");
			link.l1 = StringFromKey("JozefFushe_322");
			link.l1.go = "168";
		break;

		case "168":
			dialog.text = StringFromKey("JozefFushe_323");
			link.l1 = "...";
			link.l1.go = "exit";

			AddDialogExitQuest("FL10_s2");
		break;

		/* -------------------------------------------------------------------- */
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;

		case "exit":
			if (CheckAttribute(NextDiag, "TempNode")) NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		/* -------------------------------------------------------------------- */
		/* блок обучения */
		case "First_man":
			dialog.text = StringFromKey("JozefFushe_324");
			link.l1 = StringFromKey("JozefFushe_325");
			link.l1.go = "Advice_2";
			link.l2 = StringFromKey("JozefFushe_326");
			link.l2.go = "41";
		break;

		case "Advice_2":
			dialog.text = StringFromKey("JozefFushe_327");
			link.l1 = StringFromKey("JozefFushe_328");
			link.l1.go = "Advice_3";
			link.l2 = StringFromKey("JozefFushe_329");
			link.l2.go = "41";
		break;

		case "Advice_3":
			dialog.text = StringFromKey("JozefFushe_330");
			link.l1 = StringFromKey("JozefFushe_331");
			link.l1.go = "Advice_4";
			link.l2 = StringFromKey("JozefFushe_332");
			link.l2.go = "41";
		break;

		case "Advice_4":
			dialog.text = StringFromKey("JozefFushe_333");
			link.l1 = StringFromKey("JozefFushe_334");
			link.l1.go = "Advice_5";
			link.l2 = StringFromKey("JozefFushe_335");
			link.l2.go = "41";
		break;

		case "Advice_5":
			dialog.text = StringFromKey("JozefFushe_336");
			link.l1 = StringFromKey("JozefFushe_337");
			link.l1.go = "Advice_6";
			link.l2 = StringFromKey("JozefFushe_338");
			link.l2.go = "41";
		break;

		case "Advice_6":
			dialog.text = StringFromKey("JozefFushe_339");
			link.l1 = StringFromKey("JozefFushe_340");
			link.l1.go = "Advice_7";
			link.l2 = StringFromKey("JozefFushe_341");
			link.l2.go = "41";
		break;

		case "Advice_7":
			dialog.text = StringFromKey("JozefFushe_342");
			link.l1 = StringFromKey("JozefFushe_343");
			link.l1.go = "Advice_8";
			link.l2 = StringFromKey("JozefFushe_344");
			link.l2.go = "41";
		break;

		case "Advice_8":
			dialog.text = StringFromKey("JozefFushe_345");
			link.l1 = StringFromKey("JozefFushe_346");
			link.l1.go = "Advice_9";
			link.l2 = StringFromKey("JozefFushe_347");
			link.l2.go = "41";
		break;

		case "Advice_9":
			dialog.text = StringFromKey("JozefFushe_348");
			link.l1 = StringFromKey("JozefFushe_349");
			link.l1.go = "Advice_10";
			link.l2 = StringFromKey("JozefFushe_350");
			link.l2.go = "41";
		break;

		case "Advice_10":
			dialog.text = StringFromKey("JozefFushe_351");
			link.l1 = StringFromKey("JozefFushe_352");
			link.l1.go = "41";
		break;
	}
}
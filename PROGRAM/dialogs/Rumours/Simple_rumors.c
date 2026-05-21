// Слухи - диалог по типажам
#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag)
{
	string srum, sAttr, RumText, sTemp;
	string posrep1, posrep2, answ1, answ2, answ3, answ4;
	aref aLinks, aTemp;
	ref sld;
	int iLinks, i, iTemp;
	int iNum = -1;
	float locx, locy, locz;
	switch (Dialog.CurrentNode)
	{
		//Поиск шпиона на улице, опрос свидетеля -->
		case "SeekSpy_Checking":
			dialog.text = StringFromKey("Simple_rumors_1", &characters[sti(pchar.genquest.seekspy.baseidx)]);
			link.l1 = StringFromKey("Simple_rumors_4", RandPhraseSimple(
						StringFromKey("Simple_rumors_2", pchar),
						StringFromKey("Simple_rumors_3")));
			link.l1.go = "SeekSpy_Checking_1";
		break;
		case "SeekSpy_Checking_1":
			switch (pchar.GenQuest.SeekSpy.Type)
			{
				case "guardian": LAi_SetGuardianTypeNoGroup(npchar); break;
				case "patrol":   LAi_SetPatrolTypeNoGroup(npchar);   break;
				case "citizen":  LAi_SetCitizenTypeNoGroup(npchar);  break;
				case "merchant": LAi_SetMerchantTypeNoGroup(npchar); break;
			}
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.GenQuest.SeekSpy.BaseIdx)]);
			NextDiag.CurrentNode = "First Time"; //TODO: после квестов монку, дворянину и маргиналу проверки на новую ноду
			DialogExit();
		break;
		//<-- Поиск шпиона на улице, опрос свидетеля

		case "rumours_citizen":
		//жемчужный генератор Шарпа -->
			if (CheckAttribute(NPChar, "city") && pchar.questTemp.Sharp.City == npchar.city && sti(pchar.questTemp.Sharp.City.rumour))
			{
				pchar.questTemp.Sharp.City.rumour = false; //слух дан
				if (pchar.questTemp.Sharp.SeekSpy == "begin") // если ищем в первый раз снимем мэйн-метки
				{
					RemoveLandQuestmarkToFantoms_Main("Citizen", "SharpPearl");
					RemoveLandQuestmarkToFantoms_Main("Commoner", "SharpPearl");
				}
				Dialog.Text = Sharp_choiceAction();
				link.l1 = StringFromKey("Simple_rumors_5");
				link.l1.go = "new question";
				link.l2 = StringFromKey("Simple_rumors_8", RandPhraseSimple(
							StringFromKey("Simple_rumors_6", pchar),
							StringFromKey("Simple_rumors_7")));
				link.l2.go = "exit";
				break;
			}
			//<-- жемчужный генератор Шарпа

			if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 3)
				srum = SelectRumourEx("citizen", NPChar, &iNum);
			else srum = NoRumourText(rand(SIMPLE_RUMOUR_NUM - 1)); // fix

			AddNPCInRumourGroup(iNum, NPChar);
			if (iNum == -1 || !RumourHaveReply(iNum))
			{
				if (RumourHasInformation(srum))
				{
					posrep1 = StringFromKey("Simple_rumors_11", RandPhraseSimple(
								" " + StringFromKey("Simple_rumors_9"),
								" " + StringFromKey("Simple_rumors_10")));
					posrep2 = StringFromKey("Simple_rumors_12");
					answ1 = StringFromKey("Simple_rumors_15", RandPhraseSimple(
								StringFromKey("Simple_rumors_13", RandSwear(), GetFullName(NPChar)),
								StringFromKey("Simple_rumors_14")));
					answ2 = StringFromKey("Simple_rumors_18", RandPhraseSimple(
								StringFromKey("Simple_rumors_16", pchar, RandSwear()),
								StringFromKey("Simple_rumors_17")));
					answ3 = StringFromKey("Simple_rumors_21", RandPhraseSimple(
								StringFromKey("Simple_rumors_19"),
								StringFromKey("Simple_rumors_20")));
					answ4 = "";
				}
				else
				{
					posrep1 = StringFromKey("Simple_rumors_22");
					posrep2 = StringFromKey("Simple_rumors_23", GetAddress_Form(NPChar));
					answ1 = StringFromKey("Simple_rumors_26", RandPhraseSimple(
								StringFromKey("Simple_rumors_24"),
								StringFromKey("Simple_rumors_25", pchar, RandSwear())));
					answ2 = StringFromKey("Simple_rumors_29", RandPhraseSimple(
								StringFromKey("Simple_rumors_27"),
								StringFromKey("Simple_rumors_28", npchar)));
					answ3 = StringFromKey("Simple_rumors_32", RandPhraseSimple(
								StringFromKey("Simple_rumors_30"),
								StringFromKey("Simple_rumors_31")));
					answ4 = "";

				}
				Dialog.Text = NPCStringReactionRepeat(srum, srum + " " + posrep1, srum + " " + posrep2,
						StringFromKey("Simple_rumors_35", RandPhraseSimple(
								StringFromKey("Simple_rumors_33"),
								StringFromKey("Simple_rumors_34"))), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(answ1,
						answ2,
						answ3,
						answ4,
						npchar, Dialog.CurrentNode);
				link.l1.go = "new question";
				link.l2 = StringFromKey("Simple_rumors_38", RandPhraseSimple(
							StringFromKey("Simple_rumors_36", pchar),
							StringFromKey("Simple_rumors_37")));
				link.l2.go = "exit";
				break;
			}
			makearef(aLinks, Rumour[iNum].link); //TODO: в остальные кейсы
			iLinks = GetAttributesNum(aLinks);
			Dialog.Text = srum;
			for (i = 1; i <= iLinks; i++)
			{
				sAttr = "l" + i;
				link.(sAttr) = aLinks.(sAttr);
				link.(sAttr).go = aLinks.(sAttr).go;
			}
		break;

		/////////////////////////////////////////////////---TODO---///////////////////////////////////////////////////
		//TODO: слухи темных личностей, мещан, мещанок, дворянок, ПГГ
		//TODO: отдельные реплики для простолюдинов
		//TODO: согласование key с выдачей особых слухов, вроде наводок и шаблонных слухов

		/////////////////////////////////////////////////---слухи мещан---////////////////////////////////////////////
		case "rumours_townman":
		break;

		/////////////////////////////////////////////////---слухи мещанок---////////////////////////////////////////////
		case "rumours_towngirl":
		break;

		/////////////////////////////////////////////////---слухи темных личностей---///////////////////////////////////
		case "rumours_marginal":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_marginal") || NPChar.quest.repeat.rumours_marginal != 2)
				srum = SelectRumourEx("citizen", NPChar, &iNum); //SelectRumourEx("marginal", NPChar);
			else srum = NoRumourText(rand(SIMPLE_RUMOUR_NUM - 1));
			if (RumourHasInformation(srum))
			{
				posrep1 = StringFromKey("Simple_rumors_41", RandPhraseSimple(
							" " + StringFromKey("Simple_rumors_39"),
							" " + StringFromKey("Simple_rumors_40")));
				posrep2 = StringFromKey("Simple_rumors_42");
				answ1 = StringFromKey("Simple_rumors_45", RandPhraseSimple(
							StringFromKey("Simple_rumors_43", RandSwear(), GetFullName(NPChar)),
							StringFromKey("Simple_rumors_44")));
				answ2 = StringFromKey("Simple_rumors_48", RandPhraseSimple(
							StringFromKey("Simple_rumors_46", pchar, RandSwear()),
							StringFromKey("Simple_rumors_47")));
				answ3 = StringFromKey("Simple_rumors_51", RandPhraseSimple(
							StringFromKey("Simple_rumors_49"),
							StringFromKey("Simple_rumors_50")));
				answ4 = "";
			}
			else
			{
				posrep1 = StringFromKey("Simple_rumors_52");
				posrep2 = StringFromKey("Simple_rumors_53", GetAddress_Form(NPChar));
				answ1 = StringFromKey("Simple_rumors_56", RandPhraseSimple(
							StringFromKey("Simple_rumors_54"),
							StringFromKey("Simple_rumors_55", pchar, RandSwear())));
				answ2 = StringFromKey("Simple_rumors_59", RandPhraseSimple(
							StringFromKey("Simple_rumors_57"),
							StringFromKey("Simple_rumors_58", npchar)));
				answ3 = StringFromKey("Simple_rumors_62", RandPhraseSimple(
							StringFromKey("Simple_rumors_60"),
							StringFromKey("Simple_rumors_61")));
				answ4 = "";
			}
			Dialog.Text = NPCStringReactionRepeat(srum, srum + posrep1, srum + posrep2,
					StringFromKey("Simple_rumors_65", RandPhraseSimple(
							StringFromKey("Simple_rumors_63"),
							StringFromKey("Simple_rumors_64"))), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(answ1,
					answ2,
					answ3,
					answ4,
					npchar, Dialog.CurrentNode);
			link.l1.go = "question";
			link.l2 = StringFromKey("Simple_rumors_68", RandPhraseSimple(
						StringFromKey("Simple_rumors_66", pchar),
						StringFromKey("Simple_rumors_67")));
			link.l2.go = "exit";
		break;

		/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
		case "rumours_nobleman":
			srum = SelectRumourEx("nobleman", NPChar, &iNum);
			if (RumourHasInformation(srum))
			{
				posrep1 = StringFromKey("Simple_rumors_71", RandPhraseSimple(
							StringFromKey("Simple_rumors_69"),
							StringFromKey("Simple_rumors_70")));
				posrep2 = StringFromKey("Simple_rumors_72");
				answ1 = StringFromKey("Simple_rumors_75", RandPhraseSimple(
							StringFromKey("Simple_rumors_73"),
							StringFromKey("Simple_rumors_74")));
				answ2 = StringFromKey("Simple_rumors_78", RandPhraseSimple(
							StringFromKey("Simple_rumors_76", pchar),
							StringFromKey("Simple_rumors_77")));
				answ3 = StringFromKey("Simple_rumors_81", RandPhraseSimple(
							StringFromKey("Simple_rumors_79"),
							StringFromKey("Simple_rumors_80")));
				answ4 = "";
			}
			else
			{
				posrep1 = StringFromKey("Simple_rumors_82");
				posrep2 = StringFromKey("Simple_rumors_83", GetAddress_Form(NPChar));
				answ1 = StringFromKey("Simple_rumors_86", RandPhraseSimple(
							StringFromKey("Simple_rumors_84"),
							StringFromKey("Simple_rumors_85", pchar, RandSwear())));
				answ2 = StringFromKey("Simple_rumors_89", RandPhraseSimple(
							StringFromKey("Simple_rumors_87"),
							StringFromKey("Simple_rumors_88", npchar)));
				answ3 = StringFromKey("Simple_rumors_92", RandPhraseSimple(
							StringFromKey("Simple_rumors_90"),
							StringFromKey("Simple_rumors_91")));
				answ4 = "";
			}
			Dialog.Text = NPCStringReactionRepeat(srum, srum + posrep1, srum + posrep2,
					StringFromKey("Simple_rumors_95", RandPhraseSimple(
							StringFromKey("Simple_rumors_93"),
							StringFromKey("Simple_rumors_94"))), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(answ1,
					answ2,
					answ3,
					answ4,
					npchar, Dialog.CurrentNode);
			link.l1.go = "question";
			link.l2 = StringFromKey("Simple_rumors_98", RandPhraseSimple(
						StringFromKey("Simple_rumors_96", pchar),
						StringFromKey("Simple_rumors_97")));
			link.l2.go = "exit";
		break;

		/////////////////////////////////////////////////---слухи дворянок---////////////////////////////////////////////
		case "rumours_noblegirl":
			srum = SelectRumourEx("citizen", NPChar, &iNum); //SelectRumourEx("noblegirl", NPChar);
			if (RumourHasInformation(srum))
			{
				posrep1 = StringFromKey("Simple_rumors_101", RandPhraseSimple(
							" " + StringFromKey("Simple_rumors_99"),
							" " + StringFromKey("Simple_rumors_100")));
				posrep2 = StringFromKey("Simple_rumors_102");
				answ1 = StringFromKey("Simple_rumors_105", RandPhraseSimple(
							StringFromKey("Simple_rumors_103"),
							StringFromKey("Simple_rumors_104")));
				answ2 = StringFromKey("Simple_rumors_108", RandPhraseSimple(
							StringFromKey("Simple_rumors_106", pchar),
							StringFromKey("Simple_rumors_107")));
				answ3 = StringFromKey("Simple_rumors_111", RandPhraseSimple(
							StringFromKey("Simple_rumors_109"),
							StringFromKey("Simple_rumors_110")));
				answ4 = "";
			}
			else
			{
				posrep1 = StringFromKey("Simple_rumors_112");
				posrep2 = StringFromKey("Simple_rumors_113", GetAddress_Form(NPChar));
				answ1 = StringFromKey("Simple_rumors_116", RandPhraseSimple(
							StringFromKey("Simple_rumors_114"),
							StringFromKey("Simple_rumors_115", pchar, RandSwear())));
				answ2 = StringFromKey("Simple_rumors_119", RandPhraseSimple(
							StringFromKey("Simple_rumors_117"),
							StringFromKey("Simple_rumors_118", npchar)));
				answ3 = StringFromKey("Simple_rumors_122", RandPhraseSimple(
							StringFromKey("Simple_rumors_120"),
							StringFromKey("Simple_rumors_121")));
				answ4 = "";
			}
			Dialog.Text = NPCStringReactionRepeat(srum, srum + posrep1, srum + posrep2,
					StringFromKey("Simple_rumors_125", RandPhraseSimple(
							StringFromKey("Simple_rumors_123"),
							StringFromKey("Simple_rumors_124"))), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(answ1,
					answ2,
					answ3,
					answ4,
					npchar, Dialog.CurrentNode);
			link.l1.go = "question";
			link.l2 = StringFromKey("Simple_rumors_128", RandPhraseSimple(
						StringFromKey("Simple_rumors_126", pchar),
						StringFromKey("Simple_rumors_127")));
			link.l2.go = "exit";
		break;

		/////////////////////////////////////////////////---слухи матросов---////////////////////////////////////////////
		case "rumours_sailor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_sailor") || NPChar.quest.repeat.rumours_sailor != 2) srum = SelectRumourEx("sailor", NPChar, &iNum);
			else srum = NoRumourText(rand(SIMPLE_RUMOUR_NUM - 1)); // fix
			if (RumourHasInformation(srum))
			{
				posrep1 = StringFromKey("Simple_rumors_131", RandPhraseSimple(
							" " + StringFromKey("Simple_rumors_129"),
							" " + StringFromKey("Simple_rumors_130")));
				posrep2 = StringFromKey("Simple_rumors_132");
				answ1 = StringFromKey("Simple_rumors_135", RandPhraseSimple(
							StringFromKey("Simple_rumors_133", RandSwear(), GetFullName(NPChar)),
							StringFromKey("Simple_rumors_134")));
				answ2 = StringFromKey("Simple_rumors_138", RandPhraseSimple(
							StringFromKey("Simple_rumors_136", pchar, RandSwear()),
							StringFromKey("Simple_rumors_137")));
				answ3 = StringFromKey("Simple_rumors_141", RandPhraseSimple(
							StringFromKey("Simple_rumors_139"),
							StringFromKey("Simple_rumors_140")));
				answ4 = "";
			}
			else
			{
				posrep1 = StringFromKey("Simple_rumors_142");
				posrep2 = StringFromKey("Simple_rumors_143", GetAddress_Form(NPChar));
				answ1 = StringFromKey("Simple_rumors_146", RandPhraseSimple(
							StringFromKey("Simple_rumors_144"),
							StringFromKey("Simple_rumors_145", pchar, RandSwear())));
				answ2 = StringFromKey("Simple_rumors_149", RandPhraseSimple(
							StringFromKey("Simple_rumors_147"),
							StringFromKey("Simple_rumors_148", npchar)));
				answ3 = StringFromKey("Simple_rumors_152", RandPhraseSimple(
							StringFromKey("Simple_rumors_150"),
							StringFromKey("Simple_rumors_151")));
				answ4 = "";
			}
			Dialog.Text = NPCStringReactionRepeat(srum, srum + posrep1, srum + posrep2,
					StringFromKey("Simple_rumors_155", RandPhraseSimple(
							StringFromKey("Simple_rumors_153"),
							StringFromKey("Simple_rumors_154"))), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(answ1,
					answ2,
					answ3,
					answ4,
					npchar, Dialog.CurrentNode);
			link.l1.go = "question";
			link.l2 = StringFromKey("Simple_rumors_158", RandPhraseSimple(
						StringFromKey("Simple_rumors_156", pchar),
						StringFromKey("Simple_rumors_157")));
			link.l2.go = "exit";
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_habitue":
			srum = SelectRumourEx("habitue", NPChar, &iNum);
			Dialog.Text = StringFromKey("Simple_rumors_162", LinkRandPhrase(
						StringFromKey("Simple_rumors_159"),
						StringFromKey("Simple_rumors_160"),
						StringFromKey("Simple_rumors_161")), srum);
			link.l1 = StringFromKey("Simple_rumors_165", RandPhraseSimple(
						StringFromKey("Simple_rumors_163", RandSwear()),
						StringFromKey("Simple_rumors_164")));
			link.l1.go = "sit_3";
			link.l2 = StringFromKey("Simple_rumors_168", RandPhraseSimple(
						StringFromKey("Simple_rumors_166", pchar),
						StringFromKey("Simple_rumors_167")));
			link.l2.go = "exit_sit";
			if (RumourHasInformation(srum))
			{
				break;
			}
			if (pchar.questTemp.piratesLine == "PL5Hunter_toFirst" && npchar.location == pchar.questTemp.piratesLine.Q5.city_1 + "_tavern")
			{
				dialog.text = StringFromKey("Simple_rumors_169");
				link.l1 = StringFromKey("Simple_rumors_170");
				link.l1.go = "sit_3";
				AddQuestRecord("Pir_Line_5_Hunter", "3");
				AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_1 + "Gen"));
				pchar.questTemp.piratesLine = "PL5Hunter_toFirstUsurer";
				RemoveLandQuestMarkToFantoms_Main("habitue", "Pir_Line");
			}
			if (pchar.questTemp.piratesLine == "PL5Hunter_toSecond" && npchar.location == pchar.questTemp.piratesLine.Q5.city_2 + "_tavern")
			{
				dialog.text = StringFromKey("Simple_rumors_171");
				link.l1 = StringFromKey("Simple_rumors_172");
				link.l1.go = "sit_3";
				AddQuestRecord("Pir_Line_5_Hunter", "5");
				AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_2 + "Gen"));
				pchar.questTemp.piratesLine = "PL5Hunter_toSecondUsurer";
				RemoveLandQuestMarkToFantoms_Main("habitue", "Pir_Line");
			}
			if (pchar.questTemp.piratesLine == "PL5Hunter_toThird" && npchar.location == pchar.questTemp.piratesLine.Q5.city_3 + "_tavern")
			{
				dialog.text = StringFromKey("Simple_rumors_173");
				link.l1 = StringFromKey("Simple_rumors_174");
				link.l1.go = "sit_3";
				AddQuestRecord("Pir_Line_5_Hunter", "7");
				AddQuestUserData("Pir_Line_5_Hunter", "sCity", XI_ConvertString("Colony" + pchar.questTemp.piratesLine.Q5.city_3 + "Gen"));
				pchar.questTemp.piratesLine = "PL5Hunter_toThirdUsurer";
				RemoveLandQuestMarkToFantoms_Main("habitue", "Pir_Line");
			}
			//-->работорговец
			if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
			{
				dialog.text = StringFromKey("Simple_rumors_175", pchar);
				link.l1 = StringFromKey("Simple_rumors_176");
				link.l1.go = "Jamaica_ratH_1";
			}
			if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
			{
				dialog.text = StringFromKey("Simple_rumors_177", pchar);
				link.l1 = StringFromKey("Simple_rumors_178");
				link.l1.go = "EscapeSlave_Villemstad_H1";
			}
			//<--работорговец

			//ОЗГ, Крыса
			if (CheckAttribute(pchar, "questTemp.Headhunter"))
			{
				if (pchar.questTemp.Headhunter == "Rat_Tavern" && npchar.location == pchar.questTemp.Headhunter.Ratrumcity + "_tavern")
				{
					dialog.text = StringFromKey("Simple_rumors_179", pchar);
					link.l1 = StringFromKey("Simple_rumors_180");
					link.l1.go = "Rat_Tavern_1";
				}
			}
			//<--ОЗГ, Крыса

			//Поиск ловцов жемчуга, Шарп
			if (CheckAttribute(pchar, "questTemp.Sharp") && pchar.questTemp.Sharp == "begin" && sti(pchar.rank) >= 5)
			{
				dialog.text = DefaultText(10); // текст из Rumour_Data_11
				link.l1 = StringFromKey("Simple_rumors_181");
				link.l1.go = "SeekSharp_Tavern_1";
			}
			//<--Поиск ловцов жемчуга, Шарп

			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				dialog.text = StringFromKey("Simple_rumors_182", GetAddress_Form(pchar));
				link.l1 = StringFromKey("Simple_rumors_183");
				link.l1.go = "Alcogol_GenQuest_Church_2_1";
			}
		break;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader != 3)
				srum = SelectRumourEx("trader", NPChar, &iNum);
			else srum = NoRumourText(rand(SIMPLE_RUMOUR_NUM - 1)); // fix
			Dialog.Text = NPCStringReactionRepeat(srum,
					StringFromKey("Simple_rumors_184", srum),
					StringFromKey("Simple_rumors_185", srum),
					StringFromKey("Simple_rumors_188", RandPhraseSimple(
							StringFromKey("Simple_rumors_186"),
							StringFromKey("Simple_rumors_187"))), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						pcharrepphrase(
								StringFromKey("Simple_rumors_189", RandSwear()),
								StringFromKey("Simple_rumors_190")),
						pcharrepphrase(
								StringFromKey("Simple_rumors_191", pchar),
								StringFromKey("Simple_rumors_192")),
						pcharrepphrase(
								StringFromKey("Simple_rumors_193", RandSwear()),
								StringFromKey("Simple_rumors_194")),
						pcharrepphrase(
								StringFromKey("Simple_rumors_195"),
								StringFromKey("Simple_rumors_196")), npchar, Dialog.CurrentNode);

			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Simple_rumors_197"),
									StringFromKey("Simple_rumors_198", GetAddress_FormToNPC(NPChar), GetFullName(npchar))),
							pcharrepphrase(
									StringFromKey("Simple_rumors_199"),
									StringFromKey("Simple_rumors_200", GetAddress_FormToNPC(NPChar), GetFullName(npchar)))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Simple_rumors_201"),
									StringFromKey("Simple_rumors_202")),
							pcharrepphrase(
									StringFromKey("Simple_rumors_203"),
									StringFromKey("Simple_rumors_204"))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Simple_rumors_205"),
									StringFromKey("Simple_rumors_206", GetAddress_FormToNPC(NPChar), GetFullName(npchar))),
							pcharrepphrase(
									StringFromKey("Simple_rumors_207"),
									StringFromKey("Simple_rumors_208", GetAddress_FormToNPC(NPChar), GetFullName(npchar)))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Simple_rumors_209", GetFullName(pchar)),
									StringFromKey("Simple_rumors_210")),
							pcharrepphrase(
									StringFromKey("Simple_rumors_211"),
									StringFromKey("Simple_rumors_212", pchar, GetAddress_FormToNPC(NPChar), GetFullName(npchar)))), npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_capitan":
			NextDiag.TempNode = "quests";
			NPChar.talk_date = lastspeakdate();
			srum = SelectRumourEx("capitan", NPChar, &iNum);
			if (RumourHasInformation(srum))
			{
				posrep1 = StringFromKey("Simple_rumors_215", RandPhraseSimple(
							" " + StringFromKey("Simple_rumors_213"),
							" " + StringFromKey("Simple_rumors_214")));
				posrep2 = StringFromKey("Simple_rumors_216");
				answ1 = StringFromKey("Simple_rumors_219", RandPhraseSimple(
							StringFromKey("Simple_rumors_217"),
							StringFromKey("Simple_rumors_218")));
				answ2 = StringFromKey("Simple_rumors_222", RandPhraseSimple(
							StringFromKey("Simple_rumors_220", pchar),
							StringFromKey("Simple_rumors_221")));
				answ3 = StringFromKey("Simple_rumors_225", RandPhraseSimple(
							StringFromKey("Simple_rumors_223"),
							StringFromKey("Simple_rumors_224")));
				answ4 = "";
			}
			else
			{
				posrep1 = StringFromKey("Simple_rumors_226");
				posrep2 = StringFromKey("Simple_rumors_227");
				answ1 = StringFromKey("Simple_rumors_230", RandPhraseSimple(
							StringFromKey("Simple_rumors_228"),
							StringFromKey("Simple_rumors_229", pchar, RandSwear())));
				answ2 = StringFromKey("Simple_rumors_233", RandPhraseSimple(
							StringFromKey("Simple_rumors_231"),
							StringFromKey("Simple_rumors_232")));
				answ3 = StringFromKey("Simple_rumors_236", RandPhraseSimple(
							StringFromKey("Simple_rumors_234"),
							StringFromKey("Simple_rumors_235")));
				answ4 = "";
			}
			Dialog.Text = NPCStringReactionRepeat(srum, srum + posrep1, srum + posrep2,
					StringFromKey("Simple_rumors_239", RandPhraseSimple(
							StringFromKey("Simple_rumors_237"),
							StringFromKey("Simple_rumors_238"))), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(answ1,
					answ2,
					answ3,
					answ4,
					npchar, Dialog.CurrentNode);
			link.l1.go = "quests";
			link.l2 = StringFromKey("Simple_rumors_242", RandPhraseSimple(
						StringFromKey("Simple_rumors_240", pchar),
						StringFromKey("Simple_rumors_241")));
			link.l2.go = "exit";
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
			Dialog.Text = NPCStringReactionRepeat(
						StringFromKey("Simple_rumors_246", LinkRandPhrase(
								StringFromKey("Simple_rumors_243"),
								StringFromKey("Simple_rumors_244"),
								StringFromKey("Simple_rumors_245"))),
						StringFromKey("Simple_rumors_247"), "", "", "block", 1, npchar, Dialog.CurrentNode);

			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Simple_rumors_250", RandPhraseSimple(
								StringFromKey("Simple_rumors_248", RandSwear()),
								StringFromKey("Simple_rumors_249", pchar))),
						StringFromKey("Simple_rumors_251"),
						StringFromKey("Simple_rumors_252"),
						StringFromKey("Simple_rumors_253"), npchar, Dialog.CurrentNode);
			link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
			NextDiag.CurrentNode = NextDiag.TempNode;
			if (makeint(pchar.money) >= 1000)
			{
				link.l2 = HeroStringReactionRepeat(
							StringFromKey("Simple_rumors_256", RandPhraseSimple(
									StringFromKey("Simple_rumors_254"),
									StringFromKey("Simple_rumors_255"))), "", "", "", npchar, Dialog.CurrentNode);
				link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			}
			else
			{
				link.l2 = HeroStringReactionRepeat(
					StringFromKey("Simple_rumors_257"), "", "", "", npchar, Dialog.CurrentNode);
				link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
			}
		break;

		case "rumours_tavern_yes":
		//------------- квестовые слухи тавернщика --------->>>>>>>>
		//пиратка, квест №3
			if (pchar.questTemp.piratesLine == "KillLoy_toCumana")
			{
				Dialog.Text = StringFromKey("Simple_rumors_258");
				link.l1 = StringFromKey("Simple_rumors_259");
				link.l1.go = "rumours_tavern";
				AddQuestRecord("Pir_Line_3_KillLoy", "14");
				AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("", "а"));
				pchar.questTemp.piratesLine = "KillLoy_toCumana_2";
				PiratesLine_q3_RemoveQuestMarksToTavernkeepers();
				break;
			}
			//ОЗГ, Крыса на Тортуге
			if (CheckAttribute(pchar, "questTemp.Headhunter") && pchar.questTemp.Headhunter == "Rat_tortuga" && npchar.location == "Tortuga_tavern")
			{
				Dialog.Text = StringFromKey("Simple_rumors_260");
				link.l1 = StringFromKey("Simple_rumors_261");
				link.l1.go = "rumours_tavern";
				pchar.quest.Headhunter_PinasseTortugaOver.over = "yes";
				AddQuestRecord("Headhunt", "17");
				pchar.questTemp.Headhunter = "Rat_officer";
				if (!IsEntity(&Characters[GetCharacterIndex("RatOfficer")]))
				{
					FreeSitLocator("Tortuga_tavern", "sit2");
					CreateRatOfficer();
				}
				SetFunctionTimerCondition("Headhunter_RatOfficerOver", 0, 0, 3, false); //таймер
				RemoveLandQuestMark_Main(npchar, "Headhunt");
				AddLandQuestMark_Main(CharacterFromID("RatOfficer"), "Headhunt");
				break;
			}
			//ОЗГ, Крыса на Тортуге
			//<<<<<-------- квестовые слухи тавернщика -----------------

			RumText = SelectRumourEx("tavern", NPChar, &iNum);

			if (!RumourHasInformation(RumText))
			{
				Dialog.Text = NoRumourText(rand(SIMPLE_RUMOUR_NUM - 1)); //fix
				link.l1 = StringFromKey("Simple_rumors_264", RandPhraseSimple(
							StringFromKey("Simple_rumors_262"),
							StringFromKey("Simple_rumors_263")));

				link.l1.go = "Exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
				//  link.l2 = LinkRandPhrase("Спасибо, долж"+ GetSexPhrase("ен","на") +" откланяться.",
				//                       "Всего хорошего","Спасибо, мне пора. До свидания.");
				//  link.l2.go = "Exit";
			}
			else
			{

				AddMoneyToCharacter(pchar, -1000);

				Dialog.Text = RumText;

				link.l1 = StringFromKey("Simple_rumors_267", RandPhraseSimple(
							StringFromKey("Simple_rumors_265"),
							StringFromKey("Simple_rumors_266")));

				link.l1.go = "rumours_tavern";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}

		break;

		case "rumours_tavern_no":
			Dialog.Text = StringFromKey("Simple_rumors_268");
			link.l1 = StringFromKey("Simple_rumors_269");
			link.l1.go = "first time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			link.l2 = StringFromKey("Simple_rumors_273", LinkRandPhrase(
						StringFromKey("Simple_rumors_270", pchar),
						StringFromKey("Simple_rumors_271"),
						StringFromKey("Simple_rumors_272")));
			link.l2.go = "Exit";
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar, &iNum);
				Link.l1 = StringFromKey("Simple_rumors_276", RandPhraseSimple(
							StringFromKey("Simple_rumors_274", RandSwear()),
							StringFromKey("Simple_rumors_275", pchar)));
				Link.l1.go = "rumours_poor_2";
				Link.l2 = StringFromKey("Simple_rumors_279", RandPhraseSimple(
							StringFromKey("Simple_rumors_277"),
							StringFromKey("Simple_rumors_278")));
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else
			{
				Dialog.Text = StringFromKey("Simple_rumors_282", RandPhraseSimple(
							StringFromKey("Simple_rumors_280"),
							StringFromKey("Simple_rumors_281")));
				Link.l1 = StringFromKey("Simple_rumors_285", RandPhraseSimple(
							StringFromKey("Simple_rumors_283"),
							StringFromKey("Simple_rumors_284")));
				Link.l1.go = "exit";
			}
			NPChar.talk_date = lastspeakdate();
		break;
		case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar, &iNum);
				Link.l1 = StringFromKey("Simple_rumors_288", RandPhraseSimple(
							StringFromKey("Simple_rumors_286", RandSwear()),
							StringFromKey("Simple_rumors_287", pchar)));
				Link.l1.go = "rumours_poor";
				Link.l2 = StringFromKey("Simple_rumors_291", RandPhraseSimple(
							StringFromKey("Simple_rumors_289"),
							StringFromKey("Simple_rumors_290")));
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else
			{
				Dialog.Text = StringFromKey("Simple_rumors_294", RandPhraseSimple(
							StringFromKey("Simple_rumors_292"),
							StringFromKey("Simple_rumors_293")));
				Link.l1 = StringFromKey("Simple_rumors_297", RandPhraseSimple(
							StringFromKey("Simple_rumors_295"),
							StringFromKey("Simple_rumors_296")));
				Link.l1.go = "exit";
			}
			NPChar.talk_date = lastspeakdate();
		break;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar, &iNum);
				Link.l1 = StringFromKey("Simple_rumors_300", RandPhraseSimple(
							StringFromKey("Simple_rumors_298"),
							StringFromKey("Simple_rumors_299")));
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else
			{
				Dialog.Text = StringFromKey("Simple_rumors_303", RandPhraseSimple(
							StringFromKey("Simple_rumors_301", npchar),
							StringFromKey("Simple_rumors_302", npchar)));
				Link.l1 = StringFromKey("Simple_rumors_306", RandPhraseSimple(
							StringFromKey("Simple_rumors_304", pchar),
							StringFromKey("Simple_rumors_305")));
				Link.l1.go = "exit";
			}
		break;

		//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по одному в день--------------------
		case "rumours_lighthouse":
			Dialog.Text = NPCStringReactionRepeat(
						StringFromKey("Simple_rumors_309", RandPhraseSimple(
								StringFromKey("Simple_rumors_307"),
								StringFromKey("Simple_rumors_308"))),
						StringFromKey("Simple_rumors_310"),
						StringFromKey("Simple_rumors_311"),
						StringFromKey("Simple_rumors_312"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Simple_rumors_315", RandPhraseSimple(
								StringFromKey("Simple_rumors_313", pchar),
								StringFromKey("Simple_rumors_314"))),
						StringFromKey("Simple_rumors_316"),
						StringFromKey("Simple_rumors_317"),
						StringFromKey("Simple_rumors_318"), npchar, Dialog.CurrentNode);
			link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;

		case "rumours_lighthouse_yes":
			RumText = SelectRumourEx("tavern", NPChar, &iNum);
			if (!RumourHasInformation(RumText))
			{
				Dialog.Text = NoRumourText(rand(SIMPLE_RUMOUR_NUM - 1));
				link.l1 = StringFromKey("Simple_rumors_321", RandPhraseSimple(
							StringFromKey("Simple_rumors_319"),
							StringFromKey("Simple_rumors_320")));

				link.l1.go = "rumours_lighthouse";
				link.l2 = StringFromKey("Simple_rumors_324", RandPhraseSimple(
							StringFromKey("Simple_rumors_322"),
							StringFromKey("Simple_rumors_323")));
				link.l2.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = RumText;
				link.l1 = StringFromKey("Simple_rumors_327", RandPhraseSimple(
							StringFromKey("Simple_rumors_325"),
							StringFromKey("Simple_rumors_326")));
				link.l1.go = "rumours_lighthouse";
				link.l2 = StringFromKey("Simple_rumors_330", RandPhraseSimple(
							StringFromKey("Simple_rumors_328"),
							StringFromKey("Simple_rumors_329")));
				link.l2.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;

		case "rumours_lighthouse_void":
			Dialog.Text = NoRumourText(rand(SIMPLE_RUMOUR_NUM - 1));
			link.l1 = StringFromKey("Simple_rumors_333", RandPhraseSimple(
						StringFromKey("Simple_rumors_331"),
						StringFromKey("Simple_rumors_332")));

			link.l1.go = "rumours_lighthouse";
			link.l2 = StringFromKey("Simple_rumors_336", RandPhraseSimple(
						StringFromKey("Simple_rumors_334"),
						StringFromKey("Simple_rumors_335")));
			link.l2.go = "exit";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////		Rosarak. Диалоги по квестовым слухам
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////		Кредитный генератор Loan
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "LoanForAll": //пересылка в финансы для всех
			dialog.text = StringFromKey("Simple_rumors_340", LinkRandPhrase(
						StringFromKey("Simple_rumors_337"),
						StringFromKey("Simple_rumors_338"),
						StringFromKey("Simple_rumors_339")));
			if (CheckAttribute(pchar, "GenQuest.Loan.FindCitizen") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenDone") && !CheckAttribute(pchar, "GenQuest.Loan.FindCitizenFalied"))
			{
				if (Characters[sti(pchar.GenQuest.Loan.FindCitizenIdx)].id == Npchar.id)
				{
					dialog.text = StringFromKey("Simple_rumors_344", LinkRandPhrase(
								StringFromKey("Simple_rumors_341", GetAddress_Form(NPChar), GetFullName(npchar)),
								StringFromKey("Simple_rumors_342", GetAddress_Form(NPChar), GetFullName(npchar)),
								StringFromKey("Simple_rumors_343", GetAddress_Form(NPChar), GetFullName(npchar))));
					link.l1 = NPCharRepPhrase(pchar,
							StringFromKey("Simple_rumors_345"),
							StringFromKey("Simple_rumors_346", GetAddress_FormToNPC(NPChar)));
					link.l1.go = "LoanFindCitizen_1";
					NPChar.quest.LoanFindCitizenType = rand(2); // три типа
					break;
				}
			}
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l2 = StringFromKey("Simple_rumors_347", pchar);
				link.l2.go = "TakeChest_2";
			}
			link.l9 = StringFromKey("Simple_rumors_350", RandPhraseSimple(
						StringFromKey("Simple_rumors_348", pchar),
						StringFromKey("Simple_rumors_349")));
			link.l9.go = "exit";
		break;
		// вернуть долг ростовщику
		case "LoanFindCitizen_1":
			switch (sti(pchar.GenQuest.Loan.FindCitizenChance1))
			{
				case 0 :
					dialog.text = StringFromKey("Simple_rumors_351");
					Link.l1 = StringFromKey("Simple_rumors_352", FindMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))));
					Link.l1.go = "LoanFindCitizenType_0";
					Link.l2 = StringFromKey("Simple_rumors_353");
					Link.l2.go = "exit";
				break;

				case 1 :
					dialog.text = StringFromKey("Simple_rumors_354");
					Link.l1 = StringFromKey("Simple_rumors_355", FindMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))));
					Link.l1.go = "LoanFindCitizenType_1";
					Link.l2 = StringFromKey("Simple_rumors_356");
					Link.l2.go = "LoanFindCitizenType_1_1";
				break;

				case 2 :
					dialog.text = StringFromKey("Simple_rumors_357");
					Link.l1 = StringFromKey("Simple_rumors_358", FindMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))));
					Link.l1.go = "LoanFindCitizen_1_1";
					Link.l2 = StringFromKey("Simple_rumors_359");
					Link.l2.go = "LoanFindCitizenType_2";
				//NPChar.quest.LoanFindCitizenType = rand(1);// первые 2 типа
				break;
			}
		break;

		case "LoanFindCitizen_1_1":
			switch (sti(pchar.GenQuest.Loan.FindCitizenChance2))
			{
				case 0 :
					dialog.text = StringFromKey("Simple_rumors_360");
					Link.l1 = StringFromKey("Simple_rumors_361", FindMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))));
					Link.l1.go = "LoanFindCitizenType_0";
					Link.l2 = StringFromKey("Simple_rumors_362");
					Link.l2.go = "exit";
				break;

				case 1 :
					dialog.text = StringFromKey("Simple_rumors_363");
					Link.l1 = StringFromKey("Simple_rumors_364", FindMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))));
					Link.l1.go = "LoanFindCitizenType_1";
					Link.l2 = StringFromKey("Simple_rumors_365");
					Link.l2.go = "LoanFindCitizenType_1_1";
				break;
			}
		break;

		case "LoanFindCitizen_1_2":
			switch (sti(pchar.GenQuest.Loan.FindCitizenChance3))
			{
				case 0 :
					dialog.text = StringFromKey("Simple_rumors_366");
					Link.l1 = StringFromKey("Simple_rumors_367", FindMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))));
					Link.l1.go = "LoanFindCitizenType_0";
					Link.l2 = StringFromKey("Simple_rumors_368");
					Link.l2.go = "exit";
				break;

				case 1 :
					dialog.text = StringFromKey("Simple_rumors_369");
					Link.l1 = StringFromKey("Simple_rumors_370", FindMoneyString(makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent))));
					Link.l1.go = "LoanFindCitizenType_1";
					Link.l2 = StringFromKey("Simple_rumors_371");
					Link.l2.go = "LoanFindCitizenType_1_1";
				break;
			}
		break;

		case "LoanFindCitizenType_0":
			dialog.text = StringFromKey("Simple_rumors_372");
			Link.l1 = StringFromKey("Simple_rumors_373");
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenDone = true;
			addMoneyToCharacter(Pchar, (sti(pchar.GenQuest.Loan.FindCitizenMoney) + sti(pchar.GenQuest.Loan.FindCitizenPercent)));
			SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
			Log_SetStringToLog(StringFromKey("InfoMessages_194"));
			AddCharacterExpToSkill(pchar, "COMMERCE", 100);
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddQuestRecord("Gen_LoanFindCitizen", "3");
			npchar.LifeDay = 0;
		break;

		case "LoanFindCitizenType_1_1":
			dialog.text = StringFromKey("Simple_rumors_374");
			Link.l1 = StringFromKey("Simple_rumors_375");
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenFalied = true;
			SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
			Log_SetStringToLog(StringFromKey("InfoMessages_195"));
			AddQuestRecord("Gen_LoanFindCitizen", "2");
			npchar.LifeDay = 0;
		break;

		case "LoanFindCitizenType_1":
			dialog.text = StringFromKey("Simple_rumors_376", pchar);
			Link.l1 = StringFromKey("Simple_rumors_377");
			Link.l1.go = "fight";
			pchar.GenQuest.Loan.FindCitizenFalied = true;
			SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
			Log_SetStringToLog(StringFromKey("InfoMessages_195"));
			AddQuestRecord("Gen_LoanFindCitizen", "2");
			npchar.LifeDay = 0;
			AddCharacterExpToSkill(pchar, "Sneak", 150);
		break;

		case "LoanFindCitizenType_2":
			pchar.GenQuest.Loan.FindCitizenTempMoney = makeint(sti(pchar.GenQuest.Loan.FindCitizenMoney) - rand(sti(pchar.GenQuest.Loan.FindCitizenPercent)));
			dialog.text = StringFromKey("Simple_rumors_378", FindMoneyString(sti(pchar.GenQuest.Loan.FindCitizenTempMoney)));
			Link.l1 = StringFromKey("Simple_rumors_379");
			Link.l1.go = "LoanFindCitizen_1_2";
			Link.l2 = StringFromKey("Simple_rumors_380", pchar);
			Link.l2.go = "LoanFindCitizenType_2_1";
		//NPChar.quest.LoanFindCitizenType = rand(1);// первые 2 типа
		break;

		case "LoanFindCitizenType_2_1":
			dialog.text = StringFromKey("Simple_rumors_381");
			Link.l1 = StringFromKey("Simple_rumors_382", pchar);
			Link.l1.go = "exit";
			pchar.GenQuest.Loan.FindCitizenDone = true;
			addMoneyToCharacter(Pchar, sti(pchar.GenQuest.Loan.FindCitizenTempMoney));
			SetTimerCondition("LoanFindCitizenTimer", 0, 0, 30, false);
			Log_SetStringToLog(StringFromKey("InfoMessages_194"));
			OfficersReaction("good");
			ChangeCharacterReputation(pchar, 3);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddQuestRecord("Gen_LoanFindCitizen", "3");
			npchar.LifeDay = 0;
		break;
		//доставка сундуков
		case "TakeChest_2":
			if (GetCharacterItem(pchar, "Chest") >= sti(pchar.GenQuest.LoanChest.Chest))
			{
				// evganat - энциклопедия, изменяем отношение ростовщика
				ref rUsurer;
				makeref(rUsurer, Characters[GetCharacterIndex(pchar.GenQuest.LoanChest.ChestNpcharId)]);

				if (CheckAttribute(pchar, "GenQuest.LoanChest.Money.Discount"))
				{
					// evganat - энциклопедия, изменяем отношение ростовщика
					IncreaseNPCDisposition(rUsurer, 1);

					Dialog.Text = StringFromKey("Simple_rumors_383", pchar.GenQuest.LoanChest.Money.Discount);
					link.l1 = StringFromKey("Simple_rumors_384");
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, sti(pchar.GenQuest.LoanChest.Money) / 100 * sti(pchar.GenQuest.LoanChest.Money.Discount));
				}
				else
				{
					// evganat - энциклопедия, изменяем отношение ростовщика
					IncreaseNPCDisposition(rUsurer, 3);

					Dialog.Text = StringFromKey("Simple_rumors_385");
					link.l1 = StringFromKey("Simple_rumors_386");
					link.l1.go = "exit";
					AddMoneyToCharacter(pchar, sti(pchar.GenQuest.LoanChest.Money));
				}
				ChangeCharacterReputation(pchar, 1);
				AddCharacterExpToSkill(pchar, "Sailing", 50);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 5);
				OfficersReaction("good");
				TakeNItems(pchar, "Chest", -sti(pchar.GenQuest.LoanChest.Chest));
				DeleteAttribute(pchar, "GenQuest.LoanChest");
				DeleteAttribute(Pchar, "quest.LoanChestTimer");
				AddQuestRecord("Gen_LoanTakeChest", "3");
				CloseQuestHeader("Gen_LoanTakeChest");
			}
			else
			{
				Dialog.Text = StringFromKey("Simple_rumors_387");
				link.l1 = StringFromKey("Simple_rumors_388");
				link.l1.go = "TakeChest_3";
				link.l2 = StringFromKey("Simple_rumors_389");
				link.l2.go = "exit";
			}
		break;

		case "TakeChest_3":
			Dialog.Text = StringFromKey("Simple_rumors_390");
			link.l1 = StringFromKey("Simple_rumors_391");
			link.l1.go = "exit";
		//link.l2 = "Ну а, скажем, сумма в " + FindMoneyString(sti(pchar.GenQuest.LoanChest.Chest)*30000) + " покроет стоимость сундуков?";
		//link.l2.go = "TakeChest_4";
		break;

		/*case "TakeChest_4":
            Dialog.Text = "Да, это приемлемо.";
            if (sti(pchar.Money) >= (sti(pchar.GenQuest.LoanChest.Chest)*30000))
            {
                link.l1 = "Вот и договорились!";
    			link.l1.go = "TakeChest_5";
			}
			link.l2 = "Только это много для меня.";
			link.l2.go = "exit";
		break;

		case "TakeChest_5":
            ChangeCharacterReputation(pchar, 1);
            AddCharacterExpToSkill(pchar, "Sailing", 30);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "COMMERCE", 30);
            OfficersReaction("good");
            Dialog.Text = "С вами можно иметь дело!";
            link.l1 = "Спасибо!";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1*(sti(pchar.GenQuest.LoanChest.Chest)*30000));
			DeleteAttribute(pchar, "GenQuest.LoanChest");
			DeleteAttribute(Pchar, "quest.LoanChestTimer");
			AddQuestRecord("Gen_LoanTakeChest", "4");
            CloseQuestHeader("Gen_LoanTakeChest");
		break;
*/
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////		Квесты мэра, проникновение во враждебный город
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
			Dialog.Text = StringFromKey("Simple_rumors_394", RandPhraseSimple(
						StringFromKey("Simple_rumors_392"),
						StringFromKey("Simple_rumors_393")));
			link.l1 = StringFromKey("Simple_rumors_397", RandPhraseSimple(
						StringFromKey("Simple_rumors_395", pchar),
						StringFromKey("Simple_rumors_396")));
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city + "Gen");
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId));
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Pre"));
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////		Квест Асокольда, рендомные базары
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "AscoldTrader": //рендомный хозяин магаза
			dialog.Text = StringFromKey("Simple_rumors_398", pchar);
			if (GetQuestPastDayParam("questTemp.Ascold") > 3)
			{
				Link.l1 = StringFromKey("Simple_rumors_399", pchar);
				Link.l1.go = "AscoldTrader_6";
			}
			else
			{
				Link.l1 = StringFromKey("Simple_rumors_400", pchar);
				Link.l1.go = "quests";
			}
		break;
		case "AscoldTrader_WasSeek":
			dialog.Text = StringFromKey("Simple_rumors_401", pchar);
			Link.l2 = StringFromKey("Simple_rumors_402", pchar);
			Link.l2.go = "AscoldTrader_1";
		break;
		case "AscoldTrader_1":
			dialog.text = StringFromKey("Simple_rumors_403");
			link.l1 = StringFromKey("Simple_rumors_404", pchar);
			link.l1.go = "AscoldTrader_2";
		break;
		case "AscoldTrader_2":
			string sLoc;
			if (pchar.location == "Guadeloupe_store") sLoc = StringFromKey("Simple_rumors_405");
			else sLoc = StringFromKey("Simple_rumors_406");

			dialog.text = StringFromKey("Simple_rumors_407", sLoc);
			if (Characters[GetCharacterIndex("Ascold")].quest.meeting == "0")
			{
				link.l1 = StringFromKey("Simple_rumors_408");
				link.l1.go = "AscoldTrader_4";
			}
			else
			{
				link.l1 = StringFromKey("Simple_rumors_409");
				link.l1.go = "AscoldTrader_3";
			}
		break;
		case "AscoldTrader_3":
			dialog.text = StringFromKey("Simple_rumors_410", pchar);
			link.l1 = StringFromKey("Simple_rumors_411", pchar);
			link.l1.go = "AscoldTrader_4";
		break;
		case "AscoldTrader_4":
			dialog.text = StringFromKey("Simple_rumors_412");
			link.l1 = StringFromKey("Simple_rumors_413");
			link.l1.go = "AscoldTrader_5";
		break;
		case "AscoldTrader_5":
			dialog.text = StringFromKey("Simple_rumors_414");
			link.l1 = StringFromKey("Simple_rumors_415");
			link.l1.go = "exit";
			pchar.questTemp.Ascold = "GoToAscold";
			QuestSetCurrentNode("Ascold", "HaveRecomendation");
			AddQuestRecord("Ascold", "2");
			RemoveLandQuestmark_Main(npchar, "Ascold");
			AddLandQuestmark_Main(CharacterFromID("Ascold"), "Ascold");
		break;
		case "AscoldTrader_6":
			dialog.text = StringFromKey("Simple_rumors_416");
			link.l1 = StringFromKey("Simple_rumors_417");
			link.l1.go = "AscoldTrader_7";
		break;
		case "AscoldTrader_7":
			dialog.text = StringFromKey("Simple_rumors_418", pchar);
			link.l1 = StringFromKey("Simple_rumors_419");
			link.l1.go = "quests";
			SaveCurrentQuestDateParam("questTemp.Ascold");
		break;
		//==> Общий диалог для хозяев верфи, квест Аззи.
		case "AzzyTryTalk":
			dialog.Text = NPCStringReactionRepeat(
				StringFromKey("Simple_rumors_420"), "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
			Link.l1 = HeroStringReactionRepeat(
				StringFromKey("Simple_rumors_421"), "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l1.go = "Exit";
		break;
		case "AggryHelp":
			dialog.Text = NPCStringReactionRepeat(
				StringFromKey("Simple_rumors_422", pchar), "none", "none", "none", "block", 0, npchar, Dialog.CurrentNode);
			Link.l10 = HeroStringReactionRepeat(
				StringFromKey("Simple_rumors_423", npchar.name), "none", "none", "none", npchar, Dialog.CurrentNode);
			Link.l10.go = "exit";
			items[FindItem("Azzy_bottle")].shown = 0; //даем возможность вскрыть лампу
			Ascold_FreeAzzy_DelQuestMarks();
		break;
		//==> Общий диалог для церкви, квест Аззи.
		case "GiveLamp":
			dialog.text = StringFromKey("Simple_rumors_424", pchar);
			link.l1 = StringFromKey("Simple_rumors_425");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 100);
			TakeItemFromCharacter(pchar, "Azzy_bottle");
			Ascold_FreeAzzy_DelQuestMarks();
			Achievment_Set(ACH_Bogougodnoe_delo);
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////		Грабеж среди бела дня, попытка залезть в сундуки
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "Man_FackYou":
			if (CheckAttribute(pchar, "quest.Slavetrader_Ambush_over") && !CheckAttribute(pchar, "quest.Slavetrader_Ambush_over.confiscation"))
			{
				//Работорговец 4-е задание
				pchar.quest.Slavetrader_Ambush_over.confiscation = 1;
				dialog.text = StringFromKey("Simple_rumors_426");
				link.l1 = StringFromKey("Simple_rumors_427");
				link.l1.go = "freebie_chests";
				break;
			}
			if (CheckAttribute(pchar, "quest.Slavetrader_Ambush_over.confiscation"))
			{
				dialog.text = StringFromKey("Simple_rumors_430", RandPhraseSimple(
							StringFromKey("Simple_rumors_428"),
							StringFromKey("Simple_rumors_429")));
				link.l1 = StringFromKey("Simple_rumors_433", RandPhraseSimple(
							StringFromKey("Simple_rumors_431"),
							StringFromKey("Simple_rumors_432")));
				link.l1.go = "freebie_chests";
				break;
			}
			dialog.text = StringFromKey("Simple_rumors_437", LinkRandPhrase(
						StringFromKey("Simple_rumors_434", pchar),
						StringFromKey("Simple_rumors_435", pchar),
						StringFromKey("Simple_rumors_436", pchar)));
			link.l1 = StringFromKey("Simple_rumors_441", LinkRandPhrase(
						StringFromKey("Simple_rumors_438"),
						StringFromKey("Simple_rumors_439"),
						StringFromKey("Simple_rumors_440")));
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		case "freebie_chests":
			LAi_SetOwnerTypeNoGroup(NPChar);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////		Квест получения Синей птицы
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "RBlueBird":
			dialog.text = StringFromKey("Simple_rumors_442");
			link.l1 = StringFromKey("Simple_rumors_443");
			link.l1.go = "RBlueBird_1";
		break;
		case "RBlueBird_1":
			dialog.text = StringFromKey("Simple_rumors_444");
			link.l1 = StringFromKey("Simple_rumors_445");
			link.l1.go = "RBlueBird_2";
		break;
		case "RBlueBird_2":
			dialog.text = StringFromKey("Simple_rumors_446");
			link.l1 = StringFromKey("Simple_rumors_447");
			link.l1.go = "RBlueBird_3";
		break;
		case "RBlueBird_3":
			dialog.text = StringFromKey("Simple_rumors_448");
			link.l1 = StringFromKey("Simple_rumors_449");
			link.l1.go = "RBlueBird_4";
		break;
		case "RBlueBird_4":
			dialog.text = StringFromKey("Simple_rumors_450");
			link.l1 = StringFromKey("Simple_rumors_451");
			link.l1.go = "RBlueBird_5";
		break;
		case "RBlueBird_5":
			dialog.text = StringFromKey("Simple_rumors_452");
			link.l1 = StringFromKey("Simple_rumors_453", pchar);
			link.l1.go = "RBlueBird_6";
			link.l2 = StringFromKey("Simple_rumors_454");
			link.l2.go = "RBlueBird_close";
		break;
		case "RBlueBird_6":
			dialog.text = StringFromKey("Simple_rumors_455");
			link.l1 = StringFromKey("Simple_rumors_456");
			link.l1.go = "RBlueBird_7";
		break;
		case "RBlueBird_7":
			dialog.text = StringFromKey("Simple_rumors_457");
			link.l1 = StringFromKey("Simple_rumors_458");
			link.l1.go = "RBlueBird_8";
		break;
		case "RBlueBird_8":
			dialog.text = StringFromKey("Simple_rumors_459", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Simple_rumors_460", pchar);
			link.l1.go = "RBlueBird_9";
		break;
		case "RBlueBird_9":
			dialog.text = StringFromKey("Simple_rumors_461");
			link.l1 = StringFromKey("Simple_rumors_462");
			link.l1.go = "RBlueBird_10";
		break;
		case "RBlueBird_10":
			dialog.text = StringFromKey("Simple_rumors_463");
			link.l1 = StringFromKey("Simple_rumors_464");
			link.l1.go = "RBlueBird_11";
		break;
		case "RBlueBird_11":
			dialog.text = StringFromKey("Simple_rumors_465");
			link.l1 = StringFromKey("Simple_rumors_466");
			link.l1.go = "RBlueBird_12";
		break;
		case "RBlueBird_12":
			dialog.text = StringFromKey("Simple_rumors_467");
			link.l1 = StringFromKey("Simple_rumors_468");
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "toBermudes";
			pchar.questTemp.BlueBird.traiderId = npchar.id; //запомним Id торговца
			SetQuestHeader("Xebeca_BlueBird");
			AddQuestRecord("Xebeca_BlueBird", "1");
			AddQuestUserData("Xebeca_BlueBird", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("Xebeca_BlueBird", "sName", GetFullName(npchar));
			AddLandQuestMark_Main(CharacterFromID("Pirates_trader"), "Xebeca_BlueBird");
			AddLandQuestMark_Main(CharacterFromID("Jackman"), "Xebeca_BlueBird");
			AddLandQuestMark_Main(CharacterFromID("Pirates_tavernkeeper"), "Xebeca_BlueBird");
		break;

		case "RBlueBird_close":
			dialog.text = StringFromKey("Simple_rumors_469");
			link.l1 = StringFromKey("Simple_rumors_470");
			link.l1.go = "exit";
			pchar.questTemp.BlueBird = "over";
		break;
		case "RBlueBirdWon":
			dialog.text = StringFromKey("Simple_rumors_471");
			link.l1 = StringFromKey("Simple_rumors_472");
			link.l1.go = "RBlueBirdWon_1";
			int chComp;
			for (i = 0; i <= COMPANION_MAX; i++)
			{
				chComp = GetCompanionIndex(pchar, i);
				if (chComp != -1 && RealShips[sti(characters[chComp].ship.type)].Name == "XebekVML1")
				{
					dialog.text = StringFromKey("Simple_rumors_473");
					link.l1 = StringFromKey("Simple_rumors_474");
					link.l1.go = "RBlueBirdWon_10";
					break;
				}
			}
		break;

		case "RBlueBirdWon_1":
			dialog.text = StringFromKey("Simple_rumors_475");
			link.l1 = StringFromKey("Simple_rumors_476");
			link.l1.go = "RBlueBirdWon_2";
			AddItemLog(pchar, "chest", "4", StringFromKey("InfoMessages_134"), "Important_item");
		break;
		case "RBlueBirdWon_2":
			dialog.text = StringFromKey("Simple_rumors_477");
			link.l1 = StringFromKey("Simple_rumors_478");
			link.l1.go = "RBlueBirdWon_3";
		break;
		case "RBlueBirdWon_3":
			dialog.text = StringFromKey("Simple_rumors_479");
			link.l1 = StringFromKey("Simple_rumors_480");
			link.l1.go = "RBlueBirdWon_4";
		break;
		case "RBlueBirdWon_4":
			dialog.text = StringFromKey("Simple_rumors_481");
			link.l1 = StringFromKey("Simple_rumors_482");
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questTemp.BlueBird = "over";
			RemoveLandQuestMark_Main(npchar, "Xebeca_BlueBird");
			Achievment_Set(ACH_Prizraki_proshlogo);
		break;

		case "RBlueBirdWon_10":
			dialog.text = StringFromKey("Simple_rumors_483");
			link.l1 = StringFromKey("Simple_rumors_484", pchar);
			link.l1.go = "RBlueBirdWon_11";
		break;
		case "RBlueBirdWon_11":
			dialog.text = StringFromKey("Simple_rumors_485");
			link.l1 = StringFromKey("Simple_rumors_486", pchar);
			link.l1.go = "RBlueBirdWon_12";
		break;
		case "RBlueBirdWon_12":
			dialog.text = StringFromKey("Simple_rumors_487");
			link.l1 = StringFromKey("Simple_rumors_488");
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "9");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Xebeca_BlueBird", "sSex1", GetSexPhrase(StringFromKey("SexPhrase_13"), StringFromKey("SexPhrase_14")));
			pchar.questTemp.BlueBird = "returnMoney";
			RemoveLandQuestMark_Main(npchar, "Xebeca_BlueBird");
		break;

		case "RBlueBirdDieHard":
			dialog.text = StringFromKey("Simple_rumors_489", pchar);
			link.l1 = StringFromKey("Simple_rumors_490");
			link.l1.go = "RBlueBirdDieHard_1";
		break;
		case "RBlueBirdDieHard_1":
			dialog.text = StringFromKey("Simple_rumors_491");
			link.l1 = StringFromKey("Simple_rumors_492");
			link.l1.go = "exit";
			CloseQuestHeader("Xebeca_BlueBird");
			pchar.questTemp.BlueBird = "over";
			RemoveLandQuestMark_Main(npchar, "Xebeca_BlueBird");
			Achievment_Set(ACH_Prizraki_proshlogo);
		break;

		case "RBlueBird_retMoney_1":
			dialog.text = StringFromKey("Simple_rumors_493", pchar);
			link.l1 = StringFromKey("Simple_rumors_494", pchar);
			link.l1.go = "RBlueBird_retMoney_2";
		break;
		case "RBlueBird_retMoney_2":
			dialog.text = StringFromKey("Simple_rumors_495", pchar);
			link.l1 = StringFromKey("Simple_rumors_496");
			link.l1.go = "fight";
		break;

		case "RBlueBird_retMoney_3":
			dialog.text = StringFromKey("Simple_rumors_497", pchar);
			link.l1 = StringFromKey("Simple_rumors_498");
			link.l1.go = "RBlueBird_retMoney_4";
		break;
		case "RBlueBird_retMoney_4":
			dialog.text = StringFromKey("Simple_rumors_499");
			link.l1 = StringFromKey("Simple_rumors_500", pchar);
			link.l1.go = "RBlueBird_retMoney_5";
		break;
		case "RBlueBird_retMoney_5":
			dialog.text = StringFromKey("Simple_rumors_501");
			link.l1 = StringFromKey("Simple_rumors_502");
			link.l1.go = "RBlueBird_retMoney_6";
		break;
		case "RBlueBird_retMoney_6":
			dialog.text = StringFromKey("Simple_rumors_503");
			link.l1 = StringFromKey("Simple_rumors_504");
			link.l1.go = "RBlueBird_retMoney_7";
		break;
		case "RBlueBird_retMoney_7":
			dialog.text = StringFromKey("Simple_rumors_505");
			link.l1 = StringFromKey("Simple_rumors_506", pchar);
			link.l1.go = "RBlueBird_retMoney_8";
		break;
		case "RBlueBird_retMoney_8":
			dialog.text = StringFromKey("Simple_rumors_507");
			link.l1 = StringFromKey("Simple_rumors_508", pchar);
			link.l1.go = "RBlueBird_retMoney_9";
		break;
		case "RBlueBird_retMoney_9":
			dialog.text = StringFromKey("Simple_rumors_509");
			link.l1 = StringFromKey("Simple_rumors_510");
			link.l1.go = "RBlueBird_retMoney_10";
		break;
		case "RBlueBird_retMoney_10":
			dialog.text = StringFromKey("Simple_rumors_511", pchar);
			link.l1 = StringFromKey("Simple_rumors_512", pchar);
			link.l1.go = "RBlueBird_retMoney_11";
		break;
		case "RBlueBird_retMoney_11":
			dialog.text = StringFromKey("Simple_rumors_513");
			link.l1 = StringFromKey("Simple_rumors_514");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.BlueBird");
			pchar.questTemp.BlueBird = "over"; //закрываем квест
			AddItemLog(pchar, "chest", "14", StringFromKey("InfoMessages_134"), "Important_item");
			AddQuestRecord("Xebeca_BlueBird", "15");
			AddQuestUserData("Xebeca_BlueBird", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Xebeca_BlueBird");
			RemoveLandQuestMark_Main(npchar, "Xebeca_BlueBird");
			Achievment_Set(ACH_Prizraki_proshlogo);
		break;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////		Линейка острова погибших кораблей ISS
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "ISS_deposit":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Simple_rumors_515"),
						StringFromKey("Simple_rumors_516", GetAddress_Form(NPChar)),
						StringFromKey("Simple_rumors_517"),
						StringFromKey("Simple_rumors_518"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Simple_rumors_519", pchar),
						StringFromKey("Simple_rumors_520"),
						StringFromKey("Simple_rumors_521"),
						StringFromKey("Simple_rumors_522", GetAddress_Form(NPChar)), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		case "ISS_takeDeposit":
			dialog.text = StringFromKey("Simple_rumors_523", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Simple_rumors_524");
			link.l1.go = "ISS_takeDeposit_1";
			AddMoneyToCharacter(pchar, 1000000);
			CloseQuestHeader("ISS_PoorsMurder");
		break;
		case "ISS_takeDeposit_1":
			dialog.text = StringFromKey("Simple_rumors_525");
			link.l1 = StringFromKey("Simple_rumors_526", pchar);
			link.l1.go = "exit";
			pchar.questTemp.LSC = "over"; //конец линейки ГПК
			DeleteAttribute(pchar, "questTemp.LSC.usurerId");
			sld = characterFromId("hol_guber"); //чтобы Стэвезан мог переезжать, когда снимется пауза
			DeleteAttribute(sld, "notMoveAble");
			DeleteAttribute(&colonies[FindColony("Villemstad")], "notCaptured"); //Виллемстад можно себе
			CloseQuestHeader("ISS_PoorsMurder");
			RemoveLandQuestmark_Main(npchar, "ISS_PoorsMurder");
			Achievment_Set(ACH_Delovoy_podkhod);
		break;
		//штурм касперов
		case "WarlocksWay":
			dialog.text = StringFromKey("Simple_rumors_527");
			link.l1 = StringFromKey("Simple_rumors_528");
			link.l1.go = "StormCaspers";
		break;
		case "StormCaspers":
			dialog.text = StringFromKey("Simple_rumors_529");
			link.l1 = StringFromKey("Simple_rumors_530");
			link.l1.go = "StormCaspers_1";
		break;
		case "StormCaspers_1":
			dialog.text = StringFromKey("Simple_rumors_531");
			link.l1 = StringFromKey("Simple_rumors_532");
			link.l1.go = "StormCaspers_2";
		break;
		case "StormCaspers_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DoReloadCharacterToLocation("SanGabrielMechanic", "reload", "reload1");
			RemoveLandQuestMark_Main(CharacterFromID("Ment_6"), "ISS_DefeatCasperClan");
		break;
		case "AfterStormCaspers":
			dialog.text = StringFromKey("Simple_rumors_535", RandPhraseSimple(
						StringFromKey("Simple_rumors_533", GetFullName(pchar)),
						StringFromKey("Simple_rumors_534", GetFullName(pchar))));
			link.l1 = StringFromKey("Simple_rumors_536");
			link.l1.go = "AfterStormCaspers_0_0";
			link.l2 = StringFromKey("Simple_rumors_537");
			link.l2.go = "AfterStormCaspers_0_1";
		break;
		case "AfterStormCaspers_0_0":
			dialog.text = StringFromKey("Simple_rumors_538");
			link.l1 = StringFromKey("Simple_rumors_539");
			link.l1.go = "AfterStormCaspers_1";
			ChangeCharacterReputation(pchar, 8);
		break;
		case "AfterStormCaspers_0_1":
			dialog.text = StringFromKey("Simple_rumors_540");
			link.l1 = StringFromKey("Simple_rumors_541", pchar);
			link.l1.go = "AfterStormCaspers_1";
			ChangeCharacterReputation(pchar, -8);
		break;
		case "AfterStormCaspers_1":
			dialog.text = StringFromKey("Simple_rumors_542");
			link.l1 = StringFromKey("Simple_rumors_543");
			link.l1.go = "AfterStormCaspers_2";
		break;
		case "AfterStormCaspers_2":
			dialog.text = StringFromKey("Simple_rumors_544");
			link.l1 = StringFromKey("Simple_rumors_545");
			link.l1.go = "AfterStormCaspers_3";
		break;
		case "AfterStormCaspers_3":
			dialog.text = StringFromKey("Simple_rumors_546");
			link.l1 = StringFromKey("Simple_rumors_547");
			link.l1.go = "AfterStormCaspers_4";
		break;
		case "AfterStormCaspers_4":
			int index;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			//отряд самоубийц возвращается к повседневным делам
			makearef(aTemp, pchar.questTemp.LSC.suicideSquad);
			for (i = 0; i < GetAttributesNum(aTemp); i++)
			{
				index = sti(GetAttributeName(GetAttributeN(aTemp, i)));
				sld = &characters[index];
				LAi_SetActorType(sld);
				sld.dialog.currentnode = "First time";
				sld.quest.suicidus = true; //запоминаем что данный перец бывший суицидник
				GetCharacterPos(sld, &locx, &locy, &locz);
				switch (sld.id)
				{
					case "LSC_Prisoner1":
						sld.dialog.currentnode = "Prisoner";
						LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "TartarusPrison", "goto", "goto1", "", 10.0);
					break;
					case "Ment_6":
						LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "SanAugustineResidence", "goto", "goto1", "", 10.0);
					break;
					case "MalcolmFawn":
						LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "LostShipsCity_town", "goto", "goto02_3", "", 10.0);
					break;
					case "MaximTailor":
						LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "CeresSmithy", "goto", "goto03_1", "", 10.0);
					break;
				}
				DeleteAttribute(sld, "watchBoxes"); //они теперь свои, а свои не палят
			}
			if (CheckAttribute(pchar, "questTemp.LSC.MentosHelp"))
			{
				//Менты возвращаются на место
				for (i = 1; i <= 3; i++)
				{
					index = GetCharacterIndex("Ment_" + i);
					if (index != -1 && !LAi_IsDead(&characters[index]))
					{
						LAi_SetWarriorTypeNoGroup(&characters[index]);
						ChangeCharacterAddressGroup(&characters[index], "LostShipsCity_town", "goto", characters[index].location.baseLocator);
					}
				}
				//мушкетеры ментов возвращаются на место
				for (i = 7; i < 9; i++)
				{
					index = GetCharacterIndex("MentMush_" + i);
					if (index != -1 && !LAi_IsDead(&characters[index]))
					{
						ChangeCharacterAddressGroup(&characters[index], "LostShipsCity_town", "soldiers", "mushketer" + i);
						characters[index].Dialog.CurrentNode = "Ment_soldier";
						LAi_SetGuardianTypeNoGroup(&characters[index]);
					}
				}
			}
			pchar.quest.AfterStormCaspers_ExitFromLocation.win_condition.l1 = "ExitFromLocation";
			pchar.quest.AfterStormCaspers_ExitFromLocation.win_condition.l1.location = PChar.location;
			pchar.quest.AfterStormCaspers_ExitFromLocation.function = "AfterStormCaspers_ExitFromLocation";
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		break;
		//механика арестовали, диалоги мужика - теперь это Малькольм
		case "MechanicIsPrison_man":
			dialog.text = StringFromKey("Simple_rumors_548");
			link.l1 = StringFromKey("Simple_rumors_549");
			link.l1.go = "MechanicIsPrison_man_1";
		break;
		case "MechanicIsPrison_man_1":
			dialog.text = StringFromKey("Simple_rumors_550", npchar);
			link.l1 = StringFromKey("Simple_rumors_551");
			link.l1.go = "MechanicIsPrison_man_2";
		break;
		case "MechanicIsPrison_man_2":
			dialog.text = StringFromKey("Simple_rumors_552");
			link.l1 = StringFromKey("Simple_rumors_553");
			link.l1.go = "MechanicIsPrison_man_3";
		break;
		case "MechanicIsPrison_man_3":
			dialog.text = StringFromKey("Simple_rumors_554");
			link.l1 = StringFromKey("Simple_rumors_555");
			link.l1.go = "MechanicIsPrison_man_4";
		break;
		case "MechanicIsPrison_man_4":
			dialog.text = StringFromKey("Simple_rumors_556", pchar);
			link.l1 = StringFromKey("Simple_rumors_557");
			link.l1.go = "MechanicIsPrison_man_5";
		break;
		case "MechanicIsPrison_man_5":
			dialog.text = StringFromKey("Simple_rumors_558");
			link.l1 = StringFromKey("Simple_rumors_559");
			link.l1.go = "MechanicIsPrison_man_6";
			link.l2 = StringFromKey("Simple_rumors_560");
			link.l2.go = "MechanicIsPrison_man_6";
		break;
		case "MechanicIsPrison_man_6":
			dialog.text = StringFromKey("Simple_rumors_561");
			link.l1 = StringFromKey("Simple_rumors_562");
			link.l1.go = "MechanicIsPrison_man_7";
		break;
		case "MechanicIsPrison_man_7":
			dialog.text = StringFromKey("Simple_rumors_563");
			link.l1 = StringFromKey("Simple_rumors_564");
			link.l1.go = "MechanicIsPrison_man_8";
		break;
		case "MechanicIsPrison_man_8":
			dialog.text = StringFromKey("Simple_rumors_565");
			link.l1 = StringFromKey("Simple_rumors_566");
			link.l1.go = "MechanicIsPrison_man_9";
		break;
		case "MechanicIsPrison_man_9":
			dialog.text = StringFromKey("Simple_rumors_567", GetFullName(PChar));
			link.l1 = StringFromKey("Simple_rumors_568");
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "MechanicIsArrest_toResidence";
			bDisableFastReload = true;
			SetCrewQuantity(pchar, sti(pchar.questTemp.LSC.crew));
			DeleteAttribute(pchar, "questTemp.LSC.crew");
			AddQuestRecord("ISS_MainLine", "60");
			pchar.quest.LSC_fightEnterResidence.win_condition.l1 = "location";
			pchar.quest.LSC_fightEnterResidence.win_condition.l1.location = "SanAugustineResidence";
			pchar.quest.LSC_fightEnterResidence.function = "LSC_fightEnterResidence";
			AddLandQuestMark_Main(CharacterFromID("Ment_6"), "ISS_MainLine");
			//закрываем тюрьму
			LocatorReloadEnterDisable("LostShipsCity_town", "reload51", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload52", true);
		break;
		//механика арестовали, диалоги женские - неактуально
		/*case "MechanicIsPrison_woman":
			dialog.text = "А-а, ну вот и вы, наконец...";
			link.l1 = "В чём дело? Почему вы ещё не на корвете?... А где Механик?";
			link.l1.go = "MechanicIsPrison_man_1";
		break;
		case "MechanicIsPrison_woman_1":
			dialog.text = "Где он сейчас я не знаю. Когда я пришла на 'Сан Габриэль', его как раз выводили милиционеры. Судя по всему, он арестован, и сделать это мог только адмирал.";
			link.l1 = "Проклятье! Что же теперь делать?";
			link.l1.go = "MechanicIsPrison_woman_2";
		break;
		case "MechanicIsPrison_woman_2":
			dialog.text = "А без Механика нам не обойтись?";
			link.l1 = "Ведекер нам нужен. На корвет мы сможем попасть, а вот освободить его без Хенрика не выйдет.";
			link.l1.go = "MechanicIsPrison_man_3";
		break;
		case "MMechanicIsPrison_woman_3":
			dialog.text = "Тогда нужно идти в резиденцию к Капперу, выручать Механика. Я, как женщина, помочь в этом деле вам не смогу, к сожалению.";
			link.l1 = "Это точно... Отправляйтесь на корабль, я скоро прибуду с Ведекером. Остальные члены команды, судя по всему, уже там.";
			link.l1.go = "MechanicIsPrison_man_4";
		break;
		case "MechanicIsPrison_woman_4":
			dialog.text = "Как скажете, капитан.";
			link.l1 = "Не паникуйте там без меня. Всё будет хорошо.";
			link.l1.go = "exit";
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			pchar.questTemp.LSC = "MechanicIsArrest_toResidence";
			SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
			bDisableFastReload = true;
			SetCrewQuantity(pchar, sti(pchar.questTemp.LSC.crew));
			DeleteAttribute(pchar, "questTemp.LSC.crew");
			AddQuestRecord("ISS_MainLine", "60");
			pchar.quest.LSC_fightEnterResidence.win_condition.l1 = "location";
			pchar.quest.LSC_fightEnterResidence.win_condition.l1.location = "SanAugustineResidence";
			pchar.quest.LSC_fightEnterResidence.function = "LSC_fightEnterResidence";
			//закрываем тюрьму
			LocatorReloadEnterDisable("LostShipsCity_town", "reload51", true);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload52", true);
		break;*/
		case "SeekCrew_all":
			NextDiag.CurrentNode = NextDiag.TempNode;

			pchar.questTemp.LSC.crew = sti(pchar.questTemp.LSC.crew) + 1;
			chrDisableReloadToLocation = true;
			GetCharacterPos(pchar, &locx, &locy, &locz);

			sTemp = LAi_FindNearestLocator("reload", locx, locy, locz);
			if (pchar.location == "FleuronTavern")
				sTemp = "reload7";
			if (pchar.location == "LostShipsCity_town")
				sTemp = "reload55";

			iTemp = -1;
			if (npchar.id == "ElisTaylor")
			{
				sld = CharacterFromId("MaximTailor");
				if (sld.location != "TartarusPrison")
				{
					pchar.questTemp.LSC.crew = sti(pchar.questTemp.LSC.crew) + 1;
					sld.cityTape = "toLeave";
					iTemp = sti(sld.index);
					if (sld.location == "FleuronTavern" && pchar.location == "FleuronTavern")
					{
						if (sld.location.group == "sit")
						{
							ChangeCharacterAddressGroup(sld, sld.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
						}
						LAi_SetActorType(sld);
						LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 10.0);
					}
					else
					{
						ChangeCharacterAddressGroup(sld, "none", "", "");
					}
				}
			}
			if (npchar.id == "LSCwaitress")
			{
				sld = CharacterFromId("LSC_Prisoner1");
				pchar.questTemp.LSC.crew = sti(pchar.questTemp.LSC.crew) + 1;
				sld.cityTape = "toLeave";
				iTemp = sti(sld.index);
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}

			// запись в СЖ и отправляем на Диффиндур -->
			string sName = GetFullName(npchar);
			if (sti(pchar.questTemp.LSC.crew) < 15)
			{
				AddQuestRecord("ISS_MainLine", "58");
				if (iTemp != -1)
				{
					sName = StringFromKey("Simple_rumors_569", GetFullName(&Characters[iTemp]), GetFullName(npchar));
					AddQuestUserData("ISS_MainLine", "sName", sName);
					AddQuestUserData("ISS_MainLine", "Sex", "согласились");
				}
				else
				{
					AddQuestUserData("ISS_MainLine", "sName", sName);
					AddQuestUserData("ISS_MainLine", "Sex", "" + NPCharSexPhrase(NPChar, "согласился", "согласилась"));
				}
				AddQuestUserData("ISS_MainLine", "iCrew", FindPeoplesString(15 - sti(pchar.questTemp.LSC.crew), "Gen"));
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "77");
				if (iTemp != -1)
				{
					sName = StringFromKey("Simple_rumors_570", GetFullName(&Characters[iTemp]), GetFullName(npchar));
					AddQuestUserData("ISS_MainLine", "sName", sName);
					AddQuestUserData("ISS_MainLine", "Sex", "согласились");
				}
				else
				{
					AddQuestUserData("ISS_MainLine", "sName", sName);
					AddQuestUserData("ISS_MainLine", "Sex", "" + NPCharSexPhrase(NPChar, "согласился", "согласилась"));
				}
			}

			npchar.cityTape = "toLeave";
			if (npchar.location.group == "sit")
			{
				ChangeCharacterAddressGroup(npchar, npchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
			}
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(NPChar, "reload", sTemp, "none", "", "", "OpenTheDoors", 10.0);
			// <-- запись в СЖ и отправляем на Диффиндур 

			// собрали минимум
			if (sti(pchar.questTemp.LSC.crew) >= 15 && !CheckAttribute(pchar, "questTemp.LSC.lastManId"))
			{
				pchar.questTemp.LSC.lastManId = GetCharacterIndex("MalcolmFawn"); //сюда запишем индекс
				pchar.questTemp.LSC = "MechanicIsArrest";
				pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха
				AddQuestRecord("ISS_MainLine", "59");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("ен", "на"));

				pchar.quest.LSC_afterArestMachanic.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LSC_afterArestMachanic.win_condition.l1.location = pchar.location;
				pchar.quest.LSC_afterArestMachanic.function = "LSC_afterArestMachanic";
			}

			DialogExit();
		break;
		case "Exit_GoodBye":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "LSC_CheckPeopleOnDiffindur", 10.0);
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идёт распределение по городам
{
	string sRetRumour = StringFromKey("Simple_rumors_571");
	// флаг - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - для проверок, какой вопрос выпал. Ножно будет юзать для квестов
	switch (sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;

		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;

		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;

		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;

		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;

		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;

		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;

		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;

		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;

		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;

		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;

		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;

		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;

		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;

		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;

		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;

		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;

		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;

		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;

		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;

		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;

		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;

		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}

	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // База слухов жителей. Можно менять без новой игры
{

	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // Губернаторы
	STR_MAYOR[0] = StringFromKey("Simple_rumors_572");
	STR_MAYOR[1] = StringFromKey("Simple_rumors_573");
	STR_MAYOR[2] = StringFromKey("Simple_rumors_574");
	STR_MAYOR[3] = StringFromKey("Simple_rumors_575");
	STR_MAYOR[4] = StringFromKey("Simple_rumors_576");
	STR_MAYOR[5] = StringFromKey("Simple_rumors_577");
	STR_MAYOR[6] = StringFromKey("Simple_rumors_578");

	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = StringFromKey("Simple_rumors_579");
	STR_TAVERNKEEPER[1] = StringFromKey("Simple_rumors_580");
	STR_TAVERNKEEPER[2] = StringFromKey("Simple_rumors_581");
	STR_TAVERNKEEPER[3] = StringFromKey("Simple_rumors_582");
	STR_TAVERNKEEPER[4] = StringFromKey("Simple_rumors_583");
	STR_TAVERNKEEPER[5] = StringFromKey("Simple_rumors_584");
	STR_TAVERNKEEPER[6] = StringFromKey("Simple_rumors_585");

	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = StringFromKey("Simple_rumors_586");
	STR_SHIPYARDER[1] = StringFromKey("Simple_rumors_587");
	STR_SHIPYARDER[2] = StringFromKey("Simple_rumors_588");
	STR_SHIPYARDER[3] = StringFromKey("Simple_rumors_589");
	STR_SHIPYARDER[4] = StringFromKey("Simple_rumors_590");
	STR_SHIPYARDER[5] = StringFromKey("Simple_rumors_591");
	STR_SHIPYARDER[6] = StringFromKey("Simple_rumors_592");

	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = StringFromKey("Simple_rumors_593");
	STR_TRADER[1] = StringFromKey("Simple_rumors_594");
	STR_TRADER[2] = StringFromKey("Simple_rumors_595");
	STR_TRADER[3] = StringFromKey("Simple_rumors_596");
	STR_TRADER[4] = StringFromKey("Simple_rumors_597");
	STR_TRADER[5] = StringFromKey("Simple_rumors_598");
	STR_TRADER[6] = StringFromKey("Simple_rumors_599");

	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];

	if (sOwnerType == "Mayor") return sTempMayor;
	if (sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if (sOwnerType == "ShipYarder") return sTempShipyarder;
	if (sOwnerType == "Trader") return sTempTrader;
}

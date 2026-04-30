// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\Rumours\Simple_rumors.c"  //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, sTemp, sMoney, attrL;

	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	int iMoney, iQuantityGoods, iTradeGoods, iTmp;

	bool ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	if (!CheckAttribute(npchar, "quest.item_date"))
	{
		npchar.quest.item_date = "";
	}

	if (!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Store\" + NPChar.City + "_Store.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}

	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	string attrLoc   = Dialog.CurrentNode;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Store_4", LinkRandPhrase(
								StringFromKey("Common_Store_1"),
								StringFromKey("Common_Store_2"),
								StringFromKey("Common_Store_3", pchar))),
						StringFromKey("Common_Store_8", LinkRandPhrase(
								StringFromKey("Common_Store_5", pchar),
								StringFromKey("Common_Store_6", pchar),
								StringFromKey("Common_Store_7", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Store_11", RandPhraseSimple(
								StringFromKey("Common_Store_9"),
								StringFromKey("Common_Store_10"))),
						StringFromKey("Common_Store_14", RandPhraseSimple(
								StringFromKey("Common_Store_12", GetWorkTypeOfMan(npchar, "")),
								StringFromKey("Common_Store_13", GetWorkTypeOfMan(npchar, "")))));
				link.l1.go = "fight";
				break;
			}

			//homo Линейка Блада
			if (Pchar.questTemp.CapBloodLine == true)
			{
				dialog.Text = StringFromKey("Common_Store_18", LinkRandPhrase(
							StringFromKey("Common_Store_15", TimeGreeting()),
							StringFromKey("Common_Store_16"),
							StringFromKey("Common_Store_17", GetFullName(pchar))));
				Link.l1 = StringFromKey("Common_Store_19", NPChar.name);
				Link.l1.go = "exit";
				NextDiag.TempNode = "First time";
				break;
			}

			// Warship, 29.05.11. "Дело чести" ветка "Трусливый фехтовальщик"
			if (CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = StringFromKey("Common_Store_20");
				Link.l1 = StringFromKey("Common_Store_21");
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}

			dialog.text = NPCharRepPhrase(npchar,
					StringFromKey("Common_Store_25", LinkRandPhrase(
							StringFromKey("Common_Store_22"),
							StringFromKey("Common_Store_23"),
							StringFromKey("Common_Store_24")), GetFullName(npchar)),
					StringFromKey("Common_Store_31", LinkRandPhrase(
							StringFromKey("Common_Store_26"),
							StringFromKey("Common_Store_27"),
							StringFromKey("Common_Store_28")), GetAddress_Form(NPChar), GetFullName(npchar), RandPhraseSimple(
							StringFromKey("Common_Store_29"),
							StringFromKey("Common_Store_30"))));
			link.l1 = StringFromKey("Common_Store_34", RandPhraseSimple(
						StringFromKey("Common_Store_32"),
						StringFromKey("Common_Store_33")), GetFullName(pchar));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "second time":
			if (LAi_group_GetPlayerAlarm() > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Store_38", LinkRandPhrase(
								StringFromKey("Common_Store_35"),
								StringFromKey("Common_Store_36"),
								StringFromKey("Common_Store_37", pchar))),
						StringFromKey("Common_Store_42", LinkRandPhrase(
								StringFromKey("Common_Store_39", pchar),
								StringFromKey("Common_Store_40", pchar),
								StringFromKey("Common_Store_41", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Store_45", RandPhraseSimple(
								StringFromKey("Common_Store_43"),
								StringFromKey("Common_Store_44"))),
						StringFromKey("Common_Store_48", RandPhraseSimple(
								StringFromKey("Common_Store_46", GetWorkTypeOfMan(npchar, "")),
								StringFromKey("Common_Store_47", GetWorkTypeOfMan(npchar, "")))));
				link.l1.go = "fight";
				break;
			}
			/*if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
			{
				dialog.text = NPCharRepPhrase(npchar,
							   LinkRandPhrase("Разрази меня гром! ", "Дьявол!!! ", "Тысяча чертей!!! ")
							+ LinkRandPhrase("Неприятель ","Противник ", "Проклятый шпион ")+ LinkRandPhrase("в городе! ","прямо по курсу! ", "в кубрике! ") + RandPhraseSimple("Стража!", "Солдаты!"),
							  LinkRandPhrase("Пресвятая дева","Господи Иисусе", "Святой Себастьян")+ "! "+ LinkRandPhrase("Караул! " ,"Помогите! ","Да вы шпион! ")
							+ LinkRandPhrase("В городе враги! ","Лазутчики в городе! ","Предательство! ")+"Солдаты, сюда!!");
				link.l1 = pcharrepphrase(LinkRandPhrase("Закрой пасть!","Тишина на палубе!","Молчать!")+ " Или я "
											  + LinkRandPhrase("вырву твой язык и скормлю его псам, ", "вышибу тебе мозги, ","удушу тебя твоими же кишками, ")+ LinkRandPhrase("каналья!", "торгаш!", "мерзавец!"),
												LinkRandPhrase("Ради бога, ", "Прошу вас, ", "Немедленно ")+LinkRandPhrase("закройте рот!", "прекратите верещать, как свинья на бойне!", "заткнитесь, наконец!")
											  + LinkRandPhrase(" Или я не дам за вашу жизнь и фартинга!"," Меня уже здесь нет! И никогда не было! Вы поняли?"," Или мне придётся вас убить на месте."));
				link.l1.go = "fight";
				break;
			}*/
			// проверка награды
			/*if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) >= 40)
			{
				dialog.text = NPCharRepPhrase(npchar,
                     LinkRandPhrase("Разрази меня гром! ", "Дьявол!!! ", "Тысяча чертей!!! ")+GetFullName(pchar)+ ", по прозвищу "
							+ LinkRandPhrase("'Палач', ","'Окорок', ", "'Потрошитель', ") +LinkRandPhrase(" в городе! "," прямо по курсу! ", " с правого борта! ") + RandPhraseSimple("Стража!", "Солдаты!"),
							  LinkRandPhrase("Пресвятая дева","Господи Иисусе", "Святой Себастьян")+ "! Это сам "+GetFullName(pchar)+ LinkRandPhrase("! Ловите " ,"! Хватайте ","! Держите ")
							+ LinkRandPhrase("висельника! ","вора и убийцу! ","беглого каторжника! ")+"Солдаты, сюда!!");
				link.l1 =      pcharrepphrase(LinkRandPhrase("Закрой пасть!","Тишина на палубе!","Молчать!")+ " А не то я"
											  + LinkRandPhrase(" вырву твой язык, каналья!", " выбью из тебя мозги!"," тебе кишки выпущу!"),
							                    LinkRandPhrase("Ради бога замолчите!", "Прошу вас! Не кричите!", "К чему весь этот шум?")
											  + LinkRandPhrase(" Я уже ухожу!"," Меня уже здесь нет!"," Я не хочу вас убивать!"));
				link.l1.go = "fight";
				break;
			}    */

			// Warship, 29.05.11. "Дело чести" ветка "Трусливый фехтовальщик"
			if (CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
			{
				dialog.text = StringFromKey("Common_Store_49");
				Link.l1 = StringFromKey("Common_Store_50");
				Link.l1.go = "exit";
				DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
				break;
			}

			dialog.text = NPCharRepPhrase(npchar,
					pcharrepphrase(
							StringFromKey("Common_Store_59", LinkRandPhrase(
									StringFromKey("Common_Store_51"),
									StringFromKey("Common_Store_52", pchar),
									StringFromKey("Common_Store_53")), GetFullName(pchar), LinkRandPhrase(
									StringFromKey("Common_Store_54"),
									StringFromKey("Common_Store_55", pchar),
									StringFromKey("Common_Store_56")), RandPhraseSimple(
									StringFromKey("Common_Store_57"),
									StringFromKey("Common_Store_58"))),
							StringFromKey("Common_Store_72", LinkRandPhrase(
									StringFromKey("Common_Store_60"),
									StringFromKey("Common_Store_61"),
									StringFromKey("Common_Store_62")), RandPhraseSimple(
									StringFromKey("Common_Store_63"),
									StringFromKey("Common_Store_64")), RandPhraseSimple(
									StringFromKey("Common_Store_65"),
									StringFromKey("Common_Store_66")), LinkRandPhrase(
									StringFromKey("Common_Store_67"),
									StringFromKey("Common_Store_68"),
									StringFromKey("Common_Store_69", pchar)), RandPhraseSimple(
									StringFromKey("Common_Store_70"),
									StringFromKey("Common_Store_71")))),
					pcharrepphrase(
							StringFromKey("Common_Store_82", LinkRandPhrase(
									StringFromKey("Common_Store_73"),
									StringFromKey("Common_Store_74"),
									StringFromKey("Common_Store_75")), GetFullName(pchar), LinkRandPhrase(
									StringFromKey("Common_Store_76"),
									StringFromKey("Common_Store_77"),
									StringFromKey("Common_Store_78")), LinkRandPhrase(
									StringFromKey("Common_Store_79"),
									StringFromKey("Common_Store_80"),
									StringFromKey("Common_Store_81"))),
							StringFromKey("Common_Store_86", GetFullName(pchar), LinkRandPhrase(
									StringFromKey("Common_Store_83"),
									StringFromKey("Common_Store_84"),
									StringFromKey("Common_Store_85")))));

			link.l1 = NPCharRepPhrase(npchar,
					pcharrepphrase(
							StringFromKey("Common_Store_96", pchar, LinkRandPhrase(
									StringFromKey("Common_Store_87"),
									StringFromKey("Common_Store_88", pchar),
									StringFromKey("Common_Store_89")), LinkRandPhrase(
									StringFromKey("Common_Store_90"),
									StringFromKey("Common_Store_91"),
									StringFromKey("Common_Store_92")), LinkRandPhrase(
									StringFromKey("Common_Store_93"),
									StringFromKey("Common_Store_94"),
									StringFromKey("Common_Store_95"))),
							StringFromKey("Common_Store_105", LinkRandPhrase(
									StringFromKey("Common_Store_97"),
									StringFromKey("Common_Store_98"),
									StringFromKey("Common_Store_99")), GetAddress_FormToNPC(NPChar), GetFullName(Npchar), RandPhraseSimple(
									StringFromKey("Common_Store_100"),
									StringFromKey("Common_Store_101", pchar)), LinkRandPhrase(
									StringFromKey("Common_Store_102", pchar),
									StringFromKey("Common_Store_103"),
									StringFromKey("Common_Store_104", pchar)))),
					pcharrepphrase(
							StringFromKey("Common_Store_113", RandPhraseSimple(
									StringFromKey("Common_Store_106"),
									StringFromKey("Common_Store_107")), GetFullName(Npchar), LinkRandPhrase(
									StringFromKey("Common_Store_108"),
									StringFromKey("Common_Store_109"),
									StringFromKey("Common_Store_110")), RandPhraseSimple(
									StringFromKey("Common_Store_111", pchar),
									StringFromKey("Common_Store_112"))),
							StringFromKey("Common_Store_117", GetAddress_FormToNPC(NPChar), LinkRandPhrase(
									StringFromKey("Common_Store_114"),
									StringFromKey("Common_Store_115"),
									StringFromKey("Common_Store_116")))));
			link.l1.go = "node_1";
			NextDiag.TempNode = "Second time";
		break;

		case "node_1":
			dialog.text = NPCStringReactionRepeat(
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_123", RandPhraseSimple(
											StringFromKey("Common_Store_118"),
											StringFromKey("Common_Store_119")), LinkRandPhrase(
											StringFromKey("Common_Store_120", pchar),
											StringFromKey("Common_Store_121"),
											StringFromKey("Common_Store_122"))),
									StringFromKey("Common_Store_134", LinkRandPhrase(
											StringFromKey("Common_Store_124"),
											StringFromKey("Common_Store_125"),
											StringFromKey("Common_Store_126")), RandPhraseSimple(
											StringFromKey("Common_Store_127"),
											StringFromKey("Common_Store_128")), LinkRandPhrase(
											StringFromKey("Common_Store_129"),
											StringFromKey("Common_Store_130"),
											StringFromKey("Common_Store_131")), RandPhraseSimple(
											StringFromKey("Common_Store_132"),
											StringFromKey("Common_Store_133")))),
							pcharrepphrase(
									StringFromKey("Common_Store_137", RandPhraseSimple(
											StringFromKey("Common_Store_135", pchar),
											StringFromKey("Common_Store_136"))),
									StringFromKey("Common_Store_145", LinkRandPhrase(
											StringFromKey("Common_Store_138", NationNameGenitive(sti(NPChar.nation))),
											StringFromKey("Common_Store_139"),
											StringFromKey("Common_Store_140")), RandPhraseSimple(
											StringFromKey("Common_Store_141"),
											StringFromKey("Common_Store_142")), RandPhraseSimple(
											StringFromKey("Common_Store_143"),
											StringFromKey("Common_Store_144"))))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_146"),
									StringFromKey("Common_Store_151", pchar, RandPhraseSimple(
											StringFromKey("Common_Store_147", pchar),
											StringFromKey("Common_Store_150", pchar, RandPhraseSimple(
													StringFromKey("Common_Store_148"),
													StringFromKey("Common_Store_149")))))),
							pcharrepphrase(
									StringFromKey("Common_Store_152"),
									StringFromKey("Common_Store_153", GetFullName(pchar)))),
						NPCharRepPhrase(npchar,
							StringFromKey("Common_Store_160", RandPhraseSimple(
									StringFromKey("Common_Store_154"),
									StringFromKey("Common_Store_157", RandPhraseSimple(
											StringFromKey("Common_Store_155"),
											StringFromKey("Common_Store_156")))), RandPhraseSimple(
									StringFromKey("Common_Store_158"),
									StringFromKey("Common_Store_159"))),
							pcharrepphrase(
									StringFromKey("Common_Store_161", GetFullName(pchar)),
									StringFromKey("Common_Store_162", GetFullName(pchar)))),
						NPCharRepPhrase(npchar,
							StringFromKey("Common_Store_167", LinkRandPhrase(
									StringFromKey("Common_Store_163"),
									StringFromKey("Common_Store_164"),
									pcharrepphrase(
											StringFromKey("Common_Store_165"),
											StringFromKey("Common_Store_166", pchar)))),
							pcharrepphrase(
									StringFromKey("Common_Store_174", RandPhraseSimple(
											StringFromKey("Common_Store_168"),
											StringFromKey("Common_Store_169")), RandPhraseSimple(
											StringFromKey("Common_Store_170"),
											StringFromKey("Common_Store_171")), RandPhraseSimple(
											StringFromKey("Common_Store_172"),
											StringFromKey("Common_Store_173"))),
									StringFromKey("Common_Store_177", GetFullName(pchar), RandPhraseSimple(
											StringFromKey("Common_Store_175"),
											StringFromKey("Common_Store_176"))))), "cycle", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_178"),
									StringFromKey("Common_Store_179")),
							pcharrepphrase(
									StringFromKey("Common_Store_180", GetFullName(npchar)),
									StringFromKey("Common_Store_181", GetAddress_FormToNPC(NPChar)))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_182"),
									StringFromKey("Common_Store_183")),
							pcharrepphrase(
									StringFromKey("Common_Store_184"),
									StringFromKey("Common_Store_185", GetAddress_FormToNPC(NPChar), GetFullName(npchar)))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_186"),
									StringFromKey("Common_Store_187", GetFullName(npchar))),
							pcharrepphrase(
									StringFromKey("Common_Store_188"),
									StringFromKey("Common_Store_189"))),
						StringFromKey("Common_Store_190"), npchar, Dialog.CurrentNode);
			link.l1.go = "market";
			link.l2 = HeroStringReactionRepeat(
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_191", pchar),
									StringFromKey("Common_Store_192")),
							pcharrepphrase(
									StringFromKey("Common_Store_193"),
									StringFromKey("Common_Store_194", GetAddress_FormToNPC(NPChar), GetFullName(npchar)))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_195"),
									StringFromKey("Common_Store_196")),
							pcharrepphrase(
									StringFromKey("Common_Store_197"),
									StringFromKey("Common_Store_198", pchar, GetAddress_FormToNPC(NPChar), GetFullName(npchar)))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_199"),
									StringFromKey("Common_Store_200", pchar)),
							pcharrepphrase(
									StringFromKey("Common_Store_201"),
									StringFromKey("Common_Store_202", GetAddress_FormToNPC(NPChar), GetFullName(npchar)))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_203"),
									StringFromKey("Common_Store_204")),
							pcharrepphrase(
									StringFromKey("Common_Store_205"),
									StringFromKey("Common_Store_206"))), npchar, Dialog.CurrentNode);
			link.l2.go = "business";
			link.l3 = HeroStringReactionRepeat(
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_207"),
									StringFromKey("Common_Store_208")),
							pcharrepphrase(
									StringFromKey("Common_Store_209"),
									StringFromKey("Common_Store_210"))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_211"),
									StringFromKey("Common_Store_212")),
							pcharrepphrase(
									StringFromKey("Common_Store_213"),
									StringFromKey("Common_Store_214", pchar))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_215"),
									StringFromKey("Common_Store_216")),
							pcharrepphrase(
									StringFromKey("Common_Store_217"),
									StringFromKey("Common_Store_218"))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_219"),
									StringFromKey("Common_Store_220")),
							pcharrepphrase(
									StringFromKey("Common_Store_221"),
									StringFromKey("Common_Store_222"))), npchar, Dialog.CurrentNode);
			link.l3.go = "quests";
			//--> eddy. Аскольд, базар с рендомным торговцем
			if (pchar.questTemp.Ascold == "Seek_powder" && pchar.questTemp.Ascold.TraderId == npchar.id && !CheckAttribute(Pchar, "RomanticQuest.TalkInShop"))
			{
				link.l3.go = "AscoldTrader";
			}
			if (pchar.questTemp.Ascold == "PowderWasSeek" && pchar.questTemp.Ascold.TraderId == npchar.id)
			{
				link.l3.go = "AscoldTrader_WasSeek";
			}
			if (CheckAttribute(pchar, "GenQuest.EncGirl"))
			{
				if (pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l9 = StringFromKey("Common_Store_223", pchar);
					link.l9.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if (CheckAttribute(pchar, "GenQuest.EncGirl.Father") && pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = StringFromKey("Common_Store_224");
						link.l9.go = "EncGirl_1";
					}
				}
			}
			//<-- eddy. Аскольд, базар с рендомным торговцем
			link.l5 = HeroStringReactionRepeat(
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_225"),
									StringFromKey("Common_Store_226", GetAddress_FormToNPC(NPChar), GetFullName(npchar))),
							pcharrepphrase(
									StringFromKey("Common_Store_227"),
									StringFromKey("Common_Store_228", GetAddress_FormToNPC(NPChar), GetFullName(npchar)))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_229"),
									StringFromKey("Common_Store_230")),
							pcharrepphrase(
									StringFromKey("Common_Store_231"),
									StringFromKey("Common_Store_232"))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_233"),
									StringFromKey("Common_Store_234", GetAddress_FormToNPC(NPChar), GetFullName(npchar))),
							pcharrepphrase(
									StringFromKey("Common_Store_235"),
									StringFromKey("Common_Store_236", GetAddress_FormToNPC(NPChar), GetFullName(npchar)))),
						NPCharRepPhrase(npchar,
							pcharrepphrase(
									StringFromKey("Common_Store_237", GetFullName(pchar)),
									StringFromKey("Common_Store_238")),
							pcharrepphrase(
									StringFromKey("Common_Store_239"),
									StringFromKey("Common_Store_240", pchar, GetAddress_FormToNPC(NPChar), GetFullName(npchar)))), npchar, Dialog.CurrentNode);
			link.l5.go = "exit";
		break;

		case "market":
		//navy -->
		//занят ПГГ
			iTmp = CheckFreeServiceForNPC(NPChar, "Store");
			if (iTmp != -1)
			{
				dialog.text = StringFromKey("Common_Store_241", &characters[itmp], GetAddress_FormToNPC(&characters[iTmp]), GetFullName(&characters[iTmp]));
				link.l1 = StringFromKey("Common_Store_242");
				link.l1.go = "exit";
				break;
			}
			//navy <--
			dialog.text = StringFromKey("Common_Store_245", RandPhraseSimple(
						StringFromKey("Common_Store_243"),
						StringFromKey("Common_Store_244")));
			link.l1 = pcharrepphrase(
						StringFromKey("Common_Store_249", LinkRandPhrase(
								StringFromKey("Common_Store_246"),
								StringFromKey("Common_Store_247"),
								StringFromKey("Common_Store_248"))),
						StringFromKey("Common_Store_253", LinkRandPhrase(
								StringFromKey("Common_Store_250"),
								StringFromKey("Common_Store_251"),
								StringFromKey("Common_Store_252"))));
			link.l1.go = "trade_1";
			link.l2 = StringFromKey("Common_Store_257", LinkRandPhrase(
						StringFromKey("Common_Store_254"),
						StringFromKey("Common_Store_255"),
						StringFromKey("Common_Store_256")));
			link.l2.go = "items";
			link.l3 = pcharrepphrase(
						StringFromKey("Common_Store_260", RandPhraseSimple(
								StringFromKey("Common_Store_258"),
								StringFromKey("Common_Store_259"))),
						StringFromKey("Common_Store_263", RandPhraseSimple(
								StringFromKey("Common_Store_261"),
								StringFromKey("Common_Store_262"))));
			link.l3.go = "exit";
		break;

		case "EncGirl_1":
			dialog.text = StringFromKey("Common_Store_264");
			link.l1 = StringFromKey("Common_Store_265", pchar);
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
			dialog.text = StringFromKey("Common_Store_266");
			link.l1 = StringFromKey("Common_Store_267", pchar);
			link.l1.go = "EncGirl_3";
		break;

		case "EncGirl_3":
			dialog.text = StringFromKey("Common_Store_268");
			link.l1 = StringFromKey("Common_Store_269");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;

		case "EncGirl_4":
			if (sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = StringFromKey("Common_Store_270", pchar);
				link.l1 = StringFromKey("Common_Store_271", pchar);
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = StringFromKey("Common_Store_272", pchar);
				link.l1 = StringFromKey("Common_Store_273");
				link.l1.go = "EncGirl_6";
			}
		break;

		case "EncGirl_5":
			dialog.text = StringFromKey("Common_Store_274");
			link.l1 = StringFromKey("Common_Store_275");
			link.l1.go = "EncGirl_5_1";
		break;

		case "EncGirl_6":
			dialog.text = StringFromKey("Common_Store_276");
			link.l1 = StringFromKey("Common_Store_277");
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
			dialog.text = StringFromKey("Common_Store_278");
			link.l1 = StringFromKey("Common_Store_279");
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

		case "trade_1":
			if (CheckShipMooredInColony(rColony))
			{
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
				LaunchStore(sti(rColony.StoreNum));
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar,
						pcharrepphrase(
								StringFromKey("Common_Store_280"),
								StringFromKey("Common_Store_281")),
						pcharrepphrase(
								StringFromKey("Common_Store_282", GetFullName(pchar)),
								StringFromKey("Common_Store_283")));
				link.l1 = NPCharRepPhrase(npchar,
						pcharrepphrase(
								StringFromKey("Common_Store_284", RandSwear()),
								StringFromKey("Common_Store_285", pchar, GetFullName(npchar))),
						pcharrepphrase(
								StringFromKey("Common_Store_286"),
								StringFromKey("Common_Store_287")));
				link.l1.go = "exit";//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		break;

		case "storage_0":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage);
			if (sti(NPChar.MoneyForStorage) > 0)
			{
				dialog.text = StringFromKey("Common_Store_288", FindMoneyString(sti(NPChar.MoneyForStorage)));
				if (sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = StringFromKey("Common_Store_289");
					link.l1.go = "storage_3";
				}
				else
				{
					link.l1 = StringFromKey("Common_Store_290");
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Store_291");
				link.l1 = StringFromKey("Common_Store_292");
				link.l1.go = "storage_2";
			}
			link.l2 = StringFromKey("Common_Store_293", pchar);
			link.l2.go = "exit";
		break;

		case "storage_01":
			dialog.text = StringFromKey("Common_Store_294", pchar);
			link.l1 = StringFromKey("Common_Store_295");
			link.l1.go = "storage_1";
			link.l2 = StringFromKey("Common_Store_296", pchar);
			link.l2.go = "exit";
		break;

		case "storage_1":
			NPChar.MoneyForStorage = GetStoragePrice(15000);
			dialog.text = StringFromKey("Common_Store_297");
			if (sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = StringFromKey("Common_Store_298");
				link.l1.go = "storage_11";
			}
			else
			{
				link.l1 = StringFromKey("Common_Store_299");
				link.l1.go = "exit";
			}
		break;

		case "storage_11":
			AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage));
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			NPChar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));
		break;

		case "storage_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));
		break;

		case "storage_3":
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage));
			NPChar.MoneyForStorage = GetStoragePrice(15000);
			NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
			SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchStorage(sti(rColony.StoreNum));
		break;

		case "storage_04":
			dialog.text = StringFromKey("Common_Store_300");
			link.l1 = StringFromKey("Common_Store_301", pchar);
			link.l1.go = "storage_4";
			link.l2 = StringFromKey("Common_Store_302", pchar);
			link.l2.go = "exit";
		break;

		case "storage_4":
			NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage);
			if (sti(NPChar.MoneyForStorage) > 0)
			{
				dialog.text = StringFromKey("Common_Store_303", FindMoneyString(sti(NPChar.MoneyForStorage)));
				if (sti(pchar.money) >= sti(NPChar.MoneyForStorage))
				{
					link.l1 = StringFromKey("Common_Store_304");
					link.l1.go = "storage_5";
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Store_305");
				link.l1 = StringFromKey("Common_Store_306");
				link.l1.go = "storage_6";
			}
		break;

		case "storage_5":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage));
			DeleteAttribute(NPChar, "Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;

		case "storage_6":
			SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
			DeleteAttribute(NPChar, "Storage.Activate");
			NPChar.Storage.NoActivate = true;
			DialogExit();
		break;

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

		case "business":
			iTest = 0;
			//квест Синей Птицы, начальный диалог
			if (pchar.questTemp.BlueBird == "begin" && sti(npchar.nation) != PIRATE && npchar.city != "Panama") // !CheckAttribute(pchar, "questTemp.Headhunter")) убрал проверку на кондотьера Konstrush
			{
				dialog.text = StringFromKey("Common_Store_309", RandPhraseSimple(
							StringFromKey("Common_Store_307"),
							StringFromKey("Common_Store_308")));
				link.l1 = StringFromKey("Common_Store_310");
				link.l1.go = "RBlueBird";
				break;
			}
			//navy -->
			//занят ПГГ
			iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
			if (iTmp != -1)
			{
				dialog.text = StringFromKey("Common_Store_311", GetFullName(&Characters[iTmp]));
				link.l1 = StringFromKey("Common_Store_312");
				link.l1.go = "exit";
				break;
			}
			//navy <--
			dialog.text = NPCharRepPhrase(npchar,
					StringFromKey("Common_Store_313"),
					StringFromKey("Common_Store_314"));
			if (CheckShipMooredInColony(rColony))
			{
				/*if (CheckAttribute(pchar, "CargoQuest.iQuantityGoods"))
				{
					int iQuantityShipGoods = pchar.CargoQuest.iQuantityGoods;
					int iQuestTradeGoods = pchar.CargoQuest.iTradeGoods;
				}  */
				if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress", "failed"))
				{
					if (pchar.CargoQuest.TraderID == npchar.id)//&&  GetSquadronGoods(pchar, iQuestTradeGoods) >= iQuantityShipGoods)
					{
						link.l1 = StringFromKey("Common_Store_317", RandPhraseSimple(
									StringFromKey("Common_Store_315"),
									StringFromKey("Common_Store_316")));
						link.l1.go = "generate_quest_2";
					}
					else
					{
						if (!CheckQuestAttribute("generate_trade_quest_progress", "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
						{
							link.l1 = StringFromKey("Common_Store_318", pchar);
							link.l1.go = "generate_quest_cannot_done";
						}
						else
						{
							if (rand(1) == 1)
							{
								link.l1 = StringFromKey("Common_Store_321", RandPhraseSimple(
											StringFromKey("Common_Store_319"),
											StringFromKey("Common_Store_320")));
								link.l1.go = "generate_quest_not_closed";
							}
						}
					}
				}
				else
				{
					link.l1 = StringFromKey("Common_Store_322", GetAddress_FormToNPC(NPChar));
					link.l1.go = "generate_quest";
				}
				// --> на кредитный генератор
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = pcharrepphrase(
								StringFromKey("Common_Store_325", RandPhraseSimple(
										StringFromKey("Common_Store_323", pchar),
										StringFromKey("Common_Store_324"))),
								StringFromKey("Common_Store_328", RandPhraseSimple(
										StringFromKey("Common_Store_326", pchar),
										StringFromKey("Common_Store_327"))));

					link.l3.go = "LoanForAll";
				}
				//квест мэра - на связь с нашим шпионом
				if (CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
				{
					link.l4 = StringFromKey("Common_Store_331", RandPhraseSimple(
								StringFromKey("Common_Store_329", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))),
								StringFromKey("Common_Store_330", pchar, GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)))));
					link.l4.go = "IntelligenceForAll";
				}
				// ----------------- квест получения Синей Птицы, сдаём квест -----------------
				if (pchar.questTemp.BlueBird == "weWon" && pchar.questTemp.BlueBird.traiderId == npchar.id)
				{
					link.l1 = StringFromKey("Common_Store_332", pchar);
					link.l1.go = "RBlueBirdWon";
				}
				if (pchar.questTemp.BlueBird == "DieHard" && pchar.questTemp.BlueBird.traiderId == npchar.id)
				{
					link.l1 = StringFromKey("Common_Store_333", pchar);
					link.l1.go = "RBlueBirdDieHard";
				}
				if (pchar.questTemp.BlueBird == "returnMoney" && pchar.questTemp.BlueBird.traiderId == npchar.id && sti(pchar.questTemp.BlueBird.count) > 0)
				{
					link.l1 = StringFromKey("Common_Store_334");
					link.l1.go = "RBlueBird_retMoney_1";
				}
				if (pchar.questTemp.BlueBird == "finish" && pchar.questTemp.BlueBird.traiderId == npchar.id)
				{
					link.l1 = StringFromKey("Common_Store_335");
					link.l1.go = "RBlueBird_retMoney_3";
				}
				// ----------------- квест получения Синей Птицы, продолжение -----------------
				//homo 25/06/06 слухи
				link.l6 = pcharrepphrase(
							StringFromKey("Common_Store_338", RandPhraseSimple(
									StringFromKey("Common_Store_336"),
									StringFromKey("Common_Store_337"))),
							StringFromKey("Common_Store_341", RandPhraseSimple(
									StringFromKey("Common_Store_339", pchar),
									StringFromKey("Common_Store_340"))));

				link.l6.go = "rumours_trader";

				// ugeen --> склад товаров для ГГ
				if (CheckAttribute(NPChar, "Storage"))
				{
					if (CheckAttribute(NPChar, "Storage.Activate"))
					{
						link.l7 = StringFromKey("Common_Store_342");
						link.l7.go = "storage_0";
						link.l8 = StringFromKey("Common_Store_343", pchar);
						link.l8.go = "storage_04";
					}
					else
					{
						if (!CheckAttribute(NPChar, "Storage.NoActivate") && CheckAttribute(pchar, "questTemp.BlueBird.speakWon"))
						{
							link.l7 = StringFromKey("Common_Store_344");
							link.l7.go = "storage_01";
						}
					}
				}
				// <-- ugeen

				// <-- homo
				link.l99 = StringFromKey("Common_Store_345");
				link.l99.go = "no_quests";
			}
			else
			{
				link.l1 = NPCharRepPhrase(npchar,
						pcharrepphrase(
								StringFromKey("Common_Store_346", pchar, RandSwear()),
								StringFromKey("Common_Store_347", GetFullName(npchar))),
						pcharrepphrase(
								StringFromKey("Common_Store_348"),
								StringFromKey("Common_Store_349", pchar)));
				link.l1.go = "exit";
				// --> на кредитный генератор
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = pcharrepphrase(
								StringFromKey("Common_Store_352", RandPhraseSimple(
										StringFromKey("Common_Store_350", pchar),
										StringFromKey("Common_Store_351"))),
								StringFromKey("Common_Store_355", RandPhraseSimple(
										StringFromKey("Common_Store_353", pchar),
										StringFromKey("Common_Store_354"))));

					link.l3.go = "LoanForAll";
				}
				//квест мэра - на связь с нашим шпионом
				if (CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
				{
					link.l7 = StringFromKey("Common_Store_358", RandPhraseSimple(
								StringFromKey("Common_Store_356", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))),
								StringFromKey("Common_Store_357", pchar, GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)))));
					link.l7.go = "IntelligenceForAll";
				}
			}
		break;

		case "generate_quest":
			if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
			{
				npchar.quest.trade_date = lastspeak_date;
				//проверка враждебности нам страны торговца
				if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
				{
					dialog.text = StringFromKey("Common_Store_359", NationNameInstrumental(sti(NPChar.nation)));
					link.l1 = StringFromKey("Common_Store_360");
					link.l1.go = "exit";
				}
				else
				{
					// проверка на проф пригодность -->
					//                    if (isBadReputation(pchar, 40))
					if (PlayerRPGCheck_BadReputation(40, false))
					{
						dialog.text = StringFromKey("Common_Store_363", RandSwear(), GetFullName(pchar), RandPhraseSimple(
									StringFromKey("Common_Store_361"),
									StringFromKey("Common_Store_362")));
						link.l1 = StringFromKey("Common_Store_366", RandPhraseSimple(
									StringFromKey("Common_Store_364"),
									StringFromKey("Common_Store_365", RandSwear(), GetFullName(npchar))));
						link.l1.go = "exit";
						break;
					}
					// проверка на проф пригодность <--

					// KZ > работа перка "Искусство сделок" - персонаж всегда находит больше возможностей для выгодных сделок
					if (CheckOfficersPerk(pchar, "ArtOfDeals"))
					{
						TEV.CT = "";
						TEV.CT.Stores = "";        TEV.CT.Stores.Limits = "";
						TEV.CT.StoredGoods = "";    TEV.CT.StoredGoods.Limits = "";

						aref arFracht; makearef(arFracht, TEV.CT);
						iTmp = 0; cn = 0;

						for (i = 0; i < 3; i++)
						{
							attrL = i + 1;

							// > невраждебная торговцу нация
							sTemp = "Nation." + attrL;
							arFracht.(sTemp) = GenerateNationTrade(sti(NPChar.nation), false);
							if (sti(arFracht.(sTemp)) >= 0) cn++;
							else break;

							// > целевой магазин
							sTemp = "StoreMan." + attrL;
							arFracht.(sTemp) = findStoreMan(NPChar, sti(arFracht.Nation.(attrL)));
							if (sti(arFracht.(sTemp)) >= 0) iTmp++;
							else break;

							// > по возможности разные города
							if (HasStr(arFracht.Stores, arFracht.(sTemp)))
							{
								while (CheckAttribute(&TEV, "CT.Stores.Limits") && HasStr(arFracht.Stores, arFracht.(sTemp)))
								{
									arFracht.(sTemp) = findStoreMan(NPChar, sti(arFracht.Nation.(attrL)));
									TEV.CT.Stores.Limits = sti(TEV.CT.Stores.Limits) + 1;

									if (sti(TEV.CT.Stores.Limits) >= STORE_QUANTITY)
										DeleteAttribute(&TEV, "CT.Stores.Limits");
								}
							}

							arFracht.Stores = arFracht.Stores + " " + arFracht.(sTemp);

							// > целевой товар
							sTemp = "Goods." + attrL;
							arFracht.(sTemp) = GOOD_CHOCOLATE + idRand(npchar.id + "generate_quest", GOOD_BRICK - GOOD_CHOCOLATE);

							// > по возможности разные товары
							if (HasStr(arFracht.StoredGoods, arFracht.(sTemp)))
							{
								while (CheckAttribute(&TEV, "CT.StoredGoods.Limits") && HasStr(arFracht.StoredGoods, arFracht.(sTemp)))
								{
									arFracht.(sTemp) = GOOD_CHOCOLATE + rand(GOOD_BRICK - GOOD_CHOCOLATE);
									TEV.CT.StoredGoods.Limits = sti(TEV.CT.StoredGoods.Limits) + 1;

									if (sti(TEV.CT.StoredGoods.Limits) >= GOODS_QUANTITY)
										DeleteAttribute(&TEV, "CT.StoredGoods.Limits");
								}
							}

							arFracht.StoredGoods = arFracht.StoredGoods + " " + arFracht.(sTemp);

							// > кол-во товара
							arFracht.Quantity.(attrL) = GetSquadronFreeSpace(pchar, sti(arFracht.(sTemp))) - sti(Goods[sti(arFracht.(sTemp))].Units) - 10;

							// > целевой остров
							sTemp = "Island." + attrL;
							arFracht.(sTemp) = GetIslandByCityName(Characters[sti(arFracht.StoreMan.(attrL))].city);
							arFracht.(sTemp).Name.(attrL) = StringFromKey("Common_Store_367", XI_ConvertString(arFracht.(sTemp) + "Pre"));

							// > сколько дней в среднем занимает путь от текущей колонии до пункта назначения
							sTemp = "Days." + attrL;
							arFracht.(sTemp) = GetMaxDaysFromIsland2Island(GetArealByCityName(NPChar.city), GetArealByCityName(Characters[sti(arFracht.StoreMan.(attrL))].city));

							// > срок доставки
							sTemp = "Expire." + attrL;
							/// сроки > выбрать что-то одно
							//arFracht.(sTemp) = sti(arFracht.Days.(attrL)) - (drandEx(MakeInt(sti(arFracht.Days.(attrL)) / 2.5), true) + 1 + drandEx(MakeInt(3 * sti(arFracht.Days.(attrL)) / 8) - 1, true)); // < CSP
							//arFracht.(sTemp) = 3 + rand(4) + (sti(arFracht.Days.(attrL)) - (drandEx(MakeInt(sti(arFracht.Days.(attrL)) / 2.5), true) + 1 + drandEx(MakeInt(3 * sti(arFracht.Days.(attrL)) / 8) - 1, true))); // < +3-7 дней к сроку CSP
							arFracht.(sTemp) = 25 + rand(5); // < ГПК 1.3.2 > 25-30 дней

							// > оплата
							sTemp = "Money." + attrL;
							/// оплата > выбрать что-то одно
							//arFracht.(sTemp) = makeint(sti(arFracht.Quantity.(attrL)) / sti(Goods[sti(arFracht.Goods.(attrL))].Units) * sti(Goods[sti(arFracht.Goods.(attrL))].Weight) * sti(arFracht.Days.(attrL)) / 2 / sti(arFracht.Expire.(attrL))) * (9 + sti(pchar.Skill.Commerce) / 20); // < CSP (меньше денег)
							arFracht.(sTemp) = makeint((sti(arFracht.Quantity.(attrL)) * sti(Goods[sti(arFracht.Goods.(attrL))].Weight) / sti(Goods[sti(arFracht.Goods.(attrL))].Units)) * (4 + rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5); // < ГПК 1.3.2 (больше денег)
						}

						if (cn < 3)
						{
							dialog.text = NPCharRepPhrase(npchar,
									StringFromKey("Common_Store_368", GetAddress_Form(NPChar)),
									StringFromKey("Common_Store_369"));
							link.l1 = StringFromKey("Common_Store_370");
							link.l1.go = "exit";
						}
						else
						{
							if (iTmp > 2)
							{
								RecalculateSquadronCargoLoad(pchar); // fix неверное место

								if (sti(arFracht.Quantity.1) < 100 || sti(arFracht.Quantity.2) < 100 || sti(arFracht.Quantity.3) < 100) // это в шт. товара
								{
									dialog.text = NPCharRepPhrase(npchar,
											StringFromKey("Common_Store_371"),
											StringFromKey("Common_Store_372", GetFullName(pchar)));
									link.l1 = NPCharRepPhrase(npchar,
											StringFromKey("Common_Store_373"),
											StringFromKey("Common_Store_374"));
									link.l1.go = "exit";
								}
								else
								{
									dialog.text = StringFromKey("Common_Store_375");

									for (i = 0; i < 3; i++)
									{
										sTemp = i + 1;
										attrL = "l" + (i + 1);
										link.(attrL) = StringFromKey("Common_Store_376", FindMoneyString(sti(arFracht.Money.(sTemp))), GetGoodsNameAlt(sti(arFracht.Goods.(sTemp))), FindQtyString(sti(arFracht.Quantity.(sTemp))), XI_ConvertString("Colony" + Characters[sti(arFracht.storeMan.(sTemp))].city + "Acc"), arFracht.Island.(sTemp).Name.(sTemp), FindDaysString(makeint(sti(arFracht.Expire.(sTemp)))));
										link.(attrL).go = "exit_trade_" + sTemp;
									}

									link.l99 = StringFromKey("Common_Store_377");
									link.l99.go = "exit";
								}
							}
							else
							{
								dialog.text = StringFromKey("Common_Store_378", XI_ConvertString(NationShortName(sti(NPChar.nation)) + "hunter"));
								link.l1 = StringFromKey("Common_Store_379");
								link.l1.go = "exit";
							}
						}
					}
					// KZ < работа перка "Искусство сделок"
					else
					{
						int iTradeNation = GenerateNationTrade(sti(NPChar.nation), false);

						if (iTradeNation < 0)
						{
							dialog.text = NPCharRepPhrase(npchar,
									StringFromKey("Common_Store_380", GetAddress_Form(NPChar)),
									StringFromKey("Common_Store_381"));
							link.l1 = StringFromKey("Common_Store_382");
							link.l1.go = "exit";
						}
						else
						{
							int storeMan = findStoreMan(NPChar, iTradeNation);
							if (storeMan > 0)
							{
								//проверяем импорт/экспорт
								iTradeGoods = rand(GOOD_BRICK); //Рабы и золото не даем, бомбы и еду - да!!
								//проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
								RecalculateSquadronCargoLoad(pchar); // fix неверное место
								iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
								if (iQuantityGoods < 100)// это в шт. товара
								{
									dialog.text = NPCharRepPhrase(npchar,
											StringFromKey("Common_Store_383"),
											StringFromKey("Common_Store_384", GetFullName(pchar)));
									link.l1 = NPCharRepPhrase(npchar,
											StringFromKey("Common_Store_385"),
											StringFromKey("Common_Store_386"));
									link.l1.go = "exit";
								}
								else
								{
									iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods / 3)) - sti(Goods[iTradeGoods].Units) - 10;
									iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4 + rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

									pchar.CargoQuest.iTradeGoods = iTradeGoods;
									pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
									pchar.CargoQuest.iMoney = iMoney;
									pchar.CargoQuest.iTradeNation = iTradeNation;
									pchar.CargoQuest.iDaysExpired = 25 + rand(5);

									pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
									pchar.CargoQuest.iTradeIsland = GetIslandNameByCity(Characters[storeMan].city);
									pchar.CargoQuest.TraderID = Characters[storeMan].id;
									pchar.CargoQuest.GiveTraderID = NPChar.id;
									SaveCurrentQuestDateParam("CargoQuest");
									string sNation = XI_ConvertString("Colony" + Characters[storeMan].city);
									sTemp = "";
									if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
									{
										sTemp = StringFromKey("Common_Store_387", XI_ConvertString(pchar.CargoQuest.iTradeIsland + "Pre"));
									}
									dialog.text = StringFromKey("Common_Store_388", GetGoodsNameAlt(iTradeGoods), FindQtyString(iQuantityGoods), sNation, sTemp, FindDaysString(makeint(pchar.CargoQuest.iDaysExpired)), FindMoneyString(iMoney));
									link.l1 = StringFromKey("Common_Store_389", pchar);
									link.l1.go = "exit_trade";
									link.l2 = StringFromKey("Common_Store_390");
									link.l2.go = "exit";
								}
							}
							else
							{
								dialog.text = StringFromKey("Common_Store_391", XI_ConvertString(NationShortName(sti(NPChar.nation)) + "hunter"));
								link.l1 = StringFromKey("Common_Store_392");
								link.l1.go = "exit";
							}
						}
					}
				}
			}
			else
			{
				dialog.text = NPCharRepPhrase(npchar,
						StringFromKey("Common_Store_393"),
						StringFromKey("Common_Store_394"));
				link.l1 = NPCharRepPhrase(npchar,
						StringFromKey("Common_Store_395"),
						StringFromKey("Common_Store_396"));
				link.l1.go = "exit";
			}
		break;

		case "exit_trade_1":
			FrachtResult(NPChar, 1);
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "exit_trade_2":
			FrachtResult(NPChar, 2);
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "exit_trade_3":
			FrachtResult(NPChar, 3);
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "exit_trade":
			AddDialogExitQuest("trade_quest_open");
			Nextdiag.CurrentNode = Nextdiag.TempNode;
			DialogExit();
		break;

		case "generate_quest_2":
			if (pchar.quest.generate_trade_quest_progress == "failed")
			{
				dialog.text = StringFromKey("Common_Store_397", RandSwear());
				link.l1 = StringFromKey("Common_Store_398", pchar);
				link.l1.go = "generate_quest_failed";
				link.l9 = StringFromKey("Common_Store_399");
				link.l9.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
				iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);

				dialog.text = StringFromKey("Common_Store_400", GetGoodsNameAlt(iTradeGoods), FindQtyString(iQuantityGoods), FindMoneyString(sti(pchar.CargoQuest.iMoney)));
				link.l1 = StringFromKey("Common_Store_401");
				link.l1.go = "generate_quest_ready";
			}
		break;

		case "generate_quest_ready":
			iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
			iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);
			// блок кидалова нас на бабки -->
			if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
			{
				dialog.text = StringFromKey("Common_Store_404", RandSwear(), GetAddress_Form(NPChar), RandPhraseSimple(
							StringFromKey("Common_Store_402"),
							StringFromKey("Common_Store_403")));
				link.l1 = StringFromKey("Common_Store_407", RandSwear(), RandPhraseSimple(
							StringFromKey("Common_Store_405", pchar),
							StringFromKey("Common_Store_406")));
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, 2);
				AddCharacterExpToSkill(pchar, "Sailing", 60);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 15);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";

				AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Pre"));
				CloseQuestHeader("DELIVERY_TRADE_QUEST");
				break;
			}
			// блок кидалова нас на бабки <--
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
				dialog.text = StringFromKey("Common_Store_408", FindQtyString(iTmp));
				link.l9 = StringFromKey("Common_Store_411", RandPhraseSimple(
							StringFromKey("Common_Store_409"),
							StringFromKey("Common_Store_410", RandSwear())));
				link.l9.go = "exit";
				AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			}
			else
			{
				dialog.text = StringFromKey("Common_Store_412", GetFullName(pchar));
				link.l1 = StringFromKey("Common_Store_413");
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, 3);
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterExpToSkill(pchar, "COMMERCE", 100);

				AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));

				OfficersReaction("good");

				AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Gen"));
				CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;

		case "generate_quest_failed":
			iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
			iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);
			iMoney = 3 * makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = StringFromKey("Common_Store_414", FindMoneyString(iMoney));
			link.l1 = StringFromKey("Common_Store_415");
			link.l1.go = "exit";
			if (sti(pchar.Money) >= iMoney)
			{
				link.l2 = StringFromKey("Common_Store_416");
				link.l2.go = "generate_quest_failed_2";
			}
			else
			{
				AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindMoneyString(iMoney));
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Gen"));
			}
		break;

		case "generate_quest_failed_2":
			iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
			iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);
			iMoney = 3 * makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
			dialog.text = StringFromKey("Common_Store_417");
			link.l1 = StringFromKey("Common_Store_418");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 10);
			AddCharacterExpToSkill(pchar, "Sailing", -100);
			AddCharacterExpToSkill(pchar, "Leadership", -50);
			AddCharacterExpToSkill(pchar, "COMMERCE", -100);

			AddMoneyToCharacter(pchar, -iMoney);
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

			AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindMoneyString(iMoney));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Gen"));
			CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;

		case "generate_quest_not_closed":
			iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
			iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);

			dialog.text = StringFromKey("Common_Store_419", GetGoodsNameAlt(iTradeGoods), XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony));

			link.l1 = StringFromKey("Common_Store_420");
			link.l1.go = "exit";
		break;

		case "generate_quest_cannot_done":
			dialog.text = StringFromKey("Common_Store_421", RandSwear(), GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Common_Store_422");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Common_Store_423");
			link.l2.go = "generate_quest_cannot_done_2";

		break;

		case "generate_quest_cannot_done_2":
			iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
			iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);
			if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
			{
				dialog.text = StringFromKey("Common_Store_424", FindQtyString(iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods)));
				link.l9 = StringFromKey("Common_Store_427", RandPhraseSimple(
							StringFromKey("Common_Store_425"),
							StringFromKey("Common_Store_426", RandSwear())));
				link.l9.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_Store_428");
				link.l1 = StringFromKey("Common_Store_429");
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -3);

				pchar.quest.generate_trade_quest_progress = "";
				pchar.quest.generate_trade_quest.over = "yes";
				RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));

				AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Pre"));
				CloseQuestHeader("DELIVERY_TRADE_QUEST");
			}
		break;

		case "no_quests":
			dialog.text = StringFromKey("Common_Store_430");
			link.l1 = StringFromKey("Common_Store_431");
			link.l1.go = "node_1";
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Exit":
			if (pchar.questTemp.Ascold == "canTakeQuest" && pchar.questTemp.Ascold.TraderId == npchar.id)//eddy. Аскольд, начало
			{
				dialog.Text = StringFromKey("Common_Store_432", pchar);
				Link.l1 = StringFromKey("Common_Store_433");
				Link.l1.go = "exit";
				SaveCurrentQuestDateParam("questTemp.Ascold");
				pchar.questTemp.Ascold = "Seek_powder";
				AddQuestRecord("Ascold", "1");
				AddQuestUserData("Ascold", "sName", GetFullName(npchar));
				AddQuestUserData("Ascold", "sCity", XI_ConvertString("Colony" + npchar.city + "Pre"));
				AddLandQuestmark_Main_WithCondition(npchar, "Ascold", "Ascold_SeekPowder_Trader_QuestMarkCondition");
				AddLandQuestmarkToFantoms_Main("ItemTrader", "Ascold", "");
				RemoveMapQuestMark(npchar.city + "_town", "Ascold");
			}
			else
			{
				Nextdiag.CurrentNode = Nextdiag.TempNode;
				DialogExit();
			}
		break;
	}
}

int findStoreMan(ref NPChar, int iTradeNation)
{
	ref ch;
	int n;
	int storeArray[STORE_QUANTITY];
	int howStore = 0;

	for (n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(ch, Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
			if (sti(ch.nation) != iTradeNation) continue;
			if (NPChar.id == ch.id) continue;
			if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader") continue; //нельзя доплыть
			if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
			if (GetIslandNameByCity(ch.city) == GetIslandNameByCity(NPChar.city)) continue; // хрен вам, а не читы!
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
		return storeArray[rand(howStore - 1)];
	}
}

void FrachtResult(ref rChar, int iRes)
{
	if (!CheckAttribute(&TEV, "CT")) return;

	Restrictor(&iRes, 1, 3);

	aref arFracht; makearef(arFracht, TEV.CT);
	ref chr = GetCharacter(sti(arFracht.StoreMan.(iRes)));

	pchar.CargoQuest.iTradeGoods = arFracht.Goods.(iRes);
	pchar.CargoQuest.iQuantityGoods = arFracht.Quantity.(iRes);
	pchar.CargoQuest.iMoney = arFracht.Money.(iRes);
	pchar.CargoQuest.iTradeNation = arFracht.Nation.(iRes);
	pchar.CargoQuest.iDaysExpired = arFracht.Expire.(iRes);

	pchar.CargoQuest.iTradeColony = chr.city;
	pchar.CargoQuest.iTradeIsland = GetIslandNameByCity(chr.city);
	pchar.CargoQuest.TraderID = chr.id;
	pchar.CargoQuest.GiveTraderID = rChar.id;
	SaveCurrentQuestDateParam("CargoQuest");
}

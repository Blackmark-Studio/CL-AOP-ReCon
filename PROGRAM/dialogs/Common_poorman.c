#include "DIALOGS\Rumours\Simple_rumors.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	/*NPChar.FileDialog2 = "DIALOGS\Poorman\" + NPChar.City + "_Poorman.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}*/
	// вызов диалога по городам <--

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 25/06/06

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				//если ГГ начал мочить бродяг -->
				if (pchar.questTemp.LSC == "PoorMurderBegin")
				{
					dialog.text = StringFromKey("Common_poorman_4", LinkRandPhrase(
								StringFromKey("Common_poorman_1", pchar),
								StringFromKey("Common_poorman_2"),
								StringFromKey("Common_poorman_3")));
					link.l1 = StringFromKey("Common_poorman_8", LinkRandPhrase(
								StringFromKey("Common_poorman_5"),
								StringFromKey("Common_poorman_6"),
								StringFromKey("Common_poorman_7")));
					link.l1.go = "exit";
					break;
				}
				//<-- если ГГ начал мочить бродяг 
				//зачарованный город -->
				if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
				{
					dialog.text = StringFromKey("Common_poorman_9");
					link.l1 = StringFromKey("Common_poorman_10");
					link.l1.go = "exit";
					break;
				}
				if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
				{
					dialog.text = StringFromKey("Common_poorman_11");
					link.l1 = StringFromKey("Common_poorman_12");
					link.l1.go = "exit";
					break;
				}
				//<-- зачарованный город 
				dialog.text = StringFromKey("Common_poorman_16", LinkRandPhrase(
							StringFromKey("Common_poorman_13", GetFullName(npchar)),
							StringFromKey("Common_poorman_14", GetAddress_Form(NPChar), GetFullName(npchar)),
							StringFromKey("Common_poorman_15", GetFullName(npchar), GetAddress_Form(NPChar))));
				link.l1 = StringFromKey("Common_poorman_19", RandPhraseSimple(
							StringFromKey("Common_poorman_17"),
							StringFromKey("Common_poorman_18")));
				link.l1.go = "First time";
				npchar.quest.meeting = "1";
			}
			else
			{
				//если ГГ начал мочить бродяг -->
				if (pchar.questTemp.LSC == "PoorMurderBegin")
				{
					dialog.text = StringFromKey("Common_poorman_23", LinkRandPhrase(
								StringFromKey("Common_poorman_20", pchar),
								StringFromKey("Common_poorman_21"),
								StringFromKey("Common_poorman_22")));
					link.l1 = StringFromKey("Common_poorman_27", LinkRandPhrase(
								StringFromKey("Common_poorman_24"),
								StringFromKey("Common_poorman_25"),
								StringFromKey("Common_poorman_26")));
					link.l1.go = "exit";
					break;
				}
				//<-- если ГГ начал мочить бродяг
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Common_poorman_28"),
							StringFromKey("Common_poorman_29"),
							StringFromKey("Common_poorman_30"),
							StringFromKey("Common_poorman_31"), "block", 1, npchar, Dialog.CurrentNode);
				//разговарием с нищими о наезде
				if (pchar.questTemp.LSC == "SignOnPoorMurder" || pchar.questTemp.LSC == "PoorIsGood")
				{
					if (CheckAttribute(pchar, "questTemp.LSC.qtyTalk.headPoormanId") && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id)
					{
						link.l1 = StringFromKey("Common_poorman_32", pchar);
						link.l1.go = "PoorHeadMan";
						npchar.quest.talk = true; //больше не говорить
						break;
					}
					if (!CheckAttribute(npchar, "quest.talk"))
					{
						if (!CheckAttribute(pchar, "questTemp.LSC.qtyTalk")) pchar.questTemp.LSC.qtyTalk = 0;
						pchar.questTemp.LSC.qtyTalk = sti(pchar.questTemp.LSC.qtyTalk) + 1; //инкремент на базары по душам
						if (sti(pchar.questTemp.LSC.qtyTalk) > 4) pchar.questTemp.LSC.qtyTalk = 4;
						switch (pchar.questTemp.LSC.qtyTalk)
						{
							case "1":
								link.l1 = StringFromKey("Common_poorman_33");
								npchar.quest.talk = true; //больше не говорить
							break;
							case "2":
								link.l1 = StringFromKey("Common_poorman_34");
								npchar.quest.talk = true; //больше не говорить
							break;
							case "3":
								link.l1 = StringFromKey("Common_poorman_35");
								npchar.quest.talk = true; //больше не говорить
							break;
							case "4":
								link.l1 = StringFromKey("Common_poorman_36");
							break;
						}
						link.l1.go = "GoodTalk_" + pchar.questTemp.LSC.qtyTalk;
						SetCurrentQuestmark(npchar); // обновим метку
						break;
					}
				}
				//----------------------------------------------------------------
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Common_poorman_37"),
							StringFromKey("Common_poorman_38"),
							StringFromKey("Common_poorman_39"),
							StringFromKey("Common_poorman_40", pchar), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "pester", npchar, Dialog.CurrentNode);
				link.l2 = StringFromKey("Common_poorman_43", RandPhraseSimple(
							StringFromKey("Common_poorman_41"),
							StringFromKey("Common_poorman_42")));
				link.l2.go = "Whants";
				link.l3 = StringFromKey("Common_poorman_47", LinkRandPhrase(
							StringFromKey("Common_poorman_44"),
							StringFromKey("Common_poorman_45"),
							StringFromKey("Common_poorman_46", pchar)));
				link.l3.go = "rumours_poor";
				// --------------- линейка ГПК ---------------
				//нашёл письмо в сундуке Виллемстада
				if (pchar.questTemp.LSC == "CanFoundStuvesantKey" && CheckCharacterItem(pchar, "letter_LSC") && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id)
				{
					link.l1 = StringFromKey("Common_poorman_48", pchar);
					link.l1.go = "FoundLetter";
				}
				//базар о том, что нашёл причину заказа на нищих
				if (pchar.questTemp.LSC == "readyGoLSC" && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id)
				{
					link.l1 = StringFromKey("Common_poorman_49");
					link.l1.go = "GoLSC";
				}
				//обошёл все кладбища, не нашел мёртвых с косами и тишину
				if (pchar.questTemp.LSC == "UndertakersSurveyCompleteLSC" && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id)
				{
					link.l1 = StringFromKey("Common_poorman_50", pchar);
					link.l1.go = "SurveyCompleteLSC_1";
				}
				//расшифровал СЖ
				if (pchar.questTemp.LSC == "DecryptedLogLSC" && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id && CheckAttribute(npchar, "knowWhoYouAre"))
				{
					link.l1 = StringFromKey("Common_poorman_51");
					link.l1.go = "DecryptedLogLSC_1";
				}
				//вопросы по расшифровке СЖ
				if (pchar.questTemp.LSC == "LogbookDecryptedAndReadLSC" && pchar.questTemp.LSC.qtyTalk.headPoormanId == npchar.id && CheckAttribute(npchar, "knowWhoYouAre"))
				{
					link.l1 = StringFromKey("Common_poorman_52", pchar);
					link.l1.go = "AnswerForLogLSC_1";
				}
			}
			NextDiag.TempNode = "First time";
		break;
		case "pester":
			dialog.text = StringFromKey("Common_poorman_55", RandPhraseSimple(
						StringFromKey("Common_poorman_53", pchar),
						StringFromKey("Common_poorman_54", pchar)));
			link.l1 = StringFromKey("Common_poorman_56");
			link.l1.go = "exit";
		break;
		//выходы
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//милостыня
		case "Whants":
			if (!CheckAttribute(npchar, "wants_date") || GetNpcQuestPastDayParam(npchar, "wants_date") >= 1 || bBettaTestMode)
			{
				dialog.text = PCharRepPhrase(
							StringFromKey("Common_poorman_57", GetAddress_Form(NPChar)),
							StringFromKey("Common_poorman_58", GetAddress_Form(NPChar)));
				link.l1 = StringFromKey("Common_poorman_61", RandPhraseSimple(
							StringFromKey("Common_poorman_59"),
							StringFromKey("Common_poorman_60")));
				link.l1.go = "exit";
				Link.l2 = StringFromKey("Common_poorman_62");
				Link.l2.go = "Whants_1";
			}
			else
			{
				dialog.text = PCharRepPhrase(
							StringFromKey("Common_poorman_63"),
							StringFromKey("Common_poorman_64", GetAddress_Form(NPChar)));
				link.l1 = StringFromKey("Common_poorman_67", RandPhraseSimple(
							StringFromKey("Common_poorman_65"),
							StringFromKey("Common_poorman_66")));
				link.l1.go = "exit";
			}
		break;
		case "Whants_1":
			dialog.text = StringFromKey("Common_poorman_68", GetAddress_Form(NPChar));
			Link.l1.edit = 2;
			link.l1 = "";
			link.l1.go = "Whants_2";
		break;
		case "Whants_2":
			SaveCurrentNpcQuestDateParam(npchar, "wants_date");
			int iTemp = sti(stripblank(dialogEditStrings[2]));

			// Dolphin. Французская линейка, поиск Гранье ->
			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL2_s1" && pchar.location == "FortFrance_town")
			{
				dialog.text = StringFromKey("Common_poorman_69");
				link.l1 = StringFromKey("Common_poorman_70");
				link.l1.go = "FL2_1";
				break;
			}
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = StringFromKey("Common_poorman_71");
				link.l1 = StringFromKey("Common_poorman_72");
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
				break;
			}
			if (iTemp > 0 && iTemp <= 100)
			{
				dialog.text = StringFromKey("Common_poorman_73", FindMoneyString(iTemp), GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_poorman_74");
				link.l1.go = "exit";
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 100 && iTemp <= 1000)
			{
				dialog.text = StringFromKey("Common_poorman_75", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_poorman_76", pchar);
				link.l1.go = "exit";
				OfficersReaction("good");
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 1000 && iTemp <= 5000)
			{
				dialog.text = StringFromKey("Common_poorman_77", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_poorman_78");
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, sti(iTemp / 2000 + 0.5));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 5000 && iTemp <= 50000)
			{
				dialog.text = StringFromKey("Common_poorman_79", pchar, GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_poorman_80");
				link.l1.go = "exit";
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), sti(iTemp / 10000 + 0.5));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 50000 && iTemp <= 100000)
			{
				dialog.text = StringFromKey("Common_poorman_81", pchar, GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_poorman_82");
				link.l1.go = "exit";
				AddCharacterExpToSkill(pchar, "Leadership", sti(iTemp / 5000));
				AddCharacterExpToSkill(pchar, "Fortune", sti(iTemp / 5000));
				pchar.money = sti(pchar.money) - iTemp;
			}
			if (iTemp > 100000)
			{
				dialog.text = StringFromKey("Common_poorman_83", GetAddress_Form(NPChar), FindMoneyString(iTemp));
				link.l1 = StringFromKey("Common_poorman_84");
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -2);
			}
		break;

		//==============================================================================================
		// Французская линейка - поиск Гранье
		case "FL2_1":
			dialog.text = StringFromKey("Common_poorman_85");
			link.l1 = StringFromKey("Common_poorman_86");
			link.l1.go = "FL2_2";
		break;

		case "FL2_2":
			dialog.text = StringFromKey("Common_poorman_87");
			link.l1 = StringFromKey("Common_poorman_88");
			link.l1.go = "FL2_3";
		break;

		case "FL2_3":
			dialog.text = StringFromKey("Common_poorman_89");
			link.l1 = StringFromKey("Common_poorman_90");
			link.l1.go = "FL2_4";
		break;

		case "FL2_4":
			dialog.text = StringFromKey("Common_poorman_91");
			link.l1 = StringFromKey("Common_poorman_92");
			link.l1.go = "FL2_5";
		break;

		case "FL2_5":
			dialog.text = StringFromKey("Common_poorman_93");
			link.l1 = StringFromKey("Common_poorman_94");
			link.l1.go = "FL2_6";
		break;

		case "FL2_6":
			dialog.text = StringFromKey("Common_poorman_95");
			link.l1 = StringFromKey("Common_poorman_96");
			link.l1.go = "FL2_7";
		break;

		case "FL2_7":
			dialog.text = StringFromKey("Common_poorman_97");
			link.l1 = StringFromKey("Common_poorman_98");
			link.l1.go = "exit";

			AddDialogExitQuest("FL2_s2");
		break;

		//линейка ГПК, разговоры по душам с нищими после заказа 
		case "GoodTalk_1":
			dialog.text = StringFromKey("Common_poorman_99");
			link.l1 = StringFromKey("Common_poorman_100");
			link.l1.go = "GoodTalk_1_1";
		break;
		case "GoodTalk_1_1":
			dialog.text = StringFromKey("Common_poorman_101", pchar);
			link.l1 = StringFromKey("Common_poorman_102");
			link.l1.go = "GoodTalk_1_2";
		break;
		case "GoodTalk_1_2":
			dialog.text = StringFromKey("Common_poorman_103");
			link.l1 = StringFromKey("Common_poorman_104");
			link.l1.go = "GoodTalk_1_3";
		break;
		case "GoodTalk_1_3":
			dialog.text = StringFromKey("Common_poorman_105", pchar);
			link.l1 = StringFromKey("Common_poorman_106", pchar);
			link.l1.go = "GoodTalk_1_4";
		break;
		case "GoodTalk_1_4":
			dialog.text = StringFromKey("Common_poorman_107");
			link.l1 = StringFromKey("Common_poorman_108", pchar);
			link.l1.go = "exit";
		break;

		case "GoodTalk_2":
			dialog.text = StringFromKey("Common_poorman_109");
			link.l1 = StringFromKey("Common_poorman_110");
			link.l1.go = "GoodTalk_2_1";
		break;
		case "GoodTalk_2_1":
			dialog.text = StringFromKey("Common_poorman_111");
			link.l1 = StringFromKey("Common_poorman_112");
			link.l1.go = "GoodTalk_2_2";
		break;
		case "GoodTalk_2_2":
			dialog.text = StringFromKey("Common_poorman_113");
			link.l1 = StringFromKey("Common_poorman_114");
			link.l1.go = "GoodTalk_2_3";
		break;
		case "GoodTalk_2_3":
			dialog.text = StringFromKey("Common_poorman_115", pchar);
			link.l1 = StringFromKey("Common_poorman_116");
			link.l1.go = "GoodTalk_2_4";
		break;
		case "GoodTalk_2_4":
			dialog.text = StringFromKey("Common_poorman_117");
			link.l1 = StringFromKey("Common_poorman_118", pchar);
			link.l1.go = "GoodTalk_2_5";
		break;
		case "GoodTalk_2_5":
			dialog.text = StringFromKey("Common_poorman_119");
			link.l1 = StringFromKey("Common_poorman_120");
			link.l1.go = "exit";
		break;

		case "GoodTalk_3":
			dialog.text = StringFromKey("Common_poorman_121");
			link.l1 = StringFromKey("Common_poorman_122", pchar);
			link.l1.go = "GoodTalk_3_1";
		break;
		case "GoodTalk_3_1":
			dialog.text = StringFromKey("Common_poorman_123");
			link.l1 = StringFromKey("Common_poorman_124");
			link.l1.go = "GoodTalk_3_2";
		break;
		case "GoodTalk_3_2":
			dialog.text = StringFromKey("Common_poorman_125");
			link.l1 = StringFromKey("Common_poorman_126", pchar);
			link.l1.go = "GoodTalk_3_3";
		break;
		case "GoodTalk_3_3":
			dialog.text = StringFromKey("Common_poorman_127");
			link.l1 = StringFromKey("Common_poorman_128");
			link.l1.go = "GoodTalk_3_4";
		break;
		case "GoodTalk_3_4":
			ISS_PoorsMurder_Poorman_RemoveQuestMarks();
			pchar.questTemp.LSC.qtyTalk.headPoormanId = GetPoorHeadManId(npchar);
			sld = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			AddLandQuestMark_Main(sld, "ISS_PoorsMurder");
			dialog.text = StringFromKey("Common_poorman_129", GetFullName(sld), XI_ConvertString("Colony" + sld.city + "Pre"));
			link.l1 = StringFromKey("Common_poorman_130");
			link.l1.go = "exit";
			AddQuestRecord("ISS_PoorsMurder", "3");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("ISS_PoorsMurder", "sCity", XI_ConvertString("Colony" + sld.city + "Acc"));
			AddQuestUserData("ISS_PoorsMurder", "sName", GetFullName(sld));
		break;

		case "GoodTalk_4":
			dialog.text = StringFromKey("Common_poorman_131");
			link.l1 = StringFromKey("Common_poorman_132");
			link.l1.go = "GoodTalk_4_1";
		break;
		case "GoodTalk_4_1":
			sld = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			AddLandQuestMark_Main(sld, "ISS_PoorsMurder");
			dialog.text = StringFromKey("Common_poorman_133", XI_ConvertString("Colony" + sld.city + "Acc"), GetFullName(sld));
			link.l1 = StringFromKey("Common_poorman_134");
			link.l1.go = "exit";
		break;
		//основной бродяга
		case "PoorHeadMan":
			dialog.text = StringFromKey("Common_poorman_135", GetFullName(pchar));
			link.l1 = StringFromKey("Common_poorman_136");
			link.l1.go = "PoorHeadMan_1";
		break;
		case "PoorHeadMan_1":
			dialog.text = StringFromKey("Common_poorman_137");
			link.l1 = StringFromKey("Common_poorman_138");
			link.l1.go = "PoorHeadMan_2";
		break;
		case "PoorHeadMan_2":
			dialog.text = StringFromKey("Common_poorman_139");
			link.l1 = StringFromKey("Common_poorman_140");
			link.l1.go = "PoorHeadMan_3";
		break;
		case "PoorHeadMan_3":
			dialog.text = StringFromKey("Common_poorman_141");
			link.l1 = StringFromKey("Common_poorman_142");
			link.l1.go = "PoorHeadMan_4";
		break;
		case "PoorHeadMan_4":
			dialog.text = StringFromKey("Common_poorman_143");
			link.l1 = StringFromKey("Common_poorman_144");
			link.l1.go = "PoorHeadMan_5";
		break;
		case "PoorHeadMan_5":
			dialog.text = StringFromKey("Common_poorman_145");
			link.l1 = StringFromKey("Common_poorman_146");
			link.l1.go = "PoorHeadMan_6";
		break;
		case "PoorHeadMan_6":
			dialog.text = StringFromKey("Common_poorman_147");
			link.l1 = StringFromKey("Common_poorman_148");
			link.l1.go = "PoorHeadMan_7";
		break;
		case "PoorHeadMan_7":
			dialog.text = StringFromKey("Common_poorman_149");
			link.l1 = StringFromKey("Common_poorman_150", pchar);
			link.l1.go = "PoorHeadMan_8";
		break;
		case "PoorHeadMan_8":
			dialog.text = StringFromKey("Common_poorman_151", pchar);
			link.l1 = StringFromKey("Common_poorman_152");
			link.l1.go = "PoorHeadMan_9";
		break;
		case "PoorHeadMan_9":
			dialog.text = StringFromKey("Common_poorman_153", pchar);
			link.l1 = StringFromKey("Common_poorman_154");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toVillemstadResidence";
			AddQuestRecord("ISS_PoorsMurder", "4");
			//сработает прерывание, чтобы показать геймеру, где нужный сундук
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1 = "locator";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.location = "Villemstad_TownhallRoom";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.locator_group = "box";
			pchar.quest.LSC_enterStuvesantBox.win_condition.l1.locator = "private2";
			pchar.quest.LSC_enterStuvesantBox.function = "LSC_enterStuvesantBox";

			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
		break;
		//базар с основным после нахождения письма
		case "FoundLetter":
			dialog.text = StringFromKey("Common_poorman_155");
			link.l1 = StringFromKey("Common_poorman_156", pchar);
			link.l1.go = "FoundLetter_1";
		break;
		case "FoundLetter_1":
			dialog.text = StringFromKey("Common_poorman_157");
			link.l1 = StringFromKey("Common_poorman_158");
			link.l1.go = "FoundLetter_2";
			TakeItemFromCharacter(pchar, "letter_LSC");
		break;
		case "FoundLetter_2":
			dialog.text = StringFromKey("Common_poorman_159");
			link.l1 = StringFromKey("Common_poorman_160");
			link.l1.go = "FoundLetter_3";
		break;
		case "FoundLetter_3":
			dialog.text = StringFromKey("Common_poorman_161", pchar);
			link.l1 = StringFromKey("Common_poorman_162");
			link.l1.go = "FoundLetter_4";
		break;
		case "FoundLetter_4":
			dialog.text = StringFromKey("Common_poorman_163");
			link.l1 = StringFromKey("Common_poorman_164");
			link.l1.go = "FoundLetter_5";
		break;
		case "FoundLetter_5":
			dialog.text = StringFromKey("Common_poorman_165");
			link.l1 = StringFromKey("Common_poorman_166");
			link.l1.go = "FoundLetter_6";
		break;
		case "FoundLetter_6":
			dialog.text = StringFromKey("Common_poorman_167");
			link.l1 = StringFromKey("Common_poorman_168");
			link.l1.go = "FoundLetter_7";
		break;
		case "FoundLetter_7":
			dialog.text = StringFromKey("Common_poorman_169");
			link.l1 = StringFromKey("Common_poorman_170");
			link.l1.go = "FoundLetter_8";
		break;
		case "FoundLetter_8":
			dialog.text = StringFromKey("Common_poorman_171");
			link.l1 = StringFromKey("Common_poorman_172");
			link.l1.go = "FoundLetter_9";
		break;
		case "FoundLetter_9":
			dialog.text = StringFromKey("Common_poorman_173");
			link.l1 = StringFromKey("Common_poorman_174");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTalkStuvesant";
			pchar.questTemp.LSC.poorName = GetFullName(npchar);
			AddQuestRecord("ISS_PoorsMurder", "7");
			AddQuestUserData("ISS_PoorsMurder", "sName", pchar.questTemp.LSC.poorName);
			//снимаем прерывание на завал нищих, деньги уже не получить
			pchar.quest.ISS_Murder1.over = "yes";
			pchar.quest.ISS_Murder2.over = "yes";
			pchar.quest.ISS_Murder3.over = "yes";
			pchar.quest.ISS_Murder4.over = "yes";
			pchar.quest.ISS_Murder5.over = "yes";
			pchar.quest.ISS_Murder6.over = "yes";
			pchar.quest.ISS_Murder7.over = "yes";
			pchar.quest.ISS_Murder8.over = "yes";
			pchar.quest.ISS_Murder9.over = "yes";
			pchar.quest.ISS_Murder10.over = "yes";
			pchar.quest.ISS_Murder11.over = "yes";
			pchar.quest.ISS_Murder12.over = "yes";
			pchar.quest.ISS_Murder13.over = "yes";
			pchar.quest.ISS_Murder14.over = "yes";
			pchar.quest.ISS_Murder15.over = "yes";
			pchar.quest.ISS_Murder16.over = "yes";
			pchar.quest.ISS_Murder17.over = "yes";

			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			AddLandQuestMark_Main(CharacterFromId("Villemstad_tavernkeeper"), "ISS_PoorsMurder");
			AddLandQuestMark_Main(CharacterFromId("hol_gover"), "ISS_PoorsMurder");
		break;
		//базар с основным после завала Оливера Траста
		case "GoLSC":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Common_poorman_175"),
						StringFromKey("Common_poorman_176"),
						StringFromKey("Common_poorman_177"),
						StringFromKey("Common_poorman_178"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Common_poorman_179", npchar),
						StringFromKey("Common_poorman_180"),
						StringFromKey("Common_poorman_181"),
						StringFromKey("Common_poorman_182"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("GoLSC_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "GoLSC_1":
			dialog.text = StringFromKey("Common_poorman_183");
			link.l1 = StringFromKey("Common_poorman_184", pchar);
			link.l1.go = "GoLSC_2";
		break;
		case "GoLSC_2":
			dialog.text = StringFromKey("Common_poorman_185");
			link.l1 = StringFromKey("Common_poorman_186");
			link.l1.go = "GoLSC_3";
		break;
		case "GoLSC_3":
			dialog.text = StringFromKey("Common_poorman_187");
			link.l1 = StringFromKey("Common_poorman_188", pchar);
			link.l1.go = "GoLSC_4";
		break;
		case "GoLSC_4":
			dialog.text = StringFromKey("Common_poorman_189");
			link.l1 = StringFromKey("Common_poorman_190");
			link.l1.go = "GoLSC_5";
			GiveItem2Character(pchar, "TizerKey");
		break;
		case "GoLSC_5":
			dialog.text = StringFromKey("Common_poorman_191");
			link.l1 = StringFromKey("Common_poorman_192");
			link.l1.go = "GoLSC_6";
		break;
		case "GoLSC_6":
			dialog.text = StringFromKey("Common_poorman_193");
			link.l1 = StringFromKey("Common_poorman_194", pchar);
			link.l1.go = "GoLSC_7";
		break;
		case "GoLSC_7":
			dialog.text = StringFromKey("Common_poorman_195");
			link.l1 = StringFromKey("Common_poorman_196");
			link.l1.go = "GoLSC_8";
		break;
		case "GoLSC_8":
			dialog.text = "...";
			link.l1 = StringFromKey("Common_poorman_197");
			link.l1.go = "GoLSC_9";
		break;
		case "GoLSC_9":
			dialog.text = StringFromKey("Common_poorman_198", pchar, GetFullName(pchar));
			//			if ((GetCharacterSPECIAL(pchar, SPECIAL_P) + GetCharacterSPECIAL(pchar, SPECIAL_I)) >= 10)
			if (PlayerRPGCheck_SPECIAL_Sum(SPECIAL_P + "," + SPECIAL_I, 10))
			{
				link.l1 = StringFromKey("Common_poorman_199");
				link.l1.go = "GoLSC_10";
			}
			link.l2 = StringFromKey("Common_poorman_200");
			link.l2.go = "GoLSC_16";
			link.l3 = StringFromKey("Common_poorman_201", npchar.name);
			link.l3.go = "GoLSC_20";
		break;
		case "GoLSC_10":
			dialog.text = StringFromKey("Common_poorman_202");
			link.l1 = StringFromKey("Common_poorman_203", pchar);
			link.l1.go = "GoLSC_11";
			npchar.knowWhoYouAre = 1;
		break;
		case "GoLSC_11":
			dialog.text = "...";
			link.l1 = StringFromKey("Common_poorman_204");
			link.l1.go = "GoLSC_12";
		break;
		case "GoLSC_12":
			dialog.text = "...";
			link.l1 = StringFromKey("Common_poorman_205", pchar);
			link.l1.go = "GoLSC_13";
		break;
		case "GoLSC_13":
			dialog.text = "...";
			link.l1 = StringFromKey("Common_poorman_206");
			link.l1.go = "GoLSC_14";
		break;
		case "GoLSC_14":
			dialog.text = StringFromKey("Common_poorman_207", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Common_poorman_208");
			link.l1.go = "GoLSC_15";
		break;
		case "GoLSC_15":
			dialog.text = StringFromKey("Common_poorman_209");
			link.l1 = StringFromKey("Common_poorman_210", pchar);
			link.l1.go = "GoLSC_16";
			AddQuestRecord("ISS_PoorsMurder", "14");
			pchar.questTemp.LSC.bomjSpy = 1;
		break;
		case "GoLSC_16":
			dialog.text = StringFromKey("Common_poorman_211");
			link.l1 = StringFromKey("Common_poorman_212");
			link.l1.go = "GoLSC_17";
		break;
		case "GoLSC_17":
			dialog.text = StringFromKey("Common_poorman_213");
			link.l1 = StringFromKey("Common_poorman_214", pchar);
			link.l1.go = "GoLSC_18";
		break;
		case "GoLSC_18":
			dialog.text = StringFromKey("Common_poorman_215");
			link.l1 = StringFromKey("Common_poorman_216");
			link.l1.go = "GoLSC_19";
		break;
		case "GoLSC_19":
			dialog.text = StringFromKey("Common_poorman_217");
			link.l1 = StringFromKey("Common_poorman_218", npchar.name);
			link.l1.go = "exit";
			AddQuestRecord("ISS_PoorsMurder", "13");
			AddQuestUserData("ISS_PoorsMurder", "sName", GetFullName(npchar));
			LocatorReloadEnterDisable("Villemstad_Graveyard", "reload4", true);
			LocatorReloadEnterDisable("Villemstad_Graveyard", "reload5", true);
			LocatorReloadEnterDisable("Villemstad_Graveyard", "reload6", true);
			sld = characterFromId("Villemstad_Cemeteryman");
			sld.name = FindPersonalName("Villemstad_Cemeteryman_name");
			sld.lastname = FindPersonalName("Villemstad_Cemeteryman_lastname");
			pchar.questTemp.LSC = "goToCemeteryLSC";

			AddLandQuestMark_Main(sld, "ISS_PoorsMurder");
			LAi_SetOwnerType(sld); //перестраховка
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
		break;
		case "GoLSC_20":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReloadEnableLSC");

			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
		break;

		//обошёл все кладбища, не нашел мёртвых с косами и тишину
		case "SurveyCompleteLSC_1":
			dialog.text = "...";
			link.l1 = StringFromKey("Common_poorman_219");
			link.l1.go = "SurveyCompleteLSC_2";
		break;
		case "SurveyCompleteLSC_2":
			dialog.text = "...";
			link.l1 = StringFromKey("Common_poorman_220");
			link.l1.go = "SurveyCompleteLSC_3";
		break;
		case "SurveyCompleteLSC_3":
			dialog.text = StringFromKey("Common_poorman_221");
			link.l1 = StringFromKey("Common_poorman_222");
			link.l1.go = "SurveyCompleteLSC_4";
		break;
		case "SurveyCompleteLSC_4":
			dialog.text = StringFromKey("Common_poorman_223");
			link.l1 = StringFromKey("Common_poorman_224", pchar);
			if (CheckAttribute(npchar, "knowWhoYouAre")) link.l1.go = "SurveyCompleteLSC_6";
			else link.l1.go = "SurveyCompleteLSC_5";
		break;
		case "SurveyCompleteLSC_5":
			dialog.text = StringFromKey("Common_poorman_225", pchar.name);
			link.l1 = StringFromKey("Common_poorman_226");
			link.l1.go = "exit";
			AddQuestRecord("ISS_PoorsMurder", "23");
			pchar.questTemp.LSC = "LogToDiplomatDecryptLSC";
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			AddLandQuestMarkToFantoms_Main("diplomat", "ISS_PoorsMurder", "");
		break;
		case "SurveyCompleteLSC_6":
			dialog.text = StringFromKey("Common_poorman_227");
			link.l1 = StringFromKey("Common_poorman_228");
			link.l1.go = "SurveyCompleteLSC_7";
			PlaySound("Took_item");
			RemoveItems(pchar, "LogbookLSC", 1);
		break;
		case "SurveyCompleteLSC_7":
			dialog.text = StringFromKey("Common_poorman_229");
			link.l1 = StringFromKey("Common_poorman_230", pchar);
			link.l1.go = "SurveyCompleteLSC_8";
		break;
		case "SurveyCompleteLSC_8":
			dialog.text = StringFromKey("Common_poorman_231");
			link.l1 = StringFromKey("Common_poorman_232");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "LogToDecryptLSC";
			pchar.questTemp.LSC.decryptorId = npchar.id;
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
		break;

		//расшифровал СЖ
		case "DecryptedLogLSC_1":
			dialog.text = StringFromKey("Common_poorman_233", pchar.name);
			link.l1 = StringFromKey("Common_poorman_234");
			link.l1.go = "exit";
			AddItemLog(pchar, "LogbookLSC", "1", StringFromKey("InfoMessages_135", GetItemName("LogbookLSC")), "Important_item");
			pchar.questTemp.LSC = "LogToDecryptLSC_Taken"; // fix чтобы повторно не было выдачи
		break;

		//прочитал расшифровку и вернулся за добавкой
		case "AnswerForLogLSC_1":
			dialog.text = StringFromKey("Common_poorman_235");
			link.l1 = "...";
			link.l1.go = "AnswerForLogLSC_2";
		break;
		case "AnswerForLogLSC_2":
			dialog.text = StringFromKey("Common_poorman_236");
			link.l1 = StringFromKey("Common_poorman_237", pchar);
			link.l1.go = "AnswerForLogLSC_3";
		break;
		case "AnswerForLogLSC_3":
			dialog.text = StringFromKey("Common_poorman_238", pchar.name);
			link.l1 = StringFromKey("Common_poorman_239");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "BackToCemeteryLSC";
			AddQuestRecord("ISS_PoorsMurder", "25");
			AddQuestUserData("ISS_PoorsMurder", "sName", GetFullName(npchar));
			AddLandQuestMark_Main(characterFromId("Villemstad_Cemeteryman"), "ISS_PoorsMurder");
			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
		break;
	}
}

string GetPoorHeadManId(ref NPChar)
{
	ref ch;
	int n = FindLocation("LostShipsCity_town");
	string storeArray[30];
	if (n > 0)
		locations[n].private9.items.jewelry1 = 30;
	int howStore = 0;
	for (n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(ch, Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Poorman.c" && NPChar.id != ch.id && !CheckAttribute(ch, "quest.talk") && or(sti(pchar.nation) == PIRATE, GetNationRelation2MainCharacter(sti(ch.nation)) != RELATION_ENEMY))
		{
			storeArray[howStore] = ch.id;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	else return storeArray[rand(howStore - 1)];
}

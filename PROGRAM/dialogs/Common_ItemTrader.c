void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\ItemTrader\" + NPChar.City + "_ItemTrader.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	// ============================================================================
	// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
	if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
	{
		npchar.angry.ok = 1;
		if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
		{
			NextDiag.TempNode = NextDiag.CurrentNode;
			Dialog.CurrentNode = "AngryExitAgain";
			npchar.angry.first = 1;
		}
		else
		{
			if (npchar.angry.name == "AscoldMerchant") Dialog.CurrentNode = "AngryQuest_AscoldMerchant";
		}
	}
	// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
	// ============================================================================
	switch (Dialog.CurrentNode)
	{
		// -----------------------------------Диалог первый - первая встреча
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
						StringFromKey("Common_ItemTrader_4", LinkRandPhrase(
								StringFromKey("Common_ItemTrader_1", pchar),
								StringFromKey("Common_ItemTrader_2", pchar),
								StringFromKey("Common_ItemTrader_3", pchar))),
						StringFromKey("Common_ItemTrader_8", LinkRandPhrase(
								StringFromKey("Common_ItemTrader_5", npchar),
								StringFromKey("Common_ItemTrader_6", npchar),
								StringFromKey("Common_ItemTrader_7", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_ItemTrader_11", RandPhraseSimple(
								StringFromKey("Common_ItemTrader_9"),
								StringFromKey("Common_ItemTrader_10", npchar))),
						StringFromKey("Common_ItemTrader_14", RandPhraseSimple(
								StringFromKey("Common_ItemTrader_12"),
								StringFromKey("Common_ItemTrader_13"))));
				link.l1.go = "exit";
				break;
			}

			//зачарованный город -->
			if (pchar.questTemp.MC == "toCaracas" && npchar.city == "Caracas")
			{
				dialog.text = StringFromKey("Common_ItemTrader_18", LinkRandPhrase(
							StringFromKey("Common_ItemTrader_15"),
							StringFromKey("Common_ItemTrader_16"),
							StringFromKey("Common_ItemTrader_17")));
				link.l1 = StringFromKey("Common_ItemTrader_19");
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.MC == "toCaracasPadre" || pchar.questTemp.MC == "toCaracasTavern")
			{
				dialog.text = StringFromKey("Common_ItemTrader_20");
				link.l1 = StringFromKey("Common_ItemTrader_21");
				link.l1.go = "exit";
				break;
			}
			//<-- зачарованный город 

			dialog.text = StringFromKey("Common_ItemTrader_22", npchar);
			//--> Эммануэль Пардаль
			if (CheckAttribute(pchar, "questTemp.EPL_Prologue"))
			{
   				dialog.text = NPCharSexPhrase(npchar, StringFromKey("Common_ItemTrader_100_m"), StringFromKey("Common_ItemTrader_100_f"));
			}
			//<-- Эммануэль Пардаль
			if (GetGlobalTutor())
			{
				goto Common_ItemTrader_skipToExit_Common;
			}
			link.l1 = StringFromKey("Common_ItemTrader_23");
			link.l1.go = "Trade_exit";

			link.l2 = StringFromKey("Common_ItemTrader_24");
			link.l2.go = "quests";
			//--> eddy. Аскольд, перехват на рендомного перца
			if (pchar.questTemp.Ascold == "Seek_powder" && !CheckAttribute(npchar, "quest.answer_2"))
			{
				link.l4 = StringFromKey("Common_ItemTrader_28", LinkRandPhrase(
							StringFromKey("Common_ItemTrader_25"),
							StringFromKey("Common_ItemTrader_26"),
							StringFromKey("Common_ItemTrader_27")));
				link.l4.go = "AscoldMerchant";
			}
			//<-- eddy. Аскольд, перехват на рендомного перца
			Common_ItemTrader_skipToExit_Common:
			link.l3 = StringFromKey("Common_ItemTrader_29");
			link.l3.go = "exit";

			NextDiag.TempNode = "First time";
		break;

		case "Trade_exit":
			if (CheckNPCQuestDate(npchar, "Item_date"))
			{
				SetNPCQuestDate(npchar, "Item_date");
				GiveItemToTrader(npchar);
			}
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsTrade(npchar);
		break;
		//=================== ноды квеста мэра. поиск шпиона на улице, опрос свидетеля ==================
		case "SeekSpy_Checking":
			dialog.text = StringFromKey("Common_ItemTrader_30", &characters[sti(pchar.genquest.seekspy.baseidx)]);
			link.l1 = StringFromKey("Common_ItemTrader_33", RandPhraseSimple(
						StringFromKey("Common_ItemTrader_31", pchar),
						StringFromKey("Common_ItemTrader_32")));
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
			NextDiag.CurrentNode = "First Time";
			DialogExit();
		break;
		//Квест Аскольда. Базары с уличными торговцами
		case "AscoldMerchant":
			if (npchar.city == pchar.questTemp.Ascold.MerchantColony && npchar.location.locator == "merchant1")
			{
				dialog.text = StringFromKey("Common_ItemTrader_34", pchar);
				link.l1 = StringFromKey("Common_ItemTrader_35");
				link.l1.go = "AscoldMerchant_5";
			}
			else
			{
				//BlackThorn: более внятный поиск порошка.
				if (!CheckAttribute(npchar, "quest.answer_1") && rand(2) == 0)
				{
					npchar.quest.answer_1 = "true";
					npchar.quest.answer_2 = "true";
					if (NationNameGenitive(sti(npchar.nation)) != NationNameGenitive(sti(pchar.questTemp.Ascold.dialogNation)))
					{
						dialog.text = StringFromKey("Common_ItemTrader_36", NationNameGenitive(sti(pchar.questTemp.Ascold.dialogNation)));
						link.l2 = StringFromKey("Common_ItemTrader_37");
						link.l2.go = "exit";
						AddLandQuestmarkToFantoms_Main("ItemTrader", "Ascold", "Ascold_SeekPowder_RightCity_ItemTrader_QuestMarkCondition");
					}
					else if (XI_ConvertString("Colony" + pchar.questTemp.Ascold.MerchantColony) != XI_ConvertString("Colony" + npchar.city))
					{
						dialog.text = StringFromKey("Common_ItemTrader_38", XI_ConvertString("Colony" + pchar.questTemp.Ascold.MerchantColony));
						AddLandQuestmarkToFantoms_Main("ItemTrader", "Ascold", "Ascold_SeekPowder_RightCity_ItemTrader_QuestMarkCondition");
					}
					else
					{
						dialog.text = StringFromKey("Common_ItemTrader_39");
						AddLandQuestmarkToFantoms_Main("ItemTrader", "Ascold", "Ascold_SeekPowder_RightItemTrader_QuestMarkCondition");
					}
					link.l2 = StringFromKey("Common_ItemTrader_40");
					link.l2.go = "exit";
				}
				else
				{
					npchar.quest.answer_1 = "true";
					dialog.text = NPCStringReactionRepeat(
								StringFromKey("Common_ItemTrader_44", LinkRandPhrase(
										StringFromKey("Common_ItemTrader_41"),
										StringFromKey("Common_ItemTrader_42"),
										StringFromKey("Common_ItemTrader_43"))),
								StringFromKey("Common_ItemTrader_48", LinkRandPhrase(
										StringFromKey("Common_ItemTrader_45"),
										StringFromKey("Common_ItemTrader_46"),
										StringFromKey("Common_ItemTrader_47"))),
								StringFromKey("Common_ItemTrader_52", LinkRandPhrase(
										StringFromKey("Common_ItemTrader_49", npchar),
										StringFromKey("Common_ItemTrader_50", npchar),
										StringFromKey("Common_ItemTrader_51"))),
								StringFromKey("Common_ItemTrader_56", LinkRandPhrase(
										StringFromKey("Common_ItemTrader_53"),
										StringFromKey("Common_ItemTrader_54"),
										StringFromKey("Common_ItemTrader_55"))), "quest", 10, npchar, Dialog.CurrentNode);
					link.l1 = HeroStringReactionRepeat(
								StringFromKey("Common_ItemTrader_57"),
								StringFromKey("Common_ItemTrader_58"),
								StringFromKey("Common_ItemTrader_59"),
								StringFromKey("Common_ItemTrader_60"), npchar, Dialog.CurrentNode);
					link.l1.go = DialogGoNodeRepeat("AscoldMerchant_2", "AscoldMerchant_3", "AscoldMerchant_4", "", npchar, Dialog.CurrentNode);
				}
			}
		break;

		case "AscoldMerchant_2":
			dialog.text = StringFromKey("Common_ItemTrader_64", LinkRandPhrase(
						StringFromKey("Common_ItemTrader_61", pchar),
						StringFromKey("Common_ItemTrader_62", npchar),
						StringFromKey("Common_ItemTrader_63", npchar)));
			Link.l1 = StringFromKey("Common_ItemTrader_65");
			Link.l1.go = "exit";
		break;

		case "AscoldMerchant_3":
			dialog.text = StringFromKey("Common_ItemTrader_69", LinkRandPhrase(
						StringFromKey("Common_ItemTrader_66", npchar),
						StringFromKey("Common_ItemTrader_67"),
						StringFromKey("Common_ItemTrader_68", npchar)));
			Link.l1 = StringFromKey("Common_ItemTrader_70");
			Link.l1.go = "exit";
		break;

		case "AscoldMerchant_4":
			dialog.text = StringFromKey("Common_ItemTrader_74", LinkRandPhrase(
						StringFromKey("Common_ItemTrader_71", npchar),
						StringFromKey("Common_ItemTrader_72", npchar),
						StringFromKey("Common_ItemTrader_73", npchar)));
			Link.l1 = StringFromKey("Common_ItemTrader_75", npchar);
			Link.l1.go = "exit";
		break;

		case "AscoldMerchant_5":
			dialog.text = StringFromKey("Common_ItemTrader_76");
			link.l1 = StringFromKey("Common_ItemTrader_77");
			link.l1.go = "AscoldMerchant_6";
		break;

		case "AscoldMerchant_6":
			dialog.text = StringFromKey("Common_ItemTrader_78");
			link.l1 = StringFromKey("Common_ItemTrader_79");
			link.l1.go = "AscoldMerchant_7";
		break;

		case "AscoldMerchant_7":
			dialog.text = StringFromKey("Common_ItemTrader_80");
			link.l1 = StringFromKey("Common_ItemTrader_81");
			link.l1.go = "AscoldMerchant_8";
		break;

		case "AscoldMerchant_8":
			dialog.text = StringFromKey("Common_ItemTrader_82");
			if (sti(pchar.money) >= 1000)
			{
				Link.l1 = StringFromKey("Common_ItemTrader_83");
				Link.l1.go = "exit";
				pchar.questTemp.Ascold = "PowderWasSeek";
				AddMoneyToCharacter(pchar, -1000);
				GiveItem2Character(Pchar, "Powder_mummie");
				RemoveLandQuestmarkToFantoms_Main("ItemTrader", "Ascold");
				RemoveLandQuestmark_Main(CharacterFromID(pchar.questTemp.Ascold.TraderId), "Ascold");
				AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Ascold.TraderId), "Ascold");
			}
			else
			{
				link.l1 = StringFromKey("Common_ItemTrader_84");
				link.l1.go = "exit";
			}
		break;

		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryQuest_AscoldMerchant":
			Dialog.text = StringFromKey("Common_ItemTrader_87", RandPhraseSimple(
						StringFromKey("Common_ItemTrader_85"),
						StringFromKey("Common_ItemTrader_86")));
			Link.l1 = StringFromKey("Common_ItemTrader_90", RandPhraseSimple(
						StringFromKey("Common_ItemTrader_88"),
						StringFromKey("Common_ItemTrader_89")));
			Link.l1.go = "AngryExitAgain";
			//===>> квест Аскольда, розыск порошка мумии.
			if (pchar.questTemp.Ascold == "Seek_powder" && npchar.city == pchar.questTemp.Ascold.MerchantColony && npchar.location.locator == "merchant1")
			{
				Dialog.text = StringFromKey("Common_ItemTrader_91", pchar);
				Link.l1 = StringFromKey("Common_ItemTrader_92");
				Link.l1.go = "AngStep_1";
			}
			if (CheckAttribute(npchar, "angry.terms")) //мирилка по квесту Аскольда через 10 дней.
			{
				if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms) && pchar.questTemp.Ascold != "Seek_powder")
				{
					Dialog.text = StringFromKey("Common_ItemTrader_93", npchar);
					Link.l1 = StringFromKey("Common_ItemTrader_96", RandPhraseSimple(
								StringFromKey("Common_ItemTrader_94"),
								StringFromKey("Common_ItemTrader_95")));
					Link.l1.go = "First time";
					CharacterDelAngry(npchar);
				}
			}
		break;
		////////////////////////////////////////////////////////////////////////////////////////////////
		case "AngryExitAgain":
			DialogExit();
			DeleteAttribute(npchar, "angry.ok");
		break;

		case "AngStep_1":
			Dialog.text = StringFromKey("Common_ItemTrader_97", pchar);
			if (sti(pchar.money) >= 1000)
			{
				Link.l1 = StringFromKey("Common_ItemTrader_98");
				Link.l1.go = "AngryExitAgain";
				pchar.questTemp.Ascold = "PowderWasSeek";
				CharacterDelAngry(npchar);
				AddMoneyToCharacter(pchar, -1000);
				GiveItem2Character(Pchar, "Powder_mummie");
				RemoveLandQuestmarkToFantoms_Main("ItemTrader", "Ascold");
				RemoveLandQuestmark_Main(CharacterFromID(pchar.questTemp.Ascold.TraderId), "Ascold");
				AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Ascold.TraderId), "Ascold");
			}
			else
			{
				Link.l1 = StringFromKey("Common_ItemTrader_99");
				Link.l1.go = "AngryExitAgain";
			}
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
	}
}

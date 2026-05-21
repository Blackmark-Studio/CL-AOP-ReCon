// Аскольд
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Tichingitu_11":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = StringFromKey("Ascold_1");
			link.l1 = StringFromKey("Ascold_2");
			npchar.quest.Tichingitu = "paid";
			link.l1.go = "Tichingitu_12";
		break;

		if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "ascold")
		{
			dialog.text = StringFromKey("Ascold_3", pchar);
			link.l1 = StringFromKey("Ascold_4", pchar);
			link.l1.go = "Tichingitu_7";
			if (!CheckAttribute(npchar, "quest.Tichingitu"))
			{
				npchar.quest.Tichingitu = true;
				break;
			}
		}
		if (CheckAttribute(pchar, "questTemp.Tichingitu") && pchar.questTemp.Tichingitu == "money")
		{
			dialog.text = StringFromKey("Ascold_5", pchar);
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = StringFromKey("Ascold_6");
				link.l1.go = "Tichingitu_11";
			}
			if (CheckAttribute(npchar, "quest.Tichingitu") && npchar.quest.Tichingitu != "paid")
			{
				link.l2 = StringFromKey("Ascold_7", pchar);
				link.l2.go = "exit";
				break;
			}
		}
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Ascold_8");
				link.l1 = StringFromKey("Ascold_9", GetFullName(pchar));
				link.l1.go = "Step_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = StringFromKey("Ascold_10");
				link.l1 = StringFromKey("Ascold_11", pchar);
				link.l1.go = "exit";
				link.l2 = StringFromKey("Ascold_12");
				link.l2.go = "Step_3";
				NextDiag.TempNode = "First time";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Step_1":
			dialog.text = StringFromKey("Ascold_13");
			link.l1 = StringFromKey("Ascold_14");
			link.l1.go = "Step_2";
		break;

		case "Step_2":
			dialog.text = StringFromKey("Ascold_15");
			link.l1 = StringFromKey("Ascold_16");
			link.l1.go = "First time";
		break;

		case "Step_3":
			if (npchar.quest.meeting == "1")
			{
				dialog.text = StringFromKey("Ascold_17", pchar);
				link.l1 = "...";
				npchar.quest.meeting = "2";
			}
			else
			{
				dialog.text = StringFromKey("Ascold_20", RandPhraseSimple(
							StringFromKey("Ascold_18"),
							StringFromKey("Ascold_19", pchar)));
				link.l1 = StringFromKey("Ascold_23", RandPhraseSimple(
							StringFromKey("Ascold_21"),
							StringFromKey("Ascold_22")));
			}
			link.l1.go = "Step_4";
		break;

		case "Step_4":
			DoReloadCharacterToLocation("BasTer_town", "reload", "houseSp1");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "HaveRecomendation":
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Ascold_24");
				link.l1 = StringFromKey("Ascold_25", GetFullName(pchar), GetFullName(sld), XI_ConvertString("Colony" + sld.City + "Pre"));
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = StringFromKey("Ascold_26", pchar);
				link.l1 = StringFromKey("Ascold_27", GetFullName(sld), XI_ConvertString("Colony" + sld.City + "Pre"));
			}
			link.l1.go = "Step_5";
		break;

		case "Step_5":
			sld = characterFromId(pchar.questTemp.Ascold.TraderId);
			dialog.text = StringFromKey("Ascold_28");
			link.l1 = StringFromKey("Ascold_29", sld.lastname);
			link.l1.go = "Step_6";
		break;

		case "Step_6":
			dialog.text = StringFromKey("Ascold_30");
			link.l1 = StringFromKey("Ascold_31");
			if (CheckCharacterItem(pchar, "Powder_mummie"))
			{
				link.l1.go = "Step_7";
				TakeItemFromCharacter(pchar, "Powder_mummie");
				AddMoneyToCharacter(pchar, 30000);
			}
			else
			{
				link.l1.go = "No_Powder";
			}
		break;

		case "No_Powder":
			dialog.text = StringFromKey("Ascold_32", pchar);
			link.l1 = StringFromKey("Ascold_33", pchar);
			link.l1.go = "Step_4";
			NextDiag.TempNode = "First time";
			CloseQuestHeader("Ascold");
			pchar.questTemp.Ascold = "BreakeQuest";
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;

		case "Step_7":
			dialog.text = StringFromKey("Ascold_34");
			link.l1 = StringFromKey("Ascold_35", pchar);
			link.l1.go = "Step_8";
		break;

		case "Step_8":
			dialog.text = StringFromKey("Ascold_36");
			link.l1 = StringFromKey("Ascold_37");
			link.l1.go = "Step_9";
		break;

		case "Step_9":
			dialog.text = StringFromKey("Ascold_38");
			link.l1 = StringFromKey("Ascold_39", pchar);
			link.l1.go = "Step_10";
			link.l2 = StringFromKey("Ascold_40");
			link.l2.go = "No_Work";
		break;

		case "No_Work":
			dialog.text = StringFromKey("Ascold_41", pchar);
			link.l1 = StringFromKey("Ascold_42");
			link.l1.go = "Step_4";
			NextDiag.TempNode = "First time";
			CloseQuestHeader("Ascold");
			pchar.questTemp.Ascold = "BreakeQuest";
			group_DeleteGroup("Ascold_Spa_Attack");
			DeleteAttribute(PChar, "questTemp.Ascold.Ship");
			RemoveLandQuestmark_Main(npchar, "Ascold");
			RemoveMapQuestMark("BasTer_town", "Ascold");
			RemoveLandQuestmark_Main(CharacterFromID("Havana_tavernkeeper"), "Ascold");
			iTemp = GetCharacterIndex("FernandoGonsales");
			if (iTemp >= 0)
			{
				RemoveLandQuestmark_Main(&Characters[iTemp], "Ascold");
			}
		break;

		case "Step_10":
			dialog.text = StringFromKey("Ascold_43");

			if (or(HasPlaytestRewardNative(), BIsSubscribedApp(2230980)) && !CheckAttribute(pchar, "questTemp.Tichingitu") && !CheckAttribute(npchar, "quest.Tichingitu"))
			{
				link.l1 = StringFromKey("Ascold_270");
				link.l1.go = "Tichingitu_0";
			}
			link.l2 = StringFromKey("Ascold_44", pchar);
			link.l2.go = "exit";
			pchar.questTemp.Ascold = "SeekThreeObject";
			NextDiag.TempNode = "ResultOfSeek";
			AddQuestRecord("Ascold", "3");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("ся", "ась"));
			AddLandQuestmark_Main_WithCondition(npchar, "Ascold", "Ascold_SeekThreeItems_QuestMarkCondition");
			AddLandQuestmark_Main(CharacterFromID("Oliver_Green"), "Ascold");
		break;

		case "Tichingitu_0":
			dialog.text = StringFromKey("Ascold_271");
			link.l1 = StringFromKey("Ascold_272");
			link.l1.go = "Tichingitu_1";
		break;

		case "Tichingitu_1":
			dialog.text = StringFromKey("Ascold_45");
			link.l1 = StringFromKey("Ascold_46");
			link.l1.go = "Tichingitu_2";
		break;

		case "Tichingitu_2":
			dialog.text = StringFromKey("Ascold_47");
			link.l1 = StringFromKey("Ascold_48");
			link.l1.go = "Tichingitu_3";
		break;

		case "Tichingitu_3":
			dialog.text = StringFromKey("Ascold_49");
			link.l1 = StringFromKey("Ascold_50");
			link.l1.go = "Tichingitu_4";
		break;

		case "Tichingitu_4":
			dialog.text = StringFromKey("Ascold_51");
			link.l1 = StringFromKey("Ascold_52");
			link.l1.go = "Tichingitu_5";
		break;

		case "Tichingitu_5":
			dialog.text = StringFromKey("Ascold_53");
			link.l1 = StringFromKey("Ascold_54");
			link.l1.go = "Tichingitu_6";
		break;

		case "Tichingitu_6":
			dialog.text = StringFromKey("Ascold_55");
			link.l1 = StringFromKey("Ascold_56");
			link.l1.go = "exit";
			pchar.questTemp.Tichingitu = "true";
			AddDialogExitQuestFunction("SetTichingituJail");
			SetFunctionTimerCondition("FreeTichingituOver", 0, 0, 10, false);
		break;

		case "Tichingitu_7":
			dialog.text = StringFromKey("Ascold_57");
			link.l1 = StringFromKey("Ascold_58", pchar);
			link.l1.go = "Tichingitu_8";
		break;

		case "Tichingitu_8":
			dialog.text = StringFromKey("Ascold_59");
			link.l1 = StringFromKey("Ascold_60");
			link.l1.go = "Tichingitu_9";
		break;

		case "Tichingitu_9":
			dialog.text = StringFromKey("Ascold_61");
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = StringFromKey("Ascold_62");
				link.l1.go = "Tichingitu_11";
			}
			link.l2 = StringFromKey("Ascold_63");
			link.l2.go = "Tichingitu_10";
		break;

		case "Tichingitu_10":
			dialog.text = StringFromKey("Ascold_64");
			link.l1 = StringFromKey("Ascold_65");
			link.l1.go = "exit";
			pchar.questTemp.Tichingitu = "money";
		break;

		case "Tichingitu_12":
			AddItemLog(pchar, "letter_A", "1", StringFromKey("InfoMessages_179"), "Important_item");
			dialog.text = StringFromKey("Ascold_66");
			link.l1 = StringFromKey("Ascold_67");
			link.l1.go = "exit_vodka";
			pchar.questTemp.Tichingitu = "pay";
		break;

		case "exit_vodka":
			LAi_MethodDelay("FrameAscoldVodka", 0.1);
			DialogExit();
		break;

		case "ResultOfSeek":
			dialog.text = StringFromKey("Ascold_68");
			link.l1 = StringFromKey("Ascold_69");
			link.l1.go = "exit";
			NextDiag.TempNode = "ResultOfSeek";
			if (CheckCharacterItem(pchar, "indian19") && CheckCharacterItem(pchar, "indian20") && CheckCharacterItem(pchar, "indian21"))
			{
				link.l2 = StringFromKey("Ascold_70", pchar);
				link.l2.go = "Step_11";
			}
		break;

		case "Step_11":
			dialog.text = StringFromKey("Ascold_71", pchar);
			link.l1 = StringFromKey("Ascold_72");
			if (pchar.questTemp.Ascold == "SoughtThreeObject")
			{
				link.l1 = StringFromKey("Ascold_73", pchar);
			}
			link.l1.go = "Step_12";
			link.l2 = StringFromKey("Ascold_74");
			link.l2.go = "WantMoreMoney";
		break;

		case "WantMoreMoney":
			dialog.text = StringFromKey("Ascold_75", pchar);
			link.l1 = StringFromKey("Ascold_76");
			link.l1.go = "Step_4";
			NextDiag.TempNode = "First time";
			CloseQuestHeader("Ascold");
			pchar.questTemp.Ascold = "BreakeQuest";
			RemoveLandQuestmark_Main(npchar, "Ascold");
			RemoveLandQuestmark_Main(CharacterFromID("Oliver_Green"), "Ascold");
		break;

		case "Step_12":
			dialog.text = StringFromKey("Ascold_77");
			link.l1 = StringFromKey("Ascold_78");
			link.l1.go = "Step_13";
		break;

		case "Step_13":
			dialog.text = StringFromKey("Ascold_79");
			link.l1 = StringFromKey("Ascold_80");
			link.l1.go = "exit";
			TakeItemFromCharacter(pchar, "indian19");
			TakeItemFromCharacter(pchar, "indian20");
			TakeItemFromCharacter(pchar, "indian21");
			AddMoneyToCharacter(pchar, 90000);
			pchar.questTemp.Ascold = "TakenThreeObject";
			SaveCurrentQuestDateParam("questTemp.Ascold");
			NextDiag.TempNode = "WalkTwoMounth";
			AddQuestRecord("Ascold", "4");
			AddLandQuestmark_Main_WithCondition(npchar, "Ascold", "Ascold_WalkTwoMonth_QuestMarkCondition");
			AddMapQuestMark_Major("BasTer_town", "Ascold", "Ascold_WalkTwoMonth_WDMQuestMarkCondition");
			RemoveLandQuestmark_Main(CharacterFromID("Oliver_Green"), "Ascold");
		break;

		case "WalkTwoMounth":
			if (GetQuestPastDayParam("questTemp.Ascold") > 62)
			{
				dialog.text = StringFromKey("Ascold_81", GetFullName(pchar));
				link.l1 = StringFromKey("Ascold_82");
				link.l1.go = "Step_14";
			}
			else
			{
				dialog.text = StringFromKey("Ascold_83", pchar, GetFullName(pchar));
				link.l1 = StringFromKey("Ascold_84");
				link.l1.go = "exit";
				NextDiag.TempNode = "WalkTwoMounth";
			}
		break;

		case "Step_14":
			dialog.text = StringFromKey("Ascold_85");
			link.l1 = StringFromKey("Ascold_86");
			link.l1.go = "Step_15";
		break;

		case "Step_15":
			dialog.text = StringFromKey("Ascold_87");
			link.l1 = StringFromKey("Ascold_88");
			link.l1.go = "Step_16";
			link.l2 = StringFromKey("Ascold_89");
			link.l2.go = "No_Work";
		break;

		case "Step_16":
			dialog.text = StringFromKey("Ascold_90");
			link.l1 = StringFromKey("Ascold_91");
			link.l1.go = "exit";
			SaveCurrentQuestDateParam("questTemp.Ascold");
			NextDiag.TempNode = "AfterManowarsBattle";
			pchar.questTemp.Ascold = "ToHavanna";
			AddQuestRecord("Ascold", "5");
			RemoveLandQuestmark_Main(npchar, "Ascold");
			RemoveMapQuestMark("BasTer_town", "Ascold");
			AddLandQuestmark_Main(CharacterFromID("Havana_tavernkeeper"), "Ascold");
		break;

		case "AfterManowarsBattle":
			dialog.text = StringFromKey("Ascold_92", pchar);
			link.l1 = StringFromKey("Ascold_93");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Ascold_94");
			link.l2.go = "No_Work";
			if (pchar.questTemp.Ascold == "SeekInformatorHavanna")
			{
				link.l1 = StringFromKey("Ascold_95");
				link.l1.go = "Step_17";
			}
			if (pchar.questTemp.Ascold == "ReciveInformationManowar")
			{
				link.l1 = StringFromKey("Ascold_96", pchar);
				link.l1.go = "Step_20";
			}
			if (pchar.questTemp.Ascold == "ILookedThisAss" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
			{
				link.l1 = StringFromKey("Ascold_97");
				link.l1.go = "Step_24";
			}
			if (pchar.questTemp.Ascold == "ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
			{
				link.l1 = StringFromKey("Ascold_98");
				link.l1.go = "Step_25";
			}
			if (pchar.questTemp.Ascold == "2ILookedThisAss" && CheckAttribute(PChar, "questTemp.Ascold.List"))
			{
				link.l1 = StringFromKey("Ascold_99");
				link.l1.go = "Step_25";
			}
			if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && !CheckAttribute(PChar, "questTemp.Ascold.List"))
			{
				link.l1 = StringFromKey("Ascold_100", pchar);
				link.l1.go = "NoFoundList";
			}
			if (CheckCharacterItem(pchar, "AscoldInventoryList") && pchar.questTemp.Ascold == "ILookedThisAss")
			{
				link.l1 = StringFromKey("Ascold_101", pchar);
				link.l1.go = "Step_26";
			}
			if (CheckCharacterItem(pchar, "AscoldInventoryList") && pchar.questTemp.Ascold == "2ILookedThisAss")
			{
				link.l1 = StringFromKey("Ascold_102", pchar);
				link.l1.go = "Step_26";
			}
			if (CheckCharacterItem(pchar, "AscoldInventoryList") && pchar.questTemp.Ascold == "Ascold_ManowarsDead")
			{
				link.l1 = StringFromKey("Ascold_103", pchar);
				link.l1.go = "ManowarGoodWork";
			}
			if (pchar.questTemp.Ascold == "Ascold_ManowarsDead" && CheckAttribute(PChar, "questTemp.Ascold.List"))
			{
				link.l1 = StringFromKey("Ascold_104", pchar);
				link.l1.go = "ManowarGoodWork";
			}
			if (pchar.questTemp.Ascold == "Ascold_ManowarsNoDead")
			{
				link.l1 = StringFromKey("Ascold_105");
				link.l1.go = "ManowarNoGoodWork";
			}
		break;

		case "Step_17":
			dialog.text = StringFromKey("Ascold_106");
			link.l1 = StringFromKey("Ascold_107", pchar);
			link.l1.go = "Step_18";
		break;

		case "Step_18":
			dialog.text = StringFromKey("Ascold_108");
			link.l1 = StringFromKey("Ascold_109");
			link.l1.go = "Step_19";
		break;

		case "Step_19":
			dialog.text = StringFromKey("Ascold_110");
			link.l1 = StringFromKey("Ascold_111");
			link.l1.go = "exit";
			pchar.questTemp.Ascold = "2SeekInformatorHavanna";
			NextDiag.TempNode = "AfterManowarsBattle";
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;

		case "Step_20":
			dialog.text = StringFromKey("Ascold_112", pchar);
			link.l1 = StringFromKey("Ascold_113");
			link.l1.go = "Step_21";
		break;

		case "Step_21":
			dialog.text = StringFromKey("Ascold_114");
			link.l1 = StringFromKey("Ascold_115");
			link.l1.go = "Step_22";
		break;

		case "Step_22":
			dialog.text = StringFromKey("Ascold_116", pchar);
			link.l1 = StringFromKey("Ascold_117", pchar);
			link.l1.go = "Step_23";
			link.l2 = StringFromKey("Ascold_118");
			link.l2.go = "No_Work";
		break;

		case "Step_23":
			dialog.text = StringFromKey("Ascold_119");
			link.l1 = StringFromKey("Ascold_120");
			link.l1.go = "exit";
			AddQuestRecord("Ascold", "8");
			pchar.questTemp.Ascold = "IMustKillAll";
			NextDiag.TempNode = "AfterManowarsBattle";
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;

		case "Step_24":
			dialog.text = StringFromKey("Ascold_121");
			link.l1 = StringFromKey("Ascold_122");
			link.l1.go = "Step_25";
			link.l2 = StringFromKey("Ascold_123");
			link.l2.go = "No_Work";
		break;

		case "Step_25":
			dialog.text = StringFromKey("Ascold_124");
			link.l1 = StringFromKey("Ascold_125");
			link.l1.go = "exit";
			pchar.questTemp.Ascold = "2ILookedThisAss";
			NextDiag.TempNode = "AfterManowarsBattle";
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;

		case "NoFoundList":
			dialog.text = StringFromKey("Ascold_126", pchar);
			link.l1 = StringFromKey("Ascold_127");
			link.l1.go = "Step_4";
			NextDiag.TempNode = "First time";
			CloseQuestHeader("Ascold");
			pchar.questTemp.Ascold = "BreakeQuest";
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;

		case "Step_26":
			dialog.text = StringFromKey("Ascold_128", pchar);
			link.l1 = StringFromKey("Ascold_129");
			link.l1.go = "Step_27";
			link.l2 = StringFromKey("Ascold_130");
			link.l2.go = "No_Work";
			link.l3 = StringFromKey("Ascold_131", pchar);
			link.l3.go = "WantMoreMoney";
			TakeItemFromCharacter(pchar, "AscoldInventoryList");
			pchar.questTemp.Ascold.list = 1;
		break;

		case "Step_27":
			dialog.text = StringFromKey("Ascold_132");
			link.l1 = StringFromKey("Ascold_133", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Ascold", "10");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;

		case "ManowarGoodWork":
			dialog.text = StringFromKey("Ascold_134", pchar);
			link.l1 = StringFromKey("Ascold_135");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Ascold_136");
			link.l2.go = "Step_28";
			NextDiag.TempNode = "ManowarGoodWork";
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;

		case "ManowarNoGoodWork":
			dialog.text = StringFromKey("Ascold_137", pchar);
			link.l1 = StringFromKey("Ascold_138");
			link.l1.go = "Step_4";
			NextDiag.TempNode = "First time";
			CloseQuestHeader("Ascold");
			pchar.questTemp.Ascold = "BreakeQuest";
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;

		case "Step_28":
			dialog.text = StringFromKey("Ascold_139");
			link.l1 = StringFromKey("Ascold_140");
			link.l1.go = "Step_4";
			NextDiag.TempNode = "First time";
			CloseQuestHeader("Ascold");
			pchar.questTemp.Ascold = "BreakeQuest";
			pchar.quest.Ascold_FightNearTemple.over = "yes";
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;

		case "Ascold_KilledTemple":
			dialog.text = StringFromKey("Ascold_141", pchar);
			link.l1 = StringFromKey("Ascold_142");
			link.l1.go = "NoFoundList";
			if (CheckCharacterItem(pchar, "AscoldInventoryList") || CheckAttribute(PChar, "questTemp.Ascold.List"))
			{
				link.l1 = StringFromKey("Ascold_143");
				link.l1.go = "Step_29";
				TakeItemFromCharacter(pchar, "AscoldInventoryList");
				DeleteAttribute(PChar, "questTemp.Ascold.List");
			}
		break;

		case "Step_29":
			dialog.text = StringFromKey("Ascold_144");
			link.l1 = StringFromKey("Ascold_145", pchar);
			link.l1.go = "Step_30";
		break;

		case "Step_30":
			dialog.text = StringFromKey("Ascold_146");
			link.l1 = StringFromKey("Ascold_147");
			link.l1.go = "Step_31";
		break;

		case "Step_31":
			dialog.text = StringFromKey("Ascold_148", pchar);
			link.l1 = StringFromKey("Ascold_149");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mummie_begin";
			SaveCurrentQuestDateParam("questTemp.Ascold");
			AddQuestRecord("Ascold", "12");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Ascold", "sSex1", GetSexPhrase("ся", "ась"));
			AddLandQuestmark_Main_WithCondition(npchar, "Ascold", "Ascold_MummieBegin_QuestMarkCondition");
			AddMapQuestMark_Major("BasTer_town", "Ascold", "Ascold_MummieBegin_WDMQuestMarkCondition");
		break;

		case "Mummie_begin":
			dialog.text = StringFromKey("Ascold_150", GetFullName(pchar));
			link.l1 = StringFromKey("Ascold_151");
			link.l1.go = "exit";
			NextDiag.TempNode = "Mummie_begin";
			if (GetQuestPastDayParam("questTemp.Ascold") > 40)
			{
				dialog.text = StringFromKey("Ascold_152", pchar, GetFullName(pchar));
				link.l1 = StringFromKey("Ascold_153");
				link.l1.go = "Step_31A";
			}
		break;

		case "Step_31A":
			dialog.text = StringFromKey("Ascold_154");
			link.l1 = StringFromKey("Ascold_155");
			link.l1.go = "Step_32";
		break;

		case "Step_32":
			dialog.text = StringFromKey("Ascold_156");
			link.l1 = StringFromKey("Ascold_157");
			link.l1.go = "Step_33";
		break;

		case "Step_33":
			dialog.text = StringFromKey("Ascold_158");
			link.l1 = StringFromKey("Ascold_159");
			link.l1.go = "Step_34";
			link.l2 = StringFromKey("Ascold_160");
			link.l2.go = "No_Work";
		break;

		case "Step_34":
			dialog.text = StringFromKey("Ascold_161");
			link.l1 = StringFromKey("Ascold_162");
			link.l1.go = "Step_35";
			link.l2 = StringFromKey("Ascold_163", pchar);
			link.l2.go = "No_Work";
		break;

		case "Step_35":
			dialog.text = StringFromKey("Ascold_164");
			link.l1 = StringFromKey("Ascold_165", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "Seek_Grave";
			AddQuestRecord("Ascold", "13");
			CloseQuestHeader("Ascold");
			pchar.questTemp.Ascold = "Ascold_SeekGrave";
			RemoveLandQuestmark_Main(npchar, "Ascold");
			RemoveMapQuestMark("BasTer_town", "Ascold");
		break;

		case "Seek_Grave":
			dialog.text = StringFromKey("Ascold_166", pchar);
			link.l1 = StringFromKey("Ascold_167");
			link.l1.go = "exit";
			NextDiag.TempNode = "Seek_Grave";
			if (pchar.questTemp.Ascold == "Ascold_SeekGrave")
			{
				dialog.text = StringFromKey("Ascold_168", pchar);
				link.l1 = StringFromKey("Ascold_169", pchar);
				link.l1.go = "Step_36";
			}
			if (pchar.questTemp.Ascold == "Ascold_CantSeekGrave")
			{
				dialog.text = StringFromKey("Ascold_170", pchar);
				link.l1 = StringFromKey("Ascold_171", pchar);
				link.l1.go = "Step_37";
			}
			if (pchar.questTemp.Ascold == "Ascold_NotEnterFoundGrave")
			{
				dialog.text = StringFromKey("Ascold_172");
				link.l1 = StringFromKey("Ascold_173", pchar);
				link.l1.go = "Step_38";
			}
			if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && !CheckCharacterItem(pchar, "Rock_letter"))
			{
				dialog.text = StringFromKey("Ascold_174", pchar);
				link.l1 = StringFromKey("Ascold_175");
				link.l1.go = "exit";
			}
			if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" && CheckCharacterItem(pchar, "Rock_letter"))
			{
				dialog.text = StringFromKey("Ascold_176");
				link.l1 = StringFromKey("Ascold_177", pchar);
				link.l1.go = "Step_45";
			}
			if (pchar.questTemp.Ascold == "Ascold_EnterGrave")
			{
				dialog.text = StringFromKey("Ascold_178");
				link.l1 = StringFromKey("Ascold_179");
				link.l1.go = "exit";
			}
		break;

		case "Step_36":
			dialog.text = StringFromKey("Ascold_180");
			link.l1 = StringFromKey("Ascold_181");
			link.l1.go = "exit";
			pchar.questTemp.Ascold = "Ascold_CantSeekGrave";
		break;

		case "Step_37":
			dialog.text = StringFromKey("Ascold_182");
			link.l1 = StringFromKey("Ascold_183");
			link.l1.go = "exit";
		break;

		case "Step_38":
			dialog.text = StringFromKey("Ascold_184", pchar);
			link.l1 = StringFromKey("Ascold_185");
			link.l1.go = "Step_40";
		break;

		case "Step_40":
			dialog.text = StringFromKey("Ascold_186");
			link.l1 = StringFromKey("Ascold_187");
			link.l1.go = "Step_41";
		break;

		case "Step_41":
			dialog.text = StringFromKey("Ascold_188");
			link.l1 = StringFromKey("Ascold_189");
			link.l1.go = "Step_42";
		break;

		case "Step_42":
			dialog.text = StringFromKey("Ascold_190");
			link.l1 = StringFromKey("Ascold_191");
			link.l1.go = "Step_43";
		break;

		case "Step_43":
			dialog.text = StringFromKey("Ascold_192");
			link.l1 = StringFromKey("Ascold_193");
			link.l1.go = "Step_44";
			link.l2 = StringFromKey("Ascold_194");
			link.l2.go = "No_Work";
		break;

		case "Step_44":
			dialog.text = StringFromKey("Ascold_195");
			link.l1 = StringFromKey("Ascold_196");
			link.l1.go = "exit";
			pchar.questTemp.Ascold = "Ascold_SeekRockLetter";
			// ==> Делаем скрижали видимыми, теперь их можно найти.
			sld = ItemsFromID("Rock_letter");
			sld.shown = 1;
			// квест-указатель
			QuestPointerToLoc(sld.startLocation, "item", sld.startLocator);
			AddLandQuestmark_Main_WithCondition(npchar, "Ascold", "Ascold_SeekRockLetter_QuestMarkCondition");
		break;

		case "Step_45":
			dialog.text = StringFromKey("Ascold_197");
			link.l1 = StringFromKey("Ascold_198");
			link.l1.go = "exit";
			pchar.questTemp.Ascold = "Ascold_EnterGrave";
			SetCurrentQuestMark(npchar);
		break;

		case "Found_Grave":
			if (pchar.questTemp.Ascold == "Ascold_FoundMummy")
			{
				dialog.text = StringFromKey("Ascold_199", pchar, GetFullName(pchar));
				link.l1 = StringFromKey("Ascold_200", pchar);
				link.l1.go = "Step_46";
			}
		break;

		case "Step_46":
			dialog.text = StringFromKey("Ascold_201", pchar);
			link.l1 = StringFromKey("Ascold_202", pchar);
			link.l1.go = "Step_47";
		break;

		case "Step_47":
			dialog.text = StringFromKey("Ascold_203");
			link.l1 = StringFromKey("Ascold_204");
			link.l1.go = "Step_48";
		break;

		case "Step_48":
			dialog.text = StringFromKey("Ascold_205");
			link.l1 = StringFromKey("Ascold_206", pchar);
			link.l1.go = "Step_49";
		break;

		case "Step_49":
			dialog.text = StringFromKey("Ascold_207");
			link.l1 = StringFromKey("Ascold_208");
			link.l1.go = "Step_50";
		break;

		case "Step_50":
			dialog.text = StringFromKey("Ascold_209");
			link.l1 = StringFromKey("Ascold_210", pchar);
			link.l1.go = "Step_51";
		break;

		case "Step_51":
			dialog.text = StringFromKey("Ascold_211");
			link.l1 = StringFromKey("Ascold_212");
			link.l1.go = "exit";
			pchar.questTemp.Ascold = "Ascold_WateringMummy";
			GiveItem2Character(Pchar, "Ascold_rabble");
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;

		case "AfterAttackMummy":
			dialog.text = StringFromKey("Ascold_213");
			link.l1 = StringFromKey("Ascold_214");
			link.l1.go = "Step_52";
			if (pchar.questTemp.Ascold == "Ascold_SaveWorld")
			{
				dialog.text = StringFromKey("Ascold_215", pchar);
				link.l1 = StringFromKey("Ascold_216");
				link.l1.go = "exit";
				NextDiag.TempNode = "AfterAttackMummy";
			}
			if (GetCharacterIndex("LeifEricson") == -1)
			{
				dialog.text = StringFromKey("Ascold_217");
				link.l1 = StringFromKey("Ascold_218");
				link.l1.go = "Step_60";

				// перебиваем иниты пещеры - возвращаем сферы обратно и закрываем гробницу   - ugeen fix
				locations[FindLocation("Guadeloupe_CaveEntrance")].reload.l1.name = "reload1_back";
				locations[FindLocation("Guadeloupe_CaveEntrance")].reload.l1.emerge = "reload1";

				locations[FindLocation("Guadeloupe_Cave")].reload.l1.name = "reload1_back";
				locations[FindLocation("Guadeloupe_Cave")].reload.l1.emerge = "reload1";
				LocatorReloadEnterDisable("Guadeloupe_Cave", "reload1_back", false);

				// Rosarak. Открываем выходы
				LocatorReloadEnterDisable("Shore28", "boat", false);
				LocatorReloadEnterDisable("Shore29", "boat", false);
				LocatorReloadEnterDisable("Mayak4", "boat", false);
				LocatorReloadEnterDisable("Baster_town", "reload1_back", false);
				LocatorReloadEnterDisable("Baster_town", "boat", false);
				// Log_Info("Проход к гробнице закрылся");
			}
		break;

		case "Step_52":
			dialog.text = StringFromKey("Ascold_219");
			link.l1 = StringFromKey("Ascold_220", pchar);
			link.l1.go = "Step_53";
		break;

		case "Step_53":
			dialog.text = StringFromKey("Ascold_221", pchar);
			link.l1 = StringFromKey("Ascold_222", pchar);
			link.l1.go = "Step_54";
		break;

		case "Step_54":
			dialog.text = StringFromKey("Ascold_223", pchar);
			link.l1 = StringFromKey("Ascold_224", pchar);
			link.l1.go = "Step_55";
		break;

		case "Step_55":
			dialog.text = StringFromKey("Ascold_225");
			link.l1 = StringFromKey("Ascold_226");
			link.l1.go = "Step_56";
		break;

		case "Step_56":
			dialog.text = StringFromKey("Ascold_227");
			link.l1 = StringFromKey("Ascold_228");
			link.l1.go = "Step_57";
		break;

		case "Step_57":
			dialog.text = StringFromKey("Ascold_229", pchar);
			link.l1 = StringFromKey("Ascold_230");
			link.l1.go = "Step_58";
		break;

		case "Step_58":
			dialog.text = StringFromKey("Ascold_231", pchar);
			link.l1 = StringFromKey("Ascold_232", pchar);
			link.l1.go = "Step_59";
		break;

		case "Step_59":
			dialog.text = StringFromKey("Ascold_233", pchar);
			link.l1 = StringFromKey("Ascold_234");
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Guadeloupe_Cave", "reload3_back", true);
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], false);
			pchar.quest.Ascold_LeifIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.Ascold_LeifIsDead.win_condition.l1.character = "LeifEricson";
			pchar.quest.Ascold_LeifIsDead.function = "Ascold_LeifIsDead";
			NextDiag.TempNode = "AfterAttackMummy";
			pchar.questTemp.Ascold = "Ascold_SaveWorld";

			sld = CharacterFromID("LeifEricson");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Guadeloupe_Cave", "goto", "goto2");
			AddLandQuestmark_Main(sld, "Ascold");
			AddLandQuestmark_Main_WithCondition(npchar, "Ascold", "Ascold_SaveWorld_QuestMarkCondition");

			pchar.quest.Ascold_LeifLastWord.win_condition.l1 = "locator";
			pchar.quest.Ascold_LeifLastWord.win_condition.l1.location = "Guadeloupe_Cave";
			pchar.quest.Ascold_LeifLastWord.win_condition.l1.locator_group = "reload";
			pchar.quest.Ascold_LeifLastWord.win_condition.l1.locator = "reload3";
			pchar.quest.Ascold_LeifLastWord.function = "Ascold_LeifLastWord";
		break;

		case "Step_60":
			dialog.text = StringFromKey("Ascold_235", pchar);
			link.l1 = StringFromKey("Ascold_236", pchar);
			link.l1.go = "Step_61";
			if (CheckCharacterItem(pchar, "Azzy_bottle"))
			{
				link.l2 = StringFromKey("Ascold_237", pchar);
				link.l2.go = "Step_63";
			}
		break;

		case "Step_61":
			dialog.text = StringFromKey("Ascold_238");
			link.l1 = StringFromKey("Ascold_239", pchar);
			link.l1.go = "Step_62";
		break;

		case "Step_62":
			dialog.text = StringFromKey("Ascold_240");
			link.l1 = StringFromKey("Ascold_241");
			link.l1.go = "exit";
			NextDiag.TempNode = "GoodFriends";
			pchar.questTemp.Ascold = "Ascold_OverBusiness";
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Ascold")], "BasTer_houseSp1", "sit", "sit1"); //Обратно сажаем
			LAi_SetSitType(&characters[GetCharacterIndex("Ascold")]);
			RemoveLandQuestmark_Main(npchar, "Ascold");
		break;

		case "GoodFriends":
			dialog.text = StringFromKey("Ascold_242", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Ascold_243", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "GoodFriends";
			if (pchar.questTemp.Azzy == "HowToKnowAzzy")
			{
				link.l1 = StringFromKey("Ascold_244");
				link.l1.go = "Step_64";
			}
		break;

		case "Step_63":
			dialog.text = StringFromKey("Ascold_245");
			link.l1 = StringFromKey("Ascold_246");
			link.l1.go = "BuyAzzy";
			link.l2 = StringFromKey("Ascold_247");
			link.l2.go = "Step_62";
		break;

		case "BuyAzzy":
			dialog.text = StringFromKey("Ascold_248");
			link.l1 = StringFromKey("Ascold_249");
			link.l1.go = "Step_62";
			TakeItemFromCharacter(pchar, "Azzy_bottle");
			AddMoneyToCharacter(pchar, 50000);
			Ascold_FreeAzzy_DelQuestMarks();
		break;

		case "Step_64":
			dialog.text = StringFromKey("Ascold_250");
			link.l1 = StringFromKey("Ascold_251");
			link.l1.go = "Step_65";
		break;

		case "Step_65":
			dialog.text = StringFromKey("Ascold_252", pchar);
			link.l1 = StringFromKey("Ascold_253");
			link.l1.go = "Step_66";
		break;

		case "Step_66":
			dialog.text = StringFromKey("Ascold_254");
			link.l1 = StringFromKey("Ascold_255");
			link.l1.go = "Step_67";
		break;

		case "Step_67":
			dialog.text = StringFromKey("Ascold_256");
			link.l1 = StringFromKey("Ascold_257");
			link.l1.go = "Step_68";
		break;

		case "Step_68":
			dialog.text = StringFromKey("Ascold_258");
			link.l1 = StringFromKey("Ascold_259");
			link.l1.go = "Step_69";
		break;

		case "Step_69":
			dialog.text = StringFromKey("Ascold_260");
			link.l1 = StringFromKey("Ascold_261", pchar);
			link.l1.go = "Step_70";
		break;

		case "Step_70":
			dialog.text = StringFromKey("Ascold_262", pchar);
			link.l1 = StringFromKey("Ascold_263");
			link.l1.go = "exit";
			pchar.questTemp.Azzy = "DestrContract";
			if (sti(pchar.questTemp.Azzy.Immortal.Penalty) >= 15 && GetQuestPastDayParam("questTemp.Azzy") > 90)
			{
				dialog.text = StringFromKey("Ascold_264");
				link.l1 = StringFromKey("Ascold_265", pchar);
				link.l1.go = "Step_71";
			}
			RemoveLandQuestmark_Main(npchar, "Azzy_HellSign");
			AddLandQuestmark_Main(CharacterFromID("Oliver_Green"), "Azzy_HellSign");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_Hostess"), "Azzy_HellSign");
		break;

		case "Step_71":
			dialog.text = StringFromKey("Ascold_266", pchar);
			link.l1 = StringFromKey("Ascold_267");
			link.l1.go = "Step_72";
			GiveItem2Character(pchar, "sculMa1");
			GiveItem2Character(pchar, "sculMa2");
			GiveItem2Character(pchar, "sculMa3");
			GiveItem2Character(pchar, "indian22");
		break;

		case "Step_72":
			dialog.text = StringFromKey("Ascold_268");
			link.l1 = StringFromKey("Ascold_269", pchar);
			link.l1.go = "exit";
		break;
	}
}



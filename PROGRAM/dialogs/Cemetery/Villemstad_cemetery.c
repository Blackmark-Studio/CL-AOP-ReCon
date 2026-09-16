// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	switch (Dialog.CurrentNode)
	{
		case "Second time":
			dialog.text = StringFromKey("Villemstad_cemetery_1", GetFullName(pchar));
			link.l1 = StringFromKey("Villemstad_cemetery_2");
			link.l1.go = "quests";
			//возвращаемся на кладбище ГПК
			if (CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "BackToCemeteryLSC")
			{
				link.l1 = StringFromKey("Villemstad_cemetery_3");
				link.l1.go = "BackToCemeteryLSC_1";
			}
		break;

		case "First time":
		//возвращаемся на кладбище ГПК
			if (CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "BackToCemeteryLSC")
			{
				link.l9 = StringFromKey("Villemstad_cemetery_4");
				link.l9.go = "BackToCemeteryLSC_1";
			}
		break;

		case "quests":
			dialog.text = StringFromKey("Villemstad_cemetery_7", RandPhraseSimple(
						StringFromKey("Villemstad_cemetery_5"),
						StringFromKey("Villemstad_cemetery_6")));
			link.l1 = StringFromKey("Villemstad_cemetery_10", RandPhraseSimple(
						StringFromKey("Villemstad_cemetery_8", pchar),
						StringFromKey("Villemstad_cemetery_9")));
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "goToCemeteryLSC")
			{
				link.l1 = StringFromKey("Villemstad_cemetery_11");
				link.l1.go = "CemeteryLSC_1";
				NextDiag.TempNode = "Second time";
			}
			if (CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "DiggingDoneLSC")
			{
				link.l1 = StringFromKey("Villemstad_cemetery_12");
				link.l1.go = "DiggingDoneLSC_1";
			}
			if (CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "LogbookFoundLSC")
			{
				link.l1 = StringFromKey("Villemstad_cemetery_13");
				link.l1.go = "LogbookFoundLSC_1";
				NextDiag.TempNode = "First time";
			}
		break;

		case "CemeteryLSC_1":
			dialog.text = StringFromKey("Villemstad_cemetery_14");
			link.l1 = StringFromKey("Villemstad_cemetery_15");
			link.l1.go = "CemeteryLSC_2";
		break;
		case "CemeteryLSC_2":
			dialog.text = StringFromKey("Villemstad_cemetery_16");
			link.l1 = StringFromKey("Villemstad_cemetery_17");
			link.l1.go = "CemeteryLSC_3";
		break;
		case "CemeteryLSC_3":
			dialog.text = StringFromKey("Villemstad_cemetery_18");
			link.l1 = StringFromKey("Villemstad_cemetery_19");
			link.l1.go = "CemeteryLSC_4";
		break;
		case "CemeteryLSC_4":
			dialog.text = StringFromKey("Villemstad_cemetery_20");
			link.l1 = StringFromKey("Villemstad_cemetery_21");
			link.l1.go = "CemeteryLSC_5";
		break;
		case "CemeteryLSC_5":
			dialog.text = StringFromKey("Villemstad_cemetery_22");
			link.l1 = StringFromKey("Villemstad_cemetery_23");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "FindGraveLSC";
			AddQuestRecord("ISS_PoorsMurder", "15");
		break;

		case "DiggingDoneLSC_1":
			dialog.text = StringFromKey("Villemstad_cemetery_24");
			link.l1 = StringFromKey("Villemstad_cemetery_25", pchar);
			link.l1.go = "DiggingDoneLSC_3";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = StringFromKey("Villemstad_cemetery_26");
				link.l2.go = "DiggingDoneLSC_2";
			}
		break;
		case "DiggingDoneLSC_2":
			AddCharacterExpToSkill(pchar, "Sailing", 20);
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = StringFromKey("Villemstad_cemetery_27");
			link.l1 = StringFromKey("Villemstad_cemetery_28");
			link.l1.go = "DiggingDoneLSC_4";
		break;
		case "DiggingDoneLSC_3":
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			dialog.text = StringFromKey("Villemstad_cemetery_29");
			link.l1 = StringFromKey("Villemstad_cemetery_30");
			link.l1.go = "DiggingDoneLSC_4";
		break;
		case "DiggingDoneLSC_4":
			dialog.text = StringFromKey("Villemstad_cemetery_31");
			link.l1 = StringFromKey("Villemstad_cemetery_32");
			link.l1.go = "DiggingDoneLSC_5";
		break;
		case "DiggingDoneLSC_5":
			dialog.text = StringFromKey("Villemstad_cemetery_33");
			link.l1 = StringFromKey("Villemstad_cemetery_34");
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Villemstad_Graveyard", "reload4", false);
			LocatorReloadEnterDisable("Villemstad_Graveyard", "reload5", false);
			LocatorReloadEnterDisable("Villemstad_Graveyard", "reload6", false);
			pchar.questTemp.LSC = "InvestigationCryptLSC";
			AddItemLog(pchar, "keyForCryptLSC", "1", StringFromKey("InfoMessages_135", GetItemName("keyForCryptLSC")), "Important_item");
			pchar.quest.LSC_OpenCryptDoor.win_condition.l1 = "locator";
			pchar.quest.LSC_OpenCryptDoor.win_condition.l1.location = "Villemstad_CryptBig2";
			pchar.quest.LSC_OpenCryptDoor.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_OpenCryptDoor.win_condition.l1.locator = "reload2";
			pchar.quest.LSC_OpenCryptDoor.function = "LSC_OpenCryptDoor";
		break;

		case "LogbookFoundLSC_1":
			dialog.text = StringFromKey("Villemstad_cemetery_35");
			link.l1 = StringFromKey("Villemstad_cemetery_36");
			link.l1.go = "LogbookFoundLSC_2";
		break;
		case "LogbookFoundLSC_2":
			dialog.text = StringFromKey("Villemstad_cemetery_37");
			link.l1 = StringFromKey("Villemstad_cemetery_38");
			link.l1.go = "LogbookFoundLSC_3";
		break;
		case "LogbookFoundLSC_3":
			dialog.text = StringFromKey("Villemstad_cemetery_39");
			link.l1 = StringFromKey("Villemstad_cemetery_40");
			link.l1.go = "LogbookFoundLSC_4";
		break;
		case "LogbookFoundLSC_4":
			dialog.text = StringFromKey("Villemstad_cemetery_41");
			link.l1 = StringFromKey("Villemstad_cemetery_42");
			link.l1.go = "LogbookFoundLSC_5";
		break;
		case "LogbookFoundLSC_5":
			dialog.text = StringFromKey("Villemstad_cemetery_43");
			link.l1 = StringFromKey("Villemstad_cemetery_44", pchar);
			link.l1.go = "LogbookFoundLSC_6";
		break;
		case "LogbookFoundLSC_6":
			dialog.text = StringFromKey("Villemstad_cemetery_45");
			link.l1 = StringFromKey("Villemstad_cemetery_46");
			link.l1.go = "LogbookFoundLSC_7";
		break;
		case "LogbookFoundLSC_7":
			dialog.text = StringFromKey("Villemstad_cemetery_47");
			link.l1 = StringFromKey("Villemstad_cemetery_48");
			link.l1.go = "LogbookFoundLSC_8";
		break;
		case "LogbookFoundLSC_8":
			dialog.text = StringFromKey("Villemstad_cemetery_49");
			link.l1 = StringFromKey("Villemstad_cemetery_50");
			link.l1.go = "LogbookFoundLSC_9";
		break;
		case "LogbookFoundLSC_9":
			dialog.text = StringFromKey("Villemstad_cemetery_51");
			link.l1 = StringFromKey("Villemstad_cemetery_52");
			link.l1.go = "LogbookFoundLSC_10";
		break;
		case "LogbookFoundLSC_10":
			dialog.text = StringFromKey("Villemstad_cemetery_53", pchar);
			link.l1 = StringFromKey("Villemstad_cemetery_54");
			link.l1.go = "LogbookFoundLSC_11";
			//            if ((GetCharacterSPECIAL(pchar, SPECIAL_P) + GetCharacterSPECIAL(pchar, SPECIAL_I)) >= 7)
			if (PlayerRPGCheck_SPECIAL_Sum(SPECIAL_P + "," + SPECIAL_I, 7))
			{
				link.l1 = StringFromKey("Villemstad_cemetery_55");
				link.l1.go = "LogbookFoundLSC_18";
			}
		break;
		case "LogbookFoundLSC_11":
			dialog.text = StringFromKey("Villemstad_cemetery_56");
			link.l1 = StringFromKey("Villemstad_cemetery_57");
			link.l1.go = "LogbookFoundLSC_12";
		break;
		case "LogbookFoundLSC_12":
			dialog.text = StringFromKey("Villemstad_cemetery_58", pchar);
			link.l1 = StringFromKey("Villemstad_cemetery_59");
			link.l1.go = "LogbookFoundLSC_13";
		break;
		case "LogbookFoundLSC_13":
			dialog.text = StringFromKey("Villemstad_cemetery_60");
			link.l1 = StringFromKey("Villemstad_cemetery_61");
			link.l1.go = "LogbookFoundLSC_14";
		break;
		case "LogbookFoundLSC_14":
			dialog.text = StringFromKey("Villemstad_cemetery_62", pchar);
			link.l1 = StringFromKey("Villemstad_cemetery_63");
			link.l1.go = "LogbookFoundLSC_15";
		break;
		case "LogbookFoundLSC_15":
			dialog.text = "...";
			link.l1 = StringFromKey("Villemstad_cemetery_64");
			link.l1.go = "LogbookFoundLSC_16";
		break;
		case "LogbookFoundLSC_16":
			dialog.text = "...";
			link.l1 = StringFromKey("Villemstad_cemetery_65");
			link.l1.go = "LogbookFoundLSC_17";
		break;
		case "LogbookFoundLSC_17":
			dialog.text = StringFromKey("Villemstad_cemetery_66");
			link.l1 = StringFromKey("Villemstad_cemetery_67");
			link.l1.go = "LogbookFoundLSC_26";
			AddQuestRecord("ISS_PoorsMurder", "19");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("", "ла"));
		break;
		case "LogbookFoundLSC_18":
			dialog.text = StringFromKey("Villemstad_cemetery_68");
			link.l1 = StringFromKey("Villemstad_cemetery_69");
			link.l1.go = "LogbookFoundLSC_19";
		break;
		case "LogbookFoundLSC_19":
			dialog.text = StringFromKey("Villemstad_cemetery_70");
			link.l1 = StringFromKey("Villemstad_cemetery_71");
			link.l1.go = "LogbookFoundLSC_20";
		break;
		case "LogbookFoundLSC_20":
			dialog.text = StringFromKey("Villemstad_cemetery_72");
			link.l1 = StringFromKey("Villemstad_cemetery_73");
			link.l1.go = "LogbookFoundLSC_21";
		break;
		case "LogbookFoundLSC_21":
			dialog.text = "...";
			link.l1 = StringFromKey("Villemstad_cemetery_74");
			link.l1.go = "LogbookFoundLSC_22";
		break;
		case "LogbookFoundLSC_22":
			dialog.text = "...";
			link.l1 = StringFromKey("Villemstad_cemetery_75");
			link.l1.go = "LogbookFoundLSC_23";
		break;
		case "LogbookFoundLSC_23":
			dialog.text = "...";
			link.l1 = StringFromKey("Villemstad_cemetery_76");
			link.l1.go = "LogbookFoundLSC_24";
		break;
		case "LogbookFoundLSC_24":
			dialog.text = StringFromKey("Villemstad_cemetery_77");
			link.l1 = StringFromKey("Villemstad_cemetery_78");
			link.l1.go = "LogbookFoundLSC_25";
		break;
		case "LogbookFoundLSC_25":
			dialog.text = StringFromKey("Villemstad_cemetery_79");
			link.l1 = StringFromKey("Villemstad_cemetery_80");
			link.l1.go = "LogbookFoundLSC_26";
			pchar.questTemp.LSC = "GoodQuestBookLSC";
			AddQuestRecord("ISS_PoorsMurder", "20");
		break;
		case "LogbookFoundLSC_26":
			dialog.text = StringFromKey("Villemstad_cemetery_81");
			link.l1 = StringFromKey("Villemstad_cemetery_82");
			link.l1.go = "LogbookFoundLSC_41";
			//            if (pchar.questTemp.LSC == "GoodQuestBookLSC" && (GetCharacterSPECIAL(pchar, SPECIAL_P) + GetCharacterSPECIAL(pchar, SPECIAL_I) + GetCharacterSPECIAL(pchar, SPECIAL_L)) >= 14)
			if (pchar.questTemp.LSC == "GoodQuestBookLSC" && PlayerRPGCheck_SPECIAL_Sum(SPECIAL_P + "," + SPECIAL_I + "," + SPECIAL_L, 14))
			{
				link.l2 = StringFromKey("Villemstad_cemetery_83");
				link.l2.go = "LogbookFoundLSC_27";
			}
		break;
		case "LogbookFoundLSC_27":
			dialog.text = StringFromKey("Villemstad_cemetery_84");
			link.l1 = StringFromKey("Villemstad_cemetery_85");
			link.l1.go = "LogbookFoundLSC_28";
		break;
		case "LogbookFoundLSC_28":
			dialog.text = StringFromKey("Villemstad_cemetery_86");
			link.l1 = StringFromKey("Villemstad_cemetery_87");
			link.l1.go = "LogbookFoundLSC_29";
		break;
		case "LogbookFoundLSC_29":
			dialog.text = "...";
			link.l1 = StringFromKey("Villemstad_cemetery_88");
			link.l1.go = "LogbookFoundLSC_30";
		break;
		case "LogbookFoundLSC_30":
			dialog.text = "...";
			link.l1 = StringFromKey("Villemstad_cemetery_89");
			link.l1.go = "LogbookFoundLSC_31";
		break;
		case "LogbookFoundLSC_31":
			dialog.text = StringFromKey("Villemstad_cemetery_90");
			link.l1 = StringFromKey("Villemstad_cemetery_91");
			link.l1.go = "LogbookFoundLSC_32";
		break;
		case "LogbookFoundLSC_32":
			dialog.text = "...";
			link.l1 = StringFromKey("Villemstad_cemetery_92");
			link.l1.go = "LogbookFoundLSC_33";
		break;
		case "LogbookFoundLSC_33":
			dialog.text = "...";
			link.l1 = StringFromKey("Villemstad_cemetery_93");
			link.l1.go = "LogbookFoundLSC_33_1";
		break;
		case "LogbookFoundLSC_33_1":
			dialog.text = "...";
			link.l1 = StringFromKey("Villemstad_cemetery_94");
			link.l1.go = "LogbookFoundLSC_34";
		break;
		case "LogbookFoundLSC_34":
			dialog.text = "...";
			link.l1 = StringFromKey("Villemstad_cemetery_95");
			link.l1.go = "LogbookFoundLSC_35";
		break;
		case "LogbookFoundLSC_35":
			dialog.text = StringFromKey("Villemstad_cemetery_96");
			link.l1 = StringFromKey("Villemstad_cemetery_97");
			link.l1.go = "LogbookFoundLSC_35_1";
		break;
		case "LogbookFoundLSC_35_1":
			dialog.text = StringFromKey("Villemstad_cemetery_98");
			link.l1 = StringFromKey("Villemstad_cemetery_99");
			link.l1.go = "LogbookFoundLSC_36";
		break;
		case "LogbookFoundLSC_36":
			dialog.text = StringFromKey("Villemstad_cemetery_100");
			link.l1 = StringFromKey("Villemstad_cemetery_101");
			link.l1.go = "LogbookFoundLSC_37";
		break;
		case "LogbookFoundLSC_37":
			dialog.text = StringFromKey("Villemstad_cemetery_102");
			link.l1 = StringFromKey("Villemstad_cemetery_103");
			link.l1.go = "LogbookFoundLSC_38";
		break;
		case "LogbookFoundLSC_38":
			dialog.text = StringFromKey("Villemstad_cemetery_104");
			link.l1 = StringFromKey("Villemstad_cemetery_105");
			link.l1.go = "LogbookFoundLSC_39";
		break;
		case "LogbookFoundLSC_39":
			dialog.text = StringFromKey("Villemstad_cemetery_106");
			link.l1 = StringFromKey("Villemstad_cemetery_107");
			link.l1.go = "LogbookFoundLSC_40";
		break;
		case "LogbookFoundLSC_40":
			ref sld = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			dialog.text = StringFromKey("Villemstad_cemetery_108");
			link.l1 = StringFromKey("Villemstad_cemetery_109", GetFullName(sld), XI_ConvertString("Colony" + sld.city));
			link.l1.go = "TrueStoryCemeteryLSC_1";
			PlaySound("Took_item");
			RemoveItems(pchar, "keyForCryptLSC", 1);
		break;
		case "LogbookFoundLSC_41":
			Nextdiag.CurrentNode = "First time";
			DialogExit();
			pchar.questTemp.UndertakersSurveyLSC = 0;
			pchar.questTemp.LSC = "UndertakersSurveyLSC";
			PlaySound("Took_item");
			RemoveItems(pchar, "keyForCryptLSC", 1);
			LocatorReloadEnterDisable("Villemstad_CryptBig2", "reload2", true);
			AddQuestRecord("ISS_PoorsMurder", "21");

			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			AddLandQuestMark_Main(CharacterFromId("Tortuga_Cemeteryman"), "ISS_PoorsMurder");
			AddLandQuestMark_Main(CharacterFromId("PortRoyal_Cemeteryman"), "ISS_PoorsMurder");
			AddLandQuestMark_Main(CharacterFromId("Havana_Cemeteryman"), "ISS_PoorsMurder");
		break;

		//возвращаемся на кладбище ГПК
		case "BackToCemeteryLSC_1":
			dialog.text = StringFromKey("Villemstad_cemetery_110");
			link.l1 = StringFromKey("Villemstad_cemetery_111", pchar.questTemp.LSC.poorName);
			link.l1.go = "TrueStoryCemeteryLSC_1";
		break;

		//соединение ветвлений квеста
		case "TrueStoryCemeteryLSC_1":
			dialog.text = StringFromKey("Villemstad_cemetery_112", pchar.questTemp.LSC.poorName);
			link.l1 = StringFromKey("Villemstad_cemetery_113");
			link.l1.go = "TrueStoryCemeteryLSC_2";
		break;
		case "TrueStoryCemeteryLSC_2":
			dialog.text = StringFromKey("Villemstad_cemetery_114");
			link.l1 = StringFromKey("Villemstad_cemetery_115");
			link.l1.go = "TrueStoryCemeteryLSC_3";
		break;
		case "TrueStoryCemeteryLSC_3":
			dialog.text = StringFromKey("Villemstad_cemetery_116");
			link.l1 = StringFromKey("Villemstad_cemetery_117");
			link.l1.go = "TrueStoryCemeteryLSC_4";
		break;
		case "TrueStoryCemeteryLSC_4":
			dialog.text = StringFromKey("Villemstad_cemetery_118");
			link.l1 = StringFromKey("Villemstad_cemetery_119");
			link.l1.go = "TrueStoryCemeteryLSC_5";
		break;
		case "TrueStoryCemeteryLSC_5":
			dialog.text = StringFromKey("Villemstad_cemetery_120");
			link.l1 = "...";
			link.l1.go = "TrueStoryCemeteryLSC_6";
		break;
		case "TrueStoryCemeteryLSC_6":
			dialog.text = StringFromKey("Villemstad_cemetery_121");
			link.l1 = StringFromKey("Villemstad_cemetery_122");
			link.l1.go = "TrueStoryCemeteryLSC_7";
		break;
		case "TrueStoryCemeteryLSC_7":
			dialog.text = StringFromKey("Villemstad_cemetery_123");
			link.l1 = StringFromKey("Villemstad_cemetery_124");
			link.l1.go = "TrueStoryCemeteryLSC_8";
		break;
		case "TrueStoryCemeteryLSC_8":
			dialog.text = StringFromKey("Villemstad_cemetery_125");
			link.l1 = "...";
			link.l1.go = "TrueStoryCemeteryLSC_9";
		break;
		case "TrueStoryCemeteryLSC_9":
			dialog.text = StringFromKey("Villemstad_cemetery_126");
			link.l1 = StringFromKey("Villemstad_cemetery_127");
			link.l1.go = "TrueStoryCemeteryLSC_10";
		break;
		case "TrueStoryCemeteryLSC_10":
			dialog.text = StringFromKey("Villemstad_cemetery_128");
			link.l1 = StringFromKey("Villemstad_cemetery_129");
			link.l1.go = "TrueStoryCemeteryLSC_11";
		break;
		case "TrueStoryCemeteryLSC_11":
			dialog.text = StringFromKey("Villemstad_cemetery_130");
			link.l1 = StringFromKey("Villemstad_cemetery_131");
			link.l1.go = "TrueStoryCemeteryLSC_12";
		break;
		case "TrueStoryCemeteryLSC_12":
			dialog.text = StringFromKey("Villemstad_cemetery_132");
			link.l1 = "...";
			link.l1.go = "TrueStoryCemeteryLSC_13";
		break;
		case "TrueStoryCemeteryLSC_13":
			dialog.text = StringFromKey("Villemstad_cemetery_133");
			link.l1 = StringFromKey("Villemstad_cemetery_134");
			link.l1.go = "TrueStoryCemeteryLSC_14";
		break;
		case "TrueStoryCemeteryLSC_14":
			dialog.text = StringFromKey("Villemstad_cemetery_135", pchar.name);
			link.l1 = StringFromKey("Villemstad_cemetery_136");
			link.l1.go = "TrueStoryCemeteryLSC_15";
		break;
		case "TrueStoryCemeteryLSC_15":
			dialog.text = StringFromKey("Villemstad_cemetery_137");
			link.l1 = StringFromKey("Villemstad_cemetery_138");
			link.l1.go = "TrueStoryCemeteryLSC_16";
		break;
		case "TrueStoryCemeteryLSC_16":
			dialog.text = StringFromKey("Villemstad_cemetery_139");
			link.l1 = StringFromKey("Villemstad_cemetery_140");
			link.l1.go = "TrueStoryCemeteryLSC_17";
		break;
		case "TrueStoryCemeteryLSC_17":
			dialog.text = StringFromKey("Villemstad_cemetery_141");
			link.l1 = StringFromKey("Villemstad_cemetery_142");
			link.l1.go = "TrueStoryCemeteryLSC_18";
		break;
		case "TrueStoryCemeteryLSC_18":
			dialog.text = StringFromKey("Villemstad_cemetery_143");
			link.l1 = StringFromKey("Villemstad_cemetery_144");
			link.l1.go = "TrueStoryCemeteryLSC_19";
		break;
		case "TrueStoryCemeteryLSC_19":
			dialog.text = StringFromKey("Villemstad_cemetery_145");
			link.l1 = StringFromKey("Villemstad_cemetery_146");
			link.l1.go = "TrueStoryCemeteryLSC_20";
		break;
		case "TrueStoryCemeteryLSC_20":
			dialog.text = StringFromKey("Villemstad_cemetery_147");
			link.l1 = StringFromKey("Villemstad_cemetery_148");
			link.l1.go = "TrueStoryCemeteryLSC_21";
			AddQuestRecord("ISS_PoorsMurder", "29");
		break;
		case "TrueStoryCemeteryLSC_21":
			dialog.text = StringFromKey("Villemstad_cemetery_149");
			link.l1 = StringFromKey("Villemstad_cemetery_150");
			link.l1.go = "TrueStoryCemeteryLSC_22";
		break;
		case "TrueStoryCemeteryLSC_22":
			dialog.text = StringFromKey("Villemstad_cemetery_151");
			link.l1 = StringFromKey("Villemstad_cemetery_152");
			link.l1.go = "TrueStoryCemeteryLSC_23";
		break;
		case "TrueStoryCemeteryLSC_23":
			dialog.text = StringFromKey("Villemstad_cemetery_153");
			link.l1 = StringFromKey("Villemstad_cemetery_154");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "AskTheSmugglerLSC";

			RemoveLandQuestMark_Main(npchar, "ISS_PoorsMurder");
			ISS_PoorsMurder_FindTizer_Smuggler_AddQuestMarks();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);
}


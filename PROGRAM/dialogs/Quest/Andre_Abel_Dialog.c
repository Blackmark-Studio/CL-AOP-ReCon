void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string attrLoc = Dialog.CurrentNode;

	if (HasSubStr(attrLoc, "AndreAbelQuestSetNationLicence_"))
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.LicenceNation = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "Andre_Abel_In_Tavern_Quest_Complete_2";
	}

	switch (Dialog.CurrentNode)
	{
		case "First time":
			PChar.QuestTemp.AndreAbelQuest_StartQuest = true;

			dialog.text = StringFromKey("Andre_Abel_Dialog_3", RandPhraseSimple(
						StringFromKey("Andre_Abel_Dialog_1"),
						StringFromKey("Andre_Abel_Dialog_2")));
			if (GetCompanionQuantity(PChar) < COMPANION_MAX)
			{
				link.l1 = StringFromKey("Andre_Abel_Dialog_4", pchar);
				link.l1.go = "Andre_Abel_1";
			}
			else
			{
				// > Подсказка про полную эскадру
				link.l1 = StringFromKey("Andre_Abel_Dialog_5") + " " + StringFromKey("Andre_Abel_Dialog_97");
				link.l1.go = "exit";
				break;
			}

			link.l2 = StringFromKey("Andre_Abel_Dialog_5");
			link.l2.go = "exit";
		break;

		case "Andre_Abel_1":
			dialog.text = StringFromKey("Andre_Abel_Dialog_6", GetFullName(NPChar), NPChar.ship.name);
			link.l1 = StringFromKey("Andre_Abel_Dialog_7", GetFullName(PChar));
			link.l1.go = "Andre_Abel_2";
		break;

		case "Andre_Abel_2":
			dialog.text = StringFromKey("Andre_Abel_Dialog_8");
			link.l1 = StringFromKey("Andre_Abel_Dialog_9", pchar);
			link.l1.go = "Andre_Abel_3";
		break;

		case "Andre_Abel_3":
			dialog.text = StringFromKey("Andre_Abel_Dialog_10");
			link.l1 = StringFromKey("Andre_Abel_Dialog_11");
			link.l1.go = "Andre_Abel_5";
			link.l2 = StringFromKey("Andre_Abel_Dialog_12");
			link.l2.go = "Andre_Abel_4";
		break;

		case "Andre_Abel_4":
			dialog.text = StringFromKey("Andre_Abel_Dialog_13");
			link.l1 = StringFromKey("Andre_Abel_Dialog_14");
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			NPChar.LifeDay = 0;
			NextDiag.TempNode = "Andre_Abel_No_Quest";
			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
			RemoveMapQuestMark("FortFrance_town", "Andre_Abel_Quest");
			DeleteAttribute(pchar, "QuestTemp.AndreAbelQuest");
		break;

		case "Andre_Abel_No_Quest":
			dialog.text = StringFromKey("Andre_Abel_Dialog_17", RandPhraseSimple(
						StringFromKey("Andre_Abel_Dialog_15"),
						StringFromKey("Andre_Abel_Dialog_16")));
			link.l1 = StringFromKey("Andre_Abel_Dialog_18");
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_No_Quest";
		break;

		case "Andre_Abel_5":
			dialog.text = StringFromKey("Andre_Abel_Dialog_19");
			link.l1 = StringFromKey("Andre_Abel_Dialog_20", pchar);
			link.l1.go = "Andre_Abel_6";
			link.l2 = StringFromKey("Andre_Abel_Dialog_21");
			link.l2.go = "Andre_Abel_4";
		break;

		case "Andre_Abel_6":
			dialog.text = StringFromKey("Andre_Abel_Dialog_22");
			link.l1 = StringFromKey("Andre_Abel_Dialog_23");
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			SetQuestHeader("Andre_Abel_Quest");
			AddQuestRecord("Andre_Abel_Quest", "1");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("ся", "ась"));
			SetFunctionTimerCondition("Andre_Abel_Quest_2Days_Left", 0, 0, 2, false);
			NextDiag.TempNode = "Andre_Abel_To_Sea_1";
			RemoveMapQuestMark("FortFrance_town", "Andre_Abel_Quest");
		break;

		case "Andre_Abel_7":
			dialog.text = StringFromKey("Andre_Abel_Dialog_26", RandPhraseSimple(
						StringFromKey("Andre_Abel_Dialog_24", GetFullName(PChar)),
						StringFromKey("Andre_Abel_Dialog_25")));
			link.l1 = StringFromKey("Andre_Abel_Dialog_27");
			link.l1.go = "exit";
			NextDiag.Tempnode = "Andre_Abel_7";
		break;

		case "Andre_Abel_To_Sea_1":
			dialog.text = StringFromKey("Andre_Abel_Dialog_28");
			if (GetCompanionQuantity(PChar) != COMPANION_MAX)
			{
				link.l1 = StringFromKey("Andre_Abel_Dialog_29");
				link.l1.go = "Andre_Abel_To_Sea_2";
			}
			link.l2 = StringFromKey("Andre_Abel_Dialog_30");
			link.l2.go = "Andre_Abel_To_Sea_1_1";
			NextDiag.TempNode = "Andre_Abel_To_Sea_1";
		break;

		case "Andre_Abel_To_Sea_1_1":
			dialog.text = StringFromKey("Andre_Abel_Dialog_31");
			link.l1 = StringFromKey("Andre_Abel_Dialog_32");
			link.l1.go = "exit";
		break;

		case "Andre_Abel_To_Sea_2":
			dialog.text = StringFromKey("Andre_Abel_Dialog_33");
			link.l1 = StringFromKey("Andre_Abel_Dialog_34");
			link.l1.go = "Andre_Abel_To_Sea_3";
			NextDiag.TempNode = "Andre_Abel_7";
		break;

		case "Andre_Abel_To_Sea_3":
			DialogExit();
			NextDiag.CurrentNode = "Andre_Abel_7";
			AddQuestRecord("Andre_Abel_Quest", "3");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("", "а"));
			PChar.Quest.Andre_Abel_Quest_2Days_Left.over = "yes";
			SetFunctionTimerCondition("Andre_Abel_Quest_15_Days_Is_Left", 0, 0, 15, false);
			SetFunctionNPCDeathCondition("Andre_Abel_Quest_Andre_Is_Dead", "Andre_Abel", false);
			SetFunctionLocationCondition("Andre_Abel_Quest_Battle_With_Pirates_Squadron", "Hispaniola2", false);
			SetFunctionExitFromLocationCondition("Andre_Abel_Quest_Delete_Andre_From_Tavern", PChar.location, false);
		break;

		case "Andre_Abel_15Days_Left_1": // Это на случай, если время закончиться тогда, когда Абель будет подходить к ГГ в порту Порт-о-Принса
			if (PChar.location == "FortFrance_Tavern")    // Из таверны можно было не выходить fix
			{
				dialog.text = StringFromKey("Andre_Abel_Dialog_35", PChar.Name);
				link.l1 = StringFromKey("Andre_Abel_Dialog_96");
				link.l1.go = "Andre_Abel_15Days_Left_In_FortFrance";
				break;
			}
			dialog.text = StringFromKey("Andre_Abel_Dialog_36", PChar.Name);
			link.l1 = StringFromKey("Andre_Abel_Dialog_37");
			link.l1.go = "Andre_Abel_15Days_Left_2";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_SetImmortal(NPChar, true);
		break;

		case "Andre_Abel_15Days_Left_In_FortFrance":
			dialog.text = StringFromKey("Andre_Abel_Dialog_38");
			link.l1 = StringFromKey("Andre_Abel_Dialog_39");
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(NPChar);
			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
		break;

		case "Andre_Abel_15Days_Left_2":
			dialog.text = StringFromKey("Andre_Abel_Dialog_40");
			link.l1 = StringFromKey("Andre_Abel_Dialog_41");
			link.l1.go = "Andre_Abel_15Days_Left_3";
		break;

		case "Andre_Abel_15Days_Left_3":
			dialog.text = StringFromKey("Andre_Abel_Dialog_42");
			link.l1 = StringFromKey("Andre_Abel_Dialog_43");
			link.l1.go = "Andre_Abel_15Days_Left_4";
		break;

		case "Andre_Abel_15Days_Left_4":
			DialogExit();
			NPChar.LifeDay = 0;
			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
			LAi_CharacterDisableDialog(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload6_back", "none", "", "", "", -1);
		break;

		case "Andre_Abel_In_PortPax":
			dialog.text = StringFromKey("Andre_Abel_Dialog_44");
			link.l1 = StringFromKey("Andre_Abel_Dialog_45");
			link.l1.go = "Andre_Abel_In_PortPax_2";
			AddItemLog(pchar, "jewelry17", "33", StringFromKey("InfoMessages_178"), "Important_item");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen("PortPax_town", false);
			LAi_SetImmortal(NPChar, true);
			PChar.Quest.Andre_Abel_Quest_15_Days_Is_Left.over = "yes";
		break;

		case "Andre_Abel_In_PortPax_2":
			dialog.text = StringFromKey("Andre_Abel_Dialog_46");
			link.l1 = StringFromKey("Andre_Abel_Dialog_47");
			link.l1.go = "Andre_Abel_In_PortPax_5";
			link.l2 = StringFromKey("Andre_Abel_Dialog_48");
			link.l2.go = "Andre_Abel_In_PortPax_3";
		break;

		case "Andre_Abel_In_PortPax_3":
			dialog.text = StringFromKey("Andre_Abel_Dialog_49");
			link.l1 = StringFromKey("Andre_Abel_Dialog_50");
			link.l1.go = "Andre_Abel_In_PortPax_4";
		break;

		case "Andre_Abel_In_PortPax_4":
			DialogExit();
			LAi_SetPlayerType(PChar);
			AddQuestRecord("Andre_Abel_Quest", "9");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Andre_Abel_Quest");
			DeleteAttribute(pchar, "QuestTemp.AndreAbelQuest");
			PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead.over = "yes";
			NPChar.LifeDay = 0;
			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
			LAi_CharacterDisableDialog(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload6_back", "none", "", "", "", -1);
		break;

		case "Andre_Abel_In_PortPax_5":
			dialog.text = StringFromKey("Andre_Abel_Dialog_51");
			link.l1 = StringFromKey("Andre_Abel_Dialog_52");
			link.l1.go = "Andre_Abel_In_PortPax_6";
		break;

		case "Andre_Abel_In_PortPax_6":
			DialogExit();
			bDisableLandEncounters = true;
			LAi_SetSitType(PChar);
			LAi_ActorSetSitMode(NPChar);
			FreeSitLocator("PortPax_tavern", "sit_front2");
			FreeSitLocator("PortPax_tavern", "sit_base2");
			ChangeCharacterAddressGroup(NPChar, "PortPax_tavern", "sit", "sit_front2");
			QuestSetCurrentNode("Andre_Abel", "Andre_Abel_In_Tavern_1");
			DoFunctionReloadToLocation("PortPax_tavern", "sit", "sit_base2", "Andre_Abel_Quest_Dialog_In_PortPax_Tavern");
		break;

		case "Andre_Abel_In_Tavern_1":
			dialog.text = StringFromKey("Andre_Abel_Dialog_53");
			link.l1 = StringFromKey("Andre_Abel_Dialog_54");
			link.l1.go = "Andre_Abel_In_Tavern_2";
		break;

		case "Andre_Abel_In_Tavern_2":
			dialog.text = StringFromKey("Andre_Abel_Dialog_55", pchar);
			link.l1 = StringFromKey("Andre_Abel_Dialog_56");
			link.l1.go = "Andre_Abel_In_Tavern_3";
		break;

		case "Andre_Abel_In_Tavern_3":
			dialog.text = StringFromKey("Andre_Abel_Dialog_57");
			link.l1 = StringFromKey("Andre_Abel_Dialog_58");
			link.l1.go = "Andre_Abel_In_Tavern_4";
		break;

		case "Andre_Abel_In_Tavern_4":
			dialog.text = StringFromKey("Andre_Abel_Dialog_59");
			link.l1 = StringFromKey("Andre_Abel_Dialog_60");
			link.l1.go = "Andre_Abel_In_Tavern_7";
			link.l2 = StringFromKey("Andre_Abel_Dialog_61");
			link.l2.go = "Andre_Abel_In_Tavern_5";
			bDisableLandEncounters = false;
		break;

		case "Andre_Abel_In_Tavern_5":
			dialog.text = StringFromKey("Andre_Abel_Dialog_62", pchar);
			link.l1 = StringFromKey("Andre_Abel_Dialog_63");
			link.l1.go = "Andre_Abel_In_Tavern_6";
		break;

		case "Andre_Abel_In_Tavern_6":
			DialogExit();
			NPChar.greeting = "pirat_common";
			NPChar.LifeDay = 0;
			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
			NextDiag.CurrentNode = "Andre_Abel_In_PortPax_Tavern_No_Quest";
			AddQuestRecord("Andre_Abel_Quest", "9");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Andre_Abel_Quest");
			DeleteAttribute(pchar, "QuestTemp.AndreAbelQuest");
			LAi_SetSitType(NPChar);
			LAi_SetPlayerType(PChar);
			DoFunctionReloadToLocation("PortPax_tavern", "tables", "stay3", "");
		break;

		case "Andre_Abel_In_PortPax_Tavern_No_Quest":
			dialog.text = StringFromKey("Andre_Abel_Dialog_67", LinkRandPhrase(
						StringFromKey("Andre_Abel_Dialog_64"),
						StringFromKey("Andre_Abel_Dialog_65"),
						StringFromKey("Andre_Abel_Dialog_66")));
			link.l1 = StringFromKey("Andre_Abel_Dialog_68");
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_In_PortPax_Tavern_No_Quest";
		break;

		case "Andre_Abel_In_Tavern_7":
			dialog.text = StringFromKey("Andre_Abel_Dialog_69", pchar);
			link.l1 = StringFromKey("Andre_Abel_Dialog_70");
			link.l1.go = "Andre_Abel_In_Tavern_8";
			link.l2 = StringFromKey("Andre_Abel_Dialog_71");
			link.l2.go = "Andre_Abel_In_Tavern_5";
		break;

		case "Andre_Abel_In_Tavern_8":
			dialog.text = StringFromKey("Andre_Abel_Dialog_72");
			link.l1 = StringFromKey("Andre_Abel_Dialog_73");
			link.l1.go = "Andre_Abel_In_Tavern_9";
		break;

		case "Andre_Abel_In_Tavern_9":
			dialog.text = StringFromKey("Andre_Abel_Dialog_74");
			link.l1 = StringFromKey("Andre_Abel_Dialog_75");
			link.l1.go = "Andre_Abel_In_Tavern_10";
		break;

		case "Andre_Abel_In_Tavern_10":
			DialogExit();
			NextDiag.CurrentNode = "Andre_Abel_In_Tavern_Continue_Quest";
			LAi_SetSitType(NPChar);
			LAi_SetPlayerType(PChar);
			//HardCoffee для тестов портянки диалогов с Джекменом
			pchar.QuestTemp.AndreAbelQuest = "GoTo_Jackman1";
			AddLandQuestMark_Main(CharacterFromId("Jackman"), "Andre_Abel_Quest");
			//QuestSetCurrentNode("Jackman", "Andre_Abel_Quest_Jackman_Dialog_1");
			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
			DoFunctionReloadToLocation("PortPax_tavern", "tables", "stay3", "Andre_Abel_Quest_Dialog_In_PortPax_Tavern_End");
		break;

		case "Andre_Abel_In_Tavern_Continue_Quest":
			dialog.text = StringFromKey("Andre_Abel_Dialog_76", pchar);
			if (!CheckAttribute(PChar, "QuestTemp.Andre_Abel_Quest_Complete"))
			{
				link.l1 = StringFromKey("Andre_Abel_Dialog_80", LinkRandPhrase(
							StringFromKey("Andre_Abel_Dialog_77"),
							StringFromKey("Andre_Abel_Dialog_78"),
							StringFromKey("Andre_Abel_Dialog_79")));
				link.l1.go = "exit";
				NextDiag.TempNode = "Andre_Abel_In_Tavern_Continue_Quest";
			}
			else
			{
				link.l1 = StringFromKey("Andre_Abel_Dialog_81");
				link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_1";
			}
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_1":
			dialog.text = StringFromKey("Andre_Abel_Dialog_82");
			link.l1 = StringFromKey("Andre_Abel_Dialog_83");
			link.l1.go = "AndreAbelQuestSetNationLicence_0";
			link.l2 = StringFromKey("Andre_Abel_Dialog_84", pchar);
			link.l2.go = "AndreAbelQuestSetNationLicence_1";
			link.l3 = StringFromKey("Andre_Abel_Dialog_85");
			link.l3.go = "AndreAbelQuestSetNationLicence_2";
			link.l4 = StringFromKey("Andre_Abel_Dialog_86");
			link.l4.go = "AndreAbelQuestSetNationLicence_3";
			AddItemLog(pchar, "incas_collection", "1", StringFromKey("InfoMessages_137"), "Important_item");
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_2":
			dialog.text = StringFromKey("Andre_Abel_Dialog_87", pchar, XI_ConvertString(Nations[sti(NPChar.LicenceNation)].Name + "Gen"));
			link.l1 = StringFromKey("Andre_Abel_Dialog_88");
			link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_3";
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_3":
			dialog.text = StringFromKey("Andre_Abel_Dialog_89");
			link.l1 = StringFromKey("Andre_Abel_Dialog_90");
			link.l1.go = "Andre_Abel_In_Tavern_Quest_Complete_4";
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_4":
			DialogExit();
			NPChar.LifeDay = 0;
			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
			GiveNationLicence(sti(NPChar.LicenceNation), 50);
			SetCharacterShipLocation(NPChar, "");    // Уберем корабль из порта ("none" не работает - FindLocation вернёт -1) // > TODO: бесят меня эти none в безусловных местах в коде
			NextDiag.CurrentNode = "Andre_Abel_In_Tavern_Quest_Complete_5";
			AddQuestRecord("Andre_Abel_Quest", "23");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Andre_Abel_Quest", "sNation", XI_ConvertString(Nations[sti(NPChar.LicenceNation)].Name + "Gen"));
			CloseQuestHeader("Andre_Abel_Quest");
			DeleteAttribute(pchar, "QuestTemp.AndreAbelQuest");
			DeleteAttribute(pchar, "QuestTemp.Andre_Abel_Quest_Complete");
			Achievment_Set(ACH_Poslannik);
		break;

		case "Andre_Abel_In_Tavern_Quest_Complete_5":
			dialog.text = StringFromKey("Andre_Abel_Dialog_94", LinkRandPhrase(
						StringFromKey("Andre_Abel_Dialog_91", pchar),
						StringFromKey("Andre_Abel_Dialog_92", pchar),
						StringFromKey("Andre_Abel_Dialog_93")));
			link.l1 = StringFromKey("Andre_Abel_Dialog_95");
			link.l1.go = "exit";
			NextDiag.TempNode = "Andre_Abel_In_Tavern_Quest_Complete_5";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

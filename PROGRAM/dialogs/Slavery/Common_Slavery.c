void ProcessCommonSlavery(ref NPChar, aref Link, aref NextDiag)
{
	ref chr, sld;
	string attr, attrLoc;
	int i, iTemp, iTax, iFortValue;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Slavery_4", LinkRandPhrase(
								StringFromKey("Common_Slavery_1"),
								StringFromKey("Common_Slavery_2"),
								StringFromKey("Common_Slavery_3", pchar))),
						StringFromKey("Common_Slavery_8", LinkRandPhrase(
								StringFromKey("Common_Slavery_5", pchar),
								StringFromKey("Common_Slavery_6", pchar),
								StringFromKey("Common_Slavery_7", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Slavery_11", RandPhraseSimple(
								StringFromKey("Common_Slavery_9"),
								StringFromKey("Common_Slavery_10"))),
						StringFromKey("Common_Slavery_14", RandPhraseSimple(
								StringFromKey("Common_Slavery_12"),
								StringFromKey("Common_Slavery_13"))));
				link.l1.go = "fight";
				break;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = StringFromKey("Common_Slavery_15");
				link.l1 = StringFromKey("Common_Slavery_16");
				link.l1.go = "fight";
				break;
			}
			if (ChangeCharacterHunterScore(Pchar, "holhunter", 0) > 12)
			{
				dialog.text = StringFromKey("Common_Slavery_17", pchar);
				link.l1 = StringFromKey("Common_Slavery_18");
				link.l1.go = "fight";
				break;
			}
			if (CheckAttribute(npchar, "protector"))
			{
				dialog.text = StringFromKey("Common_Slavery_19");
				link.l1 = StringFromKey("Common_Slavery_20");
				link.l1.go = "guard";
				link.l2 = StringFromKey("Common_Slavery_21");
				link.l2.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.toPlantator") && !CheckAttribute(pchar, "GenQuest.CaptainComission.toPlantator.done") && CheckCaptainComissionIsPlantator(npchar.location))
			{
				link.l7 = StringFromKey("Common_Slavery_22");
				link.l7.go = "officer_CaptainComission";
			}
			//спрос про живой товар из ГПК
			if (CheckAttribute(pchar, "questTemp.LSC") && or(pchar.questTemp.LSC == "NeedMoneySmugglerLSC", pchar.questTemp.LSC == "SearchSlavesLSC"))
			{
				link.l8 = StringFromKey("Common_Slavery_23");
				link.l8.go = "AskTheSmugglerLSC_1";
			}
			dialog.text = StringFromKey("Common_Slavery_24");
			link.l10 = StringFromKey("Common_Slavery_25");
			link.l10.go = "exit";
		break;

		case "Man_FackYou":
			dialog.text = StringFromKey("Common_Slavery_29", LinkRandPhrase(
						StringFromKey("Common_Slavery_26", pchar),
						StringFromKey("Common_Slavery_27", pchar),
						StringFromKey("Common_Slavery_28", pchar)));
			link.l1 = StringFromKey("Common_Slavery_33", LinkRandPhrase(
						StringFromKey("Common_Slavery_30"),
						StringFromKey("Common_Slavery_31"),
						StringFromKey("Common_Slavery_32")));
			link.l1.go = "fight";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// рабы
		case "plantation_slave":
			if (CheckAttribute(npchar, "CityType") && npchar.CityType == "citizen" && HasSubStr(npchar.id, "Slave_"))
			{
				dialog.text = StringFromKey("Common_Slavery_40", RandPhraseSimple(
							StringFromKey("Common_Slavery_36", RandPhraseSimple(
									StringFromKey("Common_Slavery_34"),
									StringFromKey("Common_Slavery_35"))),
							StringFromKey("Common_Slavery_39", RandPhraseSimple(
									StringFromKey("Common_Slavery_37"),
									StringFromKey("Common_Slavery_38")))));
				link.l1 = StringFromKey("Common_Slavery_43", RandPhraseSimple(
							StringFromKey("Common_Slavery_41"),
							StringFromKey("Common_Slavery_42")));
				link.l1.go = "exit";
			}
		break;

		case "Licence":
			iTemp = GetDaysContinueNationLicence(sti(npchar.nation));
			if (GetCharacterReputation_WithNation(pchar, sti(NPChar.nation)) <= -12)
			{
				PlayerRPGCheck_NationReputation_NotifyFail(sti(NPChar.nation));
				dialog.text = StringFromKey("Common_Slavery_44", pchar);
				link.l1 = StringFromKey("Common_Slavery_47", RandPhraseSimple(
							StringFromKey("Common_Slavery_45"),
							StringFromKey("Common_Slavery_46")));
				link.l1.go = "fight";
				break;
			}
			if (iTemp == -1)
			{
				dialog.text = StringFromKey("Common_Slavery_48", pchar);
				link.l1 = StringFromKey("Common_Slavery_51", RandPhraseSimple(
							StringFromKey("Common_Slavery_49"),
							StringFromKey("Common_Slavery_50")));
				link.l1.go = "fight";
				TakeNationLicence(sti(npchar.nation));
				break;
			}
			dialog.text = StringFromKey("Common_Slavery_52");
			link.l1 = StringFromKey("Common_Slavery_53");
			link.l1.go = "plantation_exit";
		break;

		case "PegYou":
			dialog.text = StringFromKey("Common_Slavery_54", pchar, NationNameInstrumental(sti(GetBaseHeroNation())));
			link.l1 = StringFromKey("Common_Slavery_55");
			link.l1.go = "fight";
			if (CheckAttribute(NPChar, "IWantAskYou")) //HardCoffee ref exp
			{
				DeleteAttribute(NPChar, "IWantAskYou");
				if (isDay()) AddCharacterExpToSkill(pchar, SKILL_SNEAK, 20.0);
				else  AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40.0);
			}
		break;

		case "NotPegYou":
			dialog.text = StringFromKey("Common_Slavery_56");
			link.l1 = StringFromKey("Common_Slavery_57");
			link.l1.go = "plantation_exit";
			LAi_TemporaryBlindGuards();
			if (CheckAttribute(NPChar, "IWantAskYou")) //HardCoffee ref exp
			{
				DeleteAttribute(NPChar, "IWantAskYou");
				if (isDay()) AddCharacterExpToSkill(pchar, SKILL_SNEAK, 40.0);
				else  AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80.0);
			}
		break;

		case "plantation_exit":
			DialogExit();
			NextDiag.CurrentNode = "plantation_repeat";
		break;

		case "plantation_repeat":
			LAi_TemporaryBlindGuards();
			dialog.text = StringFromKey("Common_Slavery_58");
			link.l1 = "...";
			link.l1.go = "plantation_exit";
		break;

		// диалоги с управляющим на плантации\рудниках по квесту CaptainComission
		case "officer_CaptainComission":
			dialog.text = StringFromKey("Common_Slavery_59");
			link.l1 = StringFromKey("Common_Slavery_60");
			link.l1.go = "CaptainComission_10_3";
			pchar.GenQuest.CaptainComission.toPlantator.done = true;
		break;
		case "CaptainComission_10_3":
			dialog.text = StringFromKey("Common_Slavery_61");
			link.l1 = StringFromKey("Common_Slavery_62", pchar, pchar.GenQuest.CaptainComission.SlaveName);
			link.l1.go = "CaptainComission_10_4";
		break;
		case "CaptainComission_10_4":
			if (rand(1) == 0)
			{
				dialog.text = StringFromKey("Common_Slavery_63");
				link.l1 = StringFromKey("Common_Slavery_64");
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if (rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = StringFromKey("Common_Slavery_65");
					link.l1 = StringFromKey("Common_Slavery_66");
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = StringFromKey("Common_Slavery_67");
					link.l1 = StringFromKey("Common_Slavery_68");
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		case "CaptainComission_11":
			dialog.text = StringFromKey("Common_Slavery_69");
			link.l1 = StringFromKey("Common_Slavery_70");
			link.l1.go = "CaptainComission_11_1";
		break;
		case "CaptainComission_11_1":
			dialog.text = StringFromKey("Common_Slavery_71");
			if (sti(pchar.money) >= 150000)
			{
				link.l1 = StringFromKey("Common_Slavery_72");
				link.l1.go = "CaptainComission_14";
			}
			link.l2 = StringFromKey("Common_Slavery_73");
			link.l2.go = "CaptainComission_15";
		break;
		case "CaptainComission_12":
			dialog.text = StringFromKey("Common_Slavery_74");
			link.l1 = StringFromKey("Common_Slavery_75");
			link.l1.go = "CaptainComission_12_1";
		break;
		case "CaptainComission_12_1":
			dialog.text = StringFromKey("Common_Slavery_76");
			if (sti(pchar.money) >= 200000)
			{
				link.l1 = StringFromKey("Common_Slavery_77");
				link.l1.go = "CaptainComission_16";
			}
			link.l2 = StringFromKey("Common_Slavery_78");
			link.l2.go = "CaptainComission_15";
		break;
		case "CaptainComission_13":
			dialog.text = StringFromKey("Common_Slavery_79");
			if (sti(pchar.money) >= 15000)
			{
				link.l1 = StringFromKey("Common_Slavery_80");
				link.l1.go = "CaptainComission_17";
			}
			link.l2 = StringFromKey("Common_Slavery_81");
			link.l2.go = "CaptainComission_15";
		break;
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = StringFromKey("Common_Slavery_82");
			link.l1 = StringFromKey("Common_Slavery_83");
			link.l1.go = "CaptainComission_14_1";
		break;
		case "CaptainComission_14_1":
			dialog.text = StringFromKey("Common_Slavery_84");
			link.l1 = StringFromKey("Common_Slavery_85");
			link.l1.go = "CaptainComission_14_1End";
		break;
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.plantatorId = npchar.id;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		case "CaptainComission_15":
			dialog.text = StringFromKey("Common_Slavery_86");
			link.l1 = StringFromKey("Common_Slavery_87");
			link.l1.go = "CaptainComission_15_1";
		break;
		case "CaptainComission_15_1":
			dialog.text = StringFromKey("Common_Slavery_88");
			link.l1 = StringFromKey("Common_Slavery_89");
			link.l1.go = "CaptainComission_15_1End";
		break;
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			PrepareCaptainComissionSlaveEscape(sti(npchar.nation));
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.plantatorId = npchar.id;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		case "CaptainComission_16":
			dialog.text = StringFromKey("Common_Slavery_90");
			link.l1 = StringFromKey("Common_Slavery_91");
			link.l1.go = "CaptainComission_16_1";
		break;
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = StringFromKey("Common_Slavery_92");
			link.l1 = StringFromKey("Common_Slavery_93");
			link.l1.go = "CaptainComission_16_1End";
		break;
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.plantatorId = npchar.id;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		case "CaptainComission_17":
			dialog.text = StringFromKey("Common_Slavery_94");
			link.l1 = StringFromKey("Common_Slavery_95");
			link.l1.go = "CaptainComission_17_1";
		break;
		case "CaptainComission_17_1":
			dialog.text = StringFromKey("Common_Slavery_96");
			link.l1 = StringFromKey("Common_Slavery_97");
			link.l1.go = "CaptainComission_17_1End";
		break;
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.plantatorId = npchar.id;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		case "CaptainComission_18":
			dialog.text = StringFromKey("Common_Slavery_98");
			link.l1 = StringFromKey("Common_Slavery_99");
			link.l1.go = "exit";
		break;
		case "CaptainComission_19":
			dialog.text = StringFromKey("Common_Slavery_100");
			link.l1 = StringFromKey("Common_Slavery_101");
			link.l1.go = "exit";
		break;

		case "AskTheSmugglerLSC_1":
			dialog.text = StringFromKey("Common_Slavery_102");
			link.l1 = StringFromKey("Common_Slavery_103");
			if (npchar.location == "Mine_residence") link.l1.go = "SearchSlavesLSC_2";
			else link.l1.go = "AskTheSmugglerLSC_2";
		break;
		case "AskTheSmugglerLSC_2":
			dialog.text = StringFromKey("Common_Slavery_104");
			link.l1 = StringFromKey("Common_Slavery_105");
			link.l1.go = "exit";
			AddQuestRecord("ISS_PoorsMurder", "31");
			pchar.questTemp.LSC = "SearchSlavesLSC";
		break;

	}
}

bool CheckCaptainComissionIsPlantator(string location)
{
	switch (pchar.GenQuest.CaptainComission.toPlantator)
	{
		case "Bridgetown_Plantation":
			if (location == "Bridgetown_Plantation_Sp2") return true;
		break;
		case "Villemstad_Plantation":
			if (location == "Villemstad_Plantation_Sp2") return true;
		break;
		case "FortOrange_Mine":
			if (location == "Mine_residence") return true;
		break;
	}
	return false;
}

void PrepareCaptainComissionSlaveEscape(int nation)
{
	switch (pchar.GenQuest.CaptainComission.toPlantator)
	{
		case "Bridgetown_Plantation":
			pchar.GenQuest.CaptainComission.SlaveEscapeLocation = "Mayak2";
			pchar.GenQuest.CaptainComission.SlaveEscapeReload = "reload2_back";
		break;
		case "Villemstad_Plantation":
			pchar.GenQuest.CaptainComission.SlaveEscapeLocation = "Shore23";
			pchar.GenQuest.CaptainComission.SlaveEscapeReload = "reload2_back";
		break;
		case "FortOrange_Mine":
			pchar.GenQuest.CaptainComission.SlaveEscapeLocation = "Shore36";
			pchar.GenQuest.CaptainComission.SlaveEscapeReload = "reload1";
		break;
	}
	pchar.GenQuest.CaptainComission.SlaveEscapePlantationNation = nation;
}
// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// <-- вызов диалога по городам

	ref offref, sld;
	int i, cn;
	int qty;
	int iSumm;

	// выкуп колонии -->
	int colony_money;
	string attrLoc = Dialog.CurrentNode;
	if (HasSubStr(attrLoc, "CityGive_"))
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.quest.CityIdx = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "ColonyGive";
	}
	// <-- выкуп колонии

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		//			AddDialogExitQuest("MainHeroFightModeOff"); // не актуально
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "First time":
			NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Governor_4", LinkRandPhrase(
								StringFromKey("Common_Governor_1"),
								StringFromKey("Common_Governor_2"),
								StringFromKey("Common_Governor_3", pchar))),
						StringFromKey("Common_Governor_8", LinkRandPhrase(
								StringFromKey("Common_Governor_5", pchar),
								StringFromKey("Common_Governor_6", pchar),
								StringFromKey("Common_Governor_7", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Governor_11", RandPhraseSimple(
								StringFromKey("Common_Governor_9"),
								StringFromKey("Common_Governor_10"))),
						StringFromKey("Common_Governor_14", RandPhraseSimple(
								StringFromKey("Common_Governor_12"),
								StringFromKey("Common_Governor_13"))));
				link.l1.go = "fight";
				break;
			}

			if (npchar.quest.meeting == "0")
			{
				dialog.text = StringFromKey("Common_Governor_15", GetFullName(npchar), NationNameGenitive(sti(NPChar.nation)), NationKingsName(npchar), GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_Governor_16", GetFullName(pchar));
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = StringFromKey("Common_Governor_19", RandPhraseSimple(
							StringFromKey("Common_Governor_17", NationNameGenitive(sti(NPChar.nation))),
							StringFromKey("Common_Governor_18", GetAddress_Form(NPChar))));
				link.l1 = StringFromKey("Common_Governor_20", NationNameGenitive(sti(NPChar.nation)));
				link.l1.go = "work";
				link.l2 = StringFromKey("Common_Governor_21");
				link.l2.go = "quests"; // файл нации
				link.l10 = StringFromKey("Common_Governor_22");
				link.l10.go = "exit";
			}
		break;

		case "node_1":
			dialog.text = StringFromKey("Common_Governor_23");
			link.l1 = StringFromKey("Common_Governor_24", NationNameGenitive(sti(NPChar.nation)));
			link.l1.go = "work";
			link.l2 = StringFromKey("Common_Governor_25");
			link.l2.go = "quests";
			link.l10 = StringFromKey("Common_Governor_26", GetAddress_FormToNPC(NPChar));
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = StringFromKey("Common_Governor_27");
			link.l1 = StringFromKey("Common_Governor_28", pchar);
			link.l1.go = "exit";
		break;

		case "work":
			if (!CheckCharacterItem(Pchar, "patent_" + NationShortName(sti(NPChar.nation))) || !CheckAttribute(pchar, "EquipedPatentId"))
			{
				dialog.text = StringFromKey("Common_Governor_29", GetAddress_Form(NPChar), NationKingsName(npchar));
				link.l1 = StringFromKey("Common_Governor_30", NationNameGenitive(sti(NPChar.nation)));
				link.l1.go = "exit";
			}
			else
			{
				// даем задание
				// звание подрасло
				if (isReadyToNextTitle(sti(NPChar.nation)))
				{
					Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0;
					Items[sti(pchar.EquipedPatentId)].TitulCur = sti(Items[sti(pchar.EquipedPatentId)].TitulCur) + 1;

					dialog.text = StringFromKey("Common_Governor_31", GetAddress_Form(NPChar), NationKingsName(npchar), GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)), NationNameGenitive(sti(NPChar.nation)));
					link.l1 = StringFromKey("Common_Governor_32", NationKingsCrown(npchar));
					link.l1.go = "exit";
					break;
				}
				// даем задание
				dialog.text = StringFromKey("Common_Governor_36", LinkRandPhrase(
							StringFromKey("Common_Governor_33", GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))),
							StringFromKey("Common_Governor_34", GetAddress_Form(NPChar)),
							StringFromKey("Common_Governor_35")));

				//GetAddress_Form(NPChar)+", я рад, что "+ GetSexPhrase("такой бравый","такая бравая") +" "+GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur))+" на службе " + NationKingsName(npchar) + ".";
				if (pchar.questTemp.NationQuest == "")
				{
					if (pchar.questTemp.piratesLine == "begin" || pchar.questTemp.piratesLine == "over" || pchar.questTemp.piratesLine == "waiting_Q8" || pchar.questTemp.LSC == "over")
					{
						link.l1 = StringFromKey("Common_Governor_37");
						link.l1.go = "work_1";
						if (!bWorldAlivePause && pchar.questTemp.State == "") //eddy. только, если не проходил линейку.
						{
							link.l1.go = "onlyGenWork_Alter";
						}
					}
					else
					{
						link.l1 = StringFromKey("Common_Governor_38");
						link.l1.go = "onlyGenWork_2";
					}
				}
				else
				{
					if (pchar.questTemp.NationQuest == NPChar.nation)
					{
						link.l1 = StringFromKey("Common_Governor_41", RandPhraseSimple(
									StringFromKey("Common_Governor_39", pchar),
									StringFromKey("Common_Governor_40")));
						link.l1.go = "work_1";
					}
					else
					{
						// линейкам - фиг
						link.l1 = StringFromKey("Common_Governor_42");
						link.l1.go = "onlyGenWork_1";
					}
				}

				// Сдача города -->
				if (isHeroOwnCity(false))
				{
					Link.l2 = StringFromKey("Common_Governor_43", XI_ConvertString(GetNationNameByType(sti(NPChar.nation)) + "Gen"));
					Link.l2.go = "colony_capture";
				}
				// Сдача города <--
				link.l9 = StringFromKey("Common_Governor_46", RandPhraseSimple(
							StringFromKey("Common_Governor_44"),
							StringFromKey("Common_Governor_45", GetAddress_FormToNPC(NPChar))));
				link.l9.go = "exit";
			}
		break;

		case "onlyGenWork_1":
			dialog.text = StringFromKey("Common_Governor_47", NationNameGenitive(sti(pchar.questTemp.NationQuest)));
			link.l1 = StringFromKey("Common_Governor_48");
			link.l1.go = "exit";
		break;

		case "onlyGenWork_2":
			dialog.text = StringFromKey("Common_Governor_49", NationNameGenitive(sti(npchar.nation)));
			link.l1 = StringFromKey("Common_Governor_50");
			link.l1.go = "exit";
		break;

		case "onlyGenWork_Alter":
			dialog.text = StringFromKey("Common_Governor_51");
			link.l1 = StringFromKey("Common_Governor_52");
			link.l1.go = "exit";
		break;

		/////Награда за захваченную колонию.
		case "colony_capture":
			dialog.text = StringFromKey("Common_Governor_53");
			for (i = 0; i < MAX_COLONIES; i++)
			{
				if (sti(colonies[i].HeroOwn) == true)
				{
					sld = GetFortCommander(colonies[i].id);
					attrLoc = "l" + i;
					Link.(attrLoc) = GetCityName(colonies[i].id);
					Link.(attrLoc).go = "CityGive_" + i;
				}
			}
			link.l99 = StringFromKey("Common_Governor_54", pchar);
			link.l99.go = "exit";
		break;

		case "ColonyGive":
			i = sti(NPChar.quest.CityIdx);
			sld = GetFortCommander(colonies[i].id);
			colony_money = TWN_CityCost(colonies[i].id) / 50;  // те *1000 в итоге
			TWN_RealeseForMoney(colonies[i].id, false);
			dialog.text = StringFromKey("Common_Governor_55", GetAddress_FormTitle(sti(NPChar.nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur)), FindMoneyString(colony_money), NationNameInstrumental(sti(NPChar.nation)));
			link.l1 = StringFromKey("Common_Governor_56", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";

			ReOpenQuestHeader("Gen_CityCapture");
			AddQuestRecord("Gen_CityCapture", "t8");
			AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("Gen_CityCapture", "sCity", GetCityName(colonies[i].id));
			AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(GetNationNameByType(sti(NPChar.nation)) + "Gen"));

			//Выдача накопленных налогов
			if (CheckAttribute(&colonies[i], "OfficerIdx"))
			{
				int iTemp, iTax, iFortValue;
				ref Gover = GetCharacter(sti(colonies[i].OfficerIdx));
				iTemp = GetNpcQuestPastDayParam(Gover, "StartTaxDate");
				iTax = makeint((GetCharacterSkillSimple(Gover, SKILL_COMMERCE) + GetCharacterSkillSimple(Gover, SKILL_LEADERSHIP)) / 2);
				if (CheckAttribute(&colonies[i], "FortValue")) iFortValue = sti(colonies[i].FortValue);
				else iFortValue = 20;
				Gover.Gover_Tax_Sum = iFortValue * iTax * iTemp;
				AddTaxes(sti(Gover.Gover_Tax_Sum));
			}

			AddMoneyToCharacter(PChar, colony_money);
			AddTitleNextRate(sti(NPChar.nation), 1);  // счетчик звания
			ChangeCharacterNationReputation(Pchar, sti(NPChar.nation), 10);
			PChar.questTemp.DontNullDeposit = true;    // чтоб не нулили ростовщика
			SetCaptureTownByNation(colonies[i].id, sti(NPChar.nation));
		break;

		//*************************** Квест "Сопровождение флейта "Орион"" **********************        
		case "Andre_Abel_Quest_Hol_Gov_Node_1":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Governor_60", LinkRandPhrase(
								StringFromKey("Common_Governor_57"),
								StringFromKey("Common_Governor_58"),
								StringFromKey("Common_Governor_59", pchar))),
						StringFromKey("Common_Governor_64", LinkRandPhrase(
								StringFromKey("Common_Governor_61", pchar),
								StringFromKey("Common_Governor_62", pchar),
								StringFromKey("Common_Governor_63", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Governor_67", RandPhraseSimple(
								StringFromKey("Common_Governor_65"),
								StringFromKey("Common_Governor_66"))),
						StringFromKey("Common_Governor_70", RandPhraseSimple(
								StringFromKey("Common_Governor_68"),
								StringFromKey("Common_Governor_69"))));
				link.l1.go = "fight";
				NextDiag.TempNode = "Andre_Abel_Quest_Hol_Gov_Node_1";
				break;
			}
			if (pchar.location == "Villemstad_townhall2")
			{
				dialog.text = StringFromKey("Common_Governor_71");
				link.l1 = StringFromKey("Common_Governor_72", pchar);
				link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_2";
				TakeItemFromCharacter(PChar, "Andre_Abel_Letter_1");
				Log_TestInfo("Письмо отдано генерал-губернатору Кюрасао.");
				PChar.Quest.Andre_Abel_Quest_Curasao_10Days_Left.over = "yes";
			}
			else
			{
				dialog.text = StringFromKey("Common_Governor_73", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_Governor_74", GetAddress_FormToNPC(NPChar));
				link.l1.go = "exit";
				NextDiag.TempNode = "Andre_Abel_Quest_Hol_Gov_Node_1";
			}
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_2":
			dialog.text = StringFromKey("Common_Governor_75");
			link.l1 = StringFromKey("Common_Governor_76");
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_3";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_3":
			dialog.text = StringFromKey("Common_Governor_77", pchar);
			link.l1 = StringFromKey("Common_Governor_78", pchar);
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_4";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_4":
			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");

			dialog.text = StringFromKey("Common_Governor_79", pchar);

			link.l1 = StringFromKey("Common_Governor_80", pchar);
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_7";
			link.l2 = StringFromKey("Common_Governor_81");
			link.l2.go = "Andre_Abel_Quest_Hol_Gov_Node_5";
			link.l3 = StringFromKey("Common_Governor_82", pchar);
			link.l3.go = "Andre_Abel_Quest_Hol_Gov_Node_9";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_5":
			dialog.text = StringFromKey("Common_Governor_83", pchar);
			link.l1 = StringFromKey("Common_Governor_84");
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_6";
			ChangeCharacterReputation(pchar, -10);
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetFightMode(PChar, true);
			Flag_PIRATE();
			LAi_SetImmortal(CharacterFromID("Andre_Abel_Quest_Guard_1"), false);
			LAi_SetActorType(CharacterFromID("Andre_Abel_Quest_Guard_1"));
			LAi_ActorAttack(CharacterFromID("Andre_Abel_Quest_Guard_1"), PChar, "");
			//HardCoffee рефакторинг диалогов с Морганом
			//QuestSetCurrentNode("Henry Morgan", "Andre_Abel_Quest_Morgan_Dialog_16");
			pchar.QuestTemp.AndreAbelQuest = "GoTo_MorganFight";
			LAi_Group_Attack(PChar, CharacterFromID("hol_guber"));
			AddQuestRecord("Andre_Abel_Quest", "16");
			AddQuestUserData("Andre_Abel_Quest", "sText", StringFromKey("Common_Governor_105"));

			SetFunctionTimerCondition("Andre_Abel_Quest_Curacao_Townhall_Clear", 0, 0, 1, false);

			AddLandQuestMark_Main(CharacterFromId("Henry Morgan"), "Andre_Abel_Quest");
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_7":
			dialog.text = StringFromKey("Common_Governor_85", pchar);
			link.l1 = StringFromKey("Common_Governor_86");
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_8";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoFunctionReloadToLocation("Villemstad_prison", "goto", "goto9", "Andre_Abel_Quest_In_Prison");
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_9":
			iSumm = sti(PChar.rank) * 20000;
			dialog.text = StringFromKey("Common_Governor_87", FindMoneyString(iSumm));
			if (sti(PChar.money) >= iSumm)
			{
				link.l1 = StringFromKey("Common_Governor_88", pchar);
				link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_10";
			}
			link.l2 = StringFromKey("Common_Governor_89", pchar);
			link.l2.go = "Andre_Abel_Quest_Hol_Gov_Node_Allure";
			link.l3 = StringFromKey("Common_Governor_90");
			link.l3.go = "Andre_Abel_Quest_Hol_Gov_Node_5";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_10":
			iSumm = sti(PChar.rank) * 20000;
			AddMoneyToCharacter(PChar, -iSumm);
			dialog.text = StringFromKey("Common_Governor_91");
			link.l1 = StringFromKey("Common_Governor_92");
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_11";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_11":
			DialogExit();
			NextDiag.CurrentNode = "Andre_Abel_Quest_Hol_Gov_Node_GetOutRepeat";

			//HardCoffee рефакторинг диалогов с Морганом
			//QuestSetCurrentNode("Henry Morgan", "Andre_Abel_Quest_Morgan_Dialog_16");
			pchar.QuestTemp.AndreAbelQuest = "GoTo_MorganMoney";
			AddQuestRecord("Andre_Abel_Quest", "16");
			AddQuestUserData("Andre_Abel_Quest", "sText", StringFromKey("Common_Governor_106"));

			SetFunctionTimerCondition("Andre_Abel_Quest_Curacao_Townhall_Clear", 0, 0, 1, false);

			AddLandQuestMark_Main(CharacterFromId("Henry Morgan"), "Andre_Abel_Quest");
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_GetOutRepeat":
			dialog.text = StringFromKey("Common_Governor_93");
			link.l1 = StringFromKey("Common_Governor_94");
			link.l1.go = "Exit_Andre_Abel_Quest_Hol_Gov_Node_GetOutRepeat";
		break;

		case "Exit_Andre_Abel_Quest_Hol_Gov_Node_GetOutRepeat":
			DialogExit();
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_Allure":
			dialog.text = StringFromKey("Common_Governor_95");
			link.l1 = StringFromKey("Common_Governor_96", pchar);
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_Allure_1";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_Allure_1":
			dialog.text = StringFromKey("Common_Governor_97");
			link.l1 = StringFromKey("Common_Governor_98", pchar);
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_Allure_2";
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_Allure_2":
			dialog.text = StringFromKey("Common_Governor_99");
			link.l1 = StringFromKey("Common_Governor_100", pchar);
			if (PlayerRPGCheck_SPECIAL(SPECIAL_C, 8))
			{
				link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_AllureSuccess";
			}
			else
			{
				link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_AllureFail";
			}
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_AllureSuccess":
			dialog.text = StringFromKey("Common_Governor_101");
			link.l1 = StringFromKey("Common_Governor_102");
			link.l1.go = "Exit_Andre_Abel_Quest_Hol_Gov_Node_AllureSuccess";
		break;

		case "Exit_Andre_Abel_Quest_Hol_Gov_Node_AllureSuccess":
			DialogExit();
			NextDiag.CurrentNode = "Andre_Abel_Quest_Hol_Gov_Node_GetOutRepeat";

			pchar.QuestTemp.AndreAbelQuest = "GoTo_MorganAllure";
			AddQuestRecord("Andre_Abel_Quest", "16");
			AddQuestUserData("Andre_Abel_Quest", "sText", StringFromKey("Common_Governor_107"));

			SetFunctionTimerCondition("Andre_Abel_Quest_Curacao_Townhall_Clear", 0, 0, 1, false);

			AddLandQuestMark_Main(CharacterFromId("Henry Morgan"), "Andre_Abel_Quest");
		break;

		case "Andre_Abel_Quest_Hol_Gov_Node_AllureFail":
			dialog.text = StringFromKey("Common_Governor_103", pchar);
			link.l1 = StringFromKey("Common_Governor_104");
			link.l1.go = "Andre_Abel_Quest_Hol_Gov_Node_8";
		break;
	}
}

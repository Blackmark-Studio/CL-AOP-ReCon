void ProcessDialogEvent()
{
	ref NPChar, her;
	aref Link, NextDiag;
	bool bOk = false;
	bool bOk2;

	int i, Sum, nRel, nDay, iChurchQuest2_Summ;
	ref sld;

	// Церковный квест № 2 -->
	if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra"))
	{
		iChurchQuest2_Summ = sti(PChar.rank) * 100 + (rand(3) + 1) * 100;
		PChar.GenQuest.ChurchQuest_2.Summ_To_Contra = sti(iChurchQuest2_Summ);
	}
	// <-- Церковный квест № 2

	string sColony;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	if (!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}

	//тереть нафиг аттрибут при прошествии дней (navy fix)
	if (CheckAttribute(pchar, "GenQuest.contraTravel.days") && GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
	{
		DeleteAttribute(pchar, "GenQuest.contraTravel");
		CloseQuestHeader("Gen_ContrabandTravel");
	}

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Smuggling_exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			PlaceSmugglersOnShore(Pchar.quest.contraband.CurrentPlace);
			Pchar.quest.Contraband.active = true;
			pchar.GenQuest.Contraband.GuardNation = npchar.nation;

			ReOpenQuestHeader("Gen_Contraband");
			if (GetIslandNameByCity(npchar.city) == "Mein")
			{
				AddQuestRecord("Gen_Contraband", "t1_1");
			}
			else
			{
				AddQuestRecord("Gen_Contraband", "t1");
				AddQuestUserData("Gen_Contraband", "sIsland", XI_ConvertString(GetIslandNameByCity(npchar.city)));
			}
			AddQuestUserData("Gen_Contraband", "sLoc", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));

			DialogExit();
		break;

		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Smuggler_Agent_dialog_4", LinkRandPhrase(
								StringFromKey("Smuggler_Agent_dialog_1"),
								StringFromKey("Smuggler_Agent_dialog_2"),
								StringFromKey("Smuggler_Agent_dialog_3", pchar))),
						StringFromKey("Smuggler_Agent_dialog_8", LinkRandPhrase(
								StringFromKey("Smuggler_Agent_dialog_5", pchar),
								StringFromKey("Smuggler_Agent_dialog_6", pchar),
								StringFromKey("Smuggler_Agent_dialog_7", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Smuggler_Agent_dialog_11", RandPhraseSimple(
								StringFromKey("Smuggler_Agent_dialog_9"),
								StringFromKey("Smuggler_Agent_dialog_10"))),
						StringFromKey("Smuggler_Agent_dialog_14", RandPhraseSimple(
								StringFromKey("Smuggler_Agent_dialog_12", GetWorkTypeOfMan(npchar, "")),
								StringFromKey("Smuggler_Agent_dialog_13", GetWorkTypeOfMan(npchar, "")))));
				link.l1.go = "exit";
				break;
			}

			if (sti(Pchar.Rank) > 4 && !CheckAttribute(pchar, "questTemp.Headhunter"))    // && Pchar.BaseNation == PIRATE теперь все могут брать. Konstrush
			{
				dialog.text = StringFromKey("Smuggler_Agent_dialog_15", pchar);
				link.l1 = StringFromKey("Smuggler_Agent_dialog_16");
				link.l1.go = "Give_vector";
				break;
			}

			if (NPChar.quest.meeting == "0")
			{
				Dialog.Text = StringFromKey("Smuggler_Agent_dialog_17");
				Link.l1 = StringFromKey("Smuggler_Agent_dialog_18", GetFullName(pchar));
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				if (CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 1)
				{
					if (!CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakContra"))
					{
						pchar.GenQuest.CaptainComission.SpeakContra = true;
						dialog.text = StringFromKey("Smuggler_Agent_dialog_19", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.Name);
						link.l1 = StringFromKey("Smuggler_Agent_dialog_20", pchar.GenQuest.CaptainComission.Name);
						link.l1.go = "CapComission_1";
						break;
					}
					else
					{
						dialog.text = StringFromKey("Smuggler_Agent_dialog_21");
						link.l1 = StringFromKey("Smuggler_Agent_dialog_22");
						link.l1.go = "exit";
						break;
					}
				}

				if (pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
				{
					dialog.text = StringFromKey("Smuggler_Agent_dialog_23");
					link.l1 = StringFromKey("Smuggler_Agent_dialog_24");
					link.l1.go = "exit";
					break;
				}

				Dialog.Text = StringFromKey("Smuggler_Agent_dialog_25");
				if (LAi_group_GetPlayerAlarm() > 0)
				{
					Dialog.Text = StringFromKey("Smuggler_Agent_dialog_28", RandPhraseSimple(
								StringFromKey("Smuggler_Agent_dialog_26", pchar),
								StringFromKey("Smuggler_Agent_dialog_27")));
				}
				if (HaveContrabandGoods(PChar))
				{
					Link.l1 = StringFromKey("Smuggler_Agent_dialog_29", pchar);
					Link.l1.go = "Meeting_3";
				}

				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
					Link.l2 = StringFromKey("Smuggler_Agent_dialog_30");
				else
					Link.l2 = StringFromKey("Smuggler_Agent_dialog_31");
				Link.l2.go = "Travel";
				if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakSmuggler"))
				{
					if ((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					{
						link.l3 = StringFromKey("Smuggler_Agent_dialog_32");
						link.l3.go = "SM_ShipLetters_1";
					}
				}
				// Церковный генератор №2 -->
				if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
				{
					Link.l4 = StringFromKey("Smuggler_Agent_dialog_33");
					Link.l4.go = "Contra_GenQuest_Church_2_1";
				}

				if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
				{
					Link.l5 = StringFromKey("Smuggler_Agent_dialog_34", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen"));
					Link.l5.go = "Contra_GenQuest_Church_2_Contra2_1";
				}
				// <-- Церковный генератор №2

				////////////////////////////////////////////////////////
				//zagolski. начальный квест пирата
				if (CheckAttribute(pchar, "questTemp.pirateStartQuest") && pchar.questTemp.pirateStartQuest == "2" && GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal && npchar.city != pchar.questTemp.pirateStartQuest.City)
				{
					link.l4 = StringFromKey("Smuggler_Agent_dialog_35");
					link.l4.go = "pirateStartQuest_Smuggler";
				}
				//спрос про живой товар из ГПК
				if (CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "NeedMoneySmugglerLSC" && sti(pchar.money) >= 5000)
				{
					link.l5 = StringFromKey("Smuggler_Agent_dialog_36");
					link.l5.go = "AskTheSmugglerLSC_5";
				}
				Link.l7 = StringFromKey("Smuggler_Agent_dialog_37");
				Link.l7.go = "Exit";
			}
			//спрос про живой товар из ГПК
			if (CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "AskTheSmugglerLSC")
			{
				link.l5 = StringFromKey("Smuggler_Agent_dialog_38");
				link.l5.go = "AskTheSmugglerLSC_1";
			}
		break;

		case "CapComission_1":
			if (pchar.GenQuest.CaptainComission.variant == "A2")
			{
				dialog.text = StringFromKey("Smuggler_Agent_dialog_39");
				link.l1 = StringFromKey("Smuggler_Agent_dialog_40", pchar.GenQuest.CaptainComission.Name);
				link.l1.go = "CapComission_4";
			}
			if (pchar.GenQuest.CaptainComission.variant == "A3")
			{
				dialog.text = StringFromKey("Smuggler_Agent_dialog_41");
				link.l1 = StringFromKey("Smuggler_Agent_dialog_42");
				link.l1.go = "CapComission_2";
			}
		break;

		case "CapComission_2":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_43", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name"))));
			link.l1 = StringFromKey("Smuggler_Agent_dialog_44", pchar.GenQuest.CaptainComission.Name);
			link.l1.go = "CapComission_3";
		break;

		case "CapComission_3":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_45");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_46");
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "38");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim), "Name") + "Acc")));
		break;

		case "CapComission_4":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_47");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_48");
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission2", "19");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		break;

		case "SM_ShipLetters_1":
			pchar.questTemp.different.GiveShipLetters.speakSmuggler = true;
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = StringFromKey("Smuggler_Agent_dialog_49", pchar);
				link.l1 = StringFromKey("Smuggler_Agent_dialog_50");
				link.l1.go = "exit";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = StringFromKey("Smuggler_Agent_dialog_51", FindMoneyString(sti(pchar.questTemp.different.GiveShipLetters.price2)));
					link.l1 = StringFromKey("Smuggler_Agent_dialog_52");
					link.l1.go = "SM_ShipLetters_2";
					link.l2 = StringFromKey("Smuggler_Agent_dialog_53");
					link.l2.go = "SM_ShipLetters_3";
				}
				else
				{
					if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = StringFromKey("Smuggler_Agent_dialog_54", FindMoneyString(sti(pchar.questTemp.different.GiveShipLetters.price3)));
						link.l1 = StringFromKey("Smuggler_Agent_dialog_55");
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = StringFromKey("Smuggler_Agent_dialog_56");
						link.l2.go = "SM_ShipLetters_3";
					}
					if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = StringFromKey("Smuggler_Agent_dialog_57", pchar, FindMoneyString(sti(pchar.questTemp.different.GiveShipLetters.price4)));
						link.l1 = StringFromKey("Smuggler_Agent_dialog_58");
						link.l1.go = "SM_ShipLetters_2";
						link.l2 = StringFromKey("Smuggler_Agent_dialog_59");
						link.l2.go = "SM_ShipLetters_3";
					}
				}
			}
		break;

		case "SM_ShipLetters_2":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_60");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_61");
			link.l1.go = "exit";
		break;

		case "SM_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook");
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if (!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3));
				}
			}
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if (!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4));
				}
			}

			if ((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{
				ChangeCharacterReputation(pchar, -1);
				OfficersReaction("bad");
			}
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "7");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Meeting":
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour") && GetQuestPastDayParam("GenQuest.CaptainComission.GetRumour") < 2)
			{
				if (!CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakContra"))
				{
					pchar.GenQuest.CaptainComission.SpeakContra = true;
					dialog.text = StringFromKey("Smuggler_Agent_dialog_62", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.Name);
					link.l1 = StringFromKey("Smuggler_Agent_dialog_63", pchar.GenQuest.CaptainComission.Name);
					link.l1.go = "CapComission_1";
					break;
				}
				else
				{
					dialog.text = StringFromKey("Smuggler_Agent_dialog_64");
					link.l1 = StringFromKey("Smuggler_Agent_dialog_65");
					link.l1.go = "exit";
					break;
				}
			}

			if (pchar.questTemp.Slavetrader == "FindMayak" && Islands[GetCharacterCurrentIsland(pchar)].id == pchar.questTemp.Slavetrader.EsIsland)
			{
				dialog.text = StringFromKey("Smuggler_Agent_dialog_66");
				link.l1 = StringFromKey("Smuggler_Agent_dialog_67");
				link.l1.go = "exit";
				break;
			}

			Dialog.Text = StringFromKey("Smuggler_Agent_dialog_68");
			if (HaveContrabandGoods(PChar))
			{
				Link.l1 = StringFromKey("Smuggler_Agent_dialog_69");
				Link.l1.go = "Meeting_1";
			}
			Link.l2 = StringFromKey("Smuggler_Agent_dialog_70");
			Link.l2.go = "Travel";
			// Церковный генератор №2 -->
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1") && NPChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
			{
				Link.l3 = StringFromKey("Smuggler_Agent_dialog_71");
				Link.l3.go = "Contra_GenQuest_Church_2_1";
			}

			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2") && NPChar.location == PChar.GenQuest.ChurchQuest_2.Contra_Colony + "_tavern")
			{
				Link.l3 = StringFromKey("Smuggler_Agent_dialog_72", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen"));
				Link.l3.go = "Contra_GenQuest_Church_2_Contra2_1";
			}
			// <-- Церковный генератор №2

			////////////////////////////////////////////////////////	
			//zagolski. начальный квест пирата
			if (CheckAttribute(pchar, "questTemp.pirateStartQuest") && pchar.questTemp.pirateStartQuest == "2" && GetArealByCityName(npchar.city) == pchar.questTemp.pirateStartQuest.Areal && npchar.city != pchar.questTemp.pirateStartQuest.City)
			{
				link.l4 = StringFromKey("Smuggler_Agent_dialog_73");
				link.l4.go = "pirateStartQuest_Smuggler";
			}

			Link.l5 = StringFromKey("Smuggler_Agent_dialog_74");
			Link.l5.go = "Exit";
		break;

		////////////////////////////////////////////////////////	
		//zagolski. начальный квест пирата
		case "pirateStartQuest_Smuggler":
			if (!CheckAttribute(pchar, "GenQuest.contraTravel.active") && !CheckAttribute(Pchar, "quest.Contraband.Active"))
			{
				dialog.text = StringFromKey("Smuggler_Agent_dialog_75");
				link.l1 = StringFromKey("Smuggler_Agent_dialog_76");
				link.l1.go = "pirateStartQuest_Smuggler_1";
			}
			else
			{
				dialog.text = StringFromKey("Smuggler_Agent_dialog_77");
				link.l1 = StringFromKey("Smuggler_Agent_dialog_78");
				link.l1.go = "exit";
			}
		break;
		case "pirateStartQuest_Smuggler_1":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_79");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_80");
			link.l1.go = "pirateStartQuest_Smuggler_2";
		break;
		case "pirateStartQuest_Smuggler_2":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_81");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_82");
			link.l1.go = "pirateStartQuest_Smuggler_3";
		break;
		case "pirateStartQuest_Smuggler_3":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_83");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_84");
			link.l1.go = "pirateStartQuest_Smuggler_4";
		break;
		case "pirateStartQuest_Smuggler_4":
			pchar.questTemp.pirateStartQuest.Shore = SelectQuestShoreLocation();
			dialog.text = StringFromKey("Smuggler_Agent_dialog_85", XI_ConvertString(pchar.questTemp.pirateStartQuest.Shore));
			link.l1 = StringFromKey("Smuggler_Agent_dialog_86");
			link.l1.go = "exit";

			pchar.questTemp.pirateStartQuest = "3";
			pchar.questTemp.pirateStartQuest.City2Nation = npchar.nation;
			AddQuestRecord("pSQ", "3");
			AddQuestUserData("pSQ", "sCity2", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City2 + "Gen"));
			AddQuestUserData("pSQ", "sShore", XI_ConvertString(pchar.questTemp.pirateStartQuest.Shore));
			RemoveLandQuestMark_Main(npchar, "pSQ");
			AddLandQuestMark_Main(CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId), "pSQ");

			AddGeometryToLocation(pchar.questTemp.pirateStartQuest.Shore, "smg");
			pchar.quest.pirateStartQuest_Smuggler_fc2.win_condition.l1 = "Location";
			pchar.quest.pirateStartQuest_Smuggler_fc2.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Shore;
			pchar.quest.pirateStartQuest_Smuggler_fc2.function = "pirateStartQuest_Smuggler_fc2";

			SetTimerFunction("pirateStartQuest_Smuggler_RemoveSmugglers", 0, 0, 4);  // через 4 дня всех убрать
		break;
		//--------------------------------------------------

		// Церковный генератор №2 -->
		case "Contra_GenQuest_Church_2_1":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			dialog.text = StringFromKey("Smuggler_Agent_dialog_87");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_88", FindMoneyString(iChurchQuest2_Summ));
			link.l1.go = "Contra_GenQuest_Church_2_2";
		break;

		case "Contra_GenQuest_Church_2_2":
			iChurchQuest2_Summ = PChar.GenQuest.ChurchQuest_2.Summ_To_Contra;
			if (sti(PChar.money) >= iChurchQuest2_Summ)
			{
				dialog.text = StringFromKey("Smuggler_Agent_dialog_89");
				link.l1 = StringFromKey("Smuggler_Agent_dialog_90", pchar);
				link.l1.go = "Contra_GenQuest_Church_2_3";
				AddMOneyToCharacter(PChar, -iChurchQuest2_Summ);
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_1");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.Summ_To_Contra");
				DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.QuestGangJungle");    // стираем старый диалог с бандитами
			}
			else
			{
				dialog.text = StringFromKey("Smuggler_Agent_dialog_91");
				link.l1 = StringFromKey("Smuggler_Agent_dialog_92");
				link.l1.go = "exit";
			}
		break;

		case "Contra_GenQuest_Church_2_3":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_93");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_94", pchar);
			link.l1.go = "Contra_GenQuest_Church_2_4";
		break;

		case "Contra_GenQuest_Church_2_4":
			sColony = SelectNotEnemyColony(npchar);
			dialog.text = StringFromKey("Smuggler_Agent_dialog_95", XI_ConvertString("Colony" + sColony + "Acc"), XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Pre"));
			link.l1 = StringFromKey("Smuggler_Agent_dialog_96");
			link.l1.go = "exit";
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "8");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", "а"));
			AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + sColony + "Acc"));
			AddQuestUserData(sQuestTitle, "sIsland", XI_ConvertString(locations[FindLocation(sColony + "_Town")].IslandID + "Pre"));
			PChar.GenQuest.ChurchQuest_2.AskContra_2 = true;
			PChar.GenQuest.ChurchQuest_2.Contra_Colony = sColony;
		break;

		case "Contra_GenQuest_Church_2_Contra2_1":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_97");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_98", pchar);
			link.l1.go = "Contra_GenQuest_Church_2_Contra2_2";
		break;

		case "Contra_GenQuest_Church_2_Contra2_2":
			string sGenLocation = IslandGetLocationFromType(PChar.GenQuest.ChurchQuest_2.Contra_Colony, "seashore");
			PChar.GenQuest.ChurchQuest_2.QuestGangShore = sGenLocation;
			PChar.GenQuest.ChurchQuest_2.BanditsInShore = true;
			dialog.text = StringFromKey("Smuggler_Agent_dialog_99", XI_ConvertString(sGenLocation + "Pre"));
			link.l1 = StringFromKey("Smuggler_Agent_dialog_100", pchar);
			link.l1.go = "exit";
			SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "9");
			AddQuestUserData(sQuestTitle, "sShore", XI_ConvertString(sGenLocation + "Acc"));
			locations[FindLocation(sGenLocation)].DisableEncounters = true;
			SetFunctionTimerCondition("Church_GenQuest2_TimeIsLeft", 0, 0, 1, false);
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskContra_2");
		break;
		// <-- Церковный генератор №2

		case "Meeting_1":
			Dialog.Text = StringFromKey("Smuggler_Agent_dialog_101");
			Link.l1 = StringFromKey("Smuggler_Agent_dialog_102");
			Link.l1.go = "Meeting_2";
			Link.l2 = StringFromKey("Smuggler_Agent_dialog_103");
			Link.l2.go = "exit";
		break;

		case "Meeting_2":
			Dialog.Text = StringFromKey("Smuggler_Agent_dialog_104");
			Link.l1 = StringFromKey("Smuggler_Agent_dialog_105");
			Link.l1.go = "Meeting_3";
		break;

		case "Meeting_3":
			if (!CanSquadronContraband())
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Smuggler_Agent_dialog_106"),
							StringFromKey("Smuggler_Agent_dialog_107"),
							StringFromKey("Smuggler_Agent_dialog_108", pchar),
							StringFromKey("Smuggler_Agent_dialog_109", pchar), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Smuggler_Agent_dialog_110", pchar),
							StringFromKey("Smuggler_Agent_dialog_111", pchar),
							StringFromKey("Smuggler_Agent_dialog_112", pchar),
							StringFromKey("Smuggler_Agent_dialog_113"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				break;
			}

			if (!CanShipclassContraband())
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Smuggler_Agent_dialog_114", pchar),
							StringFromKey("Smuggler_Agent_dialog_115"),
							StringFromKey("Smuggler_Agent_dialog_116"),
							StringFromKey("Smuggler_Agent_dialog_117", pchar), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Smuggler_Agent_dialog_118", pchar),
							StringFromKey("Smuggler_Agent_dialog_119", pchar),
							StringFromKey("Smuggler_Agent_dialog_120", pchar),
							StringFromKey("Smuggler_Agent_dialog_121"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
				break;
			}
			bOk = CheckAttribute(pchar, "GenQuest.contraTravel.active") && (sti(pchar.GenQuest.contraTravel.active) == true);
			bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
			bool bOk3 = CheckAttribute(Pchar, "questTemp.pirateStartQuest") && (Pchar.questTemp.pirateStartQuest == "3");
			if (bOk)
			{
				if (GetQuestPastDayParam("contraTravel") > sti(PChar.GenQuest.contraTravel.days))
				{
					// просрочка
					DeleteAttribute(PChar, "GenQuest.contraTravel");
					CloseQuestHeader("Gen_ContrabandTravel");
					bOk = false;
				}
			}

			//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = StringFromKey("Smuggler_Agent_dialog_122", pchar);
				Link.l1 = StringFromKey("Smuggler_Agent_dialog_123");
				Link.l1.go = "Exit";
				break;
			}
			//navy <--

			if (bOk || bOk2 || bOk3)
			{
				Dialog.Text = StringFromKey("Smuggler_Agent_dialog_124");
				Link.l1 = StringFromKey("Smuggler_Agent_dialog_125");
				Link.l1.go = "Exit";
			}
			else
			{
				if (npchar.quest.trade_date != lastspeak_date)
				{
					npchar.quest.trade_date = lastspeak_date;

					if (GetPlayerContrabandRelation() > 5)
					{
						Pchar.quest.contraband.CurrentPlace = SelectSmugglingLocation();
						Pchar.quest.contraband.City = NPChar.city;
						if (Pchar.quest.contraband.CurrentPlace != "None")//boal fix
						{
							if (GetPlayerContrabandRelation() >= 70)
							{
								Dialog.Text = StringFromKey("Smuggler_Agent_dialog_126", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));
							}
							else
							{
								Dialog.Text = StringFromKey("Smuggler_Agent_dialog_127", GetConvertStr(Pchar.quest.contraband.CurrentPlace, "LocLables.txt"));
							}
							Link.l1 = StringFromKey("Smuggler_Agent_dialog_128");
							Link.l1.go = "Smuggling_exit";
						}
						else
						{
							//boal fix
							Dialog.Text = StringFromKey("Smuggler_Agent_dialog_129");
							Link.l1 = StringFromKey("Smuggler_Agent_dialog_130");
							Link.l1.go = "Exit";
						}
					}
					else
					{
						Dialog.Text = StringFromKey("Smuggler_Agent_dialog_131");
						Link.l1 = StringFromKey("Smuggler_Agent_dialog_132");
						Link.l1.go = "Exit";
					}
				}
				else
				{
					Dialog.Text = StringFromKey("Smuggler_Agent_dialog_133");
					Link.l1 = StringFromKey("Smuggler_Agent_dialog_134");
					Link.l1.go = "Exit";
				}
			}
		break;
		////////////////////////////////////////////////////////////////////////////////
		//	Корсарское метро
		////////////////////////////////////////////////////////////////////////////////
		case "Travel":
		//navy --> PGG
			if (CheckFreeServiceForNPC(NPChar, "Smugglers") != -1)
			{
				Dialog.Text = StringFromKey("Smuggler_Agent_dialog_135", pchar);
				Link.l1 = StringFromKey("Smuggler_Agent_dialog_136");
				Link.l1.go = "Exit";
				break;
			}
			//navy <--
			//если нет корабля у ГГ и нет компаньонов все ок
			if (sti(pchar.ship.type) == SHIP_NOTUSED && GetCompanionQuantity(pchar) == 1 && GetPassengersQuantity(pchar) == 0)
			{
				//случай если уже была инфа
				if (CheckAttribute(pchar, "GenQuest.contraTravel.active") && sti(pchar.GenQuest.contraTravel.active) == true)
				{
					//платил уже
					if (CheckAttribute(pchar, "GenQuest.contraTravel.payed") && sti(pchar.GenQuest.contraTravel.payed) == true)
					{
						Dialog.Text = StringFromKey("Smuggler_Agent_dialog_137");
						Link.l2 = StringFromKey("Smuggler_Agent_dialog_138");
					}
					//не платил, значит можно запалатить пока не вышел срок.
					else
					{
						if (GetQuestPastDayParam("contraTravel") == sti(PChar.GenQuest.contraTravel.days))
						{
							Dialog.Text = StringFromKey("Smuggler_Agent_dialog_139", pchar);
							Link.l1 = StringFromKey("Smuggler_Agent_dialog_140");
							Link.l1.go = "Travel_pay";
							Link.l3 = StringFromKey("Smuggler_Agent_dialog_141", pchar);
							Link.l3.go = "Travel_abort";
							Link.l2 = StringFromKey("Smuggler_Agent_dialog_142");
						}
						else
						{
							if (GetQuestPastDayParam("contraTravel") < sti(PChar.GenQuest.contraTravel.days))
							{
								Dialog.Text = StringFromKey("Smuggler_Agent_dialog_143");
								Link.l2 = StringFromKey("Smuggler_Agent_dialog_144");
								Link.l1 = StringFromKey("Smuggler_Agent_dialog_145", pchar);
								Link.l1.go = "Travel_abort";
							}
							else // просрочка
							{
								Dialog.Text = StringFromKey("Smuggler_Agent_dialog_146");
								Link.l2 = StringFromKey("Smuggler_Agent_dialog_147");
								DeleteAttribute(PChar, "GenQuest.contraTravel");
								CloseQuestHeader("Gen_ContrabandTravel");
							}
						}
					}
				}
				//если не было договора, обговариваем условия
				else
				{
					nRel = GetPlayerContrabandRelation();
					//если нормальные отношения и количество подстав меньше 20, работаем....
					if (nRel > 0 && Statistic_AddValue(PChar, "contr_TravelKill", 0) < 20)
					{
						//бухта...
						pchar.GenQuest.contraTravel.CurrentPlace = SelectSmugglingLocation();
						aref arTmp; makearef(arTmp, pchar.GenQuest.contraTravel);
						SetSmugglersTravelDestination(arTmp);
						//за сколько доставят 
						pchar.GenQuest.contraTravel.price = (sti(PChar.rank) * 250 + (100 - nRel) * 10 + rand(30) * 20) + sti(arTmp.destination.days) * 100;

						//если метро активно, и нет пассажиров у ГГ, и ещё сегодня не виделись, есть доступная бухта, и ранд ...
						bOk = !bPauseContrabandMetro && CheckNPCQuestDate(npchar, "Travel_Talk") &&
								Pchar.GenQuest.contraTravel.CurrentPlace != "None" && rand(50) < nRel;
						bOk2 = CheckAttribute(Pchar, "quest.Contraband.Active") && (sti(Pchar.quest.Contraband.Active) == true);
						if (bOk && !bOk2)
						{
							nDay = 1;
							SetNPCQuestDate(npchar, "Travel_Talk");
							SaveCurrentQuestDateParam("contraTravel");

							Dialog.Text = StringFromKey("Smuggler_Agent_dialog_148", GetConvertStr(locations[FindLocation(pchar.GenQuest.contraTravel.destination.loc)].id, "LocLables.txt"), XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"), FindMoneyString(sti(pchar.GenQuest.contraTravel.price)), FindDaysString(nDay), GetConvertStr(locations[FindLocation(Pchar.GenQuest.contraTravel.CurrentPlace)].id, "LocLables.txt"));

							pchar.GenQuest.contraTravel.days = nDay;
							Link.l1 = StringFromKey("Smuggler_Agent_dialog_149");
							Link.l1.go = "Travel_agree";
							Link.l2 = StringFromKey("Smuggler_Agent_dialog_150");
						}
						else
						{
							Dialog.Text = StringFromKey("Smuggler_Agent_dialog_151");
							Link.l2 = StringFromKey("Smuggler_Agent_dialog_152");
						}
					}
					//нет, посылаем в сад
					else
					{
						Dialog.Text = StringFromKey("Smuggler_Agent_dialog_153");
						Link.l2 = StringFromKey("Smuggler_Agent_dialog_154");
					}

				}
			}
			//корабль есть, посылаем в сад...
			else
			{
				if (GetPassengersQuantity(pchar) != 0)
				{
					Dialog.Text = StringFromKey("Smuggler_Agent_dialog_155");
					Link.l2 = StringFromKey("Smuggler_Agent_dialog_156", RandSwear());
				}
				else
				{
					Dialog.Text = StringFromKey("Smuggler_Agent_dialog_157");
					Link.l2 = StringFromKey("Smuggler_Agent_dialog_158");
				}
			}
			Link.l2.go = "Exit";
		break;

		//отмена
		case "Travel_abort":
			ChangeContrabandRelation(pchar, -2);
			DeleteAttribute(PChar, "GenQuest.contraTravel");
			CloseQuestHeader("Gen_ContrabandTravel");
			Dialog.Text = StringFromKey("Smuggler_Agent_dialog_159");
			Link.l1 = "";
			Link.l1.go = "Exit";
		break;

		//ГГ согласен ехать
		case "Travel_agree":
			ReOpenQuestHeader("Gen_ContrabandTravel");
			AddQuestRecord("Gen_ContrabandTravel", "1");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Gen_ContrabandTravel", "sLoc", GetConvertStr(pchar.GenQuest.contraTravel.CurrentPlace, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sLocTo", GetConvertStr(pchar.GenQuest.contraTravel.destination.loc, "LocLables.txt"));
			AddQuestUserData("Gen_ContrabandTravel", "sPlaceTo", XI_ConvertString("Colony" + pchar.GenQuest.contraTravel.destination + "Gen"));
			AddQuestUserData("Gen_ContrabandTravel", "sDays", FindDaysString(sti(pchar.GenQuest.contraTravel.days)));
			AddQuestUserData("Gen_ContrabandTravel", "sPrice", FindMoneyString(sti(pchar.GenQuest.contraTravel.price)));

			//активируем квест
			pchar.GenQuest.contraTravel.active = true;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//ГГ согласен платить
		case "Travel_pay":
		//денег хватает?
			Sum = sti(pchar.GenQuest.contraTravel.price);
			if (sti(pchar.money) >= Sum)
			{
				AddMoneyToCharacter(pchar, -1 * Sum);
				//ставим флаг оплаты
				pchar.GenQuest.contraTravel.payed = true;
				Dialog.Text = StringFromKey("Smuggler_Agent_dialog_160");
				Link.l1 = StringFromKey("Smuggler_Agent_dialog_161");
				AddQuestRecord("Gen_ContrabandTravel", "2");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("", "а"));

				//ставим контру
				PlaceSmugglersOnShore(PChar.GenQuest.contraTravel.CurrentPlace);
				//корабль на волнах в бухте....
				Sum = sti(pchar.GenQuest.contraTravel.destination.days);
				sld = GetCharacter(NPC_GenerateCharacter("Abracham_Gray", "pirate_5", "man", "man", 5, PIRATE, Sum + 2, true)); //watch_quest_moment
				//воскресим
				sld.nation = PIRATE;
				SetRandomNameToCharacter(sld);
				SetMerchantShip(sld, rand(GOOD_SILVER));
				SetFantomParamHunter(sld);
				SetCaptanModelByEncType(sld, "pirate");
				SetCharacterShipLocation(sld, PChar.GenQuest.contraTravel.CurrentPlace);

				SetTimerCondition("RemoveTravelSmugglers", 0, 0, 1, false);
			}
			//нет, посылаем в сад...
			else
			{
				Dialog.Text = StringFromKey("Smuggler_Agent_dialog_162");
				Link.l1 = StringFromKey("Smuggler_Agent_dialog_163");
			}
			Link.l1.go = "Exit";
		break;

		case "Give_vector":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_164");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_165");
			link.l1.go = "Give_vector_1";
		break;

		case "Give_vector_1":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_166");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_167");
			link.l1.go = "Give_vector_2";
			link.l2 = StringFromKey("Smuggler_Agent_dialog_168", pchar);
			link.l2.go = "exit_quest";
		break;

		case "Give_vector_2":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_169");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_170");
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "vector_barmen";
			AddQuestRecord("Headhunt", "1_1");
			AddQuestUserData("Headhunt", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			HeadHunter_Smuggler_DelQuestMarks();
			AddLandQuestMark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Headhunt");
			AddMapQuestMark_Major("LeFransua_town", "Headhunt", "");
		break;

		case "exit_quest":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_171");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_172");
			link.l1.go = "exit";
			pchar.questTemp.Headhunter = "end_quest";
			HeadHunter_Smuggler_DelQuestMarks();
		break;

		//спрос про живой товар из ГПК
		case "AskTheSmugglerLSC_1":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_173");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_174");
			link.l1.go = "AskTheSmugglerLSC_2";
			link.l2 = StringFromKey("Smuggler_Agent_dialog_175");
			link.l2.go = "AskTheSmugglerLSC_2";
			link.l3 = StringFromKey("Smuggler_Agent_dialog_176");
			link.l3.go = "AskTheSmugglerLSC_2";
			link.l4 = StringFromKey("Smuggler_Agent_dialog_177");
			link.l4.go = "AskTheSmugglerLSC_2";
		break;
		case "AskTheSmugglerLSC_2":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_178");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_179");
			link.l1.go = "AskTheSmugglerLSC_3";
		break;
		case "AskTheSmugglerLSC_3":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_180", pchar);
			link.l1 = StringFromKey("Smuggler_Agent_dialog_181");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Smuggler_Agent_dialog_182");
			link.l2.go = "AskTheSmugglerLSC_4";
			pchar.questTemp.LSC = "NeedMoneySmugglerLSC";
			if (sti(pchar.money) >= 5000)
			{
				link.l1 = StringFromKey("Smuggler_Agent_dialog_183");
				link.l1.go = "AskTheSmugglerLSC_5";
			}
			ISS_PoorsMurder_FindTizer_Smuggler_RemoveQuestMarks();
		break;
		case "AskTheSmugglerLSC_4":
			AddQuestRecord("ISS_PoorsMurder", "30");
			pchar.questTemp.LSC = "SearchSlavesLSC";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "AskTheSmugglerLSC_5":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_184");
			link.l1 = "...";
			link.l1.go = "AskTheSmugglerLSC_6";
		break;
		case "AskTheSmugglerLSC_6":
			dialog.text = StringFromKey("Smuggler_Agent_dialog_185");
			link.l1 = StringFromKey("Smuggler_Agent_dialog_186");
			link.l1.go = "exit";
			AddQuestRecord("ISS_PoorsMurder", "31");
			pchar.questTemp.LSC = "SearchSlavesLSC";
		break;

		////////////////////////////////////////////////////////////////////////////////
		//	END OF Корсарское метро
		////////////////////////////////////////////////////////////////////////////////
	}
}

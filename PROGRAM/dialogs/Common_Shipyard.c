// boal 08/04/06 общий диалог верфи
#include "DIALOGS\Rumours\Simple_rumors.c"  //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld, rRealShip, rColony;
	aref Link, NextDiag;
	string sTemp;

	int iSumm, iTemp, i;
	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернёт 7 (лодка)
	int iRank = sti(PChar.rank);

	bool bShipMoored = CheckShipMoored();

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);//homo 16/06/06

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Shipyard\" + NPChar.City + "_Shipyard.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}

	// вызов диалога по городам <--
	int iTest = FindColony(NPChar.City); // город магазина
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	//Выбор компаньонов для интерфейса кастомизаци корабля
	sTemp = Dialog.CurrentNode;
	if (HasSubStr(sTemp, "Pick_"))
	{
		i = sti(FindStringAfterChar(sTemp, "_"));
		sld = &characters[i];
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchShipCustomizeScreen(npchar, sld);
	}

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ship_tunning_not_now":  // аналог выхода, со старых времен, много переделывать.
			LockControl("DlgDown3", false);
			LockControl("DlgUp3", false);
			DialogExit();
			NextDiag.CurrentNode = "Master_Ship";  // выход для тюнинга, нужно тут из-за LoadSegment
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			LAi_LocationFightDisable(&locations[FindLocation(PChar.location)], false);
			PChar.questTemp.ShipyardExitFromLocation.location = pchar.location;
			PChar.questTemp.ShipyardExitFromLocation.shipyard = npchar.id;

			pchar.quest.ShipyardExit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.ShipyardExit.win_condition.l1.location = pchar.location;
			pchar.quest.ShipyardExit.win_condition = "ShipyardRefreshInLocation";

			sTemp = LAi_FindNearestFreeLocator2Pchar("goto");
			ChangeCharacterAddressGroup(NPChar, pchar.location, "goto", sTemp);
			LAi_SetActorType(NPChar);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_ActorRunToLocation(npchar, "reload", sTemp, "none", "", "", "", -1.0);
			DoQuestCheckDelay("ShipyardExitFromLocation", 2.0);

			SetNPCQuestDate(npchar, "resentment");
			AddDialogExitQuest("MainHeroFightModeOn");

		break;

		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Common_Shipyard_4", LinkRandPhrase(
								StringFromKey("Common_Shipyard_1"),
								StringFromKey("Common_Shipyard_2"),
								StringFromKey("Common_Shipyard_3", pchar))),
						StringFromKey("Common_Shipyard_8", LinkRandPhrase(
								StringFromKey("Common_Shipyard_5", pchar),
								StringFromKey("Common_Shipyard_6", pchar),
								StringFromKey("Common_Shipyard_7", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Common_Shipyard_11", RandPhraseSimple(
								StringFromKey("Common_Shipyard_9"),
								StringFromKey("Common_Shipyard_10"))),
						StringFromKey("Common_Shipyard_14", RandPhraseSimple(
								StringFromKey("Common_Shipyard_12", GetWorkTypeOfMan(npchar, "")),
								StringFromKey("Common_Shipyard_13", GetWorkTypeOfMan(npchar, "")))));
				link.l1.go = "exit";
				break;
			}

			if (!CheckNPCQuestDate(npchar, "resentment"))
			{
				dialog.text = StringFromKey("Common_Shipyard_15");
				link.l1 = StringFromKey("Common_Shipyard_16");
				link.l1.go = "exit";
				break;
			}

			NextDiag.TempNode = "First time";

			//homo Линейка Блада
			if (Pchar.questTemp.CapBloodLine == true)
			{
				dialog.Text = StringFromKey("Common_Shipyard_20", LinkRandPhrase(
							StringFromKey("Common_Shipyard_17", TimeGreeting()),
							StringFromKey("Common_Shipyard_18"),
							StringFromKey("Common_Shipyard_19", GetFullName(pchar))));
				Link.l1 = StringFromKey("Common_Shipyard_21", NPChar.name);
				Link.l1.go = "exit";
				break;
			}

			if (NPChar.quest.meeting == "0")
			{
				dialog.Text = StringFromKey("Common_Shipyard_22", TimeGreeting(), GetFullName(NPChar));
				Link.l1 = StringFromKey("Common_Shipyard_23", pchar, GetFullName(Pchar));
				Link.l1.go = "meeting";
				NPChar.quest.meeting = "1";
			}
			else
			{
				//--->> квест украсть чертеж на верфи
				//дача квеста
				if (drand(2) == 1 && pchar.questTemp.different == "free" && GetEventPastTime("questShipyardsMap", "day") > 7 && GetNpcQuestPastDayWOInit(npchar, "questShipyardsMap") > 30 && !CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 25)
				{
					dialog.text = StringFromKey("Common_Shipyard_24");
					link.l1 = StringFromKey("Common_Shipyard_25");
					link.l1.go = "ShipyardsMap_1";
					SaveEventStartTime("questShipyardsMap");
					SaveCurrentNpcQuestDateParam(npchar, "questShipyardsMap");
					break;
				}
				//<<--- квест украсть чертеж на верфи			

				dialog.Text = pcharrepphrase(
							StringFromKey("Common_Shipyard_26"),
							StringFromKey("Common_Shipyard_27", TimeGreeting(), GetAddress_Form(NPChar)));
				Link.l1 = pcharrepphrase(
							StringFromKey("Common_Shipyard_28"),
							StringFromKey("Common_Shipyard_29"));
				Link.l1.go = "Shipyard";
				if (GetGlobalTutor())
				{
					goto Common_Shipyard_skipToExit_Common;
				}
				if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY)
				{
					link.l11 = StringFromKey("Common_Shipyard_30");
					link.l11.go = "Cannons";
				}
				// AlexBlade -> new UI
				link.l12 = StringFromKey("Common_Shipyard_31");
				link.l12.go = "ShipCustomize";
				// 
				Link.l2 = StringFromKey("Common_Shipyard_32");
				Link.l2.go = "quests"; //(перессылка в файл города)
				// -->
				if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
				{
					link.l3 = StringFromKey("Common_Shipyard_33", pchar);
					link.l3.go = "LoanForAll";
				}
				if (CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
				{
					link.l7 = StringFromKey("Common_Shipyard_36", RandPhraseSimple(
								StringFromKey("Common_Shipyard_34", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))),
								StringFromKey("Common_Shipyard_35", pchar, GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)))));
					link.l7.go = "IntelligenceForAll";
				}
				//--> квест Аззи.
				if (CheckCharacterItem(pchar, "Azzy_bottle"))
				{
					link.l5 = StringFromKey("Common_Shipyard_37");
					if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
					{
						link.l5.go = "AggryHelp";
						pchar.questTemp.Azzy = "Azzy_IHaveLamp";
					}
					else
					{
						link.l5.go = "AzzyTryTalk";
					}
				}
				//<-- на квест Аззи.
				//проверка выполнения квеста украсть чертеж на верфи
				if (CheckCharacterItem(pchar, "ShipyardsMap") && CheckAttribute(pchar, "questTemp.different.ShipyardsMap.Id") && pchar.questTemp.different.ShipyardsMap.Id == npchar.id)
				{
					link.l6 = StringFromKey("Common_Shipyard_38", pchar, XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Gen"));
					link.l6.go = "ShipyardsMapOk_1";
				}
				if (CheckAttribute(pchar, "GenQuest.EncGirl"))
				{
					if (pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
					{
						link.l7 = StringFromKey("Common_Shipyard_39", pchar);
						link.l7.go = "EncGirl_4";
						pchar.quest.EncGirl_GetLoverFather.over = "yes";
					}
					if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
					{
						if (pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
						{
							link.l8 = StringFromKey("Common_Shipyard_40");
							link.l8.go = "EncGirl_1";
						}
					}
				}
				Common_Shipyard_skipToExit_Common:
				Link.l9 = StringFromKey("Common_Shipyard_41");
				Link.l9.go = "exit";
			}
		break;

		case "Meeting":
			dialog.Text = StringFromKey("Common_Shipyard_42");
			Link.l1 = StringFromKey("Common_Shipyard_43", GetFullName(NPChar));
			Link.l1.go = "Shipyard";
			if (GetGlobalTutor())
			{
			    goto Common_Shipyard_skipToExit;
			}
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY)
			{
				link.l13 = StringFromKey("Common_Shipyard_44");
				link.l13.go = "Cannons";
			}
			// AlexBlade -> new UI
			link.l12 = StringFromKey("Common_Shipyard_45");
			link.l12.go = "ShipCustomize";
			Link.l2 = StringFromKey("Common_Shipyard_46");
			link.l2.go = "quests";
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = StringFromKey("Common_Shipyard_47", pchar);
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			if (CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") //квест мэра - на связь с нашим шпионом
			{
				link.l7 = StringFromKey("Common_Shipyard_50", RandPhraseSimple(
							StringFromKey("Common_Shipyard_48", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId))),
							StringFromKey("Common_Shipyard_49", pchar, GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)))));
				link.l7.go = "IntelligenceForAll";
			}
			//--> квест Аззи.
			if (CheckCharacterItem(pchar, "Azzy_bottle"))
			{
				link.l5 = StringFromKey("Common_Shipyard_51");
				if (npchar.id == pchar.questTemp.Ascold.ShipyarderId)
				{
					link.l5.go = "AggryHelp";
					pchar.questTemp.Azzy = "Azzy_IHaveLamp";
				}
				else
				{
					link.l5.go = "AzzyTryTalk";
				}
			}
			//<-- на квест Аззи.
			if (CheckAttribute(pchar, "GenQuest.EncGirl"))
			{
				if (pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l8 = StringFromKey("Common_Shipyard_52", pchar);
					link.l8.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if (pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = StringFromKey("Common_Shipyard_53");
						link.l9.go = "EncGirl_1";
					}
				}
			}
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
			{
				if (CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
				{
					link.l10 = StringFromKey("Common_Shipyard_54");
					link.l10.go = "ShipLetters_6";// генератор  "Найденные документы"
				}
			}
			Common_Shipyard_skipToExit:
			Link.l11 = StringFromKey("Common_Shipyard_55", pchar);
			Link.l11.go = "exit";
		break;

		case "ShipLetters_6":
			pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = StringFromKey("Common_Shipyard_56");
				link.l1 = StringFromKey("Common_Shipyard_57");
				link.l1.go = "exit";
			}
			else
			{
				sTemp = StringFromKey("Common_Shipyard_58");
				sTemp = StringFromKey("Common_Shipyard_59", sTemp, FindMoneyString(sti(pchar.questTemp.different.GiveShipLetters.price2)));
				dialog.text = sTemp;
				link.l1 = StringFromKey("Common_Shipyard_60");
				link.l1.go = "exit";
				link.l2 = StringFromKey("Common_Shipyard_61", GetFullName(NPChar));
				link.l2.go = "ShipLetters_7";
			}
		break;

		case "ShipLetters_7":
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "4");
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "EncGirl_1":
			dialog.text = StringFromKey("Common_Shipyard_62");
			link.l1 = StringFromKey("Common_Shipyard_63", pchar);
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
			dialog.text = StringFromKey("Common_Shipyard_64");
			link.l1 = StringFromKey("Common_Shipyard_65", pchar);
			link.l1.go = "EncGirl_3";
		break;

		case "EncGirl_3":
			dialog.text = StringFromKey("Common_Shipyard_66");
			link.l1 = StringFromKey("Common_Shipyard_67");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;

		case "EncGirl_4":
			if (sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
			{
				dialog.text = StringFromKey("Common_Shipyard_68", pchar);
				link.l1 = StringFromKey("Common_Shipyard_69", pchar);
				link.l1.go = "EncGirl_5";
			}
			else
			{
				dialog.text = StringFromKey("Common_Shipyard_70", pchar);
				link.l1 = StringFromKey("Common_Shipyard_71");
				link.l1.go = "EncGirl_6";
			}
		break;

		case "EncGirl_5":
			dialog.text = StringFromKey("Common_Shipyard_72");
			link.l1 = StringFromKey("Common_Shipyard_73");
			link.l1.go = "EncGirl_5_1";
		break;

		case "EncGirl_6":
			dialog.text = StringFromKey("Common_Shipyard_74");
			link.l1 = StringFromKey("Common_Shipyard_75");
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
			dialog.text = StringFromKey("Common_Shipyard_76");
			link.l1 = StringFromKey("Common_Shipyard_77");
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

		case "shipyard":
			if (!CheckShip(Pchar) || bShipMoored)
			{
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
				ShipyardRestrictDialog(Link, NPChar);
				break;
			}
		break;

		case "Cannons":
			if (bShipMoored)
			{
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
				ShipyardRestrictDialog(Link, NPChar);
				break;
			}
		break;

		case "ShipCustomize":
			if (bShipMoored)
			{
				dialog.text = StringFromKey("Common_Shipyard_86");
				for (i = 0; i < GetCompanionQuantity(PChar); i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp == -1) continue;
					sld = &characters[iTemp];
					if (CheckAttribute(sld, "Tasks.Clone") || CheckAttribute(sld, "NonRemovable")) continue;
					sTemp = "l" + i;
					rRealShip = GetRealShip(sti(sld.Ship.Type));
					link.(sTemp) = GetFullName(sld) + " (" + xiStr(rRealShip.BaseName) + " '" + sld.Ship.Name + "')";
					link.(sTemp).go = "Pick_" + iTemp;
				}
				Link.l99 = StringFromKey("Common_Shipyard_87", pchar);
				Link.l99.go = "exit";
			}
			else
			{
				ShipyardRestrictDialog(Link, NPChar);
				break;
			}
		break;
		// квест украсть чертеж на верфи
		case "ShipyardsMap_1":
			dialog.text = StringFromKey("Common_Shipyard_92");
			link.l1 = StringFromKey("Common_Shipyard_93");
			link.l1.go = "ShipyardsMap_2";
		break;
		case "ShipyardsMap_2":
			pchar.questTemp.different = "ShipyardsMap";
			pchar.questTemp.different.ShipyardsMap = "toTarget";
			pchar.questTemp.different.ShipyardsMap.Id = npchar.id; //квестодатель
			pchar.questTemp.different.ShipyardsMap.city = findShipyardCity(npchar);
			pchar.questTemp.different.ShipyardsMap.what = StringFromKey("Common_Shipyard_97", LinkRandPhrase(
						StringFromKey("Common_Shipyard_94"),
						StringFromKey("Common_Shipyard_95"),
						StringFromKey("Common_Shipyard_96")));
			pchar.questTemp.different.ShipyardsMap.chance = rand(5); //ценность чертежа
			if (rand(12) < GetCharacterSPECIAL(pchar, "Charisma"))
			{
				pchar.questTemp.different.ShipyardsMap.skladFight = false; //не будет драки на складе
			}
			else
			{
				pchar.questTemp.different.ShipyardsMap.skladFight = true; //будет драка на складе
			}
			pchar.questTemp.different.ShipyardsMap.sklad = rand(3) + 1; //сколько денег попросят на складе за открытие двери
			pchar.questTemp.different.ShipyardsMap.fightQty = 2 + rand(3); //количество бойцов на верфи
			dialog.text = StringFromKey("Common_Shipyard_98", XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Gen"), pchar.questTemp.different.ShipyardsMap.what);
			link.l1 = StringFromKey("Common_Shipyard_99", pchar);
			link.l1.go = "ShipyardsMap_3";
		break;
		case "ShipyardsMap_3":
			dialog.text = StringFromKey("Common_Shipyard_100");
			link.l1 = StringFromKey("Common_Shipyard_101");
			link.l1.go = "ShipyardsMap_4";
		break;
		case "ShipyardsMap_4":
			dialog.text = StringFromKey("Common_Shipyard_102");
			link.l1 = StringFromKey("Common_Shipyard_103");
			link.l1.go = "ShipyardsMap_5";
		break;
		case "ShipyardsMap_5":
			dialog.text = StringFromKey("Common_Shipyard_104");
			link.l1 = StringFromKey("Common_Shipyard_105");
			link.l1.go = "ShipyardsMap_disagree";
			link.l2 = StringFromKey("Common_Shipyard_106");
			link.l2.go = "ShipyardsMap_agree";
		break;

		case "ShipyardsMap_disagree":
			dialog.text = StringFromKey("Common_Shipyard_107");
			link.l1 = StringFromKey("Common_Shipyard_108");
			link.l1.go = "exit";
			pchar.questTemp.different = "free";
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
		break;
		case "ShipyardsMap_agree":
			dialog.text = StringFromKey("Common_Shipyard_109");
			link.l1 = StringFromKey("Common_Shipyard_110");
			link.l1.go = "exit";
			sld = ItemsFromID("ShipyardsMap");
			sld.shown = true;
			sld.startLocation = pchar.questTemp.different.ShipyardsMap.city + "_Shipyard";
			sld.startLocator = "item1";
			sld.ShipName = pchar.questTemp.different.ShipyardsMap.what;
			SetTimerFunction("SmallQuests_free", 0, 0, 1); //освобождаем разрешалку на миниквесты 
			ReOpenQuestHeader("ShipyardsMap");
			AddQuestRecord("ShipyardsMap", "1");
			AddQuestUserData("ShipyardsMap", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("ShipyardsMap", "sTarget", XI_ConvertString("Colony" + pchar.questTemp.different.ShipyardsMap.city + "Pre"));
			AddQuestUserData("ShipyardsMap", "sShip", pchar.questTemp.different.ShipyardsMap.what);
		break;

		case "Allarm":
			dialog.text = StringFromKey("Common_Shipyard_111", pchar);
			link.l1 = StringFromKey("Common_Shipyard_112");
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			AddCharacterExpToSkill(pchar, "FencingLight", 10);
			AddCharacterExpToSkill(pchar, "Fencing", 10);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 10);
			ChangeCharacterReputation(pchar, -1);
			for (i = 1; i <= sti(pchar.questTemp.different.ShipyardsMap.fightQty); i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("shipowner_" + i, "shipowner_" + (rand(16) + 1), "man", "man", iTemp, sti(pchar.nation), 0, true));
				FantomMakeCoolFighter(sld, iTemp, 70, 70, "topor" + (rand(2) + 1), "pistol2", 10);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;

		case "Allarm_1":
			dialog.text = StringFromKey("Common_Shipyard_113", pchar);
			link.l1 = StringFromKey("Common_Shipyard_114");
			link.l1.go = "fight";
			ShipyardsMapQuestEnd(npchar, "3");
			ChangeCharacterReputation(pchar, -1);
			for (i = 1; i <= 5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("shipowner_" + i, "shipowner_" + (rand(16) + 1), "man", "man", iTemp, sti(pchar.nation), 0, true));
				FantomMakeCoolFighter(sld, iTemp, 70, 70, "topor" + (rand(2) + 1), "pistol2", 10);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;

		case "ShipyardsMapOk_1":
			sTemp = pchar.questTemp.different.ShipyardsMap.what;
			dialog.text = StringFromKey("Common_Shipyard_115", strcut(sTemp, 0, strlen(sTemp) - 2));
			link.l1 = StringFromKey("Common_Shipyard_116");
			link.l1.go = "ShipyardsMapOk_2";
		break;

		case "ShipyardsMapOk_2":
			TakeItemFromCharacter(pchar, "ShipyardsMap");
			SaveCurrentNpcQuestDateParam(npchar, "questShipyardsMap");
			switch (sti(pchar.questTemp.different.ShipyardsMap.chance))
			{
				case 0:
					dialog.text = StringFromKey("Common_Shipyard_117");
					link.l1 = StringFromKey("Common_Shipyard_118", pchar);
					link.l1.go = "ShipyardsMapOk_3";
				break;
				case 1:
					dialog.text = StringFromKey("Common_Shipyard_119", FindMoneyString(1500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)));
					link.l1 = StringFromKey("Common_Shipyard_120");
					link.l1.go = "ShipyardsMapOk_5";
					TakeNItems(pchar, "jewelry17", makeint(1500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) / 100));
				break;
				case 2:
					dialog.text = StringFromKey("Common_Shipyard_121", FindMoneyString(3000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)));
					link.l1 = StringFromKey("Common_Shipyard_122");
					link.l1.go = "ShipyardsMapOk_5";
					TakeNItems(pchar, "jewelry5", makeint(3000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L) / 200));
				break;
				case 3:
					dialog.text = StringFromKey("Common_Shipyard_123", FindMoneyString(4500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)));
					link.l1 = StringFromKey("Common_Shipyard_124");
					link.l1.go = "ShipyardsMapOk_5";
					AddMoneyToCharacter(pchar, 4500 * GetCharacterSPECIALSimple(PChar, SPECIAL_L));
				break;
				case 4:
					dialog.text = StringFromKey("Common_Shipyard_125", FindMoneyString(6000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L)));
					link.l1 = StringFromKey("Common_Shipyard_126");
					link.l1.go = "ShipyardsMapOk_5";
					AddMoneyToCharacter(pchar, 6000 * GetCharacterSPECIALSimple(PChar, SPECIAL_L));
				break;
				case 5:
					dialog.text = StringFromKey("Common_Shipyard_127");
					link.l1 = StringFromKey("Common_Shipyard_128");
					link.l1.go = "ShipyardsMapOk_5";
					TakeNItems(pchar, "chest", 4);
				break;
			}
		break;

		case "ShipyardsMapOk_3":
			dialog.text = StringFromKey("Common_Shipyard_129");
			link.l1 = StringFromKey("Common_Shipyard_130");
			link.l1.go = "ShipyardsMapOk_4";
			link.l2 = StringFromKey("Common_Shipyard_131");
			link.l2.go = "Allarm_1";
		break;

		case "ShipyardsMapOk_4":
			dialog.text = StringFromKey("Common_Shipyard_132");
			link.l1 = StringFromKey("Common_Shipyard_133", pchar);
			link.l1.go = "exit";
			ShipyardsMapQuestEnd(npchar, "3");
		break;

		case "ShipyardsMapOk_5":
			dialog.text = StringFromKey("Common_Shipyard_134");
			link.l1 = StringFromKey("Common_Shipyard_135");
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			ChangeCharacterReputation(pchar, 5);
			ShipyardsMapQuestEnd(npchar, "4");
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
	int storeArray[MAX_COLONIES];
	int howStore = 0;

	for (n = 0; n < MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandNameByCity(npchar.city) != colonies[n].islandLable) //не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[rand(howStore - 1)];
	return colonies[nation].id;
}

void ShipyardRestrictDialog(aref arLink, ref rChar)
{
	int iNode = 136;
	if (Dialog.CurrentNode == "Cannons")
		iNode = 80;

	dialog.text = NPCharRepPhrase(rChar,
			pcharrepphrase(
					StringFromKey("Common_Shipyard_78"),
					StringFromKey("Common_Shipyard_79")),
			pcharrepphrase(
					StringFromKey("Common_Shipyard_" + iNode, GetFullName(pchar)),
					StringFromKey("Common_Shipyard_" + (iNode + 1))));
	arLink.l1 = NPCharRepPhrase(rChar,
			pcharrepphrase(
					StringFromKey("Common_Shipyard_82", RandSwear()),
					StringFromKey("Common_Shipyard_83", pchar, GetFullName(rChar))),
			pcharrepphrase(
					StringFromKey("Common_Shipyard_84"),
					StringFromKey("Common_Shipyard_85")));
	arLink.l1.go = "exit";
}

void ShipyardsMapQuestEnd(ref rChar, string sQuestNote)
{
	AddQuestRecord("ShipyardsMap", sQuestNote);
	AddQuestUserData("ShipyardsMap", "sSex", GetSexPhrase("", "а"));
	AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + rChar.city + "Gen"));
	CloseQuestHeader("ShipyardsMap");
	DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
}

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

	bool ok;

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
	/* //HardCoffee отключаю, так как введён новый интерфейс кастомизации корабля -->
	// генератор парусов по кейсу -->
	string attrLoc   = Dialog.CurrentNode;
  	if (HasSubStr(attrLoc, "SailsColorIdx_"))
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsColorIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsColorDone";
 	}
 	if (HasSubStr(attrLoc, "SailsTypeChooseIDX_"))
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.SailsTypeChooseIDX = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "SailsTypeChoose2";
 	}
 	// генератор парусов по кейсу <--

	// --->>> ZhilyaevDm 15.11.22 перекраска кораблей с нац хуллами
	if (HasSubStr(attrLoc, "HullColorIdx_"))
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.HullColorIdx = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "HullColorDone";
	}
	if (HasSubStr(attrLoc, "HullTypeChooseIDX_"))
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.HullTypeChooseIDX = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "HullTypeChoose2";
	}
	// <<<--- ZhilyaevDm
	*/ //HardCoffee отключаю, так как введён новый интерфейс кастомизации корабля <--
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
				if (rand(1) && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questShipyardsMap") > 7 && !CheckAttribute(pchar, "questTemp.different.ShipyardsMap") && GetSummonSkillFromName(pchar, SKILL_SNEAK) > 25)
				{
					dialog.text = StringFromKey("Common_Shipyard_24");
					link.l1 = StringFromKey("Common_Shipyard_25");
					link.l1.go = "ShipyardsMap_1";
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
			if (CheckShipMooredInColony(rColony))
			{
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchShipyard(npchar);
			}
			else
			{
				ShowShipIsNotInColonyDialog(link, npChar);
			}
		break;

		case "Cannons":
			if (CheckShipMooredInColony(rColony))
			{
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchCannons(sti(rColony.StoreNum));
			}
			else
			{
				ShowShipIsNotInColonyDialog(link, npChar);
			}
		break;

		case "ShipCustomize":
			if (CheckShipMooredInColony(rColony))
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
				dialog.text = NPCharRepPhrase(npchar,
						StringFromKey("Common_Shipyard_88"),
						StringFromKey("Common_Shipyard_89"));
				link.l1 = pcharrepphrase(
							StringFromKey("Common_Shipyard_90", RandSwear()),
							StringFromKey("Common_Shipyard_91", pchar, GetFullName(npchar)));
				link.l1.go = "exit";
			}
		break;
		/*
				case "ShipCustomize":
					DialogExit();
					LaunchShipCustomizeScreen(npchar, pchar);
				break;
		*//* //HardCoffee отключаю так как появился интерфейс кастомизации
		case "SailsGerald":
            ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		    if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
			{
			    dialog.text = "Сменить цвет парусов стоит " +
				              FindMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE))+
							  ", поставить новый герб стоит " +
							  FindMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE)) +
							  ", цена смены типа парусины зависит от материала.";
							  
			    link.l1 = "Выбрать новый цвет.";
			    link.l1.go = "SailsColorChoose";
			    link.l2 = "Изобразить новый герб.";
			    link.l2.go = "SailsGeraldChoose";
			    
				// Паруса ЛГ
				if(!CheckForFlyingDuchmanSails(PChar))
				{
					link.l3 = "Изменить материал парусов."; // Материал изменить нельзя, если стоят паруса ЛГ
					link.l3.go = "SailsTypeChoose";
					link.l4 = "Я хочу установить устрашающие паруса, как на легендарном корабле-призраке!";
					link.l4.go = "FlyingDutchmanSails";
				}
				else
				{
					link.l4 = "Я хочу убрать устрашающие паруса.";
					link.l4.go = "FlyingDutchmanSails_Clear";
				}
				
			    Link.l9 = "Я " + GetSexPhrase("передумал", "передумала") +".";
				Link.l9.go = "exit";
			}
			else
			{
			    dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("Дуришь меня? А где же твой корабль? У пирса его нет!",
				                                                     "Клянусь дьяволом, тебе не обмануть меня! У пирса нет твоего корабля!"),
													  pcharrepphrase("Я не вижу вашего корабля в порту, капитан " +GetFullName(pchar)+ ". А за ваш камзол я готов дать лишь пару медных монет.",
													                 "Капитан, паруса - это такая самая большая-большая тряпка, которая висит высоко-высоко на корабле на таком длинном деревянном бревне. Привяжите свой корабль возле города и я вам её покажу."));
				link.l1 = NPCharRepPhrase(npchar, pcharrepphrase(RandSwear()+"Какая неприятность!!! Ладно, старый проныра, ещё увидимся!",
				                                                 "Я не " + GetSexPhrase("хотел", "хотела") +" вас обмануть " +GetFullName(npchar)+ ", корабль на другой стороне острова."),
												  pcharrepphrase("Огромное спасибо, я мигом.",
												                 "Спасибо за совет, обязательно им воспользуюсь."));
			    link.l1.go = "exit";
			}
		break;
		
		// Warship 16.06.09 Паруса ЛГ
		case "FlyingDutchmanSails":
			if(iShipClass < 4)
			{
				iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // Цена за установку парусов
				dialog.text = "Да, я как раз придумал интересную геометрию паруса: он напоминает рваный, чтобы книппели и ядра наносили меньший ущерб. Его, кстати, можно пошить из ненового сукна. Думаю, для вашего корабля такой комплект будет стоить " + FindMoneyString(iSumm) + ".";
				
				if(sti(PChar.money) >= iSumm)
				{
					Link.l1 = "Отлично! Меня это устраивает.";
					Link.l1.go = "FlyingDutchmanSails_SetDuchman";
				}
				
				Link.l2 = "Какая несуразная цена! Забудьте об этом.";
				Link.l2.go = "exit";
			}
			else
			{
				dialog.text = "На Вашем судне такие паруса будут выглядеть потешно. Подыщите более внушительный корабль...";
				Link.l1 = "Буду искать, куда деваться-то...";
				Link.l1.go = "exit";
			}
		break;
		
		case "FlyingDutchmanSails_SetDuchman":
			iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // Цена за установку парусов
			
			AddMoneyToCharacter(PChar, -iSumm);
			
			dialog.text = "Замечательно. Всё сделаем в лучшем виде.";
			Link.l1 = "Спасибо.";
			Link.l1.go = "exit";
			
			SetShipSailsFromFile(PChar, "ships/parus_common_torn.tga"); // Паруса ЛГ
			
			WaitDate("", 0, 0, 0, 1, 30);
		break;
		
		// Убрать паруса ЛГ
		case "FlyingDutchmanSails_Clear":
			iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // Цена за установку парусов
			
			dialog.text = "Ну, убрать так убрать. Это обойдётся тебе в " + FindMoneyString(iSumm) + ".";
			
			if(sti(PChar.money) >= iSumm)
			{
				Link.l1 = "Отлично! Меня это устраивает.";
				Link.l1.go = "FlyingDutchmanSails_SetNormal";
			}
			
			Link.l2 = "Какая несуразная цена! Забудьте об этом.";
			Link.l2.go = "exit";
		break;
		
		case "FlyingDutchmanSails_SetNormal":
			rRealShip = GetRealShip(sti(PChar.Ship.Type));
			
			iSumm = (10 / iShipClass) * iRank * MOD_SKILL_ENEMY_RATE * 10; // Цена за установку парусов
			
			AddMoneyToCharacter(PChar, -iSumm);
			
			dialog.text = "Замечательно. Всё сделаем в лучшем виде.";
			Link.l1 = "Спасибо.";
			Link.l1.go = "exit";
			
			DeleteAttribute(rRealShip, "EmblemedSails.normalTex");
			
			WaitDate("", 0, 0, 0, 1, 30);
		break;
		*/ //HardCoffee отключаю так как появился интерфейс кастомизации <--
		/* HardCoffee отключаю так как появился интерфейс кастомизации -->
				case "SailsTypeChoose":
					dialog.text = "Какой новый тип парусины ставим? У тебя сейчас паруса из материала '" + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails)) + "'.";

					Link.l1 = GetSailsType(1) + ".";
					Link.l1.go = "SailsTypeChooseIDX_1";
					Link.l2 = GetSailsType(2)  + ".";
					Link.l2.go = "SailsTypeChooseIDX_2";
					Link.l3 = GetSailsType(3)  + ".";
					Link.l3.go = "SailsTypeChooseIDX_3";

					attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
					DeleteAttribute(Link, attrLoc);

					Link.l99 = "Я " + GetSexPhrase("передумал", "передумала") +".";
					Link.l99.go = "exit";
				break;

				case "SailsTypeChoose2":
					NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
															  sti(NPChar.SailsTypeChooseIDX),
															  stf(NPChar.ShipCostRate),
															  sti(RealShips[sti(Pchar.Ship.Type)].Price));

					dialog.text = "У тебя сейчас паруса из материала '" + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails)) +
								  "', ты " + GetSexPhrase("выбрал", "выбрала") +" тип ткани '"+ GetSailsType(sti(NPChar.SailsTypeChooseIDX))+
								  "'. Стоимость замены " + FindMoneyString(sti(NPChar.SailsTypeMoney)) +". Меняем?";

					if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
					{
						Link.l1 = "Да.";
						Link.l1.go = "SailsTypeChooseDone";
					}
					Link.l99 = "Нет.";
					Link.l99.go = "exit";
				break;

				case "SailsTypeChooseDone":
					AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
					dialog.text = "Замечательно! Всё сделаем в лучшем виде.";
					Link.l9 = "Спасибо.";
					Link.l9.go = "exit";

					RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
					WaitDate("",0,0,0, 1, 30);
				break;

				// --->>> ZhilyaevDm 15.11.22 перекраска кораблей с нац хуллами. Диалог.
				case "HullTypeChoose":
					dialog.text = "Корпус твоего корабля окрашен в " + GetHullType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.hull)) + ". В какие цвета хочешь его перекрасить? ";

					Link.l1 = "В " + GetHullType(1) + ".";
					Link.l1.go = "HullTypeChooseIDX_1";
					Link.l2 = "В " + GetHullType(2) + ".";
					Link.l2.go = "HullTypeChooseIDX_2";
					Link.l3 = "В " + GetHullType(3) + ".";
					Link.l3.go = "HullTypeChooseIDX_3";
					Link.l4 = "В " + GetHullType(4) + ".";
					Link.l4.go = "HullTypeChooseIDX_4";

					attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.hull);
					DeleteAttribute(Link, attrLoc);

					Link.l99 = "Я " + GetSexPhrase("передумал", "передумала") + ".";
					Link.l99.go = "exit";
					break;

				case "HullTypeChoose2":
					NPChar.HullTypeMoney = GetHullTypePrice(stf(NPChar.ShipCostRate), sti(RealShips[sti(Pchar.Ship.Type)].Price));

					dialog.text = "Так, у тебя сейчас корпус выкрашен в " + GetHullType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.hull)) +
						", ты " + GetSexPhrase("выбрал", "выбрала") + " " + GetHullType(sti(NPChar.HullTypeChooseIDX)) +
						". Стоимость перекраски " + FindMoneyString(sti(NPChar.HullTypeMoney)) + ". Меняем?";

					if (sti(NPChar.HullTypeMoney) <= sti(Pchar.Money))
					{
						Link.l1 = "Да, меняем.";
						Link.l1.go = "HullTypeChooseDone";
					}
					Link.l99 = "Знаете, я подумаю.";
					Link.l99.go = "exit";
					break;

				case "HullTypeChooseDone":
					AddMoneyToCharacter(Pchar, -sti(NPChar.HullTypeMoney));
					dialog.text = "Замечательно! Всё сделаем в лучшем виде.";
					Link.l9 = "Спасибо.";
					Link.l9.go = "exit";

					RealShips[sti(Pchar.Ship.Type)].ship.upgrades.hull = sti(NPChar.HullTypeChooseIDX);
					WaitDate("", 0, 0, 0, 1, 30);
					break;
				// <<<--- ZhilyaevDm

				case "SailsColorChoose":
					if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
					{
						dialog.text = "Какой цвет ставим? Цена " + FindMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)) + ".";
						for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
						{
							if (CheckSailsColor(Pchar, i))
							{
								attrLoc = "l" + i;
								Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
								Link.(attrLoc).go = "SailsColorIdx_" + i;
							}
						}
						Link.l99 = "Я " + GetSexPhrase("передумал", "передумала") +".";
						Link.l99.go = "exit";
					}
					else
					{
						dialog.text = "Приходи, когда деньги будут.";
						Link.l9 = "Хорошо.";
						Link.l9.go = "exit";
					}
				break;

				case "SailsColorDone":
					AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
					dialog.text = "Договорились. Красим паруса в "+ GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name)) +" цвет.";
					Link.l9 = "Спасибо.";
					Link.l9.go = "exit";

					SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
					WaitDate("",0,0,0, 1, 30);
				break;

				case "SailsGeraldChoose":
					if(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
					{
						if(CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
						{
							NextDiag.CurrentNode = NextDiag.TempNode;
							DialogExit();
							LaunchSailsGeraldScreen(npchar);
						}
						else
						{
							dialog.text = "К сожалению, на твой корабль нельзя установить герб.";
							Link.l9 = "Жаль.";
							Link.l9.go = "exit";
						}
					}
					else
					{
						dialog.text = "Приходи, когда деньги будут.";
						Link.l9 = "Хорошо.";
						Link.l9.go = "exit";
					}
				break;
		*/ //HardCoffee отключаю, так как появился интерфейс кастомизации корабля <--
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
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
			AddQuestRecord("ShipyardsMap", "3");
			AddQuestUserData("ShipyardsMap", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("ShipyardsMap");
		break;

		case "ShipyardsMapOk_5":
			dialog.text = StringFromKey("Common_Shipyard_134");
			link.l1 = StringFromKey("Common_Shipyard_135");
			link.l1.go = "exit";
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			ChangeCharacterReputation(pchar, 5);
			AddQuestRecord("ShipyardsMap", "4");
			AddQuestUserData("ShipyardsMap", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("ShipyardsMap", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			CloseQuestHeader("ShipyardsMap");
			DeleteAttribute(pchar, "questTemp.different.ShipyardsMap");
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

void ShowShipIsNotInColonyDialog(aref link, ref npChar)
{
	dialog.text = NPCharRepPhrase(npChar,
			pcharrepphrase(
					StringFromKey("Common_Shipyard_78"),
					StringFromKey("Common_Shipyard_79")),
			pcharrepphrase(
					StringFromKey("Common_Shipyard_80", GetFullName(Pchar)),
					StringFromKey("Common_Shipyard_81")));
	link.l1 = NPCharRepPhrase(npChar,
			pcharrepphrase(
					StringFromKey("Common_Shipyard_82", RandSwear()),
					StringFromKey("Common_Shipyard_83", Pchar, GetFullName(npChar))),
			pcharrepphrase(
					StringFromKey("Common_Shipyard_84"),
					StringFromKey("Common_Shipyard_85")));
	link.l1.go = "exit";
}

/* //HardCoffee отключаю, так как появился интерфейс кастомизации -->
// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))  st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))  st = sti(shref.SailsColorIdx);
		if (st == col) return false;
	}
	return true;		
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	switch (_type)
	{
	    case 1 : return "Пенька";  break;
	    case 2 : return "Лён";     break;
	    case 3 : return "Хлопок";  break;
	}
	return "Пенька";
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

// Warship Ghdjthrf на паруса ЛГ
bool CheckForFlyingDuchmanSails(ref _char)
{
	ref realShip;
	int shipType = sti(_char.Ship.Type);
	
	if(shipType == SHIP_NOTUSED) return false;

	realShip = GetRealShip(shipType);

	if(CheckAttribute(realShip, "EmblemedSails.normalTex") && realShip.EmblemedSails.normalTex == "ships/parus_common_torn.tga")
	{
		return true;
	}

	return false;
}

// --->>> ZhilyaevDm 15.11.22 перекраска кораблей с нац хуллами
string GetHullType(int _type)
{
	switch (_type)
	{
	case 1: return "цвета британского королевского флота";			break;
	case 2: return "цвета французского военного флота";				break;
	case 3: return "военные цвета флота испанского королевства";	break;
	case 4: return "цвета кораблей голландской компании";			break;
	}
	return "английские военные цвета";
}

int GetHullTypePrice(float _shipCostRate, int _price)
{
	return makeint((_price * 0.05 + _price * 0.05) * _shipCostRate/4) * 10;
}
// <<<--- ZhilyaevDm */ //HardCoffee отключаю, так как появился интерфейс кастомизации <--
//TODO: сбалансировать штраф за обман с пожертвованиями; корректировка бонусов к здоровью в соответствии с механикой медицины

#include "DIALOGS\Rumours\Simple_rumors.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Citizen\" + NPChar.City + "_Citizen.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	iTest = FindColony(NPChar.City);
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
		case "First time":
		//--> диалог первой встречи
			if (npchar.quest.meeting == "0")
			{
				if (CheckAttribute(npchar, "quest.donation"))//пожертвования
				{
					dialog.text = StringFromKey("Monk_1", pchar);
					link.l1 = StringFromKey("Monk_2");
					link.l1.go = "donation";
					link.l2 = StringFromKey("Monk_3");
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckShipMooredInColony(rColony) && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && sti(RealShips[sti(Pchar.Ship.Type)].Class) != 7 && 7 - sti(RealShips[sti(Pchar.Ship.Type)].Class) < 4)//монах-пассажир
				{
					dialog.text = StringFromKey("Monk_4", pchar);
					link.l1 = StringFromKey("Monk_5");
					link.l1.go = "passenger";
					link.l2 = StringFromKey("Monk_6");
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan")) //корабельный капеллан
				{
					dialog.text = StringFromKey("Monk_7", pchar);
					link.l1 = StringFromKey("Monk_8");
					link.l1.go = "capellan";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = PCharRepPhrase(
							StringFromKey("Monk_12", LinkRandPhrase(
									StringFromKey("Monk_9", pchar),
									StringFromKey("Monk_10", pchar),
									StringFromKey("Monk_11", pchar))),
							StringFromKey("Monk_16", LinkRandPhrase(
									StringFromKey("Monk_13", pchar),
									StringFromKey("Monk_14", pchar),
									StringFromKey("Monk_15", pchar))));
				link.l1 = StringFromKey("Monk_20", LinkRandPhrase(
							StringFromKey("Monk_17"),
							StringFromKey("Monk_18"),
							StringFromKey("Monk_19")));
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = StringFromKey("Monk_23", RandPhraseSimple(
							StringFromKey("Monk_21"),
							StringFromKey("Monk_22")));
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES) * 10)
				{
					link.l3 = StringFromKey("Monk_24");
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7 - sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = StringFromKey("Monk_25");
					link.l4.go = "shipshine";
				}
				link.l10 = StringFromKey("Monk_29", LinkRandPhrase(
							StringFromKey("Monk_26"),
							StringFromKey("Monk_27"),
							StringFromKey("Monk_28")));
				link.l10.go = "exit";
				npchar.quest.meeting = "1";
			}
			else
			{
				//--> диалог второй встречи
				dialog.text = StringFromKey("Monk_33", LinkRandPhrase(
							StringFromKey("Monk_30", pchar),
							StringFromKey("Monk_31", pchar),
							StringFromKey("Monk_32", pchar)));
				link.l1 = StringFromKey("Monk_37", LinkRandPhrase(
							StringFromKey("Monk_34"),
							StringFromKey("Monk_35"),
							StringFromKey("Monk_36")));
				link.l1.go = "check";//на возможную выдачу квестов
				link.l2 = StringFromKey("Monk_40", RandPhraseSimple(
							StringFromKey("Monk_38"),
							StringFromKey("Monk_39")));
				link.l2.go = "quests";//(перессылка в файл города)
				if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES) * 10 && !CheckAttribute(npchar, "quest.slaves"))
				{
					link.l3 = StringFromKey("Monk_41");
					link.l3.go = "slaves";
				}
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7 - sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
				{
					link.l4 = StringFromKey("Monk_42");
					link.l4.go = "shipshine";
				}
				link.l10 = StringFromKey("Monk_46", LinkRandPhrase(
							StringFromKey("Monk_43"),
							StringFromKey("Monk_44"),
							StringFromKey("Monk_45")));
				link.l10.go = "exit";
			}
			NextDiag.TempNode = "First time";
		break;

		case "check":
			sTemp = FindCityToMC(true, false); //friend + drand
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && drand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger") && sTemp != "none") //церковная депеша
			{
				pchar.GenQuest.Monkletter.City = sTemp;
				pchar.GenQuest.Monkletter.StartCity = npchar.city;//город квестодателя
				dialog.text = StringFromKey("Monk_47", pchar, XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.City + "Gen"));
				link.l1 = StringFromKey("Monk_48", XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.City + "Gen"));
				link.l1.go = "Monkletter";
				link.l2 = StringFromKey("Monk_49");
				link.l2.go = "exit_monkletter";
				npchar.quest.monkletter = "true";
				break;
			}

			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && drand(8) > 5 && sti(pchar.rank < 20) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) //привезти молитвенники
			{
				pchar.GenQuest.Churchbooks.StartCity = npchar.city; //город квестодателя
				pchar.GenQuest.Churchbooks.Nation = npchar.nation;
				dialog.text = StringFromKey("Monk_50", pchar, NationNameGenitive(sti(npchar.nation)));
				link.l1 = StringFromKey("Monk_51");
				link.l1.go = "Churchbooks";
				link.l2 = StringFromKey("Monk_52", pchar);
				link.l2.go = "exit_churchbooks";
				npchar.quest.churchbooks = "true";
				break;
			}

			dialog.text = StringFromKey("Monk_55", RandPhraseSimple(
						StringFromKey("Monk_53", pchar),
						StringFromKey("Monk_54", pchar)));
			link.l1 = StringFromKey("Monk_56");
			link.l1.go = "exit";
		break;

		//-------------------------------------------------пожертвования------------------------------------------------
		case "donation":
			sTemp = DonationType();
			dialog.text = StringFromKey("Monk_57", pchar, sTemp);
			if (sti(pchar.money) < 100)
			{
				link.l1 = StringFromKey("Monk_58");
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = StringFromKey("Monk_59");
				link.l1.go = "donation_1";
			}
		break;

		case "donation_1":
			dialog.text = StringFromKey("Monk_60", pchar);
			link.l1 = StringFromKey("Monk_61");
			link.l1.go = "donation_rate_1";
			if (sti(pchar.money) >= 1000)
			{
				link.l2 = StringFromKey("Monk_62");
				link.l2.go = "donation_rate_2";
			}
			if (sti(pchar.money) >= 5000)
			{
				link.l3 = StringFromKey("Monk_63");
				link.l3.go = "donation_rate_3";
			}
			if (sti(pchar.money) >= 10000)
			{
				link.l4 = StringFromKey("Monk_64");
				link.l4.go = "donation_rate_4";
			}
			link.l5 = StringFromKey("Monk_65");
			link.l5.go = "donation_rate_none";
		break;

		case "donation_rate_1": //никаких плюшек
			AddMoneyToCharacter(pchar, -100);
			dialog.text = StringFromKey("Monk_66", pchar);
			link.l1 = StringFromKey("Monk_67");
			link.l1.go = "exit";
		break;

		case "donation_rate_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = StringFromKey("Monk_68", pchar);
			link.l1 = StringFromKey("Monk_69");
			link.l1.go = "exit";
			AddCharacterHealth(pchar, 3);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCrewMorale(pchar, 2);
		break;

		case "donation_rate_3":
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = StringFromKey("Monk_70", pchar);
			link.l1 = StringFromKey("Monk_71");
			link.l1.go = "exit";
			AddCharacterHealth(pchar, 4);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			AddCrewMorale(pchar, 3);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
		break;

		case "donation_rate_4":
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = StringFromKey("Monk_72", pchar);
			link.l1 = StringFromKey("Monk_73");
			link.l1.go = "exit";
			AddCharacterHealth(pchar, 7);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			AddCrewMorale(pchar, 5);
			ChangeCharacterReputation(pchar, 10);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeCrewExp(pchar, "Sailors", 5);
			ChangeCrewExp(pchar, "Cannoners", 5);
			ChangeCrewExp(pchar, "Soldiers", 5);
		break;

		case "donation_rate_none":
			dialog.text = StringFromKey("Monk_74", pchar);
			link.l1 = StringFromKey("Monk_75");
			link.l1.go = "donation_exit";
		break;

		case "donation_exit":
			DialogExit();
			ChangeCharacterReputation(pchar, -5);
			AddCharacterHealth(pchar, -3);
			LAi_CharacterDisableDialog(npchar);
		break;

		//-------------------------------------------отпустить рабов---------------------------------------------------
		case "slaves":
			dialog.text = StringFromKey("Monk_76", pchar);
			link.l1 = StringFromKey("Monk_77");
			link.l1.go = "slaves_1";
		break;

		case "slaves_1":
			AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES) * 10);
			dialog.text = StringFromKey("Monk_78", pchar);
			link.l1 = StringFromKey("Monk_79");
			link.l1.go = "slaves_2";
		break;

		case "slaves_2":
			npchar.quest.slaves = "true";
			DialogExit();
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_206", NewStr()), "Monk_RemoveSlaves", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
		break;
		//<-- отпустить рабов

		//----------------------------------------------освятить корабль------------------------------------------------
		case "shipshine":
		//получение среднего класса кораблей в эскадре героя
			iTemp = GetPcharSquadronAverageClass(false);
			switch (GetCompanionQuantity(pchar))
			{
				case 1:
					sTemp = StringFromKey("Monk_80", iTemp);
					pchar.GenQuest.Shipshine.Money = 5000 * (7 - iTemp);
				break;
				case 2:
					sTemp = StringFromKey("Monk_81");
					pchar.GenQuest.Shipshine.Money = makeint(1.8 * (5000 * (7 - iTemp)));
				break;
				case 3:
					sTemp = StringFromKey("Monk_82");
					pchar.GenQuest.Shipshine.Money = makeint(2.6 * (5000 * (7 - iTemp)));
				break;
				case 4:
					sTemp = StringFromKey("Monk_83");
					pchar.GenQuest.Shipshine.Money = makeint(3.4 * (5000 * (7 - iTemp)));
				break;
				case 5:
					sTemp = StringFromKey("Monk_84");
					pchar.GenQuest.Shipshine.Money = makeint(4.2 * (5000 * (7 - iTemp)));
				break;
				case 6:
					sTemp = StringFromKey("Monk_85"); //оставил, вдруг будем расширять...
					pchar.GenQuest.Shipshine.Money = makeint(5.0 * (5000 * (7 - iTemp)));
				break;
			}
			dialog.text = StringFromKey("Monk_86");
			link.l1 = sTemp;
			link.l1.go = "shipshine_1";
		break;

		case "shipshine_1":
			dialog.text = StringFromKey("Monk_87", pchar, FindMoneyString(sti(pchar.GenQuest.Shipshine.Money)));
			if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
			{
				link.l1 = StringFromKey("Monk_88");
				link.l1.go = "shipshine_2";
			}
			link.l2 = StringFromKey("Monk_89");
			link.l2.go = "shipshine_exit";
		break;

		case "shipshine_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
			dialog.text = StringFromKey("Monk_90", pchar);
			link.l1 = StringFromKey("Monk_91");
			link.l1.go = "shipshine_3";
		break;

		case "shipshine_3":
			DialogExit();
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_207", NewStr()), "Monk_Shipshine", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); //крутим время
			RecalculateJumpTable();
		break;

		case "shipshine_exit":
			DialogExit();
			DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
		//<-- освятить корабль

		//------------------------------------------корабельный капеллан-----------------------------------------------
		case "capellan":
			dialog.text = StringFromKey("Monk_92");
			link.l1 = StringFromKey("Monk_93");
			link.l1.go = "capellan_1";
			pchar.questTemp.ShipCapellan = "true";
		break;

		case "capellan_1":
			dialog.text = StringFromKey("Monk_94", pchar);
			if (sti(pchar.money) >= 50000)
			{
				link.l1 = StringFromKey("Monk_95");
				link.l1.go = "capellan_2";
			}
			link.l2 = StringFromKey("Monk_96"); //TODO: просто отказ без ссылки на недостаток денег
			link.l2.go = "capellan_exit";
		break;

		case "capellan_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "capellan_2":
			AddMoneyToCharacter(pchar, -50000);
			chrDisableReloadToLocation = true; //закрыть локацию
			dialog.text = StringFromKey("Monk_97", pchar);
			link.l1 = StringFromKey("Monk_98");
			link.l1.go = "capellan_3";
		break;

		case "capellan_3":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "loc1", "Monk_Capellan", -1);
			pchar.questTemp.ShipCapellan.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType"); //удалить признак фантома
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.ShipCapellan.Yes = "true"; //капеллан в команде
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			npchar.Capellan = "";
			npchar.Payment = true;
			npchar.reputation = 65;
		break;

		case "capellan_4":
			dialog.text = StringFromKey("Monk_99", pchar);
			link.l1 = StringFromKey("Monk_100");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Monk_101");
			link.l2.go = "capellan_5";
			if (Get_My_Cabin() == npchar.location)
			{
				link.l3 = StringFromKey("Monk_102");
				link.l3.go = "capellan_8";
			}
			NextDiag.TempNode = "capellan_4";
		break;

		case "capellan_5": //HardCoffee - может стоит придумать отдельную ветку диалога для "кровавого убийцы"?
			dialog.text = StringFromKey("Monk_103", pchar);
			link.l1 = StringFromKey("Monk_104");
			link.l1.go = "capellan_6";
		break;

		case "capellan_6":
			DialogExit();
			ShipCapellan_Remove();
		break;

		case "capellan_7": //HardCoffee ref
			dialog.text = StringFromKey("Monk_105");
			link.l1 = StringFromKey("Monk_106");
			if (Get_My_Cabin() == NPChar.location) link.l1.go = "capellan_8";
			else link.l1.go = "exit";
			NextDiag.TempNode = "capellan_7";
		break;

		case "capellan_8": //HardCoffee выгнать капеллана из каюты
			if (CheckAttribute(loadedLocation, "locators.reload.reload1") && LAi_IsLocatorFree("reload", "reload1", 0.05))
			{
				LAi_SetActorTypeNoGroup(NPChar);
				LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
			}
			else ChangeCharacterAddress(NPChar, "none", "");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//<-- капеллан

		//--------------------------------------------монах-пассажир---------------------------------------------------
		case "passenger":
			if (drand(19) < 15) SetPassengerParameter("Monkpassenger", false);
			else SetPassengerParameter("Monkpassenger", true);
			dialog.text = StringFromKey("Monk_107", pchar, XI_ConvertString("Colony" + pchar.GenQuest.Monkpassenger.City), XI_ConvertString(GetIslandNameByCity(pchar.GenQuest.Monkpassenger.City) + "Pre"), FindDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)), FindMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			link.l1 = StringFromKey("Monk_108", pchar);
			link.l1.go = "passenger_1";
			link.l2 = StringFromKey("Monk_109");
			link.l2.go = "passenger_exit";
			npchar.quest.passenger = true;
		break;

		case "passenger_exit":
			dialog.text = StringFromKey("Monk_110", pchar);
			link.l1 = StringFromKey("Monk_111");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;

		case "passenger_1":
			dialog.text = StringFromKey("Monk_112");
			link.l1 = StringFromKey("Monk_113");
			link.l1.go = "passenger_2";
		break;

		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Monkpassenger.id = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType"); //удалить признак фантома, иначе - пустые города
			LAi_SetImmortal(npchar, true);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sTitle = npchar.index + "Citizpassenger";

			// LDH 13Sep17 - do not add to an existing Citizpassenger record
			// "Rename" the quest record by copying it to a new name and deleting the old record
			if (CheckAttribute(pchar, "questinfo." + sTitle))
			{
				string sTempLDH = frand(1);
				sTempLDH = strcut(sTempLDH, 2, 5);    // 4 random digits
				string sTitle1 = sTitle + sTempLDH;

				aref arTo, arFrom;
				makearef(arFrom, pchar.questinfo.(sTitle));
				makearef(arTo, pchar.questinfo.(sTitle1));
				CopyAttributes(arTo, arFrom);
				pchar.questinfo.(sTitle1) = "";

				DeleteAttribute(pchar, "questinfo." + sTitle);

				Trace("Duplicate Citizpassenger record " + sTitle + " copied to " + sTitle1 + " **");
			}

			AddQuestRecordEx(sTitle, "Citizpassenger", "1");
			AddQuestUserDataForTitle(sTitle, "sType", "монаха");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = StringFromKey("Monk_114", XI_ConvertString("Colony" + pchar.GenQuest.Monkpassenger.City), XI_ConvertString(GetIslandNameByCity(pchar.GenQuest.Monkpassenger.City) + "Pre"));
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
			AddQuestUserData(sTitle, "sMoney", FindMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			pchar.quest.Monkpassenger.win_condition.l1 = "location";
			pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City + "_town";
			pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
			SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;

		case "passenger_3":
			pchar.quest.Monkpassenger_Over.over = "yes"; //снять таймер
			dialog.text = StringFromKey("Monk_115", pchar);
			link.l1 = StringFromKey("Monk_116");
			link.l1.go = "passenger_4";
		break;

		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
			ChangeCharacterReputation(pchar, 2);
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity")) AddCharacterExpToSkill(pchar, "Sneak", 50);
			sTitle = npchar.index + "Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
		//<-- монах-пассажир

		//---------------------------------------------церковная депеша-------------------------------------------------
		case "exit_monkletter":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;

		case "Monkletter":
			dialog.text = StringFromKey("Monk_117", pchar);
			link.l1 = StringFromKey("Monk_118");
			link.l1.go = "Monkletter_1";
		break;

		case "Monkletter_1":
			DialogExit();
			GiveItem2Character(pchar, "letter_church");
			ReOpenQuestHeader("Monkletter");
			AddQuestRecord("Monkletter", "1");
			AddQuestUserData("Monkletter", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.City + "Gen"));
			AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.StartCity));
			SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
			OfficersReaction("good");
		break;
		//<-- Церковная депеша

		//-------------------------------------------доставить молитвенники---------------------------------------------
		case "exit_churchbooks":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

		case "Churchbooks":
			dialog.text = StringFromKey("Monk_119", NationNameGenitive(sti(npchar.nation)));
			link.l1 = StringFromKey("Monk_120");
			link.l1.go = "Churchbooks_1";
		break;

		case "Churchbooks_1":
			DialogExit();
			ReOpenQuestHeader("Churchbooks");
			AddQuestRecord("Churchbooks", "1");
			AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
			AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony" + pchar.GenQuest.Churchbooks.StartCity));
			SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
			pchar.GenQuest.Churchbooks = "go";
			switch (rand(3))
			{
				case 0: pchar.GenQuest.Churchbooks.Item = "jewelry8"; break;
				//Бронзовое кольцо
				case 1: pchar.GenQuest.Churchbooks.Item = "jewelry9"; break;
				//Бронзовый крестик
				case 2: pchar.GenQuest.Churchbooks.Item = "indian17"; break;
				//Тельная ладанка
				case 3: pchar.GenQuest.Churchbooks.Item = "jewelry15"; break;
				//Изумрудные подвески
				//Награды в ККС: amulet_2 _3 _5 _7 _10
			}
			OfficersReaction("good");
		break;
		//<-- доставить молитвенники

		/*case "CitizenNotBlade": //HardCoffee ref
			dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Monk_118"), StringFromKey("Monk_119"));
			link.l1 = LinkRandPhrase(StringFromKey("Monk_120"), StringFromKey("Monk_121"), StringFromKey("Monk_122"));
			link.l1.go = "exit";
		break;*/

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (drand(9))
	{
		case 0: sText = StringFromKey("Monk_124", LinkRandPhrase(
					StringFromKey("Monk_121"),
					StringFromKey("Monk_122"),
					StringFromKey("Monk_123"))); break;
		case 1: sText = StringFromKey("Monk_125"); break;
		case 2: sText = StringFromKey("Monk_126"); break;
		case 3: sText = StringFromKey("Monk_127"); break;
		case 4: sText = StringFromKey("Monk_128"); break;
		case 5: sText = StringFromKey("Monk_129"); break;
		case 6: sText = StringFromKey("Monk_130"); break;
		case 7: sText = StringFromKey("Monk_131"); break;
		case 8: sText = StringFromKey("Monk_132"); break;
		case 9: sText = StringFromKey("Monk_133"); break;
	}
	return sText;
}

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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
		case "fight":
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "quest_fight":
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DeliverToBander_Dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "First time":
			dialog.text = StringFromKey("Banders_dialog_1", pchar);
			link.l1 = StringFromKey("Banders_dialog_2", pchar.questTemp.jailCanMove.Deliver.name);
			link.l1.go = "Step_1";
			NextDiag.TempNode = "Second time";
		break;
		case "Step_1":
			dialog.text = StringFromKey("Banders_dialog_3");
			link.l1 = StringFromKey("Banders_dialog_4");
			link.l1.go = "Step_2";
			TakeItemFromCharacter(pchar, "Malyava");
		break;

		case "Step_2":
			dialog.text = StringFromKey("Banders_dialog_5", pchar);
			link.l1 = StringFromKey("Banders_dialog_6");
			link.l1.go = "Step_3";
		break;

		case "Step_3":
			dialog.text = StringFromKey("Banders_dialog_7", pchar);
			link.l1 = StringFromKey("Banders_dialog_8");
			link.l1.go = "Step_4";
		break;

		case "Step_4":
			dialog.text = StringFromKey("Banders_dialog_9");
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = StringFromKey("Banders_dialog_10", pchar);
				link.l1.go = "Step_5";
			}
			link.l2 = StringFromKey("Banders_dialog_11", pchar);
			link.l2.go = "Step_no";
		break;

		case "Step_5":
			switch (sti(pchar.questTemp.jailCanMove.Deliver.good))
			{
				case 0://попытка грабежа
					dialog.text = StringFromKey("Banders_dialog_12", pchar);
					link.l1 = StringFromKey("Banders_dialog_13");
					link.l1.go = "Step_fight";
				break;
				case 1://кидалово
					AddMoneyToCharacter(pchar, -50000);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10 + rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));

					dialog.text = StringFromKey("Banders_dialog_14", FindDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)), pchar.questTemp.jailCanMove.Deliver.Island.Areal, pchar.questTemp.jailCanMove.Deliver.add1, pchar.questTemp.jailCanMove.Deliver.ShipName1, pchar.questTemp.jailCanMove.Deliver.ShipName2, pchar.questTemp.jailCanMove.Deliver.Goods);
					link.l1 = StringFromKey("Banders_dialog_15", pchar);
					link.l1.go = "Step_lay";
				break;
				case 2://наведем на торговый корабль
					AddMoneyToCharacter(pchar, -50000);
					GetBandersTradeShore();
					GetBandersTradeGoods();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.terms = 10 + rand(2);
					pchar.questTemp.jailCanMove.Deliver.ShipName1 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.ShipName2 = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));

					dialog.text = StringFromKey("Banders_dialog_16", FindDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)), pchar.questTemp.jailCanMove.Deliver.Island.Areal, pchar.questTemp.jailCanMove.Deliver.add1, pchar.questTemp.jailCanMove.Deliver.ShipName1, pchar.questTemp.jailCanMove.Deliver.ShipName2, pchar.questTemp.jailCanMove.Deliver.Goods);
					link.l1 = StringFromKey("Banders_dialog_17", pchar);
					link.l1.go = "Step_trader";
				break;
				case 3://наведем на курьерский корабль
					AddMoneyToCharacter(pchar, -50000);
					GetBandersTradeShore();
					GetBandersTradeNation();
					pchar.questTemp.jailCanMove.Deliver.ShipName = GenerateRandomNameToShip(sti(pchar.questTemp.jailCanMove.Deliver.Nation));
					pchar.questTemp.jailCanMove.Deliver.terms = 5 + rand(5);
					dialog.text = StringFromKey("Banders_dialog_18", FindDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)), pchar.questTemp.jailCanMove.Deliver.Island.Areal, pchar.questTemp.jailCanMove.Deliver.add2, pchar.questTemp.jailCanMove.Deliver.ShipName);
					link.l1 = StringFromKey("Banders_dialog_19", pchar);
					link.l1.go = "Step_cureer";
				break;
			}
		break;

		case "Step_fight":
			dialog.text = StringFromKey("Banders_dialog_20", pchar);
			link.l1 = StringFromKey("Banders_dialog_21");
			link.l1.go = "quest_fight";
			link.l2 = StringFromKey("Banders_dialog_22");
			link.l2.go = "Step_takemoney";
		break;

		case "Step_takemoney":
			dialog.text = StringFromKey("Banders_dialog_23", pchar);
			link.l1 = StringFromKey("Banders_dialog_24");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			AddQuestRecord("MalyavaDeliver", "13");
			AddQuestUserData("MalyavaDeliver", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("MalyavaDeliver");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;

		case "Step_lay":
			dialog.text = StringFromKey("Banders_dialog_25");
			link.l1 = StringFromKey("Banders_dialog_26");
			link.l1.go = "exit";
			AddQuestRecord("MalyavaDeliver", "5");
			AddQuestUserData("MalyavaDeliver", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("MalyavaDeliver", "sDay", FindDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("MalyavaDeliver", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("MalyavaDeliver", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("MalyavaDeliver", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
			pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_lay";//придём - а там пусто
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;

		case "Step_trader":
			dialog.text = StringFromKey("Banders_dialog_27");
			link.l1 = StringFromKey("Banders_dialog_28");
			link.l1.go = "exit";
			AddQuestRecord("MalyavaDeliver", "5");
			AddQuestUserData("MalyavaDeliver", "sGoods", pchar.questTemp.jailCanMove.Deliver.add);
			AddQuestUserData("MalyavaDeliver", "sDay", FindDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("MalyavaDeliver", "sShipName1", pchar.questTemp.jailCanMove.Deliver.ShipName1);
			AddQuestUserData("MalyavaDeliver", "sShipName2", pchar.questTemp.jailCanMove.Deliver.ShipName2);
			AddQuestUserData("MalyavaDeliver", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1 = "location";
			pchar.quest.jailCanMoveDeliver_ShipsAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
			pchar.quest.jailCanMoveDeliver_ShipsAttack.function = "Deliver_CreateTraderShips";//создание кораблей
			SetFunctionTimerCondition("Deliver_TraderShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;

		case "Step_cureer":
			dialog.text = StringFromKey("Banders_dialog_29");
			link.l1 = StringFromKey("Banders_dialog_30");
			link.l1.go = "exit";
			AddQuestRecord("MalyavaDeliver", "8");
			AddQuestUserData("MalyavaDeliver", "sDay", FindDaysString(sti(pchar.questTemp.jailCanMove.Deliver.terms)));
			AddQuestUserData("MalyavaDeliver", "sText", pchar.questTemp.jailCanMove.Deliver.add2);
			AddQuestUserData("MalyavaDeliver", "sShipName", pchar.questTemp.jailCanMove.Deliver.ShipName);
			AddQuestUserData("MalyavaDeliver", "sShoreName", pchar.questTemp.jailCanMove.Deliver.Island.Areal);
			pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1 = "location";
			pchar.quest.jailCanMoveDeliver_ShipsCAttack.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.Island;//отправляем в локацию
			pchar.quest.jailCanMoveDeliver_ShipsCAttack.function = "Deliver_CreateCureerShips";//создание кораблей
			SetFunctionTimerCondition("Deliver_CureerShipsOver", 0, 0, sti(pchar.questTemp.jailCanMove.Deliver.terms), false);//таймер
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
		break;

		case "Step_no":
			dialog.text = StringFromKey("Banders_dialog_31");
			link.l1 = StringFromKey("Banders_dialog_32");
			link.l1.go = "exit";
			AddQuestRecord("MalyavaDeliver", "12");
			AddQuestUserData("MalyavaDeliver", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("MalyavaDeliver", "sSex1", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("MalyavaDeliver");
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
		break;

		case "Second time":
			dialog.text = StringFromKey("Banders_dialog_33");
			link.l1 = StringFromKey("Banders_dialog_34");
			link.l1.go = "exit";
			NextDiag.TempNode = "Second time";
		break;

		case "Man_FackYou":
			dialog.text = StringFromKey("Banders_dialog_35", pchar);
			link.l1 = StringFromKey("Banders_dialog_39", LinkRandPhrase(
						StringFromKey("Banders_dialog_36"),
						StringFromKey("Banders_dialog_37"),
						StringFromKey("Banders_dialog_38")));
			link.l1.go = "fight";
		break;
	}
}

void GetBandersTradeShore()//выберем остров для торгашей и курьера
{
	pchar.questTemp.jailCanMove.Deliver.Island = GetRandomIslandExcept("Panama,Pearl,Tenotchitlan");
	pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomFreeShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
	while (pchar.questTemp.jailCanMove.Deliver.Island.Shore == "")
	{
		pchar.questTemp.jailCanMove.Deliver.Island = GetRandomIslandExcept("Panama,Pearl,Tenotchitlan");
		pchar.questTemp.jailCanMove.Deliver.Island.Shore = GetIslandRandomFreeShoreId(pchar.questTemp.jailCanMove.Deliver.Island);
		if (!isLocationFreeForQuests(pchar.questTemp.jailCanMove.Deliver.Island)) pchar.questTemp.jailCanMove.Deliver.Island.Shore = "";
	}
	//Rosarak. Город берём по ареалу бухты (может быть и "none")
	pchar.questTemp.jailCanMove.Deliver.Island.Town = GetCityNameByLocation(&locations[FindLocation(pchar.questTemp.jailCanMove.Deliver.Island.Shore)]);
	if (pchar.questTemp.jailCanMove.Deliver.Island.Town == "none")
	{
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = GetConvertStr(pchar.questTemp.jailCanMove.Deliver.Island, "LocLables.txt");
	}
	else
	{
		pchar.questTemp.jailCanMove.Deliver.Island.Areal = XI_ConvertString("Colony" + pchar.questTemp.jailCanMove.Deliver.Island.Town + "Gen");
	}
}

void GetBandersTradeGoods()//выберем товар для торгашей
{
	switch (rand(6))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_EBONY;
			pchar.questTemp.jailCanMove.Deliver.add = StringFromKey("Banders_dialog_40");
		break;
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_MAHOGANY;
			pchar.questTemp.jailCanMove.Deliver.add = StringFromKey("Banders_dialog_41");
		break;
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_SANDAL;
			pchar.questTemp.jailCanMove.Deliver.add = StringFromKey("Banders_dialog_42");
		break;
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_COFFEE;
			pchar.questTemp.jailCanMove.Deliver.add = StringFromKey("Banders_dialog_43");
		break;
		case 4:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_SILK;
			pchar.questTemp.jailCanMove.Deliver.add = StringFromKey("Banders_dialog_44");
		break;
		case 5:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_FOOD;
			pchar.questTemp.jailCanMove.Deliver.add = StringFromKey("Banders_dialog_45");
		break;
		case 6:
			pchar.questTemp.jailCanMove.Deliver.Goods = GOOD_WEAPON;
			pchar.questTemp.jailCanMove.Deliver.add = StringFromKey("Banders_dialog_46");
		break;
	}
}

void GetBandersTradeNation()//выберем нацию торгаша и курьера
{
	switch (rand(3))
	{
		case 0:
			pchar.questTemp.jailCanMove.Deliver.Nation = SPAIN;
			pchar.questTemp.jailCanMove.Deliver.add1 = StringFromKey("Banders_dialog_47");
			pchar.questTemp.jailCanMove.Deliver.add2 = StringFromKey("Banders_dialog_48");
		break;
		case 1:
			pchar.questTemp.jailCanMove.Deliver.Nation = FRANCE;
			pchar.questTemp.jailCanMove.Deliver.add1 = StringFromKey("Banders_dialog_49");
			pchar.questTemp.jailCanMove.Deliver.add2 = StringFromKey("Banders_dialog_50");
		break;
		case 2:
			pchar.questTemp.jailCanMove.Deliver.Nation = HOLLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = StringFromKey("Banders_dialog_51");
			pchar.questTemp.jailCanMove.Deliver.add2 = StringFromKey("Banders_dialog_52");
		break;
		case 3:
			pchar.questTemp.jailCanMove.Deliver.Nation = ENGLAND;
			pchar.questTemp.jailCanMove.Deliver.add1 = StringFromKey("Banders_dialog_53");
			pchar.questTemp.jailCanMove.Deliver.add2 = StringFromKey("Banders_dialog_54");
		break;
	}
}




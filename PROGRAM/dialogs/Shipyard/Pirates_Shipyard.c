// диалог по городам
// Это мастер тюнинга
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	int cannonQ, cannonMax, cannonMaxQ, shipClass, shipCapacity, shipMaxCrew, shipHP, cannonDiff, iCaliber;
	int questReapairMatherial1, questReapairMatherial2, questReapairMatherial3, questReapairWorkPrice;
	int AllMatherial1, AllMatherial2, AllMatherial3;
	int quantityMatherial1, quantityMatherial2, quantityMatherial3;
	int cannonMatherial1, cannonMatherial2, cannonMatherial3;
	int capacityMatherial1, capacityMatherial2, capacityMatherial3;
	int SpeedRateMatherial1, SpeedRateMatherial2, SpeedRateMatherial3;
	int MaxCrewMatherial1, MaxCrewMatherial2, MaxCrewMatherial3;
	int TurnRateMatherial1, TurnRateMatherial2, TurnRateMatherial3;
	int HPMatherial1, HPMatherial2, HPMatherial3;
	int WindAgainstMatherial1, WindAgainstMatherial2, WindAgainstMatherial3;
	int cannonAllWorkPrice, cannonQWorkPrice, cannonWorkPrice, capacityWorkPrice, SpeedRateWorkPrice, MaxCrewWorkPrice, TurnRateWorkPrice, HPWorkPrice, WindAgainstWorkPrice;
	float shipSpeedRate, shipTurnRate, shipWindAgainst;

	int amount;
	ref shTo, chTo;
	string sTemp;
	string s1;

	if (HasSubStr(Dialog.CurrentNode, "ship_tuning_start|"))
	{
		string attrL = Dialog.CurrentNode;
		int index = findsubstr(attrL, "|", 0);
		chTo = &characters[GetCompanionIndex(pchar, sti(strcut(attrL, index + 1, strlen(attrL) - 1)))];
		NPChar.SelectedShip.Type = chTo.ship.type;
		Dialog.CurrentNode = "ship_tuning_start";
	}

	if (CheckAttribute(NPChar, "SelectedShip.Type") && sti(NPChar.SelectedShip.Type) != SHIP_NOTUSED)
	{
		cannonQ = sti(RealShips[sti(NPChar.SelectedShip.Type)].CannonsQuantity);
		cannonMax = sti(RealShips[sti(NPChar.SelectedShip.Type)].MaxCaliber);
		cannonMaxQ = sti(RealShips[sti(NPChar.SelectedShip.Type)].CannonsQuantityMax);
		shipClass = sti(RealShips[sti(NPChar.SelectedShip.Type)].Class);
		//int   shipPrice     = sti(RealShips[sti(NPChar.Ship.Type)].Price);
		shipCapacity = sti(RealShips[sti(NPChar.SelectedShip.Type)].Capacity);
		shipSpeedRate = stf(RealShips[sti(NPChar.SelectedShip.Type)].SpeedRate);
		shipMaxCrew = sti(RealShips[sti(NPChar.SelectedShip.Type)].MaxCrew);
		shipHP = sti(RealShips[sti(NPChar.SelectedShip.Type)].HP);
		shipTurnRate = stf(RealShips[sti(NPChar.SelectedShip.Type)].TurnRate);
		shipWindAgainst = stf(RealShips[sti(NPChar.SelectedShip.Type)].WindAgainstSpeed);
		cannonDiff = cannonMaxQ - cannonQ;
		iCaliber;

		/*
				if(cannonDiff >= 2)
				{
					cannonDiff = 2;
					cannonMaxQ = cannonQ + cannonDiff;
				}
				else
				{
					cannonDiff = 0;
				}
		*/
		float fQuestShip = 1.0;

		if (CheckAttribute(pchar, "ship.type") && sti(pchar.ship.type) != SHIP_NOTUSED && CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "QuestShip")) fQuestShip = 1.3;

		//int  zWorkPrice  = makeint(8000 * ((7-shipClass) * MOD_SKILL_ENEMY_RATE) * fQuestShip);
		int sundukSum = makeint(((7 - shipClass) * 1.3) * fQuestShip);

		cannonMatherial1 = makeint((cannonQ * 2 + 70 * (7 - shipClass) - 20) * fQuestShip);
		cannonMatherial2 = makeint((7 - shipClass) / 2 * fQuestShip);
		if (cannonMatherial2 < 1) cannonMatherial2 = 1;
		cannonMatherial3 = sundukSum;
		cannonWorkPrice = makeint((100 * cannonQ * MOD_SKILL_ENEMY_RATE + 8000 * ((7 - shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		capacityMatherial1 = makeint((70 * (7 - shipClass) + shipCapacity * 7 / 100) * fQuestShip);
		capacityMatherial2 = makeint((20 * (7 - shipClass) + 10) * fQuestShip);
		capacityMatherial3 = sundukSum;
		capacityWorkPrice = makeint((2 * shipCapacity * MOD_SKILL_ENEMY_RATE + 8000 * ((7 - shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		SpeedRateMatherial1 = makeint((shipHP * 25 / 1000 + 140 * (7 - shipClass)) * fQuestShip);
		SpeedRateMatherial2 = makeint(10 * (7 - shipClass) * fQuestShip);
		SpeedRateMatherial3 = sundukSum;
		SpeedRateWorkPrice = makeint((100 * shipSpeedRate * MOD_SKILL_ENEMY_RATE + 8000 * ((7 - shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		MaxCrewMatherial1 = makeint((shipMaxCrew * 6 / 10 + 100 * (7 - shipClass)) * fQuestShip);
		MaxCrewMatherial2 = makeint((11 * (7 - shipClass) + 3) * fQuestShip);
		MaxCrewMatherial3 = sundukSum;
		MaxCrewWorkPrice = makeint((15 * shipMaxCrew * MOD_SKILL_ENEMY_RATE + 8000 * ((7 - shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		TurnRateMatherial1 = makeint((shipHP * 25 / 1000 + 750 / shipClass + 20) * fQuestShip);
		TurnRateMatherial2 = makeint((10 * (7 - shipClass) + 2) * fQuestShip);
		TurnRateMatherial3 = sundukSum;
		TurnRateWorkPrice = makeint((30 * shipTurnRate * MOD_SKILL_ENEMY_RATE + 8000 * ((7 - shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		HPMatherial1 = makeint((70 * (7 - shipClass) + shipHP * 7 / 100) * fQuestShip);
		HPMatherial2 = makeint(10 * ((7 - shipClass) * 3) * fQuestShip);
		HPMatherial3 = sundukSum;
		HPWorkPrice = makeint((shipHP * MOD_SKILL_ENEMY_RATE + 8000 * ((7 - shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		WindAgainstMatherial1 = makeint((shipHP * 25 / 1000 + 1500 / shipClass + 20) * fQuestShip);
		WindAgainstMatherial2 = makeint((11 * (7 - shipClass) + 1) * fQuestShip);
		WindAgainstMatherial3 = sundukSum;
		WindAgainstWorkPrice = makeint((300 * shipSpeedRate * MOD_SKILL_ENEMY_RATE + 8000 * ((7 - shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		quantityMatherial1 = makeint((cannonQ * 2 + 70 * (7 - shipClass) - 20) * fQuestShip);
		quantityMatherial2 = makeint((7 - shipClass) / 2 * fQuestShip);
		if (quantityMatherial2 < 1) quantityMatherial2 = 1;
		quantityMatherial3 = sundukSum;
		cannonQWorkPrice = makeint((100 * cannonMaxQ * MOD_SKILL_ENEMY_RATE + 8000 * ((7 - shipClass) * MOD_SKILL_ENEMY_RATE)) * fQuestShip);

		AllMatherial1 = cannonMatherial1 + quantityMatherial1;
		AllMatherial2 = cannonMatherial2 + quantityMatherial2;
		AllMatherial3 = cannonMatherial3 + quantityMatherial3;
		cannonAllWorkPrice = cannonWorkPrice + cannonQWorkPrice;
		//int  zWorkPriceAll  = zWorkPrice * 2;

		// ZhilyaevDm ремонт ЛГ / Пса войны
		questReapairMatherial1 = makeint(HPMatherial1 * 1.5);                        // красн. дерево для корпуса
		questReapairMatherial2 = makeint(capacityMatherial1 / 2);    // сандал для мачт
		questReapairMatherial3 = makeint(SpeedRateMatherial1 / 2);    // шёлк для парусов
		questReapairWorkPrice = 250000;                                // цена ремонта

		float discount = 1.0;
		if (CheckAttribute(NPChar, "Discount"))
		{
			discount = 0.8;
		}

		cannonMatherial1 = cannonMatherial1 * discount;
		cannonMatherial2 = cannonMatherial2 * discount;
		cannonMatherial3 = cannonMatherial3 * discount;
		if (cannonMatherial3 < 1) cannonMatherial3 = 1;
		cannonWorkPrice = cannonWorkPrice * discount;

		quantityMatherial1 = quantityMatherial1 * discount;
		quantityMatherial2 = quantityMatherial2 * discount;
		quantityMatherial3 = quantityMatherial3 * discount;
		if (quantityMatherial3 < 1) quantityMatherial3 = 1;
		cannonQWorkPrice = cannonQWorkPrice * discount;

		AllMatherial1 = AllMatherial1 * discount;
		AllMatherial2 = AllMatherial2 * discount;
		AllMatherial3 = AllMatherial3 * discount;
		if (AllMatherial3 < 1) AllMatherial3 = 1;
		cannonAllWorkPrice = cannonAllWorkPrice * discount;

		capacityMatherial1 = capacityMatherial1 * discount;
		capacityMatherial2 = capacityMatherial2 * discount;
		capacityMatherial3 = capacityMatherial3 * discount;
		if (capacityMatherial3 < 1) capacityMatherial3 = 1;
		capacityWorkPrice = capacityWorkPrice * discount;

		SpeedRateMatherial1 = SpeedRateMatherial1 * discount;
		SpeedRateMatherial2 = SpeedRateMatherial2 * discount;
		SpeedRateMatherial3 = SpeedRateMatherial3 * discount;
		if (SpeedRateMatherial3 < 1) SpeedRateMatherial3 = 1;
		SpeedRateWorkPrice = SpeedRateWorkPrice * discount;

		MaxCrewMatherial1 = MaxCrewMatherial1 * discount;
		MaxCrewMatherial2 = MaxCrewMatherial2 * discount;
		MaxCrewMatherial3 = MaxCrewMatherial3 * discount;
		if (MaxCrewMatherial3 < 1) MaxCrewMatherial3 = 1;
		MaxCrewWorkPrice = MaxCrewWorkPrice * discount;

		TurnRateMatherial1 = TurnRateMatherial1 * discount;
		TurnRateMatherial2 = TurnRateMatherial2 * discount;
		TurnRateMatherial3 = TurnRateMatherial3 * discount;
		if (TurnRateMatherial3 < 1) TurnRateMatherial3 = 1;
		TurnRateWorkPrice = TurnRateWorkPrice * discount;

		HPMatherial1 = HPMatherial1 * discount;
		HPMatherial2 = HPMatherial2 * discount;
		HPMatherial3 = HPMatherial3 * discount;
		if (HPMatherial3 < 1) HPMatherial3 = 1;
		HPWorkPrice = HPWorkPrice * discount;

		WindAgainstMatherial1 = WindAgainstMatherial1 * discount;
		WindAgainstMatherial2 = WindAgainstMatherial2 * discount;
		WindAgainstMatherial3 = WindAgainstMatherial3 * discount;
		if (WindAgainstMatherial3 < 1) WindAgainstMatherial3 = 1;
		WindAgainstWorkPrice = WindAgainstWorkPrice * discount;

		if (cannonMatherial2 < 1) cannonMatherial2 = 1;
		if (quantityMatherial2 < 1) quantityMatherial2 = 1;
	}

	int j;
	sTemp = Dialog.CurrentNode;
	if (HasStr(sTemp, "SeaQuestionChooseAnswer_"))
	{
		j = findsubstr(sTemp, "_", 0);
		TEV.SeaQuestionTemp.Answer = strcut(sTemp, j + 1, strlen(sTemp) - 1);
		Dialog.CurrentNode = "Question_chinese_check";
	}

	switch (Dialog.CurrentNode)
	{

		// -----------------------------------Диалог первый - первая встреча
		case "First time":  // перехват основного диалога, только один раз
			if (NPChar.quest.meeting == "0")
			{
				Dialog.Text = StringFromKey("Pirates_Shipyard_1", GetFullName(npchar));
				Link.l1 = pcharrepphrase(
							StringFromKey("Pirates_Shipyard_2", GetFullName(pchar)),
							StringFromKey("Pirates_Shipyard_3", GetFullName(pchar)));
				Link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else // нужно, если по квестам будет сброс на  "First time"
			{
				dialog.text = StringFromKey("Pirates_Shipyard_4");
				link.l1 = pcharrepphrase(
							StringFromKey("Pirates_Shipyard_5"),
							StringFromKey("Pirates_Shipyard_6"));
				link.l1.go = "node_3";
				link.l2 = pcharrepphrase(
							StringFromKey("Pirates_Shipyard_7"),
							StringFromKey("Pirates_Shipyard_8", pchar));
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Master_Ship";
			Dialog.CurrentNode = "Master_Ship";
		break;

		case "Master_Ship":
			dialog.text = StringFromKey("Pirates_Shipyard_9");
			link.l1 = pcharrepphrase(
						StringFromKey("Pirates_Shipyard_10"),
						StringFromKey("Pirates_Shipyard_11"));
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase(
						StringFromKey("Pirates_Shipyard_12"),
						StringFromKey("Pirates_Shipyard_13", pchar));
			link.l2.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "TuningEnd":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar, "Tuning");
			AddQuestRecord("ShipTuning", "End");
			CloseQuestHeader("ShipTuning");
			DialogExit();

			CheckAchievments_CheckTuning();
		break;

		case "TuningLose":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DeleteAttribute(NPChar, "Tuning");
			AddQuestRecord("ShipTuning", "Lose");
			AddQuestUserData("ShipTuning", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("ShipTuning");
			DialogExit();
		break;

		case "node_1":
			dialog.text = StringFromKey("Pirates_Shipyard_14");
			link.l1 = pcharrepphrase(
						StringFromKey("Pirates_Shipyard_15"),
						StringFromKey("Pirates_Shipyard_16"));
			link.l1.go = "node_2";
		break;

		case "node_2":
			dialog.text = StringFromKey("Pirates_Shipyard_17", pchar);
			link.l1 = pcharrepphrase(
						StringFromKey("Pirates_Shipyard_18"),
						StringFromKey("Pirates_Shipyard_19"));
			link.l1.go = "node_3";
			link.l2 = pcharrepphrase(
						StringFromKey("Pirates_Shipyard_20"),
						StringFromKey("Pirates_Shipyard_21"));
			link.l2.go = "exit";
		break;

		case "node_3":
			dialog.text = StringFromKey("Pirates_Shipyard_22", GetAddress_Form(NPChar));
			link.l1 = pcharrepphrase(
						StringFromKey("Pirates_Shipyard_23"),
						StringFromKey("Pirates_Shipyard_24"));
			link.l1.go = "shipyard_dlg";
			Link.l2 = StringFromKey("Pirates_Shipyard_25");
			Link.l2.go = "quests"; //(пересылка в файл города)
			// -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = StringFromKey("Pirates_Shipyard_26", pchar);
				link.l3.go = "LoanForAll";//(перессылка в файл города)
			}
			link.l9 = pcharrepphrase(
						StringFromKey("Pirates_Shipyard_27"),
						StringFromKey("Pirates_Shipyard_28"));
			link.l9.go = "exit";
			NextDiag.TempNode = "Master_Ship";
		break;

		case "shipyard_dlg":
			if (CheckAttribute(NPChar, "Tuning.TuningNode"))
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_31", RandPhraseSimple(
							StringFromKey("Pirates_Shipyard_29"),
							StringFromKey("Pirates_Shipyard_30")));
				Link.l1 = StringFromKey("Pirates_Shipyard_32");
				Link.l1.go = NPChar.Tuning.TuningNode;
				link.l2 = StringFromKey("Pirates_Shipyard_33");
				link.l2.go = "shipyard";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_34");
				Link.l1 = StringFromKey("Pirates_Shipyard_35");
				Link.l1.go = StartOrSelectTuningShip(NPChar);
				link.l2 = StringFromKey("Pirates_Shipyard_36");
				link.l2.go = "shipyard";
			}
			link.l3 = StringFromKey("Pirates_Shipyard_37");
			link.l3.go = "Cannons";
			// link.l4 = "Хочу изменить внешний вид парусов.";
			// link.l4.go = "SailsGerald";
			// AlexBlade -> new UI
			link.l4 = StringFromKey("Pirates_Shipyard_38");
			link.l4.go = "ShipCustomize";
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l5 = StringFromKey("Pirates_Shipyard_39", pchar);
				link.l5.go = "LoanForAll";//(пересылка в файл города)
			}
			Link.l9 = StringFromKey("Pirates_Shipyard_40");
			Link.l9.go = "ship_tunning_not_now";
		break;

		case "Discount_1":
			dialog.Text = StringFromKey("Pirates_Shipyard_41");
			Link.l1 = StringFromKey("Pirates_Shipyard_42");
			Link.l1.go = "Discount_2";
			Link.l9 = StringFromKey("Pirates_Shipyard_43");
			Link.l9.go = "ship_tuning_start";
		break;

		case "Discount_2":
			dialog.Text = StringFromKey("Pirates_Shipyard_44");
			Link.l1 = StringFromKey("Pirates_Shipyard_45");
			Link.l1.go = "Discount_3";
			LockControl("DlgDown3", true);
			LockControl("DlgUp3", true);
		break;

		case "Discount_3":
			NPChar.SeaQuestions = rand(sti(NullCharacter.SeaQuestions));
			sTemp = "q" + NPChar.SeaQuestions;
			dialog.Text = NullCharacter.SeaQuestions.(sTemp);

			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Discount_4";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);

			Link.l9 = StringFromKey("Pirates_Shipyard_46");
			Link.l9.go = "ship_tunning_not_now";
		break;

		case "Discount_4":
			sTemp = "a" + NPChar.SeaQuestions;
			if (NullCharacter.SeaQuestions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = StringFromKey("Pirates_Shipyard_47", pchar);
				link.l1 = StringFromKey("Pirates_Shipyard_48", pchar);
				link.l1.go = "ship_tuning_start";
				NPChar.Discount = true;
				LockControl("DlgDown3", false);
				LockControl("DlgUp3", false);
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Shipyard_49");
				link.l1 = StringFromKey("Pirates_Shipyard_50");
				link.l1.go = "Discount_5";
				link.l2 = StringFromKey("Pirates_Shipyard_51");
				link.l2.go = "ship_tunning_not_now";
			}
		break;

		case "Discount_5":
			sTemp = "q" + NPChar.SeaQuestions;
			dialog.Text = NullCharacter.SeaQuestions.(sTemp);
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Discount_4";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);

			Link.l9 = StringFromKey("Pirates_Shipyard_52");
			Link.l9.go = "ship_tunning_not_now";
		break;

		case "ship_tunning_not_now_2":
			dialog.Text = StringFromKey("Pirates_Shipyard_53");
			Link.l1 = StringFromKey("Pirates_Shipyard_56", RandPhraseSimple(
						StringFromKey("Pirates_Shipyard_54"),
						StringFromKey("Pirates_Shipyard_55")));
			Link.l1.go = "ship_tunning_not_now";
		break;

		case "ship_tuning_select":
			dialog.Text = StringFromKey("Pirates_Shipyard_57");
			ref rShipOwner;
			for (int shipsQty = 0; shipsQty < COMPANION_MAX; shipsQty++)
			{
				int iNpcIndex = GetCompanionIndex(pchar, shipsQty);
				if (iNpcIndex >= 0)
				{
					rShipOwner = &characters[iNpcIndex];
					string sLink = "l" + shipsQty;
					Link.(sLink) = StringFromKey("Pirates_Shipyard_58", XI_ConvertString(RealShips[sti(rShipOwner.Ship.Type)].BaseName), rShipOwner.Ship.Name);
					Link.(sLink).go = "ship_tuning_start|" + shipsQty;
				}
			}
		break;

		case "ship_tuning_start":
			if (sti(NPChar.SelectedShip.Type) == SHIP_NOTUSED || Pchar.location.from_sea != "Pirates_town")
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_59");
				Link.l1 = StringFromKey("Pirates_Shipyard_60");
				Link.l1.go = "ship_tunning_not_now";
			}
			else
			{
				if (GetHour() == 13)
				{
					dialog.Text = StringFromKey("Pirates_Shipyard_61");
					Link.l1 = StringFromKey("Pirates_Shipyard_62");
					Link.l1.go = "ship_tunning_not_now";
				}
				else
				{
					if (shipClass == 7)
					{
						dialog.Text = StringFromKey("Pirates_Shipyard_63");
						Link.l1 = StringFromKey("Pirates_Shipyard_64");
						Link.l1.go = "ship_tunning_not_now";
						break;
					}

					s1 = StringFromKey("Pirates_Shipyard_65", XI_ConvertString(RealShips[sti(NPChar.SelectedShip.Type)].BaseName));
					if (sti(RealShips[sti(NPChar.SelectedShip.Type)].Stolen) == true && !CheckAttribute(&RealShips[sti(NPChar.SelectedShip.Type)], "Tuning"))
					{
						s1 = StringFromKey("Pirates_Shipyard_66", s1);
					}
					s1 = StringFromKey("Pirates_Shipyard_67", pchar, s1);
					dialog.Text = s1;

					if (RealShips[sti(NPChar.SelectedShip.Type)].BaseType == SHIP_FLYINGDUTCHMAN)    //	ZhilyaevDm ремонт ЛГ
					{
						Link.l99 = StringFromKey("Pirates_Shipyard_68");
						Link.l99.go = "fdm_repairing_dialog";
					}

					if (RealShips[sti(NPChar.SelectedShip.Type)].BaseType == SHIP_CORVETTE_QUEST)    //	ZhilyaevDm ремонт Пса войны
					{
						Link.l99 = StringFromKey("Pirates_Shipyard_69", XI_ConvertString("corvette_quest"));
						Link.l99.go = "wdg_repairing_dialog";
					}

					if (cannonMax < 36 && cannonMax > 3 && cannonDiff > 0 && !CheckAttribute(&RealShips[sti(NPChar.SelectedShip.Type)], "Tuning.Cannon"))
					{
						Link.l1 = StringFromKey("Pirates_Shipyard_70");
						Link.l1.go = "ship_tunning_cannon_all";
					}
					else
					{
						if (cannonMax < 36 && cannonMax > 3 && !CheckAttribute(&RealShips[sti(NPChar.SelectedShip.Type)], "Tuning.Cannon"))
						{
							Link.l1 = StringFromKey("Pirates_Shipyard_71");
							Link.l1.go = "ship_tunning_cannon";
						}
						else
						{
							if (cannonDiff > 0 && !CheckAttribute(&RealShips[sti(NPChar.SelectedShip.Type)], "Tuning.Cannon"))
							{
								Link.l1 = StringFromKey("Pirates_Shipyard_72");
								Link.l1.go = "ship_c_quantity";
							}
						}
					}

					if (!CheckAttribute(&RealShips[sti(NPChar.SelectedShip.Type)], "Tuning.Capacity"))
					{
						Link.l2 = StringFromKey("Pirates_Shipyard_73");
						Link.l2.go = "ship_tunning_Capacity";
					}
					if (!CheckAttribute(&RealShips[sti(NPChar.SelectedShip.Type)], "Tuning.SpeedRate"))
					{
						Link.l3 = StringFromKey("Pirates_Shipyard_74");
						Link.l3.go = "ship_tunning_SpeedRate";
					}
					if (!CheckAttribute(&RealShips[sti(NPChar.SelectedShip.Type)], "Tuning.TurnRate"))
					{
						Link.l4 = StringFromKey("Pirates_Shipyard_75");
						Link.l4.go = "ship_tunning_TurnRate";
					}
					if (!CheckAttribute(&RealShips[sti(NPChar.SelectedShip.Type)], "Tuning.MaxCrew"))
					{
						Link.l5 = StringFromKey("Pirates_Shipyard_76");
						Link.l5.go = "ship_tunning_MaxCrew";
					}
					if (!CheckAttribute(&RealShips[sti(NPChar.SelectedShip.Type)], "Tuning.HP"))
					{
						Link.l6 = StringFromKey("Pirates_Shipyard_77");
						Link.l6.go = "ship_tunning_HP";
					}
					if (!CheckAttribute(&RealShips[sti(NPChar.SelectedShip.Type)], "Tuning.WindAgainst"))
					{
						Link.l7 = StringFromKey("Pirates_Shipyard_78");
						Link.l7.go = "ship_tunning_WindAgainst";
					}
					Link.l10 = StringFromKey("Pirates_Shipyard_79", pchar);
					Link.l10.go = "ship_tunning_not_now_2";
				}
			}
		break;

		case "Question_chinese_check":
			dialogEditStrings[1] = TEV.SeaQuestionTemp.Answer;
			Dialog.CurrentNode = TEV.SeaQuestionTemp;

			DeleteAttribute(&TEV, "SeaQuestionTemp");
			ProcessCommonDialogEvent(NPChar, Link, NextDiag);
		break;

		////////////////////////////////////////// --->>>  ZhilyaevDm ремонт ЛГ / Пса войны

		case "fdm_repairing_dialog":    // спец диалог для ЛГ
			s1 = StringFromKey("Pirates_Shipyard_80");
			dialog.Text = s1;

			Link.l1 = StringFromKey("Pirates_Shipyard_81");
			Link.l1.go = "quest_ship_repairing";
		break;

		case "wdg_repairing_dialog":    // спец диалог для Пса
			s1 = StringFromKey("Pirates_Shipyard_82");
			dialog.Text = s1;

			Link.l1 = StringFromKey("Pirates_Shipyard_83");
			Link.l1.go = "quest_ship_repairing";
		break;

		case "quest_ship_repairing":

			if (RealShips[sti(NPChar.SelectedShip.Type)].BaseType == SHIP_FLYINGDUTCHMAN) // ЛГ
			{
				s1 = StringFromKey("Pirates_Shipyard_84", questReapairMatherial1, questReapairMatherial2, questReapairMatherial3, its(3 * questReapairWorkPrice));

			}
			if (RealShips[sti(NPChar.SelectedShip.Type)].BaseType == SHIP_CORVETTE_QUEST) // Пес войны
			{
				s1 = StringFromKey("Pirates_Shipyard_85", pchar, questReapairMatherial1, questReapairMatherial2, questReapairMatherial3, FindMoneyString(questReapairWorkPrice));
			}

			dialog.Text = s1;

			Link.l1 = StringFromKey("Pirates_Shipyard_86", pchar);
			Link.l1.go = "quest_ship_repairing_start";
			Link.l2 = StringFromKey("Pirates_Shipyard_87");
			Link.l2.go = "ship_tunning_not_now";
		break;

		case "quest_ship_repairing_start":

			amount = questReapairWorkPrice;
			if (RealShips[sti(NPChar.SelectedShip.Type)].BaseType == SHIP_FLYINGDUTCHMAN) amount *= 3;

			if (makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);

				NPChar.Tuning.Money = amount;
				NPChar.Tuning.Matherial1 = questReapairMatherial1;
				NPChar.Tuning.Matherial2 = questReapairMatherial2;
				NPChar.Tuning.Matherial3 = questReapairMatherial3;
				NPChar.Tuning.ShipType = NPChar.SelectedShip.Type;
				NPChar.Tuning.ShipName = RealShips[sti(NPChar.SelectedShip.Type)].BaseName;

				NPChar.Tuning.TuningNode = "quest_ship_repairing_again";
				dialog.text = StringFromKey("Pirates_Shipyard_88");
				link.l1 = StringFromKey("Pirates_Shipyard_89", pchar);
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_380", XI_ConvertString(RealShips[sti(NPChar.SelectedShip.Type)].BaseName), NPChar.Tuning.Matherial1, NPChar.Tuning.Matherial2, NPChar.Tuning.Matherial3, FindMoneyString(sti(NPChar.Tuning.Money))));
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Shipyard_90");
				link.l1 = StringFromKey("Pirates_Shipyard_91");
				link.l1.go = "Exit";
			}
		break;

		case "quest_ship_repairing_again":
			if (GetShipOwnerInSquadron(NPChar))
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_92", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_93");
				Link.l1.go = "quest_ship_repairing_again_2";
				Link.l2 = StringFromKey("Pirates_Shipyard_94");
				Link.l2.go = "Exit";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_95", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_96");
				Link.l1.go = "TuningLose";
			}
		break;

		case "quest_ship_repairing_again_2":
			checkResoursesForRepairing(Pchar, NPChar, GOOD_MAHOGANY, GOOD_SANDAL, GOOD_SILK);

			if (sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				dialog.text = StringFromKey("Pirates_Shipyard_97", pchar);
				link.l1 = StringFromKey("Pirates_Shipyard_98");
				link.l1.go = "quest_ship_repairing_complite";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_99", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3));
				link.l1 = StringFromKey("Pirates_Shipyard_100");
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_381", NPChar.Tuning.Matherial1, NPChar.Tuning.Matherial2, NPChar.Tuning.Matherial3));
			}
		break;

		case "quest_ship_repairing_complite":
			shTo = &RealShips[sti(NPChar.SelectedShip.Type)];
			chTo = &characters[GetShipOwnerInSquadron(NPChar)];

			//	проверяем наличие апгрейдов
			bool upgrHull        = CheckAttribute(shTo, "Tuning.HP");
			bool upgrSpeed        = CheckAttribute(shTo, "Tuning.SpeedRate");
			bool upgrTurn        = CheckAttribute(shTo, "Tuning.TurnRate");
			bool upgrCapacity    = CheckAttribute(shTo, "Tuning.Capacity");
			bool upgrCrew        = CheckAttribute(shTo, "Tuning.MaxCrew");
			bool upgrWindAgSp    = CheckAttribute(shTo, "Tuning.WindAgainst");
			bool upgrCannon        = CheckAttribute(shTo, "Tuning.Cannon");
			int iCannons = chTo.Ship.Cannons.Type;

			if (RealShips[sti(NPChar.SelectedShip.Type)].BaseType == SHIP_FLYINGDUTCHMAN) // ЛГ
			{
				chTo.Ship.Type = GenerateShipExt(SHIP_FLYINGDUTCHMAN_O, true, chTo);
			}
			if (RealShips[sti(NPChar.SelectedShip.Type)].BaseType == SHIP_CORVETTE_QUEST) // Пес войны
			{
				chTo.Ship.Type = GenerateShipExt(SHIP_CORVETTE_QUEST_O, true, chTo);
			}

			shTo = &RealShips[sti(chTo.Ship.Type)]; // обновляем

			//	возвращаем апгрейды параметров нового корабля
			if (upgrHull)
			{
				shTo.Tuning.HP = true;                shTo.HP = sti(shTo.HP) + makeint(sti(shTo.HP) / 5);
			}
			if (upgrSpeed)
			{
				shTo.Tuning.SpeedRate = true;            shTo.SpeedRate = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate) / 5.0);
			}
			if (upgrTurn)
			{
				shTo.Tuning.TurnRate = true;            shTo.TurnRate = (stf(shTo.TurnRate) + stf(shTo.TurnRate) / 5.0);
			}
			if (upgrCapacity)
			{
				shTo.Tuning.Capacity = true;            shTo.Capacity = sti(shTo.Capacity) + makeint(sti(shTo.Capacity) / 5);
			}
			if (upgrCrew)
			{
				shTo.Tuning.MaxCrew = true;            shTo.MaxCrew = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew) / 5);
			}
			if (upgrWindAgSp)
			{
				shTo.Tuning.WindAgainst = true;        shTo.WindAgainstSpeed = FloatToString(stf(shTo.WindAgainstSpeed) + 0.5 * stf(shTo.WindAgainstSpeed) / stf(shTo.Class) + 0.005, 2);
			}
			if (upgrCannon)
			{
				shTo.Tuning.Cannon = true;            shTo.MaxCaliber = 32;
			}

			ProcessHullRepair(chTo, 100.0);
			ProcessSailRepair(chTo, 100.0);
			ShipOverhaul(chTo);
			chTo.Ship.Cannons.Type = iCannons;

			dialog.Text = StringFromKey("Pirates_Shipyard_101");
			WaitDate("", 0, 0, 5, 0, 10);
			dialog.Text = StringFromKey("Pirates_Shipyard_102");
			Link.l1 = StringFromKey("Pirates_Shipyard_103");
			Link.l1.go = "TuningEnd";

			Achievment_Set(ACH_Korabl_legenda);
		break;

		////////////////////////////////////////// <<<--- ZhilyaevDm ремонт ЛГ / Пса войны

		////////////////////////////////////////// калибр и количество орудий  ////////////////////////////////////////////////////
		case "ship_tunning_cannon_all":
			s1 = StringFromKey("Pirates_Shipyard_104", cannonQ, cannonMaxQ);
			s1 = StringFromKey("Pirates_Shipyard_105", s1, cannonMax, AllMatherial1);
			s1 = StringFromKey("Pirates_Shipyard_106", s1, AllMatherial2, AllMatherial3);
			s1 = StringFromKey("Pirates_Shipyard_107", s1, FindMoneyString(cannonAllWorkPrice));

			dialog.Text = s1;
			Link.l1 = StringFromKey("Pirates_Shipyard_108");
			Link.l1.go = "ship_tunning_cannon_all_start";
			Link.l2 = StringFromKey("Pirates_Shipyard_109");
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = StringFromKey("Pirates_Shipyard_110");
				Link.l3.go = "Discount_1";
			}
		break;

		case "ship_tunning_cannon_all_start":
			amount = cannonAllWorkPrice;
			if (makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
				NPChar.Tuning.Money = amount;
				NPChar.Tuning.Cannon = true;

				NPChar.Tuning.Matherial1 = AllMatherial1; // чёрное дерево
				NPChar.Tuning.Matherial2 = AllMatherial2; // кожа
				NPChar.Tuning.Matherial3 = AllMatherial3;
				NPChar.Tuning.ShipType = NPChar.SelectedShip.Type;
				NPChar.Tuning.ShipName = RealShips[sti(NPChar.SelectedShip.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");

				NPChar.Tuning.TuningNode = "ship_tunning_cannon_all_again";
				dialog.text = StringFromKey("Pirates_Shipyard_111");
				link.l1 = StringFromKey("Pirates_Shipyard_112", pchar);
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_382", XI_ConvertString(RealShips[sti(NPChar.SelectedShip.Type)].BaseName), NPChar.Tuning.Matherial1, NPChar.Tuning.Matherial2, NPChar.Tuning.Matherial3, FindMoneyString(sti(NPChar.Tuning.Money))));
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Shipyard_113");
				link.l1 = StringFromKey("Pirates_Shipyard_114");
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_cannon_all_again":
			if (GetShipOwnerInSquadron(NPChar))
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_115", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_116");
				Link.l1.go = "ship_tunning_cannon_all_again_2";
				Link.l2 = StringFromKey("Pirates_Shipyard_117");
				Link.l2.go = "Exit";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_118", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_119");
				Link.l1.go = "TuningLose";
			}
		break;

		case "ship_tunning_cannon_all_again_2":
			checkMatherial(Pchar, NPChar, GOOD_EBONY, "incas_collection", "chest");

			if (sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				dialog.text = StringFromKey("Pirates_Shipyard_120", pchar);
				link.l1 = StringFromKey("Pirates_Shipyard_121");
				link.l1.go = "ship_tunning_cannon_all_complite";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_122", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3));
				link.l1 = StringFromKey("Pirates_Shipyard_123");
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_383", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3)));
			}
		break;

		case "ship_tunning_cannon_all_complite":
			AddTimeToCurrent(8, 30);
			shTo = &RealShips[sti(NPChar.SelectedShip.Type)];
			chTo = &characters[GetShipOwnerInSquadron(NPChar)];
			DeleteAttribute(NPChar, "Tuning");

			// изменим калибр орудий
			iCaliber = sti(shTo.MaxCaliber);
			switch (iCaliber)
			{
				case 6:  iCaliber = 0; break;
				case 8:  iCaliber = 1; break;
				case 12: iCaliber = 2; break;
				case 16: iCaliber = 3; break;
				case 20: iCaliber = 4; break;
				case 24: iCaliber = 5; break;
				case 32: iCaliber = 6; break;
				case 36: iCaliber = 7; break;
			}
			iCaliber = iCaliber + 1;
			if (iCaliber > 7) iCaliber = 7;
			switch (iCaliber)
			{
				case 0: iCaliber = 6;  break;
				case 1: iCaliber = 8;  break;
				case 2: iCaliber = 12; break;
				case 3: iCaliber = 16; break;
				case 4: iCaliber = 20; break;
				case 5: iCaliber = 24; break;
				case 6: iCaliber = 32; break;
				case 7: iCaliber = 36; break;
			}
			shTo.MaxCaliber = iCaliber;

			// изменим количество орудий
			shTo.rcannon = sti(shTo.rcannon) + cannonDiff / 2;
			shTo.lcannon = sti(shTo.rcannon);
			shTo.CannonsQuantity = sti(shTo.rcannon) + sti(shTo.lcannon) + sti(shTo.fcannon) + sti(shTo.bcannon);

			chTo.Ship.Cannons.Borts.cannonl = sti(shTo.lcannon);
			chTo.Ship.Cannons.Borts.cannonr = sti(shTo.rcannon);
			chTo.Ship.Cannons.Borts.cannonf = sti(shTo.fcannon);
			chTo.Ship.Cannons.Borts.cannonb = sti(shTo.bcannon);
			chTo.Ship.Cannons = sti(shTo.CannonsQuantity);
			shTo.Tuning.Cannon = true;

			// finish <--
			TEV.AchievementData.Tuning.Cannon = true;
			s1 = StringFromKey("Pirates_Shipyard_124");
			s1 = StringFromKey("Pirates_Shipyard_125", s1);
			dialog.Text = s1;
			Link.l1 = StringFromKey("Pirates_Shipyard_126");
			Link.l1.go = "TuningEnd";
		break;

		////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////
		case "ship_c_quantity":
			s1 = StringFromKey("Pirates_Shipyard_127", cannonQ, cannonMaxQ);
			s1 = StringFromKey("Pirates_Shipyard_128", s1, quantityMatherial1);
			s1 = StringFromKey("Pirates_Shipyard_129", s1, quantityMatherial2, quantityMatherial3);
			s1 = StringFromKey("Pirates_Shipyard_130", s1, FindMoneyString(cannonQWorkPrice));
			dialog.Text = s1;
			Link.l1 = StringFromKey("Pirates_Shipyard_131");
			Link.l1.go = "ship_c_quantity_start";
			Link.l2 = StringFromKey("Pirates_Shipyard_132");
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = StringFromKey("Pirates_Shipyard_133");
				Link.l3.go = "Discount_1";
			}

		break;

		case "ship_c_quantity_start":
			amount = cannonQWorkPrice;
			if (makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
				NPChar.Tuning.Money = amount;
				NPChar.Tuning.Cannon = true;

				NPChar.Tuning.Matherial1 = quantityMatherial1; // чёрное дерево
				NPChar.Tuning.Matherial2 = quantityMatherial2; // кожа
				NPChar.Tuning.Matherial3 = quantityMatherial3;
				NPChar.Tuning.ShipType = NPChar.SelectedShip.Type;
				NPChar.Tuning.ShipName = RealShips[sti(NPChar.SelectedShip.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");

				NPChar.Tuning.TuningNode = "ship_c_quantity_again";
				dialog.text = StringFromKey("Pirates_Shipyard_134");
				link.l1 = StringFromKey("Pirates_Shipyard_135", pchar);
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_384", XI_ConvertString(RealShips[sti(NPChar.SelectedShip.Type)].BaseName), NPChar.Tuning.Matherial1, NPChar.Tuning.Matherial2, NPChar.Tuning.Matherial3, FindMoneyString(sti(NPChar.Tuning.Money))));
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Shipyard_136");
				link.l1 = StringFromKey("Pirates_Shipyard_137");
				link.l1.go = "Exit";
			}
		break;

		case "ship_c_quantity_again":
			if (GetShipOwnerInSquadron(NPChar))
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_138", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_139");
				Link.l1.go = "ship_c_quantity_again_2";
				Link.l2 = StringFromKey("Pirates_Shipyard_140");
				Link.l2.go = "Exit";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_141", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_142");
				Link.l1.go = "TuningLose";
			}
		break;

		case "ship_c_quantity_again_2":
			checkMatherial(Pchar, NPChar, GOOD_EBONY, "incas_collection", "chest");

			if (sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				dialog.text = StringFromKey("Pirates_Shipyard_143", pchar);
				link.l1 = StringFromKey("Pirates_Shipyard_144");
				link.l1.go = "ship_c_quantity_complite";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_145", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3));
				link.l1 = StringFromKey("Pirates_Shipyard_146");
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_385", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3)));
			}
		break;

		case "ship_c_quantity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(NPChar.SelectedShip.Type)];
			chTo = &characters[GetShipOwnerInSquadron(NPChar)];

			// изменим количество орудий
			shTo.rcannon = sti(shTo.rcannon) + cannonDiff / 2;
			shTo.lcannon = sti(shTo.rcannon);
			shTo.CannonsQuantity = sti(shTo.rcannon) + sti(shTo.lcannon) + sti(shTo.fcannon) + sti(shTo.bcannon);

			chTo.Ship.Cannons.Borts.cannonl = sti(shTo.lcannon);
			chTo.Ship.Cannons.Borts.cannonr = sti(shTo.rcannon);
			chTo.Ship.Cannons.Borts.cannonf = sti(shTo.fcannon);
			chTo.Ship.Cannons.Borts.cannonb = sti(shTo.bcannon);
			chTo.Ship.Cannons = sti(shTo.CannonsQuantity);
			shTo.Tuning.Cannon = true;
			// finish <--
			TEV.AchievementData.Tuning.Cannon = true;
			dialog.Text = StringFromKey("Pirates_Shipyard_147");
			Link.l1 = StringFromKey("Pirates_Shipyard_148");
			Link.l1.go = "TuningEnd";
		break;

		////////////////////////////////////////// только калибр орудий ////////////////////////////////////////////////////
		case "ship_tunning_cannon":
			s1 = StringFromKey("Pirates_Shipyard_149", cannonQ, cannonMax);

			s1 = StringFromKey("Pirates_Shipyard_150", s1, cannonMatherial1);
			s1 = StringFromKey("Pirates_Shipyard_151", s1, cannonMatherial2, cannonMatherial3);
			s1 = StringFromKey("Pirates_Shipyard_152", s1, FindMoneyString(cannonWorkPrice));
			dialog.Text = s1;
			Link.l1 = StringFromKey("Pirates_Shipyard_153");
			Link.l1.go = "ship_tunning_cannon_start";
			Link.l2 = StringFromKey("Pirates_Shipyard_154");
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = StringFromKey("Pirates_Shipyard_155");
				Link.l3.go = "Discount_1";
			}
		break;

		case "ship_tunning_cannon_start":
			amount = cannonWorkPrice;
			if (makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
				NPChar.Tuning.Money = amount;
				NPChar.Tuning.Cannon = true;
				NPChar.Tuning.Matherial1 = cannonMatherial1; // чёрное дерево
				NPChar.Tuning.Matherial2 = cannonMatherial2; // кожа
				NPChar.Tuning.Matherial3 = cannonMatherial3;
				NPChar.Tuning.ShipType = NPChar.SelectedShip.Type;
				NPChar.Tuning.ShipName = RealShips[sti(NPChar.SelectedShip.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");

				NPChar.Tuning.TuningNode = "ship_tunning_cannon_again";
				dialog.text = StringFromKey("Pirates_Shipyard_156");
				link.l1 = StringFromKey("Pirates_Shipyard_157", pchar);
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_386", XI_ConvertString(RealShips[sti(NPChar.SelectedShip.Type)].BaseName), NPChar.Tuning.Matherial1, NPChar.Tuning.Matherial2, NPChar.Tuning.Matherial3, FindMoneyString(sti(NPChar.Tuning.Money))));
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Shipyard_158");
				link.l1 = StringFromKey("Pirates_Shipyard_159");
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_cannon_again":
			if (GetShipOwnerInSquadron(NPChar))
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_160", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_161");
				Link.l1.go = "ship_tunning_cannon_again_2";
				Link.l2 = StringFromKey("Pirates_Shipyard_162");
				Link.l2.go = "Exit";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_163", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_164");
				Link.l1.go = "TuningLose";
			}
		break;

		case "ship_tunning_cannon_again_2":
			checkMatherial(Pchar, NPChar, GOOD_EBONY, "incas_collection", "chest");

			if (sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				dialog.text = StringFromKey("Pirates_Shipyard_165", pchar);
				link.l1 = StringFromKey("Pirates_Shipyard_166");
				link.l1.go = "ship_tunning_cannon_complite";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_167", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3));
				link.l1 = StringFromKey("Pirates_Shipyard_168");
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_387", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3)));
			}
		break;

		case "ship_tunning_cannon_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(NPChar.SelectedShip.Type)];
			DeleteAttribute(NPChar, "Tuning");
			// изменим калибр орудий
			iCaliber = sti(shTo.MaxCaliber);
			switch (iCaliber)
			{
				case 6:  iCaliber = 0; break;
				case 8:  iCaliber = 1; break;
				case 12: iCaliber = 2; break;
				case 16: iCaliber = 3; break;
				case 20: iCaliber = 4; break;
				case 24: iCaliber = 5; break;
				case 32: iCaliber = 6; break;
				case 36: iCaliber = 7; break;
			}
			iCaliber = iCaliber + 1;
			if (iCaliber > 7) iCaliber = 7;
			switch (iCaliber)
			{
				case 0: iCaliber = 6;  break;
				case 1: iCaliber = 8;  break;
				case 2: iCaliber = 12; break;
				case 3: iCaliber = 16; break;
				case 4: iCaliber = 20; break;
				case 5: iCaliber = 24; break;
				case 6: iCaliber = 32; break;
				case 7: iCaliber = 36; break;
			}
			shTo.MaxCaliber = iCaliber;
			shTo.Tuning.Cannon = true;
			// finish <--
			TEV.AchievementData.Tuning.Cannon = true;
			dialog.Text = StringFromKey("Pirates_Shipyard_169");
			Link.l1 = StringFromKey("Pirates_Shipyard_170");
			Link.l1.go = "TuningEnd";
		break;

		////////////////////////////////////////// трюм ////////////////////////////////////////////////////
		case "ship_tunning_Capacity":
			s1 = StringFromKey("Pirates_Shipyard_171", shipCapacity);

			s1 = StringFromKey("Pirates_Shipyard_172", s1, capacityMatherial1);
			s1 = StringFromKey("Pirates_Shipyard_173", s1, capacityMatherial2, capacityMatherial3);
			s1 = StringFromKey("Pirates_Shipyard_174", s1, FindMoneyString(capacityWorkPrice));
			dialog.Text = s1;
			Link.l1 = StringFromKey("Pirates_Shipyard_175");
			Link.l1.go = "ship_tunning_Capacity_start";
			Link.l2 = StringFromKey("Pirates_Shipyard_176");
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = StringFromKey("Pirates_Shipyard_177");
				Link.l3.go = "Discount_1";
			}

		break;

		case "ship_tunning_Capacity_start":
			amount = capacityWorkPrice;
			if (makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
				NPChar.Tuning.Money = amount;
				NPChar.Tuning.Matherial1 = capacityMatherial1; // красное дерево GOOD_MAHOGANY
				NPChar.Tuning.Matherial2 = capacityMatherial2; //  GOOD_OIL
				NPChar.Tuning.Matherial3 = capacityMatherial3;
				NPChar.Tuning.ShipType = NPChar.SelectedShip.Type;
				NPChar.Tuning.ShipName = RealShips[sti(NPChar.SelectedShip.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");

				NPChar.Tuning.TuningNode = "ship_tunning_Capacity_again";
				dialog.text = StringFromKey("Pirates_Shipyard_178");
				link.l1 = StringFromKey("Pirates_Shipyard_179", pchar);
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_388", XI_ConvertString(RealShips[sti(NPChar.SelectedShip.Type)].BaseName), NPChar.Tuning.Matherial1, NPChar.Tuning.Matherial2, NPChar.Tuning.Matherial3, FindMoneyString(sti(NPChar.Tuning.Money))));
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Shipyard_180");
				link.l1 = StringFromKey("Pirates_Shipyard_181");
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_Capacity_again":
			if (GetShipOwnerInSquadron(NPChar))
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_182", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_183");
				Link.l1.go = "ship_tunning_Capacity_again_2";
				Link.l2 = StringFromKey("Pirates_Shipyard_184");
				Link.l2.go = "Exit";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_185", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_186");
				Link.l1.go = "TuningLose";
			}
		break;

		case "ship_tunning_Capacity_again_2":
			checkMatherial(Pchar, NPChar, GOOD_SANDAL, "jewelry5", "chest");

			if (sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				dialog.text = StringFromKey("Pirates_Shipyard_187", pchar);
				link.l1 = StringFromKey("Pirates_Shipyard_188");
				link.l1.go = "ship_tunning_Capacity_complite";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_189", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3));
				link.l1 = StringFromKey("Pirates_Shipyard_190");
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_389", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3)));
			}
		break;

		case "ship_tunning_Capacity_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(NPChar.SelectedShip.Type)];
			DeleteAttribute(NPChar, "Tuning");
			// изменим
			if (!CheckAttribute(shTo, "Bonus_Capacity"))
			{
				shTo.Capacity = sti(shTo.Capacity) + makeint(sti(shTo.Capacity) / 5);
			}
			else
			{
				shTo.Capacity = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
			}
			shTo.Tuning.Capacity = true;
			// finish <--
			TEV.AchievementData.Tuning.Capacity = true;
			dialog.Text = StringFromKey("Pirates_Shipyard_191");
			Link.l1 = StringFromKey("Pirates_Shipyard_192");
			Link.l1.go = "TuningEnd";
		break;

		////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
		case "ship_tunning_SpeedRate":
			s1 = StringFromKey("Pirates_Shipyard_193", shipSpeedRate);

			s1 = StringFromKey("Pirates_Shipyard_194", s1, SpeedRateMatherial1);
			s1 = StringFromKey("Pirates_Shipyard_195", s1, SpeedRateMatherial3, SpeedRateMatherial2, FindMoneyString(SpeedRateWorkPrice));

			dialog.Text = s1;
			Link.l1 = StringFromKey("Pirates_Shipyard_196");
			Link.l1.go = "ship_tunning_SpeedRate_start";
			Link.l2 = StringFromKey("Pirates_Shipyard_197");
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = StringFromKey("Pirates_Shipyard_198");
				Link.l3.go = "Discount_1";
			}

		break;

		case "ship_tunning_SpeedRate_start":
			amount = SpeedRateWorkPrice;
			if (makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
				NPChar.Tuning.Money = amount;
				NPChar.Tuning.Matherial1 = SpeedRateMatherial1; // GOOD_SAILCLOTH
				NPChar.Tuning.Matherial2 = SpeedRateMatherial2; //  GOOD_SILK
				NPChar.Tuning.Matherial3 = SpeedRateMatherial3;
				NPChar.Tuning.ShipType = NPChar.SelectedShip.Type;
				NPChar.Tuning.ShipName = RealShips[sti(NPChar.SelectedShip.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");

				NPChar.Tuning.TuningNode = "ship_tunning_SpeedRate_again";
				dialog.text = StringFromKey("Pirates_Shipyard_199");
				link.l1 = StringFromKey("Pirates_Shipyard_200", pchar);
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_390", XI_ConvertString(RealShips[sti(NPChar.SelectedShip.Type)].BaseName), NPChar.Tuning.Matherial1, NPChar.Tuning.Matherial2, NPChar.Tuning.Matherial3, FindMoneyString(sti(NPChar.Tuning.Money))));
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Shipyard_201");
				link.l1 = StringFromKey("Pirates_Shipyard_202");
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_SpeedRate_again":
			if (GetShipOwnerInSquadron(NPChar))
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_203", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_204");
				Link.l1.go = "ship_tunning_SpeedRate_again_2";
				Link.l2 = StringFromKey("Pirates_Shipyard_205");
				Link.l2.go = "Exit";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_206", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_207");
				Link.l1.go = "TuningLose";
			}
		break;

		case "ship_tunning_SpeedRate_again_2":
			checkMatherial(Pchar, NPChar, GOOD_SILK, "jewelry2", "chest");

			if (sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				dialog.text = StringFromKey("Pirates_Shipyard_208", pchar);
				link.l1 = StringFromKey("Pirates_Shipyard_209");
				link.l1.go = "ship_tunning_SpeedRate_complite";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_210", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3));
				link.l1 = StringFromKey("Pirates_Shipyard_211");
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_391", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3)));
			}
		break;

		case "ship_tunning_SpeedRate_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(NPChar.SelectedShip.Type)];
			DeleteAttribute(NPChar, "Tuning");
			// изменим
			if (!CheckAttribute(shTo, "Bonus_SpeedRate"))
			{
				shTo.SpeedRate = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate) / 5.0);
			}
			else
			{
				shTo.SpeedRate = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
			}
			shTo.Tuning.SpeedRate = true;
			// finish <--
			TEV.AchievementData.Tuning.SpeedRate = true;
			dialog.Text = StringFromKey("Pirates_Shipyard_212");
			Link.l1 = StringFromKey("Pirates_Shipyard_213");
			Link.l1.go = "TuningEnd";
		break;
		////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
		case "ship_tunning_MaxCrew":
			s1 = StringFromKey("Pirates_Shipyard_214", FindPeoplesString(shipMaxCrew, "No"));

			s1 = StringFromKey("Pirates_Shipyard_215", s1, MaxCrewMatherial1);
			s1 = StringFromKey("Pirates_Shipyard_216", s1, MaxCrewMatherial2, MaxCrewMatherial3, FindMoneyString(MaxCrewWorkPrice));
			dialog.Text = s1;
			Link.l1 = StringFromKey("Pirates_Shipyard_217");
			Link.l1.go = "ship_tunning_MaxCrew_start";
			Link.l2 = StringFromKey("Pirates_Shipyard_218");
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = StringFromKey("Pirates_Shipyard_219");
				Link.l3.go = "Discount_1";
			}

		break;

		case "ship_tunning_MaxCrew_start":
			amount = MaxCrewWorkPrice;
			if (makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
				NPChar.Tuning.Money = amount;
				NPChar.Tuning.Matherial1 = MaxCrewMatherial1; // GOOD_FRUITS
				NPChar.Tuning.Matherial2 = MaxCrewMatherial2; //  GOOD_CLOTHES
				NPChar.Tuning.Matherial3 = MaxCrewMatherial3;
				NPChar.Tuning.ShipType = NPChar.SelectedShip.Type;
				NPChar.Tuning.ShipName = RealShips[sti(NPChar.SelectedShip.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");

				NPChar.Tuning.TuningNode = "ship_tunning_MaxCrew_again";
				dialog.text = StringFromKey("Pirates_Shipyard_220");
				link.l1 = StringFromKey("Pirates_Shipyard_221", pchar);
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_392", XI_ConvertString(RealShips[sti(NPChar.SelectedShip.Type)].BaseName), NPChar.Tuning.Matherial1, NPChar.Tuning.Matherial2, NPChar.Tuning.Matherial3, FindMoneyString(sti(NPChar.Tuning.Money))));
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Shipyard_222");
				link.l1 = StringFromKey("Pirates_Shipyard_223");
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_MaxCrew_again":
			if (GetShipOwnerInSquadron(NPChar))
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_224", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_225");
				Link.l1.go = "ship_tunning_MaxCrew_again_2";
				Link.l2 = StringFromKey("Pirates_Shipyard_226");
				Link.l2.go = "Exit";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_227", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_228");
				Link.l1.go = "TuningLose";
			}
		break;

		case "ship_tunning_MaxCrew_again_2":
			checkMatherial(Pchar, NPChar, GOOD_LEATHER, "jewelry1", "chest");

			if (sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				dialog.text = StringFromKey("Pirates_Shipyard_229", pchar);
				link.l1 = StringFromKey("Pirates_Shipyard_230");
				link.l1.go = "ship_tunning_MaxCrew_complite";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_231", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3));
				link.l1 = StringFromKey("Pirates_Shipyard_232");
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_393", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3)));
			}
		break;

		case "ship_tunning_MaxCrew_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(NPChar.SelectedShip.Type)];
			// изменим
			shTo.MaxCrew = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew) / 5);
			shTo.Tuning.MaxCrew = true;
			// finish <--
			TEV.AchievementData.Tuning.MaxCrew = true;
			dialog.Text = StringFromKey("Pirates_Shipyard_233");
			Link.l1 = StringFromKey("Pirates_Shipyard_234");
			Link.l1.go = "TuningEnd";
		break;

		////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
		case "ship_tunning_TurnRate":
			s1 = StringFromKey("Pirates_Shipyard_235", shipTurnRate);

			s1 = StringFromKey("Pirates_Shipyard_236", s1, TurnRateMatherial1);
			s1 = StringFromKey("Pirates_Shipyard_237", s1, TurnRateMatherial3, TurnRateMatherial2, FindMoneyString(TurnRateWorkPrice));
			dialog.Text = s1;
			Link.l1 = StringFromKey("Pirates_Shipyard_238");
			Link.l1.go = "ship_tunning_TurnRate_start";
			Link.l2 = StringFromKey("Pirates_Shipyard_239");
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = StringFromKey("Pirates_Shipyard_240");
				Link.l3.go = "Discount_1";
			}

		break;

		case "ship_tunning_TurnRate_start":
			amount = TurnRateWorkPrice;
			if (makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
				NPChar.Tuning.Money = amount;
				NPChar.Tuning.Matherial1 = TurnRateMatherial1; // GOOD_PLANKS
				NPChar.Tuning.Matherial2 = TurnRateMatherial2; //  GOOD_LINEN
				NPChar.Tuning.Matherial3 = TurnRateMatherial3;
				NPChar.Tuning.ShipType = NPChar.SelectedShip.Type;
				NPChar.Tuning.ShipName = RealShips[sti(NPChar.SelectedShip.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");

				NPChar.Tuning.TuningNode = "ship_tunning_TurnRate_again";
				dialog.text = StringFromKey("Pirates_Shipyard_241");
				link.l1 = StringFromKey("Pirates_Shipyard_242", pchar);
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_394", XI_ConvertString(RealShips[sti(NPChar.SelectedShip.Type)].BaseName), NPChar.Tuning.Matherial1, NPChar.Tuning.Matherial2, NPChar.Tuning.Matherial3, FindMoneyString(sti(NPChar.Tuning.Money))));
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Shipyard_243");
				link.l1 = StringFromKey("Pirates_Shipyard_244");
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_TurnRate_again":
			if (GetShipOwnerInSquadron(NPChar))
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_245", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_246");
				Link.l1.go = "ship_tunning_TurnRate_again_2";
				Link.l2 = StringFromKey("Pirates_Shipyard_247");
				Link.l2.go = "Exit";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_248", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_249");
				Link.l1.go = "TuningLose";
			}
		break;

		case "ship_tunning_TurnRate_again_2":
			checkMatherial(Pchar, NPChar, GOOD_LINEN, "jewelry3", "chest");

			if (sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				dialog.text = StringFromKey("Pirates_Shipyard_250", pchar);
				link.l1 = StringFromKey("Pirates_Shipyard_251");
				link.l1.go = "ship_tunning_TurnRate_complite";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_252", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3));
				link.l1 = StringFromKey("Pirates_Shipyard_253");
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_395", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3)));
			}
		break;

		case "ship_tunning_TurnRate_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(NPChar.SelectedShip.Type)];
			// изменим
			if (!CheckAttribute(shTo, "Bonus_TurnRate"))
			{
				shTo.TurnRate = (stf(shTo.TurnRate) + stf(shTo.TurnRate) / 5.0);
			}
			else
			{
				shTo.TurnRate = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
			}
			shTo.Tuning.TurnRate = true;
			// finish <--
			TEV.AchievementData.Tuning.TurnRate = true;
			dialog.Text = StringFromKey("Pirates_Shipyard_254");
			Link.l1 = StringFromKey("Pirates_Shipyard_255");
			Link.l1.go = "TuningEnd";
		break;
		////////////////////////////////////////// HP ////////////////////////////////////////////////////
		case "ship_tunning_HP":
			s1 = StringFromKey("Pirates_Shipyard_256", shipHP);

			s1 = StringFromKey("Pirates_Shipyard_257", s1, HPMatherial1);
			s1 = StringFromKey("Pirates_Shipyard_258", s1, HPMatherial2, HPMatherial3, FindMoneyString(HPWorkPrice));
			dialog.Text = s1;
			Link.l1 = StringFromKey("Pirates_Shipyard_259");
			Link.l1.go = "ship_tunning_HP_start";
			Link.l2 = StringFromKey("Pirates_Shipyard_260");
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = StringFromKey("Pirates_Shipyard_261");
				Link.l3.go = "Discount_1";
			}

		break;

		case "ship_tunning_HP_start":
			amount = HPWorkPrice;
			if (makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
				NPChar.Tuning.Money = amount;
				NPChar.Tuning.Matherial1 = HPMatherial1; // GOOD_EBONY
				NPChar.Tuning.Matherial2 = HPMatherial2; //  GOOD_SANDAL
				NPChar.Tuning.Matherial3 = HPMatherial3;
				NPChar.Tuning.ShipType = NPChar.SelectedShip.Type;
				NPChar.Tuning.ShipName = RealShips[sti(NPChar.SelectedShip.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");

				NPChar.Tuning.TuningNode = "ship_tunning_HP_again";
				dialog.text = StringFromKey("Pirates_Shipyard_262");
				link.l1 = StringFromKey("Pirates_Shipyard_263", pchar);
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_396", XI_ConvertString(RealShips[sti(NPChar.SelectedShip.Type)].BaseName), NPChar.Tuning.Matherial1, NPChar.Tuning.Matherial2, NPChar.Tuning.Matherial3, FindMoneyString(sti(NPChar.Tuning.Money))));
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Shipyard_264");
				link.l1 = StringFromKey("Pirates_Shipyard_265");
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_HP_again":
			if (GetShipOwnerInSquadron(NPChar))
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_266", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_267");
				Link.l1.go = "ship_tunning_HP_again_2";
				Link.l2 = StringFromKey("Pirates_Shipyard_268");
				Link.l2.go = "Exit";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_269", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_270");
				Link.l1.go = "TuningLose";
			}
		break;

		case "ship_tunning_HP_again_2":
			checkMatherial(Pchar, NPChar, GOOD_MAHOGANY, "jewelry17", "chest");

			if (sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				dialog.text = StringFromKey("Pirates_Shipyard_271", pchar);
				link.l1 = StringFromKey("Pirates_Shipyard_272");
				link.l1.go = "ship_tunning_HP_complite";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_273", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3));
				link.l1 = StringFromKey("Pirates_Shipyard_274");
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_397", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3)));
			}
		break;

		case "ship_tunning_HP_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(NPChar.SelectedShip.Type)];
			// изменим
			if (!CheckAttribute(shTo, "Bonus_HP"))
			{
				shTo.HP = sti(shTo.HP) + makeint(sti(shTo.HP) / 5);
			}
			else
			{
				shTo.HP = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
			}
			shTo.Tuning.HP = true;
			// finish <--
			TEV.AchievementData.Tuning.HP = true;
			dialog.Text = StringFromKey("Pirates_Shipyard_275");
			Link.l1 = StringFromKey("Pirates_Shipyard_276");
			Link.l1.go = "TuningEnd";
		//
		break;
		////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
		case "ship_tunning_WindAgainst":
			s1 = StringFromKey("Pirates_Shipyard_277", FloatToString(shipWindAgainst, 2));

			s1 = StringFromKey("Pirates_Shipyard_278", s1, WindAgainstMatherial1);
			s1 = StringFromKey("Pirates_Shipyard_279", s1, WindAgainstMatherial2, WindAgainstMatherial3, FindMoneyString(WindAgainstWorkPrice));
			dialog.Text = s1;
			Link.l1 = StringFromKey("Pirates_Shipyard_280");
			Link.l1.go = "ship_tunning_WindAgainst_start";
			Link.l2 = StringFromKey("Pirates_Shipyard_281");
			Link.l2.go = "ship_tunning_not_now";
			if (!CheckAttribute(NPChar, "Discount"))
			{
				Link.l3 = StringFromKey("Pirates_Shipyard_282");
				Link.l3.go = "Discount_1";
			}
		break;

		case "ship_tunning_WindAgainst_start":
			amount = WindAgainstWorkPrice;
			if (makeint(Pchar.money) >= amount)
			{
				AddMoneyToCharacter(Pchar, -amount);
				NPChar.Tuning.Money = amount;
				NPChar.Tuning.Matherial1 = WindAgainstMatherial1;
				NPChar.Tuning.Matherial2 = WindAgainstMatherial2;
				NPChar.Tuning.Matherial3 = WindAgainstMatherial3;
				NPChar.Tuning.ShipType = NPChar.SelectedShip.Type;
				NPChar.Tuning.ShipName = RealShips[sti(NPChar.SelectedShip.Type)].BaseName;
				DeleteAttribute(NPChar, "Discount");
				NPChar.Tuning.TuningNode = "ship_tunning_WindAgainst_again";
				dialog.text = StringFromKey("Pirates_Shipyard_283");
				link.l1 = StringFromKey("Pirates_Shipyard_284", pchar);
				link.l1.go = "Exit";

				ReOpenQuestHeader("ShipTuning");
				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_398", XI_ConvertString(RealShips[sti(NPChar.SelectedShip.Type)].BaseName), NPChar.Tuning.Matherial1, NPChar.Tuning.Matherial2, NPChar.Tuning.Matherial3, FindMoneyString(sti(NPChar.Tuning.Money))));
			}
			else
			{
				dialog.text = StringFromKey("Pirates_Shipyard_285");
				link.l1 = StringFromKey("Pirates_Shipyard_286");
				link.l1.go = "Exit";
			}
		break;

		case "ship_tunning_WindAgainst_again":
			if (GetShipOwnerInSquadron(NPChar))
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_287", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_288");
				Link.l1.go = "ship_tunning_WindAgainst_again_2";
				Link.l2 = StringFromKey("Pirates_Shipyard_289");
				Link.l2.go = "Exit";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_290", pchar);
				Link.l1 = StringFromKey("Pirates_Shipyard_291");
				Link.l1.go = "TuningLose";
			}
		break;

		case "ship_tunning_WindAgainst_again_2":
			checkMatherial(Pchar, NPChar, GOOD_COTTON, "jewelry4", "chest");

			if (sti(NPChar.Tuning.Matherial2) < 1 && sti(NPChar.Tuning.Matherial1) < 1 && sti(NPChar.Tuning.Matherial3) < 1)
			{
				dialog.text = StringFromKey("Pirates_Shipyard_292", pchar);
				link.l1 = StringFromKey("Pirates_Shipyard_293");
				link.l1.go = "ship_tunning_WindAgainst_complite";
			}
			else
			{
				dialog.Text = StringFromKey("Pirates_Shipyard_294", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3));
				link.l1 = StringFromKey("Pirates_Shipyard_295");
				link.l1.go = "Exit";

				AddQuestRecord("ShipTuning", "t1");
				AddQuestUserData("ShipTuning", "sText", StringFromKey("Pirates_Shipyard_399", sti(NPChar.Tuning.Matherial1), sti(NPChar.Tuning.Matherial2), sti(NPChar.Tuning.Matherial3)));
			}
		break;

		case "ship_tunning_WindAgainst_complite":
			AddTimeToCurrent(6, 30);
			shTo = &RealShips[sti(NPChar.SelectedShip.Type)];
			// изменим
			shTo.WindAgainstSpeed = FloatToString(stf(shTo.WindAgainstSpeed) + 0.5 * stf(shTo.WindAgainstSpeed) / stf(shTo.Class) + 0.005, 2);
			shTo.Tuning.WindAgainst = true;
			// finish <--
			TEV.AchievementData.Tuning.WindAgainst = true; // для ачивки
			dialog.Text = StringFromKey("Pirates_Shipyard_296");
			Link.l1 = StringFromKey("Pirates_Shipyard_297");
			Link.l1.go = "TuningEnd";
		break;
		///////////////////////////////  квестовые ветки
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Pirates_Shipyard_300", RandPhraseSimple(
								StringFromKey("Pirates_Shipyard_298"),
								StringFromKey("Pirates_Shipyard_299"))),
						StringFromKey("Pirates_Shipyard_301"),
						StringFromKey("Pirates_Shipyard_302"),
						StringFromKey("Pirates_Shipyard_303"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Pirates_Shipyard_306", RandPhraseSimple(
								StringFromKey("Pirates_Shipyard_304", pchar),
								StringFromKey("Pirates_Shipyard_305"))),
						StringFromKey("Pirates_Shipyard_307"),
						StringFromKey("Pirates_Shipyard_308"),
						StringFromKey("Pirates_Shipyard_309"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (!CheckAttribute(npchar, "Step_Door"))
			{
				link.l2 = StringFromKey("Pirates_Shipyard_310");
				link.l2.go = "Step_Door_1";
			}
			// ==> Перехват на квесты
			if (CheckAttribute(pchar, "questTemp.State.SeekBible"))// квест №2, поиск Евангелие
			{
				if (!CheckCharacterItem(pchar, "Bible"))
				{
					dialog.text = StringFromKey("Pirates_Shipyard_311");
					link.l2 = StringFromKey("Pirates_Shipyard_312");
					link.l2.go = "Step_S2_1";
				}
				else
				{
					dialog.text = StringFromKey("Pirates_Shipyard_313", pchar);
					link.l2 = StringFromKey("Pirates_Shipyard_314");
					link.l2.go = "exit";
				}
			}
			if (pchar.questTemp.piratesLine == "KillLoy_toAlexus")
			{
				link.l1 = StringFromKey("Pirates_Shipyard_315");
				link.l1.go = "PL_Q3_1";
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.T1") && pchar.questTemp.piratesLine.T1 == "KillLoy_GoodWork") //if (pchar.questTemp.piratesLine.T1 == "KillLoy_GoodWork")
			{
				link.l1 = StringFromKey("Pirates_Shipyard_316");
				link.l1.go = "PL_Q3_SW1";
			}
			if (CheckAttribute(pchar, "questTemp.piratesLine.T1") && pchar.questTemp.piratesLine.T1 == "KillLoy_LoyIsDied") //if (pchar.questTemp.piratesLine.T1 == "KillLoy_LoyIsDied")
			{
				link.l1 = StringFromKey("Pirates_Shipyard_317");
				link.l1.go = "PL_Q3_SW2";
			}
			if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAlexus"))
			{
				link.l1 = StringFromKey("Pirates_Shipyard_318");
				link.l1.go = "Al_ShipLetters_1";// генератор  "Найденные документы"
				pchar.questTemp.different.GiveShipLetters.speakAlexus = true;
			}
			if (pchar.questTemp.BlueBird == "toSeekBermudes") //шебека Синяя Птица
			{
				link.l1 = StringFromKey("Pirates_Shipyard_319");
				link.l1.go = "BlueBird_1";
			}
		// <== Перехват на квесты
		break;
		//*************************** Генератор - "Найденные судовые документы" **************

		case "Al_ShipLetters_1":
			dialog.text = StringFromKey("Pirates_Shipyard_320");
			s1 = StringFromKey("Pirates_Shipyard_321");
			s1 = StringFromKey("Pirates_Shipyard_322", s1);
			link.l1 = s1;
			link.l1.go = "Al_ShipLetters_2";
		break;
		case "Al_ShipLetters_2":
			s1 = StringFromKey("Pirates_Shipyard_323", pchar);
			s1 = StringFromKey("Pirates_Shipyard_324", s1, FindMoneyString(sti(pchar.questTemp.different.GiveShipLetters.price5)));
			dialog.text = s1;
			link.l1 = StringFromKey("Pirates_Shipyard_325", pchar);
			link.l1.go = "Al_ShipLetters_3";
			link.l2 = StringFromKey("Pirates_Shipyard_326");
			link.l2.go = "exit";
		break;
		case "Al_ShipLetters_3":
			TakeItemFromCharacter(pchar, "CaptainBook");
			addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5));
			ChangeCharacterReputation(pchar, -1);
			OfficersReaction("bad");
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер
			AddQuestRecord("GiveShipLetters", "9");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//*************************** Пиратка, квест №3, поиски Лоу ***************************
		case "PL_Q3_1":
			dialog.text = StringFromKey("Pirates_Shipyard_327");
			link.l1 = StringFromKey("Pirates_Shipyard_328");
			link.l1.go = "PL_Q3_3";
			link.l2 = StringFromKey("Pirates_Shipyard_329");
			link.l2.go = "PL_Q3_2";
		break;
		case "PL_Q3_2":
			dialog.text = StringFromKey("Pirates_Shipyard_330", pchar);
			link.l1 = StringFromKey("Pirates_Shipyard_331");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "10");
			pchar.questTemp.piratesLine = "KillLoy_toJackman";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID("Jackman"), "Pir_Line");
		break;
		case "PL_Q3_3":
			dialog.text = StringFromKey("Pirates_Shipyard_332");
			link.l1 = StringFromKey("Pirates_Shipyard_333");
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = StringFromKey("Pirates_Shipyard_334");
			link.l1 = StringFromKey("Pirates_Shipyard_335");
			link.l1.go = "PL_Q3_5";
		break;
		case "PL_Q3_5":
			dialog.text = StringFromKey("Pirates_Shipyard_336");
			link.l1 = StringFromKey("Pirates_Shipyard_337");
			link.l1.go = "PL_Q3_6";
		break;
		case "PL_Q3_6":
			dialog.text = StringFromKey("Pirates_Shipyard_338");
			link.l1 = StringFromKey("Pirates_Shipyard_339", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_3_KillLoy", "11");
			pchar.questTemp.piratesLine = "KillLoy_toTavernAgain";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID("Pirates_tavernkeeper"), "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID("Jackman"), "Pir_Line");
		//
		break;

		case "PL_Q3_SW1":
			dialog.text = StringFromKey("Pirates_Shipyard_340", pchar);
			link.l1 = StringFromKey("Pirates_Shipyard_341", pchar);
			link.l1.go = "exit";
		break;
		case "PL_Q3_SW2":
			dialog.text = StringFromKey("Pirates_Shipyard_342");
			link.l1 = StringFromKey("Pirates_Shipyard_343");
			link.l1.go = "PL_Q3_SW3";
		break;
		case "PL_Q3_SW3":
			dialog.text = StringFromKey("Pirates_Shipyard_344");
			link.l1 = StringFromKey("Pirates_Shipyard_345");
			link.l1.go = "exit";
		break;
		//*************************** шебека Синяя Птица ***************************
		case "BlueBird_1":
			dialog.text = StringFromKey("Pirates_Shipyard_346");
			link.l1 = StringFromKey("Pirates_Shipyard_347");
			link.l1.go = "BlueBird_2";
		break;
		case "BlueBird_2":
			dialog.text = StringFromKey("Pirates_Shipyard_348");
			link.l1 = StringFromKey("Pirates_Shipyard_349");
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = StringFromKey("Pirates_Shipyard_350");
			link.l1 = StringFromKey("Pirates_Shipyard_351");
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = StringFromKey("Pirates_Shipyard_352", pchar);
			link.l1 = StringFromKey("Pirates_Shipyard_353");
			link.l1.go = "exit";
			AddQuestRecord("Xebeca_BlueBird", "5");
			pchar.questTemp.BlueBird = "toCavern";
			RemoveLandQuestMark_Main(npchar, "Xebeca_BlueBird");
			pchar.quest.BlueBird_inCavern.win_condition.l1 = "locator";
			pchar.quest.BlueBird_inCavern.win_condition.l1.location = "Bermudes_Cavern";
			pchar.quest.BlueBird_inCavern.win_condition.l1.locator_group = "quest";
			pchar.quest.BlueBird_inCavern.win_condition.l1.locator = "BlueBird";
			pchar.quest.BlueBird_inCavern.function = "BlueBird_inCavern";
			LAi_LocationDisableMonstersGen("Bermudes_Cavern", true); //монстров не генерить
			LAi_LocationDisableOfficersGen("Bermudes_Cavern", true); //офицеров не пускать
		break;
		//*************************** Открывание двери ***************************
		case "Step_Door_1":
			dialog.text = StringFromKey("Pirates_Shipyard_354");
			if (sti(pchar.money) >= 20000)
			{
				link.l1 = StringFromKey("Pirates_Shipyard_355");
				link.l1.go = "Step_Door_2";
			}
			else
			{
				link.l1 = StringFromKey("Pirates_Shipyard_356");
				link.l1.go = "Step_Door_3";
			}
			link.l2 = StringFromKey("Pirates_Shipyard_357");
			link.l2.go = "exit";
		break;
		case "Step_Door_2":
			npchar.Step_Door = true; // fix
			dialog.text = StringFromKey("Pirates_Shipyard_358");
			link.l1 = StringFromKey("Pirates_Shipyard_359", npchar.name);
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			AddMoneyToCharacter(pchar, -20000);
			pchar.quest.CloseBermudesDungeonDoor.win_condition.l1 = "MapEnter";
			pchar.quest.CloseBermudesDungeonDoor.win_condition = "CloseBermudesDungeonDoor";
		break;
		case "Step_Door_3":
			dialog.text = StringFromKey("Pirates_Shipyard_360");
			link.l1 = StringFromKey("Pirates_Shipyard_361");
			link.l1.go = "exit";
		break;
		//*************************** Квест №2, диалоги с Франциско на выходе из Инквизиии ***************************
		case "Step_S2_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Pirates_Shipyard_362"),
						StringFromKey("Pirates_Shipyard_363"),
						StringFromKey("Pirates_Shipyard_364"),
						StringFromKey("Pirates_Shipyard_365"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Pirates_Shipyard_366"),
						StringFromKey("Pirates_Shipyard_367", pchar),
						StringFromKey("Pirates_Shipyard_368"),
						StringFromKey("Pirates_Shipyard_369", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S2_2", "none", "none", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_S2_2":
			dialog.text = StringFromKey("Pirates_Shipyard_370");
			link.l1 = StringFromKey("Pirates_Shipyard_371");
			link.l1.go = "Step_S2_3";
		break;
		case "Step_S2_3":
			dialog.text = StringFromKey("Pirates_Shipyard_372", pchar);
			link.l1 = StringFromKey("Pirates_Shipyard_373");
			link.l1.go = "Step_S2_4";
		break;
		case "Step_S2_4":
			dialog.text = StringFromKey("Pirates_Shipyard_374");
			link.l1 = StringFromKey("Pirates_Shipyard_375");
			link.l1.go = "Step_S2_5";
		break;
		case "Step_S2_5":
			dialog.text = StringFromKey("Pirates_Shipyard_376");
			link.l1 = StringFromKey("Pirates_Shipyard_377");
			link.l1.go = "Step_S2_6";
		break;
		case "Step_S2_6":
			dialog.text = StringFromKey("Pirates_Shipyard_378");
			link.l1 = StringFromKey("Pirates_Shipyard_379");
			link.l1.go = "exit";
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", false);
			LocatorReloadEnterDisable("Shore3", "reload2_back", false);
			Pchar.quest.Inquisition_fightInDangeon.win_condition.l1 = "location";
			Pchar.quest.Inquisition_fightInDangeon.win_condition.l1.location = "Bermudes_Dungeon";
			Pchar.quest.Inquisition_fightInDangeon.win_condition = "Inquisition_fightInDangeon";
			pchar.GenQuestBox.Terks_Grot = true;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry5 = 200;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry17 = 300;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade33 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade28 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade34 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade32 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade23 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol5 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol4 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.pistol6 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potion2 = 5;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian18 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry7 = 5;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.blade5 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potion2 = 10;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.potionwine = 3;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry1 = 100;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry2 = 80;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry3 = 60;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry4 = 45;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.incas_collection = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.chest = 5;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.jewelry14 = 10;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian6 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian11 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian15 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian12 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.indian18 = 1;
			pchar.GenQuestBox.Bermudes_Dungeon.box1.items.Bible = 1;
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;

	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void checkMatherial(ref Pchar, ref NPChar, int good1, int good2, int good3)
{
	int amount;

	amount = GetSquadronGoods(Pchar, good1) - sti(NPChar.Tuning.Matherial1);
	if (amount < 0)
	{
		amount = amount + sti(NPChar.Tuning.Matherial1);
	}
	else
	{
		amount = sti(NPChar.Tuning.Matherial1);
	}
	RemoveCharacterGoods(Pchar, good1, amount);
	NPChar.Tuning.Matherial1 = sti(NPChar.Tuning.Matherial1) - amount;

	amount = GetCharacterItem(pchar, good2) - sti(NPChar.Tuning.Matherial2);
	if (amount < 0)
	{
		amount = amount + sti(NPChar.Tuning.Matherial2);
	}
	else
	{
		amount = sti(NPChar.Tuning.Matherial2);
	}
	TakeNItems(pchar, good2, -amount);
	NPChar.Tuning.Matherial2 = sti(NPChar.Tuning.Matherial2) - amount;

	amount = GetCharacterItem(pchar, good3) - sti(NPChar.Tuning.Matherial3);
	if (amount < 0)
	{
		amount = amount + sti(NPChar.Tuning.Matherial3);
	}
	else
	{
		amount = sti(NPChar.Tuning.Matherial3);
	}
	TakeNItems(pchar, good3, -amount);
	NPChar.Tuning.Matherial3 = sti(NPChar.Tuning.Matherial3) - amount;
}

void checkResoursesForRepairing(ref Pchar, ref NPChar, int good1, int good2, int good3)
{
	int amount;

	amount = GetSquadronGoods(Pchar, good1) - sti(NPChar.Tuning.Matherial1);
	if (amount < 0)
	{
		amount = amount + sti(NPChar.Tuning.Matherial1);
	}
	else
	{
		amount = sti(NPChar.Tuning.Matherial1);
	}
	RemoveCharacterGoods(Pchar, good1, amount);
	NPChar.Tuning.Matherial1 = sti(NPChar.Tuning.Matherial1) - amount;

	amount = GetSquadronGoods(Pchar, good2) - sti(NPChar.Tuning.Matherial2);
	if (amount < 0)
	{
		amount = amount + sti(NPChar.Tuning.Matherial2);
	}
	else
	{
		amount = sti(NPChar.Tuning.Matherial2);
	}
	RemoveCharacterGoods(Pchar, good2, amount);
	NPChar.Tuning.Matherial2 = sti(NPChar.Tuning.Matherial2) - amount;

	amount = GetSquadronGoods(Pchar, good3) - sti(NPChar.Tuning.Matherial3);
	if (amount < 0)
	{
		amount = amount + sti(NPChar.Tuning.Matherial3);
	}
	else
	{
		amount = sti(NPChar.Tuning.Matherial3);
	}
	RemoveCharacterGoods(Pchar, good3, amount);
	NPChar.Tuning.Matherial3 = sti(NPChar.Tuning.Matherial3) - amount;

}

string StartOrSelectTuningShip(ref NPChar)
{
	for (int shipsQty = 0; shipsQty < COMPANION_MAX; shipsQty++)
	{
		if (GetCompanionIndex(pchar, shipsQty) != -1)
		{
			if (shipsQty > 0) return "ship_tuning_select";
		}
	}
	NPChar.SelectedShip.Type = pchar.ship.type;
	return "ship_tuning_start";
}

int GetShipOwnerInSquadron(ref NPChar)
{
	ref rShipOwner;
	for (int shipsQty = 0; shipsQty < COMPANION_MAX; shipsQty++)
	{
		int iNpcIndex = GetCompanionIndex(pchar, shipsQty);
		if (iNpcIndex >= 0)
		{
			rShipOwner = &characters[iNpcIndex];
			if (NPChar.Tuning.ShipType == rShipOwner.Ship.Type && NPChar.Tuning.ShipName == RealShips[sti(rShipOwner.Ship.Type)].BaseName)
				return GetCharacterIndex(rShipOwner.id);
		}
	}
	return 0;
}
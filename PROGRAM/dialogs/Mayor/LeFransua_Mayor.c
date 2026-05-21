// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
	string attr, sTemp;
	int i = 1;

	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("LeFransua_Mayor_3", RandPhraseSimple(
								StringFromKey("LeFransua_Mayor_1"),
								StringFromKey("LeFransua_Mayor_2"))),
						StringFromKey("LeFransua_Mayor_4"),
						StringFromKey("LeFransua_Mayor_5"),
						StringFromKey("LeFransua_Mayor_6"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("LeFransua_Mayor_9", RandPhraseSimple(
								StringFromKey("LeFransua_Mayor_7", pchar),
								StringFromKey("LeFransua_Mayor_8"))),
						StringFromKey("LeFransua_Mayor_10"),
						StringFromKey("LeFransua_Mayor_11"),
						StringFromKey("LeFransua_Mayor_12", NPChar.name), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "takeRumour"))
			{
				attr = "l" + i; i++;
				link.(attr) = StringFromKey("LeFransua_Mayor_13");
				link.(attr).go = "SharpPearl_1";
			}
			if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
			{
				attr = "l" + i; i++;
				link.(attr) = StringFromKey("LeFransua_Mayor_14");
				link.(attr).go = "Mushket";
			}
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				attr = "l" + i; i++;
				if (CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
				{
					link.(attr) = StringFromKey("LeFransua_Mayor_15");
					link.(attr).go = "CapComission1";
				}
				if (CheckAttribute(pchar, "GenQuest.CaptainComission.PirateShips"))
				{
					link.(attr) = StringFromKey("LeFransua_Mayor_16", NPChar.name);
					link.(attr).go = "CapComission3";
				}
				if (CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
				{
					link.(attr) = StringFromKey("LeFransua_Mayor_17");
					link.(attr).go = "CapComission6";
				}
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin")
			{
				attr = "l" + i; i++;
				link.(attr) = StringFromKey("LeFransua_Mayor_18", pchar);
				link.(attr).go = "Marginpassenger";
				if (CheckAttribute(NPChar, "GenQuest.Business"))
				{
					link.(attr) = StringFromKey("LeFransua_Mayor_19", NPChar.name);
					link.(attr).go = "Marginpassenger_3";
				}
			}
		break;

		case "Mushket":
			dialog.text = StringFromKey("LeFransua_Mayor_20");
			link.l1 = StringFromKey("LeFransua_Mayor_21");
			link.l1.go = "Mushket_1";
			DeleteAttribute(pchar, "questTemp.mushket2x2");
		break;
		case "Mushket_1":
			dialog.text = StringFromKey("LeFransua_Mayor_22");
			link.l1 = StringFromKey("LeFransua_Mayor_23");
			link.l1.go = "Mushket_2";
		break;
		case "Mushket_2":
			dialog.text = StringFromKey("LeFransua_Mayor_24", pchar);
			link.l1 = StringFromKey("LeFransua_Mayor_25");
			link.l1.go = "exit";
			SetMushketCapitainInWorld(false);
			pchar.questTemp.mushket2x2_stid = true;
			SaveCurrentQuestDateParam("questTemp.mushket2x2_stid");
			AddQuestRecord("SeekDoubleMushket", "2_2");

			AddLandQuestMark_Main(CharacterFromID("PortoBello_Tavernkeeper"), "SeekDoubleMushket");

			RemoveLandQuestMark_Main(CharacterFromID("Jackman"), "SeekDoubleMushket");
			RemoveLandQuestMark_Main(npchar, "SeekDoubleMushket");
		break;

		case "CapComission1":
			dialog.text = StringFromKey("LeFransua_Mayor_26");
			link.l1 = StringFromKey("LeFransua_Mayor_27", pchar.GenQuest.CaptainComission.SlaveName);
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
			pchar.GenQuest.CaptainComission.toPlantator = GetRandomPlantation();
		break;

		case "CapComission2":
			if (HasSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_Mine"))
				sTemp = StringFromKey("LeFransua_Mayor_28", XI_ConvertString("Colony" + GetSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_", 0) + "Gen"));
			else
				sTemp = StringFromKey("LeFransua_Mayor_29", XI_ConvertString("Colony" + GetSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_", 0) + "Gen"));
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = StringFromKey("LeFransua_Mayor_30", sTemp);
				link.l1 = StringFromKey("LeFransua_Mayor_31");
				link.l1.go = "CapComission2_1";
			}
			else
			{
				pchar.quest.CaptainComission_SellSlave.over = "yes";
				dialog.text = StringFromKey("LeFransua_Mayor_32", pchar, sTemp);
				link.l1 = StringFromKey("LeFransua_Mayor_33", pchar, NPChar.name);
				link.l1.go = "CapComission2_2";
				if (makeint(pchar.money) > 150000)
				{
					link.l2 = StringFromKey("LeFransua_Mayor_34");
					link.l2.go = "CapComission2_3";
				}
			}
		break;

		case "CapComission2_1":
			dialog.text = StringFromKey("LeFransua_Mayor_35", pchar);
			link.l1 = StringFromKey("LeFransua_Mayor_36", pchar);
			link.l1.go = "CapComission2_11";
		break;

		case "CapComission2_11":
			dialog.text = StringFromKey("LeFransua_Mayor_37", pchar);
			link.l1 = StringFromKey("LeFransua_Mayor_38");
			link.l1.go = "CapComission2_12";
		break;

		case "CapComission2_12":
			dialog.text = StringFromKey("LeFransua_Mayor_39");
			link.l1 = StringFromKey("LeFransua_Mayor_40");
			link.l1.go = "exit";
			if (HasSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_Mine"))
				sTemp = StringFromKey("LeFransua_Mayor_41", XI_ConvertString("Colony" + GetSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_", 0) + "Gen"));
			else
				sTemp = StringFromKey("LeFransua_Mayor_42", XI_ConvertString("Colony" + GetSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_", 0) + "Gen"));
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sColony", sTemp);
			AddQuestUserData("CaptainComission1", "sIsland", XI_ConvertString(GetIslandNameByCity(GetSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_", 0)) + "Acc"));
		break;

		case "CapComission2_2":
			if (rand(1) == 0)
			{
				dialog.text = StringFromKey("LeFransua_Mayor_43");
				link.l1 = StringFromKey("LeFransua_Mayor_44");
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = StringFromKey("LeFransua_Mayor_45", pchar.name);
				link.l1 = StringFromKey("LeFransua_Mayor_46");
				link.l1.go = "exit";
				if (!CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
				{
					AddQuestRecord("CaptainComission1", "31");
					AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
				}
				pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			}
		break;

		case "CapComission2_2_1":
			dialog.text = StringFromKey("LeFransua_Mayor_47");
			link.l1 = StringFromKey("LeFransua_Mayor_48");
			link.l1.go = "CapComission2_2_2";
		break;

		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			dialog.text = StringFromKey("LeFransua_Mayor_49", GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM), XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen"), pchar.GenQuest.CaptainComission.ShipName1, pchar.GenQuest.CaptainComission.ShipName2, XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"));
			link.l1 = StringFromKey("LeFransua_Mayor_50");
			link.l1.go = "CapComission2_2_3";
		break;

		case "CapComission2_2_3":
			dialog.text = StringFromKey("LeFransua_Mayor_51");
			link.l1 = StringFromKey("LeFransua_Mayor_52");
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "24");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
			AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
			AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat"));
			AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Pre"));
			pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
			pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
			pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips";
			SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
			pchar.GenQuest.CaptainComission.PirateShips = "goaway";
		break;

		case "CapComission2_3":
			dialog.text = StringFromKey("LeFransua_Mayor_53");
			link.l1 = StringFromKey("LeFransua_Mayor_54");
			link.l1.go = "CapComission2_31";
		break;

		case "CapComission2_31":
			dialog.text = StringFromKey("LeFransua_Mayor_55");
			link.l1 = StringFromKey("LeFransua_Mayor_56");
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			addMoneyToCharacter(pchar, -150000);
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission3":
			dialog.text = StringFromKey("LeFransua_Mayor_57", GetFullName(pchar));
			if (pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = StringFromKey("LeFransua_Mayor_58", pchar);
				link.l1.go = "CapComission4";
			}
			else
			{
				if (pchar.GenQuest.CaptainComission.PirateShips == "died")
				{
					link.l1 = StringFromKey("LeFransua_Mayor_59", pchar);
					link.l1.go = "CapComission5";
				}
			}
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		break;

		case "CapComission4":
			dialog.text = StringFromKey("LeFransua_Mayor_60");
			link.l1 = StringFromKey("LeFransua_Mayor_61");
			link.l1.go = "CapComission4_1";
			link.l2 = StringFromKey("LeFransua_Mayor_62", NPChar.name);
			link.l2.go = "CapComission4_2";
		break;

		case "CapComission4_1":
			dialog.text = StringFromKey("LeFransua_Mayor_63");
			link.l1 = StringFromKey("LeFransua_Mayor_64");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "ла"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		break;

		case "CapComission4_2":
			dialog.text = StringFromKey("LeFransua_Mayor_65");
			link.l1 = StringFromKey("LeFransua_Mayor_66");
			link.l1.go = "CapComission4_4";
			if (sti(pchar.money) >= 200000)
			{
				link.l2 = StringFromKey("LeFransua_Mayor_67");
				link.l2.go = "CapComission4_5";
			}
		break;

		case "CapComission4_4":
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("CaptainComission1", "28");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			DialogExit();
		break;

		case "CapComission4_5":
			dialog.text = StringFromKey("LeFransua_Mayor_68");
			link.l1 = StringFromKey("LeFransua_Mayor_69");
			link.l1.go = "exit";
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission5":
			dialog.text = StringFromKey("LeFransua_Mayor_70", pchar);
			link.l1 = StringFromKey("LeFransua_Mayor_71");
			link.l1.go = "exit";
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission6":
			dialog.text = StringFromKey("LeFransua_Mayor_72", pchar);
			link.l1 = StringFromKey("LeFransua_Mayor_73", pchar, NPChar.name);
			link.l1.go = "CapComission2_2";
			if (makeint(pchar.money) > 150000)
			{
				link.l2 = StringFromKey("LeFransua_Mayor_74");
				link.l2.go = "CapComission2_3";
			}
		break;

		//Захват пассажиров
		case "Marginpassenger":
			dialog.text = StringFromKey("LeFransua_Mayor_75", pchar);
			link.l1 = StringFromKey("LeFransua_Mayor_76", pchar);
			link.l1.go = "Marginpassenger_1";
			NPChar.GenQuest.Business = true;
		break;

		case "Marginpassenger_1":
			dialog.text = StringFromKey("LeFransua_Mayor_77", pchar);
			link.l1 = StringFromKey("LeFransua_Mayor_78", pchar);
			link.l1.go = "Marginpassenger_2";
		break;

		case "Marginpassenger_2":
			dialog.text = StringFromKey("LeFransua_Mayor_79", pchar);
			link.l1 = StringFromKey("LeFransua_Mayor_80");
			link.l1.go = "Marginpassenger_3";
		break;

		case "Marginpassenger_3":
			dialog.text = StringFromKey("LeFransua_Mayor_81");
			link.l1 = StringFromKey("LeFransua_Mayor_82", pchar.GenQuest.Marginpassenger.Text, XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City + "Gen")); //TODO: чек падежа
			link.l1.go = "Marginpassenger_4";
		break;

		case "Marginpassenger_4":
			int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Money) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance));
			dialog.text = StringFromKey("LeFransua_Mayor_83", FindMoneyString(iTemp));
			link.l1 = StringFromKey("LeFransua_Mayor_84", pchar);
			link.l1.go = "Marginpassenger_money";
			link.l2 = StringFromKey("LeFransua_Mayor_85", pchar);
			link.l2.go = "Marginpassenger_offer";
		break;

		case "Marginpassenger_money":
			dialog.text = StringFromKey("LeFransua_Mayor_86");
			link.l1 = StringFromKey("LeFransua_Mayor_87");
			link.l1.go = "Marginpassenger_money_1";
		break;

		case "Marginpassenger_money_1":
			int iMoney = makeint(sti(pchar.GenQuest.Marginpassenger.Money) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance));
			dialog.text = StringFromKey("LeFransua_Mayor_88");
			link.l1 = StringFromKey("LeFransua_Mayor_89");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, iMoney);
			ref sld = characterFromId("MarginPass");
			RemovePassenger(Pchar, sld);
			sld.lifeday = 0;
			AddQuestRecord("Marginpassenger", "12");
			AddQuestUserData("Marginpassenger", "sSum", FindMoneyString(iMoney));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;

		case "Marginpassenger_offer":
			pchar.GenQuest.Marginpassenger.Goods = GOOD_EBONY + rand(makeint(GOOD_SANDAL - GOOD_EBONY));
			pchar.GenQuest.Marginpassenger.GoodsQty = 220 + dRandEx(10, false) * 10;
			//TODO: адаптация к захвату колоний, смена аргументов на переменную наций
			if (drand(1) || !bWorldAlivePause)
			{
				SelectSouthshore();
				while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore)) SelectSouthshore();
				dialog.text = StringFromKey("LeFransua_Mayor_90", pchar, XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat")); //TODO: чек падежа
				link.l1 = StringFromKey("LeFransua_Mayor_91");
				link.l1.go = "Marginpassenger_offer_1";
			}
			else
			{
				SelectSouthcity();
				pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
				dialog.text = StringFromKey("LeFransua_Mayor_92", pchar, XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen"), pchar.GenQuest.Marginpassenger.ShipName1, XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Gen"));
				link.l1 = StringFromKey("LeFransua_Mayor_93");
				link.l1.go = "Marginpassenger_offer_2";
			}
			ref marginPass = CharacterFromId("MarginPass");
			RemovePassenger(Pchar, marginPass);
			marginPass.lifeday = 0;
			pchar.GenQuest.Marginpassenger = "final";
		break;

		case "Marginpassenger_offer_1":
			DialogExit();
			AddQuestRecord("Marginpassenger", "13");
			AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat"));
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
		break;

		case "Marginpassenger_offer_2":
			DialogExit();
			AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Gen"));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5 + dRandEx(2, false), false);
		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = StringFromKey("LeFransua_Mayor_94");
			link.l1 = StringFromKey("LeFransua_Mayor_95");
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
			SeaPearl_PiratesBaron_DelQuestMarks();
			SeaPearl_Hostess_AddQuestMarks();
		break;
		case "SharpPearl_2":
			AddQuestRecord("SharpPearl", "16");
			AddQuestUserData("SharpPearl", "sName", GetFullName(NPChar));

			dialog.text = StringFromKey("LeFransua_Mayor_96");
			link.l1 = StringFromKey("LeFransua_Mayor_97");
			link.l1.go = "exit";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

void SelectSouthshore()
{
	switch (dRandEx(6, 0))
	{
		case 0: pchar.GenQuest.Marginpassenger.Shore = "shore37"; break;
		case 1: pchar.GenQuest.Marginpassenger.Shore = "shore47"; break;
		case 2: pchar.GenQuest.Marginpassenger.Shore = "shore48"; break;
		case 3: pchar.GenQuest.Marginpassenger.Shore = "shore25"; break;
		case 4: pchar.GenQuest.Marginpassenger.Shore = "shore21"; break;
		case 5: pchar.GenQuest.Marginpassenger.Shore = "shore20"; break;
		case 6: pchar.GenQuest.Marginpassenger.Shore = "shore19"; break;
	}
}

void SelectSouthcity() //TODO: уж очень тут ограничены варианты городов, надо по нациями
{
	switch (dRandEx(2, 0))
	{
		case 0:
			pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Havana";
		break;

		case 1:
			pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago";
		break;

		case 2:
			pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
			pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo";
		break;
	}
}

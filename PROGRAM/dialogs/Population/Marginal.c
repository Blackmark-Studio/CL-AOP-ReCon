//Jason общий диалог уличных контриков
#include "DIALOGS\Rumours\Simple_rumors.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

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

	switch (Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = StringFromKey("Marginal_1");
					link.l1 = StringFromKey("Marginal_2");
					link.l1.go = "passenger";
					link.l2 = StringFromKey("Marginal_3");
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = StringFromKey("Marginal_7", LinkRandPhrase(
							StringFromKey("Marginal_4"),
							StringFromKey("Marginal_5"),
							StringFromKey("Marginal_6", pchar)));
				link.l1 = StringFromKey("Marginal_8", GetAddress_FormToNPC(NPChar));
				link.l1.go = "question";
				link.l2 = StringFromKey("Marginal_11", RandPhraseSimple(
							StringFromKey("Marginal_9"),
							StringFromKey("Marginal_10")));
				link.l2.go = "quests"; //(перессылка в файл города)
				link.l3 = StringFromKey("Marginal_12");
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
				//--> Эммануэль Пардаль
				if (CheckAttribute(pchar, "questTemp.EPL_Prologue"))
				{
					dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Marginal_66", TimeGreeting(), pchar.name), StringFromKey("Marginal_67", TimeGreeting(), pchar.name));
					link.l1 = StringFromKey("Marginal_68", TimeGreeting(), npchar.name);
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
					DeleteAttribute(link, "l3");
					npchar.quest.meeting = "0";
					break;
				}
				//<-- Эммануэль Пардаль
				break;
			}
			dialog.text = StringFromKey("Marginal_13");
			link.l1 = StringFromKey("Marginal_14");
			link.l1.go = "exit";
			link.l2 = StringFromKey("Marginal_17", RandPhraseSimple(
						StringFromKey("Marginal_15"),
						StringFromKey("Marginal_16")));
			link.l2.go = "quests"; //(перессылка в файл города)
		break;

		//----------------------------------------захват пассажиров для выкупа------------------------------------------
		case "passenger":
			DeleteAttribute(npchar, "talker");
			dialog.text = StringFromKey("Marginal_18");
			link.l1 = StringFromKey("Marginal_19");
			link.l1.go = "passenger_1";
		break;

		case "passenger_1":
			dialog.text = StringFromKey("Marginal_20");
			link.l1 = StringFromKey("Marginal_21");
			link.l1.go = "passenger_2";
			link.l2 = StringFromKey("Marginal_22");
			link.l2.go = "exit_quest";
		break;

		case "passenger_2":
			pchar.GenQuest.Marginpassenger.Money = 7000 + dRandEx(5, false) * 1000;
			dialog.text = StringFromKey("Marginal_23", pchar, FindMoneyString(sti(pchar.GenQuest.Marginpassenger.Money)));
			if (sti(pchar.money) >= sti(pchar.GenQuest.Marginpassenger.Money))
			{
				link.l1 = StringFromKey("Marginal_24");
				link.l1.go = "passenger_4";
			}
			link.l2 = StringFromKey("Marginal_25");
			link.l2.go = "passenger_3";
			link.l3 = StringFromKey("Marginal_26");
			link.l3.go = "exit_quest";
		break;

		case "passenger_3":
			dialog.text = StringFromKey("Marginal_27");
			link.l1 = StringFromKey("Marginal_28");
			link.l1.go = "passenger_wait";
		break;

		case "passenger_wait":
			DialogExit();
			SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
			npchar.dialog.currentnode = "passenger_repeat";
		break;

		case "passenger_repeat":
			dialog.text = StringFromKey("Marginal_29", pchar);
			if (sti(pchar.money) >= sti(pchar.GenQuest.Marginpassenger.Money))
			{
				link.l1 = StringFromKey("Marginal_30");
				link.l1.go = "passenger_4";
			}
			link.l2 = StringFromKey("Marginal_31");
			link.l2.go = "exit";
			Nextdiag.Tempnode = "passenger_repeat";
		break;

		case "passenger_4"://установка параметров
			pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Marginpassenger.Money));
			pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
			pchar.GenQuest.Marginpassenger.City = npchar.city;
			pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city);
			pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
			pchar.GenQuest.Marginpassenger.Days = 7 + drand(5);
			pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
			pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
			pchar.GenQuest.Marginpassenger.Chance = 0.8 + frand(0.4);
			SelectMarginpassengerParameter();
			log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
			dialog.text = StringFromKey("Marginal_32", pchar, FindDaysString(sti(pchar.GenQuest.Marginpassenger.Days)), GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name"))), pchar.GenQuest.Marginpassenger.ShipName, XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity + "Gen"), pchar.GenQuest.Marginpassenger.Text, pchar.GenQuest.Marginpassenger.q1Name, GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Acc")), pchar.GenQuest.Marginpassenger.Text1, XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity), pchar.GenQuest.Marginpassenger.q2Name, pchar.GenQuest.Marginpassenger.Text2, FindMoneyString(sti(pchar.GenQuest.Marginpassenger.Money) * 4));
			link.l1 = StringFromKey("Marginal_33");
			link.l1.go = "passenger_5";
		break;

		case "passenger_5":
			dialog.text = StringFromKey("Marginal_34", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name"))));
			link.l1 = StringFromKey("Marginal_35");
			link.l1.go = "exit_quest";
			npchar.lifeday = 0;
			ReOpenQuestHeader("Marginpassenger");
			AddQuestRecord("Marginpassenger", "1");
			AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City));
			AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity));
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
			AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
			AddQuestUserData("Marginpassenger", "sDay", FindDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
			AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Pre")));
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
			AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
			pchar.GenQuest.Marginpassenger = "begin";
			SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
		break;

		//замечание по обнаженному оружию от персонажей типа citizen
		/*case "CitizenNotBlade": //HardCoffee ref 
			dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Marginal_33"), StringFromKey("Marginal_34"));
			link.l1 = LinkRandPhrase(StringFromKey("Marginal_35"), StringFromKey("Marginal_36"), StringFromKey("Marginal_37"));
			link.l1.go = "exit";
		break;*/

		case "question":
			dialog.text = StringFromKey("Marginal_39", LinkRandPhrase(
						StringFromKey("Marginal_36"),
						StringFromKey("Marginal_37"),
						StringFromKey("Marginal_38")));
			link.l1 = StringFromKey("Marginal_43", LinkRandPhrase(
						StringFromKey("Marginal_40"),
						StringFromKey("Marginal_41"),
						StringFromKey("Marginal_42")));
			link.l1.go = "rumours_marginal";
		break;

		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (drand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "girl_" + (rand(9) + 1);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = StringFromKey("Marginal_44");
		switch (drand(4))
		{
			case 0:
				pchar.GenQuest.Marginpassenger.Text = StringFromKey("Marginal_45");
				pchar.GenQuest.Marginpassenger.Text1 = StringFromKey("Marginal_46");
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_store";
			break;
			case 1:
				pchar.GenQuest.Marginpassenger.Text = StringFromKey("Marginal_47");
				pchar.GenQuest.Marginpassenger.Text1 = StringFromKey("Marginal_48");
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_shipyard";
			break;
			case 2:
				pchar.GenQuest.Marginpassenger.Text = StringFromKey("Marginal_49");
				pchar.GenQuest.Marginpassenger.Text1 = StringFromKey("Marginal_50");
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_tavern";
			break;
			case 3:
				pchar.GenQuest.Marginpassenger.Text = StringFromKey("Marginal_51");
				pchar.GenQuest.Marginpassenger.Text1 = StringFromKey("Marginal_52");
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_bank";
			break;
			case 4:
				pchar.GenQuest.Marginpassenger.Text = StringFromKey("Marginal_53");
				pchar.GenQuest.Marginpassenger.Text1 = StringFromKey("Marginal_54");
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_" + (rand(9) + 11); //TODO: можно и не бюргеров, а молодых (LOVERS)
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = StringFromKey("Marginal_55");
		switch (drand(4))
		{
			case 0:
				pchar.GenQuest.Marginpassenger.Text = StringFromKey("Marginal_56");
				pchar.GenQuest.Marginpassenger.Text1 = StringFromKey("Marginal_57");
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_store";
			break;
			case 1:
				pchar.GenQuest.Marginpassenger.Text = StringFromKey("Marginal_58");
				pchar.GenQuest.Marginpassenger.Text1 = StringFromKey("Marginal_59");
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_shipyard";
			break;
			case 2:
				pchar.GenQuest.Marginpassenger.Text = StringFromKey("Marginal_60");
				pchar.GenQuest.Marginpassenger.Text1 = StringFromKey("Marginal_61");
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_tavern";
			break;
			case 3:
				pchar.GenQuest.Marginpassenger.Text = StringFromKey("Marginal_62");
				pchar.GenQuest.Marginpassenger.Text1 = StringFromKey("Marginal_63");
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_bank";
			break;
			case 4:
				pchar.GenQuest.Marginpassenger.Text = StringFromKey("Marginal_64");
				pchar.GenQuest.Marginpassenger.Text1 = StringFromKey("Marginal_65");
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_portoffice";
			break;
		}
	}

	int iShip = SHIP_SLOOP;
	int iRank = sti(pchar.rank);

	//TODO: нужен баланс:
	if (iRank < 4) iShip = SHIP_SLOOP;
	if (iRank >= 4 && iRank < 7) iShip = SHIP_BARKENTINE + rand(2);
	if (iRank >= 7 && iRank < 10) iShip = SHIP_CARAVEL + rand(2);
	if (iRank >= 10 && iRank < 16) iShip = SHIP_GALEON_L;
	if (iRank >= 16) iShip = SHIP_PINNACE + rand(7);

	pchar.GenQuest.Marginpassenger.ShipType = iShip;
}

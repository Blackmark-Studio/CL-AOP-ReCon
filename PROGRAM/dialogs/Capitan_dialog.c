// разговор с капитаном на палубе  Boal
#include "DIALOGS\Rumours\Simple_rumors.c" //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	//homo Осады
	aref aData;
	makearef(aData, NullCharacter.Siege);
	string sCap, sGroup;
	string fort;
	int ifortPower, fortDamage, SquadronDamage;

	if (CheckAttribute(aData, "nation"))
	{
		sCap = NationShortName(sti(aData.nation)) + "SiegeCap_";
		sGroup = "Sea_" + sCap + "1";
	}

	if (sGroup != "" && Group_FindGroup(sGroup) != -1)
	{
		// string myships  = GetCompanionQuantity(PChar);
		// string escships = Group_GetCharactersNum(sGroup);

		switch (sti(aData.conation))
		{
			case 0:  fort = StringFromKey("Capitan_dialog_1"); break;
			case 1:  fort = StringFromKey("Capitan_dialog_2"); break;
			case 2:  fort = StringFromKey("Capitan_dialog_3"); break;
			case 3:  fort = StringFromKey("Capitan_dialog_4"); break;
			case 4:  fort = StringFromKey("Capitan_dialog_5"); break;
		}
		ifortPower = sti(colonies[FindColony(aData.colony)].FortValue);
		fortDamage = CheckFortInjuri();
		SquadronDamage = CheckSquadronInjuri();
	}

	int iMoney;
	ref sld;

	if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 3000 + rand(10) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}

	ProcessCommonDialogRumors(NPChar, Link, NextDiag); //homo 26/06/06

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			NextDiag.TempNode = "first time";
			if (!bDisableMapEnter)
			{
				if (NPChar.quest.meeting == "0")
				{
					if (CheckAttribute(NPChar, "EncType") && NPChar.EncType == "war")
					{
						Dialog.text = StringFromKey("Capitan_dialog_6", TimeGreeting(), GetAddress_Form(NPChar), GetFullName(NPChar), NationKingsName(NPChar));
					}
					else
					{
						if (npchar.id == "RatSeaOfficer")
							Dialog.text = StringFromKey("Capitan_dialog_182", TimeGreeting(), GetAddress_Form(NPChar), GetFullName(NPChar));
						else
							Dialog.text = StringFromKey("Capitan_dialog_7", TimeGreeting(), GetAddress_Form(NPChar), GetFullName(NPChar));
					}
					NPChar.quest.meeting = "1";
					link.l1 = StringFromKey("Capitan_dialog_8", GetFullName(Pchar));
				}
				else
				{
					Dialog.text = StringFromKey("Capitan_dialog_9");
					link.l1 = StringFromKey("Capitan_dialog_10");
				}
				link.l1.go = "quests";
				link.l2 = StringFromKey("Capitan_dialog_11", pchar);
				link.l2.go = "exit";
			}
			else
			{
				Dialog.text = StringFromKey("Capitan_dialog_12", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Capitan_dialog_13");
				link.l1.go = "exit";
			}
		break;

		case "quests":
			if (!CheckAttribute(NPChar, "MainCaptanId") || NPChar.MainCaptanId == pchar.GenQuest.CaptainId)
			{
				Dialog.text = StringFromKey("Capitan_dialog_14", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Capitan_dialog_15", pchar);
				//homo 25/06/06
				link.l1.go = "rumours_capitan";
				//
				if (CheckAttribute(NPChar, "EncGroupName")) // только для фантомов грабеж
				{
					link.l2 = StringFromKey("Capitan_dialog_18", RandPhraseSimple(
								StringFromKey("Capitan_dialog_16"),
								StringFromKey("Capitan_dialog_17")));
					link.l2.go = "Talk_board";
				}
				if (CheckAttribute(NPChar, "Ship.Mode") && NPChar.Ship.Mode == "Trade")
				{
					link.l3 = StringFromKey("Capitan_dialog_19");
					link.l3.go = "price_1";
					link.l4 = StringFromKey("Capitan_dialog_20");
					link.l4.go = "Trade_1";
				}
				//--> квест мэра, поиски пирата
				if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.DestroyPirate != "Execute")
				{
					link.l6 = StringFromKey("Capitan_dialog_21");
					link.l6.go = "MQ_step_1";
				}
				//<-- квест мэра, поиски пирата
				link.l5 = StringFromKey("Capitan_dialog_22");
				link.l5.go = "Play_Game";
				link.l9 = StringFromKey("Capitan_dialog_23");
				link.l9.go = "exit";
			}
			else
			{
				Dialog.text = StringFromKey("Capitan_dialog_24", GetFullName(characterFromID(NPChar.MainCaptanId)), XI_ConvertString(RealShips[sti(characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Type)].BaseName), characters[GetCharacterIndex(NPChar.MainCaptanId)].Ship.Name);
				link.l1 = StringFromKey("Capitan_dialog_25");
				link.l1.go = "exit";
				NextDiag.TempNode = "Go_away_Good";
			}
		break;
		//=====================================================
		case "Trade_1":
			dialog.text = StringFromKey("Capitan_dialog_26");
			link.l1 = StringFromKey("Capitan_dialog_27");
			link.l1.go = "Trade_2";
			link.l2 = StringFromKey("Capitan_dialog_28", pchar);
			link.l2.go = "exit";
		break;

		case "Trade_2":
			FillShipStore(NPChar);
			pchar.shiptrade.character = NPChar.id;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteAttribute(pchar, "PriceList.StoreManIdx"); // не вести лог по кораблям
			LaunchStore(SHIP_STORE);
		break;

		case "Play_Game":
			dialog.text = StringFromKey("Capitan_dialog_29");
			link.l1 = StringFromKey("Capitan_dialog_30");
			link.l1.go = "Card_Game";
			link.l2 = StringFromKey("Capitan_dialog_31");
			link.l2.go = "Dice_Game";
			link.l10 = StringFromKey("Capitan_dialog_32");
			link.l10.go = "exit";
		break;
		// карты -->
		case "Card_Game":
		//            if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
			if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || PlayerRPGCheck_BadReputation(30, false) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
				SetNPCQuestDate(npchar, "Card_date_Yet");
				dialog.text = StringFromKey("Capitan_dialog_33");
				link.l1 = StringFromKey("Capitan_dialog_34");
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Capitan_dialog_35");
				link.l1 = StringFromKey("Capitan_dialog_36");
				link.l1.go = "Cards_begin";
				link.l2 = StringFromKey("Capitan_dialog_37");
				link.l2.go = "Cards_Rule";
			}
		break;

		case "Cards_Rule":
			dialog.text = GlobalStringConvert("CARDS_RULE");
			link.l1 = StringFromKey("Capitan_dialog_38");
			link.l1.go = "Cards_begin";
			link.l3 = StringFromKey("Capitan_dialog_39");
			link.l3.go = "exit";
		break;

		case "Cards_begin":
			Dialog.text = StringFromKey("Capitan_dialog_40");
			link.l1 = StringFromKey("Capitan_dialog_41");
			link.l1.go = "Cards_Node_100";
			link.l2 = StringFromKey("Capitan_dialog_42");
			link.l2.go = "Cards_Node_500";
			link.l3 = StringFromKey("Capitan_dialog_43");
			link.l3.go = "exit";
		break;

		case "Cards_Node_100":
			if (sti(pchar.Money) < 300)
			{
				dialog.text = StringFromKey("Capitan_dialog_44");
				link.l1 = StringFromKey("Capitan_dialog_45");
				link.l1.go = "exit";
				break;
			}
			if (sti(npchar.Money) < 300)
			{
				dialog.text = StringFromKey("Capitan_dialog_46");
				link.l1 = StringFromKey("Capitan_dialog_47");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Capitan_dialog_48");
			link.l1 = StringFromKey("Capitan_dialog_49");
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate = 100;
			pchar.GenQuest.Cards.SitType = false;
		break;

		case "Cards_Node_500":
			if (sti(pchar.Money) < 1500)
			{
				dialog.text = StringFromKey("Capitan_dialog_50");
				link.l1 = StringFromKey("Capitan_dialog_51");
				link.l1.go = "exit";
				break;
			}
			if (sti(npchar.Money) < 1500)
			{
				dialog.text = StringFromKey("Capitan_dialog_52");
				link.l1 = StringFromKey("Capitan_dialog_53");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Capitan_dialog_54");
			link.l1 = StringFromKey("Capitan_dialog_55");
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate = 500;
			pchar.GenQuest.Cards.SitType = false;
		break;

		case "Cards_begin_go":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCardsGame();
		break;
		// карты <--
		//  Dice -->
		case "Dice_Game":
		//            if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || isBadReputation(pchar, 30) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
			if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || PlayerRPGCheck_BadReputation(30, false) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(3))
			{
				PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
				SetNPCQuestDate(npchar, "Dice_date_Yet");
				dialog.text = StringFromKey("Capitan_dialog_56");
				link.l1 = StringFromKey("Capitan_dialog_57");
				link.l1.go = "exit";
			}
			else
			{
				if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
				{
					dialog.text = StringFromKey("Capitan_dialog_58");
					link.l1 = StringFromKey("Capitan_dialog_59");
					link.l1.go = "Dice_begin";
					link.l2 = StringFromKey("Capitan_dialog_60");
					link.l2.go = "Dice_Rule";
				}
				else
				{
					dialog.text = StringFromKey("Capitan_dialog_61");
					link.l1 = StringFromKey("Capitan_dialog_62");
					link.l1.go = "exit";
				}
			}
		break;

		case "Dice_Rule":
			dialog.text = GlobalStringConvert("DICE_RULE");
			link.l1 = StringFromKey("Capitan_dialog_63");
			link.l1.go = "Dice_begin";
			link.l3 = StringFromKey("Capitan_dialog_64");
			link.l3.go = "exit";
		break;

		case "Dice_begin":
			Dialog.text = StringFromKey("Capitan_dialog_65");
			link.l1 = StringFromKey("Capitan_dialog_66");
			link.l1.go = "Dice_Node_100";
			link.l2 = StringFromKey("Capitan_dialog_67");
			link.l2.go = "Dice_Node_500";
			link.l3 = StringFromKey("Capitan_dialog_68");
			link.l3.go = "exit";
		break;

		case "Dice_Node_100":
			if (!CheckDiceGameSmallRate())
			{
				dialog.text = StringFromKey("Capitan_dialog_69", pchar);
				link.l1 = StringFromKey("Capitan_dialog_70");
				link.l1.go = "exit";
				break;
			}
			if (sti(pchar.Money) < 300)
			{
				dialog.text = StringFromKey("Capitan_dialog_71");
				link.l1 = StringFromKey("Capitan_dialog_72");
				link.l1.go = "exit";
				break;
			}
			if (sti(npchar.Money) < 300)
			{
				dialog.text = StringFromKey("Capitan_dialog_73");
				link.l1 = StringFromKey("Capitan_dialog_74");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Capitan_dialog_75");
			link.l1 = StringFromKey("Capitan_dialog_76");
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate = 50;
			pchar.GenQuest.Dice.SitType = false;
		break;

		case "Dice_Node_500":
			if (!CheckDiceGameSmallRate())
			{
				dialog.text = StringFromKey("Capitan_dialog_77", pchar);
				link.l1 = StringFromKey("Capitan_dialog_78");
				link.l1.go = "exit";
				break;
			}
			if (!CheckDiceGameBigRate())
			{
				dialog.text = StringFromKey("Capitan_dialog_79");
				link.l1 = StringFromKey("Capitan_dialog_80");
				link.l1.go = "Dice_Node_100";
				link.l2 = StringFromKey("Capitan_dialog_81");
				link.l2.go = "exit";
				break;
			}
			if (sti(pchar.Money) < 1500)
			{
				dialog.text = StringFromKey("Capitan_dialog_82");
				link.l1 = StringFromKey("Capitan_dialog_83");
				link.l1.go = "exit";
				break;
			}
			if (sti(npchar.Money) < 1500)
			{
				dialog.text = StringFromKey("Capitan_dialog_84");
				link.l1 = StringFromKey("Capitan_dialog_85");
				link.l1.go = "exit";
				break;
			}
			dialog.text = StringFromKey("Capitan_dialog_86");
			link.l1 = StringFromKey("Capitan_dialog_87");
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate = 200;
			pchar.GenQuest.Dice.SitType = false;
		break;

		case "Dice_begin_go":
			SetNPCQuestDate(npchar, "Dice_date_begin");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchDiceGame();
		break;
		// Dice <--
		case "price_1":
			if (CheckNPCQuestDate(npchar, "trade_date"))
			{
				SetNPCQuestDate(npchar, "trade_date");
				iMoney = findPriceStoreMan(NPChar);
				if (iMoney == -1)
				{
					Dialog.Text = StringFromKey("Capitan_dialog_88");
					Link.l1 = StringFromKey("Capitan_dialog_89");
					Link.l1.go = "exit";
				}
				else
				{
					sld = &Characters[iMoney];
					pchar.PriceList.ShipStoreIdx = iMoney;

					Dialog.Text = StringFromKey("Capitan_dialog_90", GetTraderCityName(sld)); // KZ FreeStores > у свободного магазина имя с него самого
					Link.l1 = StringFromKey("Capitan_dialog_91");
					Link.l1.go = "price_2";
					Link.l9 = StringFromKey("Capitan_dialog_92");
					Link.l9.go = "exit";
				}
			}
			else
			{
				Dialog.Text = StringFromKey("Capitan_dialog_93");
				Link.l1 = StringFromKey("Capitan_dialog_94");
				Link.l1.go = "exit";
			}
		break;

		case "price_2":
			sld = &Characters[sti(pchar.PriceList.ShipStoreIdx)];
			// FreeStores > Прайс пишем от колонии или от самого магазина
			SetPriceListByTrader(sld);
			Dialog.Text = StringFromKey("Capitan_dialog_95");
			Link.l1 = StringFromKey("Capitan_dialog_96");
			Link.l1.go = "exit";
			LogSound_WithNotify(StringFromKey("InfoMessages_116", GetTraderCityName(sld)), "Notebook_2", "LogBook"); // FreeStores > у свободного магазина имя с него самого
		break;

		case "Talk_board":
			if ((Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) > GetCompanionQuantity(PChar) && rand(11) > GetCharacterSkillToOld(PChar, SKILL_FORTUNE))
			{
				Dialog.text = StringFromKey("Capitan_dialog_97");
				link.l1 = StringFromKey("Capitan_dialog_98");
				link.l1.go = "Boarding";
			}
			else
			{
				if (rand(21) > (GetSummonSkillFromNameToOld(PChar, SKILL_GRAPPLING) + GetSummonSkillFromNameToOld(PChar, SKILL_LEADERSHIP)))
				{
					PlayerRPGCheck_Skill_NotifyFail(SKILL_GRAPPLING, true);
					PlayerRPGCheck_Skill_NotifyFail(SKILL_LEADERSHIP, false);
					Dialog.text = StringFromKey("Capitan_dialog_99");
					link.l1 = StringFromKey("Capitan_dialog_100");
					link.l1.go = "Boarding";
				}
				else
				{
					PlayerRPGCheck_Skill_NotifyPass(SKILL_GRAPPLING);
					PlayerRPGCheck_Skill_NotifyPass(SKILL_LEADERSHIP);
					Pchar.GenQuest.MoneyForCaptureShip = makeint(100 + (Group_GetCharactersNum(NPChar.EncGroupName) - Group_GetDeadCharactersNum(NPChar.EncGroupName)) * (7 - sti(RealShips[sti(NPChar.Ship.Type)].Class)) * (1 + rand(10)) * 500);
					Dialog.text = StringFromKey("Capitan_dialog_101", RandSwear(), XI_ConvertString(NationShortName(sti(NPChar.nation)) + "hunter"));
					link.l1 = StringFromKey("Capitan_dialog_102", FindMoneyString(sti(Pchar.GenQuest.MoneyForCaptureShip)), GetAddress_FormToNPC(NPChar));
					link.l1.go = "Capture";
					link.l2 = StringFromKey("Capitan_dialog_103", pchar);
					link.l2.go = "exit";
				}
			}
			// тут нужен учет запрета повторного наезда
			NextDiag.TempNode = "Go_away";
			sld = characterFromId(pchar.GenQuest.CaptainId);
			sld.talk_date_Go_away = lastspeakdate(); // boal злопамятность
		break;

		case "Go_away":
			Dialog.Text = StringFromKey("Capitan_dialog_104");
			Link.l1 = StringFromKey("Capitan_dialog_105");
			Link.l1.go = "exit";
			NextDiag.TempNode = "Go_away";
		break;

		case "Go_away_Good":
			Dialog.Text = StringFromKey("Capitan_dialog_106", GetAddress_Form(NPChar));
			Link.l1 = StringFromKey("Capitan_dialog_107");
			Link.l1.go = "exit";
			NextDiag.TempNode = "Go_away_Good";
		break;

		case "Capture":
			NextDiag.TempNode = "Go_away";
			Dialog.Text = StringFromKey("Capitan_dialog_108");
			Link.l1 = StringFromKey("Capitan_dialog_109");
			Link.l1.go = "exit";
			AddMoneyToCharacter(pchar, sti(Pchar.GenQuest.MoneyForCaptureShip));
			ChangeCharacterReputation(pchar, -5);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			ChangeCharacterHunterScore(pchar, NationShortName(sti(NPChar.nation)) + "hunter", 7 + rand(10));
		break;

		case "Boarding":
			if (CheckAttribute(NPChar, "MainCaptanId"))
			{
				PChar.StartBattleAfterDeck = true;
				PChar.StartBattleMainCaptanId = NPChar.MainCaptanId;
				PChar.StartBattleEncGroupName = NPChar.EncGroupName;
			}
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "QuestAboardCabinDialog":  // тестовый диалог, в игре не работает, для метода SetQuestAboardCabinDialog
			NextDiag.TempNode = "QuestAboardCabinDialog";
			Dialog.Text = StringFromKey("Capitan_dialog_110");
			Link.l1 = StringFromKey("Capitan_dialog_111");
			Link.l1.go = "QuestAboardCabinDialog_1";
			Link.l2 = StringFromKey("Capitan_dialog_112");
			Link.l2.go = "QuestAboardCabinDialog_2";
			Link.l3 = StringFromKey("Capitan_dialog_113");  // предмет, далее не ясно или  QuestAboardCabinDialog_1 или QuestAboardCabinDialog_2
			Link.l3.go = "QuestAboardCabinDialog_3";  // можно закодить покидание корабля, но экипаж уже вырезан и тп...
		break;

		case "QuestAboardCabinDialog_1":
			Dialog.Text = StringFromKey("Capitan_dialog_114");
			Link.l1 = StringFromKey("Capitan_dialog_115");
			Link.l1.go = "exit";
			// тут можно восстановить НР противника (NPChar) или добавить парочку гардов против ГГ
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattle"); // тут ругань обратно
		break;

		case "QuestAboardCabinDialog_2":
			Dialog.Text = StringFromKey("Capitan_dialog_116");
			Link.l1 = StringFromKey("Capitan_dialog_117");
			Link.l1.go = "exit";
			AddDialogExitQuestFunction("QuestAboardCabinDialogSurrender");
		break;

		case "QuestAboardCabinDialog_3":
			Dialog.Text = StringFromKey("Capitan_dialog_118");
			Link.l1 = StringFromKey("Capitan_dialog_119");
			if (rand(1) == 1)  // пример!!!
			{
				Link.l1.go = "QuestAboardCabinDialog_2";
			}
			else
			{
				Link.l1.go = "QuestAboardCabinDialog_3_1";
			}
			TakeNItems(NPChar, "Chest", -1);
			TakeNItems(pchar, "Chest", 1);
		break;

		case "QuestAboardCabinDialog_3_1":
			Dialog.Text = StringFromKey("Capitan_dialog_120", pchar);
			Link.l1 = StringFromKey("Capitan_dialog_121");
			Link.l1.go = "QuestAboardCabinDialog_1";
		break;
		//eddy. квест мэра, поиски пирата
		case "MQ_step_1":
			Dialog.Text = StringFromKey("Capitan_dialog_122");
			Link.l1 = StringFromKey("Capitan_dialog_123");
			Link.l1.go = "exit";
		break;

		//homo Наводка на купца
		case "MerchantTrap_Abordage":
			Dialog.Text = StringFromKey("Capitan_dialog_124", pchar, NationKingsName(NPChar), NationNameSK(sti(NPChar.nation)));
			Link.l1 = StringFromKey("Capitan_dialog_125");
			Link.l1.go = "exit";
			LAi_SetCurHPMax(NPChar);
			AddDialogExitQuestFunction("QuestAboardCabinDialogExitWithBattleNoParam"); // тут ругань обратно
		break;

		case "Siegehelp":
			ref rchar = Group_GetGroupCommander(sGroup);
			if (NPChar.id == rchar.id)
			{
				dialog.text = StringFromKey("Capitan_dialog_126", fort);
				link.l1 = StringFromKey("Capitan_dialog_127", GetAddress_FormToNPC(NPChar));
				link.l1.go = "attack_fort";
				link.l2 = StringFromKey("Capitan_dialog_128", GetAddress_FormToNPC(NPChar));
				link.l2.go = "exit";
			}
			else
			{
				Dialog.text = StringFromKey("Capitan_dialog_129", GetFullName(rchar), XI_ConvertString(RealShips[sti(rchar.Ship.Type)].BaseName), rchar.Ship.Name);
				link.l1 = StringFromKey("Capitan_dialog_130");
				link.l1.go = "exit";

			}
			NextDiag.TempNode = "Siegehelp";
		break;

		case "attack_fort":
			dialog.text = StringFromKey("Capitan_dialog_131");
			link.l1 = StringFromKey("Capitan_dialog_132", GetConvertStr(aData.Colony + " Town", "LocLables.txt"));
			link.l1.go = "Siegehelp_1";
			link.l2 = StringFromKey("Capitan_dialog_133", GetAddress_FormToNPC(NPChar));
			link.l2.go = "exit";
			NextDiag.TempNode = "Siegehelp_0";
		break;

		case "Siegehelp_0":
			Dialog.text = StringFromKey("Capitan_dialog_134");
			link.l1 = StringFromKey("Capitan_dialog_135", pchar);
			link.l1.go = "exit";
			NPChar.DeckDialogNode = "Siegehelp_0";
			NextDiag.TempNode = "Siegehelp_0";

		break;

		case "Siegehelp_1":
			SiegeResult("");
			if (sti(aData.win) == 0)
			{
				dialog.text = StringFromKey("Capitan_dialog_136");
				link.l1 = StringFromKey("Capitan_dialog_137");
				link.l1.go = "Big_part";
				link.l2 = StringFromKey("Capitan_dialog_138");
				link.l2.go = "Middle_part";
				link.l3 = StringFromKey("Capitan_dialog_139");
				link.l3.go = "Small_part";
			}
			else
			{
				dialog.text = StringFromKey("Capitan_dialog_140");
				link.l1 = StringFromKey("Capitan_dialog_141", GetAddress_FormToNPC(NPChar));
				link.l1.go = "attack_fort_03";
				link.l2 = StringFromKey("Capitan_dialog_142", GetAddress_FormToNPC(NPChar));
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Siegehelp_0";

		break;

		case "attack_fort_03":
			if ((sti(aData.iSquadronPower) * SquadronDamage - (ifortPower) * fortDamage) < 4000)
			{
				dialog.text = StringFromKey("Capitan_dialog_143", GetPart(4));
				link.l1 = StringFromKey("Capitan_dialog_144", GetAddress_FormToNPC(NPChar));
				link.l1.go = "attack_fort_04";
				aData.PartAttaksFort = 4;
				link.l2 = StringFromKey("Capitan_dialog_145", pchar, GetAddress_FormToNPC(NPChar));
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Capitan_dialog_146");
				link.l1 = StringFromKey("Capitan_dialog_147", GetAddress_FormToNPC(NPChar));
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Siegehelp_0";
		break;
		case "Big_part":
			if ((sti(aData.iSquadronPower) * SquadronDamage - (ifortPower) * fortDamage) <= -1500)
			{
				dialog.text = StringFromKey("Capitan_dialog_148");
				link.l1 = StringFromKey("Capitan_dialog_149", GetAddress_FormToNPC(NPChar));
				link.l1.go = "attack_fort_04";
				aData.PartAttaksFort = 2;
			}
			else
			{
				dialog.text = StringFromKey("Capitan_dialog_150", GetNumShips(GetCompanionQuantity(PChar)), GetNumShips(Group_GetCharactersNum(sGroup)), GetPart(4));
				aData.PartAttaksFort = 4;
				link.l1 = StringFromKey("Capitan_dialog_151", pchar, GetAddress_FormToNPC(NPChar));
				link.l1.go = "attack_fort_04";
				link.l2 = StringFromKey("Capitan_dialog_152", GetAddress_FormToNPC(NPChar));
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Siegehelp_0";
		break;

		case "attack_fort_04":
			dialog.text = StringFromKey("Capitan_dialog_153");
			link.l1 = StringFromKey("Capitan_dialog_154", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			NextDiag.TempNode = "Siegehelp_0";
			PChar.quest.Union_with_Escadra = "Yes";
		break;

		case "Middle_part":
			if ((sti(aData.iSquadronPower) * SquadronDamage - (ifortPower) * fortDamage) <= -600)
			{
				dialog.text = StringFromKey("Capitan_dialog_155");
				link.l1 = StringFromKey("Capitan_dialog_156", GetAddress_FormToNPC(NPChar));
				link.l1.go = "attack_fort_04";
				aData.PartAttaksFort = 3;
			}
			else
			{
				dialog.text = StringFromKey("Capitan_dialog_157", GetNumShips(GetCompanionQuantity(PChar)), GetNumShips(Group_GetCharactersNum(sGroup)), GetPart(4));
				link.l1 = StringFromKey("Capitan_dialog_158", pchar, GetAddress_FormToNPC(NPChar));
				link.l1.go = "attack_fort_04";
				aData.PartAttaksFort = 4;
				link.l2 = StringFromKey("Capitan_dialog_159", GetAddress_FormToNPC(NPChar));
				link.l2.go = "exit";
			}
			NextDiag.TempNode = "Siegehelp_0";
		break;

		case "Small_part":
			dialog.text = StringFromKey("Capitan_dialog_160");
			link.l1 = StringFromKey("Capitan_dialog_161", pchar, GetAddress_FormToNPC(NPChar));
			link.l1.go = "attack_fort_04";
			aData.PartAttaksFort = 4;
			NextDiag.TempNode = "Siegehelp_0";
		break;

		case "Talk_Capture_City":
			AfterTownBattle();  // все, все свободны
			LAi_LoginInCaptureTown(NPChar, false);
			LAi_SetImmortal(NPChar, false);
			aData.win = 1;
			EndOfTheSiege("End");
			NPChar.location = "";
			int ilt = makeint(sti(aData.loot) / sti(aData.PartAttaksFort));
			dialog.text = StringFromKey("Capitan_dialog_162", FindMoneyString(sti(aData.loot)), ilt);
			link.l1 = StringFromKey("Capitan_dialog_163", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			//AddDialogExitQuest("End_Siege_and_Attaks_City");

			NextDiag.TempNode = "no_return_02";
			AddMoneyToCharacter(PChar, ilt);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			ChangeCharacterReputation(PChar, 10);
			AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 80);
			AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 100);
			AddCharacterExpToSkill(GetMainCharacter(), "Defence", 100);
			AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 100);
			AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 100);
			AddCharacterExpToSkill(GetMainCharacter(), "Fortune", 80);
			aData.loot = sti(aData.loot) - ilt;
			if (CheckAttribute(PChar, "quest.LeaveTown")) Pchar.quest.LeaveTown.over = "yes";
			//--> слухи
			SiegeRumour(
				StringFromKey("Capitan_dialog_164", NationNameSK(sti(aData.conation)), GetConvertStr(aData.Colony + " Town", "LocLables.txt"), GetAddress_Form(NPChar)), "", sti(aData.nation), -1, 30, 3);
		//<-- слухи
		break;

		case "no_return_02":
			dialog.text = StringFromKey("Capitan_dialog_165");
			link.l1 = StringFromKey("Capitan_dialog_166", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit";
			NextDiag.TempNode = "no_return_02";
		break;

		case "GoldSquadron":
			ref rch = Group_GetGroupCommander("Sea_Head_of_Gold_Squadron");
			if (NPChar.id == rch.id)
			{
				dialog.text = StringFromKey("Capitan_dialog_167");

				link.l1 = StringFromKey("Capitan_dialog_168", GetAddress_FormToNPC(NPChar));
				link.l1.go = "exit";

			}
			else
			{
				Dialog.text = StringFromKey("Capitan_dialog_169", GetFullName(rch), XI_ConvertString(RealShips[sti(rch.Ship.Type)].BaseName), rch.Ship.Name);
				link.l1 = StringFromKey("Capitan_dialog_170");
				link.l1.go = "exit";

			}
			NextDiag.TempNode = "GoldSquadron";
		break;
	}
}

string GetNumShips(int ship)
{
	string numships;
	switch (ship)
	{
		case 0: numships = StringFromKey("Capitan_dialog_171"); break;
		case 1: numships = StringFromKey("Capitan_dialog_172");      break;
		case 2: numships = StringFromKey("Capitan_dialog_173");       break;
		case 3: numships = StringFromKey("Capitan_dialog_174");       break;
		case 4: numships = StringFromKey("Capitan_dialog_175");    break;
		case 5: numships = StringFromKey("Capitan_dialog_176");     break;
		case 6: numships = StringFromKey("Capitan_dialog_177");    break;
	}
	return numships;
}

string GetPart(int part)
{
	string numpart;
	switch (part)
	{
		case 0: numpart = ""; break;
		case 1: numpart = StringFromKey("Capitan_dialog_178"); break;
		case 2: numpart = StringFromKey("Capitan_dialog_179"); break;
		case 3: numpart = StringFromKey("Capitan_dialog_180"); break;
		case 4: numpart = StringFromKey("Capitan_dialog_181");      break;

	}
	return numpart;
}

int findPriceStoreMan(ref NPChar)
{
	ref ch;
	int n;
	int storeArray[40];
	int howStore = 0;

	for (n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(ch, Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
			//if (sti(ch.nation) !=  sti(NPChar.nation)) continue;
			if (ch.location == "none") continue; // фикс для новых, невидимых до поры островов
			// FreeStores > о ценах магазина вне колонии рассказывают только при QuestsAvailable у торговца
			if (!IsNPCQuestsAllowed(ch)) continue;
			storeArray[howStore] = n;
			howStore++;

			// homo 05/09/06
			if (CheckAttribute(NPChar, "FromColony") && NPChar.FromColony == ch.City) return n;
			//
		}
	}
	if (howStore == 0)
	{
		return -1;
	}
	else
	{
		return storeArray[rand(howStore - 1)];
	}
}

//Jason общий диалог дворян
#include "DIALOGS\Rumours\Simple_rumors.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

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

	iTest = FindColony(NPChar.City); // 170712
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	switch (Dialog.CurrentNode)
	{
		case "First time":
			NextDiag.TempNode = "First time";
			//--> проверка репутации - дворяне гнобят супернегодяев
			if (sti(pchar.reputation) <= 10 && sti(rColony.HeroOwn) != true)
			{
				PlayerRPGCheck_Reputation_NotifyFail("good");
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Nobleman_1", pchar),
							StringFromKey("Nobleman_2", pchar),
							StringFromKey("Nobleman_3"),
							StringFromKey("Nobleman_4", pchar), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Nobleman_5"),
							StringFromKey("Nobleman_6"),
							StringFromKey("Nobleman_7"),
							StringFromKey("Nobleman_8"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
				break;
			}
			//--> диалог первой встречи
			if (NPChar.quest.meeting == "0")
			{
				// проверка наличия корабля в порту
				if (CheckShipMooredInColony(rColony) && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 5 - sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)//дворянин-пассажир
				{
					dialog.text = StringFromKey("Nobleman_9", GetAddress_Form(NPChar));
					link.l1 = StringFromKey("Nobleman_10", GetAddress_FormToNPC(NPChar));
					link.l1.go = "passenger";
					link.l2 = StringFromKey("Nobleman_11", GetAddress_FormToNPC(NPChar));
					link.l2.go = "exit";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				if (CheckAttribute(npchar, "quest.donation") && GetCharacterEquipSuitID(pchar) != "suit_1") //клянчит деньги, если только мы не одеты, как бомж (ниже также)
				{
					if (CheckCharacterPerk(pchar, "Nobleman") || GetCharacterEquipSuitID(pchar) == "suit_3") sTemp = StringFromKey("Nobleman_12");
					else sTemp = "";
					dialog.text = StringFromKey("Nobleman_13", sTemp);
					link.l1 = StringFromKey("Nobleman_14");
					link.l1.go = "donation";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard") && GetCharacterEquipSuitID(pchar) != "suit_1") //семейная реликвия
				{
					dialog.text = StringFromKey("Nobleman_15", GetAddress_Form(NPChar));
					link.l1 = StringFromKey("Nobleman_16");
					link.l1.go = "lombard";
					npchar.quest.meeting = "1";
					break;
				}
				if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves") && GetCharacterEquipSuitID(pchar) != "suit_1") //привезти рабов
				{
					dialog.text = StringFromKey("Nobleman_17");
					link.l1 = StringFromKey("Nobleman_18", GetAddress_FormToNPC(NPChar));
					link.l1.go = "slaves";
					npchar.quest.meeting = "1";
					break;
				}
				dialog.text = StringFromKey("Nobleman_21", RandPhraseSimple(
							StringFromKey("Nobleman_19", GetAddress_Form(NPChar)),
							StringFromKey("Nobleman_20", pchar)));
				link.l1 = StringFromKey("Nobleman_22", TimeGreeting(), GetAddress_FormToNPC(NPChar));
				link.l1.go = "question";
				link.l2 = StringFromKey("Nobleman_25", RandPhraseSimple(
							StringFromKey("Nobleman_23"),
							StringFromKey("Nobleman_24")));
				link.l2.go = "quests"; //(перессылка в файл города)
				link.l3 = PCharRepPhrase(
							StringFromKey("Nobleman_28", RandPhraseSimple(
									StringFromKey("Nobleman_26"),
									StringFromKey("Nobleman_27", pchar))),
							StringFromKey("Nobleman_31", RandPhraseSimple(
									StringFromKey("Nobleman_29"),
									StringFromKey("Nobleman_30"))));
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			else //--> повторные обращения
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Nobleman_32"),
							StringFromKey("Nobleman_33"),
							StringFromKey("Nobleman_34", pchar),
							StringFromKey("Nobleman_35", pchar), "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Nobleman_36"),
							StringFromKey("Nobleman_37", pchar),
							StringFromKey("Nobleman_38"),
							StringFromKey("Nobleman_39"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			}
		break;

		case "question":
			dialog.text = StringFromKey("Nobleman_43", LinkRandPhrase(
						StringFromKey("Nobleman_40"),
						StringFromKey("Nobleman_41"),
						StringFromKey("Nobleman_42")));
			link.l1 = StringFromKey("Nobleman_47", LinkRandPhrase(
						StringFromKey("Nobleman_44"),
						StringFromKey("Nobleman_45"),
						StringFromKey("Nobleman_46")));
			link.l1.go = "rumours_nobleman";
			NextDiag.TempNode = "First time";
		break;

		//--------------------------------------------дворянин-пассажир---------------------------------------------------
		case "passenger":
			if (drand(19) > 9) SetPassengerParameter("Noblepassenger", false);
			else SetPassengerParameter("Noblepassenger", true);
			dialog.text = StringFromKey("Nobleman_48", pchar, XI_ConvertString("Colony" + pchar.GenQuest.Noblepassenger.City), XI_ConvertString(GetIslandNameByCity(pchar.GenQuest.Noblepassenger.City) + "Pre"), FindDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)), FindMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			link.l1 = StringFromKey("Nobleman_49", pchar);
			link.l1.go = "passenger_1";
			link.l2 = StringFromKey("Nobleman_50", GetAddress_FormToNPC(NPChar));
			link.l2.go = "passenger_exit";
		break;

		case "passenger_exit":
			dialog.text = StringFromKey("Nobleman_51");
			link.l1 = StringFromKey("Nobleman_52");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;

		case "passenger_1":
			dialog.text = StringFromKey("Nobleman_53");
			link.l1 = StringFromKey("Nobleman_54", GetAddress_FormToNPC(NPChar));
			link.l1.go = "passenger_2";
		break;

		case "passenger_2":
			DialogExit();
			pchar.GenQuest.Noblepassenger.id = npchar.id;
			LAi_SetImmortal(npchar, true);
			DeleteAttribute(npchar, "LifeDay");
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
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
			AddQuestUserDataForTitle(sTitle, "sType", "дворянина");
			AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
			sTemp = StringFromKey("Nobleman_55", XI_ConvertString("Colony" + pchar.GenQuest.Noblepassenger.City), XI_ConvertString(GetIslandNameByCity(pchar.GenQuest.Noblepassenger.City) + "Pre"));
			AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sCity", sTemp);
			AddQuestUserData(sTitle, "sDays", FindDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
			AddQuestUserData(sTitle, "sMoney", FindMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
			pchar.quest.Noblepassenger.win_condition.l1 = "location";
			pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City + "_town";
			pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
			SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;

		case "passenger_3":
			pchar.quest.Noblepassenger_Over.over = "yes"; //снять таймер
			dialog.text = StringFromKey("Nobleman_56", pchar);
			link.l1 = StringFromKey("Nobleman_57", GetAddress_FormToNPC(NPChar));
			link.l1.go = "passenger_4";
		break;

		case "passenger_4":
			chrDisableReloadToLocation = false;//открыть локацию
			DialogExit();
			npchar.lifeday = 0;
			RemovePassenger(Pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
			ChangeCharacterReputation(pchar, 2);
			OfficersReaction("good");
			AddCharacterExpToSkill(pchar, "Sailing", 80);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity")) AddCharacterExpToSkill(pchar, "Sneak", 50);
			sTitle = npchar.index + "Citizpassenger";
			AddQuestRecordEx(sTitle, "Citizpassenger", "3");
			CloseQuestHeader(sTitle);
			DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
		//<-- дворянин-пассажир

		//-------------------------------------------------помощь деньгами------------------------------------------------
		case "donation":
			sTemp = DonationText();
			dialog.text = StringFromKey("Nobleman_58", sTemp);
			link.l1 = StringFromKey("Nobleman_59");
			link.l1.go = "donation_1";
		break;

		case "donation_1":
			iTemp = drand(5) + 2;
			pchar.GenQuest.Nobledonation.Money = iTemp * 1200 + rand(iTemp) * 150;
			dialog.text = StringFromKey("Nobleman_60", FindMoneyString(sti(pchar.GenQuest.Nobledonation.Money)));
			if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
			{
				link.l1 = StringFromKey("Nobleman_61");
				link.l1.go = "donation_2";
			}
			link.l2 = StringFromKey("Nobleman_62", pchar);
			link.l2.go = "donation_exit";
		break;

		case "donation_exit":
			DialogExit();
			OfficersReaction("bad");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
			RemoveLandQuestMark_Gen(npchar, "Nobledonation");
		break;

		case "donation_2":
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
			dialog.text = StringFromKey("Nobleman_63", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Nobleman_64", pchar);
			link.l1.go = "donation_3";
		break;

		case "donation_3":
			DialogExit();
			ChangeOfficersLoyality("good_all", rand(2) + 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1) + 2);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Nobledonation");
			RemoveLandQuestMark_Gen(npchar, "Nobledonation");
		break;
		//<-- помощь деньгами

		//-------------------------------------------------семейная реликвия---------------------------------------------
		case "lombard":
			LombardText();
			if (CheckCharacterPerk(pchar, "Nobleman") || GetCharacterEquipSuitID(pchar) == "suit_3") sTemp = StringFromKey("Nobleman_65");
			else sTemp = "";
			dialog.text = StringFromKey("Nobleman_66", sTemp, pchar.GenQuest.Noblelombard.Item, XI_ConvertString(GetArealByCityName(npchar.city) + "Pre"));
			link.l1 = StringFromKey("Nobleman_67", GetAddress_FormToNPC(NPChar));
			link.l1.go = "lombard_1";
		break;

		case "lombard_1":
			dialog.text = StringFromKey("Nobleman_68", pchar.GenQuest.Noblelombard.Text);
			link.l1 = StringFromKey("Nobleman_69");
			link.l1.go = "lombard_2";
			link.l2 = StringFromKey("Nobleman_70");
			link.l2.go = "lombard_exit";
		break;

		case "lombard_exit":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DeleteAttribute(pchar, "GenQuest.Noblelombard");
			RemoveLandQuestMark_Gen(npchar, "Noblelombard");
		break;

		case "lombard_2":
			dialog.text = StringFromKey("Nobleman_71");
			link.l1 = "...";
			link.l1.go = "lombard_3";
		break;

		case "lombard_3":
			DialogExit();
			pchar.GenQuest.Noblelombard = "true";
			pchar.GenQuest.Noblelombard.Name = GetFullName(npchar);
			pchar.GenQuest.Noblelombard.id = npchar.id;
			pchar.GenQuest.Noblelombard.City = npchar.city;
			pchar.GenQuest.Noblelombard.Money = 20000 + drand(60) * 500;
			pchar.GenQuest.Noblelombard.Percent = makeint(sti(pchar.GenQuest.Noblelombard.Money) * 0.3);
			pchar.GenQuest.Noblelombard.Summ = sti(pchar.GenQuest.Noblelombard.Money) + sti(pchar.GenQuest.Noblelombard.Percent);
			pchar.GenQuest.Noblelombard.Chance = drand(9);
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_RemoveLoginTime(npchar);
			DeleteAttribute(npchar, "CityType");//удалить признак фантома

			sTemp = "sit" + (1 + rand(3));
			FreeSitLocator(pchar.GenQuest.Noblelombard.City + "_tavern", sTemp);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", pchar.GenQuest.Noblelombard.City + "_tavern", "sit", sTemp, "Nobleman_lombardTavern", 10); //reload4_back - таверна

			SetFunctionTimerCondition("Noblelombard_Over", 0, 0, 1, false); //таймер до конца суток
			ReOpenQuestHeader("Noblelombard");
			AddQuestRecord("Noblelombard", "1");
			AddQuestUserData("Noblelombard", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Noblelombard.City));
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			AddLandQuestMark_Gen_WithCondition(npchar, "Noblelombard", "Gen_Nobelman_Lombard_Waiting_QuestMarkCondition");
			sld = characterFromId(pchar.GenQuest.Noblelombard.City + "_usurer");
			AddLandQuestMark_Gen(sld, "Noblelombard");
		break;

		case "lombard_4":
			if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
			{
				pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
				dialog.text = StringFromKey("Nobleman_72", GetAddress_Form(NPChar));
				if (pchar.GenQuest.Noblelombard == "full") link.l1 = StringFromKey("Nobleman_73", pchar);
				if (pchar.GenQuest.Noblelombard == "maxpercent") link.l1 = StringFromKey("Nobleman_74", pchar);
				if (pchar.GenQuest.Noblelombard == "minpercent") link.l1 = StringFromKey("Nobleman_75", pchar);
				link.l1.go = "lombard_5";
				break;
			}
			if (pchar.GenQuest.Noblelombard == "fail")
			{
				dialog.text = StringFromKey("Nobleman_76", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Nobleman_77", pchar);
				link.l1.go = "lombard_fail";
			}
			else
			{
				dialog.text = StringFromKey("Nobleman_78", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Nobleman_79");
				link.l1.go = "exit";
				NextDiag.TempNode = "lombard_4";
			}
		break;

		case "lombard_fail":
			pchar.quest.Noblelombard_Over.over = "yes"; //снять таймер
			dialog.text = StringFromKey("Nobleman_80", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Nobleman_81", pchar, GetAddress_FormToNPC(NPChar));
			link.l1.go = "lombard_fail_1";
		break;

		case "lombard_fail_1":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddQuestRecord("Noblelombard", "4");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			CloseQuestHeader("Noblelombard");
			DeleteAttribute(Pchar, "quest.noblelombard");
			DeleteAttribute(Pchar, "GenQuest.Noblelombard");
			RemoveLandQuestMark_Gen(npchar, "Noblelombard");
		break;

		case "lombard_5":
			dialog.text = StringFromKey("Nobleman_82", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Nobleman_83");
			link.l1.go = "lombard_6";
		break;

		case "lombard_6":
			dialog.text = StringFromKey("Nobleman_84");
			link.l1 = "...";
			link.l1.go = "lombard_7";
		break;

		case "lombard_7":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			ChangeOfficersLoyality("good_all", 2);
			AddQuestRecord("Noblelombard", "5");
			AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
			SetFunctionTimerCondition("Noblelombard_Regard", 0, 0, 90, false); //таймер
			RemoveLandQuestMark_Gen(npchar, "Noblelombard");
			sld = characterFromId(pchar.GenQuest.Noblelombard.City + "_usurer");
			AddLandQuestMark_Gen_WithCondition(sld, "Noblelombard", "Gen_Nobelman_Lombard_UsurerRegard_QuestMarkCondition");
		break;
		//<-- семейная реликвия

		//------------------------------------------привезти рабов под заказ--------------------------------------------
		case "slaves":
			npchar.quest.slaves.price = 3 + drand(1);//цена на рабов в золотых самородках
			npchar.quest.slaves.qty = 50 + drand(5) * 10;//количество
			npchar.quest.slaves.money = sti(npchar.quest.slaves.qty) * sti(npchar.quest.slaves.price);
			dialog.text = StringFromKey("Nobleman_88", LinkRandPhrase(
						StringFromKey("Nobleman_85"),
						StringFromKey("Nobleman_86"),
						StringFromKey("Nobleman_87")), FindPeoplesString(sti(npchar.quest.slaves.qty), "Acc"), sti(npchar.quest.slaves.price));
			link.l1 = StringFromKey("Nobleman_89");
			link.l1.go = "slaves_1";
			/*if(CheckCharacterPerk(pchar, "Slavetrader"))
			link.l2 = "(Махинатор) О, это мой профиль, придётся тебе отсыпать побольше бабла";
			link.l2.go = "";*/
			link.l3 = StringFromKey("Nobleman_90");
			link.l3.go = "exit_slaves";
		break;

		case "exit_slaves":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			RemoveLandQuestMark_Gen(npchar, "Nobleslaves");
		break;

		case "slaves_1":
			dialog.text = StringFromKey("Nobleman_91");
			link.l1 = StringFromKey("Nobleman_92", GetAddress_FormToNPC(NPChar));
			link.l1.go = "slaves_2";
		break;

		case "slaves_2":
			DialogExit();
			TEV.NobleSlaves_NoblemanId = npchar.id;
			DeleteAttribute(npchar, "LifeDay");
			DeleteAttribute(npchar, "CityType");//удалить признак фантома, иначе - пустые города
			SaveCurrentNpcQuestDateParam(npchar, "slaves_date");//запоминаем дату
			LAi_SetActorType(npchar);

			//Rosarak ПРИШЛО ВРЕМЯ ФИКСИТЬ УСАДКУ NPC, Я ЖИВУ АКТИВНОЙ И ПОЛНОЦЕННОЙ ЖИЗНЬЮ, КАЖДЫЙ ДЕНЬ Я ФИКШУ УСАДКИ НПЦ
			sTemp = "sit" + (1 + rand(5));
			FreeSitLocator(npchar.city + "_church", sTemp);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city + "_church", "sit", sTemp, "Nobleslaves_Place", 10.0); //reload7_back - церковь

			chrDisableReloadToLocation = true;//закрыть локацию
			Colonies[FindColony(npchar.city)].questslaves = true;
			sTitle = npchar.city + "Nobleslaves";
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "Nobleslaves", "1");
			AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData(sTitle, "sName", GetFullName(npchar));
			AddQuestUserData(sTitle, "sQty", FindSlavesWithCaseString(sti(npchar.quest.slaves.qty), "Acc"));
			AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
			AddLandQuestMark_Gen_WithCondition(npchar, "Nobleslaves", "Gen_Nobelman_Slaves_Waiting_QuestMarkCondition");
		break;

		case "slaves_3":
			if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
			{
				dialog.text = StringFromKey("Nobleman_93", FindSlavesWithCaseString(sti(npchar.quest.slaves.qty), "Acc"));
				if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
				{
					link.l1 = StringFromKey("Nobleman_94", pchar);
					link.l1.go = "slaves_4";
				}
				else
				{
					link.l1 = StringFromKey("Nobleman_95");
					link.l1.go = "exit";
					NextDiag.TempNode = "slaves_3";
				}
			}
			else
			{
				dialog.text = StringFromKey("Nobleman_96");
				link.l1 = StringFromKey("Nobleman_97", pchar);
				link.l1.go = "slaves_8";
			}
		break;

		case "slaves_4":
			dialog.text = StringFromKey("Nobleman_98");
			link.l1 = StringFromKey("Nobleman_99");
			link.l1.go = "slaves_5";
		break;

		case "slaves_5":
			dialog.text = StringFromKey("Nobleman_100", sti(npchar.quest.slaves.price));
			link.l1 = StringFromKey("Nobleman_101");
			link.l1.go = "slaves_6";
		break;

		case "slaves_6":
			RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
			AddItemLog(pchar, "jewelry5", npchar.quest.slaves.money, StringFromKey("InfoMessages_170"), "Important_item");
			dialog.text = StringFromKey("Nobleman_102");
			link.l1 = StringFromKey("Nobleman_103", GetAddress_FormToNPC(NPChar));
			link.l1.go = "slaves_7";
		break;

		case "slaves_7":
			DialogExit();
			npchar.lifeday = 0;
			DeleteAttribute(&Colonies[FindColony(npchar.city)], "questslaves");
			LAi_SetActorType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.city + "_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Sailing", 50);//навигация
			AddCharacterExpToSkill(pchar, "Fortune", 30);//везение
			ChangeCharacterReputation(pchar, -2);
			sTitle = npchar.city + "Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "2");
			CloseQuestHeader(sTitle);
			RemoveLandQuestMark_Gen(npchar, "Nobleslaves");
		break;

		case "slaves_8":
			DialogExit();
			npchar.lifeday = 0;
			LAi_CharacterDisableDialog(npchar);
			DeleteAttribute(&Colonies[FindColony(npchar.city)], "questslaves");
			sTitle = npchar.city + "Nobleslaves";
			AddQuestRecordEx(sTitle, "Nobleslaves", "3");
			CloseQuestHeader(sTitle);
			RemoveLandQuestMark_Gen(npchar, "Nobleslaves");
		break;
		//<-- привезти рабов под заказ

		//замечание по обнаженному оружию от персонажей типа citizen
		/*case "CitizenNotBlade": //HardCoffee ref TODO подчистить, если всё норм
			dialog.text = NPCharSexPhrase(NPChar, StringFromKey("Nobleman_94"), StringFromKey("Nobleman_95"));
			link.l1 = LinkRandPhrase(StringFromKey("Nobleman_96"), StringFromKey("Nobleman_97"), StringFromKey("Nobleman_98"));
			link.l1.go = "exit";
		break;*/

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetHP(NPChar, 400, 400);
			TakeNItems(NPChar, "potion2", 3);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			LAi_group_MoveCharacter(NPChar, "TempFight");
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (drand(5))
	{
		case 0: sText = StringFromKey("Nobleman_104"); break;
		case 1: sText = StringFromKey("Nobleman_105"); break;
		case 2: sText = StringFromKey("Nobleman_106"); break;
		case 3: sText = StringFromKey("Nobleman_107"); break;
		case 4: sText = StringFromKey("Nobleman_108"); break;
		case 5: sText = StringFromKey("Nobleman_109"); break;
	}
	return sText;
}

void LombardText()
{
	switch (drand(5))
	{
		case 0:
			pchar.GenQuest.Noblelombard.Item = StringFromKey("Nobleman_110");
			pchar.GenQuest.Noblelombard.Text = StringFromKey("Nobleman_113", RandPhraseSimple(
						StringFromKey("Nobleman_111"),
						StringFromKey("Nobleman_112")));
		break;
		case 1: pchar.GenQuest.Noblelombard.Item = StringFromKey("Nobleman_114");
			pchar.GenQuest.Noblelombard.Text = StringFromKey("Nobleman_117", RandPhraseSimple(
						StringFromKey("Nobleman_115"),
						StringFromKey("Nobleman_116")));
		break;
		case 2:
			pchar.GenQuest.Noblelombard.Item = StringFromKey("Nobleman_118");
			pchar.GenQuest.Noblelombard.Text = StringFromKey("Nobleman_121", RandPhraseSimple(
						StringFromKey("Nobleman_119"),
						StringFromKey("Nobleman_120")));
		break;
		case 3:
			pchar.GenQuest.Noblelombard.Item = StringFromKey("Nobleman_122");
			pchar.GenQuest.Noblelombard.Text = StringFromKey("Nobleman_125", RandPhraseSimple(
						StringFromKey("Nobleman_123"),
						StringFromKey("Nobleman_124")));
		break;
		case 4:
			pchar.GenQuest.Noblelombard.Item = StringFromKey("Nobleman_126");
			pchar.GenQuest.Noblelombard.Text = StringFromKey("Nobleman_129", RandPhraseSimple(
						StringFromKey("Nobleman_127"),
						StringFromKey("Nobleman_128")));
		break;
		case 5:
			pchar.GenQuest.Noblelombard.Item = StringFromKey("Nobleman_130");
			pchar.GenQuest.Noblelombard.Text = StringFromKey("Nobleman_133", RandPhraseSimple(
						StringFromKey("Nobleman_131"),
						StringFromKey("Nobleman_132")));
		break;
	}
}

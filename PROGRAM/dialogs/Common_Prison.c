// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	ref NPChar, sld;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool ok;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\Prison\" + NPChar.City + "_Prison.c";
	if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// Линейка ле Баска. Второй квест.
		case "Old_campfire_Jail_exit":
			AddDialogExitQuest("Old_campfire_73");
			dialogexit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First time":
			NextDiag.TempNode = "First time";
			dialog.text = StringFromKey("Common_Prison_3", RandPhraseSimple(
						StringFromKey("Common_Prison_1"),
						StringFromKey("Common_Prison_2")));
			link.l1 = StringFromKey("Common_Prison_4", pchar);
			link.l1.go = "exit";
			link.l2 = StringFromKey("Common_Prison_5");

			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if ((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
					link.l2.go = "F_ShipLetters_1";
				else
					link.l2.go = "quests";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.ReasonToFast") && !CheckAttribute(pchar, "questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					link.l2.go = "ReasonToFast_Prison1";
				else
					link.l2.go = "quests";
			}

			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = StringFromKey("Common_Prison_6");
				link.l4.go = "ForGoodMove";
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = StringFromKey("Common_Prison_7", GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId)));
				link.l5.go = "KnowAboutPrisoner";
			}

			if (CheckAttribute(pchar, "GenQuest.CaptainComission.variant") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if (!CheckAttribute(pchar, "GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar, "GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakMayor"));
					if (pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = StringFromKey("Common_Prison_8", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")), pchar.GenQuest.CaptainComission.Name);
						link.l6.go = "CapComission_PrisonBad1";
					}
					if (pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = StringFromKey("Common_Prison_9", GetFullName(pchar), XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"), pchar.GenQuest.CaptainComission.Name);
						link.l6.go = "CapComission_PrisonGood1";
					}
				}
			}

			if (CheckAttribute(pchar, "GenQuest.EncGirl"))
			{
				if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if (pchar.GenQuest.EncGirl.Father == "fort_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = StringFromKey("Common_Prison_10");
						link.l9.go = "EncGirl_1";
					}
				}
			}

			// Квест тёмной личности "Похититель"
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = StringFromKey("Common_Prison_11");
				link.l12.go = "Marginpassenger";
			}

			// Квест "Правосудие на продажу" (Warship, Rosarak)
			if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = StringFromKey("Common_Prison_12", PChar.GenQuest.JusticeOnSale.SmugglerName);
				link.l13.go = "JusticeOnSale_1";
			}
		break;

		case "EncGirl_1":
			dialog.text = StringFromKey("Common_Prison_13");
			link.l1 = StringFromKey("Common_Prison_14", pchar);
			link.l1.go = "EncGirl_2";
		break;

		case "EncGirl_2":
			dialog.text = StringFromKey("Common_Prison_15");
			link.l1 = StringFromKey("Common_Prison_16", pchar);
			link.l1.go = "EncGirl_3";
		break;

		case "EncGirl_3":
			dialog.text = StringFromKey("Common_Prison_17");
			link.l1 = StringFromKey("Common_Prison_18");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;

		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = StringFromKey("Common_Prison_19");
			link.l1 = StringFromKey("Common_Prison_20", pchar.GenQuest.Marginpassenger.Name, pchar.GenQuest.Marginpassenger.q1Name, pchar.GenQuest.Marginpassenger.Text);
			link.l1.go = "Marginpassenger_1";
		break;

		case "Marginpassenger_1":
			dialog.text = StringFromKey("Common_Prison_21");
			link.l1 = StringFromKey("Common_Prison_22", pchar.GenQuest.Marginpassenger.q1Name, GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name"))), pchar.GenQuest.Marginpassenger.ShipName);
			link.l1.go = "Marginpassenger_2";
		break;

		case "Marginpassenger_2":
			dialog.text = StringFromKey("Common_Prison_23");
			link.l1 = StringFromKey("Common_Prison_24", pchar, XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity), pchar.GenQuest.Marginpassenger.q2Name);
			link.l1.go = "Marginpassenger_3";
		break;

		case "Marginpassenger_3":
			dialog.text = StringFromKey("Common_Prison_25");
			link.l1 = StringFromKey("Common_Prison_26");
			link.l1.go = "Marginpassenger_4";
		break;

		case "Marginpassenger_4":
			dialog.text = StringFromKey("Common_Prison_27", GetAddress_Form(NPChar), pchar.GenQuest.Marginpassenger.Name);
			link.l1 = StringFromKey("Common_Prison_28", pchar);
			link.l1.go = "Marginpassenger_5";
		break;

		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterReputation(pchar, 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100); // лидерство 
			ChangeContrabandRelation(pchar, -20);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
			//Rosarak: а пусть губер действительно "узнает" о нашем поступке
			sTemp = npchar.City;
			sld = CharacterFromId(sTemp + "_Mayor");
			IncreaseNPCDispositionEx(sld, pchar, false, 1);
		//if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp)) pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
		//pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
		//<-- Похититель

		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = StringFromKey("Common_Prison_29");
			link.l1 = StringFromKey("Common_Prison_30");
			if (makeint(pchar.reputation) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if (pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
			{
				// вилка_А
				dialog.text = StringFromKey("Common_Prison_31", pchar);
				link.l1 = StringFromKey("Common_Prison_32", pchar);
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";

				if (pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if (pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if (pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
			{
				// получена карта
				dialog.text = StringFromKey("Common_Prison_33", pchar);
				link.l1 = StringFromKey("Common_Prison_34", pchar);
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";
			}
			if (pchar.questTemp.ReasonToFast == "PatrolDied")
			{
				// патруль перебит
				dialog.text = StringFromKey("Common_Prison_35", pchar);
				link.l1 = StringFromKey("Common_Prison_36", pchar);
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}
		break;

		case "ReasonToFast_Prison_BadRep":
			if (pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
			{
				// вилка_А
				dialog.text = StringFromKey("Common_Prison_37", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
				link.l1 = StringFromKey("Common_Prison_38");
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";

				if (pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if (pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if (pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
			{
				// получена карта
				dialog.text = StringFromKey("Common_Prison_39");
				link.l1 = StringFromKey("Common_Prison_40");
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
			}
			if (pchar.questTemp.ReasonToFast == "PatrolDied")
			{
				// патруль перебит
				dialog.text = StringFromKey("Common_Prison_41");
				link.l1 = StringFromKey("Common_Prison_42");
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}
		break;

		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = StringFromKey("Common_Prison_43");
			link.l1 = StringFromKey("Common_Prison_44");
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterReputation(pchar, 1);
			GiveItem2Character(pchar, "mapQuest");
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = StringFromKey("Common_Prison_45");
			link.l1 = StringFromKey("Common_Prison_46");
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterReputation(pchar, 1);
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = StringFromKey("Common_Prison_47");
			link.l1 = StringFromKey("Common_Prison_48");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 1);
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar, "ReasonToFast");
		break;

		case "ReasonToFast_Prison_BadRep1":
			dialog.text = StringFromKey("Common_Prison_49", pchar);
			link.l1 = StringFromKey("Common_Prison_50");
			link.l1.go = "fight";

			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1 = "EnterToSea";
			pchar.quest.ReasonToFast_ExitFromTown.function = "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------

		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = StringFromKey("Common_Prison_51");
			link.l1 = StringFromKey("Common_Prison_52");
			link.l1.go = "CapComission_PrisonBad2";
		break;

		case "CapComission_PrisonBad2":
			dialog.text = StringFromKey("Common_Prison_53", pchar.GenQuest.CaptainComission.Name);
			link.l1 = StringFromKey("Common_Prison_54");
			link.l1.go = "CapComission_PrisonBad3";
		break;

		case "CapComission_PrisonBad3":
			dialog.text = StringFromKey("Common_Prison_55");
			link.l1 = StringFromKey("Common_Prison_56");
			link.l1.go = "fight";
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;

		case "CapComission_PrisonGood1":
			dialog.text = StringFromKey("Common_Prison_57");
			link.l1 = StringFromKey("Common_Prison_58");
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;

		case "CapComission_PrisonFree1":
			if (CheckAttribute(pchar, "GenQuest.CaptainComission")) //Лесник (Slayer). Разделение диалога на случай убийства
			{
				dialog.text = StringFromKey("Common_Prison_59");
				link.l1 = StringFromKey("Common_Prison_60");
				link.l1.go = "CapComission_PrisonFree2";
			}
			else
			{
				dialog.text = StringFromKey("Common_Prison_61", pchar);
				link.l2 = StringFromKey("Common_Prison_62", pchar);
				link.l2.go = "fight";
				NextDiag.TempNode = "First time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("OpenTheDoors");
			}
		break;

		case "CapComission_PrisonFree2":
			dialog.text = StringFromKey("Common_Prison_63");
			link.l1 = StringFromKey("Common_Prison_64");
			link.l1.go = "CapComission_PrisonFree3";
		break;

		case "CapComission_PrisonFree3":
			dialog.text = StringFromKey("Common_Prison_65");
			link.l1 = StringFromKey("Common_Prison_66");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("OpenTheDoors");
		break;

		// -------------------------- Операция 'Галеон' ----------------------------
		case "F_ShipLetters_1":
			dialog.text = StringFromKey("Common_Prison_67");
			link.l1 = StringFromKey("Common_Prison_68");
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;

		case "F_ShipLetters_2":
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = StringFromKey("Common_Prison_69");
				link.l1 = StringFromKey("Common_Prison_70");
				link.l1.go = "exit";
			}
			else
			{
				if (!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = StringFromKey("Common_Prison_71", FindMoneyString(sti(pchar.questTemp.different.GiveShipLetters.price2)));
					link.l1 = StringFromKey("Common_Prison_72");
					link.l1.go = "F_ShipLetters_3";
					link.l2 = StringFromKey("Common_Prison_73");
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = StringFromKey("Common_Prison_74", FindMoneyString(sti(pchar.questTemp.different.GiveShipLetters.price4)));
						link.l1 = StringFromKey("Common_Prison_75");
						link.l1.go = "F_ShipLetters_3";
						link.l2 = StringFromKey("Common_Prison_76");
						link.l2.go = "F_ShipLetters_4";
					}
					if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = StringFromKey("Common_Prison_77", FindMoneyString(sti(pchar.questTemp.different.GiveShipLetters.price3)));
						link.l1 = StringFromKey("Common_Prison_78");
						link.l1.go = "F_ShipLetters_3";
						link.l2 = StringFromKey("Common_Prison_79");
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;

		case "F_ShipLetters_3":
			dialog.text = StringFromKey("Common_Prison_80");
			link.l1 = StringFromKey("Common_Prison_81");
			link.l1.go = "exit";
		break;

		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook");
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
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
			if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
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

			if ((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{
				ChangeCharacterReputation(pchar, -1);
				OfficersReaction("bad");
			}
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "ForGoodMove":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Common_Prison_82"),
						StringFromKey("Common_Prison_83"),
						StringFromKey("Common_Prison_84"),
						StringFromKey("Common_Prison_85"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Common_Prison_86", pchar),
						StringFromKey("Common_Prison_87", pchar),
						StringFromKey("Common_Prison_88"),
						StringFromKey("Common_Prison_89"), npchar, Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;

		case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = (dRand(15) + 10) * 100;
			// if(sti(colonies[FindColony(npchar.city)].jail) && sti(pchar.money) >= sti(pchar.questTemp.jailCanMove.money))
			if (CheckAttribute(npchar, "jailTakeMoney") && sti(npchar.jailTakeMoney) && sti(pchar.money) >= sti(pchar.questTemp.jailCanMove.money))
			{
				dialog.text = StringFromKey("Common_Prison_90", FindMoneyString(sti(pchar.questTemp.jailCanMove.money)));
				link.l1 = StringFromKey("Common_Prison_91", pchar);
				link.l1.go = "ForGoodMove_agree";
				link.l2 = StringFromKey("Common_Prison_92");
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_Prison_95", RandPhraseSimple(
							StringFromKey("Common_Prison_93"),
							StringFromKey("Common_Prison_94")));
				link.l1 = StringFromKey("Common_Prison_96");
				link.l1.go = "exit";
			}
		break;
		case "ForGoodMove_agree":
			dialog.text = StringFromKey("Common_Prison_97");
			link.l1 = StringFromKey("Common_Prison_98");
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.jailCanMove.money));
		break;

		case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = StringFromKey("Common_Prison_99"); break;
				case "1": sTemp = StringFromKey("Common_Prison_100"); break;
				case "2": sTemp = StringFromKey("Common_Prison_101"); break;
				case "3": sTemp = StringFromKey("Common_Prison_102"); break;
				case "4": sTemp = StringFromKey("Common_Prison_103"); break;
				case "5": sTemp = StringFromKey("Common_Prison_104"); break;
				case "6": sTemp = StringFromKey("Common_Prison_105"); break;
			}
			dialog.text = sTemp;
			link.l1 = StringFromKey("Common_Prison_106");
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;

		case "KnowAboutPrisoner_0":
			dialog.text = StringFromKey("Common_Prison_107");
			link.l1 = StringFromKey("Common_Prison_108");
			link.l1.go = "notFree_exit";
		break;

		case "KnowAboutPrisoner_1":
			dialog.text = StringFromKey("Common_Prison_109");
			link.l1 = StringFromKey("Common_Prison_110");
			link.l1.go = "notFree_exit";
		break;

		case "KnowAboutPrisoner_2":
			dialog.text = StringFromKey("Common_Prison_111");
			link.l1 = StringFromKey("Common_Prison_112");
			link.l1.go = "notFree_exit";
		break;

		case "KnowAboutPrisoner_3":
			dialog.text = StringFromKey("Common_Prison_113");
			link.l1 = StringFromKey("Common_Prison_114");
			link.l1.go = "notFree_exit";
		break;

		case "KnowAboutPrisoner_4":
			dialog.text = StringFromKey("Common_Prison_115");
			link.l1 = StringFromKey("Common_Prison_116");
			link.l1.go = "KnowAboutPrisoner_free";
		break;

		case "KnowAboutPrisoner_5":
			dialog.text = StringFromKey("Common_Prison_117");
			link.l1 = StringFromKey("Common_Prison_118");
			link.l1.go = "KnowAboutPrisoner_free";
		break;

		case "KnowAboutPrisoner_6":
			dialog.text = StringFromKey("Common_Prison_119");
			link.l1 = StringFromKey("Common_Prison_120");
			link.l1.go = "KnowAboutPrisoner_free";
		break;

		case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = (rand(3) + 2) * 1000;
			if (sti(pchar.money) > sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				dialog.text = StringFromKey("Common_Prison_121", FindMoneyString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)));
				link.l1 = StringFromKey("Common_Prison_122", pchar);
				link.l1.go = "KnowAboutPrisoner_agree";
				link.l2 = StringFromKey("Common_Prison_123");
				link.l2.go = "KnowAboutPrisoner_exit";
			}
			else
			{
				dialog.text = StringFromKey("Common_Prison_124");
				link.l1 = StringFromKey("Common_Prison_125");
				link.l1.go = "exit";
			}
		break;
		case "KnowAboutPrisoner_agree":
			dialog.text = StringFromKey("Common_Prison_126");
			link.l1 = StringFromKey("Common_Prison_127");
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		case "KnowAboutPrisoner_exit":
			dialog.text = StringFromKey("Common_Prison_128");
			link.l1 = StringFromKey("Common_Prison_129", pchar);
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;

		case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//---------------- Протектор ------------------
		case "First_protector":
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = StringFromKey("Common_Prison_132", RandPhraseSimple(
							StringFromKey("Common_Prison_130"),
							StringFromKey("Common_Prison_131")));
				link.l1 = StringFromKey("Common_Prison_133");
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = StringFromKey("Common_Prison_136", RandPhraseSimple(
							StringFromKey("Common_Prison_134"),
							StringFromKey("Common_Prison_135")));
				link.l1 = StringFromKey("Common_Prison_139", RandPhraseSimple(
							StringFromKey("Common_Prison_137"),
							StringFromKey("Common_Prison_138")));
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
		case "First_soldier":
		/*//HardCoffee TODO: гварды на входе не реагируют на врагов и пиратов
		int iNPCharnation = sti(NPChar.nation);
		if (sti(pchar.nation) == PIRATE && iNPCharnation != PIRATE) // заглушка на пирата
		{
			dialog.text = RandPhraseSimple(StringFromKey("Common_Soldier_1", GetSexPhrase(StringFromKey("SexPhrase_54"),StringFromKey("SexPhrase_55"))), StringFromKey("Common_Soldier_2", GetSexPhrase(StringFromKey("SexPhrase_54"),StringFromKey("SexPhrase_55"))));
			link.l1 = RandPhraseSimple(StringFromKey("Common_Soldier_3"), StringFromKey("Common_Soldier_4"));
			link.l1.go = "fight";
			break;
		}
		if (GetNationRelation2MainCharacter(iNPCharnation) == RELATION_ENEMY && iNPCharnation != PIRATE)
		{
			dialog.text = RandPhraseSimple(StringFromKey("Common_Soldier_6"), StringFromKey("Common_Soldier_5", GetSexPhrase(StringFromKey("SexPhrase_54"),StringFromKey("SexPhrase_55"))));
			link.l1 = RandPhraseSimple(StringFromKey("Common_Soldier_7"), StringFromKey("Common_Soldier_8"));
			link.l1.go = "fight";
			break;
		}
		if (GetNationRelation(iNPCharnation, GetBaseHeroNation()) == RELATION_ENEMY && iNPCharnation != PIRATE)
		{
			if (loadedLocation.id == "Santiago_Incquisitio") dialog.text = StringFromKey("Common_Soldier_9");
			else dialog.text = RandPhraseSimple(StringFromKey("Common_Soldier_9"), StringFromKey("Common_Soldier_10"));
			//==> по лицензии, если есть
			if (CheckNationLicence(iNPCharnation))
			{
				link.l1 = StringFromKey("Common_Soldier_11", GetRusNameNationLicence(iNPCharnation));
				link.l1.go = "LicenceOk";
			}
			//==> и по флагу в любом случае
			if (HasSubStr(pchar.location.from_sea, "_town")) //если причалил в городе
			{	//не видит, он в данже сидит
				link.l2 = StringFromKey("Common_Soldier_12", NationNameGenitive(sti(pchar.nation)));
			}
			else //если причалил не в городе
			{	//find ship location
				link.l2 = StringFromKey("Common_Soldier_13", GetSexPhrase("",StringFromKey("SexEnding_1")), XI_ConvertString(GetIslandNameByCity(npchar.city)+"Gen"), NationNameGenitive(sti(pchar.nation)));
			}
			link.l2.go = CheckSneakByGuards(iNPCharnation);
		}
		else*/
				{
			dialog.text = StringFromKey("Common_Prison_142", RandPhraseSimple(
						StringFromKey("Common_Prison_140"),
						StringFromKey("Common_Prison_141")));
			link.l1 = StringFromKey("Common_Prison_143");
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		}
		break;
		//---------------- Заключенные ------------------
		case "First_prisoner":
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = StringFromKey("Common_Prison_147", LinkRandPhrase(
							StringFromKey("Common_Prison_144"),
							StringFromKey("Common_Prison_145", pchar),
							StringFromKey("Common_Prison_146")));
				link.l1 = StringFromKey("Common_Prison_150", RandPhraseSimple(
							StringFromKey("Common_Prison_148"),
							StringFromKey("Common_Prison_149")));
				link.l1.go = "NoMoreTalkExit";
				if (idRand(npchar.id + "jailCanMove", 10) > 7 && !CheckAttributeMass(pchar, "quest", "GivePrisonFree_Death,GivePrisonFree_Over,DeliverToBander", "|"))
				{
					dialog.text = StringFromKey("Common_Prison_153", RandPhraseSimple(
								StringFromKey("Common_Prison_151", pchar),
								StringFromKey("Common_Prison_152", pchar)));
					link.l1 = StringFromKey("Common_Prison_154");
					link.l1.go = "Prisoner_1"; // на квест освобождения заключенного
				}
			}
			else
			{
				dialog.text = StringFromKey("Common_Prison_158", LinkRandPhrase(
							StringFromKey("Common_Prison_155"),
							StringFromKey("Common_Prison_156", pchar),
							StringFromKey("Common_Prison_157")));
				link.l1 = StringFromKey("Common_Prison_161", RandPhraseSimple(
							StringFromKey("Common_Prison_159"),
							StringFromKey("Common_Prison_160")));
				link.l1.go = "NoMoreTalkExit";

				if (CheckAttribute(pchar, "quest.GivePrisonFree_Over")) iTemp = -1;
				else if (CheckAttribute(pchar, "quest.DeliverToBander") && !CheckAttribute(pchar, "quest.GivePrisonFree_Death")) iTemp = 1;
				else if (CheckAttribute(pchar, "quest.GivePrisonFree_Death") && !CheckAttribute(pchar, "quest.DeliverToBander")) iTemp = 0;
				else if (CheckAttribute(pchar, "quest.DeliverToBander") && CheckAttribute(pchar, "quest.GivePrisonFree_Death")) iTemp = -1;
				else iTemp = rand(1);
				if (iTemp != -1 && idRand(npchar.id + "jailCanMove", 10) > 7 && !sti(colonies[FindColony(npchar.city)].HeroOwn))
				{
					dialog.text = StringFromKey("Common_Prison_164", RandPhraseSimple(
								StringFromKey("Common_Prison_162", pchar),
								StringFromKey("Common_Prison_163", pchar)));
					link.l1 = StringFromKey("Common_Prison_165");
					if (iTemp)
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключенного
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключенного --------------------
		case "Prisoner_1":
			dialog.text = StringFromKey("Common_Prison_166");
			link.l1 = StringFromKey("Common_Prison_167");
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
			npchar.nation = PIRATE; //если заключенный бежит, значит пират
		break;
		case "Prisoner_2":
			dialog.text = StringFromKey("Common_Prison_168", pchar);
			link.l1 = StringFromKey("Common_Prison_169");
			link.l1.go = "Prisoner_3";
		break;
		case "Prisoner_3":
			dialog.text = StringFromKey("Common_Prison_170", GetFullName(npchar), XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Acc"));
			link.l1 = StringFromKey("Common_Prison_171");
			link.l1.go = "Prisoner_4";
		break;
		case "Prisoner_4":
			dialog.text = StringFromKey("Common_Prison_172");
			link.l1 = StringFromKey("Common_Prison_173");
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(colonies[FindColony(npchar.city)].nation)) != RELATION_ENEMY && LAi_grp_playeralarm == 0)
			{
				link.l2 = StringFromKey("Common_Prison_174", XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Acc"));
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				link.l3 = StringFromKey("Common_Prison_175");
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = StringFromKey("Common_Prison_176", XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Acc"));
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
		case "Prisoner_5":
			dialog.text = StringFromKey("Common_Prison_179", RandPhraseSimple(
						StringFromKey("Common_Prison_177", pchar),
						StringFromKey("Common_Prison_178")));
			link.l1 = StringFromKey("Common_Prison_182", RandPhraseSimple(
						StringFromKey("Common_Prison_180"),
						StringFromKey("Common_Prison_181")));
			link.l1.go = "NoMoreTalkExit";
		break;
		case "Prisoner_agree":
			dialog.text = StringFromKey("Common_Prison_183");
			link.l1 = StringFromKey("Common_Prison_184");
			link.l1.go = "Prisoner_agree_1";
		break;
		case "Prisoner_agree_1":
			dialog.text = StringFromKey("Common_Prison_185", pchar);
			link.l1 = StringFromKey("Common_Prison_186");
			link.l1.go = "Prisoner_agree_2";
		break;
		case "Prisoner_agree_2":
			sTemp = GetNationNameByType(sti(colonies[FindColony(npchar.city)].nation)) + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(colonies[FindColony(npchar.city)].nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
			AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Pre"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			pchar.quest.PrisonerEnterToSea.win_condition.l1 = "EnterToSea";
			pchar.quest.PrisonerEnterToSea.win_condition = "PrisonerEnterToSea";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "Prisoner_agree_3":
			dialog.text = StringFromKey("Common_Prison_187");
			link.l1 = StringFromKey("Common_Prison_188");
			link.l1.go = "Prisoner_agree_4";
		break;
		case "Prisoner_agree_4":
			sTemp = GetNationNameByType(sti(colonies[FindColony(npchar.city)].nation)) + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
			AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Pre"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			pchar.quest.PrisonerEnterToSea.win_condition.l1 = "EnterToSea";
			pchar.quest.PrisonerEnterToSea.win_condition = "PrisonerEnterToSea";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

		case "ToPrisonHead_agree":
			dialog.text = StringFromKey("Common_Prison_189");
			link.l1 = StringFromKey("Common_Prison_190");
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.MayorId = characters[GetCharacterIndex(npchar.city + "_Mayor")].id; //Id мэра
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

		case "ToPrisonHead_canMove":
			dialog.text = StringFromKey("Common_Prison_191", pchar);
			link.l1 = StringFromKey("Common_Prison_192");
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
		case "ToPrisonHead_canMove_1":
			dialog.text = StringFromKey("Common_Prison_193");
			link.l1 = StringFromKey("Common_Prison_194", XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Acc"));
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
		case "ToPrisonHead_canMove_2":
			dialog.text = StringFromKey("Common_Prison_195");
			link.l1 = StringFromKey("Common_Prison_196");
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
		case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
			AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId + "Pre"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			pchar.quest.PrisonerEnterToSea.win_condition.l1 = "EnterToSea";
			pchar.quest.PrisonerEnterToSea.win_condition = "PrisonerEnterToSea";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

		case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = StringFromKey("Common_Prison_197"); break;
				case "1": sTemp = StringFromKey("Common_Prison_198"); break;
				case "2": sTemp = StringFromKey("Common_Prison_199"); break;
				case "3": sTemp = StringFromKey("Common_Prison_200"); break;
				case "4": sTemp = StringFromKey("Common_Prison_201"); break;
				case "5": sTemp = StringFromKey("Common_Prison_202"); break;
				case "6": sTemp = StringFromKey("Common_Prison_203"); break;
			}
			dialog.text = StringFromKey("Common_Prison_204", pchar);
			link.l1 = StringFromKey("Common_Prison_205", sTemp);
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;

		case "ToPrisonHead_notFree_1":
			dialog.text = StringFromKey("Common_Prison_206");
			link.l1 = StringFromKey("Common_Prison_207");
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = StringFromKey("Common_Prison_208");
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;

		case "ToPrisonHead_notFree_2":
			dialog.text = StringFromKey("Common_Prison_211", RandPhraseSimple(
						StringFromKey("Common_Prison_209", pchar),
						StringFromKey("Common_Prison_210")));
			link.l1 = StringFromKey("Common_Prison_212");
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

		case "ToPrisonHead_expansive":
			dialog.text = StringFromKey("Common_Prison_213", pchar);
			link.l1 = StringFromKey("Common_Prison_214", pchar);
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
		case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = StringFromKey("Common_Prison_215");
					link.l1 = StringFromKey("Common_Prison_216");
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = StringFromKey("Common_Prison_217");
					link.l1 = StringFromKey("Common_Prison_218");
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = StringFromKey("Common_Prison_219");
					link.l1 = StringFromKey("Common_Prison_220");
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = StringFromKey("Common_Prison_221");
					link.l1 = StringFromKey("Common_Prison_222", pchar);
					link.l1.go = "Node_3";
				break;
				case 4:
					dialog.text = StringFromKey("Common_Prison_223");
					link.l1 = StringFromKey("Common_Prison_224");
					link.l1.go = "Node_4";
				break;
			}
		break;

		case "Node_1":
			dialog.text = StringFromKey("Common_Prison_225");
			link.l1 = StringFromKey("Common_Prison_226");
			link.l1.go = "PrisonerInPlace_3";
			LogSound_WithNotify(StringFromKey("InfoMessages_197"), "Important_item", "Icollection");
			TakeNItems(pchar, "incas_collection", 1 + drand(1));
			TakeNItems(pchar, "chest", 4 + drand(4));
			TakeNItems(pchar, "jewelry1", 70 + rand(15));
			TakeNItems(pchar, "jewelry2", 50 + rand(15));
			TakeNItems(pchar, "jewelry3", 60 + rand(15));
			TakeNItems(pchar, "jewelry4", 40 + rand(10));
			TakeNItems(pchar, "jewelry15", 10 + rand(10));
			TakeNItems(pchar, "jewelry18", 60 + rand(20));
			TakeNItems(pchar, "jewelry14", 40 + rand(15));
			TakeNItems(pchar, "jewelry7", 60 + rand(20));
			// evganat - энциклопедия
			if (CheckRandomPage("questprisoner", "treasure", 1))
			{
				GetPage(GetRandomTome(), 5);
			}
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;

		case "Node_2":
			dialog.text = StringFromKey("Common_Prison_227");
			link.l1 = StringFromKey("Common_Prison_228");
			link.l1.go = "PrisonerInPlace_3";
			sTemp = pchar.questTemp.jailCanMove.Item1;
			AddItemLog(pchar, sTemp, "1", StringFromKey("InfoMessages_162", GetItemName(sTemp)), "Important_item");
			TakeNItems(pchar, "jewelry5", 40 + rand(10));
			TakeNItems(pchar, "jewelry6", 20 + rand(20));
			TakeNItems(pchar, "jewelry17", 80 + rand(20));
			TakeNItems(pchar, "jewelry13", 10 + rand(10));
			TakeNItems(pchar, "jewelry11", 20 + rand(20));
			TakeNItems(pchar, "jewelry12", 50 + rand(20));
			// evganat - энциклопедия
			if (CheckRandomPage("questprisoner", "treasure", 2))
			{
				GetPage(GetRandomTome(), 5);
			}
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;

		case "Node_3":
			dialog.text = StringFromKey("Common_Prison_229");
			link.l1 = StringFromKey("Common_Prison_230", pchar);
			link.l1.go = "PrisonerInPlace_3";
			sTemp = pchar.questTemp.jailCanMove.Item2;
			AddItemLog(pchar, sTemp, "1", StringFromKey("InfoMessages_163", GetItemName(sTemp)), "Important_item");
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;

		case "Node_4":
			dialog.text = StringFromKey("Common_Prison_231");
			link.l1 = StringFromKey("Common_Prison_232");
			link.l1.go = "Node_4_1";
		break;

		case "Node_4_1":
			dialog.text = StringFromKey("Common_Prison_233");
			link.l1 = StringFromKey("Common_Prison_234");
			link.l1.go = "Node_4_2";
		break;

		case "Node_4_2":
			if (CheckCharacterItem(pchar, "map_part1"))
			{
				GiveItem2Character(pchar, "map_part2");
			}
			else
			{
				GiveItem2Character(pchar, "map_part1");
			}
			dialog.text = StringFromKey("Common_Prison_235");
			link.l1 = StringFromKey("Common_Prison_236");
			link.l1.go = "PrisonerInPlace_4";
		break;

		case "PrisonerInPlace_1":
			dialog.text = StringFromKey("Common_Prison_237", pchar);
			link.l1 = StringFromKey("Common_Prison_238");
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;

		case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

			Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
			Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
			Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;

		case "PrisonerInPlace_3":
			dialog.text = StringFromKey("Common_Prison_239");
			link.l1 = StringFromKey("Common_Prison_240");
			link.l1.go = "PrisonerInPlace_2";
		break;

		case "PrisonerInPlace_4":
			dialog.text = StringFromKey("Common_Prison_241");
			link.l1 = StringFromKey("Common_Prison_242");
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;

		// -------------------- освобождение заключенного --------------------
		// ------------------------ передать маляву --------------------------
		case "Deliver_1":
			dialog.text = StringFromKey("Common_Prison_243", GetFullName(npchar));
			link.l1 = StringFromKey("Common_Prison_244");
			link.l1.go = "Deliver_2";
		break;
		case "Deliver_2":
			dialog.text = StringFromKey("Common_Prison_245");
			link.l1 = StringFromKey("Common_Prison_246");
			link.l1.go = "Deliver_3";
		break;
		case "Deliver_3":
			dialog.text = StringFromKey("Common_Prison_247");
			link.l1 = StringFromKey("Common_Prison_248");
			link.l1.go = "Prisoner_5";
			link.l2 = StringFromKey("Common_Prison_249");
			link.l2.go = "Deliver_agree";
		break;
		case "Deliver_agree":
			dialog.text = StringFromKey("Common_Prison_250");
			link.l1 = StringFromKey("Common_Prison_251");
			link.l1.go = "Deliver_4";
		break;
		case "Deliver_4":
			dialog.text = StringFromKey("Common_Prison_252");
			link.l1 = StringFromKey("Common_Prison_253");
			link.l1.go = "Deliver_5";
		break;
		case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetRandomCommonLoc(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = StringFromKey("Common_Prison_254");
				link.l1 = StringFromKey("Common_Prison_255");
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = StringFromKey("Common_Prison_256", pchar);
				link.l1 = StringFromKey("Common_Prison_257");
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6) * 500 + 500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true;
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("MalyavaDeliver");
				AddQuestRecord("MalyavaDeliver", "1");
				AddQuestUserData("MalyavaDeliver", "sSex", GetSexPhrase("ся", "ась"));
				AddQuestUserData("MalyavaDeliver", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
				AddQuestUserData("MalyavaDeliver", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;

		// "Правосудие на продажу" (Warship, Rosarak)
		case "JusticeOnSale_1":
			dialog.text = StringFromKey("Common_Prison_258", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Common_Prison_259");
			link.l1.go = "JusticeOnSale_3";
			link.l2 = StringFromKey("Common_Prison_260");
			link.l2.go = "JusticeOnSale_2";
		break;

		case "JusticeOnSale_2":
			NextDiag.TempNode = "First time";
			dialog.text = StringFromKey("Common_Prison_261", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Common_Prison_262");
			link.l1.go = "exit";
		break;

		case "JusticeOnSale_3":
			dialog.text = StringFromKey("Common_Prison_263", GetFullName(PChar));
			link.l1 = StringFromKey("Common_Prison_264", pchar);
			link.l1.go = "JusticeOnSale_4";
		break;

		case "JusticeOnSale_4":
			dialog.text = StringFromKey("Common_Prison_265");
			link.l1 = StringFromKey("Common_Prison_266");
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			if (sti(PChar.money) >= 5000)
			{
				link.l2 = StringFromKey("Common_Prison_267");
				link.l2.go = "JusticeOnSale_5";
			}
		break;

		case "JusticeOnSale_5_WithoutMoney":
		//			iTemp = GetCharacterSPECIAL(pchar, "Luck") + GetCharacterSPECIAL(pchar, "Charisma");
		//			if(iTemp > idRand(npchar.id + "JusticeOnSale_WithoutMoney", 20) && !isBadReputation(pchar, 40))
			if (PlayerRPGCheck_SPECIAL_Sum("Luck,Charisma", idRand(npchar.id + "JusticeOnSale_WithoutMoney", 20)) && !PlayerRPGCheck_BadReputation(40, false))
			{
				AddCharacterExpToSkill(pchar, "Fortune", 50);
				PChar.GenQuest.JusticeOnSale.Persuade = true;
				dialog.text = StringFromKey("Common_Prison_268", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_Prison_269");
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = StringFromKey("Common_Prison_270", GetAddress_Form(NPChar), PChar.GenQuest.JusticeOnSale.SmugglerName);
				link.l1 = StringFromKey("Common_Prison_271", GetAddress_FormToNPC(NPChar));
				link.l1.go = "exit";
			}
		break;

		case "JusticeOnSale_5":
		//			iTemp = GetCharacterSPECIAL(pchar, "Luck") + GetCharacterSPECIAL(pchar, "Charisma");
		//			if(iTemp > idRand(npchar.id + "JusticeOnSale", 15) && !isBadReputation(pchar, 25))
			if (PlayerRPGCheck_SPECIAL_Sum("Luck,Charisma", idRand(npchar.id + "JusticeOnSale", 15)) && !PlayerRPGCheck_BadReputation(25, false))
			{
				AddMoneyToCharacter(PChar, -5000);
				PChar.GenQuest.JusticeOnSale.Persuade = true;
				PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
				dialog.text = StringFromKey("Common_Prison_272");
				link.l1 = StringFromKey("Common_Prison_273");
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				ChangeCharacterReputation(PChar, -3);
				dialog.text = StringFromKey("Common_Prison_274", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Common_Prison_275");
				link.l1.go = "exit";
			}
		break;

		case "JusticeOnSale_6":
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
			DialogExit();
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0:
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1:
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2:
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3:
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch (rand(8))
	{
		case 0:
			itemID = "indian6";
		break;
		case 1:
			itemID = "indian10";
		break;
		case 2:
			itemID = "indian12";
		break;
		case 3:
			itemID = "indian19";
		break;
		case 4:
			itemID = "indian20";
		break;
		case 5:
			itemID = "indian22";
		break;
		case 6:
			itemID = "indian21";
		break;
		case 7:
			itemID = "sculMa2";
		break;
		case 8:
			itemID = "sculMa1";
		break;

	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch (rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade22");
		break;
		case 1:
			itemID = GetGeneratedItem("blade19");
		break;
		case 2:
			itemID = GetGeneratedItem("blade31");
		break;
		case 3:
			itemID = "cirass4";
		break;
		case 4:
			itemID = GetGeneratedItem("blade21");
		break;
		case 5:
			itemID = "spyglass4";
		break;
		case 6:
			itemID = GetGeneratedItem("blade15");
		break;
		case 7:
			itemID = GetGeneratedItem("blade34");
		break;
		case 8:
			itemID = "cirass3";
		break;
	}
	return itemID;
}

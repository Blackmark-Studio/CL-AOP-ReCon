// Соукинс в Пуэрто-Принсипе
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			dialog.text = StringFromKey("RichardSoukins_1", pchar);
			link.l1 = StringFromKey("RichardSoukins_2");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (pchar.questTemp.piratesLine == "Soukins_toPuertoPrincipe")
			{
				link.l1 = StringFromKey("RichardSoukins_3", pchar);
				link.l1.go = "PL_Q7_1";
			}

			//if (Pchar.BaseNation == PIRATE) Доступно всем. Konstrush
			//{
			if (!CheckAttribute(PChar, "questTemp.pirateStartQuest"))
			{
				link.l2 = StringFromKey("RichardSoukins_4");
				link.l2.go = "pirateStartQuest";
			}
			else
			{
				if (pchar.questTemp.pirateStartQuest == "3" && !CheckAttribute(PChar, "questTemp.pirateStartQuest.many") && npchar.city == pchar.questTemp.pirateStartQuest.City)
				{
					link.l2 = StringFromKey("RichardSoukins_5", pchar);
					link.l2.go = "pirateStartQuest_many";
				}
				if (pchar.questTemp.pirateStartQuest == "3" && GetCharacterItem(pchar, "pirateStartQuest") > 0 && npchar.city == pchar.questTemp.pirateStartQuest.City)
				{
					link.l2 = StringFromKey("RichardSoukins_6", pchar);
					link.l2.go = "pirateStartQuest_info_1";
				}
				if (pchar.questTemp.pirateStartQuest == "5" && npchar.city == pchar.questTemp.pirateStartQuest.City)
				{
					link.l2 = StringFromKey("RichardSoukins_7");
					link.l2.go = "pirateStartQuest_final";
				}
			}
			if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "takeRumour"))
			{
				link.l3 = StringFromKey("RichardSoukins_8");
				link.l3.go = "SharpPearl_1";
			}

			if (CheckAttribute(PChar, "questTemp.pSQ_Bacchus") && CheckAttribute(PChar, "questTemp.pirateStartQuest"))
			{
				if (pchar.questTemp.pSQ_Bacchus == "to_Baron" && npchar.city == pchar.questTemp.pirateStartQuest.City && GetSquadronGoods(pchar, GOOD_SLAVES) >= 200)
				{
					link.l4 = StringFromKey("RichardSoukins_9");
					link.l4.go = "pirateStartQuest_BacchusSlaves";
				}

				if (pchar.questTemp.pSQ_Bacchus == "to_Baron_noTalk" && npchar.city == pchar.questTemp.pirateStartQuest.City && GetSquadronGoods(pchar, GOOD_SLAVES) >= 200)
				{
					link.l4 = StringFromKey("RichardSoukins_10");
					link.l4.go = "pirateStartQuest_BacchusSlaves_NoTalk";
				}
			}
		//}
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			LAi_LocationFightDisable(loadedLocation, false);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		//zagolski. начальный квест за пирата ===================================
		case "pirateStartQuest":
			dialog.text = StringFromKey("RichardSoukins_11", pchar);
			link.l1 = StringFromKey("RichardSoukins_12");
			link.l1.go = "pirateStartQuest_1";
			link.l2 = StringFromKey("RichardSoukins_13");
			link.l2.go = "exit";
			pchar.questTemp.pirateStartQuest = "0";
			pirateStartQuest_Begin_DelQuestMarks();
		break;
		case "pirateStartQuest_1":
			dialog.text = StringFromKey("RichardSoukins_14");
			link.l1 = StringFromKey("RichardSoukins_15", pchar);
			link.l1.go = "pirateStartQuest_2";
		break;
		case "pirateStartQuest_2":
			dialog.text = StringFromKey("RichardSoukins_16");
			link.l1 = StringFromKey("RichardSoukins_17");
			link.l1.go = "pirateStartQuest_3";
			link.l2 = StringFromKey("RichardSoukins_18");
			link.l2.go = "exit";
		break;
		case "pirateStartQuest_3":
			dialog.text = StringFromKey("RichardSoukins_19");
			link.l1 = StringFromKey("RichardSoukins_20");
			link.l1.go = "pirateStartQuest_4";

			pchar.questTemp.pirateStartQuest = "1";
			pchar.questTemp.pirateStartQuest.City = npchar.city;
			pchar.questTemp.pirateStartQuest.Areal = GetArealByCityName(pchar.questTemp.pirateStartQuest.City);
			pchar.questTemp.pirateStartQuest.BaronId = npchar.id;

			AddQuestRecord("pSQ", "1");
			AddQuestUserData("pSQ", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ", "sName", GetFullName(npchar));

			AddLandQuestMark_Main(CharacterFromID("Santiago_tavernkeeper"), "pSQ");
		break;
		case "pirateStartQuest_4":
			dialog.text = StringFromKey("RichardSoukins_21");
			link.l1 = StringFromKey("RichardSoukins_22");
			link.l1.go = "exit";
		break;

		case "pirateStartQuest_many":
			dialog.text = StringFromKey("RichardSoukins_23");
			link.l1 = StringFromKey("RichardSoukins_24");
			link.l1.go = "pirateStartQuest_many_1";
		break;
		case "pirateStartQuest_many_1":
			dialog.text = StringFromKey("RichardSoukins_25");
			link.l1 = StringFromKey("RichardSoukins_26");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 5000);
			pchar.questTemp.pirateStartQuest.many = "";
			RemoveLandQuestMark_Main(npchar, "pSQ");
		break;

		//------------------------------------
		case "pirateStartQuest_info_1":
			dialog.text = StringFromKey("RichardSoukins_27");
			link.l1 = StringFromKey("RichardSoukins_28", pchar);
			link.l1.go = "pirateStartQuest_info_2";
			TakeItemFromCharacter(pchar, "pirateStartQuest");
		break;
		case "pirateStartQuest_info_2":
			dialog.text = StringFromKey("RichardSoukins_29", pchar);
			link.l1 = StringFromKey("RichardSoukins_30");
			if (!CheckAttribute(pchar, "questTemp.pSQ_Bacchus"))
			{
				link.l1.go = "pirateStartQuest_info_3_Bacchus";
			}
			else
			{
				link.l1.go = "pirateStartQuest_info_3";
			}
			link.l2 = StringFromKey("RichardSoukins_31");
			link.l2.go = "pirateStartQuest_info_noex";
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "pirateStartQuest_info_noex":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "0";
			CloseQuestHeader("pSQ");
			RemoveLandQuestMark_Main(npchar, "pSQ");
		break;
		case "pirateStartQuest_info_3_Bacchus":
			dialog.text = StringFromKey("RichardSoukins_32");
			link.l1 = StringFromKey("RichardSoukins_33");
			link.l1.go = "pirateStartQuest_info_3_Bacchus_1";

			link.l2 = StringFromKey("RichardSoukins_34");
			link.l2.go = "pirateStartQuest_info_3_Bacchus_2";
		break;
		case "pirateStartQuest_info_3_Bacchus_1":
			dialog.text = StringFromKey("RichardSoukins_35");
			link.l1 = StringFromKey("RichardSoukins_36");
			link.l1.go = "pirateStartQuest_info_3";

			// СЖ запись
			pchar.questTemp.pSQ_Bacchus = "to_Bacchus";
			AddQuestRecord("pSQ_Bacchus", "1");
			AddQuestUserData("pSQ_Bacchus", "sCity", XI_ConvertString("Colony" + pchar.questTemp.pirateStartQuest.City + "Gen"));
			AddQuestUserData("pSQ_Bacchus", "sName", GetFullName(npchar));
		break;
		case "pirateStartQuest_info_3_Bacchus_2":
			dialog.text = StringFromKey("RichardSoukins_37");
			link.l1 = StringFromKey("RichardSoukins_38");
			link.l1.go = "pirateStartQuest_info_3";

			pchar.questTemp.pSQ_Bacchus = "over";
		break;
		case "pirateStartQuest_info_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			pchar.questTemp.pirateStartQuest = "4";

			AddQuestRecord("pSQ", "7");
			AddQuestUserData("pSQ", "sName", GetFullName(CharacterFromID(pchar.questTemp.pirateStartQuest.BaronId)));
			RemoveLandQuestMark_Main(npchar, "pSQ");

			pchar.quest.zpq_seaBattle.win_condition.l1 = "location";
			pchar.quest.zpq_seaBattle.win_condition.l1.location = pchar.questTemp.pirateStartQuest.Areal;
			pchar.quest.zpq_seaBattle.function = "pirateStartQuest_seaBattle";
		break;

		case "pirateStartQuest_final":
			dialog.text = StringFromKey("RichardSoukins_39", pchar);
			link.l1 = StringFromKey("RichardSoukins_40", pchar);
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, 15000);
			pchar.questTemp.pirateStartQuest = "0";
			AddQuestRecord("pSQ", "10");
			CloseQuestHeader("pSQ");
			RemoveLandQuestMark_Main(npchar, "pSQ");
			group_DeleteGroup("pirateStartQuest_Smuggler_group");
			Achievment_Set(ACH_Pervye_shagi_k_viselitse);
		break;

		case "pirateStartQuest_BacchusSlaves":
			dialog.text = StringFromKey("RichardSoukins_41");
			link.l1 = StringFromKey("RichardSoukins_42");
			link.l1.go = "exit";

			AddMoneyToCharacter(pchar, 200 * 250);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, 200);

			pchar.questTemp.pSQ_Bacchus = "over";
			pchar.quest.pirateStartQuest_Bahus_Expired.over = "yes";
			AddQuestRecord("pSQ_Bacchus", "3");
			CloseQuestHeader("pSQ_Bacchus");
			RemoveLandQuestMark_Main(npchar, "pSQ_Bacchus");
		break;

		case "pirateStartQuest_BacchusSlaves_NoTalk":
			dialog.text = StringFromKey("RichardSoukins_43");
			link.l1 = StringFromKey("RichardSoukins_44");
			link.l1.go = "pirateStartQuest_BacchusSlaves_NoTalk_0";
		break;

		case "pirateStartQuest_BacchusSlaves_NoTalk_0":
			dialog.text = StringFromKey("RichardSoukins_45");
			link.l1 = StringFromKey("RichardSoukins_46");
			link.l1.go = "pirateStartQuest_BacchusSlaves_NoTalk_1";
		break;

		case "pirateStartQuest_BacchusSlaves_NoTalk_1":
			dialog.text = StringFromKey("RichardSoukins_47");
			link.l1 = StringFromKey("RichardSoukins_48");
			link.l1.go = "exit";

			AddMoneyToCharacter(pchar, 200 * 250);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, 200);

			pchar.questTemp.pSQ_Bacchus = "over";
			pchar.quest.pirateStartQuest_Bahus_Expired.over = "yes";
			AddQuestRecord("pSQ_Bacchus", "3");
			CloseQuestHeader("pSQ_Bacchus");
			RemoveLandQuestMark_Main(npchar, "pSQ_Bacchus");
		break;

		//пиратка, квест №7
		case "PL_Q7_1":
			dialog.text = StringFromKey("RichardSoukins_49");
			link.l1 = GetFullName(pchar) + ".";
			link.l1.go = "PL_Q7_2";
		break;
		case "PL_Q7_2":
			dialog.text = StringFromKey("RichardSoukins_50", pchar);
			link.l1 = StringFromKey("RichardSoukins_51", pchar);
			link.l1.go = "PL_Q7_3";
		break;
		case "PL_Q7_3":
			dialog.text = StringFromKey("RichardSoukins_52");
			link.l1 = StringFromKey("RichardSoukins_53");
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			pchar.questTemp.piratesLine = "Soukins_FightinResidence";
			RemoveLandQuestmark_Main(CharacterFromID("PuertoPrincipe_tavernkeeper"), "Pir_Line");
			RemoveLandQuestmark_Main(CharacterFromID("PuertoPrincipe_waitress"), "Pir_Line");
			for (i = 1; i <= 5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("questPirate_" + i, "citiz_" + (rand(9) + 51), "man", "man", 25, PIRATE, iTemp, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 25, 70, 70, "blade26", "pistol6", 20);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;
		case "PL_Q7_5":
			dialog.text = StringFromKey("RichardSoukins_54", pchar);
			link.l1 = StringFromKey("RichardSoukins_55");
			link.l1.go = "fight";
			LAi_SetPlayerType(pchar);
			pchar.questTemp.piratesLine = "Soukins_FightinResidence";
			RemoveLandQuestmark_Main(CharacterFromID("PuertoPrincipe_tavernkeeper"), "Pir_Line");
			RemoveLandQuestmark_Main(CharacterFromID("PuertoPrincipe_waitress"), "Pir_Line");
			for (i = 1; i <= 5; i++)
			{
				iTemp = 10 + rand(10);
				sld = GetCharacter(NPC_GenerateCharacter("questPirate_" + i, "citiz_" + (rand(9) + 51), "man", "man", 25, PIRATE, iTemp, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 25, 70, 70, "blade26", "pistol6", 20);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, npchar.chr_ai.group);
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
		break;
		//пиратка, квест №8
		case "PL_Q8_deck":
			dialog.text = StringFromKey("RichardSoukins_56", pchar);
			link.l1 = StringFromKey("RichardSoukins_57");
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = StringFromKey("RichardSoukins_58");
			link.l1 = StringFromKey("RichardSoukins_59");
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;

		case "PL_Q8_deck_2":
			dialog.text = StringFromKey("RichardSoukins_60", pchar);
			link.l1 = StringFromKey("RichardSoukins_61", pchar);
			link.l1.go = "PL_Q8_deck_3";
		break;
		case "PL_Q8_deck_3":
			dialog.text = StringFromKey("RichardSoukins_62", pchar);
			link.l1 = StringFromKey("RichardSoukins_63");
			link.l1.go = "PL_Q8_deck_4";
		break;
		case "PL_Q8_deck_4":
			dialog.text = StringFromKey("RichardSoukins_64");
			link.l1 = StringFromKey("RichardSoukins_65", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_5";
			npchar.DeckDialogNode = "PL_Q8_deck_5";
		break;
		case "PL_Q8_deck_5":
			dialog.text = StringFromKey("RichardSoukins_66");
			link.l1 = StringFromKey("RichardSoukins_67");
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_5";
			npchar.DeckDialogNode = "PL_Q8_deck_5";
		break;
		//в бухте Дарьенский залив
		case "Shore48":
			dialog.text = StringFromKey("RichardSoukins_68");
			link.l1 = StringFromKey("RichardSoukins_69", pchar);
			link.l1.go = "Shore48_1";
		break;
		case "Shore48_1":
			LAi_LocationFightDisable(&Locations[FindLocation("Shore48")], false);
			chrDisableReloadToLocation = false;
			LAi_SetWarriorTypeNoGroup(npchar);
			NextDiag.TempNode = "Shore48_over";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Shore48_over":
			dialog.text = StringFromKey("RichardSoukins_70");
			link.l1 = StringFromKey("RichardSoukins_71");
			link.l1.go = "exit";
		break;
		//после штурма у стен Панамы
		case "PQ8_exitTown":
			dialog.text = StringFromKey("RichardSoukins_72");
			link.l1 = StringFromKey("RichardSoukins_73");
			link.l1.go = "PQ8_exitTown_1";
		break;
		case "PQ8_exitTown_1":
			dialog.text = StringFromKey("RichardSoukins_74");
			link.l1 = StringFromKey("RichardSoukins_75");
			link.l1.go = "PQ8_exitTown_2";
		break;
		case "PQ8_exitTown_2":
			dialog.text = StringFromKey("RichardSoukins_76", pchar);
			link.l1 = StringFromKey("RichardSoukins_77");
			link.l1.go = "PQ8_exitTown_3";
		break;
		case "PQ8_exitTown_3":
			dialog.text = StringFromKey("RichardSoukins_78", pchar);
			link.l1 = StringFromKey("RichardSoukins_79");
			link.l1.go = "exit";
			LAi_warrior_DialogEnable(npchar, false);
		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = StringFromKey("RichardSoukins_80");
			link.l1 = StringFromKey("RichardSoukins_81");
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
			SeaPearl_PiratesBaron_DelQuestMarks();
			SeaPearl_Hostess_AddQuestMarks();
		break;
		case "SharpPearl_2":
			AddQuestRecord("SharpPearl", "16");
			AddQuestUserData("SharpPearl", "sName", GetFullName(NPChar));

			dialog.text = StringFromKey("RichardSoukins_82");
			link.l1 = StringFromKey("RichardSoukins_83");
			link.l1.go = "exit";
		break;
	}
}

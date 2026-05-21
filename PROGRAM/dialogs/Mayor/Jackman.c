// Джекмен на Бермудах
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// ============================================================================
	// ============================= блок angry ==========>>>>>>>>>>>>>>>>>>>>>>>>>
	if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
	{
		npchar.angry.ok = 1;
		if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
		{
			NextDiag.TempNode = NextDiag.CurrentNode;
			Dialog.CurrentNode = "AngryExitAgain";
			npchar.angry.first = 1;
		}
		else
		{
			switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
			{
				case "repeat":
					if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
					if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
					if (npchar.angry.name == "BlueBird_1") Dialog.CurrentNode = "AngryRepeat_1";
				break;
			}
		}
	}
	// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
	// ============================================================================

	switch (Dialog.CurrentNode)
	{
		case "Exit":
		//Если поговорили по делу - сбросим агр (агр по птице оставим)
			if (CheckAttribute(npchar, "quest.repeat.Firsttime")) DeleteAttribute(npchar, "quest.repeat.Firsttime");
			if (CheckAttribute(npchar, "quest.repeat.I_know_you_good")) DeleteAttribute(npchar, "quest.repeat.I_know_you_good");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		case "ExitAgr":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			NextDiag.TempNode = "First time";

			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Jackman_1", pchar),
						StringFromKey("Jackman_2"),
						StringFromKey("Jackman_3"),
						StringFromKey("Jackman_4"), "repeat", 2, npchar, "Firsttime");
			//fix если агр дошёл до 4 степени, то фраза забагуется
			if (sti(NPChar.quest.repeat.Firsttime) < 4) JackmanBeginPhrases(link, NPChar);

			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Jackman_5"),
						StringFromKey("Jackman_6"),
						StringFromKey("Jackman_7"),
						StringFromKey("Jackman_8"), npchar, "Firsttime");
			link.l1.go = "ExitAgr";
		break;

		case "I_know_you_good":
			NextDiag.TempNode = "I_know_you_good";

			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Jackman_11", GetFullName(pchar), RandPhraseSimple(
								StringFromKey("Jackman_9"),
								StringFromKey("Jackman_10", pchar))),
						StringFromKey("Jackman_12"),
						StringFromKey("Jackman_13"),
						StringFromKey("Jackman_14", pchar), "repeat", 1, npchar, "I_know_you_good");

			if (sti(NPChar.quest.repeat.I_know_you_good) < 4) JackmanBeginPhrases(link, NPChar);

			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Jackman_15", pchar),
						StringFromKey("Jackman_16", pchar),
						StringFromKey("Jackman_17"),
						StringFromKey("Jackman_18", pchar), npchar, "I_know_you_good");
			link.l1.go = "ExitAgr";
		/*HardCoffee не знаю почему, но в "First time" эти чеки изменены, а тут - нет
		if (pchar.questTemp.piratesLine.T1 == "KillLoy_GoodWork" && !CheckAttribute(npchar, "quest.PQ3"))
		{
			link.piratesLine = "" + GetSexPhrase("Готов", "Готова") +" сообщить, что Эдвард Лоу умер с ужасом в глазах и твоим именем в ушах.";
			link.piratesLine.go = "PL_SEAWOLF";
		}*/
		break;

		//********************* пиратка, направление на квест №1 *********************
		case "PL_Q1_1":
			if (CheckAttribute(NPChar, "notQuestLine"))
			{
				dialog.text = StringFromKey("Jackman_19");
				link.l1 = StringFromKey("Jackman_20", pchar);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Jackman_21", pchar);
				link.l1 = StringFromKey("Jackman_22");
				link.l1.go = "PL_Q1_2";
				LockQuestLine(characterFromId("eng_guber")); // лочим английскую линейку
				RemoveLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
				RemoveMapQuestMark("PortRoyal_town", "Eng_Line");
			}
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			RemoveMapQuestMark("Pirates_town", "Pir_Line");
		break;
		case "PL_Q1_2":
			dialog.text = StringFromKey("Jackman_23", pchar);
			link.l1 = StringFromKey("Jackman_24");
			link.l1.go = "exit";
			pchar.questTemp.piratesLine = "toFirstQuest";
			AddQuestRecord("Pir_Line_0_Waiting", "2");
		break;
		//********************* пиратка, квест №3, поиски Лоу *********************
		case "PL_Q3_1":
			dialog.text = StringFromKey("Jackman_25", pchar);
			link.l1 = StringFromKey("Jackman_26", pchar);
			link.l1.go = "PL_Q3_fight";
		break;
		case "PL_Q3_fight":
			LAi_LocationFightDisable(&Locations[FindLocation("Pirates_townhall")], false);
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			for (i = 3; i <= 5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("QuestPir_" + i, "pirate_" + i, "man", "man", 100, PIRATE, 0, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 100, 100, 100, "topor2", "pistol3", 100);
				LAi_SetWarriorType(sld);
				LAi_SetImmortal(sld, true);
				sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
				LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
			LAi_group_SetLookRadius("PIRATE_CITIZENS", 100);
			LAi_group_SetRelation("PIRATE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("PIRATE_CITIZENS", LAI_GROUP_PLAYER, false);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;

		case "PL_Q3_2":
			dialog.text = StringFromKey("Jackman_27");
			link.l1 = StringFromKey("Jackman_28");
			link.l1.go = "PL_Q3_3";
		break;
		case "PL_Q3_3":
			dialog.text = StringFromKey("Jackman_29");
			link.l1 = StringFromKey("Jackman_30");
			link.l1.go = "PL_Q3_4";
		break;
		case "PL_Q3_4":
			dialog.text = StringFromKey("Jackman_31");
			link.l1 = StringFromKey("Jackman_32");
			link.l1.go = "PL_Q3_5";
		break;
		case "PL_Q3_5":
			dialog.text = StringFromKey("Jackman_33", pchar);
			link.l1 = StringFromKey("Jackman_34");
			link.l1.go = "PL_Q3_6";
		break;
		case "PL_Q3_6":
			dialog.text = StringFromKey("Jackman_35");
			link.l1 = StringFromKey("Jackman_36");
			link.l1.go = "PL_Q3_7";
		break;
		case "PL_Q3_7":
			dialog.text = StringFromKey("Jackman_37", pchar);
			link.l1 = StringFromKey("Jackman_38", pchar);
			link.l1.go = "PL_Q3_8";
		break;
		case "PL_Q3_8":
			dialog.text = StringFromKey("Jackman_39", pchar);
			link.l1 = StringFromKey("Jackman_40");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Pir_Line_3_KillLoy", "12");
			pchar.questTemp.piratesLine = "KillLoy_2toTavernAgain";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
		//после поисков Лоу
		case "PL_SEAWOLF":
			NextDiag.TempNode = "I_know_you_good";
			npchar.quest.PQ3 = true;
			int chComp;
			bool bOk = false;
			for (i = 0; i <= COMPANION_MAX; i++)
			{
				chComp = GetCompanionIndex(pchar, i);
				if (chComp != -1 && RealShips[sti(characters[chComp].ship.type)].Name == "BrigSW1")
				{
					bOk = true;
					break;
				}
			}
			if (bOk)
			{
				dialog.text = StringFromKey("Jackman_41", pchar);
				link.l1 = StringFromKey("Jackman_42");
				link.l1.go = "exit";
				AddQuestRecord("Pir_Line_3_KillLoy", "19");
			}
			else
			{
				dialog.text = StringFromKey("Jackman_43", pchar);
				link.l1 = StringFromKey("Jackman_44");
				link.l1.go = "exit";
				AddMoneyToCharacter(pchar, 20000);
				AddQuestRecord("Pir_Line_3_KillLoy", "20");
				AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("", "а"));
			}
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
		//********************* пиратка, квест №6. двойник *********************
		/*case "PL_Q6": //HardCoffee ref Morgan's dialogue
			dialog.text = "О-о-о, кого я вижу?! Глазам не верю!";
			link.l1 = "Морган послал к тебе сказать, что капитан Гудли мёртв.";
			link.l1.go = "PL_Q6_1";
		break;*/
		case "PL_Q6_1":
			dialog.text = StringFromKey("Jackman_45");
			link.l1 = StringFromKey("Jackman_46", pchar);
			link.l1.go = "PL_Q6_2";
		break;
		case "PL_Q6_2":
			dialog.text = StringFromKey("Jackman_47");
			link.l1 = StringFromKey("Jackman_48");
			link.l1.go = "PL_Q6_3";
		break;
		case "PL_Q6_3":
			dialog.text = StringFromKey("Jackman_49", pchar);
			link.l1 = StringFromKey("Jackman_50");
			link.l1.go = "PL_Q6_4";
		break;
		case "PL_Q6_4":
			dialog.text = StringFromKey("Jackman_51");
			link.l1 = StringFromKey("Jackman_52");
			link.l1.go = "PL_Q6_5";
		break;
		case "PL_Q6_5":
			dialog.text = StringFromKey("Jackman_53");
			link.l1 = StringFromKey("Jackman_54");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "2");
			AddQuestUserData("Pir_Line_6_Jackman", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.piratesLine = "PL6Brother_toSantaCatalina";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			//ставим Джона Лидса в залив Косумель
			sld = GetCharacter(NPC_GenerateCharacter("JohnLids", "officer_4", "man", "man", 30, sti(pchar.nation), -1, true)); //watch_quest_moment
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("JohnLids_ship"), CANNON_TYPE_CULVERINE_LBS24, 80, 60, 60);
			sld.name = FindPersonalName("JohnLids_name");
			sld.lastname = FindPersonalName("JohnLids_lastname");
			sld.dialog.filename = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode = "First time";
			sld.DeckDialogNode = "JohnLids";
			sld.Abordage.Enable = false;
			sld.AnalizeShips = true;
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable = true;
			sld.Ship.Mode = "Pirate";
			sld.greeting = "Gr_MiddPirate";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
			Group_AddCharacter("LidsGroup", "JohnLids");
			Group_SetGroupCommander("LidsGroup", "JohnLids");
			Group_SetAddress("LidsGroup", "Beliz", "quest_ships", "Quest_ship_11");
			Group_SetTaskNone("LidsGroup");
			AddLandQuestmark_Main(sld, "Pir_Line");
		break;

		case "PL_Q6_after":
			DeleteAttribute(pchar, "QuestTemp.PirLine_quests_task");
			dialog.text = StringFromKey("Jackman_55", pchar);
			link.l1 = StringFromKey("Jackman_56", pchar);
			link.l1.go = "PL_Q6_after_1";
		break;
		case "PL_Q6_after_1":
			dialog.text = StringFromKey("Jackman_57");
			link.l1 = StringFromKey("Jackman_58", pchar);
			link.l1.go = "PL_Q6_after_2";
		break;
		case "PL_Q6_after_2":
			dialog.text = StringFromKey("Jackman_59", pchar);
			link.l1 = StringFromKey("Jackman_60", pchar);
			link.l1.go = "PL_Q6_after_3";
		break;
		case "PL_Q6_after_3":
			dialog.text = StringFromKey("Jackman_61", pchar);
			link.l1 = StringFromKey("Jackman_62");
			link.l1.go = "exit";
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "5");
			sld = characterFromId("Henry Morgan");
			LAi_SetHuberTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "sit", "sit2");
			//HardCoffee реф диалогов Моргана
			pchar.QuestTemp.PirLine_quests_task = "Q7_GoToMorgan";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestMark_Main(sld, "Pir_Line");
		//QuestSetCurrentNode("Henry Morgan", "PL_Q7_begin");
		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = StringFromKey("Jackman_63");
			link.l1 = StringFromKey("Jackman_64");
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
			SeaPearl_PiratesBaron_DelQuestMarks();
			SeaPearl_Hostess_AddQuestMarks();
		break;
		case "SharpPearl_2":
			AddQuestRecord("SharpPearl", "16");
			AddQuestUserData("SharpPearl", "sName", GetFullName(NPChar));

			dialog.text = StringFromKey("Jackman_65");
			link.l1 = StringFromKey("Jackman_66");
			link.l1.go = "exit";
		break;

		//********************** поиски Синей птицы ***********************
		case "BlueBird_1":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Jackman_67"),
						StringFromKey("Jackman_68"),
						StringFromKey("Jackman_69"),
						StringFromKey("Jackman_70"), "repeat", 2, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Jackman_71"),
						StringFromKey("Jackman_72"),
						StringFromKey("Jackman_73", pchar),
						StringFromKey("Jackman_74"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("BlueBird_2", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
		break;
		case "BlueBird_2":
			dialog.text = StringFromKey("Jackman_75");
			link.l1 = StringFromKey("Jackman_76", pchar);
			link.l1.go = "BlueBird_3";
		break;
		case "BlueBird_3":
			dialog.text = StringFromKey("Jackman_77");
			link.l1 = StringFromKey("Jackman_78");
			link.l1.go = "BlueBird_4";
		break;
		case "BlueBird_4":
			dialog.text = StringFromKey("Jackman_79");
			link.l1 = StringFromKey("Jackman_80");
			link.l1.go = "BlueBird_5";
		break;
		case "BlueBird_5":
			dialog.text = StringFromKey("Jackman_81");
			link.l1 = StringFromKey("Jackman_82");
			link.l1.go = "exit";
			RemoveLandQuestMark_Main(npchar, "Xebeca_BlueBird");
		break;

		case "BlueBird_6":
			if (CheckAttribute(NPChar, "quest.repeat.BlueBird_6") && "3" == NPChar.quest.repeat.BlueBird_6)
				pchar.questTemp.BlueBird.StopAnnoyJackman = true;
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Jackman_83"),
						StringFromKey("Jackman_84"),
						StringFromKey("Jackman_85"),
						StringFromKey("Jackman_86", pchar), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Jackman_87"),
						StringFromKey("Jackman_88"),
						StringFromKey("Jackman_89"),
						StringFromKey("Jackman_90"), npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;
		//********************** Английская линейка ***********************
		/*//HardCoffee ref dialogue
		 case "EngLine_quests":
			dialog.text = "Рад видеть английского капера на моём острове. Что тебе нужно, говори.";
			link.l1 = "У меня есть для тебя работа. Заказчик - генерал-губернатор Ямайки.";
			link.l1.go = "Step_1";
		  break;*/

		case "Step_1":
			DeleteAttribute(pchar, "QuestTemp.EngLine_Jackman_task");
			dialog.text = StringFromKey("Jackman_91");
			link.l1 = StringFromKey("Jackman_92");
			link.l1.go = "Step_2";
		break;

		case "Step_2":
			dialog.text = StringFromKey("Jackman_93");
			link.l1 = StringFromKey("Jackman_94");
			link.l1.go = "Step_3";
		break;

		case "Step_3":
			dialog.text = StringFromKey("Jackman_95");
			link.l1 = StringFromKey("Jackman_96");
			link.l1.go = "Step_4";
		break;

		case "Step_4":
			dialog.text = StringFromKey("Jackman_97");
			link.l1 = StringFromKey("Jackman_98");
			link.l1.go = "Step_5";
		break;

		case "Step_5":
			dialog.text = StringFromKey("Jackman_99");
			link.l1 = StringFromKey("Jackman_100");
			link.l1.go = "exit";

			AddQuestRecord("Eng_Line_2_Talking", "4");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
			if (pchar.questTemp.Count == "4")
			{
				pchar.questTemp.State = "after_talks_with_pirates";
				AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
			}
		//NextDiag.TempNode = "First time";
		break;
		/* //HardCoffee ref dialogue
 		case "Lets_go_bussines":
			dialog.text = "Рад тебя видеть, " + pchar.name + ". Какими судьбами на Бермудах?";
			link.l1 = "Я по делу. Мы с Морганом атакуем Белиз, ты примешь участие в деле?";
			link.l1.go = "Step_6";
  		break;*/

		case "Step_6":
			DeleteAttribute(pchar, "QuestTemp.EngLine_Jackman_task");
			if (GetCompanionQuantity(pchar) != 4)
			{
				dialog.text = StringFromKey("Jackman_101");
				link.l1 = StringFromKey("Jackman_102");
				link.l1.go = "Step_7";
			}
			else
			{
				dialog.text = StringFromKey("Jackman_103");
				link.l1 = StringFromKey("Jackman_104");
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;

		case "Step_7":
			AddQuestRecord("Eng_Line_3_Morgan", "4");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			LAi_SetActorType(npchar);
			LAi_ActorSetStayMode(npchar);
			ChangeCharacterAddressGroup(npchar, "Pirates_townhall", "goto", "governor1");
			CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 10, false);
			Fantom_SetBalls(npchar, "pirate");
			npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
			pchar.questTemp.CompanionQuantity = makeint(sti(pchar.questTemp.CompanionQuantity) + 1);
			pchar.questTemp.CompanionQuantity.Jackman = true;
			NextDiag.TempNode = "Have_hot_bussines";
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;

		break;

		case "Have_hot_bussines":   // Если геймеру вдруг захочется ещё пообщаться, не знаю, сможет ли. Но на всякий случай.
			dialog.text = StringFromKey("Jackman_105");
			link.l1 = StringFromKey("Jackman_106");
			link.l1.go = "exit";
			NextDiag.TempNode = "Have_hot_bussines";
		break;

		case "Gold_found_in_fort":    // Нода разговора в форте Куманы
			if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman") && !IsCompanion(characterFromID("Jackman")))
			{
				dialog.text = StringFromKey("Jackman_107", pchar);
			}
			else
			{
				dialog.text = StringFromKey("Jackman_108", pchar);
			}
			link.l1 = StringFromKey("Jackman_109", pchar);
			link.l1.go = "Step_8";
		break;

		case "Step_8":
			dialog.text = StringFromKey("Jackman_110", pchar, pchar.name, pchar.lastname);
			link.l1 = StringFromKey("Jackman_111");
			link.l1.go = "Step_9";
		break;

		case "Step_9":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 15.0);
			DialogExit();
			NextDiag.TempNode = "I_know_you_good"; //HardCoffee ref dialogue
			NextDiag.CurrentNode = NextDiag.TempNode;
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;
		//********************** Голландская линейка ***********************
		/*case "HolLine8_quest": //HardCoffee ref dialogue
		   dialog.text = "Слушаю тебя, зачем " + GetSexPhrase("пожаловал", "пожаловала") +" ко мне?";
		   link.l1 = "Я " + GetSexPhrase("прибыл", "прибыла") +" сюда по делу, ищу одного пирата, который пытался продать необычную Библию.";
		   link.l1.go = "Step_H8_1";
		 break;*/
		case "Step_H8_1":
			DeleteAttribute(pchar, "QuestTemp.HolLine_quests_task");
			dialog.text = StringFromKey("Jackman_112");
			link.l1 = StringFromKey("Jackman_113");
			link.l1.go = "Step_H8_2";
		break;
		case "Step_H8_2":
			dialog.text = StringFromKey("Jackman_114");
			link.l1 = StringFromKey("Jackman_115");
			link.l1.go = "Step_H8_3";
		break;
		case "Step_H8_3":
			dialog.text = StringFromKey("Jackman_116");
			link.l1 = StringFromKey("Jackman_117");
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_8_SeekBible", "3");
			pchar.questTemp.State = "SeekBible_toFFBrothel";
			NextDiag.TempNode = NextDiag.CurrentNode;
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Pirates_tavernkeeper"), "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("FortFrance_hostess"), "Hol_Line");
			AddLandQuestmarkToFantoms_Main("Horse", "Hol_Line", "HolLine_8_SeekBible_Horse_QuestMarkCondition");
		break;
		//********************* Французская линейка *********************
		/*case "FraLine8_talk": //HardCiffee ref dialogue
			dialog.text = "Надо же, капитан " + GetFullName(pchar) + " " + GetSexPhrase("пожаловал", "пожаловала") +"! Весьма рад! Выкладывай – я же вижу, что тебе не терпится сообщить что-то интересное.";
			link.l1 = "В общем, ничего особенно интересного я не предложу. Всего только отказаться от участия в грядущей войне между Англией и Голландией.";
			link.l1.go = "Step_F8_1";
		break;*/
		case "Step_F8_1":
			DeleteAttribute(pchar, "QuestTemp.FraLine_Jackman_task");
			dialog.text = StringFromKey("Jackman_118");
			link.l1 = StringFromKey("Jackman_119", pchar);
			link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count) + 1;
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "5");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		//********************* Пиратская линейка *********************
		case "PL_Q8_deck":
			dialog.text = StringFromKey("Jackman_120");
			link.l1 = StringFromKey("Jackman_121");
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;
		case "PL_Q8_deck_1":
			dialog.text = StringFromKey("Jackman_122");
			link.l1 = StringFromKey("Jackman_123");
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_deck_1";
		break;

		case "PL_Q8":
			dialog.text = StringFromKey("Jackman_124");
			link.l1 = StringFromKey("Jackman_125");
			link.l1.go = "PL_Q8_1";
		break;
		case "PL_Q8_1":
			dialog.text = StringFromKey("Jackman_126");
			link.l1 = StringFromKey("Jackman_127");
			link.l1.go = "PL_Q8_2";
		break;
		case "PL_Q8_2":
			dialog.text = StringFromKey("Jackman_128");
			link.l1 = StringFromKey("Jackman_129");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Panama_inEngland";
		break;
		//поиски супер-мушкета
		case "Mushket":
			dialog.text = StringFromKey("Jackman_130");
			link.l1 = StringFromKey("Jackman_131");
			link.l1.go = "Mushket_1";
			DeleteAttribute(pchar, "questTemp.mushket2x2");
		break;
		case "Mushket_1":
			dialog.text = StringFromKey("Jackman_132");
			link.l1 = StringFromKey("Jackman_133");
			link.l1.go = "Mushket_2";
		break;
		case "Mushket_2":
			dialog.text = StringFromKey("Jackman_134");
			link.l1 = StringFromKey("Jackman_135");
			link.l1.go = "exit";
			SetMushketCapitainInWorld(true);
			AddQuestRecord("SeekDoubleMushket", "2");

			RemoveLandQuestMark_Main(CharacterFromID("LeFransua_Mayor"), "SeekDoubleMushket");
			RemoveLandQuestMark_Main(npchar, "SeekDoubleMushket");
		break;

		//*************************** Квест "Сопровождение флейта "Орион"" **********************

		case "Andre_Abel_Quest_Jackman_Dialog_3":
			pchar.QuestTemp.AndreAbelQuest = true;
			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
			dialog.text = StringFromKey("Jackman_136", pchar);
			link.l1 = StringFromKey("Jackman_137", pchar);
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_4";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_4":
			dialog.text = StringFromKey("Jackman_138");
			link.l1 = StringFromKey("Jackman_139", pchar);
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_5";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_5":
			dialog.text = StringFromKey("Jackman_140", pchar);
			link.l1 = StringFromKey("Jackman_141", pchar);
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_6";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_6":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DoFunctionReloadToLocation("Pirates_town", "reload", "reload3", "Andre_Abel_Quest_After_First_Jackman_Dialog");
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_7":
			pchar.QuestTemp.AndreAbelQuest = true;
			dialog.text = StringFromKey("Jackman_142", pchar);
			link.l1 = StringFromKey("Jackman_143", pchar);
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_8";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_8":
			dialog.text = StringFromKey("Jackman_144");
			link.l1 = StringFromKey("Jackman_145");
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_9";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_9":
			dialog.text = StringFromKey("Jackman_146");
			link.l1 = StringFromKey("Jackman_147");
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_10";
			TakeItemFromCharacter(PChar, "Andre_Abel_Letter_2");
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_10":
			dialog.text = StringFromKey("Jackman_148", pchar);
			link.l1 = StringFromKey("Jackman_149", pchar);
			link.l1.go = "Andre_Abel_Quest_Jackman_Dialog_11";
		break;

		case "Andre_Abel_Quest_Jackman_Dialog_11":
			DialogExit();
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("Andre_Abel_Quest", "22");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("", "а"));
			PChar.QuestTemp.Andre_Abel_Quest_Complete = true;

			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
			AddLandQuestMark_Main(CharacterFromID("Andre_Abel"), "Andre_Abel_Quest");
		break;

		//*************************** Генератор "Поручение капитана - Выкуп" **********************
		case "CapComission1":
			if (CheckAttribute(npchar, "quest.repeat")) DeleteAttribute(npchar, "quest.repeat");
			dialog.text = StringFromKey("Jackman_150");
			link.l1 = StringFromKey("Jackman_151", pchar.GenQuest.CaptainComission.SlaveName);
			link.l1.go = "CapComission2";
			DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
			pchar.GenQuest.CaptainComission.toPlantator = GetRandomPlantation();
		break;

		case "CapComission2":
			if (HasSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_Mine"))
				sTemp = StringFromKey("Jackman_152", XI_ConvertString("Colony" + GetSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_", 0) + "Gen"));
			else
				sTemp = StringFromKey("Jackman_153", XI_ConvertString("Colony" + GetSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_", 0) + "Gen"));
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.DaysLeft"))
			{
				dialog.text = StringFromKey("Jackman_154", sTemp);
				link.l1 = StringFromKey("Jackman_155");
				link.l1.go = "CapComission2_1";
			}
			else
			{
				dialog.text = StringFromKey("Jackman_156", pchar, sTemp);
				link.l1 = StringFromKey("Jackman_157", pchar);
				link.l1.go = "CapComission2_2";
				if (makeint(pchar.money) > 150000)
				{
					link.l2 = StringFromKey("Jackman_158");
					link.l2.go = "CapComission2_3";
				}
			}
		break;

		case "CapComission2_1":
			dialog.text = StringFromKey("Jackman_159", pchar);
			link.l1 = StringFromKey("Jackman_160", pchar);
			link.l1.go = "CapComission2_11";
		break;

		case "CapComission2_11":
			dialog.text = StringFromKey("Jackman_161", pchar);
			link.l1 = StringFromKey("Jackman_162");
			link.l1.go = "CapComission2_12";
		break;

		case "CapComission2_12":
			dialog.text = StringFromKey("Jackman_163");
			link.l1 = StringFromKey("Jackman_164");
			link.l1.go = "exit";
			if (HasSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_Mine"))
				sTemp = StringFromKey("Jackman_165", XI_ConvertString("Colony" + GetSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_", 0) + "Gen"));
			else
				sTemp = StringFromKey("Jackman_166", XI_ConvertString("Colony" + GetSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_", 0) + "Gen"));
			AddQuestRecord("CaptainComission1", "10");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sColony", sTemp);
			AddQuestUserData("CaptainComission1", "sIsland", XI_ConvertString(GetIslandNameByCity(GetSubStr(pchar.GenQuest.CaptainComission.toPlantator, "_", 0)) + "Acc"));
		break;

		case "CapComission2_2":
			if (rand(1) == 0)
			{
				dialog.text = StringFromKey("Jackman_167");
				link.l1 = StringFromKey("Jackman_168");
				link.l1.go = "CapComission2_2_1";
			}
			else
			{
				dialog.text = StringFromKey("Jackman_169", pchar.name);
				link.l1 = StringFromKey("Jackman_170");
				link.l1.go = "CapComission2_4";
			}
		break;

		case "CapComission2_2_1":
			dialog.text = StringFromKey("Jackman_171");
			link.l1 = StringFromKey("Jackman_172");
			link.l1.go = "CapComission2_2_2";
		break;

		case "CapComission2_2_2":
			CaptainComission_GetRandomShore();
			pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
			pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
			sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat");
			dialog.text = StringFromKey("Jackman_173", GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM), XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen"), pchar.GenQuest.CaptainComission.ShipName1, pchar.GenQuest.CaptainComission.ShipName2, sLoc);
			link.l1 = StringFromKey("Jackman_174");
			link.l1.go = "CapComission2_2_3";
		break;

		case "CapComission2_2_3":
			dialog.text = StringFromKey("Jackman_175");
			link.l1 = StringFromKey("Jackman_176");
			link.l1.go = "CapComission2_2_4";
		break;

		case "CapComission2_2_4":
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
			DialogExit();
		break;

		case "CapComission2_3":
			dialog.text = StringFromKey("Jackman_177");
			link.l1 = StringFromKey("Jackman_178");
			link.l1.go = "CapComission2_31";
		break;

		case "CapComission2_31":
			dialog.text = StringFromKey("Jackman_179");
			link.l1 = StringFromKey("Jackman_180");
			link.l1.go = "CapComission2_32";
		break;

		case "CapComission2_32":
			AddQuestRecord("CaptainComission1", "9");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			addMoneyToCharacter(pchar, -150000);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission2_4":
			if (!CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
			{
				AddQuestRecord("CaptainComission1", "31");
				AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			}
			pchar.GenQuest.CaptainComission.RepeatSpeak = true;
			DialogExit();
		break;

		case "CapComission3":
			dialog.text = StringFromKey("Jackman_181", pchar, GetFullName(pchar));
			if (pchar.GenQuest.CaptainComission.PirateShips == "goaway")
			{
				link.l1 = StringFromKey("Jackman_182", pchar);
				link.l1.go = "CapComission4";
			}
			if (pchar.GenQuest.CaptainComission.PirateShips == "died")
			{
				link.l1 = StringFromKey("Jackman_183", pchar);
				link.l1.go = "CapComission5";
			}
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		break;

		case "CapComission4":
			dialog.text = StringFromKey("Jackman_184");
			link.l1 = StringFromKey("Jackman_185");
			link.l1.go = "CapComission4_1";
			link.l2 = StringFromKey("Jackman_186");
			link.l2.go = "CapComission4_2";
		break;

		case "CapComission4_1":
			dialog.text = StringFromKey("Jackman_187");
			link.l1 = StringFromKey("Jackman_188");
			link.l1.go = "CapComission4_3";
		break;

		case "CapComission4_2":
			dialog.text = StringFromKey("Jackman_189");
			link.l1 = StringFromKey("Jackman_190");
			link.l1.go = "CapComission4_4";
			if (sti(pchar.money) >= 200000)
			{
				link.l2 = StringFromKey("Jackman_191");
				link.l2.go = "CapComission4_5";
			}
		break;

		case "CapComission4_3":
			ChangeCharacterReputation(pchar, -2);
			AddQuestRecord("CaptainComission1", "27");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", "ла"));
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			DialogExit();
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
			dialog.text = StringFromKey("Jackman_192");
			link.l1 = StringFromKey("Jackman_193");
			link.l1.go = "CapComission4_6";
		break;

		case "CapComission4_6":
			addMoneyToCharacter(pchar, -200000);
			AddQuestRecord("CaptainComission1", "29");
			AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission5":
			dialog.text = StringFromKey("Jackman_194", pchar);
			link.l1 = StringFromKey("Jackman_195");
			link.l1.go = "CapComission5_1";
		break;

		case "CapComission5_1":
			AddQuestRecord("CaptainComission1", "34");
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		case "CapComission6":
			dialog.text = StringFromKey("Jackman_196", pchar);
			link.l1 = StringFromKey("Jackman_197", pchar, NPChar.name);
			link.l1.go = "CapComission2_2";
			if (makeint(pchar.money) > 150000)
			{
				link.l2 = StringFromKey("Jackman_198");
				link.l2.go = "CapComission2_3";
			}
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = StringFromKey("Jackman_202", LinkRandPhrase(
						StringFromKey("Jackman_199", pchar),
						StringFromKey("Jackman_200", pchar),
						StringFromKey("Jackman_201", pchar)));
			link.l1 = StringFromKey("Jackman_206", LinkRandPhrase(
						StringFromKey("Jackman_203"),
						StringFromKey("Jackman_204"),
						StringFromKey("Jackman_205")));
			link.l1.go = "PL_Q3_fight";
		break;

		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
			dialog.text = StringFromKey("Jackman_209", RandPhraseSimple(
						StringFromKey("Jackman_207", pchar),
						StringFromKey("Jackman_208")));
			link.l1 = StringFromKey("Jackman_210");
			link.l1.go = "AngryExitAgainWithOut";
			if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
			{
				if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
				{
					dialog.text = StringFromKey("Jackman_211");
					link.l1 = StringFromKey("Jackman_212", pchar);
					link.l1.go = NextDiag.TempNode;
					CharacterDelAngry(npchar);
				}
			}
		break;
		case "AngryRepeat_2":
			dialog.text = StringFromKey("Jackman_215", RandPhraseSimple(
						StringFromKey("Jackman_213", pchar),
						StringFromKey("Jackman_214")));
			link.l1 = StringFromKey("Jackman_218", RandPhraseSimple(
						StringFromKey("Jackman_216"),
						StringFromKey("Jackman_217")));
			link.l1.go = "AngryExitAgain";
			if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Джекменом через 10 дней.
			{
				if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
				{
					dialog.text = StringFromKey("Jackman_219");
					link.l1 = StringFromKey("Jackman_220");
					link.l1.go = NextDiag.TempNode;
					CharacterDelAngry(npchar);
				}
			}
		break;
		case "AngryExitAgain":
			DialogExit();
			DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
			DialogExit();
			DeleteAttribute(npchar, "angry.ok");
			DoReloadCharacterToLocation("Pirates_town", "reload", "reload3");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
	}
}

void JackmanBeginPhrases(aref link, ref NPChar)
{
	//английская линейка -->
	if (CheckAttribute(pchar, "QuestTemp.EngLine_Jackman_task"))
	{
		if ("EngLine_begin" == pchar.QuestTemp.EngLine_Jackman_task)
		{
			link.l30 = StringFromKey("Jackman_225");
			link.l30.go = "Step_1";
		}
		else if ("Lets_go_bussines" == pchar.QuestTemp.EngLine_Jackman_task)
		{
			link.l30 = StringFromKey("Jackman_226");
			link.l30.go = "Step_6";
		}
	}
	//<-- английская линейка
	//Голландская линейка -->
	if (CheckAttribute(pchar, "QuestTemp.HolLine_quests_task") && pchar.QuestTemp.HolLine_quests_task == "HolLine8_quest")
	{
		link.l31 = StringFromKey("Jackman_227", pchar);
		link.l31.go = "Step_H8_1";
	}
	//<-- Голландская линейка
	//Французская линейка -->
	if (CheckAttribute(pchar, "QuestTemp.FraLine_Jackman_task") && pchar.QuestTemp.FraLine_Jackman_task == "FraLine8_talk")
	{
		link.l32 = StringFromKey("Jackman_228");
		link.l32.go = "Step_F8_1";
	}
	//<-- Французская линейка
	//поиски шебеки Синяя Птица
	if (CheckAttribute(pchar, "questTemp.BlueBird"))
	{
		if (pchar.questTemp.BlueBird == "toBermudes")
		{
			link.l33 = StringFromKey("Jackman_229");
			link.l33.go = "BlueBird_1";
		}
		else if (pchar.questTemp.BlueBird == "weWon" && !CheckAttribute(pchar, "questTemp.BlueBird.StopAnnoyJackman"))
		{
			link.l33 = StringFromKey("Jackman_230", pchar);
			link.l33.go = "BlueBird_6";
		}
	}

	//жемчужный генератор Шарпа
	if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "takeRumour"))
	{
		link.l34 = StringFromKey("Jackman_231");
		link.l34.go = "SharpPearl_1";
	}

	//поиски супер-мушкета
	if (CheckAttribute(pchar, "questTemp.mushket2x2") && !CheckCharacterItem(pchar, "mushket2x2"))
	{
		link.l35 = StringFromKey("Jackman_232");
		link.l35.go = "Mushket";
	}

	//Сопровождение флейта "Орион"
	if (CheckAttribute(pchar, "QuestTemp.AndreAbelQuest"))
	{
		if ("GoTo_Jackman1" == pchar.QuestTemp.AndreAbelQuest)
		{
			link.l36 = StringFromKey("Jackman_233");
			link.l36.go = "Andre_Abel_Quest_Jackman_Dialog_3";
		}
		else if ("GoTo_Jackman2" == pchar.QuestTemp.AndreAbelQuest)
		{
			link.l36 = StringFromKey("Jackman_234");
			link.l36.go = "Andre_Abel_Quest_Jackman_Dialog_7";
		}
	}

	//поручение капитана - выкуп
	if (CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
	{
		if (CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
		{
			link.l37 = StringFromKey("Jackman_235");
			link.l37.go = "CapComission1";
		}
		else if (CheckAttribute(pchar, "GenQuest.CaptainComission.PirateShips"))
		{
			link.l37 = StringFromKey("Jackman_236");
			link.l37.go = "CapComission3";
		}
		else if (CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
		{
			link.l37 = StringFromKey("Jackman_237");
			link.l37.go = "CapComission6";
		}
	}
	//пиратская линейка --->
	if (pchar.questTemp.piratesLine == "over") return;
	switch (pchar.questTemp.piratesLine)
	{
		case "begin":
			link.l38 = StringFromKey("Jackman_238");
			link.l38.go = "PL_Q1_1";
		break;
		case "KillLoy_toJackman":
			link.l38 = StringFromKey("Jackman_239");
			link.l38.go = "PL_Q3_1";
		break;
		case "KillLoy_toTavernAgain":
			link.l38 = StringFromKey("Jackman_240");
			link.l38.go = "PL_Q3_2";
		break;
		case "waiting_Q6":
			link.l38 = StringFromKey("Jackman_241");
			link.l38.go = "PL_Q6_1";
		break;
		case "Panama_backToShip":
			link.l38 = StringFromKey("Jackman_242");
			link.l38.go = "PL_Q8";
		break;
		if (CheckAttribute(pchar, "questTemp.piratesLine.T1") && pchar.questTemp.piratesLine.T1 == "KillLoy_GoodWork" && !CheckAttribute(npchar, "quest.PQ3"))
		{
			link.l38 = StringFromKey("Jackman_243", pchar);
			link.l38.go = "PL_SEAWOLF";
		}
		else if (pchar.QuestTemp.PirLine_quests_task == "PL_Q6_after")
		{
			link.l38 = StringFromKey("Jackman_244", pchar);
			link.l38.go = "PL_Q6_after";
		}
	}
	//пиратская линейка <---
}
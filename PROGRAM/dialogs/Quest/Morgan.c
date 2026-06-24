// Генри Морган
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	float locx, locy, locz;
	string sTemp;
	int iTemp;
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
				break;
			}
		}
	}
	// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
	// ============================================================================
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			if (CheckAttribute(npchar, "quest.repeat")) DeleteAttribute(npchar, "quest.repeat");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "ExitAgr":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			NextDiag.TempNode = "First time";

			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Morgan_1"),
						StringFromKey("Morgan_2"),
						StringFromKey("Morgan_3"),
						StringFromKey("Morgan_4"), "repeat", 2, npchar, "Firsttime");

			if (sti(NPChar.quest.repeat.Firsttime) < 4) MorganBeginPhrases(Link);

			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Morgan_5"),
						StringFromKey("Morgan_6"),
						StringFromKey("Morgan_7"),
						StringFromKey("Morgan_8"), npchar, "Firsttime");
			link.l1.go = "ExitAgr";
		break;

		case "I_know_you_good":
			NextDiag.TempNode = "I_know_you_good";

			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Morgan_9", pchar, GetFullName(pchar)),
						StringFromKey("Morgan_10"),
						StringFromKey("Morgan_11"),
						StringFromKey("Morgan_12", pchar), "repeat", 1, npchar, Dialog.CurrentNode);

			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Morgan_13", pchar),
						StringFromKey("Morgan_14"),
						StringFromKey("Morgan_15"),
						StringFromKey("Morgan_16", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = "ExitAgr";

			if (sti(NPChar.quest.repeat.I_know_you_good) < 4)
			{
				if (pchar.questTemp.piratesLine == "waiting_Q4" && GetQuestPastDayParam("questTemp.piratesLine") > 5 && pchar.questTemp.Sharp != "toPearl")
				{
					link.l2 = StringFromKey("Morgan_17");
					link.l2.go = "PL_Q4_1";
				}
				else if (pchar.questTemp.piratesLine == "waiting_Q8" && GetQuestPastDayParam("questTemp.piratesLine") > 30)
				{
					link.l2 = StringFromKey("Morgan_18", pchar);
					link.l2.go = "PL_Q8_1";
				}
				else if (pchar.questTemp.piratesLine == "Panama_toReady" && GetQuestPastDayParam("questTemp.piratesLine") > 20)
				{
					link.l2 = StringFromKey("Morgan_19");
					link.l2.go = "PL_Q8_ready_1";
				}
				MorganBeginPhrases(Link);
			}

		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = StringFromKey("Morgan_20");
			link.l1 = StringFromKey("Morgan_21");
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
			SeaPearl_PiratesBaron_DelQuestMarks();
			SeaPearl_Hostess_AddQuestMarks();
		break;
		case "SharpPearl_2":
			AddQuestRecord("SharpPearl", "16");
			AddQuestUserData("SharpPearl", "sName", GetFullName(NPChar));

			dialog.text = StringFromKey("Morgan_22");
			link.l1 = StringFromKey("Morgan_23");
			link.l1.go = "exit";
		break;
		//********************* Английская линейка *********************
		/*HardCoffee реф диалогов
		case "EngLine_quests":
		   dialog.text = "У вас ко мне дело?";
		   link.l1 = "Сэр, генерал-губернатор Ямайки, сэр Томас Мэдифорд нуждается в вашей помощи.";
		   link.l1.go = "Step_1_1";
		 break;*/

		case "Step_1_1":
			DeleteAttribute(pchar, "QuestTemp.EngLine_Morgan_task");
			dialog.text = StringFromKey("Morgan_24");
			link.l1 = StringFromKey("Morgan_25", pchar);
			link.l1.go = "Step_1_2";
		break;

		case "Step_1_2":
			dialog.text = StringFromKey("Morgan_26");
			link.l1 = StringFromKey("Morgan_27");
			link.l1.go = "Step_1_3";
		break;

		case "Step_1_3":
			dialog.text = StringFromKey("Morgan_28");
			link.l1 = StringFromKey("Morgan_29");
			link.l1.go = "Step_1_4";
		break;

		case "Step_1_4":
			dialog.text = StringFromKey("Morgan_30");
			link.l1 = StringFromKey("Morgan_31");
			link.l1.go = "exit";
			AddQuestRecord("Eng_Line_2_Talking", "2");
			AddQuestUserData("Eng_Line_2_Talking", "sSex", GetSexPhrase("", "а"));
			AddQuestRecord("Eng_Line_3_Morgan", "1");
			AddQuestUserData("Eng_Line_3_Morgan", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestmark_Main(npchar, "Eng_Line");

			pchar.questTemp.Count = makeint(sti(pchar.questTemp.Count) + 1);
			if (pchar.questTemp.Count == "4")
			{
				pchar.questTemp.State = "after_talks_with_pirates";
				AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
			}
			NextDiag.TempNode = "I_know_you_good";
		break;

		case "hot_business":            // начало диалога по третьему квесту англ.линейки
			DeleteAttribute(pchar, "QuestTemp.EngLine_Morgan_task");
			if (CheckAttribute(npchar, "quest.repeat")) DeleteAttribute(npchar, "quest.repeat");
			dialog.text = StringFromKey("Morgan_32", pchar);
			link.l1 = StringFromKey("Morgan_33");
			link.l1.go = "Step_3_1";
		break;

		case "Step_3_1":
			if (GetQuestPastDayParam("questTemp") < 27 && pchar.questTemp.CurQuestNumber == "3")
			{
				dialog.text = StringFromKey("Morgan_34", pchar);
				link.l1 = StringFromKey("Morgan_35");
				link.l1.go = "Step_3_2";
			}
			else
			{
				dialog.text = StringFromKey("Morgan_36", pchar);
				link.l1 = StringFromKey("Morgan_37");
				link.l1.go = "exit";
				AddQuestRecord("Eng_Line_3_Morgan", "8");
				AddQuestUserData("Eng_Line_3_Morgan", "sSex", GetSexPhrase("ёл", "ла"));
				AddQuestUserData("Eng_Line_3_Morgan", "sSex1", GetSexPhrase("", "а"));
				CloseQuestHeader("Eng_Line_3_Morgan");
				//NextDiag.TempNode = "First time";
				if (pchar.questTemp.CurQuestNumber == "3")
				{
					SaveCurrentQuestDateParam("questTemp");
					pchar.questTemp.Waiting_time = "2";
					pchar.questTemp.CurQuestNumber = "4";
				}
				RemoveLandQuestmark_Main(npchar, "Eng_Line");
			}
		break;

		case "Step_3_2":
			dialog.text = StringFromKey("Morgan_38", pchar);
			link.l1 = StringFromKey("Morgan_39");
			link.l1.go = "Step_3_3";
		break;

		case "Step_3_3":
			dialog.text = StringFromKey("Morgan_40");
			link.l1 = StringFromKey("Morgan_41");
			link.l1.go = "Step_3_4";
		break;

		case "Step_3_4":
			dialog.text = StringFromKey("Morgan_42", pchar);
			link.l1 = StringFromKey("Morgan_43");
			link.l1.go = "I_want_attack";
			link.l2 = StringFromKey("Morgan_44", pchar);
			link.l2.go = "Step_3_6";
		break;

		case "I_want_attack":    // Идем на испанцев, а может и не идем
			if (GetCompanionQuantity(pchar) == 1)   // Заставляем геймера избавиться от взятых кубиков.
			{
				dialog.text = StringFromKey("Morgan_45");
				link.l1 = StringFromKey("Morgan_46");
				link.l1.go = "Step_3_7";
			}
			else
			{
				NextDiag.TempNode = "Step_3_4";
				dialog.text = StringFromKey("Morgan_47");
				link.l1 = StringFromKey("Morgan_48");
				link.l1.go = "exit";
				link.l2 = StringFromKey("Morgan_49", pchar);
				link.l2.go = "Step_3_6";
			}
		break;

		case "Have_hot_bussines":    // Если геймеру вдруг захочется ещё пообщаться, не знаю, сможет ли. Но на всякий случай.
			dialog.text = StringFromKey("Morgan_50");
			link.l1 = StringFromKey("Morgan_51");
			link.l1.go = "exit";
			NextDiag.TempNode = "Have_hot_bussines";
		break;

		case "Step_3_6":                   // Отказ от предложения Моргана атаковать испанский город.
			dialog.text = StringFromKey("Morgan_52");
			link.l1 = StringFromKey("Morgan_53");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -10);
			AddCharacterSkill(pchar, SKILL_LEADERSHIP, 0);

			AddQuestRecord("Eng_Line_3_Morgan", "2");
			AddQuestUserData("Eng_Line_3_Morgan", "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("Eng_Line_3_Morgan");
			pchar.questTemp.Waiting_time = "2";       // 2 так, для проформы, чтоб поддержать стандарт
			pchar.questTemp.CurQuestNumber = "4";     // идем на четвёртый квест
			NextDiag.TempNode = "First time";
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;

		case "Step_3_7":                  // Согласие на участие в нападении на Белиз
			AddQuestRecord("Eng_Line_3_Morgan", "3");
			pchar.nation = PIRATE;
			pchar.questTemp.State = "AttackBeliz_GoOn";
			LAi_SetActorType(NPChar);
			LAi_ActorSetStayMode(NPChar);
			ChangeCharacterAddressGroup(NPChar, "PortRoyal_houseS1", "goto", "goto7");
			CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 8.5, false);
			Fantom_SetBalls(npchar, "pirate");
			npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			// ==>  Кол-во компаньонов. Нужно для раздела золота независимо от того, кто остался жив, т.е. в обойме компаньонов(по закону берегового братства).
			pchar.questTemp.CompanionQuantity = "2";
			//HardCoffee ref Jackman's dialogue
			//characters[GetCharacterIndex("Jackman")].dialog.currentnode = "Lets_go_bussines";
			pchar.QuestTemp.EngLine_Jackman_task = "Lets_go_bussines";
			AddLandQuestmark_Main(&characters[GetCharacterIndex("Jackman")], "Eng_Line");
			// ==>  Помещаем Джона Морриса в Бриджтаун и даем соотв. ноду
			characters[GetCharacterIndex("John Morris")].dialog.currentnode = "Lets_go_bussines";
			AddLandQuestmark_Main(&characters[GetCharacterIndex("John Morris")], "Eng_Line");
			// ==>  Заводим таймер на прерывание, даем 31 дней.
			SetTimerCondition("time_over_Beliz_attack", 0, 0, 51, false);
			SaveCurrentQuestDateParam("questTemp");
			NextDiag.TempNode = "Have_hot_bussines";
			pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
			// ==> капитулянтская нода губернатору Белиза
			characters[GetCharacterIndex("Beliz_Mayor")].dialog.captureNode = "EngLine3Quest_BelizAttack"; //капитулянтская нода мэра
			AddLandQuestmark_Main(&characters[GetCharacterIndex("Beliz_Mayor")], "Eng_Line");
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "time_over_Beliz":    // Геймер не успел взять Венесуэлу
			dialog.text = StringFromKey("Morgan_54", pchar);
			link.l1 = StringFromKey("Morgan_55");
			link.l1.go = "Step_3_8";
			// выход с палубы
			pchar.quest.Munity = "Deads";
			LAi_LockFightMode(Pchar, false);
		break;

		case "Step_3_8":
			LAi_SetPlayerType(pchar);
			if (IsCompanion(npchar))
			{
				RemoveCharacterCompanion(pchar, npchar);
			}
			if (IsCompanion(characterFromID("Jackman")))
			{
				RemoveCharacterCompanion(pchar, characterFromID("Jackman"));
			}
			if (IsCompanion(characterFromID("John Morris")))
			{
				RemoveCharacterCompanion(pchar, characterFromID("John Morris"));
			}

			QuestToSeaLogin_Prepare(worldMap.playerShipX, worldMap.playerShipZ, worldMap.island);
			if (worldMap.island != WDM_NONE_ISLAND)      // если возле острова
			{
				questToSeaLoginer.FromCoast = true;
			}
			else
			{
				questToSeaLoginer.FromCoast = false;
			}
			QuestToSeaLogin_Launch();

			Log_SetStringToLog(StringFromKey("InfoMessages_189"));
			// ==> Возвращаем на место Моргана
			ChangeCharacterAddressGroup(npchar, "PortRoyal_houseS1", "sit", "sit2");
			LAi_SetHuberType(npchar);
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			// ==> Возвращаем на место Джекмена
			if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))
			{
				LAi_SetHuberType(characterfromID("Jackman"));
				LAi_group_MoveCharacter(characterfromID("Jackman"), "PIRATE_CITIZENS");
				ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Pirates_townhall", "sit", "sit1");
				characters[GetCharacterIndex("Jackman")].dialog.currentnode = "First time";
			}
			RemoveLandQuestmark_Main(&characters[GetCharacterIndex("Jackman")], "Eng_Line");
			// ==> Возвращаем на место Джона Морриса
			if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
			{
				LAi_SetHuberType(characterfromID("John Morris"));
				LAi_group_MoveCharacter(characterfromID("John Morris"), "ENGLAND_CITIZENS");
				ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "PortSpein_houseF2", "sit", "sit1");
				characters[GetCharacterIndex("John Morris")].dialog.currentnode = "First time";
			}
			RemoveLandQuestmark_Main(&characters[GetCharacterIndex("John Morris")], "Eng_Line");
			//снимем ноду губеру
			characters[GetCharacterIndex("Beliz_Mayor")].dialog.captureNode = "CAPTURE_Main";
			RemoveLandQuestmark_Main(&characters[GetCharacterIndex("Beliz_Mayor")], "Eng_Line");
			AddMoneyToCharacter(pchar, -50000);
			ChangeCharacterReputation(pchar, -20);
			// нулим опыт в лидерстве и удаче
			AddCharacterSkill(pchar, SKILL_LEADERSHIP, 0);
			AddCharacterSkill(pchar, SKILL_SNEAK, 0);

			AddQuestRecord("Eng_Line_3_Morgan", "6");
			CloseQuestHeader("Eng_Line_3_Morgan");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			RemoveLandQuestmark_Main(characterfromID("John Morris"), "Eng_Line");
			RemoveLandQuestmark_Main(characterfromID("Jackman"), "Eng_Line");
			pchar.questTemp.Waiting_time = "2";
			pchar.questTemp.CurQuestNumber = "4";     // идем на четвёртый квест
			DeleteAttribute(pchar, "questTemp.CompanionQuantity");
			DeleteAttribute(pchar, "TempPerks.QuestTroopers");  //снятие перка квестового десанта
			// потом подумаем как дать солдат в помошь...
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Gold_found_in_fort":    // Нода разговора в форте Куманы
			dialog.text = StringFromKey("Morgan_56", pchar);
			link.l1 = StringFromKey("Morgan_57");
			link.l1.go = "Step_3_9";
		break;

		case "Step_3_9":
			if (!IsCompanion(characterFromID("Henry Morgan")))
			{
				dialog.text = StringFromKey("Morgan_58", pchar);
			}
			else
			{
				dialog.text = StringFromKey("Morgan_59", pchar);
			}
			link.l1 = StringFromKey("Morgan_60");
			link.l1.go = "Step_3_10";
		break;

		case "Step_3_10":
			if (GetCargoMaxSpace(pchar) >= RecalculateCargoLoad(pchar))
			{
				dialog.text = StringFromKey("Morgan_61", pchar.Ship.Cargo.Goods.gold);
			}
			else
			{
				dialog.text = StringFromKey("Morgan_62", GetCargoMaxSpace(pchar), RecalculateCargoLoad(pchar), pchar.Ship.Cargo.Goods.gold);
			}
			link.l1 = StringFromKey("Morgan_63", pchar);
			link.l1.go = "out_fort";
			link.l2 = StringFromKey("Morgan_64");
			link.l2.go = "Agree_sale_gold";
			link.l3 = StringFromKey("Morgan_65", pchar);
			link.l3.go = "exit";
			NextDiag.TempNode = "Think_sale_gold";
		break;

		case "Think_sale_gold":    // ГГ думает о продаже золота
			dialog.text = StringFromKey("Morgan_66", pchar);
			link.l1 = StringFromKey("Morgan_67");
			link.l1.go = "Agree_sale_gold";
			link.l2 = StringFromKey("Morgan_68");
			link.l2.go = "out_fort";
			link.l3 = StringFromKey("Morgan_69");
			link.l3.go = "exit";
			NextDiag.TempNode = "Think_sale_gold";
		break;

		case "Agree_sale_gold":    // ГГ согласен продать золото
			dialog.text = StringFromKey("Morgan_70");
			link.l1 = StringFromKey("Morgan_71", pchar);
			link.l1.go = "sale_gold_25_persent";
			link.l2 = StringFromKey("Morgan_72", pchar);
			link.l2.go = "sale_gold_50_persent";
			link.l3 = StringFromKey("Morgan_73", pchar);
			link.l3.go = "sale_gold_75_persent";
			link.l4 = StringFromKey("Morgan_74", pchar);
			link.l4.go = "sale_gold_all";
			link.l5 = StringFromKey("Morgan_75", pchar);
			link.l5.go = "out_fort";
		break;

		case "sale_gold_25_persent":
			dialog.text = StringFromKey("Morgan_76", pchar);
			link.l1 = StringFromKey("Morgan_77");
			link.l1.go = "out_fort";
			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty) * 0.25));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty) * 0.25 * 200));
		break;

		case "sale_gold_50_persent":
			dialog.text = StringFromKey("Morgan_78", pchar);
			link.l1 = StringFromKey("Morgan_79");
			link.l1.go = "out_fort";
			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty) * 0.5));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty) * 0.50 * 200));
		break;

		case "sale_gold_75_persent":
			dialog.text = StringFromKey("Morgan_80", pchar);
			link.l1 = StringFromKey("Morgan_81");
			link.l1.go = "out_fort";
			RemoveCharacterGoods(Pchar, GOOD_GOLD, makeint(sti(pchar.questTemp.BelizGoldQty) * 0.75));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty) * 0.75 * 200));
		break;

		case "sale_gold_all":
			dialog.text = StringFromKey("Morgan_82");
			link.l1 = StringFromKey("Morgan_83");
			link.l1.go = "out_fort";
			RemoveCharacterGoods(Pchar, GOOD_GOLD, sti(pchar.questTemp.BelizGoldQty));
			AddMoneyToCharacter(pchar, makeint(sti(pchar.questTemp.BelizGoldQty) * 200));
		break;

		case "out_fort":
			pchar.quest.time_over_Beliz_attack_Map_01.over = "yes"; // сброс, если уже откладывали
			pchar.quest.time_over_Beliz_attack_Map_02.over = "yes";
			pchar.quest.time_over_Beliz_attack.over = "yes";

			if (IsCompanion(characterFromID("Jackman")))
			{
				RemoveCharacterCompanion(pchar, characterFromID("Jackman"));
			}
			if (IsCompanion(characterFromID("John Morris")))
			{
				RemoveCharacterCompanion(pchar, characterFromID("John Morris"));
			}
			AddQuestRecord("Eng_Line_3_Morgan", "7");
			RemoveCharacterCompanion(pchar, npchar);
			// ==> Возвращаем на место Моргана
			ChangeCharacterAddressGroup(npchar, "PortRoyal_houseS1", "sit", "sit2");
			LAi_SetHuberTypeNoGroup(npchar);
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
			// ==> Возвращаем на место Джекмена
			if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Jackman"))
			{
				ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Jackman")], "Pirates_townhall", "sit", "sit1");
				LAi_SetHuberType(characterfromID("Jackman"));
				characters[GetCharacterIndex("Jackman")].dialog.currentnode = "I_know_you_good";
			}
			else
			{
				characters[GetCharacterIndex("Jackman")].dialog.currentnode = "First time";
			}
			RemoveLandQuestmark_Main(characterfromID("Jackman"), "Eng_Line");
			// ==> Возвращаем на место Джона Морриса
			if (CheckAttribute(pchar, "questTemp.CompanionQuantity.Morris"))
			{
				ChangeCharacterAddressGroup(&characters[GetCharacterIndex("John Morris")], "PortSpein_houseF2", "sit", "sit1");
				LAi_SetHuberType(characterfromID("John Morris"));
				characters[GetCharacterIndex("John Morris")].dialog.currentnode = "I_know_you_good";
			}
			else
			{
				characters[GetCharacterIndex("John Morris")].dialog.currentnode = "First time";
			}
			RemoveLandQuestmark_Main(characterfromID("John Morris"), "Eng_Line");
			ChangeCharacterReputation(pchar, 1);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Fencing", 500);
			AddCharacterExpToSkill(pchar, "Pistol", 550);
			AddCharacterExpToSkill(pchar, "Sailing", 550);
			AddCharacterExpToSkill(pchar, "Accuracy", 330);
			AddCharacterExpToSkill(pchar, "Cannons", 150);

			CloseQuestHeader("Eng_Line_3_Morgan");
			pchar.questTemp.Waiting_time = "2";
			pchar.questTemp.CurQuestNumber = "4";     // идем на четвёртый квест
			pchar.questTemp.State = "empty";
			DeleteAttribute(pchar, "questTemp.CompanionQuantity");
			DeleteAttribute(pchar, "questTemp.BelizGoldQty");
			DeleteAttribute(pchar, "TempPerks.QuestTroopers"); //дублирование снятия перка квестового десанта
			LAi_LocationFightDisable(&Locations[FindLocation("Beliz_fort")], false); //вернём боевки
			chrDisableReloadToLocation = false;
			pchar.nation = ENGLAND; // вернём нацию
			InterfaceStates.Buttons.Save.enable = true;   // вернём запись
			DoReloadCharacterToLocation("Beliz_town", "reload", "gate_back"); //ГГ в город
			NextDiag.CurrentNode = "I_know_you_good";
			DialogExit();
		break;

		case "Give_blade":
			DeleteAttribute(pchar, "QuestTemp.EngLine_Morgan_task");
			dialog.text = StringFromKey("Morgan_84", GetFullName(pchar));
			link.l1 = StringFromKey("Morgan_85", pchar);
			link.l1.go = "Step_9_1";
		break;

		case "Step_9_1":
			dialog.text = StringFromKey("Morgan_86");
			link.l1 = StringFromKey("Morgan_87");
			link.l1.go = "exit";
			//NextDiag.TempNode = "I_know_you_good";
			GiveItem2Character(pchar, "blade27");
			RemoveCharacterEquip(NPChar, BLADE_ITEM_TYPE);
			TakeItemFromCharacter(NPChar, "blade27");
			GiveItem2Character(NPChar, "blade22");
			EquipCharacterByItem(NPChar, "blade22");
			RemoveLandQuestmark_Main(npchar, "Eng_Line");
		break;
		//********************* Голландская линейка *********************
		/*case "HolLine3_fromMansfield":
			dialog.text = "Чему обязан за удовольствие видеть вас здесь?";
			link.l1 = "Я " + GetSexPhrase("прибыл", "прибыла") +" к вам по поручению Эдварда Мэнсфилда.";
			link.l1.go = "Step_H3_1";
		break;*/
		case "Step_H3_1":
			DeleteAttribute(pchar, "QuestTemp.HolLine_quests_task");
			dialog.text = StringFromKey("Morgan_88");
			link.l1 = StringFromKey("Morgan_89");
			link.l1.go = "Step_H3_2";
		break;
		case "Step_H3_2":
			dialog.text = StringFromKey("Morgan_90");
			link.l1 = StringFromKey("Morgan_91");
			link.l1.go = "Step_H3_3";
		break;
		case "Step_H3_3":
			dialog.text = StringFromKey("Morgan_92");
			link.l1 = StringFromKey("Morgan_93", pchar);
			link.l1.go = "Step_H3_4";
			link.l2 = StringFromKey("Morgan_94");
			link.l2.go = "Step_H3_NoWork";
		break;
		case "Step_H3_NoWork":
			dialog.text = StringFromKey("Morgan_95");
			link.l1 = StringFromKey("Morgan_96");
			link.l1.go = "exit";
			//NextDiag.TempNode = "First time";
			pchar.questTemp.State = "WormEnglPlans_SurrenderWorkMorgan";
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "4");
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("ся", "ась"));
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;
		case "Step_H3_4":
			dialog.text = StringFromKey("Morgan_97");
			link.l1 = StringFromKey("Morgan_98");
			link.l1.go = "exit";
			pchar.questTemp.Hol_Line_AboutWorm.Nums = 2;
			pchar.questTemp.Hol_Line_AboutWorm.Again = false;
			pchar.questTemp.State = "WormEnglPlans_WormPicarder";
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "6");
			AddQuestUserData("Hol_Line_3_WormEnglishPlans", "sSex", GetSexPhrase("ся", "ась"));
			AddLandQuestmark_Main_WithCondition(npchar, "Hol_Line", "HolLine_3_WormPicarder_Morgan_QuestMarkCondition");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_tavernkeeper"), "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_trader"), "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_shipyarder"), "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_Hostess"), "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("Tortuga_usurer"), "Hol_Line");
		break;
		case "HolLine3_aboutWorm":
			dialog.text = StringFromKey("Morgan_99");
			link.l1 = StringFromKey("Morgan_100");
			link.l1.go = "Step_H3_5";
		break;
		case "Step_H3_5":
			dialog.text = StringFromKey("Morgan_101");
			if (sti(pchar.questTemp.Hol_Line_AboutWorm.Nums) < 4)
				link.l1 = StringFromKey("Morgan_102", FactsAboutTheWurm());
			else
				link.l1 = StringFromKey("Morgan_103", FactsAboutTheWurm());
			link.l1.go = "Step_H3_6";
		break;
		case "Step_H3_5_again":
			dialog.text = StringFromKey("Morgan_104");
			link.l1 = StringFromKey("Morgan_105", FactsAboutTheWurm());
			link.l1.go = "Step_H3_6";
		break;
		case "Step_H3_6":
			iTemp = sti(pchar.questTemp.Hol_Line_AboutWorm.Nums);
			if (iTemp > 6)
			{
				dialog.text = StringFromKey("Morgan_106");
				link.l1 = StringFromKey("Morgan_107", pchar);
				link.l1.go = "Step_H3_10";
			}
			else
			{
				pchar.questTemp.Hol_Line_AboutWorm.Again = true;
				dialog.text = StringFromKey("Morgan_108");
				if (3 == iTemp)
					dialog.text = StringFromKey("Morgan_109", dialog.text);
				else if (4 == iTemp)
					dialog.text = StringFromKey("Morgan_110", dialog.text);
				else if (5 == iTemp)
					dialog.text = StringFromKey("Morgan_111", dialog.text);
				else if (6 == iTemp)
					dialog.text = StringFromKey("Morgan_112", dialog.text);
				dialog.text = StringFromKey("Morgan_113", dialog.text);
				link.l1 = StringFromKey("Morgan_114");
				link.l1.go = "exit";
				link.l2 = StringFromKey("Morgan_115", pchar);
				link.l2.go = "Step_H3_7";
				SetCurrentQuestMark(npchar); // обновим метку
			}
		break;
		case "Step_H3_7":
			dialog.text = StringFromKey("Morgan_116");
			link.l1 = StringFromKey("Morgan_117");
			link.l1.go = "Step_H3_8";
		break;
		case "Step_H3_8":
			dialog.text = StringFromKey("Morgan_118");
			link.l1 = StringFromKey("Morgan_119");
			link.l1.go = "Step_H3_9";
		break;
		case "Step_H3_9":
			dialog.text = StringFromKey("Morgan_120");
			link.l1 = StringFromKey("Morgan_121");
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "12");
			DeleteAttribute(pchar, "questTemp.Hol_Line_AboutWorm");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;
		case "Step_H3_10":
			dialog.text = StringFromKey("Morgan_122");
			link.l1 = StringFromKey("Morgan_123");
			link.l1.go = "Step_H3_11";
		break;
		case "Step_H3_11":
			dialog.text = StringFromKey("Morgan_124");
			link.l1 = StringFromKey("Morgan_125", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			AddQuestRecord("Hol_Line_3_WormEnglishPlans", "13");
			DeleteAttribute(pchar, "questTemp.Hol_Line_AboutWorm");
			pchar.questTemp.State = "WormEnglPlans_SaveOfficer";
			sld = GetCharacter(NPC_GenerateCharacter("Alan_MacLine", "off_eng_2", "man", "man", 10, ENGLAND, 1, false));
			sld.name = FindPersonalName("Alan_MacLine_name");
			sld.lastname = FindPersonalName("Alan_MacLine_lastname");
			sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Alan_MacLine")], "SentJons_prison", "goto", "goto9");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(sld, "Hol_Line");
			AddLandQuestmarkToFantoms_Main("JailOff", "Hol_Line", "SentJons_JailOff_QuestMarkCondition");
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;
		// ==> Квест №6 голландки.
		/*case "HolLine6_fromStuvesant": //HardCoffee реф диалгов
		  dialog.text = "Что привело вас ко мне на этот раз?";
		  link.l1 = "Я " + GetSexPhrase("уполномочен", "уполномочена") +" заявить, что Нидерланды хотят возмездия за смерть Эдварда Мэнсфилда.";
		  link.l1.go = "Step_H6_1";
	  break;*/
		case "Step_H6_1":
			DeleteAttribute(pchar, "QuestTemp.HolLine_quests_task");
			dialog.text = StringFromKey("Morgan_126");
			link.l1 = StringFromKey("Morgan_127");
			link.l1.go = "Step_H6_2";
		break;
		case "Step_H6_2":
			dialog.text = StringFromKey("Morgan_128");
			link.l1 = StringFromKey("Morgan_129");
			link.l1.go = "Step_H6_3";
		break;
		case "Step_H6_3":
			dialog.text = StringFromKey("Morgan_130");
			link.l1 = StringFromKey("Morgan_131");
			link.l1.go = "Step_H6_4";
		break;
		case "Step_H6_4":
			dialog.text = StringFromKey("Morgan_132");
			link.l1 = StringFromKey("Morgan_133", pchar);
			link.l1.go = "Step_H6_5";
		break;
		case "Step_H6_5":
			dialog.text = StringFromKey("Morgan_134");
			link.l1 = StringFromKey("Morgan_135");
			link.l1.go = "exit";
			AddQuestRecord("Hol_Line_6_RevengeMansfield", "2");
			AddQuestUserData("Hol_Line_6_RevengeMansfield", "sSex", GetSexPhrase("ен", "на"));
			pchar.questTemp.State = "RevengeMansfield_toTavern";
			NextDiag.TempNode = "I_know_you_good";
			LAi_group_MoveCharacter(characterFromID("Santiago_tavernkeeper"), "QuestGroup");
			LAi_group_MoveCharacter(characterFromID("Santiago_waitress"), "QuestGroup");
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(characterFromID("Santiago_tavernkeeper"), "Hol_Line");
		break;
		case "HolLine6_fromSantiago":
			DeleteAttribute(pchar, "QuestTemp.HolLine_quests_task");
			dialog.text = StringFromKey("Morgan_136");
			link.l1 = StringFromKey("Morgan_137");
			link.l1.go = "Step_H6_6";
		break;
		case "Step_H6_6":
			dialog.text = StringFromKey("Morgan_138", pchar);
			link.l1 = StringFromKey("Morgan_139", pchar);
			link.l1.go = "Step_H6_7";
		break;
		case "Step_H6_7":
			dialog.text = StringFromKey("Morgan_140");
			link.l1 = StringFromKey("Morgan_141", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "RevengeMansfield_FromMorganWithResult";
			AddQuestRecord("Hol_Line_6_RevengeMansfield", "4");
			NextDiag.TempNode = "I_know_you_good";
			RemoveLandQuestmark_Main(npchar, "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;
		//********************* Французская линейка *********************
		/*case "FraLine8_talk": //HardCoffee реф диалогов
			dialog.text = "Ага, да это " + GetSexPhrase("сам", "сама") +" капитан " + GetFullName(pchar) + "! Я давно за тобой присматриваю. До сих пор ты не " + GetSexPhrase("лез", "лезла") +" в мои дела, и поэтому ещё " + GetSexPhrase("жив", "жива") +" и " + GetSexPhrase("здоров", "здорова") +". Говори, зачем " + GetSexPhrase("пожаловал", "пожаловала") +". Полагаю, не для праздных разговоров.";
			link.l1 = "Послушай, Морган, те же знаешь, что просто так я не " + GetSexPhrase("стал", "стала") +" бы тебя беспокоить. Я по делу.";
			link.l1.go = "Step_F8_1";
		break;*/
		case "Step_F8_1":
			dialog.text = StringFromKey("Morgan_142");
			link.l1 = StringFromKey("Morgan_143");
			link.l1.go = "Step_F8_2";
		break;
		case "Step_F8_2":
			dialog.text = StringFromKey("Morgan_144");
			link.l1 = StringFromKey("Morgan_145");
			link.l1.go = "Step_F8_3";
		break;
		case "Step_F8_3":
			dialog.text = StringFromKey("Morgan_146");
			link.l1 = StringFromKey("Morgan_147");
			link.l1.go = "Step_F8_4";
		break;
		case "Step_F8_4":
			dialog.text = StringFromKey("Morgan_148");
			link.l1 = StringFromKey("Morgan_149");
			link.l1.go = "Step_F8_5";
		break;
		case "Step_F8_5":
			dialog.text = StringFromKey("Morgan_150");
			link.l1 = StringFromKey("Morgan_151", pchar);
			link.l1.go = "Step_F8_6";
		break;
		case "Step_F8_6":
			dialog.text = StringFromKey("Morgan_152");
			if (sti(pchar.money) >= 250000)
			{
				link.l1 = StringFromKey("Morgan_153");
				link.l1.go = "Step_F8_7";
			}
			if ("NeedMoney" != pchar.QuestTemp.FraLine_Morgan_task)
			{
				link.l2 = StringFromKey("Morgan_154");
				link.l2.go = "Fra_NeedMoney";
			}
			NextDiag.TempNode = "I_know_you_good";
		break;
		case "Step_F8_7":
			DeleteAttribute(pchar, "QuestTemp.FraLine_Morgan_task");
			AddMoneyToCharacter(pchar, -250000);
			dialog.text = StringFromKey("Morgan_155");
			link.l1 = StringFromKey("Morgan_156", pchar);
			link.l1.go = "exit";
			pchar.questTemp.Count = makeint(pchar.questTemp.Count) + 1;
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "4");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Oliver_Green"), "Fra_Line");
		break;
		case "Fra_NeedMoney":
			if (CheckAttribute(npchar, "quest.repeat")) DeleteAttribute(npchar, "quest.repeat");
			//Может стоит добавить сюда запись в журнал о том, что ему надо 250к?
			DialogExit();
			pchar.QuestTemp.FraLine_Morgan_task = "NeedMoney";
		break;
		//********************* Пиратская линейка *********************
		//квест №1, диалог в тюрьме
		case "PL_Q1_1":
			dialog.text = StringFromKey("Morgan_157", pchar);
			link.l1 = StringFromKey("Morgan_158", pchar);
			link.l1.go = "PL_Q1_2";
		break;
		case "PL_Q1_2":
			dialog.text = StringFromKey("Morgan_159");
			link.l1 = StringFromKey("Morgan_160");
			link.l1.go = "PL_Q1_3";
		break;
		case "PL_Q1_3":
			dialog.text = StringFromKey("Morgan_161", pchar);
			link.l1 = StringFromKey("Morgan_162", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.QuestTemp.PirLine_quests_task = "AfterPrison";
			AddMoneyToCharacter(PChar, 10000);
			AddDialogExitQuestFunction("PiratesLine_q1_MorganEnd");
		break;
		//квест №2, диалог в резиденции Порт-Ройал.
		case "PL_Q2_1":
			DeleteAttribute(pchar, "QuestTemp.PirLine_quests_task");
			CloseQuestHeader("Pir_Line_1_JohnBolton");
			dialog.text = StringFromKey("Morgan_163", pchar);
			link.l1 = StringFromKey("Morgan_164");
			link.l1.go = "PL_Q2_2";
		break;
		case "PL_Q2_2":
			dialog.text = StringFromKey("Morgan_165");
			link.l1 = StringFromKey("Morgan_166", pchar);
			link.l1.go = "exit";
			sld = GetCharacter(NPC_GenerateCharacter("EdwardLoy", "EdwardLow", "man", "man", 10, PIRATE, -1, true));
			FantomMakeCoolFighter(sld, 10, 55, 50, "blade25", "pistol3", 75);
			FantomMakeCoolSailor(sld, SHIP_BRIGSW, FindPersonalName("EdwardLoy_mapEnc"), CANNON_TYPE_CANNON_LBS24, 60, 45, 45);
			sld.name = FindPersonalName("EdwardLoy_name");
			sld.lastname = FindPersonalName("EdwardLoy_lastname");
			sld.rank = 10;
			sld.city = "LeFransua";
			sld.location = "LeFransua_House4";
			sld.location.group = "goto";
			sld.location.locator = "goto1";
			sld.dialog.filename = "Quest\PiratesLine_dialog.c";
			sld.dialog.currentnode = "EdwardLoy";
			sld.greeting = "Gr_EvilPirate";
			sld.AlwaysSandbankManeuver = true;
			sld.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
			LAi_SetWarriorType(sld);
			GiveItem2Character(pchar, "BlackLabel");
			LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
			pchar.questTemp.piratesLine = "BlackLabel_toLaVega";
			SetQuestHeader("Pir_Line_2_BlackLabel");
			AddQuestRecord("Pir_Line_2_BlackLabel", "1");
			NextDiag.TempNode = "I_know_you_good";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestmark_Main(sld, "Pir_Line");
			AddLandQuestmark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Pir_Line");
		break;

		/*case "PL_Q2_wait": //HardCoffee реф диалогов
			dialog.text = "" + GetSexPhrase("Вручил", "Вручила") +" Метку?";
			link.l1 = "Нет ещё, Морган, занимаюсь этим...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q2_wait";
		break;*/

		/*case "PL_Q2_away_1":
			DeleteAttribute(pchar, "QuestTemp.PirLine_quests_task");
			dialog.text = "А-а! Ну, рассказывай, " + GetSexPhrase("был", "была") +" на Мартинике? Лоу " + GetSexPhrase("нашёл", "нашла") +"?";
			link.l1 = "" + GetSexPhrase("Был", "Была") +", метку " + GetSexPhrase("передал", "передала") +".";
			link.l1.go = "PL_Q2_away_2";

		break;*/
		case "PL_Q2_away_2":
			dialog.text = StringFromKey("Morgan_167");
			link.l1 = StringFromKey("Morgan_168", pchar);
			link.l1.go = "PL_Q2_away_3";
			CloseQuestHeader("Pir_Line_2_BlackLabel");
		break;
		case "PL_Q2_away_3":
			dialog.text = StringFromKey("Morgan_169");
			link.l1 = StringFromKey("Morgan_170");
			link.l1.go = "PL_Q2_away_4";
		break;
		case "PL_Q2_away_4":
			dialog.text = StringFromKey("Morgan_171");
			link.l1 = StringFromKey("Morgan_172");
			link.l1.go = "PL_Q2_away_5";
			AddItemLog(pchar, "chest", "1", StringFromKey("InfoMessages_136"), "Important_item");
		break;
		case "PL_Q2_away_5":
			dialog.text = StringFromKey("Morgan_173");
			link.l1 = StringFromKey("Morgan_174");
			link.l1.go = "PL_Q2_away_6";
		break;
		case "PL_Q2_away_6":
			dialog.text = StringFromKey("Morgan_175");
			link.l1 = StringFromKey("Morgan_176");
			link.l1.go = "exit";
			SetQuestHeader("Pir_Line_3_KillLoy");
			AddQuestRecord("Pir_Line_3_KillLoy", "1");
			AddQuestUserData("Pir_Line_3_KillLoy", "sSex", GetSexPhrase("", "а"));
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "KillLoy_toHouse";
			pchar.QuestTemp.PirLine_quests_task = "ShouldKillLoy";
			ChangeCharacterAddress(characterFromId("EdwardLoy"), "none", "");
			pchar.quest.PiratesLine_q3_LoyHouse.win_condition.l1 = "location";
			pchar.quest.PiratesLine_q3_LoyHouse.win_condition.l1.location = "LeFransua_House4";
			pchar.quest.PiratesLine_q3_LoyHouse.function = "PiratesLine_q3_LoyHouse";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
		case "ShouldKillLoy":
			dialog.text = StringFromKey("Morgan_177");
			link.l1 = StringFromKey("Morgan_178");
			link.l1.go = "exitAgr";
			link.l2 = StringFromKey("Morgan_179", pchar);
			link.l2.go = "PL_Q3_notFound";
		break;
		case "PL_Q3_notFound":
			dialog.text = StringFromKey("Morgan_180", pchar);
			link.l1 = StringFromKey("Morgan_181", pchar);
			link.l1.go = "PL_Q3_notFound_1";
		break;
		case "PL_Q3_notFound_1":
			dialog.text = StringFromKey("Morgan_182");
			link.l1 = StringFromKey("Morgan_183");
			link.l1.go = "exit";
			DeleteAttribute(pchar, "QuestTemp.PirLine_quests_task");
			pchar.questTemp.piratesLine = "waiting_Q4";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_3_KillLoy");
			AddLandQuestmark_Main_WithCondition(npchar, "Pir_Line", "PirLine_waiting_Q4_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Pir_Line", "PirLine_waiting_Q4_WDMQuestMarkCondition");
		break;
		case "PL_Q3_GoodWork":
			DeleteAttribute(pchar, "QuestTemp.PirLine_quests_task");
			dialog.text = StringFromKey("Morgan_184", pchar);
			link.l1 = StringFromKey("Morgan_185");
			link.l1.go = "PL_Q3_GoodWork_1";
		break;
		case "PL_Q3_GoodWork_1":
			dialog.text = StringFromKey("Morgan_186");
			link.l1 = StringFromKey("Morgan_187");
			link.l1.go = "PL_Q3_GoodWork_2";
		break;
		case "PL_Q3_GoodWork_2":
			dialog.text = StringFromKey("Morgan_188", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Morgan_189");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q4";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_3_KillLoy");
			AddItemLog(pchar, "incas_collection", "1", StringFromKey("InfoMessages_137"), "Important_item");
			AddLandQuestmark_Main_WithCondition(npchar, "Pir_Line", "PirLine_waiting_Q4_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Pir_Line", "PirLine_waiting_Q4_WDMQuestMarkCondition");
		break;
		//квест №4, жемчужные тартаны
		case "PL_Q4_1":
			dialog.text = StringFromKey("Morgan_190");
			link.l1 = StringFromKey("Morgan_191");
			link.l1.go = "PL_Q4_3";
		break;
		case "PL_Q4_3":
			dialog.text = StringFromKey("Morgan_192");
			link.l1 = StringFromKey("Morgan_193");
			link.l1.go = "PL_Q4_4";
		break;
		case "PL_Q4_4":
			dialog.text = StringFromKey("Morgan_194");
			link.l1 = StringFromKey("Morgan_195", pchar);
			link.l1.go = "PL_Q4_5";
		break;

		case "PL_Q4_5":
			dialog.text = StringFromKey("Morgan_196", pchar);
			link.l1 = StringFromKey("Morgan_197");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "PearlQ4_toTerks"; //флаг квеста
			pchar.questTemp.Sharp.PearlAreal = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Island = "Terks";
			pchar.questTemp.Sharp.PearlAreal.Shore = "Shore56";
			pchar.questTemp.Sharp.PearlAreal.locator = "Quest_ship_1";
			pchar.questTemp.Sharp.PearlAreal.terms = 30; //сроки
			pchar.questTemp.Sharp.PearlAreal.qtyShips = 9; //кол-во тартан ловцов
			//			pchar.questTemp.Sharp.PearlAreal.SmallPearlQty = 0; //для итогового подсчета
			//			pchar.questTemp.Sharp.PearlAreal.BigPearlQty = 0;
			pchar.questTemp.Sharp.PearlAreal.PinctadaQty = 0;
			SetQuestHeader("Pir_Line_4_Pearl");
			AddQuestRecord("Pir_Line_4_Pearl", "1");
			AddQuestUserData("Pir_Line_4_Pearl", "sSex", GetSexPhrase("ен", "на"));
			pchar.quest.PQ4_SeaPearl_login.win_condition.l1 = "location";
			pchar.quest.PQ4_SeaPearl_login.win_condition.l1.location = "Terks";
			pchar.quest.PQ4_SeaPearl_login.function = "PQ4_SeaPearl_login";
			SetTimerFunction("PQ4_SeaPearl_Late", 0, 0, sti(pchar.questTemp.Sharp.PearlAreal.terms));

			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			RemoveMapQuestMark("PortRoyal_town", "Pir_Line");
		break;
		/*case "PL_Q4_wait": //HardCoffee реф диалогов
			dialog.text = "" + GetSexPhrase("Ограбил", "Ограбила") +" ловцов жемчуга?";
			link.l1 = "Нет ещё, Морган, я занимаюсь этим...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q4_wait";
		break;

		case "PL_Q4_late":
			dialog.text = "Ну, что скажешь?";
			link.l1 = "Генри, случилось так, что я " + GetSexPhrase("опоздал", "опоздала") +" к Терксу.";
			link.l1.go = "PL_Q4_late_1";
		break;*/
		case "PL_Q4_late_1": //опоздал

			dialog.text = StringFromKey("Morgan_198", pchar);
			link.l1 = StringFromKey("Morgan_199");
			link.l1.go = "PearlQ4_late_2";
		break;
		case "PearlQ4_late_2":
			DeleteAttribute(pchar, "QuestTemp.PirLine_quests_task");
			dialog.text = StringFromKey("Morgan_200");
			link.l1 = StringFromKey("Morgan_201");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q5";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_4_Pearl");
			//дача пятого квеста
			Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1 = "location";
			Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1.location = "PortRoyal_town";
			Pchar.quest.PQ5_meetInPortRoyal.function = "PQ5_meetInPortRoyal";
		break;
		//неудачный наезд
		case "PL_Q4_badWork":
			dialog.text = StringFromKey("Morgan_202", pchar);
			link.l1 = StringFromKey("Morgan_203", pchar);
			link.l1.go = "PL_Q4_badWork_1";
		break;
		case "PL_Q4_badWork_1":
			dialog.text = StringFromKey("Morgan_204", pchar);
			link.l1 = StringFromKey("Morgan_205");
			link.l1.go = "PearlQ4_late_2";
		break;
		//удачный наезд
		case "PL_Q4_goodWork":
			DeleteAttribute(pchar, "QuestTemp.PirLine_quests_task");
			dialog.text = StringFromKey("Morgan_206", GetFullName(pchar));
			if (GetSquadronGoods(pchar, GOOD_PINCTADA) <= 0)
			{
				link.l1 = StringFromKey("Morgan_207");
				link.l1.go = "PL_Q4_goodWork_lair";
			}
			else
			{
				link.l1 = StringFromKey("Morgan_208", pchar, GetSquadronGoods(pchar, GOOD_PINCTADA));
				link.l1.go = "PL_Q4_goodWork_1";
			}
		break;

		case "PL_Q4_goodWork_lair":
			dialog.text = StringFromKey("Morgan_209", pchar);
			link.l1 = StringFromKey("Morgan_210");
			link.l1.go = "PL_Q4_goodWork_lair_1";
		break;
		case "PL_Q4_goodWork_lair_1":
			dialog.text = StringFromKey("Morgan_211");
			link.l1 = StringFromKey("Morgan_212");
			link.l1.go = "fight"; //А это нормально, что Морган в этой битве бессмертный?
			chrDisableReloadToLocation = true;
			pchar.questTemp.piratesLine = "over";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;

		case "PL_Q4_goodWork_1":
			if (GetSquadronGoods(pchar, GOOD_PINCTADA) < sti(pchar.questTemp.piratesLine.Qty.Pinctada))
			{
				dialog.text = StringFromKey("Morgan_213", pchar, pchar.questTemp.piratesLine.Qty.Pinctada);
				link.l1 = StringFromKey("Morgan_214");
				link.l1.go = "PL_Q4_goodWork_2";
				link.l2 = StringFromKey("Morgan_215");
				link.l2.go = "PL_Q4_goodWork_6";
			}
			else
			{
				if (GetSquadronGoods(pchar, GOOD_PINCTADA) >= 6000)
				{
					dialog.text = StringFromKey("Morgan_216", pchar);
					link.l1 = StringFromKey("Morgan_217");
					link.l1.go = "PL_Q4_goodWork_3";
				}
				else
				{
					dialog.text = StringFromKey("Morgan_218", pchar);
					link.l1 = StringFromKey("Morgan_219", pchar);
					link.l1.go = "PL_Q4_goodWork_5";
				}
			}
		break;
		case "PL_Q4_goodWork_2":
			dialog.text = StringFromKey("Morgan_220", pchar);
			link.l1 = StringFromKey("Morgan_221");
			link.l1.go = "fight";
			chrDisableReloadToLocation = true;
			pchar.questTemp.piratesLine = "over";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;
		case "PL_Q4_goodWork_3":
			dialog.text = StringFromKey("Morgan_222");
			link.l1 = StringFromKey("Morgan_223");
			link.l1.go = "PL_Q4_goodWork_4";
			PlaySound("Took_item");
			if (CheckAttribute(pchar, "questTemp.piratesLine.Qty.CheckPinctada"))
			{
				Log_Info(StringFromKey("InfoMessages_218", makeint(sti(pchar.questTemp.piratesLine.Qty.CheckPinctada) / 2)));
				RemoveCharacterGoods(pchar, GOOD_PINCTADA, makeint(sti(pchar.questTemp.piratesLine.Qty.CheckPinctada) / 2));
			}
			else
			{
				iTemp = GetSquadronGoods(pchar, GOOD_PINCTADA);
				Log_Info(StringFromKey("InfoMessages_217", makeint(iTemp / 2)));
				RemoveCharacterGoods(pchar, GOOD_PINCTADA, makeint(iTemp / 2));
			}
		break;
		case "PL_Q4_goodWork_5":
			dialog.text = StringFromKey("Morgan_224", pchar);
			link.l1 = StringFromKey("Morgan_225");
			link.l1.go = "PL_Q4_goodWork_4";
			if (!CheckAttribute(pchar, "questTemp.piratesLine.Qty.CheckPinctada"))
			{
				RemoveCharacterGoods(pchar, GOOD_PINCTADA, GetSquadronGoods(pchar, GOOD_PINCTADA));
			}
		break;
		case "PL_Q4_goodWork_6":
			dialog.text = StringFromKey("Morgan_226");
			link.l1 = StringFromKey("Morgan_227");
			link.l1.go = "PL_Q4_goodWork_7";
			pchar.questTemp.piratesLine.Qty.CheckPinctada = sti(pchar.questTemp.piratesLine.Qty.Pinctada);
		break;
		case "PL_Q4_goodWork_7":
			dialog.text = CheckPearl();
			link.l1 = StringFromKey("Morgan_228");
			if (sti(pchar.questTemp.piratesLine.Qty.Pinctada) == 0)
			{
				if (sti(pchar.questTemp.piratesLine.Qty.CheckPinctada) >= 6000)
					link.l1.go = "PL_Q4_goodWork_3";
				else    link.l1.go = "PL_Q4_goodWork_5";
			}
			else
			{
				NextDiag.TempNode = "PL_Q4_goodWork_7";
				link.l1.go = "exit";
			}
		break;
		case "PL_Q4_goodWork_4":
			dialog.text = StringFromKey("Morgan_229");
			link.l1 = StringFromKey("Morgan_230");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q5";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			AddQuestRecord("Pir_Line_4_Pearl", "5");
			CloseQuestHeader("Pir_Line_4_Pearl");
			DeleteAttribute(pchar, "questTemp.piratesLine.Qty");
			//дача пятого квеста
			Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1 = "location";
			Pchar.quest.PQ5_meetInPortRoyal.win_condition.l1.location = "PortRoyal_town";
			Pchar.quest.PQ5_meetInPortRoyal.function = "PQ5_meetInPortRoyal";
		break;
		//квест №5, ГГ-ОЗГ. базар после дела
		case "PL_Q5_begin":
			dialog.text = StringFromKey("Morgan_231", pchar, PChar.Name);
			link.l1 = StringFromKey("Morgan_232");
			link.l1.go = "PL_Q5_begin_1";
		break;
		case "PL_Q5_begin_1":
			dialog.text = StringFromKey("Morgan_233", pchar);
			link.l1 = StringFromKey("Morgan_234");
			link.l1.go = "PL_Q5_begin_2";
		break;
		case "PL_Q5_begin_2":
			dialog.text = StringFromKey("Morgan_235");
			link.l1 = StringFromKey("Morgan_236");
			link.l1.go = "PL_Q5_begin_3";
		break;
		case "PL_Q5_begin_3":
			dialog.text = StringFromKey("Morgan_237");
			link.l1 = StringFromKey("Morgan_238");
			link.l1.go = "PL_Q5_begin_4";
		break;
		case "PL_Q5_begin_4":
			dialog.text = StringFromKey("Morgan_239", pchar);
			link.l1 = StringFromKey("Morgan_240", pchar);
			link.l1.go = "PL_Q5_begin_5";
		break;
		case "PL_Q5_begin_5":
			dialog.text = StringFromKey("Morgan_241", pchar);
			link.l1 = StringFromKey("Morgan_242", pchar);
			link.l1.go = "PL_Q5_begin_6";
		break;
		case "PL_Q5_begin_6":
			dialog.text = StringFromKey("Morgan_243");
			link.l1 = StringFromKey("Morgan_244");
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_talking";
			AddDialogExitQuestFunction("PQ5_Morgan_1");
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
		break;

		case "PL_Q5_talking":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("Morgan_245", GetMainCharacterNameDat());
			link.l1 = StringFromKey("Morgan_246", sld);
			link.l1.go = "PL_Q5_talking_1";
		break;
		case "PL_Q5_talking_1":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("Morgan_247", sld);
			link.l1 = StringFromKey("Morgan_248", sld);
			link.l1.go = "PL_Q5_talking_2";
		break;

		case "PL_Q5_talking_2":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("Morgan_249", GetMainCharacterNameDat());
			link.l1 = StringFromKey("Morgan_250", sld);
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end";
			AddDialogExitQuestFunction("PQ5_Morgan_4");
		break;

		case "PL_Q5_end":
			dialog.text = StringFromKey("Morgan_251", GetFullName(pchar));
			link.l1 = StringFromKey("Morgan_252");
			link.l1.go = "PL_Q5_end_1";
		break;
		case "PL_Q5_end_1":
			dialog.text = StringFromKey("Morgan_253", pchar);
			link.l1 = StringFromKey("Morgan_254");
			link.l1.go = "PL_Q5_end_2";
		break;
		case "PL_Q5_end_2":
			dialog.text = StringFromKey("Morgan_255");
			link.l1 = StringFromKey("Morgan_256", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end_3";
			AddDialogExitQuestFunction("PQ5_Morgan_5");
		break;

		case "PL_Q5_end_3":
			dialog.text = StringFromKey("Morgan_257");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q5_end_3";
		break;

		case "PL_Q5_afterFight":
			dialog.text = StringFromKey("Morgan_258", GetMainCharacterNameDat());
			link.l1 = StringFromKey("Morgan_259", pchar);
			link.l1.go = "PL_Q5_afterFight_1";
			AddMoneyToCharacter(PChar, 35000);
		break;
		case "PL_Q5_afterFight_1":
			dialog.text = StringFromKey("Morgan_260");
			link.l1 = StringFromKey("Morgan_261");
			link.l1.go = "PL_Q5_afterFight_2";
		break;
		case "PL_Q5_afterFight_2":
			dialog.text = StringFromKey("Morgan_262", pchar);
			link.l1 = StringFromKey("Morgan_263", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "waiting_Q6";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			CloseQuestHeader("Pir_Line_5_Hunter");
			//сразу даем квест №6
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "1");
			CharacterDelAngry(CharacterFromID("Jackman"));
			//HardCoffee реф диалогов Джекмана
			pchar.QuestTemp.PirLine_quests_task = "Q6_GoToJackman";
			//QuestSetCurrentNode("Jackman", "PL_Q6"); //даем ноду Джекмену
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestMark_Main(CharacterFromID("Jackman"), "Pir_Line");
		break;
		//квест №7, охота на Соукинса
		/*case "PL_Q7_begin": //HardCoffee реф диалгов
			dialog.text = "А-а-а, вот и " + pchar.name + " " + GetSexPhrase("пожаловал", "пожаловала") +"! Значит, скоро начнутся проблемы.";
			link.l1 = "Генри, шутки шутками, но мне уже откровенно не до смеха.";
			link.l1.go = "PL_Q7_begin_1";
			CloseQuestHeader("Pir_Line_6_Jackman");
		break;*/
		case "PL_Q7_begin_1":
			DeleteAttribute(pchar, "QuestTemp.PirLine_quests_task");
			dialog.text = StringFromKey("Morgan_264", pchar);
			link.l1 = StringFromKey("Morgan_265");
			link.l1.go = "PL_Q7_begin_2";
			CloseQuestHeader("Pir_Line_6_Jackman");
		break;
		case "PL_Q7_begin_2":
			dialog.text = StringFromKey("Morgan_266");
			link.l1 = StringFromKey("Morgan_267");
			link.l1.go = "PL_Q7_begin_3";
		break;
		case "PL_Q7_begin_3":
			dialog.text = StringFromKey("Morgan_268");
			link.l1 = StringFromKey("Morgan_269");
			link.l1.go = "PL_Q7_begin_4";
		break;
		case "PL_Q7_begin_4":
			dialog.text = StringFromKey("Morgan_270", pchar);
			link.l1 = StringFromKey("Morgan_271", pchar);
			link.l1.go = "exit";
			SetQuestHeader("Pir_Line_7_Soukins");
			AddQuestRecord("Pir_Line_7_Soukins", "1");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toLaVega";
			SetLocationCapturedState("LaVega_town", false);
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestMark_Main(CharacterFromID("LaVega_tavernkeeper"), "Pir_Line");
		break;

		/*case "PL_Q7_LaVegaLate": //HardCoffee реф диалогов
			dialog.text = "О-о, опять "+ GetSexPhrase("наш герой","наша героиня") +" " + GetSexPhrase("явился", "явилась") +". Ну, что " + GetSexPhrase("узнал", "узнала") +"?";
			link.l1 = "Ты знаешь, я не " + GetSexPhrase("нашёл", "нашла") +" Стива Линнея в Ла-Веге.";
			link.l1.go = "PL_Q7_LaVegaLate_1";
		break;*/
		case "PL_Q7_AboutLiney":
			DeleteAttribute(pchar, "QuestTemp.PirLine_quests_task");
			dialog.text = StringFromKey("Morgan_272", pchar);
			if ("Soukins_LaVegaLate" == pchar.questTemp.piratesLine)
			{
				link.l1 = StringFromKey("Morgan_273", pchar);
				link.l1.go = "PL_Q7_LaVegaLate_1";
			}
			else if (pchar.questTemp.piratesLine == "Soukins_seekLeon" || pchar.questTemp.piratesLine == "Soukins_LeonNotFound")
			{
				link.l1 = StringFromKey("Morgan_274");
				link.l1.go = "PL_Q7_LeonNotFound_1";
			}
			else if ("Soukins_toMorgan" == pchar.questTemp.piratesLine)
			{
				link.l1 = StringFromKey("Morgan_275", pchar);
				link.l1.go = "PL_Q7_afterLeon_1";
			}
		break;
		case "PL_Q7_LaVegaLate_1":
			dialog.text = StringFromKey("Morgan_276", pchar);
			link.l1 = StringFromKey("Morgan_277");
			link.l1.go = "PL_Q7_LaVegaLate_2";
		break;
		case "PL_Q7_LaVegaLate_2":
			dialog.text = StringFromKey("Morgan_278");
			link.l1 = StringFromKey("Morgan_279");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_7_Soukins", "4");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toSantoDomingo";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestMark_Main(CharacterFromID("SantoDomingo_shipyarder"), "Pir_Line");
		break;

		/*case "PL_Q7_LeonNotFound": //HardCoffee реф диалогов
			dialog.text = "О-о, опять "+ GetSexPhrase("наш герой","наша героиня") +" " + GetSexPhrase("явился", "явилась") +". Ну, что " + GetSexPhrase("узнал", "узнала") +"?";
			link.l1 = "Генри, Стив Линней пропал без вести.";
			link.l1.go = "PL_Q7_LeonNotFound_1";
		break;*/
		case "PL_Q7_LeonNotFound_1":
			dialog.text = StringFromKey("Morgan_280");
			link.l1 = StringFromKey("Morgan_281");
			link.l1.go = "PL_Q7_LeonNotFound_2";
		break;
		case "PL_Q7_LeonNotFound_2":
			dialog.text = StringFromKey("Morgan_282");
			link.l1 = StringFromKey("Morgan_283");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, -3);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
			AddLandQuestmark_Main_WithCondition(npchar, "Pir_Line", "PirLine_waiting_Q8_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Pir_Line", "PirLine_waiting_Q8_WDMQuestMarkCondition");
		break;

		/*case "PL_Q7_afterLeon": //HardCoffee ref dialogue
			dialog.text = "А-а, рад тебя видеть. Что нового расскажешь?";
			link.l1 = "К сожалению, Стив Линней мёртв. Его убили пираты с фрегата 'Леон'. Но с ними я уже " + GetSexPhrase("рассчитался", "рассчиталась") +".";
			link.l1.go = "PL_Q7_afterLeon_1";
		break;*/
		case "PL_Q7_afterLeon_1":
			dialog.text = StringFromKey("Morgan_284");
			link.l1 = StringFromKey("Morgan_285");
			link.l1.go = "PL_Q7_afterLeon_2";
		break;
		case "PL_Q7_afterLeon_2":
			dialog.text = StringFromKey("Morgan_286");
			link.l1 = StringFromKey("Morgan_287");
			link.l1.go = "PL_Q7_afterLeon_3";
		break;
		case "PL_Q7_afterLeon_3":
			dialog.text = StringFromKey("Morgan_288");
			link.l1 = StringFromKey("Morgan_289");
			link.l1.go = "PL_Q7_afterLeon_4";
		break;
		case "PL_Q7_afterLeon_4":
			dialog.text = StringFromKey("Morgan_290");
			link.l1 = StringFromKey("Morgan_291");
			link.l1.go = "PL_Q7_afterLeon_5";
		break;
		case "PL_Q7_afterLeon_5":
			dialog.text = StringFromKey("Morgan_292");
			link.l1 = StringFromKey("Morgan_293");
			link.l1.go = "PL_Q7_afterLeon_6";
		break;
		case "PL_Q7_afterLeon_6":
			dialog.text = StringFromKey("Morgan_294");
			link.l1 = StringFromKey("Morgan_295");
			link.l1.go = "PL_Q7_afterLeon_7";
		break;
		case "PL_Q7_afterLeon_7":
			dialog.text = StringFromKey("Morgan_296", pchar);
			link.l1 = StringFromKey("Morgan_297");
			link.l1.go = "PL_Q7_afterLeon_8";
		break;
		case "PL_Q7_afterLeon_8":
			dialog.text = StringFromKey("Morgan_298");
			link.l1 = StringFromKey("Morgan_299");
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_7_Soukins", "8");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Soukins_toPuertoPrincipe";
			sld = ItemsFromID("OpenBook");
			sld.shown = true;
			sld = ItemsFromID("Ladder");
			sld.shown = true;
			sld.startLocation = "PuertoPrincipe_town";
			sld.startLocator = "item1";
			sld.useLocation = "PuertoPrincipe_town";
			sld.useLocator = "button01";
			//прерывание на вход в резиденцию, не дать осмотреться геймеру
			Pchar.quest.PQ7_inSoukinsResidence.win_condition.l1 = "location";
			Pchar.quest.PQ7_inSoukinsResidence.win_condition.l1.location = "PuertoPrincipe_townhall";
			Pchar.quest.PQ7_inSoukinsResidence.function = "PQ7_inSoukinsResidence";

			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddLandQuestMark_Main(CharacterFromID("PuertoPrincipe_tavernkeeper"), "Pir_Line");
			AddLandQuestMark_Main(CharacterFromID("PuertoPrincipe_waitress"), "Pir_Line");
		break;
		/*case "PL_Q7_BadWork": //HardCoffee ref dialogue
			dialog.text = "Ну, как дела? " + GetSexPhrase("Сумел", "Сумела") +" помешать Соукинсу?";
			link.l1 = "К сожалению, нет, Генри...";
			link.l1.go = "PL_Q7_BadWork_1";
		break;*/
		case "PL_Q7_BadWork_1":
			DeleteAttribute(pchar, "QuestTemp.PirLine_quests_task");
			dialog.text = StringFromKey("Morgan_300");
			link.l1 = StringFromKey("Morgan_301", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, -10);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
			AddLandQuestmark_Main_WithCondition(npchar, "Pir_Line", "PirLine_waiting_Q8_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Pir_Line", "PirLine_waiting_Q8_WDMQuestMarkCondition");
			sld = ItemsFromID("OpenBook");
			QuestPointerDelLoc(sld.startLocation, "item", sld.startLocator); // уберем указатель на всякий
		break;
		/*case "PL_Q7_GoodWork"://HardCoffee ref dialogue
			dialog.text = "Ну, как дела? " + GetSexPhrase("Сумел", "Сумела") +" помешать Соукинсу?";
			link.l1 = "Да, всё " + GetSexPhrase("сделал", "сделала") +", как и планировали.";
			link.l1.go = "PL_Q7_GoodWork_1";
		break;*/
		case "PL_Q7_GoodWork_1":
			DeleteAttribute(pchar, "QuestTemp.PirLine_quests_task");
			dialog.text = StringFromKey("Morgan_302");
			link.l1 = StringFromKey("Morgan_303");
			link.l1.go = "PL_Q7_GoodWork_2";
		break;
		case "PL_Q7_GoodWork_2":
			dialog.text = StringFromKey("Morgan_304");
			link.l1 = StringFromKey("Morgan_305");
			link.l1.go = "PL_Q7_GoodWork_3";
		break;
		case "PL_Q7_GoodWork_3":
			dialog.text = StringFromKey("Morgan_306", pchar, GetFullName(PChar));
			link.l1 = StringFromKey("Morgan_307", pchar);
			link.l1.go = "PL_Q7_GoodWork_4";
		break;
		case "PL_Q7_GoodWork_4":
			dialog.text = StringFromKey("Morgan_308", pchar);
			link.l1 = StringFromKey("Morgan_309", pchar);
			link.l1.go = "PL_Q7_GoodWork_5";
		break;
		case "PL_Q7_GoodWork_5":
			dialog.text = StringFromKey("Morgan_310");
			link.l1 = StringFromKey("Morgan_311", pchar);
			link.l1.go = "PL_Q7_GoodWork_6";
			RemoveItems(PChar, "OpenBook", 1);
		break;
		case "PL_Q7_GoodWork_6":
			dialog.text = StringFromKey("Morgan_312");
			link.l1 = StringFromKey("Morgan_313");
			link.l1.go = "PL_Q7_GoodWork_7";
		break;
		case "PL_Q7_GoodWork_7":
			dialog.text = StringFromKey("Morgan_314");
			link.l1 = StringFromKey("Morgan_315");
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			CloseQuestHeader("Pir_Line_7_Soukins");
			ChangeCharacterReputation(pchar, 10);
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "waiting_Q8";
			AddLandQuestmark_Main_WithCondition(npchar, "Pir_Line", "PirLine_waiting_Q8_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Pir_Line", "PirLine_waiting_Q8_WDMQuestMarkCondition");
		break;
		//квест №8, штурм Панамы
		case "PL_Q8_1":
			if (pchar.questTemp.State == "" || pchar.questTemp.State == "EndOfQuestLine")
			{
				dialog.text = StringFromKey("Morgan_316");
				link.l1 = StringFromKey("Morgan_317");
				link.l1.go = "PL_Q8_2";
				pchar.questTemp.State = "EndOfQuestLine"; //если геймер ещё не брал нац.линейку, то и не даем её после штурма Панамы
				bWorldAlivePause = false; // Конец линейки
			}
			else
			{
				dialog.text = StringFromKey("Morgan_318", pchar, NationNamePeopleAcc(sti(pchar.questTemp.NationQuest)));
				link.l1 = StringFromKey("Morgan_319");
				link.l1.go = "exitAgr";
				RemoveLandQuestmark_Main(npchar, "Pir_Line");
				RemoveMapQuestMark("PortRoyal_town", "Pir_Line");
			}
		break;
		case "PL_Q8_2":
			dialog.text = StringFromKey("Morgan_320");
			link.l1 = StringFromKey("Morgan_321");
			link.l1.go = "PL_Q8_3";
		break;
		case "PL_Q8_3":
			dialog.text = StringFromKey("Morgan_322", pchar);
			link.l1 = StringFromKey("Morgan_323");
			link.l1.go = "PL_Q8_4";
		break;
		case "PL_Q8_4":
			dialog.text = StringFromKey("Morgan_324");
			link.l1 = StringFromKey("Morgan_325", pchar);
			link.l1.go = "PL_Q8_5";
		break;
		case "PL_Q8_5":
			dialog.text = StringFromKey("Morgan_326", pchar, GetFullName(PChar));
			link.l1 = StringFromKey("Morgan_327");
			link.l1.go = "PL_Q8_6";
		break;
		case "PL_Q8_6":
			dialog.text = StringFromKey("Morgan_328");
			link.l1 = StringFromKey("Morgan_329");
			link.l1.go = "PL_Q8_7";
		break;
		case "PL_Q8_7":
			dialog.text = StringFromKey("Morgan_330");
			link.l1 = StringFromKey("Morgan_331");
			link.l1.go = "PL_Q8_8";
		break;
		case "PL_Q8_8":
			dialog.text = StringFromKey("Morgan_332");
			link.l1 = StringFromKey("Morgan_333", pchar);
			link.l1.go = "PL_Q8_9";
		break;
		case "PL_Q8_9":
			dialog.text = StringFromKey("Morgan_334", pchar);
			link.l1 = StringFromKey("Morgan_335");
			link.l1.go = "PL_Q8_10";
		break;
		case "PL_Q8_10":
			dialog.text = StringFromKey("Morgan_336");
			link.l1 = StringFromKey("Morgan_337");
			link.l1.go = "PL_Q8_11";
		break;
		case "PL_Q8_11":
			dialog.text = StringFromKey("Morgan_338");
			link.l1 = StringFromKey("Morgan_339");
			link.l1.go = "PL_Q8_12";
		break;
		case "PL_Q8_12":
			dialog.text = StringFromKey("Morgan_340", pchar);
			link.l1 = StringFromKey("Morgan_341");
			link.l1.go = "PL_Q8_13";
		break;
		case "PL_Q8_13":
			dialog.text = StringFromKey("Morgan_342");
			link.l1 = StringFromKey("Morgan_343", pchar);
			link.l1.go = "PL_Q8_14";
		break;
		case "PL_Q8_14":
			dialog.text = StringFromKey("Morgan_344", pchar);
			link.l1 = StringFromKey("Morgan_345");
			link.l1.go = "PL_Q8_15";
		break;
		case "PL_Q8_15":
			dialog.text = StringFromKey("Morgan_346");
			link.l1 = StringFromKey("Morgan_347");
			link.l1.go = "PL_Q8_16";
		break;
		case "PL_Q8_16":
			dialog.text = StringFromKey("Morgan_348");
			link.l1 = StringFromKey("Morgan_349", pchar);
			link.l1.go = "exit";
			AddQuestRecord("Pir_Line_8_Panama", "1");
			NextDiag.TempNode = "I_know_you_good";
			pchar.questTemp.piratesLine = "Panama_toReady";
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			SetTimerFunction("PQ8_timeOver", 0, 0, 35);
			LocatorReloadEnterDisable("Shore48", "reload1_back", true); //закрывем подходы к Панаме
			LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", true);
			AddLandQuestmark_Main_WithCondition(npchar, "Pir_Line", "PirLine_PanamaToReady_QuestMarkCondition");
			AddMapQuestMark_Major("PortRoyal_town", "Pir_Line", "PirLine_PanamaToReady_WDMQuestMarkCondition");
		break;

		/*case "PL_Q8_ready": //HardCoffee ref dialog
			if (GetQuestPastDayParam("questTemp.piratesLine") > 20)
			{
				dialog.text = "Ага, вот и ты " + GetSexPhrase("пришёл", "пришла") +"! Это хорошо, так как время пришло. Я так понимаю, что ты " + GetSexPhrase("готов", "готова") +"?";
				link.l1 = "Да, адмирал. В полной боевой готовности.";
				link.l1.go = "PL_Q8_ready_1";
			}
			else
			{
				dialog.text = "Зачем " + GetSexPhrase("явился", "явилась") +"? Через 20 дней, я же сказал тебе!";
				link.l1 = "Да, я помню. Просто " + GetSexPhrase("хотел", "хотела") +" увидеть...";
				link.l1.go = "PL_Q8_NotReady1";
			}
		break;
		case "PL_Q8_NotReady1":
			dialog.text = "Послушай, " + PChar.name + ", я же тебе ясно сказал, чтобы ты " + GetSexPhrase("приходил", "приходила") +" с одним кораблём. Тебе нужно делать лишь то, что я говорю. Что тут непонятного?!";
			link.l1 = "Всё ясно, адмирал, сейчас исправим.";
			link.l1.go = "exit";
		break;*/
		case "PL_Q8_ready_1":
			if (GetCompanionQuantity(pchar) == 1)
			{
				dialog.text = StringFromKey("Morgan_350");
				link.l1 = StringFromKey("Morgan_351");
				link.l1.go = "PL_Q8_ready_2";
			}
			else
			{
				dialog.text = StringFromKey("Morgan_352", pchar, pchar.name);
				link.l1 = StringFromKey("Morgan_353");
				link.l1.go = "exit";
			}
		break;
		case "PL_Q8_ready_2":
			dialog.text = StringFromKey("Morgan_354", GetFullName(PChar));
			link.l1 = StringFromKey("Morgan_355");
			link.l1.go = "PL_Q8_ready_3";
		break;
		case "PL_Q8_ready_3":
			dialog.text = StringFromKey("Morgan_356");
			link.l1 = StringFromKey("Morgan_357", pchar);
			link.l1.go = "PL_Q8_ready_4";
		break;
		case "PL_Q8_ready_4":
			pchar.quest.PQ8_timeOver.over = "yes"; //снимаем таймер 
			SetTimerFunction("PQ8_PanamaTimerOver", 0, 0, 20); //ставим новый таймер
			pchar.Quest.PQ8_EnterPortoBello.win_condition.l1 = "location";
			pchar.Quest.PQ8_EnterPortoBello.win_condition.l1.location = "PortoBello";
			pchar.Quest.PQ8_EnterPortoBello.function = "PQ8_EnterPortoBello";
			pchar.questTemp.piratesLine = "Panama_toPortoBello";
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			AddQuestRecord("Pir_Line_8_Panama", "4");
			AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("ен", "на"));
			pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
			characters[GetCharacterIndex("PortoBello_Mayor")].dialog.captureNode = "PQ8_MayorPortoBello"; //капитулянтская нода мэра
			//Морган
			FantomMakeCoolSailor(npchar, SHIP_FRIGATE_M, FindPersonalName("Henry_Morgan_ship"), CANNON_TYPE_CANNON_LBS42, 90, 100, 100);
			pchar.nation = PIRATE;
			LAi_SetActorType(NPChar);
			LAi_ActorSetStayMode(NPChar);
			//LAi_SetImmortal(NPChar, false);
			NPChar.Ship.Cargo.Goods.Food = 1000;
			LAi_NoRebirthDisable(NPChar);
			LAi_RebirthOldName(NPChar);
			npchar.DeckDialogNode = "PL_Q8_deck"; //ноду на палубу
			ChangeCharacterAddressGroup(NPChar, "PortRoyal_houseS1", "goto", "goto7");
			CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 8.5, false);
			npchar.CompanionEnemyEnable = false;  // нет отпора при обстреле
			SetCharacterRemovable(npchar, false);
			//Джекмен
			sld = characterFromId("Jackman");
			FantomMakeCoolSailor(sld, SHIP_WARSHIP, FindPersonalName("Jackman_ship2"), CANNON_TYPE_CULVERINE_LBS32, 95, 95, 100);
			sld.CompanionEnemyEnable = false;  // нет отпора при обстреле
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 1000;
			LAi_SetImmortal(sld, false);
			LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			SetCompanionIndex(pchar, -1, sti(sld.index));
			//Джон Моррис
			if (GetCharacterIndex("John Morris") == -1)
			{
				sld = GetCharacter(NPC_GenerateCharacter("John Morris", "John_Morris", "man", "man", 38, PIRATE, -1, false));
				sld.name = FindPersonalName("JohnMorris_name");
				sld.lastname = FindPersonalName("JohnMorris_lastname");
				sld.Dialog.Filename = "Quest\JohnMorris.c";
				sld.greeting = "Gr_HeadPirates";
				FantomMakeCoolFighter(sld, 35, 90, 50, BLADE_LONG, "pistol4", 150);
				LAi_SetStayType(sld);
				LAi_SetLoginTime(sld, 0.0, 24.0);
				LAi_SetHP(sld, 180.0, 180.0);
			}
			else
			{
				sld = characterFromId("John Morris");
			}
			FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, FindPersonalName("JohnMorris_ship"), CANNON_TYPE_CANNON_LBS32, 100, 100, 95);
			sld.CompanionEnemyEnable = false;  // нет отпора при обстреле
			LAi_SetImmortal(sld, false);
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 1000;
			LAi_NoRebirthDisable(sld);
			LAi_RebirthOldName(sld);
			sld.RebirthPhantom = true; //не тереть фантома после смерти.  
			sld.DeckDialogNode = "PL_Q8_deck"; //ноду на палубу
			SetCompanionIndex(pchar, -1, sti(sld.index));
			//Ричард Соукинс
			sld = characterFromId("Richard_Soukins");
			FantomMakeCoolSailor(sld, SHIP_LINESHIP, FindPersonalName("Richard_Soukins_ship"), CANNON_TYPE_CULVERINE_LBS32, 90, 85, 95);
			sld.CompanionEnemyEnable = false;  // нет отпора при обстреле
			SetCharacterRemovable(sld, false);
			sld.Ship.Cargo.Goods.Food = 2500;
			LAi_SetImmortal(sld, true);
			LAi_NoRebirthEnable(sld);
			LAi_RemoveLoginTime(sld);
			sld.DeckDialogNode = "PL_Q8_deck"; //ноду на палубу
			SetCompanionIndex(pchar, -1, sti(sld.index));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "PL_Q8_timeOver":
			dialog.text = StringFromKey("Morgan_358");
			link.l1 = StringFromKey("Morgan_359");
			link.l1.go = "PL_Q8_timeOver_1";
			// выход с палубы
			pchar.quest.Munity = "Deads";
			LAi_LockFightMode(Pchar, false);
		break;
		case "PL_Q8_timeOver_1":
			dialog.text = StringFromKey("Morgan_360");
			link.l1 = StringFromKey("Morgan_361");
			link.l1.go = "PL_Q8_timeOver_2";
		break;
		case "PL_Q8_timeOver_2":
			dialog.text = StringFromKey("Morgan_362", pchar);
			link.l1 = StringFromKey("Morgan_363");
			link.l1.go = "PL_Q8_timeOver_3";
		break;
		case "PL_Q8_timeOver_3":
			SetTimerFunction("PQ8_openPanama", 0, 0, 40);
			LocatorReloadEnterDisable("Shore48", "reload1_back", true); //закрывем подходы к Панаме
			LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", true);
			pchar.questTemp.piratesLine = "over";
			AddQuestRecord("Pir_Line_8_Panama", "3");
			AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("Pir_Line_8_Panama");
			//возвращаем Моргана
			if (IsCompanion(npchar))  RemoveCharacterCompanion(pchar, npchar);
			//Возвращаем на место Джекмена
			iTemp = GetCharacterIndex("Jackman");
			if (iTemp != -1)
			{
				if (IsCompanion(&characters[iTemp]))
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}
				LAi_SetHuberType(&characters[iTemp]);
				LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
				ChangeCharacterAddressGroup(&characters[iTemp], "Pirates_townhall", "sit", "sit1");
				characters[iTemp].dialog.currentnode = "First time";
			}
			//Возвращаем на место Джона Морриса
			iTemp = GetCharacterIndex("John Morris");
			if (iTemp != -1)
			{
				if (IsCompanion(&characters[iTemp]))
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}
				if (CheckAttribute(&TEV, "JohnMorrisIsLifeInHouse"))
				{
					LAi_SetHuberType(characterfromID("John Morris"));
					LAi_group_MoveCharacter(&characters[iTemp], "ENGLAND_CITIZENS");
					ChangeCharacterAddressGroup(&characters[iTemp], "PortSpein_houseF2", "sit", "sit1");
					characters[iTemp].dialog.currentnode = "I_know_you_good";
				}
				else
				{
					sld = &characters[iTemp];
					sld.lifeDay = 0;
				}

			}
			//Возвращаем на место Соукинса
			iTemp = GetCharacterIndex("Richard_Soukins");
			if (iTemp != -1)
			{
				if (IsCompanion(&characters[iTemp]))
				{
					RemoveCharacterCompanion(pchar, &characters[iTemp]);
				}
				LAi_SetHuberType(&characters[iTemp]);
				LAi_group_MoveCharacter(&characters[iTemp], "PIRATE_CITIZENS");
				ChangeCharacterAddressGroup(&characters[iTemp], "PuertoPrincipe_townhall", "sit", "sit1");
				characters[iTemp].dialog.currentnode = "First time";
			}
			NextDiag.TempNode = "PL_Q8_timeOver_exit";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_timeOver_exit":
			dialog.text = StringFromKey("Morgan_364");
			link.l1 = "...";
			link.l1.go = "PL_Q8_timeOver_exit";
		break;
		//в резиденции взятого Портобело
		case "PL_Q8_PBResidence":
			dialog.text = StringFromKey("Morgan_365", pchar);
			link.l1 = StringFromKey("Morgan_366");
			link.l1.go = "PL_Q8_PBResidence_1";
		break;
		case "PL_Q8_PBResidence_1":
			dialog.text = StringFromKey("Morgan_367");
			link.l1 = StringFromKey("Morgan_368");
			link.l1.go = "PL_Q8_PBResidence_2";
		break;
		case "PL_Q8_PBResidence_2":
			dialog.text = StringFromKey("Morgan_369");
			link.l1 = StringFromKey("Morgan_370");
			link.l1.go = "PL_Q8_PBResidence_3";
		break;
		case "PL_Q8_PBResidence_3":
			dialog.text = StringFromKey("Morgan_371");
			link.l1 = StringFromKey("Morgan_372");
			link.l1.go = "PL_Q8_PBResidence_4";
		break;
		case "PL_Q8_PBResidence_4":
			dialog.text = StringFromKey("Morgan_373", pchar.name);
			link.l1 = StringFromKey("Morgan_374", pchar);
			link.l1.go = "PL_Q8_PBResidence_5";
		break;
		case "PL_Q8_PBResidence_5":
			dialog.text = StringFromKey("Morgan_375");
			link.l1 = StringFromKey("Morgan_376");
			link.l1.go = "PL_Q8_PBResidence_6";
		break;
		case "PL_Q8_PBResidence_6":
			dialog.text = StringFromKey("Morgan_377");
			link.l1 = StringFromKey("Morgan_378");
			link.l1.go = "PL_Q8_PBResidence_7";
		break;
		case "PL_Q8_PBResidence_7":
			if (pchar.location.from_sea == "Shore48")
			{
				dialog.text = StringFromKey("Morgan_379", pchar);
				link.l1 = StringFromKey("Morgan_380", pchar);
				link.l1.go = "PL_Q8_PBResidence_8";
			}
			else
			{
				dialog.text = StringFromKey("Morgan_381");
				link.l1 = StringFromKey("Morgan_382", pchar);
				link.l1.go = "PL_Q8_PBResidence_8";
			}
		break;
		case "PL_Q8_PBResidence_8":
			dialog.text = StringFromKey("Morgan_383");
			link.l1 = StringFromKey("Morgan_384");
			link.l1.go = "PL_Q8_PBResidence_9";
		break;
		case "PL_Q8_PBResidence_9":
			dialog.text = StringFromKey("Morgan_385");
			link.l1 = StringFromKey("Morgan_386");
			link.l1.go = "PL_Q8_PBResidence_10";
		break;
		case "PL_Q8_PBResidence_10":
			dialog.text = StringFromKey("Morgan_387");
			link.l1 = StringFromKey("Morgan_388", pchar);
			link.l1.go = "PL_Q8_PBResidence_11";
		break;
		case "PL_Q8_PBResidence_11":
			dialog.text = StringFromKey("Morgan_389", PChar.name);
			link.l1 = StringFromKey("Morgan_390");
			link.l1.go = "PL_Q8_PBResidence_12";
		break;
		case "PL_Q8_PBResidence_12":
			dialog.text = StringFromKey("Morgan_391");
			link.l1 = StringFromKey("Morgan_392");
			link.l1.go = "PL_Q8_PBResidence_13";
		break;
		case "PL_Q8_PBResidence_13":
			dialog.text = StringFromKey("Morgan_393", pchar);
			link.l1 = StringFromKey("Morgan_394");
			link.l1.go = "PL_Q8_PBResidence_14";
		break;
		case "PL_Q8_PBResidence_14":
			LAi_SetWarriorTypeNoGroup(npchar);
			chrDisableReloadToLocation = false;
			//bQuestDisableMapEnter = false;
			LocatorReloadEnterDisable("Shore48", "reload1_back", false); //открываем проход в джанглы через бухту
			Pchar.quest.PQ8_PBExitResidence.win_condition.l1 = "ExitFromLocation";
			Pchar.quest.PQ8_PBExitResidence.win_condition.l1.location = pchar.location;
			Pchar.quest.PQ8_PBExitResidence.function = "PQ8_PBExitResidence";
			NextDiag.TempNode = "PL_Q8_PBResidence_over";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_PBResidence_over":
			dialog.text = StringFromKey("Morgan_395");
			link.l1 = StringFromKey("Morgan_396", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "PL_Q8_PBResidence_over";
		break;
		//у ворот Панамы
		case "PL_Q8_ExTPanama":
			iTemp = GetCharacterIndex("Richard_Soukins");

			if (PChar.QuestTemp.piratesLine == "Panama_RichardBadWork")
			{
				if (LAi_IsDead(&Characters[iTemp]))
				{
					dialog.text = StringFromKey("Morgan_397", pchar);
					link.l1 = StringFromKey("Morgan_398");
					link.l1.go = "PL_Q8_ExTPanama_1";
				}
				else
				{
					dialog.text = StringFromKey("Morgan_399", pchar);
					link.l1 = StringFromKey("Morgan_400", pchar);
					link.l1.go = "PL_Q8_ExTPanama_7_Soukins";
				}
			}
			else
			{
				dialog.text = StringFromKey("Morgan_401", pchar, PChar.name);
				link.l1 = StringFromKey("Morgan_402", pchar);
				link.l1.go = "PL_Q8_ExTPanama_1";
			}
		break;
		case "PL_Q8_ExTPanama_1":
			dialog.text = StringFromKey("Morgan_403");
			link.l1 = StringFromKey("Morgan_404");
			link.l1.go = "PL_Q8_ExTPanama_2";
			CreateJohnCoxon(); //Тело нашли и опознали, сажаем на место Соункинса нового губернатора
		break;
		case "PL_Q8_ExTPanama_2":
			dialog.text = StringFromKey("Morgan_405", pchar);
			link.l1 = StringFromKey("Morgan_406");
			link.l1.go = "PL_Q8_ExTPanama_3";
		break;
		case "PL_Q8_ExTPanama_3":
			dialog.text = StringFromKey("Morgan_407");
			link.l1 = StringFromKey("Morgan_408");
			link.l1.go = "PL_Q8_ExTPanama_4";
		break;
		case "PL_Q8_ExTPanama_4":
			dialog.text = StringFromKey("Morgan_409");
			link.l1 = StringFromKey("Morgan_410");
			link.l1.go = "PL_Q8_ExTPanama_5";
		break;
		case "PL_Q8_ExTPanama_5":
			dialog.text = StringFromKey("Morgan_411");
			link.l1 = StringFromKey("Morgan_412");
			link.l1.go = "PL_Q8_ExTPanama_6";
		break;
		case "PL_Q8_ExTPanama_6":
			dialog.text = StringFromKey("Morgan_413");
			link.l1 = StringFromKey("Morgan_414");
			link.l1.go = "PL_Q8_ExTPanama_7";
		break;
		case "PL_Q8_ExTPanama_7":
			AddQuestRecord("Pir_Line_8_Panama", "9");
			//characters[GetCharacterIndex("Panama_Mayor")].dialog.captureNode = "PQ8_afterAttack"; //капитулянтская нода мэра
			pchar.quest.PQ8_piratesInPanama.win_condition.l1 = "location";
			pchar.quest.PQ8_piratesInPanama.win_condition.l1.location = "Panama_town";
			pchar.quest.PQ8_piratesInPanama.function = "PQ8_piratesInPanama";
			NextDiag.TempNode = "PL_Q8_ExTPanama_over";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "PL_Q8_ExTPanama_over":
			dialog.text = StringFromKey("Morgan_415");
			link.l1 = StringFromKey("Morgan_416", pchar);
			link.l1.go = "exit";
		break;
		case "PL_Q8_ExTPanama_7_Soukins":
			dialog.text = StringFromKey("Morgan_417");
			link.l1 = StringFromKey("Morgan_418");
			link.l1.go = "PL_Q8_ExTPanama_8_Soukins";
		break;
		case "PL_Q8_ExTPanama_8_Soukins":
			dialog.text = StringFromKey("Morgan_419", pchar);
			link.l1 = StringFromKey("Morgan_420");
			link.l1.go = "PL_Q8_ExTPanama_9_Soukins";
		break;
		case "PL_Q8_ExTPanama_9_Soukins":
			QuestSetCurrentNode("Richard_Soukins", "PQ8_exitTown");
			AddQuestRecord("Pir_Line_8_Panama", "10");
			CloseQuestHeader("Pir_Line_8_Panama");
			LocatorReloadEnterDisable("Panama_ExitTown", "reload4", true); //закроем вход в город
			SetTimerFunction("PQ8_openPanama_2", 0, 0, 30); //таймер на открыть всё потом.
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload4", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//в Панаме после выхода ГГ из резиденции
		case "PL_Q8_Panama1":
			dialog.text = StringFromKey("Morgan_421", pchar);
			link.l1 = StringFromKey("Morgan_422", pchar);
			link.l1.go = "PL_Q8_Panama1_1";
		break;
		case "PL_Q8_Panama1_1":
			dialog.text = StringFromKey("Morgan_423");
			link.l1 = StringFromKey("Morgan_424");
			link.l1.go = "PL_Q8_Panama1_2";
		break;
		case "PL_Q8_Panama1_2":
			dialog.text = StringFromKey("Morgan_425");
			link.l1 = StringFromKey("Morgan_426");
			link.l1.go = "PL_Q8_Panama1_3";
		break;
		case "PL_Q8_Panama1_3":
			dialog.text = StringFromKey("Morgan_427");
			link.l1 = StringFromKey("Morgan_428");
			link.l1.go = "PL_Q8_Panama1_4";
		break;
		case "PL_Q8_Panama1_4":
			sld = characterFromId("FantomMayor");
			sld.lifeDay = 0;
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1 = "locator";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.location = "Panama_TownhallRoom";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator_group = "box";
			pchar.quest.PL_Q8_ResEnterBox.win_condition.l1.locator = "private1";
			pchar.quest.PL_Q8_ResEnterBox.function = "PL_Q8_ResEnterBox";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload3", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//в резиденции Панамы с ключом
		case "PL_Q8_Panama2":
			npchar.quest.locInd = FindLocation(pchar.location);
			sld = &locations[sti(npchar.quest.locInd)];
			if (CheckAttribute(sld, "private1.money")) sld.private1.money = 0;
			if (CheckAttribute(sld, "private2.money")) sld.private2.money = 0;
			dialog.text = StringFromKey("Morgan_429", pchar);
			link.l1 = StringFromKey("Morgan_430", pchar);
			link.l1.go = "PL_Q8_Panama2_1";
		break;
		case "PL_Q8_Panama2_1":
			dialog.text = StringFromKey("Morgan_431");
			link.l1 = StringFromKey("Morgan_432");
			link.l1.go = "PL_Q8_Panama2_2";
		break;
		case "PL_Q8_Panama2_2":
			string sDialogText, sLinkL1, sLinkL1Go;
			dialog.text = StringFromKey("Morgan_433", PChar.name);
			link.l1 = StringFromKey("Morgan_434");
			link.l1.go = "PL_Q8_Panama2_3";
		break;
		case "PL_Q8_Panama2_3":
			sld = &locations[sti(npchar.quest.locInd)];
			int iMoneyForMorgan = 50000000;
			if (CheckAttribute(sld, "private1.items.gold") || sti(pchar.money) >= iMoneyForMorgan)
			{
				//Пасхалка, заставить Моргана делиться при высоком Восприятии и Обучаемости
				//                if ((GetCharacterSPECIAL(pchar, SPECIAL_P) + GetCharacterSPECIAL(pchar, SPECIAL_I)) >= 10)
				if (PlayerRPGCheck_SPECIAL_Sum(SPECIAL_P + "," + SPECIAL_I, 10))
				{
					dialog.text = StringFromKey("Morgan_435", pchar);
					link.l1 = StringFromKey("Morgan_436", pchar);
					link.l1.go = "PL_Q8_Panama2_4_2";
					iMoneyForMorgan = 47500000;
					AddQuestRecord("Pir_Line_8_Panama", "13");
				}
				else
				{
					dialog.text = StringFromKey("Morgan_437");
					link.l1 = StringFromKey("Morgan_438");
					link.l1.go = "PL_Q8_Panama2_4_1";
					AddQuestRecord("Pir_Line_8_Panama", "12");
				}
				AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("ёл", "ла"));
				AddQuestUserData("Pir_Line_8_Panama", "sSex1", GetSexPhrase("", "а"));
				if (CheckAttribute(sld, "private1.items.gold"))
				{
					AddMoneyToCharacter(pchar, sti(sld.private1.items.gold) - iMoneyForMorgan); //если договорился с Морганом, но из сундука золото не брал
					DeleteAttribute(sld, "private1.items.gold");
				}
				else AddMoneyToCharacter(pchar, -iMoneyForMorgan);
				SetBan("Exchange", 0);
			}
			else
			{
				LAi_SetStayTypeNoGroup(npchar);
				dialog.text = StringFromKey("Morgan_439", pchar.name);
				link.l1 = StringFromKey("Morgan_440");
				NextDiag.TempNode = "PL_Q8_Panama2_3";
				link.l1.go = "exit";
			}
		break;
		case "PL_Q8_Panama2_4_1":
			dialog.text = StringFromKey("Morgan_441", pchar);
			link.l1 = StringFromKey("Morgan_442");
			link.l1.go = "PL_Q8_Panama2_5";
		break;
		case "PL_Q8_Panama2_4_2":
			dialog.text = StringFromKey("Morgan_443", pchar);
			link.l1 = StringFromKey("Morgan_444");
			link.l1.go = "PL_Q8_Panama2_5";
		break;
		case "PL_Q8_Panama2_5":
			dialog.text = StringFromKey("Morgan_445");
			link.l1 = StringFromKey("Morgan_446");
			link.l1.go = "PL_Q8_Panama2_6";
		break;
		case "PL_Q8_Panama2_6":
			Pchar.quest.PL_Q8_inPanamaFort2.win_condition.l1 = "location";
			Pchar.quest.PL_Q8_inPanamaFort2.win_condition.l1.location = "Panama_Fort";
			Pchar.quest.PL_Q8_inPanamaFort2.function = "PL_Q8_inPanamaFort2";
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2", "none", "", "", "OpenTheDoors", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//Морган в Порт-Ройал
		case "PL_Q8_afterPanama":
			dialog.text = StringFromKey("Morgan_447", pchar.name);
			link.l1 = StringFromKey("Morgan_448", pchar);
			link.l1.go = "PL_Q8_afterPanama_1";
		break;
		case "PL_Q8_afterPanama_1":
			dialog.text = StringFromKey("Morgan_449", pchar);
			link.l1 = StringFromKey("Morgan_450", pchar);
			link.l1.go = "PL_Q8_afterPanama_2";
		break;
		case "PL_Q8_afterPanama_2":
			dialog.text = StringFromKey("Morgan_451");
			link.l1 = StringFromKey("Morgan_452");
			link.l1.go = "PL_Q8_afterPanama_3";
		break;
		case "PL_Q8_afterPanama_3":
			dialog.text = StringFromKey("Morgan_453", PChar.name);
			link.l1 = StringFromKey("Morgan_454");
			link.l1.go = "PL_Q8_afterPanama_4";
		break;
		case "PL_Q8_afterPanama_4":
			dialog.text = StringFromKey("Morgan_455");
			link.l1 = StringFromKey("Morgan_456");
			link.l1.go = "PL_Q8_afterPanama_5";
		break;
		case "PL_Q8_afterPanama_5":
			dialog.text = StringFromKey("Morgan_457");
			link.l1 = StringFromKey("Morgan_458");
			link.l1.go = "PL_Q8_afterPanama_6";
		break;
		case "PL_Q8_afterPanama_6":
			dialog.text = StringFromKey("Morgan_459", PChar.name);
			link.l1 = StringFromKey("Morgan_460");
			link.l1.go = "PL_Q8_afterPanama_7";
		break;
		case "PL_Q8_afterPanama_7":
			dialog.text = StringFromKey("Morgan_461", pchar);
			link.l1 = StringFromKey("Morgan_462");
			link.l1.go = "PL_Q8_afterPanama_8";
		break;
		case "PL_Q8_afterPanama_8":
			dialog.text = StringFromKey("Morgan_463", PChar.name);
			link.l1 = StringFromKey("Morgan_464", pchar, GetFullName(PChar));
			link.l1.go = "PL_Q8_afterPanama_9";
		break;
		case "PL_Q8_afterPanama_9":
			dialog.text = StringFromKey("Morgan_465", pchar);
			link.l1 = StringFromKey("Morgan_466");
			link.l1.go = "exit";
			NextDiag.TempNode = "Morgan_strife";
			pchar.questTemp.piratesLine = "over";
			AddQuestRecord("Pir_Line_8_Panama", "15");
			AddQuestUserData("Pir_Line_8_Panama", "sSex", GetSexPhrase("ся", "ась"));
			CloseQuestHeader("Pir_Line_8_Panama");
			RemoveLandQuestmark_Main(npchar, "Pir_Line");
			Achievment_Set(ACH_Ya_uedu_zhit_v_London);
		break;

		case "Morgan_strife":
			dialog.text = StringFromKey("Morgan_469", pchar, RandPhraseSimple(
						StringFromKey("Morgan_467", pchar),
						StringFromKey("Morgan_468")));
			link.l1 = StringFromKey("Morgan_470");
			link.l1.go = "exit";
			NextDiag.TempNode = "Morgan_strife";
		break;
		case "Andre_Abel_Quest_Morgan_Dialog_2":
			if (CheckAttribute(npchar, "quest.repeat")) DeleteAttribute(npchar, "quest.repeat");
			pchar.QuestTemp.AndreAbelQuest = true;
			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
			dialog.text = StringFromKey("Morgan_471");
			link.l1 = StringFromKey("Morgan_472");
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_3";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_3":
			dialog.text = StringFromKey("Morgan_473");
			link.l1 = StringFromKey("Morgan_474");
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_4";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_4":
			dialog.text = StringFromKey("Morgan_475");
			link.l1 = StringFromKey("Morgan_476");
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_5";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_5":
			dialog.text = StringFromKey("Morgan_477", GetFullName(pchar));

			link.l1 = StringFromKey("Morgan_478");
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_6";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_6":
			dialog.text = StringFromKey("Morgan_479", pchar);
			link.l1 = StringFromKey("Morgan_480");
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_9";
			link.l2 = StringFromKey("Morgan_481");
			link.l2.go = "Andre_Abel_Quest_Morgan_Dialog_7";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_7":
			dialog.text = StringFromKey("Morgan_482");
			link.l1 = StringFromKey("Morgan_483", pchar);
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_8";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("Andre_Abel_Quest", "12");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("ся", "ась"));
			ChangeCharacterAddressGroup(CharacterFromID("Andre_Abel"), "none", "", "");
			PChar.QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek = true; // Флаг для разговора с тавернщиком в Порт-о-Принсе
			AddLandQuestMark_Main(CharacterFromID("PortPax_tavernkeeper"), "Andre_Abel_Quest");
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_9":
			dialog.text = StringFromKey("Morgan_484");
			link.l1 = StringFromKey("Morgan_485");
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_10";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_10":
			DialogExit();
			NextDiag.TempNode = "I_know_you_good";
			NextDiag.CurrentNode = NextDiag.TempNode;
			Log_TestInfo("Получено письмо от Генри Моргана.");
			GiveItem2Character(PChar, "Andre_Abel_Letter_1");
			AddQuestRecord("Andre_Abel_Quest", "14");
			QuestSetCurrentNode("hol_guber", "Andre_Abel_Quest_Hol_Gov_Node_1");
			SetFunctionTimerCondition("Andre_Abel_Quest_Curasao_10Days_Left", 0, 0, 10, false);
			SetFunctionLocationCondition("Andre_Abel_Quest_In_Curacao_Townhall", "Villemstad_townhall2", false);

			AddLandQuestMark_Main(CharacterFromID("hol_guber"), "Andre_Abel_Quest");
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_11": //После возвращения от губернатора
			if (CheckAttribute(npchar, "quest.repeat")) DeleteAttribute(npchar, "quest.repeat");
			dialog.text = StringFromKey("Morgan_486", pchar);
			if ("GoTo_MorganPrison" == pchar.QuestTemp.AndreAbelQuest)
				link.l1 = StringFromKey("Morgan_487", pchar);
			else
				link.l1 = StringFromKey("Morgan_488", pchar);
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_12";
		break;
		case "Andre_Abel_Quest_Morgan_Dialog_12":
			if ("GoTo_MorganPrison" == pchar.QuestTemp.AndreAbelQuest)
				dialog.text = StringFromKey("Morgan_489");
			else
				dialog.text = StringFromKey("Morgan_490");
			dialog.text = StringFromKey("Morgan_491", dialog.text);
			if ("GoTo_MorganFight" == pchar.QuestTemp.AndreAbelQuest)
				link.l1 = StringFromKey("Morgan_492", pchar);
			else if ("GoTo_MorganMoney" == pchar.QuestTemp.AndreAbelQuest)
				link.l1 = StringFromKey("Morgan_493");
			else
				link.l1 = StringFromKey("Morgan_494", pchar);
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_13";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_13":
			dialog.text = StringFromKey("Morgan_495");
			link.l1 = StringFromKey("Morgan_496");
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_14";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_14":
			dialog.text = StringFromKey("Morgan_497", pchar);
			link.l1 = StringFromKey("Morgan_498");
			link.l1.go = "Andre_Abel_Quest_Morgan_Dialog_15";
		break;

		case "Andre_Abel_Quest_Morgan_Dialog_15":
			DialogExit();
			Log_TestInfo("Получено письмо от Генри Моргана.");
			GiveItem2Character(PChar, "Andre_Abel_Letter_2");
			AddQuestRecord("Andre_Abel_Quest", "21");
			AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("Andre_Abel_Quest", "sSex1", GetSexPhrase("", "а"));
			//HardCoffee рефакторинг диалога с Джэкманом
			//QuestSetCurrentNode("Jackman", "Andre_Abel_Quest_Jackman_Dialog_7");
			pchar.QuestTemp.AndreAbelQuest = "GoTo_Jackman2";

			RemoveLandQuestMark_Main(npchar, "Andre_Abel_Quest");
			AddLandQuestMark_Main(CharacterFromID("Jackman"), "Andre_Abel_Quest");
		break;

		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
			dialog.text = StringFromKey("Morgan_501", RandPhraseSimple(
						StringFromKey("Morgan_499", pchar),
						StringFromKey("Morgan_500")));
			link.l1 = StringFromKey("Morgan_502");
			link.l1.go = "AngryExitAgainWithOut";
			if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Морганом через 10 дней.
			{
				if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
				{
					dialog.text = StringFromKey("Morgan_503");
					link.l1 = StringFromKey("Morgan_504", pchar);
					link.l1.go = NextDiag.TempNode;
					CharacterDelAngry(npchar);
				}
			}
		break;
		case "AngryRepeat_2":
			dialog.text = StringFromKey("Morgan_507", RandPhraseSimple(
						StringFromKey("Morgan_505", pchar),
						StringFromKey("Morgan_506")));
			link.l1 = StringFromKey("Morgan_510", RandPhraseSimple(
						StringFromKey("Morgan_508"),
						StringFromKey("Morgan_509")));
			link.l1.go = "AngryExitAgain";
			if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Морганом через 10 дней.
			{
				if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
				{
					dialog.text = StringFromKey("Morgan_511");
					link.l1 = StringFromKey("Morgan_512");
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
			if (Pchar.location == "SentJons_HouseF3") DoReloadCharacterToLocation("SentJons_town", "reload", "houseF3");
			else DoReloadCharacterToLocation("PortRoyal_town", "reload", "houseS1");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
	}
}

void MorganBeginPhrases(aref Link)
{
	int iTemp;
	aref aTemp;
	//Английская линейка -->
	if (CheckAttribute(pchar, "QuestTemp.EngLine_Morgan_task"))
	{
		if ("EngLine_begin" == pchar.QuestTemp.EngLine_Morgan_task)
		{
			Link.l30 = StringFromKey("Morgan_513");
			Link.l30.go = "Step_1_1";
		}
		else if ("hot_business" == pchar.QuestTemp.EngLine_Morgan_task)
		{
			Link.l30 = StringFromKey("Morgan_514", pchar);
			Link.l30.go = "hot_business";
		}
		else if ("Give_blade" == pchar.QuestTemp.EngLine_Morgan_task)
		{
			Link.l30 = StringFromKey("Morgan_515");
			Link.l30.go = "Give_blade";
		}
	}
	//<-- Английская линейка
	//Голландская линейка -->
	if (CheckAttribute(pchar, "QuestTemp.HolLine_quests_task"))
	{
		if ("fromMansfield" == pchar.QuestTemp.HolLine_quests_task)
		{
			link.l31 = StringFromKey("Morgan_516", pchar);
			link.l31.go = "Step_H3_1";
		}
		else if ("fromStuvesant" == pchar.QuestTemp.HolLine_quests_task)
		{
			link.l31 = StringFromKey("Morgan_517", pchar);
			link.l31.go = "Step_H6_1";
		}
		else if ("fromSantiago" == pchar.QuestTemp.HolLine_quests_task)
		{
			link.l31 = StringFromKey("Morgan_518", pchar);
			link.l31.go = "HolLine6_fromSantiago";
		}
	}
	else if (CheckAttribute(pchar, "questTemp.Hol_Line_AboutWorm"))
	{
		MakeARef(aTemp, pchar.questTemp.Hol_Line_AboutWorm);
		iTemp = GetAttributesNum(aTemp);
		if (iTemp > 2)
		{
			if (pchar.questTemp.Hol_Line_AboutWorm.Again == false)
			{
				link.l31 = StringFromKey("Morgan_519");
				link.l31.go = "HolLine3_aboutWorm";
			}
			else if (pchar.questTemp.Hol_Line_AboutWorm.Again == true && iTemp > sti(pchar.questTemp.Hol_Line_AboutWorm.Nums))
			{
				link.l31 = StringFromKey("Morgan_520");
				link.l31.go = "Step_H3_5_again";
			}
			pchar.questTemp.Hol_Line_AboutWorm.Nums = iTemp;
		}
	}
	//<-- Голландская линейка
	//Французская линейка -->
	if (CheckAttribute(pchar, "QuestTemp.FraLine_Morgan_task"))
	{
		if ("FraLine8_talk" == pchar.QuestTemp.FraLine_Morgan_task)
		{
			//Наверное надо более понятно написать, к чему эта фраза буддет вести
			link.l32 = StringFromKey("Morgan_521", pchar);
			link.l32.go = "Step_F8_1";
		}
		else if ("NeedMoney" == pchar.QuestTemp.FraLine_Morgan_task && sti(pchar.money) >= 250000)
		{
			link.l32 = StringFromKey("Morgan_522", pchar);
			link.l32.go = "Step_F8_6";
		}
	}
	//<-- Французская линейка
	//Приратская линейка -->
	if (pchar.questTemp.piratesLine != "over" && CheckAttribute(pchar, "QuestTemp.PirLine_quests_task"))
	{
		switch (pchar.QuestTemp.PirLine_quests_task)
		{
			case "AfterPrison":
				link.l33 = StringFromKey("Morgan_523");
				link.l33.go = "PL_Q2_1";
			break;
			case "PL_Q2_away_1":
				link.l33 = StringFromKey("Morgan_524", pchar);
				link.l33.go = "PL_Q2_away_2";
			break;
			case "ShouldKillLoy":
				link.l33 = StringFromKey("Morgan_525");
				link.l33.go = "ShouldKillLoy";
			break;
			case "PL_Q3_GoodWork":
				link.l33 = StringFromKey("Morgan_526");
				link.l33.go = "PL_Q3_GoodWork";
			break;
			case "PL_Q4_late":
				link.l33 = StringFromKey("Morgan_527", pchar);
				link.l33.go = "PL_Q4_late_1";
			break;
			case "PL_Q4_DidWork":
				link.l33 = StringFromKey("Morgan_528");
				if ("PearlQ4_badWork" == pchar.questTemp.piratesLine) link.l33.go = "PL_Q4_badWork";
				else if ("PearlQ4_goodWork" == pchar.questTemp.piratesLine) link.l33.go = "PL_Q4_goodWork";
			break;
			case "Q7_GoToMorgan":
				link.l33 = StringFromKey("Morgan_529", pchar);
				link.l33.go = "PL_Q7_begin_1";
			break;
			case "PL_Q7_AboutLiney":
				link.l33 = StringFromKey("Morgan_530");
				link.l33.go = "PL_Q7_AboutLiney";
			break;
			case "PL_Q7_BadWork":
				link.l33 = StringFromKey("Morgan_531");
				link.l33.go = "PL_Q7_BadWork_1";
			break;
			case "PL_Q7_GoodWork":
				link.l33 = StringFromKey("Morgan_532");
				link.l33.go = "PL_Q7_GoodWork_1";
			break;
		}
	}
	// <--Пиратская линейка
	//Прочие квесты -->
	if (CheckAttribute(pchar, "QuestTemp.AndreAbelQuest")) //Сопровождение ориона
	{
		if (pchar.QuestTemp.AndreAbelQuest == "GoTo_Morgan1")
		{
			Link.l34 = StringFromKey("Morgan_533");
			Link.l34.go = "Andre_Abel_Quest_Morgan_Dialog_2";
		}
		else if (HasSubStr(pchar.QuestTemp.AndreAbelQuest, "GoTo_Morgan"))
		{
			Link.l34 = StringFromKey("Morgan_534", pchar);
			Link.l34.go = "Andre_Abel_Quest_Morgan_Dialog_11";
		}
	}
	if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "takeRumour"))
	{
		Link.l35 = StringFromKey("Morgan_535");
		Link.l35.go = "SharpPearl_1";
	}
	//<-- Прочие квесты
}

string CheckPearl()
{
	//    bool sSumPearl = false;
	//    int iBigPearl, iSmallPearl;
	int iPinctada, iGoodQty;

	//    if (sti(pchar.questTemp.piratesLine.Qty.SmallPearl) >= sti(pchar.items.jewelry12))
	//    {
	//        pchar.questTemp.piratesLine.Qty.SmallPearl = sti(pchar.questTemp.piratesLine.Qty.SmallPearl) - sti(pchar.items.jewelry12);
	//        iSmallPearl = sti(pchar.items.jewelry12);
	//    }
	//    else
	//    {
	//        iSmallPearl = sti(pchar.items.jewelry12) - sti(pchar.questTemp.piratesLine.Qty.SmallPearl);
	//        pchar.questTemp.piratesLine.Qty.SmallPearl = 0;
	//    }
	//
	//    if (sti(pchar.questTemp.piratesLine.Qty.BigPearl) >= sti(pchar.items.jewelry11))
	//    {
	//        pchar.questTemp.piratesLine.Qty.BigPearl = sti(pchar.questTemp.piratesLine.Qty.BigPearl) - sti(pchar.items.jewelry11);
	//        iBigPearl = sti(pchar.items.jewelry11);
	//    }
	//    else
	//    {
	//        iBigPearl = sti(pchar.items.jewelry11) - sti(pchar.questTemp.piratesLine.Qty.BigPearl);
	//        pchar.questTemp.piratesLine.Qty.BigPearl = 0;
	//    }

	iGoodQty = GetSquadronGoods(pchar, GOOD_PINCTADA);
	if (sti(pchar.questTemp.piratesLine.Qty.Pinctada) >= iGoodQty)
	{
		pchar.questTemp.piratesLine.Qty.Pinctada = sti(pchar.questTemp.piratesLine.Qty.Pinctada) - iGoodQty;
		iPinctada = iGoodQty;
	}
	else
	{
		iPinctada = iGoodQty - sti(pchar.questTemp.piratesLine.Qty.Pinctada);
		pchar.questTemp.piratesLine.Qty.Pinctada = 0;
	}

	//    PlaySound("Took_item");
	//    if (iSmallPearl != 0)
	//    {
	//        Log_Info(StringFromKey("InfoMessages_154", iSmallPearl));
	//        TakeNItems(pchar, "jewelry12", -iSmallPearl);
	//    }
	//    if (iBigPearl != 0)
	//    {
	//        Log_Info(StringFromKey("InfoMessages_155", iBigPearl));
	//        TakeNItems(pchar, "jewelry11", -iBigPearl);
	//    }
	if (iPinctada != 0)
	{
		Log_Info(StringFromKey("InfoMessages_217", iPinctada));
		RemoveCharacterGoods(pchar, GOOD_PINCTADA, iPinctada);
	}
	//    if (sti(pchar.questTemp.piratesLine.Qty.BigPearl) == 0 && sti(pchar.questTemp.piratesLine.Qty.SmallPearl) == 0)
	if (sti(pchar.questTemp.piratesLine.Qty.Pinctada) == 0)
	{
		return StringFromKey("Morgan_536", pchar);
	}
	return StringFromKey("Morgan_537", sti(pchar.questTemp.piratesLine.Qty.Pinctada));
}

string FactsAboutTheWurm()
{
	string sTemp = "";
	aref aHL, aPlace;
	MakeAref(aHL, pchar.questTemp.Hol_Line_AboutWorm);
	int iQAtr = GetAttributesNum(aHL);

	for (int i = 2; i < iQAtr; i++)
	{
		aPlace = GetAttributeN(aHL, i);
		switch (GetAttributeName(aPlace))
		{
			if (iQAtr > 4)
			{
				switch (i)
				{
					case 2: sTemp = StringFromKey("Morgan_538", sTemp); break;
					case 3: sTemp = StringFromKey("Morgan_539", sTemp); break;
					case 4: sTemp = StringFromKey("Morgan_540", sTemp); break;
					case 5:
						sTemp = StringFromKey("Morgan_541", sTemp);
						if (iQAtr < 7) sTemp = StringFromKey("Morgan_542", sTemp);
					break;
					case 6: sTemp = StringFromKey("Morgan_543", sTemp); break;
				}
			}
			else if (iQAtr == 4 && sTemp != "")  sTemp = StringFromKey("Morgan_544", sTemp);
			else sTemp = StringFromKey("Morgan_545", sTemp);
			case "Tavern": sTemp = StringFromKey("Morgan_546", sTemp); break;
			case "Store": sTemp = StringFromKey("Morgan_547", sTemp); break;
			case "Shipyard": sTemp = StringFromKey("Morgan_548", sTemp); break;
			case "Usurer": sTemp = StringFromKey("Morgan_549", sTemp); break;
			case "Brothel": sTemp = StringFromKey("Morgan_550", sTemp); break;
		}
	}
	if (sTemp != "") sTemp = sTemp + ".";
	return sTemp;
}


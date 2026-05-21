// boal 27.03.2004 Изабела Армани (романтическая ветка)
void ProcessDialogEvent()
{
	ref NPChar, d, sld, rColony;
	aref Link, NextDiag;
	string NPC_Meeting;
	int i, iMoney, iTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, sTemp;
	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;
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
				//когда достал обещаниями денег дать
					if (npchar.angry.name == "NewLife_Budget_Add") Dialog.CurrentNode = "AngryRepeat_Budget_Add";
					//когда подарками достал, а сам не давал
					if (npchar.angry.name == "NewLife_Present") Dialog.CurrentNode = "AngryRepeat_Present";
				break;
				case "quest":
				//когда долги достали Изабеллу
					if (npchar.angry.name == "NewLife_Budget_Pay") Dialog.CurrentNode = "AngryRepeat_Budget_Pay";
					//когда достало Изабеллу пиратсво ГГ
					if (npchar.angry.name == "NewLife_KnowPirates") Dialog.CurrentNode = "AngryRepeat_KnowPirates";
				break;
			}
		}
	}
	// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
	// ============================================================================
	switch (Dialog.CurrentNode)
	{
		case "exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			NPChar.quest.meeting = NPC_Meeting;
			DialogExit();
		break;

		case "First time":
			NextDiag.TempNode = "first time";
			//был в спальне
			pchar.quest.wasInBeedroom = true;
			bDisableFastReload = true;
			// прерывание на выход, а то ход истории в руках геймера
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
			dialog.text = StringFromKey("Isabella_1");
			link.l1 = StringFromKey("Isabella_2", GetFullName(pchar));
			link.l1.go = "Next_1";
			link.l2 = StringFromKey("Isabella_3");
			link.l2.go = "exit";
		break;

		case "Next_1":
			NextDiag.TempNode = "Next_2";

			dialog.text = StringFromKey("Isabella_4", NPChar.Name, NPChar.LastName);
			link.l1 = StringFromKey("Isabella_5");
			link.l1.go = "Next_4";
			link.l2 = StringFromKey("Isabella_6");
			link.l2.go = "exit";
		break;

		case "Next_2":
			NextDiag.TempNode = "Next_2";
			dialog.text = StringFromKey("Isabella_7");
			link.l1 = StringFromKey("Isabella_8");
			link.l1.go = "Next_3";
			link.l2 = StringFromKey("Isabella_9");
			link.l2.go = "exit";
		break;

		case "Next_3":
			NextDiag.TempNode = "Next_2";
			dialog.text = StringFromKey("Isabella_10");
			link.l1 = StringFromKey("Isabella_11");
			link.l1.go = "exit";
		break;

		case "Next_4":
			dialog.text = StringFromKey("Isabella_12");
			link.l1 = StringFromKey("Isabella_13");
			link.l1.go = "Next_5";
			link.l2 = StringFromKey("Isabella_14");
			link.l2.go = "Next_6";
			link.l3 = StringFromKey("Isabella_15");
			link.l3.go = "Next_7";
		break;

		case "Next_5":
			dialog.text = StringFromKey("Isabella_16");
			link.l1 = StringFromKey("Isabella_17");
			link.l1.go = "Next_8";
			link.l2 = StringFromKey("Isabella_18");
			link.l2.go = "Next_9";
			Pchar.RomanticQuest.TalkInShop = true;
		break;

		case "Next_6":
			dialog.text = StringFromKey("Isabella_19", characters[GetCharacterIndex("Husband")].Name);
			link.l1 = StringFromKey("Isabella_20");
			link.l1.go = "Romantic_Battle_in_Bedroom";
		break;

		case "Next_7":
			dialog.text = StringFromKey("Isabella_21", characters[GetCharacterIndex("Husband")].Name);
			link.l1 = StringFromKey("Isabella_22");
			link.l1.go = "Romantic_Battle_in_Bedroom";
		break;

		case "Next_8":
			NextDiag.TempNode = "Good_1";
			dialog.text = StringFromKey("Isabella_23");
			link.l1 = StringFromKey("Isabella_24");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, 3);
		break;

		case "Next_9":
			NextDiag.TempNode = "Next_2";
			dialog.text = StringFromKey("Isabella_25");
			link.l1 = StringFromKey("Isabella_26");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -4);
		break;

		case "Good_1":
			NextDiag.TempNode = "Good_1";
			dialog.text = StringFromKey("Isabella_27");
			link.l1 = StringFromKey("Isabella_28", Npchar.Name);
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep) + 1;
			pchar.quest.wasInBeedroom = true;
			bDisableFastReload = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
		break;

		case "Romantic_Battle_in_Bedroom":
			NextDiag.CurrentNode = "Next_2";
			DialogExit();
			AddDialogExitQuest("Romantic_Battle_in_Bedroom_1");
		break;

		case "Murder":
			NextDiag.TempNode = "Murder";
			dialog.text = StringFromKey("Isabella_29");
			link.l1 = "...";
			link.l1.go = "exit";
			PChar.quest.Romantic_TalkInShop.over = "yes";
		break;

		case "TalkInShop":
			NextDiag.TempNode = "TalkInShop_2";
			dialog.text = StringFromKey("Isabella_30", GetFullName(PChar));
			link.l1 = StringFromKey("Isabella_31");
			link.l1.go = "exit";
		//AddDialogExitQuest("Romantic_TalkInShop_3");
		break;

		case "TalkInShop_2":
			dialog.text = StringFromKey("Isabella_32");
			link.l1 = StringFromKey("Isabella_33");
			link.l1.go = "TalkInShop_3";
		break;

		case "TalkInShop_3":
			dialog.text = StringFromKey("Isabella_34");
			link.l1 = StringFromKey("Isabella_35");
			link.l1.go = "TalkInShop_4";
		break;

		case "TalkInShop_4":
			dialog.text = StringFromKey("Isabella_36", GetCharacterFullName("SanJuan_trader"), GetCharacterFullName("SanJuan_trader"));
			link.l1 = StringFromKey("Isabella_37");
			link.l1.go = "TalkInShop_5";
			link.l2 = StringFromKey("Isabella_38");
			link.l2.go = "TalkInShop_6";
		break;

		case "TalkInShop_5":
			AddMoneyToCharacter(pchar, -1200);
			NextDiag.TempNode = "Good_1";
			dialog.text = StringFromKey("Isabella_39");
			link.l1 = StringFromKey("Isabella_40");
			link.l1.go = "TalkInShop_Go";
		break;

		case "TalkInShop_6":
			NextDiag.CurrentNode = "TalkInShop_7";
			DialogExit();
			characters[GetCharacterIndex("SanJuan_trader")].dialog.currentnode = "Romantic_2";
			AddDialogExitQuest("Romantic_TalkInShop_3");
		break;

		case "TalkInShop_7":
			NextDiag.TempNode = "Good_1";
			dialog.text = StringFromKey("Isabella_41");
			link.l1 = StringFromKey("Isabella_42");
			link.l1.go = "TalkInShop_Go";
		break;

		case "TalkInShop_Go":
			NextDiag.CurrentNode = "Good_1";
			DialogExit();
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "SanJuan_church", "goto", "goto1", "Romantic_TalkInShop_end", 4.0);
			chrDisableReloadToLocation = true;
		break;

		case "TalkInChurch":
		//NextDiag.TempNode = "TalkInChurch_1";
			dialog.text = StringFromKey("Isabella_43");
			link.l1 = StringFromKey("Isabella_44");
			link.l1.go = "TalkInChurch_1";
			DeleteAttribute(npchar, "talker"); //снимаем говорилку
		break;

		case "TalkInChurch_1":
			dialog.text = StringFromKey("Isabella_45");
			link.l1 = StringFromKey("Isabella_46");
			link.l1.go = "TalkInChurch_2";
		break;

		case "TalkInChurch_2":
			dialog.text = StringFromKey("Isabella_47");
			link.l1 = StringFromKey("Isabella_48");
			link.l1.go = "TalkInChurch_3";
		break;

		case "TalkInChurch_3":
			dialog.text = StringFromKey("Isabella_49");
			link.l1 = StringFromKey("Isabella_50");
			link.l1.go = "TalkInChurch_4";
		break;

		case "TalkInChurch_4":
			dialog.text = StringFromKey("Isabella_51");
			link.l1 = StringFromKey("Isabella_52");
			link.l1.go = "TalkInChurch_Go";
		break;

		case "TalkInChurch_Go":
			chrDisableReloadToLocation = true;
			NextDiag.CurrentNode = "WaitShip";
			Pchar.RomanticQuest.ShipToCumana = true;
			DialogExit();
			AddQuestRecord("Romantic_Line", "5");
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "SanJuan_houseS1Bedroom", "goto", "goto4", "Romantic_TalkInChurch_end", 20.0);
			// немного веселой жизни
			TraderHunterOnMap();
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
			AddLandQuestmark_Main(CharacterFromID("Cumana_tavernkeeper"), "Romantic_Line");
			AddLandQuestmarkToFantoms_Main("Citizen", "Romantic_Line", "RomanticLine_ShipToCumana_Citizen_QuestMarkCondition");
			AddLandQuestmarkToFantoms_Main("Commoner", "Romantic_Line", "RomanticLine_ShipToCumana_Citizen_QuestMarkCondition");
		break;

		case "WaitShip":
			NextDiag.TempNode = "WaitShip";
			dialog.text = StringFromKey("Isabella_53");
			link.l1 = StringFromKey("Isabella_54", Npchar.Name);
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep) + 1;
			bDisableFastReload = true;
			pchar.quest.wasInBeedroom = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
		break;
		// разговор с братом
		case "Brother_1":
			dialog.text = StringFromKey("Isabella_55");
			link.l1 = StringFromKey("Isabella_56");
			link.l1.go = "Brother_2";
		break;
		case "Brother_2":
			dialog.text = StringFromKey("Isabella_57");
			link.l1 = StringFromKey("Isabella_58");
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_Brother_House_3");
			NextDiag.TempNode = "Brother_3";
		break;
		case "Brother_3":
			dialog.text = StringFromKey("Isabella_59", GetFullName(pchar));
			link.l1 = StringFromKey("Isabella_60");
			link.l1.go = "Brother_4";
		break;
		case "Brother_4":
			AddQuestRecord("Romantic_Line", "8");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SanJuan_houseS1Bedroom", "goto", "goto4", "Romantic_TalkInChurch_end", 5.0);
			NextDiag.CurrentNode = "Temp_Thanks";
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		case "Temp_Thanks":
			NextDiag.TempNode = "Temp_Thanks";
			dialog.text = StringFromKey("Isabella_61");
			link.l1 = StringFromKey("Isabella_62");
			link.l1.go = "exit";
			if (!CheckAttribute(pchar, "quest.VisitStep")) pchar.quest.VisitStep = 1;
			else pchar.quest.VisitStep = makeint(pchar.quest.VisitStep) + 1;
			bDisableFastReload = true;
			pchar.quest.wasInBeedroom = true;
			pchar.quest.RP_afterVisitBedroom.win_condition.l1 = "ExitFromLocation";
			pchar.quest.RP_afterVisitBedroom.win_condition.l1.location = pchar.location;
			pchar.quest.RP_afterVisitBedroom.win_condition = "RP_afterVisitBedroom";
		break;
		// разговор с ГГ на взятом бриге
		case "BrigAbordage":
			dialog.text = StringFromKey("Isabella_63");
			link.l1 = StringFromKey("Isabella_64");
			link.l1.go = "BrigAbordage_1";
		break;
		case "BrigAbordage_1":
			dialog.text = StringFromKey("Isabella_65");
			link.l1 = StringFromKey("Isabella_66");
			link.l1.go = "BrigAbordage_2";
		break;
		case "BrigAbordage_2":
			dialog.text = StringFromKey("Isabella_67");
			if (CheckCharacterItem(pchar, "Order"))
			{
				link.l1 = StringFromKey("Isabella_68");
				link.l1.go = "BrigAbordage_8";
			}
			else
			{
				link.l1 = StringFromKey("Isabella_69");
				link.l1.go = "BrigAbordage_3";
			}
		break;
		// --> нету поддельных векселей в наличие
		case "BrigAbordage_3":
			dialog.text = StringFromKey("Isabella_70");
			link.l1 = StringFromKey("Isabella_71");
			link.l1.go = "BrigAbordage_4";
		break;
		case "BrigAbordage_4":
			dialog.text = StringFromKey("Isabella_72");
			link.l1 = StringFromKey("Isabella_73");
			link.l1.go = "BrigAbordage_5";
		break;
		case "BrigAbordage_5":
			dialog.text = StringFromKey("Isabella_74");
			link.l1 = StringFromKey("Isabella_75");
			link.l1.go = "BrigAbordage_6";
		break;
		case "BrigAbordage_6":
			dialog.text = StringFromKey("Isabella_76");
			link.l1 = StringFromKey("Isabella_77");
			link.l1.go = "BrigAbordage_7";
		break;
		case "BrigAbordage_7":
			dialog.text = StringFromKey("Isabella_78");
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetPlayerType(pchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.location = "none";
			npchar.location.group = "";
			npchar.location.locator = "";
			AddQuestRecord("Romantic_Line", "17");
			QuestSetCurrentNode("Atilla", "Isabella_Sink");
		break;
		// --> поддельные векселя - у ГГ.
		case "BrigAbordage_8":
			dialog.text = StringFromKey("Isabella_79", GetFullName(pchar));
			link.l1 = StringFromKey("Isabella_80");
			link.l1.go = "BrigAbordage_9";
			TakeItemFromCharacter(pchar, "Order");
		break;
		case "BrigAbordage_9":
			dialog.text = StringFromKey("Isabella_81");
			link.l1 = StringFromKey("Isabella_82");
			link.l1.go = "BrigAbordage_10";
		break;
		case "BrigAbordage_10":
			dialog.text = StringFromKey("Isabella_83");
			link.l1 = StringFromKey("Isabella_84");
			link.l1.go = "BrigAbordage_11";
		break;
		case "BrigAbordage_11":
			dialog.text = StringFromKey("Isabella_85");
			link.l1 = StringFromKey("Isabella_86");
			link.l1.go = "BrigAbordage_12";
		break;
		case "BrigAbordage_12":
			dialog.text = StringFromKey("Isabella_87");
			link.l1 = StringFromKey("Isabella_88");
			link.l1.go = "exit";
			LAi_SetPlayerType(pchar);
			pchar.RomanticQuest = "SeekInPortoBello";
			AddQuestRecord("Romantic_Line", "18");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			//засада, оставленная Сальватором в Портобело
			Pchar.quest.Romantic_AmbushInPortoBello.win_condition.l1 = "location";
			Pchar.quest.Romantic_AmbushInPortoBello.win_condition.l1.location = "PortoBello_houseF2";
			Pchar.quest.Romantic_AmbushInPortoBello.win_condition = "Romantic_AmbushInPortoBello";
			//кузину Роситу в дом Белиза
			sld = GetCharacter(NPC_GenerateCharacter("Rosita", "girl_11", "woman", "towngirl", 5, SPAIN, -1, false));
			sld.name = FindPersonalName("Rosita_name");
			sld.lastname = FindPersonalName("Rosita_lastname");
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			sld.dialog.currentnode = "Rosita";
			sld.greeting = "Gr_Dama";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_houseS4", "goto", "goto2");
			AddLandQuestmark_Main(sld, "Romantic_Line");
			AddLandQuestmark_Main(CharacterFromID("PortoBello_tavernkeeper"), "Romantic_Line");
		break;
		//Изабелла в доме с засадой в Портобело
		case "AmbushPortoBello":
			dialog.text = StringFromKey("Isabella_89", pchar.name);
			link.l1 = StringFromKey("Isabella_90");
			link.l1.go = "AmbushPortoBello_1";
		break;
		case "AmbushPortoBello_1":
			dialog.text = StringFromKey("Isabella_91");
			link.l1 = StringFromKey("Isabella_92");
			link.l1.go = "AmbushPortoBello_2";
		break;
		case "AmbushPortoBello_2":
			dialog.text = StringFromKey("Isabella_93");
			link.l1 = StringFromKey("Isabella_94");
			link.l1.go = "AmbushPortoBello_3";
		break;
		case "AmbushPortoBello_3":
			dialog.text = StringFromKey("Isabella_95");
			link.l1 = StringFromKey("Isabella_96");
			link.l1.go = "AmbushPortoBello_4";
		break;
		case "AmbushPortoBello_4":
			dialog.text = StringFromKey("Isabella_97", pchar.name);
			link.l1 = StringFromKey("Isabella_98");
			link.l1.go = "AmbushPortoBello_5";
		break;
		case "AmbushPortoBello_5":
			AddQuestRecord("Romantic_Line", "24");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 2.0);
			DialogExit();
		break;
		//Изабелла на выходе из дома Роситы в Белизе
		case "BelizTalk":
			dialog.text = StringFromKey("Isabella_99", pchar.name);
			link.l1 = StringFromKey("Isabella_100");
			link.l1.go = "BelizTalk_1";
		break;
		case "BelizTalk_1":
			dialog.text = StringFromKey("Isabella_101");
			link.l1 = StringFromKey("Isabella_102");
			link.l1.go = "BelizTalk_2";
		break;
		case "BelizTalk_2":
			dialog.text = StringFromKey("Isabella_103");
			link.l1 = StringFromKey("Isabella_104");
			link.l1.go = "BelizTalk_3";
		break;
		case "BelizTalk_3":
			dialog.text = StringFromKey("Isabella_105", pchar.name);
			link.l1 = StringFromKey("Isabella_106");
			link.l1.go = "BelizTalk_4";
		break;
		case "BelizTalk_4":
			dialog.text = StringFromKey("Isabella_107");
			link.l1 = StringFromKey("Isabella_108");
			link.l1.go = "BelizTalk_5";
		break;
		case "BelizTalk_5":
			dialog.text = StringFromKey("Isabella_109");
			link.l1 = StringFromKey("Isabella_110");
			link.l1.go = "BelizTalk_6";
		break;
		case "BelizTalk_6":
			dialog.text = StringFromKey("Isabella_111");
			link.l1 = StringFromKey("Isabella_112");
			link.l1.go = "BelizTalk_7";
		break;
		case "BelizTalk_7":
			dialog.text = StringFromKey("Isabella_113");
			link.l1 = StringFromKey("Isabella_114");
			link.l1.go = "BelizTalk_8";
		break;
		case "BelizTalk_8":
			QuestSetCurrentNode("Atilla", "SalvatorNews");
			NextDiag.CurrentNode = "BelizTalk_after";
			AddQuestRecord("Romantic_Line", "19");
			chrDisableReloadToLocation = false;
			RemovePassenger(pchar, npchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "houseS4", "Beliz_houseS4", "goto", "goto1", "Romantic_TalkInChurch_end", 3.5);
			DialogExit();
			AddLandQuestmark_Main(characterFromID("Atilla"), "Romantic_Line");
		break;
		case "BelizTalk_after":
			dialog.text = StringFromKey("Isabella_115");
			link.l1 = StringFromKey("Isabella_116");
			link.l1.go = "exit";
			NextDiag.TempNode = "BelizTalk_after";
		break;
		//Изабелла в пещере
		case "IsabellaInCave":
			dialog.text = StringFromKey("Isabella_117", pchar.name);
			link.l1 = StringFromKey("Isabella_118");
			link.l1.go = "IsabellaInCave_1";
		break;
		case "IsabellaInCave_1":
			dialog.text = StringFromKey("Isabella_119");
			link.l1 = StringFromKey("Isabella_120");
			link.l1.go = "IsabellaInCave_2";
		break;
		case "IsabellaInCave_2":
			dialog.text = StringFromKey("Isabella_121", pchar.name);
			link.l1 = StringFromKey("Isabella_122");
			link.l1.go = "IsabellaInCave_3";
		break;
		case "IsabellaInCave_3":
			dialog.text = StringFromKey("Isabella_123");
			link.l1 = StringFromKey("Isabella_124");
			link.l1.go = "IsabellaInCave_4";
		break;
		case "IsabellaInCave_4":
			dialog.text = StringFromKey("Isabella_125");
			link.l1 = StringFromKey("Isabella_126");
			link.l1.go = "IsabellaInCave_5";
		break;
		case "IsabellaInCave_5":
			dialog.text = StringFromKey("Isabella_127", pchar.name);
			link.l1 = StringFromKey("Isabella_128");
			link.l1.go = "IsabellaInCave_6";
		break;
		case "IsabellaInCave_6":
			dialog.text = StringFromKey("Isabella_129");
			link.l1 = StringFromKey("Isabella_130");
			link.l1.go = "IsabellaInCave_7";
		break;
		case "IsabellaInCave_7":
			dialog.text = StringFromKey("Isabella_131");
			link.l1 = StringFromKey("Isabella_132");
			link.l1.go = "exit";
			LAi_SetActorType(npchar);
			pchar.RomanticQuest = "FoundIsabella";
			AddDialogExitQuest("Romantic_SalvatorInCave");
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		//после схватки с Сальватором в пещере
		case "SalvatorIsDead":
			dialog.text = StringFromKey("Isabella_133");
			link.l1 = StringFromKey("Isabella_134");
			link.l1.go = "SalvatorIsDead_1";
		break;
		case "SalvatorIsDead_1":
			dialog.text = StringFromKey("Isabella_135", pchar.name);
			link.l1 = StringFromKey("Isabella_136");
			link.l1.go = "SalvatorIsDead_2";
		break;
		case "SalvatorIsDead_2":
			dialog.text = StringFromKey("Isabella_137", pchar.name);
			link.l1 = StringFromKey("Isabella_138");
			link.l1.go = "SalvatorIsDead_3";
		break;
		case "SalvatorIsDead_3":
			dialog.text = StringFromKey("Isabella_139");
			link.l1 = StringFromKey("Isabella_140");
			link.l1.go = "SalvatorIsDead_4";
		break;
		case "SalvatorIsDead_4":
			dialog.text = StringFromKey("Isabella_141");
			link.l1 = StringFromKey("Isabella_142");
			link.l1.go = "SalvatorIsDead_5";
		break;
		case "SalvatorIsDead_5":
			dialog.text = StringFromKey("Isabella_143");
			link.l1 = StringFromKey("Isabella_144");
			link.l1.go = "SalvatorIsDead_6";
		break;
		case "SalvatorIsDead_6":
			dialog.text = StringFromKey("Isabella_145", pchar.name);
			link.l1 = StringFromKey("Isabella_146");
			link.l1.go = "SalvatorIsDead_7";
		break;
		case "SalvatorIsDead_7":
			Pchar.quest.Romantic_DelivToRosita.win_condition.l1 = "location";
			Pchar.quest.Romantic_DelivToRosita.win_condition.l1.location = "Beliz_houseS4";
			Pchar.quest.Romantic_DelivToRosita.win_condition = "Romantic_DelivToRosita";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;
		//после спасения в доме у Роситы
		case "RositaHouse":
			dialog.text = StringFromKey("Isabella_147", GetFullName(pchar));
			link.l1 = StringFromKey("Isabella_148");
			link.l1.go = "RositaHouse_1";
			AddQuestRecord("Romantic_Line", "22");
		break;
		case "RositaHouse_1":
			dialog.text = StringFromKey("Isabella_149");
			link.l1 = StringFromKey("Isabella_150");
			link.l1.go = "exit";
			NextDiag.TempNode = "RositaHouse_1";
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		//Изабелла вновь в Сан-Хуане
		case "InSanJuanAgain":
			dialog.text = StringFromKey("Isabella_151", pchar.name);
			link.l1 = StringFromKey("Isabella_152");
			link.l1.go = "InSanJuanAgain_1";
		break;
		case "InSanJuanAgain_1":
			dialog.text = StringFromKey("Isabella_153");
			link.l1 = StringFromKey("Isabella_154");
			link.l1.go = "InSanJuanAgain_2";
		break;
		case "InSanJuanAgain_2":
			dialog.text = StringFromKey("Isabella_155");
			link.l1 = StringFromKey("Isabella_156");
			link.l1.go = "InSanJuanAgain_3";
		break;
		case "InSanJuanAgain_3":
			dialog.text = StringFromKey("Isabella_157", pchar.name);
			link.l1 = StringFromKey("Isabella_158");
			link.l1.go = "InSanJuanAgain_4";
		break;
		case "InSanJuanAgain_4":
			dialog.text = StringFromKey("Isabella_159");
			link.l1 = StringFromKey("Isabella_160");
			link.l1.go = "exit";
			NextDiag.TempNode = "InSanJuanAgain_after";
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //закрываем двери дома.
			pchar.RomanticQuest = "WaitBeginWidding";
			AddQuestRecord("Romantic_Line", "23");
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		case "InSanJuanAgain_after":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Isabella_161"),
						StringFromKey("Isabella_162"),
						StringFromKey("Isabella_163"),
						StringFromKey("Isabella_164"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Isabella_165"),
						StringFromKey("Isabella_166"),
						StringFromKey("Isabella_167"),
						StringFromKey("Isabella_168"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "exit", "exit", "InSanJuanAgain_out", npchar, Dialog.CurrentNode);
			NextDiag.TempNode = "InSanJuanAgain_after";
		break;
		case "InSanJuanAgain_out":
			AddDialogExitQuest("Romantic_OutFromHouse");
			DialogExit();
		break;

		case "Cancel_Widding":
			dialog.text = StringFromKey("Isabella_169");
			link.l1 = StringFromKey("Isabella_170");
			link.l1.go = "exit";
			NextDiag.TempNode = "Cancel_Widding_1";
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //закрываем дом
			CloseQuestHeader("Romantic_Line");
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		case "Cancel_Widding_1":
			dialog.text = StringFromKey("Isabella_171");
			link.l1 = StringFromKey("Isabella_172");
			link.l1.go = "exit";
			NextDiag.TempNode = "Cancel_Widding_1";
		break;
		//свадьба
		case "TalkWidding":
			dialog.text = StringFromKey("Isabella_173", pchar.name);
			link.l1 = StringFromKey("Isabella_174");
			link.l1.go = "TalkWidding_1";
		break;
		case "TalkWidding_1":
			dialog.text = StringFromKey("Isabella_175", pchar.name);
			link.l1 = StringFromKey("Isabella_176");
			link.l1.go = "TalkWidding_2";
		break;
		case "TalkWidding_2":
			dialog.text = StringFromKey("Isabella_177");
			link.l1 = "...";
			link.l1.go = "exit";
			LAi_SetActorType(npchar);
			LAi_ActorTurnToLocator(npchar, "barmen", "stay");
			AddDialogExitQuest("Romantic_Padre");
		break;
		//драка в церкви
		case "AmbushInChurch":
			dialog.text = StringFromKey("Isabella_178", pchar.name);
			link.l1 = StringFromKey("Isabella_179");
			link.l1.go = "exit";
			AddDialogExitQuest("Romantic_fightInChurch_2");
		break;
		case "IsabellaIsMyWife":
			dialog.text = StringFromKey("Isabella_180");
			link.l1 = StringFromKey("Isabella_181");
			link.l1.go = "IsabellaIsMyWife_1";
		break;
		case "IsabellaIsMyWife_1":
			dialog.text = StringFromKey("Isabella_182");
			link.l1 = StringFromKey("Isabella_183");
			link.l1.go = "IsabellaIsMyWife_2";
		break;
		case "IsabellaIsMyWife_2":
			dialog.text = StringFromKey("Isabella_184", pchar.name);
			link.l1 = StringFromKey("Isabella_185");
			link.l1.go = "IsabellaIsMyWife_3";
		break;
		case "IsabellaIsMyWife_3":
			rColony = GetColonyByIndex(FindColony("SanJuan"));
			dialog.text = StringFromKey("Isabella_186");
			if (sti(rColony.HeroOwn))
			{
				link.l1 = StringFromKey("Isabella_187");
				LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			}
			else
			{
				link.l1 = StringFromKey("Isabella_188");
				pchar.RomanticQuest.MayorOk = 1; //флаг на базар с мэром Сан-Хуана
				AddLandQuestmark_Main(characterFromID("SanJuan_Mayor"), "Romantic_Line");
			}
			link.l1.go = "IsabellaIsMyWife_4";
		break;
		case "IsabellaIsMyWife_4":
			chrDisableReloadToLocation = true;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto1", "Romantic_TalkInChurch_end", 15.0);
			NextDiag.TempNode = "NewLife_firstTime";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Romantic_Line");
		break;
		//первый диалог после свадьбы
		case "NewLife_firstTime":
			rColony = GetColonyByIndex(FindColony("SanJuan"));
			dialog.text = StringFromKey("Isabella_189");
			if (sti(rColony.HeroOwn))
			{
				dialog.text = StringFromKey("Isabella_190");
				link.l1 = StringFromKey("Isabella_191");
			}
			else
			{
				dialog.text = StringFromKey("Isabella_192");
				link.l1 = StringFromKey("Isabella_193");
			}
			link.l1.go = "NewLife_firstTime_1";
		break;
		case "NewLife_firstTime_1":
			dialog.text = StringFromKey("Isabella_194");
			link.l1 = StringFromKey("Isabella_195");
			link.l1.go = "NewLife_firstTime_2";
		break;
		case "NewLife_firstTime_2":
			dialog.text = StringFromKey("Isabella_196");
			link.l1 = StringFromKey("Isabella_197");
			link.l1.go = "NewLife_firstTime_3";
		break;
		case "NewLife_firstTime_3":
			dialog.text = StringFromKey("Isabella_198");
			link.l1 = StringFromKey("Isabella_199");
			link.l1.go = "NewLife_firstTime_4";
		break;
		case "NewLife_firstTime_4":
			dialog.text = StringFromKey("Isabella_200");
			link.l1 = StringFromKey("Isabella_201");
			link.l1.go = "NewLife_firstTime_5";
		break;
		case "NewLife_firstTime_5":
			dialog.text = StringFromKey("Isabella_202", FindMoneyString(MOD_SKILL_ENEMY_RATE * 10000));
			link.l1 = StringFromKey("Isabella_203");
			link.l1.go = "NewLife_firstTime_6";
		break;
		case "NewLife_firstTime_6":
			dialog.text = StringFromKey("Isabella_204");
			link.l1 = StringFromKey("Isabella_205");
			link.l1.go = "exit";
			NextDiag.TempNode = "NewLife";
			AddDialogExitQuest("Romantic_afterFirstTime");
		break;
		//************************************ новая жизнь бывшего корсара ********************************
		case "NewLife_hello":
			iTemp = GetQuestPastDayParam("RomanticQuest");
			dialog.text = StringFromKey("Isabella_209", LinkRandPhrase(
						StringFromKey("Isabella_206"),
						StringFromKey("Isabella_207"),
						StringFromKey("Isabella_208")));
			link.l1 = StringFromKey("Isabella_212", RandPhraseSimple(
						StringFromKey("Isabella_210"),
						StringFromKey("Isabella_211")));
			link.l1.go = "NewLife";
			if (iTemp > 40)
			{
				dialog.text = StringFromKey("Isabella_215", RandPhraseSimple(
							StringFromKey("Isabella_213", FindDaysString(iTemp)),
							StringFromKey("Isabella_214", FindDaysString(iTemp))));
				link.l1 = StringFromKey("Isabella_218", RandPhraseSimple(
							StringFromKey("Isabella_216"),
							StringFromKey("Isabella_217")));
				link.l1.go = "NewLife_hello_1";
			}
			if (GetQuestPastDayParam("RomanticQuest") > 3 && pchar.RomanticQuest == "OpenTheDoosOfHouse")
			{
				dialog.text = StringFromKey("Isabella_219");
				link.l1 = StringFromKey("Isabella_220");
				link.l1.go = "NewLife_hello_2";
			}
		break;
		case "NewLife_hello_1":
			dialog.text = StringFromKey("Isabella_221");
			link.l1 = StringFromKey("Isabella_224", RandPhraseSimple(
						StringFromKey("Isabella_222"),
						StringFromKey("Isabella_223")));
			link.l1.go = "NewLife";
			SaveCurrentQuestDateParam("RomanticQuest"); //обновим дату, от которой считаем отсутствие
			LAi_CharacterPlaySound(npchar, "Gr_Isabella_3");
		break;
		case "NewLife_hello_2":
			dialog.text = StringFromKey("Isabella_225");
			link.l1 = StringFromKey("Isabella_226");
			link.l1.go = "NewLife";
			SaveCurrentQuestDateParam("RomanticQuest"); //обновим дату, от которой считаем отсутствие
			LAi_CharacterPlaySound(npchar, "Gr_Isabella_3");
		break;
		//======================== типовое меню ==========================
		case "NewLife":
		//проверяем, как там с финансами у нас
			iMoney = IsabellaCheckBudgetMoney();
			if (iMoney > 0)
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Isabella_227", FindMoneyString(iMoney)),
							StringFromKey("Isabella_228", FindMoneyString(iMoney)),
							StringFromKey("Isabella_229", FindMoneyString(iMoney)),
							StringFromKey("Isabella_230", FindMoneyString(iMoney)), "block", 3, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Isabella_233", RandPhraseSimple(
									StringFromKey("Isabella_231"),
									StringFromKey("Isabella_232"))),
							StringFromKey("Isabella_234"),
							StringFromKey("Isabella_235"),
							StringFromKey("Isabella_236"), npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay";
				break;
			}
			//--> проверяем статистику на пиратство
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.GrabbingTown") && pchar.RomanticQuest.Cheking != "Ok")
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.GrabbingTown) * 150) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = StringFromKey("Isabella_239", RandPhraseSimple(
								StringFromKey("Isabella_237"),
								StringFromKey("Isabella_238")));
					link.l1 = StringFromKey("Isabella_243", LinkRandPhrase(
								StringFromKey("Isabella_240"),
								StringFromKey("Isabella_241"),
								StringFromKey("Isabella_242")));
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("GrabbingTown");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.TakeTown") && pchar.RomanticQuest.Cheking != "Ok")
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.TakeTown) * 140) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = StringFromKey("Isabella_246", RandPhraseSimple(
								StringFromKey("Isabella_244"),
								StringFromKey("Isabella_245")));
					link.l1 = StringFromKey("Isabella_250", LinkRandPhrase(
								StringFromKey("Isabella_247"),
								StringFromKey("Isabella_248"),
								StringFromKey("Isabella_249")));
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("TakeTown");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.KillFort") && pchar.RomanticQuest.Cheking != "Ok")
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.KillFort) * 130) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = StringFromKey("Isabella_253", RandPhraseSimple(
								StringFromKey("Isabella_251"),
								StringFromKey("Isabella_252")));
					link.l1 = StringFromKey("Isabella_257", LinkRandPhrase(
								StringFromKey("Isabella_254"),
								StringFromKey("Isabella_255"),
								StringFromKey("Isabella_256")));
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("KillFort");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.AbordShip") && pchar.RomanticQuest.Cheking != "Ok")
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.AbordShip) * 70) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = StringFromKey("Isabella_260", RandPhraseSimple(
								StringFromKey("Isabella_258"),
								StringFromKey("Isabella_259")));
					link.l1 = StringFromKey("Isabella_264", LinkRandPhrase(
								StringFromKey("Isabella_261"),
								StringFromKey("Isabella_262"),
								StringFromKey("Isabella_263")));
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("AbordShip");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			if (CheckAttribute(pchar, "RomanticQuest.Cheking.KillShip") && pchar.RomanticQuest.Cheking != "Ok")
			{
				if (rand(sti(pchar.RomanticQuest.Cheking.KillShip) * 50) >= GetCharacterSkill(pchar, "Sneak"))//ранд типа слухи не дошли
				{
					dialog.text = StringFromKey("Isabella_267", RandPhraseSimple(
								StringFromKey("Isabella_265"),
								StringFromKey("Isabella_266")));
					link.l1 = StringFromKey("Isabella_271", LinkRandPhrase(
								StringFromKey("Isabella_268"),
								StringFromKey("Isabella_269"),
								StringFromKey("Isabella_270")));
					link.l1.go = "NewLife_KnowPirates";
					IsabellaSetCurrentState("KillShip");
					LAi_CharacterPlaySound(npchar, "Gr_Isabella_2");
					break;
				}
			}
			//<-- проверяем статистику на пиратство
			//        -------  ОСНОВНОЕ МЕНЮ  ----------
			dialog.text = StringFromKey("Isabella_275", LinkRandPhrase(
						StringFromKey("Isabella_272"),
						StringFromKey("Isabella_273"),
						StringFromKey("Isabella_274", pchar.lastname)));
			link.l1 = StringFromKey("Isabella_276");
			link.l1.go = "NewLife_JustTalk";
			link.l2 = StringFromKey("Isabella_277");
			link.l2.go = "NewLife_Budget";
			link.l3 = StringFromKey("Isabella_278");
			link.l3.go = "NewLife_Present";
			link.l4 = StringFromKey("Isabella_279");
			link.l4.go = "NewLife_Sex";
			link.l5 = StringFromKey("Isabella_280");
			link.l5.go = "NewLife_Sleep";
		break;
		//=========================== Бюджет =================================
		case "NewLife_Budget":
			iMoney = IsabellaCheckBudgetMoney();
			if (iMoney > -(MOD_SKILL_ENEMY_RATE * 10000)) //деньги на исходе
			{
				if (iMoney == 0)
				{
					dialog.text = StringFromKey("Isabella_283", RandPhraseSimple(
								StringFromKey("Isabella_281"),
								StringFromKey("Isabella_282")));
				}
				else
				{
					dialog.text = StringFromKey("Isabella_284", FindMoneyString(-iMoney));
					link.l1 = StringFromKey("Isabella_287", RandPhraseSimple(
								StringFromKey("Isabella_285"),
								StringFromKey("Isabella_286")));
					link.l1.go = "NewLife";
				}
				link.l2 = StringFromKey("Isabella_290", RandPhraseSimple(
							StringFromKey("Isabella_288"),
							StringFromKey("Isabella_289")));
				link.l2.go = "NewLife_Budget_Add";
				LAi_CharacterPlaySound(npchar, "Gr_Isabella_4");
			}
			else //профицит
			{
				dialog.text = StringFromKey("Isabella_293", RandPhraseSimple(
							StringFromKey("Isabella_291", FindMoneyString(-iMoney)),
							StringFromKey("Isabella_292", FindMoneyString(-iMoney))));
				link.l1 = StringFromKey("Isabella_296", RandPhraseSimple(
							StringFromKey("Isabella_294"),
							StringFromKey("Isabella_295")));
				link.l1.go = "NewLife";
				link.l2 = StringFromKey("Isabella_297");
				link.l2.go = "NewLife_Budget_Add";
			}
		break;
		case "NewLife_Budget_Add":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Isabella_298"),
						StringFromKey("Isabella_299"),
						StringFromKey("Isabella_300"),
						StringFromKey("Isabella_301"), "repeat", 1, npchar, Dialog.CurrentNode);
			if (sti(pchar.money) >= 50000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Isabella_302"),
							StringFromKey("Isabella_303"),
							StringFromKey("Isabella_304"), "...", npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_50";
			}
			if (sti(pchar.money) >= 100000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l2 = HeroStringReactionRepeat(
							StringFromKey("Isabella_305"),
							StringFromKey("Isabella_306"),
							StringFromKey("Isabella_307"), "...", npchar, Dialog.CurrentNode);
				link.l2.go = "NewLife_Budget_100";
			}
			if (sti(pchar.money) >= 200000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l3 = HeroStringReactionRepeat(
							StringFromKey("Isabella_308"),
							StringFromKey("Isabella_309"),
							StringFromKey("Isabella_310"), "...", npchar, Dialog.CurrentNode);
				link.l3.go = "NewLife_Budget_200";
			}
			if (sti(pchar.money) >= 500000 && npchar.quest.repeat.NewLife_Budget_Add.ans != "3")
			{
				link.l4 = HeroStringReactionRepeat(
							StringFromKey("Isabella_311"),
							StringFromKey("Isabella_312"),
							StringFromKey("Isabella_313"), "...", npchar, Dialog.CurrentNode);
				link.l4.go = "NewLife_Budget_500";
			}
			link.l5 = HeroStringReactionRepeat(
						StringFromKey("Isabella_314"),
						StringFromKey("Isabella_315"),
						StringFromKey("Isabella_316"),
						StringFromKey("Isabella_317"), npchar, Dialog.CurrentNode);
			link.l5.go = "NewLife_Budget_No";
		break;
		case "NewLife_Budget_50":
			dialog.text = StringFromKey("Isabella_318", pchar.name);
			link.l1 = StringFromKey("Isabella_319");
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(50000);
		break;
		case "NewLife_Budget_100":
			dialog.text = StringFromKey("Isabella_320");
			link.l1 = StringFromKey("Isabella_321");
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(100000);
		break;
		case "NewLife_Budget_200":
			dialog.text = StringFromKey("Isabella_322");
			link.l1 = StringFromKey("Isabella_323");
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(200000);
		break;
		case "NewLife_Budget_500":
			dialog.text = StringFromKey("Isabella_324");
			link.l1 = StringFromKey("Isabella_325");
			link.l1.go = "NewLife";
			IsabellaAddMoneyBudget(500000);
		break;
		case "NewLife_Budget_No":
			dialog.text = StringFromKey("Isabella_329", LinkRandPhrase(
						StringFromKey("Isabella_326"),
						StringFromKey("Isabella_327"),
						StringFromKey("Isabella_328")));
			link.l1 = StringFromKey("Isabella_333", LinkRandPhrase(
						StringFromKey("Isabella_330"),
						StringFromKey("Isabella_331"),
						StringFromKey("Isabella_332")));
			link.l1.go = "NewLife";
		break;
		//заплатить долги и понулить счетчик бюджета
		case "NewLife_Budget_Pay":
			iMoney = IsabellaCheckBudgetMoney();
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Isabella_334", pchar.lastname),
						StringFromKey("Isabella_335"),
						StringFromKey("Isabella_336"),
						StringFromKey("Isabella_337"), "quest", 30, npchar, Dialog.CurrentNode);
			if (sti(pchar.money) >= iMoney)
			{
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Isabella_338"),
							StringFromKey("Isabella_339"),
							StringFromKey("Isabella_340"),
							StringFromKey("Isabella_341"), npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay_2";
				link.l2 = StringFromKey("Isabella_342");
				link.l2.go = "NewLife_Budget_Pay_1";
			}
			else
			{
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Isabella_343", FindMoneyString(iMoney)),
							StringFromKey("Isabella_344"),
							StringFromKey("Isabella_345"),
							StringFromKey("Isabella_346"), npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Budget_Pay_1";
			}
		break;
		case "NewLife_Budget_Pay_1":
			dialog.text = StringFromKey("Isabella_349", RandPhraseSimple(
						StringFromKey("Isabella_347"),
						StringFromKey("Isabella_348")));
			link.l1 = StringFromKey("Isabella_352", RandPhraseSimple(
						StringFromKey("Isabella_350"),
						StringFromKey("Isabella_351")));
			link.l1.go = "NewLife_exit";
		break;
		case "NewLife_Budget_Pay_2":
			dialog.text = StringFromKey("Isabella_355", RandPhraseSimple(
						StringFromKey("Isabella_353"),
						StringFromKey("Isabella_354")));
			link.l1 = StringFromKey("Isabella_358", RandPhraseSimple(
						StringFromKey("Isabella_356"),
						StringFromKey("Isabella_357")));
			link.l1.go = "NewLife";
			iMoney = IsabellaCheckBudgetMoney();
			AddMoneyToCharacter(pchar, -iMoney);
			IsabellaNullBudget();
		break;
		//=========================== Изабелла узнала, что ГГ опять пиратствует =================================
		case "NewLife_KnowPirates":
			pchar.RomanticQuest.Cheking = "Ok"; //флаг "не проверять больше на пиратство" в этот раз
			if (rand(12) < GetCharacterSPECIAL(pchar, "Charisma")) //поверила, дура
			{
				dialog.text = StringFromKey("Isabella_362", LinkRandPhrase(
							StringFromKey("Isabella_359", pchar.name),
							StringFromKey("Isabella_360"),
							StringFromKey("Isabella_361", pchar.name)));
				link.l1 = StringFromKey("Isabella_365", RandPhraseSimple(
							StringFromKey("Isabella_363"),
							StringFromKey("Isabella_364")));
				link.l1.go = "NewLife";
			}
			else //не поверила, и правильно сделала
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Isabella_366"),
							StringFromKey("Isabella_367"),
							StringFromKey("Isabella_368", pchar.name),
							StringFromKey("Isabella_369", pchar.lastname), "quest", 80, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Isabella_370"),
							StringFromKey("Isabella_371"),
							StringFromKey("Isabella_372"),
							StringFromKey("Isabella_373"), npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife";
			}
		break;
		//=========================== Секс =================================
		case "NewLife_Sex":
			if (GetQuestPastMonthParam("RomanticQuest") > 2 && GetNpcQuestPastDayParam(npchar, "sex") != 0)
			{
				dialog.text = StringFromKey("Isabella_374");
				link.l1 = StringFromKey("Isabella_375");
				link.l1.go = "NewLife_Sex_1";
			}
			else
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Isabella_376"),
							StringFromKey("Isabella_377"),
							StringFromKey("Isabella_378"),
							StringFromKey("Isabella_379"), "cycle", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Isabella_380"),
							StringFromKey("Isabella_381"),
							StringFromKey("Isabella_382"),
							StringFromKey("Isabella_383"), npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_Sex_5";
			}
		break;
		case "NewLife_Sex_1":
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //запоминаем секс
			dialog.text = StringFromKey("Isabella_384");
			link.l1 = StringFromKey("Isabella_385");
			link.l1.go = "NewLife_Sex_2";
		break;
		case "NewLife_Sex_2":
			dialog.text = StringFromKey("Isabella_386");
			link.l1 = StringFromKey("Isabella_387");
			link.l1.go = "NewLife_Sex_3";
		break;
		case "NewLife_Sex_3":
			dialog.text = StringFromKey("Isabella_388");
			link.l1 = StringFromKey("Isabella_389");
			link.l1.go = "NewLife_Sex_4";
		break;
		case "NewLife_Sex_4":
			if (rand(6) < 5)
			{
				dialog.text = StringFromKey("Isabella_390");
				link.l1 = StringFromKey("Isabella_391");
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = StringFromKey("Isabella_392");
				link.l1 = StringFromKey("Isabella_393");
				link.l1.go = "NewLife_exit";
			}
		break;

		case "NewLife_Sex_Late":
			dialog.text = StringFromKey("Isabella_394");
			link.l1 = StringFromKey("Isabella_395");
			link.l1.go = "NewLife_Sex_Late_1";
		break;
		case "NewLife_Sex_Late_1":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto1", "Romantic_TalkInChurch_end", 3.5);
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NewLife_Sex_5":
			if (GetNpcQuestPastDayParam(npchar, "sex") > 3)
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Isabella_396"),
							StringFromKey("Isabella_397"),
							StringFromKey("Isabella_398"),
							StringFromKey("Isabella_399"), "block", 60, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Isabella_400"),
							StringFromKey("Isabella_401"),
							StringFromKey("Isabella_402"),
							StringFromKey("Isabella_403"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("NewLife_Sex_10", "NewLife_Sex_11", "NewLife_Sex_12", "NewLife_Sex_13", npchar, Dialog.CurrentNode);
			}
			else //слишком часто, не прокатит
			{
				dialog.text = StringFromKey("Isabella_407", LinkRandPhrase(
							StringFromKey("Isabella_404"),
							StringFromKey("Isabella_405"),
							StringFromKey("Isabella_406")));
				link.l1 = StringFromKey("Isabella_410", RandPhraseSimple(
							StringFromKey("Isabella_408"),
							StringFromKey("Isabella_409")));
				link.l1.go = "NewLife_exit";
			}
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //запоминаем секс
		break;
		case "NewLife_Sex_10":
			dialog.text = StringFromKey("Isabella_411");
			link.l1 = StringFromKey("Isabella_412");
			link.l1.go = "NewLife_GoSex";
		break;
		case "NewLife_Sex_11":
			if (rand(10) < 8)
			{
				dialog.text = StringFromKey("Isabella_413");
				link.l1 = StringFromKey("Isabella_414");
				link.l1.go = "NewLife_GoSex";
			}
			else //не свезло
			{
				dialog.text = StringFromKey("Isabella_418", LinkRandPhrase(
							StringFromKey("Isabella_415"),
							StringFromKey("Isabella_416"),
							StringFromKey("Isabella_417")));
				link.l1 = StringFromKey("Isabella_421", RandPhraseSimple(
							StringFromKey("Isabella_419"),
							StringFromKey("Isabella_420")));
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_Sex_12":
			if (rand(10) < 5)
			{
				dialog.text = StringFromKey("Isabella_422");
				link.l1 = StringFromKey("Isabella_423");
				link.l1.go = "NewLife_GoSex";
			}
			else //не свезло
			{
				dialog.text = StringFromKey("Isabella_427", LinkRandPhrase(
							StringFromKey("Isabella_424"),
							StringFromKey("Isabella_425"),
							StringFromKey("Isabella_426")));
				link.l1 = StringFromKey("Isabella_430", RandPhraseSimple(
							StringFromKey("Isabella_428"),
							StringFromKey("Isabella_429")));
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_Sex_13":
			if (rand(10) < 2)
			{
				dialog.text = StringFromKey("Isabella_431");
				link.l1 = StringFromKey("Isabella_432");
				link.l1.go = "NewLife_GoSex";
			}
			else //не свезло
			{
				dialog.text = StringFromKey("Isabella_433");
				link.l1 = StringFromKey("Isabella_434");
				link.l1.go = "NewLife_exit";
			}
		break;
		//идем в спальню
		case "NewLife_GoSex":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			SaveCurrentNpcQuestDateParam(npchar, "sex"); //запомнить секс
			Pchar.quest.Romantic_Sex.win_condition.l1 = "location";
			Pchar.quest.Romantic_Sex.win_condition.l1.location = "SanJuan_houseS1Bedroom";
			Pchar.quest.Romantic_Sex.win_condition = "Romantic_Sex";
			SetTimerCondition("Romantic_IsabellaBackToHall", 0, 0, 1, false);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "SanJuan_houseS1Bedroom", "goto", "goto6", "Romantic_TalkInChurch_end", 20.0);
			DialogExit();
		break;
		//после секса
		case "NewLife_afterSex":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Isabella_435"),
						StringFromKey("Isabella_436"),
						StringFromKey("Isabella_437"),
						StringFromKey("Isabella_438"), "block", 30, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Isabella_439"),
						StringFromKey("Isabella_440"),
						StringFromKey("Isabella_441"),
						StringFromKey("Isabella_442"), npchar, Dialog.CurrentNode);
			link.l1.go = "NewLife_afterSex_1";
		break;
		case "NewLife_afterSex_1":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto2", "Romantic_TalkInChurch_end", 20.0);
			Pchar.quest.Romantic_IsabellaBackToHall.over = "yes";
			DialogExit();
		break;
		//=========================== Сон =================================
		case "NewLife_Sleep":
			dialog.text = StringFromKey("Isabella_443");
			if (!isDay())
			{
				link.l1 = StringFromKey("Isabella_444");
				link.l1.go = "NewLife_Sleep_day";
			}
			else
			{
				link.l1 = StringFromKey("Isabella_445");
				link.l1.go = "NewLife_Sleep_night";
				link.l2 = StringFromKey("Isabella_446");
				link.l2.go = "NewLife_Sleep_day";
			}
		break;
		case "NewLife_Sleep_day":
			dialog.text = StringFromKey("Isabella_447");
			link.l1 = StringFromKey("Isabella_448");
			link.l1.go = "room_day_wait";
			link.l2 = StringFromKey("Isabella_449");
			link.l2.go = "NewLife_exit";
		break;
		case "NewLife_Sleep_night":
			dialog.text = StringFromKey("Isabella_450");
			link.l1 = StringFromKey("Isabella_451");
			link.l1.go = "room_night_wait";
			link.l2 = StringFromKey("Isabella_452");
			link.l2.go = "NewLife_exit";
		break;
		case "room_day_wait":
			DialogExit();
			NextDiag.TempNode = "NewLife_hello";
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate("wait_day");
			AddDialogExitQuest("sleep_in_home");
		break;
		case "room_night_wait":
			DialogExit();
			NextDiag.TempNode = "NewLife_hello";
			NextDiag.CurrentNode = NextDiag.TempNode;
			TavernWaitDate("wait_night");
			AddDialogExitQuest("sleep_in_home");
		break;
		//=========================== Просто разговор =================================
		case "NewLife_JustTalk":
			if (CheckAttribute(pchar, "RomanticQuest.Atilla"))
			{
				switch (pchar.RomanticQuest.Atilla)
				{
					case "YouAreSwine":
						dialog.text = StringFromKey("Isabella_453", pchar.name);
						link.l1 = StringFromKey("Isabella_454");
						link.l1.go = "NewLife_exit";
					break;
					case "YouAreBaster":
						dialog.text = StringFromKey("Isabella_455");
						link.l1 = StringFromKey("Isabella_456");
						link.l1.go = "NewLife_exit";
					break;
					case "YouAreNormal":
						dialog.text = StringFromKey("Isabella_457");
						link.l1 = StringFromKey("Isabella_458");
						link.l1.go = "NewLife_exit";
					break;
					case "YouAreGood":
						dialog.text = StringFromKey("Isabella_459");
						link.l1 = StringFromKey("Isabella_460");
						link.l1.go = "NewLife_exit";
					break;
				}
				DeleteAttribute(pchar, "RomanticQuest.Atilla");
				break;
			}
			switch (rand(1))
			{
				case 0:
					dialog.text = StringFromKey("Isabella_464", LinkRandPhrase(
								StringFromKey("Isabella_461"),
								StringFromKey("Isabella_462", pchar.name),
								StringFromKey("Isabella_463", GetMainCharacterNameGen())));
					link.l1 = StringFromKey("Isabella_467", RandPhraseSimple(
								StringFromKey("Isabella_465"),
								StringFromKey("Isabella_466")));
					link.l1.go = "NewLife_exit";
				break;
				case 1:
					dialog.text = StringFromKey("Isabella_471", LinkRandPhrase(
								StringFromKey("Isabella_468"),
								StringFromKey("Isabella_469"),
								StringFromKey("Isabella_470")));
					link.l1 = StringFromKey("Isabella_474", RandPhraseSimple(
								StringFromKey("Isabella_472"),
								StringFromKey("Isabella_473")));
					link.l1.go = "NewLife_exit";
				break;
			}
		break;
		//=========================== Подарки =================================
		case "NewLife_Present":
			dialog.text = StringFromKey("Isabella_477", RandPhraseSimple(
						StringFromKey("Isabella_475"),
						StringFromKey("Isabella_476")));
			iTemp = 1;
			for (i = 18; i >= 1; i--)
			{
				if (i == 8 || i == 9) continue;
				if (CheckCharacterItem(pchar, "jewelry" + i))
				{
					sTemp = "l" + iTemp;
					link.(sTemp) = GetItemName("jewelry" + i) + "."; // Вместо XI_ConvertString используем GetItemName
					link.(sTemp).go = "NewLife_jewelry_" + i;
					iTemp++;
				}
			}
			if (iTemp == 1)
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Isabella_478"),
							StringFromKey("Isabella_479"),
							StringFromKey("Isabella_480", pchar.name),
							StringFromKey("Isabella_481"), "repeat", 20, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Isabella_482"),
							StringFromKey("Isabella_483"),
							StringFromKey("Isabella_484"),
							StringFromKey("Isabella_485"), npchar, Dialog.CurrentNode);
				link.l1.go = "NewLife_exit";
			}
		break;
		case "NewLife_jewelry_1":
			dialog.text = StringFromKey("Isabella_489", LinkRandPhrase(
						StringFromKey("Isabella_486"),
						StringFromKey("Isabella_487"),
						StringFromKey("Isabella_488")));
			link.l1 = StringFromKey("Isabella_493", LinkRandPhrase(
						StringFromKey("Isabella_490"),
						StringFromKey("Isabella_491"),
						StringFromKey("Isabella_492")));
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry1");
		break;
		case "NewLife_jewelry_2":
			if (rand(4) == 1)
			{
				dialog.text = StringFromKey("Isabella_494");
				link.l1 = StringFromKey("Isabella_495");
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = StringFromKey("Isabella_499", LinkRandPhrase(
							StringFromKey("Isabella_496"),
							StringFromKey("Isabella_497"),
							StringFromKey("Isabella_498")));
				link.l1 = StringFromKey("Isabella_503", LinkRandPhrase(
							StringFromKey("Isabella_500"),
							StringFromKey("Isabella_501"),
							StringFromKey("Isabella_502")));
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry2");
		break;
		case "NewLife_jewelry_3":
			if (rand(10) == 1)
			{
				dialog.text = StringFromKey("Isabella_504");
				link.l1 = StringFromKey("Isabella_505");
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = StringFromKey("Isabella_509", LinkRandPhrase(
							StringFromKey("Isabella_506"),
							StringFromKey("Isabella_507"),
							StringFromKey("Isabella_508")));
				link.l1 = StringFromKey("Isabella_513", LinkRandPhrase(
							StringFromKey("Isabella_510"),
							StringFromKey("Isabella_511"),
							StringFromKey("Isabella_512")));
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry3");
		break;
		case "NewLife_jewelry_4":
			if (rand(3) == 1)
			{
				dialog.text = StringFromKey("Isabella_514");
				link.l1 = StringFromKey("Isabella_515");
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = StringFromKey("Isabella_519", LinkRandPhrase(
							StringFromKey("Isabella_516"),
							StringFromKey("Isabella_517"),
							StringFromKey("Isabella_518")));
				link.l1 = StringFromKey("Isabella_523", LinkRandPhrase(
							StringFromKey("Isabella_520"),
							StringFromKey("Isabella_521"),
							StringFromKey("Isabella_522")));
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry4");
		break;
		case "NewLife_jewelry_5":
			dialog.text = StringFromKey("Isabella_527", LinkRandPhrase(
						StringFromKey("Isabella_524"),
						StringFromKey("Isabella_525"),
						StringFromKey("Isabella_526")));
			link.l1 = StringFromKey("Isabella_531", LinkRandPhrase(
						StringFromKey("Isabella_528"),
						StringFromKey("Isabella_529"),
						StringFromKey("Isabella_530")));
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry5");
		break;
		case "NewLife_jewelry_6":
			dialog.text = StringFromKey("Isabella_535", LinkRandPhrase(
						StringFromKey("Isabella_532"),
						StringFromKey("Isabella_533"),
						StringFromKey("Isabella_534")));
			link.l1 = StringFromKey("Isabella_539", LinkRandPhrase(
						StringFromKey("Isabella_536"),
						StringFromKey("Isabella_537"),
						StringFromKey("Isabella_538")));
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry6");
		break;
		case "NewLife_jewelry_7":
			if (rand(2) == 1)
			{
				dialog.text = StringFromKey("Isabella_540");
				link.l1 = StringFromKey("Isabella_541");
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = StringFromKey("Isabella_545", LinkRandPhrase(
							StringFromKey("Isabella_542"),
							StringFromKey("Isabella_543"),
							StringFromKey("Isabella_544")));
				link.l1 = StringFromKey("Isabella_549", LinkRandPhrase(
							StringFromKey("Isabella_546"),
							StringFromKey("Isabella_547"),
							StringFromKey("Isabella_548")));
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry7");
		break;
		case "NewLife_jewelry_10":
			dialog.text = StringFromKey("Isabella_553", LinkRandPhrase(
						StringFromKey("Isabella_550"),
						StringFromKey("Isabella_551"),
						StringFromKey("Isabella_552")));
			link.l1 = StringFromKey("Isabella_557", LinkRandPhrase(
						StringFromKey("Isabella_554"),
						StringFromKey("Isabella_555"),
						StringFromKey("Isabella_556")));
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry10");
		break;
		case "NewLife_jewelry_11":
			dialog.text = StringFromKey("Isabella_561", LinkRandPhrase(
						StringFromKey("Isabella_558"),
						StringFromKey("Isabella_559"),
						StringFromKey("Isabella_560")));
			link.l1 = StringFromKey("Isabella_565", LinkRandPhrase(
						StringFromKey("Isabella_562"),
						StringFromKey("Isabella_563"),
						StringFromKey("Isabella_564")));
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry11");
		break;
		case "NewLife_jewelry_12":
			dialog.text = StringFromKey("Isabella_569", LinkRandPhrase(
						StringFromKey("Isabella_566"),
						StringFromKey("Isabella_567"),
						StringFromKey("Isabella_568")));
			link.l1 = StringFromKey("Isabella_572", RandPhraseSimple(
						StringFromKey("Isabella_570"),
						StringFromKey("Isabella_571")));
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry12");
		break;
		case "NewLife_jewelry_13":
			dialog.text = StringFromKey("Isabella_576", LinkRandPhrase(
						StringFromKey("Isabella_573"),
						StringFromKey("Isabella_574"),
						StringFromKey("Isabella_575")));
			link.l1 = StringFromKey("Isabella_580", LinkRandPhrase(
						StringFromKey("Isabella_577"),
						StringFromKey("Isabella_578"),
						StringFromKey("Isabella_579")));
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry13");
		break;
		case "NewLife_jewelry_14":
			if (rand(1) == 1)
			{
				dialog.text = StringFromKey("Isabella_581");
				link.l1 = StringFromKey("Isabella_582");
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = StringFromKey("Isabella_586", LinkRandPhrase(
							StringFromKey("Isabella_583"),
							StringFromKey("Isabella_584"),
							StringFromKey("Isabella_585")));
				link.l1 = StringFromKey("Isabella_590", LinkRandPhrase(
							StringFromKey("Isabella_587"),
							StringFromKey("Isabella_588"),
							StringFromKey("Isabella_589")));
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry14");
		break;
		case "NewLife_jewelry_15":
			if (rand(1) == 1)
			{
				dialog.text = StringFromKey("Isabella_591");
				link.l1 = StringFromKey("Isabella_592");
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = StringFromKey("Isabella_596", LinkRandPhrase(
							StringFromKey("Isabella_593"),
							StringFromKey("Isabella_594"),
							StringFromKey("Isabella_595")));
				link.l1 = StringFromKey("Isabella_600", LinkRandPhrase(
							StringFromKey("Isabella_597"),
							StringFromKey("Isabella_598"),
							StringFromKey("Isabella_599")));
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry15");
		break;
		case "NewLife_jewelry_16":
			dialog.text = StringFromKey("Isabella_604", LinkRandPhrase(
						StringFromKey("Isabella_601"),
						StringFromKey("Isabella_602"),
						StringFromKey("Isabella_603")));
			link.l1 = StringFromKey("Isabella_607", RandPhraseSimple(
						StringFromKey("Isabella_605"),
						StringFromKey("Isabella_606")));
			link.l1.go = "NewLife_exit";
		break;
		case "NewLife_jewelry_17":
			dialog.text = StringFromKey("Isabella_611", LinkRandPhrase(
						StringFromKey("Isabella_608"),
						StringFromKey("Isabella_609"),
						StringFromKey("Isabella_610")));
			link.l1 = StringFromKey("Isabella_614", RandPhraseSimple(
						StringFromKey("Isabella_612"),
						StringFromKey("Isabella_613")));
			link.l1.go = "NewLife_exit";
			TakeItemFromCharacter(pchar, "jewelry17");
		break;
		case "NewLife_jewelry_18":
			if (rand(8) == 1)
			{
				dialog.text = StringFromKey("Isabella_615");
				link.l1 = StringFromKey("Isabella_616");
				link.l1.go = "NewLife_GoSex";
			}
			else
			{
				dialog.text = StringFromKey("Isabella_620", LinkRandPhrase(
							StringFromKey("Isabella_617"),
							StringFromKey("Isabella_618"),
							StringFromKey("Isabella_619")));
				link.l1 = StringFromKey("Isabella_624", LinkRandPhrase(
							StringFromKey("Isabella_621"),
							StringFromKey("Isabella_622"),
							StringFromKey("Isabella_623")));
				link.l1.go = "NewLife_exit";
			}
			TakeItemFromCharacter(pchar, "jewelry18");
		break;
		//выход
		case "NewLife_exit":
			NextDiag.TempNode = "NewLife";
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "goto", "goto" + (rand(3) + 1), "Romantic_TalkInChurch_end", -1);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		//==> попытки дать денег
		case "AngryRepeat_Budget_Add":
			dialog.text = StringFromKey("Isabella_627", RandPhraseSimple(
						StringFromKey("Isabella_625"),
						StringFromKey("Isabella_626")));
			link.l1 = StringFromKey("Isabella_628");
			link.l1.go = "AngryExitAgain";
			if (CheckAttribute(npchar, "angry.terms")) //примиряемся 10 дней.
			{
				if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
				{
					dialog.text = StringFromKey("Isabella_629");
					link.l1 = StringFromKey("Isabella_630");
					link.l1.go = NextDiag.TempNode;
					CharacterDelAngry(npchar);
				}
				else //примирение через кольцо с сапфиром
				{
					if (CheckCharacterItem(pchar, "jewelry6") && CheckCharacterItem(pchar, "jewelry10"))
					{
						dialog.text = StringFromKey("Isabella_631");
						link.l1 = StringFromKey("Isabella_632");
						link.l1.go = NextDiag.TempNode;
						CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry6");
						TakeItemFromCharacter(pchar, "jewelry10");
					}
				}
			}
		break;
		//==> вовремя не рассчитался с долгами
		case "AngryRepeat_Budget_Pay":
			dialog.text = StringFromKey("Isabella_635", RandPhraseSimple(
						StringFromKey("Isabella_633"),
						StringFromKey("Isabella_634")));
			link.l1 = StringFromKey("Isabella_636");
			link.l1.go = "AngryExitAgain";
			if (CheckAttribute(npchar, "angry.terms")) //примиряемся 30 дней.
			{
				if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
				{
					dialog.text = StringFromKey("Isabella_637");
					link.l1 = StringFromKey("Isabella_638");
					link.l1.go = NextDiag.TempNode;
					CharacterDelAngry(npchar);
				}
				else //примирение через изумруды
				{
					if (CheckCharacterItem(pchar, "jewelry4") && CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "jewelry15"))
					{
						dialog.text = StringFromKey("Isabella_639");
						link.l1 = StringFromKey("Isabella_640");
						link.l1.go = NextDiag.TempNode;
						CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry4");
						TakeItemFromCharacter(pchar, "jewelry7");
						TakeItemFromCharacter(pchar, "jewelry15");
					}
				}
			}
		break;
		//==> если попался на пиратстве
		case "AngryRepeat_KnowPirates":
			dialog.text = StringFromKey("Isabella_643", RandPhraseSimple(
						StringFromKey("Isabella_641"),
						StringFromKey("Isabella_642")));
			link.l1 = StringFromKey("Isabella_644");
			link.l1.go = "AngryExitAgain";
			if (CheckAttribute(npchar, "angry.terms")) //примиряемся 80 дней.
			{
				if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
				{
					dialog.text = StringFromKey("Isabella_645");
					link.l1 = StringFromKey("Isabella_646");
					link.l1.go = NextDiag.TempNode;
					CharacterDelAngry(npchar);
					IsabellaSetCurrentState("All");
				}
				else //примирение через алмаз, рубины и большую жемчужину
				{
					if (CheckCharacterItem(pchar, "jewelry1") && CheckCharacterItem(pchar, "jewelry2") && CheckCharacterItem(pchar, "jewelry3") && CheckCharacterItem(pchar, "jewelry18") && CheckCharacterItem(pchar, "jewelry11"))
					{
						dialog.text = StringFromKey("Isabella_647", pchar.name);
						link.l1 = StringFromKey("Isabella_648");
						link.l1.go = NextDiag.TempNode;
						CharacterDelAngry(npchar);
						TakeItemFromCharacter(pchar, "jewelry1");
						TakeItemFromCharacter(pchar, "jewelry2");
						TakeItemFromCharacter(pchar, "jewelry3");
						TakeItemFromCharacter(pchar, "jewelry18");
						TakeItemFromCharacter(pchar, "jewelry11");
						IsabellaSetCurrentState("All");
					}
				}
			}
		break;
		//==> если достал подарками
		case "AngryRepeat_Present":
			dialog.text = StringFromKey("Isabella_651", RandPhraseSimple(
						StringFromKey("Isabella_649"),
						StringFromKey("Isabella_650")));
			link.l1 = StringFromKey("Isabella_654", RandPhraseSimple(
						StringFromKey("Isabella_652"),
						StringFromKey("Isabella_653")));
			link.l1.go = "AngryExitAgain";
			if (CheckAttribute(npchar, "angry.terms")) //примиряемся 20 дней.
			{
				if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
				{
					dialog.text = StringFromKey("Isabella_655");
					link.l1 = StringFromKey("Isabella_656");
					link.l1.go = NextDiag.TempNode;
					CharacterDelAngry(npchar);
				}
				else //примирение через злато-серебро
				{
					if (CheckCharacterItem(pchar, "jewelry5") && CheckCharacterItem(pchar, "jewelry17"))
					{
						if (sti(pchar.items.jewelry5) >= 3 && sti(pchar.items.jewelry17) >= 5)
						{
							dialog.text = StringFromKey("Isabella_657");
							link.l1 = StringFromKey("Isabella_658");
							link.l1.go = NextDiag.TempNode;
							CharacterDelAngry(npchar);
							TakeNItems(pchar, "jewelry5", -3);
							TakeNItems(pchar, "jewelry17", -5);
						}
					}
				}
			}
		break;
		case "AngryExitAgain":
			DialogExit();
			DeleteAttribute(npchar, "angry.ok");
		break;

		// <<<<<<<<<<<<============= блок нод angry =============================
	}
}

// диалоговый файл №1 на фр. линейку
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	float locx, locy, locz;
	string sTemp, attrName;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("FraLineNpc_1_1");
			link.l1 = StringFromKey("FraLineNpc_1_2");
			link.l1.go = "exit";

			//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
			//Квест №1, сопровождение Леграна.
			if (pchar.questTemp.State == "Fr1Legran_toTavern")// квест №1, Легран в таверне
			{
				dialog.text = StringFromKey("FraLineNpc_1_3");
				link.l1 = StringFromKey("FraLineNpc_1_4");
				link.l1.go = "Step_F1_1";
			}
			if (pchar.questTemp.State == "Fr1Legran_afterFightBand")// квест №1, Легаран после боя.
			{
				dialog.text = StringFromKey("FraLineNpc_1_5");
				link.l1 = StringFromKey("FraLineNpc_1_6", pchar);
				link.l1.go = "Step_F1_3";
				link.l2 = StringFromKey("FraLineNpc_1_7", pchar);
				link.l2.go = "Step_F1_5";
			}
			//Квест №2, доставка письма на Тортугу
			if (pchar.questTemp.State == "Fr2Letter_SeekProblems")// квест №2, странные типы в таверне
			{
				dialog.text = StringFromKey("FraLineNpc_1_8");
				link.l1 = StringFromKey("FraLineNpc_1_9");
				link.l1.go = "Step_F2_1";
			}
			if (pchar.questTemp.State == "Fr2Letter_SeekProblems" && pchar.location == "Shore22")// квест №2, странные типы в бухте
			{
				dialog.text = StringFromKey("FraLineNpc_1_10");
				link.l1 = StringFromKey("FraLineNpc_1_11");
				link.l1.go = "Step_F2_5";
			}
			if (npchar.id == "DeLeiva")// квест №3, база с мужем донны Анны
			{
				dialog.text = StringFromKey("FraLineNpc_1_12", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("FraLineNpc_1_13");
				link.l1.go = "Step_F3_1";
			}
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_toAnna")// квест №5, донна Анна в резиденции Тортуги
			{
				dialog.text = StringFromKey("FraLineNpc_1_14");
				link.l1 = StringFromKey("FraLineNpc_1_15", pchar);
				link.l1.go = "Step_F5_1";
			}
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_toHavana")
			{
				dialog.text = StringFromKey("FraLineNpc_1_16", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("FraLineNpc_1_17");
				link.l1.go = "exit";
			}
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_SeekHoseBrothers")
			{
				dialog.text = StringFromKey("FraLineNpc_1_18", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("FraLineNpc_1_19");
				link.l1.go = "exit";
			}
			if (npchar.id == "DeLeivaBrother_1" || npchar.id == "DeLeivaBrother_2")// квест №5, братья де Лейва
			{
				dialog.text = StringFromKey("FraLineNpc_1_20");
				link.l1 = StringFromKey("FraLineNpc_1_21");
				link.l1.go = "Step_F5_2";
			}
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "Fr5AnnaHant_GoodWork")// квест №5, донна Анна после выполнения задачи
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("FraLineNpc_1_22", UpperFirst(GetAddress_Form(NPChar))),
							StringFromKey("FraLineNpc_1_23"),
							StringFromKey("FraLineNpc_1_24"),
							StringFromKey("FraLineNpc_1_25"), "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("FraLineNpc_1_26"),
							StringFromKey("FraLineNpc_1_27", pchar),
							StringFromKey("FraLineNpc_1_28", pchar),
							StringFromKey("FraLineNpc_1_29"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F5_8", "none", "none", "none", npchar, Dialog.CurrentNode);

			}
			if (npchar.id == "AnnaDeLeiva" && pchar.questTemp.State == "empty")// квест №5, донна Анна после выполнения задачи
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("FraLineNpc_1_30", UpperFirst(GetAddress_Form(NPChar))),
							StringFromKey("FraLineNpc_1_31"),
							StringFromKey("FraLineNpc_1_32"),
							StringFromKey("FraLineNpc_1_33"), "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("FraLineNpc_1_34"),
							StringFromKey("FraLineNpc_1_35", pchar),
							StringFromKey("FraLineNpc_1_36", pchar),
							StringFromKey("FraLineNpc_1_37"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F5_8", "none", "none", "none", npchar, Dialog.CurrentNode);
			}
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_toGuadeloupe")// квест №6, базар в доме Олоне
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("FraLineNpc_1_38", pchar),
							StringFromKey("FraLineNpc_1_39"),
							StringFromKey("FraLineNpc_1_40"),
							StringFromKey("FraLineNpc_1_41"), "block", 0, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("FraLineNpc_1_42"),
							StringFromKey("FraLineNpc_1_43"),
							StringFromKey("FraLineNpc_1_44"),
							StringFromKey("FraLineNpc_1_45"), npchar, Dialog.CurrentNode);
				link.l1.go = DialogGoNodeRepeat("Step_F6_1", "none", "none", "none", npchar, Dialog.CurrentNode);
			}
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_FoundMoney") //успели к деньгам
			{
				dialog.text = StringFromKey("FraLineNpc_1_46", pchar);
				link.l1 = StringFromKey("FraLineNpc_1_47");
				link.l1.go = "Step_F6_14";
				LAi_LocationDisableOfficersGen("Cumana_town", false); //офицеров пускать
			}
			if (npchar.id == "Olone" && pchar.questTemp.State == "Fr5Olone_WeLate") //деньги ушли
			{
				dialog.text = StringFromKey("FraLineNpc_1_48", pchar);
				link.l1 = StringFromKey("FraLineNpc_1_49");
				link.l1.go = "Step_F6_10";
				LAi_LocationDisableOfficersGen("Cumana_town", false); //офицеров пускать
			}
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr8ThreeCorsairs_toBonrepo") //Квест №8. Маркиз Бонрепо в Бас-Тере
			{
				dialog.text = StringFromKey("FraLineNpc_1_50");
				link.l1 = StringFromKey("FraLineNpc_1_51", pchar, GetFullName(pchar));
				link.l1.go = "Step_F8_1";
			}
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr8ThreeCorsairs_toSeek")
			{
				dialog.text = StringFromKey("FraLineNpc_1_52");
				if (sti(pchar.questTemp.Count) == 3)
				{
					link.l1 = StringFromKey("FraLineNpc_1_53");
					link.l1.go = "Step_F8_9";
				}
				else
				{
					link.l1 = StringFromKey("FraLineNpc_1_54");
					link.l1.go = "exit";
				}
			}
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "Fr12EndWar_toBorepo")
			{
				dialog.text = StringFromKey("FraLineNpc_1_55", pchar);
				link.l1 = StringFromKey("FraLineNpc_1_56", pchar);
				link.l1.go = "Step_F12_1";
			}
			if (npchar.id == "Bonrepo" && pchar.questTemp.State == "EndOfQuestLine")
			{
				dialog.text = StringFromKey("FraLineNpc_1_57", pchar);
				link.l1 = StringFromKey("FraLineNpc_1_58");
				link.l1.go = "exit";
			}
		break;
		//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//********************************* Доставка Леграна до Мартиники. Квест №1 **********************************
		case "Step_F1_1":
			dialog.text = StringFromKey("FraLineNpc_1_59");
			link.l1 = StringFromKey("FraLineNpc_1_60", pchar, GetFullName(pchar));
			link.l1.go = "Step_F1_2";
		break;
		case "Step_F1_2":
			dialog.text = StringFromKey("FraLineNpc_1_61");
			link.l1 = StringFromKey("FraLineNpc_1_62");
			link.l1.go = "Step_F1_exit";
		break;
		case "Step_F1_exit":
			locations[FindLocation("Shore39")].DisableEncounters = true; //энкаунтеры закроем
			pchar.questTemp.State = "Fr1Legran_toLeMaren";
			AddQuestRecord("Fra_Line_1_LegranDis", "2");
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Tortuga_tavern", "tables", LAi_FindNearestFreeLocator("tables", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 8);
			Pchar.quest.Fr1Legran_intoLeMaren.win_condition.l1 = "location";
			Pchar.quest.Fr1Legran_intoLeMaren.win_condition.l1.location = "Shore39";
			Pchar.quest.Fr1Legran_intoLeMaren.win_condition = "Fr1Legran_intoLeMaren";
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		case "Step_F1_3":
			dialog.text = StringFromKey("FraLineNpc_1_63");
			link.l1 = StringFromKey("FraLineNpc_1_64");
			link.l1.go = "Step_F1_4";
		break;
		case "Step_F1_4":
			dialog.text = StringFromKey("FraLineNpc_1_65", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FraLineNpc_1_66");
			link.l1.go = "Step_F1_4_exit";
		break;
		case "Step_F1_4_exit":
			pchar.questTemp.State = "Fr1Legran_backGovernor";
			AddQuestRecord("Fra_Line_1_LegranDis", "3");
			AddMoneyToCharacter(pchar, 20000);
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", 10.0);
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], true);
			NPChar.LifeDay = 0;
			RemovePassenger(pchar, npchar);
			DialogExit();
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;
		case "Step_F1_5":
			dialog.text = StringFromKey("FraLineNpc_1_67", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_68");
			link.l1.go = "Step_F1_6";
		break;
		case "Step_F1_6":
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			AddQuestRecord("Fra_Line_1_LegranDis", "4");
			pchar.questTemp.State = "Fr1Legran_LegranKilled";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;
		//********************************* Арест ГГ у Стэвезанта. Квест №2 **********************************
		case "Step_F2_1":
			dialog.text = StringFromKey("FraLineNpc_1_69", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_70", GetFullName(pchar));
			link.l1.go = "Step_F2_2";
		break;
		case "Step_F2_2":
			dialog.text = StringFromKey("FraLineNpc_1_71");
			link.l1 = StringFromKey("FraLineNpc_1_72");
			link.l1.go = "Step_F2_3";
		break;
		case "Step_F2_3":
			dialog.text = StringFromKey("FraLineNpc_1_73");
			link.l1 = StringFromKey("FraLineNpc_1_74");
			link.l1.go = "Step_F2_4";
		break;
		case "Step_F2_4":
			chrDisableReloadToLocation = true;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			for (i = 12; i <= 13; i++)
			{
				sld = characterFromId("Bandit_" + i);
				LAi_SetStayType(sld);
				if (i == 12) ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "tables", "stay5");
				else ChangeCharacterAddressGroup(sld, "Villemstad_tavern", "goto", "goto3");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", 10);
			}
			Pchar.quest.Fr2Letter_OutTavern_2.win_condition.l1 = "location";
			Pchar.quest.Fr2Letter_OutTavern_2.win_condition.l1.location = "Villemstad_town";
			Pchar.quest.Fr2Letter_OutTavern_2.win_condition = "Fr2Letter_OutTavern_2";
			locations[FindLocation("Shore22")].DisableEncounters = true; //энкаутеры уберем временно
			LAi_SetPlayerType(pchar);
			DialogExit();
			RemoveLandQuestmark_Main(CharacterFromID("Villemstad_tavernkeeper"), "Fra_Line");
		break;

		case "Step_F2_5":
			dialog.text = StringFromKey("FraLineNpc_1_75");
			link.l1 = StringFromKey("FraLineNpc_1_76");
			link.l1.go = "Step_F2_6";
		break;
		case "Step_F2_6":
			dialog.text = StringFromKey("FraLineNpc_1_77");
			link.l1 = StringFromKey("FraLineNpc_1_78");
			link.l1.go = "Step_F2_7";
		break;
		case "Step_F2_7":
			dialog.text = StringFromKey("FraLineNpc_1_79", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_80", pchar);
			link.l1.go = "Step_F2_8";
		break;
		case "Step_F2_8":
			dialog.text = StringFromKey("FraLineNpc_1_81");
			link.l1 = StringFromKey("FraLineNpc_1_82");
			link.l1.go = "Step_F2_9";
		break;
		case "Step_F2_9":
			dialog.text = StringFromKey("FraLineNpc_1_83", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_84");
			link.l1.go = "Step_F2_10";
		break;
		case "Step_F2_10":
			dialog.text = StringFromKey("FraLineNpc_1_85");
			link.l1 = StringFromKey("FraLineNpc_1_86");
			link.l1.go = "Step_F2_11";
		break;
		case "Step_F2_11":
			DeleteAttribute(&locations[FindLocation("Shore22")], "DisableEncounters"); //энкаутеры вернём
			chrDisableReloadToLocation = true;
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition.l1 = "location";
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition.l1.location = "Curacao";
			Pchar.quest.Fr2Letter_FightWithGaleon.win_condition = "Fr2Letter_FightWithGaleon";
			AddQuestRecord("Fra_Line_2_DelivLetter", "4");
			for (i = 12; i <= 13; i++)
			{
				sld = characterFromId("Bandit_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_RemoveCheckMinHP(sld);
				LAi_SetHP(sld, 200, 200);
				RemoveLandQuestmark_Main(sld, "Fra_Line");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetPlayerType(pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//********************************* Драка с мужем де Лейва. Квест №3 **********************************
		case "Step_F3_1":
			dialog.text = StringFromKey("FraLineNpc_1_87", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_88");
			link.l1.go = "Step_F3_2";
		break;
		case "Step_F3_2":
			dialog.text = StringFromKey("FraLineNpc_1_89");
			link.l1 = StringFromKey("FraLineNpc_1_90");
			link.l1.go = "Step_F3_3";
		break;
		case "Step_F3_3":
			LAi_LocationFightDisable(loadedLocation, false);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetPlayerType(pchar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//********************************* Месть Анне де Лейва. Квест №5 **********************************
		case "Step_F5_1":
			dialog.text = StringFromKey("FraLineNpc_1_91", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_92");
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr5AnnaHant_toHavana";
			AddQuestRecord("Fra_Line_5_KillAnnaHanters", "2");
			sld = GetCharacter(NPC_GenerateCharacter("InesDeLasCierras", "girl_9", "woman", "towngirl", 10, SPAIN, -1, false));
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			sld.name = FindPersonalName("InesDeLasCierras_name");
			sld.lastname = FindPersonalName("InesDeLasCierras_lastname");
			sld.greeting = "Gr_Dama";
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "Havana_houseSp2", "goto", "goto2");
			AddLandQuestmark_Main(sld, "Fra_Line");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		case "Step_F5_2":
			dialog.text = StringFromKey("FraLineNpc_1_93");
			link.l1 = StringFromKey("FraLineNpc_1_94", pchar);
			link.l1.go = "Step_F5_3";
		break;
		case "Step_F5_3":
			dialog.text = StringFromKey("FraLineNpc_1_95");
			link.l1 = StringFromKey("FraLineNpc_1_96", pchar);
			link.l1.go = "Step_F5_4";
		break;
		case "Step_F5_4":
			dialog.text = StringFromKey("FraLineNpc_1_97");
			link.l1 = StringFromKey("FraLineNpc_1_98", pchar);
			link.l1.go = "Step_F5_5";
		break;
		case "Step_F5_5":
			dialog.text = StringFromKey("FraLineNpc_1_99");
			link.l1 = StringFromKey("FraLineNpc_1_100");
			link.l1.go = "Step_F5_6";
		break;
		case "Step_F5_6":
			dialog.text = StringFromKey("FraLineNpc_1_101", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_102", pchar);
			link.l1.go = "Step_F5_7";
		break;
		case "Step_F5_7":
			LAi_LocationDisableOfficersGen("Mayak10", false); //офицеров пускать
			pchar.questTemp.State = "Fr5AnnaHant_GoodWork";
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("AnnaDeLeiva"), "Fra_Line");
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak10")], false);
			LAi_group_Delete("EnemyFight");
			for (i = 1; i <= 2; i++)
			{
				sld = characterFromId("DeLeivaBrother_" + i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				RemoveLandQuestmark_Main(sld, "Fra_Line");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
		break;
		case "Step_F5_8":
			dialog.text = StringFromKey("FraLineNpc_1_103");
			link.l1 = StringFromKey("FraLineNpc_1_104", pchar);
			link.l1.go = "Step_F5_9";
		break;
		case "Step_F5_9":
			dialog.text = StringFromKey("FraLineNpc_1_105", GetAddress_Form(NPChar), pchar.name);
			link.l1 = StringFromKey("FraLineNpc_1_106");
			link.l1.go = "Step_F5_10";
		break;
		case "Step_F5_10":
			dialog.text = StringFromKey("FraLineNpc_1_107");
			link.l1 = StringFromKey("FraLineNpc_1_108");
			link.l1.go = "exit";
			npchar.LifeDay = 0;
		break;
		//********************************* Франсуа Олоне. Квест №6 **********************************
		case "Step_F6_1":
			dialog.text = StringFromKey("FraLineNpc_1_109");
			link.l1 = StringFromKey("FraLineNpc_1_110");
			link.l1.go = "Step_F6_2";
			TakeItemFromCharacter(pchar, "letter_FraLineQ6");
		break;
		case "Step_F6_2":
			dialog.text = StringFromKey("FraLineNpc_1_111");
			link.l1 = StringFromKey("FraLineNpc_1_112");
			link.l1.go = "Step_F6_3";
		break;
		case "Step_F6_3":
			dialog.text = StringFromKey("FraLineNpc_1_113");
			link.l1 = StringFromKey("FraLineNpc_1_114");
			link.l1.go = "Step_F6_WantMoney";
			link.l2 = StringFromKey("FraLineNpc_1_115");
			link.l2.go = "Step_F6_4";
			SaveCurrentQuestDateParam("questTemp");
		break;
		case "Step_F6_WantMoney":
			dialog.text = StringFromKey("FraLineNpc_1_116");
			link.l1 = StringFromKey("FraLineNpc_1_117");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			AddMoneyToCharacter(pchar, 10000);
			pchar.questTemp.State = "Fr6Olone_TakeMoney";
			AddQuestRecord("Fra_Line_6_Olone", "2");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;
		case "Step_F6_4":
			if (GetCompanionQuantity(pchar) == 1)   // Заставляем геймера избавиться от взятых кубиков.
			{
				if (GetQuestPastDayParam("questTemp") < 6)
				{
					dialog.text = StringFromKey("FraLineNpc_1_118", pchar);
					link.l1 = StringFromKey("FraLineNpc_1_119");
					link.l1.go = "Step_F6_5";
				}
				else
				{
					dialog.text = StringFromKey("FraLineNpc_1_120", pchar);
					link.l1 = StringFromKey("FraLineNpc_1_121", pchar);
					link.l1.go = "Step_F6_7";
				}
			}
			else
			{
				dialog.text = StringFromKey("FraLineNpc_1_122", pchar);
				link.l1 = StringFromKey("FraLineNpc_1_123");
				link.l1.go = "exit";
				link.l2 = StringFromKey("FraLineNpc_1_124", pchar);
				link.l2.go = "Step_F6_WantMoney";
				NextDiag.TempNode = "Step_F6_4";
			}
		break;
		case "Step_F6_5":
			dialog.text = StringFromKey("FraLineNpc_1_125");
			link.l1 = StringFromKey("FraLineNpc_1_126", pchar);
			link.l1.go = "Step_F6_6";
		break;
		case "Step_F6_6":
			dialog.text = StringFromKey("FraLineNpc_1_127");
			link.l1 = StringFromKey("FraLineNpc_1_128");
			link.l1.go = "Step_F6_GoOn";
		break;
		case "Step_F6_GoOn":
		//==> формируем эскадру
			LAi_SetActorType(NPChar);
			LAi_ActorSetStayMode(NPChar);
			CharacterIntoCompanionAndGoOut(pchar, npchar, "reload", "reload1", 5, false);
			for (i = 1; i <= 2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Captain_" + i, "officer_" + (rand(9) + 11), "man", "man", 20, FRANCE, -1, true)); //watch_quest_moment
				FantomMakeCoolSailor(sld, SHIP_CORVETTE, "", CANNON_TYPE_CANNON_LBS24, 70, 70, 70);
				FantomMakeCoolFighter(sld, 20, 90, 70, BLADE_LONG, "pistol4", 120);
				sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
				sld.CompanionEnemyEnable = false;
				sld.Abordage.Enable = false; // НЕЛЬЗЯ!
				sld.RebirthPhantom = true;
				SetCompanionIndex(pchar, -1, sti(sld.index));
				sld.DeckDialogNode = "HaveHotBussines";
				SetCharacterRemovable(sld, false);
				LAi_LoginInCaptureTown(sld, true);
			}
			// ==> текущая дата, у генерал-губернатора Куманы потом сверим
			SaveCurrentQuestDateParam("questTemp");
			pchar.TempPerks.QuestTroopers = true; //перк квестового десанта
			// ==> капитулянтская нода губернатору Куманы
			characters[GetCharacterIndex("Cumana_Mayor")].dialog.captureNode = "FraLine6Quest_Attack";
			npchar.DeckDialogNode = "HaveHotBussines";
			AddQuestRecord("Fra_Line_6_Olone", "3");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("ся", "ась"));
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main_WithCondition(CharacterFromID("Cumana_Mayor"), "Fra_Line", "StateLines_CaptureCity_QuestMarkCondition");
		break;
		case "Step_F6_7":
			dialog.text = StringFromKey("FraLineNpc_1_129", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_130");
			link.l1.go = "Step_F6_8";
		break;
		case "Step_F6_8":
			dialog.text = StringFromKey("FraLineNpc_1_131");
			link.l1 = StringFromKey("FraLineNpc_1_132");
			link.l1.go = "Step_F6_9";
		break;
		case "Step_F6_9":
			dialog.text = StringFromKey("FraLineNpc_1_133", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_134");
			link.l1.go = "Step_F6_WantMoney";
		break;
		case "HaveHotBussines":
			dialog.text = StringFromKey("FraLineNpc_1_135");
			link.l1 = StringFromKey("FraLineNpc_1_136");
			link.l1.go = "exit";
		break;
		case "Step_F6_10":
			dialog.text = StringFromKey("FraLineNpc_1_137", pchar.name);
			link.l1 = StringFromKey("FraLineNpc_1_138");
			link.l1.go = "Step_F6_11";
		break;
		case "Step_F6_11":
			dialog.text = StringFromKey("FraLineNpc_1_139", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_140");
			link.l1.go = "Step_F6_12";
		break;
		case "Step_F6_12":
			dialog.text = StringFromKey("FraLineNpc_1_141", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_142");
			link.l1.go = "Step_F6_13";
		break;
		case "Step_F6_13":
			dialog.text = StringFromKey("FraLineNpc_1_143");
			link.l1 = StringFromKey("FraLineNpc_1_144");
			link.l1.go = "Step_F6_fight";
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "4");
		break;
		case "Step_F6_fight":
			NPChar.LifeDay = 0;
			DeleteAttribute(NPChar, "RebirthPhantom");
			for (i = 1; i <= 2; i++)
			{
				sld = characterFromId("Captain_" + i);
				sld.LifeDay = 0;
				DeleteAttribute(sld, "RebirthPhantom");
			}
			chrDisableReloadToLocation = true;
			pchar.questTemp.State = "Fr6Olone_OloneIsDead";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "Step_F6_14":
			if (sti(pchar.money) >= 200000)
			{
				dialog.text = StringFromKey("FraLineNpc_1_145");
				link.l1 = StringFromKey("FraLineNpc_1_146");
				link.l1.go = "Step_F6_15";
				link.l2 = StringFromKey("FraLineNpc_1_147", pchar);
				link.l2.go = "Step_F6_20";
			}
			else
			{
				dialog.text = StringFromKey("FraLineNpc_1_148", pchar);
				link.l1 = StringFromKey("FraLineNpc_1_149");
				link.l1.go = "Step_F6_17";
			}
		break;
		case "Step_F6_15":
			dialog.text = StringFromKey("FraLineNpc_1_150");
			link.l1 = StringFromKey("FraLineNpc_1_151");
			link.l1.go = "Step_F6_16";
			AddMoneyToCharacter(pchar, -150000);
		break;
		case "Step_F6_16":
			chrDisableReloadToLocation = true;
			NPChar.LifeDay = 0;
			DeleteAttribute(NPChar, "RebirthPhantom");
			for (i = 1; i <= 2; i++)
			{
				iTemp = GetCharacterIndex("Captain_" + i);
				if (iTemp > 0)
				{
					sld = &characters[iTemp];
					sld.LifeDay = 0;
					DeleteAttribute(sld, "RebirthPhantom");
				}
			}
			AddQuestRecord("Fra_Line_6_Olone", "5");
			pchar.questTemp.State = "Fr6Olone_OloneIsLive";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "CanFightCurLocation", -1);
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], true);
			DialogExit();
		break;
		case "Step_F6_17":
			dialog.text = StringFromKey("FraLineNpc_1_152", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_153");
			link.l1.go = "Step_F6_18";
		break;
		case "Step_F6_18":
			dialog.text = StringFromKey("FraLineNpc_1_154");
			link.l1 = StringFromKey("FraLineNpc_1_155");
			link.l1.go = "Step_F6_fight";
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "6");
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], false);
			//==> кэпов в подмогу Олоне, пенальти за попытку сшустрить.
			for (i = 1; i <= 2; i++)
			{
				iTemp = GetCharacterIndex("Captain_" + i);
				if (iTemp > 0)
				{
					sld = &characters[iTemp];
					LAi_SetWarriorType(sld);
					ChangeCharacterAddress(sld, "Cumana_town", LAi_FindRandomLocator("goto"));
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
		break;
		case "Step_F6_20":
			dialog.text = StringFromKey("FraLineNpc_1_156");
			link.l1 = StringFromKey("FraLineNpc_1_157", pchar);
			link.l1.go = "Step_F6_21";
		break;
		case "Step_F6_21":
			NPChar.LifeDay = 0;
			LAi_group_Delete("EnemyFight");
			AddQuestRecord("Fra_Line_6_Olone", "8");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("", "а"));
			LAi_LocationFightDisable(&Locations[FindLocation("Cumana_town")], false);
			//==> кэпов в подмогу Олоне, пенальти за попытку сшустрить.
			for (i = 1; i <= 2; i++)
			{
				iTemp = GetCharacterIndex("Captain_" + i);
				if (iTemp > 0)
				{
					sld = &characters[iTemp];
					sld.LifeDay = 0;
					DeleteAttribute(sld, "RebirthPhantom");
					LAi_SetWarriorType(sld);
					ChangeCharacterAddress(sld, "Cumana_town", LAi_FindRandomLocator("goto"));
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
			}
			chrDisableReloadToLocation = true;
			pchar.questTemp.State = "Fr6Olone_OloneIsDead";
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//********************************* Маркиз Бонрепо. Квест №8 **********************************
		case "Step_F8_1":
			dialog.text = StringFromKey("FraLineNpc_1_158");
			link.l1 = StringFromKey("FraLineNpc_1_159", pchar);
			link.l1.go = "Step_F8_2";
		break;
		case "Step_F8_2":
			dialog.text = StringFromKey("FraLineNpc_1_160");
			link.l1 = StringFromKey("FraLineNpc_1_161");
			link.l1.go = "Step_F8_3";
		break;
		case "Step_F8_3":
			dialog.text = StringFromKey("FraLineNpc_1_162");
			link.l1 = StringFromKey("FraLineNpc_1_163", pchar);
			link.l1.go = "Step_F8_4";
		break;
		case "Step_F8_4":
			dialog.text = StringFromKey("FraLineNpc_1_164");
			link.l1 = StringFromKey("FraLineNpc_1_165", pchar);
			link.l1.go = "Step_F8_5";
		break;
		case "Step_F8_5":
			dialog.text = StringFromKey("FraLineNpc_1_166");
			link.l1 = StringFromKey("FraLineNpc_1_167");
			link.l1.go = "Step_F8_6";
		break;
		case "Step_F8_6":
			dialog.text = StringFromKey("FraLineNpc_1_168", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_169");
			link.l1.go = "Step_F8_7";
			link.l2 = StringFromKey("FraLineNpc_1_170");
			link.l2.go = "Step_F8_Fight";
		break;
		case "Step_F8_Fight":
			CloseQuestHeader("Fra_Line_8_ThreeCorsairs");
			SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			for (i = 1; i <= 4; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Guard_" + i, "guard_fra_" + (rand(3) + 1), "man", "man", 30, FRANCE, 0, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 40, 75, 75, BLADE_LONG, "pistol3", 180);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
				ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			}
			LAi_group_AttackGroup("FRANCE_CITIZENS", LAI_GROUP_PLAYER);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "CanFightCurLocation", 10.0);
			NPChar.LifeDay = 0;
			pchar.questTemp.State = "QuestLineBreake";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "2");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;
		case "Step_F8_7":
			dialog.text = StringFromKey("FraLineNpc_1_171");
			link.l1 = StringFromKey("FraLineNpc_1_172");
			link.l1.go = "exit";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "3");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.State = "Fr8ThreeCorsairs_toSeek";
			SaveCurrentQuestDateParam("questTemp");
			// ==>  Помещаем Моргана на Антигуа и даем ноду доступа к квестам
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Henry Morgan")], "SentJons_HouseF3", "goto", "goto1");
			//HardCoffee реф диалогов Моргана
			//QuestSetCurrentNode("Henry Morgan", "FraLine8_talk");
			pchar.QuestTemp.FraLine_Morgan_task = "FraLine8_talk";
			sld = characterFromID("Henry Morgan");
			LAi_SetHuberStayType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
			LAi_SetLoginTime(sld, 0.0, 24.0);
			AddLandQuestmark_Main(sld, "Fra_Line");
			// ==>  Генерим и помещаем Джона Морриса в Бриджтаун и даем ноду доступа к квестам
			sld = GetCharacter(NPC_GenerateCharacter("John Morris", "John_Morris", "man", "man", 38, PIRATE, -1, false));
			sld.name = FindPersonalName("JohnMorris_name");
			sld.lastname = FindPersonalName("JohnMorris_lastname");
			sld.Dialog.Filename = "Quest\JohnMorris.c";
			sld.greeting = "Gr_HeadPirates";
			LAi_SetHuberType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
			LAi_SetLoginTime(sld, 0.0, 24.0);
			ChangeCharacterAddressGroup(sld, "PortSpein_houseF2", "sit", "sit1");
			LAi_LocationFightDisable(&Locations[FindLocation("PortSpein_houseF2")], true);
			TEV.JohnMorrisIsLifeInHouse = true;
			// ==>  Даем ноду доступа к квестам Джону Моррису
			QuestSetCurrentNode("John Morris", "FraLine8_talk");
			AddLandQuestmark_Main(sld, "Fra_Line");
			// ==>  Даем ноду доступа к квестам Джекмену
			//QuestSetCurrentNode("Jackman", "FraLine8_talk");
			pchar.QuestTemp.FraLine_Jackman_task = "FraLine8_talk";
			AddLandQuestmark_Main(CharacterFromID("Jackman"), "Fra_Line");
			// ==>  Оформляем счетчик посещения корсаров, в итоге должен == 3
			pchar.questTemp.Count = "0";
			AddLandQuestmark_Main_WithCondition(npchar, "Fra_Line", "FraLine_8_ThreeCorsairs_QuestMarkCondition");
			AddLandQuestmark_Main(CharacterFromID("Oliver_Green"), "Fra_Line");
		break;
		case "Step_F8_9":
			dialog.text = StringFromKey("FraLineNpc_1_173", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_174", pchar);
			link.l1.go = "Step_F8_10";
		break;
		case "Step_F8_10":
			dialog.text = StringFromKey("FraLineNpc_1_175", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_176");
			link.l1.go = "Step_F8_11";
		break;
		case "Step_F8_11":
			pchar.questTemp.State = "Fr8ThreeCorsairs_backGovernor";
			AddQuestRecord("Fra_Line_8_ThreeCorsairs", "8");
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex", GetSexPhrase(StringFromKey("SexPhrase_5"), StringFromKey("SexPhrase_6")));
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex1", GetSexPhrase("му", "й"));
			AddQuestUserData("Fra_Line_8_ThreeCorsairs", "sSex2", GetSexPhrase("ен", "на"));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", 6.0);
			if (PChar.sex == "woman")
				pchar.name = GlobalStringConvert("BaronWomanTitle") + " " + pchar.name;
			else
				pchar.name = GlobalStringConvert("BaronTitle") + " " + pchar.name;
			SetCharacterPerk(pchar, "Nobleman");
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;
		//********************************* Конец войне. Квест №12 **********************************
		case "Step_F12_1":
			dialog.text = StringFromKey("FraLineNpc_1_177");
			link.l1 = StringFromKey("FraLineNpc_1_178");
			link.l1.go = "Step_F12_2";
		break;
		case "Step_F12_2":
			dialog.text = StringFromKey("FraLineNpc_1_179");
			link.l1 = StringFromKey("FraLineNpc_1_180");
			link.l1.go = "Step_F12_3";
		break;
		case "Step_F12_3":
			dialog.text = StringFromKey("FraLineNpc_1_181");
			link.l1 = StringFromKey("FraLineNpc_1_182", pchar);
			link.l1.go = "Step_F12_4";
		break;
		case "Step_F12_4":
			dialog.text = StringFromKey("FraLineNpc_1_183", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_184");
			link.l1.go = "Step_F12_5";
		break;
		case "Step_F12_5":
			dialog.text = StringFromKey("FraLineNpc_1_185", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_186");
			link.l1.go = "Step_F12_6";
		break;
		case "Step_F12_6":
			dialog.text = StringFromKey("FraLineNpc_1_187", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_188");
			link.l1.go = "Step_F12_7";
		break;
		case "Step_F12_7":
			dialog.text = StringFromKey("FraLineNpc_1_189");
			link.l1 = StringFromKey("FraLineNpc_1_190");
			link.l1.go = "Step_F12_8";
		break;
		case "Step_F12_8":
			dialog.text = StringFromKey("FraLineNpc_1_191", pchar);
			link.l1 = StringFromKey("FraLineNpc_1_192");
			link.l1.go = "exit";
			npchar.LifeDay = 0;
			pchar.questTemp.State = "EndOfQuestLine";
			bWorldAlivePause = false; // Конец линейки
			AddQuestRecord("Fra_Line_12_EndOfWar", "2");
			AddQuestUserData("Fra_Line_12_EndOfWar", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Fra_Line_12_EndOfWar", "sSex1", GetSexPhrase("му", "й"));
			CloseQuestHeader("Fra_Line_12_EndOfWar");
			DeleteAttribute(pchar, "questTemp.Waiting_time");
			//==> в течение месяца Солей Руаяль можно взять себе.			
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			SetCrewQuantityFull(sld);
			Fantom_SetBalls(sld, "pirate");
			Group_SetType("SoleiRoyal", "war");
			Group_AddCharacter("SoleiRoyal", "SoleiRoyalCaptain");
			Group_SetGroupCommander("SoleiRoyal", "SoleiRoyalCaptain");
			Group_SetAddress("SoleiRoyal", "Guadeloupe", "Quest_ships", "quest_ship_1");
			SetTimerCondition("Fr12EndOfWar_TakeOutShip", 0, 0, 30, false);
			AddTitleNextRate(sti(NPChar.nation), 5);
			ChangeCharacterReputation(pchar, 5);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
			AddCharacterExpToSkill(pchar, "Repair", 630);
			AddCharacterExpToSkill(pchar, "Sneak", 490);
			AddCharacterExpToSkill(pchar, "FencingLight", 530);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 530);
			AddCharacterExpToSkill(pchar, "Fencing", 530);
			AddCharacterExpToSkill(pchar, "Pistol", 530);
			AddCharacterExpToSkill(pchar, "Fortune", 660);
			AddCharacterExpToSkill(pchar, "Accuracy", 520);
			AddCharacterExpToSkill(pchar, "Grappling", 750);
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			//слухи
			AddSimpleRumour(
				StringFromKey("FraLineNpc_1_193", pchar), sti(npchar.nation), 5, 1);
			Achievment_Set(ACH_Na_sluzhbe_Frantsii);
		break;
	}
}

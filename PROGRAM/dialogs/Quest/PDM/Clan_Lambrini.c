
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int Rank = sti(pchar.rank) - 4 + MOD_SKILL_ENEMY_RATE*3;
	if (Rank < 1) Rank = 1;
	int Sila = 70 + MOD_SKILL_ENEMY_RATE*3 * 3;
	int DopHP = 60 + MOD_SKILL_ENEMY_RATE*3 * 12;
	int Bonus = sti(pchar.rank);
	if (Bonus <= 6) Bonus = 1;
	if (Bonus >= 7 && Bonus <= 12) Bonus = 1.2;
	if (Bonus >= 13) Bonus = 1.5;
	int Plata1 = 20000 + 2000 * sti(pchar.rank) * Bonus;
	int Plata2 = 10000 + 1500 * sti(pchar.rank) * Bonus;
	pchar.PDM_NK_Plata1.Money = 20000 + 2000 * sti(pchar.rank) * Bonus;
	pchar.PDM_NK_Plata2.Money = 10000 + 1500 * sti(pchar.rank) * Bonus;

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":
			dialog.text = StringFromKey("Clan_Lambrini_1", pchar);
			link.l1 = StringFromKey("Clan_Lambrini_2");
			link.l1.go = "Octavio_1_1";
			link.l2 = StringFromKey("Clan_Lambrini_3");
			link.l2.go = "exit";
			// PlayVoice("Kopcapkz\Voices\PDM\Octavio Lambrini.wav");
		break;

		case "Octavio_1_1":
			dialog.text = StringFromKey("Clan_Lambrini_4");
			if (pchar.FaceId == "1001") //Питер Блад
			{
				link.l1 = StringFromKey("Clan_Lambrini_5", GetFullName(pchar));
				link.l1.go = "Octavio_1_2";
			}
			else if (pchar.FaceId == "1002") // Мишель де Граммон
			{
				link.l1 = StringFromKey("Clan_Lambrini_6", GetFullName(pchar));
				link.l1.go = "Octavio_1_2";
			}
			else if (pchar.FaceId == "1003") // Вильям Патерсон
			{
				link.l1 = StringFromKey("Clan_Lambrini_7", GetFullName(pchar));
				link.l1.go = "Octavio_1_2";
			}
			else if (pchar.FaceId == "1004") // Барт Португалец
			{
				link.l1 = StringFromKey("Clan_Lambrini_8", GetFullName(pchar));
				link.l1.go = "Octavio_1_2";
			}
			else if (pchar.FaceId == "1006") // Диего Эспиноза
			{
				link.l1 = StringFromKey("Clan_Lambrini_9", GetFullName(pchar));
				link.l1.go = "Octavio_1_2";
			}
			else if (pchar.FaceId == "1014") //Даниель Грин
			{
				link.l1 = StringFromKey("Clan_Lambrini_10", pchar, GetFullName(pchar));
				link.l1.go = "Octavio_1_2";
			}
			else if (pchar.FaceId == "1007" || pchar.FaceId == "1008") // Шарпы
			{
				link.l1 = StringFromKey("Clan_Lambrini_11", pchar, GetFullName(pchar));
				link.l1.go = "Octavio_1_2";
			}
			else if (sti(pchar.reputation) > 80) //человек чести
			{
				link.l2 = StringFromKey("Clan_Lambrini_12", GetFullName(pchar));
				link.l2.go = "Octavio_1_2";
			}
			else if (sti(pchar.reputation) < 20) //кровавый убийца
			{
				link.l2 = StringFromKey("Clan_Lambrini_13", GetFullName(pchar));
				link.l2.go = "Octavio_1_2";
			}
			link.l9 = StringFromKey("Clan_Lambrini_14", pchar, pchar.name);
			link.l9.go = "Octavio_proval";
		break;
		
		case "Octavio_1_2":
			if (pchar.FaceId == "1001") // Питер Блад
			{
				dialog.text = StringFromKey("Clan_Lambrini_15");
			}
			else if (pchar.FaceId == "1002") // Мишель де Граммон
			{
				dialog.text = StringFromKey("Clan_Lambrini_16");
			}
			else if (pchar.FaceId == "1003") // Вильям Патерсон
			{
				dialog.text = StringFromKey("Clan_Lambrini_17");
			}
			else if (pchar.FaceId == "1004") // Барт Португалец
			{
				dialog.text = StringFromKey("Clan_Lambrini_18");
			}
			else if (pchar.FaceId == "1005") // Джессика Брэдфорд
			{
				dialog.text = StringFromKey("Clan_Lambrini_19");
			}
			else if (pchar.FaceId == "1006") // Диего Эспиноза
			{
				dialog.text = StringFromKey("Clan_Lambrini_20");
			}
			else if (pchar.FaceId == "1014") // Даниель Грин
			{
				dialog.text = StringFromKey("Clan_Lambrini_21", GetFullName(pchar));
			}
			else if (pchar.FaceId == "1007" || pchar.FaceId == "1008") // Шарпы
			{
				dialog.text = StringFromKey("Clan_Lambrini_22");
			}
			else if (sti(pchar.reputation) > 80 || sti(pchar.reputation) < 20)
			{
				dialog.text = StringFromKey("Clan_Lambrini_23", GetFullName(pchar));
			}
			link.l1 = StringFromKey("Clan_Lambrini_24");
			link.l1.go = "Octavio_1_3";
		break;

		case "Octavio_proval":
			dialog.text = StringFromKey("Clan_Lambrini_25", pchar);
			link.l1 = StringFromKey("Clan_Lambrini_26", pchar);
			link.l1.go = "exit";
		break;

		case "Octavio_1_3":
			dialog.text = StringFromKey("Clan_Lambrini_27");
			link.l1 = StringFromKey("Clan_Lambrini_28");
			link.l1.go = "Octavio_1_4";
		break;

		case "Octavio_1_4":
			dialog.text = StringFromKey("Clan_Lambrini_29");
			link.l1 = StringFromKey("Clan_Lambrini_30");
			link.l1.go = "Octavio_1_5";
		break;

		case "Octavio_1_5":
			dialog.text = StringFromKey("Clan_Lambrini_31");
			link.l1 = StringFromKey("Clan_Lambrini_32");
			link.l1.go = "Octavio_1_6";
		break;

		case "Octavio_1_6":
			dialog.text = StringFromKey("Clan_Lambrini_33");
			link.l1 = StringFromKey("Clan_Lambrini_34", pchar);
			link.l1.go = "Octavio_1_7";
		break;

		case "Octavio_1_7":
			dialog.text = StringFromKey("Clan_Lambrini_35");
			link.l1 = StringFromKey("Clan_Lambrini_36");
			link.l1.go = "Octavio_1_8";
		break;

		case "Octavio_1_8":
			dialog.text = StringFromKey("Clan_Lambrini_37", Plata1);
			link.l1 = StringFromKey("Clan_Lambrini_38", pchar);
			link.l1.go = "Octavio_1_9";
			link.l2 = StringFromKey("Clan_Lambrini_39");
			link.l2.go = "exit";
		break;

		case "Octavio_1_9":
			dialog.text = StringFromKey("Clan_Lambrini_40", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Clan_Lambrini_41");
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_1_10_EsheRaz";
			RemoveLandQuestmark_Main(npchar, "PDM_Clan_Lambrini");
			
			PDM_CL_OdliSpawn();

			SetQuestHeader("PDM_Clan_Lambrini");
			AddQuestRecord("PDM_Clan_Lambrini", "1");
			AddQuestUserData("PDM_Clan_Lambrini", "sSex", GetSexPhrase("","а"));
		break;

		case "Octavio_1_10_EsheRaz":
			dialog.text = StringFromKey("Clan_Lambrini_42", pchar);
			link.l1 = StringFromKey("Clan_Lambrini_43");
			link.l1.go = "Octavio_1_11_EsheRaz";
		break;

		case "Octavio_1_11_EsheRaz":
			dialog.text = StringFromKey("Clan_Lambrini_44", pchar);
			link.l1 = StringFromKey("Clan_Lambrini_45");
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_1_10_EsheRaz";
		break;

		case "Antonio_1_1":
			dialog.text = StringFromKey("Clan_Lambrini_46", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Clan_Lambrini_47");
			link.l1.go = "Antonio_1_2";
		break;

		case "Antonio_1_2":
			dialog.text = StringFromKey("Clan_Lambrini_48", pchar);
			link.l1 = StringFromKey("Clan_Lambrini_49", GetFullName(pchar));
			link.l1.go = "Antonio_1_3";
		break;

		case "Antonio_1_3":
			dialog.text = StringFromKey("Clan_Lambrini_50");
			link.l1 = StringFromKey("Clan_Lambrini_51");
			link.l1.go = "Antonio_1_4";
			link.l2 = StringFromKey("Clan_Lambrini_52");
			link.l2.go = "Antonio_Ugroza";
			link.l3 = StringFromKey("Clan_Lambrini_53");
			link.l3.go = "exit";
			NextDiag.TempNode = "Antonio_1_1";
		break;

		case "Antonio_Ugroza":
			dialog.text = StringFromKey("Clan_Lambrini_54");
			link.l1 = StringFromKey("Clan_Lambrini_55");
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_Ugroza";
		break;

		case "Octavio_2_1":
			dialog.text = StringFromKey("Clan_Lambrini_56", pchar);
			// Проверяем, какой путь был выбран
			if (CheckAttribute(pchar, "questTemp.PDM_CL_ChoiceOdli"))
			{   // Выбрали сторону Одли (убедили) - нужна проверка харизмы
				if (GetCharacterSkill(pchar, "Sneak") >= 25 || GetCharacterSPECIAL(pchar, "Charisma") >= 5)
				{   // Харизма успешна
					link.l1 = StringFromKey("Clan_Lambrini_57");
					link.l1.go = "Octavio_2_2";
				}
				else
				{   // Харизмы не хватило - Октавио не верит
					link.l1 = StringFromKey("Clan_Lambrini_58");
					link.l1.go = "Octavio_2_2_fail";
				}
			}
			else
			{   // Убили Томаса (сторона Ламбрини) - проверка не нужна
				link.l2 = StringFromKey("Clan_Lambrini_59");
				link.l2.go = "Octavio_2_2";
			}
		break;

		case "Octavio_2_2":
			dialog.text = StringFromKey("Clan_Lambrini_60", pchar, Plata1);
			link.l1 = StringFromKey("Clan_Lambrini_61");
			if (CheckAttribute(pchar, "questTemp.PDM_CL_ChoiceOdli"))
			{	// Выбрали сторону Одли
				AddMoneyToCharacter(pchar, sti(Plata1));
				ChangeCharacterReputation(pchar, 5);
				ChangeCharacterNationReputation(pchar, ENGLAND, 5);
				AddCharacterExpToSkill(pchar, "Leadership", 70);
				AddCharacterExpToSkill(pchar, "Fortune", 70);
				AddCharacterExpToSkill(pchar, "Sneak", 70);

				AddQuestRecord("PDM_Clan_Lambrini", "4");
				RemoveLandQuestmark_Main(npchar, "PDM_Clan_Lambrini");
				
				PChar.quest.PDM_CL_Ubrat_Lodku.win_condition.l1 = "ExitFromLocation";
				PChar.quest.PDM_CL_Ubrat_Lodku.win_condition.l1.location = PChar.location;
				PChar.quest.PDM_CL_Ubrat_Lodku.function = "PDM_CL_Ubrat_Lodku";

				link.l1.go = "exit";
				NextDiag.TempNode = "Octavio_2_3_EsheRaz";
			}
			else
			{	// Выбрали сторону Ламбрини
				npchar.lifeday = 0;
				AddMoneyToCharacter(pchar, sti(Plata1));
				ChangeCharacterReputation(pchar, -10);
				ChangeCharacterNationReputation(pchar, ENGLAND, -5);
				AddCharacterExpToSkill(pchar, "Sneak", 150);
				AddCharacterExpToSkill(pchar, "Leadership", 150);
				AddCharacterExpToSkill(pchar, "Sailing", 150);
				AddCharacterExpToSkill(pchar, "Accuracy", 150);
				AddCharacterExpToSkill(pchar, "Cannons", 150);
				AddCharacterExpToSkill(pchar, "Grappling", 150);
				ChangeContrabandRelation(pchar, 25);
				
				CloseQuestHeader("PDM_Clan_Lambrini");
				RemoveLandQuestmark_Main(npchar, "PDM_Clan_Lambrini");
				RemoveMapQuestMark("PortSpein_town", "PDM_Clan_Lambrini");
				Achievment_Set(ACH_Clan_Lambrini);

				link.l1.go = "Octavio_2_3";
			}
		break;

		case "Octavio_2_3":
			dialog.text = StringFromKey("Clan_Lambrini_62", pchar);

			// Проверяем наличие перка Англии. Если нет - выводим строку диалога
			if (!CheckAttribute(pchar, "perks.list.FlagEng"))
			{
				link.l1 = StringFromKey("Clan_Lambrini_63");
				link.l1.go = "Octavio_flag_eng";
			}
			// Франция
			if (!CheckAttribute(pchar, "perks.list.FlagFra"))
			{
				link.l2 = StringFromKey("Clan_Lambrini_64");
				link.l2.go = "Octavio_flag_fra";
			}
			// Испания
			if (!CheckAttribute(pchar, "perks.list.FlagSpa"))
			{
				link.l3 = StringFromKey("Clan_Lambrini_65");
				link.l3.go = "Octavio_flag_spa";
			}
			// Голландия
			if (!CheckAttribute(pchar, "perks.list.FlagHol"))
			{
				link.l4 = StringFromKey("Clan_Lambrini_66");
				link.l4.go = "Octavio_flag_hol";
			}

			// Обработка ситуации, когда у героя УЖЕ ЕСТЬ все 4 флага
			if (CheckAttribute(pchar, "perks.list.FlagEng") && CheckAttribute(pchar, "perks.list.FlagFra") && CheckAttribute(pchar, "perks.list.FlagSpa") && CheckAttribute(pchar, "perks.list.FlagHol"))
			{
				link.l5 = StringFromKey("Clan_Lambrini_67");
				link.l5.go = "Octavio_flag_all";

			}
			link.l9 = StringFromKey("Clan_Lambrini_68");
			link.l9.go = "Octavio_2_3_bye";
		break;

		case "Octavio_flag_eng":
			dialog.text = StringFromKey("Clan_Lambrini_69");
			link.l1 = StringFromKey("Clan_Lambrini_70");
			link.l1.go = "Octavio_2_3_bye";
			SetCharacterPerk(pchar, "FlagEng"); // Выдаем перк
		break;

		case "Octavio_flag_fra":
			dialog.text = StringFromKey("Clan_Lambrini_71");
			link.l1 = StringFromKey("Clan_Lambrini_72");
			link.l1.go = "Octavio_2_3_bye";
			SetCharacterPerk(pchar, "FlagFra"); // Выдаем перк
		break;

		case "Octavio_flag_spa":
			dialog.text = StringFromKey("Clan_Lambrini_73");
			link.l1 = StringFromKey("Clan_Lambrini_74");
			link.l1.go = "Octavio_2_3_bye";
			SetCharacterPerk(pchar, "FlagSpa"); // Выдаем перк
		break;

		case "Octavio_flag_hol":
			dialog.text = StringFromKey("Clan_Lambrini_75");
			link.l1 = StringFromKey("Clan_Lambrini_76");
			link.l1.go = "Octavio_2_3_bye";
			SetCharacterPerk(pchar, "FlagHol"); // Выдаем перк
		break;

		case "Octavio_flag_all":
			dialog.text = StringFromKey("Clan_Lambrini_77");
			link.l1 = StringFromKey("Clan_Lambrini_78");
			link.l1.go = "Octavio_2_3_bye";
		break;

		case "Octavio_2_3_bye":
			dialog.text = StringFromKey("Clan_Lambrini_79", pchar);
			link.l1 = StringFromKey("Clan_Lambrini_80");
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_2_3_EsheRaz";
		break;

		// Для провала харизмы
		case "Octavio_2_2_fail":
			dialog.text = StringFromKey("Clan_Lambrini_81", pchar);
			link.l1 = StringFromKey("Clan_Lambrini_82");
			link.l1.go = "exit";

			// Провал - никаких наград
			AddQuestRecord("PDM_Clan_Lambrini", "7");
			RemoveLandQuestmark_Main(npchar, "PDM_Clan_Lambrini");

			PChar.quest.PDM_CL_Ubrat_Lodku.win_condition.l1 = "ExitFromLocation";
			PChar.quest.PDM_CL_Ubrat_Lodku.win_condition.l1.location = PChar.location;
			PChar.quest.PDM_CL_Ubrat_Lodku.function = "PDM_CL_Ubrat_Lodku";

			NextDiag.TempNode = "Octavio_2_4_EsheRaz";
		break;

		case "Octavio_2_3_EsheRaz":
			dialog.text = StringFromKey("Clan_Lambrini_83", pchar.name);
			link.l1 = StringFromKey("Clan_Lambrini_84");
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_2_3_EsheRaz";
		break;

		case "Octavio_2_4_EsheRaz":
			dialog.text = StringFromKey("Clan_Lambrini_85");
			link.l1 = StringFromKey("Clan_Lambrini_86");
			link.l1.go = "exit";
			NextDiag.TempNode = "Octavio_2_4_EsheRaz";
		break;

		case "Antonio_1_4":
			dialog.text = StringFromKey("Clan_Lambrini_87");
			link.l1 = StringFromKey("Clan_Lambrini_88", pchar);
			link.l1.go = "Antonio_1_5";
		break;

		case "Antonio_1_5":
			dialog.text = StringFromKey("Clan_Lambrini_89");
			link.l1 = StringFromKey("Clan_Lambrini_90", pchar);
			link.l1.go = "Antonio_1_6";
			link.l2 = StringFromKey("Clan_Lambrini_91");
			link.l2.go = "exit";
		break;

		case "Antonio_1_6":
			dialog.text = StringFromKey("Clan_Lambrini_92");
			link.l1 = StringFromKey("Clan_Lambrini_93", pchar);
			link.l1.go = "Antonio_1_7";
		break;

		case "Antonio_1_7":
			dialog.text = StringFromKey("Clan_Lambrini_94", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Clan_Lambrini_95");
			link.l1.go = "Antonio_1_8";
			link.l2 = StringFromKey("Clan_Lambrini_96");
			link.l2.go = "exit";
		break;

		case "Antonio_1_8":
			dialog.text = StringFromKey("Clan_Lambrini_97", GetAddress_Form(NPChar), pchar.name);
			link.l1 = StringFromKey("Clan_Lambrini_98");
			link.l1.go = "Antonio_1_9";
		break;

		case "Antonio_1_9":
			dialog.text = StringFromKey("Clan_Lambrini_99", Plata2);
			link.l1 = StringFromKey("Clan_Lambrini_100", Plata2);
			link.l1.go = "Antonio_1_10";
			link.l2 = StringFromKey("Clan_Lambrini_101", Plata2);
			link.l2.go = "exit";
		break;

		case "Antonio_1_10":
			dialog.text = StringFromKey("Clan_Lambrini_102");
			link.l1 = StringFromKey("Clan_Lambrini_103");
			link.l1.go = "Antonio_1_11";
		break;

		case "Antonio_1_11":
			sld = CharacterFromID("PDM_Odli");
			sld.AlwaysFriend = true;
			sld.ShipEnemyDisable  = true;
			sld.Abordage.Enable = false;
			LAi_SetImmortal(sld, true);
			
			sld = CharacterFromID("PDM_Octavio_Lambrini");
			sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
			sld.dialog.currentnode   = "Octavio_2_1";
			AddLandQuestMark_Main(sld, "PDM_Clan_Lambrini");
			DeleteQuestCondition("PDM_CL_Odli_Ubit");
			pchar.questTemp.PDM_CL_ChoiceOdli = true;
			AddQuestRecord("PDM_Clan_Lambrini", "3");

			NextDiag.CurrentNode = "Antonio_1_again";
			DialogExit();
		break;

		case "Antonio_1_again":
			dialog.text = StringFromKey("Clan_Lambrini_104");
			link.l1 = StringFromKey("Clan_Lambrini_105");
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_1_again";
		break;

		case "Antonio_2_1":
			dialog.text = StringFromKey("Clan_Lambrini_106", TimeGreeting(), GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Clan_Lambrini_107");
			link.l1.go = "Antonio_2_2";
		break;

		case "Antonio_2_2":
			dialog.text = StringFromKey("Clan_Lambrini_108", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Clan_Lambrini_109");
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_2_3_EsheRaz";

			FreeSitLocator("PortSpein_tavern", "sit_base1");
			FreeSitLocator("PortSpein_tavern", "sit_base2");
			FreeSitLocator("PortSpein_tavern", "sit_front2");
			
			RemoveLandQuestmark_Main(npchar, "PDM_Clan_Lambrini");
			sld = CharacterFromID("PDM_Octavio_Lambrini");
			ChangeCharacterAddressGroup(sld, "PortSpein_tavern", "sit", "sit_front2");

			PDM_CL_ClientSpawnInTavern();

			AddQuestRecord("PDM_Clan_Lambrini", "5");
			SetFunctionLocationCondition("PDM_CL_TavernKino", "PortSpein_tavern", false);
		break;

		case "Antonio_2_3_EsheRaz":
			dialog.text = StringFromKey("Clan_Lambrini_110", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Clan_Lambrini_111", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "Antonio_2_3_EsheRaz";
		break;

		case "Octavio_4_1":
			dialog.text = StringFromKey("Clan_Lambrini_112");
			link.l1 = StringFromKey("Clan_Lambrini_113");
			link.l1.go = "Octavio_4_2";

			if (!CharacterIsHere("PDM_CL_Pokupatel"))
			{
				FreeSitLocator("PortSpein_tavern", "sit_base2");
				PDM_CL_ClientSpawnInTavern();
			}
		break;

		case "Octavio_4_2":
			dialog.text = StringFromKey("Clan_Lambrini_114");
			link.l1 = StringFromKey("Clan_Lambrini_115");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_CL_TavernKino_3");
		break;

		case "Antonio_5_1":
			dialog.text = StringFromKey("Clan_Lambrini_116", UpperFirst(GetAddress_Form(NPChar)), pchar.name);
			link.l1 = StringFromKey("Clan_Lambrini_117", pchar);
			link.l1.go = "Antonio_5_2";
		break;

		case "Antonio_5_2":
			dialog.text = StringFromKey("Clan_Lambrini_118");
			link.l1 = StringFromKey("Clan_Lambrini_119");
			link.l1.go = "Antonio_5_3";
			Pchar.GenQuest.Hunter2Pause = true;
		break;

		case "Antonio_5_3":
			dialog.text = StringFromKey("Clan_Lambrini_120");
			link.l1 = StringFromKey("Clan_Lambrini_121");
			link.l1.go = "Antonio_5_4";
			link.l2 = StringFromKey("Clan_Lambrini_122");
			link.l2.go = "exit";
			NextDiag.TempNode = "Antonio_5_again";
		break;
		
		case "Antonio_5_again":
			dialog.text = StringFromKey("Clan_Lambrini_123");
			link.l1 = StringFromKey("Clan_Lambrini_124");
			link.l1.go = "Antonio_5_4";
			link.l2 = StringFromKey("Clan_Lambrini_125");
			link.l2.go = "exit";
			NextDiag.TempNode = "Antonio_5_again";
		break;

		case "Antonio_5_4":
			dialog.text = StringFromKey("Clan_Lambrini_126");
			link.l1 = StringFromKey("Clan_Lambrini_127");
			link.l1.go = "Antonio_5_5";
		break;

		case "Antonio_5_5":
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "PDM_Clan_Lambrini");
			AddDialogExitQuestFunction("PDM_CL_OnShore");
		break;

		case "Pokupatel_6_1":
			dialog.text = StringFromKey("Clan_Lambrini_128");
			link.l1 = StringFromKey("Clan_Lambrini_129");
			link.l1.go = "Pokupatel_6_2";
		break;

		case "Pokupatel_6_2":
			dialog.text = StringFromKey("Clan_Lambrini_130");
			link.l1 = StringFromKey("Clan_Lambrini_131");
			link.l1.go = "Pokupatel_6_3";
		break;

		case "Pokupatel_6_3":
			dialog.text = StringFromKey("Clan_Lambrini_132", pchar);
			link.l1 = StringFromKey("Clan_Lambrini_133");
			link.l1.go = "Pokupatel_6_4";
		break;

		case "Pokupatel_6_4":
			dialog.text = StringFromKey("Clan_Lambrini_134");
			link.l1 = StringFromKey("Clan_Lambrini_135");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_CL_OnShore_8");
		break;

		case "Antonio_8_1":
			dialog.text = StringFromKey("Clan_Lambrini_136");
			link.l1 = StringFromKey("Clan_Lambrini_137");
			link.l1.go = "Antonio_8_2";
		break;

		case "Antonio_8_2":
			dialog.text = StringFromKey("Clan_Lambrini_138", Plata2);
			link.l1 = StringFromKey("Clan_Lambrini_139", pchar);
			link.l1.go = "Antonio_8_3";
			AddMoneyToCharacter(pchar, sti(Plata2));
			ChangeContrabandRelation(pchar, -20); //репу контры вниз
		break;
		case "Antonio_8_3":
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_CharacterDisableDialog(npchar);
			Achievment_Set(ACH_Clan_Lambrini);
			AddDialogExitQuestFunction("PDM_CL_FinalNagrada");
			AddQuestRecord("PDM_Clan_Lambrini", "8");
		break;
	}
}

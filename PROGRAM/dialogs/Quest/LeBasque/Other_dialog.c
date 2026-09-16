void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iShipSlot;
	int iShipIndex;
	int iFreeSlots;
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{

		case "First time":
			sld = characterFromId("Mayak_Bandit_1");
			LAi_ActorTurnToCharacter(sld, characterFromID("Mayak_Bandit_3"));
			dialog.text = StringFromKey("Other_dialog_11");
			link.l1 = "...";
			link.l1.go = "dialog_exit";
		break;

		case "dialog_exit":
			AddDialogExitQuest("Shadow_of_a_big_deal_43");
			dialogexit();
		break;

		case "dialog_1":
			sld = characterFromId("Mayak_Bandit_1");
			LAi_ActorTurnToLocator(sld, "goto", "bask7");
			dialog.text = StringFromKey("Other_dialog_12");
			link.l1 = "...";
			link.l1.go = "dialog_1_exit";
		break;

		case "dialog_1_exit":
			AddDialogExitQuest("Shadow_of_a_big_deal_48");
			dialogexit();
		break;

		case "dialog_2":
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_13");
			link.l1.go = "dialog_3";
		break;

		case "dialog_3":
			dialog.text = StringFromKey("Other_dialog_14", pchar);
			link.l1 = StringFromKey("Other_dialog_15");
			link.l1.go = "dialog_3_exit";
		break;

		case "dialog_3_exit":
			AddDialogExitQuest("Shadow_of_a_big_deal_50");
			dialogexit();
		break;

		case "Spa_1":
			dialog.text = StringFromKey("Other_dialog_16");
			link.l1 = StringFromKey("Other_dialog_17");
			link.l1.go = "Spa_2";
		break;

		case "Spa_2":
			dialog.text = StringFromKey("Other_dialog_18");
			link.l1 = StringFromKey("Other_dialog_19");
			link.l1.go = "Spa_3";
		break;

		case "Spa_3":
			dialog.text = StringFromKey("Other_dialog_20");
			link.l1 = StringFromKey("Other_dialog_21");
			link.l1.go = "Spa_4";
		break;

		case "Spa_4":
			dialog.text = StringFromKey("Other_dialog_22");
			link.l1 = StringFromKey("Other_dialog_23");
			link.l1.go = "Spa_4_exit";
		break;

		case "Spa_4_exit":
			AddDialogExitQuest("Old_campfire_28");
			dialogexit();
		break;

		case "Spa_5":
			dialog.text = StringFromKey("Other_dialog_24");
			link.l1 = "...";
			link.l1.go = "Spa_5_exit";
		break;

		case "Spa_5_exit":
			AddDialogExitQuest("Old_campfire_31");
			dialogexit();
		break;

		case "Pirate_ExitTown_1":
			dialog.text = StringFromKey("Other_dialog_25");
			link.l1 = StringFromKey("Other_dialog_26");
			link.l1.go = "Pirate_ExitTown_2";
		break;

		case "Pirate_ExitTown_2":
			if (GetCharacterSPECIAL(pchar, "Charisma") > 6) // обаяние норм
			{
				PlayerRPGCheck_SPECIAL_NotifyPass("Charisma");
				dialog.text = StringFromKey("Other_dialog_27", pchar);
				link.l1 = StringFromKey("Other_dialog_28");
				link.l1.go = "Pirate_ExitTown_2_1";
			}
			else // обаяние меньше
			{
				PlayerRPGCheck_SPECIAL_NotifyFailNeed("Charisma", 6); // проверка не пройдена
				dialog.text = StringFromKey("Other_dialog_29");
				link.l1 = StringFromKey("Other_dialog_30");
				link.l1.go = "Pirate_ExitTown_2_2";
			}
		break;

		case "Pirate_ExitTown_2_1":
			AddDialogExitQuest("Old_campfire_80_1");
			dialogexit();
		break;

		case "Pirate_ExitTown_2_2":
			AddDialogExitQuest("Old_campfire_80_1_1");
			dialogexit();
		break;

		case "Leru_1":
			RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
			dialog.text = StringFromKey("Other_dialog_31");
			link.l1 = StringFromKey("Other_dialog_32");
			link.l1.go = "Leru_2";
		break;

		case "Leru_2":
			dialog.text = StringFromKey("Other_dialog_33");
			link.l1 = StringFromKey("Other_dialog_34");
			link.l1.go = "Leru_3";
		break;

		case "Leru_3":
			dialog.text = StringFromKey("Other_dialog_35");
			link.l1 = StringFromKey("Other_dialog_36");
			link.l1.go = "Leru_4";
		break;

		case "Leru_4":
			dialog.text = StringFromKey("Other_dialog_37");
			link.l1 = StringFromKey("Other_dialog_38");
			link.l1.go = "Leru_4_exit";
		break;

		case "Leru_4_exit":
			AddDialogExitQuestFunction("StartLaPaloma");
			dialogexit();
		break;

		case "Leru_5":
			dialog.text = StringFromKey("Other_dialog_39");
			link.l1 = "...";
			link.l1.go = "Leru_5_exit";
		break;

		case "Leru_5_exit":
			dialogexit();
		break;

		// Эстебан Молина.
		case "Molina_1":
			dialog.text = StringFromKey("Other_dialog_40");
			link.l1 = StringFromKey("Other_dialog_41");
			link.l1.go = "Molina_2";
		break;

		case "Molina_2":
			dialog.text = StringFromKey("Other_dialog_42");
			link.l1 = StringFromKey("Other_dialog_43");
			link.l1.go = "Molina_3";
		break;

		case "Molina_3":
			GiveItem2Character(pchar, "casket");
			LogSound_WithNotify(StringFromKey("InfoMessages_240", GetItemName("casket"), 1), "Important_item", "Icollection");
			dialog.text = StringFromKey("Other_dialog_44");
			link.l1 = StringFromKey("Other_dialog_45");
			link.l1.go = "Molina_4";
		break;

		case "Molina_4":
			dialog.text = StringFromKey("Other_dialog_46");
			link.l1 = StringFromKey("Other_dialog_47");
			link.l1.go = "Molina_4_exit";
		break;

		case "Molina_4_exit":
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			AddDialogExitQuestFunction("Molina_TakePrisoner");
			dialogexit();
		break;

		case "Hunting_huntsman_Molina_1":
			CharacterTurnByChr(pchar, npchar);

			dialog.text = StringFromKey("Other_dialog_48");
			link.l1 = "...";
			link.l1.go = "Hunting_huntsman_Molina_1_exit";
		break;

		case "Hunting_huntsman_Molina_1_exit":
			sld = CharacterFromID("Mishel_le_Bask");

			sld.Dialog.Filename = "Quest\LeBasque\LeBasque_dialog.c";
			sld.Dialog.CurrentNode = "Hunting_huntsman_14";

			CharacterTurnByChr(pchar, sld);

			LAi_SetActorType(pchar);
			LAi_ActorDialog(pchar, sld, "", -1, 0);
			dialogexit();
		break;

		// Пиратусы в гроте
		case "Spain_grot_2":
			dialog.text = StringFromKey("Other_dialog_49");
			link.l1 = StringFromKey("Other_dialog_50");
			link.l1.go = "Spain_grot_2_exit";
		break;

		case "Spain_grot_2_exit":
			AddDialogExitQuest("Hunting_huntsman_14");
			DialogExit();
		break;

		// Мартин Кесада
		case "Martin_Kesada_1":
			sld = characterFromID("Etien_Marso");
			DeleteAttribute(sld, "FreeFighter");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, characterFromID("Martin_Kesada_Officer"), "", -1);
			RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");

			dialog.text = StringFromKey("Other_dialog_51");
			link.l1 = StringFromKey("Other_dialog_52");
			link.l1.go = "Martin_Kesada_2";
		break;

		case "Martin_Kesada_2":
			dialog.text = StringFromKey("Other_dialog_53", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Other_dialog_54");
			link.l1.go = "Martin_Kesada_3";
		break;

		case "Martin_Kesada_3":
			dialog.text = StringFromKey("Other_dialog_55");
			link.l1 = StringFromKey("Other_dialog_56");
			link.l1.go = "Martin_Kesada_4";
		break;

		case "Martin_Kesada_4":
			dialog.text = StringFromKey("Other_dialog_57");
			link.l1 = StringFromKey("Other_dialog_58");
			link.l1.go = "Martin_Kesada_5";
		break;

		case "Martin_Kesada_5":
			dialog.text = StringFromKey("Other_dialog_59");
			link.l1 = StringFromKey("Other_dialog_60");
			link.l1.go = "Martin_Kesada_6";
		break;

		case "Martin_Kesada_6":
			dialog.text = StringFromKey("Other_dialog_61");
			link.l1 = "...";
			link.l1.go = "Martin_Kesada_4_exit";
		break;

		case "Martin_Kesada_4_exit":
			AddDialogExitQuest("Hunting_huntsman_29");
			dialogexit();
		break;

		case "Martin_Kesada_cap_1":
			dialog.text = StringFromKey("Other_dialog_62");
			link.l1 = StringFromKey("Other_dialog_63");
			link.l1.go = "Martin_Kesada_cap_2";
		break;

		case "Martin_Kesada_cap_2":
			dialog.text = StringFromKey("Other_dialog_64");
			link.l1 = StringFromKey("Other_dialog_65");
			link.l1.go = "Martin_Kesada_cap_3_exit";
		break;

		case "Martin_Kesada_cap_3_exit":
		LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			dialogexit();
		break;

		// Бартоломео
		case "Bartolomeo_1":
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_66");
			link.l1.go = "Bartolomeo_2";
		break;

		case "Bartolomeo_2":
			dialog.text = StringFromKey("Other_dialog_67");
			link.l1 = StringFromKey("Other_dialog_68");
			link.l1.go = "Bartolomeo_3";
		break;

		case "Bartolomeo_3":
			dialog.text = StringFromKey("Other_dialog_69");
			if (sti(pchar.money) >= 2000)
			{
				link.l1 = StringFromKey("Other_dialog_70");
				link.l1.go = "Bartolomeo_4_money";
			}
			else
			{
				link.l1 = StringFromKey("Other_dialog_71");
				link.l1.go = "Bartolomeo_4_threat";
			}
		break;

		case "Bartolomeo_4_money":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = StringFromKey("Other_dialog_72");
			link.l1 = StringFromKey("Other_dialog_73");
			link.l1.go = "Bartolomeo_4_exit";
		break;

		case "Bartolomeo_4_threat":
			ChangeCharacterReputation(pchar, -5);
			dialog.text = StringFromKey("Other_dialog_74");
			link.l1 = StringFromKey("Other_dialog_75");
			link.l1.go = "Bartolomeo_4_exit";
		break;

		case "Bartolomeo_4_exit":
			RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuest("Hunting_huntsman_42");
			dialogexit();
		break;

		// Связной 
		case "Messenger_1":
			dialog.text = StringFromKey("Other_dialog_76", pchar);
			link.l1 = StringFromKey("Other_dialog_77");
			link.l1.go = "Messenger_2";
		break;

		case "Messenger_2":
			dialog.text = StringFromKey("Other_dialog_78");
			link.l1 = StringFromKey("Other_dialog_79");
			link.l1.go = "Messenger_3";
		break;

		case "Messenger_3":
			dialog.text = StringFromKey("Other_dialog_80");
			link.l1 = StringFromKey("Other_dialog_81");
			link.l1.go = "Messenger_4";
		break;

		case "Messenger_4":
		GiveItem2Character(pchar, "venezi_cehin");
			dialog.text = StringFromKey("Other_dialog_82");
			link.l1 = StringFromKey("Other_dialog_83");
			link.l1.go = "Messenger_4_exit";
		break;

		case "Messenger_4_exit":
		AddDialogExitQuest("Hunting_huntsman_50");
			dialogexit();
		break;

		case "Messenger_5":
			dialog.text = StringFromKey("Other_dialog_84");
			link.l1 = StringFromKey("Other_dialog_85");
			link.l1.go = "Messenger_5_exit";
		break;

		case "Messenger_5_exit":
		AddDialogExitQuest("Hunting_huntsman_54");
			dialogexit();
		break;

		// Игнасио Вела
		case "Vela_1":
			dialog.text = StringFromKey("Other_dialog_86");
			link.l1 = "...";
			link.l1.go = "Vela_1_exit";
		break;

		case "Vela_1_exit":
		AddDialogExitQuest("Hunting_huntsman_65");
			dialogexit();
		break;

		case "Vela_2":
			dialog.text = StringFromKey("Other_dialog_87");
			link.l1 = StringFromKey("Other_dialog_88");
			link.l1.go = "Vela_4";
		break;

		case "Vela_4":
			dialog.text = StringFromKey("Other_dialog_89");
			link.l1 = StringFromKey("Other_dialog_90");
			link.l1.go = "Vela_4_exit";
		break;

		case "Vela_4_exit":
			AddDialogExitQuest("Hunting_huntsman_67");
			dialogexit();
		break;

		case "Rohas_1":
			RemoveLandQuestmark_Main(npchar, "Hunting_huntsman");
			dialog.text = StringFromKey("Other_dialog_91", pchar);
			link.l1 = StringFromKey("Other_dialog_92");
			link.l1.go = "Rohas_2";
		break;

		case "Rohas_2":
			dialog.text = StringFromKey("Other_dialog_93");
			link.l1 = StringFromKey("Other_dialog_94");
			link.l1.go = "Rohas_3";
		break;

		case "Rohas_3":
			dialog.text = StringFromKey("Other_dialog_95");
			link.l1 = StringFromKey("Other_dialog_96");
			link.l1.go = "Rohas_3_exit";
		break;

		case "Rohas_3_exit":
			AddDialogExitQuest("Hunting_huntsman_89");
			dialogexit();
		break;

		case "Rohas_4":
			dialog.text = StringFromKey("Other_dialog_97");
			link.l1 = "...";
			link.l1.go = "Rohas_5_exit";
		break;

		case "Rohas_5_exit":
			AddDialogExitQuest("Hunting_huntsman_91");
			dialogexit();
		break;

		// Тессье. Писарь Ожерона.
		case "Tessie_1":
			RemoveLandQuestmark_Main(npchar, "Brides_Tortuga");
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_98");
			link.l1.go = "Tessie_2";
		break;

		case "Tessie_2":
			dialog.text = StringFromKey("Other_dialog_99");
			link.l1 = StringFromKey("Other_dialog_100", pchar);
			link.l1.go = "Tessie_3";
		break;

		case "Tessie_3":
			dialog.text = StringFromKey("Other_dialog_101");
			link.l1 = StringFromKey("Other_dialog_102");
			link.l1.go = "Tessie_4";
		break;

		case "Tessie_4":
			dialog.text = StringFromKey("Other_dialog_103");
			link.l1 = StringFromKey("Other_dialog_104");
			link.l1.go = "Tessie_5";
		break;

		case "Tessie_5":
			dialog.text = StringFromKey("Other_dialog_105");
			link.l1 = StringFromKey("Other_dialog_106");
			link.l1.go = "Tessie_6_exit";
		break;

		case "Tessie_6_exit":
			AddDialogExitQuest("Brides_Tortuga_4");
			NextDiag.CurrentNode = "Tessie_second";
			dialogexit();
		break;

		case "Tessie_second":
			dialog.text = StringFromKey("Other_dialog_107");
			link.l1 = StringFromKey("Other_dialog_108");
			link.l1.go = "Tessie_second_exit";
		break;

		case "Tessie_second_exit":
			NextDiag.CurrentNode = "Tessie_second";
			dialogexit();
		break;

		case "Tessie_7":
			RemoveLandQuestmark_Main(npchar, "Brides_Tortuga");
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_109");
			link.l1.go = "Tessie_8";
		break;

		case "Tessie_8":
			dialog.text = StringFromKey("Other_dialog_110");
			link.l1 = StringFromKey("Other_dialog_111");
			link.l1.go = "Tessie_9";
		break;

		case "Tessie_9":
			dialog.text = StringFromKey("Other_dialog_112");
			link.l1 = StringFromKey("Other_dialog_113");
			link.l1.go = "Tessie_10";
		break;

		case "Tessie_10":
			dialog.text = StringFromKey("Other_dialog_114");
			link.l1 = StringFromKey("Other_dialog_115");
			link.l1.go = "Tessie_10_exit";
		break;

		case "Tessie_10_exit":
			PlaySound("Quest\LeBask\Bask5.mp3");
			sld = GetCharacter(NPC_GenerateCharacter("Assassins_Vargas_1", "killer_1", "man", "man", CB_Rank()*2, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank()*2, CB_Fencing()*2, CB_Pistol()*2, "blade34", "pistol5", 100);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_Graveyard", "goto", "goto6");
			sld = GetCharacter(NPC_GenerateCharacter("Assassins_Vargas_2", "killer_6", "man", "man", CB_Rank()*2, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank()*2, CB_Fencing()*2, CB_Pistol()*2, "blade14", "pistol5", 100);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_Graveyard", "goto", "goto1");
			sld = GetCharacter(NPC_GenerateCharacter("Assassins_Vargas_3", "killer_3", "man", "man", CB_Rank()*2, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank()*2, CB_Fencing()*2, CB_Pistol()*2, "topor1", "pistol6", 90);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_Graveyard", "goto", "goto1");
			sld = GetCharacter(NPC_GenerateCharacter("Assassins_Vargas_4", "Killer_8_mush", "man", "mushketer", CB_Rank()*2, SPAIN, -1, true));
			FantomMakeCoolFighter(sld, CB_Rank(), CB_Fencing()*2, CB_Pistol()*2, "unarmed", "mushket", 20);
			CB_Perks(sld);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Tortuga_Graveyard", "goto", "goto1");
			dialogexit();
			AddDialogExitQuest("Brides_Tortuga_9");
		break;

		case "Tessie_11":
			dialog.text = StringFromKey("Other_dialog_116");
			link.l1 = StringFromKey("Other_dialog_117");
			link.l1.go = "Tessie_11_exit";
		break;

		case "Tessie_11_exit":
		AddDialogExitQuest("Brides_Tortuga_12");
			dialogexit();
		break;

		case "Tessie_12":
			dialog.text = StringFromKey("Other_dialog_118");
			link.l1 = StringFromKey("Other_dialog_119");
			link.l1.go = "Tessie_13";
		break;

		case "Tessie_13":
			dialog.text = StringFromKey("Other_dialog_120");
			link.l1 = StringFromKey("Other_dialog_121");
			link.l1.go = "Tessie_14";
		break;

		case "Tessie_14":
			dialog.text = StringFromKey("Other_dialog_122");
			link.l1 = StringFromKey("Other_dialog_123");
			link.l1.go = "Tessie_15";
		break;

		case "Tessie_15":
			dialog.text = StringFromKey("Other_dialog_124");
			link.l1 = StringFromKey("Other_dialog_125");
			link.l1.go = "Tessie_16";
		break;

		case "Tessie_16":
			dialog.text = StringFromKey("Other_dialog_126");
			link.l1 = StringFromKey("Other_dialog_127");
			link.l1.go = "Tessie_16_exit";
		break;

		case "Tessie_16_exit":
			AddDialogExitQuest("Brides_Tortuga_18");
			dialogexit();
		break;

		// молодой на Тортуге
		case "Kid_1":
			dialog.text = StringFromKey("Other_dialog_128");
			link.l1 = StringFromKey("Other_dialog_129");
			link.l1.go = "Kid_2";
		break;

		case "Kid_2":
			dialog.text = StringFromKey("Other_dialog_130");
			link.l1 = StringFromKey("Other_dialog_131");
			link.l1.go = "Kid_3";
		break;

		case "Kid_3":
			GiveItem2Character(pchar, "strange_note");
			dialog.text = StringFromKey("Other_dialog_132");
			link.l1 = StringFromKey("Other_dialog_133");
			link.l1.go = "Kid_4";
		break;

		case "Kid_4":
			dialog.text = StringFromKey("Other_dialog_134");
			link.l1 = StringFromKey("Other_dialog_135");
			link.l1.go = "Kid_5";
		break;

		case "Kid_5":
			dialog.text = StringFromKey("Other_dialog_136");
			link.l1 = StringFromKey("Other_dialog_137");
			link.l1.go = "Kid_5_exit";
		break;

		case "Kid_5_exit":
			chrDisableReloadToLocation = false; // открыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "none", "", "", "", -1);
			dialogexit();
		break;

		// Начальник левых французов - Делакруа
		case "Luc_Delacroix_1":
			dialog.text = StringFromKey("Other_dialog_138", pchar);
			link.l1 = StringFromKey("Other_dialog_139", pchar);
			link.l1.go = "Luc_Delacroix_2";
		break;

		case "Luc_Delacroix_2":
			dialog.text = StringFromKey("Other_dialog_140", pchar);
			link.l1 = StringFromKey("Other_dialog_141");
			link.l1.go = "Luc_Delacroix_3";
		break;

		case "Luc_Delacroix_3":
			dialog.text = StringFromKey("Other_dialog_142");
			link.l1 = StringFromKey("Other_dialog_143");
			link.l1.go = "Luc_Delacroix_4";
		break;

		case "Luc_Delacroix_4":
			dialog.text = StringFromKey("Other_dialog_144");
			link.l1 = "...";
			link.l1.go = "Luc_Delacroix_4_exit";
		break;

		case "Luc_Delacroix_4_exit":
			AddDialogExitQuest("Brides_Tortuga_24");
			dialogexit();
		break;

		// Боцман Пьер
		case "Bertran_Waband_1":
			dialog.text = StringFromKey("Other_dialog_145");
			link.l1 = StringFromKey("Other_dialog_146");
			link.l1.go = "Bertran_Waband_2";
		break;

		case "Bertran_Waband_2":
			dialog.text = StringFromKey("Other_dialog_147");
			link.l1 = StringFromKey("Other_dialog_148");
			link.l1.go = "Bertran_Waband_3";
		break;

		case "Bertran_Waband_3":
			dialog.text = StringFromKey("Other_dialog_149");
			link.l1 = StringFromKey("Other_dialog_150");
			link.l1.go = "Bertran_Waband_3_exit";
		break;

		case "Bertran_Waband_3_exit":
		AddDialogExitQuest("Brides_Tortuga_26");
			dialogexit();
		break;

		case "Bertran_Waband_4":
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_151");
			link.l1.go = "Bertran_Waband_5";
		break;

		case "Bertran_Waband_5":
			dialog.text = StringFromKey("Other_dialog_152");
			link.l1 = StringFromKey("Other_dialog_153");
			link.l1.go = "Bertran_Waband_5_exit";
		break;

		case "Bertran_Waband_5_exit":
			AddDialogExitQuest("Brides_Tortuga_28");
			dialogexit();
		break;

		// Умирающий Кэп
		case "Esteban_Ruiz_1":
			RemoveLandQuestmark_Main(npchar, "Brides_Tortuga");
			locCameraFromToPos(-2.7, 14.5, 8.8, false, -5.8, 14, 7.9);
			dialog.text = StringFromKey("Other_dialog_154");
			link.l1 = StringFromKey("Other_dialog_155");
			link.l1.go = "Esteban_Ruiz_2";
		break;

		case "Esteban_Ruiz_2":
			dialog.text = StringFromKey("Other_dialog_156");
			link.l1 = StringFromKey("Other_dialog_157");
			link.l1.go = "Esteban_Ruiz_3";
		break;

		case "Esteban_Ruiz_3":
			dialog.text = StringFromKey("Other_dialog_158");
			link.l1 = StringFromKey("Other_dialog_159");
			link.l1.go = "Esteban_Ruiz_4";
		break;

		case "Esteban_Ruiz_4":
			dialog.text = StringFromKey("Other_dialog_160");
			link.l1 = StringFromKey("Other_dialog_161");
			link.l1.go = "Esteban_Ruiz_5";
		break;

		case "Esteban_Ruiz_5":
			dialog.text = StringFromKey("Other_dialog_162");
			link.l1 = StringFromKey("Other_dialog_163");
			link.l1.go = "Esteban_Ruiz_6";
		break;

		case "Esteban_Ruiz_6":
			dialog.text = StringFromKey("Other_dialog_164");
			link.l1 = StringFromKey("Other_dialog_165");
			link.l1.go = "Esteban_Ruiz_7";
		break;

		case "Esteban_Ruiz_7":
			dialog.text = StringFromKey("Other_dialog_166");
			link.l1 = "...";
			link.l1.go = "Esteban_Ruiz_5_exit";
		break;

		case "Esteban_Ruiz_5_exit":
			PlayVoice("PEOPLE FIGHT\Death_NPC_02.wav");
			LAi_SetActorType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "Ground_Death1", "", 3);
			DoQuestCheckDelay("Brides_Tortuga_40", 3.0);
			dialogexit();
		break;

		// офицер Варгаса
		case "Officer_Vargas_1":
			dialog.text = StringFromKey("Other_dialog_167");
			link.l1 = StringFromKey("Other_dialog_168");
			link.l1.go = "Officer_Vargas_2";
		break;

		case "Officer_Vargas_2":
			dialog.text = StringFromKey("Other_dialog_169", pchar);
			link.l1 = "...";
			link.l1.go = "Officer_Vargas_2_exit";
		break;

		case "Officer_Vargas_2_exit":
			sld = characterFromId("Etien_Marso");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_Mine", "goto", "goto1");
			PlaySound("People Fight\PistolFire.wav");
			AddDialogExitQuest("Brides_Tortuga_52");
			dialogexit();
		break;

		case "Mass_dialog_1":
			dialog.text = StringFromKey("Other_dialog_170");
			link.l1 = "...";
			link.l1.go = "Mass_dialog_1_exit";
		break;

		case "Mass_dialog_1_exit":
			AddDialogExitQuest("Royal_jackpot_24");
			dialogexit();
		break;

		case "Mass_dialog_2":
			dialog.text = StringFromKey("Other_dialog_171");
			link.l1 = "...";
			link.l1.go = "Mass_dialog_2_exit";
		break;

		case "Mass_dialog_2_exit":
			AddDialogExitQuest("Royal_jackpot_25");
			dialogexit();
		break;

		case "Mass_dialog_3":
			dialog.text = StringFromKey("Other_dialog_172");
			link.l1 = "...";
			link.l1.go = "Mass_dialog_3_exit";
		break;

		case "Mass_dialog_3_exit":
			AddDialogExitQuest("Royal_jackpot_26");
			dialogexit();
		break;

		case "Mass_dialog_4":
			dialog.text = StringFromKey("Other_dialog_173");
			link.l1 = StringFromKey("Other_dialog_174");
			link.l1.go = "Mass_dialog_4_exit";
		break;

		case "Mass_dialog_4_exit":
			AddDialogExitQuest("Royal_jackpot_27");
			dialogexit();
		break;

		case "Mass_dialog_5":
			dialog.text = StringFromKey("Other_dialog_175");
			link.l1 = "...";
			link.l1.go = "Mass_dialog_5_exit";
		break;

		case "Mass_dialog_5_exit":
			AddDialogExitQuest("Royal_jackpot_29");
			dialogexit();
		break;

		case "Mass_dialog_6":
			dialog.text = StringFromKey("Other_dialog_176");
			link.l1 = "...";
			link.l1.go = "Mass_dialog_6_exit";
		break;

		case "Mass_dialog_6_exit":
		AddDialogExitQuest("Royal_jackpot_30");
			dialogexit();
		break;

		case "Mass_dialog_7":
			dialog.text = StringFromKey("Other_dialog_177");
			link.l1 = "...";
			link.l1.go = "Mass_dialog_7_exit";
		break;

		case "Mass_dialog_7_exit":
		AddDialogExitQuest("Royal_jackpot_31");
			dialogexit();
		break;

		case "Mass_dialog_8":
			dialog.text = StringFromKey("Other_dialog_178", pchar.lastname, pchar.name);
			link.l1 = "...";
			link.l1.go = "Mass_dialog_8_exit";
		break;

		case "Mass_dialog_8_exit":
		AddDialogExitQuest("Royal_jackpot_32");
			dialogexit();
		break;

		case "Mass_dialog_9":
			dialog.text = StringFromKey("Other_dialog_179");
			link.l1 = "...";
			link.l1.go = "Mass_dialog_9_exit";
		break;

		case "Mass_dialog_9_exit":
			AddDialogExitQuest("Royal_jackpot_32_1");
			dialogexit();
		break;

		case "Royal_Navigator_1":
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_180");
			link.l1.go = "Royal_Navigator_1_exit";
		break;

		case "Royal_Navigator_1_exit":
		AddDialogExitQuest("Royal_jackpot_51");
			dialogexit();
		break;

		case "Royal_Navigator_2":
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_181");
			link.l1.go = "Royal_Navigator_3";
		break;

		case "Royal_Navigator_3":
			dialog.text = StringFromKey("Other_dialog_182");
			link.l1 = StringFromKey("Other_dialog_183");
			link.l1.go = "Royal_Navigator_4";
		break;

		case "Royal_Navigator_4":
			dialog.text = StringFromKey("Other_dialog_184");
			link.l1 = StringFromKey("Other_dialog_185");
			link.l1.go = "Royal_Navigator_5";
		break;

		case "Royal_Navigator_5":
			dialog.text = StringFromKey("Other_dialog_186");
			link.l1 = StringFromKey("Other_dialog_187");
			link.l1.go = "Royal_Navigator_6";
		break;

		case "Royal_Navigator_6":
			dialog.text = StringFromKey("Other_dialog_188");
			link.l1 = StringFromKey("Other_dialog_189");
			link.l1.go = "Royal_Navigator_6_1";
		break;

		case "Royal_Navigator_6_1":
			dialog.text = StringFromKey("Other_dialog_190");
			link.l1 = StringFromKey("Other_dialog_191");
			link.l1.go = "Royal_Navigator_6_2";
		break;

		case "Royal_Navigator_6_2":
			dialog.text = StringFromKey("Other_dialog_192");
			link.l1 = StringFromKey("Other_dialog_193");
			link.l1.go = "Royal_Navigator_7";
		break;

		case "Royal_Navigator_7":
			dialog.text = StringFromKey("Other_dialog_194");
			link.l1 = "...";
			link.l1.go = "Royal_Navigator_7_exit";
		break;

		case "Royal_Navigator_7_exit":
			AddDialogExitQuest("Royal_jackpot_55");
			dialogexit();
		break;

		case "Patrol_Halt":
			RemoveLandQuestmark_Main(npchar, "Royal_jackpot");
			dialog.text = StringFromKey("Other_dialog_195");

			if (!CheckAttribute(pchar, "questTemp.AoP.RoyalJackpot.HasPassword"))
			{
				pchar.questTemp.AoP.RoyalJackpot.HasPassword = 0;
			}

			if (sti(pchar.questTemp.AoP.RoyalJackpot.HasPassword) == 1)
			{
				link.l1 = StringFromKey("Other_dialog_196");
				link.l1.go = "Patrol_Halt_1";
			}
			else
			{
				link.l1 = StringFromKey("Other_dialog_197");
				link.l1.go = "Patrol_NoPassword_1";
			}
		break;

		case "Patrol_Halt_1":
			dialog.text = StringFromKey("Other_dialog_198");
			link.l1 = StringFromKey("Other_dialog_199");
			link.l1.go = "Patrol_Password";
		break;

		case "Patrol_Password":
			dialog.text = StringFromKey("Other_dialog_200");
			link.l1 = StringFromKey("Other_dialog_201");
			link.l1.go = "Patrol_Check_Fail";
			link.l2 = StringFromKey("Other_dialog_202");
			link.l2.go = "Patrol_Check_Fail";
			link.l3 = StringFromKey("Other_dialog_203");
			link.l3.go = "Patrol_Check";
			link.l4 = StringFromKey("Other_dialog_204");
			link.l4.go = "Patrol_Check_Fail";
		break;

		case "Patrol_Check":
			AddCharacterExpToSkill(PChar, SKILL_SNEAK, 20);
			dialog.text = StringFromKey("Other_dialog_205", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Other_dialog_206");
			link.l1.go = "Patrol_Check_1";
		break;

		case "Patrol_Check_1":
			dialog.text = StringFromKey("Other_dialog_207");
			link.l1 = StringFromKey("Other_dialog_208");
			link.l1.go = "Patrol_Pass";
		break;

		case "Patrol_Check_Fail":
			dialog.text = StringFromKey("Other_dialog_209", pchar);
			link.l1 = StringFromKey("Other_dialog_210");
			link.l1.go = "Patrol_Fail";
		break;

		case "Patrol_NoPassword_1":
			dialog.text = StringFromKey("Other_dialog_211");
			link.l1 = StringFromKey("Other_dialog_212");
			link.l1.go = "Patrol_NoPassword_2";
		break;

		case "Patrol_NoPassword_2":
			dialog.text = StringFromKey("Other_dialog_213", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Other_dialog_214");
			link.l1.go = "Patrol_NoPassword_3";
		break;

		case "Patrol_NoPassword_3":
			dialog.text = StringFromKey("Other_dialog_215");
			link.l1 = StringFromKey("Other_dialog_216");
			link.l1.go = "Patrol_Fail";
		break;

		case "Patrol_Pass":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_57_good");
		break;

		case "Patrol_Ambush":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_57_ambush");
		break;

		case "Patrol_Fail":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_57_bad");
		break;

		case "Mateo_Serrano_1":
			dialog.text = StringFromKey("Other_dialog_217");
			link.l1 = StringFromKey("Other_dialog_218");
			link.l1.go = "Mateo_Serrano_2";
		break;

		case "Mateo_Serrano_2":
			dialog.text = StringFromKey("Other_dialog_219");
			link.l1 = StringFromKey("Other_dialog_220");
			link.l1.go = "Mateo_Serrano_3";
		break;

		case "Mateo_Serrano_3":
			dialog.text = StringFromKey("Other_dialog_221", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Other_dialog_222");
			link.l1.go = "Mateo_Serrano_4";
		break;

		case "Mateo_Serrano_4":
			dialog.text = StringFromKey("Other_dialog_223");
			link.l1 = StringFromKey("Other_dialog_224", pchar);
			link.l1.go = "Mateo_Serrano_5_exit";
		break;

		case "Mateo_Serrano_5_exit":
			AddDialogExitQuest("Royal_jackpot_63");
			DialogExit();
		break;

		case "Atauko_Royal_1":
			dialog.text = StringFromKey("Other_dialog_225");
			link.l1 = StringFromKey("Other_dialog_226");
			link.l1.go = "Atauko_Royal_2";
		break;

		case "Atauko_Royal_2":
			dialog.text = StringFromKey("Other_dialog_227");
			link.l1 = StringFromKey("Other_dialog_228");
			link.l1.go = "Atauko_Royal_3";
		break;

		case "Atauko_Royal_3":
			dialog.text = StringFromKey("Other_dialog_229");
			link.l1 = StringFromKey("Other_dialog_230");
			link.l1.go = "Atauko_Royal_4";
		break;

		case "Atauko_Royal_4":
			dialog.text = StringFromKey("Other_dialog_231");
			link.l1 = StringFromKey("Other_dialog_232");
			link.l1.go = "Atauko_Royal_exit";
		break;

		case "Atauko_Royal_exit":
			DialogExit();
			AddDialogExitQuest("Royal_jackpot_83");
		break;

		case "Don_Alonso_1":
			dialog.text = StringFromKey("Other_dialog_233");
			link.l1 = StringFromKey("Other_dialog_234");
			link.l1.go = "Don_Alonso_2";
		break;

		case "Don_Alonso_2":
			dialog.text = StringFromKey("Other_dialog_235");
			link.l1 = StringFromKey("Other_dialog_236");
			link.l1.go = "Don_Alonso_3";
		break;

		case "Don_Alonso_3":
			dialog.text = StringFromKey("Other_dialog_237");
			link.l1 = "...";
			link.l1.go = "Don_Alonso_3_exit";
		break;

		case "Don_Alonso_3_exit":
		AddDialogExitQuest("Royal_jackpot_122");
			dialogexit();
		break;

		case "Don_Alonso_5":
			dialog.text = StringFromKey("Other_dialog_238");
			link.l1 = "...";
			link.l1.go = "Don_Alonso_5_exit";
		break;

		case "Don_Alonso_5_exit":
			sld = CharacterFromID("Mary_Belfler");
			sld.Dialog.CurrentNode = "Royal_jackpot_10";
			LAi_ActorDialogNow(sld, pchar, "", -1);
			DialogExit();
		break;

		case "Don_Alonso_4":
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_239");
			link.l1.go = "Don_Alonso_4_exit";
		break;

		case "Don_Alonso_4_exit":
		AddDialogExitQuest("Royal_jackpot_133");
			dialogexit();
		break;

		case "Matros_1":
			dialog.text = StringFromKey("Other_dialog_240");
			link.l1 = "...";
			link.l1.go = "Matros_2_exit";
		break;

		case "Matros_2":
			dialog.text = StringFromKey("Other_dialog_241");
			link.l1 = "...";
			link.l1.go = "Matros_2_exit";
		break;

		case "Matros_2_exit":
		AddDialogExitQuest("Royal_jackpot_137");
			dialogexit();
		break;

		case "Matros_3":
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_242");
			link.l1.go = "Matros_4";
		break;

		case "Matros_4":
			dialog.text = StringFromKey("Other_dialog_243");
			link.l1 = StringFromKey("Other_dialog_244");
			link.l1.go = "Matros_4_exit";
		break;

		case "Matros_4_exit":
			AddDialogExitQuest("Royal_jackpot_139");
			dialogexit();
		break;

		case "Fakel_1":
			dialog.text = StringFromKey("Other_dialog_245");
			link.l1 = StringFromKey("Other_dialog_246");
			link.l1.go = "Fakel_2";
		break;

		case "Fakel_2":
			dialog.text = StringFromKey("Other_dialog_247");
			link.l1 = StringFromKey("Other_dialog_248");
			link.l1.go = "Fakel_3";
		break;

		case "Fakel_3":
			dialog.text = StringFromKey("Other_dialog_249");
			link.l1 = "...";
			link.l1.go = "Fakel_3_exit";
		break;

		case "Fakel_3_exit":
			AddDialogExitQuest("Royal_jackpot_146");
			DialogExit();
		break;

		case "Loader_1":
			dialog.text = StringFromKey("Other_dialog_250");
			link.l1 = StringFromKey("Other_dialog_251");
			link.l1.go = "Loader_2";
		break;

		case "Loader_2":
			dialog.text = StringFromKey("Other_dialog_252");
			link.l1 = "...";
			link.l1.go = "Loader_2_exit";
		break;

		case "Loader_2_exit":
			AddDialogExitQuest("Royal_jackpot_152");
			DialogExit();
		break;

		case "Alone_Bucaneer_1":
			dialog.text = StringFromKey("Other_dialog_253");
			link.l1 = StringFromKey("Other_dialog_254");
			link.l1.go = "Alone_Bucaneer_2";
		break;

		case "Alone_Bucaneer_2":
			dialog.text = StringFromKey("Other_dialog_255");
			link.l1 = StringFromKey("Other_dialog_256", GetFullName(pchar));
			link.l1.go = "Alone_Bucaneer_3";
		break;

		case "Alone_Bucaneer_3":
			dialog.text = StringFromKey("Other_dialog_257", GetFullName(pchar));
			link.l1 = StringFromKey("Other_dialog_258");
			link.l1.go = "Alone_Bucaneer_3_1";
		break;

		case "Alone_Bucaneer_3_1":
			dialog.text = StringFromKey("Other_dialog_259");
			link.l1 = "...";
			link.l1.go = "Alone_Bucaneer_3_exit";
		break;

		case "Alone_Bucaneer_3_exit":
			AddDialogExitQuest("Keys_lagoon_28");
			dialogexit();
		break;

		case "Alone_Bucaneer_4":
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_260");
			link.l1.go = "Alone_Bucaneer_5";
		break;

		case "Alone_Bucaneer_5":
			dialog.text = StringFromKey("Other_dialog_261");
			link.l1 = "...";
			link.l1.go = "Alone_Bucaneer_5_exit";
		break;

		case "Alone_Bucaneer_5_exit":
			AddDialogExitQuest("Keys_lagoon_31");
			dialogexit();
		break;

		case "Indian_1":
			RemoveLandQuestmark_Main(npchar, "Keys_lagoon");
			dialog.text = StringFromKey("Other_dialog_262");
			link.l1 = StringFromKey("Other_dialog_263");
			link.l1.go = "Indian_1_exit";
		break;

		case "Indian_1_exit":
			AddDialogExitQuest("Keys_lagoon_32");
			dialogexit();
		break;

		case "Alone_Bucaneer_6":
			dialog.text = StringFromKey("Other_dialog_264");
			link.l1 = StringFromKey("Other_dialog_265");
			link.l1.go = "Alone_Bucaneer_6_exit";
		break;

		case "Alone_Bucaneer_6_exit":
			AddDialogExitQuest("Keys_lagoon_33");
			dialogexit();
		break;

		case "Indian_2":
			TakeNItemsNotification(pchar, "potion4", -1, "default", "", "");
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_266");
			link.l1.go = "Indian_2_exit";
		break;

		case "Indian_2_exit":
			AddDialogExitQuest("Keys_lagoon_34");
			dialogexit();
		break;

		case "Indian_3":
			dialog.text = "...";
			link.l1 = StringFromKey("Other_dialog_267");
			link.l1.go = "Indian_4";
		break;

		case "Indian_4":
			dialog.text = StringFromKey("Other_dialog_268");
			link.l1 = StringFromKey("Other_dialog_269");
			link.l1.go = "Indian_5";
		break;

		case "Indian_5":
			dialog.text = StringFromKey("Other_dialog_270");
			link.l1 = "...";
			link.l1.go = "Indian_5_exit";
		break;

		case "Indian_5_exit":
			AddDialogExitQuest("Keys_lagoon_36");
			dialogexit();
		break;

		case "Alone_Bucaneer_7":
			dialog.text = StringFromKey("Other_dialog_271");
			link.l1 = "...";
			link.l1.go = "Alone_Bucaneer_7_exit";
		break;

		case "Alone_Bucaneer_7_exit":
			AddDialogExitQuest("Keys_lagoon_37");
			dialogexit();
		break;

		case "Alone_Bucaneer_8":
			sld = CharacterFromID("Alone_Bucaneer");
			dialog.text = StringFromKey("Other_dialog_272", sld.name);
			link.l1 = "...";
			link.l1.go = "Alone_Bucaneer_8_exit";
		break;

		case "Alone_Bucaneer_8_exit":
			AddDialogExitQuest("Keys_lagoon_39");
			dialogexit();
		break;

		case "Alone_Bucaneer_9":
			RemoveLandQuestmark_Main(npchar, "Keys_lagoon");
			dialog.text = StringFromKey("Other_dialog_273");
			link.l1 = StringFromKey("Other_dialog_274");
			link.l1.go = "Alone_Bucaneer_9_exit";
		break;

		case "Alone_Bucaneer_9_exit":
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			AddDialogExitQuest("Keys_lagoon_43");
			dialogexit();
		break;

		case "Dozor":
			dialog.text = StringFromKey("Other_dialog_275");
			link.l1 = "...";
			link.l1.go = "Dozor_exit";
		break;

		case "Dozor_exit":
			AddDialogExitQuest("Keys_lagoon_78");
			dialogexit();
		break;

		case "Cabrera_1":
			RemoveLandQuestmark_Main(npchar, "Keys_lagoon");
			dialog.text = StringFromKey("Other_dialog_276");
			link.l1 = StringFromKey("Other_dialog_277");
			link.l1.go = "Cabrera_2_Exit";
		break;

		case "Cabrera_2_Exit":
			AddDialogExitQuest("Keys_lagoon_87_1");
			DialogExit();
		break;

		case "Cabrera_3":
			dialog.text = StringFromKey("Other_dialog_278");
			link.l1 = StringFromKey("Other_dialog_279");
			link.l1.go = "Cabrera_4";
		break;

		case "Cabrera_4":
			dialog.text = StringFromKey("Other_dialog_280");
			link.l1 = StringFromKey("Other_dialog_281");
			link.l1.go = "Cabrera_5";
		break;

		case "Cabrera_5":
			dialog.text = StringFromKey("Other_dialog_282");
			link.l1 = StringFromKey("Other_dialog_283", pchar);
			link.l1.go = "Cabrera_6";
		break;

		case "Cabrera_6":
			dialog.text = StringFromKey("Other_dialog_284");
			link.l1 = StringFromKey("Other_dialog_285");
			link.l1.go = "Cabrera_7";
		break;

		case "Cabrera_7":
			dialog.text = StringFromKey("Other_dialog_286");
			link.l1 = StringFromKey("Other_dialog_287");
			link.l1.go = "Cabrera_7_exit";
		break;

		case "Cabrera_7_exit":
			AddDialogExitQuest("Keys_lagoon_88");
			DialogExit();
		break;

		case "Keys_lagoon_ShipKeeper_1":
			iShipIndex = 0;
			for (iShipSlot = 1; iShipSlot < COMPANION_MAX; iShipSlot++)
			{
				if (GetCompanionIndex(pchar, iShipSlot) < 0) continue;
				if (!GetRemovable(GetCharacter(GetCompanionIndex(pchar, iShipSlot)))) continue;
				iShipIndex++;
			}

			if (iShipIndex > 0)
			{
				dialog.text = StringFromKey("Other_dialog_288");
				link.l1 = StringFromKey("Other_dialog_289");
				link.l1.go = "Keys_lagoon_ShipKeeper_2";
			}
			else
			{
				dialog.text = StringFromKey("Other_dialog_290");
				link.l1 = StringFromKey("Other_dialog_291");
				link.l1.go = "Keys_lagoon_ShipKeeper_NoShips";
			}
		break;

		case "Keys_lagoon_ShipKeeper_2":
			for (iShipSlot = COMPANION_MAX - 1; iShipSlot >= 1; iShipSlot--)
			{
				iShipIndex = GetCompanionIndex(pchar, iShipSlot);
				if (iShipIndex < 0) continue;

				sld = GetCharacter(iShipIndex);
				if (!GetRemovable(sld)) continue;

				sld.AoP.ArubaStoredShip = true;
				sld.AoP.ArubaStoredShipSlot = iShipSlot;
				RemoveCharacterCompanion(pchar, sld);
			}

			dialog.text = StringFromKey("Other_dialog_292");
			link.l1 = StringFromKey("Other_dialog_293");
			link.l1.go = "Keys_lagoon_ShipKeeper_2_exit";
		break;

		case "Keys_lagoon_ShipKeeper_NoShips":
			dialog.text = StringFromKey("Other_dialog_294");
			link.l1 = "...";
			link.l1.go = "Keys_lagoon_ShipKeeper_NoShips_exit";
		break;

		case "Keys_lagoon_ShipKeeper_NoShips_exit":
			LAi_SetStayType(npchar);
			NextDiag.CurrentNode = "Keys_lagoon_ShipKeeper_1";
			DialogExit();
		break;

		case "Keys_lagoon_ShipKeeper_2_exit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

case "Keys_lagoon_ShipKeeper_2_exit":
LAi_CharacterDisableDialog(npchar);
dialogexit();
break;

case "Keys_lagoon_ShipKeeper_Return_1":
iShipIndex = 0;
for (iShipSlot = 0; iShipSlot < MAX_CHARACTERS; iShipSlot++)
{
	sld = &characters[iShipSlot];
	if (CheckAttribute(sld, "AoP.ArubaStoredShip")) iShipIndex++;
}

iFreeSlots = 0;
for (iShipSlot = 1; iShipSlot < COMPANION_MAX; iShipSlot++)
{
	if (GetCompanionIndex(pchar, iShipSlot) < 0) iFreeSlots++;
}

if (iShipIndex <= 0)
{
	dialog.text = StringFromKey("Other_dialog_295");
	link.l1 = StringFromKey("Other_dialog_296");
	link.l1.go = "Keys_lagoon_ShipKeeper_Return_NoShips";
}
else
{
	dialog.text = StringFromKey("Other_dialog_297");
	
	if (iFreeSlots >= iShipIndex)
	{
		link.l1 = StringFromKey("Other_dialog_298");
		link.l1.go = "Keys_lagoon_ShipKeeper_Return_2";
	}
	else
	{
		link.l1 = StringFromKey("Other_dialog_299");
		link.l1.go = "Keys_lagoon_ShipKeeper_Return_NoSlots";
	}
}
break;

case "Keys_lagoon_ShipKeeper_Return_NoSlots":
dialog.text = StringFromKey("Other_dialog_300");
link.l1 = StringFromKey("Other_dialog_301");
link.l1.go = "Keys_lagoon_ShipKeeper_Return_Wait";
break;

case "Keys_lagoon_ShipKeeper_Return_Wait":
NextDiag.CurrentNode = "Keys_lagoon_ShipKeeper_Return_1";
DialogExit();
break;

case "Keys_lagoon_ShipKeeper_Return_NoShips":
NextDiag.CurrentNode = "Keys_lagoon_ShipKeeper_Return_1";
DialogExit();
break;

case "Keys_lagoon_ShipKeeper_Return_2":
for (iShipSlot = 0; iShipSlot < MAX_CHARACTERS; iShipSlot++)
{
	sld = &characters[iShipSlot];
	if (!CheckAttribute(sld, "AoP.ArubaStoredShip")) continue;

	SetCompanionIndex(pchar, -1, sti(sld.index));
SetCharacterRemovable(sld, true);
DeleteAttribute(sld, "AoP.ArubaStoredShip");
DeleteAttribute(sld, "AoP.ArubaStoredShipSlot");
}

dialog.text = StringFromKey("Other_dialog_302");
link.l1 = StringFromKey("Other_dialog_303");
link.l1.go = "Keys_lagoon_ShipKeeper_Return_3";
break;

case "Keys_lagoon_ShipKeeper_Return_3":
dialog.text = StringFromKey("Other_dialog_304");
link.l1 = StringFromKey("Other_dialog_305");
link.l1.go = "Keys_lagoon_ShipKeeper_Return_exit";
break;

case "Keys_lagoon_ShipKeeper_Return_exit":
AddDialogExitQuest("Keys_lagoon_296");
DialogExit();
break;

		case "Bedroom_Spa_1":
			dialog.text = StringFromKey("Other_dialog_306");
			link.l1 = StringFromKey("Other_dialog_307");
			link.l1.go = "Bedroom_Spa_2";
		break;

		case "Bedroom_Spa_2":
			dialog.text = StringFromKey("Other_dialog_308");
			link.l1 = StringFromKey("Other_dialog_309");
			link.l1.go = "Bedroom_Spa_2_Exit";
		break;

		case "Bedroom_Spa_2_Exit":
			AddDialogExitQuest("Keys_lagoon_137");
			DialogExit();
		break;

		case "Exit":
			NextDiag.CurrentNode = "first time";
			DialogExit();
		break;

	}
}

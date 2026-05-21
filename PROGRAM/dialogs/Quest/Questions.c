void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTermsValidity;

	int iNation, j;
	int LicenceValidity;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string sTemp, sAttr;

	sAttr = Dialog.CurrentNode;
	if (HasStr(sAttr, "SeaQuestionChooseAnswer_"))
	{
		j = findsubstr(sAttr, "_", 0);
		TEV.SeaQuestionTemp.Answer = strcut(sAttr, j + 1, strlen(sAttr) - 1);
		Dialog.CurrentNode = "Question_chinese_check";
	}

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "exit_over":
			npchar.lifeDay = 0;
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "SCQ_exit":
			npchar.lifeDay = 0;
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		case "good_all":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Questions_1", npchar),
						StringFromKey("Questions_2"),
						StringFromKey("Questions_3"),
						StringFromKey("Questions_4"), "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Questions_5"),
						StringFromKey("Questions_6"),
						StringFromKey("Questions_7"),
						StringFromKey("Questions_8"), npchar, Dialog.CurrentNode);
			link.l1.go = "Exit";
			NextDiag.TempNode = "good_all";
		break;
		case "All_disagree":
			npchar.lifeDay = 0;
			NextDiag.TempNode = "All_bye";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "All_bye":
			dialog.text = StringFromKey("Questions_9");
			link.l1 = StringFromKey("Questions_10");
			link.l1.go = "Exit";
			NextDiag.TempNode = "All_bye";
		break;
		//================================== в Порт оф Спейне ======================================
		case "PortSpein":
			NextDiag.TempNode = "PortSpein";
			dialog.text = StringFromKey("Questions_11");
			link.l1 = StringFromKey("Questions_12", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit_over";
			link.l2 = StringFromKey("Questions_13");
			link.l2.go = "PortSpein_1";
			DeleteAttribute(npchar, "talker");
		break;
		case "PortSpein_1":
			dialog.text = StringFromKey("Questions_14", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Questions_15");

			sTemp = "PortSpein_2";
			if (CheckForTreasureMap(pchar))
				sTemp += "_pistol";

			link.l1.go = sTemp;
		break;
		case "PortSpein_2":
			dialog.text = StringFromKey("Questions_16");
			link.l1 = StringFromKey("Questions_17");
			link.l1.go = "PortSpein_3";
		break;

		case "PortSpein_2_pistol":
			dialog.text = StringFromKey("Questions_18");
			link.l1 = StringFromKey("Questions_19");
			link.l1.go = "PortSpein_3_pistol";
		break;

		case "PortSpein_3":
			dialog.text = StringFromKey("Questions_20", pchar);
			link.l1 = StringFromKey("Questions_21", pchar);
			link.l1.go = "PortSpein_4";
			link.l2 = StringFromKey("Questions_22");
			link.l2.go = "All_disagree";
		break;

		case "PortSpein_3_pistol":
			dialog.text = StringFromKey("Questions_23", pchar);
			link.l1 = StringFromKey("Questions_24", pchar);
			link.l1.go = "PortSpein_4";
			link.l2 = StringFromKey("Questions_25");
			link.l2.go = "All_disagree";
		break;

		case "PortSpein_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = StringFromKey("Questions_26", NullCharacter.questions.(sTemp));
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortSpein_check";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;
		case "PortSpein_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = StringFromKey("Questions_27", pchar);
				link.l1 = StringFromKey("Questions_28");

				sTemp = "PortSpein_ok";
				if (CheckForTreasureMap(pchar))
					sTemp += "_pistol";

				link.l1.go = sTemp;
			}
			else
			{
				dialog.text = StringFromKey("Questions_29");
				link.l1 = StringFromKey("Questions_30");
				link.l1.go = "PortSpein_5";
				link.l2 = StringFromKey("Questions_31");
				link.l2.go = "PortSpein_6";
			}
		break;
		case "PortSpein_ok":
			dialog.text = StringFromKey("Questions_32");
			link.l1 = StringFromKey("Questions_33", pchar);
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
			GiveItem2Character(pchar, "map_full");
			TEV.MapTreasureNoScam = true; // без подделки
			ReOpenQuestHeader("QM_Port_Of_Spein");
			AddQuestRecord("QM_Port_Of_Spein", "1");
			AddQuestUserData("QM_Port_Of_Spein", "sName", GetFullName(npchar));
			CloseQuestHeader("QM_Port_Of_Spein");
		break;

		case "PortSpein_ok_pistol":
			dialog.text = StringFromKey("Questions_34");
			link.l1 = StringFromKey("Questions_35", pchar);
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
			pchar.GenQuestRandItem.LaVega_town = true;
			ReOpenQuestHeader("QM_Port_Of_Spein");
			AddQuestRecord("QM_Port_Of_Spein", "2");
			AddQuestUserData("QM_Port_Of_Spein", "sName", GetFullName(npchar));
		break;

		case "PortSpein_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = StringFromKey("Questions_36", NullCharacter.questions.(sTemp));
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortSpein_check";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;
		case "PortSpein_6":
			dialog.text = StringFromKey("Questions_37");
			link.l1 = StringFromKey("Questions_38");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortSpein_again";
		break;
		case "PortSpein_again":
			dialog.text = StringFromKey("Questions_39");
			link.l1 = StringFromKey("Questions_40", pchar);
			link.l1.go = "PortSpein_5";
		break;
		//================================== Виллемстад: Найти пропавшего торговца ======================================
		case "Villemstad":
			NextDiag.TempNode = "Villemstad";
			dialog.text = StringFromKey("Questions_41");
			link.l1 = StringFromKey("Questions_44", RandPhraseSimple(
						StringFromKey("Questions_42", GetAddress_FormToNPC(NPChar)),
						StringFromKey("Questions_43", GetAddress_FormToNPC(NPChar))));
			link.l1.go = "SCQ_Hasband";
			link.l2 = StringFromKey("Questions_47", RandPhraseSimple(
						StringFromKey("Questions_45", pchar),
						StringFromKey("Questions_46", GetAddress_FormToNPC(NPChar))));
			link.l2.go = "exit";
		break;
		case "SCQ_Hasband":
			dialog.text = StringFromKey("Questions_48");
			link.l1 = StringFromKey("Questions_49");
			link.l1.go = "SCQ_Hasband_0";
		break;
		case "SCQ_Hasband_0":
			dialog.text = StringFromKey("Questions_50");
			link.l1 = StringFromKey("Questions_51");
			link.l1.go = "SCQ_Hasband_1";
		break;
		case "SCQ_Hasband_1":
			dialog.text = StringFromKey("Questions_52", pchar);
			link.l1 = StringFromKey("Questions_53");
			link.l1.go = "SCQ_Hasband_2";
			link.l2 = StringFromKey("Questions_54", pchar);
			link.l2.go = "exit";
		break;
		case "SCQ_Hasband_2":
			dialog.text = StringFromKey("Questions_55");
			link.l1 = StringFromKey("Questions_56", pchar);
			link.l1.go = "exit";
			npchar.quest.SeekCap = "womanHasband"; //личный флаг ситизена на квест
			RemoveLandQuestMark_Main(npchar, "SCQ_Hasband_Truba");
			RemoveMapQuestMark("Villemstad_town", "SCQ_Hasband_Truba");
			//==> ставим квестодателя в церковь // надо проверить, возможно надо поменять на Hasband_Truba и здесь. Hirurg39
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
			pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			SetQuestHeader("SCQ_Hasband_Truba");
			AddQuestRecord("SCQ_Hasband_Truba", "1");

			sld = GetCharacter(NPC_GenerateCharacter("QuetionsVillemstad_MuzhTorgovets", "GrunMaurits", "man", "man", sti(PChar.rank), HOLLAND, -1, true));
			FantomMakeCoolSailor(sld, SHIP_SHNYAVA, FindPersonalName("GrunMaurits_ship"), CANNON_TYPE_CULVERINE_LBS12, 30, 30, 30);
			sld.name = FindPersonalName("GrunMaurits_name");
			sld.lastname = FindPersonalName("GrunMaurits_lastname");
			sld.dialog.filename = "Quest\Questions.c";
			sld.DeckDialogNode = "HasbandCap_inDeck";
			sld.Ship.Mode = "trade";
			Group_FindOrCreateGroup("QuetionsVillemstad_MuzhTorgovets_Ship");
			Group_SetType("QuetionsVillemstad_MuzhTorgovets_Ship", "pirate");
			Group_AddCharacter("QuetionsVillemstad_MuzhTorgovets_Ship", "QuetionsVillemstad_MuzhTorgovets");
			Group_SetGroupCommander("QuetionsVillemstad_MuzhTorgovets_Ship", "QuetionsVillemstad_MuzhTorgovets");
			pchar.questTemp.SCQ_Hasband_Luiza = true;
			AddLandQuestMark_Main(sld, "SCQ_Hasband_Truba");

			string sCity = "Caracas";
			sTemp = "5";

			switch (rand(2))
			{
				case 1: sCity = "Cumana"; break;
				case 2: sCity = "Maracaibo"; sTemp = "6"; break;
			}

			Group_SetAddress("QuetionsVillemstad_MuzhTorgovets_Ship", sCity, "quest_ships", "Quest_ship_" + sTemp);
		break;

		case "HasbandCap_inDeck":
			dialog.text = StringFromKey("Questions_57", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Questions_58", GetFullName(Pchar));
			link.l1.go = "HasbandCap_inDeck_1";
		break;
		case "HasbandCap_inDeck_1":
			dialog.text = StringFromKey("Questions_59", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Questions_60");
			link.l1.go = "HasbandCap_inDeck_2";
		break;
		case "HasbandCap_inDeck_2":
			dialog.text = StringFromKey("Questions_61");
			link.l1 = StringFromKey("Questions_62");
			link.l1.go = "HasbandCap_inDeck_3";
		break;
		case "HasbandCap_inDeck_3":
			dialog.text = StringFromKey("Questions_63");
			link.l1 = StringFromKey("Questions_64");
			link.l1.go = "HasbandCap_inDeck_4";
		break;
		case "HasbandCap_inDeck_4":
			dialog.text = StringFromKey("Questions_65");
			link.l1 = StringFromKey("Questions_66");
			link.l1.go = "HasbandCap_inDeck_5";
		break;
		case "HasbandCap_inDeck_5":
			dialog.text = StringFromKey("Questions_67", pchar);
			link.l1 = StringFromKey("Questions_68", pchar);
			link.l1.go = "HasbandCap_inDeck_6";
		break;
		case "HasbandCap_inDeck_6":
			dialog.text = StringFromKey("Questions_69");
			link.l1 = StringFromKey("Questions_70");
			link.l1.go = "exit";
			npchar.lifeday = 0;
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
			AddQuestRecord("SCQ_Hasband_Truba", "2");
			sld = characterFromId("QuetionsVillemstad");
			sld.dialog.filename = "Quest\Questions.c";
			sld.dialog.currentnode = "womanHasbandover";
			pchar.GenQuestRandItem.PuertoPrincipe_town = true;
			DeleteAttribute(pchar, "questTemp.SCQ_Hasband_Luiza");
			RemoveLandQuestMark_Main(npchar, "SCQ_Hasband_Truba");
			AddLandQuestMark_Main(sld, "SCQ_Hasband_Truba");
		break;
		case "HasbandCap_inDeck_exit":
			dialog.text = StringFromKey("Questions_71", GetFullName(Pchar));
			link.l1 = StringFromKey("Questions_72");
			link.l1.go = "exit";
			NextDiag.TempNode = "HasbandCap_inDeck_exit";
		break;

		//================================== Порт-о-Принс: Вызволение из плена мужа горожанки ======================================
		case "PortPax":
			NextDiag.TempNode = "PortPax";
			dialog.text = StringFromKey("Questions_73", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Questions_74", GetFullName(Pchar));
			link.l1.go = "SCQ_Pirates";
			DeleteAttribute(npchar, "talker");
		break;
		case "SCQ_Pirates":
			dialog.text = StringFromKey("Questions_75", GetFullName(Pchar));
			link.l1 = StringFromKey("Questions_76");
			link.l1.go = "SCQ_Pirates_1";
		break;
		case "SCQ_Pirates_1":
			dialog.text = StringFromKey("Questions_77");
			link.l1 = StringFromKey("Questions_78");
			link.l1.go = "SCQ_Pirates_2";
		break;
		case "SCQ_Pirates_2":
			dialog.text = StringFromKey("Questions_79");
			link.l1 = StringFromKey("Questions_80");
			link.l1.go = "SCQ_Pirates_3";
		break;
		case "SCQ_Pirates_3":
			dialog.text = StringFromKey("Questions_81");
			link.l1 = StringFromKey("Questions_82");
			link.l1.go = "SCQ_Pirates_4";
		break;
		case "SCQ_Pirates_4":
			dialog.text = StringFromKey("Questions_83");
			link.l1 = StringFromKey("Questions_84");
			link.l1.go = "SCQ_Pirates_5";
		break;
		case "SCQ_Pirates_5":
			npchar.quest.SeekCap = "PirateFashion"; //личный флаг ситизена на квест
			dialog.text = StringFromKey("Questions_85");
			link.l1 = StringFromKey("Questions_86", pchar);
			link.l1.go = "SCQ_Pirates_6";
			link.l2 = StringFromKey("Questions_87", pchar);
			link.l2.go = "exit";
		break;
		case "SCQ_Pirates_6":
			dialog.text = StringFromKey("Questions_88", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Questions_89");
			link.l1.go = "SCQ_Pirates_7";
		break;
		case "SCQ_Pirates_7":
			dialog.text = StringFromKey("Questions_90");
			link.l1 = StringFromKey("Questions_91", pchar);
			link.l1.go = "exit";
			RemoveLandQuestMark_Main(npchar, "SCQ_PirateFashion");
			RemoveMapQuestMark("PortPax_town", "SCQ_PirateFashion");
			//==> ставим квестодателя в церковь
			pchar.quest.SeekShip_Stay.win_condition.l1 = "ExitFromLocation";
			npchar.location = npchar.city + "_church";
			npchar.location.locator = "goto2";
			pchar.quest.SeekShip_Stay.win_condition.l1.location = pchar.location;
			pchar.quest.SeekShip_Stay.function = "SeekShip_Stay";
			pchar.quest.SeekShip_Stay.Idx = npchar.index;
			NextDiag.TempNode = "SCQ_womanResult";
			SetQuestHeader("SCQ_PirateFashion");
			AddQuestRecord("SCQ_PirateFashion", "1");

			sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortPax_KoriBoll", "officer_17", "man", "man", sti(PChar.rank), PIRATE, -1, true));
			FantomMakeCoolSailor(sld, SHIP_SLOOP_W, FindPersonalName("KoriBoll_ship"), CANNON_TYPE_CANNON_LBS8, 30, 30, 30);
			DeleteAttribute(sld, "perks.list.FastReload");
			DeleteAttribute(sld, "perks.list.SailsDamageUp");
			DeleteAttribute(sld, "perks.list.CrewDamageUp");
			DeleteAttribute(sld, "perks.list.CriticalShoot");
			DeleteAttribute(sld, "perks.list.LongRangeShoot");
			DeleteAttribute(sld, "perks.list.CannonProfessional");
			DeleteAttribute(sld, "perks.list.ShipSpeedUp");
			DeleteAttribute(sld, "perks.list.MusketsShoot");
			sld.name = FindPersonalName("KoriBoll_name");
			sld.lastname = FindPersonalName("KoriBoll_lastname");
			sld.dialog.filename = "Quest\Questions.c";
			sld.dialog.currentnode = "PiratesCap_Board";
			sld.AlwaysEnemy = true;
			Group_FindOrCreateGroup("QuetionsPortPax_KoriBoll_Ship");
			Group_SetType("QuetionsPortPax_KoriBoll_Ship", "pirate");
			Group_AddCharacter("QuetionsPortPax_KoriBoll_Ship", "QuetionsPortPax_KoriBoll");
			Group_SetGroupCommander("QuetionsPortPax_KoriBoll_Ship", "QuetionsPortPax_KoriBoll");
			Group_SetAddress("QuetionsPortPax_KoriBoll_Ship", "Terks", "quest_ships", "Quest_ship_3");

			PChar.quest.SCQ_PirateFashion_Potunul.win_condition.l1 = "Character_sink";
			PChar.quest.SCQ_PirateFashion_Potunul.win_condition.l1.character = "QuetionsPortPax_KoriBoll";
			PChar.quest.SCQ_PirateFashion_Potunul.win_condition = "SCQ_PirateFashion_Potunul";
			PChar.quest.SCQ_PirateFashion_Nashli.win_condition.l1 = "location";
			PChar.quest.SCQ_PirateFashion_Nashli.win_condition.l1.location = "Terks";
			PChar.quest.SCQ_PirateFashion_Nashli.win_condition = "SCQ_PirateFashion_Nashli";
		break;
		case "PiratesCap_Board":
			dialog.text = StringFromKey("Questions_92");
			link.l1 = StringFromKey("Questions_93");
			link.l1.go = "PiratesCap_Board_1";
		break;
		case "PiratesCap_Board_1":
			dialog.text = StringFromKey("Questions_94");
			link.l1 = StringFromKey("Questions_95");
			link.l1.go = "PiratesCap_Board_2";
		break;
		case "PiratesCap_Board_2":
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("SCQ_PirateFashion_afterCabinFight");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			SetBan("Looting", 1);
		break;
		case "PirateFashion_Board":
			dialog.text = StringFromKey("Questions_96");
			link.l1 = StringFromKey("Questions_97", pchar, GetFullName(pchar));
			link.l1.go = "PirateFashion_Board_1";
		break;
		case "PirateFashion_Board_1":
			dialog.text = StringFromKey("Questions_98");
			link.l1 = StringFromKey("Questions_99");
			link.l1.go = "PirateFashion_Board_2";
		break;

		case "PirateFashion_Board_2":
			ChangeCharacterAddressGroup(npchar, "none", "", "");
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			sld = characterFromId("QuetionsPortPax");
			sld.dialog.filename = "Quest\Questions.c";
			sld.dialog.currentnode = "PirateFashionover";
			AddQuestRecord("SCQ_PirateFashion", "4");
			SetBan("Looting", 0);
			AddLandQuestMark_Main(sld, "SCQ_PirateFashion");
			DialogExit();
			AddDialogExitQuest("pchar_back_to_player");
		break;
		//================================== Сан-Хуан ======================================
		case "SanJuan":
			NextDiag.TempNode = "SanJuan";
			dialog.text = StringFromKey("Questions_100");
			link.l1 = StringFromKey("Questions_101");
			link.l1.go = "exit_over";
			link.l2 = StringFromKey("Questions_102", GetAddress_FormToNPC(NPChar));
			link.l2.go = "SanJuan_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "SanJuan_1":
			dialog.text = StringFromKey("Questions_103");
			link.l1 = StringFromKey("Questions_104");
			link.l1.go = "SanJuan_2";
		break;
		case "SanJuan_2":
			dialog.text = StringFromKey("Questions_105");
			link.l1 = StringFromKey("Questions_106");
			link.l1.go = "SanJuan_3";
		break;
		case "SanJuan_3":
			dialog.text = StringFromKey("Questions_107");
			link.l1 = StringFromKey("Questions_108");
			link.l1.go = "SanJuan_4";
		break;
		case "SanJuan_4":
			dialog.text = StringFromKey("Questions_109");
			link.l1 = StringFromKey("Questions_110");
			link.l1.go = "SanJuan_5";
			link.l2 = StringFromKey("Questions_111");
			link.l2.go = "All_disagree";
		break;
		case "SanJuan_5":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = StringFromKey("Questions_112", NullCharacter.questions.(sTemp));
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "SanJuan_check";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;
		case "SanJuan_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = StringFromKey("Questions_113", pchar);
				link.l1 = StringFromKey("Questions_114");
				link.l1.go = "SanJuan_ok";
			}
			else
			{
				dialog.text = StringFromKey("Questions_115", pchar);
				link.l1 = StringFromKey("Questions_116");
				link.l1.go = "SanJuan_6";
				link.l2 = StringFromKey("Questions_117");
				link.l2.go = "SanJuan_7";
			}
		break;
		case "SanJuan_ok":
			iNation = 5;
			LicenceValidity = 40;
			for (int i = 0; i < 4; i++)
			{
				if (GetRelation2BaseNation(i) == RELATION_ENEMY)
				{
					iNation = i;
					break;
				}
			}
			if (iNation == 5 || pchar.BaseNation == PIRATE) // если пират или со всеми в мире, то генерим лицензию случайной нации сроком 40 дней
			{
				iNation = rand(3);
			}
			GiveNationLicence(iNation, LicenceValidity + GetDaysContinueNationLicence(iNation));//фикс - продляю лицензию на весь срок, а не по сложным округлениям

			dialog.text = StringFromKey("Questions_118", GetRusNameNationLicence(iNation), LicenceValidity);
			link.l1 = StringFromKey("Questions_119", GetAddress_FormToNPC(NPChar));
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
		break;
		case "SanJuan_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = StringFromKey("Questions_120", NullCharacter.questions.(sTemp));
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "SanJuan_check";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;
		case "SanJuan_7":
			dialog.text = StringFromKey("Questions_121", pchar);
			link.l1 = StringFromKey("Questions_122");
			link.l1.go = "exit";
			NextDiag.TempNode = "SanJuan_again";
		break;
		case "SanJuan_again":
			dialog.text = StringFromKey("Questions_123");
			link.l1 = StringFromKey("Questions_124");
			link.l1.go = "SanJuan_6";
		break;
		//================================== Кумана ======================================
		case "Cumana":
			NextDiag.TempNode = "Cumana";
			dialog.text = StringFromKey("Questions_125");
			link.l1 = StringFromKey("Questions_126");
			link.l1.go = "exit_over";
			link.l2 = StringFromKey("Questions_127");
			link.l2.go = "Cumana_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Cumana_1":
			dialog.text = StringFromKey("Questions_128");
			link.l1 = StringFromKey("Questions_129");
			link.l1.go = "Cumana_2";
		break;
		case "Cumana_2":
			dialog.text = StringFromKey("Questions_130");
			link.l1 = StringFromKey("Questions_131");
			link.l1.go = "Cumana_3";
		break;
		case "Cumana_3":
			dialog.text = StringFromKey("Questions_132");
			link.l1 = StringFromKey("Questions_133", pchar);
			link.l1.go = "Cumana_4";
			link.l2 = StringFromKey("Questions_134");
			link.l2.go = "All_disagree";
		break;
		case "Cumana_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = StringFromKey("Questions_135", NullCharacter.questions.(sTemp));
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Cumana_check";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;
		case "Cumana_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = StringFromKey("Questions_136");
				link.l1 = StringFromKey("Questions_137", pchar);
				link.l1.go = "Cumana_ok";
			}
			else
			{
				dialog.text = StringFromKey("Questions_138", pchar);
				link.l1 = StringFromKey("Questions_139");
				link.l1.go = "Cumana_6";
				link.l2 = StringFromKey("Questions_140");
				link.l2.go = "Cumana_7";
			}
		break;
		case "Cumana_ok":
			dialog.text = StringFromKey("Questions_141");
			link.l1 = StringFromKey("Questions_142");
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
			pchar.GenQuestRandItem.Shore46 = true;
			ReOpenQuestHeader("QM_Cumana");
			AddQuestRecord("QM_Cumana", "1");
			AddQuestUserData("QM_Cumana", "sName", GetFullName(npchar));
		break;
		case "Cumana_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = StringFromKey("Questions_143", NullCharacter.questions.(sTemp));
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Cumana_check";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;
		case "Cumana_7":
			dialog.text = StringFromKey("Questions_144");
			link.l1 = StringFromKey("Questions_145");
			link.l1.go = "exit";
			NextDiag.TempNode = "Cumana_again";
		break;
		case "Cumana_again":
			dialog.text = StringFromKey("Questions_146");
			link.l1 = StringFromKey("Questions_147");
			link.l1.go = "Cumana_6";
		break;
		//================================== Порт-Ройал ======================================
		case "PortRoyal":
			NextDiag.TempNode = "PortRoyal";
			dialog.text = StringFromKey("Questions_148", pchar);
			link.l1 = StringFromKey("Questions_149");
			link.l1.go = "exit_over";
			link.l2 = StringFromKey("Questions_150", GetAddress_FormToNPC(NPChar));
			link.l2.go = "PortRoyal_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "PortRoyal_1":
			dialog.text = StringFromKey("Questions_151");
			link.l1 = StringFromKey("Questions_152");
			link.l1.go = "PortRoyal_2";
		break;
		case "PortRoyal_2":
			dialog.text = StringFromKey("Questions_153");
			link.l1 = StringFromKey("Questions_154");
			link.l1.go = "PortRoyal_3";
		break;
		case "PortRoyal_3":
			dialog.text = StringFromKey("Questions_155");
			link.l1 = StringFromKey("Questions_156");
			link.l1.go = "PortRoyal_4";
			link.l2 = StringFromKey("Questions_157");
			link.l2.go = "All_disagree";
		break;
		case "PortRoyal_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = StringFromKey("Questions_158", NullCharacter.questions.(sTemp));
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortRoyal_check";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;
		case "PortRoyal_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = StringFromKey("Questions_159");
				link.l1 = StringFromKey("Questions_160");
				link.l1.go = "PortRoyal_ok";
			}
			else
			{
				dialog.text = StringFromKey("Questions_161", pchar);
				link.l1 = StringFromKey("Questions_162");
				link.l1.go = "PortRoyal_6";
				link.l2 = StringFromKey("Questions_163");
				link.l2.go = "PortRoyal_7";
			}
		break;
		case "PortRoyal_ok":
			dialog.text = StringFromKey("Questions_164");
			link.l1 = StringFromKey("Questions_165", pchar);
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
			pchar.GenQuestRandItem.Shore36 = true;
			ReOpenQuestHeader("QM_Port_Royal");
			AddQuestRecord("QM_Port_Royal", "1");
			AddQuestUserData("QM_Port_Royal", "sName", GetFullName(npchar));
		break;
		case "PortRoyal_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = StringFromKey("Questions_166", NullCharacter.questions.(sTemp));
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "PortRoyal_check";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;
		case "PortRoyal_7":
			dialog.text = StringFromKey("Questions_167", pchar);
			link.l1 = StringFromKey("Questions_168");
			link.l1.go = "exit";
			NextDiag.TempNode = "PortRoyal_again";
		break;
		case "PortRoyal_again":
			dialog.text = StringFromKey("Questions_169");
			link.l1 = StringFromKey("Questions_170");
			link.l1.go = "PortRoyal_6";
		break;
		//================================== Сантьяго ======================================
		case "Santiago":
			NextDiag.TempNode = "Santiago";
			dialog.text = StringFromKey("Questions_171");
			link.l1 = StringFromKey("Questions_172");
			link.l1.go = "exit_over";
			link.l2 = StringFromKey("Questions_173");
			link.l2.go = "Santiago_1";
			DeleteAttribute(npchar, "talker");
			npchar.LifeDay = 20;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		case "Santiago_1":
			dialog.text = StringFromKey("Questions_174");
			link.l1 = StringFromKey("Questions_175");
			link.l1.go = "Santiago_2";
		break;
		case "Santiago_2":
			dialog.text = StringFromKey("Questions_176");
			link.l1 = StringFromKey("Questions_177");
			link.l1.go = "Santiago_3";
		break;
		case "Santiago_3":
			dialog.text = StringFromKey("Questions_178");
			link.l1 = StringFromKey("Questions_179", pchar);
			link.l1.go = "Santiago_4";
			link.l2 = StringFromKey("Questions_180");
			link.l2.go = "All_disagree";
		break;
		case "Santiago_4":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = StringFromKey("Questions_181", NullCharacter.questions.(sTemp));
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Santiago_check";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;
		case "Santiago_check":
			sTemp = "a" + npchar.quest.numQuestion;
			if (NullCharacter.questions.(sTemp) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = StringFromKey("Questions_182");
				link.l1 = StringFromKey("Questions_183");
				link.l1.go = "Santiago_ok";
			}
			else
			{
				dialog.text = StringFromKey("Questions_184", pchar);
				link.l1 = StringFromKey("Questions_185");
				link.l1.go = "Santiago_6";
				link.l2 = StringFromKey("Questions_186");
				link.l2.go = "Santiago_7";
			}
		break;
		case "Santiago_ok":
			sTemp = GetConvertStr("itmname_pistol6", "ItemsDescribe.txt");
			dialog.text = StringFromKey("Questions_187", sTemp);
			link.l1 = StringFromKey("Questions_188");
			link.l1.go = "exit_over";
			NextDiag.TempNode = "good_all";
			pchar.GenQuestRandItem.Cuba_Grot = true;
			ReOpenQuestHeader("QM_Santiago");
			AddQuestRecord("QM_Santiago", "1");
			AddQuestUserData("QM_Santiago", "sName", GetFullName(npchar));
			AddQuestUserData("QM_Santiago", "sBladeName", sTemp);
		break;
		case "Santiago_6":
			sTemp = "q" + npchar.quest.numQuestion;
			dialog.text = StringFromKey("Questions_189", NullCharacter.questions.(sTemp));
			Link.l1.edit = 1;
			Link.l1 = "";
			Link.l1.go = "Santiago_check";

			SeaQuestion_Chinese_GenerateRandomAnswers(Npchar, Link);
		break;
		case "Santiago_7":
			dialog.text = StringFromKey("Questions_190");
			link.l1 = StringFromKey("Questions_191");
			link.l1.go = "exit";
			NextDiag.TempNode = "Santiago_again";
		break;
		case "Santiago_again":
			dialog.text = StringFromKey("Questions_192");
			link.l1 = StringFromKey("Questions_193");
			link.l1.go = "Santiago_6";
		break;

		// --- результаты женских квестов ---
		case "SCQ_womanResult":
			dialog.text = StringFromKey("Questions_194");
			link.l1 = StringFromKey("Questions_195", GetAddress_FormToNPC(NPChar));
			link.l1.go = "SCQ_womanResult_exit";
		break;
		case "womanHasbandover":
			dialog.text = StringFromKey("Questions_196");
			link.l1 = StringFromKey("Questions_197", GetAddress_FormToNPC(NPChar));
			link.l1.go = "SCQR_womanHasband";
		break;
		case "womanRevengeover":
			dialog.text = StringFromKey("Questions_198", npchar.quest.SeekCap.capName);
			link.l1 = StringFromKey("Questions_199", GetAddress_FormToNPC(NPChar));
			link.l1.go = "SCQR_womanRevenge";
		break;
		case "PirateFashionover":
			dialog.text = StringFromKey("Questions_200");
			link.l1 = StringFromKey("Questions_201");
			link.l1.go = "SCQR_PirateFashion";
		break;
		case "SCQ_womanResult_exit":
			switch (npchar.quest.SeekCap)
			{
				case "womanHasband":
					dialog.text = StringFromKey("Questions_202");
					link.l1 = StringFromKey("Questions_203", pchar);
					link.l1.go = "exit";
				break;
				case "womanRevenge":
					dialog.text = StringFromKey("Questions_204", npchar.quest.SeekCap.capName);
					link.l1 = StringFromKey("Questions_205", GetAddress_FormToNPC(NPChar));
					link.l1.go = "exit";
				break;
				case "PirateFashion":
					dialog.text = StringFromKey("Questions_206");
					link.l1 = StringFromKey("Questions_207", pchar, GetAddress_FormToNPC(NPChar), npchar.lastname);
					link.l1.go = "exit";
				break;
			}
		break;

		case "SCQR_womanHasband":
			dialog.text = StringFromKey("Questions_208");
			link.l1 = StringFromKey("Questions_209");
			link.l1.go = "SCQ_exit";
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(PChar, "jewelry4", 10);
			pchar.questTemp.womanHasband_Nagrada = true;
			AddQuestRecord("SCQ_Hasband_Truba", "5");
			AddQuestUserData("SCQ_Hasband_Truba", "sSex", GetSexPhrase("", "а"));
			RemoveLandQuestMark_Main(npchar, "SCQ_Hasband_Truba");
			if (CheckAttribute(pchar, "questTemp.womanHasband_Nagrada") && CheckAttribute(pchar, "questTemp.womanHasband_Truba"))
			{
				CloseQuestHeader("SCQ_Hasband_Truba");
				DeleteAttribute(pchar, "questTemp.womanHasband_Nagrada");
				DeleteAttribute(pchar, "questTemp.womanHasband_Truba");
			}
		break;
		case "SCQR_PirateFashion":
			dialog.text = StringFromKey("Questions_210");
			link.l1 = StringFromKey("Questions_211", pchar);
			link.l1.go = "SCQR_PirateFashion_2";
		break;
		case "SCQR_PirateFashion_2":
			dialog.text = StringFromKey("Questions_212", GetAddress_Form(NPChar), GetFullName(Pchar));
			link.l1 = StringFromKey("Questions_213");
			link.l1.go = "SCQR_PirateFashion_3";
			AddMoneyToCharacter(pchar, 5000);
			TakeNItems(PChar, "jewelry1", 10);
		break;
		case "SCQR_PirateFashion_3":
			dialog.text = StringFromKey("Questions_214", GetAddress_Form(NPChar), GetFullName(Pchar));
			link.l1 = StringFromKey("Questions_215");
			link.l1.go = "SCQ_exit";
			sld = characterFromId("QuetionsPortPax_MuzhPassajir");
			RemovePassenger(pchar, sld);
			sld.lifeDay = 0;
			sTemp = "SCQ_" + npchar.index;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание смерть горожанина-квестодателя
			AddQuestRecord("SCQ_PirateFashion", "5");
			pchar.GenQuestRandItem.Tortuga_Cave = true;
			RemoveLandQuestMark_Main(npchar, "SCQ_PirateFashion");
		break;

		case "Question_chinese_check":
			dialogEditStrings[1] = TEV.SeaQuestionTemp.Answer;
			Dialog.CurrentNode = TEV.SeaQuestionTemp;

			DeleteAttribute(&TEV, "SeaQuestionTemp");
			ProcessDialogEvent();
		break;
	}
}

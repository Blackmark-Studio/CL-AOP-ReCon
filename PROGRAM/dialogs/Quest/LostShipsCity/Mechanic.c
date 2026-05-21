void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp;
	string sTemp;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("Mechanic_1", pchar);
			link.l1 = StringFromKey("Mechanic_2");
			link.l1.go = "FT_1";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//обнаружение ГГ в сундуках
		case "fight":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetOwnerTypeNoGroup(npchar);
			LAi_group_Attack(NPChar, Pchar);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "Man_FackYou":
			dialog.text = StringFromKey("Mechanic_6", LinkRandPhrase(
						StringFromKey("Mechanic_3", pchar),
						StringFromKey("Mechanic_4", pchar),
						StringFromKey("Mechanic_5", pchar)));
			link.l1 = StringFromKey("Mechanic_7");
			link.l1.go = "fight";
		break;
		case "Woman_FackYou":
			dialog.text = StringFromKey("Mechanic_8");
			link.l1 = StringFromKey("Mechanic_9");
			link.l1.go = "exit_setOwner";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//замечение по обнаженному оружию
		case "LSCNotBlade":
			dialog.text = StringFromKey("Mechanic_13", LinkRandPhrase(
						StringFromKey("Mechanic_10", pchar),
						StringFromKey("Mechanic_11"),
						StringFromKey("Mechanic_12", pchar)));
			link.l1 = StringFromKey("Mechanic_17", LinkRandPhrase(
						StringFromKey("Mechanic_14"),
						StringFromKey("Mechanic_15"),
						StringFromKey("Mechanic_16")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			if (loadedLocation.type == "town")
			{
				dialog.text = StringFromKey("Mechanic_18", npchar);
				link.l1 = StringFromKey("Mechanic_22", LinkRandPhrase(
							StringFromKey("Mechanic_19"),
							StringFromKey("Mechanic_20"),
							StringFromKey("Mechanic_21")));
			}
			else
			{
				dialog.text = StringFromKey("Mechanic_23", npchar);
				link.l1 = StringFromKey("Mechanic_26", RandPhraseSimple(
							StringFromKey("Mechanic_24", pchar),
							StringFromKey("Mechanic_25")));
			}
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;

		case "FT_1":
			dialog.text = StringFromKey("Mechanic_27", pchar);
			link.l1 = StringFromKey("Mechanic_28", GetFullName(pchar));
			link.l1.go = "FT_2";
			//теперь можно тепаться к Механику
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false);
		break;
		case "FT_2":
			dialog.text = StringFromKey("Mechanic_29");
			link.l1 = StringFromKey("Mechanic_30");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("Mechanic_31");
			link.l1 = StringFromKey("Mechanic_32", pchar);
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("Mechanic_33");
			link.l1 = StringFromKey("Mechanic_34", pchar);
			link.l1.go = "FT_5";
		break;
		case "FT_5":
			dialog.text = StringFromKey("Mechanic_35");
			link.l1 = StringFromKey("Mechanic_36");
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = StringFromKey("Mechanic_37");
			link.l1 = StringFromKey("Mechanic_38");
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = StringFromKey("Mechanic_39");
			link.l1 = StringFromKey("Mechanic_40");
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = StringFromKey("Mechanic_41");
			link.l1 = StringFromKey("Mechanic_42");
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = StringFromKey("Mechanic_43");
			link.l1 = StringFromKey("Mechanic_44", pchar);
			link.l1.go = "FT_10";
		break;
		case "FT_10":
			dialog.text = StringFromKey("Mechanic_45");
			link.l1 = StringFromKey("Mechanic_46");
			link.l1.go = "FT_11";
		break;
		case "FT_11":
			dialog.text = StringFromKey("Mechanic_47", pchar);
			link.l1 = StringFromKey("Mechanic_48", pchar);
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = StringFromKey("Mechanic_49");
			link.l1 = StringFromKey("Mechanic_50", pchar);
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = StringFromKey("Mechanic_51", pchar);
			link.l1 = StringFromKey("Mechanic_52");
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = StringFromKey("Mechanic_53");
			link.l1 = StringFromKey("Mechanic_54");
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = StringFromKey("Mechanic_55", pchar);
			link.l1 = StringFromKey("Mechanic_56");
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			dialog.text = StringFromKey("Mechanic_57");
			link.l1 = StringFromKey("Mechanic_58", pchar);
			link.l1.go = "FT_17";
		break;
		case "FT_17":
			dialog.text = StringFromKey("Mechanic_59");
			link.l1 = StringFromKey("Mechanic_60");
			link.l1.go = "FT_18";
		break;
		case "FT_18":
			dialog.text = StringFromKey("Mechanic_61");
			link.l1 = StringFromKey("Mechanic_62");
			link.l1.go = "FT_19";
		break;
		case "FT_19":
			dialog.text = StringFromKey("Mechanic_63");
			link.l1 = StringFromKey("Mechanic_64");
			link.l1.go = "FT_20";
		break;
		case "FT_20":
			dialog.text = StringFromKey("Mechanic_65");
			link.l1 = StringFromKey("Mechanic_66");
			link.l1.go = "FT_21";
		break;
		case "FT_21":
			dialog.text = StringFromKey("Mechanic_67");
			//            if (GetCharacterSPECIAL(pchar, SPECIAL_I) > 7)
			if (PlayerRPGCheck_SPECIAL(SPECIAL_I, 8))
			{
				link.l1 = StringFromKey("Mechanic_68");
				link.l1.go = "FT_21_1";
			}
			link.l2 = StringFromKey("Mechanic_69");
			link.l2.go = "FT_21_0";
		break;
		case "FT_21_0":
			dialog.text = StringFromKey("Mechanic_70", pchar);
			link.l1 = StringFromKey("Mechanic_71");
			link.l1.go = "FT_22";
		break;
		case "FT_21_1":
			dialog.text = StringFromKey("Mechanic_72");
			link.l1 = StringFromKey("Mechanic_73");
			link.l1.go = "FT_22";
		break;
		case "FT_22":
			dialog.text = StringFromKey("Mechanic_74");
			link.l1 = StringFromKey("Mechanic_75");
			link.l1.go = "FT_23";
		break;
		case "FT_23":
			dialog.text = StringFromKey("Mechanic_76");
			link.l1 = StringFromKey("Mechanic_77");
			link.l1.go = "FT_24";
		break;
		case "FT_24":
			dialog.text = StringFromKey("Mechanic_78");
			link.l1 = StringFromKey("Mechanic_79");
			link.l1.go = "FT_25";
		break;
		case "FT_25":
			dialog.text = StringFromKey("Mechanic_80");
			link.l1 = StringFromKey("Mechanic_81", pchar);
			link.l1.go = "FT_26";
		break;
		case "FT_26":
			dialog.text = StringFromKey("Mechanic_82");
			link.l1 = StringFromKey("Mechanic_83");
			link.l1.go = "FT_27";
		break;
		case "FT_27":
			dialog.text = StringFromKey("Mechanic_84", pchar);
			link.l1 = StringFromKey("Mechanic_85", pchar);
			link.l1.go = "FT_28";
		break;
		case "FT_28":
			dialog.text = StringFromKey("Mechanic_86");
			link.l1 = StringFromKey("Mechanic_87");
			link.l1.go = "FT_29";
			if (sti(pchar.money >= 1500000))
			{
				link.l2 = StringFromKey("Mechanic_88");
				link.l2.go = "FT_31";
			}
		break;
		case "FT_29":
			dialog.text = StringFromKey("Mechanic_89", pchar);
			link.l1 = StringFromKey("Mechanic_90");
			link.l1.go = "FT_30";
		break;
		case "FT_30":
			dialog.text = StringFromKey("Mechanic_91");
			link.l1 = StringFromKey("Mechanic_92");
			link.l1.go = "FT_30_1";
		break;
		case "FT_30_1":
			dialog.text = StringFromKey("Mechanic_93");
			link.l1 = StringFromKey("Mechanic_94", pchar);
			link.l1.go = "FT_31";
		break;
		case "FT_31":
			dialog.text = StringFromKey("Mechanic_95", pchar);
			link.l1 = StringFromKey("Mechanic_96", pchar);
			link.l1.go = "FT_32";
		break;
		case "FT_32":
			dialog.text = StringFromKey("Mechanic_97");
			link.l1 = StringFromKey("Mechanic_98");
			link.l1.go = "FT_33";
		break;
		case "FT_33":
			dialog.text = StringFromKey("Mechanic_99");
			link.l1 = StringFromKey("Mechanic_100");
			link.l1.go = "FT_34";
		break;
		case "FT_34":
			dialog.text = StringFromKey("Mechanic_101", pchar);
			link.l1 = StringFromKey("Mechanic_102");
			link.l1.go = "FT_35";
		break;
		case "FT_35":
			dialog.text = StringFromKey("Mechanic_103");
			link.l1 = StringFromKey("Mechanic_104", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "CheckMillion";
			pchar.questTemp.LSC = "fromMechanicToAdmiral";
			Npchar.quest.money = 0; //счетчик бабла, отданного Механику
			AddQuestRecord("ISS_MainLine", "34");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("", "а"));
			AddQuestUserData("ISS_MainLine", "sSex2", GetSexPhrase("ен", "на"));
			AddLandQuestMark_Main(CharacterFromID("LSCMayor"), "ISS_MainLine");
		break;

		//проверка миллиона
		case "CheckMillion":
			dialog.text = StringFromKey("Mechanic_105");
			if (sti(pchar.money) < 1500000)
			{
				link.l1 = StringFromKey("Mechanic_106", pchar);
				link.l1.go = "CheckMillion_noMoney";
			}
			else
			{
				link.l1 = StringFromKey("Mechanic_107", pchar);
				link.l1.go = "OffM_GiveMoney_1";
			}
			NextDiag.TempNode = "CheckMillion";
		break;
		case "CheckMillion_noMoney":
			dialog.text = StringFromKey("Mechanic_108");
			link.l1 = StringFromKey("Mechanic_109");
			link.l1.go = "exit";
		break;
		case "OffM_GiveMoney_1":
			AddMoneyToCharacter(pchar, -1500000);
			dialog.text = StringFromKey("Mechanic_110");
			link.l1 = StringFromKey("Mechanic_111");
			link.l1.go = "FreeCorvett";
		break;
		//освобождние корвета
		case "FreeCorvett":
			dialog.text = StringFromKey("Mechanic_112");
			link.l1 = StringFromKey("Mechanic_113");
			link.l1.go = "FreeCorvett_1";
		break;
		case "FreeCorvett_1":
			dialog.text = StringFromKey("Mechanic_114");
			link.l1 = StringFromKey("Mechanic_115");
			link.l1.go = "FreeCorvett_2";
		break;
		case "FreeCorvett_2":
			dialog.text = StringFromKey("Mechanic_116");
			link.l1 = StringFromKey("Mechanic_117");
			link.l1.go = "FreeCorvett_3";
		break;
		case "FreeCorvett_3":
			dialog.text = StringFromKey("Mechanic_118");
			link.l1 = StringFromKey("Mechanic_119");
			link.l1.go = "FreeCorvett_4";
			link.l2 = StringFromKey("Mechanic_120");
			link.l2.go = "FreeCorvett_4";
		break;
		case "FreeCorvett_4":
			dialog.text = StringFromKey("Mechanic_121");
			link.l1 = StringFromKey("Mechanic_122");
			link.l1.go = "FreeCorvett_5";
		break;
		case "FreeCorvett_5":
			dialog.text = StringFromKey("Mechanic_123");
			link.l1 = StringFromKey("Mechanic_124", pchar);
			link.l1.go = "FreeCorvett_6";
		break;
		case "FreeCorvett_6":
			dialog.text = StringFromKey("Mechanic_125");
			link.l1 = StringFromKey("Mechanic_126", pchar);
			link.l1.go = "FreeCorvett_7";
		break;
		case "FreeCorvett_7":
			dialog.text = StringFromKey("Mechanic_127");
			link.l1 = StringFromKey("Mechanic_128");
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor";
			pchar.questTemp.LSC = "toUnderwater";
			pchar.questTemp.LSC.immersions = 0; //количество совершенных погружений
			// pchar.questTemp.LSC.immersions.model = pchar.model; //запомним модельку ГГ
			// pchar.questTemp.LSC.immersions.animation = pchar.model.animation;
			pchar.questTemp.LSC.immersions.pay = true; //оплачено
			pchar.questTemp.LSC.immersions.pinion = false; //флаг найденной шестерёнки
			AddQuestRecord("ISS_MainLine", "36");
			pchar.Ship.Type = GenerateShipExt(SHIP_CORVETTE_QUEST, false, pchar);
			pchar.questTemp.LSC.IgnoreShipStatPenalty = true;
			SetBaseShipData(pchar);
			pchar.Ship.name = FindPersonalName("LSC_ship");
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS24;
			SetCharacterGoods(pchar, GOOD_BALLS, 0);
			SetCharacterGoods(pchar, GOOD_GRAPES, 0);
			SetCharacterGoods(pchar, GOOD_KNIPPELS, 0);
			SetCharacterGoods(pchar, GOOD_BOMBS, 0);
			SetCharacterGoods(pchar, GOOD_SAILCLOTH, 0);
			SetCharacterGoods(pchar, GOOD_PLANKS, 0);
			SetCharacterGoods(pchar, GOOD_POWDER, 0);
			SetCharacterGoods(pchar, GOOD_FOOD, 0);
			SetCharacterGoods(pchar, GOOD_WEAPON, 0);
			SetCharacterGoods(pchar, GOOD_MEDICAMENT, 0);
			SetCrewQuantity(pchar, 0);
			AddSimpleRumourCityTip(
				StringFromKey("Mechanic_129"), "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip(
				StringFromKey("Mechanic_130"), "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip(
				StringFromKey("Mechanic_131"), "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip(
				StringFromKey("Mechanic_132"), "LostShipsCity", 10, 1, "LSC", "");
			// нулим предметы в каюте
			ref loc;
			int n;
			if (Pchar.SystemInfo.CabinType != "")
			{
				loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; //"My_Cabin"

				for (n = 1; n <= 4; n++)
				{
					sTemp = "box" + n;
					DeleteAttribute(loc, sTemp + ".items");
					loc.(sTemp).items = "";
					loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
					loc.(sTemp).money = 0;
				}
			}
			loc = &locations[FindLocation("My_Deck")];
			for (n = 1; n <= 4; n++)
			{
				sTemp = "box" + n;
				DeleteAttribute(loc, sTemp + ".items");
				loc.(sTemp).items = "";
				loc.(sTemp) = Items_MakeTime(0, 0, 1, 2003);
				loc.(sTemp).money = 0;
			}
			// снимем квест-метки
			RemoveLandQuestMark_Main(CharacterFromID("LSCwaitress"), "ISS_MainLine");
			RemoveLandQuestMark_Main(CharacterFromID("LSCMayor"), "ISS_MainLine");
			AddLandQuestMark_Main_WithCondition(npchar, "ISS_MainLine", "LSC_ToUnderwater_Mechanic_QuestMarkCondition");
		break;
		//
		case "takeArmor":
			dialog.text = StringFromKey("Mechanic_133");
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				link.l1 = StringFromKey("Mechanic_134");
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = StringFromKey("Mechanic_135", pchar);
				link.l1.go = "DeepAgain";
				if (CheckCharacterItem(pchar, "Pinion"))
				{
					link.l2 = StringFromKey("Mechanic_136", pchar);
					link.l2.go = "FoundPinion";
				}
			}
		break;

		case "DeepAgain":
			dialog.text = StringFromKey("Mechanic_137");
			link.l1 = StringFromKey("Mechanic_138", pchar);
			link.l1.go = "DeepAgain_1";
		break;
		case "DeepAgain_1":
			dialog.text = StringFromKey("Mechanic_139");
			link.l1 = StringFromKey("Mechanic_140");
			link.l1.go = "DeepAgain_2";
		break;
		case "DeepAgain_2":
			dialog.text = StringFromKey("Mechanic_141");
			link.l1 = StringFromKey("Mechanic_142");
			link.l1.go = "DeepAgain_3";
		break;
		case "DeepAgain_3":
			dialog.text = StringFromKey("Mechanic_143", pchar);
			link.l1 = StringFromKey("Mechanic_144");
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor2";
		break;

		case "takeArmor2":
			dialog.text = StringFromKey("Mechanic_145");
			if (sti(pchar.questTemp.LSC.immersions.pay))
			{
				link.l1 = StringFromKey("Mechanic_146");
				link.l1.go = "exit";
			}
			else
			{
				link.l1 = StringFromKey("Mechanic_147");
				link.l1.go = "DeepAgain2";
				if (CheckCharacterItem(pchar, "Pinion"))
				{
					link.l2 = StringFromKey("Mechanic_148", pchar);
					link.l2.go = "FoundPinion";
				}
			}
			if (sti(pchar.questTemp.LSC.immersions.pinion))
			{
				link.l3 = StringFromKey("Mechanic_149", pchar);
				link.l3.go = "endImmersion";
			}
		break;

		case "DeepAgain2":
			dialog.text = StringFromKey("Mechanic_150");
			if (sti(pchar.money) >= 30000)
			{
				link.l1 = StringFromKey("Mechanic_151", pchar);
				link.l1.go = "DeepAgain2_1";
			}
			else
			{
				link.l1 = StringFromKey("Mechanic_152");
				link.l1.go = "exit";
			}
		break;
		case "DeepAgain2_1":
			dialog.text = StringFromKey("Mechanic_153");
			link.l1 = StringFromKey("Mechanic_154");
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -30000);
			SaveCurrentQuestDateParam("questTemp.LSC.immersions");
			NextDiag.TempNode = "readyArmor";
		break;
		case "readyArmor":
			if (GetQuestPastDayParam("questTemp.LSC.immersions") >= 1)
			{
				dialog.text = StringFromKey("Mechanic_155");
				link.l1 = StringFromKey("Mechanic_156");
				link.l1.go = "exit";
				pchar.questTemp.LSC.immersions.pay = true; //оплачено
				NextDiag.TempNode = "takeArmor2";
			}
			else
			{
				dialog.text = StringFromKey("Mechanic_157");
				link.l1 = StringFromKey("Mechanic_158");
				link.l1.go = "exit";
			}
		break;

		case "FoundPinion":
			dialog.text = StringFromKey("Mechanic_159");
			link.l1 = StringFromKey("Mechanic_160");
			link.l1.go = "FoundPinion_1";
		break;
		case "FoundPinion_1":
			dialog.text = StringFromKey("Mechanic_161");
			link.l1 = StringFromKey("Mechanic_162");
			link.l1.go = "FoundPinion_deep";
			link.l2 = StringFromKey("Mechanic_163");
			link.l2.go = "endImmersion";
			TakeItemFromCharacter(pchar, "Pinion");
			pchar.questTemp.LSC.immersions.pinion = true; //нашёл шестеренку
			AddQuestRecord("ISS_MainLine", "38");
		break;
		case "FoundPinion_deep":
			dialog.text = StringFromKey("Mechanic_164");
			link.l1 = StringFromKey("Mechanic_165");
			link.l1.go = "exit";
			NextDiag.TempNode = "takeArmor2";
		break;

		case "endImmersion":
			dialog.text = StringFromKey("Mechanic_166");
			link.l1 = StringFromKey("Mechanic_167");
			link.l1.go = "endImmersion_1";
		break;
		case "endImmersion_1":
			dialog.text = StringFromKey("Mechanic_168");
			link.l1 = StringFromKey("Mechanic_169");
			link.l1.go = "endImmersion_2";
		break;
		case "endImmersion_2":
			dialog.text = StringFromKey("Mechanic_170", pchar);
			link.l1 = StringFromKey("Mechanic_171");
			link.l1.go = "endImmersion_3";
		break;
		case "endImmersion_3":
			dialog.text = StringFromKey("Mechanic_172");
			link.l1 = StringFromKey("Mechanic_173");
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "39");
			pchar.questTemp.LSC = "toSeekStevedore";
			NextDiag.TempNode = "foundStevedore";
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("LSCBarmen"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("MalcolmFawn"), "ISS_MainLine");
		break;

		case "foundStevedore":
			dialog.text = StringFromKey("Mechanic_174");
			if (pchar.questTemp.LSC == "foundStevedore")
			{
				link.l1 = StringFromKey("Mechanic_175");
				link.l1.go = "foundStevedore_1";
			}
			else
			{
				link.l1 = StringFromKey("Mechanic_176");
				link.l1.go = "exit";
			}
		break;
		case "foundStevedore_1":
			dialog.text = StringFromKey("Mechanic_177", pchar);
			link.l1 = StringFromKey("Mechanic_178");
			link.l1.go = "foundStevedore_2";
		break;
		case "foundStevedore_2":
			dialog.text = StringFromKey("Mechanic_179");
			link.l1 = StringFromKey("Mechanic_180", pchar);
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.LSC.immersions");
			AddQuestRecord("ISS_MainLine", "40");
			pchar.questTemp.LSC = "toSeekGoods";
			DeleteShellBoat("LostShipsCity_town");
			DeployShipToReload("LostShipsCity_town", "locators.reload.reload_fawn");
			NextDiag.TempNode = "takeGoods";
			sld = CharacterFromId("MalcolmFawn");
			sld.cityTape = "quest"; //тип нпс
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "quest", "fawn");
			//теперь можно тепаться в Диффиндур
			LocatorReloadEnterDisable("LostShipsCity_town", "reload72", false);

			AddLandQuestMark_Main_WithCondition(npchar, "ISS_MainLine", "LSC_ToSeekGoods_Mechanic_QuestMarkCondition");
			AddLandQuestMark_Main(CharacterFromID("LSCMayor"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("ElisTaylor"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("ElizaCalvo"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("LeaToors"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("OreliBertin"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("LSC_Trader"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("LSC_Priest"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("LSCwaitress"), "ISS_MainLine");

			AddLandQuestMark_Main(CharacterFromID("MalcolmFawn"), "ISS_MainLine");
		break;
		//комплектование корвета товарами
		case "takeGoods":
			NextDiag.TempNode = "takeGoods";
			dialog.text = StringFromKey("Mechanic_181");
			npchar.quest.LSC.Balls = false;
			npchar.quest.LSC.Grapes = false;
			npchar.quest.LSC.Knippels = false;
			npchar.quest.LSC.Bombs = false;
			npchar.quest.LSC.Sailcloth = false; //магазин
			npchar.quest.LSC.Planks = false; //магазин
			npchar.quest.LSC.Powder = false;
			npchar.quest.LSC.Food = false; //магазин
			npchar.quest.LSC.Weapon = false;
			npchar.quest.LSC.Medicament = false;
			iTemp = 0;
			npchar.quest.LSC.s0 = "";
			npchar.quest.LSC.s1 = "";
			if (GetCargoGoods(pchar, GOOD_BALLS) >= 100)
			{
				npchar.quest.LSC.Balls = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Balls;
			npchar.quest.LSC.(sTemp) = StringFromKey("Mechanic_182", npchar.quest.LSC.(sTemp));
			if (GetCargoGoods(pchar, GOOD_GRAPES) >= 100)
			{
				npchar.quest.LSC.Grapes = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Grapes;
			npchar.quest.LSC.(sTemp) = StringFromKey("Mechanic_183", npchar.quest.LSC.(sTemp));
			if (GetCargoGoods(pchar, GOOD_KNIPPELS) >= 100)
			{
				npchar.quest.LSC.Knippels = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Knippels;
			npchar.quest.LSC.(sTemp) = StringFromKey("Mechanic_184", npchar.quest.LSC.(sTemp));
			if (GetCargoGoods(pchar, GOOD_BOMBS) >= 100)
			{
				npchar.quest.LSC.Bombs = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Bombs;
			npchar.quest.LSC.(sTemp) = StringFromKey("Mechanic_185", npchar.quest.LSC.(sTemp));
			if (GetCargoGoods(pchar, GOOD_SAILCLOTH) >= 50)
			{
				npchar.quest.LSC.Sailcloth = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Sailcloth;
			npchar.quest.LSC.(sTemp) = StringFromKey("Mechanic_186", npchar.quest.LSC.(sTemp));
			if (GetCargoGoods(pchar, GOOD_PLANKS) >= 50)
			{
				npchar.quest.LSC.Planks = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Planks;
			npchar.quest.LSC.(sTemp) = StringFromKey("Mechanic_187", npchar.quest.LSC.(sTemp));
			if (GetCargoGoods(pchar, GOOD_POWDER) >= 200)
			{
				npchar.quest.LSC.Powder = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Powder;
			npchar.quest.LSC.(sTemp) = StringFromKey("Mechanic_188", npchar.quest.LSC.(sTemp));
			if (GetCargoGoods(pchar, GOOD_FOOD) >= 200)
			{
				npchar.quest.LSC.Food = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Food;
			npchar.quest.LSC.(sTemp) = StringFromKey("Mechanic_189", npchar.quest.LSC.(sTemp));
			if (GetCargoGoods(pchar, GOOD_WEAPON) >= 50)
			{
				npchar.quest.LSC.Weapon = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Weapon;
			npchar.quest.LSC.(sTemp) = StringFromKey("Mechanic_190", npchar.quest.LSC.(sTemp));
			if (GetCargoGoods(pchar, GOOD_MEDICAMENT) >= 50)
			{
				npchar.quest.LSC.Medicament = true;
				iTemp++;
			}
			sTemp = "s" + npchar.quest.LSC.Medicament;
			npchar.quest.LSC.(sTemp) = StringFromKey("Mechanic_191", npchar.quest.LSC.(sTemp));
			if (iTemp < 10)
			{
				if (iTemp == 0)
				{
					link.l1 = StringFromKey("Mechanic_192", pchar);
				}
				else
				{
					sTemp = npchar.quest.LSC.s0;
					npchar.quest.LSC.s0 = strcut(sTemp, 0, (strlen(sTemp) - 2));
					sTemp = npchar.quest.LSC.s1;
					npchar.quest.LSC.s1 = strcut(sTemp, 0, (strlen(sTemp) - 2));
					link.l1 = StringFromKey("Mechanic_193", npchar.quest.LSC.s1, npchar.quest.LSC.s0);
				}
				link.l1.go = "takeGoods_again";
			}
			else
			{
				link.l1 = StringFromKey("Mechanic_194");
				link.l1.go = "TakeCrew";
				DeleteAttribute(pchar, "questTemp.LSC.Balls");
				DeleteAttribute(pchar, "questTemp.LSC.Grapes");
				DeleteAttribute(pchar, "questTemp.LSC.Knippels");
				DeleteAttribute(pchar, "questTemp.LSC.Bombs");
				DeleteAttribute(pchar, "questTemp.LSC.Sailcloth");
				DeleteAttribute(pchar, "questTemp.LSC.Planks");
				DeleteAttribute(pchar, "questTemp.LSC.Powder");
				DeleteAttribute(pchar, "questTemp.LSC.Food");
				DeleteAttribute(pchar, "questTemp.LSC.Weapon");
				DeleteAttribute(pchar, "questTemp.LSC.Medicament");
				DeleteAttribute(pchar, "questTemp.LSC.additional");
			}
		break;
		case "takeGoods_again":
			dialog.text = StringFromKey("Mechanic_195");
			link.l1 = StringFromKey("Mechanic_196");
			link.l1.go = "exit";
		break;
		//Набор команды
		case "TakeCrew":
			dialog.text = StringFromKey("Mechanic_197", pchar);
			link.l1 = StringFromKey("Mechanic_198", pchar);
			link.l1.go = "TakeCrew_1";
		break;
		case "TakeCrew_1":
			dialog.text = StringFromKey("Mechanic_199");
			link.l1 = StringFromKey("Mechanic_200");
			link.l1.go = "TakeCrew_2";
		break;
		case "TakeCrew_2":
			dialog.text = StringFromKey("Mechanic_201");
			link.l1 = StringFromKey("Mechanic_202");
			link.l1.go = "TakeCrew_3";
		break;
		case "TakeCrew_3":
			dialog.text = StringFromKey("Mechanic_203");
			link.l1 = StringFromKey("Mechanic_204");
			link.l1.go = "TakeCrew_4";
		break;
		case "TakeCrew_4":
			dialog.text = StringFromKey("Mechanic_205", pchar.name);
			link.l1 = StringFromKey("Mechanic_206");
			link.l1.go = "TakeCrew_5";
		break;
		case "TakeCrew_5":
			dialog.text = StringFromKey("Mechanic_207");
			link.l1 = StringFromKey("Mechanic_208", pchar);
			link.l1.go = "TakeCrew_6";
			link.l2 = StringFromKey("Mechanic_209");
			link.l2.go = "TakeCrew_7";
			NextDiag.TempNode = "TakeCrewNew";
			pchar.questTemp.LSC = "toSeekPeopleInCrew";
			AddDialogExitQuestFunction("LSC_SmallStormIsBegin");
			//важные персонажи в общий счетчик не идут и их можно взять всегда
			sld = CharacterFromId("Ment_6");
			sld.quest.toSeekPeopleInCrew = true;
			AddLandQuestMark_Main(sld, "ISS_MainLine");
			sld = CharacterFromId("MalcolmFawn");
			sld.quest.toSeekPeopleInCrew = true;
			RemoveLandQuestMark_Main(sld, "ISS_MainLine");

			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		case "TakeCrew_6":
			AddQuestRecord("ISS_MainLine", "54");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ен", "на"));
			pchar.questTemp.LSC.crew = 0; //количество уговоренных людей.
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		case "TakeCrew_7":
			dialog.text = StringFromKey("Mechanic_210");
			link.l1 = StringFromKey("Mechanic_211");
			link.l1.go = "TakeCrew_8";
		break;
		case "TakeCrew_8":
			dialog.text = StringFromKey("Mechanic_212");
			link.l1 = StringFromKey("Mechanic_213");
			link.l1.go = "TakeCrew_9";
		break;
		case "TakeCrew_9":
			dialog.text = StringFromKey("Mechanic_214");
			link.l1 = StringFromKey("Mechanic_215");
			link.l1.go = "TakeCrew_10";
		break;
		case "TakeCrew_10":
			dialog.text = StringFromKey("Mechanic_216");
			link.l1 = StringFromKey("Mechanic_217");
			link.l1.go = "TakeCrew_11";
		break;
		case "TakeCrew_11":
			dialog.text = StringFromKey("Mechanic_218", pchar);
			link.l1 = StringFromKey("Mechanic_219");
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "55");
			AddLandQuestMark_Main(CharacterFromID("OreliBertin"), "ISS_MainLine");
		break;
		//прием народа в команду
		case "TakeCrewNew":
			if (pchar.questTemp.LSC == "toCrewCollection")
			{
				dialog.text = StringFromKey("Mechanic_220");
				link.l1 = StringFromKey("Mechanic_221");
				link.l1.go = "TakeCrewNew_1";
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.LSC.crew") && sti(pchar.questTemp.LSC.crew) > 0)
				{
					dialog.text = StringFromKey("Mechanic_222", FindPeoplesString(sti(pchar.questTemp.LSC.crew), "Acc"));
				}
				else
				{
					dialog.text = StringFromKey("Mechanic_223");
				}
				link.l1 = StringFromKey("Mechanic_224");
				link.l1.go = "exit";
			}
		break;
		case "TakeCrewNew_1":
			dialog.text = StringFromKey("Mechanic_225");
			link.l1 = StringFromKey("Mechanic_226");
			link.l1.go = "TakeCrewNew_2";
		break;
		case "TakeCrewNew_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuestFunction("LSC_MoveSeekCrewToTavern");

			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 4.0);
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//разговор в тюрьме
		case "inPrison":
			dialog.text = StringFromKey("Mechanic_227");
			link.l1 = StringFromKey("Mechanic_228");
			link.l1.go = "inPrison_1";
		break;
		case "inPrison_1":
			dialog.text = StringFromKey("Mechanic_229");
			link.l1 = StringFromKey("Mechanic_230");
			link.l1.go = "inPrison_2";
		break;
		case "inPrison_2":
			dialog.text = StringFromKey("Mechanic_231");
			link.l1 = StringFromKey("Mechanic_232", pchar);
			link.l1.go = "inPrison_3";
		break;
		case "inPrison_3":
			dialog.text = StringFromKey("Mechanic_233", pchar);
			link.l1 = StringFromKey("Mechanic_234");
			link.l1.go = "inPrison_4";
		break;
		case "inPrison_4":
			dialog.text = StringFromKey("Mechanic_235");
			link.l1 = StringFromKey("Mechanic_236");
			link.l1.go = "inPrison_4_1";
		break;
		case "inPrison_4_1":
			dialog.text = StringFromKey("Mechanic_237");
			link.l1 = StringFromKey("Mechanic_238");
			link.l1.go = "inPrison_5";
		break;
		case "inPrison_5":
			dialog.text = StringFromKey("Mechanic_239");
			link.l1 = StringFromKey("Mechanic_240");
			link.l1.go = "inPrison_6";
		break;
		case "inPrison_6":
			dialog.text = StringFromKey("Mechanic_241", pchar);
			link.l1 = StringFromKey("Mechanic_242");
			link.l1.go = "inPrison_7";
		break;
		case "inPrison_7":
			dialog.text = StringFromKey("Mechanic_243");
			link.l1 = StringFromKey("Mechanic_244", pchar);
			link.l1.go = "inPrison_8";
		break;
		case "inPrison_8":
			dialog.text = StringFromKey("Mechanic_245");
			link.l1 = StringFromKey("Mechanic_246");
			link.l1.go = "inPrison_9";
		break;
		case "inPrison_9":
			dialog.text = StringFromKey("Mechanic_247");
			link.l1 = StringFromKey("Mechanic_248");
			link.l1.go = "exit";
			chrDisableReloadToLocation = false;
			LAi_CharacterDisableDialog(npchar);
			GiveItem2Character(pchar, "stop_storm");
			AddQuestRecord("ISS_MainLine", "63");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся", "ась"));
			AddDialogExitQuestFunction("LSC_BigStormIsBegin");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
	}
}

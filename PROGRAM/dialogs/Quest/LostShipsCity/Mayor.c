void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iTemp, i;

	string NodeName = Dialog.CurrentNode;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (npchar.location == "SanAugustineResidence")
			{
				dialog.text = StringFromKey("Mayor_1", pchar);
				link.l1 = StringFromKey("Mayor_2", pchar);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = StringFromKey("Mayor_3", pchar);
				link.l1 = StringFromKey("Mayor_4", pchar);
				link.l1.go = "NRes_1";
			}
			NextDiag.TempNode = "First time";
			if (npchar.quest.meeting == "0")
			{
				npchar.quest.meeting = "1";
				pchar.questTemp.LSC = "AdmiralFoundHero";
				if (CheckAttribute(loadedLocation, "storm"))
				{
					dialog.text = StringFromKey("Mayor_5", pchar);
					link.l1 = StringFromKey("Mayor_6", pchar, GetFullName(pchar));
					link.l1.go = "FT_1";
					PChar.quest.LSC_admiralOwnFind.over = "yes";
				}
				else
				{
					dialog.text = StringFromKey("Mayor_7");
					link.l1 = StringFromKey("Mayor_8", GetFullName(pchar));
					link.l1.go = "FT_1";
				}
				break;
			}
			//квестовые ноды по главной линейке
			if (pchar.questTemp.LSC == "toAdmNarvalRing" && CheckCharacterItem(pchar, "RingNarval"))
			{
				link.l4 = StringFromKey("Mayor_9");
				link.l4.go = "NarvalRing_1";
			}
			if (pchar.questTemp.LSC == "NarvalDestroyed")
			{
				link.l4 = StringFromKey("Mayor_10", pchar);
				link.l4.go = "DestrNarval_1";
			}
			if (pchar.questTemp.LSC == "toAdmiralBarmenDead")
			{
				link.l4 = StringFromKey("Mayor_11", pchar);
				link.l4.go = "BarmenDead_1";
			}
			if (pchar.questTemp.LSC == "fromMechanicToAdmiral")
			{
				link.l4 = StringFromKey("Mayor_12", pchar);
				link.l4.go = "CasperDead_1";
			}
			//дополнительные квестовые ноды
			//муж Элис Тейлор
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC != "AdmiralIsWaiting" && pchar.questTemp.LSC.ElisHusband == "toElis")
			{
				link.l5 = StringFromKey("Mayor_13");
				link.l5.go = "ELTHusb_begin";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiral")
			{
				link.l5 = StringFromKey("Mayor_14", pchar);
				link.l5.go = "ELTHusb_SF";
			}
			if (CheckAttribute(pchar, "questTemp.LSC.ElisHusband") && pchar.questTemp.LSC.ElisHusband == "toAdmiralGood")
			{
				link.l5 = StringFromKey("Mayor_15", pchar);
				link.l5.go = "ELTHusb_good";
			}
			//квест со скелетом Декстера
			if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && pchar.questTemp.LSC != "AdmiralIsWaiting" && pchar.questTemp.LSC.lostDecster == "toAdmiral")
			{
				link.l6 = StringFromKey("Mayor_16");
				link.l6.go = "LostDecster";
			}
			//поиск товаров на корвет
			if (pchar.questTemp.LSC == "toSeekGoods")
			{
				link.l8 = StringFromKey("Mayor_17");
				link.l8.go = "SeekGoods";
			}
			//найм команды
			if (CheckAttribute(pchar, "questTemp.LSC.crew"))
			{
				link.l8 = StringFromKey("Mayor_18");
				link.l8.go = "SeekCrew";
			}
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NRes_1":
			dialog.text = StringFromKey("Mayor_19", pchar);
			link.l1 = StringFromKey("Mayor_20", pchar);
			link.l1.go = "exit";
		break;

		case "FT_1":
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");

			dialog.text = StringFromKey("Mayor_21", pchar, GetFullName(npchar));
			link.l1 = StringFromKey("Mayor_22", pchar);
			link.l1.go = "FT_1_1";
		break;
		case "FT_1_1":
			dialog.text = StringFromKey("Mayor_23");
			link.l1 = StringFromKey("Mayor_24");
			link.l1.go = "FT_1_2";
		break;
		case "FT_1_2":
			dialog.text = StringFromKey("Mayor_25");
			link.l1 = StringFromKey("Mayor_26", npchar.name);
			link.l1.go = "FT_2";
		break;
		case "FT_2":
			dialog.text = StringFromKey("Mayor_27", pchar);
			link.l1 = StringFromKey("Mayor_28");
			link.l1.go = "FT_3";
		break;
		case "FT_3":
			dialog.text = StringFromKey("Mayor_29");
			link.l1 = StringFromKey("Mayor_30");
			link.l1.go = "FT_4";
		break;
		case "FT_4":
			dialog.text = StringFromKey("Mayor_31", pchar);
			link.l1 = StringFromKey("Mayor_32", pchar);
			link.l1.go = "FT_5";
			//если выполнена нац. линейка
			if (CheckAttrValue(pchar, "questTemp.State", "EndOfQuestLine"))
			{
				link.l2 = StringFromKey("Mayor_33", pchar);
				link.l2.go = "FT_5";
			}
			//если завалил ЛГ
			if (CheckAttribute(pchar, "GenQuest.GhostShip.LastBattleEnd"))
			{
				link.l3 = StringFromKey("Mayor_34", pchar);
				link.l3.go = "FT_5";
			}
			//если женился на фурии и уже проникся новой жизнью
			int iBelovedWife = GetCharacterIndex("Isabella");
			if (!LAi_IsDead(characters[iBelovedWife]) && HasStrEx(characters[iBelovedWife].dialog.currentnode, "NewLife,NewLife_hello", "|"))
			{
				//учёл пол, что бы не фонил диалог
				link.l4 = StringFromKey("Mayor_35", pchar);
				link.l4.go = "FT_5";
			}
		break;
		case "FT_5":
			dialog.text = StringFromKey("Mayor_36", pchar);
			link.l1 = StringFromKey("Mayor_37");
			link.l1.go = "FT_6";
		break;
		case "FT_6":
			dialog.text = StringFromKey("Mayor_38");
			link.l1 = StringFromKey("Mayor_39");
			link.l1.go = "FT_7";
		break;
		case "FT_7":
			dialog.text = StringFromKey("Mayor_40");
			link.l1 = StringFromKey("Mayor_41");
			link.l1.go = "FT_7_1";
		break;
		case "FT_7_1":
			dialog.text = StringFromKey("Mayor_42");
			link.l1 = StringFromKey("Mayor_43");
			link.l1.go = "FT_7_2";
		break;
		case "FT_7_2":
			dialog.text = StringFromKey("Mayor_44", pchar);
			link.l1 = StringFromKey("Mayor_45");
			link.l1.go = "FT_8";
		break;
		case "FT_8":
			dialog.text = StringFromKey("Mayor_46");
			link.l1 = StringFromKey("Mayor_47");
			link.l1.go = "FT_9";
		break;
		case "FT_9":
			dialog.text = StringFromKey("Mayor_48", pchar);
			link.l1 = StringFromKey("Mayor_49", pchar);
			if (pchar.money == "0") link.l1.go = "FT_11_1";
			else link.l1.go = "FT_10";
		break;
		case "FT_10":
			if (pchar.questTemp.LSC == "AdmiralFoundHero")
			{
				dialog.text = StringFromKey("Mayor_50", pchar);
				link.l1 = StringFromKey("Mayor_51");
				link.l1.go = "FT_11";
				pchar.money = makeint(sti(pchar.money) / 50);
			}
			else
			{
				dialog.text = StringFromKey("Mayor_52", pchar);
				link.l1 = StringFromKey("Mayor_53");
				link.l1.go = "FT_12";
				pchar.money = 0;
			}
		break;
		case "FT_11":
			dialog.text = StringFromKey("Mayor_54");
			link.l1 = StringFromKey("Mayor_55");
			link.l1.go = "FT_12";
		break;
		case "FT_11_1":
			dialog.text = StringFromKey("Mayor_56");
			link.l1 = StringFromKey("Mayor_57");
			link.l1.go = "FT_12";
		break;
		case "FT_12":
			dialog.text = StringFromKey("Mayor_58", pchar);
			link.l1 = StringFromKey("Mayor_59");
			link.l1.go = "FT_13";
		break;
		case "FT_13":
			dialog.text = StringFromKey("Mayor_60");
			link.l1 = StringFromKey("Mayor_61");
			link.l1.go = "FT_14";
		break;
		case "FT_14":
			dialog.text = StringFromKey("Mayor_62");
			link.l1 = StringFromKey("Mayor_63");
			link.l1.go = "FT_15";
		break;
		case "FT_15":
			dialog.text = StringFromKey("Mayor_64", pchar);
			link.l1 = StringFromKey("Mayor_65");
			link.l1.go = "FT_16";
		break;
		case "FT_16":
			if (npchar.chr_ai.type == LAI_TYPE_ACTOR) LAi_SetLSCoutTypeNoGroup(npchar);
			AddDialogExitQuestFunction("LSC_admiralTakeAll");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//базар с ГГ, если сам не пришёл к адмиралу
		case "FoundHero":
			npchar.quest.meeting = "1";
			NextDiag.TempNode = "First time";
			pchar.questTemp.LSC = "AdmiralNotFoundHero";
			dialog.text = StringFromKey("Mayor_66", pchar);
			link.l1 = StringFromKey("Mayor_67");
			link.l1.go = "FoundHero_1";
		break;
		case "FoundHero_1":
			dialog.text = StringFromKey("Mayor_68", pchar);
			link.l1 = StringFromKey("Mayor_69", pchar);
			link.l1.go = "FoundHero_2";
		break;
		case "FoundHero_2":
			dialog.text = StringFromKey("Mayor_70");
			link.l1 = StringFromKey("Mayor_71", pchar, GetFullName(pchar));
			link.l1.go = "FT_1";
		break;

		//ГГ принёс амулет нарвалов
		case "NarvalRing_1":
			dialog.text = StringFromKey("Mayor_72");
			link.l1 = StringFromKey("Mayor_73", pchar);
			link.l1.go = "NarvalRing_2";
		break;
		case "NarvalRing_2":
			dialog.text = StringFromKey("Mayor_74");
			link.l1 = StringFromKey("Mayor_75");
			link.l1.go = "NarvalRing_3";
		break;
		case "NarvalRing_3":
			dialog.text = StringFromKey("Mayor_76", pchar);
			link.l1 = StringFromKey("Mayor_77");
			link.l1.go = "NarvalRing_4";
			TakeItemFromCharacter(pchar, "RingNarval");
		break;
		case "NarvalRing_3":
			dialog.text = StringFromKey("Mayor_78");
			link.l1 = StringFromKey("Mayor_79", pchar);
			link.l1.go = "NarvalRing_4";
		break;
		case "NarvalRing_4":
			dialog.text = StringFromKey("Mayor_80", pchar);
			link.l1 = StringFromKey("Mayor_81");
			link.l1.go = "NarvalRing_5";
		break;
		case "NarvalRing_5":
			dialog.text = StringFromKey("Mayor_82");
			link.l1 = StringFromKey("Mayor_83");
			link.l1.go = "NarvalRing_6";
			link.l2 = StringFromKey("Mayor_84");
			link.l2.go = "NarvalRing_7";
		break;
		case "NarvalRing_6":
			dialog.text = StringFromKey("Mayor_85");
			link.l1 = StringFromKey("Mayor_86");
			link.l1.go = "NarvalRing_7_1";
		break;
		case "NarvalRing_7_1":
			dialog.text = StringFromKey("Mayor_87");
			link.l1 = StringFromKey("Mayor_88");
			link.l1.go = "NarvalRing_7";
		break;
		case "NarvalRing_7":
			dialog.text = StringFromKey("Mayor_89");
			link.l1 = StringFromKey("Mayor_90");
			link.l1.go = "NarvalRing_8";
		break;

		case "NarvalRing_8":
			dialog.text = StringFromKey("Mayor_91");
			link.l1 = StringFromKey("Mayor_92");
			link.l1.go = "NarvalRing_9";
		break;
		case "NarvalRing_9":
			dialog.text = StringFromKey("Mayor_93", pchar);
			link.l1 = StringFromKey("Mayor_94", pchar);
			link.l1.go = "NarvalRing_10";
		break;
		case "NarvalRing_10":
			dialog.text = StringFromKey("Mayor_95", pchar);
			link.l1 = StringFromKey("Mayor_96");
			link.l1.go = "NarvalRing_11";
		break;
		case "NarvalRing_11":
			dialog.text = StringFromKey("Mayor_97");
			link.l1 = StringFromKey("Mayor_98", pchar);
			link.l1.go = "NarvalRing_12";
		break;
		case "NarvalRing_12":
			dialog.text = StringFromKey("Mayor_99");
			link.l1 = StringFromKey("Mayor_100");
			link.l1.go = "NarvalRing_13";
		break;
		case "NarvalRing_13":
			AddQuestRecord("ISS_MainLine", "13");
			pchar.questTemp.LSC = "toDestoyAllNarval";
			RemoveLandQuestMark_Main(CharacterFromID("LSCBarmen"), "ISS_MainLine");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			//для того что бы были свежие трупы лочим возможность переходов и быстрое перемещение
			DisableFastTravel(true);
			if (pchar.location == "LostShipsCity_town")
			{
				AddDialogExitQuest("LSC_NarvalAssault");
			}
			else
			{
				//блочим двери ведущие не туда
				LocatorReloadEnterDisable("SanAugustineResidence", "reload4", true);
				LocatorReloadEnterDisable("SanAugustineResidence", "reload7", true);
				LocatorReloadEnterDisable("SanAugustineResidence", "reload8", true);
				LocatorReloadEnterDisable("FleuronTavern", "reload3", true);
				LocatorReloadEnterDisable("FleuronTavern", "reload4", true);
				LocatorReloadEnterDisable("FleuronTavern", "reload5", true);
				pchar.quest.LSCNarvalAssault.win_condition.l1 = "ExitFromLocation";
				pchar.quest.LSCNarvalAssault.win_condition.l1.location = pchar.location;
				pchar.quest.LSCNarvalAssault.function = "LSCNarvalAssault";
			}
			pchar.quest.NavalEnterOfficers.win_condition.l1 = "location";
			pchar.quest.NavalEnterOfficers.win_condition.l1.location = "VelascoShipInside1";
			pchar.quest.NavalEnterOfficers.function = "NavalEnterOfficers";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//клан Нарвал уничтожен
		case "DestrNarval_1":
			dialog.text = StringFromKey("Mayor_101");
			iTemp = 0;
			for (i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("Ment_" + i) != -1)
				{
					iTemp++;
				}
			}
			if (iTemp == 0)
			{
				link.l1 = StringFromKey("Mayor_102");
				link.l1.go = "DestrNarval_Bad";
			}
			else
			{
				if (iTemp == sti(pchar.questTemp.LSC.qtyOfficers))
				{
					link.l1 = StringFromKey("Mayor_103");
					link.l1.go = "DestrNarval_Ok";
				}
				else
				{
					link.l1 = StringFromKey("Mayor_104");
					link.l1.go = "DestrNarval_BadOk";
				}
				DeleteAttribute(pchar, "questTemp.LSC.qtyOfficers");
			}
		break;
		case "DestrNarval_Bad":
			dialog.text = StringFromKey("Mayor_105");
			link.l1 = StringFromKey("Mayor_106");
			link.l1.go = "DestrNarval_Bad1";
			link.l1 = StringFromKey("Mayor_107");
			link.l1.go = "DestrNarval_Bad1";
		break;
		case "DestrNarval_Bad1":
			dialog.text = StringFromKey("Mayor_108");
			link.l1 = StringFromKey("Mayor_109");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTavernNarvalDestroyed";
			AddQuestRecord("ISS_MainLine", "17");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			AddLandQuestMark_Main(CharacterFromID("LSCBarmen"), "ISS_MainLine");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		case "DestrNarval_Ok":
			dialog.text = StringFromKey("Mayor_110");
			link.l1 = StringFromKey("Mayor_111");
			link.l1.go = "DestrNarval_Ok1";
			AddQuestRecord("ISS_MainLine", "15");
			AddMoneyToCharacter(pchar, 100000);
		break;
		case "DestrNarval_BadOk":
			dialog.text = StringFromKey("Mayor_112");
			link.l1 = StringFromKey("Mayor_113");
			link.l1.go = "DestrNarval_Ok1";
			AddQuestRecord("ISS_MainLine", "16");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			AddMoneyToCharacter(pchar, 10000);
		break;
		case "DestrNarval_Ok1":
			dialog.text = StringFromKey("Mayor_114");
			link.l1 = StringFromKey("Mayor_115");
			link.l1.go = "DestrNarval_Ok2";
		break;
		case "DestrNarval_Ok2":
			dialog.text = StringFromKey("Mayor_116");
			link.l1 = StringFromKey("Mayor_117");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toTavernNarvalDestroyed";
			AddLandQuestMark_Main(CharacterFromID("LSCBarmen"), "ISS_MainLine");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
		break;
		//подслушивание в погребке
		case "Interception":
			sld = characterFromId("Blaze");
			// bool bOk = false;
			// float fAng;
			// GetCharacterAy(sld, &fAng);
			// if (fAng > -1.35 && fAng < -0.28) bOk = true;
			// if (fAng > 1.8 && fAng < 2.9) bOk = true;
			// if (sti(sld.questTemp.LSC.itemState) && bOk)
			if (sti(sld.questTemp.LSC.itemState))
			{
				dialog.text = StringFromKey("Mayor_118");
				link.l1 = StringFromKey("Mayor_119");
				link.l1.go = "Interception_1";
				sld.questTemp.LSC = "InterceptionOk";
				sld.questTemp.LSC.knowMechanic = true; //флаг ГГ знает о Механике
				CharacterTurnAy(sld, 2.50);
			}
			else
			{
				dialog.text = StringFromKey("Mayor_120");
				link.l1 = StringFromKey("Mayor_121");
				link.l1.go = "exit";
				sld.questTemp.LSC = "InterceptionYouSeen";
				AddDialogExitQuestFunction("LCS_EndScriptInterception");
			}
		break;
		case "Interception_1":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("Mayor_122");
			link.l1 = StringFromKey("Mayor_123", sld);
			link.l1.go = "Interception_2";
		break;
		case "Interception_2":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("Mayor_124", sld);
			link.l1 = StringFromKey("Mayor_125", sld, GetFullName(sld));
			link.l1.go = "Interception_4";
			locCameraFromToPos(72.87, 8.33, -36.35, true, 73.87, 6.85, -33.84);
		break;
		case "Interception_4":
			sld = characterFromId("Blaze");
			dialog.text = StringFromKey("Mayor_126", sld);
			link.l1 = StringFromKey("Mayor_127", sld);
			link.l1.go = "Interception_5";
		break;
		case "Interception_5":
			dialog.text = StringFromKey("Mayor_128");
			link.l1 = StringFromKey("Mayor_129");
			link.l1.go = "Interception_6";
			locCameraToPos(77.3, 8.65, -30.9, true);
		break;
		case "Interception_6":
			dialog.text = StringFromKey("Mayor_130");
			link.l1 = StringFromKey("Mayor_131");
			link.l1.go = "Interception_7";
		break;
		case "Interception_7":
			dialog.text = StringFromKey("Mayor_132");
			link.l1 = StringFromKey("Mayor_133");
			link.l1.go = "Interception_8";
		break;
		case "Interception_8":
			dialog.text = StringFromKey("Mayor_134");
			link.l1 = StringFromKey("Mayor_135");
			link.l1.go = "Interception_9";
		break;
		case "Interception_9":
			dialog.text = StringFromKey("Mayor_136");
			link.l1 = StringFromKey("Mayor_137");
			link.l1.go = "Interception_10";
		break;
		case "Interception_10":
			dialog.text = StringFromKey("Mayor_138");
			link.l1 = StringFromKey("Mayor_139");
			link.l1.go = "Interception_11";
		break;
		case "Interception_11":
			dialog.text = StringFromKey("Mayor_140");
			link.l1 = StringFromKey("Mayor_141");
			link.l1.go = "Interception_12";
		break;
		case "Interception_12":
			dialog.text = StringFromKey("Mayor_142");
			link.l1 = StringFromKey("Mayor_143");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LCS_EndScriptInterception");
		break;

		case "BarmenDead_1":
			dialog.text = StringFromKey("Mayor_144");
			link.l1 = StringFromKey("Mayor_145");
			link.l1.go = "BarmenDead_2";
		break;
		case "BarmenDead_2":
			dialog.text = StringFromKey("Mayor_146");
			link.l1 = StringFromKey("Mayor_147");
			link.l1.go = "BarmenDead_3";
		break;
		case "BarmenDead_3":
			dialog.text = StringFromKey("Mayor_148", pchar);
			link.l1 = StringFromKey("Mayor_149");
			link.l1.go = "BarmenDead_4";
		break;
		case "BarmenDead_4":
			dialog.text = StringFromKey("Mayor_150");
			link.l1 = StringFromKey("Mayor_151", pchar);
			link.l1.go = "BarmenDead_5";
		break;
		case "BarmenDead_5":
			dialog.text = StringFromKey("Mayor_152");
			link.l1 = StringFromKey("Mayor_153");
			link.l1.go = "BarmenDead_6";
		break;
		case "BarmenDead_6":
			dialog.text = StringFromKey("Mayor_154");
			link.l1 = StringFromKey("Mayor_155");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "toSeekOldCitizen";
			AddQuestRecord("ISS_MainLine", "28");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ёл", "ла"));
			AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("ся", "ась"));
			AddQuestUserData("ISS_MainLine", "sSex2", GetSexPhrase("", "ла"));
			pchar.quest.LSC_SaveSesilGalard.win_condition.l1 = "location";
			pchar.quest.LSC_SaveSesilGalard.win_condition.l1.location = "AvaShipInside3";
			pchar.quest.LSC_SaveSesilGalard.function = "LSC_SaveSesilGalard";
			AddLandQuestMark_Main(CharacterFromID("MalcolmFawn"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("HenryFolder"), "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("OreliBertin"), "ISS_MainLine");
		break;
		//замочили касперов
		case "CasperDead_1":
			dialog.text = StringFromKey("Mayor_156");
			link.l1 = StringFromKey("Mayor_157", pchar);
			link.l1.go = "CasperDead_2";
		break;
		case "CasperDead_2":
			dialog.text = StringFromKey("Mayor_158", pchar);
			link.l1 = StringFromKey("Mayor_159", pchar);
			link.l1.go = "CasperDead_3";
		break;
		case "CasperDead_3":
			dialog.text = StringFromKey("Mayor_160");
			link.l1 = StringFromKey("Mayor_161", pchar);
			link.l1.go = "CasperDead_4";
		break;
		case "CasperDead_4":
			dialog.text = StringFromKey("Mayor_162");
			link.l1 = StringFromKey("Mayor_163", pchar);
			link.l1.go = "CasperDead_5";
		break;
		case "CasperDead_5":
			dialog.text = StringFromKey("Mayor_164");
			link.l1 = StringFromKey("Mayor_165");
			link.l1.go = "CasperDead_6";
		break;
		case "CasperDead_6":
			dialog.text = StringFromKey("Mayor_166", pchar);
			link.l1 = StringFromKey("Mayor_167");
			link.l1.go = "CasperDead_7";
		break;
		case "CasperDead_7":
			dialog.text = StringFromKey("Mayor_168", pchar);
			link.l1 = StringFromKey("Mayor_169");
			link.l1.go = "CasperDead_8";
		break;
		case "CasperDead_8":
			dialog.text = StringFromKey("Mayor_170");
			link.l1 = StringFromKey("Mayor_171", pchar);
			link.l1.go = "CasperDead_9";
		break;
		case "CasperDead_9":
			dialog.text = StringFromKey("Mayor_172", pchar);
			link.l1 = StringFromKey("Mayor_173");
			link.l1.go = "CasperDead_11";
			link.l2 = StringFromKey("Mayor_174", pchar);
			link.l2.go = "CasperDead_10";
		break;
		case "CasperDead_10":
			dialog.text = StringFromKey("Mayor_175", pchar);
			link.l1 = StringFromKey("Mayor_176");
			link.l1.go = "CasperDead_11";
		break;
		case "CasperDead_11":
			dialog.text = StringFromKey("Mayor_177", pchar);
			link.l1 = StringFromKey("Mayor_178");
			link.l1.go = "CasperDead_12";
		break;
		case "CasperDead_12":
			dialog.text = StringFromKey("Mayor_179");
			link.l1 = StringFromKey("Mayor_180");
			link.l1.go = "CasperDead_13";
		break;
		case "CasperDead_13":
			dialog.text = StringFromKey("Mayor_181", pchar);
			link.l1 = StringFromKey("Mayor_182", pchar);
			link.l1.go = "CasperDead_14";
		break;
		case "CasperDead_14":
			dialog.text = StringFromKey("Mayor_183");
			link.l1 = StringFromKey("Mayor_184");
			link.l1.go = "exit";
			pchar.questTemp.LSC = "seekMillionAndHalf";
			AddQuestRecord("ISS_MainLine", "37");
			RemoveLandQuestMark_Main(npchar, "ISS_MainLine");
			AddLandQuestMark_Main(CharacterFromID("LSCwaitress"), "ISS_MainLine");
		break;
		//поиск товаров на корвет
		case "SeekGoods":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Mayor_185"),
						StringFromKey("Mayor_186", pchar),
						StringFromKey("Mayor_187", pchar),
						StringFromKey("Mayor_188", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Mayor_189"),
						StringFromKey("Mayor_190", pchar),
						StringFromKey("Mayor_191"),
						StringFromKey("Mayor_192", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekGoods_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekGoods_1":
			dialog.text = StringFromKey("Mayor_193");
			link.l1 = StringFromKey("Mayor_194");
			link.l1.go = "SeekGoods_2";
		break;
		case "SeekGoods_2":
			dialog.text = StringFromKey("Mayor_195", pchar);
			link.l1 = StringFromKey("Mayor_196");
			link.l1.go = "SeekGoods_3";
		break;
		case "SeekGoods_3":
			dialog.text = StringFromKey("Mayor_197");
			link.l1 = StringFromKey("Mayor_198");
			link.l1.go = "SeekGoods_4";
		break;
		case "SeekGoods_4":
			dialog.text = StringFromKey("Mayor_199", pchar);
			link.l1 = StringFromKey("Mayor_200", pchar);
			link.l1.go = "SeekGoods_5";
		break;
		case "SeekGoods_5":
			dialog.text = StringFromKey("Mayor_201");
			link.l1 = StringFromKey("Mayor_202");
			link.l1.go = "SeekGoods_6";
		break;
		case "SeekGoods_6":
			dialog.text = StringFromKey("Mayor_203", pchar);
			link.l1 = StringFromKey("Mayor_204");
			link.l1.go = "SeekGoods_7";
		break;
		case "SeekGoods_7":
			dialog.text = StringFromKey("Mayor_205");
			link.l1 = StringFromKey("Mayor_206", pchar);
			link.l1.go = "SeekGoods_8";
		break;
		case "SeekGoods_8":
			dialog.text = StringFromKey("Mayor_207");
			link.l1 = StringFromKey("Mayor_208");
			link.l1.go = "SeekGoods_9";
		break;
		case "SeekGoods_9":
			dialog.text = StringFromKey("Mayor_209", pchar);
			link.l1 = StringFromKey("Mayor_210", pchar);
			link.l1.go = "SeekGoods_10";
		break;
		case "SeekGoods_10":
			dialog.text = StringFromKey("Mayor_211");
			link.l1 = StringFromKey("Mayor_212");
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "52");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("", "а"));
			pchar.questTemp.LSC.additional.powder = true; //флаг на дачу квеста ментом
			AddLandQuestMark_Main(CharacterFromID("Ment_6"), "ISS_MainLine");
		break;
		//найм команды
		case "SeekCrew":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Mayor_213"),
						StringFromKey("Mayor_214"),
						StringFromKey("Mayor_215"),
						StringFromKey("Mayor_216"), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Mayor_217"),
						StringFromKey("Mayor_218", pchar),
						StringFromKey("Mayor_219"),
						StringFromKey("Mayor_220"), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("SeekCrew_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "SeekCrew_1":
			dialog.text = StringFromKey("Mayor_221");
			link.l1 = StringFromKey("Mayor_222");
			link.l1.go = "SeekCrew_2";
		break;
		case "SeekCrew_2":
			dialog.text = StringFromKey("Mayor_223");
			link.l1 = StringFromKey("Mayor_224");
			link.l1.go = "SeekCrew_3";
		break;
		case "SeekCrew_3":
			dialog.text = StringFromKey("Mayor_225");
			link.l1 = StringFromKey("Mayor_226");
			link.l1.go = "SeekCrew_4";
		break;
		case "SeekCrew_4":
			dialog.text = StringFromKey("Mayor_227");
			link.l1 = StringFromKey("Mayor_228");
			link.l1.go = "SeekCrew_5";
		break;
		case "SeekCrew_5":
			dialog.text = StringFromKey("Mayor_229", pchar);
			link.l1 = StringFromKey("Mayor_230", pchar);
			link.l1.go = "SeekCrew_6";
		break;
		case "SeekCrew_6":
			dialog.text = StringFromKey("Mayor_231", pchar);
			link.l1 = StringFromKey("Mayor_232");
			link.l1.go = "SeekCrew_7";
		break;
		case "SeekCrew_7":
			dialog.text = StringFromKey("Mayor_233", pchar);
			link.l1 = StringFromKey("Mayor_234", pchar);
			link.l1.go = "exit";
			AddQuestRecord("ISS_MainLine", "56");
			AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ся", "ась"));
		break;
		//финальный диалог
		case "fightTalking":
			dialog.text = StringFromKey("Mayor_235", pchar);
			link.l1 = StringFromKey("Mayor_236", pchar);
			link.l1.go = "fightTalking_1";
		break;
		case "fightTalking_1":
			dialog.text = StringFromKey("Mayor_237");
			link.l1 = StringFromKey("Mayor_238");
			link.l1.go = "fightTalking_2_2";
			link.l2 = StringFromKey("Mayor_239");
			link.l2.go = "fightTalking_2_1";
			link.l3 = StringFromKey("Mayor_240");
			link.l3.go = "fightTalking_2_2";
		break;
		case "fightTalking_2_1":
			dialog.text = StringFromKey("Mayor_241", pchar);
			link.l1 = StringFromKey("Mayor_242");
			link.l1.go = "fightTalking_3";
		break;
		case "fightTalking_2_2":
			dialog.text = StringFromKey("Mayor_243", pchar);
			link.l1 = StringFromKey("Mayor_244");
			link.l1.go = "fightTalking_3";
		break;
		case "fightTalking_3":
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetWarriorTypeNoGroup(NPChar);
			AddDialogExitQuestFunction("LSC_figtInResidence");
			DialogExit();
		break;

		//освободить мужа Элис Тейлор
		case "ELTHusb_begin":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("Mayor_245"),
						StringFromKey("Mayor_246"),
						StringFromKey("Mayor_247"),
						StringFromKey("Mayor_248", pchar), "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("Mayor_249"),
						StringFromKey("Mayor_250"),
						StringFromKey("Mayor_251"),
						StringFromKey("Mayor_252", pchar), npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("ELTHusb_begin_1", "", "", "", npchar, Dialog.CurrentNode);
		break;
		case "ELTHusb_begin_1":
			dialog.text = StringFromKey("Mayor_253");
			link.l1 = StringFromKey("Mayor_254");
			link.l1.go = "ELTHusb_begin_2";
		break;
		case "ELTHusb_begin_2":
			dialog.text = StringFromKey("Mayor_255");
			link.l1 = StringFromKey("Mayor_256");
			link.l1.go = "exit";
			RemoveLandQuestMark_Main(npchar, "ISS_ElisHusband");
		break;

		case "ELTHusb_SF":
			dialog.text = StringFromKey("Mayor_257");
			link.l1 = StringFromKey("Mayor_258");
			link.l1.go = "ELTHusb_SF_1";
		break;
		case "ELTHusb_SF_1":
			dialog.text = StringFromKey("Mayor_259");
			link.l1 = StringFromKey("Mayor_260");
			link.l1.go = "ELTHusb_SF_2";
		break;
		case "ELTHusb_SF_2":
			dialog.text = StringFromKey("Mayor_261");
			link.l1 = StringFromKey("Mayor_262");
			link.l1.go = "ELTHusb_SF_3";
		break;
		case "ELTHusb_SF_3":
			dialog.text = StringFromKey("Mayor_263");
			link.l1 = StringFromKey("Mayor_264");
			link.l1.go = "ELTHusb_SF_4";
		break;
		case "ELTHusb_SF_4":
			dialog.text = StringFromKey("Mayor_265");
			link.l1 = StringFromKey("Mayor_266");
			link.l1.go = "ELTHusb_SF_5";
		break;
		case "ELTHusb_SF_5":
			dialog.text = StringFromKey("Mayor_267");
			link.l1 = StringFromKey("Mayor_268");
			link.l1.go = "exit";
			pchar.questTemp.LSC.ElisHusband = "toWaitress";
			AddQuestRecord("ISS_ElisHusband", "7");
			AddLandQuestMark_Main(CharacterFromID("LSCwaitress"), "ISS_ElisHusband");

			RemoveLandQuestMark_Main(npchar, "ISS_ElisHusband");
			RemoveLandQuestMark_Main(CharacterFromID("MaximTailor"), "ISS_ElisHusband");
			RemoveLandQuestMark_Main(CharacterFromID("LSC_PrisonerHead"), "ISS_ElisHusband");
		break;

		case "ELTHusb_good":
			dialog.text = StringFromKey("Mayor_269", pchar);
			link.l1 = StringFromKey("Mayor_270");
			link.l1.go = "ELTHusb_good_1";
		break;
		case "ELTHusb_good_1":
			dialog.text = StringFromKey("Mayor_271");
			link.l1 = StringFromKey("Mayor_272");
			link.l1.go = "ELTHusb_good_2";
		break;
		case "ELTHusb_good_2":
			dialog.text = StringFromKey("Mayor_273");
			link.l1 = StringFromKey("Mayor_274");
			link.l1.go = "ELTHusb_good_3";
		break;
		case "ELTHusb_good_3":
			dialog.text = StringFromKey("Mayor_275");
			link.l1 = StringFromKey("Mayor_276");
			link.l1.go = "exit";
			pchar.questTemp.LSC.ElisHusband = "toElisGood";
			AddQuestRecord("ISS_ElisHusband", "10");
			sld = characterFromId("MaximTailor");
			ChangeCharacterAddress(sld, "none", "");
			RemoveLandQuestMark_Main(npchar, "ISS_ElisHusband");
			AddLandQuestMark_Main(CharacterFromID("ElisTaylor"), "ISS_ElisHusband");
		break;
		//квест со скелетом Декстера
		case "LostDecster":
			dialog.text = StringFromKey("Mayor_277");
			link.l1 = StringFromKey("Mayor_278");
			link.l1.go = "LostDecster_1";
		break;
		case "LostDecster_1":
			dialog.text = StringFromKey("Mayor_279");
			link.l1 = StringFromKey("Mayor_280");
			link.l1.go = "LostDecster_2";
		break;
		case "LostDecster_2":
			dialog.text = StringFromKey("Mayor_281");
			link.l1 = StringFromKey("Mayor_282");
			link.l1.go = "LostDecster_3";
		break;
		case "LostDecster_3":
			dialog.text = StringFromKey("Mayor_283");
			link.l1 = StringFromKey("Mayor_284");
			link.l1.go = "LostDecster_4";
		break;
		case "LostDecster_4":
			dialog.text = StringFromKey("Mayor_285");
			link.l1 = StringFromKey("Mayor_286");
			link.l1.go = "LostDecster_5";
		break;
		case "LostDecster_5":
			dialog.text = StringFromKey("Mayor_287");
			link.l1 = StringFromKey("Mayor_288");
			link.l1.go = "LostDecster_6";
		break;
		case "LostDecster_6":
			dialog.text = StringFromKey("Mayor_289", pchar);
			link.l1 = StringFromKey("Mayor_290");
			link.l1.go = "LostDecster_7";
			pchar.questTemp.LSC.lostDecster = "seekBox";
			AddQuestRecord("LSC_findDekster", "5");
			RemoveLandQuestMark_Main(npchar, "LSC_findDekster");
		break;
		case "LostDecster_7":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			sld = CharacterFromId("Ment_6");
			sld.dialog.currentnode = "talkAboutDextar";
			float locx, locy, locz;
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			chrDisableReloadToLocation = true;
		break;
		//замечение по обнаженному оружию;
		case "LSCNotBlade":
			dialog.text = StringFromKey("Mayor_294", LinkRandPhrase(
						StringFromKey("Mayor_291"),
						StringFromKey("Mayor_292"),
						StringFromKey("Mayor_293", pchar)));
			link.l1 = StringFromKey("Mayor_298", LinkRandPhrase(
						StringFromKey("Mayor_295"),
						StringFromKey("Mayor_296"),
						StringFromKey("Mayor_297")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
		case "CitizenNotBlade":
			dialog.text = StringFromKey("Mayor_302", LinkRandPhrase(
						StringFromKey("Mayor_299"),
						StringFromKey("Mayor_300"),
						StringFromKey("Mayor_301", pchar)));
			link.l1 = StringFromKey("Mayor_306", LinkRandPhrase(
						StringFromKey("Mayor_303"),
						StringFromKey("Mayor_304"),
						StringFromKey("Mayor_305")));
			link.l1.go = "exit";
			NextDiag.TempNode = "First Time";
		break;
	}
}

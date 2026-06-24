void ProcessDialogEvent()
{
	bool bOk;
	int i, iTemp = GetCountFighters();
	string sTitle, sGroup, sTemp, sText;
	float locx, locy, locz;
	ref NPChar, rItem, rChar, rLoc;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		////////////////////////////////////////////////////////////////////////////////////////
		//		ПАТРУЛЬНЫЕ БРОДЯГИ
		////////////////////////////////////////////////////////////////////////////////////////

		/////	ВСТРЕЧА С ПАТРУЛЬНЫМИ
		case "First time patrol":
			PlaySpeech(pchar, GetSexCase(pchar, "Enc_Waiker", "Enc_Alert", "Enc_Waiker"));

			if (GetCharacterEquipSuitID(pchar) == "Suit_1" && iTemp < 1)
			{
				dialog.text = StringFromKey("Secret_Fort_1");
				link.l1 = StringFromKey("Secret_Fort_2");
				link.l1.go = "Patrol_1_talk_1a";
			}
			else
			{
				if (iTemp > 0)
					dialog.text = StringFromKey("Secret_Fort_3");
				else
					dialog.text = StringFromKey("Secret_Fort_4", pchar);
				link.l1 = StringFromKey("Secret_Fort_5");
				link.l1.go = "Patrol_1_talk_1b";
			}
		break;

		///// ВЕТКА №1
		case "Patrol_1_talk_1a":
			dialog.text = StringFromKey("Secret_Fort_6");
			link.l1 = StringFromKey("Secret_Fort_7");
			link.l1.go = "Patrol_1_talk_2a";
		break;

		case "Patrol_1_talk_2a":
			dialog.text = StringFromKey("Secret_Fort_8");
			link.l1 = "...";
			link.l1.go = "Patrol_1_talk_end";
		break;

		///// ВЕТКА №2
		case "Patrol_1_talk_1b":
			if (iTemp > 0)
				dialog.text = StringFromKey("Secret_Fort_9");
			else
				dialog.text = StringFromKey("Secret_Fort_10", pchar);
			link.l1 = StringFromKey("Secret_Fort_11");
			link.l1.go = "Patrol_1_talk_2b";
		break;

		case "Patrol_1_talk_2b":
			dialog.text = StringFromKey("Secret_Fort_12");
			link.l1 = StringFromKey("Secret_Fort_13");
			link.l1.go = "Patrol_1_talk_3b";
		break;

		case "Patrol_1_talk_3b":
			dialog.text = StringFromKey("Secret_Fort_14");
			link.l1 = StringFromKey("Secret_Fort_15");
			link.l1.go = "Patrol_1_talk_4b";
		break;

		case "Patrol_1_talk_4b":
			rChar = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			dialog.text = StringFromKey("Secret_Fort_16");
			link.l1 = StringFromKey("Secret_Fort_17", GetFullName(rChar), XI_ConvertString("Colony" + rChar.city + "Gen"));
			link.l1.go = "Patrol_1_talk_5b";
		break;

		case "Patrol_1_talk_5b":
			dialog.text = StringFromKey("Secret_Fort_18");
			link.l1 = StringFromKey("Secret_Fort_19", GetFullName(pchar));
			link.l1.go = "Patrol_1_talk_6b";
		break;

		case "Patrol_1_talk_6b":
			NextDiag.TempNode = "Second time patrol";
			dialog.text = StringFromKey("Secret_Fort_20", GetFullName(pchar));
			link.l1 = "...";
			link.l1.go = "Patrol_1_talk_end";
		break;

		case "Patrol_1_talk_end":
			DialogExit();
			for (i = 0; i <= 1; i++)
			{
				rChar = CharacterFromId("Secret_Fort_Exit_Man" + i);
				DeleteAttribute(rChar, "protector");
				rChar.dialog.currentnode = "Second time patrol";
				LAi_SetWarriorType(rChar);
				rChar.greeting = "Gr_SecretFort_Patrol"; // > подгоняем ГГ
				rChar.lifeDay = 1; // > сутки потусят и по делам
				SaveCurrentNpcQuestDateParam(rChar, "LifeTimeCreate");
			}
			LocatorReloadEnterDisable("Secret_Fort_Exit", "reload3", false);
			pchar.questTemp.LSC = "SecretFortFound";
		break;

		case "Second time patrol":
			NextDiag.TempNode = "Second time patrol";
			dialog.text = StringFromKey("Secret_Fort_21");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		////////////////////////////////////////////////////////////////////////////////////////
		//		ГЛАВНЫЙ БРОДЯГА СТАРОГО ФОРТА
		////////////////////////////////////////////////////////////////////////////////////////

		/////	ПЕРВЫЙ КВЕСТОВЫЙ ДИАЛОГ С ГЛАВНЫМ
		case "First time commander":
			dialog.text = StringFromKey("Secret_Fort_22", pchar, GetFullName(NPChar));
			link.l1 = StringFromKey("Secret_Fort_23", pchar, GetFullName(pchar));
			link.l1.go = "Commander_1_talk_1";
		break;

		case "Commander_1_talk_1":
			rChar = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			dialog.text = StringFromKey("Secret_Fort_24");
			link.l1 = StringFromKey("Secret_Fort_25", GetFullName(rChar), XI_ConvertString("Colony" + rChar.city + "Gen"));
			link.l1.go = "Commander_1_talk_2";
		break;

		case "Commander_1_talk_2":
			dialog.text = StringFromKey("Secret_Fort_26");
			link.l1 = StringFromKey("Secret_Fort_27");
			link.l1.go = "Commander_1_talk_3";
		break;

		case "Commander_1_talk_3":
			dialog.text = StringFromKey("Secret_Fort_28", pchar);
			link.l1 = StringFromKey("Secret_Fort_29");
			link.l1.go = "Commander_1_talk_4";
		break;

		case "Commander_1_talk_4":
			dialog.text = StringFromKey("Secret_Fort_30");
			link.l1 = StringFromKey("Secret_Fort_31");
			link.l1.go = "Commander_1_talk_5";
		break;

		case "Commander_1_talk_5":
			NextDiag.TempNode = "Second time commander";
			dialog.text = StringFromKey("Secret_Fort_32");
			link.l1 = "...";
			link.l1.go = "Commander_1_talk_end";
		break;

		case "Commander_1_talk_end":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			RemovePassenger(pchar, CharacterFromID("TitherDenLSC"));
			AddDialogExitQuest("SecretFort_TizerJournal");

			for (i = 0; i <= 1; i++)
			{
				rChar = CharacterFromId("Secret_Fort_Exit_Man" + i);
				rChar.greeting = "Gr_poorman";
			}
		break;

		/////	ВТОРОЙ КВЕСТОВЫЙ ДИАЛОГ С ГЛАВНЫМ
		case "Commander_2_talk_1":
			dialog.text = StringFromKey("Secret_Fort_33");
			link.l1 = StringFromKey("Secret_Fort_34");
			link.l1.go = "Commander_2_talk_2";
		break;

		case "Commander_2_talk_2":
			dialog.text = StringFromKey("Secret_Fort_35");
			if (CheckCharacterPerk(pchar, "Nobleman"))
			{
				link.l1 = StringFromKey("Secret_Fort_36");
				link.l1.go = "Commander_2_talk_3_1";
			}
			else
			{
				link.l1 = StringFromKey("Secret_Fort_37");
				link.l1.go = "Commander_2_talk_3_2";
			}
		break;

		case "Commander_2_talk_3_1":
			dialog.text = StringFromKey("Secret_Fort_38", GetFullName(pchar));
			link.l1 = StringFromKey("Secret_Fort_39");
			link.l1.go = "Commander_2_talk_4";
		break;

		case "Commander_2_talk_3_2":
			dialog.text = StringFromKey("Secret_Fort_40", GetFullName(pchar));
			link.l1 = StringFromKey("Secret_Fort_41");
			link.l1.go = "Commander_2_talk_4";
		break;

		case "Commander_2_talk_4":
			dialog.text = StringFromKey("Secret_Fort_42");
			link.l1 = StringFromKey("Secret_Fort_43");
			link.l1.go = "Commander_2_talk_5";
		break;

		case "Commander_2_talk_5":
			dialog.text = StringFromKey("Secret_Fort_44", pchar);
			link.l1 = StringFromKey("Secret_Fort_45");
			link.l1.go = "Commander_2_talk_6";
			link.l2 = StringFromKey("Secret_Fort_46");
			link.l2.go = "Commander_2_talk_6";
			link.l3 = StringFromKey("Secret_Fort_47");
			link.l3.go = "Commander_2_talk_6";
			link.l4 = StringFromKey("Secret_Fort_48");
			link.l4.go = "Commander_2_talk_6";
		break;

		case "Commander_2_talk_6":
			dialog.text = StringFromKey("Secret_Fort_49");
			link.l1 = StringFromKey("Secret_Fort_50");
			link.l1.go = "Commander_2_talk_7";
		break;

		case "Commander_2_talk_7":
			dialog.text = StringFromKey("Secret_Fort_51");
			link.l1 = StringFromKey("Secret_Fort_52");
			link.l1.go = "Commander_2_talk_8";
		break;

		case "Commander_2_talk_8":
			dialog.text = StringFromKey("Secret_Fort_53", GetFullName(pchar));
			link.l1 = StringFromKey("Secret_Fort_54");
			link.l1.go = "Commander_2_talk_9";
		break;

		case "Commander_2_talk_9":
			dialog.text = StringFromKey("Secret_Fort_55");
			link.l1 = StringFromKey("Secret_Fort_56");
			link.l1.go = "Commander_2_talk_10";
		break;

		case "Commander_2_talk_10":
			NextDiag.TempNode = "Second time commander";
			dialog.text = StringFromKey("Secret_Fort_57", GetFullName(pchar));
			link.l1 = StringFromKey("Secret_Fort_58");
			link.l1.go = "Commander_2_talk_end";
		break;

		case "Commander_2_talk_end":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			rItem = ItemsFromID("TizerJournal");
			rItem.groupID = READING_ITEM_TYPE;
			AddQuestRecord("ISS_PoorsMurder", "37");
			RemoveItems(pchar, "strangeNoteLSC", 1);
		break;

		/////	ТРЕТИЙ КВЕСТОВЫЙ ДИАЛОГ С ГЛАВНЫМ
		case "Commander_3_talk_1":
			dialog.text = StringFromKey("Secret_Fort_59", GetFullName(pchar));
			link.l1 = StringFromKey("Secret_Fort_60");
			link.l1.go = "Commander_3_talk_2";
		break;

		case "Commander_3_talk_2":
			dialog.text = StringFromKey("Secret_Fort_61");
			link.l1 = StringFromKey("Secret_Fort_62", pchar);
			link.l1.go = "Commander_3_talk_3";
		break;

		case "Commander_3_talk_3":
			dialog.text = StringFromKey("Secret_Fort_63");
			link.l1 = StringFromKey("Secret_Fort_64");
			link.l1.go = "Commander_3_talk_4";
		break;

		case "Commander_3_talk_4":
			dialog.text = StringFromKey("Secret_Fort_65");
			link.l1 = StringFromKey("Secret_Fort_66");
			link.l1.go = "Commander_3_talk_5";
		break;

		case "Commander_3_talk_5":
			dialog.text = StringFromKey("Secret_Fort_67");
			link.l1 = StringFromKey("Secret_Fort_68");
			link.l1.go = "Commander_3_talk_6";
		break;

		case "Commander_3_talk_6":
			dialog.text = StringFromKey("Secret_Fort_69");
			link.l1 = StringFromKey("Secret_Fort_70");
			link.l1.go = "Commander_3_talk_7";
			AddQuestRecord("ISS_PoorsMurder", "38");
		break;

		case "Commander_3_talk_7":
			NextDiag.TempNode = "Second time commander";
			dialog.text = StringFromKey("Secret_Fort_71");
			link.l1 = StringFromKey("Secret_Fort_72");
			link.l1.go = "Commander_3_talk_end";
		break;

		case "Commander_3_talk_end":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("SecretFort_TizerHouse_1");
		break;

		/////	ЧЕТВЁРТЫЙ КВЕСТОВЫЙ ДИАЛОГ С ГЛАВНЫМ
		case "Commander_4_talk_1":
			dialog.text = StringFromKey("Secret_Fort_73", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Secret_Fort_74", pchar);
			link.l1.go = "Commander_4_talk_2";
		break;

		case "Commander_4_talk_2":
			dialog.text = StringFromKey("Secret_Fort_75", pchar, GetFullName(pchar));
			link.l1 = StringFromKey("Secret_Fort_76");
			link.l1.go = "Commander_4_talk_3";
		break;

		case "Commander_4_talk_3":
			dialog.text = StringFromKey("Secret_Fort_77");
			link.l1 = StringFromKey("Secret_Fort_78");
			link.l1.go = "Commander_4_talk_4";
		break;

		case "Commander_4_talk_4":
			dialog.text = StringFromKey("Secret_Fort_79");
			link.l1 = StringFromKey("Secret_Fort_80");
			link.l1.go = "Commander_4_talk_5";
		break;

		case "Commander_4_talk_5":
			NextDiag.TempNode = "Final time commander";
			dialog.text = StringFromKey("Secret_Fort_81");
			link.l1 = StringFromKey("Secret_Fort_82");
			link.l1.go = "Commander_4_talk_end";
		break;

		case "Commander_4_talk_end":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddQuestRecord("PreparationForISS", "5");
		break;

		/////	ЗАТЫЧКА ДО ЗАВЕРШЕНИЯ ПОДГОТОВКИ TODO > разнообразить потом
		case "Second time commander":
			NextDiag.TempNode = "Second time commander";
			dialog.text = StringFromKey("Secret_Fort_83");
			link.l1 = StringFromKey("Secret_Fort_84");
			link.l1.go = "exit";
		break;

		/////	ПОДГОТОВКА ЗАВЕРШЕНА, ТЕПЕРЬ ЭТО ПОСТОЯННЫЕ ДИАЛОГИ С ГЛАВНЫМ
		case "Final time commander":
			NextDiag.TempNode = "Final time commander";
			dialog.text = StringFromKey("Secret_Fort_85", pchar.name);
			if (CheckShip(pchar))
			{
				link.l1 = StringFromKey("Secret_Fort_86");
				link.l1.go = "Commander_Store_Goods";
			}
			link.l2 = StringFromKey("Secret_Fort_87");
			link.l2.go = "Commander_Store_Items";
			link.l3 = StringFromKey("Secret_Fort_88");
			link.l3.go = "Commander_Store_Ships";

			if (pchar.questTemp.LSC != "over" && GetPassengersQuantity(pchar) > 0 && !CheckAttribute(&TEV, "StoreLSC"))
			{
				link.l4 = StringFromKey("Secret_Fort_89");
				link.l4.go = "Commander_Store_Officers";
			}

			if (pchar.questTemp.LSC == "over" && CheckAttribute(&TEV, "StoreLSC"))
			{
				link.l5 = StringFromKey("Secret_Fort_90");
				link.l5.go = "Commander_Store_Officers_TakeBack";
			}

			if (!CheckAttribute(NPChar, "TalkDepartureLSC"))
			{
				if (!CheckShip(pchar) && !CheckAttribute(NPChar, "TakeBarkasLSC"))
				{
					link.l6 = StringFromKey("Secret_Fort_91");
					link.l6.go = "Commander_5_talk_barkas";
				}
				if (CheckConditionDepartureLSC())
				{
					link.l7 = StringFromKey("Secret_Fort_92");
					link.l7.go = "Commander_5_talk_1";
				}
			}

			link.l99 = StringFromKey("Secret_Fort_93", pchar);
			link.l99.go = "exit";
		break;

		/////	ХРАНЕНИЕ ТОВАРОВ
		case "Commander_Store_Goods":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			npchar.MoneyForStorage = 0;
			npchar.Storage.Activate = true;
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			LaunchStorage(SHIP_STORE);
		break;

		/////	ХРАНЕНИЕ ВЕЩЕЙ
		case "Commander_Store_Items":
			if (!CheckAttribute(npchar, "StorageOpen"))
			{
				npchar.StorageOpen = "Opened";
				npchar.StoragePrice = 0;
			}
			SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchItemsStorage(&stores[SHIP_STORE]);
		break;

		/////	ХРАНЕНИЕ КОРАБЛЕЙ
		case "Commander_Store_Ships":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchPortman(NPChar);
		break;

		/////	ХРАНЕНИЕ ОФИЦЕРОВ
		case "Commander_Store_Officers":
			StoreOfficersLSC();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Commander_Store_Officers_TakeBack":
			TakeStoredOfficersLSC(NPChar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		/////	РАЗГОВОР ПРО БАРКАС
		case "Commander_5_talk_barkas":
			NextDiag.TempNode = "Final time commander";
			dialog.text = StringFromKey("Secret_Fort_94");
			link.l1 = StringFromKey("Secret_Fort_95");
			link.l1.go = "Commander_5_talk_barkas_take";
			link.l2 = StringFromKey("Secret_Fort_96");
			link.l2.go = "exit";
		break;

		case "Commander_5_talk_barkas_take":
			TakeBarkasLSC();
			NPChar.TakeBarkasLSC = "1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			dialog.text = StringFromKey("Secret_Fort_97");
			link.l1 = StringFromKey("Secret_Fort_98");
			link.l1.go = "exit";
		break;

		/////	ОТПРАВЛЯЕМСЯ В ГПК
		case "Commander_5_talk_1":
			NextDiag.TempNode = "Final time commander";
			dialog.text = StringFromKey("Secret_Fort_99", pchar, pchar.name);
			link.l1 = StringFromKey("Secret_Fort_100");
			link.l1.go = "Commander_5_talk_end";
		break;

		case "Commander_5_talk_end":
			NPChar.TalkDepartureLSC = "1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddQuestRecord("PreparationForISS", "6");
			pchar.questTemp.LSC = "GoToLSC";
			AddDialogExitQuest("ReloadEnableLSC");
		break;

		/////	ВЕРНУЛИСЬ ИЗ ГПК
		case "Commander_6_talk_1":
			dialog.text = StringFromKey("Secret_Fort_101", pchar);
			link.l1 = StringFromKey("Secret_Fort_102");
			link.l1.go = "Commander_6_talk_2";
		break;

		case "Commander_6_talk_2":
			dialog.text = StringFromKey("Secret_Fort_103");
			link.l1 = StringFromKey("Secret_Fort_104");
			link.l1.go = "Commander_6_talk_3";
		break;

		case "Commander_6_talk_3":
			dialog.text = StringFromKey("Secret_Fort_105");
			link.l1 = StringFromKey("Secret_Fort_106");
			link.l1.go = "Commander_6_talk_end";
		break;

		case "Commander_6_talk_end":
			NextDiag.TempNode = "Final time commander";
			dialog.text = StringFromKey("Secret_Fort_107");
			link.l1 = StringFromKey("Secret_Fort_108");
			link.l1.go = "exit";
		break;

		////////////////////////////////////////////////////////////////////////////////////////
		//		БРОДЯГА В АРСЕНАЛЕ ФОРТА
		////////////////////////////////////////////////////////////////////////////////////////
		case "First time guard":
			NextDiag.TempNode = "Second time guard";
			dialog.text = StringFromKey("Secret_Fort_109");
			link.l1 = StringFromKey("Secret_Fort_110");
			link.l1.go = "exit";
		break;

		case "Second time guard":
			NextDiag.TempNode = "Second time guard";
			dialog.text = StringFromKey("Secret_Fort_111");
			link.l1 = StringFromKey("Secret_Fort_112");
			link.l1.go = "exit";
		break;

		////////////////////////////////////////////////////////////////////////////////////////
		//		БРОДЯГИ ВО ДВОРЕ ФОРТА
		////////////////////////////////////////////////////////////////////////////////////////
		case "First time courtyard":
			NextDiag.TempNode = "Second time courtyard";
			dialog.text = StringFromKey("Secret_Fort_113");
			link.l1 = StringFromKey("Secret_Fort_114");
			link.l1.go = "exit";
		break;

		case "Second time courtyard":
			NextDiag.TempNode = "Second time courtyard";
			dialog.text = StringFromKey("Secret_Fort_115");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		////////////////////////////////////////////////////////////////////////////////////////
		//		БРОДЯГА-ТАВЕРНЩИК В ТАВЕРНЕ
		////////////////////////////////////////////////////////////////////////////////////////
		case "First time barman":
			NextDiag.TempNode = "Second time barman";
			dialog.text = StringFromKey("Secret_Fort_116");
			link.l1 = StringFromKey("Secret_Fort_117");
			link.l1.go = "exit";
		break;

		case "Second time barman":
			NextDiag.TempNode = "Second time barman";
			dialog.text = StringFromKey("Secret_Fort_118");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		////////////////////////////////////////////////////////////////////////////////////////
		//		БРОДЯГИ-КАРТЁЖНИКИ В ТАВЕРНЕ
		////////////////////////////////////////////////////////////////////////////////////////
		case "First time gambler":
			NextDiag.TempNode = "Second time gambler";
			dialog.text = StringFromKey("Secret_Fort_119");
			link.l1 = StringFromKey("Secret_Fort_120");
			link.l1.go = "exit";
		break;

		case "Second time gambler":
			NextDiag.TempNode = "Second time gambler";
			dialog.text = StringFromKey("Secret_Fort_121");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		////////////////////////////////////////////////////////////////////////////////////////
		//		БРОДЯГА В ЧАСОВНЕ
		////////////////////////////////////////////////////////////////////////////////////////
		case "First time chapel":
			NextDiag.TempNode = "Second time chapel";
			dialog.text = StringFromKey("Secret_Fort_122");
			link.l1 = StringFromKey("Secret_Fort_123");
			link.l1.go = "exit";
		break;

		case "Second time chapel":
			NextDiag.TempNode = "Second time chapel";
			dialog.text = StringFromKey("Secret_Fort_124");
			link.l1 = StringFromKey("Secret_Fort_125");
			link.l1.go = "exit";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

bool CheckConditionDepartureLSC()
{
	if (!CheckShip(pchar)) return false;
	if (GetPassengersQuantity(pchar) > 0) return false;
	if (GetCompanionQuantity(pchar) > 1) return false;
	return true;
}

void StoreOfficersLSC()
{
	int q = GetPassengersQuantity(pchar);
	if (q < 1) return;

	ref sld;
	string sTemp, sText = "init";
	int i, j, idx;
	bool bFighter;

	string sLocatorGoto, sLocatorSit, arLocatorsGoto[2], arLocatorsSit[2];

	for (i = 1; i <= 32; i++)
	{
		ArrayAddValue(&arLocatorsGoto, "goto" + i);
	}

	for (i = 1; i <= 6; i++)
	{
		ArrayAddValue(&arLocatorsSit, "sit" + i);
	}

	for (i = 0; q > 0; i++)
	{
		bFighter = false;
		idx = GetPassenger(pchar, 0);
		if (idx == -1) break;
		sld = GetCharacter(idx);
		sTemp = "sld" + i;
		if (StrHasStr(sld.id, sText, 1)) continue;
		sText = sText + "," + sld.id;
		TEV.StoreLSC.(sTemp) = idx;

		//офицеров раскидываем в форте
		if (isOfficerInShip(sld, true))
		{
			sLocatorGoto = ArrayGetRandomValue(&arLocatorsGoto);
			ArrayRemoveValue(&arLocatorsGoto, sLocatorGoto);

			sld.Dialog.CurrentNode = "NiceDayLSC";
			TEV.StoreLSC.(sTemp).isOfficer = 1;
			LAi_SetImmortal(sld, true);

			//абордажников снимаем с должности, иначе они нормально не распределяются по форту
			for (j = 0; j < 4; j++)
			{
				if (GetOfficersIndex(pchar, j) == idx)
				{
					bFighter = true;
					RemoveOfficersIndex(pchar, GetOfficersIndex(pchar, j));
				}
			}

			if (CheckAttribute(sld, "Capellan")) // > капеллан в часовню
			{
				LAi_CharacterDisableDialog(sld);//капеллану пока не до разговоров
				LAi_SetBarmanType(sld);
				ChangeCharacterAddressGroup(sld, "Secret_Fort_Chapel", "barmen", "stay");
			}
			else if (bFighter || rand(1)) // > бойцы всегда гуляют на свежем воздухе, а прочие гуляют лишь с шансом 50% TODO > чек с максимумом офицеров
			{
				LAi_SetWarriorTypeNoGroup(sld);
				ChangeCharacterAddressGroup(sld, "Secret_Fort", "goto", sLocatorGoto);
			}
			else
			{
				// большинство офицеров тусят в таверне
				sLocatorSit = ArrayGetRandomValue(&arLocatorsSit);
				ArrayRemoveValue(&arLocatorsSit, sLocatorSit);
				LAi_SetSitTypeNoGroup(sld);
				FreeSitLocator("Secret_Fort_Tavern", sLocatorSit);
				ChangeCharacterAddressGroup(sld, "Secret_Fort_Tavern", "sit", sLocatorSit);
			}
		}
		else
		{
			//остальные просто куда-то отошли по делам
			if (CheckAttribute(sld, "HiredDate"))
				TEV.StoreLSC.(sTemp).isOfficer = 1;
			else
				TEV.StoreLSC.(sTemp).isOfficer = 0;
			ChangeCharacterAddress(sld, "none", "");
		}
		RemovePassenger(pchar, sld);
	}
	//<------ снять офицеров и разместить в форте
}

void TakeStoredOfficersLSC(ref rChar)
{
	ref sld;
	aref aStore;
	aref tempObject;
	int i, idx;

	DeleteAttribute(rChar, "storedLSC");

	makearef(aStore, TEV.StoreLSC);
	for (i = 0; i < GetAttributesNum(aStore); i++)
	{
		tempObject = GetAttributeN(aStore, i);
		if (idx == -1) continue;

		idx = sti(GetAttributeValue(tempObject));
		sld = GetCharacter(idx);
		// Восстановление пассажиров
		if (HasStr(GetAttributeName(tempObject), "sld"))
		{
			if (sti(tempObject.isOfficer))
			{
				LAi_SetImmortal(sld, false);
				sld.location = "none";
				sld.Dialog.CurrentNode = "hired";
				pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(sld.id);
				LandEnc_OfficerHired();
			}
			else AddPassenger(pchar, sld, false);
		}
	}

	// удаление временного хранилища
	DeleteAttribute(&TEV, "StoreLSC");
}

void TakeBarkasLSC()
{
	//выдать баркас
	pchar.Ship.Type = GenerateShipExt(SHIP_BARKAS, true, pchar);
	pchar.Ship.Name = GenerateRandomNameToShip(PIRATE);
	SetBaseShipData(pchar);
	SetCrewQuantity(pchar, 0);
	RecalculateCargoLoad(pchar);
	pchar.location.from_sea = "Shore_ship2"; // корабль в бухте
}

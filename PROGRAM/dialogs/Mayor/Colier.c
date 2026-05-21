// Эдвард Кольер, глава буканьеров и авторитетный пират. Заместитель Моргана
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// evganat - пасха
	string sAttr = Dialog.CurrentNode;
	int i, idx;
	ref sld;
	if (HasSubStr(sAttr, "BuyMorganFrigateChr"))
	{
		i = findsubstr(sAttr, "-", 0);
		int iChar = GetPassenger(PChar, sti(strcut(sAttr, i + 1, strlen(sAttr) - 1)));
		sld = GetCharacter(iChar);
		CheckForReleaseOfficer(iChar);
		sld.Ship.Type = GenerateShipExt(SHIP_FRIGATE_M, 0, sld);
		SetBaseShipData(sld);
		RemovePassenger(pchar, sld);
		SetCompanionIndex(pchar, -1, iChar);
		sld.Ship.Name = FindPersonalName("Henry_Morgan_ship");
		Dialog.CurrentNode = "BuyMorganFrigate_success";
	}

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
				break;
			}
		}
	}
	// <<<<<<<<<<<<<<<<<<<<<<======= блок angry ===================================
	// ============================================================================
	switch (Dialog.CurrentNode)
	{
		case "First time":
			if (StrHasStr(pchar.questTemp.LSC, "BequestToProvidenceLSC,CoilerNeedMoneyLSC,PreparationsForDepartureLSC", 1))
			{
				dialog.text = StringFromKey("Colier_1", pchar);
				link.l1 = StringFromKey("Colier_2");
				link.l1.go = "exit";
			}
			else
			{
				NextDiag.TempNode = "First time";
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("Colier_3", pchar),
							StringFromKey("Colier_4"),
							StringFromKey("Colier_5"),
							StringFromKey("Colier_6", pchar), "repeat", 2, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat(
							StringFromKey("Colier_7"),
							StringFromKey("Colier_8", npchar.name),
							StringFromKey("Colier_9", npchar.name),
							StringFromKey("Colier_10"), npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			// Подводка к ГПК
			// пришли отдать завещание ГПК
			if (pchar.questTemp.LSC == "BequestToProvidenceLSC")
			{
				link.l1 = StringFromKey("Colier_11");
				link.l1.go = "BequestToProvidenceLSC_1";
			}
			//денюжка для Койлера ГПК
			if (pchar.questTemp.LSC == "CoilerNeedMoneyLSC" && sti(pchar.money) >= 100000)
			{
				dialog.text = StringFromKey("Colier_12");
				link.l1 = StringFromKey("Colier_13");
				link.l1.go = "BequestToProvidenceLSC_6";
			}
			//подготовка к отплытию в ГПК завершена
			if (pchar.questTemp.LSC == "PreparationsForDepartureLSC" && GetCompanionQuantity(pchar) <= 1 && sti(pchar.Ship.Type) == SHIP_NOTUSED)
			{
				link.l1 = StringFromKey("Colier_14");
				link.l1.go = "PreparationsForDepartureLSC_1";
			}
			// пришли забрать своё после ГПК
			if (pchar.questTemp.LSC == "over" && CheckAttribute(npchar, "storedLSC"))
			{
				link.l1 = StringFromKey("Colier_15");
				link.l1.go = "TakeAllFromProvidenceLSC_1";
			}
			// Поиск Шарпа
			if (CheckAttribute(pchar, "questTemp.Sharp") && StrStartsWith(pchar.questTemp.Sharp, "takeRumour"))
			{
				link.l2 = StringFromKey("Colier_16");
				link.l2.go = "SharpPearl_1";
			}
		break;

		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		//********************* капитан Шарп *********************
		case "SharpPearl_1":
			dialog.text = StringFromKey("Colier_17");
			link.l1 = StringFromKey("Colier_18");
			link.l1.go = "SharpPearl_2";
			pchar.questTemp.Sharp = "seekSharp";
			RemoveLandQuestmarkToFantoms_Main("Pearl_HeadMan", "SharpPearl");
			SeaPearl_PiratesBaron_DelQuestMarks();
			SeaPearl_Hostess_AddQuestMarks();
		break;
		case "SharpPearl_2":
			AddQuestRecord("SharpPearl", "16");
			AddQuestUserData("SharpPearl", "sName", GetFullName(NPChar));

			dialog.text = StringFromKey("Colier_19");
			link.l1 = StringFromKey("Colier_20");
			link.l1.go = "exit";
		break;

		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
			dialog.text = StringFromKey("Colier_23", RandPhraseSimple(
						StringFromKey("Colier_21", pchar),
						StringFromKey("Colier_22")));
			link.l1 = StringFromKey("Colier_24");
			link.l1.go = "AngryExitAgainWithOut";
			if (CheckAttribute(npchar, "angry.terms")) //примиряемся с Кольером через 30 дней.
			{
				if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
				{
					dialog.text = StringFromKey("Colier_25");
					link.l1 = StringFromKey("Colier_26", pchar);
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
			DoReloadCharacterToLocation("Providencia_town", "reload", "reload3");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		// evganat - пасха
		case "BuyMorganFrigate":
			dialog.text = StringFromKey("Colier_27", pchar.name);
			link.l1 = StringFromKey("Colier_28");
			link.l1.go = "BuyMorganFrigate_2";
		break;

		case "BuyMorganFrigate_2":
			dialog.text = StringFromKey("Colier_29", pchar);
			link.l1 = StringFromKey("Colier_30");
			link.l1.go = "BuyMorganFrigate_3";
		break;

		case "BuyMorganFrigate_3":
			dialog.text = StringFromKey("Colier_31", pchar);
			link.l1 = StringFromKey("Colier_32", pchar);
			link.l1.go = "BuyMorganFrigate_4";
		break;

		case "BuyMorganFrigate_4":
			dialog.text = StringFromKey("Colier_33");
			link.l1 = StringFromKey("Colier_34");
			link.l1.go = "BuyMorganFrigate_5";
		break;

		case "BuyMorganFrigate_5":
			npchar.buyfrigate = "waitformoney";
			dialog.text = StringFromKey("Colier_35");
			if (sti(pchar.money) >= 400000)
			{
				link.l1 = StringFromKey("Colier_36");
				link.l1.go = "BuyMorganFrigate_ok";
			}
			link.l2 = StringFromKey("Colier_37");
			link.l2.go = "BuyMorganFrigate_exit";
		break;

		case "BuyMorganFrigate_exit":
			DialogExit();
			NextDiag.TempNode = "BuyMorganFrigate_return";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

		case "BuyMorganFrigate_return":
			if (npchar.buyfrigate == "waitformoney")
			{
				dialog.text = StringFromKey("Colier_38");
				if (sti(pchar.money) >= 400000)
				{
					link.l1 = StringFromKey("Colier_39");
					link.l1.go = "BuyMorganFrigate_ok";
				}
			}
			if (npchar.buyfrigate == "choosechr")
			{
				dialog.text = StringFromKey("Colier_40");
				link.l1 = StringFromKey("Colier_41");
				link.l1.go = "BuyMorganFrigate_ok";
			}
			link.l2 = StringFromKey("Colier_42");
			link.l2.go = "BuyMorganFrigate_exit";
		break;

		case "BuyMorganFrigate_ok":
			if (npchar.buyfrigate == "waitformoney")
			{
				AddMoneyToCharacter(pchar, -400000);
				sAttr = StringFromKey("Colier_43");
			}
			npchar.buyfrigate = "choosechr";
			if (GetCompanionQuantity(pchar) >= COMPANION_MAX)
			{
				dialog.text = StringFromKey("Colier_44", sAttr);
				link.l1 = StringFromKey("Colier_45");
				link.l1.go = "BuyMorganFrigate_exit";
				break;
			}
			dialog.text = StringFromKey("Colier_46", sAttr);
			int charIdx;
			int q = 0;
			int n = GetPassengersQuantity(pchar);
			bool ok;
			string sProf;
			for (i = 0; i < n; i++)
			{
				charIdx = GetPassenger(pchar, i);
				sld = GetCharacter(charIdx);
				if (charIdx != -1)
				{
					ok = CheckAttribute(&characters[charIdx], "prisoned") && sti(characters[charIdx].prisoned) == true;
					if (!ok && !CheckAttribute(&characters[charIdx], "CompanionDisable") && GetRemovable(&characters[charIdx]))
					{
						sAttr = "l" + i;
						sProf = " ";
						if (IsOfficer(sld)) sProf += StringFromKey("Colier_47");
						if (sti(pchar.Fellows.Passengers.navigator) == sti(sld.index)) sProf += StringFromKey("Colier_48");
						if (sti(pchar.Fellows.Passengers.boatswain) == sti(sld.index)) sProf += StringFromKey("Colier_49");
						if (sti(pchar.Fellows.Passengers.cannoner) == sti(sld.index)) sProf += StringFromKey("Colier_50");
						if (sti(pchar.Fellows.Passengers.doctor) == sti(sld.index)) sProf += StringFromKey("Colier_51");
						if (sti(pchar.Fellows.Passengers.carpenter) == sti(sld.index)) sProf += StringFromKey("Colier_52");
						if (sti(pchar.Fellows.Passengers.treasurer) == sti(sld.index)) sProf += StringFromKey("Colier_53");
						link.(sAttr) = GetFullName(&characters[charIdx]) + sProf;
						link.(sAttr).go = "BuyMorganFrigateChr-" + i;
						q++;
					}
				}
			}
			sAttr = "l" + n;
			link.(sAttr) = StringFromKey("Colier_54");
			link.(sAttr).go = "BuyMorganFrigate_exit";
		break;

		case "BuyMorganFrigate_success":
			NextDiag.TempNode = "First time";
			dialog.text = StringFromKey("Colier_55", pchar.name);
			link.l1 = StringFromKey("Colier_56");
			link.l1.go = "exit";
		break;

		// пришли отдать завещание ГПК
		case "BequestToProvidenceLSC_1":
			dialog.text = StringFromKey("Colier_57", pchar.name);
			link.l1 = StringFromKey("Colier_58");
			link.l1.go = "BequestToProvidenceLSC_2";
		break;
		case "BequestToProvidenceLSC_2":
			dialog.text = StringFromKey("Colier_59");
			link.l1 = "...";
			link.l1.go = "BequestToProvidenceLSC_3";
		break;
		case "BequestToProvidenceLSC_3":
			dialog.text = StringFromKey("Colier_60", pchar.name);
			link.l1 = StringFromKey("Colier_61");
			link.l1.go = "BequestToProvidenceLSC_4";
		break;
		case "BequestToProvidenceLSC_4":
			dialog.text = StringFromKey("Colier_62");
			link.l1 = StringFromKey("Colier_63");
			link.l1.go = "BequestToProvidenceLSC_5";
			link.l2 = StringFromKey("Colier_64");
			link.l2.go = "exit";
			pchar.questTemp.LSC = "CoilerNeedMoneyLSC";
			if (sti(pchar.money) >= 100000)
			{
				link.l2 = StringFromKey("Colier_65");
				link.l2.go = "BequestToProvidenceLSC_6";
			}
			if (IsCharacterPerkOn(pchar, "SeaDogProfessional") && GetReputationName(sti(PChar.reputation)) == "REPUTATIONT_BAD_4")
			{
				PlayerRPGCheck_Perk_NotifyPass("SeaDogProfessional");
				PlayerRPGCheck_Reputation_NotifyPass(false, false);
				link.l3 = StringFromKey("Colier_66");
				link.l3.go = "BequestToProvidenceLSC_7";
			}
		break;
		case "BequestToProvidenceLSC_5":
			dialog.text = StringFromKey("Colier_67");
			link.l1 = StringFromKey("Colier_68");
			link.l1.go = "exit";
			PlaySound("Took_item");
			RemoveItems(pchar, "bequestLSC", 1);
			AddQuestRecord("PreparationForISS", "2");
			DeleteAttribute(pchar, "questTemp.LSC.poorName");
			AddDialogExitQuest("ReloadEnableLSC");
			RemoveLandQuestMark_Main(npchar, "PreparationForISS");
		break;
		case "BequestToProvidenceLSC_6":
			dialog.text = StringFromKey("Colier_69");
			link.l1 = StringFromKey("Colier_70");
			link.l1.go = "BequestToProvidenceLSC_12";
			AddMoneyToCharacter(pchar, -100000);
		break;
		case "BequestToProvidenceLSC_7":
			dialog.text = StringFromKey("Colier_71");
			link.l1 = StringFromKey("Colier_72", pchar);
			link.l1.go = "BequestToProvidenceLSC_8";
		break;
		case "BequestToProvidenceLSC_8":
			dialog.text = "...";
			link.l1 = StringFromKey("Colier_73");
			link.l1.go = "BequestToProvidenceLSC_9";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;
		case "BequestToProvidenceLSC_9":
			dialog.text = StringFromKey("Colier_74");
			link.l1 = StringFromKey("Colier_75", pchar);
			link.l1.go = "BequestToProvidenceLSC_10";
		break;
		case "BequestToProvidenceLSC_10":
			dialog.text = StringFromKey("Colier_76");
			link.l1 = StringFromKey("Colier_77");
			link.l1.go = "BequestToProvidenceLSC_11";
		break;
		case "BequestToProvidenceLSC_11":
			dialog.text = StringFromKey("Colier_78");
			link.l1 = StringFromKey("Colier_79");
			link.l1.go = "BequestToProvidenceLSC_12";
		break;
		case "BequestToProvidenceLSC_12":
			dialog.text = StringFromKey("Colier_80");
			link.l1 = StringFromKey("Colier_81");
			link.l1.go = "BequestToProvidenceLSC_13";
		break;
		case "BequestToProvidenceLSC_13":
			dialog.text = StringFromKey("Colier_82");
			link.l1 = StringFromKey("Colier_83");
			link.l1.go = "BequestToProvidenceLSC_14";
		break;
		case "BequestToProvidenceLSC_14":
			dialog.text = StringFromKey("Colier_84");
			link.l1 = StringFromKey("Colier_85");
			link.l1.go = "exit";

			pchar.questTemp.LSC = "PreparationsForDepartureLSC";
			sld = characterFromId("Providencia_PortMan");
			sld.Dialog.currentnode = "PreparationsForDepartureLSC";
			DeleteAttribute(sld, "dontGive");
			AddLandQuestMark_Main(sld, "PreparationForISS");
			AddLandQuestMark_Main_WithCondition(npchar, "PreparationForISS", "PreparationForISS_Done_Colier_QuestMarkCondition");
		break;

		//подготовка к отплытию в ГПК завершена
		case "PreparationsForDepartureLSC_1":
			dialog.text = StringFromKey("Colier_86");
			link.l1 = StringFromKey("Colier_87");
			link.l1.go = "PreparationsForDepartureLSC_2";
		break;
		case "PreparationsForDepartureLSC_2":
			dialog.text = StringFromKey("Colier_88");
			link.l1 = StringFromKey("Colier_89");
			link.l1.go = "PreparationsForDepartureLSC_3";
			AddQuestRecord("PreparationForISS", "3");
			PlaySound("Important_item");
			ChangeItemDescribe("bequestLSC", "itmdescr_bequestDoneLSC");
			AddDialogExitQuest("ReloadEnableLSC");
		break;
		case "PreparationsForDepartureLSC_3":
			aref chrTemp;
			string sTemp;
			int iOfficer = 0;
			string sExclude = "init";

			//послать в добрый путь
			pchar.questTemp.LSC = "BequestToProvidenceDoneLSC";
			npchar.storedLSC = true;
			AddLandQuestMark_Main_WithCondition(npchar, "PreparationForISS", "PreparationForISS_Return_Colier_QuestMarkCondition");
			RemoveLandQuestMark_Main(characterFromId("Providencia_PortMan"), "PreparationForISS");

			for (i = 0; GetPassengersQuantity(pchar) > 0; i++)
			{
				idx = GetPassenger(pchar, 0);
				if (idx == -1) break;
				sld = GetCharacter(idx);
				sTemp = "sld" + i;
				if (StrHasStr(sld.id, sExclude, 1)) continue;
				sExclude = sExclude + "," + sld.id;
				TEV.StoreLSC.(sTemp) = idx;

				//офицеров раскидываем в городе
				if (isOfficerInShip(sld, true))
				{
					sld.Dialog.CurrentNode = "NiceDayLSC";
					TEV.StoreLSC.(sTemp).isOfficer = 1;
					LAi_SetImmortal(sld, true);
					//абордажников снимаем с должности, иначе они нормально не распределяются по городу
					for (int j = 0; j < 4; j++)
					{
						if (GetOfficersIndex(pchar, j) == idx) RemoveOfficersIndex(pchar, GetOfficersIndex(pchar, j));
					}

					if (CheckAttribute(sld, "Capellan")) LAi_CharacterDisableDialog(sld);//капеллану пока не до разговоров
					//первого в бордель
					if (iOfficer == 0)
					{
						LAi_SetSitTypeNoGroup(sld);
						ChangeCharacterAddressGroup(sld, "Providencia_SecBrRoom", "sit", "sit4");
					}
					//второй бродит по городу
					if (iOfficer == 1)
					{
						LAi_SetCitizenTypeNoGroup(sld);
						ChangeCharacterAddressGroup(sld, "Providencia_town", "goto", "goto5");
					}

					//четверо около таверны
					if (iOfficer > 1)
					{
						trace("Providencia_town " + sld.name + iOfficer);
						LAi_SetSitTypeNoGroup(sld);
						if (iOfficer == 2) ChangeCharacterAddressGroup(sld, "Providencia_town", "sit", "sit_front4");
						if (iOfficer == 3) ChangeCharacterAddressGroup(sld, "Providencia_town", "sit", "sit_base4");
						if (iOfficer == 4) ChangeCharacterAddressGroup(sld, "Providencia_town", "sit", "sit_base3");

						//остальные в таверну
						if (iOfficer >= 5)
						{
							LAi_SetSitTypeNoGroup(sld);
							FreeSitLocator("Providencia_tavern", "sit" + iOfficer);
							ChangeCharacterAddressGroup(sld, "Providencia_tavern", "sit", "sit" + iOfficer);
						}
					}
					iOfficer++;
				}
				else
				{
					//остальные просто куда-то отошли по делам
					if (CheckAttribute(sld, "HiredDate")) TEV.StoreLSC.(sTemp).isOfficer = 1;
					else TEV.StoreLSC.(sTemp).isOfficer = 0;
					ChangeCharacterAddress(sld, "none", "");
				}
				RemovePassenger(pchar, sld);
			}
			//<------ снять офицеров и разместить в городе

			//выдать люггер
			pchar.Ship.Type = GenerateShipExt(SHIP_LUGGER, true, pchar);
			pchar.Ship.Name = GenerateRandomNameToShip(PIRATE);
			SetBaseShipData(pchar);
			SetCrewQuantity(pchar, 10);
			RecalculateCargoLoad(pchar);
			pchar.location.from_sea = "Providencia_town"; // корабль в порту

			//забрать корабли и выдать баркасу (тут прячeм компаньонов, реализация понадобится для секретного убежища)
			/*for (i = 0; i < COMPANION_MAX; i++)
            {
                idx = GetCompanionIndex(PChar, i);
                if (idx == -1) break;

                if (i == 0) //У ГГ забираем старое и даём новое корыто
                {
                    sld = GetCharacter(NPC_GenerateCharacter("StoreBroLSC", "", "man", "man", sti(PChar.rank) + 5, PIRATE, -1, true)); //временщик
                    sld.Ship.Type = GenerateShipExt(SHIP_BARKAS, true, sld);
                    sld.Ship.Name = GenerateRandomNameToShip(PIRATE);
                    SetBaseShipData(sld);
                    SetCrewQuantity(sld, 10);
                    DumpAttributes(sld);
                    idx = sld.index;
                    SetCompanionIndex(pchar, -1, idx);
                    sld.curshipnum = COMPANION_MAX;
                    SeaAI_SwapShipsAttributes(pchar, sld, true);
                }
                else
                {
                    sld = GetCharacter(idx);
                    sTemp = "ship" + i;
                    TEV.StoreLSC.(sTemp) = idx;
                    RemoveCharacterCompanion(pchar, sld);
                }
            }*/
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		// пришли забрать своё после ГПК
		case "TakeAllFromProvidenceLSC_1":
			dialog.text = StringFromKey("Colier_90", GetFullName(pchar));
			link.l1 = StringFromKey("Colier_91");
			link.l1.go = "TakeAllFromProvidenceLSC_2";
			link.l2 = StringFromKey("Colier_92");
			link.l2.go = "TakeAllFromProvidenceLSC_2";
		break;
		case "TakeAllFromProvidenceLSC_2":
			dialog.text = StringFromKey("Colier_93");
			link.l1 = StringFromKey("Colier_94");
			link.l1.go = "TakeAllFromProvidenceLSC_3";
		break;
		//вот тут по хорошему прописать иф, если мы приперлись спустя год.
		case "TakeAllFromProvidenceLSC_3":
			dialog.text = StringFromKey("Colier_95");
			link.l1 = StringFromKey("Colier_96");
			link.l1.go = "TakeAllFromProvidenceLSC_4";
			link.l2 = StringFromKey("Colier_97"); //Тут еще один ИФ придется писать
			link.l2.go = "exit";
		break;
		case "TakeAllFromProvidenceLSC_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();

			aref aStore;
			aref tempObject;

			RemoveItems(pchar, "bequestLSC", 1);
			DeleteAttribute(npchar, "storedLSC");
			RemoveLandQuestMark_Main(npchar, "PreparationForISS");

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
				// Восстановление компаньонов
				//TODO к релизу убрать, т.к. теперь компаньонов восстанавливаем сами с помощью ПУ
				/* if (HasStr(GetAttributeName(tempObject), "ship"))
				 {
					 if (sld.id == "StoreBroLSC")
					 {
						 idx = GetPassenger(pchar, 0);
						 SeaAI_SwapShipsAttributes(GetCharacter(idx), sld, true);
						 DeleteCharacter(sld);
						 RemovePassenger(pchar, GetCharacter(idx));
					 }
					 SetCompanionIndex(pchar, -1, idx);
				 }*/
			}

			// удаление временного хранилища
			DeleteAttribute(&TEV, "StoreLSC");
		break;
	}
}
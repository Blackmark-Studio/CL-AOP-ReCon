void ProcessDialogEvent()
{
	ref NPChar, refLoc;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref chr, rShip, rItm;
	float fTemp;
	bool bOk;
	int i, iTemp, iCount;
	string sAttr, sProf, sGun, sGunType;
	string attrL, sType;
	ref rAmmo;

	sGunType = GUN_ITEM_TYPE;
	if (MusketPriority(pchar))
		sGunType = MUSKET_ITEM_TYPE;

	sGun = GetCharacterEquipByGroup(pchar, sGunType);

	sAttr = Dialog.CurrentNode; //HardCoffee вызов в каюту
	if (HasSubStr(sAttr, "Call_"))
	{
		i = sti(FindStringAfterChar(sAttr, "_"));
		chr = &characters[i];
		sAttr = GetFullName(chr);
		for (iTemp = 0; iTemp < COMPANION_MAX; iTemp++)
		{
			if (GetCompanionIndex(pchar, iTemp) == i)
			{
				bOk = true;
				PlaceCompanionCloneNearMChr(iTemp, false);
				break;
			}
			bOk = false;
		}
		if (!bOk)
		{
			if (CheckAttribute(loadedLocation, "locators.reload.reload1") && LAi_IsLocatorFree("reload", "reload1", -0.2))
				PlaceCharacter(chr, "reload", PChar.location);
			else PlaceCharacter(chr, "rld", PChar.location);
			if (CheckAttribute(chr, "prisoned") && sti(chr.prisoned) == true)
			{
				LAi_SetStayTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, "Prisoner");
				LAi_MethodDelay("TurnPrisonerToPchar", 2); //повернуть арестанта в сторону гг
			}
			else
			{
				LAi_SetWarriorTypeNoGroup(chr);
				LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
			}
			//LAi_tmpl_goto_SetLocator(chr, "rld", LAi_FindFreeRandomLocator("rld"), -1.0);
			float locx, locy, locz;
			GetCharacterPos(chr, &locx, &locy, &locz);
			LAi_tmpl_goto_SetLocator(chr, "rld", LAi_FindNearestFreeLocator("rld", locx, locy, locz), -1.0);
		}
		Log_info(StringFromKey("InfoMessages_152", sAttr));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit_Self();
	}

	if (HasStr(sAttr, "SetGunBullets1_"))
	{
		i = findsubstr(sAttr, "_", 0);
		TEV.CT.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1);
		Dialog.CurrentNode = "SetGunBullets2";
	}
	if (HasStr(sAttr, "ChoosePotion1_"))
	{
		i = findsubstr(sAttr, "_", 0);
		TEV.CT.ChoosePotion = strcut(sAttr, i + 1, strlen(sAttr) - 1);
		Dialog.CurrentNode = "ChoosePotion2";
	}

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		case "EnterCasper_self":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			DoReloadCharacterToLocation("SanGabrielMechanic", "reload", "reload1");

			if (CheckAttribute(pchar, "quest.LSC_TempTomasWarrior")) // Томас Бойл с нами
			{
				pchar.quest.LSC_TempTomasWarrior.over = "yes";
				chr = CharacterFromId("LSC_Prisoner1");
				ChangeCharacterAddressGroup(chr, "SanGabrielMechanic", "reload", "reload1");
			}
		break;
		case "WaitCasper":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			SetCurrentTime(23, 55);
			WaitDate("", 0, 0, 0, 0, 10);
			DoQuestReloadToLocation("LostShipsCity_town", "item", "wait", "");
			RecalculateJumpTable();
			RefreshWeather();
			RefreshLandTime();
		break;
		case "EnterCasper_suicideSquad":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			DeleteAttribute(pchar, "questTemp.LSC.suicideSquad");
			DoReloadCharacterToLocation("SanGabrielMechanic", "reload", "reload1");
		break;

		//==================================================================================================================
		//	Французский сюжет
		//==================================================================================================================
		// диалог матери и фр. офицера в начале игры
		case "FL1":
			dialog.text = StringFromKey("MainHero_dialog_1");
			link.l1 = StringFromKey("MainHero_dialog_2");
			link.l1.go = "FL1_1";
		break;

		case "FL1_1":
			dialog.text = StringFromKey("MainHero_dialog_3");
			link.l1 = StringFromKey("MainHero_dialog_4");
			link.l1.go = "exit";
		break;

		case "FL2":
			dialog.text = StringFromKey("MainHero_dialog_5");
			link.l1 = StringFromKey("MainHero_dialog_6");
			link.l1.go = "FL2_1";
		break;

		case "FL2_1":
			dialog.text = StringFromKey("MainHero_dialog_7");
			link.l1 = StringFromKey("MainHero_dialog_8");
			link.l1.go = "FL2_2";
		break;

		case "FL2_2":
			dialog.text = StringFromKey("MainHero_dialog_9");
			link.l1 = "...";
			link.l1.go = "exit";
		break;

		case "FL3_1":
			dialog.text = StringFromKey("MainHero_dialog_10");
			link.l1 = StringFromKey("MainHero_dialog_11");
			link.l1.go = "FL3_2";
		break;

		case "FL3_2":
			dialog.text = StringFromKey("MainHero_dialog_12");
			link.l1 = StringFromKey("MainHero_dialog_13");
			link.l1.go = "exit";
		break;

		// Диалог Фуше и патрульного на Тортуге
		case "FL4_1":
			PlaySound("Voice\" + VoiceGetLanguage() + "\FranceLine\stoyatkuda.wav");

			dialog.text = StringFromKey("MainHero_dialog_14");
			link.l1 = StringFromKey("MainHero_dialog_15");
			link.l1.go = "exit";
		break;

		case "FL2_18":
			PlaySound("VOICE\" + VoiceGetLanguage() + "\FranceLine\otday.ogg");
			dialog.text = StringFromKey("MainHero_dialog_16");
			link.l1 = StringFromKey("MainHero_dialog_17");
			link.l1.go = "FL2_18_1";
		break;

		case "FL2_18_1":
			dialog.text = StringFromKey("MainHero_dialog_18");
			link.l1 = StringFromKey("MainHero_dialog_19");
			link.l1.go = "FL2_18_2";
			LAi_Fade("FL2_s18b", "");
		break;

		case "FL2_18_2":
			DialogExit();
			DoQuestCheckDelay("FL2_s18c", 0.1);
		break;

		case "FL2_s20":
			dialog.text = StringFromKey("MainHero_dialog_20");
			link.l1 = StringFromKey("MainHero_dialog_21");
			link.l1.go = "FL2_s20_1";
		break;

		case "FL2_s20_1":
			DialogExit();
			locCameraFollow();
		break;

		case "First time":
			NextDiag.TempNode = "First time";

			Dialog.Text = StringFromKey("MainHero_dialog_22");
			Link.l1 = StringFromKey("MainHero_dialog_23");
			Link.l1.go = "exit";
			//ОЗГ
			//===> Сюжетная линейка Мишеля де Граммона
			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL1_s50")
			{
				dialog.text = StringFromKey("MainHero_dialog_24");
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuest("FL1_s49c");
			}
			//===> Квест Кондотьера
			if (CheckAttribute(pchar, "questTemp.Headhunter") && pchar.questTemp.Headhunter == "halen_room")
			{
				dialog.text = StringFromKey("MainHero_dialog_25");
				link.l1 = "...";
				link.l1.go = "exit";
				AddDialogExitQuestFunction("RatHunters_Sleep");
			}
			//===> Квесты мэра, базар после боевки на палубе
			if (CheckAttribute(pchar, "quest.DestroyPirate_PirateIsOut") || CheckAttribute(pchar, "quest.CaptainComission_CapIsOut"))
			{
				dialog.text = StringFromKey("MainHero_dialog_26");
				Link.l1 = "...";
				Link.l1.go = "exit";
				pchar.quest.Munity = "Deads";
			}
			// ==> Английская линейка, квест №8: в поселении буканьеров
			if (pchar.questTemp.State == "ToMansfield_GoOn")
			{
				dialog.text = StringFromKey("MainHero_dialog_27");
				link.l1 = "...";
				link.l1.go = "exit";
			}
			// ==> Исп. линейка, квест №4: в спальне донны Анны
			if (pchar.questTemp.State == "Sp4Detection_toMirderPlace")
			{
				dialog.text = StringFromKey("MainHero_dialog_28");
				link.l1 = "...";
				link.l1.go = "exit";
				pchar.questTemp.State = "Sp4Detection_FoundLetter";
				AddQuestRecord("Spa_Line_4_MirderDetection", "2");
				AddQuestUserData("Spa_Line_4_MirderDetection", "sSex", GetSexPhrase("", "а"));
				AddLandQuestmark_Main(CharacterFromID("Havana_waitress"), "Spa_Line");
			}
			// ==> Французская линейка, квест №2: в таверне Тортуги
			if (pchar.questTemp.State == "Fr2Letter_SeekProblems")
			{
				dialog.text = StringFromKey("MainHero_dialog_29");
				link.l1 = "...";
				link.l1.go = "exit";
				pchar.questTemp.Out = 1;
				SaveCurrentQuestDateParam("questTemp");
			}
			// ==> Изабелла, нашли мертвую служанку
			if (pchar.RomanticQuest == "SeekIsabella" && pchar.location == "Beliz_ExitTown")
			{
				dialog.text = StringFromKey("MainHero_dialog_30");
				link.l1 = "...";
				link.l1.go = "exit";
				pchar.RomanticQuest = "FoundServantGirl";
			}
			// ==> Квест Аскольда, обнаружение входа в пещеру к гробнице
			if (pchar.questTemp.Ascold == "Ascold_NotEnterFoundGrave")
			{
				dialog.text = StringFromKey("MainHero_dialog_31");
				link.l1 = "";
				link.l1.go = "exit";
				AddLandQuestmark_Main(CharacterFromID("Ascold"), "Ascold");
			}
			//===> Квест Аскольда, попытка вскрыть лампу.
			if (pchar.questTemp.Azzy == "Azzy_IHaveLamp" && locations[reload_location_index].type == "shipyard")
			{
				dialog.text = StringFromKey("MainHero_dialog_32");
				Link.l1 = StringFromKey("MainHero_dialog_33");
				Link.l1.go = "FreedomAzzy";
			}
			//===> шебека Синяя Птица
			if (pchar.questTemp.BlueBird == "seenCarriers")
			{
				dialog.text = StringFromKey("MainHero_dialog_34");
				Link.l1 = "...";
				Link.l1.go = "exit";
				AddDialogExitQuestFunction("BlueBird_endCaveDialog");
			}
		break;
		// boal -->

		case "TalkSelf_Main":
			NextDiag.TempNode = "First time";
			//===> ожидалка кавалеров Армо
			if (CheckAttribute(pchar, "questTemp.LSC.TalkSelf_Armo"))
			{
				DeleteAttribute(pchar, "questTemp.LSC.TalkSelf_Armo");
				dialog.text = StringFromKey("MainHero_dialog_35");
				link.l1 = StringFromKey("MainHero_dialog_36");
				link.l1.go = "exit";
				link.l2 = StringFromKey("MainHero_dialog_37");
				link.l2.go = "WaitCasper";
				break;
			}
			//===> финальная реплика-рассуждение в LSC
			if (CheckAttribute(pchar, "questTemp.LSC.TalkSelf_Start"))
			{
				DeleteAttribute(pchar, "questTemp.LSC.TalkSelf_Start");
				dialog.text = StringFromKey("MainHero_dialog_38");
				link.l1 = StringFromKey("MainHero_dialog_39");
				link.l1.go = "EnterCasper_self";
				if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad"))
				{
					aref aSuicideSquad;
					makearef(aSuicideSquad, pchar.questTemp.LSC.suicideSquad);
					if (GetAttributesNum(aSuicideSquad) > 0)
					{
						link.l2 = StringFromKey("MainHero_dialog_40");
						link.l2.go = "EnterCasper_suicideSquad";
					}
				}
				link.l3 = StringFromKey("MainHero_dialog_41");
				link.l3.go = "exit";
				break;
			}
			//===> финальная реплика-рассуждение в LSC
			if (pchar.questTemp.LSC == "finishSelfTalk")
			{
				LAi_ActorTurnByLocator(pchar, "reload", "reload66");
				dialog.text = StringFromKey("MainHero_dialog_42");
				link.l1 = StringFromKey("MainHero_dialog_43");
				link.l1.go = "exit";
				link.l2 = StringFromKey("MainHero_dialog_44");
				link.l2.go = "exit";
				link.l3 = StringFromKey("MainHero_dialog_45");
				link.l3.go = "exit";
				link.l4 = StringFromKey("MainHero_dialog_46");
				link.l4.go = "exit";
				AddDialogExitQuest("LSC_finishMovie"); //TODO По идее тут будет выдача уникальной черты для персонажу. Если повезёт и успеем.
				break;
			}
			if (CheckAttribute(pchar, "questTemp.LocationClone")) //navy after duel in tavern
			{
				Dialog.Text = StringFromKey("MainHero_dialog_49", RandPhraseSimple(
							StringFromKey("MainHero_dialog_47"),
							StringFromKey("MainHero_dialog_48")));
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.LocationClone");
				break;
			}

			Dialog.Text = StringFromKey("MainHero_dialog_52", RandPhraseSimple(
						StringFromKey("MainHero_dialog_50"),
						StringFromKey("MainHero_dialog_51")));

			if (CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL1_s60")
			{
				link.l1 = StringFromKey("MainHero_dialog_53");
				link.l1.go = "FL1_s60_exit";
			}

			//исп.линейка, квест №6, возможность переночевать в оплаченной комнате
			if (CheckAttribute(pchar, "questTemp.State.Open") && pchar.location == "Tortuga_tavern_upstairs")
			{
				if (makeint(environment.time) >= 22.0 || makeint(environment.time) < 10.0)
				{
					link.l1 = StringFromKey("MainHero_dialog_54");
					link.l1.go = "TalkSelf_room_day";
				}
				else
				{
					link.l1 = StringFromKey("MainHero_dialog_55");
					link.l1.go = "TalkSelf_room_night";
					link.l2 = StringFromKey("MainHero_dialog_56");
					link.l2.go = "TalkSelf_room_day";
				}
			}

			if (Get_My_Cabin() == pchar.location)
			{
				//HardCoffee приглашения в каюту -->
				if (GetOfficerPassengerQuantity(pchar))
				{
					link.callOfficer = StringFromKey("MainHero_dialog_57");
					link.callOfficer.go = "callOfficerToCabin";
				}

				if (GetPrisonerQty() > 0)
				{
					link.callPrisoner = StringFromKey("MainHero_dialog_58");
					link.callPrisoner.go = "callPrisonerToCabin";
				}

				if (!bDisableMapEnter) //боя в море нет
				{
					if (GetCompanionQuantity(PChar) > 1)
					{
						link.callCompanion = StringFromKey("MainHero_dialog_59");
						link.callCompanion.go = "callCompanionToCabin";
					}    // <-- HardCoffee приглашения в каюту
					if (GetCargoGoods(pchar, GOOD_SLAVES) > 0)
					{
						Link.l6 = StringFromKey("MainHero_dialog_60");
						Link.l6.go = "TalkSelf_SlavesToCrew";
					}
				}

				if (GetDlcEnabled(NABOB_PACK))
				{
					if ("1" == TEV.cabinParrot)
					{
						Link.parrot = StringFromKey("MainHero_dialog_141");
						Link.parrot.go = "putParrotAway";
					}
					else if (TEV.cabinParrot == "0" && !IsEntity(&ParrotLocModel))
					{
						Link.parrot = StringFromKey("MainHero_dialog_142");
						Link.parrot.go = "showParrot";
					}
				}

			}
			if (IsTimeSkipPossible()) // 21.03.09 Warship fix Во время линейки Блада отдыхать нельзя
			{
				Link.l7 = StringFromKey("MainHero_dialog_61");
				if (CheckPossibleTimeSkip()) Link.l7.go = "TalkSelf_StartWait";
				else Link.l7.go = "TalkSelf_StartWaitDisable";
			}
			// захват города
			if (GetCharIDXForTownAttack(pchar.location) != -1 && !CheckAttribute(Pchar, "GenQuestFort.StartAttack") && pchar.location != "Providencia_ExitTown") //Rosarak Временно блочим Провиденсию
			{
				Link.l8 = StringFromKey("MainHero_dialog_62");
				Link.l8.go = "TalkSelf_TownAttack";
			}

			if (StrStartsWith(pchar.location, "my_"))
			{
				if (LootCollectorCheckCrew())
				{
					chr = GetCharacter(sti(pchar.Fellows.Passengers.boatswain));
					if (or(CheckCharacterPerk(pchar, "LootCollection") || CheckCharacterPerk(chr, "LootCollection"),
					 	CheckCharacterPerk(pchar, "Mentor") || CheckCharacterPerk(chr, "Mentor")) &&
					 	 chr.location != pchar.location && pchar.location != Get_My_Cabin())
					{
						Link.l9 = StringFromKey("MainHero_dialog_63", GetFullName(chr));
						Link.l9.go = "TalkSelf_Looting_BoatswainCall";
					}
				}

				if (CheckHoldBox(false) > 0)
				{
					Link.l10 = StringFromKey("MainHero_dialog_64");
					Link.l10.go = "TalkSelf_Looting_Info";
				}
			}

			if (sGun != "" && CheckAttribute(pchar, "chr_ai." + sGunType + ".bulletNum") && sti(pchar.chr_ai.(sGunType).bulletNum) > 0)
			{
				Link.l11 = StringFromKey("MainHero_dialog_65");
				Link.l11.go = "SetGunBullets";
			}

			if (FindPotionTypesQty(pchar) > 0 || CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l12 = StringFromKey("MainHero_dialog_66");
				Link.l12.go = "ChoosePotion";
			}

			// evganat - пасха
			if (CheckAttribute(pchar, "questTemp.easter.xolotl_shore") && !bDisableMapEnter && pchar.location == Get_My_Cabin() && !CheckAttribute(pchar, "questTemp.easter.xolotl_incabin"))
			{
				link.l13 = StringFromKey("MainHero_dialog_67");
				link.l13.go = "Xolotl_summon";
			}
			if (CheckAttribute(pchar, "questTemp.easter.xolotl_shore") && Whr_IsStorm())
			{
				link.l14 = StringFromKey("MainHero_dialog_68");
				link.l14.go = "WhereIsXolotl";
			}

			if (CheckSelfRepairConditions()) //Ремонт на берегу
			{
				Link.l15 = StringFromKey("MainHero_dialog_69");
				Link.l15.go = "StartSelfRepair";
			}

			Link.l16 = StringFromKey("MainHero_dialog_72", RandPhraseSimple(
						StringFromKey("MainHero_dialog_70"),
						StringFromKey("MainHero_dialog_71")));
			Link.l16.go = "exit";
		break;
		case "StartSelfRepair":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			LaunchRepair(pchar);
		break;

		case "SetGunBullets":
			Dialog.Text = StringFromKey("MainHero_dialog_73");
			rItm = ItemsFromID(sGun);
			sType = rItm.chargetype;
			iTemp = KZ|Symbol(sType, ",");

			for (i = 0; i <= iTemp; i++)
			{
				sAttr = sType;

				if (iTemp > 0)
					sAttr = GetSubStr(sType, ",", i);

				if (sAttr != "")
				{
					rAmmo = ItemsFromID(rItm.type.(sAttr).bullet);
					TEV.CT.AMMOQ = " " + StringFromKey("MainHero_dialog_74");

					if (GetCharacterItem(pchar, rAmmo.id) > 0)
					{
						TEV.CT.AMMOQ = " (";

						if (sAttr == LAi_GetCharacterBulletType(pchar, sGunType) && GetCharacterItem(pchar, sAttr) > 0)
							TEV.CT.AMMOQ = " " + StringFromKey("MainHero_dialog_75") + " ";

						TEV.CT.BULLET = GetCharacterItem(pchar, rAmmo.id);
						TEV.CT.POWDER = GetCharacterItem(pchar, LAi_GetAmmoGunpowderType(sAttr));

						if (LAi_GetAmmoGunpowderType(sAttr) != "")
							TEV.CT.CHARGE = func_min(sti(TEV.CT.BULLET), sti(TEV.CT.POWDER));
						else
							TEV.CT.CHARGE = TEV.CT.BULLET;

						TEV.CT.AMMOQ = StringFromKey("MainHero_dialog_76", TEV.CT.AMMOQ, TEV.CT.CHARGE);
					}

					attrL = "l" + i;
					Link.(attrL) = GetConvertStr(rAmmo.name, "ItemsDescribe.txt") + TEV.CT.AMMOQ;
					Link.(attrL).go = "SetGunBullets1_" + i;
				}
			}

			Link.l99 = StringFromKey("MainHero_dialog_77");
			Link.l99.go = "TalkSelf_Main";
		break;

		case "SetGunBullets2":
			rItm = ItemsFromID(sGun);
			TEV.CT.TEMP0 = GetConvertStr(rItm.name, "ItemsDescribe.txt");
			sAttr = rItm.chargetype;

			if (KZ|Symbol(sAttr, ",") > 0)
				sAttr = GetSubStr(rItm.chargetype, ",", sti(TEV.CT.SetGunBullets));

			TEV.CT.TEMP1 = rItm.type.(sAttr).bullet;
			LAi_SetCharacterUseBullet(pchar, sGunType, TEV.CT.TEMP1);
			LAi_GunSetUnload(pchar, sGunType);
			rItm = ItemsFromID(TEV.CT.TEMP1);
			Log_Clear();
			LogSound_WithNotify(StringFromKey("InfoMessages_198", GetFullName(pchar), TEV.CT.TEMP0, GetConvertStr(rItm.name, "ItemsDescribe.txt")), "Reload", "AmmoSelect");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;

		case "ChoosePotion":
			Dialog.Text = StringFromKey("MainHero_dialog_78");

			aref Items, arItems;
			attrL = "";
			makearef(arItems, pchar.items);
			iTemp = GetAttributesNum(arItems);

			for (i = 0; i < iTemp; i++)
			{
				rItm = ItemsFromID(GetAttributeName(GetAttributeN(arItems, i)));
				if (!CheckAttribute(rItm, "potion")) continue;
				if (!CheckAttribute(rItm, "potion.health")) continue;

				attrL = "l" + i;
				Link.(attrL) = StringFromKey("MainHero_dialog_79", GetConvertStr(rItm.name, "ItemsDescribe.txt"), sti(GetCharacterItem(pchar, rItm.id)));
				Link.(attrL).go = "ChoosePotion1_" + rItm.id;
			}

			if (CheckAttribute(pchar, "GenQuest.Potion_choice"))
			{
				Link.l98 = StringFromKey("MainHero_dialog_80");
				Link.l98.go = "ChoosePotion3";
			}

			Link.l99 = StringFromKey("MainHero_dialog_81");
			Link.l99.go = "TalkSelf_Main";
		break;

		case "ChoosePotion2":
			rItm = ItemsFromID(TEV.CT.ChoosePotion);
			log_info(StringFromKey("InfoMessages_238", GetConvertStr(rItm.name, "ItemsDescribe.txt")));
			pchar.GenQuest.Potion_choice = TEV.CT.ChoosePotion;
			DialogExit_Self();
		break;

		case "ChoosePotion3":
			log_info(StringFromKey("InfoMessages_239"));
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			DialogExit_Self();
		break;

		// evganat - пасха
		case "WhereIsXolotl":
			dialog.text = StringFromKey("MainHero_dialog_82", XI_ConvertString(pchar.questTemp.easter.xolotl_shore + "Pre"));
			link.l1 = "";
			link.l1.go = "exit";
		break;

		case "Xolotl_summon":
			if (CheckAttribute(pchar, "questTemp.easter.xolotl_shore") && pchar.NearestLandLocatorInRadius == pchar.questTemp.easter.xolotl_shore)
			{
				EasterSummonXolotl();
				DialogExit_Self();
				break;
			}
			dialog.text = "";
			link.l1 = StringFromKey("MainHero_dialog_83");
			link.l1.go = "exit";
		break;

		case "FL1_s60_exit":
			AddDialogExitQuest("FL1_s61");
			DialogExit_Self();
		break;

		case "TalkSelf_StartWaitDisable":
			dialog.text = StringFromKey("MainHero_dialog_84");
			link.l1 = "";
			link.l1.go = "exit";
		break;

		case "TalkSelf_StartWait":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
			PChar.GenQuest.CallFunctionParam = "LaunchTavernWaitScreen";
			DoQuestCheckDelay("CallFunctionParam", 0.1); // Нужно с задержкой, иначе - ГГ начинает крутиться
		break;

		case "TalkSelf_room_night":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Night");
			TavernWaitDate("wait_night");
			DialogExit_Self();
		break;

		case "TalkSelf_room_day":
			NextDiag.CurrentNode = NextDiag.TempNode;
			//AddDialogExitQuestFunction("TavernWaitDate_Day");
			TavernWaitDate("wait_day");
			DialogExit_Self();
		break;
		//  захват города
		case "TalkSelf_TownAttack":
			bOk = (GetPartyCrewQuantity(Pchar, true) >= 500) || bBettaTestMode;
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && bOk)
			{
				chr = GetCharacter(GetCharIDXForTownAttack(pchar.location));
				if (chr.from_sea == Pchar.location.from_sea)
				{
					Dialog.Text = StringFromKey("MainHero_dialog_85");
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					if (pchar.location == "Panama_ExitTown" && !sti(Colonies[FindColony("PortoBello")].HeroOwn))
					{
						Dialog.Text = StringFromKey("MainHero_dialog_86");
						Link.l1 = "...";
						Link.l1.go = "exit";
					}
					else
					{
						Dialog.Text = StringFromKey("MainHero_dialog_87", GetCityName(chr.City));
						Link.l1 = StringFromKey("MainHero_dialog_88");
						Link.l1.go = "TalkSelf_TownAttack_Start";
						Link.l2 = StringFromKey("MainHero_dialog_89");
						Link.l2.go = "exit";
					}
				}
			}
			else
			{
				if (!CheckAttribute(Pchar, "GenQuestFort.StartAttack"))
				{
					Dialog.Text = StringFromKey("MainHero_dialog_90");
					Link.l1 = "...";
					Link.l1.go = "exit";
				}
				else
				{
					Dialog.Text = StringFromKey("MainHero_dialog_91");
					Link.l2 = "...";
					Link.l2.go = "exit";
				}
			}
		break;

		case "TalkSelf_TownAttack_Start":
			NextDiag.CurrentNode = NextDiag.TempNode;

			Pchar.GenQuestFort.StartAttack = true;
			Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
			DeleteQuestAttribute("Union_with_Escadra");
			chr = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (isCityHasFort(chr.City))
			{
				SetLocationCapturedState(chr.from_sea, true);
			}
			else
			{
				SetLocationCapturedState(chr.Default, true); // для сухопутных
			}
			AddDialogExitQuest("Capture_Forts");
			Ship_NationAgressive(chr, chr);
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  -->
		case "TalkSelf_SlavesToCrew":
			if (GetCurCrewEscadr() >= GetMaxCrewAble())
			{
				Dialog.Text = StringFromKey("MainHero_dialog_92");
				Link.l1 = StringFromKey("MainHero_dialog_93");
				Link.l1.go = "exit";
			}
			else
			{
				if (GetCrewQuantity(pchar) >= GetMaxCrewQuantity(pchar))
				{
					Dialog.Text = StringFromKey("MainHero_dialog_94");
					Link.l1 = StringFromKey("MainHero_dialog_95");
					Link.l1.go = "exit";
				}
				else
				{
					if (GetFreeCrewQuantity(pchar) <= GetCargoGoods(pchar, GOOD_SLAVES))
					{
						pchar.GenQuest.SlavesToCrew = GetFreeCrewQuantity(pchar);
					}
					else
					{
						pchar.GenQuest.SlavesToCrew = GetCargoGoods(pchar, GOOD_SLAVES);
					}
					Dialog.Text = StringFromKey("MainHero_dialog_96", pchar.GenQuest.SlavesToCrew);
					Link.l1 = StringFromKey("MainHero_dialog_97");
					Link.l1.go = "TalkSelf_SlavesToCrew_1";
					Link.l2 = StringFromKey("MainHero_dialog_98");
					Link.l2.go = "exit";
				}
			}
		break;

		case "TalkSelf_SlavesToCrew_1":
			if (CheckOfficersPerk(pchar, "IronWill"))
			{
				AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 5.0));
			}
			else
			{
				AddCrewMorale(pchar, -makeint(sti(pchar.GenQuest.SlavesToCrew) / 3.0));
			}
			// падение опыта -->
			fTemp = stf(GetCrewQuantity(pchar) + sti(pchar.GenQuest.SlavesToCrew));
			pchar.Ship.Crew.Exp.Sailors = (stf(pchar.Ship.Crew.Exp.Sailors) * GetCrewQuantity(pchar) +
					stf(pchar.Ship.Crew.Exp.Sailors) * 0.3 * sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Cannoners = (stf(pchar.Ship.Crew.Exp.Cannoners) * GetCrewQuantity(pchar) +
					stf(pchar.Ship.Crew.Exp.Cannoners) * 0.3 * sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			pchar.Ship.Crew.Exp.Soldiers = (stf(pchar.Ship.Crew.Exp.Soldiers) * GetCrewQuantity(pchar) +
					stf(pchar.Ship.Crew.Exp.Soldiers) * 0.3 * sti(pchar.GenQuest.SlavesToCrew)) / fTemp;
			// падение опыта <-- 
			pchar.Ship.Crew.Quantity = sti(pchar.Ship.Crew.Quantity) + sti(pchar.GenQuest.SlavesToCrew);
			RemoveCharacterGoodsSelf(pchar, GOOD_SLAVES, sti(pchar.GenQuest.SlavesToCrew));

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
		// Зачислить рабов в команду  <--
		// boal <--

		//navy CONTRABAND METRO -->
		case "GenTravel_Main":
			NextDiag.TempNode = "First time";
			dialog.Text = StringFromKey("MainHero_dialog_99");
			Link.l1 = StringFromKey("MainHero_dialog_100");
			Link.l1.go = "exit";

			chr = CharacterFromID("Abracham_Gray");
			chr.location = "none";
			SeaExchangeCharactersShips(PChar, chr, false, false);
			SetCrewQuantity(PChar, 0);

			//грузим ГГ куда нужно...
			SetAnyReloadToLocation(pchar.GenQuest.contraTravel.destination.loc, pchar.GenQuest.contraTravel.destination.group, pchar.GenQuest.contraTravel.destination.locator, "", 0, 0, 0, 0);
			AddDialogExitQuest("AnyReloadToLocation");
			chrDisableReloadToLocation = false;

			CloseQuestHeader("Gen_ContrabandTravel");
			setCharacterShipLocation(PChar, pchar.GenQuest.contraTravel.destination.loc);
			setWDMPointXZ(pchar.GenQuest.contraTravel.destination.loc);

			//трем аттрибуты
			DeleteAttribute(PChar, "GenQuest.contraTravel");
		break;
		//navy CONTRABAND METRO <--

		// Квест Аскольда, Туманы от Лейфа.
		case "Leif_MisteryMists":
			Dialog.Text = StringFromKey("MainHero_dialog_101");
			Link.l1 = StringFromKey("MainHero_dialog_102");
			Link.l1.go = "exit";

			AddDialogExitQuestFunction("Ascold_LeifGiveMeFog_End");
		break;

		// Квест Аскольда, освобождение Аззи.
		case "FreedomAzzy":
			chr = GetCharacter(NPC_GenerateCharacter("Azzy", "Azzy", "man", "man", 22, PIRATE, -1, false));
			chr.name = FindPersonalName("Azzy_name");
			chr.lastname = FindPersonalName("Azzy_lastname");
			chr.Dialog.Filename = "Quest\Azzy_dialog.c";
			GiveItem2Character(chr, "blade28");// сабля Моргана
			chr.equip.blade = "blade28";
			chr.rank = 100;
			chr.reputation = "0";
			SetSelfSkill(chr, 100, 100, 100, 100, 100);
			SetShipSkill(chr, 100, 100, 100, 100, 100, 100, 100, 100, 100);
			LAi_SetImmortal(chr, true);
			LAi_SetActorType(chr);
			LAi_SetLoginTime(chr, 0.0, 24.0);
			LAi_SetHP(chr, 10000.0, 10000.0);
			chr.greeting = "Gr_Azzy";
			ChangeCharacterAddressGroup(chr, pchar.location, "officers", "reload1_1");
			DoQuestCheckDelay("Ascold_AzzyIsFree", 4.0);
			pchar.questTemp.Azzy = "Azzy_Freedom";
			pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
			DialogExit();
			Achievment_Set(ACH_Ispolnitel_zhelaniy);
		break;

		case "TalkSelf_Looting_BoatswainCall":
			chr = GetCharacter(sti(pchar.Fellows.Passengers.boatswain));
			PlaceCharacter(chr, "rld", pchar.location);
			LAi_SetStayType(chr);
			DialogExit_Self();
		break;

		case "TalkSelf_Looting_Info":
			refLoc = &locations[FindLocation("My_Deck")];
			TEV.LootingInfoMoney = "0";

			if (CheckAttribute(refLoc, "box1.money") && sti(refLoc.box1.money) > 0)
				TEV.LootingInfoMoney = sti(refLoc.box1.money);

			Link.l1 = StringFromKey("MainHero_dialog_103");
			Link.l1.go = "TalkSelf_Main";

			if (CheckHoldBox(false) > 2)
			{
				Dialog.Text = StringFromKey("MainHero_dialog_104", sti(TEV.LootingInfoMoney));
				Link.l2 = StringFromKey("MainHero_dialog_105");
				Link.l2.go = "TalkSelf_Looting_Money";
				Link.l3 = StringFromKey("MainHero_dialog_106");
				Link.l3.go = "TalkSelf_Looting_Erase";
			}
			else
			{
				if (CheckHoldBox(false) < 2)
				{
					Dialog.Text = StringFromKey("MainHero_dialog_107");
					Link.l2 = StringFromKey("MainHero_dialog_108");
					Link.l2.go = "TalkSelf_Looting_Erase";
				}
				else
				{
					Dialog.Text = StringFromKey("MainHero_dialog_109", sti(TEV.LootingInfoMoney));
					Link.l2 = StringFromKey("MainHero_dialog_110");
					Link.l2.go = "TalkSelf_Looting_Money";
				}
			}
		break;

		case "TalkSelf_Looting_Erase":
			Dialog.Text = StringFromKey("MainHero_dialog_111");
			Link.l1 = StringFromKey("MainHero_dialog_112", pchar);
			Link.l1.go = "TalkSelf_Main";
			Link.l2 = StringFromKey("MainHero_dialog_113");
			Link.l2.go = "TalkSelf_Looting_Erase_Accept";
		break;

		case "TalkSelf_Looting_Erase_Accept":
			iTemp = sti(pchar.money);
			CheckHoldBox(true);
			LogSound_WithNotify(StringFromKey("InfoMessages_141"), "Ship\jakor_00" + (1 + rand(1)) + ".wav", "BoxMinus");

			if (sti(pchar.money) > iTemp)
				LogSound_WithNotify(StringFromKey("InfoMessages_142", (sti(pchar.money) - iTemp)), "Took_item", "Money");

			DialogExit_Self();
		break;

		case "TalkSelf_Looting_Money":
			Dialog.Text = StringFromKey("MainHero_dialog_114");
			Link.l1 = StringFromKey("MainHero_dialog_115");
			Link.l1.go = "TalkSelf_Main";
			Link.l2 = StringFromKey("MainHero_dialog_116");
			Link.l2.go = "TalkSelf_Looting_Money_Accept";
		break;

		case "TalkSelf_Looting_Money_Accept":
			iTemp = sti(pchar.money);
			refLoc = &locations[FindLocation("My_Deck")];
			pchar.money = makeint(sti(pchar.money) + sti(refLoc.box1.money));
			refLoc.box1.money = 0;

			if (sti(pchar.money) > iTemp)
				LogSound_WithNotify(StringFromKey("InfoMessages_142", (sti(pchar.money) - iTemp)), "Took_item", "Money");

			DialogExit_Self();
		break;

		case "callCompanionToCabin":    //HardCoffee приглашения в каюту
			link.l0 = StringFromKey("MainHero_dialog_117", pchar);
			link.l0.go = "TalkSelf_Main";
			if (CheckAttribute(loadedLocation, "locators.reload.reload1") && !LAi_IsLocatorFree("reload", "reload1", 0.05))
			{
				dialog.text = StringFromKey("MainHero_dialog_118");
				link.l99 = StringFromKey("MainHero_dialog_119");
			}
			else if (HaveFreeSpaceInCabin())
			{
				Dialog.Text = StringFromKey("MainHero_dialog_120");
				iCount = 0;
				for (i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp < 0) continue;
					chr = &characters[iTemp];
					if (CheckAttribute(chr, "Tasks.Clone") || CheckAttribute(chr, "NonRemovable") || chr.id == pchar.id) continue;
					iCount++;
					sAttr = "l" + (iCount);
					rShip = GetRealShip(sti(chr.Ship.Type));
					link.(sAttr) = GetFullName(chr) + " (" + xiStr(rShip.BaseName) + " '" + chr.Ship.Name + "')";
					link.(sAttr).go = "Call_" + iTemp;
				}
				if (0 == iCount) link.l99 = StringFromKey("MainHero_dialog_121");
				else link.l99 = StringFromKey("MainHero_dialog_122");
			}
			else
			{
				dialog.text = StringFromKey("MainHero_dialog_123");
				link.l99 = StringFromKey("MainHero_dialog_124");
			}
			link.l99.go = "exit";
		break;

		case "callPrisonerToCabin":
			link.l0 = StringFromKey("MainHero_dialog_125", pchar);
			link.l0.go = "TalkSelf_Main";
			if (CheckAttribute(loadedLocation, "locators.reload.reload1") && !LAi_IsLocatorFree("reload", "reload1", -0.2))
			{
				dialog.text = StringFromKey("MainHero_dialog_126");
				link.l99 = StringFromKey("MainHero_dialog_127");
			}
			else if (HaveFreeSpaceInCabin())
			{
				Dialog.Text = StringFromKey("MainHero_dialog_128");
				iCount = 0;
				for (i = 0; i < GetPassengersQuantity(pchar); i++)
				{
					iTemp = GetPassenger(pchar, i);
					if (iTemp == -1) continue;
					chr = &characters[iTemp];
					if (Get_My_Cabin() == chr.location) continue;
					if (CheckAttribute(chr, "prisoned") && sti(chr.prisoned) > 0)
					{
						iCount++;
						sAttr = "l" + (iCount);
						sProf = "(" + NationNameMan(sti(chr.nation));
						if (CheckAttribute(chr, "survivor")) sProf = sProf + ", " + LowerFirst(XI_ConvertString("shipwrecked"));
						else if (CheckAttribute(chr, "Back.Ship.Mode") && chr.nation != PIRATE)
						{
							if ("war" == chr.Back.Ship.Mode) sProf = sProf + ", " + LowerFirst(XI_ConvertString("War"));
							else if ("trade" == chr.Back.Ship.Mode) sProf = sProf + ", " + LowerFirst(XI_ConvertString("Merchant"));
						}
						sProf = sProf + ")";
						link.(sAttr) = GetFullName(chr) + " " + sProf;
						link.(sAttr).go = "Call_" + iTemp;
					}
				}
				if (0 == iCount) link.l99 = StringFromKey("MainHero_dialog_129");
				else link.l99 = StringFromKey("MainHero_dialog_130");
			}
			else
			{
				dialog.text = StringFromKey("MainHero_dialog_131");
				link.l99 = StringFromKey("MainHero_dialog_132");
			}
			link.l99.go = "exit";
		break;

		case "callOfficerToCabin":
			link.l0 = StringFromKey("MainHero_dialog_133", pchar);
			link.l0.go = "TalkSelf_Main";
			if (CheckAttribute(loadedLocation, "locators.reload.reload1") && !LAi_IsLocatorFree("reload", "reload1", 0.05))
			{
				dialog.text = StringFromKey("MainHero_dialog_134");
				link.l99 = StringFromKey("MainHero_dialog_135");
			}
			else if (HaveFreeSpaceInCabin())
			{
				dialog.text = StringFromKey("MainHero_dialog_136");
				iCount = 0;
				for (i = 0; i < GetPassengersQuantity(pchar); i++)
				{
					iTemp = GetPassenger(pchar, i);
					if (iTemp == -1) continue;
					chr = &characters[iTemp];
					if (Get_My_Cabin() == chr.location) continue;
					if (CheckAttribute(chr, "prisoned") && sti(chr.prisoned) > 0) continue;
					if (CheckAttribute(chr, "NonRemovable") && !CheckAttribute(chr, "Capellan")) continue;
					sProf = GetOfficerOccupation(chr);
					iCount++;
					sAttr = "l" + (iCount);
					link.(sAttr) = GetFullName(chr) + " " + sProf;
					link.(sAttr).go = "Call_" + iTemp;
				}
				if (0 == iCount) link.l99 = StringFromKey("MainHero_dialog_137");
				else link.l99 = StringFromKey("MainHero_dialog_138");
			}
			else
			{
				dialog.text = StringFromKey("MainHero_dialog_139");
				link.l99 = StringFromKey("MainHero_dialog_140");
			}
			link.l99.go = "exit";
		break;
		// приглашения в каюту <--

		case "putParrotAway":
			DisableCabinParrot();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;

		case "showParrot":
			TEV.cabinParrot = "1";
			CreateParrotInLocation(loadedlocation, true);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit_Self();
		break;
	}
}

void DialogExit_Self()
{
	DialogExit();
	locCameraSleep(false); //boal
	DeleteAttributeEx(&TEV, "LootingInfoMoney,LootingTempMode");
}

int CheckHoldBox(bool del)
{
	aref itemsARef;
	ref locRef = &locations[FindLocation("My_Deck")];
	int result = 0;

	if (del)
	{
		DeleteAttribute(locRef, "box1.items");
		locRef.box1.items = "";
		pchar.money = makeint(sti(pchar.money) + sti(locRef.box1.money));
		locRef.box1.money = 0;
		return 0;
	}

	if (CheckAttribute(locRef, "box1"))
	{
		if (CheckAttribute(locRef, "box1.items"))
		{
			makearef(itemsARef, locRef.box1.items);

			if (GetAttributesNum(itemsARef) > 0)
				result += 1;
		}

		if (CheckAttribute(locRef, "box1.money"))
		{
			if (sti(locRef.box1.money) <= 0) // а вдруг?
				locRef.box1.money = 0;
			else
				result += 2;
		}
	}
	return result;
}

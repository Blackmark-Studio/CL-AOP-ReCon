void QuestComplete(string sQuestName, string qname)
{
	// boal -->
	ref sld, npchar;
	aref arOldMapPos, arAll, arPass;
	int iTemp, i, ShipType, iRank, iCount; // нужно для вычислений любых целых (нации)
	float locx, locy, locz, fTemp;
	string attrName, Model, Blade, Gun, sTemp, sQuestTown, sQuestTitle; // любые строки для вычислений
	bool bOk;
	if (bQuestLogShow)
	{
		Log_Info("Quest completed : " + sQuestName + "  param = " + qname);
		trace("Quest completed : " + sQuestName + "  param = " + qname + " " + GetQuestBookDataDigit());
	}
	// boal <--

	if (CheckAttribute(pchar, "quest." + qname + ".function"))
	{
		string sFunction = pchar.quest.(qname).function;
		call sFunction(qname);
		return;
	}

	switch (sQuestName)
	{
		// boal -->
		// смена отношений от времени
		// boal все теперь проверяется 15-25 день при расчёте состояния мира = изменение в 5% - ранд(100) > 95
		case "Nation_Legend":
			SetTimerCondition("Nation_Legend", 0, 0, 15 + rand(10), true);
			// --> тут чиним стророжевиков
			if (!bSeaActive && !bAbordageStarted)
			{
				//TODO: нужно? RepairAllDefenderFortShips();
			}
			// <-- тут чиним стророжевиков
			if (rand(100) > 93 && !bWorldAlivePause)
			{
				if (IsEntity(&worldMap))
				{
					LaunchNationLegend();
				}
				else
				{
					if (!bQuestCheckProcessFreeze) // можно показать
					{
						DoQuestCheckDelay("Nation_Legend_Map", 1.5);
					}
					else
					{
						Pchar.quest.Nation_Legend_Map.win_condition.l1 = "MapEnter";
						Pchar.quest.Nation_Legend_Map.win_condition = "Nation_Legend_Map";
					}
				}
			}
		break;

		case "Nation_Legend_Map":
			if (!bQuestCheckProcessFreeze) // можно показать
			{
				LaunchNationLegend();
			}
			else
			{
				Pchar.quest.Nation_Legend_Map_TEST.win_condition.l1 = "MapEnter";
				Pchar.quest.Nation_Legend_Map_TEST.win_condition = "Nation_Legend_Map";
			}
		break;

		case "LocTeleport":
			TeleportCharacterToPos(pchar, stf(pchar.locx), stf(pchar.locy), stf(pchar.locz));
		break;

		// начало игры, туториал
		case "Tut_StartGame_CheckMinHP_1":
			if (!CheckAttribute(pchar, "HeroParam.Teach_beat"))
			{
				pchar.HeroParam.Teach_beat = 0;
			}
			pchar.HeroParam.Teach_beat = sti(pchar.HeroParam.Teach_beat) + 1;
			sld = characterFromID("Sailor_1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
			bOk = false;
			if (sti(pchar.HeroParam.Teach_beat) == 1 && sti(pchar.HeroParam.Teach_battle) == 1)
			{
				bOk = true;
			}
			else
			{
				if (sti(pchar.HeroParam.Teach_beat) == 2 && sti(pchar.HeroParam.Teach_battle) == 2)
				{
					bOk = true;
					pchar.HeroParam.Teach_beat = 3; // признак, что выиграл
				}
			}
			if (bOk)
			{
				DoQuestCheckDelay("Tut_StartGame_CheckMinHP_Hero", 0.3);
			}
		break;

		case "Tut_StartGame_CheckMinHP_2":
			if (!CheckAttribute(pchar, "HeroParam.Teach_beat"))
			{
				pchar.HeroParam.Teach_beat = 0;
			}
			pchar.HeroParam.Teach_beat = sti(pchar.HeroParam.Teach_beat) + 1;
			sld = characterFromID("Sailor_2");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
			if (sti(pchar.HeroParam.Teach_beat) == 2 && sti(pchar.HeroParam.Teach_battle) == 2)
			{
				sld = characterFromID("Sailor_1");
				LAi_SetActorTypeNoGroup(sld);
				pchar.HeroParam.Teach_beat = 3; // признак, что выиграл
				DoQuestCheckDelay("Tut_StartGame_CheckMinHP_Hero", 0.3);
			}
		break;

		case "Tut_StartGame_CheckMinHP_Hero":
		// запуск диалога
			LAi_SetActorTypeNoGroup(pchar);
			sld = characterFromID("Sailor_2");
			LAi_SetActorTypeNoGroup(sld);
			sld = characterFromID("Sailor_1");
			LAi_SetActorTypeNoGroup(sld);
			PChar.GenQuest.CallFunctionParam = "Tut_StartDialog";
			DoQuestCheckDelay("CallFunctionParam", 2.0);
		break;
		//  Карты сокровищ  ГЕНЕРАТОР -->
		case "SetTreasureFromMap":
			SetTreasureBoxFromMap();
		break;
		//  Карты сокровищ  ГЕНЕРАТОР <--

		case "ArestInResidenceEnd":
		//LAi_LocationFightDisable(&Locations[FindLocation(Pchar.quest.ArestInResidenceEnd.ResidenceLocation)], true);
			LAi_LockFightMode(Pchar, false); // ножками убежал
		break;
		// ОЗГи
		case "Battle_Hunters_Land":
			Lai_SetPlayerType(pchar);
			LAi_SetFightMode(Pchar, true);
			DeleteAttribute(pchar, "PostEventQuest.questDelay.MainHeroFightModeOff");
			for (i = 1; i <= sti(PChar.HunterCost.Qty); i++)
			{
				sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				//LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
				LAi_group_MoveCharacter(sld, "LAND_HUNTER");
			}
			//LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			//LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
			LAi_group_SetRelation("LAND_HUNTER", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("LAND_HUNTER", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("LAND_HUNTER", "Battle_Hunters_Over");

			// Rosarak. Помощь при хорошем отношении нации
			if (CheckAttribute(loadedLocation, "townsack"))
			{
				TEV.GUARDS.iNation = GetCityNation(loadedLocation.townsack);
				TEV.GUARDS.iRel = GetCharacterReputation_WithNation(pchar, sti(TEV.GUARDS.iNation));
				if (sti(TEV.GUARDS.iRel) > 20 && GetNationRelation2MainCharacter(sti(TEV.GUARDS.iNation)) != RELATION_ENEMY
				&& !LAi_grp_alarmactive && rand(100) > (80 - sti(TEV.GUARDS.iRel))) // От 40% на Хорошем до 100% на Восхищении
				{
					Log_Info(StringFromKey("InfoMessages_39"));
					TEV.GUARDS.group = GetNationNameByType(sti(TEV.GUARDS.iNation)) + "_citizens";
					LAi_group_SetRelation(TEV.GUARDS.group, LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
					pchar.quest.Battle_Hunters_Escape.win_condition.l1 = "ExitFromLocation";
					pchar.quest.Battle_Hunters_Escape.win_condition.l1.location = pchar.location;
					pchar.quest.Battle_Hunters_Escape.win_condition = "Battle_Hunters_Over"; // Вернуть отношение группы при побеге
				}
				else if (sti(TEV.GUARDS.iNation) != PIRATE && !LAi_grp_alarmactive) Log_Info(StringFromKey("InfoMessages_40"));
			}
		break;

		case "Battle_Hunters_Over":
			LAi_group_RemoveCheck("LAND_HUNTER");
			LAi_group_Delete("LAND_HUNTER");
			if (!CheckAttribute(&TEV, "GUARDS")) break;
			if (CheckAttribute(&TEV, "GUARDS.group"))
			{
				if (CheckAttribute(pchar, "quest.Battle_Hunters_Escape"))
				{
				    pchar.quest.Battle_Hunters_Escape.over = "yes";
				}
				LAi_group_SetRelation(LAI_GROUP_PLAYER, TEV.GUARDS.group, LAI_GROUP_NEITRAL);
			}
			DeleteAttribute(&TEV, "GUARDS");
		break;

		case "GoAway_Hunters_Land":
		//LAi_SetActorType(Pchar);
		//DoQuestCheckDelay("pchar_back_to_player", 4.0);
			LAi_LockFightMode(pchar, false);
			DeleteAttribute(pchar, "PostEventQuest.questDelay.MainHeroFightModeOff");
			DoQuestCheckDelay("OpenTheDoors", 4.0);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			for (i = 1; i <= sti(PChar.HunterCost.Qty); i++)
			{
				sld = characterFromID(PChar.HunterCost.TempHunterType + "LandHunter0" + i);
				//LAi_RemoveCheckMinHP(sld);  можно пальнуть в спину, тогда по идее будет бой
				LAi_type_actor_Reset(sld);
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
			}
		break;

		case "Officers_Citizen_Type":
			for (i = 0; i < sti(TEV.walkers.count); i++)
			{
				sTemp = GetSubStringByNum(TEV.walkers, i);
				sld = characterFromID(sTemp);
				LAi_SetCitizenTypeNoGroup(sld);
				EquipCharacterByItem(sld, FindCharacterItemByGroup(sld, GUN_ITEM_TYPE));
                // ~!mu
			}
			DeleteAttribute(&TEV, "walkers");
		break;

		// офицеры выживают!
		case "Survive_In_SeaOfficer":
			sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaOfficerIdx));
			iTemp = NPC_GeneratePhantomCharacter("citizen", sti(sld.Nation), MAN, -1);  // создать клон
			if (iTemp != -1)
			{
				npchar = &Characters[iTemp];
				if (CheckAttribute(sld, "PGGAi"))
				{
					sTemp = npchar.id; // новый рандомный ИД
					DeleteAttribute(npchar, "");// все трем, а там и перки!
					CopyAttributes(npchar, sld);

					npchar.index = iTemp;
					// меняемся ИД, старый новому, новый трупу
					sld.id = sTemp; //navy (ПГГ fix) 26.12.06
					// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
					DeleteAttribute(npchar, "Ship");
					npchar.ship.type = SHIP_NOTUSED;
					npchar.location = "none";
					npchar.location.from_sea = "";

					DeleteAttribute(npchar, "Fellows"); // его офицеры
					// пгг в рядового НПС
					sld.LifeDay = 0;
					DeleteAttribute(sld, "PGGAi");
				}
				else
				{
					ChangeAttributesFromCharacter(npchar, sld, true);

					sld.location = "none";
					sld.location.from_sea = "";
				}
				PlaySound("Encounter_Map_1");
				LAi_SetCurHPMax(npchar);
				AddPassenger(Pchar, npchar, false);
				Log_Info(StringFromKey("InfoMessages_41", XI_ConvertString("Officer"), GetFullName(npchar)));
			}
		break;

		case "Get_TreasureBarrel":
			Set_TreasureBarrel();
		break;

		// враги спасшиеся на шлюпках homo
		case "Survive_In_SeaPrisoner":  //homo 22/06/07
			sld = GetCharacter(sti(Pchar.GenQuest.Survive_In_SeaPrisonerIdx));
			iTemp = SetCharToPrisoner(sld);
			if (iTemp != -1)
			{
				npchar = &Characters[iTemp];
				PlaySound("Encounter_Map_1");
				// лишнее, помер ПГГ и все тут if (findsubstr(sld.id, "PsHero_" , 0) != -1) npchar = sld.id; //homo for navy (ПГГ fix)
				LAi_SetCurHPMax(npchar);
				sld.location = "none";
				sld.location.from_sea = "";
				Log_Info(StringFromKey("InfoMessages_42", GetFullName(npchar)));
			}
		break;
		//  ЛГ
		case "Survive_In_Sea":
			DeleteSeaEnvironment();
			PChar.GenQuest.GhostShip.KillMe = sti(PChar.GenQuest.GhostShip.KillMe) + 1;
			PChar.GenQuest.GhostShip.AskAbout = 2; // опять будет
			Survive_In_Sea_Go2Land();
		break;

		case "GhostShip_Dead":
			if (CheckAttribute(pchar, "GenQuest.GhostShip.LastBattle"))
			{
				Log_Info(StringFromKey("InfoMessages_43"));
				AddQuestRecord("GhostShipQuest", "Dead_2");
				AddQuestUserData("GhostShipQuest", "sSex", GetSexPhrase("", "а"));
				CloseQuestHeader("GhostShipQuest");
				RemoveLandQuestmarkToFantoms_Main("habitue", "GhostShipQuest");

				AddCharacterExpToSkill(PChar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Sailing", 500);
				AddCharacterExpToSkill(PChar, "Accuracy", 500);
				AddCharacterExpToSkill(PChar, "Cannons", 500);
				AddCharacterExpToSkill(PChar, "Repair", 500);
				AddCharacterExpToSkill(PChar, "Defence", 500);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
				PChar.GenQuest.GhostShip.LastBattleEnd = true;
				// меняем парус у корабля, если корабль взял ГГ
				sld = GetRealShip(sti(pchar.GenQuest.GhostShip.ShipType));
				DeleteAttribute(sld, "EmblemedSails.normalTex");
				//слухи
				for (i = 0; i < 3; i++)
				{
					switch (i)
					{
						case 0:
							sTemp = StringFromKey("Common_rumours_86");
						break;
						case 1:
							sTemp = StringFromKey("Common_rumours_87");
						break;
						case 2:
							sTemp = StringFromKey("Common_rumours_88");
						break;
					}
					iTemp = FindRumour(AddSimpleRumourTip(sTemp, 60, 1, "habitue", ""));
					Rumour[iTemp].group = "GhostShip_Dead";
				}
				Achievment_Set(ACH_Razrushitel_proklyatiy);
			}
			else
			{
				Log_Info(StringFromKey("InfoMessages_44"));
				AddQuestRecord("GhostShipQuest", "Dead_1");
				AddQuestUserData("GhostShipQuest", "sSex", GetSexPhrase("ся", "ась"));
				AddCharacterExpToSkill(PChar, "Leadership", 600);
				AddCharacterExpToSkill(PChar, "Sailing", 1000);
				AddCharacterExpToSkill(PChar, "Accuracy", 1000);
				AddCharacterExpToSkill(PChar, "Cannons", 1000);
				AddCharacterExpToSkill(PChar, "Repair", 1000);
				AddCharacterExpToSkill(PChar, "Defence", 1000);
				AddCharacterExpToSkill(PChar, "Sneak", 500);
				PChar.GenQuest.GhostShip.DeadByMe = sti(PChar.GenQuest.GhostShip.DeadByMe) + 1;
				PChar.GenQuest.GhostShip.AskAbout = 2; // опять будет
				/*PChar.GenQuest.VideoAVI        = "Ending";
                PChar.GenQuest.VideoAfterQuest = "";

                DoQuestCheckDelay("PostVideo_Start", 0.1); */
			}
		break;

		case "GhostCapt_OfferPrize":
			Sea_CabinStartNow();
			pchar.quest.GhostShipCapInCabin.win_condition.l1 = "location";
			pchar.quest.GhostShipCapInCabin.win_condition.l1.location = Get_My_Cabin();
			pchar.quest.GhostShipCapInCabin.win_condition = "GhostShipCapInCabinOffer";
		break;

		case "GhostShipCapInCabinOffer":
			chrDisableReloadToLocation = true;
			LAi_LockFightMode(pchar, true);
			sld = CharacterFromID("GhostCapt");
			sld.dialog.currentnode = "GhostCapt_Prize";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "GhostShipCapInCabinDied":
			sld = CharacterFromID("GhostCapt");
			LAi_SetCurHP(sld, 0.0);
		break;

		case "GhostShipHelp": // битва в порту
			chrDisableReloadToLocation = true;
			Pchar.GenQuestFort.FarLocator = true;
			sTemp = "officers"; // не везде есть!
			for (i = 0; i < MAX_TOWN_CREW; i++)
			{
				sld = SetFantomSkeletForts(sTemp, "", "TOWN_BATTLE_SOLDIERS", "GhostShipCrew");
				if (sld.location.locator == "")
				{
					sTemp = "rld";
					sld = SetFantomSkeletForts(sTemp, "", "TOWN_BATTLE_SOLDIERS", "GhostShipCrew");
					if (sld.location.locator == "") break;
				}
			}
			// наши
			Pchar.GenQuestFort.FarLocator = false;
			// помощь эскадре
			iTemp = sti(Characters[GetCharacterIndex(pchar.GenQuest.GhostShipWorkId)].nation);

			for (i = 0; i < MAX_ESCADRA_CREW; i++) //всегда 5 даем
			{
				SetFantomDefenceLocal("goto", "", iTemp, LAI_GROUP_PLAYER);
			}
			// натравим
			LAi_group_SetHearRadius("TOWN_BATTLE_SOLDIERS", 100.0);
			LAi_group_FightGroupsEx("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			LAi_group_SetRelation("TOWN_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

			LAi_group_SetCheck("TOWN_BATTLE_SOLDIERS", "GhostShipHelp_Finish");
			LAi_SetFightMode(Pchar, true);
		break;

		case "GhostShipHelp_Finish":
			LAi_SetFightMode(Pchar, false);
			LAi_grp_alarmactive = false; // конец тревоги

			if (!CheckAttribute(pchar, "GenQuest.GhostShip.ChurchHelpStart"))
			{
				// город
				sTemp = "GhostShipDone_" + pchar.GenQuest.GhostShipWorkId;
				pchar.GenQuest.(sTemp) = true;
				Log_Info(StringFromKey("InfoMessages_45"));
				Statistic_AddValue(Pchar, "QuestGhostShipHelp_Done", 1);
				AddQuestRecord("GhostShipQuest", "help_t2");
			}
			else
			{
				// бухта
				pchar.GenQuest.GhostShip.ChurchHelp = true;
				Log_Info(StringFromKey("InfoMessages_46"));
				DeleteAttribute(pchar, "GenQuest.GhostShip.ChurchHelpStart");
				//AddQuestTemplate("GhostShipQuest", "church_t2");
				Statistic_AddValue(Pchar, "QuestChurchHelpGhostShip_Done", 1);
			}
			PlaySound("DoorLocked");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			SetLocationCapturedState(pchar.location, false);
		break;
		// помощь церкви
		case "GhostShipChurchShorePlace":
			Pchar.GenQuest.Hunter2Pause = true;

			Pchar.GenQuest.GhostShip.ChurchHelpStart = true;

			chrDisableReloadToLocation = true;
			Pchar.GenQuestFort.FarLocator = true;
			sTemp = "officers"; // не везде есть!
			iTemp = 3 + rand(4);
			for (i = 0; i < iTemp; i++)
			{
				sld = SetFantomSkeletForts(sTemp, "", "SKEL_BATTLE_SOLDIERS", "GhostShipCrew");
				if (sld.location.locator == "")
				{
					sTemp = "reload"; // опасно - может быть лодка!
					sld = SetFantomSkeletForts(sTemp, "", "SKEL_BATTLE_SOLDIERS", "GhostShipCrew");
					if (sld.location.locator == "") break;
				}
			}
			Pchar.GenQuestFort.FarLocator = false;

			// натравим
			LAi_group_SetHearRadius("SKEL_BATTLE_SOLDIERS", 100.0);
			LAi_group_FightGroupsEx("SKEL_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
			LAi_group_SetRelation("SKEL_BATTLE_SOLDIERS", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

			LAi_group_SetCheck("SKEL_BATTLE_SOLDIERS", "GhostShipHelp_Finish");
			LAi_SetFightMode(Pchar, true);
		break;
		// GhostShipHelp <--
		////////////////////////////////////Квест награда за голову///////////////////////////////////////////////////////
		case "SeaHunterCheck":
			SeaHunterCheck();
		break;

		case "CheckMaxHealthQuest":
			SetTimerCondition("CheckMaxHealthQuest", 0, 0, 5, true);
			SetNewDayHealthMax();
		break;

		case "My_Deck_Battle_End":  //после драк с пленными
			if ("My_Deck" != pchar.location) Reset_Officers_InCabin(); //HardCoffee чтобы появилась возможность диалога с офицерами после битвы
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); //HardCoffee для битв в каюте.
			chrDisableReloadToLocation = false;
			LAi_SetFightMode(Pchar, false);
			if (CheckAttribute(pchar, "equip.blade") && pchar.equip.blade == "unarmed")
				LAi_MethodDelay("Take_Fists_Away", 1.5); //Оденем на гг его экпировку
		break;

		// Индульгенция
		case "donation":
			int iDonation = MakeInt(PChar.questTemp.donate);
			int iRep      = MakeInt(PChar.reputation);
			int iRepIncr;
            // Тут целочисленное деление
			if (iRep < 10)      iRepIncr = iDonation / 1000;
            else if (iRep < 80) iRepIncr = iDonation / (1000 * (iRep/10 + 1));
            else                iRepIncr = iDonation / 10000;
			if (iRep < REPUTATION_MAX && iRepIncr)
            {
                ChangeCharacterReputation(PChar, iRepIncr);
                PChar.questTemp.donate = 0;
            }
		break;

		case "SetQuestHoldBox": // трюм
			if (Pchar.location == "My_Deck") FillQuestHoldBox(&Locations[FindLocation(Pchar.location)]);
		break;

		case "Munity_on_Ship_Map":
			if (IsEntity(&worldMap) && GetCrewQuantity(pchar) > 0) MunityOnShip("ShipMunity");
		break;

		case "Munity_on_Ship":
			pchar.quest.Munity = "";
			pchar.GenQuest.MunityStart = true;
			PlaySound("Boarding_1");
			InterfaceStates.Buttons.Save.enable = 0;
			LAi_SetFightMode(Pchar, true);

			if (!CheckAttribute(pchar, "GenQuest.SlavesMunity"))
			{
				for (i = 1; i <= 9; i++)
				{
					sld = SetFantomDefenceLocal("goto", "", PIRATE, LAI_GROUP_TmpEnemy);
					if (i >= (sti(PChar.Ship.Crew.Quantity) / ((8 - GetCharacterShipClass(PChar)) * 8))) break;
					RemoveCharacterCrew(PChar, (8 - GetCharacterShipClass(PChar)) * 8);
				}
				PChar.Ship.Crew.Morale = 25;
				ChangeCrewExp(PChar, "Soldiers", 2); // бонус на подавление
			}
			else
			{
				for (i = 1; i <= 9; i++)
				{
					sld = SetFantomSlaves("goto", "", LAI_GROUP_TmpEnemy);
					if (i >= (GetCargoGoods(PChar, GOOD_SLAVES) / ((8 - GetCharacterShipClass(PChar)) * 8))) break;
					RemoveCharacterGoodsSelf(PChar, GOOD_SLAVES, (8 - GetCharacterShipClass(PChar)) * 8);
				}
				DeleteAttribute(pchar, "GenQuest.SlavesMunity");
				ChangeCrewExp(PChar, "Soldiers", 3); // бонус на подавление
			}
			LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
			LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
			LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

			LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "Dead_Munity");
		break;

		case "Dead_Munity":
			if (CheckAttribute(pchar, "questTemp.MunityOfficerIDX.begin") && Pchar.questTemp.MunityOfficerIDX.begin == "1")
			{
				Log_SetStringToLog(StringFromKey("InfoMessages_47"));
				pchar.questTemp.MunityOfficerIDX = "-1";
				Pchar.questTemp.MunityOfficerIDX.begin = "0";
			}
			else Log_SetStringToLog(StringFromKey("InfoMessages_48"));

			InterfaceStates.Buttons.Save.enable = 1;
			pchar.quest.Munity = "Deads";
			LAi_SetFightMode(Pchar, false);
			DeleteAttribute(pchar, "GenQuest.MunityStart");
		break;

		///  захват форта - город
		case "FreeCaptureForts": // уберем солдат, откроем входы (на всяк случай) при выходе на карту
			TWN_FreeCaptureForts();
		break;
		// захват с суши по диалогу мэра (телепорт)
		case "Town_Capture_Land":
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			//Pchar.GenQuestFort.SoundOff = true;
			DeleteQuestAttribute("Union_with_Escadra");

			SetLocationCapturedState(sld.Default, true);

			DoQuestReloadToLocation(sld.Default.BoardLocation, sld.Default.BoardGroup, sld.Default.BoardLocator, "Capture_Forts");
		break;

		case "Capture_Town_Siege":
			PrepareTownBattle(); // тут только джунгли для этого случая

			if (!CheckAttribute(Pchar, "GenQuestFort.SoundOff"))
			{
				PlaySound("Landing_0");
				AddCharacterExpToSkill(Pchar, "Leadership", 100);
				AddCharacterExpToSkill(Pchar, "Sneak", 100);
			}
			else
			{
				DeleteAttribute(Pchar, "GenQuestFort.SoundOff");
			}
		break;
		// Возвращение губернаторам родные диалоги // boal переделал 251204
		case "Return_Gover_Dialog":
			Characters[sti(PChar.GenQuest.GoverIdx)].dialog.CurrentNode = "First time";
		break;

		case "Return_Gover_Dialog_Exit":
			DoQuestCheckDelay("Return_Gover_Dialog", 0.5);
		break;
		// после битвы в форте сюда
		case "Capture_Forts":
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			if (sld.city == "Villemstad") VillemstadResGatesUnlock(); //Открыть ворота
			TWN_Capture_Forts();
		break;

		case "FightInTown":
			TWN_FightInTown();
		break;

		case "FightInTown_OpenNext":
			TWN_FightInTown_OpenNext();
		break;

		case "FightInTown_Finish":
			DeleteAttributeMass(&TEV, "Music", "KeepPlaying,ForceKeepPlaying,ForcePlayTrack");
			LAi_group_Delete("TOWN_BATTLE_SOLDIERS");
			LAi_grp_alarmactive = false; // конец тревоги

			//AlexBlade - сменим диалог у губера после того как разберемся со стражей
			ref Builder;
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			Builder = characterFromID(sld.City + "_Mayor");

			if (CheckAttribute(Builder, "dialog.captureNode")) //eddy. а то снимает нужную мне ноду.
			{
				Builder.dialog.CurrentNode = Builder.dialog.captureNode;
				DeleteAttribute(Builder, "dialog.captureNode");
			}
			else Builder.dialog.CurrentNode = "CAPTURE_Main";

			//LAi_LocationFightDisable(&Locations[FindLocation(Pchar.location)], true); eddy. не лочить боевки в резиденции
			LAi_LockFightMode(pchar, false);
			LAi_SetFightMode(Pchar, false);
		break;

		//Два пути захвата форта
		// 1 уходим с добычей - в диалоге мэра

		// 2 Если оставляем форт себе
		case "Residence_Captured_Any":
			TWN_Residence_Captured_Any();
		break;

		case "Residence_Captured_Any_02":
			TWN_Residence_Captured_Any_02();
		break;

		case "Back_Mayor_Type":
			TWN_Back_Mayor_Type();
		break;

		case "CapturedToOurCity":
			ResetSoundBoarding();
			KZ|Random("Action\Battle\Victory");
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));

			Log_Info(StringFromKey("InfoMessages_49", XI_ConvertString("ColonyLevel4"), GetCityName(sld.City)));

			// убрать контрабандиста
			sTemp = sld.City + "_Smuggler";
			if (GetCharacterIndex(sTemp) >= 0) // не везде есть
			{
				ChangeCharacterAddress(characterFromID(sTemp), "None", ""); // вся логика теперь в рассидки таверны
			}
			SetCaptureTownByHero(sld.City);
			LaunchColonyInfoScreen(); // табличка   TODO даёт вылет
			// отсчет для отбития
			//if (!isCityHasFort(sld.City)) // сухопутный город
			sTemp = "Attack_Fort_" + sld.City;
			SetTimerCondition(sTemp, 0, 0, 25 + rand(70), false);
			PChar.Quest.(sTemp).CityId = sld.City;
			PChar.Quest.(sTemp).function = "TWN_Siege_Any";
		break;
		///////////////////////////////// захват города <--
		//  системные фичи
		case "PostVideo_Start":
			bMainMenuLaunchAfterVideo = true;
			PostVideoAndQuest(PChar.GenQuest.VideoAVI, 100, "PostVideo_After");
		break;

		case "PostVideo_After":
			PostEvent("DoInfoShower", 100, "s", "");
			DoQuestCheckDelay(PChar.GenQuest.VideoAfterQuest, 0.1);
		break;

		case "SetTimerEvent":
			attrName = PChar.Quest.(qname).Event;
			sTemp = PChar.Quest.(qname).Event.Type;
			Model = PChar.Quest.(qname).Event.Param;
			SetEventHandler(attrName, attrName, 0);
			Event(attrName, sTemp, Model);
		break;

		case "CallFunctionParam":
			attrName = PChar.GenQuest.CallFunctionParam;
			call attrName();
		break;

		// Warship. CallFunctionParam не хочет работать с диалогами, поэтому испльзовать можно эту...
		case "NextFunction":
			DoQuestFunctionDelay(PChar.QuestTemp.NextFunction, 0.1);
		break;

		// вызов табличкм А в это время..
		case "LaunchFrameForm":
			PChar.GenQuest.CallFunctionParam = "LaunchFrameForm";
			DoQuestCheckDelay("CallFunctionParam", stf(pchar.AutoQuest.FrameDelay));
		break;

		case "Move_Govenour":  // переместим губернатора в другой город
			SetTimerCondition("Move_Govenour", 0, 0, 25 + rand(10), true);
			Move_Govenour();
		break;

		case "pchar_back_to_player":
			Lai_SetPlayerType(pchar);
		break;

		case "God_hit_us": // это такой прикол - задействовать в ловушки для сундуков(boal)
			iTemp = 10 + rand(15);
			if ((MakeInt(pchar.chr_ai.hp) - iTemp) > 0)
			{
				LAi_SetActorType(PChar);
				LAi_ActorAnimation(PChar, "hit_attack_2", "pchar_back_to_player", 1.0);
			}
			if (!LAi_IsImmortal(pchar))
			{
				LAi_ApplyCharacterDamage(pchar, iTemp, "trap");
				SendMessage(pchar, "lfff", MSG_CHARACTER_VIEWDAMAGE, iTemp, MakeFloat(MakeInt(pchar.chr_ai.hp)), MakeFloat(MakeInt(pchar.chr_ai.hp_max)));
				LAi_CheckKillCharacter(pchar);
				SendMessage(pchar, "l", MSG_CHARACTER_STOPSTRAFE);
			}
		break;
		// диалог с ГГ генератор
		case "TalkSelf_Start":
			StartActorSelfDialog("TalkSelf_Main");
		break;
		// диалог с ГГ квестовые реплики
		case "TalkSelf_Quest":
			StartActorSelfDialog("First time");
		break;
		/////  сидим за столом в таверне ->
		case "alc":
			dialogDisable = true;
			LAi_Fade("alc_2_prepare", "alc2");
		break;

		case "alc_2_prepare":
			LAi_SetSitType(pchar);
			LAi_SetActorType(characterFromID(pchar.questTemp.friend_in_tavern));
			LAi_ActorSetSitMode(characterFromID(pchar.questTemp.friend_in_tavern));

			sld = characterFromID(pchar.questTemp.friend_in_tavern);
			FreeSitLocator(sld.Default, sld.Default.ToLocator);  // очистим стул
			ChangeCharacterAddressGroup(pchar, sld.Default, sld.Default.group, sld.Default.ToLocator);
		break;

		case "alc2":
			dialogDisable = false;
			LAi_ActorDialogNow(characterFromID(pchar.questTemp.friend_in_tavern), pchar, "", -1);
		break;

		case "exit_sit":
			if (CheckQuestAttribute("fight_in_tavern", "fight"))
			{
				pchar.quest.fight_in_tavern = "0";
				LAi_SetSitType(characterFromID(pchar.questTemp.friend_in_tavern));
			}
			else
			{
				if (pchar.location.group == "sit")
				{
					LAi_Fade("exit_sit_2", "");
				}
			}
		break;

		case "exit_sit_2":
			sld = characterFromID(pchar.questTemp.friend_in_tavern);
			LAi_SetSitType(sld);
			LAi_SetPlayerType(pchar);
			//ChangeCharacterAddress(pchar, sld.Default, sld.Default.ToGo);
			LAi_PlaceCharInTavern(pchar); // ближний к столу
		break;
		// реплика таверншика о запрете драк -->
		case "tavern_keeper":
			if (pchar.chr_ai.type == "sit")
			{
				LAi_CharacterEnableDialog(pchar);
				DeleteAttribute(pchar, "nonTable");
			}
			attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
			sld = characterFromID(attrName);
			sld.dialog.currentnode = "tavern_keeper";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "tavern_keeper_2", -1);
		break;

		case "tavern_keeper_2":
			attrName = GetCharIDByParam("TavernMan", "location", pchar.location);
			sld = characterFromID(attrName);
			sld.dialog.currentnode = "First time";
			LAi_SetBarmanType(sld);
		break;
		// реплика таверншика о запрете драк <--
		case "without_memory":
			LAi_Fade("exit_sit_2", "saved_by_off");
			bQuestCheckProcessFreeze = true;
			WaitDate("", 0, 0, 0, 5, 30);
			bQuestCheckProcessFreeze = false;
			RefreshLandTime();
		break;

		case "saved_by_off":
			LAi_SetStayType(pchar);
			Log_Info(StringFromKey("InfoMessages_50"));

			int oSum = 500 + rand(4500);
			if (makeint(Pchar.money) < oSum) oSum = makeint(Pchar.money);
			AddMoneyToCharacter(pchar, -oSum);
			if (!CheckAttribute(pchar, "questTemp.stels.tavern") || sti(pchar.questTemp.stels.tavern) != GetDataDay())
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, makeint(50 + oSum / 100));
				pchar.questTemp.stels.tavern = GetDataDay();
			}

			sld = characterFromID(loadedLocation.fastreload + "_waitress");
			pchar.questTemp.officiantLocator = sld.location.locator;
			pchar.questTemp.officiantGroup = sld.location.group;   // запомнить, где была
			PlaceCharacter(sld, "goto", pchar.location);
			sld.dialog.currentnode = "without_money";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "officiant_back_to_citizen", 5.0, 1.0);
			DoQuestCheckDelay("pchar_back_to_player", 6.0);
		break;

		case "officiant_back_to_citizen":
			LAi_SetPlayerType(pchar);
			sld = characterFromID(loadedLocation.fastreload + "_waitress");
			LAi_SetWaitressType(sld);
			sld.location.locator = pchar.questTemp.officiantLocator;
			sld.location.group = pchar.questTemp.officiantGroup;
		break;
		//  агенты стран в таверне -->
		case "NationUpdate":
			UpdateRelations();
			if (bSeaActive)
			{
				RefreshBattleInterface();
			}
		break;

		case "pir_flag_rise":
			Flag_PIRATE();
		break;
		// агенты в тавернах -->
		case "any_patent_take":
			AddMoneyToCharacter(pchar, -sti(pchar.PatentPrice));

			RemovePatent();

			GiveItem2Character(pchar, "patent_" + pchar.PatentNation);
			EquipCharacterbyItem(pchar, "patent_" + pchar.PatentNation);

			Items[sti(pchar.EquipedPatentId)].TitulCur = 1; // текущ звание сбросим
			Items[sti(pchar.EquipedPatentId)].TitulCurNext = 0; // счетчик звание сбросим
		break;

		case "fra_flag_rise":
			Flag_FRANCE();
		break;

		case "eng_flag_rise":
			Flag_ENGLAND();
		break;

		case "spa_flag_rise":
			Flag_SPAIN();
		break;

		case "hol_flag_rise":
			Flag_HOLLAND();
		break;

		case "QuestAboardCabinDialog":  // диалог в абордаже, в каюте при достижении минНР
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)]; // фантом, тень отца капитана
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
		break;

		case "LAi_ReloadBoarding": // задержка нужна
			LAi_EnableReload();
			DelEventHandler("Control Activation", "LAi_ActivateReload");
			Log_SetActiveAction("Nothing");
			LAi_ReloadBoarding();
		break;

		//AlexBlade - реакт для выхода с палубы, чтобы не вызывать "выход в море" через меню команд
		case "Exit_Sea":
			if (!bSeaActive || bAbordageStarted)
			{
				if (isShipInside(pchar.location) || CheckShipSituation_GenQuest())
				{
					Return2SeaAfterCabin();
				}
				else
				{
					int idxLoadLoc = FindLoadedLocation();
					if (idxLoadLoc != -1)
					{
						UnloadLocation(&Locations[idxLoadLoc]);
					}
					wdmReloadToSea();
				}
			}
		break;
		// boal <---

		////////////////////////////////////////////////////////////////////////
		//  Служебный квест контрабандистов - ограничение по времени
		////////////////////////////////////////////////////////////////////////
		case "Rand_Smuggling":
		//слишком падает ChangeContrabandRelation(pchar, -10); // boal
			pchar.quest.KillSmugglers_after.over = "yes";
			RemoveSmugglersFromShore();
		break;

		//Постановка стражников в локацию передачи контрабандистов
		case "Rand_ContrabandInterruption":
			chrDisableReloadToLocation = true;
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			// солдаты в начале
			iTemp = GetCurrentLocationNation();
			if (iTemp == -1)
			{
				iTemp = sti(pchar.GenQuest.Contraband.GuardNation); // Нация патруля
			}
			Pchar.quest.contraband.SoldierQty = makeint(2 * GetOfficersQuantity(Pchar) + 3);
			for (i = 2; i <= sti(Pchar.quest.contraband.SoldierQty); i++)
			{
				sld = SetFantomDefenceLocal("", "", iTemp, "CoastalGuards");
				attrName = "SoldierIDX" + i;
				Pchar.quest.contraband.(attrName) = sld.index;
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, Pchar, "", 38);
				sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
				sld.Dialog.CurrentNode = "First time";
				sld.greeting = "Gr_Costal_Guards";
			}
			// вызовем независимо!!!! не тут SetCoastalGuardPursuit();

			// офицер в конце
			sld = SetFantomOfficer("", "", iTemp, "CoastalGuards");
			Pchar.quest.contraband.SoldierIDX1 = sld.index;
			LAi_SetActorType(sld);
			sld.Dialog.Filename = "Smuggler_Guards_dialog.c";
			sld.Dialog.CurrentNode = "First time";
			sld.greeting = "Gr_Costal_Guards";

			LAi_ActorDialog(&Characters[makeint(Pchar.quest.contraband.SoldierIDX1)], Pchar, "", 35, 1); // boal 120c - озвереть ждать!!!
			LAi_group_SetCheck("CoastalGuards", "CoastalGuardsAllDead");
		break;

		case "Rand_ContrabandInterruptionAtSeaEnded":
			StopCoastalGuardPursuit();

			AddSimpleRumourCity(StringFromKey("Common_rumours_89"), Pchar.quest.contraband.City, 3, 5, "");
		break;

		case "Rand_ContrabandAtSeaEnded":
			StopCoastalGuardPursuit();

			AddSimpleRumourCity(StringFromKey("Common_rumours_89"), Pchar.quest.contraband.City, 3, 5, "");
		break;

		case "CoastalGuardsAllDead":
			for (i = 1; i < 4; i++)
			{
				sTemp = "Rand_Smug0" + i;
				sld = CharacterFromID(sTemp);
				LAi_SetGuardianTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, pchar.GenQuest.Smugglers_Group); // вернём обратно
			}
			LAi_grp_alarmactive = false; // конец тревоги
			TEV.ContrabandMoment.PatrolFight.End = "1";
			chrDisableReloadToLocation = false;
		break;
		//  контрабанды <--

		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - УДАЛЕНИЕ ТЕКУЩЕГО НАПРАВЛЕНИЯ И СИЛЫ ВЕТРА
		/////////////////////////////////////////////////////////////////////////////////
		case "EraseWind":
			DeleteAttribute(pchar, "wind");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - УДАЛЕНИЕ ТЕКУЩЕГО НАПРАВЛЕНИЯ И СИЛЫ ВЕТРА
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// СБРОС СЧЕТЧИКА ДУЭЛЕЙ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////
		case "HabitueSpeakDisable_End":
			DeleteTrait(pchar, "Bully");
			DeleteAttribute(pchar, "questTemp.duelQty");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// СБРОС СЧЕТЧИКА ДУЭЛЕЙ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	СЛУЖЕБНЫЕ ФИЧИ
		/////////////////////////////////////////////////////////////////////////////////
		case "hide_weapon":
			LAi_SetFightMode(pchar, false);
		break;

		case "AnyReloadToLocation":
			int iMonth, iDay, iHour, iMin;

			iMonth = sti(PChar.AutoQuest.delayMonth);
			iDay = sti(PChar.AutoQuest.delayDay);
			iHour = sti(PChar.AutoQuest.delayHour);
			iMin = sti(PChar.AutoQuest.delayMin);

			if (iMonth > 0 || iDay > 0 || iHour > 0 || iMin > 0)
			{
				bQuestCheckProcessFreeze = true;
				WaitDate("", 0, iMonth, iDay, iHour, iMin);
				bQuestCheckProcessFreeze = false;
			}
			DoQuestReloadToLocation(PChar.AutoQuest.idLocation, PChar.AutoQuest.idGroup, PChar.AutoQuest.idLocator, PChar.AutoQuest.questName);
		break;
		/////////////////////////////////////////////////////////////////////////////////
		//	СЛУЖЕБНЫЕ ФИЧИ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	START OF ПГГ
		/////////////////////////////////////////////////////////////////////////////////
		case "PGG_Companion_Leave":
			chrDisableReloadToLocation = true;
			sld = &Characters[sti(pchar.questTemp.PGG_Companion_Leave.index)];
			PlaceCharacter(sld, "goto", "random_must_be_near");

			sld.Dialog.CurrentNode = "companion_leave";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "RemoveCharacterFromLocation":
			sld = CharacterFromID(PChar.questTemp.Chr2Remove);
			ChangeCharacterAddressGroup(sld, "None", "", "");
			LAi_SetImmortal(sld, false);
		break;

		case "PGG_Q1AfterShoreFight":
			PGG_Q1AfterShoreFight();
		break;

		case "PGG_Q1AfterDeckFight":
			PGG_Q1AfterDeckFight();
		break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF ПГГ
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		//	Корсарское метро
		/////////////////////////////////////////////////////////////////////////////////
		case "RemoveTravelSmugglers":
			if (!CheckAttribute(PChar, "GenQuest.contraTravel.PatrolFight")) ChangeContrabandRelation(PChar, -10);
			RemoveSmugglersFromShore();

			if (!CheckAttribute(PChar, "GenQuest.contraTravel.ship"))
			{
				AddQuestRecord("Gen_ContrabandTravel", "3");
				AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("", "а"));
				DeleteAttribute(PChar, "GenQuest.contraTravel");
				CloseQuestHeader("Gen_ContrabandTravel");
			}

			sld = CharacterFromID("Abracham_Gray");
			sld.location.from_sea = "";
		break;

		case "Travel_talkOnDeck":
		//убираем контрабандистов
			RemoveSmugglersFromShore();
			//кинозвезда Абрахам Грей
			sld = CharacterFromID("Abracham_Gray");
			//параметры
			sld.nation = PIRATE;
			Ship_FlagRefresh(PChar); //флаг на лету
			sld.location.from_sea = "";

			LAi_group_MoveCharacter(sld, "TmpEnemy");
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);

			SetActorDialogAny2Pchar("Abracham_Gray", "", 2.0, 0.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(pchar, sld, "", 1.0);
			//компания
			iTemp = 3 + rand(3);
			arrayNPCModelHow = 0;
			for (i = 0; i < iTemp; i++)
			{
				attrName = "goto" + (3 + i);
				sld = SetFantomDefenceLocal("goto", attrName, PIRATE, "TmpEnemy");
				CreateModel(sti(sld.index), "smuggler", MAN);
				SetNPCModelUniq(sld, "smuggler", MAN);
				SetNewModelToChar(sld);
			}
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_ClearAllTargets();
			LAi_SetFightModeForOfficers(false);
		break;

		case "Travel_AfterDeckFight":
			AddQuestRecord("Gen_ContrabandTravel", "5");
			AddQuestUserData("Gen_ContrabandTravel", "sSex", GetSexPhrase("", "а"));
			StartActorSelfDialog("GenTravel_Main");
		break;
		/////////////////////////////////////////////////////////////////////////////////
		//	END OF Корсарское метро
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - ДОСТАВКА ГРУЗА
		/////////////////////////////////////////////////////////////////////////////////
		case "trade_quest_open":
			int iTradeGoods    = sti(pchar.CargoQuest.iTradeGoods);
			int iQuantityGoods = sti(pchar.CargoQuest.iQuantityGoods);
			int iTradeNation   = sti(pchar.CargoQuest.iTradeNation);
			int iMoney         = sti(pchar.CargoQuest.iMoney);
			AddCharacterGoods(pchar, iTradeGoods, iQuantityGoods);
			//задаем квест
			SetTimerCondition("generate_trade_quest", 0, 0, sti(pchar.CargoQuest.iDaysExpired), false);

			pchar.quest.generate_trade_quest_progress = "begin";
			ReOpenQuestHeader("DELIVERY_TRADE_QUEST");
			AddQuestRecord("DELIVERY_TRADE_QUEST", "1");

			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserDataForTitle("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Gen"));

			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sBaseColony", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.CargoQuest.GiveTraderID)].city + "Gen"));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Gen"));
			attrName = "";
			if (pchar.CargoQuest.iTradeIsland != pchar.CargoQuest.iTradeColony)
			{
				attrName = StringFromKey("InfoMessages_6", XI_ConvertString(pchar.CargoQuest.iTradeIsland + "Pre"));
			}
			AddQuestUserData("DELIVERY_TRADE_QUEST", "island", attrName);
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTermsDelivery", FindDaysString(makeint(pchar.CargoQuest.iDaysExpired)));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindMoneyString(iMoney));
			// немного веселой жизни
			TraderHunterOnMap();
		break;

		case "generate_trade_quest":
			if (pchar.quest.generate_trade_quest_progress == "begin")
			{
				pchar.quest.generate_trade_quest_progress = "failed";
				Log_SetStringToLog(StringFromKey("InfoMessages_51"));
				ChangeCharacterReputation(pchar, -10);
				OfficersReaction("bad");
				ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) + "hunter", 15);
				AddQuestRecord("DELIVERY_TRADE_QUEST", "3");
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(sti(pchar.CargoQuest.iTradeGoods)));
				AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Gen"));
			}
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - ДОСТАВКА ГРУЗА
		/////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////
		// НАЧАЛО КВЕСТА - СПИМ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////
		case "sleep_in_tavern":
			if (CheckCharacterPerk(pchar, "WildCaribbean") && CheckAttribute(pchar, "QuestTemp.TakeArmT102") && rand(3) == 1 && !CheckAttribute(pchar, "GenQuest.GhostShip.LastBattleEnd")) // пасхалка
			{
				DeleteAttribute(pchar, "QuestTemp.TakeArmT102");
				PChar.GenQuest.CallFunctionParam = "QuestArmT102";
				DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "CallFunctionParam");
			}
			else
			{
				DoQuestReloadToLocation(pchar.location + "_upstairs", "goto", "goto1", "restore_hp");
			}
		break;

		case "restore_hp":
			int iOfficer;
			LAi_SetCurHPMax(pchar);
			for (i = 1; i < 4; i++)
			{
				if (GetOfficersIndex(Pchar, i) != -1)
				{
					iOfficer = GetOfficersIndex(Pchar, i);
					LAi_SetCurHPMax(&characters[iOfficer]);
				}
			}
			//отдых в таверне или дома восстанавливает здоровье
			RestoreNewDayHealth();
		break;
		/////////////////////////////////////////////////////////////////////////////////
		// КОНЕЦ КВЕСТА - СПИМ В ТАВЕРНЕ
		/////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало    LOAN - ОГРАНИЧЕНИЕ ПО ВРЕМЕНИ
		////////////////////////////////////////////////////////////////////////
		case "LoanFindCitizenTimer": // должник
			Log_SetStringToLog(StringFromKey("InfoMessages_52"));
			LoansMoneyAvengerAmount(&Characters[GetCharacterIndex(pchar.GenQuest.Loan.FindCitizenNpcharId)], MOD_SKILL_ENEMY_RATE + 30);
		//DeleteAttribute(pchar, "GenQuest.Loan");
		break;

		case "LoanChestTimer": // сундук
			Log_SetStringToLog(StringFromKey("InfoMessages_53"));

			// evganat - энциклопедия, изменяем отношение ростовщика
			ref rUsurer;
			makeref(rUsurer, Characters[GetCharacterIndex(pchar.GenQuest.LoanChest.ChestNpcharId)]);
			IncreaseNPCDisposition(rUsurer, -2);

			LoansMoneyAvengerAmount(&Characters[GetCharacterIndex(pchar.GenQuest.LoanChest.ChestNpcharId)], MOD_SKILL_ENEMY_RATE + 15); // кто дал
			LoansMoneyAvengerAmount(&Characters[sti(pchar.GenQuest.LoanChest.TargetIdx)], MOD_SKILL_ENEMY_RATE + 15);// кому везли
			pchar.GenQuest.LoanChest.Money.Discount = (rand(3) + 1) * 10; //процент удержания гонорара за просрочку
			//DeleteAttribute(pchar, "GenQuest.LoanChest");
			AddQuestRecord("Gen_LoanTakeChest", "2");
		//CloseQuestHeader("Gen_LoanTakeChest");
		break;

		case "LoansForAll":
			sTemp = pchar.quest.(qname).CityId;
			LoansMoneyAvenger(&Characters[GetCharacterIndex(sTemp + "_usurer")]);
			Characters[GetCharacterIndex(sTemp + "_usurer")].Dialog.CurrentNode = "DeadMotherfucker";
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    LOAN - ОГРАНИЧЕНИЕ ПО ВРЕМЕНИ
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  НАЧАЛО	ЦЕРКОВНЫЕ КВЕСТЫ
		////////////////////////////////////////////////////////////////////////

		// Остальное на функциях
		case "Church_GenQuest2_AskedBand":
			sQuestTown = PChar.GenQuest.ChurchQuest_2.QuestTown;
			PChar.GenQuest.ChurchQuest_2.AskContra_1 = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "7");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("ёл", "ла"));
			Log_TestInfo("ГГ думает, что на этом острове нужной банды нет.");
		break;

		case "Church_GenQuest2_BanditsIsEnemies":
			sQuestTown = PChar.GenQuest.ChurchQuest_2.QuestTown;
			iCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for (i = 0; i < iCount; i++)
			{
				sld = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetImmortal(sld, false);
				LAi_SetWarriorType(sld);
				LAi_Group_MoveCharacter(sld, "Church_GenQuest2_Bandits_Group");
			}
			LAi_SetFightMode(PChar, true);
			LAi_Group_SetRelation("Church_GenQuest2_Bandits_Group", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("Church_GenQuest2_Bandits_Group", LAI_GROUP_PLAYER, true);
			SetFunctionExitFromLocationCondition("Church_GenQuest2_BanditsIsEnemies_2_Clear", PChar.location, false);
			LAi_Group_SetCheckFunction("Church_GenQuest2_Bandits_Group", "Church_GenQuest2_DeadBandits");
		break;

		////////////////////////////////////////////////////////////////////////
		//  КОНЕЦ	ЦЕРКОВНЫЕ КВЕСТЫ
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало    Сопровождение торговца
		////////////////////////////////////////////////////////////////////////
		case "prepare_for_convoy_quest":
			iTemp = sti(colonies[FindColony(pchar.quest.destination)].nation);
			sld = GetCharacter(NPC_GenerateCharacter("QuestTrader", "", "man", "man", makeint((sti(pchar.rank) + 60) / 4), iTemp, -1, true));
			SetCaptanModelByEncType(sld, "trade");
			sld.reputation = (1 + rand(44) + rand(44));
			sld.Dialog.Filename = "Convoy_Traider.c";
			sld.dialog.currentnode = "prepare_convoy_quest";
			sld.greeting = "tra_quest"; //Gr_ConvoyTrader
			sld.BakNation = sld.nation;
			sld.Abordage.Enable = true;
			sld.CompanionEnemyEnable = true;
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			pchar.quest.generate_convoy_quest_progress = "begin";
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "convoy_refused":
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
			pchar.quest.generate_convoy_quest_timer.over = "yes";
			sld = characterFromID("QuestTrader");
			if (checkquestattribute("generate_convoy_quest_progress", "completed"))
			{
				OfficersReaction("good");
				AddCharacterExpToSkill(pchar, "Sailing", 100);
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "COMMERCE", 5);
				AddQuestRecord("convoy_quest", "4");
				CloseQuestHeader("convoy_quest");
				AddMoneyToCharacter(pchar, sti(pchar.ConvoyQuest.convoymoney));
				ChangeCharacterReputation(pchar, 1);
				RemoveCharacterCompanion(Pchar, sld);
				CloseQuestHeader("convoy_quest");
			}
			pchar.quest.generate_convoy_quest_progress = "";
			LAi_SetActorType(sld);
			LAi_ActorGoToLocatorNoCheck(characterFromID("QuestTrader"), "reload", LocatorToSendConvoyNpc(sld), "TeleportNpcForced", 30.0);
		break;

		case "generate_convoy_quest_timer":
			AddQuestRecord("convoy_quest", "2");
			CloseQuestHeader("convoy_quest");
			sld = characterFromID("QuestTrader");
			ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 5 + rand(10));// награда
			RemoveCharacterCompanion(Pchar, sld);
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -10);
			pchar.quest.generate_convoy_quest_progress = "";
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
		break;

		case "generate_convoy_quest_failed": // торговец умер
			ChangeCharacterReputation(pchar, -5);
			OfficersReaction("bad");
			RemoveCharacterCompanion(Pchar, characterFromID("QuestTrader"));
			pchar.quest.generate_convoy_quest_progress = "";
			pchar.quest.generate_convoy_quest_failed.over = "yes";
			pchar.quest.generate_convoy_quest_completed.over = "yes";
			pchar.quest.generate_convoy_quest_timer.over = "yes";
			AddQuestRecord("convoy_quest", "3");
			CloseQuestHeader("convoy_quest");
		break;

		case "generate_convoy_quest_completed":
			sld = characterFromID("QuestTrader");
			if (IsCompanion(sld))
			{
				sld.greeting = "tra_convoy_complete";
				sld.dialog.currentnode = "complete_convoy_quest";
				PlaceCharacter(sld, "goto", pchar.location);
				Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
				chrDisableReloadToLocation = true;
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else
			{
				ChangeCharacterReputation(pchar, -5);
				ChangeCharacterHunterScore(pchar, NationShortName(sti(sld.BakNation)) + "hunter", 10 + rand(10));// награда
				OfficersReaction("bad");
				pchar.quest.generate_convoy_quest_progress = "";
				pchar.quest.generate_convoy_quest_failed.over = "yes";
				pchar.quest.generate_convoy_quest_completed.over = "yes";
				pchar.quest.generate_convoy_quest_timer.over = "yes";
				AddQuestRecord("convoy_quest", "5");
				CloseQuestHeader("convoy_quest");
			}
		break;

		case "convoy_agreeded":
			sld = characterFromID("QuestTrader");
			sld.ToPointForced = ""; // HardCoffee отправить в локатор без проверки на занятость, чтобы не стояли
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", LocatorToSendConvoyNpc(sld), 5.0, false);
			ReOpenQuestHeader("convoy_quest");
			AddQuestRecord("convoy_quest", "1");
			AddQuestUserData("convoy_quest", "sSex", GetSexPhrase("ся", "ась"));
			sTemp = XI_ConvertString("Colony" + pchar.quest.destination + "Gen") + StringFromKey("InfoMessages_6", XI_ConvertString(GetIslandNameByCity(pchar.quest.destination) + "Pre")) + ",";
			AddQuestUserData("convoy_quest", "sCity", sTemp);
			AddQuestUserData("convoy_quest", "sDay", FindDaysString(sti(pchar.ConvoyQuest.iDay)));
			AddQuestUserData("convoy_quest", "sMoney", FindMoneyString(sti(pchar.ConvoyQuest.convoymoney)));
			// по городу вернём его порт
			attrName = GetPortByCityName(pchar.quest.destination);
			pchar.quest.generate_convoy_quest_completed.win_condition.l1 = "Location";
			pchar.quest.generate_convoy_quest_completed.win_condition.l1.location = attrName;
			pchar.quest.generate_convoy_quest_completed.win_condition = "generate_convoy_quest_completed";
			if (rand(2) == 1) TraderHunterOnMap();
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    Сопровождение торговца
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало    Доставка пассажира
		////////////////////////////////////////////////////////////////////////
		case "prepare_for_passenger_quest":
			iTemp = sti(colonies[FindColony(TEV.GenQuest_DestinationCity)].nation);
			iRank = NPC_GenerateCharacter("QuestPassanger", "", "man", "man", makeint((sti(pchar.rank) + 60) / 4), iTemp, -1, true);
			sld = &characters[iRank];
			sld.id = sld.id + "_" + sld.index; //меняем ID на оригинальный
			sld.reputation = (1 + rand(44) + rand(44));
			SetCaptanModelByEncType(sld, "trade");
			SetRandomNameToCharacter(sld);
			sld.Dialog.Filename = "Convoy_Passenger.c";
			sld.dialog.currentnode = "prepare_convoy_quest";
			sld.greeting = "cit_quest";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
			chrDisableReloadToLocation = true;
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "AllPassangersDead": // торговец умер
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			ChangeCharacterReputation(pchar, -5);
			RemovePassenger(PChar, sld);
			sTemp = sld.id + "_complited";
			pchar.quest.(sTemp).over = "yes";
			sTemp = sld.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			DeleteAttribute(pchar, "GenQuest.ConvoyPassenger." + sld.id); //извлекаем из структуры недовольных
			//--> смотрим Deck
			makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			if (GetAttributesNum(arAll) == 0) pchar.quest.ConvoyMapPassenger.over = "yes";
			//<-- смотрим Deck
			attrName = sld.index + "convoy_passenger";
			AddQuestRecordEx(attrName, "Gen_convoy_passenger", "3");
			CloseQuestHeader(attrName);
		break;

		case "AllPassangersTimeOver":
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			sTemp = sld.id;
			Pchar.GenQuest.ConvoyPassenger.(sTemp) = sld.index; //в структуру недовольных
			if (!CheckAttribute(Pchar, "quest.ConvoyMapPassenger"))
			{
				Pchar.quest.ConvoyMapPassenger.win_condition.l1 = "MapEnter";
				Pchar.quest.ConvoyMapPassenger.win_condition = "AllPassengerDeck";
			}
		break;

		case "AllPassengerDeck": // разговор на палубе
			MakeCloneShipDeck(pchar, true); // подмена палубы
			makearef(arAll, pchar.GenQuest.ConvoyPassenger);
			iTemp = GetAttributesNum(arAll);
			for (i = 0; i < iTemp; i++)
			{
				arPass = GetAttributeN(arAll, i);
				sld = &characters[sti(arPass)];
				ChangeCharacterAddress(sld, "Ship_deck", "goto4");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			makearef(arOldMapPos, worldMap.old);
			WdmPrepareMapForAbordage(arOldMapPos);
			DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
			ReloadFromWMtoL_complete();
			pchar.quest.Munity = "";  // признак выхода с палубы
			LAi_LockFightMode(Pchar, true);
		break;

		case "AllPassangersComplited":
			sld = &characters[sti(pchar.quest.(qname).Idx)];
			sTemp = sld.id + "_TimeOver";
			pchar.quest.(sTemp).over = "yes";
			sTemp = sld.id + "_dead";
			pchar.quest.(sTemp).over = "yes";
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу
			chrDisableReloadToLocation = true;
			sld.greeting = "cit_complete";
			sld.dialog.currentnode = "complete_convoy_quest";
			PlaceCharacter(sld, "goto", "random_must_be");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    Доставка пассажира
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало   Ланд энкаунтеры
		////////////////////////////////////////////////////////////////////////
		//------------------- банда грабителей -------------------------
		case "LandEnc_RaidersBegin":
			FightDisable_Forced();
			LAi_LockFightMode(pchar, true);
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "Gang" + pchar.quest.(qname).LocIdx + "_";
			sld = characterFromId(sTemp + "0");
			fTemp = (stf(locations[reload_location_index].locators_radius.encdetector) - 3) / 5;
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", fTemp, 0);
			for (i = 1; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				if (sld.id != "none")
				{
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorFollow(sld, pchar, "", -1);
				}
			}
		break;

		case "LandEnc_RaidersBeforeDialog": //если выстрел до диалога
			attrName = locations[reload_location_index].index;
			sTemp = "EncRaiders_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			Model = "RaidersGroup_" + attrName; //имя группы
			sTemp = "Gang" + attrName + "_";
			for (i = 0; i < 4; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);
				//LAi_group_MoveCharacter(sld, Model);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(Model, "LandEnc_RaidersAfrer");
		break;

		case "LandEnc_RaidersAfrer": //чистим за собой
			attrName = locations[reload_location_index].index;
			locations[sti(attrName)].bonfire = false;
			sTemp = "TimeRaiders_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			sTemp = "RaidersGroup_" + attrName;
			Delay_DeleteGroup(sTemp);
			Gun = "Raiders_" + attrName;
			AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_91", GetFullName(pchar), pchar.GenQuest.(Gun).name), StringFromKey("Common_rumours_92", GetFullName(pchar), pchar.GenQuest.(Gun).name), StringFromKey("Common_rumours_93", pchar.GenQuest.(Gun).name, GetFullName(pchar))), sti(pchar.GenQuest.(Gun).nation), 5, 1);
			DeleteAttribute(pchar, "GenQuest." + Gun); //трем нацию и имя
		break;

		case "LandEnc_RaidersOver": //чистим за собой
			attrName = pchar.quest.(qname).LocIdx;
			locations[sti(attrName)].bonfire = false;
			pchar.quest.(qname).over = "yes";
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "EncRaiders_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			sTemp = "Gang" + attrName + "_";
			for (i = 0; i < iTemp; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				LAi_RemoveCheckMinHP(CharacterFromID(sTemp + i));
			}
			sTemp = "RaidersGroup_" + attrName;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			DeleteAttribute(pchar, "GenQuest." + attrName); //трем нацию и имя
		break;

		//------------------- злые карибы -------------------------
		case "LandEnc_CaribBeforeDialog": //если выстрел до диалога - нападение
			attrName = locations[reload_location_index].index;
			sTemp = "EncCarib_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			Model = "CaribGroup_" + attrName; //имя группы
			sTemp = "Carib" + attrName + "_";
			for (i = 0; i < 4; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(Model, "LandEnc_CaribAfrer");
		break;

		case "LandEnc_MiskitoBeforeDialog": //если выстрел до диалога - бегство
			attrName = locations[reload_location_index].index;
			sTemp = "EncCarib_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			Model = "CaribGroup_" + attrName; //имя группы
			sTemp = "Carib" + attrName + "_";
			for (i = 0; i < 4; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetActorType(sld);
				LAi_SetImmortal(sld, false);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
			}
			DoQuestCheckDelay("LandEnc_CaribAfrer", 10.0);
			//А тут защита, если за 10 секунд игрок успеет сменить локацию
			PChar.quest.LandEnc_CaribAfrer_Exit.win_condition.l1 = "ExitFromLocation";
			PChar.quest.LandEnc_CaribAfrer_Exit.win_condition.l1.location = PChar.location;
			PChar.quest.LandEnc_CaribAfrer_Exit.win_condition = "LandEnc_CaribAfrer_Exit";
			PChar.quest.LandEnc_CaribAfrer_Exit.LocIdx = attrName;
			chrDisableReloadToLocation = false;
		break;

		case "LandEnc_CaribBegin":
			chrDisableReloadToLocation = true;
			FightDisable_Forced();
			LAi_LockFightMode(pchar, true);
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "Carib" + pchar.quest.(qname).LocIdx + "_";
			sld = characterFromId(sTemp + "0");
			fTemp = (stf(locations[reload_location_index].locators_radius.encdetector) - 3) / 5;
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", fTemp, 0);
			for (i = 1; i < iTemp; i++)
			{
				sld = CharacterFromID(sTemp + i);
				if (sld.id != "none")
				{
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorFollow(sld, pchar, "", -1);
				}
			}
		break;

		case "LandEnc_CaribAfrer": //чистим за собой
			attrName = locations[reload_location_index].index;
			locations[sti(attrName)].bonfire = false;
			sTemp = "TimeCarib_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			pchar.quest.LandEnc_CaribAfrer_Exit.over = "yes"; //снимаем защитное прерывание
			sTemp = "CaribGroup_" + attrName;
			Delay_DeleteGroup(sTemp);
		break;

		case "LandEnc_CaribAfrer_Exit":
			attrName = pchar.quest.(qname).LocIdx;
			locations[sti(attrName)].bonfire = false;
			sTemp = "TimeCarib_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			sTemp = "CaribGroup_" + attrName;
			Delay_DeleteGroup(sTemp);
		break;

		case "LandEnc_CaribOver": //чистим за собой
			attrName = pchar.quest.(qname).LocIdx;
			locations[sti(attrName)].bonfire = false;
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "Carib" + attrName + "_";
			for (i = 0; i < iTemp; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				LAi_RemoveCheckMinHP(CharacterFromID(sTemp + i));
			}
			sTemp = "CaribGroup_" + attrName;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			pchar.quest.(qname).over = "yes";
			sTemp = "EncCarib_" + attrName;
			pchar.quest.(sTemp).over = "yes";
		break;

		//------------------- девка в джунлях -------------------------
		case "LandEnc_RapersTalk":
			for (i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
		break;

		case "LandEnc_RapersBeforeDialog": //если выстрел до диалога
			if (GetCharacterIndex("CangGirl") != -1) LAi_RemoveCheckMinHP(CharacterFromID("CangGirl"));
			for (i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("GangMan_" + i) == -1) continue;
				sld = CharacterFromID("GangMan_" + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			//			LAi_group_SetCheck("EnemyFight", "LandEnc_RapersAfrer");
			sld = CharacterFromID("CangGirl");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, true);
		break;

		case "LandEnc_RapersAfrer": // грохнули бандюков
			pchar.GenQuest.EncGirl.Saved_CangGirl = true;
			sld = CharacterFromID("CangGirl");
			sld.greeting = "Enc_RapersGirl_2";
			sld.dialog.currentnode = "ThanksForHelp";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "LandEnc_RapersBadExit":
			iTemp = GetCharacterIndex("CangGirl");
			if (iTemp < 0) // если ГГ собственноручно прибил тетку
			{
				ChangeCharacterReputation(pchar, -5);
				AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_94", pchar.GenQuest.EncGirl.name),
						StringFromKey("Common_rumours_95", GetFullName(pchar), pchar.GenQuest.EncGirl.name),
						StringFromKey("Common_rumours_96", pchar.GenQuest.EncGirl.name)), sti(pchar.GenQuest.EncGirl.nation), 5, 1);
			}
			else if (CheckAttribute(pchar, "GenQuest.EncGirl.Saved_CangGirl")) // спасли тетку
			{
				if (pchar.GenQuest.EncGirl == "close") //... и послали её куда подальше
				{

				}
				else if (!CheckAttribute(pchar, "GenQuest.EncGirl.Ransom"))
				{
					ChangeCharacterReputation(pchar, 5);
					AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_97", pchar.GenQuest.EncGirl.name),
							StringFromKey("Common_rumours_98", GetFullName(pchar), pchar.GenQuest.EncGirl.name),
							StringFromKey("Common_rumours_99", pchar.GenQuest.EncGirl.name, GetMainCharacterNameGen())), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
				}
			}
			else // оставил на растерзание бандитам
			{
				if (pchar.GenQuest.EncGirl == "Begin_11")
				{
					ChangeCharacterReputation(pchar, -8);
				}
				else if (pchar.GenQuest.EncGirl == "Begin_22")
				{
					ChangeCharacterReputation(pchar, -8);
				}
				else if (pchar.GenQuest.EncGirl == "Begin_33")
				{
					ChangeCharacterReputation(pchar, -5);
				}
				AddSimpleRumour(RandPhraseSimple(StringFromKey("Common_rumours_100", GetFullName(pchar), pchar.GenQuest.EncGirl.name),
						StringFromKey("Common_rumours_101", pchar.GenQuest.EncGirl.name)), sti(pchar.GenQuest.EncGirl.nation), 5, 1);

			}

			if (iTemp > -1 ) characters[iTemp].lifeDay = "0";

			for (i = 1; i <= 3; i++)
			{
				iTemp = GetCharacterIndex("GangMan_" + i);
				if (iTemp < 0) continue;
				sld = &characters[iTemp];
				LAi_RemoveCheckMinHP(sld);
				sld.lifeDay = "0";
			}

			DeleteAttribute(pchar, "GenQuest.EncGirl"); //трем нацию и имя
			if (CheckAttribute(pchar, "quest.LandEnc_RapersBadExit"))
			{
				pchar.quest.LandEnc_RapersBadExit.over = "yes";
			}
		break;

		case "EncGirl_Massacre": //Rosarak. Прерывание за резню (beta)
			if (pchar.GenQuest.EncGirl == "GetChest")
			{
				AddQuestRecord("JungleGirl", "28");
				AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
				CloseQuestHeader("JungleGirl");
			}
			if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
			{
				sld = characterFromId("CangGirl");
				sTemp = XI_ConvertString("people" + GetNationNameByType(sti(sld.nation)) + "Ins");
				AddQuestRecord("JungleGirl", "29");
				AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
				AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ся", "ась"));
				AddQuestUserData("JungleGirl", "sNation", sTemp);
				CloseQuestHeader("JungleGirl");
			}
			//--> Снимаем все прерывания
			makearef(arPass, pchar.quest);
			iTemp = GetAttributesNum(arPass);
			for (i = 0; i < iTemp; i++)
			{
				sTemp = GetAttributeName(GetAttributeN(arPass, i));
				if (HasSubStr(sTemp, "EncGirl"))
					pchar.quest.(sTemp).over = "yes";
			}
			//<-- Снимаем все прерывания
			LAi_group_Delete("DeliveQuest_Girl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;

		case "EncGirl_Kick": //Rosarak. Прерывание за битьё (beta)
			ChangeCharacterReputation(pchar, -3);
			if (pchar.GenQuest.EncGirl == "GetChest")
			{
				AddQuestRecord("JungleGirl", "30");
				AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
				AddQuestUserData("JungleGirl", "sPirate", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
				CloseQuestHeader("JungleGirl");
			}
			if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
			{
				AddQuestRecord("JungleGirl", "31");
				CloseQuestHeader("JungleGirl");
			}
			//--> Снимаем все прерывания
			makearef(arPass, pchar.quest);
			iTemp = GetAttributesNum(arPass);
			for (i = 0; i < iTemp; i++)
			{
				sTemp = GetAttributeName(GetAttributeN(arPass, i));
				if (HasSubStr(sTemp, "EncGirl"))
					pchar.quest.(sTemp).over = "yes";
			}
			//<-- Снимаем все прерывания
			LAi_group_Delete("DeliveQuest_Girl");
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;

		//------------------- девка просит помочь подруге -------------------------
		case "Enc_FriendGirl_after": //если выстрел до диалога
			ChangeCharacterReputation(pchar, -(rand(4) + 1));
			if (rand(1))
			{
				AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_102", pchar.GenQuest.EncGirl.name),
						StringFromKey("Common_rumours_103", GetFullName(pchar), pchar.GenQuest.EncGirl.name),
						StringFromKey("Common_rumours_104", pchar.GenQuest.EncGirl.name)), sti(pchar.GenQuest.EncGirl.nation), 5, 1);
			}
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;

		case "Enc_FriendGirl_afterGang":
			DeleteAttribute(pchar, "GenQuest.EncGirl");
		break;

		//------------------- патруль в джунглях -------------------------
		case "LandEnc_PatrolBegin":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
			iTemp = sti(pchar.quest.(qname).EncQty);
			sTemp = "Patrol" + pchar.quest.(qname).LocIdx + "_";
			npchar = characterFromId(sTemp + "0");
			fTemp = (stf(locations[reload_location_index].locators_radius.encdetector) - 3) / 5;
			LAi_SetActorTypeNoGroup(npchar);
			LAi_ActorDialog(npchar, pchar, "", fTemp, 0);
			for (i = 1; i < iTemp; i++)
			{
				sld = characterFromId(sTemp + i);
				LAi_SetActorType(sld);
				LAi_ActorFollow(sld, npchar, "", -1);
			}
		break;

		case "LandEnc_PatrolBeforeDialog": //если выстрел до диалога
			attrName = locations[reload_location_index].index;
			sTemp = "EncPatrol_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			Model = "PatrolGroup_" + attrName; //имя группы
			sTemp = "Patrol" + attrName + "_";
			for (i = 0; i < 4; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			LAi_group_SetRelation(Model, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(Model, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(Model, "LandEnc_PatrolAfrer");
		break;

		case "LandEnc_PatrolAfrer": //чистим за собой
			attrName = locations[reload_location_index].index;
			sTemp = "TimePatrol_" + attrName;
			pchar.quest.(sTemp).over = "yes";
			sTemp = "PatrolGroup_" + attrName;
			Delay_DeleteGroup(sTemp);
			//слухи
			AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_105"),
					StringFromKey("Common_rumours_106"),
					StringFromKey("Common_rumours_107")), sti(pchar.GenQuest.(attrName).nation), 5, 1);
			AddSimpleRumour(StringFromKey("Common_rumours_108", GetFullName(pchar), NationNameGenitive(sti(pchar.GenQuest.(attrName).nation)), NationNamePeople(sti(pchar.GenQuest.(attrName).nation))), sti(pchar.GenQuest.(attrName).nation) + 10, 5, 1);
			DeleteAttribute(pchar, "GenQuest." + attrName); //трем нацию патруля, если есть
		break;

		case "LandEnc_PatrolOver": //чистим за собой
			sTemp = pchar.quest.(qname).LocIdx;
			//слухи
			AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_109", GetMainCharacterNameGen()),
					StringFromKey("Common_rumours_110"),
					StringFromKey("Common_rumours_111")), sti(pchar.GenQuest.(sTemp).nation), 5, 1);
			DeleteAttribute(pchar, "GenQuest." + sTemp); //трем нацию патруля, если есть
			sTemp = "PatrolGroup_" + pchar.quest.(qname).LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			pchar.quest.(qname).over = "yes";
			sTemp = "EncPatrol_" + pchar.quest.(qname).LocIdx;
			pchar.quest.(sTemp).over = "yes";
		break;

		case "DeleteGroupOnExitLocation": //группу нулим
			sTemp = pchar.quest.DeleteGroupOnExitLocation.GroupName;
			LAi_group_Delete(sTemp);
		break;

		//------------------- праздношатающиеся перцы -------------------------
		case "EncWalker_Rumours":
			PChar.quest.EncWalker_Over.over = "yes";
			if (rand(1))
			{
				switch (rand(2))
				{
					case 0:
						if (pchar.GenQuest.EncWalker == "man")
							sTemp = StringFromKey("Rumour_Data_111");
						else
							sTemp = StringFromKey("Rumour_Data_112");
					break;
					case 1:
						if (pchar.GenQuest.EncWalker == "man")
							sTemp = StringFromKey("Rumour_Data_113");
						else
							sTemp = StringFromKey("Rumour_Data_114", pchar.GenQuest.EncWalker.Name);
					break;
					case 2:
						if (pchar.GenQuest.EncWalker == "man")
							sTemp = StringFromKey("Rumour_Data_115", pchar.GenQuest.EncWalker.Name);
						else
							sTemp = StringFromKey("Rumour_Data_116", pchar.GenQuest.EncWalker.Name);
					break;
				}
				AddSimpleRumourCity(sTemp, pchar.GenQuest.EncWalker.City, 5, 1, "");
				//Для цикла, если будет -->
				//iTemp = FindRumour(AddSimpleRumourCity(sTemp, pchar.GenQuest.EncWalker.City, 5, 1, ""));
				//Rumour[iTemp].group = "EncWalkerDead_" + pchar.GenQuest.EncWalker.City;
			}
			DeleteAttribute(pchar, "GenQuest.EncWalker");
		break;

		case "EncWalker_Over":
			DeleteAttribute(pchar, "GenQuest.EncWalker");
			LAi_group_RemoveCheck("LandEncGroup");
		break;

		//------------------- Правосудие на продажу -------------------------
		// Агрим контриков, чтоб не шатались рядом, пока своих бьют
		case "JusticeOnSale_BeforeDialog":
			ChangeContrabandRelation(pchar, -5);
			attrName = "JusticeOnSaleGroup_" + PChar.GenQuest.JusticeOnSale.LocIdx;
			sTemp = "JusticeOnSale_Jungle_";
			for (i = 0; i < 4; i++)
			{
				if (GetCharacterIndex(sTemp + i) == -1) continue;
				sld = CharacterFromID(sTemp + i);
				LAi_RemoveCheckMinHP(sld);
				DelLandQuestMark(sld);
			}
			LAi_group_SetRelation(attrName, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(attrName, LAI_GROUP_PLAYER, true);
			//Конец квеста
			if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait"))
			{
				JusticeOnSale_DeleteCaptain();
				JusticeOnSale_DeleteShip();
				CloseQuestHeader("JusticeOnSale");
				AddQuestRecord("JusticeOnSale", "1_1");
				AddQuestUserData("JusticeOnSale", "sSex", GetSexPhrase("", "а"));
				DeleteQuestCondition("JusticeOnSale_Over");
				DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
			}
		break;

		case "JusticeOnSale_CaptainEscape_Done":
			JusticeOnSale_DeleteCaptain();
			DeleteQuestCondition("JusticeOnSale_CaptainEscape_Fail");
			Log_Info(StringFromKey("InfoMessages_54", XI_ConvertString("Captain"), PChar.GenQuest.JusticeOnSale.SmugglerName));
			AddQuestRecord("JusticeOnSale", "3");

			//Даём 2 дня
			PChar.Quest.JusticeOnSale_Over.win_condition.l1 = "Timer";
			PChar.Quest.JusticeOnSale_Over.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			PChar.Quest.JusticeOnSale_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			PChar.Quest.JusticeOnSale_Over.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			PChar.Quest.JusticeOnSale_Over.function = "JusticeOnSale_Over";

			//Помог сбежать - репа в плюс
			ChangeContrabandRelation(pchar, 20);
			AddCharacterExpToSkill(PChar, "Sneak", 100);
		break;

		////////////////////////////////////////////////////////////////////////
		//  Конец   Ланд энкаунтеры
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало    Уничтожение банды
		////////////////////////////////////////////////////////////////////////
		case "AllMayorsQuests_Late": //провальное прерывание на все квесты мэра
			sTemp = pchar.GenQuest.questName;
			pchar.quest.(sTemp).over = "yes"; //снимаем прерывание на квест
			pchar.GenQuest.(sTemp) = "Late"; //флаг опоздал
			npchar = characterFromId(pchar.GenQuest.(sTemp).MayorId);
			AddQuestRecord("MayorsQuestsList", "20");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			//снимаем кораблики пирата и торговцев
			if (sTemp == "DestroyPirate")
			{
				Group_DeleteGroup("MQGroupPirate");
				LAi_group_Delete("MayorPirateGroup");
				for (i = 0; i < 5; i++)
				{
					Group_DeleteGroup("MQGroupAll_" + i);
				}
			}
		break;

		case "DestroyGang_fight":
			if (rand(1))
			{
				chrDisableReloadToLocation = true;
				Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
				sTemp = pchar.GenQuest.questName;
				pchar.quest.(sTemp).over = "yes"; //снимаем текущее многоразовое прерывание
				ref location = &locations[reload_location_index];
				LAi_LocationFightDisable(location, true);      //лочим возможность начать драку до диалог, это лишнее
				string encGroup = LAi_FindRandomLocator("encdetector");
				sTemp = "locators." + encGroup;
				makearef(arAll, location.(sTemp));
				iTemp = GetAttributesNum(arAll); //кол-во человек в банде
				if (iTemp <= 0) iTemp = 1; //если локаторов меньше четырёх
				//--> генерим ранг
				if (sti(pchar.rank) > 6 || MOD_SKILL_ENEMY_RATE > 7)
				{
					if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE * 4 / iTemp);
					else iRank = sti(pchar.rank) + sti(MOD_SKILL_ENEMY_RATE * 2.5 / iTemp);
				}
				else
				{
					//казуалам зелёный свет на начало игры
					if (sti(pchar.rank) > 3) iRank = sti(pchar.rank);
					else
					{
						iRank = 1;
						iTemp = 1;
					}
				}
				//<-- генерим ранг
				i = 0;
				arrayNPCModelHow = 0;
				int iMainGang;
				while (i < iTemp)
				{
					if (i == 0)
					{
						//главарь банды
						iMainGang = NPC_GenerateCharacter("MayorQuestGang_" + i, "pirate_" + (rand(15) + 1), "man", "man", iRank, PIRATE, 0, true);
						//watch_quest_moment; не стал ему менять стек на охрану, чтобы была аналогия с простыми генераторными бандами, да и не кулфайтер он; мб сделать?
						sld = &characters[iMainGang];
						sld.name = pchar.GenQuest.DestroyGang.name;  //имя главаря
						sld.lastname = pchar.GenQuest.DestroyGang.lastname;
						sld.dialog.filename = "MayorQuests_dialog.c";
						sld.dialog.currentnode = "DestroyGang_begin";
						sld.greeting = "Enc_Raiders";
						sld.SaveItemsForDead = true; // сохранять на трупе вещи
						sld.DontClearDead = true;  // не убирать труп через 200с
						// evganat - энциклопедия
						if (CheckRandomPage("questjungle", "mayorquest", -1))
						{
							sld.encyclopedia.tome = GetRandomTome();
							sld.encyclopedia.page = 5;
						}
					}
					else sld = GetCharacter(NPC_GenerateCharacter("MayorQuestGang_" + i, "pirate_" + (rand(15) + 1), "man", "man", iRank, PIRATE, 0, true));
					SetNPCModelUniq(sld, "pirate", MAN);
					LAi_SetActorType(sld);
					SetFantomParamFromRank(sld, iRank, true);
					//Получим локатор для логина
					attrName = GetAttributeName(GetAttributeN(arAll, i));
					ChangeCharacterAddressGroup(sld, location.id, encGroup, attrName);
					LAi_SetActorType(sld);
					if (i == 0) LAi_ActorDialog(sld, pchar, "", -1, 0);
					else LAi_ActorFollow(sld, &characters[iMainGang], "", -1);
					i++;
				}
			}
		break;

		case "DestroyGang_SuddenAttack":
			for (i = 0; i < 4; i++)
			{
				if (GetCharacterIndex("MayorQuestGang_" + i) == -1) continue;
				sld = CharacterFromID("MayorQuestGang_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "DestroyGang");
				LAi_SetImmortal(sld, false);
			}
			LAi_group_SetRelation("DestroyGang", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("DestroyGang", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("DestroyGang", "DestroyGang_After");
		break;

		case "DestroyGang_After":
			pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
			makearef(arAll, pchar.GenQuest.DestroyGang);
			pchar.GenQuest.DestroyGang = "Execute"; //флаг выполнил успешно
			sTemp = GetFullName(&characters[GetCharacterIndex(arAll.MayorId)]);
			// судовой журнал
			AddQuestRecord("MayorsQuestsList", "2");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)].city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
			AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arAll));
			// слухи
			AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_112", sTemp, GetMainCharacterNameDat(), GetFullName(arAll)),
					StringFromKey("Common_rumours_113", GetFullName(arAll)),
					StringFromKey("Common_rumours_114", GetMainCharacterNameDat(), GetFullName(arAll))), sti(characters[GetCharacterIndex(arAll.MayorId)].nation), 5, 1);
			LAi_group_Delete("DestroyGang");
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    Уничтожение банды
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало    Поиск лазутчика в городе
		////////////////////////////////////////////////////////////////////////
		case "SeekSpy_login":
			if (CheckAttribute(pchar, "GenQuest.SeekSpy.City"))
			{
				//шпион на улице
				sTemp = pchar.GenQuest.questName;
				pchar.quest.(sTemp).over = "yes"; //снимаем текущее многоразовое прерывание
				sld = GetCharacter(NPC_GenerateCharacter("MayorQuestSpy", RandCitizenModel(), "man", "man", iRank, PIRATE, sti(pchar.GenQuest.SeekSpy.Terms), false)); //watch_quest_moment
				sld.dialog.filename = "MayorQuests_dialog.c";
				sld.dialog.currentnode = "SeekSpy_street";
				sld.city = characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city;
				sld.greeting = "cit_common";
				LAi_SetLoginTime(sld, 6.0, 21.99);
				//SetFantomParamFromRank(sld, Rank, true);
				LAi_SetCitizenType(sld);
				iTemp = sti(characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].nation);
				sTemp = GetNationNameByType(iTemp) + "_citizens";
				LAi_group_MoveCharacter(sld, sTemp);
				PlaceCharacter(sld, "goto", "random_must_be");
			}
			else
			{
				//шпион в коммонах
				iTemp = reload_location_index;
				if (locations[iTemp].fastreload == characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city)
				{
					chrDisableReloadToLocation = true;
					sTemp = pchar.GenQuest.questName;
					pchar.quest.(sTemp).over = "yes"; //снимаем текущее прерывание
					pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
					//--> генерим ранг
					if (sti(pchar.rank) > 6)
					{
						if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 5;
						else iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
					}
					else
					{
						//казуалам зелёный свет на начало игры
						if (sti(pchar.rank) > 3) iRank = sti(pchar.rank);
						else
						{
							iRank = 1;
							if (iTemp > 2) iTemp = 2;
						}
					}
					//<-- генерим ранг
					sld = GetCharacter(NPC_GenerateCharacter("MayorQuestSpy", "citiz_" + (rand(9) + 11), "man", "man", iRank, PIRATE, 0, true)); //TODO: согласовать шпиона с типами домов в будущем
					sld.dialog.filename = "MayorQuests_dialog.c";
					sld.dialog.currentnode = "SeekSpy_house";
					sld.greeting = "cit_common";
					SetFantomParamFromRank(sld, iRank, true);
					PlaceCharacter(sld, "goto", "random");
					LAi_SetCitizenType(sld);
					//LAi_ActorDialog(sld, pchar, "", -1, 0);
				}
			}
		break;

		case "SeekSpy_After":
			pchar.GenQuest.SeekSpy = "Execute"; //флаг выполнил успешно
			sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)]);
			// судовой журнал
			AddQuestRecord("MayorsQuestsList", "4");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.SeekSpy.MayorId)].city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
			// слухи
			AddSimpleRumour(RandPhraseSimple(StringFromKey("Common_rumours_115", sTemp, GetMainCharacterNameDat()),
					StringFromKey("Common_rumours_116", GetMainCharacterNameDat())), sti(characters[sti(pchar.GenQuest.SeekSpy.MayorId)].nation), 5, 1);
			LAi_group_Delete("SeekSpy");
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    Поиск лазутчика в городе
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало    Повод для спешки
		////////////////////////////////////////////////////////////////////////

		case "ReasonToFast_PatrolDied":
			sTemp = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_group_RemoveCheck(sTemp);
			LAi_group_Delete(sTemp);
			if (pchar.questTemp.ReasonToFast == "PatrolAfterHunter")
			{
				AddQuestRecord("ReasonToFast", "6");
				AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("", "а"));
			}
			if (pchar.questTemp.ReasonToFast == "PatrolAfter")
			{
				AddQuestRecord("ReasonToFast", "8");
			}
			if (pchar.questTemp.ReasonToFast == "PatrolAngry")
			{
				AddQuestRecord("ReasonToFast", "4");
			}
			DeleteAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther"); //можем говорить с губером

			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1 = "Timer";
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.ReasonToFast_SpeakMayor.function = "ReasonToFast_SpeakMayor";

			DeleteAttribute(&Locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], "DisableEncounters");
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), sti(pchar.questTemp.ReasonToFast.relation));
			pchar.questTemp.ReasonToFast = "PatrolDied";
			pchar.questTemp.ReasonToFast.speakAfterPatrolDied = false;
			DeleteAttribute(pchar, "GenQuest.HunterScore2Pause"); //вертаем начисление нзг
			DeleteAttribute(pchar, "GenQuest.ReputationNotChange"); //вертаем смену репы
		break;

		case "ReasonToFast_MeetHunter":
			ReasonToFast_GenerateHunter();
		break;

		case "ReasonToFast_PatrolAngry":
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sld = CharacterFromID(sTemp + "0");
			sld.dialog.filename = "Encounters\Patrol.c";
			sld.dialog.currentnode = "Reason_To_Fast_AfterHunter3";
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, sld);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
		break;

		case "ReasonToFast_HunterGoOut":
			sld = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1);
			sld.LifeDay = 0;
			pchar.questTemp.ReasonToFast = "MeetHunterSuccess";

			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sld = CharacterFromID(sTemp + "0");
			sld.dialog.filename = "Encounters\Patrol.c";
			sld.dialog.currentnode = "Reason_To_Fast_AfterHunter1";
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, sld);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 1.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", -1);
		break;

		case "ReasonToFast_MeetWithSailor":
			Sea_DeckBoatStartNow(pchar);
		break;

		case "ReasonToFast_ClearVictim":
			pchar.quest.ReasonToFast_SetShip_1.over = "yes";
			pchar.quest.ReasonToFast_SetShip_2.over = "yes";
			sld = characterFromId("VictimCap_1");
			sld.lifeDay = 0;
			Group_DeleteGroup("Sea_Victim_1");
			AddQuestRecord("ReasonToFast", "19");
			AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
		break;

		case "ReasonToFast_TrHuntersDied":
			LAi_group_RemoveCheck("LAND_HUNTER");
			LAi_group_Delete("LAND_HUNTER");
			bDisableLandEncounters = false;
			if (pchar.questTemp.ReasonToFast == "GetMap")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", XI_ConvertString("RewardMap"));
			}
			if (pchar.questTemp.ReasonToFast == "LakeyExitSuccess")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", XI_ConvertString("RewardAsset"));
			}
			if (pchar.questTemp.ReasonToFast == "LakeyExitFail")
			{
				AddQuestRecord("ReasonToFast", "21");
				AddQuestUserData("ReasonToFast", "sName", GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_NOM));
				AddQuestUserData("ReasonToFast", "sText", XI_ConvertString("RewardMoney"));
			}
			if (pchar.questTemp.ReasonToFast == "GetTreasure")
			{
				AddQuestRecord("ReasonToFast", "23");
				AddQuestUserData("ReasonToFast", "sName", GetName(pchar.questTemp.ReasonToFast.mapIdx, pchar.questTemp.ReasonToFast.map, NAME_GEN));
				CloseQuestHeader("ReasonToFast");
				DeleteAttribute(pchar, "questTemp.ReasonToFast");
			}
		break;

		case "ReasonToFast_LakeyGoOut":
			sld = CharacterFromID("ReasonToFastLakey_1");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			sld.LifeDay = 0;
		break;

		case "ReasonToFast_GoAway_Hunters_Land":
			DoQuestCheckDelay("OpenTheDoors", 4.0);
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			for (i = 1; i <= sti(pchar.HunterCost.Qty); i++)
			{
				sld = characterFromID("LandHunter0" + i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "", 4.0);
				iTemp = GetCharacterIndex("LandHunter0" + i);
				if (iTemp != -1)
				{
					characters[iTemp].lifeDay = 0;
				}
			}
			pchar.quest.ReasonToFast_SetHunterPort_1.over = "yes";
			pchar.quest.ReasonToFast_SetHunterPort_2.over = "yes";
			bDisableLandEncounters = false;
			DeleteAttribute(pchar, "questTemp.ReasonToFast");
		break;

		////////////////////////////////////////////////////////////////////////
		//  Конец    Повод для спешки
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало    Уничтожение контры
		////////////////////////////////////////////////////////////////////////
		case "KillSmugglers_after":
			if (CheckAttribute(pchar, "GenQuest.KillSmugglers") && pchar.GenQuest.KillSmugglers.Areal == GetArealByLocation(&locations[reload_location_index]))
			{
				pchar.GenQuest.KillSmugglers = "Execute"; //флаг выполнил успешно
				pchar.quest.AllMayorsQuests_Late.over = "yes"; //снимаем общий таймер
				ChangeContrabandRelation(pchar, -30); //репу контры вниз
				Pchar.quest.Contraband.over = "yes";
				CloseQuestHeader("Gen_Contraband");
				pchar.GenQuest.KillSmugglers.shoreId = pchar.location; //бухту запомним, чисто понты
				sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)]);
				ReOpenQuestHeader("MayorsQuestsList");
				AddQuestRecord("MayorsQuestsList", "9");
				AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.KillSmugglers.MayorId)].city + "Gen"));
				AddQuestUserData("MayorsQuestsList", "MayorName", sTemp);
				// слухи
				AddSimpleRumour(RandPhraseSimple(StringFromKey("Common_rumours_117", sTemp, GetMainCharacterNameDat()),
						StringFromKey("Common_rumours_118", sTemp, GetMainCharacterNameDat())), sti(characters[sti(pchar.GenQuest.KillSmugglers.MayorId)].nation), 5, 1);
			}
		break;

		case "KillSmugglers_outShore":
			pchar.quest.KillSmugglers.over = "yes"; //снимаем текущее прерывание
			DeleteAttribute(&TEV, "ContrabandMoment");
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    Уничтожение контры
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало    Поиск и уничтожение пирата
		////////////////////////////////////////////////////////////////////////
		case "DestroyPirate_Begin":
			npchar = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
			int islandIdx = FindIsland(pchar.GenQuest.DestroyPirate.Areal);
			aref arQuestLoc, arPlTarget, arLocator;
			makearef(arPlTarget, Islands[islandIdx].reload);
			string locatorName, captainId, GroupName;
			//--> генерим ранг
			if (sti(pchar.rank) > 6)
			{
				if (sti(pchar.rank) > 20) iRank = sti(pchar.rank) + 2; //15
				else iRank = sti(pchar.rank);  //10
			}
			else
			{
				iRank = sti(pchar.rank);
			}
			//<-- генерим ранг
			//определяем локаторы для размещения торговцев
			makearef(arQuestLoc, Islands[islandIdx].Quest_ships);
			iTemp = GetAttributesNum(arQuestLoc) - 1;
			int n = 0;
			int iRand = rand(4);
			for (i = iTemp; n < 5; i--)
			{
				arLocator = GetAttributeN(arQuestLoc, i);
				locatorName = GetAttributeName(arLocator);
				sTemp = "l" + n;
				if (HasSubStr(locatorName, "Quest"))
				{
					if (iRand == n)
					{
						//==> ставим пирата
						Group_AddCharacter("MQGroupPirate", "MQPirate");
						Group_SetType("MQGroupPirate", "pirate");
						Group_SetGroupCommander("MQGroupPirate", "MQPirate");
						Group_LockTask("MQGroupPirate");
						Group_SetAddress("MQGroupPirate", pchar.GenQuest.DestroyPirate.Areal, "Quest_ships", locatorName);
						int iShore = GetAttributesNum(arPlTarget) - 1;
						arLocator = GetAttributeN(arPlTarget, iShore);
						locatorName = GetAttributeName(arLocator);
						Group_SetTaskMove("MQGroupPirate", stf(arPlTarget.(locatorName).ships.(sTemp).x), stf(arPlTarget.(locatorName).ships.(sTemp).z));
					}
					else
					{
						//ставим торговцев
						captainId = "MQCaptain_" + n;
						GroupName = "MQGroupAll_" + n;
						sld = GetCharacter(NPC_GenerateCharacter(captainId, "", "man", "man", iRank, sti(npchar.nation), -1, true));
						SetCaptanModelByEncType(sld, "trade");
						DeleteAttribute(sld, "Ship");
						SetShipToFantom(sld, "trade", true);
						sld.Ship.Mode = "Trade";
						sld.AlwaysSandbankManeuver = true;
						sld.DontRansackCaptain = true;  //fix
						Group_AddCharacter(GroupName, captainId);
						Group_SetGroupCommander(GroupName, captainId);
						Group_SetAddress(GroupName, pchar.GenQuest.DestroyPirate.Areal, "Quest_ships", locatorName);
						Group_SetTaskMove(GroupName, stf(arPlTarget.l1.ships.(sTemp).x), stf(arPlTarget.l1.ships.(sTemp).z));
					}
					n++;
				}
			}
			//сформируем строку с типом корабля, пригодится
			sld = characterFromId("MQPirate");
			iTemp = RealShips[sti(sld.ship.type)].basetype;
			pchar.GenQuest.DestroyPirate.ShipType = GetShipSexWord(ShipsTypes[iTemp].name, XI_ConvertString("PiratMan"), XI_ConvertString("PiratWoman")) + XI_ConvertString(ShipsTypes[iTemp].name + "Gen");
			//прерывание на смерть пирата
			pchar.quest.DestroyPirate.win_condition.l1 = "NPC_Death";
			pchar.quest.DestroyPirate.win_condition.l1.character = "MQPirate";
			pchar.quest.DestroyPirate.win_condition = "DestroyPirate_after";
			//таймер
			SetTimerCondition("DestroyPirate_Late", 0, 0, sti(pchar.GenQuest.DestroyPirate.Terms), false);
			//судовой журнал
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "10");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sDay", FindDaysString(sti(pchar.GenQuest.DestroyPirate.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindMoneyString(sti(pchar.GenQuest.DestroyPirate.Money)));
		break;

		case "DestroyPirate_WithoutFight":
			pchar.quest.Munity = "Deads";  // откроем выход
			sld = characterFromId("MQPirate");
			sld.money = pchar.money;
			pchar.money = 0;
			Ship_SetTaskRunaway(SECONDARY_TASK, sti(sld.index), 1); //сваливаем
		break;

		case "DestroyPirate_FightInDeck":
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			iRank = 5 + sti(MOD_SKILL_ENEMY_RATE);
			LAi_group_Delete("EnemyFight");
			arrayNPCModelHow = 0;
			for (i = 1; i < iRank; i++)
			{
				iTemp = GetCharacterIndex("saylor_0" + i); //на палубе уже кто-то есть
				if (iTemp == -1)
				{
					iTemp = NPC_GenerateCharacter("saylor_0" + i, "pirate_" + (rand(15) + 1), "man", "man", 10, PIRATE, 0, true); //TODO: скалирование ранга
					SetNPCModelUniq(&characters[iTemp], "pirate", MAN);
					ChangeCharacterAddressGroup(&characters[iTemp], pchar.location, "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				}
				LAi_group_MoveCharacter(&characters[iTemp], "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DestroyPirate_TeamIsDead");
		break;

		case "DestroyPirate_TeamIsDead":
			Pchar.quest.DestroyPirate_PirateIsOut.win_condition.l1 = "ExitFromSea";
			Pchar.quest.DestroyPirate_PirateIsOut.win_condition = "DestroyPirate_PirateIsOut";
			LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(loadedLocation, true);
			DoQuestCheckDelay("TalkSelf_Quest", 0.4); //диалог сам-на-сам
		break;

		case "DestroyPirate_PirateIsOut":
			pchar.quest.DestroyPirate_Late.over = "yes"; //снимаем таймер
			pchar.GenQuest.DestroyPirate = "PirateIsOut"; //флаг пират свалил
			npchar = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
			LAi_group_Delete("MayorPirateGroup");
			Group_DeleteGroup("MQGroupPirate");
			for (i = 0; i < 5; i++)
			{
				Group_DeleteGroup("MQGroupAll_" + i);
			}
			// слухи
			AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_119", GetMainCharacterNameGen()),
					StringFromKey("Common_rumours_121"),
					StringFromKey("Common_rumours_120", GetFullName(pchar))), sti(npchar.nation), 5, 1);
		break;

		case "DestroyPirate_after":
			pchar.quest.DestroyPirate_PirateIsOut.over = "yes"; //снимаем прерывание на ушёл с поля боя
			pchar.quest.DestroyPirate_Late.over = "yes"; //снимаем таймер
			LAi_group_Delete("MayorPirateGroup");
			Group_DeleteGroup("MQGroupPirate");
			pchar.GenQuest.DestroyPirate = "Execute"; //флаг выполнил успешно
			npchar = characterFromId(pchar.GenQuest.DestroyPirate.MayorId);
			// судовой журнал
			AddQuestRecord("MayorsQuestsList", "11");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "ShipType", GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType));
			AddQuestUserData("MayorsQuestsList", "sDay", FindDaysString(sti(pchar.GenQuest.DestroyPirate.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindMoneyString(sti(pchar.GenQuest.DestroyPirate.Money)));
			// слухи
			AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_122", GetFullName(npchar), GetMainCharacterNameDat(), GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType)),
					StringFromKey("Common_rumours_123", GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType)),
					StringFromKey("Common_rumours_124", XI_ConvertString("Colony" + npchar.city + "Gen"), GetMainCharacterNameDat(), GetStrSmallRegister(pchar.GenQuest.DestroyPirate.ShipType))), sti(npchar.nation), 5, 1);
		break;

		case "DestroyPirate_Late":
			if (bSeaActive)
			{
				Pchar.quest.AllMayorsQuests_Late.win_condition.l1 = "ExitFromSea";
				Pchar.quest.AllMayorsQuests_Late.win_condition = "AllMayorsQuests_Late";
			}
			else
			{
				DoQuestCheckDelay("AllMayorsQuests_Late", 0.1);
			}
		break;

		case "DestroyPirate_toShore":
			sTemp = pchar.GenQuest.questName;
			pchar.quest.DestroyPirate_Late.over = "yes"; //снимаем таймер
			pchar.GenQuest.(sTemp) = "Found";
			npchar = characterFromId(pchar.GenQuest.(sTemp).MayorId);
			attrName = GetConvertStr(pchar.GenQuest.DestroyPirate.outShoreId, "LocLables.txt");
			//судовой журнал
			AddQuestRecord("MayorsQuestsList", "12");
			AddQuestUserData("MayorsQuestsList", "Shore", attrName);
			// слухи
			AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_125", GetFullName(npchar), GetMainCharacterNameDat(), GetMainCharacterNameGen()),
					StringFromKey("Common_rumours_126"),
					StringFromKey("Common_rumours_127")), sti(npchar.nation), 5, 1);
			//снимаем кораблики пирата и торговцев
			LAi_group_Delete("MayorPirateGroup");
			Group_DeleteGroup("MQGroupPirate");
			for (i = 0; i < 5; i++)
			{
				Group_DeleteGroup("MQGroupAll_" + i);
			}
			pchar.money = 0;
			pchar.quest.Munity = "Deads";
			pchar.location.from_sea = npchar.city + "_town";
			//--> ВОТ ЗДЕСЬ МЕТОД НА РЕЛОАД ИЗ ПАЛУБЫ В БУХТУ
			DoReloadFromDeckToLocation(pchar.GenQuest.DestroyPirate.outShoreId, "reload", "sea");
		//<-- ВОТ ЗДЕСЬ МЕТОД НА РЕЛОАД ИЗ ПАЛУБЫ В БУХТУ
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    Поиск и уничтожение пирата
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало   Генератор - Поручение капитана "Операция 'Галеон'"
		////////////////////////////////////////////////////////////////////////

		case "CaptainComission_FightInDeck":
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_LocationFightDisable(loadedLocation, false);
			LAi_SetFightMode(pchar, true);
			iRank = sti(pchar.rank) + 5 + rand(MOD_SKILL_ENEMY_RATE);
			LAi_group_Delete("EnemyFight");
			for (i = 1; i < 5; i++)
			{
				sld = characterFromID("saylor_0" + i);
				sld.rank = iRank;
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CaptainComission_TeamIsDead");
		break;

		case "CaptainComission_TeamIsDead":
			pchar.quest.CaptainComission_CapIsOut.win_condition.l1 = "ExitFromSea";
			pchar.quest.CaptainComission_CapIsOut.function = "CaptainComission_CapIsOut";
			pchar.quest.CaptainComission_CapIsDead.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_CapIsDead.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapIsDead.function = "CaptainComission_CapIsDead";
			LAi_SetFightMode(pchar, false);
			LAi_LocationFightDisable(loadedLocation, true);
		//DoQuestCheckDelay("TalkSelf_Quest", 0.4); //Лесник (Slayer). Тут лишнее
		break;

		case "CaptainComission_TalkCanoneer":
			LAi_Fade("CaptainComission_TalkCanoneer_prepare", "CaptainComission_TalkCanoneer2");
		break;

		case "CaptainComission_TalkCanoneer_prepare":
			LAi_SetSitType(pchar);
			sld = characterFromID("CapComission_Canoneer");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			ChangeCharacterAddressGroup(pchar, pchar.GenQuest.CaptainComission.City + "_tavern", "sit", "sit_front2");
		break;

		case "CaptainComission_TalkCanoneer2":
			LAi_ActorDialogNow(characterFromID("CapComission_Canoneer"), pchar, "", -1);
		break;

		case "CaptainComission_exit_sit":
			if (pchar.location.group == "sit")
			{
				LAi_Fade("CaptainComission_exit_sit_2", "");
			}
		break;

		case "CaptainComission_exit_sit_2":
			sld = characterFromID("CapComission_Canoneer");
			LAi_SetSitType(sld);
			LAi_SetPlayerType(pchar);
			PlaceCharacter(pchar, "tables", pchar.location); // ближний к столу
		break;

		case "CaptainComission_GangDialog_1":
			sld = characterFromID("Gang_0");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "CaptainComission_MapEnterAfterShoreBattle":
			for (i = 1; i <= 3; i++)
			{
				iTemp = GetCharacterIndex("Pirate_Captain0" + i);
				if (iTemp != -1)
				{
					characters[iTemp].lifeDay = 0;
				}
			}
			Group_DeleteGroup("Pirate_Guards");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;

		case "CaptainComission_GenerateCapJail":
			sld = characterFromID("CapComission_1");
			ChangeCharacterAddressGroup(sld, pchar.GenQuest.CaptainComission.City + "_prison", "goto", "goto9");
			LAi_group_MoveCharacter(sld, "Prisoner_Group");
			LAi_SetCitizenType(sld); // Лесник (Slayer). С этого места не было кода
			LAi_SetStayType(sld);
			sld.name = pchar.GenQuest.CaptainComission.Name;
			sld.lastname = "";
			sld.greeting = "Gr_prison";
			sld.dialog.FileName = "Quest\GenQuests_dialog.c";
			sld.dialog.currentnode = "CaptainComission_370";
		break;

		case "CaptainComission_Capitan_Cdox":
		// Лесник (Slayer). Добавлена проверка на смерть капитана по "поручению капитана" от руки игрока уже после тюрьмы
			AddQuestRecord("CaptainComission2", "33");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;

		case "CaptainComission_PrisonFree_Death":
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
			pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
			pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			AddQuestRecord("CaptainComission2", "54");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;

		case "CaptainComission_DeletePrisonGroup":
			LAi_group_Delete("CapComission_Prison");
		break;

		case "CaptainComission_ExitFromPrison":
			iTemp = GetCharacterIndex("CapComission_1");
			if (iTemp != -1)
			{
				pchar.quest.CaptainComission_ExitFromTown.win_condition.l1 = "EnterToSea";
				pchar.quest.CaptainComission_ExitFromTown.function = "CaptainComission_ExitFromTown";
				pchar.GenQuest.CaptainComission.canSpeakCaptain = true;
				pchar.TownEscape = true;
			}
		break;

		case "CaptainComission_MeetWithCaptain":
			Sea_DeckBoatStartNow(pchar);
		break;

		case "CaptainComission_MapEnterCapDied":
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
		break;

		case "CaptainComission_ShoreGangDialog":
			SetMainCharacterIndex(1);
			pchar = GetMainCharacter();
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			DoQuestFunctionDelay("CaptainComission_BattleInShore", 5.0);
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец   Генератор - Поручение капитана "Операция 'Галеон'"
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало   Генератор - "Кораблекрушенцы"
		////////////////////////////////////////////////////////////////////////

		case "ShipWreck_RemoveSailorsFromShore":
			for (i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				iTemp = GetCharacterIndex("ShipWreck_" + i);
				if (iTemp != -1)
				{
					Characters[iTemp].LifeDay = 0;
				}
			}
			DeleteAttribute(pchar, "GenQuest.ShipWreck");
		break;

		////////////////////////////////////////////////////////////////////////
		//  Конец   Генератор - "Кораблекрушенцы"
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало    Грабители в городах
		////////////////////////////////////////////////////////////////////////
		case "Berglars_Ostin":
			chrDisableReloadToLocation = true;
			sld = GetCharacter(NPC_GenerateCharacter("Ostin", "Ostin", "man", "man", 30, SPAIN, -1, false));
			FantomMakeCoolFighter(sld, 30, 100, 70, "blade32", "pistol5", 50);
			sld.name = FindPersonalName("Ostin_name");
			sld.lastname = FindPersonalName("Ostin_lastname");
			sld.rank = 30;
			sld.dialog.filename = "Quest\Berglars.c";
			sld.dialog.currentnode = "Final_fight";
			sld.greeting = "Gr_OliverTrast";
			sld.money = 30670;
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Sliding");
			TakeNItems(sld, "jewelry1", 20 + rand(5));
			TakeNItems(sld, "jewelry2", 14 + rand(5));
			TakeNItems(sld, "jewelry3", 18 + rand(5));
			TakeNItems(sld, "jewelry4", 16 + rand(5));
			GiveItem2Character(sld, "incas_collection");
			GiveItem2Character(sld, "spyglass4");
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Berglars_Over":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			AddQuestRecord("BerglarsGang", "14");
			AddQuestUserData("BerglarsGang", "sSex", GetSexPhrase("", "а"));
			Achievment_Set(ACH_Detektiv);
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    Грабители в городах
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало   Бордель
		////////////////////////////////////////////////////////////////////////
		case "Brothel_checkVisitTime":
			LocatorReloadEnterDisable(qname + "_Brothel", "reload2_back", true); //закрываем комнату
			sld = characterFromId(pchar.quest.(qname).HorseId);
			sld.location = qname + "_Brothel";
			sld.location.group = "goto";
			sld.location.locator = pchar.quest.(qname).locator;
			//ChangeCharacterAddressGroup(sld, qname+"_Brothel", "goto", pchar.quest.(qname).locator);
			DeleteAttribute(&characters[GetCharacterIndex(qname + "_Hostess")], "quest.selected"); //снимаем флаг у хозяйки
			//==> ноду девкам
			for (i = 0; i < MAX_CHARACTERS; i++)
			{
				makeref(sld, Characters[i]);
				if (sld.location == qname + "_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
				{
					sld.dialog.currentnode = "Horse_talk";
				}
			}
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец    Бордель
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало    Грабеж жемчужного промысла
		////////////////////////////////////////////////////////////////////////
		//--------------------- промысел через залив Сан-Хуан дель Норте и подземелье -----------------------
		case "PearlGen_checkSantaCatalina":
			if (locations[reload_cur_location_index].id == "Pearl_CaveEntrance")
			{
				if (!CheckAttribute(&locations[reload_location_index], "PearlSantaCatalina") || GetNpcQuestPastDayParam(&locations[reload_location_index], "PearlSantaCatalina") > 30)
				{
					LAi_group_Delete("PearlGroup_2");
					iTemp = sti(colonies[FindColony("SantaCatalina")].nation); //Принадлежность промысла нации, от Санта-Каталины
					SaveCurrentNpcQuestDateParam(&locations[reload_location_index], "PearlSantaCatalina");
					switch (iTemp)
					{
						case ENGLAND:    sTemp = "milit_eng_" + (rand(7) + 1);        break;
						case FRANCE:    sTemp = "milit_fra_" + (rand(7) + 1);        break;
						case SPAIN:        sTemp = "milit_spa_" + (rand(7) + 1);    break;
						case HOLLAND:    sTemp = "milit_hol_" + (rand(7) + 1);        break;
						case PIRATE:    sTemp = "citiz_" + (rand(9) + 51);            break; //ПРОМЫСЕЛ НАШ, на охране слоник-базич
					}
					sld = GetCharacter(NPC_GenerateCharacter("PearlGuardMan_2", sTemp, "man", "man", 10, iTemp, 31, true));
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto" + RandFromThreeDight(3, 4, 8));
					sld.city = "SantaCatalina"; //НЗГ Санта-Каталины
					LAi_group_MoveCharacter(sld, "PearlGroup_2");
					LAi_SetActorType(sld);
					locations[FindLocation("Pearl_town_2")].pearlVillage = true; //флаг генерить жемчужников
					bOk = true;    //мир
					if (GetRelation2BaseNation(iTemp) != RELATION_FRIEND)
					{
						if (GetDaysContinueNationLicence(iTemp) == -1)
						{
							if ((GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetCharacterReputation_WithNation(pchar, iTemp)) < (10 + rand(50) + rand(50))) // Хорошие отношения с нацией, владеющей промыслами, повышают шанс на мирный проход в поселение, а плохие - понижают
							{
//								Log_SetStringToLog(StringFromKey("InfoMessages_55"));
								Notification(StringFromKey("InfoMessages_55"), "none");
								LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
								bOk = false; //война
							}
							else
							{
								AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
							}
						}
					}
					if (bOk)
					{
						chrDisableReloadToLocation = true;
						sld.dialog.Filename = "Pearl_dialog.c";
						sld.dialog.currentnode = "GuardMan";
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else //обратный путь
			{
				if (locations[reload_cur_location_index].id == "Pearl_town_2" && GetCharacterIndex("HeadMan_2") == -1)
				{
					iTemp = 0;
					for (i = 0; i < MAX_CHARACTERS; i++)
					{
						if (characters[i].location == "Pearl_town_2")
						{
							characters[i].location = "none";
							iTemp++;
						}
					}
					if (iTemp > 0) //остатки жемчуга скоммуниздили оставшиеся в живых жемчужники
					{
						DeleteAttribute(&locations[FindLocation("PearlTown2_Townhall")], "box1");
						DeleteAttribute(&locations[FindLocation("PearlTown2_Townhall")], "box2");
					}
				}
			}
			pchar.quest.PearlGen_SetNewInterrapt_2.win_condition.l1 = "ExitFromLocation";
			pchar.quest.PearlGen_SetNewInterrapt_2.win_condition.l1.location = "Pearl_Jungle_06";
			pchar.quest.PearlGen_SetNewInterrapt_2.function = "PearlGen_SetSantaCatalina";
		break;

		//----------------------------------- промысел через Теночтитлан --------------------------------------
		case "PearlGen_checkTeno":
			if (locations[reload_cur_location_index].id == "Pearl_Jungle_03")
			{
				if (!CheckAttribute(&locations[reload_location_index], "PearlTeno") || GetNpcQuestPastDayParam(&locations[reload_location_index], "PearlTeno") > 30)
				{
					LAi_group_Delete("PearlGroup_1");
					iTemp = sti(colonies[FindColony("SantaCatalina")].nation); //Принадлежность промысла нации, от Санта-Каталины
					SaveCurrentNpcQuestDateParam(&locations[reload_location_index], "PearlTeno");
					switch (iTemp)
					{
						case ENGLAND:    sTemp = "milit_eng_" + (rand(7) + 1);        break;
						case FRANCE:    sTemp = "milit_fra_" + (rand(7) + 1);        break;
						case SPAIN:        sTemp = "milit_spa_" + (rand(7) + 1);    break;
						case HOLLAND:    sTemp = "milit_hol_" + (rand(7) + 1);        break;
						case PIRATE:    sTemp = "citiz_" + (rand(9) + 51);            break; //ПРОМЫСЕЛ НАШ, на охране слоник-базич
					}
					sld = GetCharacter(NPC_GenerateCharacter("PearlGuardMan_1", sTemp, "man", "man", 10, iTemp, 31, true));
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto" + RandFromThreeDight(1, 9, 8));
					sld.city = "SantaCatalina"; //испанские НЗГ
					LAi_group_MoveCharacter(sld, "PearlGroup_1");
					LAi_SetActorType(sld);
					locations[FindLocation("Pearl_town_1")].pearlVillage = true; //флаг генерить жемчужников
					bOk = true;    //мир
					if (GetRelation2BaseNation(iTemp) != RELATION_FRIEND)
					{
						if (GetDaysContinueNationLicence(iTemp) == -1)
						{
							if ((GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetCharacterReputation_WithNation(pchar, iTemp)) < (10 + rand(50) + rand(50))) // Хорошие отношения с нацией, владеющей промыслами, повышают шанс на мирный проход в поселение, а плохие - понижают
							{
//								Log_SetStringToLog(StringFromKey("InfoMessages_55"));
								Notification(StringFromKey("InfoMessages_55"), "none");
								LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", -1);
								bOk = false; //война
							}
							else
							{
								AddCharacterExpToSkill(pchar, SKILL_SNEAK, 80);
							}
						}
					}
					if (bOk)
					{
						chrDisableReloadToLocation = true;
						sld.dialog.Filename = "Pearl_dialog.c";
						sld.dialog.currentnode = "GuardMan";
						LAi_ActorDialog(sld, pchar, "", -1, 0);
					}
				}
			}
			else //обратный путь
			{
				if (locations[reload_cur_location_index].id == "Pearl_town_1" && GetCharacterIndex("HeadMan_1") == -1)
				{
					iTemp = 0;
					for (i = 0; i < MAX_CHARACTERS; i++)
					{
						if (characters[i].location == "Pearl_town_1")
						{
							characters[i].location = "none";
							iTemp++;
						}
					}
					if (iTemp > 0) //остатки жемчуга скоммуниздили оставшиеся в живых жемчужники
					{
						DeleteAttribute(&locations[FindLocation("PearlTown1_Townhall")], "box1");
						DeleteAttribute(&locations[FindLocation("PearlTown1_Townhall")], "box2");
					}
				}
			}
			pchar.quest.PearlGen_SetNewInterrapt_1.win_condition.l1 = "ExitFromLocation";
			pchar.quest.PearlGen_SetNewInterrapt_1.win_condition.l1.location = "Pearl_Jungle_02";
			pchar.quest.PearlGen_SetNewInterrapt_1.function = "PearlGen_SetTeno";
		break;

		case "PearlToShore_ForSale":
			chrDisableReloadToLocation = false;
			LAi_SetCitizenTypeNoGroup(&characters[sti(pchar.quest.PearlToShore_ForSale.idx)]);
		break;

		case "Pearl_GuardManIsLife":
			sld = &characters[sti(pchar.quest.Pearl_GuardManIsLife.idx)];
			sld.dialog.Filename = "Pearl_dialog.c";
			sld.dialog.currentnode = "GuardManAllarm";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto10");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.5, 0);
		break;

        case "SeaPearl_SharpPrisoner_GiveFree_ReloadToGrot":
            chrDisableReloadToLocation = false;

            DoQuestReloadToLocation("Hispaniola_Grot", "reload", "reload1", "");
        break;
        case "SeaPearl_SharpPrisoner_GiveFree_StartDialogDelay":
            DoQuestCheckDelay("SeaPearl_SharpPrisoner_GiveFree_StartDialog", 1.5);
        break;
		case "SeaPearl_SharpPrisoner_GiveFree_StartDialog":
			sld = CharacterFromID("Sharp_Prisoner");

			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "SeaPearl_SharpPrisoner_GiveFree_ReleaseSharp":
			LAi_LocationDisableMonstersGen(pchar.location, false);

			sld = CharacterFromID("Sharp_Prisoner");
			ReleasePrisoner(sld);

			if (CheckAttribute(&TEV, "Sharp_Prisoner_DialogChoosen"))
			{
				DeleteAttribute(&TEV, "Sharp_Prisoner_DialogChoosen");
			}

			ref rChrOld = CharacterFromID("Sharp");
			rChrOld.lifeDay = 0;

			pchar.questTemp.Sharp = "over_SharpReleased";
			AddQuestRecord("SharpPearl", "30");
			AddQuestUserData("SharpPearl", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("SharpPearl");
			Achievment_Set(ACH_Lovets_zhemchuga);
		break;
		case "SeaPearl_SharpPrisoner_GiveFree_HireSharp":
			LAi_LocationDisableMonstersGen(pchar.location, false);

			sld = CharacterFromID("Sharp_Prisoner");
			ReleasePrisoner(sld);

			if (CheckAttribute(&TEV, "Sharp_Prisoner_DialogChoosen"))
			{
				DeleteAttribute(&TEV, "Sharp_Prisoner_DialogChoosen");
			}

			SeaPearl_SharpPrisoner_GiveFree_AddSharpToCrew();

			pchar.questTemp.Sharp = "over_SharpHired";
			AddQuestRecord("SharpPearl", "31");
			CloseQuestHeader("SharpPearl");
			Achievment_Set(ACH_Lovets_zhemchuga);
		break;

		////////////////////////////////////////////////////////////////////////
		//  Конец    Грабеж жемчужного промысла
		////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////
		//  Начало Тюремные квесты
		////////////////////////////////////////////////////////////////////////
		case "GivePrisonFree":
			chrDisableReloadToLocation = true;
			LAi_LocationDisableMonstersGen(pchar.location, true);
			pchar.quest.GivePrisonFree_Death.over = "yes";
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			sld.dialog.currentnode = "PrisonerInPlace";
			RemovePassenger(pchar, sld);
			LAi_SetActorTypeNoGroup(sld);
			GetCharacterPos(sld, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "GivePrisonFree_Death":
			AddQuestRecord("GivePrisonFree", "2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			pchar.quest.PrisonerEnterToSea.over = "yes";
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
			pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
			pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;

		case "PrisonerEnterToSea":
			sld = CharacterFromID(pchar.questTemp.jailCanMove.prisonerId);
			LAi_type_actor_Reset(sld);
			ChangeCharacterAddressGroup(sld, "None", "", "");
			FaceMaker(sld);
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
		break;

		case "GivePrisonFree_Over":
			AddQuestRecord("GivePrisonFree", "6");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.prisonerId);
			if (iTemp > 0)
			{
				characters[iTemp].lifeDay = 0;
				ChangeCharacterAddress(&characters[iTemp], "none", "");
			}
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
			Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
			Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
			Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;

		case "DeliverToBander":
			if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.City") && pchar.questTemp.jailCanMove.Deliver.City == locations[reload_location_index].fastreload)
			{
				LAi_group_Delete("EnemyFight");
				chrDisableReloadToLocation = true;
				pchar.quest.DeliverToBander.over = "yes";
				pchar.quest.DeliverToBander_over.over = "yes";
				//--> генерим ранг
				if (sti(pchar.rank) > 6 || MOD_SKILL_ENEMY_RATE > 7)
				{
					iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE;
				}
				else
				{
					//казуалам зелёный свет на начало игры
					if (sti(pchar.rank) > 3) iRank = sti(pchar.rank);
					else
					{
						iRank = 1;
					}
				}
				//<-- генерим ранг
				GetCharacterPos(pchar, &locx, &locy, &locz);
				arrayNPCModelHow = 0;
				for (i = 1; i <= 2; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Bander_" + i, "pirate_" + (rand(15) + 1), "man", "man", iRank, PIRATE, 0, true));
					SetNPCModelUniq(sld, "pirate", MAN);
					sld.dialog.filename = "quest\Banders_dialog.c";
					sld.dialog.currentnode = "First time";
					sld.greeting = "marginal";
					SetFantomParamFromRank(sld, iRank, true);
					if (i == 1)
					{
						LAi_SetOwnerType(sld);
						sld.dialog.currentnode = "Second time";
						ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindFarLocator("goto", locx, locy, locz));
					}
					else
					{
						LAi_SetActorType(sld);
						sld.dialog.currentnode = "First time";
						ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestLocator("goto", locx, locy, locz));
					}
					LAi_group_MoveCharacter(sld, "EnemyFight");
				}
				LAi_ActorDialog(sld, pchar, "", 1.0, 0);
			}
		break;

		case "DeliverToBander_over":
			AddQuestRecord("MalyavaDeliver", "2");
			CloseQuestHeader("MalyavaDeliver");
			pchar.quest.DeliverToBander.over = "yes";
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
			if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			TakeItemFromCharacter(pchar, "Malyava");
		break;

		case "DeliverToBander_Dead":
			AddQuestRecord("MalyavaDeliver", "3");
			AddQuestUserData("MalyavaDeliver", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("MalyavaDeliver", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			CloseQuestHeader("MalyavaDeliver");
			chrDisableReloadToLocation = false;
			iTemp = GetCharacterIndex(pchar.questTemp.jailCanMove.Deliver.Id);
			if (iTemp > 0) ChangeCharacterAddress(&characters[iTemp], "none", "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			TakeItemFromCharacter(pchar, "Malyava");
		break;

		case "DeletePrisonGroup":
			LAi_group_Delete("DeliveQuest_Prison");
		break;
		////////////////////////////////////////////////////////////////////////
		//  Конец  Тюремные квесты
		////////////////////////////////////////////////////////////////////////

		// универсальный диалогостартер (см метод  SetActorDialogAny2Pchar)
		case "ActorDialog_Any2Pchar":
			LAi_SetActorType(PChar);
			LAi_ActorWaitDialog(Pchar, characterFromID(Pchar.AutoQuest.NPCharId));
			LAi_ActorDialog(characterFromID(Pchar.AutoQuest.NPCharId), Pchar, Pchar.AutoQuest.Quest, stf(Pchar.AutoQuest.Time1), stf(Pchar.AutoQuest.Time2));
		break;

		case "OpenTheDoors":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		break;

		case "CanEnterToMap":
			bQuestDisableMapEnter = false;
		break;

		case "CloseBermudesDungeonDoor":
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			sld = characterFromId("Pirates_shipyarder");
			DeleteAttribute(sld, "Step_Door");
		break;

		case "CanFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, false);
			chrDisableReloadToLocation = false;
		break;

		case "CannotFightCurLocation":
			LAi_LocationFightDisable(loadedLocation, true);
			chrDisableReloadToLocation = false;
		break;

		case "MainHeroFightModeOn":
			LAi_SetFightMode(pchar, true);
		break;

		case "MainHeroFightModeOff":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, true);
		break;

		case "MainHeroFightModeOff_NoLock":
			LAi_SetFightMode(pchar, false);
			LAi_LockFightMode(pchar, false);
		break;

		case "ChurchNightGuard_timerInChurch_2":
			TavernWaitDate("wait_day");
		break;

		case "MayorSitBack": //посадить мэра обратно
			iTemp = GetCharacterIndex(Pchar.quest.MayorSitBack.mayorId);
			if (iTemp > 0)
			{
				sld = &characters[iTemp];
				sld.location = Pchar.quest.MayorSitBack.locationName;
				sld.location.group = "sit";
				sld.location.locator = Pchar.quest.MayorSitBack.locatorName;
				LAi_SetHuberTypeNoGroup(sld);
				RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
				RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			}
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  START Английская линейка
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//==========================   Квест N1, Сопровождение герцога Альбермаля ========================

		case "fight_withSpanish_Albermal":                      //  Атака испанца на наш корабль с Альбермалем
			bQuestDisableMapEnter = true;
			Island_SetReloadEnableGlobal("Antigua", false);

			sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "navy_off_spa_2", "man", "man", 15, SPAIN, 0, true));
			FantomMakeCoolSailor(sld, SHIP_FLEUT, FindPersonalName("CaptainAttack_1_ship"), CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 20, 65, 40, "blade25", "pistol3", 80);
			sld.DontRansackCaptain = true; //квестовые не сдаются
			sld.SinkTenPercent = true; //уходим с повреждениями

			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Antigua", "", "");
			Group_LockTask("Spa_Attack");

			pchar.quest.after_fight_withSpanish_Albermal.win_condition.l1 = "NPC_Death";
			pchar.quest.after_fight_withSpanish_Albermal.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.after_fight_withSpanish_Albermal.win_condition = "after_fight_withSpanish_Albermal";
		break;

		case "after_fight_withSpanish_Albermal":                  // Испанский флейт на дне или захвачен
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Antigua", true);
			pchar.quest.goto_Oxbay_Albermal.win_condition.l1 = "location";
			pchar.quest.goto_Oxbay_Albermal.win_condition.l1.location = "SentJons_townhall";
			pchar.quest.goto_Oxbay_Albermal.win_condition = "goto_SentJons_Albermal";
			AddQuestRecord("Eng_Line_1_Albermal", "3");
			group_DeleteGroup("Spa_Attack");
		break;

		case "goto_SentJons_Albermal":
			sld = characterFromID("Albermal");                    //  Альбермаль в резиденции губернатора
			ChangeCharacterAddressGroup(sld, "SentJons_townhall", "goto", "goto5");
			sld.dialog.currentnode = "in_the_SentJons";
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar("Albermal", "", 0.0, 1.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		break;

		//==========================   Квест N3, Нападение на Белиз ========================
		case "time_over_Beliz_attack":
		// 50 дней на взятие Белиза, включая и походы за двумя пиратами, если геймер решит, что это ему нужно
			if (IsEntity(&worldMap))
			{
				if (!bQuestCheckProcessFreeze) // можно показать
				{
					pchar.quest.time_over_Beliz_attack_Map_01.over = "yes"; // сброс, если уже откладывали
					pchar.quest.time_over_Beliz_attack_Map_02.over = "yes";

					makearef(arOldMapPos, worldMap.old);
					WdmPrepareMapForAbordage(arOldMapPos);
					MakeCloneShipDeck(pchar, true); // подмена палубы
					DoReloadFromWorldMapToLocation("Ship_deck", "goto", "goto5");
					ReloadFromWMtoL_complete();

					sld = characterFromID("Henry Morgan");
					ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto6");
					LAi_SetWarriorType(sld);
					LAi_warrior_DialogEnable(sld, true);
					sld.dialog.currentnode = "time_over_Beliz";
					AddLandQuestmark_Main(sld, "Eng_Line");
					// ==> антураж
					arrayNPCModelHow = 0;
					for (i = 1; i < 5; i++)
					{
						attrName = "pirate_" + (rand(15) + 1);
						sld = GetCharacter(NPC_GenerateCharacter("MorganPir_" + i, attrName, "man", "man", 15, PIRATE, 1, true)); //watch_quest_moment; мб пираты Моргана должны быть покруче обычных?
						SetNPCModelUniq(sld, "pirate", MAN);
						sld.dialog.Filename = "Sailors_dialog.c";
						sld.dialog.currentnode = "Morgan_wait_you";
						LAi_SetWarriorType(sld);
						LAi_warrior_DialogEnable(sld, true);
						LAi_SetLoginTime(sld, 0.0, 24.0);
						LAi_SetHP(sld, 100.0, 100.0);
						ChangeCharacterAddressGroup(sld, "Ship_deck", "goto", "goto" + i);
					}
					pchar.quest.Munity = "";  // признак выхода с палубы (закрыто, а то можно не говорить)
					LAi_LockFightMode(pchar, true);
				}
				else
				{
					// отложим до разморозки (пролет табличек)
					Pchar.quest.time_over_Beliz_attack_Map_01.win_condition.l1 = "MapEnter";
					Pchar.quest.time_over_Beliz_attack_Map_01.win_condition = "time_over_Beliz_attack";
				}
			}
			else
			{
				// подождём выхода на карту, раз время прошло, но мы не на ней
				Pchar.quest.time_over_Beliz_attack_Map_02.win_condition.l1 = "MapEnter";
				Pchar.quest.time_over_Beliz_attack_Map_02.win_condition = "time_over_Beliz_attack";
			}
		break;

		//==========================   Квест N4, Разведмиссия в Кюрасао ========================
		case "Intelligence_Curacao_GoToShore":    //  Встреча с кораблем голландцев близ Кюрасао.
			if (pchar.questTemp.State == "Intelligence_Curacao_FightGard" || pchar.questTemp.State == "Intelligence_Curacao_OutPrison")
			{
				LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_Bank")], true); // вертаем запрет на боевки
				sld = characterFromID("Villemstad_usurer");
				ChangeCharacterAddressGroup(sld, "Villemstad_Bank", "goto", "goto1");
				LAi_SetBarmanType(sld);
				LAi_SetHP(sld, 80, 80); //вертаем ростовщика если убит
				pchar.quest.Intelligence_Curacao_OutTown.over = "yes";
			}
			else    //==> боевка с голландским кораблем
			{
				bQuestDisableMapEnter = true;
				Island_SetReloadEnableGlobal("Curacao", false);

				pchar.questTemp.abordage = 0; // запрещаем абордаж повторно - это сброс запрета

				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_hol_4", "man", "man", 23, HOLLAND, 0, true));
				FantomMakeCoolSailor(sld, SHIP_CORVETTE, "", CANNON_TYPE_CANNON_LBS24, 75, 65, 70);
				FantomMakeCoolFighter(sld, 25, 70, 50, BLADE_LONG, "pistol3", 70);
				sld.DontRansackCaptain = true; //квестовые не сдаются
				sld.SinkTenPercent = true; // уходим с повреждениями
				sld.Ship.name = FindPersonalName("CaptainAttack_1_ship2");

				Group_FindOrCreateGroup("Hol_Attack");
				Group_SetType("Hol_Attack", "war");
				Group_AddCharacter("Hol_Attack", "CaptainAttack_1");
				Group_SetGroupCommander("Hol_Attack", "CaptainAttack_1");
				Group_SetAddress("Hol_Attack", "Curacao", "", "");
				Group_SetPursuitGroup("Hol_Attack", PLAYER_GROUP);
				Group_SetTaskAttack("Hol_Attack", PLAYER_GROUP);
				Group_LockTask("Hol_Attack");
				//==> признак нахождения письма в каюте кэпа
				pchar.questTemp.EngLineQ4_PutLetter = 1;

				pchar.quest.Intelligence_Curacao_Boarding.win_condition.l1 = "Character_Capture";
				pchar.quest.Intelligence_Curacao_Boarding.win_condition.l1.character = "CaptainAttack_1";
				pchar.quest.Intelligence_Curacao_Boarding.win_condition = "Intelligence_Curacao_Boarding";

				pchar.quest.Intelligence_Curacao_Sink.win_condition.l1 = "Character_sink";
				pchar.quest.Intelligence_Curacao_Sink.win_condition.l1.character = "CaptainAttack_1";
				pchar.quest.Intelligence_Curacao_Sink.win_condition = "Intelligence_Curacao_Sink";
			}
		break;

		case "Intelligence_Curacao_Sink":   // Голландский корабль  потоплен
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Curacao", true);
			pchar.questTemp.State = "Intelligence_Curacao_Sink";
			AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "8");
			group_DeleteGroup("Hol_Attack");
			DeleteAttribute(PChar, "questTemp.EngLineQ4_PutLetter");
			pchar.quest.Intelligence_Curacao_Boarding.over = "yes";
            AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;

		case "Intelligence_Curacao_Boarding":   // Голландский корабль захвачен
			pchar.quest.Intelligence_Curacao_Sink.over = "yes";
			if (CheckCharacterItem(pchar, "letter_EngLineQ4"))
			{
				AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "9");
				AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("Eng_Line_4_Intelligence_Curacao", "sSex1", GetSexPhrase("ёл", "ла"));
				pchar.questTemp.State = "Intelligence_Curacao_Boarding";
				TakeItemFromCharacter(pchar, "letter_EngLineQ4");
				GiveItem2Character(pchar, "letter_open_EngLineQ4");
			}
			else
			{
				AddQuestRecord("Eng_Line_4_Intelligence_Curacao", "11");
				pchar.questTemp.State = "Intelligence_Curacao_BoardingNotFoundLetter";
			}
            AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
			bQuestDisableMapEnter = false;
			Island_SetReloadEnableGlobal("Curacao", true);
			pchar.quest.Intelligence_Curacao_Sink.over = "yes";
			group_DeleteGroup("Hol_Attack");
			DeleteAttribute(PChar, "questTemp.EngLineQ4_PutLetter");
		break;

		case "Intelligence_Curacao_KickYozef":  // ГГ отпинали в доме у ростовщика
			LAi_SetFightMode(pchar, false);
			DoReloadCharacterToLocation("Villemstad_prison", "goto", "goto9");
			if (!CheckAttribute(pchar, "questTemp.Azzy.Immortal")) LAi_SetImmortal(pchar, false);
			// ==> Забираем клинки, пистоли и деньги.
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
            RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "")
				TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));
			while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
				TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
			while (FindCharacterItemByGroup(pchar, MUSKET_ITEM_TYPE) != "")
				TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, MUSKET_ITEM_TYPE));
			pchar.money = 0;
			// <== Забираем клинки, пистоли и деньги.
			TakeNationLicence(HOLLAND);
			DoQuestCheckDelay("Intelligence_Curacao_GoPrisonMan", 10);
			sld = GetCharacter(NPC_GenerateCharacter("Hoverd_Tantum", "citiz_47", "man", "man", 15, ENGLAND, 3, false));
			sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
			sld.name = FindPersonalName("Hoverd_Tantum_name");
			sld.lastname = FindPersonalName("Hoverd_Tantum_lastname");
			LAi_SetStayTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto13");
		break;

		case "Intelligence_Curacao_GoPrisonMan":
			sld = characterFromID("Hoverd_Tantum");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto23", "Intelligence_Curacao_TalkingPrisonMan", -1);
		break;

		case "Intelligence_Curacao_TalkingPrisonMan":
			sld = characterFromID("Hoverd_Tantum");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

		//==========================   Квест N5, Нападение на Форт Оранж ========================
		// boal нужно переделать на генераторо захвата с сущи -->
		case "AttackFortOrange_GoToFort":
			Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
			DeleteQuestAttribute("Union_with_Escadra");
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			SetLocationCapturedState(sld.city + "_town", true);
			DoQuestCheckDelay("Capture_Forts", 0.5);
			Ship_NationAgressive(sld, sld);
			Log_SetStringToLog(StringFromKey("InfoMessages_56"));
			// установка отмены боевки в резиденции при захвате города
			//string _city, string _method, bool _majorOff
			SetCaptureResidenceQuest("FortOrange", "", true); // ФО, нет метода, губернатора в сад

			Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition.l1 = "location";
			Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition.l1.location = "FortOrange_townhall";
			Pchar.quest.AttackFortOrange_FightWithCommendant.win_condition = "AttackFortOrange_FightWithCommendant";
		break;

		case "AttackFortOrange_FightWithCommendant":
			chrDisableReloadToLocation = true; // закрыть выход из локации
			bDisableFastReload = true; // закрыть переходы.
			//--> огонь и пламень
			locations[FindLocation("FortOrange_town")].hidden_effects = true;
			locations[FindLocation("FortOrange_ExitTown")].hidden_effects = true;
			//<-- огонь и пламень

			sld = GetCharacter(NPC_GenerateCharacter("Orange_Comendant", "huber_25", "man", "man", 25, HOLLAND, 0, true));
			sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
			LAi_SetWarriorType(sld);
			LAi_warrior_DialogEnable(sld, true);
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			sld.cirassId = FindItem("cirass5"); //1.2.3
			LAi_LoginInCaptureTown(sld, true);
			FantomMakeCoolFighter(sld, 38, 90, 70, BLADE_LONG, "pistol3", 30);
			Statistic_AddValue(Pchar, "hol_GrabbingTown", 1); // статистика
			Achievement_AddStats_SturmColonies();
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 1.2);
		break;

		case "AttackFortOrange_AfterFightWithCommendant":
			AfterTownBattle();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.questTemp.State = "AttackFortOrange_WeWin";
			AddQuestRecord("Eng_Line_5_AttackFortOrange", "2");
            AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;

		//==========================   Квест N6, Моррис Уильямс ========================
		case "MorrisWillams_ShipToPort":
			Log_QuestInfo("На рейде Порт-Ройал установлен фрегат Морриса Уильямса.");
			sld = GetCharacter(NPC_GenerateCharacter("Morris_Willams", "MorrisWillams", "man", "man", 25, ENGLAND, -1, true));
			sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
			sld.name = FindPersonalName("Morris_Willams_name");
			sld.lastname = FindPersonalName("Morris_Willams_lastname");
			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			sld.greeting = "Gr_MiddPirate";
			LAi_SetStayTypeNoGroup(sld);
			FantomMakeCoolSailor(sld, SHIP_FRIGATE, FindPersonalName("Morris_Willams_ship"), CANNON_TYPE_CULVERINE_LBS24, 90, 90, 90);
			FantomMakeCoolFighter(sld, 28, 70, 40, BLADE_LONG, "pistol4", 100);
			sld.Ship.Stopped = true;
			sld.DeckDialogNode = "First time";
			sld.Ship.Mode = "Pirate";
			AddLandQuestmark_Main(sld, "Eng_Line");

			Group_FindOrCreateGroup("Willams_Group");
			Group_AddCharacter("Willams_Group", "Morris_Willams");
			Group_SetGroupCommander("Willams_Group", "Morris_Willams");
			Group_SetAddress("Willams_Group", "Jamaica", "quest_ships", "quest_ship_1");

			pchar.quest.MorrisWillams_WillamsAttack.win_condition.l1 = "NPC_Death";
			pchar.quest.MorrisWillams_WillamsAttack.win_condition.l1.character = "Morris_Willams";
			pchar.quest.MorrisWillams_WillamsAttack.win_condition = "MorrisWillams_WillamsAttack";
		break;

		case "MorrisWillams_WillamsAttack":
			sld = characterFromID("Morris_Willams");
			sld.LifeDay = 1; // уберем нпс на след.день.
			SaveCurrentNpcQuestDateParam(sld, "LifeTimeCreate");
			pchar.questTemp.State = "QuestLineBreake";
			ChangeCharacterReputation(pchar, -20);
			CloseQuestHeader("Eng_Line_6_MorrisWillams");
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;

		case "MorrisWillams_MeetWithManFromWillams":
			chrDisableReloadToLocation = true;
			Log_QuestInfo("Первая встреча с боцманом Уильямса.");
			pchar.quest.MorrisWillams_WillamsAttack.over = "yes"; // снимаем прерывание на завершение линейки

			sld = GetCharacter(NPC_GenerateCharacter("Bocman_Willams", "citiz_60", "man", "man", 25, ENGLAND, -1, true)); //watch_quest_moment; ванильный _15 сейчас циклоп
			sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
			sld.name = FindPersonalName("Bocman_Willams_name");
			sld.lastname = FindPersonalName("Bocman_Willams_lastname");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "MorrisWillams_InTavernWithWillams":
			sld = characterFromID("Morris_Willams");
			FreeSitLocator("PortRoyal_tavern", "sit11");
			LAi_SetSitTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "PortRoyal_tavern", "sit", "sit11");
			LocatorReloadEnterDisable("PortRoyal_town", "gate_back", true); //на всякий случай, чтобы геймер не слинял.
			LocatorReloadEnterDisable("PortRoyal_town", "reload1_back", true);
			LocatorReloadEnterDisable("PortRoyal_town", "boat", true);
		break;

		case "MorrisWillams_CheckTimeForForward":
			if (GetQuestPastTimeParam("questTemp") < 2)
			{
				Log_QuestInfo("Успел выйти в море за два часа игрового времени. Пинас должен быть на месте.");
				Pchar.quest.MW_AttackPinnace.win_condition.l1 = "location";
				Pchar.quest.MW_AttackPinnace.win_condition.l1.location = "PuertoRico";
				Pchar.quest.MW_AttackPinnace.win_condition = "MW_AttackPinnace";
				SetTimerCondition("MorrisWillams_PinaceTimeOver", 0, 0, 16, false);
			}
			else
			{
				Log_QuestInfo("Не успел выйти в море за два часа игрового времени. Пинаса не будет.");
				pchar.questTemp.State = "MorrisWillams_PinnaceNotFound";
				characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "First time";
                AddLandQuestmark_Main(CharacterFromID("Morris_Willams"), "Eng_Line");
                AddLandQuestmark_Main(CharacterFromID("SanJuan_tavernkeeper"), "Eng_Line");
			}
		break;

		case "MorrisWillams_PinaceTimeOver":
			pchar.quest.MW_AttackPinnace.over = "yes";
			Log_QuestInfo("Пинас не появится, не успел за 16 дней.");
			pchar.questTemp.State = "MorrisWillams_PinnaceNotFound";
			characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "First time";
			AddLandQuestmark_Main(CharacterFromID("Morris_Willams"), "Eng_Line");
            AddLandQuestmark_Main(CharacterFromID("SanJuan_tavernkeeper"), "Eng_Line");
		break;

		case "MW_AttackPinnace":
			Log_QuestInfo("Пинас установлен между фортом и кораблями охранения.");
			Island_SetReloadEnableGlobal("PuertoRico", false);
			characters[GetCharacterIndex("Morris_Willams")].dialog.currentnode = "First time";
			AddLandQuestmark_Main(CharacterFromID("Morris_Willams"), "Eng_Line");

			sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "navy_off_spa_3", "man", "man", 28, SPAIN, 0, true));
			sld.SinkTenPercent = true; // уходим с повреждениями
			sld.DontRansackCaptain = true; //квестовые не сдаются

			FantomMakeCoolSailor(sld, SHIP_PINNACE, FindPersonalName("CaptainAttack_1_ship3"), CANNON_TYPE_CANNON_LBS24, 85, 80, 85);
			FantomMakeCoolFighter(sld, 28, 90, 70, BLADE_LONG, "pistol3", 100);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "trade");
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetAddress("Spa_Attack", "PuertoRico", "", "");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			//            Group_SetTaskMove("Spa_Attack", 1930.0, -315.0);
			Group_LockTask("Spa_Attack");

			//==> признак нахождения письма в комоде
			pchar.questTemp.EngLineQ6_PutMoney = 1;
			pchar.questTemp.QtyMoneyTillBoarding = pchar.money;  // запомнить кол-во денег до абордажа, нужно для определения взял ли ГГ бабки из сундука в каюте

			pchar.quest.MorrisWillams_PinnaceBoarding.win_condition.l1 = "Character_Capture";
			pchar.quest.MorrisWillams_PinnaceBoarding.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.MorrisWillams_PinnaceBoarding.win_condition = "MorrisWillams_PinnaceBoarding";

			pchar.quest.MorrisWillams_PinnaceSink.win_condition.l1 = "Character_sink";
			pchar.quest.MorrisWillams_PinnaceSink.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.MorrisWillams_PinnaceSink.win_condition = "MorrisWillams_PinnaceSink";

			pchar.quest.MorrisWillams_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.MorrisWillams_DieHard.win_condition = "MorrisWillams_DieHard";
			pchar.quest.MorrisWillams_PinaceTimeOver.over = "yes";  // снимаем таймер на прибытие пинаса к острову
		break;

		case "MorrisWillams_PinnaceBoarding":
			iTemp = sti(pchar.money) - sti(pchar.questTemp.QtyMoneyTillBoarding);
			if (iTemp >= 140000)
			{
				Log_QuestInfo("Пинас взят на абордаж, деньги найдены.");
				AddQuestRecord("Eng_Line_6_MorrisWillams", "10");
				AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("Eng_Line_6_MorrisWillams", "sSex1", GetSexPhrase("ёл", "ла"));
				pchar.questTemp.State = "MorrisWillams_PinnaceBoard";
			}
			else
			{
				Log_QuestInfo("Пинас взят на абордаж, деньги не найдены. Миссия провалена.");
				AddQuestRecord("Eng_Line_6_MorrisWillams", "23");
				pchar.questTemp.State = "MorrisWillams_PinnaceBoardNotFoundMoney";
			}
			Island_SetReloadEnableGlobal("PuertoRico", true);
			group_DeleteGroup("Spa_Attack");
			Pchar.quest.MorrisWillams_DieHard.over = "yes";
			pchar.quest.MorrisWillams_PinnaceSink.over = "yes";
			DeleteAttribute(PChar, "questTemp.EngLineQ6_PutMoney");
			DeleteAttribute(PChar, "questTemp.QtyMoneyTillBoarding");
		break;

		case "MorrisWillams_PinnaceSink":
			Log_QuestInfo("Пинас потоплен.");
			Island_SetReloadEnableGlobal("PuertoRico", true);
			Pchar.quest.MorrisWillams_DieHard.over = "yes";
			pchar.quest.MorrisWillams_PinnaceBoarding.over = "yes";
			pchar.questTemp.State = "MorrisWillams_PinnaceSink";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "11");
			group_DeleteGroup("Spa_Attack");
			DeleteAttribute(PChar, "questTemp.EngLineQ6_PutMoney");
			DeleteAttribute(PChar, "questTemp.QtyMoneyTillBoarding");
		break;

		case "MorrisWillams_DieHard":
			Log_QuestInfo("Не сумел взять пинас. Пинаса больше нет.");
			Island_SetReloadEnableGlobal("PuertoRico", true);
			pchar.quest.MorrisWillams_PinnaceBoarding.over = "yes";
			pchar.quest.MorrisWillams_PinnaceSink.over = "yes";
			pchar.questTemp.State = "MorrisWillams_DieHard";
			AddQuestRecord("Eng_Line_6_MorrisWillams", "12");
			group_DeleteGroup("Spa_Attack");
			DeleteAttribute(PChar, "questTemp.EngLineQ6_PutMoney");
			DeleteAttribute(PChar, "questTemp.QtyMoneyTillBoarding");
		break;

		case "MorrisWillams_Arrest":
			Log_QuestInfo("Вторая встреча с боцманом Уильямса.");
			chrDisableReloadToLocation = true;
			sld = characterFromID("Bocman_Willams");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, "PortRoyal_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "MorrisWillams_HusbandInCave":
			Log_QuestInfo("Диалог и сразу бой. Снова диалог с Эттербери и на выход.");
			chrDisableReloadToLocation = true; // закрыть выход из локации
			arrayNPCModelHow = 0;
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bandit" + i, "citiz_" + (rand(9) + 51), "man", "man", 20, PIRATE, 0, true));
				SetNPCModelUniq(sld, "mercenary", MAN);
				FantomMakeCoolFighter(sld, 20, 70, 60, BLADE_LONG, "pistol2", 50);
				LAi_SetWarriorType(sld);
				sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Jamaica_Grot", "monsters", "monster" + i);
			}
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 1.5);

			npchar = GetCharacter(NPC_GenerateCharacter("Jillians_Husband", "vrach_61", "man", "man", 10, ENGLAND, 0, false));
			npchar.Dialog.Filename = "Quest\EngLineNpc_2.c";
			npchar.name = FindPersonalName("Jillians_Husband_name");
			npchar.lastname = FindPersonalName("Jillians_Husband_lastname");
			ChangeCharacterAddressGroup(npchar, "Jamaica_Grot", "monsters", "monster4");
			LAi_SetActorType(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_ActorWaitDialog(npchar, pchar);
		break;

		case "MorrisWillams_AftreFightingInCave":
			pchar.questTemp.State = "MorrisWillams_AfterFight";
			LAi_SetActorType(pchar);
			sld = characterFromID("Jillians_Husband");
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
			chrDisableReloadToLocation = false; // открыть выход из локации.
		break;

		case "MorrisWillams_SeekCirassa":
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			LAi_LocationDisableOffGenTimer("Shore_ship2", 1); //офицеров не пускать 1 день
			for (i = 1; i <= 7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Skelet" + i, "Skel" + (rand(3) + 1), "skeleton", "man", 25, PIRATE, 0, true));
				sld.skeleton = "1";
				if (i == 2)
				{
					sld.name = FindPersonalName("MorrisWillamsSkelet_name");
					sld.lastname = FindPersonalName("MorrisWillamsSkelet_lastname");
					sld.SaveItemsForDead = true; // сохранять на трупе вещи
					sld.DontClearDead = true;
					FantomMakeCoolFighter(sld, 40, 100, 70, BLADE_LONG, "pistol3", 110);
					GiveItem2Character(sld, "cirass5");
					GiveItem2Character(sld, "map_nevis");
					GiveItem2Character(sld, "map_normal");
					GiveItem2Character(sld, "spyglass4");
					TakeNItems(sld, "jewelry5", 150);
					TakeNItems(sld, "jewelry1", 54);
					TakeNItems(sld, "jewelry2", 32);
					TakeNItems(sld, "jewelry3", 41);
					TakeNItems(sld, "jewelry5", 25);
				}
				else FantomMakeCoolFighter(sld, 25, 80, 60, BLADE_LONG, "pistol3", 70);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				GetCharacterPos(pchar, &locx, &locy, &locz);
				sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
				if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
				ChangeCharacterAddressGroup(sld, "Shore_ship2", "goto", sTemp);
			}
			LAi_group_SetLookRadius("EnemyFight", 100);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "MorrisWillams_AfterFightInShore");
			Pchar.quest.MorrisWillams_SeekCirassaAgain.win_condition.l1 = "ExitFromLocation";
			Pchar.quest.MorrisWillams_SeekCirassaAgain.win_condition.l1.location = "Shore_ship2";
			Pchar.quest.MorrisWillams_SeekCirassaAgain.win_condition = "MorrisWillams_SeekCirassaAgain";
		break;

		case "MorrisWillams_AfterFightInShore":
			Pchar.quest.MorrisWillams_SeekCirassaAgain.over = "yes";
		break;

		case "MorrisWillams_SeekCirassaAgain":
			Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1 = "location";
			Pchar.quest.MorrisWillams_SeekCirassa.win_condition.l1.location = "Shore_ship2";
			Pchar.quest.MorrisWillams_SeekCirassa.win_condition = "MorrisWillams_SeekCirassa";
		break;

		//==========================   Квест N8, К Эдварду Мэнсфилду за золотом ========================
		case "ToMansfield_IntoTheTown":
			sld = GetCharacter(NPC_GenerateCharacter("Dick_Manson", "pirate_9", "man", "man", 10, ENGLAND, 5, true)); //watch_quest_moment
			sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
			sld.name = FindPersonalName("Dick_Manson_name");
			sld.lastname = FindPersonalName("Dick_Manson_lastname");
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "LaVega_tavern", "goto", "goto2");
			LAi_SetStayTypeNoGroup(sld);
			DoQuestCheckDelay("TalkSelf_Quest", 2.0); //диалог сам-на-сам
            AddLandQuestmark_Main(sld, "Eng_Line");
		break;

		case "ToMansfield_OutFromFort":
			Log_QuestInfo("Диалоговый буканьер убран из форта.");
			characters[GetCharacterIndex("Dick_Manson")].lifeDay = 0;
			if (pchar.questTemp.State == "ToMansfield_CatchToPardal")
			{
				Log_QuestInfo("Установлено прерывание на появление галеона возле Кубы.");
				Pchar.quest.ToMansfield_FightNearSantiago.win_condition.l1 = "location";
				Pchar.quest.ToMansfield_FightNearSantiago.win_condition.l1.location = "Cuba1";
				Pchar.quest.ToMansfield_FightNearSantiago.win_condition = "ToMansfield_FightNearSantiago";
				SetTimerCondition("ToMansfield_NotFoundGaleon", 0, 0, 12, false);
			}
			else
			{
				AddQuestRecord("Eng_Line_8_ToMansfield", "3");
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex1", GetSexPhrase("ёл", "ла"));
				pchar.questTemp.State = "ToMansfield_DidNotFindBecaners";
			}
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;

		case "ToMansfield_NotFoundGaleon":
		// ==> снимаем все прерывания, которые могут быть установлены
			Pchar.quest.ToMansfield_FightNearSantiago.over = "yes";
			pchar.questTemp.State = "ToMansfield_NotFoundGaleon";
			AddQuestRecord("Eng_Line_8_ToMansfield", "4");
			AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("", "а"));
			Log_QuestInfo("Не успел доплыть до Кубы. Галеон снят с бухты Сантьяго.");
		break;

		case "ToMansfield_FightNearSantiago":
			Log_QuestInfo("Галеон находится в бухте возле Сантьяго. Галеон идёт вглубь бухты в город.");
			Pchar.quest.ToMansfield_NotFoundGaleon.over = "yes"; // снимаем таймер на появление галеона

			sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "off_spa_2", "man", "man", 31, SPAIN, 0, true));
			sld.SinkTenPercent = true; // уходим с повреждениями
			sld.DontRansackCaptain = true; //квестовые не сдаются

			FantomMakeCoolSailor(sld, SHIP_GALEON_H, "", CANNON_TYPE_CANNON_LBS32, 95, 90, 90);
			FantomMakeCoolFighter(sld, 38, 90, 70, BLADE_LONG, "pistol3", 120);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Cuba1", "", "");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_LockTask("Spa_Attack");
			//==> признак нахождения письма в комоде
			pchar.questTemp.ELQ8_PutLetter = 1;

			pchar.quest.ToMansfield_GaleonBoarding.win_condition.l1 = "Character_Capture";
			pchar.quest.ToMansfield_GaleonBoarding.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.ToMansfield_GaleonBoarding.win_condition = "ToMansfield_GaleonBoarding";

			pchar.quest.ToMansfield_GaleonSink.win_condition.l1 = "Character_sink";
			pchar.quest.ToMansfield_GaleonSink.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.ToMansfield_GaleonSink.win_condition = "ToMansfield_GaleonSink";
			pchar.quest.ToMansfield_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.ToMansfield_DieHard.win_condition = "ToMansfield_DieHard";
		break;

		case "ToMansfield_GaleonBoarding":
			if (CheckCharacterItem(pchar, "letter_EngLineQ8"))
			{
				Log_QuestInfo("Письмо найдено и помещено в предметы.");
				AddQuestRecord("Eng_Line_8_ToMansfield", "5");
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex1", GetSexPhrase("ёл", "ла"));
				pchar.questTemp.State = "ToMansfield_Boarding";
				TakeItemFromCharacter(pchar, "letter_EngLineQ8");
				GiveItem2Character(pchar, "letter_open_EngLineQ8");
			}
			else
			{
				Log_QuestInfo("Письмо не найдено.");
				AddQuestRecord("Eng_Line_8_ToMansfield", "6");
				AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("", "а"));
				pchar.questTemp.State = "ToMansfield_BoardingNotFoundLetter";
			}
			pchar.quest.ToMansfield_GaleonSink.over = "yes";
			Pchar.quest.ToMansfield_DieHard.over = "yes"; // снимаем таймер на снятие галеона
			group_DeleteGroup("Spa_Attack");
			DeleteAttribute(PChar, "questTemp.ELQ8_PutLetter");
		break;

		case "ToMansfield_GaleonSink":
			Log_QuestInfo("Галеон потоплен.");
			pchar.quest.ToMansfield_GaleonBoarding.over = "yes";
			Pchar.quest.ToMansfield_DieHard.over = "yes"; // снимаем таймер на снятие галеона
			pchar.questTemp.State = "ToMansfield_GaleonSink";
			AddQuestRecord("Eng_Line_8_ToMansfield", "7");
			AddQuestUserData("Eng_Line_8_ToMansfield", "sSex", GetSexPhrase("", "а"));
			group_DeleteGroup("Spa_Attack");
			DeleteAttribute(PChar, "questTemp.ELQ8_PutLetter");
		break;

		case "ToMansfield_DieHard":
			Log_QuestInfo("Галеон снят.");
			pchar.quest.ToMansfield_GaleonBoarding.over = "yes";
			pchar.quest.ToMansfield_GaleonSink.over = "yes";
			pchar.questTemp.State = "ToMansfield_NotFoundGaleon";
			AddQuestRecord("Eng_Line_8_ToMansfield", "4");
			group_DeleteGroup("Spa_Attack");
			DeleteAttribute(PChar, "questTemp.ELQ8_PutLetter");
		break;

		//==========================   Квест N9, Нападение на Саньяго ========================
		case "AttackSantiago_FightWithPardal":
			Log_QuestInfo("Эскадра Пардаля установлена, будет бой.");
			Island_SetReloadEnableGlobal("Cuba1", false);
			PChar.questTemp.ELQ9_Diffrent = 1;
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			// ==> генерим эскадру Пардаля
			for (i = 1; i <= 4; i++)
			{
				attrName = "navy_off_spa_4";
				iRank = 27;
				ShipType = SHIP_GALEON_H;
				if (i == 1)
				{
					attrName = "navy_off_spa_5";
					iRank = 40;
					ShipType = SHIP_BATTLESHIP;
				}
				if (i == 2)
				{
					attrName = "navy_off_spa_3";
					iRank = 30;
					ShipType = SHIP_FRIGATE;
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, attrName, "man", "man", iRank, SPAIN, 0, true));
				FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_LBS_BY_SHIP, 95, 90, 90);
				FantomMakeCoolFighter(sld, iRank, 95, 70, BLADE_LONG, "pistol3", 120);
				Group_AddCharacter("Spa_Attack", "CaptainAttack_" + i);
				if (i == 1)
				{
					sld.Ship.Name = FindPersonalName("Spa_Attack_ship");
					sld.name = FindPersonalName("Spa_Attack_name");
					sld.lastname = FindPersonalName("Spa_Attack_lastname");
				}
			}
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Cuba1", "", "");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_LockTask("Spa_Attack");

			pchar.quest.AttackSantiago_AfterFight.win_condition.l1 = "Group_Death";
			pchar.quest.AttackSantiago_AfterFight.win_condition.l1.group = "Spa_Attack";
			pchar.quest.AttackSantiago_AfterFight.win_condition = "AttackSantiago_AfterFight";
			pchar.quest.AttackSantiago_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.AttackSantiago_DieHard.win_condition = "AttackSantiago_DieHard";
			// ==> запрет выхода на карту на 6мин если порт, а то есть возмоность свалить
			// === на карту сразу по выходу и это меняет схему боя.
			if (pchar.location.from_sea == "Santiago_town")
			{
				bQuestDisableMapEnter = true;
				DoQuestCheckDelay("CanEnterToMap", 400);
			}
		break;

		case "AttackSantiago_AfterFight":
			Log_QuestInfo("Эскадра Пардаля разбита.");
			pchar.questTemp.State = "AttackSantiago_GoodWork";
			AddQuestRecord("Eng_Line_9_AttackSantiago", "3");
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
			group_DeleteGroup("Spa_Attack");
			DeleteAttribute(PChar, "questTemp.ELQ9_Diffrent");
			ChangeCharacterReputation(pchar, 3);
			pchar.quest.AttackSantiago_DieHard.over = "yes"; //fix
			Island_SetReloadEnableGlobal("Cuba1", true);
		break;

		case "AttackSantiago_DieHard":
			pchar.quest.AttackSantiago_AfterFight.over = "yes";
			pchar.questTemp.State = "AttackSantiago_GoodWork";
			Log_QuestInfo("Эскадра Пардаля снята.");
			AddQuestRecord("Eng_Line_9_AttackSantiago", "4");
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
			group_DeleteGroup("Spa_Attack");
			DeleteAttribute(PChar, "questTemp.ELQ9_Diffrent");
			AddCharacterExpToSkill(pchar, "Leadership", -1650);
			AddCharacterExpToSkill(pchar, "Defence", -1300);
			AddCharacterExpToSkill(pchar, "Cannons", -1600);
			AddCharacterExpToSkill(pchar, "Sailing", -1400);
			AddCharacterExpToSkill(pchar, "Sneak", -1350);
			AddCharacterExpToSkill(pchar, "Grappling", 1200);
			AddCharacterExpToSkill(pchar, "Repair", -950);
			AddCharacterExpToSkill(pchar, "Pistol", -1200);
			AddCharacterExpToSkill(pchar, "Accuracy", -1510);
			AddCharacterExpToSkill(pchar, "Fencing", -1900);
			ChangeCharacterReputation(pchar, -5);
			Island_SetReloadEnableGlobal("Cuba1", true);
		break;

		//==========================   Квест N10, Отбить атаку испанцев на Порт-Ройал ========================
		case "SpanishAttack_Battle":
			Log_QuestInfo("Испанская эскадра установлена, будет крутой бой.");
			Island_SetReloadEnableGlobal("Jamaica", false);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			// ==> Испанские кэпы
			for (i = 1; i <= 7; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_MANOWAR;
						Model = "navy_off_spa_6";
						iRank = 40;
						Blade = "blade33";
					break;
					case 2:
						ShipType = SHIP_WARSHIP;
						Model = "navy_off_spa_5";
						iRank = 30;
						Blade = "blade28";
					break;
					case 3:
						ShipType = SHIP_BATTLESHIP;
						Model = "navy_off_spa_4";
						iRank = 33;
						Blade = "blade24";
					break;
					case 4:
						ShipType = SHIP_LINESHIP;
						Model = "navy_off_spa_4";
						iRank = 35;
						Blade = "blade34";
					break;
					case 5:
						ShipType = SHIP_GALEON;
						Model = "navy_off_spa_1";
						iRank = 27;
						Blade = "blade26";
					break;
					case 6:
						ShipType = SHIP_GALEON_H;
						Model = "navy_off_spa_3";
						iRank = 33;
						Blade = "blade28";
					break;
					case 7:
						ShipType = SHIP_FRIGATE;
						Model = "navy_off_spa_2";
						iRank = 29;
						Blade = "blade32";
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, Model, "man", "man", iRank, SPAIN, 0, true));
				//пришлось делать ветвление, т.к. фрегату давать 32ф пушки жирно,
				//а если всей эскадре ставить то что на ней должно быть получится жир, там вплоть до 42ф будет
				if (ShipType == SHIP_FRIGATE) FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_LBS_BY_SHIP, 100, 95, 95);
				else FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 100, 95, 95);
				FantomMakeCoolFighter(sld, iRank, 100, 90, Blade, "pistol3", 150);
				Group_AddCharacter("Spa_Attack", "CaptainAttack_" + i);
			}
			// ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Jamaica", "quest_ships", "quest_ship_3");
			Group_LockTask("Spa_Attack");
			// ==> прерывание на убиение эскадры
			pchar.quest.SpanishAttack_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.SpanishAttack_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SpanishAttack_AfterBattle.win_condition = "SpanishAttack_AfterBattle";
			pchar.quest.SpanishAttack_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.SpanishAttack_DieHard.win_condition = "SpanishAttack_DieHard";

			if (pchar.location.from_sea == "PortRoyal_town")
			{
				bQuestDisableMapEnter = true;
				DoQuestCheckDelay("CanEnterToMap", 400);
			}
		break;

		case "SpanishAttack_AfterBattle":
		/*if (!Group_isDead("JamaykaSquadron"))
			{
            	Group_SetTaskNone("JamaykaSquadron");
            }*/
			Log_QuestInfo("Испанская эскадра разбита.");
			pchar.questTemp.State = "SpanishAttack_GoodWork";
			AddQuestRecord("Eng_Line_10_SpanishAttack", "2");
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Jamaica", true);
			pchar.quest.SpanishAttack_DieHard.over = "yes";
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;

		case "SpanishAttack_DieHard":
		/*if (!Group_isDead("JamaykaSquadron"))
            {
            	Group_SetTaskNone("JamaykaSquadron");
            } */
			Log_QuestInfo("Свалил с поля боя, линейке конец.");
			pchar.questTemp.State = "QuestLineBreake";
			AddQuestRecord("Eng_Line_10_SpanishAttack", "3");
			CloseQuestHeader("Eng_Line_10_SpanishAttack");
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Jamaica", true);
			pchar.quest.SpanishAttack_AfterBattle.over = "yes";
			SetCaptureTownByNation("PortRoyal", SPAIN);
			UpdateRelations();
			RefreshBattleInterface();
			SetGovenourToCity(ENGLAND, "PortSpein");
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;

		//==========================   Квест N12, Встреча полковника Линча и арест Мэдифорда ========================
		case "ColonelLinch_IntoTheResidence":
			sld = GetCharacter(NPC_GenerateCharacter("Thomas_Linch", "ThomasLinch", "man", "man", 30, ENGLAND, 10, true));
			sld.name = FindPersonalName("Thomas_Linch_name");
			sld.lastname = FindPersonalName("Thomas_Linch_lastname");
			sld.Dialog.Filename = "Quest\EngLineNpc_1.c";
			sld.greeting = "Gr_military";
			ChangeCharacterAddressGroup(sld, "SentJons_townhall", "goto", "goto5");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar("Thomas_Linch", "", 0.0, 1.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		break;

		case "ColonelLinch_AfterFight":
			pchar.nation = ENGLAND;
			Ship_FlagRefresh(PChar); //флаг на лету
			bDisableFastReload = false; // открыть переходы.
			chrDisableReloadToLocation = false; // открыть выход из локации.
			pchar.questTemp.State = "ColonelLinch_ModifordArrested";
			//LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
			sld = GetCharacter(NPC_GenerateCharacter("Thomas_Modiford", "Modyford", "man", "man", 10, ENGLAND, 40, false));
			sld.name = FindPersonalName("Thomas_Modiford_name");
			sld.lastname = FindPersonalName("Thomas_Modiford_lastname");
			sld.Dialog.Filename = "Quest\EngLineNpc_2.c";
			sld.dialog.currentnode = "You_baster";
			LAi_SetImmortal(sld, true);
			FaceMaker(sld);
			SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
			DoReloadCharacterToLocation("PortRoyal_prison", "goto", "goto23");
			ChangeCharacterAddressGroup(sld, "PortRoyal_prison", "goto", "goto9");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, Pchar, "", 1.5, 0);
			pchar.quest.ColonelLinch_Exit.win_condition.l1 = "ExitFromLocation";
			pchar.quest.ColonelLinch_Exit.win_condition.l1.location = pchar.location;
			pchar.quest.ColonelLinch_Exit.win_condition = "ColonelLinch_Exit";
		break;

		case "ColonelLinch_Exit":
			sld = characterFromID("eng_guber");   //  Англ.губер будет Томасом Линчем.
			sld.model = "ThomasLinch";
			sld.name = FindPersonalName("Thomas_Linch_name");
			sld.lastname = FindPersonalName("Thomas_Linch_lastname");
			sld.model.animation = "man";
			SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
			FaceMaker(sld);
			SetGovenourToCity(ENGLAND, "PortRoyal");
			AddQuestRecord("Eng_Line_12_ColonelLinch", "3");
//			LAi_SetHuberStayType(sld);
			LAi_SetImmortal(sld, false);
			LAi_SetImmortal(characterFromID("PortRoyal_Mayor"), false);
			AddLandQuestmark_Main(CharacterFromID("eng_guber"), "Eng_Line");
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  END Английская линейка
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  START Голландская линейка
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//==========================   Квест N1, доставка Аарона Мендеса Чумакейро ========================
		case "SeekChumakeiro_intoMarigoHouse":
			Log_QuestInfo("Выручаем Аарона из беды.");
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			LAi_group_Delete("EnemyFight");
			arrayNPCModelHow = 0;
			for (i = 1; i <= 2; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bandit" + i, "citiz_" + (rand(9) + 51), "man", "man", 20, PIRATE, 0, true)); //watch_quest_moment
				SetNPCModelUniq(sld, "mercenary", MAN);
				FantomMakeCoolFighter(sld, 18, 70, 60, BLADE_LONG, "pistol2", 10);
				LAi_SetWarriorType(sld);
				LAi_warrior_DialogEnable(sld, false);
				sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Marigo_houseF1", "goto", "goto" + i);
			}
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "SeekChumakeiro_intoResidence":
			sld = characterFromID("Chumakeiro");                    //  Чумакейро в резиденции губернатора
			ChangeCharacterAddressGroup(sld, "Villemstad_townhall2", "goto", "goto2");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar("Chumakeiro", "", 0.0, 1.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		break;

		//==========================   Квест N4, защита форта Оранж   ========================
		case "DefenceOrange_FightNearJamaica":
			if (GetQuestPastDayParam("questTemp") < 12)
			{
				Log_QuestInfo("Установлены английские корабли.");
				Island_SetReloadEnableGlobal("Jamaica", false);
				//bQuestDisableMapEnter = true;
				Group_FindOrCreateGroup("Eng_Attack");
				Group_SetType("Eng_Attack", "war");
				// ==> Английские кэпы
				for (i = 1; i <= 3; i++)
				{
					switch (i)
					{
						case 1:
							ShipType = SHIP_FRIGATE;
							Model = "navy_off_eng_4";
							iRank = 23;
							Blade = "blade33";
						break;
						case 2:
							ShipType = SHIP_BRIG;
							Model = "navy_off_eng_2";
							iRank = 19;
							Blade = "blade28";
						break;
						case 3:
							ShipType = SHIP_CORVETTE;
							Model = "navy_off_eng_3";
							iRank = 21;
							Blade = "blade24";
						break;
					}
					sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, Model, "man", "man", iRank, ENGLAND, 0, true));
					FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_LBS_BY_SHIP, 80, 70, 95);
					FantomMakeCoolFighter(sld, iRank, 70, 50, Blade, "pistol3", 75);
					Group_AddCharacter("Eng_Attack", "CaptainAttack_" + i);
				}
				// ==> стравливание
				Group_SetGroupCommander("Eng_Attack", "CaptainAttack_1");
				Group_SetTaskAttack("Eng_Attack", PLAYER_GROUP);
				Group_SetAddress("Eng_Attack", "Jamaica", "quest_ships", "quest_ship_8");
				Group_LockTask("Eng_Attack");
				// ==> прерывание на убиение эскадры
				pchar.quest.DefenceOrange_AfterBattle.win_condition.l1 = "Group_Death";
				pchar.quest.DefenceOrange_AfterBattle.win_condition.l1.group = "Eng_Attack";
				pchar.quest.DefenceOrange_AfterBattle.win_condition = "DefenceOrange_AfterBattle";
				pchar.quest.DefenceOrange_DieHard.win_condition.l1 = "MapEnter";
				pchar.quest.DefenceOrange_DieHard.win_condition = "DefenceOrange_DieHard";
			}
			else
			{
				SetLocationCapturedState("FortOrange_town", true);
				pchar.questTemp.State = "DefenceOrange_LateRiseOrange";
				//--> огонь и пламень
				locations[FindLocation("FortOrange_town")].hidden_effects = true;
				locations[FindLocation("FortOrange_ExitTown")].hidden_effects = true;
				//<-- огонь и пламень
				Log_QuestInfo("Не успел прибыть вовремя, форт Оранж разорен.");
				AddQuestRecord("Hol_Line_4_DefenceOrange", "3");
				AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex", GetSexPhrase("", "а"));
			}
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;

		case "DefenceOrange_AfterBattle":
			Log_QuestInfo("Английская эскадра разбита, теперь очередь за десантом.");
			AddQuestRecord("Hol_Line_4_DefenceOrange", "2");
			pchar.questTemp.State = "DefenceOrange_SquadronDestroyed";
			group_DeleteGroup("Eng_Attack");
			Island_SetReloadEnableGlobal("Jamaica", true);
			bQuestDisableMapEnter = false;
			Pchar.quest.DefenceOrange_FightInShore.win_condition.l1 = "location";
			Pchar.quest.DefenceOrange_FightInShore.win_condition.l1.location = "Shore35";
			Pchar.quest.DefenceOrange_FightInShore.win_condition = "DefenceOrange_FightInShore";
		break;

		case "DefenceOrange_FightInShore":
			Log_QuestInfo("Схватка с английским десантом на берегу.");
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			GetCharacterPos(pchar, &locx, &locy, &locz);
			for (i = 1; i <= 15; i++)
			{
				if (i == 3 || i == 7 || i == 11)
				{
					Model = "navy_off_eng_" + (rand(1) + 3);
					Blade = "blade24";
					iRank = 25;
					Gun = "pistol4";
				}
				else
				{
					Model = "navy_eng_" + (rand(7) + 9);
					iRank = 20;
					Blade = BLADE_LONG;
					Gun = "pistol3";
				}
				sld = GetCharacter(NPC_GenerateCharacter("Solder" + i, Model, "man", "man", 25, ENGLAND, 0, true)); //элитные солдаты
				FantomMakeCoolFighter(sld, iRank, 70, 60, Blade, Gun, 70);

				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Shore35", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
			}
			for (i = 1; i <= 8; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("pirate_" + i, "sold_hol_" + (rand(7) + 9), "man", "man", 25, HOLLAND, 0, true));
				FantomMakeCoolFighter(sld, iRank, 60, 50, Blade, Gun, 50);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				sTemp = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
				if (sTemp == "") sTemp = LAi_FindNearestLocator("goto", locx, locy, locz);
				ChangeCharacterAddressGroup(sld, "Shore35", "goto", sTemp);
			}
			LAi_group_SetLookRadius("EnemyFight", 100);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			Pchar.quest.DefenceOrange_FightInExitTown.win_condition.l1 = "location";
			Pchar.quest.DefenceOrange_FightInExitTown.win_condition.l1.location = "FortOrange_ExitTown";
			Pchar.quest.DefenceOrange_FightInExitTown.win_condition = "DefenceOrange_FightInExitTown";
		break;

		case "DefenceOrange_FightInExitTown":
			Log_QuestInfo("Схватка с английским десантом у форта Оранж.");
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			GetCharacterPos(pchar, &locx, &locy, &locz);
			for (i = 1; i <= 18; i++)
			{
				if (i == 3 || i == 7 || i == 11 || i == 17)
				{
					Model = "off_eng_" + (rand(1) + 3);
					Blade = "blade24";
					iRank = 25;
					Gun = "pistol4";
				}
				else
				{
					Model = "sold_eng_" + (rand(7) + 9);
					iRank = 20;
					Blade = BLADE_LONG;
					Gun = "pistol3";
				}
				sld = GetCharacter(NPC_GenerateCharacter("Solder" + i, Model, "man", "man", 25, ENGLAND, 0, true));
				FantomMakeCoolFighter(sld, iRank, 100, 70, Blade, Gun, 70);

				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			}
			for (i = 1; i <= 15; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("pirate_" + i, "sold_hol_" + (rand(7) + 9), "man", "man", 25, HOLLAND, 0, true));
				FantomMakeCoolFighter(sld, iRank, 60, 50, Blade, Gun, 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "rld", LAi_FindNearestLocator("rld", locx, locy, locz));
			}
			LAi_group_SetLookRadius("EnemyFight", 100);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "DefenceOrange_WeWon");
		break;

		case "DefenceOrange_WeWon":
			chrDisableReloadToLocation = false; // открыть выход из локации.
			Log_QuestInfo("Английский десант уничтожен.");
			AddQuestRecord("Hol_Line_4_DefenceOrange", "4");
			pchar.questTemp.State = "DefenceOrange_LandingDestroyed";
			pchar.quest.DefenceOrange_DieHard.over = "yes";
			//==> чтобы все были просто счастливы и сразу.
			QuestSetCurrentNode("FortOrange_Mayor", "DefenceOrange");
			QuestSetCurrentNode("FortOrange_waitress", "DefenceOrange");
			QuestSetCurrentNode("FortOrange_tavernkeeper", "DefenceOrange");
			QuestSetCurrentNode("FortOrange_trader", "DefenceOrange");
		break;

		case "DefenceOrange_DieHard":
			pchar.quest.DefenceOrange_AfterBattle.over = "yes";
			pchar.quest.DefenceOrange_FightInShore.over = "yes";
			AddQuestRecord("Hol_Line_4_DefenceOrange", "5");
			AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex", GetSexPhrase("", "ла"));
			AddQuestUserData("Hol_Line_4_DefenceOrange", "sSex1", GetSexPhrase("", "а"));
			SetLocationCapturedState("FortOrange_town", true);
			group_DeleteGroup("Eng_Attack");
			Island_SetReloadEnableGlobal("Jamaica", true);
			bQuestDisableMapEnter = false;
			pchar.questTemp.State = "DefenceOrange_DieHard";
			//--> огонь и пламень
			locations[FindLocation("FortOrange_town")].hidden_effects = true;
			locations[FindLocation("FortOrange_ExitTown")].hidden_effects = true;
		//<-- огонь и пламень
		break;

		//==========================   Квест N5, сопровождение трёх флейтов до Ла Веги и обратно  ========================
		case "ThreeFleutes_TalkIntoLaVega":
			chrDisableReloadToLocation = true;
			//===> Эдвард убит, теперь Ла Вегой рулит капитан Купер.
			sld = characterFromID("Edward Mansfield");
			sld.name = FindPersonalName("EdwardMansfield_name");
			sld.lastname = FindPersonalName("EdwardMansfield_lastname");
			sld.model.animation = "man";
			sld.model = "officer_28"; //watch_quest_moment //ещё есть citiz_57
			SendMessage(sld, "lss", MSG_CHARACTER_SETMODEL, sld.model, sld.model.animation);
			FaceMaker(sld);
			//===> к ГГ подходит перец и сообщает о смерти Мэнсфилда
			sld = GetCharacter(NPC_GenerateCharacter("Talker", "officer_12", "man", "man", 25, PIRATE, 0, true)); //watch_quest_moment
			sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
			LAi_SetStayTypeNoGroup(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, "LaVega_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.5, 0);
		break;

		case "ThreeFleutes_BackToCuracao":
			Log_QuestInfo("Засада испанцев, к бою.");
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //ссорим ГГ и испанцев, а то они в нейтрале.
			SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY);
			Island_SetReloadEnableGlobal("Hispaniola1", false);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			// ==> Испанские кэпы
			for (i = 1; i <= 4; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_LINESHIP;
						Model = "navy_off_spa_5";
						iRank = 31;
						Blade = "blade24";
					break;
					case 2:
						ShipType = SHIP_GALEON;
						Model = "navy_off_spa_2";
						iRank = 26;
						Blade = "blade28";
					break;
					case 3:
						ShipType = SHIP_CARAVEL;
						Model = "navy_off_spa_3";
						iRank = 28;
						Blade = "blade33";
					break;
					case 4:
						ShipType = SHIP_GALEON_H;
						Model = "navy_off_spa_4";
						iRank = 30;
						Blade = "blade33";
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, Model, "man", "man", iRank, SPAIN, 0, true));
				FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 90, 80, 80);
				FantomMakeCoolFighter(sld, iRank, 90, 70, Blade, "pistol3", 75);
				Group_AddCharacter("Spa_Attack", "CaptainAttack_" + i);
			}
			// ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Hispaniola1", "", "");
			Group_LockTask("Spa_Attack");
			// ==> прерывание на убиение эскадры
			pchar.quest.ThreeFleutes_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.ThreeFleutes_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.ThreeFleutes_AfterBattle.win_condition = "ThreeFleutes_AfterBattle";
			pchar.quest.ThreeFleutes_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.ThreeFleutes_DieHard.win_condition = "ThreeFleutes_DieHard";
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;

		case "ThreeFleutes_AfterBattle":
			Island_SetReloadEnableGlobal("Hispaniola1", true);
			pchar.quest.ThreeFleutes_DieHard.over = "yes";
			group_DeleteGroup("Spa_Attack");
			//--> сколько у нас флейтов из компаньонов
			iTemp = 0;
			for (i = 1; i <= COMPANION_MAX; i++)
			{
				ShipType = GetCompanionIndex(pchar, i);
				if (ShipType != -1)
				{
					sld = GetCharacter(ShipType);
					ShipType = sti(sld.ship.type);
					iRank = sti(RealShips[ShipType].basetype);
					if (iRank == SHIP_FLEUT) iTemp++;
				}
			}
			//--> результат в СЖ
			if (iTemp < 3)
			{
				pchar.questTemp.State = "ThreeFleutes_LostFleuts";
				if (iTemp < 1)
				{
					AddQuestRecord("Hol_Line_5_ThreeFleutes", "6");
					AddQuestUserData("Hol_Line_5_ThreeFleutes", "sSex", GetSexPhrase("", "а"));
				}
				else
				{
					AddQuestRecord("Hol_Line_5_ThreeFleutes", "5");
					AddQuestUserData("Hol_Line_5_ThreeFleutes", "QtyFleutes", iTemp);
				}
			}
			else
			{
				AddQuestRecord("Hol_Line_5_ThreeFleutes", "4");
				AddQuestUserData("Hol_Line_5_ThreeFleutes", "sSex", GetSexPhrase("", "а"));
				pchar.questTemp.State = "ThreeFleutes_AllFleuts";
			}
		break;

		case "ThreeFleutes_DieHard":
			pchar.quest.ThreeFleutes_AfterBattle.over = "yes";
			AddQuestRecord("Hol_Line_5_ThreeFleutes", "3");
			pchar.questTemp.State = "ThreeFleutes_DieHard";
			Island_SetReloadEnableGlobal("Hispaniola1", true);
			group_DeleteGroup("Spa_Attack");
			for (i = 1; i <= 3; i++)
			{
				sld = characterFromID("Captain_" + i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
			}
		break;

		//==========================   Квест N7, доставка депеши на Тортугу  ========================
		case "DelivLettTortuga_SnapMeeting":
			chrDisableReloadToLocation = true;
			Log_QuestInfo("Встреча с незнакомцем.");
			sld = GetCharacter(NPC_GenerateCharacter("Stranger_HL7", "citiz_18", "man", "man", 15, FRANCE, 0, false));
			sld.Dialog.Filename = "Quest\HolLineNpc_1.c";
			sld.name = FindPersonalName("Stranger_HL7_name");
			sld.lastname = FindPersonalName("Stranger_HL7_lastname");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "DelivLettTortuga_2KickPhar":
			LAi_SetCitizenType(characterFromId("AntonioDeBarras"));
			LAi_ActorAnimation(pchar, "death_2", "DelivLettTortuga_3KickPhar", 3.0);
		break;

		case "DelivLettTortuga_3KickPhar":
			LAi_ActorSetLayMode(pchar);
			DoQuestCheckDelay("DelivLettTortuga_KickPhar", 1.0);
			sld = characterFromID("AntonioDeBarras");
			ChangeCharacterAddress(sld, "None", "");
		break;

		case "DelivLettTortuga_KickPhar":
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_14"), "", 0, 3);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим час
			RecalculateJumpTable();
			pchar.questTemp.State = "DelivLettTortuga_AfterRape";
			AddLandQuestmark_Main(CharacterFromID("Tortuga_tavernkeeper"), "Hol_Line");
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Hol_Line");
			//LAi_SetStayType(sld);
			TakeItemFromCharacter(pchar, "letter_HolLineQ7_1");
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "4");
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation("Tortuga_tavern_upstairs")], false);
		break;

		case "DelivLettTortuga_BrigTimeOver":
			pchar.quest.DelivLettTortuga_AttackBrig.over = "yes";
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "7");
			pchar.questTemp.State.KingResult = "BrigNotFound"; //флаг на вообще не нашёл
		break;

		case "DelivLettTortuga_AttackBrig":
			Log_QuestInfo("Бриг найден, на абордаж!");
			pchar.quest.DelivLettTortuga_BrigTimeOver.over = "yes";
			//SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY); //ссорим ГГ и пиратов.
			Island_SetReloadEnableGlobal("PuertoRico", false);
			Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "trade");
			sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "citiz_60", "man", "man", 30, PIRATE, 0, true)); //watch_quest_moment; опять циклоп, можно кого угодно ставить
			sld.Dialog.Filename = "Quest\HolLineNpc_2.c";
			sld.DontRansackCaptain = true;
			FantomMakeCoolSailor(sld, SHIP_BRIG, FindPersonalName("CaptainAttack_1_ship4"), CANNON_TYPE_CANNON_LBS20, 65, 70, 75);
			FantomMakeCoolFighter(sld, 30, 80, 40, "blade24", "pistol3", 90);
			Group_AddCharacter("Pirate_Attack", "CaptainAttack_1");
			AddLandQuestmark_Main(sld, "Hol_Line");
			// ==> стравливание
			Group_SetGroupCommander("Pirate_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "PuertoRico", "", "");
			Group_LockTask("Pirate_Attack");
			// ==> прерывания
			pchar.quest.DelivLettTortuga_AfterBrigSunk.win_condition.l1 = "Character_sink";
			pchar.quest.DelivLettTortuga_AfterBrigSunk.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.DelivLettTortuga_AfterBrigSunk.win_condition = "DelivLettTortuga_AfterBrigSunk";
			pchar.quest.DelivLettTortuga_BrigDieHard.win_condition.l1 = "MapEnter";
			pchar.quest.DelivLettTortuga_BrigDieHard.win_condition = "DelivLettTortuga_BrigDieHard";
		break;

		case "DelivLettTortuga_BrigDieHard":
			pchar.quest.DelivLettTortuga_AfterBrigSunk.over = "yes";
			group_DeleteGroup("Pirate_Attack");
			Island_SetReloadEnableGlobal("PuertoRico", true);
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "7");
			pchar.questTemp.State.KingResult = "BrigNotFound"; //флаг на вообще не нашёл
		break;

		case "DelivLettTortuga_AfterBrigSunk":
			pchar.quest.DelivLettTortuga_BrigDieHard.over = "yes";
			Island_SetReloadEnableGlobal("PuertoRico", true);
			group_DeleteGroup("Pirate_Attack");
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "6");
			pchar.questTemp.State.KingResult = "BrigSunk"; //флаг на утонул
		break;

		case "DelivLettTortuga_WarshipTimeOver":
			pchar.quest.DelivLettTortuga_AttackWarship.over = "yes";
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "9");
		break;

		case "DelivLettTortuga_AttackWarship":
			Log_QuestInfo("Военный галеон найден, на абордаж!");
			pchar.quest.DelivLettTortuga_WarshipTimeOver.over = "yes";
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //ссорим ГГ и испанцев.
			SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY);
			Island_SetReloadEnableGlobal("SantaCatalina", false);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			Group_AddCharacter("Spa_Attack", "AntonioDeBarras");
			AddLandQuestmark_Main(CharacterFromID("AntonioDeBarras"), "Hol_Line");
			// ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "AntonioDeBarras");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "SantaCatalina", "", "");
			Group_LockTask("Spa_Attack");
			// ==> прерывания
			pchar.quest.DelivLettTortuga_AfterWarshipSunk.win_condition.l1 = "Character_sink";
			pchar.quest.DelivLettTortuga_AfterWarshipSunk.win_condition.l1.character = "AntonioDeBarras";
			pchar.quest.DelivLettTortuga_AfterWarshipSunk.win_condition = "DelivLettTortuga_AfterWarshipSunk";
			pchar.quest.DelivLettTortuga_WarshipDieHard.win_condition.l1 = "MapEnter";
			pchar.quest.DelivLettTortuga_WarshipDieHard.win_condition = "DelivLettTortuga_WarshipDieHard";
		break;

		case "DelivLettTortuga_WarshipDieHard":
			pchar.quest.DelivLettTortuga_AfterWarshipSunk.over = "yes";
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("SantaCatalina", true);
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "9");
		break;

		case "DelivLettTortuga_AfterWarshipSunk":
			pchar.quest.DelivLettTortuga_WarshipDieHard.over = "yes";
			Island_SetReloadEnableGlobal("SantaCatalina", true);
			group_DeleteGroup("Spa_Attack");
			AddQuestRecord("Hol_Line_7_DelivLettTortuga", "10");
			pchar.questTemp.State.KingResult = "WarshipSunk"; //флаг на утонул
		break;

		//==========================   Квест N8, поиски Библии  ========================
		case "SeekBible_SaveDeGraf":
			Log_QuestInfo("Нужно спасти фрегат де Графа!");
			Island_SetReloadEnableGlobal("Cartahena", false);
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //ссорим ГГ и испанцев.
			SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			// ==> Испанские кэпы
			for (i = 1; i <= 5; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_BATTLESHIP;
						Model = "navy_off_spa_5";
						iRank = 28;
						Blade = "blade24";
					break;
					case 2:
						ShipType = SHIP_GALEON_H;
						Model = "navy_off_spa_4";
						iRank = 26;
						Blade = "blade28";
					break;
					case 3:
						ShipType = SHIP_LINESHIP;
						Model = "navy_off_spa_4";
						iRank = 34;
						Blade = "blade28";
					break;
					case 4:
						ShipType = SHIP_GALEON_H;
						Model = "navy_off_spa_3";
						iRank = 30;
						Blade = "blade33";
					break;
					case 5:
						ShipType = SHIP_CARAVEL;
						Model = "navy_off_spa_2";
						iRank = 36;
						Blade = "blade28";
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, Model, "man", "man", iRank, SPAIN, 0, true));
				FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 95, 90, 85);
				FantomMakeCoolFighter(sld, iRank, 96, 80, Blade, "pistol3", 85);
				Group_AddCharacter("Spa_Attack", "CaptainAttack_" + i);
			}
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Cartahena", "", "");
			// ==> де Граф
			sld = GetCharacter(NPC_GenerateCharacter("LoranDeGraf", "citiz_4", "man", "man", 45, HOLLAND, -1, true)); //watch_quest_moment; аналога _14 из ванилы не имеем
			sld.DeckDialogNode = "First time";
			sld.Dialog.Filename = "Quest\HolLineNpc_2.c";
			sld.name = FindPersonalName("LoranDeGraf_name");
			sld.lastname = FindPersonalName("LoranDeGraf_lastname");
			sld.greeting = "Gr_MiddPirate";
			sld.ShipEnemyDisable = true; //при попадании не враждебен
			sld.Abordage.Enable = false; // НЕЛЬЗЯ!
			LAi_SetStayTypeNoGroup(sld);
			FantomMakeCoolSailor(sld, SHIP_FRIGATE_H, FindPersonalName("LoranDeGraf_ship"), CANNON_TYPE_CANNON_LBS32, 90, 80, 80);
			FantomMakeCoolFighter(sld, 45, 80, 80, "topor2", "pistol3", 100);
			Group_AddCharacter("Quest_Group", "LoranDeGraf");
			Group_SetType("Quest_Group", "war");
			Group_SetGroupCommander("Quest_Group", "LoranDeGraf");
			Group_SetPursuitGroup("Quest_Group", PLAYER_GROUP);
			Group_SetAddress("Quest_Group", "Cartahena", "", "");
			AddLandQuestmark_Main(sld, "Hol_Line");
			// ==> стравливание
			Group_SetTaskAttack("Spa_Attack", "Quest_Group");
			Group_SetTaskAttack("Quest_Group", "Spa_Attack");
			Group_LockTask("Quest_Group");
			Group_LockTask("Spa_Attack");
			pchar.quest.SeekBible_WeWon.win_condition.l1 = "Group_Death";
			pchar.quest.SeekBible_WeWon.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SeekBible_WeWon.win_condition = "SeekBible_WeWon";
			pchar.quest.SeekBible_NotSavedDeGraf.win_condition.l1 = "NPC_Death";
			pchar.quest.SeekBible_NotSavedDeGraf.win_condition.l1.character = "LoranDeGraf";
			pchar.quest.SeekBible_NotSavedDeGraf.win_condition = "SeekBible_NotSavedDeGraf";
			pchar.quest.SeekBible_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.SeekBible_DieHard.win_condition = "SeekBible_DieHard";
			AddLandQuestmark_Main(characterFromId("Chumakeiro"), "Hol_Line");
		break;

		case "SeekBible_WeWon":
			pchar.quest.SeekBible_NotSavedDeGraf.over = "yes";
			pchar.quest.SeekBible_DieHard.over = "yes";
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Cartahena", true);
			AddQuestRecord("Hol_Line_8_SeekBible", "8");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex1", GetSexPhrase("", "а"));
			pchar.questTemp.State = "SeekBible_WeWon";
		break;

		case "SeekBible_DieHard":
			if (pchar.questTemp.State == "SeekBible_DeGrafIsDead")
			{
				group_DeleteGroup("Spa_Attack");
			}
			else
			{
				pchar.quest.SeekBible_WeWon.over = "yes";
				pchar.quest.SeekBible_NotSavedDeGraf.over = "yes";
				group_DeleteGroup("Spa_Attack");
				group_DeleteGroup("Quest_Group");
				Island_SetReloadEnableGlobal("Cartahena", true);
				AddQuestRecord("Hol_Line_8_SeekBible", "6");
				AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("ся", "ась"));
				AddQuestUserData("Hol_Line_8_SeekBible", "sSex1", GetSexPhrase("", "ла"));
				pchar.questTemp.State = "SeekBible_DeGrafDieHard";
			}
		break;

		case "SeekBible_NotSavedDeGraf":
			pchar.quest.SeekBible_WeWon.over = "yes";
			Island_SetReloadEnableGlobal("Cartahena", true);
			AddQuestRecord("Hol_Line_8_SeekBible", "7");
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("Hol_Line_8_SeekBible", "sSex1", GetSexPhrase("", "а"));
			pchar.questTemp.State = "SeekBible_DeGrafIsDead";
		break;

		case "SeekBible_DeGrafToTavern":
			sld = characterFromId("LoranDeGraf");
			FreeSitLocator("Tortuga_tavern", "sit3");
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit3");
			LAi_SetSitTypeNoGroup(sld);
			group_DeleteGroup("Quest_Group");
		break;

		//==========================   Квест N10, Оборона Кюрасао.  ========================
		case "SpaAttackCuracao_Battle":
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY); //ссорим ГГ и испанцев.
			SetNationRelationBoth(SPAIN, HOLLAND, RELATION_ENEMY);
			Log_QuestInfo("Испанская эскадра установлена, будет крутой бой.");
			Island_SetReloadEnableGlobal("Curacao", false);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			// ==> Испанские кэпы
			for (i = 1; i <= 7; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_MANOWAR;
						Model = "navy_off_spa_6";
						iRank = 45;
						Blade = "blade33";
					break;
					case 2:
						ShipType = SHIP_BATTLESHIP;
						Model = "navy_off_spa_5";
						iRank = 35;
						Blade = "blade28";
					break;
					case 3:
						ShipType = SHIP_WARSHIP;
						Model = "navy_off_spa_5";
						iRank = 33;
						Blade = "blade24";
					break;
					case 4:
						ShipType = SHIP_LINESHIP;
						Model = "navy_off_spa_4";
						iRank = 30;
						Blade = "blade34";
					break;
					case 5:
						ShipType = SHIP_GALEON_H;
						Model = "navy_off_spa_3";
						iRank = 29;
						Blade = "topor2";
					break;
					case 6:
						ShipType = SHIP_FRIGATE;
						Model = "navy_off_spa_2";
						iRank = 27;
						Blade = "topor2";
					break;
					case 7:
						ShipType = SHIP_CORVETTE;
						Model = "navy_off_spa_1";
						iRank = 25;
						Blade = "topor2";
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, Model, "man", "man", iRank, SPAIN, 0, true));
				//пришлось делать ветвление, т.к. корвету давать 32ф пушки жирно,
				//а если всей эскадре ставить реальные пушки, то получится жир, там вплоть до 42ф будет
				if (ShipType == SHIP_CORVETTE) FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_LBS_BY_SHIP, 100, 95, 95);
				else FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 100, 95, 95);
				FantomMakeCoolFighter(sld, iRank, 100, 90, Blade, "pistol3", 150);
				Group_AddCharacter("Spa_Attack", "CaptainAttack_" + i);
			}
			// ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Curacao", "", "");
			Group_LockTask("Spa_Attack");
			// натравим сторожевиков
			//Group_SetTaskAttack("CuracaoSquadron", "Spa_Attack"); // обязательно потом сбросить, иначе вылет
			//Group_LockTask("CuracaoSquadron");
			// ==> прерывание на убиение эскадры
			pchar.quest.SpaAttackCuracao_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.SpaAttackCuracao_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SpaAttackCuracao_AfterBattle.win_condition = "SpaAttackCuracao_AfterBattle";
			pchar.quest.SpaAttackCuracao_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.SpaAttackCuracao_DieHard.win_condition = "SpaAttackCuracao_DieHard";

			if (pchar.location.from_sea == "Villemstad_town")
			{
				bQuestDisableMapEnter = true;
				DoQuestCheckDelay("CanEnterToMap", 400);
			}

			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;

		case "SpaAttackCuracao_AfterBattle":
		/*if (!Group_isDead("CuracaoSquadron"))
			{
            	Group_SetTaskNone("CuracaoSquadron");
            }*/
			Log_QuestInfo("Испанская эскадра разбита.");
			pchar.questTemp.State = "SpaAttackCuracao_GoodWork";
			AddQuestRecord("Hol_Line_10_SpaAttackCuracao", "2");
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Curacao", true);
			pchar.quest.SpaAttackCuracao_DieHard.over = "yes";
		break;

		case "SpaAttackCuracao_DieHard":
		/*if (!Group_isDead("CuracaoSquadron"))
            {
            	Group_SetTaskNone("CuracaoSquadron");
            } */
			Log_QuestInfo("Свалил с поля боя, линейке конец.");
			pchar.questTemp.State = "QuestLineBreake";
			AddQuestRecord("Hol_Line_10_SpaAttackCuracao", "3");
			CloseQuestHeader("Hol_Line_10_SpaAttackCuracao");
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Curacao", true);
			pchar.quest.SpaAttackCuracao_AfterBattle.over = "yes";
			SetCaptureTownByNation("Villemstad", SPAIN);
			UpdateRelations();
			RefreshBattleInterface();
			SetGovenourToCity(HOLLAND, "Marigo");
			RemoveLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;

		//==========================   Квест N11, Спасти Мариго от нападения испанцев.  ========================
		case "SpaAttackSentMartin_YouLate":
			Log_QuestInfo("Опоздал. Мариго захвачен испанцами.");
			pchar.questTemp.State = "SpaAttackSentMartin_Late";
			AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "4");
			AddQuestUserData("Hol_Line_11_SpaAttackSentMartin", "sSex", GetSexPhrase("", "а"));
			pchar.quest.SpaAttackSentMartin_Battle.over = "yes";
			SetCaptureTownByNation("Marigo", SPAIN);
			UpdateRelations();
			RefreshBattleInterface();

			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;

		case "SpaAttackSentMartin_Battle":
			Log_QuestInfo("Испанская эскадра установлена, будет крутой бой.");
			pchar.quest.SpaAttackSentMartin_YouLate.over = "yes";
			Island_SetReloadEnableGlobal("SentMartin", false);
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			// ==> Испанские кэпы
			for (i = 1; i <= 8; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_MANOWAR;
						Model = "navy_off_spa_6";
						iRank = 42;
						Blade = "blade33";
					break;
					case 2:
						ShipType = SHIP_GALEON_H;
						Model = "navy_off_spa_3";
						iRank = 32;
						Blade = "blade33";
					break;
					case 3:
						ShipType = SHIP_WARSHIP;
						Model = "navy_off_spa_5";
						iRank = 39;
						Blade = "blade28";
					break;
					case 4:
						ShipType = SHIP_BATTLESHIP;
						Model = "navy_off_spa_4";
						iRank = 35;
						Blade = "blade24";
					break;
					case 5:
						ShipType = SHIP_LINESHIP;
						Model = "navy_off_spa_5";
						iRank = 33;
						Blade = "blade34";
					break;
					case 6:
						ShipType = SHIP_FRIGATE;
						Model = "navy_off_spa_3";
						iRank = 29;
						Blade = "blade26";
					break;
					case 7:
						ShipType = SHIP_CORVETTE;
						Model = "navy_off_spa_2";
						iRank = 28;
						Blade = "blade28";
					break;
					case 8:
						ShipType = SHIP_GALEON;
						Model = "navy_off_spa_1";
						iRank = 27;
						Blade = "blade32";
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, Model, "man", "man", iRank, SPAIN, 0, true));
				//пришлось делать ветвление, т.к. корвету и фрегату давать 32ф пушки жирно,
				//а если всей эскадре ставить реальные пушки, то получится жир, там вплоть до 42ф будет
				if (ShipType == SHIP_CORVETTE || ShipType == SHIP_FRIGATE) FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_LBS_BY_SHIP, 100, 95, 95);
				else FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_CANNON_LBS32, 100, 95, 95);
				FantomMakeCoolFighter(sld, iRank, 100, 90, Blade, "pistol3", 150);
				Group_AddCharacter("Spa_Attack", "CaptainAttack_" + i);
			}
			// ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "SentMartin", "quest_ships", "quest_ship_4");
			Group_LockTask("Spa_Attack");
			// натравим сторожевиков
			//Group_SetTaskAttack("SentMartinSquadron", "Spa_Attack"); // обязательно потом сбросить, иначе вылет
			//Group_LockTask("SentMartinSquadron");
			// ==> прерывание на убиение эскадры
			pchar.quest.SpaAttackSentMartin_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.SpaAttackSentMartin_AfterBattle.win_condition.l1.group = "Spa_Attack";
			pchar.quest.SpaAttackSentMartin_AfterBattle.win_condition = "SpaAttackSentMartin_AfterBattle";
			pchar.quest.SpaAttackSentMartin_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.SpaAttackSentMartin_DieHard.win_condition = "SpaAttackSentMartin_DieHard";

			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;

		case "SpaAttackSentMartin_AfterBattle":
			Log_QuestInfo("Испанская эскадра разбита.");
			pchar.questTemp.State = "SpaAttackSentMartin_GoodWork";
			AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "2");
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("SentMartin", true);
			pchar.quest.SpaAttackSentMartin_DieHard.over = "yes";
		break;

		case "SpaAttackSentMartin_DieHard":
			Log_QuestInfo("Свалил с поля боя, линейке конец.");
			pchar.questTemp.State = "QuestLineBreake";
			AddQuestRecord("Hol_Line_11_SpaAttackSentMartin", "3");
			CloseQuestHeader("Hol_Line_11_SpaAttackSentMartin");
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("SentMartin", true);
			pchar.quest.SpaAttackSentMartin_AfterBattle.over = "yes";
			SetCaptureTownByNation("Marigo", SPAIN);
			UpdateRelations();
			RefreshBattleInterface();
			RemoveLandQuestmark_Main(CharacterFromID("hol_guber"), "Hol_Line");
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  END Голландская линейка
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  START Испанская линейка
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//========================  Квест N2, задание Инквизиции.  =======================
		case "Inquisition_MeetFrancisco":
			chrDisableReloadToLocation = true;
			Log_QuestInfo("Встреча с Франциско.");
			sld = GetCharacter(NPC_GenerateCharacter("Francisco", "priest_4", "man", "man", 15, SPAIN, 0, false));
			sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
			sld.name = FindPersonalName("Francisco_name");
			sld.lastname = FindPersonalName("Francisco_lastname");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, "Santiago_town", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Inquisition_afterFightAndrew":
			LAi_LocationFightDisable(&Locations[FindLocation("Villemstad_bank")], true);
			sld = characterFromId("Villemstad_usurer");
			LAi_IsDead(sld);
			LAi_SetHP(sld, 100, 100);
			sld.location = "Villemstad_Bank";
			sld.location.group = "barmen";
			sld.location.locator = "stay";
			LAi_SetBarmanType(sld);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		break;

		case "Inquisition_LuggerTimeOver":
			pchar.quest.Inquisition_AttackLugger.over = "yes";
			AddQuestRecord("Spa_Line_2_Inquisition", "7");
		break;

		case "Inquisition_AttackLugger":
			Log_QuestInfo("Люггер найден, на абордаж!");
			pchar.quest.Inquisition_LuggerTimeOver.over = "yes";
			//SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY); //ссорим ГГ и пиратов.
			Island_SetReloadEnableGlobal("Jamaica", false);
			Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "trade");
			sld = GetCharacter(NPC_GenerateCharacter("JansenDeFonceicao", "officer_2", "man", "man", 25, PIRATE, -1, true));
			sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
			sld.name = FindPersonalName("JansenDeFonceicao_name");
			sld.lastname = FindPersonalName("JansenDeFonceicao_lastname");
			sld.DontRansackCaptain = true;
			FantomMakeCoolSailor(sld, SHIP_LUGGER_W, FindPersonalName("JansenDeFonceicao_ship"), CANNON_TYPE_CANNON_LBS8, 70, 70, 70);
			FantomMakeCoolFighter(sld, 25, 60, 40, "blade24", "pistol3", 60);
			Group_AddCharacter("Pirate_Attack", "JansenDeFonceicao");
			AddLandQuestmark_Main(sld, "Spa_Line");
			// ==> стравливание
			Group_SetGroupCommander("Pirate_Attack", "JansenDeFonceicao");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "Jamaica", "quest_ships", "quest_ship_7");
			Group_LockTask("Pirate_Attack");
			// ==> прерывания
			pchar.quest.Inquisition_AfterLuggerSink.win_condition.l1 = "NPC_Death";
			pchar.quest.Inquisition_AfterLuggerSink.win_condition.l1.character = "JansenDeFonceicao";
			pchar.quest.Inquisition_AfterLuggerSink.win_condition = "Inquisition_AfterLuggerSink";
			pchar.quest.Inquisition_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.Inquisition_DieHard.win_condition = "Inquisition_DieHard";
		break;

		case "Inquisition_DieHard":
			pchar.quest.Inquisition_LuggerSink.over = "yes";
			group_DeleteGroup("Pirate_Attack");
			Island_SetReloadEnableGlobal("Jamaica", true);
			AddQuestRecord("Spa_Line_2_Inquisition", "7");
		break;

		case "Inquisition_AfterLuggerSink":
			if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
			{
				pchar.quest.Inquisition_DieHard.over = "yes";
				Island_SetReloadEnableGlobal("Jamaica", true);
				group_DeleteGroup("Pirate_Attack");
				AddQuestRecord("Spa_Line_2_Inquisition", "9");
			}
			else
			{
				characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)].id = "JansenDeFonceicao";
			}
		break;

		case "Inquisition_fightForJacow":
			Log_QuestInfo("Яков здесь.");
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			sld = GetCharacter(NPC_GenerateCharacter("Bandit", "citiz_58", "man", "man", 25, PIRATE, 0, true)); //watch_quest_moment
			FantomMakeCoolFighter(sld, 25, 70, 60, "blade21", "pistol2", 30);
			LAi_SetStayType(sld);
			sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
			LAi_group_MoveCharacter(sld, "EnemyFight");
			ChangeCharacterAddressGroup(sld, "Panama_houseSp1", "goto", "goto1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.3);
			Pchar.quest.Inquisition_fightForJacow2.win_condition.l1 = "location";
			Pchar.quest.Inquisition_fightForJacow2.win_condition.l1.location = "Panama_houseSp1_Room";
			Pchar.quest.Inquisition_fightForJacow2.win_condition = "Inquisition_fightForJacow2";
		break;

		case "Inquisition_fightForJacow2":
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			sld = GetCharacter(NPC_GenerateCharacter("JacowDeFonseka", "merch_11", "man", "man", 10, HOLLAND, -1, false));
			ChangeCharacterAddressGroup(sld, "Panama_houseSp1_Room", "goto", "goto4");
			sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
			sld.name = FindPersonalName("Panama_houseSp1_Room_name");
			sld.lastname = FindPersonalName("Panama_houseSp1_Room_lastname");
			LAi_SetImmortal(sld, true);
			LAi_SetStayTypeNoGroup(sld);
			arrayNPCModelHow = 0;
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bandit" + i, "citiz_" + (rand(9) + 51), "man", "man", 25, PIRATE, 0, true)); //watch_quest_moment
				SetNPCModelUniq(sld, "mercenary", MAN);
				FantomMakeCoolFighter(sld, 25, 70, 60, BLADE_LONG, "pistol3", 30);
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Panama_houseSp1_Room", "goto", "goto" + i);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Inquisition_afterFightJacow");
		break;

		case "Inquisition_afterFightJacow":
			chrDisableReloadToLocation = false;
			LAi_SetActorType(pchar);
			sld = characterFromID("JacowDeFonseka");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		break;

		case "Inquisition_fightInDangeon":
			Log_QuestInfo("Со скелетами надо подраться.");
			chrDisableReloadToLocation = true;
			for (i = 1; i <= 40; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Skelet" + i, "Skel" + (rand(3) + 1), "skeleton", "man", 1, PIRATE, 0, true));
				sld.skeleton = "1";
				sld.rank = 1;
				sld.skill.Fencing = 1;
				sld.skill.Pistol = 1;
				LAi_SetHP(sld, 1, 1);
				DeleteAttribute(sld, "Items");
				GiveItem2Character(sld, "blade1");
				EquipCharacterbyItem(sld, "blade1");
				GiveItem2Character(sld, "pistol1");
				EquipCharacterbyItem(sld, "pistol1");
				TakeNItems(sld, "bullet", 1);
				AddItems(sld, "GunPowder", 1);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Bermudes_Dungeon", "monsters", "monster" + i);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Inquisition_afterFightSkel");
		break;

		case "Inquisition_afterFightSkel":
			LocatorReloadEnterDisable("Pirates_Shipyard", "reload2", true);
			chrDisableReloadToLocation = false;
		break;
		//========================  Квест N3, захват Рока Бразильца.  =======================
		case "TakeRockBras_toRock":
			Log_QuestInfo("Корвет Рока найден, на абордаж!");
			pchar.questTemp.State = "TakeRockBras_toNearestMaracaibo";
			pchar.quest.Inquisition_LuggerTimeOver.over = "yes";
			//SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY); //ссорим ГГ и пиратов.
			Island_SetReloadEnableGlobal("Maracaibo", false);
			Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "war");
			sld = GetCharacter(NPC_GenerateCharacter("RockBrasilian", "Roche", "man", "man", 30, PIRATE, -1, true));
			sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
			sld.name = FindPersonalName("RockBrasilian_name");
			sld.lastname = FindPersonalName("RockBrasilian_lastname");
			sld.DontRansackCaptain = true;
			FantomMakeCoolSailor(sld, SHIP_CORVETTE, FindPersonalName("RockBrasilian_ship"), CANNON_TYPE_CULVERINE_LBS24, 100, 95, 90);
			FantomMakeCoolFighter(sld, 30, 90, 90, "blade28", "pistol3", 120);
			Group_AddCharacter("Pirate_Attack", "RockBrasilian");
			AddLandQuestmark_Main(sld, "Spa_Line");
			// ==> стравливание
			Group_SetGroupCommander("Pirate_Attack", "RockBrasilian");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "Maracaibo", "", "");
			Group_LockTask("Pirate_Attack");
			// ==> прерывания
			pchar.quest.TakeRockBras_AfterCorvetteSink.win_condition.l1 = "NPC_Death";
			pchar.quest.TakeRockBras_AfterCorvetteSink.win_condition.l1.character = "RockBrasilian";
			pchar.quest.TakeRockBras_AfterCorvetteSink.win_condition = "TakeRockBras_AfterCorvetteSink";
			pchar.quest.TakeRockBras_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.TakeRockBras_DieHard.win_condition = "TakeRockBras_DieHard";
		break;

		case "TakeRockBras_DieHard":
			pchar.questTemp.State = "TakeRockBras_DieHardRock";
			pchar.quest.TakeRockBras_AfterCorvetteSink.over = "yes";
			group_DeleteGroup("Pirate_Attack");
			Island_SetReloadEnableGlobal("Maracaibo", true);
			AddQuestRecord("Spa_Line_3_RockBrasilian", "3");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;

		case "TakeRockBras_AfterCorvetteSink":
			if (!CheckAttribute(pchar, "GenQuest.LastQuestPrisonerIdx"))
			{
				pchar.questTemp.State = "TakeRockBras_RockSink";
				pchar.quest.TakeRockBras_DieHard.over = "yes";
				Island_SetReloadEnableGlobal("Maracaibo", true);
				group_DeleteGroup("Pirate_Attack");
				AddQuestRecord("Spa_Line_3_RockBrasilian", "4");
				AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
			}
			else
			{
				characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)].id = "RockBrasilian";
			}
		break;
		//========================  Квест N4, Расследование убийства коменданта.  =======================
		case "Sp4Detection_Race_1":
			LAi_LocationDisableMonstersGen("Tortuga_Cave", true); //монстров не генерить
			LAi_LocationDisableOfficersGen("Shore58", true); //офицеров не пускать
			sld = GetCharacter(NPC_GenerateCharacter("AnryDEstre", "BigPirate", "man", "man", 40, FRANCE, 10, false));
			sld.name = FindPersonalName("AnryDEstre_name");
			sld.lastname = FindPersonalName("AnryDEstre_lastname");
			sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
			sld.money = 21340;
			FantomMakeCoolFighter(sld, 40, 100, 100, "blade32", "pistol4", 100);
			TakeNItems(sld, "jewelry7", 1);
			ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto7");
			LAi_SetHP(sld, 1, 1);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorRunToLocation(sld, "reload", "basement1", "Tortuga_Cave", "goto", "goto1", "", -1);
			pchar.quest.Sp4Detection_Race_2.win_condition.l1 = "location";
			pchar.quest.Sp4Detection_Race_2.win_condition.l1.location = "Tortuga_Cave";
			pchar.quest.Sp4Detection_Race_2.win_condition = "Sp4Detection_Race_2";
			AddLandQuestmark_Main(sld, "Spa_Line");
		break;

		case "Sp4Detection_Race_2":
			sld = characterFromId("AnryDEstre");
			LAi_ActorRunToLocation(sld, "reload", "reload2", "Shore58", "goto", "goto15", "", -1);
			pchar.quest.Sp4Detection_Race_3.win_condition.l1 = "location";
			pchar.quest.Sp4Detection_Race_3.win_condition.l1.location = "Shore58";
			pchar.quest.Sp4Detection_Race_3.win_condition = "Sp4Detection_Race_3";
		break;

		case "Sp4Detection_Race_3":
			sld = characterFromId("AnryDEstre");
			sld.DontClearDead = true;
			sld.SaveItemsForDead = true;
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
		break;

		case "Sp4Detection_YouWin":
			LAi_LocationDisableOfficersGen("Shore58", false); //офицеров пускать
			LAi_LocationDisableMonstersGen("Tortuga_Cave", false); //монстров генерить
			pchar.questTemp.State = "Sp4Detection_DEstreIsDead";
			AddQuestRecord("Spa_Line_4_MirderDetection", "6");
			AddQuestUserData("Spa_Line_4_MirderDetection", "sSex", GetSexPhrase("", "а"));
		break;

		//==========================   Квест N5, Разорение Ла Веги ========================
		case "Sp5LaVegaAttack_AttackGoOn":
			Pchar.GenQuestFort.fortCharacterIdx = GetCharacterIndex("Edward Mansfield");
			DeleteQuestAttribute("Union_with_Escadra");
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			SetLocationCapturedState(sld.city + "_town", true);
			DoQuestCheckDelay("Capture_Forts", 0.5);
			Ship_NationAgressive(sld, sld);
			Log_SetStringToLog(StringFromKey("InfoMessages_56"));
			//==> снимаем губернатора, он нестандарт.
			ChangeCharacterAddress(characterFromID("Edward Mansfield"), "None", "");
			Pchar.quest.Sp5LaVegaAttack_FightWithMayor.win_condition.l1 = "location";
			Pchar.quest.Sp5LaVegaAttack_FightWithMayor.win_condition.l1.location = "LaVega_townhall";
			Pchar.quest.Sp5LaVegaAttack_FightWithMayor.win_condition = "Sp5LaVegaAttack_FightWithMayor";
		break;

		case "Sp5LaVegaAttack_FightWithMayor":
			chrDisableReloadToLocation = true; // закрыть выход из локации
			bDisableFastReload = true; // закрыть переходы.
			sld = GetCharacter(NPC_GenerateCharacter("LaVega_Comendant", "Mansfield", "man", "man", 35, PIRATE, -1, true));
			sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
			sld.name = FindPersonalName("Edward_Mansfield_name");
			sld.lastname = FindPersonalName("Edward_Mansfield_lastname");
			sld.City = "LaVega";
			LAi_LoginInCaptureTown(sld, true);
			sld.DontClearDead = true; // не убирать труп через 200с
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.cirassId = FindItem("cirass5");
			FantomMakeCoolFighter(sld, 45, 90, 70, "blade17", "pistol3", 50);
			ChangeCharacterAddressGroup(sld, "LaVega_townhall", "goto", "goto1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.8);
		break;

		case "Sp5LaVegaAttack_AfterFight":
			AfterTownBattle();
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			pchar.questTemp.State = "Sp5LaVegaAttack_WeWon";
			AddQuestRecord("Spa_Line_5_LaVegaAttack", "3");
			SetCaptureTownByNation("LaVega", SPAIN);
			AddLandQuestmark_Main(CharacterFromID("Santiago_Mayor"), "Spa_Line");
		break;
		//=================== Квест N6, перехват голландского вестового на Тортуге ===================
		case "Sp6TakeMess_waitingBoy":
			Pchar.quest.Sp6TakeMess_TalkWithBoy.win_condition.l1 = "location";
			Pchar.quest.Sp6TakeMess_TalkWithBoy.win_condition.l1.location = "Tortuga_tavern";
			Pchar.quest.Sp6TakeMess_TalkWithBoy.win_condition = "Sp6TakeMess_TalkWithBoy";
		break;

		case "Sp6TakeMess_TalkWithBoy":
		//==> Алкаш
			sld = GetCharacter(NPC_GenerateCharacter("Boozer", "citiz_46", "man", "man", 10, FRANCE, 0, false));
			sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
			LAi_SetSitType(sld);
			FreeSitLocator("Tortuga_tavern", "sit2");
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "sit", "sit2");
			AddLandQuestmark_Main(sld, "Spa_Line");
			//==> Посыльный
			chrDisableReloadToLocation = true;
			sld = GetCharacter(NPC_GenerateCharacter("PortMansBoy", "shipowner_4", "man", "man", 10, FRANCE, 0, false)); //TODO: молодого пацана
			sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern", "goto", "goto2");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Sp6TakeMess_Interception":
			if (GetQuestPastTimeParam("questTemp") < 3)
			{
				Log_QuestInfo("Вперёд на перехват!");
				//==> вестовой.
				sld = GetCharacter(NPC_GenerateCharacter("Messanger", "off_hol_4", "man", "man", 30, FRANCE, 30, false));
				sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
				FantomMakeCoolFighter(sld, 30, 70, 50, "blade34", "pistol5", 60);
				ChangeCharacterAddressGroup(sld, "Tortuga_town", "reload", "reload3");
				GiveItem2Character(sld, "letter_HolLineQ7_1"); //даем ту же депешу, что была по голландке
				sld.money = 18430;
				sld.DontClearDead = true; // не убирать труп через 200с
				sld.SaveItemsForDead = true; // сохранять на трупе вещи
				LAi_SetCheckMinHP(sld, (LAi_GetCharacterHP(sld) - 1), false, "Sp6TakeMess_AttackMessanger");
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload2_back", "none", "", "", "Sp6TakeMess_MessengerOut", -1);
				LAi_Actor2WaitDialog(sld, pchar);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
				LocatorReloadEnterDisable("Tortuga_town", "gate_back", true);
				AddLandQuestmark_Main(sld, "Spa_Line");
				//==> добавим солдатиков в город
				for (i = 1; i <= 10; i++)
				{
					sld = GetCharacter(NPC_GenerateCharacter("AddSolder" + i, "Sold_fra_" + (rand(7) + 9), "man", "man", 25, FRANCE, 0, true));
					sld.Dialog.Filename = "Common_Soldier.c";
					sld.city = "Tortuga";
					sld.citytype = "soldier";
					FantomMakeCoolFighter(sld, sti(pchar.rank) + 6, 70, 50, BLADE_LONG, "pistol3", 60);
					LAi_SetPatrolType(sld);
					ChangeCharacterAddressGroup(sld, "Tortuga_town", "goto", "goto" + (rand(20) + 1));
					LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
				}
				LAi_group_SetLookRadius("FRANCE_CITIZENS", 50);
				Pchar.quest.Sp6TakeMess_FightInPort.win_condition.l1 = "location";
				Pchar.quest.Sp6TakeMess_FightInPort.win_condition.l1.location = "Tortuga";
				Pchar.quest.Sp6TakeMess_FightInPort.win_condition = "Sp6TakeMess_FightInPort";
			}
		break;

		case "Sp6TakeMess_AttackMessanger":
			iTemp = GetCharacterIndex("Messanger");
			if (iTemp != -1)
			{
				sld = &characters[iTemp];
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
				LAi_group_Attack(sld, Pchar);
				SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
			}
		break;

		case "Sp6TakeMess_MessengerOut":
			ChangeCharacterAddress(characterFromID("Messanger"), "None", "");
		break;

		case "Sp6TakeMess_FightInPort":
			if (GetCharacterIndex("Messanger") == -1)
			{
				bDisableFastReload = false; //открываем фаст релоад
				LocatorReloadEnterDisable("Tortuga_town", "gate_back", false);
				SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
				Island_SetReloadEnableGlobal("Tortuga", false);
				Group_FindOrCreateGroup("Fra_Attack");
				Group_SetType("Fra_Attack", "war");
				// ==> Французские кэпы
				for (i = 1; i <= 8; i++)
				{
					iTemp = FRANCE;
					switch (i)
					{
						case 1:
							ShipType = SHIP_FRIGATE_H;
							Model = "navy_off_fra_5";
							iRank = 42;
							Blade = "blade33";
						break;
						case 2:
							ShipType = SHIP_BRIG;
							Model = "navy_off_fra_1";
							iRank = 29;
							Blade = "blade33";
						break;
						case 3:
							ShipType = SHIP_FRIGATE;
							Model = "navy_off_fra_4";
							iRank = 35;
							Blade = "blade28";
						break;
						case 4:
							ShipType = SHIP_FRIGATE;
							Model = "navy_off_fra_4";
							iRank = 35;
							Blade = "blade24";
						break;
						case 5:
							ShipType = SHIP_CORVETTE;
							Model = "navy_off_fra_2";
							iRank = 32;
							Blade = "blade34";
						break;
						case 6:
							ShipType = SHIP_BRIG;
							Model = "navy_off_fra_1";
							iRank = 28;
							Blade = "blade26";
						//iTemp = HOLLAND;
						break;
						case 7:
							ShipType = SHIP_PINNACE;
							Model = "navy_off_fra_2";
							iRank = 31;
							Blade = "blade28";
						break;
						case 8:
							ShipType = SHIP_CORVETTE;
							Model = "navy_off_fra_3";
							iRank = 33;
							Blade = "blade32";
						break;
					}
					sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, Model, "man", "man", iRank, iTemp, -1, true));
					FantomMakeCoolSailor(sld, ShipType, "", CANNON_TYPE_LBS_BY_SHIP, 80, 70, 90);
					FantomMakeCoolFighter(sld, iRank, 80, 60, Blade, "pistol3", 75);
					Group_AddCharacter("Fra_Attack", "CaptainAttack_" + i);
				}
				// ==> стравливание
				Group_SetGroupCommander("Fra_Attack", "CaptainAttack_1");
				Group_SetTaskAttack("Fra_Attack", PLAYER_GROUP);
				Group_SetPursuitGroup("Fra_Attack", PLAYER_GROUP);
				Group_SetAddress("Fra_Attack", "Tortuga", "", "");
				Group_LockTask("Fra_Attack");
				pchar.quest.Sp6TakeMess_OpenTortuga.win_condition.l1 = "MapEnter";
				pchar.quest.Sp6TakeMess_OpenTortuga.win_condition = "Sp6TakeMess_OpenTortuga";
			}
			else characters[GetCharacterIndex("Messanger")].lifeDay = 0;
		break;

		case "Sp6TakeMess_OpenTortuga":
			Island_SetReloadEnableGlobal("Tortuga", true);
		break;

		case "Sp6TakeMess_WaitMessanger":
			chrDisableReloadToLocation = true; // закрыть выход из локации
			bDisableFastReload = true; // закрыть переходы.
			DoQuestCheckDelay("Sp6TakeMess_2WaitMessanger", 10.0);
		break;

		case "Sp6TakeMess_2WaitMessanger":
			sld = GetCharacter(NPC_GenerateCharacter("Messanger", "off_hol_4", "man", "man", 40, FRANCE, 0, false));
			sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
			FantomMakeCoolFighter(sld, 40, 95, 80, "blade34", "pistol5", 100);
			ChangeCharacterAddressGroup(sld, "Tortuga_tavern_upstairs", "reload", "reload1_back");
			GiveItem2Character(sld, "letter_HolLineQ7_1"); //даем ту же депешу, что была по голландке
			sld.money = 18430;
			sld.DontClearDead = true; // не убирать труп через 200с
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
		break;
		//=================== Квест N7, спасти Пардаля ===================
		case "Sp7SavePardal_FightNearAntigua":
			Log_QuestInfo("Спасаем Пардаля, он не должен быть потоплен.");
			PChar.questTemp.SLQ7_Diffrent = 1; //Моисею Воклейну в каюту
			Island_SetReloadEnableGlobal("Antigua", false);
			// ==> Пардаль
			Group_SetType("Quest_Group", "war");
			Group_FindOrCreateGroup("Quest_Group");
			for (i = 1; i <= 3; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_BATTLESHIP;
						Model = "navy_off_spa_5";
						iRank = 30;
						Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS36;
					break;
					case 2:
						ShipType = SHIP_GALEON_H;
						Model = "navy_off_spa_4";
						iRank = 27;
						Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS32;
					break;
					case 3:
						ShipType = SHIP_GALEON_L;
						Model = "navy_off_spa_3";
						iRank = 24;
						Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS24;
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter("OurCaptain_" + i, Model, "man", "man", iRank, SPAIN, 0, true));
				sld.ShipEnemyDisable = true; //при попадании не враждебен
				FantomMakeCoolSailor(sld, ShipType, "", iTemp, 60, 50, 50);
				FantomMakeCoolFighter(sld, iRank, 70, 40, Blade, "pistol3", 50);
				if (sld.id == "OurCaptain_1")
				{
					sld.DeckDialogNode = "First time";
					sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
					sld.name = FindPersonalName("OurCaptain_1_name");
					sld.lastname = FindPersonalName("OurCaptain_1_lastname");
					sld.greeting = "Gr_military";
					sld.Abordage.Enable = false; // НЕЛЬЗЯ!
					sld.Ship.Name = FindPersonalName("OurCaptain_1_ship");
					LAi_SetStayTypeNoGroup(sld);
					AddLandQuestmark_Main(sld, "Spa_Line");
				}
				Group_AddCharacter("Quest_Group", "OurCaptain_" + i);
			}
			Group_SetGroupCommander("Quest_Group", "OurCaptain_1"); //это Пардаль
			Group_SetPursuitGroup("Quest_Group", PLAYER_GROUP);
			Group_SetAddress("Quest_Group", "Antigua", "", "");
			// ==> Флибустьеры
			Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
			for (i = 1; i <= 7; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_BATTLESHIP;
						iRank = 35;
						Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
					break;
					case 2:
						ShipType = SHIP_FRIGATE;
						iRank = 31;
						Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
					break;
					case 3:
						ShipType = SHIP_WARSHIP;
						iRank = 33;
						Blade = "blade28";
						iTemp = CANNON_TYPE_CANNON_LBS32;
					break;
					case 4:
						ShipType = SHIP_CORVETTE;
						iRank = 29;
						Blade = "blade24";
						iTemp = CANNON_TYPE_CANNON_LBS24;
					break;
					case 5:
						ShipType = SHIP_BATTLESHIP;
						iRank = 34;
						Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS32;
					break;
					case 6:
						ShipType = SHIP_LINESHIP;
						iRank = 32;
						Blade = "blade26";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
					break;
					case 7:
						ShipType = SHIP_CORVETTE;
						iRank = 28;
						Blade = "blade34";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, "citiz_" + (rand(9) + 51), "man", "man", iRank, PIRATE, 0, true)); //watch_quest_moment; можно делать officer/citiz в зависимости от кораблей
				FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 95, 95);
				FantomMakeCoolFighter(sld, iRank, 100, 90, Blade, "pistol3", 150);
				if (sld.id == "CaptainAttack_1")
				{
					sld.name = FindPersonalName("Pir_Attack_name");
					sld.lastname = FindPersonalName("Pir_Attack_lastname");
					sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
					sld.Ship.Name = FindPersonalName("Pir_Attack_ship");
					LAi_SetStayTypeNoGroup(sld);
				}
				Group_AddCharacter("Pir_Attack", "CaptainAttack_" + i);
			}
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
			Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Antigua", "", "");
			// ==> стравливание
			Group_SetTaskAttack("Pir_Attack", "Quest_Group");
			Group_SetTaskAttack("Quest_Group", "Pir_Attack");
			Group_LockTask("Quest_Group");
			//Group_LockTask("Pir_Attack");
			// ==> прерывание на убиение эскадры
			pchar.quest.Sp7SavePardal_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp7SavePardal_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp7SavePardal_AfterBattle.win_condition = "Sp7SavePardal_AfterBattle";
			pchar.quest.Sp7SavePardal_NotSavedPardal.win_condition.l1 = "NPC_Death";
			pchar.quest.Sp7SavePardal_NotSavedPardal.win_condition.l1.character = "OurCaptain_1";
			pchar.quest.Sp7SavePardal_NotSavedPardal.win_condition = "Sp7SavePardal_NotSavedPardal";
			pchar.quest.Sp7SavePardal_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.Sp7SavePardal_DieHard.win_condition = "Sp7SavePardal_DieHard";
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;

		case "Sp7SavePardal_AfterBattle":
			Log_QuestInfo("Флибустьерская эскадра разбита.");
			pchar.questTemp.State = "Sp7SavePardal_GoodWork";
			AddQuestRecord("Spa_Line_7_SavePardal", "2");
			AddQuestUserData("Spa_Line_7_SavePardal", "sSex", GetSexPhrase("ёл", "ла"));
			Island_SetReloadEnableGlobal("Antigua", true);
			pchar.quest.Sp7SavePardal_NotSavedPardal.over = "yes";
		break;

		case "Sp7SavePardal_DieHard":
			group_DeleteGroup("Pir_Attack");
			group_DeleteGroup("Quest_Group");
			if (pchar.questTemp.State != "Sp7SavePardal_PardalIsSink" && pchar.questTemp.State != "Sp7SavePardal_GoodWork" && pchar.questTemp.State != "Sp7SavePardal_2GoodWork")
			{
				Log_QuestInfo("Свалил с поля боя, очень плохо.");
				pchar.questTemp.State = "Sp7SavePardal_DieHard";
				AddQuestRecord("Spa_Line_7_SavePardal", "3");
				Island_SetReloadEnableGlobal("Antigua", true);
				pchar.quest.Sp7SavePardal_AfterBattle.over = "yes";
				pchar.quest.Sp7SavePardal_NotSavedPardal.over = "yes";
			}
		break;

		case "Sp7SavePardal_NotSavedPardal":
			pchar.quest.Sp7SavePardal_AfterBattle.over = "yes";
			Island_SetReloadEnableGlobal("Antigua", true);
			AddQuestRecord("Spa_Line_7_SavePardal", "4");
			pchar.questTemp.State = "Sp7SavePardal_PardalIsSink";
		break;
		//=================== Квест N8, спасти Куману ===================
		case "Sp8SaveCumana_RescueTimeOver":
			Log_QuestInfo("Опоздал. Кумана разорена.");
			pchar.questTemp.State = "Sp8SaveCumana_YouLate";
			AddQuestRecord("Spa_Line_8_SaveCumana", "2");
			pchar.quest.Sp8SaveCumana_Battle.over = "yes";
			SetLocationCapturedState("Cumana_town", true);
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		//TODO партиклы в куману
		break;

		case "Sp8SaveCumana_Battle":
			Log_QuestInfo("Пиратская эскадра установлена.");
			pchar.quest.Sp8SaveCumana_RescueTimeOver.over = "yes";
			PChar.questTemp.SLQ8_Diffrent = 1; //капитану Анселю в каюту
			Island_SetReloadEnableGlobal("Cumana", false);
			Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
			// ==> Пиратские кэпы
			for (i = 1; i <= 8; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_BATTLESHIP;
						iRank = 42;
						Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
					break;
					case 2:
						ShipType = SHIP_FRIGATE;
						iRank = 34;
						Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
					break;
					case 3:
						ShipType = SHIP_WARSHIP;
						iRank = 36;
						Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
					break;
					case 4:
						ShipType = SHIP_CORVETTE;
						iRank = 32;
						Blade = "blade24";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
					break;
					case 5:
						ShipType = SHIP_BATTLESHIP;
						iRank = 37;
						Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS32;
					break;
					case 6:
						ShipType = SHIP_LINESHIP;
						iRank = 33;
						Blade = "blade26";
						iTemp = CANNON_TYPE_CANNON_LBS32;
					break;
					case 7:
						ShipType = SHIP_CORVETTE;
						iRank = 33;
						Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
					break;
					case 8:
						ShipType = SHIP_FRIGATE;
						Model = "navy_off_spa_4";
						iRank = 35;
						Blade = "blade32";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, "citiz_" + (rand(9) + 51), "man", "man", iRank, PIRATE, 0, true)); //watch_quest_moment; можно делать officer/citiz в зависимости от кораблей
				FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 95, 95);
				FantomMakeCoolFighter(sld, iRank, 100, 90, Blade, "pistol3", 150);
				if (sld.id == "CaptainAttack_1")
				{
					sld.name = FindPersonalName("Pir_Attack2_name");
					sld.lastname = FindPersonalName("Pir_Attack2_lastname");
					sld.Dialog.Filename = "Quest\SpaLineNpc_2.c";
					sld.Ship.Name = FindPersonalName("Pir_Attack2_ship");
					LAi_SetStayTypeNoGroup(sld);
				}
				Group_AddCharacter("Pir_Attack", "CaptainAttack_" + i);
			}
			// ==> стравливание
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pir_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Cumana", "", "");
			Group_LockTask("Pir_Attack");
			pchar.quest.Sp8SaveCumana_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp8SaveCumana_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp8SaveCumana_AfterBattle.win_condition = "Sp8SaveCumana_AfterBattle";
			pchar.quest.Sp8SaveCumana_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.Sp8SaveCumana_DieHard.win_condition = "Sp8SaveCumana_DieHard";
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;

		case "Sp8SaveCumana_AfterBattle":
			Log_QuestInfo("Пиратская эскадра разбита.");
			pchar.questTemp.State = "Sp8SaveCumana_GoodWork";
			AddQuestRecord("Spa_Line_8_SaveCumana", "3");
			AddQuestUserData("Spa_Line_8_SaveCumana", "sSex", GetSexPhrase("", "а"));
			group_DeleteGroup("Pir_Attack");
			Island_SetReloadEnableGlobal("Cumana", true);
			pchar.quest.Sp8SaveCumana_DieHard.over = "yes";
		break;

		case "Sp8SaveCumana_DieHard":
			Log_QuestInfo("Свалил с поля боя, очень плохо.");
			pchar.questTemp.State = "Sp8SaveCumana_DieHard";
			AddQuestRecord("Spa_Line_8_SaveCumana", "4");
			AddQuestUserData("Spa_Line_8_SaveCumana", "sSex", GetSexPhrase("", "а"));
			group_DeleteGroup("Pir_Attack");
			Island_SetReloadEnableGlobal("Cumana", true);
			pchar.quest.Sp8SaveCumana_AfterBattle.over = "yes";
			SetLocationCapturedState("Cumana_town", true);
		//TODO партиклы в куману
		break;
		//=================== Квест N9, сопровождение четырёх галеонов ===================
		case "Sp9SaveCumana_toCaimanBattle":
			Log_QuestInfo("Засада пиратов, к бою.");
			pchar.questTemp.State = "Sp9SaveCumana_BackHavana";
			Island_SetReloadEnableGlobal("Caiman", false);
			Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
			// ==> Пиратские кэпы
			for (i = 1; i <= 5; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_LINESHIP;
						iRank = 32;
						Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS32;
					break;
					case 2:
						ShipType = SHIP_GALEON_H;
						iRank = 26;
						Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
					break;
					case 3:
						ShipType = SHIP_CARAVEL;
						iRank = 25;
						Blade = "blade25";
						iTemp = CANNON_TYPE_CANNON_LBS24;
					break;
					case 4:
						ShipType = SHIP_GALEON_H;
						iRank = 27;
						Blade = "blade28";
						iTemp = CANNON_TYPE_CANNON_LBS32;
					break;
					case 5:
						ShipType = SHIP_WARSHIP;
						iRank = 30;
						Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, "citiz_" + (rand(9) + 51), "man", "man", iRank, PIRATE, 0, true)); //watch_quest_moment; можно делать officer/citiz в зависимости от кораблей
				FantomMakeCoolSailor(sld, ShipType, "", iTemp, 90, 80, 80);
				FantomMakeCoolFighter(sld, iRank, 90, 70, Blade, "pistol3", 75);
				Group_AddCharacter("Pir_Attack", "CaptainAttack_" + i);
			}
			// ==> стравливание
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pir_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Caiman", "", "");
			Group_LockTask("Pir_Attack");
			// ==> прерывание на убиение эскадры
			pchar.quest.Sp9SaveCumana_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp9SaveCumana_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp9SaveCumana_AfterBattle.win_condition = "Sp9SaveCumana_AfterBattle";
			pchar.quest.Sp9SaveCumana_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.Sp9SaveCumana_DieHard.win_condition = "Sp9SaveCumana_DieHard";
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;

		case "Sp9SaveCumana_AfterBattle":
			Island_SetReloadEnableGlobal("Caiman", true);
			pchar.quest.Sp9SaveCumana_DieHard.over = "yes";
			group_DeleteGroup("Pir_Attack");
			//--> сколько у нас флейтов из компаньонов
			iTemp = 0;
			for (i = 1; i <= COMPANION_MAX; i++)
			{
				ShipType = GetCompanionIndex(pchar, i);
				if (ShipType != -1)
				{
					sld = GetCharacter(ShipType);
					ShipType = sti(sld.ship.type);
					iRank = sti(RealShips[ShipType].basetype);
					if (iRank == SHIP_GALEON_L) iTemp++;
				}
			}
			//--> результат в СЖ
			if (iTemp < 4)
			{
				if (iTemp == 1)
				{
					AddQuestRecord("Spa_Line_9_FourGolgGaleons", "3");
					AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("", "а"));
				}
				else
				{
					AddQuestRecord("Spa_Line_9_FourGolgGaleons", "4");
					AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("", "а"));
					AddQuestUserData("Spa_Line_9_FourGolgGaleons", "QtyGaleons", iTemp);
				}
			}
			else
			{
				AddQuestRecord("Spa_Line_9_FourGolgGaleons", "5");
				AddQuestUserData("Spa_Line_9_FourGolgGaleons", "sSex", GetSexPhrase("", "а"));
			}
		break;

		case "Sp9SaveCumana_DieHard":
			pchar.quest.Sp9SaveCumana_AfterBattle.over = "yes";
			AddQuestRecord("Spa_Line_9_FourGolgGaleons", "6");
			Island_SetReloadEnableGlobal("Caiman", true);
			group_DeleteGroup("Pir_Attack");
			for (i = 1; i <= 4; i++)
			{
				sld = characterFromID("Captain_" + i);
				if (sld.id != "none")
				{
					RemoveCharacterCompanion(pchar, sld);
					sld.LifeDay = 0;
				}
			}
		break;
		//=================== Квест N10, Защита Маракайбо  ===================
		case "Sp10Maracaibo_TalkWithOfficer":
			Log_QuestInfo("Столкновение с офицером на выходе из резиденции.");
			sld = GetCharacter(NPC_GenerateCharacter("SpaTalkOfficer", "off_spa_2", "man", "man", 20, SPAIN, 0, true));
			sld.Dialog.Filename = "Quest\SpaLineNpc_1.c";
			ChangeCharacterAddressGroup(sld, "Maracaibo_town", "goto", "goto8");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
		break;

		case "Sp10Maracaibo_Battle":
			Log_QuestInfo("Пиратская эскадра установлена.");
			Island_SetReloadEnableGlobal("Maracaibo", false);
			Group_FindOrCreateGroup("Pir_Attack");
			Group_SetType("Pir_Attack", "war");
			// ==> Пиратские кэпы
			for (i = 1; i <= 8; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_MANOWAR;
						iRank = 45;
						Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
					break;
					case 2:
						ShipType = SHIP_FRIGATE;
						iRank = 34;
						Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
					break;
					case 3:
						ShipType = SHIP_WARSHIP;
						iRank = 37;
						Blade = "blade34";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
					break;
					case 4:
						ShipType = SHIP_CORVETTE;
						iRank = 32;
						Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
					break;
					case 5:
						ShipType = SHIP_BATTLESHIP;
						iRank = 39;
						Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
					break;
					case 6:
						ShipType = SHIP_LINESHIP;
						iRank = 36;
						Blade = "blade32";
						iTemp = CANNON_TYPE_CANNON_LBS32;
					break;
					case 7:
						ShipType = SHIP_MANOWAR;
						iRank = 42;
						Blade = "topor2";
						iTemp = CANNON_TYPE_CANNON_LBS42;
					break;
					case 8:
						ShipType = SHIP_FRIGATE;
						Model = "navy_off_spa_4";
						iRank = 35;
						Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, "citiz_" + (rand(9) + 51), "man", "man", iRank, PIRATE, 0, true)); //watch_quest_moment; можно делать officer/citiz в зависимости от кораблей
				FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 95, 95);
				FantomMakeCoolFighter(sld, iRank, 100, 90, Blade, "pistol3", 150);
				Group_AddCharacter("Pir_Attack", "CaptainAttack_" + i);
			}
			// ==> стравливание
			Group_SetGroupCommander("Pir_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Pir_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Pir_Attack", PLAYER_GROUP);
			Group_SetAddress("Pir_Attack", "Maracaibo", "", "");
			Group_LockTask("Pir_Attack");
			pchar.quest.Sp10Maracaibo_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.Sp10Maracaibo_AfterBattle.win_condition.l1.group = "Pir_Attack";
			pchar.quest.Sp10Maracaibo_AfterBattle.win_condition = "Sp10Maracaibo_AfterBattle";
			pchar.quest.Sp10Maracaibo_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.Sp10Maracaibo_DieHard.win_condition = "Sp10Maracaibo_DieHard";
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
		break;

		case "Sp10Maracaibo_AfterBattle":
			Log_QuestInfo("Пиратская эскадра разбита.");
			pchar.questTemp.State = "Sp10Maracaibo_GoodWork";
			AddQuestRecord("Spa_Line_10_Maracaibo", "3");
			group_DeleteGroup("Pir_Attack");
			Island_SetReloadEnableGlobal("Maracaibo", true);
			pchar.quest.Sp10Maracaibo_DieHard.over = "yes";
			AddLandQuestmark_Main(CharacterFromID("Maracaibo_Mayor"), "Spa_Line");
		break;

		case "Sp10Maracaibo_DieHard":
			Log_QuestInfo("Свалил с поля боя, линейке конец.");
			pchar.questTemp.State = "Sp10Maracaibo_DieHard";
			AddQuestRecord("Spa_Line_10_Maracaibo", "4");
			group_DeleteGroup("Pir_Attack");
			Island_SetReloadEnableGlobal("Maracaibo", true);
			pchar.quest.Sp10Maracaibo_AfterBattle.over = "yes";
			SetCaptureTownByNation("Maracaibo", ENGLAND);
			UpdateRelations();
			RefreshBattleInterface();
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  END Испанская линейка
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  START Французская линейка
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//=================== Квест N1, доставка Пьера Леграна до Мартиники  ===================
		case "Fr1Legran_intoLeMaren":
			GetCharacterPos(pchar, &locx, &locy, &locz);
			sld = characterFromId("Legran");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Shore39", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			arrayNPCModelHow = 0;
			for (i = 1; i <= 6; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("FraBandit" + i, "pirate_" + (rand(15) + 1), "man", "man", 20, PIRATE, 0, true)); //watch_quest_moment; пусть будут обычные пираты
				SetNPCModelUniq(sld, "pirate", MAN);
				sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
				FantomMakeCoolFighter(sld, 20, 65, 30, BLADE_LONG, "pistol2", 40);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Shore39", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
			}
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(&Locations[FindLocation("Shore39")], true);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Fr1Legran_afterFightBandits":
			DeleteAttribute(&locations[FindLocation("Shore39")], "DisableEncounters"); //энкаутеры вернём
			chrDisableReloadToLocation = false;
			sld = characterFromId("Legran");
			if (!LAi_IsDead(sld))
			{
				pchar.questTemp.State = "Fr1Legran_afterFightBand";
				LAi_SetActorType(pchar);
				LAi_SetActorType(sld);
				SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
				LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 1.0);
			}
			else
			{
				pchar.questTemp.State = "Fr1Legran_LegranIsDead";
				AddQuestRecord("Fra_Line_1_LegranDis", "5");
				AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
			}
		break;
		//=================== Квест N2, доставка письма в Кюрасао  ===================
		case "Fr2Letter_intoPrison_1":
			sld = GetCharacter(NPC_GenerateCharacter("HolPrisoner", "off_hol_3", "man", "man", 15, HOLLAND, 0, false)); //тюремщик
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			LAi_SetStayTypeNoGroup(sld);
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto13");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto23", "Fr2Letter_intoPrison_2", -1);
		break;

		case "Fr2Letter_intoPrison_2":
			pchar.questTemp.State = "Fr2Letter_PrisonTalk";
			sld = characterFromID("HolPrisoner");
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
		break;

		case "Fr2Letter_intoPrison_3":
			WaitDate("", 0, 0, 1, 0, 0); //крутим день
			SetCurrentTime(9, 20);
			RecalculateJumpTable();
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_24"), "", 0, 6);
			LaunchFrameForm();
			npchar = characterFromId("hol_guber");
			sld = GetCharacter(NPC_GenerateCharacter("GoverFantom", npchar.model, "man", npchar.model.animation, 15, HOLLAND, 0, false));
			sld.name = FindPersonalName("hol_guber_name");
			sld.lastname = FindPersonalName("hol_guber_lastname");
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			LAi_SetStayTypeNoGroup(sld);
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "Villemstad_prison", "goto", "goto13");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto23", "Fr2Letter_intoPrison_4", -1);
		break;

		case "Fr2Letter_intoPrison_4":
			pchar.questTemp.State = "Fr2Letter_VisitGovernor";
			sld = characterFromID("GoverFantom");
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
		break;

		case "Fr2Letter_OutTavern_1":
			if (!CheckAttribute(pchar, "questTemp.Out"))
			{
				chrDisableReloadToLocation = false;
				bDisableFastReload = true;
				DoQuestCheckDelay("TalkSelf_Quest", 0.2); //диалог сам-на-сам
				pchar.quest.Fr2Letter_shore22.win_condition.l1 = "locator";
				pchar.quest.Fr2Letter_shore22.win_condition.l1.location = "Shore22";
				pchar.quest.Fr2Letter_shore22.win_condition.l1.locator_group = "quest";
				pchar.quest.Fr2Letter_shore22.win_condition.l1.locator = "detector1";
				pchar.quest.Fr2Letter_shore22.function = "Fr2Letter_shore22";
			}
			for (i = 12; i <= 13; i++)
			{
				sld = characterFromId("Bandit_" + i);
				LAi_SetActorTypeNoGroup(sld);
				if (i == 12) sTemp = "goto14";
				else sTemp = "goto13";
				ChangeCharacterAddressGroup(sld, "Shore22", "goto", sTemp);
			}
		break;

		case "Fr2Letter_OutTavern_2":
			bDisableFastReload = false;
			if (GetQuestPastMinutesParam("questTemp") < 5)
			{
				Log_QuestInfo("Успел выбежать из таверны.");
				for (i = 12; i <= 13; i++)
				{
					sld = characterFromId("Bandit_" + i);
					ChangeCharacterAddressGroup(sld, "Villemstad_town", "goto", "goto9");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "gate_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
				Pchar.quest.Fr2Letter_OutTavern_3.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_3.win_condition.l1.location = "Villemstad_ExitTown";
				Pchar.quest.Fr2Letter_OutTavern_3.win_condition = "Fr2Letter_OutTavern_3";
			}
			else Log_QuestInfo("Не успел выбежать из таверны, рулим в бухту Пальмовый берег.");
		break;

		case "Fr2Letter_OutTavern_3":
			if (GetQuestPastMinutesParam("questTemp") < 13)
			{
				Log_QuestInfo("Успел выбежать.");
				for (i = 12; i <= 13; i++)
				{
					sld = characterFromId("Bandit_" + i);
					ChangeCharacterAddressGroup(sld, "Villemstad_ExitTown", "goto", "goto2");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
				Pchar.quest.Fr2Letter_OutTavern_4.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_4.win_condition.l1.location = "Curacao_jungle_01";
				Pchar.quest.Fr2Letter_OutTavern_4.win_condition = "Fr2Letter_OutTavern_4";
				//SaveCurrentQuestDateParam("questTemp");
			}
			else Log_QuestInfo("Не успел, рулим в бухту Пальмовый берег.");
		break;

		case "Fr2Letter_OutTavern_4":
			if (GetQuestPastMinutesParam("questTemp") < 19)
			{
				Log_QuestInfo("Успел выбежать.");
				for (i = 12; i <= 13; i++)
				{
					sld = characterFromId("Bandit_" + i);
					ChangeCharacterAddressGroup(sld, "Curacao_jungle_01", "goto", "goto5");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);

				}
				Pchar.quest.Fr2Letter_OutTavern_5.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_5.win_condition.l1.location = "Curacao_jungle_02";
				Pchar.quest.Fr2Letter_OutTavern_5.win_condition = "Fr2Letter_OutTavern_5";
				//SaveCurrentQuestDateParam("questTemp");
			}
			else Log_QuestInfo("Не успел, рулим в бухту Пальмовый берег.");
		break;

		case "Fr2Letter_OutTavern_5":
			if (GetQuestPastMinutesParam("questTemp") < 24)
			{
				Log_QuestInfo("Успел выбежать.");
				for (i = 12; i <= 13; i++)
				{
					sld = characterFromId("Bandit_" + i);
					ChangeCharacterAddressGroup(sld, "Curacao_jungle_02", "goto", "goto4");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
				Pchar.quest.Fr2Letter_OutTavern_6.win_condition.l1 = "location";
				Pchar.quest.Fr2Letter_OutTavern_6.win_condition.l1.location = "Curacao_jungle_03";
				Pchar.quest.Fr2Letter_OutTavern_6.win_condition = "Fr2Letter_OutTavern_6";
				//SaveCurrentQuestDateParam("questTemp");
			}
			else Log_QuestInfo("Не успел, рулим в бухту Пальмовый берег.");
		break;

		case "Fr2Letter_OutTavern_6":
			if (GetQuestPastMinutesParam("questTemp") < 32)
			{
				Log_QuestInfo("Успел выбежать.");
				for (i = 12; i <= 13; i++)
				{
					sld = characterFromId("Bandit_" + i);
					ChangeCharacterAddressGroup(sld, "Curacao_jungle_03", "goto", "goto7");
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "Fr2Letter_OutTavern_1", -1);
				}
			}
			else Log_QuestInfo("Не успел, рулим в бухту Пальмовый берег.");
		break;

		case "Fr2Letter_FightWithGaleon":
			Log_QuestInfo("Галеон найден, на абордаж!");
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "navy_off_spa_3", "man", "man", 30, SPAIN, 0, true));
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			sld.DontRansackCaptain = true;
			FantomMakeCoolSailor(sld, SHIP_GALEON_H, FindPersonalName("CaptainAttack_1_ship5"), CANNON_TYPE_CULVERINE_LBS24, 80, 60, 60);
			FantomMakeCoolFighter(sld, 30, 70, 50, "blade28", "pistol3", 50);
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			// ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			//Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Curacao", "quest_ships", "Quest_ship_6");
			Group_LockTask("Spa_Attack");
		break;

		case "Fr2Letter_FightAfterShot":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
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
			AddQuestRecord("Fra_Line_2_DelivLetter", "7");
			AddQuestUserData("Fra_Line_2_DelivLetter", "sSex", GetSexPhrase("ся", "ась"));
		break;
		//=================== Квест N3, похищение донны Анны  ===================
		case "Fr3TakeAnna_FightInHouse":
			chrDisableReloadToLocation = true;
			LAi_LocationFightDisable(loadedLocation, true);
			LAi_group_Delete("PeaceGroup");
			sld = GetCharacter(NPC_GenerateCharacter("AnnaDeLeiva", "AnnaDeLeiva", "woman", "towngirl2", 10, SPAIN, -1, false));
			sld.Dialog.Filename = "Quest\FraLineNpc_2.c";
			sld.name = FindPersonalName("AnnaDeLeiva_name");
			sld.lastname = FindPersonalName("AnnaDeLeiva_lastname");
			sld.greeting = "Gr_Dama";
			sld.RebirthPhantom = true;
			LAi_NoRebirthEnable(sld);
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "PeaceGroup");
			ChangeCharacterAddressGroup(sld, "Havana_houseS1Bedroom", "goto", "goto7");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_group_Delete("EnemyFight");
			AddLandQuestmark_Main(sld, "Fra_Line");
			for (i = 1; i <= 5; i++)
			{
				Model = "Sold_spa_" + (rand(7) + 9);
				iRank = 18;
				attrName = "SpaFighter" + i;
				if (i == 1)
				{
					Model = "off_spa_5";
					iRank = 23;
					attrName = "DeLeiva";
				}
				sld = GetCharacter(NPC_GenerateCharacter(attrName, Model, "man", "man", iRank, SPAIN, 0, true));
				FantomMakeCoolFighter(sld, iRank, 70, 50, BLADE_LONG, "pistol2", 40);
				LAi_SetWarriorType(sld);
				if (i == 1)
				{
					sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
					sld.name = FindPersonalName("FraLineNpc_1_name");
					sld.lastname = FindPersonalName("FraLineNpc_1_lastname");
					ChangeCharacterAddressGroup(sld, "Havana_houseS1", "goto", "goto2");
				}
				else
				{
					LAi_warrior_DialogEnable(sld, false);
					ChangeCharacterAddressGroup(sld, "Havana_houseS1", "goto", "goto5");
				}
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = characterFromId("DeLeiva");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			DoQuestCheckDelay("MainHeroFightModeOff", 1.0);
		break;

		case "Fr3TakeAnna_DelivShip":
			sld = characterFromId("AnnaDeLeiva");
			if (LAi_IsDead(sld))
			{
				AddQuestRecord("Fra_Line_3_TakeAnna", "5");
				pchar.questTemp.State = "Fr3TakeAnna_BadResult";
				DeleteAttribute(sld, "RebirthPhantom");
				sld.LifeDay = 0;
			}
			else
			{
				AddQuestRecord("Fra_Line_3_TakeAnna", "4");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false);
				pchar.questTemp.State = "Fr3TakeAnna_NiceResult";
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, "Tortuga_townhall", "goto", "goto2");
			}
			DeleteQuestCheck("Fr3TakeAnna_DelivShip");
			DeleteQuestCheck("Fr3TakeAnna_DelivShip2");
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;

		case "Fr3_AfterAnna_IKnowYou": //Узнавание ГГ в таверне Гаваны.
			sld = characterFromId("Havana_waitress");
			if (sti(sld.nation) == SPAIN)
			{
				chrDisableReloadToLocation = true;
				LAi_LocationFightDisable(&Locations[FindLocation("Havana_tavern")], false);
				sld.dialog.currentnode = "Allarm";
				LAi_SetActorTypeNoGroup(sld);
				LAi_ActorDialog(sld, pchar, "", 0, 0);
			}
		break;

		//=================== Квест N4, Солей Руаяль, сопровождение до Гваделупы  ===================
		case "Fr4SoleiRoyal_Fight":
			Log_QuestInfo("Испанская эскадра установлена.");
			Island_SetReloadEnableGlobal("Dominica", false);
			group_DeleteGroup("Spa_Attack");
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			// ==> Испанские кэпы
			for (i = 1; i <= 4; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_GALEON_H;
						iRank = 23;
						Blade = "topor2";
						iTemp = CANNON_TYPE_CANNON_LBS24;
					break;
					case 2:
						ShipType = SHIP_GALEON_H;
						iRank = 21;
						Blade = "blade33";
						iTemp = CANNON_TYPE_CANNON_LBS24;
					break;
					case 3:
						ShipType = SHIP_GALEON_H;
						iRank = 23;
						Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS24;
					break;
					/*case 4:
                        ShipType = SHIP_WARSHIP;
                        iRank = 32;
                        Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;
                    case 5:
                        ShipType = SHIP_GALEON_H;
                        iRank = 24;
                        Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 6:
                        ShipType = SHIP_GALEON_H;
                        iRank = 32;
                        Blade = "blade32";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;*/
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, "navy_off_spa_" + (rand(1) + 3), "man", "man", iRank, SPAIN, 0, true)); //TODO: во всех таких моментах через SetCaptanModelByEncType
				if (i == 3)
				{
					sld.name = FindPersonalName("Huan_name");
					sld.lastname = FindPersonalName("Galeno_lastname");
					sld.model = "navy_off_spa_6"; FaceMaker(sld); //TODO: уникальную
					sld.DontRansackCaptain = true;
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 80, 80, 60);
					FantomMakeCoolFighter(sld, iRank, 77, 80, Blade, "pistol5", 80);
				}
				else
				{
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 60, 50, 50);
					FantomMakeCoolFighter(sld, iRank, 80, 90, Blade, "pistol3", 50);
				}
				Group_AddCharacter("Spa_Attack", "CaptainAttack_" + i);
			}
			// ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Dominica", "", "");
			Group_LockTask("Spa_Attack");
			pchar.quest.Fr4SoleiRoyal_WiWon.win_condition.l1 = "Group_Death";
			pchar.quest.Fr4SoleiRoyal_WiWon.win_condition.l1.group = "Spa_Attack";
			pchar.quest.Fr4SoleiRoyal_WiWon.win_condition = "Fr4SoleiRoyal_WiWon";
			pchar.quest.Fr4SoleiRoyal_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.Fr4SoleiRoyal_DieHard.win_condition = "Fr4SoleiRoyal_DieHard";
		break;

		case "Fr4SoleiRoyal_WiWon":
			Log_QuestInfo("Испанская эскадра разбита.");
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Dominica", true);
			pchar.quest.Fr4SoleiRoyal_DieHard.over = "yes";
			if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
			{
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "4");
				AddQuestUserData("Fra_Line_4_SoleiRoyal", "sSex", GetSexPhrase("ся", "лась"));
				pchar.questTemp.State = "Fr4SoleiRoyal_SoleiRoyalSunk";
                AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
			}
			else
			{
				pchar.questTemp.State = "Fr4SoleiRoyal_GoodWork";
				AddQuestRecord("Fra_Line_4_SoleiRoyal", "3");
				AddQuestUserData("Fra_Line_4_SoleiRoyal", "sSex", GetSexPhrase("ся", "лась"));
				AddLandQuestmark_Main(CharacterFromID("BasTer_Mayor"), "Fra_Line");
			}
		break;

		case "Fr4SoleiRoyal_DieHard":
			Log_QuestInfo("Свалил с поля боя, очень плохо.");
			pchar.questTemp.State = "Fr4SoleiRoyal_DieHard";
			AddQuestRecord("Fra_Line_4_SoleiRoyal", "5");
			AddQuestUserData("Fra_Line_4_SoleiRoyal", "sSex", GetSexPhrase("ся", "лась"));
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Dominica", true);
			pchar.quest.Fr4SoleiRoyal_WiWon.over = "yes";
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			sld.LifeDay = 0;
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;
		//=================== Квест N5, решение проблем донны Анны  ===================
		case "Fr5Anna_InShore":
			chrDisableReloadToLocation = true;
			//==> братьев к маяку.
			for (i = 1; i <= 2; i++)
			{
				//watch_quest_moment; тут были 2 брата очень похожие, нужно забрать эти модельки из ванилы или сделать свои аналоги
				//officer_12 и officer_2 из модпака
				if (i == 1) sTemp = "citiz_8";
				else sTemp = "citiz_5";
				sld = GetCharacter(NPC_GenerateCharacter("DeLeivaBrother_" + i, sTemp, "man", "man", 35, SPAIN, -1, true));
				if (i == 1)
				{
					sld.name = FindPersonalName("DeLeivaBrother_1_name");
					sld.lastname = FindPersonalName("DeLeivaBrother_1_lastname");
					sld.money = 34780;
					FantomMakeCoolFighter(sld, 37, 95, 70, "blade25", "pistol5", 100);
				}
				else
				{
					sld.name = FindPersonalName("DeLeivaBrother_2_name");
					sld.lastname = FindPersonalName("DeLeivaBrother_2_lastname");
					sld.money = 41340;
					FantomMakeCoolFighter(sld, 34, 95, 70, "blade33", "pistol4", 100);
				}
				sld.Dialog.Filename = "Quest\FraLineNpc_1.c";
				sld.SaveItemsForDead = true; // сохранять на трупе вещи
				sld.DontClearDead = true; // не убирать труп через 200с
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_warrior_DialogEnable(sld, true);
				ChangeCharacterAddressGroup(sld, "Mayak10", "goto", "goto12");
				LAi_group_MoveCharacter(sld, "PeaceGroup");
				AddLandQuestmark_Main(sld, "Fra_Line");
			}
			LAi_LocationFightDisable(&Locations[FindLocation("Mayak10")], true);
		break;
		//=================== Квест N6, доставка письма Олоне  ===================
		case "Fr6Olone_GuadeloupeBattle":
			Log_QuestInfo("Испанец установлен.");
			AddQuestRecord("Fra_Line_6_Olone", "7");
			AddQuestUserData("Fra_Line_6_Olone", "sSex", GetSexPhrase("ся", "лась"));
			bQuestDisableMapEnter = true;
			group_DeleteGroup("Spa_Attack");
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			// ==> Испанский кэп
			sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_1", "navy_off_spa_5", "man", "man", 35, SPAIN, -1, true));
			sld.DontRansackCaptain = true;
			FantomMakeCoolSailor(sld, SHIP_LINESHIP, "", CANNON_TYPE_CULVERINE_LBS32, 100, 95, 95);
			FantomMakeCoolFighter(sld, 35, 100, 90, BLADE_LONG, "pistol3", 150);
			Group_AddCharacter("Spa_Attack", "CaptainAttack_1");
			// ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Guadeloupe", "", "");
			Group_LockTask("Spa_Attack");
			pchar.quest.CanEnterToMap.win_condition.l1 = "NPC_Death";
			pchar.quest.CanEnterToMap.win_condition.l1.character = "CaptainAttack_1";
			pchar.quest.CanEnterToMap.win_condition = "CanEnterToMap";
		break;

		case "Fr6Olone_TalkWithOlone":
		//==> Олоне
			GetCharacterPos(pchar, &locx, &locy, &locz);
			chrDisableReloadToLocation = true;
			sld = characterFromID("Olone");
			LAi_SetCurHPMax(sld);
			ChangeCharacterAddress(sld, "Cumana_town", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//=================== Квест N7, спасение рядового Рока Бразильца  ===================
		case "Fr7RockBras_DelivShip":
			sld = characterFromId("RockBrasilian");
			if (LAi_IsDead(sld))
			{
				AddQuestRecord("Fra_Line_7_RockBras", "4");
				AddQuestUserData("Fra_Line_7_RockBras", "sSex", GetSexPhrase("", "а"));
				AddQuestUserData("Fra_Line_7_RockBras", "sSex1", GetSexPhrase("", "ла"));
				pchar.questTemp.State = "Fr7RockBras_RockIsDead";
				DeleteAttribute(sld, "RebirthPhantom");
				sld.LifeDay = 0;
			}
			else
			{
				AddQuestRecord("Fra_Line_7_RockBras", "3");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false);
				pchar.questTemp.State = "Fr7RockBras_RockIsSaved";
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);
				ChangeCharacterAddressGroup(sld, "Tortuga_townhall", "goto", "goto2");
			}
            RemoveLandQuestmark_Main(CharacterFromID("Santiago_Priest"), "Fra_Line");
            RemoveLandQuestmark_Main(CharacterFromID("Beliz_tavernkeeper"), "Fra_Line");
            RemoveLandQuestmark_Main(CharacterFromID("Havana_tavernkeeper"), "Fra_Line");
            RemoveLandQuestmark_Main(CharacterFromID("SantoDomingo_tavernkeeper"), "Fra_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Santiago_tavernkeeper"), "Fra_Line");
            AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;
		//=================== Квест N9, отбить нападение на Порт-о-Принс  ===================
		case "Fr9GuardPP_Late":
			pchar.quest.Fr9GuardPP_Fight.over = "yes";
			pchar.questTemp.State = "Fr9GuardPP_Late";
			AddQuestRecord("Fra_Line_9_GuardPortPax", "5");
			AddQuestUserData("Fra_Line_9_GuardPortPax", "sSex", GetSexPhrase("", "а"));
			SetCaptureTownByNation("PortPax", SPAIN);
			UpdateRelations();
			RefreshBattleInterface();
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;

		case "Fr9GuardPP_Fight":
			Log_QuestInfo("Испанская эскадра установлена. Это будет великая битва...");
			pchar.quest.Fr9GuardPP_Late.over = "yes";
			Island_SetReloadEnableGlobal("Hispaniola2", false);
			group_DeleteGroup("Spa_Attack");
			Group_FindOrCreateGroup("Spa_Attack");
			Group_SetType("Spa_Attack", "war");
			// ==> Испанские кэпы
			for (i = 1; i <= 6; i++)
			{
				switch (i)
				{
					case 1:
						ShipType = SHIP_MANOWAR;
						iRank = 40;
						Blade = "topor2";
						iTemp = CANNON_TYPE_CANNON_LBS42;
					break;
					case 2:
						ShipType = SHIP_GALEON_H;
						iRank = 30;
						Blade = "blade31";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
					break;
					case 3:
						ShipType = SHIP_BATTLESHIP;
						iRank = 38;
						Blade = "blade34";
						iTemp = CANNON_TYPE_CANNON_LBS32;
					break;
					case 4:
						ShipType = SHIP_WARSHIP;
						iRank = 35;
						Blade = "blade33";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
					break;
					case 5:
						ShipType = SHIP_GALEON_H;
						iRank = 31;
						Blade = "blade28";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
					break;
					case 6:
						ShipType = SHIP_LINESHIP;
						iRank = 36;
						Blade = "blade32";
						iTemp = CANNON_TYPE_CANNON_LBS32;
					break;
					/*case 7:
                        ShipType = SHIP_GALEON_H;
                        iRank = 30;
                        Blade = "topor2";
						iTemp = CANNON_TYPE_CULVERINE_LBS24;
                    break;
                    case 8:
                        ShipType = SHIP_BATTLESHIP;
                        iRank = 37;
                        Blade = "blade35";
						iTemp = CANNON_TYPE_CULVERINE_LBS32;
                    break;*/
				}
				sld = GetCharacter(NPC_GenerateCharacter("CaptainAttack_" + i, "navy_off_spa_1", "man", "man", iRank, SPAIN, 0, true)); //watch_quest_moment; ниже модель обновляется
				if (i == 2 || i == 5 || i == 7)
				{
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 80, 90, 70);
					FantomMakeCoolFighter(sld, iRank, 90, 90, Blade, "pistol3", 100);
				}
				else
				{
					FantomMakeCoolSailor(sld, ShipType, "", iTemp, 100, 100, 90);
					FantomMakeCoolFighter(sld, iRank, 100, 90, Blade, "pistol5", 200);
				}
				SetCaptanModelByEncType(sld, "war");
				Group_AddCharacter("Spa_Attack", "CaptainAttack_" + i);
			}
			// ==> стравливание
			Group_SetGroupCommander("Spa_Attack", "CaptainAttack_1");
			Group_SetTaskAttack("Spa_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Spa_Attack", PLAYER_GROUP);
			Group_SetAddress("Spa_Attack", "Hispaniola2", "", "");
			Group_LockTask("Spa_Attack");
			pchar.quest.Fr9GuardPP_WiWon.win_condition.l1 = "Group_Death";
			pchar.quest.Fr9GuardPP_WiWon.win_condition.l1.group = "Spa_Attack";
			pchar.quest.Fr9GuardPP_WiWon.win_condition = "Fr9GuardPP_WiWon";
			pchar.quest.Fr9GuardPP_DieHard.win_condition.l1 = "MapEnter";
			pchar.quest.Fr9GuardPP_DieHard.win_condition = "Fr9GuardPP_DieHard";
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;

		case "Fr9GuardPP_WiWon":
			Log_QuestInfo("Испанская эскадра разбита.");
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			pchar.quest.Fr9GuardPP_DieHard.over = "yes";
			if (LAi_IsDead(characterFromId("SoleiRoyalCaptain")))
			{
				AddQuestRecord("Fra_Line_9_GuardPortPax", "3");
				pchar.questTemp.State = "Fr9GuardPP_SoleiRoyalSunk";

			}
			else
			{
				pchar.questTemp.State = "Fr9GuardPP_GoodWork";
				AddQuestRecord("Fra_Line_9_GuardPortPax", "2");
			}
		break;

		case "Fr9GuardPP_DieHard":
			Log_QuestInfo("Свалил с поля боя, линейке конец.");
			pchar.questTemp.State = "Fr9GuardPP_DieHard";
			AddQuestRecord("Fra_Line_9_GuardPortPax", "4");
			group_DeleteGroup("Spa_Attack");
			Island_SetReloadEnableGlobal("Hispaniola2", true);
			pchar.quest.Fr9GuardPP_WiWon.over = "yes";
			sld = characterFromId("SoleiRoyalCaptain");
			RemoveCharacterCompanion(pchar, sld);
			sld.LifeDay = 0;
			SetCaptureTownByNation("PortPax", SPAIN);
			UpdateRelations();
			RefreshBattleInterface();
		break;
		//=================== Квест N12, конец войны  ===================
		case "Fr12EndOfWar_TakeOutShip":
			group_DeleteGroup("SoleiRoyal");
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  END Французская линейка
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////   Изабелла начало   //////////////////////////////////////////
		case "Romantic_Pirat_toTavern":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			FreeSitLocator("Pirates_tavern", "sit2");
			DoQuestReloadToLocation("Pirates_tavern", "sit", "sit2", "");
			sld = characterFromID("Atilla");
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;

		case "Romantic_Atilla_Beer_Timer":
			sld = characterFromID("Atilla");
			ChangeCharacterAddressGroup(sld, "None", "", "");
		break;

		case "Romantic_Pirat_toTavern_end":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			bDisableLandEncounters = false;
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false); //теперь открываем дом Изабеллы
			pchar.RomanticQuest = "toSalvator";
			AddQuestRecord("Romantic_Line", "3");
			LAI_SetPlayerType(pchar);
			DoQuestReloadToLocation("Pirates_tavern", "tables", "stay3", "");
			sld = CharacterFromID("Atilla");
			LAI_SetSitType(sld);
			Pchar.quest.Romantic_TalkInShop.win_condition.l1 = "location";
			Pchar.quest.Romantic_TalkInShop.win_condition.l1.location = "SanJuan_Store";
			Pchar.quest.Romantic_TalkInShop.win_condition = "Romantic_TalkInShop";
			PChar.quest.Romantic_TalkInShop.again = true; // вешаем на долго, тк не факт, что Pchar.RomanticQuest.TalkInShop = true; было
			PChar.quest.Romantic_TalkInShop.DontCheck = true;
			Pchar.RomanticQuest.PriestAsk = true;

			AddLandQuestmark_Main(CharacterFromID("SanJuan_Priest"), "Romantic_Line");
		break;

		case "RP_afterVisitBedroom":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			sld = characterFromID("Husband");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, Pchar, "", -1, 0);
		break;

		case "RP_talkWithHusbandIsOver":
			LAi_SetStayType(characterFromID("Husband"));
		break;

		case "Romantic_TalkInShop":
			if (CheckAttribute(Pchar, "RomanticQuest.TalkInShop"))
			{
				PChar.quest.Romantic_TalkInShop.over = "yes";
				characters[GetCharacterIndex("SanJuan_trader")].dialog.currentnode = "Romantic_1";
				sld = CharacterFromID("Isabella");
				LAi_SetStayType(sld);
				ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto3");
				sld.dialog.currentnode = "TalkInShop";
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "Romantic_TalkInShop_3", -1, 0);
			}
		break;

		case "Romantic_TalkInShop_2":
			sld = characterFromID("Isabella");
			LAi_ActorDialog(sld, Pchar, "", 1.0, 0);
		break;

		case "Romantic_TalkInShop_3":
			sld = CharacterFromID("SanJuan_trader");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, Pchar, "", 0.0, 0);
		break;

		case "Romantic_TalkInShop_end":
			chrDisableReloadToLocation = false;
			LAi_SetStayType(characterFromID("SanJuan_trader"));
			LAI_SetPlayerType(Pchar);
			AddQuestRecord("Romantic_Line", "4");
			sld = CharacterFromID("Isabella");
			LAi_SetCitizenType(sld);
			sld.dialog.currentnode = "TalkInChurch";
			DoQuestFunctionDelay("SetIsabellaTalker", 4.0);
		break;

		case "Romantic_Battle_in_Bedroom_1":
			sld = CharacterFromID("Husband");
			ChangeCharacterAddressGroup(sld, "SanJuan_houseS1Bedroom", "reload", "reload1");
			LAi_SetActorType(Pchar);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, Pchar, "Romantic_Battle_in_Bedroom_2", 3.0);
		break;

		case "Romantic_Battle_in_Bedroom_2":
			sld = CharacterFromID("Husband");
			sld.Dialog.CurrentNode = "Romantic_Battle_in_Bedroom";
			LAi_ActorWaitDialog(Pchar, sld);
			LAi_ActorDialog(sld, Pchar, "", 2.0, 0);
		break;

		case "Romantic_Battle_in_Bedroom_3":
			pchar.quest.RP_afterVisitBedroom.over = "yes";
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			LAi_SetPlayerType(pchar);
			ChangeCharacterReputation(pchar, -15);
			sld = CharacterFromID("Husband");
			Lai_SetImmortal(sld, false);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "TmpEnemy");
			LAi_group_SetHearRadius("TmpEnemy", 100.0);
			LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("TmpEnemy", "Romantic_Battle_in_Bedroom_End");
		break;

		case "Romantic_Battle_in_Bedroom_End":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			sld = CharacterFromID("Isabella");
			sld.Dialog.CurrentNode = "Murder";
			AddQuestRecord("Romantic_Line", "1");
			CloseQuestHeader("Romantic_Line");

            RemoveLandQuestmark_Main(CharacterFromID("Cumana_tavernkeeper"), "Romantic_Line");
            RemoveLandQuestmarkToFantoms_Main("Citizen", "Romantic_Line");
            RemoveLandQuestmarkToFantoms_Main("Commoner", "Romantic_Line");
		break;

		case "Romantic_Battle_in_Bedroom_4":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Husband");
			LAi_ActorRunToLocation(sld, "reload", "reload1", "SanJuan_houseSp6", "goto", "goto5", "Romantic_Battle_in_Bedroom_5", 2.0);
			AddQuestRecord("Romantic_Line", "2");
		break;

		case "Romantic_Battle_in_Bedroom_5":
			sld = CharacterFromID("Husband");
			LAi_SetHuberStayType(sld);
			LAi_SetStayHuberPointWindow(sld, "goto", "goto1");
			LAi_SetStayHuberPointMap(sld, "goto", "goto2");
		break;
		// церковь
		case "Romantic_TalkInChurch_end":
			sld = CharacterFromID("Isabella");
			LAi_SetStayType(sld);
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		break;
		// разговор с братом в порту куманы -->
		case "Romantic_Brother":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			sld = GetCharacter(NPC_GenerateCharacter("MigelDeValdes", "citiz_7", "man", "man", 5, SPAIN, -1, true)); //TODO: уникальную модельку брату
			sld.name = FindPersonalName("MigelDeValdes_name");
			sld.lastname = FindPersonalName("MigelDeValdes_lastname");
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			sld.DontClearDead = true; // не убирать труп через 200с
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			sld.dialog.currentnode = "Romantic_Brother_1";
			sld.greeting = "Gr_YoungMan";
			PlaceCharacter(sld, "goto", PChar.location);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 10.0, 0);
		break;

		case "Romantic_Brother_port":
			chrDisableReloadToLocation = true;
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			sld = CharacterFromID("MigelDeValdes");
			sld.dialog.currentnode = "Romantic_Brother_port_1";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			//PlaceCharacter(sld, "goto", PChar.location);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0.5, 0);
		break;
		// --> разговор в доме с братом, сцена 8
		case "Romantic_Brother_House":
			sld = CharacterFromID("Isabella");
			sld.dialog.currentnode = "Brother_1";
			ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto", "goto3");
			LAi_SetActorType(sld);
			sld = CharacterFromID("MigelDeValdes");
			sld.dialog.currentnode = "Romantic_Brother_port_1";
			ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto", "goto4");
			LAi_SetActorType(sld);
			pchar.RomanticQuest = "exitFromDetector";
		break;

		case "Romantic_Brother_House_3":
		// ГГ обратно
			SetMainCharacterIndex(1);
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			locCameraTarget(PChar);
			locCameraFollow();
			EndQuestMovie();
			LAi_SetCitizenType(characterFromID("Isabella"));
			sld = characterFromID("MigelDeValdes");
			LAi_SetCitizenType(sld);
			sld.dialog.currentnode = "Romantic_Brother_Thanks";
			sld = characterFromID("Husband");
			sld.dialog.currentnode = "WeWaitYouTonight";
			pchar.RomanticQuest = "DelivMigel"; //флаг "братан доставлен"
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //закрываем двери, чтобы не доставал до поры своим присутствием
			AddLandQuestmark_Main(CharacterFromID("Isabella"), "Romantic_Line");
		break;
		// --> смерть брата
		case "Romantic_DeadBrother_1":
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false);
			chrDisableReloadToLocation = true;
			SetMainCharacterIndex(1);
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			locCameraTarget(PChar);
			locCameraFollow();
			npchar = characterFromID("MigelDeValdes");
			LAi_group_MoveCharacter(npchar, "BrotherGroup");
			sld = characterFromID("Husband");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", "BrotherGroup", LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", "BrotherGroup", true);
			LAi_group_SetCheck("BrotherGroup", "Romantic_DeadBrother_2");
			LAi_LockFightMode(pchar, true); //саблю не достать
			EndQuestMovie();
		break;

		case "Romantic_DeadBrother_2":
			LAi_group_Delete("BrotherGroup");
			sld = characterFromID("Husband");
			sld.dialog.currentnode = "SeenMainHero";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;

		case "Romantic_DeadBrother_3":
			sld = characterFromID("Husband");
			LAi_SetStayType(sld);
			LocatorReloadEnterDisable("SanJuan_houseSp6", "reload2", true); //спальню тоже, а то может быть открыта
			LAi_LocationFightDisable(&Locations[FindLocation("SanJuan_houseSp6")], true);
			// Атиллу поставим в дом на Бермудах для диалога в дальнейшем после ареста
			sld = characterFromID("Atilla");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Pirates_houseF1", "sit", "sit2");
			sld.dialog.currentnode = "TalkingNews";
			AddLandQuestmark_Main(sld, "Romantic_Line");
			AddLandQuestmark_Main(CharacterFromID("Pirates_tavernkeeper"), "Romantic_Line");
		break;

		case "Romantic_DeadBrother_Cancel": //если ГГ не явлся к дому Изабеллы в течение суток
			pchar.RomanticQuest = "QuestOver";
			//LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //закрываем дверь в дом Изабеллы
			ChangeCharacterAddress(CharacterFromID("Husband"), "none", "");
			ChangeCharacterAddress(CharacterFromID("MigelDeValdes"), "none", "");
			CloseQuestHeader("Romantic_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Isabella"), "Romantic_Line");
		break;
		// --> попытка ареста ГГ
		case "Romantic_ArrestInHouse":
		// Атиллу поставим в дом на Бермудах для диалога в дальнейшем после ареста
			sld = characterFromID("Atilla");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Pirates_houseF1", "sit", "sit2");
			sld.dialog.currentnode = "TalkingNews";
			AddLandQuestmark_Main(sld, "Romantic_Line");
			AddLandQuestmark_Main(CharacterFromID("Pirates_tavernkeeper"), "Romantic_Line");
			//Сальватор убегает на выход
			npchar = characterFromID("Husband");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "SanJuan_houseS1Bedroom", "goto", "goto3", "", 5.0);
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true); //опять закрываем, чтобы ГГ до поры не ломился в дом
			//Команда на арест ГГ
			iTemp = FindColony("SanJuan");
			sTemp = NationShortName(sti(colonies[iTemp].nation));
			for (i = 1; i <= 3; i++)
			{
				if (i == 1)
				{
					if (sti(colonies[iTemp].HeroOwn))
					{
						Model = "officer_24"; //watch_quest_moment; наш слон
					}
					else
					{
						Model = "off_" + sTemp + "_3";
					}
					iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 6;
					Blade = "blade20";
				}
				else
				{
					if (sti(colonies[iTemp].HeroOwn))
					{
						Model = "citiz_" + (rand(9) + 31); //; наши маленькие слонята
					}
					else
					{
						Model = "urban_" + sTemp + "_" + (rand(7) + 1);
					}
					iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 2;
					Blade = "blade24";
				}
				sld = GetCharacter(NPC_GenerateCharacter("Soldier_" + i, Model, "man", "man", iRank, sti(colonies[iTemp].nation), 0, true));
				FantomMakeCoolFighter(sld, iRank, 100, 90, Blade, "pistol5", 200);
				sld.City = colonies[iTemp].id;
				sld.CityType = "soldier";
				sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
				sld.dialog.currentnode = "ArrestInHome_2";
				LAi_SetWarriorType(sld);
				if (i != 1) LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, GetNationNameByType(sti(colonies[iTemp].nation)) + "_citizens");
				ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "reload", "reload1");
			}
			sld = characterFromID("Soldier_1");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.5, 0);
		break;
		//через два месяца Алиллу - в дом
		case "Romantic_AtillaToHouse":
			sld = characterFromID("Atilla");
			LAi_SetSitType(sld);
			ChangeCharacterAddressGroup(sld, "Pirates_houseF1", "sit", "sit2");
			sld.dialog.currentnode = "AtillaInHouse";
			AddLandQuestmark_Main(sld, "Romantic_Line");
		break;
		//засада в доме Сальватора в Сан-Хуане
		case "Romantic_AmbushInHouse":
			Log_QuestInfo("Засада Сальватора.");
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			LAi_LocationFightDisable(&locations[FindLocation("SanJuan_houseSp6")], true);
			LAi_group_Delete("EnemyFight");
			for (i = 1; i <= 3; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bandit" + i, "citiz_" + (rand(9) + 51), "man", "man", 25, PIRATE, 0, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 25, 70, 60, BLADE_LONG, "pistol2", 20);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto", "goto" + i);
			}
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			sld.dialog.currentnode = "AmbushBandit";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		//атака брига с Изабеллой
		case "Romantic_BrigTimeOver":
			Log_QuestInfo("Не успел к бригу у Портобело. Изабелла погибла.");
			pchar.quest.Romantic_AttackBrig.over = "yes";
			AddQuestRecord("Romantic_Line", "14");
			QuestSetCurrentNode("Atilla", "Brig_Late"); //нода Атилле на опаздал
			AddLandQuestmark_Main(characterFromID("Atilla"), "Romantic_Line");
		break;

		case "Romantic_AttackBrig":
			Log_QuestInfo("Бриг найден, на абордаж!");
			pchar.quest.Romantic_BrigTimeOver.over = "yes";
			Island_SetReloadEnableGlobal("PortoBello", false);
			Group_FindOrCreateGroup("Pirate_Attack");
			Group_SetType("Pirate_Attack", "trade");
			sld = GetCharacter(NPC_GenerateCharacter("IsaAttackCap", "officer_2", "man", "man", 20, PIRATE, 0, true)); //watch_quest_moment
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			sld.dialog.currentnode = "BrigAbordage";
			FantomMakeCoolSailor(sld, SHIP_BRIG, FindPersonalName("IsaAttackCap_ship"), CANNON_TYPE_CULVERINE_LBS16, 75, 80, 70);
			FantomMakeCoolFighter(sld, 40, 75, 70, "blade24", "pistol3", 100);
			sld.DontRansackCaptain = true;
			Group_AddCharacter("Pirate_Attack", "IsaAttackCap");
			// ==> стравливание
			Group_SetGroupCommander("Pirate_Attack", "IsaAttackCap");
			Group_SetTaskAttack("Pirate_Attack", PLAYER_GROUP);
			Group_SetPursuitGroup("Pirate_Attack", PLAYER_GROUP);
			Group_SetAddress("Pirate_Attack", "PortoBello", "", "");
			Group_LockTask("Pirate_Attack");
			// ==> прерывания
			pchar.quest.Romantic_AfterBrigSunk.win_condition.l1 = "Character_sink";
			pchar.quest.Romantic_AfterBrigSunk.win_condition.l1.character = "IsaAttackCap";
			pchar.quest.Romantic_AfterBrigSunk.win_condition = "Romantic_AfterBrigSunk";
			pchar.quest.Romantic_BrigDieHard.win_condition.l1 = "MapEnter";
			pchar.quest.Romantic_BrigDieHard.win_condition = "Romantic_BrigDieHard";
		break;

		case "Romantic_BrigDieHard":
			pchar.quest.Romantic_AfterBrigSunk.over = "yes";
			group_DeleteGroup("Pirate_Attack");
			Island_SetReloadEnableGlobal("PortoBello", true);
			AddQuestRecord("Romantic_Line", "16");
			QuestSetCurrentNode("Atilla", "Brig_DieHard"); //нода Атилле на бриг ушёл от погони
			AddLandQuestmark_Main(characterFromID("Atilla"), "Romantic_Line");
		break;

		case "Romantic_AfterBrigSunk":
			pchar.quest.Romantic_BrigDieHard.over = "yes";
			Island_SetReloadEnableGlobal("PortoBello", true);
			group_DeleteGroup("Pirate_Attack");
			AddQuestRecord("Romantic_Line", "15");
			QuestSetCurrentNode("Atilla", "Brig_Sunk"); //нода Атилле бриг утонул
			AddLandQuestmark_Main(characterFromID("Atilla"), "Romantic_Line");
		break;

		case "Romantic_TaklInCabinBrig":
			sld = characterFromID("Isabella");
			sld.dialog.currentnode = "BrigAbordage";
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 5.0, 0);
		break;
		//засада в Портобело
		case "Romantic_AmbushInPortoBello":
			Log_QuestInfo("Засада Сальватора.");
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			LAi_LocationFightDisable(&locations[FindLocation("PortoBello_houseF2")], true);
			LAi_group_Delete("EnemyFight");
			for (i = 51; i <= 52; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bandit" + i, "citiz_" + i, "man", "man", 30, PIRATE, 0, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, 30, 80, 70, "topor2", "pistol3", 40);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				if (i == 51) sTemp = "goto4";
				else sTemp = "goto5";
				ChangeCharacterAddressGroup(sld, "PortoBello_houseF2", "goto", sTemp);
			}
			sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
			sld.dialog.currentnode = "AmbushPotroBello";
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			RemoveLandQuestmark_Main(CharacterFromID("PortoBello_tavernkeeper"), "Romantic_Line");
		break;

		case "Romantic_TalkPortoBello":
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("Isabella");
			sld.dialog.currentnode = "AmbushPortoBello";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 1.5);
		break;
		//базар с Изабеллой у дома Роситы
		case "Romantic_BelizCityTalk":
			chrDisableReloadToLocation = true;
			Pchar.GenQuest.Hunter2Pause = true; // ОЗГи на паузу.
			sld = CharacterFromID("Isabella");
			sld.dialog.currentnode = "BelizTalk";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto17");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0.0);
		break;
		//смерть охранника Изабеллы в пещере
		case "Romantic_BanditIsDead":
			sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0.0);
		break;
		//Сальватор в пещере
		case "Romantic_SalvatorInCave":
			LAi_LockFightMode(pchar, true); //саблю не достать
			sld = CharacterFromID("Husband");
			sld.dialog.currentnode = "TalkInCave";
			sld.items.jewelry5 = 100;
			sld.items.jewelry13 = 7;
			sld.items.jewelry14 = 6;
			sld.items.jewelry15 = 5;
			sld.items.jewelry17 = 30;
			sld.items.jewelry18 = 12;
			sld.items.indian1 = 1;
			sld.items.indian5 = 1;
			sld.items.indian6 = 1;
			sld.items.indian10 = 2;
			sld.items.indian12 = 1;
			sld.items.indian14 = 1;
			sld.items.jewelry12 = 12;
			sld.items.jewelry11 = 6;
			sld.items.jewelry10 = 20;
			sld.items.jewelry7 = 21;
			sld.items.jewelry6 = 11;
			sld.items.jewelry4 = 7;
			sld.items.jewelry3 = 15;
			sld.items.jewelry2 = 18;
			sld.items.jewelry1 = 31;
			sld.money = 350535;
			Lai_SetImmortal(sld, false);
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto7");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "Romantic_SalvatorIsDead":
			LAi_LocationDisableOfficersGen("Beliz_Cave_2", false); //офицеров пускать
			LAi_LocationDisableMonstersGen("Beliz_Cave_2", false); //монстров генерить
			QuestSetCurrentNode("Isabella", "SalvatorIsDead");
			sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0.0);
		break;

		// --> разговор Изабеллы с Роситой в доме после освобождения Изабеллы
		case "Romantic_DelivToRosita":
			if (GetCharacterIndex("Isabella") == -1)
			{
				QuestSetCurrentNode("Rosita", "IsabellaIsDead_Beliz");
				AddLandQuestmark_Main(characterFromID("Rosita"), "Romantic_Line");
			}
			else
			{
				pchar.RomanticQuest = "Beliz_exitFromDetector";
				QuestSetCurrentNode("Rosita", "SavedIsabella");
			}
		break;

		case "Romantic_DelivToRosita_2":
		// ГГ обратно
			SetMainCharacterIndex(1);
			PChar = GetMainCharacter();
			LAi_SetPlayerType(PChar);
			locCameraTarget(PChar);
			locCameraFollow();
			EndQuestMovie();
			LAi_SetCitizenType(characterFromID("Rosita"));
			sld = characterFromID("Isabella");
			LAi_SetCitizenType(sld);
			sld.dialog.currentnode = "RositaHouse";
			AddLandQuestmark_Main(sld, "Romantic_Line");
			//через месяц Изабеллу - в Сан-Хуан
			SetTimerCondition("Romantic_IsabellaToSanJuan", 0, 1, 0, false);
		break;

		case "Romantic_IsabellaToSanJuan":
			sld = CharacterFromID("Isabella");
			sld.lastname = FindPersonalName("MigelDeValdes_lastname");
			ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto", "goto1");
			sld.dialog.currentnode = "InSanJuanAgain";
			AddLandQuestmark_Main(sld, "Romantic_Line");
		break;

		case "Romantic_OutFromHouse":
			DoReloadCharacterToLocation("SanJuan_town", "reload", "houseSp6");
		break;

		case "Romantic_Widding_Cancel": //если ГГ не явлся к в церковь для венчания в течение суток
			pchar.quest.Isabella_widding.over = "yes";
			pchar.RomanticQuest = "QuestOver";
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", false); //открываем дом
			sld = characterFromID("Isabella");
			LAi_SetStayType(sld);
			sld.dialog.currentnode = "Cancel_Widding";
			AddLandQuestmark_Main(sld, "Romantic_Line");
			ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto", "goto1");
			sld = CharacterFromID("SanJuan_Priest");
			LAi_SetPriestType(sld);
		break;
		//свадьба Изабеллы и ГГ. Шампанского!!!!!
		case "Romantic_Padre":
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "barmen", "stay");
			DoQuestCheckDelay("Romantic_Padre_1", 1.0);
		break;

		case "Romantic_Padre_1":
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_25"), "Romantic_Padre_2", 0, 3);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 0, 40);
			RecalculateJumpTable();
		break;

		case "Romantic_Padre_2":
			StartQuestMovie(true, true, true);
			locCameraToPos(-1.52, 3.25, -3.36, false);
			sld = CharacterFromID("SanJuan_Priest");
			sld.dialog.currentnode = "Romantic_2";
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar("SanJuan_Priest", "", 0.0, 0.0);
			LAi_ActorFollow(PChar, sld, "ActorDialog_Any2Pchar", 0.0);
		break;

		case "Romantic_Padre_3":
			LAi_SetPlayerType(PChar);
			locCameraTarget(PChar);
			locCameraFollow();
			EndQuestMovie();
			sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			DoQuestCheckDelay("Romantic_fightInChurch", 2.0);
		break;
		//Нападение бандитов в церкви
		case "Romantic_fightInChurch":
			Log_QuestInfo("Последняя подстава Сальватора.");
			chrDisableReloadToLocation = true; // закрыть выход из локации.
			LAi_group_Delete("EnemyFight");
			iTemp = sti(2 + (MOD_SKILL_ENEMY_RATE / 1.5));
			iRank = 10 + MOD_SKILL_ENEMY_RATE * 2;
			for (i = 1; i <= iTemp; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("Bandit" + i, "citiz_" + (i + 50), "man", "man", iRank, PIRATE, 0, true)); //watch_quest_moment
				FantomMakeCoolFighter(sld, iRank, 80, 70, "topor2", "", 40);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				sld.Dialog.Filename = "Quest\Isabella\BrigCaptain.c";
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "SanJuan_church", "reload", "reload1");
			}
			sld.dialog.currentnode = "AmbushInChurch";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;

		case "Romantic_fightInChurch_1":
			sld = characterFromID("Isabella");
			sld.dialog.currentnode = "AmbushInChurch";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

		case "Romantic_fightInChurch_2":
			LAi_LocationFightDisable(loadedLocation, false);
			//падре в сторону
			sld = characterFromID("SanJuan_Priest");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "barmen", "bar2", "", -1);
			//деремся
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("EnemyFight", "SPAIN_CITIZENS", LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Romantic_afterFightInChurch");
			//Изабелла в сторону
			sld = characterFromID("Isabella");
			//LAi_SetImmortal(sld, false); // для тестов
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			GiveItem2Character(sld, "unarmed");
			EquipCharacterbyItem(sld, "unarmed");
			LAi_SetFightMode(sld, false);
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorRunToLocator(sld, "barmen", "bar1", "", -1);
		break;

		case "Romantic_afterFightInChurch":
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(loadedLocation, true);
			sld = CharacterFromID("SanJuan_Priest");
			LAi_SetPriestType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld = CharacterFromID("Isabella");
			if (LAi_IsDead(sld))
			{
				AddQuestRecord("Romantic_Line", "25");
				pchar.RomanticQuest = "IsabellaIsDead";
				QuestSetCurrentNode("Atilla", "IsabellaIsDead");
				QuestSetCurrentNode("Rosita", "IsabellaIsDead");
				AddLandQuestmark_Main(characterFromID("Atilla"), "Romantic_Line");
				AddLandQuestmark_Main(characterFromID("Rosita"), "Romantic_Line");
			}
			else
			{
				AddQuestRecord("Romantic_Line", "26");
				pchar.RomanticQuest = "IsabellaIsMyWife";
				QuestSetCurrentNode("Atilla", "IsabellaIsMyWife");
				QuestSetCurrentNode("Rosita", "IsabellaIsMyWife");
				LAi_SetCitizenType(CharacterFromID("Isabella"));
				QuestSetCurrentNode("Isabella", "IsabellaIsMyWife");
                AddLandQuestmark_Main(characterFromID("Atilla"), "Romantic_Line");
                AddLandQuestmark_Main(characterFromID("Rosita"), "Romantic_Line");
                AddLandQuestmark_Main(characterFromID("Isabella"), "Romantic_Line");
			}
		break;
		//новая сеймейная жизнь.
		case "Romantic_afterFirstTime":
			SaveCurrentQuestDateParam("RomanticQuest");
			IsabellaSetCurrentState("all");  //запомнинаем текущую статистику
			IsabellaCheckBreachState(); //тут же проверяем для обращений сразу же
			pchar.RomanticQuest.HorseCheck = pchar.questTemp.HorseQty; //запоминаем текущее кол-во посещения борделей
			IsabellaNullBudget(); //нулим семейный бюджет
			sld = CharacterFromID("Isabella");
			sld.greeting = "Gr_Isabella_1";
			SaveCurrentNpcQuestDateParam(sld, "sex"); //запомниаем последний секс
			sld.sex.control_year = sti(sld.sex.control_year) - 1; //-1 год (для первого раза)
			QuestSetCurrentNode("Rosita", "IsabellaIsWife"); //Росите ноду, по которой она помогать будет с проблемами
			pchar.RomanticQuest = "NewLifeForHero";
			AddQuestRecord("Romantic_Line", "28");
			AddQuestUserData("Romantic_Line", "IsabellaBuget", FindMoneyString(MOD_SKILL_ENEMY_RATE * 10000));
			CloseQuestHeader("Romantic_Line");
			RemoveLandQuestmark_Main(sld, "Romantic_Line");
			RemoveLandQuestmark_Main(characterFromID("Rosita"), "Romantic_Line");
			//прерывание на вход в дом Изабеллы
			Pchar.quest.Romantic_OutHome.win_condition.l1 = "location";
			Pchar.quest.Romantic_OutHome.win_condition.l1.location = "PuertoRico";
			Pchar.quest.Romantic_OutHome.win_condition = "Romantic_OutHome";
			Achievment_Set(ACH_Nashedshiy_svoyu_gavan);
		break;
		//запускаем проверку на пиратские делишки на входе в дом
		case "Romantic_EnterHome":
			if (CheckAttribute(pchar, "RomanticQuest.State"))
			{
				IsabellaCheckBreachState();
				pchar.RomanticQuest.Cheking = "";
				QuestSetCurrentNode("Isabella", "NewLife_hello");
				Pchar.quest.Romantic_OutHome.win_condition.l1 = "location";
				Pchar.quest.Romantic_OutHome.win_condition.l1.location = "PuertoRico";
				Pchar.quest.Romantic_OutHome.win_condition = "Romantic_OutHome";
			}
		break;

		case "Romantic_OutHome":
			if (CheckAttribute(pchar, "RomanticQuest.State"))
			{
				pchar.RomanticQuest = "NewLifeForHero";     //для проверки сроков отсутсвия на детекторе итем
				SaveCurrentQuestDateParam("RomanticQuest"); //эти самые сроки и запомним
				Pchar.quest.Romantic_EnterHome.win_condition.l1 = "location";
				Pchar.quest.Romantic_EnterHome.win_condition.l1.location = "SanJuan_houseSp6";
				Pchar.quest.Romantic_EnterHome.win_condition = "Romantic_EnterHome";
			}
		break;
		//сам секс собсно
		case "Romantic_Sex":
			sld = CharacterFromID("Isabella");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			if (GetNpcQuestPastMinutesParam(sld, "sex") > 10)
			{
				QuestSetCurrentNode("Isabella", "NewLife_Sex_Late");
				LAi_ActorDialog(sld, pchar, "", 1.0, 0);
			}
			else
			{
				DoQuestCheckDelay("PlaySex_1", 3.0);
			}
		break;

		case "PlaySex_1":
			iTemp = rand(13) + 1;
			switch (iTemp)
			{
				case 1: fTemp = 18.2; break;
				case 2: fTemp = 5.1;  break;
				case 3: fTemp = 19.3; break;
				case 4: fTemp = 8.2;  break;
				case 5: fTemp = 11.3; break;
				case 6: fTemp = 18.2; break;
				case 7: fTemp = 18.2; break;
				case 8: fTemp = 9.3;  break;
				case 9: fTemp = 19.4; break;
				case 10:fTemp = 12.2; break;
				case 11:fTemp = 19.4; break;
				case 12:fTemp = 12.3; break;
				case 13:fTemp = 10.2; break;
				case 14:fTemp = 11.2; break;
			}
			if (CheckAttrValue(&InterfaceStates, "NoAdultSounds", "0"))
				TEV.Sound.PlaySexSoundNum = iTemp;
			else
				TEV.Music.KeepPlaying = "";

			ResetSound();
			SetLaunchFrameFormParam("", "", 0, fTemp);
			SetLaunchFrameFormPic("loading\inside\censored1.tga");
			LaunchFrameForm();
			DoQuestCheckDelay("PlaySex_2", 1.0);
		break;

		case "PlaySex_2":
            if (CheckAttribute(&TEV, "Sound.PlaySexSoundNum"))
            {
				PlayStereoSound("sex\sex" + TEV.Sound.PlaySexSoundNum + ".wav");
				DeleteAttribute(&TEV, "Sound.PlaySexSoundNum");
            }
			AddTimeToCurrent(2, rand(30));
			LAi_SetCurHPMax(pchar);
			if (pchar.location == "SanJuan_houseS1Bedroom")
			{
				QuestSetCurrentNode("Isabella", "NewLife_afterSex");
				LAi_SetStayType(CharacterFromID("Isabella"));
			}
			//квест официантки
			if (pchar.questTemp.different == "FackWaitress_facking")
			{
				sld = characterFromId("WairessQuest");
				ChangeCharacterAddress(sld, "none", "");
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterHealth(pchar, 3);
				AddCharacterExpToSkill(pchar, "Fencing", -15);
				AddCharacterExpToSkill(pchar, "Pistol", -15);
				ChangeCharacterReputation(pchar, -1);
				if (sti(pchar.questTemp.different.FackWaitress.Kick) != 1)
				{
					pchar.questTemp.different = "FackWaitress_fackNoMoney";
					AddCharacterExpToSkill(pchar, "Fortune", 100);
				}
				pchar.money = sti(pchar.money) / sti(pchar.questTemp.different.FackWaitress.Kick);
				chrDisableReloadToLocation = false;
			}
			//квест развода хозяйки борделя
			if (pchar.questTemp.different == "HostessSex" && CheckAttribute(pchar, "questTemp.different.HostessSex.city"))
			{
				sld = characterFromId(pchar.questTemp.different.HostessSex.city + "_Hostess");
				ChangeCharacterAddressGroup(sld, pchar.questTemp.different.HostessSex.city + "_SecBrRoom", "goto", "goto8");
				LAi_SetOwnerTypeNoGroup(sld);
				DeleteAttribute(pchar, "questTemp.different.HostessSex");
				pchar.questTemp.different = "free";
			}
			if (CheckAttribute(pchar, "GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "EncGirl_facking")
			{
				sld = characterFromId("CangGirl");
				ChangeCharacterAddress(sld, "none", "");
				AddCharacterExpToSkill(pchar, "Leadership", 20);
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				AddCharacterExpToSkill(pchar, "Fencing", -20);
				AddCharacterExpToSkill(pchar, "Pistol", -20);
				AddCharacterHealth(pchar, 5);
				ChangeCharacterReputation(pchar, -1);
				//чем больше удачи, тем меньше шанс потерять деньги
				iTemp = 11 - sti(GetCharacterSPECIAL(pchar, SPECIAL_L));
				if (drand(iTemp) != 0) pchar.money = sti(pchar.money) - makeint(sti(pchar.money) / 15);
				else AddCharacterExpToSkill(pchar, "Fortune", 100);
				chrDisableReloadToLocation = false;
				SetFunctionTimerCondition("EncGirl_SpeakTavernKeeper", 0, 0, 1, false);
			}
		break;

		case "Romantic_IsabellaBackToHall":
			Pchar.quest.Romantic_Sex.over = "yes";
			sld = CharacterFromID("Isabella");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "SanJuan_houseSp6", "goto", "goto1");
			QuestSetCurrentNode("Isabella", "NewLife");
		break;

		case "sleep_in_home":
			DoQuestReloadToLocation("SanJuan_houseS1Bedroom", "goto", "goto4", "restore_hp");
		break;

		case "royal_sleep":
			DoQuestReloadToLocation(pchar.location, "goto", RandPhraseSimple("goto6", "goto7"), "restore_hp");
		break;
		/////////////////////////////////////   Изабелла конец   //////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  Квест Аскольда начало
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		int iCannonType, iShipType;
		string sShipName;
		case "Ascold_AttackTenManowars":
			LocatorReloadEnterDisable("Tenotchitlan_Jungle_02", "reload3_back", true); //закроем до поры храм
			Island_SetReloadEnableGlobal("Caiman", false);
			pchar.questTemp.Ascold = "ILookedThisAss";
			// ==> корабль, куда помещаем предметы
			i = 1;
			pchar.questTemp.Ascold.Ship = "AscoldCaptainAttack_" + i;
			Log_QuestInfo("Журнал в мановаре с ID кэпа: " + pchar.questTemp.Ascold.Ship);
			Group_FindOrCreateGroup("Ascold_Spa_Attack");
			Group_SetType("Ascold_Spa_Attack", "war");
			// ==> Испанские кэпы
			SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
			for (i = 1; i <= 6; i++)
			{
				iRank = 30 + rand(5);
				sTemp = "AscoldCaptainAttack_" + i;
				switch (i)
				{
					case 1:
						iCannonType = CANNON_TYPE_CANNON_LBS42;
						iShipType = SHIP_SANTISIMA;
						sShipName = FindPersonalName("AscoldCaptainAttack_ship");
						Blade = "blade20";
					break;
					case 2:
						iCannonType = CANNON_TYPE_CANNON_LBS32;
						iShipType = SHIP_BATTLESHIP;
						sShipName = "";
						Blade = "topor2";
					break;
					case 3:
						iCannonType = CANNON_TYPE_CULVERINE_LBS32;
						iShipType = SHIP_WARSHIP;
						sShipName = "";
						Blade = "blade15";
					break;
					case 4:
						iCannonType = CANNON_TYPE_CANNON_LBS32;
						iShipType = SHIP_WARSHIP;
						sShipName = "";
						Blade = "blade31";
					break;
					case 5:
						iCannonType = CANNON_TYPE_CANNON_LBS24;
						iShipType = SHIP_CORVETTE;
						sShipName = "";
						Blade = "blade21";
					break;
					case 6:
						iCannonType = CANNON_TYPE_CANNON_LBS24;
						iShipType = SHIP_CORVETTE;
						sShipName = "";
						Blade = "blade34";
					break;
				}
				sld = GetCharacter(NPC_GenerateCharacter(sTemp, "navy_off_spa_1", "man", "man", iRank, SPAIN, -1, true)); //watch_quest_moment; ниже модель обновляется
				FantomMakeCoolSailor(sld, iShipType, sShipName, iCannonType, 90, 90, 90);
				FantomMakeCoolFighter(sld, iRank, 90, 90, Blade, "pistol3", 100);
				SetCaptanModelByEncType(sld, "war");
				sld.DontRansackCaptain = true;
				sld.AnalizeShips = true;
				sld.SuperShooter = true;
				sld.ship.Crew.Morale = 100;
				ChangeCrewExp(sld, "Sailors", 100);
				ChangeCrewExp(sld, "Cannoners", 100);
				ChangeCrewExp(sld, "Soldiers", 90);
				SetRandGeraldSail(sld, sti(sld.Nation));
				Group_AddCharacter("Ascold_Spa_Attack", sTemp);
			}
			// ==> стравливание
			Group_SetGroupCommander("Ascold_Spa_Attack", "AscoldCaptainAttack_1");
			//Group_SetPursuitGroup("Ascold_Spa_Attack", PLAYER_GROUP); //TODO
			Group_SetAddress("Ascold_Spa_Attack", "Caiman", "quest_ships", "quest_ship_6");
			Group_SetTaskAttack("Ascold_Spa_Attack", PLAYER_GROUP);
			Group_LockTask("Ascold_Spa_Attack");
			// ==> прерывание на убиение эскадры
			pchar.quest.Ascold_VictoryManowar.win_condition.l1 = "Group_Death";
			pchar.quest.Ascold_VictoryManowar.win_condition.l1.group = "Ascold_Spa_Attack";
			pchar.quest.Ascold_VictoryManowar.win_condition = "Ascold_VictoryManowar";
			pchar.quest.Ascold_DieHardManowar.win_condition.l1 = "MapEnter";
			pchar.quest.Ascold_DieHardManowar.win_condition = "Ascold_DieHardManowar";
            AddLandQuestmark_Main(CharacterFromID("Ascold"), "Ascold");
		break;

		case "Ascold_VictoryManowar":
			LocatorReloadEnterDisable("Tenotchitlan_Jungle_02", "reload3_back", false); //откроем храм
			Island_SetReloadEnableGlobal("Caiman", true);
			group_DeleteGroup("Ascold_Spa_Attack");
			pchar.quest.Ascold_DieHardManowar.over = "yes";
			pchar.questTemp.Ascold = "Ascold_ManowarsDead";
			DeleteAttribute(PChar, "questTemp.Ascold.Ship");
			AddQuestRecord("Ascold", "9");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("", "а"));
			Pchar.quest.Ascold_FightNearTemple.win_condition.l1 = "location";
			Pchar.quest.Ascold_FightNearTemple.win_condition.l1.location = "Temple";
			Pchar.quest.Ascold_FightNearTemple.win_condition = "Ascold_FightNearTemple";
			AddLandQuestmark_Main(CharacterFromID("Ascold"), "Ascold");
		break;

		case "Ascold_DieHardManowar":
			Island_SetReloadEnableGlobal("Caiman", true);
			group_DeleteGroup("Ascold_Spa_Attack");
			pchar.quest.Ascold_VictoryManowar.over = "yes";
			pchar.questTemp.Ascold = "Ascold_ManowarsNoDead";
			DeleteAttribute(PChar, "questTemp.Ascold.Ship");
			AddQuestRecord("Ascold", "9_1");
			AddQuestUserData("Ascold", "sSex", GetSexPhrase("", "а"));
			AddLandQuestmark_Main(CharacterFromID("Ascold"), "Ascold");
		break;

		case "Ascold_FightNearTemple":
			chrDisableReloadToLocation = true; // закрыть выход из локации
			LAi_group_Delete("EnemyFight");
			for (i = 1; i <= 20; i++)
			{
				if (i == 1 || i == 8 || i == 11 || i == 15)
				{
					sld = GetCharacter(NPC_GenerateCharacter("Enemy_" + i, "off_spa_" + (rand(1) + 5), "man", "man", 25, SPAIN, 0, true)); //watch_quest_moment
					FantomMakeCoolFighter(sld, 25, 80, 80, BLADE_LONG, "pistol5", 100);
				}
				else
				{
					sld = GetCharacter(NPC_GenerateCharacter("Enemy_" + i, "sold_spa_" + (rand(7) + 9), "man", "man", 20, SPAIN, 0, true));
					FantomMakeCoolFighter(sld, 20, 50, 50, BLADE_LONG, "pistol3", 40);
				}
				LAi_SetWarriorType(sld);
				if (i < 16) LAi_warrior_SetStay(sld, true);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				ChangeCharacterAddressGroup(sld, "Temple", "goto", "goto" + i);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			//LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Ascold_WinNearTemple");
		break;

		case "Ascold_WinNearTemple":
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(pchar.location, "reload2", false);
			AddQuestRecord("Ascold", "14");
			pchar.quest.Ascold_fightInsideTemple.win_condition.l1 = "location";
			pchar.quest.Ascold_fightInsideTemple.win_condition.l1.location = "Temple_Inside";
			pchar.quest.Ascold_fightInsideTemple.function = "Ascold_fightInsideTemple";
			AddLandQuestmark_Main(CharacterFromID("Ascold"), "Ascold");
		break;

		case "Ascold_InGraveAfterFight":
			pchar.questTemp.Ascold = "Ascold_MummyIsLive";
			LAi_LocationFightDisable(&Locations[FindLocation("Guadeloupe_Cave")], true);
			LAi_LocationDisableMonstersGen("Guadeloupe_Cave", true);
			sld = GetCharacter(NPC_GenerateCharacter("LeifEricson", "Leif_Erikson", "skeleton", "man", 100, PIRATE, -1, true));
			sld.skeleton = "1";
			FantomMakeCoolFighter(sld, 100, 100, 100, "vikingHeroSword", "", 3000);
			sld.name = FindPersonalName("LeifEricson_name");
			sld.lastname = FindPersonalName("LeifEricson_lastname");
			sld.Dialog.Filename = "Quest\LeifEricson.c";
			sld.SaveItemsForDead = true; // сохранять на трупе вещи
			GiveItem2Character(sld, "Azzy_bottle");
			sld.DontClearDead = true; // не убирать труп через 200с
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "locator1");
			LAi_SetImmortal(sld, true);
			LAi_CharacterPlaySound(sld, "Gr_LeifEricson");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar("LeifEricson", "", -1, 0.0);
			LAi_ActorFollow(PChar, sld, "ActorDialog_Any2Pchar", 0.0);
		break;

		case "Ascold_MummyFightTown":
			for (i = 1; i <= 13; i++)
			{
				iTemp = GetCharacterIndex("MySkel" + i);
				if (iTemp == -1)
					continue;
				sld = &Characters[iTemp];
				sld.LifeDay = 0;
				ChangeCharacterAddress(sld, "none", "");
			}
			Pchar.GenQuestFort.fortCharacterIdx = GetCharIDXForTownAttack(pchar.location);
			DeleteQuestAttribute("Union_with_Escadra");
			sld = GetCharacter(sti(Pchar.GenQuestFort.fortCharacterIdx));
			SetLocationCapturedState("BasTer_town", true);
			DoQuestCheckDelay("Capture_Forts", 0.5);
			// AlexBlade > fix Порчи отношений - Слишком много лишних телодвижений
			// Ship_NationAgressive(sld, sld);
			Log_SetStringToLog(StringFromKey("InfoMessages_57"));
			characters[GetCharacterIndex("BasTer_Mayor")].dialog.captureNode = "Ascold_MummyAttack"; //капитулянтская нода мэра
			AddLandQuestmark_Main(CharacterFromID("BasTer_Mayor"), "Ascold");
		break;

		case "Ascold_ExitCave":
			ref boarder = &characters[sti(pchar.Fellows.Old.Officers.first_idx)];
			if (boarder.chr_ai.type != "officer") break; //если зачем-то сняли с должности, находясь в пещере
			boarder.dialog.filename.origin = boarder.dialog.filename;
			boarder.dialog.filename = "Quest\ForAll_dialog.c";
			boarder.dialog.currentnode = "Ericson_cave";

			LAi_SetActorType(pchar);
			LAi_SetActorType(boarder);

			SetActorDialogAny2Pchar(boarder.id, "", -1, 0.0);
			LAi_ActorFollow(pchar, boarder, "ActorDialog_Any2Pchar", -1);
			LAi_ActorFollow(boarder, pchar, "ActorDialog_Any2Pchar", -1);

			DeleteAttribute(pchar, "Fellows.Old");
		break;

		case "Ascold_AzzyIsFree":
			LAi_LocationFightDisable(&Locations[FindLocation("Shore28")], true);
			ChangeCharacterAddressGroup(&characters[GetCharacterIndex("Azzy")], "Shore28", "goto", "goto25");
			DoReloadCharacterToLocation("Shore28", "goto", "goto24");
			DoQuestCheckDelay("Azzy_IsFree", 4.0);
		break;

		case "Azzy_IsFree":
			LAi_SetActorType(PChar);
			sld = characterFromID("Azzy");
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.0);
		break;

		case "Azzy_PlusSkill":
			DeleteAttribute(pchar, "questTemp.Azzy.AddSpecial");
			// boal оптимизация скилов -->
			DelBakSkillAttr(pchar);
			ClearCharacterExpRate(pchar);
			RefreshCharacterSkillExpRate(pchar);
			// boal оптимизация скилов <--
			WaitDate("", 0, 0, 2, 0, 1);
			RecalculateJumpTable();
			StoreDayUpdate();
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_20"), "", 0, 4);
			LaunchFrameForm();
		//DoReloadCharacterToLocation("Tortuga_town", "reload", "reload91");
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  Квест Аскольда-Аззи конец
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  Пиратская линейка     начало
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "PiratesLine_toTavern":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			FreeSitLocator("PuertoPrincipe_tavern", "sit2");
			DoQuestReloadToLocation("PuertoPrincipe_tavern", "sit", "sit2", "");
			LAi_SetSitType(pchar);
			sld = CharacterFromID("QuestPirate1");
			sld.dialog.currentnode = "Tavern_1";
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;

		case "PiratesLine_q1_MorganGoTo":
			sld = characterFromID("Henry Morgan");
			sld.Dialog.CurrentNode = "PL_Q1_1";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

		case "PQ5_Morgan_2":
			LAi_SetActorType(pchar);
			LAi_ActorTurnToCharacter(pchar, characterFromID("Henry Morgan"));
			sld = characterFromID("CapGoodly");
			ChangeCharacterAddressGroup(sld, "PortRoyal_houseS1", "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto1", "PQ5_Morgan_3", -1.0);
		break;

		case "PQ5_Morgan_3":
			SetMainCharacterIndex(GetCharacterIndex("CapGoodly"));
			PChar = GetMainCharacter();
			locCameraToPos(2.49, 2.65, -11.076, false);
			LAi_SetActorType(PChar);
			LAi_ActorDialog(PChar, characterFromID("Henry Morgan"), "", 0, 0);
		break;

		case "PQ6_afterBattle":
		//убираем Джона Лидса
			chrDisableReloadToLocation = false;
			group_DeleteGroup("LidsGroup");
			LocatorReloadEnterDisable("Shore7", "boat", false); //откроем выход в море
			SetQuestHeader("Pir_Line_6_Jackman");
			AddQuestRecord("Pir_Line_6_Jackman", "4");
			AddQuestUserData("Pir_Line_6_Jackman", "sSex", GetSexPhrase(StringFromKey("SexPhrase_15"), StringFromKey("SexPhrase_16")));
			//HardCoffee Jackman dialogue
			pchar.QuestTemp.PirLine_quests_task = "PL_Q6_after";
			AddLandQuestmark_Main(CharacterFromID("Jackman"), "Pir_Line");
		//QuestSetCurrentNode("Jackman", "PL_Q6_after");
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  Пиратская линейка     конец
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//поисковый генератор
		case "CitizSeekCap_afterCabinFight":
			sld = GetCharacter(NPC_GenerateCharacter(pchar.GenQuest.CitizSeekCap.label + "_" + pchar.GenQuest.CitizSeekCap.WifeCity, pchar.GenQuest.CitizSeekCap.model, pchar.GenQuest.CitizSeekCap.sex, pchar.GenQuest.CitizSeekCap.ani, 5, pchar.GenQuest.CitizSeekCap.nation, -1, false));
			sld.name = pchar.GenQuest.CitizSeekCap.WifeName;
			sld.lastname = pchar.GenQuest.CitizSeekCap.WifeLastname;
			sld.dialog.filename = "Quest\ForAll_dialog.c";
			sld.dialog.currentnode = pchar.GenQuest.CitizSeekCap.label + "_Board";
			sld.quest.SeekCap = pchar.GenQuest.CitizSeekCap.label;
			sld.quest.cribCity = pchar.GenQuest.CitizSeekCap.WifeCity;
			DeleteAttribute(pchar, "GenQuest.CitizSeekCap");
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		break;
		case "CitizSeekCap_GivePrisoner":
			sld = GetCharacter(NPC_GenerateCharacter(pchar.GenQuest.CitizSeekCap.label + "_" + pchar.GenQuest.CitizSeekCap.PrisonerCity, pchar.GenQuest.CitizSeekCap.model, pchar.GenQuest.CitizSeekCap.sex, pchar.GenQuest.CitizSeekCap.ani, 5, sti(pchar.GenQuest.CitizSeekCap.nation), -1, false));
			sld.name = pchar.GenQuest.CitizSeekCap.PrisonerName;
			sld.lastname = pchar.GenQuest.CitizSeekCap.PrisonerLastname;
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			log_info(StringFromKey("InfoMessages_241", sld.name)); // 170712
			PlaySound("interface\notebook.wav");
			DeleteAttribute(pchar, "GenQuest.CitizSeekCap");
		break;

		case "PQ8_jungle_afterFight":
			chrDisableReloadToLocation = false;
			pchar.questTemp.piratesLine = "Panama_inJungleIsOver";
			iTemp = GetCharacterIndex("Richard_Soukins");
			if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
			{
				sld = &characters[iTemp];
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER_OWN);
				for (i = 1; i <= sti(pchar.questTemp.piratesLine.crewRichard); i++)
				{
					iTemp = GetCharacterIndex("RSpirate_" + i);
					if (iTemp != -1)
					{
						LAi_group_MoveCharacter(&characters[iTemp], sld.chr_ai.group);
					}
				}
				for (i = 1; i <= sti(pchar.questTemp.piratesLine.crewRichard); i++)
				{
					iTemp = GetCharacterIndex("RSmush_" + i);
					if (iTemp != -1)
					{
						LAi_group_MoveCharacter(&characters[iTemp], sld.chr_ai.group);
					}
				}
				for (i = 1; i <= 3; i++)
				{
					iTemp = GetCharacterIndex("RSofficer_" + i);
					if (iTemp != -1)
					{
						LAi_group_MoveCharacter(&characters[iTemp], sld.chr_ai.group);
					}
				}
			}
		break;

		case "PQ8_ExitTown_afterFight":
			LocatorReloadEnterDisable("Shore48", "boat", false); //откроем выход из бухты
			LocatorReloadEnterDisable("PortoBello_Jungle_01", "reload1_back", false); //открываем подходы к Панаме
			SetLocationCapturedState("Panama_town", true); //убираем всех из города
			sld = characterFromId("Henry Morgan");
			sld.dialog.currentNode = "PL_Q8_ExTPanama";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квесты ГПК				===>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "WaitingForConditionsLSC":
			DeleteAttribute(&TEV, "waitingForConditionsLSC");
			iTemp = FindIsland("LostShipsCity");
			Islands[iTemp].reload_enable = true;
		break;

		case "ReloadEnableLSC":
			iTemp = FindIsland("LostShipsCity");
			Islands[iTemp].visible = true;
			Islands[iTemp].reload_enable = true;
			Islands[iTemp].alwaysStorm = true; //живем в штормах
			Islands[iTemp].MaxSeaHeight = 2.0;
			Islands[iTemp].storm = true;
			Islands[iTemp].tornado = true;
			//даже если сами перешли то катсцены не избежать
			pchar.quest.EnterToSeaLSC.win_condition.l1 = "location";
			pchar.quest.EnterToSeaLSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.EnterToSeaLSC.win_condition = "PutToLSC";
		break;

		case "DiggingDoneLSC":
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_21"), "", 0.1, 2.0);
			pchar.questTemp.LSC = "DiggingDoneLSC";
			AddQuestRecord("ISS_PoorsMurder", "16");
			WaitDate("", 0, 0, 0, 0, 10);
			LaunchFrameForm();
			RefreshLandTime();
			RecalculateJumpTable();
			Whr_UpdateWeather();
		break;

		case "DaytimeOutingLSC":
			fTemp = GetHour();
			if (fTemp >= 14) fTemp = 24 - fTemp + 14;
			else fTemp = 14 - fTemp;
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_34"), "Reload_To_Location", 5, 3);
			SetLaunchFrameReloadLocationParam("OutRHouse", "rld", "loc0", "DaytimeOutingLSC_2");
			WaitDate("", 0, 0, 0, fTemp, 0);
			LaunchFrameForm();

			LAi_LocationDisableOfficersGen("FortOrange_Mine", true);
			LAi_LocationDisableOfficersGen("OutRHouse", true);

			//убираются носильщики и мушкетер на дереве
			for (i = 0; i<MAX_CHARACTERS; i++)
			{
				makeref(npchar, characters[i]);
				if (npchar.location == "FortOrange_Mine")
				{
					if (CheckAttribute(npchar, "model.animation") && npchar.model.animation == "genres")
					{
						LAi_SetImmortal(npchar, false);
						npchar.lifeday = 0;
						ChangeCharacterAddress(npchar, "none", "");
					}
					else if (CheckAttribute(npchar, "location.locator") && npchar.location.locator == "soldier1")
					{
						npchar.lifeday = 0;
						ChangeCharacterAddress(npchar, "none", "");
					}
				}
			}
		break;

		case "DaytimeOutingLSC_2":
			sld = CharacterFromID("TizerDenLSC");
			ChangeCharacterAddressGroup(sld, "OutRHouse", "rld", "loc1");
			LAi_SetActorType(sld);
			sld.Dialog.CurrentNode = "DaytimeOutingLSC";
			LAi_SetActorType(pchar);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "DaytimeOutingLSC_3":
			Lai_SetPlayerType(pchar);
			LocatorReloadEnterDisable("OutRHouse", "reload2_back", true);
			sld = CharacterFromID("TizerDenLSC");
			LAi_ActorRunToLocatorNoCheck(sld, "reload", "reload1_back", "", 15.0);
			pchar.quest.DaytimeOutingLSC_4.win_condition.l1 = "location";
			pchar.quest.DaytimeOutingLSC_4.win_condition.l1.location = "FortOrange_Mine";
			pchar.quest.DaytimeOutingLSC_4.win_condition = "DaytimeOutingLSC_4";
		break;

		case "DaytimeOutingLSC_4":
			chrDisableReloadToLocation = true;
			pchar.quest.DaytimeOutingLSC_5.win_condition.l1        			= "locator";
			pchar.quest.DaytimeOutingLSC_5.win_condition.l1.location 		= "FortOrange_Mine";
			pchar.quest.DaytimeOutingLSC_5.win_condition.l1.locator_group 	= "rld";
			pchar.quest.DaytimeOutingLSC_5.win_condition.l1.locator 		= "attack1";
			pchar.quest.DaytimeOutingLSC_5.win_condition 					= "DaytimeOutingLSC_5";
			sld = CharacterFromID("TizerDenLSC");
			LAi_type_actor_Reset(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_Mine", "officers", "reload6_1");
			LAi_ActorRunToLocator(sld, "officers", "reload3_3", "", 20);
		break;

		case "DaytimeOutingLSC_5":
			LAi_SetActorType(pchar);
			sld = CharacterFromID("TizerDenLSC");
			LAi_ActorWaitDialog(pchar, sld);
			LAi_type_actor_Reset(sld);
			sld.Dialog.CurrentNode = "DaytimeOutingLSC_1";
			LAi_ActorDialog(sld, pchar, "", 1, 0);
			chrDisableReloadToLocation = false;
		break;

		case "DaytimeOutingLSC_6":
			sld = GetCharacter(NPC_GenerateCharacter("TizerSlaveLSC", "Slave_2", "man", "man", 7, PIRATE, 0, false));
			sld.dialog.filename = "Quest\LostShipsCity\TizerDen.c";
			sld.dialog.CurrentNode = "SlaveDialog";
			sld.name = FindPersonalName("Slave_name");
			sld.lastname = "";
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_Mine", "quest", "Slave");
			sld = CharacterFromID("TizerDenLSC");
			LAi_SetImmortal(sld, false);
			LAi_ActorRunToLocator(sld, "quest", "Tizer", "DaytimeOutingLSC_7_1", 10);
			DoQuestCheckDelay("DaytimeOutingLSC_7", 0.3);
		break;

		case "DaytimeOutingLSC_7":
			StartQuestMovie(true, true, true);
			LAi_ActorRunToLocator(pchar, "quest", "Hero", "DaytimeOutingLSC_8", 10);

			locCameraFlyToPositionLookToPoint(72.6, 1.5, -21.6, 72.8, 2.0, -3.7, 0.27, -35.9, 220.00, 1.0, 300);
			Pchar.FuncCameraFly = "DaytimeOutingLSCFunc";
		break;

		case "DaytimeOutingLSC_7_1":
			LAi_ActorTurnToLocator(CharacterFromID("TizerDenLSC"), "quest", "Slave");
		break;

		case "DaytimeOutingLSC_8":
			sld = CharacterFromID("TizerSlaveLSC");
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "DaytimeOutingLSC_9":
			LAi_group_Delete("EnemyFight");
			for (i = 0; i < 15; i++)
			{
				if (i == 0)
				{
					sld = GetCharacter(NPC_GeneratePhantomCharacter("rivados_mush", PIRATE, MAN, 0));
					sld.id = "FreeSlave"+i;
					FantomMakeCoolFighter(sld, sti(sld.rank), 80, 80, "unarmed", "mortar", 50);
					ChangeCharacterAddressGroup(sld, pchar.location, "soldiers",  "soldier1");
				}
				else
				{
					sld = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
					sld.id = "FreeSlave"+i;
					if (i == 14)
						ChangeCharacterAddressGroup(sld, pchar.location, "rld",  "warrior");
					else
						ChangeCharacterAddressGroup(sld, pchar.location, "quest",  "Watcher"+i);
				}
				LAi_SetImmortal(sld, true);
				LAi_SetActorType(sld);
				LAi_ActorTurnToLocator(sld, "quest", "effect1");
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			locCameraFlyToPositionLookToPoint(72.8, 2.7, -3.7, 79.8, 13.7, -1.7, 0.27, -35.9, 100.00, 1.0, 500);
			pchar.FuncCameraFly = "DaytimeOutingLSCFunc_2";
		break;

		case "AhtungMinetown":
			sld = CharacterFromID("Minetown_Commend");
			LAi_ActorFollowEverywhere(sld, "", -1);
			LAi_group_Delete("EnemyFight");

			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i = 1; i < 3; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddress(npchar, pchar.location, "mush" + i);
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "AhtungMinetown_1");
			pchar.quest.EnterToFortOrangeTownLSC.win_condition.l1 = "location";
			pchar.quest.EnterToFortOrangeTownLSC.win_condition.l1.location = "FortOrange_town";
			pchar.quest.EnterToFortOrangeTownLSC.function = "EnterToFortOrangeTownLSC";
			LAi_LocationDisableOfficersGen("FortOrange_town", true);
		break;

		case "AhtungMinetown_1":
			sld = CharacterFromID("Minetown_Commend");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			LocatorReloadEnterDisable("FortOrange_Mine", "reload1", false);
		break;

		case "AhtungMinetown_2":
			EndQuestMovie();
			pchar.FuncCameraFly = "";
			locCameraNextState();
			locCameraTarget(pchar);
			locCameraFollow();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload12", "TheStarsAlignedLSC", 10.0);
			LAi_ActorRunToLocator(CharacterFromID("TitherDenLSC"), "reload", "reload12", "", 10.0);
			//готовим локу выхода из города
			LAi_LocationDisableOfficersGen("FortOrange_ExitTown", true);
			pchar.GenQuest.Enc2Pause = true;
			if (!CheckAttribute(pchar, "questTemp.Azzy.Immortal")) LAi_SetImmortal(pchar, false);
			for (i = 0; i<MAX_CHARACTERS; i++)
			{
				makeref(sld, characters[i]);
				if (sld.location == "FortOrange_ExitTown")
				{
					LAi_SetImmortal(sld, false);
					sld.lifeday = 0;
					ChangeCharacterAddress(sld, "none", "");
				}
			}
		break;

		case "NightTimeOutingLSC":
			LAi_LocationDisableOfficersGen("FortOrange_Mine", true);
			LAi_LocationDisableOfficersGen("OutRHouse", true);
			LAi_LocationDisableOfficersGen("FortOrange_town", true);

			fTemp = GetHour();
			if (fTemp > 0) fTemp = 24 - fTemp;
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_34"), "Reload_To_Location", 5, 3);
			EquipCharacterbyItem(pchar, "suit_1");
			SetLaunchFrameReloadLocationParam("OutRHouse", "goto", "goto4", "NightTimeOutingLSC_1");
			WaitDate("", 0, 0, 0, fTemp, 0);
			LaunchFrameForm();
		break;

		case "NightTimeOutingLSC_1":
			StartQuestMovie(true, true, true);
			locCameraFromToPos(11.96, 8.84, 7.20, false, 10.39, 2.12, -10.00);
			sld = CharacterFromID("TizerDenLSC");
			ChangeCharacterAddressGroup(sld, "OutRHouse", "item", "flower3");
			CreateLocationParticles("shipfire", "reload", "reload2_back", 0.0, 1.0, 1.0, "");
			CreateLocationParticles("shipfire", "reload", "reload2_back", 2.5, -1.0, -2.5, "");
			PlayStereoSound("fortfire");

			for (i = 0; i < 6; i++)
			{
				if (i < 2)
				{
					sld = GetCharacter(NPC_GeneratePhantomCharacter("urban_mush", HOLLAND, MAN, 0));
				}
				else
				{
					sld = GetCharacter(NPC_GeneratePhantomCharacter("milit_sold", HOLLAND, MAN, 0));
				}
				ChangeCharacterAddressGroup(sld, "OutRHouse", "goto",  "goto2");
				LAi_SetActorType(sld);
				if (i < 1) LAi_ActorRunToLocator(sld, "rld", "loc" + i, "NightTimeOutingLSC_2", -1);
				else LAi_ActorRunToLocator(sld, "rld", "loc" + i, "", -1);
			}
		break;

		case "NightTimeOutingLSC_2":
			locCameraFromToPos(11.96, 8.84, 7.20, false, 0.39, 2.12, 0.00);
			sld = CharacterFromID("TizerDenLSC");
			GiveItem2Character(sld, "blade34");
			EquipCharacterByItem(sld, "blade34");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "reload", "reload1_back", "NightTimeOutingLSC_3", 10);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1_back", "", 10);
		break;

		case "NightTimeOutingLSC_3":
			EndQuestMovie();
			LAi_LocationDisableOfficersGen("Orange_mines", true);
			//убираются жители рудников
			for (i = 0; i<MAX_CHARACTERS; i++)
			{
				makeref(npchar, characters[i]);
				if (npchar.location == "FortOrange_Mine")
				{
					npchar.lifeday = 0;
					ChangeCharacterAddress(npchar, "none", "");
				}
			}
			//закрываем переходы
			for (i = 1; i < 7; i++)
			{
				LocatorReloadEnterDisable("FortOrange_Mine", "reload"+i, true);
			}
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			DoQuestReloadToLocation("FortOrange_Mine", "reload", "reload6", "NightTimeOutingLSC_4");
		break;

		case "NightTimeOutingLSC_4":
			sld = CharacterFromID("TizerDenLSC");
			LAi_type_actor_Reset(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_Mine", "officers", "reload6_1");
			LAi_ActorRunToLocator(sld, "rld", "attack1", "NightTimeOutingLSC_5", 20);
		break;

		case "NightTimeOutingLSC_5":
			LocatorReloadEnterDisable("FortOrange_Mine", "reload4", false);
			sld = CharacterFromID("TizerDenLSC");
			LAi_ActorRunToLocation(sld, "reload", "reload4", "Orange_mines", "goto", "goto1", "", -1.0);
			pchar.quest.NightTimeOutingLSCFunc_1.win_condition.l1 = "location";
			pchar.quest.NightTimeOutingLSCFunc_1.win_condition.l1.location = "Orange_mines";
			pchar.quest.NightTimeOutingLSCFunc_1.function = "NightTimeOutingLSCFunc_1";
			sld = &locations[FindLocation("Orange_mines")];
			DeleteAttribute(sld, "models.always.DungeonOrange1_rocks");
			sld.models.day.charactersPatch = "DungeonOrange1_patch2";
			sld.models.night.charactersPatch = "DungeonOrange1_patch2";
			LAi_LocationFightDisable(sld, true);
		break;

		case "NightTimeOutingLSC_6":
			sld = CharacterFromID("TizerDenLSC");
			TEV.NightTimeOutingLSC.name = sld.name;
			TEV.NightTimeOutingLSC.lastname = sld.lastname;
			sld.name = sld.name + " " + XI_ConvertString("NationLegendText_4") + " " + FindPersonalName("Slave_name");
			sld.lastname = "";
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

		case "OutFromMineLSC_1":
			//рабы размещаются на своих местах
			for (i = 2; i < 12; i++)
			{
				sld = CharacterFromID("slavesLSC"+i);
				LAi_type_actor_Reset(sld);
				sld.dialog.filename = "Quest\LostShipsCity\TizerDen.c";
				sld.Dialog.CurrentNode = "NightTimeAlcholOutLSC_1";
				LAi_warrior_DialogEnable(sld, true);
				ChangeCharacterAddressGroup(sld, "Orange_mines", "quest",  "body" + (i - 1));
				LAi_SetActorTypeNoGroup(sld);
				if (i == 2 || i == 4 || i == 6)
					LAi_ActorSetSitPoorMode(sld);
				else if (i == 3 || i == 7 || i == 9)
					LAi_ActorSetLayMode(sld);
				else if (i == 5 || i == 8 || i == 10)
					LAi_ActorSetStayMode(sld);
				else
				{
					LAi_SetStayType(sld);
					sld.talker = 10;
				}
			}
		break;

		case "OutFromMineLSC_2":
			sld = CharacterFromID("Minetown_Commend");
			FantomMakeCoolFighter(sld, sti(pchar.rank), 75, 75, "blade26", "pistol3", 50);
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, false);
			sld.dialog.filename = "Quest\LostShipsCity\TizerDen.c";
			sld.dialog.CurrentNode = "Minetown_Commend";
			ChangeCharacterAddressGroup(sld, "Orange_mines", "quest", "mushketer2");
			for (i = 1; i < 3; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("milit_sold", HOLLAND, MAN, 1));
				npchar.id = "mineGuard"+i;
				ChangeCharacterAddressGroup(npchar, "Orange_mines", "quest", "mushketer2");
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, sld, "", -1);
			}
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 3.0, 0);
		break;

		case "OutFromMineLSC_3":
			LAi_LocationFightDisable(&Locations[FindLocation("Orange_mines")], false);
			LAi_group_Delete("EnemyFight");
			sld = CharacterFromID("Minetown_Commend");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for (i = 1; i < 3; i++)
			{
				sld = CharacterFromID("mineGuard"+i);
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
			sld = CharacterFromID("TizerDenLSC");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);        //стравливаем
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "OutFromMineLSC_4");
		break;

		case "OutFromMineLSC_4":
			LAi_LocationFightDisable(&Locations[FindLocation("Orange_mines")], true);
			LAi_SetActorType(pchar);
			sld = CharacterFromID("TizerDenLSC");
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(pchar, sld);
			sld.dialog.CurrentNode = "OutFromMineEndLSC_1";
			LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		break;

		case "OutFromMineLSC_5":
			sld = CharacterFromID("TizerDenLSC");
			GiveItem2Character(sld, "pistol3");
			EquipCharacterByItem(sld, "pistol3");
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(pchar, sld);
			sld.dialog.CurrentNode = "OutFromMineEndLSC_2";
			LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		break;

		case "OutFromMineLSC_6":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("TizerDenLSC");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "item", "berglar1", "", -1);
			AddLandQuestMark_Main(sld, "ISS_PoorsMurder");
		break;

		case "OutFromMineLSC_7":
			sld = CharacterFromID("slavesLSC11");
			LAi_ActorSetSitPoorMode(sld);
		break;

		case "OutFromMineLSC_8":
			sld = CharacterFromID("slavesLSC11");
			LAi_SetActorType(sld);
			LAi_SetSitPoorAnimation(sld);
			LAi_tmpl_ani_PlayAnimation(sld, "Ground_SitDown", -1);
			sld = CharacterFromID("TizerDenLSC");
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			LAi_ActorWaitDialog(pchar, sld);
			sld.dialog.CurrentNode = "NightTimeAlcholOutLSC_3";
			LAi_ActorDialog(sld, pchar, "", 4.0, 0);
		break;

		case "OutFromMineLSC_9":
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_23"), "OutFromMineLSC_10", 5, 3);
			ChangeCharacterAddressGroup(CharacterFromID("slavesLSC11"), "Orange_mines", "item", "berglar1");
			WaitDate("", 0, 0, 0, 4, 0);
			LaunchFrameForm();
			RecalculateJumpTable();
		break;

		case "OutFromMineLSC_10":
			sld = CharacterFromID("slavesLSC4");
			LAi_SetActorType(sld);
			LAi_SetSitPoorAnimation(sld);
			LAi_tmpl_ani_PlayAnimation(sld, "Ground_SitDown", -1);
			StartQuestMovie(true, true, true);
			LAi_SetActorType(pchar);
			locCameraFromToPos(-45.46, 4.55, 58.98, false, -75.50, -20.64, 100.00);
			sld = CharacterFromID("FortOrange_tavernkeeper");
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "Orange_mines", "reload", "reload2_back");
			LAi_ActorGoToLocator(sld, "quest", "body10", "OutFromMineLSC_11", -1);
		break;

		case "OutFromMineLSC_11":
			sld = CharacterFromID("slavesLSC10");
			LAi_SetActorType(sld);
			LAi_SetSitPoorAnimation(sld);
			LAi_tmpl_ani_PlayAnimation(sld, "Ground_SitDown", -1);
			sld = CharacterFromID("FortOrange_tavernkeeper");
			LAi_ActorTurnToCharacter(CharacterFromID("slavesLSC11"), sld);
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(pchar, sld);
			sld.dialog.CurrentNode = "OutFromMineLSC";
			LAi_ActorDialogNow(sld, pchar, "", 0);
		break;

		case "OutFromMineLSC_12":
			locCameraFromToPos(-45.46, 4.55, 58.98, false, -75.50, -20.64, 100.00);
			npchar = CharacterFromID("FortOrange_tavernkeeper");
			sld = CharacterFromID("TizerDenLSC");
			LAi_ActorTurnToCharacter(sld, npchar);
			LAi_tmpl_ani_PlayAnimation(sld, "Shot", -1.0);
			DoQuestFunctionDelay("NightTimeOutingLSCFunc_8", 1.2);
		break;

		case "OutFromMineLSC_13":
			for (i = 1; i < 20; i++)
			{
				sld = CharacterFromID("NightSlaveLSC"+i);
				if (!LAi_IsDead(sld))
					LAi_SetCitizenTypeNoGroup(sld);
			}
			sld = GetCharacter(NPC_GenerateCharacter("TitherDenLSC", "Tither", "man", "man", 27, PIRATE, -1, true));
			LAi_SetImmortal(sld, true);
			sld.dialog.filename = "Quest\LostShipsCity\TizerDen.c";
			sld.dialog.CurrentNode = "FortOrangeAhtung";
			sld.name = FindPersonalName("Tizer_name");
			sld.lastname = FindPersonalName("Tizer_lastname");
			sld.greeting = "Gr_slave";
			ChangeCharacterAddressGroup(sld, "FortOrange_town", "reload", "reload13");
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC":
			chrDisableReloadToLocation = true;
			fTemp = GetHour();
			if (fTemp > 19.0) fTemp = 24.0 - fTemp + 10.0;
			else if (fTemp < 9.0) fTemp = 10.0 - fTemp;
			WaitDate("", 0, 0, 0, fTemp, 0);
			DoReloadCharacterToLocation("FortOrange_ExitTown", "goto", "goto9");
			sld = CharacterFromID("TitherDenLSC");
			ChangeCharacterAddress(sld, "FortOrange_ExitTown", "goto17");
			LAi_ActorRunToLocator(pchar, "goto", "goto18", "TheStarsAlignedLSC_1", 6.0);
		break;

		case "TheStarsAlignedLSC_1":
			CreateLocationParticlesLoopedSound("shipfire", "reload", "reload3", 8.0, 9.0, -13.0, "fortfire");
			CreateLocationParticlesLoopedSound("shipfire", "reload", "reload3", 5.0, 18.0, 9.0, "fortfire");
			CreateLocationParticlesLoopedSound("shipfire", "reload", "reload3", 8.0, 3.0, -15.0, "fortfire");
			LAi_LocationDisableOfficersGen("FortOrange_ExitTown", false);
			sld = &locations[FindLocation("FortOrange_ExitTown")];
			sld.FortOrange_ExitTown_fireLSC = true;
			sld = CharacterFromID("TitherDenLSC");
			sld.dialog.CurrentNode = "TheStarsAligned";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC_2":
			for (i = 1; i < 4; i++)
			{
				iTemp = GetOfficersIndex(pchar, i);
				if (iTemp != -1) {
					sld = GetCharacter(iTemp);
					ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "reload", "reload2_back");
					LAi_warrior_DialogEnable(sld, false);
					LAi_tmpl_SetFollow(sld, pchar, -1.0);
					pchar.questTemp.LSC.StarsAlignedCompanion = sld.id;
				}
			}
			if (!CheckAttribute(pchar, "questTemp.LSC.StarsAlignedCompanion"))
			{
				arrayNPCModelHow = 0;
				for (i = 1; i < 3; i++)
				{
					sld = GetCharacter(NPC_GeneratePhantomCharacter("sailor", PIRATE, MAN, 1));
					SetNPCModelUniq(sld, "sailor", MAN);
					sld.id = "PcharSailorLSC"+i;
					ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "reload", "reload2_back");
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_tmpl_SetFollow(sld, pchar, -1.0);
					LAi_warrior_DialogEnable(sld, false);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
					pchar.questTemp.LSC.StarsAlignedCompanion = sld.id;
				}
			}
			LAi_SetImmortal(sld, true);
			LAi_warrior_DialogEnable(sld, true);
			sld.dialog.filename = "Quest\LostShipsCity\OtherNPC.c";
			sld.dialog.CurrentNode = "StarsAlignedCompanion";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "TheStarsAlignedLSC_3":
			//наши ребята за спину ГГ
			if (pchar.questTemp.LSC.StarsAlignedCompanion == "PcharSailorLSC2")
			{
				for (i = 1; i < 3; i++)
				{
					sld = CharacterFromID("PcharSailorLSC"+i);
					LAi_SetActorType(sld);
					if (i == 1) LAi_ActorGoToLocator(sld, "goto", "goto7", "", 5.0);
					if (i == 2) LAi_ActorGoToLocator(sld, "goto", "goto19", "", 5.0);
				}
			}
			else
			{
				for (i = 1; i < 4; i++)
				{
					iTemp = GetOfficersIndex(pchar, i);
					if (iTemp != -1) {
						sld = GetCharacter(iTemp);
						LAi_SetActorType(sld);
						if (i == 1) LAi_ActorGoToLocator(sld, "goto", "goto7", "", 5.0);
						if (i == 2) LAi_ActorGoToLocator(sld, "goto", "goto19", "", 5.0);
						if (i == 3) LAi_ActorGoToLocator(sld, "item", "item5", "", 5.0);
					}
				}
			}
			//выход Джона Коксона
			LAi_group_Delete("EnemyFight");
			sld = GetCharacter(NPC_GenerateCharacter("John_CoxonLSC", "John_Coxon", "man", "man", makeint(stf(pchar.rank) * 0.75), PIRATE, 1, false));
			sld.name = FindPersonalName("John_Coxon_name");
			sld.lastname = FindPersonalName("John_Coxon_lastname");
			sld.Dialog.Filename = "Mayor\JohnCoxon.c";
			sld.dialog.currentnode = "TheStarsAlignedLSC";
			sld.greeting = "";
			FantomMakeCoolFighter(sld, makeint(stf(pchar.rank) * 0.75), 90, 50, "blade15", "pistol6", 150);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "rld", "loc1");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			//мушкетеры
			for (i = 3; i < 7; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("pirate_mush", PIRATE, MAN, 1));
				npchar.id = "John_CoxonBoysLSC" + i;
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, sld, "", -1);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			//обычные пираты
			for (i = 7; i < 15; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("pirate", PIRATE, MAN, 1));
				npchar.id = "John_CoxonBoysLSC" + i;
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, sld, "", -1);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			//элита Коксона
			for (i = 1; i < 3; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("mercenary", PIRATE, MAN, 1));
				npchar.id = "John_CoxonBoysLSC" + i;
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, sld, "", -1);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			LAi_ActorRunToLocator(sld, "goto", "goto3", "TheStarsAlignedLSC_4", 6.5);
		break;

		case "TheStarsAlignedLSC_4":
			if (pchar.questTemp.LSC.StarsAlignedCompanion == "PcharSailorLSC2")
			{
				for (i = 1; i < 3; i++)
				{
					sld = CharacterFromID("PcharSailorLSC"+i);
					LAi_SetActorType(sld);
					LAi_ActorTurnToCharacter(sld, pchar);
				}
			}
			else
			{
				for (i = 1; i < 4; i++)
				{
					iTemp = GetOfficersIndex(pchar, i);
					if (iTemp != -1) {
						sld = GetCharacter(iTemp);
						LAi_ActorTurnToCharacter(sld, pchar);
					}
				}
			}
			for (i = 3; i < 15; i++)
			{
				sld = CharacterFromID("John_CoxonBoysLSC" + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorStay(sld);
				LAi_ActorTurnToCharacter(sld, pchar);
			}
			sld = CharacterFromID("John_CoxonLSC");
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "TheStarsAlignedLSC_5":
			for (i = 1; i < 15; i++)
			{
				sld = CharacterFromID("John_CoxonBoysLSC" + i);
				LAi_SetActorType(sld);
				LAi_SetStayType(sld);
			}
			sld = CharacterFromID("John_CoxonLSC");
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetCheckMinHP(sld, 1, true, "TheStarsAlignedLSC_6");
			LAi_SetWarriorTypeNoGroup(sld);

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			Lai_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);
		break;

		case "TheStarsAlignedLSC_6":
			for (i = 1; i < 15; i++)
			{
				sld = CharacterFromID("John_CoxonBoysLSC" + i);
				if (LAi_IsDead(sld)) continue;
				LAi_SetActorType(sld);
				LAi_ActorStay(sld);
			}
			sld = CharacterFromID("John_CoxonLSC");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			sld = CharacterFromID("TitherDenLSC");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			if (pchar.questTemp.LSC.StarsAlignedCompanion == "PcharSailorLSC2")
			{
				for (i = 1; i < 3; i++)
				{
					sld = CharacterFromID("PcharSailorLSC"+i);
					if (LAi_IsDead(sld)) continue;
					LAi_SetActorType(sld);
					LAi_ActorStay(sld);
				}
			}
			else
			{
				for (i = 1; i < 4; i++)
				{
					iTemp = GetOfficersIndex(pchar, i);
					if (iTemp != -1) {
						sld = GetCharacter(iTemp);
						if (LAi_IsDead(sld)) continue;
						LAi_SetActorType(sld);
						LAi_ActorStay(sld);
					}
				}
			}
			sld = CharacterFromID(pchar.questTemp.LSC.StarsAlignedCompanion);
			sld.dialog.currentnode = "StarsAlignedAhtung";
			LAi_SetActorType(pchar);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "TheStarsAlignedLSC_7":
			sld = CharacterFromID(pchar.questTemp.LSC.StarsAlignedCompanion);
			sld.dialog.currentnode = "StarsAlignedAhtung";
			LAi_SetActorType(pchar);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC_8":
			//реальных персов для сценок гонять не хочется, суем фейковых
			if (CheckAttribute(pchar, "questTemp.piratesLine") && pchar.questTemp.piratesLine == "over")
			{
				sld = GetCharacter(NPC_GenerateCharacter("JungleManLSC", "Edward_Colier", "man", "man", 30, PIRATE, 1, false));
				sld.name = FindPersonalName("Providencia_Mayor_name");
				sld.lastname = FindPersonalName("Providencia_Mayor_lastname");
				sld.greeting = "Gr_HeadPirates";
			}
			else
			{
				sld = GetCharacter(NPC_GenerateCharacter("JungleManLSC", "Morgan", "man", "man", 30, PIRATE, 1, false));
				sld.name = FindPersonalName("Henry_Morgan_name");
				sld.lastname = FindPersonalName("Henry_Morgan_lastname");
				sld.greeting = "Gr_Morgan";
			}
			sld.dialog.filename = "Quest\LostShipsCity\OtherNPC.c";
			sld.dialog.CurrentNode = "JungleManDialog";
			FantomMakeCoolFighter(sld, 30, 90, 50, "blade27", "pistol6", 150);
			LAi_SetLoginTime(sld, 0.0, 24.0);
			LAi_SetActorType(sld);
			ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "rld", "loc2");
			//мушкетеры
			for (i = 1; i < 7; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("elite_eng_mush", ENGLAND, MAN, 1));
				npchar.id = "JungleManBoysLSC" + i;
				FantomMakeCoolFighter(npchar, sti(npchar.rank), 80, 80, "unarmed", "mushket", 100);
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc2");
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, sld, "", -1);
			}
			//солдаты
			for (i = 7; i < 15; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("army_sold", ENGLAND, MAN, 1));
				npchar.id = "JungleManBoysLSC" + i;
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc2");
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, sld, "", -1);
			}
			LAi_ActorRunToLocator(sld, "goto", "goto5", "TheStarsAlignedLSC_9", 7.0);

		break;

		case "TheStarsAlignedLSC_9":
			for (i = 3; i < 15; i++)
			{
				sld = CharacterFromID("JungleManBoysLSC" + i);
				LAi_type_actor_Reset(sld);
				LAi_ActorStay(sld);
				LAi_ActorTurnToCharacter(sld, pchar);
			}
			sld = CharacterFromID("JungleManLSC");
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "TheStarsAlignedLSC_10":
			sld = CharacterFromID("John_CoxonLSC");
			npchar = CharacterFromID("JungleManLSC");
			LAi_ActorTurnToCharacter(npchar, sld);
			sld.name = npchar.name + " " + XI_ConvertString("NationLegendText_4") + " " + sld.name;
			sld.lastname = "";
			sld.dialog.CurrentNode = "JungleManAndCoxonDialog";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC_11":
			sld = CharacterFromID("John_CoxonLSC");
			sld.name = FindPersonalName("John_Coxon_name");
			sld.lastname = FindPersonalName("John_Coxon_lastname");
			sld = CharacterFromID("JungleManLSC");
			sld.dialog.CurrentNode = "JungleManDialog2";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC_12":
			sld = CharacterFromID("John_CoxonLSC");
			npchar = CharacterFromID("JungleManLSC");
			LAi_ActorTurnToCharacter(npchar, sld);
			sld.name = npchar.name + " " + XI_ConvertString("NationLegendText_4") + " " + sld.name;
			sld.lastname = "";
			sld.dialog.CurrentNode = "JungleManAndCoxonDialog2";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC_13":
			sld = CharacterFromID("John_CoxonLSC");
			sld.name = FindPersonalName("John_Coxon_name");
			sld.lastname = FindPersonalName("John_Coxon_lastname");
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = CharacterFromID("JungleManLSC");
			sld.dialog.CurrentNode = "JungleManDialog3";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC_14":
			sld = CharacterFromID("John_CoxonLSC");
			sld.dialog.CurrentNode = "JungleCoxonDialog";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC_15":
			sld = CharacterFromID("John_CoxonLSC");
			npchar = CharacterFromID("JungleManLSC");
			LAi_ActorTurnToCharacter(npchar, sld);
			npchar.dialog.CurrentNode = "JungleManDialog4";
			LAi_ActorWaitDialog(pchar, npchar);
			LAi_ActorDialog(npchar, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC_16":
			sld = CharacterFromID("TitherDenLSC");
			npchar = CharacterFromID("JungleManLSC");
			LAi_ActorTurnToCharacter(npchar, sld);
			sld.name = sld.name + " " + XI_ConvertString("NationLegendText_4") + " " + npchar.name;
			sld.lastname = "";
			sld.dialog.CurrentNode = "JungleManAndTitherDialog";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC_17":
			LAi_FadeEx(0.0, 2.0, 1.0, "TheStarsAlignedFuncLSC_1", "TheStarsAlignedFuncLSC_2", "");
		break;

		case "TheStarsAlignedLSC_18":
			locCameraTarget(pchar);
			locCameraFollow();
			sld = CharacterFromID("TitherDenLSC");
			sld.dialog.CurrentNode = "JungleDialog";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC_19":
			sld = CharacterFromID("JungleManLSC");
			ChangeCharacterAddress(sld, "none", "");
			for (i = 1; i < 15; i++)
			{
				if (i < 3 || i > 9)
				{
					sld = CharacterFromID("JungleManBoysLSC" + i);
					LAi_type_actor_Reset(sld);
					ChangeCharacterAddress(sld, "none", "");
				}
			}
			sld = CharacterFromID(pchar.questTemp.LSC.StarsAlignedCompanion);
			sld.dialog.CurrentNode = "StarsAlignedAhtung2";
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 7.0, 0);
		break;

		case "TheStarsAlignedLSC_20":
			locCameraFromToPos(21.02, 8.73, -7.73, false, -120.28, -30.69, 30.00);
			LAi_group_Delete("EnemyFight");

			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 3;
			else iTemp = 6;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				npchar.id = "MarmonLSC" + i;
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocator(npchar, "goto", "goto3", "TheStarsAlignedLSC_21", 7.0);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			for (i = 3; i < 10; i++)
			{
				sld = CharacterFromID("JungleManBoysLSC" + i);
				LAi_ActorTurnToCharacter(sld, npchar);
			}
			for (i = 1; i < 15; i++)
			{
				sld = CharacterFromID("John_CoxonBoysLSC" + i);
				if (LAi_IsDead(sld)) continue;
				LAi_ActorTurnToCharacter(sld, npchar);
			}
			if (pchar.questTemp.LSC.StarsAlignedCompanion == "PcharSailorLSC2")
			{
				for (i = 1; i < 3; i++)
				{
					sld = CharacterFromID("PcharSailorLSC"+i);
					if (LAi_IsDead(sld)) continue;
					LAi_ActorTurnToCharacter(sld, npchar);
				}
			}
			else
			{
				for (i = 1; i < 4; i++)
				{
					iTemp = GetOfficersIndex(pchar, i);
					if (iTemp != -1) {
						sld = GetCharacter(iTemp);
						if (LAi_IsDead(sld)) continue;
						LAi_ActorTurnToCharacter(sld, npchar);
					}
				}
			}
			sld = CharacterFromID("TitherDenLSC");
			LAi_ActorTurnToCharacter(sld, npchar);
			sld = CharacterFromID("John_CoxonLSC");
			LAi_ActorTurnToCharacter(sld, npchar);
			LAi_ActorTurnToCharacter(pchar, npchar);
		break;

		case "TheStarsAlignedLSC_21":
			SetBan("Looting,Exchange", 1);
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 3;
			else iTemp = 6;
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID("MarmonLSC" + i);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			TheStarsAlignedFightLSC();

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "TheStarsAlignedLSC_22");
			PlaySound("Voice\" + VoiceGetLanguage() + "\EvilPirates01.wav");
		break;

		case "TheStarsAlignedLSC_22":
			TheStarsAlignedReturnLSC("TheStarsAlignedLSC_23");
		break;

		case "TheStarsAlignedLSC_23":
			sld = CharacterFromID("John_CoxonLSC");
			sld.dialog.CurrentNode = "FirstWaves";
			LAi_type_actor_Reset(sld);
			if (sti(InterfaceStates.Launched) > 0)
			{
				LAi_Actor2WaitDialog(sld, pchar);
			}
			else
			{
				LAi_ActorWaitDialog(pchar, sld);
				LAi_ActorDialog(sld, pchar, "", 7.0, 0);
			}
		break;

		case "TheStarsAlignedLSC_24":
			locCameraFromToPos(21.02, 8.73, -7.73, false, -120.28, -30.69, 30.00);
			LAi_group_Delete("EnemyFight");

			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 4;
			else iTemp = 6;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				npchar.id = "MarmonLoc1LSC" + i;
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocator(npchar, "goto", "goto3", "TheStarsAlignedLSC_25", 7.0);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				npchar.id = "MarmonLoc2LSC" + i;
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc2");
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocator(npchar, "goto", "goto6", "", 7.0);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 0;
			else iTemp = 1;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados_mush", PIRATE, MAN, 0));
				npchar.id = "MarmonMushLoc1LSC" + i;
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocator(npchar, "goto", "goto3", "", 7.0);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados_mush", PIRATE, MAN, 0));
				npchar.id = "MarmonMushLoc2LSC" + i;
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc2");
				LAi_SetActorType(npchar);
				LAi_ActorRunToLocator(npchar, "goto", "goto6", "", 7.0);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			for (i = 3; i < 10; i++)
			{
				sld = CharacterFromID("JungleManBoysLSC" + i);
				if (LAi_IsDead(sld)) continue;
				LAi_type_actor_Reset(sld);
				LAi_ActorTurnToLocator(sld, "goto", "goto6");
			}
			for (i = 1; i < 15; i++)
			{
				sld = CharacterFromID("John_CoxonBoysLSC" + i);
				if (LAi_IsDead(sld)) continue;
				LAi_type_actor_Reset(sld);
				LAi_ActorTurnToLocator(sld, "goto", "goto6");
			}
		break;

		case "TheStarsAlignedLSC_25":
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 4;
			else iTemp = 6;
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID("MarmonLoc1LSC" + i);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID("MarmonLoc2LSC" + i);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 0;
			else iTemp = 1;
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID("MarmonMushLoc1LSC" + i);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			for (i = 0; i < iTemp; i++)
			{
				sld = CharacterFromID("MarmonMushLoc2LSC" + i);
				LAi_SetWarriorTypeNoGroup(sld);
			}
			TheStarsAlignedFightLSC();

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "TheStarsAlignedLSC_26");
			PlaySound("Voice\" + VoiceGetLanguage() + "\EvilPirates01.wav");
		break;

		case "TheStarsAlignedLSC_26":
			TheStarsAlignedReturnLSC("TheStarsAlignedLSC_27");
		break;

		case "TheStarsAlignedLSC_27":
			sld = CharacterFromID("John_CoxonLSC");
			sld.dialog.CurrentNode = "SecondWaves";
			LAi_type_actor_Reset(sld);
			if (sti(InterfaceStates.Launched) > 0)
			{
				LAi_Actor2WaitDialog(sld, pchar);
			}
			else
			{
				LAi_ActorWaitDialog(pchar, sld);
				LAi_ActorDialog(sld, pchar, "", 7.0, 0);
			}
		break;

		case "TheStarsAlignedLSC_28":
			sld = CharacterFromID("John_CoxonLSC");
			LAi_type_actor_Reset(sld);
			LAi_ActorRunToLocator(sld, "reload", "reload3", "TheStarsAlignedLSC_29", -1);
		break;

		case "TheStarsAlignedLSC_29":
			sld = CharacterFromID("John_CoxonLSC");
			ChangeCharacterAddress(sld, "none", "");
			DoQuestCheckDelay("TheStarsAlignedLSC_30", 5.0);
		break;

		case "TheStarsAlignedLSC_30":
			LAi_group_Delete("EnemyFight");

			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 4;
			else iTemp = 6;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc2");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 1;
			else iTemp = 2;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados_mush", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc2");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			TheStarsAlignedFightLSC();

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DoQuestCheckDelay("TheStarsAlignedLSC_31", 10.0);
		break;

		case "TheStarsAlignedLSC_31":
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 4;
			else iTemp = 6;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 1;
			else iTemp = 2;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados_mush", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			LAi_group_SetCheck("EnemyFight", "TheStarsAlignedLSC_32");
		break;

		case "TheStarsAlignedLSC_32":
			TheStarsAlignedReturnLSC("TheStarsAlignedLSC_33");
		break;

		case "TheStarsAlignedLSC_33":
			sld = CharacterFromID("TitherDenLSC");
			sld.dialog.CurrentNode = "ThirdWaves";
			LAi_type_actor_Reset(sld);
			if (sti(InterfaceStates.Launched) > 0)
			{
				LAi_Actor2WaitDialog(sld, pchar);
			}
			else
			{
				LAi_ActorWaitDialog(pchar, sld);
				LAi_ActorDialog(sld, pchar, "", 7.0, 0);
			}
		break;

		case "TheStarsAlignedLSC_34":
			LAi_group_Delete("EnemyFight");

			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 5;
			else iTemp = 10;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc2");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			TheStarsAlignedFightLSC();

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DoQuestCheckDelay("TheStarsAlignedLSC_35", 10.0);
		break;

		case "TheStarsAlignedLSC_35":
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 2;
			else iTemp = 4;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "goto", "goto9");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 1;
			else iTemp = 2;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados_mush", PIRATE, MAN, 0));
				if (i == 0)
					ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "goto", "goto9");
//					ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "quest", "sniper1");
				if (i == 1)
					ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "goto", "goto9");
//					ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "quest", "sniper3");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			LAi_group_SetCheck("EnemyFight", "TheStarsAlignedLSC_36");
		break;

		case "TheStarsAlignedLSC_36":
			TheStarsAlignedReturnLSC("TheStarsAlignedLSC_37");
		break;

		case "TheStarsAlignedLSC_37":
			sld = CharacterFromID("John_CoxonLSC");
			sld.dialog.CurrentNode = "CoxonReturn";
			ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "officers", "reload3_1");
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 5;
			else iTemp = 0;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("slaves", PIRATE, MAN, 1));
				npchar.id = "John_CoxonSlaves" + i;
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "reload", "reload3");
				LAi_SetActorType(npchar);
				LAi_ActorFollow(npchar, sld, "", -1);
			}
			LAi_type_actor_Reset(sld);
			if (sti(InterfaceStates.Launched) > 0)
			{
				LAi_Actor2WaitDialog(sld, pchar);
			}
			else
			{
				LAi_ActorWaitDialog(pchar, sld);
				LAi_ActorDialog(sld, pchar, "", 7.0, 0);
			}
		break;

		case "TheStarsAlignedLSC_38":
			LAi_group_Delete("EnemyFight");

			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 10;
			else iTemp = 15;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc2");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			TheStarsAlignedFightLSC();

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DoQuestCheckDelay("TheStarsAlignedLSC_39", 40.0);
		break;

		case "TheStarsAlignedLSC_39":
			for (i = 0; i < 6; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "goto", "goto9");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			DoQuestCheckDelay("TheStarsAlignedLSC_40", 10.0);
		break;

		case "TheStarsAlignedLSC_40":
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 2;
			else iTemp = 4;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados_mush", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "goto", "goto9");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			DoQuestCheckDelay("TheStarsAlignedLSC_41", 10.0);
		break;

		case "TheStarsAlignedLSC_41":
			sld = CharacterFromID("JungleManLSC");
			ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "reload", "reload3");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, true);
			for (i = 1; i < 15; i++)
			{
				if (i < 3 || i > 9)
				{
					sld = CharacterFromID("JungleManBoysLSC" + i);
					ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "reload", "reload3");
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			for (i = 0; i < 5; i++)
			{
				sld = GetCharacter(NPC_GeneratePhantomCharacter("slaves", PIRATE, MAN, 1));
				sld.id = "JungleManSlavesLSC" + i;
				ChangeCharacterAddressGroup(sld, "FortOrange_ExitTown", "reload", "reload3");
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_group_SetCheck("EnemyFight", "TheStarsAlignedLSC_42");
		break;

		case "TheStarsAlignedLSC_42":
			TheStarsAlignedReturnLSC("TheStarsAlignedLSC_43");
		break;

		case "TheStarsAlignedLSC_43":
			sld = CharacterFromID("JungleManLSC");
			sld.dialog.CurrentNode = "ReturnJungleMan";
			LAi_SetActorType(sld);
			LAi_type_actor_Reset(pchar);
			if (sti(InterfaceStates.Launched) > 0)
			{
				LAi_Actor2WaitDialog(sld, pchar);
			}
			else
			{
				LAi_ActorWaitDialog(pchar, sld);
				LAi_ActorDialog(sld, pchar, "", 7.0, 0);
			}
		break;

		case "TheStarsAlignedLSC_44":
			LAi_group_Delete("EnemyFight");

			for (i = 0; i < 10; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			for (i = 0; i < 10; i++)
			{
				if (i == 0)
				{
					npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados_mush", PIRATE, MAN, 0));
					FantomMakeCoolFighter(npchar, sti(npchar.rank), 80, 80, "unarmed", "mortar", 100);
				}
				else
				{
					npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				}
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc2");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			TheStarsAlignedFightLSC();

			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			DoQuestCheckDelay("TheStarsAlignedLSC_45", 5.0);

			//открываем пути для побега
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("FortOrange_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("FortOrange_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("FortOrange_ExitTown", "reload3", true);
			pchar.GenQuest.Enc2Pause = true;
			for (i = 0; i<MAX_CHARACTERS; i++)
			{
				makeref(sld, characters[i]);
				if (sld.location == "Shore35")
				{
					LAi_SetImmortal(sld, false);
					sld.lifeday = 0;
					ChangeCharacterAddress(sld, "none", "");
				}
			}
			pchar.quest.EnterToFortOrangeTownLSC.win_condition.l1 = "location";
			pchar.quest.EnterToFortOrangeTownLSC.win_condition.l1.location = "Shore35";
			pchar.quest.EnterToFortOrangeTownLSC.function = "BattleInShoreLSC";
		break;

		case "TheStarsAlignedLSC_45":
			for (i = 1; i < 7; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados_mush", PIRATE, MAN, 0));
//					ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "quest", "sniper" + i);
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "goto", "goto9");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			DoQuestCheckDelay("TheStarsAlignedLSC_46", 10.0);
		break;

		case "TheStarsAlignedLSC_46":
			if (pchar.location != "FortOrange_ExitTown") return;
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 2;
			else iTemp = 3;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc1");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			if (pchar.questTemp.LSC == "MayorFiledLSC") iTemp = 2;
			else iTemp = 4;
			for (i = 0; i < iTemp; i++)
			{
				npchar = GetCharacter(NPC_GeneratePhantomCharacter("rivados", PIRATE, MAN, 0));
				ChangeCharacterAddressGroup(npchar, "FortOrange_ExitTown", "rld", "loc2");
				LAi_SetWarriorTypeNoGroup(npchar);
				LAi_group_MoveCharacter(npchar, "EnemyFight");
			}
			DoQuestCheckDelay("TheStarsAlignedLSC_46", 10.0);
		break;

		case "TheStarsAlignedLSC_47":
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("FortOrange_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("FortOrange_ExitTown", "reload3", false);
			sld = CharacterFromID("JungleManLSC");
			LAi_SetActorType(sld);
			sld.dialog.CurrentNode = "GoodByeOrangeBeach";
			LAi_SetActorType(pchar);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialog(sld, pchar, "", 15.0, 0);
		break;

		case "TheStarsAlignedLSC_48":
			SetBan("Looting,Exchange", 0);
			LAi_FadeEx(0.0, 2.0, 1.8, "AfterStarsAlignedFuncLSC_1", "AfterStarsAlignedFuncLSC_2", "AfterStarsAlignedFuncLSC_3");
		break;

		case "SecretFort_TizerJournal":
			sld = &locations[FindLocation("Secret_Fort_Tizer_House")];
			LAi_LocationDisableOfficersGen(sld.id, true);
			sld.secret1.items.TizerJournal = 1;
			sld.secret1.difficult = 1;
			sld.secret1.visitedTime = 1;
			pchar.quest.SecretFort_TizerJournal_Find_1.win_condition.l1 = "location";
			pchar.quest.SecretFort_TizerJournal_Find_1.win_condition.l1.location = "Secret_Fort_Tizer_House";
			pchar.quest.SecretFort_TizerJournal_Find_1.win_condition = "SecretFort_TizerJournal_LockTheDoors";
		break;

		case "SecretFort_TizerJournal_LockTheDoors":
			LogSound_WithNotify(StringFromKey("InfoMessages_247"), "Notebook_1", "SneakFail");
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			pchar.quest.SecretFort_TizerJournal_Find_2.win_condition.l1 = "item";
			pchar.quest.SecretFort_TizerJournal_Find_2.win_condition.l1.item = "TizerJournal";
			pchar.quest.SecretFort_TizerJournal_Find_2.win_condition = "SecretFort_TizerJournal_Found";
		break;

		case "SecretFort_TizerJournal_Found":
			LogSound_WithNotify(StringFromKey("InfoMessages_240", GetItemName("TizerJournal"), 1), "Important_item", "Icollection");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			sld = CharacterFromId("Secret_Fort_Commander");
			sld.dialog.currentnode = "Commander_2_talk_1";
			AddQuestRecord("ISS_PoorsMurder", "36");
		break;

		case "SecretFort_TizerHouse_1":
			pchar.quest.Secret_Fort_Tizer_House_1.win_condition.l1 = "location";
			pchar.quest.Secret_Fort_Tizer_House_1.win_condition.l1.location = "Secret_Fort_Tizer_House";
			pchar.quest.Secret_Fort_Tizer_House_1.win_condition = "SecretFort_TizerHouse_Sleep";
		break;

		case "SecretFort_TizerHouse_Sleep":
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestFunctionDelay("ISS_PoorsMurder_SecretFort_TizerHouse_Sleep", 2.5);
		break;

		case "PutToLSC":
			CloseQuestHeader("PreparationForISS");
			pchar.questTemp.LSC.drownedman = 1;
			int iLostShips = FindIsland("LostShipsCity");
			Islands[iLostShips].reload_enable = false;
			StartQuestMovie(false, false, true);
			//если бессмертны то не разыгрываем кораблекрушение, а сразу портуем в ГПК
			if (LAi_IsImmortal(pchar))
			{
				DoQuestFunctionDelay("ReloadToLSC", 5.0);
			}
			else
			{
				DoQuestFunctionDelay("DamageShipLSC_Start", 9.0);
				DoQuestFunctionDelay("DamageShipLSC_End", 25.0);
			}
		break;

		case "LSC_AfterFirstReload_StartDialog":
            sld = &Characters[GetCharacterIndex("JorgeStouks")];
            LAi_SetActorType(sld);
            LAi_ActorWaitDialog(pchar, sld);

            LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "LSC_NarvalAssault":
			LSCNarvalAssault("");
		break;

		case "LSC_NarvalDestroyedGotoVelasco": // телепорт внутрь Веласко
			DoQuestReloadToLocation("VelascoShipInside1", "reload", "reload1", "pchar_back_to_player");
		break;

		case "LSC_NavalExitVelasco":
		//Уоркман уходит на своих двух
			sld = CharacterFromId("Ment_6");
			LAi_ActorGoToLocator(sld, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "LSC_MentRefresh", -1);
			//мушкетеры ментов возвращаются на место
			for (i = 7; i < 9; i++)
			{
				iTemp = GetCharacterIndex("MentMush_" + i);
				if (iTemp != -1)
				{
					ChangeCharacterAddressGroup(&characters[iTemp], "LostShipsCity_town", "soldiers", "mushketer" + i);
					characters[iTemp].Dialog.CurrentNode = "Ment_soldier";
					LAi_SetGuardianTypeNoGroup(&characters[iTemp]);
				}
			}
			//распространим слухи
			sld = CharacterFromId("LSCBarmen");
			sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_50"), "LostShipsCity", 10, 1, "LSC", "");
			sld.myselfRumour = sld.myselfRumour + "," + AddSimpleRumourCityTip(StringFromKey("Common_rumours_51"), "LostShipsCity", 10, 1, "LSC", "");
			sld.myselfRumour = sld.myselfRumour + "," + AddSimpleRumourCityTip(StringFromKey("Common_rumours_52"), "LostShipsCity", 10, 1, "LSC", "");
			sld.myselfRumour = sld.myselfRumour + "," + AddSimpleRumourCityTip(StringFromKey("Common_rumours_53"), "LostShipsCity", 10, 1, "LSC", "");
			sld.myselfRumour = sld.myselfRumour + "," + AddSimpleRumourCityTip(StringFromKey("Common_rumours_54"), "LostShipsCity", 10, 1, "LSC", "");
			sld.myselfRumour = sld.myselfRumour + "," + AddSimpleRumourCityTip(StringFromKey("Common_rumours_55"), "LostShipsCity", 10, 1, "LSC", "");
			sld.myselfRumour = sld.myselfRumour + "," + AddSimpleRumourCityTip(StringFromKey("Common_rumours_56"), "LostShipsCity", 10, 1, "LSC", "");
			sld.myselfRumour = sld.myselfRumour + "," + AddSimpleRumourCityTip(StringFromKey("Common_rumours_57"), "LostShipsCity", 10, 1, "LSC", "");
			sld.myselfRumour = sld.myselfRumour + "," + AddSimpleRumourCityTip(StringFromKey("Common_rumours_58"), "LostShipsCity", 10, 1, "LSC", "");
			sld.myselfRumour = sld.myselfRumour + "," + AddSimpleRumourCityTip(StringFromKey("Common_rumours_59"), "LostShipsCity", 10, 1, "LSC", "");
		break;

		case "LSC_MentRefresh": // стабилизация ментов после убийства нарвалов
			for (i = 1; i <= 3; i++)
			{
				iTemp = GetCharacterIndex("Ment_" + i);
				if (iTemp != -1)
				{
					sld = &characters[iTemp];
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
					sld.Dialog.CurrentNode = "First time";
					sld.cityTape = "ment"; //тип нпс
					LAi_SetLSCoutTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
				}
			}
			sld = CharacterFromId("Ment_6");
			LAi_SetRolyPoly(sld, false);
			ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sld.location.baseLocator);
			sld.Dialog.CurrentNode = "First time";
			sld.cityTape = "ment"; //тип нпс
			LAi_SetLSCoutTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
			DisableFastTravel(false); //разрешаем быстрое перемещение
			chrDisableReloadToLocation = false;
		break;

		case "NarvalDestroyed":
			pchar.questTemp.LSC = "NarvalDestroyed";
			pchar.questTemp.LSC.NarvalDestroyed = true;
			AddQuestRecord("ISS_MainLine", "14");
			AddLandQuestMark_Main(CharacterFromID("LSCMayor"), "ISS_MainLine");
			for (i = 1; i <= 3; i++)
			{
				iTemp = GetCharacterIndex("Ment_" + i);
				if (iTemp != -1)
				{
					LAi_SetWarriorType(&characters[iTemp]);
					LAi_group_MoveCharacter(&characters[iTemp], LAI_GROUP_PLAYER_OWN);
				}
			}
			DeleteShellBoat("LostShipsCity_town");
			DoQuestCheckDelay("MentTalkAbout", 5.5);
		break;

		case "MentTalkAbout":
			sld = characterFromId("Ment_6");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

		case "LSC_EnterComplite_1":
			sld = characterFromId("LSCMayor");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "stay1");
			LAi_SetStayType(sld);
			sld = characterFromId("Casper_head");
			if (sld.chr_ai.type == LAI_TYPE_STAY)
			{
				StartQuestMovie(true, true, true);
				SetMainCharacterIndex(GetCharacterIndex("Casper_head"));
				PChar = GetMainCharacter();
				locCameraToPos(77.3, 8.65, -30.9, false);
				LAi_SetActorType(PChar);
				LAi_ActorDialog(PChar, characterFromID("LSCMayor"), "", 0, 0);
			}
		break;

		case "LSC_EnterComplite_2":
			sld = characterFromId("Casper_head");
			LAi_SetActorType(sld);
			LAi_ActorTurnByLocator(sld, "quest", "stay2");
			LAi_SetStayType(sld);
			sld = characterFromId("LSCMayor");
			if (sld.chr_ai.type == LAI_TYPE_STAY)
			{
				StartQuestMovie(true, true, true);
				SetMainCharacterIndex(GetCharacterIndex("Casper_head"));
				PChar = GetMainCharacter();
				locCameraToPos(77.3, 8.65, -30.9, false);
				LAi_SetActorType(PChar);
				LAi_ActorDialog(PChar, characterFromID("LSCMayor"), "", 0, 0);
			}
		break;

		case "LSC_SesilAfraid":
			sld = characterFromID("SesilGalard");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorAfraid(sld, pchar, false);
		break;

		case "LSC_SesilAfterFight":
			chrDisableReloadToLocation = false;
			iTemp = GetCharacterIndex("SesilGalard");
			if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
			{
				sld = &characters[iTemp];
				while (FindCharacterItemByGroup(sld, BLADE_ITEM_TYPE) != "")
				{
					TakeItemFromCharacter(sld, FindCharacterItemByGroup(sld, BLADE_ITEM_TYPE));
				}
				sld.dialog.currentnode = "First time";
				sld.greeting = "Enc_RapersGirl_2";
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, "TmpEnemy");
				LAi_ActorWaitDialog(sld, pchar);
				AddQuestRecord("ISS_MainLine", "29");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ёл", "ла"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("", "а"));
				pchar.questTemp.LSC = "toKnowAboutMechanic";
				sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_90"), "LostShipsCity", 10, 1, "LSC", "");
				sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_128"), "LostShipsCity", 10, 1, "LSC", "");
				sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_129"), "LostShipsCity", 10, 1, "LSC", "");
				sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_130"), "LostShipsCity", 10, 1, "LSC", "");
				sld.myselfRumour = AddSimpleRumourCityTip(StringFromKey("Common_rumours_131"), "LostShipsCity", 10, 1, "LSC", "");

			    AddLandQuestMark_Main(CharacterFromID("SesilGalard"), "ISS_MainLine");
			}
			else
			{
				AddQuestRecord("ISS_MainLine", "30");
				AddQuestUserData("ISS_MainLine", "sSex", GetSexPhrase("ёл", "ла"));
				AddQuestUserData("ISS_MainLine", "sSex1", GetSexPhrase("", "а"));
				pchar.questTemp.LSC = "SessilIsDead";
				AddSimpleRumourCityTip(StringFromKey("Common_rumours_132"), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(StringFromKey("Common_rumours_133"), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(StringFromKey("Common_rumours_134"), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(StringFromKey("Common_rumours_135"), "LostShipsCity", 10, 1, "LSC", "");
				AddSimpleRumourCityTip(StringFromKey("Common_rumours_136"), "LostShipsCity", 10, 1, "LSC", "");

				AddLandQuestMark_Main(CharacterFromID("OreliBertin"), "ISS_MainLine");
			}
		break;

		case "LSC_casperIsGone":
			sld = &characters[sti(pchar.questTemp.LSC.Armo.casperIdx)];
			LAi_ActorTurnByLocator(sld, "quest", "target");
			sld.checkChrDistance = 5; //проверять дистанцию до характерса
			sld.checkChrDistance.id = "Blaze"; //Id характерса
			sld.checkChrDistance.time = 0; //время повторной проверки
			sld.checkChrDistance.node = sld.id; //нода диалога
		break;

		case "LSC_PedroOpenedDoor":
			sld = characterFromId("PedroHurtado");
			LAi_ActorTurnToLocator(sld, "goto", "goto04_5");
			LAi_ActorAnimation(sld, "Barman_idle", "LSC_EndOpenDoor", 1.5);
			DoQuestFunctionDelay("LSC_Click", 1.0);
		break;

		case "LSC_EndOpenDoor":
			sld = characterFromId("PedroHurtado");
			sld.dialog.currentNode = "StStart_Opened";
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;

		// --> тайна Санта-Люсии
		case "LSC_DeployShellBoat": // скорлупка
			DeployShipToReload("LostShipsCity_town", "locators.reload.reload_ring");
		break;

		case "LSC_RingTalkAfterDeployShellBoat": //разговор после образования скорлупки
			LSC_RingMalcolmTalk("ring_11");
		break;

		case "LSC_RingTalkLook": // смотрим на кольцо
			LAi_SetPlayerType(pchar);
			LSC_RingMalcolmTalk("ring_13");
		break;

		case "LSC_RingEnterInside": // входим в трюм разбитого корабля
			chrDisableReloadToLocation = true;//закрыть локацию
			LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
			// ставим крабикусов
			iRank = 20 + MOD_SKILL_ENEMY_RATE;
			iTemp = 150 + MOD_SKILL_ENEMY_RATE * 10 + sti(pchar.rank) * 10;
			LAi_group_Register("EnemyCrab");
			for (i = 1; i <= 10; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("CrabInside_" + i, "crabBig", "crab", "crabBig", iRank, PIRATE, -1, false));
				sld.monster = "1";
				sld.name = FindPersonalName("CrabInside_name");
				sld.lastname = "";
				GiveItem2Character(sld, "unarmed");
				EquipCharacterbyItem(sld, "unarmed");
				if (MOD_SKILL_ENEMY_RATE > 5) sld.MultiFighter = MOD_SKILL_ENEMY_RATE / 2.5;
				sld.SaveItemsForDead = true;
				sld.animal = true;
				LAi_SetHP(sld, iTemp, iTemp);
				SetCharacterPerk(sld, "BasicDefense");
				SetCharacterPerk(sld, "AdvancedDefense");
				SetCharacterPerk(sld, "CriticalHit");
				LAi_SetWarriorType(sld);
				//if (bPincers()) TakeNItems(sld, "crab_pincers", 2); // клешни
				ChangeCharacterAddressGroup(sld, "ExternalRingInside", "goto", "goto" + i);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyCrab");
			}
			LAi_group_SetRelation("EnemyCrab", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("EnemyCrab", 13.0);
			LAi_group_SetHearRadius("EnemyCrab", 5.0);
			LAi_group_SetSayRadius("EnemyCrab", 8.0);
			LAi_group_SetCheck("EnemyCrab", "LSC_RingInsideCrabsDead");
			LAi_SetFightMode(pchar, true);
		break;

		case "LSC_RingInsideCrabsDead": // перебили крабов
			KZ|Random("Special\LSC");
			LAi_group_Delete("EnemyCrab");
			sld = characterFromId("MalcolmFawn");
			ChangeCharacterAddressGroup(sld, "ExternalRingInside", "reload", "reload1");
			LSC_RingMalcolmTalk("ring_15");
			AddComplexSelfExpToScill(150, 150, 150, 150);
		break;

		case "LSC_RingDialog": // активатор диалогов
			sld = characterFromId("MalcolmFawn");
			LSC_RingMalcolmTalk(sld.quest.diagnode);
		break;

		case "LSC_RingEnterDeck": // входим на палубу разбитого корабля
			chrDisableReloadToLocation = true;//закрыть локацию
			// ставим крабикусов
			iRank = 20 + MOD_SKILL_ENEMY_RATE;
			iTemp = 100 + MOD_SKILL_ENEMY_RATE * 20 + sti(pchar.rank) * 5;
			for (i = 2; i <= 7; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("CrabDeck_" + i, "crabBig", "crab", "crabBig", iRank, PIRATE, -1, false));
				sld.monster = "1";
				sld.name = FindPersonalName("CrabInside_name");
				sld.lastname = "";
				GiveItem2Character(sld, "unarmed");
				EquipCharacterbyItem(sld, "unarmed");
				if (MOD_SKILL_ENEMY_RATE > 5) sld.MultiFighter = MOD_SKILL_ENEMY_RATE / 2.5;
				sld.SaveItemsForDead = true;
				sld.animal = true;
				LAi_SetHP(sld, iTemp, iTemp);
				SetCharacterPerk(sld, "BasicDefense");
				SetCharacterPerk(sld, "AdvancedDefense");
				SetCharacterPerk(sld, "CriticalHit");
				ChangeCharacterAddressGroup(sld, "ExternalRingDeck", "goto", "goto" + i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
				LAi_warrior_DialogEnable(sld, false);
				LAi_group_MoveCharacter(sld, "EnemyCrab");
			}
			LAi_group_SetRelation("EnemyCrab", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetLookRadius("EnemyCrab", 15.0);
			LAi_group_SetHearRadius("EnemyCrab", 6.0);
			LAi_group_SetSayRadius("EnemyCrab", 12.0);
			LAi_group_SetCheck("EnemyCrab", "LSC_RingDeckCrabsDead");
			LSC_RingMalcolmTalk("ring_22");
		break;

		case "LSC_RingDeckCrabsDead": // перебили крабов
			KZ|Random("Special\LSC");
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("ExternalRingDeck", "reload2", true);
			LAi_group_Delete("EnemyCrab");
			LSC_RingMalcolmTalk("ring_24");
			AddComplexSelfExpToScill(150, 150, 150, 150);
		break;

		case "LSC_RingEnterCabin": // вошли в каюту
			chrDisableReloadToLocation = true;
			sld = characterFromId("MalcolmFawn");
			sld.quest.diagnode = "ring_31";
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto1", "LSC_RingDialog", -1);
		break;

		case "LSC_RingSetToBarman": //
			sld = characterFromId("MalcolmFawn");
			LAi_SetBarmanType(sld);
		break;

		case "LSC_RingFinalStage": //
			sld = characterFromId("MalcolmFawn");
			sld.quest.ring_final = true;
			LAi_SetActorType(sld);
			LAi_SetImmortal(sld, false);
			LAi_ActorRunToLocator(sld, "reload", "reload1", "", 6.0);
			DoQuestFunctionDelay("LSC_RingOver", 6.0); // закрываем квест
			SetFunctionTimerCondition("LSC_RingDeleteItemsBoxes", 0, 0, 2, false); // через 2 дня боксы опустеют
		break;

		case "LSC_RingFindGold": // нашли золото
			PlaySound("Ambient\LAND\door_001.wav");
			PlaySound("Ambient\LAND\door_004.wav");
			PlaySound("Types\" + VoiceGetLanguage() + "\warrior03.wav");
			PlaySound("Types\" + VoiceGetLanguage() + "\warrior04.wav");
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_58", NewStr()), "", 0, 4);//табличка
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 2, 10); //крутим время
			RecalculateJumpTable();
			sld = characterFromId("MalcolmFawn");
			sld.quest.diagnode = "ring_46";
			DoQuestCheckDelay("LSC_RingDialog", 6.0);
		break;

		case "LSC_RingGoToBack":
			sld = characterFromId("MalcolmFawn");
			LAi_SetStayType(sld);
			DoQuestReloadToLocation("LostShipsCity_town", "quest", "ring", "");
			LAi_RemoveLoginTime(sld);
			ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload_ring");
		break;
		// <-- тайна Санта-Люсии

		// --> пей до дна
		case "LSC_DrinkPedroTalk": // Педро подходит раз
			chrDisableReloadToLocation = true; //закрыть локацию
			sld = characterFromId("PedroHurtado");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			if (pchar.questTemp.LSC.Drink == "grabbing") DoQuestCheckDelay("LSC_DrinkPedroTeleport", 0.1);

		break;

		case "LSC_DrinkPedroTeleport": // Педро подходит два
			sld = characterFromId("PedroHurtado");
			ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "reload", "reload69");
		break;

		case "LSC_DrinkGotoVelasco": // выводим на улицы
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload38", "LSC_DrinkGotoVelasco_1");
		break;

		case "LSC_DrinkGotoVelasco_1": // идем к 'Веласко'
			sld = characterFromId("PedroHurtado");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocator(sld, "goto", "goto16_4", "LSC_DrinkGotoVelasco_2", -1);
			LAi_SetImmortal(sld, true);
			pchar.quest.LSC_Drink1.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink1.win_condition.l1.date.hour = sti(GetTime() + 1);
			pchar.quest.LSC_Drink1.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink1.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink1.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink1.function = "LSC_DrinkDelete";
		break;

		case "LSC_DrinkGotoVelasco_2": // стоит, ждет
			sld = characterFromId("PedroHurtado");
			LAi_SetStayType(sld);
		break;

		case "LSC_DrinkGotoVelasco_3": // телепорт внутрь Веласко
			DoQuestReloadToLocation("VelascoBank", "reload", "reload2", "pchar_back_to_player");

			sld = ItemsFromID("key_drink");
			sld.shown = true;
			sld.startLocation = "VelascoBank";
			sld.startLocator = "key1";

			// считаем деньги ГГ
			pchar.questTemp.LSC.Drink.Money = sti(pchar.money);
			pchar.quest.LSC_Drink2.win_condition.l1 = "location";
			pchar.quest.LSC_Drink2.win_condition.l1.location = "VelascoBank";
			pchar.quest.LSC_Drink2.win_condition = "LSC_DrinkInVelasco";
		break;

		case "LSC_DrinkInVelasco": // внутри Веласко
			chrDisableReloadToLocation = false;
			pchar.questTemp.LSC.Drink = "grabbing";
			pchar.quest.LSC_Drink3.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_Drink3.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_Drink3.win_condition = "LSC_DrinkPedroTalk";
		break;

		case "LSC_DrinkClear": // вертаем всех на места через три часа
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("PedroHurtado");
			LAi_SetImmortal(sld, false);
			pchar.quest.LSC_Drink3.win_condition.l1 = "Timer";
			pchar.quest.LSC_Drink3.win_condition.l1.date.hour = sti(GetTime() + 3);
			pchar.quest.LSC_Drink3.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
			pchar.quest.LSC_Drink3.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.LSC_Drink3.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
			pchar.quest.LSC_Drink3.function = "LSC_DrinkDelete";
		break;
		// <-- пей до дна
		//помощь ментов в уничтожении касперов
		case "LSC_MentosStartAttackOnCasper":
			SetLaunchFrameFormParam(StringFromKey("InfoMessages_34"), "LSC_MentosStartAttackOnCasperReloadToLocation", 0, 3);
			LaunchFrameForm();
			SetCurrentTime(23, 10); //23:10
			RefreshLandTime();
		break;
		case "LSC_MentosStartAttackOnCasperReloadToLocation":
			DoQuestReloadToLocation("LostShipsCity_town", "goto", "goto03_7", "LSC_MentosAttackOnCasperMovie");
		break;
		case "LSC_MentosAttackOnCasperMovie": //идем на стрелку
			LAi_SetActorType(pchar);
			DoQuestFunctionDelay("LSC_MentosAttackOnCasper_AdditionalHelp", 25.0);
			for (i = 1; i <= 3; i++)
			{
				iTemp = GetCharacterIndex("Ment_" + i);
				if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
				{
					sld = &characters[iTemp];
					sTemp = "goto04_" + i;
					ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", sTemp);
					LAi_SetActorTypeNoGroup(sld);
					LAi_ActorGoToLocator(sld, "goto", "goto04_7", "", -1);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
			sld = CharacterFromId("MentMush_7");
			ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto03_2");
			LAi_SetActorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			sld = CharacterFromId("MentMush_8");
			ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto03_10");
			LAi_SetActorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

			sld = CharacterFromId("Ment_6");
			ChangeCharacterAddressGroup(sld, "LostShipsCity_town", "goto", "goto04_8");
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto04_5", "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetRolyPoly(sld, true);

			StartQuestMovie(false, false, true);
			locCameraFromToPos(74.83, 11.63, 46.97, false, -0.22, -20.2, 60.00);
			DoQuestFunctionDelay("LSC_MentosAttackOnCasperMovie_1", 4.0);
		break;
		case "LSC_ClearCasperDeckWaitRolyPoly":
			DoQuestCheckDelay("LSC_ClearCasperDeck", 5.0);
		break;
		case "LSC_ClearCasperDeck":
			pchar.questTemp.LSC.suicideSquad.ClearCasperDeck = true;
			if (CheckAttribute(pchar, "questTemp.LSC.MentosHelp"))
			{
				//Менты возвращаются на место
				for (i = 1; i <= 3; i++)
				{
					iTemp = GetCharacterIndex("Ment_" + i);
					if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
					{
						sld = &characters[iTemp];
						GetCharacterPos(sld, &locx, &locy, &locz);
						LAi_SetActorTypeNoGroup(sld);
						sTemp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
						if (sTemp == "reload55")
							sTemp = "reload48";
						LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "", 15.0);
					}
				}
				//мушкетеры ментов возвращаются на место
				for (i = 7; i < 9; i++)
				{
					iTemp = GetCharacterIndex("MentMush_" + i);
					if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
					{
						sld = &characters[iTemp];
						GetCharacterPos(sld, &locx, &locy, &locz);
						LAi_SetActorTypeNoGroup(sld);
						sTemp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
						if (sTemp == "reload55")
							sTemp = "reload48";
						LAi_ActorRunToLocation(sld, "reload", sTemp, "none", "", "", "", 15.0);
					}
				}
				sld = CharacterFromId("Ment_6");
			}
			else
			{
				makearef(arAll, pchar.questTemp.LSC.suicideSquad);
				iTemp = sti(GetAttributeName(GetAttributeN(arAll, 0)));
				sld = &characters[iTemp];
			}
			sld.dialog.currentnode = "StormCaspers";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "LSC_StableSuicideSquadWaitRolyPoly":
			LAi_SetFightMode(pchar, false);
			if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad"))
			{
				DoQuestCheckDelay("LSC_StableSuicideSquad", 5.0);
			}
		break;
		case "LSC_StableSuicideSquad":
			makearef(arAll, pchar.questTemp.LSC.suicideSquad);
			if (GetAttributesNum(arAll) == 0)
			{
				pchar.quest.AfterStormCaspers_ExitFromLocation.win_condition.l1 = "ExitFromLocation";
				pchar.quest.AfterStormCaspers_ExitFromLocation.win_condition.l1.location = PChar.location;
				pchar.quest.AfterStormCaspers_ExitFromLocation.function = "AfterStormCaspers_ExitFromLocation";
				chrDisableReloadToLocation = false;
				bDisableFastReload = false;
			}
			else
			{
				iTemp = sti(GetAttributeName(GetAttributeN(arAll, 0)));
				characters[iTemp].dialog.currentnode = "AfterStormCaspers";
				LAi_CharacterEnableDialog(&characters[iTemp]);
				LAi_SetActorTypeNoGroup(&characters[iTemp]);
				LAi_ActorDialog(&characters[iTemp], pchar, "", -1, 0);
			}
		break;

		case "LSC_AfterFightCasperNoSuicideSquad":
			iTemp = GetCharacterIndex("LSC_Prisoner1");
			//если тюремщик Томас Бойл с нами
			if (!LAi_IsDead(&characters[iTemp]) && characters[iTemp].location == "SanGabrielMechanic")
			{
				// ждём пока встанет
				DoQuestCheckDelay("LSC_AfterFightCasper_StartTomasDialog", 5.0);
				LAi_SetFightMode(pchar, false);
			}
			else
			{
				DoQuestCheckDelay("LSC_AfterFightCasperNoSuicideSquad_OpenTheDoors", 1.0);
			}
		break;

		case "LSC_AfterFightCasper_StartTomasDialog":
			sld = &characters[GetCharacterIndex("LSC_Prisoner1")];

			LAi_SetRolyPoly(sld, false);
			sld.dialog.currentnode = "AfterFightCasper";
			LAi_SetActorTypeNoGroup(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
		break;

		case "LSC_AfterFightCasperNoSuicideSquad_OpenTheDoors":
			chrDisableReloadToLocation = false;
		break;
		case "LSC_AfterFightCasper_Insane_OpenTheDoors":
			LocatorReloadEnterDisable("LostShipsCity_town", "reload55", false);
			chrDisableReloadToLocation = false;
		break;

		//путь чернокнижника
		case "LSC_WarlocksWayTalkAboutUs":
			if (CheckAttribute(pchar, "questTemp.LSC.suicideSquad"))
			{
				makearef(arAll, pchar.questTemp.LSC.suicideSquad);
				if (GetAttributesNum(arAll) > 0)
				{
					for (i = 0; i < GetAttributesNum(arAll); i++)
					{
						iTemp = sti(GetAttributeName(GetAttributeN(arAll, i)));
						sld = &characters[iTemp];
						PlaceCharacter(sld, "goto", "random_must_be_near");
					}
					iTemp = sti(GetAttributeName(GetAttributeN(arAll, 0)));
					characters[iTemp].dialog.currentnode = "WarlocksWay";
					LAi_SetActorTypeNoGroup(&characters[iTemp]);
					LAi_ActorDialog(&characters[iTemp], pchar, "", -1, 0);
				}
			}
		break;

		//общий сбор
		case "LSC_toSeekCrewInTavern":
			sld = CharacterFromId("MalcolmFawn");
			LAi_RemoveLoginTime(sld);
			sld.dialog.currentnode = "SeekCrewInTavern";
			ChangeCharacterAddressGroup(sld, pchar.location, pchar.location.group, pchar.location.locator);

			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "LSC_MalcolmReturn":
			sld = CharacterFromId("MalcolmFawn");
			// LAi_SetStayTypeNoGroup(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "LostShipsCity_town", "quest", "fawn", "", 10.0);
		break;

		//сценка после боя с Чадом
		case "Wait_Ment6_to_up":
			sld = characterFromId("Ment_6");
			sld.dialog.currentnode = "MentOffIsLife";
			LAi_SetActorTypeNoGroup(sld);
			LAi_ActorDialog(sld, pchar, "", -1.0, 0);
			LAi_SetRolyPoly(sld, false);
		break;
		case "LSC_talkWithWalker":
			sld = CharacterFromId("Ment_6");
			LAi_ActorWaitDialog(pchar, sld);
			//ищем друзей Уоркмана
			iTemp = 0;
			for (i = 1; i <= 3; i++)
			{
				if (GetCharacterIndex("Ment_" + i) != -1)
				{
					if (!CheckAttribute(sld, "quest.agree_man")) sld.quest.agree_man = GetCharacterIndex("Ment_" + i);
					iTemp++;
				}
			}
			for (i = 7; i < 9; i++)
			{
				if (GetCharacterIndex("MentMush_" + i) != -1)
				{
					if (!CheckAttribute(sld, "quest.agree_man")) sld.quest.agree_man = GetCharacterIndex("MentMush_" + i);
					iTemp++;
				}
			}
			//Уоркман нам друг
			if (sld.quest.AngerAtAdmiral == "4")
			{
				//всех друзей Уоркмана порешали
				if (iTemp == 0) sld.dialog.currentnode = "GoodWalkerFinishForeverAlone";
				else sld.dialog.currentnode = "GoodWalkerFinish";
			}
			//Уоркман нам не друг
			else sld.dialog.currentnode = "BadWalkerFinish";
			//trace("quest.agree_man");
			TEV.LSC_talkWithWalker_AllLookIt = true;
			DoQuestCheckDelay("LSC_AllLookIt", 9.0);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "LSC_AllLookIt":
			if (CheckAttribute(&TEV, "LSC_talkWithWalker_AllLookIt"))
			{
				for (i = 1; i < 6; i++)
				{
					iTemp = GetCharacterIndex("Ment_" + i);
					if (iTemp != -1)
					{
						LAi_ActorSetStayMode(&characters[iTemp]);
						LAi_ActorTurnToCharacter(&characters[iTemp], pchar);
					}
				}
			}
		break;
		case "LSC_talkWithWalker_1":
			locCameraFromToPos(-10.927, 15.261, 8.544, true, 13.00, 2.00, -5.00);
			iTemp = GetCharacterIndex("MentProt_7");
			if (iTemp != -1)
			{
				sld = &characters[iTemp];
			}
			else
			{
				for (i = 1; i < 6; i++)
				{
					iTemp = GetCharacterIndex("Ment_" + i);
					if (iTemp != -1)
					{
						sld = &characters[iTemp];
						break;
					}
				}
			}
			sld.dialog.filename = "Quest\LostShipsCity\Mentos.c";
			sld.dialog.currentnode = "EndWalkerFinish";
			LAi_SetActorType(sld);
			LAi_ActorWaitDialog(pchar, sld);
			LAi_ActorDialogNow(sld, pchar, "", 0);
		break;
		case "LSC_talkWithWalker_2":
			sTemp = LAI_GROUP_PLAYER;
			//обработка друзей Уоркмана
			if (CheckAttribute(pchar, "questTemp.LSC.walker_finish.walker_ment")) sTemp = "EnemyFight";
			sld = CharacterFromId("Ment_6");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_group_MoveCharacter(sld, sTemp);
			for (i = 1; i <= 3; i++)
			{
				iTemp = GetCharacterIndex("Ment_" + i);
				if (iTemp != -1)
				{
					sld = &characters[iTemp];
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sTemp);
				}
			}
			for (i = 7; i < 9; i++)
			{
				iTemp = GetCharacterIndex("MentMush_" + i);
				if (iTemp != -1)
				{
					sld = &characters[iTemp];
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sTemp);
				}
			}
			//обработка бойцов адмирала
			sTemp = LAI_GROUP_PLAYER;
			if (CheckAttribute(pchar, "questTemp.LSC.walker_finish.admital_ment")) sTemp = "EnemyFight";
			for (i = 4; i <= 5; i++)
			{
				iTemp = GetCharacterIndex("Ment_" + i);
				if (iTemp != -1)
				{
					sld = &characters[iTemp];
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sTemp);
				}
			}
			for (i = 9; i <= 10; i++)
			{
				iTemp = GetCharacterIndex("MentMush_" + i);
				if (iTemp != -1)
				{
					sld = &characters[iTemp];
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sTemp);
				}
			}
			for (i = 7; i <= 10; i++)
			{
				iTemp = GetCharacterIndex("MentProt_" + i);
				if (iTemp != -1 && i != 9)
				{
					sld = &characters[iTemp];
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, sTemp);
				}
			}
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "LSC_talkWithWalker_3");
			DeleteAttribute(pchar, "questTemp.LSC.walker_finish");
			DoQuestCheckDelay("LSC_talkWithWalker_4", 10.0);
		break;
		case "LSC_talkWithWalker_3":
			chrDisableReloadToLocation = true;
			//всех выживших расфирмировываем
			iCount = 0;
			for (i = 1; i <= 5; i++)
			{
				iTemp = GetCharacterIndex("Ment_" + i);
				if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
				{
					sld = &characters[iTemp];
					iCount++;
					sld.lifeDay = 0;
					LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
				}
			}
			for (i = 7; i <= 10; i++)
			{
				iTemp = GetCharacterIndex("MentMush_" + i);
				if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
				{
					sld = &characters[iTemp];
					iCount++;
					sld.lifeDay = 0;
					LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
				}
			}
			for (i = 7; i <= 10; i++)
			{
				iTemp = GetCharacterIndex("MentProt_" + i);
				if (iTemp != -1 && i != 9 && !LAi_IsDead(&characters[iTemp]))
				{
					sld = &characters[iTemp];
					iCount++;
					sld.lifeDay = 0;
					LAi_group_MoveCharacter(sld, LAI_GROUP_TmpEnemy);
				}
			}
			//стражник у тюрьмы
			iTemp = GetCharacterIndex("MentProt_9");
			if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
			{
				sld = &characters[iTemp];
				iCount++;
				sld.lifeDay = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
			//выживших добавляем в состав команды
			if (iCount != 0) SetCrewQuantity(pchar, GetCrewQuantity(pchar) + iCount);
			//стабилизируется Уолкер
			sld = CharacterFromID("Ment_6");
			if (!LAi_IsDead(sld))
			{
				LAi_SetActorType(sld);
				sld.cityTape = "toLeave";
				LAi_group_MoveCharacter(sld, LAI_GROUP_DEFAULT);
				LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 15.0);
			}
			//стабилизируются суицидники
			sld = CharacterFromID("MaximTailor");
			if (!LAi_IsDead(sld) && CheckAttribute(sld, "quest.suicidus") && sld.location == pchar.location)
			{
				LAi_SetRolyPoly(sld, false);
				LAi_SetActorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_DEFAULT);
				LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 15.0);
			}
			iTemp = GetCharacterIndex("LSC_Prisoner1");
			if (iTemp != -1)
			{
				sld = &characters[iTemp];
				if (!LAi_IsDead(sld) && CheckAttribute(sld, "quest.suicidus") && sld.location == pchar.location)
				{
					LAi_SetRolyPoly(sld, false);
					LAi_SetActorType(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_DEFAULT);
					LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 15.0);
				}
			}

			sld = CharacterFromID("MalcolmFawn");
			if (!CheckAttribute(sld, "quest.suicidus")) ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto09_0");
			if (sld.chr_ai.type == LAI_TYPE_INJURE)
			{
				DoQuestCheckDelay("LSC_talkWithWalker_3_StartMalcolmDialog", 5.0);
			}
			else
			{
				DoQuestCheckDelay("LSC_talkWithWalker_3_StartMalcolmDialog", 1.0);
			}
		break;
		case "LSC_talkWithWalker_3_StartMalcolmDialog":
		//Малькольм идет поговорить
			sld = CharacterFromID("MalcolmFawn");
			LAi_CharacterEnableDialog(sld);
			LAi_SetRolyPoly(sld, false);
			sld.dialog.currentnode = "GoToSaveMechanic";

			if (sld.location != pchar.location)
			{
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto09_0");
			}
			LAi_SetActorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_DEFAULT);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		case "LSC_talkWithWalker_4":
			sld = CharacterFromID("MalcolmFawn");
			if (CheckAttribute(sld, "quest.suicidus"))
			{
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto09_0");
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				LAi_SetRolyPoly(sld, true);
			}
			sld = CharacterFromID("MaximTailor");
			if (CheckAttribute(sld, "quest.suicidus"))
			{
				ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto09_5");
				LAi_SetWarriorTypeNoGroup(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			iTemp = GetCharacterIndex("LSC_Prisoner1");
			if (iTemp != -1)
			{
				sld = &characters[iTemp];
				if (CheckAttribute(sld, "quest.suicidus"))
				{
					ChangeCharacterAddressGroup(sld, pchar.location, "goto", "goto09_6");
					LAi_SetWarriorTypeNoGroup(sld);
					LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
				}
			}
		break;
		case "LSC_talkWithWalker_MilitiaEscape":
		// ментов отправляем спасаться
			iCount = 0;
			for (i = 1; i <= 5; i++)
			{
				iTemp = GetCharacterIndex("Ment_" + i);
				if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
				{
					sld = &characters[iTemp];
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload55", "none", "", "", "", 90.0);
				}
			}
			for (i = 7; i <= 10; i++)
			{
				iTemp = GetCharacterIndex("MentMush_" + i);
				if (iTemp != -1 && !LAi_IsDead(&characters[iTemp]))
				{
					sld = &characters[iTemp];
					LAi_SetActorType(sld);
					if (i == 8) // мушкетер на баке
					{
						ChangeCharacterAddressGroup(sld, "none", "", "");
					}
					LAi_ActorRunToLocation(sld, "reload", "reload55", "none", "", "", "", 90.0);
				}
			}
			for (i = 7; i <= 10; i++)
			{
				iTemp = GetCharacterIndex("MentProt_" + i);
				if (iTemp != -1 && i != 9 && !LAi_IsDead(&characters[iTemp]))
				{
					sld = &characters[iTemp];
					LAi_SetActorType(sld);
					LAi_ActorRunToLocation(sld, "reload", "reload55", "none", "", "", "", 90.0);
				}
			}
		break;
		case "LSC_MalcolmStay":
			sld = CharacterFromID("MalcolmFawn");
			LAi_SetActorType(sld);
			sld.dialog.currentnode = "GoodBye";

			pchar.quest.Duglas_Officer.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Duglas_Officer.win_condition.l1.location = pchar.location;
			pchar.quest.Duglas_Officer.win_condition = "LSC_MalcolmFinishDialog";
		break;
		case "LSC_CheckPeopleOnDiffindur":
			DoQuestFunctionDelay("LSC_GoodByeEnough", 1.0);
		break;
		case "LSC_MalcolmFinishDialog":
			sld = CharacterFromID("MalcolmFawn");
			LAi_ActorDialog(sld, pchar, "", 5.0, 0);
		break;
		case "LSC_finishSelfTalk":
			sld = CharacterFromID("MalcolmFawn");
			LAi_ActorRunToLocation(sld, "goto", "goto17_4", "none", "", "", "", 10.0);
			pchar.questTemp.LSC = "finishSelfTalk";
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto17_3", "TalkSelf_Start", 5.0);
		break;
		case "LSC_finishMovie":
			StartQuestMovie(false, false, true);
			locCameraFlyToPositionLookToHero(3.57, 10.64, 178.96, 103.57, 52.83, 130.96, 0.015, -1);
			Pchar.FuncCameraFly = "";
			Sea.MaxSeaHeight = 7.0;

			Sea.Sea2.Amp1 = 6.0;
			Sea.Sea2.AnimSpeed1 = 4.25;
			Sea.Sea2.Scale1 = 0.5;

			Sea.Sea2.Amp2 = 4.0;
			Sea.Sea2.AnimSpeed2 = 9.0;
			Sea.Sea2.Scale2 = 0.5;

			Sea.Sea2.FoamV = 1.5;
			Sea.Sea2.FoamK = 0.04;
			Sea.Sea2.FoamUV = 0.15;
			Sea.Sea2.PosShift = 0.25;

			DoQuestCheckDelay("LSC_finishMovieWaterFall", 0.2);
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocation(pchar, "goto", "goto17_4", "LostShipsCity_town", "reload", "reload66", "LSC_DeleteShellBoat", 10.0);
		break;
		case "LSC_DeleteShellBoat":
			DeleteShellBoat("LostShipsCity_town");
		break;
		case "LSC_finishMovieWaterFall":
			if (stf(Sea.MaxSeaHeight) < 25.0)
			{
				LSC_WaterUpFunction();
				DoQuestFunctionDelay("LSC_finishMovieWaterFallFunction", 0.02);
			}
			else
			{
				DoQuestCheckDelay("LSC_TeleportFromLSC", 1.0);
			}
		break;
		case "LSC_TeleportFromLSC":
			Whr_SetLock(false);
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			locCameraNextState();
			pchar.quest.LSC_StormWaterUp.win_condition.l1 = "ExitFromLocation";
			pchar.quest.LSC_StormWaterUp.win_condition.l1.location = pchar.location;
			pchar.quest.LSC_StormWaterUp.function = "LSC_closeLine";
			QuestToSeaLogin_Prepare(-670.034, -614.29, "LostShipsCity");
			questToSeaLoginer.FromCoast = true;
			QuestToSeaLogin_Launch();
		break;
		case "LSC_StopStorm":
			WeatherParams.Storm = false;
			DoQuestFunctionDelay("LSC_takeStormIsland", 0.5);
			pchar.quest.LSC_takeStormIsland.over = "yes";
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квесты ГПК				<===
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		case "Teno_youWinFight":
			pchar.questTemp.Teno = "YouWinGod"; //флаг конца линейки Тено
			LAi_SetFightMode(pchar, false);
			iTemp = GetCharacterIndex("AztecCitizen_1");
			if (iTemp != -1) characters[iTemp].dialog.currentnode = "Aztec1AF";
			iTemp = GetCharacterIndex("AztecCitizen_2");
			if (iTemp != -1) characters[iTemp].dialog.currentnode = "Aztec2AF";
			LocatorReloadEnterDisable("Tenochtitlan", "reload1_back", true);
			sld = characterFromId("Montesuma");
			sld.lastname = "II";
			sld.dialog.currentnode = "AfterGTemple";
			DeleteAttribute(sld, "reactionOnFightModeOn");
			DeleteAttribute(sld, "BreakTmplAndFight");
			LAi_SetActorType(sld);
			LAi_ActorStay(sld);
			ChangeCharacterAddressGroup(sld, "Tenochtitlan", "teleport", "fire1");
			pchar.quest.Teno_exitFromTeno.win_condition.l1 = "locator";
			pchar.quest.Teno_exitFromTeno.win_condition.l1.location = "Tenochtitlan";
			pchar.quest.Teno_exitFromTeno.win_condition.l1.locator_group = "teleport";
			pchar.quest.Teno_exitFromTeno.win_condition.l1.locator = "fire1";
			pchar.quest.Teno_exitFromTeno.function = "Teno_exitFromTeno";
			sld = characterFromId("DeadmansGod");
			sld.dialog.currentnode = "WinInTemple";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 1.0, 0);
		break;

		case "Teno_MontesumaArrived":
			sld = characterFromId("Montesuma");
			LAi_ActorTurnByLocator(sld, "quest", "quest1");
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_warrior_SetStay(sld, true);
		break;

		case "Teno_CollierGroup_Dead":
			LAi_group_Delete("Teno_CollierGroup");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////  homo  Линейка Блада     начало
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		//case "CureLord":
		//    CureLord();
		//break;
		
		case "CapBloodLine_Kirk_2":
			CapBloodLine_Kirk_2();
		break;
		
		case "CapBloodLine_Kirk_4":
			CapBloodLine_Kirk_4();
		break;
		
		case "CapBloodLine_Kirk_9":
			CapBloodLine_Kirk_9();
		break;
		
		case "CapBloodLine_Kirk_10":
			CapBloodLine_Kirk_10();
		break;

		case "CureLordMovie_Con1":
			CureLordMovie_Con1();
		break;

		case "CureLordMovie_Con2":
			CureLordMovie_Con2();
		break;

		case "CureLordMovie_Con3":
			DoQuestFunctionDelay("CureLordMovie_Con3", 0.5);
		break;

		case "CapBloodLineInit":
			CapBloodLineInit("");
		break;

		case "CapBlood_CheckMinHP":
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
			InterfaceStates.Buttons.Save.enable = false;
			InterfaceStates.Launched = true;
			LAi_SetFightMode(pchar, false);
			DoQuestFunctionDelay("Blood_StartGame_End", 1.5);
		//CapBloodLineInit();
		break;

		case "Dragun_2_CheckMinHP":
			for (i = 0; i <= 2; i++)
			{
				sld = characterFromID("Dragun_" + i);
				if (i == 2)
				{
					LAi_RemoveCheckMinHP(sld);
					LAi_KillCharacter(sld);
				}
				else
				{
					string sQuest = "CapGobartAttack_" + i;
					pchar.quest.(sQuest).win_condition.l1 = "NPC_Death";
					pchar.quest.(sQuest).win_condition.l1.character = sld.id;
					pchar.quest.(sQuest).function = "CapGobartAttack";
					LAi_SetImmortal(sld, false);
					LAi_SetWarriorTypeNoGroup(sld);//fix
					LAi_warrior_DialogEnable(sld, false);//fix
					LAi_group_MoveCharacter(sld, "TmpEnemy");
				}
			}
			SetTutorials_Blood_AfterFirstFight();
		//LAi_group_FightGroups("TmpEnemy", LAI_GROUP_PLAYER, true);
		break;

		case "BishopOnHouse":
			sld = characterFromID("Bishop");
			sld.talker = 10;
			LAi_SetCitizenType(sld);
			LAi_SetOwnerTypeNoGroup(sld);
		//LAi_SetStayTypeNoGroup(sld);

		break;

		case "NettlOnTavern":
			sld = characterFromID("Nettl");
			LAi_SetSitTypeNoGroup(sld);
			//sld.dialog.currentnode = "NStep_1";
			ChangeCharacterAddressGroup(sld, "Bridgetown_tavern", "sit", "sit8");
			if (Pchar.questTemp.CapBloodLine.stat == "needMoney")
			{
				AddLandQuestmark_Main_WithCondition(sld, "CapBloodLine", "CapBloodLine_NeedMoney_Nettl_QuestMarkCondition");
				if (CapBloodLine_CheckMoneyForNettl())
					QuestPointerToLocEx("Bridgetown_town", "reload", "reload4_back", "CapBloodLine_q2");
			}
			PChar.Quest.Nettl_Away_Force.over = "yes";
		break;

		case "SSOnHouse":
            Pchar.questTemp.CapBloodLine.stat = "PrepareToEscape2_1";
            CapBloodLine_SpainSpy_AddQuestMarks();
        break;

		case "SaveArabelaServiceAfraid":
			npchar = characterFromID("ArabelaService");
			sld = characterFromID("SpaRaider");
			LAi_ActorAfraid(npchar, sld, true);
			LAi_SetWarriorTypeNoGroup(sld);
			LAi_warrior_DialogEnable(sld, false);
			LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		//sld.talker = 10;
		//LAi_ActorDialog(sld, pchar, "",  3.0, 0);
		break;

		case "ShipGuardsDie":
			ShipGuardsDie();
		break;

		case "move_slave_2":
			Pchar.model = "blood_bomj";
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE); // Hokkins: Fix активного индикатора огнестрельного оружия, при старте на плантации!
			pchar.quest.CapBloodLine_firstEnterHome.win_condition.l1 = "location";
			pchar.quest.CapBloodLine_firstEnterHome.win_condition.l1.location = "Bridgetown_Plantation_G6";
			pchar.quest.CapBloodLine_firstEnterHome.function = "CapBloodLine_firstEnterHome";
			StartPictureAsVideo("Loading\finalbad2.tga", 1);
			DoReloadCharacterToLocation("Bridgetown_Plantation_G6", "goto", "goto1");
			LAi_MethodDelay("FadeDelay", 0.1);
		break;
		//homo
		case "CapBloodLine_ShipTakeGate_Reset":
			CapBloodLine_ShipTakeGate_Reset();
		break;
		// Захват Арабелы - катсцена
		// CBL_AST - CapBloodLine_ArabellaShipTake
		case "CBL_AST_crewman1_Reached":
			LAi_type_actor_Reset(pchar);
			LAi_ActorAnimation(pchar, "attack_fast_1", "CBL_AST_guard2_OnDeath", 1.5);

			sld = CharacterFromID("ShipGuard_2");
			LAi_SetCurHP(sld, 0.0);
			LAi_KillCharacter(sld);
		break;
		case "CBL_AST_crewman2_Reached":
			sld = CharacterFromID("Hugtorp");
			LAi_type_actor_Reset(sld);
			LAi_ActorAnimation(sld, "attack_force_5", "CBL_AST_guard3_OnDeath", 1.5);

			sld = CharacterFromID("ShipGuard_3");
			LAi_SetCurHP(sld, 0.0);
			LAi_KillCharacter(sld);
		break;
		case "CBL_AST_guard2_OnDeath":
			LAi_ActorAnimation(pchar, "fight stand_2", "", -1);

			DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_4", 3.0);
			DoQuestFunctionDelay("CBL_AST_crewman6", 0.2);
		break;
		case "CBL_AST_guard3_OnDeath":
			sld = CharacterFromID("Hugtorp");
			LAi_ActorAnimation(sld, "fight stand_7", "", -1);
		break;
		case "CBL_AST_crewman3_Reached":
			sld = CharacterFromID("Ogl");
			LAi_ActorFollow(sld, CharacterFromID("ShipGuard_1"), "CBL_AST_crewman3_1_Reached", 5.0);

			DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_4_1", 0.1);
		break;
		case "CBL_AST_crewman3_1_Reached":
			sld = CharacterFromID("Ogl");
			LAi_type_actor_Reset(sld);
			LAi_ActorAnimation(sld, "attack_break_1", "CBL_AST_guard1_OnDeath", 1.5);

			DoQuestCheckDelay("CBL_AST_crewman3_OnAttack", 1.0);
		break;
		case "CBL_AST_crewman3_OnAttack":
			sld = CharacterFromID("ShipGuard_1");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_CharacterPlaySound(sld, "CBL_BackStab");

			LAi_SetCurHP(sld, 0.0);
			LAi_KillCharacter(sld);
		break;
		case "CBL_AST_guard1_OnDeath":
			sld = CharacterFromID("Ogl");
			LAi_ActorAnimation(sld, "fight stand_5", "CBL_AST_crewman3_OnIdle", 3.0);

			DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_5", 5.0);
		break;
		case "CBL_AST_crewman3_OnIdle":
			sld = CharacterFromID("Ogl");
			LAi_ActorAnimation(sld, "fight stand_2", "", -1);
		break;
		case "CBL_AST_crewman4_Reached":
			sld = CharacterFromID("FreeSlave_1");
			LAi_ActorGoToLocator(sld, "rld", "aloc15", "", -1);

			sld = CharacterFromID("Hugtorp");
			LAi_type_actor_Reset(sld);
			LAi_ActorGoToLocator(sld, "rld", "aloc3", "", 5.0);
		break;
		case "CBL_AST_crewman4_1_Reached":
			sld = CharacterFromID("FreeSlave_1");
			LAi_CharacterPlaySound(sld, "CBL_squeak_planks");

			npchar = CharacterFromID("ShipGuard_0");
			LAi_ActorTurnToCharacter(npchar, sld);

			sld = CharacterFromID("Volverston");
			LAi_ActorRunToLocatorNoCheck(sld, "quest", "quest21", "CBL_AST_crewman5_Reached", 2.0);

			DoQuestCheckDelay("CBL_AST_guard0_Shot", 0.25);
		break;
		case "CBL_AST_guard0_Shot":
			sld = CharacterFromID("ShipGuard_0");

			LAi_type_actor_Reset(sld);
			LAi_ActorAnimation(sld, "shot", "", -1);
			DoQuestCheckDelay("CBL_AST_crewman4_Death", 0.75);

			sld = CharacterFromID("FreeSlave_1");
			LAi_ActorRunToLocatorNoCheck(sld, "rld", "aloc7", "", -1);

			DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_5_3", 1.0);
		break;
		case "CBL_AST_crewman4_Death":
			sld = CharacterFromID("FreeSlave_1");
			LAi_SetCurHP(sld, 0.0);
			LAi_KillCharacter(sld);
		break;
		case "CBL_AST_crewman5_Reached":
			sld = CharacterFromID("Volverston");

			npchar = CharacterFromID("ShipGuard_0");
			LAi_ActorTurnToCharacter(sld, npchar);
			LAi_ActorTurnToCharacter(npchar, sld);

			LAi_ActorAnimation(sld, "CBL_attack_break_fast", "CBL_AST_crewman5_OnAttack", 0.5);

			LAi_type_actor_Reset(npchar);
			LAi_ActorAnimation(npchar, "CBL_block", "", 2.0);
		break;
		case "CBL_AST_crewman5_OnAttack":
			sld = CharacterFromID("ShipGuard_0");
			LaunchBlood(sld, 1.0 + frand(0.6), true, "fight");
			LAi_CharacterPlaySound(sld, "CBL_BlockBreak");

			LAi_SetCurHP(sld, 0.0);
			LAi_KillCharacter(sld);
			LAi_ActorAnimation(sld, "death_0", "", -1);

			sld = CharacterFromID("Volverston");
			LAi_ActorAnimation(sld, "fight stand_2", "", -1);

			DoQuestFunctionDelay("CapBloodLine_ArabellaShipTakeScene_6", 2.0);
		break;
		// <--
		// Линейка Блада - Глобальный туториал
		case "BloodLine_GlobalTutor_EndTortuga1Dialog":
			chrDisableReloadToLocation = false;
			bDisableCharacterMenu = false;
 			QuestPointerToLoc("Tortuga_town", "reload", "reload5_back");
 			AddLandQuestmark_Main(CharacterFromId("Tortuga_shipyarder"), "GlobalTutor");
 			// потом снимем - Арабелу нужно передать кому-то другому =)
 			SetCharacterRemovable(CharacterFromID("Pitt"), false);
 			if (GetTime() > 21.0 || GetTime() < 7.0)
			{
				iTemp = 1;
				if (GetTime() > 21.0) iTemp = sti(24 - GetHour()) + 1 + 7;
				if (GetTime() < 7.0) iTemp = sti(7 - GetHour()) + 1;
				SetLaunchFrameFormParam(StringFromKey("InfoMessages_23"), "Reload_To_Location", 0.1, 2.0);
				SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "BloodLine_GlobalTutor_TortugaStartShipTask");
				WaitDate("", 0, 0, 0, iTemp, 0);
				LaunchFrameForm();
				RefreshLandTime();
				RecalculateJumpTable();
				Whr_UpdateWeather();
			}
			else
			{
			    DoQuestFunctionDelay("BloodLine_GlobalTutor_StartNavigationTutorial", 2.0);
			}
			// лок на обновление времени
			pchar.questTemp.TimeLock = true;
			// обновляем команду в таверне
			SetCrewQuantityOverMax(GetColonyByIndex(FindColony("Tortuga")), sti(pchar.questTemp.BloodLine_GTutor.hireCrewQty));
			// офицеров не генерим
			LAi_LocationDisableOfficersGen("Tortuga_shipyard", true);
			LAi_LocationDisableOfficersGen("Tortuga_PortOffice", true);
			LAi_LocationDisableOfficersGen("Tortuga_tavern", true);
			// прерывание на верфи
			SetFunctionLocationCondition("BloodLine_GlobalTutor_OnTortugaShipyard", "Tortuga_shipyard", false);

		break;
		case "BloodLine_GlobalTutor_TortugaStartShipTask":
			// старт туториала
			DoQuestFunctionDelay("BloodLine_GlobalTutor_StartNavigationTutorial", 2.0);
		break;
		case "BloodLine_GlobalTutor_EndTortuga2Dialog":
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable("Tortuga_town", "reload4_back", false);
			QuestPointerToLoc("Tortuga_town", "reload", "reload4_back");
 			AddLandQuestmark_Main(CharacterFromId("Tortuga_tavernkeeper"), "GlobalTutor");
 			// открыть таск
 			DoQuestFunctionDelay("BloodLine_GlobalTutor_StartCrewTutorial", 1.0);
			// прерывание в таверне
			SetFunctionLocationCondition("BloodLine_GlobalTutor_OnTortugaTavern", "Tortuga_tavern", false);
		break;
		//<-- Глобальный туториал
		//-->работорговец
		case "Slavetrader_Ambush":
			chrDisableReloadToLocation = true;
			pchar.quest.Slavetrader_Ambush_over.Ususer_group = Characters[GetCharacterIndex(pchar.questTemp.Slavetrader.UsurerId)].chr_ai.group;
			//Временная группа ростовщика, чтобы на нас случайно не ополчился гарнизон
			LAi_group_MoveCharacter(CharacterFromId(pchar.questTemp.Slavetrader.UsurerId), LAI_GROUP_PLAYER);
			LAi_SetImmortal(CharacterFromId(pchar.questTemp.Slavetrader.UsurerId), true);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetFightMode(pchar, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_Ambush_Over");
		break;

		case "Slavetrader_Ambush_Over":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			FightDisable_Forced();
			LAi_LocationFightDisable(&Locations[FindLocation(Characters[GetCharacterIndex(pchar.questTemp.Slavetrader.UsurerId)].location)], true);
			LAi_group_MoveCharacter(CharacterFromId(pchar.questTemp.Slavetrader.UsurerId), pchar.quest.Slavetrader_Ambush_over.Ususer_group);
			LAi_SetImmortal(CharacterFromId(pchar.questTemp.Slavetrader.UsurerId), false);
		break;

		case "Slavetrader_findTortugaRat"://охрана Гонтьера
			SetBan("Looting,Exchange", 1);
			chrDisableReloadToLocation = true; // закрыть выход из локации
			sld = GetCharacter(NPC_GenerateCharacter("Ratlover", "horse02", "woman", "towngirl", 10, FRANCE, -1, false));
			ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "barmen", "bar2");
			sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Rat_lover"; // диалоговый узел
			sld.name = FindPersonalName("Ratlover_name");
			sld.lastname = FindPersonalName("Ratlover_lastname");
			LAi_SetImmortal(sld, true);
			LAi_SetStayTypeNoGroup(sld);

			sld = GetCharacter(NPC_GenerateCharacter("SLBanditHead", "citiz_51", "man", "man", 25, PIRATE, 0, true));
			FantomMakeCoolFighter(sld, 45, 100, 100, "blade26", "pistol6", 80);
			sld.cirassId = FindItem("cirass5");
			LAi_SetStayType(sld);
			sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Rat_bandos";
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld.DontClearDead = true;
			ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "goto", "goto1");
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.3);
		break;

		case "Slavetrader_findTortugaRat1"://охрана Гонтьера
			arrayNPCModelHow = 0;
			for (i = 3; i <= 5; i++)
			{
				sld = GetCharacter(NPC_GenerateCharacter("SVBandit" + i, "citiz_" + (rand(9) + 51), "man", "man", 25, PIRATE, 0, true));
				SetNPCModelUniq(sld, "mercenary", MAN);
				FantomMakeCoolFighter(sld, 35, 100, 100, "blade33", "pistol6", 80);
				LAi_SetStayType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.DontClearDead = true;
				ChangeCharacterAddressGroup(sld, "Tortuga_HouseHut", "goto", "goto" + i);
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat2");
		break;

		case "Slavetrader_findTortugaRat2":
			chrDisableReloadToLocation = false;
			LAi_SetActorType(pchar);
			sld = characterFromID("Ratlover");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		break;

		case "Slavetrader_EscapeSlaves_Win":
			chrDisableReloadToLocation = false;
			sld = GetCharacter(NPC_GenerateCharacter("Slavewoman", "horse99", "woman", "towngirl", 10, PIRATE, -1, false));
			ChangeCharacterAddressGroup(sld, pchar.questTemp.Slavetrader.Island.Shore, "goto", "goto31");
			sld.Dialog.Filename = "Quest\Other_quests_NPC.c";
			sld.dialog.currentnode = "Slave_woman"; // диалоговый узел
			sld.name = FindPersonalName("Slave_woman_name");
			sld.lastname = "";
			LAi_SetImmortal(sld, true);
			LAi_SetStayTypeNoGroup(sld);
			LAi_SetActorType(pchar);
			sld = characterFromID("Slavewoman");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);

		break;
		//<--работорговец

		//ОЗГ, Карлос Кассир
		case "CarlosDie":
			if (CheckAttribute(PChar, "quest.CarlosPlace")) Pchar.quest.CarlosPlace.over = "yes";
			if (CheckAttribute(PChar, "quest.HeadhunterTimer")) Pchar.quest.HeadhunterTimer.over = "yes";
			DoQuestCheckDelay("hide_weapon", 1.0);
			chrDisableReloadToLocation = false;
			LAi_LocationDisableOfficersGen(pchar.questTemp.Headhunter.City + "_ExitTown", false); //офицеров пускать
			DeleteAttribute(&locations[FindLocation(pchar.questTemp.Headhunter.City + "_ExitTown")], "DisableEncounters"); //энкаутеры откроем
			AddQuestRecord("Headhunt", "2");
			pchar.questTemp.Headhunter = "hunt_carlos_yes";
			AddLandQuestMark_Main(CharacterFromID("LeFransua_tavernkeeper"), "Headhunt");
		break;

		//ОЗГ, наймиты Крысы
		case "RatHunters_Dead":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Headhunt", "28");
			pchar.questTemp.Headhunter = "halen_still";
			AddLandQuestMark_Main(CharacterFromID("Villemstad_tavernkeeper"), "Headhunt");
		break;

		case "Headhunter_FightInPort":
			LocatorReloadEnterDisable("Villemstad_town", "gate", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload33", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);

			pchar.quest.Headhunter_Halen_fight.win_condition.l1 = "NPC_Death";
			pchar.quest.Headhunter_Halen_fight.win_condition.l1.character = "Halen";
			pchar.quest.Headhunter_Halen_fight.win_condition = "Headhunter_HalenDeadInTown";

			iTemp = GetCharacterIndex("Halen");
			if (iTemp != -1)
			{
				sld = &characters[iTemp];
				LAi_RemoveCheckMinHP(sld);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
				LAi_group_Attack(sld, Pchar);
				SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);
				RemoveLandQuestMark_Main(sld, "Headhunt");
			}
		break;

		case "Headhunter_HalenOut":
			if (CheckAttribute(pchar, "quest.Headhunter_SeekHalen"))
			{
			    pchar.quest.Headhunter_SeekHalen.over = "yes";
			}
			ChangeCharacterAddress(characterFromID("Halen"), "None", "");
			LocatorReloadEnterDisable("Villemstad_town", "gate", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload33", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
		break;

		case "Headhunter_MissHalen":
			if (CheckAttribute(pchar, "quest.Headhunter_HalenTimer"))
			{
			    pchar.quest.Headhunter_HalenTimer.over = "yes";
			}
			pchar.quest.Headhunter_MissHalen.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Headhunter_MissHalen.win_condition.l1.location = "Villemstad_town";
			pchar.quest.Headhunter_MissHalen.win_condition = "Headhunter_HalenOut";
		break;

		case "Headhunter_HalenDeadInTown":
			LocatorReloadEnterDisable("Villemstad_town", "gate", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload33", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
			LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
		break;

		case "FindJa":
			chrDisableReloadToLocation = false;
			AddQuestRecord("Headhunt", "35");
		break;

		// Myth fix -->
		case "TestPgg":
			DoQuestReloadToLocation(PChar.location.from_sea, "reload", "sea", "PGG_end");
		break;

		case "TestPgg1":
			DoQuestReloadToLocation("Ship_deck", "reload", "reload1", "PGG_end");
		break;

		case "Pgg_end":
			DoQuestCheckDelay("Pgg_end2", 1);
		break;

		case "Pgg_end2":
			PGG_Q1LocationLoaded("");
		break;
		// Myth fix <--

		case "NewMayorName":
			ref Mayor = CharacterFromID(TEV.oldMayor);
			SetRandomNameToCharacter(Mayor);
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Действия горожан по мини-квестам	--->
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		//отпускание рабов через монаха
		case "Monk_RemoveSlaves":
			int iSlavesQty = GetSquadronGoods(pchar, GOOD_SLAVES);
			ChangeCharacterReputation(pchar, (iSlavesQty >= 500) * 3 + (iSlavesQty >= 300) * 3 + (iSlavesQty >= 100) * 3 + 1);
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			OfficersReaction("good");
		break;

		//освящение кораблей через монаха
		case "Monk_Shipshine":
			OfficersReaction("good");
			ChangeCharacterReputation(pchar, 2);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			AddCrewMorale(pchar, 10);
			pchar.quest.Shipshine.win_condition.l1 = "Timer";
			pchar.quest.Shipshine.win_condition.l1.date.hour = sti(GetTime());
			pchar.quest.Shipshine.win_condition.l1.date.day = GetAddingDataDay(0, 0, 15);
			pchar.quest.Shipshine.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 15);
			pchar.quest.Shipshine.win_condition.l1.date.year = GetAddingDataYear(0, 0, 15);
			pchar.quest.Shipshine.function = "Monkshipshine_Over";
		break;

		//установка капеллана в кают-компанию
		case "Monk_Capellan":
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId(pchar.questTemp.ShipCapellan.id);
			sld.dialog.currentnode = "capellan_4";
			LAi_SetStayType(sld);
		break;

		//установка дворянина с реликвией в таверну
		case "Nobleman_lombardTavern":
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId(pchar.GenQuest.Noblelombard.id);
			sld.dialog.currentnode = "lombard_4";
			LAi_SetSitType(sld);
		break;

		//установка дворянина в церковь
		case "Nobleslaves_Place":
			chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId(TEV.NobleSlaves_NoblemanId);
			sld.nonTable = true;
			sld.dialog.currentnode = "slaves_3";
			LAi_SetSitType(sld);
			LAi_SetLoginTime(sld, 11.0, 13.0);
			DeleteAttribute(&TEV, "NobleSlaves_NoblemanId");
		break;

		//выдача пассажира после абордажа
		case "Marginpassenger_GivePrisoner":
			sld = GetCharacter(NPC_GenerateCharacter("MarginPass", pchar.GenQuest.Marginpassenger.model, pchar.GenQuest.Marginpassenger.sex, pchar.GenQuest.Marginpassenger.ani, 2, sti(pchar.GenQuest.Marginpassenger.Nation), -1, true));
			sld.Dialog.Filename = "Quest\Marginpassenger.c";
			sld.dialog.currentnode = "MarginPass";
			sld.name = pchar.GenQuest.Marginpassenger.q1Name;
			sld.lastname = "";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
			pchar.GenQuest.Marginpassenger.Boarding = "true";
			AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
			AddComplexSelfExpToScill(60, 60, 60, 60);
		break;

		//после боя в бухте
		case "Marginpassenger_Afterbattle":
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = false;
			AddCharacterGoods(pchar, sti(pchar.GenQuest.Marginpassenger.Goods), sti(pchar.GenQuest.Marginpassenger.GoodsQty));
			AddQuestRecord("Marginpassenger", "15");
			AddQuestUserData("Marginpassenger", "sSex", GetSexPhrase("ёл", "ла"));
			AddQuestUserData("Marginpassenger", "sSex2", GetSexPhrase("", "а"));
			AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat"));
			CloseQuestHeader("Marginpassenger");
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			AddComplexSelfExpToScill(80, 80, 80, 80);
			AddCrewMorale(Pchar, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
			ChangeOfficersLoyality("good_all", 1);
			ChangeCharacterNationReputation(pchar, SPAIN, -2);
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	<---	Действия горожан по мини-квестам
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Проклятый Идол" начало				===>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "PDM_CI_SpawnJC":
			sld = GetCharacter(NPC_GenerateCharacter("James_Callow", "James_Callow", "man", "man", 10, PIRATE, -1, true));
			sld.name = FindPersonalName("James_Callow_name");                                            //Джеймс Кэллоу
			sld.lastname = FindPersonalName("James_Callow_lastname");
			sld.Dialog.Filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "First time";
			LAi_SetSitType(sld);
			LAi_SetImmortal(sld, true);
			FreeSitLocator("LaVega_tavern", "sit_base3");
			DoQuestCheckDelay("PDM_CI_SpawnJC_2", 1.5); //fix
		break;

		case "PDM_CI_SpawnJC_2":
			sld = CharacterFromID("James_Callow");
			ChangeCharacterAddressGroup(sld, "LaVega_tavern", "sit", "sit_base3");
			AddLandQuestMark_Main(sld, "PDM_Cursed_Idol");
			AddMapQuestMark_Major("LaVega_town", "PDM_Cursed_Idol", "");
		break;

		case "PDM_Callow_sadis_na_stul":
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "sit", "sit_front3");
			LAi_SetSitType(pchar);
			sld = CharacterFromID("James_Callow");
			LAi_SetSitType(sld);
			LAi_SetActorType(sld);
			LAi_ActorSetSitMode(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;

		case "PDM_Callow_vstaem":
			ChangeCharacterAddressGroup(pchar, "LaVega_tavern", "tables", "stay1");
			LAi_SetPlayerType(pchar);
		break;

		case "PDM_Callow_RodjerFin":
			sld = CharacterFromID("James_Callow");
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "CollowRad_1";
		break;

		case "PDM_Callow_RadPoka":
			sld = CharacterFromID("James_Callow");
			ChangeCharacterAddressGroup(sld, "LaVega_town", "none", "");
		break;

		case "PDM_FraOff_Bitva_1_Posle":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			sld = CharacterFromID("James_Callow");
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "CollowNeRad_1";
			AddLandQuestMark_Main(sld, "PDM_Cursed_Idol");
			SetTimerFunction("PDM_PI_Vernut_Gorod", 0, 0, 1);
			AddQuestRecord("PDM_Cursed_Idol", "6_5");
		break;

		case "PDM_Callow_poradomoy":
			sld = CharacterFromID("James_Callow");
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "Callow_POBEDA_1";
			AddLandQuestMark_Main(sld, "PDM_Cursed_Idol");
			AddQuestRecord("PDM_Cursed_Idol", "11");
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			LAi_LocationFightDisable(loadedLocation, true);

			sld = CharacterFromID("Tortuga_usurer");
			sld.dialog.filename = "Common_Usurer.c";
			sld.dialog.currentnode = "First time";
		break;

		case "Rostovshik_Mochilovo_3_1":
			sld = CharacterFromID("PDM_PI_Skel_Rostov");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
		break;

		case "PDM_PI_Skelety_on_Ship":
			pchar.quest.Munity = "";
			pchar.GenQuest.MunityStart = true;

			StartQuestMovie(true, true, true);
			locCameraFromToPos(-3.20, 7.00, -3.40, false, 20.00, -4.00, -25.00);

			string ani;
			sTemp = LAi_GetBoardingModel(pchar, &ani);
			sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Matrosiki_10", sTemp, "man", ani, sti(pchar.rank), PIRATE, -1, true));
			ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
			sld.name = UpperFirst(XI_ConvertString("sailor1"));
			sld.lastname = "";
			LAi_SetActorType(sld);
			sld.dialog.filename = "Quest\PDM\Cursed_Idol.c";
			sld.dialog.currentnode = "Matros_preduprejdaet";
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			for (i = 6; i <= 9; i++)
			{
				sTemp = LAi_GetBoardingModel(pchar, &ani);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_Matrosiki_" + i, sTemp, "man", ani, sti(pchar.rank), PIRATE, -1, true));
				PlaceCharacter(sld, "goto", "random");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "goto", "goto2", "", -1);
			DoQuestCheckDelay("PDM_PI_Skelety_on_Ship_2", 3.0);
		break;

		case "PDM_PI_Skelety_on_Ship_2":
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("PDM_PI_Matrosiki_10");
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		break;

		case "PDM_PI_Skelety_on_Ship_3":
			EndQuestMovie();

			//DoQuestFunctionDelay("PDM_PI_Vykl_Music", 1.0);
			InterfaceStates.Buttons.Save.enable = 1;
			LAi_SetFightMode(Pchar, true);
			Log_SetStringToLog(StringFromKey("InfoMessages_59"));
			//Скелеты
			for (i = 1; i <= 6; i++)
			{
				sTemp = "skel" + (rand(3) + 1);
				sld = GetCharacter(NPC_GenerateCharacter("PDM_PI_skel_" + i, sTemp, "skeleton", "man", sti(pchar.rank), PIRATE, -1, true));
				sld.skeleton = "1";
				PlaceCharacter(sld, "goto", "random_free");
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				sld.SaveItemsForDead = true;
				sld.DontChangeBlade = true;
				DeleteAttribute(sld, "items");
				AddMoneyToCharacter(sld, 66);
				AddItems(sld, "mineral6", rand(100) - 60);
				AddItems(sld, "mineral10", rand(15) - 8);
			}
			ChangeCrewExp(PChar, "Soldiers", 2); // бонус на подавление
			LAi_group_SetHearRadius("EnemyFight", 100.0);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);

			LAi_group_SetCheck("EnemyFight", "PDM_PI_Dead_Skelety");
		break;

		case "PDM_PI_Dead_Skelety":
			Log_SetStringToLog(StringFromKey("InfoMessages_60"));
			if (pchar.rank >= 1 && pchar.rank <= 6) AddCharacterCrew(pchar, -10);
			if (pchar.rank >= 7 && pchar.rank <= 12) AddCharacterCrew(pchar, -25);
			if (pchar.rank >= 13 && pchar.rank <= 18) AddCharacterCrew(pchar, -50);
			if (pchar.rank >= 19) AddCharacterCrew(pchar, -100);
			InterfaceStates.Buttons.Save.enable = 1;
			pchar.quest.Munity = "Deads";
			LAi_SetFightMode(Pchar, false);
			SetTimerFunction("PDM_PI_Skelety_v_more", 0, 0, 20);
		break;

		case "PDM_Callow_Voina":
			sld = CharacterFromID("James_Callow");
			FantomMakeCoolFighter(sld, sti(pchar.rank), 25, 25, "blade34", "", 100);
			FantomMakeCoolSailor(sld, SHIP_SCHOONER_W, FindPersonalName("James_Callow_ship"), CANNON_TYPE_CULVERINE_LBS12, 50, 55, 45);
			realships[sti(sld.ship.type)].HP = 9000;
			sld.ship.HP = 9000;
			sld.name = FindPersonalName("James_Callow_name");
			sld.lastname = FindPersonalName("James_Callow_lastname");
			LAi_SetImmortal(sld, false);
			sld.SinkTenPercent = true;
			sld.AlwaysSandbankManeuver = true;
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			sld.AnalizeShips = true;
			sld.DontRansackCaptain = true;
			sld.AlwaysEnemy = true;
			sld.Abordage.Enable = false;
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "SwordplayProfessional");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Sliding");
			sld.ship.Crew.Morale = 80;

			Group_FindOrCreateGroup("Nui");                    //Название группы
			Group_SetType("Nui", "war");                        //Тип поведения
			Group_AddCharacter("Nui", "James_Callow");    //Добавить капитана
			Group_SetGroupCommander("Nui", "James_Callow");
			Group_SetTaskAttack("Nui", PLAYER_GROUP);
			Group_SetPursuitGroup("Nui", PLAYER_GROUP);
			Group_SetAddress("Nui", "Hispaniola1", "", "");
			Group_LockTask("Nui");

			pchar.quest.PDM_Pobeda_nad_Callow.win_condition.l1 = "NPC_Death";
			pchar.quest.PDM_Pobeda_nad_Callow.win_condition.l1.character = "James_Callow";
			pchar.quest.PDM_Pobeda_nad_Callow.win_condition = "PDM_Pobeda_nad_Callow";
			PChar.quest.PDM_NEPobeda_nad_Callow.win_condition.l1 = "MapEnter";
			PChar.quest.PDM_NEPobeda_nad_Callow.win_condition = "PDM_NEPobeda_nad_Callow";

			DoQuestFunctionDelay("PDM_PI_Callow_na_dno", 50.0);
		break;

		case "PDM_Pobeda_nad_Callow":
			AddQuestRecord("PDM_Cursed_Idol", "8");
			CloseQuestHeader("PDM_Cursed_Idol");
			AddCharacterExpToSkill(PChar, "Leadership", 50);
			AddCharacterExpToSkill(PChar, "Sailing", 50);
			PChar.quest.PDM_NEPobeda_nad_Callow.over = "yes";
			Achievment_Set(ACH_Proklyatyy_idol);
		break;

		case "PDM_NEPobeda_nad_Callow":
			PChar.quest.PDM_Pobeda_nad_Callow.over = "yes";
			sld = CharacterFromID("James_Callow");
			Group_SetAddress("Nui", "none", "", "");
			LAi_KillCharacter(sld);
			AddCharacterExpToSkill(PChar, "Leadership", -50);
			AddQuestRecord("PDM_Cursed_Idol", "9");
			AddQuestUserData("PDM_Cursed_Idol", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("PDM_Cursed_Idol");
			Achievment_Set(ACH_Proklyatyy_idol);
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Проклятый Идол" конец				<===
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Тичингиту" начало					===>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "TichingituFree":
			sld = characterFromId("Tichingitu");
			sld.dialog.currentnode = "Tichingitu_9";
			ChangeCharacterAddressGroup(sld, "BasTer_exittown", "rld", "aloc14"); // 170712
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
			RemoveAllCharacterItems(sld, true);
			GiveItem2Character(sld, "unarmed");
			EquipCharacterbyItem(sld, "unarmed"); // 151012
		break;

		////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Тичингиту" конец						<===
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Невыносимая жара" начало				===>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		case "PDM_PJ_Arest_0":
			sld = GetCharacter(NPC_GenerateCharacter("PDM_PJ_Strajnik_4", "sold_fra_4", "man", "man", 10, FRANCE, -1, true));
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.City = "FortFrance";
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "goto", "goto34");
			LAi_ActorGoToLocator(sld, "officers", "reloadPr1_1", "", -1);

			sld = GetCharacter(NPC_GenerateCharacter("PDM_PJ_Strajnik_3", "sold_fra_3", "man", "man", 10, FRANCE, -1, true));
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.City = "FortFrance";
			ChangeCharacterAddressGroup(sld, "FortFrance_town", "goto", "goto34");
			LAi_ActorGoToLocator(sld, "officers", "reloadPr1_3", "PDM_PJ_Arest_1_1", -1);

			sld = CharacterFromID("PDM_PJ_Strajnik_1");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetLoginTime(sld, 0.0, 24.0);
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			LAi_SetLoginTime(sld, 0.0, 24.0);

			StartQuestMovie(true, true, true);
			locCameraFromToPos(-35.50, 7.00, 25.00, true, -20.00, 0.00, 15.00);
		break;

		case "PDM_PJ_Arest_1":
			sld = CharacterFromID("PDM_PJ_Strajnik_3");
			LAi_ActorAnimation(sld, "barman_idle", "", 1.5);
			DoQuestCheckDelay("PDM_PJ_Arest_2", 1.5);
			DoQuestCheckDelay("PDM_PJ_Arest_1_2", 0.8);
			sld = CharacterFromID("PDM_PJ_Strajnik_4");
			LAi_ActorTurnToCharacter(sld, CharacterFromID("PDM_PJ_Strajnik_1"));
		break;

		case "PDM_PJ_Arest_1_1":
			locCameraFromToPos(-31.50, 6.00, 40.00, true, -20.00, 0.00, 0.00);
			DoQuestCheckDelay("PDM_PJ_Arest_1", 0.4);
		break;

		case "PDM_PJ_Arest_1_2":
			sld = CharacterFromID("PDM_PJ_Strajnik_1");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
            RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
		break;

		case "PDM_PJ_Arest_2":
			sld = CharacterFromID("PDM_PJ_Strajnik_1");
			// Основная ходьба
			sld.actions.forward_walk = "prison_walk";
			// Лестница вверх
			sld.actions.forward_walk_stairs_up = "prison_walk";
			// Лестница вниз
			sld.actions.forward_walk_stairs_down = "prison_walk";
			EndChangeCharacterActionsBlend(sld);

			LAi_ActorGoToLocator(sld, "reload", "reload6_back", "", -1);
			DoQuestCheckDelay("PDM_PJ_Arest_3", 1.0);
		break;

		case "PDM_PJ_Arest_3":
			sld = CharacterFromID("PDM_PJ_Strajnik_3");
			LAi_ActorGoToLocator(sld, "reload", "reload6_back", "", -1);
			sld = CharacterFromID("PDM_PJ_Strajnik_4");
			LAi_ActorGoToLocator(sld, "officers", "reload6_3", "", -1);
			DoQuestCheckDelay("PDM_PJ_Arest_4", 6.0);
		break;

		case "PDM_PJ_Arest_4":
			DoQuestReloadToLocation("FortFrance_Malta_Dungeon", "item", "item3", "PDM_PJ_Arest_5");
			EndQuestMovie();
		break;

		case "PDM_PJ_Arest_5":
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			if (sld.id != "none")
			{
				sld.greeting = "soldier_common";
				LAi_SetLoginTime(sld, 6.0, 21.99);
			}

			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			CloseQuestHeader("PDM_Proklyataya_Jara");
			AddQuestRecord("PDM_Proklyataya_Jara", "6");
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Sneak", 40);
			Achievment_Set(ACH_Proklyataya_zhara);
		break;

		case "PDM_PJ_Protrezvel":
			sld = CharacterFromID("PDM_PJ_Strajnik_1");
			sld.dialog.filename = "Common_Soldier.c";
			sld.dialog.currentnode = "First time";
			LAi_SetLoginTime(sld, 6.0, 21.99);
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.City = "FortFrance";
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Невыносимая жара" конец					<===
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Кольцо Жозефины Лодет" начало			===>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		case "PDM_PK_Ubita":
			AddQuestRecord("PDM_Poteryanoe_Koltso", "4");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "а"));
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("Josephine_Lodet");
			sld.dialog.currentnode = "Konets";
			AddLandQuestMark_Main(sld, "PDM_Poteryanoe_Koltso");

			AddCharacterExpToSkill(pchar, "FencingLight", 100);
			AddCharacterExpToSkill(pchar, "Fencing", 100);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 100);
			ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, SPAIN, -7);
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Потерянное кольцо" конец				<===
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Непутёвый Казначей" начало			===>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		case "PDM_NK_Nachalo":
			sld = GetCharacter(NPC_GenerateCharacter("Andreas_Fickler", "Fickler", "man", "man", 10, HOLLAND, -1, false));
			sld.name = FindPersonalName("Andreas_Fickler_name");
			sld.lastname = FindPersonalName("Andreas_Fickler_lastname");
			sld.City = "Villemstad";
			sld.Dialog.Filename = "Quest\PDM\Neputyovy_kaznachey.c";
			LAi_SetCitizenType(sld);
			LAi_SetLoginTime(sld, 6.0, 21.99);
			sld.talker = 5;
			//черты
			SetCharacterPerk(sld, "LoyalOff");
			SetCharacterPerk(sld, "Honest");
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
			ChangeCharacterAddressGroup(sld, "Villemstad_town", "sit", "sit_front2");
			LAi_SetSitType(sld);
            AddLandQuestMark_Main(sld, "PDM_Neputyovy_kaznachey");
            AddMapQuestMark_Major("Villemstad_town", "PDM_Neputyovy_kaznachey", "");
		break;

		case "PDM_NK_Viktor":
			AddCharacterExpToSkill(pchar, "FencingLight", 120);
			AddCharacterExpToSkill(pchar, "Fencing", 120);
			AddCharacterExpToSkill(pchar, "FencingHeavy", 120);
			AddCharacterExpToSkill(pchar, "Pistol", 120);

			AddQuestRecord("PDM_Neputyovy_kaznachey", "4");

			sld = CharacterFromID("Andreas_Fickler");
			sld.dialog.filename = "Quest\PDM\Neputyovy_kaznachey.c";
			sld.dialog.currentnode = "Fickler_11";
			AddLandQuestMark_Main(sld, "PDM_Neputyovy_kaznachey");
		break;

		case "PDM_NK_Litsenzia":
			if (GetDaysContinueNationLicence(HOLLAND) < 15) GiveNationLicence(HOLLAND, 15);
			if (GetDaysContinueNationLicence(SPAIN) < 15) GiveNationLicence(SPAIN, 15);
			if (GetDaysContinueNationLicence(ENGLAND) < 15) GiveNationLicence(ENGLAND, 15);
			if (GetDaysContinueNationLicence(FRANCE) < 15) GiveNationLicence(FRANCE, 15);
			TakeItemFromCharacter(pchar, "Litsenzia");
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Непутёвый Казначей" конец			<===
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Клан Ламбрини" начало				===>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PDM_CL_OnShore_7":
			PDM_CL_OnShore_7();
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Клан Ламбрини" конец				<===
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Вызволение из плена мужа горожанки" начало	===>
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		case "SCQ_PirateFashion_afterCabinFight":
			sld = GetCharacter(NPC_GenerateCharacter("QuetionsPortPax_MuzhPassajir", "LabbeVincent", "man", "man", 3, FRANCE, -1, false));
			sld.name = FindPersonalName("QuetionsPortPax_MuzhPassajir_name");
			sld.lastname = FindPersonalName("QuetionsPortPax_MuzhPassajir_lastname");
			sld.dialog.filename = "Quest\Questions.c";
			sld.dialog.currentnode = "PirateFashion_Board";
			LAi_SetStayType(sld);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(sld, pchar.location, "rld", LAi_FindFarLocator("rld", locx, locy, locz));
			LAi_SetActorType(pchar);
			LAi_SetActorType(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", -1);
		break;

		case "SCQ_PirateFashion_Potunul":
			AddQuestRecord("SCQ_PirateFashion", "2");
			CloseQuestHeader("SCQ_PirateFashion");
			sld = characterFromId("QuetionsPortPax");
			sld.lifeday = 0;
		break;

		case "SCQ_PirateFashion_Nashli":
			AddQuestRecord("SCQ_PirateFashion", "3");
		break;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Квест "Вызволение из плена мужа горожанки" конец	<===
		/////////////////////////////////////////////////////////////////////////////////////////////////////////

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Возвращение корабела
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "ShipyardExitFromLocation":
			sld = characterFromId(PChar.questTemp.ShipyardExitFromLocation.shipyard);
			ChangeCharacterAddressGroup(sld, "None", "", "");
		break;

		case "ShipyardRefreshInLocation":
			LAi_LocationFightDisable(&locations[FindLocation(PChar.questTemp.ShipyardExitFromLocation.location)], true);
			sld = characterFromId(PChar.questTemp.ShipyardExitFromLocation.shipyard);
			LAi_SetHuberType(sld);
			ChangeCharacterAddressGroup(sld, PChar.questTemp.ShipyardExitFromLocation.location, "sit", "sit1");
			DeleteAttribute(PChar, "questTemp.ShipyardExitFromLocation");
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	RPG Опции (Rosarak)
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "Duglas_Officer":
			ref rDouglas = CharacterFromID("Douglas");
			DeleteAttribute(rDouglas, "DontChangeGun");
			SetCharacterToMushketer(rDouglas, "mushket2x2");
			bOk = false;
			for (i = 1; i < 4; i++)
			{
				if (GetCharacterIndex("Douglas") == GetOfficersIndex(pchar, i)) bOk = true;
			}
			if (bOk)
			{
				LAi_SetOfficerType(rDouglas);
				LAi_tmpl_SetFollow(rDouglas, GetMainCharacter(), -1.0);
			}
			else LAi_SetCitizenType(rDouglas);
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Задание Табак Малькольма
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "Malcolm_Fawn_is_death":
			AddQuestRecord("MalcolmsTobacco", "2");
			CloseQuestHeader("MalcolmsTobacco");
			if (CheckAttribute(pchar, "quest.MalcolmsTobacco"))
			{
			    pchar.quest.MalcolmsTobacco.over = "yes";
			}
			DeleteAttribute(pchar, "GenQuest.Hunter2Pause");
		break;
		case "MalcolmTobacco_GoToStore":
			DoQuestReloadToLocation("PuertoPrincipe_store", "reload", "reload1", "pchar_back_to_player");
			sld = characterFromID("PuertoPrincipe_trader");
			sld.quest.MalcolmTobacco = true;
	        AddLandQuestMark_Main(sld, "MalcolmsTobacco");
		break;
		case "MalcolmTobacco_GoFromStore":
			DoQuestReloadToLocation("PuertoPrincipe_town", "reload", "reload8", "pchar_back_to_player");
		break;
		case "MalcolmShoreGangDialog":
			SetMainCharacterIndex(1);
			pchar = GetMainCharacter();
			LAi_SetPlayerType(pchar);
			locCameraTarget(pchar);
			locCameraFollow();
			EndQuestMovie();
			InterfaceStates.Buttons.Save.enable = true;
			bDisableCharacterMenu = false;
			sld = CharacterFromID("MalcolmFawn");
			if (CheckAttribute(sld, "quest.MalcolmsTobacco.moneyback")) DoQuestFunctionDelay("MalcolmBackToPchar", 2.0);
			else DoQuestFunctionDelay("MalcolmBattleInShore", 2.0);
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Задание церкви. Очистить подземелье от нечисти
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "Church_ClearGhost":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			AddQuestRecordEx(pchar.questTemp.GhostType.title + "Church_DestroyGhost", "Church_DestroyGhost", "6");
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	Серия миниквестов "Дело чести"
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "CoatHonor_Login":
			iTemp = GetCityNation(PChar.QuestTemp.AffairOfHonor.CoatHonor.CityId);
			npchar = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_CoatHonor_Man", "officer_5", "man", "man", rand(10) + 4, iTemp, 3, true));
			CreateModel(sti(npchar.index), "urban_off", MAN);
			Characters_RefreshModel(npchar); // Jason: рефрешить модель обязательно
			// Jason: дохляки нам не нужны - делаем кулфайтера
			iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 10;
			int Scl = 35 + 2 * sti(pchar.rank);
			FantomMakeCoolFighter(npchar, iRank, Scl, Scl, RandPhraseSimple("blade12", "blade15"), RandPhraseSimple("pistol6", "pistol5"), Scl * 3); //TODO weapon
			float Mft = MOD_SKILL_ENEMY_RATE / 20;
			npchar.MultiFighter = 1.0 + Mft; // мультифайтер
			npchar.dialog.filename = "Quest\ForAll_dialog.c";
			npchar.dialog.currentnode = "AffairOfHonor_CoatHonor_4";
			LAi_SetWarriorType(npchar);
			LAi_SetImmortal(npchar, true);
			PlaceCharacter(npchar, "goto", "random");
		break;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		////	ситизены
		/////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "FollowDone":
			if (LAi_grp_playeralarm == 0)
			{
				sld = characterFromId(TEV.CitizenHelpRoutes.follower);
				if (LAi_CharacterSeesThePchar(sld, 20)) LAi_ActorDialogNow(sld, pchar, "", -1);
				else NormalizeRoutedCitizen("");
			}
			else NormalizeRoutedCitizen("");
		break;

		case "TeleportNpcForced":
			//HardCoffee заставить нпс переместится в локацию, даже если он уже в ней находится
			//Используется совместно с атрибутом TeleportNpc
			TeleportNpcToLocation();
		break;

		case "CrackPinctados": //HardCoffee открывашка жемчужниц
			iTemp = sti(TEV.CrackPinctadosSmall);
			iCount = sti(TEV.CrackPinctadosBig);
			TakeNItemsNotification(pchar, "jewelry12", iTemp, StringFromKey("InfoMessages_248", iTemp), "SmallPearl", "noSound");
			TakeNItemsNotification(pchar, "jewelry11", iCount, StringFromKey("InfoMessages_249", iCount), "BigPearl", "Important_item");
			DeleteAttribute(&TEV, "CrackPinctadosSmall");
			DeleteAttribute(&TEV, "CrackPinctadosBig");
		break;
	}
}

void FrameAscoldVodka()
{
	WaitDate("", 0, 0, 0, 5, 5);
	LAi_SetAlcoholState(2);
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_22"), "Reload_To_Location", 0.1, 2.0);
	SetLaunchFrameReloadLocationParam("BasTer_houseSp1", "barmen", "bar1", "");
	LaunchFrameForm();
}

// boal -->
////////////////////////   общие методы //////////////////////////
void SetActorDialogAny2Pchar(string _charId, string _doQuest, float time1, float time2)
{
	Pchar.AutoQuest.NPCharId = _charId;
	Pchar.AutoQuest.Quest = _doQuest;
	Pchar.AutoQuest.Time1 = time1;
	Pchar.AutoQuest.Time2 = time2;
}

//для универсализации (navy 17.10.05)
//уcтановки для телепорта ГГ в любую локацию с задержкой или без.
//Для отложенного вызова напр. AddDialogExitQuest()
void SetAnyReloadToLocation(string idLocation, string idGroup, string idLocator, string questName, int delayMonth, int delayDay, int delayHour, int delayMin)
{
	ref PChar = GetMainCharacter();

	PChar.AutoQuest.delayMonth = delayMonth;
	PChar.AutoQuest.delayDay = delayDay;
	PChar.AutoQuest.delayHour = delayHour;
	PChar.AutoQuest.delayMin = delayMin;

	PChar.AutoQuest.idLocation = idLocation;
	PChar.AutoQuest.idGroup = idGroup;
	PChar.AutoQuest.idLocator = idLocator;
	PChar.AutoQuest.questName = questName;
}

// Инициация таблички В это время на Беде  -->
// _FrameText - текст  Перенос строки делать "текст"+ NewStr() +"текст"
// _FrameQuest - квест после завершения таблички, если == "Reload_To_Location" см. SetLaunchFrameReloadLocationParam
// если же будет == "Run_Function" см. SetLaunchFrameRunFunctionParam
// _delay - время в с. отложения вызова таблички (нужно для неконфликта с заставкой загрузки локаций, где-то 0.1-1.5с)
// _autoEnd - время в с. автозавершения показа таблички, 4-6с на фразу
void SetLaunchFrameFormParam(string _FrameText, string _FrameQuest, float _delay, float _autoEnd)
{
	pchar.AutoQuest.FrameText = _FrameText;
	pchar.AutoQuest.FrameQuest = _FrameQuest;
	pchar.AutoQuest.FrameDelay = _delay;
	pchar.AutoQuest.FrameAutoEnd = _autoEnd;
}

void SetLaunchFrameFormPic(string _FramePic)
{
	pchar.AutoQuest.FramePic = _FramePic;
}
// метод для инициации перехода после таблички
void SetLaunchFrameReloadLocationParam(string idLocation, string idGroup, string idLocator, string questName)
{
	pchar.AutoQuest.FrameLocation = idLocation;
	pchar.AutoQuest.FrameGroup = idGroup;
	pchar.AutoQuest.FrameLocator = idLocator;
	pchar.AutoQuest.FrameLocationQuest = questName;
}
// метод для вызова метода из кода после таблички _func - метод, _delay - задержка вызова метода после таблички в с.
void SetLaunchFrameRunFunctionParam(string _func, float _delay)
{
	pchar.AutoQuest.FrameFunction = _func;
	pchar.AutoQuest.FrameFunctionDelay = _delay;
}
// Инициация таблички В это время на Беде  <--

void WaitNextHours(string qName)
{
	bool bTime = IsDay();
	string sHour;
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	pchar.locx = locx;
	pchar.locy = locy;
	pchar.locz = locz;
	sHour = StringFromKey("InfoMessages_23");
	if (sti(TEV.WaitHours) == 1)    sHour = StringFromKey("InfoMessages_14");
	if (sti(TEV.WaitHours) == 24)    sHour = StringFromKey("InfoMessages_24");
	if (isShipInside(pchar.location))
	{
		SetLaunchFrameFormParam(sHour, "", 0.1, 2.0);
	}
	else
	{
		SetLaunchFrameFormParam(sHour, "Reload_To_Location", 0.1, 2.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
	}

	WaitDate("", 0, 0, 0, sti(TEV.WaitHours), 0);

	if (bTime == IsDay())
		TEV.Music.ForceKeepPlaying = "";

	//ожидание снимает алкоголь... 2 часа = кружка
	LAi_DawnWaitAlcoholState(sti(TEV.WaitHours) * 900);

	LaunchFrameForm();
	DeleteAttribute(&TEV, "WaitHours");
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

void RemovePatent()
{
	RemoveCharacterEquip(pchar, "patent");
	if (CheckCharacterItem(Pchar, "patent_eng"))
	{
		TakeItemFromCharacter(pchar, "patent_eng");
		ChangeCharacterReputation(pchar, -10);
	}
	if (CheckCharacterItem(Pchar, "patent_fra"))
	{
		TakeItemFromCharacter(pchar, "patent_fra");
		ChangeCharacterReputation(pchar, -10);
	}
	if (CheckCharacterItem(Pchar, "patent_spa"))
	{
		TakeItemFromCharacter(pchar, "patent_spa");
		ChangeCharacterReputation(pchar, -10);
	}
	if (CheckCharacterItem(Pchar, "patent_hol"))
	{
		TakeItemFromCharacter(pchar, "patent_hol");
		ChangeCharacterReputation(pchar, -10);
	}
}

void StartActorSelfDialog(string _CurrentNode)
{
	LAi_SetActorType(pchar);
	LAi_CharacterSaveAy(pchar);
	locCameraSleep(true);
	if (stf(pchar.chr_ai.type.ay) > 0)
	{
		CharacterTurnAy(pchar, -PI + abs(stf(pchar.chr_ai.type.ay)));  // 180 == 1
	}
	else
	{
		CharacterTurnAy(pchar, PI - abs(stf(pchar.chr_ai.type.ay)));  // 180 == 1
	}
	pchar.Dialog.CurrentNode = _CurrentNode;
	LAi_ActorSelfDialog(pchar, "pchar_back_to_player");
}

// подъем флагов
void Flag_PIRATE()
{
	PChar.nation = PIRATE;
	Ship_FlagRefresh(PChar); //флаг на лету
	SetNationToOfficers(PIRATE);

	SetNationRelation2MainCharacter(ENGLAND, RELATION_ENEMY);
	SetNationRelation2MainCharacter(FRANCE, RELATION_ENEMY);
	SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);

	SetNationRelation2MainCharacter(PIRATE, RELATION_FRIEND);
	SetNationRelation2MainCharacter(HOLLAND, RELATION_ENEMY);

	LAi_group_SetRelation("PIRATE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//Relation_PIRATE_SOLDIERS();
	// капеллан
	//if (CheckAttribute(pchar, "questTemp.ShipCapellan.Yes")) ShipCapellan_Remove();

	LAi_group_ClearAllTargets();
	DoQuestCheckDelay("NationUpdate", 3.0);
	UpdateRelations();
	if (bSeaActive)
	{
		RefreshBattleInterface();
	}
	if (isEntity(&worldMap))
	{
		wdmSetNationFlag(sti(pchar.nation));
	}
}

void Flag_FRANCE()
{
	PChar.nation = FRANCE;
	Ship_FlagRefresh(PChar); //флаг на лету
	SetNationToOfficers(FRANCE);

	SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, FRANCE));
	SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
	SetNationRelation2MainCharacter(SPAIN, GetNationRelation(FRANCE, SPAIN));
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);

	SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(FRANCE, HOLLAND));

	LAi_group_SetRelation("FRANCE_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//Relation_FRANCE_SOLDIERS();
	LAi_group_ClearAllTargets();
	DoQuestCheckDelay("NationUpdate", 3.0);
	UpdateRelations();
	if (bSeaActive)
	{
		RefreshBattleInterface();
	}
	if (isEntity(&worldMap))
	{
		wdmSetNationFlag(sti(pchar.nation));
	}
}

void Flag_ENGLAND()
{
	PChar.nation = ENGLAND;
	Ship_FlagRefresh(PChar); //флаг на лету
	SetNationToOfficers(ENGLAND);

	SetNationRelation2MainCharacter(ENGLAND, RELATION_FRIEND);
	SetNationRelation2MainCharacter(FRANCE, GetNationRelation(ENGLAND, FRANCE));
	SetNationRelation2MainCharacter(SPAIN, GetNationRelation(ENGLAND, SPAIN));
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
	SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(ENGLAND, HOLLAND));

	LAi_group_SetRelation("ENGLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//Relation_ENGLAND_SOLDIERS();
	LAi_group_ClearAllTargets();
	DoQuestCheckDelay("NationUpdate", 3.0);
	UpdateRelations();
	if (bSeaActive)
	{
		RefreshBattleInterface();
	}
	if (isEntity(&worldMap))
	{
		wdmSetNationFlag(sti(pchar.nation));
	}
}

void Flag_SPAIN()
{
	PChar.nation = SPAIN;
	Ship_FlagRefresh(PChar); //флаг на лету
	SetNationToOfficers(SPAIN);

	SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, SPAIN));
	SetNationRelation2MainCharacter(FRANCE, GetNationRelation(FRANCE, SPAIN));
	SetNationRelation2MainCharacter(SPAIN, RELATION_FRIEND);
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
	SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(SPAIN, HOLLAND));

	LAi_group_SetRelation("SPAIN_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//Relation_SPAIN_SOLDIERS();
	LAi_group_ClearAllTargets();
	DoQuestCheckDelay("NationUpdate", 3.0);
	UpdateRelations();
	if (bSeaActive)
	{
		RefreshBattleInterface();
	}
	if (isEntity(&worldMap))
	{
		wdmSetNationFlag(sti(pchar.nation));
	}
}

void Flag_HOLLAND()
{
	PChar.nation = HOLLAND;
	Ship_FlagRefresh(PChar); //флаг на лету
	SetNationToOfficers(HOLLAND);

	SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(ENGLAND, HOLLAND));
	SetNationRelation2MainCharacter(FRANCE, GetNationRelation(FRANCE, HOLLAND));
	SetNationRelation2MainCharacter(SPAIN, GetNationRelation(SPAIN, HOLLAND));
	SetNationRelation2MainCharacter(PIRATE, RELATION_ENEMY);
	SetNationRelation2MainCharacter(HOLLAND, RELATION_FRIEND);

	LAi_group_SetRelation("HOLLAND_CITIZENS", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	//Relation_HOLLAND_SOLDIERS();
	LAi_group_ClearAllTargets();
	DoQuestCheckDelay("NationUpdate", 3.0);
	UpdateRelations();
	if (bSeaActive)
	{
		RefreshBattleInterface();
	}
	if (isEntity(&worldMap))
	{
		wdmSetNationFlag(sti(pchar.nation));
	}
}

void Flag_Rerise()
{
	switch (sti(PChar.nation))
	{
		case ENGLAND:    Flag_ENGLAND();    break;
		case FRANCE:    Flag_FRANCE();      break;
		case SPAIN:        Flag_SPAIN();    break;
		case PIRATE:    Flag_PIRATE();      break;
		case HOLLAND:    Flag_HOLLAND();    break;
	}
}

//Sith проматывание дней
void WaitNextDays(string qName)
{
	bool bTime = IsDay();
	string sDay;
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	pchar.locx = locx;
	pchar.locy = locy;
	pchar.locz = locz;
	sDay = StringFromKey("InfoMessages_219");
	if (sti(TEV.WaitHours) == 1)
		sDay = StringFromKey("InfoMessages_24");
	if (isShipInside(pchar.location))
	{
		SetLaunchFrameFormParam(sDay, "", 0.1, 2.0);
	}
	else
	{
		SetLaunchFrameFormParam(sDay, "Reload_To_Location", 0.1, 2.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
	}
	for (int i = 0; i < sti(TEV.WaitHours); i++)
		WaitDate("", 0, 0, 1, 0, 0);

	if (bTime == IsDay())
		TEV.Music.ForceKeepPlaying = "";

	LAi_DawnWaitAlcoholState(sti(TEV.WaitHours) * 21600);
	LaunchFrameForm();
	DeleteAttribute(&TEV, "WaitHours");
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}

//проматывание минут
void WaitNextMinutes(string qName)
{
	bool bTime = IsDay();
	string sMin;
	float locx, locy, locz;
	GetCharacterPos(pchar, &locx, &locy, &locz);
	pchar.locx = locx;
	pchar.locy = locy;
	pchar.locz = locz;
	sMin = StringFromKey("InfoMessages_220");
	if (sti(TEV.WaitHours) == 60) sMin = StringFromKey("InfoMessages_14");
	if (isShipInside(pchar.location))
	{
		SetLaunchFrameFormParam(sMin, "", 0.1, 2.0);
	}
	else
	{
		SetLaunchFrameFormParam(sMin, "Reload_To_Location", 0.1, 2.0);
		SetLaunchFrameReloadLocationParam(pchar.location, "goto", LAi_FindNearestFreeLocator2Pchar("goto"), "LocTeleport");
	}

	WaitDate("", 0, 0, 0, 0, sti(TEV.WaitHours));

	if (bTime == IsDay())
		TEV.Music.ForceKeepPlaying = "";

	//ожидание снимает алкоголь... 2 часа = кружка
	LAi_DawnWaitAlcoholState(sti(TEV.WaitHours) * 15);

	LaunchFrameForm();
	DeleteAttribute(&TEV, "WaitHours");
	RefreshLandTime();
	RecalculateJumpTable();
	Whr_UpdateWeather();
}
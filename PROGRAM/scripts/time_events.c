void ActivateTimeEvents()
{

}

//////////////////////// boal SLiB ////////////////////////////////
void SalaryNextDayUpdate()
{
	if (sti(NullCharacter.SalayPayMonth) != GetDataMonth() && !bDisableMapEnter) // boal
	{
		// проверка на наличие кому платить -->
		int nPaymentQ = 0;
		int i, cn;
		ref chref;

		for (i = 0; i < COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(pchar, i);
			if (cn >= 0)
			{
				chref = GetCharacter(cn);
				if (GetRemovable(chref)) // считаем только своих, а то вских сопровождаемых кормить!!!
				{
					nPaymentQ += GetSalaryForShip(chref);
				}
			}
		}

		// проверка на наличие кому платить <--
		NullCharacter.SalayPayMonth = GetDataMonth(); // boal
		// в туториале Блада - плата не берётся
		if(GetGlobalTutor()) return;

		if (nPaymentQ > 0)
		{
			if (CheckAttribute(pchar,"CrewPayment"))
			{
				nPaymentQ += makeint(pchar.CrewPayment); // а тут помним все до копейки!
			}
			if (CheckAttribute(pchar,"Partition.MonthPart"))
			{
				nPaymentQ += makeint(pchar.Partition.MonthPart); // доля за месяц
				DeleteAttribute(pchar,"Partition.MonthPart");
			}

			pchar.CrewPayment = nPaymentQ;
			LaunchMoneyGraphCollect();

			if (!dialogRun && !bQuestCheckProcessFreeze && !bAbordageStarted && !bIsRepairingProcess) // можно показать
			{
				LaunchSalaryScreen("");
			}
			else
			{
				Pchar.quest.LaunchSalaryScreen.win_condition.l1 = "MapEnter";
				PChar.quest.LaunchSalaryScreen.function         = "LaunchSalaryScreen";
			}
		}
	}
}

#event_handler("EvSituationsUpdate","WorldSituationsUpdate");
void WorldSituationsUpdate()
{
	int iStep = GetEventData();
	int i;

	switch(iStep)
	{
		case 0:
			g_sDayRand = Rand(32768); //TODO: избавиться от dRandEx
			//HardCoffee перевод dRandEx на idRand
			string sTemp;
			TEV.dRandEx.last = "0";
			for (i = 1; i < 11; i++)
			{
				sTemp = i;
				TEV.dRandEx.(sTemp) = Rand(32768);
			}
			DeleteAttribute(pchar, "SkipEshipIndex");// boal
			ChangeMoraleDueToDebt(false); //долги с предыдущего месяца
			Log_QuestInfo("WorldSituationsUpdate DailyEatCrewUpdate");
		break;
		
		case 1:
		    Whr_RainGenerator(); //генератор дождей
			DailyEatCrewUpdate(); // boal
			//Jason: еженедельное обновление паролей кланов LSC и ежедневное вытирание
			if (CheckAttribute(pchar, "questTemp.LSC.CasperParol"))
			{
				if (GetDataDay() == 7 || GetDataDay() == 14 || GetDataDay() == 21 || GetDataDay() == 28)
				{
					pchar.questTemp.LSC.CasperParol = UpdateLSCClanParol();
					pchar.questTemp.LSC.NarvalParol = UpdateLSCClanParol();
					if (CheckAttribute(pchar, "questTemp.LSC.NParol_bye")) DeleteAttribute(pchar, "questTemp.LSC.NParol_bye");
					if (CheckAttribute(pchar, "questTemp.LSC.CParol_bye")) DeleteAttribute(pchar, "questTemp.LSC.CParol_bye");
				}
				if (CheckAttribute(pchar, "questTemp.LSC.parol_nrv")) DeleteAttribute(pchar, "questTemp.LSC.parol_nrv");
				if (CheckAttribute(pchar, "questTemp.LSC.parol_cpr")) DeleteAttribute(pchar, "questTemp.LSC.parol_cpr");
			}
			Log_QuestInfo("WorldSituationsUpdate SalaryNextDayUpdate");
			
			// evganat - пасха
			EasterCheckGodDay();
			// проверка ачивок
			CheckAchievments();
		break;
		
		case 2:
			// ушло в переходы локаций PGG_DailyUpdate(); // navy
			SalaryNextDayUpdate();
			ProcessDayRepair();
		break;
		
		case 3:
			//UpdateDisease();
			Group_FreeAllDead();
		break;
		
		case 4:
			QuestActions(); //eddy
		break;
		
		case 5:
			//UpdateColonyProfit();  
			wdmEmptyAllOldEncounter();// homo чистка энкоутеров
		break;
		
		case 6:
			UpdateCrewExp(); // изменение опыта команды
		break;
		
		case 7:
			UpdateCrewInColonies(); // пересчет наёмников в городах
		break;
		
		case 8:
			if (IsEntity(&worldMap))
			{
				EmptyAllFantomCharacter(); // трем НПС
				wdmEmptyAllDeadQuestEncounter();
			}
		break;
		
		case 9:
			UpdateFame(); // это теперь известность репутации
			GenerateRumour(); //homo 05/07/06
		break;
		
		case 10:
			DailyStoreMoneyUpdate();
			DeleteAttributeEx(&TEV, "SkladManIsDead,ArtOfDeals,BlindGuards");
			if (CheckAttribute(&TEV, "SecretFortUnlocked") && GetEventPastTime("CreateSecretFortNPC", "day") > (7 + rand(3)) && !StrStartsWith(pchar.location, "Secret_Fort"))
				CreateSecretFortNPC();
		break;
	}

	iStep++;
	InterfaceStates.WorldSituationUpdateStep = iStep;

	if(iStep <= 10)
	{
		PostEvent("EvSituationsUpdate", 1000, "l", iStep);
	}
}


//////////////////////////////// начало игры - туториал ////////////////////////////////
void Tut_StartGame(string sQuest)
{
	InterfaceStates.Buttons.Save.enable = false;
	StartQuestMovie(true, true, true);
	SetCharacterTask_None(GetMainCharacter());
	LAi_LockFightMode(Pchar, true);
	PChar.GenQuest.CallFunctionParam = "Tut_Continue";
	DoQuestCheckDelay("CallFunctionParam", 5.0);
	LAi_LocationFightDisable(loadedLocation, true);
	InterfaceStates.Buttons.Save.enable = false;
	DoQuestFunctionDelay("Tut_locCamera_1", 0.1);
}

void Tut_locCamera_1(string _tmp)
{
	locCameraToPos(-5, 2.5, 5.6, false);
	ChangeShowIntarface();
	LAi_SetActorType(pchar);
}

void Tut_Continue()
{
    ref sld;
    LAi_LocationFightDisable(loadedLocation, false);
    LAi_SetFightMode(Pchar, false);
    LAi_LockFightMode(pchar, true);
    
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_1", "Sandro_Thorne", "man", "man", 1, PIRATE, 0, false)); //стартовый Сандро Торн
    sld.name 	= FindPersonalName("BlueBirdCapitain_name");
    sld.lastname 	= FindPersonalName("BlueBirdCapitain_lastname");
    sld.Dialog.CurrentNode = "First time";
    sld.dialog.filename = "Quest\StartGame_dialog.c";
    sld.greeting = "Teacher_pirat";

    SetSPECIAL(sld, 9,8,10,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_1");
    GiveItem2Character(sld, "blade1");
	EquipCharacterByItem(sld, "blade1");
	// пустоля нет, лечилок нет
    ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
    LAi_SetActorType(sld);
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "pchar_back_to_player", 5.0, 0);

	// генерим второго матроса, но пока не ставим
	sld = GetCharacter(NPC_GenerateCharacter("Sailor_2", "shipowner_1", "man", "man", 1, PIRATE, 0, false)); //TODO: уникальную
    sld.name 	= FindPersonalName("Sailor_name");
    sld.lastname 	= FindPersonalName("Sailor_lastname");

    SetSPECIAL(sld, 8,10,9,3,6,10,4);
    InitStartParam(sld);
    SetEnergyToCharacter(sld);

    LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_2");
    GiveItem2Character(sld, "blade4");
	EquipCharacterByItem(sld, "blade4");
	GiveItem2Character(sld, "pistol2");
	EquipCharacterByItem(sld, "pistol2");
	TakeNItems(sld, "bullet", 30);
	AddItems(sld, "GunPowder", 30);
	// лечилок нет
    sld.location = "Ship_deck_Low";  // чтоб не терся, пока его нет
	//раскидаем квестовых нпс по локациям
	SetQuestsCharacters();

	SetTutorials_SandBox_TutDeck();
	SetFunctionExitFromLocationCondition("Tutorial_CameraControl_Delay", pchar.location, false); // Запуск туториала в порту
//	LaunchInfoMessage(0); // сообщение общий привет
}

void Tut_RestoreState()
{
	ref sld;
	
	pchar.Health.Damg = 0.0; // здоровье бережем
	pchar.Health.weekDamg = 0.0;

	LAi_SetCurHPMax(pchar);
	LAi_SetCheckMinHP(pchar, 1, true, "Tut_StartGame_CheckMinHP_Hero");
	LAi_SetImmortal(pchar, false);

	for (int i = 1; i <= 2; i++)
	{
		sld = characterFromID("Sailor_" + i);
		LAi_SetCurHPMax(sld);
		LAi_SetCheckMinHP(sld, 1, true, "Tut_StartGame_CheckMinHP_" + i);
		LAi_SetImmortal(sld, false);
	}
	
	DeleteAttribute(pchar, "HeroParam.Teach_beat");
}

void Tut_TeachBattle()
{
	ref sld;
	
	LAi_SetPlayerType(pchar);
	LAi_SetFightMode(Pchar, true);
	sld = characterFromID("Sailor_1");
	LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, "TmpEnemy");

    // туториалы на палубе
	if (CheckAttribute(pchar, "HeroParam.Teach_battle_count"))
	{
		pchar.HeroParam.Teach_battle_count = sti(pchar.HeroParam.Teach_battle_count) + 1;
		if (sti(pchar.HeroParam.Teach_battle_count) == 1)
		{
			Tutorial_TutDeck_GuideFight("");
		}
		if (sti(pchar.HeroParam.Teach_battle_count) == 2)
		{
			Tutorial_TutDeck_LandTimeScaleDown("");
		}
	}
	
	if (sti(pchar.HeroParam.Teach_battle) == 2)
	{
        sld = characterFromID("Sailor_2");
		if (!IsEntity(sld))
        {
        	ChangeCharacterAddressGroup(sld, "Ship_deck_Low", "reload", "reload1");
        }
		LAi_SetWarriorType(sld);
	    LAi_group_MoveCharacter(sld, "TmpEnemy");
	}
	LAi_group_SetHearRadius("TmpEnemy", 100.0);
    LAi_group_FightGroupsEx("TmpEnemy", LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
    LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	
//	LaunchInfoMessage(1); // сообщение о шрапнели
}

void Tut_StartDialog()
{
	ref sld = CharacterFromID("Sailor_1");
	
	if (CheckAttribute(pchar, "HeroParam.Teach_beat"))
	{ // признак, что выиграл
		if (sti(pchar.HeroParam.Teach_beat) == 3)
		{
		    sld.Dialog.CurrentNode = "Teach_battle_win_2";
		}
		else
		{
			if (sti(pchar.HeroParam.Teach_battle) == 1)
			{
				sld.Dialog.CurrentNode = "Teach_battle_win";
			}
			else
			{
			    sld.Dialog.CurrentNode = "Teach_battle_win_3";
			}
		}
	}
	else
	{
		sld.Dialog.CurrentNode = "Teach_battle_lose";
	}
	LAi_ActorWaitDialog(pchar, sld);
	LAi_ActorDialog(sld, pchar, "", 4.0, 0);
}
//поставить НПС-раздатчиков квеста в нужные города по нации ГГ
void SetQuestsCharacters()
{
	//Удаляем лишние атрибуты из окна создания персонажа
	DeleteAttribute(&TEV, "hero_name");
	DeleteAttribute(&TEV, "hero_anim");
	
	ref sld;
	string sTown;
	int iNation = sti(pchar.nation);
	switch (iNation)
	{
		case 0: sTown = "PortRoyal"; break;
		case 1: sTown = "Tortuga";	break;
		case 2:	sTown = "Havana";	break;
		case 3:	sTown = "Villemstad"; break;
		case 4:	
			sTown = "PortRoyal";
			iNation = ENGLAND;
		break;
	}
	//заказчик убийства нищих
	sld = characterFromId("PoorKillSponsor");
	sld.nation = iNation;
	sld.city = sTown;
	sld.location = sTown + "_town";
	sld.location.group = "goto";
	sld.location.locator = "goto2";
	LAi_group_MoveCharacter(sld, GetNationNameByType(iNation) + "_citizens");
	AddMapQuestMark_Major(sld.location, "ISS_PoorsMurder", "ISS_PoorsMurder_Begin_WDMQuestMarkCondition");
}

void DailyStoreMoneyUpdate() //HardCoffee ежедневное обновление бабла в магазинах
{
	int i;
	ref rMerch;
	for (i = 0; i < STORE_QUANTITY; i++) //обновить магазины и контрабандистов
	{
		//у торговцев в море своё бабло, в Fantom_SetRandomMoney
		rMerch = &Stores[i];
		switch (rMerch.StoreSize)
		{
			case "large":
				rMerch.money =			STORE_MIN_MONEY + RandBin(STORE_RAND_MONEY);
				rMerch.smugglerMoney =	SMUGG_MIN_MONEY	+ RandBin(SMUGG_RAND_MONEY);
			break;
			case "medium":
				rMerch.money =			STORE_MIN_MONEY/2 + RandBin(STORE_RAND_MONEY/2);
				rMerch.smugglerMoney =	SMUGG_MIN_MONEY + RandBin(SMUGG_RAND_MONEY);
			break;
			case "small":
				rMerch.money =			STORE_MIN_MONEY/2 + RandBin(STORE_RAND_MONEY/2);
				rMerch.smugglerMoney =	SMUGG_MIN_MONEY	+ RandBin(SMUGG_RAND_MONEY);
			break;
		}
	}
	//обновить торговцев предметами
	for (i = 0; i < MAX_CHARACTERS; i++)
	{
		rMerch = &Characters[i];
		if (!CheckAttribute(rMerch, "Merchant")) continue;

		if (rMerch.id == "walker")  continue; //бродячие торговцы: у них id == "walker", они перезаписываются

		if (CheckAttribute(rMerch, "city") && "LostShipsCity" == rMerch.city) continue; //Барыгу гпк не обновляем - у него много бабла

		if (HasStr(rMerch.id, "_usurer")) //Банкиры
		{
			rMerch.money = BANK_TRADER_MIN_MONEY + RandBin(BANK_TRADER_RAND_MONEY);
			continue;
		}

		if (HasStr(rMerch.id, "_trader")) //Магазины
		{
			rMerch.money = STORE_TRADER_MIN_MONEY + RandBin(STORE_TRADER_RAND_MONEY);
			continue;
		}

		if (HasStr(rMerch.id, "_Lightman") || HasStr(rMerch.id, "_Cemeteryman")) //смотрители погостов и маяков
		{
			rMerch.money = LIGHT_TRADER_MIN_MONEY + RandBin(LIGHT_TRADER_RAND_MONEY);
			continue;
		}
		//лоточники
		rMerch.money = MERCH_TRADER_MIN_MONEY + RandBin(MERCH_TRADER_RAND_MONEY);
	}
}

// перенес из ВМЛ 25/09/06
void ProcessDayRepair()
{
	int i, cn;
	float matQ, tmpf, repPercent;
	ref chref;
	// boal 21.01.2004 на лету в море не чиним, тк идут дни прям в море -->
	if (bSeaActive == false || pchar.location == pchar.SystemInfo.CabinType) // спим в каюте
	{
		for (i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(pchar,i);
			if(cn==-1) continue;
			chref = GetCharacter(cn);

			// расчёт починки корпуса
			if (GetHullPercent(chref)<100.0 )
			{
				repPercent = GetHullRPD(chref);
				matQ = repPercent*GetHullPPP(chref);
				tmpf = GetRepairGoods(true,chref);
				if (tmpf > 0)
				{
					if (tmpf < matQ) repPercent = tmpf/GetHullPPP(chref);
					repPercent = ProcessHullRepair(chref, repPercent);
					matQ = repPercent*GetHullPPP(chref);
					RemoveRepairGoods(true, chref, matQ);
		            AddCharacterExpToSkill(chref, "Repair", matQ / 3.0); // boal  check skill
	            }
			}

			// расчёт починки парусов
			if (GetSailPercent(chref) < 100.0)
			{
				repPercent = GetSailRPD(chref);
				matQ = repPercent*GetSailSPP(chref);
				tmpf = GetRepairGoods(false, chref);
				if (tmpf > 0)
				{
					if (tmpf < matQ) repPercent = tmpf/GetSailSPP(chref);
					repPercent = ProcessSailRepair(chref, repPercent);
					matQ = repPercent * GetSailSPP(chref);
					RemoveRepairGoods(false, chref, matQ);
		            AddCharacterExpToSkill(chref, "Repair", matQ / 4.0); // boal  check skill
	            }
			}
		}
	}
	// boal 21.01.2004 <--
}

void RemoveRepairGoods(bool bIsHull, ref chref, float matQ)
{
	int nGoodsQ = 0;
	float fGoodsQ = GetRepairGoods(bIsHull, chref);

	if (bIsHull)
	{
		if (fGoodsQ <= matQ) DeleteAttribute(chref,"RepairMaterials.forHull");
		else
		{
			fGoodsQ -= matQ;
			nGoodsQ = makeint(fGoodsQ);
			chref.RepairMaterials.forHull = fGoodsQ - nGoodsQ;
		}
		SetCharacterGoods(chref,GOOD_PLANKS,nGoodsQ);
	}
	else
	{
		if (fGoodsQ <= matQ) DeleteAttribute(chref,"RepairMaterials.forSails");
		else
		{
			fGoodsQ -= matQ;
			nGoodsQ = makeint(fGoodsQ);
			chref.RepairMaterials.forSails = fGoodsQ - nGoodsQ;
		}
		SetCharacterGoods(chref, GOOD_SAILCLOTH,nGoodsQ);
	}
}

float GetRepairGoods(bool bIsHull, ref chref)
{
	float fGoodsQ = 0.0;

	if (bIsHull)
	{
		fGoodsQ = GetCargoGoods(chref,GOOD_PLANKS);
		if (CheckAttribute(chref,"RepairMaterials.forHull")) // погрешность округления списания колва досок за процент
			fGoodsQ += stf(chref.RepairMaterials.forHull);
	}
	else
	{
		fGoodsQ = GetCargoGoods(chref,GOOD_SAILCLOTH);
		if (CheckAttribute(chref,"RepairMaterials.forSails"))
			fGoodsQ += stf(chref.RepairMaterials.forSails);
	}

	return fGoodsQ;
}

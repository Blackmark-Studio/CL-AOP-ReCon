#define I_MIN_MORALE	10

// boal -->
#define FOOD_BY_CREW       10.0
#define FOOD_BY_SLAVES     20.0
#define FOOD_BY_PASSENGERS 10.0
#define RUM_BY_CREW        20.0
// boal <--

//bool bInterfaceFood = false;
//int iFoodQuantity = 0;

// вернёт число дней на сколько есть еда на всех кораблях
int CalculateFood()
{
	int chrIndex;
	int iCrewQuantity = 0;
	float foodNeeded = 0;
	int iSlavesQuantity = 0;
	int iFoodQuantity = 0;

	for (int i=0; i<COMPANION_MAX; i++)
	{
		chrIndex = GetCompanionIndex(pchar, i);
		if (chrIndex != -1)
		{
            if (!GetRemovable(&characters[chrIndex])) continue;
			if (characters[chrIndex].ship.type != SHIP_NOTUSED)
			{
				iCrewQuantity   = iCrewQuantity   + sti(characters[chrIndex].ship.crew.quantity);
				iFoodQuantity   = iFoodQuantity   + GetCargoGoods(&characters[chrIndex], GOOD_FOOD);
				iSlavesQuantity = iSlavesQuantity + GetCargoGoods(&characters[chrIndex], GOOD_SLAVES);
			}
		}
	}
	int iPassQuantity = GetPassengersQuantity(pchar);

	foodNeeded = makefloat(iCrewQuantity/FOOD_BY_CREW + iPassQuantity/FOOD_BY_PASSENGERS + iSlavesQuantity/FOOD_BY_SLAVES);

	if (foodNeeded < 1)
	{
		foodNeeded = 1;
	}

	iFoodQuantity = makeint(iFoodQuantity/foodNeeded + 0.2);

	return iFoodQuantity;
}

// еды на одном корабле
int CalculateShipFood(ref _chr)
{
	int iCrewQuantity = 0;
	float foodNeeded = 0;
	int iSlavesQuantity = 0;
	int iFoodQuantity = 0;
	int iPassQuantity = 0;

	iCrewQuantity   =  sti(_chr.ship.crew.quantity);
	iFoodQuantity   =  GetCargoGoods(_chr, GOOD_FOOD);
	iSlavesQuantity =  GetCargoGoods(_chr, GOOD_SLAVES);
	if (CheckAttribute(_chr, "id") && _chr.id == pchar.id)
	{
		iPassQuantity = GetPassengersQuantity(pchar);
	}

	foodNeeded = makefloat(iCrewQuantity/FOOD_BY_CREW + iPassQuantity/FOOD_BY_PASSENGERS + iSlavesQuantity/FOOD_BY_SLAVES);

	if (foodNeeded < 1)
	{
		foodNeeded = 1;
	}

	iFoodQuantity = makeint(iFoodQuantity/foodNeeded + 0.2);

	return iFoodQuantity;
}

// Warship 11.07.09 Вернёт кол-во дней, на сколько хватит рому на одном корабле
int CalculateShipRum(ref _character)
{
	int crewQuantity = GetCrewQuantity(_character);
	int rumQuantity = GetCargoGoods(_character, GOOD_RUM);
	float rumNeeded = makefloat((crewQuantity + 5.1) / RUM_BY_CREW); // Сколько жрут за день
	
	if(rumNeeded < 1.0) rumNeeded = 1.0;	
	rumQuantity = makeint(rumQuantity/rumNeeded + 0.2);		
	return rumQuantity;
}

// Ugeen  29.10.10 вернёт число дней на сколько есть рому на всех кораблях
int CalculateRum()
{
	int chrIndex;
	int iCrewQuantity = 0;
	int iRumCount = 0;
	float RumNeeded = 0;

	for (int i=0; i<COMPANION_MAX; i++)
	{
		chrIndex = GetCompanionIndex(pchar, i);
		if (chrIndex != -1)
		{
            if (!GetRemovable(&characters[chrIndex])) continue;
			if (characters[chrIndex].ship.type != SHIP_NOTUSED)
			{
				iCrewQuantity += GetCrewQuantity(&characters[chrIndex]);
				iRumCount     += makeint(GetCargoGoods(&characters[chrIndex], GOOD_RUM));							
			}
		}
	}
	RumNeeded = makefloat(iCrewQuantity/RUM_BY_CREW);

	if (RumNeeded < 1.0)
	{
		RumNeeded = 1.0;
	}

	return makeint(iRumCount/RumNeeded + 0.2);
}

// boal 21.04.04 крысы на корабле -->
void DailyRatsEatGoodsUpdate(ref chref)
{
	if (CheckCharacterPerk(pchar, "Sanitary")) return; // KZ > с перком "Абсолютная санитария" в эскадре нет крыс и вне боя матросы обходятся без медицины
	if(GetCharacterItem(chref, "indian11")) return; // проверка крысиного бога //HardCoffee дополнительно проверим в казначее
	if (CheckAttribute(chref, "Fellows.Passengers.treasurer") && sti(chref.Fellows.Passengers.treasurer) > 0
		&& CheckCharacterItem(GetCharacter(sti(chref.Fellows.Passengers.treasurer)), "indian11")) return;
	if (CheckAttribute(&TEV, "captainInTheLSC")) return; //в ГПК крыса одна и это Чад
    int iGoods = GOOD_POWDER + rand(GOOD_OIL - GOOD_POWDER);
    int iQuantity = GetCargoGoods(chref, iGoods);
    if (iQuantity > 60 && rand(4) != 2) // шанс не жрать, если весь спектр
    {
        float fSkill = GetSummonSkillFromNameToOld(chref, SKILL_REPAIR) + GetSummonSkillFromNameToOld(chref,SKILL_FORTUNE);
        
        iQuantity = 1+ rand(makeint(iQuantity / (10+fSkill)));
        RemoveCharacterGoodsSelf(chref, iGoods, iQuantity);
        notification(RandSwear() + " " + StringFromKey("InfoMessages_94", chref.Ship.Name,
                         LinkRandPhrase(GlobalStringConvert("rat_spoiled"), GlobalStringConvert("rat_damaged"), GlobalStringConvert("rat_destroyed")),
                         iQuantity, XI_ConvertString("pcs"), GetGoodsNameAlt(iGoods)), "Rats");

        Statistic_AddValue(pchar, "RatsEatGoods", iQuantity);
                
		if (iQuantity > 400) iQuantity = 400;
		
		AddCharacterExpToSkill(chref, SKILL_REPAIR, iQuantity);
        AddCharacterExpToSkill(chref, SKILL_FORTUNE, iQuantity/10);
    }
}

// boal food for crew 20.01.2004 -->
//Для ежедневных событий есть WorldSituationsUpdate
void DailyEatCrewUpdate()
{
    ref mainCh = GetMainCharacter();
    int i, cn;
    ref chref;

    mainCh.questTemp.abordage = 0; // fix квест потопить пирата второй абордаж

	RestoreNewDayHealth(); // здоровье за день в том числе для офицеров
    AzzyCheckSumControl(); // квест Аззи, подсчет контрольныйх сумм по неуязвимости

    DeleteAttribute(mainCh, "GenQuest.Hunter2Pause");  // boal бойня в форте кончилась - ОЗГи вернулись
	
	if (GetOfficersPerkUsing(pchar, "Capellan1", false)) AddCrewMorale(mainCh, 2); //Jason, влияние корабельного капеллана на мораль

	////////////////      ЕДА     /////////////////
	if (bNoEatNoRats) return; // betatest
    if (sti(mainCh.Ship.Type) == SHIP_NOTUSED ) return;
	
	for (i = 0; i < COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(mainCh,i);
		if (cn < 0) continue;
		chref = GetCharacter(cn);

		if (!GetRemovable(chref)) continue;

		DailyRatsEatGoodsUpdate(chref); // RATS
		DailyEatCrewUpdateForShip(chref, false);
	}
}

// boal 20.01.2004 <--

// Warship. Вынес в отдельный метод
void DailyEatCrewUpdateForShip(ref rChar, bool IsCompanionTraveler) // IsCompanionTraveler - спец флаг для компаньонов-путешественников
{
	if (bIsRepairingProcess) return; //HardCoffee во время ремонта корабля матросы сами ищут еду

	int iCrewQty = GetCrewQuantity(rChar);
	int iGoodSlaves = GetCargoGoods(rChar, GOOD_SLAVES);

	if (iCrewQty < 1 && iGoodSlaves < 1) return;

	int iGoodFood = GetCargoGoods(rChar, GOOD_FOOD);
	int iGoodMeds = GetCargoGoods(rChar, GOOD_MEDICAMENT);
	int iGoodRum = GetCargoGoods(rChar, GOOD_RUM);

	int cn, morale, nMoraleDecreaseQ, iDeadCrew;
	float fCheckDrugs = 1.0;
	bool bAptekar = CheckOfficersPerk(rChar, "Aptekar");
	bool bNaturalcure = CheckOfficersPerk(rChar, "Naturalcure"); // KZ > перк "Лечение травами" - всякий раз, когда отрабатывает расчёт медицины, даются лекарства в кол-ве от 5% до 15% от числа команды на корабле rChar
	bool bIronWill = CheckOfficersPerk(rChar, "IronWill");

	if(!CheckAttribute(rChar, "Ship.Crew.Morale"))
	{
		rChar.Ship.Crew.Morale = 50;
	}

	if (CheckOfficersPerk(rChar, "Doctor3"))
		fCheckDrugs = 0.5;
	else
	{
		if (bAptekar)
			fCheckDrugs = 0.7;
		else if (bNaturalcure)
			fCheckDrugs = 0.9;
	}

	// расчёт медицины -->
	if (fCheckDrugs >= frandSmall(1.0))
	{
		if (bNaturalcure && iCrewQty > 0)
			AddCharacterGoodsSimple(rChar, GOOD_MEDICAMENT, makeint(iCrewQty * (0.05 + frandSmall(0.10))));
		
		// матросы
		cn = iCrewQty / 10;
		if (cn > 30) cn = 30;
		cn = rand(cn) + 1;
		if (iCrewQty < cn) cn = iCrewQty;
		
		if (cn > 0 && !CheckCharacterPerk(pchar, "Sanitary")) // KZ > с перком "Абсолютная санитария" в эскадре нет крыс и вне боя матросы обходятся без медицины
		{
			if (iGoodMeds < 1)
			{
				if(!IsCompanionTraveler) Log_Info(StringFromKey("InfoMessages_95", UpperFirst(XI_ConvertString("musicmod_s")), rChar.Ship.Name, FindSailorString(cn, "No")));
				iCrewQty = iCrewQty - cn;
				Statistic_AddValue(pchar, "Sailors_dead", cn);
				rChar.Ship.Crew.Quantity = iCrewQty;
				// мораль в минус
				morale = sti(rChar.Ship.Crew.Morale);
				
				if (bIronWill) cn /= 1.5;
				
				AddCrewMorale(rChar, -makeint(cn / 2)); // до 15 пунктов за раз
			}
			else
			{
				if (CheckShipSituationDaily_GenQuest(rChar) == 2) cn = cn * 2;
				if (CheckShipSituationDaily_GenQuest(rChar) == 3) cn = cn * 3;
				
				if (bAptekar) // KZ > с перком "Аптекарство" расход медикаментов при лечении уменьшен на 30%
					cn = makeint(cn * 0.7);
				else if (bNaturalcure) // KZ > с перком "Лечение травами" расход медикаментов при лечении уменьшен на 15%
					cn = makeint(cn * 0.85);
				
				if (cn < 1)
					cn = 1;
				
				RemoveCharacterGoodsSelf(rChar, GOOD_MEDICAMENT, cn);
				iGoodMeds -= cn;
			}
		}
		if (iGoodMeds < 16)
		{
			if (!IsCompanionTraveler)
				Log_Info(StringFromKey("InfoMessages_71", UpperFirst(XI_ConvertString("musicmod_s")), rChar.Ship.Name));
		}
		// рабы
		cn = iGoodSlaves / 10;
		if(cn > 30) cn = 30;
		cn = rand(cn)+1;
		if(iGoodSlaves < cn) cn = iGoodSlaves;
		if(cn > 0)
		{
			if(iGoodMeds < 1)
			{
				if (or(!CheckOfficersPerk(rChar, "LifeSupport"), CheckOfficersPerk(rChar, "LifeSupport") && rand(9) < 4)) // KZ > перк "Поддержание жизни" снижает риск смерти рабов на 60%
				{
					if (!IsCompanionTraveler)
						Log_Info(StringFromKey("InfoMessages_95", UpperFirst(XI_ConvertString("musicmod_s")), rChar.Ship.Name, FindSailorString(cn, "No")));
					
					RemoveCharacterGoodsSelf(rChar, GOOD_SLAVES, cn);
				}
			}
			else
			{
				cn /= 3;
				RemoveCharacterGoodsSelf(rChar, GOOD_MEDICAMENT, cn);
			}
		}
		// повторный контроль
		if(iCrewQty < 1 && iGoodSlaves < 1) return;
	}
	// расчёт медицины <--
	
	iCrewQty = makeint((iCrewQty+5.1) / RUM_BY_CREW); // eat ratio
	//if (rChar == 0) rChar = 1;
	if(iCrewQty > 0)
	{
		if(iGoodRum >= iCrewQty)
		{
			RemoveCharacterGoodsSelf(rChar, GOOD_RUM, iCrewQty);
			// проверка на остатки
			cn = makeint(iGoodRum / iCrewQty);
			if (cn < 1)
			{
				if(!IsCompanionTraveler)
				{
					Log_Info(StringFromKey("InfoMessages_96", UpperFirst(XI_ConvertString("musicmod_s")), rChar.Ship.Name));
					PlaySound("Notebook_1"); // Hokkins: произведем звук, когда ром закончится.
				}
			}
			// поднимем мораль
			if(CheckShipSituationDaily_GenQuest(rChar) == 1) AddCrewMorale(rChar, 2);
		}
		else
		{
			iCrewQty = iGoodRum;
			RemoveCharacterGoodsSelf(rChar, GOOD_RUM, iCrewQty);
		}
	}
	iCrewQty = GetCrewQuantity(rChar);
	// рассчет перегруза команды на мораль -->
	if(iCrewQty > GetOptCrewQuantity(rChar))
	{
		if (!CheckOfficersPerk(rChar, "MasterOverload")) // KZ > перк "Мастер перегруза" полностью убирает штраф на снижение морали при перегрузе команды
			AddCrewMorale(rChar, -(1+rand(3)));
	}
	// рассчет перегруза команды на мораль <--

	int nMoraleDecreaseCalc = 12 - GetSummonSkillFromNameToOld(rChar, SKILL_LEADERSHIP);

	// расчёт еды после Рома
	iCrewQty = makeint((iCrewQty+5.1) / FOOD_BY_CREW + GetPassengersQuantity(rChar) / FOOD_BY_PASSENGERS); // eat ratio
	iCrewQty = iCrewQty + makeint((iGoodSlaves+6)/ FOOD_BY_SLAVES);  // учет рабов
	if (iCrewQty == 0) iCrewQty = 1;
	if (iGoodFood >= iCrewQty)
	{
		RemoveCharacterGoodsSelf(rChar, GOOD_FOOD, iCrewQty);
		// проверка на остатки
		cn = makeint(iGoodFood / iCrewQty);
		if (cn < 4)
		{
			if (!IsCompanionTraveler)
			{
				Log_Info(StringFromKey("InfoMessages_97", UpperFirst(XI_ConvertString("musicmod_s")), rChar.Ship.Name, FindDaysString(cn)));
				Log_Info(StringFromKey("InfoMessages_98"));
				PlaySound("Notebook_1");
			}
		}
	}
	else
	{
		iCrewQty = iGoodFood;
		RemoveCharacterGoodsSelf(rChar, GOOD_FOOD, iCrewQty);
		PlaySound("Notebook_1");
		
		if(!IsCompanionTraveler) Log_Info(StringFromKey("InfoMessages_100", UpperFirst(XI_ConvertString("musicmod_s")), rChar.Ship.Name));
		
		if(sti(rChar.index) == GetMainCharacterIndex())
		{
			AddCharacterHealth(PChar, -1);
		}
		
		cn = GetCrewQuantity(rChar);
		if(cn > 1)
		{
			iDeadCrew = makeint(cn/10 +0.5);
			rChar.Ship.Crew.Quantity = cn - iDeadCrew;
			Statistic_AddValue(pchar, "Sailors_dead", iDeadCrew);
			if(!IsCompanionTraveler) Log_Info(StringFromKey("InfoMessages_101"));
		}
		cn = iGoodSlaves;
		if(cn > 0)
		{
			RemoveCharacterGoodsSelf(rChar, GOOD_SLAVES, makeint(cn/5 + 0.5));
			if(!IsCompanionTraveler) Log_Info(StringFromKey("InfoMessages_102"));
		}
		morale = sti(rChar.Ship.Crew.Morale);
		
		nMoraleDecreaseQ = nMoraleDecreaseCalc;
		if (bIronWill) nMoraleDecreaseQ *= 0.5;
		rChar.Ship.Crew.Morale = morale - nMoraleDecreaseQ;
		if(sti(rChar.Ship.Crew.Morale) < MORALE_MIN) rChar.Ship.Crew.Morale = MORALE_MIN;
	}
	
	if (rChar.index == pchar.index)
	{
		if (!IsEntity(&worldMap)) return;

		if (sti(rChar.Ship.Crew.Morale) <= MORALE_MIN && GetCrewQuantity(rChar) > 0)
		{
			Log_Info(StringFromKey("InfoMessages_103", rChar.Ship.Name));
			MunityOnShip("ShipMunity");
			return;
		}
		// возможный бунт рабов
		if (rand(2) == 1)
		{
			if (CheckCharacterPerk(pchar, "SlaveTraderTrait") && rand(1) == 0) return;

			if (iGoodSlaves > (GetCrewQuantity(rChar) * (0.5 + stf(rChar.Ship.Crew.Morale) / 50.0)))
			{
				nMoraleDecreaseQ = nMoraleDecreaseCalc;
				if (bIronWill) nMoraleDecreaseQ *= 0.5;
				if (nMoraleDecreaseQ > rand(10))
				{
					rChar.GenQuest.SlavesMunity = true;
					Log_Info(StringFromKey("InfoMessages_99"));
					MunityOnShip("SlavesMunity");
				}
			}
		}
	}
	//квестовые оффы и компаньоны-путешественники не бунтуют
	else if (!IsCompanionTraveler && GetShipRemovable(rChar) && !CheckAttribute(rChar, "OfficerWantToGo.DontGo"))
	{
		// допуск, что лояльность есть у всех офов
		if (sti(rChar.loyality) <= 0 || and(sti(rChar.Ship.Crew.Morale) <= MORALE_MIN, GetCrewQuantity(rChar) > 0))
		{
			Log_Info(StringFromKey("InfoMessages_103", rChar.Ship.Name));
			Log_SetStringToLog(StringFromKey("InfoMessages_104"));
			Statistic_AddValue(PChar, "ShipMunity", 1);
			RemoveCharacterCompanion(PChar, rChar);
			//fix  ПГГ
			if (!CheckAttribute(rChar, "PGGAi"))
			{
				rChar.LifeDay = 0; // стереть при выходе
			}
			else
			{
				rChar.PGGAi.IsPGG = true;
				rChar.RebirthPhantom = true;
				rChar.PGGAi.location.town = PGG_FindRandomTownByNation(sti(rChar.nation));
				rChar.Dialog.FileName = "PGG_dialog.c";
				rChar.Dialog.CurrentNode = "Second Time";
				PGG_ChangeRelation2MainCharacter(rChar, -20);
			}
			rChar.location = ""; // нафиг, нафиг..а то в таверне появлялся...
			rChar.location.group = "";
			rChar.location.locator = "";
		}
	}
}

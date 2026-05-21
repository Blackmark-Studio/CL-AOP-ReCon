// логика абордажа, переработка boal 28.04.06
// многопалубный абордаж, Jason
#define BRDLT_SHIP	0
#define BRDLT_FORT	1

#define BRDLT_MAXCREW 60

#define LOCINITBRD_DEFAULTLOCATION "BOARDING_U_H_CS_T12"
#define LOCINITBRD_DEFAULTLOCATION_FORT "Any_fort_1"

#define MAX_GROUP_SIZE   24

bool   IsFort = false;
int    boarding_location = -1;
int    boarding_location_type = -1;
object boarding_fader;


int   boarding_player_crew = 0;
int   boarding_officers    = 0;
float boarding_player_base_crew    = 0.0; //boal
float boarding_player_crew_per_chr = 1.0;
int   boarding_player_crew_start   = 0; //sd

int   boarding_enemy_crew = 0;
float boarding_enemy_base_crew    = 0.0;
float boarding_enemy_crew_per_chr = 1.0;
int   boarding_enemy_crew_start   = 0; //sd

ref    boarding_enemy;
object boarding_adr[4];
float  boarding_exp = 0;
float  bonus_player_hp = 0;
float  bonus_enemy_hp = 0;
int    bonus_player_rank = 0;
int    bonus_enemy_rank = 0;
int    boarding_echr_index = -1;
int    boarding_erank = 10;
bool   LAi_boarding_process = false;
bool   Surrendered = false; // сдача в плен

int inside_ecrew_1, inside_ecrew_2;

//Процес абордажа
bool LAi_IsBoardingProcess()
{
	return LAi_boarding_process;
}

//Получить картинку для перехода в абордаж
string LAi_GetBoardingImage(ref echr, bool isMCAttack)
{
	ref mchr = GetMainCharacter();
	string deckID = "";
	isMCAttack   = true;// boal 110804 fix всегда герой
	if(isMCAttack)
	{
		deckID = GetShipLocationID(echr);
	}else{
		deckID = GetShipLocationID(mchr);
	}
	int locID = -1;
	if(deckID != "")
	{
		locID = FindLocation(deckID);
		if(locID < 0)
		{
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(locID >= 0)
	{
		if(CheckAttribute(&Locations[locID], "image"))
		{
			if(Locations[locID].image != "")
			{
				return GetRandomLoadingPic(Locations[locID].image);
			}
		}
	}
	return "loading\battle_" + rand(2) + ".tga";
}

//Начать абордаж с главным персонажем
void LAi_StartBoarding(int locType, ref echr, bool isMCAttack)
{
    SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
	//ResetSoundScheme();
	ResetSound(); // new
	PauseAllSounds();
	
	bQuestCheckProcessFreeze = true;//fix
	
	EmptyAbordageCharacters();
	
	// NK -->
	if(locType == BRDLT_FORT)
    {
        isMCAttack = true;
        IsFort = true;
    }
	else
    {
        IsFort = false;
    }
    // NK <--
	//Установим обработчик на убийство группы
	SetEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill", 1);
	//Настроим интерфейс
	DeleteBattleInterface();
	InitBattleLandInterface();
	//StartBattleLandInterface();
	//Сохраним индекс врага
	boarding_echr_index = sti(echr.index);
	//Параметры сражающихся сторон
	ref mchr = GetMainCharacter();
	int mclass = GetCharacterShipClass(mchr);
	int mcrew = GetCrewQuantity(mchr);
	
	DeleteAttribute(pchar, "abordage_active");
	// boal учет оружия 21.01.2004 -->
	Log_TestInfo("Наших до оружия " + mcrew);
	mcrew = GetWeaponCrew(mchr, mcrew);
	
	// boal 21.01.2004 <--
	int eclass = GetCharacterShipClass(echr);
	int ecrew = GetCrewQuantity(echr);
	int ecrewBak;

    Log_TestInfo("Наших с оружием " + mcrew + " Врагов " + ecrew);
    
    boarding_location_type = locType;
	// Сдача в плен -->
	bool ok = (TestRansackCaptain) && (boarding_location_type != BRDLT_FORT);
    if (!CheckAttribute(echr, "DontRansackCaptain")) //квестовые не сдаются
    {
    	if (CheckForSurrender(mchr, echr, 1) || ok) // 1 - это учет первый раз, до битвы на палубе
    	{
    		echr.ship.crew.morale = 5;// после захвата у них мораль такая

    		if (mclass < eclass)
			{
				AddCrewMorale(mchr, ( 3 + 2*rand(eclass-mclass)));
			} 
			else
			{
				AddCrewMorale(mchr, 3);
			}
			SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
            //Следующей локации нет
			DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
			boarding_location = -1;

		    bQuestCheckProcessFreeze = false;//fix
		    
			//Настроим интерфейс
			Log_SetActiveAction("Nothing");
			EndBattleLandInterface();
            //Выгружаемся в интерфейс
            
			ChangeCrewExp(pchar, "Soldiers", 1);			
			LaunchRansackMain(pchar, echr, "crew");
			// на деле параметры LaunchRansackMain не важны совсем - все определеятеся от реалий - жив кэп и сколько у него матросов - их и обрабатываем
			// но они используются в сообщениях  crew - это сдался сразу
    		LAi_boarding_process = false;  
			Event(SHIP_CAPTURED, "l", sti(echr.index));
			
			if (mclass < 7) // на 7-ом классе нет трюма (пока?!)
			{
				int bonus, trophy = 1;
				LootCollectorCompensation(echr); // KZ > компенсация лута, если нарвались на капитулянта; кэп сдался сразу
				
				if (eclass < 3)
					trophy = 4;
				else
				{
					if (eclass < 5)
						trophy = 2;
				}
				
				for (bonus = 0; bonus < trophy; bonus++)
				{
				    LootCollectorRandItems();
				}

			}
			
    		return;
    	}
	}
	// Сдача в плен <--
	
	// --> ugeen  Мушкетный залп из ККС, перенес ZhilyaevDm	28.02.23
	float 	mShipClassCoeff, eShipClassCoeff;
	int   	mCrewShot = 0;
	int	  	eCrewShot = 0;
	float	mDamage, eDamage;
	float   mCoeff = 0.0;
	bool	bOk = false;

	if (CheckOfficersPerk(mchr, "MusketsShoot") && !IsFort) // для ГГ
	{
		bOk = true;
		int OffQty = GetOfficersQuantity(mchr);
		if (OffQty < 0) OffQty = 1;

		mShipClassCoeff = (eclass - mclass) * 0.15; // считаем коэффицент классности для ГГ
		mCrewShot = makeint(mcrew / 4);				// количество стрелков ГГ

		mCoeff = 0.5 + 0.1 * OffQty;
		// это базовая величина потенциального урона, который может нанести команда протагониста.
		mDamage = mcrew * mCoeff / 4 + rand(makeint(mcrew * (1 - mCoeff) / 4));

		mDamage = mDamage * (1 + mShipClassCoeff);
		// evganat - энциклопедия
		int iBonus = 0;
		iBonus = GetParamPageBonus("MusketsShoot");
		mDamage *= 1.0 + 0.01*iBonus;
		
		if (mDamage > ecrew * 0.75) mDamage = ecrew * 0.75;

		ecrewBak = makeint(mDamage);
		ecrew = ecrew - ecrewBak;

//		Log_SetStringToLog(StringFromKey("InfoMessages_68", FindPeoplesString(ecrewBak, "No")));
		Notification(StringFromKey("InfoMessages_68", FindPeoplesString(ecrewBak, "No")), "MusketsShoot");
	}
	if (CheckOfficersPerk(echr, "MusketsShoot") && !IsFort) // для противника
	{
		bOk = true;
		
		eShipClassCoeff = (mclass - eclass) * 0.15; 				// считаем коэффицент классности для противника
		eCrewShot = makeint(ecrew / 4);								// количество стрелков противника
		eDamage = ecrew * 0.2 + rand(makeint(ecrew / 20)); 			// базовая величина потенциального урона, который может нанести противник

		eDamage = eDamage * (1 + eShipClassCoeff);
		if (eDamage > mcrew * 0.75) eDamage = mcrew * 0.75;

		ecrewBak = makeint(eDamage);
		mcrew = mcrew - ecrewBak;

//		Log_SetStringToLog(StringFromKey("InfoMessages_69", FindPeoplesString(ecrewBak, "No")));
		Notification(StringFromKey("InfoMessages_69", FindPeoplesString(ecrewBak, "No")), "X");
		Statistic_AddValue(mchr, "DeadCrewBoard", ecrewBak);
		Statistic_AddValue(mchr, "Sailors_dead", ecrewBak);
	}
	if (bOk)
	{
		//PlaySound("MushketShot");	//в ккс другие звуки на залпе потом пожно будет добавить, пока так
		 
		if(mclass <=2 || eclass <= 2) PlaySound("MusketFire1");
		else
		{
			if(rand(2) > 1) PlaySound("MusketFire3");
			else 			PlaySound("MusketFire2");
		}
		
	}
	// MusketsShoot <--

	
	// MusketsShoot --> 

	/* // оригинальный код
	float tmpDefence;
    if (CheckOfficersPerk(mchr, "MusketsShoot") && !IsFort)
    {
        tmpDefence   = MakeFloat(GetSummonSkillFromName(echr, SKILL_DEFENCE)) / SKILL_MAX;
        ecrewBak = makeint(ecrew * 0.25);
		if (ecrewBak > mcrew) ecrewBak = mcrew;
		ecrewBak = makeint(ecrewBak * (2.1 - tmpDefence) / 2.0);
        ecrew = ecrew - ecrewBak;
        Log_SetStringToLog("Мушкетным залпом убито " + ecrewBak + " человек команды противника.");
        PlaySound("MushketShot");
    }
	if (CheckCharacterPerk(echr, "MusketsShoot") && !IsFort)
    {
        tmpDefence   = MakeFloat(GetSummonSkillFromName(mchr, SKILL_DEFENCE)) / SKILL_MAX;
        ecrewBak = makeint(mcrew * 0.25);
		if (ecrewBak > ecrew) ecrewBak = ecrew;
		ecrewBak = makeint(ecrewBak * (2.1 - tmpDefence) / 2.0);
        mcrew = mcrew - ecrewBak;
        Log_SetStringToLog("Мушкетным залпом убито " + ecrewBak + " человек нашей команды.");
        Statistic_AddValue(mchr, "DeadCrewBoard", ecrewBak);
		Statistic_AddValue(mchr, "Sailors_dead", ecrewBak);
        PlaySound("MushketShot");
    }
	*/
    // MusketsShoot <--
    
	if(ecrew < 0) ecrew = 0;
	if(mcrew < 0) mcrew = 0;
	boarding_erank = sti(echr.rank);

	// база для расчёта
	boarding_enemy_base_crew = ecrew;
	boarding_player_base_crew = mcrew;
	
	//Количество хитпойнтов для бонуса - учет опыта солдат
	bonus_player_hp = 0;
	bonus_enemy_hp = 0;
	GetBoardingHP(mchr, echr, &bonus_player_hp, &bonus_enemy_hp);
	//Определяем цепь локаций для абордажа
	boarding_location = -1;

	string deckID = "";
	isMCAttack   = true;// boal 110804 fix всегда герой
	if(isMCAttack)
	{
		deckID = GetShipLocationID(echr);
	}else{
		deckID = GetShipLocationID(mchr);
	}
	int locID = -1;
	if(deckID != "")
	{
		locID = FindLocation(deckID);
		if(locID < 0)
		{
			Trace("Boarding: ship location not found <" + deckID + ">, set default");
			deckID = "";
		}
	}
	if(deckID == "")
	{
		if(locType == BRDLT_FORT)
		{
			deckID = LOCINITBRD_DEFAULTLOCATION_FORT;
		}else{
			deckID = LOCINITBRD_DEFAULTLOCATION;
		}
		locID = FindLocation(deckID);
	}
	if (locID < 0)
	{   // исключительная ситуация
		Trace("Boarding: ship location not found <" + deckID + ">, no start boarding");

	    bQuestCheckProcessFreeze = false;//fix
		    
		if(boarding_location_type == BRDLT_SHIP)
		{
            ChangeCrewExp(pchar, "Soldiers", 1);
            SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
			LaunchRansackMain(GetMainCharacter(), echr, "captain");	  // на деле параметры LaunchRansackMain не важны совсем - все определеятеся от реалий
            LAi_boarding_process = false;
			Event(SHIP_CAPTURED, "l", sti(echr.index)); // TODO can be harmfull
		}
		else
		{
			if (boarding_location_type == BRDLT_FORT)
			{
                ChangeCrewExp(pchar, "Soldiers", 1);
                SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
				Event(FORT_CAPTURED, "l", sti(echr.index));
				echr.Ship.Crew.Quantity = 10 + rand(350); // рабы (остатки выживших)
                LaunchFortCapture(echr);
                LAi_boarding_process = false;
			}else{
				Trace("Boarding: unknow boarding location type");
			}
		}
		return;
	}

	pchar.abordage = 0;
	//Определяем размеры команд
	boarding_enemy = echr;
	//Максимальное количество человек на корабле
	int maxcrew = MAX_GROUP_SIZE;
	
    if(CheckAttribute(&Locations[locID], "boarding.locatorNum"))
	{
		maxcrew = sti(Locations[locID].boarding.locatorNum);
	}
    //  модифицируем от класса корабля тут
    int iMaxcrew  = func_min(mclass, eclass); // класс 1 - сама круть 7 - хрень
    switch (iMaxcrew)
    {
		case 7: iMaxcrew = 8;	break;
		case 6: iMaxcrew = 10;	break;
		case 5: iMaxcrew = 12;	break;
		case 4: iMaxcrew = 14;	break;
		case 3: iMaxcrew = 16;	break;
		case 2: iMaxcrew = 22;	break;
		case 1: iMaxcrew = 24;	break;
    }
    if (iMaxcrew < maxcrew) maxcrew = iMaxcrew;
    
	if (boarding_location_type == BRDLT_SHIP && eclass != 7)  // на тартане каюты нет
	{
    	boarding_enemy.ShipCabinLocationId = GetShipCabinID(echr);
	}

	// boal check -->
	if(maxcrew > BRDLT_MAXCREW)
	{
	    maxcrew = BRDLT_MAXCREW;
	}
	// boal check <--

	//Отношение сторон

	// fort -->
	// boal 21.01.2004 -->
	int cn, j, compCrew, i;
    ref officer;
    if(IsFort)
    {
        mcrew = mcrew + GetTroopersCrewQuantity(GetMainCharacter()); // если нет перка, то нолик
        boarding_player_base_crew = mcrew;// учет всех кораблей
        //Максимальное количество человек
        Log_TestInfo("Итого: До расчёта mcrew = "+mcrew+ " ecrew = "+ ecrew + " bonus_enemy_hp = "+ bonus_enemy_hp + " bonus_player_hp = "+bonus_player_hp);
    }
    // boal 21.01.2004 <--
    // fort <--
	
	float rel;
	if (mcrew < 1) mcrew = 1;
	if (ecrew < 1) ecrew = 1;
	bonus_player_rank = 0;
	bonus_enemy_rank = 0;
	if (mcrew > ecrew)
	{
		bonus_player_rank = makeint(0.5 * MOD_SKILL_ENEMY_RATE * makefloat((mcrew - ecrew) / makefloat(ecrew)));
		Log_TestInfo("PLAYER rank bonus = " +bonus_player_rank);
        if (mcrew > maxcrew)
		{
			rel = makefloat(mcrew) / makefloat(maxcrew);
			mcrew = maxcrew;
			ecrew = MakeInt(ecrew / rel + 0.5);
		}
	}
	else
	{
		bonus_enemy_rank = makeint(2 * MOD_SKILL_ENEMY_RATE * makefloat((ecrew - mcrew) / makefloat(mcrew)));
		Log_TestInfo("ENEMY rank bonus = " +bonus_enemy_rank);
        if (ecrew > maxcrew)
		{       
			rel = makefloat(ecrew) / makefloat(maxcrew);
			ecrew = maxcrew;
			mcrew = MakeInt(mcrew/rel + 0.5);
		}
	}

	if (mcrew < 1) mcrew = 1; //HardCoffee TODO отрефакторить
	if (ecrew < 1) ecrew = 1;
    Log_TestInfo("После приведения mcrew = "+mcrew+ " ecrew = "+ ecrew + " bonus_enemy_hp = "+ bonus_enemy_hp + " bonus_player_hp = "+bonus_player_hp);
	
	//boarding_enemy_crew_start  = ecrew;
	
	//Jason: устанавливаем число тушек по разным палубам
	// верхнюю палубу оставляем без изменений по количеству, но срезаем 15% HP у воинов противника, на нижних палубах будут добавочные враги, но это компенсация за разделенность сил противника относительно сил героя
	inside_ecrew_1 = makeint(ecrew*0.3+0.5); // 30% - инсайд первого прохода
	inside_ecrew_2 = makeint(ecrew*0.2+0.5); // 20% - инсайд второго прохода
	if (inside_ecrew_1 < 1) inside_ecrew_1 = 1;
	if (inside_ecrew_2 < 1) inside_ecrew_2 = 1;
	if(IsFort) // на двор и бастион - поровну, по рез. тестов будем решать пропорции
	{
		inside_ecrew_1 = ecrew*0.3+0.5; // 30% - инсайд первого прохода
		inside_ecrew_2 = ecrew*0.3+0.5; // 30% - инсайд второго прохода
		ecrew = ecrew*0.6+0.5;
	}
	
	//ecrew = ecrew*0.7+1;
	
	boarding_enemy_crew        = ecrew;
	boarding_enemy_crew_start  = ecrew;
	boarding_player_crew       = mcrew;
	boarding_player_crew_start = mcrew;
	//Количество офицеров
	boarding_officers = 0;
	int passq;
	for(i = 1; i < 4; i++)
	{
		passq = GetOfficersIndex(pchar, i);
		if (passq >= 0)
		{
            // boal 05.09.03 offecer need to go to abordage -->
		    // TODO if(makeint(Characters[GetOfficersIndex(GetMainCharacter(), i)].AbordageMode) == 0) continue;	// не берем
			// boal 05.09.03 offecer need to go to abordage <--
			boarding_officers = boarding_officers + 1;   
			LAi_SetOfficerType(&characters[passq]);
		}
	}
  
    //boarding_player_crew_per_chr = (curplayercrew + boarding_officers)/(mcrew + boarding_officers);
    boarding_player_crew_per_chr = makefloat(boarding_player_base_crew / makefloat(mcrew)); //приведение типа
	// START MOD Code by Stone-D : 30/07/2003
	boarding_enemy_crew_per_chr = makefloat(boarding_enemy_base_crew / makefloat(ecrew)); // Stone-D : For calculating final crew numbers
	// END MOD Code by Stone-D : 30/07/2003

	//Выставим игроку и офицерам максимальную жизнь и запомним адреса
	LAi_SetCurHPMax(mchr);
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group    = mchr.location.group;
	boarding_adr[0].locator  = mchr.location.locator;
	for(i = 1; i < 4; i++)
	{
		int idx = GetOfficersIndex(GetMainCharacter(), i);
		if(idx < 0)
		{
			boarding_adr[i].location = "";
			boarding_adr[i].group    = "";
			boarding_adr[i].locator  = "";
			continue;
		}
		LAi_SetCurHPMax(&Characters[idx]);
		boarding_adr[i].location = Characters[idx].location;
		boarding_adr[i].group    = Characters[idx].location.group;
		boarding_adr[i].locator  = Characters[idx].location.locator;
	}
	//Стартуем
	LAi_boarding_process = true;
	LAi_LoadLocation(deckID, locType);

	LAi_MethodDelay("CheckBoardingTutorials", 1.5);

	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

//Загрузить локацию абордажа
void LAi_LoadLocation(string locationID, int locType)
{
//	Log_TestInfo("LoadLocation()");
	ReloadProgressStart();
	//Ищем локацию
	int locIndex = FindLocation(locationID);
	Log_SetActiveAction("Nothing");
    Dead_Char_num = 0; // boal dead body
	if(locIndex >= 0)
	{
		//Устанавливаем главного персонажа
		ref mchr = GetMainCharacter();
		mchr.location = locationID;
		mchr.location.group = "rld";
		// boal random place to star battle 28/11/03 -->
		int locNum[20];
		int locI;
		int maxLocators = 2;
		
		if (CheckAttribute(&Locations[locIndex], "boarding.locatorNum"))
		{
			maxLocators = sti(Locations[locIndex].boarding.locatorNum);
		}
		locI = 0;
		locNum[locI] = rand(maxLocators-1);
		string sLocType = "loc";
		// определение стороны на палубе
		if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
		{
		    sLocType = ChooseShipUpDeck(mchr, boarding_enemy);
		}

		mchr.location.locator = sLocType + locNum[locI];
		// для каюты перекрыть
		if (CheckAttribute(&Locations[locIndex], "CabinType") && CheckAttribute(&Locations[locIndex], "boarding.Loc.Hero"))
		{
		    mchr.location.locator = Locations[locIndex].boarding.Loc.Hero;
		}
		bool   okLoc;
		int iLoc, j;
		// boal random place to star battle 28/11/03 <--
		if (!CheckAttribute(&Locations[locIndex], "CabinType"))
		{ // не грузим офов, если каюту
	        //Устанавливаем офицеров, если такие есть
	        int logined = 1;
			for(int i = 1; i < 4; i++)
			{
				int idx = GetOfficersIndex(mchr, i);
				if(idx < 0) continue;
				//Log_TestInfo("Load Off " + Characters[idx].id);
				if (logined > maxLocators) break;
				if (CheckAttribute(&characters[idx],"AboardRestriction")) continue;

	            // boal 05.09.03 offecer need to go to abordage -->
//			    if(makeint(Characters[idx].AbordageMode) == 0) continue;	// не берем
				// boal 05.09.03 offecer need to go to abordage <--
				DeleteAttribute(&Characters[idx], "location");
				//Characters[idx].location = locationID;
				// boal чтоб грузились в фортах -->
				Characters[idx].location.loadcapture = true;
			    // boal чтоб грузились в фортах <--
				//Characters[idx].location.group = "rld";
				// boal random place to star battle 28/11/03 -->
				iLoc = rand(3);

				okLoc = false;
				while (!okLoc)
				{
				    for(j = 0; j <=locI; j++)
				    {
				        if (locNum[j] == iLoc)
				        {
				            iLoc = rand(3);
				            okLoc = false;
				            break;
				        }
				        okLoc = true;
				    }
				}
				locI++;
			    locNum[locI] = iLoc;
				//Characters[idx].location.locator = sLocType + locNum[locI];
				// boal random place to star battle 28/11/03 <--
				ChangeCharacterAddressGroup(&Characters[idx], locationID, "rld", sLocType + locNum[locI]);
				logined = logined + 1;
			}
		}
		//Перегружаемся в локацию
		boarding_location = locIndex;
				
		if(LoadLocation(&Locations[boarding_location]))
		{
			//работа с сундуком в каюте boal -->
			if (CheckAttribute(&Locations[boarding_location], "CabinType"))
			{
				FillAboardCabinBox(&Locations[boarding_location], boarding_enemy);
			}  
			//Расставляем персонажей
			LAi_SetBoardingActors(locationID);
			// boal <--
			//Вытащим саблю
			LAi_InstantFightMode(PChar);
			//Запретим диалог
			dialogDisable = true;
		}else{
			Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
		}
	}else{
		Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	}
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 100);
}

//Перегрузиться в следующую локации
void LAi_ReloadBoarding()
{
//	Log_TestInfo("ReloadBoarding()");
	//Разрешим диалоги
	dialogDisable = false;
	//Проверим предыдущую локацию
	if(boarding_location < 0)
	{
		Trace("Boarding: No loaded current boarding location");
		LAi_boarding_process = false;
		return;
	}
	//Установить хендлеры для обработки
	SetEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade", 0);
	//Создаём фейдер и запускаем
	CreateEntity(&boarding_fader, "fader");
	string nextDeck = Locations[boarding_location].boarding.nextdeck;
	if (nextDeck != "")
	{
		//SendMessage(&boarding_fader, "ls", FADER_PICTURE0, "interfaces\card_desk.tga");
		if(CheckAttribute(&Locations[FindLocation(nextDeck)], "image"))
		{
			SendMessage(&boarding_fader, "ls", FADER_PICTURE0, GetRandomLoadingPic(Locations[FindLocation(nextDeck)].image));
		}
	}
	float fadeOutTime = RELOAD_TIME_FADE_OUT;
	SendMessage(&boarding_fader, "lfl", FADER_OUT, fadeOutTime, false);
	SendMessage(&boarding_fader, "l", FADER_STARTFRAME);
}

void LAi_ReloadStartFade()
{
	//Выгружаем локацию
	if (LAi_boarding_process && HasAttrValue(&InterfaceStates, "ContinuousMusic.Boarding", "1"))
		TEV.Music.KeepPlaying = ""; // KZ > непрерывная музыка в процессе абордажа корабля/форта
	
	ResetSound();
	
	SendMessage(&Particles,"l", PS_CLEAR_CAPTURED);
	DelEventHandler("FaderEvent_StartFade", "LAi_ReloadStartFade");
	if(boarding_location >= 0) UnloadLocation(&Locations[boarding_location]);
}

void LAi_ReloadEndFade()
{        
	bool bCaptanSurrender = false;
	int eclass = sti(GetCharacterShipClass(boarding_enemy)); // класс корабля противника
	//Загружаем следующую локацию
	DelEventHandler("FaderEvent_EndFade", "LAi_ReloadEndFade");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	//Определим возможность продолжения перегрузок
	bool canReload = true;
	// Jason: во всех инсайдах и добавочных локациях форта число расчётных тушек х2, по рез.тестов возможно, будет дифференциация по типам инсайдов.
	if(CheckAttribute(&Locations[boarding_location], "UpDeckType"))
	{
		boarding_enemy_crew = inside_ecrew_1*2; // увеличиваем внутри число тушек вдвое
	}
	else boarding_enemy_crew = inside_ecrew_2*2; // увеличиваем внутри число тушек вдвое
	
	if(IsFort)
    {
		if(CheckAttribute(&Locations[boarding_location], "insidenext")) boarding_enemy_crew = inside_ecrew_2*2;
		else boarding_enemy_crew = inside_ecrew_1*2;
	}
	//if(boarding_enemy_crew <= 0) canReload = false;
	if(!CheckAttribute(&Locations[boarding_location], "boarding.nextdeck")) canReload = false;
	if(Locations[boarding_location].boarding.nextdeck == "") canReload = false;
	
 	if(canReload) //Jason Продолжаем абордаж
	{
		Trace("Boarding: go to inside location");
		LAi_LoadLocation(Locations[boarding_location].boarding.nextdeck, -1);
	}
    else
    {
		if (CheckAttribute(boarding_enemy, "ShipCabinLocationId"))
		{
            if (!CheckAttribute(boarding_enemy, "DontRansackCaptain")) //квестовые не сдаются
	        {
	            Surrendered = (Surrendered) || (TestRansackCaptain);
	    		if (Surrendered && (boarding_location_type == BRDLT_SHIP))
	    		{
	    		    bCaptanSurrender = true;    // это уже не первая палуба точно, значит потери были
	   			}
	    	}
    		if (!bCaptanSurrender)
    		{
				boarding_enemy_crew = 1;
				if(CheckAttribute(&Locations[FindLocation(boarding_enemy.ShipCabinLocationId)], "image"))
				{
					//SendMessage(&boarding_fader, "ls", FADER_PICTURE0, "interfaces\card_desk.tga");
					SendMessage(&boarding_fader, "ls", FADER_PICTURE0, GetRandomLoadingPic(Locations[FindLocation(boarding_enemy.ShipCabinLocationId)].image));
				}
				LAi_LoadLocation(boarding_enemy.ShipCabinLocationId, -1);
				DeleteAttribute(boarding_enemy, "ShipCabinLocationId"); // чтоб не зациклилось
				return;
			}
		}
  		if (CheckAttribute(pchar, "GenQuest.QuestAboardCaptanSurrender")) // квестовая сдача в плен кэпа
		{
		    DeleteAttribute(pchar, "GenQuest.QuestAboardCaptanSurrender"); // разово
		    bCaptanSurrender = true;
		}
		if (bCaptanSurrender)
			ResetSoundBoarding();
		SendMessage(&Particles,"l", PS_CLEAR_CAPTURED); // повторное удаление партиклов, фикс огней в море.
		//Следующей локации нет
		DelEventHandler("LAi_event_GroupKill", "LAi_BoardingGroupKill");
		boarding_location = -1;
		//Пересчитываем команду игрока

		float crew = boarding_player_crew * boarding_player_crew_per_chr; // ВЫЖИВШИЕ офицеры - это не мартросы не должны влиять
		// boal 22.01.2004 -->
		ref mchar       = GetMainCharacter();
		float fDefenceSkill = 0.9 + MakeFloat(GetSummonSkillFromName(mchar, SKILL_DEFENCE)) / SKILL_MAX;
		int deadCrew    = makeint((boarding_player_base_crew - crew) / fDefenceSkill + 0.3); // бонус выжившим
		if (GetOfficersPerkUsing(pchar, "Capellan2", false)) deadCrew = makeint(deadCrew*0.5); //Jason, капеллан на борту - потери в 2 раза меньше
		int deadCrewWOMedic = makeint(boarding_player_base_crew - crew); // без бонуса
		float leaderSkill = GetSummonSkillFromNameToOld(mchar, SKILL_LEADERSHIP);
		int iTemp;
		if (leaderSkill < 1) leaderSkill = 1; //fix
		
		// расчёт медицины -->
		iTemp = deadCrewWOMedic - deadCrew;
		if(CheckShipSituationDaily_GenQuest(pchar) > 1) 
		{
			if(iTemp > 0 && !CheckCharacterPerk(pchar, "Sanitary"))
			{
				deadCrew += deadCrewWOMedic; // если эпидемия - матросы не лечатся, лекарство не потребляется
			}	
		}	
		else
		{
			if (iTemp > 0)
			{
				if (GetCargoGoods(mchar, GOOD_MEDICAMENT) < iTemp)
				{
					deadCrewWOMedic = iTemp - GetCargoGoods(mchar, GOOD_MEDICAMENT); // умерли от ран
					RemoveCharacterGoodsSelf(mchar, GOOD_MEDICAMENT, GetCargoGoods(mchar, GOOD_MEDICAMENT)); // все нулим
					deadCrew += deadCrewWOMedic; // трупов больше
					Log_Info(StringFromKey("InfoMessages_70", FindSailorString(deadCrewWOMedic, "No")));
				}
				else
				{
					RemoveCharacterGoodsSelf(mchar, GOOD_MEDICAMENT, iTemp);
					if (GetCargoGoods(mchar, GOOD_MEDICAMENT) < 16)
					{
						Log_Info(StringFromKey("InfoMessages_71", UpperFirst(XI_ConvertString("musicmod_s")), mchar.Ship.Name));
					}
				}
			}
		}
		// расчёт медицины <--

        bQuestCheckProcessFreeze = false;//fix
        
		RemoveCharacterGoodsSelf(mchar, GOOD_WEAPON, deadCrew);
		
		crew = boarding_player_base_crew - deadCrew; // выжившие с бонусом
		Statistic_AddValue(mchar, "Sailors_dead", deadCrew);
		Statistic_AddValue(mchar, "DeadCrewBoard", deadCrew);
		
		AddCharacterExpToSkill(mchar, "Defence", makeint(deadCrew / 3 + 0.5)); //качаем защиту
        AddCharacterExpToSkill(mchar, "Grappling", makeint(deadCrew / 3 + 0.5));
                	
		// после боя падает мораль
		if (deadCrew > makeint(crew+0.3)) // погибло больше, чем выжило
		{
      		AddCrewMorale(mchar, sti(-20 / leaderSkill));
		}
		else
		{  //растет, если потерь мало
			AddCrewMorale(mchar, sti(leaderSkill));
		}

		// boal 22.01.2004 <--
		SetCrewQuantityOverMax(GetMainCharacter(), MakeInt(crew + 0.3)); // десант весь ГГ как перегруз команды
		Log_TestInfo("----- в конце стало " + FindSailorString(sti(crew), "No") + " ---");
		//Пересчитываем команду соперника
		crew = 0;// какие ещё люди? все трупы! boarding_enemy_base_crew*(0.1 + rand(20)*0.01);
		if (boarding_echr_index >= 0)
		{
			SetCrewQuantity(&Characters[boarding_echr_index], MakeInt(crew + 0.3));
			boarding_echr_index = -1;
		}

		//Начислим опыт
		//AddCharacterExp(GetMainCharacter(), MakeInt(boarding_exp));
                
		//Настроим интерфейс
		Log_SetActiveAction("Nothing");
		EndBattleLandInterface();
		//Востановим адреса
		ref mchr = GetMainCharacter();
		mchr.location         = boarding_adr[0].location;
		mchr.location.group   = boarding_adr[0].group;
		mchr.location.locator = boarding_adr[0].locator;
		
		for(int i = 1; i < 4; i++)
		{
			int idx = GetOfficersIndex(GetMainCharacter(), i);
			if(idx < 0) continue;
			Characters[idx].location         = boarding_adr[i].location;
			Characters[idx].location.group   = boarding_adr[i].group;
			Characters[idx].location.locator = boarding_adr[i].locator;
		}
		//Выгружаемся в интерфейс
		LAi_boarding_process = false;
		// START MOD Code by Stone-D : 27/07/2003
        if (bCaptanSurrender)
        {
			ChangeCrewExp(pchar, "Soldiers", 4);
			
			if (GetCharacterShipClass(pchar) < 7) // на 7-ом классе нет трюма (пока?!)
			{
				int bonus, trophy = 1;
				LootCollectorCompensation(boarding_enemy); // KZ > компенсация лута, если нарвались на капитулянта; кэп сдался не сразу
				
				if (eclass < 4)
					trophy = 2;
				
				for (bonus = 0; bonus < trophy; bonus++)
				{
				    LootCollectorRandItems();
				}

			}
			
			LAi_SetCurHPMax(boarding_enemy);  // нужно, чтоб был живой!!!
			SetCrewQuantity(boarding_enemy, MakeInt(boarding_enemy_base_crew*(rand(20)*0.01))); // раз кэп живой, то можно раненых воскресить
			LaunchRansackMain(pchar, boarding_enemy, "captain"); //капитан в плен
			LAi_boarding_process = false;
			Event(SHIP_CAPTURED, "l", sti(boarding_enemy.index));
			return;
		}
		// END MOD Code by Stone-D : 27/07/2003
		if(boarding_location_type == BRDLT_SHIP)
		{
			ResetSoundBoarding();
		    ChangeCrewExp(pchar, "Soldiers", 5);
		    // нельзя это делать до формы, критерий будет "" LAi_SetCurHP(boarding_enemy, 0.0); // умер, чтоб на форме обмена не жил
			LaunchRansackMain(pchar, boarding_enemy, ""); //не сдался
			LAi_boarding_process = false;	 
			Event(SHIP_CAPTURED, "l", sti(boarding_enemy.index));
			return;
		}
		if(boarding_location_type == BRDLT_FORT)
		{
			if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Attack", "1"))
				TEV.Music.ForceKeepPlaying = "";
			else
				ResetSoundBoarding();

            ChangeCrewExp(pchar, "Soldiers", 7);
			Event(FORT_CAPTURED, "l", sti(boarding_enemy.index));
			boarding_enemy.Ship.Crew.Quantity = 10 + rand(350); // рабы (остатки выживших)
			LaunchFortCapture(boarding_enemy);
			LAi_boarding_process = false;
			return;
		}
		Trace("Boarding: unknow boarding location type");
		Log_TestInfo("Boarding - unknown boarding location type : " + boarding_location_type);
	}
}

void ResetSoundBoarding()
{
	DeleteAttributeMass(&TEV, "Music", "KeepPlaying,ForceKeepPlaying,ForcePlayTrack");
	ResetSoundScheme();
	if (musicID > 0) StopSound(musicID, 0);
	musicID = -1;
	StopSound(0, 0);
	PauseAllSounds();
}

//Разрешить перегрузку на следующую палубу
#event_handler("LAi_event_boarding_EnableReload", "LAi_EnableReload");
void LAi_EnableReload()
{
	if (boardM == 1)
	{
		ResetSoundScheme(); //надо гасить только Scheme, иначе партиклы звука на кострах, факелах, и прочем - не пашут
		SetSoundScheme("deck"); // обычная схема
		boardM = -1;
	}
	Surrendered = CheckForSurrender(GetMainCharacter(), boarding_enemy, 2); // проверка сдачи в плен, перед каютой 2 - второй учет метода

	SetEventHandler("Control Activation","LAi_ActivateReload",1);
//	if (boarding_location_type != BRDLT_SHIP) Log_SetActiveAction("Reload"); // belamour убрать замок во время абордажа корабля
	if(CheckAttribute(loadedlocation, "CabinType")) Log_SetActiveAction("BoardingEnd");
	else Log_SetActiveAction("BoardingReload"); // belamour legendary edition бутафория
	//Уберём саблю
	ref mchr = GetMainCharacter();
	SendMessage(&mchr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", 0);
	
	if (CheckAttribute(&TEV, "LootCollector.Mode") && !HasStrEx(loadedLocation.type, "boarding_cabine,residence", "|"))
	{
		if (sti(TEV.LootCollector.Mode) == 3)
		{
			if (LootCollectorCheckCrew())
			{
				TEV.LootCollector.Transfer = "1";
				//PlaySound("Gotcha");
				Log_Clear();
				LogSound_WithNotify(StringFromKey("InfoMessages_72")+"&"+StringFromKey("InfoMessages_73"), "Notebook_1", "ShipCrew");
				LootCollectorTransferItemsToShip(false);
			}
			else
				DeleteAttributeMass(&TEV, "LootCollector", "CanBeRun,Transfer");
		}
		else
		{
			if (sti(TEV.LootCollector.Mode) > 0)
			{
				TEV.LootCollector.CanBeRun = true;
				
				if (sti(TEV.LootCollector.Mode) == 2)
				{
					LootCollector();
					//PlaySound("Gotcha");
				}
				else
				{
					if (sti(TEV.LootCollector.Mode) == 1)
						Log_Info(StringFromKey("InfoMessages_74"));
				}
			}
			else
				DeleteAttributeMass(&TEV, "LootCollector", "CanBeRun,Transfer");
		}
	}
	
	// sd -->
	Log_TestInfo("Start boarding_enemy_crew_start: " + boarding_enemy_crew_start + " boarding_enemy_crew: " + boarding_enemy_crew);
	Log_TestInfo("Start boarding_player_crew_start: " + boarding_player_crew_start + " boarding_player_crew: " + boarding_player_crew);
	// sd <--
	
	//Вернём выживших обратно в кучу
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int index = LAi_loginedcharacters[i];
		if (index >= 0)
		{
			if (index != GetMainCharacterIndex())
			{
				ref chr = &Characters[index];
				if (!LAi_IsDead(chr) && !IsOfficer(chr) && chr.model.animation != "mushketer") // boal && sd не нужны офицеры для матросов
				{
					if (chr.chr_ai.group == LAI_GROUP_PLAYER)
					{
						boarding_player_crew = boarding_player_crew + 1;
						//hardCoffee матросы ходят по палубе
						LAi_SetCitizenTypeNoGroup(chr);
						LAi_tmpl_cabin_InitTemplate(chr);
					}
				}
			}
		}
	}
	// Jason: перебираем классы кораблей и определяем следующую палубу
	int eclass = sti(GetCharacterShipClass(boarding_enemy)); // класс корабля противника
	if (CheckAttribute(&Locations[boarding_location], "UpDeckType"))
	{
		switch (eclass)
		{
			case 1: Locations[boarding_location].boarding.nextdeck = "Boarding_GunDeck"; break;
			case 2: Locations[boarding_location].boarding.nextdeck = "Boarding_GunDeck"; break;
			case 3: Locations[boarding_location].boarding.nextdeck = "Boarding_Campus"; break;
			case 4: Locations[boarding_location].boarding.nextdeck = "Boarding_Campus"; break;
			case 5: Locations[boarding_location].boarding.nextdeck = "Boarding_Cargohold"; break;
			case 6: Locations[boarding_location].boarding.nextdeck = "Boarding_Cargohold"; break;
			case 7: Locations[boarding_location].boarding.nextdeck = ""; break;
		}
	}
	if (IsFort && Locations[boarding_location].boarding.nextdeck == "Boarding_bastion")
	{
		Locations[boarding_location].boarding.nextdeck = "Boarding_bastion"+(drand(1)+1);
	}
	
	// evganat - энциклопедия
	if (!ENCYCLOPEDIA_DISABLED && IsFort && HasSubStr(Locations[boarding_location].id, "Boarding_bastion"))
	{
		if (CheckRandomPage("fort", "", -1))
		{
            notification(StringFromKey("InfoMessages_75"), "Document");
			GetPage(GetRandomTome(), 1);
		}
	}

	// END MOD Code by Stone-D : 01/08/2003 -->
	Log_TestInfo("New boarding_player_crew: " + boarding_player_crew);
	Log_TestInfo("Next Location: " + Locations[boarding_location].boarding.nextdeck);
	Log_TestInfo("Enemy ship class: " + eclass);
	// END MOD Code by Stone-D : 01/08/2003 <--
}

//Активация перегрузки на следующую палубу
void LAi_ActivateReload()
{
	string controlName = GetEventData();
	if(controlName != "ChrAction") return;
	DelEventHandler("Control Activation", "LAi_ActivateReload");
	Log_SetActiveAction("Nothing");
	LAi_ReloadBoarding();
}

//Расставить персонажей для боя
void LAi_SetBoardingActors(string locID)
{
    int    limit, i, iQty;
	ref    chr;
	string model, ani, sTemp;
	int    xhp;
	int    locIndex = FindLocation(locID);
	int    mclass = GetCharacterShipClass(GetMainCharacter());
	int    eclass = GetCharacterShipClass(boarding_enemy);
	int    iNation = sti(boarding_enemy.nation);
	ref    mchr = GetMainCharacter(); // boal star with new loc always
    int    locMChar;
    
	limit = MAX_GROUP_SIZE;
	// локаторов разное число на моделях. Переделал все на инфу из кода boal 01.01.05  +1 всегда для ГГ
	chr = &Locations[locIndex];
	
	if(CheckAttribute(chr, "boarding.locatorNum")) limit = sti(chr.boarding.locatorNum);

	Log_TestInfo("Location: " + locID + " Limit: " + limit);
	Log_TestInfo("Player: " + boarding_player_crew + " x " + boarding_player_crew_per_chr + " Enemy: " + boarding_enemy_crew + " x " + boarding_enemy_crew_per_chr);

	//Установим союзников из команды
	// boal прежде всего ставим офицеров, коротых в фотре почему-то нет -->
	/*if (IsFort) // boal 21.01.05 не прошло и года... починил в другом месте - правильно
	{
        for(i = 1; i < 4; i++)
		{
			int idx = GetOfficersIndex(mchr, i);
			if(idx < 0) continue;
            // boal 05.09.03 offecer need to go to abordage -->
		    if(makeint(Characters[idx].AbordageMode) == 0) continue;	// не берем
		    // грузим сами насильно уже в сущ локацию
		    chr = &Characters[idx];
		    PlaceCharacter(chr, mchr.location.group, mchr.location);
		}
	} */
	// boal прежде всего ставим офицеров, коротых в форте почему-то нет <--
    string sLocType = "loc";
	// определение стороны на палубе
	if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
	{
	    sLocType = ChooseShipUpDeck(mchr, boarding_enemy);
	}
	if (!CheckAttribute(&Locations[locIndex], "CabinType"))
	{
		// не грузим матросов в каюту
		for(i = LAi_numloginedcharacters; i < limit; i++)
		{
			if(boarding_player_crew <= 0) break;
			model = LAi_GetBoardingModel(mchr, &ani);
			// boal star with new loc always  -->
			if (mchr.location.locator == (sLocType + i))
			{ // искодим из того, что наша локация всегда < 4 офицеры пусть накладываются а матросик идет к противнику
	           locMChar = rand(3);
	           while (mchr.location.locator == (sLocType + locMChar))
	           {
	               locMChar = rand(3);
	           }
		       chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType+locMChar);// 0-всегда свободен, если офицеров нет, а i != 0, тк мы точно есть
			}
			else
			{
			   chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType + i);
			}
			// boal star with new loc always  <--

			LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);

			boarding_player_crew = boarding_player_crew - 1;
			// boal расчёт как у нормальных фантомов -->
			//LAi_SetAdjustFencingSkill(chr, 3.0, 6.0);
			//LAi_AdjustFencingSkill(chr);

			// boal <--
			SetFantomParamOur(chr, false);

			SetNewModelToChar(chr); //иначе сабли не те, что реально
			chr.AboardFantom = true;
		}
		//ставим своих мушкетеров -->		
		if (CheckOfficersPerk(mchr, "MusketsShoot") || IsFort)
		{
			//AlexBlade - мушкетеры в форте, по умолчанию не работали
			if (IsFort)
			{
				iQty = 3;
				for(i=0; i<iQty; i++)
				{
					model = LAi_GetBoardingMushketerModel(mchr);
					chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", 5, sti(mchr.nation), 0, false));
					chr.id = "GenChar_" + chr.index;
					chr.AboardFantom = true;
					chr.MusketerDistance = 10.0;
					LAi_SetWarriorType(chr);
					LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
					ChangeCharacterAddressGroup(chr, locID, "rld", sLocType + i);
					SetFantomParamOur(chr, true);
				}
			} 
			else 
			{
				if (CheckAttribute(&Locations[locIndex], "UpDeckType") && !CheckAttribute(boarding_enemy, "CrewType.Skel"))
				{
					iQty = 2;
					for(i=1; i<=iQty; i++)
					{
						if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
						{
							model = LAi_GetBoardingMushketerModel(mchr);		
							chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", 5, sti(mchr.nation), 0, false));
							chr.id = "GenChar_" + chr.index;
							chr.AboardFantom = true;
							chr.MusketerDistance = 0;
							LAi_SetWarriorType(chr);
							LAi_group_MoveCharacter(chr, LAI_GROUP_PLAYER);
							ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);
							SetFantomParamOur(chr, true);
						}
					}			
				}
			}
		}
		//<-- ставим своих мушкетеров
	}
	//Установим врагов
	if (sLocType == "loc")
	{
	    sLocType = "aloc";
	}
	else
	{
	    sLocType = "loc";
	}
	arrayNPCModelHow = 0;
	
	for(i = 0; i < limit; i++) // <= тк loc0 .. loc4 = 5
	{
		if (boarding_enemy_crew <= 0) break;
		model = LAi_GetBoardingModel(boarding_enemy, &ani);
		if (i == 0 && CheckAttribute(&Locations[locIndex], "boarding.Loc.Capt")) //локатор каюты
		{
		    chr = LAi_CreateFantomCharacterEx(model, ani, "rld", Locations[locIndex].boarding.Loc.Capt);
		}
		else
		{
			chr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocType + i);
		}
		
		//Rosarak Разнообразие моделек
		chr.nation = boarding_enemy.nation;
		if (HasSubStr(boarding_enemy.model, "merch_")) //Ship.Mode == "Trade" не всем ставится
				sTemp = "sailor_merchant";
		else	sTemp = GetModelType(model);
		SetNPCModelUniq(chr, sTemp, MAN);
		
		LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);
		
		boarding_enemy_crew = boarding_enemy_crew - 1;

		if (i == 0 && CheckAttribute(&Locations[locIndex], "CabinType")) //Спавним капитана
		{
			ChangeAttributesFromCharacter(chr, boarding_enemy, true);
			chr.CaptanId = boarding_enemy.id; // иначе у фантома свой ИД   // TODO поправить опечатку
			boarding_enemy.CaptanId = boarding_enemy.id;
			//капитану даем оружие получше, если можно
			if (!CheckAttribute(chr, "SaveItemsForDead"))
					LAi_NPC_Equip(chr, sti(chr.rank), true, true);
			chr.SuperShooter = true; // супер стрелок (вероятность пальбы выше, от сложности, если ещё и пистоль есть)
			
			// evganat - энциклопедия
			if(eclass <= 3)
			{
				if(CheckRandomPage("captain", "", eclass))
				{
					chr.encyclopedia.tome = GetRandomTome();
					chr.encyclopedia.page = 1;
				}
			}
			
			if (boarding_enemy.sex == "man") chr.greeting = "CapSinkShip";
			SetCharacterPerk(chr, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, дается ГГ и боссам уровней
			if (CheckAttribute(chr,"Situation"))
			{
				if(bSeaCanGenerateShipSituation) SetQuestAboardCabinDialogSituation(chr);
				else DeleteAttribute(chr,"Situation");
			}
			else
			{
				CaptainComission_GenerateSituation(chr);
				SetQuestAboardCabinDialog(chr); /// проверка на минНр
				SetQuestAboardCabin_CheckCaptain(chr);
			}	
			// если это место отработало, то кэп либо убит, либо по квестам сдаётся в плен
			// 1.2.3 эффект кирасы
			//if (CheckCharacterPerk(chr, "Ciras"))
			//{
		    xhp = makeint((MOD_SKILL_ENEMY_RATE*2+sti(chr.rank))/10.0);

		    if (xhp > 0)
		    {
		        if (xhp >= 5) xhp = 5;
		        // путаница с 3  и 4 кирасами (меняем)
		        if (xhp == 3)
				{
					xhp = 4;
				}
				else
				{
				    if (xhp == 4) xhp = 3;
				}
				model = "cirass" + xhp;
				chr.cirassId = FindItem(model);
				Log_TestInfo("На капитане кираса " + model);
		    }
			//}
		}
		else SetFantomParamEnemy(chr, false);
		SetNewModelToChar(chr); //иначе сабли не те, что реально
		chr.AboardFantom = true;

		// Jason: на палубе уменьшаем хитпоинты вражеским тушкам до 85% от расчётного
		int ihp;
		if (CheckAttribute(&Locations[locIndex], "UpDeckType"))
		{
			ihp = LAi_GetCharacterHP(chr)*0.85+0.5;
			LAi_SetHP(chr, ihp, ihp);
		}
		// Jason: в инсайдах уменьшаем хитпоинты вражеским тушкам, т.к. возросло вдвое их количество
		if (CheckAttribute(&Locations[locIndex], "InsideDeckType") || CheckAttribute(&Locations[locIndex], "AddFortType"))
		{
			ihp = LAi_GetCharacterHP(chr)/1.5;
			LAi_SetHP(chr, ihp, ihp);
		}
	}
	//ставим вражеских мушкетеров -->
	if (CheckCharacterPerk(boarding_enemy, "MusketsShoot") || IsFort)
	{
		//AlexBlade - мушкетеры в форте, по умолчанию не работали
		if (IsFort)
		{
			iQty = 3;
			for(i=0; i<iQty; i++)
			{
				chr = SetFantomDefenceForts("rld", sLocType + i, sti(boarding_enemy.nation), LAI_GROUP_BRDENEMY, "fort_mush");
				chr.AboardFantom = true;
				chr.MusketerDistance = 0;
				SetFantomParamEnemy(chr, true);
			}
		} 
		else 
		{
			if (CheckAttribute(&Locations[locIndex], "UpDeckType") && !CheckAttribute(boarding_enemy, "CrewType.Skel"))
			{
				iQty = 2;
				for(i=1; i<=iQty; i++)
				{
					if (LAi_CheckLocatorFree("rld", sLocType+"mush"+i))
					{
						model = LAi_GetBoardingMushketerModel(boarding_enemy);		
						chr = GetCharacter(NPC_GenerateCharacter("GenChar_", model, "man", "mushketer", 5, sti(boarding_enemy.nation), 0, false));
						chr.id = "GenChar_" + chr.index;
						chr.AboardFantom = true;
						chr.MusketerDistance = 0;
						LAi_SetWarriorType(chr);
						LAi_group_MoveCharacter(chr, LAI_GROUP_BRDENEMY);
						ChangeCharacterAddressGroup(chr, locID, "rld", sLocType+"mush"+i);
						SetFantomParamEnemy(chr, true);
					}
				}			
			}
		}
		
	}
	//<-- ставим вражеских мушкетеров
	//Заставим драться эти 2 группы
	LAi_group_FightGroupsEx(LAI_GROUP_PLAYER, LAI_GROUP_BRDENEMY, true, GetMainCharacterIndex(), -1, false, false);
	LAi_group_SetCheckEvent(LAI_GROUP_BRDENEMY);
}

void SetFantomParamEnemy(ref rChr, bool bMushketer) // ~!mu
{
	rChr.EnemyRank = boarding_enemy.rank;
	if (bonus_enemy_rank > 0) rChr.RankBonus = bonus_enemy_rank;

    CalculateAppropriateSkills(rChr);
    SetFantomHP(rChr);

	if (!bMushketer)
	{
		DeleteAttribute(rChr, "Items");
		LAi_NPC_Equip(rChr, sti(rChr.rank), true, true);
	}

	DeleteAttribute(rChr, "EnemyRank");
    DeleteAttribute(rChr, "RankBonus");

	AddCharHP(rChr, bonus_enemy_hp);
	if (CheckOfficersPerk(boarding_enemy, "Prevention"))
		AddCharHP(rChr, makeint(stf(rChr.chr_ai.hp_max) / 10));
}

void SetFantomParamOur(ref rChr, bool bMushketer) // ~!mu
{
	rChr.OurMan = true;
	if (bonus_player_rank > 0) rChr.RankBonus = bonus_player_rank;

    CalculateAppropriateSkills(rChr);
    SetFantomHP(rChr);

	if (!bMushketer)
	{
		DeleteAttribute(rChr, "Items");
		LAi_NPC_Equip(rChr, sti(rChr.rank), true, true);
	}

	DeleteAttribute(rChr, "OurMan");
    DeleteAttribute(rChr, "RankBonus");

	AddCharHP(rChr, bonus_player_hp); // влияение опыта и морали в НР
	if (CheckOfficersPerk(pchar, "Prevention")) // KZ > работа перка "Профилактика" - увеличивает общее здоровье абордажной команды на 10% во время сражения
		AddCharHP(rChr, makeint(stf(rChr.chr_ai.hp_max) / 10));
}

//Убийство группы
void LAi_BoardingGroupKill()
{
	string group = GetEventData();
	if(group != LAI_GROUP_BRDENEMY) return;
	// отключим шум абордажа (который включается при аларме в sound.c)

	PostEvent("LAi_event_boarding_EnableReload", 5000);
}

//Моделька для абордажного персонажа
string LAi_GetBoardingModel(ref rCharacter, ref ani)
{
	aref models;
	ani = "man";
	int iNation = sti(rCharacter.nation);
	string atr;
	string model;
	
	int shClass = GetCharacterShipType(rCharacter);
	if (shClass != SHIP_NOTUSED)
	{
		ref rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
		shClass = sti(rBaseShip.Class);
	}
	
	//Особые команды
	if (CheckAttribute(rCharacter, "CrewType"))
	{
		makearef(models,rCharacter.CrewType);
		switch(GetAttributeName(GetAttributeN(models,0)))
		{
			case "Skel": return GetRandSkelModel(); break;
			case "Smugglers": return "citiz_"+(rand(9)+21); break;
			case "Draugr": return "Draugr_"+(rand(7)+1); break;
		}
	}

	if(sti(rCharacter.index) == GetMainCharacterIndex())
	{
		//Национальная форма; TODO (обсудить): Адмиралам всегда ветеранов
		if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1)
		{
			if(shClass == 1) atr = "boardingModel.enemy_elite";
			else atr = "boardingModel.enemy";
			iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
		}			//Матросы
		else atr = "boardingModel.player";
	}
	else
	{
		//По нации
		if(shClass == 1) atr = "boardingModel.enemy_elite";
		else atr = "boardingModel.enemy";
		
		//Армия в форте
		if (CheckAttribute(rCharacter, "Fort"))
		{
			atr = "fantomModel";	
		}
		
		//Торговцы
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Trade")
		{
			atr = "boardingModel.merchant";
		}
	}
	
	if (iNation < 0) iNation = PIRATE;
	//eddy. замаскировавшися пиратов тоже надо учитывать
	if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Pirate" && !IsMainCharacter(rCharacter)) iNation = PIRATE;
	if (iNation == PIRATE && shClass < 3 && !IsMainCharacter(rCharacter)) atr = "boardingModel.enemy_elite"; //watch_type
	
	makearef(models, Nations[iNation].(atr));
	int num = GetAttributesNum(models);
	if(num <= 0) return "";
	int i = rand(num - 1);
	atr = GetAttributeName(GetAttributeN(models, i));
	model = models.(atr);
	atr = atr + ".ani";
	if(CheckAttribute(models, atr))
	{
		if(models.(atr) != "")
		{
			ani = models.(atr);
		}
	}
	return model;
}

string LAi_GetBoardingMushketerModel(ref rCharacter)
{
	string model;
	int iNation = sti(rCharacter.nation);
	
	int shClass = GetCharacterShipType(rCharacter);
	if (shClass != SHIP_NOTUSED)
	{
		ref rBaseShip = GetRealShip(sti(rCharacter.Ship.Type));
		shClass = sti(rBaseShip.Class);
	}
	
	//TODO: Команда скелетов
	/*if (CheckAttribute(rCharacter, "CrewType.Skel"))
	{
		return GetRandSkelModelMush();
	}*/
	
	if(sti(rCharacter.index) == GetMainCharacterIndex())
	{
		//Национальная форма; TODO (обсудить): Адмиралам всегда ветеранов
        if (isMainCharacterPatented() && sti(Items[sti(rCharacter.EquipedPatentId)].TitulCur) > 1)
        {
            iNation = sti(Items[sti(rCharacter.EquipedPatentId)].Nation);
        }			//Матросы
        else return "mush_ctz_"+(rand(2)+4);
	}
	else
    {
		//Армия в форте
		if (CheckAttribute(rCharacter, "Fort"))
		{
			if(iNation == PIRATE) return "mush_ctz_" + (rand(2)+7); //Пираты
			return "navy_mush_" + NationShortName(iNation) + "_" + (rand(2)+1); //Флот
		}
		//Торговцы
		if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Trade")
		{
            return "mush_ctz_"+(rand(2)+1);
        }
		else
        {	//По нации
            iNation = sti(rCharacter.nation);
        }
	}
	
	if (iNation < 0) iNation = PIRATE;
	//eddy. замаскировавшися пиратов тоже надо учитывать
	if (CheckAttribute(rCharacter, "Ship.Mode") && rCharacter.Ship.Mode == "Pirate" && !IsMainCharacter(rCharacter)) iNation = PIRATE;
	if(iNation == PIRATE)
	{
		if(shClass < 3) model = "mush_ctz_" + (rand(2)+10); //Элитные наёмники
		else model = "mush_ctz_" + (rand(2)+7); //Пираты
	}
	else
	{
		if(shClass == 1) model = "navy_mush_" + NationShortName(iNation) + "_" + (rand(2)+4); //Ветераны
		else model = "navy_mush_" + NationShortName(iNation) + "_" + (rand(2)+1); //Флот
	}	
	return model;
}

// boal 03/08/06 полностью переписал метод Stone-D от 27/07/2003
bool CheckForSurrender(ref mchr, ref echr, int _deck)
{
    if (boarding_location_type == BRDLT_FORT) return false; // Forts don't surrender.

    if (CheckAttribute(echr, "AlwaysSurrender")) return true; // всегда сдаются (для квестовых нужд)
    
    if (GetPrisonerQty() > PRISONER_MAX) return false; // очень много пленых
    
	if (sti(echr.rank) > (50 - MOD_SKILL_ENEMY_RATE)) return false; //max уровень кэпов

	if (!IsCharacterPerkOn(mchr,"SeaDogProfessional")) //скрытая фича-пасхалка
	{
		if (sti(mchr.rank) < (sti(echr.rank) + MOD_SKILL_ENEMY_RATE / 2))  return false; // 26/06/07 Проверка на ранг
	}
    
	int eclass = GetCharacterShipClass(echr);
	int mclass = GetCharacterShipClass(mchr);
	if (eclass == 1) return false; // 1 класс не сдаётся в принципе
	
	float fCrewRate;
	if (sti(echr.Nation) == PIRATE) fCrewRate = 0.2;
	// торговцы склонны сдаться
	else if (CheckAttribute(echr, "Ship.Mode") && echr.Ship.Mode == "Trade") fCrewRate = 0.9;
	else fCrewRate = 0.5;

	float mcrew = stf(GetWeaponCrew(mchr, GetCrewQuantity(mchr))); // честный учет с оружием
	float ecrew = stf(GetCrewQuantity(echr));
	
	float fRep    = abs(REPUTATION_NEUTRAL - sti(mchr.reputation)) / 50.0; // приведение к 0..1
	float emorale = stf(echr.ship.crew.morale) / MORALE_MAX; // 0..1  это рандом
	float mmorale = stf(mchr.ship.crew.morale) / MORALE_MAX; // 0..1
	float mskill  = (GetSummonSkillFromNameToOld(mchr, "Leadership") + GetSummonSkillFromNameToOld(mchr, "Grappling")) / 20.0;  // 0..10
	float eskill  = (GetCharacterSkillToOld(echr, "Leadership") + GetCharacterSkillToOld(echr, "Defence")) / 20.0;    // 0..10

    mcrew = mcrew * (mcrew * GetCrewExp(mchr, "Soldiers")) / (GetOptCrewQuantity(mchr) * GetCrewExpRate());
    ecrew = ecrew * (ecrew * GetCrewExp(echr, "Soldiers")) / (GetOptCrewQuantity(echr) * GetCrewExpRate());  // это рандом, а значит случайность
    mcrew = mcrew *(0.5 + mmorale);
    ecrew = ecrew *(0.5 + emorale); // рандом в  emorale - она ранд
    
    mcrew = mcrew * (0.2 + mskill)*(0.05 + fRep)*fCrewRate;
    ecrew = ecrew * (0.2 + eskill);
	// подсчет компаньонов у сторон  -->
    int mShip = GetCompanionQuantity(mchr);
    int eShip;
    string sGroupID = Ship_GetGroupID(echr);
    if (sGroupID != "")
    {
    	eShip = Group_GetLiveCharactersNum(sGroupID);
    }
    else
    {
    	eShip = 1;
    }
	// <--
	float fStep = 1;
	if (_deck == 2)
	{
		fStep = 1.4;
	}
    mcrew = mcrew * (1.0 + mclass / 20.0) * fStep; // влияние класса минимально, тк есть в экипаже
    ecrew = ecrew * (1.0 + eclass / 20.0);  // класс также влияет наоборот, даёт бонус мелким
    
    mcrew = mcrew * (1.0 + (mShip-1) / 5.0);
    ecrew = ecrew * (1.0 + (eShip-1) / 5.0);
    if (bBettaTestMode) // иначе плодил компил.лог в подзорку
    {
    	Log_Info("Surrender Hero = "+ mcrew + "    Enemy = " + ecrew + " eShipQty = " + eShip);
    }
    if (mcrew > ecrew)
	{
		return true; // Yay! Surrender!
	}
	return false; // не сдался
}

// boal 03/12/05 выбор локатора от корабля лок - маленькие, алок - большие-->
string ChooseShipUpDeck(ref _mchar, ref _enemy)
{
    string sLoc = "loc";
    
	if (GetCargoMaxSpace(_mchar) > GetCargoMaxSpace(_enemy))
	{
	    sLoc = "aloc";
	}
	
    return sLoc;
}
// boal 03/12/05 <--

// KZ > опция быстрого сбора лута реквизирована из ЧМ для КС от Cheatsurfer; механика расширена; убраны приписки "csm" в названиях методов и переменных
#event_handler(EVENT_LOCATION_LOAD, "DeleteLootCollectorBox");
#event_handler(EVENT_LOCATION_UNLOAD, "DeleteLootCollectorBox");

// Пылесосит весь лут с трупов и сундуков в абордажной локации, помещает все собранное добро в спецсундук BoxLC и запускает его обыск.
void LootCollector()
{
	aref arFader;
	
	if (GetEntity(arFader, "fader") || !IsEntity(&loadedLocation) || !LAi_IsBoardingProcess() || sti(InterfaceStates.Launched) > 0 || !CheckAttributeMass(&TEV, "LootCollector", "Mode,CanBeRun", "|") || !LootCollectorCheckCrew())
		return;

	if (!CheckAttribute(loadedLocation, "type") || HasStrEx(loadedLocation.type, "boarding_cabine,residence", "|") || sti(TEV.LootCollector.Mode) < 1 || sti(TEV.LootCollector.Mode) > 2)
		return;

	int i, j, n, iBoxes;
	float x, y, z;

	string sBox, sTemp, sAttr;

	aref arLC, arBoxLC, arBoxes, arFromBox, arFromBody, arItem;
	ref rLoc, rDeadman;

	rLoc = &Locations[FindLocation(pchar.location)];

	GetCharacterPos(pchar, &x, &y, &z);
	makearef(arLC, rLoc.locators.box.BoxLC);

	arLC.x = x;
	arLC.y = y;
	arLC.z = z;

	arLC.vx.x = 0.0;
	arLC.vx.y = 0.0;
	arLC.vx.z = 0.0;

	arLC.vy.x = 0.0;
	arLC.vy.y = 0.0;
	arLC.vy.z = 0.0;

	arLC.vz.x = 0.0;
	arLC.vz.y = 0.0;
	arLC.vz.z = 0.0;

	arLC.radius = 3.0;
	rLoc.locators_radius.box.BoxLC = 2.0;

	makearef(arBoxes, rLoc.locators.box);
	iBoxes = GetAttributesNum(arBoxes);

	if (iBoxes > 0)
	{
		if (iBoxes > MAX_HANDLED_BOXES)
			iBoxes = MAX_HANDLED_BOXES;

		for (i = 0; i < iBoxes; i++)
		{
			sTemp = GetAttributeName(GetAttributeN(arBoxes, i));

			if (sTemp == "" || HasStr(sTemp, "BoxLC"))
				continue;

			if (HasStr(sTemp, "private") && !CheckAttribute(rLoc, sTemp + ".opened"))
			{
				Log_Info(StringFromKey("InfoMessages_76"));
				PlayVoice("Notebook_1");
				continue;
			}

			if (CheckAttribute(rLoc, sTemp + ".money") && sti(rLoc.(sTemp).money) > 0)
				rLoc.BoxLC.money = sti(rLoc.BoxLC.money) + sti(rLoc.(sTemp).money);

			makearef(arFromBox, rLoc.(sTemp).items);

			n = GetAttributesNum(arFromBox);

			if (n > 0)
			{
				for (j = 0; j < n; j++)
				{
					arItem = GetAttributeN(arFromBox, j);
					sAttr = GetAttributeName(arItem);

					if (FindItem(sAttr) >= 0)
					{
						if (!CheckAttribute(rLoc, "BoxLC.items." + sAttr))
							rLoc.BoxLC.items.(sAttr) = 0;

						rLoc.BoxLC.items.(sAttr) = makeint(sti(rLoc.BoxLC.items.(sAttr)) + makeint(GetAttributeValue(arItem)));
						rLoc.(sTemp).items.(sAttr) = 0;
					}
				}
			}

			DeleteAttribute(rLoc, sTemp + ".items");
			rLoc.(sTemp).items = "";
			rLoc.(sTemp).money = 0;
		}
	}

	if (Dead_Char_num > 0)
	{
		for (i = 0; i < Dead_Char_num; i++)
		{
			rDeadman = &Dead_Characters[i];

			if (!CheckAttribute(rDeadman, "index"))
				continue;

			if (CheckAttribute(rDeadman, "money") && sti(rDeadman.money) > 0)
				rLoc.BoxLC.money = sti(rLoc.BoxLC.money) + sti(rDeadman.money);

			makearef(arFromBody, rDeadman.items);

			n = GetAttributesNum(arFromBody);

			if (n > 0)
			{
				for (j = 0; j < n; j++)
				{
					arItem = GetAttributeN(arFromBody, j);
					sAttr = GetAttributeName(arItem);

					if (FindItem(sAttr) >= 0)
					{
						if (!CheckAttribute(rLoc, "BoxLC.items." + sAttr))
							rLoc.BoxLC.items.(sAttr) = 0;

						rLoc.BoxLC.items.(sAttr) = makeint(sti(rLoc.BoxLC.items.(sAttr)) + makeint(GetAttributeValue(arItem)));
						rDeadman.items.(sAttr) = 0;
					}
				}
			}

			DeleteAttribute(rDeadman, "items");
			rDeadman.items = "";
			rDeadman.money = 0;
			//Dead_DelLoginedCharacter(rDeadman); // для упорных хомячков оставим (обыск трупов)
		}
	}
	
	TEV.LootCollector.Run = true;
	sBox = "BoxLC";
	pchar.boxname = sBox;
	makearef(arBoxLC, rLoc.(sBox));
	LaunchItemsBox(&arBoxLC);
}

// Скрыть в локе сундук BoxLC
void HideLootCollectorBox()
{
	ref rLoc;

	if (FindLoadedLocation() >= 0)
	{
		rLoc = &Locations[FindLocation(pchar.location)];

		if (CheckAttribute(rLoc, "BoxLC"))
			rLoc.locators.box.BoxLC.y = -10000.0;
	}
}

// Удалить в локе сундук BoxLC
void DeleteLootCollectorBox()
{
	ref rLoc;
	
	if (FindLoadedLocation() >= 0)
	{
		rLoc = &Locations[FindLocation(pchar.location)];

		if (CheckAttribute(rLoc, "BoxLC"))
		{	
			DeleteAttribute(rLoc, "BoxLC.items");

			rLoc.BoxLC.items = "";
			rLoc.BoxLC.money = 0;

			DeleteAttribute(rLoc, "BoxLC");
			DeleteAttribute(&TEV, "LootCollector.CanBeRun");
		}
	}
}

void LootCollectorTransferItemsToShip(bool privateBox)
{
	if (!CheckAttribute(&TEV, "LootCollector.Transfer"))
		return;
	
	DeleteAttribute(&TEV, "LootCollector.Transfer");
	DeleteAttribute(&TEV, "TransferMoney");
	ref loc, locTo, rDeadman, rItem;
	aref arFromBox, arBoxes, arItem, arFromBody;
	string sTemp, sAttr;
	int i, j, n, iBoxes;
	
	bool perkEnabled = GetOfficersPerkUsing(pchar, "HawkEye", false);
	
	if (CheckAttribute(pchar, "Fellows.Passengers.boatswain"))
	{
		if (sti(pchar.Fellows.Passengers.boatswain) >= 0)
		{
			ref npchar = GetCharacter(sti(pchar.Fellows.Passengers.boatswain));
			perkEnabled = perkEnabled || CheckCharacterPerk(npchar, "HawkEye");
		}
	}
	
	loc   = &locations[FindLocation(pchar.location)];
	locTo = &locations[FindLocation("My_Deck")];
	
	makearef(arBoxes, loc.locators.box);
	iBoxes = GetAttributesNum(arBoxes);
	
/*	if (FindLocation("My_Deck") >= 0)
	{
		if (CheckAttribute(locTo, "box1"))
			locTo.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()); // лишнее, и без этого лут в сундуке не потрётся
	}*/
	
	if (iBoxes > 0)
	{
		if (iBoxes > MAX_HANDLED_BOXES)
			iBoxes = MAX_HANDLED_BOXES;

		for (i = 0; i < iBoxes; i++)
		{
			sTemp = GetAttributeName(GetAttributeN(arBoxes, i));

			if (sTemp == "")
				continue;
			
			if (HasStr(sTemp, "private") && !privateBox)
				continue;

			if (CheckAttribute(loc, sTemp + ".money") && sti(loc.(sTemp).money) > 0)
			{
				pchar.money = sti(pchar.money) + sti(loc.(sTemp).money);
				TEV.TransferMoney.Chest = "1";
			}

			makearef(arFromBox, loc.(sTemp).items);
			n = GetAttributesNum(arFromBox);

			if (n > 0)
			{
				for (j = 0; j < n; j++)
				{
					arItem = GetAttributeN(arFromBox, j);
					sAttr = GetAttributeName(arItem);
					
					if (!CheckAttribute(&TEV, "BoxTransferItems"))
					{
						if (LootCollectorCheckAbility() && perkEnabled && HasStrEx(sAttr, "mineral,indian2,indian4,indian9,indian13,indian16", "|")) // подменяем некоторый мусор на бижу
						{
							if (sAttr != "mineral3") // свечи теперь не мусор, их собираем
								sAttr = "jewelry" + (1 + rand(8));
						}
					}
					
					if (FindItem(sAttr) >= 0)
					{
						rItem = ItemsFromID(sAttr);
						
						if (CheckAttribute(rItem, "ItemType") && rItem.ItemType == "QUESTITEMS") // квестовые вещи сразу в карман ГГ
							ItemTake(PChar, sAttr, makeint(GetAttributeValue(arItem)));
						else
						{
							if (!CheckAttribute(locTo, "box1." + sAttr))
								locTo.box1.items.(sAttr) = 0;
							
							locTo.box1.items.(sAttr) = makeint(sti(locTo.box1.items.(sAttr)) + makeint(GetAttributeValue(arItem)));
						}
						
						loc.(sTemp).items.(sAttr) = 0;
					}
				}
			}
			DeleteAttribute(loc, sTemp + ".items");
			loc.(sTemp).items = "";
			loc.(sTemp).money = 0;
		}
	}
	
	if (CheckAttribute(&TEV, "BoxTransferItems"))
	{
		DeleteAttribute(&TEV, "BoxTransferItems");
		return;
	}
	
	if (Dead_Char_num > 0)
	{
		for (i = 0; i < Dead_Char_num; i++)
		{
			rDeadman = &Dead_Characters[i];

			if (!CheckAttribute(rDeadman, "index"))
				continue;

			if (CheckAttribute(rDeadman, "money") && sti(rDeadman.money) > 0)
			{
				locTo.box1.money = sti(locTo.box1.money) + sti(rDeadman.money);
				TEV.TransferMoney.Deadman = "1";
			}

			makearef(arFromBody, rDeadman.items);
			n = GetAttributesNum(arFromBody);

			if (n > 0)
			{
				for (j = 0; j < n; j++)
				{
					arItem = GetAttributeN(arFromBody, j);
					sAttr = GetAttributeName(arItem);
					
					if (LootCollectorCheckAbility() && perkEnabled && HasStrEx(sAttr, "mineral,indian2,indian4,indian9,indian13,indian16", "|")) // подменяем некоторый мусор на бижу
					{
						if (sAttr != "mineral3") // свечи теперь не мусор, их собираем
							sAttr = "jewelry" + (1 + rand(8));
					}
					
					if (FindItem(sAttr) >= 0)
					{
						rItem = ItemsFromID(sAttr);
						
						if (CheckAttribute(rItem, "ItemType") && rItem.ItemType == "QUESTITEMS") // квестовые вещи сразу в карман ГГ
							ItemTake(PChar, sAttr, 1);
						else
						{
							if (!CheckAttribute(locTo, "box1.items." + sAttr))
								locTo.box1.items.(sAttr) = 0;
							
							locTo.box1.items.(sAttr) = makeint(sti(locTo.box1.items.(sAttr)) + makeint(GetAttributeValue(arItem)));
						}
						
						rDeadman.items.(sAttr) = 0;
					}
				}
			}
			DeleteAttribute(rDeadman, "items");
			rDeadman.items = "";
			rDeadman.money = 0;
		}
	}
	
	if (CheckAttribute(&TEV, "TransferMoney.Chest"))
		PlaySound("Took_item");
	
	if (CheckAttribute(&TEV, "TransferMoney.Deadman"))
		PlayVoice("uplata");
	
	DeleteAttribute(&TEV, "TransferMoney");
}

bool LootCollectorCheckAbility()
{
	int skillNeed, shipclassEnemy;
	ref boatswainOur;
	
	if (!CheckAttribute(boarding_enemy, "index"))
		return false;
	
	if (CheckAttribute(pchar, "Fellows.Passengers.boatswain"))
	{
		if (sti(pchar.Fellows.Passengers.boatswain) > 0)
		{
			boatswainOur = GetCharacter(sti(pchar.Fellows.Passengers.boatswain));
			
			if (!CheckAttribute(boatswainOur, "index"))
				return false;
			
			skillNeed = GetSummonSkillFromName(boatswainOur, SKILL_GRAPPLING);
			shipclassEnemy = sti(GetCharacterShipClass(boarding_enemy));
			
			if (shipclassEnemy > 5)
				return true;
			
			switch (shipclassEnemy)
			{
				case 1:
					if (skillNeed > 74)
						return true;
				break;
				case 2:
					if (skillNeed > 59)
						return true;
				break;
				case 3:
					if (skillNeed > 44)
						return true;
				break;
				case 4:
					if (skillNeed > 29)
						return true;
				break;
				case 5:
					if (skillNeed > 14)
						return true;
				break;
			}
		}
	}
	return false;
}

// KZ > генерация трофеев в сундуках и в карманах сдавшегося капитана; идея заимствована из патча Вейна для КС
void LootCollectorCompensation(ref npc)
{
	if (FindLocation("My_Deck") < 0 || GetCharacterShipClass(pchar) > 6) // TODO add > если команды 0
		return;
	
	int iEnemyShipClass = GetCharacterShipClass(npc);
	int iMoney = 0;
	int iNation = sti(npc.nation);
	ref itemRef, loc = &locations[FindLocation("My_Deck")];
	string itemID, sTemp = "";
	
	if (iEnemyShipClass < 1 || iEnemyShipClass > 7 || iNation >= MAX_NATIONS)
		return;
	
	float nLuck = GetCharacterSPECIAL(pchar, SPECIAL_L) + round_up(stf(pchar.Skill.Fortune) / 10.0) + GetFortuneBonus(5);
	
	// > личные вещи кэпа TODO добавить страницы по энциклопедии
	if (CheckAttribute(npc, "money") && sti(npc.money) > 0)
	{
		iMoney = sti(npc.money);
		npc.money = 0;
	}
	
	if (CheckAttribute(npc, "items"))
	{
		aref arItem, arFromBody;
		makearef(arFromBody, npc.items);
		int j, n = GetAttributesNum(arFromBody);
		
		for (j = 0; j < n; j++)
		{
			arItem = GetAttributeN(arFromBody, j);
			itemID = GetAttributeName(arItem);
			
			if (FindItem(itemID) >= 0)
			{
				itemRef = ItemsFromID(itemID);
				
				if (CheckAttribute(itemRef, "ItemType") && itemRef.ItemType == "QUESTITEMS") // квестовые вещи сразу в карман ГГ
					ItemTake(PChar, itemID, 1);
				else
				{
					if (!CheckAttribute(loc, "box1.items." + itemID))
						loc.box1.items.(itemID) = 0;
					
					loc.box1.items.(itemID) = makeint(sti(loc.box1.items.(itemID)) + makeint(GetAttributeValue(arItem)));
				}
				
				npc.items.(itemID) = 0;
			}
		}
		
		DeleteAttribute(npc, "items");
		npc.items = "";
	}
	// < личные вещи кэпа
	
	// > содержимое сундуков каюты
	if (iNation == PIRATE) // сдавшийся кэп - пират
	{
		if (nLuck >= rand(399) && GetCharacterItem(pchar, "map_full") == 0) // карты сокровищ
		{
			if (GetCharacterItem(pchar, "map_part1") == 0)
				AddItemLog(pchar, "map_part1", "1", StringFromKey("InfoMessages_77"), "Notebook_1");
			else
			{
				if (GetCharacterItem(pchar, "map_part2") == 0)
					AddItemLog(pchar, "map_part2", "1", StringFromKey("InfoMessages_77"), "Notebook_1");
			}
		}
		
		FillCabinBoxMap(loc, 200 - (7 - iEnemyShipClass) * 5); // карты островов архипелага пиратам
	}
	else // не пират
		FillCabinBoxMap(loc, 250 - (7 - iEnemyShipClass) * 5); // карты островов архипелага прочим нациям
	
	if (CheckAttribute(npc, "Ship.Mode") && npc.Ship.Mode == "Trade") // сдавшийся кэп - торговец
	{
		iMoney = iMoney + (10 - iEnemyShipClass) * 200 + rand(10 - iEnemyShipClass) * 2000 + rand(10)*50 + rand(6 - iEnemyShipClass) * 4000;
		
		if (nLuck >= rand(399)) // с редким шансом дадим костюм
		{
			if (rand(4) == 4)
				itemID = "suit_3"; // костюм дворянина, шанс ещё чуть ниже
			else
				itemID = "suit_2"; // костюм торговца
			
			if (FindItem(itemID) >= 0)
			{
				itemRef = ItemsFromID(itemID);
				loc.box1.items.(itemID) = sti(loc.box1.items.(itemID)) + 1;
				itemID = XI_ConvertString("suit");
				sTemp = GetConvertStr(itemRef.name, "ItemsDescribe.txt");
			}
		}
	}
	else // не торговец
	{
		iMoney = iMoney + (10 - iEnemyShipClass) * 90 + rand((10 - iEnemyShipClass) * 2000);
		
		if (nLuck >= rand(399)) // с редким шансом дадим кирасу
		{
			itemID = "cirass";
			
			if (iNation < 1 || iNation > 3) // англичанам и пиратам - "Скальд"
				itemID = itemID + 1;
			else
				itemID = itemID + (iNation + 1); // прочим - кирасы по национальности
			
			if (FindItem(itemID) >= 0)
			{
				itemRef = ItemsFromID(itemID);
				loc.box1.items.(itemID) = sti(loc.box1.items.(itemID)) + 1;
				itemID = XI_ConvertString("cuirass");
				sTemp = GetConvertStr(itemRef.name, "ItemsDescribe.txt");
			}
		}
	}
	// < содержимое сундуков каюты
	
	if (sTemp != "")
		TEV.TempText = StringFromKey("InfoMessages_81", itemID, sTemp);
	
	LootCollectorRandItems(); // генерим всякую дополнительную мелочь из сундуков да нычек и направляем в трюм
	
	if (!CheckAttribute(PChar, "QuestTemp.MorganKeyTaken") && nLuck >= rand(999)) // золотой ключ от сундуков Моргана; суём прямо в руки ГГ, от греха подальше
	{
		PChar.QuestTemp.MorganKeyTaken = true;
		AddItemLog(pchar, "keyMorgan", "1", StringFromKey("InfoMessages_78"), "Notebook_1");
	}
	
	LogSound_WithNotify(StringFromKey("InfoMessages_79"), "Gotcha&Notebook_2", "ShipCrew");

	if (iMoney > 0) // деньги сразу ГГ
	{
		pchar.money = sti(pchar.money) + iMoney;
//		Log_Info(StringFromKey("InfoMessages_80", iMoney));
		Notification(StringFromKey("InfoMessages_80", iMoney), "Money");
	}
	
	if (CheckAttribute(&TEV, "TempText"))
	{
//		Log_Info("" + TEV.TempText);
		Notification("" + TEV.TempText, "ShipCrew");
	}

	DeleteAttribute(&TEV, "TempText");
}

void LootCollectorRandItems()
{
	if (FindLocation("My_Deck") < 0 || GetCharacterShipClass(pchar) > 6)
		return;
	
	int itemsTotal = rand(GetCharacterSPECIAL(pchar, SPECIAL_L));
	int i, r, itemQty;
	string itemID;
	ref itemRef, locRef = &locations[FindLocation("My_Deck")];
	bool encouragementLoot = false;
	bool perkEnabled = GetOfficersPerkUsing(pchar, "HawkEye", false);
	
	if (CheckAttribute(pchar, "Fellows.Passengers.boatswain"))
	{
		if (sti(pchar.Fellows.Passengers.boatswain) >= 0)
		{
			ref npchar = GetCharacter(sti(pchar.Fellows.Passengers.boatswain));
			perkEnabled = perkEnabled || CheckCharacterPerk(npchar, "HawkEye");
		}
	}
	
	if (itemsTotal > 0)
	{
		for (i = 0; i < itemsTotal; i++)
		{
			r = rand(RANDITEMS_QUANTITY - 1);
			itemID = RandItems[r].id;
			
			if (FindItem(itemID) < 0)
				continue;
			
			if (LootCollectorCheckAbility() && perkEnabled && HasStrEx(itemID, "mineral,indian2,indian4,indian9,indian13,indian16", "|")) // подменяем некоторый мусор на бижу
			{
				if (itemID != "mineral3") // свечи теперь не мусор, их собираем
					itemID = "jewelry" + (1 + rand(8));
			}
			
			itemQty = rand(GetCharacterSPECIAL(pchar, SPECIAL_L));
			itemRef = &Items[FindItem(itemID)];
			
			if (itemQty > 0)
			{
				if (CheckAttribute(itemRef, "groupID") && HasStrEx(itemRef.groupID, "blade,cirass,gun,spyglass", "|")) // аммуниция всегда поштучно
					itemQty = 1;
				
				itemID = GetGeneratedItem(itemID);
				locRef.box1.items.(itemID) = sti(locRef.box1.items.(itemID)) + itemQty;
			}
			else
			{
				itemQty = rand(1);
				encouragementLoot = true;
			}
		}
	}
	else
	{
		itemQty = rand(3);
		encouragementLoot = true;
	}
	
	if (LootCollectorCheckAbility() && perkEnabled && encouragementLoot && itemQty > 0) // если не повезло что-то найти, даём шанс на бижутерию при наличии перка "Глаз Алмаз" у ГГ или у боцмана
	{
		itemID = "jewelry" + (1 + rand(8));
		
		if (FindItem(itemID) >= 0)
		{
			itemID = GetGeneratedItem(itemID);
			locRef.box1.items.(itemID) = sti(locRef.box1.items.(itemID)) + itemQty;
		}
	}
}

bool LootCollectorCheckCrew()
{
	if (GetCrewQuantity(pchar) > 0 && CheckOfficer("boatswain"))
		return true;
	
	return false;
}

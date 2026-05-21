
// BOAL 09.09.03 Каюта капитана

bool	bCabinStarted = false;
bool	bDeckBoatStarted = false;

void Cabin_ReloadStartFade()
{
	int a = GetEventData();
	aref reload_fader = GetEventData();
	LayerFreeze(SEA_EXECUTE,true);
	LayerFreeze(SEA_REALIZE,true);
	LayerFreeze(SEA_REFLECTION2,true);
	LayerFreeze(EXECUTE,false);
	LayerFreeze(REALIZE,false);

	MoveWeatherToLayers(EXECUTE, REALIZE);
	MoveSeaToLayers(EXECUTE, REALIZE);
	HideGrass();

	SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
    ClearAllFire();

	DelEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade");

	fOldMaxSeaHeight = stf(Sea.MaxSeaHeight);
	if (pchar.SystemInfo.CabinType == "My_Cabin_Small3") Sea.MaxSeaHeight = 0.5; //небольшие каюты затапливает на 1.2
	else Sea.MaxSeaHeight = 1.2;						// set maxinum sea height for ship abordage
}

void Cabin_ReloadEndFade()
{
	// Delete current cannonballs
	AIBalls.Clear = "";

 	PauseParticles(true);
    //DeleteParticles(); // boal fix костры нах

	// start Cabin location
 	int a = GetEventData();
	aref reload_fader = GetEventData();
	
	Cabin_Start();
	
	DelEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFade");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

void Sea_CabinStartNow()
{
	ResetSound();

	if (!bCabinStarted)
	{
		DeleteBattleInterface();
        bSeaReloadStarted = true;

        Set_My_Cabin();
        
    	object reload_fader;
    	CreateEntity(&reload_fader, "fader");
    	SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade", 0);
    	SetEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFade", 0);

    	SendMessage(&reload_fader, "ls", FADER_PICTURE0, GetRandomLoadingPic(Locations[FindLocation(Pchar.SystemInfo.CabinType)].image));
    	SendMessage(&reload_fader, "lfl", FADER_OUT, 1.0, false);
    	SendMessage(&reload_fader, "l", FADER_STARTFRAME);

    	bAbordageStarted = true;
    	bCabinStarted = true;
    	Sea.AbordageMode = true;
	}
	else Return2SeaAfterCabin();
}
void Sea_HoldStartNow() //HardCoffee переход в трюм
{
	ResetSound();

	if (bCabinStarted)
	{
		Return2SeaAfterCabin();
		return;
	}
	bSeaReloadStarted = true;
	Set_My_Cabin();
    object reload_fader;
    CreateEntity(&reload_fader, "fader");
    SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade", 0);
    SetEventHandler("FaderEvent_EndFade", "Hold_ReloadEndFade", 0);

    SendMessage(&reload_fader, "ls", FADER_PICTURE0, "loading\trumkor_" + rand(1) + ".tga");
    SendMessage(&reload_fader, "lfl", FADER_OUT, 1.0, false);
    SendMessage(&reload_fader, "l", FADER_STARTFRAME);

    bAbordageStarted = true;
    bCabinStarted = true;
    Sea.AbordageMode = true;
}

void Hold_ReloadEndFade() //HardCoffee сделано по аналогии с Cabin_ReloadEndFade
{
	// Delete current cannonballs
	AIBalls.Clear = "";

 	PauseParticles(true);

	// start Cabin location
 	int a = GetEventData();
	aref reload_fader = GetEventData();

	ResetSound();
	int i;
	//Настроим интерфейс
	DeleteBattleInterface();
	InitBattleLandInterface();

	ref mchr = GetMainCharacter();

	int locID = FindLocation("My_Deck");
	if (locID < 0) return;
	//Выставим  и запомним адреса
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group = mchr.location.group;
	boarding_adr[0].locator = mchr.location.locator;

	//Стартуем
	LAi_boarding_process = false;

	ReloadProgressStart();

	mchr.location = "My_Deck";
	mchr.location.group = "rld";
	mchr.location.locator = "loc0";

	Pchar.quest.SetQuestHoldBox.win_condition.l1          = "location";
	Pchar.quest.SetQuestHoldBox.win_condition.l1.location = "My_Deck";
	Pchar.quest.SetQuestHoldBox.win_condition             = "SetQuestHoldBox";

	boarding_location = locID;
	Locations[locID].boarding = "true";
	LoadLocation(&Locations[locID]);
	dialogDisable = false;

	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 100);

	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);

	DelEventHandler("FaderEvent_EndFade", "Hold_ReloadEndFade");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

void Cabin_Start()
{
	ResetSound();

	//Настроим интерфейс
	DeleteBattleInterface();
	InitBattleLandInterface();
	
	string locID = "";
	locID = Get_My_Cabin();
	
	int locIndex = FindLocation(locID);
	if (locIndex < 0)
	{
		Trace("Cabin: ship location not found <" + locID + ">, set default");
	    return;
	}
	//Выставим  и запомним адреса
	boarding_adr[0].location = pchar.location;
	boarding_adr[0].group = pchar.location.group;
	boarding_adr[0].locator = pchar.location.locator;
	
	//Стартуем
	LAi_boarding_process = false;

	Log_TestInfo("Cabin_Start Cabin_LoadLocation: " + locID);

	ReloadProgressStart();
	Log_SetActiveAction("Nothing");

	//Устанавливаем главного персонажа
	pchar.location = locID;
	pchar.location.group = "rld";
	pchar.location.locator = "loc0";

	//Перегружаемся в локацию
	boarding_location = locIndex;
	Locations[locIndex].boarding = "true";
	if (LoadLocation(&Locations[locIndex]))
	{
		dialogDisable = false;
	}
	else
	{
		Trace("Cabin_Start Location not loaded: " + locID);
	}

	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 100);

	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

void Return2SeaAfterCabin()
{
	Log_TestInfo("Return2SeaAfterCabin");
	EndBattleLandInterface();

	// evganat - фикс Шолотля
	if(CheckAttribute(pchar, "questTemp.easter.xolotl_incabin"))
        EasterDissapearXolotl();

    // вышли из каюты, пока сидели
	if (CheckAttribute(&TEV, "begin_sit"))
		LAi_GetUpFromChair();

 	Return2SeaClearNPC();

    //Установить хендлеры для обработки
	SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFadeAfter", 0);
	SetEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFadeAfter", 0);
	//Создаём фейдер и запускаем
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "ls", FADER_PICTURE0, GetLoadingImage_Sea());

	float fadeOutTime = RELOAD_TIME_FADE_OUT;

	SendMessage(&boarding_fader, "lfl", FADER_OUT, fadeOutTime, false);
	SendMessage(&boarding_fader, "l", FADER_STARTFRAME);
	TurnPrisonerToPchar(); //HardCoffee отключить наркоманскую поворачивалку
}

void Return2SeaClearNPC()
{
	ResetSoundBoarding();
	if (bDeckBoatStarted) DeleteNPCfromDeck(); // палуба
	else
	{
    	SetOfficersLocationToNone();
    	SetPrisonerLocationToNone();
		CompanionSaveTasks(); //компаньонов тоже
	}
	DeleteAttribute(pchar, "GenQuest.CaptainId");
}

void Cabin_ReloadStartFadeAfter() //Выгружаем локацию
{
	ResetSound();
	
	DelEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFadeAfter");
	if(boarding_location >= 0) UnloadLocation(&Locations[boarding_location]);
}

void Cabin_ReloadEndFadeAfter() //Загружаем следующую локацию
{
	ref sld;
	DelEventHandler("FaderEvent_EndFade", "Cabin_ReloadEndFadeAfter");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	boarding_location = -1;
	//Настроим интерфейс
	Log_SetActiveAction("Nothing");
	EndBattleLandInterface();
	//Востановим адреса
	ref mchr = GetMainCharacter();
	mchr.location = boarding_adr[0].location;
	mchr.location.group = boarding_adr[0].group;
	mchr.location.locator = boarding_adr[0].locator;

	if (bDisableMapEnter) // если бой, то ломаем корпус
	{
	    mchr.Ship.HP = makefloat(stf(mchr.Ship.HP) - GetCharacterShipHP(mchr) * 0.01);
	    if (stf(mchr.Ship.HP) < 0) mchr.Ship.HP = 0;
	}

	//Выгружаемся в интерфейс		
	LAi_boarding_process = false;

 	LayerFreeze(EXECUTE, true);
	LayerFreeze(REALIZE, true);

	LayerFreeze(SEA_REFLECTION2, false);
	LayerFreeze(SEA_EXECUTE, false);
	LayerFreeze(SEA_REALIZE, false);

	MoveWeatherToLayers(SEA_EXECUTE, SEA_REALIZE);
	MoveSeaToLayers(SEA_EXECUTE, SEA_REALIZE);
	ShowGrass();

	Sea.MaxSeaHeight = fOldMaxSeaHeight; // restore old MaxSeaHeight
	bAbordageStarted = false;
	bCabinStarted    = false;
	bDeckBoatStarted = false;
	Sea.AbordageMode = false;

	InitBattleInterface();
	StartBattleInterface();
	RefreshBattleInterface();

	SetSchemeForSea();

	PauseParticles(false);

	bSeaReloadStarted = false;

	Ship_RecreateStaticSounds();
	// <--
	/*if (WeatherHour < (GetHour() - 3) || WeatherHour > (GetHour() + 21)) // меняем только в новом часе... а то часто и баг в каюте
	{
        // boal 160804 час для погоды...
        CreateWeatherEnvironment(); // boal fix by mithrandir
    }
    else
    {
        Weather.isDone = "";

    	SetEventHandler(WEATHER_CALC_FOG_COLOR,"Whr_OnCalcFogColor",0);
    	SetEventHandler("frame","Whr_OnWindChange",0);
    	WhrCreateRainEnvironment();
    	WhrCreateSunGlowEnvironment();
    	WhrCreateLightningEnvironment();
    	WhrCreateSkyEnvironment();
    	WhrCreateSeaEnvironment();

    	bWeatherLoaded = true;
    }*/
	// boal 24.04.04 ругаем группы тут -->
	if (CheckAttribute(mchr, "StartBattleAfterDeck"))
	{
        Ship_NationAgressivePatent(characterFromID(mchr.StartBattleMainCaptanId));  //патент
        Ship_FlagRefresh(characterFromID(mchr.StartBattleMainCaptanId)); //флаг на лету
        SetCharacterRelationBoth(GetCharacterIndex(mchr.StartBattleMainCaptanId), GetMainCharacterIndex(), RELATION_ENEMY);
	    Group_SetTaskAttack(mchr.StartBattleEncGroupName, PLAYER_GROUP);

	    SetNationRelation2MainCharacter(sti(Characters[GetCharacterIndex(mchr.StartBattleMainCaptanId)].nation), RELATION_ENEMY);
	    UpdateRelations();
	    RefreshBattleInterface();
	    DeleteAttribute(mchr, "StartBattleAfterDeck"); // очищаем начало битвы
	    DoQuestCheckDelay("NationUpdate", 3.0);
	}
	if (CheckAttribute(mchr, "GenQuest.DestroyPirate.FightAfterDeck")) //квест мэра на пирата
	{
		sld = characterFromId("MQPirate");
		DeleteAttribute(sld, "ShipTaskLock"); //снимаем лок таска, не надо уже
		sld.nation = PIRATE;
		Ship_NationAgressivePatent(sld);
		Ship_FlagRefresh(sld); //флаг на лету
		Ship_SetTaskAttack(SECONDARY_TASK, sti(sld.index), 1);
		UpdateRelations();
		RefreshBattleInterface();
		DoQuestCheckDelay("NationUpdate", 0.1);
	}
	// ugeen --> генератор - "Поручение капитана - Операция 'Галеон'"
	if (CheckAttribute(mchr, "GenQuest.CaptainComission.FightAfterDeck"))
	{
		sld = characterFromId("CapComission_1");
		DeleteAttribute(sld, "AlwaysFriend");
		sld.nation = PIRATE;
		Ship_NationAgressivePatent(sld);
		Ship_FlagRefresh(sld); //флаг на лету
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
		Group_SetTaskAttack("Sea_CapComission_1", PLAYER_GROUP);
		Group_LockTask("Sea_CapComission_1");
		UpdateRelations();
		RefreshBattleInterface();
		DoQuestCheckDelay("NationUpdate", 0.1);
	}
	// <-- ugeen
	// boal 24.04.04 ругаем группы тут <--
	
	CheckCaptainFreeQuestAboardSituation(); // проверка некоторых квестовых ситуаций (взрыв или эпидемия), если отпустили без меню грабежа 
	
	// fix огней
	DeleteParticles();
	CreateParticleEntity();

	Whr_ColorizeSeaWater(); //красим воду
}

/////////// диалог на палубе ////////////
void Sea_DeckBoatStartNow(ref _iShipsCharacter)
{
	string boat_pic = "loading\boat_" + rand(2) + ".tga";	
	if(CheckAttribute(pchar, "TownEscape")) boat_pic = "loading\Escape_Town.tga";
	
	if (!bAbordageStarted)
	{
	    bSeaReloadStarted = true;

		object reload_fader;
		CreateEntity(&reload_fader, "fader");
		SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade", 0);  // одинаковый с каютой
		SetEventHandler("FaderEvent_EndFade", "DeckBoat_ReloadEndFade", 0);
		
		//SendMessage(&reload_fader, "ls", FADER_PICTURE0, "interfaces\card_desk.tga");
		SendMessage(&reload_fader, "ls", FADER_PICTURE0, boat_pic);
		SendMessage(&reload_fader, "lfl", FADER_OUT, 1.0, false);
		SendMessage(&reload_fader, "l", FADER_STARTFRAME);

        MakeCloneShipDeck(_iShipsCharacter, false); // подмена палубы
		SetSailorDeck_Ships(_iShipsCharacter);

		ResetSound();
	    //PlaySound("Abandon_0");// шлюпки на воду!
		bAbordageStarted = true;
		bDeckBoatStarted = true;
		Sea.AbordageMode = true;
	}

}

void DeckBoat_ReloadEndFade()
{
	// Delete current cannonballs
	AIBalls.Clear = "";
 	PauseParticles(true);
	// start DeckBoat location
	int a = GetEventData();
	aref reload_fader = GetEventData();
	DeckBoat_Start();
	DelEventHandler("FaderEvent_EndFade", "DeckBoat_ReloadEndFade");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}
void DeckBoat_Start()
{
	ResetSound();
	int i;
	//Настроим интерфейс
	DeleteBattleInterface();
	StartBattleLandInterface();
    if(!CheckAttribute(GetMainCharacter(), "TownEscape")) 
	{
		PlaySound("Abandon_0");// шлюпки на воду!
	}	
	ref mchr = GetMainCharacter();

	string DeckBoatID = "";
	DeckBoatID = "Deck_Near_Ship";

	int locID = -1;
	locID = FindLocation(DeckBoatID);
	if(locID < 0)
	{
		Trace("Boarding: ship location not found <" + DeckBoatID + ">, set default");
	    DeckBoatID = "";
	    return;
	}
	//Выставим  и запомним адреса
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group = mchr.location.group;
	boarding_adr[0].locator = mchr.location.locator;
	for(i = 1; i < 4; i++)
	{
		int idx = GetOfficersIndex(GetMainCharacter(), i);
		if(idx < 0)
		{
			boarding_adr[i].location = "";
			boarding_adr[i].group = "";
			boarding_adr[i].locator = "";
			continue;
		}
		boarding_adr[i].location = Characters[idx].location;
		boarding_adr[i].group = Characters[idx].location.group;
		boarding_adr[i].locator = Characters[idx].location.locator;
	}

	//Стартуем
	LAi_boarding_process = false;
	DeckBoat_LoadLocation(DeckBoatID);
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}


void DeckBoat_LoadLocation(string locationID) //Загрузить локацию абордажа
{
	ReloadProgressStart();
	int locIndex = FindLocation(locationID); //Ищем локацию
	Log_SetActiveAction("Nothing");
	if (locIndex >= 0)
	{	//Устанавливаем главного персонажа
		ref mchr = GetMainCharacter();
		DeleteAttribute(mchr, "StartBattleAfterDeck"); // очищаем начало битвы
		mchr.location = locationID;
		mchr.location.group = "goto";
		mchr.location.locator = "goto5";

		//Перегружаемся в локацию
		boarding_location = locIndex;
		Locations[locIndex].boarding = "true";
		if (LoadLocation(&Locations[locIndex])) dialogDisable = false; //Запретим диалог
		else Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
	}
	else Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 100);
}
void Sea_DeckBoatLoad(int ShipsCharacter)
{
	if (bSeaActive == false) return;
	ref rCharacter = GetCharacter(ShipsCharacter);
	if (LAi_IsDead(rCharacter)) return;  // нефиг, а то в списке есть трупы
	Sea_DeckBoatStartNow(rCharacter);
}

void SetSailorDeck_Ships(ref Chref)
{
	string characterID = Chref.id;
	ref sld;
    string  ani, model;
    int cn, Rank = 10;

	//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
	pchar.GenQuest.CaptainId = characterID; // boal заготовка для других квестов, обработка в диалоге
	pchar.quest.Munity = ""; // закрыто для квестов на выход
	//<-- eddy. квест мэра, закрываем выход с палубы
	
	// Warship 08.07.09 Пасхалка с бригантиной Мэри Селест
	// Генерим нашего матроса, который скажет, что, мол, корабль пуст
	if (characterID == "MaryCelesteCapitan")
	{
		model = LAi_GetBoardingModel(PChar, &ani);
		sld = GetCharacter(NPC_GenerateCharacter("saylor_0", model, "man", ani, Rank, sti(PChar.nation), 0, true));
	    sld.name = UpperFirst(XI_ConvertString("sailor1"));
	    sld.lastname = "";
        sld.Dialog.Filename = "Sailors_dialog.c";
    	sld.Dialog.CurrentNode = "On_MaryCeleste_Deck";
    	sld.greeting = "Gr_Soldier";
		
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, PChar, "", 5.0, 0);
		
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto8");
		
		chrDisableReloadToLocation = true; // Чтобы нельзя было выйти до разговора
		
		PChar.QuestTemp.MaryCeleste = "OnDeck";
		Map_ReleaseQuestEncounter(characterID); // Убираем с глобалки
		return;
	}
	
	if (CheckAttribute(pchar,"questTemp.ReasonToFast.canSpeakSailor") || CheckAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain"))
	{
		model = LAi_GetBoardingModel(PChar, &ani);
		sld = GetCharacter(NPC_GenerateCharacter("saylor_0", model, "man", ani, 10, sti(PChar.nation), 0, true));
		sld.name = XI_ConvertString("boatswain");
	    sld.lastname = "";
		sld.Dialog.Filename = "Sailors_dialog.c";
		if(CheckAttribute(pchar,"questTemp.ReasonToFast.canSpeakSailor"))
			sld.Dialog.CurrentNode = "On_MyShip_Deck";
		if(CheckAttribute(pchar,"GenQuest.CaptainComission.canSpeakBoatswain"))
			sld.Dialog.CurrentNode = "CapComission_OnShipDeck";
    	sld.greeting = "Gr_Soldier";
		
		chrDisableReloadToLocation = true; // Чтобы нельзя было выйти до разговора
				
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, PChar, "", 5.0, 0);
		
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto8");				
		return;
	}
	
	if(CheckAttribute(pchar,"GenQuest.Hold_GenQuest.canSpeakSailor"))
	{
		model = LAi_GetBoardingModel(PChar, &ani);
		sld = GetCharacter(NPC_GenerateCharacter("saylor_0", model, "man", ani, 10, sti(PChar.nation), 0, true));
		sld.name = XI_ConvertString("boatswain");
	    sld.lastname = "";
		sld.Dialog.Filename = "Sailors_dialog.c";
		if(pchar.GenQuest.Hold_GenQuest == "prisoner_escaped")
		{
			sld.Dialog.CurrentNode = "Hold_GenQuest_OnShipDeck";
		}
		if(pchar.GenQuest.Hold_GenQuest == "prisoner_ransom")
		{
			sld.Dialog.CurrentNode = "Hold_GenQuest_OnShipDeck4";
		}	
    	sld.greeting = "Gr_Soldier";
		
		chrDisableReloadToLocation = true; // Чтобы нельзя было выйти до разговора
				
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, PChar, "", 5.0, 0);
		
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto8");				
		return;	
	}
	
	if(CheckAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain"))
	{
		sld = characterFromID("CapComission_1");
		sld.dialog.currentnode = "CaptainComission_380";
		sld.greeting = "Gr_Soldier";
		chrDisableReloadToLocation = true; // Чтобы нельзя было выйти до разговора
		ChangeCharacterAddressGroup(sld, "Deck_Near_Ship", "goto", "goto8");	
		LAi_CharacterEnableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		return;	
	}

	if (characterID == "MQPirate" || characterID == "CapComission_1") // TODO заменить на флаг, чтоб было всем квестовым
	{  // клон для квестов
	    ref CopyChref;
	    
		CopyChref = GetCharacter(NPC_GenerateCharacter("FantomDeckCap", "none", "man", "man", 1, PIRATE, 0, false));
		
	    int NewCapIdx = sti(CopyChref.index);
		aref arToChar, arFromChar;
		
		DeleteAttribute(CopyChref, "");
		
	    makearef(arToChar, CopyChref);
	    makearef(arFromChar, Chref);
	    CopyAttributes(arToChar, arFromChar);
	    
		CopyChref.index = NewCapIdx;
		CopyChref.id = "FantomDeckCap";
		CopyChref.lifeDay = 0;
		
	    LAi_SetWarriorType(CopyChref);
		LAi_warrior_DialogEnable(CopyChref, true);
		LAi_SetLoginTime(CopyChref, 0.0, 24.0); // фикс, чтоб были всегда
		// запоминаем старый диалог
		if (!CheckAttribute(CopyChref,"DeckDialogNode"))
	    {
	        CopyChref.Dialog.Filename = "Capitan_dialog.c";
		    SetCapGreetByModel(CopyChref);
		    CopyChref.Dialog.CurrentNode = "First time";
	    }
	    else  CopyChref.Dialog.CurrentNode = CopyChref.DeckDialogNode;

	    if (CheckAttribute(CopyChref, "talk_date_Go_away") && CopyChref.talk_date_Go_away == LastSpeakDate())
			CopyChref.Dialog.CurrentNode = "Go_away";// boal кусок кода для запрета повторных наездов на капитана

		ChangeCharacterAddressGroup(CopyChref, "Deck_Near_Ship", "goto", "goto9");
	}
	else
	{   // здесь настоящий кэп, не клон
		LAi_SetWarriorType(Chref);
		LAi_warrior_DialogEnable(Chref, true);
		LAi_SetLoginTime(Chref, 0.0, 24.0); // фикс, чтоб были всегда
		// запоминаем старый диалог
		if (CheckAttribute(Chref, "Dialog.Filename"))
	    {
	        Chref.Bak.Dialog.Filename    = Chref.Dialog.Filename;
	        Chref.Bak.Dialog.CurrentNode = Chref.Dialog.CurrentNode;
	    }
	    else
	    {
	        Chref.Bak.Dialog.Filename    = "";
	        Chref.Bak.Dialog.CurrentNode = "First time";
	    }

		if (!CheckAttribute(Chref,"DeckDialogNode"))
	    {
	        Chref.Dialog.Filename = "Capitan_dialog.c";
		    SetCapGreetByModel(Chref);
		    Chref.Dialog.CurrentNode = "First time";
	    }
	    else Chref.Dialog.CurrentNode = Chref.DeckDialogNode;

	    if (CheckAttribute(Chref, "talk_date_Go_away") && Chref.talk_date_Go_away == LastSpeakDate())
	    {	// boal кусок кода для запрета повторных наездов на капитана
			if(CheckAttribute(Chref,"surrendered")) Chref.Dialog.CurrentNode = "surrender_goaway";
			else Chref.Dialog.CurrentNode = "Go_away";
	    }
		ChangeCharacterAddressGroup(Chref, "Deck_Near_Ship", "goto", "goto9");
	}

	if (CheckAttribute(pchar,"GenQuest.CaptainComission")) Rank = sti(pchar.rank) + rand(MOD_SKILL_ENEMY_RATE); // чтобы жизнь медом не казалась
    
    for (int i = 1; i < 5; i++)
    {
        model = LAi_GetBoardingModel(Chref, &ani);
		cn = NPC_GenerateCharacter("saylor_0" + i, model, "man", ani, Rank, sti(Chref.nation), 0, true);
		sld = &Characters[cn];
		
		//Rosarak Разнообразие моделек
		if (HasSubStr(Chref.model, "merch_")) //Ship.Mode == "Trade" не всем ставится
				ani = "sailor_merchant";
		else	ani = GetModelType(model);
		SetNPCModelUniq(sld, ani, MAN);
		
        LAi_SetWarriorType(sld); // участвуют в расстреле - переинитим тип
    	LAi_warrior_DialogEnable(sld, true);
	    sld.name    = UpperFirst(XI_ConvertString("sailor1"));
	    sld.lastname = "";
        sld.Dialog.Filename = "Sailors_dialog.c";
    	sld.Dialog.CurrentNode = "On_Deck";
    	SetSailGreetByModel(sld);
	}

	ChangeCharacterAddressGroup(characterFromID("saylor_01"), "Deck_Near_Ship", "goto", "goto8");
	ChangeCharacterAddressGroup(characterFromID("saylor_02"), "Deck_Near_Ship", "goto", "goto3");
	ChangeCharacterAddressGroup(characterFromID("saylor_03"), "Deck_Near_Ship", "goto", "goto6");
	ChangeCharacterAddressGroup(characterFromID("saylor_04"), "Deck_Near_Ship", "goto", "goto7");
}

void DeleteNPCfromDeck()
{
    int i;
    ref Cref;
    //Log_TestInfo("DeleteNPCfromDeck");
    for (i = 0; i < TOTAL_CHARACTERS; i++)
    {
        Cref = GetCharacter(i);
        if (CheckAttribute(Cref, "location") && Cref.location == "Deck_Near_Ship")
        {
			Cref.location = "none";
			//Log_TestInfo("DeleteNPCfromDeck " + Cref.id);
			// диалог в зад
			if (CheckAttribute(Cref, "Dialog.Filename") && Cref.Dialog.Filename == "Capitan_dialog.c")
			{
				Cref.Dialog.Filename = Cref.Bak.Dialog.Filename;
				Cref.Dialog.CurrentNode = Cref.Bak.Dialog.CurrentNode;
			}
        }
    }
}

void SetPrisonerInHold() //Устанавливаем пленных, если такие есть
{
	ref rPrison;
    int i, cn;

    for (i = 0; i < GetPassengersQuantity(pchar); i++)
    {
        cn = GetPassenger(pchar, i);
        if (cn < 0) continue;
        rPrison = GetCharacter(cn);
        if (CheckAttribute(rPrison, "Capellan") && GetPrisonerQty() > 1 && rand(2) == 0)
        {	//Капеллан может зайти в трюм промывать мозг пленным
        	LAi_SetCitizenTypeNoGroup(rPrison);
        	PlaceCharacter(rPrison, "rld", pchar.location);
        	continue;
        }

        if (!CheckAttribute(rPrison,"prisoned") || sti(rPrison.prisoned) == false || CheckAttribute(rPrison,"NonRemovable")) continue;

		if (rand(2) == 0) LAi_SetPoorTypeNoGroup(rPrison); //чтобы они сидели на полу, а не только ходили
		else LAi_SetCitizenTypeNoGroup(rPrison); //HardCoffee фикс вызова диалога после вышвыривания его из каюты

		if ("My_Deck" == rPrison.location) continue;
		LAi_group_MoveCharacter(rPrison, "Prisoner");
		PlaceCharacter(rPrison, "goto", pchar.location);
    }
}

void SetPrisonerLocationToNone()
{
	ref rPris;
	int i, cn;
	for (i = 0; i < GetPassengersQuantity(pchar); i++)
	{
		cn = GetPassenger(pchar,i);
		if (cn < 0) continue;
		rPris = GetCharacter(cn);
		if (CheckAttribute(rPris,"Capellan") && "none" != rPris.location) //Уберём капеллана, он может оказаться в трюме
		{
			ChangeCharacterAddress(rPris, "none", "");
			continue;
		}

		if (!CheckAttribute(rPris, "prisoned") || sti(rPris.prisoned) == 0
		 || CheckAttribute(rPris, "NonRemovable") || rPris.location == "none") continue;

		ChangeCharacterAddress(rPris, "none", "");
	}
}

void TurnPrisonerToPchar() //HardCoffee эта наркомания заставит арестанта повернуться в сторону гг, если его вызвали в каюту
{
	if (Number_Group_People("Prisoner", 0) < 1) return;
	if (Get_My_Cabin() != pchar.location) return;
	int cn;
	ref rPrison;
	float ftime;
	for (int i = 0; i < GetPassengersQuantity(pchar); i++)
	{
		cn = GetPassenger(pchar,i);
		if (cn < 0) continue;
		rPrison = GetCharacter(cn);
		if (CheckAttribute(rPrison,"prisoned") && sti(rPrison.prisoned) == true && Get_My_Cabin() == rPrison.location && rand(1) == 0)
			CharacterTurnByChr(rPrison, pchar);
	}
	ftime = 0.5 + frand(1.5);
	LAi_MethodDelay("TurnPrisonerToPchar", ftime);
}

void SetOfficersInCabin() //HardCoffee установка в кабину только выбранных офицеров
{
    ref rChr;
    int idx, i;
	// Я хз, куда ещё это запихнуть. Тут без всяких лишних проверок сразу ясно, что это каюта и всё спокойно
	if (GetDlcEnabled(NABOB_PACK))
	{
		if (!CheckAttribute(&TEV, "gotNabobRevard") && CheckAttribute(loadedlocation, "box1"))
		{
			loadedlocation.box1.items.RapierReCon = 1;
			loadedlocation.box1.items.recon_potion = 1;
			TEV.gotNabobRevard = "revardTaken";
		}
	}

	for (i = 0; i < GetPassengersQuantity(pchar); i++)
	{
		idx = GetPassenger(pchar, i);
		if (idx < 1) continue;
		rChr = &Characters[idx];
		if (CheckAttribute(rChr,"NonRemovable") || !checkattribute(rChr, "Tasks.beInCabin") || !sti(rChr.Tasks.beInCabin)) continue;
		PlaceCharacter(rChr, "rld", pchar.location);
		if (rand(1) == 0 && rChr.id != "Douglas" && PlaceCharacter(rChr, "sit", "random") != "") //посадим офицера
		{
			rChr.nonTable = true;
			LAi_SetSitTypeNoGroup(rChr);
		}
		else LAi_SetWarriorTypeNoGroup(rChr);
		LAi_group_MoveCharacter(rChr, LAI_GROUP_PLAYER); //чтобы в случае чего они могли вступить в бой
		if (!HaveFreeSpaceInCabin()) return;
	}
}

void SetOfficersInCampus() //Устанавливаем рандомных офов в кампус
{
	ref rChr;
    int i, cn;
    for (i = 0; i < GetPassengersQuantity(pchar); i++)
    {
        cn = GetPassenger(pchar,i);
        if (cn < 0) continue;
        rChr = GetCharacter(cn);
        if (CheckAttribute(rChr,"NonRemovable") && !CheckAttribute(rChr, "Capellan")) continue;
        if (CheckAttribute(rChr,"prisoned") && sti(rChr.prisoned) == true) continue;
		//HardCoffee так как введён рандом на посещение кампуса оффами - при перезаходе гг в кампус - удалим предыдущих
        if ("My_Campus" == rChr.location) ChangeCharacterAddress(rChr, "none", "");
		if (rand(1) == 0) continue; //Чтобы не создавать толпу (не вечно же они сидят в кают компании)
		DeleteAttribute(rChr,"nonTable");
		PlaceCharacter(rChr, "goto", pchar.location);
		if (rand(1) == 0 && rChr.id != "Douglas" && PlaceCharacter(rChr, "sit", "random") != "") //посадим офицера
		{
			if ("sit3" == rChr.location.locator) rChr.nonTable = true;
			LAi_SetSitTypeNoGroup(rChr);
		}
		else LAi_SetCitizenTypeNoGroup(rChr);
		LAi_group_MoveCharacter(rChr, LAI_GROUP_PLAYER);
	}
}

void SetOfficersLocationToNone() //HardCoffee функции Passengers и Prisoner разбиты, так как вызываются в разных ситуациях
{
	ref rChr;
	int i, cn;
	for (i = 0; i < GetPassengersQuantity(pchar); i++)
	{
		cn = GetPassenger(pchar,i);
		if (cn < 0) continue;
		rChr = GetCharacter(cn); //исключаем квестовых кроме капеллана
		if (CheckAttribute(rChr,"NonRemovable") && !CheckAttribute(rChr,"Capellan")) continue;
		if (CheckAttribute(rChr,"prisoned") && sti(rChr.prisoned) == true) continue; //исключаем арестантов
		DeleteAttribute(rChr,"nonTable");
		//установка шаблонов поведения связана с тем, что появились сидячие офицеры в каюте и кампусе
		//проверяем всех персонажей, так как возможно анимация "сидеть" останется когда офицер захочет уволиться в таверне
		LAi_SetFollowerType(rChr); //заставить офицера следовать за гг
		LAi_SetOfficerType(rChr); //заставить сражаться
		if ("none" != rChr.location) ChangeCharacterAddress(rChr, "none", "");	//используется когда гг в каюте
	}
}

void Reset_Officers_InCabin()	//HardCoffee функция заставит сидящих в каюте офицеров вступить в бой
{	//так же вернёт возможность диалога с офицером после драки в каюте
	ref rChr;
    int idx, i;

	for(i = 0; i < LAi_numloginedcharacters; i++) //для того, чтобы с компаньонами то же можно было поговорить
	{
		idx = LAi_loginedcharacters[i];
		if (idx < 0) continue;
		rChr = &characters[idx];
		if (CheckAttribute(rChr,"Capellan") && "none" != rChr.location)
			ChangeCharacterAddress(rChr, "none", ""); //Капеллана убираем, нечего ему мешаться во время боя
		if (rChr.id == pchar.id || CheckAttribute(rChr,"NonRemovable")) continue;
		if (CheckAttribute(rChr,"prisoned") && sti(rChr.prisoned) == true) continue;
		if (LAI_TYPE_SIT == rChr.chr_ai.type) //HardCoffee костыль для того, чтобы вытащить сидячего офицера из локатора sit
			PlaceCharacter(rChr, "rld", PChar.location);
		if (LAI_GROUP_PLAYER == rChr.chr_ai.group) LAi_SetWarriorTypeNoGroup(rChr);
	}
}
void SetSailorsInGunDeck(ref loc) //HardCoffee функция заселит палубу матросами
{
	if (!CheckAttribute(loc, "locators.goto")) return;
	aref grp;
	makearef(grp, loc.locators.goto);
	int iMax = GetAttributesNum(grp);
	if (iMax < 1) return;

	if ("My_Deck_Medium" == loc.id) iMax /= 2;

	ref rChr;
	int i, iTemp, iRank;
	string model, ani, sLocator;
	string sVoice = VoiceGetLanguage();

	int realCrew = GetCrewQuantity(pchar);
	int iSailor = realCrew * iMax / GetOptCrewQuantity(pchar);
	if (iSailor >= realCrew / 10)
		iSailor = realCrew / 10 - 1;
	if (iSailor > iMax)
		iSailor = iMax;

	if (iSailor > 0)
	{	//экипировка зависит от ранга, ранг матросов 1...22 зависит от опыта и рандома
		iRank = makeint((GetCrewExp(pchar, "Sailors") + GetCrewExp(pchar, "Cannoners") + GetCrewExp(pchar, "Soldiers")) / 30 + 1);
		for (i = 0; i < iSailor; i++)
		{

			sLocator = LAi_FindFreeRandomLocator("rld");
			if (sLocator == "") break;

			model = LAi_GetBoardingModel(pchar, &ani);
			rChr = LAi_CreateFantomCharacterEx(model, ani, "rld", sLocator);
			LAi_NPC_Equip(rChr, rand(iRank) + iRank, true, true);
			setNewModelToChar(rChr);
			iTemp = rand(3);
			if (0 == iTemp && PlaceCharacter(rChr, "sit", "random") != "")
			{
				LAi_SetSitType(rChr);
			}
			//else if (iTemp == 1 && Rand(1) == 0) LAi_SetPoorType(rChr); //сидеть на полу
			else LAi_SetCitizenType(rChr);
			rChr.dialog.FileName = "Our_Sailor.c";
			rChr.dialog.currentnode = "Gun_deck_sailor";

			if ("russian" != sVoice)
				rChr.greeting = "Voice\" +sVoice +"\pirat_guard_4.WAV"; //Good to see you captain
			/*else if (rChr.chr_ai.type == LAI_TYPE_POOR)
				rChr.greeting = "Voice\" +sVoice +"\pirat_guard_1.WAV";*/
			else
			{
				switch (rand(3))
				{
					case 0: rChr.greeting = "Voice\" +sVoice +"\pirat_guard_1.WAV"; break;
					case 1: rChr.greeting = "Voice\" +sVoice +"\pirat_guard_2.WAV"; break;
					case 2: rChr.greeting = "Voice\" +sVoice +"\pirat_guard_3.WAV"; break;
					case 3: rChr.greeting = "Voice\" +sVoice +"\pirat_guard_4.WAV"; break;
				}
			}

			rChr.LifeDay = 0; //Чтобы удалялись при смене локации
			LAi_group_MoveCharacter(rChr, LAI_GROUP_PLAYER);
		}
	}

	for (i = 0; i < GetPassengersQuantity(pchar); i++)
	{	//Поставим ещё и офицеров
        iTemp = GetPassenger(pchar,i);
        if (iTemp < 0) continue;
        rChr = GetCharacter(iTemp);
        //if (CheckAttribute(tempChr, "Capellan") && "none" != tempChr.location) tempChr.location = "none"; //вытащим капеллана из трюма
        if (CheckAttribute(rChr,"NonRemovable") && !CheckAttribute(rChr, "Capellan")) continue;
        if (CheckAttribute(rChr,"prisoned") && sti(rChr.prisoned) == true)
		{
			if ("none" != rChr.location) ChangeCharacterAddress(rChr, "none", "");	//Уберём арестантов из каюты
			continue;
		}
        if ("My_Deck_Medium" == rChr.location) ChangeCharacterAddress(rChr, "none", "");
		if (rand(7) == 0) PlaceCharacter(rChr, "goto", "random");
        LAi_SetCitizenTypeNoGroup(rChr);
        LAi_group_MoveCharacter(rChr, LAI_GROUP_PLAYER);
	}
}
/*
void SetGunDeckSailorsToNone() //функция удалит матросов с орудийной палубы
{	//предполагается использовать её для тренировочных поединков с офицерам на орудийной палубе
	int i, idx;
	ref chr;
	int iLogin = LAi_numloginedcharacters;
	for(i = 0; i < iLogin; i++)
	{
		idx = LAi_loginedcharacters[i];
		if (idx < 0) continue;
		chr = &characters[idx];
		if (CheckAttribute(chr, "dialog.FileName") && chr.dialog.FileName == "Our_Sailor.c")
			ChangeCharacterAddress(chr, "none", "");
	}
}
*/
bool HaveFreeSpaceInCabin() //HardCoffee функция проверяет свободные локаторы для вызова персонажей в каюту.
{
	switch (loadedlocation.id) //чтобы не создавать толпу в каюте
	{
		case "My_Cabin_Small3":		if (LAi_numloginedcharacters > 1) 	return false;	break;	//7 класс
		case "My_Cabin_Small2":		if (LAi_numloginedcharacters > 3) 	return false;	break;	//люггер
		case "My_Cabin_Small4":		if (LAi_numloginedcharacters > 3) 	return false;	break;	//шлюп
		case "My_Cabin_Small":		if (LAi_numloginedcharacters > 4) 	return false;	break;	//тяж шлюп
		case "My_Cabin_Medium3":	if (LAi_numloginedcharacters > 4) 	return false;	break;	//торг шхуна //the same as 3
		case "My_Cabin_Medium4":	if (LAi_numloginedcharacters > 4) 	return false;	break;	//воен шхуна //the same as 3
		case "My_Cabin_Medium5":	if (LAi_numloginedcharacters > 4) 	return false;	break;	//хебек //the same as 3
		case "My_Cabin_Medium6":	if (LAi_numloginedcharacters > 4) 	return false;	break;	//квестовый бриг
		case "My_Cabin_Medium":		if (LAi_numloginedcharacters > 4)	return false;	break;	//бриг
		case "My_Cabin_Medium2":	if (LAi_numloginedcharacters > 4)	return false;	break;	//корвет
		case "My_Cabin":			if (LAi_numloginedcharacters > 8)	return false;	break;	//галеон
		case "My_Cabin_Big":		if (LAi_numloginedcharacters > 6)	return false;	break;	//фрегат
		case "My_Cabin_Huge":		if (LAi_numloginedcharacters > 10)	return false;	break;	//самовар
		case "My_Cabin_Quest":		if (LAi_numloginedcharacters > 8)	return false;	break;	//псы
		case "My_CabineFDM":		if (LAi_numloginedcharacters > 8)	return false;	break;	//лг
	}
	return true;
}

int Number_Group_People(string group, int decrease)
{	//HardCoffee эта функция считает сколько человек в группе на локации
	//decrease нужен, на случай если ктото планирует выйти из группы
	int n = 0;
	int index;
	ref chr;
	for (int i = 0; i < LAi_numloginedcharacters; i++)
	{
		index = LAi_loginedcharacters[i];
		if (index < 0) continue;
		chr = &characters[index];
		if (CheckAttribute(chr, "Capellan")) continue; //капеллан в боях не участвует
		if (chr.chr_ai.group == group) n++;
	}
	return n - decrease;
}

void Take_Fists_Away() //HardCoffee функция заберёт у гг кулаки, и восстановит предыдущую экипировку
{	//здесь нет проверки на аттрибут - проверка есть перед вызовом этой функции
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	TakeNItems(pchar, "unarmed", -1);
	if (!CheckAttribute(&TEV, "tPunch")) return;
	if (CheckAttribute(&TEV, "tPunch.equip.blade")) EquipCharacterByItem(pchar, TEV.tPunch.equip.blade);
	if (CheckAttribute(&TEV, "tPunch.equip.gun")) EquipCharacterByItem(pchar, TEV.tPunch.equip.gun);
	if (CheckAttribute(&TEV, "tPunch.equip.cirass")) EquipCharacterByItem(pchar, TEV.tPunch.equip.cirass);
    if (CheckAttribute(&TEV, "tPunch.equip.musket")) EquipCharacterByItem(pchar, TEV.tPunch.equip.musket);
	Deleteattribute(&TEV, "tPunch");
}

void Take_Fists() //HardCoffee функция подготовит гг для кулачного боя
{
	TEV.tPunch = true; //для невозможности переэкипироваться во время кулачного боя
	if (CheckAttribute(pchar, "equip.blade") && pchar.equip.blade != "") TEV.tPunch.equip.blade = pchar.equip.blade;
	if (CheckAttribute(pchar, "equip.gun") && pchar.equip.gun != "") TEV.tPunch.equip.gun = pchar.equip.gun;
	if (CheckAttribute(pchar, "equip.cirass") && pchar.equip.cirass != "") TEV.tPunch.equip.cirass = pchar.equip.cirass;
    if (CheckAttribute(pchar, "equip.musket") && pchar.equip.musket != "") TEV.tPunch.equip.musket = pchar.equip.musket;
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE); //снимаем экипировку
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
	RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
	GiveItem2Character(pchar, "unarmed"); //выдаём гг кулаки
	EquipCharacterByItem(pchar, "unarmed");
}

// AlexBlade > Загрузка локации палубы из моря для квестовых нужд
// Отличается от DoReloadFromSeaToLocation тем, что выход из локи осуществляется аналогично выходу из абордажа/каюты
// Таким образом при выходе не исчезают находящиеся рядом корабли-энкаунтеры
void Sea_DeckBoatLoad_ForQuest(int charIndex)
{
	if (bSeaActive == false) return;
	ref rCharacter = GetCharacter(charIndex);
	if (LAi_IsDead(rCharacter)) return;  // нефиг, а то в списке есть трупы
	Sea_DeckBoatLoad_ForQuest_StartNow(rCharacter);
}

void Sea_DeckBoatLoad_ForQuest_StartNow(ref _iShipsCharacter)
{
	string boat_pic = "loading\boat_" + rand(2) + ".tga";	
	if(CheckAttribute(pchar, "TownEscape")) boat_pic = "loading\Escape_Town.tga";
	
	if (!bAbordageStarted)
	{
		ResetSound();
	    bSeaReloadStarted = true;

		object reload_fader;
		CreateEntity(&reload_fader, "fader");
		SetEventHandler("FaderEvent_StartFade", "Cabin_ReloadStartFade", 0);  // одинаковый с каютой
		SetEventHandler("FaderEvent_EndFade", "DeckBoat_ForQuest_ReloadEndFade", 0);
		
		//SendMessage(&reload_fader, "ls", FADER_PICTURE0, "interfaces\card_desk.tga");
		SendMessage(&reload_fader, "ls", FADER_PICTURE0, boat_pic);
		SendMessage(&reload_fader, "lfl", FADER_OUT, 1.0, false);
		SendMessage(&reload_fader, "l", FADER_STARTFRAME);

        MakeCloneShipDeck(_iShipsCharacter, true); // подмена палубы
		
		bAbordageStarted = true;
		bDeckBoatStarted = true;
		Sea.AbordageMode = true;
	}
}

void DeckBoat_ForQuest_ReloadEndFade()
{
	// Delete current cannonballs
	AIBalls.Clear = "";
 	PauseParticles(true);
	// start DeckBoat location
	int a = GetEventData();
	aref reload_fader = GetEventData();
	DeckBoat_ForQuest_Start();
	DelEventHandler("FaderEvent_EndFade", "DeckBoat_ForQuest_ReloadEndFade");
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}
void DeckBoat_ForQuest_Start()
{
	ResetSound();
	int i;
	
	//Настроим интерфейс
	DeleteBattleInterface();
	StartBattleLandInterface();
	ref mchr = GetMainCharacter();

	string DeckBoatID = "";
	DeckBoatID = "Ship_deck";

	int locID = -1;
	locID = FindLocation(DeckBoatID);
	if(locID < 0)
	{
		Trace("Boarding: ship location not found <" + DeckBoatID + ">, set default");
	    DeckBoatID = "";
	    return;
	}
	//Выставим  и запомним адреса
	boarding_adr[0].location = mchr.location;
	boarding_adr[0].group = mchr.location.group;
	boarding_adr[0].locator = mchr.location.locator;
	for(i = 1; i < 4; i++)
	{
		int idx = GetOfficersIndex(GetMainCharacter(), i);
		if(idx < 0)
		{
			boarding_adr[i].location = "";
			boarding_adr[i].group = "";
			boarding_adr[i].locator = "";
			continue;
		}
		boarding_adr[i].location = Characters[idx].location;
		boarding_adr[i].group = Characters[idx].location.group;
		boarding_adr[i].locator = Characters[idx].location.locator;
	}

	//Стартуем
	LAi_boarding_process = false;
	DeckBoat_ForQuest_LoadLocation(DeckBoatID);
	CreateEntity(&boarding_fader, "fader");
	SendMessage(&boarding_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
}

void DeckBoat_ForQuest_LoadLocation(string locationID) //Загрузить локацию
{
	ReloadProgressStart();
	int locIndex = FindLocation(locationID); //Ищем локацию
	Log_SetActiveAction("Nothing");
	if (locIndex >= 0)
	{	//Устанавливаем главного персонажа
		ref mchr = GetMainCharacter();
		DeleteAttribute(mchr, "StartBattleAfterDeck"); // очищаем начало битвы
		mchr.location = locationID;
		mchr.location.group = "reload";
		mchr.location.locator = "reload1";

		//Перегружаемся в локацию
		boarding_location = locIndex;
		Locations[locIndex].boarding = "true";
		if (LoadLocation(&Locations[locIndex])) dialogDisable = false; //Запретим диалог
		else Trace("Boarding: Boarding location not loaded, current loc <" + locationID + ">");
	}
	else Trace("Boarding: Boarding location not found, current loc <" + locationID + ">");
	ReloadProgressEnd();
	PostEvent("LoadSceneSound", 100);
}
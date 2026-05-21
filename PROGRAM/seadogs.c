#include "_mod_on_off.h"
#include "storm-engine\layers.h"
#include "storm-engine\events.h"
#include "globals.c"
#include "animals.c"
#include "NumberUtilities.c" // Warship 26.07.09. Работа с числами
#include "sea_ai\sea.c"
#include "ships\ships.c"
#include "Encounters\Encounters.c"
#include "worldmap\worldmap.c"
#include "Loc_ai\LAi_init.c"
#include "store\goods.h"
#include "cannons\cannons.c"
#include "nations\nations.c"
#include "particles.c"
#include "characters\characters.c"
#include "locations\locations.c"
#include "interface\interface.h"
#include "store\storeutilite.c"
#include "dialog.c"
#include "quests\quests.c"
//#include "quests\EncGirl_Functions.c"
#include "islands\islands.c"
#include "colonies\colonies.c"
#include "reload.c"
#include "battle_interface\loginterface.c"
#include "calendar.c"
#include "teleport.c"
#include "utils.c"
#include "weather\WhrWeather.c"
#include "controls\controls.c"
#include "ITEMS\items.h"
#include "ITEMS\itemLogic.c"
#include "ITEMS\chestLogic.c" //HardCoffee буду переносить сюда заполнялки сундуков
#include "ITEMS\items_utilite.c"
#include "store\store.h"
#include "interface\interface.c"
#include "interactive.c"
#include "migrations.c"
#include "achievements.c"
#include "utils_recon.c"
#include "scripts\array_utils.c"

extern void InitBaseCannons();
extern void InitCharacters();
extern void InitBaseInterfaces();

extern void wdmInitWorldMap();
extern void InitGoods();
extern void InitStores();
extern int InitItems();
extern void InitCharactersTables();
extern void InitCharactersNames();
extern void InitPiratesNames();
extern void InitGeneratorNames();
extern void InitIndianNames(); //Jason имена индейцев
extern void InitVikingNames(); //AlexBlade имена викингов
extern void CreateCharacters();

extern void ActiveF4Control(); // boal debuger
extern void ActiveF5Control(); // boal debuger
extern void ActiveF7Control(); // boal debuger
extern void ActiveF10Control(); // boal debuger
extern void ActiveF12Control(); // boal debuger
extern void ActiveINSERTControl(); // boal debuger

native float Bring2RangeNoCheck(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Bring2Range(float fMin1, float fMax1, float fMin2, float fMax2, float fValue);
native float Clampf(float fValue);
native float Degree2Radian(float fDegree);
native int RDTSC_B();
native int RDTSC_E(int iRDTSC);

native int SetTexturePath(int iLevel, string sPath);
native int SetGlowParams(float fBlurBrushSize, int Intensivity, int BlurPasses);
native int RPrint(int x, int y, string sPrint);
native int GetTexture(string fileName);
native void ReleaseTexture(int texId);
native void SetCameraShake(float time, float i1, float i2, float r1, float r2, bool sc, bool ev, int fd);

native int GetSteamEnabled();
native int GetDLCenabled(int enable);
native int GetDLCCount();
native int GetDLCData(int id);
native int DLCStartOverlay(int id);
native int SetAchievement(string id);
native int GetAchievement(string id);
native int SetStat(string id, int value);
native int GetStat(string id);
native int StoreStats();
native int ClearAchievement(string id);
native int ResetStats(int bAchievementsToo);
native bool IsVerified();
native bool Verify();
native string GetPersonaName();
native int GetAppID();
native bool IsSteamDeck();
native bool IsVirtualKeyboardShowing();
// Virtual Keyboard Mode:
// 0 - Single Line (Enter closes the keyboard)
// 1 - Multiple Lines (Enter makes a new line)
// 2 - Email ('@' character is on last row)
// 3 - Numeric (only numbers, 0123456789)
native bool ShowSteamVirtualKeyboard(int iVKMode, int iTextFieldX, int iTextFieldY, int iTextFieldWidth, int iTextFieldHeight);
// GetOverlaysInfo function usage example:
// {
//     object itemsInfo[2]; // MUST BE of size [2] !!!
//     int itemsInfoSize = GetOverlaysInfo(&itemsInfo);
//     for (int i = 0; i < itemsInfoSize; i++) {
//         string itemId = itemsInfo[i].itemId;
//         string itemPath = itemsInfo[i].itemPath;
//         // itemId: Steam UGC ID of the item (int64 as a string)
//         // itemPath: Full absolute path to the item's content directory (somewhere inside steamapps)
//         //           (^ can be used in FINDFILESINTODIRECTORY!)
//     }
// }
native int GetOverlaysInfo(ref paOutOverlaysInfo);
//Если включен оверлей стим, то ссылка откроется в оверлее, если оверлей отключен, то проверит на фулскрин, если фулскрина нет, то откроет ссылку вы браузере
native bool GameOverlayToWebPage(string url);
native bool IsInSafeMode();
//if true then either
//1: the game crashed and the user chose safe mode
//OR
//2: enabled in engine.ini mod_safe_mode = 1
native int ShellExecuteOpenURL(string url);
native bool SteamSetRichPresence(string sKey, string sValue); // rich presence stuff
native bool SteamClearRichPresence(); // wipe out all current rich presence
native bool BIsSubscribedApp(int uAppID); // true - user has license to specified App ID
native bool GameOverlayToWebPageModal(string sWebPageURL); // for Call To Actions //откывает нужную ссылку в стим оверлее
native bool HasPlaytestRewardNative(); // true - user is in Tichingitu ach list

#libriary "script_libriary_test"
#libriary "dx9render_script_libriary"
#libriary "SteamApiScriptLib"

#event_handler(NEW_GAME_EVENT,"NewGame");
#event_handler(GAME_OVER_EVENT,"GameOverE");
#event_handler("Control Activation","ProcessControls");
#event_handler("MainMenuKey","ProcessMainMenuKey");
#event_handler("InterfaceKey","ProcessInterfaceKey");
#event_handler("CameraPosAng","ProcessCameraPosAng");
#event_handler("SeaDogs_ClearSaveData", "ClearLocationsSaveData");
#event_handler("StopQuestCheckProcessFreeze","ProcessStopQuestCheckProcessFreeze"); // boal 240804

float fHighPrecisionDeltaTime;	

void ProcessStopQuestCheckProcessFreeze() // boal 240804
{
    bQuestCheckProcessFreeze = false;
    wdmLockReload            = false;
    QuestsCheck(); // выполнить отложенные

    if (rand(20) == 10) // 16.01.06 не помню уже зачем разлочивал ГГ, но на деле мешает до квестам, но если где повиснет, то спасет ф2
    {
    	DoQuestCheckDelay("pchar_back_to_player", 0.5); // если в диалоге залочило, вернём управление
    }
}

object Camera;

void ProcessCameraPosAng()
{
	Camera.Pos.x = GetEventData();
	Camera.Pos.y = GetEventData();
	Camera.Pos.z = GetEventData();

	Camera.Ang.x = GetEventData();
	Camera.Ang.y = GetEventData();
	Camera.Ang.z = GetEventData();
}

void proc_break_video()
{
	trace("proc_break_video()");
	if (sti(InterfaceStates.videoIdx) != 1)
	{
		//InterfaceStates.videoIdx = -1;
		//Event("ievntEndVideo");
	}
}

void Main()
{
	screenscaling = BI_COMPARE_HEIGHT;
	ControlsInit(GetTargetPlatform(),true);
	nTeleportLocation = 1;
	
	NationsInit();
	EncountersInit();
	CannonsInit();
	ShipsInit();
	IslandsInit();
	WeatherInit();
	InitPerks();

	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
	
	SetEventHandler("Control Activation","proc_break_video",0);
	InterfaceStates.Launched = false;
	SetEventHandler(EVENT_END_VIDEO,"Main_LogoVideo",0);
	InterfaceStates.videoIdx = 0;
	Event(EVENT_END_VIDEO);

	SetGlowParams(1.0, 50, 2);
}

void Main_InitGame()
{
	nTeleportLocation      = 1;
    bDisableLandEncounters = false;
	bDisableCharacterMenu  = false;
	bWorldAlivePause       = true;
	bPauseContrabandMetro  = false;
	bMonstersGen           = false;
	bLandEncountersGen     = true;
	chrDisableReloadToLocation = false;
	bDisableFastReload         = false;
	bDisableMapEnter           = false;
	bDisableSailTo             = false;
	bEnableIslandSailTo        = false;
	bReloadCanBe               = false;
	bMapEnter                  = false;
	bQuestDisableMapEnter      = false;
    bAbordageStarted           = false;
    bCabinStarted              = false;
	bDeckBoatStarted           = false;
	bWMEncounterCheck		   = false;
	LAi_IsCapturedLocation     = false;
	LAi_IsBoarding             = false;
	LAi_restoreStates          = false;
	LAi_boarding_process       = false;
	boarding_location          = -1;
	
	NationsInit();
	EncountersInit();
	CannonsInit();
	ShipsInit();
	IslandsInit();
	WeatherInit();
	InitPerks();
	
	if(LoadSegment("store\initGoods.c"))
	{
		InitGoods();
		UnloadSegment("store\initGoods.c");
	}

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces_main();
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}
}
void Main_LogoVideo()
{
	LoadGameOptions();
	
	if(CheckAttribute(&InterfaceStates,"SkipStartVideo")) //Hokkins: убираем вступительные видео, чтобы быстрее грузиться
	{
		if(sti(InterfaceStates.SkipStartVideo) != 0)
		{
			DelEventHandler(EVENT_END_VIDEO,"Main_LogoVideo");
			// HardCoffe загрузить библиотеку vlc чтобы первое воспроизводимое видео загружалось быстрее
			if (GetTargetPlatform() == "pc") CreateEntity(&aviVideoObj,"CAviPlayer");
			else CreateEntity(&aviVideoObj,"WMVideoPlay");
			SendMessage(&aviVideoObj,"l",MSG_SET_VIDEO_LOAD_LIBVLC);
			// <--
			DeleteClass(&aviVideoObj);
			Event("DoInfoShower","sl","game prepare",true);
			SetEventHandler("frame","Main_Start",1);
			return;
		}
	}
	
	int i = sti(InterfaceStates.videoIdx);
	switch(i)
	{
	case 0:
		InterfaceStates.videoIdx = 1;
		StartPostVideo("Blackmark",1);
	break;

	case 1:
		InterfaceStates.videoIdx = 2;
		StartPostVideo("ReCon",1);
	break;

	case 2:
		InterfaceStates.videoIdx = 3;
		StartPostVideo("Valkyrie",1);
	break;

//	default:
		DelEventHandler(EVENT_END_VIDEO,"Main_LogoVideo");
		DeleteClass(&aviVideoObj);
		Event("DoInfoShower","sl","game prepare",true);
		SetEventHandler("frame","Main_Start",1);
//	break;
	}

}

void Main_Start()
{
	ReloadProgressStart();
	
	DelEventHandler("Control Activation","proc_break_video");
	DelEventHandler("frame","Main_Start");

	if( GetTargetPlatform()=="pc" )	ControlsInit(GetTargetPlatform(),false);

	string gameProfile = GetLastProfileFromCurrentProfile();
	if (gameProfile == "")
		LoadPlayerProfileDefault();
	else
		PlayerProfile.name = gameProfile;
    
	ReloadProgressUpdate();
	InitGame();
	ReloadProgressUpdate();

	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0;
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;


	InterfaceStates.Buttons.Load.enable = true;
	
	Event("DoInfoShower","sl","game prepare",false);

	StartLanguageSetting(LanguageGetLanguage());
	LaunchMainMenu();

	CharacterIsDead(GetMainCharacter());
	
	ReloadProgressEnd();
	KZ|Folder();
}

void SaveGame()
{
	string saveName = GetEventData();
	string saveData = GetEventData();
	DelEventHandler("evntSave","SaveGame");

	aref arTmp;
	if( !GetEntity(arTmp,"fader") )
	{
		//implemet interface
		//LaunchQuickSaveMenu();
		pchar.version_number = 104;
		SaveEngineState(saveName);
		ISetSaveData(saveName,saveData);
	}

	//hide interface
	PostEvent("DoInfoShower",1,"sl","save game",false);
	DeleteEntitiesByType("scrshoter");
	HideQuickSaveMenu();
	SaveLastSavePathToCurrentProfile(saveName);
	SaveLastProfileToCurrentProfile();
}

void LoadGame()
{
	string saveName = GetEventData();
	DelEventHandler("evntLoad","LoadGame");

	string retStr="";
	SendMessage(&GameInterface,"lse",MSG_INTERFACE_GET_SAVE_DATA,saveName,&retStr);
	if( retStr=="" ) {return;}
	
    PauseParticles(true); //fix вылета у форта
    // не помогло DeleteFortEnvironment();  //fix
    
	PauseAllSounds(); // boal fix
    ResetSound();  // fix
    // вылетам у форта НЕТ -->
    if (bSeaActive && !bAbordageStarted)
    {
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--

	DeleteEntities();
	ClearEvents();
	ClearPostEvents();
	SetTimeScale(1.0);
	TimeScaleCounter = 0;

    string loadScr="";
    switch (rand(4))
    {
        case 0 :
			loadScr = "loading\Escape_Town.tga";
		break;
		case 1 :
			loadScr = "loading\Standsea_" + rand(3) + ".tga";
		break;
		case 2 :
			loadScr = "loading\lookat.tga";
		break;
		case 3 :
			loadScr = "loading\shipcannon.tga";
		break;
		case 4 :
			loadScr = "loading\rescue.tga";
		break;
	}
	
	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	//SendMessage(&reload_fader, "ls", FADER_PICTURE0, "interfaces\card_desk.tga");
	SendMessage(&reload_fader, "ls",FADER_PICTURE0, loadScr);
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	ReloadProgressStart();
	pchar.savegamename = saveName;
	SetEventHandler("frame","LoadGame_continue",1);
	
	iCalculateSaveLoadCount("Load");
}

void LoadGame_continue()
{
	DelEventHandler("frame","LoadGame_continue");
	FreezeGroupControls(curKeyGroupName,true);
	LoadEngineState(pchar.savegamename);
}

void InterfaceDoExit()
{
	DelEventHandler("frame","InterfaceDoExit");
	InterfaceStates.Launched=false;
	if(sti(InterfaceStates.doUnFreeze)==true)
	{
		SendMessage(&GameInterface,"l",MSG_INTERFACE_RELEASE);
		if(!IsEntity(&aviVideoObj))
		{
			if( bSeaActive && !bAbordageStarted )
			{
				LayerFreeze(SEA_REALIZE,false);
				LayerFreeze(SEA_EXECUTE,false);
			}
			else
			{
				LayerFreeze(REALIZE,false);
				LayerFreeze(EXECUTE,false);
			}
		}
		DeleteAttribute(&GameInterface,"");
	}
	switch(interfaceResultCommand)
	{
		case RC_INTERFACE_FORTCAPTURE_EXIT:
			ReloadAfterFortCapture();
		break;

		case RC_INTERFACE_DO_NOTHING:
		break;
			
		case RC_INTERFACE_MAIN_MENU_EXIT:
			GameOverMainMenu();
		break;
		
		case RC_INTERFACE_DO_NEW_GAME:
			DeleteAttribute(&TEV, "MENUVOLUME");
			InterfaceStates.doUnFreeze = false;
			DeleteEntities();
			ClearEvents();
			ClearPostEvents();

            if (CheckAttribute(pchar, "HeroParam")) // признак, что есть герой
            {
				trace("Main_InitGame");
				Main_InitGame(); // boal вынес все в одинметод, новая игра из страой глючит
			}
			else
			{
				if(LoadSegment("Interface\BaseInterface.c"))
				{
					InitBaseInterfaces_main();
					InitBaseInterfaces();
					UnloadSegment("Interface\BaseInterface.c");
				}
			}
			LaunchSelectCharacter();
		break;
		
		case RC_INTERFACE_DO_LOAD_GAME:
			if(CheckAttribute(&InterfaceStates,"Buttons.Resume.enable") && sti(InterfaceStates.Buttons.Resume.enable) == true)
			{
				LaunchLoadGame(false);
			}
			else
			{
				LaunchLoadGame(true);
			}
		break;
		
		case RC_INTERFACE_DO_SAVE_GAME:
			LaunchSaveGame();
		break;

		case RC_INTERFACE_DO_OPTIONS:
			LaunchOptionScreen();
		break;
			
		case RC_INTERFACE_DO_CREDITS:
		    LaunchAboutScreen();
		break;
		
		case RC_INTERFACE_DO_RESUME_GAME:
		break;
		
		case RC_INTERFACE_RANSACK_MAIN_EXIT:
			Return2SeaAfterAbordage();
		break;
		
		case RC_INTERFACE_CHARACTER_SELECT_EXIT:
			DeleteEntities();
			ClearEvents();
			SetEventHandler("frame","NewGame",1);
			InterfaceStates.doUnFreeze = false;
		break;
		
		case RC_INTERFACE_TO_CHAR:
			pchar = GetMainCharacter();
			LaunchCharacter(pchar);
		break;
		
		case RC_INTERFACE_TO_SHIP:
			LaunchShipState();
		break;
		
		case RC_INTERFACE_TO_LOGBOOK:
			LaunchQuestBook();
		break;
		
		case RC_INTERFACE_TO_ITEMS:
			LaunchItems(); // TODO
		break;

		case RC_INTERFACE_LAUNCH_GAMEMENU:
			LaunchGameMenuScreen();
		break;
		
		// Warship -->
		case RC_INTERFACE_BEST_MAP:
			LaunchBestMapScreen(); // Смотрим отличную карту
			break;
		// <-- Warship
		
		case RC_INTERFACE_MAPVIEW:
			LaunchMapViewScreen(); // Смотрим атлас карт
		break;
		
		//evganat - энциклопедия
		case RC_INTERFACE_ENCYCLOPEDIA:
			LaunchEncyclopedia();
		break;
		
		case RC_INTERFACE_MUSIC_SETTINGS:
		    LaunchMusicSettings();
        break;

		case INTERFACE_CHARACTER_ALL:
			LaunchMainCharacter();
        break;

		case INTERFACE_NATIONRELATION:
			LaunchNationRelation();
        break;

		case RC_INTERFACE_TO_TRADEBOOK:
			LaunchTradeBook();
        break;

		case RC_INTERFACE_TO_ALCHEMY:
			LaunchAlchemy();
        break;
	}
}

void EngineLayersOffOn(bool on)
{
	on = !on;
	if( on ) 
	{
		LayerFreeze(REALIZE,on);
		LayerFreeze(EXECUTE,on);
		LayerFreeze(SEA_REALIZE,on);
		LayerFreeze(SEA_EXECUTE,on);
	}
	else 
	{
		if(bSeaActive && !bAbordageStarted) 
		{
			LayerFreeze(SEA_REALIZE,on);
			LayerFreeze(SEA_EXECUTE,on);
		} 
		else 
		{
			LayerFreeze(REALIZE,on);
			LayerFreeze(EXECUTE,on);
		}
	}
}

string seadogs_saveFrom = "";

void OnSave()
{
	seadogs_saveFrom = "";
	if(IsEntity(&worldMap) != 0)
	{
		seadogs_saveFrom = "world map";
	}
	else
	{
		if(IsEntity(&AISea) != 0)
		{
			Sea_Save();
			seadogs_saveFrom = "sea";
		}
		else
		{
			int ldLoc = FindLoadedLocation();
			if(ldLoc >= 0)
			{
				seadogs_saveFrom = "location";
				SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_SETCHRPOSITIONS);
				LAi_SaveInfo();
				PostEvent("SeaDogs_ClearSaveData", 400, "a", &Locations[ldLoc]);
			}
			else
			{
				Trace("OnSave() -> unknow character location");
				return;
			}
		}
	}
	
	/*Как будет работать с автосэйвом перед абордажем: если деньги есть (метод вернул 1) - делаем сэйв, снимаем деньги.
	Если метод вернул 0 (денег нету) - сэйв все-равно будет, но денег не снимут и не будет лога
	Если метод вернёт 2 (платный s/l отключен) - сэйв
	По идее, с включенным платным s/l и неимением денег на него, в эту процедуру, кроме как автосэйвом, никак не пройти*/
	if(iPayForSaveLoad() == 1)
	{
		int iMoney = CalculatePayForSaveLoadStatistic("Save");
		Log_Info(GetConvertStr("Pay for save", "interface_strings.txt") + FindMoneyString(iMoney));
	}

	iCalculateSaveLoadCount("Save");

}

void ClearLocationsSaveData()
{
	aref loc = GetEventData();
	if (loc) SendMessage(loc, "l", MSG_LOCATION_CLRCHRPOSITIONS);
}

int actLoadFlag = 0;

void OnLoad()
{
	DeleteAttribute(&TEV, "MAINMENU");
	actLoadFlag = 1;
    
	if(screenscaling < 50) screenscaling = BI_COMPARE_HEIGHT;
	
	DeleteAttribute(pchar, "abordage_active_count");
	FreezeGroupControls(curKeyGroupName,false);

	if( CharacterIsDead(pchar) ) {
		pchar.chr_ai.hp = 1.0;
	}

	Nation_InitAfterLoading();

	ResetSoundBoarding();

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		//InitBaseInterfaces_main();
		InitBaseInterfaces();
		InitInterfaceTables();
		UnloadSegment("Interface\BaseInterface.c");
	}

    //если требуется переиничиваем итемы сохраняя при этом изменения уже внесенные в итемы в течении игры
	if (GetArraySize(&Items) != TOTAL_ITEMS || GetArraySize(&itemModels) != ITEMS_QUANTITY)
	{
	    OnLoadUpdateItemArrays();
	}
	
	ReloadProgressUpdate();
	
	DialogsInit();
	//IslandsInit();
	//LocationInit();

	ReloadProgressUpdate();

	InitCharacterEvents();
	ReloadProgressUpdate();

	QuestsInit();
	ReloadProgressUpdate();

	PDMQuestsInit();
	ReloadProgressUpdate();
	
	InitTeleport();
	ReloadProgressUpdate();

	InitParticles();
	ReloadProgressUpdate();
    
    ApplyMigrations();
    
	RefreshShipHulls(-1);
	ReloadProgressUpdate();

	WeatherInit();
	ReloadProgressUpdate();

	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;
	
	if(seadogs_saveFrom == "location")
	{
		ref mainchar;
		mainchar = GetMainCharacter();
		// boal: лажа это!!  есть actLoadFlag  //mainchar.isload = 1;
		LoadMainCharacterInFirstLocation(mainchar.location,"", mainchar.location.from_sea);
		int ldLoc = FindLoadedLocation();
		if(ldLoc >= 0)
		{
			SendMessage(&Locations[ldLoc], "l", MSG_LOCATION_TLPCHRPOSITIONS);
		}
	}
	else
	{
		if (seadogs_saveFrom == "sea")
		{
			Sea_Load();
 		}
		else
		{
			if(seadogs_saveFrom == "world map")
			{
				wdmLoadSavedMap();
			}
			else
			{
				Trace("Unknow seadogs_saveFrom == " + seadogs_saveFrom);
			}
		}
	}

	//ReloadEndFade();
	EngineLayersOffOn(true);
	//NewGame();
	bIsRepairingProcess = false;
	DialogRun = false;
	InterfaceStates.Launched = false;
	
	ReloadProgressUpdate();

	PerkLoad(false);
	TEV.RefreshActiveSeaPerks = "";

	ReloadProgressUpdate();
	
	LoadGameOptions();

	ReloadProgressEnd();

	if( CheckAttribute(&InterfaceStates,"WorldSituationUpdateStep") &&
		sti(InterfaceStates.WorldSituationUpdateStep) < 10 )
	{
		Event("EvSituationsUpdate", "l", sti(InterfaceStates.WorldSituationUpdateStep));
	}

	actLoadFlag = 0;
	
	int iMoney;
	if(iPayForSaveLoad() != 2)
	{
		iMoney = CalculatePayForSaveLoadStatistic("Load");
		Log_Info(GetConvertStr("Pay for save", "interface_strings.txt") + FindMoneyString(iMoney));
	}
	
	iCalculateSaveLoadCount("Load");
	
	string sCondition;
	for(int i = 0; i < MAX_GAMEMODE_CONDITIONS; i++)
	{
		sCondition = GameModeConditions[i];
		if(sCondition == "") continue;
		SetEventHandler(sCondition, sCondition, 0); // Обновим ивент, т.к. терся
		Log_TestInfo("Обновлено прерывание - " + sCondition);
	}
	
	/*if(LoadSegment("items\initItems.c"))
	{
		InitItems();
		UnloadSegment("items\initItems.c");
	}
	InitInteractiveInterface();*/
	
	SaveStartGameParam();
}

void NewGame()
{
	DeleteEntities();
	DelEventHandler("frame","NewGame");

	CreateEntity(&LanguageObject,"obj_strservice");
	CreateEntity(&reload_fader, "fader");
	//SendMessage(&reload_fader, "ls", FADER_PICTURE0, "interfaces\card_desk.tga");
	SendMessage(&reload_fader, "ls",FADER_PICTURE0, RandPhraseSimple("loading\preparelogo.tga", "loading\preparelogo.tga"));
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);

	SetEventHandler("frame","NewGame_continue",1);
}

void NewGame_continue()
{
	DeleteAttribute( pchar, "abordage_active_count" );  // это тут не работает, но и не мешает Boal

	ReloadProgressStart();

	DelEventHandler("frame","NewGame_continue");

	if(LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}

	InitGame();
	
	ReloadProgressUpdate();
	
	CreateColonyCommanders();

	ReloadProgressUpdate();

	SetNames();
	ReloadProgressUpdate();
	
	Environment.date.hour = worldMap.date.hour;
	Environment.date.min = worldMap.date.min;
	Environment.date.sec = worldMap.date.sec;
	Environment.time = stf(worldMap.date.hour) + stf(worldMap.date.min)/60.0 + stf(worldMap.date.sec)/3600.0; //boal
	Environment.date.year = worldMap.date.year;
	Environment.date.month = worldMap.date.month;
	Environment.date.day = worldMap.date.day;

	InterfaceStates.WorldSituationUpdateStep = 100;
	InterfaceStates.Buttons.Resume.enable = true;
	InterfaceStates.Buttons.Save.enable = true;
	InterfaceStates.Buttons.Load.enable = true;
	
	pchar = GetMainCharacter(); //fix
	initNewMainCharacter(); // все там
	ReloadProgressUpdate();
	
	InitPsHeros();   // boal 05/07/06 ПГГ
	ReloadProgressUpdate();
	
    RumourInit();  //homo 23/06/06
	ReloadProgressUpdate();
	
	ActivateTimeEvents();
	
	ReloadProgressUpdate();
	
	if (bWildCaribbean)
	{
		SetCharacterPerk(pchar, "WildCaribbean");
	}
	//LoadMainCharacterInFirstLocation(sTeleportLocName, sTeleportLocator, sTeleportLocName);
	startGameWeather = true;
	if (startHeroType == 1) //21/07/07 homo для Блада даем другое начало
    {
        //homo тут это должно точно работать
        RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
        RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
        RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
        RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
        RemoveCharacterEquip(pchar, PATENT_ITEM_TYPE);
        RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
        RemoveCharacterEquip(pchar, MAPS_ITEM_TYPE);
        DeleteAttribute(pchar, "items");
        InterfaceStates.startGameWeather = FindWeather("20 Hour");
        LoadMainCharacterInFirstLocationGroup("Estate", "reload", "reload1");
    }
/*    else if (startHeroType == 2)  // линейка Граммона
    {
        InterfaceStates.startGameWeather = FindWeather("20 Hour");
        LoadMainCharacterInFirstLocationGroup("GrammonEstate", "goto", "goto12");
    }*/
    else  // стандартный тутор
    {
        InterfaceStates.startGameWeather = FindWeather("11 Hour");
        LoadMainCharacterInFirstLocationGroup("Ship_deck_Low", "goto", "goto4");
    }
	
	ReloadProgressUpdate();
	
	//InitTowns();
	UpdateCrewInColonies(); // пересчет наёмников в городах
	ReloadProgressUpdate();

	//InitSmuggling();
	InitInteractiveInterface();
	ReloadProgressEnd();
}

void InitGame()
{
	InitSound();

	ReloadProgressUpdate();

	DeleteSeaEnvironment();
	//CharactersInit();
	if(LoadSegment("worldmap\worldmap_init.c"))
	{
		wdmInitWorldMap();
		UnloadSegment("worldmap\worldmap_init.c");
	}
    InitPerks();
    ReloadProgressUpdate();
    
	IslandsInit();
	ReloadProgressUpdate();
	
	LocationInit();
	ReloadProgressUpdate();
	
	DialogsInit();
	ReloadProgressUpdate();
	
	InitTeleport();
	ReloadProgressUpdate();
	
	InitParticles();
	ReloadProgressUpdate();

	ColoniesInit();
	ReloadProgressUpdate();

    if(LoadSegment("items\initItems.c"))
	{
		InitItems();
		UnloadSegment("items\initItems.c");
	}

	ReloadProgressUpdate();
	GenerateGenerableItems(); // <-- ugeen генерация предметов
	
	ReloadProgressUpdate();
	
	CharactersInit();

	ReloadProgressUpdate();

	if(LoadSegment("store\initStore.c"))
	{
		InitStores();
		UnloadSegment("store\initStore.c");
	}
	
	QuestsInit();
	ReloadProgressUpdate();

	
	SeaAIGroupsInit();
	ReloadProgressUpdate();
	
	InitQuestMapEncounters();
	ReloadProgressUpdate();
	
	//InitLandRandomEncounters();
	//ReloadProgressUpdate();

	//SetNextWeather("10 Hours");

	ResetQuestMovie();
	ReloadProgressUpdate();
	
	LoadGameOptions();

	ReloadProgressUpdate();
	InfoShowSetting();
}

int counter = 0;
void ProcessControls()
{
	string itemID, ControlName = GetEventData();
 	aref arItm;
 	float kZoom, newTimeScale;
	bool bFT = CheckAttribute(&TEV, "AltMode.FastTravel");
	
	if (ControlName == "QuickSave") { MakeQuickSave(); }
	if (ControlName == "QuickLoad") { MakeQuickLoad(); }

    if (dialogRun) return;
	if (sti(InterfaceStates.Launched)==true) return;
	
	if (ControlName == "WhrPrevWeather")	{ Whr_LoadNextWeather(-1); }
	if (ControlName == "WhrNextWeather")	{ Whr_LoadNextWeather(1); }
	if (ControlName == "WhrUpdateWeather")	{ Whr_UpdateWeather(); }

	if (bSeaActive && !bAbordageStarted)
	{
		switch (ControlName)
		{
			case "MainMenu": 			ProcessMainMenuKey();		break;
			case "MainMenuDouble": 		ProcessMainMenuKey(); 		break;
			case "Interface": 			ProcessInterfaceKey(); 		break;
			case "CharacterShipMenu": 	ProcessShipStateKey(); 		break;
			case "LogbookMenu": 		ProcessQuestBookKey(); 		break;
			case "ItemsMenu": 			ProcessItemsKey(); 			break;
			case "NationsMenu": 		ProcessNationRelationKey(); break;
			case "AlchemyKey": 			ProcessAlchemyKey(); 		break;

			case "Sea_CameraSwitch": 	SeaCameras_Switch(); 		break;
			case "Ship_Fire": 			Ship_DoFire(); 				break;

			case "Tele": 				Sea_ReloadStart(); 			break;
		}
	}
	else
	{
		switch (ControlName)
		{
			case "MainMenu": 			ProcessMainMenuKey();		break;
			case "MainMenuDouble": 		ProcessMainMenuKey(); 		break;
			case "Interface": 			ProcessInterfaceKey();		break;
			case "CharacterShipMenu": 	ProcessShipStateKey(); 		break;
			case "LogbookMenu": 		ProcessQuestBookKey(); 		break;
			case "ItemsMenu": 			ProcessItemsKey(); 			break;
			case "NationsMenu": 		ProcessNationRelationKey(); break;
			case "AlchemyKey": 			ProcessAlchemyKey(); 		break;
			case "Tele":				StartQuickTeleport();		break;
			case "TeleBack": 			Teleport(-1); 				break;
			case "Action":
				//DumpAttributes(loadedLocation/*loadedLocation.reload.reload1.x*/);
				//trace("Y: " + loadedLocation.reload.reload1.y);
				//trace("Z: " + loadedLocation.reload.reload1.z);
			break;
		}
	}
	
    // boal 27.11.03 time -->
	if (HasStrEx(ControlName, "TimeScaleFaster,TimeScaleSlower", "|"))
	{
		if (CheckAttribute(&TEV, "StopTimeScale")) return; //квестовые моменты
		if (CheckAttribute(loadedLocation, "type") && loadedLocation.type == "Underwater") return; //запрет ускорения под водой
		DeleteAttribute(pchar, "pause");
		if (HasStr(ControlName, "Faster"))
		{
			if (TimeScaleCounter >= 12)
			{
			    TimeScaleCounter += 4;
			}
			else
			{
                if (TimeScaleCounter >= 4)
				{
				    TimeScaleCounter += 2;
				}
				else
				{
					TimeScaleCounter++;
				}
			}
		}
		else
		{
            if (TimeScaleCounter >= 16)
			{
			    TimeScaleCounter -= 4;
			}
			else
			{
				if (TimeScaleCounter >= 6)
				{
				    TimeScaleCounter -= 2;
				}
				else
				{
					TimeScaleCounter--;
				}
			}
		}

		if (true) // MOD_SKILL_ENEMY_RATE > 1) // запрет 0.25 скорости
		{
			if (!bBettaTestMode && TimeScaleCounter < -2)
				TimeScaleCounter = -2;
		}
 
		if (bSeaActive && !bAbordageStarted)
		{
			if (bDisableMapEnter)
			{
				if (TimeScaleCounter > 20)
					TimeScaleCounter = 20; // бой в море x6
			}
			else
			{
				if (TimeScaleCounter > 28)
					TimeScaleCounter = 28; // море x8
			}
		}
		else
		{
			if (IsEntity(&worldMap))
			{
				if (TimeScaleCounter > 16)
					TimeScaleCounter = 16; // карта x5
			}
			else
			{
				if (TimeScaleCounter > 8)
					TimeScaleCounter = 8; // суша x3
			}
		}

		newTimeScale = 1 + (TimeScaleCounter)*0.25; // GetSeaTimeScale()
		if (newTimeScale < 0) //don't wanna crash the game
		{
			TimeScaleCounter = -4;
			newTimeScale = 0;
		}

		if (TimeScaleCounter == 0) //back to normal
		{
			if(IsPerkIntoList("TimeSpeed"))
			{
				SetTimeScale(1.0);
				DelPerkFromActiveList("TimeSpeed");
			}
		}
		else
		{
			SetTimeScale(newTimeScale);
			SetCooldownTextForActivePerkInList("TimeSpeed", newTimeScale, 0);
		}
	}
	// boal <--
	
	// KZ > реф кода от belamour на быстрые переходы по ALT
	if (HasStr(ControlName, "AltModeFastTravel_"))
	{
		if (bFT && !GetEntity(arItm, "fader"))
		{
			HKT_Button(ControlName);
			return;
		}
	}
	
	if (HasStr(ControlName, "AltModificator"))
	{
		Log_Clear();
		if (!IsEntity(&ILogAndActions) || !bFastEnable() || GetEntity(arItm, "fader")) return;
		
		TEV.AltMode.FastTravel = true;
		
		itemID = "pl";
		if (ControlName == "AltModificatorOff")
		{
			itemID = "min";
			ModifyTextHide();
		}
		
		SetTimeScale(1.0);
		DelPerkFromActiveList("TimeSpeed");
		PlaySound(itemID + "us_s");
		ModifyTextInfo();
	}
	else
	{
		switch(ControlName)
		{
			case "TimeScale":
				DeleteAttribute(pchar, "pause");
				if (CheckAttribute(&TEV, "StopTimeScale")) return; //квестовые моменты
				if (CheckAttribute(loadedLocation, "type") && loadedLocation.type == "Underwater") return; //запрет ускорения под водой
				if(IsPerkIntoList("TimeSpeed"))
				{
					SetTimeScale(1.0);
					TimeScaleCounter = 0;
					DelPerkFromActiveList("TimeSpeed");
				}
				else
				{
					if (CheckAttrValue(&InterfaceStates, "TimeSpeedAccel", "1"))
					{
						switch (GetPos(1))
						{
							case 1:
								TimeScaleCounter = 8;		// суша x3
							break;
							case 2:
								if (bDisableMapEnter)
									TimeScaleCounter = 20;	// бой в море x6
								else
									TimeScaleCounter = 28;	// море x8
							break;
							case 3:
								TimeScaleCounter = 16;		// карта x5
							break;
						}

						newTimeScale = 1 + (TimeScaleCounter) * 0.25;
						SetTimeScale(newTimeScale);
						SetCooldownTextForActivePerkInList("TimeSpeed", newTimeScale, 0);
					}
					else
					{
						SetTimeScale(GetSeaTimeScale());
						TimeScaleCounter = 4;
						SetCooldownTextForActivePerkInList("TimeSpeed", GetSeaTimeScale(), 0);
					}
				}
			break;
		
			case "VK_PAUSETimePause":
				if (!CheckAttribute(pchar, "pause"))
				{
					pchar.pause = true;
					SetTimeScale(0.0);
					TimeScaleCounter = -3;
					AddPerkToActiveList("TimeSpeed");
				}
				else
				{
					DeleteAttribute(pchar, "pause");
					SetTimeScale(1.0);	
					DelPerkFromActiveList("TimeSpeed");
					TimeScaleCounter = 0;
				}
			break;
			
			case "WMapCancel":
				if(IsEntity(&worldMap))
				{
					pchar.space_press = 1;
					DeleteAttribute(pchar, "SkipEshipIndex");// boal
				}
			break;
			
			case "Map_Best":
				if(CheckCharacterItem(PChar, "Map_Best") || bBettaTestMode)
					LaunchBestMapScreen();
			break;

			// --> ugeen
			case "MapView":
				if (or(bSeaActive && !bAbordageStarted, bLandInterfaceStart && !LAi_IsFightMode(pchar)) || IsEntity(&worldmap))
				{ // изврат - но по другому никак
					if (CheckCharacterItem(PChar, "MapsAtlas"))
						LaunchMapViewScreen();
				}
			break;
			// <-- ugeen
			
			case "ChrFightMode":
				ModifyTextHide();
			break;

			case "OfficersCharge":
				if (!bFT && GetOfficersQuantity(pchar) > 0)
				{
					pchar.OfficerAttRange = 35.0;
					OfficersFollow();
					Log_SetStringToLog(GlobalStringConvert("Officer_Attack"));
				}	
			break;

			case "OfficersFollow":
				if (!bFT && GetOfficersQuantity(pchar) > 0)
				{
					pchar.OfficerAttRange = 7.0;
					OfficersFollow();
					Log_SetStringToLog(GlobalStringConvert("Officer_Follow"));
				}	
			break;

			case "OfficersHold":
				if (!bFT && GetOfficersQuantity(pchar) > 0)
				{
					pchar.OfficerAttRange = 7.0;
					OfficersHold();
					Log_SetStringToLog(GlobalStringConvert("Officer_Stay"));
				}	
			break;
			
			/*// boal -->
			case "ChrBackward": //ChrStrafeLeft ChrStrafeRight
				if (bLandInterfaceStart && LAi_IsFightMode(pchar))
				{
					pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
					if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
				}
			break;
			
			case "ChrStrafeLeft":
				if (bLandInterfaceStart && LAi_IsFightMode(pchar))
				{
					pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
					if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
				}
			break;
			
			case "ChrStrafeRight":
				if (bLandInterfaceStart && LAi_IsFightMode(pchar))
				{
					pchar.chr_ai.energy = stf(pchar.chr_ai.energy) - 3;
					if (stf(pchar.chr_ai.energy) < 0) pchar.chr_ai.energy = 0;
				}
			break;*/ //убираем расход энергии из-за любого передвижения влево и вправо EvgAnat
			
			case "BOAL_UsePotion": // boal KEY_C
				if (!bFT && bLandInterfaceStart)
				{
					if(LAi_IsPoison(pchar)) 
					{
						if (UseBestPotion(pchar, true) == 0) 
						{
							if (UseBestPotion(pchar, false) == 0) 
							{
								Log_SetStringToLog(GlobalStringConvert("Potion_Not_Found"));
							}
						}
					}
					else 
					{
						if (UseBestPotion(pchar, false) == 0) 
						{
							if (UseBestPotion(pchar, true) == 0) 
							{
								Log_SetStringToLog(GlobalStringConvert("Potion_Not_Found"));
							}
						}
					}	
				}
			break;
			
			// Warship 13.06.09 Выпить противоядие KEY_V
			case "UseAntidote":
				if (!bFT && bLandInterfaceStart)
				{
					if(FindCharacterAntidote(PChar, &itemID)) // В itemID запишется ID предмета, который можно использовать
					{
						DoCharacterUsedItem(PChar, itemID);
						Log_Info(GlobalStringConvert("Used_Antidote"));
					}
				}
			break;
			
			case "HK_SecondWind":
				if (!bFT && bLandInterfaceStart && GetCharacterPerkUsing(pchar, "SecondWind"))
				{
					PlaySound("SecondWind");
					ActivateCharacterPerk(pchar, "SecondWind");
				}
				else
				{
					if (!bFT && bLandInterfaceStart && curKeyGroupName == "FightModeControls")
						PlaySound("knopka");
				}
			break;
			
			case "BOAL_ActivateRush":  // boal KEY_F
				if (!bFT && bLandInterfaceStart && GetCharacterPerkUsing(pchar, "Rush"))
				{
					PlaySound("Rush");
					ActivateCharacterPerk(pchar, "Rush");
				}
				else
				{
					if (!bFT && bLandInterfaceStart && curKeyGroupName == "FightModeControls")
					{
						PlaySound("knopka");
					}
				}
			break;

			case "BOAL_DeadSearch":  // boal KEY_1
				if (!bFT && bLandInterfaceStart && !GetBan("Looting"))
				{
					if (Dead_FindCloseBody() != -1)
					{
						Dead_OpenBoxProcedure();
					}
					else
					{
						Log_Info(GlobalStringConvert("No_Search_Anyone"));
					}
				}
			break;
			
			case "BOAL_SetCamera":
				// KZ > на F10 перезапуск музыки
				if(LoadSegment("Debuger.c"))
				{
					ActiveF10Control();
					UnloadSegment("Debuger.c");
					Statistic_AddValue(PChar, "Cheats.KeyF10", 1);
				}
			break;

			case "BOAL_Control":
				// по F11 вызывает окно отладчика
				if (MOD_BETTATESTMODE == "On" || MOD_BETTATESTMODE == "Test")
				{
				   LaunchDebuderMenu();
				   Statistic_AddValue(PChar, "Cheats.KeyF11", 1);
				}
			break;
			
			case "Say": // KEY_Y
				// Интерфейс автозакупки товаров
				if (!bFT && bLandInterfaceStart && CheckOfficer("treasurer")) // Если есть казначей и ГГ находится на суше
					LaunchTransferGoodsScreen();
			break;
			
			case "TeleportActive":
				// KZ > на F4 временный интерфейс настройки непрерывной музыки
				if (false && LoadSegment("Debuger.c"))
				{
					ActiveF4Control();
					UnloadSegment("Debuger.c");
					Statistic_AddValue(PChar, "Cheats.KeyF4", 1);
				}
			break;
			
			case "BOAL_ControF5":
				if (MOD_BETTATESTMODE == "On")
				{
					if(LoadSegment("Debuger.c"))
					{
						ActiveF5Control();
						UnloadSegment("Debuger.c");
					}
					Statistic_AddValue(PChar, "Cheats.KeyF5", 1);
				}
			break;

			case "BOAL_ControF7":
				// по F7 вызывает окно отладчика
				if (MOD_BETTATESTMODE == "On")
				{
					if(LoadSegment("Debuger.c"))
					{
						ActiveF7Control();
						UnloadSegment("Debuger.c");
					}
					Statistic_AddValue(PChar, "Cheats.KeyF7", 1);
				}
			break;

			case "BOAL_Control2": // F12
				//Найти ближайшего видимого персонажа в заданном радиусе
				if(LoadSegment("Debuger.c"))
				{
					ActiveF12Control(); // можно меять пряв в рабочей игре
					UnloadSegment("Debuger.c");
					Statistic_AddValue(PChar, "Cheats.KeyF12", 1);
				}
			break;

			case "BOAL_ControlDebug": // VK_INSERT
				if (MOD_BETTATESTMODE == "On")
				{
					if(LoadSegment("Debuger.c"))
					{
						ActiveINSERTControl();
						UnloadSegment("Debuger.c");
					}
					Statistic_AddValue(PChar, "Cheats.KeyINSERT", 1);
				}
			break;
			// boal <--
			
			case "RunLootCollector":
				LootCollector();
			break;
			
			case "CharacterCamera_Forward":
				if(CheckAttribute(&locCamera, "zoom.lock"))
					break;
				if(!CheckAttribute(&locCamera, "zoom"))
					kZoom = 0.75;
				else
					kZoom = stf(locCamera.zoom);
				kZoom -= 0.05;
				if(kZoom < 0.5)
					kZoom = 0.5;
				locCamera.zoom = kZoom;
				locCameraSetRadius(stf(locCamera.maxRadius)*kZoom);
			break;

			case "CharacterCamera_Backward":
				if(CheckAttribute(&locCamera, "zoom.lock"))
					break;
				if(!CheckAttribute(&locCamera, "zoom"))
					kZoom = 0.75;
				else
					kZoom = stf(locCamera.zoom);
				kZoom += 0.05;
				if(!bBettaTestMode)
				{
					if(kZoom > 1.0) kZoom = 1.0;
				}
				locCamera.zoom = kZoom;
				locCameraSetRadius(stf(locCamera.maxRadius)*kZoom);
			break;
		}
	}
}

void Teleport(int step)
{
	nTeleportLocation = nTeleportLocation + step;
	if(nTeleportLocation >=	nLocationsNum) nTeleportLocation = 1;
	if(nTeleportLocation <=	0) nTeleportLocation = nLocationsNum - 1;
	
	sTeleportLocName = Locations[nTeleportLocation].id;
	Trace("Teleport to '" + sTeleportLocName + "'");

	ReleaseSound(0);
	ClearEvents();
	ClearPostEvents();
	DeleteEntities();
	SetEventHandler("frame","NewGame",1);
}

void ProcessMainMenuKey()
{
	if (interfacestates.buttons.resume.enable == "1")
	{
		//LaunchMainMenu();
		LaunchGameMenuScreen();
	}
}
// вызов меню по Ф2
bool CheckPossibleProcessInterfaceKey()
{
	if (CharacterIsDead(PChar)) return false;
	if (bSeaActive && !bAbordageStarted)
	{
		if (CheckAttribute(&BattleInterface,"ComState") && sti(BattleInterface.ComState) != 0)
			return false;
	}
	else
	{
		if (SendMessage(PChar, "ls", MSG_CHARACTER_EX_MSG, "CheckFightMode") != 0)
			return false;
		if (CheckAttribute(&objLandInterface,"ComState") && sti(objLandInterface.ComState) != 0)
			return false;
	}
	if (bDisableCharacterMenu)
	{
		if (!CheckAttribute(&TEV, "StopTimeScale"))
			Log_SetStringToLog(XI_ConvertString("You can`t launch menu"));
		return false;
	}
	if (bAbordageStarted && !bCabinStarted && !bDeckBoatStarted)
	{
		if (!CheckAttribute(&TEV, "StopTimeScale"))
			Log_SetStringToLog(XI_ConvertString("You can`t launch menu"));
		return false;
	}
	
	return true;
}

void ProcessNationRelationKey()
{
	if (CheckPossibleProcessInterfaceKey())
	{
		LaunchNationRelation();
	}
}

void ProcessQuestBookKey()
{
	if (CheckPossibleProcessInterfaceKey())
	{
		LaunchQuestBook();
	}
}

void ProcessInterfaceKey()
{
	if (CheckPossibleProcessInterfaceKey())
	{
		LaunchMainCharacter();
	}
}

void ProcessItemsKey()
{
	if (CheckPossibleProcessInterfaceKey())
	{
		LaunchItems();
	}
}

void ProcessShipStateKey()
{
	if (CheckPossibleProcessInterfaceKey())
	{
		LaunchShipState();
	}
}

void ProcessAlchemyKey()
{
	if (CheckPossibleProcessInterfaceKey())
	{
		LaunchAlchemy();
	}
}

void GameOverMainMenu()
{
	if (bSeaActive && !bAbordageStarted)
	{
		PauseParticles(true); //fix вылета у форта
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	PostEvent("LAi_event_GameOver", 100, "s", "MainMenu");
}

void GameOverE()
{
	// вылетам у форта НЕТ -->
    if (bSeaActive && !bAbordageStarted)
    {
		PauseParticles(true); //fix вылета у форта
		SendMessage(&AIBalls, "l", MSG_MODEL_RELEASE);
	}
	// вылетам у форта НЕТ <--
	GameOver("sea");
	DeleteSeaEnvironment();
}

void GameOver(string sName)
{
	string sM = "Action\Death\";
	string sP = "loading\";

	PauseAllSounds();
	ResetSound();
	EngineLayersOffOn(false);

	ClearEvents();
	ClearPostEvents();
	DeleteEntities();

	if (sti(InterfaceStates.Launched))
	{
		UnloadSegment(Interfaces[CurrentInterface].SectionName);
	}

	if (LoadSegment("Interface\BaseInterface.c"))
	{
		InitBaseInterfaces();
		UnloadSegment("Interface\BaseInterface.c");
	}

	InterfaceStates.showGameMenuOnExit = false;
	InterfaceStates.Buttons.Resume.enable = false;
	InterfaceStates.Buttons.Save.enable = false;

	InitSound();
	SetEventHandler(EVENT_END_VIDEO, "LaunchMainMenu_afterVideo", 0);

	switch (sName)
	{
		case "sea":
			sM += "Sea";
			sP += "deadsea";
		break;

		case "boarding":
			sM += "Sea";
			sP += "deadsea";
		break;

		case "land":
			sM += "Land";
			sP += "death_" + rand(2);
		break;

		case "town":
			sM += "Land";
			sP += "finalbad1";
		break;

		case "blood":
			sM += "Land";
			sP += "finalbad2";
		break;

		case "mutiny":
			sM += "Land";
			sP += "finalbad3";
		break;

		case "mainmenu":
			sP += "preparelogo";
		break;
	}

	StartPictureAsVideo(sP + ".tga", 3.5);
	if (sName != "mainmenu")
		KZ|Random("&" + sM + ",Action\Death");

	reload_location_index = -1;
	DeleteSeaEnvironment();
	InterfaceStates.BackEnvironmentIsCreated = false;

	LayerDelObject(EXECUTE, &InterfaceBackScene);
	LayerDelObject(REALIZE, &InterfaceBackScene);

	if (isEntity(&InterfaceBackScene))
	{
		DeleteClass(&InterfaceBackScene);
	}
}

// тяжкая игра - сайв токо в церкви 17.03.05 boal
bool QuickSaveGameEnabledHardcore()
{
    if (bBettaTestMode || !bHardcoreGame)
		return true;

	int idxLoadLoc = FindLoadedLocation();

	if (idxLoadLoc != -1)
	{
		if (CheckAttribute(&Locations[idxLoadLoc], "type"))
		{
			if (or(Pchar.BaseNation != PIRATE && or(Locations[idxLoadLoc].type == "church", Locations[idxLoadLoc].id == "GloriaChurch"), Pchar.BaseNation == PIRATE && or(Locations[idxLoadLoc].type == "tavern", Locations[idxLoadLoc].id == "FleuronTavern")))
				return true;
		}
	}

    return false;
}

bool CheckBattleSeaSaveEnabled()
{
	string sSaveEnable = GetConvertStr("SeaBattleMode_SaveEnable", KVL_MODS_FILE);
	string sSmallRegStr = GetStrSmallRegister(sSaveEnable);
	if(sSmallRegStr == "on" || sSmallRegStr == LowerFirst(XI_ConvertString("Yes")))
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool CheckSaveGameEnabled()
{
    bool TmpBool = true;
    ref mchref = GetMainCharacter();
	
    if(CheckAttribute(&InterfaceStates, "Buttons.Save.enable")) 
	{
		if(InterfaceStates.Buttons.Save.enable != 1) 
		{
			TmpBool = false;
		}
	} 
	else 
	{
		TmpBool = false;
	}

	if(CheckAttribute(loadedLocation, "type") && loadedLocation.type == "Underwater") TmpBool = false; // belamour запрет в подводной локации

	if(dialogRun == true) TmpBool = false; // Hokkins: запрет если запущен диалог

	if(bAbordageStarted) {TmpBool = false;}

	if(LAi_IsBoardingProcess()) {TmpBool = false;}

	if(CharacterIsDead(mchref)) {TmpBool = false;}

	if(LAi_IsFightMode(mchref) && MOD_SKILL_ENEMY_RATE > 1) {TmpBool = false;} 

	if(bDisableMapEnter && !CheckBattleSeaSaveEnabled()) {TmpBool = false;} 

	if(TmpBool)
	{
		int idxLoadLoc = FindLoadedLocation();
	    if (idxLoadLoc != -1 )
	    {
	        if (Locations[idxLoadLoc].id == "Ship_deck" || Locations[idxLoadLoc].id == "Deck_Near_Ship") // сайв на палубе глюкавый
	        {
	            TmpBool = false;
	        }
	    }
	}
    return TmpBool;
}

// Warship 17.06.08 Платный Сэйв/Лоад
int iPayForSaveLoad() // 0 - низя сделать сэйв, т.к. денег нету, 1 - мона делать сэйв, 2 - отключен режит платного S/L
{
	string sPayStr = GetConvertStr("Pay For Save Load", KVL_MODS_FILE);
	int iPayMonPerRank = sti(GetConvertStr("Pay For Save Load Money Qty", KVL_MODS_FILE));
		
	if(iPayMonPerRank < 100)	// Вот смысл этой фичи, если реально почти ничего не платишь?
		iPayMonPerRank = 100;
	
	string sSmallRegStr = GetStrSmallRegister(sPayStr);
	
	if(sSmallRegStr == "on" || sSmallRegStr == LowerFirst(XI_ConvertString("Yes")))
	{
		int iSLMoney = sti(PChar.rank)*iPayMonPerRank;
		PChar.Statistic.PayForSaveLoad.Money = iSLMoney;
		
		if(sti(PChar.money) >= iSLMoney)
			return 1;
		else
			return 0;
	}
	else
	{
		return 2;
	}
}

// Просто чтоб код был в одном месте. _SaveLoad - только "Save" или "Load". Метод вернёт кол-во денег, потраченных на загрузку/сохранение
int CalculatePayForSaveLoadStatistic(string _SaveLoad)
{
	int iMoney = 0;
	ref MChref = GetMainCharacter();
	if(_SaveLoad == "Save")
	{
		if(iPayForSaveLoad() == 1)
		{
			iMoney = sti(MChref.Statistic.PayForSaveLoad.Money);
			MChref.money = sti(MChref.money) - iMoney;	// Нужно без лога
			Statistic_AddValue(MChref, "PayForSaveLoad.PayForSave", iMoney);
		}
	}
	else
	{
		if(iPayForSaveLoad() == 0)
		{
			iMoney = sti(MChref.money);
			Statistic_AddValue(MChref, "PayForSaveLoad.PayForLoad", iMoney);
			MChref.money = 0;
		}
		
		if(iPayForSaveLoad() == 1)
		{
			iMoney = sti(PChar.Statistic.PayForSaveLoad.Money);
			MChref.money = sti(PChar.money) - iMoney;
			Statistic_AddValue(MChref, "PayForSaveLoad.PayForLoad", iMoney);
		}
	}
	
	return iMoney;
}

// Статистика по сэйвам/лоадам
// Просто чтоб код был в одном месте. _SaveLoad - только "Save" или "Load". Метод вернёт общее кол-во загрузок/сохранения
int iCalculateSaveLoadCount(string _SaveLoad)
{
	int iCount;
	ref MChref = GetMainCharacter();
	string sAttrName = _SaveLoad + "Count";	
	iCount = sti(MChref.SystemInfo.(sAttrName));
	iCount++;
	MChref.SystemInfo.(sAttrName) = iCount;
	return iCount;
}

void SaveLastProfileToCurrentProfile() {
	string name = "Player";
	if (CheckAttribute(&PlayerProfile, "name")) {
		name = PlayerProfile.name;
	}

	object opt;
	ReadSavedOptionsByFile(&opt, "SAVE\currentprofile");
	opt.LastProfile = name;
	SaveSavedOptionsByFile(&opt, "SAVE\currentprofile");
}

string GetLastProfileFromCurrentProfile() {
	object opt;
	ReadSavedOptionsByFile(&opt, "SAVE\currentprofile");
	if (!CheckAttribute(&opt, "LastProfile")) {
		return "";
	}

	return opt.LastProfile;
}

void SaveLastSavePathToCurrentProfile(string path) {
	object opt;
	ReadSavedOptionsByFile(&opt, "SAVE\currentprofile");
	opt.LastSavePath = path;
	SaveSavedOptionsByFile(&opt, "SAVE\currentprofile");
}

string GetLastSavePathFromCurrentProfile() {
	object opt;
	ReadSavedOptionsByFile(&opt, "SAVE\currentprofile");
	if (!CheckAttribute(&opt, "LastSavePath")) {
		return "";
	}

	return opt.LastSavePath;
}
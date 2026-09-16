#include "interface\utils\popup_error.c"
#include "interface\utils\menu_volume.c"
#include "interface\mainmenu_location.c"

int iCanMoveChanges = 1;

string currentRewardId = "";

object rewardsInfo;

void InitInterface(string iniName)
{
	TEV.MAINMENU = "";
	Event("DoInfoShower", "sl", "MainMenuLaunch", false);

	string tmp;

	aref arScrShoter;
	if (!GetEntity(&arScrShoter, "scrshoter"))
	{
		CreateScreenShoter();
	}

	MainMenu_CreateBackEnvironment();

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);

	SetFormatedText("VERSION", GetConvertStr("Version", "interface_strings.txt") + GetVerNum());

	SetFormatedText("SUBSCRIBE", XI_ConvertString("Subscribe"));

	SetEventHandler("LoadLastSave", "LoadLastSave", 0);
	SetEventHandler("NewGamePress", "NewGamePress", 0);
	SetEventHandler("LoadPress", "LoadPress", 0);
	SetEventHandler("OptionsPress", "OptionsPress", 0);
	SetEventHandler("CreditsPress", "CreditsPress", 0);
	SetEventHandler("QuitPress", "QuitPress", 0);

	SetEventHandler("ShowChangesWindow", "ShowChangesWindow", 0);
	SetEventHandler("HideChangesWindow", "HideChangesWindow", 0);
	SetEventHandler("ShowPreorderURL", "ShowPreorderURL", 0);
	SetEventHandler("ShowDlcURL", "ShowDlcURL", 0);
	SetEventHandler("ShowDiscordQRCodeWindow", "ShowDiscordQRCodeWindow", 0);
	SetEventHandler("ShowVKQRCodeWindow", "ShowVKQRCodeWindow", 0);
	SetEventHandler("HideQRCodeWindow", "HideQRCodeWindow", 0);

	SetEventHandler("CuratorCheckResult","MM_ProcessCuratorCheckResult",0);
	SetEventHandler("MM_ShowReward", "MM_ShowReward", 0);
	SetEventHandler("PopupIsShown","PopupIsShown",0);

	// evganat - двигаем
	SetEventHandler("MoveFinished", "MoveFinished", 0);
	AddNodeToMoveList("CHANGES_FRAME_WINDOW", 960, 63, 1390, 560);
	AddNodeToMoveList("CHANGES_CAPTION", 960, 67, 1390, 87);
	AddNodeToMoveList("CHANGES_BTN_EXIT", 1360, 67, 1380, 87);
	AddNodeToMoveList("CHANGES_FRAME", 970, 98, 1372, 550);
	AddNodeToMoveList("CHANGES_TEXT", 980, 108, 1362, 550);
	AddNodeToMoveList("CHANGES_SCROLL", 1372, 98, 1380, 550);

	GameInterface.SavePath = "SAVE";

	// кнопка "новая игра" --->
	if (CheckAttribute(pchar, "actions"))
	{
		SetNodeUsing("BTN_NEWGAME", false); // блок кнопки НИ после выхода в меню
		SetNodeUsing("NEW_GAME_INFO", true);
	}
	else
	{
		SetNodeUsing("NEW_GAME_INFO", false);
	}
	// <---
	// кнопка "продолжить игру" --->
	string saveName = GetLastSavePathFromCurrentProfile();
	string saveData = "";

	if (saveName != "" && XI_CheckFolder(saveName))
		SendMessage(&GameInterface, "lse", MSG_INTERFACE_GET_SAVE_DATA, saveName, &saveData);
	else
		saveName = "";

	if (saveName == "" || saveData == "" || !HasSubStr(saveData, "SaveVer=" + VERSION_NUM_PRE))
	{
		SetSelectable("BTN_RESUMEGAME", false);
	}
	// <---

	if (LanguageGetLanguage() != "Russian")
	{
		SetNodeUsing("POINTER", false);
		SetNodeUsing("BTN_DISCORD", false);
		SetNodeUsing("BTN_VK", false);
	}
	else
	{
		SetNodeUsing("ENGLISH_POINTER", false);
		SetNodeUsing("ENGLISH_BTN_DISCORD", false);
	}

	if (true)
	{
		SetNodeUsing("BTN_STEAM_URL", false);
	}
	SetNodeUsing("BTN_DLC_URL", true);

	if (!MusicIsPlaying())
		KZ|MusicRandom("Menu");

	if (Whr_IsNight())
		tmp = "night";
	else
		tmp = "day";

	if (Whr_IsRain())
		tmp = tmp + "_rain";

	ResetSoundScheme();
	SetSoundScheme("mainmenu_" + tmp);

	MenuVolume_FadeIn(); // > музыка и схема звука уже заведены, теперь громкость

	// Награды за франшизу
	MM_InitFranchiseRewards();
}

void MM_InitFranchiseRewards()
{
	bool hasReward = false;
	// Тичингиту
	if (!CheckAttribute(&rewardsInfo, "indian_officer"))
	{
		rewardsInfo.indian_officer = or(HasPlaytestRewardNative(), BIsSubscribedApp(CL_STEAMID));
		SetNewPicture("REWARD_ITEM_1", "interfaces\portraits\128\face_" + 2013 + ".tga");
		hasReward = rewardsInfo.indian_officer == "1";
		SetNodeUsing("REWARD_AVAILABLE_1", hasReward);
		if (!hasReward)
		{
		    Picture_SetColor("REWARD_ITEM_1", argb(220,50,50,50));
		}
	}

	if (!CheckAttribute(&rewardsInfo, "legendGuide"))
	{
		SetNewGroupPicture("REWARD_ITEM_2","ITEMS_33", "itm15");
		SetNodeUsing("REWARD_AVAILABLE_2", false);
		int status = -1;
		if (GetSteamEnabled())
		{
		    status = BeginCuratorCheckAsync(CL_CURATOR, 10);
		}
		if (status == 0) Log_Info("Error while checking your Steam subscription. Please try restarting the game");
	}

	SetNewGroupPicture("REWARD_ITEM_3","ITEMS_EMPTY", "empty");
	Picture_SetColor("REWARD_ITEM_3", argb(220,50,50,50));
	SetNodeUsing("REWARD_AVAILABLE_3", false);
}

void MM_ShowReward()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	ref item;
	bool bOk = false;
	object mockItem;

	switch (nodName)
	{
		// Тичингиту
		case "REWARD_ITEM_1":
			mockItem.isMock = true;
			mockItem.id = "indian_officer";
			mockItem.picTexture = "interfaces\portraits\256\face_" + 2013 + ".tga";
			mockItem.name = FindPersonalName("Tichingitu_name");
			mockItem.describe = GetConvertStr("indian_officer_desc", "franchiseRewards.txt");

			item = &mockItem;
			bOk = true;
		break;
		// Предмет за подписку
		case "REWARD_ITEM_2":
			item = ItemsFromID("legendGuide");
			DumpAttributes(item);
			bOk = true;
	 	break;
		case "REWARD_CLOSE_BUTTON":
		{
			MM_HideReward();
			return;
		}
		break;
	}

	if (!bOk) MM_ShowEmptyReward();
	else MM_ShowRewardItem(item);
}

void MM_ShowEmptyReward()
{
	ShowError(GetConvertStr("noRewardYetMessage", "franchiseRewards.txt"));
	XI_WindowDisable("REWARD_WINDOW", true);
	XI_WindowShow("REWARD_WINDOW", false);
}

void MM_ShowRewardItem(ref item)
{
	if (!CheckAttribute(item, "id"))
	{
		Trace("MM_ShowRewardItem - item has no Id");
	    return;
	}
	SetFormatedText("REWARD_CONDITIONS", GetConvertStr("condition_" + item.id, "franchiseRewards.txt"));
	if (MM_ToggleReward(currentRewardId != item.id)) return;

	currentRewardId = item.id;
	if (CheckAttribute(item, "isMock"))
	{
		SetNewPicture("REWARD_PICTURE", item.picTexture);
		SetFormatedText("REWARD_NAME", item.name);
		SetFormatedText("REWARD_DESCRIPTION", item.describe);
	}
	else
	{
		SetNewGroupPicture("REWARD_PICTURE", item.picTexture, "itm" + item.picIndex);
		SetFormatedText("REWARD_NAME", GetItemName(item.id));
		SetFormatedText("REWARD_DESCRIPTION", GetItemDescribe(sti(item.index), GetMainCharacter()));
	}
	SetVAligmentFormatedText("REWARD_NAME");

//	FillUpDescriptors(item, !XI_IsWindowEnable("REWARD_WINDOW"));
//	FillUpStats(item, &NullCharacter);

	string steamButtonText = GetConvertStr("steamButtonGet", "franchiseRewards.txt");
	bool alreadyGot = false;
	string sAttr = item.id;

	if (CheckAttribute(&rewardsInfo, sAttr) && rewardsInfo.(sAttr) == "1")
	{
		alreadyGot = true;
	}

	SetSelectable("GET_REWARD_BUTTON", !alreadyGot);
	if (alreadyGot) steamButtonText = GetConvertStr("steamButtonAlreadyGot", "franchiseRewards.txt");
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"GET_REWARD_BUTTON",0, "#"+steamButtonText);
}

bool MM_ToggleReward(bool forceShow)
{
	bool isShowed = XI_IsWindowEnable("REWARD_WINDOW");
	if (forceShow) isShowed = false;

	if (!isShowed) MM_InitFranchiseRewards();
	XI_WindowDisable("REWARD_WINDOW", isShowed);
	XI_WindowShow("REWARD_WINDOW", !isShowed);
	SetCurrentNode("REWARD_CLOSE_BUTTON");
	return isShowed;
}

void MM_HideReward()
{
	XI_WindowDisable("REWARD_WINDOW", true);
	XI_WindowShow("REWARD_WINDOW", false);
}

void PopupIsShown()
{
	XI_WindowDisable("CHANGES_WINDOW", true);
	XI_WindowDisable("QR_WINDOW", true);
}

void PopupIsClosed()
{
	XI_WindowDisable("CHANGES_WINDOW", false);
	XI_WindowDisable("QR_WINDOW", false);
}

void NewGamePress()
{
	IDoExit(RC_INTERFACE_DO_NEW_GAME, true);
}

void LoadPress()
{
	IDoExit(RC_INTERFACE_DO_LOAD_GAME, false);
}

void OptionsPress()
{
	IDoExit(RC_INTERFACE_DO_OPTIONS, false);
}

void CreditsPress()
{
	IDoExit(RC_INTERFACE_DO_CREDITS, false);
}

void QuitPress()
{
	DelEventHandler("frame", "QuitPress");
	EngineLayersOffOn(false);
	IDoExit(-1, false);
	ExitProgram();
}

void IDoExit(int exitCode, bool bClear)
{
	InterfaceStates.BackEnvironmentIsCreated = true;

	DelEventHandler("LoadLastSave", "LoadLastSave");
	DelEventHandler("NewGamePress", "NewGamePress");
	DelEventHandler("LoadPress", "LoadPress");
	DelEventHandler("OptionsPress", "OptionsPress");
	DelEventHandler("CreditsPress", "CreditsPress");
	DelEventHandler("QuitPress", "QuitPress");

	DelEventHandler("ShowChangesWindow", "ShowChangesWindow");
	DelEventHandler("HideChangesWindow", "HideChangesWindow");
	DelEventHandler("ShowPreorderURL", "ShowPreorderURL");
	DelEventHandler("ShowDlcURL", "ShowDlcURL");
	DelEventHandler("ShowDiscordQRCodeWindow", "ShowDiscordQRCodeWindow");
	DelEventHandler("ShowVKQRCodeWindow", "ShowVKQRCodeWindow");
	DelEventHandler("HideQRCodeWindow", "HideQRCodeWindow");
	MenuVolume_Stop();

	DelEventHandler("CuratorCheckResult","MM_ProcessCuratorCheckResult");
	DelEventHandler("MM_ShowReward", "MM_ShowReward");
	DelEventHandler("PopupIsShown","PopupIsShown");

	// evganat - двигаем
	DelEventHandler("MoveFinished", "MoveFinished");
	ClearMoveList();

	interfaceResultCommand = exitCode;
	EndCancelInterface(bClear);
}

void ShowChangesWindow()
{
	if (iCanMoveChanges == -1)
	{
		HideChangesWindow();
		return;
	}
	XI_WindowShow("CHANGES_WINDOW", true);
	XI_WindowDisable("CHANGES_WINDOW", false);
	HideQRCodeWindow();

	// evganat - двигаем
	if (iCanMoveChanges == 1)
	{
		MoveAllNodesToDirSoftly("left", 10, 600, "open");
		PlaySound("Interface\book_slide_01.mp3");
		iCanMoveChanges = 0;
	}

	SetFormatedText("CHANGES_CAPTION", XI_ConvertString("Changelog"));
	SetFormatedText("CHANGES_TEXT", GetConvertStr("ChangeLog", "Changelog.txt"));

	SetAlignmentFormatedText("CHANGES_TEXT", SCRIPT_ALIGN_LEFT);
}

void HideChangesWindow()
{
	// evganat - двигаем
	if (iCanMoveChanges == -1)
	{
		MoveAllNodesToDirSoftly("right", 10, 600, "close");
		PlaySound("Interface\book_slide_02.mp3");
		iCanMoveChanges = 0;
	}
}

// evganat - двигаем
void MoveFinished()
{
	string tag = GetEventData();
	switch (tag)
	{
		case "open":
			iCanMoveChanges = -1;
		break;

		case "close":
			iCanMoveChanges = 1;
			XI_WindowShow("CHANGES_WINDOW", false);
			XI_WindowDisable("CHANGES_WINDOW", true);
		break;
	}
}

void ShowPreorderURL()
{
    GameOverlayToWebPage("https://store.steampowered.com/app/3549020/Caribbean_Legend_Age_of_Pirates/");
    //ShellExecuteOpenURL("https://store.steampowered.com/app/3549020/Caribbean_Legend_Age_of_Pirates/");
    //ShellExecuteOpenURL("https://steamcommunity.com/app/2230980/workshop/");
}

void ShowDlcURL()
{
    GameOverlayToWebPage("https://store.steampowered.com/dlc/3549020");
}

void ShowDiscordQRCodeWindow()
{
	ShellExecuteOpenURL("https://discord.com/invite/Kz7XBQxBQa");
}

void ShowVKQRCodeWindow()
{
	ShellExecuteOpenURL("https://vk.com/reconteam");
}

void HideQRCodeWindow()
{
	XI_WindowShow("QR_WINDOW", false);
	XI_WindowDisable("QR_WINDOW", true);
}

void MainMenu_CreateBackEnvironment()
{
	LayerFreeze(EXECUTE, false);
	LayerFreeze(REALIZE, false);

	if (CheckAttribute(&InterfaceStates, "BackEnvironmentIsCreated") && InterfaceStates.BackEnvironmentIsCreated == "1") return;

	// KZ > сцены нет, значит прошлую уже снесли вместе с сущностями - выбор локации пора обновить
	MainMenuLoc_Forget();

	Render.BackColor = 0;
	Render.SeaEffect = false;
	Sea.UnderWater = false;
	bMainCharacterInFire = false;
	bMainMenu = true;

	int iMenuLoc = MainMenuLoc_Choose();

	ICreateWeather(iMenuLoc);

	CreateEntity(&InterfaceBackScene, "InterfaceBackScene");
	LayerAddObject(EXECUTE, &InterfaceBackScene, -1);
	LayerAddObject(REALIZE, &InterfaceBackScene, 1000);

	// > фон из обычной локации: свет, фонари, техники и погода приезжают вместе с ней
	if (iMenuLoc >= 0)
	{
		if (MainMenuLoc_Load(iMenuLoc))
		{
			bMainMenu = false;
			return;
		}
		Trace("MainMenuLoc: локация " + MainMenuLoc_Id(iMenuLoc) + " не загрузилась, показываю штатную сцену меню");
		MainMenuLoc_Forget();
		// > локация могла оказаться сухопутной и море не завести - штатной сцене оно нужно
		MainMenu_CreateSea("MainMenu");
	}

	SendMessage(&InterfaceBackScene, "ls", 0, "MainMenu\MainMenu"); // set model
	SendMessage(&InterfaceBackScene, "ls", 1, "camera"); // set camera

	if (Whr_IsNight())
	{
		InterfaceBackScene.light.turnon = true;
		InterfaceBackScene.light.model = "mainmenu\Fonar_night";
		InterfaceBackScene.light.lightcolormin = argb(0, 200, 200, 120);//argb(255,114,114,80);
		InterfaceBackScene.light.lightcolormax = argb(48, 255, 255, 180);
		InterfaceBackScene.light.colorperiod = 0.4;
		InterfaceBackScene.light.addcolorperiod = 1.0;
		InterfaceBackScene.light.rangemin = 10.0;
		InterfaceBackScene.light.rangemax = 14.0;
		InterfaceBackScene.light.rangeperiod = 1.5;
		InterfaceBackScene.light.locator = "Light";
		InterfaceBackScene.light.lightlocator = "fonar";
		InterfaceBackScene.light.flarelocator = "fire";
		InterfaceBackScene.light.flaresize = 0.5;
		InterfaceBackScene.light.minflarecolor = 120.0;
		InterfaceBackScene.light.maxflarecolor = 200.0;
	}
	else
	{
		MainMenu_CreateAnimals();

		InterfaceBackScene.light.turnon = false;
		InterfaceBackScene.light.model = "mainmenu\Fonar_day";
		InterfaceBackScene.light.locator = "Light";
		InterfaceBackScene.light.lightlocator = "fonar";
	}
	SendMessage(&InterfaceBackScene, "ls", 8, "light");

	if (Whr_IsNight())
	{
		// create particles
		InitParticles();
		CreateParticleSystem("candle", stf(InterfaceBackScene.lightpos.x), stf(InterfaceBackScene.lightpos.y), stf(InterfaceBackScene.lightpos.z), 0.0, 0.0, 0.0, 0);
	}
	bMainMenu = false;
}

void MainMenu_DeleteBackEnvironment()
{
	LayerDelObject(EXECUTE, &InterfaceBackScene);
	LayerDelObject(REALIZE, &InterfaceBackScene);

	MainMenu_DeleteAnimals();
	DeleteShipEnvironment();
	DeleteWeather();
	DeleteSea();
	DeleteClass(&InterfaceBackScene);
	DeleteCoastFoamEnvironment();

	iNextWeatherNum = -1;
	iCurWeatherHour = -1;
}

void MainMenu_CreateAnimals()
{
	InterfaceBackScene.seagull.locator = "seagull";
	InterfaceBackScene.seagull.model = "mainmenu\seagull";
	InterfaceBackScene.seagull.animation = "seagull";
	InterfaceBackScene.seagull.aniaction = "idle";
	SendMessage(&InterfaceBackScene, "ls", 9, "seagull");
}

void MainMenu_DeleteAnimals()
{
	if (IsEntity(&Animals))
	{
		DeleteClass(&Animals);
	}
}
// Hokkins: <--

// > море и пена сцены меню. У локации они берутся из её environment, у штатной сцены - как раньше
bool bMainMenuSeaCreated = false;
void MainMenu_CreateSea(string sFoamID)
{
	if (!bMainMenuSeaCreated)
	{
		CreateSea(EXECUTE, REALIZE);
		Sea.MaxSeaHeight = 1.0;
		Sea.isDone = "";
		bMainMenuSeaCreated = true;
	}

	// > пену переставляем всегда: на откате в кадре должен быть прибой штатной сцены, а не чужой
	if (IsEntity(&CoastFoam)) DeleteCoastFoamEnvironment();
	if (sFoamID != "") CreateCoastFoamEnvironment(sFoamID, EXECUTE, REALIZE);
}

void ICreateWeather(int iMenuLoc)
{
	int n = 0;

	if (CheckAttribute(&InterfaceStates, "mainmenuweather"))
	{
		n = sti(InterfaceStates.mainmenuweather);
	}
	else
	{
		n = rand(iTotalNumWeathers - 1);

		int oldN = n;

		while(true)
		{
			if (!CheckAttribute(&Weathers[n], "skip") || Weathers[n].skip != "1")
			{
				break;
			}
			//candle
			n++;
			if (n == iTotalNumWeathers) n = 0;
			if (n == oldN) break;
		}
	}

	// > у локации-фона запечённый свет бывает только под одну погоду, и тогда при любой другой нужный *.col не найдётся, а движок проглотит это молча и отрисует сцену плоско
	if (iMenuLoc >= 0)
	{
		string sLocWeather = MainMenuLoc_Weather(iMenuLoc);
		int iLocIdx = MainMenuLoc_LocIndex(iMenuLoc);
		if (sLocWeather == "" && iLocIdx >= 0)
		{
			// > у локации с залоченной квестовой погодой свет запечён только под неё
			if (CheckAttribute(&Locations[iLocIdx], "QuestlockWeather")) sLocWeather = Locations[iLocIdx].QuestlockWeather;
		}

		if (sLocWeather != "")
		{
			int iLocWeather = FindWeather(sLocWeather);
			if (iLocWeather >= 0) n = iLocWeather;
			else Trace("MainMenuLoc: погода " + sLocWeather + " локации " + MainMenuLoc_Id(iMenuLoc) + " не найдена");
		}
	}

	if (n < 0 || n >= iTotalNumWeathers) n = 0;
	SetNextWeather(Weathers[n].id);
	iBlendWeatherNum = -1; // залоченная погода
	Whr_LoadNextWeather(0);
	iBlendWeatherNum = -1; // залоченная погода
	InterfaceBackScene.current_weather = n;
	InterfaceStates.mainmenuweather = n;

	bMainMenuSeaCreated = false;
	if (MainMenuLoc_NeedSea(iMenuLoc))
	{
		CreateSea(EXECUTE, REALIZE);
		bMainMenuSeaCreated = true;
	}
	CreateWeather(EXECUTE, REALIZE);
	CreateShipEnvironment();
	Sea.MaxSeaHeight = 1.0;
	Sea.isDone = "";

	if (bMainMenuSeaCreated)
	{
		string sFoamID = MainMenuLoc_FoamID(iMenuLoc);
		if (sFoamID != "") CreateCoastFoamEnvironment(sFoamID, EXECUTE, REALIZE);
	}

	iBlendWeatherNum = -1; // залоченная погода
}

void LoadLastSave()
{
	SetEventHandler("evntLoad", "LoadGame", 0);
	PostEvent("evntLoad", 0, "s", GetLastSavePathFromCurrentProfile());
	IDoExit(-1, false);
}

void MM_ProcessCuratorCheckResult()
{
	string sResult = GetEventData();
	if (sResult == "success")
	{
		rewardsInfo.legendGuide = true;
		if (currentRewardId != "" && currentRewardId == "legendGuide")
		{
			SetSelectable("GET_REWARD_BUTTON", false);
			SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"GET_REWARD_BUTTON",0, "#"+GetConvertStr("steamButtonAlreadyGot", "franchiseRewards.txt"));
		}
		SetNodeUsing("REWARD_AVAILABLE_2", true);
		return;
	}

	SetNodeUsing("REWARD_AVAILABLE_2", false);
	if (sResult == "notsubscribedfailure")
	{
		Trace("ProcessCuratorCheckResult: NotSubscribedFailure! ;-(");
	}
	else
	{
		Trace("ProcessCuratorCheckResult: Unknown sResult=" + sResult);
	}
}
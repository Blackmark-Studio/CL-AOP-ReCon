int iCanMoveChanges = 1;
float fMus, fSnd;

void InitInterface(string iniName)
{
	TEV.MAINMENU = "";
	Event("DoInfoShower", "sl", "MainMenuLaunch", false);

	string tmp;
	float fS, fM, fD;
	GetMasterVolume(&fS, &fM, &fD);

	if (CheckAttribute(&TEV, "MENUVOLUME.MUS"))
		fMus = stf(TEV.MENUVOLUME.MUS);
	else
		fMus = fM;

	fSnd = fS;

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
	SetEventHandler("VolumeFader", "VolumeFadeIn", 0);

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
	string saveData;
	if (saveName != "") SendMessage(&GameInterface, "lse", MSG_INTERFACE_GET_SAVE_DATA, saveName, &saveData);
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
		KZ|Random("Menu");

	if (Whr_IsNight())
		tmp = "night";
	else
		tmp = "day";

	if (Whr_IsRain())
		tmp = tmp + "_rain";

	ResetSoundScheme();
	SetSoundScheme("mainmenu_" + tmp);

	if (fMus < 0.333) fMus = 0.333;
	if (CheckAttribute(&TEV, "MENUVOLUME.RTM"))
	{
		KZ|Volume(fMus, fSnd);

		if (sti(TEV.MENUVOLUME.RTM) == 1)
			PostEvent("VolumeFader", 1);
		else
			DelEventHandler("VolumeFader", "VolumeFadeIn");
	}
}

void VolumeFadeIn()
{
	DeleteAttribute(&TEV, "MENUVOLUME.RTM");
	fMus += 0.01;
	fSnd += 0.01;

	if (fMus >= 1.0)
	{
		KZ|Volume(1, 1);
		DelEventHandler("VolumeFader", "VolumeFadeIn");
		return;
	}

	KZ|Volume(fMus, fSnd);
	PostEvent("VolumeFader", 55);
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
	DelEventHandler("VolumeFader", "VolumeFadeIn");

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

int iChar;
void MainMenu_CreateBackEnvironment()
{
	LayerFreeze(EXECUTE, false);
	LayerFreeze(REALIZE, false);

	if (CheckAttribute(&InterfaceStates, "BackEnvironmentIsCreated") && InterfaceStates.BackEnvironmentIsCreated == "1") return;

	Render.BackColor = 0;
	Render.SeaEffect = false;
	Sea.UnderWater = false;
	bMainCharacterInFire = false;
	bMainMenu = true;

	ICreateWeather();

	CreateEntity(&InterfaceBackScene, "InterfaceBackScene");
	LayerAddObject(EXECUTE, &InterfaceBackScene, -1);
	LayerAddObject(REALIZE, &InterfaceBackScene, 1000);

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
	DeleteClass(GetCharacter(iChar));
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

void ICreateWeather()
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

	if (n < 0 || n >= iTotalNumWeathers) n = 0;
	SetNextWeather(Weathers[n].id);
	iBlendWeatherNum = -1; // залоченная погода
	Whr_LoadNextWeather(0);
	iBlendWeatherNum = -1; // залоченная погода
	InterfaceBackScene.current_weather = n;
	InterfaceStates.mainmenuweather = n;

	CreateSea(EXECUTE, REALIZE);
	CreateWeather(EXECUTE, REALIZE);
	CreateShipEnvironment();
	Sea.MaxSeaHeight = 1.0;
	Sea.isDone = "";

	CreateCoastFoamEnvironment("MainMenu", EXECUTE, REALIZE);

	iBlendWeatherNum = -1; // залоченная погода
}

void LoadLastSave()
{
	SetEventHandler("evntLoad", "LoadGame", 0);
	PostEvent("evntLoad", 0, "s", GetLastSavePathFromCurrentProfile());
	IDoExit(-1, false);
}

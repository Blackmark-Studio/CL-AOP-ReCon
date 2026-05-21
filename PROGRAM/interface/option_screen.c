int g_nCurControlsMode = -1;
int g_ControlsLngFile = -1;

bool g_bToolTipStarted = false;
bool bSkipChangeHUD = false;

float fHUDRatio    = 1.0;
int iHUDBase    = screenscaling;
int newBase    = screenscaling;

#define BI_LOW_RATIO    0.25
#define BI_HI_RATIO    4.0
#define BI_DIF_RATIO    3.75

#define MB_VIDEO_SETTINGS        "MB_VIDEO_SETTINGS"
#define MB_GAME_SETTINGS        "MB_GAME_SETTINGS"
#define MB_SOUND_SETTINGS        "MB_SOUND_SETTINGS"
#define MB_CONTROLS_SETTINGS    "MB_CONTROLS_SETTINGS"

int curFoliageDrawDistance, curGrassDrawDistance;
string sFoliageDrawDistance, settingsState = MB_VIDEO_SETTINGS;

int CalcHUDBase(float fSlider, float MyScreen)
{
	float fRes = BI_DIF_RATIO * fSlider;
	float curBase = MyScreen / (BI_LOW_RATIO + fRes);

	return makeint(curBase + 0.5);
}

float CalcHUDSlider(float fRatio)
{
	float fRes = fRatio - BI_LOW_RATIO;
	fRes /= BI_DIF_RATIO;

	return fRes;
}

void InitInterface(string iniName)
{
	fHUDRatio = GetScreenScale();
	iHUDBase = makeint(screenscaling);
	newBase = iHUDBase;

	g_nCurControlsMode = -1;
	g_ControlsLngFile = LanguageOpenFile("ControlsNames.txt");

	if (CheckAttribute(&InterfaceStates, "showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
	{
		LoadGameOptions();
	}
	else
	{
		DeleteAttribute(&PlayerProfile, "name");
		LoadGameOptions();
	}

	IReadVariableBeforeInit();
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);
	IReadVariableAfterInit();

	ProcessVideoSettingsBtn();
	SetControlsTabMode(1);

	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("InterfaceBreak", "ProcessCancelExit", 0);  // boal
	SetEventHandler("ProcessVideoSettingsBtn", "ProcessVideoSettingsBtn", 0);
	SetEventHandler("ProcessGameSettingsBtn", "ProcessGameSettingsBtn", 0);
	SetEventHandler("ProcessSoundSettingsBtn", "ProcessSoundSettingsBtn", 0);
	SetEventHandler("ProcessControlsSettingsBtn", "ProcessControlsSettingsBtn", 0);
	SetEventHandler("eTabControlPress", "procTabChange", 0);
	SetEventHandler("eventBtnAction", "procBtnAction", 0);
	SetEventHandler("eventKeyChange", "procKeyChange", 0);

	SetEventHandler("CheckButtonChange", "procCheckBoxChange", 0);
	SetEventHandler("eSlideChange", "procSlideChange", 0);

	SetEventHandler("evntKeyChoose", "procKeyChoose", 0);
	SetEventHandler("ShowInfo", "ShowInfo", 0);
	SetEventHandler("MouseRClickUP", "HideInfo", 0);

	SetEventHandler("evFaderFrame", "FaderFrame", 0);

	aref ar; makearef(ar, objControlsState.key_codes);
	SendMessage(&GameInterface, "lsla", MSG_INTERFACE_MSG_TO_NODE, "KEY_CHOOSER", 0, ar);

	float ftmp1 = -1.0;
	float ftmp2 = -1.0;
	float ftmp3 = -1.0;
	GetMasterVolume(&ftmp1, &ftmp2, &ftmp3);
	if (ftmp1 == -1.0 && ftmp2 == -1.0 && ftmp3 == -1.0)
	{
		SetSelectable("MUSIC_SLIDE", false);
		SetSelectable("SOUND_SLIDE", false);
		SetSelectable("DIALOG_SLIDE", false);
	}

	// Warship 07.07.09 Эффект свечения
	if (!CheckAttribute(&InterfaceStates, "GlowEffect"))
	{
		InterfaceStates.GlowEffect = 50;
	}

	if (!CheckAttribute(&InterfaceStates, "FoliageDrawDistance"))
	{
		InterfaceStates.FoliageDrawDistance = 1000;
	}

	float fFoliageDrawDistance = sti(InterfaceStates.FoliageDrawDistance) / 5000.0;
	GameInterface.nodes.FOLIAGE_DRAW_DISTANCE_SLIDE.value = fFoliageDrawDistance;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "FOLIAGE_DRAW_DISTANCE_SLIDE", 0, fFoliageDrawDistance);
	sFoliageDrawDistance = sti(InterfaceStates.FoliageDrawDistance);
	curFoliageDrawDistance = sti(InterfaceStates.FoliageDrawDistance);

	float glowEffect = sti(InterfaceStates.GlowEffect) / 250.0; // если делить на 250, то хер, т.к. целое, а если на 250.0 - все гуд

	GameInterface.nodes.GLOW_SLIDE.value = glowEffect;
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "GLOW_SLIDE", 0, glowEffect);

	fHUDRatio = GetScreenScale();
	float sl = CalcHUDSlider(fHUDRatio);
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "HUD_SLIDE", 2, makeint(sl * 100.0));
	GameInterface.nodes.hud_slide.value = sl;
	iHUDBase = CalcHUDBase(sl, stf(Render.screen_y));
	SetFormatedText("HUD_DESCRIP_TEXT", XI_ConvertString("HudDescripText") + ": " + Render.screen_y + "  / " + newBase + " : " + FloatToString(fHUDRatio, 2));
	
	if (!SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "CONTINUOUS_MUSIC_CHECKBOX", 3, 1))
		CheckContinuousMusicButtonEnable(0);
	
	HideContinuousMusicSettings(0);
}

void HideContinuousMusicSettings(bool bRes)
{
	SetNodeUsing("CONTINUOUS_MUSIC_BUTTON_PLUS", bRes);
	SetNodeUsing("CONTINUOUS_MUSIC_BUTTON_MINUS", false);
	SwitchContinuousButtonVisual(false);
	XI_WindowDisable("CONTINUOUS_MUSIC_BUTTON_PLUS_WINDOW", !bRes);
	XI_WindowShow("CONTINUOUS_MUSIC_BUTTON_PLUS_WINDOW", bRes);
}

void ProcessCancelExit()
{
	LoadGameOptions();
	ProcessExit();
}

void ProcessVideoSettingsBtn()
{
	DisableString("FontTypeText");
	HideContinuousMusicSettings(0);
	SetFormatedText("TITLE", XI_ConvertString("MB_GRAPHICS"));
	XI_WindowDisable("VIDEO_SETTINGS_WINDOW", false);
	XI_WindowShow("VIDEO_SETTINGS_WINDOW", true);

	XI_WindowShow("GAME_SETTINGS_WINDOW", false);
	XI_WindowShow("CONTROLS_SETTINGS_WINDOW", false);
	XI_WindowShow("SOUND_SETTINGS_WINDOW", false);
	SetCurrentNode("MB_VIDEO_SETTINGS");
	settingsState = MB_VIDEO_SETTINGS;
}

void ProcessGameSettingsBtn()
{
	FontDes();
	HideContinuousMusicSettings(0);
	SetFormatedText("TITLE", XI_ConvertString("MB_GAME"));
	XI_WindowShow("VIDEO_SETTINGS_WINDOW", false);
	XI_WindowShow("SOUND_SETTINGS_WINDOW", false);
	XI_WindowShow("CONTROLS_SETTINGS_WINDOW", false);

	XI_WindowDisable("GAME_SETTINGS_WINDOW", false);
	XI_WindowShow("GAME_SETTINGS_WINDOW", true);
	SetCurrentNode("MB_GAME_SETTINGS");
	settingsState = MB_GAME_SETTINGS;
}

void ProcessSoundSettingsBtn()
{
	DisableString("FontTypeText");
	HideContinuousMusicSettings(1);
	SetFormatedText("TITLE", XI_ConvertString("MB_SOUNDS"));
	XI_WindowShow("VIDEO_SETTINGS_WINDOW", false);
	XI_WindowShow("GAME_SETTINGS_WINDOW", false);
	XI_WindowShow("CONTROLS_SETTINGS_WINDOW", false);

	XI_WindowDisable("SOUND_SETTINGS_WINDOW", false);
	XI_WindowShow("SOUND_SETTINGS_WINDOW", true);
	SetCurrentNode("MB_SOUND_SETTINGS");
	settingsState = MB_SOUND_SETTINGS;
}

void ProcessControlsSettingsBtn()
{
	DisableString("FontTypeText");
	HideContinuousMusicSettings(0);
	SetFormatedText("TITLE", XI_ConvertString("MB_CONTROLS"));
	XI_WindowShow("VIDEO_SETTINGS_WINDOW", false);
	XI_WindowShow("GAME_SETTINGS_WINDOW", false);
	XI_WindowShow("SOUND_SETTINGS_WINDOW", false);

	XI_WindowDisable("CONTROLS_SETTINGS_WINDOW", false);
	XI_WindowShow("CONTROLS_SETTINGS_WINDOW", true);
	SetCurrentNode("MB_CONTROLS_SETTINGS");
	settingsState = MB_CONTROLS_SETTINGS;
}

void ProcessOkExit()
{
	screenscaling = newBase;

	// Warship 07.07.09 Эффект свечения
	SetGlowParams(1.0, sti(InterfaceStates.GlowEffect), 2);

	if (CheckAttribute(&InterfaceStates, "FoliageDrawDistance") && sti(InterfaceStates.FoliageDrawDistance) != curFoliageDrawDistance)
    {
		if (bSeaActive && !bAbordageStarted)
			Sea_IslandDrawVegetation(AISea.Island);
	}

	// evganat - применяем настройки маркеров персонажей
	int iLocation = FindLocation(pchar.location);
	if(iLocation != -1)
		SetLocationCharacterMarksOptions(&Locations[iLocation]);

	SaveGameOptions();
	//	ProcessExit();
	Event("eventChangeOption");

	// change sea settings
	//TODO переделать детализацию моря (убрать ползунок добавить чекбоксы, хорошее или плохое) ползунок плохо работает с рябью на воде
	//SetSeaGridStep(stf(InterfaceStates.SeaDetails));
}

void ProcessExit()
{
	if (CheckAttribute(&InterfaceStates, "showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
	{
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
		return;
	}

	IDoExit(RC_INTERFACE_OPTIONSCREEN_EXIT);
	if (!CheckAttribute(&InterfaceStates, "InstantExit") || sti(InterfaceStates.InstantExit) == false)
	{
		ReturnToMainMenu();
	}
}

void IDoExit(int exitCode)
{
	DelEventHandler("evntKeyChoose", "procKeyChoose");
	DelEventHandler("eSlideChange", "procSlideChange");
	DelEventHandler("CheckButtonChange", "procCheckBoxChange");

	DelEventHandler("eventKeyChange", "procKeyChange");
	DelEventHandler("eventBtnAction", "procBtnAction");
	DelEventHandler("eTabControlPress", "procTabChange");
	DelEventHandler("exitCancel", "ProcessCancelExit");
	DelEventHandler("ShowInfo", "ShowInfo");
	DelEventHandler("MouseRClickUP", "HideInfo");
	DelEventHandler("evFaderFrame", "FaderFrame");
	DelEventHandler("InterfaceBreak", "ProcessCancelExit");
	DelEventHandler("ProcessVideoSettingsBtn", "ProcessVideoSettingsBtn");
	DelEventHandler("ProcessGameSettingsBtn", "ProcessGameSettingsBtn");
	DelEventHandler("ProcessSoundSettingsBtn", "ProcessSoundSettingsBtn");
	DelEventHandler("ProcessControlsSettingsBtn", "ProcessControlsSettingsBtn");

	LanguageCloseFile(g_ControlsLngFile);

	interfaceResultCommand = exitCode;
	if (CheckAttribute(&InterfaceStates, "InstantExit") && sti(InterfaceStates.InstantExit) == true)
	{
		EndCancelInterface(true);
	}
	else
	{
		EndCancelInterface(false);
	}
	ControlsMakeInvert();
}

void IReadVariableBeforeInit()
{
	GetSoundOptionsData();
	GetMouseOptionsData();
	GetVideoOptionsData();
}

void IReadVariableAfterInit()
{
	int i, n;
	string s = "";
	GetHerbOptionsData();
	GetControlsStatesData();

	if(CheckAttribute(&InterfaceStates,"MoreInfo")) {
		iMoreInfo = sti(InterfaceStates.MoreInfo);
	}
	SetFormatedText("MOREINFO_TEXT", MoreInfoDes());

	if(CheckAttribute(&InterfaceStates,"FontType")) {
		iFontType = sti(InterfaceStates.FontType);
	}
	FontDes();

	if (CheckAttribute(&InterfaceStates, "ShowControlTips"))
	{
		iShowTips = sti(InterfaceStates.ShowControlTips);
	}
	SetFormatedText("CONTROLTIPS_TEXT", ControlTipsDes());

	if (CheckAttribute(&InterfaceStates, "TargetMode"))
	{
		iGlobalTarget = sti(InterfaceStates.TargetMode);
	}
	SetFormatedText("TARGET_MODE_TEXT", XI_ConvertString("TargetMode_" + iGlobalTarget));

	i = 12;
	if (CheckAttribute(&InterfaceStates, "QuickSaveSlots"))
	{
		i = sti(InterfaceStates.QuickSaveSlots);
	}
	SetFormatedText("QUICKSAVESLOTS_TEXT", XI_ConvertString("QuickSaveSlots_" + i));

	i = 1;
	if (CheckAttribute(&InterfaceStates, "EnabledQuestsMarks"))
	{
		i = sti(InterfaceStates.EnabledQuestsMarks);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "QUESTMARK_CHECKBOX", 2, 1, i);

	i = 1;
	if (CheckAttribute(&InterfaceStates, "EnabledQuestsPointers"))
	{
		i = sti(InterfaceStates.EnabledQuestsPointers);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "QUESTPOINTER_CHECKBOX", 2, 1, i);

	i = 0;
	if (CheckAttribute(&InterfaceStates, "SimpleSea"))
	{
		i = sti(InterfaceStates.SimpleSea);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SIMPLESEA_CHECKBOX", 2, 1, i);

	i = 0;
	if (CheckAttribute(&InterfaceStates, "ShowBattleMode"))
	{
		i = sti(InterfaceStates.ShowBattleMode);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "BATTLE_MODE_CHECKBOX", 2, 1, i);

	i = 0;
	if (CheckAttribute(&InterfaceStates, "SkipStartVideo"))
	{
		i = sti(InterfaceStates.SkipStartVideo);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SKIPVIDEO_CHECKBOX", 2, 1, i);

	i = 1;
	if (CheckAttribute(&InterfaceStates, "EnabledShipMarks"))
	{
		i = sti(InterfaceStates.EnabledShipMarks);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SHIPMARK_CHECKBOX", 2, 1, i);

	i = 1;
	if (CheckAttribute(&InterfaceStates, "EnabledAutoSaveMode"))
	{
		i = sti(InterfaceStates.EnabledAutoSaveMode);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "AUTOSAVE_CHECKBOX", 2, 1, i);

	i = 1;
	if (CheckAttribute(&InterfaceStates, "ShowCharString"))
	{
		i = sti(InterfaceStates.ShowCharString);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CHAR_STRING_CHECKBOX", 2, 1, i);

	i = 1;
	if (CheckAttribute(&InterfaceStates, "ShowTutorial"))
	{
		i = sti(InterfaceStates.ShowTutorial);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TUTORIAL_CHECKBOX", 2, 1, i);

	i = 1;
	if (CheckAttribute(&InterfaceStates, "SkyRotation"))
	{
		i = sti(InterfaceStates.SkyRotation);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SKYROTATION_CHECKBOX", 2, 1, i);

	i = 0;
	if (CheckAttribute(&InterfaceStates, "TimeSpeedAccel"))
	{
		i = sti(InterfaceStates.TimeSpeedAccel);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TIMESPEEDACCEL_CHECKBOX", 2, 1, i);

	i = 1;
	if (CheckAttribute(&InterfaceStates, "NoAdultSounds"))
	{
		i = sti(InterfaceStates.NoAdultSounds);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "ADULT_SOUNDS_CHECKBOX", 2, 1, i);

	i = 1;
	if (CheckAttribute(&InterfaceStates, "CrewOnDeck"))
	{
		i = sti(InterfaceStates.CrewOnDeck);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CREWONDECK_CHECKBOX", 2, 1, i);

	// KZ > Continuous music
	i = 1;

	if (CheckAttribute(&InterfaceStates, "ContinuousMusic"))
		i = sti(InterfaceStates.ContinuousMusic);

	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CONTINUOUS_MUSIC_CHECKBOX", 2, 1, i);

	for (n = 1; n <= 7; n++)
	{
		i = 1;

		switch (n)
		{
			case 1: s = "jungle"; break;
			case 2: s = "house"; break;
			case 3: s = "brothel"; break;
			case 4: s = "ship"; break;
			case 5: s = "boarding"; break;
			case 6: s = "attack"; break;
			case 7: s = "lsc"; i = 0; break;
		}

		if (CheckAttribute(&InterfaceStates, "ContinuousMusic." + s))
			i = sti(InterfaceStates.ContinuousMusic.(s));

		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CONTINUOUS_MUSIC_" + s + "_CHECKBOX", 2, 1, i);
	}
	// KZ < Continuous music
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255, 196, 196, 196);
	int nColor2 = nColor1;
	int nColor3 = nColor1;
	int nColor4 = nColor1;

	string sPic1 = "TabSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;

	switch (nMode)
	{
		case 1: // море от первого лица
			sPic1 = "TabDeSelected";
			nColor1 = argb(255, 255, 255, 255);
		break;
		case 2: // режим путешествий на земле
			sPic2 = "TabDeSelected";
			nColor2 = argb(255, 255, 255, 255);
		break;
		case 3: // море от 3-го лица
			sPic3 = "TabDeSelected";
			nColor3 = argb(255, 255, 255, 255);
		break;
		case 4: // режим боя на земле
			sPic4 = "TabDeSelected";
			nColor4 = argb(255, 255, 255, 255);
		break;
	}

	SetNewGroupPicture("TABBTN_SAILING_1ST", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_PRIMARY_LAND", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_SAILING_3RD", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_FIGHT_MODE", "TABS", sPic4);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_SAILING_1ST", 8, 0, nColor1);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_PRIMARY_LAND", 8, 0, nColor2);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_SAILING_3RD", 8, 0, nColor3);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_FIGHT_MODE", 8, 0, nColor4);

	FillControlsList(nMode);
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if (sNodName == "TABBTN_SAILING_1ST")
	{
		SetControlsTabMode(1);
		return;
	}
	if (sNodName == "TABBTN_PRIMARY_LAND")
	{
		SetControlsTabMode(2);
		return;
	}
	if (sNodName == "TABBTN_SAILING_3RD")
	{
		SetControlsTabMode(3);
		return;
	}
	if (sNodName == "TABBTN_FIGHT_MODE")
	{
		SetControlsTabMode(4);
		return;
	}
}

void procBtnAction()
{
	int i, iComIndex = GetEventData();
	string sNodName = GetEventData();

	if (sNodName == "MB_ACCEPT")
	{
		if (iComIndex == ACTION_ACTIVATE || iComIndex == ACTION_MOUSECLICK)
		{
			ProcessOkExit();
		}
		return;
	}
	if (sNodName == "MB_RESTORE_DEFAULT")
	{
		RestoreDefaultSettings();
		return;
	}

	if(sNodName == "FONT_LEFT")
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_LEFTSTEP )
		{
			if(iFontType < 1) return;
			iFontType -= 1;
			FontDes();
			InterfaceStates.FontType = iFontType;
		}
		return;
	}
	if(sNodName == "FONT_RIGHT")
	{
		if(iComIndex==ACTION_MOUSECLICK || iComIndex==ACTION_RIGHTSTEP)
		{
			if(iFontType > 0) return;
			iFontType += 1;
			FontDes();
			InterfaceStates.FontType = iFontType;
		}
		return;
	}

	if (sNodName == "MOREINFO_RIGHT")
	{
		if (iComIndex == ACTION_MOUSECLICK || iComIndex == ACTION_RIGHTSTEP)
		{
			if(iMoreInfo > 0) return;
			iMoreInfo += 1;
			SetFormatedText("MOREINFO_TEXT", MoreinfoDes());
			InterfaceStates.MoreInfo = iMoreInfo;
		}
		return;
	}
	if (sNodName == "MOREINFO_LEFT")
	{
		if (iComIndex == ACTION_MOUSECLICK || iComIndex == ACTION_LEFTSTEP)
		{
			if(iMoreInfo < 1) return;
			iMoreInfo -= 1;
			SetFormatedText("MOREINFO_TEXT", MoreinfoDes());
			InterfaceStates.MoreInfo = iMoreInfo;
		}
		return;
	}
	if (sNodName == "CONTROLTIPS_RIGHT")
	{
		if (iComIndex == ACTION_MOUSECLICK || iComIndex == ACTION_RIGHTSTEP)
		{
			if (iShowTips >= CONTROL_TIPS_ALL) return;
			iShowTips++;
			SetFormatedText("CONTROLTIPS_TEXT", ControlTipsDes());
			InterfaceStates.ShowControlTips = iShowTips;
		}
		return;
	}
	if (sNodName == "CONTROLTIPS_LEFT")
	{
		if (iComIndex == ACTION_MOUSECLICK || iComIndex == ACTION_LEFTSTEP)
		{
			if (iShowTips <= CONTROL_TIPS_NONE) return;
			iShowTips--;
			SetFormatedText("CONTROLTIPS_TEXT", ControlTipsDes());
			InterfaceStates.ShowControlTips = iShowTips;
		}
		return;
	}
	if (sNodName == "TARGET_MODE_RIGHT")
	{
		if (iComIndex == ACTION_MOUSECLICK || iComIndex == ACTION_RIGHTSTEP)
		{
			if (iGlobalTarget >= CONTROL_TIPS_ALL) return;
			iGlobalTarget++;
			SetFormatedText("TARGET_MODE_TEXT", XI_ConvertString("TargetMode_" + iGlobalTarget));
			InterfaceStates.TargetMode = iGlobalTarget;
		}
		return;
	}
	if (sNodName == "TARGET_MODE_LEFT")
	{
		if (iComIndex == ACTION_MOUSECLICK || iComIndex == ACTION_LEFTSTEP)
		{
			if (iGlobalTarget <= CONTROL_TIPS_NONE) return;
			iGlobalTarget--;
			SetFormatedText("TARGET_MODE_TEXT", XI_ConvertString("TargetMode_" + iGlobalTarget));
			InterfaceStates.TargetMode = iGlobalTarget;
		}
		return;
	}
	if (sNodName == "QUICKSAVESLOTS_RIGHT")
	{
		if (iComIndex == ACTION_MOUSECLICK || iComIndex == ACTION_RIGHTSTEP)
		{
			i = sti(InterfaceStates.QuickSaveSlots);
			if (i >= 96) return;
			i = makeint(i * 2);
			SetFormatedText("QUICKSAVESLOTS_TEXT", XI_ConvertString("QUICKSAVESLOTS_" + i));
			InterfaceStates.QuickSaveSlots = i;
		}
		return;
	}
	if (sNodName == "QUICKSAVESLOTS_LEFT")
	{
		if (iComIndex == ACTION_MOUSECLICK || iComIndex == ACTION_LEFTSTEP)
		{
			i = sti(InterfaceStates.QuickSaveSlots);
			if (i <= 3) return;
			i = makeint(i * 0.5);
			SetFormatedText("QUICKSAVESLOTS_TEXT", XI_ConvertString("QUICKSAVESLOTS_" + i));
			InterfaceStates.QuickSaveSlots = i;
		}
		return;
	}
	if (sNodName == "CONTINUOUS_MUSIC_BUTTON_PLUS")
	{
		if (iComIndex == ACTION_MOUSECLICK)
		{
			SwitchContinuousButtonVisual(true);
		}
		return;
	}
	
	if (sNodName == "CONTINUOUS_MUSIC_BUTTON_MINUS")
	{
		if (iComIndex == ACTION_MOUSECLICK)
		{
			SwitchContinuousButtonVisual(false);
		}
		return;
	}
}

void SwitchContinuousButtonVisual(bool bPlus)
{
	XI_WindowDisable("CONTINUOUS_MUSIC_SETTINGS_WINDOW", !bPlus);
	XI_WindowShow("CONTINUOUS_MUSIC_SETTINGS_WINDOW", bPlus);

	XI_WindowDisable("CONTINUOUS_MUSIC_BUTTON_PLUS_WINDOW", bPlus);
	XI_WindowShow("CONTINUOUS_MUSIC_BUTTON_PLUS_WINDOW", !bPlus);

	XI_WindowDisable("CONTINUOUS_MUSIC_BUTTON_MINUS_WINDOW", !bPlus);
	XI_WindowShow("CONTINUOUS_MUSIC_BUTTON_MINUS_WINDOW", bPlus);
}

void RestoreDefaultSettings()
{
	int i, n;
	string s;

	//настройка графики
	if (settingsState == MB_VIDEO_SETTINGS)
	{
		GameInterface.nodes.GAMMA_SLIDE.value = 0.5;
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "GAMMA_SLIDE", 0, 0.5);
		GameInterface.nodes.BRIGHT_SLIDE.value = 0.5;
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "BRIGHT_SLIDE", 0, 0.5);
		GameInterface.nodes.CONTRAST_SLIDE.value = 0.5;
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "CONTRAST_SLIDE", 0, 0.5);
		GameInterface.nodes.GLOW_SLIDE.value = 0.0;
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "GLOW_SLIDE", 0, 0.0);
		GameInterface.nodes.HERB_SLIDE.value = 0.0;
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HERB_SLIDE", 0, 0.0);
		GameInterface.nodes.HERB_SLIDE2.value = 0.0;
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HERB_SLIDE2", 0, 0.0);

		InterfaceStates.CrewOnDeck = 1;
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"CREWONDECK_CHECKBOX", 2, 1, 1);

		InterfaceStates.SkyRotation = 1;
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"SKYROTATION_CHECKBOX", 2, 1, 1);

		InterfaceStates.FoliageDrawDistance = 1000;
		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"FOLIAGE_DRAW_DISTANCE_SLIDE", 0, 0.2);
	}

	//игровые настройки
	if (settingsState == MB_GAME_SETTINGS)
	{
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SIMPLESEA_CHECKBOX", 2, 1, 0);
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "BATTLE_MODE_CHECKBOX", 2, 1, 0);
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SKIPVIDEO_CHECKBOX", 2, 1, 0);
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "AUTOSAVE_CHECKBOX", 2, 1, 1);
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SHIPMARK_CHECKBOX", 2, 1, 1);
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "QUESTMARK_CHECKBOX", 2, 1, 1);
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TIMESPEEDACCEL_CHECKBOX", 2, 1, 0);

		InterfaceStates.MoreInfo = 0;
		iMoreInfo = 0;
		SetFormatedText("MOREINFO_TEXT", MoreInfoDes());
		InterfaceStates.ShowControlTips = 3;
		iShowTips = CONTROL_TIPS_ALL;
		SetFormatedText("CONTROLTIPS_TEXT", ControltipsDes());
		iGlobalTarget = 2;
		SetFormatedText("TARGET_MODE_TEXT", XI_ConvertString("TargetMode_" + iGlobalTarget));
		SetFormatedText("QUICKSAVESLOTS_TEXT", XI_ConvertString("QuickSaveSlots_12"));

		fHUDRatio = GetScreenScale();
		float sl = CalcHUDSlider(fHUDRatio);
		if (FloatToString(sl, 2) != FloatToString(stf(GameInterface.nodes.hud_slide.value), 2)) bSkipChangeHUD = true;
		GameInterface.nodes.hud_slide.value = sl;
		SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "HUD_SLIDE", 2, makeint(sl * 100.0));
		iHUDBase = CalcHUDBase(sl, stf(Render.screen_y));
		SetFormatedText("HUD_DESCRIP_TEXT", XI_ConvertString("HudDescripText") + ": " + Render.screen_y + "  / " + iHUDBase + " : " + fHUDRatio);
	}

	//настройка звуков
	if (settingsState == MB_SOUND_SETTINGS)
	{
		SendMessage(&sound, "lfff", MSG_SOUND_SET_MASTER_VOLUME, 0.25, 0.25, 0.25);
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "MUSIC_SLIDE", 0, 0.25);
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "SOUND_SLIDE", 0, 0.25);
		SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "DIALOG_SLIDE", 0, 0.25);
		InterfaceStates.ContinuousMusic = 1;
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CONTINUOUS_MUSIC_CHECKBOX", 2, 1, 1);
		InterfaceStates.NoAdultSounds = 1;
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"ADULT_SOUNDS_CHECKBOX", 2, 1, 1);

		for (n = 1; n < 8; n++)
		{
			switch (n)
			{
				case 1: s = "jungle"; break;
				case 2: s = "house"; break;
				case 3: s = "brothel"; break;
				case 4: s = "ship"; break;
				case 5: s = "boarding"; break;
				case 6: s = "attack"; break;
				case 7: s = "lsc"; break;
			}

			i = 1;
			if (n == 7) i--;
			SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CONTINUOUS_MUSIC_" + s + "_CHECKBOX", 2, 1, i);
		}
	}

	//настройка управления
	if (settingsState == MB_CONTROLS_SETTINGS)
	{
		RestoreDefaultKeys();
	}
}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if (settingsState == MB_SOUND_SETTINGS && !HasStr(sNodName, "CONTINUOUS_MUSIC_"))
		HideContinuousMusicSettings(1);

	if (sNodName == "HERB_CHECKBOX")
	{
		if (bBtnState == true)
		{
			switch (nBtnIndex)
			{
				case 1: iGrassQuality = 3; break;
				case 2: iGrassQuality = 2; break;
				case 3: iGrassQuality = 1; break;
				case 4: iGrassQuality = 0; break;
			}
		}
		return;
	}

	if (sNodName == "ALWAYS_RUN_CHECKBOX")
	{
		// always run
		SetAlwaysRun(bBtnState);
	}

	if (sNodName == "INVERT_MOUSE_CHECKBOX")
	{
		// invert mouse
		InterfaceStates.InvertCameras = bBtnState;
	}

	if (sNodName == "QUESTMARK_CHECKBOX")
	{
		InterfaceStates.EnabledQuestsMarks = bBtnState;
	}

	if (sNodName == "QUESTPOINTER_CHECKBOX")
	{
		InterfaceStates.EnabledQuestsPointers = bBtnState;
	}

	if (sNodName == "SIMPLESEA_CHECKBOX")
	{
		// Show battle mode border
		InterfaceStates.SimpleSea = bBtnState;
	}

	if (sNodName == "BATTLE_MODE_CHECKBOX")
	{
		// Show battle mode border
		InterfaceStates.ShowBattleMode = bBtnState;
	}

	if (sNodName == "SKIPVIDEO_CHECKBOX")
	{
		// Skip Start Video
		InterfaceStates.SkipStartVideo = bBtnState;
	}

	if (sNodName == "SHIPMARK_CHECKBOX")
	{
		// Show battle mode border
		InterfaceStates.EnabledShipMarks = bBtnState;
	}

	if (sNodName == "AUTOSAVE_CHECKBOX")
	{
		// Show battle mode border
		InterfaceStates.EnabledAutoSaveMode = bBtnState;
	}

	if (sNodName == "CHAR_STRING_CHECKBOX")
	{
		InterfaceStates.ShowCharString = bBtnState;
	}

	if (sNodName == "TUTORIAL_CHECKBOX")
	{
		InterfaceStates.ShowTutorial = bBtnState;
	}

	if (sNodName == "CREWONDECK_CHECKBOX")
	{
		InterfaceStates.CrewOnDeck = bBtnState;
	}

	if (sNodName == "SKYROTATION_CHECKBOX")
	{
		InterfaceStates.SkyRotation = bBtnState;
	}

	if (sNodName == "TIMESPEEDACCEL_CHECKBOX")
	{
		InterfaceStates.TimeSpeedAccel = bBtnState;
	}

	if (sNodName == "ADULT_SOUNDS_CHECKBOX")
	{
		InterfaceStates.NoAdultSounds = bBtnState;
	}

	if (sNodName == "CONTINUOUS_MUSIC_CHECKBOX")
	{
		InterfaceStates.ContinuousMusic = bBtnState;
		CheckContinuousMusicButtonEnable(bBtnState);
	}
	
	switch (sNodName)
	{
		case "CONTINUOUS_MUSIC_CHECKBOX": InterfaceStates.ContinuousMusic = bBtnState; break;
		case "CONTINUOUS_MUSIC_JUNGLE_CHECKBOX": InterfaceStates.ContinuousMusic.Jungle = bBtnState; break;
		case "CONTINUOUS_MUSIC_HOUSE_CHECKBOX": InterfaceStates.ContinuousMusic.House = bBtnState; break;
		case "CONTINUOUS_MUSIC_BROTHEL_CHECKBOX": InterfaceStates.ContinuousMusic.Brothel = bBtnState; break;
		case "CONTINUOUS_MUSIC_SHIP_CHECKBOX": InterfaceStates.ContinuousMusic.Ship = bBtnState; break;
		case "CONTINUOUS_MUSIC_BOARDING_CHECKBOX": InterfaceStates.ContinuousMusic.Boarding = bBtnState; break;
		case "CONTINUOUS_MUSIC_ATTACK_CHECKBOX": InterfaceStates.ContinuousMusic.Attack = bBtnState; break;
		case "CONTINUOUS_MUSIC_LSC_CHECKBOX": InterfaceStates.ContinuousMusic.LSC = bBtnState; break;
	}
}

void CheckContinuousMusicButtonEnable(bool bState)
{
	Button_SetEnable("CONTINUOUS_MUSIC_JUNGLE_CHECKBOX", bState);
	Button_SetEnable("CONTINUOUS_MUSIC_HOUSE_CHECKBOX", bState);
	Button_SetEnable("CONTINUOUS_MUSIC_BROTHEL_CHECKBOX", bState);
	Button_SetEnable("CONTINUOUS_MUSIC_SHIP_CHECKBOX", bState);
	Button_SetEnable("CONTINUOUS_MUSIC_BOARDING_CHECKBOX", bState);
	Button_SetEnable("CONTINUOUS_MUSIC_ATTACK_CHECKBOX", bState);
	Button_SetEnable("CONTINUOUS_MUSIC_LSC_CHECKBOX", bState);
}

void procSlideChange()
{
	string sNodeName = GetEventData();
	int nVal = GetEventData();
	float fVal = GetEventData();

	if (settingsState == MB_SOUND_SETTINGS && !HasStr(sNodeName, "CONTINUOUS_MUSIC_"))
		HideContinuousMusicSettings(1);

	if (sNodeName == "GAMMA_SLIDE" || sNodeName == "BRIGHT_SLIDE" || sNodeName == "CONTRAST_SLIDE")
	{
		ChangeVideoColor();
		return;
	}

	// Warship 07.07.09 Эффект свечения
	if (sNodeName == "GLOW_SLIDE")
	{
		InterfaceStates.GlowEffect = fVal * 250;
		return;
	}

	if (sNodeName == "SEA_DETAILS_SLIDE")
	{
		ChangeSeaDetail();
		return;
	}

	if (sNodeName == "HUD_SLIDE")
	{
		ChangeHUDDetail();
		return;
	}

	if (sNodeName == "HERB_SLIDE" || sNodeName == "HERB_SLIDE2")
	{
		if (sNodeName == "HERB_SLIDE")
			ChangeHerbDetail(0);
		else
			ChangeHerbDetail(1);
		return;
	}

	if (sNodeName == "MUSIC_SLIDE" || sNodeName == "SOUND_SLIDE" || sNodeName == "DIALOG_SLIDE")
	{
		ChangeSoundSetting();
		return;
	}

	if (sNodeName == "VMOUSE_SENSITIVITY_SLIDE" || sNodeName == "HMOUSE_SENSITIVITY_SLIDE")
	{
		ChangeMouseSensitivity();
	}

	if (sNodeName == "FOLIAGE_DRAW_DISTANCE_SLIDE")
	{
		InterfaceStates.FoliageDrawDistance = fVal * 5000;
		sFoliageDrawDistance = sti(InterfaceStates.FoliageDrawDistance);
		return;
	}
}

void ChangeMouseSensitivity()
{
	InterfaceStates.mouse.loc_sens = stf(GameInterface.nodes.hmouse_sensitivity_slide.value);
	InterfaceStates.mouse.sea_sens = stf(GameInterface.nodes.vmouse_sensitivity_slide.value);
	SetRealMouseSensitivity();
}

void ChangeVideoColor()
{
	float fCurContrast = stf(GameInterface.nodes.contrast_slide.value);
	float fCurGamma = stf(GameInterface.nodes.GAMMA_SLIDE.value);
	float fCurBright = stf(GameInterface.nodes.BRIGHT_SLIDE.value);

	float fContrast = ConvertContrast(fCurContrast, false);
	float fGamma = ConvertGamma(fCurGamma, false);
	float fBright = ConvertBright(fCurBright, false);

	if (!CheckAttribute(&InterfaceStates, "video.contrast") ||
	(stf(InterfaceStates.video.contrast) != fContrast) ||
	(stf(InterfaceStates.video.gamma) != fGamma) ||
	(stf(InterfaceStates.video.brightness) != fBright))
	{
		InterfaceStates.video.contrast = fContrast;
		InterfaceStates.video.gamma = fGamma;
		InterfaceStates.video.brightness = fBright;
		XI_SetColorCorrection(fContrast, fGamma, fBright);
	}
}

void ChangeSeaDetail()
{
	float fCurSeaDetail = stf(GameInterface.nodes.sea_details_slide.value);
	float fSeaDetail = ConvertSeaDetails(fCurSeaDetail, false);
	if (!CheckAttribute(&InterfaceStates, "SeaDetails") ||
	(stf(InterfaceStates.SeaDetails) != fSeaDetail))
	{
		InterfaceStates.SeaDetails = fSeaDetail;
	}
}

void ChangeHerbDetail(int iSlide)
{
	string sMsg;
	float fRange = stf(GameInterface.nodes.herb_slide.value);
	float fHeight = stf(GameInterface.nodes.herb_slide2.value);
	float fDistMin = 10.0;
	float fDistMax = 50.0;

	InterfaceStates.HerbDetails.Range = fRange;
	fDistMin = fDistMin + fRange * 100.0;
	fDistMax = fDistMax + fRange * 100.0;

	InterfaceStates.HerbDetails.Height = fHeight;

//	switch (iSlide)
//	{
//		 > TODO
//				case 0:
//					sMsg = "#    " + XI_ConvertString("Herb Range") + " " + FloatToString(fRange, 1);
//					SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "TITLES_STR", 1, 12, sMsg);
//				break;
//				case 1:
//					sMsg = "#    " + XI_ConvertString("Herb Height") + " " + FloatToString(fHeight, 1);
//					SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE, "TITLES_STR", 1, 13, sMsg);
//				break;
//	}

	if (IsEntity(PChar))
		SendMessage(loadedLocation, "lsffffff", MSG_LOCATION_EX_MSG, "SetGrassParams", 1.0, 1.0, 0.2 + fHeight * 2.0, fDistMin, fDistMax, 0.0);
}

void ChangeSoundSetting()
{
	float fMusic = stf(GameInterface.nodes.music_slide.value);
	float fSound = stf(GameInterface.nodes.sound_slide.value);
	float fDialog = stf(GameInterface.nodes.dialog_slide.value);
	SendMessage(&sound, "lfff", MSG_SOUND_SET_MASTER_VOLUME, fSound, fMusic, fDialog);
}

void FillControlsList(int nMode)
{
	int n, qC, idx;
	string groupName;
	aref arGrp, arC;

	if (nMode == g_nCurControlsMode)
	{
		return;
	}
	g_nCurControlsMode = nMode;
	DeleteAttribute(&GameInterface, "controls_list");
	GameInterface.controls_list.select = 0;

	groupName = GetGroupNameByMode(nMode);
	if (CheckAttribute(&objControlsState, "keygroups." + groupName))
	{
		makearef(arGrp, objControlsState.keygroups.(groupName));
		qC = GetAttributesNum(arGrp);
		idx = 0;
		for (n = 0; n < qC; n++) {
			arC = GetAttributeN(arGrp, n);
			// --> belamour убрать контролки из опций 
			string sControl = GetAttributeName(arC);
			if (HasStr(sControl, "AltModeFastTravel_")) continue;
			// <-- belamour

			if (false == CheckAttribute(arC, "invisible") || arC.invisible != "1")
			{
				//if( CheckAttribute(arC,"remapping") && arC.remapping=="1" ) {
				if (AddToControlsList(idx, GetAttributeName(arC), GetAttributeValue(arC), CheckAttribute(arC, "remapping") && arC.remapping == "1"))
				{
					idx++;
				}
			}
		}
	}
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONTROLS_LIST", 0);
}

bool AddToControlsList(int row, string sControl, string sKey, bool bRemapable)
{
	string rowname = "tr" + (row + 1);
	GameInterface.controls_list.(rowname).userdata.remapable = bRemapable;
	GameInterface.controls_list.(rowname).userdata.control = sControl;
	GameInterface.controls_list.(rowname).userdata.key = sKey;
	GameInterface.controls_list.(rowname).td2.str = LanguageConvertString(g_ControlsLngFile, sControl);
	if (GameInterface.controls_list.(rowname).td2.str == "")
	{
		trace("Warning!!! " + sControl + " hav`t translate value");
	}
	if (!bRemapable)
	{
		// выделение контролок которые нельзя поменять
		GameInterface.controls_list.(rowname).td2.color = argb(255, 128, 128, 128);
	}
	if (CheckAttribute(&objControlsState, "key_codes." + sKey + ".img"))
	{
		GameInterface.controls_list.(rowname).td1.fontidx = 0;
		GameInterface.controls_list.(rowname).td1.textoffset = "2,-1";
		GameInterface.controls_list.(rowname).td1.scale = 0.5;
		GameInterface.controls_list.(rowname).td1.str = objControlsState.key_codes.(sKey).img;
	}
	return true;
}

string GetGroupNameByMode(int nMode)
{
	switch (nMode)
	{
		case 1: return "Sailing1Pers"; break;
		case 2: return "PrimaryLand"; break;
		case 3: return "Sailing3Pers"; break;
		case 4: return "FightModeControls"; break;
	}
	return "unknown";
}

void GetSoundOptionsData()
{
	float fCurMusic = 0.25;
	float fCurSound = 0.25;
	float fCurDialog = 0.25;
	SendMessage(&sound, "leee", MSG_SOUND_GET_MASTER_VOLUME, &fCurSound, &fCurMusic, &fCurDialog);
	GameInterface.nodes.music_slide.value = fCurMusic;
	GameInterface.nodes.sound_slide.value = fCurSound;
	GameInterface.nodes.dialog_slide.value = fCurDialog;
}

void GetMouseOptionsData()
{
	float fCurXSens = 0.5;
	float fCurYSens = 0.5;
	if (CheckAttribute(&InterfaceStates, "mouse.loc_sens"))
	{
		fCurXSens = stf(InterfaceStates.mouse.loc_sens);
	}
	if (CheckAttribute(&InterfaceStates, "mouse.sea_sens"))
	{
		fCurYSens = stf(InterfaceStates.mouse.sea_sens);
	}
	if (fCurXSens < 0.0) fCurXSens = 0.0;
	if (fCurXSens > 1.0) fCurXSens = 1.0;
	if (fCurYSens < 0.0) fCurYSens = 0.0;
	if (fCurYSens > 1.0) fCurYSens = 1.0;
	GameInterface.nodes.hmouse_sensitivity_slide.value = fCurXSens;
	GameInterface.nodes.vmouse_sensitivity_slide.value = fCurYSens;
}

void GetVideoOptionsData()
{
	float fC = 1.0;
	float fG = 1.0;
	float fB = 0.0;
	float fD = 1.0;
	float fE = 0.0;
	float fR = 0.0;
	float fHR = 0.0;
	float fHH = 0.0;

	if (CheckAttribute(&InterfaceStates, "video.contrast"))
	{
		fC = stf(InterfaceStates.video.contrast);
	}

	if (CheckAttribute(&InterfaceStates, "video.gamma"))
	{
		fG = stf(InterfaceStates.video.gamma);
	}

	if (CheckAttribute(&InterfaceStates, "video.brightness"))
	{
		fB = stf(InterfaceStates.video.brightness);
	}

	if (CheckAttribute(&InterfaceStates, "SeaDetails"))
	{
		fD = stf(InterfaceStates.SeaDetails);
	}

	if (CheckAttribute(&InterfaceStates, "HerbDetails.Range"))
		fHR = stf(InterfaceStates.HerbDetails.Range);

	if (CheckAttribute(&InterfaceStates, "HerbDetails.Height"))
		fHH = stf(InterfaceStates.HerbDetails.Height);

	ISetColorCorrection(fC, fG, fB, fD, fE, fR, fHR, fHH);
}

void ISetColorCorrection(float fContrast, float fGamma, float fBright, float fSeaDetails, float fPerspDetails, float fRad, float fHerbRange, float fHerbHeight)
{
	float fCurContrast = ConvertContrast(fContrast, true);
	float fCurGamma = ConvertGamma(fGamma, true);
	float fCurBright = ConvertBright(fBright, true);
	float fCurSeaDetails = ConvertSeaDetails(fSeaDetails, true);
	float fCurHerbRange = fHerbRange;
	float fCurHerbHeight = fHerbHeight;

	Restrictor(&fCurContrast, 0.0, 1.0);
	Restrictor(&fCurGamma, 0.0, 1.0);
	Restrictor(&fCurBright, 0.0, 1.0);
	Restrictor(&fCurSeaDetails, 0.0, 1.0);
	Restrictor(&fCurHerbRange, 0.0, 1.0);
	Restrictor(&fCurHerbHeight, 0.0, 1.0);

	GameInterface.nodes.CONTRAST_SLIDE.value = fCurContrast;
	GameInterface.nodes.GAMMA_SLIDE.value = fCurGamma;
	GameInterface.nodes.BRIGHT_SLIDE.value = fCurBright;
	GameInterface.nodes.SEA_DETAILS_SLIDE.value = fCurSeaDetails;
	GameInterface.nodes.HERB_SLIDE.value = fCurHerbRange;
	GameInterface.nodes.HERB_SLIDE2.value = fCurHerbHeight;

	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "CONTRAST_SLIDE", 0, fCurContrast);
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "GAMMA_SLIDE", 0, fCurGamma);
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "BRIGHT_SLIDE", 0, fCurBright);
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "SEA_DETAILS_SLIDE", 0, fCurSeaDetails);
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HERB_SLIDE", 0, fCurHerbRange);
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HERB_SLIDE2", 0, fCurHerbHeight);

	XI_SetColorCorrection(fContrast, fGamma, fBright);
	//Set sea detail
}

float ConvertContrast(float fContrast, bool Real2Slider)
{
	// контрастность от 0.75 до 1.25
	if (Real2Slider)
	{
		return fContrast * 2.0 - 1.5;
	}
	return fContrast * 0.5 + 0.75;
}

float ConvertGamma(float fGamma, bool Real2Slider)
{
	// гамма от 0.5 до 2.0
	if (Real2Slider)
	{
		if (fGamma <= 1.0)
		{
			return fGamma - 0.5;
		}
		return fGamma * 0.5;
	}
	if (fGamma <= 0.5)
	{
		return fGamma + 0.5;
	}
	return fGamma * 2.0;
}

float ConvertBright(float fBright, bool Real2Slider)
{
	if (Real2Slider)
	{
		return (fBright + 50.0) / 100.0;
	}
	return fBright * 100 - 50;
}

float ConvertSeaDetails(float fDetails, bool Real2Slider)
{
	return fDetails;
}

void GetHerbOptionsData()
{
	int nSelBtn = 0;
	switch (iGrassQuality)
	{
		case 0: nSelBtn = 4; break;
		case 1: nSelBtn = 3; break;
		case 2: nSelBtn = 2; break;
		case 3: nSelBtn = 1; break;
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "HERB_CHECKBOX", 2, nSelBtn, true);
}

void GetControlsStatesData()
{
	int nAlwaysRun = 0;
	if (CheckAttribute(&InterfaceStates, "alwaysrun"))
	{
		nAlwaysRun = sti(InterfaceStates.alwaysrun);
	}
	int nInvertCam = 0;
	if (CheckAttribute(&InterfaceStates, "InvertCameras"))
	{
		nInvertCam = sti(InterfaceStates.InvertCameras);
	}
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "ALWAYS_RUN_CHECKBOX", 2, 1, nAlwaysRun);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "INVERT_MOUSE_CHECKBOX", 2, 1, nInvertCam);
}

void SetAlwaysRun(bool bRun)
{
	InterfaceStates.alwaysrun = bRun;
	pchar.alwaysrun = bRun;
}

void procKeyChange()
{
	//FillControlsList();
	string srow = "tr" + GameInterface.controls_list.select;
	if (!CheckAttribute(&GameInterface, "controls_list." + srow))
	{
		return;
	}
	if (sti(GameInterface.controls_list.(srow).userdata.remapable) != 1)
	{
		return;
	}
	ChooseOtherControl();
}

void ChooseOtherControl()
{
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowShow("CHANGEKEY_WINDOW", true);
	SetCurrentNode("KEY_CHOOSER");
	string srow = "tr" + GameInterface.controls_list.select;
	SetFormatedText("CHANGEKEY_TEXT", XI_ConvertString("Press any key"));
	AddLineToFormatedText("CHANGEKEY_TEXT", " ");
	AddLineToFormatedText("CHANGEKEY_TEXT", GameInterface.controls_list.(srow).td2.str);
	AddLineToFormatedText("CHANGEKEY_TEXT", " ");
	AddLineToFormatedText("CHANGEKEY_TEXT", XI_ConvertString("KeyAlreadyUsed"));
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CHANGEKEY_TEXT", 8, 0, argb(255, 255, 128, 128));
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CHANGEKEY_TEXT", 8, 4, argb(0, 255, 64, 64));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CHANGEKEY_TEXT", 5);
}

int glob_retVal;
ref procKeyChoose()
{
	int keyIdx = GetEventData();
	int stickUp = GetEventData();

	glob_retVal = false;

	if (keyIdx == 7)
	{
		ReturnFromReassign();
		glob_retVal = true;
		return &glob_retVal;
	}

	if (DoMapToOtherKey(keyIdx, stickUp))
	{
		ReturnFromReassign();
		glob_retVal = true;
	}

	return &glob_retVal;
}

void ReturnFromReassign()
{
	XI_WindowShow("CHANGEKEY_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);
	SetCurrentNode("CONTROLS_LIST");
}

bool DoMapToOtherKey(int keyIdx, int stickUp)
{
	string srow = "tr" + GameInterface.controls_list.select;
	string groupName = GetGroupNameByMode(g_nCurControlsMode);
	string sControl = GameInterface.controls_list.(srow).userdata.control;
	string sKey = GameInterface.controls_list.(srow).userdata.key;

	aref arControlGroup;
	aref arKeyRoot, arKey;
	string tmpstr;
	int keyCode;

	if (stickUp)
	{
		//SetStickNotAvailable();
		return false;
	}

	makearef(arControlGroup, objControlsState.keygroups.(groupName));
	makearef(arKeyRoot, objControlsState.key_codes);
	arKey = GetAttributeN(arKeyRoot, keyIdx);
	keyCode = sti(GetAttributeValue(arKey));

	// check for not allowed keys
	if (//keyCode==sti(objControlsState.key_codes.VK_F1) ||
	keyCode == sti(objControlsState.key_codes.VK_F2) ||
	//keyCode==sti(objControlsState.key_codes.VK_F3) ||
	//keyCode==sti(objControlsState.key_codes.VK_F4) ||
	//keyCode==sti(objControlsState.key_codes.VK_F5) ||
	keyCode == sti(objControlsState.key_codes.VK_F6) ||
	//keyCode==sti(objControlsState.key_codes.VK_F7) ||
	keyCode == sti(objControlsState.key_codes.VK_F8) ||
	keyCode == sti(objControlsState.key_codes.VK_F9))
	{
		return false;
	}

	if (CheckAttribute(arKey, "stick") && sti(arKey.stick) == true) return false;

	if (KeyAlreadyUsed(groupName, sControl, GetAttributeName(arKey)))
	{
		SetKeyChooseWarning(XI_ConvertString("KeyAlreadyUsed"));
		return false;
	}

	tmpstr = arControlGroup.(sControl);
	if (CheckAttribute(arKeyRoot, tmpstr + ".stick") && sti(arKeyRoot.(tmpstr).stick) == true) return false;

	int state = 0;
	if (CheckAttribute(arControlGroup, sControl + ".state"))
	{
		state = sti(arControlGroup.(sControl).state);
	}

    if (CheckAttribute(&objControlsState, "map.controls." + sControl + ".sync"))
    {
        tmpstr = objControlsState.map.controls.(sControl).sync;
        if (CheckAttribute(&objControlsState, "keygroups." + groupName + "." + tmpstr))
        {
            CI_CreateAndSetControls(groupName, tmpstr, keyCode, state, true);
            tmpstr = ControlsFindRow(tmpstr);
            GameInterface.controls_list.(tmpstr).userdata.key = GetAttributeName(arKey);
            GameInterface.controls_list.(tmpstr).td1.str = arKey.img;
        }
    }

	CI_CreateAndSetControls(groupName, sControl, keyCode, state, true);
	GameInterface.controls_list.(srow).userdata.key = GetAttributeName(arKey);
	GameInterface.controls_list.(srow).td1.str = arKey.img;
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONTROLS_LIST", 0);
	return true;
}

string ControlsFindRow(string sControl)
{
    aref aList, aRow;
    makearef(aList, GameInterface.controls_list);
    int qty = GetAttributesNum(aList);
    for (int i = 0; i < qty; i++)
    {
        aRow = GetAttributeN(aList, i);
        if (CheckAttribute(aRow, "userdata.control") && aRow.userdata.control == sControl)
            return GetAttributeName(aRow);
    }
    return "none";
}

void RestoreDefaultKeys()
{
	SetMouseToDefault();
	ControlsInit(GetTargetPlatform(), false);

	int nMode = g_nCurControlsMode;
	g_nCurControlsMode = -1;
	FillControlsList(nMode);
}

void SetMouseToDefault()
{
	InterfaceStates.InvertCameras = false;
	InterfaceStates.mouse.loc_sens = 0.5;
	InterfaceStates.mouse.sea_sens = 0.5;

	SetRealMouseSensitivity();
	SetAlwaysRun(true);

	GetControlsStatesData();
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "VMOUSE_SENSITIVITY_SLIDE", 0, stf(InterfaceStates.mouse.sea_sens));
	SendMessage(&GameInterface, "lslf", MSG_INTERFACE_MSG_TO_NODE, "HMOUSE_SENSITIVITY_SLIDE", 0, stf(InterfaceStates.mouse.loc_sens));
}

void ShowInfo()
{
	g_bToolTipStarted = true;
	string sHeader = "TEST";
	string sNode = GetCurrentNode();

	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	switch (sNode)
	{
		case "GAMMA_SLIDE":
			sHeader = XI_ConvertString("gamma");
			sText1 = XI_ConvertString("gamma_descr");
			sText3 = XI_ConvertString("FullScreenOnly");
		break;
		case "BRIGHT_SLIDE":
			sHeader = XI_ConvertString("Brightness");
			sText1 = XI_ConvertString("brightness_descr");
			sText3 = XI_ConvertString("FullScreenOnly");
		break;
		case "CONTRAST_SLIDE":
			sHeader = XI_ConvertString("Contrast");
			sText1 = XI_ConvertString("Contrast_descr");
			sText3 = XI_ConvertString("FullScreenOnly");
		break;

		case "GLOW_SLIDE":
			sHeader = XI_ConvertString("Glow");
			sText1 = XI_ConvertString("Glow_descr");
			sText2 = XI_ConvertString("PostProcessOnly");
		break;

		case "SEA_DETAILS_SLIDE":
			sHeader = XI_ConvertString("Sea Detail");
			sText1 = XI_ConvertString("Sea Detail_descr");
			sText2 = XI_ConvertString("ItCanRedusePerfomance");
			sText3 = XI_ConvertString("NeedToExitFromSea");
		break;

		case "HERB_CHECKBOX":
			sHeader = XI_ConvertString("Herb Quantity");
			sText1 = XI_ConvertString("Herb Quantity_descr");
			sText2 = XI_ConvertString("ItCanRedusePerfomance");
		break;

		case "HERB_SLIDE":
			sHeader = XI_ConvertString("Herb Range");
			sText1 = XI_ConvertString("Herb Range_descr");
			sText2 = XI_ConvertString("ItCanRedusePerfomance");
		break;

		case "HERB_SLIDE2":
			sHeader = XI_ConvertString("Herb Height");
			sText1 = XI_ConvertString("Herb Height_descr");
			sText2 = XI_ConvertString("ItCanRedusePerfomance");
		break;

		case "FOLIAGE_DRAW_DISTANCE_SLIDE":
			sHeader = XI_ConvertString("Foliage Options");
			sText1 = XI_ConvertString("Foliage Draw Distance_descr");
			sText2 = XI_ConvertString("ItCanRedusePerfomance");
		break;

		case "MUSIC_SLIDE":
			sHeader = XI_ConvertString("Music Volume");
			sText1 = XI_ConvertString("Music Volume_descr");
		break;

		case "SOUND_SLIDE":
			sHeader = XI_ConvertString("Sound Volume");
			sText1 = XI_ConvertString("Sound Volume_descr");
		break;

		case "DIALOG_SLIDE":
			sHeader = XI_ConvertString("Dialog Volume");
			sText1 = XI_ConvertString("Dialog Volume_descr");
		break;

		case "HUD_SLIDE":
			sHeader = XI_ConvertString("HUD_SLIDE");
			sText1 = XI_ConvertString("HUD_SLIDE_descr");
		break;

		case "ALWAYS_RUN_CHECKBOX":
			sHeader = XI_ConvertString("Always Run");
			sText1 = XI_ConvertString("Always Run_descr");
		break;

		case "INVERT_MOUSE_CHECKBOX":
			sHeader = XI_ConvertString("Invert Vertical Mouse Control");
			sText1 = XI_ConvertString("Invert Vertical Mouse Control_descr");
		break;

		case "VMOUSE_SENSITIVITY_SLIDE":
			sHeader = XI_ConvertString("Location Mouse Sensitivity");
			sText1 = XI_ConvertString("Location Mouse Sensitivity_descr");
		break;

		case "HMOUSE_SENSITIVITY_SLIDE":
			sHeader = XI_ConvertString("Sea Mouse Sensitivity");
			sText1 = XI_ConvertString("Sea Mouse Sensitivity_descr");
		break;

		case "SIMPLESEA_CHECKBOX":
			sHeader = XI_ConvertString("SimpleSea Mode");
			sText1 = XI_ConvertString("SimpleSea Mode_descr");
		break;

		case "BATTLE_MODE_CHECKBOX":
			sHeader = XI_ConvertString("Show battle mode");
			sText1 = XI_ConvertString("Show battle mode_descr");
		break;

		case "SKIPVIDEO_CHECKBOX":
			sHeader = XI_ConvertString("SkipStartVideo");
			sText1 = XI_ConvertString("SkipStartVideo_descr");
		break;

		case "SHIPMARK_CHECKBOX":
			sHeader = XI_ConvertString("ShipMark Mode");
			sText1 = XI_ConvertString("ShipMark Mode_descr");
		break;

		case "AUTOSAVE_CHECKBOX":
			sHeader = XI_ConvertString("AutoSave Mode");
			sText1 = XI_ConvertString("AutoSave Mode_descr");
		break;

		case "QUESTMARK_CHECKBOX":
			sHeader = XI_ConvertString("QuestMark Mode");
			sText1 = XI_ConvertString("QuestMark Mode_descr");
		break;

		case "QUESTPOINTER_CHECKBOX":
			sHeader = XI_ConvertString("QuestPointer Mode");
			sText1 = XI_ConvertString("QuestPointer Mode_descr");
		break;

		case "CHAR_STRING_CHECKBOX":
			sHeader = XI_ConvertString("Show characters strings");
			sText1 = XI_ConvertString("Show characters strings_descr");
		break;

		case "TUTORIAL_CHECKBOX":
			sHeader = XI_ConvertString("Show tutorial");
			sText1 = XI_ConvertString("Show tutorial_descr");
		break;

		case "FONT_DESCRIP_TEXT":
			sHeader = XI_ConvertString("Questbook Font");
			sText1 = XI_ConvertString("Questbook Font_descr");
		break;

		case "FONT_TITLE":
			sHeader = XI_ConvertString("Questbook Font");
			sText1 = XI_ConvertString("Questbook Font_descr");
		break;

		case "MOREINFO_TEXT":
			sHeader = XI_ConvertString("More Info");
			sText1 = XI_ConvertString("More Info_descr");
		break;

		case "MOREINFO_TITLE":
			sHeader = XI_ConvertString("More Info");
			sText1 = XI_ConvertString("More Info_descr");
		break;

		case "CONTROLTIPS_TEXT":
			sHeader = XI_ConvertString("ControlTipsMode");
			sText1 = XI_ConvertString("ControlTipsMode_base");
			sText3 = XI_ConvertString("ControlTipsMode_ext");
		break;

		case "CONTROLTIPS_TITLE":
			sHeader = XI_ConvertString("ControlTipsMode");
			sText1 = XI_ConvertString("ControlTipsMode_base");
			sText3 = XI_ConvertString("ControlTipsMode_ext");
		break;

		case "TARGET_MODE_TEXT":
			sHeader = XI_ConvertString("TargetMode");
			sText1 = XI_ConvertString("TargetMode_descr");
		break;

		case "TARGET_MODE_TITLE":
			sHeader = XI_ConvertString("TargetMode");
			sText1 = XI_ConvertString("TargetMode_descr");
		break;

		case "QUICKSAVESLOTS_TEXT":
			sHeader = XI_ConvertString("QuickSaveSlots");
			sText1 = XI_ConvertString("QuickSaveSlots_descr");
		break;

		case "QUICKSAVESLOTS_TITLE":
			sHeader = XI_ConvertString("QuickSaveSlots");
			sText1 = XI_ConvertString("QuickSaveSlots_descr");
		break;

		case "SKYROTATION_CHECKBOX":
			sHeader = XI_ConvertString("Sky rotation");
			sText1 = XI_ConvertString("Sky rotation descr");
		break;

		case "ADULT_SOUNDS_CHECKBOX":
			sHeader = XI_ConvertString("Adult sounds");
			sText1 = XI_ConvertString("Adult sounds descr");
		break;

		case "CREWONDECK_CHECKBOX":
			sHeader = XI_ConvertString("Crew on deck");
			sText1 = XI_ConvertString("Crew on deck descr");
		break;

		case "TIMESPEEDACCEL_CHECKBOX":
			sHeader = XI_ConvertString("TimeSpeedAccel");
			sText1 = XI_ConvertString("TimeSpeedAccel descr");
		break;

		case "CONTINUOUS_MUSIC_CHECKBOX":
			sHeader = XI_ConvertString("Continuous music");
			sText1 = XI_ConvertString("Continuous music descr");
		break;

		case "CONTINUOUS_MUSIC_JUNGLE_CHECKBOX":
			sHeader = XI_ConvertString("Continuous music") + " " + XI_ConvertString("Continuous music jungle");
		break;

		case "CONTINUOUS_MUSIC_HOUSE_CHECKBOX":
			sHeader = XI_ConvertString("Continuous music") + " " + XI_ConvertString("Continuous music house");
		break;

		case "CONTINUOUS_MUSIC_BROTHEL_CHECKBOX":
			sHeader = XI_ConvertString("Continuous music") + " " + XI_ConvertString("Continuous music brothel");
		break;

		case "CONTINUOUS_MUSIC_SHIP_CHECKBOX":
			sHeader = XI_ConvertString("Continuous music") + " " + XI_ConvertString("Continuous music ship");
		break;

		case "CONTINUOUS_MUSIC_BOARDING_CHECKBOX":
			sHeader = XI_ConvertString("Continuous music") + " " + XI_ConvertString("Continuous music boarding");
		break;

		case "CONTINUOUS_MUSIC_ATTACK_CHECKBOX":
			sHeader = XI_ConvertString("Continuous music") + " " + XI_ConvertString("Continuous music attack");
		break;

		case "CONTINUOUS_MUSIC_LSC_CHECKBOX":
			sHeader = XI_ConvertString("Continuous music") + " " + XI_ConvertString("Continuous music lsc");
		break;
	}

	if (HasStr(sNode, "CONTINUOUS") && !HasStr(sNode, "CONTINUOUS_MUSIC_CHECKBOX"))
	{
		sText1 = XI_ConvertString("Continuous music descr");
		sText2 = XI_ConvertString("NeedTo") + " " + LowerFirst(XI_ConvertString("Continuous music settings"));
	}

	CreateTooltip("#" + sHeader, sText1, argb(255, 255, 255, 255), sText2, argb(255, 255, 192, 192), sText3, argb(255, 255, 255, 255), "", argb(255, 255, 255, 255), sPicture, sGroup, sGroupPicture, 64, 64);
}

void HideInfo()
{
	if (g_bToolTipStarted)
	{
		g_bToolTipStarted = false;
		CloseTooltip();
		SetCurrentNode("OK_BUTTON");
	}
}

bool KeyAlreadyUsed(string sGrpName, string sControl, string sKey)
{
	if (!CheckAttribute(&objControlsState, "keygroups." + sGrpName + "." + sControl))
	{
		return false;
	}
	if (objControlsState.keygroups.(sGrpName).(sControl) == sKey)
	{
		return false;
	}

	bool bAlreadyUsed = false;
	int n, q, i, grp;
	aref arGrp, arCntrl, arGrpList;

	// проверка на совпадение в той же группе
	makearef(arGrp, objControlsState.keygroups.(sGrpName));
	q = GetAttributesNum(arGrp);
	for (n = 0; n < q; n++)
	{
		arCntrl = GetAttributeN(arGrp, n);
		if (GetAttributeValue(arCntrl) == sKey)
		{
			bAlreadyUsed = true;
			break;
		}
	}

	if (bAlreadyUsed)
	{
		return bAlreadyUsed;
	}

	// найдем группу в которой эта контролка также отображается
	makearef(arGrpList, objControlsState.keygroups);
	grp = GetAttributesNum(arGrpList);
	for (i = 0; i < grp; i++)
	{
		arGrp = GetAttributeN(arGrpList, i);
		if (!CheckAttribute(arGrp, sControl))
		{
			continue;
		}

		q = GetAttributesNum(arGrp);
		for (n = 0; n < q; n++)
		{
			arCntrl = GetAttributeN(arGrp, n);
			if (GetAttributeValue(arCntrl) == sKey)
			{
				bAlreadyUsed = true;
				break;
			}
		}
		if (bAlreadyUsed)
		{
			break;
		}
	}

	return bAlreadyUsed;
}

void SetKeyChooseWarning(string sWarningText)
{
	SendMessage(&GameInterface, "lslle", MSG_INTERFACE_MSG_TO_NODE, "CHANGEKEY_TEXT", 10, 4, &sWarningText);
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CHANGEKEY_TEXT", 5);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CHANGEKEY_TEXT", 8, 4, argb(255, 255, 64, 64));
	PostEvent("evFaderFrame", 700, "lll", 500, 0, 50);
}

void FaderFrame()
{
	int nTotalTime = GetEventData();
	int nCurTime = GetEventData();
	int nDeltaTime = GetEventData();

	nCurTime = nCurTime + nDeltaTime;
	if (nCurTime > nTotalTime)
	{
		nCurTime = nTotalTime;
	}

	int nAlpha = 255 * (nTotalTime - nCurTime) / nTotalTime;
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "CHANGEKEY_TEXT", 8, 4, argb(nAlpha, 255, 64, 64));

	if (nCurTime < nTotalTime)
	{
		PostEvent("evFaderFrame", nDeltaTime, "lll", nTotalTime, nCurTime, nDeltaTime);
	}
}

void ChangeHUDDetail()
{
	float sl = stf(GameInterface.nodes.hud_slide.value);
	newBase = CalcHUDBase(sl, stf(Render.screen_y));
	if (newBase != iHUDBase && !bSkipChangeHUD)
	{
		fHUDRatio = stf(Render.screen_y) / newBase;
		SetFormatedText("HUD_DESCRIP_TEXT", XI_ConvertString("HudDescripText") + ": " + Render.screen_y + " / " + newBase + " : " + stf(sti(fHUDRatio * 100)) / 100);
	}
	bSkipChangeHUD = false;
}

string ControlTipsDes()
{
	switch (iShowTips)
	{
		case CONTROL_TIPS_NONE: return XI_ConvertString("Off"); break;
		case CONTROL_TIPS_BASE: return XI_ConvertString("BaseTips"); break;
		case CONTROL_TIPS_EXTEND: return XI_ConvertString("ExtendedTips"); break;
		case CONTROL_TIPS_ALL: return XI_ConvertString("AllTips"); break;
		return " ";
	}
}

string MoreInfoDes()
{
	string sText = " ";
	switch (iMoreInfo)
	{
		case 0: sText =  XI_ConvertString("FightMode"); break;
		case 1: sText =  XI_ConvertString("Always"); break;
	}
	return sText;
}

string FontDes()
{
	string sText = " ";
	switch (iFontType)
	{
		case 0:
			sText =  XI_ConvertString("Font_Italic");
			CreateString(true, "FontTypeText", "", "INTERFACE_TITLE", COLOR_NORMAL, 447, 250, SCRIPT_ALIGN_CENTER, 0.8);
			GameInterface.strings.FontTypeText = sText;
		break;
		case 1:
			sText =  XI_ConvertString("Font_Normal");
			CreateString(true, "FontTypeText", "", "INTERFACE_NORMAL", COLOR_NORMAL, 447, 252, SCRIPT_ALIGN_CENTER, 0.9);
			GameInterface.strings.FontTypeText = sText;
		break;
	}	
	return sText;
}
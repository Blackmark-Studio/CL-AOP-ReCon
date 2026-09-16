#define CONFIRMMODE_PROFILE_DELETE     1
#define CONFIRMMODE_SAVE_DELETE        2
#define CONFIRMMODE_SAVE_OVERWRITE     3
#define CONFIRMMODE_LOAD_GAME          4
#define CONFIRMMODE_BAD_SAVE           5

#define SAVEIMAGE_UPDATE_TIME    50

bool bThisSave;
bool bIsGameProcessNow;
aref scrshot;
object emptyscrshot;

int g_nLablesFileID = -1;
int g_nInterfaceFileID = -1;
string currentProfile;
string sSaveVersion;

int g_nCurrentSaveIndex = 0;
int g_nFirstSaveIndex = -1;
int g_nSaveQuantity = 0;

// теперь слоты убраны на строки под современный формат
#define MAX_SAVE_SLOTS					7 // количество слотов
#define SLOTS_IN_LINE					1 // количество слотов в строке
#define LINE_COUNT						7 // количество строк

// KZ > кэширование физически прочитанных сейвов с диска.
// Движок прекрасно кэширует сейвы, но прежний код здесь сразу слал MSG_SCRSHOT_RELEASE после каждого чтения, поэтому при любой прокрутке тот же файл читался с диска заново.
// Теперь каждый сейв (лимит задаётся в SAVE_CACHE_LIMIT) читается с диска ОДИН раз, кэшируется в g_oSaveCache и берётся оттуда при повторных показах на экране. Процедура повторяется при любых физических манипуляциях с сейвами (удаление, смена профиля).
object g_oSaveList[MAX_SAVE_SLOTS];
object g_oSaveContainer;

// > Кол-во файлов сейвов для кэширования. При переполнении самая старая запись вытесняется.
#define SAVE_CACHE_LIMIT 128

// > Сколько файлов сейвов предварительно загружать при открытии интерфейса. Не рекомендуется задавать выше SAVE_CACHE_LIMIT, иначе лишние сразу вытеснятся.
#define SAVE_CACHE_PREFETCH 35

object g_oSaveCache;			// > собственно, кэш
int    g_nSaveCacheNum  = 0;	// > сколько записей реально занято
int    g_nSaveCacheNext = 0;	// > позиция следующей записи

int g_nConfirmMode;
string g_sConfirmReturnWindow;
bool isMainMenuChecker = false;

void InitInterface_BB(string iniName, bool isSave, bool isMainMenu)
{
	if (CheckAttribute(&PlayerProfile, "name"))
	{
		PlayerProfile.old_name = PlayerProfile.name;
	}

	isMainMenuChecker = isMainMenu;
	bThisSave = isSave;
	bIsGameProcessNow = true;
	sSaveVersion = "";

	if (bThisSave) GameInterface.title = "titleSave";
	else GameInterface.title = "titleLoad";

	g_nLablesFileID = LanguageOpenFile("LocLables.txt");
	g_nInterfaceFileID = LanguageOpenFile("interface_strings.txt");

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);

	if (bThisSave)
	{
		SetSelectable("BTN_PROFILE", false);
		SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "BTN_SAVELOAD", 0, "Save");
	}

	FillProfileList();
	FindScrshotClass();
	InitSaveObjList();
	ClearSaveCache(); // > сброс кэша при входе в интерфейс

	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("eventBtnAction", "procBtnAction", 0);
	SetEventHandler("eventSelecterActivate", "procSelecterActivate", 0);
	SetEventHandler("eventSelecterMove", "procSelecterMove", 0);
	SetEventHandler("eventSaveClick", "procSaveClick", 0);
	SetEventHandler("evLoadOneSaveInfo", "procLoadOneSaveInfo", 0);
	SetEventHandler("eProfileBtnAction", "procProfileBtnAction", 0);
	SetEventHandler("eventConfirm", "procConfirm", 0);
	SetEventHandler("ScrollPosChange", "ScrollPosChange", 0);
	SetEventHandler("LoadProfile", "LoadProfile", 0);
	SetEventHandler("SaveLoad", "SaveLoad", 0);
	SetEventHandler("eventSaveCustom", "ProcessCustomSaveAction", 0);

	PostEvent("evLoadOneSaveInfo", 1);

	if (isSave == false && GetLastProfileFromCurrentProfile() == "" && sti(PlayerProfile.profilesQuantity) > 1)
	{
		FillSaveList(0);
		ProcChooseProfileFromList();
	}
	else
	{
		SetCurrentProfile(GetCurrentProfile());
	}
}

void SetCurrentProfile(string sProfileName)
{
	ClearSaveCache(); // > сброс кэша - у другого профиля другие файлы (и возможны одноимённые названия)
	currentProfile = sProfileName;
	PlayerProfile.name = sProfileName;
	// fill save list
	DeleteAttribute(&g_oSaveContainer, "");
	int nSaveNum = 0;
	string saveName;
	int nSaveSize;
	string attr;
	GameInterface.SavePath = "SAVE\\" + currentProfile;

	while(SendMessage(&GameInterface, "llee", MSG_INTERFACE_SAVE_FILE_FIND, nSaveNum, &saveName, &nSaveSize) != 0)
	{
		attr = "s" + nSaveNum;
		g_oSaveContainer.(attr).savename = saveName;
		g_oSaveContainer.(attr).savesize = nSaveSize;
		nSaveNum++;
	}
	g_oSaveContainer.listsize = nSaveNum;
	g_nSaveQuantity = nSaveNum;
	g_nFirstSaveIndex = -1;
	g_nCurrentSaveIndex = 0; // > сброс при смене профиля, иначе оставался индекс прошлого
	PreloadSaveCache(); // > префетч сейвов в кэш ДО первой отрисовки списка; видимые слоты сразу из кэша
	FillSaveList((g_nCurrentSaveIndex / MAX_SAVE_SLOTS) * MAX_SAVE_SLOTS);
	if (!bThisSave) SelectSaveImage(0);
	SetClickable("SAVESCROLL", g_nSaveQuantity > MAX_SAVE_SLOTS);
	// show profile name
	string profNameText = "#" + XI_ConvertString("ProfileName") + ": " + currentProfile;
	int textWidth = GetStringWidth(profNameText, "interface_button", 0.95);
	int iconOffset = -3;
	int i = 1;
	while (textWidth > 200)
	{
	    profNameText = strcut(profNameText, 0, strlen(profNameText)-(1+i));
	    textWidth = GetStringWidth(profNameText, "interface_button", 0.95);
	    i++;
	}
	if (i > 1)
	{
	    profNameText += "...";
	    iconOffset = 0;
	}
	SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "SAVEINFO", 1, 1, profNameText);
	// set icon pos
	float foffsetX, foffsetY;
	GetXYWindowOffset(&foffsetX, &foffsetY);

	int posLeft = 771+makeint(foffsetX + textWidth * 0.5) + iconOffset;
	SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "PROFILE_PIC", 0, posLeft,170+makeint(foffsetY),posLeft + 20,190+makeint(foffsetY));
	SSI("1000");
}

void ProcessCancelExit()
{
	DelEventHandler("ScrollPosChange", "ScrollPosChange");
	DelEventHandler("eventConfirm", "procConfirm");
	DelEventHandler("evLoadOneSaveInfo", "procLoadOneSaveInfo");
	DelEventHandler("eProfileBtnAction", "procProfileBtnAction");
	DelEventHandler("eventSaveClick", "procSaveClick");
	DelEventHandler("eventSelecterActivate", "procSelecterActivate");
	DelEventHandler("eventSelecterMove", "procSelecterMove");
	DelEventHandler("eventBtnAction", "procBtnAction");
	DelEventHandler("exitCancel", "ProcessCancelExit");
	DelEventHandler("LoadProfile", "LoadProfile");
	DelEventHandler("SaveLoad", "SaveLoad");
	DelEventHandler("eventSaveCustom", "ProcessCustomSaveAction");

	if (CheckAttribute(&PlayerProfile, "old_name"))
	{
		PlayerProfile.name = PlayerProfile.old_name;
	}

	if (CheckAttribute(&InterfaceStates, "showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
	{
		// Warship Fix свечения
		if (CheckAttribute(&InterfaceStates, "GlowEffect"))
		{
			SetGlowParams(1.0, sti(InterfaceStates.GlowEffect), 2);
		}

		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
		return;
	}

	IDoExit(RC_INTERFACE_SAVELOAD_EXIT);

	if (!CheckAttribute(&InterfaceStates, "InstantExit") || sti(InterfaceStates.InstantExit) == false)
	{
		ReturnToMainMenu();
	}
}

void IDoExit(int exitCode)
{
	DeleteAttribute(&PlayerProfile, "old_name");

	GameInterface.SavePath = "SAVE";

	ClearSaveCache(); // > сброс кэша при выходе из интерфейса

	if (g_nLablesFileID != -1)
	{
		LanguageCloseFile(g_nLablesFileID);
		g_nLablesFileID = -1;
	}
	if (g_nInterfaceFileID != -1)
	{
		LanguageCloseFile(g_nInterfaceFileID);
		g_nInterfaceFileID = -1;
	}

	interfaceResultCommand = exitCode;
	if (CheckAttribute(&InterfaceStates, "InstantExit") && sti(InterfaceStates.InstantExit) == true)
	{
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}

void FindScrshotClass()
{
	if (!GetEntity(&scrshot, "scrshoter"))
	{
		makearef(scrshot, emptyscrshot);
	}
}

string GetCurrentProfile()
{
	if (CheckAttribute(&PlayerProfile, "name") && PlayerProfile.name != "")
	{
		return PlayerProfile.name;
	}
	trace("error (save_load.c) : PlayerProfile.name attribute not found.");

	object FolderList;
	XI_FindFoldersWithoutNetsave("SAVE" + "\*", &FolderList);

	int num = GetAttributesNum(&FolderList);
	if (num > 0)
		return GetAttributeValue(GetAttributeN(&FolderList, num - 1));
	return "";
}

void FillProfileList()
{
	PlayerProfile.profilesQuantity = 0;

	object FolderList;
	XI_FindFoldersWithoutNetsave("SAVE\*", &FolderList);

	int num = GetAttributesNum(&FolderList);
	string folderName;

	int i = 0;
	string attr;
	for (i = 0; i < num; i++) {
		attr = "profile_" + i;
		PlayerProfile.(attr) = GetAttributeValue(GetAttributeN(&FolderList, i));
	}

	PlayerProfile.profilesQuantity = num;
}

void procSelecterActivate()
{
	SaveLoadCurrentIntoSlot();
}

void procBtnAction()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if (iComIndex == ACTION_RIGHTSTEP)
	{
		if (sNodName == "BTN_PROFILE")
		{
			if (GetSelectable("BTN_SAVELOAD"))
			{
				SetCurrentNode("BTN_SAVELOAD");
			}
			else
			{
				sNodName = "BTN_SAVELOAD";
			}
		}
		if (sNodName == "BTN_SAVELOAD")
		{
			if (GetSelectable("BTN_DELETE"))
			{
				SetCurrentNode("BTN_DELETE");
			}
			else
			{
				sNodName = "BTN_DELETE";
			}
		}
		if (sNodName == "BTN_DELETE")
		{
			SetCurrentNode("BTN_EXIT");
		}
		return;
	}

	if (iComIndex == ACTION_LEFTSTEP)
	{
		if (sNodName == "BTN_EXIT")
		{
			if (GetSelectable("BTN_DELETE"))
			{
				SetCurrentNode("BTN_DELETE");
			}
			else
			{
				sNodName = "BTN_DELETE";
			}
		}
		if (sNodName == "BTN_DELETE")
		{
			if (GetSelectable("BTN_SAVELOAD"))
			{
				SetCurrentNode("BTN_SAVELOAD");
			}
			else
			{
				sNodName = "BTN_SAVELOAD";
			}
		}
		if (sNodName == "BTN_SAVELOAD" && !bThisSave)
		{
			SetCurrentNode("BTN_PROFILE");
		}
		return;
	}

	if (iComIndex == ACTION_ACTIVATE || iComIndex == ACTION_MOUSECLICK)
	{
		if (sNodName == "BTN_PROFILE")
		{
			ProcChooseProfileFromList();
		}
		if (sNodName == "BTN_SAVELOAD")
		{
			SaveLoadCurrentIntoSlot();
		}
		if (sNodName == "BTN_DELETE")
		{
			DoConfirm(CONFIRMMODE_SAVE_DELETE);
		}
	}
}

void SaveLoadCurrentIntoSlot()
{
	if (bThisSave)
	{
		// запись
		if (GetCurSaveName() == "")
		{
			// не перезапись старого файла
			ProcessSave();
		}
		else
		{
			DoConfirm(CONFIRMMODE_SAVE_OVERWRITE);
		}
	}
	else
	{
		// чтение
		if (g_nCurrentSaveIndex < 0 || g_nCurrentSaveIndex >= g_nSaveQuantity)
		{
			// нет такой ячейки с записью
			return;
		}
		int nSlot = g_nCurrentSaveIndex - g_nFirstSaveIndex;
		if (nSlot < 0 || nSlot >= MAX_SAVE_SLOTS)
			return;
		// > грузим только полностью прочитанный корректный сейв
		if (!GetSelectable("SAVEIMG" + (nSlot + 1)))
			return;
		if (!IsActualSaveVersion(&g_oSaveList[nSlot]))
		{
			DoConfirm(CONFIRMMODE_BAD_SAVE);
		}
		else if (bIsGameProcessNow)
		{
			// в данный момент уже идет игра?
			DoConfirm(CONFIRMMODE_LOAD_GAME);
		}
		else
		{
			ProcessLoad();
		}
	}
}

void ProcChooseProfileFromList()
{
	// disable all windows
	XI_WindowDisable("MAIN_WINDOW", true);
	// enable profile window
	XI_WindowDisable("PROFILE_WINDOW", false);
	XI_WindowShow("PROFILE_WINDOW", true);
	// set current node to profile list
	FillProfileListIntoTable();
	SetCurrentNode("PROFILE_WINDOW_LIST");
}

void FillProfileListIntoTable()
{
	// Fill Profile List
	int n, q, nSel;
	string src_attr, dst_attr, sCurProfile;
	q = sti(PlayerProfile.profilesQuantity);
	nSel = 1;
	if (CheckAttribute(&PlayerProfile, "name"))
	{
		sCurProfile = PlayerProfile.name;
	}
	else
	{
		sCurProfile = "";
	}
	DeleteAttribute(&GameInterface, "profile_window_list");
	for (n = 0; n < q; n++)
	{
		src_attr = "profile_" + n;
		dst_attr = "tr" + (n + 1);
		GameInterface.profile_window_list.(dst_attr).td1.str = PlayerProfile.(src_attr);
		if (PlayerProfile.(src_attr) == sCurProfile)
		{
			nSel = n + 1;
		}
	}
	GameInterface.profile_window_list.select = nSel;
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "PROFILE_WINDOW_LIST", 0);
}

void ProcExitProfile()
{
	// disable all windows
	XI_WindowShow("PROFILE_WINDOW", false);
	// enable main window
	XI_WindowDisable("MAIN_WINDOW", false);
	// set current node to button for start profile choosing
	SetCurrentNode("BTN_PROFILE");
}

void ProcChooseProfile()
{
	string attr = "profile_" + (sti(GameInterface.profile_window_list.select) - 1);
	if (CheckAttribute(&PlayerProfile, attr))
	{
		SetCurrentProfile(PlayerProfile.(attr));
	}

	ProcExitProfile();
}

void ProcDeleteProfile()
{
	int nProfileIdx = sti(GameInterface.profile_window_list.select) - 1;
	// deleting process:
	string attr = "profile_" + nProfileIdx;
	string sThisProfile = PlayerProfile.(attr);
	DeleteProfile(PlayerProfile.(attr));

	// shifting profile list
	int nProfilesQ = sti(PlayerProfile.profilesQuantity);
	nProfilesQ--;
	string attrSrc, attrDst;
	for (int n = nProfileIdx; n < nProfilesQ; n++)
	{
		attrDst = "profile_" + n;
		attrSrc = "profile_" + (n + 1);
		PlayerProfile.(attrDst) = PlayerProfile.(attrSrc);
	}
	DeleteAttribute(&PlayerProfile, "profile_" + nProfilesQ);
	PlayerProfile.profilesQuantity = nProfilesQ;
	FillProfileListIntoTable();

	if (sThisProfile == currentProfile)
	{
		SetCurrentProfile("");
	}
}

void DeleteProfile(string profileName)
{
	string oldpath = "";

	// Warship 08.07.09 fix - ошибка из-за отсутствия атрибута
	if (CheckAttribute(&GameInterface, "SavePath"))
	{
		oldpath = GameInterface.SavePath;
	}

	GameInterface.SavePath = "SAVE\" + profileName;
	// deleting all files from profile folder
	int nSaveNum= 0;
	string saveName;
	int nSaveSize;
	while(SendMessage(&GameInterface, "llee", MSG_INTERFACE_SAVE_FILE_FIND, nSaveNum, &saveName, &nSaveSize) != 0)
	{
		nSaveNum++;
		SendMessage(&GameInterface, "ls", MSG_INTERFACE_DELETE_SAVE_FILE, saveName);
	}
	XI_DeleteFolder(GameInterface.SavePath);
	GameInterface.SavePath = oldpath;
}

void procSelecterMove()
{
	int iComIndex = GetEventData();

	int nLeft, nTop, nRight, nBottom;
	bool bMakeMove = false;

	switch (iComIndex)
	{
		case ACTION_RIGHTSTEP:
			bMakeMove = GetMoveToOtherSave(g_nCurrentSaveIndex + 1, &nLeft, &nTop, &nRight, &nBottom);
		break;
		case ACTION_LEFTSTEP:
			bMakeMove = GetMoveToOtherSave(g_nCurrentSaveIndex - 1, &nLeft, &nTop, &nRight, &nBottom);
		break;
		case ACTION_UPSTEP:
			bMakeMove = GetMoveToOtherSave(g_nCurrentSaveIndex - SLOTS_IN_LINE, &nLeft, &nTop, &nRight, &nBottom);
		break;
		case ACTION_DOWNSTEP:
			bMakeMove = GetMoveToOtherSave(g_nCurrentSaveIndex + SLOTS_IN_LINE, &nLeft, &nTop, &nRight, &nBottom);
		break;
	}

	if (bMakeMove)
	{
		SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "SAVE_SELECTER", 0, nLeft, nTop, nRight, nBottom);
	}

	if (g_nSaveQuantity > SLOTS_IN_LINE)
	{
		int nLineQ = g_nSaveQuantity / SLOTS_IN_LINE;
		int nLineCur = (g_nCurrentSaveIndex) / SLOTS_IN_LINE;

		SendMessage(&GameInterface, "lsf", MSG_INTERFACE_SET_SCROLLER, "SAVESCROLL", makefloat(nLineCur) / makefloat(nLineQ));
	}
}

void SetSelecting(int nSlot, bool bSelect)
{
	string sNodeName;
	int nColor;
	sNodeName = "SAVEIMG" + (nSlot + 1);
	if (bSelect)
	{
		nColor = argb(255, 255, 255, 255);
	}
	else
	{
		nColor = argb(255, 148, 148, 148);
	}
	if (!IsActualSaveVersion(&g_oSaveList[nSlot]))
	{
		if (bSelect) nColor = argb(255, 204, 0, 0);
		else nColor = argb(255, 102, 0, 0);
	}
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 5, bSelect);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 3, nSlot * 3 + 1, nColor);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 3, nSlot * 3 + 2, nColor);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 3, nSlot * 3 + 3, nColor);
}

// > Есть ли на этой позиции селектора реальный сейв (в режиме записи - слот нового сохранения)
bool IsRealSaveIndex(int nIndex)
{
	if (nIndex < 0) return false;
	if (bThisSave && nIndex == 0) return true; // > слот нового сохранения всегда доступен
	int nContainerIdx = nIndex;
	if (bThisSave) nContainerIdx -= 1;
	return CheckAttribute(&g_oSaveContainer, "s" + nContainerIdx + ".savename");
}

bool GetMoveToOtherSave(int nNewSaveIndex, ref rLeft, ref rTop, ref rRight, ref rBottom)
{
	if (nNewSaveIndex < 0) return false;
	if (g_nCurrentSaveIndex == nNewSaveIndex) return false;

	int nMaxQ = (g_nSaveQuantity + makeint(SLOTS_IN_LINE - 1)) / SLOTS_IN_LINE * SLOTS_IN_LINE + SLOTS_IN_LINE;
	if (nNewSaveIndex > nMaxQ) return false;

	int nOldIdx = g_nCurrentSaveIndex - g_nFirstSaveIndex;
	int nNewIdx = nNewSaveIndex - g_nFirstSaveIndex;

	if (nNewIdx < 0)
	{
		if (g_nFirstSaveIndex > 0)
		{
			FillSaveList(g_nFirstSaveIndex - SLOTS_IN_LINE);
		}
		nNewIdx = nNewSaveIndex - g_nFirstSaveIndex;
	}
	else if (nNewIdx > makeint(MAX_SAVE_SLOTS - 1))
	{
		FillSaveList(g_nFirstSaveIndex + SLOTS_IN_LINE);
		nNewIdx = nNewSaveIndex - g_nFirstSaveIndex;
	}

	// > Скорость прокрутки вниз теперь равна скорости прокрутки вверх: двигаемся по факту наличия реального сейва, а не по готовности эскиза
	if (nNewIdx > 0 && !IsRealSaveIndex(nNewSaveIndex))
	{
		nNewIdx = g_nCurrentSaveIndex - g_nFirstSaveIndex;
		nNewSaveIndex = g_nCurrentSaveIndex;
		if (nNewIdx == nOldIdx)
		{
			ReloadSaveInfo();
			return false; // нельзя перейти на новый элемент (на первый всегда можно)
		}
	}

	// старое немигает новое подмигивает & старый текст серый новый выделенный - светлый
	if (g_nCurrentSaveIndex >= 0 && nOldIdx >= 0 && nOldIdx < MAX_SAVE_SLOTS)
	{
		SetSelecting(nOldIdx, false);
	}
	SetSelecting(nNewIdx, true);

	g_nCurrentSaveIndex = nNewSaveIndex;
	ReloadSaveInfo();

	int nLeft = 469;
	int nTop = 70 + 60 * nNewIdx;
	int nRight = 575;
	int nBottom = 126 + 60 * nNewIdx;

	rLeft = nLeft;
	rTop = nTop;
	rRight = nRight;
	rBottom = nBottom;
	return true;
}

void procSaveClick()
{
	int i, iComIdx = GetEventData();
	string sNodName = GetEventData();

	for (i = 0; i < MAX_SAVE_SLOTS; i++)
	{
		if (sNodName == ("SAVEIMG" + (i + 1)))
		{
			SelectSaveImage(g_nFirstSaveIndex + i);
			return;
		}
		if (sNodName == ("SAVEBUTTON" + (i + 1)))
		{
			SelectSaveImage(g_nFirstSaveIndex + i);
			return;
		}
	}
}

void SelectSaveImage(int nSaveIndex)
{
	int nLeft, nTop, nRight, nBottom;
	bool bMakeMove = GetMoveToOtherSave(nSaveIndex, &nLeft, &nTop, &nRight, &nBottom);
	if (bMakeMove)
	{
		SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "SAVE_SELECTER", 0, nLeft, nTop, nRight, nBottom);
	}
	SetCurrentNode("SAVE_SELECTER");
}

void FillSaveList(int nFirstSaveIndex)
{
	if (nFirstSaveIndex < 0) nFirstSaveIndex = 0;
	nFirstSaveIndex = nFirstSaveIndex / SLOTS_IN_LINE;
	nFirstSaveIndex = nFirstSaveIndex * SLOTS_IN_LINE;

	bool bNoRebuildSaveList = g_nFirstSaveIndex >= 0;
	int nDelta = nFirstSaveIndex - g_nFirstSaveIndex;
	g_nFirstSaveIndex = nFirstSaveIndex;

	int i, d;

	// KZ > кешируем, не шуршим диск, если не нужно
	if (bNoRebuildSaveList && nDelta != 0 && abs(nDelta) < MAX_SAVE_SLOTS)
	{
		if (nDelta > 0)
		{
			// > прокрутка вниз, слоты уезжают вверх, а новые появляются снизу
			for (i = 0; i < MAX_SAVE_SLOTS - nDelta; i++)
				MoveSaveInfo(i + nDelta, i);			// > перенос кэша вверх
			for (i = MAX_SAVE_SLOTS - nDelta; i < MAX_SAVE_SLOTS; i++)
				FillSaveLine(i, nFirstSaveIndex + i);	// > читаются только новые нижние слоты
		}
		else
		{
			// > прокрутка вверх, слоты уезжают вниз, а новые появляются сверху
			d = -nDelta;
			for (i = MAX_SAVE_SLOTS - 1; i >= d; i--)
				MoveSaveInfo(i - d, i);					// > перенос кэша вниз
			for (i = 0; i < d; i++)
				FillSaveLine(i, nFirstSaveIndex + i);	// > читаются только новые нижние слоты
		}
	}
	else
	{
		for (i = 0; i < LINE_COUNT; i++)
			FillSaveLine(i, nFirstSaveIndex + (SLOTS_IN_LINE * i));
	}

	ReloadSaveInfo();
}

void FillSaveLine(int nLine, int nBegIndex)
{
	int nBeg = nLine * SLOTS_IN_LINE;
	int i, n;
	string attr;
	if (bThisSave) nBegIndex -= 1;
	for (i = 0; i < SLOTS_IN_LINE; i++)
	{
		n = nBegIndex + i;
		attr = "s" + n;
		if (CheckAttribute(&g_oSaveContainer, attr))
		{
			LoadInfo(nBeg + i, n, g_oSaveContainer.(attr).savename);
		}
		else
		{
			FillEmptySaveSlot(nBeg + i);
		}
	}
}

void FillEmptySaveSlot(int nSlot)
{
	ClearSaveInfoByIndex(nSlot);
	g_oSaveList[nSlot].saveidx = -1;
	g_oSaveList[nSlot].savefile = "";
	g_oSaveList[nSlot].loaded = 1;
	ShowDataForSave(nSlot, "empty", 0, "");
}

void ShowDataForSave(int nSlot, string picname, int picpointer, string strdata)
{
	string nodname = "SAVEIMG" + (nSlot + 1);
	bool bClickable = bThisSave;
	if (picname != "")
	{
		if (picname == "empty")
		{
			SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, nodname, 2, 0, "interfaces\SaveIcons\SaveEmpty.tga");
		}
		if (picname == "loading")
		{
			SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, nodname, 2, 0, "interfaces\SaveIcons\SaveLoading.tga");
		}
		if (picname == "corrupted")
		{
			SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, nodname, 2, 0, "interfaces\SaveIcons\SaveCorrupted.tga");
		}
	}
	if (picpointer != 0)
	{
		SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, nodname, 7, picpointer);
		bClickable = true;
	}
	SetSelectable(nodname, bClickable);

	string fileSystemTime = "";
	string fileSystemDate = "";
	string sSystemTimeString = "No Time";
	if (CheckAttribute(&g_oSaveList[nSlot], "savefile") && g_oSaveList[nSlot].savefile != "") //fix boal
	{
		SendMessage(&GameInterface, "lsee", MSG_INTERFACE_GETTIME, "SAVE\" + currentProfile + "\" + g_oSaveList[nSlot].savefile, &fileSystemTime, &fileSystemDate);
		sSystemTimeString = GetSystemTimeString(fileSystemTime, fileSystemDate);
	}
	SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 1, nSlot * 3 + 3, "#" + sSystemTimeString);

	if (strdata != "")
	{
		string facestr, locName, timeStr, language, playtime, curship, saveVer;
		if (ParseSaveData(strdata, &facestr, &locName, &timeStr, &language, &playtime, &curship, &saveVer))
		{
			int iLen = 30;
			if (strlen(locName) > iLen)
			{
				locName = strcut(locName, 0, iLen) + "...";
			}
			SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 1, nSlot * 3 + 1, "#" + locName);
			SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 1, nSlot * 3 + 2, "#" + timeStr);
			g_oSaveList[nSlot].faceinfo = facestr;
			g_oSaveList[nSlot].playtime = playtime;
			g_oSaveList[nSlot].curship = curship;
			g_oSaveList[nSlot].saveVer = saveVer;
			g_oSaveList[nSlot].hasdata = 1;
		}
		else
		{
			SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 1, nSlot * 3 + 1, "#Unknown");
			SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 1, nSlot * 3 + 2, "#No Time");
			g_oSaveList[nSlot].faceinfo = "";
			g_oSaveList[nSlot].playtime = "";
			g_oSaveList[nSlot].saveVer = "";
			g_oSaveList[nSlot].hasdata = 1;
		}
	}
	else
	{
		SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 1, nSlot * 3 + 1, "#Unknown");
		SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 1, nSlot * 3 + 2, "#No Time");
		g_oSaveList[nSlot].faceinfo = "";
		g_oSaveList[nSlot].playtime = "";
		g_oSaveList[nSlot].saveVer = "";
		g_oSaveList[nSlot].hasdata = 0;
	}
	if (nSlot == 0)
		SetSelecting(nSlot, true);
	else
		SetSelecting(nSlot, false);

	if ((g_nCurrentSaveIndex - g_nFirstSaveIndex) == nSlot)
	{
		ReloadSaveInfo();
	}
}

string GetSystemTimeString(string systemTime, string systemDate)
{
	return systemTime + " " + systemDate;
}

void InitSaveObjList()
{
	int i;
	for (i = 0; i < MAX_SAVE_SLOTS; i++)
	{
		g_oSaveList[i].saveidx = -1;
	}
}

void ClearSaveInfoByIndex(int i)
{
	if (g_oSaveList[i].saveidx == -1)
	{
		return;
	}
	DeleteAttribute(&g_oSaveList[i], "");
	g_oSaveList[i].saveidx = -1;
}

void MoveSaveInfo(int nSrc, int nDst)
{
	CopyAttributes(&g_oSaveList[nDst], &g_oSaveList[nSrc]);
	DeleteAttribute(&g_oSaveList[nSrc], "");
	g_oSaveList[nSrc].saveidx = -1;

	// copy info from src control to dst control
	string sDstImgNod = "SAVEIMG" + (nDst + 1);
	string sSrcImgNod = "SAVEIMG" + (nSrc + 1);
	SetSelectable(sDstImgNod, GetSelectable(sSrcImgNod));
	SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sDstImgNod, 8, sSrcImgNod);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 2, nDst * 3 + 1, nSrc * 3 + 1);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 2, nDst * 3 + 2, nSrc * 3 + 2);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "SAVENOTES", 2, nDst * 3 + 3, nSrc * 3 + 3);
	SetSelecting(nDst, false);
	// set src control to empty
	ShowDataForSave(nSrc, "empty", 0, "");
}

void LoadInfo(int nInfoIdx, int nSaveIdx, string sSaveName)
{
	// > в слоте уже показан ровно этот же сейв и он загружен - ничего не перечитываем
	if (sti(g_oSaveList[nInfoIdx].saveidx) == nSaveIdx && CheckAttribute(&g_oSaveList[nInfoIdx], "savefile") && g_oSaveList[nInfoIdx].savefile == sSaveName && CheckAttribute(&g_oSaveList[nInfoIdx], "loaded") && g_oSaveList[nInfoIdx].loaded == "1")
		return;

	ClearSaveInfoByIndex(nInfoIdx);
	g_oSaveList[nInfoIdx].saveidx = nSaveIdx;
	g_oSaveList[nInfoIdx].savefile = sSaveName;

	// > этот сейв уже читали раньше, берём его из кэша и не шуршим диском
	if (TryShowSaveFromCache(nInfoIdx, sSaveName))
		return;

	g_oSaveList[nInfoIdx].loaded = 0;
	ShowDataForSave(nInfoIdx, "loading", 0, "");
}

// KZ > кэш прочитанных сейвов
// > Ищет сейв в кэше по имени файла, возвращает индекс записи или -1
int CacheFindSave(string sFile)
{
	int k;
	string sAttr;

	for (k = 0; k < g_nSaveCacheNum; k++)
	{
		sAttr = "e" + k;

		if (CheckAttribute(&g_oSaveCache, sAttr + ".file") && g_oSaveCache.(sAttr).file == sFile)
			return k;
	}

	return -1;
}

// > Заносит сейв в кэш (при переполнении вытесняется самая старая запись)
void CacheStoreSave(string sFile, string sStrData, int nTex, bool bCorrupted)
{
	int k = CacheFindSave(sFile);
	string sAttr;

	// > уже в кэше, просто обновим данные на месте
	if (k >= 0)
	{
		sAttr = "e" + k;
		g_oSaveCache.(sAttr).strdata   = sStrData;
		g_oSaveCache.(sAttr).tex       = nTex;
		g_oSaveCache.(sAttr).corrupted = bCorrupted;
		return;
	}

	// > новая запись запишется в текущую позицию
	k = g_nSaveCacheNext;
	sAttr = "e" + k;

	// > весь кэш забит, начинаем вытеснять старые записи
	if (CheckAttribute(&g_oSaveCache, sAttr + ".file"))
	{
		if (IsEntity(&scrshot) && sti(g_oSaveCache.(sAttr).corrupted) == 0)
			SendMessage(scrshot, "ls", MSG_SCRSHOT_RELEASE, g_oSaveCache.(sAttr).file);
	}

	g_oSaveCache.(sAttr).file      = sFile;
	g_oSaveCache.(sAttr).strdata   = sStrData;
	g_oSaveCache.(sAttr).tex       = nTex;
	g_oSaveCache.(sAttr).corrupted = bCorrupted;

	g_nSaveCacheNext = g_nSaveCacheNext + 1;

	if (g_nSaveCacheNext >= SAVE_CACHE_LIMIT)
		g_nSaveCacheNext = 0;

	if (g_nSaveCacheNum < SAVE_CACHE_LIMIT)
		g_nSaveCacheNum++;
}

// > Показ сейва из кэша БЕЗ обращения к диску (true - показан, false - нет в кэше)
bool TryShowSaveFromCache(int nSlot, string sFile)
{
	int k = CacheFindSave(sFile);

	if (k < 0)
		return false;

	string sAttr = "e" + k;
	g_oSaveList[nSlot].loaded = 1;

	if (sti(g_oSaveCache.(sAttr).corrupted) != 0)
		ShowDataForSave(nSlot, "corrupted", 0, "");
	else
		ShowDataForSave(nSlot, "", sti(g_oSaveCache.(sAttr).tex), g_oSaveCache.(sAttr).strdata);

	return true;
}

// > Убирает из кэша только один сейв по имени файла и освобождает его эскиз
void CacheRemoveSave(string sFile)
{
	int k = CacheFindSave(sFile);

	if (k < 0) return;

	string sAttr = "e" + k;

	// > превьюшку релизим только у нормальных сейвов (у битых её нет)
	if (IsEntity(&scrshot) && sti(g_oSaveCache.(sAttr).corrupted) == 0)
		SendMessage(scrshot, "ls", MSG_SCRSHOT_RELEASE, g_oSaveCache.(sAttr).file);

	// > освобождаем запись
	DeleteAttribute(&g_oSaveCache, sAttr);
}

// > Полная очистка кэша + освобождение всех удерживаемых текстур эскизов.
void ClearSaveCache()
{
	if (IsEntity(&scrshot))
	{
		int k;
		string sAttr;

		for (k = 0; k < g_nSaveCacheNum; k++)
		{
			sAttr = "e" + k;

			// > превьюшку релизим только у нормальных сейвов (у битых её нет)
			if (CheckAttribute(&g_oSaveCache, sAttr + ".file") && sti(g_oSaveCache.(sAttr).corrupted) == 0)
				SendMessage(scrshot, "ls", MSG_SCRSHOT_RELEASE, g_oSaveCache.(sAttr).file);
		}
	}

	DeleteAttribute(&g_oSaveCache, "");
	g_nSaveCacheNum  = 0;
	g_nSaveCacheNext = 0;
}

// > Префетч: при открытии интерфейса читаем с диска первые SAVE_CACHE_PREFETCH сейвов и кладём их в кэш, чтобы прокрутка списка шла плавно, без постоянных обращений к диску.
void PreloadSaveCache()
{
	if (!IsEntity(&scrshot))
		return; // > без скриншотера читать нечего

	int iCount = g_nSaveQuantity;

	if (iCount > SAVE_CACHE_PREFETCH)
		iCount = SAVE_CACHE_PREFETCH;

	int n, pTex;
	string attr, sFile, strdata;
	for (n = 0; n < iCount; n++)
	{
		attr = "s" + n;

		if (!CheckAttribute(&g_oSaveContainer, attr + ".savename")) continue;

		sFile = g_oSaveContainer.(attr).savename;

		strdata = "";
		pTex = SendMessage(scrshot, "lsse", MSG_SCRSHOT_READ, "SAVE\\" + currentProfile, sFile, &strdata);

		if (strdata == "")
		{
			CacheStoreSave(sFile, "", 0, true);
			SendMessage(scrshot, "ls", MSG_SCRSHOT_RELEASE, sFile); // > битый, текстуру не держим
		}
		else
			CacheStoreSave(sFile, strdata, pTex, false); // > текстуру НЕ освобождаем, нужна для эскиза
	}
}
// KZ < кэш прочитанных сейвов

void procLoadOneSaveInfo()
{
	int i;
	int pTex;
	string strdata;
	bool bYesScrShoter = IsEntity(&scrshot);
	for (i = 0; i < MAX_SAVE_SLOTS; i++)
	{
		if (g_oSaveList[i].saveidx != "-1")
		{
			if (!CheckAttribute(&g_oSaveList[i], "loaded") || g_oSaveList[i].loaded == "0")
			{
				g_oSaveList[i].loaded = 1;
				strdata = "";
				pTex = 0;
				if (bYesScrShoter)
				{
					pTex = SendMessage(scrshot, "lsse", MSG_SCRSHOT_READ, "SAVE\\" + currentProfile, g_oSaveList[i].savefile, &strdata);
				}
				if (strdata == "")
				{
					ShowDataForSave(i, "corrupted", 0, "");

					// > запоминаем "битый", чтобы не читать его с диска повторно; его текстуру держать незачем
					CacheStoreSave(g_oSaveList[i].savefile, "", 0, true);

					if (bYesScrShoter)
						SendMessage(scrshot, "ls", MSG_SCRSHOT_RELEASE, g_oSaveList[i].savefile);
				}
				else
				{
					ShowDataForSave(i, "", pTex, strdata);

					// > кладём в кэш; RELEASE НЕ шлём, т.к., текстура эскиза нужна для повторных показов
					CacheStoreSave(g_oSaveList[i].savefile, strdata, pTex, false);
				}
				// только один сейф файл за раз
				break;
			}
		}
	}
	PostEvent("evLoadOneSaveInfo", SAVEIMAGE_UPDATE_TIME);
}

void procProfileBtnAction()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if (XI_IsWindowEnable("PROFILE_WINDOW") && iComIndex == ACTION_DEACTIVATE)
	{
		PressEsc();
		return;
	}

	if (iComIndex == ACTION_ACTIVATE || iComIndex == ACTION_MOUSECLICK)
	{
		if (sNodName == "PROFILE_WINDOW_BTN_EXIT")
		{
			PressEsc();
		}
		if (sNodName == "PROFILE_WINDOW_BTN_CHOOSE")
		{
			ProcChooseProfile();
		}
		if (sNodName == "PROFILE_WINDOW_BTN_DELETE")
		{
			DoConfirm(CONFIRMMODE_PROFILE_DELETE);
		}
		return;
	}
}

void PressEsc()
{
	if (isMainMenuChecker && g_nSaveQuantity == 0)
	{
		SetCurrentProfile("");
		ProcExitProfile();
	}
	else
		ProcExitProfile();
}

bool ParseSaveData(string fullSaveData, ref facestr, ref locationStr, ref timeStr, ref languageID, ref playtime, ref curship, ref saveVer)
{
	string lastStr;
	if (!GetNextSubStr(fullSaveData, locationStr, &lastStr, "@")) return false;
	if (!GetNextSubStr(lastStr, facestr, &lastStr, "@")) return false;
	if (!GetNextSubStr(lastStr, timeStr, &lastStr, "@")) return false;
	if (!GetNextSubStr(lastStr, playtime, &lastStr, "@")) return false;
	if (!GetNextSubStr(lastStr, curship, &lastStr, "@")) return false;
	if (!GetNextSubStr(lastStr, languageID, &lastStr, "@")) return false;
	if (!GetNextSubStr(lastStr, saveVer, &lastStr, "@")) return false;
	return true;
}

bool GetNextSubStr(string inStr, ref outStr, ref lastStr, string separator)
{
	if (inStr == "")
	{
		outStr = "";
		lastStr = "";
		return false;
	}
	int strSize = strlen(inStr) - 1;
	int sympos = findsubstr(inStr, separator, 0);
	if (sympos == -1)
	{
		outStr = inStr;
		lastStr = "";
		return true;
	}
	if (sympos > 0)    outStr = strcut(inStr, 0, sympos - 1);
	else    outStr = "";
	if (strSize > sympos + 1) lastStr = strcut(inStr, sympos + 1, strSize);
	else lastStr = "";
	return true;
}

void ProcessDeleteSaveFile()
{
	string curSave = GetCurSaveName();
	if (curSave == "")
	{
		return;
	}
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_DELETE_SAVE_FILE, curSave);
	CacheRemoveSave(curSave); // > выкидываем только что удалённый файл из кэша

	int c, cDel = g_nCurrentSaveIndex;
	if (bThisSave) cDel -= 1;
	if (cDel < 0) return;

	string attrDst, attrSrc;
	aref arSrc, arDst;
	for (c = cDel; c < g_nSaveQuantity - 1; c++)
	{
		attrDst = "s" + c;
		attrSrc = "s" + (c + 1);
		makearef(arDst, g_oSaveContainer.(attrDst));
		makearef(arSrc, g_oSaveContainer.(attrSrc));
		CopyAttributes(arDst, arSrc);
	}
	attrDst = "s" + (g_nSaveQuantity - 1);
	DeleteAttribute(&g_oSaveContainer, attrDst);

	g_nSaveQuantity--;
	g_oSaveContainer.listsize = g_nSaveQuantity;

	FillSaveList(g_nFirstSaveIndex);
	SetClickable("SAVESCROLL", g_nSaveQuantity > MAX_SAVE_SLOTS);

	// при интерфейсе загрузки выделение обязательно оставляем на реальном сейве
	attrDst = "s" + cDel;
	if (!CheckAttribute(&g_oSaveContainer, attrDst))
	{
		if (g_nCurrentSaveIndex > g_nFirstSaveIndex)
		{
			SelectSaveImage(g_nCurrentSaveIndex - 1);
		}
	}

	ReloadSaveInfo();
}

void ProcessLoad()
{
	string sCurSave = GetCurSaveName();
	PlayerProfile.name = currentProfile;
	SaveLastProfileToCurrentProfile();
	// read option from profile
	LoadGameOptions();

	IDoExit(RC_INTERFACE_SAVELOAD_EXIT);
	ResetSound();

	SetEventHandler("evntLoad", "LoadGame", 1);
	PostEvent("evntLoad", 0, "s", "SAVE\" + PlayerProfile.name + "\" + sCurSave);
	Event("evntPreLoad");
}

void ProcessSave()
{
	string curSave = GetCurSaveName();
	if (curSave != "")
	{
		SendMessage(&GameInterface, "ls", MSG_INTERFACE_DELETE_SAVE_FILE, curSave);
		ClearSaveCache(); // > перезапись удаляет старый файл, его запись в кэше больше не валидна
	}

	LaunchCustomSaveGame();
}

void LaunchCustomSaveGame()
{
	string curLocName = GetCurLocationName();
	string saveName;
	saveName = GetClampedSaveName(curLocName, 0);
	int idx = 0;
	while(SendMessage(&GameInterface, "ls", MSG_INTERFACE_NEW_SAVE_FILE_NAME, saveName) == 1)
	{
		saveName = GetClampedSaveName(curLocName, idx + 1);
		idx++;
	}

	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowDisable("CUSTOM_SAVE_WINDOW", false);
	XI_WindowShow("CUSTOM_SAVE_WINDOW", true);

	GameInterface.CUSTOM_SAVE_NAME.str = saveName;
	SetFormatedText("CUSTOM_SAVE_MSG", XI_ConvertString("SaveName"));
}

void ExitSaveCustomGame()
{
	XI_WindowShow("CUSTOM_SAVE_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);
	// set current node to button for start profile choosing
	SetCurrentNode("BTN_PROFILE");
}

void ProcessCustomSaveAction()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if (iComIndex == ACTION_ACTIVATE || iComIndex == ACTION_MOUSECLICK)
	{
		if (sNodName == "CUSTOM_SAVE_BTN_OK")
		{

			string saveName = GameInterface.CUSTOM_SAVE_NAME.str;
			string sSaveDescriber = GetSaveDataString(saveName);
			SetEventHandler("evntSave", "SaveGame", 1);

			DeleteAfterSaveFunction();
			bAutoSaveStarted = true;
			PostEvent("Event_AutoSaveRefresh", AUTOSAVE_COOLDOWN);

			PostEvent("evntSave", 0, "ss", "SAVE\" + currentProfile + "\" + saveName, sSaveDescriber);
			// Warship Fix свечения
			if (CheckAttribute(&InterfaceStates, "GlowEffect"))
			{
				SetGlowParams(1.0, sti(InterfaceStates.GlowEffect), 2);
			}
			ExitSaveCustomGame();
			IDoExit(RC_INTERFACE_SAVELOAD_EXIT);
		}
		if (sNodName == "CUSTOM_SAVE_BTN_CANCEL")
		{
			ExitSaveCustomGame();
		}
	}
}

string GetCurSaveName()
{
	if (bThisSave && or(g_nCurrentSaveIndex < 1, g_nCurrentSaveIndex > g_nSaveQuantity)) return "";
	if (!bThisSave && g_nCurrentSaveIndex >= g_nSaveQuantity) return "";
	string attr;
	if (bThisSave)
		attr = "s" + (g_nCurrentSaveIndex - 1);
	else
		attr = "s" + g_nCurrentSaveIndex;
	if (CheckAttribute(&g_oSaveContainer, attr + ".savename"))
	{
		return g_oSaveContainer.(attr).savename;
	}
	return "";
}

void DoConfirm(int nConfirmMode)
{
	g_sConfirmReturnWindow = "MAIN_WINDOW";
	if (XI_IsWindowEnable("PROFILE_WINDOW"))
	{
		g_sConfirmReturnWindow = "PROFILE_WINDOW";
	}
	XI_WindowDisable(g_sConfirmReturnWindow, true);
	// enable confirm window
	XI_WindowDisable("CONFIRM_WINDOW", false);
	XI_WindowShow("CONFIRM_WINDOW", true);
	SetNodeUsing("CONFIRM_BADSAVE", false);
	SetCurrentNode("CONFIRM_YES");

	g_nConfirmMode = nConfirmMode;
	switch (nConfirmMode)
	{
		case CONFIRMMODE_PROFILE_DELETE:
			SetFormatedText("CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID, "Delete profile confirm"));
		break;
		case CONFIRMMODE_SAVE_DELETE:
			SetFormatedText("CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID, "Delete savefile confirm"));
		break;
		case CONFIRMMODE_SAVE_OVERWRITE:
			SetFormatedText("CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID, "Overwrite savefile confirm"));
		break;
		case CONFIRMMODE_LOAD_GAME:
			SetFormatedText("CONFIRM_TEXT", LanguageConvertString(g_nInterfaceFileID, "Load game confirm"));
		break;
		case CONFIRMMODE_BAD_SAVE:
			SetNodeUsing("CONFIRM_BADSAVE", true);
			SetNodeUsing("CONFIRM_YES", false);
			SetNodeUsing("CONFIRM_NO", false);
			SetCurrentNode("CONFIRM_BADSAVE");
			SetFormatedText("CONFIRM_TEXT", sSaveVersion);
		break;
	}
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "CONFIRM_TEXT", 5); // центрируем по вертикали
}

void procConfirm()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();

	if (iComIndex == ACTION_ACTIVATE || iComIndex == ACTION_MOUSECLICK)
	{
		if (sNodName == "CONFIRM_YES")
		{
			UndoConfirm(true);
		}
		else
		{
			UndoConfirm(false);
		}
	}
	if (iComIndex == ACTION_DEACTIVATE)
	{
		UndoConfirm(false);
	}
}

void UndoConfirm(bool bPositiveChoose)
{
	// disable confirm
	XI_WindowDisable("CONFIRM_WINDOW", true);
	XI_WindowShow("CONFIRM_WINDOW", false);
	// enable window where confirm was started
	XI_WindowDisable(g_sConfirmReturnWindow, false);

	int nTmp = g_nConfirmMode;
	if (bPositiveChoose)
	{
		switch (nTmp)
		{
			case CONFIRMMODE_PROFILE_DELETE: ProcDeleteProfile(); break;
			case CONFIRMMODE_SAVE_DELETE: ProcessDeleteSaveFile(); break;
			case CONFIRMMODE_SAVE_OVERWRITE: ProcessSave(); break;
			case CONFIRMMODE_LOAD_GAME: ProcessLoad(); break;
		}
	}
	// возвращаем управление правильной контролке
	switch (nTmp)
	{
		case CONFIRMMODE_PROFILE_DELETE: SetCurrentNode("PROFILE_WINDOW_BTN_DELETE"); break;
		case CONFIRMMODE_SAVE_DELETE:
			if (GetSelectable("BTN_DELETE"))
			{
				SetCurrentNode("BTN_DELETE");
			}
			else
			{
				SetCurrentNode("SAVE_SELECTER");
			}
		break;
		case CONFIRMMODE_SAVE_OVERWRITE: SetCurrentNode("BTN_SAVELOAD"); break;
		case CONFIRMMODE_LOAD_GAME: SetCurrentNode("BTN_SAVELOAD"); break;
		case CONFIRMMODE_BAD_SAVE: SetCurrentNode("BTN_SAVELOAD"); break;
	}
}

void ShowCharacterFace(int iPlace, string sFace)
{
	string nodname = "OFFICER" + (iPlace + 1);
	string facegroup = sFace;
	if (sFace == "" || sFace == "*")
	{
		facegroup = "face128_fighter";
		switch (iPlace)
		{
			case 0: facegroup = "emptyface"; break;
			case 4: facegroup = "face128_navigator"; break;
			case 5: facegroup = "face128_boatswain"; break;
			case 6: facegroup = "face128_cannoner"; break;
			case 7: facegroup = "face128_doctor"; break;
			case 8: facegroup = "face128_treasurer"; break;
			case 9: facegroup = "face128_carpenter"; break;
		}
	}
	if (facegroup == "emptyface")
		SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, nodname, 6, facegroup, "emptyface");
	else
		SendMessage(&GameInterface, "lslss", MSG_INTERFACE_MSG_TO_NODE, nodname, 6, facegroup, "face");
}

void ShowFaceInfo(string facestr)
{
	string sstr = facestr;
	string sdat;
	for (int i = 0; i < 10; i++)
	{
		sdat = "";
		if (GetNextSubStr(sstr, &sdat, &sstr, ","))
		{
			ShowCharacterFace(i, sdat);
		}
		else
		{
			ShowCharacterFace(i, "*");
		}
	}
}

void SSI(string shipTexture)
{
	if (shipTexture != "1000")    SetNewPicture("SHIP_ICON", "interfaces\ships\" + shipTexture + ".tga.tx");
	else SetNewPicture("SHIP_ICON", "");
}

void ReloadSaveInfo()
{
	int nSlot = g_nCurrentSaveIndex - g_nFirstSaveIndex;
	string info = "";
	string playtime = "#";
	string curship = "#";

	if (nSlot >= 0 && nSlot < MAX_SAVE_SLOTS && CheckAttribute(&g_oSaveList[nSlot], "faceinfo"))
	{
		info = g_oSaveList[nSlot].faceinfo;
		if (g_oSaveList[nSlot].playtime != "")
		{
			playtime = "#" + XI_ConvertString("Play Time") + ": " + ParsePlayTime(g_oSaveList[nSlot].playtime);
			XI_MakeNode("RESOURCE\INI\interfaces\save_load.ini", "PICTURE", "GAMETIME_PIC", 120);
		}
		else
		{
			playtime = "#" + XI_ConvertString("TenSpace");
			XI_DeleteNode("GAMETIME_PIC");
		}
	}
	ShowFaceInfo(info);
	if (nSlot >= 0 && nSlot < MAX_SAVE_SLOTS && CheckAttribute(&g_oSaveList[nSlot], "curship")) SSI(g_oSaveList[nSlot].curship);
	else SetNewPicture("SHIP_ICON", "");
	int textWidth = GetStringWidth(playtime, "interface_button", 0.95);
	int iconOffset = -3;
	int i = 1;
	while (textWidth > 200)
	{
	    playtime = strcut(playtime, 0, strlen(playtime)-(1+i));
	    textWidth = GetStringWidth(playtime, "interface_button", 0.95);
	    i++;
	}
	if (i > 1)
	{
	    playtime += "...";
	    iconOffset = 0;
	}
	SendMessage(&GameInterface, "lslls", MSG_INTERFACE_MSG_TO_NODE, "SAVEINFO", 1, 2, playtime);
	// set icon pos
	float foffsetX, foffsetY;
	GetXYWindowOffset(&foffsetX, &foffsetY);
	int posLeft = 771+makeint(foffsetX + textWidth * 0.5) + iconOffset;
	SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "GAMETIME_PIC", 0, posLeft,210+makeint(foffsetY),posLeft + 19,229+makeint(foffsetY));

	if (info == "")
	{
		SetSelectable("BTN_SAVELOAD", bThisSave);
		SetSelectable("BTN_DELETE", false);
	}
	else
	{
		SetSelectable("BTN_SAVELOAD", true);
		SetSelectable("BTN_DELETE", true);
	}
}

void ScrollPosChange()
{
	float fPos = GetEventData();
	string sNod = GetEventData();

	if (sNod == "SAVESCROLL")
	{
		int saveIndex = sti(fPos * g_nSaveQuantity);
		if (saveIndex == g_nCurrentSaveIndex) return;
		if (g_nCurrentSaveIndex >= 0)
		{
			int nOldIdx = g_nCurrentSaveIndex - g_nFirstSaveIndex;
			SetSelecting(nOldIdx, false);
		}
		int nLineQ = g_nSaveQuantity / SLOTS_IN_LINE;
		int nLine = makeint(makefloat(nLineQ) * fPos);
		FillSaveList(nLine * SLOTS_IN_LINE);

		SetSelecting(0, true);
		SelectSaveImage(g_nFirstSaveIndex);
	}
}

void LoadProfile()
{
	ProcChooseProfile();
}

void SaveLoad()
{
	int i, iComIdx = GetEventData();
	string sNodName = GetEventData();

	for (i = 0; i < MAX_SAVE_SLOTS; i++)
	{
		if (sNodName == ("SAVEIMG" + (i + 1)))
		{
			SelectSaveImage(g_nFirstSaveIndex + i);
			break;
		}
	}

	SaveLoadCurrentIntoSlot();
}

bool IsActualSaveVersion(ref saveSlot)
{
	sSaveVersion = LanguageConvertString(g_nInterfaceFileID, "BadSaveNoVersion");

	// > в слоте нет прочитанного сейва (пустой, заглушка "загружается", битый файл) - сверять версию не с чем
	if (!CheckAttribute(saveSlot, "hasdata") || saveSlot.hasdata != "1")
		return true;

	if (!CheckAttribute(saveSlot, "saveVer"))
		return false;

	if (saveSlot.saveVer != "SaveVer=" + VERSION_NUM_PRE)
	{
		switch (saveSlot.saveVer)
		{
			case "SaveVer=99941":
				sSaveVersion = LanguageConvertString(g_nInterfaceFileID, "BadSaveVersion") +" 1.1.2 \n" +LanguageConvertString(g_nInterfaceFileID, "BadSaveInfo");
			break;
			case "SaveVer=99940":
				sSaveVersion = LanguageConvertString(g_nInterfaceFileID, "BadSaveVersion") +" 1.0.3 \n" +LanguageConvertString(g_nInterfaceFileID, "BadSaveInfo");
			break;
		}
		return false;
	}

	return true;
}
// Sith окно обучения
string descr = "";
string loadScr = "";
string cimg1 = "";
string cimg2 = "";
string cimg3 = "";
string cimg4 = "";
string cimg5 = "";
string cimg6 = "";
int curShowTutorial = true;

void InitInterface_SB(string iniName, string tutorialName, bool bShowVideo)
{
	// if(bShowVideo) PauseAllSounds(); // ставим звуки на паузу если видео
	StartAboveForm(true);
	//LAi_SetActorType(pchar);
	// лочим квест и карту
    bQuestCheckProcessFreeze = true;
    if(IsEntity(&worldMap))
    {
    	wdmLockReload = true;
    }

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

//	PlaySound("Ambient\SEA\Ship_bell_Two.wav"); //TODO < нужно ли?

	SetFormatedText("TITLE", GetConvertStr(tutorialName + "_title", "TutorialDescribe.txt"));

    string videoName = GetConvertStr(tutorialName + "_video", "TutorialDescribe.txt"); // переопредление названия видео в title
    if (videoName == "")
	{
	    videoName = tutorialName;
	}

	bool bAdaptive = false;
	if(!bShowVideo) // показ картинки
	{
		SetNodeUsing("INFO_PICTURE", true);
		SetNodeUsing("INFO_VIDEO", false);
		SetNodeUsing("ZOOM",false);
		SetNodeUsing("ZOOMPLUS",false);
		SetNodeUsing("VFRAME",false);
		loadScr = "loading\salary.tga";
		SetNewPicture("INFO_PICTURE", loadScr);
	}
	else
	{
		if (bShowVideo && FindTutorialVideoFile(videoName)) // если играем видео
		{
			SetNodeUsing("INFO_PICTURE", false);
			SetNodeUsing("INFO_VIDEO", true);
			loadScr = "tutorial\" + videoName + ".webm";
			SetNewVideo("INFO_VIDEO", loadScr);
			SetNewVideo("INFO_VIDEOZ", loadScr);
			SetFormatedText("ZOOM", "ᐽ");
		}
		else
		{
			// видео не нашли - адаптивная верстка под текст
			SetNodeUsing("INFO_PICTURE", false);
			SetNodeUsing("INFO_VIDEO", false);
			SetNodeUsing("ZOOM",false);
			SetNodeUsing("ZOOMPLUS",false);
			SetNodeUsing("VFRAME",false);
			SetNodeUsing("VFRAME_BORDER",false);

			bAdaptive = true;
		}
	}

	SetNodesState_InfoText(tutorialName, bAdaptive);

	cimg1 = GetConvertStr(tutorialName + "_controlsimg1", "TutorialDescribe.txt");
	cimg2 = GetConvertStr(tutorialName + "_controlsimg2", "TutorialDescribe.txt");
	cimg3 = GetConvertStr(tutorialName + "_controlsimg3", "TutorialDescribe.txt");
	cimg4 = GetConvertStr(tutorialName + "_controlsimg4", "TutorialDescribe.txt");
	cimg5 = GetConvertStr(tutorialName + "_controlsimg5", "TutorialDescribe.txt");
	cimg6 = GetConvertStr(tutorialName + "_controlsimg6", "TutorialDescribe.txt");
	SetFormatedText("CONTROLS_TEXT", XI_ConvertString("Controls") + ":");
	if(cimg1 !="" || cimg2 !="" || cimg3 !="" || cimg4 !="" || cimg5 !="" || cimg6 !="")
	{
		string cimTotal = "";
		if(cimg1 !="") cimTotal += GetKeyCodeImg(cimg1);
		if(cimg2 !="") cimTotal += GetKeyCodeImg(cimg2);
		if(cimg3 !="") cimTotal += GetKeyCodeImg(cimg3);
		if(cimg4 !="") cimTotal += GetKeyCodeImg(cimg4);
		if(cimg5 !="") cimTotal += GetKeyCodeImg(cimg5);
		if(cimg6 !="") cimTotal += GetKeyCodeImg(cimg6);
		SetFormatedText("CONTROLS_IMG", cimTotal);
		/* if(cimg2 !="") SetFormatedText("CONTROLS_IMG", GetKeyCodeImg(cimg1)+GetKeyCodeImg(cimg2));
		else SetFormatedText("CONTROLS_IMG", GetKeyCodeImg(cimg1)); */
		SetNodeUsing("B_OK", false);
		SetNodeUsing("B_OK2", true);
		SetNodeUsing("CONTROLS_TEXT", true);
		SetNodeUsing("CONTROLS_IMG", true);
	}
	else
	{
		SetFormatedText("CONTROLS_TEXT", "");
		SetNodeUsing("B_OK", true);
		SetNodeUsing("B_OK2", false);
		SetNodeUsing("CONTROLS_TEXT", false);
		SetNodeUsing("CONTROLS_IMG", false);
	}

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0); // Выход
	SetEventHandler("exitCancel","ProcessCancelExit",0); // Выход по крестику или Esc
	SetEventHandler("ievnt_command","ProcCommand",0); // выход только тут (по НЕТ)
	SetEventHandler("CheckButtonChange","procCheckBoxChange",0);
	SetEventHandler("evntDoPostExit","DoPostExit",0); // выход из интерфейса
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);

	if(CheckAttribute(&InterfaceStates,"ShowTutorial"))
	{
		curShowTutorial = sti(InterfaceStates.ShowTutorial);
	}
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TUTORIAL_CHECKBOX", 2, 1, curShowTutorial);
	SetNodeUsing("TUTORIAL_CHECKBOX",!GetGlobalTutor());
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_TUTORIAL);
}

void ProcessCancelExit()
{
	IDoExit(RC_INTERFACE_TUTORIAL);
}

void IDoExit(int exitCode)
{
	if(CheckAttribute(&InterfaceStates,"ShowTutorial"))
	{
		if(sti(InterfaceStates.ShowTutorial) != curShowTutorial) SaveGameOptions();
	}
	EndAboveForm(true);
	//LAi_SetPlayerType(pchar);
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("CheckButtonChange","procCheckBoxChange");
	DelEventHandler("evntDoPostExit","DoPostExit");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	
	interfaceResultCommand = exitCode;
	EndCancelInterface(true);
	PostEvent("StopQuestCheckProcessFreeze", 100);// заморозка проверки квестов
	// SetSchemeAfterFlagRise(); // возвращаем звуки если видео
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	
	switch(nodName)
	{
		case "B_OK":
			if(comName=="activate" || comName=="click")
			{
				IDoExit(RC_INTERFACE_TUTORIAL);
			}
		break;
		case "B_OK2":
			if(comName=="activate" || comName=="click")
			{
				IDoExit(RC_INTERFACE_TUTORIAL);
			}
		break;
	}
}

void procCheckBoxChange()
{
	string sNodName = GetEventData();
	int nBtnIndex = GetEventData();
	int bBtnState = GetEventData();

	if(sNodName == "TUTORIAL_CHECKBOX") 
	{
        InterfaceStates.ShowTutorial = bBtnState;
	}
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void ShowInfoWindow()
{
	XI_WindowDisable("INFO_WINDOW", false);
	XI_WindowShow("INFO_WINDOW", true);
}

void HideInfoWindow()
{
	XI_WindowDisable("INFO_WINDOW", true);
	XI_WindowShow("INFO_WINDOW", false);
}

void SetNodesState_InfoText(string tutorialName, bool bAdaptive)
{
	descr = GetConvertStr(tutorialName + "_descr", "TutorialDescribe.txt");
	SetFormatedText("INFO_TEXT", descr);
	SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT",5);

	int nStrings = GetNumberOfStringsInFormatedText("INFO_TEXT", descr); // считаем сколько строк в форме
	if (!bAdaptive)
	{
		if(nStrings < 8)// Запрет на скроллинг
		{
			SetNodeUsing("SCROLL_TEXT",false);
			SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 13, 1); //1 - запрет, 0 - нет
		}

		return;
	}

	if(nStrings < 8)// Запрет на скроллинг
	{
		SetNodeUsing("SCROLL_TEXT",false);
		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 13, 1);
	}

	int nodeLeft, nodeTop, nodeRight, nodeBottom;
	int maxStringQty = 15; // Столько строк макс. поместится в форму, иначе юзаем скролл
	SetNodeUsing("SCROLL_TEXT",false);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 13, 1);

	int needStringQty = nStrings - 7 + 1;
	if (needStringQty > maxStringQty)
	{
		SetNodeUsing("SCROLL_TEXT", true);
		needStringQty = maxStringQty;
		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 13, 0);
	}

	float foffsetX, foffsetY;
	GetXYWindowOffset(&foffsetX, &foffsetY);
//		Log_Info("offX: " + makeint(foffsetX) + ", offY: " + makeint(foffsetY));

	SetNodePosition("INFO_TEXT", 217 + makeInt(foffsetX), 240 + makeint(foffsetY), 584 + makeInt(foffsetX), 354 + makeint(foffsetY));
	SetNodePosition("MAIN_FRAME", 201 + makeInt(foffsetX), 195 + makeint(foffsetY), 600 + makeInt(foffsetX), 407 + makeint(foffsetY));
	SetNodePosition("TITLE", 206 + makeInt(foffsetX), 198 + makeint(foffsetY), 595 + makeInt(foffsetX), 221 + makeint(foffsetY));
	SetNodePosition("CONTROLS_IMG", 306 + makeInt(foffsetX), 365 + makeint(foffsetY), 439 + makeInt(foffsetX), 387 + makeint(foffsetY));
	SetNodePosition("CONTROLS_TEXT", 212 + makeInt(foffsetX), 368 + makeint(foffsetY), 301 + makeInt(foffsetX), 384 + makeint(foffsetY));
	SetNodePosition("B_OK", 345 + makeInt(foffsetX), 362 + makeint(foffsetY), 456 + makeInt(foffsetX), 390 + makeint(foffsetY));
	SetNodePosition("B_OK2", 456 + makeInt(foffsetX), 362 + makeint(foffsetY), 584 + makeInt(foffsetX), 390 + makeint(foffsetY));
	SetNodePosition("SCROLL_TEXT", 584 + makeInt(foffsetX), 240 + makeint(foffsetY), 595 + makeInt(foffsetX), 354 + makeint(foffsetY));

	if (needStringQty > 0)
	{
		int halfStringHeight = 8; // половина высоты строки текста (высота = 16)
		int dY = halfStringHeight * needStringQty;

		GetNodePosition("INFO_TEXT", &nodeLeft, &nodeTop, &nodeRight, &nodeBottom);
		SetNodePosition("INFO_TEXT", nodeLeft, nodeTop - dY, nodeRight, nodeBottom + dY);

		GetNodePosition("MAIN_FRAME", &nodeLeft, &nodeTop, &nodeRight, &nodeBottom);
		SetNodePosition("MAIN_FRAME", nodeLeft, nodeTop - dY, nodeRight, nodeBottom + dY);

		GetNodePosition("TITLE", &nodeLeft, &nodeTop, &nodeRight, &nodeBottom);
		SetNodePosition("TITLE", nodeLeft, nodeTop - dY, nodeRight, nodeBottom - dY);

		GetNodePosition("CONTROLS_IMG", &nodeLeft, &nodeTop, &nodeRight, &nodeBottom);
		SetNodePosition("CONTROLS_IMG", nodeLeft, nodeTop + dY, nodeRight, nodeBottom + dY);
		GetNodePosition("CONTROLS_TEXT", &nodeLeft, &nodeTop, &nodeRight, &nodeBottom);
		SetNodePosition("CONTROLS_TEXT", nodeLeft, nodeTop + dY, nodeRight, nodeBottom + dY);
		GetNodePosition("B_OK", &nodeLeft, &nodeTop, &nodeRight, &nodeBottom);
		SetNodePosition("B_OK", nodeLeft, nodeTop + dY, nodeRight, nodeBottom + dY);
		GetNodePosition("B_OK2", &nodeLeft, &nodeTop, &nodeRight, &nodeBottom);
		SetNodePosition("B_OK2", nodeLeft, nodeTop + dY, nodeRight, nodeBottom + dY);

		GetNodePosition("SCROLL_TEXT", &nodeLeft, &nodeTop, &nodeRight, &nodeBottom);
		SetNodePosition("SCROLL_TEXT", nodeLeft, nodeTop - dY, nodeRight, nodeBottom + dY);
	}

//		Log_Info("l: " + nodeLeft + ", t: " + (nodeTop - dY) + ", r: " + nodeRight+ ", b: " + (nodeBottom + dY));
}

bool FindTutorialVideoFile(string videoFileName)
{
	object objFileFinder;
	aref arList;
	int iNumFiles = 0;

	string tutorialDir = "resource\VIDEOS\tutorial\";
	objFileFinder.dir = tutorialDir;
	objFileFinder.mask = videoFileName + ".webm";
	CreateEntity(&objFileFinder, "FINDFILESINTODIRECTORY");
	makearef(arList, objFileFinder.filelist);
	iNumFiles = GetAttributesNum(arList);
	DeleteClass(&objFileFinder);

	if (iNumFiles <= 0)
	{
//		Trace("FindTutorialVideoFile >> Can't find video file: " + tutorialDir + videoFileName);
		return false;
	}

	return true;
}
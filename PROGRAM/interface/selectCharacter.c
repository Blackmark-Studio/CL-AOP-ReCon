#include "interface\utils\menu_volume.c"

#define DEFAULT_NAME "Player"
#define DEFAULT_PASS ""

#define SELCHAR_MAX_WINDOWS 5

#define SELCHAR_PERSON_WINDOW 1
#define SELCHAR_NATION_WINDOW 2
#define SELCHAR_EQUIP_WINDOW 3
#define SELCHAR_ATTRIBUTES_WINDOW 4
#define SELCHAR_DIFFICULT_WINDOW 5


bool isOkExit = false;
int idLngFile = -1;
int iCurWindow;
int iCharModel = 0;
int iModelQty  = 8;
string sLocation_id, sLocation_locator, sLocation_camera, sLocation_turn;
bool bLocationLoaded = false;
string sCharacterName;
int heroQty = 0;
string totalInfo;
string infoCharStr;
bool bShowSkills = false;
int iCurItemsTablePage = 1;
int iItemsTablePageQty = 1;
string CurTable, CurRow, CurCol;
string ShipI_sCachedShipPic;
object PIRATES_DependObj;

// KZ > поворот модели перса с удержанием клавиш A и D или ЛКМ
// > положение мыши при ЛКМ - в любом месте, кроме ноды ввода текста, но для начала движения нужно навестись на тушку перса
// > при зажатых A или D - в любом месте, кроме ноды ввода текста
float fSelCharFacingAy      = 4.42;  // > текущий целевой угол поворота модели

// > поворот клавишами A/D при удержании (постоянная скорость)
#define SELCHAR_KEY_A          65     // > VK-код клавиши A
#define SELCHAR_KEY_D          68     // > VK-код клавиши D
#define SELCHAR_KEY_TURN_SPEED 2.0    // > скорость вращения клавишами, rad/sec (полный оборот ~3.1 сек)

// > поворот перетаскиванием ЛКМ по рамке FRAME_ROTATE (скорость привязана к движению мыши)
#define SELCHAR_VK_LBUTTON      1     // > VK-код левой кнопки мыши
#define SELCHAR_FRAME_TURN_SENS 0.005 // > чувствительность вращения мышью, rad/pixel

// > координаты ноды FRAME_ROTATE из *.ini
float SELCHAR_FRAME_LEFT;
float SELCHAR_FRAME_TOP;
float SELCHAR_FRAME_RIGHT;
float SELCHAR_FRAME_BOTTOM;

bool  bSelCharFrameGrab  = false; // > флаг на зажатую ЛКМ на FRAME_ROTATE
float fSelCharFramePrevX = 0.0;   // > позиция мыши по X в прошлом кадре (для дельты вращения)

void InitInterface(string iniName)
{
	GameInterface.title = "titleCharacterSelect";
	GameInterface.faces.current = 1;
	iCurWindow = SELCHAR_PERSON_WINDOW;
	ShipI_sCachedShipPic = "";
	InitPiratesDependingsObject();

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetMainCharacterIndex(1);
	SetNationRelations();

	sCharacterName = pchar.id;

	GameInterface.PROFILE_NAME.str = DEFAULT_NAME;
	GameInterface.PROFILE_PASS.str = DEFAULT_PASS;

    LoadStartGameParam(); // boal
    MOD_EXP_RATE = 10; // задаем в начале игры (выбор, от 5 до 15, 10 - середина по умолчанию, 15 - медлено)
    GameInterface.nodes.EXP_SLIDE.value = 0.5;
    SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"EXP_SLIDE", 0, 0.5);

    if (startHeroType < 1) startHeroType = 1; // fix
    else if (startHeroType > sti(GetNewMainCharacterParam("hero_qty"))) startHeroType = sti(GetNewMainCharacterParam("hero_qty")); // fix

	SetEventHandler("exitCancel", "exitCancel", 0);
	SetEventHandler("selectEngland", "selectEngland", 0);
	SetEventHandler("selectFrance", "selectFrance", 0);
	SetEventHandler("selectSpain", "selectSpain", 0);
	SetEventHandler("selectHolland", "selectHolland", 0);
	SetEventHandler("selectPirate", "selectPirate", 0);
	SetEventHandler("confirmChangeProfileName", "confirmChangeProfileName", 0);
	SetEventHandler("MouseRClickUP","HideInfo",0);
	SetEventHandler("HideInfoWindow","HideInfo",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("eChangePiratesBtn","ProcessChangePiratesBtn",0);

	SetEventHandler("noteOk","procNoteOk",0);

	SetEventHandler("frame","IProcessFrame",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);

	if (!CheckAttribute(&GameInterface, "SavePath"))
		GameInterface.SavePath = "SAVE";

    heroQty   = sti(GetNewMainCharacterParam("hero_qty"));

    if (!CheckAttribute(&NullCharacter, "HeroParam.HeroType") || !CheckAttribute(&NullCharacter, "HeroParam.nation"))
    {   // иначе уже загружен и выбран гг, смотрим настройки и идем обратно
		SetVariable(true);
	}
	else
	{
	    SetVariable(false);
	}
	TmpI_ShowLevelComplexity();
	SetByDefault();

	DeleteAttribute(pchar, "perks");
	LAi_SetActorTypeNoGroup(PChar);
	SelectOperation();
	SelectCharacter();
	UpdateVisibleElements();
	DoSelectActivePiratesRow(-1);

	MenuVolume_FadeOut(true); // > в конце приглушения гасим и схему звука локации

	SetFormatedText("ROTATE_CHAR_TEXT", GetConvertStr("ChrTurnH", "ControlsNames.txt"));
	SetFormatedText("ROTATE_CHAR_IMAGE", GetKeyCodeImg("ChrStrafeLeft") + " " + GetKeyCodeImg("ChrAimingShot") + " " + GetKeyCodeImg("ChrStrafeRight"));

	// debug управление
	if (!TestMode())
	{
	    SetNodeUsing("FRAME_BGR3", false);
	    SetNodeUsing("MODEL_FRAME_CAPTION", false);
	    SetNodeUsing("LEFTCHANGE_MODEL", false);
	    SetNodeUsing("RIGHTCHANGE_MODEL", false);
	    SetNodeUsing("FRAME_BIG3", false);
	}
}

void SetByDefault()
{
    CheckButton_SetState("CHECK_ENCOUNTERS", iEncountersRate, true);

	if (iArcadeSails == 1)// 1 0
    {
    	CheckButton_SetState("CHECK_ARCADESAIL", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_ARCADESAIL", 2, true);
    }
    if (bRechargePistolOnLine)// 1 0
    {
    	CheckButton_SetState("CHECK_PISTOL", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_PISTOL", 1, false);
    }
    if (bHardcoreGame)// 1 0
    {
    	CheckButton_SetState("CHECK_HARDCORE", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_HARDCORE", 1, false);
    }
	if (bPartitionSet)// 1 0
    {
    	CheckButton_SetState("CHECK_PARTITION", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_PARTITION", 1, false);
    }
	if (bWildCaribbean)// 1 0
    {
    	CheckButton_SetState("CHECK_WILD", 1, true);
    }
    else
    {
        CheckButton_SetState("CHECK_WILD", 1, false);
    }
}

void IProcessFrame()
{
	SelChar_ProcessModelTurn();

	if(GetCurrentNode() == "PROFILE_NAME")
	{
		if(!CheckAttribute(&characters[GetCharacterIndex(sCharacterName)], "profile.name"))
		{
			confirmChangeProfileName();
		}

		if(characters[GetCharacterIndex(sCharacterName)].profile.name!= GameInterface.PROFILE_NAME.str)
		{
			confirmChangeProfileName();
		}
	}
}

void ReadGameOptionsFromUI()
{
	///
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 1))
	{
		iEncountersRate = 1;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 2))
	{
		iEncountersRate = 2;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ENCOUNTERS", 3, 3))
	{
		iEncountersRate = 3;
	}
	////
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ARCADESAIL", 3, 1))
	{
		iArcadeSails = 1;
	}
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_ARCADESAIL", 3, 2))
	{
		iArcadeSails = 0;
	}
	///
 	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_PISTOL", 3, 1))
	{
		bRechargePistolOnLine = true;
	}
	else
	{
		bRechargePistolOnLine = false;
	}
	///
 	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_HARDCORE", 3, 1))
	{
		bHardcoreGame = true;
	}
	else
	{
		bHardcoreGame = false;
	}
	///
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_PARTITION", 3, 1))
	{
		bPartitionSet = true;
	}
	else
	{
		bPartitionSet = false;
	}
	///
	if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CHECK_WILD", 3, 1))
	{
		bWildCaribbean = true;
	}
	else
	{
		bWildCaribbean = false;
	}
}

void exitCancel()
{
	DeleteAttribute(pchar, "actions");
	if (sLocation_id != "")
	{
		int lindex;
		lindex = FindLocation(sLocation_id);
		UnloadLocation(&Locations[lindex]);
	}
	IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
	ReturnToMainMenu();
}

bool IsCorrectProfileName()
{
	int n,nLen;
	string str,sCurProfileName;

	sCurProfileName = GameInterface.PROFILE_NAME.str;
	nLen = strlen(sCurProfileName);
	if (nLen==0) return false;

	for (n=0; n<nLen; n++)
	{
		str = GetSymbol(&sCurProfileName,n);
		if( str=="*" ) {return false;}
		if( str=="?" ) {return false;}
		if( str=="\" ) {return false;}
		if( str=="/" ) {return false;}
	}
	return true;
}

void ShowNoteText(bool bShow)
{
	if (bShow)
    {
		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("CONFIRM_WINDOW", true);
		XI_WindowDisable("NOTE_WINDOW", false);
		XI_WindowShow("NOTE_WINDOW", true);
		SetCurrentNode("NOTE_WINDOW_OK");
	}
    else
    {
		XI_WindowDisable("MAIN_WINDOW", false);
		XI_WindowDisable("CONFIRM_WINDOW", false);
		XI_WindowDisable("NOTE_WINDOW", true);
		XI_WindowShow("NOTE_WINDOW", false);
		SetCurrentNode("PROFILE_NAME");
	}
}

void procNoteOk()
{
	ShowNoteText(false);
}

// > целевой угол поворота модели
void SelChar_SetFacing(float ay)
{
	fSelCharFacingAy = ay;
	CharacterTurnAy(Pchar, ay);
}

// KZ > поворот модели двумя способами:
// 1 - клавиши A или D при удержании: постоянная скорость, плавно, непрерывное вращение на 360°;
// 2 - удержание ЛКМ: скорость и направление привязаны к движению мыши по горизонтали; ЛКМ можно зажать в любом месте, но движение начнётся только при наведении на перса.
// Способы ВЗАИМОИСКЛЮЧАЕМЫ: не конфликтуют - работает источник, стартовавший первым.
void SelChar_ProcessModelTurn()
{
	if (!bLocationLoaded) { bSelCharFrameGrab = false; return; } // > персонаж или камера ещё не готовы

	// > флаги работы клавиш A и D
	string sNode = GetCurrentNode();
	bool bNameInput = sNode == "PROFILE_NAME" || sNode == "PROFILE_STR";
	bool bKeyA = (!bNameInput) && XI_IsVirtualKeyPressed(SELCHAR_KEY_A);
	bool bKeyD = (!bNameInput) && XI_IsVirtualKeyPressed(SELCHAR_KEY_D);
	bool bKeyTurn = or(bKeyA && !bKeyD, bKeyD && !bKeyA); // > автивной может быть только одна из клавиша

	// флаг работы ЛКМ
	bool bLMB = XI_IsVirtualKeyPressed(SELCHAR_VK_LBUTTON);
	if (!bLMB) bSelCharFrameGrab = false; // > отпустили ЛКМ

	GetNodePosition("FRAME_ROTATE", &SELCHAR_FRAME_LEFT, &SELCHAR_FRAME_TOP, &SELCHAR_FRAME_RIGHT, &SELCHAR_FRAME_BOTTOM);

	float mx = 0.0;
	bool bMouseTurn = false;
	if (bLMB && CheckAttribute(&GameInterface, "mousepos"))
	{
		mx = stf(GameInterface.mousepos.x);
		float my = stf(GameInterface.mousepos.y);
		// > захват уже идёт ИЛИ ЛКМ нажата именно над моделькой перса
		bMouseTurn = or(bSelCharFrameGrab, mx >= SELCHAR_FRAME_LEFT && mx <= SELCHAR_FRAME_RIGHT && my >= SELCHAR_FRAME_TOP && my <= SELCHAR_FRAME_BOTTOM);
	}

	// > при конфликте работы, приоритет у первого активного
	if (bMouseTurn && bKeyTurn)
	{
		if (bSelCharFrameGrab)
			fSelCharFramePrevX = mx; // > не копим дельту мышки при конфликте
		return;
	}

	// > работа ЛКМ (скорость вращения = скорость движения мыши по X)
	if (bMouseTurn)
	{
		if (!bSelCharFrameGrab) // > первый кадр захвата без рывка
		{
			bSelCharFrameGrab = true;
			fSelCharFramePrevX = mx;
			return;
		}
		float dx = mx - fSelCharFramePrevX;
		if (dx != 0.0)
			SelChar_SetFacing(fSelCharFacingAy - dx * SELCHAR_FRAME_TURN_SENS); // > вращение относительно экрана (меняй - на +, если нужно относительно персонажа)
		fSelCharFramePrevX = mx;
		return;
	}

	// > работа клавиш A и D (постоянная скорость вращения, настройка в SELCHAR_KEY_TURN_SPEED)
	if (bKeyTurn)
	{
		float dAngle = SELCHAR_KEY_TURN_SPEED * makefloat(GetDeltaTime()) * 0.001; // > шаг за кадр, rad
		if (bKeyA) SelChar_SetFacing(fSelCharFacingAy + dAngle);
		else if (bKeyD) SelChar_SetFacing(fSelCharFacingAy - dAngle);
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	if (StrEndsWith(nodName, "_TYPE_BORDER"))
	{
		if(comName=="click")
		{
			ProcessCommandExecuteType(nodName);
		}
	}

	switch(nodName)
	{
        case "LEFTCHANGE_CHARACTER":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    	break;

    	case "RIGHTCHANGE_CHARACTER":
    		if(comName=="click")
    		{
    		    ProcessCommandExecuteRight();
    		}
    	break;
    	case "LEFTCHANGE_STORY":
    		if(comName=="click")
    		{
    		    ProcessChangeStoryBtn();
    		}
    	break;

    	case "RIGHTCHANGE_STORY":
    		if(comName=="click")
    		{
    		    ProcessChangeStoryBtn();
    		}
    	break;

    	case "LEFTCHANGE_MODEL":
    		if(comName=="click")
    		{
    		    iCharModel--;
                if (iCharModel < 0)
                    iCharModel = iModelQty;
    		    SelectCharacter_Model();
    		}
    	break;

    	case "RIGHTCHANGE_MODEL":
    		if(comName=="click")
    		{
				iCharModel++;
                if (iCharModel > iModelQty)
                    iCharModel = 0;
    		    SelectCharacter_Model();
    		}
    	break;

    	case "EQUIPMENT_PAGE_BACK":
    		if(comName=="click")
    		{
    			if (iCurItemsTablePage <= 1)
    				return;

				iCurItemsTablePage -= 1;
				RefreshEquipmentTable();
    		}
    	break;

    	case "EQUIPMENT_PAGE_NEXT":
    		if(comName=="click")
    		{
    			if (iCurItemsTablePage >= iItemsTablePageQty)
    				return;

    			iCurItemsTablePage += 1;
				RefreshEquipmentTable();
    		}
    	break;

		case "BACK_BUTTON1":
    		if(comName=="click")
    		{
    		    ProcessCommandBackButton(iCurWindow);
    		}
			else if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		else if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;

    	case "NEXT_BUTTON1":
    		if(comName=="click")
    		{
    		    ProcessCommandNextButton(iCurWindow);
    		}
			else if(comName=="leftstep")
    		{
    		    ProcessCommandExecuteLeft();
    		}
    		else if(comName=="rightstep")
    		{
                ProcessCommandExecuteRight();
    		}
    	break;

		case "LEFTCHANGE_COMPLEX":
		if(comName=="click")
		{
		    if (MOD_SKILL_ENEMY_RATE > 1)
		    {
               MOD_SKILL_ENEMY_RATE--;
            }
            TmpI_ShowLevelComplexity();
		}
		break;

		case "RIGHTCHANGE_COMPLEX":
			if(comName=="click")
			{
			    if (MOD_SKILL_ENEMY_RATE < 10)
			    {
	               MOD_SKILL_ENEMY_RATE++;
	            }
	            TmpI_ShowLevelComplexity();
			}
		break;

		case "ATTRIBUTES_SHOW_SKILLS_CHECK":
			if(SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "ATTRIBUTES_SHOW_SKILLS_CHECK", 3, 1))
			{
				bShowSkills = true;
			}
			else
			{
				bShowSkills = false;
			}

			ShowSkillsWindow(bShowSkills);
		break;

		case "CONFIRM_WINDOW_MB_YES":
			if (comName == "click" || comName == "activate")
			{
				StartTheGame();
			}

			if (comName == "deactivate")
			{
				ShowConfirmWindow(false);
			}
		break;

		case "CONFIRM_WINDOW_MB_NO":
			if (comName == "click" || comName == "activate")
			{
				ShowConfirmWindow(false);
			}

			if (comName == "deactivate")
			{
				ShowConfirmWindow(false);
			}
		break;
	}
}

void ProcessChangeStoryBtn()
{
	// Для этих героев смена сюжет-фриплей недоступна
	if (startHeroType > 3)
	{
		return;
	}

   	bool bStoryMode = !IsFreeplayModeStart();

	if (!bStoryMode)
	{
		NullCharacter.HeroParam.FreeplayMode = false;
    	SetFormatedText("STORY_TITLE", XI_ConvertString("SelChar_Story"));
    	SetFormatedText("STORY_INFO", XI_ConvertString("SelChar_StoryDesc"));

		if (startHeroType == 1) // Питер Блад
		{
			NullCharacter.HeroParam.nation = ENGLAND;
		}
		else if (startHeroType == 2) // Мишель де Граммон
		{
			NullCharacter.HeroParam.nation = FRANCE;
		}
		else if (startHeroType == 3) // Эммануэль Пардаль
		{
			NullCharacter.HeroParam.nation = SPAIN;
		}
	}
	else
	{
		NullCharacter.HeroParam.FreeplayMode = true;
	    SetFormatedText("STORY_TITLE", XI_ConvertString("SelChar_Freeplay"));
	    SetFormatedText("STORY_INFO", XI_ConvertString("SelChar_FreeplayDesc"));
	}

	SelectNation(sti(NullCharacter.HeroParam.nation));
}

void ProcessChangePiratesBtn()
{
    string comName = GetEventData();
	string nodName = GetEventData();

	int idxRow = -1;

    switch(nodName)
	{
		case "ATTRIBUTES_P_PLUS_BTN":
			IncreasePIRATES(SPECIAL_S, 1);
			idxRow = 1;
		break;
		case "ATTRIBUTES_P_MINUS_BTN":
			DecreasePIRATES(SPECIAL_S, 1);
			idxRow = 1;
		break;
		case "ATTRIBUTES_I_PLUS_BTN":
			IncreasePIRATES(SPECIAL_P, 1);
			idxRow = 2;
		break;
		case "ATTRIBUTES_I_MINUS_BTN":
			DecreasePIRATES(SPECIAL_P, 1);
			idxRow = 2;
		break;
		case "ATTRIBUTES_R_PLUS_BTN":
			IncreasePIRATES(SPECIAL_A, 1);
			idxRow = 3;
		break;
		case "ATTRIBUTES_R_MINUS_BTN":
			DecreasePIRATES(SPECIAL_A, 1);
			idxRow = 3;
		break;
		case "ATTRIBUTES_A_PLUS_BTN":
			IncreasePIRATES(SPECIAL_C, 1);
			idxRow = 4;
		break;
		case "ATTRIBUTES_A_MINUS_BTN":
			DecreasePIRATES(SPECIAL_C, 1);
			idxRow = 4;
		break;
		case "ATTRIBUTES_T_PLUS_BTN":
			IncreasePIRATES(SPECIAL_I, 1);
			idxRow = 5;
		break;
		case "ATTRIBUTES_T_MINUS_BTN":
			DecreasePIRATES(SPECIAL_I, 1);
			idxRow = 5;
		break;
		case "ATTRIBUTES_E_PLUS_BTN":
			IncreasePIRATES(SPECIAL_E, 1);
			idxRow = 6;
		break;
		case "ATTRIBUTES_E_MINUS_BTN":
			DecreasePIRATES(SPECIAL_E, 1);
			idxRow = 6;
		break;
		case "ATTRIBUTES_S_PLUS_BTN":
			IncreasePIRATES(SPECIAL_L, 1);
			idxRow = 7;
		break;
		case "ATTRIBUTES_S_MINUS_BTN":
			DecreasePIRATES(SPECIAL_L, 1);
			idxRow = 7;
		break;
	}

	if (idxRow >= 1)
	{
		Event("TableSelectChange", "sll", "TABLE_SPECIAL", idxRow, 1);
	}
}

void IncreasePIRATES(string name, int _add)
{
	string  sSkillName;

    sSkillName = name;

	if (sti(pchar.skill.FreeSPECIAL) < _add) _add = sti(pchar.skill.FreeSPECIAL);
	if ((GetSkillValue(pchar, SPECIAL_TYPE, sSkillName) + _add) > SPECIAL_MAX)
	{
		_add = SPECIAL_MAX - GetSkillValue(pchar, SPECIAL_TYPE, sSkillName);
	}
	if (_add > 0)
	{
		AddSPECIALValue(pchar, sSkillName, _add);
		pchar.skill.FreeSPECIAL = sti(pchar.skill.FreeSPECIAL) - _add;
	}
	else return;

	SetHeroParamPIRATES_FromMainCharacter();
	RefreshSkills();
	RefreshPIRATES();
}

void DecreasePIRATES(string name, int _add)
{
	string  sSkillName;

    sSkillName = name;

	if (GetSkillValue(pchar, SPECIAL_TYPE, sSkillName) <= _add)
	{
		_add = GetSkillValue(pchar, SPECIAL_TYPE, sSkillName) - 1;
	}
	if (_add > 0)
	{
		AddSPECIALValue(pchar, sSkillName, -_add);
		pchar.skill.FreeSPECIAL = sti(pchar.skill.FreeSPECIAL) + _add;
	}
	else return;

	SetHeroParamPIRATES_FromMainCharacter();
	RefreshSkills();
	RefreshPIRATES();
}

void ShowSkillsWindow(bool show)
{
	if (show)
	{
		XI_WindowShow("SKILLS_WINDOW", true);
		XI_WindowDisable("SKILLS_WINDOW", false);
	}
	else
	{
		XI_WindowShow("SKILLS_WINDOW", false);
		XI_WindowDisable("SKILLS_WINDOW", true);
	}
}

void ShowConfirmWindow(bool show)
{
	if (show)
	{
		SetCurrentNode("CONFIRM_WINDOW_MB_NO");

		XI_WindowDisable("MAIN_WINDOW", true);
		XI_WindowDisable("PERSON_WINDOW", true);
		XI_WindowDisable("TYPES_WINDOW", true);
		XI_WindowDisable("NATION_WINDOW", true);
		XI_WindowDisable("ATTRIBUTES_WINDOW", true);
		XI_WindowDisable("SKILLS_WINDOW", true);
		XI_WindowDisable("OTHERS_WINDOW", true);

		XI_WindowDisable("CONFIRM_WINDOW", false);
		XI_WindowShow("CONFIRM_WINDOW", true);
		EI_CreateFrame("CONFIRM_WINDOW_BORDERS",190,190,610,360);
	}
	else
	{
		XI_WindowDisable("MAIN_WINDOW", false);
		XI_WindowDisable("PERSON_WINDOW", false);
		XI_WindowDisable("TYPES_WINDOW", false);
		XI_WindowDisable("NATION_WINDOW", false);
		XI_WindowDisable("ATTRIBUTES_WINDOW", false);
		XI_WindowDisable("SKILLS_WINDOW", false);
		XI_WindowDisable("OTHERS_WINDOW", false);

		XI_WindowDisable("CONFIRM_WINDOW", true);
		XI_WindowShow("CONFIRM_WINDOW", false);
		XI_WindowDisable("MAIN_WINDOW", false);
		SetCurrentNode("OK_BUTTON");
	}
}

//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
void CreateProfileFolders()
{
	string folder = GameInterface.SavePath + "\";
	folder+= pchar.profile.name;

	if (XI_CheckFolder(folder)) return;

	if(!XI_CreateFolder(folder))
		trace("Could not create profile folder");
}
//----------------------------------------------------------------------------------------------------
void DeleteProfile()
{
	string folder;

	folder = GameInterface.SavePath + "\"+ pchar.profile.name;

	int nSaveNum= 0;
	string saveName;
	int nSaveSize;

	string path = GameInterface.SavePath;
	GameInterface.SavePath = folder;

    while (SendMessage(&GameInterface,"llee",MSG_INTERFACE_SAVE_FILE_FIND,nSaveNum,&saveName,&nSaveSize)!=0)
    {
		nSaveNum++;
		SendMessage(&GameInterface,"ls",MSG_INTERFACE_DELETE_SAVE_FILE,saveName);
    }

	GameInterface.SavePath = path;
	XI_DeleteFolder(folder);
}
//----------------------------------------------------------------------------------------------------
bool ProfileExists()
{
	string folder = GameInterface.SavePath + "\";

	folder+= pchar.profile.name;

	return (XI_CheckFolder(folder));
}
//----------------------------------------------------------------------------------------------------
//
//----------------------------------------------------------------------------------------------------
void SelectNation(int iNation)
{
	/////////////////////////////////////////////////////
	string sNationPict;
	bool bSwitchEnable = IsFreeplayModeStart();
	int disableFlagColor = argb(255,96,96,96);
	int disableCaptionColor = argb(255,255,255,255);
	if (!bSwitchEnable)
	{
		disableFlagColor = argb(156,96,48,48);
		disableCaptionColor = argb(200,128,128,128);
	}
	for (int i=0; i<MAX_NATIONS; i++)
	{
		sNationPict = GetNationNameByType(i);

		SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNationPict, 4, disableFlagColor);
		SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,"NATION_SELECT_BACK", 4, i, "empty");
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"NATIONS_FRAME_CAPTIONS", 3, i+1, disableCaptionColor);
	}

	for (int iNation1 = 0; iNation1<MAX_NATIONS; iNation1++)
	{
		int rel = GetNationRelation(iNation, iNation1);
		if (rel == RELATION_ENEMY)
		{
			SendMessage( &GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,"NATION_RELATION_ICONS", 4, iNation1, "Enemy");
		}
		else
		{
			SendMessage( &GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,"NATION_RELATION_ICONS", 4, iNation1, "Friend");
		}
	}

	sNationPict = GetNationNameByType(iNation);
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE,sNationPict, 4, argb(255,128,128,128));
	SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,"NATION_SELECT_BACK", 4, iNation, "SelectionLight");
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"NATIONS_FRAME_CAPTIONS", 3, iNation+1, argb(255,255,255,255));
	/////////////////////////////////////////////////////
	NullCharacter.HeroParam.Nation = iNation;
	if (iCurWindow == SELCHAR_NATION_WINDOW)
	{
	    NationBonusShow(sti(NullCharacter.HeroParam.Nation) == PIRATE);
	}
	SetNationDifficultText();

	SetHeroParam_Items();
	DiscardItemsTablePagination();
	RefreshEquipmentTable();

	SetHeroParam_Perks();
	RefreshPerksTable();

	SetHeroParam_Ship();
	RefreshShipInfo();
}

void selectEngland()
{
	if (IsFreeplayModeStart())
	{
	    SelectNation(ENGLAND);
	}
	else
	{
	    SelectNation(sti(NullCharacter.HeroParam.nation));
	}
}

void selectFrance()
{
	if (IsFreeplayModeStart())
	{
	    SelectNation(FRANCE);
	}
	else
	{
	    SelectNation(sti(NullCharacter.HeroParam.nation));
	}
}

void selectSpain()
{
	if (IsFreeplayModeStart())
	{
	    SelectNation(SPAIN);
	}
	else
	{
	    SelectNation(sti(NullCharacter.HeroParam.nation));
	}
}

void selectHolland()
{
	if (IsFreeplayModeStart())
	{
	    SelectNation(HOLLAND);
	}
	else
	{
	    SelectNation(sti(NullCharacter.HeroParam.nation));
	}
}

void selectPirate()
{
	if (IsFreeplayModeStart())
	{
	    SelectNation(PIRATE);
	}
	else
	{
	    SelectNation(sti(NullCharacter.HeroParam.nation));
	}
}

void IDoExit(int exitCode, bool bCode)
{
	DelEventHandler("exitCancel", "exitCancel");
	DelEventHandler("selectEngland", "selectEngland");
	DelEventHandler("selectFrance", "selectFrance");
	DelEventHandler("selectSpain", "selectSpain");
	DelEventHandler("selectHolland", "selectHolland");
	DelEventHandler("selectPirate", "selectPirate");
	DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("HideInfoWindow","HideInfo");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("eChangePiratesBtn","ProcessChangePiratesBtn");

	DelEventHandler("noteOk","procNoteOk");

	DelEventHandler("frame","IProcessFrame");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	MenuVolume_Stop();

	if(isOkExit == false)
	{
		EndCancelInterface(bCode); // > уровень приглушения ушёл в TEV, доведёт его главное меню
	}
	else
	{
		MenuVolume_Restore(); // > дальше игра, приглушение снимаем сразу
		DeleteAttributeEx(&TEV, "MAINMENU,MENUVOLUME");
		StopMusic(0);
		ResetSound();
        MOD_EXP_RATE = makeint(5 + 10.0 * (1.0 - stf(GameInterface.nodes.EXP_SLIDE.value)));  // 0т 5 до 15
		trace("MOD_EXP_RATE = " + MOD_EXP_RATE);
		interfaceResultCommand = exitCode;
		EndCancelInterface(bCode);
	}
}

void confirmChangeProfileName()
{
	PlayerProfile.name = GameInterface.PROFILE_NAME.str;
	pchar.profile.name = GameInterface.PROFILE_NAME.str;
}

void confirmChangeProfilePass()
{
	PlayerProfile.password = GameInterface.PROFILE_PASS.str;
	pchar.profile.pass = GameInterface.PROFILE_PASS.str;
	SetCurrentNode("OK_BUTTON");
}

void ShowInfoWindow()
{
	string sHeader = "TEST";
//	string sNode = GetCurrentNode();
	string sNode = GetEventData();

	int nChooseNum;
	string sRow, sCol;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	switch(sNode)
	{
		case "CHECK_ENCOUNTERS":
			sHeader = XI_ConvertString("EncountersRate");
			sText1 = GetRPGText("EncountersRate_desc");
		break;

		case "CHECK_ARCADESAIL":
			sHeader = XI_ConvertString("Sailing Mode");
			sText1 = GetRPGText("ArcadeSailMode_desc");
		break;

		case "CHECK_PISTOL":
			sHeader = XI_ConvertString("New Fight Mode");
			sText1 = GetRPGText("RechargePistolOnLine_desc");
		break;

		case "CHECK_HARDCORE":
			sHeader = XI_ConvertString("HardcoreGame");
			sText1 = GetRPGText("HardcoreGame_desc");
		break;

		case "CHECK_PARTITION":
			sHeader = XI_ConvertString("Partition");
			sText1 = GetRPGText("Partition_hint");
		break;

		case "CHECK_WILD":
			sHeader = XI_ConvertString("WildCaribbean");
			sText1 = GetRPGText("WildCaribbean_desc");
		break;

		case "EXP_SLIDE":
			sHeader = GetRPGText("EXP_SLIDE");
			sText1 = GetRPGText("EXP_SLIDE_desc");
		break;

		case "TABLE_TRAITS":
			CloseTooltipNew();
			nChooseNum = sti(SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_TRAITS", 1)) + 1;
			sRow = "tr"+nChooseNum;

			if (!CheckAttribute(&GameInterface, "TABLE_TRAITS."+sRow+".UserData.ID"))
				return;
		    sHeader = GetConvertStr(GameInterface.TABLE_TRAITS.(sRow).UserData.ID, "AbilityDescribe.txt");
		    sText1 = GetConvertStr("perk" + GameInterface.TABLE_TRAITS.(sRow).UserData.ID, "AbilityDescribe.txt");
		break;

		case "TABLE_EQUIPMENT":
			CloseTooltipNew();
			nChooseNum = sti(SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_EQUIPMENT", 1)) + 1;
			sRow = "tr"+nChooseNum;
			nChooseNum = sti(SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_EQUIPMENT", 3)) + 1;
			sCol = "td"+nChooseNum;

			if (!CheckAttribute(&GameInterface, "TABLE_EQUIPMENT."+sRow+"."+sCol+".UserData.ID"))
				return;

			string sItemId = GameInterface.TABLE_EQUIPMENT.(sRow).(sCol).UserData.ID;
			ref rItem = ItemsFromID(sItemId);
		    sHeader = GetItemName(rItem.id);
		    sText1 = GetItemDescribe(sti(rItem.index), PChar);
			sGroup = rItem.picTexture;
			sGroupPicture = "itm" + rItem.picIndex;
		break;

		case "TABLE_PERKS":
			CloseTooltipNew();
			nChooseNum = sti(SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_PERKS", 1)) + 1;
			sRow = "tr"+nChooseNum;
			nChooseNum = sti(SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_PERKS", 3)) + 1;
			sCol = "td"+nChooseNum;

			if (!CheckAttribute(&GameInterface, "TABLE_PERKS."+sRow+"."+sCol+".UserData.ID"))
				return;

			string sPerkName = GameInterface.TABLE_PERKS.(sRow).(sCol).UserData.ID;
		    sHeader = GetConvertStr(sPerkName, "AbilityDescribe.txt");
		    sText1 = GetConvertStr("perk"+sPerkName, "AbilityDescribe.txt");
			sGroup = "PERK_ENABLE";
			sGroupPicture = sPerkName;
		break;

		case "SHIP_BACK":
			aref shipObj;
			makearef(shipObj, NullCharacter.HeroParam.Ship);

			if (!CheckAttribute(shipObj, "id"))
			{
				return;
			}

			ref refShipType = GetShipByType(sti(shipObj.id));
			string sShip = refShipType.Name;

			sHeader = XI_ConvertString(sShip);
		    sText1 = GetConvertStr(sShip, "ShipsDescribe.txt");

			sGroup = "";
			sGroupPicture = "";
			sPicture = "interfaces\ships\" + sShip + ".tga";
		break;

		case "TABLE_SPECIAL":
			CloseTooltipNew();
			nChooseNum = sti(SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_SPECIAL", 1)) + 1;
			sRow = "tr"+nChooseNum;

		    sHeader = XI_ConvertString("Characteristics");
		    sText1  = GetRPGText(GameInterface.TABLE_SPECIAL.(sRow).UserData.ID + "_hint");
		break;

		case "TABLE_PERSON_SKILLS":
			CloseTooltipNew();
			nChooseNum = sti(SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_PERSON_SKILLS", 1)) + 1;
			sRow = "tr"+nChooseNum;

			sHeader = XI_ConvertString(GameInterface.TABLE_PERSON_SKILLS.(sRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.TABLE_PERSON_SKILLS.(sRow).UserData.ID + "_hint");
		break;

		case "TABLE_SHIP_SKILLS":
		    CloseTooltipNew();
			nChooseNum = sti(SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_SHIP_SKILLS", 1)) + 1;
			sRow = "tr"+nChooseNum;

			sHeader = XI_ConvertString(GameInterface.TABLE_SHIP_SKILLS.(sRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.TABLE_SHIP_SKILLS.(sRow).UserData.ID + "_hint");
		break;

		case "TABLE_STATS":
		    CloseTooltipNew();
			nChooseNum = sti(SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_STATS", 1)) + 1;
			sRow = "tr"+nChooseNum;

			sHeader = XI_ConvertString(GameInterface.TABLE_STATS.(sRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.TABLE_STATS.(sRow).UserData.ID + "_hint");
		break;

		case "ENGLAND":
			sHeader = XI_ConvertString("England");
			sText1 = GetRPGText(Nations[ENGLAND].Name + "_descr");
			if (!IsFreePlayModeStart())
				sText2 = XI_ConvertString("SelChar_StoryDesc");
		break;

		case "FRANCE":
			sHeader = XI_ConvertString("France");
			sText1 = GetRPGText(Nations[FRANCE].Name + "_descr");
			if (!IsFreePlayModeStart())
				sText2 = XI_ConvertString("SelChar_StoryDesc");
		break;

		case "SPAIN":
			sHeader = XI_ConvertString("Spain");
			sText1 = GetRPGText(Nations[SPAIN].Name + "_descr");
			if (!IsFreePlayModeStart())
				sText2 = XI_ConvertString("SelChar_StoryDesc");
		break;

		case "HOLLAND":
			sHeader = XI_ConvertString("Holland");
			sText1 = GetRPGText(Nations[HOLLAND].Name + "_descr");
			if (!IsFreePlayModeStart())
				sText2 = XI_ConvertString("SelChar_StoryDesc");
		break;

		case "PIRATE":
			sHeader = XI_ConvertString("Pirate");
			sText1 = GetRPGText(Nations[PIRATE].Name + "_descr");
			if (!IsFreePlayModeStart())
				sText2 = XI_ConvertString("SelChar_StoryDesc");
		break;
	}

//	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
	CreateTooltipNew(sNode, sHeader, sText1, sText2, sText3, "", sPicture, sGroup, sGroupPicture, 64, 64);
}

void HideInfo()
{
	CloseTooltipNew();
}

void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	if (sNodName == "TABBTN_PERSON")
	{
		iCurWindow = SELCHAR_PERSON_WINDOW;
		UpdateVisibleElements();
		return;
	}
	if (sNodName == "TABBTN_NATION")
	{
		iCurWindow = SELCHAR_NATION_WINDOW;
		UpdateVisibleElements();
		return;
	}
	if (sNodName == "TABBTN_EQUIP")
	{
		iCurWindow = SELCHAR_EQUIP_WINDOW;
		UpdateVisibleElements();
		return;
	}
	if (sNodName == "TABBTN_ATTRIBUTES")
	{
		iCurWindow = SELCHAR_ATTRIBUTES_WINDOW;
		UpdateVisibleElements();
		return;
	}
	if (sNodName == "TABBTN_DIFFICULT")
	{
		iCurWindow = SELCHAR_DIFFICULT_WINDOW;
		UpdateVisibleElements();
		return;
	}
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
	int iCol = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    CurCol   =  "td" + (iCol);

 	NullSelectTable("TABLE_TRAITS");
    NullSelectTable("TABLE_EQUIPMENT");
    NullSelectTable("TABLE_PERKS");
 	NullSelectTable("TABLE_SPECIAL");
    NullSelectTable("TABLE_PERSON_SKILLS");
    NullSelectTable("TABLE_SHIP_SKILLS");
    NullSelectTable("TABLE_STATS");

    if (CurTable == "TABLE_SPECIAL")
	{
		DoSelectDependTableSkillsRows();
		DoSelectActivePiratesRow(iSelected);
	}
}

void NullSelectTable(string sControl)
{
	if (sControl != CurTable)
	{
	    GameInterface.(sControl).select = 0;
	    Table_UpdateWindow(sControl);
	}
}

void ProcessCommandExecuteLeft()
{
    if (startHeroType > 1)
    {
       startHeroType--;
    }
    else
    {
       startHeroType = heroQty;
    }
    SetVariable(true);
	SelectOperation();
	SelectCharacter();
	SetNodeState_InfoChar();
}

void ProcessCommandExecuteRight()
{
    if (startHeroType < heroQty)
    {
       startHeroType++;
    }
    else
    {
       startHeroType = 1;
    }
    SetVariable(true);
	SelectOperation();
	SelectCharacter();
	SetNodeState_InfoChar();
}

void ProcessCommandBackButton(int numWindow)
{
    if (numWindow > 1)
    {
		iCurWindow--;
		UpdateVisibleElements();
    }
    else
	{
	    exitCancel();
	}
}

void ProcessCommandNextButton(int numWindow)
{
    if (numWindow < SELCHAR_MAX_WINDOWS)
    {
		iCurWindow++;
		UpdateVisibleElements();
    }
	else
    {
		if( !IsCorrectProfileName() )
		{
			ShowNoteText(true);
			return;
		}
		confirmChangeProfileName();
		if (!ProfileExists())
		{
			CreateProfileFolders();
			StartTheGame();
		}
		else
		{
			ShowConfirmWindow(true);
		}
    }
}

void UpdateVisibleElements()
{
	ShowSkillsWindow(false);

	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BACK_BUTTON1",0, "#"+XI_ConvertString("Back"));
	SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"NEXT_BUTTON1",0, "#"+XI_ConvertString("btnEG_Ok"));

	if (iCurWindow == SELCHAR_PERSON_WINDOW)
	{
		XI_WindowShow("PERSON_WINDOW", true);
		XI_WindowDisable("PERSON_WINDOW", false);
		XI_WindowShow("TYPES_WINDOW", false);
		XI_WindowShow("NATION_WINDOW", false);
		XI_WindowShow("ATTRIBUTES_WINDOW", false);
		XI_WindowShow("OTHERS_WINDOW", false);

		SetNodeState_InfoChar();
		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"BACK_BUTTON1",0, "#"+XI_ConvertString("Cancel"));
	}
	else if (iCurWindow == SELCHAR_NATION_WINDOW)
	{
		XI_WindowShow("NATION_WINDOW", true);
		XI_WindowDisable("NATION_WINDOW", false);
		XI_WindowShow("TYPES_WINDOW", false);
		XI_WindowShow("PERSON_WINDOW", false);
		XI_WindowShow("ATTRIBUTES_WINDOW", false);
		XI_WindowShow("OTHERS_WINDOW", false);

		NationBonusShow(sti(NullCharacter.HeroParam.nation) == PIRATE);
	}
	else if (iCurWindow == SELCHAR_EQUIP_WINDOW)
	{
		XI_WindowShow("TYPES_WINDOW", true);
		XI_WindowDisable("TYPES_WINDOW", false);
		XI_WindowShow("PERSON_WINDOW", false);
		XI_WindowShow("NATION_WINDOW", false);
		XI_WindowShow("ATTRIBUTES_WINDOW", false);
		XI_WindowShow("OTHERS_WINDOW", false);

		RefreshEquipmentTable();
	}
	else if (iCurWindow == SELCHAR_ATTRIBUTES_WINDOW)
	{
		XI_WindowShow("ATTRIBUTES_WINDOW", true);
		XI_WindowDisable("ATTRIBUTES_WINDOW", false);
		XI_WindowShow("PERSON_WINDOW", false);
		XI_WindowShow("TYPES_WINDOW", false);
		XI_WindowShow("NATION_WINDOW", false);
		XI_WindowShow("OTHERS_WINDOW", false);

		ShowSkillsWindow(bShowSkills);
	}
	else if (iCurWindow == SELCHAR_DIFFICULT_WINDOW)
	{
		XI_WindowShow("OTHERS_WINDOW", true);
		XI_WindowDisable("OTHERS_WINDOW", false);
		XI_WindowShow("TYPES_WINDOW", false);
		XI_WindowShow("NATION_WINDOW", false);
		XI_WindowShow("PERSON_WINDOW", false);
		XI_WindowShow("ATTRIBUTES_WINDOW", false);

		SendMessage(&GameInterface,"lsls",MSG_INTERFACE_MSG_TO_NODE,"NEXT_BUTTON1",0, "#"+XI_ConvertString("Start"));
	}
}

void SetVariable(bool _init)
{
	bool bStoryMode = false;
    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    SetFormatedText("HERO_NAME", GetNewMainCharacterName());
    if (_init)
    {
    	NullCharacter.HeroParam.HeroType = GetNewMainCharacterType(startHeroType);
    	NullCharacter.HeroParam.nation = GetNewMainCharacterNation(startHeroType);
	}

	SetSelectable("LEFTCHANGE_STORY", true);
	SetSelectable("RIGHTCHANGE_STORY", true);
	// Для этих героев смена сюжет-фриплей недоступна
	if (startHeroType > 3)
	{
		SetSelectable("LEFTCHANGE_STORY", false);
		SetSelectable("RIGHTCHANGE_STORY", false);
	}

	if (startHeroType == 1) //HardCoffee fix иначе нация для этих персонажей загрузится из последнего профиля
	{
		NullCharacter.HeroParam.nation = ENGLAND;
		bStoryMode = true;
	}
	else if (startHeroType == 2)
	{
		NullCharacter.HeroParam.nation = FRANCE;
		bStoryMode = true;
	}
	else if (startHeroType == 3) // Эммануэль Пардаль
	{
		NullCharacter.HeroParam.nation = SPAIN;
		bStoryMode = true;
	}
	if (bStoryMode)
	{
		NullCharacter.HeroParam.FreeplayMode = false;
    	SetFormatedText("STORY_TITLE", XI_ConvertString("SelChar_Story"));
    	SetFormatedText("STORY_INFO", XI_ConvertString("SelChar_StoryDesc"));
	}
	else
	{
		NullCharacter.HeroParam.FreeplayMode = true;
	    SetFormatedText("STORY_TITLE", XI_ConvertString("SelChar_Freeplay"));
	    SetFormatedText("STORY_INFO", XI_ConvertString("SelChar_FreeplayDesc"));
	}

    SetNewPicture("FACEPICT", "interfaces\portraits\256\face_" + GetNewMainCharacterFace() + ".tga");
    SelectNation(sti(NullCharacter.HeroParam.nation));
	SetNationBonusText();
    infoCharStr = LanguageConvertString(idLngFile, "hero_" + startHeroType);
	MainChAnim = LanguageConvertString(idLngFile, "animation_" + startHeroType);
	SetInfoText();
	RefreshCharType();
    LanguageCloseFile(idLngFile);
}

string GetCharacterTypeFromNode(string nodeName)
{
	return FindStringBeforeSubstr(nodeName, "_TYPE");
}

void SetMainCharacterPIRATES_ByHeroType(string sType)
{
	DeleteAttribute(&NullCharacter, "HeroParam.Pirates");
	aref piratesObj;
	makearef(piratesObj, NullCharacter.HeroParam.Pirates);

	switch (sType)
	{
		case "Adventurer":
			piratesObj.P = 5;
			piratesObj.I = 7;
			piratesObj.R = 6;
			piratesObj.A = 4;
			piratesObj.T = 6;
			piratesObj.E = 6;
			piratesObj.S = 8;
		break;

		case "Corsair":
			piratesObj.P = 7;
			piratesObj.I = 6;
			piratesObj.R = 9;
			piratesObj.A = 3;
			piratesObj.T = 5;
			piratesObj.E = 6;
			piratesObj.S = 6;
		break;

		case "Merchant":
			piratesObj.P = 4;
			piratesObj.I = 9;
			piratesObj.R = 3;
			piratesObj.A = 8;
			piratesObj.T = 9;
			piratesObj.E = 5;
			piratesObj.S = 4;
		break;

		case "Master":
			piratesObj.P = 8;
			piratesObj.I = 5;
			piratesObj.R = 5;
			piratesObj.A = 5;
			piratesObj.T = 7;
			piratesObj.E = 7;
			piratesObj.S = 5;
		break;

		case "Inquisitor":
			piratesObj.P = 6;
			piratesObj.I = 5;
			piratesObj.R = 6;
			piratesObj.A = 9;
			piratesObj.T = 6;
			piratesObj.E = 5;
			piratesObj.S = 5;
		break;

		case "SecretAgent":
			piratesObj.P = 6;
			piratesObj.I = 6;
			piratesObj.R = 6;
			piratesObj.A = 6;
			piratesObj.T = 6;
			piratesObj.E = 6;
			piratesObj.S = 6;
		break;
	}

	if (CheckAttribute(piratesObj, "P"))
	{
		SetSPECIAL(pchar,
			piratesObj.P,
			piratesObj.I,
			piratesObj.E,
			piratesObj.A,
			piratesObj.T,
			piratesObj.R,
			piratesObj.S);
		pchar.skill.FreeSPECIAL = 0;

		piratesObj.FreePIRATES = 0;
	}
	else
	{
		SetSPECIAL(pchar, 4, 4, 4, 4, 4, 4, 4); //фикс для любителей стирать тип ГГ в файле - была дыра
		pchar.skill.FreeSPECIAL = 14;
		SetHeroParamPIRATES_FromMainCharacter();
	}
}

void SetHeroParamPIRATES_FromMainCharacter()
{
	aref piratesObj;
	makearef(piratesObj, NullCharacter.HeroParam.Pirates);

	piratesObj.P = GetSkillValue(PChar, SPECIAL_TYPE, SPECIAL_S);
	piratesObj.I = GetSkillValue(PChar, SPECIAL_TYPE, SPECIAL_P);
	piratesObj.R = GetSkillValue(PChar, SPECIAL_TYPE, SPECIAL_A);
	piratesObj.A = GetSkillValue(PChar, SPECIAL_TYPE, SPECIAL_C);
	piratesObj.T = GetSkillValue(PChar, SPECIAL_TYPE, SPECIAL_I);
	piratesObj.E = GetSkillValue(PChar, SPECIAL_TYPE, SPECIAL_E);
	piratesObj.S = GetSkillValue(PChar, SPECIAL_TYPE, SPECIAL_L);

	piratesObj.FreePIRATES = pchar.skill.FreeSPECIAL;
}

void DiscardPIRATES(string sType)
{
	SetMainCharacterPIRATES_ByHeroType(sType);

	RefreshPIRATES();
	RefreshSkills();
}

void RefreshSkills()
{
	string row, skillName;
	int skillVal, i;

	InitStartParam(pchar);
	SetEnergyToCharacter(pchar);

	aref rDepObj, rAttr;
	string depPIRATES_Name;
	bool bTableSpecialSelected = false;
	int n;

	for (i=1; i<=7; i++)
	{
		row = "tr" + i;
		DeleteAttribute(&GameInterface, "TABLE_PERSON_SKILLS." + row);
		DeleteAttribute(&GameInterface, "TABLE_SHIP_SKILLS." + row);
	}
	for (i=1; i<=3; i++)
	{
		row = "tr" + i;
		DeleteAttribute(&GameInterface, "TABLE_STATS." + row);
	}

	GameInterface.TABLE_PERSON_SKILLS.select = 0;
	for (i=1; i<=7; i++)
	{
		row = "tr" + i;
		skillName = GetSkillNameByTRIdx("SelfType", i);

		GameInterface.TABLE_PERSON_SKILLS.(row).UserData.ID = skillName;
		GameInterface.TABLE_PERSON_SKILLS.(row).td1.icon1.group = "ICONS_SPEC";
	    GameInterface.TABLE_PERSON_SKILLS.(row).td1.icon1.image = skillName + " skill icon";
	    GameInterface.TABLE_PERSON_SKILLS.(row).td1.icon1.width = 30;
    	GameInterface.TABLE_PERSON_SKILLS.(row).td1.icon1.height = 30;

		GameInterface.TABLE_PERSON_SKILLS.(row).td2.fontidx = 1;
		GameInterface.TABLE_PERSON_SKILLS.(row).td2.align = "left";
		GameInterface.TABLE_PERSON_SKILLS.(row).td2.textoffset = "6,0";
		GameInterface.TABLE_PERSON_SKILLS.(row).td2.scale = 0.9;

		GameInterface.TABLE_PERSON_SKILLS.(row).td3.fontidx = 0;
		GameInterface.TABLE_PERSON_SKILLS.(row).td3.scale = 0.8;
		GameInterface.TABLE_PERSON_SKILLS.(row).td3.textoffset = "-3,0";

		GameInterface.TABLE_PERSON_SKILLS.(row).td1.str = "";
		GameInterface.TABLE_PERSON_SKILLS.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(PChar, SKILL_TYPE, skillName);
		GameInterface.TABLE_PERSON_SKILLS.(row).td3.str = skillVal;
	}

	Table_UpdateWindow("TABLE_PERSON_SKILLS");

	GameInterface.TABLE_SHIP_SKILLS.select = 0;
	for (i=1; i<=7; i++)
	{
		row = "tr" + i;
		skillName = GetSkillNameByTRIdx("ShipType", i);

		GameInterface.TABLE_SHIP_SKILLS.(row).UserData.ID = skillName;
		GameInterface.TABLE_SHIP_SKILLS.(row).td1.icon1.group = "ICONS_SPEC";
	    GameInterface.TABLE_SHIP_SKILLS.(row).td1.icon1.image = skillName + " skill icon";
	    GameInterface.TABLE_SHIP_SKILLS.(row).td1.icon1.width = 30;
    	GameInterface.TABLE_SHIP_SKILLS.(row).td1.icon1.height = 30;

		GameInterface.TABLE_SHIP_SKILLS.(row).td2.fontidx = 1;
		GameInterface.TABLE_SHIP_SKILLS.(row).td2.align = "left";
		GameInterface.TABLE_SHIP_SKILLS.(row).td2.textoffset = "6,0";
		GameInterface.TABLE_SHIP_SKILLS.(row).td2.scale = 0.9;

		GameInterface.TABLE_SHIP_SKILLS.(row).td3.fontidx = 0;
		GameInterface.TABLE_SHIP_SKILLS.(row).td3.scale = 0.8;
		GameInterface.TABLE_SHIP_SKILLS.(row).td3.textoffset = "-3,0";

		GameInterface.TABLE_SHIP_SKILLS.(row).td1.str = "";
		GameInterface.TABLE_SHIP_SKILLS.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(PChar, SKILL_TYPE, skillName);
		GameInterface.TABLE_SHIP_SKILLS.(row).td3.str = skillVal;
	}

	Table_UpdateWindow("TABLE_SHIP_SKILLS");

	GameInterface.TABLE_STATS.select = 0;
	for (i=1; i<=3; i++)
	{
		row = "tr" + i;
		GameInterface.TABLE_STATS.(row).td1.icon1.width = 24;
		GameInterface.TABLE_STATS.(row).td1.icon1.height = 24;

		GameInterface.TABLE_STATS.(row).td2.align = "left";
		GameInterface.TABLE_STATS.(row).td2.textoffset = "6,0";
	}
	GameInterface.TABLE_STATS.tr1.UserData.ID = "Life";
	GameInterface.TABLE_STATS.tr1.td1.icon1.group = "ICONS_CHAR";
	GameInterface.TABLE_STATS.tr1.td1.icon1.image = "Life";

	GameInterface.TABLE_STATS.tr1.td2.str = XI_ConvertString("Life");
	GameInterface.TABLE_STATS.tr1.td3.str = MakeInt(LAi_GetCharacterHP(pchar)) + " / " + MakeInt(LAi_GetCharacterMaxHP(pchar));

	GameInterface.TABLE_STATS.tr2.UserData.ID = "Energy";
	GameInterface.TABLE_STATS.tr2.td1.icon1.group = "ICONS_CHAR";
	GameInterface.TABLE_STATS.tr2.td1.icon1.image = "Energy";
	GameInterface.TABLE_STATS.tr2.td2.str = XI_ConvertString("Energy");
	GameInterface.TABLE_STATS.tr2.td3.str = MakeInt(LAi_GetCharacterMaxEnergy(pchar)) + " / " + MakeInt(LAi_GetCharacterMaxEnergy(pchar));

	GameInterface.TABLE_STATS.tr3.UserData.ID = "weight";
	GameInterface.TABLE_STATS.tr3.td1.icon1.group = "ICONS_CHAR";
	GameInterface.TABLE_STATS.tr3.td1.icon1.image = "weight";
	GameInterface.TABLE_STATS.tr3.td2.str = XI_ConvertString("weight");
	GameInterface.TABLE_STATS.tr3.td3.str = GetMaxItemsWeight(pchar);

	Table_UpdateWindow("TABLE_STATS");
}

void DoSelectDependTableSkillsRows()
{
	string row;
	int i;

	aref rDepObj, rAttr;
	string depPIRATES_Name;
	bool bTableSpecialSelected = false;
	int n;
	float fRate;

	for (i=1; i<=7; i++)
	{
		row = "tr" + i;
		DeleteAttribute(&GameInterface, "TABLE_PERSON_SKILLS." + row + ".td1.icon2");
		DeleteAttribute(&GameInterface, "TABLE_PERSON_SKILLS." + row + ".td2.color");
		DeleteAttribute(&GameInterface, "TABLE_PERSON_SKILLS." + row + ".td3.color");
		DeleteAttribute(&GameInterface, "TABLE_SHIP_SKILLS." + row + ".td1.icon2");
		DeleteAttribute(&GameInterface, "TABLE_SHIP_SKILLS." + row + ".td2.color");
		DeleteAttribute(&GameInterface, "TABLE_SHIP_SKILLS." + row + ".td3.color");
	}
	for (i=1; i<=3; i++)
	{
		row = "tr" + i;
		DeleteAttribute(&GameInterface, "TABLE_STATS." + row + ".td1.icon2");
		DeleteAttribute(&GameInterface, "TABLE_STATS." + row + ".td2.color");
		DeleteAttribute(&GameInterface, "TABLE_STATS." + row + ".td3.color");
	}

	if (CurTable == "TABLE_SPECIAL")
	{
		bTableSpecialSelected = true;
	    depPIRATES_Name = GameInterface.TABLE_SPECIAL.(CurRow).UserData.ID;
	}

	if (bTableSpecialSelected)
	{
		makearef(rDepObj, PIRATES_DependObj.(depPIRATES_Name).skills_p);
		n = GetAttributesNum(rDepObj);

		for (i = 0; i < n; i++)
		{
			rAttr = GetAttributeN(rDepObj, i);
			row = "tr" + GetIdxByStatName(GetAttributeValue(rAttr));
			GameInterface.TABLE_PERSON_SKILLS.(row).td2.color = argb(255,240,230,140);
			GameInterface.TABLE_PERSON_SKILLS.(row).td3.color = argb(255,240,230,140);

			fRate = stf(rAttr.rate);
			GameInterface.TABLE_PERSON_SKILLS.(row).td1.icon2.group = "RECON_SELECT_CHARACTER";
			GameInterface.TABLE_PERSON_SKILLS.(row).td1.icon2.image = "StatDepend" + GetDependingStringByRate(fRate);
			GameInterface.TABLE_PERSON_SKILLS.(row).td1.icon2.width = 15;
			GameInterface.TABLE_PERSON_SKILLS.(row).td1.icon2.height = 15;
			GameInterface.TABLE_PERSON_SKILLS.(row).td1.icon2.offset = "21, 0";
		}
	}

	Table_UpdateWindow("TABLE_PERSON_SKILLS");

	if (bTableSpecialSelected)
	{
		makearef(rDepObj, PIRATES_DependObj.(depPIRATES_Name).skills_s);
		n = GetAttributesNum(rDepObj);

		for (i = 0; i < n; i++)
		{
			rAttr = GetAttributeN(rDepObj, i);
			row = "tr" + GetIdxByStatName(GetAttributeValue(rAttr));
			GameInterface.TABLE_SHIP_SKILLS.(row).td2.color = argb(255,240,230,140);
			GameInterface.TABLE_SHIP_SKILLS.(row).td3.color = argb(255,240,230,140);

			fRate = stf(rAttr.rate);
			GameInterface.TABLE_SHIP_SKILLS.(row).td1.icon2.group = "RECON_SELECT_CHARACTER";
			GameInterface.TABLE_SHIP_SKILLS.(row).td1.icon2.image = "StatDepend" + GetDependingStringByRate(fRate);
			GameInterface.TABLE_SHIP_SKILLS.(row).td1.icon2.width = 15;
			GameInterface.TABLE_SHIP_SKILLS.(row).td1.icon2.height = 15;
			GameInterface.TABLE_SHIP_SKILLS.(row).td1.icon2.offset = "21, 0";
		}
	}

	Table_UpdateWindow("TABLE_SHIP_SKILLS");

	if (bTableSpecialSelected)
	{
		makearef(rDepObj, PIRATES_DependObj.(depPIRATES_Name).stats);
		n = GetAttributesNum(rDepObj);

		for (i = 0; i < n; i++)
		{
			rAttr = GetAttributeN(rDepObj, i);
			row = "tr" + GetIdxByStatName(GetAttributeValue(rAttr));
			GameInterface.TABLE_STATS.(row).td2.color = argb(255,240,230,140);
			GameInterface.TABLE_STATS.(row).td3.color = argb(255,240,230,140);

			fRate = stf(rAttr.rate);
			GameInterface.TABLE_STATS.(row).td1.icon2.group = "RECON_SELECT_CHARACTER";
			GameInterface.TABLE_STATS.(row).td1.icon2.image = "StatDepend" + GetDependingStringByRate(fRate);
			GameInterface.TABLE_STATS.(row).td1.icon2.width = 15;
			GameInterface.TABLE_STATS.(row).td1.icon2.height = 15;
			GameInterface.TABLE_STATS.(row).td1.icon2.offset = "21, 0";
		}
	}

	Table_UpdateWindow("TABLE_STATS");
}

string GetDependingStringByRate(float fRate)
{
    if (fRate > 0.66) return "High";
	else if (fRate > 0.33) return "Medium";

	return "Low";
}

void RefreshPIRATES()
{
	string row, skillName;
	int skillVal, i;

	GameInterface.TABLE_SPECIAL.select = 0;
	for (i=1; i<=7; i++)
	{
		row = "tr" + i;
		skillName = GetSkillNameByTRIdx("SPECIALType", i);

		GameInterface.TABLE_SPECIAL.(row).UserData.ID = skillName;
		GameInterface.TABLE_SPECIAL.(row).td1.fontidx = 0;
		GameInterface.TABLE_SPECIAL.(row).td1.scale = 1.3;
		GameInterface.TABLE_SPECIAL.(row).td1.textoffset = "-1,0";

		GameInterface.TABLE_SPECIAL.(row).td2.fontidx = 1;
		GameInterface.TABLE_SPECIAL.(row).td2.align = "left";
		GameInterface.TABLE_SPECIAL.(row).td2.textoffset = "3,0";

		GameInterface.TABLE_SPECIAL.(row).td3.fontidx = 0;
		GameInterface.TABLE_SPECIAL.(row).td3.scale = 1.2;

		GameInterface.TABLE_SPECIAL.(row).td1.str = XI_ConvertString(skillName + "T");
		GameInterface.TABLE_SPECIAL.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(PChar, SPECIAL_TYPE, skillName);
		GameInterface.TABLE_SPECIAL.(row).td3.str = skillVal;
	}
	Table_UpdateWindow("TABLE_SPECIAL");

	SetFormatedText("ATTRIBUTES_BALANCE", pchar.skill.FreeSPECIAL);
}

void DoSelectActivePiratesRow(int iRow)
{
	int idx = iRow - 1;
	for (int i = 0; i < 7; i++)
	{
		SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,"ATTRIBUTES_BACK_SELECTION_PICTURES", 4, i, "empty");
	}

	if (idx >= 0)
	{
		SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,"ATTRIBUTES_BACK_SELECTION_PICTURES", 4, idx, "SelectionLight");
	}
}

void RefreshTraitsTable()
{
	GameInterface.TABLE_TRAITS.select = 0;
	string row, skillName;
	int skillVal, i;
	for (i=1; i<=5; i++)
	{
		row = "tr" + i;
		DeleteAttribute(&GameInterface, "TABLE_TRAITS." + row);

		GameInterface.TABLE_TRAITS.(row).td1.str = "";
		GameInterface.TABLE_TRAITS.(row).td2.str = "";
	}

	GameInterface.TABLE_TRAITS.tr1.UserData.ID = "Energaiser";
	GameInterface.TABLE_TRAITS.tr1.td1.str = "";
	GameInterface.TABLE_TRAITS.tr1.td1.icon.group = "RECON_SELECT_CHARACTER";
	GameInterface.TABLE_TRAITS.tr1.td1.icon.image = "TraitIcon";
	GameInterface.TABLE_TRAITS.tr1.td1.icon.width = 18;
	GameInterface.TABLE_TRAITS.tr1.td1.icon.height = 18;
	GameInterface.TABLE_TRAITS.tr1.td1.icon.offset = "0, 5";

	GameInterface.TABLE_TRAITS.tr1.td2.str = GetConvertStr("Energaiser", "AbilityDescribe.txt");

	if (startHeroType == 2) // Граммон
	{
		GameInterface.TABLE_TRAITS.tr2.UserData.ID = "Nobleman";
		GameInterface.TABLE_TRAITS.tr2.td1.str = "";
		GameInterface.TABLE_TRAITS.tr2.td1.icon.group = "RECON_SELECT_CHARACTER";
		GameInterface.TABLE_TRAITS.tr2.td1.icon.image = "TraitIcon";
		GameInterface.TABLE_TRAITS.tr2.td1.icon.width = 18;
		GameInterface.TABLE_TRAITS.tr2.td1.icon.height = 18;
		GameInterface.TABLE_TRAITS.tr2.td1.icon.offset = "0, 5";

		GameInterface.TABLE_TRAITS.tr2.td2.str = GetConvertStr("Nobleman", "AbilityDescribe.txt");
	}
	else if (HasStrEx(pchar.model.animation, "Danielle,Jessika", "|"))
	{
		GameInterface.TABLE_TRAITS.tr2.UserData.ID = "Dignity";
		GameInterface.TABLE_TRAITS.tr2.td1.str = "";
		GameInterface.TABLE_TRAITS.tr2.td1.icon.group = "RECON_SELECT_CHARACTER";
		GameInterface.TABLE_TRAITS.tr2.td1.icon.image = "TraitIcon";
		GameInterface.TABLE_TRAITS.tr2.td1.icon.width = 18;
		GameInterface.TABLE_TRAITS.tr2.td1.icon.height = 18;
		GameInterface.TABLE_TRAITS.tr2.td1.icon.offset = "0, 5";

		GameInterface.TABLE_TRAITS.tr2.td2.str = GetConvertStr("Dignity", "AbilityDescribe.txt");
	}

	Table_UpdateWindow("TABLE_TRAITS");
}

void RefreshEquipmentTable()
{
	aref itemsObj, curItem;
	ref rItem;
	string col;
	int i, n, nItems, qty, idx;
	int nTotalElements = 0;

	GameInterface.TABLE_EQUIPMENT.select = 0;
	DeleteAttribute(&GameInterface, "TABLE_EQUIPMENT.tr1");
	for (i=1; i<=4; i++)
	{
		col = "td" + i;
		GameInterface.TABLE_EQUIPMENT.tr1.(col).str = "";
		GameInterface.TABLE_EQUIPMENT.tr1.(col).scale = 0.65;
		GameInterface.TABLE_EQUIPMENT.tr1.(col).textoffset = "20,12";

		GameInterface.TABLE_EQUIPMENT.tr1.(col).icon2.group = "RECON_SELECT_CHARACTER_MATERIAL";
		GameInterface.TABLE_EQUIPMENT.tr1.(col).icon2.image = "ListElement";
		GameInterface.TABLE_EQUIPMENT.tr1.(col).icon2.width = 38;
		GameInterface.TABLE_EQUIPMENT.tr1.(col).icon2.height = 38;
		GameInterface.TABLE_EQUIPMENT.tr1.(col).icon2.offset = "-1, 1";
	}

	makearef(itemsObj, NullCharacter.HeroParam.Items);
	nItems = GetAttributesNum(itemsObj);
	nTotalElements = nItems;
	i = 1;
	n = (iCurItemsTablePage - 1) * 4;

	if (CheckAttribute(&NullCharacter, "HeroParam.Money"))
	{
	    nTotalElements += 1;

		if (iCurItemsTablePage == 1 )
		{
	   		i=2;
			rItem = &Items[FindItem("Gold")];

			col = "td" + 1;
			GameInterface.TABLE_EQUIPMENT.tr1.(col).UserData.ID = rItem.id;
			GameInterface.TABLE_EQUIPMENT.tr1.(col).str = NullCharacter.HeroParam.Money;
			GameInterface.TABLE_EQUIPMENT.tr1.(col).icon1.group = rItem.picTexture;
			GameInterface.TABLE_EQUIPMENT.tr1.(col).icon1.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_EQUIPMENT.tr1.(col).icon1.width = 38;
			GameInterface.TABLE_EQUIPMENT.tr1.(col).icon1.height = 38;
			GameInterface.TABLE_EQUIPMENT.tr1.(col).icon1.offset = "-1, 1";
		}
		else
		{
		    n -= 1;
		}
	}

	if (n < 0) n = 0;
	for ( ; i <= 4; i++)
	{
		if (n >= nItems)
		{
		    break;
		}
		curItem = GetAttributeN(itemsObj, n);
		qty = 1;
		if (CheckAttribute(curItem, "qty"))
		{
			qty = sti(curItem.qty);
		}
		idx = FindItem(curItem.id);
		if (idx < 0)
		{
			n++;
		    continue;
		}
		rItem = &Items[idx];

		col = "td" + i;
		if (qty > 1)
		{
			GameInterface.TABLE_EQUIPMENT.tr1.(col).str = its(qty);
		}
		GameInterface.TABLE_EQUIPMENT.tr1.(col).UserData.ID = rItem.id;
		GameInterface.TABLE_EQUIPMENT.tr1.(col).icon1.group = rItem.picTexture;
		GameInterface.TABLE_EQUIPMENT.tr1.(col).icon1.image = "itm" + rItem.picIndex;
		GameInterface.TABLE_EQUIPMENT.tr1.(col).icon1.width = 38;
		GameInterface.TABLE_EQUIPMENT.tr1.(col).icon1.height = 38;
		GameInterface.TABLE_EQUIPMENT.tr1.(col).icon1.offset = "-1, 1";

		n++;
	}

	Table_UpdateWindow("TABLE_EQUIPMENT");
	iItemsTablePageQty = func_max(1, round_up(1.0 * nTotalElements / 4));

	SetFormatedText("EQUIPMENT_TITLE", XI_ConvertString("SelChar_Equipment"));
	if (iItemsTablePageQty > 1)
	{
		SetFormatedText("EQUIPMENT_TITLE", XI_ConvertString("SelChar_Equipment") + " (" +iCurItemsTablePage+"/"+iItemsTablePageQty+ ")");
	}

	if (iCurWindow == SELCHAR_EQUIP_WINDOW)
	{
		SetNodeUsing("EQUIPMENT_PAGE_BACK", false);
		SetNodeUsing("EQUIPMENT_PAGE_NEXT", false);

		if (iCurItemsTablePage > 1)
		{
			SetNodeUsing("EQUIPMENT_PAGE_BACK", true);
		}
		if (iCurItemsTablePage < iItemsTablePageQty)
		{
			SetNodeUsing("EQUIPMENT_PAGE_NEXT", true);
		}
	}
}

void DiscardItemsTablePagination()
{
	iCurItemsTablePage = 1;
}

void RefreshPerksTable()
{
	aref perksObj, curPerk;
	string col;
	int i, n, nPerks, idx;

	GameInterface.TABLE_PERKS.select = 0;
	DeleteAttribute(&GameInterface, "TABLE_PERKS.tr1");

	for (i=1; i<=4; i++)
	{
		col = "td" + i;
		GameInterface.TABLE_PERKS.tr1.(col).str = "";
		GameInterface.TABLE_PERKS.tr1.(col).icon2.group = "RECON_SELECT_CHARACTER_MATERIAL";
		GameInterface.TABLE_PERKS.tr1.(col).icon2.image = "ListElement";
		GameInterface.TABLE_PERKS.tr1.(col).icon2.width = 38;
		GameInterface.TABLE_PERKS.tr1.(col).icon2.height = 38;
		GameInterface.TABLE_PERKS.tr1.(col).icon2.offset = "-1, 1";
	}

	makearef(perksObj, NullCharacter.HeroParam.Perks);
	nPerks = GetAttributesNum(perksObj);
	i = 1;

	for (n = 0; n < nPerks; n++)
	{
		curPerk = GetAttributeN(perksObj, n);
		if (CheckAttribute(curPerk, "hidden")) continue;

		col = "td" + i;
		GameInterface.TABLE_PERKS.tr1.(col).UserData.ID = curPerk.id;
		GameInterface.TABLE_PERKS.tr1.(col).icon1.group = "PERK_ENABLE";
		GameInterface.TABLE_PERKS.tr1.(col).icon1.image = curPerk.id;
		GameInterface.TABLE_PERKS.tr1.(col).icon1.width = 38;
		GameInterface.TABLE_PERKS.tr1.(col).icon1.height = 38;
		GameInterface.TABLE_PERKS.tr1.(col).icon1.offset = "-1, 1";

		i++;
	}

	Table_UpdateWindow("TABLE_PERKS");
}

void InitPiratesDependingsObject()
{
	aref rObj;
	makearef(rObj, PIRATES_DependObj);
	string statName = SPECIAL_S;
    rObj.(statName).skills_p.s1 = SKILL_FENCING;
    rObj.(statName).skills_p.s1.rate = 0.6;
    rObj.(statName).skills_p.s2 = SKILL_F_HEAVY;
    rObj.(statName).skills_p.s2.rate = 0.9;
    rObj.(statName).skills_s.s1 = SKILL_CANNONS;
    rObj.(statName).skills_s.s1.rate = 0.4;
	rObj.(statName).stats.s1 = "Life";
    rObj.(statName).stats.s1.rate = 0.5;
	rObj.(statName).stats.s2 = "weight";
    rObj.(statName).stats.s2.rate = 0.7;

	statName = SPECIAL_P;
    rObj.(statName).skills_p.s1 = SKILL_F_LIGHT;
    rObj.(statName).skills_p.s1.rate = 0.1;
    rObj.(statName).skills_p.s2 = SKILL_SNEAK;
    rObj.(statName).skills_p.s2.rate = 0.5;
    rObj.(statName).skills_s.s1 = SKILL_ACCURACY;
    rObj.(statName).skills_s.s1.rate = 0.8;
    rObj.(statName).skills_s.s2 = SKILL_SAILING;
    rObj.(statName).skills_s.s2.rate = 0.2;
    rObj.(statName).skills_s.s3 = SKILL_REPAIR;
    rObj.(statName).skills_s.s3.rate = 0.2;

	statName = SPECIAL_A;
    rObj.(statName).skills_p.s1 = SKILL_F_LIGHT;
    rObj.(statName).skills_p.s1.rate = 0.9;
    rObj.(statName).skills_p.s2 = SKILL_FENCING;
    rObj.(statName).skills_p.s2.rate = 0.4;
    rObj.(statName).skills_p.s3 = SKILL_PISTOL;
    rObj.(statName).skills_p.s3.rate = 0.5;
    rObj.(statName).skills_s.s1 = SKILL_GRAPPLING;
    rObj.(statName).skills_s.s1.rate = 0.7;
    rObj.(statName).stats.s1 = "Energy";
    rObj.(statName).stats.s1.rate = 1.0;

	statName = SPECIAL_C;
    rObj.(statName).skills_p.s1 = SKILL_LEADERSHIP;
    rObj.(statName).skills_p.s1.rate = 0.9;
    rObj.(statName).skills_s.s1 = SKILL_COMMERCE;
    rObj.(statName).skills_s.s1.rate = 0.2;
    rObj.(statName).skills_s.s3 = SKILL_DEFENCE;
    rObj.(statName).skills_s.s3.rate = 0.5;

	statName = SPECIAL_I;
    rObj.(statName).skills_p.s1 = SKILL_LEADERSHIP;
    rObj.(statName).skills_p.s1.rate = 0.1;
    rObj.(statName).skills_s.s1 = SKILL_COMMERCE;
    rObj.(statName).skills_s.s1.rate = 0.8;
    rObj.(statName).skills_s.s2 = SKILL_CANNONS;
    rObj.(statName).skills_s.s2.rate = 0.6;
    rObj.(statName).skills_s.s3 = SKILL_SAILING;
    rObj.(statName).skills_s.s3.rate = 0.8;
    rObj.(statName).skills_s.s4 = SKILL_GRAPPLING;
    rObj.(statName).skills_s.s4.rate = 0.3;

	statName = SPECIAL_E;
	rObj.(statName).skills_p.s1 = SKILL_F_HEAVY;
    rObj.(statName).skills_p.s1.rate = 0.1;
    rObj.(statName).skills_s.s1 = SKILL_REPAIR;
    rObj.(statName).skills_s.s1.rate = 0.8;
    rObj.(statName).skills_s.s2 = SKILL_DEFENCE;
    rObj.(statName).skills_s.s2.rate = 0.5;
	rObj.(statName).stats.s1 = "Life";
    rObj.(statName).stats.s1.rate = 0.5;
	rObj.(statName).stats.s2 = "weight";
    rObj.(statName).stats.s2.rate = 0.5;

    statName = SPECIAL_L;
	rObj.(statName).skills_p.s1 = SKILL_FORTUNE;
    rObj.(statName).skills_p.s1.rate = 1.0;
    rObj.(statName).skills_p.s2 = SKILL_PISTOL;
    rObj.(statName).skills_p.s2.rate = 0.5;
    rObj.(statName).skills_p.s3 = SKILL_SNEAK;
    rObj.(statName).skills_p.s3.rate = 0.5;
    rObj.(statName).skills_s.s1 = SKILL_ACCURACY;
    rObj.(statName).skills_s.s1.rate = 0.2;
}

int GetIdxByStatName(string statName)
{
    int idx = -1;

	switch (statName)
	{
		case SKILL_LEADERSHIP:		idx = 1; break;
		case SKILL_F_LIGHT:			idx = 2;   break;
		case SKILL_FENCING:			idx = 3;   break;
		case SKILL_F_HEAVY:			idx = 4;   break;
		case SKILL_PISTOL:			idx = 5;    break;
		case SKILL_FORTUNE:			idx = 6;   break;
		case SKILL_SNEAK:			idx = 7;      break;

		case SKILL_SAILING:			idx = 1; break;
		case SKILL_ACCURACY:		idx = 2;   break;
		case SKILL_CANNONS:			idx = 3;   break;
		case SKILL_GRAPPLING:		idx = 4;   break;
		case SKILL_DEFENCE:			idx = 5;    break;
		case SKILL_REPAIR:			idx = 6;   break;
		case SKILL_COMMERCE:		idx = 7;      break;

		case "Life":				idx = 1;  break;
		case "Energy":				idx = 2;  break;
		case "weight":				idx = 3;  break;
	}

	return idx;
}

void RefreshShipInfo()
{
	aref shipObj;
	makearef(shipObj, NullCharacter.HeroParam.Ship);

	if (!CheckAttribute(shipObj, "id"))
	{
		SelChar_SetShipPicture("interfaces\portraits\128\face_1.tga");
		SetFormatedText("SHIP_CLASS", "");
    	SetFormatedText("SHIP_TYPE_NAME", "");
		return;
	}

	ref refShipType = GetShipByType(sti(shipObj.id));
	string sShip = refShipType.Name;
	SelChar_SetShipPicture("interfaces\ships\" + sShip + ".tga");

    SetFormatedText("SHIP_CLASS", XI_ConvertString("ShipClass") + " " + refShipType.Class);
    SetFormatedText("SHIP_TYPE_NAME", XI_ConvertString(sShip));
}

void SelChar_SetShipPicture(string sPath)
{
	if (ShipI_sCachedShipPic == sPath) return;
	ShipI_sCachedShipPic = sPath;
	SetNewPicture("SHIP_PICTURE", sPath);
}

void ProcessCommandExecuteType(string nodeName)
{
    idLngFile = LanguageOpenFile("HeroDescribe.txt");

	string charType = GetCharacterTypeFromNode(nodeName);
    NullCharacter.HeroParam.HeroType = charType;

	RefreshCharType();
    LanguageCloseFile(idLngFile);
}

void RefreshCharType()
{
	string charType = NullCharacter.HeroParam.HeroType;

	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "CORSAIR_TYPE",  4, argb(255,96,96,96));
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "ADVENTURER_TYPE", 4, argb(255,96,96,96));
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "MERCHANT_TYPE", 4, argb(255,96,96,96));
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "INQUISITOR_TYPE", 4, argb(255,96,96,96));
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "SECRETAGENT_TYPE", 4, argb(255,96,96,96));
	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, "MASTER_TYPE", 4, argb(255,96,96,96));

	for (int i = 0; i < 6; i++)
	{
		SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,"TYPES_SELECT_BACK", 4, i, "empty");
	}

	SetNewGroupPicture("CORSAIR_TYPE_BORDER", "RECON_SELECT_CHARACTER", "TypeDeSelected");
	SetNewGroupPicture("ADVENTURER_TYPE_BORDER", "RECON_SELECT_CHARACTER", "TypeDeSelected");
	SetNewGroupPicture("MERCHANT_TYPE_BORDER", "RECON_SELECT_CHARACTER", "TypeDeSelected");
	SetNewGroupPicture("INQUISITOR_TYPE_BORDER", "RECON_SELECT_CHARACTER", "TypeDeSelected");
	SetNewGroupPicture("SECRETAGENT_TYPE_BORDER", "RECON_SELECT_CHARACTER", "TypeDeSelected");
	SetNewGroupPicture("MASTER_TYPE_BORDER", "RECON_SELECT_CHARACTER", "TypeDeSelected");

	SendMessage(&GameInterface,"lsll",MSG_INTERFACE_MSG_TO_NODE, charType + "_TYPE", 4, argb(255,128,128,128));
	SetNewGroupPicture(charType + "_TYPE_BORDER", "RECON_SELECT_CHARACTER", "TypeSelected");
	SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,"TYPES_SELECT_BACK", 4,
		GetPictureNumberFromCharType(charType), "SelectionLight");


	SetHeroParam_Items();
	DiscardItemsTablePagination();
	RefreshEquipmentTable();

	SetHeroParam_Perks();
	RefreshPerksTable();

	SetHeroParam_Ship();
	RefreshShipInfo();

	DiscardPIRATES(charType);

    totalInfo = LanguageConvertString(idLngFile, charType);
	SetInfoChar();
}

int GetPictureNumberFromCharType(string charType)
{
    switch(charType)
	{
		case "Corsair":
			return 0;
		break;

		case "Adventurer":
			return 1;
		break;

		case "Merchant":
			return 2;
		break;

		case "Inquisitor":
			return 3;
		break;

		case "SecretAgent":
			return 4;
		break;

		case "Master":
			return 5;
		break;
	}
}

void SetInfoText()
{
    SetFormatedText("INFO_CHAR", infoCharStr);
//    SetVAligmentFormatedText("INFO_CHAR");
}

void SetNodeState_InfoChar()
{
	int nStrings = GetNumberOfStringsInFormatedText("INFO_CHAR", infoCharStr);
	int maxStringQty = 9; // Столько строк макс. поместится в форму, иначе юзаем скролл
	SetNodeUsing("INFO_CHAR_SCROLL",false);

	if (nStrings > maxStringQty)
	{
		SetNodeUsing("INFO_CHAR_SCROLL", true);
	}
}

void SetInfoChar()
{
    SetFormatedText("INFO_TYPE", totalInfo);
//    SetVAligmentFormatedText("INFO_TYPE");
}

void NationBonusShow(bool bShow)
{
	SetNodeUsing("NATION_BONUS_FRAME", bShow);
	SetNodeUsing("NATION_BONUS_TEXT", bShow);
	SetNodeUsing("NATION_BONUS_TITLE", bShow);
}

void SetNationBonusText()
{
	string infoText = GetRPGText("Pirate_bonuses_descr");
	SetFormatedText("NATION_BONUS_TEXT", infoText);
	SetVAligmentFormatedText("NATION_BONUS_TEXT");
}

void SetNationDifficultText()
{
	int iNation = sti(NullCharacter.HeroParam.nation);
	string sTitle = XI_ConvertString("SelChar_NationDifficult");
	string sDiff = XI_ConvertString("SelChar_NationDifficult_" + GetNationDifficultString(iNation));
	SetFormatedText("NATION_DIFFICULT", sTitle + ": " + sDiff);
}

string GetNationDifficultString(int iNation)
{
    switch(iNation)
	{
	    case ENGLAND:	return "Medium"; break;
		case FRANCE:	return "Easy"; break;
		case SPAIN:		return "Medium"; break;
		case HOLLAND:	return "Easy"; break;
		case PIRATE:	return "Hard"; break;
	}

	return "Medium";
}

void TmpI_ShowLevelComplexity()
{
    SetFormatedText("COMPLEX_TYPE", GetLevelComplexity(MOD_SKILL_ENEMY_RATE));
	SetFormatedText("INFO_COMPLEX", GetRPGText("LevelComplexity_desc"));
	SetVAligmentFormatedText("INFO_COMPLEX");
}

void SelectOperation()
{
	idLngFile = LanguageOpenFile("HeroDescribe.txt");

	LanguageConvertString(idLngFile, "hero_" + startHeroType);

	string sName = LanguageConvertString(idLngFile, "heroName_" + startHeroType);
	string sLastName = LanguageConvertString(idLngFile, "heroLastname_" + startHeroType);
	string sCharacterName = sName + " " + sLastName;

	string sHeroModel = LanguageConvertString(idLngFile, "heroModel_" + startHeroType);
    iModelQty = GetCountSubString(sHeroModel) - 1;
	PChar.HeroModel = sHeroModel;

	iCharModel = 0;
	string sModel = GetSubStringByNum(PChar.HeroModel, iCharModel);
	PChar.model = sModel;

	string sAni = LanguageConvertString(idLngFile, "animation_" + startHeroType);
	PChar.model.animation = sAni;

    SetFormatedText("MODEL_FRAME_CAPTION", XI_ConvertString("Preview"));
    SetNewModelToChar(PChar);

	RefreshTraitsTable();
	RefreshCharType();

	sLocation_id = LanguageConvertString(idLngFile, "idLocation_" + startHeroType);
	sLocation_locator = LanguageConvertString(idLngFile, "locatorLocation_" + startHeroType);
	sLocation_camera = LanguageConvertString(idLngFile, "coordinateLocation_" + startHeroType);
	sLocation_turn = LanguageConvertString(idLngFile, "turnLocation_" + startHeroType);

	LanguageCloseFile(idLngFile);
}

void SelectCharacter_Model()
{
    PChar.model = GetSubStringByNum(PChar.HeroModel, iCharModel);
    SendMessage(PChar, "lss", MSG_CHARACTER_SETMODEL, PChar.model, PChar.model.animation);
    SetFormatedText("MODEL_FRAME_CAPTION", XI_ConvertString("Preview"));
}

void SelectCharacter()
{
	int lindex;
	if (bLocationLoaded && PChar.location != "" && sLocation_id == PChar.location) return;
	else if (bLocationLoaded && PChar.location != "" && sLocation_id != PChar.location)
	{
		trace("unloaded");
		lindex = FindLocation(PChar.location);
		UnloadLocation(&Locations[lindex]);
		bLocationLoaded = false;
	}
	
	if (sLocation_id != "" && sLocation_locator != "")
	{
		lindex = FindLocation(sLocation_id);
		PChar.location         = sLocation_id;
		PChar.location.locator = sLocation_locator;
	}
	else
	{
		lindex = FindLocation("Estate");
		PChar.location         = "Estate";
		PChar.location.locator = "goto12";
	}
	PChar.location.group   = "goto";
	LoadLocation(&Locations[lindex]);
	bLocationLoaded = true;
	
	SetCharacterTask_None(PChar);
    LAi_LockFightMode(Pchar, true);
	LAi_LocationFightDisable(loadedLocation, true);
	LAi_SetActorTypeNoGroup(Pchar);

	InterfaceStates.Buttons.Controls.enable = false;
	InterfaceStates.Launched = true;
	InterfaceStates.doUnFreeze = false;
	DoQuestFunctionDelay("SelectCharacter_locCamera", 0.1);
}

void SelectCharacter_locCamera(string _tmp)
{
    if (sLocation_turn != "") SelChar_SetFacing(stf(sLocation_turn));
	else SelChar_SetFacing(4.42);
	
	if (sLocation_camera != "")
	{
		float i1 = stf(GetSubStringByNum(sLocation_camera, 0));
		float i2 = stf(GetSubStringByNum(sLocation_camera, 1));
		float i3 = stf(GetSubStringByNum(sLocation_camera, 2));
		int   i4 = sti(GetSubStringByNum(sLocation_camera, 3));
		float i5 = stf(GetSubStringByNum(sLocation_camera, 4));
		float i6 = stf(GetSubStringByNum(sLocation_camera, 5));
		float i7 = stf(GetSubStringByNum(sLocation_camera, 6));
		locCameraFromToPos(i1, i2, i3, i4, i5, i6, i7);
	}
	else locCameraFromToPos(9.14, 7.83, 0.15, 0, 22.45, 5.67, -4.71);
	ChangeShowIntarface();
}

void StartTheGame()
{
	isOkExit = true;
	ReadGameOptionsFromUI();
	SaveStartGameParam(); // boal
	IDoExit(RC_INTERFACE_CHARACTER_SELECT_EXIT, true);
}
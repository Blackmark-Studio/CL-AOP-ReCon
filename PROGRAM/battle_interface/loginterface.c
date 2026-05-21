#include "storm-engine\battle_interface\log_msg.h"

#define LOG_FOR_SEA			1
#define LOG_FOR_LAND		2
#define LOG_FOR_WORLDMAP	3

object showWindow;

object ILogAndActions;
object IBoardingStatus;
bool   bYesBoardStatus;
string g_ActiveActionName;

#define NOTIFICATIONS_SPEED 0.03
#define MAX_NOTIFICATIONS 9
object Notifications[MAX_NOTIFICATIONS];
int notificationsQty = -1;

#event_handler("blieGetMsgIconRoot","BI_GetMsgIconRoot");

void InitLogInterface()
{
	SetEventHandler("SetWindowSize","LI_SetWindowSize",0);
	CreateEntity(&ILogAndActions,"ILogAndActions");
	DelEventHandler("SetWindowSize","LI_SetWindowSize");
	DeleteAttribute(&ILogAndActions,"");
	ILogAndActions.type = "";
	CreateLogEnvironment();
	CreatePicInfoEnvironment();
//	CreateTimeSpeedEnvironment();
	CreateLevelUpEnvironment();
	SendMessage(&ILogAndActions,"lll",LOG_AND_ACTIONS_INIT,sti(InterfaceStates.BattleShow.FastCommand),sti(InterfaceStates.BattleShow.LogString));
	SetEventHandler(EVENT_LOCATION_LOAD,"LI_LocationLoad",0);
	SetEventHandler("BI_FastCommand","BI_FastCommand",0);
	SetEventHandler(BI_EVENT_SET_VISIBLE,"SetLogInterfaceVisible",0);
	LayerAddObject(EXECUTE,&ILogAndActions,-257);
	LayerAddObject(REALIZE,&ILogAndActions,-1);
	LayerAddObject(SEA_EXECUTE,&ILogAndActions,-257);
	LayerAddObject(SEA_REALIZE,&ILogAndActions,-1);

	for(int i = 0; i < MAX_NOTIFICATIONS; i++)
	{
		DeleteAttribute(&Notifications[i],"printing");
		DeleteAttribute(&Notifications[i],"str");
		DeleteAttribute(&Notifications[i],"index");
		DeleteAttribute(&Notifications[i],"lt");
	}
	notificationsQty = -1;

	InitActivePerkShower();
}

void Log_RemoveFromSingleLayers()
{
	LayerDelObject(EXECUTE,&ILogAndActions);
	LayerDelObject(REALIZE,&ILogAndActions);
	LayerDelObject(SEA_EXECUTE,&ILogAndActions);
	LayerDelObject(SEA_REALIZE,&ILogAndActions);
}

void Log_MoveToSingleLayers()
{
	LayerAddObject(EXECUTE,&ILogAndActions,-257);
	LayerAddObject(REALIZE,&ILogAndActions,-1);
	LayerAddObject(SEA_EXECUTE,&ILogAndActions,-257);
	LayerAddObject(SEA_REALIZE,&ILogAndActions,-1);
}

void LI_SetWindowSize()
{
	int w = GetEventData();
	int h = GetEventData();
	int bTVused = GetEventData();
	if(bTVused)	SetShowWindowParameters(bTVused,w,h,40,24,w-40,h-24);
	else	SetShowWindowParameters(bTVused,w,h,0,0,w,h);
}

void SetLogInterfaceVisible()
{
	int visibleFlag = GetEventData();
	SendMessage(&ILogAndActions,"ll",LI_SET_VISIBLE,visibleFlag);
}

void LI_LocationLoad()
{
	CreateILogAndActions(LOG_FOR_LAND);
}

void InitBattleInterfacesParameters()
{
	DeleteClass(&IBoardingStatus);
	DeleteAttribute(&IBoardingStatus,"");
	bYesBoardStatus = false;
}

void CreateILogAndActions(int loadType)
{
	DeleteAttribute(&IBoardingStatus,"ActiveActions");
	if (loadType == LOG_FOR_SEA)
	{
		CreateSeaActionsEnvironment();
	}
	else if (loadType == LOG_FOR_LAND)
	{
		CreateLandActionsEnvironment();
	}
	else if (loadType == LOG_FOR_WORLDMAP)
	{
		CreateWorldMapActionsEnvironment();
	}
	SendMessage(&ILogAndActions,"lll",LOG_AND_ACTIONS_CHANGE,sti(InterfaceStates.BattleShow.FastCommand),sti(InterfaceStates.BattleShow.LogString));
	Log_SetActiveAction(g_ActiveActionName);
	CreatePicInfoEnvironment();
	SendMessage(&ILogAndActions,"l", LOG_REFRESH_PIC);
}

void Log_SetActiveAction(string actionName)
{
	if(bMainMenu) return;
	if(questMovieIsLockPlayerCtrl) return;
	float fHtRatio = GetScreenScale();
	string sActionText, sTextFont, cname;
	float fFontScale;
	int iTextWidth, iKeyWidth, iTextOffset;

	g_ActiveActionName = actionName;
	// change text
	if(CheckAttribute(&ILogAndActions,"ActiveActions."+actionName+".Text") && actionName != "Map" && actionName != "EnterToSea" && !dialogRun)
    {
		if(iShowTips >= CONTROL_TIPS_EXTEND)//подсказки включены в настройках
		{
			if(actionName == "Closed")
            {
				Log_SetActiveAction_SetText("", ILogAndActions.ActiveActions.(actionName).Text);
			}
            else
            {
				Log_SetActiveAction_SetText(GetKeyByControl(FindControlFromActionName(actionName)), ILogAndActions.ActiveActions.(actionName).Text);
			}
		}
        else
        {
			ILogAndActions.ActiveActions.text1.text = "";
			ILogAndActions.ActiveActions.text2.text = "";
		}
	}
    else
    {
		ILogAndActions.ActiveActions.text1.text = "";
		ILogAndActions.ActiveActions.text2.text = "";
	}
	SendMessage(&ILogAndActions,"ls",LOG_SET_ACTIVE_ACTION,actionName);
}

void Log_SetActiveActionSea(string sAction)
{
	if (BattleInterface.SeaActiveActionName != sAction)
	{
		RefreshBattleInterface();
		if (iShowTips >= CONTROL_TIPS_EXTEND) BI_ShowFastKeyTip(sAction);
	}
	BattleInterface.SeaActiveActionName = sAction;
    SendMessage(&ILogAndActions, "ls", LOG_SET_ACTIVE_ACTION, sAction);
}

void Log_SetActiveAction_SetText(string sControlName, string sActionText)
{
	float fHtRatio = GetScreenScale();
	string sTextFont, cname;
	float fFontScale;
	int iTextWidth, iKeyWidth, iTextOffset;

	if(sControlName == "")
	{
		ILogAndActions.ActiveActions.text1.text = "";
		ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right)/2;
	}
	else
	{
//		sActionText = ILogAndActions.ActiveActions.(actionName).Text;
		sTextFont	= ILogAndActions.ActiveActions.text2.font;
		fFontScale	= ILogAndActions.ActiveActions.text2.scale;
		iTextWidth	= GetStringWidth(sActionText, sTextFont, fFontScale);
		iKeyWidth = makeint(35 * fHtRatio);
		iTextOffset = makeint(9 * fHtRatio);

		if(CheckAttribute(&objControlsState,"key_codes."+sControlName+".img"))
			ILogAndActions.ActiveActions.text1.text = objControlsState.key_codes.(sControlName).img;
		ILogAndActions.ActiveActions.text1.pos.x = sti(showWindow.right)/2 - makeint(iTextWidth/2) - iTextOffset;
		ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right)/2 + makeint(iKeyWidth/2) + iTextOffset;
	}
	ILogAndActions.ActiveActions.text2.text = sActionText;
}

void Log_SetStringToLog(string strLog)
{
	SendMessage(&ILogAndActions,"lls",LOG_ADD_STRING, false, strLog);
}

void Notification(string strLog, string ability)
{
	if(Ability == "") return;
	if(CheckAttribute(pchar,"systeminfo.NoNotifications")) return;
	int IconIndex = -1;
	float fLifeTime = 30.0/NOTIFICATIONS_SPEED*0.01;

	switch (ability)
	{
		case "BasicDefense": IconIndex = 0; break;
		case "AdvancedDefense": IconIndex = 1; break;
		case "CriticalHit": IconIndex = 2; break;
		case "Ciras": IconIndex = 3; break;
		case "SwordplayProfessional": IconIndex = 4; break;
		case "Grus": IconIndex = 5; break;
		case "Rush": IconIndex = 6; break;
		case "Tireless": IconIndex = 7; break;
		case "IronWill": IconIndex = 13; break;
		case "Medic": IconIndex = 15; break;
		case "Trustworthy": IconIndex = 18; break;
		case "MusketsShoot": IconIndex = 29; break;
		case "SeaDogProfessional": IconIndex = 40; break;
		case "Brander": IconIndex = 47; break;
		case "Troopers": IconIndex = 48; break;
		case "Carpenter": IconIndex = 51; break;
		case "HPPlus": IconIndex = 57; break;
		case "EnergyPlus": IconIndex = 58; break;
		case "WildCaribbean": IconIndex = 65; break; // Дикие карибы (поке не исп.)
		case "ShipCrew": IconIndex = 65; break; // Исп. для "сбор трофеев"
		case "Icollection": IconIndex = 71; break;
		case "Leadership": IconIndex = 72; break;
		case "FencingLight": IconIndex = 73; break;
		case "Fencing": IconIndex = 74; break;
		case "FencingHeavy": IconIndex = 75; break;
		case "Pistol": IconIndex = 76; break;
		case "Fortune": IconIndex = 77; break;
		case "Sneak": IconIndex = 78; break;
		case "X": IconIndex = 79; break;
		case "ShipSight": IconIndex = 80; break;
		case "Sailing": IconIndex = 81; break;
		case "Accuracy": IconIndex = 82; break;
		case "Cannons": IconIndex = 83; break;
		case "Grappling": IconIndex = 84; break;
		case "Defence": IconIndex = 85; break;
		case "Repair": IconIndex = 86; break;
		case "Commerce": IconIndex = 87; break;
		case "Document": IconIndex = 88; break;
		case "HealthDown": IconIndex = 89; break;
		case "HealthUp": IconIndex = 57; break;
		case "RepDown": IconIndex = 90; break;
		case "RepUp": IconIndex = 91; break;
		case "SeaFast": IconIndex = 92; break;
		case "DeadShip": IconIndex = 95; break;
		case "Dubloon": IconIndex = 96; break;
		case "Money": IconIndex = 97; break;
		case "Drunk": IconIndex = 98; break;
		case "SneakFail": IconIndex = 101; break;
		case "AmmoSelect": IconIndex = 102; break;
		case "AmmoNotSelect": IconIndex = 103; break;
		case "Capacity": IconIndex = 104; break;
		case "Alchemy": IconIndex = 106; break;
		case "BoxPlus": IconIndex = 107; break;
		case "BoxMinus": IconIndex = 108; break;
		case "MapsAtlas": IconIndex = 110; break;
		case "LogBook": IconIndex = 111; break;
		case "Cotton": IconIndex = 112; break;
		case "Ale": IconIndex = 113; break;
		case "Oil": IconIndex = 114; break;
		case "Fruits": IconIndex = 115; break;
		case "Chocolate": IconIndex = 116; break;
		case "Linen": IconIndex = 117; break;
		case "Wine": IconIndex = 118; break;
		case "Silk": IconIndex = 119; break;
		case "Wheat": IconIndex = 120; break;
		case "Rum": IconIndex = 121; break;
		case "Sailcloth": IconIndex = 122; break;
		case "Sugar": IconIndex = 123; break;
		case "Tobacco": IconIndex = 124; break;
		case "Leather": IconIndex = 125; break;
		case "Copra": IconIndex = 126; break;
		case "Clothes": IconIndex = 127; break;
		case "Paprika": IconIndex = 128; break;
		case "Pinctada": IconIndex = 129; break;
		case "BigPearl": IconIndex = 130; break;
		case "SmallPearl": IconIndex = 131; break;
		case "migraine_potion": IconIndex = 132; break;
		case "zingiber": IconIndex = 133; break;
		case "matricaria": IconIndex = 134; break;
		case "ginseng": IconIndex = 135; break;


		case "Powder": IconIndex = 144; break;
        case "Balls": IconIndex = 145; break;
        case "Grapes": IconIndex = 146; break;
        case "Bombs": IconIndex = 147; break;
        case "Knippels": IconIndex = 148; break;
        case "Cinnamon": IconIndex = 149; break;
        case "Mahogany": IconIndex = 150; break;
        case "Ebony": IconIndex = 151; break;
        case "Coffee": IconIndex = 152; break;
        case "Sandal": IconIndex = 153; break;
        case "Slaves": IconIndex = 154; break;
        case "Planks": IconIndex = 155; break;
        case "Food": IconIndex = 156; break;
        case "Weapon": IconIndex = 157; break;
        case "Gold": IconIndex = 158; break;
        case "Silver": IconIndex = 159; break;
		case "Brick": IconIndex = 161; break;
		case "Medicament": IconIndex = 162; break;
		case "Cannon_3": IconIndex = 163; break;
		case "Cannon_6": IconIndex = 164; break;
		case "Cannon_8": IconIndex = 165; break;
		case "Cannon_12": IconIndex = 166; break;
		case "Cannon_16": IconIndex = 167; break;
		case "Cannon_18": IconIndex = 168; break;
		case "Cannon_20": IconIndex = 169; break;
		case "Cannon_24": IconIndex = 170; break;
		case "Cannon_32": IconIndex = 171; break;
		case "Cannon_36": IconIndex = 172; break;
		case "Cannon_42": IconIndex = 173; break;
		case "Culverine_8": IconIndex = 174; break;
		case "Culverine_18": IconIndex = 175; break;
		case "Culverine_36": IconIndex = 191; break;

		case "Threat1": IconIndex = 193; break;
		case "Threat2": IconIndex = 194; break;
		case "Threat3": IconIndex = 195; break;
		case "Threat4": IconIndex = 196; break;
		case "Threat5": IconIndex = 197; break;
		case "Threat0": IconIndex = 198; break;

		case "SkullAztec": IconIndex = 200; break;
		case "Hat9": IconIndex = 201; break;
		case "Key": IconIndex = 202; break;
		case "Discovery": IconIndex = 203; break;
		case "Indians": IconIndex = 204; break;
		case "Smugglers": IconIndex = 205; break;
		case "FstTravel": IconIndex = 206; break;
		case "Rats": IconIndex = 207; break;
		case "Personal abilities": IconIndex = 4; break;
		case "Ship abilities": IconIndex = 41; break;
		case "enghunter": IconIndex = 42; break;
		case "frahunter": IconIndex = 43; break;
		case "spahunter": IconIndex = 44; break;
		case "holhunter": IconIndex = 45; break;
		case "pirhunter": IconIndex = 46; break;

		case "Strength": IconIndex = 208; break; // P
		case "Perception": IconIndex = 209; break; // I
		case "Agility": IconIndex = 210; break; // R
		case "Charisma": IconIndex = 211; break; // A
		case "Intellect": IconIndex = 212; break; // T
		case "Endurance": IconIndex = 213; break; // E
		case "Luck": IconIndex = 214; break; // S

		case "None": IconIndex = 239; break;
	}

	if (HasSubStr(ability, "face_"))
	{
	    string faceStr = FindStringAfterChar(ability, "_");
	    int faceId = -1;
	    if (faceStr != "")
		{
		    faceId = sti(faceStr);
		}

	    switch(faceId)
		{
			case 2003: IconIndex = 176; break; // Pitt
			case 2004: IconIndex = 177; break; // Ogl
			case 2005: IconIndex = 178; break; // Hugtorp
			case 2006: IconIndex = 179; break; // Volverston
			case 2007: IconIndex = 180; break; // Dieke

			case 2008: IconIndex = 181; break; // James_Callow
			case 2009: IconIndex = 182; break; // Fickler

			case 2010: IconIndex = 183; break; // Jafar_Preston
			case 2012: IconIndex = 184; break; // Humphrey_Douglas
			case 2014: IconIndex = 185; break; // Danielle_Sheppard
			case 2015: IconIndex = 186; break; // Workman
			case 2016: IconIndex = 187; break; // Angellica
			case 2017: IconIndex = 188; break; // YokoDias
			case 2018: IconIndex = 189; break; // Magnus
			case 2019: IconIndex = 190; break; // Rimalier

			case 2013: IconIndex = 224; break; // Tichingitu
			case 2022: IconIndex = 225; break; // Malcolm_Fawn
			case 2066: IconIndex = 226; break; // Sharp

//			case 2025: IconIndex = 227; break; // Thomas_Boyle
		}

		// Если не оказалось портрета - ставим пустоту
		if (IconIndex == -1)
		{
			IconIndex = 239;
		}
	}

	if (IconIndex == -1)
	{
	    Trace("Error Notification(): icon with name '"+ability+"' not found!");
	    IconIndex = 239;
	}

	if(notificationsQty < MAX_NOTIFICATIONS - 1)
	{
		notificationsQty++;
		Notifications[notificationsQty].str = strLog;
		Notifications[notificationsQty].index = IconIndex;
		Notifications[notificationsQty].lt = fLifeTime;
		if(notificationsQty < 1) SetEventHandler("frame","PushNotification",0);
	}
}

void PushNotification()
{
    int i;
	for(i = 0; i < 3; i++)
	{
		if(CheckAttribute(&Notifications[i],"lt"))
		{
			if(!CheckAttribute(&Notifications[i],"printing"))
			{
				Notifications[i].printing = true;
				Pic_Info(Notifications[i].str, makeint(Notifications[i].index), i);
				//log_info(" Not "+Notifications[i].str+ " " +stf(Notifications[i].lt));
			}
			Notifications[i].lt = stf(Notifications[i].lt) - MakeFloat(GetDeltaTime()) * 0.001;
			if(stf(Notifications[i].lt) < 0.1)
			{
				DeleteAttribute(&Notifications[i],"str");
				DeleteAttribute(&Notifications[i],"index");
				DeleteAttribute(&Notifications[i],"lt");
			}
		}
	}
	if(CheckAttribute(&Notifications[0],"lt")) return;
	if(CheckAttribute(&Notifications[1],"lt")) return;
	if(CheckAttribute(&Notifications[2],"lt")) return;

	for( i = 3; i < 6; i++)
	{
		if(CheckAttribute(&Notifications[i],"lt"))
		{

			if(!CheckAttribute(&Notifications[i],"printing"))
			{
				Notifications[i].printing = true;
				Pic_Info(Notifications[i].str, makeint(Notifications[i].index), i);
			}
			Notifications[i].lt = stf(Notifications[i].lt) - MakeFloat(GetDeltaTime()) * 0.001;
			if(stf(Notifications[i].lt) < 0.1)
			{
				DeleteAttribute(&Notifications[i],"str");
				DeleteAttribute(&Notifications[i],"index");
				DeleteAttribute(&Notifications[i],"lt");
			}
		}
	}
	if(CheckAttribute(&Notifications[3],"lt")) return;
	if(CheckAttribute(&Notifications[4],"lt")) return;
	if(CheckAttribute(&Notifications[5],"lt")) return;

	for( i = 6; i < 9; i++)
	{
		if(CheckAttribute(&Notifications[i],"lt"))
		{
			if(!CheckAttribute(&Notifications[i],"printing"))
			{
				Notifications[i].printing = true;
				Pic_Info(Notifications[i].str, makeint(Notifications[i].index), i);
			}
			Notifications[i].lt = stf(Notifications[i].lt) - MakeFloat(GetDeltaTime()) * 0.001;
			if(stf(Notifications[i].lt) < 0.1)
			{
				DeleteAttribute(&Notifications[i],"str");
				DeleteAttribute(&Notifications[i],"index");
				DeleteAttribute(&Notifications[i],"lt");
			}
		}
	}
	if(CheckAttribute(&Notifications[6],"lt")) return;
	if(CheckAttribute(&Notifications[7],"lt")) return;
	if(CheckAttribute(&Notifications[8],"lt")) return;

	for(i = 0; i < MAX_NOTIFICATIONS; i++)
	{
		DeleteAttribute(&Notifications[i],"printing");
	}
	notificationsQty = -1;
	DelEventHandler("frame", "PushNotification");
}

void ClearActiveStageNotifications() //HardCoffee убрать отображаемые соообщения и отобразить те, которые на очереди
{
	PushNotification();

	ref rNote;
	int i, iFirst, iSecond, iThird;
	SendMessage(&ILogAndActions, "leee", LOG_CLEAR_ACTIVE_STAGES, &iFirst, &iSecond, &iThird);
	//LOG_CLEAR_ACTIVE_STAGES отправляет индексы массива Notifications, отображаемых на данный момент сообщений в лог
	// по дефолту возвращает -1 !!
	// очищает отображаемые сообщения
	for (i = 0; i < MAX_NOTIFICATIONS; i++)
	{
		rNote = &Notifications[i];
		if (i == iFirst || i == iSecond || i == iThird)
		{
			if (CheckAttribute(rNote, "index"))
			{
				DeleteAttribute(rNote, "str");
				DeleteAttribute(rNote, "index");
				DeleteAttribute(rNote, "lt");
			}
		}
		DeleteAttribute(rNote, "printing");
	}

	PushNotification();
}

void ClearAllNotifications() //очитстить лог сообщений
{
	int i, iFirst, iSecond, iThird;
	SendMessage(&ILogAndActions, "leee", LOG_CLEAR_ACTIVE_STAGES, &iFirst, &iSecond, &iThird);
	for (i = 0; i < MAX_NOTIFICATIONS; i++)
	{
		DeleteAttribute(&Notifications[i], "");
	}
	notificationsQty = -1;
	DelEventHandler("frame", "PushNotification");
}

bool ShowExpNotifications()
{
	if(LAi_IsFightMode(pchar)) return false;
	if(CheckAttribute(pchar,"systeminfo.InGameNotifications")) return true;
	if(CheckAttribute(pchar,"chr_ai.type") && Pchar.chr_ai.type != "player") return false;
	if(CheckAttribute(pchar,"Ship.POS.Mode"))
	{
		if(pchar.Ship.POS.Mode == SHIP_WAR) return false;
	}
	if(isEntity(&WorldMap)) return false;

	return true;
}

void Pic_Info(string strLog, int IconIndex, int iArrIdx)
{
	SendMessage(&ILogAndActions,"lsll", LOG_ADD_PIC, strLog, IconIndex, iArrIdx);
}

void TimeScale_Info(string strLog)
{
	bool bShow = false;
	if(strLog != "") bShow = true;
	SendMessage(&ILogAndActions,"lsl", LOG_TIME_SPEED, strLog, bShow);
}

void LA_LevelUp(string strLog, string Rank)
{
	PlayStereoSound("interface\new_level.wav");
	SendMessage(&ILogAndActions,"lss", LOG_LEVEL_UP, strLog, Rank);
}

void Log_Chr(ref chr, string sText)
{
	if(ShowCharString())
	{
		SendMessage(chr, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, sText, 255.0, 255.0, 255.0);
	}
}

bool ShowCharString()
{
	//if (bBettaTestMode) return true;
	if(CheckAttribute(&InterfaceStates,"ShowCharString") && sti(InterfaceStates.ShowCharString) > 0) return true;

	return false;
}

void Log_SetEternalString(string strLog)
{
	SendMessage(&ILogAndActions,"lls",LOG_ADD_STRING, true, strLog);
}

void CreateLogEnvironment()
{
	float fHtRatio = GetScreenScale();
	
	ILogAndActions.Log.width = sti(showWindow.sw)/2;
	ILogAndActions.Log.height = sti(showWindow.sh)-makeint(80 * fHtRatio);
	ILogAndActions.Log.right = sti(showWindow.right) - RecalculateHIcon(makeint(340 * fHtRatio));
	ILogAndActions.Log.up = sti(showWindow.top) + makeint(16 * fHtRatio);
	ILogAndActions.Log.font = "interface_normal";
	ILogAndActions.Log.fontscale = 1.2 * fHtRatio;
	ILogAndActions.Log.color = argb(0,255,255,255);
	ILogAndActions.Log.offsetString = makeint(24 * fHtRatio);
	ILogAndActions.Log.speed = 0.05;
	ILogAndActions.Log.color_speed = 0.02;
}

void CreatePicInfoEnvironment()
{
	/* belamour legendary edition боковые уведомления основные настройки:
	ILogAndActions.PicInfo - настройки текста в уведомлении
	ILogAndActions.PicInfoBack - настройки текстуры подложки
	ILogAndActions.PicInfoIcon - настройки текстуры иконки

	общие для всех настройки:
	ILogAndActions.PicInfo.color_speed - скорость блендинга (пропадания) подсказки.
	ILogAndActions.PicInfo.maxcolor, ILogAndActions.PicInfo.mincolor - максимальное(минимальное значение для альфа каналов (влияет на скорость затухания)
	ILogAndActions.PicInfo.right - можно менять на left и наоборот в зависимости от нужного равнения по краю */

	float fHtRatio = GetScreenScale();
	ILogAndActions.PicInfo.width = sti(showWindow.right)/2;
	ILogAndActions.PicInfo.height = sti(showWindow.bottom)-makeint(350 * fHtRatio);
	ILogAndActions.PicInfo.right = sti(showWindow.right) - RecalculateHIcon(makeint(75 * fHtRatio));
	// AlexBlade - Компас всегда вверху, пока отключим
//	if(iCompassPos)
//	{
		if(!isEntity(&WorldMap))
		{
			ILogAndActions.PicInfo.up = sti(showWindow.top) + makeint(425 * fHtRatio);
		}
		else
		{
			ILogAndActions.PicInfo.up = sti(showWindow.bottom)/2 + makeint(75 * fHtRatio);
		}
//	}
//	else
//	{
//		if(!isEntity(&WorldMap))
//		{
//			ILogAndActions.PicInfo.up = sti(showWindow.top) + makeint(165 * fHtRatio);
//		}
//		else
//		{
//			ILogAndActions.PicInfo.up = sti(showWindow.bottom)/2 + makeint(75 * fHtRatio);
//		}
//	}
	ILogAndActions.PicInfo.font = "interface_normal";
	ILogAndActions.PicInfo.fontscale = 1.2 * fHtRatio;
	ILogAndActions.PicInfo.color = argb(255,255,255,255);
	ILogAndActions.PicInfo.offsetString = makeint(50 * fHtRatio);
	ILogAndActions.PicInfo.color_speed = NOTIFICATIONS_SPEED;
	ILogAndActions.PicInfo.maxcolor = argb(255,128,128,128);
	ILogAndActions.PicInfo.mincolor = argb(0,128,128,128); // не менять!!!

	ILogAndActions.PicInfoBack.TextureName = "battle_interface\info_fader_r.tga.tx";
	ILogAndActions.PicInfoBack.width = RecalculateHIcon(makeint(350 * fHtRatio));
	ILogAndActions.PicInfoBack.height = RecalculateHIcon(makeint(40 * fHtRatio));
	ILogAndActions.PicInfoBack.right = sti(showWindow.right) + RecalculateHIcon(makeint(5 * fHtRatio));
	// AlexBlade - Компас всегда вверху, пока отключим
//	if(iCompassPos)
//	{
		if(!isEntity(&WorldMap))
		{
			ILogAndActions.PicInfoBack.top = sti(showWindow.top) + makeint(420 * fHtRatio);
		}
		else
		{
			ILogAndActions.PicInfoBack.top = sti(showWindow.bottom)/2 + makeint(70 * fHtRatio);
		}
//	}
//	else
//	{
//		if(!isEntity(&WorldMap))
//		{
//			ILogAndActions.PicInfoBack.top = sti(showWindow.top) + makeint(160 * fHtRatio);
//		}
//		else
//		{
//			ILogAndActions.PicInfoBack.top = sti(showWindow.bottom)/2 + makeint(70 * fHtRatio);
//		}
//	}

	ILogAndActions.PicInfoIcon.TextureName = "battle_interface\MessageIcons.tga.tx";
	ILogAndActions.PicInfoIcon.horzQ = 16;
	ILogAndActions.PicInfoIcon.vertQ = 16;
	ILogAndActions.PicInfoIcon.width = RecalculateHIcon(makeint(50 * fHtRatio));
	ILogAndActions.PicInfoIcon.height = RecalculateHIcon(makeint(50 * fHtRatio));
	ILogAndActions.PicInfoIcon.left = sti(showWindow.right) - RecalculateHIcon(makeint(60 * fHtRatio));
	// AlexBlade - Компас всегда вверху, пока отключим
//	if(iCompassPos)
//	{
		if(!isEntity(&WorldMap))
		{
			ILogAndActions.PicInfoIcon.top = sti(showWindow.top) + makeint(415 * fHtRatio);
		}
		else
		{
			ILogAndActions.PicInfoIcon.top = sti(showWindow.bottom)/2 + makeint(65 * fHtRatio);
		}
//	}
//	else
//	{
//		if(!isEntity(&WorldMap))
//		{
//			ILogAndActions.PicInfoIcon.top = sti(showWindow.top) + makeint(155 * fHtRatio);
//		}
//		else
//		{
//			ILogAndActions.PicInfoIcon.top = sti(showWindow.bottom)/2 + makeint(65 * fHtRatio);
//		}
//	}
}

//void CreateTimeSpeedEnvironment()
//{
//	float fHtRatio = GetScreenScale();
//
//	ILogAndActions.timespeedtext.left = sti(showWindow.right) - RecalculateHIcon(makeint(100 * fHtRatio));
//	ILogAndActions.timespeedtext.up = sti(showWindow.bottom)/2 - RecalculateVIcon(makeint(0 * fHtRatio));
//	ILogAndActions.timespeedtext.font = "interface_normal";
//	ILogAndActions.timespeedtext.fontscale = 1.75 * fHtRatio;
//	ILogAndActions.timespeedtext.color = argb(255,255,255,255);
//
//	ILogAndActions.timespeedicon.TextureName = "interfaces\le\battle_interface\timescale.tga.tx";
//	ILogAndActions.timespeedicon.width = RecalculateHIcon(makeint(60 * fHtRatio));
//	ILogAndActions.timespeedicon.height = RecalculateHIcon(makeint(60 * fHtRatio));
//	ILogAndActions.timespeedicon.left = sti(showWindow.right) - RecalculateHIcon(makeint(100 * fHtRatio));
//	ILogAndActions.timespeedicon.top = sti(showWindow.bottom)/2 - RecalculateVIcon(makeint(0 * fHtRatio));
//	ILogAndActions.timespeedicon.color = argb(255,128,128,128);
//}

void CreateLevelUpEnvironment()
{
	float fHtRatio = GetScreenScale();
	ILogAndActions.levelupstring.width = sti(showWindow.right)/2;
	ILogAndActions.levelupstring.height = sti(showWindow.bottom)/2;
	ILogAndActions.levelupstring.left = sti(showWindow.right)/2;
	ILogAndActions.levelupstring.up = sti(showWindow.bottom)/2 - makeint(42 * fHtRatio);
//	ILogAndActions.levelupstring.font = "interface_normal_bold";
//	ILogAndActions.levelupstring.fontscale = 1.4 * fHtRatio;
    ILogAndActions.levelupstring.font = "interface_normal";
	ILogAndActions.levelupstring.fontscale = 1.6 * fHtRatio;
	ILogAndActions.levelupstring.color = argb(0,255,255,255); // альфу не менять
	ILogAndActions.levelupstring.color_speed = 0.05;

	ILogAndActions.leveluprank.width = sti(showWindow.right)/2;
	ILogAndActions.leveluprank.height = sti(showWindow.bottom)/2;
	ILogAndActions.leveluprank.left = sti(showWindow.right)/2;
	ILogAndActions.leveluprank.up = sti(showWindow.bottom)/2 + makeint(0 * fHtRatio);
	ILogAndActions.leveluprank.font = "bold_numbers";
	ILogAndActions.leveluprank.fontscale = 1.7 * fHtRatio;
	ILogAndActions.leveluprank.color = argb(0,255,255,255);
	//ILogAndActions.leveluprank.color_speed = 0.02;

	ILogAndActions.levelupback.TextureName = "battle_interface\info_fader_c.tga.tx";
	ILogAndActions.levelupback.width = RecalculateHIcon(makeint(450 * fHtRatio));
	ILogAndActions.levelupback.height = RecalculateVIcon(makeint(100 * fHtRatio));
	ILogAndActions.levelupback.left = sti(showWindow.right)/2 - RecalculateHIcon(makeint(225 * fHtRatio));
	ILogAndActions.levelupback.top = sti(showWindow.bottom)/2 - RecalculateVIcon(makeint(50 * fHtRatio));
	ILogAndActions.levelupback.color = argb(0,128,128,128); // альфу не менять
}

void CreateSeaActionsEnvironment()
{
	float fHtRatio = GetScreenScale();
	int iTmp, iTmp2;

	ILogAndActions.type = "sea";
	//значёк активного действия под значками скоростей -->
	ILogAndActions.ActiveActions.TextureName = "battle_interface\list_icons.tga";
	ILogAndActions.ActiveActions.horzQ = 16;
	ILogAndActions.ActiveActions.vertQ = 8;
	int iPosX = sti(showWindow.right) + RecalculateHIcon(makeint(-10 * fHtRatio))
	 	- RecalculateHIcon(makeint(256 * fHtRatio)) / 2; //Центр компаса справа
	int iPosY = sti(showWindow.top) - RecalculateVIcon(makeint(0 * fHtRatio)) + RecalculateHIcon(makeint(256 * fHtRatio)) / 2
	 	- RecalculateVIcon(makeint(10 * fHtRatio)); //Центр компаса сверху
	ILogAndActions.ActiveActions.width = RecalculateHIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.height = RecalculateHIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.left = iPosX - RecalculateHIcon(makeint(-48 * fHtRatio));
	ILogAndActions.ActiveActions.top = sti(showWindow.bottom)/2 - RecalculateVIcon(makeint(-30 * fHtRatio));
	// <--

	ILogAndActions.ActiveActionsBack.TextureName = "battle_interface\info_fader_b.tga.tx";
	ILogAndActions.ActiveActionsBack.width = RecalculateHIcon(makeint(100 * fHtRatio)); // ширина текcтуры также зависит от длины текста
	ILogAndActions.ActiveActionsBack.height = RecalculateVIcon(makeint(50 * fHtRatio));
	ILogAndActions.ActiveActionsBack.centr = sti(showWindow.right)/2; // центр текстуры по Х
	ILogAndActions.ActiveActionsBack.top = sti(showWindow.bottom) - RecalculateVIcon(makeint(225 * fHtRatio));
	ILogAndActions.ActiveActionsBack.color = argb(192,32,32,32);

	ILogAndActions.ActiveActions.text2.font = "interface_normal";
	ILogAndActions.ActiveActions.text2.scale = 1.3 * fHtRatio;
	ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text2.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(212 * fHtRatio));
	ILogAndActions.ActiveActions.text2.text = XI_ConvertString("for_quick_action");

	ILogAndActions.ActiveActions.text1.font = "keyboard_symbol";
	ILogAndActions.ActiveActions.text1.scale = 1.1 * fHtRatio;
	ILogAndActions.ActiveActions.text1.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text1.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(218 * fHtRatio));

	iTmp = sti(showWindow.right)/2;
	iTmp2 = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));

	ILogAndActions.ActiveActions.Moor.IconNum		= 29;
	ILogAndActions.ActiveActions.Moor.Text			= XI_ConvertString("for_quick_action_Moor");//Причалить (переопределяется в BI_ShowFastKeyTip)
	ILogAndActions.ActiveActions.Moor.pos.x			= iTmp;
	ILogAndActions.ActiveActions.Moor.pos.y			= iTmp2;
	ILogAndActions.ActiveActions.Board.IconNum		= 30;
	ILogAndActions.ActiveActions.Board.Text			= XI_ConvertString("for_quick_action_Board");//Взять на абордаж (переопределяется в BI_ShowFastKeyTip)
	ILogAndActions.ActiveActions.Board.pos.x		= iTmp;
	ILogAndActions.ActiveActions.Board.pos.y		= iTmp2;
	ILogAndActions.ActiveActions.LandTroops.IconNum	= 42;
	ILogAndActions.ActiveActions.LandTroops.Text	= XI_ConvertString("for_quick_action_LandTroops");//Высадка союзного десанта (переопределяется в BI_ShowFastKeyTip)
	ILogAndActions.ActiveActions.LandTroops.pos.x	= iTmp;
	ILogAndActions.ActiveActions.LandTroops.pos.y	= iTmp2;
	ILogAndActions.ActiveActions.Map.IconNum		= 28;
	ILogAndActions.ActiveActions.Map.Text			= XI_ConvertString("for_quick_action_Map");//На глобальную карту (переопределяется в BI_ShowFastKeyTip)
	ILogAndActions.ActiveActions.Map.pos.x			= iTmp;
	ILogAndActions.ActiveActions.Map.pos.y			= iTmp2;
	ILogAndActions.ActiveActions.Reload.IconNum		= 48;
	ILogAndActions.ActiveActions.Reload.Text		= XI_ConvertString("for_quick_action_Reload_Sea");//Обмен с кораблем (переопределяется в BI_ShowFastKeyTip)
	ILogAndActions.ActiveActions.Reload.pos.x		= iTmp;
	ILogAndActions.ActiveActions.Reload.pos.y		= iTmp2;
	ILogAndActions.ActiveActions.Deck.IconNum		= 0;
	ILogAndActions.ActiveActions.Deck.Text			= XI_ConvertString("for_quick_action_Deck");//Палуба
	ILogAndActions.ActiveActions.Deck.pos.x			= iTmp;
	ILogAndActions.ActiveActions.Deck.pos.y			= iTmp2;
	ILogAndActions.ActiveActions.Nothing.IconNum	= -1;
	ILogAndActions.ActiveActions.Nothing.Text		= XI_ConvertString("for_quick_action");
}

void CreateLandActionsEnvironment()
{
	float fHtRatio = GetScreenScale();
	int iTmp, iTmp2;
	
	ILogAndActions.type = "land";
	ILogAndActions.ActiveActions.TextureName = "battle_interface\LandCommands.tga";
	ILogAndActions.ActiveActions.horzQ = 16;
	ILogAndActions.ActiveActions.vertQ = 4;
	ILogAndActions.ActiveActions.width = RecalculateHIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.height = RecalculateVIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.left = sti(showWindow.right) - RecalculateHIcon(makeint(284 * fHtRatio));
	ILogAndActions.ActiveActions.top = sti(showWindow.top) + RecalculateVIcon(makeint(32 * fHtRatio));

	ILogAndActions.ActiveActionsBack.TextureName = "battle_interface\info_fader_b.tga.tx";
	ILogAndActions.ActiveActionsBack.width = RecalculateHIcon(makeint(100 * fHtRatio)); // ширина текcтуры также зависит от длины текста
	ILogAndActions.ActiveActionsBack.height = RecalculateVIcon(makeint(50 * fHtRatio));
	ILogAndActions.ActiveActionsBack.centr = sti(showWindow.right)/2; // центр текстуры по Х
	ILogAndActions.ActiveActionsBack.top = sti(showWindow.bottom) - RecalculateVIcon(makeint(205 * fHtRatio));
	ILogAndActions.ActiveActionsBack.color = argb(192,32,32,32);

	ILogAndActions.ActiveActions.text2.font = "interface_normal";
	ILogAndActions.ActiveActions.text2.scale = 1.3 * fHtRatio;
	ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text2.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(192 * fHtRatio));
	ILogAndActions.ActiveActions.text2.text = XI_ConvertString("for_quick_action");

	ILogAndActions.ActiveActions.text1.font = "keyboard_symbol";
	ILogAndActions.ActiveActions.text1.scale = 1.1 * fHtRatio;
	ILogAndActions.ActiveActions.text1.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text1.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(198 * fHtRatio));

	iTmp = sti(showWindow.right)/2;
	iTmp2 = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));

	ILogAndActions.ActiveActions.Parrot.IconNum			= 16;
	ILogAndActions.ActiveActions.Parrot.Text			= XI_ConvertString("Interact");
	ILogAndActions.ActiveActions.Parrot.pos.x			= iTmp;
	ILogAndActions.ActiveActions.Parrot.pos.y			= iTmp2;

	ILogAndActions.ActiveActions.ToSea.IconNum			= 14;
	ILogAndActions.ActiveActions.ToSea.Text				= XI_ConvertString("for_quick_action_ToSea");
	ILogAndActions.ActiveActions.ToSea.pos.x			= iTmp;
	ILogAndActions.ActiveActions.ToSea.pos.y			= iTmp2;

	ILogAndActions.ActiveActions.Talk.IconNum			= 1;
	ILogAndActions.ActiveActions.Talk.Text				= XI_ConvertString("for_quick_action_Talk");
	ILogAndActions.ActiveActions.Talk.pos.x				= iTmp;
	ILogAndActions.ActiveActions.Talk.pos.y				= iTmp2;

	ILogAndActions.ActiveActions.Look.IconNum			= 0;
	ILogAndActions.ActiveActions.Look.Text				= XI_ConvertString("for_quick_action_Look");
	ILogAndActions.ActiveActions.Look.pos.x				= iTmp;
	ILogAndActions.ActiveActions.Look.pos.y				= iTmp2;

	ILogAndActions.ActiveActions.Pick.IconNum			= 16;
	ILogAndActions.ActiveActions.Pick.Text				= XI_ConvertString("for_quick_action_Pick");
	ILogAndActions.ActiveActions.Pick.pos.x				= iTmp;
	ILogAndActions.ActiveActions.Pick.pos.y				= iTmp2;

	ILogAndActions.ActiveActions.Action.IconNum			= 0;
	ILogAndActions.ActiveActions.Action.Text			= XI_ConvertString("for_quick_action_Action");
	ILogAndActions.ActiveActions.Action.pos.x			= iTmp;
	ILogAndActions.ActiveActions.Action.pos.y			= iTmp2;

	ILogAndActions.ActiveActions.OpenBox.IconNum		= 16;
	ILogAndActions.ActiveActions.OpenBox.Text			= XI_ConvertString("for_quick_action_OpenBox");
	ILogAndActions.ActiveActions.OpenBox.pos.x			= iTmp;
	ILogAndActions.ActiveActions.OpenBox.pos.y			= iTmp2;

	ILogAndActions.ActiveActions.DeadBox.IconNum		= 56;
	ILogAndActions.ActiveActions.DeadBox.Text			= XI_ConvertString("for_quick_action_DeadBox");
	ILogAndActions.ActiveActions.DeadBox.pos.x			= iTmp;
	ILogAndActions.ActiveActions.DeadBox.pos.y			= iTmp2;

	ILogAndActions.ActiveActions.Reload.IconNum			= 13;
	ILogAndActions.ActiveActions.Reload.Text			= XI_ConvertString("for_quick_action_Reload");
	ILogAndActions.ActiveActions.Reload.pos.x			= iTmp;
	ILogAndActions.ActiveActions.Reload.pos.y			= iTmp2;

	ILogAndActions.ActiveActions.BoardingReload.IconNum	= 13;
	ILogAndActions.ActiveActions.BoardingReload.Text	= XI_ConvertString("for_quick_action_BoardingReload");
	ILogAndActions.ActiveActions.BoardingReload.pos.x	= iTmp;
	ILogAndActions.ActiveActions.BoardingReload.pos.y	= iTmp2;

	ILogAndActions.ActiveActions.BoardingEnd.IconNum	= 13;
	ILogAndActions.ActiveActions.BoardingEnd.Text		= XI_ConvertString("for_quick_action_BoardingEnd");
	ILogAndActions.ActiveActions.BoardingEnd.pos.x		= iTmp;
	ILogAndActions.ActiveActions.BoardingEnd.pos.y		= iTmp2;

	ILogAndActions.ActiveActions.PlayEvent.IconNum		= 0;
	ILogAndActions.ActiveActions.PlayEvent.Text			= XI_ConvertString("for_quick_action_Use");
	ILogAndActions.ActiveActions.PlayEvent.pos.x		= iTmp;
	ILogAndActions.ActiveActions.PlayEvent.pos.y		= iTmp2;

	ILogAndActions.ActiveActions.Closed.IconNum			= 29;
	ILogAndActions.ActiveActions.Closed.Text			= XI_ConvertString("for_quick_action_Closed");
	ILogAndActions.ActiveActions.Closed.pos.x			= iTmp;
	ILogAndActions.ActiveActions.Closed.pos.y			= iTmp2;

	ILogAndActions.ActiveActions.Nothing.IconNum		= -1;
	ILogAndActions.ActiveActions.Nothing.Text			= XI_ConvertString("for_quick_action");
}

void CreateWorldMapActionsEnvironment()
{
	float fHtRatio = GetScreenScale();
	int iTmp, iTmp2;

	ILogAndActions.type = "map";
	ILogAndActions.ActiveActions.TextureName = "battle_interface\WorldMapCommands.tga";
	ILogAndActions.ActiveActions.horzQ = 8;
	ILogAndActions.ActiveActions.vertQ = 2;
	ILogAndActions.ActiveActions.width = RecalculateHIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.height = RecalculateVIcon(makeint(48 * fHtRatio));
	ILogAndActions.ActiveActions.left = sti(showWindow.right) - RecalculateHIcon(makeint(284 * fHtRatio));
	ILogAndActions.ActiveActions.top = sti(showWindow.top) + RecalculateVIcon(makeint(32 * fHtRatio));

	ILogAndActions.ActiveActionsBack.TextureName = "battle_interface\info_fader_b.tga.tx";
	ILogAndActions.ActiveActionsBack.width = RecalculateHIcon(makeint(100 * fHtRatio)); // ширина текcтуры также зависит от длины текста
	ILogAndActions.ActiveActionsBack.height = RecalculateVIcon(makeint(50 * fHtRatio));
	ILogAndActions.ActiveActionsBack.centr = sti(showWindow.right)/2; // центр текстуры по Х
	ILogAndActions.ActiveActionsBack.top = sti(showWindow.bottom) - RecalculateVIcon(makeint(205 * fHtRatio));
	ILogAndActions.ActiveActionsBack.color = argb(192,32,32,32);

	ILogAndActions.ActiveActions.text2.font = "interface_normal";
	ILogAndActions.ActiveActions.text2.scale = 1.3 * fHtRatio;
	ILogAndActions.ActiveActions.text2.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text2.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(192 * fHtRatio));
	ILogAndActions.ActiveActions.text2.text = XI_ConvertString("for_quick_action");
	
	ILogAndActions.ActiveActions.text1.font = "keyboard_symbol";
	ILogAndActions.ActiveActions.text1.scale = 1.0 * fHtRatio;
	ILogAndActions.ActiveActions.text1.pos.x = sti(showWindow.right)/2;
	ILogAndActions.ActiveActions.text1.pos.y = sti(showWindow.bottom) - RecalculateVIcon(makeint(198 * fHtRatio));

	iTmp = sti(showWindow.right)/2;
	iTmp2 = sti(showWindow.bottom) - RecalculateVIcon(makeint(200 * fHtRatio));

	ILogAndActions.ActiveActions.EnterToIsland.IconNum		= 0;
	ILogAndActions.ActiveActions.EnterToIsland.Text			= XI_ConvertString("for_quick_action_EnterToIsland");
	ILogAndActions.ActiveActions.EnterToSea.IconNum			= 1;
	ILogAndActions.ActiveActions.EnterToSea.Text			= XI_ConvertString("for_quick_action_EnterToSea");//Выйти в море
	ILogAndActions.ActiveActions.EnterToSea.pos.x			= iTmp;
	ILogAndActions.ActiveActions.EnterToSea.pos.y			= iTmp2;
	ILogAndActions.ActiveActions.EnterToAttack.IconNum		= 2;
	ILogAndActions.ActiveActions.EnterToAttack.Text			= XI_ConvertString("for_quick_action_EnterToAttack");//Присоединиться к бою
	ILogAndActions.ActiveActions.EnterToAttack.pos.x		= iTmp;
	ILogAndActions.ActiveActions.EnterToAttack.pos.y		= iTmp2;
	ILogAndActions.ActiveActions.EnterToEnemy.IconNum		= 3;
	ILogAndActions.ActiveActions.EnterToEnemy.Text			= XI_ConvertString("for_quick_action_EnterToEnemy");//Защищаться
	ILogAndActions.ActiveActions.EnterToEnemy.pos.x			= iTmp;
	ILogAndActions.ActiveActions.EnterToEnemy.pos.y			= iTmp2;
	ILogAndActions.ActiveActions.EnterToShip.IconNum		= 4;
	ILogAndActions.ActiveActions.EnterToShip.Text			= XI_ConvertString("for_quick_action_EnterToShip");//Атаковать
	ILogAndActions.ActiveActions.EnterToShip.pos.x			= iTmp;
	ILogAndActions.ActiveActions.EnterToShip.pos.y			= iTmp2;
	ILogAndActions.ActiveActions.GetOnBoard.IconNum			= 4;
	ILogAndActions.ActiveActions.GetOnBoard.Text			= XI_ConvertString("for_quick_action_GetOnBoard");//Взять на борт
	ILogAndActions.ActiveActions.GetOnBoard.pos.x			= iTmp;
	ILogAndActions.ActiveActions.GetOnBoard.pos.y			= iTmp2;	
	ILogAndActions.ActiveActions.EnterToStorm.IconNum		= 5;
	ILogAndActions.ActiveActions.EnterToStorm.Text			= XI_ConvertString("for_quick_action_EnterToStorm");//Шторм
	ILogAndActions.ActiveActions.EnterToStorm.pos.x			= iTmp;
	ILogAndActions.ActiveActions.EnterToStorm.pos.y			= iTmp2;
	ILogAndActions.ActiveActions.Nothing.IconNum			= -1;
	ILogAndActions.ActiveActions.Nothing.Text				= XI_ConvertString("for_quick_action");
}

void DrawCharacterHP(float myHP,float enemyHP)
{
	float fHtRatio = GetScreenScale();
	
	if(bYesBoardStatus==false)
	{
		CreateEntity(&IBoardingStatus,"IBoardingStatus");
		IBoardingStatus.myLeft = sti(showWindow.left)+makeint(16 * fHtRatio);
		IBoardingStatus.myTop = sti(showWindow.bottom)-makeint(140 * fHtRatio);
		IBoardingStatus.enemyLeft = sti(showWindow.left)+makeint(16 * fHtRatio);
		IBoardingStatus.enemyTop = sti(showWindow.bottom)-makeint(128 * fHtRatio);
		IBoardingStatus.height = RecalculateVIcon(makeint(8 * fHtRatio));
		IBoardingStatus.width = RecalculateHIcon(makeint(120 * fHtRatio));
		IBoardingStatus.myColor = argb(255,0,0,128);
		IBoardingStatus.enemyColor = argb(255,128,0,0);
		SendMessage(&IBoardingStatus,"l",LOG_INIT_CHARCTER_HP);
		bYesBoardStatus = true;
	}
	if(myHP==0)
	{
		bYesBoardStatus=false;
		DeleteClass(&IBoardingStatus);
		DeleteAttribute(&IBoardingStatus,"");
	}
	if(enemyHP==0)
	{
		bYesBoardStatus=false;
		DeleteClass(&IBoardingStatus);
		DeleteAttribute(&IBoardingStatus,"");
	}
	SendMessage(&IBoardingStatus,"lff",LOG_SET_CHARCTER_HP,myHP,enemyHP);
}

void BI_FastCommand()
{
	int tmpi;
	string FComName = GetEventData();
	string sTemp;

	if( LAi_IsDead(pchar) ) {return;}

	aref arFader;
	if( GetEntity(arFader,"fader") ) {return;}

	bool bEC = false;

	if( ILogAndActions.type == "sea" )
	{
		switch(FComName)
		{
		case "Moor":		bEC = true; Sea_LandLoad(); break;
		case "Board":		bEC = true; Sea_AbordageLoad(SHIP_ABORDAGE,true); break;
		case "LandTroops":	bEC = true; Sea_AbordageLoad(FORT_ABORDAGE,true); break;
		case "Map":			bEC = true; Sea_MapLoad(); break; //  pchar.location = ""; тут нах не нужно
		case "Reload":
			if(bi_nReloadTarget!=-1)
			{
				bEC = true;
				LaunchTransferMain(pchar,GetCharacter(bi_nReloadTarget),"Transfer");
			}
		break;
		}
	}
	if( ILogAndActions.type == "land" )
	{
		if(CheckAttribute(pchar,"Quests.quest_act"))
		{
			Event("evntQuestComplete","s",Characters[nMainCharacterIndex].Quests.quest_act);
			return;
		}
		switch(FComName)
		{
			case "OpenBox":
			    // AlexBlade - раскладка старая, альтернативу пока отключим
//				if(iControlsMode == 0)
//				{
					if (!LAi_IsFightMode(pchar)) // в бою быстрой командой низя открыть сундук
					{
						bEC = true;
						OpenBoxProcedure();
					}
    //				}
    //				else // с альтернативной раскладкой можем обыскивать
    //				{
    //					bEC = true;
    //					OpenBoxProcedure();
    //				}
			break;

			case "Pick": bEC = true; Item_OnPickItem(); break;
			case "Action": bEC = true; Item_OnUseItem(); break;
			case "Talk":
				bEC = true;
				tmpi = SendMessage(pchar,"ls",MSG_CHARACTER_EX_MSG,"FindDialogCharacter");
				if(tmpi>=0)	{Event("dlgReady","l",tmpi);}
			break;
			case "Reload":
				bEC = true;
				if (bCabinStarted)   // boal
	            {
	                // раставление НПС при переходах - миниквесты
	                BOAL_ReloadToLoc(chrWaitReloadRef, chrWaitReloadLocator);
	            }
	            else
					Event("Control Activation","s","ChrAction");
			break;
			case "ToSea": bEC = true; Event("Control Activation","s","ChrAction"); break;
			case "BoardingReload":  break;
			case "BoardingEnd":  break;
			case "Parrot":
				sTemp = "Types\Parrot" +its(Rand(3) +".mp3");
				PlayCharVoice(sTemp);
				if (Get_My_Cabin() == pchar.location && GetDlcEnabled(NABOB_PACK))
					Achievment_Set(ACH_MyParrot);
				Log_SetActiveAction("Nothing");
			break;
			// AlexBlade - хз зачем, отключим
//			case "PlayEvent":
//				bEC = true;
//				PlayLocatorEvent();
//			break;
		}
	}
	if( ILogAndActions.type == "map" )
	{
		switch(FComName)
		{
		case "EnterToSea":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToIsland":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToShip":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToStorm":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToAttack":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "EnterToEnemy":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		case "GetOnBoard":
			bEC = true;
			SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
			break;
		}
	}

	if( bEC )
	{
		g_ActiveActionName = "";
		SendMessage(&ILogAndActions,"ls",LOG_SET_ACTIVE_ACTION,"");
	}
}

void ClearAllLogStrings()
{
	SendMessage(&ILogAndActions,"l",LI_CLEAR_STRINGS);
}

void BI_GetMsgIconRoot()
{
	aref arTmp;
	aref pARef[4];
	int i,idx,cn;
	idx = 0;

	if(bSeaActive && !bAbordageStarted)
	{
		for(i=0; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(pchar,i);
			if(cn<0) {continue;}
			Characters[cn].MessageIcons = true;
			makearef(arTmp,Characters[cn].MessageIcons);
			pARef[idx] = arTmp;
			idx++;
		}
		SendMessage(&BattleInterface,"le", BI_MSG_SET_MSG_ICONS, &pARef);
	}


	else
	{
		for(i=0; i<4; i++)
		{
			cn = GetOfficersIndex(pchar,i);
			if(cn<0) {continue;}
			Characters[cn].MessageIcons = true;
			makearef(arTmp,Characters[cn].MessageIcons);
			pARef[idx] = arTmp;
			idx++;
		}
		SendMessage(&objLandInterface,"le", MSG_BATTLE_LAND_SET_MSGICONS, &pARef);
	}
}

void LoadLIStates()
{
	pchar = GetMainCharacter();//нужно, чтобы не ругалось
	if(!CheckAttribute(pchar, "id")) return;
	int i,cn;
	ref chref;

	DeleteAttribute(pchar,"MessageIcons");
	for(i=1; i<COMPANION_MAX; i++)
	{
		cn = GetOfficersIndex(pchar,i);
		if(cn>=0)
		{
			chref = GetCharacter(cn);
			DeleteAttribute(chref,"MessageIcons");
		}
		cn = GetCompanionIndex(pchar,i);
		if(cn>=0)
		{
			chref = GetCharacter(cn);
			DeleteAttribute(chref,"MessageIcons");
		}
	}
}


string FindControlFromActionName(string _actionName)
{
	string control = "BIFastCommand";

	switch(_actionName)
	{
		case "DeadBox": control = "BOAL_DeadSearch"; break;
		case "BoardingReload": control = "ChrAction"; break;
		case "BoardingEnd": control = "ChrAction"; break;
		case "Talk":
		    // AlexBlade - раскладка старая, альтернативу пока отключим
//			if(iControlsMode == 0) control = "ChrAction";
			control = "ChrAction";
		break;
		case "Reload":
		    // AlexBlade - раскладка старая, альтернативу пока отключим
//			if(iControlsMode == 0)
//			{
//				if(ILogAndActions.type == "sea") control = "IAction";
//				else control = "ChrAction";
//			}
            if(ILogAndActions.type == "sea") control = "BIFastCommand";
            else control = "ChrAction";
		break;
		case "ToSea":
		    // AlexBlade - раскладка старая, альтернативу пока отключим
//			if(iControlsMode == 0) control = "ChrAction";
			control = "ChrAction";
		break;
	}

	return control;
}
// AlexBlade - хз зачем, пока отключим
/*
#event_handler("Event_ErrorLog","Event_ErrorLog");
void Event_ErrorLog()
{
	string string1 = GetEventData();
	string string2 = GetEventData();
	if(MOD_BETTATESTMODE != "off")
		log_info(string1 + string2);
}
*/
#include "storm-engine\battle_interface\msg_control.h"
#include "storm-engine\sea_ai\script_defines.h"
#include "battle_interface\landinterface.c"
#include "battle_interface\TaskWindow\TaskWindow.c"
#include "battle_interface\ispyglass.c"
#include "battle_interface\reload_tables.c"
#include "battle_interface\utils.c"
#include "battle_interface\ActivePerksShow.c"
#include "battle_interface\WmInterface.c"
#include "battle_interface\BI_ControlTips.c"

#define BI_ICONS_SHIPS_TEXTURE_NAME "battle_interface\icons.tga"

#define BI_ICONS_ST_NONE		0
#define BI_ICONS_ST_MYSHIPS		1
#define BI_ICONS_ST_COMMAND		2
#define BI_ICONS_ST_TARGETING		3

#define BI_ICONS_TEXTURE_COMMAND	0
#define BI_ICONS_TEXTURE_SHIP1		1
#define BI_ICONS_TEXTURE_ABILITY	2

#define FLAG_CMN		0	// общие флаги
#define FLAG_SHP		1	// адмиральские флаги
#define FLAG_FRT		2	// флаги для фортов и городских администраций
#define FLAG_MER		3	// торговые флаги
#define FLAG_WHT		4	// белые флаги
#define FLAG_QST		5	// квестовые флаги
#define FLAG_PER		6	// персональные флаги
#define	FLAG_PIR		7	// пиратские флаги

#define SAILDIR_POS_DIF	10000.0 //используется для указания компаньону направления "уплыть"
#define BLINKS_TIME 600 //сколько времени (в кадрах) будет моргать нехватка пороха и боеприпасов

int bi_icons_ShowType;
int bi_icons_CommandMode;

int bi_idxSelectedPicture;

object BattleInterface;

bool bDisableSailTo = false;

bool bDisableMapEnter = false;

bool bReloadCanBe = false;
bool bMapEnter = false;
bool bSailTo=false;
bool bAttack=false;
bool bAbordage = false;
bool bDefend=false;

bool bEnableIslandSailTo = false;

int BI_intRetValue;
int BI_retComValue;
int BI_ChargeState[5];
float BI_g_fRetVal;

int BI_intNRetValue[17];

object BI_objRetValue;
object objShipPointer;
// boal -->
bool boal_soundOn = true;
// boal <--

int CurrentShip = 0;
int CurrentFlag = 0;
int ShipFlagsQuantity = -1;

bool bCannonsRangeShow = true; //конусы стрельбы, по умолчанию всегда
int iCommandsFile = -1;
int iControlsFile = -1;
int iLocLablesFile = -1;
int iBlincCount = 0;
int iPowderBlinks = 0;
int iChargeBlinks = 0;
float fTextScale = 1.0;
int iTextColor;

#event_handler("evntRandomSailDmg","ProcessRandomSailDmg");
//#event_handler("NextDay","ProcessDayRepair");
#event_handler("GetSailTextureData","procGetSailTextureData");
#event_handler("EventMastFall","procMastFall");
#event_handler("evntGetSmallFlagData","procGetSmallFlagData");

#event_handler(SHIP_CREATE,"BI_CreateShip");
#event_handler("GetRiggingData","procGetRiggingData");

void InitBattleInterface()
{
	iCommandsFile = LanguageOpenFile("commands_name.txt"); //HardCoffee описание команд командного меню
	iControlsFile = LanguageOpenFile("ControlsNames.txt"); //описание назначения кнопок
	iLocLablesFile = LanguageOpenFile("LocLables.txt"); //названия локаций для причаливания, чтобы не дёргать его каждую секунду
	DeleteAttribute(&BattleInterface, ""); //фикс неисчезающих подсказок

	BI_InitializeCommands();
	bi_icons_CommandMode = 0;
	BattleInterface.comstate = 0;
	BattleInterface.SelCharacter = -1;
	bi_idxSelectedPicture = -1;
	BattleInterface.boardRadius = 50;
	BattleInterface.freeDistance = MIN_ENEMY_DISTANCE_TO_DISABLE_MAP_ENTER;

	LoadSeaPerkShower();
	SetParameterData();

	BattleInterface.blindSpeed = 0.003;
	BattleInterface.MaxWind = 30.0;
	BattleInterface.MaxShipSpeed = 20.0;
	if (iArcadeSails == 1) BattleInterface.ShipSpeedScaler = (1.0 / 2.5);
	else BattleInterface.ShipSpeedScaler = (1.0 / 1.0);
	BattleInterface.ShowNavigator = InterfaceStates.BattleShow.Navigator;
	BattleInterface.ShowCommands = InterfaceStates.BattleShow.Command;
	BattleInterface.MainChrIndex = nMainCharacterIndex;
	CreateEntity(&BattleInterface,"battle_interface");
	DeleteAttribute(&BattleInterface,"CommandTextures");
	DeleteAttribute(&BattleInterface,"CommandShowParam");
	LayerAddObject(SEA_EXECUTE,&BattleInterface,-1);
	LayerAddObject(SEA_REALIZE,&BattleInterface,-1);

	SetEventHandler(SHIP_DELETE,"BI_DeleteShip",0);
	SetEventHandler(SHIP_DEAD,"BI_DeadShip",0);

	SetEventHandler("BI_CommandEndChecking","BI_CommandEndChecking",0);
	SetEventHandler("BI_LaunchCommand","BI_LaunchCommand",0);
	SetEventHandler("BI_GetChargeQuantity","BI_GetChargeQuantity",0);
	SetEventHandler("BI_SetPossibleCommands","BI_SetPossibleCommands",0);
	SetEventHandler("GetCurrentCharge","GetCurrentCharge",0);
	SetEventHandler("evntGetCharacterShipClass","biGetCharacterShipClass",0);
	SetEventHandler(BI_EVENT_SET_VISIBLE,"BI_CommandVisible",0);
	SetEventHandler(BI_EVENT_SET_SEA_STATE,"BI_SetSeaState",0);
	SetEventHandler(BI_EVENT_GET_DATA,"BI_GetData",0);
	SetEventHandler("evntGetLandData","BI_GetLandData",0);
	SetEventHandler(BI_EVENT_GET_FORT_RELATION,"BI_GetFortRelation",0);
	SetEventHandler(EVENT_CHANGE_COMPANIONS,"RefreshBattleInterface",0);
	SetEventHandler("BI_CallUpdateShip","BI_UpdateShip",0);
	SetEventHandler("frame","BI_Frame",1);
	SetEventHandler("evntPerkAgainUsable","BI_PerkAgainUsable",0);
	SetEventHandler("evntSetUsingAbility","procSetUsingAbility",0);
	SetEventHandler("evntCheckEnableLocator","procCheckEnableLocator",0);
	SetEventHandler("evntCheckEnableShip","procCheckEnableShip",0);
	SetEventHandler("evntGetSRollSpeed","procGetSRollSpeed",0);
	SetEventHandler("DoSailHole","ProcessSailDamage",0);
	SetEventHandler("evntBISelect", "BI_SetSelectTip", 0);
	SetEventHandler("evntBISelectShip","procBISelectShip",0);
	SetEventHandler("refreshCannonsQty","BI_ShowCannonsQty",1);

	procLoadIntoNew(); // Проинитим таблицу активных перков
	SetEventHandler("Control Activation","BI_ProcessControlPress",0);

	CreateILogAndActions(LOG_FOR_SEA);
	BattleInterface.SeaActiveActionName = "nothing";
	Log_SetActiveActionSea("Nothing");
	ResetTimeScale(); // boal
	InitActivePerkShower();
}

ref BI_GetFortRelation()
{
	BI_intRetValue = BI_RELATION_NEUTRAL;
	aref arLoc = GetEventData();
	int chrIdx = Fort_FindCharacter(AISea.Island,"reload",arLoc.name);
	if(chrIdx>=0)
	{
		switch( SeaAI_GetRelation(chrIdx,nMainCharacterIndex) )
		{
		case RELATION_FRIEND:	BI_intRetValue = BI_RELATION_FRIEND;	break;
		case RELATION_NEUTRAL:	BI_intRetValue = BI_RELATION_NEUTRAL;	break;
		case RELATION_ENEMY:	BI_intRetValue = BI_RELATION_ENEMY;		break;
		}
	}
	return &BI_intRetValue;
}

void BI_CommandVisible()
{
	int visibleFlag = GetEventData();
	SendMessage(&BattleInterface,"ll",BI_SET_VISIBLE,visibleFlag);
}

int bi_nReloadTarget=-1;
bool biold_bCanEnterToLand = false;
bool biold_bAbordageShipCanBe = false;
bool biold_bAbordageFortCanBe = false;
bool biold_bReloadCanBe = false;
bool biold_bMapEnter = false;
bool bOldNotEnoughBalls = false;

void BI_Frame()
{
	bool bYesUpdateCommand = false;
	ref rChr;

	if (iShowTips > CONTROL_TIPS_NONE)
	{
		if (Crosshair.OutsideCamera == false && !bCommMenu)
		{
			BattleInterface.textinfo.SalvoFad.text = "1";
			BattleInterface.textinfo.SalvoKey.text = GetKeyCodeImg("Ship_Fire");
			BattleInterface.textinfo.SalvoTip.text = LanguageConvertString(iControlsFile, "Ship_Fire");
		}
		else if (SendMessage(&AISea, "la", AI_MESSAGE_CHECK_FOR_FIRERANGE, pchar) && !bCommMenu)
		{
			iBlincCount++;
			if (iBlincCount > 120)
			{
				iBlincCount = 121;
				BattleInterface.textinfo.SalvoFad.text = "1";
				BattleInterface.textinfo.SalvoKey.text = GetKeyCodeImg("Ship_Fire");
				BattleInterface.textinfo.SalvoTip.text = LanguageConvertString(iControlsFile, "Ship_Fire");
			}
		}
		else
		{
			iBlincCount--;
			if (iBlincCount < -300 || bMapEnter)
			{
				iBlincCount = 0;
				BattleInterface.textinfo.SalvoFad.text = " ";
				BattleInterface.textinfo.SalvoKey.text = " ";
				BattleInterface.textinfo.SalvoTip.text = " ";
			}
		}
	}

	/*	//раскоммент подключит мигание всех видов боеприпасов
	if(bNotEnoughBalls!=bOldNotEnoughBalls)
	{
		bOldNotEnoughBalls = bNotEnoughBalls;
		if(bNotEnoughBalls)
		{
			SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,true);
		}
		else
		{
			SendMessage(&BattleInterface,"ll",BI_MSG_NOT_ENOUGH_BALLS_FLAG,false);
		}
	}*/

	if (biold_bAbordageShipCanBe != bAbordageShipCanBe)
	{
		bYesUpdateCommand = true;
		biold_bAbordageShipCanBe = bAbordageShipCanBe;
	}
	if (biold_bAbordageFortCanBe != bAbordageFortCanBe)
	{
		bYesUpdateCommand = true;
		biold_bAbordageFortCanBe = bAbordageFortCanBe;
	}
	if (biold_bCanEnterToLand != bCanEnterToLand)
	{
		bYesUpdateCommand = true;
		biold_bCanEnterToLand = bCanEnterToLand;
	}
	if (biold_bReloadCanBe != bReloadCanBe)
	{
		bYesUpdateCommand = true;
		biold_bReloadCanBe = bReloadCanBe;
	}
	if (biold_bMapEnter != bMapEnter)
	{
		bYesUpdateCommand = true;
		biold_bMapEnter = bMapEnter;
	}

	if (bYesUpdateCommand)
	{
		BI_SetCommandMode(-1,-1,-1,-1);
	}

	if (bAbordageShipCanBe)
	{
		Log_SetActiveActionSea("Board");
		if (boal_soundOn) // boal
		{
		    boal_soundOn = false;
            PlayVoice("Boarding_0");
		}
		return;
	}

	if (bAbordageFortCanBe)
	{
		Log_SetActiveActionSea("LandTroops");
		if (boal_soundOn) // boal
		{
		    boal_soundOn = false;
            PlayVoice("Abandon_0");
		}
		return;
	}

	if (bReloadCanBe) //Обмен товарами
	{
		Log_SetActiveActionSea("Reload");
		return;
	}

	if (bCanEnterToLand)
	{
		if (CheckAttribute(&TEV, "DesMoinesMoorDisable") && Sea_FindNearColony(0) == "DesMoines_town")
		{
			Log_SetActiveActionSea("Nothing");
			boal_soundOn = true;
			return;
		}
		Log_SetActiveActionSea("Moor");
		if (boal_soundOn) // boal
		{
		    boal_soundOn = false;
            PlayVoice("AnchorDrop");
		}
		return;
	}
	boal_soundOn = true; // boal

	if (bMapEnter)
	{
		Log_SetActiveActionSea("Map");
		return;
	}

	Log_SetActiveActionSea("Nothing");
}

void StartBattleInterface()
{
	bi_nReloadTarget = -1;
	bReloadCanBe = false;
	bi_icons_ShowType = BI_ICONS_ST_MYSHIPS;
	BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
	BI_SetIslandData();
	InterfaceSpyGlassInit();

	objShipPointer.textures.friend = "battle_interface\Frendly.tga";
	objShipPointer.textures.enemy = "battle_interface\Enemy.tga";
	objShipPointer.textures.unknown = "battle_interface\Unknown.tga"; //HardCoffee colour pointers
	objShipPointer.textures.neutral = "battle_interface\Neutral.tga";
	objShipPointer.textures.alliance = "battle_interface\Alliance.tga";
	CreateEntity(&objShipPointer,"shippointer");
	LayerAddObject(SEA_EXECUTE,&objShipPointer,222222);
	LayerAddObject(SEA_REALIZE,&objShipPointer,-1);

	CannonsRangeRefresh();
	Ship_CheckMainCharacter(); //Обновить активное действие до актуального
	PostEvent("Event_CheckSeaTutorials", 2000);
	TW_Init();
}

void RefreshBattleInterface()
{
	BI_SetCommandMode(0,-1,-1,-1);
	SendMessage(&BattleInterface,"l",BI_MSG_REFRESH);
	BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
}

void DeleteBattleInterface()
{
    ResetTimeScale(); // boal

 	LanguageCloseFile(iCommandsFile); //HardCoffee
 	LanguageCloseFile(iControlsFile);
 	LanguageCloseFile(iLocLablesFile);

	BattleInterface.SeaActiveActionName = "nothing";
	Log_SetActiveActionSea("Nothing");
	InterfaceSpyGlassRelease();
	UnloadSeaPerkShower();

    DeleteClass(&BattleInterface);
	DeleteClass(&objShipPointer);
	
	DelEventHandler(SHIP_DELETE, "BI_DeleteShip");
	DelEventHandler(SHIP_DEAD,"BI_DeadShip");
	DelEventHandler("BI_CommandEndChecking", "BI_CommandEndChecking");
	DelEventHandler("BI_LaunchCommand", "BI_LaunchCommand");
	DelEventHandler("BI_GetChargeQuantity","BI_GetChargeQuantity");
	DelEventHandler("BI_SetPossibleCommands","BI_SetPossibleCommands");
	DelEventHandler("GetCurrentCharge","GetCurrentCharge");
	DelEventHandler("evntGetCharacterShipClass","biGetCharacterShipClass");
	DelEventHandler(BI_EVENT_SET_VISIBLE,"BI_CommandVisible");
	DelEventHandler(BI_EVENT_SET_SEA_STATE,"BI_SetSeaState");
	DelEventHandler(BI_EVENT_GET_DATA,"BI_GetData");
	DelEventHandler("evntGetLandData","BI_GetLandData");
	DelEventHandler(BI_EVENT_GET_FORT_RELATION,"BI_GetFortRelation");
	DelEventHandler(EVENT_CHANGE_COMPANIONS,"RefreshBattleInterface");
	DelEventHandler("BI_CallUpdateShip","BI_UpdateShip");
	DelEventHandler("frame","BI_Frame");
	DelEventHandler("evntPerkAgainUsable","BI_PerkAgainUsable");
	DelEventHandler("evntSetUsingAbility","procSetUsingAbility");
	DelEventHandler("evntCheckEnableLocator","procCheckEnableLocator");
	DelEventHandler("evntCheckEnableShip","procCheckEnableShip");
	DelEventHandler("evntGetSRollSpeed","procGetSRollSpeed");
	DelEventHandler("Control Activation","BI_ProcessControlPress");
	DelEventHandler("DoSailHole","ProcessSailDamage");
	DelEventHandler("evntBISelectShip","procBISelectShip");
	DelEventHandler("evntBISelect","BI_SetSelectTip");
	DelEventHandler("refreshCannonsQty","BI_ShowCannonsQty");

	TW_Close();

	// был сброс времени, выше поднял
	//DeleteClass(&BattleInterface);
	//DeleteClass(&objShipPointer);
}

ref BI_CommandEndChecking()
{
	BI_retComValue = 0;
	string comName = GetEventData();

	bool bTip = iShowTips >= CONTROL_TIPS_ALL;
	if (bTip) sCommandTip = "";

	switch(comName)
	{
		case "cancel":				BI_retComValue = -1;break;
		case "BI_MyHold":			BI_retComValue = 0;	break;
		case "BI_Cabin":			BI_retComValue = 0;	break;
		case "BI_Board":			BI_retComValue = 0;	break;
		case "BI_LandTroops":		BI_retComValue = 0;	break;
		case "BI_Map":				BI_retComValue = 0;	break;
		case "BI_SailAway":			BI_retComValue = 0;	break;
		case "BI_HeaveToDrift":		BI_retComValue = 0;	break;
		case "BI_Reload":			BI_retComValue = 0;	break;
		case "BI_ImmediateReload":	BI_retComValue = 0;	break;
		case "BI_LightRepair":		BI_retComValue = 0;	break;
		case "BI_InstantRepair":	BI_retComValue = 0;	break;
		case "BI_Turn180":			BI_retComValue = 0;	break;
		case "BI_Moor":				BI_retComValue = 0;	break;
		case "BI_SailTowards": //HardCoffee команда компаньону для указания направления "уплыть"
			if (bTip) sCommandTip = LanguageConvertString(iCommandsFile, "sea_SailAway");
			BI_retComValue = BI_COMMODE_USER_ICONS;
		break;
		case "BI_Boat":	// выслать шлюпку для разговора
			if (bTip) sCommandTip = LanguageConvertString(iCommandsFile, "sea_SendBoat");
			BI_retComValue = BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT;
			BattleInterface.Commands.Boat.EffectRadius = DistanceToShipTalk;
			//--> eddy. снижаем радиус базара если взят квест мэра
			if (CheckAttribute(pchar, "GenQuest.DestroyPirate")) BattleInterface.Commands.Boat.EffectRadius = 150;
		break;
		case "BI_Attack":
			if (bTip) sCommandTip = LanguageConvertString(iCommandsFile, "sea_Attack");
			BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_ENEMY_FORT_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
			BattleInterface.Commands.Attack.EffectRadius	= 2000; //boal
		break;
		case "BI_Abordage":
			if (bTip) sCommandTip = LanguageConvertString(iCommandsFile, "sea_Abordage");
			BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT;
			BattleInterface.Commands.Abordage.EffectRadius	= 2000; //boal
		break;
		case "BI_Defend":
			if (bTip) sCommandTip = LanguageConvertString(iCommandsFile, "sea_Defend");
			BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_FRIEND_FORT_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
			BattleInterface.Commands.Defend.EffectRadius	= 2000; //boal
		break;
		case "BI_Charge":
			if (bTip) sCommandTip = LanguageConvertString(iCommandsFile, "sea_Charge");
			BI_retComValue = BI_COMMODE_CANNON_CHARGE;
		break;
		case "BI_Brander":
			if (bTip) sCommandTip = LanguageConvertString(iCommandsFile, "sea_Brander");
			BI_retComValue = BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_ALLLOCATOR_SELECT;
		break;
		case "BI_Ability":
			BI_retComValue = BI_COMMODE_ABILITY_ICONS;
		break;
		case "BI_ImmDeath":
			if (bTip) sCommandTip = LanguageConvertString(iCommandsFile, "sea_ImmediateDeath");
			BI_retComValue = BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_FRIEND_FORT_SELECT+BI_COMMODE_NEUTRAL_FORT_SELECT+BI_COMMODE_ENEMY_FORT_SELECT;
			BattleInterface.Commands.ImmediateDeath.EffectRadius	= 900000;
		break;
		case "BI_InstantBoarding":
			if (bTip) sCommandTip = LanguageConvertString(iCommandsFile, "sea_InstantBoarding");
			BI_retComValue = BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT;
		break;

		case "BI_SailTo":
			if (bTip) sCommandTip = LanguageConvertString(iCommandsFile, "sea_SailTo");
			int iIsland = FindIsland(pchar.location);
			if(iIsland > 0 && !sti(Islands[iIsland].reload_enable)) bEnableIslandSailTo	= false;

			if (bEnableIslandSailTo)
				BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT+BI_COMMODE_FRIEND_FORT_SELECT+BI_COMMODE_NEUTRAL_FORT_SELECT+BI_COMMODE_ENEMY_FORT_SELECT+BI_COMMODE_DISEASED_TOWN+BI_COMMODE_NOTDISEASED_TOWN+BI_COMMODE_LAND_SELECT; //+BI_COMMODE_ALLLOCATOR_SELECT;
			else
				BI_retComValue = BI_COMMODE_MY_SHIP_SELECT+BI_COMMODE_NEUTRAL_SHIP_SELECT+BI_COMMODE_FRIEND_SHIP_SELECT+BI_COMMODE_ENEMY_SHIP_SELECT;//+BI_COMMODE_ALLLOCATOR_SELECT;

			if (bBettaTestMode) BattleInterface.Commands.SailTo.EffectRadius = 900000;
			else
			{
				// BattleInterface.Commands.SailTo.EffectRadius = 5000; //boal
				// Радиус доплыть до - Зависимость от восприятия
				BattleInterface.Commands.SailTo.EffectRadius = 4000 + 150*GetCharacterSPECIAL(pchar, "Perception");
				// Если глобал тутор - поставим увеличенный радиус
				if (GetGlobalTutor())
				{
					BattleInterface.Commands.SailTo.EffectRadius = 7000;
				}
				//zagolski. наличие карт и радиус доплыть
				// BattleInterface.Commands.SailTo.EffectRadius = 3000 + 350*GetCharacterSPECIAL(pchar, "Perception");
				/*
				if (CheckMainHeroMap("map_barbados") && Islands[iIsland].id == "Barbados") 				break;
				if (CheckMainHeroMap("map_jam") && Islands[iIsland].id == "Jamaica") 					break;
				if (CheckMainHeroMap("map_puerto") && Islands[iIsland].id == "PuertoRico") 				break;

				bool bCubaAll = (Islands[iIsland].id == "Cuba1") || (Islands[iIsland].id == "Cuba2");
				if (CheckMainHeroMap("map_cuba") && bCubaAll) 								break;

				if (CheckMainHeroMap("map_Curacao") && Islands[iIsland].id == "Curacao") 				break;
				if (CheckMainHeroMap("map_TORTUGA") && Islands[iIsland].id == "Tortuga") 				break;
				if (CheckMainHeroMap("map_sm") && Islands[iIsland].id == "SentMartin") 					break;
				if (CheckMainHeroMap("map_trinidad") && Islands[iIsland].id == "Trinidad") 				break;
				if (CheckMainHeroMap("map_nevis") && Islands[iIsland].id == "Nevis") 					break;
				if (CheckMainHeroMap("map_antigua") && Islands[iIsland].id == "Antigua") 				break;
				if (CheckMainHeroMap("map_guad") && Islands[iIsland].id == "Guadeloupe") 				break;
				if (CheckMainHeroMap("map_martiniqua") && Islands[iIsland].id == "Martinique") 				break;

				bool bHispAll = (Islands[iIsland].id == "Hispaniola1") || (Islands[iIsland].id == "Hispaniola2");
				if (CheckMainHeroMap("map_hisp") && bHispAll) 								break;

				if (!CheckMainHeroMap("map_bermudas") && Islands[iIsland].id == "Bermudes") 				break;
				if (CheckMainHeroMap("map_dominica") && Islands[iIsland].id == "Dominica") 				break;
				if (CheckMainHeroMap("map_terks") && Islands[iIsland].id == "Terks") 					break;
				if (CheckMainHeroMap("map_cayman") && Islands[iIsland].id == "Caiman") 					break;
				if (CheckMainHeroMap("map_beliz") && Islands[iIsland].id == "Beliz") 					break;
				if (CheckMainHeroMap("map_santa") && Islands[iIsland].id == "SantaCatalina") 				break;

				bool bMain1 = (Islands[iIsland].id == "Cartahena") || (Islands[iIsland].id == "PortoBello");
				if (CheckMainHeroMap("map_maine_1") && bMain1) 								break;

				bool bMain2 = (Islands[iIsland].id == "Maracaibo") || (Islands[iIsland].id == "Cumana") || (Islands[iIsland].id == "Caracas");
				if (CheckMainHeroMap("map_maine_2") && bMain2) 								break;

				BattleInterface.Commands.SailTo.EffectRadius = (3000 + 300*GetCharacterSPECIAL(pchar, "Perception"))/4;
				*/
			}
		break;
	}

	return &BI_retComValue;
}

void BI_LaunchCommand()
{
	bool bOk;
	int charIdx = GetEventData();
	string commandName = GetEventData();
	int targetNum = GetEventData();
	string locName = GetEventData();
	ref chRef = GetCharacter(charIdx);

	BI_DeactivateSelectTip();

	if (LAi_IsDead(chRef)) return;

	aref arFader;
	if (GetEntity(arFader,"fader")) return;

	if (targetNum == -1 && locName == "cancel")
	{
		SendMessage(&BattleInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");
		return;
	}
	if (commandName == "cancel")
	{
		SendMessage(&BattleInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");
		return;
	}

	string alternativeCommand;
	if (CheckAttribute( &BattleInterface, "AbilityIcons."+commandName+".quest" ))
	{
		alternativeCommand = commandName;
		commandName = "BI_UseItemAbilitie";
	}

	switch (commandName)
	{
		case "BI_Cabin":		Sea_CabinStartNow();	break;
		case "BI_MyHold":		Sea_HoldStartNow();		break;
		case "BI_Moor":			Sea_LandLoad();			break;
        case "BI_Board":		Sea_AbordageLoad(SHIP_ABORDAGE, true);	break;
       	case "BI_LandTroops":	Sea_AbordageLoad(FORT_ABORDAGE, true);	break;

		case "BI_Mine":
			if (GetCargoGoods(chRef, GOOD_POWDER) >= 200 && GetRemovable(chRef)) SetMineFree(chRef, 1);
			else PlayInterfaceCommand("interface\knock.wav");
		break;

		case "BI_Boat":
			// Warship 09.07.09 Мэри Селест // Второй раз на неё выслать шлюпку низя
			if (Characters[targetNum].id != "MaryCelesteCapitan" || PChar.QuestTemp.MaryCeleste != "OnDeck")
				Sea_DeckBoatLoad(targetNum);
			else PlayInterfaceCommand("knock");
		break;

		case "BI_SailTowards":
			float posX = stf(Characters[charIdx].Ship.Pos.x);
			float posZ = stf(Characters[charIdx].Ship.Pos.z);
			float fAng;
			switch(locName)
			{
				case "dir_n":
					posZ += SAILDIR_POS_DIF;
					Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				break;
				case "dir_ne":
					fAng = PIm2 * 0.125;
					posX = posX + sin(fAng) * SAILDIR_POS_DIF;
					posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
					Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				break;
				case "dir_e":
					posX += SAILDIR_POS_DIF;
					Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				break;
				case "dir_se":
					fAng = PIm2 * 0.375;
					posX = posX + sin(fAng) * SAILDIR_POS_DIF;
					posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
					Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				break;
				case "dir_s":
					posZ -= SAILDIR_POS_DIF;
					Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				break;
				case "dir_sw":
					fAng = PIm2 * 0.625;
					posX = posX + sin(fAng) * SAILDIR_POS_DIF;
					posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
					Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				break;
				case "dir_w":
					posX -= SAILDIR_POS_DIF;
					Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				break;
				case "dir_nw":
					fAng = PIm2 * 0.875;
					posX = posX + sin(fAng) * SAILDIR_POS_DIF;
					posZ = posZ + cos(fAng) * SAILDIR_POS_DIF;
					Ship_SetTaskMove(SECONDARY_TASK, charIdx, posX, posZ);
				break;
			}
			PlayVoice("INTERFACE\Ships_Bell.wav");
		break;

		case "BI_Charge":
			int chargeType = GOOD_BALLS;
			switch (targetNum)
			{
				case 1:
					if (sti(chRef.ship.cargo.goods.balls) < 1)
					{
						PlayInterfaceCommand("knock");
						return;
					}
					//PlayCharVoice("ChargeBalls");
					SendMessage(&Sound, "lslllll", MSG_SOUND_PLAY, "ChargeBalls", SOUND_WAV_STEREO, VOLUME_SPEECH, false, false, false);
					chargeType = GOOD_BALLS;
				break;
				case 2:
					if (sti(chRef.ship.cargo.goods.grapes) < 1)
					{
						PlayInterfaceCommand("knock");
						return;
					}
//					LaunchInfoMessage(2); // сообщение о картечи
					//PlayCharVoice("ChargeGrapes");
					SendMessage(&Sound, "lslllll", MSG_SOUND_PLAY, "ChargeGrapes", SOUND_WAV_STEREO, VOLUME_SPEECH, false, false, false);
					chargeType = GOOD_GRAPES;
				break;
				case 3:
					if (sti(chRef.ship.cargo.goods.knippels) < 1)
					{
						PlayVoice("knock");
						return;
					}
					//PlayCharVoice("ChargeKnippels");
					SendMessage(&Sound, "lslllll", MSG_SOUND_PLAY, "ChargeKnippels", SOUND_WAV_STEREO, VOLUME_SPEECH, false, false, false);
					chargeType = GOOD_KNIPPELS;
				break;
				case 4:
					if (sti(chRef.ship.cargo.goods.bombs) < 1)
					{
						PlayInterfaceCommand("knock");
						return;
					}
					//PlayCharVoice("ChargeBombs");
					SendMessage(&Sound, "lslllll", MSG_SOUND_PLAY, "ChargeBombs", SOUND_WAV_STEREO, VOLUME_SPEECH, false, false, false);
					chargeType = GOOD_BOMBS;
				break;
			}
			Ship_ChangeCharge(chRef, chargeType);
			// исходим из того, что приказы через команды дают токо ГГ и его офам, офы выбирают какой снаряд, поэтому команду запоминаем для них
			chRef.ShipCannonChargeType = chargeType;
		break;

		case "BI_Map":
			if (bMapEnter) Sea_MapLoad(); //pchar.location = "";	// boal не помню уже зачем, в ВМЛ было
			else Log_SetStringToLog(XI_ConvertString("Map is closed"));
		break;

		case "BI_SailAway":
			if (CheckAttribute(&characters[charIdx], "SeaAI.Task.Target"))  //fix
				Ship_SetTaskRunAway(SECONDARY_TASK, charIdx, sti(characters[charIdx].SeaAI.Task.Target));
			else	// boal fix если вдруг нет, то от ГГ удаляться
				Ship_SetTaskRunAway(SECONDARY_TASK, charIdx, GetMainCharacterIndex());
			PlayVoice("INTERFACE\Ships_Bell.wav");
		break;
		case "BI_HeaveToDrift":
			Ship_SetTaskDrift(SECONDARY_TASK,charIdx);
		break;
		case "BI_Defend":
			Ship_SetTaskDefend(SECONDARY_TASK,charIdx, GetTargChrIndex(targetNum,locName));
			DeleteAttribute(chRef, "ShipCannonChargeType"); // флаг офов, чем пулять постоянно, ставится игроком командами, до след приказа Атака или конца снарядов
		break;
		case "BI_Attack":
			Ship_SetTaskAttack(SECONDARY_TASK,charIdx, GetTargChrIndex(targetNum,locName));
			DeleteAttribute(chRef, "ShipCannonChargeType"); // флаг офов, чем пулять постоянно, ставится игроком командами, до след приказа Атака или конца снарядов
		break;
		case "BI_Abordage":
			Ship_SetTaskAbordage(SECONDARY_TASK,charIdx, GetTargChrIndex(targetNum,locName));
		break;
		case "BI_Reload":
			if (bi_nReloadTarget != -1) LaunchTransferMain(chRef, GetCharacter(bi_nReloadTarget), "Transfer");
		break;
		case "BI_SailTo":
			/*if(targetNum==-1)
			{ // приплыть в локатор с именем locName
				if( !IsEntity(&SailToFader) ) {SeaAI_SailToLocator(locName);}
			}
			else
			{ // догнать перса с индексом targetNum
				if( !IsEntity(&SailToFader) ) {SeaAI_SailToCharacter(targetNum);}
			} */
			// boal 09.02.2004 -->
			if (bDisableMapEnter && !bBettaTestMode)
			{
				PlayInterfaceCommand("knock");
				break;
			}
			if (!CheckEnemyCompanionDistance2GoAway(false) && !bBettaTestMode)  // компаньон в беде
			{
				PlayInterfaceCommand("knock");
				break;
			}
			// boal 09.02.2004 <--
			if (targetNum == -1)
			{ // приплыть в локатор с именем locName
				bOk = true;

				if (MOD_SKILL_ENEMY_RATE >= 2 && !bBettaTestMode)
				{
					targetNum = Fort_FindCharacter(AISea.Island,"reload",locName);
					if (targetNum == -1) // тут нужна проверка на город-враг ищем форт по порту
					{
						targetNum = Fort_FindCharacterByPort(AISea.Island, locName);
					}
				}
				if (targetNum >= 0)
				{
					if (GetRelation(sti(pchar.index), targetNum) == RELATION_ENEMY && !CheckAttribute(&Characters[targetNum], "CanBeSailTo"))
					{
						if (sti(Characters[targetNum].Fort.Mode) == FORT_NORMAL)
						{
							bOk = false;
						}
					}
				}
				if (bOk)
				{
					if (!IsEntity(&SailToFader))
					{
						SeaAI_SailToLocator(locName);
					}
				}
				else PlayInterfaceCommand("knock");
			}
			else
			{	// догнать перса с индексом targetNum
				// --> boal плывем только к друзьям или спец персам (потопить пирата)
				if (GetRelation(sti(pchar.index), targetNum) != RELATION_ENEMY || CheckAttribute(&Characters[targetNum], "CanBeSailTo") || bBettaTestMode)
				{
					if (!IsEntity(&SailToFader)) SeaAI_SailToCharacter(targetNum);
				}
				else PlayInterfaceCommand("knock");
				// <-- boal плывем только к друзьям или спец персам (потопить пирата)
			}
		break;
		case "BI_ImmDeath":
			if (targetNum==-1)
			{ // смерть форта
				targetNum = Fort_FindCharacter(AISea.Island,"reload",locName);
				if (targetNum>=0) Fort_SetAbordageMode(pchar, GetCharacter(targetNum));
			}
			else ShipDead(targetNum,KILL_BY_BALL,nMainCharacterIndex);
		break;

		case "BI_InstantBoarding":
			ActivateCharacterPerk(GetCharacter(charIdx), "InstantBoarding");
			CharacterPerkOff(GetCharacter(charIdx), "InstantBoarding");
			if (CheckSuccesfullBoard(GetCharacter(charIdx), GetCharacter(targetNum)))
				Sea_AbordageStartNow(SHIP_ABORDAGE,targetNum,true,true);
			else
			{
				Log_SetStringToLog(XI_ConvertString("failed to board"));
				Event("BI_LaunchCommand","lsls", charIdx, "BI_SailTo", targetNum, locName);
				return;
			}
		break;

		case "BI_Brander":	//ActivateCharacterPerk(pchar,"Brander"); - многоразовый приказ
			Ship_SetTaskBrander(SECONDARY_TASK, charIdx, targetNum);
		break;
		case "BI_ImmediateReload":
			ActivateCharacterPerk(GetCharacter(charIdx), "ImmediateReload");
		break;
		case "BI_LightRepair":
			ActivateCharacterPerk(GetCharacter(charIdx), "LightRepair");
			ActivateSpecRepair(GetCharacter(charIdx), 0);
		break;
		case "BI_InstantRepair":
			ActivateCharacterPerk(GetCharacter(charIdx), "InstantRepair");
			ActivateSpecRepair(GetCharacter(charIdx), 1);
		break;
		case "BI_Turn180":
			ActivateCharacterPerk(GetCharacter(charIdx), "Turn180");
			Ship_Turn180(GetCharacter(charIdx));
		break;
		case "BI_UseItemAbilitie": // items abilities
			CompleteQuestName(BattleInterface.AbilityIcons.(alternativeCommand).quest, "");
		break;
		//case "BI_Ability": Event("evntSetUsingAbility","l", charIdx); break;
	}
	//BI_SetCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1);
	BI_SetSpecCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1, 0);
}

void BI_SetIslandData()
{
    if (!CheckAttribute(&AISea, "Island"))
	{
		trace("ERROR: BI_SetIslandData - has bug");
		return; // boal 26.03.04 fix
	}
	int isln = FindIsland(AISea.Island);
	if (isln == -1) return;

	ref atmp;
	atmp = GetIslandByIndex(isln);
	SendMessage(&BattleInterface,"la",BI_MSG_SET_ISLAND,atmp);
}

void BI_UpdateShip()
{
	int charIndex = GetEventData();
	AddShipToInterface(charIndex);
}

void BI_CreateShip()
{
	int charIndex = GetEventData();
	if (charIndex >= 0) ClearActiveChrPerks(GetCharacter(charIndex));
	if (IsEntity(&BattleInterface)) AddShipToInterface(charIndex);
}

void AddShipToInterface(int charIndex)
{
	if (charIndex == -1)
	{
		Trace("ERROR: Invalid character index for create ship");
		return;
	}
	ref chRef = GetCharacter(charIndex);
	int st = GetCharacterShipType(chRef);
	if (st == SHIP_NOTUSED)
	{
		Trace("WARNING!!! Character id = "+chRef.id+" hav`t ship.");
		return;
	}
	ref shipRef = GetRealShip(st);
	
	int idx, i;
	
	if (CheckAttribute(chRef, "curshipnum")) idx = sti(chRef.curshipnum);
	else
	{
		for(i = 0; i < MAX_SHIPS_ON_SEA; i++)
		{
			if(Ships[i] == charIndex)
			{
				idx = i;
				chRef.curshipnum = i;
			}
		}
	}
	if (idx < 0) 
	{
		for(i = 0; i < 4; i++)
		{
			if (GetCompanionIndex(pchar, i) >= 0 && GetRemovable(GetCharacter(GetCompanionIndex(pchar, i))))
			{
				if (GetCompanionIndex(pchar, i) == charIndex) 
				{
					idx = i;
					chRef.curshipnum = i;
				}
			}
		}
	}
		
	int myShip = false;
	int shipRelation = BI_RELATION_NEUTRAL;
	switch (SeaAI_GetRelation(charIndex,nMainCharacterIndex))
	{
		case RELATION_FRIEND: shipRelation = BI_RELATION_FRIEND; break;
		case RELATION_ENEMY: shipRelation = BI_RELATION_ENEMY; break;
	}

	for(i = 0; i < COMPANION_MAX; i++)
	{
		if (GetCompanionIndex(pchar,i) == charIndex)
		{
			myShip = true;
		}
	}


	if (CharacterIsDead(chRef))
	{
		if (!CheckAttribute(chRef,"ship.shipsink") || sti(chRef.ship.shipsink) == false)
			return;
	}

	SendMessage(&BattleInterface, "llaall", BI_IN_CREATE_SHIP, charIndex, chRef, shipRef, myShip, shipRelation);
}

void BI_DeleteShip()
{
	int charIndex = GetEventData();
	if (charIndex ==- 1)
	{
		Trace("ERROR: Invalid character index");
		return;
	}
	if (IsCompanion(GetCharacter(charIndex))) RemoveCharacterCompanion(pchar,GetCharacter(charIndex));
	DeleteAttribute(GetCharacter(charIndex), "ship.shipsink");
	DeleteAttribute(GetCharacter(charIndex), "curshipnum");
	RefreshBattleInterface();
}

void BI_DeadShip()
{
	int charIndex = GetEventData();
	if (charIndex==-1)
	{
		Trace("ERROR: Invalid character index");
		return;
	}
	if (IsCompanion(GetCharacter(charIndex)))
	{
		// Hokkins: скроем весь интерфейс, если у ГГ нет компаньонов.
		if (GetCompanionQuantity(pchar) > 1) RemoveCharacterCompanion(pchar,GetCharacter(charIndex));
		else ChangeShowIntarface();
		 // Hokkins: так же скрываем интерфейс, если наш корабль потопили, но в эскадре есть корабли.
		if(CharacterIsDead(pchar) && GetCompanionQuantity(pchar) > 1) ChangeShowIntarface();
	}
	Characters[charIndex].ship.shipsink = true;
	RefreshBattleInterface();
}

void BI_SetCommandMode(int commode, int texNum, int picNum, int chIdx)
{
	bi_icons_CommandMode = commode;
	SendMessage(&BattleInterface,"llllll",BI_IN_SET_COMMAND_MODE,commode,texNum,picNum,chIdx,-1);
}

void BI_SetSpecCommandMode(int commode, int texNum, int picNum, int chIdx, int comState)
{
	bi_icons_CommandMode = commode;
	SendMessage(&BattleInterface,"llllll",BI_IN_SET_COMMAND_MODE,commode,texNum,picNum,chIdx,comState);
}

void BI_SetPossibleCommands()
{
	int chIdx = GetEventData();
	ref rShip = GetRealShip(sti(pchar.ship.type));
    int iClass = sti(rShip.Class);
    BI_DeactivateSelectTip();

	if (chIdx < 0 || CharacterIsDead(GetCharacter(chIdx)))
	{
		aref aroot,arcur;
		makearef(aroot,BattleInterface.Commands);
		int q = GetAttributesNum(aroot);
		for (int i = 0; i < q; i++)
		{
			arcur = GetAttributeN(aroot,i);
			arcur.enable = false;
		}
		//BattleInterface.Commands.Cancel.enable = true;
		return;
	}

	// для главного персонажа
	if (sti(pchar.index) == chIdx)
	{
		BattleInterface.Commands.ImmediateDeath.enable	= bBettaTestMode; // boal cheat
		BattleInterface.Commands.InstantBoarding.enable	= bBettaTestMode; // boal cheat
		if (iClass < 7) BattleInterface.Commands.MyHold.enable = !GetGlobalTutor();
		else BattleInterface.Commands.MyHold.enable		= false;

		if (CheckAttribute(&TEV, "DesMoinesMoorDisable") && Sea_FindNearColony(0) == "DesMoines_town")
			BattleInterface.Commands.Moor.enable		= or(false, bBettaTestMode);
		else
			BattleInterface.Commands.Moor.enable		= bCanEnterToLand;

		BattleInterface.Commands.Board.enable			= bAbordageShipCanBe;
		BattleInterface.Commands.SailAway.enable		= false;
		BattleInterface.Commands.HeaveToDrift.enable	= false;
		BattleInterface.Commands.Charge.enable			= false;
		BattleInterface.Commands.LandTroops.enable		= bAbordageFortCanBe;
		BattleInterface.Commands.Attack.enable			= false;
		BattleInterface.Commands.Defend.enable			= false;
		BattleInterface.Commands.Reload.enable			= bReloadCanBe;
		BattleInterface.Commands.Abordage.enable		= false;
		BattleInterface.Commands.SailTo.enable			= !bDisableSailTo && bSailTo;
		BattleInterface.Commands.Map.enable				= bMapEnter;
		if (sti(RealShips[sti(pchar.Ship.Type)].BaseType) < SHIP_BOAT)
        {
            BattleInterface.Commands.Cabin.enable		= !GetGlobalTutor();
        }
        BattleInterface.Commands.Boat.enable			= !GetGlobalTutor();
        BattleInterface.Commands.SailTowards.enable		= false;
	}
	// для спутников
	else
	{
		BattleInterface.Commands.SailTowards.enable		= true;
		BattleInterface.Commands.MyHold.enable			= false;
		BattleInterface.Commands.Moor.enable			= false;
		BattleInterface.Commands.Board.enable			= false;
		BattleInterface.Commands.SailAway.enable		= true;
		BattleInterface.Commands.HeaveToDrift.enable	= true;
		BattleInterface.Commands.Charge.enable			= CheckAttribute(GetCharacter(chIdx), "Ship.Cannons.Charge.Type"); // 1.2.4
		BattleInterface.Commands.LandTroops.enable		= false;
		BattleInterface.Commands.Attack.enable			= bAttack;
		BattleInterface.Commands.Abordage.enable	    = CanAbordage(GetCharacter(chIdx));
		BattleInterface.Commands.Defend.enable			= bDefend;
		BattleInterface.Commands.Reload.enable			= false;
		BattleInterface.Commands.SailTo.enable			= false;
		BattleInterface.Commands.Map.enable				= false;
		BattleInterface.Commands.ImmediateDeath.enable  = false; // boal
		BattleInterface.Commands.InstantBoarding.enable  = false; // boal
		BattleInterface.Commands.Cabin.enable			= false;
        BattleInterface.Commands.Boat.enable			= false; //boal
	}
    Event("evntSetUsingAbility","l", chIdx);
}

void BI_InitializeCommands()
{

	DeleteAttribute(&BattleInterface,"Commands");
	DeleteAttribute(&BattleInterface,"AbilityIcons");

	BattleInterface.Commands.Cancel.enable			= false;
	BattleInterface.Commands.Cancel.picNum			= 1;
	BattleInterface.Commands.Cancel.selPicNum		= 0;
	BattleInterface.Commands.Cancel.texNum			= 2;
	BattleInterface.Commands.Cancel.event			= "Cancel";
	BattleInterface.Commands.Cancel.note			= LanguageConvertString(iCommandsFile, "sea_Cancel");

	BattleInterface.Commands.Moor.enable			= false;
	BattleInterface.Commands.Moor.picNum			= 29;
	BattleInterface.Commands.Moor.selPicNum			= 13;
	BattleInterface.Commands.Moor.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Moor.event				= "BI_Moor";
	BattleInterface.Commands.Moor.note				= LanguageConvertString(iCommandsFile, "sea_Moor");

	BattleInterface.Commands.SailTo.enable			= false;
	BattleInterface.Commands.SailTo.picNum			= 16;
	BattleInterface.Commands.SailTo.selPicNum		= 0;
	BattleInterface.Commands.SailTo.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SailTo.event			= "BI_SailTo";
	BattleInterface.Commands.SailTo.note			= LanguageConvertString(iCommandsFile, "sea_SailTo");

	BattleInterface.Commands.Board.enable			= false;
	BattleInterface.Commands.Board.picNum			= 30;
	BattleInterface.Commands.Board.selPicNum		= 14;
	BattleInterface.Commands.Board.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Board.event			= "BI_Board";
	BattleInterface.Commands.Board.note				= LanguageConvertString(iCommandsFile, "sea_Board");

	BattleInterface.Commands.LandTroops.enable		= false;
	BattleInterface.Commands.LandTroops.picNum		= 42;
	BattleInterface.Commands.LandTroops.selPicNum	= 45;
	BattleInterface.Commands.LandTroops.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.LandTroops.event		= "BI_LandTroops";
	BattleInterface.Commands.LandTroops.note		= LanguageConvertString(iCommandsFile, "sea_LandTroops");

	BattleInterface.Commands.Map.enable				= false;
	BattleInterface.Commands.Map.picNum				= 28;
	BattleInterface.Commands.Map.selPicNum			= 12;
	BattleInterface.Commands.Map.texNum				= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Map.event				= "BI_Map";
	BattleInterface.Commands.Map.note				= LanguageConvertString(iCommandsFile, "sea_Map");

	BattleInterface.Commands.Attack.enable			= false;
	BattleInterface.Commands.Attack.picNum			= 49;
	BattleInterface.Commands.Attack.selPicNum		= 33;
	BattleInterface.Commands.Attack.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Attack.event			= "BI_Attack";
	BattleInterface.Commands.Attack.note			= LanguageConvertString(iCommandsFile, "sea_Attack");

	BattleInterface.Commands.Abordage.enable		= false;
	BattleInterface.Commands.Abordage.picNum		= 30;
	BattleInterface.Commands.Abordage.selPicNum		= 14;
	BattleInterface.Commands.Abordage.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Abordage.event			= "BI_Abordage";
	BattleInterface.Commands.Abordage.note			= LanguageConvertString(iCommandsFile, "sea_Abordage");

	BattleInterface.Commands.SailAway.enable		= false;
	BattleInterface.Commands.SailAway.picNum		= 50;
	BattleInterface.Commands.SailAway.selPicNum		= 34;
	BattleInterface.Commands.SailAway.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SailAway.event			= "BI_SailAway";
	BattleInterface.Commands.SailAway.note			= LanguageConvertString(iCommandsFile, "sea_SailAway");

	BattleInterface.Commands.HeaveToDrift.enable	= false;
	BattleInterface.Commands.HeaveToDrift.picNum	= 25;
	BattleInterface.Commands.HeaveToDrift.selPicNum	= 9;
	BattleInterface.Commands.HeaveToDrift.texNum	= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.HeaveToDrift.event		= "BI_HeaveToDrift";
	BattleInterface.Commands.HeaveToDrift.note		= LanguageConvertString(iCommandsFile, "sea_HeaveToDrift");

	BattleInterface.Commands.Reload.enable			= false;
	BattleInterface.Commands.Reload.picNum			= 48;
	BattleInterface.Commands.Reload.selPicNum		= 32;
	BattleInterface.Commands.Reload.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Reload.event			= "BI_Reload";
	BattleInterface.Commands.Reload.note			= LanguageConvertString(iCommandsFile, "sea_Reload");

	BattleInterface.Commands.Charge.enable			= false;
	BattleInterface.Commands.Charge.picNum			= 17;
	BattleInterface.Commands.Charge.selPicNum		= 1;
	BattleInterface.Commands.Charge.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Charge.event			= "BI_Charge";
	BattleInterface.Commands.Charge.note			= LanguageConvertString(iCommandsFile, "sea_Charge");

	BattleInterface.Commands.Defend.enable			= false;
	BattleInterface.Commands.Defend.picNum			= 51;
	BattleInterface.Commands.Defend.selPicNum		= 35;
	BattleInterface.Commands.Defend.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Defend.event			= "BI_Defend";
	BattleInterface.Commands.Defend.note			= LanguageConvertString(iCommandsFile, "sea_Defend");

	BattleInterface.Commands.SailTowards.enable		= false;
	BattleInterface.Commands.SailTowards.picNum		= 16;
	BattleInterface.Commands.SailTowards.selPicNum	= 0;
	BattleInterface.Commands.SailTowards.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.SailTowards.event		= "BI_SailTowards";
	BattleInterface.Commands.SailTowards.note		= LanguageConvertString(iCommandsFile, "sea_SailTowards");

	BattleInterface.Commands.Ability.enable			= false;
	BattleInterface.Commands.Ability.picNum			= 27;
	BattleInterface.Commands.Ability.selPicNum		= 11;
	BattleInterface.Commands.Ability.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Ability.event			= "BI_Ability";
	BattleInterface.Commands.Ability.note			= LanguageConvertString(iCommandsFile, "sea_Ability");
	
	BattleInterface.Commands.Boat.enable			= false;
	BattleInterface.Commands.Boat.picNum			= 26;
	BattleInterface.Commands.Boat.selPicNum			= 10;
	BattleInterface.Commands.Boat.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Boat.event				= "BI_Boat";
	BattleInterface.Commands.Boat.note				= LanguageConvertString(iCommandsFile, "sea_SendBoat");
	
	BattleInterface.Commands.Cabin.enable			= false;
	BattleInterface.Commands.Cabin.picNum			= 27;
	BattleInterface.Commands.Cabin.selPicNum		= 11;
	BattleInterface.Commands.Cabin.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Cabin.event			= "BI_Cabin";
	BattleInterface.Commands.Cabin.note	   			= LanguageConvertString(iCommandsFile, "sea_Cabin");
	
	BattleInterface.Commands.ImmediateDeath.enable	= false;
	BattleInterface.Commands.ImmediateDeath.picNum	= 43;    // это чит
	BattleInterface.Commands.ImmediateDeath.selPicNum	= 43;
	BattleInterface.Commands.ImmediateDeath.texNum	= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.ImmediateDeath.event	= "BI_ImmDeath";
	BattleInterface.Commands.ImmediateDeath.note	= LanguageConvertString(iCommandsFile, "sea_ImmediateDeath");

	BattleInterface.Commands.Brander.enable			= false;
	BattleInterface.Commands.Brander.picNum			= 52;
	BattleInterface.Commands.Brander.selPicNum		= 36;
	BattleInterface.Commands.Brander.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Brander.event			= "BI_Brander";
    BattleInterface.Commands.Brander.note			= GetConvertStr("Brander", "AbilityDescribe.txt");
    
	BattleInterface.Commands.ImmediateReload.enable			= false;
	BattleInterface.Commands.ImmediateReload.picNum			= 53;
	BattleInterface.Commands.ImmediateReload.selPicNum		= 37;
	BattleInterface.Commands.ImmediateReload.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.ImmediateReload.event			= "BI_ImmediateReload";
    BattleInterface.Commands.ImmediateReload.note			= GetConvertStr("ImmediateReload", "AbilityDescribe.txt");
    
	BattleInterface.Commands.InstantBoarding.enable			= false;
	BattleInterface.Commands.InstantBoarding.picNum			= 30;   // это чит
	BattleInterface.Commands.InstantBoarding.selPicNum		= 14;
	BattleInterface.Commands.InstantBoarding.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.InstantBoarding.event			= "BI_InstantBoarding";
    BattleInterface.Commands.InstantBoarding.note			= GetConvertStr("InstantBoarding", "AbilityDescribe.txt");

	BattleInterface.Commands.LightRepair.enable			= false;
	BattleInterface.Commands.LightRepair.picNum			= 38;
	BattleInterface.Commands.LightRepair.selPicNum		= 54;
	BattleInterface.Commands.LightRepair.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.LightRepair.event			= "BI_LightRepair";
	BattleInterface.Commands.LightRepair.note			= GetConvertStr("LightRepair", "AbilityDescribe.txt");
	
	BattleInterface.Commands.InstantRepair.enable		= false;
	BattleInterface.Commands.InstantRepair.picNum		= 55;
	BattleInterface.Commands.InstantRepair.selPicNum	= 39;
	BattleInterface.Commands.InstantRepair.texNum		= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.InstantRepair.event		= "BI_InstantRepair";
	BattleInterface.Commands.InstantRepair.note			= GetConvertStr("InstantRepair", "AbilityDescribe.txt");
	
	BattleInterface.Commands.Turn180.enable				= false;
	BattleInterface.Commands.Turn180.picNum				= 56;
	BattleInterface.Commands.Turn180.selPicNum			= 40;
	BattleInterface.Commands.Turn180.texNum				= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Turn180.event				= "BI_Turn180";
	BattleInterface.Commands.Turn180.note				= GetConvertStr("Turn180", "AbilityDescribe.txt");

	BattleInterface.Commands.MyHold.enable			= false;
	BattleInterface.Commands.MyHold.picNum			= 75;
	BattleInterface.Commands.MyHold.selPicNum		= 74;
	BattleInterface.Commands.MyHold.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.MyHold.event			= "BI_MyHold";
	BattleInterface.Commands.MyHold.note	    	= LanguageConvertString(iCommandsFile, "sea_Hold");

	BattleInterface.Commands.Mine.enable			= false;
	BattleInterface.Commands.Mine.picNum			= 67;
	BattleInterface.Commands.Mine.selPicNum			= 66;
	BattleInterface.Commands.Mine.texNum			= BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.Commands.Mine.event				= "BI_Mine";
	BattleInterface.Commands.Mine.note	    		= LanguageConvertString(iCommandsFile, "sea_Mine");
}

ref BI_GetChargeQuantity()
{
	int chIdx = GetEventData();
	ref chr = GetCharacter(chIdx);
	BI_ChargeState[0] = 4;
	BI_ChargeState[1] = GetCargoGoods(chr, GOOD_BALLS);
	BI_ChargeState[2] = GetCargoGoods(chr, GOOD_GRAPES);
	BI_ChargeState[3] = GetCargoGoods(chr, GOOD_KNIPPELS);
	BI_ChargeState[4] = GetCargoGoods(chr, GOOD_BOMBS);

	return &BI_ChargeState;
}

ref GetCurrentCharge()
{
	BI_intNRetValue[0] = 8; //wind
	BI_intNRetValue[3] = 24; //balls
	BI_intNRetValue[4] = 25; //grape
	BI_intNRetValue[5] = 26; //knipp
	BI_intNRetValue[6] = 27; //boom
	BI_intNRetValue[7] = -1; //blink for current charge
	//if (CheckAttribute(pchar,"Ship.Cannons.Charge.Type")) //HardCoffee TODO
	switch (sti(pchar.Ship.Cannons.Charge.Type))
	{
		case GOOD_BALLS:
			BI_intNRetValue[3] = 16;
			if (bNotEnoughBalls)
			{
				if (iChargeBlinks < BLINKS_TIME)
				{
					iChargeBlinks++;
					BI_intNRetValue[7] = 1;
				}
				//else BI_intNRetValue[3] = 28;
			}
		break;
		case GOOD_GRAPES:
			BI_intNRetValue[4] = 17;
			if (bNotEnoughBalls)
			{
				if (iChargeBlinks < BLINKS_TIME)
				{
					iChargeBlinks++;
					BI_intNRetValue[7] = 2;
				}
				//else BI_intNRetValue[4] = 31;
			}
		break;
		case GOOD_KNIPPELS:
			BI_intNRetValue[5] = 18;
			if (bNotEnoughBalls)
			{
				if (iChargeBlinks < BLINKS_TIME)
				{
					iChargeBlinks++;
					BI_intNRetValue[7] = 3;
				}
				//else BI_intNRetValue[5] = 30;
			}
		break;
		case GOOD_BOMBS:
			BI_intNRetValue[6] = 19;
			if (bNotEnoughBalls)
			{
				if (iChargeBlinks < BLINKS_TIME)
				{
					iChargeBlinks++;
					BI_intNRetValue[7] = 4;
				}
				//else BI_intNRetValue[6] = 29;
			}
		break;
	}
/* //lack of ammo icons
	if (sti(pchar.ship.cargo.goods.balls) < 1 && BI_intNRetValue[7] != 1 && BI_intNRetValue[3] != 28)
		BI_intNRetValue[3] = 8;
	if (sti(pchar.ship.cargo.goods.grapes) < 1 && BI_intNRetValue[7] != 2 && BI_intNRetValue[4] != 31)
		BI_intNRetValue[4] = 11;
	if (sti(pchar.ship.cargo.goods.knippels) < 1 && BI_intNRetValue[7] != 3 && BI_intNRetValue[5] != 30)
		BI_intNRetValue[5] = 10;
	if (sti(pchar.ship.cargo.goods.bombs) < 1 && BI_intNRetValue[7] != 4 && BI_intNRetValue[6] != 29)
		BI_intNRetValue[6] = 9;
*/
	BattleInterface.textinfo.ballsQty.text = pchar.ship.cargo.goods.balls;
	BattleInterface.textinfo.GrapesQty.text = pchar.ship.cargo.goods.grapes;
	BattleInterface.textinfo.KnippelsQty.text = pchar.ship.cargo.goods.knippels;
	BattleInterface.textinfo.BombsQty.text = pchar.ship.cargo.goods.bombs;

	//Mett: мониторим порох -->
	BI_intNRetValue[8] = 20;
	BI_intNRetValue[9] = 0;
	if (sti(pchar.ship.cargo.goods.powder) < 1)
	{
		//BI_intNRetValue[8] = 52;
		if (iPowderBlinks < BLINKS_TIME)
		{
			iPowderBlinks++;
			BI_intNRetValue[9] = 1;
		}
    }
    else
	{
	    iPowderBlinks = 0;
	}

	BattleInterface.textinfo.PowderQty.text = pchar.ship.cargo.goods.powder;
	// <---

	float fState = Ship_GetSailState(pchar);
	if (fState < 0.33)	BI_intNRetValue[1] = 2; //отображение текущего положения парусов
	else if (fState < 0.66) BI_intNRetValue[1] = 1;
	else BI_intNRetValue[1] = 0;

	BI_intNRetValue[10] = 21; //weapon
	BI_intNRetValue[11] = 22; //planks
	BI_intNRetValue[12] = 23; //Sailcloth
/*
	if (sti(pchar.ship.cargo.goods.weapon) < 1) BI_intNRetValue[10] = 13;
	if (sti(pchar.ship.cargo.goods.planks) < 1) BI_intNRetValue[11] = 14;
	if (sti(pchar.ship.cargo.goods.cloth) < 1) BI_intNRetValue[12] = 15;
*/
	BattleInterface.textinfo.weaponQty.text = pchar.ship.cargo.goods.weapon;
	BattleInterface.textinfo.planksQty.text = pchar.ship.cargo.goods.planks;
	BattleInterface.textinfo.clothQty.text = pchar.ship.cargo.goods.sailcloth;

	// Обновление статуса для перков
	SeaPerkShower_RefreshPerkForUsing();

	// Надпись HP и SP корабля ГГ
	if(CheckAttribute(pchar,"Ship.HP"))
		BattleInterface.ShipIcon.HPvalue = ""+sti(pchar.Ship.HP)+"/"+GetCharacterShipHP(pchar)+"";
	if(CheckAttribute(pchar,"Ship.SP"))
		BattleInterface.ShipIcon.SPvalue = ""+sti(pchar.Ship.SP)+"/"+100+"";

	return &BI_intNRetValue;
}

ref biGetCharacterShipClass()
{
	int nChrIdx = GetEventData();
	BI_intRetValue = 1;
	if( nChrIdx>=0 && nChrIdx<TOTAL_CHARACTERS ) {
		BI_intRetValue = GetCharacterShipClass( &Characters[nChrIdx] );
	}
	return &BI_intRetValue;
}

void BI_SetSeaState()
{
	bool bTmp;
	bSailTo = GetEventData();
	bTmp = GetEventData();
	bMapEnter = GetEventData();
	bAttack = GetEventData();
	bAbordage = bAttack;
	bDefend = GetEventData();
	bReloadCanBe = GetEventData();
	bi_nReloadTarget = GetEventData();
	bEnableIslandSailTo = bMapEnter;
	if (bDisableMapEnter || GetBan("Map")) bMapEnter = false;
	// boal хрен вам убираем - нужное это делов в игре bReloadCanBe = 0;//убираем перегруз товара кроме как через меню.
}

void SetShipPictureDataByShipTypeName(string sType)
{
	switch(sType)
	{
	// 7-й КЛАСС	(6 кораблей)
	case "Barkas":				BI_intNRetValue[0] = 0+0*16;	BI_intNRetValue[1] = 0+0*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Баркас
	case "Tartane":				BI_intNRetValue[0] = 2+0*16;	BI_intNRetValue[1] = 2+0*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тартана
	case "Liuto":				BI_intNRetValue[0] = 4+0*16;	BI_intNRetValue[1] = 4+0*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Леудо		
	case "WarTartane":			BI_intNRetValue[0] = 6+0*16;	BI_intNRetValue[1] = 6+0*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Дау
    case "Feluca":				BI_intNRetValue[0] = 8+0*16;	BI_intNRetValue[1] = 8+0*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фелюка
	case "Bilancetta":			BI_intNRetValue[0] = 10+0*16;	BI_intNRetValue[1] = 10+0*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тартана
	// 6-й КЛАСС	(5 кораблей)
    case "Lugger":				BI_intNRetValue[0] = 12+0*16;	BI_intNRetValue[1] = 12+0*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Люггер
	case "Lugger_w":			BI_intNRetValue[0] = 14+0*16;	BI_intNRetValue[1] = 14+0*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Люггер
	case "Sloop":				BI_intNRetValue[0] = 0+1*16;	BI_intNRetValue[1] = 0+1*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	//  Шлюп
	case "Sloop_w":				BI_intNRetValue[0] = 2+1*16;	BI_intNRetValue[1] = 2+1*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Воен. Шлюп
	case "Cutter":				BI_intNRetValue[0] = 4+1*16;	BI_intNRetValue[1] = 4+1*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Куттер
	// 5-й КЛАСС	(5 кораблей)
	case "Schooner":			BI_intNRetValue[0] = 6+1*16;	BI_intNRetValue[1] = 6+1*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Шхуна
	case "Schooner_w":			BI_intNRetValue[0] = 8+1*16;	BI_intNRetValue[1] = 8+1*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Воен. Шхуна
	case "Barque":				BI_intNRetValue[0] = 10+1*16;	BI_intNRetValue[1] = 10+1*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Барк
	case "Barque_w":			BI_intNRetValue[0] = 12+1*16;	BI_intNRetValue[1] = 12+1*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Усил. Барк
	case "Xebek_l":				BI_intNRetValue[0] = 14+1*16;	BI_intNRetValue[1] = 14+1*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Щебека
	// 4-й КЛАСС	(9 кораблей)
	case "Barkentine":			BI_intNRetValue[0] = 0+2*16;	BI_intNRetValue[1] = 0+2*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Баркентина
	case "Brigantine":			BI_intNRetValue[0] = 2+2*16;	BI_intNRetValue[1] = 2+2*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// ВБригантина
	case "Shnyava":				BI_intNRetValue[0] = 4+2*16;	BI_intNRetValue[1] = 4+2*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Шнява
	case "Fleut":				BI_intNRetValue[0] = 6+2*16;	BI_intNRetValue[1] = 6+2*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Флейт
	case "Brig_l":				BI_intNRetValue[0] = 8+2*16;	BI_intNRetValue[1] = 8+2*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Бриг
	case "Brig":				BI_intNRetValue[0] = 10+2*16;	BI_intNRetValue[1] = 10+2*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Бриг
	case "Caravel":				BI_intNRetValue[0] = 12+2*16;	BI_intNRetValue[1] = 12+2*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тор. Каравелла
	case "Caravel_w":			BI_intNRetValue[0] = 14+2*16;	BI_intNRetValue[1] = 14+2*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Воен.Каравелла
	case "Galeon_l":			BI_intNRetValue[0] = 0+3*16;	BI_intNRetValue[1] = 0+3*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Галеон
	// 3-й КЛАСС	(6 кораблей)
	case "Pinnace":				BI_intNRetValue[0] = 2+3*16;	BI_intNRetValue[1] = 2+3*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Пинас
	case "Caracca":				BI_intNRetValue[0] = 4+3*16;	BI_intNRetValue[1] = 4+3*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Каракка
	case "Corvette_l":			BI_intNRetValue[0] = 6+3*16;	BI_intNRetValue[1] = 6+3*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Корвет
	case "Corvette":			BI_intNRetValue[0] = 8+3*16;	BI_intNRetValue[1] = 8+3*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Корвет
	case "Polacre":				BI_intNRetValue[0] = 10+3*16;	BI_intNRetValue[1] = 10+3*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Полакр
	case "Galeon":				BI_intNRetValue[0] = 12+3*16;	BI_intNRetValue[1] = 12+3*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Галеон
	// 2-й КЛАСС	(4 кораблей)
	case "EastIndiaMan":		BI_intNRetValue[0] = 14+3*16;	BI_intNRetValue[1] = 14+3*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Ост-индец
	case "Galeon_h":			BI_intNRetValue[0] = 0+4*16;	BI_intNRetValue[1] = 0+4*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Галеон
	case "Frigate":				BI_intNRetValue[0] = 2+4*16;	BI_intNRetValue[1] = 2+4*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Фрегат
	case "Frigate_h":			BI_intNRetValue[0] = 4+4*16;	BI_intNRetValue[1] = 4+4*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Фрегат
	// 1-й КЛАСС	(4 кораблей)
	case "Lineship":			BI_intNRetValue[0] = 6+4*16;	BI_intNRetValue[1] = 6+4*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Военный
	case "Warship":				BI_intNRetValue[0] = 8+4*16;	BI_intNRetValue[1] = 8+4*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Линейный
	case "Battleship":			BI_intNRetValue[0] = 10+4*16;	BI_intNRetValue[1] = 10+4*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Боевой
	case "Manowar":				BI_intNRetValue[0] = 12+4*16;	BI_intNRetValue[1] = 12+4*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Мановар
	// Квестовые Корабли	(4 кораблей)
	case "SoleyRu":				BI_intNRetValue[0] = 14+4*16;	BI_intNRetValue[1] = 14+4*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Кор. Мановар Солей Руаяль
	case "Santisima":			BI_intNRetValue[0] = 0+5*16;	BI_intNRetValue[1] = 0+5*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Бы	стрый мановар
	case "BrigQeen":			BI_intNRetValue[0] = 2+5*16;	BI_intNRetValue[1] = 2+5*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Быстрая Бригантина Стрела
	case "BrigSW":				BI_intNRetValue[0] = 4+5*16;	BI_intNRetValue[1] = 4+5*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Бриг Морской Волк
	case "XebekVML":			BI_intNRetValue[0] = 6+5*16;	BI_intNRetValue[1] = 6+5*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Щебека Синяя Птица
	case "Corvette_quest":		BI_intNRetValue[0] = 8+5*16;	BI_intNRetValue[1] = 8+5*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Корвет Пес Войны
	case "Corvette_quest_o":	BI_intNRetValue[0] = 10+5*16;	BI_intNRetValue[1] = 10+5*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Корвет Пес Войны
	case "ArabellaShip":		BI_intNRetValue[0] = 12+5*16;	BI_intNRetValue[1] = 12+5*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Фрегат Арабелла - Синко Льягас
	case "FrigateQueen":		BI_intNRetValue[0] = 14+5*16;	BI_intNRetValue[1] = 14+5*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Быстрый Фрегат Королева
	case "Flyingdutchman":		BI_intNRetValue[0] = 0+6*16;	BI_intNRetValue[1] = 0+6*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Прокл. Корабль Призрак
	case "Flyingdutchman_o":	BI_intNRetValue[0] = 2+6*16;	BI_intNRetValue[1] = 2+6*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Летучий Голландец
	case "LuggerQuest":			BI_intNRetValue[0] = 4+6*16;	BI_intNRetValue[1] = 4+6*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Курьерский Люггер 
	case "Polacre_q":			BI_intNRetValue[0] = 6+6*16;	BI_intNRetValue[1] = 6+6*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Тяж. Полакр Призрак Тени
	//case "ArabellaShip_o":	BI_intNRetValue[0] = 8+6*16;	BI_intNRetValue[1] = 8+6*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Лег. Фрегат Арабелла - Синко Льягас
	case "Veinard":				BI_intNRetValue[0] = 10+6*16;	BI_intNRetValue[1] = 10+6*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Быстрый Шлюп - Вейнард
	case "Frigate_M":			BI_intNRetValue[0] = 12+6*16;	BI_intNRetValue[1] = 12+6*16 + 1;	BI_intNRetValue[2] = BI_ICONS_TEXTURE_SHIP1;	break;	// Быстрый Шлюп - Вейнард
	}
	BI_intNRetValue[3] = false;
}

void SetShipPictureDataByShipType(int st)
{
	if(st>=0 && st<SHIP_TYPES_QUANTITY)
	{
		SetShipPictureDataByShipTypeName( ShipsTypes[st].name );
	}
}

ref BI_GetData()
{
	int dataType = GetEventData();
	int chrIdx;
	ref chRef;

	switch(dataType)
	{
	// Получаем номер картинки корабля
	case BIDT_SHIPPICTURE:
		chRef = GetCharacter(GetEventData());
		if( CharacterIsDead(chRef) )
		{
			BI_intNRetValue[0] = 65;
			BI_intNRetValue[1] = 64; // выбранная черепушка
			BI_intNRetValue[2] = BI_ICONS_TEXTURE_COMMAND;
			BI_intNRetValue[3] = true;
			break;
		}
		int st = sti(chRef.Ship.Type);
		if (!CheckAttribute(&RealShips[st], "basetype")) Log_TestInfo("BIDT_SHIPPICTURE нет basetype у корабля НПС ID=" + chRef.id);
		st = sti(RealShips[st].basetype);
		SetShipPictureDataByShipType( st );
		break;

	case BIDT_GERALD_DATA:
			chrIdx = GetEventData();
			if(chrIdx<0) break;
			chRef = GetCharacter(chrIdx);
			BI_intNRetValue[0] = 8;
			switch( SeaAI_GetRelation(chrIdx,nMainCharacterIndex) )
			{
				case RELATION_FRIEND:	BI_intNRetValue[1] = 7;		break;
				case RELATION_NEUTRAL:	BI_intNRetValue[1] = -1;	break;
				case RELATION_ENEMY:	BI_intNRetValue[1] = 6;		break;
			}
			BI_intNRetValue[2] = 8;
			switch (sti(chRef.nation))
			{
				case ENGLAND:	BI_intNRetValue[3] = 3;	break;
				case FRANCE:	BI_intNRetValue[3] = 2;	break;
				case SPAIN:		BI_intNRetValue[3] = 0;	break;
				case HOLLAND:	BI_intNRetValue[3] = 4;	break;
				case PIRATE:	BI_intNRetValue[3] = 5;	break;
			}
		break;
	}
	return &BI_intNRetValue;
}

void SetParameterData()
{
	int i, iPosX, iPosY, iDeltaX, iDeltaY, iIconSize;
	int iCenterX = sti(showWindow.right) / 2;
	string sIconSize;
	float fHtRatio = GetScreenScale();

	BattleInterface.CommandTextures.list.t0.name = "battle_interface\list_icons.tga.tx";
	BattleInterface.CommandTextures.list.t0.xsize = 16;
	BattleInterface.CommandTextures.list.t0.ysize = 8;

	BattleInterface.CommandTextures.list.t1.name = "battle_interface\ship_icons1.tga";
	BattleInterface.CommandTextures.list.t1.xsize = 16;
	BattleInterface.CommandTextures.list.t1.ysize = 16;

	BattleInterface.CommandTextures.list.t2.name = "battle_interface\cancel.tga.tx";
	BattleInterface.CommandTextures.list.t2.xsize = 2;
	BattleInterface.CommandTextures.list.t2.ysize = 1;

	BattleInterface.CommandTextures.list.t3.name = "battle_interface\small_nations.tga.tx";
	BattleInterface.CommandTextures.list.t3.xsize = 16;
	BattleInterface.CommandTextures.list.t3.ysize = 1;

	BattleInterface.CommandTextures.list.t4.name = "battle_interface\LandCommands.tga.tx";
	BattleInterface.CommandTextures.list.t4.xsize = 16;
	BattleInterface.CommandTextures.list.t4.ysize = 4;

	BattleInterface.charge.charge1.picNum = 19;
	BattleInterface.charge.charge1.selPicNum = 3;
	BattleInterface.charge.charge1.note = XI_convertString("Balls");
	BattleInterface.charge.charge2.picNum = 18;
	BattleInterface.charge.charge2.selPicNum = 2;
	BattleInterface.charge.charge2.note = XI_convertString("Grapes");
	BattleInterface.charge.charge3.picNum = 21;
	BattleInterface.charge.charge3.selPicNum = 5;
	BattleInterface.charge.charge3.note = XI_convertString("Knippels");
	BattleInterface.charge.charge4.picNum = 20;
	BattleInterface.charge.charge4.selPicNum = 4;
	BattleInterface.charge.charge4.note = XI_convertString("Bombs");

	BattleInterface.CommandTextures.ChargeTexNum = 0;
	BattleInterface.CommandTextures.CommandTexNum = 0;

	BattleInterface.CommandShowParam.maxShowQuantity = 10;
	BattleInterface.CommandShowParam.iconDistance = makeint(4 * fHtRatio);
	BattleInterface.CommandShowParam.iconWidth = RecalculateHIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.iconHeight = RecalculateVIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.leftIconsOffset = sti(showWindow.left)+RecalculateHIcon(makeint(16 * fHtRatio));
	BattleInterface.CommandShowParam.downIconsOffset = sti(showWindow.bottom)-RecalculateVIcon(makeint(80 * fHtRatio));
	BattleInterface.CommandShowParam.buttonWidth = RecalculateHIcon(makeint(8 * fHtRatio));
	BattleInterface.CommandShowParam.buttonHeight = RecalculateVIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.buttonOffset = RecalculateHIcon(makeint(4 * fHtRatio));
	BattleInterface.CommandShowParam.buttonTexture = "battle_interface\lr_buttons.tga";
	BattleInterface.CommandShowParam.shipStateWidth = RecalculateHIcon(makeint(64 * fHtRatio));
	BattleInterface.CommandShowParam.shipStateHeight = RecalculateVIcon(makeint(16 * fHtRatio));
	BattleInterface.CommandShowParam.shipStateTexture = "battle_interface\indicators.tga";
	BattleInterface.CommandShowParam.shipStateOffset = RecalculateVIcon(0);
	BattleInterface.CommandShowParam.GeraldWidth = RecalculateHIcon(makeint(32 * fHtRatio));
	BattleInterface.CommandShowParam.GeraldHeight = RecalculateVIcon(makeint(32 * fHtRatio));
	BattleInterface.CommandShowParam.commandFont = "bold_numbers";
	BattleInterface.CommandShowParam.printXOffset = RecalculateHIcon(makeint(32 * fHtRatio));
	BattleInterface.CommandShowParam.printYOffset = RecalculateVIcon(makeint(-26 * fHtRatio));
	BattleInterface.CommandShowParam.commandNoteFont = "interface_normal";
	BattleInterface.CommandShowParam.noteXOffset = RecalculateHIcon(0);
	BattleInterface.CommandShowParam.noteYOffset = RecalculateVIcon(makeint(-30 * fHtRatio));
	BattleInterface.CommandShowParam.argbTFactorColor = argb(256,64,64,64);

	BattleInterface.UserIcons.ui1.enable = true;
	BattleInterface.UserIcons.ui1.selpic = 96;
	BattleInterface.UserIcons.ui1.pic = 112;
	BattleInterface.UserIcons.ui1.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui1.name = "dir_n";
	BattleInterface.UserIcons.ui1.note = LanguageConvertString(iCommandsFile, "sea_SailN");

	BattleInterface.UserIcons.ui2.enable = true;
	BattleInterface.UserIcons.ui2.selpic = 97;
	BattleInterface.UserIcons.ui2.pic = 113;
	BattleInterface.UserIcons.ui2.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui2.name = "dir_ne";
	BattleInterface.UserIcons.ui2.note = LanguageConvertString(iCommandsFile, "sea_SailNE");

	BattleInterface.UserIcons.ui3.enable = true;
	BattleInterface.UserIcons.ui3.selpic = 98;
	BattleInterface.UserIcons.ui3.pic = 114;
	BattleInterface.UserIcons.ui3.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui3.name = "dir_e";
	BattleInterface.UserIcons.ui3.note = LanguageConvertString(iCommandsFile, "sea_SailE");

	BattleInterface.UserIcons.ui4.enable = true;
	BattleInterface.UserIcons.ui4.selpic = 99;
	BattleInterface.UserIcons.ui4.pic = 115;
	BattleInterface.UserIcons.ui4.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui4.name = "dir_se";
	BattleInterface.UserIcons.ui4.note = LanguageConvertString(iCommandsFile, "sea_SailSE");

	BattleInterface.UserIcons.ui5.enable = true;
	BattleInterface.UserIcons.ui5.selpic = 100;
	BattleInterface.UserIcons.ui5.pic = 116;
	BattleInterface.UserIcons.ui5.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui5.name = "dir_s";
	BattleInterface.UserIcons.ui5.note = LanguageConvertString(iCommandsFile, "sea_SailS");

	BattleInterface.UserIcons.ui6.enable = true;
	BattleInterface.UserIcons.ui6.selpic = 101;
	BattleInterface.UserIcons.ui6.pic = 117;
	BattleInterface.UserIcons.ui6.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui6.name = "dir_sw";
	BattleInterface.UserIcons.ui6.note = LanguageConvertString(iCommandsFile, "sea_SailSW");

    BattleInterface.UserIcons.ui7.enable = true;
	BattleInterface.UserIcons.ui7.selpic = 102;
	BattleInterface.UserIcons.ui7.pic = 118;
	BattleInterface.UserIcons.ui7.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui7.name = "dir_w";
	BattleInterface.UserIcons.ui7.note = LanguageConvertString(iCommandsFile, "sea_SailW");

	BattleInterface.UserIcons.ui8.enable = true;
	BattleInterface.UserIcons.ui8.selpic = 103;
	BattleInterface.UserIcons.ui8.pic = 119;
	BattleInterface.UserIcons.ui8.tex = BI_ICONS_TEXTURE_COMMAND;
	BattleInterface.UserIcons.ui8.name = "dir_nw";
	BattleInterface.UserIcons.ui8.note = LanguageConvertString(iCommandsFile, "sea_SailNW");

	BattleInterface.MessageIcons.IconWidth = RecalculateHIcon(makeint(64 * fHtRatio));
	BattleInterface.MessageIcons.IconHeight = RecalculateVIcon(makeint(24 * fHtRatio));
	BattleInterface.MessageIcons.IconDist = RecalculateVIcon(2);
	BattleInterface.MessageIcons.IconBottom = sti(showWindow.bottom)-RecalculateVIcon(makeint((80+20) * fHtRatio));
	BattleInterface.MessageIcons.IconMaxQuantity = 4;
	BattleInterface.MessageIcons.BlendTime = 3.0;
	BattleInterface.MessageIcons.FallSpeed = 22.0;
	BattleInterface.MessageIcons.argbHighBlind = argb(255,128,128,128);
	BattleInterface.MessageIcons.argbLowBlind = argb(255,68,68,68);
	BattleInterface.MessageIcons.BlindUpTime = 0.5;
	BattleInterface.MessageIcons.BlindDownTime = 1.0;
	BattleInterface.MessageIcons.texture = "battle_interface\MessageIcons.tga.tx";
	BattleInterface.MessageIcons.TexHSize = 2;
	BattleInterface.MessageIcons.TexVSize = 2;

	BattleInterface.navigation.compasTexture			= "battle_interface\compass.tga.tx";
    BattleInterface.navigation.cannonsTexture			= "battle_interface\indicators_cannons_reload.tga.tx";
    BattleInterface.navigation.emptyTexture				= "battle_interface\indicators_dark_and_center_ship.tga.tx";
    BattleInterface.navigation.windTexture				= "battle_interface\wind_pointer.tga.tx";

	BattleInterface.navigation.windWidth				= makeint(37 * fHtRatio); //Стрелка направления ветра
	BattleInterface.navigation.windHeight				= makeint(148 * fHtRatio);

	i = RecalculateHIcon(makeint(204 * fHtRatio)); //размер компаса
	iIconSize = RecalculateXIcon(makeint(48 * fHtRatio)); //размер значков
	sIconSize = iIconSize +"," +iIconSize;

	BattleInterface.navigation.aspectRatio				= showWindow.aspectRatio;
	BattleInterface.navigation.navigatorWidth			= i;
	BattleInterface.navigation.navigatorHeight			= i;
	BattleInterface.navigation.rightPos					= sti(showWindow.right) + RecalculateHIcon(makeint(-36 * fHtRatio)); //компас отступ справа
	BattleInterface.navigation.topPos					= sti(showWindow.top) + RecalculateVIcon(makeint(19 * fHtRatio)); //компас отступ сверху

	i /= 2;
	iPosX = sti(BattleInterface.navigation.rightPos) - i; //Центр компаса справа
	iPosY = sti (BattleInterface.navigation.topPos) + i - RecalculateVIcon(makeint(10 * fHtRatio)); //Центр компаса сверху
//Show Cannons -->
	iDeltaY = RecalculateYIcon(makeint(-6 * fHtRatio));
	iDeltaX = iDeltaY; //отступы количества орудий от компаса
	fTextScale = 1.2 * fHtRatio; //Размер шрифта орудий
//	iTextColor = GetColorInt("yellow"); //цвет шрифта орудий
	iTextColor = argb(255,240,225,200); //цвет шрифта орудий

	BattleInterface.textinfo.FrontCannon.font = "interface_normal";
	BattleInterface.textinfo.FrontCannon.scale = fTextScale;
	BattleInterface.textinfo.FrontCannon.color = iTextColor;
	BattleInterface.textinfo.FrontCannon.pos.x = iPosX;
	BattleInterface.textinfo.FrontCannon.pos.y = iPosY - i + iDeltaY;
	BattleInterface.textinfo.FrontCannon.text = " ";
	BattleInterface.textinfo.FrontCannon.refreshable = true;

	BattleInterface.textinfo.BackCannon.font = "interface_normal";
	BattleInterface.textinfo.BackCannon.scale = fTextScale;
	BattleInterface.textinfo.BackCannon.color = iTextColor;
	BattleInterface.textinfo.BackCannon.pos.x = iPosX;
	BattleInterface.textinfo.BackCannon.pos.y = iPosY + i - iDeltaY;
	BattleInterface.textinfo.BackCannon.text = " ";
	BattleInterface.textinfo.BackCannon.refreshable = true;

	BattleInterface.textinfo.RightCannon.font = "interface_normal";
	BattleInterface.textinfo.RightCannon.scale = fTextScale;
	BattleInterface.textinfo.RightCannon.color = iTextColor;
	BattleInterface.textinfo.RightCannon.pos.x = iPosX + i - iDeltaX;
	BattleInterface.textinfo.RightCannon.pos.y = iPosY;
	BattleInterface.textinfo.RightCannon.text = " ";
	BattleInterface.textinfo.RightCannon.refreshable = true;

	BattleInterface.textinfo.LeftCannon.font = "interface_normal";
	BattleInterface.textinfo.LeftCannon.scale = fTextScale;
	BattleInterface.textinfo.LeftCannon.color = iTextColor;
	BattleInterface.textinfo.LeftCannon.pos.x = iPosX - i + iDeltaX;
	BattleInterface.textinfo.LeftCannon.pos.y = iPosY;
	BattleInterface.textinfo.LeftCannon.text = " ";
	BattleInterface.textinfo.LeftCannon.refreshable = true;

	BI_ShowCannonsQty();
//Show Cannons <--

	BattleInterface.textinfo.Date.font = "interface_normal_bold_smallscale";
	BattleInterface.textinfo.Date.scale = 0.29 * fHtRatio;
	BattleInterface.textinfo.Date.pos.x = iPosX;
	BattleInterface.textinfo.Date.pos.y = sti(BattleInterface.textinfo.BackCannon.pos.y) + RecalculateYIcon(makeint(32 * fHtRatio));
	BattleInterface.textinfo.Date.text = GetQuestBookData();
	BattleInterface.textinfo.Date.refreshable = true;

	BattleInterface.textinfo.Location.font = "interface_normal_bold_smallscale";
	BattleInterface.textinfo.Location.scale = 0.29 * fHtRatio;
	BattleInterface.textinfo.Location.pos.x = iPosX;
	BattleInterface.textinfo.Location.pos.y = sti(BattleInterface.textinfo.Date.pos.y) + RecalculateYIcon(makeint(22 * fHtRatio));
	BattleInterface.textinfo.Location.refreshable = true;
	BattleInterface.textinfo.Location.text = "";

	iPosY = sti(BattleInterface.textinfo.Location.pos.y) + RecalculateYIcon(makeint(55* fHtRatio));
	iDeltaX = RecalculateXIcon(makeint(32* fHtRatio)); // для значков ветра отступ от центра компаса

	BattleInterface.navigation.sailstateTexture			= "battle_interface\list_icon2.tga";
	BattleInterface.navigation.sailstateTextureGreed	= "4,4";
	BattleInterface.navigation.sailstatePos				= its(iPosX - iDeltaX) +"," +iPosY;
	BattleInterface.navigation.sailstatePictureSize		= sIconSize;

	BattleInterface.navigation.windStateTexture			= "battle_interface\list_icon2.tga";
	BattleInterface.navigation.windTextureGreed			= "4,4";
	BattleInterface.navigation.windPos					= its(iPosX + iDeltaX) +"," +iPosY;
	BattleInterface.navigation.windPictureSize			= sIconSize;

	BattleInterface.navigation.speedShowFont			= "interface_normal";
	BattleInterface.navigation.speedOutYOffset			= iPosY + iIconSize / 2 + RecalculateYIcon(makeint(6 * fHtRatio));
	BattleInterface.navigation.shipSpeedXOffset			= sti(BattleInterface.navigation.sailstatePos);
	BattleInterface.navigation.windSpeedXOffset			= sti(BattleInterface.navigation.windPos);
	BattleInterface.navigation.fontScale				= 1.25 * fHtRatio;

	BattleInterface.navigation.leftChargeBegAngle		= 204;
	BattleInterface.navigation.leftChargeEndAngle		= 336;
	BattleInterface.navigation.rightChargeBegAngle		= 156;
	BattleInterface.navigation.rightChargeEndAngle		= 24;
	BattleInterface.navigation.forwardChargeBegAngle	= 343;
	BattleInterface.navigation.forwardChargeEndAngle	= 378;
	BattleInterface.navigation.backwardChargeBegAngle	= 198;
	BattleInterface.navigation.backwardChargeEndAngle	= 162;
	BattleInterface.navigation.mapRadius				= makeint(63 * fHtRatio);
	BattleInterface.navigation.horizontRadius			= 400;
	BattleInterface.navigation.minScale					= 0.5;
	BattleInterface.navigation.maxScale					= 4;
	BattleInterface.navigation.curScale					= 2;
	BattleInterface.navigation.scaleStep				= 0.1;
	BattleInterface.navigation.argbReadyCannonColor		= argb(255,143,129,101);
	BattleInterface.navigation.argbChargeCannonColor	= argb(255,153,143,65);
	BattleInterface.navigation.argbDamageCannonColor	= argb(255,111,26,26);
	BattleInterface.navigation.argbDisableCannonColor	= argb(255,47,47,47);
	BattleInterface.navigation.argbSeaColor				= argb(255,10,30,80);
	BattleInterface.navigation.argbFireZoneColor		= argb(60,250,250,250);
	BattleInterface.navigation.argbEnemyShipColor		= argb(255,255,0,0);
	BattleInterface.navigation.argbFrendShipColor		= argb(255,0,255,0);
	BattleInterface.navigation.argbNeutralShipColor		= argb(255,128,128,128);
	BattleInterface.navigation.argbDeadShipColor		= argb(255,0,0,255);
	BattleInterface.navigation.argbBackMaxColor			= argb(255,0,0,128);
	BattleInterface.navigation.argbBackMinColor			= argb(0,0,0,128);
	BattleInterface.navigation.shipShowRadius			= 8.0;

// BottomBar -->
	iPosY = sti(showWindow.bottom) - RecalculateYIcon(makeint(122 * fHtRatio)); //Высота надписи с аммуницией от низа экрана
	iPosX = RecalculateXIcon(makeint(77 * fHtRatio)); //расстояние между значками аммуниции
	iDeltaX = RecalculateXIcon(makeint(117 * fHtRatio)); //расстояние значков от центра экрана
	fTextScale = 1.2 * fHtRatio; //Размер шрифта боеприпасов
	iTextColor = GetColorInt("white"); //цвет шрифта боеприпасов

	// BottomBar Back
	BattleInterface.navigation.bottomBarBackTexture			= "battle_interface\BI_BottomBarBack.tga";
	BattleInterface.navigation.bottomBarBackLeftPos				= (iCenterX - makeint(182 * fHtRatio)) +"," + (iPosY + RecalculateYIcon(makeint(52 * fHtRatio)));
	BattleInterface.navigation.bottomBarBackLeftPictureSize		= RecalculateXIcon(makeint(384 * fHtRatio)) +"," +RecalculateYIcon(makeint(192 * fHtRatio));
	BattleInterface.navigation.bottomBarBackRightPos			= (iCenterX + makeint(182 * fHtRatio)) +"," + (iPosY + RecalculateYIcon(makeint(52 * fHtRatio)));
	BattleInterface.navigation.bottomBarBackRightPictureSize	= RecalculateXIcon(makeint(384 * fHtRatio)) +"," +RecalculateYIcon(makeint(192 * fHtRatio));

	BattleInterface.bottomBar.AmmoPicSize	= RecalculateXIcon(makeint(48 * fHtRatio)) +"," +RecalculateXIcon(makeint(48 * fHtRatio));
	BattleInterface.bottomBar.PowderPicSize	= RecalculateXIcon(makeint(42 * fHtRatio)) +"," +RecalculateXIcon(makeint(42 * fHtRatio));
	BattleInterface.bottomBar.WeaponPicSize	= RecalculateXIcon(makeint(44 * fHtRatio)) +"," +RecalculateXIcon(makeint(50 * fHtRatio));
	BattleInterface.bottomBar.PlanksPicSize	= RecalculateXIcon(makeint(36 * fHtRatio)) +"," +RecalculateXIcon(makeint(36 * fHtRatio));
	BattleInterface.bottomBar.ClothPicSize	= RecalculateXIcon(makeint(38 * fHtRatio)) +"," +RecalculateXIcon(makeint(38 * fHtRatio));
	BattleInterface.bottomBar.AmmoTexture	= "battle_interface\list_icon2_ammo.tga";
	BattleInterface.bottomBar.AmmoTexGreed	= "8,4";

	BattleInterface.textinfo.BombsQty.font = "interface_normal";
	BattleInterface.textinfo.BombsQty.scale = fTextScale;
	BattleInterface.textinfo.BombsQty.color = iTextColor;
	BattleInterface.textinfo.BombsQty.pos.x = iCenterX - iDeltaX;
	BattleInterface.textinfo.BombsQty.pos.y = iPosY;
	BattleInterface.textinfo.BombsQty.text = pchar.ship.cargo.goods.Bombs;
	BattleInterface.textinfo.BombsQty.refreshable = true;

	BattleInterface.textinfo.KnippelsQty.font = "interface_normal";
	BattleInterface.textinfo.KnippelsQty.scale = fTextScale;
	BattleInterface.textinfo.KnippelsQty.color = iTextColor;
	BattleInterface.textinfo.KnippelsQty.pos.x = sti(BattleInterface.textinfo.BombsQty.pos.x) - iPosX;
	BattleInterface.textinfo.KnippelsQty.pos.y = iPosY;
	BattleInterface.textinfo.KnippelsQty.text = pchar.ship.cargo.goods.Knippels;
	BattleInterface.textinfo.KnippelsQty.refreshable = true;

	BattleInterface.textinfo.GrapesQty.font = "interface_normal";
	BattleInterface.textinfo.GrapesQty.scale = fTextScale;
	BattleInterface.textinfo.GrapesQty.color = iTextColor;
	BattleInterface.textinfo.GrapesQty.pos.x = sti(BattleInterface.textinfo.KnippelsQty.pos.x) - iPosX;
	BattleInterface.textinfo.GrapesQty.pos.y = iPosY;
	BattleInterface.textinfo.GrapesQty.text = pchar.ship.cargo.goods.Grapes;
	BattleInterface.textinfo.GrapesQty.refreshable = true;

	BattleInterface.textinfo.BallsQty.font = "interface_normal";
	BattleInterface.textinfo.BallsQty.scale = fTextScale;
	BattleInterface.textinfo.BallsQty.color = iTextColor;
	BattleInterface.textinfo.BallsQty.pos.x = sti(BattleInterface.textinfo.GrapesQty.pos.x) - iPosX;
	BattleInterface.textinfo.BallsQty.pos.y = iPosY;
	BattleInterface.textinfo.BallsQty.text = pchar.ship.cargo.goods.Balls;
	BattleInterface.textinfo.BallsQty.refreshable = true;

	BattleInterface.textinfo.PowderQty.font = "interface_normal";
	BattleInterface.textinfo.PowderQty.scale = fTextScale;
	BattleInterface.textinfo.PowderQty.color = iTextColor;
	BattleInterface.textinfo.PowderQty.pos.x = iCenterX + iDeltaX;
	BattleInterface.textinfo.PowderQty.pos.y = iPosY;
	BattleInterface.textinfo.PowderQty.text = pchar.ship.cargo.goods.powder;
	BattleInterface.textinfo.PowderQty.refreshable = true;

	BattleInterface.textinfo.WeaponQty.font = "interface_normal";
	BattleInterface.textinfo.WeaponQty.scale = fTextScale;
	BattleInterface.textinfo.WeaponQty.color = iTextColor;
	BattleInterface.textinfo.WeaponQty.pos.x = sti(BattleInterface.textinfo.PowderQty.pos.x) + iPosX;
	BattleInterface.textinfo.WeaponQty.pos.y = iPosY;
	BattleInterface.textinfo.WeaponQty.text = pchar.ship.cargo.goods.Weapon;
	BattleInterface.textinfo.WeaponQty.refreshable = true;

	BattleInterface.textinfo.PlanksQty.font = "interface_normal";
	BattleInterface.textinfo.PlanksQty.scale = fTextScale;
	BattleInterface.textinfo.PlanksQty.color = iTextColor;
	BattleInterface.textinfo.PlanksQty.pos.x = sti(BattleInterface.textinfo.WeaponQty.pos.x) + iPosX;
	BattleInterface.textinfo.PlanksQty.pos.y = iPosY;
	BattleInterface.textinfo.PlanksQty.text = pchar.ship.cargo.goods.Planks;
	BattleInterface.textinfo.PlanksQty.refreshable = true;

	BattleInterface.textinfo.ClothQty.font = "interface_normal";
	BattleInterface.textinfo.ClothQty.scale = fTextScale;
	BattleInterface.textinfo.ClothQty.color = iTextColor;
	BattleInterface.textinfo.ClothQty.pos.x = sti(BattleInterface.textinfo.PlanksQty.pos.x) + iPosX;
	BattleInterface.textinfo.ClothQty.pos.y = iPosY;
	BattleInterface.textinfo.ClothQty.text = pchar.ship.cargo.goods.Sailcloth;
	BattleInterface.textinfo.ClothQty.refreshable = true;

	iPosY = iPosY + RecalculateVIcon(makeint(50 * fHtRatio)); //расстояние между надписью и значком

	BattleInterface.bottomBar.ballsPos		= BattleInterface.textinfo.BallsQty.pos.x +"," +(iPosY + RecalculateYIcon(makeint(6 * fHtRatio)));
	BattleInterface.bottomBar.grapesPos		= BattleInterface.textinfo.GrapesQty.pos.x +"," +(iPosY + RecalculateYIcon(makeint(6 * fHtRatio)));
	BattleInterface.bottomBar.knippelsPos	= BattleInterface.textinfo.KnippelsQty.pos.x +"," +(iPosY + RecalculateYIcon(makeint(6 * fHtRatio)));
	BattleInterface.bottomBar.bombsPos		= BattleInterface.textinfo.BombsQty.pos.x +"," +(iPosY + RecalculateYIcon(makeint(6 * fHtRatio)));
	BattleInterface.bottomBar.powderPos		= (sti(BattleInterface.textinfo.PowderQty.pos.x) + RecalculateXIcon(makeint(2 * fHtRatio))) +"," +iPosY;
	BattleInterface.bottomBar.weaponPos		= (sti(BattleInterface.textinfo.WeaponQty.pos.x) + RecalculateXIcon(makeint(1 * fHtRatio))) +"," +(iPosY + RecalculateYIcon(makeint(4 * fHtRatio)));
	BattleInterface.bottomBar.planksPos		= (sti(BattleInterface.textinfo.planksQty.pos.x) + RecalculateXIcon(makeint(-2 * fHtRatio))) +"," +(iPosY + RecalculateYIcon(makeint(8 * fHtRatio)));
	BattleInterface.bottomBar.ClothPos		= (sti(BattleInterface.textinfo.ClothQty.pos.x) + RecalculateXIcon(makeint(-3 * fHtRatio))) +"," +(iPosY + RecalculateYIcon(makeint(8 * fHtRatio)));

//Bottom bar <--
//Control Tips -->
	iShowTips = sti(InterfaceStates.ShowControlTips);
	BI_ShowFastKeyTip("nothing");
	if (iShowTips > CONTROL_TIPS_NONE)
	{
		InitSeaTips(iIconSize, iPosY);
	}
//Control Tips <--

	if( CheckAttribute(&InterfaceStates,"ShowBattleMode") ) {
		BattleInterface.battleborder.used = InterfaceStates.ShowBattleMode;
	} else {
		BattleInterface.battleborder.used = false;
	}
	BattleInterface.battleborder.color1 = argb(255,255,255,255);
	BattleInterface.battleborder.color2 = argb(155,255,255,255);
	BattleInterface.battleborder.extpos = "0,0," + ShowWindow.right + "," + ShowWindow.bottom;
	BattleInterface.battleborder.intpos1 =
		RecalculateHIcon(20) + "," +
		RecalculateVIcon(20) + "," +
		(sti(ShowWindow.right)-RecalculateHIcon(20)) + "," +
		(sti(ShowWindow.bottom)-RecalculateVIcon(20));
	BattleInterface.battleborder.intpos2 =
		RecalculateHIcon(10) + "," +
		RecalculateVIcon(10) + "," +
		(sti(ShowWindow.right)-RecalculateHIcon(10)) + "," +
		(sti(ShowWindow.bottom)-RecalculateVIcon(10));
	BattleInterface.battleborder.speed = 1.5;
	BattleInterface.battleborder.texture = "battle_interface\battleborder.tga.tx";

	DeleteAttribute(&BattleInterface, "ShipIcon"); //HardCoffee test
	iPosX = RecalculateXIcon(makeint(70 * fHtRatio));	//размещение рамок кораблей

	int playerShipLabelOffset = 0;
    BattleInterface.ShipIcon.iconoffset1 = iPosX +","+RecalculateYIcon(makeint(70 * fHtRatio));
	BattleInterface.ShipIcon.iconoffset2 = iPosX +","+RecalculateYIcon(makeint((206 + playerShipLabelOffset) * fHtRatio)); // 70 + 136 * 1
	BattleInterface.ShipIcon.iconoffset3 = iPosX +","+RecalculateYIcon(makeint((338 + playerShipLabelOffset) * fHtRatio)); // 70 + 136 * 2
	BattleInterface.ShipIcon.iconoffset4 = iPosX +","+RecalculateYIcon(makeint((458 + playerShipLabelOffset) * fHtRatio));
	BattleInterface.ShipIcon.iconoffset5 = iPosX +","+RecalculateYIcon(makeint((586 + playerShipLabelOffset) * fHtRatio));
	BattleInterface.ShipIcon.iconoffset6 = iPosX +","+RecalculateYIcon(makeint((714 + playerShipLabelOffset) * fHtRatio));	//ZhilyaevDm 6й корабль

	BattleInterface.ShipIcon.backtexturename		= "battle_interface\ShipBackIcon.tga.tx";
	BattleInterface.ShipIcon.backcolor				= argb(255,128,128,128);
	BattleInterface.ShipIcon.backuv					= "0.0,0.005,1.0,1.0";
	BattleInterface.ShipIcon.backoffset				= RecalculateXIcon(makeint(-4 * fHtRatio))+","+RecalculateYIcon(makeint(8 * fHtRatio));
    BattleInterface.ShipIcon.backiconsize			= RecalculateXIcon(makeint(106 * fHtRatio))+","+RecalculateYIcon(makeint(106 * fHtRatio));

	BattleInterface.ShipIcon.backtexturenameMC		= "battle_interface\ShipBackIcon0.tga.tx"; //Рамка корабля гг
	BattleInterface.ShipIcon.backcolorMC			= BattleInterface.ShipIcon.backcolor;
	BattleInterface.ShipIcon.backuvMC				= BattleInterface.ShipIcon.backuv;
	BattleInterface.ShipIcon.backoffsetMC			= RecalculateXIcon(makeint(-4 * fHtRatio))+","+RecalculateYIcon(makeint(8 * fHtRatio));
    BattleInterface.ShipIcon.backiconsizeMC			= RecalculateXIcon(makeint(118 * fHtRatio))+","+RecalculateYIcon(makeint(118 * fHtRatio));

	iPosX = RecalculateXIcon(makeint(-3* fHtRatio));
	BattleInterface.ShipIcon.sailorfontid			= "interface_normal_smallscale";
	BattleInterface.ShipIcon.sailorfontcolor		= argb(255,255,255,255);
    BattleInterface.ShipIcon.sailorfontscale		= 0.26 * fHtRatio;
    BattleInterface.ShipIcon.sailorfontoffset       = iPosX +","+RecalculateYIcon(makeint(42 * fHtRatio));

 	BattleInterface.ShipIcon.shipnamefontid			= "interface_normal_smallscale";
	BattleInterface.ShipIcon.shipnamefontcolor		= argb(255,255,255,255);
	BattleInterface.ShipIcon.shipnamefontscale		= 0.26 * fHtRatio;
    BattleInterface.ShipIcon.shipnamefontoffset     = iPosX +","+RecalculateYIcon(makeint(26* fHtRatio));

	//матросы и название корабля гг
    BattleInterface.ShipIcon.sailorfontscaleMC		= 0.3 * fHtRatio;
    BattleInterface.ShipIcon.sailorfontoffsetMC     = iPosX +","+RecalculateYIcon(makeint(40 * fHtRatio));
	BattleInterface.ShipIcon.shipnamefontcolorMC	= argb(255,255,255,255);
	BattleInterface.ShipIcon.shipnamefontscaleMC	= 0.0 * fHtRatio;
//	BattleInterface.ShipIcon.shipnamefontscaleMC	= 0.3 * fHtRatio;
    BattleInterface.ShipIcon.shipnamefontoffsetMC   = RecalculateXIcon(makeint(-4.0 * fHtRatio)) +","+RecalculateVIcon(makeint(66.0* fHtRatio));

	//pchar HP-bar -->
	iPosX = makeint(118.0 * fHtRatio);
	BattleInterface.ShipIcon.shipstatetexturenameMC	= "battle_interface\ShipStateHorizontal.tga.tx";
	BattleInterface.ShipIcon.shipstatecolorMC		= argb(255,128,128,128);
	BattleInterface.ShipIcon.shipHPuvMC				= "0.0468,0.2929,0.9609,0.4375";
	BattleInterface.ShipIcon.shipSPuvMC				= "0.0468,0.4726,0.9609,0.6132";
    BattleInterface.ShipIcon.shipHPoffsetMC			= its(iPosX + makeint(39.0 * fHtRatio)) + "," + makeint(-7.5 * fHtRatio);
    BattleInterface.ShipIcon.shipSPoffsetMC			= its(iPosX + makeint(39.0 * fHtRatio)) + "," + makeint(12.5 * fHtRatio);
    BattleInterface.ShipIcon.shipHPiconsizeMC		= makeint(206 * fHtRatio) + "," + makeint(16 * fHtRatio);
    BattleInterface.ShipIcon.shipSPiconsizeMC		= makeint(206 * fHtRatio) + "," + makeint(15.5 * fHtRatio);

	BattleInterface.ShipIcon.shipstatebacktexturename	= "battle_interface\ShipStateBackIcon.tga.tx";
	BattleInterface.ShipIcon.shipstatebackcolor		= argb(255,128,128,128);
	BattleInterface.ShipIcon.shipstatebackuv		= "0.0,0.0,0.995,1.0";
	BattleInterface.ShipIcon.shipstatebackoffset	= its(iPosX + makeint(38 * fHtRatio)) + "," + makeint(8.0 * fHtRatio);
    BattleInterface.ShipIcon.shipstatebackiconsize	= makeint(224.0 * fHtRatio) + "," + makeint(108.0 * fHtRatio);

	BattleInterface.ShipIcon.shipHpfontid			= "interface_normal_smallscale";
	BattleInterface.ShipIcon.shipHpfontcolor		= argb(255,255,255,255);
    BattleInterface.ShipIcon.shipHpfontscale		= 0.26 * fHtRatio;
    BattleInterface.ShipIcon.shipHpfontoffset       = its(iPosX + makeint(39.0 * fHtRatio)) +","+RecalculateYIcon(makeint(-16 * fHtRatio));

    BattleInterface.ShipIcon.shipSpfontid			= "interface_normal_smallscale";
	BattleInterface.ShipIcon.shipSpfontcolor		= argb(255,255,255,255);
    BattleInterface.ShipIcon.shipSpfontscale		= 0.26 * fHtRatio;
    BattleInterface.ShipIcon.shipSpfontoffset       = its(iPosX + makeint(39.0 * fHtRatio)) +","+RecalculateYIcon(makeint(3 * fHtRatio));
	//pchar HP-bar <--

	BattleInterface.ShipIcon.shipstatetexturename	= "battle_interface\ShipState.tga.tx";
	BattleInterface.ShipIcon.shipstatecolor			= argb(255,128,128,128);
	BattleInterface.ShipIcon.shipHPuv				= "0.0,0.0625,0.5,0.6875";
	BattleInterface.ShipIcon.shipSPuv				= "0.5,0.0625,1.0,0.6875";

    BattleInterface.ShipIcon.shipHPoffset			= RecalculateHIcon(makeint(-30 * fHtRatio))+","+RecalculateVIcon(makeint(-6 * fHtRatio));
    BattleInterface.ShipIcon.shipSPoffset			= RecalculateHIcon(makeint(22 * fHtRatio))+","+RecalculateVIcon(makeint(-6 * fHtRatio));
    BattleInterface.ShipIcon.shipHPiconsize			= RecalculateHIcon(makeint(54 * fHtRatio))+","+RecalculateVIcon(makeint(67 * fHtRatio));
    BattleInterface.ShipIcon.shipSPiconsize			= BattleInterface.ShipIcon.shiphpiconsize;

	BattleInterface.ShipIcon.shipclasstexturename	= "battle_interface\ShipClass.tga.tx";
	BattleInterface.ShipIcon.shipclasscolor			= argb(255,128,128,128);
	BattleInterface.ShipIcon.shipclassuv			= "0.0,0.0,1.0,1.0";
    BattleInterface.ShipIcon.shipclassoffset		= RecalculateHIcon(makeint(-3 * fHtRatio))+","+RecalculateVIcon(makeint(-37 * fHtRatio));
    BattleInterface.ShipIcon.shipclassiconsize		= RecalculateHIcon(makeint(115 * fHtRatio))+","+RecalculateVIcon(makeint(29 * fHtRatio));
    BattleInterface.ShipIcon.mcshipclassoffset		= RecalculateHIcon(makeint(-3 * fHtRatio))+","+RecalculateVIcon(makeint(-40 * fHtRatio));
	BattleInterface.ShipIcon.mcshipclassiconsize	= RecalculateHIcon(makeint(128 * fHtRatio))+","+RecalculateVIcon(makeint(32 * fHtRatio));


	BattleInterface.ShipIcon.gunchargeprogress		= "0.0625, 0.211, 0.359, 0.5, 0.633, 0.781, 0.983";

	BattleInterface.ShipIcon.shiptexturename		= "battle_interface\ship_icons2.tga.tx";
	BattleInterface.ShipIcon.shipcolor				= argb(255,128,128,128);

	BattleInterface.ShipIcon.shipoffset				= RecalculateHIcon(makeint(-3 * fHtRatio))+","+RecalculateVIcon(makeint(-2 * fHtRatio));
	BattleInterface.ShipIcon.shipiconsize			= RecalculateHIcon(makeint(72 * fHtRatio))+","+RecalculateVIcon(makeint(72 * fHtRatio));
	BattleInterface.ShipIcon.shipiconsizeMC			= RecalculateHIcon(makeint(80 * fHtRatio))+","+RecalculateVIcon(makeint(80 * fHtRatio));
	BattleInterface.ShipIcon.xsize 					= 16;
	BattleInterface.ShipIcon.ysize 					= 8;
    BattleInterface.ShipIcon.commandlistverticaloffset = makeint(-20 * fHtRatio);
    BattleInterface.ShipIcon.commandlistverticaloffsetMC = makeint(49 * fHtRatio);

	DeleteAttribute(&BattleInterface, "CommandList");

	BattleInterface.CommandList.CommandMaxIconQuantity = 12;
	BattleInterface.CommandList.CommandIconSpace = 1;
	BattleInterface.CommandList.CommandIconLeft = makeint(128 * fHtRatio);
	BattleInterface.CommandList.CommandIconWidth = RecalculateXIcon(makeint(48 * fHtRatio));
	BattleInterface.CommandList.CommandIconHeight = RecalculateYIcon(makeint(48 * fHtRatio));
	BattleInterface.CommandList.CommandIconSelOffset = makeint(3.0 * fHtRatio); //HardCoffee scale for selected icon

	BattleInterface.CommandList.CommandNoteFont = "interface_normal_smallscale";
	BattleInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
	BattleInterface.CommandList.CommandNoteScale = 0.26 * fHtRatio;
	BattleInterface.CommandList.CommandNoteOffset = RecalculateHIcon(0) + "," + RecalculateVIcon(makeint(-42 * fHtRatio));

/*	//HardCoffee эти стрелки теперь в подсказках
	BattleInterface.CommandList.UDArrow_Texture = "battle_interface\arrowly.tga.tx";
	BattleInterface.CommandList.UDArrow_UV_Up = "0.0,1.0,1.0,0.0";
	BattleInterface.CommandList.UDArrow_UV_Down = "0.0,0.0,1.0,1.0";
	BattleInterface.CommandList.UDArrow_Size = RecalculateHIcon(makeint(-32 * fHtRatio)) + "," + RecalculateVIcon(makeint(32 * fHtRatio));
	BattleInterface.CommandList.UDArrow_Offset_Up = RecalculateHIcon(makeint(-41 * fHtRatio)) + "," + RecalculateVIcon(makeint(-30 * fHtRatio));
	BattleInterface.CommandList.UDArrow_Offset_Down = RecalculateHIcon(makeint(-41 * fHtRatio)) + "," + RecalculateVIcon(makeint(46 * fHtRatio));
*/

	BattleInterface.ShipInfoImages.RelationTexture = "battle_interface\ship_arrows1.tga.tx";
	BattleInterface.ShipInfoImages.RelationOffset.x = 0.0;
	BattleInterface.ShipInfoImages.RelationOffset.y = 0.3;
	BattleInterface.ShipInfoImages.RelationOffset.z = 0.0;
	BattleInterface.ShipInfoImages.RelationSize = "0.75,0.5";
	BattleInterface.ShipInfoImages.RelationUV1 = "0.0,0.0,0.25,1.0"; // friend
	BattleInterface.ShipInfoImages.RelationUV2 = "0.25,0.0,0.5,1.0"; // enemy
	BattleInterface.ShipInfoImages.RelationUV3 = "0.5,0.0,0.75,1.0"; // neutral

	BattleInterface.ShipInfoImages.ProgressTexture = "battle_interface\indicators.tga.tx";
	BattleInterface.ShipInfoImages.ProgressSize = "2.0,0.1";
	//
	BattleInterface.ShipInfoImages.ProgressBackOffset.x = 0.0;
	BattleInterface.ShipInfoImages.ProgressBackOffset.y = 0.65;
	BattleInterface.ShipInfoImages.ProgressBackOffset.z = 0.0;
	BattleInterface.ShipInfoImages.ProgressBackSize = "2.0,0.3";
	BattleInterface.ShipInfoImages.ProgressBackUV = "0.0,0.5,1.0,1.0";
	//
	BattleInterface.ShipInfoImages.HullOffset.x = 0.0;
	BattleInterface.ShipInfoImages.HullOffset.y = 0.75;
	BattleInterface.ShipInfoImages.HullOffset.z = 0.0;
	BattleInterface.ShipInfoImages.HullUV = "0.0,0.333,1.0,0.5";
	//
	BattleInterface.ShipInfoImages.SailOffset.x = 0.0;
	BattleInterface.ShipInfoImages.SailOffset.y = 0.65;
	BattleInterface.ShipInfoImages.SailOffset.z = 0.0;
	BattleInterface.ShipInfoImages.SailUV = "0.0,0.167,1.0,0.333";
	//
	BattleInterface.ShipInfoImages.CrewOffset.x = 0.0;
	BattleInterface.ShipInfoImages.CrewOffset.y = 0.55;
	BattleInterface.ShipInfoImages.CrewOffset.z = 0.0;
	BattleInterface.ShipInfoImages.CrewUV = "0.0,0.0,1.0,0.166";

	BattleInterface.ShifInfoVisible = InterfaceStates.enabledshipmarks;
}

ref ProcessSailDamage()
{
	// от кого удар
	int shootIdx = GetEventData();
	// перс
	int chrIdx = GetEventData();

	string sMastName = GetEventData();
	// координаты паруса
	string reyName = GetEventData();
	int groupNum = GetEventData();
	// данные о дырках
	int holeCount = GetEventData();
	int holeData = GetEventData();
	int maxHoleCount = GetEventData();
	// мощность паруса
	float sailPower = GetEventData();

	ref chref = GetCharacter(chrIdx);
	string groupName = ""+groupNum;
	aref arSail;
	makearef(arSail,chref.ship.sails.(reyName).(groupName));
	
	if (LAi_IsImmortal(chref)) 
	{ 
		arSail.hd = DeleteOneSailHole(sti(chref.index), groupName, reyName, holeData, 1); //мгновенная заплатка
		BI_g_fRetVal = 0.0;
		return &BI_g_fRetVal;
	}

	float sailDmg = 0.0;
	float sailDmgMax = GetCharacterShipSP(chref) * sailPower;
	if (!CheckAttribute(arSail,"dmg")) sailDmg = 0.0;

	if (sMastName == "*")
	{
		sailDmg = sailDmg + GetRigDamage(shootIdx, sti(AIBalls.CurrentBallType), chref);
		if (sailDmg > sailDmgMax) sailDmg = sailDmgMax;
		int needHole = GetNeedHoleFromDmg(sailDmg, sailDmgMax, maxHoleCount);
		if (holeCount != needHole)
		{
			if (holeCount < needHole)
			{
				holeData = RandomHole2Sail(chrIdx,reyName,groupNum, maxHoleCount, holeData, needHole - holeCount);
				holeCount = needHole;
			}
			else
			{
				sailDmg = GetNeedDmgFromHole(holeCount, sailDmgMax, maxHoleCount);
			}
		}
	}
	else
	{
		if(sMastName!="#")	{ arSail.mastFall = sMastName; }
		sailDmg = sailDmgMax;
	}
	
	/*if (sailDmg < 0.5)
	{
		Log_SetStringtoLog("MUST DIE!!! " + sailDmg);
	}*/

	arSail.hc = holeCount;
	arSail.hd = holeData;
	arSail.mhc = maxHoleCount;
	arSail.sp = sailPower;
	arSail.dmg = sailDmg;

	chref.ship.SP = CalculateShipSP(chref);
	BI_g_fRetVal = sailDmg;
	return &BI_g_fRetVal;
}

ref procGetSailTextureData()
{
	int st,i,sq;
	ref shref;
	aref arEmbl,arSail;
	string attrName;

	int chrIdx = GetEventData();

	DeleteAttribute(&BI_objRetValue,"");
    if (chrIdx>=0)
	{
		st = GetCharacterShipType(GetCharacter(chrIdx));
		if (st != SHIP_NOTUSED)
		{
			string sUpgrade = "common";
		
			shref = GetRealShip(st);
		
			int iUpgrade = sti(shref.ship.upgrades.sails);  
			switch(iUpgrade)
			{
				case 1:	sUpgrade = "common";	break;
				case 2:	sUpgrade = "pat";		break;
				case 3:	sUpgrade = "silk";		break;
			}
			
		
			string nationFileName = "ships\parus_" + sUpgrade + ".tga";
			string tmpStr;
		
			BI_objRetValue.normalTex = nationFileName;
			// AlexBlade > fix оповещения об отсутствующем файле тексутры в system.log
			// BI_objRetValue.geraldTex = "";
			BI_objRetValue.sailscolor = argb(255,255,255,255);  // белый парус
		
			//BI_objRetValue.geraldTexPointer = 0; // (IDirect3DTexture8*)
			
			//if (CheckAttribute(&characters[chrIdx], "ShipSails.SailsColor"))
			if (CheckAttribute(shref, "ShipSails.SailsColor")) // 1.2.3 цвет теперь атрибут корабля, а не НПС
			{
				BI_objRetValue.sailscolor = sti(shref.ShipSails.SailsColor);
			}
			//if( CheckAttribute(&characters[chrIdx],"ShipSails.gerald_name") ) // не наследуется при обмене кораблей, потому не в  ship.
			if( CheckAttribute(shref,"ShipSails.gerald_name") ) // 1.2.3 герб теперь атрибут корабля, а не НПС
			{
				BI_objRetValue.geraldTex = "Ships\Gerald\" + shref.ShipSails.gerald_name;
			}
			/*
			switch(sti(Characters[chrIdx].nation))  // Не работает это
			{
				case ENGLAND:	
					nationFileName = "ships\parus_" + sUpgrade + "_england.tga";		
				break;
				case FRANCE:	
					nationFileName = "ships\parus_" + sUpgrade + "_france.tga";		
				break;
				case SPAIN:		
					nationFileName = "ships\parus_" + sUpgrade + "_spain.tga";	
				break;
				case PIRATE:
					nationFileName = "ships\parus_" + sUpgrade + "_pirate.tga";
					//BI_objRetValue.normalTex = "ships\sail_Pirates.tga";
				break;
				case HOLLAND:	
					nationFileName = "ships\parus_" + sUpgrade + "_holland.tga";	
				break;
			}
			*/
			
			BI_objRetValue.maxSP = shref.sp;
			// boal -->
			if (CheckAttribute(shref, "EmblemedSails.normalTex")) // заднанный в типе парус
		    {
		        BI_objRetValue.normalTex = shref.EmblemedSails.normalTex;
		        nationFileName           = shref.EmblemedSails.normalTex;
		    }
			if( CheckAttribute(&Characters[chrIdx],"Features.GeraldSails") && sti(Characters[chrIdx].Features.GeraldSails)==true) 
			{
				makearef(arEmbl,shref.GeraldSails);
			} else {
				makearef(arEmbl,shref.EmblemedSails);
			} 
			/*if (CheckAttribute(shref, "GeraldSails"))
		    {
		        makearef(arEmbl, shref.GeraldSails);  */
				// boal <--
			sq = GetAttributesNum(arEmbl);
			for(i=0; i<sq; i++)
			{
				arSail = GetAttributeN(arEmbl,i);
				attrName = GetAttributeName(arSail);
				tmpStr = GetAttributeValue(arSail);
				if( CheckAttribute(arSail,"hscale") ) {
					BI_objRetValue.(attrName).hscale = arSail.hscale;
				}
				if( CheckAttribute(arSail,"vscale") ) {
					BI_objRetValue.(attrName).vscale = arSail.vscale;
				}
				if(tmpStr=="1") {
					//BI_objRetValue.(attrName).Gerald = nationFileName;  
					BI_objRetValue.(attrName) = nationFileName;
				} else {
					BI_objRetValue.(attrName).Gerald = tmpStr;
				}
				//BI_objRetValue.(attrName).Gerald = "ships\chuckskull.tga"; // текстура герба (если не указана, то берётся BI_objRetValue.geraldTex или BI_objRetValue.geraldTexPointer)
				//BI_objRetValue.(attrName).hscale = 0.5; // масштаб в размере паруса (0.5 - герб занимает половину паруса)
				//BI_objRetValue.(attrName).vscale = 0.5; // если нет vscale, то используется = scale
			}
			//}
		}
	}

	return &BI_objRetValue;
}

ref procGetRiggingData()
{
	int i,n,s;

	string datName = GetEventData();
	i = GetEventData();
	n = GetEventData();
	s = GetEventData();	// isSpecial Flag ??	
	
	if(datName == "GetShipFlagTexNum")
	{
		aref rCharacter = GetEventData();

		switch(n)
		{
			case HOLLAND: 	BI_intNRetValue[0] = 0; break;						
			case ENGLAND: 	BI_intNRetValue[0] = 1; break;
			case FRANCE: 	BI_intNRetValue[0] = 2; break;
			case SPAIN: 	BI_intNRetValue[0] = 3; break;
			
			case PIRATE: 	
					BI_intNRetValue[0] = GetPirateFlag(rCharacter);
					BI_intNRetValue[1] = FLAG_PIR; 		
			break;			
		}
		if(n != PIRATE)
		{
			if(s == 1)	BI_intNRetValue[1] = GetShipFlagTextureNum(rCharacter); 	
			else 		BI_intNRetValue[1] = FLAG_CMN;
		}			
	}
	
	if(datName == "GetTownFlagTexNum")
	{				
		switch(n)
		{
			case HOLLAND: 	BI_intNRetValue[0] = 0; break;						
			case ENGLAND: 	BI_intNRetValue[0] = 1; break;
			case FRANCE: 	BI_intNRetValue[0] = 2; break;
			case SPAIN: 	BI_intNRetValue[0] = 3; break;						
			case PIRATE: 	
				BI_intNRetValue[0] = 0; 		
				BI_intNRetValue[1] = FLAG_PIR; 		
			break;
		}		
		if(n != PIRATE)
		{	
			if(s == 1) BI_intNRetValue[1] = FLAG_FRT;
			else	   BI_intNRetValue[1] = FLAG_FRT; 	// приходится вот так вот изгаляться, тк не все модели тулом читаются 
		}				
	}	
	return &BI_intNRetValue;
}


void SetTownFlag(ref loc, object mdl)
{
	if (!CheckAttribute(loc, "townsack")) return;
	int iNation = GetCityNation(loc.townsack);
	SendMessage(&Flag, "lil", MSG_FLAG_INIT_TOWN, &mdl, iNation);
}

void SetFortFlag(ref rModel)
{
	if (!CheckAttribute(rModel, "fortcmdridx")) return;
	int idx = sti(rModel.fortcmdridx);
	if (idx < 0) return;
	ref chr = GetCharacter(idx);
	int iNation = sti(chr.nation);	
	SendMessage(&Flag, "lil", MSG_FLAG_INIT_TOWN, &rModel, iNation);	
}

int GetPirateFlag(ref chr)
{
	if(!CheckAttribute(chr,"id")) return 0;
	if(CheckAttribute(chr, "Flags.Pirate")) 
	{
		return sti(chr.Flags.Pirate);
	}	
	string sGroup = GetGroupIDFromCharacter(chr);
	if(sGroup == "") return 0;
	ref cmdr = Group_GetGroupCommander(sGroup);
	if (!CheckAttribute(cmdr, "Flags.Pirate")) 
	{
		cmdr.Flags.Pirate = rand(2);
	}	
	return sti(cmdr.Flags.Pirate);
}

bool IsShipCommander(ref chr)
{
	string sGroup = GetGroupIDFromCharacter(chr);
	if(sGroup == "") return 0;
	ref cmdr = Group_GetGroupCommander(sGroup);
	if(chr.id == cmdr.id) return true;
	return false;
}

bool IsShipMerchant(ref chr)
{
	if (CheckAttribute(chr, "RealEncounterType") && 
	    CheckAttribute(chr, "Ship.Mode") && 
		chr.Ship.Mode == "trade") return true;
	return false;
}

int GetShipFlagTextureNum(ref chr)
{
	if(!CheckAttribute(chr,"id")) return 0;	
	int iNation = sti(chr.nation);
	
	if(iNation == PIRATE) return FLAG_PIR;
	else
	{		
		//если сдался - выбрасывает белый флаг
		if(CheckAttribute(chr,"surrendered")) return FLAG_WHT;			
		else
		{		
			if(IsCompanion(chr) || IsMainCharacter(chr) || chr.id == "BoatChar") // ГГ , компаньоны, шлюпка у берега
			{
				if(iNation != PIRATE) return FLAG_PER;								
				else				  return FLAG_PIR; 	
			}			
			else
			{			
				// командующие эскадрами
				if(IsShipCommander(chr)) return FLAG_SHP;								
				else
				{
					// купчишки
					if(IsShipMerchant(chr)) return FLAG_MER;								
					// все прочие .. военные патрули, эскорты и т.п.
					else 					return FLAG_FRT;									
				}				
			}			
		}					
	}		
	return FLAG_CMN;
}

void procBISelectShip()
{
	int chrIdx = GetEventData();
	int iRelation = 0; //HardCoffee colour pointers
	bool myShip = false;
	if (chrIdx == nMainCharacterIndex) chrIdx = -1;
	if (chrIdx != -1) iRelation = SeaAI_GetRelation(chrIdx, nMainCharacterIndex);
	for (int i = 0; i < COMPANION_MAX; i++)
	{
		if (GetCompanionIndex(pchar, i) == chrIdx) myShip = true;
	}
	if (myShip) iRelation = RELATION_ALLIANCE;
	SendMessage(&objShipPointer, "lllfffff", MSG_SP_CHANGESHIP, chrIdx, iRelation, 0.005, 1.0, 1.0, 1.0, 5.0);
}

ref procGetSmallFlagData()
{
	int chrIdx = GetEventData();
	BI_intNRetValue[0] = 3;
	BI_intNRetValue[1] = 0;
	if (chrIdx >= 0)
	{
		int iNation = sti(Characters[chrIdx].nation);
		switch (iNation)
		{
			case ENGLAND:	BI_intNRetValue[1] = 3;	break;
			case FRANCE:	BI_intNRetValue[1] = 2;	break;
			case SPAIN:		BI_intNRetValue[1] = 0;	break;
			case HOLLAND:	BI_intNRetValue[1] = 4;	break;
			case PIRATE:	BI_intNRetValue[1] = 5;	break;
		}

		BI_intNRetValue[2] = 7;
		switch (SeaAI_GetRelation(chrIdx,nMainCharacterIndex))
		{
			case RELATION_FRIEND:	BI_intNRetValue[2] = 7; break;
			case RELATION_NEUTRAL:	BI_intNRetValue[2] = 8; break; //HardCoffee нейтралы теперь с белой рамкой
			case RELATION_ENEMY:	BI_intNRetValue[2] = 6; break;
		}
		for (int i = 0; i < COMPANION_MAX; i++) //HardCoffee отдельный цвет для компаньонов
		{
			if (GetCompanionIndex(pchar, i) == chrIdx)
			{
				BI_intNRetValue[2] = 9; //Синий
				break;
			}
		}

	}
	return &BI_intNRetValue;
}

void procMastFall()
{
	int chrIdx = GetEventData();
	string mastName = GetEventData();
	int bFirstFall = GetEventData();

	if(chrIdx<0) return;
	int mastNum = strcut(mastName,4,strlen(mastName)-1);

	//trace("For character "+chrIdx+" fall Mast name "+mastName+" has index "+mastNum);
	SendMessage(&Sailors, "lal", MSG_PEOPLES_ON_SHIP_MASTFALL, GetCharacter(chrIdx), mastNum);
}

void BI_PerkAgainUsable()
{
	BI_SetCommandMode(-1,-1,-1,-1);
}

float GetRigDamage(int shootIdx, int iBallType, ref damage_chr)
{
	ref rBall = GetGoodByType(iBallType);
	float fDistanceDamageMultiply = Bring2Range(1.2, 0.25, 0.0, stf(AIBalls.CurrentMaxBallDistance), stf(AIBalls.CurrentBallDistance));
	float fDmgRig = fDistanceDamageMultiply * stf(rBall.DamageRig);
	//float fDmgRig = stf(rBall.DamageRig);
	int iBonus = 0;	// evganat - энциклопедия
    if (shootIdx >= 0)
	{
		ref shoot_chr = GetCharacter(shootIdx);
		if (CheckOfficersPerk(shoot_chr,"CannonProfessional") )	
		{ 
			// evganat - энциклопедия
			if (IsMainCharacter(shoot_chr) || IsCompanion(shoot_chr))
				iBonus = GetParamPageBonus("CannonProfessional_damage");
			
			fDmgRig *= 1.3 + 0.01*iBonus;
		}
		else if (CheckOfficersPerk(shoot_chr, "SailsDamageUp")) fDmgRig *= 1.15;
	}

	if (CheckOfficersPerk(damage_chr, "ShipDefenseProfessional"))
	{
		// evganat - энциклопедия
		if(IsMainCharacter(damage_chr) || IsCompanion(damage_chr))
			iBonus = GetParamPageBonus("ShipDefenseProfessional_damage");		
		fDmgRig *= 0.65 - 0.01 * iBonus;
	} // fix
	else if (CheckOfficersPerk(damage_chr, "AdvancedBattleState")) fDmgRig *= 0.75; // fix
	else if	(CheckOfficersPerk(damage_chr, "BasicBattleState")) fDmgRig *= 0.85; // fix
	return fDmgRig;
}

void MakeSailDmg(int chrIdx, float dmg)
{
	object objSail;
	if (!GetEntity(&objSail,"sail")) return;

	int iSailsUpgrade = 1;
	if (!CheckAttribute(&characters[chrIdx], "upgrades.sails"))
		characters[chrIdx].upgrades.sails = 1;
	//убираем 1 вариант апгрейда (паруса по умолчанию)
	iSailsUpgrade = sti(characters[chrIdx].upgrades.sails) - 1;
	dmg = dmg + ((dmg / 100) * iSailsUpgrade * 5);
	SendMessage(&objSail, "lslf", MSG_SAIL_SCRIPT_PROCESSING, "RandomSailsDmg", chrIdx, dmg);
}

ref ProcessRandomSailDmg()
{
	BI_g_fRetVal = 0.0;
	//"lslfflll"
	int chrIdx = GetEventData();
	string nodeName = GetEventData();
	int grNum = GetEventData();
	float fDmg = GetEventData();
	float fSPow = GetEventData();
	int hc_new = GetEventData();
	int mhc = GetEventData();
	int hdat_new = GetEventData();

	if(chrIdx<0) return &BI_g_fRetVal;
	ref chref = GetCharacter(chrIdx);
	if(LAi_IsImmortal(chref)) return &BI_g_fRetVal;

	aref arSail;
	string groupName = ""+grNum;
	makearef(arSail,chref.ship.sails.(nodeName).(groupName));

	int hc_old = 0;
	if( CheckAttribute(arSail,"hc") )	hc_old = sti(arSail.hc);
	float fDmg_old = 0.0;
	if( CheckAttribute(arSail,"dmg") )	fDmg_old = stf(arSail.dmg);

	int itmp = hc_new;
	float sailDmgMax = GetCharacterShipSP(chref) * fSPow;

	float fTopDmg = sailDmgMax;
	if(itmp<mhc)	fTopDmg = GetNeedDmgFromHole(itmp+1,sailDmgMax,mhc) - 0.0001;
	if(fTopDmg>fDmg_old+fDmg)	fTopDmg = fDmg_old+fDmg;

	fDmg = fTopDmg-fDmg_old;
	if(fDmg<=0.0)	return &BI_g_fRetVal;
	chref.ship.SP = stf(chref.ship.SP)-fDmg;

	itmp = GetNeedHoleFromDmg(fTopDmg,sailDmgMax,mhc);
	if(itmp>hc_old)
	{
		BI_g_fRetVal = fDmg;
		arSail.hc = hc_new;
		arSail.hd = hdat_new;
	}
	else
	{
		BI_g_fRetVal = -fDmg;
		if( !CheckAttribute(arSail,"hc") )	arSail.hc = 0;
		if( !CheckAttribute(arSail,"hd") )	arSail.hd = 0;
	}

	arSail.mhc = mhc;
	arSail.sp = fSPow;
	arSail.dmg = fTopDmg;

	return &BI_g_fRetVal;
}

void procSetUsingAbility()
{
	int q, i;
	int chIdx = GetEventData();
	int mainIdx = sti(pchar.index);
	aref aroot,arcur;
	string tmpStr;

	if (chIdx < 0 || CharacterIsDead(GetCharacter(chIdx)))
	{
		makearef(aroot,BattleInterface.AbilityIcons);
		q = GetAttributesNum(aroot);
		for (i = 0; i < q; i++)
		{
			arcur = GetAttributeN(aroot,i);
			arcur.enable = false;
		}
		return;
	}

	BattleInterface.Commands.Mine.enable = !GetGlobalTutor();
	// для главного персонажа
	if (mainIdx == chIdx)
	{
		BattleInterface.Commands.Brander.enable = false;

		BattleInterface.Commands.ImmediateReload.enable	= IsSeaPerkReadyForActivation("ImmediateReload");
        BattleInterface.Commands.LightRepair.enable = IsSeaPerkReadyForActivation("LightRepair");
		BattleInterface.Commands.InstantRepair.enable = IsSeaPerkReadyForActivation("InstantRepair");
		BattleInterface.Commands.Turn180.enable = IsSeaPerkReadyForActivation("Turn180");
		
		// Set items abilities
		q = FindQuestUsableItem(&arcur, 0);
		while (q > 0)
		{
			tmpStr = arcur.id;
			if (GetCharacterItem(pchar,arcur.id) > 0)
			{
				BattleInterface.AbilityIcons.(tmpStr).enable	= true;
				BattleInterface.AbilityIcons.(tmpStr).picNum	= arcur.quest.pic;
				BattleInterface.AbilityIcons.(tmpStr).texNum	= 9;
				BattleInterface.AbilityIcons.(tmpStr).event		= arcur.id;
				BattleInterface.AbilityIcons.(tmpStr).quest		= arcur.quest;
			}
			else
			{
				BattleInterface.AbilityIcons.(tmpStr).enable	= false;
			}
			q = FindQuestUsableItem(&arcur,q+1);
		}
	}
	else
	{
		BattleInterface.Commands.Brander.enable			= false;
		if (bAttack && GetRemovable(GetCharacter(chIdx)) && GetOfficersPerkUsing(pchar, "Brander", false))
		{
			BattleInterface.Commands.Brander.enable		= true;
		}
		//BattleInterface.AbilityIcons.Troopers.enable		= GetCharacterPerkUsing(pchar,"Troopers");

		BattleInterface.Commands.InstantRepair.enable	= false;
		BattleInterface.Commands.InstantRepair.enable	= CheckInstantRepairCondition(GetCharacter(chIdx));
		BattleInterface.Commands.ImmediateReload.enable	= GetCharacterPerkUsing(GetCharacter(chIdx), "ImmediateReload");//false;
		BattleInterface.Commands.InstantBoarding.enable	= false;
		BattleInterface.Commands.LightRepair.enable		= false;
		if (GetCharacterPerkUsing(GetCharacter(chIdx),"LightRepair"))
		{
            if (GetHullPercent(GetCharacter(chIdx)) < 10.0 || GetSailPercent(GetCharacter(chIdx)) < 10.0)
			{
                BattleInterface.Commands.LightRepair.enable = true;
			}
		}
		BattleInterface.Commands.Turn180.enable			= GetCharacterPerkUsing(GetCharacter(chIdx), "Turn180");//false;
	}
}

ref procCheckEnableLocator()
{
	BI_intRetValue = true;

	string comName = GetEventData();
	aref arLoc = GetEventData();

	if(comName=="BI_SailTo")
	{
		if( CheckAttribute(&AISea,"Island") && CheckAttribute(arLoc,"name") )
		{
			if (CheckAttribute(&TEV, "DesMoinesMoorDisable") && Sea_FindNearColony(1) == "Maracaibo" && arLoc.name == "reload_4")
				BI_intRetValue = false;
			else
				BI_intRetValue = Island_isGotoEnableLocal(AISea.Island,arLoc.name);
		}
	}

	return &BI_intRetValue;
}

ref procCheckEnableShip()
{
	BI_intRetValue = true;

	string comName = GetEventData();
	int cn = GetEventData();

	ref rCommander;

	if(cn>=0)
	{
		switch(comName)
		{
		case "BI_InstantBoarding": BI_intRetValue = true; break;
		//case "BI_Speak":	BI_intRetValue = true;	break;
		}
	}

	return &BI_intRetValue;
}

void BI_ProcessControlPress()
{
	string ControlName = GetEventData();
	if (sti(InterfaceStates.Launched) != 0) return;

	switch (ControlName)
	{
		case "hk_charge1":
			if (sti(pchar.ship.cargo.goods.balls) < 1)
			{
				PlayInterfaceCommand("knock");
				return;
			}
			if (sti(pchar.Ship.Cannons.Charge.Type) != GOOD_BALLS)
			{
				iChargeBlinks = 0;
				//PlayCharVoice("ChargeBalls");
				SendMessage(&Sound, "lslllll", MSG_SOUND_PLAY, "ChargeBalls", SOUND_WAV_STEREO, VOLUME_SPEECH, false, false, false);
				Ship_ChangeCharge(pchar, GOOD_BALLS);
			}
		break;
	
		case "hk_charge2":
			if (sti(pchar.ship.cargo.goods.grapes) < 1)
			{
				PlayInterfaceCommand("knock");
				return;
			}
			if (sti(pchar.Ship.Cannons.Charge.Type) != GOOD_GRAPES)
			{
				iChargeBlinks = 0;
//				LaunchInfoMessage(2); // сообщение о картечи
				//PlayCharVoice("ChargeGrapes");
				SendMessage(&Sound, "lslllll", MSG_SOUND_PLAY, "ChargeGrapes", SOUND_WAV_STEREO, VOLUME_SPEECH, false, false, false);
				Ship_ChangeCharge(pchar, GOOD_GRAPES);
			}
		break;
	
		case "hk_charge3":
			if (sti(pchar.ship.cargo.goods.knippels) < 1)
			{
				PlayInterfaceCommand("knock");
				return;
			}
			if (sti(pchar.Ship.Cannons.Charge.Type) != GOOD_KNIPPELS)
			{
				iChargeBlinks = 0;
				//PlayCharVoice("ChargeKnippels");
				SendMessage(&Sound, "lslllll", MSG_SOUND_PLAY, "ChargeKnippels", SOUND_WAV_STEREO, VOLUME_SPEECH, false, false, false);
				Ship_ChangeCharge(pchar, GOOD_KNIPPELS);
			}
		break;
	
		case "hk_charge4":
			if (sti(pchar.ship.cargo.goods.bombs) < 1)
			{
				PlayInterfaceCommand("knock");
				return;
			}
			if (sti(pchar.Ship.Cannons.Charge.Type) != GOOD_BOMBS)
			{
				iChargeBlinks = 0;
				//PlayCharVoice("ChargeBombs");
				SendMessage(&Sound, "lslllll", MSG_SOUND_PLAY, "ChargeBombs", SOUND_WAV_STEREO, VOLUME_SPEECH, false, false, false);
				Ship_ChangeCharge(pchar, GOOD_BOMBS);
			}
		break;

		case "hk_perk1":
			if (IsSeaPerkReadyForActivation("Turn180"))
			{
				PlayInterfaceCommand("INTERFACE\Ships_Bell.wav");
				ActivateCharacterPerk(pchar, "Turn180");
				Ship_Turn180(pchar);
			}
			else PlayInterfaceCommand("knock");
		break;
		case "hk_perk2":
			if (IsSeaPerkReadyForActivation("ImmediateReload"))
			{
				PlayInterfaceCommand("INTERFACE\Ships_Bell.wav");
				ActivateCharacterPerk(pchar, "ImmediateReload");
			}
			else PlayInterfaceCommand("knock");
		break;
		case "hk_perk3":
			if (IsSeaPerkReadyForActivation("InstantRepair"))
			{
				PlayInterfaceCommand("INTERFACE\Ships_Bell.wav");
				ActivateCharacterPerk(pchar, "InstantRepair");
				ActivateSpecRepair(pchar, 1);
			}
			else PlayInterfaceCommand("knock");
		break;
		case "hk_perk4":
			if (IsSeaPerkReadyForActivation("LightRepair"))
			{
				PlayInterfaceCommand("INTERFACE\Ships_Bell.wav");
				ActivateCharacterPerk(pchar, "LightRepair");
				ActivateSpecRepair(pchar, 0);
			}
			else PlayInterfaceCommand("knock");
		break;

		case "hk_cabin":
			if (GetGlobalTutor()) return;
			PlayInterfaceCommand("OK");
			Sea_CabinStartNow();
		break;

		case "FireZoneKey":
			bCannonsRangeShow = !bCannonsRangeShow;
			CannonsRangeRefresh();
			RefreshFireZoneTip();
		break;

		case "BICommandsActivate": 
			PlayInterfaceCommand("OK"); // boal даёшь звуки!
		break;
	}
}

ref procGetSRollSpeed()
{
	int chrIdx = GetEventData();
	BI_g_fRetVal = 0.0;
	if (chrIdx >= 0) BI_g_fRetVal = GetRSRollSpeed(GetCharacter(chrIdx));
	return &BI_g_fRetVal;
}
// скорость подъема паруса
float GetRSRollSpeed(ref chref)
{
	int iShip = sti(chref.ship.type);
	if( iShip<0 || iShip>=REAL_SHIPS_QUANTITY ) {return 0.0;}
	
	float fRollSpeed = 0.5 + 0.05 * makefloat( GetSummonSkillFromNameToOld(chref,SKILL_SAILING) ); //fix skill
	int crewQ = GetCrewQuantity(chref);
	if (!CheckAttribute(&RealShips[iShip], "MaxCrew"))
	{
		Log_TestInfo("GetRSRollSpeed нет MaxCrew у корабля НПС ID=" + chref.id);
		return 0.0;
	}
 	int crewMax = sti(RealShips[iShip].MaxCrew);
 	int crewOpt = sti(RealShips[iShip].OptCrew);//boal
 	if (crewMax < crewQ) crewQ  = crewMax; // boal
	// опыт матросов
	float  fExp;
	
	if (crewOpt <= 0) crewOpt = 0; // fix для профилактики деления на ноль
	
	fExp = 0.05 + stf(GetCrewExp(chref, "Sailors") * crewQ) / stf(crewOpt * GetCrewExpRate());
	if (fExp > 1) fExp = 1;
	fRollSpeed = fRollSpeed * fExp;
	// мораль
	float  fMorale = stf(stf(GetCharacterCrewMorale(chref)) / MORALE_MAX);
	fRollSpeed = fRollSpeed * (0.7 + fMorale / 2.0);

	if (iArcadeSails != 1)
	{
		fRollSpeed = fRollSpeed / 2.5;
	}
	if(CheckOfficersPerk(chref, "SailsMan"))
	{
		// evganat - энциклопедия
		int iBonus = 0;
		if(IsCompanionOptimized(chref))
			iBonus = GetParamPageBonus("SailsMan");
		fRollSpeed = fRollSpeed * (1.1 + 0.01*iBonus); // 10%
	}
	return fRollSpeed;
}

ref BI_GetLandData()
{
	int iTmp;
	string attrName;
	aref arLoc, arIsl, arList;
	arLoc = GetEventData();

	BI_intNRetValue[0] = 0;
	BI_intNRetValue[1] = BI_RELATION_NEUTRAL;
	BI_intNRetValue[2] = -1;
	BI_intNRetValue[3] = -1;
	BI_intNRetValue[4] = -1;
	BI_intNRetValue[5] = -1;
	BI_intNRetValue[6] = 0;

	if(CheckAttribute(arLoc,"fort.model"))
	{
		BI_intNRetValue[0] = 1; // тип форт
		int chrIdx = Fort_FindCharacter(AISea.Island,"reload",arLoc.name);
		if(chrIdx>=0)
		{
			switch(SeaAI_GetRelation(chrIdx,nMainCharacterIndex))
			{
				case RELATION_FRIEND:	BI_intNRetValue[1] = BI_RELATION_FRIEND;  break;
				case RELATION_NEUTRAL:	BI_intNRetValue[1] = BI_RELATION_NEUTRAL; break;
				case RELATION_ENEMY:	BI_intNRetValue[1] = BI_RELATION_ENEMY;   break;
			}
			BI_intNRetValue[5] = chrIdx;
		}
	}
	else
	{
		if (CheckAttribute(arLoc,"istown") && arLoc.istown=="1")
		{
			iTmp = FindLocation(arLoc.go);
			if(iTmp>=0)
			{
				iTmp = FindColony(Locations[iTmp].fastreload);
				if(iTmp>=0)
				{
					BI_intNRetValue[0] = 2; // тип город
					switch(GetNationRelation2MainCharacter(sti(Colonies[iTmp].nation)))
					{
						case RELATION_FRIEND:	BI_intNRetValue[1] = BI_RELATION_FRIEND; break;
						case RELATION_NEUTRAL:	BI_intNRetValue[1] = BI_RELATION_NEUTRAL;break;
						case RELATION_ENEMY:	BI_intNRetValue[1] = BI_RELATION_ENEMY;  break;
					}
					BI_intNRetValue[6] = sti(Colonies[iTmp].disease);
				}
			}
		}
	}

	/*if( CheckAttribute(arLoc,"tex") && CheckAttribute(arLoc,"pic") )
	{
		makearef( arIsl, Islands[FindIsland(AISea.Island)] );
		attrName = "InterfaceTextures." + arLoc.tex;
		if( CheckAttribute(arIsl,attrName) )
		{
			BI_intNRetValue[2] = AddTextureToList( &BattleInterface, arIsl.(attrName), sti(arIsl.(attrName).h)*2, sti(arIsl.(attrName).v) );
			BI_intNRetValue[3] = sti(arLoc.pic);
			BI_intNRetValue[4] = sti(arLoc.pic) + sti(arIsl.(attrName).h);
		}
	}*/

	if (CheckAttribute(arLoc,"label"))
	{
		arLoc.labelLoc = GetConvertStr(arLoc.label, "LocLables.txt");
		if (arLoc.labelLoc == "")
		{
			Trace("Warning! Language: string <"+arLoc.label+"> hav`t translation into file <LocLables.txt>");
		}
	}

	if (BI_intNRetValue[2] < 0 || BI_intNRetValue[3] < 0)
	{
		BI_intNRetValue[2] = 0; //AddTextureToList( &BattleInterface, "battle_interface\cicons_locators.tga", 8, 1 );
		switch (BI_intNRetValue[0])
		{
            case 0: // бухта
				if (!CheckAttribute(arLoc, "mayak"))
				{
					BI_intNRetValue[3] = 31;
					BI_intNRetValue[4] = 15;
				}
				else
				{	// маяк
					BI_intNRetValue[3] = 73;
					BI_intNRetValue[4] = 72;
				}
            break;
			case 1: // форт
				BI_intNRetValue[3] = 62;
				BI_intNRetValue[4] = 46;
			break;
			case 2: // город
				BI_intNRetValue[3] = 63;
				BI_intNRetValue[4] = 47;
            break;
		}
	}

	return &BI_intNRetValue;
}

int GetTargChrIndex(int targNum, string locName)
{
	if (targNum == -1) return Fort_FindCharacter(AISea.Island,"reload",locName);
	else return targNum;
}

bool CheckSuccesfullBoard(ref rBoarderChr, ref rSieger)
{
	if (bBettaTestMode) return true;
	if (LAi_IsDead(rSieger)) return false;  // fix
	// skill = 1 -> k = 0.5; skill = 10 -> k = 2.0
	float k = 0.333 + GetSummonSkillFromNameToOld(rBoarderChr, SKILL_SNEAK) * 0.167;

	// skill = 1 -> limit = 0.45 -> 0.2^0.5 (20%);   skill = 10 -> limit = 0.81 -> 0.9^2 (90%)
	float topLimit = 0.41 + GetSummonSkillFromNameToOld(rBoarderChr, SKILL_GRAPPLING) * 0.04;

	if (pow(rand(1000)/1000.0, k) < topLimit) return true;
	return false;
}

// НОВОЕ ГПК патч 1.2.3
// рандомный герб на парус
void SetRandGeraldSail(ref chr, int nation)
{
	string ret = "";
	int    st = GetCharacterShipType(chr);
	ref    shref;
	
	// 1.2.3 переделка на герб привязан к кораблю, то есть при обмене сохранится
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		switch (nation)
		{
		    case ENGLAND:	ret = "eng_" + (1 + rand(4));	break;
	        case FRANCE:	ret = "fra_" + (1 + rand(5));	break;
	        case SPAIN:		ret = "spa_" + (1 + rand(4));	break;
	        case HOLLAND:	ret = "hol_" + (1 + rand(3));	break;
	        case PIRATE:	ret = "pir_" + (1 + rand(5));	break;
		}
		shref.ShipSails.Gerald_Name = ret + ".tga.tx";
	}		
}

void SetSailsColor(ref chr, int col)
{
	int st = GetCharacterShipType(chr);
	ref shref;
	
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		
		shref.SailsColorIdx   = col;
		shref.ShipSails.SailsColor = SailsColors[col].color;
	}		
}

bool CanAbordage(ref chr)
{
    //квестовым компаньонам с заблокированным абордажем не показываем иконки абордажа
    if (CheckAttribute(chr, "Abordage.Enable") && sti(chr.Abordage.Enable) == 0)
    	return false;
    return bAbordage;
}

void BI_ShowCannonsQty()
{
	if (!CheckAttribute(pchar,"Ship.Cannons.Type")) return;
	if (sti(pchar.Ship.Cannons.Type) == CANNON_TYPE_NONECANNON) return;
	if (GetCannonsNum(pchar) < 1) return;
	int iColor = GetColorInt("orange");

	BattleInterface.textinfo.FrontCannon.text = GetBortCannonsQty(pchar, "cannonf");
	BattleInterface.textinfo.BackCannon.text = GetBortCannonsQty(pchar, "cannonb");
	BattleInterface.textinfo.RightCannon.text = GetBortCannonsQty(pchar, "cannonr");
	BattleInterface.textinfo.LeftCannon.text = GetBortCannonsQty(pchar, "cannonl");
	if (sti(BattleInterface.textinfo.FrontCannon.text) < GetBortCannonsMaxQty(pchar, "cannonf"))
		BattleInterface.textinfo.FrontCannon.color = iColor;
	if (sti(BattleInterface.textinfo.BackCannon.text) < GetBortCannonsMaxQty(pchar, "cannonb"))
		BattleInterface.textinfo.BackCannon.color = iColor;
	if (sti(BattleInterface.textinfo.RightCannon.text) < GetBortCannonsMaxQty(pchar, "cannonr"))
		BattleInterface.textinfo.RightCannon.color = iColor;
	if (sti(BattleInterface.textinfo.LeftCannon.text) < GetBortCannonsMaxQty(pchar, "cannonl"))
		BattleInterface.textinfo.LeftCannon.color = iColor;
}

void CannonsRangeRefresh()
{
	/*belamour legendary edition подсветка рэнджа установленных пушек:
	AI_MESSAGE_CANNONS_RANGE   "lllllffl"
	пушки заряжены:
	1 - цвет у борта, 2 - цвет по краям
	пушки разряжены:
	3 - цвет у борта, 4 - цвет по краям, 5 - время возрастания альфы, 6 - время затухания,
	! чем больше альфа, тем больше должны быть показатели 5 и 6
	7 - показывать/ не показывать дистанцию пушек
	*/
	//llll 1-2-центр/край заряжено, 3-4-центр/край разряжено
	//ff время возрастания/убывания
	if (Whr_IsNight()) SendMessage(&AISea, "lllllffl", AI_MESSAGE_CANNONS_RANGE, argb(0,255,255,255), argb(15,255,255,255), argb(0,255,0,0), argb(55,255,0,0), 0.002, 0.002, bCannonsRangeShow);
	else SendMessage(&AISea, "lllllffl", AI_MESSAGE_CANNONS_RANGE, argb(0,255,255,255), argb(25,255,255,255), argb(0,255,0,0), argb(75,255,0,0), 0.002, 0.002, bCannonsRangeShow);
}

bool IsSeaPerkReadyForActivation(string sPerkID)
{
    switch (sPerkID)
	{
		case "InstantRepair":
			if (CheckInstantRepairCondition(pchar))
				return true;
			else return false;
		break;
		case "LightRepair":
			if (!CheckOfficersPerk(pchar, "LightRepair") && GetOfficersPerkUsing(pchar, "LightRepair", false)
				&& or(GetHullPercent(pchar) < 10.0, GetSailPercent(pchar) < 10.0))
			{
				return true;
			}
			else return false;
		break;
		case "Turn180":
			if (!CheckOfficersPerk(pchar, "Turn180") && GetOfficersPerkUsing(pchar, "Turn180", false))
				return true;
			else return false;
		break;
		case "ImmediateReload":
			if (!CheckOfficersPerk(pchar, "ImmediateReload") && GetOfficersPerkUsing(pchar, "ImmediateReload", false))
				return true;
			else return false;
		break;
	}

	return false;
}

bool IsSeaPerkAcquired(string sPerkID)
{
	return IsOfficersPerkAcquired(pchar, sPerkID);
}

string GetPosString(int x1, int y1, int x2, int y2)
{
	return x1 + "," + y1 + "," + x2 + "," + y2;
}

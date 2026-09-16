void ExternControlsInit(bool bFirst)
{
	//Trace("ExternControlsInit");
	ExternInitKeyCodes();

	if(bFirst)
	{
		CI_CreateAndSetControls( "", "ICancel", CI_GetKeyCode("VK_ESCAPE"), 0, false );
		CI_CreateAndSetControls( "", "IAction", CI_GetKeyCode("VK_SPACE"), 0, false );

		return;
	}

	CI_CreateAndSetControls( "", "Map_Best", CI_GetKeyCode("KEY_N"), 0, true); // Отличная карта

	// boal Не подведем -->
	CI_CreateAndSetControls( "", "BOAL_Control", CI_GetKeyCode("VK_F11"), 0, false );
    CI_CreateAndSetControls( "", "BOAL_Control2", CI_GetKeyCode("VK_F12"), 0, false );
    CI_CreateAndSetControls( "", "BOAL_ControF5", CI_GetKeyCode("VK_F5"), 0, false );
    CI_CreateAndSetControls( "", "BOAL_ControF7", CI_GetKeyCode("VK_F7"), 0, false );
    CI_CreateAndSetControls( "", "BOAL_ControlDebug", CI_GetKeyCode("VK_INSERT"), 0, false );
    
    CI_CreateAndSetControls( "", "TimeScaleFaster", CI_GetKeyCode("VK_ADD"), 0, false );
	CI_CreateAndSetControls( "", "TimeScaleSlower", CI_GetKeyCode("VK_SUBTRACT"), 0, false );
	CI_CreateAndSetControls( "", "VK_PAUSETimePause", CI_GetKeyCode("VK_PAUSE"), 0, false );

	CI_CreateAndSetControls( "", "TeleportActive", CI_GetKeyCode("VK_F4"), 0, false );

	if (MOD_BETTATESTMODE == "On")
	{
		// Teleport
		CI_CreateAndSetControls( "", "TeleportUp", CI_GetKeyCode("VK_UP"), 0, false );
		CI_CreateAndSetControls( "", "TeleportDown", CI_GetKeyCode("VK_DOWN"), 0, false );
		CI_CreateAndSetControls( "", "TeleportSelect", CI_GetKeyCode("VK_RETURN"), 0, false );

		// weather
		CI_CreateAndSetControls( "", "WhrPrevWeather", CI_GetKeyCode("VK_L_BREAKE"), 0, false );
		CI_CreateAndSetControls( "", "WhrNextWeather", CI_GetKeyCode("VK_R_BREAKE"), 0, false );
		CI_CreateAndSetControls( "", "WhrUpdateWeather", CI_GetKeyCode("VK_A_QUOTE"), 0, false );

		CI_CreateAndSetControls( "", "CoastFoamLB", CI_GetKeyCode("VK_LBUTTON"), 0, true );
		CI_CreateAndSetControls( "", "CoastFoamRB", CI_GetKeyCode("VK_RBUTTON"), 0, true );
		CI_CreateAndSetControls( "", "CoastFoamINS", CI_GetKeyCode("VK_INSERT"), 0, true );
		CI_CreateAndSetControls( "", "CoastFoamDEL", CI_GetKeyCode("VK_DELETE"), 0, true );
		CI_CreateAndSetControls( "", "CoastFoamCopy", CI_GetKeyCode("KEY_C"), 0, true );
	}
	// boal <--

	// Cameras =====================================================================
	// character camera
	CI_CreateAndSetControls( "", "ChrCamTurnV", CI_GetKeyCode("VK_MROTATION_VERTICAL"), 0, false );
	SetControlForInverting("ChrCamTurnV",false);
	CI_CreateAndSetControls( "", "ChrCamTurnH", CI_GetKeyCode("VK_MROTATION_HORIZONTAL"), 0, false );
	CI_CreateAndSetControls( "", "ChrCamSpecMode", CI_GetKeyCode("VK_CONTROL"), 0, false );
	CI_CreateAndSetControls( "", "Turn V", CI_GetKeyCode("VK_MROTATION_VERTICAL"), INVERSE_CONTROL, false );
	SetControlForInverting("Turn V",true);
	CI_CreateAndSetControls( "", "Turn H", CI_GetKeyCode("VK_MROTATION_HORIZONTAL"), 0, false );
	// ship follow camera
	CI_CreateAndSetControls( "Sailing3Pers", "ShipCamera_Turn_V", CI_GetKeyCode("VK_MROTATION_VERTICAL"), INVERSE_CONTROL, false );
	MapControlToGroup("ShipCamera_Turn_V", "BattleInterfaceControls");
	DoControlInvisible("Sailing3Pers", "ShipCamera_Turn_V");
	DoControlInvisible("BattleInterfaceControls", "ShipCamera_Turn_V");
	SetControlForInverting("ShipCamera_Turn_V",true);
	CI_CreateAndSetControls( "Sailing3Pers", "ShipCamera_Turn_H", CI_GetKeyCode("VK_MROTATION_HORIZONTAL"), 0, false );
	MapControlToGroup("ShipCamera_Turn_H", "BattleInterfaceControls");
	DoControlInvisible("Sailing3Pers", "ShipCamera_Turn_H");
	DoControlInvisible("BattleInterfaceControls", "ShipCamera_Turn_H");
	CI_CreateAndSetControls( "Sailing3Pers", "ShipCamera_Forward", CI_GetKeyCode("VK_MWHEEL_UP"), 0, true );
//	MapControlToGroup("ShipCamera_Forward", "Sailing1Pers");
	CI_CreateAndSetControls( "Sailing3Pers", "ShipCamera_Backward", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, true );
//	MapControlToGroup("ShipCamera_Backward", "Sailing1Pers");
	CI_CreateAndSetControls("Sailing3Pers", "FireCamera_Set", CI_GetKeyCode("VK_RBUTTON"), 0, true);
	MapControlToGroup("FireCamera_Set", "Sailing1Pers");
	MapControlToGroup("FireCamera_Set", "SailingFire");

	// deck camera
	CI_CreateAndSetControls( "Sailing1Pers", "DeckCamera_Turn_V", CI_GetKeyCode("VK_MROTATION_VERTICAL"), 0, false );
	SetControlForInverting("DeckCamera_Turn_V",false);
	DoControlInvisible("Sailing1Pers", "DeckCamera_Turn_V");
	CI_CreateAndSetControls( "Sailing1Pers", "DeckCamera_Turn_H", CI_GetKeyCode("VK_MROTATION_HORIZONTAL"), 0, false );
	DoControlInvisible("Sailing1Pers", "DeckCamera_Turn_H");
	CI_CreateAndSetControls( "Sailing1Pers", "DeckCamera_Forward", CI_GetKeyCode("VK_LBUTTON"), 0, true );
	CI_CreateAndSetControls( "Sailing1Pers", "DeckCamera_Backward", CI_GetKeyCode("VK_MBUTTON"), 0, true );

	// fire camera
	CI_CreateAndSetControls("SailingFire", "FireCamera_Turn_V", CI_GetKeyCode("VK_MROTATION_VERTICAL"), 0, false);
	SetControlForInverting("FireCamera_Turn_V",false);
	DoControlInvisible("SailingFire", "FireCamera_Turn_V");
	CI_CreateAndSetControls("SailingFire", "FireCamera_Turn_H", CI_GetKeyCode("VK_MROTATION_HORIZONTAL"), 0, false);
	DoControlInvisible("SailingFire", "FireCamera_Turn_H");

	// free camera
	CI_CreateAndSetControls( "", "FreeCamera_Turn_V", CI_GetKeyCode("VK_MROTATION_VERTICAL"), INVERSE_CONTROL, false );
	SetControlForInverting("FreeCamera_Turn_V",true);
	CI_CreateAndSetControls( "", "FreeCamera_Turn_H", CI_GetKeyCode("VK_MROTATION_HORIZONTAL"), 0, false );
	CI_CreateAndSetControls( "", "FreeCamera_Forward", CI_GetKeyCode("VK_LBUTTON"), 0, false );  //VK_LBUTTON
	CI_CreateAndSetControls( "", "FreeCamera_Backward", CI_GetKeyCode("VK_RBUTTON"), 0, false );   //VK_RBUTTON


// Character ===================================================================
	CI_CreateAndSetControls( "", "ChrTurnH", CI_GetKeyCode("VK_MROTATION_HORIZONTAL"), 0, false );
	CI_CreateAndSetControls( "PrimaryLand", "ChrForward", CI_GetKeyCode("KEY_W"), 0, true );
	CI_CreateAndSetControls( "PrimaryLand", "ChrForward1", CI_GetKeyCode("VK_RBUTTON"), 0, true ); // вторая команда
	MapControlToGroup("ChrForward","FightModeControls");
	MapControlToGroup("ChrForward","BattleInterfaceControls");
	CI_CreateAndSetControls( "PrimaryLand", "ChrBackward", CI_GetKeyCode("KEY_S"), 0, true );
	MapControlToGroup("ChrBackward","FightModeControls");
	MapControlToGroup("ChrBackward","BattleInterfaceControls");
	CI_CreateAndSetControls( "PrimaryLand", "ChrStrafeLeft", CI_GetKeyCode("KEY_A"), 0, true );
	MapControlToGroup("ChrStrafeLeft","FightModeControls");
	MapControlToGroup("ChrStrafeLeft","BattleInterfaceControls");
	CI_CreateAndSetControls( "PrimaryLand", "ChrStrafeRight", CI_GetKeyCode("KEY_D"), 0, true );
	MapControlToGroup("ChrStrafeRight","FightModeControls");
	MapControlToGroup("ChrStrafeRight","BattleInterfaceControls");
	CI_CreateAndSetControls("PrimaryLand", "ChrSwitchWalk", CI_GetKeyCode("VK_CAPSLOCK"), 0, true); // evganat - переключатель бега, переведено на CAPS
	MapControlToGroup("ChrSwitchWalk","FightModeControls");
	MapControlToGroup("ChrSwitchWalk","BattleInterfaceControls");
	CI_CreateAndSetControls("PrimaryLand", "ChrSprint", CI_GetKeyCode("VK_SHIFT"), 0, true);
	MapControlToGroup("ChrSprint","FightModeControls");
	MapControlToGroup("ChrSprint","BattleInterfaceControls");
	CI_CreateAndSetControls( "PrimaryLand", "ChrFightMode", CI_GetKeyCode("KEY_E"), 0, true );
	
	CI_CreateAndSetControls( "PrimaryLand", "ChrSwitchFightMode", CI_GetKeyCode("KEY_2"), 0, true );
	MapControlToGroup("ChrSwitchFightMode", "FightModeControls");
	
	// evganat - ПРИЦЕЛИВАНИЕ
	CI_CreateAndSetControls("FightModeControls", "ChrAiming", CI_GetKeyCode("KEY_Q"), 0, true);
    CI_CreateAndSetControls("FightModeControls", "ChrFire", CI_GetKeyCode("KEY_Q"), 0, true);
	CI_CreateAndSetControls("FightModeControls", "ChrAimingShot", CI_GetKeyCode("VK_LBUTTON"), 0, true);
    MapControlToGroup("ChrFire","BattleInterfaceControls");
    SyncControls("ChrAiming", "ChrFire");

	// evganat - камера
	CI_CreateAndSetControls("PrimaryLand", "ChrCamCameraSwitch", CI_GetKeyCode("VK_TAB"), 0, true);
	MapControlToGroup("ChrCamCameraSwitch", "FightModeControls");

	CI_CreateAndSetControls("PrimaryLand", "CharacterCamera_Forward", CI_GetKeyCode("VK_MWHEEL_UP"), 0, true);
	MapControlToGroup("CharacterCamera_Forward", "FightModeControls");
	CI_CreateAndSetControls("PrimaryLand", "CharacterCamera_Backward", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, true);
	MapControlToGroup("CharacterCamera_Backward", "FightModeControls");

    // boal -->
	CI_CreateAndSetControls( "PrimaryLand", "BOAL_UsePotion", CI_GetKeyCode("KEY_C"), 0, true ); // Warship 13.06.09 Дефолтом перевесил на "C"
	MapControlToGroup("BOAL_UsePotion","FightModeControls");
	
	// Warship 13.06.09 Выпить противоядие
	CI_CreateAndSetControls("PrimaryLand", "UseAntidote", CI_GetKeyCode("KEY_V"), 0, true);
	MapControlToGroup("UseAntidote", "FightModeControls");

    CI_CreateAndSetControls( "PrimaryLand", "BOAL_DeadSearch", CI_GetKeyCode("KEY_1"), 0, true );
	MapControlToGroup("BOAL_DeadSearch","FightModeControls");
	
	// --> belamour альтернативный модификатор
	CI_CreateAndSetControls( "PrimaryLand", "AltModificator", CI_GetKeyCode("VK_MENU"), 0, false );
	CI_CreateAndSetControls( "PrimaryLand", "AltModificatorOff", CI_GetKeyCode("VK_MENU"), INVERSE_CONTROL, false );
	
	// быстрый переход по заведениям
	CI_CreateAndSetControls( "PrimaryLand", "AltModeFastTravel_Port", CI_GetKeyCode("KEY_1"), 0, true ); // VK_BACK
	CI_CreateAndSetControls( "PrimaryLand", "AltModeFastTravel_store", CI_GetKeyCode("KEY_2"), 0, true );
	CI_CreateAndSetControls( "PrimaryLand", "AltModeFastTravel_Shipyard", CI_GetKeyCode("KEY_3"), 0, true );
	CI_CreateAndSetControls( "PrimaryLand", "AltModeFastTravel_tavern", CI_GetKeyCode("KEY_4"), 0, true );
	CI_CreateAndSetControls( "PrimaryLand", "AltModeFastTravel_townhall", CI_GetKeyCode("KEY_5"), 0, true );
	CI_CreateAndSetControls( "PrimaryLand", "AltModeFastTravel_bank", CI_GetKeyCode("KEY_6"), 0, true );
	CI_CreateAndSetControls( "PrimaryLand", "AltModeFastTravel_church", CI_GetKeyCode("KEY_7"), 0, true );
	CI_CreateAndSetControls( "PrimaryLand", "AltModeFastTravel_Brothel", CI_GetKeyCode("KEY_8"), 0, true );
	CI_CreateAndSetControls( "PrimaryLand", "AltModeFastTravel_PortOffice", CI_GetKeyCode("KEY_9"), 0, true );
	CI_CreateAndSetControls( "PrimaryLand", "AltModeFastTravel_prison", CI_GetKeyCode("KEY_0"), 0, true );
	
	MapControlToGroup("AltModeFastTravel_Port", "AltPressedGroup");
	MapControlToGroup("AltModeFastTravel_store", "AltPressedGroup");
	MapControlToGroup("AltModeFastTravel_Shipyard", "AltPressedGroup");
	MapControlToGroup("AltModeFastTravel_tavern", "AltPressedGroup");
	MapControlToGroup("AltModeFastTravel_townhall", "AltPressedGroup");
	MapControlToGroup("AltModeFastTravel_bank", "AltPressedGroup");
	MapControlToGroup("AltModeFastTravel_church", "AltPressedGroup");
	MapControlToGroup("AltModeFastTravel_Brothel", "AltPressedGroup");
	MapControlToGroup("AltModeFastTravel_PortOffice", "AltPressedGroup");
	MapControlToGroup("AltModeFastTravel_prison", "AltPressedGroup");
	// <-- belamour
	
	CI_CreateAndSetControls( "FightModeControls", "BOAL_ActivateRush", CI_GetKeyCode("KEY_F"), 0, true ); // boal ярость на суше
	// boal <--
	
	CI_CreateAndSetControls("FightModeControls", "HK_SecondWind", CI_GetKeyCode("KEY_B"), 0, true );
	
	//Jonathan A 2009-08-19 -->
	CI_CreateAndSetControls( "PrimaryLand", "OfficersCharge", CI_GetKeyCode("KEY_J"), 0, true );
	MapControlToGroup("OfficersCharge","FightModeControls");
	MapControlToGroup("OfficersCharge","BattleInterfaceControls");

	CI_CreateAndSetControls( "PrimaryLand", "OfficersHold", CI_GetKeyCode("KEY_H"), 0, true );
	MapControlToGroup("OfficersHold","FightModeControls");
	MapControlToGroup("OfficersHold","BattleInterfaceControls");

	CI_CreateAndSetControls( "PrimaryLand", "OfficersFollow", CI_GetKeyCode("KEY_G"), 0, true );
	MapControlToGroup("OfficersFollow","FightModeControls");
	MapControlToGroup("OfficersFollow","BattleInterfaceControls");
	// <-- JA
	
	CI_CreateAndSetControls("PrimaryLand", "RunLootCollector", CI_GetKeyCode("VK_A_TILDA"), 0, true);
	MapControlToGroup("RunLootCollector", "FightModeControls");
	
	CI_CreateAndSetControls("PrimaryLand", "AlchemyKey", CI_GetKeyCode("KEY_K"), 0, true); // Интерфейс мультиобъектов
	MapControlToGroup("AlchemyKey", "BattleInterfaceControls");
	MapControlToGroup("AlchemyKey","Sailing3Pers");
	MapControlToGroup("AlchemyKey","Sailing1Pers");
	MapControlToGroup("AlchemyKey","WorldMapControls");
	MapControlToGroup("AlchemyKey","MainInterface");
	MapControlToGroup("AlchemyKey","SailingFire");

	CI_CreateAndSetControls( "PrimaryLand", "Say", CI_GetKeyCode("KEY_Y"), 0, true );


	CI_CreateAndSetControls( "FightModeControls", "ChrBlock", CI_GetKeyCode("VK_SPACE"), 0, true );
	CI_CreateAndSetControls( "FightModeControls", "ChrAltAttackBase", CI_GetKeyCode("VK_LBUTTON"), 0, true );   //2
	CI_CreateAndSetControls( "FightModeControls", "ChrAttackBreakBase", CI_GetKeyCode("VK_MBUTTON"), 0, true ); //ChrAttackRoundBase
	CI_CreateAndSetControls( "FightModeControls", "ChrAttackBase", CI_GetKeyCode("VK_RBUTTON"), 0, true );   //1

	CI_CreateAndSetControls( "FightModeControls", "ChrAttackChoseBase", CI_GetKeyCode("VK_SHIFT"), 0, true );

	CI_CreateAndSetControls( "FightModeControls", "ChrAttackFient", CI_GetKeyCode("KEY_Z"), 0, true );// финт
	CI_CreateAndSetControls( "FightModeControls", "ChrParry", CI_GetKeyCode("KEY_X"), 0, true ); //парирование


	MapControlToGroup("ChrBlock","BattleInterfaceControls");
	
	CI_CreateAndSetControls( "FightModeControls", "ChrFightMode", CI_GetKeyCode("KEY_E"), 0, true );
	MapControlToGroup("ChrFightMode","BattleInterfaceControls");
	
	CI_CreateAndSetControls( "FightModeControls", "ChrFire", CI_GetKeyCode("KEY_Q"), 0, true );
	
	MapControlToGroup("ChrFire","BattleInterfaceControls");

// Ship ========================================================================
	
	CI_CreateAndSetControls( "Sailing3Pers", "Ship_TurnLeft", CI_GetKeyCode("KEY_A"), 0, true );
	MapControlToGroup("Ship_TurnLeft","Sailing1Pers");
	MapControlToGroup("Ship_TurnLeft","SailingFire");
	CI_CreateAndSetControls( "Sailing3Pers", "Ship_TurnRight", CI_GetKeyCode("KEY_D"), 0, true );
	MapControlToGroup("Ship_TurnRight","Sailing1Pers");
	MapControlToGroup("Ship_TurnRight","SailingFire");
	CI_CreateAndSetControls( "Sailing3Pers", "Ship_SailUp", CI_GetKeyCode("KEY_W"), 0, true );
	MapControlToGroup("Ship_SailUp","Sailing1Pers");
	MapControlToGroup("Ship_SailUp","SailingFire");
	CI_CreateAndSetControls( "Sailing3Pers", "Ship_SailDown", CI_GetKeyCode("KEY_S"), 0, true );
	MapControlToGroup("Ship_SailDown","Sailing1Pers");
	MapControlToGroup("Ship_SailDown","SailingFire");
	CI_CreateAndSetControls( "Sailing3Pers", "Ship_Fire", CI_GetKeyCode("VK_LBUTTON"), 0, true );
	//MapControlToGroup("Ship_Fire","Sailing1Pers");
    MapControlToGroup("Ship_Fire","SailingFire");
	CI_CreateAndSetControls( "Sailing3Pers", "Sea_CameraSwitch", CI_GetKeyCode("VK_TAB"), 0, true );
	MapControlToGroup("Sea_CameraSwitch","Sailing1Pers");
	MapControlToGroup("Sea_CameraSwitch","SailingFire");

	CI_CreateAndSetControls( "Sailing1Pers", "TelescopeMode", CI_GetKeyCode("VK_CONTROL"), 0, true );
	MapControlToGroup("TelescopeMode","SailingFire");

// World map ===================================================================
	CI_CreateAndSetControls( "", "WMapTurnH", CI_GetKeyCode("VK_MROTATION_HORIZONTAL"), 0, false );
	CI_CreateAndSetControls( "", "WMapTurnV", CI_GetKeyCode("VK_MROTATION_VERTICAL"), INVERSE_CONTROL, false );
	//SetControlForInverting("WMapTurnV",true);
	CI_CreateAndSetControls( "WorldMapControls", "WMapForward", CI_GetKeyCode("VK_MWHEEL_UP"), 0, true );
	CI_CreateAndSetControls( "WorldMapControls", "WMapBackward", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, true );
	CI_CreateAndSetControls( "WorldMapControls", "WMapCameraSwitch", CI_GetKeyCode("VK_TAB"), 0, true );

	CI_CreateAndSetControls( "WorldMapControls", "WMapShipSailUp", CI_GetKeyCode("KEY_W"), 0, true );
	
	CI_CreateAndSetControls( "WorldMapControls", "WMapShipSailDown", CI_GetKeyCode("KEY_S"), 0, true );
	
	CI_CreateAndSetControls( "WorldMapControls", "WMapShipTurnLeft", CI_GetKeyCode("KEY_A"), 0, true );
	
	CI_CreateAndSetControls( "WorldMapControls", "WMapShipTurnRight", CI_GetKeyCode("KEY_D"), 0, true );
	CI_CreateAndSetControls( "WorldMapControls", "WMapCancel", CI_GetKeyCode("VK_SPACE"), 0, true );


    // Interface ===================================================================
	// Main interface
	CI_CreateAndSetControls( "", "ITurnH", CI_GetKeyCode("VK_MROTATION_HORIZONTAL"), 0, false );
	CI_CreateAndSetControls( "", "ITurnV", CI_GetKeyCode("VK_MROTATION_VERTICAL"), INVERSE_CONTROL, false );
	CI_CreateAndSetControls( "", "ILClick", CI_GetKeyCode("VK_LBUTTON"), 0, false );
	CI_CreateAndSetControls( "", "IRClick", CI_GetKeyCode("VK_RBUTTON"), 0, false );
	CI_CreateAndSetControls( "Sailing1Pers", "Interface", CI_GetKeyCode("VK_F1"), 0, true );
	MapControlToGroup("Interface","Sailing3Pers");
	MapControlToGroup("Interface","PrimaryLand");
	MapControlToGroup("Interface","WorldMapControls");
	MapControlToGroup("Interface","MainInterface");
	MapControlToGroup("Interface","SailingFire");
	CI_CreateAndSetControls( "Sailing1Pers", "CharacterShipMenu", CI_GetKeyCode("VK_F2"), 0, true );
	MapControlToGroup("CharacterShipMenu","Sailing3Pers");
	MapControlToGroup("CharacterShipMenu","PrimaryLand");
	MapControlToGroup("CharacterShipMenu","WorldMapControls");
	MapControlToGroup("CharacterShipMenu","MainInterface");
	MapControlToGroup("CharacterShipMenu","SailingFire");
	CI_CreateAndSetControls( "Sailing1Pers", "LogbookMenu", CI_GetKeyCode("VK_F3"), 0, true );
	MapControlToGroup("LogbookMenu","Sailing3Pers");
	MapControlToGroup("LogbookMenu","PrimaryLand");
	MapControlToGroup("LogbookMenu","WorldMapControls");
	MapControlToGroup("LogbookMenu","MainInterface");
	MapControlToGroup("LogbookMenu","SailingFire");
	CI_CreateAndSetControls( "Sailing1Pers", "ItemsMenu", CI_GetKeyCode("VK_F4"), 0, true );
	MapControlToGroup("ItemsMenu","Sailing3Pers");
	MapControlToGroup("ItemsMenu","PrimaryLand");
	MapControlToGroup("ItemsMenu","WorldMapControls");
	MapControlToGroup("ItemsMenu","MainInterface");
	MapControlToGroup("ItemsMenu","SailingFire");
	CI_CreateAndSetControls( "Sailing1Pers", "NationsMenu", CI_GetKeyCode("VK_F5"), 0, true );
	MapControlToGroup("NationsMenu","Sailing3Pers");
	MapControlToGroup("NationsMenu","PrimaryLand");
	MapControlToGroup("NationsMenu","WorldMapControls");
	MapControlToGroup("NationsMenu","MainInterface");
	MapControlToGroup("NationsMenu","SailingFire");
	CI_CreateAndSetControls( "Sailing1Pers", "MainMenuDouble", CI_GetKeyCode("VK_ESCAPE"), 0, false );
	MapControlToGroup("MainMenuDouble","Sailing3Pers");
	MapControlToGroup("MainMenuDouble","PrimaryLand");
	MapControlToGroup("MainMenuDouble","WorldMapControls");
	MapControlToGroup("MainMenuDouble","FightModeControls");
	MapControlToGroup("MainMenuDouble","SailingFire");
	CI_CreateAndSetControls( "Sailing1Pers", "QuickSave", CI_GetKeyCode("VK_F6"), 0, false );
	MapControlToGroup("QuickSave","Sailing3Pers");
	MapControlToGroup("QuickSave","PrimaryLand");
	MapControlToGroup("QuickSave","WorldMapControls");
	MapControlToGroup("QuickSave","FightModeControls");
	MapControlToGroup("QuickSave","BattleInterfaceControls");
	MapControlToGroup("QuickSave","SailingFire");
	CI_CreateAndSetControls( "Sailing1Pers", "QuickLoad", CI_GetKeyCode("VK_F9"), 0, false );
	MapControlToGroup("QuickLoad","Sailing3Pers");
	MapControlToGroup("QuickLoad","PrimaryLand");
	MapControlToGroup("QuickLoad","WorldMapControls");
	MapControlToGroup("QuickLoad","FightModeControls");
	MapControlToGroup("QuickLoad","BattleInterfaceControls");
	MapControlToGroup("QuickLoad","SailingFire");
	MapControlToGroup("QuickLoad","DialogControls");
	MapControlToGroup("QuickLoad","MainInterface");
	MapControlToGroup("QuickLoad","VideoPlayer");
	CI_CreateAndSetControls( "", "IStartButton", CI_GetKeyCode("VK_RETURN"), 0, false );
	CI_CreateAndSetControls( "", "ICancel", CI_GetKeyCode("VK_ESCAPE"), 0, false );
	CI_CreateAndSetControls( "", "IAction", CI_GetKeyCode("VK_SPACE"), 0, false );
	CI_CreateAndSetControls( "", "ILeftShift", CI_GetKeyCode("VK_SHIFT"), 0, false );
	CI_CreateAndSetControls( "", "IRightShift", CI_GetKeyCode("VK_SHIFT"), 0, false );
	CI_CreateAndSetControls( "", "IUp", CI_GetKeyCode("VK_UP"), 0, false );
	CI_CreateAndSetControls( "", "IDown", CI_GetKeyCode("VK_DOWN"), 0, false );
	CI_CreateAndSetControls( "", "IRight", CI_GetKeyCode("VK_RIGHT"), 0, false );
	CI_CreateAndSetControls( "", "ILeft", CI_GetKeyCode("VK_LEFT"), 0, false );
	CI_CreateAndSetControls("MainInterface", "InterfaceGoLeft", CI_GetKeyCode("KEY_Q"), 0, false);
	CI_CreateAndSetControls("MainInterface", "InterfaceGoRight", CI_GetKeyCode("KEY_E"), 0, false);
	CI_CreateAndSetControls("MainInterface", "InterfaceTabSwitch", CI_GetKeyCode("VK_TAB"), 0, false);
	CI_CreateAndSetControls("MainInterface", "SC_InterfaceHide", CI_GetKeyCode("KEY_H"), 0, false);

	// Battle interface
	CI_CreateAndSetControls( "Sailing3Pers", "BICommandsActivate", CI_GetKeyCode("VK_RETURN"), 0, true );
	MapControlToGroup("BICommandsActivate","Sailing1Pers");
	MapControlToGroup("BICommandsActivate","WorldMapControls");
	MapControlToGroup("BICommandsActivate","SailingFire");
	CI_CreateAndSetControls( "PrimaryLand", "LICommandsActivate", CI_GetKeyCode("VK_RETURN"), 0, true );
	MapControlToGroup("LICommandsActivate","FightModeControls");

	//HardCoffee дополнительные кнопки для командного меню
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsActivateAdd", CI_GetKeyCode("VK_RETURN"), 0, true);
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsConfirm", CI_GetKeyCode("VK_RETURN"), 0, true);
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsConfirmAdd", CI_GetKeyCode("VK_RETURN"), 0, true);
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsCancel", CI_GetKeyCode("VK_ESCAPE"), 0, false);
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsCancelAdd", CI_GetKeyCode("VK_ESCAPE"), 0, true);
	ControlsMakeIntersectable("BICommandsActivateAdd", "BICommandsConfirmAdd");
	ControlsMakeIntersectable("BICommandsConfirm", "BICommandsConfirmAdd");
	ControlsMakeIntersectable("BICommandsConfirm", "BICommandsActivateAdd");

	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsLeft", CI_GetKeyCode("VK_LEFT"), 0, true);
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsRight", CI_GetKeyCode("VK_RIGHT"), 0, true);
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsUp", CI_GetKeyCode("VK_UP"), 0, true);
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsDown", CI_GetKeyCode("VK_DOWN"), 0, true);
	//EvgAnat - дополнительный контрол переключения команд
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsLeftW", CI_GetKeyCode("VK_MWHEEL_UP"), 0, false);
	CI_CreateAndSetControls("BattleInterfaceControls", "BICommandsRightW", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, false);

	CI_CreateAndSetControls("Sailing3Pers", "MiniMapZoomIn", CI_GetKeyCode("KEY_E"), 0, true);
	MapControlToGroup("MiniMapZoomIn","Sailing1Pers");
	MapControlToGroup("MiniMapZoomIn","SailingFire");
	CI_CreateAndSetControls("Sailing3Pers", "MiniMapZoomOut", CI_GetKeyCode("KEY_F"), 0, true);
	MapControlToGroup("MiniMapZoomOut","Sailing1Pers");
	MapControlToGroup("MiniMapZoomOut","SailingFire");

	CI_CreateAndSetControls("PrimaryLand", "ChrAction", CI_GetKeyCode("VK_LBUTTON"), 0, true);
	CI_CreateAndSetControls("Sailing3Pers", "BIFastCommand", CI_GetKeyCode("VK_SPACE"), 0, true);
	MapControlToGroup("BIFastCommand","Sailing1Pers");
	MapControlToGroup("BIFastCommand","PrimaryLand");
	MapControlToGroup("BIFastCommand","FightModeControls");
	MapControlToGroup("BIFastCommand","WorldMapControls");
	MapControlToGroup("BIFastCommand","BattleInterfaceControls");
	MapControlToGroup("BIFastCommand","SailingFire");

	// hot keys for cannon charge reload
	// Balls
	CI_CreateAndSetControls("Sailing3Pers", "hk_charge1", CI_GetKeyCode("KEY_1"), 0, true);
	MapControlToGroup("hk_charge1", "Sailing1Pers");
	MapControlToGroup("hk_charge1", "BattleInterfaceControls");
	MapControlToGroup("hk_charge1", "SailingFire");
	// Grapes
	CI_CreateAndSetControls("Sailing3Pers", "hk_charge2", CI_GetKeyCode("KEY_2"), 0, true);
	MapControlToGroup("hk_charge2", "Sailing1Pers");
	MapControlToGroup("hk_charge2", "BattleInterfaceControls");
	MapControlToGroup("hk_charge2", "SailingFire");
	// Knippels
	CI_CreateAndSetControls("Sailing3Pers", "hk_charge3", CI_GetKeyCode("KEY_3"), 0, true);
	MapControlToGroup("hk_charge3", "Sailing1Pers");
	MapControlToGroup("hk_charge3", "BattleInterfaceControls");
	MapControlToGroup("hk_charge3", "SailingFire");
	// Bombs
	CI_CreateAndSetControls("Sailing3Pers", "hk_charge4", CI_GetKeyCode("KEY_4"), 0, true);
	MapControlToGroup("hk_charge4", "Sailing1Pers");
	MapControlToGroup("hk_charge4", "BattleInterfaceControls");
	MapControlToGroup("hk_charge4", "SailingFire");
	//Perks
	CI_CreateAndSetControls("Sailing3Pers", "hk_perk1", CI_GetKeyCode("KEY_5"), 0, true);
	MapControlToGroup("hk_perk1", "Sailing1Pers");
	MapControlToGroup("hk_perk1", "BattleInterfaceControls");
	MapControlToGroup("hk_perk1", "SailingFire");

	CI_CreateAndSetControls("Sailing3Pers", "hk_perk2", CI_GetKeyCode("KEY_6"), 0, true);
	MapControlToGroup("hk_perk2", "Sailing1Pers");
	MapControlToGroup("hk_perk2", "BattleInterfaceControls");
	MapControlToGroup("hk_perk2", "SailingFire");

	CI_CreateAndSetControls("Sailing3Pers", "hk_perk3", CI_GetKeyCode("KEY_7"), 0, true);
	MapControlToGroup("hk_perk3", "Sailing1Pers");
	MapControlToGroup("hk_perk3", "BattleInterfaceControls");
	MapControlToGroup("hk_perk3", "SailingFire");

	CI_CreateAndSetControls("Sailing3Pers", "hk_perk4", CI_GetKeyCode("KEY_8"), 0, true);
	MapControlToGroup("hk_perk4", "Sailing1Pers");
	MapControlToGroup("hk_perk4", "BattleInterfaceControls");
	MapControlToGroup("hk_perk4", "SailingFire");

	CI_CreateAndSetControls("Sailing3Pers", "hk_cabin", CI_GetKeyCode("KEY_X"), 0, true); // Переход в каюту (из моря)
	MapControlToGroup("hk_cabin", "Sailing1Pers");
	MapControlToGroup("hk_cabin", "BattleInterfaceControls");
	MapControlToGroup("hk_cabin", "SailingFire");

	CI_CreateAndSetControls("PrimaryLand", "LI_CabinExit", CI_GetKeyCode("KEY_X"), 0, true); // Выход в море (на корабле героя)
	MapControlToGroup("hk_cabin", "BattleInterfaceControls");

	CI_CreateAndSetControls("Sailing3Pers", "FireZoneKey", CI_GetKeyCode("KEY_Q"), 0, true);
	MapControlToGroup("FireZoneKey", "Sailing1Pers");
	MapControlToGroup("FireZoneKey", "SailingFire");

	// переключение режимов залпа (случайный - от носа к корме - от кормы к носу)
	CI_CreateAndSetControls("Sailing3Pers", "hk_FireMode", CI_GetKeyCode("KEY_T"), 0, true);
	MapControlToGroup("hk_FireMode", "Sailing1Pers");
	MapControlToGroup("hk_FireMode", "BattleInterfaceControls");
	MapControlToGroup("hk_FireMode", "SailingFire");

// Dialog =====================================================================
	CI_CreateAndSetControls( "DialogControls", "DlgAction", CI_GetKeyCode("VK_SPACE"), 0, false );
	CI_CreateAndSetControls( "DialogControls", "DlgAction1", CI_GetKeyCode("VK_LBUTTON"), 0, false );   // boal new engine
	CI_CreateAndSetControls( "DialogControls", "DlgAction2", CI_GetKeyCode("VK_RETURN"), 0, false );
	CI_CreateAndSetControls( "", "DlgCancel", CI_GetKeyCode("VK_ESCAPE"), 0, false );
	CI_CreateAndSetControls( "DialogControls", "DlgUp", CI_GetKeyCode("VK_UP"), 0, false );
	CI_CreateAndSetControls( "DialogControls", "DlgDown", CI_GetKeyCode("VK_DOWN"), 0, false );
	CI_CreateAndSetControls( "DialogControls", "DlgUp2", CI_GetKeyCode("VK_MWHEEL_UP"), 0, false );
	CI_CreateAndSetControls( "DialogControls", "DlgDown2", CI_GetKeyCode("VK_MWHEEL_DOWN"), 0, false );
	CI_CreateAndSetControls( "DialogControls", "DlgUp3", CI_GetKeyCode("KEY_W"), 0, false );
	CI_CreateAndSetControls( "DialogControls", "DlgDown3", CI_GetKeyCode("KEY_S"), 0, false );
	CI_CreateAndSetControls( "DialogControls", "DlgScrollUp", CI_GetKeyCode("VK_PRIOR"), 0, false );
	CI_CreateAndSetControls( "DialogControls", "DlgScrollDown", CI_GetKeyCode("VK_NEXT"), 0, false );

	for (int i = 1; i <= 9; i++) {
        CI_CreateAndSetControls("DialogControls", "DlgActionSel" + i, CI_GetKeyCode("KEY_" + i), 0, false);
    }

	// TimeScale (кроме NumPad)
    CI_CreateAndSetControls("BattleInterfaceControls", "TimeScale", CI_GetKeyCode("KEY_R"), 0, true);
    AddControlToSettingsGroups("TimeScale");
	CI_CreateAndSetControls("BattleInterfaceControls", "TimeScaleFasterBA", CI_GetKeyCode("VK_A_PLUS"), 0, true);
    AddControlToSettingsGroups("TimeScaleFasterBA");
	CI_CreateAndSetControls("BattleInterfaceControls", "TimeScaleSlowerBA", CI_GetKeyCode("VK_A_MINUS"), 0, true);
    AddControlToSettingsGroups("TimeScaleSlowerBA");
    MapControlToGroup("TimeScale",       "SailingFire");
    MapControlToGroup("TimeScaleFasterBA", "SailingFire");
    MapControlToGroup("TimeScaleSlowerBA", "SailingFire");

	CI_CreateAndSetControls("PrimaryLand", "MapView", CI_GetKeyCode("KEY_M"), 0, true); // Атлас карт
	MapControlToGroup("MapView", "Sailing1Pers");
	MapControlToGroup("MapView", "Sailing3Pers");
	MapControlToGroup("MapView", "PrimaryLand");
	MapControlToGroup("MapView", "WorldMapControls");
	MapControlToGroup("MapView", "BattleInterfaceControls");
	MapControlToGroup("MapView", "SailingFire");

	// Music by KZ
    CI_CreateAndSetControls("BattleInterfaceControls", "KZ_NextMusicTrack", CI_GetKeyCode("VK_F10"), 0, true);
	MapControlToGroup("KZ_NextMusicTrack", "PrimaryLand");
	MapControlToGroup("KZ_NextMusicTrack", "FightModeControls");
	MapControlToGroup("KZ_NextMusicTrack", "Sailing3Pers");
	MapControlToGroup("KZ_NextMusicTrack", "Sailing1Pers");
	MapControlToGroup("KZ_NextMusicTrack", "WorldMapControls");
	MapControlToGroup("KZ_NextMusicTrack", "SailingFire");

	//Interactive
	CI_CreateAndSetControls("", "IntCode0", CI_GetKeyCode("VK_NUMPAD0"), 0, false);
	CI_CreateAndSetControls("", "IntCode1", CI_GetKeyCode("VK_NUMPAD1"), 0, false);
	CI_CreateAndSetControls("", "IntCode2", CI_GetKeyCode("VK_NUMPAD2"), 0, false);
	CI_CreateAndSetControls("", "IntCode3", CI_GetKeyCode("VK_NUMPAD3"), 0, false);
	CI_CreateAndSetControls("", "IntCode4", CI_GetKeyCode("VK_NUMPAD4"), 0, false);
	CI_CreateAndSetControls("", "IntCode5", CI_GetKeyCode("VK_NUMPAD5"), 0, false);
	CI_CreateAndSetControls("", "IntCode6", CI_GetKeyCode("VK_NUMPAD6"), 0, false);
	CI_CreateAndSetControls("", "IntCode7", CI_GetKeyCode("VK_NUMPAD7"), 0, false);
	CI_CreateAndSetControls("", "IntCode8", CI_GetKeyCode("VK_NUMPAD8"), 0, false);
	CI_CreateAndSetControls("", "IntCode9", CI_GetKeyCode("VK_NUMPAD9"), 0, false);
	CI_CreateAndSetControls("", "IntCodeEnd", CI_GetKeyCode("KEY_I"), 0, false);

	// Маркировать основные клавиши панели для отображения во всех вкладках
    BI_MarkAlwaysDisplay();

	// Рас/Синхронизация клавиш
    SetKeySyncParametres();
}

void ExternInitKeyCodes()
{
	// DIGITS
	objControlsState.key_codes.KEY_0 = 48;
	objControlsState.key_codes.KEY_0.img = "⓪";
	objControlsState.key_codes.KEY_1 = 49;
	objControlsState.key_codes.KEY_1.img = "①";
	objControlsState.key_codes.KEY_2 = 50;
	objControlsState.key_codes.KEY_2.img = "②";
	objControlsState.key_codes.KEY_3 = 51;
	objControlsState.key_codes.KEY_3.img = "③";
	objControlsState.key_codes.KEY_4 = 52;
	objControlsState.key_codes.KEY_4.img = "④";
	objControlsState.key_codes.KEY_5 = 53;
	objControlsState.key_codes.KEY_5.img = "⑤";
	objControlsState.key_codes.KEY_6 = 54;
	objControlsState.key_codes.KEY_6.img = "⑥";
	objControlsState.key_codes.KEY_7 = 55;
	objControlsState.key_codes.KEY_7.img = "⑦";
	objControlsState.key_codes.KEY_8 = 56;
	objControlsState.key_codes.KEY_8.img = "⑧";
	objControlsState.key_codes.KEY_9 = 57;
	objControlsState.key_codes.KEY_9.img = "⑨";

    // LETTERS
	objControlsState.key_codes.KEY_A = 65;
	objControlsState.key_codes.KEY_A.img = "Ⓐ";
	objControlsState.key_codes.KEY_B = 66;
	objControlsState.key_codes.KEY_B.img = "Ⓑ";
	objControlsState.key_codes.KEY_C = 67;
	objControlsState.key_codes.KEY_C.img = "Ⓒ";
	objControlsState.key_codes.KEY_D = 68;
	objControlsState.key_codes.KEY_D.img = "Ⓓ";
	objControlsState.key_codes.KEY_E = 69;
	objControlsState.key_codes.KEY_E.img = "Ⓔ";
	objControlsState.key_codes.KEY_F = 70;
	objControlsState.key_codes.KEY_F.img = "Ⓕ";
	objControlsState.key_codes.KEY_G = 71;
	objControlsState.key_codes.KEY_G.img = "Ⓖ";
	objControlsState.key_codes.KEY_H = 72;
	objControlsState.key_codes.KEY_H.img = "Ⓗ";
	objControlsState.key_codes.KEY_I = 73;
	objControlsState.key_codes.KEY_I.img = "Ⓘ";
	objControlsState.key_codes.KEY_J = 74;
	objControlsState.key_codes.KEY_J.img = "Ⓙ";
	objControlsState.key_codes.KEY_K = 75;
	objControlsState.key_codes.KEY_K.img = "Ⓚ";
	objControlsState.key_codes.KEY_L = 76;
	objControlsState.key_codes.KEY_L.img = "Ⓛ";
	objControlsState.key_codes.KEY_M = 77;
	objControlsState.key_codes.KEY_M.img = "Ⓜ";
	objControlsState.key_codes.KEY_N = 78;
	objControlsState.key_codes.KEY_N.img = "Ⓝ";
	objControlsState.key_codes.KEY_O = 79;
	objControlsState.key_codes.KEY_O.img = "Ⓞ";
	objControlsState.key_codes.KEY_P = 80;
	objControlsState.key_codes.KEY_P.img = "Ⓟ";
	objControlsState.key_codes.KEY_Q = 81;
	objControlsState.key_codes.KEY_Q.img = "Ⓠ";
	objControlsState.key_codes.KEY_R = 82;
	objControlsState.key_codes.KEY_R.img = "Ⓡ";
	objControlsState.key_codes.KEY_S = 83;
	objControlsState.key_codes.KEY_S.img = "Ⓢ";
	objControlsState.key_codes.KEY_T = 84;
	objControlsState.key_codes.KEY_T.img = "Ⓣ";
	objControlsState.key_codes.KEY_U = 85;
	objControlsState.key_codes.KEY_U.img = "Ⓤ";
	objControlsState.key_codes.KEY_V = 86;
	objControlsState.key_codes.KEY_V.img = "Ⓥ";
	objControlsState.key_codes.KEY_W = 87;
	objControlsState.key_codes.KEY_W.img = "Ⓦ";
	objControlsState.key_codes.KEY_X = 88;
	objControlsState.key_codes.KEY_X.img = "Ⓧ";
	objControlsState.key_codes.KEY_Y = 89;
	objControlsState.key_codes.KEY_Y.img = "Ⓨ";
	objControlsState.key_codes.KEY_Z = 90;
	objControlsState.key_codes.KEY_Z.img = "Ⓩ";

    // MOUSE
	objControlsState.key_codes.VK_LBUTTON	= 1;
	objControlsState.key_codes.VK_LBUTTON.img = "ᐼ";
	objControlsState.key_codes.VK_RBUTTON	= 2;
	objControlsState.key_codes.VK_RBUTTON.img = "ᐽ";
	objControlsState.key_codes.VK_MBUTTON	= 4;
	objControlsState.key_codes.VK_MBUTTON.img = "ᐲ";
	objControlsState.key_codes.VK_XBUTTON1	= 5;
	objControlsState.key_codes.VK_XBUTTON1.img = "ᐲ"; //TO_DO
	objControlsState.key_codes.VK_XBUTTON2	= 6;
	objControlsState.key_codes.VK_XBUTTON2.img = "ᐲ"; //TO_DO
    // MOUSE ADDITIONAL (TO_DO)
	objControlsState.key_codes.VK_MROTATION_HORIZONTAL	= 256; //CE_MOUSE_X_AXIS
	objControlsState.key_codes.VK_MROTATION_HORIZONTAL.img = "ᐲ";
	objControlsState.key_codes.VK_MROTATION_VERTICAL	= 257; //CE_MOUSE_Y_AXIS
	objControlsState.key_codes.VK_MROTATION_VERTICAL.img = "ᐲ";
	objControlsState.key_codes.VK_MWHEEL_UP		= 258; //CE_MOUSE_WHEEL_UP
	objControlsState.key_codes.VK_MWHEEL_UP.img = "ᐱ";
	objControlsState.key_codes.VK_MWHEEL_DOWN	= 259; //CE_MOUSE_WHEEL_DOWN
	objControlsState.key_codes.VK_MWHEEL_DOWN.img = "ᐯ";

    // NUMPAD
	objControlsState.key_codes.VK_NUMPAD0     = 96;
	objControlsState.key_codes.VK_NUMPAD0.img = "⓿";
	objControlsState.key_codes.VK_NUMPAD1     = 97;
	objControlsState.key_codes.VK_NUMPAD1.img = "⓵";
	objControlsState.key_codes.VK_NUMPAD2     = 98;
	objControlsState.key_codes.VK_NUMPAD2.img = "⓶";
	objControlsState.key_codes.VK_NUMPAD3     = 99;
	objControlsState.key_codes.VK_NUMPAD3.img = "⓷";
	objControlsState.key_codes.VK_NUMPAD4     = 100;
	objControlsState.key_codes.VK_NUMPAD4.img = "⓸";
	objControlsState.key_codes.VK_NUMPAD5     = 101;
	objControlsState.key_codes.VK_NUMPAD5.img = "⓹";
	objControlsState.key_codes.VK_NUMPAD6     = 102;
	objControlsState.key_codes.VK_NUMPAD6.img = "⓺";
	objControlsState.key_codes.VK_NUMPAD7     = 103;
	objControlsState.key_codes.VK_NUMPAD7.img = "⓻";
	objControlsState.key_codes.VK_NUMPAD8     = 104;
	objControlsState.key_codes.VK_NUMPAD8.img = "⓼";
	objControlsState.key_codes.VK_NUMPAD9     = 105;
	objControlsState.key_codes.VK_NUMPAD9.img = "⓽";
	objControlsState.key_codes.VK_MULTIPLY    = 106;
	objControlsState.key_codes.VK_MULTIPLY.img = "⊗";
	objControlsState.key_codes.VK_ADD     = 107;
	objControlsState.key_codes.VK_ADD.img = "⊕";
	objControlsState.key_codes.VK_SEPARATOR	= 108;
	objControlsState.key_codes.VK_SEPARATOR.img = "⌴"; //TO_DO ⊙
	objControlsState.key_codes.VK_SUBTRACT	= 109;
	objControlsState.key_codes.VK_SUBTRACT.img = "⊖";
	objControlsState.key_codes.VK_DECIMAL	= 110;
	objControlsState.key_codes.VK_DECIMAL.img = "⌴"; //TO_DO ⊚
	objControlsState.key_codes.VK_DIVIDE	= 111;
	objControlsState.key_codes.VK_DIVIDE.img = "⊘";

    // FUNCTION KEYS
	objControlsState.key_codes.VK_F1     = 112;
	objControlsState.key_codes.VK_F1.img = "⑴";
	objControlsState.key_codes.VK_F2     = 113;
	objControlsState.key_codes.VK_F2.img = "⑵";
	objControlsState.key_codes.VK_F3     = 114;
	objControlsState.key_codes.VK_F3.img = "⑶";
	objControlsState.key_codes.VK_F4     = 115;
	objControlsState.key_codes.VK_F4.img = "⑷";
	objControlsState.key_codes.VK_F5     = 116;
	objControlsState.key_codes.VK_F5.img = "⑸";
	objControlsState.key_codes.VK_F6     = 117;
	objControlsState.key_codes.VK_F6.img = "⑹";
	objControlsState.key_codes.VK_F7     = 118;
	objControlsState.key_codes.VK_F7.img = "⑺";
	objControlsState.key_codes.VK_F8     = 119;
	objControlsState.key_codes.VK_F8.img = "⑻";
	objControlsState.key_codes.VK_F9     = 120;
	objControlsState.key_codes.VK_F9.img = "⑼";
	objControlsState.key_codes.VK_F10     = 121;
	objControlsState.key_codes.VK_F10.img = "⑽";
    objControlsState.key_codes.VK_F11     = 122;
	objControlsState.key_codes.VK_F11.img = "⑾";
    objControlsState.key_codes.VK_F12     = 123;
	objControlsState.key_codes.VK_F12.img = "⑿";

    // OTHER (TO_DO: ПЕРЕВЕРИТЬ)
	objControlsState.key_codes.VK_BACK     = 8;
	objControlsState.key_codes.VK_BACK.img = "↰";
	objControlsState.key_codes.VK_TAB      = 9;
	objControlsState.key_codes.VK_TAB.img  = "⇄";
	objControlsState.key_codes.VK_RETURN   = 13;
	objControlsState.key_codes.VK_RETURN.img = "↲";
	objControlsState.key_codes.VK_SHIFT     = 16;
	objControlsState.key_codes.VK_SHIFT.img = "⇪";
	objControlsState.key_codes.VK_CONTROL   = 17;
	objControlsState.key_codes.VK_CONTROL.img = "∁";

	objControlsState.key_codes.VK_ESCAPE	= 27;
	objControlsState.key_codes.VK_ESCAPE.img = "↺";
	objControlsState.key_codes.VK_SPACE		= 32;
	objControlsState.key_codes.VK_SPACE.img = "⌴";
	objControlsState.key_codes.VK_PRIOR		= 33;
	objControlsState.key_codes.VK_PRIOR.img = "⊼";
	objControlsState.key_codes.VK_NEXT		= 34;
	objControlsState.key_codes.VK_NEXT.img  = "⊻";
	objControlsState.key_codes.VK_CAPSLOCK  = 20;
	objControlsState.key_codes.VK_CAPSLOCK.img = "⇵";

	objControlsState.key_codes.VK_LEFT		= 37;
	objControlsState.key_codes.VK_LEFT.img  = "←";
	objControlsState.key_codes.VK_UP		= 38;
	objControlsState.key_codes.VK_UP.img    = "↑";
	objControlsState.key_codes.VK_RIGHT		= 39;
	objControlsState.key_codes.VK_RIGHT.img = "→";
	objControlsState.key_codes.VK_DOWN		= 40;
	objControlsState.key_codes.VK_DOWN.img  = "↓";

    // TO_DO ПЕРЕВЕРИТЬ (ИКОНОК НЕТ)
	objControlsState.key_codes.VK_MENU      = 18;
	objControlsState.key_codes.VK_MENU.img  = "ₐ";
	objControlsState.key_codes.VK_PAUSE	    = 19;
	objControlsState.key_codes.VK_PAUSE.img = "⌴"; //TO_DO
	objControlsState.key_codes.VK_INSERT	  = 45;
	objControlsState.key_codes.VK_INSERT.img  = "⎀";
	objControlsState.key_codes.VK_DELETE	  = 46;
	objControlsState.key_codes.VK_DELETE.img  = "⌦";
	objControlsState.key_codes.VK_A_POINT     = 186;    //; :
	objControlsState.key_codes.VK_A_POINT.img = ";";
	objControlsState.key_codes.VK_A_PLUS      = 187;    //= +
	objControlsState.key_codes.VK_A_PLUS.img  = "⊞";
	objControlsState.key_codes.VK_A_SMALL     = 188;    //, <
	objControlsState.key_codes.VK_A_SMALL.img = "<";
	objControlsState.key_codes.VK_A_MINUS     = 189;    //- _
	objControlsState.key_codes.VK_A_MINUS.img = "⊟";
	objControlsState.key_codes.VK_A_BIG		  = 190;    //. >
	objControlsState.key_codes.VK_A_BIG.img   = ">";
	objControlsState.key_codes.VK_A_QWS	      = 191;    //?/
	objControlsState.key_codes.VK_A_QWS.img   = "‽";
	objControlsState.key_codes.VK_A_TILDA     = 192;    // ` ~
	objControlsState.key_codes.VK_A_TILDA.img  = "∼";
	objControlsState.key_codes.VK_L_BREAKE     = 219;   //[ {
	objControlsState.key_codes.VK_L_BREAKE.img = "〈";
	objControlsState.key_codes.VK_A_SLUSH	   = 220;   // \ |
	objControlsState.key_codes.VK_A_SLUSH.img  = "∤";
	objControlsState.key_codes.VK_R_BREAKE	   = 221;   //] }
	objControlsState.key_codes.VK_R_BREAKE.img = "〉";
	objControlsState.key_codes.VK_A_QUOTE      = 222;   //' "
	objControlsState.key_codes.VK_A_QUOTE.img  = "᾿";

    // Порядок учитывается в поиске бинда для остальных групп
    objControlsState.keygroups.FightModeControls = "";
	objControlsState.keygroups.PrimaryLand  = "";
	objControlsState.keygroups.Sailing3Pers = "";
	objControlsState.keygroups.Sailing1Pers = "";
	objControlsState.keygroups.WorldMapControls = "";

	// Key groups for controls remapping
	objControlsState.grouplist.FightModeControls = true;
	objControlsState.grouplist.PrimaryLand  = true;
	objControlsState.grouplist.Sailing3Pers = true;
	objControlsState.grouplist.Sailing1Pers = true;
	objControlsState.grouplist.WorldMapControls = true;
	objControlsState.grouplist.AltPressedGroup  = true;
    objControlsState.grouplist.BattleInterfaceControls = true;
	objControlsState.grouplist.MainInterface = true;
}

void SetKeySyncParametres()
{
    // В указанных парах можно менять кнопки, когда на второй уже стоит такой же бинд
    // Распространяется сразу на все группы (запрещать в одной, но разрешать в другой — пока нечего)

    // Прицеливание и стрельба
    SameBindingAllowed("ChrAiming", "ChrFire", 1);
    // Спринт и модификатор атаки
    SameBindingAllowed("ChrSprint", "ChrAttackChoseBase", 0);
    // Блок и быстрое действие
    SameBindingAllowed("ChrBlock", "BIFastCommand", 0);
    // Командное меню и движение
    SameBindingAllowed("ChrForward",     "BICommandsUp",    2);
    SameBindingAllowed("ChrBackward",    "BICommandsDown",  2);
    SameBindingAllowed("ChrStrafeLeft",  "BICommandsLeft",  2);
    SameBindingAllowed("ChrStrafeRight", "BICommandsRight", 2);
    // Командное меню и управление кораблём в море и на глобалке
    SameBindingAllowed("Ship_SailUp",    "BICommandsUp",    3);
    SameBindingAllowed("Ship_SailDown",  "BICommandsDown",  3);
    SameBindingAllowed("Ship_TurnLeft",  "BICommandsLeft",  3);
    SameBindingAllowed("Ship_TurnRight", "BICommandsRight", 3);
    // Командное меню, удары, выстрелы
    SameBindingAllowed("ChrAltAttackBase", "ChrAimingShot", 0);
}

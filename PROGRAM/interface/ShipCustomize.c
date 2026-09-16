// AlexBlade - Интерфейс изменения внешнего вида корабля

#define SAIL_COLOR_WHITE 0

#define SAIL_UPGRADE_COMMON 1
#define SAIL_UPGRADE_PAT 2
#define SAIL_UPGRADE_SILK 3
#define SAIL_MATERIAL_FD 4
#define SAIL_MATERIAL_UNIQUE 5

#define HULL_TYPE_MAX 12 // Максимум hull'ов в реале пока 7
#define HULL_TYPE_MIN 1

#define EMPTY_GERALD_PIC_NAME "empty"

#define SC_DEFAULT_WINDOW 0
#define SC_SAILS_COLOR_WINDOW 1
#define SC_SAILS_MATERIAL_WINDOW 2
#define SC_SAILS_GERALD_WINDOW 3
#define SC_HULL_COLOR_WINDOW 4
#define SC_DIALOG_WINDOW 5
#define SC_PHOTOMODE_WINDOW 6

ref _ownerChRef;
ref _real_ship;
ref chref;
ref _shipyarderRef;

int iHulls = 1;
// state
int currentWindow;
int bckupCurrentWindow = 0;
object SC_State;
bool bIsInit = false;
bool bShowMaterialAttention = false;
bool bMV_Drag = false;
float translationCamTimer = 0.0;
float curTranslationCoef = 0.0;

bool bSC_SetPhotoMode = false;
bool bSC_HidePhotoModeControls = false;
float SC_v_translateCoef = 0.0;
float SC_GlobalWindAngle = PI / 6;
float SC_zShipSpeed = 0.0;
float SC_SkyRotateAngle = 0.0;
float SC_PhotoModeGridPos = 0.0;

// Entities
object real_ship_model;
object fake_sail;
object fake_rope;
object fake_ship;
object fake_flag;
object fake_vant;
object fake_vantL;
object fake_vantZ;

object sea_obj;
object seafoam_obj;
object shipTrack_obj;

// WeatherBackup
int whrBckpColor = 0;
int whrBckpAmbient = 0;
int whrBckpFogEnable = 0;

#event_handler("Control Activation", "ProcessInterfaceControls"); // обработка сторонних контролов

void InitInterface_RR(string iniName, ref shipyarder, ref ownerChref)
{
	// лочим квест и карту
    bQuestCheckProcessFreeze = true;
	
	_shipyarderRef = shipyarder;
	_ownerChRef = ownerChref;
	//use fake char to edit ship
	chref = &Characters[NPC_GenerateCharacter("ShipCustom_fakeChar", "citiz_1", MAN, "man", 1, sti(ownerChref.nation), 0, false)];
	chref.ship.type = ownerChref.ship.type;
	chref.Features.GeraldSails = true;
	
	int _shipType = GetCharacterShipType(chref);
	if (_shipType == SHIP_NOTUSED) {
		Trace("Cannot open ShipCustomize, character has no ship");
		Log_Info("Cannot open ShipCustomize, character has no ship");
		return;
	}
	_real_ship = GetRealShip(_shipType);
	if (!TestRef(_real_ship)) {
		Trace("Cannot open ShipCustomize, character has no RealShip");
		Log_Info("Cannot open ShipCustomize, character has no RealShip");
		return;
	}
	
	iHulls = GetShipHulls(_real_ship.Name);
	
	InitShipCustomizeState(_real_ship, ownerChref);
	
	SetEventHandlers();
	
	GameInterface.title = "titleShipCustomize";
    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	SetNodesInitState(ownerChref);

	setLighting();
	resolveModelViewerShip(_real_ship, sti(SC_State.Current.HullIdx));
}

void InitShipCustomizeState(ref _real_ship, ref ownerChref) {
	SC_State.ShipClass = GetCharacterShipClass(ownerChref);
	SC_State.MainCharRank = sti(pchar.rank);
	// SC_State.CanSetSailsGerald = CanSetSailsGerald(chref) && CheckAttribute(_real_ship, "GeraldSails");
	SC_State.CanSetSailsGerald = CanSetSailsGerald(chref) && CheckSailsGerald(chref);
	
	// Hull
	SC_State.Initials.HullIdx = 1;
	SC_State.Current.HullIdx = 1;
	if (CheckAttribute(_real_ship, "ship.upgrades.hull")) {
		SC_State.Initials.HullIdx = sti(_real_ship.ship.upgrades.hull);
		SC_State.Current.HullIdx = sti(SC_State.Initials.HullIdx);
	}
	
	if (iHulls <= 1 || !CheckAttribute(_real_ship, "HullsAmount")) {
		SC_State.HullChangeNotAvailable = true;
	}

	if (iHulls > 1)
		SC_State.HullAmount = iHulls;

	if (CheckAttribute(_real_ship, "isNationalHull") && sti(_real_ship.isNationalHull) == true){
		SC_State.IsNationalHull = true;
	}
	
	// Sail material
	int curSailMaterialIdx = 0;
	int curSailUpgrade = SAIL_UPGRADE_COMMON;
	if (CheckAttribute(_real_ship, "Ship.upgrades.sails")) {
		curSailUpgrade = sti(_real_ship.ship.upgrades.sails);
	} else {
		_real_ship.ship.upgrades.sails = SAIL_UPGRADE_COMMON;
	}
	curSailMaterialIdx = curSailUpgrade - 1;
	string _sailTexFileName = "";
	bool isSailTexUnique = false;
	if (CheckAttribute(_real_ship, "EmblemedSails.normalTex")) {
		string parusName = FindStringAfterSubstr(FindStringBeforeSubstr(_real_ship.EmblemedSails.normalTex, ".tga"), "parus_");

		if (parusName == "common" && curSailUpgrade != SAIL_UPGRADE_COMMON) {
			DeleteAttribute(_real_ship, "EmblemedSails.normalTex");
			_real_ship.Ship.upgrades.sails = SAIL_UPGRADE_COMMON;
			curSailMaterialIdx = SAIL_UPGRADE_COMMON - 1;
		}
		if (parusName == "pat" && curSailUpgrade != SAIL_UPGRADE_PAT) {
			curSailUpgrade = SAIL_UPGRADE_PAT;
			DeleteAttribute(_real_ship, "EmblemedSails.normalTex");
			_real_ship.Ship.upgrades.sails = SAIL_UPGRADE_PAT;
			curSailMaterialIdx = SAIL_UPGRADE_PAT - 1;
		}
		if (parusName == "silk" && curSailUpgrade != SAIL_UPGRADE_SILK) {
			curSailUpgrade = SAIL_UPGRADE_SILK;
			DeleteAttribute(_real_ship, "EmblemedSails.normalTex");
			_real_ship.Ship.upgrades.sails = SAIL_UPGRADE_SILK;
			curSailMaterialIdx = SAIL_UPGRADE_SILK - 1;
		}
		if (parusName == "common_torn") {
			_real_ship.Ship.upgrades.sails = SAIL_UPGRADE_COMMON;
			_sailTexFileName = _real_ship.EmblemedSails.normalTex;
			curSailMaterialIdx = SAIL_MATERIAL_FD - 1;
		} else {
			// Unique textures
			if (parusName == "pesgovna" || parusName == "SoleyRu") {
				_real_ship.Ship.upgrades.sails = SAIL_UPGRADE_COMMON;
				_sailTexFileName = _real_ship.EmblemedSails.normalTex;
				isSailTexUnique = true;
				curSailMaterialIdx = SAIL_MATERIAL_UNIQUE - 1;
			} else {
				//Unknown
				if (CheckAttribute(_real_ship, "EmblemedSails.normalTex")) {
					DeleteAttribute(_real_ship, "EmblemedSails.normalTex");
					_real_ship.Ship.upgrades.sails = SAIL_UPGRADE_COMMON;
					curSailMaterialIdx = SAIL_UPGRADE_COMMON - 1;
				}
			}
		}
	}
	SC_State.Initials.sailMaterial.Idx = curSailMaterialIdx;
	SC_State.Initials.sailMaterial.upgrade = curSailUpgrade;
	SC_State.Initials.sailMaterial.tex.fileName = _sailTexFileName;
	SC_State.Initials.sailMaterial.tex.isUnique = isSailTexUnique;
	SC_State.Current.sailMaterial.Idx = curSailMaterialIdx;
	SC_State.Current.sailMaterial.upgrade = curSailUpgrade;
	SC_State.Current.sailMaterial.tex.fileName = _sailTexFileName;
	
	// Sail color
	SC_State.Initials.sailColor = SAIL_COLOR_WHITE;
	if (CheckAttribute(_real_ship, "SailsColorIdx")) {
		SC_State.Initials.sailColor = sti(_real_ship.SailsColorIdx);
	}
	SC_State.Current.sailColor = sti(SC_State.Initials.sailColor);
	
	// Sail gerald
	if (CheckAttribute(_real_ship, "ShipSails.Gerald_Name")) {
		SC_State.Initials.sailGeraldName = _real_ship.ShipSails.Gerald_Name;
		SC_State.Current.sailGeraldName = _real_ship.ShipSails.Gerald_Name;
	}
	
	// Ship load
	SC_SetShipLoad(0.5);
}

void SetEventHandlers() {
	SetEventHandler("TableSelectChange","procTabChange", 0);
	SetEventHandler("ievnt_command","ProcCommand", 0);
	SetEventHandler("onTableClick","procTableClick", 0);
	
	SetEventHandler("confirmChange_V_COEF_EDIT", "confirmChange_V_COEF_EDIT", 0);
	SetEventHandler("confirmChange_GRID_POS_EDIT", "confirmChange_GRID_POS_EDIT", 0);
	SetEventHandler("eSlideChange","procSlideChange",0);
	
	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
}

void DelEventHandlers() {
	DelEventHandler("TableSelectChange","procTabChange");
	DelEventHandler("ievnt_command","ProcCommand");
	DelEventHandler("onTableClick","procTableClick");
	
	DelEventHandler("confirmChange_V_COEF_EDIT", "confirmChange_V_COEF_EDIT");
	DelEventHandler("confirmChange_GRID_POS_EDIT", "confirmChange_GRID_POS_EDIT");
	DelEventHandler("eSlideChange","procSlideChange");
	
	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
}

void SetNodesInitState(ref ownerChref) {
	FillChangesTable();
	FillPricesTable();
	SetNodeUsing("CLOSE_CURRENT_CHANGE_BUTTON", false);

	// Sail Material
	SetNodeUsing("SAILS_MATERIAL_ATTENTION", false);
	SetNodeUsing("SAILS_MATERIAL_ATTENTION_FRAME", false);
	
	// Sail Gerald
	SetNodeUsing("SAILS_GERALD_UNAVAILABLE", false);
	SetFormatedText("SAILS_GERALD_UNAVAILABLE", XI_ConvertString("SC_Sails_Gerald_Unavailable"));
	
	// Hull
	SetNodeUsing("HULL_COLOR_UNAVAILABLE", false);
	SetFormatedText("HULL_COLOR_UNAVAILABLE", XI_ConvertString("SC_Hull_Color_Unavailable"));
	
	// Other
	SetNewPicture("CHARACTER_PICTURE", "interfaces\portraits\128\face_" + ownerChref.FaceId + ".tga");
	SetFormatedText("SUMMARY_TITLE", XI_ConvertString("SC_SummaryTitle"));
	SetFormatedText("CHARACTER_NAME", GetFullName(ownerChref));
	SetFormatedText("CHARACTER_MONEY_TEXT", MakeMoneyShow(sti(pchar.money), MONEY_SIGN, MONEY_DELIVER));
	SetFormatedText("SHIP_NAME_TEXT", ownerChref.ship.name);
	SetFormatedText("SHIP_TYPE_TEXT", XI_ConvertString(_real_ship.BaseName));
	
	//Debug photo mode
	FillExtraSettingsTable();
	//Draw Help Control image
 	if (CheckAttribute(&objControlsState, "keygroups.MainInterface.SC_InterfaceHide"))
 	{
	 	string sKeyName = objControlsState.keygroups.MainInterface.SC_InterfaceHide;
		SendMessage(&GameInterface,"lslsssllllllfl",MSG_INTERFACE_MSG_TO_NODE,"CONTROLS_HELP_TEXT", 0, "SC_HelpControlImage", objControlsState.key_codes.(sKeyName).img, "KEYBOARD_SYMBOL",
			670,543, argb(255,255,255,255),argb(255,255,255,255), SCRIPT_ALIGN_RIGHT,
			false, 0.55, 0);
 	}
	SetNodeUsing("CONTROLS_HELP_TEXT", false);
	// v_translate
	SC_v_translateCoef = 0.333;
	GameInterface.PHOTO_MODE_V_COEF_EDIT.str = FloatToString(SC_v_translateCoef, 3);
	// global_wind
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"PHOTO_MODE_WIND_ANGLE_SLIDE", 0, SC_GetGlobalWindAngleAsRangePos());
	// sky_angle
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"PHOTO_MODE_SKY_ANGLE_SLIDE", 0, SC_GetSkyRotateAngleAsRangePos());
	// ship_load
	SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"PHOTO_MODE_SHIP_IMMERSION_SLIDE", 0, SC_GetShipLoad());
	// grid position
	SC_SetPhotoGridPos(0.290);
	GameInterface.PHOTO_MODE_GRID_POS_EDIT.str = FloatToString(SC_PhotoModeGridPos, 3);
	
	FillSailsMaterialTable();
	FillSailsColorTable();
	FillSailsGeraldTable();
	FillHullColorTable();
	
	SetCurrentNode("MODEL_VIEWER_TEST");
	HideAllWindows();
	currentWindow = SC_DEFAULT_WINDOW;
}

void FillChangesTable() {
	string _tableName = "TABLE_CHANGES";
	GameInterface.(_tableName).hr.td1.str = "";
	GameInterface.(_tableName).tr1.td1.str = XI_ConvertString("SC_SailColorText");
	GameInterface.(_tableName).tr2.td1.str = XI_ConvertString("SC_SailMaterialText");
	GameInterface.(_tableName).tr3.td1.str = XI_ConvertString("SC_GeraldText");
	GameInterface.(_tableName).tr4.td1.str = XI_ConvertString("SC_HullColorText");
	
	Table_UpdateWindow(_tableName);
}

void FillPricesTable() {
	string _rowId;
	string _tableName = "TABLE_PRICES";
	GameInterface.(_tableName).hr.td1.str = "";
	for (int _i=0; _i < 4; _i++) {
		_rowId = "tr" + (_i+1);
		GameInterface.(_tableName).(_rowId).td1.str = "";
	}
	
	aref pricesRef; makearef(pricesRef, SC_State.Price);
	if (CheckAttribute(pricesRef, "SailColor")) {
		GameInterface.(_tableName).tr1.td1.str = MakeMoneyShow(sti(pricesRef.SailColor), MONEY_SIGN, MONEY_DELIVER);
	}
	if (CheckAttribute(pricesRef, "SailMaterial")) {
		GameInterface.(_tableName).tr2.td1.str = MakeMoneyShow(sti(pricesRef.SailMaterial), MONEY_SIGN, MONEY_DELIVER);
	}
	if (CheckAttribute(pricesRef, "Gerald")) {
		GameInterface.(_tableName).tr3.td1.str = MakeMoneyShow(sti(pricesRef.Gerald), MONEY_SIGN, MONEY_DELIVER);
	}
	if (CheckAttribute(pricesRef, "HullColor")) {
		GameInterface.(_tableName).tr4.td1.str = MakeMoneyShow(sti(pricesRef.HullColor), MONEY_SIGN, MONEY_DELIVER);
	}
	
	int priceAccum = GetPriceSummary();
	bool bSetActiveBuyBtn = priceAccum > 0 && sti(pchar.money) >= priceAccum;
	Button_SetEnable("BUTTON_BUY", bSetActiveBuyBtn);
	if (bSetActiveBuyBtn) {
		SetFormatedText("SUMMARY_TEXT", XI_ConvertString("SC_SummaryText") + ": " + MakeMoneyShow(priceAccum, MONEY_SIGN, MONEY_DELIVER));
	} else {
		SetFormatedText("SUMMARY_TEXT", "");
	}
	
	Table_UpdateWindow(_tableName);
}

void FillSailsColorTable() {
	string _tableName = "TABLE_SAILS_COLOR";
	GameInterface.(_tableName).hr.td1.str = "";
	
	string _sailTexFileName = "ships\parus_common.tga.tx";
	if (CheckAttribute(&SC_State, "Initials.sailMaterial.tex.fileName")) {
		if (SC_State.Initials.sailMaterial.tex.fileName != "") {
			_sailTexFileName = SC_State.Initials.sailMaterial.tex.fileName;
		} else {
			string sCurMaterialTableRowAttr = "tr" + (sti(SC_State.Initials.sailMaterial.Idx) + 1);
			_sailTexFileName = GameInterface.TABLE_SAILS_MATERIAL.(sCurMaterialTableRowAttr).td1.icon1.texture;
			
		}
	}
	
	int colorsCount = GetArraySize(&SailsColors);
	string _trAttr;
	for (int i = 0; i < colorsCount; i++) {
		_trAttr = "tr" + (i + 1);
		GameInterface.(_tableName).(_trAttr).td1.ID = "f" + i;
		GameInterface.(_tableName).(_trAttr).td1.str = XI_ConvertString(SailsColors[i].name);
		GameInterface.(_tableName).(_trAttr).td1.textoffset = "50,0";
		GameInterface.(_tableName).(_trAttr).td1.fontidx=0;
		GameInterface.(_tableName).(_trAttr).td1.scale=0.65;
		GameInterface.(_tableName).(_trAttr).td1.icon1.texture = _sailTexFileName;
		GameInterface.(_tableName).(_trAttr).td1.icon1.color = SailsColors[i].color;
		GameInterface.(_tableName).(_trAttr).td1.icon1.width = 44;
		GameInterface.(_tableName).(_trAttr).td1.icon1.height = 44;
		GameInterface.(_tableName).(_trAttr).td1.icon1.offset = "-1,0";
		
		GameInterface.(_tableName).(_trAttr).td2.valign = "bottom";
		GameInterface.(_tableName).(_trAttr).td2.align = "right";
		GameInterface.(_tableName).(_trAttr).td2.textoffset = "0,-3";
		GameInterface.(_tableName).(_trAttr).td2.color = argb(255, 252,255, 128);
	}

	int selectRowIdx = 1;
	if (CheckAttribute(&SC_State, "Initials.sailColor")) {
		selectRowIdx = sti(SC_State.Initials.sailColor) + 1;
	}
	_trAttr = "tr" + selectRowIdx;
	GameInterface.(_tableName).select = selectRowIdx;
	GameInterface.(_tableName).(_trAttr).td1.icon2.group = "usedflag";
	GameInterface.(_tableName).(_trAttr).td1.icon2.image = "usedflag";
	GameInterface.(_tableName).(_trAttr).td1.icon2.width = 60;
	GameInterface.(_tableName).(_trAttr).td1.icon2.height = 60;
	GameInterface.(_tableName).(_trAttr).td1.icon2.offset = "-12,-12";
	GameInterface.(_tableName).(_trAttr).td2.str = XI_ConvertString("SC_Current");

	Table_UpdateWindow(_tableName);
	
	SetScrollForSelectedTableRow(_tableName, selectRowIdx, 6);
}

void FillSailsGeraldTable() {
	int i = 0;
	
	object objFileFinder;
	aref arList, arFile;
	int iNumFiles;
	string sFile, sName;
	string sDirectory = "ships\gerald\";
	
	objFileFinder.dir = "resource\textures\" + sDirectory;
	objFileFinder.mask = "*.tga.tx";
	
	CreateEntity(&objFileFinder, "FINDFILESINTODIRECTORY");
	makearef(arList, objFileFinder.filelist);
	iNumFiles = GetAttributesNum(arList);
	
	string _geraldTexFileName = "";
	int _currentIdx = 0;
	if (CheckAttribute(&SC_State, "Initials.sailGeraldName")) {
		_geraldTexFileName = SC_State.Initials.sailGeraldName;
	}
	
	string sAttrNum = its(0);
	SC_State.Interface.Gerald.Pictures.(sAttrNum).texturePath = "ships\emptygerald.tga.tx";
	SC_State.Interface.Gerald.Pictures.(sAttrNum).Idx = 0;
	SC_State.Interface.Gerald.PicturesCount = iNumFiles + 1;
	for (; i < iNumFiles; i++) 
	{
		arFile = GetAttributeN(arList, i);
		sFile = GetAttributeValue(arFile);
		string _nationShortName = strcut(sFile, 0, 2);
		
		if (_geraldTexFileName == sFile) {
			_currentIdx = i + 1;
		}
		
		sAttrNum = its(i+1);
		SC_State.Interface.Gerald.Pictures.(sAttrNum).texturePath = sDirectory + sFile;
		SC_State.Interface.Gerald.Pictures.(sAttrNum).FileName = sFile;
		SC_State.Interface.Gerald.Pictures.(sAttrNum).Idx = (i + 1);
	}
	SC_State.Initials.sailGerald.Idx = _currentIdx;
	SC_State.Current.sailGerald.Idx = _currentIdx;
	DeleteClass(&objFileFinder);
	
	string _tableName = "TABLE_SAILS_GERALD";
	int tableColNum = 4;
	string sAttrRow, sAttrCol;
	
	GameInterface.(_tableName).hr.td1.str = "";
	
	int _currentRowIdx = 1;
	int _currentColIdx = 1;
	aref geraldPictures; makearef(geraldPictures, SC_State.Interface.Gerald.Pictures);
	for (i = 0; i < GetAttributesNum(geraldPictures); i++) {
		aref geraldPic = GetAttributeN(geraldPictures, i);
		
		int rowIdx = (i / tableColNum) + 1;
		int colIdx = (i % tableColNum) + 1;
		sAttrRow = "tr" + rowIdx;
		sAttrCol = "td" + colIdx;
		int _idx = sti(geraldPic.idx);
		if (_currentIdx == _idx) {
			_currentRowIdx = rowIdx;
			_currentColIdx = colIdx;
		}
		
		GameInterface.(_tableName).(sAttrRow).(sAttrCol).Idx = _idx;
		GameInterface.(_tableName).(sAttrRow).(sAttrCol).valign = "bottom";
		GameInterface.(_tableName).(sAttrRow).(sAttrCol).align = "center";
		GameInterface.(_tableName).(sAttrRow).(sAttrCol).color = argb(255, 252,255, 128);
		GameInterface.(_tableName).(sAttrRow).(sAttrCol).icon1.texture = geraldPic.texturePath;
		GameInterface.(_tableName).(sAttrRow).(sAttrCol).icon1.width = 64;
		GameInterface.(_tableName).(sAttrRow).(sAttrCol).icon1.height = 64;
		GameInterface.(_tableName).(sAttrRow).(sAttrCol).icon1.offset = "-3,0";
	}

	sAttrRow = "tr" + _currentRowIdx;
	sAttrCol = "td" + _currentColIdx;
	
	GameInterface.(_tableName).select = _currentRowIdx;
	GameInterface.(_tableName).selectCol = _currentColIdx;
	GameInterface.(_tableName).(sAttrRow).(sAttrCol).str = XI_ConvertString("SC_Current");
	GameInterface.(_tableName).(sAttrRow).(sAttrCol).icon2.group = "usedflag";
	GameInterface.(_tableName).(sAttrRow).(sAttrCol).icon2.image = "usedflag";
	GameInterface.(_tableName).(sAttrRow).(sAttrCol).icon2.width = 60;
	GameInterface.(_tableName).(sAttrRow).(sAttrCol).icon2.height = 60;
	GameInterface.(_tableName).(sAttrRow).(sAttrCol).icon2.offset = "-6,-6";
	
	Table_UpdateWindow(_tableName);
	
	SetScrollForSelectedTableRow(_tableName, _currentRowIdx, 4);
}

void FillSailsMaterialTable() {
	string _tableName = "TABLE_SAILS_MATERIAL";
	string _trAttr;

	GameInterface.(_tableName).hr.td1.str = "";
	
	for (int i = 0; i < 5; i++) {
		_trAttr = "tr" + (i + 1);
		
		GameInterface.(_tableName).(_trAttr).td1.fontidx=0;
		GameInterface.(_tableName).(_trAttr).td1.scale=0.65;
		GameInterface.(_tableName).(_trAttr).td1.textoffset = "56,0";
		GameInterface.(_tableName).(_trAttr).td1.textoffsets.s2 = "14";
		GameInterface.(_tableName).(_trAttr).td1.icon1.width = 52;
		GameInterface.(_tableName).(_trAttr).td1.icon1.height = 52;
		GameInterface.(_tableName).(_trAttr).td1.icon1.offset = "-3,0";
		
		GameInterface.(_tableName).(_trAttr).td1.icon2.width = 60;
		GameInterface.(_tableName).(_trAttr).td1.icon2.height = 60;
		GameInterface.(_tableName).(_trAttr).td1.icon2.offset = "-12,-8";
		
		GameInterface.(_tableName).(_trAttr).td2.textoffset = "0,-3";
		GameInterface.(_tableName).(_trAttr).td2.valign = "bottom";
		GameInterface.(_tableName).(_trAttr).td2.align = "right";
		GameInterface.(_tableName).(_trAttr).td2.color = argb(255, 252,255, 128);
	}
	
	GameInterface.(_tableName).tr1.td1.str = XI_ConvertString("SC_SailMaterialCommon");
	GameInterface.(_tableName).tr1.td1.Id = "common";
	GameInterface.(_tableName).tr1.td1.icon1.texture = "ships\parus_common" + ".tga.tx";
	
	GameInterface.(_tableName).tr2.td1.str = XI_ConvertString("SC_SailMaterialPat");
	GameInterface.(_tableName).tr2.td1.Id = "pat";
	GameInterface.(_tableName).tr2.td1.icon1.texture = "ships\parus_pat" + ".tga.tx";
	
	GameInterface.(_tableName).tr3.td1.str = XI_ConvertString("SC_SailMaterialSilk");
	GameInterface.(_tableName).tr3.td1.Id = "silk";
	GameInterface.(_tableName).tr3.td1.icon1.texture = "ships\parus_silk" + ".tga.tx";
	
	GameInterface.(_tableName).tr4.td1.str = XI_ConvertString("SC_SailMaterialFD");
	GameInterface.(_tableName).tr4.td1.Id = "FD";
	GameInterface.(_tableName).tr4.td1.icon1.texture = "ships\parus_common_torn" + ".tga.tx";
	if (!CheckFlyingDutchmanSailAvailable()) {
		GameInterface.(_tableName).tr4.td2.str = XI_ConvertString("SC_Unavailable");
		GameInterface.(_tableName).tr4.td2.color = argb(255,255,110,74);
	} 
	
	if (CheckAttribute(&SC_State, "Initials.sailMaterial.tex.isUnique") && sti(SC_State.Initials.sailMaterial.tex.isUnique)) {
		string _texFileName = SC_State.Initials.sailMaterial.tex.fileName;
		string parusName = FindStringAfterSubstr(FindStringBeforeSubstr(_texFileName, ".tga"), "parus_");
		GameInterface.(_tableName).tr5.td1.str = XI_ConvertString("SC_SailMaterial" + parusName);
		GameInterface.(_tableName).tr5.td1.Id = "U_" + parusName;
		GameInterface.(_tableName).tr5.td1.icon1.texture = _texFileName;
	} else {
		aref arTable; makearef(arTable, GameInterface.(_tableName));
		DeleteAttribute(arTable, "tr5");
	}
	
	int selectRowIdx = sti(SC_State.Initials.sailMaterial.Idx) + 1;
	_trAttr = "tr" + selectRowIdx;
	GameInterface.(_tableName).select = selectRowIdx;
	GameInterface.(_tableName).(_trAttr).td1.icon2.group = "usedflag";
	GameInterface.(_tableName).(_trAttr).td1.icon2.image = "usedflag";

	string sMaterialName = GameInterface.(_tableName).(_trAttr).td1.Id;
	if (StrStartsWith(sMaterialName, "U_")) {
		GameInterface.(_tableName).(_trAttr).td2.str = XI_ConvertString("SC_Current") + "\n" + XI_ConvertString("SC_Unique");
		GameInterface.(_tableName).(_trAttr).td2.color = argb(255, 74, 255, 110);
	} else {
		GameInterface.(_tableName).(_trAttr).td2.str = XI_ConvertString("SC_Current");
	}

	Table_UpdateWindow(_tableName);
}

void FillHullColorTable() {
	if (CheckAttribute(&SC_State, "HullChangeNotAvailable")) {
		return;
	}
	
	string _tableName = "TABLE_HULL_COLOR";
	string _trAttr;

	GameInterface.(_tableName).hr.td1.str = "";
	
	int hullAmount = 0;
	bool _isNationalHull = false;
	if (CheckAttribute(&SC_State, "IsNationalHull")) {
		hullAmount = 4;
		_isNationalHull = true;
	} else {
		hullAmount = sti(SC_State.HullAmount);
	}
	
	
	for (int i = 0; i < hullAmount; i++) {
		_trAttr = "tr" + (i + 1);
		
		GameInterface.(_tableName).(_trAttr).td1.str = XI_ConvertString("SC_HullDescVariation") + " - " + (i + 1);
		GameInterface.(_tableName).(_trAttr).td1.textoffset = "50,0";
		GameInterface.(_tableName).(_trAttr).td1.textoffsets.s2 = "14";
		GameInterface.(_tableName).(_trAttr).td1.textoffsets.s3 = "14";
		GameInterface.(_tableName).(_trAttr).td1.fontidx=0;
		GameInterface.(_tableName).(_trAttr).td1.scale=0.65;
		
		if (_isNationalHull) {
			GameInterface.(_tableName).(_trAttr).td1.str = GetHullTypesDesc(i);
			GameInterface.(_tableName).(_trAttr).td1.textoffset = "48,0";
		}
		
		GameInterface.(_tableName).(_trAttr).td1.icon1.group = "SHIP_STATE_ICONS";
		GameInterface.(_tableName).(_trAttr).td1.icon1.image = "Hull";
		GameInterface.(_tableName).(_trAttr).td1.icon1.width = 44;
		GameInterface.(_tableName).(_trAttr).td1.icon1.height = 44;
		GameInterface.(_tableName).(_trAttr).td1.icon1.offset="-2,0";
		
		if (_isNationalHull) {
			GameInterface.(_tableName).(_trAttr).td1.icon1.group = "NATIONS";
			GameInterface.(_tableName).(_trAttr).td1.icon1.image = GetNationNameByType(i);
			GameInterface.(_tableName).(_trAttr).td1.icon1.width = 44;
			GameInterface.(_tableName).(_trAttr).td1.icon1.height = 44;
			GameInterface.(_tableName).(_trAttr).td1.icon1.offset="-4,0";
		}
		
		GameInterface.(_tableName).(_trAttr).td2.valign = "bottom";
		GameInterface.(_tableName).(_trAttr).td2.align = "right";
		GameInterface.(_tableName).(_trAttr).td2.textoffset = "0,-3";
		GameInterface.(_tableName).(_trAttr).td2.color = argb(255, 252, 255, 128);
	}
	
	int selectRowIdx = sti(SC_State.Initials.HullIdx);
	_trAttr = "tr" + selectRowIdx;
	GameInterface.(_tableName).select = selectRowIdx;
	GameInterface.(_tableName).(_trAttr).td1.icon2.group = "usedflag";
	GameInterface.(_tableName).(_trAttr).td1.icon2.image = "usedflag";
	GameInterface.(_tableName).(_trAttr).td1.icon2.width = 60;
	GameInterface.(_tableName).(_trAttr).td1.icon2.height = 60;
	GameInterface.(_tableName).(_trAttr).td1.icon2.offset = "-12,-12";
	
	GameInterface.(_tableName).(_trAttr).td2.str = XI_ConvertString("SC_Current");

	Table_UpdateWindow(_tableName);
}

// Ни дня без костылей
// TODO ПЕРЕНЕСТИ в двигло
void SetScrollForSelectedTableRow(string tableNodeName, int selectRowIdx, int maxVisibleTableRows) {
	int i;
	GameInterface.(tableNodeName).select = 0;
	Table_UpdateWindow(tableNodeName);
	
	if (selectRowIdx <= 0) {
		return;
	}
	
	if (selectRowIdx <= maxVisibleTableRows) {
		for (i = 0; i < selectRowIdx; i++)
			SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,tableNodeName, -1, 3, "downstep");
	} else {
		for (i = 0; i < maxVisibleTableRows; i++)
			SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,tableNodeName, -1, 3, "downstep");
	
		for (i = 0; i < (selectRowIdx - maxVisibleTableRows) * 2; i++)
			SendMessage(&GameInterface,"lslls",MSG_INTERFACE_MSG_TO_NODE,tableNodeName, -1, 3, "downstep");
	}
}

void HideAllWindows() {
	SetNodeUsing("SAILS_GERALD_UNAVAILABLE", false);
	SetNodeUsing("HULL_COLOR_UNAVAILABLE", false);
	
	XI_WindowDisable("DIALOG_WINDOW", true);
	XI_WindowShow("DIALOG_WINDOW", false);
	
	XI_WindowDisable("SAILS_GERALD_WINDOW", true);
	XI_WindowShow("SAILS_GERALD_WINDOW", false);
	
	XI_WindowDisable("SAILS_COLOR_WINDOW", true);
	XI_WindowShow("SAILS_COLOR_WINDOW", false);
	
	XI_WindowDisable("SAILS_MATERIAL_WINDOW", true);
	XI_WindowShow("SAILS_MATERIAL_WINDOW", false);
	
	XI_WindowDisable("HULL_COLOR_WINDOW", true);
	XI_WindowShow("HULL_COLOR_WINDOW", false);
	
	XI_WindowDisable("PHOTO_MODE_WINDOW", true);
	XI_WindowShow("PHOTO_MODE_WINDOW", false);
}

void ShowWindowByTabMode(int nMode) {
	HideAllWindows();
	
	switch (nMode)
	{
		case 1:
			XI_WindowDisable("SAILS_COLOR_WINDOW", false);
			XI_WindowShow("SAILS_COLOR_WINDOW", true);
			currentWindow = SC_SAILS_COLOR_WINDOW;
			SetCurrentNode("TABLE_SAILS_COLOR");
			SetNodeUsing("CLOSE_CURRENT_CHANGE_BUTTON", true);
			SetMV_Camera_ToLeft_Smooth();
		break;
		case 2:
			XI_WindowDisable("SAILS_MATERIAL_WINDOW", false);
			XI_WindowShow("SAILS_MATERIAL_WINDOW", true);
			currentWindow = SC_SAILS_MATERIAL_WINDOW;
			SetCurrentNode("TABLE_SAILS_MATERIAL");
			if (!bShowMaterialAttention) {
				SetNodeUsing("SAILS_MATERIAL_ATTENTION", false);
				SetNodeUsing("SAILS_MATERIAL_ATTENTION_TITLE", false);
				SetNodeUsing("SAILS_MATERIAL_ATTENTION_FRAME", false);
			}
			SetNodeUsing("CLOSE_CURRENT_CHANGE_BUTTON", true);
			SetMV_Camera_ToLeft_Smooth();
		break;
		case 3:
			currentWindow = SC_SAILS_GERALD_WINDOW;
			if (sti(SC_State.CanSetSailsGerald)) {
				XI_WindowDisable("SAILS_GERALD_WINDOW", false);
				XI_WindowShow("SAILS_GERALD_WINDOW", true);
				SetCurrentNode("TABLE_SAILS_GERALD");
			} else {
				SetNodeUsing("CURRENT_CHANGE_FRAME", true);
				SetNodeUsing("SAILS_GERALD_UNAVAILABLE", true);
			}
			SetNodeUsing("CLOSE_CURRENT_CHANGE_BUTTON", true);
			SetMV_Camera_ToLeft_Smooth();
		break;
		case 4:
			currentWindow = SC_HULL_COLOR_WINDOW;
			if (!CheckAttribute(&SC_State, "HullChangeNotAvailable")) {
				XI_WindowDisable("HULL_COLOR_WINDOW", false);
				XI_WindowShow("HULL_COLOR_WINDOW", true);
				SetCurrentNode("TABLE_HULL_COLOR");
			} else {
				SetNodeUsing("CURRENT_CHANGE_FRAME", true);
				SetNodeUsing("HULL_COLOR_UNAVAILABLE", true);
			}
			SetNodeUsing("CLOSE_CURRENT_CHANGE_BUTTON", true);
			SetMV_Camera_ToLeft_Smooth();
		break;
	}
}

void procTableClick() {
	string _tableName = GetEventData();
	int iRowIndex = GetEventData();
	int iColIndex = GetEventData();
	
	string _trAttr, _tdAttr;
	switch(_tableName) {
		case "TABLE_SAILS_COLOR":
			int currentColorRow = sti(SC_State.Current.sailColor) + 1;
			DeleteAttribute(&GameInterface, _tableName + ".tr" + currentColorRow + ".td1.icon2");
			
			_trAttr = "tr" + (iRowIndex + 1);
			GameInterface.(_tableName).(_trAttr).td1.icon2.group = "usedflag";
			GameInterface.(_tableName).(_trAttr).td1.icon2.image = "usedflag";
			GameInterface.(_tableName).(_trAttr).td1.icon2.width = 60;
			GameInterface.(_tableName).(_trAttr).td1.icon2.height = 60;
			GameInterface.(_tableName).(_trAttr).td1.icon2.offset = "-12,-12";
			Table_UpdateWindow(_tableName);
			
			SetSailColor(iRowIndex);
		break;
		case "TABLE_SAILS_MATERIAL":
			ClearSailsMaterialAttention();
			if (sti(SC_State.Initials.sailMaterial.Idx) == SAIL_MATERIAL_UNIQUE - 1) {
				// Uniques
				SetSailsMaterialAttention(XI_ConvertString("SC_Unique"), XI_ConvertString("SC_SailUnique_WarningText"));
			}
			if (iRowIndex == SAIL_MATERIAL_FD - 1) {
				// Dutchman
				if (!CheckFlyingDutchmanSailAvailable()) {
					SetSailsMaterialAttention(XI_ConvertString("SC_Unavailable"), XI_ConvertString("SC_SailFD_UnavailableText"));
					return;
				}
			}
			
			int currentMaterialRow = sti(SC_State.Current.sailMaterial.Idx) + 1;
			DeleteAttribute(&GameInterface, _tableName + ".tr" + currentMaterialRow + ".td1.icon2");
			
			_trAttr = "tr" + (iRowIndex + 1);
			GameInterface.(_tableName).(_trAttr).td1.icon2.group = "usedflag";
			GameInterface.(_tableName).(_trAttr).td1.icon2.image = "usedflag";
			GameInterface.(_tableName).(_trAttr).td1.icon2.width = 60;
			GameInterface.(_tableName).(_trAttr).td1.icon2.height = 60;
			GameInterface.(_tableName).(_trAttr).td1.icon2.offset = "-12,-8";
			Table_UpdateWindow(_tableName);
			
			SetSailMaterial(iRowIndex);
			SetSailMaterialTextureForTableSailsColor(iRowIndex);
		break;
		case "TABLE_SAILS_GERALD":
			int geraldTableColNum = 4;
			int currentGeraldIdx = sti(SC_State.Current.sailGerald.Idx);
			int newGeraldIdx = iRowIndex * geraldTableColNum + (iColIndex - 1);
			if (newGeraldIdx >= sti(SC_State.Interface.Gerald.PicturesCount)) {
				return;
			}
			DeleteAttribute(&GameInterface, _tableName + ".tr" + ((currentGeraldIdx / geraldTableColNum) + 1) + ".td" + ((currentGeraldIdx % geraldTableColNum) + 1) + ".icon2");
			
			_trAttr = "tr" + (iRowIndex + 1);
			_tdAttr = "td" + iColIndex;
			GameInterface.(_tableName).(_trAttr).(_tdAttr).icon2.group = "usedflag";
			GameInterface.(_tableName).(_trAttr).(_tdAttr).icon2.image = "usedflag";
			GameInterface.(_tableName).(_trAttr).(_tdAttr).icon2.width = 60;
			GameInterface.(_tableName).(_trAttr).(_tdAttr).icon2.height = 60;
			GameInterface.(_tableName).(_trAttr).(_tdAttr).icon2.offset = "-6,-6";
			Table_UpdateWindow(_tableName);
			
			SetSailGerald(newGeraldIdx);
		break;
		case "TABLE_HULL_COLOR":
			int currentHullRow = sti(SC_State.Current.HullIdx);
			DeleteAttribute(&GameInterface, _tableName + ".tr" + currentHullRow + ".td1.icon2");
			
			_trAttr = "tr" + (iRowIndex + 1);
			GameInterface.(_tableName).(_trAttr).td1.icon2.group = "usedflag";
			GameInterface.(_tableName).(_trAttr).td1.icon2.image = "usedflag";
			GameInterface.(_tableName).(_trAttr).td1.icon2.width = 60;
			GameInterface.(_tableName).(_trAttr).td1.icon2.height = 60;
			GameInterface.(_tableName).(_trAttr).td1.icon2.offset = "-12,-12";
			Table_UpdateWindow(_tableName);
		
			SetHullColor(iRowIndex + 1);
		break;
	}
}

void ClearSailsMaterialAttention() {
	bShowMaterialAttention = false;
	SetFormatedText("SAILS_MATERIAL_ATTENTION_TITLE", "");
	SetFormatedText("SAILS_MATERIAL_ATTENTION", "");
	SetNodeUsing("SAILS_MATERIAL_ATTENTION", false);
	SetNodeUsing("SAILS_MATERIAL_ATTENTION_FRAME", false);
	SetNodeUsing("SAILS_MATERIAL_ATTENTION_TITLE", false);
}

void SetSailsMaterialAttention(string title, string text) {
	bShowMaterialAttention = true;
	SetFormatedText("SAILS_MATERIAL_ATTENTION_TITLE", title);
	SetFormatedText("SAILS_MATERIAL_ATTENTION", text);
	SetNodeUsing("SAILS_MATERIAL_ATTENTION", true);
	SetNodeUsing("SAILS_MATERIAL_ATTENTION_FRAME", true);
	SetNodeUsing("SAILS_MATERIAL_ATTENTION_TITLE", true);
}

void setLighting() {
	if (!IsEntity(&Weather) || !CheckAttribute(&Weather, "Sun")) return;

	int scolor = argb(255,255,255,250);
    int sambient = argb(255,120,120,120);

	whrBckpColor = sti(Weather.Sun.Color);
	whrBckpAmbient = sti(Weather.Sun.Ambient);
	whrBckpFogEnable = sti(Weather.Fog.Enable);
	
	Weather.Sun.Color = scolor;
	Weather.Sun.Ambient = sambient;
	Weather.Fog.Enable = true;
	
	Weather.isDone = "";
}

void resetWeather() {
	Sky.Angle = 0.0;
	
	resetLighting();
	
	WhrCreateSeaEnvironment();
	Sea.Fog.Enable = sti(Weather.Fog.Enable);
	Sea.Fog.SeaDensity = weather.Fog.SeaDensity;
	Sea.Fog.Density = weather.Fog.Density;
	Sea.isDone = "";
}

void resetLighting() {
	if (whrBckpColor == 0 || whrBckpAmbient == 0) return;

	Weather.Sun.Color = whrBckpColor;
	Weather.Sun.Ambient = whrBckpAmbient;
	Weather.Fog.Enable = whrBckpFogEnable;

	Weather.isDone = "";
}

void emptyModelViewer() {
	SendMessage(&fake_flag, "li", MSG_FLAG_DEL_GROUP, &real_ship_model);
	SendMessage(&fake_vantZ, "li", MSG_VANT_DEL_GROUP, &real_ship_model);
	SendMessage(&fake_vantL, "li", MSG_VANT_DEL_GROUP, &real_ship_model);
	SendMessage(&fake_vant, "li", MSG_VANT_DEL_GROUP, &real_ship_model);
    SendMessage(&fake_sail, "li", MSG_SAIL_DEL_GROUP, &fake_ship);
	SendMessage(&fake_rope, "li", MSG_ROPE_DEL_GROUP, &real_ship_model);
	
	// if(CheckAttribute(chref, "ship")) DeleteClass(chref);
	if(CheckAttribute(_real_ship, "ship")) DeleteClass(&_real_ship);
	
	// if (IsEntity(&fake_flag))
    	// DeleteClass(&fake_flag);
	if (IsEntity(&seafoam_obj))
    	DeleteClass(&seafoam_obj);
	if (IsEntity(&shipTrack_obj))
    	DeleteClass(&shipTrack_obj);
	if (IsEntity(&real_ship_model))
    	DeleteClass(&real_ship_model);
	if (IsEntity(&fake_ship))
    	DeleteClass(&fake_ship);
}

bool InitEntitiesForShipMV() {
	if (!FindEntity(&fake_sail, "sail")) {
		Log_Info("Sail not found!");
		Trace("Sail not found!");
		return false;
	}
	if (!FindEntity(&fake_rope, "rope")) {
		Log_Info("Rope not found!");
		Trace("Rope not found!");
		return false;
	}
	if (!FindEntity(&fake_flag, "flag")) {
		Log_Info("flag not found!");
		Trace("flag not found!");
		return false;
	}
	if (!FindEntity(&fake_vant, "vant")) {
		Log_Info("Vant not found!");
		Trace("Vant not found!");
		return false;
	}
	if (!FindEntity(&fake_vantL, "vantl")) {
		Log_Info("VAntL not found!");
		Trace("VAntL not found!");
		return false;
	}
	if (!FindEntity(&fake_vantZ, "vantz")) {
		Log_Info("VantZ not found!");
		Trace("VantZ not found!");
		return false;
	}
	
	if (!IsEntity(&fake_ship)) {
    	CreateEntity(&fake_ship, "ship");
	}
	
	// if (!IsEntity(&fake_flag)) {
		// CreateEntity(&fake_flag, "flag");
	// }	
	if (!IsEntity(&Sea)) {
		CreateEntity(&Sea, "sea");
	}
	
	return true;
}

void SetSeaWeatherSettings_Simple()
{
	bSeaActive = true;
	
	WhrCreateSeaEnvironment();
	
	Sea.Fog.Enable = true;
	Sea.Fog.Start = 25;
	Sea.Fog.Density = 0.02;
	Sea.Fog.SeaDensity = 0.0025;
	
	if (stf(Weather.Wind.Speed) > 12.0) {
		Sea.MaxSeaHeight = 10.0;
	}
	bSeaActive = false;
	
	Sea.isDone = "";
}

void resolveModelViewerShip(ref shipRef, int hullID) {
	if (!InitEntitiesForShipMV()) {
		emptyModelViewer();
		return;
	}
	
	string shipName = shipRef.name;
	
	SetTextureForShip(shipRef, chref);
//	SetTexturePath(0, "Ships/"+shipName+"/Hull"+hullID+"/");
	
	if (!IsEntity(&real_ship_model))
    	CreateEntity(&real_ship_model, "modelr");
	
	if (!IsEntity(&shipTrack_obj)) {
		CreateEntity(&shipTrack_obj, "ShipTracks");
		SendMessage(&shipTrack_obj,"li",MSG_SHIP_INIT_FOR_MV,&Sea);
	}
	
	
    if(IsEntity(&real_ship_model)) {
        SendMessage(&real_ship_model, "ls", MSG_MODEL_LOAD_GEO, "Ships/"+shipName+"/"+shipName);
		
		Ship_SetTrackSettings(chref);
		SendMessage(&fake_ship,"laaiii",MSG_SHIP_INIT_FOR_MV,chref,shipRef,&real_ship_model,&Sea,&shipTrack_obj);
		
		SendMessage(&fake_sail, "liil", MSG_SAIL_INIT, &fake_ship, &real_ship_model, 1);
		SendMessage(&fake_rope, "lii", MSG_ROPE_INIT, &fake_ship, &real_ship_model);
		SendMessage(&fake_vant, "lii", MSG_VANT_INIT, &fake_ship, &real_ship_model);
		SendMessage(&fake_vantL, "lii", MSG_VANT_INIT, &fake_ship, &real_ship_model);
		SendMessage(&fake_vantZ, "lii", MSG_VANT_INIT, &fake_ship, &real_ship_model);
		SendMessage(&fake_flag, "lili", MSG_FLAG_INIT, &real_ship_model, sti(pchar.nation), &fake_ship);
		
		// add ship rigging to scene
		SendMessage(&GameInterface, "lsliiiiii", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 2, &fake_rope, &fake_sail,&fake_flag, &fake_vant, &fake_vantL, &fake_vantZ);
		// add SHIP to scene (or MODELR, see XI_MODELVIEWER node in engine src)
		SendMessage(&GameInterface, "lslsi", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 0, "ship", &fake_ship);
		
		float minCamDistCoef = 0.3;
		float maxCamDistCoef = 1.7;
		float turnAngle = -PI/8;
		float camZoomCoef = 8.0;
		
		if (!IsEntity(&seafoam_obj)) {
			CreateEntity(&seafoam_obj,"Seafoam");
		}
		SendMessage(&seafoam_obj,"li",MSG_SHIP_INIT_FOR_MV,&Sea);
		
		if (!bIsInit) {
			// camera settings (need for start drawing)
			SendMessage(&GameInterface, "lslfffffffff", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 1,
				/*чуствительность по горизонтали*/ 1.0,
				/*чуствительность по вертикали*/ 0.25,
				/*угол поворота камеры относительно объекта. Для корабля: 0.0 - смотрим на нос, PI/2 - смотрим на правый борт под 90гр*/ turnAngle,
				/*максимальный угол возвышения по вертикали*/ PI / 3,
				/*текущий угол возвышения по вертикали*/ PI / 36,
				/*множитель минимальной дистанции*/ minCamDistCoef,
				/*множитель максимальной дистанции*/ maxCamDistCoef,
				/*множитель шага зума*/ camZoomCoef,
				/*смещение модельки относительно камеры (0.0 - центр, +t - вправо, -t - влево,)*/ curTranslationCoef);
			
			//Set SeaWeatherSettings
			SetSeaWeatherSettings_Simple();
			// изменяемая центровка камеры
			SendMessage(&GameInterface, "lslsf", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 4, "v_translate", SC_v_translateCoef);
			
			bIsInit = true;
		}
		
		// Add sea to scene (and sky)
		SendMessage(&GameInterface, "lsliiii", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 3, &Sea, &Sky, &seafoam_obj, &shipTrack_obj);
		// установка скорости кораблю
		SendMessage(&GameInterface, "lslsf", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 5, "setShipSpeed", SC_zShipSpeed);
    }
}


float newTranslateCoef;
float oldTranslateCoef;
float translateAnimTimeSeconds = 0.33;
void SetMV_Camera_ToLeft_Smooth() {
	newTranslateCoef = 0.17;
	oldTranslateCoef = curTranslationCoef;
	translationCamTimer = 0.0;
	
	SetEventHandler("frame", "ProcessCameraTranslation",0);
}

void SetMV_Camera_ToCenter_Smooth() {
	newTranslateCoef = 0.0;
	oldTranslateCoef = curTranslationCoef;
	translationCamTimer = 0.0;
	
	SetEventHandler("frame", "ProcessCameraTranslation",0);
}

void SetMV_Camera_SetTranslation(float translateCoef) {
	curTranslationCoef = translateCoef;
	
	SendMessage(&GameInterface, "lslsf", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 4, "translate", curTranslationCoef);
}

void ProcessCameraTranslation() {
	float dt = makefloat(GetDeltaTime()) * 0.001;
	translationCamTimer += dt;

	SetMV_Camera_SetTranslation(EaseInOut(oldTranslateCoef, newTranslateCoef, translationCamTimer / translateAnimTimeSeconds));
	
	if (translationCamTimer > translateAnimTimeSeconds) {
		DelEventHandler("frame", "ProcessCameraTranslation");
		translationCamTimer = 0.0;
	}
}

// UTILS
float EaseInOut(float a, float b, float t)
{
    if (t <= 0.0)
        return a;
    else if (t >= 1.0)
        return b;

    return a + (b - a) * t * t * (3.0 - 2.0 * t);
}

void ProcessBreakExit()
{
	CancelAllShipChanges();
	ProcessExit();
}

void ProcessCancelExit()
{
	if (currentWindow == SC_DIALOG_WINDOW) {
		CloseDialogWindow();
		return;
	}

	if (currentWindow == SC_PHOTOMODE_WINDOW)
	{
		if (bSC_HidePhotoModeControls)
		{
			SC_PhotoMode_ShowControls(!bSC_HidePhotoModeControls);
		}
		else
		{
		    SetPhotoMode(false);
		}
		return;
	}

	if (currentWindow != SC_DEFAULT_WINDOW) {
		HandleActivateCloseCurrentChangeButton();
		return;
	}

	CancelAllShipChanges();
	ProcessExit();
}

void ProcessExit()
{
	resetWeather();
	SetTexturePath(0, "");

	DelEventHandlers();
	emptyModelViewer();
	// DeleteClass(&sea_obj);
	
	interfaceResultCommand = RC_INTERFACE_SALARY_EXIT;
	EndCancelInterface(true);
    PostEvent("StopQuestCheckProcessFreeze", 100); // отмена заморозки проверки квестов
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch(nodName)
	{
    	case "EXIT_BTN":
    		if(comName=="activate" || comName=="click")
    		{
				ProcessBreakExit();
    		}
    	break;
    	case "BUTTON_BUY":
    		if(comName=="activate" || comName=="click")
    		{
				ShowDialogWindow();
    		}
    	break;
    	case "REMOVE_GERALD_BTN":
    		if(comName=="activate" || comName=="click")
    		{
                RemoveSailGerald();	
    		}
    	break;
		case "DISCARD_BTN":
    		if(comName=="activate" || comName=="click")
    		{
				HandleActivateDiscardButton();
    		}
    	break;
		case "DISCARD_ALL_BTN":
    		if(comName=="activate" || comName=="click")
    		{
				HandleActivateDiscardAllButton();
    		}
    	break;
		case "CLOSE_CURRENT_CHANGE_BUTTON":
    		if(comName=="activate" || comName=="click")
    		{
				HandleActivateCloseCurrentChangeButton();
    		}
    	break;
		case "DIALOG_OK_BUTTON":
    		if(comName=="activate" || comName=="click")
    		{
				ApplyShipChanges();
    		}
    	break;
		case "DIALOG_CANCEL_BUTTON":
    		if(comName=="activate" || comName=="click")
    		{
				CloseDialogWindow();
    		}
    	break;
		case "DIALOG_EXIT_BUTTON":
    		if(comName=="activate" || comName=="click")
    		{
				CloseDialogWindow();
    		}
    	break;
		case "MODEL_VIEWER_TEST":
		 if(comName=="upstep" || comName=="speedup")
			{
				SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 4, "zoom_in");
			}
		 else if (comName=="downstep" || comName=="speeddown")
			{
				SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 4, "zoom_out");
			}
		break;
		// Debug Photo mode
		case "PHOTO_MODE_BUTTON":
			if(comName=="activate" || comName=="click")
    		{
				SetPhotoMode(!bSC_SetPhotoMode);
    		}
		break;
//		case "PHOTO_MODE_HIDE_INTERFACE_BUTTON":
//			SC_PhotoMode_ShowControls(!bSC_HidePhotoModeControls);
//		break;
		case "PHOTO_MODE_INC_V_COEF_BUTTON":
			if(comName=="activate" || comName=="click")
    		{
				SC_IncreaseVTransCoef(0.01);
				SendMessage(&GameInterface, "lslsf", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 4, "v_translate", SC_v_translateCoef);
				GameInterface.PHOTO_MODE_V_COEF_EDIT.str = FloatToString(SC_v_translateCoef, 3);
			}
		break;
		case "PHOTO_MODE_DEC_V_COEF_BUTTON":
			if(comName=="activate" || comName=="click")
    		{
				SC_IncreaseVTransCoef(-0.01);
				SendMessage(&GameInterface, "lslsf", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 4, "v_translate", SC_v_translateCoef);
				GameInterface.PHOTO_MODE_V_COEF_EDIT.str = FloatToString(SC_v_translateCoef, 3);
			}
		break;
		case "PHOTO_MODE_INC_GRID_POS_BUTTON":
			if(comName=="activate" || comName=="click")
    		{
				SC_IncreasePhotoGridPos(0.01);
				GameInterface.PHOTO_MODE_GRID_POS_EDIT.str = FloatToString(SC_PhotoModeGridPos, 3);
			}
		break;
		case "PHOTO_MODE_DEC_GRID_POS_BUTTON":
			if(comName=="activate" || comName=="click")
    		{
				SC_IncreasePhotoGridPos(-0.01);
				GameInterface.PHOTO_MODE_GRID_POS_EDIT.str = FloatToString(SC_PhotoModeGridPos, 3);
			}
		break;
	}
}

void ProcessInterfaceControls()
{
    string sCurNode = GetCurrentNode();
	string controlName = GetEventData();

	if (controlName == "SC_InterfaceHide")
	{
		if (currentWindow != SC_PHOTOMODE_WINDOW)
			return;

		SC_PhotoMode_ShowControls(!bSC_HidePhotoModeControls);
	}
}

void confirmChange_V_COEF_EDIT()
{
	SC_SetVTransCoef(stf(GameInterface.PHOTO_MODE_V_COEF_EDIT.str));
	SendMessage(&GameInterface, "lslsf", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 4, "v_translate", SC_v_translateCoef);
	GameInterface.PHOTO_MODE_V_COEF_EDIT.str = FloatToString(SC_v_translateCoef, 3);
}

void confirmChange_GRID_POS_EDIT()
{
	SC_SetPhotoGridPos(stf(GameInterface.PHOTO_MODE_GRID_POS_EDIT.str));
	GameInterface.PHOTO_MODE_GRID_POS_EDIT.str = FloatToString(SC_PhotoModeGridPos, 3);
}

void procTabChange()
{
	string sNodName = GetEventData();
	int iRowIndex = GetEventData();
	int iColIndex = GetEventData();
	
	if (sNodName == "TABLE_CHANGES") {
		ShowWindowByTabMode(iRowIndex);
	}
}

void HandleActivateDiscardButton() {
	switch(currentWindow) {
		case SC_SAILS_COLOR_WINDOW:
			DiscardSailColor();
		break;
		case SC_SAILS_MATERIAL_WINDOW:
			DiscardSailMaterial();
		break;
		case SC_SAILS_GERALD_WINDOW:
			DiscardSailGerald();
		break;
		case SC_HULL_COLOR_WINDOW:
			DiscardHullColor();
		break;
	}
}

void HandleActivateDiscardAllButton() {
	DiscardSailColor();
	DiscardSailMaterial();
	DiscardSailGerald();
	DiscardHullColor();
}

void HandleActivateCloseCurrentChangeButton() {
	HideAllWindows();
	currentWindow = SC_DEFAULT_WINDOW;
	SetMV_Camera_ToCenter_Smooth();
	SetNodeUsing("CLOSE_CURRENT_CHANGE_BUTTON", false);
	SetNodeUsing("CURRENT_CHANGE_FRAME", false);
	SetCurrentNode("MODEL_VIEWER_TEST");
}

void ShowDialogWindow() {
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowDisable("BACK_WINDOW", true);
	XI_WindowDisable("SAILS_GERALD_WINDOW", true);
	XI_WindowDisable("SAILS_COLOR_WINDOW", true);
	XI_WindowDisable("SAILS_MATERIAL_WINDOW", true);
	XI_WindowDisable("HULL_COLOR_WINDOW", true);
	
	XI_WindowDisable("DIALOG_WINDOW", false);
	XI_WindowShow("DIALOG_WINDOW", true);
	bckupCurrentWindow = currentWindow;
	currentWindow = SC_DIALOG_WINDOW;
	
	SetFormatedText("DIALOG_TEXT", XI_ConvertString("SC_BuyText") + "\n" + FindMoneyString(GetPriceSummary()) + "?");
	SetCurrentNode("DIALOG_CANCEL_BUTTON");
}

void CloseDialogWindow() {
	XI_WindowDisable("DIALOG_WINDOW", true);
	XI_WindowShow("DIALOG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowDisable("BACK_WINDOW", false);
	
	currentWindow = bckupCurrentWindow;
	
	switch(currentWindow) {
		case SC_SAILS_COLOR_WINDOW:
			XI_WindowDisable("SAILS_COLOR_WINDOW", false);
		break;
		case SC_SAILS_MATERIAL_WINDOW:
			XI_WindowDisable("SAILS_MATERIAL_WINDOW", false);
		break;
		case SC_SAILS_GERALD_WINDOW:
			XI_WindowDisable("SAILS_GERALD_WINDOW", false);
		break;
		case SC_HULL_COLOR_WINDOW:
			XI_WindowDisable("HULL_COLOR_WINDOW", false);
		break;
	}
}

void UpdateModelViewerShip() {
	emptyModelViewer();
	resolveModelViewerShip(_real_ship, sti(SC_State.Current.HullIdx));
}

// > Смена окраса корпуса меняет только текстуры, геометрия модели же остаётся прежней, поэтому не перезагружаем весь корабль, а лишь обновляем его текстуры.
void UpdateModelViewerShipHullTexture() {
	if (!IsEntity(&real_ship_model)) {
		// > модель ещё не создана, грузим всё полностью
		UpdateModelViewerShip();
		return;
	}

	SetTextureForShip(_real_ship, chref);
	SendMessage(&real_ship_model, "l", MSG_MODEL_RELOAD_TEXTURES);
}

// > То же самое и для смены цвета/материала парусов и герба - при изменении обновляем только текстуры.
void UpdateModelViewerShipSailTexture() {
	if (!IsEntity(&fake_sail) || !IsEntity(&fake_ship)) {
		// > паруса ещё не созданы, грузим всё полностью
		UpdateModelViewerShip();
		return;
	}

	SendMessage(&fake_sail, "li", MSG_SAIL_RELOAD_TEXTURES, &fake_ship);
}

string GetHullTypesDesc(int hullTypeIdx) {
	return XI_ConvertString("SC_HullDesc" + hullTypeIdx);
}

void SetHullColor(int nIdx) {
	if (CheckAttribute(&SC_State, "HullChangeNotAvailable"))
		return;
	if (nIdx < HULL_TYPE_MIN || nIdx > iHulls)
		return;
	
	if (sti(SC_State.Current.HullIdx) == nIdx)
		return;
	
	SC_State.Current.HullIdx = nIdx;
	_real_ship.ship.upgrades.hull = nIdx;
	
	if (nIdx == sti(SC_State.Initials.HullIdx)) {
		RemoveHullColorPriceToChanges();
	} else {
		AddHullColorPriceToChanges();
	}

	// > обновляем только текстуры
	UpdateModelViewerShipHullTexture();
}

void SetSailColor(int nIdx)
{
	if (nIdx < 0 || nIdx > SAILS_COLOR_QUANTITY - 1)
		return;
	int curColor = nIdx;
	if (sti(SC_State.Current.sailColor) == curColor)
		return;
	
	SC_State.Current.sailColor = curColor;
	
	if (curColor == sti(SC_State.Initials.sailColor)) {
		RemoveSailColorPriceToChanges();
	} else {
		AddSailColorPriceToChanges();
	}
	
	_real_ship.ShipSails.SailsColor = SailsColors[curColor].color;
	_real_ship.SailsColorIdx = curColor;

	// > обновляем только текстуры
	UpdateModelViewerShipSailTexture();
}

void SetSailMaterialTextureForTableSailsColor(int materialIdx) {
	string _tableName = "TABLE_SAILS_COLOR";
	
	string trAttr =  "tr" + (materialIdx + 1);
	string _sailTexFileName = GameInterface.TABLE_SAILS_MATERIAL.(trAttr).td1.icon1.texture;
	
	int colorsCount = GetArraySize(&SailsColors);
	for (int i = 0; i < colorsCount; i++) {
		string _trAttr = "tr" + (i + 1);
		GameInterface.(_tableName).(_trAttr).td1.icon1.texture = _sailTexFileName;
	}

	Table_UpdateWindow(_tableName);
}

void SetSailMaterial(int materialIdx) {
	if (sti(SC_State.Current.sailMaterial.Idx) == materialIdx) {
		return;
	}
	
	int sailUpgradeIdx = materialIdx + 1;
	SC_State.Current.sailMaterial.Idx = materialIdx;
	
	string sailTexFileName = GetSailTextureFilenameFromIdx(materialIdx);
	if (sailTexFileName == "") {
		if (sailUpgradeIdx < SAIL_UPGRADE_COMMON || sailUpgradeIdx > SAIL_UPGRADE_SILK) {
			Trace("Cannot set sail upgrade with incorrect number: " + sailUpgradeIdx);
			Log_Info("Cannot set sail upgrade with incorrect number: " + sailUpgradeIdx);
			return;
		}
		DeleteAttribute(_real_ship, "EmblemedSails.normalTex");
		_real_ship.Ship.upgrades.sails = sailUpgradeIdx;
	} else {
		_real_ship.Ship.upgrades.sails = SAIL_UPGRADE_COMMON;
		_real_ship.EmblemedSails.normalTex = sailTexFileName;
	}
	
	if (sti(SC_State.Initials.sailMaterial.Idx) == materialIdx) {
		RemoveSailMaterialPriceToChanges();
	} else {
		AddSailMaterialPriceToChanges();
	}

	// > обновляем только текстуры
	UpdateModelViewerShipSailTexture();
}

string GetSailTextureFilenameFromIdx(int materialIdx) {
	if (materialIdx < 3)
		return "";
	
	string trAttr = "tr" + (materialIdx + 1);
	
	return GameInterface.TABLE_SAILS_MATERIAL.(trAttr).td1.icon1.texture;
}

void SetSailGerald(int geraldIdx) {
	if (geraldIdx == sti(SC_State.Current.sailGerald.Idx))
		return;
	
	SC_State.Current.sailGerald.Idx = geraldIdx;
	if (geraldIdx == 0) {
		DeleteAttribute(&_real_ship, "ShipSails.Gerald_Name");
	} else {
		_real_ship.ShipSails.Gerald_Name = GetGeraldTextureFilenameFromIdx(geraldIdx);
	}
	
	if (geraldIdx == sti(SC_State.Initials.sailGerald.Idx))
		RemoveSailGeraldPriceToChanges();
	else
		AddSailGeraldPriceToChanges();

	// > обновляем только текстуры
	UpdateModelViewerShipSailTexture();
}

string GetGeraldTextureFilenameFromIdx(int geraldIdx) {
	if (geraldIdx <= 0)
		return "";
	
	string sAttrNum = its(geraldIdx);
	
	return SC_State.Interface.Gerald.Pictures.(sAttrNum).FileName;
}

void CancelAllShipChanges() {
	// Hull
	if (!CheckAttribute(&SC_State, "HullChangeNotAvailable")) {
		_real_ship.ship.upgrades.hull = SC_State.Initials.HullIdx;
	}
	
	// Sail material
	_real_ship.Ship.upgrades.sails = SC_State.Initials.sailMaterial.upgrade;
	if (CheckAttribute(&SC_State, "Initials.sailMaterial.tex.fileName") && SC_State.Initials.sailMaterial.tex.fileName != "") {
		_real_ship.EmblemedSails.normalTex = SC_State.Initials.sailMaterial.tex.fileName;
	} else {
		DeleteAttribute(_real_ship, "EmblemedSails.normalTex");
	}
	
	// Sail color
	_real_ship.SailsColorIdx = SC_State.Initials.sailColor;
	_real_ship.ShipSails.SailsColor = SailsColors[sti(SC_State.Initials.sailColor)].color;
	
	// Sail gerald
	if (CheckAttribute(&SC_State, "Initials.sailGeraldName")) {
		_real_ship.ShipSails.Gerald_Name = SC_State.Initials.sailGeraldName;
	} else {
		DeleteAttribute(_real_ship, "ShipSails.Gerald_Name");
	}
}

int GetPriceSummary() {
	if (!CheckAttribute(&SC_State, "Price"))
		return 0;
	aref pricesAref; makearef(pricesAref, SC_State.Price);
	int priceAttrsNum = GetAttributesNum(pricesAref);
	int priceSummary = 0;
	
	for (int i=0; i < priceAttrsNum; i++) {
		aref resAr = GetAttributeN(pricesAref, i);
		priceSummary += sti(GetAttributeValue(resAr));
	}
	
	return priceSummary;
}

void ApplyShipChanges() {
	int price = GetPriceSummary();
	AddMoneyToCharacter(Pchar, -price);
	WaitDate("",0,0,0, 1, 30);
	ProcessExit();
	Achievment_Set(ACH_Kapitan_estet);
}

void DiscardSailColor() {
	Event("onTableClick", "sll", "TABLE_SAILS_COLOR", sti(SC_State.Initials.sailColor), 1);
	GameInterface.TABLE_SAILS_COLOR.select = sti(SC_State.Initials.sailColor) + 1;
}

void DiscardSailMaterial() {
	int newRow = sti(SC_State.Initials.sailMaterial.Idx) + 1;
	Event("onTableClick", "sll", "TABLE_SAILS_MATERIAL", newRow - 1, 1);
	GameInterface.TABLE_SAILS_MATERIAL.select = newRow;
	Table_UpdateWindow("TABLE_SAILS_MATERIAL");
}

void RemoveSailGerald() {
	Event("onTableClick", "sll", "TABLE_SAILS_GERALD", 0, 1);
	GameInterface.TABLE_SAILS_GERALD.select = 1;
	Table_UpdateWindow("TABLE_SAILS_GERALD");
}

void DiscardSailGerald() {
	int newRow = sti(SC_State.Initials.sailGerald.Idx) / 4;
	int newCol = sti(SC_State.Initials.sailGerald.Idx) % 4 + 1;
	Event("onTableClick", "sll", "TABLE_SAILS_GERALD", newRow, newCol);
	GameInterface.TABLE_SAILS_GERALD.select = newRow + 1;
	Table_UpdateWindow("TABLE_SAILS_GERALD");
}

void DiscardHullColor() {
	if (CheckAttribute(&SC_State, "HullChangeNotAvailable"))
		return;
	
	int initialHullTypeIdx = sti(SC_State.Initials.HullIdx);
	Event("onTableClick", "sll", "TABLE_HULL_COLOR", (initialHullTypeIdx - 1), 1);
	GameInterface.TABLE_HULL_COLOR.select = initialHullTypeIdx;
	Table_UpdateWindow("TABLE_HULL_COLOR");
}

void AddSailColorPriceToChanges() {
	SC_State.Price.SailColor = GetSailsTuningPrice(_ownerChRef, _shipyarderRef, SAILSCOLOR_PRICE_RATE);
	FillPricesTable();
}

void RemoveSailColorPriceToChanges() {
	DeleteAttribute(&SC_State, "Price.SailColor");
	FillPricesTable();
}

void AddSailGeraldPriceToChanges() {
	SC_State.Price.Gerald = GetSailsTuningPrice(_ownerChRef, _shipyarderRef, SAILSGERALD_PRICE_RATE);
	FillPricesTable();
}

void RemoveSailGeraldPriceToChanges() {
	DeleteAttribute(&SC_State, "Price.Gerald");
	FillPricesTable();
}

void AddHullColorPriceToChanges() {
	SC_State.Price.HullColor = GetHullTypePrice(stf(_shipyarderRef.ShipCostRate), sti(_real_ship.Price));
	FillPricesTable();
}

void RemoveHullColorPriceToChanges() {
	DeleteAttribute(&SC_State, "Price.HullColor");
	FillPricesTable();
}

void AddSailMaterialPriceToChanges() {
	int dutchmanSailsIdx = SAIL_MATERIAL_FD - 1;
	if (sti(SC_State.Initials.sailMaterial.Idx) == dutchmanSailsIdx || sti(SC_State.Current.sailMaterial.Idx) == dutchmanSailsIdx) {
		SC_State.Price.SailMaterial = GetDutchmanSailsPrice();
	} else {
		SC_State.Price.SailMaterial = GetSailsTypePrice(sti(SC_State.Initials.sailMaterial.Upgrade),
									  sti(_real_ship.Ship.upgrades.sails),
									  stf(_shipyarderRef.ShipCostRate),
									  sti(_real_ship.Price));
	}
	FillPricesTable();
}

void RemoveSailMaterialPriceToChanges() {
	DeleteAttribute(&SC_State, "Price.SailMaterial");
	FillPricesTable();
}

bool CheckFlyingDutchmanSailAvailable() {
	return CheckAttribute(&SC_State, "ShipClass") && sti(SC_State.ShipClass) < 4;
}

int GetDutchmanSailsPrice() {
	return (10 / sti(SC_State.ShipClass)) * sti(SC_State.MainCharRank) * MOD_SKILL_ENEMY_RATE * 10;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price) {
	int ret;
	ret = _tobe - _asis;
	
	if (ret < 0) ret = 0;
	
	return makeint((ret*_price*0.05 + _price*0.05)*_shipCostRate / 10) * 10;
}

int GetHullTypePrice(float _shipCostRate, int _price) {
	return makeint((_price * 0.05 + _price * 0.05) * _shipCostRate/4) * 10;
}

bool CheckSailsGerald(ref chr)
{
    int    st = GetCharacterShipType(chr);
	ref    shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))  return true;
	}
	return false;
}

// ================ DEBUG PHOTO MODE ================

void SetPhotoMode(bool isSet) {
	bSC_SetPhotoMode = isSet;
	
	if (isSet) {
		SendMessage(&GameInterface, "lslsl", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 5, "useSailRotation", 1);
		SendMessage(&GameInterface, "lslsl", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 5, "enableFlags", 0);
		SC_ShowPhotoModeInterface();
	} else {
		SendMessage(&GameInterface, "lslsl", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 5, "useSailRotation", 0);
		SendMessage(&GameInterface, "lslsl", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 5, "enableFlags", 1);
		SC_HidePhotoModeInterface();
	}
}

void SC_ShowPhotoModeInterface()
{
	HandleActivateCloseCurrentChangeButton();
	
	XI_WindowDisable("MAIN_WINDOW", true);
	XI_WindowShow("MAIN_WINDOW", false);
	
	XI_WindowDisable("PHOTO_MODE_WINDOW", false);
	XI_WindowShow("PHOTO_MODE_WINDOW", true);
	
//	SetNodeUsing("PHOTO_MODE_HIDE_INTERFACE_BUTTON", true);

	bSC_HidePhotoModeControls = false;

	currentWindow = SC_PHOTOMODE_WINDOW;
}

void SC_HidePhotoModeInterface()
{
	bSC_HidePhotoModeControls = false;
	
	XI_WindowDisable("MAIN_WINDOW", false);
	XI_WindowShow("MAIN_WINDOW", true);
	
	XI_WindowDisable("PHOTO_MODE_WINDOW", true);
	XI_WindowShow("PHOTO_MODE_WINDOW", false);
	
//	SetNodeUsing("PHOTO_MODE_HIDE_INTERFACE_BUTTON", false);
	
	HandleActivateCloseCurrentChangeButton();

	currentWindow = SC_DEFAULT_WINDOW;
}

void SC_PhotoMode_ShowControls(bool isHide)
{
	bSC_HidePhotoModeControls = isHide;
	XI_WindowDisable("PHOTO_MODE_WINDOW", bSC_HidePhotoModeControls);
	XI_WindowShow("PHOTO_MODE_WINDOW", !bSC_HidePhotoModeControls);

	SetNodeUsing("EXIT_BTN", !bSC_HidePhotoModeControls);
	SetNodeUsing("PHOTO_MODE_BUTTON", !bSC_HidePhotoModeControls);

	SetCurrentNode("MODEL_VIEWER_TEST");
}

void FillExtraSettingsTable()
{
	string _tableName = "EXT_SETTINGS_TABLE";
	GameInterface.(_tableName).hr.td1.str = XI_ConvertString("SC_ExtraSettings");
	GameInterface.(_tableName).tr1.td1.str = XI_ConvertString("SC_ExtSet_ShipSpeed");
	GameInterface.(_tableName).tr2.td1.str = XI_ConvertString("SC_ExtSet_ShipImmersion");
	GameInterface.(_tableName).tr3.td1.str = XI_ConvertString("SC_ExtSet_WindDirection");
	GameInterface.(_tableName).tr4.td1.str = XI_ConvertString("SC_ExtSet_SkyTurning");
	GameInterface.(_tableName).tr5.td1.str = XI_ConvertString("SC_ExtSet_CameraCentering");
	GameInterface.(_tableName).tr6.td1.str = XI_ConvertString("SC_ExtSet_GuidingLinePosition");
	
	Table_UpdateWindow(_tableName);
}

void procSlideChange()
{
	string sNodeName = GetEventData();
	int nVal = GetEventData();
	float fVal = GetEventData();

	if (sNodeName == "PHOTO_MODE_SHIP_SPEED_SLIDE") 
	{
		SC_HandleShipSpeedSlider(fVal);
		return;
	}
	if (sNodeName == "PHOTO_MODE_SHIP_IMMERSION_SLIDE") 
	{
		SC_HandleShipImmersionSlider(fVal);
		return;
	}
	if (sNodeName == "PHOTO_MODE_WIND_ANGLE_SLIDE") 
	{
		SC_HandleWindAngleSlider(fVal);
		return;
	}
	if (sNodeName == "PHOTO_MODE_SKY_ANGLE_SLIDE") 
	{
		SC_HandleSkyAngleSlider(fVal);
		return;
	}
}

void SC_HandleShipSpeedSlider(float fValueArg)
{
	float fCalculatedZShipSpeed = fValueArg * 20.0;
	SC_SetZShipSpeed(fCalculatedZShipSpeed);
	string sMsg = "#"+ FloatToString(fCalculatedZShipSpeed, 3);
}

void SC_HandleShipImmersionSlider(float fValueArg)
{
	float fCalculatedImmersion = fValueArg;
	SC_SetShipLoad(fCalculatedImmersion);
	string sMsg = "#"+ FloatToString(fCalculatedImmersion, 3);
}

void SC_HandleWindAngleSlider(float fValueArg)
{
    float fValue = (fValueArg - 0.5) * 2.0;
	float fCalculatedWindAngle = fValue * PId2;
	SC_SetGlobalWindAngle(fCalculatedWindAngle);
	string sMsg = "#"+ FloatToString(fCalculatedWindAngle, 3);
}

void SC_HandleSkyAngleSlider(float fValueArg)
{
    float fValue = (fValueArg - 0.5) * 2.0;
	float fCalculatedSkyAngle = fValue * PI;
	SC_SetSkyRotateAngle(fCalculatedSkyAngle);
	string sMsg = "#"+ FloatToString(fCalculatedSkyAngle, 3);
}

void SC_HandleGridSlider(float fValueArg)
{
    float fValue = fValueArg * 0.5;
	SC_SetPhotoGridPos(fValue);
}


void SC_IncreaseVTransCoef(float inc)
{
	SC_SetVTransCoef(SC_v_translateCoef + inc);
}

void SC_SetVTransCoef(float vCoef)
{
	if (vCoef < 0.0)
		vCoef = 0.0;
	if (vCoef > 1.0)
		vCoef = 1.0;
	
	SC_v_translateCoef = vCoef;
}

void SC_IncreaseGlobalWindAngle(float inc)
{
	SC_SetGlobalWindAngle(SC_GlobalWindAngle + inc);
}

void SC_SetGlobalWindAngle(float angle)
{
	Restrictor(&angle, -PId2, PId2);
	
	SC_GlobalWindAngle = angle;
	
	SendMessage(&GameInterface, "lslsf", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 5, "setGlobalWindAngle", SC_GlobalWindAngle);
}

float SC_GetGlobalWindAngleAsRangePos()
{
	float angle = SC_GlobalWindAngle;
	Restrictor(&angle, -PId2, PId2);
	
	return angle / PI + 0.5;
}

void SC_IncreaseZShipSpeed(float inc)
{
	SC_SetZShipSpeed(SC_zShipSpeed + inc);
}

void SC_SetZShipSpeed(float speed)
{
	Restrictor(&speed, 0.0, 20.0);  // knots
	
	SC_zShipSpeed = speed;
	
	SendMessage(&GameInterface, "lslsf", MSG_INTERFACE_MSG_TO_NODE, "MODEL_VIEWER_TEST", 5, "setShipSpeed", SC_zShipSpeed);
}

// уровень погружения от веса
void SC_SetShipLoad(float fLoad)
{
	Restrictor(&fLoad, 0.0, 1.0);
	
	if (CheckAttribute(_real_ship, "SubSeaDependWeight"))
	{
		chref.Ship.Immersion = (stf(_real_ship.SubSeaDependWeight) * fLoad);
	}
}

float SC_GetShipLoad()
{
	if (CheckAttribute(chref, "Ship.Immersion") && CheckAttribute(_real_ship, "SubSeaDependWeight"))
	{
		if (stf(_real_ship.SubSeaDependWeight) != 0.0)
			return stf(chref.Ship.Immersion) / stf(_real_ship.SubSeaDependWeight);
	}
	
	return 0.0;
}

void SC_IncreaseSkyRotateAngle(float inc)
{
	SC_SetSkyRotateAngle(SC_SkyRotateAngle + inc);
}

void SC_SetSkyRotateAngle(float fAng)
{
	Restrictor(&fAng, -PI, PI);
	
	SC_SkyRotateAngle = fAng;
	Sky.Angle = fAng;
}

float SC_GetSkyRotateAngleAsRangePos()
{
	float angle = SC_SkyRotateAngle;
	Restrictor(&angle, -PI, PI);
	
	return angle / PIm2 + 0.5;
}

void SC_IncreasePhotoGridPos(float inc)
{
	SC_SetPhotoGridPos(SC_PhotoModeGridPos + inc);
}

void SC_SetPhotoGridPos(float fPos)
{
	if (fPos < 0.0)
		fPos = 0.0;
	if (fPos > 0.5)
		fPos = 0.5;
	
	SC_PhotoModeGridPos = fPos;
	
	int lineHeight = 20000;
	int lineOldOffset = 5;
	int screenHeight = 600;
	
	int left = 0;
	int right = 1080;
	int top = makeint(screenHeight - fPos * makefloat(screenHeight) - lineOldOffset);
	int bottom = top + lineHeight / 2;

//	int bottom1 = makeint(fPos * makefloat(screenHeight));
//	int top1 = bottom1 - lineHeight / 2;

	SendMessage(&GameInterface,"lslllll",MSG_INTERFACE_MSG_TO_NODE,"PHOTO_MODE_GRID_RECTANGLE", 0, left,top,right,bottom);
//	SendMessage(&GameInterface,"lslllll",MSG_INTERFACE_MSG_TO_NODE,"PHOTO_MODE_GRID_RECTANGLE1", 0, left,top1,right,bottom1);
}
bool bWMEncounterCheck = false;

void InitWmInterface()
{
	DeleteAttribute(&BattleInterface,"");
	WM_InitializeCommands();
	WM_SetParameterData();

	CreateEntity(&BattleInterface,"WM_INTERFACE");
	LayerAddObject(EXECUTE,&BattleInterface,-1);
	LayerAddObject(REALIZE,&BattleInterface,-1);

	SetEventHandler("BI_CommandEndChecking","WM_CommandEndChecking",0);
	SetEventHandler("BI_LaunchCommand","WM_LaunchCommand",0);
	SetEventHandler("WM_SetPossibleCommands","WM_SetPossibleCommands",0);
	SetEventHandler("WM_UpdateCurrentAction","WM_UpdateCurrentAction",0);

	CreateILogAndActions(LOG_FOR_WORLDMAP);
	Log_SetActiveAction("EnterToSea");

	SetEventHandler("BI_UpdateWmInterface","BI_UpdateWmInterface",0);
	PostEvent("BI_UpdateWmInterface",1000);
	SetEventHandler("Control Activation","WM_ProcessControlPress",0); // boal
	InitActivePerkShower();
	procLoadIntoNew();
	TEV.WDM_ShipRadiusUpdate = true;
	wdmEvent_ShipRadiusUpdate();
}
// boal -->
void WM_ProcessControlPress()
{
	string ControlName = GetEventData();
	if( sti(InterfaceStates.Launched) != 0 ) {return;}

	switch(ControlName)
	{
		case "BICommandsActivate": 
			PlaySound("OK"); // boal даёшь звуки!
		break;
	}
}
// boal <--

void BI_UpdateWmInterface()
{
	WM_SetShipData();
	SendMessage(&BattleInterface,"l",BI_MSG_REFRESH);
	PostEvent("BI_UpdateWmInterface",1000);
	
//	LaunchInfoMessage(3); // сообщение на глобальной карте
}

void DeleteWmInterface()
{
	DeleteClass(&BattleInterface);
	DelEventHandler("BI_CommandEndChecking", "WM_CommandEndChecking");
	DelEventHandler("BI_LaunchCommand", "WM_LaunchCommand");
	DelEventHandler("WM_SetPossibleCommands","WM_SetPossibleCommands");
	DelEventHandler("WM_UpdateCurrentAction","WM_UpdateCurrentAction");

	DelEventHandler("BI_UpdateWmInterface","BI_UpdateWmInterface");
	DelEventHandler("Control Activation","WM_ProcessControlPress"); // boal
}

ref WM_CommandEndChecking()
{
	BI_retComValue = 0;
	string comName = GetEventData();

	switch(comName)
	{
	case "cancel":
		BI_retComValue = -1;
		break;
	}

	return &BI_retComValue;
}

void WM_LaunchCommand()
{
	int charIdx = GetEventData();
	string commandName = GetEventData();
	int targetNum = GetEventData();
	string locName = GetEventData();

	ref chRef = GetCharacter(charIdx);
	if( LAi_IsDead(chRef) ) return;

	aref arFader;
	if( GetEntity(arFader,"fader") ) {return;}

	if(targetNum==-1 && locName=="cancel") {
		SendMessage(&BattleInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");
		return;
	}
	if(commandName=="cancel") {
		SendMessage(&BattleInterface,"ls",MSG_BATTLE_LAND_MAKE_COMMAND,"cancel");
		return;
	}

	switch(commandName)
	{
	case "EnterToSea":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	case "EnterToIsland":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	case "EnterToShip":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	case "EnterToStorm":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	case "EnterToAttack":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	case "EnterToEnemy":
		SendMessage(&worldMap,"l",MSG_WORLDMAP_LAUNCH_EXIT_TO_SEA);
		break;
	}

	BI_SetSpecCommandMode(BI_COMMODE_MY_SHIP_SELECT,-1,-1,-1, 0);
}

void WM_SetPossibleCommands()
{
	int chIdx = GetEventData();
	int mainIdx = sti(pchar.index);

	if( chIdx<0 || CharacterIsDead(GetCharacter(chIdx)) )
	{
		// отключим все команды
		aref aroot,arcur;
		makearef(aroot,BattleInterface.Commands);
		int q = GetAttributesNum(aroot);
		for(int i=0; i<q; i++)
		{
			arcur = GetAttributeN(aroot,i);
			arcur.enable = false;
		}
		return;
	}

	BattleInterface.Commands.Cancel.enable = true;
	BattleInterface.Commands.EnterToAttack.enable = false;
	BattleInterface.Commands.EnterToShip.enable	= false;
	BattleInterface.Commands.EnterToSea.enable = false;
	BattleInterface.Commands.EnterToIsland.enable = false;
	BattleInterface.Commands.EnterToStorm.enable = false;
	BattleInterface.Commands.EnterToEnemy.enable = false;

	if (GetGlobalTutor())
	{
		if (worldmap.island == "Tortuga")
		{
		    BattleInterface.Commands.EnterToIsland.enable = true;
		}
		return;
	}

	bool bDefault = true;
	switch( sti(worldMap.encounter_type) )
	{
	case 0:
		BattleInterface.Commands.EnterToIsland.enable = true;
		//Log_SetActiveAction("EnterToIsland");
		Log_SetActiveAction("EnterToSea");  //boal
		bDefault = false;
		break;
	case 1:
		BattleInterface.Commands.EnterToShip.enable	= true;
		Log_SetActiveAction("EnterToShip");
		bDefault = false;
		break;
	case 2:
		BattleInterface.Commands.EnterToAttack.enable = true;
		Log_SetActiveAction("EnterToAttack");
		bDefault = false;
		break;
	case 3:
		BattleInterface.Commands.EnterToEnemy.enable = true;
		Log_SetActiveAction("EnterToEnemy");
		bDefault = false;
		break;
	case 4:
		BattleInterface.Commands.EnterToStorm.enable = true;
		Log_SetActiveAction("EnterToStorm");
		bDefault = false;
		break;
	}

	if( bDefault )
	{
		if( sti(worldMap.encounter_island) ) {
			BattleInterface.Commands.EnterToIsland.enable = true;
			//Log_SetActiveAction("EnterToIsland");
			Log_SetActiveAction("EnterToSea");  //boal
		} else {
			BattleInterface.Commands.EnterToSea.enable = true;
			Log_SetActiveAction("EnterToSea");
		}
	}
}

void WM_UpdateCurrentAction()
{
	bool bDefault = true;

	if (GetGlobalTutor())
	{
		return;
	}

	switch( sti(worldMap.encounter_type) )
	{
	case 0:
		//Log_SetActiveAction("EnterToIsland");
		Log_SetActiveAction("EnterToSea");  //boal
		bDefault = false;
		break;
	case 1:
		// Не Работает =(
//		if(FindRealEncounterTypeFromId(worldMap.areaEncId) > ENCOUNTER_TYPE_ALONE)
//		{
//			Log_SetActiveAction("GetOnBoard");
//			bDefault = false;
//			break;
//		}
		Log_SetActiveAction("EnterToShip");
		bDefault = false;
		break;
	case 2:
		Log_SetActiveAction("EnterToAttack");
		bDefault = false;
		break;
	case 3:
		Log_SetActiveAction("EnterToEnemy");
		bDefault = false;
		break;
	case 4:
		Log_SetActiveAction("EnterToStorm");
		bDefault = false;
		break;
	}
	if( bDefault ) {
		if( sti(worldMap.encounter_island) ) {
			//Log_SetActiveAction("EnterToIsland");
			Log_SetActiveAction("EnterToSea");  //boal
		} else {
			Log_SetActiveAction("EnterToSea");
		}
	}
	SendMessage(&BattleInterface,"l",BI_MSG_REFRESH);
}

void WM_InitializeCommands()
{
	int idLngFile = LanguageOpenFile("commands_name.txt");

	BattleInterface.Commands.Cancel.enable			= false;
	BattleInterface.Commands.Cancel.picNum			= 1;
	BattleInterface.Commands.Cancel.selPicNum		= 0;
	BattleInterface.Commands.Cancel.texNum			= 0;
	BattleInterface.Commands.Cancel.event			= "Cancel";
	BattleInterface.Commands.Cancel.note			= LanguageConvertString(idLngFile, "sea_Cancel");

	BattleInterface.Commands.EnterToSea.enable		= false;
 	BattleInterface.Commands.EnterToShip.picNum		= 1;
	BattleInterface.Commands.EnterToShip.selPicNum	= 9;
	BattleInterface.Commands.EnterToSea.texNum		= 1;
	BattleInterface.Commands.EnterToSea.event		= "EnterToSea";
	BattleInterface.Commands.EnterToSea.note		= LanguageConvertString(idLngFile, "worldmap_sea");

	BattleInterface.Commands.EnterToIsland.enable		= false;
	BattleInterface.Commands.EnterToIsland.picNum		= 1;//0;
	BattleInterface.Commands.EnterToIsland.selPicNum	= 9;//8;
	BattleInterface.Commands.EnterToIsland.texNum		= 1;
	BattleInterface.Commands.EnterToIsland.event		= "EnterToIsland";
	BattleInterface.Commands.EnterToIsland.note			= LanguageConvertString(idLngFile, "worldmap_sea");

	BattleInterface.Commands.EnterToShip.enable		= false;
	BattleInterface.Commands.EnterToSea.picNum		= 4;
	BattleInterface.Commands.EnterToSea.selPicNum	= 12;
	BattleInterface.Commands.EnterToShip.texNum		= 1;
	BattleInterface.Commands.EnterToShip.event		= "EnterToShip";
	BattleInterface.Commands.EnterToShip.note		= LanguageConvertString(idLngFile, "worldmap_sea");

	BattleInterface.Commands.EnterToStorm.enable		= false;
	BattleInterface.Commands.EnterToStorm.picNum		= 5;
	BattleInterface.Commands.EnterToStorm.selPicNum		= 13;
	BattleInterface.Commands.EnterToStorm.texNum		= 1;
	BattleInterface.Commands.EnterToStorm.event			= "EnterToStorm";
	BattleInterface.Commands.EnterToStorm.note			= LanguageConvertString(idLngFile, "worldmap_sea");

	BattleInterface.Commands.EnterToAttack.enable		= false;
	BattleInterface.Commands.EnterToAttack.picNum		= 2;
	BattleInterface.Commands.EnterToAttack.selPicNum	= 10;
	BattleInterface.Commands.EnterToAttack.texNum		= 1;
	BattleInterface.Commands.EnterToAttack.event		= "EnterToAttack";
	BattleInterface.Commands.EnterToAttack.note			= LanguageConvertString(idLngFile, "worldmap_sea");

	BattleInterface.Commands.EnterToEnemy.enable	= false;
	BattleInterface.Commands.EnterToEnemy.picNum	= 3;
	BattleInterface.Commands.EnterToEnemy.selPicNum	= 11;
	BattleInterface.Commands.EnterToEnemy.texNum	= 1;
	BattleInterface.Commands.EnterToEnemy.event		= "EnterToEnemy";
	BattleInterface.Commands.EnterToEnemy.note		= LanguageConvertString(idLngFile, "worldmap_sea");

	LanguageCloseFile(idLngFile);

	worldMap.encounter_type = -1;
}

void WM_SetParameterData()
{
	float fHtRatio = GetScreenScale();
	int coff, boff, doff, numline;
	string sAttr, sAttrDes, sAttrB;
	
	BattleInterface.CommandTextures.list.t0.name = "battle_interface\cancel.tga.tx";
	BattleInterface.CommandTextures.list.t0.xsize = 2;
	BattleInterface.CommandTextures.list.t0.ysize = 1;

	BattleInterface.CommandTextures.list.t1.name = "battle_interface\worldmapcommands.tga.tx";
	BattleInterface.CommandTextures.list.t1.xsize = 8;
	BattleInterface.CommandTextures.list.t1.ysize = 2;

	BattleInterface.wm_sign.fontid					= "interface_normal_smallscale";
//	BattleInterface.wm_sign.fontcolor				= argb(255,255,255,168); //argb(255,255,255,255);
	BattleInterface.wm_sign.fontcolor				= argb(255,255,255,255);
	BattleInterface.wm_sign.fontscale				= 0.26 * fHtRatio;
    BattleInterface.wm_sign.fontoffset       		= RecalculateHIcon(makeint(-4 * fHtRatio))+","+RecalculateVIcon(makeint(42 * fHtRatio));

	BattleInterface.wm_sign.shipnamefontid			= "interface_normal_smallscale";
	BattleInterface.wm_sign.shipnamefontcolor		= argb(255,255,255,255);
	BattleInterface.wm_sign.shipnamefontscale		= 0.26 * fHtRatio;
    BattleInterface.wm_sign.shipnamefontoffset       = RecalculateHIcon(makeint(-4 * fHtRatio))+","+RecalculateVIcon(makeint(26 * fHtRatio));

	BattleInterface.wm_sign.backtexturename			= "battle_interface\ShipBackIcon.tga.tx";
	BattleInterface.wm_sign.backcolor				= argb(255,128,128,128);
	BattleInterface.wm_sign.backuv					= "0.0,0.0,1.0,1.0";
	BattleInterface.wm_sign.backoffset				= RecalculateHIcon(makeint(-4 * fHtRatio))+","+RecalculateVIcon(makeint(8 * fHtRatio)); //"0.0,0.0";
	BattleInterface.wm_sign.backiconsize			= RecalculateHIcon(makeint(106 * fHtRatio))+","+RecalculateVIcon(makeint(106 * fHtRatio));

	BattleInterface.wm_sign.shipstatetexturename	= "battle_interface\ShipState.tga.tx";
	BattleInterface.wm_sign.shipstatecolor			= argb(255,128,128,128);
	BattleInterface.wm_sign.shiphpuv				= "0.0,0.0625,0.5,0.6875";
    BattleInterface.wm_sign.shiphpoffset			= RecalculateHIcon(makeint(-30 * fHtRatio))+","+RecalculateVIcon(makeint(-6 * fHtRatio));
	BattleInterface.wm_sign.shipspoffset			= RecalculateHIcon(makeint(22 * fHtRatio))+","+RecalculateVIcon(makeint(-6 * fHtRatio));
	
    BattleInterface.wm_sign.shiphpiconsize			= RecalculateHIcon(makeint(54 * fHtRatio))+","+RecalculateVIcon(makeint(67 * fHtRatio));
	BattleInterface.wm_sign.shipspiconsize			= RecalculateHIcon(makeint(54 * fHtRatio))+","+RecalculateVIcon(makeint(67 * fHtRatio));
	BattleInterface.wm_sign.shipspuv				= "0.5,0.0625,1.0,0.6875";

	BattleInterface.wm_sign.shipclasstexturename	= "battle_interface\ShipClass.tga.tx";
	BattleInterface.wm_sign.shipclasscolor			= argb(255,128,128,128); //argb(255,128,128,128);
	BattleInterface.wm_sign.shipclassuv				= "0.0,0.0,1.0,1.0";
    BattleInterface.wm_sign.shipclassoffset			= RecalculateHIcon(makeint(-3 * fHtRatio))+","+RecalculateVIcon(makeint(-37 * fHtRatio));
	
    BattleInterface.wm_sign.shipclassiconsize		= RecalculateHIcon(makeint(115 * fHtRatio))+","+RecalculateVIcon(makeint(29 * fHtRatio));

	BattleInterface.wm_sign.gunchargeprogress		= "0.0625, 0.219, 0.359, 0.5, 0.641, 0.781, 0.983";

	BattleInterface.wm_sign.shiptexturename			= "battle_interface\ship_icons2.tga.tx";
	BattleInterface.wm_sign.shipcolor				= argb(255,128,128,128);
	
    BattleInterface.wm_sign.shipoffset				= RecalculateHIcon(makeint(-3 * fHtRatio))+","+RecalculateVIcon(makeint(-2 * fHtRatio));

    BattleInterface.wm_sign.shipiconsize			= RecalculateHIcon(makeint(72 * fHtRatio))+","+RecalculateVIcon(makeint(72 * fHtRatio));

    BattleInterface.wm_sign.commandlistverticaloffset = -20 * fHtRatio;

    BattleInterface.wm_sign.iconoffset1 = RecalculateHIcon(makeint(70 * fHtRatio))+","+RecalculateVIcon(makeint(70 * fHtRatio));
	BattleInterface.wm_sign.iconoffset2 = RecalculateHIcon(makeint(70 * fHtRatio))+","+RecalculateVIcon(makeint(198 * fHtRatio));
	BattleInterface.wm_sign.iconoffset3 = RecalculateHIcon(makeint(70 * fHtRatio))+","+RecalculateVIcon(makeint(326 * fHtRatio));
	BattleInterface.wm_sign.iconoffset4 = RecalculateHIcon(makeint(70 * fHtRatio))+","+RecalculateVIcon(makeint(454 * fHtRatio));
	BattleInterface.wm_sign.iconoffset5 = RecalculateHIcon(makeint(70 * fHtRatio))+","+RecalculateVIcon(makeint(582 * fHtRatio));
	BattleInterface.wm_sign.iconoffset6 = RecalculateHIcon(makeint(70 * fHtRatio))+","+RecalculateVIcon(makeint(710 * fHtRatio));	//ZhilyaevDm 6й корабль

	BattleInterface.CommandList.CommandMaxIconQuantity = 8;
	BattleInterface.CommandList.CommandIconSpace = 1;
	BattleInterface.CommandList.CommandIconLeft = makeint(128 * fHtRatio);//157; boal
	BattleInterface.CommandList.CommandIconWidth = RecalculateHIcon(makeint(48 * fHtRatio));
	BattleInterface.CommandList.CommandIconHeight = RecalculateVIcon(makeint(48 * fHtRatio));

//	BattleInterface.CommandList.CommandNoteFont = "interface_normal";
//	BattleInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
//	BattleInterface.CommandList.CommandNoteScale = 1.0 * fHtRatio;
//	BattleInterface.CommandList.CommandNoteOffset = RecalculateHIcon(0) + "," + RecalculateVIcon(makeint(-42 * fHtRatio));

	BattleInterface.CommandList.CommandNoteFont = "interface_normal_smallscale";
	BattleInterface.CommandList.CommandNoteColor = argb(255,255,255,255);
	BattleInterface.CommandList.CommandNoteScale = 0.26 * fHtRatio;
	BattleInterface.CommandList.CommandNoteOffset = RecalculateHIcon(0) + "," + RecalculateVIcon(makeint(-42 * fHtRatio));

	BattleInterface.CommandList.UDArrow_Texture = "battle_interface\arrowly.tga";
	BattleInterface.CommandList.UDArrow_UV_Up = "0.0,1.0,1.0,0.0";
	BattleInterface.CommandList.UDArrow_UV_Down = "0.0,0.0,1.0,1.0";
	BattleInterface.CommandList.UDArrow_Size = RecalculateHIcon(makeint(32 * fHtRatio)) + "," + RecalculateVIcon(makeint(32 * fHtRatio));
	BattleInterface.CommandList.UDArrow_Offset_Up = RecalculateHIcon(makeint(-41 * fHtRatio)) + "," + RecalculateVIcon(makeint(-30 * fHtRatio));
	BattleInterface.CommandList.UDArrow_Offset_Down = RecalculateHIcon(makeint(-41 * fHtRatio)) + "," + RecalculateVIcon(makeint(46 * fHtRatio));

	BattleInterface.maincharindex = pchar.index;

	int iTipBottomOffset = sti(showWindow.bottom) - RecalculateVIcon(65 * fHtRatio);
	for(numLine = 1; numLine <= N_TIPS; numline++)
	{
		sAttr = "Con"+(N_TIPS - numLine + 1);
		sAttrDes = "Con"+(N_TIPS - numLine + 1)+"desc";
		sAttrB = "Con"+(N_TIPS - numLine + 1)+"Back";

		coff = -3 + (numLine-1)*45;
		boff = 0 + (numLine-1)*45;
		doff = -6 + (numLine-1)*45;

		BattleInterface.textinfo.(sAttrB).font = "Info_fader_ls";
		BattleInterface.textinfo.(sAttrB).scale = 0.6 * fHtRatio;
		BattleInterface.textinfo.(sAttrB).color = argb(155,255,255,255);
		BattleInterface.textinfo.(sAttrB).pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(200 * fHtRatio));
		BattleInterface.textinfo.(sAttrB).pos.y = iTipBottomOffset - RecalculateVIcon(makeint(boff * fHtRatio));
		BattleInterface.textinfo.(sAttrB).align = "centr";
		BattleInterface.textinfo.(sAttrB).text = "";
		BattleInterface.textinfo.(sAttrB).refreshable = true;

		BattleInterface.textinfo.(sAttr).font = "KEYBOARD_SYMBOL";
		BattleInterface.textinfo.(sAttr).scale = 0.9 * fHtRatio;
		BattleInterface.textinfo.(sAttr).color = argb(255,255,255,255);
		BattleInterface.textinfo.(sAttr).pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(29 * fHtRatio));
		BattleInterface.textinfo.(sAttr).pos.y = iTipBottomOffset - RecalculateVIcon(makeint(coff * fHtRatio));
		BattleInterface.textinfo.(sAttr).align = "left";
		BattleInterface.textinfo.(sAttr).text = "";
		BattleInterface.textinfo.(sAttr).refreshable = true;

		BattleInterface.textinfo.(sAttrDes).font = "interface_normal";
		BattleInterface.textinfo.(sAttrDes).scale = 1.2 * fHtRatio;
		BattleInterface.textinfo.(sAttrDes).color = argb(255,255,255,255);
		BattleInterface.textinfo.(sAttrDes).pos.x = sti(showWindow.left) + RecalculateHIcon(makeint(71 * fHtRatio));
		BattleInterface.textinfo.(sAttrDes).pos.y = iTipBottomOffset - RecalculateVIcon(makeint(doff * fHtRatio));
		BattleInterface.textinfo.(sAttrDes).align = "left";
		BattleInterface.textinfo.(sAttrDes).text = "";
		BattleInterface.textinfo.(sAttrDes).refreshable = true;
	}

	ControlsMapDesc();

	WM_SetShipData();
}

void WM_SetShipData()
{
	int i,n,cn;
	string signattr;
	float uvleft,uvtop, uvright,uvbottom;

	i = 1;
	for(n=0; n<COMPANION_MAX; n++)
	{
		cn = GetCompanionIndex(pchar,n);
		if( cn!=-1 )
		{
			signattr = "sign" + i;
			BattleInterface.wm_sign.(signattr).leftprogress = GetHullPercent(&Characters[cn]) * 0.01;
			BattleInterface.wm_sign.(signattr).rightprogress = GetSailPercent(&Characters[cn]) * 0.01;
			GetStarProgressByValue(GetCharacterShipClass(&Characters[cn]), &uvleft, &uvtop, &uvright, &uvbottom);
			BattleInterface.wm_sign.(signattr).starprogress = uvleft+","+uvtop + "," + uvright+","+uvbottom;
			GetTextureUVForShip( sti(RealShips[sti(characters[cn].Ship.Type)].basetype), &uvleft,&uvtop, &uvright,&uvbottom);
			BattleInterface.wm_sign.(signattr).faceuv = uvleft+","+uvtop + "," + uvright+","+uvbottom;
			BattleInterface.wm_sign.(signattr).text = GetCrewQuantity(&Characters[cn]);
			BattleInterface.wm_sign.(signattr).shipname = Characters[cn].Ship.Name;
			i++;
		}
	}
}

float DEPRECATED__GetStarProgressByValue(int n)
{
	float f = 0.0;
	switch( n )
	{
	case 1: f = 0.219; break;
	case 2: f = 0.359; break;
	case 3: f = 0.5; break;
	case 4: f = 0.641; break;
	case 5: f = 0.781; break;
	case 6: f = 0.983; break;
	}
	return f;
}

//belamour присвоить uv классу корабля (замена progressbar)
void GetStarProgressByValue(int n, ref rLeft, ref rTop, ref rRight, ref rBottom)
{
	float fLeft = 0.0;
	float fRight = 0.0;

	float pw = 1.0/8.0;

	fLeft = pw*n;
    fRight = fLeft + pw;

	rLeft = fLeft;
    rTop = 0.0;
    rRight = fRight;
    rBottom = 1.0;
}

void ControlsMapDesc()
{
	int iControlsTips = iShowTips;
	int numline;
	string sAttr, sAttrDes, sAttrB;

//	if(iControlsTips > 0 && !IsSteamDeck())
	if(iControlsTips > 0)
	{
		int colorbase = argb(255,255,255,255);

		for(numline = 1; numline <= N_TIPS; numline++)
		{
			sAttrB = "Con"+numLine+"Back";
			sAttr = "Con"+numLine;
			sAttrDes = "Con"+numLine+"desc";

			BattleInterface.textinfo.(sAttrB).text = "";
			BattleInterface.textinfo.(sAttr).text = "";
			BattleInterface.textinfo.(sAttrDes).text = "";

			BattleInterface.textinfo.(sAttr).color = colorbase;
			BattleInterface.textinfo.(sAttrDes).color = colorbase;
		}

		// поднять паруса / спустить паруса
		numline = N_TIPS;
		sAttrB = "Con"+numLine+"Back";
		sAttr = "Con"+numLine;
		sAttrDes = "Con"+numLine+"desc";
		if(!CheckAttribute(&BattleInterface, "internal.wm_player_state"))
			BattleInterface.internal.wm_player_state = 0;
		if(sti(BattleInterface.internal.wm_player_state) > 0)
		{
			BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("Ship_SailDown");
			BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("Ship_SailDown","ControlsNames.txt");
		}
		else
		{
			BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("Ship_SailUp");
			BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("Ship_SailUp","ControlsNames.txt");
		}
		BattleInterface.textinfo.(sAttrB).text = "1";

		// ускорить время / отключить ускорение
		numline--;
		sAttrB = "Con"+numLine+"Back";
		sAttr = "Con"+numLine;
		sAttrDes = "Con"+numLine+"desc";
		BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("TimeScale");
		BattleInterface.textinfo.(sAttrB).text = "1";
		if(TimeScaleCounter <= 0)
			BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("TimeScaleOn","ControlsNames.txt");
		else
			BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("TimeScaleOff","ControlsNames.txt");

		if (!wdmLockReload)
		{
			// выйти в море
			numline--;
			sAttrB = "Con"+numLine+"Back";
			sAttr = "Con"+numLine;
			sAttrDes = "Con"+numLine+"desc";
			BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("WMapCancel");
			BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("WMapCancel","ControlsNames.txt");
			BattleInterface.textinfo.(sAttrB).text = "1";
		}

		// режим камеры
		numline--;
		sAttrB = "Con"+numLine+"Back";
		sAttr = "Con"+numLine;
		sAttrDes = "Con"+numLine+"desc";
		BattleInterface.textinfo.(sAttr).text = GetKeyCodeImg("WMapCameraSwitch");
		BattleInterface.textinfo.(sAttrDes).text = GetConvertStr("WMapCameraSwitch","ControlsNames.txt");
		BattleInterface.textinfo.(sAttrB).text = "1";
	}
}

#event_handler("WM_Event_UpdatePlayerShipState","WM_Event_UpdatePlayerShipState");
void WM_Event_UpdatePlayerShipState()
{
	int sailState = GetEventData();
	int iControlsTips = iShowTips;
//	if(iControlsTips > 0 && !IsSteamDeck())
	if(iControlsTips > 0)
	{
		BattleInterface.internal.wm_player_state = sailState;
		ControlsMapDesc();
	}
}

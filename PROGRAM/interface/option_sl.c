
void OSL_WriteGameOption()
{
	object gopt;
	PrepareDefaultOption(&gopt);
	GetRealOptions(&gopt);
	SaveSavedOptions(&gopt);
}

void OSL_ReadGameOption()
{
	object gopt;
	PrepareDefaultOption(&gopt);
	ReadSavedOptions(&gopt);
	SetCurentOptions(&gopt);
}

void PrepareDefaultOption(ref optref)
{
//HardCoffee global volume options
/*	optref.volume.music = 0.25;
	optref.volume.sound = 0.25;
	optref.volume.dialog = 0.25;*/
	optref.cameramode.follow_on = true;
	optref.alwaysrun = true;
	optref.video.grassquantity = 0;
	optref.seadetails = 1.0;
	optref.ifonttype = 0;
	optref.imoreinfo = 0;
	optref.itarget = 2;
	optref.iquicksaveslots = 12;
	optref.NoAdultSounds = 1;

	optref.HerbDetails.Range = 0.5;
	optref.HerbDetails.Height = 0.225;
	optref.FoliageDrawDistance = 2250.0;

	SeaParametrs.MaxVertices = MaxVertices;
	SeaParametrs.MaxIndices = MaxIndices;
	SeaParametrs.GridStepX = GridStepX;
	SeaParametrs.GridStepPC = GridStepPC;
	SeaParametrs.LodScale = LodScale;
	SeaParametrs.MaxWaveDistance = MaxWaveDistance;
}

void GetRealOptions(ref optref)
{
//HardCoffee global volume options
/*	float ftmp1, ftmp2, ftmp3;

	ftmp1 = stf(optref.volume.sound);
	ftmp2 = stf(optref.volume.music);
	ftmp3 = stf(optref.volume.dialog);
	GetMasterVolume(&ftmp1, &ftmp2, &ftmp3);
	optref.volume.sound = ftmp1;
	optref.volume.music = ftmp2;
	optref.volume.dialog = ftmp3;*/

	optref.cameramode.follow_on = !locCameraEnableSpecialMode;

	optref.video.grassquantity = iGrassQuality;
	if( CheckAttribute(&InterfaceStates,"SeaDetails") ) {
		optref.seadetails = stf(InterfaceStates.SeaDetails);
	}

	if( CheckAttribute(&InterfaceStates,"InvertCameras") ) {
		optref.cameramode.InvertCameras = sti(InterfaceStates.InvertCameras);
	} else {
		optref.cameramode.InvertCameras = false;
	}

	if( CheckAttribute(&InterfaceStates,"EnabledQuestsMarks") ) {
        optref.cameramode.EnabledQuestsMarks = sti(InterfaceStates.EnabledQuestsMarks);
    } else {
        optref.cameramode.EnabledQuestsMarks = true;
    }

	if( CheckAttribute(&InterfaceStates,"EnabledQuestsPointers") ) {
        optref.cameramode.EnabledQuestsPointers = sti(InterfaceStates.EnabledQuestsPointers);
    } else {
        optref.cameramode.EnabledQuestsPointers = true;
    }
	
	if( CheckAttribute(&InterfaceStates,"SimpleSea") ) {
		optref.cameramode.SimpleSeaMode = sti(InterfaceStates.SimpleSea);
	} else {
		optref.cameramode.SimpleSeaMode = true;
	}

	if( CheckAttribute(&InterfaceStates,"ShowBattleMode") ) {
		optref.cameramode.ShowBattleMode = sti(InterfaceStates.ShowBattleMode);
	} else {
		optref.cameramode.ShowBattleMode = false;
	}
	
	if( CheckAttribute(&InterfaceStates,"SkipStartVideo") ) {
		optref.cameramode.SkipStartVideo = sti(InterfaceStates.SkipStartVideo);
	} else {
		optref.cameramode.SkipStartVideo = false;
	}
	
	if( CheckAttribute(&InterfaceStates,"EnabledShipMarks") ) {
		optref.cameramode.EnabledShipMarks = sti(InterfaceStates.EnabledShipMarks);
	} else {
		optref.cameramode.EnabledShipMarks = true;
	}

	if( CheckAttribute(&InterfaceStates,"ShowCharString") ) {
        optref.cameramode.ShowCharString = sti(InterfaceStates.ShowCharString);
    } else {
        optref.cameramode.ShowCharString = true;
    }

    if( CheckAttribute(&InterfaceStates,"ShowTutorial") ) {
        optref.cameramode.ShowTutorial = sti(InterfaceStates.ShowTutorial);
    } else {
        optref.cameramode.ShowTutorial = true;
    }

	if( CheckAttribute(&InterfaceStates,"ShowControlTips") ) {
		optref.cameramode.ShowControlTips = InterfaceStates.ShowControlTips;
	} else {
		optref.cameramode.ShowControlTips = "3";
	}

	if( CheckAttribute(&InterfaceStates,"FontType") ) {
		optref.ifonttype = sti(InterfaceStates.FontType);
	} else {
		optref.ifonttype = 0;
	}

	if( CheckAttribute(&InterfaceStates,"MoreInfo") ) {
		optref.imoreinfo = sti(InterfaceStates.MoreInfo);
	} else {
		optref.imoreinfo = 0;
	}

	if( CheckAttribute(&InterfaceStates,"TargetMode") ) {
		optref.itarget = sti(InterfaceStates.TargetMode);
	} else {
		optref.itarget = 2;
	}

	if( CheckAttribute(&InterfaceStates,"QuickSaveSlots") ) {
		optref.iquicksaveslots = sti(InterfaceStates.QuickSaveSlots);
	} else {
		optref.iquicksaveslots = 12;
	}

	if( CheckAttribute(&InterfaceStates,"NoAdultSounds") ) {
		optref.NoAdultSounds = sti(InterfaceStates.NoAdultSounds);
	} else {
		optref.NoAdultSounds = 1;
	}

	if( CheckAttribute(&InterfaceStates,"CrewOnDeck") ) {
		optref.cameramode.CrewOnDeck = sti(InterfaceStates.CrewOnDeck);
	} else {
		optref.cameramode.CrewOnDeck = true;
	}

	if( CheckAttribute(&InterfaceStates,"SkyRotation") ) {
		optref.cameramode.SkyRotation = sti(InterfaceStates.SkyRotation);
	} else {
		optref.cameramode.SkyRotation = true;
	}

	// KZ NewFovCalculation > Смена вертикального FOV на лету
	if( CheckAttribute(&InterfaceStates,"NewFovCalculation") ) {
		optref.cameramode.NewFovCalculation = sti(InterfaceStates.NewFovCalculation);
	} else {
		optref.cameramode.NewFovCalculation = GetNewFovCalculationDefault();
	}

	// KZ HudAutoFit > Подгон HUD под разрешение экрана после загрузки сейва
	if( CheckAttribute(&InterfaceStates,"HudAutoFit") ) {
		optref.HudAutoFit = sti(InterfaceStates.HudAutoFit);
	} else {
		optref.HudAutoFit = false;
	}

	if( CheckAttribute(&InterfaceStates,"TimeSpeedAccel") ) {
		optref.TimeSpeedAccel = sti(InterfaceStates.TimeSpeedAccel);
	} else {
		optref.TimeSpeedAccel = false;
	}

	// > Continuous music
	SetContinuousMusic(&InterfaceStates, optref);
	// < Continuous music

	// автосейвы
	string sAutoSave;
	for(int i = 0; i < AUTO_SAVE_TYPE_MAX; i++)
	{
		sAutoSave = "AutoSave_" + GetAutoSaveType(i);
		if(CheckAttribute(&InterfaceStates, sAutoSave))
			optref.(sAutoSave) = sti(InterfaceStates.(sAutoSave));
		else
			optref.(sAutoSave) = 10;
	}
	// <--

	GetControlsOptions(optref);

	// mouse
	if( CheckAttribute(&InterfaceStates,"mouse.loc_sens") ) {
		optref.mouse.loc_sensitivity = InterfaceStates.mouse.loc_sens;
	} else {
		optref.mouse.loc_sensitivity = 0.5;
	}
	if( CheckAttribute(&InterfaceStates,"mouse.sea_sens") ) {
		optref.mouse.sea_sensitivity = InterfaceStates.mouse.sea_sens;
	} else {
		optref.mouse.sea_sensitivity = 0.5;
	}
	// video colors
	if( CheckAttribute(&InterfaceStates,"video.contrast") ) {
		optref.video.contrast = InterfaceStates.video.contrast;
	} else {
		optref.video.contrast = 1.0;
	}
	if( CheckAttribute(&InterfaceStates,"video.gamma") ) {
		optref.video.gamma = InterfaceStates.video.gamma;
	} else {
		optref.video.gamma = 1.0;
	}
	if( CheckAttribute(&InterfaceStates,"video.brightness") ) {
		optref.video.brightness = InterfaceStates.video.brightness;
	} else {
		optref.video.brightness = 0.0;
	}
	
	if (CheckAttribute(&InterfaceStates, "HerbDetails.Range"))
		optref.HerbDetails.Range = InterfaceStates.HerbDetails.Range;
	else
		optref.HerbDetails.Range = 0.0;
	
	if (CheckAttribute(&InterfaceStates, "HerbDetails.Height"))
		optref.HerbDetails.Height = InterfaceStates.HerbDetails.Height;
	else
		optref.HerbDetails.Height = 0.0;

	if (CheckAttribute(&InterfaceStates, "FoliageDrawDistance"))
	{
		if (sti(optref.FoliageDrawDistance) > 5000)
			optref.FoliageDrawDistance = 5000;
		else
			optref.FoliageDrawDistance = stf(InterfaceStates.FoliageDrawDistance);
	}
	else
		optref.FoliageDrawDistance = 1000;

	// Warship 07.07.09 Эффект свечения
	if(CheckAttribute(&InterfaceStates, "GlowEffect"))
	{
		optref.GlowEffect = InterfaceStates.GlowEffect;
	}
	else
	{
		optref.GlowEffect = 50;
	}
	
	SeaParametrs.MaxVertices = MaxVertices;
	SeaParametrs.MaxIndices = MaxIndices;
	SeaParametrs.GridStepX = GridStepX;
	SeaParametrs.GridStepPC = GridStepPC;
	SeaParametrs.MaxWaveDistance = MaxWaveDistance;
	SeaParametrs.LodScale = LodScale;

	// always run
	if( CheckAttribute(&InterfaceStates,"alwaysrun") ) {
		optref.alwaysrun = InterfaceStates.alwaysrun;
	} else {
		optref.alwaysrun = false;
	}
}

void SetCurentOptions(ref optref)
{
	//HardCoffee global volume options //они уже записываются по мере дёргания ползунков
	//SendMessage(&sound,"lfff", MSG_SOUND_SET_MASTER_VOLUME, stf(optref.volume.sound),	stf(optref.volume.music),	stf(optref.volume.dialog));

	locCameraEnableSpecialMode = !sti(optref.cameramode.follow_on);
	
	if( CheckAttribute(optref,"cameramode.SimpleSeaMode") ) {
		InterfaceStates.SimpleSea = optref.cameramode.SimpleSeaMode;
	} else {
		InterfaceStates.SimpleSea = false;
	}

	if( CheckAttribute(optref,"cameramode.ShowBattleMode") ) {
		InterfaceStates.ShowBattleMode = optref.cameramode.ShowBattleMode;
	} else {
		InterfaceStates.ShowBattleMode = false;
	}
	
	if( CheckAttribute(optref,"cameramode.SkipStartVideo") ) {
		InterfaceStates.SkipStartVideo = optref.cameramode.SkipStartVideo;
	} else {
		InterfaceStates.SkipStartVideo = false;
	}

	if( CheckAttribute(optref,"cameramode.EnabledQuestsMarks") ) {
		InterfaceStates.EnabledQuestsMarks = optref.cameramode.EnabledQuestsMarks;
	} else {
		InterfaceStates.EnabledQuestsMarks = true;
	}

	if( CheckAttribute(optref,"cameramode.EnabledQuestsPointers") ) {
		InterfaceStates.EnabledQuestsPointers = optref.cameramode.EnabledQuestsPointers;
	} else {
		InterfaceStates.EnabledQuestsPointers = true;
	}

	if( CheckAttribute(optref,"cameramode.ShowCharString") ) {
        InterfaceStates.ShowCharString = optref.cameramode.ShowCharString;
    } else {
        InterfaceStates.ShowCharString = true;
    }

    if( CheckAttribute(optref,"cameramode.ShowTutorial") ) {
        InterfaceStates.ShowTutorial = optref.cameramode.ShowTutorial;
    } else {
        InterfaceStates.ShowTutorial = true;
    }

	if( CheckAttribute(optref,"cameramode.EnabledShipMarks") ) {
		InterfaceStates.EnabledShipMarks = optref.cameramode.EnabledShipMarks;
	} else {
		InterfaceStates.EnabledShipMarks = true;
	}

	if( CheckAttribute(optref,"cameramode.ShowControlTips") ) {
		InterfaceStates.ShowControlTips = optref.cameramode.ShowControlTips;
	} else {
		InterfaceStates.ShowControlTips = "3";
	}

	if( CheckAttribute(optref,"ifonttype") ) {
		InterfaceStates.FontType = sti(optref.ifonttype);
	} else {
		InterfaceStates.FontType = 0;
	}

	if( CheckAttribute(optref,"imoreinfo") ) {
		InterfaceStates.MoreInfo = sti(optref.imoreinfo);
	} else {
		InterfaceStates.MoreInfo = 0;
	}

	if( CheckAttribute(optref,"itarget") ) {
		iGlobalTarget = sti(optref.itarget);
		InterfaceStates.TargetMode = iGlobalTarget;
	} else {
		InterfaceStates.TargetMode = 2;
	}

	if( CheckAttribute(optref,"iquicksaveslots") ) {
		InterfaceStates.QuickSaveSlots = sti(optref.iquicksaveslots);
	} else {
		InterfaceStates.QuickSaveSlots = 12;
	}

	if( CheckAttribute(optref,"NoAdultSounds") ) {
		InterfaceStates.NoAdultSounds = sti(optref.NoAdultSounds);
	} else {
		InterfaceStates.NoAdultSounds = 1;
	}

	if( CheckAttribute(optref,"cameramode.CrewOnDeck") ) {
		InterfaceStates.CrewOnDeck = optref.cameramode.CrewOnDeck;
	} else {
		InterfaceStates.CrewOnDeck = true;
	}

	if( CheckAttribute(optref,"cameramode.SkyRotation") ) {
		InterfaceStates.SkyRotation = optref.cameramode.SkyRotation;
	} else {
		InterfaceStates.SkyRotation = true;
	}

	// > NewFovCalculation
	if( CheckAttribute(optref,"cameramode.NewFovCalculation") ) {
		InterfaceStates.NewFovCalculation = optref.cameramode.NewFovCalculation;
	} else {
		InterfaceStates.NewFovCalculation = GetNewFovCalculationDefault();
	}

	// > HudAutoFit
	if( CheckAttribute(optref,"HudAutoFit") ) {
		InterfaceStates.HudAutoFit = optref.HudAutoFit;
	} else {
		InterfaceStates.HudAutoFit = false;
	}

	if( CheckAttribute(optref,"TimeSpeedAccel") ) {
		InterfaceStates.TimeSpeedAccel = optref.TimeSpeedAccel;
	} else {
		InterfaceStates.TimeSpeedAccel = true;
	}

	// > Continuous music
	SetContinuousMusic(optref, &InterfaceStates);
	// < Continuous music

	// автосейвы
	string sAutoSave;
	for(int i = 0; i < AUTO_SAVE_TYPE_MAX; i++)
	{
		sAutoSave = "AutoSave_" + GetAutoSaveType(i);
		if(CheckAttribute(optref, sAutoSave))
			InterfaceStates.(sAutoSave) = sti(optref.(sAutoSave));
		else
			InterfaceStates.(sAutoSave) = 10;
	}
	// <--

	// mouse
	if( CheckAttribute(optref,"cameramode.InvertCameras") ) {
		InterfaceStates.InvertCameras = optref.cameramode.InvertCameras;
	} else {
		InterfaceStates.InvertCameras = false;
	}
	if( CheckAttribute(optref,"mouse.loc_sensitivity") ) {
		InterfaceStates.mouse.loc_sens = optref.mouse.loc_sensitivity;
	} else {
		InterfaceStates.mouse.loc_sens = 0.5;
	}
	if( CheckAttribute(optref,"mouse.sea_sensitivity") ) {
		InterfaceStates.mouse.sea_sens = optref.mouse.sea_sensitivity;
	} else {
		InterfaceStates.mouse.sea_sens = 0.5;
	}
	// video colors
	if( CheckAttribute(optref,"video.contrast") ) {
		InterfaceStates.video.contrast = optref.video.contrast;
	} else {
		InterfaceStates.video.contrast = 1.0;
	}
	if( CheckAttribute(optref,"video.gamma") ) {
		InterfaceStates.video.gamma = optref.video.gamma;
	} else {
		InterfaceStates.video.gamma = 1.0;
	}
	if( CheckAttribute(optref,"video.brightness") ) {
		InterfaceStates.video.brightness = optref.video.brightness;
	} else {
		InterfaceStates.video.brightness = 0.0;
	}
	
	if (CheckAttribute(optref, "HerbDetails.Range"))
		InterfaceStates.HerbDetails.Range = optref.HerbDetails.Range;
	else
		InterfaceStates.HerbDetails.Range = 0.0;
	
	if (CheckAttribute(optref, "HerbDetails.Height"))
		InterfaceStates.HerbDetails.Height = optref.HerbDetails.Height;
	else
		InterfaceStates.HerbDetails.Height = 0.0;

	if (CheckAttribute(optref, "FoliageDrawDistance"))
	{
		if (sti(optref.FoliageDrawDistance) > 5000)
			InterfaceStates.FoliageDrawDistance = 5000;
		else
			InterfaceStates.FoliageDrawDistance = stf(optref.FoliageDrawDistance);
	}
	else
		InterfaceStates.FoliageDrawDistance = 1000;

	// Warship 07.07.09 Эффект свечения
	if(CheckAttribute(optref, "GlowEffect"))
	{
		InterfaceStates.GlowEffect = optref.GlowEffect;
	}
	else
	{
		InterfaceStates.GlowEffect = 50;
	}
	
	SetGlowParams(1.0, sti(InterfaceStates.GlowEffect), 2);

	// > NewFovCalculation
	SetNewFovCalculation(sti(InterfaceStates.NewFovCalculation));

	// > HudAutoFit
	SetHudAutoFitOnLoad(sti(InterfaceStates.HudAutoFit));

	if( CheckAttribute(optref,"video.grassquantity") ) {
		iGrassQuality = sti(optref.video.grassquantity);
	}
	
	if( CheckAttribute(optref,"seadetails") ) {
		InterfaceStates.SeaDetails = stf(optref.seadetails);
	}

	XI_SetColorCorrection(stf(InterfaceStates.video.contrast),stf(InterfaceStates.video.gamma),stf(InterfaceStates.video.brightness));

	aref arControls;
	makearef(arControls,optref.controls);
	RestoreKeysFromOptions(arControls);

	// always run
	if( CheckAttribute(&optref,"alwaysrun") ) {
		InterfaceStates.alwaysrun = optref.alwaysrun;
	} else {
		InterfaceStates.alwaysrun = false;
	}

	ControlsMakeInvert();
	SetRealMouseSensitivity();
}

void ReadSavedOptions(ref gopt)
{
	string sFileName = "options";
	if( CheckAttribute(&PlayerProfile,"name") && PlayerProfile.name!="" ) {
		sFileName = "save\"+PlayerProfile.name+"\options\options";
	}
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_LOADOPTIONS, sFileName, gopt);
}

void SaveSavedOptions(ref gopt)
{
	string sFileName = "options";
	if( CheckAttribute(&PlayerProfile,"name") && PlayerProfile.name!="" ) {
		sFileName = "save\"+PlayerProfile.name+"\options\options";
	}
	SendMessage(&GameInterface, "lsa", MSG_INTERFACE_SAVEOPTIONS, sFileName, gopt);
}

void GetControlsOptions(ref optref)
{
	int ng,qg, nc,qc;
	aref arIn, arOut, arGrp, arCntrl;
	string grName, cntrlName;

	makearef(arOut,objControlsState.keygroups);
	optref.controls = true;
	makearef(arIn,optref.controls);

	qg = GetAttributesNum(arOut);
	for(ng=0; ng<qg; ng++)
	{
		arGrp = GetAttributeN(arOut,ng);
		grName = GetAttributeName(arGrp);
		if( CheckAttribute(&objControlsState,"grouplist."+grName) && sti(objControlsState.grouplist.(grName))==true )
		{
			qc = GetAttributesNum(arGrp);
			for(nc=0; nc<qc; nc++)
			{
				arCntrl = GetAttributeN(arGrp,nc);
				if( CheckAttribute(arCntrl,"remapping") && sti(arCntrl.remapping)==true )
				{
					cntrlName = GetAttributeName(arCntrl);
					arIn.(grName).(cntrlName) = GetAttributeValue(arCntrl);
					arIn.(grName).(cntrlName).state = arCntrl.state;
				}
			}
		}
	}
}

void SetContinuousMusic(ref rRead, ref rWrite)
{
	int i, n;
	string s;

	for (n = 0; n <= 7; n++)
	{
		s = "ContinuousMusic";
		i = 1;

		switch (n)
		{
			case 1: s += ".Jungle"; break;
			case 2: s += ".House"; break;
			case 3: s += ".Brothel"; break;
			case 4: s += ".Ship"; break;
			case 5: s += ".Boarding"; break;
			case 6: s += ".Attack"; break;
			case 7: s += ".LSC"; i = 0; break;
		}

		if (CheckAttribute(&rRead, s))
			rWrite.(s) = sti(rRead.(s));
		else
			rWrite.(s) = i;
	}
}

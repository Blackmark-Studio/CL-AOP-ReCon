
#define DEFAULT_CAM_PERSP      1.0
#define DEFAULT_CAM_PERSP_DEN  1.85

#define SEA_CAMERA_SHIP "SeaShipCamera"
#define SEA_CAMERA_DECK "SeaDeckCamera"
#define SEA_CAMERA_FIRE "SeaFireCamera"
#define SEA_CAMERA_FREE "SeaFreeCamera"

object	SeaCameras;
aref	Crosshair;
object	SeaShipCamera, SeaFreeCamera, SeaDeckCamera, SeaFireCamera;
ref		SeaShipCharacterForCamera;
bool	bCanSwitchCameras = true;

void DeleteSeaCamerasEnvironment()
{
	DeleteClass(&SeaCameras);
	DeleteClass(&SeaFreeCamera);
	DeleteClass(&SeaShipCamera);
	DeleteClass(&SeaDeckCamera);
	DeleteClass(&SeaFireCamera);
//	DelEventHandler("SeaCameras_Switch", "SeaCameras_Switch");
	DelEventHandler(TELESCOPE_ACTIVE, "SeaCameras_TelescopeActive");
}

void CreateSeaCamerasEnvironment()
{
	bCanSwitchCameras = true;

	CreateEntity(&SeaCameras, "SEA_CAMERAS");
	CreateEntity(&SeaFreeCamera, "FREE_CAMERA");
	CreateEntity(&SeaShipCamera, "SHIP_CAMERA");
	CreateEntity(&SeaDeckCamera, "DECK_CAMERA");
	CreateEntity(&SeaFireCamera, "FIRE_CAMERA");

	LayerAddObject(SEA_EXECUTE, &SeaShipCamera, iShipPriorityExecute + 5);
	LayerAddObject(SEA_EXECUTE, &SeaFreeCamera, 1);
	LayerAddObject(SEA_EXECUTE, &SeaDeckCamera, iShipPriorityExecute + 5);
	LayerAddObject(SEA_EXECUTE, &SeaFireCamera, iShipPriorityExecute + 5);

	SeaFreeCamera.Perspective = DEFAULT_CAM_PERSP;
	SeaShipCamera.Perspective = DEFAULT_CAM_PERSP;

	// Ship camera paramerets
	SeaShipCamera.SensivityDistance = 30.0;
	SeaShipCamera.SensivityHeightAngle = 0.02;
	SeaShipCamera.SensivityHeightAngleOnShip = 0.005;
	SeaShipCamera.SensivityAzimuthAngle = 0.04;
	SeaShipCamera.MaxAngleX = 0.07;
	SeaShipCamera.MinAngleX = -1.4;
	SeaShipCamera.Distance = 70.0; //69.0
	SeaShipCamera.MinDistance = 25.0;
	SeaShipCamera.MaxDistance = 1500.0; //90.0
	SeaShipCamera.MinHeightOnSea = 1.0;
	SeaShipCamera.MaxHeightOnShip = 5.0; //16.0
	SeaShipCamera.InvertMouseX = 1.0;
	SeaShipCamera.InvertMouseY = -1.0;
	
	// Deck camera paramerets
	SeaDeckCamera.Perspective = 1.285;
	SeaDeckCamera.SensivityDistance = 0.01;
	SeaDeckCamera.SensivityHeightAngle = 0.0015;
	SeaDeckCamera.SensivityAzimuthAngle = 0.0015;
	SeaDeckCamera.StepUp = 0.5;
	SeaDeckCamera.StepMin = 0.01;
	SeaDeckCamera.h_max = 2.0;
	SeaDeckCamera.h_min = 0.5;
	SeaDeckCamera.h_step = 0.1;
	SeaDeckCamera.h_def = 1.6;
	SeaDeckCamera.MaxAngleX = 0.7;
	SeaDeckCamera.MinAngleX = -1.3;
	SeaDeckCamera.RockingX = 0.5;
	SeaDeckCamera.RockingZ = 0.5;

	// evganat - атрибуты SeaFireCamera
	SeaFireCamera.Perspective = 1.285;
//	SeaFireCamera.Perspective = 1.185;
	SeaFireCamera.SensivityDistance = 0.01;
	SeaFireCamera.SensivityHeightAngle = 0.0015;
	SeaFireCamera.SensivityAzimuthAngle = 0.0015;
	SeaFireCamera.MaxAngleX = 0.3;
	SeaFireCamera.MinAngleX = -0.3;
	SeaFireCamera.RockingX = 0.5;
	SeaFireCamera.RockingZ = 0.5;
	SeaFireCamera.MouseSpeedAy = 0.8;

	makearef(Crosshair,SeaCameras.Crosshair);

	if (!bSeaLoad)
	{
		SeaCameras.Camera = SEA_CAMERA_SHIP;
	
		Crosshair.OutsideCamera = true;
	}
//	Crosshair.Colors.Default = argb(0, 255, 255, 0);
//	Crosshair.Colors.Enemy = argb(0, 255, 0, 0);
//	Crosshair.Colors.Friend = argb(0, 0, 255, 0);
//	Crosshair.Colors.Neutral = argb(0, 128, 128, 128);

	//кружки
	Crosshair.Texture = "BATTLE_INTERFACE\crossballs.tga";
	Crosshair.Technique = "battle_tex_col_Rectangle";
	Crosshair.SubTexX = 2;
	Crosshair.SubTexY = 2;
	Crosshair.Colors.Normal = argb(190, 228, 200, 154);
	Crosshair.Colors.Uncharged = argb(140, 106, 27, 27);
	Crosshair.Colors.Damaged = argb(125, 80, 0, 0);
	Crosshair.Colors.Center = argb(210, 139, 45, 45);
	Crosshair.Colors.TargetNeutral = argb(120, 180, 160, 140);
	Crosshair.Colors.TargetFriend = argb(120, 80, 220, 80);
	Crosshair.Colors.TargetEnemy = argb(120, 220, 80, 80);

	Crosshair.TargetSize = 0.75;

	Crosshair.CrosshairSizeMin = 1.0;
	Crosshair.CrosshairSizeMaxDefault = 8.0;
	Crosshair.CrosshairSizeMaxSpyglass = 4.0;

	Crosshair.CrosshairSizeMax = Crosshair.CrosshairSizeMaxDefault;

	// стартовая координата мыши (дистанция)
	Crosshair.StartMouseDist = -140.0;

	//флуктуации - пороги
	Crosshair.MaxDeltaDist = 2.5; //порог для начала флуктуации, считывается за 1 кадр.
	Crosshair.MaxDeltaAy = 0.007;
	Crosshair.MaxDeltaHeight = 2.0;

	Crosshair.MaxTargetDeltaDist = 10.0;
	Crosshair.TargetBoxIncreaseWidth = 3.5;
	Crosshair.TargetBoxIncreaseLength = 3.1;

	SendMessage(&AISea, "la", AI_MESSAGE_SET_CAMERAS_ATTRIBUTE, &SeaCameras);

//	SetEventHandler("SeaCameras_Switch", "SeaCameras_Switch", 1);
	SetEventHandler(TELESCOPE_ACTIVE, "SeaCameras_TelescopeActive", 0);

	// add cameras to list
	SendMessage(&SeaCameras, "li", AI_CAMERAS_ADD_CAMERA, &SeaShipCamera);
	SendMessage(&SeaCameras, "li", AI_CAMERAS_ADD_CAMERA, &SeaFreeCamera);
	SendMessage(&SeaCameras, "li", AI_CAMERAS_ADD_CAMERA, &SeaDeckCamera);
	SendMessage(&SeaCameras, "li", AI_CAMERAS_ADD_CAMERA, &SeaFireCamera);
}

void SeaCameras_TelescopeActive()
{
	int iTelescopeActive = GetEventData();
	Crosshair.OutsideCamera = SeaCameras_isCameraOutside();
	if (iTelescopeActive)
	{
		bCanSwitchCameras = false;
	}
	else
	{
		bCanSwitchCameras = true;
	}
}

void SeaCameras_Switch(string sControl)
{
	if (!bSeaActive || bAbordageStarted)
		return;
	if (!bCanSwitchCameras)
		return;

	string curCamera = SeaCameras.Camera;
	string newCamera;

	if (sControl == "Sea_CameraSwitch")	// таб
	{
		if (curCamera == SEA_CAMERA_SHIP)
			newCamera = SEA_CAMERA_DECK;
		else
			newCamera = SEA_CAMERA_SHIP;
	}
	else if (sControl == "FireCamera_Set")	// пкм
	{
		if (curCamera == SEA_CAMERA_FREE)
			return;
		if (curCamera == SEA_CAMERA_FIRE)
		{
			if (!CheckAttribute(&SeaFireCamera, "LastCamera"))
				SeaFireCamera.LastCamera = SEA_CAMERA_SHIP;
			newCamera = SeaFireCamera.LastCamera;
			SendMessage(&AISea, "la", AI_MESSAGE_FIRE_CAMERA_EXIT, pchar);
		}
		else
		{
			newCamera = SEA_CAMERA_FIRE;
			SeaFireCamera.LastCamera = curCamera;
		}
	}
	else if (sControl == "FreeCam")
	{
		if (curCamera == SEA_CAMERA_FREE)
			newCamera = SEA_CAMERA_SHIP;
		else
			newCamera = SEA_CAMERA_FREE;
	}

	SeaCameras.Camera = newCamera;
	Crosshair.OutsideCamera = (newCamera != SEA_CAMERA_FIRE);
	Sailors.IsOnDeck = or(newCamera == SEA_CAMERA_FIRE, newCamera == SEA_CAMERA_DECK && !sti(InterfaceStates.CrewOnDeck));

	SeaCameras_UpdateCamera();

	RefreshCameraTip();
}

/*
void SeaCameras_Switch()
{
	if (!bCanSwitchCameras) return;

	int bSwitch = false;
	
	// Коммент - выбираем состояние, из которого переключаемся
	// Sailors.IsOnDeck = 1; - Флаг, находимся ли мы на палубе
	// если Sailors.IsOnDeck == 1, значит, мы на палубе, и матросов бегающих мы не увидем
	switch (SeaCameras.Camera)
	{
		case SEA_CAMERA_FREE:
			SeaCameras.Camera = SEA_CAMERA_SHIP;
			Sailors.IsOnDeck = 0;
			bSwitch = true;
		break;
		case SEA_CAMERA_SHIP:
			if (!LAi_IsDead(&Characters[nMainCharacterIndex]))
			{
				SeaCameras.Camera = SEA_CAMERA_DECK;
				Crosshair.OutsideCamera = false;
				Sailors.IsOnDeck = !sti(InterfaceStates.CrewOnDeck);
				bSwitch = true;
			}
		break;
		case SEA_CAMERA_DECK:
			//SeaCameras.Camera = SEA_CAMERA_FREE; break;		// Debug : SeaFreeCamera, release : SeaShipCamera
			SeaCameras.Camera = SEA_CAMERA_SHIP;
			// boal -->
			if (locCameraEnableFree)
            {
			    SeaCameras.Camera = SEA_CAMERA_FREE;
			}
			// boal <--
			Crosshair.OutsideCamera = true;
			Sailors.IsOnDeck = 0;
			bSwitch = true;
		break;
	}
	RefreshCameraTip();
	if (bSwitch) SeaCameras_UpdateCamera();
}
*/

void SeaCameras_SetShipCameraAy(float ay)
{
	TEV.ShipCameraAy = Degree2Radian(ay);
}

void SeaCameras_UpdateCamera()
{
	switch (SeaCameras.Camera)
	{
		case SEA_CAMERA_SHIP:
			SendMessage(&SeaCameras, "lia", AI_CAMERAS_SET_CAMERA, &SeaShipCamera, &SeaShipCharacterForCamera);

			if(CheckAttribute(&TEV, "ShipCameraAy"))
			{
				SendMessage(&SeaShipCamera, "lf", MSG_SHIP_CAMERA_SET_AY, stf(TEV.ShipCameraAy));
				DeleteAttribute(&TEV, "ShipCameraAy");
			}
		break;
		case SEA_CAMERA_FREE:
			SendMessage(&SeaCameras, "lia", AI_CAMERAS_SET_CAMERA, &SeaFreeCamera, &SeaShipCharacterForCamera);
		break;
		case SEA_CAMERA_DECK:
			SendMessage(&SeaCameras, "lia", AI_CAMERAS_SET_CAMERA, &SeaDeckCamera, &SeaShipCharacterForCamera);
		break;
		case SEA_CAMERA_FIRE:
			string sBort = "";
			float fAng = 0.0;
			GetFireCameraBort(&sBort, &fAng);
			SeaFireCamera.Bort = sBort;
			SendMessage(&AISea, "la", AI_MESSAGE_FIRE_CAMERA_RESET, &Characters[GetMainCharacterIndex()]);
			SendMessage(&SeaCameras, "liasf", AI_CAMERAS_SET_CAMERA, &SeaFireCamera, &SeaShipCharacterForCamera, "cam_"+sBort, fAng);
		break;
	}
}

void SeaCameras_SetDieCamera()
{
	bool bOldCanSwitchCameras;
	if (SeaCameras.Camera == SEA_CAMERA_DECK)
	{
		SeaCameras.Camera = SEA_CAMERA_SHIP;
		Crosshair.OutsideCamera = true;
		Sailors.IsOnDeck = 0;
		DeleteClass(&Telescope);
		SeaCameras_UpdateCamera();
		SendMessage(&objISpyGlass, "ll", MSG_TELESCOPE_REQUEST,0); // выключить телескоп
	}
	//Убрать конусы стрельбы
	SendMessage(&AISea, "lllllffl", AI_MESSAGE_CANNONS_RANGE, argb(0,255,255,255), argb(25,255,255,255), argb(0,255,0,0), argb(75,255,0,0), 0.002, 0.002, false);
}

bool SeaCameras_isCameraOutside()
{
	if (SeaCameras.Camera == SEA_CAMERA_SHIP) return true;
	if (SeaCameras.Camera == SEA_CAMERA_FREE) return true;
	if (SeaCameras.Camera == SEA_CAMERA_DECK) return true;
	return false;
}

void SeaCameras_SetShipForSeaCamera(object Character)
{
	makeref(SeaShipCharacterForCamera, Character);
	SeaCameras_UpdateCamera();
}

void GetFireCameraBort(ref sBort, ref fAng)
{
	float fAngTemp = fAng;

	if(!CheckAttribute(SeaFireCamera, "LastCamera"))
		SeaFireCamera.LastCamera = SEA_CAMERA_SHIP;
	switch(SeaFireCamera.LastCamera)
	{
		case SEA_CAMERA_SHIP:
			SendMessage(&SeaShipCamera, "le", MSG_SHIP_CAMERA_GET_AY, &fAngTemp);
			fAngTemp += PI;
		break;
		case SEA_CAMERA_DECK:
			SendMessage(&SeaDeckCamera, "le", MSG_DECK_CAMERA_GET_AY, &fAngTemp);
		break;
	}
	while(fAngTemp > PI)
		fAngTemp -= PIm2;
	while(fAngTemp < -PI)
		fAngTemp += PIm2;
	fAng = fAngTemp;

	float PI_m5d6 = PI*5.0/6.0;
	if(fAng > -PId6 && fAng < PId6)
	{
		sBort = "f";
		return;
	}
	if(fAng > PId6 && fAng < PI_m5d6)
	{
		sBort = "r";
		return;
	}
	if(fAng > -PI_m5d6 && fAng < -PId6)
	{
		sBort = "l";
		return;
	}
	sBort = "b";
}

#event_handler("GetCurBort", "GetCurBort");
string GetCurBort()
{
	if(CheckAttribute(SeaFireCamera, "Bort"))
		return "cannon" + SeaFireCamera.Bort;
	return "cannonr";
}

#event_handler("FireCamera_UpdateAttributes", "FireCamera_UpdateAttributes");
void FireCamera_UpdateAttributes()
{
	makearef(Crosshair, SeaCameras.Crosshair);

	float fCannons = stf(pchar.TmpSkill.Cannons);
	float fAccuracy = stf(pchar.TmpSkill.Accuracy);
	float fCrewExp = stf(GetCrewExp(pchar, "Cannoners"));
	float kCrewExp = Bring2Range(0.8, 1.2, 1.0, 100.0, fCrewExp);

	float fCannonPerk = 1.0; // увеличиваем скорость сведения от перка
	if (CheckOfficersPerk(pchar, "CannonProfessional")) fCannonPerk += 0.10;

	//скорость движения прицельных кружков
	Crosshair.DistSpeed = Bring2Range(45.0, 80.0, 0.01, 1.0, fCannons) * kCrewExp * fCannonPerk; //дистанция
	Crosshair.AySpeed = Bring2Range(0.1, 0.15, 0.01, 1.0, fCannons) * kCrewExp * fCannonPerk; //угол (горизонталь)
	Crosshair.HeightSpeed = Bring2Range(4.5, 8.0, 0.01, 1.0, fCannons) * kCrewExp * fCannonPerk; //высота

	//плотность сведения
	float maxDensity = 0.65;
	if (IsEquipCharacterByItem(pchar, "hat4")) maxDensity = 0.75;

	Crosshair.Density = Bring2Range(0.2, maxDensity, 0.01, 1.0, fAccuracy); //0 - не сводятся, 1 - в точку.
	Crosshair.DensitySpeed = Bring2Range(0.45, 2.5, 0.01, 1.0, fAccuracy) * kCrewExp; //скорость досведения

	//флуктуации - коэффициенты влияния. Расчитываются на основе дельты при превышении порога
	Crosshair.FluctuationDistToDist = Bring2Range(0.0022, 0.0007, 0.01, 1.0, fAccuracy);
	Crosshair.FluctuationDistToAy = Bring2Range(0.00075, 0.0003, 0.01, 1.0, fAccuracy);
	Crosshair.FluctuationDistToHeight = Bring2Range(0.00015, 0.00008, 0.01, 1.0, fAccuracy);

	Crosshair.FluctuationAyToDist = Bring2Range(85.0, 35.0, 0.01, 1.0, fAccuracy);
	Crosshair.FluctuationAyToAy = Bring2Range(10.5, 4.25, 0.01, 1.0, fAccuracy);
	Crosshair.FluctuationAyToHeight = Bring2Range(48.0, 25.0, 0.01, 1.0, fAccuracy);

	Crosshair.FluctuationHeightToDist = 0.0;
	Crosshair.FluctuationHeightToAy = Bring2Range(0.04, 0.015, 0.01, 1.0, fAccuracy);
	Crosshair.FluctuationHeightToHeight = Bring2Range(0.04, 0.007, 0.01, 1.0, fAccuracy);
}

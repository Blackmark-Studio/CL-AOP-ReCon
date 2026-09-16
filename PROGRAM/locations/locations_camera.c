#define LOCCAMERA_FOLLOW	1
#define LOCCAMERA_TOPOS		2
#define LOCCAMERA_FREE		3

// Hokkins: радиус наземной камеры -->
#define DEFAULT_CAM_RAD 3.0
#define DEFAULT_CAM_RAD_DEN 0.22

// Warship 20.07.09 Новое
#define LOCCAMERA_MAX_STATES 15
#define LOCCAMERA_ROTATE "Rotate"
#define LOCCAMERA_FLYTOPOS "FlyToPosition"
#define LOCCAMERA_NEARHERO "LockNearHero"
// AlexBlade - новый тип камеры - плавная смена целевой точки камеры
#define LOCCAMERA_LOOKFROMTOANGLE "LookFromToAngle"

// evganat - меняем целевую точку камеры
#define LOCCAMERA_LOOKTOHERO "LookToHero"
#define LOCCAMERA_LOOKTOPOINT "LookToPoint"
#define LOCCAMERA_LOOKTOANGLE "LookToAngle"
#define LOCCAMERA_FLYUPROTATE_LOOKY "FlyUpRotateLookY"
#define LOCCAMERA_FLYTOPOS_ROTATE "FlyToPositionRotate"
#event_handler("frame", "locCameraDelayUpdate");
#event_handler("frame", "locCameraUpdate");

object objLocCameraStates[LOCCAMERA_MAX_STATES];
int iLocCameraCurState = -1;

int locCameraCurMode;
int LocCameraOldSaveState = 1;
bool locCameraEnableSpecialMode;
bool locCameraEnableFree;
bool LocCameraSaveLocked = false;

void locCameraInit()
{
	locCameraEnableFree = false;
	locCameraEnableSpecialMode = false;
	//locCameraEnableFree = true;
	locCameraCurMode = LOCCAMERA_FOLLOW;
}

void locCameraSetRadius(float fRadius)
{
	SendMessage(&locCamera, "lf", MSG_CAMERA_SET_RADIUS, fRadius);
}

//Set camera follow mode
bool locCameraFollow()
{
	return locCameraFollowEx(false);
}

bool locCameraFollowEx(bool isTeleport)
{
	if(IsEntity(&locCamera) == 0) return false;
	bool res;
	if(isTeleport)
		res = SendMessage(&locCamera, "ll", MSG_CAMERA_FOLLOW, isTeleport);
	else
		res = SendMessage(&locCamera, "l", MSG_CAMERA_FOLLOW);
	locCameraCurMode = LOCCAMERA_FOLLOW;
	locCameraSetFollowCamAngleToCharacterAngle();
	return res;
}

void locCameraSetFollowCamAngleToCharacterAngle()
{
	SendMessage(&locCamera, "l", -8);
}

//Set camera toPos mode
bool locCameraToPos(float x, float y, float z, bool isTeleport)
{
	return locCameraToPosEx(x, y, z, isTeleport, 1.0);
}

bool locCameraToPosEx(float x, float y, float z, bool isTeleport, float fMorphSpeed)
{
	if(IsEntity(&locCamera) == 0) return false;
	if(locCameraEnableFree == true) return true;
	int delta = GetDeltaTime();
	fMorphSpeed *= delta * 0.02;
	bool res = SendMessage(&locCamera, "lffflf", MSG_CAMERA_TOPOS, x, y, z, isTeleport, fMorphSpeed);
	locCameraCurMode = LOCCAMERA_TOPOS;
	return res;
}

//Set camera move mode (speed meter per second)
bool locCameraFree()
{
	if(IsEntity(&locCamera) == 0) return false;
	bool res = SendMessage(&locCamera, "l", MSG_CAMERA_FREE);
	locCameraCurMode = LOCCAMERA_FREE;
	return res;
}

//
bool locCameraLock(float ax)
{
	if(IsEntity(&locCamera) == 0) return false;
	bool res = SendMessage(&locCamera, "lf", MSG_CAMERA_MOVE, ax);
	return res;
}


void locCameraSleep(bool isSleep)
{
	SendMessage(&locCamera, "ll", MSG_CAMERA_SLEEP, isSleep);
}

void locCameraSwitch()
{
	if(locCameraEnableFree == false)
	{
		LAi_CharacterEnableDialog(pchar);
		return;
	}
	LAi_CharacterDisableDialog(pchar);
	string controlName = GetEventData();
	if(controlName != "ChrCamCameraSwitch") return;
	if(locCameraCurMode != LOCCAMERA_FREE)
	{
		locCameraFree();
	}else{
		locCameraFollow();
	}
}

void locCameraSetSpecialMode(bool isEnable)
{
	locCameraEnableSpecialMode = isEnable;
}

#event_handler("EventGetSpecialMode", "locCameraGetSpecialMode");
int locCameraGetSpecialMode()
{
	return false;
}   
void LoadTrackCamera(string sTrackName,float fTrackTime,aref arTrackPause)
{
	SendMessage(&locCamera, "lsfa", -2, sTrackName, fTrackTime, arTrackPause);
}

void TurnOffTrackCamera()
{
	SendMessage(&locCamera, "l", -3);
}
// boal -->
void locCameraTarget(ref _char)
{
    SendMessage(&locCamera, "li", MSG_CAMERA_SETTARGET, _char);
}
// boal <--	 
// TODO нет в ядре  
bool locCameraFromToPos(float from_x,float from_y,float from_z, bool isTeleport, float to_x,float to_y,float to_z)
{
	if(IsEntity(&locCamera) == 0)
		return false;
	if(locCameraEnableFree == true)
		return true;
	bool res = SendMessage(&locCamera, "lffflfffl", -4, from_x, from_y, from_z, isTeleport, to_x, to_y, to_z, true);
	locCameraCurMode = LOCCAMERA_TOPOS;
	return res;
}

bool locCameraFromToPosEx(float from_x, float from_y, float from_z, bool isTeleport, float to_x, float to_y, float to_z, bool targetChr)
{
	if(IsEntity(&locCamera) == 0)
		return false;
	if(locCameraEnableFree == true)
		return true;
	bool res = SendMessage(&locCamera, "lffflfffl", -4, from_x, from_y, from_z, isTeleport, to_x, to_y, to_z, targetChr);
	locCameraCurMode = LOCCAMERA_TOPOS;
	return res;
}

// AlexBlade - Альтернатива locCameraFromToPos, конечная позиция определяется через углы поворота.
// Значения углов можно получить через дебаг меню ("Дамп атрибутов камеры").
bool locCameraFromToAngle(float from_x,float from_y,float from_z, bool isTeleport, float xAng, float yAng)
{
    float to_x, to_y, to_z;
    float mult = 400.0;
    float chrModelHeight = 1.8;
    if (CheckAttribute(pchar, "model.height"))
    {
        chrModelHeight = stf(pchar.model.height);
    }

    object _rmtx1; aref _rmtx1_aref; makearef(_rmtx1_aref, _rmtx1);
    CreateRotationMatrixZXY(xAng, yAng, 0.0, _rmtx1_aref);

    to_x = from_x + mult * stf(_rmtx1_aref.vz.x);
    to_y = from_y + mult * stf(_rmtx1_aref.vz.y) - 0.8 * chrModelHeight;
    to_z = from_z + mult * stf(_rmtx1_aref.vz.z);
//    Log_Info(to_x + "," + to_y + "," + to_z);
//    Log_Info("vz.x:" + stf(_rmtx1_aref.vz.x) + ", vz.y:" + stf(_rmtx1_aref.vz.y) + ", vz.z:" + stf(_rmtx1_aref.vz.z));

	return locCameraFromToPos(from_x,from_y,from_z, isTeleport, to_x, to_y, to_z);
}

// andre39966 - locCameraFlyUpRotateLookY - подъём камеры с вращением
// _x, _y, _z   - стартовая позиция камеры
// _angY        - стартовый угол, в градусах
// _height      - на сколько метров нужно подняться
// _rotateY     - на сколько градусов камера будет поворачиваться
// _lookDist    - дистанция точки взгляда
// _lookY       - фиксированная высота взгляда
// _time        - длительность в секундах

bool locCameraFlyUpRotateLookY(float _x, float _y, float _z, float _angY, float _height, float _rotateY, float _lookDist, float _lookY, float _time)
{
	ref curCameraState;
	int cameraCurState;

	if (IsEntity(&locCamera) == 0) return false;
	if (locCameraEnableFree == true) return true;
	if (_time <= 0.0) return false;

	cameraCurState = locCameraGetFirstEmptyState();
	if (cameraCurState == -1) return false;

	curCameraState = &objLocCameraStates[cameraCurState];

	curCameraState.startCameraX = _x;
	curCameraState.startCameraY = _y;
	curCameraState.startCameraZ = _z;

	curCameraState.curCameraX = _x;
	curCameraState.curCameraY = _y;
	curCameraState.curCameraZ = _z;

	curCameraState.startAngY = _angY;
	curCameraState.height = _height;
	curCameraState.rotateY = _rotateY;
	curCameraState.lookDist = _lookDist;
	curCameraState.lookY = _lookY;

	curCameraState.totalTime = _time;
	curCameraState.curTime = 0.0;
	curCameraState.time = -1.0;

	curCameraState.type = LOCCAMERA_FLYUPROTATE_LOOKY;

	if (iLocCameraCurState == -1) iLocCameraCurState = cameraCurState;

	return true;
}

// Hokkins: радиус наземной камеры -->
float CalcLandRadius()
{
    float fCamRadAdj = 0.0;
    if(CheckAttribute(&InterfaceStates, "RadDetails"))
       fCamRadAdj = stf(InterfaceStates.RadDetails) / DEFAULT_CAM_RAD_DEN;

    return (DEFAULT_CAM_RAD + fCamRadAdj);
}
// Hokkins: радиус наземной камеры <--

/////////////////////////////////////////////////////////////////////////////////////////
//							Warship 20.07.09 НОВОЕ - СНИМАЕМ КИНО
/////////////////////////////////////////////////////////////////////////////////////////

// Функция запуска вращения камеры вокруг персонажа.
// Параметры:
// float  _offsetX ... _offsetZ - смещение камеры относительно текущей позиции персонажа
// float _rotateX, _rotateY - скорость фращения по данной оси, от 0.01 и меньше до 0.3, может быть отрицательна
// float _radius - радиус, он же дистанция от начальных точек до камеры
// float _startAngle- начальный угол, откуда крутим
// int _time - время вращения В КАДРАХ. Она секунда - в среднем 30 кадров, но если учитывать тормоза, то может быть и 10
// bool _teleport - если true, переместится в заданную точку мгновенно, иначе - плавный полет
bool locCameraRotateAroundHero(float _offsetX, float _offsetY, float _offsetZ, float _rotateX, float _rotateY,  float _radius, float _startAngle, int _time)
{
	ref curCameraState;
	int cameraCurState = locCameraGetFirstEmptyState();
	float charX, charY, charZ;
	
	if(cameraCurState == -1 || !GetCharacterPos(PChar, &charX, &charY, &charZ)) return false;
	
	curCameraState = &objLocCameraStates[cameraCurState];
	curCameraState.curCameraX = charX + _offsetX;
	curCameraState.curCameraY = charY + _offsetY;
	curCameraState.curCameraZ = charZ + _offsetZ;
	curCameraState.offsetX = _offsetX;
	curCameraState.offsetY = _offsetY;
	curCameraState.offsetZ = _offsetZ;
	curCameraState.rotateX = _rotateX;
	curCameraState.rotateY = _rotateY;
	curCameraState.rotateRadius = _radius;
	curCameraState.time = _time;
	curCameraState.angle = _startAngle;
	curCameraState.type = LOCCAMERA_ROTATE; // Тип камеры
	
	if(iLocCameraCurState == -1) iLocCameraCurState = 0;
	
	return true;
}

bool locCameraSetSpeedpoint(int spNum, float accel, float timer)
{
	if(iLocCameraCurState == -1)
		return false;
	
	ref curCameraState = &objLocCameraStates[iLocCameraCurState];
	string sPoint = "point" + spNum;
	curCameraState.speedpoints.(sPoint).timer = timer;
	curCameraState.speedpoints.(sPoint).accel = accel * GetRealDeltaTime() / timer;
}

void locCameraSetCurSpeedpoint(int spNum)
{
	if(iLocCameraCurState == -1)
		return;
	ref curCameraState = &objLocCameraStates[iLocCameraCurState];
	if(!CheckAttribute(curCameraState, "speedpoints"))
		return;
	
	curCameraState.speedpoints.cur = spNum;
}

// Полет камеры от начальных точек _startX ... _startZ до конечных точек _endX ... _endZ
// float _speed - множитель скорости в режиме полета _time == -1. Если _speed == 1, то это стандартная скорость
// int _time - кол-во кадров, за которое должно долететь. Если -1, то высчитывается исходя из расстояния
// bool _fromCurCameraPos - если true, то при переходе на эту функци полета, начальная позиция будет считаться как текущая позиция камеры
void locCameraFlyToPosition(ref curCameraState, float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _speed, int _time)
{
	float distance = GetDistance3D(_startX, _startY, _startZ, _endX, _endY, _endZ);

	curCameraState.curCameraX = _startX;
	curCameraState.curCameraY = _startY;
	curCameraState.curCameraZ = _startZ;
	curCameraState.endCameraX = _endX;
	curCameraState.endCameraY = _endY;
	curCameraState.endCameraZ = _endZ;
	
	if(_time == -1)
	{
		curCameraState.speedX = (_endX - _startX) / (distance * (1 / _speed));
		curCameraState.speedY = (_endY - _startY) / (distance * (1 / _speed));
		curCameraState.speedZ = (_endZ - _startZ) / (distance * (1 / _speed));
	}
	else
	{
		curCameraState.speedX = (_endX - _startX) / _time;
		curCameraState.speedY = (_endY - _startY) / _time;
		curCameraState.speedZ = (_endZ - _startZ) / _time;
	}
	
	curCameraState.speed = _speed;
	curCameraState.time = _time;
	curCameraState.type = LOCCAMERA_FLYTOPOS; // Тип камеры
	
	if(iLocCameraCurState == -1) iLocCameraCurState = 0;
}

void locCameraLookFromToAngle(ref curCameraState, float _startX, float _startY, float _startZ, float _startAX, float _startAY, float _endAX, float _endAY, int _time)
{
	curCameraState.curCameraX = _startX;
	curCameraState.curCameraY = _startY;
	curCameraState.curCameraZ = _startZ;

	curCameraState.speedX = (_endAX - _startAX) / _time;
	curCameraState.speedY = (_endAY - _startAY) / _time;
	curCameraState.speedZ = 0.0;

	curCameraState.speed = 1.0;
	curCameraState.time = _time;
	curCameraState.type = LOCCAMERA_LOOKFROMTOANGLE; // Тип камеры

	if(iLocCameraCurState == -1) iLocCameraCurState = 0;
}


bool locCameraFlyToPositionLookToHero(float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _speed, int _time)
{
	int iCameraCurState = locCameraGetFirstEmptyState();
	if(iCameraCurState == -1)
		return false;
	ref curCameraState = &objLocCameraStates[iCameraCurState];
	locCameraFlyToPosition(curCameraState, _startX, _startY, _startZ, _endX, _endY, _endZ, _speed, _time);
	curCameraState.lookTo = LOCCAMERA_LOOKTOHERO;	// смотрим на ГГ
	return true;
}

bool locCameraFlyToPositionLookToPoint(float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _lookToX, float _lookToY, float _lookToZ, float _speed, int _time)
{
	int iCameraCurState = locCameraGetFirstEmptyState();
	if(iCameraCurState == -1)
		return false;
	ref curCameraState = &objLocCameraStates[iCameraCurState];
	locCameraFlyToPosition(curCameraState, _startX, _startY, _startZ, _endX, _endY, _endZ, _speed, _time);
	curCameraState.lookTo = LOCCAMERA_LOOKTOPOINT;	// смотрим на точку
	curCameraState.lookTo.x = _lookToX;
	curCameraState.lookTo.y = _lookToY;
	curCameraState.lookTo.z = _lookToZ;
	return true;
}

// andre39966 - locCameraFlyToPositionRotate - перемещение камеры между двумя точками с регулируемым поворотом вокруг своей оси
// _startX, _startY, _startZ - стартовая позиция камеры
// _endX, _endY, _endZ       - конечная позиция камеры
// _startAX                   - стартовый угол наклона камеры по вертикали, в градусах
// _startAY                   - стартовый угол поворота камеры по горизонтали, в градусах
// _endAX                     - конечный угол наклона камеры по вертикали, в градусах
// _endAY                     - конечный угол поворота камеры по горизонтали, в градусах
// _delayTimeSec              - задержка перед началом движения, в секундах
// _flyTimeSec                - длительность перемещения, в секундах
// _rotateTimeSec             - длительность поворота, в секундах
bool locCameraFlyToPositionRotate(float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _startAX, float _startAY, float _endAX, float _endAY, float _delayTimeSec, float _flyTimeSec, float _rotateTimeSec)
{
	ref curCameraState;
	int cameraCurState;

	if (IsEntity(&locCamera) == 0) return false;
	if (locCameraEnableFree == true) return true;
	if (_delayTimeSec < 0.0 || _flyTimeSec <= 0.0 || _rotateTimeSec <= 0.0) return false;

	cameraCurState = locCameraGetFirstEmptyState();
	if (cameraCurState == -1) return false;

	if (!locCameraSaveLocked)
	{
		locCameraOldSaveState = sti(InterfaceStates.Buttons.Save.enable);
		InterfaceStates.Buttons.Save.enable = 0;
		locCameraSaveLocked = true;
	}

	curCameraState = &objLocCameraStates[cameraCurState];

	curCameraState.startCameraX = _startX;
	curCameraState.startCameraY = _startY;
	curCameraState.startCameraZ = _startZ;

	curCameraState.endCameraX = _endX;
	curCameraState.endCameraY = _endY;
	curCameraState.endCameraZ = _endZ;

	curCameraState.curCameraX = _startX;
	curCameraState.curCameraY = _startY;
	curCameraState.curCameraZ = _startZ;

	curCameraState.startAX = _startAX;
	curCameraState.startAY = _startAY;
	curCameraState.endAX = _endAX;
	curCameraState.endAY = _endAY;

	curCameraState.delayTime = _delayTimeSec;
	curCameraState.flyTime = _flyTimeSec;
	curCameraState.rotateTime = _rotateTimeSec;
	curCameraState.curTime = 0.0;

	curCameraState.time = -1.0;
	curCameraState.type = LOCCAMERA_FLYTOPOS_ROTATE;

	if (iLocCameraCurState == -1) iLocCameraCurState = cameraCurState;

	return true;
}

// То же, что и выше, только с возможностью задержки в начале, плавным стартом и концом
// _delaySec    - задержка перед началом полёта в секундах.
// _timeSec     - длительность самого полёта в секундах.
bool locCameraFlyToPositionLookToPointDelay(float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _lookToX, float _lookToY, float _lookToZ, float _speed, float _delaySec, float _timeSec)
{
	if (!locCameraSaveLocked)
	{
		locCameraOldSaveState = sti(InterfaceStates.Buttons.Save.enable);
		InterfaceStates.Buttons.Save.enable = 0;
		locCameraSaveLocked = true;
	}

	pchar.questTemp.LocCameraDelay.stage = "delay";

	pchar.questTemp.LocCameraDelay.startX = _startX;
	pchar.questTemp.LocCameraDelay.startY = _startY;
	pchar.questTemp.LocCameraDelay.startZ = _startZ;

	pchar.questTemp.LocCameraDelay.endX = _endX;
	pchar.questTemp.LocCameraDelay.endY = _endY;
	pchar.questTemp.LocCameraDelay.endZ = _endZ;

	pchar.questTemp.LocCameraDelay.lookToX = _lookToX;
	pchar.questTemp.LocCameraDelay.lookToY = _lookToY;
	pchar.questTemp.LocCameraDelay.lookToZ = _lookToZ;

	pchar.questTemp.LocCameraDelay.delay = _delaySec;
	pchar.questTemp.LocCameraDelay.time = _timeSec;
	pchar.questTemp.LocCameraDelay.curTime = 0.0;

	Pchar.FuncCameraFly = "";

	locCameraFromToPosEx(_startX, _startY, _startZ, true, _lookToX, _lookToY, _lookToZ, false);

	return true;
}

// andre39966 - locCameraFlyUpRotateLookYDelay - подъём камеры с вращением и задержкой перед началом
// _x, _y, _z - стартовая позиция камеры
// _angY      - стартовый угол, в градусах
// _height    - на сколько метров нужно подняться
// _rotateY   - на сколько градусов камера будет поворачиваться
// _lookDist  - дистанция точки взгляда
// _lookY     - фиксированная высота взгляда
// _timeSec   - длительность движения, в секундах
// _delaySec  - задержка перед началом движения, в секундах
bool locCameraFlyUpRotateLookYDelay(float _x, float _y, float _z, float _angY, float _height, float _rotateY, float _lookDist, float _lookY, float _timeSec, float _delaySec)
{
	float radians;

	if (!locCameraSaveLocked)
	{
		locCameraOldSaveState = sti(InterfaceStates.Buttons.Save.enable);
		InterfaceStates.Buttons.Save.enable = 0;
		locCameraSaveLocked = true;
	}

	pchar.questTemp.LocCameraDelay.type = "FlyUpRotate";
	pchar.questTemp.LocCameraDelay.stage = "delay";

	pchar.questTemp.LocCameraDelay.startX = _x;
	pchar.questTemp.LocCameraDelay.startY = _y;
	pchar.questTemp.LocCameraDelay.startZ = _z;

	pchar.questTemp.LocCameraDelay.angY = _angY;
	pchar.questTemp.LocCameraDelay.height = _height;
	pchar.questTemp.LocCameraDelay.rotateY = _rotateY;
	pchar.questTemp.LocCameraDelay.lookDist = _lookDist;
	pchar.questTemp.LocCameraDelay.lookY = _lookY;

	pchar.questTemp.LocCameraDelay.delay = _delaySec;
	pchar.questTemp.LocCameraDelay.time = _timeSec;
	pchar.questTemp.LocCameraDelay.curTime = 0.0;

	radians = _angY * 0.01745329252;

	locCameraFromToPosEx(_x, _y, _z, true, _x + sin(radians) * _lookDist, _lookY, _z + cos(radians) * _lookDist, false);

	return true;
}

void locCameraDelayUpdate()
{
	bool isFlyUpRotate;
	float dltTime, delay, curTime, totalTime, k;
	float startX, startY, startZ;
	float endX, endY, endZ;
	float lookToX, lookToY, lookToZ;
	float cameraX, cameraY, cameraZ;
	float angY, height, rotateY, lookDist, fixedLookY, radians;
	string sQuest;

	if (!CheckAttribute(pchar, "questTemp.LocCameraDelay")) return;

	isFlyUpRotate = CheckAttribute(pchar, "questTemp.LocCameraDelay.type") && pchar.questTemp.LocCameraDelay.type == "FlyUpRotate";

	dltTime = GetRealDeltaTime();
	if (isFlyUpRotate) dltTime = dltTime * (1.0 + TimeScaleCounter * 0.25);

	startX = stf(pchar.questTemp.LocCameraDelay.startX);
	startY = stf(pchar.questTemp.LocCameraDelay.startY);
	startZ = stf(pchar.questTemp.LocCameraDelay.startZ);

	if (isFlyUpRotate)
	{
		angY = stf(pchar.questTemp.LocCameraDelay.angY);
		height = stf(pchar.questTemp.LocCameraDelay.height);
		rotateY = stf(pchar.questTemp.LocCameraDelay.rotateY);
		lookDist = stf(pchar.questTemp.LocCameraDelay.lookDist);
		fixedLookY = stf(pchar.questTemp.LocCameraDelay.lookY);

		radians = angY * 0.01745329252;

		lookToX = startX + sin(radians) * lookDist;
		lookToY = fixedLookY;
		lookToZ = startZ + cos(radians) * lookDist;
	}
	else
	{
		endX = stf(pchar.questTemp.LocCameraDelay.endX);
		endY = stf(pchar.questTemp.LocCameraDelay.endY);
		endZ = stf(pchar.questTemp.LocCameraDelay.endZ);

		lookToX = stf(pchar.questTemp.LocCameraDelay.lookToX);
		lookToY = stf(pchar.questTemp.LocCameraDelay.lookToY);
		lookToZ = stf(pchar.questTemp.LocCameraDelay.lookToZ);
	}

	if (pchar.questTemp.LocCameraDelay.stage == "delay")
	{
		locCameraFromToPosEx(startX, startY, startZ, true, lookToX, lookToY, lookToZ, false);

		delay = stf(pchar.questTemp.LocCameraDelay.delay) - dltTime;
		pchar.questTemp.LocCameraDelay.delay = delay;

		if (delay > 0.0) return;

		pchar.questTemp.LocCameraDelay.stage = "fly";
		pchar.questTemp.LocCameraDelay.curTime = 0.0;
		return;
	}

	curTime = stf(pchar.questTemp.LocCameraDelay.curTime) + dltTime;
	totalTime = stf(pchar.questTemp.LocCameraDelay.time);

	if (totalTime <= 0.0) totalTime = 0.1;

	k = curTime / totalTime;

	if (k < 0.0) k = 0.0;
	if (k > 1.0) k = 1.0;

	if (isFlyUpRotate)
	{
		k = k * k * k * (k * (k * 6.0 - 15.0) + 10.0);
	}
	else
	{
		k = k * k * (3.0 - 2.0 * k);
	}

	if (isFlyUpRotate)
	{
		cameraX = startX;
		cameraY = startY + height * k;
		cameraZ = startZ;

		radians = (angY + rotateY * k) * 0.01745329252;

		lookToX = cameraX + sin(radians) * lookDist;
		lookToY = fixedLookY;
		lookToZ = cameraZ + cos(radians) * lookDist;
	}
	else
	{
		cameraX = startX + (endX - startX) * k;
		cameraY = startY + (endY - startY) * k;
		cameraZ = startZ + (endZ - startZ) * k;
	}

	locCameraFromToPosEx(cameraX, cameraY, cameraZ, true, lookToX, lookToY, lookToZ, false);

	pchar.questTemp.LocCameraDelay.curTime = curTime;

	if (curTime < totalTime) return;

	if (isFlyUpRotate)
	{
		sQuest = "";
		if (CheckAttribute(Pchar, "FuncCameraFly")) sQuest = Pchar.FuncCameraFly;

		DeleteAttribute(pchar, "questTemp.LocCameraDelay");
		Pchar.FuncCameraFly = "";

		if (locCameraSaveLocked)
		{
			InterfaceStates.Buttons.Save.enable = locCameraOldSaveState;
			locCameraSaveLocked = false;
		}

		if (sQuest != "") call sQuest();
	}
	else
	{
		sQuest = "";
		if (CheckAttribute(Pchar, "FuncCameraFly")) sQuest = Pchar.FuncCameraFly;

		locCameraFromToPosEx(endX, endY, endZ, true, lookToX, lookToY, lookToZ, false);

		DeleteAttribute(pchar, "questTemp.LocCameraDelay");
		Pchar.FuncCameraFly = "";

		if (sQuest != "") call sQuest();
	}
}

bool locCameraFlyToPositionLookToOffset(float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _offsetX, float _offsetY, float _offsetZ, float _speed, int _time)
{
	int iCameraCurState = locCameraGetFirstEmptyState();
	if(iCameraCurState == -1)
		return false;
	ref curCameraState = &objLocCameraStates[iCameraCurState];
	locCameraFlyToPosition(curCameraState, _startX, _startY, _startZ, _endX, _endY, _endZ, _speed, _time);
	curCameraState.lookTo = LOCCAMERA_LOOKTOANGLE;	// смотрим под углом
	curCameraState.lookTo.offsetX = _offsetX;
	curCameraState.lookTo.offsetY = _offsetY;
	curCameraState.lookTo.offsetZ = _offsetZ;
	return true;
}

bool locCameraFlyToPositionLookToAngle(float _startX, float _startY, float _startZ, float _endX, float _endY, float _endZ, float _ax, float _ay, float _speed, int _time)
{
	int iCameraCurState = locCameraGetFirstEmptyState();
	if(iCameraCurState == -1)
		return false;
	ref curCameraState = &objLocCameraStates[iCameraCurState];
	locCameraFlyToPosition(curCameraState, _startX, _startY, _startZ, _endX, _endY, _endZ, _speed, _time);
	curCameraState.lookTo = LOCCAMERA_LOOKTOANGLE;	// смотрим под углом
	float ax = _ax * PI / 180.0;
	float ay = _ay * PI / 180.0;
	curCameraState.lookTo.offsetX = cos(ax) * sin(ay);
	curCameraState.lookTo.offsetY = sin(ax);
	curCameraState.lookTo.offsetZ = cos(ax) * cos(ay);
	return true;
}

bool locCameraFlyLookFromToAngle(float _startX, float _startY, float _startZ, float _startAx, float _startAy, float _endAx, float _endAy, int _time)
{
	int iCameraCurState = locCameraGetFirstEmptyState();
	if(iCameraCurState == -1)
		return false;
	ref curCameraState = &objLocCameraStates[iCameraCurState];
	locCameraLookFromToAngle(curCameraState, _startX, _startY, _startZ, _startAx, _startAy, _endAx, _endAy, _time);

	curCameraState.lookTo = LOCCAMERA_LOOKTOANGLE;
	curCameraState.lookTo.ax = _startAx;
	curCameraState.lookTo.ay = _startAy;
	return true;
}

// Фиксирование камеры в определённой точке относительно ГГ
// float _offsetX ... _offsetZ - смещение относительно координат ГГ, для определения точки, где будет находиться камера
// int _time - кол-во кадров, сколько будет висеть. Если -1 - будет висеть вечно
// bool _canRotate - если true, то камера будет крутиться вместе с персонажем
bool locCameraLockNearHero(float _offsetX, float _offsetY, float _offsetZ, int _time, bool _canRotate)
{
	ref curCameraState;
	int cameraCurState = locCameraGetFirstEmptyState();
	float charX, charY, charZ, offsetAY;
	
	if(cameraCurState == -1 || !GetCharacterPos(PChar, &charX, &charY, &charZ)) return false;
	
	offsetAY = atan2(_offsetZ, _offsetX);
	
	if(_offsetX > 0 && _offsetZ > 0)
	{
		offsetAY = offsetAY + PI;
	}
	
	curCameraState = &objLocCameraStates[cameraCurState];
	curCameraState.curCameraX = charX;
	curCameraState.curCameraY = charY;
	curCameraState.curCameraZ = charZ;
	curCameraState.offsetX = _offsetX;
	curCameraState.offsetY = _offsetY;
	curCameraState.offsetZ = _offsetZ;
	curCameraState.time = _time;
	curCameraState.canRotate = _canRotate;
	curCameraState.offsetAY = offsetAY;
	curCameraState.type = LOCCAMERA_NEARHERO; // Тип камеры
	
	if(iLocCameraCurState == -1) iLocCameraCurState = 0;
	
	return true;
}

int locCameraGetFirstEmptyState()
{
	for(int i = 0; i < LOCCAMERA_MAX_STATES; i++)
	{
		if(!CheckAttribute(&objLocCameraStates[i], "time"))
		{
			return i;
		}
	}
	
	return -1;
}

// Переход к следующей функции установки камеры
// Последовательность методов задается, например, так:
// locCameraRotateAroundHero(0.0, 1.0, 0.0, 0.03, 0.0, 3.0, 0.0, 200);
// locCameraRotateAroundHero(0.0, 1.0, 0.0, 0.0, 0.01, 5.0, 0.0, 150);
// locCameraRotateAroundHero(0.0, 1.0, 0.0, -0.03, 0.03, 7.0, 0.0, 225);
// В результате получаем последовательные полеты камеры
void locCameraNextState()
{
	if (CheckAttribute(PChar, "FuncCameraFly"))
	{
		string func = Pchar.FuncCameraFly;

		if (locCameraSaveLocked)
		{
			InterfaceStates.Buttons.Save.enable = locCameraOldSaveState;
			locCameraSaveLocked = false;
		}

		locCameraResetState();

		if (func != "") call func();
		return;
	}

	ref prevCamera, curCamera;
	float distance;
	int time;

	prevCamera = &objLocCameraStates[iLocCameraCurState];

	if (prevCamera.type == LOCCAMERA_FLYTOPOS_ROTATE && locCameraSaveLocked)
	{
		InterfaceStates.Buttons.Save.enable = locCameraOldSaveState;
		locCameraSaveLocked = false;
	}

	DeleteAttribute(prevCamera, "time");
	iLocCameraCurState++;

	curCamera = &objLocCameraStates[iLocCameraCurState];

	if (iLocCameraCurState == LOCCAMERA_MAX_STATES || !CheckAttribute(&curCamera, "curCameraX"))
	{
		locCameraResetState();
		return;
	}

	time = sti(curCamera.time);

	Log_TestInfo("locCameraNextState() == " + curCamera.type);
}

// Сброс специальных состояний камеры - привязывание к персонажу
void locCameraResetState()
{
	locCameraFollow();
	
	iLocCameraCurState = -1;
	
	// Потрем все
	for(int i = 0; i < LOCCAMERA_MAX_STATES; i++)
	{
		DeleteAttribute(&objLocCameraStates[i], "");
	}
	//Log_TestInfo("locCameraResetState()");
}

// Обновление позиции камеры при входе в кадр
void locCameraUpdate()
{
	ref curCameraState;
	float charX, charY, charZ, charAY;
	float offsetX, offsetZ;
	float rotateRadius, rotateAngle;
	float time; // Здесь время дробное, т.к. учитывается ещё ускорение времени

	float cameraTime;
	float totalTime;
	float progress;
	float cameraX, cameraY, cameraZ;
	float angleX, angleY;
	float lookX, lookY, lookZ;
	float radians;

	float startX, startY, startZ;
	float endX, endY, endZ;
	float startAX, startAY;
	float endAX, endAY;
	float flyTime, rotateTime;
	float delayTime, activeTime;
	float flyProgress, rotateProgress;

	float accel = 0.0;
	float kSpeedTimer = -1.0;
	string sPoint = "";
	float dltTime = GetRealDeltaTime();
	
	float timeScale = 1 + TimeScaleCounter * 0.25; // Текущее ускорение времени
	
	bool bAoPNPCDialogCamera = false;
	bool bCanUpdateCamera = false;

	if (CheckAttribute(pchar, "questTemp.AoP.NPCDialog.Count"))
	{
		bAoPNPCDialogCamera = true;
	}

	if (!sti(InterfaceStates.Launched))
	{
		bCanUpdateCamera = true;
	}

	if (bAoPNPCDialogCamera)
	{
		bCanUpdateCamera = true;
	}

	if(iLocCameraCurState != -1 && bCanUpdateCamera)
	{
		if(GetCharacterPos(PChar, &charX, &charY, &charZ))
		{
			curCameraState = &objLocCameraStates[iLocCameraCurState];
			
			time = stf(curCameraState.time);
			
			bool bSetPoint = false;
			
			if(CheckAttribute(curCameraState, "speedpoints.cur"))
			{
				sPoint = "point" + curCameraState.speedpoints.cur;
				accel = stf(curCameraState.speedpoints.(sPoint).accel);
				kSpeedTimer = stf(curCameraState.speedpoints.(sPoint).timer);
			}
			
			switch(curCameraState.type)
			{
				case LOCCAMERA_ROTATE:
					rotateRadius = stf(curCameraState.rotateRadius);
					rotateAngle = stf(curCameraState.angle);
					
					// X rotation
					if(stf(curCameraState.rotateX) != 0.0)
					{
						curCameraState.rotateX = stf(curCameraState.rotateX) + accel * dltTime;
						curCameraState.curCameraX = charX + sin(rotateAngle) * rotateRadius + stf(curCameraState.offsetX);
						curCameraState.curCameraZ = charZ + cos(rotateAngle) * rotateRadius + stf(curCameraState.offsetZ);
						curCameraState.angle = rotateAngle + stf(curCameraState.rotateX) * timeScale;
					}
					else // Иначе просто обновление
					{
						curCameraState.curCameraX = charX + stf(curCameraState.offsetX);
						curCameraState.curCameraZ = charZ + stf(curCameraState.offsetZ);
					}
					
					// Y rotation
					if(stf(curCameraState.rotateY) != 0.0)
					{
						curCameraState.rotateY = stf(curCameraState.rotateY) + accel * dltTime;
						curCameraState.curCameraY = charY + cos(rotateAngle) * rotateRadius + stf(curCameraState.offsetY);
						curCameraState.curCameraX = charX + sin(rotateAngle) * rotateRadius + stf(curCameraState.offsetX);
						curCameraState.angle = rotateAngle + stf(curCameraState.rotateY) * timeScale;
					}
					else
					{
						curCameraState.curCameraY = charY + stf(curCameraState.offsetY);
					}
				break;
				
				case LOCCAMERA_FLYTOPOS:
					curCameraState.speedX = stf(curCameraState.speedX) + accel * dltTime;
					curCameraState.speedY = stf(curCameraState.speedY) + accel * dltTime;
					curCameraState.speedZ = stf(curCameraState.speedZ) + accel * dltTime;
					curCameraState.curCameraX = stf(curCameraState.curCameraX) + stf(curCameraState.speedX) * timeScale;
					curCameraState.curCameraY = stf(curCameraState.curCameraY) + stf(curCameraState.speedY) * timeScale;
					curCameraState.curCameraZ = stf(curCameraState.curCameraZ) + stf(curCameraState.speedZ) * timeScale;
					if(CheckAttribute(curCameraState, "lookTo") && curCameraState.lookTo != LOCCAMERA_LOOKTOHERO)
					{
						if(curCameraState.lookTo == LOCCAMERA_LOOKTOANGLE)
						{
							curCameraState.lookTo.x = stf(curCameraState.curCameraX) + stf(curCameraState.lookTo.offsetX);
							curCameraState.lookTo.y = stf(curCameraState.curCameraY) + stf(curCameraState.lookTo.offsetY);
							curCameraState.lookTo.z = stf(curCameraState.curCameraZ) + stf(curCameraState.lookTo.offsetZ);
						}
						//Log_TestInfo("camPos = " + curCameraState.curCameraX + ", " + curCameraState.curCameraY + ", " + curCameraState.curCameraZ + ", lookTo = " + curCameraState.lookTo.x + ", " + curCameraState.lookTo.y + ", " + curCameraState.lookTo.z);
						locCameraFromToPosEx(stf(curCameraState.curCameraX), stf(curCameraState.curCameraY), stf(curCameraState.curCameraZ), true, stf(curCameraState.lookTo.x), stf(curCameraState.lookTo.y), stf(curCameraState.lookTo.z), false);
						bSetPoint = true;
					}
				break;
				
				case LOCCAMERA_NEARHERO:
					offsetX = stf(curCameraState.offsetX);
					offsetZ = stf(curCameraState.offsetZ);
					
					if(sti(curCameraState.canRotate) && GetCharacterAy(PChar, &charAY))
					{
						curCameraState.curCameraX = charX + offsetX * sin(charAY + stf(curCameraState.offsetAY));
						curCameraState.curCameraZ = charZ + offsetZ * cos(charAY + stf(curCameraState.offsetAY));
					}
					else
					{
						curCameraState.curCameraX = charX + offsetX;
						curCameraState.curCameraZ = charZ + offsetZ;
					}
					
					curCameraState.curCameraY = charY + stf(curCameraState.offsetY);
				break;

				case LOCCAMERA_LOOKFROMTOANGLE:
					curCameraState.speedX = stf(curCameraState.speedX) + accel * dltTime;
					curCameraState.speedY = stf(curCameraState.speedY) + accel * dltTime;
					curCameraState.speedZ = stf(curCameraState.speedZ) + accel * dltTime;

					curCameraState.lookTo.ax = stf(curCameraState.lookTo.ax) + stf(curCameraState.speedX) * timeScale;
					curCameraState.lookTo.ay = stf(curCameraState.lookTo.ay) + stf(curCameraState.speedY) * timeScale;

					locCameraFromToAngle(stf(curCameraState.curCameraX), stf(curCameraState.curCameraY), stf(curCameraState.curCameraZ), true, stf(curCameraState.lookTo.ax), stf(curCameraState.lookTo.ay));
					bSetPoint = true;
				break;

				case LOCCAMERA_FLYUPROTATE_LOOKY:
					curCameraState.curTime = stf(curCameraState.curTime) + dltTime * timeScale;

					totalTime = stf(curCameraState.totalTime);
					if (totalTime <= 0.0) totalTime = 1.0;

					progress = stf(curCameraState.curTime) / totalTime;

					if (progress < 0.0) progress = 0.0;
					if (progress > 1.0) progress = 1.0;

					cameraX = stf(curCameraState.startCameraX);
					cameraY = stf(curCameraState.startCameraY) + stf(curCameraState.height) * progress;
					cameraZ = stf(curCameraState.startCameraZ);

					rotateAngle = stf(curCameraState.startAngY) + stf(curCameraState.rotateY) * progress;
					radians = rotateAngle * 0.01745329252;

					lookX = cameraX + sin(radians) * stf(curCameraState.lookDist);
					lookY = stf(curCameraState.lookY);
					lookZ = cameraZ + cos(radians) * stf(curCameraState.lookDist);

					curCameraState.curCameraX = cameraX;
					curCameraState.curCameraY = cameraY;
					curCameraState.curCameraZ = cameraZ;

					locCameraFromToPosEx(cameraX, cameraY, cameraZ, true, lookX, lookY, lookZ, false);
					bSetPoint = true;

					if (progress >= 1.0)
					{
						locCameraNextState();
						return;
					}
				break;

				case LOCCAMERA_FLYTOPOS_ROTATE:
					delayTime = stf(curCameraState.delayTime);
					flyTime = stf(curCameraState.flyTime);
					rotateTime = stf(curCameraState.rotateTime);

					cameraTime = stf(curCameraState.curTime) + dltTime * timeScale;
					curCameraState.curTime = cameraTime;

					startX = stf(curCameraState.startCameraX);
					startY = stf(curCameraState.startCameraY);
					startZ = stf(curCameraState.startCameraZ);

					endX = stf(curCameraState.endCameraX);
					endY = stf(curCameraState.endCameraY);
					endZ = stf(curCameraState.endCameraZ);

					startAX = stf(curCameraState.startAX);
					startAY = stf(curCameraState.startAY);
					endAX = stf(curCameraState.endAX);
					endAY = stf(curCameraState.endAY);

					if (cameraTime < delayTime)
					{
						curCameraState.curCameraX = startX;
						curCameraState.curCameraY = startY;
						curCameraState.curCameraZ = startZ;

						locCameraFromToAngle(startX, startY, startZ, true, startAX * PI / 180.0, startAY * PI / 180.0);
						bSetPoint = true;
						break;
					}

					activeTime = cameraTime - delayTime;

					flyProgress = activeTime / flyTime;
					rotateProgress = activeTime / rotateTime;

					if (flyProgress < 0.0) flyProgress = 0.0;
					if (flyProgress > 1.0) flyProgress = 1.0;

					if (rotateProgress < 0.0) rotateProgress = 0.0;
					if (rotateProgress > 1.0) rotateProgress = 1.0;

					flyProgress = flyProgress * flyProgress * (3.0 - 2.0 * flyProgress);
					rotateProgress = rotateProgress * rotateProgress * (3.0 - 2.0 * rotateProgress);

					cameraX = startX + (endX - startX) * flyProgress;
					cameraY = startY + (endY - startY) * flyProgress;
					cameraZ = startZ + (endZ - startZ) * flyProgress;

					angleX = startAX + (endAX - startAX) * rotateProgress;
					angleY = startAY + (endAY - startAY) * rotateProgress;

					curCameraState.curCameraX = cameraX;
					curCameraState.curCameraY = cameraY;
					curCameraState.curCameraZ = cameraZ;

					locCameraFromToAngle(cameraX, cameraY, cameraZ, true, angleX * PI / 180.0, angleY * PI / 180.0);
					bSetPoint = true;

					if (activeTime >= flyTime && activeTime >= rotateTime)
					{
						locCameraNextState();
						return;
					}
				break;
			}
			
			if(!bSetPoint)
				locCameraToPos(stf(curCameraState.curCameraX), stf(curCameraState.curCameraY), stf(curCameraState.curCameraZ), true);
			
			if(time != -1.0)
			{
				time -= 1 * timeScale; // Учет ускорения времени
				curCameraState.time = time;
			}
			
			if(kSpeedTimer > -1.0)
			{
				kSpeedTimer -= dltTime;
				if(kSpeedTimer <= 0.0)
				{
					sPoint = "point" + (sti(curCameraState.speedpoints.cur) + 1);
					if(CheckAttribute(curCameraState, "speedpoints."+sPoint))
						curCameraState.speedpoints.cur = sti(curCameraState.speedpoints.cur) + 1;
					else
						DeleteAttribute(curCameraState, "speedpoints");
				}
				else
					curCameraState.speedpoints.(sPoint).timer = kSpeedTimer;
			}
			
			if(time <= 0.0 && time != -1.0)
			{
				locCameraNextState();
			}
			
			// Тут высчитываем попадание в нужную точку
			if(time == -1.0 && curCameraState.type == LOCCAMERA_FLYTOPOS)
			{
				if(stf(curCameraState.curCameraX) + stf(curCameraState.speedX) * timeScale >= stf(curCameraState.endCameraX) &&
					stf(curCameraState.curCameraX) - stf(curCameraState.speedX) * timeScale <= stf(curCameraState.endCameraX) &&
					stf(curCameraState.curCameraY) + stf(curCameraState.speedY) * timeScale >= stf(curCameraState.endCameraY) &&
					stf(curCameraState.curCameraY) - stf(curCameraState.speedY) * timeScale <= stf(curCameraState.endCameraY) &&
					stf(curCameraState.curCameraZ) + stf(curCameraState.speedZ) * timeScale >= stf(curCameraState.endCameraZ) &&
					stf(curCameraState.curCameraZ) - stf(curCameraState.speedZ) * timeScale <= stf(curCameraState.endCameraZ))
				{
					locCameraNextState();
				}
			}
		}
	}
}

#event_handler("AimingActive", "AimingActive");
void AimingActive()
{
	int isActive = GetEventData();
	
	if(isActive)
	{
		locCameraSetRadius(stf(locCamera.maxRadius)*0.75);
		locCamera.zoom.lock = true;
		BI_CrosshairSet();
		SendMessage(&objLandInterface, "ll", MSG_BATTLE_LAND_CROSSHAIR_SHOW, 1);
	}
	else
	{
		if(!CheckAttribute(&locCamera, "zoom"))
			locCamera.zoom = 0.75;
		if(CheckAttribute(&locCamera, "zoom.lock"))
			DeleteAttribute(&locCamera, "zoom.lock");
		locCameraSetRadius(stf(locCamera.maxRadius)*stf(locCamera.zoom));
		SendMessage(&objLandInterface, "ll", MSG_BATTLE_LAND_CROSSHAIR_SHOW, 0);
	}
}

// SetCameraShake(float time, float i1, float i2, float r1, float r2, bool sc, bool ev, int fd)
// time - продолжительность в секундах, -1.0 до выключения, 0.0 выключить принудительно
// i1 - интенсивность смещения положения камеры (оффсета по x, y) - множитель аргумента функции шума
// i2 - интесивность кручения ориентации камеры (pitch, yaw, roll)
// r1 - диапазон смещения в метрах (от -param до +param)
// r2 - диапазон углов поворота в радианах (от -param до +param)
// sc - true использовать screen space для смещения (будет учитывать повороты),
//     false использовать world space (смещать глобально, шумовой оффсет игнорирует шумовой наклон)
// ev - true вызывать ивент "CamShakeScaler" для получения множителя из скриптов, false не вызывать
//     По задумке скриптовый множитель должен заменять собой движковый множитель затухания, поэтому при
//     использовании ивента затухание лучше отключать (поставить -1 в следующем параметре), а сам float
//     возвращать от 0.0 до 1.0. В скриптах можно: настроить свою функцию для затухания (fade out easing),
//     скалировать силу тряски в зависимости от дистанции до какой-то координаты (например, персонажа) и т.п.
//     Ивент ничего не передаёт, так что, например, дельту надо брать самостоятельно через GetRealDeltaTime()
// fd - номер изинга из списка ниже для нарастания затухания, -1 не использовать затухание. Smoothstep хорош для
//     относительно продолжительной тряски (3 секунды и более), условный x^3 подойдёт для более коротких

// Any other number in func parameter <-> no easing
// Attenuation increasing (from Engine)
#define CAM_EASING_SMOOTH_STEP 0 // 3x^2 - 2x^3
#define CAM_EASING_LINEAR      1 // x
#define CAM_EASING_QUAD        2 // x^2
#define CAM_EASING_CUBE        3 // x^3
#define CAM_EASING_QUART       4 // x^4
#define CAM_EASING_SINE        5 // 1 - cos((pi*0.5) * x)
#define CAM_EASING_CIRC        6 // 1 - sqrt(1 - x^2)
#define CAM_EASING_SIGMOID     7 // x^2 / (x^2 + (1 - x)^2)
#define CAM_EASING_ELASTIC     8 // sin(pi * 6.5 * x) * pow(2, 10 * (x - 1))

// Простейший пример функции для вызова шума
void SetCameraShakeSimple(float time, float power, float range)
{
    SetCameraShake(time, 5.0 * power, 3.0 * power, 1.2 * range, 0.5 * range, true, false, CAM_EASING_SMOOTH_STEP);
}

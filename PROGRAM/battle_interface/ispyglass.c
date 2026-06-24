
object objISpyGlass;

void InterfaceSpyGlassInit()
{
	FillISpyGlassParameters();
	CreateEntity(&objISpyGlass, "ispyglass");
	TelescopeInitParameters(&Telescope);

	LayerAddObject(SEA_EXECUTE, &objISpyGlass, -1);
	LayerAddObject(SEA_REALIZE, &objISpyGlass, -1);
	SetEventHandler("SetTelescopeInfo", "SetSpyGlassData", 0);
	SetEventHandler(BI_EVENT_SET_VISIBLE, "CheckInterfaceVisible", 0);
}

void InterfaceSpyGlassRelease()
{
	DelEventHandler(BI_EVENT_SET_VISIBLE, "CheckInterfaceVisible");
	DelEventHandler("SetTelescopeInfo", "SetSpyGlassData");
	DelEventHandler("frame", "ZoomTelescope");
	DeleteClass(&objISpyGlass);
}

void CheckInterfaceVisible()
{
	int vtype = GetEventData();
	if (vtype != 0)
	{
		DelEventHandler("frame", "ZoomTelescope");
		SendMessage(&objISpyGlass, "lsfll", MSG_TELESCOPE_SET_TYPE, "", 1.0, 0, 0); //Убрать для сохранения накрученного масштаба
		objISpyGlass.fWhell = FloatToString(1.0, 1);
		SendMessage(&objActivePerkShower, "ll", MSG_ACTIVE_PERK_CAN_SHOW, 1);
		SendMessage(&objSeaPerkShower, "ll", MSG_ACTIVE_PERK_CAN_SHOW, 1);
		SetTimeScale(1 + TimeScaleCounter * 0.25);
	}
	else
	{
		SetEventHandler("frame", "ZoomTelescope", 0);
		SendMessage(&objActivePerkShower, "ll", MSG_ACTIVE_PERK_CAN_SHOW, 0);
		SendMessage(&objSeaPerkShower, "ll", MSG_ACTIVE_PERK_CAN_SHOW, 0);
		SetTimeScale(1.0);
	}
}

string CalculateHold(ref rChr) //приблизительная заполненность трюма
{	//реальную загруженность приводим относительно трюма базового корабля
    ref rRealShip = GetRealShip(sti(rChr.Ship.Type));
   	ref rBaseShip = GetShipByType(sti(rRealShip.BaseType));
   	int iRealCap = GetCargoMaxSpace(rChr); //максимальная вместимость реального корабля
   	int iBaseCap = sti(rBaseShip.Capacity); //максимальная вместимость кораблей этого типа
    int iHold = GetCargoLoad(rChr); //сколько загружено в реальном корабле
	if (iHold >= iBaseCap) return iBaseCap +"/" +iBaseCap; //если корабль перегружен
    iHold = makeint(iHold * iBaseCap / iRealCap); //приведённое значение загруженности корабля

    //округление
    int iLow, iUp, iCompare;
    int iShow = 0;

	int iK = 100;
    if (iBaseCap < 1000) iK = 10;

	iLow = makeint(iHold / iK) * iK;
	iUp = iLow + iK;
	iCompare = iLow + iK * 0.5;

    if (iCompare < iHold) iShow = iUp;
    else iShow = iLow;

    if (iShow <= 0) iShow = 1;

    return iShow +"/" +iBaseCap;
}

void SetSpyGlassData()
{
	int chrIdx = GetEventData();
	if (chrIdx < 0) return;
	ref chref = GetCharacter(chrIdx);
	if (!CheckAttribute(chref, "Ship.Type")) return;
	int iShip = sti(chref.Ship.Type);
	if (iShip == SHIP_NOTUSED) return;

	string sShipPortrait = "battle_interface\spyglass\Error_Spyglass.tga";
	string sCapFrame = sShipPortrait;
	string sCapPortrait = sShipPortrait;

	int	shipHull = -1;
	int shipSail = -1;
	int shipCrew = -1;
	int shipCannons = -1;
	int shipMaxCannons = -1;
	string cannonsType = "";
	string cannonsQty = "";
	string chargeType = "";
	int shipCharge = -1;
	int shipNation = -1;
	int shipClass = -1;
	float shipSpeed = -1.0;
	string shipName = "";
	string shipType = "";
	string shipMode = "";
	string sHold = "";
	bool isFort;
	int nSailState = -1;
	object tmpobj;
	aref arScopeItm;

	if (Items_FindItem(GetCharacterEquipByGroup(pchar, SPYGLASS_ITEM_TYPE), &arScopeItm) < 0)
		makearef(arScopeItm, tmpobj);
	
	float fDistance = stf(FloatToString(Ship_GetDistance2D(pchar, chref), 1)); //boal
	// ship or fort -->
	iShip = sti(RealShips[iShip].basetype);
	if (CheckAttribute(arScopeItm,"scope.show.ship_name") && sti(arScopeItm.scope.show.ship_name) > 0)
    	shipName = chref.Ship.Name;
	
	if (CheckAttribute(arScopeItm, "scope.show.nation") && sti(arScopeItm.scope.show.nation) > 0)
    	shipNation = sti(chref.nation);
	
   	if (CheckAttribute(arScopeItm,"scope.show.crew") && sti(arScopeItm.scope.show.crew) > 0)
		shipCrew = GetCrewQuantity(chref);
	
    if (CheckAttribute(arScopeItm,"scope.show.charge") && sti(arScopeItm.scope.show.charge) > 0)
    {
    	switch(sti(chref.Ship.Cannons.Charge.Type))
    	{
    		case GOOD_GRAPES:
    			shipCharge = 0;
    			chargeType = XI_convertString("Grapes");
    		break;
    		case GOOD_BALLS:
    			shipCharge = 1;
    			chargeType = XI_convertString("Balls");
			break;
    		case GOOD_BOMBS:
    			shipCharge = 2;
    			chargeType = XI_convertString("Bombs");
    		break;
    		case GOOD_KNIPPELS:
    			shipCharge = 3;
    			chargeType = XI_convertString("Knippels");
    		break;
    	}
   	}

	if (CheckAttribute(arScopeItm,"scope.show.cannontype") && sti(arScopeItm.scope.show.cannontype) > 0)
	{
		switch (sti(chref.Ship.Cannons.Type))
		{
			case CANNON_TYPE_NONECANNON: 		cannonsType = XI_ConvertString("NoneCannons");			break;
			case CANNON_TYPE_CANNON_LBS3: 		cannonsType = XI_ConvertString("ShortCannon_3");		break;
			case CANNON_TYPE_CANNON_LBS6:		cannonsType = XI_ConvertString("ShortCannon_6");		break;
			case CANNON_TYPE_CANNON_LBS8:		cannonsType = XI_ConvertString("ShortCannon_8");		break;
			case CANNON_TYPE_CANNON_LBS12:		cannonsType = XI_ConvertString("ShortCannon_12");		break;
			case CANNON_TYPE_CANNON_LBS16:		cannonsType = XI_ConvertString("ShortCannon_16");		break;
			case CANNON_TYPE_CANNON_LBS20:		cannonsType = XI_ConvertString("ShortCannon_20");		break;
			case CANNON_TYPE_CANNON_LBS24:		cannonsType = XI_ConvertString("ShortCannon_24");		break;
			case CANNON_TYPE_CANNON_LBS32:		cannonsType = XI_ConvertString("ShortCannon_32");		break;
			case CANNON_TYPE_CANNON_LBS36:		cannonsType = XI_ConvertString("ShortCannon_36");		break;
			case CANNON_TYPE_CANNON_LBS42:		cannonsType = XI_ConvertString("ShortCannon_42");		break;
			case CANNON_TYPE_CANNON_LBS48:		cannonsType = XI_ConvertString("ShortCannon_48");		break;
			case CANNON_TYPE_CULVERINE_LBS8:	cannonsType = XI_ConvertString("ShortCulverine_8");		break;
			case CANNON_TYPE_CULVERINE_LBS12:	cannonsType = XI_ConvertString("ShortCulverine_12");	break;
			case CANNON_TYPE_CULVERINE_LBS16:	cannonsType = XI_ConvertString("ShortCulverine_16");	break;
			case CANNON_TYPE_CULVERINE_LBS24:	cannonsType = XI_ConvertString("ShortCulverine_24");	break;
			case CANNON_TYPE_CULVERINE_LBS32:	cannonsType = XI_ConvertString("ShortCulverine_32");	break;
		}
	}

	isFort = ShipsTypes[iShip].name == "fort";

	if (isFort) // смотрим на форт
	{
		sShipPortrait = "INTERFACES\PORTRAITS\256\face_3004.tga";

		if (CheckAttribute(arScopeItm,"scope.show.ship_type") && sti(arScopeItm.scope.show.ship_type) > 0)
		{
			shipType = XI_ConvertString("Fort_Name");//boal fix
		}
		if (CheckAttribute(arScopeItm,"scope.show.cannons") && sti(arScopeItm.scope.show.cannons) > 0)
		{
			shipCannons = Fort_GetCannonsQuantity(chref);
			if (!CheckAttribute(chref, "fort.Cannons.Quantity")) shipMaxCannons = 0;
			else shipMaxCannons = sti(chref.Fort.Cannons.Quantity);
		}
		if (CheckAttribute(arScopeItm,"scope.show.hull") && sti(arScopeItm.scope.show.hull) > 0)
		{
			if (CheckAttribute(chref,"ship.hp") && CheckAttribute(chref,"fort.hp") && stf(chref.Fort.hp) > 0.0)
			{
				shipHull = makeint(stf(chref.ship.hp) / stf(chref.Fort.hp) * 100.0);
			}
			else shipHull = 100;
		}
	}
	else // смотрим на корабль
	{
		sShipPortrait = "interfaces\ships\" + ShipsTypes[iShip].name + ".tga";
		shipClass = GetCharacterShipClass(chref);

		if (CheckAttribute(arScopeItm,"scope.show.ship_type") && sti(arScopeItm.scope.show.ship_type) > 0)
    	{
    		shipType = XI_ConvertString(GetShipTypeName(chref));
    		if (CheckAttribute(chref, "Ship.Mode"))
			{
				if ("trade" == chref.Ship.Mode) shipMode = XI_convertString("istrader");
				else if ("war" == chref.Ship.Mode) shipMode = XI_convertString("war");
			}
    	}
		if (CheckAttribute(arScopeItm,"scope.show.cannons") && sti(arScopeItm.scope.show.cannons) > 0)
		{
			shipCannons = GetIntactCannonQuantity(chref);
			shipMaxCannons = GetCannonQuantity(chref);
		}
		if (CheckAttribute(arScopeItm,"scope.show.hull") && sti(arScopeItm.scope.show.hull) > 0)
		{
			shipHull = makeint(GetHullPercent(chref));
		}
		if (CheckAttribute(arScopeItm,"scope.show.hold") && sti(arScopeItm.scope.show.hold) > 0)
		{
			sHold = CalculateHold(chref);
		}
		if (CheckAttribute(arScopeItm,"scope.show.sail") && sti(arScopeItm.scope.show.sail) > 0)
		{
			shipSail = makeint(GetSailPercent(chref));
		}
		if (CheckAttribute(arScopeItm,"scope.show.speed") && sti(arScopeItm.scope.show.speed) > 0)
		{
			shipSpeed = stf(chref.Ship.speed.z) * stf(BattleInterface.ShipSpeedScaler);
		}

        float fSailSt = Ship_GetSailState(chref);
        if (fSailSt < 0.3 ) nSailState = 2;
        else if (fSailSt < 0.6 ) nSailState = 1;
        else nSailState = 0;
        // Warship 08.07.09 Запрет спуска парусов
		// Показываем всегда иконку полных парусов, без этого - прыгает
		if (CheckAttribute(chref, "CanDropSails") && !sti(chref.CanDropSails)) nSailState = 0;
	}
	if (shipCannons > 0 && shipMaxCannons > 0)
		cannonsQty = shipCannons +"/" +shipMaxCannons;
	//ship or fort <--
	
	//captain -->
	string sCaptainName = GetCharacterFullName(chref.id);
	string sBangBang = "";
	int nDefenceSkill = -1;
	int nCannonSkill = -1;
	int nAccuracySkill = -1;
	int nNavigationSkill = -1;
	int nBoardingSkill = -1;

	if (isFort)
		sCapPortrait = "interfaces\empty_face.tga";
	else if (sti(chref.faceID) > -1)
		sCapPortrait = "interfaces\portraits\256\face_" +chref.faceID +".tga";
	else
		sCapPortrait = "interfaces\portraits\256\face_0.tga";

	if (CheckAttribute(arScopeItm,"scope.show.mushketshot") && sti(arScopeItm.scope.show.mushketshot) > 0  && CheckCharacterPerk(chref, "MusketsShoot") && !isFort)
	{
		sBangBang = GetConvertStr("MusketsShoot", "AbilityDescribe.txt");
		sCapFrame = "battle_interface\spyglass\CapBackIcon_mushket.tga";
	}
	else if (isFort) sCapFrame = "battle_interface\spyglass\CapBackIcon_fort.tga";
	else sCapFrame = "battle_interface\spyglass\CapBackIcon_spyglass.tga";

	if (CheckAttribute(arScopeItm,"scope.show.captain_skills") && sti(arScopeItm.scope.show.captain_skills) > 0
		&& !CheckAttribute(pchar,"GenQuest.ShipSituation.Explosion") && chref.ID != "MaryCelesteCapitan")
	{	//Не Кэп "Мэри Селест" и не смертники
		nDefenceSkill = GetCharacterSkill(chref,SKILL_DEFENCE);
		nCannonSkill = GetCharacterSkill(chref,SKILL_CANNONS);
		nAccuracySkill = GetCharacterSkill(chref,SKILL_ACCURACY);
		nNavigationSkill = GetCharacterSkill(chref,SKILL_SAILING);
		nBoardingSkill = GetCharacterSkill(chref,SKILL_GRAPPLING);
	}
    // captain <--
	SendMessage(&objISpyGlass,"llssslllffsssllllllllssls", MSG_ISG_UPDATE, isFort, shipName, shipType, shipMode, shipHull, shipSail,
		shipCrew, shipSpeed, fDistance, cannonsType, cannonsQty, chargeType, shipCharge, shipNation, nSailState,
		nDefenceSkill, nCannonSkill, nAccuracySkill, nNavigationSkill, nBoardingSkill, sCaptainName, sBangBang, shipClass, sHold);


	SendMessage(&objISpyGlass,"lsffff", MSG_ISG_SET_SHIPICON, sShipPortrait, 0.0, 0.0, 1.0, 1.0);
	SendMessage(&objISpyGlass,"lsffff", MSG_ISG_SET_CHARICON, sCapPortrait, 0.0, 0.0, 1.0, 1.0);
	SendMessage(&objISpyGlass,"lsffff", MSG_ISG_SET_CHARFRAME, sCapFrame, 0.0, 0.0, 1.0, 1.0);

	if (bBettaTestMode) // debug info
	{
		//LaunchShipStateNPC(chref); return; // открыть интерфейс корабля
		//LaunchCharacter(chref); return; // открыть интерфейс нпс
	}
}

void FillISpyGlassParameters()
{
	float fHtRatio = GetScreenScale();

	string sTexture;
	if (CheckAttribute(pchar, "equip.spyglass")) sTexture = pchar.equip.spyglass;
	else sTexture = "spyglass1";

	DeleteAttribute(&objISpyGlass, "");

	objISpyGlass.lens.texture = "battle_interface\spyglass\" + sTexture + ".tga";

	objISpyGlass.lens.pos = its(sti(showWindow.left) - 1) +"," +its(sti(showWindow.top) - 1) +"," +showWindow.right +"," +showWindow.bottom;
	// AlexBlade - Если перейдете на текстуры CL (4096*512), используйте этот расчет ->
	// objISpyGlass.lens.pos = (nHCenter-sti(showWindow.bottom)*4)+","+(sti(showWindow.top)-1)+","+(nHCenter+sti(showWindow.bottom)*4)+","+showWindow.bottom;

	int iIconScale, iTmpOffset, iVoffset, iHoffset;
	int iFrameLeft, iFrameTop, iFrameRight, iFrameBottom, iFrameCenterX, iFrameCenterY;
	int iIconLeft, iIconTop, iIconRight, iIconBottom;
	int iTextH, iTextV;

	int iTextColor = argb(255,255,204,102);
	string sTextFont = "interface_normal";
	string sAlign;
	string sIconTexture = "battle_interface\spyglass\Error_Spyglass.tga";
	float fIconsFontScale = 1.5;

	//LEFT, TOP, RIGHT, BOTTOM
	//ship portrait-->
	//frame
	iIconScale = RecalculateVIconScaled(178, fHtRatio); //Размер рамки корабля
	iFrameLeft = sti(showWindow.left) + RecalculateHIconScaled(16, fHtRatio); //отступ слева
	iFrameTop = sti(showWindow.top) + RecalculateVIconScaled(23, fHtRatio); //отступ сверху
	iFrameRight = iFrameLeft + iIconScale;
	iFrameBottom = iFrameTop + iIconScale;
	iFrameCenterX = makeint((iFrameRight + iFrameLeft) * 0.5);
	iFrameCenterY = makeint((iFrameBottom + iFrameTop) * 0.5);

	objISpyGlass.shipsign.back.texture = "battle_interface\ShipBackIcon.tga";
	objISpyGlass.shipsign.back.pos = iFrameLeft +"," +iFrameTop +"," +iFrameRight +"," +iFrameBottom;

	iIconScale = makeint(0.685 * iIconScale * 0.5); //0.5 Размер портрета корабля
	iVoffset = RecalculateVIconScaled(-16, fHtRatio); //Сместить портрет корабля по вертикали
	iHoffset = RecalculateHIconScaled(1, fHtRatio);
	objISpyGlass.shipsign.ship.pos = its(iFrameCenterX - iIconScale + iHoffset) +"," +its(iFrameCenterY - iIconScale + iVoffset) + "," +
									its(iFrameCenterX + iIconScale + iHoffset)+"," +its(iFrameCenterY + iIconScale + iVoffset);
	objISpyGlass.shipsign.ship.uv = "0,0,1.0,1.0";

	//Надписи корабля
	//Надписей возле портретов корабля и капитана может быть 2 - эта штука их отцентрует
	objISpyGlass.frameTextVoffset = RecalculateVIconScaled(17, fHtRatio);

	iHoffset = iFrameRight + RecalculateHIconScaled(11, fHtRatio); // Отступ типа корабля от рамки вправо
	iVoffset = iFrameBottom - (iFrameBottom - iFrameTop) * 0.5 - RecalculateVIconScaled(31, fHtRatio); //найдём середину рамки по вертикали
	objISpyGlass.text.shipType.font = sTextFont;
	objISpyGlass.text.shipType.pos = iHoffset +"," +iVoffset;
	objISpyGlass.text.shipType.align = "left";
	objISpyGlass.text.shipType.color = iTextColor;
	objISpyGlass.text.shipType.scale = fHtRatio * 1.5;

	objISpyGlass.text.shipType.font = sTextFont;
	objISpyGlass.text.shipMode.pos = iHoffset +"," +iVoffset;
	objISpyGlass.text.shipMode.align = "left";
	objISpyGlass.text.shipMode.color = iTextColor;
	objISpyGlass.text.shipMode.scale = fHtRatio * 1.2;

	iHoffset = iFrameRight * 0.5 + iFrameLeft - RecalculateHIconScaled(5, fHtRatio); //Смещение имени корабля и команды относительно центра рамки
	objISpyGlass.text.shipName.font = sTextFont;
	objISpyGlass.text.shipName.pos = iHoffset +"," +its(iFrameBottom - RecalculateVIconScaled(55, fHtRatio));
	objISpyGlass.text.shipName.align = "center";
	objISpyGlass.text.shipName.color = iTextColor;
	objISpyGlass.text.shipName.scale = fHtRatio * 1.2;

	objISpyGlass.text.crew.font = sTextFont;
	objISpyGlass.text.crew.pos = iHoffset +"," +its(iFrameBottom - RecalculateVIconScaled(33, fHtRatio));
	objISpyGlass.text.crew.align = "center";
	objISpyGlass.text.crew.color = iTextColor;
	objISpyGlass.text.crew.scale = fHtRatio * 1.5;

	// hp sp bar
	iIconScale = RecalculateHIconScaled(76, fHtRatio); //ширина полосок хп и паруса
	iIconTop = iFrameTop + RecalculateVIconScaled(11, fHtRatio); //Отступ полосок от рамки сверху
	iIconBottom = iFrameBottom - RecalculateVIconScaled(55, fHtRatio); //Отступ полосок от рамки снизу
	iIconLeft = iFrameLeft + RecalculateHIconScaled(3, fHtRatio); //Отступ полоски хп от левого края рамки корабля
	iIconRight = iFrameRight - RecalculateHIconScaled(3, fHtRatio);  //Отступ полоски парусов от правого края рамки корабля

	objISpyGlass.shipsign.hp.texture = "battle_interface\ShipState.tga";
	objISpyGlass.shipsign.hp.pos = iIconLeft +"," +iIconTop +"," +its(iIconLeft + iIconScale) +"," +iIconBottom;
	objISpyGlass.shipsign.hp.uv = "0.0,0.0625,0.5,0.6875";
	objISpyGlass.shipsign.sp.texture = "battle_interface\ShipState.tga";
	objISpyGlass.shipsign.sp.pos = its(iIconRight - iIconScale) +"," +iIconTop +"," +iIconRight +"," +iIconBottom;
	objISpyGlass.shipsign.sp.uv = "0.5,0.0625,1.0,0.6875";

	// shipclass
	iIconScale = RecalculateHIconScaled(100, fHtRatio); // 0.5 ширины полоски класса
	iIconTop = iFrameTop - RecalculateVIconScaled(9, fHtRatio);
	iIconBottom = iIconTop + RecalculateVIconScaled(50, fHtRatio);
	iTmpOffset = iFrameCenterX + RecalculateHIconScaled(1, fHtRatio);
	objISpyGlass.shipsign.class.texture = "battle_interface\ShipClass.tga";
	objISpyGlass.shipsign.class.pos = its(iTmpOffset - iIconScale) +"," +iIconTop + "," +its(iTmpOffset + iIconScale) +"," +iIconBottom;

	objISpyGlass.shipClassUVarray.uv0 = "0.125,0.0,0.25,1.0";
	objISpyGlass.shipClassUVarray.uv1 = "0.25,0.0,0.375,1.0";
	objISpyGlass.shipClassUVarray.uv2 = "0.375,0.0,0.5,1.0";
	objISpyGlass.shipClassUVarray.uv3 = "0.5,0.0,0.625,1.0";
	objISpyGlass.shipClassUVarray.uv4 = "0.625,0.0,0.75,1.0";
	objISpyGlass.shipClassUVarray.uv5 = "0.75,0.0,0.875,1.0";
	//<-- ship portrait

	iIconScale = 66; //Размер значков
	iVoffset = RecalculateVIconScaled(iIconScale, fHtRatio);
	iHoffset = RecalculateHIconScaled(iIconScale, fHtRatio);
	iIconTop = iFrameBottom + RecalculateVIconScaled(10, fHtRatio); //отступ первого значка от рамки корабля
	iIconLeft = makeint(iFrameCenterX - iHoffset * 0.5) + RecalculateHIconScaled(2, fHtRatio); //расположить левый край значка относительно центра рамки
	iIconRight = iIconLeft + iHoffset;
	iIconBottom = iIconTop + iVoffset;

	iTextH = iIconRight + RecalculateHIconScaled(16, fHtRatio); //Отступ текста от значка
	iTextV = iVoffset * 0.5 + RecalculateVIconScaled(15, fHtRatio); //отцентровать вертикальное положение текста по значку
	iTmpOffset = RecalculateVIconScaled(23, fHtRatio); //расстояние между значками

	//Это массив позиций значков, будет нужно для ребаланса труб
	// и чтобы небыло пустых пространств, когда смотрим на форт, у форта нет состояния парусов и трюма
	objISpyGlass.iconPositionArray.p0 = iIconLeft +"," +iIconTop + "," +iIconRight +"," +iIconBottom;
	objISpyGlass.textPositionArray.p0 = iTextH +"," +its(iIconBottom - iTextV);
	iIconTop = iIconBottom + iTmpOffset;
	iIconBottom = iIconTop + iVoffset;
	objISpyGlass.iconPositionArray.p1 = iIconLeft +"," +iIconTop + "," +iIconRight +"," +iIconBottom;
	objISpyGlass.textPositionArray.p1 = iTextH +"," +its(iIconBottom - iTextV);
	iIconTop = iIconBottom + iTmpOffset;
	iIconBottom = iIconTop + iVoffset;
	objISpyGlass.iconPositionArray.p2 = iIconLeft +"," +iIconTop + "," +iIconRight +"," +iIconBottom;
	objISpyGlass.textPositionArray.p2 = iTextH +"," +its(iIconBottom - iTextV);
	iIconTop = iIconBottom + iTmpOffset;
	iIconBottom = iIconTop + iVoffset;
	objISpyGlass.iconPositionArray.p3 = iIconLeft +"," +iIconTop + "," +iIconRight +"," +iIconBottom;
	objISpyGlass.textPositionArray.p3 = iTextH +"," +its(iIconBottom - iTextV);
	iIconTop = iIconBottom + iTmpOffset;
	iIconBottom = iIconTop + iVoffset;
	objISpyGlass.iconPositionArray.p4 = iIconLeft +"," +iIconTop + "," +iIconRight +"," +iIconBottom;
	objISpyGlass.textPositionArray.p4 = iTextH +"," +its(iIconBottom - iTextV);

	//showNumber: отображаемая позиция значка если смотрим на корабль, если смотрим на форт
	//далее позиция для текста применится относительно позиции значка

	sAlign = "left";
	sIconTexture = "battle_interface\LIST_ICON2.tga";
	//паруса, скорость
	objISpyGlass.info.sailState.texture = sIconTexture;
	//objISpyGlass.info.sailState.pos = objISpyGlass.iconPositionArray.p0;
	objISpyGlass.info.sailState.showNumber = "0,0";
	objISpyGlass.info.sailState.uv = "0.0,0.0,0.25,0.25";
	//LEFT, TOP, RIGHT, BOTTOM
	objISpyGlass.sailStateUVarray.uv0 = "0.0,0.0,0.25,0.25"; // up
	objISpyGlass.sailStateUVarray.uv1 = "0.25,0.0,0.5,0.25"; // middle
	objISpyGlass.sailStateUVarray.uv2 = "0.5,0.0,0.75,0.25"; // down

	objISpyGlass.text.speed.font = sTextFont;
	objISpyGlass.text.speed.align = sAlign;
	objISpyGlass.text.speed.color = iTextColor;
	objISpyGlass.text.speed.scale = fHtRatio * fIconsFontScale;

	//distance
	objISpyGlass.info.distance.texture = sIconTexture;
	objISpyGlass.info.distance.showNumber = "1,0";
	objISpyGlass.info.distance.uv = "0.75,0.5,1.0,0.75";

	objISpyGlass.text.distance.font = sTextFont;
	objISpyGlass.text.distance.align = sAlign;
	objISpyGlass.text.distance.color = iTextColor;
	objISpyGlass.text.distance.scale = fHtRatio * fIconsFontScale;

	//Cannons
	//так как у картинки орудий возможны две надписи - эта штука орпределяет растояние между ними
	objISpyGlass.iconTextVoffset = RecalculateVIconScaled(11, fHtRatio);

	objISpyGlass.info.cannon.texture = sIconTexture;
	objISpyGlass.info.cannon.showNumber = "2,1";
	objISpyGlass.info.cannon.uv = "0.5,0.5,0.75,0.75";

	objISpyGlass.text.cannonsType.font = sTextFont;
	objISpyGlass.text.cannonsType.align = sAlign;
	objISpyGlass.text.cannonsType.color = iTextColor;
	objISpyGlass.text.cannonsType.scale = fHtRatio * fIconsFontScale;

	objISpyGlass.text.cannonsQty.font = sTextFont;
	objISpyGlass.text.cannonsQty.align = sAlign;
	objISpyGlass.text.cannonsQty.color = iTextColor;
	objISpyGlass.text.cannonsQty.scale = fHtRatio * fIconsFontScale;

	//Hold
	objISpyGlass.info.hold.texture = sIconTexture;
	objISpyGlass.info.hold.showNumber = "3,0";
	objISpyGlass.info.hold.uv = "0.75,0.0,1.0,0.25";

	objISpyGlass.text.hold.font = sTextFont;
	objISpyGlass.text.hold.align = sAlign;
	objISpyGlass.text.hold.color = iTextColor;
	objISpyGlass.text.hold.scale = fHtRatio * fIconsFontScale;

	//Charge
	objISpyGlass.info.charge.texture = sIconTexture;
	objISpyGlass.info.charge.uv = "0.25,0.25,0.5,0.5";
	objISpyGlass.info.charge.showNumber = "4,2";

	objISpyGlass.chargeUVarray.uv0 = "0.0,0.25,0.25,0.5"; // grapes
	objISpyGlass.chargeUVarray.uv1 = "0.25,0.25,0.5,0.5"; // balls
	objISpyGlass.chargeUVarray.uv2 = "0.5,0.25,0.75,0.5"; // bomb
	objISpyGlass.chargeUVarray.uv3 = "0.75,0.25,1.0,0.5"; // knippels

	objISpyGlass.text.chargeType.font = sTextFont;
	objISpyGlass.text.chargeType.align = sAlign;
	objISpyGlass.text.chargeType.color = iTextColor;
	objISpyGlass.text.chargeType.scale = fHtRatio * fIconsFontScale;

	//Nation
	iIconScale = 400;
	iIconLeft = iFrameLeft + RecalculateHIconScaled(0, fHtRatio); //Отступ флага слева
	iIconRight = RecalculateHIconScaled(iIconScale, fHtRatio);
	iIconBottom = sti(showWindow.bottom) + RecalculateHIconScaled(iIconScale, fHtRatio) / 6;
	iIconTop = iIconBottom - RecalculateVIconScaled(iIconScale, fHtRatio);
	objISpyGlass.info.nation.texture = "battle_interface\spyglass\nations_spyglass.tga";
	objISpyGlass.info.nation.pos = iIconLeft +"," +iIconTop +"," +iIconRight +"," +iIconBottom;
	objISpyGlass.info.nation.uv = "0,0,1.0,1.0";

	objISpyGlass.nationUVarray.uv0 = "0.0,0,0.25,0.25"; // england 0
	objISpyGlass.nationUVarray.uv2 = "0.5,0,0.75,0.25"; // france 1
	objISpyGlass.nationUVarray.uv3 = "0.75,0.0,1.0,0.25"; // spain 2
	objISpyGlass.nationUVarray.uv1 = "0.25,0,0.5,0.25"; // holland 3
	objISpyGlass.nationUVarray.uv4 = "0.0,0.25,0.25,0.5"; // pirate 4

	//Control tip -->
	if (iShowTips >= CONTROL_TIPS_ALL)
	{
		objISpyGlass.tip.zoomKey.font = "keyboard_symbol";
		objISpyGlass.tip.zoomKey.pos = its(sti(showWindow.right) - RecalculateHIcon(39 * fHtRatio)) +"," +its(iIconTop - RecalculateVIconScaled(2, fHtRatio));
		objISpyGlass.tip.zoomKey.align = "center";
		objISpyGlass.tip.zoomKey.color = BattleInterface.textinfo.SpyKey.color;
		objISpyGlass.tip.zoomKey.scale = BattleInterface.textinfo.SpyKey.scale;
		objISpyGlass.tip.zoomKey.text = objControlsState.key_codes.VK_MWHEEL_UP.img;

		objISpyGlass.tip.zoomTxt.font = sTextFont;
		objISpyGlass.tip.zoomTxt.pos = its(sti(showWindow.right) - RecalculateHIcon(71 * fHtRatio)) +"," +its(iIconTop - RecalculateVIconScaled(0, fHtRatio));
		objISpyGlass.tip.zoomTxt.align = "right";
		objISpyGlass.tip.zoomTxt.color = BattleInterface.textinfo.SpyTip.color;
		objISpyGlass.tip.zoomTxt.scale = BattleInterface.textinfo.SpyTip.scale;
		objISpyGlass.tip.zoomTxt.text = LanguageConvertString(iControlsFile, "TelescopeZoom");
	}
	// Control tips <--

	//Captain -->
	//LEFT, TOP, RIGHT, BOTTOM
	//frame
	iIconScale = 175; //Размер рамки капитана
	iFrameTop = sti(showWindow.top) + RecalculateVIconScaled(19, fHtRatio); //отступ сверху
	iFrameBottom = iFrameTop + RecalculateVIconScaled(iIconScale, fHtRatio);
	iFrameRight = sti(showWindow.right) - RecalculateHIconScaled(16, fHtRatio); //отступ слева
	iFrameLeft = iFrameRight - RecalculateHIconScaled(iIconScale, fHtRatio);
	objISpyGlass.captain.back.pos = iFrameLeft +"," +iFrameTop +"," +iFrameRight +"," +iFrameBottom;
	//face
	iVoffset = RecalculateVIconScaled(13, fHtRatio); // Mask size
	iHoffset = RecalculateHIconScaled(13, fHtRatio);
	objISpyGlass.captain.faceMask.pos = its(iFrameLeft + iHoffset) +"," +its(iFrameTop + iVoffset) +"," +its(iFrameRight - iHoffset) +"," +its(iFrameBottom - iVoffset);
	objISpyGlass.captain.faceMask.texture = "battle_interface\CharFaceMask.tga";
	objISpyGlass.captain.faceMask.uv = "0,0,1.0,1.0";

	iVoffset = RecalculateVIconScaled(27, fHtRatio); //Скукожить портрет по вертикали
	iHoffset = RecalculateHIconScaled(27, fHtRatio); //Скукожить портрет по горизонтали
	objISpyGlass.captain.face.pos = its(iFrameLeft + iHoffset) +"," +its(iFrameTop + iVoffset) +"," +its(iFrameRight - iHoffset) +"," +its(iFrameBottom - iVoffset);

	iVoffset = iFrameBottom - (iFrameBottom - iFrameTop) * 0.5 - RecalculateVIconScaled(38, fHtRatio); //найти центр рамки по вертикали
	objISpyGlass.captext.capname.pos = its(iFrameLeft - RecalculateHIconScaled(11, fHtRatio)) +"," +its(iFrameTop + iVoffset);
	objISpyGlass.captext.capname.font = sTextFont;
	objISpyGlass.captext.capname.align = "right";
	objISpyGlass.captext.capname.color = iTextColor;
	objISpyGlass.captext.capname.scale = fHtRatio * 1.5;

	objISpyGlass.captext.shoot.pos = objISpyGlass.captext.capname.pos;
	objISpyGlass.captext.shoot.font = sTextFont;
	objISpyGlass.captext.shoot.align = "right";
	objISpyGlass.captext.shoot.color = iTextColor;
	objISpyGlass.captext.shoot.scale = fHtRatio * 1.2;

	sAlign = "right";
	sIconTexture =  "interfaces\icons_spec.tga";
	iIconScale = 66; //Размер значков перков
	iVoffset = RecalculateVIconScaled(iIconScale, fHtRatio);
	iHoffset = RecalculateHIconScaled(iIconScale, fHtRatio);
	iIconTop = iFrameBottom + RecalculateVIconScaled(16, fHtRatio); //отступ первого значка от рамки капитана
	iIconLeft = iFrameLeft - (iFrameLeft - iFrameRight) * 0.5 - iHoffset * 0.5 + RecalculateHIconScaled(3, fHtRatio); //расположить левый край значка относительно центра рамки
	iIconRight = iIconLeft + iHoffset;
	iIconBottom = iIconTop + iVoffset;

	iTextH = iIconleft - RecalculateHIconScaled(16, fHtRatio); //Отступ текста от значка
	iTextV = iVoffset * 0.5 + RecalculateVIconScaled(16, fHtRatio); //отцентровать вертикальное положение текста по значку
	iTmpOffset = RecalculateVIconScaled(8, fHtRatio); //расстояние между значками

	//navigation
	objISpyGlass.captain.navigation.pos = iIconLeft +"," +iIconTop + "," +iIconRight +"," +iIconBottom;
	objISpyGlass.captext.navigation.pos = iTextH +"," +its(iIconBottom - iTextV);
	iIconTop = iIconBottom + iTmpOffset;
	iIconBottom = iIconTop + iVoffset;

	objISpyGlass.captain.navigation.texture = sIconTexture;
	objISpyGlass.captain.navigation.uv = "0.5,0.125,0.625,0.25";

	objISpyGlass.captext.navigation.font = sTextFont;
	objISpyGlass.captext.navigation.align = sAlign;
	objISpyGlass.captext.navigation.color = iTextColor;
	objISpyGlass.captext.navigation.scale = fHtRatio * fIconsFontScale;

	//accuracy // орудия
	objISpyGlass.captain.accuracy.pos = iIconLeft +"," +iIconTop + "," +iIconRight +"," +iIconBottom;
	objISpyGlass.captext.accuracy.pos = iTextH +"," +its(iIconBottom - iTextV);
	iIconTop = iIconBottom + iTmpOffset;
	iIconBottom = iIconTop + iVoffset;

	objISpyGlass.captain.accuracy.texture = sIconTexture;
	objISpyGlass.captain.accuracy.uv = "0.25,0.125,0.375,0.25";

	objISpyGlass.captext.accuracy.font = sTextFont;
	objISpyGlass.captext.accuracy.align = sAlign;
	objISpyGlass.captext.accuracy.color = iTextColor;
	objISpyGlass.captext.accuracy.scale = fHtRatio * fIconsFontScale;

	//Cannons
	objISpyGlass.captain.cannon.pos = iIconLeft +"," +iIconTop + "," +iIconRight +"," +iIconBottom;
	objISpyGlass.captext.cannon.pos = iTextH +"," +its(iIconBottom - iTextV);
	iIconTop = iIconBottom + iTmpOffset;
	iIconBottom = iIconTop + iVoffset;

	objISpyGlass.captain.cannon.texture = sIconTexture;
	objISpyGlass.captain.cannon.uv = "0.375,0.125,0.5,0.25";

	objISpyGlass.captext.cannon.font = sTextFont;
	objISpyGlass.captext.cannon.align = sAlign;
	objISpyGlass.captext.cannon.color = iTextColor;
	objISpyGlass.captext.cannon.scale = fHtRatio * fIconsFontScale;

	//board
	objISpyGlass.captain.boarding.pos = iIconLeft +"," +iIconTop + "," +iIconRight +"," +iIconBottom;
	objISpyGlass.captext.boarding.pos = iTextH +"," +its(iIconBottom - iTextV);
	iIconTop = iIconBottom + iTmpOffset;
	iIconBottom = iIconTop + iVoffset;

	objISpyGlass.captain.boarding.texture = sIconTexture;
	objISpyGlass.captain.boarding.uv = "0.75,0.125,0.875,0.25";

	objISpyGlass.captext.boarding.font = sTextFont;
	objISpyGlass.captext.boarding.align = sAlign;
	objISpyGlass.captext.boarding.color = iTextColor;
	objISpyGlass.captext.boarding.scale = fHtRatio * fIconsFontScale;

	//defence
	objISpyGlass.captain.defence.pos = iIconLeft +"," +iIconTop + "," +iIconRight +"," +iIconBottom;
	objISpyGlass.captext.defence.pos = iTextH +"," +its(iIconBottom - iTextV);
	iIconTop = iIconBottom + iTmpOffset;
	iIconBottom = iIconTop + iVoffset;

	objISpyGlass.captain.defence.texture = sIconTexture;
	objISpyGlass.captain.defence.uv = "0.875,0.125,1.0,0.25";

	objISpyGlass.captext.defence.align = sAlign;
	objISpyGlass.captext.defence.color = iTextColor;
	objISpyGlass.captext.defence.scale = fHtRatio * fIconsFontScale;
	// <-- Captain
}

void TelescopeInitParameters(ref fTelescope)
{
	aref arItmScope;
	if (Items_FindItem(GetCharacterEquipByGroup(pchar, SPYGLASS_ITEM_TYPE), &arItmScope) > -1)
	{
		setTelescopeInitParameters(arItmScope);
	}
	else
	{
		object tmpobj;
		setTelescopeInitParameters(&tmpobj);
	}
}

void ZoomTelescope()
{
	if (nWeelStep == 0) return;
	float fZoom = stf(objISpyGlass.fZoom);
	float fWhell = stf(objISpyGlass.fWhell) + nWeelStep;

	if (fWhell < 1.0) fWhell = 1.0;
	else if (fWhell > fZoom) fWhell = fZoom;
	else PlayInterfaceCommand("interface\telescope.wav");

	SendMessage(&objISpyGlass, "lsfll", MSG_TELESCOPE_SET_TYPE, "", fWhell, 0, 0);
	objISpyGlass.fWhell = FloatToString(fWhell, 1);
	nWeelStep = 0;
}

void setTelescopeInitParameters(aref arItmScope)
{
	string texName = "telescope.tga";
	int activateTime = 500;
	int updateTime = 150;

	if (CheckAttribute(arItmScope,"scope.texture")) texName = arItmScope.scope.texture;

	if (CheckAttribute(arItmScope,"scope.zoom")) objISpyGlass.fZoom = arItmScope.scope.zoom;
	else objISpyGlass.fZoom = FloatToString(5.5, 1);

	if (CheckAttribute(arItmScope,"scope.time_activate")) activateTime = sti(arItmScope.scope.time_activate);
	if (CheckAttribute(arItmScope,"scope.time_update")) updateTime = sti(arItmScope.scope.time_update);
	objISpyGlass.fWhell = FloatToString(1.0, 1);

	SendMessage(&objISpyGlass, "lsfll", MSG_TELESCOPE_SET_TYPE, texName, 1.0, activateTime, updateTime);
}

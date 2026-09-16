#define MAX_CANNON_DAMAGE_DISTANCE				3.0

#define FIRE_MODE_RANDOM "random"
#define FIRE_MODE_DIRECT "direct"
#define FIRE_MODE_REVERSE "reverse"

void DeleteCannonsEnvironment()
{
	DelEventHandler(CANNON_GET_RECHARGE_TIME, "Cannon_GetRechargeTime");
	DelEventHandler(CANNON_GET_FIRE_TIME, "Cannon_GetFireTime");
	DelEventHandler(CANNON_GET_FIRE_HEIGHT, "Cannon_GetFireHeight");
	DelEventHandler(CANNON_FIRE, "Cannon_FireCannon");
	DelEventHandler(CANNON_UNLOAD, "Cannon_UnloadBall");
	DelEventHandler(CANNON_LOAD, "Cannon_LoadBall");
	DelEventHandler(CANNON_RECALCULATE_PARAMETERS, "Cannon_RecalculateParametersEvent");
	DelEventHandler(CANNON_DAMAGE, "Cannon_DamageEvent");
}

void CreateCannonsEnvironment()
{
	SetEventHandler(CANNON_GET_RECHARGE_TIME, "Cannon_GetRechargeTime", 0);
	SetEventHandler(CANNON_GET_FIRE_TIME, "Cannon_GetFireTime", 0);
	SetEventHandler(CANNON_GET_FIRE_HEIGHT, "Cannon_GetFireHeight", 0);
	SetEventHandler(CANNON_FIRE, "Cannon_FireCannon", 0);
	SetEventHandler(CANNON_UNLOAD, "Cannon_UnloadBall", 0);
	SetEventHandler(CANNON_LOAD, "Cannon_LoadBall", 0);
	SetEventHandler(CANNON_RECALCULATE_PARAMETERS, "Cannon_RecalculateParametersEvent", 0);
	SetEventHandler(CANNON_DAMAGE, "Cannon_DamageEvent", 0);

	SendMessage(&AISea, "lff", AI_MESSAGE_CANNONS_PARAMS, MAX_CANNON_DAMAGE_DISTANCE, 1.0);	// fMaxCannonDamageDistance, fMaxCannonDamageRadiusPoint
}

bool Cannon_LoadBall()
{
	aref	aCharacter = GetEventData();

	if (CheckAttribute(aCharacter, "AoP_NoShipFire")) return false;

	int iBallType = sti(aCharacter.Ship.Cannons.Charge.Type);
	int iNumBalls = GetCargoGoods(aCharacter, iBallType);
 	// boal -->
	int iNumPowder = GetCargoGoods(aCharacter, GOOD_POWDER);
	if (iNumBalls > 0 && iNumPowder > 0)
	{
		AddCharacterGoodsCannon(aCharacter, iBallType, -1);
		AddCharacterGoodsCannon(aCharacter, GOOD_POWDER, -1);
		// boal <--
		return true;
	}
	return false;
}

void Cannon_UnloadBall()
{
	aref aCharacter = GetEventData();
	if(CheckAttribute(aCharacter, "Ship.Cannons"))
	{
		AddCharacterGoodsCannon(aCharacter, sti(aCharacter.Ship.Cannons.Charge.Type), 1);
	}	
	// boal -->
	AddCharacterGoodsCannon(aCharacter, GOOD_POWDER, 1);
	// boal <--
}

void AddCharacterGoodsCannon(aref aCharacter, int iGood, int iQuantity)
{
	string sGoodName = Goods[iGood].name;
	aCharacter.Ship.Cargo.Goods.(sGoodName) = sti(aCharacter.Ship.Cargo.Goods.(sGoodName)) + iQuantity;
	aCharacter.Ship.Cargo.RecalculateCargoLoad = true;
}

void Cannon_RecalculateParametersEvent()
{
	int iCharacterIndex = GetEventData();
	Cannon_RecalculateParameters(iCharacterIndex);
}

void Cannon_RecalculateParameters(int iCharacterIndex)
{
	if (sti(Characters[iCharacterIndex].Ship.Cannons.Type) == CANNON_TYPE_NONECANNON) { return; }

	ref	rCharacter = GetCharacter(iCharacterIndex);
	ref	rCannon = GetCannonByType(sti(rCharacter.Ship.Cannons.Type));
	ref	rBall = GetGoodByType(sti(rCharacter.Ship.Cannons.Charge.Type));
	if (CheckAttribute(rCharacter, "TmpPerks.LongRangeShoot"))
	{
		// evganat - энциклопедия
		int iBonus = 0;
		if (!ENCYCLOPEDIA_DISABLED)
		{
			if (IsMainCharacter(rCharacter) || IsCompanion(rCharacter))
				iBonus += GetParamPageBonus("LongRangeShoot");
		}
		rCharacter.Ship.Cannons.SpeedV0 = stf(rCannon.SpeedV0) * stf(rBall.SpeedV0) * AIShip_isPerksUse(rCharacter.TmpPerks.LongRangeShoot, 1.0, 1.15 + 0.01 * iBonus); //slib
	}
	else
	{
	    rCharacter.Ship.Cannons.SpeedV0 = stf(rCannon.SpeedV0) * stf(rBall.SpeedV0);
	}
	rCharacter.Ship.Cannons.FireAngMax = rCannon.FireAngMax;
	rCharacter.Ship.Cannons.FireAngMin = rCannon.FireAngMin;
}

float Cannon_GetFireHeight()
{
	aref aCharacter = GetEventData();
	aref aEnemy = GetEventData();
	
	ref rBallType = GetGoodByType(sti(aCharacter.Ship.Cannons.Charge.Type));
	ref rEnemyShip = GetRealShip(sti(aEnemy.Ship.Type));

	string sBallName = rBallType.Name;

	float Y,DY;
	Y = stf(rEnemyShip.Height.(sBallName).Y);
	DY = stf(rEnemyShip.Height.(sBallName).DY);

	Y = Y / 2 + (frnd() - 0.5) * DY;

	return Y;
}

// calculate recharge time for cannon
float Cannon_GetRechargeTime()
{
	aref	aCharacter = GetEventData();

	if (CheckAttribute(aCharacter, "AoP_NoShipFire")) return 1000000.0;

	float	fCannonSkill = 1.0 - stf(aCharacter.TmpSkill.Cannons) / 3.0;

	ref		rCannon = GetCannonByType(sti(aCharacter.Ship.Cannons.Type));
	float	fReloadTime = GetCannonReloadTime(rCannon); // boal 28.01.03 - 09.02.05

	float fMultiply = 1.0;
	// boal -->
	// evganat - энциклопедия
	int iBonus = 0;
	if (!ENCYCLOPEDIA_DISABLED && CheckOfficersPerk(aCharacter, "FastReload"))
	{
		if (IsMainCharacter(aCharacter) || IsCompanion(aCharacter))
			iBonus = GetParamPageBonus("FastReload");
	}
    fMultiply = AIShip_isPerksUse(aCharacter.TmpPerks.FastReload, 1.0, 0.9 - 0.01 * iBonus);
	fMultiply = AIShip_isPerksUse(aCharacter.TmpPerks.ImmediateReload, fMultiply, 0.5);

	ref refBaseShip = GetRealShip(sti(aCharacter.ship.Type));
	if (sti(refBaseShip.BaseType) != SHIP_FORT)
	{
        // boal 060804 для компа поблажки
		if (sti(aCharacter.index) != GetMainCharacterIndex())
		{
		    fReloadTime -= MOD_SKILL_ENEMY_RATE; // -10c на невозможном
		}
		// boal <--
		float crewQty  = GetCrewQuantity(aCharacter);
	    float OptCrew  = GetOptCrewQuantity(aCharacter);
	    float MaxCrew  = GetMaxCrewQuantity(aCharacter);
	    float fMorale  = GetCharacterCrewMorale(aCharacter);
	    
	    if (crewQty > MaxCrew) crewQty = MaxCrew; // fix 14/03/05
	    if (OptCrew > 0)
	    {
            float  fExp;
			fExp = 0.001 + stf(GetCrewExp(aCharacter, "Cannoners") * crewQty) / stf(OptCrew * GetCrewExpRate());
			if (fExp > 1) fExp = 1;
			fReloadTime = fReloadTime * (1.0 + (1.0 - fExp) * 3.0);
        }
	    fReloadTime = fReloadTime * (1.0 + (1.0 - fMorale / MORALE_NORMAL) * 0.2);
	    
        if (crewQty <= (GetMinCrewQuantity(aCharacter)))
        {
            fReloadTime = fReloadTime * 3.0; //меньше команды - тормозим
        } 
    // boal  корректный учет команды <--
    }

    // глобальный туториал - перезарядка ГГ ускорена в 5 раз
    if (sti(aCharacter.index) == GetMainCharacterIndex() && GetGlobalTutor())
	{
		fReloadTime = fReloadTime * 0.19;
	}

	return  fMultiply * fReloadTime * fCannonSkill;
}

// calculate delay before fire
float Cannon_GetFireTime()
{
	aref aCharacter = GetEventData();
	string sBort = GetEventData();
	bool isRandom = GetEventData();		// true для случайной задержки в момент реального выстрела, false для расчёта упреждения по среднему числу
	int cannonIndex = GetEventData();	// индекс орудия (от носа к корме) от 0 до количества пушек

	if (CheckAttribute(aCharacter, "AoP_NoShipFire")) return 1000000.0;

	ref refBaseShip = GetRealShip(sti(aCharacter.ship.Type));
	// make 10 seconds random delay between fire from fort cannons
	if (refBaseShip.Name == ShipsTypes[SHIP_FORT].Name) { return frnd() * 20.0; }   // иначе пулеметный залп

	// количество пушек и навык орудий
	int nCannons = GetBortCannonsQty(aCharacter, sBort);

	float fCannonSkill = stf(aCharacter.TmpSkill.Cannons);
	float fFireTime = 1.3 - fCannonSkill;
//	fFireTime = frnd() * fFireTime * 6.0;

//	// режим стрельбы
	bool bRipple = isRandom;
	if(bRipple)
	{
		if (!CheckAttribute(aCharacter, "firemode") || aCharacter.firemode == FIRE_MODE_RANDOM)
			bRipple = false;
		if (cannonIndex <= -1)
			bRipple = false;
		if (sBort != "cannonr" && sBort != "cannonl")
			bRipple = false;
	}

//	// рандом
	float rMin = 0.35;
	float rMax = 4.85;
	float fRandom = 1.0;
	if (bRipple)
	{
		float rAverage = (rMin + rMax) * 0.5;
		rMin = (rMin + rAverage) * 0.5;
		rMax = (rAverage + rMax) * 0.5;
		if(nCannons < 2)
			fRandom = rAverage;
		else if(aCharacter.firemode == FIRE_MODE_DIRECT)
			fRandom = rMin + (rMax - rMin) * cannonIndex / makefloat(nCannons - 1);	// прямой порядок - от носа к корме
		else
			fRandom = rMax - (rMax - rMin) * cannonIndex / makefloat(nCannons - 1); // обратный порядок - от кормы к носу
	}
	else if (isRandom)
		fRandom = rMin + frand(rMax - rMin);
	else
		fRandom = (rMax + rMin) * 0.5;

	if (iArcadeSails) { fFireTime = fFireTime * 0.5; }
				   
	float crewQ   = GetCrewQuantity(aCharacter);
 	float crewMax = stf(refBaseShip.MaxCrew);
 	float crewOpt = stf(refBaseShip.OptCrew);
 	if (crewMax < crewQ) crewQ  = crewMax;
 	
	float fCrewMorale = GetCharacterCrewMorale(aCharacter);

    float  fExp;
	fExp = 0.05 + stf(GetCrewExp(aCharacter, "Cannoners") * crewQ) / stf(crewOpt * GetCrewExpRate());
	if (fExp > 1) fExp = 1;
	
	fFireTime = fFireTime * (2.0 - fExp);
	fFireTime = fFireTime * (1 + (1 - fCrewMorale/MORALE_NORMAL)/5.0);
	
	return fFireTime * fRandom;
}

void Cannon_FireCannon()
{
	float fX, fY, fZ, fSpeedV0, fFireDirection, fFireHeightAngle, fCannonDirAng, fMaxFireDistance, fAngle;

	aref aCharacter = GetEventData();

	DeleteAttribute(aCharacter, "Sea_AI.Cannon.Charge"); //должно располагаться здесь, а не выше

	fX = GetEventData();
	fY = GetEventData();
	fZ = GetEventData();
	fSpeedV0 = GetEventData();
	fFireDirection = GetEventData();
	fFireHeightAngle = GetEventData();
	fCannonDirAng = GetEventData();
	fMaxFireDistance = GetEventData();
	fAngle = GetEventData();
	bool bMode = sti(GetEventData());
	string bort = GetEventData();

	if (CheckAttribute(aCharacter, "AoP_NoShipFire")) return;

	Ball_AddBall(aCharacter, fX, fY, fZ, fSpeedV0, fFireDirection, fFireHeightAngle, fCannonDirAng, fMaxFireDistance, bMode, bort);
}

// Damage 2 cannon from balls
float Cannon_DamageEvent()
{
	//return 0.0;
	aref	aCharacter = GetEventData();
	float	fBallDamage = GetEventData();	// ball damage
	float	fCurDamage = GetEventData();	// current cannon damage (0.0 .. 1.0)
	float	fDistance = GetEventData();		// distance from ball 2 cannon
	float	x = GetEventData();				// x, y, z - cannon position
	float	y = GetEventData();
	float	z = GetEventData();

	if(CheckAttribute(aCharacter, "chr_ai.immortal"))
	{
		if(sti(aCharacter.chr_ai.immortal) == 1)
		{
			return 0.0;
		}
	}

	ref	rCannon = GetCannonByType(sti(aCharacter.Ship.Cannons.Type));
	
	float fMaxCHP = stf(rCannon.hp);
	//fCurDamage = (fCurDamage * fMaxCHP + fBallDamage * (1.0 - fDistance / MAX_CANNON_DAMAGE_DISTANCE)) / fMaxCHP;
    //Log_TestInfo("fBallDamage "  + fBallDamage + " fCurDamage " +fCurDamage + " fMaxCHP " + fMaxCHP + " fDistance " +fDistance);
    fBallDamage *= 0.1 / fDistance;
    fCurDamage =  fCurDamage  + fBallDamage / fMaxCHP;  // TODO
    
	//fCurDamage = fCurDamage - fCurDamage/100*(sti(aCharacter.ship.upgrades.cannons)-1)*20;
	if (fCurDamage >= 1.0)
	{
		fCurDamage = 1.0;
		CreateBlast(x,y,z);
		CreateParticleSystem("blast_inv", x, y, z, 0.0, 0.0, 0.0, 0);
		Play3DSound("cannon_explosion", x, y, z);
		if (sti(aCharacter.index) == GetMainCharacterIndex())
		{
		    Log_Info(XI_ConvertString("Cannon_DamageEvent"));
			PostEvent("refreshCannonsQty", 50);
		}
		aCharacter.Ship.Cargo.RecalculateCargoLoad = true; // boal 27.07.06 пушки - груз
	}

	return fCurDamage;
}

int GetBortIntactCannonsNum(ref rCharacter, string sBort, int iNumCannonsOnBort)
{
	string sBort_real = sBort;
	float fDamage;

	switch (sBort)
	{
		case "rcannon": sBort_real = "cannonr"; break;
		case "lcannon": sBort_real = "cannonl"; break;
		case "fcannon": sBort_real = "cannonf"; break;
		case "bcannon": sBort_real = "cannonb"; break;
	}
	
	if (!CheckAttribute(rCharacter, "Ship.Cannons.Borts." + sBort_real + ".damages") ||
	    !CheckAttribute(rCharacter, "Ship.Cannons.Borts." + sBort + ".damages")) return iNumCannonsOnBort;
				
	aref arDamages;
	if(CheckAttribute(rCharacter, "Ship.Cannons.Borts." + sBort_real + ".damages"))
	{
		makearef(arDamages, rCharacter.Ship.Cannons.Borts.(sBort_real).damages);
	}
	else
	{
		makearef(arDamages, rCharacter.Ship.Cannons.Borts.(sBort).damages);
	}	
	
	int iNumIntactCannons = 0;
	for (int i=0; i<iNumCannonsOnBort; i++)
	{
		fDamage = stf(GetAttributeValue(GetAttributeN(arDamages, i)));
		if (fDamage < 1.0) { iNumIntactCannons++; }
	}
	int iNumRealCannons = iNumIntactCannons;
	
	return iNumIntactCannons;
}


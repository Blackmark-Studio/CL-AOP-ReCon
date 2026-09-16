// > перевод водоизмещения в центнеры
int Tonnes2CWT(int iTonnes)
{
	int a = iTonnes * 10000 / 508;
	a = 100 * ((a + 99) / 100);
	return a;
}

void InitShips()
{
	ref refShip;
	int i, idx;

	for (idx = 0; idx < SHIP_TYPES_QUANTITY_WITH_FORT; idx++)
	{
		makeref(refShip, ShipsTypes[idx]);

		refship.index = idx;

		refship.InertiaAccelerationX = 0.2;		refship.InertiaBrakingX = 0.7;
		refship.InertiaAccelerationY = 0.4;		refship.InertiaBrakingY = 0.4;
		refship.InertiaAccelerationZ = 1.0;		refship.InertiaBrakingZ = 1.0;

		refship.Rocking.y = 0.5;
		refship.Rocking.az = 0.05;

		refship.NetGeraldSails = "";
		refship.Soundtype = "";

		refship.WaterLine = 0.0;
		refship.SpeedDependWeight = 0.0;
		refship.SubSeaDependWeight = 0.0;
		refship.TurnDependWeight = 0.0;
		refship.TurnDependSpeed = 0.0;

		refShip.Height.Bombs.Y		= 3.0;		refShip.Height.Bombs.DY		= 1.0;
		refShip.Height.Grapes.Y		= 4.0;		refShip.Height.Grapes.DY	= 1.0;
		refShip.Height.Knippels.Y	= 25.0;		refShip.Height.Knippels.DY	= 15.0;
		refShip.Height.Balls.Y		= 3.0;		refShip.Height.Balls.DY		= 1.0;

		refship.WindAgainstSpeed   = 1.0;
		refship.CabinType		   = "Cabin_Small"; // потом припишем слово My_ и будет каютой для ГГ
		refShip.AbordageLocation			= "BOARDING_SMALL_DECK";
		refship.DeckType		  = "Low";

		refShip.MaxCaliber	= 12;
		refShip.Cannon		= CANNON_TYPE_CANNON_LBS12;

		aref cannonl, cannonr, cannonb, cannonf;

		refShip.HullsAmount = 3;
		refShip.isNationalHull = false;	// для кораблей с нац.хулами true
		refShip.CannonDiff = 0;			// разброс рандома стволов. По умолчанию 0

		refship.CanEncounter = true;
		refship.Type.Merchant = true;
		refship.Type.War = true;
		refship.Track.Enable = false;
		refShip.FireHeight = 3.0;

		refShip.Massa = 1500000.0;
		refShip.Volume = 900.0;
		refShip.lowpolycrew = 5;
		refShip.buildtime = 10;

		refShip.rcannon = 0;
		refShip.lcannon = 0;
		refShip.fcannon = 0;
		refShip.bcannon = 0;

		ShipsTypes[idx].Cannons.Borts.cannonl = "";
		ShipsTypes[idx].Cannons.Borts.cannonr = "";
		ShipsTypes[idx].Cannons.Borts.cannonf = "";
		ShipsTypes[idx].Cannons.Borts.cannonb = "";

		makearef(cannonl,ShipsTypes[idx].Cannons.Borts.cannonl);
		makearef(cannonr,ShipsTypes[idx].Cannons.Borts.cannonr);
		makearef(cannonf,ShipsTypes[idx].Cannons.Borts.cannonf);
		makearef(cannonb,ShipsTypes[idx].Cannons.Borts.cannonb);

		cannonf.FireZone	= Degree2Radian(30.0);
		cannonf.FireDir		= Degree2Radian(0.0);
		cannonf.FireAngMin	= -0.35;
		cannonf.FireAngMax	= 0.60;

		cannonr.FireZone	= Degree2Radian(80.0);
		cannonr.FireDir		= Degree2Radian(90.0);
		cannonr.FireAngMin	= -0.35;
		cannonr.FireAngMax	= 0.60;

		cannonb.FireZone	= Degree2Radian(30.0);
		cannonb.FireDir		= Degree2Radian(180.0);
		cannonb.FireAngMin	= -0.35;
		cannonb.FireAngMax	= 0.60;

		cannonl.FireZone	= Degree2Radian(80.0);
		cannonl.FireDir		= Degree2Radian(270.0);
		cannonl.FireAngMin	= -0.35;
		cannonl.FireAngMax	= 0.60;
	}

	///////////////////////////////////////////////////////////////////////////
	//// Boat
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BOAT]);
	refShip.Name									= "Boat";
	refship.Soundtype								= "lugger";
	refShip.Class									= 7;
	refShip.Cannon								= CANNON_TYPE_NONECANNON;
	refShip.MaxCaliber							= 0;
	refShip.Weight								= Tonnes2CWT(10);
	refShip.Capacity							= 50;
	refShip.CannonsQuantity						= 0;
	refShip.rcannon								= 0;
	refShip.lcannon								= 0;
	refShip.fcannon								= 0;
	refShip.bcannon								= 0;
	refShip.MaxCrew								= 10; //sailing crew
	refShip.MinCrew								= 2;
	refShip.BoardingCrew						= 0;
	refShip.GunnerCrew							= 0;
	refShip.CannonerCrew						= 0;
	refShip.SailorCrew							= 10;
	refShip.SpeedRate							= 4;
	refShip.TurnRate							= 40;
	refShip.Price								= 100;
	refShip.HP									= 100;
	refShip.SP									= 100;
	refship.CanEncounter						= false;
	refship.Type.Merchant						= false;
	refship.Type.War							= false;
	refShip.lowpolycrew = 0;

	refship.WaterLine							= -0.3;

	refShip.Massa = 10000.0;
	refShip.Volume = 100.0;

	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 0.4;	refship.InertiaBrakingY		= 0.2;
	refship.InertiaAccelerationZ	= 0.15;	refship.InertiaBrakingZ		= 0.05;

///////////////////////////////////////////////////////////////////////////
//// Boat
///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SHELL]);
	refShip.Name									= "Skorlupka";
	refship.Soundtype								= "lugger";
	refShip.Class									= 7;
	refShip.Cannon								= CANNON_TYPE_NONECANNON;
	refShip.MaxCaliber							= 0;
	refShip.Weight								= Tonnes2CWT(10);
	refShip.Capacity							= 50;
	refShip.CannonsQuantity						= 0;
	refShip.rcannon								= 0;
	refShip.lcannon								= 0;
	refShip.fcannon								= 0;
	refShip.bcannon								= 0;
	refShip.MaxCrew								= 10; //sailing crew
	refShip.MinCrew								= 2;
	refShip.BoardingCrew						= 0;
	refShip.GunnerCrew							= 0;
	refShip.CannonerCrew						= 0;
	refShip.SailorCrew							= 10;
	refShip.SpeedRate							= 4;
	refShip.TurnRate							= 40;
	refShip.Price								= 100;
	refShip.HP									= 100;
	refShip.SP									= 100;
	refship.CanEncounter						= false;
	refship.Type.Merchant						= false;
	refship.Type.War							= false;
	refShip.lowpolycrew = 0;

	refship.WaterLine							= -0.3;

	refShip.Massa = 10000.0;
	refShip.Volume = 100.0;

	refship.InertiaAccelerationX	= 5.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY	= 0.4;	refship.InertiaBrakingY		= 0.2;
	refship.InertiaAccelerationZ	= 0.15;	refship.InertiaBrakingZ		= 0.05;

//	============================================================ Class 7 ===============================================================

	///////////////////////////////////////////////////////////////////////////
	//// Баркас
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BARKAS]);
	refShip.Name						= "Barkas";
	refship.Soundtype					= "lugger";
	refShip.Class						= 7;
	refShip.Cannon						= CANNON_TYPE_NONECANNON;
	refShip.MaxCaliber					= 0;
	refShip.Weight						= Tonnes2CWT(10);
	refShip.Capacity					= 60;

	refShip.CannonsQuantity				= 0;
	refShip.rcannon						= 0;
	refShip.lcannon						= 0;
	refShip.fcannon						= 0;
	refShip.bcannon						= 0;

	refShip.MaxCrew						= 12;
	refShip.MinCrew						= 3;
	refShip.BoardingCrew				= 2;
	refShip.GunnerCrew					= 2;
	refShip.CannonerCrew				= 16;
	refShip.SailorCrew					= 20;

	refShip.SpeedRate					= 8.0;
	refShip.TurnRate					= 50;
	refShip.Price						= 650;
	refShip.HP							= 105;
	refShip.SP							= 100;
	refship.CabinType					= "Cabin_Small3";
	refship.CanEncounter				= false;
	refship.Type.Merchant				= false;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 10.0;
	refShip.sea_enchantment				= 4.0;
	refShip.lowpolycrew					= 2;
	refShip.buildtime					= 10;

	refShip.Massa						= 10000.0;
	refShip.Volume						= 20.0;
	refship.WaterLine					= -0.05;
	refship.WindAgainstSpeed			= 8.0;

	refship.InertiaAccelerationX		= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY		= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ		= 5.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.Height.Bombs.Y				= 0.4;	refShip.Height.Bombs.DY		= 0.2;
	refShip.Height.Grapes.Y				= 1.3;	refShip.Height.Grapes.DY	= 0.6;
	refShip.Height.Knippels.Y			= 6.5;	refShip.Height.Knippels.DY	= 5.8;
	refShip.Height.Balls.Y				= 0.4;	refShip.Height.Balls.DY		= 0.2;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 9;
	refship.Track1.Width				= "1.0, 2.0";
	refship.Track1.Speed				= "5.2, 6.2";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7;
	refship.Track2.Width				= "1.2, 2.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	//// Тартана
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_TARTANE]);
	refShip.Name						= "Tartane";
	refship.Soundtype					= "lugger";
	refShip.Class						= 7;
	refShip.Cannon						= CANNON_TYPE_NONECANNON;
	refShip.MaxCaliber					= 0;
	refShip.Weight						= Tonnes2CWT(10);
	refShip.Capacity					= 155;

	refShip.CannonsQuantity				= 0;
	refShip.rcannon						= 0;
	refShip.lcannon						= 0;
	refShip.fcannon						= 0;
	refShip.bcannon						= 0;

	refShip.MaxCrew						= 17;
	refShip.MinCrew						= 4;
	refShip.BoardingCrew				= 2;
	refShip.GunnerCrew					= 2;
	refShip.CannonerCrew				= 16;
	refShip.SailorCrew					= 20;

	refShip.SpeedRate					= 8.8;
	refShip.TurnRate					= 55;
	refShip.Price						= 1000;
	refShip.HP							= 215;
	refShip.SP							= 100;
	refship.CabinType					= "Cabin_Small3";
	refship.CanEncounter				= false;
	refship.Type.Merchant				= false;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 10.0;
	refShip.sea_enchantment				= 4.0;
	refShip.lowpolycrew					= 3;
	refShip.buildtime					= 10;

	refShip.Massa						= 10000.0;
	refShip.Volume						= 20.0;
	refship.WaterLine					= 0.1;
	refship.WindAgainstSpeed			= 8.7;

	refship.InertiaAccelerationX		= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY		= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ		= 5.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.Height.Bombs.Y				= 0.4;	refShip.Height.Bombs.DY		= 0.2;
	refShip.Height.Grapes.Y				= 1.3;	refShip.Height.Grapes.DY	= 0.6;
	refShip.Height.Knippels.Y			= 6.5;	refShip.Height.Knippels.DY	= 5.8;
	refShip.Height.Balls.Y				= 0.4;	refShip.Height.Balls.DY		= 0.2;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 9;
	refship.Track1.Width				= "1.0, 2.0";
	refship.Track1.Speed				= "5.2, 6.2";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7;
	refship.Track2.Width				= "1.2, 2.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	//// Леудо
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LIUTO]);
	refShip.Name						= "Liuto";
	refship.Soundtype					= "lugger";
	refShip.Class						= 7;
	refShip.Cannon						= CANNON_TYPE_NONECANNON;
	refShip.MaxCaliber					= 0;
	refShip.Weight						= Tonnes2CWT(10);
	refShip.Capacity					= 400;

	refShip.CannonsQuantity				= 0;
	refShip.rcannon						= 0;
	refShip.lcannon						= 0;
	refShip.fcannon						= 0;
	refShip.bcannon						= 0;

	refShip.MaxCrew						= 21;
	refShip.MinCrew						= 4;
	refShip.BoardingCrew				= 2;
	refShip.GunnerCrew					= 2;
	refShip.CannonerCrew				= 16;
	refShip.SailorCrew					= 20;

	refShip.SpeedRate					= 10.6;
	refShip.TurnRate					= 55;
	refShip.Price						= 2250;
	refShip.HP							= 325;
	refShip.SP							= 100;
	refship.CabinType					= "Cabin_Small3";
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 12.0;
	refShip.sea_enchantment				= 4.0;
	refShip.lowpolycrew					= 2;
	refShip.buildtime					= 10;

	refShip.Massa						= 10000.0;
	refShip.Volume						= 20.0;
	refship.WaterLine					= -0.3;
	refship.WindAgainstSpeed			= 9.5;

	refship.InertiaAccelerationX		= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY		= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ		= 5.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.Height.Bombs.Y				= 0.4;	refShip.Height.Bombs.DY		= 0.2;
	refShip.Height.Grapes.Y				= 1.3;	refShip.Height.Grapes.DY	= 0.6;
	refShip.Height.Knippels.Y			= 6.5;	refShip.Height.Knippels.DY	= 5.8;
	refShip.Height.Balls.Y				= 0.4;	refShip.Height.Balls.DY		= 0.2;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 9;
	refship.Track1.Width				= "1.0, 2.0";
	refship.Track1.Speed				= "5.2, 6.2";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7;
	refship.Track2.Width				= "1.2, 2.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	//// Дау
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_WAR_TARTANE]);
	refShip.Name						= "WarTartane";
	refship.Soundtype					= "lugger";
	refShip.Class						= 7;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS3;
	refShip.MaxCaliber					= 3;
	refShip.Weight						= Tonnes2CWT(30);
	refShip.Capacity					= 390;

	refShip.CannonsQuantity				= 6;
	refShip.rcannon						= 3;
	refShip.lcannon						= 3;
	refShip.fcannon						= 0;
	refShip.bcannon						= 0;

	refShip.MaxCrew						= 29;
	refShip.MinCrew						= 5;
	refShip.BoardingCrew				= 2;
	refShip.GunnerCrew					= 2;
	refShip.CannonerCrew				= 16;
	refShip.SailorCrew					= 20;

	refShip.SpeedRate					= 12.2;
	refShip.TurnRate					= 65;
	refShip.Price						= 4500;
	refShip.HP							= 360;
	refShip.SP							= 100;
	refship.CabinType					= "Cabin_Small3";
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 9.0;
	refShip.sea_enchantment				= 4.0;
	refShip.lowpolycrew					= 3;
	refShip.buildtime					= 10;

	refShip.Massa						= 50000.0;
	refShip.Volume						= 100.0;

	refship.WaterLine					= 0.1;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.4;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 10.9;

	refship.InertiaAccelerationX		= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY		= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ		= 5.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 1.8;	refShip.Height.Grapes.DY	= 0.9;
	refShip.Height.Knippels.Y			= 6.7;	refShip.Height.Knippels.DY	= 6.7;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "1.0, 2.0";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "1.2, 2.0";
	refship.Track2.Speed	= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	//// Фелюка
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FELUCA]);
	refShip.Name						= "Feluca";
	refship.Soundtype					= "lugger";
	refShip.Class						= 7;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS6;
	refShip.MaxCaliber					= 6;
	refShip.Weight						= Tonnes2CWT(10);
	refShip.Capacity					= 540;

	refShip.CannonsQuantity				= 8;
	refShip.rcannon						= 4;
	refShip.lcannon						= 4;
	refShip.fcannon						= 0;
	refShip.bcannon						= 0;

	refShip.MaxCrew						= 40;
	refShip.MinCrew						= 5;
	refShip.BoardingCrew				= 2;
	refShip.GunnerCrew					= 2;
	refShip.CannonerCrew				= 16;
	refShip.SailorCrew					= 20;

	refShip.SpeedRate					= 12.1;
	refShip.TurnRate					= 55;
	refShip.Price						= 7000;
	refShip.HP							= 410;
	refShip.SP							= 100;
	refship.CabinType					= "Cabin_Small3";
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 8.4;
	refShip.sea_enchantment				= 4.0;
	refShip.lowpolycrew					= 3;
	refShip.buildtime					= 10;

	refShip.Massa						= 50000.0;
	refShip.Volume						= 100.0;

	refship.WaterLine					= -0.25;
	refship.SpeedDependWeight			= 0.07;
	refship.SubSeaDependWeight			= 0.4;
	refship.TurnDependWeight			= 0.8;
	refship.WindAgainstSpeed			= 9.2;

	refship.InertiaAccelerationX		= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY		= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ		= 5.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 1.0;	refShip.Height.Grapes.DY	= 0.5;
	refShip.Height.Knippels.Y			= 11.0;	refShip.Height.Knippels.DY	= 3.5;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "1.0, 2.0";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "1.2, 2.0";
	refship.Track2.Speed	= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	//// Кеч (быв. билансетта)
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BILANCETTA]);
	refShip.Name						= "Bilancetta";
	refship.Soundtype					= "lugger";
	refShip.Class						= 7;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS6;
	refShip.MaxCaliber					= 6;
	refShip.Weight						= Tonnes2CWT(80);
	refShip.Capacity					= 420;

	refShip.CannonsQuantity				= 8;
	refShip.rcannon 					= 4;
	refShip.lcannon 					= 4;
	refShip.fcannon 					= 0;
	refShip.bcannon 					= 0;

	refShip.MaxCrew						= 47;
	refShip.MinCrew						= 8;
	refShip.BoardingCrew				= 70;
	refShip.GunnerCrew					= 12;
	refShip.CannonerCrew				= 48;
	refShip.SailorCrew					= 120;

	refShip.SpeedRate					= 13.5;
	refShip.TurnRate					= 54.0;
	refShip.Price						= 9500;
	refShip.HP							= 540;
	refShip.SP							= 100;
	refship.CabinType					= "Cabin_Small2";
	refship.CanEncounter				= true;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew					= 4;
	refShip.buildtime					= 15;

	refShip.Massa						= 50000.0;
	refShip.Volume						= 100.0;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 0.1;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed   			= 8.7;

	refship.InertiaAccelerationX		= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY		= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ		= 10.0;	refship.InertiaBrakingZ		= 10.0;

	refShip.Height.Bombs.Y				= 1.65;	refShip.Height.Bombs.DY		= 1.35;
	refShip.Height.Grapes.Y				= 2.64;	refShip.Height.Grapes.DY	= 0.5;
	refShip.Height.Knippels.Y			= 14.64;refShip.Height.Knippels.DY	= 13.5;
	refShip.Height.Balls.Y				= 1.65;	refShip.Height.Balls.DY		= 1.35;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.0;
	refship.Track1.LifeTime 			= 9;
	refship.Track1.Width				= "1.5, 3.0";
	refship.Track1.Speed				= "5.0, 6.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime 			= 7;
	refship.Track2.Width				= "1.2, 2.2";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	//// War Tartane Баркас оригинал
	///////////////////////////////////////////////////////////////////////////
	/*makeref(refShip,ShipsTypes[SHIP_WAR_TARTANE]);
	refShip.Name								= "WarTartane";
	refship.Soundtype							= "lugger";
	refShip.Class								= 7;
	refShip.Cannon								= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber							= 8;
	refShip.Weight								= Tonnes2CWT(10);
	refShip.Capacity							= 210;
	refShip.CannonsQuantity						= 8;
	refShip.rcannon								= 4;
	refShip.lcannon								= 4;
	refShip.fcannon								= 0;
	refShip.bcannon								= 0;
	refShip.MaxCrew								= 20;
	refShip.MinCrew								= 3;
	refShip.BoardingCrew						= 2;
	refShip.GunnerCrew							= 2;
	refShip.CannonerCrew						= 16;
	refShip.SailorCrew							= 20;
	refShip.SpeedRate							= 14.0;
	refShip.TurnRate							= 70;
	refShip.Price								= 2500;
	refShip.HP									= 210;
	refShip.SP									= 100;
	refship.CabinType							= "Cabin_Small3";
	refship.CanEncounter					= true;
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 10.0;
	refShip.sea_enchantment					= 4.0;
	refShip.lowpolycrew						= 3;
	refShip.buildtime = 10;

	refShip.Massa = 50000.0;
	refShip.Volume = 100.0;

	refship.WaterLine					= 0.1;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.4;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 7.0;

	refship.InertiaAccelerationX	= 3.0;	refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY	= 14;	refship.InertiaBrakingY		= 5;
	refship.InertiaAccelerationZ	= 5.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 1.8;	refShip.Height.Grapes.DY	= 0.9;
	refShip.Height.Knippels.Y			= 6.7;	refShip.Height.Knippels.DY	= 6.7;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 9;
	refship.Track1.Width	= "1.0, 2.0";
	refship.Track1.Speed	= "5.2, 6.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 7;
	refship.Track2.Width	= "1.2, 2.0";
	refship.Track2.Speed	= "0.15, 0.25"; */

//	============================================================ Class 6 ===============================================================

	///////////////////////////////////////////////////////////////////////////
	//// Люггер
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LUGGER]);
	refShip.Name						= "Lugger";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber					= 8;
	refShip.Weight						= Tonnes2CWT(150);
	refShip.Capacity					= 725;

	refShip.CannonsQuantity				= 12;
	refShip.CannonDiff					= 1;	// 12, 10
	refShip.rcannon						= 4;
	refShip.lcannon						= 4;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 50;
	refShip.MinCrew						= 11;
	refShip.BoardingCrew				= 25;
	refShip.GunnerCrew					= 6;
	refShip.CannonerCrew				= 24;
	refShip.SailorCrew					= 50;

	refShip.SpeedRate					= 14.4;
	refShip.TurnRate					= 57.0;
	refShip.Price						= 14000;
	refShip.HP							= 730;
	refShip.SP							= 100;
	refship.CabinType					= "Cabin_Small2";
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew					= 5;
	refShip.buildtime					= 20;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 0.2;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 9.2;

	refship.InertiaAccelerationX		= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY		= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ		= 10.0;	refship.InertiaBrakingZ		= 10.0;

	refShip.Height.Bombs.Y				= 2.1;	refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.1;	refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 10.5;	refShip.Height.Knippels.DY	= 8.5;
	refShip.Height.Balls.Y				= 2.1;	refShip.Height.Balls.DY		= 1.0;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 9;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "8.0, 10.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7;
	refship.Track2.Width				= "3.0, 4.5";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	//// Курьерский люггер
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CAREERLUGGER]);
	refShip.Name            			= "Lugger_c";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon          			= CANNON_TYPE_CANNON_LBS6;
	refShip.MaxCaliber      			= 6;
	refShip.Weight						= Tonnes2CWT(120);
	refShip.Capacity        			= 550;
	refShip.CannonsQuantity				= 10; // 0,2,4,4	0,2,3,3
	refShip.CannonDiff					= 1;	// 10, 8
	refShip.rcannon 					= 4;
	refShip.lcannon 					= 4;
	refShip.fcannon 					= 0;
	refShip.bcannon 					= 2;

	refShip.MaxCrew         			= 44;
	refShip.MinCrew         			= 9;
	refShip.SpeedRate       			= 15.15;
	refShip.TurnRate        			= 65.0;
	refShip.Price           			= 10100;
	refShip.HP              			= 620;
	refShip.SP              			= 100;

	refship.CabinType					= "Cabin_Small2";

	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.lowpolycrew 				= 5;

	refship.Rocking.y 					= 0.5;
	refship.Rocking.az 					= 0.035;

	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 9.9;

	refship.InertiaAccelerationX		= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY		= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ		= 10.0;	refship.InertiaBrakingZ		= 10.0;

	refShip.Height.Bombs.Y				= 1.65;	refShip.Height.Bombs.DY		= 1.35;
	refShip.Height.Grapes.Y				= 2.64;	refShip.Height.Grapes.DY	= 0.5;
	refShip.Height.Knippels.Y			= 14.64; refShip.Height.Knippels.DY	= 13.5;
	refShip.Height.Balls.Y				= 1.65;	refShip.Height.Balls.DY		= 1.35;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime 			= 9;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "8.0, 10.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime 			= 7;
	refship.Track2.Width				= "3.0, 4.5";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england				= true;
	refship.nation.france				= true;
	refship.nation.spain				= true;
	refship.nation.holland				= true;
	refship.nation.pirate				= false;

	///////////////////////////////////////////////////////////////////////////
	//// Шлюп
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SLOOP]);
	refShip.Name						= "Sloop";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber					= 8;
	refShip.Weight						= Tonnes2CWT(170);
	refShip.Capacity					= 900;

	refShip.CannonsQuantity				= 14; // 2,2,5,5
	refShip.CannonDiff					= 0;  // 14
	refShip.rcannon 					= 5;
	refShip.lcannon 					= 5;
	refShip.fcannon 					= 2;
	refShip.bcannon 					= 2;

	refShip.MaxCrew						= 62;
	refShip.MinCrew						= 12;
	refShip.BoardingCrew				= 40;
	refShip.GunnerCrew					= 5;
	refShip.CannonerCrew				= 32;
	refShip.SailorCrew					= 80;

	refShip.SpeedRate					= 13.1;
	refShip.TurnRate					= 48.0;
	refShip.Price						= 21000;
	refShip.HP							= 1055;
	refShip.SP							= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 5;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew					= 6;
	refShip.buildtime					= 20;

	refship.Rocking.y					= 0.45;
	refship.Rocking.az					= 0.02;

	refship.CabinType					= "Cabin_Small4";

	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 8.0;

	refShip.Height.Bombs.Y				= 1.6;	refShip.Height.Bombs.DY		= 1.25;
	refShip.Height.Grapes.Y				= 2.75;	refShip.Height.Grapes.DY	= 0.6;
	refShip.Height.Knippels.Y			= 13.2;	refShip.Height.Knippels.DY	= 8.5;
	refShip.Height.Balls.Y				= 1.6;	refShip.Height.Balls.DY		= 1.25;

	refship.InertiaAccelerationX		= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY		= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ		= 8.0;	refship.InertiaBrakingZ		= 8.0;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 9;
	refship.Track1.Width				= "2.0, 2.5";
	refship.Track1.Speed				= "5.2, 6.2";

	refship.Track2.ZStart				= -0.05;
	refship.Track2.LifeTime				= 7;
	refship.Track2.Width				= "3.0, 4.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	//// Хой
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SLOOP_W]);
	refShip.Name						= "Sloop_w";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS6;
	refShip.MaxCaliber					= 8;
	refShip.Weight						= Tonnes2CWT(175);
	refShip.Capacity					= 990;

	refShip.CannonsQuantity				= 14;
	refShip.CannonDiff					= 1;	// 14, 12
	refShip.rcannon						= 5;
	refShip.lcannon						= 5;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 68;
	refShip.MinCrew						= 16;
	refShip.BoardingCrew				= 40;
	refShip.GunnerCrew					= 5;
	refShip.CannonerCrew				= 32;
	refShip.SailorCrew					= 80;

	refShip.SpeedRate					= 12.3;
	refShip.TurnRate					= 50.0;
	refShip.Price						= 20000;
	refShip.HP							= 860;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 5;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew					= 6;
	refShip.buildtime					= 20;

	refship.Rocking.y					= 0.45;
	refship.Rocking.az					= 0.02;

	refship.CabinType					= "Cabin_Small4";

	refship.WaterLine					= 0.4;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.16;
	refship.WindAgainstSpeed			= 8.9;

	refShip.Height.Bombs.Y				= 1.0;	refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 1.1;	refShip.Height.Grapes.DY	= 0.5;
	refShip.Height.Knippels.Y			= 13.2;	refShip.Height.Knippels.DY	= 8.9;
	refShip.Height.Balls.Y				= 1.0;	refShip.Height.Balls.DY		= 0.5;

	refship.InertiaAccelerationX		= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY		= 9;	refship.InertiaBrakingY		= 9;
	refship.InertiaAccelerationZ		= 8.0;	refship.InertiaBrakingZ		= 8.0;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 9;
	refship.Track1.Width				= "2.0, 2.5";
	refship.Track1.Speed				= "5.2, 6.2";

	refship.Track2.ZStart				= -0.05;
	refship.Track2.LifeTime				= 7;
	refship.Track2.Width				= "3.0, 4.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	//////////////////////////////////////////////////////////////////////////
	//// Куттер
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CUTTER]);
	refShip.Name						= "Cutter";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber					= 8;
	refShip.Weight						= Tonnes2CWT(170);
	refShip.Capacity					= 700;

	refShip.CannonsQuantity				= 16;
	refShip.CannonDiff					= 1;	//16, 14
	refShip.rcannon						= 6;
	refShip.lcannon						= 6;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 66;
	refShip.MinCrew						= 18;
	refShip.BoardingCrew				= 40;
	refShip.GunnerCrew					= 5;
	refShip.CannonerCrew				= 32;
	refShip.SailorCrew					= 80;

	refShip.SpeedRate					= 14.0;
	refShip.TurnRate					= 53.5;
	refShip.Price						= 23500;
	refShip.HP							= 945;
	refShip.SP							= 100;

	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 5;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew					= 7;
	refShip.buildtime					= 20;

	refship.Rocking.y					= 0.45;
	refship.Rocking.az					= 0.02;

	refship.CabinType					= "Cabin_Small";

	refship.WaterLine					= -0.2;

	refship.SpeedDependWeight			= 0.22;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 8.0;

	refShip.Height.Bombs.Y				= 2.0;	refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.8;	refShip.Height.Grapes.DY	= 1.9;
	refShip.Height.Knippels.Y			= 15.2;	refShip.Height.Knippels.DY	= 13.9;
	refShip.Height.Balls.Y				= 2.0;	refShip.Height.Balls.DY		= 1.0;

	refship.InertiaAccelerationX		= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY		= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ		= 8.0;	refship.InertiaBrakingZ		= 8.0;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 9;
	refship.Track1.Width				= "2.0, 2.5";
	refship.Track1.Speed				= "5.2, 6.2";

	refship.Track2.ZStart				= -0.05;
	refship.Track2.LifeTime				= 7;
	refship.Track2.Width				= "3.0, 4.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england				= true;
	refship.nation.france				= true;
	refship.nation.spain				= true;
	refship.nation.holland				= true;
	refship.nation.pirate				= true;

//	============================================================ Class 5 ===============================================================

	//////////////////////////////////////////////////////////////////////////
	//// Торговая Шхуна
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SCHOONER]);
	refShip.Name						= "Schooner";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber					= 8;
	refShip.Weight						= Tonnes2CWT(250);
	refShip.Capacity					= 1600;

	refShip.CannonsQuantity				= 12;
	refShip.CannonDiff					= 1;	// 12, 10
	refShip.rcannon						= 5;
	refShip.lcannon						= 5;
	refShip.fcannon						= 0;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 115;
	refShip.MinCrew						= 22;
	refShip.BoardingCrew				= 60;
	refShip.GunnerCrew					= 12;
	refShip.CannonerCrew				= 40;
	refShip.SailorCrew					= 120;
	refShip.SpeedRate					= 13.9;
	refShip.TurnRate					= 44.0;
	refShip.Price						= 28000;
	refShip.HP							= 1270;
	refShip.SP							= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 8.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew					= 10;
	refShip.buildtime					= 40;

	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.03;

	refship.CabinType					= "Cabin_Medium3";

	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.2;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 8.1;

	refship.InertiaAccelerationX		= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY		= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ		= 6.0;

	refShip.Height.Bombs.Y				= 1.7;		refShip.Height.Bombs.DY		= 0.8;
	refShip.Height.Grapes.Y				= 2.9;		refShip.Height.Grapes.DY	= 1.4;
	refShip.Height.Knippels.Y			= 13.9;		refShip.Height.Knippels.DY	= 13.7;
	refShip.Height.Balls.Y				= 1.7;		refShip.Height.Balls.DY		= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 8;
	refship.Track1.Width				= "1.2, 2.2";
	refship.Track1.Speed				= "7.2, 8.2";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 6;
	refship.Track2.Width				= "2.2, 3.2";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	//////////////////////////////////////////////////////////////////////////
	//// Военная Шхуна
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SCHOONER_W]);
	refShip.Name						= "Schooner_w";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS12;
	refShip.MaxCaliber					= 12;
	refShip.Weight						= Tonnes2CWT(220);
	refShip.Capacity					= 1350;

	refShip.CannonsQuantity				= 18;
	refShip.CannonDiff					= 1;	// 18, 16
	refShip.rcannon						= 7;
	refShip.lcannon						= 7;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 128;
	refShip.MinCrew						= 24;
	refShip.BoardingCrew				= 60;
	refShip.GunnerCrew					= 12;
	refShip.CannonerCrew				= 40;
	refShip.SailorCrew					= 120;
	refShip.SpeedRate					= 13.1;
	refShip.TurnRate					= 48.0;
	refShip.Price						= 30500;
	refShip.HP							= 1400;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 9.5;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew					= 12;
	refShip.buildtime					= 40;

	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.03;

	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.2;
	refship.TurnDependWeight			= 0.3;

	refship.WindAgainstSpeed			= 9.2;

	refship.CabinType					= "Cabin_Medium4";

	refship.InertiaAccelerationX		= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY		= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ		= 6.0;

	refShip.Height.Bombs.Y				= 1.7;		refShip.Height.Bombs.DY		= 0.8;
	refShip.Height.Grapes.Y				= 2.9;		refShip.Height.Grapes.DY	= 1.4;
	refShip.Height.Knippels.Y			= 13.9;		refShip.Height.Knippels.DY	= 13.7;
	refShip.Height.Balls.Y				= 1.7;		refShip.Height.Balls.DY		= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 8;
	refship.Track1.Width				= "1.2, 2.2";
	refship.Track1.Speed				= "7.2, 8.2";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 6;
	refship.Track2.Width				= "2.2, 3.2";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

	/*//////////////////////////////////////////////////////////////////////////
	//// Шхуна ориг. на квест
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SCHOONER]);
	refShip.Name						= "Schooner";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS12;
	refShip.MaxCaliber					= 16;
	refShip.Weight						= Tonnes2CWT(200);
	refShip.Capacity					= 1300;
	refShip.CannonsQuantity				= 20;
	refShip.rcannon						= 8;
	refShip.lcannon						= 8;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;
	refShip.MaxCrew						= 120;
	refShip.MinCrew						= 24;
	refShip.BoardingCrew				= 60;
	refShip.GunnerCrew					= 12;
	refShip.CannonerCrew				= 40;
	refShip.SailorCrew					= 120;
	refShip.SpeedRate					= 13.0;
	refShip.TurnRate					= 35.0;
	refShip.Price						= 35000;
	refShip.HP							= 1250;
	refShip.SP							= 100;
	refship.CabinType					= "Cabin_Medium3";
	refship.Type.Merchant					= true;
	refship.Type.War						= true;
	refShip.fWindAgainstSpeed				= 8.0;
	refShip.sea_enchantment					= 2.0;
	refShip.lowpolycrew = 12;
	refShip.buildtime = 40;

	refship.Rocking.y = 0.4;
	refship.Rocking.az = 0.03;

	refship.WaterLine					= -0.2;

	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.2;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed   = 7.5;

	refship.InertiaAccelerationX	= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY	= 6;		refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ	= 6.0;	refship.InertiaBrakingZ		= 6.0;

	refShip.Height.Bombs.Y				= 1.7;		refShip.Height.Bombs.DY		= 0.8;
	refShip.Height.Grapes.Y				= 2.9;		refShip.Height.Grapes.DY	= 1.4;
	refShip.Height.Knippels.Y			= 13.9;		refShip.Height.Knippels.DY	= 13.7;
	refShip.Height.Balls.Y				= 1.7;		refShip.Height.Balls.DY		= 0.8;

	refship.Track.Enable	= true;
	refship.Track1.ZStart	= 0.20;
	refship.Track1.LifeTime = 8;
	refship.Track1.Width	= "1.2, 2.2";
	refship.Track1.Speed	= "7.2, 8.2";

	refship.Track2.ZStart	= -0.15;
	refship.Track2.LifeTime = 6;
	refship.Track2.Width	= "2.2, 3.2";
	refship.Track2.Speed	= "0.15, 0.25";*/

	///////////////////////////////////////////////////////////////////////////
	/// Торговый Барк
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BARQUE]);
	refShip.Name						= "Barque";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber					= 8;
	refShip.Weight						= Tonnes2CWT(350);
	refShip.Capacity					= 1800;

	refShip.CannonsQuantity				= 14;
	refShip.CannonDiff					= 1;	// 14, 12
	refShip.rcannon						= 6;
	refShip.lcannon						= 6;
	refShip.fcannon						= 0;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 120;
	refShip.MinCrew						= 20;
	refShip.BoardingCrew				= 40;
	refShip.GunnerCrew					= 8;
	refShip.CannonerCrew				= 32;
	refShip.SailorCrew					= 80;
	refShip.SpeedRate					= 10.2;
	refShip.TurnRate					= 31.5;
	refShip.Price						= 26500;
	refShip.HP							= 1500;
	refShip.SP							= 100;

	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 3.1;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 9;
	refShip.buildtime					= 40;

	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.025;

	refship.CabinType					= "Cabin_Medium3";

	refship.WaterLine					= 0.15;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.8;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 6.5;

	refShip.Height.Bombs.Y				= 3.3;	refShip.Height.Bombs.DY		= 1.6;
	refShip.Height.Grapes.Y				= 4.9;	refShip.Height.Grapes.DY	= 2.4;
	refShip.Height.Knippels.Y			= 15.8;	refShip.Height.Knippels.DY	= 12.4;
	refShip.Height.Balls.Y				= 3.3;	refShip.Height.Balls.DY		= 1.6;

	refship.InertiaAccelerationX		= 4.0;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY		= 4;	refship.InertiaBrakingY		= 4.0;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ		= 6.0;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 7.5;
	refship.Track1.Width				= "6.0, 7.0";
	refship.Track1.Speed				= "7.2, 9.2";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 5.0;
	refship.Track2.Width				= "6.0, 8.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	/// Усиленный Барк
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BARQUE_W]);
	refShip.Name						= "Barque_w";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon						= CANNON_TYPE_CULVERINE_LBS12;
	refShip.MaxCaliber					= 12;
	refShip.Weight						= Tonnes2CWT(350);
	refShip.Capacity					= 1400;

	refShip.CannonsQuantity				= 16;
	refShip.CannonDiff					= 1;	// 16, 14
	refShip.rcannon						= 6;
	refShip.lcannon						= 6;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 138;
	refShip.MinCrew						= 18;
	refShip.BoardingCrew				= 40;
	refShip.GunnerCrew					= 8;
	refShip.CannonerCrew				= 32;
	refShip.SailorCrew					= 80;
	refShip.SpeedRate					= 11.3;
	refShip.TurnRate					= 37.0;
	refShip.Price						= 28500;
	refShip.HP							= 1700;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 3.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 11;
	refShip.buildtime					= 40;

	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.025;

	refship.CabinType					= "Cabin_Medium4";

	refship.WaterLine					= 0.5;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.8;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 6.7;

	refShip.Height.Bombs.Y				= 3.3;	refShip.Height.Bombs.DY		= 1.6;
	refShip.Height.Grapes.Y				= 4.9;	refShip.Height.Grapes.DY	= 2.4;
	refShip.Height.Knippels.Y			= 15.8;	refShip.Height.Knippels.DY	= 12.4;
	refShip.Height.Balls.Y				= 3.3;	refShip.Height.Balls.DY		= 1.6;

	refship.InertiaAccelerationX		= 4.0;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY		= 4;	refship.InertiaBrakingY		= 4.0;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ		= 6.0;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 7.5;
	refship.Track1.Width				= "6.0, 7.0";
	refship.Track1.Speed				= "7.2, 9.2";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 5.0;
	refship.Track2.Width				= "6.0, 8.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england				= true;
	refship.nation.france				= true;
	refship.nation.spain				= true;
	refship.nation.holland				= true;
	refship.nation.pirate				= false;

	//////////////////////////////////////////////////////////////////////////
	// Лёгкая Щебека
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_XEBEK_L]);
	refShip.Name						= "Xebek_l";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS12;
	refShip.MaxCaliber					= 12;
	refShip.Weight						= Tonnes2CWT(380);
	refShip.Capacity					= 1350;

	refShip.CannonsQuantity				= 18;
	refShip.CannonDiff					= 1;	// 18, 16
	refShip.rcannon						= 7;
	refShip.lcannon						= 7;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 130;
	refShip.MinCrew						= 21;
	refShip.BoardingCrew				= 130;
	refShip.GunnerCrew					= 20;
	refShip.CannonerCrew				= 38;
	refShip.SailorCrew					= 220;

	refShip.SpeedRate					= 14.0;
	refShip.TurnRate					= 50.0;
	refShip.Price						= 32555;
	refShip.HP							= 1520;
	refShip.SP							= 100;

	refship.CabinType					= "Cabin_Medium5";
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 7;
	refShip.buildtime					= 60;
	refship.WindAgainstSpeed			= 9.2;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= 0.2;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;

	refship.InertiaAccelerationX		= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY		= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y				= 1.7;		refShip.Height.Bombs.DY	= 0.8;
	refShip.Height.Grapes.Y				= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y			= 10.1;		refShip.Height.Knippels.DY	= 9.2;
	refShip.Height.Balls.Y				= 1.7;		refShip.Height.Balls.DY	= 0.8;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "4.0, 6.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england				= false;
	refship.nation.france				= true;
	refship.nation.spain				= true;
	refship.nation.holland				= true;
	refship.nation.pirate				= true;

//	============================================================ Class 4 ===============================================================

	///////////////////////////////////////////////////////////////////////////
	/// Баркентина (Ориг.)
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BARKENTINE]);
	refShip.Name						= "Barkentine";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS12;
	refShip.MaxCaliber					= 12;
	refShip.Weight						= Tonnes2CWT(350);
	refShip.Capacity					= 2000;

	refShip.CannonsQuantity				= 16;
	refShip.CannonDiff					= 1;	// 16, 14
	refShip.rcannon						= 6;
	refShip.lcannon						= 6;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 157;
	refShip.MinCrew						= 28;
	refShip.BoardingCrew				= 95;
	refShip.GunnerCrew					= 20;
	refShip.CannonerCrew				= 38;
	refShip.SailorCrew					= 180;

	refShip.SpeedRate					= 11.8;
	refShip.TurnRate					= 39.0;
	refShip.Price						= 35000;
	refShip.HP							= 2100;
	refShip.SP							= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 12;
	refShip.buildtime					= 60;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= 1.15;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 8.0;
	refship.CabinType					= "Cabin_Medium";

	refship.InertiaAccelerationX		= 5.5;	refship.InertiaBrakingX			= 5.5;
	refship.InertiaAccelerationY		= 8;	refship.InertiaBrakingY			= 8;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ			= 6.0;

	refShip.Height.Bombs.Y				= 3.5;		refShip.Height.Bombs.DY		= 1.7;
	refShip.Height.Grapes.Y				= 4.8;		refShip.Height.Grapes.DY	= 2.4;
	refShip.Height.Knippels.Y			= 16.7;		refShip.Height.Knippels.DY	= 12.8;
	refShip.Height.Balls.Y				= 3.5;		refShip.Height.Balls.DY		= 1.7;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "4.0, 6.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = false;
	refship.nation.france = false;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	/*/////////////////////////////////////////////////////////////////////////
	// Лёгкая Бригантина
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIGANTINE_L]);
	refShip.Name						= "Brigantine_l";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CULVERINE_LBS16;
	refShip.MaxCaliber					= 16;
	refShip.Weight						= Tonnes2CWT(320);
	refShip.Capacity					= 1550;

	refShip.CannonsQuantity				= 20;
	refShip.rcannon						= 8;
	refShip.lcannon						= 8;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 130;
	refShip.MinCrew						= 30;
	refShip.BoardingCrew				= 110;
	refShip.GunnerCrew					= 18;
	refShip.CannonerCrew				= 36;
	refShip.SailorCrew					= 200;
	refShip.SpeedRate					= 15.6;
	refShip.TurnRate					= 47.0;

	refShip.Price						= 36545;
	refShip.HP							= 2000;
	refShip.SP							= 100;
	refship.CabinType					= "Cabin_Medium";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 12;
	refShip.buildtime					= 60;

	refship.WindAgainstSpeed			= 9.5;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= 0.1;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;

	refship.InertiaAccelerationX		= 5.5;	refship.InertiaBrakingX			= 5.5;
	refship.InertiaAccelerationY		= 8;	refship.InertiaBrakingY			= 8;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ			= 6.0;

	refShip.Height.Bombs.Y				= 2.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y			= 13.2;		refShip.Height.Knippels.DY	= 11.6;
	refShip.Height.Balls.Y				= 2.0;		refShip.Height.Balls.DY		= 1.0;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "4.0, 6.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = false;
	refship.nation.holland = false;
	refship.nation.pirate = true;*/

	///////////////////////////////////////////////////////////////////////////
	/// Бригантина (Ориг.)
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIGANTINE]);
	refShip.Name						= "Brigantine";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CULVERINE_LBS16;
	refShip.MaxCaliber					= 16;
	refShip.Weight						= Tonnes2CWT(350);
	refShip.Capacity					= 1700;

	refShip.CannonsQuantity				= 16;
	refShip.CannonDiff					= 1;	// 16, 14
	refShip.rcannon						= 6;
	refShip.lcannon						= 6;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 155;
	refShip.MinCrew						= 28;
	refShip.BoardingCrew				= 80;
	refShip.GunnerCrew					= 16;
	refShip.CannonerCrew				= 26;
	refShip.SailorCrew					= 120;

	refShip.SpeedRate					= 14.5;
	refShip.TurnRate					= 45.0;
	refShip.Price						= 38000;
	refShip.HP							= 2400;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 12;
	refShip.buildtime					= 60;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= 0.1;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 8.9;
	refship.CabinType					= "Cabin_Medium";

	refship.InertiaAccelerationX		= 5.5;	refship.InertiaBrakingX			= 5.5;
	refship.InertiaAccelerationY		= 8;	refship.InertiaBrakingY			= 8;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ			= 6.0;

	refShip.Height.Bombs.Y				= 2.0;		refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y			= 13.2;		refShip.Height.Knippels.DY	= 11.6;
	refShip.Height.Balls.Y				= 2.0;		refShip.Height.Balls.DY		= 1.0;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "4.0, 6.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = false;
	refship.nation.france = false;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	/// Шнява
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SHNYAVA]);
	refShip.Name						= "Shnyava";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber					= 16;
	refShip.Weight						= Tonnes2CWT(350);
	refShip.Capacity					= 2150;

	refShip.CannonsQuantity				= 16;
	refShip.CannonDiff					= 1;	// 16, 14
	refShip.rcannon						= 7;
	refShip.lcannon						= 7;
	refShip.fcannon						= 2;
	refShip.bcannon						= 0;

	refShip.MaxCrew						= 165;
	refShip.MinCrew						= 30;
	refShip.BoardingCrew				= 95;
	refShip.GunnerCrew					= 20;
	refShip.CannonerCrew				= 38;
	refShip.SailorCrew					= 180;

	refShip.SpeedRate					= 13.5;
	refShip.TurnRate					= 36.5;
	refShip.Price						= 40000;
	refShip.HP							= 2400;
	refShip.SP							= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 12;
	refShip.buildtime					= 60;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= 1.15;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 6.4;
	refship.CabinType					= "Cabin_Medium";

	refship.InertiaAccelerationX		= 5.5;	refship.InertiaBrakingX			= 5.5;
	refship.InertiaAccelerationY		= 8;	refship.InertiaBrakingY			= 8;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ			= 6.0;

	refShip.Height.Bombs.Y				= 3.5;		refShip.Height.Bombs.DY		= 1.7;
	refShip.Height.Grapes.Y				= 4.8;		refShip.Height.Grapes.DY	= 2.4;
	refShip.Height.Knippels.Y			= 16.7;		refShip.Height.Knippels.DY	= 12.8;
	refShip.Height.Balls.Y				= 3.5;		refShip.Height.Balls.DY		= 1.7;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "4.0, 6.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	/// Флейт
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FLEUT]);
	refShip.Name						= "Fleut";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber					= 20;
	refShip.Weight						= Tonnes2CWT(450);
	refShip.Capacity					= 2750;

	refShip.CannonsQuantity				= 16;
	refShip.CannonDiff					= 1;	// 16, 14
	refShip.rcannon						= 6;
	refShip.lcannon						= 6;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 195;
	refShip.MinCrew						= 34;
	refShip.BoardingCrew				= 70;
	refShip.GunnerCrew					= 12;
	refShip.CannonerCrew				= 40;
	refShip.SailorCrew					= 140;

	refShip.SpeedRate					= 12.7;
	refShip.TurnRate					= 35.0;
	refShip.Price						= 43400;
	refShip.HP							= 2900;
	refShip.SP							= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 2;
	refShip.sea_enchantment				= 1.5;
	refShip.lowpolycrew					= 16;
	refShip.buildtime					= 60;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 1.2;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.8;
	refship.TurnDependWeight			= 0.25;
	refship.WindAgainstSpeed			= 4.1;
	refship.CabinType					= "Cabin_Medium";
	refship.DeckType					= "Medium";

	refship.InertiaAccelerationX		= 4.5;	refship.InertiaBrakingX			= 4.5;
	refship.InertiaAccelerationY		= 6;	refship.InertiaBrakingY			= 6;
	refship.InertiaAccelerationZ		= 4.0;	refship.InertiaBrakingZ			= 4.0;

	refShip.Height.Bombs.Y				= 3.4;		refShip.Height.Bombs.DY		= 1.7;
	refShip.Height.Grapes.Y				= 5.0;		refShip.Height.Grapes.DY	= 2.5;
	refShip.Height.Knippels.Y			= 17.8;		refShip.Height.Knippels.DY	= 13.3;
	refShip.Height.Balls.Y				= 3.4;		refShip.Height.Balls.DY		= 1.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "8.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "6.0, 8.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	/// Лёгкий Бриг
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIG_L]);
	refShip.Name						= "Brig_l";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber					= 16;
	refShip.Weight						= Tonnes2CWT(400);
	refShip.Capacity					= 1600;

	refShip.CannonsQuantity				= 16;
	refShip.CannonDiff					= 1;	// 16, 14
	refShip.rcannon						= 6;
	refShip.lcannon						= 6;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 157;
	refShip.MinCrew						= 27;
	refShip.BoardingCrew				= 90;
	refShip.GunnerCrew					= 12;
	refShip.CannonerCrew				= 32;
	refShip.SailorCrew					= 160;

	refShip.SpeedRate					= 15.2;
	refShip.TurnRate					= 49.0;
	refShip.Price						= 46500;
	refShip.HP							= 2350;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.1;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 12;
	refShip.buildtime					= 60;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= 0.1;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 6.6;
	refship.CabinType					= "Cabin_Medium";

	refship.InertiaAccelerationX		= 5.5;		refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY		= 8;		refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ		= 6.0;		refship.InertiaBrakingZ		= 6.0;

	refShip.Height.Bombs.Y				= 2.0;		refShip.Height.Bombs.DY		= 2.0;
	refShip.Height.Grapes.Y				= 3.3;		refShip.Height.Grapes.DY	= 1.6;
	refShip.Height.Knippels.Y			= 14.9;		refShip.Height.Knippels.DY	= 14.0;
	refShip.Height.Balls.Y				= 2.0;		refShip.Height.Balls.DY		= 2.0;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "4.0, 6.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = false;
	refship.nation.holland = false;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	/// Бриг
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIG]);
	refShip.Name						= "Brig";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber					= 20;
	refShip.Weight						= Tonnes2CWT(400);
	refShip.Capacity					= 1800;

	refShip.CannonsQuantity				= 16;
	refShip.CannonDiff					= 1;	// 16, 14
	refShip.rcannon						= 6;
	refShip.lcannon						= 6;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 175;
	refShip.MinCrew						= 32;
	refShip.BoardingCrew				= 90;
	refShip.GunnerCrew					= 16;
	refShip.CannonerCrew				= 32;
	refShip.SailorCrew					= 160;

	refShip.SpeedRate					= 14.0;
	refShip.TurnRate					= 45.0;
	refShip.Price						= 49000;
	refShip.HP							= 2700;
	refShip.SP							= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 3.4;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 14;
	refShip.buildtime					= 60;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= 0.1;
	refship.SpeedDependWeight			= 0.27;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 5.9;
	refship.CabinType					= "Cabin_Medium";

	refship.InertiaAccelerationX		= 5.5;		refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY		= 8;		refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ		= 6.0;		refship.InertiaBrakingZ		= 6.0;

	refShip.Height.Bombs.Y				= 2.0;		refShip.Height.Bombs.DY		= 2.0;
	refShip.Height.Grapes.Y				= 3.3;		refShip.Height.Grapes.DY	= 1.6;
	refShip.Height.Knippels.Y			= 14.9;		refShip.Height.Knippels.DY	= 14.0;
	refShip.Height.Balls.Y				= 2.0;		refShip.Height.Balls.DY		= 2.0;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "4.0, 6.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = false;
	refship.nation.france = false;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	/// Торговая Каравелла Латина
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CARAVEL]);
	refShip.Name						= "Caravel";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber					= 16;
	refShip.Weight						= Tonnes2CWT(700);
	refShip.Capacity					= 3450;

	refShip.CannonsQuantity				= 20;
	refShip.CannonDiff					= 1;	// 20, 18
	refShip.rcannon						= 8;
	refShip.lcannon						= 8;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 211;
	refShip.MinCrew						= 39;
	refShip.BoardingCrew				= 90;
	refShip.GunnerCrew					= 15;
	refShip.CannonerCrew				= 64;
	refShip.SailorCrew					= 180;

	refShip.SpeedRate					= 10.1;
	refShip.TurnRate					= 26;
	refShip.Price						= 52000;
	refShip.HP							= 2650;
	refShip.SP							= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 2;
	refShip.sea_enchantment				= 1.5;
	refShip.lowpolycrew					= 16;
	refShip.buildtime					= 40;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;
	refship.CabinType					= "Cabin_Medium";
	refship.DeckType					= "Medium";

	refship.WaterLine					= 1.0;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 5.2;

	refship.InertiaAccelerationX		= 3.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY		= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ		= 3.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.Height.Bombs.Y				= 2.7;	refShip.Height.Bombs.DY		= 1.3;
	refShip.Height.Grapes.Y				= 4.3;	refShip.Height.Grapes.DY	= 2.1;
	refShip.Height.Knippels.Y			= 13.0;	refShip.Height.Knippels.DY	= 11.7;
	refShip.Height.Balls.Y				= 2.7;	refShip.Height.Balls.DY		= 1.3;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 10;
	refship.Track1.Width				= "4.0, 5.0";
	refship.Track1.Speed				= "7.2, 9.2";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "5.0, 7.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	/// Военная Каравелла
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CARAVEL_W]);
	refShip.Name						= "Caravel_w";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber					= 16;
	refShip.Weight						= Tonnes2CWT(650);
	refShip.Capacity					= 2900;

	refShip.CannonsQuantity				= 30;
	refShip.CannonDiff					= 2;	// 30, 28, 26
	refShip.rcannon						= 13;
	refShip.lcannon						= 13;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 244;
	refShip.MinCrew						= 41;
	refShip.BoardingCrew				= 90;
	refShip.GunnerCrew					= 15;
	refShip.CannonerCrew				= 64;
	refShip.SailorCrew					= 180;

	refShip.SpeedRate					= 11.2;
	refShip.TurnRate					= 29;
	refShip.Price						= 59500;
	refShip.HP							= 2900;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2;
	refShip.sea_enchantment				= 1.5;
	refShip.lowpolycrew					= 19;
	refShip.buildtime					= 40;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;
	refship.CabinType					= "Cabin_Medium";
	refship.DeckType					= "Medium";

	refship.WaterLine					= 1.0;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 3.8;

	refship.InertiaAccelerationX		= 3.0;	refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY		= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ		= 3.0;	refship.InertiaBrakingZ		= 3.0;

	refShip.Height.Bombs.Y				= 2.7;	refShip.Height.Bombs.DY		= 1.3;
	refShip.Height.Grapes.Y				= 4.3;	refShip.Height.Grapes.DY	= 2.1;
	refShip.Height.Knippels.Y			= 13.0;	refShip.Height.Knippels.DY	= 11.7;
	refShip.Height.Balls.Y				= 2.7;	refShip.Height.Balls.DY		= 1.3;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 10;
	refship.Track1.Width				= "4.0, 5.0";
	refship.Track1.Speed				= "7.2, 9.2";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "5.0, 7.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	/// Лёгкий Галеон
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_GALEON_L]);
	refShip.Name						= "Galeon_l";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber					= 20;
	refShip.Weight						= Tonnes2CWT(800);
	refShip.Capacity					= 3100;

	refShip.CannonsQuantity				= 20;
	refShip.CannonDiff					= 1;	// 20, 18
	refShip.rcannon						= 8;
	refShip.lcannon						= 8;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 263;
	refShip.MinCrew						= 45;
	refShip.BoardingCrew				= 120;
	refShip.GunnerCrew					= 20;
	refShip.CannonerCrew				= 40;
	refShip.SailorCrew					= 240;

	refShip.SpeedRate					= 11.5;
	refShip.TurnRate					= 30.0;
	refShip.Price						= 62000;
	refShip.HP							= 3150;
	refShip.SP							= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.1;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 18;
	refShip.buildtime					= 60;

	refship.Rocking.y					= 0.45;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 0.85;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.95;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 3.2;
	refship.CabinType					= "Cabin_Medium";
	refship.DeckType					= "Medium";

	refship.InertiaAccelerationX		= 4.0;	refship.InertiaBrakingX			= 4.0;
	refship.InertiaAccelerationY		= 6;	refship.InertiaBrakingY			= 6;
	refship.InertiaAccelerationZ		= 4.0;	refship.InertiaBrakingZ			= 4.0;

	refShip.Height.Bombs.Y				= 4.3;		refShip.Height.Bombs.DY		= 2.1;
	refShip.Height.Grapes.Y				= 5.6;		refShip.Height.Grapes.DY	= 2.8;
	refShip.Height.Knippels.Y			= 18.7;		refShip.Height.Knippels.DY	= 12.7;
	refShip.Height.Balls.Y				= 4.3;		refShip.Height.Balls.DY		= 2.1;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 16.5;
	refship.Track1.Width				= "5.2, 7.3";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 10.5;
	refship.Track2.Width				= "6.0, 8.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

//	============================================================ Class 3 ===============================================================

	///////////////////////////////////////////////////////////////////////////
	/// Пинас
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_PINNACE]);
	refShip.Name						= "Pinnace";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber					= 24;
	refShip.Weight						= Tonnes2CWT(800);
	refShip.Capacity					= 3700;

	refShip.CannonsQuantity				= 18;
	refShip.CannonDiff					= 1;	// 18, 16
	refShip.rcannon						= 6;
	refShip.lcannon						= 6;
	refShip.fcannon						= 2;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 251;
	refShip.MinCrew						= 44;
	refShip.BoardingCrew				= 110;
	refShip.GunnerCrew					= 20;
	refShip.CannonerCrew				= 36;
	refShip.SailorCrew					= 220;

	refShip.SpeedRate					= 11.9;
	refShip.TurnRate					= 33.0;
	refShip.Price						= 65000;
	refShip.HP							= 3550;
	refShip.SP							= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 2.3;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew					= 16;
	refShip.buildtime					= 80;

	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 0.1;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 1.3;
	refship.TurnDependWeight			= 0.25;
	refship.WindAgainstSpeed			= 5.2;
	refship.CabinType					= "Cabin_Medium2";
	refship.DeckType					= "Medium";

	refship.InertiaAccelerationX		= 3.0;		refship.InertiaBrakingX		= 3.0;
	refship.InertiaAccelerationY		= 4;		refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ		= 3.0;		refship.InertiaBrakingZ		= 3.0;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 5.5;		refShip.Height.Grapes.DY	= 2.7;
	refShip.Height.Knippels.Y			= 24.1;		refShip.Height.Knippels.DY	= 20.7;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.5;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.85;
	refShip.GeraldSails.rey_b2.vscale	= 0.65;
	refShip.GeraldSails.rey_b3.vscale	= 0.65;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.30;
	refship.Track1.LifeTime				= 14.5;
	refship.Track1.Width				= "5.7, 7.9";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 8.5;
	refship.Track2.Width				= "10.0, 12.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = false;
	refship.nation.holland = false;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	/// Каракка
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CARACCA]);
	refShip.Name						= "Caracca";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber					= 20;
	refShip.Weight						= Tonnes2CWT(750);
	refShip.Capacity					= 4100;

	refShip.CannonsQuantity				= 20;
	refShip.CannonDiff					= 1;	// 20, 18
	refShip.rcannon						= 8;
	refShip.lcannon						= 8;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 314;
	refShip.MinCrew						= 60;
	refShip.BoardingCrew				= 120;
	refShip.GunnerCrew					= 20;
	refShip.CannonerCrew				= 40;
	refShip.SailorCrew					= 240;

	refShip.SpeedRate					= 10.2;
	refShip.TurnRate					= 28.0;
	refShip.Price						= 72000;
	refShip.HP							= 3950;
	refShip.SP							= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 18;
	refShip.buildtime					= 60;

	refship.Rocking.y					= 0.45;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 0.6;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.95;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 5.4;
	refship.CabinType					= "Cabin_Medium2";
	refship.DeckType					= "Medium";

	refship.InertiaAccelerationX		= 4.0;	refship.InertiaBrakingX			= 4.0;
	refship.InertiaAccelerationY		= 6;	refship.InertiaBrakingY			= 6;
	refship.InertiaAccelerationZ		= 4.0;	refship.InertiaBrakingZ			= 4.0;

	refShip.Height.Bombs.Y				= 4.3;		refShip.Height.Bombs.DY		= 2.1;
	refShip.Height.Grapes.Y				= 5.6;		refShip.Height.Grapes.DY	= 2.8;
	refShip.Height.Knippels.Y			= 18.7;		refShip.Height.Knippels.DY	= 12.7;
	refShip.Height.Balls.Y				= 4.3;		refShip.Height.Balls.DY		= 2.1;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 16.5;
	refship.Track1.Width				= "5.2, 7.3";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 10.5;
	refship.Track2.Width				= "6.0, 8.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = false;
	refship.nation.france = false;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	/// Лёгкий Корвет
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CORVETTE_L]);
	refShip.Name						= "Corvette_l";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS20;
	refShip.MaxCaliber					= 20;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity					= 2950;

	refShip.CannonsQuantity				= 32;
	refShip.CannonDiff					= 1;	// 20, 18
	refShip.rcannon						= 13;
	refShip.lcannon						= 13;
	refShip.fcannon						= 2;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 205;
	refShip.MinCrew						= 31;
	refShip.BoardingCrew				= 110;
	refShip.GunnerCrew					= 20;
	refShip.CannonerCrew				= 32;
	refShip.SailorCrew					= 200;

	refShip.SpeedRate					= 16.7;
	refShip.TurnRate					= 47.0;
	refShip.Price						= 77500;
	refShip.HP							= 3140;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.2;
	refShip.sea_enchantment				= 1.5;
	refShip.lowpolycrew					= 16;
	refShip.buildtime					= 80;

	refship.Rocking.y					= 0.8;
	refship.Rocking.az					= 0.025;

	refship.WaterLine					= -0.4;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed			= 6.4;
	refship.CabinType					= "Cabin_Medium2";

	refship.InertiaAccelerationX		= 8.0;		refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY		= 6;		refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ		= 6.0;		refship.InertiaBrakingZ		= 6.0;

	refShip.Height.Bombs.Y				= 1.2;		refShip.Height.Bombs.DY		= 0.6;
	refShip.Height.Grapes.Y				= 3.0;		refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 15.4;		refShip.Height.Knippels.DY	= 14.9;
	refShip.Height.Balls.Y				= 1.2;		refShip.Height.Balls.DY		= 0.6;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.17;
	refship.Track1.LifeTime				= 12.5;
	refship.Track1.Width				= "4.0, 5.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 6.5;
	refship.Track2.Width				= "5.0, 7.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = false;
	refship.nation.holland = false;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	/// Корвет
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CORVETTE]);
	refShip.Name						= "Corvette";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber					= 24;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity					= 2950;

	refShip.CannonsQuantity				= 28;
	refShip.CannonDiff					= 2;	// 28, 16, 24
	refShip.rcannon						= 12;
	refShip.lcannon						= 12;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 255;
	refShip.MinCrew						= 37;
	refShip.BoardingCrew				= 110;
	refShip.GunnerCrew					= 20;
	refShip.CannonerCrew				= 32;
	refShip.SailorCrew					= 200;
	refShip.SpeedRate					= 15.1;
	refShip.TurnRate					= 40.0;
	refShip.Price						= 85000;
	refShip.HP							= 3350;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.2;
	refShip.sea_enchantment				= 1.5;
	refShip.lowpolycrew					= 19;
	refShip.buildtime					= 80;

	refship.Rocking.y					= 0.8;
	refship.Rocking.az					= 0.025;

	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed			= 5.2;
	refship.CabinType					= "Cabin_Medium2";

	refship.InertiaAccelerationX		= 8.0;		refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY		= 6;		refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ		= 6.0;		refship.InertiaBrakingZ		= 6.0;

	refShip.Height.Bombs.Y				= 1.5;		refShip.Height.Bombs.DY = 0.9;
	refShip.Height.Grapes.Y				= 1.8;		refShip.Height.Grapes.DY = 1.0;
	refShip.Height.Knippels.Y			= 15.0;		refShip.Height.Knippels.DY = 9.0;
	refShip.Height.Balls.Y				= 1.5;		refShip.Height.Balls.DY = 0.9	;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.17;
	refship.Track1.LifeTime				= 12.5;
	refship.Track1.Width				= "4.0, 5.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 6.5;
	refship.Track2.Width				= "5.0, 7.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = false;
	refship.nation.holland = false;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	//// Полакр
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_POLACRE]);
	refShip.Name						= "Polacre";
	refship.Soundtype					= "lugger";
	refShip.Class						= 3;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber					= 24;
	refShip.Weight						= Tonnes2CWT(550);
	refShip.Capacity					= 2650;

	refShip.CannonsQuantity				= 22;
	refShip.CannonDiff					= 1;	// 22, 20
	refShip.rcannon						= 9;
	refShip.lcannon						= 9;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 227;
	refShip.MinCrew						= 40;
	refShip.BoardingCrew				= 170;
	refShip.GunnerCrew					= 30;
	refShip.CannonerCrew				= 92;
	refShip.SailorCrew					= 320;

	refShip.SpeedRate					= 14.7;
	refShip.TurnRate					= 41.0;
	refShip.Price						= 80000;
	refShip.HP							= 3250;
	refShip.SP							= 100;

	refship.CabinType					= "Cabin_Medium2";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 15;
	refShip.buildtime					= 60;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 8.3;

	refship.InertiaAccelerationX		= 5.5;		refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY		= 8;		refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ		= 6.0;		refship.InertiaBrakingZ		= 6.0;

	refShip.Height.Bombs.Y				= 1.7;		refShip.Height.Bombs.DY		= 0.8;
	refShip.Height.Grapes.Y				= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y			= 10.1;		refShip.Height.Knippels.DY	= 9.2;
	refShip.Height.Balls.Y				= 1.7;		refShip.Height.Balls.DY		= 0.8;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "4.0, 6.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = false;
	refship.nation.france = false;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	/// Галеон
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_GALEON]);
	refShip.Name						= "Galeon";
	refship.Soundtype					= "frigate";
	refShip.Class						= 3;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber					= 24;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity					= 4150;

	refShip.CannonsQuantity				= 36;
	refShip.CannonDiff					= 2;	// 36, 34, 32
	refShip.rcannon						= 15;
	refShip.lcannon						= 15;
	refShip.fcannon						= 2;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 290;
	refShip.MinCrew						= 57;
	refShip.BoardingCrew				= 200;
	refShip.GunnerCrew					= 36;
	refShip.CannonerCrew				= 72;
	refShip.SailorCrew					= 400;

	refShip.SpeedRate					= 10.8;
	refShip.TurnRate					= 30.0;
	refShip.Price						= 97000;
	refShip.HP							= 4350;
	refShip.SP							= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 22;
	refShip.buildtime					= 80;

	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.02;

	refship.WaterLine					= -0.2;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 3.5;
	refship.CabinType					= "Cabin";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY		= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ		= 4.5;	refship.InertiaBrakingZ		= 4.5;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.4;		refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.4;		refShip.Height.Knippels.DY	= 19.8;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.5;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.98;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.0;
	refship.Track1.LifeTime				= 14.5;
	refship.Track1.Width				= "5.2, 7.3";
	refship.Track1.Speed				= "5.5, 6.5";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 8.5;
	refship.Track2.Width				= "6.0, 8.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = false;
	refship.nation.france = false;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

//	============================================================ Class 2 ===============================================================


	///////////////////////////////////////////////////////////////////////////
	/// Ост-Индец
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_EASTINDIAMAN]);
	refShip.Name						= "EastIndiaMan";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon						= CANNON_TYPE_CULVERINE_LBS24;
	refShip.MaxCaliber					= 24;
	refShip.Weight						= Tonnes2CWT(1100);
	refShip.Capacity					= 5600;

	refShip.CannonsQuantity				= 34;
	refShip.CannonDiff					= 2;	// 36, 34, 32
	refShip.rcannon						= 15;
	refShip.lcannon						= 15;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 335;
	refShip.MinCrew						= 53;
	refShip.BoardingCrew				= 200;
	refShip.GunnerCrew					= 36;
	refShip.CannonerCrew				= 72;
	refShip.SailorCrew					= 400;

	refShip.SpeedRate					= 13.4;
	refShip.TurnRate					= 31.0;
	refShip.Price						= 115000;
	refShip.HP							= 4800;
	refShip.SP							= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= false;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 22;
	refShip.buildtime					= 80;

	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.02;

	refship.WaterLine					= 0.6;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 4.4;
	refship.CabinType					= "Cabin";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY		= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ		= 4.5;	refship.InertiaBrakingZ		= 4.5;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 5.1;		refShip.Height.Grapes.DY	= 1.6;
	refShip.Height.Knippels.Y			= 19.5;		refShip.Height.Knippels.DY	= 14.1;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.4;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.98;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.0;
	refship.Track1.LifeTime				= 14.5;
	refship.Track1.Width				= "5.2, 7.3";
	refship.Track1.Speed				= "5.5, 6.5";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 8.5;
	refship.Track2.Width				= "6.0, 8.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = false;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	/// Тяжёлый Галеон
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_GALEON_H]);
	refShip.Name						= "Galeon_h";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS32;
	refShip.MaxCaliber					= 32;
	refShip.Weight						= Tonnes2CWT(1050);
	refShip.Capacity					= 5150;

	refShip.CannonsQuantity				= 54;
	refShip.CannonDiff					= 3;	// 54, 52, 50, 48
	refShip.rcannon						= 22;
	refShip.lcannon						= 22;
	refShip.fcannon						= 4;
	refShip.bcannon						= 6;

	refShip.MaxCrew						= 435;
	refShip.MinCrew						= 66;
	refShip.BoardingCrew				= 200;
	refShip.GunnerCrew					= 36;
	refShip.CannonerCrew				= 72;
	refShip.SailorCrew					= 400;

	refShip.SpeedRate					= 9.6;
	refShip.TurnRate					= 27.0;
	refShip.Price						= 125000;
	refShip.HP							= 5650;
	refShip.SP							= 100;
	refship.Type.Merchant				= true;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 26;
	refShip.buildtime					= 80;

	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.02;

	refship.WaterLine					= -0.2;

	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.3;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 3.6;
	refship.CabinType					= "Cabin";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 4.5;	refship.InertiaBrakingX		= 4.5;
	refship.InertiaAccelerationY		= 3;	refship.InertiaBrakingY		= 3;
	refship.InertiaAccelerationZ		= 4.5;	refship.InertiaBrakingZ		= 4.5;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.4;		refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.4;		refShip.Height.Knippels.DY	= 19.8;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 1.5;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.98;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.0;
	refship.Track1.LifeTime				= 14.5;
	refship.Track1.Width				= "5.2, 7.3";
	refship.Track1.Speed				= "5.5, 6.5";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 8.5;
	refship.Track2.Width				= "6.0, 8.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = false;
	refship.nation.france = false;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	/// Фрегат
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATE]);
	refShip.Name						= "Frigate";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber					= 24;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity					= 3500;

	refShip.CannonsQuantity				= 46;
	refShip.CannonDiff					= 2;	// 46, 44, 42
	refShip.rcannon						= 20;
	refShip.lcannon						= 20;
	refShip.fcannon						= 2;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 345;
	refShip.MinCrew						= 51;
	refShip.BoardingCrew				= 150;
	refShip.GunnerCrew					= 30;
	refShip.CannonerCrew				= 92;
	refShip.SailorCrew					= 300;

	refShip.SpeedRate					= 14.65;
	refShip.TurnRate					= 40.0;
	refShip.Price						= 138000;
	refShip.HP							= 4650;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 24;
	refShip.buildtime					= 100;


	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 0.33;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 5.4;
	refship.CabinType					= "Cabin_Big";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY		= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ		= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y				= 3.7;	refShip.Height.Bombs.DY		= 1.8;
	refShip.Height.Grapes.Y				= 5.2;	refShip.Height.Grapes.DY	= 2.6;
	refShip.Height.Knippels.Y			= 24.0;	refShip.Height.Knippels.DY	= 19.7;
	refShip.Height.Balls.Y				= 3.7;	refShip.Height.Balls.DY		= 1.8;

	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.9;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 14.5;
	refship.Track1.Width				= "3.7, 3.9";
	refship.Track1.Speed				= "7.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 8.5;
	refship.Track2.Width				= "8.0, 9.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = false;
	refship.nation.holland = false;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	/// Тяжёлый Фрегат
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATE_H]);
	refShip.Name						= "Frigate_h";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS32;
	refShip.MaxCaliber					= 32;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity					= 4000;

	refShip.CannonsQuantity				= 52;
	refShip.CannonDiff					= 3;	// 52, 50, 48, 46
	refShip.rcannon						= 21;
	refShip.lcannon						= 21;
	refShip.fcannon						= 4;
	refShip.bcannon						= 6;

	refShip.MaxCrew						= 395;
	refShip.MinCrew						= 59;
	refShip.BoardingCrew				= 150;
	refShip.GunnerCrew					= 30;
	refShip.CannonerCrew				= 92;
	refShip.SailorCrew					= 300;

	refShip.SpeedRate					= 13.3;
	refShip.TurnRate					= 35.0;
	refShip.Price						= 155000;
	refShip.HP							= 5450;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 26;
	refShip.buildtime					= 100;


	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 4.8;
	refship.CabinType					= "Cabin_Big";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 5.0;	 refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY		= 4;	 refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ		= 5.0;	 refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y				= 2.7;	 refShip.Height.Bombs.DY		= 1.35;
	refShip.Height.Grapes.Y				= 5.325; refShip.Height.Grapes.DY		= 1.575;
	refShip.Height.Knippels.Y			= 19.5;	 refShip.Height.Knippels.DY		= 13.5;
	refShip.Height.Balls.Y				= 2.7;	 refShip.Height.Balls.DY		= 1.35;

	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.9;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 14.5;
	refship.Track1.Width				= "3.7, 3.9";
	refship.Track1.Speed				= "7.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 8.5;
	refship.Track2.Width				= "8.0, 9.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refShip.isNationalHull				= false;
	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

//	============================================================ Class 1 ===============================================================

	///////////////////////////////////////////////////////////////////////////
	/// Военный корабль
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LINESHIP]);
	refShip.Name						= "Lineship"; //несоответствие
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS32;
	refShip.MaxCaliber					= 32;
	refShip.Weight						= Tonnes2CWT(2500);
	refShip.Capacity					= 4850;

	refShip.CannonsQuantity				= 56;
	refShip.CannonDiff					= 3;	// 56, 54, 52, 50
	refShip.rcannon						= 25;
	refShip.lcannon						= 25;
	refShip.fcannon						= 2;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 465;
	refShip.MinCrew						= 60;
	refShip.BoardingCrew				= 210;
	refShip.GunnerCrew					= 30;
	refShip.CannonerCrew				= 112;
	refShip.SailorCrew					= 420;

	refShip.SpeedRate					= 12.0;
	refShip.TurnRate					= 29.0;
	refShip.Price						= 195000;
	refShip.HP							= 6100;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew					= 28;
	refShip.buildtime					= 120;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 1.05;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.15;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed			= 2.8;
	refship.CabinType					= "Cabin";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 4.5;		refship.InertiaBrakingX			= 4.0;
	refship.InertiaAccelerationY		= 3.5;		refship.InertiaBrakingY			= 3;
	refship.InertiaAccelerationZ		= 4.5;		refship.InertiaBrakingZ			= 4.0;

	refShip.Height.Bombs.Y				= 6.7;		refShip.Height.Bombs.DY		= 3.3;
	refShip.Height.Grapes.Y				= 8.3;		refShip.Height.Grapes.DY	= 4.1;
	refShip.Height.Knippels.Y			= 32.1;		refShip.Height.Knippels.DY	= 25.8;
	refShip.Height.Balls.Y				= 6.7;		refShip.Height.Balls.DY		= 3.3;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.8;
	refShip.GeraldSails.rey_b2.vscale	= 0.6;
	refShip.GeraldSails.rey_b3.vscale	= 0.6;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.15;
	refship.Track1.LifeTime				= 16.5;
	refship.Track1.Width				= "3.0, 4.0";
	refship.Track1.Speed				= "8.0, 8.0";

	refship.Track2.ZStart				= -0.25;
	refship.Track2.LifeTime				= 10.5;
	refship.Track2.Width				= "6.0, 7.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refShip.isNationalHull = true;
	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	/// Линейный Корабль
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_WARSHIP]);
	refShip.Name						= "Warship"; //несоответствие
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS36;
	refShip.MaxCaliber					= 36;
	refShip.Weight						= Tonnes2CWT(2500);
	refShip.Capacity					= 5450;

	refShip.CannonsQuantity				= 68;
	refShip.CannonDiff					= 3;	// 68, 66, 64, 62
	refShip.rcannon						= 32;
	refShip.lcannon						= 32;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 555;
	refShip.MinCrew						= 80;
	refShip.BoardingCrew				= 250;
	refShip.GunnerCrew					= 50;
	refShip.CannonerCrew				= 136;
	refShip.SailorCrew					= 500;

	refShip.SpeedRate					= 11.3;
	refShip.TurnRate					= 24;
	refShip.Price						= 265000;
	refShip.HP							= 6900;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew					= 29;
	refShip.buildtime					= 120;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.55;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 2.2;
	refship.CabinType					= "Cabin";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 4.0;	refship.InertiaBrakingX			= 3.5;
	refship.InertiaAccelerationY		= 3.0;		refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ		= 4.0;	refship.InertiaBrakingZ			= 3.5;

	refShip.Height.Bombs.Y				= 3.0;		refShip.Height.Bombs.DY		= 3.0;
	refShip.Height.Grapes.Y				= 4.0;		refShip.Height.Grapes.DY	= 2.0;
	refShip.Height.Knippels.Y			= 23.0;		refShip.Height.Knippels.DY	= 22.0;
	refShip.Height.Balls.Y				= 3.0;		refShip.Height.Balls.DY		= 3.0;

	/*refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.8;
	refShip.GeraldSails.rey_b2.vscale	= 0.65;
	refShip.GeraldSails.rey_b3.vscale	= 0.55;*/

	refShip.GeraldSails.rey_b2	= 1;
	refShip.GeraldSails.rey_b3	= 1;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.25;
	refship.Track1.LifeTime				= 9.5;
	refship.Track1.Width				= "7.0, 7.5";
	refship.Track1.Speed				= "8.0, 9.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "8.0, 10.0";
	refship.Track2.Speed				= "1.0, 2.0";

	refShip.isNationalHull = true;
	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	/// Боевой Корабль
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BATTLESHIP]);
	refShip.Name						= "Battleship";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS36;
	refShip.MaxCaliber					= 36;
	refShip.Weight						= Tonnes2CWT(2500);
	refShip.Capacity					= 6000;

	refShip.CannonsQuantity				= 78;
	refShip.CannonDiff					= 3;	// 78, 76, 74, 72
	refShip.rcannon						= 37;
	refShip.lcannon						= 37;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 650;
	refShip.MinCrew						= 115;
	refShip.BoardingCrew				= 300;
	refShip.GunnerCrew					= 50;
	refShip.CannonerCrew				= 160;
	refShip.SailorCrew					= 600;

	refShip.SpeedRate					= 9.8;
	refShip.TurnRate					= 19.0;
	refShip.Price						= 380000;
	refShip.HP							= 7800;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew					= 31;
	refShip.buildtime					= 130;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= -0.1;
	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 1.8;
	refship.CabinType					= "Cabin";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 3.5;	refship.InertiaBrakingX			= 3.0;
	refship.InertiaAccelerationY		= 2.5;	refship.InertiaBrakingY			= 2.5;
	refship.InertiaAccelerationZ		= 3.5;	refship.InertiaBrakingZ			= 3.0;

	refShip.Height.Bombs.Y				= 4.0;		refShip.Height.Bombs.DY		= 3.0;
	refShip.Height.Grapes.Y				= 5.0;		refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 27.0;		refShip.Height.Knippels.DY	= 27.0;
	refShip.Height.Balls.Y				= 4.0;		refShip.Height.Balls.DY		= 3.0;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.8;
	refShip.GeraldSails.rey_b2.vscale	= 0.65;
	refShip.GeraldSails.rey_b3.vscale	= 0.55;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.25;
	refship.Track1.LifeTime				= 9.5;
	refship.Track1.Width				= "7.0, 7.5";
	refship.Track1.Speed				= "8.0, 9.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "8.0, 10.0";
	refship.Track2.Speed				= "1.0, 2.0";

	refShip.isNationalHull = true;
	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

	///////////////////////////////////////////////////////////////////////////
	/// Мановар
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_MANOWAR]);
	refShip.Name						= "Manowar";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS42;
	refShip.MaxCaliber					= 42;
	refShip.Weight						= Tonnes2CWT(4000);
	refShip.Capacity					= 6600;

	refShip.CannonsQuantity				= 106;
	refShip.CannonDiff					= 3;	// 106, 104, 102, 100
	refShip.rcannon						= 51;
	refShip.lcannon						= 51;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 830;
	refShip.MinCrew						= 170;
	refShip.BoardingCrew				= 400;
	refShip.GunnerCrew					= 80;
	refShip.CannonerCrew				= 204;
	refShip.SailorCrew					= 800;

	refShip.SpeedRate					= 8.7;
	refShip.TurnRate					= 13.5;
	refShip.Price						= 570000;
	refShip.HP							= 10000;
	refShip.SP							= 100;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew					= 35;
	refShip.buildtime					= 140;

	refship.Rocking.y					= 0.3;
	refship.Rocking.az					= 0.02	;

	refship.WaterLine					= 0.3;
	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 1.8;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 1.1;
	refship.CabinType					= "Cabin_Huge";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 1.5;		refship.InertiaBrakingX		= 1.5;
	refship.InertiaAccelerationY		= 1.5;		refship.InertiaBrakingY		= 1.5;
	refship.InertiaAccelerationZ		= 1.5;		refship.InertiaBrakingZ		= 1.5;

	refShip.Height.Bombs.Y				= 8.6;		refShip.Height.Bombs.DY		= 4.3;
	refShip.Height.Grapes.Y				= 12.5;		refShip.Height.Grapes.DY	= 6.2;
	refShip.Height.Knippels.Y			= 36.8;		refShip.Height.Knippels.DY	= 29.6;
	refShip.Height.Balls.Y				= 8.6;		refShip.Height.Balls.DY		= 4.3;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_c1			= 1;
	refShip.GeraldSails.rey_c1.vscale	= 0.98;
	refShip.GeraldSails.rey_b2.vscale	= 0.98;
	refShip.GeraldSails.rey_b3.vscale	= 0.98;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.30;
	refship.Track1.LifeTime				= 18.5;
	refship.Track1.Width				= "6.5, 7.5";
	refship.Track1.Speed				= "8.0, 9.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 10.5;
	refship.Track2.Width				= "16.0, 18.0";
	refship.Track2.Speed				= "0.15, 0.25";

	refShip.isNationalHull = true;
	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = false;

//	============================================================ Quest ships ===============================================================

	///////////////////////////////////////////////////////////////////////////
	/// Солей Руаяль Королевский Мановар
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SOLEYRU]);
	refShip.Name						= "SoleyRu";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS42;
	refShip.MaxCaliber					= 42;
	refShip.Weight						= Tonnes2CWT(4500);
	refShip.Capacity					= 8000;

	refShip.CannonsQuantity				= 112;
	refShip.rcannon						= 52;
	refShip.lcannon						= 52;
	refShip.fcannon						= 4;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 1000;
	refShip.MinCrew						= 170;
	refShip.BoardingCrew				= 500;
	refShip.GunnerCrew					= 80;
	refShip.CannonerCrew				= 204;
	refShip.SailorCrew					= 800;

	refShip.SpeedRate					= 10.0;
	refShip.TurnRate					= 20.0;
	refShip.Price						= 750000;
	refShip.HP							= 14000;
	refShip.SP							= 100;

	refship.EmblemedSails.normalTex		= "ships\parus_SoleyRu.tga";
	refship.CanEncounter				= false;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew					= 37;
	refShip.buildtime					= 140;

	refship.Rocking.y					= 0.3;
	refship.Rocking.az					= 0.02;

	refship.WaterLine					= 0.4;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.8;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 2.2;
	refship.CabinType					= "Cabin_Huge";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 2.0;	refship.InertiaBrakingX			= 2.0;
	refship.InertiaAccelerationY		= 2;	refship.InertiaBrakingY			= 2;
	refship.InertiaAccelerationZ		= 2.0;	refship.InertiaBrakingZ			= 2.0;

	refShip.Height.Bombs.Y				= 8.6;		refShip.Height.Bombs.DY		= 4.3;
	refShip.Height.Grapes.Y				= 12.5;		refShip.Height.Grapes.DY	= 6.2;
	refShip.Height.Knippels.Y			= 36.8;		refShip.Height.Knippels.DY	= 29.6;
	refShip.Height.Balls.Y				= 8.6;		refShip.Height.Balls.DY		= 4.3;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_c1			= 1;
	refShip.GeraldSails.rey_c1.vscale	= 0.98;
	refShip.GeraldSails.rey_b2.vscale	= 0.98;
	refShip.GeraldSails.rey_b3.vscale	= 0.98;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.30;
	refship.Track1.LifeTime				= 18.5;
	refship.Track1.Width				= "6.5, 7.5";
	refship.Track1.Speed				= "8.0, 9.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 10.5;
	refship.Track2.Width				= "16.0, 18.0";
	refship.Track2.Speed				= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	/// Быстрый мановар Мортиферо
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_SANTISIMA]);
	refShip.Name						= "Santisima";
	refship.Soundtype					= "manowar";
	refShip.Class						= 1;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS42;
	refShip.MaxCaliber					= 42;
	refShip.Weight						= Tonnes2CWT(1250);
	refShip.Capacity					= 7000;

	refShip.CannonsQuantity				= 108;
	refShip.rcannon						= 51;
	refShip.lcannon						= 51;
	refShip.fcannon						= 2;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 900;
	refShip.MinCrew						= 150;
	refShip.BoardingCrew				= 500;
	refShip.GunnerCrew					= 80;
	refShip.CannonerCrew				= 204;
	refShip.SailorCrew					= 800;

	refShip.SpeedRate					= 12.0;
	refShip.TurnRate					= 25.0;
	refShip.Price						= 680000;
	refShip.HP							= 12000;
	refShip.SP							= 100;

	refship.EmblemedSails.normalTex		= "ships\parus_silk.tga";
	refship.CanEncounter				= false;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.0;
	refShip.lowpolycrew					= 33;
	refShip.buildtime					= 140;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.9;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 2.6;
	refship.CabinType					= "Cabin_Huge";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 2.0;		refship.InertiaBrakingX		= 2.0;
	refship.InertiaAccelerationY		= 2;		refship.InertiaBrakingY		= 2;
	refship.InertiaAccelerationZ		= 2.0;		refship.InertiaBrakingZ		= 2.0;

	refShip.Height.Bombs.Y				= 4.0;		refShip.Height.Bombs.DY		= 3.3;
	refShip.Height.Grapes.Y				= 4.5;		refShip.Height.Grapes.DY	= 3.2;
	refShip.Height.Knippels.Y			= 26.8;		refShip.Height.Knippels.DY	= 23.6;
	refShip.Height.Balls.Y				= 4.0;		refShip.Height.Balls.DY		= 3.3;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_c1			= 1;
	refShip.GeraldSails.rey_c1.vscale	= 0.9;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.9;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.30;
	refship.Track1.LifeTime				= 18.5;
	refship.Track1.Width				= "6.5, 7.5";
	refship.Track1.Speed				= "8.0, 9.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 10.5;
	refship.Track2.Width				= "16.0, 18.0";
	refship.Track2.Speed				= "0.15, 0.25";

	//////////////////////////////////////////////////////////////////////////
	// Бригантина Стрела
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIGQEEN]);
	refShip.Name						= "BrigQeen";
	refship.Soundtype					= "corvette";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CULVERINE_LBS24;
	refShip.MaxCaliber					= 24;
	refShip.Weight						= Tonnes2CWT(320);
	refShip.Capacity					= 2000;

	refShip.CannonsQuantity				= 24;
	refShip.rcannon						= 10;
	refShip.lcannon						= 10;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 205;
	refShip.MinCrew						= 27;
	refShip.BoardingCrew				= 110;
	refShip.GunnerCrew					= 18;
	refShip.CannonerCrew				= 36;
	refShip.SailorCrew					= 200;

	refShip.SpeedRate					= 18.88;
	refShip.TurnRate					= 57.0;
	refShip.Price						= 168886;
	refShip.HP							= 3000;
	refShip.SP							= 100;

	refship.CabinType					= "Cabin_Medium6";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 15;
	refShip.buildtime					= 60;

	refship.WindAgainstSpeed			= 9.1;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= -0.5;
	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.34;

	refship.InertiaAccelerationX		= 5.5;		refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY		= 8;		refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ		= 6.0;		refship.InertiaBrakingZ		= 6.0;

	refShip.Height.Bombs.Y				= 1.0;		refShip.Height.Bombs.DY		= 0.5;
	refShip.Height.Grapes.Y				= 2.0;		refShip.Height.Grapes.DY	= 1.0;
	refShip.Height.Knippels.Y			= 10.0;		refShip.Height.Knippels.DY	= 8.0;
	refShip.Height.Balls.Y				= 1.0;		refShip.Height.Balls.DY		= 0.5;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 14.5;
	refship.Track1.Width				= "3.7, 3.9";
	refship.Track1.Speed				= "7.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 8.5;
	refship.Track2.Width				= "8.0, 9.0";
	refship.Track2.Speed				= "0.15, 0.25";

	//////////////////////////////////////////////////////////////////////////
	// Бриг Морской Волк
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_BRIGSW]);
	refShip.Name						= "BrigSW";
	refship.Soundtype					= "lugger";
	refShip.Class						= 4;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber					= 24;
	refShip.Weight						= Tonnes2CWT(400);
	refShip.Capacity					= 2250;

	refShip.CannonsQuantity				= 24;
	refShip.rcannon						= 10;
	refShip.lcannon						= 10;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 236;
	refShip.MinCrew						= 32;
	refShip.BoardingCrew				= 100;
	refShip.GunnerCrew					= 18;
	refShip.CannonerCrew				= 36;
	refShip.SailorCrew					= 190;

	refShip.SpeedRate					= 17.3;
	refShip.TurnRate					= 51.0;
	refShip.Price						= 177777;
	refShip.HP							= 3250;
	refShip.SP							= 100;

	refship.CabinType					= "Cabin_Medium6";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 15;
	refShip.buildtime					= 60;

	refship.WindAgainstSpeed			= 7.40;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= -0.80;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;

	refship.InertiaAccelerationX		= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY		= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y				= 1.5;			refShip.Height.Bombs.DY	= 0.7;
	refShip.Height.Grapes.Y				= 2.8;			refShip.Height.Grapes.DY	= 1.4;
	refShip.Height.Knippels.Y			= 16.9;		refShip.Height.Knippels.DY	= 15.4;
	refShip.Height.Balls.Y				= 1.5;		refShip.Height.Balls.DY	= 0.7;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "4.0, 6.0";
	refship.Track2.Speed				= "0.15, 0.25";

	//////////////////////////////////////////////////////////////////////////
	// Щебека Синяя Птица
	//////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_XebekVML]);
	refShip.Name						= "XebekVML";
	refship.Soundtype					= "lugger";
	refShip.Class						= 5;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS16;
	refShip.MaxCaliber					= 16;
	refShip.Weight						= Tonnes2CWT(380);
	refShip.Capacity					= 1650;

	refShip.CannonsQuantity				= 22;
	refShip.rcannon						= 9;
	refShip.lcannon						= 9;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 175;
	refShip.MinCrew						= 25;
	refShip.BoardingCrew				= 130;
	refShip.GunnerCrew					= 20;
	refShip.CannonerCrew				= 38;
	refShip.SailorCrew					= 220;

	refShip.SpeedRate					= 18.0;
	refShip.TurnRate					= 60.0;
	refShip.Price						= 150500;
	refShip.HP							= 2550;
	refShip.SP							= 100;

	refship.CabinType					= "Cabin_Medium";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 10;
	refShip.buildtime					= 60;

	refship.WindAgainstSpeed			= 11.7;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= 0.20;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;

	refship.InertiaAccelerationX		= 5.5;	refship.InertiaBrakingX	= 5.5;
	refship.InertiaAccelerationY		= 8;	refship.InertiaBrakingY	= 8;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ	= 6.0;

	refShip.Height.Bombs.Y				= 1.7;			refShip.Height.Bombs.DY	= 0.8;
	refShip.Height.Grapes.Y				= 3.4;			refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y			= 10.1;		refShip.Height.Knippels.DY	= 9.2;
	refShip.Height.Balls.Y				= 1.7;		refShip.Height.Balls.DY	= 0.8;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "4.0, 6.0";
	refship.Track2.Speed				= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	/// Корвет Пёс Войны
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CORVETTE_QUEST]);
	refShip.Name						= "Corvette_quest";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber					= 24;
	refShip.Weight						= Tonnes2CWT(680);
	refShip.Capacity					= 2700;

	refShip.CannonsQuantity				= 40;
	refShip.rcannon						= 16;
	refShip.lcannon						= 16;
	refShip.fcannon						= 4;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 285;
	refShip.MinCrew						= 15;
	refShip.BoardingCrew				= 170;
	refShip.GunnerCrew					= 30;
	refShip.CannonerCrew				= 92;
	refShip.SailorCrew					= 320;

	refShip.SpeedRate					= 17.5;
	refShip.TurnRate					= 54.0;
	refShip.Price						= 250000;
	refShip.HP							= 4000;
	refShip.SP							= 100;

	refship.CabinType					= "Cabin_Quest";
	refship.EmblemedSails.normalTex		= "ships\parus_pesgovna.tga";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 2.2;
	refShip.sea_enchantment				= 1.5;
	refShip.lowpolycrew					= 19;
	refShip.buildtime					= 80;

	refship.Rocking.y					= 0.8;
	refship.Rocking.az					= 0.025;

	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed			= 5.7;

	refship.InertiaAccelerationX		= 8.0;	refship.InertiaBrakingX			= 8.0;
	refship.InertiaAccelerationY		= 6;	refship.InertiaBrakingY			= 6;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ			= 6.0;

	refShip.Height.Bombs.Y				= 1.3;		refShip.Height.Bombs.DY		= 0.6;
	refShip.Height.Grapes.Y				= 3.1;		refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 14.7;		refShip.Height.Knippels.DY	= 15.0;
	refShip.Height.Balls.Y				= 1.3;		refShip.Height.Balls.DY		= 0.6;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.17;
	refship.Track1.LifeTime				= 12.5;
	refship.Track1.Width				= "4.0, 5.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 6.5;
	refship.Track2.Width				= "5.0, 7.0";
	refship.Track2.Speed				= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	/// Легендарный Корвет Пёс Войны
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_CORVETTE_QUEST_O]);
	refShip.Name						= "Corvette_quest_o";
	refship.Soundtype					= "corvette";
	refShip.Class						= 3;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS32;
	refShip.MaxCaliber					= 32;
	refShip.Weight						= Tonnes2CWT(680);
	refShip.Capacity					= 3350;
	refShip.CannonsQuantity				= 40;
	refShip.rcannon						= 16;
	refShip.lcannon						= 16;
	refShip.fcannon						= 4;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 345;
	refShip.MinCrew						= 30;
	refShip.BoardingCrew				= 170;
	refShip.GunnerCrew					= 30;
	refShip.CannonerCrew				= 92;
	refShip.SailorCrew					= 320;

	refShip.SpeedRate					= 19.0;
	refShip.TurnRate					= 60.0;
	refShip.Price						= 500000;
	refShip.HP							= 5000;
	refShip.SP							= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 2.2;
	refShip.sea_enchantment				= 1.5;
	refShip.lowpolycrew					= 20;
	refShip.buildtime					= 80;

	refship.Rocking.y					= 0.8;
	refship.Rocking.az					= 0.025;

	refship.WaterLine					= -0.50;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.7;
	refship.TurnDependWeight			= 0.35;
	refship.WindAgainstSpeed			= 7.7;
	refship.CabinType					= "Cabin_Quest";

	refship.InertiaAccelerationX		= 8.0;	refship.InertiaBrakingX			= 8.0;
	refship.InertiaAccelerationY		= 6;	refship.InertiaBrakingY			= 6;
	refship.InertiaAccelerationZ		= 6.0;	refship.InertiaBrakingZ			= 6.0;

	refShip.Height.Bombs.Y				= 1.3;		refShip.Height.Bombs.DY		= 0.6;
	refShip.Height.Grapes.Y				= 3.1;		refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 14.7;		refShip.Height.Knippels.DY	= 15.0;
	refShip.Height.Balls.Y				= 1.3;		refShip.Height.Balls.DY		= 0.6;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.17;
	refship.Track1.LifeTime				= 12.5;
	refship.Track1.Width				= "4.0, 5.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 6.5;
	refship.Track2.Width				= "5.0, 7.0";
	refship.Track2.Speed				= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	/// Фрегат Арабелла - Синко Льягас
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_ARABELLA]);
	refShip.Name						= "ArabellaShip";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS36;
	refShip.MaxCaliber					= 36;
	refShip.Weight						= Tonnes2CWT(1050);
	refShip.Capacity					= 3750;

	refShip.CannonsQuantity				= 52;
	refShip.rcannon						= 22;
	refShip.lcannon						= 22;
	refShip.fcannon						= 4;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 425;
	refShip.MinCrew						= 38;
	refShip.BoardingCrew				= 240;
	refShip.GunnerCrew					= 40;
	refShip.CannonerCrew				= 92;
	refShip.SailorCrew					= 400;

	refShip.SpeedRate					= 17.3;
	refShip.TurnRate					= 42.0;
	refShip.Price						= 450000;
	refShip.HP							= 6240;
	refShip.SP							= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 22;
	refShip.buildtime					= 100;

	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.035;
	refship.WaterLine					= -0.6;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 5.5;
	refship.CabinType					= "Cabin_Quest";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY		= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ		= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y				= 3.1;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.2;	refShip.Height.Knippels.DY	= 18.3;
	refShip.Height.Balls.Y				= 3.1;	refShip.Height.Balls.DY		= 1.5;

	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.9;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 14.5;
	refship.Track1.Width				= "3.7, 3.9";
	refship.Track1.Speed				= "7.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 8.5;
	refship.Track2.Width				= "8.0, 9.0";
	refship.Track2.Speed				= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	/// Фрегат Арабелла - Синко Льягас Легендарная
	///////////////////////////////////////////////////////////////////////////
	/*makeref(refShip,ShipsTypes[SHIP_ARABELLA_O]);
	refShip.Name						= "ArabellaShip_o";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS36;
	refShip.MaxCaliber					= 36;
	refShip.Weight						= Tonnes2CWT(1050);
	refShip.Capacity					= 4000;

	refShip.CannonsQuantity				= 52;
	refShip.rcannon						= 22;
	refShip.lcannon						= 22;
	refShip.fcannon						= 4;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 455;
	refShip.MinCrew						= 38;
	refShip.BoardingCrew				= 240;
	refShip.GunnerCrew					= 40;
	refShip.CannonerCrew				= 92;
	refShip.SailorCrew					= 400;

	refShip.SpeedRate					= 18.3;
	refShip.TurnRate					= 42.0;
	refShip.Price						= 650000;
	refShip.HP							= 6540;
	refShip.SP							= 100;

	refship.EmblemedSails.normalTex		= "ships\sail_Arabella.tga";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 22;
	refShip.buildtime					= 100;

	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.035;
	refship.WaterLine					= -0.6;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 6.1;
	refship.CabinType					= "Cabin_Quest";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY		= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ		= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y				= 3.1;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.2;	refShip.Height.Knippels.DY	= 18.3;
	refShip.Height.Balls.Y				= 3.1;	refShip.Height.Balls.DY		= 1.5;

	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.9;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 14.5;
	refship.Track1.Width				= "3.7, 3.9";
	refship.Track1.Speed				= "7.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 8.5;
	refship.Track2.Width				= "8.0, 9.0";
	refship.Track2.Speed				= "0.15, 0.25";*/

	///////////////////////////////////////////////////////////////////////////
	/// Королева
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATEQUEEN]);
	refShip.Name						= "FrigateQueen";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon						= CANNON_TYPE_CULVERINE_LBS32;
	refShip.MaxCaliber					= 32;
	refShip.Weight						= Tonnes2CWT(950);
	refShip.Capacity					= 3550;

	refShip.CannonsQuantity				= 48;
	refShip.rcannon						= 20;
	refShip.lcannon						= 20;
	refShip.fcannon						= 4;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 385;
	refShip.MinCrew						= 40;
	refShip.BoardingCrew				= 240;
	refShip.GunnerCrew					= 40;
	refShip.CannonerCrew				= 92;
	refShip.SailorCrew					= 400;

	refShip.SpeedRate					= 18.0;
	refShip.TurnRate					= 51.0;
	refShip.Price						= 350000;
	refShip.HP							= 6000;
	refShip.SP							= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 21;
	refShip.buildtime					= 100;

	refship.Rocking.y					= 0.4;
	refship.Rocking.az					= 0.035;
	refship.WaterLine					= -0.6;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 7.2;
	refship.CabinType					= "Cabin_Quest";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY		= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ		= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y				= 3.1;	refShip.Height.Bombs.DY		= 1.5;
	refShip.Height.Grapes.Y				= 4.5;	refShip.Height.Grapes.DY	= 2.2;
	refShip.Height.Knippels.Y			= 21.2;	refShip.Height.Knippels.DY	= 18.3;
	refShip.Height.Balls.Y				= 3.1;	refShip.Height.Balls.DY		= 1.5;

	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.9;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 14.5;
	refship.Track1.Width				= "3.7, 3.9";
	refship.Track1.Speed				= "7.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 8.5;
	refship.Track2.Width				= "8.0, 9.0";
	refship.Track2.Speed				= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	/// Корабль Призрак
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FLYINGDUTCHMAN]);
	refShip.Name						= "Flyingdutchman";	 // ЛГ
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS36;
	refShip.MaxCaliber					= 36;
	refShip.Weight						= Tonnes2CWT(1800);
	refShip.Capacity					= 5300;

	refShip.CannonsQuantity				= 60;
	refShip.rcannon						= 24;
	refShip.lcannon						= 24;
	refShip.fcannon						= 4;
	refShip.bcannon						= 8;

	refShip.MaxCrew						= 500;
	refShip.MinCrew						= 66;
	refShip.BoardingCrew				= 250;
	refShip.GunnerCrew					= 50;
	refShip.CannonerCrew				= 136;
	refShip.SailorCrew					= 500;

	refShip.SpeedRate					= 15.2;
	refShip.TurnRate					= 40.0;
	refShip.Price						= 666666;
	refShip.HP							= 6999;
	refShip.SP							= 100;

	refship.EmblemedSails.normalTex		= "ships\parus_common_torn.tga";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew					= 28;
	refShip.buildtime					= 120;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed			= 4.5;
	refship.CabinType					= "CabineFDM";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 4.0;	refship.InertiaBrakingX		= 3.5;
	refship.InertiaAccelerationY		= 3.0;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ		= 4.0;	refship.InertiaBrakingZ		= 3.5;

	refShip.Height.Bombs.Y				= 6.4;		refShip.Height.Bombs.DY		= 3.2;
	refShip.Height.Grapes.Y				= 8.5;		refShip.Height.Grapes.DY	= 4.2;
	refShip.Height.Knippels.Y			= 27.4;		refShip.Height.Knippels.DY	= 23.4;
	refShip.Height.Balls.Y				= 6.4;		refShip.Height.Balls.DY		= 3.2;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.8;
	refShip.GeraldSails.rey_b2.vscale	= 0.65;
	refShip.GeraldSails.rey_b3.vscale	= 0.55;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.25;
	refship.Track1.LifeTime				= 9.5;
	refship.Track1.Width				= "7.0, 7.5";
	refship.Track1.Speed				= "8.0, 9.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "8.0, 10.0";
	refship.Track2.Speed				= "1.0, 2.0";

	///////////////////////////////////////////////////////////////////////////
	/// Легендарный Варшип
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FLYINGDUTCHMAN_O]);
	refShip.Name						= "Flyingdutchman_o";  // Очищенный ЛГ
	refship.Soundtype					= "lineship";
	refShip.Class						= 1;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS42;
	refShip.MaxCaliber					= 42;
	refShip.Weight						= Tonnes2CWT(1800);
	refShip.Capacity					= 6100;

	refShip.CannonsQuantity				= 62;
	refShip.rcannon						= 25;
	refShip.lcannon						= 25;
	refShip.fcannon						= 4;
	refShip.bcannon						= 8;

	refShip.MaxCrew						= 600;
	refShip.MinCrew						= 66;
	refShip.BoardingCrew				= 250;
	refShip.GunnerCrew					= 50;
	refShip.CannonerCrew				= 136;
	refShip.SailorCrew					= 500;

	refShip.SpeedRate					= 16.5;
	refShip.TurnRate					= 45.0;
	refShip.Price						= 777777;
	refShip.HP							= 8000;
	refShip.SP							= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 1.0;
	refShip.sea_enchantment				= 1.1;
	refShip.lowpolycrew					= 30;
	refShip.buildtime					= 120;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= 0.0;

	refship.SpeedDependWeight			= 0.35;
	refship.SubSeaDependWeight			= 1.0;
	refship.TurnDependWeight			= 0.4;
	refship.WindAgainstSpeed			= 5.0;
	refship.CabinType					= "Cabin_Huge"; //Алексус сделает красиво Konstrush
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 4.0;	refship.InertiaBrakingX		= 3.5;
	refship.InertiaAccelerationY		= 3.0;	refship.InertiaBrakingY		= 2.5;
	refship.InertiaAccelerationZ		= 4.0;	refship.InertiaBrakingZ		= 3.5;

	refShip.Height.Bombs.Y				= 6.4;		refShip.Height.Bombs.DY		= 3.2;
	refShip.Height.Grapes.Y				= 8.5;		refShip.Height.Grapes.DY	= 4.2;
	refShip.Height.Knippels.Y			= 27.4;		refShip.Height.Knippels.DY	= 23.4;
	refShip.Height.Balls.Y				= 6.4;		refShip.Height.Balls.DY		= 3.2;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.8;
	refShip.GeraldSails.rey_b2.vscale	= 0.65;
	refShip.GeraldSails.rey_b3.vscale	= 0.55;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.25;
	refship.Track1.LifeTime				= 9.5;
	refship.Track1.Width				= "7.0, 7.5";
	refship.Track1.Speed				= "8.0, 9.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "8.0, 10.0";
	refship.Track2.Speed				= "1.0, 2.0";

	///////////////////////////////////////////////////////////////////////////
	//// Тяжёлый Люггер
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_LUGGERQUEST]);
	refShip.Name						= "LuggerQuest";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS8;
	refShip.MaxCaliber					= 8;
	refShip.Weight						= Tonnes2CWT(145);
	refShip.Capacity					= 650;

	refShip.CannonsQuantity				= 12;
	refShip.CannonDiff					= 1;	// 12, 10
	refShip.rcannon						= 4;
	refShip.lcannon						= 4;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 56;
	refShip.MinCrew						= 11;
	refShip.BoardingCrew				= 70;
	refShip.GunnerCrew					= 12;
	refShip.CannonerCrew				= 48;
	refShip.SailorCrew					= 120;
	refShip.SpeedRate					= 13.7;
	refShip.TurnRate					= 51.0;
	refShip.Price						= 16500;
	refShip.HP							= 850;
	refShip.SP							= 100;

	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refShip.fWindAgainstSpeed			= 6.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew					= 5;
	refShip.buildtime					= 20;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;

	refship.CabinType					= "Cabin_Small2";

	refship.WaterLine					= -0.01;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 11.0;

	refship.InertiaAccelerationX		= 10.0;	refship.InertiaBrakingX		= 10.0;
	refship.InertiaAccelerationY		= 10;	refship.InertiaBrakingY		= 10;
	refship.InertiaAccelerationZ		= 10.0;	refship.InertiaBrakingZ		= 10.0;

	refShip.Height.Bombs.Y				= 1.5;	refShip.Height.Bombs.DY		= 0.7;
	refShip.Height.Grapes.Y				= 2.7;	refShip.Height.Grapes.DY	= 1.3;
	refShip.Height.Knippels.Y			= 13.4;	refShip.Height.Knippels.DY	= 9.7;
	refShip.Height.Balls.Y				= 1.5;	refShip.Height.Balls.DY		= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 9;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "8.0, 10.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7;
	refship.Track2.Width				= "3.0, 4.5";
	refship.Track2.Speed				= "0.15, 0.25";

	refship.nation.england = true;
	refship.nation.france = true;
	refship.nation.spain = true;
	refship.nation.holland = true;
	refship.nation.pirate = true;

	///////////////////////////////////////////////////////////////////////////
	//// Призрак Тени - тяжёлый полакр
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_POLACRE_QUEST]);
	refShip.Name						= "Polacre_q";
	refship.Soundtype					= "lugger";
	refShip.Class						= 3;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS24;
	refShip.MaxCaliber					= 32;
	refShip.Weight						= Tonnes2CWT(600);
	refShip.Capacity					= 3350;

	refShip.CannonsQuantity				= 24;
	refShip.rcannon						= 10;
	refShip.lcannon						= 10;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 265;
	refShip.MinCrew						= 37;
	refShip.BoardingCrew				= 170;
	refShip.GunnerCrew					= 30;
	refShip.CannonerCrew				= 92;
	refShip.SailorCrew					= 320;

	refShip.SpeedRate					= 16.7;
	refShip.TurnRate					= 56.0;
	refShip.Price						= 240000;
	refShip.HP							= 4255;
	refShip.SP							= 100;

	refship.CabinType					= "Cabin_Medium6";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refship.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.8;
	refShip.lowpolycrew					= 17;
	refShip.buildtime					= 60;

	refship.WindAgainstSpeed			= 10.0;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.04;

	refship.WaterLine					= 0.0;
	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.6;
	refship.TurnDependWeight			= 0.3;

	refship.InertiaAccelerationX		= 5.5;		refship.InertiaBrakingX		= 5.5;
	refship.InertiaAccelerationY		= 8;		refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ		= 6.0;		refship.InertiaBrakingZ		= 6.0;

	refShip.Height.Bombs.Y				= 1.7;		refShip.Height.Bombs.DY		= 0.8;
	refShip.Height.Grapes.Y				= 3.4;		refShip.Height.Grapes.DY	= 1.7;
	refShip.Height.Knippels.Y			= 10.1;		refShip.Height.Knippels.DY	= 9.2;
	refShip.Height.Balls.Y				= 1.7;		refShip.Height.Balls.DY		= 0.8;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.8;
	refShip.GeraldSails.rey_b3.vscale	= 0.8;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 12;
	refship.Track1.Width				= "2.0, 3.0";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 7.5;
	refship.Track2.Width				= "4.0, 6.0";
	refship.Track2.Speed				= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	//// Быстрый Шлюп Veinard
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_VEINARD]);
	refShip.Name						= "veinard";
	refship.Soundtype					= "lugger";
	refShip.Class						= 6;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS12;
	refShip.MaxCaliber					= 12;
	refShip.Weight						= Tonnes2CWT(180);
	refShip.Capacity					= 1200;

	refShip.CannonsQuantity				= 18;
	refShip.rcannon						= 7;
	refShip.lcannon						= 7;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 125;
	refShip.MinCrew						= 18;
	refShip.BoardingCrew				= 40;
	refShip.GunnerCrew					= 5;
	refShip.CannonerCrew				= 32;
	refShip.SailorCrew					= 80;

	refShip.SpeedRate					= 16.0;
	refShip.TurnRate					= 50.0;
	refShip.Price						= 35000;
	refShip.HP							= 1750;
	refShip.SP							= 100;

	refship.CabinType					= "Cabin_Small2";
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refship.fWindAgainstSpeed			= 7.0;
	refShip.sea_enchantment				= 2.0;
	refShip.lowpolycrew					= 9;
	refShip.buildtime					= 20;
	refship.WindAgainstSpeed			= 7.5;

	refship.Rocking.y					= 0.45;
	refship.Rocking.az					= 0.02;

	refship.WaterLine					= -0.78;
	refship.SpeedDependWeight			= 0.2;
	refship.SubSeaDependWeight			= 1.1;
	refship.TurnDependWeight			= 0.3;

	refShip.Height.Bombs.Y				= 2.0;	refShip.Height.Bombs.DY		= 1.0;
	refShip.Height.Grapes.Y				= 3.8;	refShip.Height.Grapes.DY	= 1.9;
	refShip.Height.Knippels.Y			= 15.2;	refShip.Height.Knippels.DY	= 13.9;
	refShip.Height.Balls.Y				= 2.0;	refShip.Height.Balls.DY		= 1.0;

	refship.InertiaAccelerationX		= 8.0;	refship.InertiaBrakingX		= 8.0;
	refship.InertiaAccelerationY		= 8;	refship.InertiaBrakingY		= 8;
	refship.InertiaAccelerationZ		= 8.0;	refship.InertiaBrakingZ		= 8.0;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 9;
	refship.Track1.Width				= "2.0, 2.5";
	refship.Track1.Speed				= "5.2, 6.2";

	refship.Track2.ZStart				= -0.05;
	refship.Track2.LifeTime				= 7;
	refship.Track2.Width				= "3.0, 4.0";
	refship.Track2.Speed				= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	/// Фрегат Моргана - Оксфорд
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FRIGATE_M]);
	refShip.Name						= "Frigate_M";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS42;
	refShip.MaxCaliber					= 42;
	refShip.Weight						= Tonnes2CWT(860);
	refShip.Capacity					= 4200;

	refShip.CannonsQuantity				= 60;
	refShip.CannonDiff					= 0;
	refShip.rcannon						= 26;
	refShip.lcannon						= 26;
	refShip.fcannon						= 4;
	refShip.bcannon						= 4;

	refShip.MaxCrew						= 455;
	refShip.MinCrew						= 60;

	refShip.SpeedRate					= 16.35;
	refShip.TurnRate					= 39.0;
	refShip.Price						= 425000;
	refShip.HP							= 6550;
	refShip.SP							= 100;

	refship.CanEncounter				= false;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 25;
	refShip.buildtime					= 100;

	refship.Rocking.y					= 0.5;
	refship.Rocking.az					= 0.035;

	refship.WaterLine					= -0.6;

	refship.SpeedDependWeight			= 0.3;
	refship.SubSeaDependWeight			= 0.9;
	refship.TurnDependWeight			= 0.3;
	refship.WindAgainstSpeed			= 5.2;
	refship.CabinType					= "Cabin";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 5.0;	refship.InertiaBrakingX		= 5.0;
	refship.InertiaAccelerationY		= 4;	refship.InertiaBrakingY		= 4;
	refship.InertiaAccelerationZ		= 5.0;	refship.InertiaBrakingZ		= 5.0;

	refShip.Height.Bombs.Y				= 2.4;	refShip.Height.Bombs.DY		= 2.3;
	refShip.Height.Grapes.Y				= 3.0;	refShip.Height.Grapes.DY	= 1.5;
	refShip.Height.Knippels.Y			= 16.0;	refShip.Height.Knippels.DY	= 15.1;
	refShip.Height.Balls.Y				= 2.4;	refShip.Height.Balls.DY		= 2.3;

	refShip.GeraldSails.rey_b1			= 1;
	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b1.vscale	= 0.9;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.25;
	refship.Track1.LifeTime				= 16.5;
	refship.Track1.Width				= "6.0, 8.2";
	refship.Track1.Speed				= "9.0, 9.0";

	refship.Track2.ZStart				= 0.0;
	refship.Track2.LifeTime				= 13.5;
	refship.Track2.Width				= "8.0, 9.0";
	refship.Track2.Speed				= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	/// Санта-Маргарита - Военный Галеон Армады
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_MARGARITA]);
	refShip.Name						= "Margarita";
	refship.Soundtype					= "frigate";
	refShip.Class						= 2;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS36;
	refShip.MaxCaliber					= 36;
	refShip.Weight						= Tonnes2CWT(1000);
	refShip.Capacity					= 6900;

	refShip.CannonsQuantity				= 38;
	refShip.CannonDiff					= 0;
	refShip.rcannon						= 17;
	refShip.lcannon						= 17;
	refShip.fcannon						= 2;
	refShip.bcannon						= 2;

	refShip.MaxCrew						= 479;
	refShip.MinCrew						= 90;

	refShip.SpeedRate					= 14.79;
	refShip.TurnRate					= 30.0;
	refShip.Price						= 250000;
	refShip.HP							= 7900;
	refShip.SP							= 100;

	refship.CanEncounter				= false;
	refship.Type.Merchant				= false;
	refship.Type.War					= true;
	refship.QuestShip					= true;

	refShip.fWindAgainstSpeed			= 2.0;
	refShip.sea_enchantment				= 1.2;
	refShip.lowpolycrew					= 16;

	refship.Rocking.y					= 0.45;
	refship.Rocking.az					= 0.035;
	refship.WaterLine					= 0.5;
	refship.SpeedDependWeight			= 0.15;
	refship.SubSeaDependWeight			= 0.95;
	refship.TurnDependWeight			= 0.2;
	refship.WindAgainstSpeed			= 3.6;
	refship.CabinType					= "Cabin_Huge";
	refship.DeckType					= "Big";

	refship.InertiaAccelerationX		= 4.0;	refship.InertiaBrakingX		= 4.0;
	refship.InertiaAccelerationY		= 6;	refship.InertiaBrakingY		= 6;
	refship.InertiaAccelerationZ		= 4.0;	refship.InertiaBrakingZ		= 4.0;

	refShip.Height.Bombs.Y				= 4.3;	refShip.Height.Bombs.DY		= 2.1;
	refShip.Height.Grapes.Y				= 5.6;	refShip.Height.Grapes.DY	= 2.8;
	refShip.Height.Knippels.Y			= 18.7;	refShip.Height.Knippels.DY	= 12.7;
	refShip.Height.Balls.Y				= 4.3;	refShip.Height.Balls.DY		= 2.1;

	refShip.GeraldSails.rey_b2			= 1;
	refShip.GeraldSails.rey_b3			= 1;
	refShip.GeraldSails.rey_b2.vscale	= 0.7;
	refShip.GeraldSails.rey_b3.vscale	= 0.7;

	refship.Track.Enable				= true;
	refship.Track1.ZStart				= 0.20;
	refship.Track1.LifeTime				= 16.5;
	refship.Track1.Width				= "5.2, 7.3";
	refship.Track1.Speed				= "6.0, 8.0";

	refship.Track2.ZStart				= -0.15;
	refship.Track2.LifeTime				= 10.5;
	refship.Track2.Width				= "6.0, 8.0";
	refship.Track2.Speed				= "0.15, 0.25";

	///////////////////////////////////////////////////////////////////////////
	/// FORT
	///////////////////////////////////////////////////////////////////////////
	makeref(refShip,ShipsTypes[SHIP_FORT]);
	refShip.Name						= "Fort";
	refShip.isFort						= true; // для удобства проверок на rRealShip
	refShip.Class						= 1;
	refShip.Cannon						= CANNON_TYPE_CANNON_LBS32;
	refShip.MaxCaliber					= 48;
	refShip.Weight						= Tonnes2CWT(22500);
	refShip.Capacity					= 300000;
	refShip.CannonsQuantity				= 68;
	refShip.rcannon						= 68;
	refShip.lcannon						= 0;
	refShip.fcannon						= 0;
	refShip.bcannon						= 0;
	refShip.MaxCrew						= 1800;
	refShip.OptCrew						= 1600;
	refShip.MinCrew						= 400;
	refShip.BoardingCrew				= 800;
	refShip.GunnerCrew					= 800;
	refShip.CannonerCrew				= 800;
	refShip.SailorCrew					= 0;
	refShip.SpeedRate					= 0.0;
	refShip.TurnRate					= 0;
	refShip.Price						= 12000;
	refShip.HP							= 54000;
	refShip.SP							= 100;
	refShip.buildtime					= 240;
	refShip.CanEncounter				= false;

	for (i = 0; i < SHIP_TYPES_QUANTITY; i++)
	{
		makeref(refShip, ShipsTypes[i]);

		if (!CheckAttribute(refShip, "Name"))
		{
			trace("ERROR InitShips(): Ship " + i + " doesn't have 'Name' attribute");
			continue;
		}

		if (!CheckAttribute(refShip, "TurnRate"))
			trace("ERROR InitShips(): Ship " + i + " doesn't have 'TurnRate' attribute");

		if (!CheckAttribute(refShip, "SpeedRate"))
			trace("ERROR InitShips(): Ship " + i + " doesn't have 'SpeedRate' attribute");

		if (!CheckAttribute(refShip, "Class"))
			trace("ERROR InitShips(): Ship " + i + " doesn't have 'Class' attribute");
		else
		{
			idx = sti(refShip.Class);
			if (idx < 1) idx = 1;
			if (idx > 7) idx = 7;
			refShip.Class = idx;
		}

		refShip.HullsAmount = GetShipHulls(refShip.name + "1"); // > подсчёт кол-ва вариантов окраса корпуса у корабля
		refship.InertiaAccelerationY = stf(refship.InertiaAccelerationY) / 6.0;
		// boal 10/11/05 пробить оптимальный экипаж
		refShip.OptCrew = sti(refShip.MaxCrew);
		refShip.MaxCrew = makeint(sti(refShip.MaxCrew) * 1.25 + 0.5); // перегруз
		/// как говаривал мой папа - нахрена попу гармонь?	Приходится приводить к каноническому виду, править все буковки по файлу мне лень
		refShip.cannonr	 = refShip.rcannon;
		refShip.cannonl	 = refShip.lcannon;
		refShip.cannonf	 = refShip.fcannon;
		refShip.cannonb	 = refShip.bcannon;
	}
}

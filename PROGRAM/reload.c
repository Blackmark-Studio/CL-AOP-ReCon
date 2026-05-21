
#define RELOAD_TIME_FADE_OUT	0.5
#define RELOAD_TIME_FADE_IN		0.5

object reload_fader;
aref reload_locator_ref;
int reload_cur_island_index, reload_cur_location_index;
int reload_island_index, reload_location_index;

object reload_xaddress;

bool LoadMainCharacterInFirstLocation(string location_id, string emerge_locator, string ship_location)
{
	int lindex, i;
	//Find ship location
	if(ship_location != "")
	{
		lindex = FindLocation(ship_location);
		if(lindex < 0)
		{
			Trace("Incorrect location id for location character's ship location " + ship_location + " not found");
		}
	}
	if(lindex >= 0)
	{
		SetPlayerShipLocation(lindex);
	}
	//Find location
	lindex = FindLocation(location_id);
	if(lindex < 0)
	{
		Trace("Incorrect location id for first location location " + location_id + " not found");
		return false;
	}
	//Trace("!!! Reload to " + lindex);
	//Find reload data
	aref reload_group;
	aref locator_ref;
	makearef(reload_group, Locations[lindex].reload);
	
	int num = GetAttributesNum(reload_group);
	if(num == 0)
	{
		Trace("Location " + location_id + " not have reload groups!");
		return false;
	}
	if(emerge_locator != "")
	{
		for(i = 0; i < num; i++)
		{
            locator_ref = GetAttributeN(reload_group, i);
			if(emerge_locator == locator_ref.name) break;
		}
		if(i == num)
		{
			Trace("Emerge locator " + emerge_locator + " in location " + location_id + " not found!");
			locator_ref = GetAttributeN(reload_group, 0);
			emerge_locator = locator_ref.name;
			Trace("Character emerge on first locator (" + emerge_locator + ")");
		}
	}else{
		locator_ref = GetAttributeN(reload_group, 0);
		emerge_locator = locator_ref.name;
	}
    //  Eddy -->
	if (HasSubStr(emerge_locator, "_back"))
	{
        emerge_locator = strcut(emerge_locator, 0, strlen(emerge_locator)-6);
	}
    // <--  Eddy
	lockedReloadLocator = emerge_locator;
	pchar.location = Locations[lindex].id;
	pchar.location.group = "reload";
	pchar.location.locator = emerge_locator;
	if(IsEntity(&chrAnimationKipper) == false) CreateEntity(&chrAnimationKipper, "CharacterAnimationKipper");
	ReloadProgressUpdate();
	LoadLocation(&Locations[lindex]);
	//Fader
	PostEvent("LoadSceneSound", 100);
	return true;
}

// boal 03.10.06 блок предыстории
bool LoadMainCharacterInFirstLocationGroup(string location_id, string sGroup, string emerge_locator)
{
	int lindex;
	
	//Find location
	lindex = FindLocation(location_id);
	if(lindex < 0)
	{
		Trace("Incorrect location id for first location location " + location_id + " not found");
		return false;
	}

	lockedReloadLocator = emerge_locator;
	pchar.location         = location_id;
	pchar.location.group   = sGroup;
	pchar.location.locator = emerge_locator;
	if(IsEntity(&chrAnimationKipper) == false) CreateEntity(&chrAnimationKipper, "CharacterAnimationKipper");
	ReloadProgressUpdate();
	LoadLocation(&Locations[lindex]);
	//Fader
	PostEvent("LoadSceneSound", 100);
	return true;
}

void SetPlayerShipLocation(int location_index)
{
	//Main character
	if(location_index < 0)
	{
		Trace("SetPlayerShipLocation - incorrect location index");
		return;
	}
	pchar.location.from_sea = Locations[location_index].id;
}


//reload_group = xxx.reload
int Reload(aref reload_group, string locator_name, string current_location)
{		
	SetTimeScale(1.0); // Фикс ломающегося фейдера при смене локации на ускоренном времени 
	//EmptySelectedTutorials();
	SetReloadNextTipsImage();
	dialogDisable = true;
	reload_xaddress.active = "false";
	//Trace("locator_name = " + locator_name + " lockedReloadLocator = " + lockedReloadLocator);
	//Check locked locator
	if(locator_name == lockedReloadLocator)
	{
		lockedReloadLocator = "";
		return -1;
	}
	//Find reload data
	int i;
	int num = GetAttributesNum(reload_group);
	if(num == 0) return 0;
	for(i = 0; i < num; i++)
	{
		reload_locator_ref = GetAttributeN(reload_group, i);
		if(locator_name == reload_locator_ref.name) break;
	}
	if(i == num)
	{
		Trace("Can't reload...");
		Trace("Reload locator '" + locator_name + "' in currend location not found!");
		return 0;
	}
	//Check main attributes
	if(CheckAttribute(reload_locator_ref, "name") == 0)
	{
		Trace("Can't reload...");
		Trace("Reload: attribute 'name' in " + GetAttributeName(reload_locator_ref) + " not accessible");
		return 0;
	}
	if(CheckAttribute(reload_locator_ref, "go") == 0)
	{
		Trace("Can't reload...");
		Trace("Reload: attribute 'go' in " + GetAttributeName(reload_locator_ref) + " not accessible");
		return 0;
	}
	if(CheckAttribute(reload_locator_ref, "emerge") == 0)
	{
		Trace("Can't reload...");
		Trace("Reload: attribute 'emerge' in " + GetAttributeName(reload_locator_ref) + " not accessible");
		return 0;
	}
	//Find current location
	reload_cur_island_index = -1;
	reload_cur_location_index = -1;
	if(current_location != "")
	{		
		reload_cur_island_index = FindIsland(current_location);
		if(reload_cur_island_index < 0)
		{
			reload_cur_location_index = FindLocation(current_location);
			if(reload_cur_location_index < 0)
			{
				Trace("Can't unload currend location...");
				Trace("Current location not found: id = " + current_location);
			}
		}
	}
	//Find location & reload
	reload_island_index = -1;
	reload_location_index = -1;
	reload_island_index = FindIsland(reload_locator_ref.go);
	if(reload_island_index < 0)
	{
		reload_location_index = FindLocation(reload_locator_ref.go);
		if(reload_location_index < 0)
		{
			Trace("Can't reload...");
			Trace("Location not found: id = " + reload_locator_ref.go);
			return 0;
		}
	}

	//Trace("reload_cur_island_index = " + reload_cur_island_index);
	//Trace("reload_cur_location_index = " + reload_cur_location_index);
	//Trace("reload_island_index = " + reload_island_index);
	//Trace("reload_location_index = " + reload_location_index);
	//Test in sea exit

	if((reload_cur_island_index < 0) && (reload_island_index >= 0))
	{
		if(reload_cur_location_index >= 0)
		{
			//From location to sea
			if(Locations[reload_cur_location_index].id != pchar.location.from_sea)
			{
				Trace("Not reload to sea, no ships: cur:" + Locations[reload_cur_location_index].id + " from:" + pchar.location.from_sea);
				return -1;
			}
		}
	}
	
	//Start fader
	SetEventHandler("FaderEvent_StartFade", "ReloadStartFade", 0);
	SetEventHandler("FaderEvent_EndFade", "ReloadEndFade", 0);
	CreateEntity(&reload_fader, "fader");
	if(reload_island_index >= 0)
	{
		//SendMessage(&reload_fader, "ls", FADER_PICTURE0, "interfaces\card_desk.tga");
		if(!CheckAttribute(pchar, "todeck"))
		{
			SendMessage(&reload_fader, "ls",FADER_PICTURE0,"loading\Standsea_" + rand(3) + ".tga");
		}
		else
		{
			SendMessage(&reload_fader, "ls",FADER_PICTURE,"loading\cabine.tga");
		}
	}
	else
	{
		int loc_pict_index = reload_location_index;
		if(loc_pict_index < 0) loc_pict_index = reload_cur_location_index;
		if(loc_pict_index >= 0)
		{		
			if(CheckAttribute(&Locations[loc_pict_index],"image"))
			{
				//SendMessage(&reload_fader, "ls", FADER_PICTURE0, "interfaces\card_desk.tga");
				if (CheckAttribute(&TEV, "FD_Reload") && TEV.FD_Reload == "afterFDsink")
				{
					SendMessage(&reload_fader, "ls",FADER_PICTURE0,"loading\rescue.tga");
					DeleteAttribute(&TEV, "FD_Reload");
				}
				else
				{
					SendMessage(&reload_fader, "ls", FADER_PICTURE0, GetRandomLoadingPic(Locations[loc_pict_index].image));
				}
				//	SendMessage(&reload_fader, "ls", FADER_PICTURE0, Locations[loc_pict_index].image);
			}
		}
	}

	bool IsMakeShot = true;
	float fadeOutTime = RELOAD_TIME_FADE_OUT;
	if((reload_cur_island_index < 0) && (reload_cur_location_index < 0))
	{
		fadeOutTime = 0.00001;	//Can't need fade out - no loaded location
		IsMakeShot = false;
	}
	SendMessage(&reload_fader, "lfl", FADER_OUT, fadeOutTime, false);
	if(IsMakeShot == true) SendMessage(&reload_fader, "l", FADER_STARTFRAME);
	//Set lockedReloadLocator
	if(reload_cur_island_index < 0)
	{
		//From location
		if(reload_island_index < 0)
		{		//To location
			lockedReloadLocator = reload_locator_ref.emerge;
		}
		else
		{	//To sea
			lockedReloadLocator = "";
		}
	}
	else
	{
		//From sea
		if(reload_island_index < 0)
		{		//To location
			lockedReloadLocator = reload_locator_ref.emerge;
		}
		else
		{	//To sea			
			lockedReloadLocator = "";
		}
	}
	//Trace("Start reload");
	return 1;
}

void ReloadStartFade()
{
	bool bResetSound = true; // > в локах одинакового типа звук можно не сбрасывать
	DeleteAttribute(&TEV, "Music.KeepPlaying");

	if (HasAttrValue(&InterfaceStates, "ContinuousMusic", "1"))
	{
		if (CheckAttribute(&TEV, "Music.ForceKeepPlaying"))
			TEV.Music.KeepPlaying = "";
		else
		{
			bool bOk = LAi_grp_alarmactive && !LAi_boarding_process && !CheckAttribute(pchar, "GenQuestFort.StartAttack");

			// KZ > идея непрерывной музыки реквизирована из ЧМ для КС от Cheatsurfer
			if (!bOk && reload_location_index >= 0 && reload_cur_location_index >= 0)
			{
				ref rLocIn = &locations[reload_location_index];
				ref rLocOut = &locations[reload_cur_location_index];

				if (CheckAttribute(&TEV, "Music.CurrentTrack") && CheckAttributeEx(rLocOut, "type,id.label", "&") && CheckAttributeEx(rLocIn, "type,id.label", "&"))
				{
					if (bSeaActive)
					{
						if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Ship", "1") && rLocIn.type == rLocOut.type && !HasStr(rLocOut.id.label, "Boarding deck"))
						{
							bResetSound = false;
							TEV.Music.KeepPlaying = "";	// > на корабле
						}
					}
					else
					{
						if (reload_cur_location_index == reload_location_index)
						{
							if (or(CheckAttribute(rLocOut, "lockWeather") && rLocOut.lockWeather == "Inside", CheckAttribute(rLocOut, "QuestlockWeather") && rLocOut.QuestlockWeather == "23 Hour"))
							{
								bResetSound = false;
								TEV.Music.KeepPlaying = "";	// > перезагрузка локации
							}
						}
						else if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Jungle", "1") && rLocOut.type == "jungle")
						{
							if (rLocIn.type == rLocOut.type && !HasStrEx(rLocIn.id.label, "Graveyard,Village", "|") && !HasStrEx(rLocOut.id.label, "Graveyard,Village", "|"))
							{
								bResetSound = false;
								TEV.Music.KeepPlaying = "";	// > джунгли
							}
						}
						else if (StrStartsWith(rLocOut.id.label, "Tavern") && StrStartsWith(rLocIn.id.label, "Tavern"))
							TEV.Music.KeepPlaying = "";		// > таверна и комната отдыха // TODO KZ > добавить комнатам при тавернах амбиент приглушённых звуков из зала
						else if (or(rLocOut.id.label == "Store" && !HasStrEx(rLocIn.id.label, "portoffice,tavern", "|"), rLocIn.id.label == "Store" && !HasStrEx(rLocOut.id.label, "portoffice,tavern", "|")))
						{
							if (or(rLocOut.type == "Shop" && rLocIn.type == "House" && !CheckAttribute(rLocIn, "brothel") && !HasStr(rLocOut.id.label, "Brothel"), rLocOut.type == "House" && rLocIn.type == "Shop") && !CheckAttribute(rLocOut, "brothel") && !HasStr(rLocIn.id.label, "Brothel"))
								TEV.Music.KeepPlaying = "";	// > магазин, склад магазина
						}
						else if (rLocOut.id.label == "portoffice" && rLocIn.id.label == "portoffice")
						{
							bResetSound = false;
							TEV.Music.KeepPlaying = "";		// > портовое управление Санто-Доминго
						}
						else if (HasAttrValue(&InterfaceStates, "ContinuousMusic.House", "1") && HasStrEx(rLocOut.type, "Ascold,house", "|") && HasStrEx(rLocIn.type, "Ascold,house", "|") && !HasStrEx(rLocIn.id, "PortOffice,brothel,Brothel_room,SecBrRoom", "|") && !HasStrEx(rLocOut.id, "PortOffice,brothel,Brothel_room,SecBrRoom", "|"))
						{
							bResetSound = false;
							TEV.Music.KeepPlaying = "";		// > дома и комнаты в них
						}
						else if (rLocOut.type == "residence" && rLocIn.type == "residence")
						{
							bResetSound = false;
							TEV.Music.KeepPlaying = "";		// > резиденция Виллемстада
						}
						else if (StrStartsWith(rLocOut.id.label, "Packhouse") && StrStartsWith(rLocIn.id.label, "Packhouse"))
							TEV.Music.KeepPlaying = "";		// > пакгаус, офис пакгауса
						else if (HasStr(rLocOut.id, "_Bank") && HasStr(rLocIn.id, "_Bank"))
						{
							bResetSound = false;
							TEV.Music.KeepPlaying = "";		// > банк, хранилище банка
						}
						else if (HasAttrValue(&InterfaceStates, "ContinuousMusic.Brothel", "1") && HasStrEx(rLocOut.id, "brothel,Brothel_room,SecBrRoom", "|") && HasStrEx(rLocIn.id, "brothel,Brothel_room,SecBrRoom", "|"))
							TEV.Music.KeepPlaying = "";		// > бордель
						else if (HasAttrValue(&InterfaceStates, "ContinuousMusic.LSC", "1") && HasStrEx(rLocOut.type, "LostShipsCity,LSC_inside", "|") && !HasStr(rLocIn.type, "underwater") && !HasStr(rLocOut.type, "underwater"))
							TEV.Music.KeepPlaying = "";		// > улица и помещения ГПК
						else if (or(rLocOut.id == "Secret_Fort", rLocIn.id == "Secret_Fort") && or(rLocOut.id == "Secret_Fort_ammo", rLocIn.id == "Secret_Fort_ammo"))
							TEV.Music.KeepPlaying = "";		// > форт в джунглях и старый арсенал
					}
				}
			}
		}
	}

	//if (bResetSound) // KZ > TODO > галочку в опции
		ResetSound();

	DelEventHandler("FaderEvent_StartFade", "ReloadStartFade");
	//Trace("ReloadStartFade");
	if(reload_cur_island_index < 0)
	{
		//From location
		if(reload_island_index < 0)
		{
			//To location
			if(reload_cur_location_index >= 0) UnloadLocation(&Locations[reload_cur_location_index]);
			return;
		}else{
			//To sea
			if(reload_cur_location_index >= 0)
			{
				UnloadLocation(&Locations[reload_cur_location_index]);
			}else pchar.location.from_sea = "";			
			DeleteClass(&chrAnimationKipper);
			return;
		}
	}else{
		//From sea
		if(reload_island_index < 0)
		{
			//To location
			DeleteSeaEnvironment();
			pchar.location.from_sea = reload_locator_ref.go;
		}else{
			//To sea
			DeleteSeaEnvironment();
			pchar.location.from_sea = "";
		}
		Partition_SetValue("after");// Дележ добычи уход на сушу
	}
}

void ReloadEndFade()
{
    EmptyAllFantomCharacter(); // fix место тут!!!! а не выше, вот вам и баги по квестам, блин boal
    PGG_DailyUpdate();
    Siege_DailyUpdate();//homo осады 05/11/06
	dialogDisable = false;
	ReloadProgressStart();
	DelEventHandler("FaderEvent_EndFade", "ReloadEndFade");
	//Trace("ReloadEndFade");
	ReloadProgressUpdate();
	int iLoc;
	if(reload_cur_island_index < 0)
	{
		//From location
		if(reload_island_index < 0)
		{
			//To location
			ReloadToLocation(reload_location_index, reload_locator_ref);
		}
		else
		{
			//To sea
			ReloadToSea(reload_island_index, reload_locator_ref);
		}
	}
	else
	{
		//From sea
		if(reload_island_index < 0)
		{
			//To location
			ReloadToLocation(reload_location_index, reload_locator_ref);
		}
		else
		{
			//To sea
			ReloadToSea(reload_island_index, reload_locator_ref);
		}
	}
	SendMessage(&reload_fader, "lfl", FADER_IN, RELOAD_TIME_FADE_IN, true);
	PostEvent("LoadSceneSound", 100);
	ReloadProgressUpdate();
	ReloadProgressEnd();
}

string FindEmergeLocator(ref rObject, string emerge_str)
{
	aref arReload;
	makearef(arReload,rObject.reload);
	int n = GetAttributesNum(arReload);
	for (int i=0;i<n;i++)
	{
		aref arLoc;
		arLoc = GetAttributeN(arReload,i);
		if (arLoc.name == emerge_str) 
		{
			string loc_name = GetAttributeName(arLoc);
			return loc_name;
		}
	}
 	Trace("ERROR(no find emerge string): string FindEmergeLocator(ref rObject, string emerge_str) : " + emerge_str);
	return "";
}

object chrAnimationKipper;

int ReloadToLocation(int location_index, aref reload_data)
{
	// boal переход в зашлушки, ставим дверь обратно-->
	if (CheckAttribute(&Locations[location_index], "MustSetReloadBack"))
	{
	    // reload_data.name = "reload3_back";  - откуда идем
		// reload_data.go = "Antigua_townhall";  - куда идем
		// reload_data.emerge = "reload1";  - локатор куда он же выход обратно
		// reload_data.FromSea = true; - есть только на острове, ведет к пляжу заглушке
		aref arReload, arLocator;

		makearef(arReload, Locations[location_index].reload);
		int iNumReload = GetAttributesNum(arReload);
		int i;
		if (!CheckAttribute(reload_data, "FromSea"))
		{   // переход суша-суша
			for (i=0; i<iNumReload; i++)
			{
				arLocator = GetAttributeN(arReload, i);
				if (arLocator.Name == reload_data.emerge)
				{
	                arLocator.go     = pchar.location; // где был
	                arLocator.emerge = reload_data.name; // откуда шагнул
	                if (CheckAttribute(&Locations[reload_cur_location_index], "fastreload"))
	                {
	                    Locations[location_index].fastreload = Locations[reload_cur_location_index].fastreload;
	                }
	                else
	                {
	                    DeleteAttribute(&Locations[location_index], "fastreload");
	                }
	                if (CheckAttribute(&Locations[reload_cur_location_index], "id.label"))
	                {
	                	arLocator.label  = Locations[reload_cur_location_index].id.label; // как завать, куда вернуться
	                }
	                else
	                {
	                    arLocator.label  = "";
	                }
	                if (CheckAttribute(&Locations[reload_cur_location_index], "townsack"))
	                {
	                    Locations[location_index].townsack = Locations[reload_cur_location_index].townsack;
	                }
	                else
	                {
	                    DeleteAttribute(&Locations[location_index], "townsack");
	                }
	                if (CheckAttribute(&Locations[reload_cur_location_index], "islandId"))
	                {
	                    Locations[location_index].islandId = Locations[reload_cur_location_index].islandId;
	                }
	                else
	                {
	                    DeleteAttribute(&Locations[location_index], "islandId");
	                }
	                if (CheckAttribute(&Locations[reload_cur_location_index], "id.label") && locations[reload_cur_location_index].type != "town")
	                {
	                    Locations[location_index].id.label = Locations[reload_cur_location_index].id.label;
	                }
					break;
				}
			}
		}
		else
		{ // переход море-суша
			// идея как работает
			// в Islands_init.c на локаторах входа в бухту-заглушку приписочка  .FromSea = true;
			// на суше в Locations\init\ на локаторах выхода в море приписочка  .ToSea = true;
			// на самой локации .MustSetReloadBack = true;
		    for (i=0; i<iNumReload; i++)
			{
				arLocator = GetAttributeN(arReload, i);
				if (CheckAttribute(arLocator, "ToSea")) // признак, что локатор выхода в море
				{
	                arLocator.go     = pchar.location; // где был
	                arLocator.emerge = reload_data.name; // откуда шагнул
                    // метка == море всегда
				}
			}
		}
	}
	// boal <--
	pchar.location = Locations[location_index].id;
	pchar.location.group = "reload";
	pchar.location.locator = reload_data.emerge;
	if(reload_xaddress.active == "true")
	{
		pchar.location.group = reload_xaddress.group;
		pchar.location.locator = reload_xaddress.locator;
	}
	
	//сменить анимацию перед загрузкой локации, нужно для подводных храмов.
	if (CheckAttribute(&locations[location_index], "changeAnimation"))
	{
		if (locations[location_index].id.label == "TempleUnderwater")
		{
			if (IsMusketer(pchar))
			{
				pchar.NeedMushReset = pchar.equip.musket;
                RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			}
			// if (CheckCharacterPerk(pchar, "Merman")) ~!mu
            // TO_DO:
            if (PChar.sex == "woman") PChar.model.animation = "Danielle_swim";
            else PChar.model.animation = "swim";
		}
		else
		{
			if (CheckAttribute(pchar,"NeedMushReset"))
			{
                EquipCharacterByItem(pchar, pchar.NeedMushReset);
				DeleteAttribute(pchar,"NeedMushReset");
			}
            pchar.model.animation = MainChAnim;
		}
	}

	if(!IsEntity(&chrAnimationKipper)) CreateEntity(&chrAnimationKipper, "CharacterAnimationKipper");

    // eddy --> открыть/закрыть двери в заглушках городов.
    if (CheckNPCQuestDate(&Locations[location_index], "Common_date"))
    {
    	if (Locations[location_index].type == "town" && CheckAttribute(&locations[location_index], "houseEnc"))
    	{
            string  sName;
            aref	arDis, arRld;
    		makearef(arRld, Locations[location_index].reload);
    		int		Qty = GetAttributesNum(arRld);
            SetNPCQuestDate(&Locations[location_index], "Common_date");
    		for (int a=0; a<Qty; a++)
    		{
    			arDis = GetAttributeN(arRld, a);
                sName = arDis.go;
    			if (HasSubStr(sName, "Common"))
    			{
                    if (CheckAttribute(arDis, "canEnter"))
					{
						arDis.disable = false;
						DeleteAttribute(arDis, "canEnter"); //автосъем флага на открытую дверь
					}
					else arDis.disable = rand(1);
    			}
    		}
    	}
    }
	//меняем радиусы детекторов энкаунтеров
	Locations[location_index].locators_radius.encdetector = 8 + rand(10);
    // <-- eddy
	LAi_CreateShoreChest(&Locations[location_index]);
	return LoadLocation(&Locations[location_index]);
}

int ReloadToLocationEx(int location_index, string sLocator)
{
	pchar.location = Locations[location_index].id;
	pchar.location.group = "reload";
	pchar.location.locator = sLocator;

	/*
	if(reload_xaddress.active == "true")
	{
		pchar.location.group = reload_xaddress.group;
		pchar.location.locator = reload_xaddress.locator;
	}
	*/
	
	if(IsEntity(&chrAnimationKipper) == false) 
	{
		CreateEntity(&chrAnimationKipper, "CharacterAnimationKipper");
	}
	return LoadLocation(&Locations[location_index]);
}

int ReloadToSea(int island_index, aref reload_data)
{
	
	object Login;

	pchar.lastFightMode = 0;

	ref rIsland = GetIslandByIndex(island_index);
	/*Trace("============================");
	Trace("island_index = " + island_index);
	DumpAttributes(rIsland);
	Trace("============================");*/

	pchar.location = rIsland.id;
	pchar.location.group = "reload";
	pchar.location.locator = reload_data.emerge;

	Login.Island = rIsland.id;

	Login.Encounters = "";

	string sLoc = FindEmergeLocator(rIsland,reload_data.emerge);

	Login.PlayerGroup.x = rIsland.reload.(sLoc).ships.l0.x;	// FIX-ME
	Login.PlayerGroup.z = rIsland.reload.(sLoc).ships.l0.z;
	Login.PlayerGroup.ay = rIsland.reload.(sLoc).ships.l0.ay;
	Login.FromCoast = true;

    //сохраняем координаты куда перемещаемся для корректного рассчета уровня моря
    WeatherParams.Whr_ColorizeSeaWater.SAIL_TO_LOCATOR.x = Login.PlayerGroup.x;
    WeatherParams.Whr_ColorizeSeaWater.SAIL_TO_LOCATOR.z = Login.PlayerGroup.z;

	Trace("Load from location to sea sLoc = " + sLoc + ", x = " + Login.PlayerGroup.x + ",z = " + Login.PlayerGroup.z);
		
	SeaLogin(&Login);
	return 1;

	/*
	reload_data.x
	reload_data.y
	reload_data.z
	reload_data.ships.l1.x
	*/
	return -1;
}


bool TeleportCharacterFromCurLocationToLocation(string locatorExit, string group, string locator)
{
	reload_xaddress.group = group;
	reload_xaddress.locator = locator;
	aref reload_group;
	makearef(reload_group, loadedLocation.reload);
	if(Reload(reload_group, locatorExit, loadedLocation.id) == false) return false;
	reload_xaddress.active = "true";
	return true;
}

//boal -->
int BOAL_ReloadToLoc(aref reload_group, string locator_name)
{
	int i;
	int num = GetAttributesNum(reload_group);
	if(num == 0) return 0;
	for(i = 0; i < num; i++)
	{
		reload_locator_ref = GetAttributeN(reload_group, i);
		if(locator_name == reload_locator_ref.name) break;
	}
	if(i == num)
	{
		return 0;
	}
	//Check main attributes
	if(!CheckAttribute(reload_locator_ref, "name"))
	{
		return 0;
	}
	if(!CheckAttribute(reload_locator_ref, "emerge"))
	{
		return 0;
	}
	if(!CheckAttribute(reload_locator_ref, "go"))  // нужна только эта проверка
	{
		return 0;
	}
	//Main character
	Pchar.quest.SetQuestHoldBox.win_condition.l1          = "location";
	Pchar.quest.SetQuestHoldBox.win_condition.l1.location = "My_Deck";
	Pchar.quest.SetQuestHoldBox.win_condition             = "SetQuestHoldBox";

	boarding_location  = FindLocation(reload_locator_ref.go); // че потом грохать

	//DoReloadCharacterToLocation(reload_locator_ref.go, "reload", reload_locator_ref.emerge);
	Reload(reload_group, locator_name, Pchar.location);

	return 1;
}
// boal <--

// EvgAnat - возвращает количество лоадингов с подходящим названием в папке
int GetLoadingPicsNum(string sImage)
{
	object objFileFinder;
	aref arList;
	int i, iNumFiles;
	string filename, dirname;
	iNumFiles = 1;
	filename = strcut(sImage, 8, strlen(sImage) - 1);
	if (HasSubStr(filename, "\"))
 	{
        i = findsubstr(filename, "\" , 0);
		dirname = strcut(filename, 0, i);
	 	filename = strcut(filename, i+1, strlen(filename) - 1);
 	}
	filename = strcut(filename, 0, strlen(filename) - 5);
	objFileFinder.dir = "resource\textures\loading\" + dirname;
	objFileFinder.mask = filename + "*";
	CreateEntity(&objFileFinder, "FINDFILESINTODIRECTORY");
	makearef(arList, objFileFinder.filelist);
	iNumFiles = GetAttributesNum(arList);	
	DeleteClass(&objFileFinder);
	return iNumFiles;
}

string GetRandomLoadingPic(string sImage)
{
	string res = sImage;
	if(GetLoadingPicsNum(res) > 1)
	{
		res = strcut(res, 0, strlen(res)-5) + "_" + rand(GetLoadingPicsNum(res) - 1) + ".tga";
	}
	return res;
}

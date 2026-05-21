#include "items\items.h"

object randItemModels[MAX_LOADED_RANDITEMS];
object itemModels[ITEMS_QUANTITY];
object buttonModels[MAX_BUTTONS];

aref useLocators[MAX_BUTTONS];
aref useAttrs[MAX_BUTTONS];
int  useLocatorsCount=0;

int iScriptItemStartNum=0;
int iScriptItemEndNum=0;
int iScriptItemCount=0;

float SPAWN_TIME = 168.0; //hours = 168.0

int iHerbItemModelsCount = 0;

void Items_LoadModel(ref _itemModel, ref _item)
{
	if (!IsEntity(&_itemModel))
	{
		string itemFolder = "items";
		CreateEntity(&_itemModel, "MODELR");

		if (CheckAttribute(_item, "folder") && FindFile("RESOURCE\MODELS\\" + _item.folder, _item.id, "*.gm", 0))
			itemFolder = _item.folder;

		SendMessage(&_itemModel, "ls", MSG_MODEL_SET_DIRPATH, itemFolder+"\");
		SendMessage(&_itemModel, "ls", MSG_MODEL_LOAD_GEO, itemFolder + "\" + _item.model);
		SendMessage(&_itemModel, "ls", MSG_MODEL_SET_DIRPATH,"");
		SendMessage(&_itemModel, "ls", MSG_MODEL_SET_TECHNIQUE, "RandItem");
		if (itemFolder == "ammo")
			SendMessage(&_itemModel, "lslff", MSG_MODEL_BLEND, "blenditem", 1000, 0.0, 1.0);
		LayerAddObject(EXECUTE, &_itemModel, ITEMS_LAYER);
		LayerAddObject(REALIZE, &_itemModel, ITEMS_LAYER);

		//Trace("ItemLogic: Loaded model "+itemFolder+"\"+_item.model);
	}
}

void Item_OnLoadLocation(string currentLocation)
{
	//Trace("ItemLogic: On load location "+currentLocation);

	// precache active locators in current location
	aref   activeLocation;
	int i, currentLocationIndex = FindLocation(currentlocation);
	pchar.itemLocationIndex = currentLocationIndex;
	aref aloc, an, al;
	useLocatorsCount = 0;
	makearef(activeLocation, Locations[currentLocationIndex]);
	makearef (aloc, activeLocation.items);
	for (i = 0; i < GetAttributesNum(aloc); i++)
	{
		an = GetAttributeN(aloc, i);
		if (!CheckAttribute(an,"locator"))
			continue;
		if (!FindLocator(activeLocation.id, an.locator, &al, true))
			continue;

		useLocators[useLocatorsCount] = al;
		useAttrs[useLocatorsCount] = an;
		useLocatorsCount++;
	}

	iHerbItemModelsCount = 0;

	// load buttons & items
	Items_ShowButtons(currentLocation);
	RandItems_OnLoadLocation(activeLocation);
	Box_OnLoadLocation(activeLocation);

	// показ предметов в локаторах new
	aref itemShow;
	makearef(itemShow, activeLocation.itemShow);
	int numAttrs = GetAttributesNum(itemShow);
	for (i = 0; i < numAttrs; i++)
	{
		aloc = GetAttributeN(itemShow, i);
		Items_ShowItemNew(GetAttributeName(aloc), FindItem(GetAttributeValue(aloc)));
	}

	for (i = 0; i < ITEMS_QUANTITY; i++)
	{
		if (!CheckAttribute(&Items[i], "startLocator"))
			continue;
		if (!CheckAttribute(&Items[i], "startLocation"))
			continue;
		if (!CheckAttribute(&Items[i], "shown"))
			continue;
		if (Items[i].shown == "1")
		{
			if (Items[i].startLocation == currentLocation)
			{
				Items_ShowItem(i);
			}
		}
	}
}

void Item_OnUnLoadLocation()
{
	int i = 0;
	//Trace("ItemLogic: On unload location");
	for (i = 0; i < ITEMS_QUANTITY; i++)
	{
		if (IsEntity(&itemModels[i]))
			DeleteClass(&itemModels[i]);
	}

	for (i = 0; i < MAX_LOADED_HERBS; i++)
	{
		if (IsEntity(&JungleHerbs[i]))
			DeleteClass(&JungleHerbs[i]);
	}

	for (i = 0; i < MAX_BUTTONS; i++)
	{
		if (IsEntity(&buttonModels[i]))
			DeleteClass(&buttonModels[i]);
	}

	for (i = 0; i < MAX_LOADED_RANDITEMS; i++)
	{
		if (IsEntity(&randItemModels[i]))
			DeleteClass(&randItemModels[i]);
	}

	pchar.itemLocationIndex = -1;
}

void Item_OnEnterLocator(aref _location, string _locator)
{
	//Trace("ItemLogic: Entered locator "+_locator);
	int itemN;

	if (HasSubStr(_locator, "button"))
	{ // use item
        for (itemN = ItemsForLocators_start; itemN < ItemsForLocators_end; itemN++)
		{
			if (!CheckAttribute(&Items[itemN], "useLocator"))
				continue;
			if (!CheckAttribute(&Items[itemN], "useLocation"))
				continue;
			if (!CheckAttribute(&Items[itemN], "shown"))
				continue;
			if (Items[itemN].shown == "0")
			{
				if (Items[itemN].useLocation == _location.id)
				{
					if (Items[itemN].useLocator == _locator)
					{
						Log_SetActiveAction("Action");
						pchar.activeItem = itemN;
						pchar.activeLocator = _locator;
						pchar.activeRandItem = false;
						pchar.activeItem.pick = false;
					}
				}
			}
		}
	}
	else if (CheckAttribute(_location, "itemShow." + _locator) && !GetBan("HerbPickup"))
	{
		pchar.activeItem = FindItem(_location.itemShow.(_locator));
		ILogAndActions.ActiveActions.Pick.Text = XI_ConvertString("for_quick_action_PickHerb");
		Log_SetActiveAction("Pick");
		pchar.activeLocator = _locator;
		pchar.activeRandItem = false;
		pchar.activeItem.pick = true;
		ILogAndActions.ActiveActions.Pick.Text = XI_ConvertString("for_quick_action_Pick");
	}
	else
	{
		int n = FindItem("pistol7");
		for (itemN = ItemsForLocators_start; itemN <= ItemsForLocators_end; itemN++)
		{
			if (itemN == ItemsForLocators_end)
				itemN = n;

			if (!CheckAttribute(&Items[itemN], "startLocator"))
				continue;
			if (!CheckAttribute(&Items[itemN], "startLocation"))
				continue;
			if (!CheckAttribute(&Items[itemN], "shown"))
				continue;
			if (Items[itemN].startLocator == _locator)
			{
				if (Items[itemN].shown == "1")
				{
					if (Items[itemN].startLocation == _location.id)
					{
						Log_SetActiveAction("Pick");
						pchar.activeItem = itemN;
						pchar.activeLocator = _locator;
						pchar.activeRandItem = false;
						pchar.activeItem.pick = true;
					}
				}
			}
			if (itemN == n)
				break;
		}
	}
    // ===> eddy. проверка вхождения ГГ в локаторы группы Item.
    QuestCheckEnterLocItem(_location, _locator);
    // <===
	BLI_RefreshCommandMenu();
}

void Item_OnExitLocator(aref _location, string _locator)
{
	Log_SetActiveAction("Nothing");
	pchar.activeItem = "";
	BLI_RefreshCommandMenu();
    // ===> eddy. проверка выхождения ГГ из локаторов группы Item.
    QuestCheckExitLocItem(_location, _locator);
    // <===
}

void Item_OnPickItem()
{
	Log_SetActiveAction("Nothing");
	aref activeLocation;
	makearef(activeLocation, Locations[sti(pchar.itemLocationIndex)]);

	ref rItemModel;
	int langFile = LanguageOpenFile("ItemsDescribe.txt");
	int iActiveItem = sti(pchar.activeItem);
	string sItemId, sItemName, sMsg = LanguageConvertString(langFile, "youve_got");
	string sIcon = "BoxPlus";
	string sSnd = "Important_item";

	if (pchar.activeRandItem == true)
	{
		string activeRandItemAttribute = "RandItemType" + iActiveItem;
		if (CheckAttribute(activeLocation, activeRandItemAttribute))
		{
			rItemModel = &randItemModels[iActiveItem];
			sItemId = Items[sti(activeLocation.(activeRandItemAttribute))].id;
			sItemName = LanguageConvertString(langFile, Items[sti(activeLocation.(activeRandItemAttribute))].name);
			activeLocation.(activeRandItemAttribute) = -1;
		}
	}
	else
	{
		string locator = pchar.activeLocator;

		if (CheckAttribute(activeLocation, "itemShow." + locator + ".modelIndex"))
		{
			sMsg = LanguageConvertString(langFile, "herb_find");
			sIcon = "Alchemy";
			rItemModel = &JungleHerbs[sti(activeLocation.itemShow.(locator).modelIndex)];

			if (CheckAttribute(activeLocation, "itemShow." + locator + ".particleId"))
				DeleteParticleSystem(activeLocation.itemShow.(locator).particleId); //очистка подсветки локатора после взятия предмета

			DeleteAttribute(activeLocation, "itemShow." + locator);
		}
		else
		{
			rItemModel = &itemModels[iActiveItem];
			Items[iActiveItem].shown = false;
		}
		QuestPointerDelLoc(activeLocation.id, "item", locator);

		if (CheckAttribute(&Items[iActiveItem], "particleId"))
		{
			DeleteParticleSystem(Items[iActiveItem].particleId); //очистка подсветки предмета после взятия
		}

		sItemId = Items[iActiveItem].id;
		switch (sItemId)
		{
			case "key3":
				sIcon = "Key";
				sSnd = "interface\itemKey.wav";
			break;
			case "migraine_potion":
				sIcon = "migraine_potion";
			break;
			case "herb_matricaria":
				sIcon = "matricaria";
				sSnd = "interface\harvestMatricaria.mp3";
			break;
			case "herb_zingiber":
				sIcon = "zingiber";
				sSnd = "interface\harvestZingiber.mp3";
			break;
			case "herb_ginseng":
				sIcon = "ginseng";
				sSnd = "interface\harvestGinseng.mp3";
			break;
		}
		sItemName = LanguageConvertString(langFile, Items[iActiveItem].name);
		// ===> перехват взятия предметов из локатора item на метод обрабоки для квестовых нужд
		QuestCheckTakeItem(activeLocation, Items[iActiveItem].id);
		// <===
	}
	SendMessage(rItemModel, "lslff", MSG_MODEL_BLEND, "blenditemlit", 1000, 1.0, 0.0);
	TakeNItemsNotification(pchar, GetGeneratedItem(sItemId), 1, sMsg + " " + sItemName + "!", sIcon, sSnd);
	DeleteAttribute(pchar, "activeItem");
	LanguageCloseFile(langFile);
}

void Item_OnUseItem()
{
	aref aloc, an, al;
	aref activeLocation;
	int activeItem = sti(pchar.activeItem);
	makearef(activeLocation, Locations[sti(pchar.itemLocationIndex)]);

	makearef (aloc, activeLocation.items);
	// boal баг! нет предмета, а он работает!!!
    if (!CheckCharacterItem(pchar, Items[activeItem].id))
    {
		Log_SetStringToLog(XI_ConvertString("You have not need item"));
        PlaySound("knock");
        return;
    }
    Log_SetActiveAction("Nothing");
	//Log_SetStringToLog("Using "+Items[activeItem].id);
	//Trace("ItemLogic: using item "+Items[activeItem].id);
	Items[activeItem].shown = true;
	Items[activeItem].shown.used = true; //использован
	// AlexBlade > fix Ставим обычную модельку, если у нас активен "Глаз Алмаз"
	if (CheckAttribute(&Items[activeItem], "model") && HasSubStr(Items[activeItem].model, "-new"))
	{
		Items[activeItem].model = strcut(Items[activeItem].model, 0, strlen(Items[activeItem].model) - 4 - 1);
	}
	// AlexBlade > По квесту Лейфа поставим скрижаль из модели локации позже по коду
	bool bOk = true;
	if (CheckAttribute(&Items[activeItem], "id") && Items[activeItem].id == "Rock_letter")
	{
		bOk = false;
	}
	FindLocator(activeLocation.id, pchar.activeLocator, &al, true);
	if (bOk)
	{
		Items_LoadModel(&itemModels[activeItem], &Items[activeItem]);

		SendMessage(&itemModels[activeItem], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
		SendMessage(&itemModels[activeItem], "lslff", MSG_MODEL_BLEND, "blenditem", 1000, 0.0, 1.0);
	}

	SetEventHandler("frame", "Item_OnUseFrame", 0);
	TakeItemFromCharacter(pchar, Items[activeItem].id);
	Items[activeItem].startLocator = "";
	al.active = true;
	al.timePassed = 0;

	int langFile = LanguageOpenFile("ItemsDescribe.txt");
	string displayItemName, youvegotString;
	youvegotString = LanguageConvertString(langFile, "used_item");
	displayItemName = LanguageConvertString(langFile, Items[activeItem].name);
	Log_SetStringToLog(youvegotString+" "+displayItemName+"!");
    PlaySound("EventMap");

    // ===> перехват на метод обрабоки для квестовых нужд при опускании предмета в локаторы button. Эдди.
    QuestCheckUseButton(activeLocation, pchar.activeLocator, Items[activeItem].id);
    // <===
	DeleteAttribute(pchar,"activeItem");
	
	CompleteQuestName("OnUse_"+Items[activeItem].id, "");
}

void Item_OnUseFrame()
{
	aref aloc, an, al;
	aref activeLocation;
    bool usedOnFrame=false;
    if (CheckAttribute(pchar, "itemLocationIndex") && sti(pchar.itemLocationIndex) > 0) // boal fix 230804
    {
    	makearef(activeLocation, Locations[sti(pchar.itemLocationIndex)]);

    	makearef (aloc, activeLocation.items);
    	for (int i=0; i<useLocatorsCount; i++)
    	{
    		an = useAttrs[i];
    		al = useLocators[i];
    		if (!CheckAttribute(al, "active"))
    			continue;
    		if (al.active != "1")
    			continue;
    		int timePassed = sti(al.timePassed) + GetDeltaTime();
    		al.timePassed = timePassed;
    		if (timePassed > BUTTON_ACTIVATION_TIME)
    		{
    			al.active = false;
    			continue;
    		}

    		usedOnFrame = true;
    		float timeK = makefloat(timePassed) / makefloat(BUTTON_ACTIVATION_TIME);
    		float deltaY = makefloat(an.deltaY) * timeK;

    		SendMessage(&buttonModels[i], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y)+deltaY, makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));

    		for (int j=0; j<ITEMS_QUANTITY; j++)
    		{
    			if (Items[j].useLocator == an.locator)
    			{
    				SendMessage(&itemModels[j], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y)+makeFloat(an.itemDeltaY)+deltaY, makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
    				break;
    			}
    		}
    	}
    }
    else
    {
        Log_TestInfo("Error: Item_OnUseFrame нет mch.itemLocationIndex ");
    }
	if (!usedOnFrame)
		DelEventHandler("frame", "Item_OnUseFrame");
}

void Items_ShowButtons(string _locationName)
{
	aref al;
	//Trace("ItemLogic: found "+useLocatorsCount+" buttons");
	for (int i=0; i<useLocatorsCount; i++)
	{
		Items_LoadModel(&buttonModels[i], &useAttrs[i]);
		al = useLocators[i];
		if (useAttrs[i].trigged != "1")
			SendMessage(&buttonModels[i], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
		else
			SendMessage(&buttonModels[i], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y)+makefloat(useAttrs[i].deltaY), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
	}
}

void Items_ShowItem(int _itemN)
{
	aref al;
	aref activeLocation;
	makearef(activeLocation, Locations[sti(pchar.itemLocationIndex)]);

	if (Items[_itemN].model == "")
	{
		Trace("Items_ShowItem: no model for item "+activeLocation.id+"."+Items[_itemN].id);
		return;
	}

	if (Items[_itemN].startLocator != "")
	{ //unused
		Items_LoadModel(&itemModels[_itemN], &Items[_itemN]);

		if (!FindLocator(Items[_itemN].startLocation, Items[_itemN].startLocator, &al, true))
		{
			if (TestMode())
				Trace("Items_ShowItem: locator for item "+_itemN+" not found! "+Items[_itemN].startLocation+">>"+Items[_itemN].startLocator);
		}
		else
		{
			if (TestMode())
				Trace("Items_ShowItem: showing item at "+al.x+", "+al.y+", "+al.z);

			SendMessage(&itemModels[_itemN], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
		}
	}
	else
	{ //used
		if (Items[_itemN].useLocation != activeLocation.id)
			return;

		Items_LoadModel(&itemModels[_itemN], &Items[_itemN]);

		for (int i=0; i<useLocatorsCount; i++)
		{
			al = useLocators[i];
			if (useAttrs[i].locator == Items[_itemN].useLocator)
			{
				SendMessage(&itemModels[i], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y)+makeFloat(useAttrs[i].itemDeltaY)+makeFloat(useAttrs[i].deltaY), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
				return;
			}
		}
	}
}

void Items_ShowItemNew(string locator, int _itemN)
{
	aref al;
	aref activeLocation;
	makearef(activeLocation, Locations[sti(pchar.itemLocationIndex)]);

	int modelIndex = iHerbItemModelsCount;

	if (modelIndex >= GetArraySize(&JungleHerbs))
	{
		trace("Items_ShowItemNew: >= " + GetArraySize(&JungleHerbs) + " items!");
		return;
	}

	iHerbItemModelsCount++;

	if (_itemN < 0)
		trace("Items_ShowItemNew: item not found!!!");

	if (Items[_itemN].model == "")
	{
		Trace("Items_ShowItemNew: no model for item "+activeLocation.id+"."+Items[_itemN].id);
		return;
	}

	if (StrStartsWith(Items[_itemN].id, "herb_") && GetBan("HerbHarvest"))
		return;

	activeLocation.itemShow.(locator).modelIndex = modelIndex;
	Items_LoadModel(&JungleHerbs[modelIndex], &Items[_itemN]);

	if (!FindLocator(activeLocation.id, locator, &al, true))
	{
		if (TestMode())
			trace("Items_ShowItemNew: locator for item "+_itemN+" not found! ["+activeLocation.id+">>"+locator);

		if (CheckAttribute(activeLocation, "itemShow." + locator))
			DeleteAttribute(activeLocation, "itemShow." + locator);
	}
	else
	{
		if (TestMode())
			trace("Items_ShowItemNew: showing item at "+al.x+", "+al.y+", "+al.z);

		if (!GetBan("HerbPickup") && GetOfficersPerkUsing(pchar, "HawkEye", true))
		{
			float x, y, z, h, up = 0.1;
			x = al.x;
			y = al.y;
			z = al.z;
			if (Items[_itemN].id == "herb_zingiber") up = 0.8;
			else if (Items[_itemN].id == "herb_matricaria") up = 0.6;
			else if (Items[_itemN].id == "herb_ginseng") up = 0.6;
			else up = 0.2;

			if (CheckAttribute(&InterfaceStates, "HerbDetails.Height") && stf(InterfaceStates.HerbDetails.Height) > 0.0)
			{
				h = stf(InterfaceStates.HerbDetails.Height);
				if (h > 0.65) up += 0.5;
				else if (h < 0.17) up += 0.15;
				else if (h < 0.25) up += h * 0.9;
				else up += h * 0.75;
			}

			activeLocation.itemShow.(locator).particleId = CreateParticleSystemX("signstar", x, y+up, z, x, y+up, z, 0);
		}

		SendMessage(&JungleHerbs[modelIndex], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
	}
}

void Items_HideItem(int itemN)
{
}

int Items_FindItem(string itemID, ref itemARef)
{
	int idx = FindItem(itemID);
    if (idx >= 0) makearef(itemARef,Items[idx]);
	return idx;
}

// ************** RANDOM ITEMS *****************
void RandItems_OnLoadLocation(ref _location)
{
	string locatorName;
	aref randItemLocator;
	for (int i=1; i<MAX_LOADED_RANDITEMS; i++)
	{
		string lastSpawnTimeString = "LastSpawnTime"+i;
		string randItemTypeString = "RandItemType"+i;
		locatorName = "randitem"+i;
		if (!FindLocator(_location.id, locatorName, &randItemlocator, true))
			break;

        // boal -->
        if (!SetLocationQuestRandItem(i, _location, locatorName, randItemLocator))
        {
        // boal <--
            // randitem locator found
    		if (CheckAttribute(_location, lastSpawnTimeString))
    		{ // already spawned?
    			if (CheckAttribute(_location, randItemTypeString))
    			{
    				if (sti(_location.(randItemTypeString)) != -1)
    				{
    					RandItems_DrawRandItem(i, _location, randItemLocator);
    				}
    				else
    				{ //already picked up, try to respawn
    					if ((stf(_location.(lastSpawnTimeString))+SPAWN_TIME) < Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()))
    					{
    						RandItems_SpawnRandItem(i, _location, randItemLocator);
    					}
    				}
    			}
    			else
    			{ // nothing here
    				if ((stf(_location.(lastSpawnTimeString))+SPAWN_TIME) < Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()))
    				{
    					RandItems_SpawnRandItem(i, _location, randItemLocator);
    				}
    			}
    		}
    		else
    		{
    			RandItems_SpawnRandItem(i, _location, randItemLocator);
    		}
		}
	}
}

float Items_MakeTime (float _h, float _d, float _m, float _y)
{
	return (_h+24.0*(_d + 30.0*(_m + 12.0*_y)));
}

void RandItems_SpawnRandItem(int _index, aref _location, aref al)
{
	aref randItem;
	string lastSpawnTimeString;
	int n;

	string alName = GetAttributeName(al);
	string alNameAttribute = "items."+alName;
	if (CheckAttribute(_location, alNameAttribute))
	{
		n = Items_FindItem(_location.items.(alName), &randItem);
		if (n == -1)
			return;

		lastSpawnTimeString = "LastSpawnTime"+_index;
		_location.(lastSpawnTimeString) = Items_MakeTime(0, 15, 1, 2003);
	}
	else
	{
		n = Items_FindItem(RandItems[rand(RANDITEMS_QUANTITY-1)].id, &randItem);
		if (n == -1)
			return;

		lastSpawnTimeString = "LastSpawnTime"+_index;
		_location.(lastSpawnTimeString) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	}
	
    if (GetCharacterSkillToOld(pchar, SKILL_FORTUNE) < rand(15)) return; // boal fix
    
	if (!CheckAttribute(randItem, "model") || randItem.model == "")
	{
		Trace("ItemLogic: no model for item "+_location.id+"."+randItem.id);
		return;
	}

	Items_LoadModel(&randItemModels[_index],  randItem);
	SendMessage(&randItemModels[_index], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));

	lastSpawnTimeString = "RandItemType"+_index;
	_location.(lastSpawnTimeString) = n;
}

void RandItems_DrawRandItem(int _index, aref _location, aref al)
{
	string randItemTypeString = "RandItemType"+_index;
	int n = sti(_location.(randItemTypeString));
	
    if (GetCharacterSkillToOld(pchar, SKILL_FORTUNE) < rand(15)) return; // boal fix
    
	if (Items[n].model == "")
	{
		Trace("ItemLogic: no model for item "+_location.id+"."+Items[n].id);
		return;
	}
	
	Items_LoadModel(&randItemModels[_index],  &Items[n]);
	SendMessage(&randItemModels[_index], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));
}

void RandItem_OnEnterLocator(aref _location, string _locator)
{

    int randIndex = sti(strcut(_locator, 8, strlen(_locator)-1));
	string randItemAttribute = "RandItemType"+randIndex;
	if (CheckAttribute(_location, randItemAttribute))
	{
		int currentType = sti(_location.(RandItemAttribute));
		if (currentType != -1)
		{
			Log_SetActiveAction("Pick");
			pchar.activeItem = randIndex;
			pchar.activeLocator = _locator;
			pchar.activeRandItem = true;
			pchar.activeItem.pick = true;
			BLI_RefreshCommandMenu();
		}
	}
}
// ****************** BOXES ********************

void SecretBoxRelog() //HardCoffee очистить обнаруженные секретные сундуки если гг ушёл с локации
{
	string locatorName;
	aref ar;
	for (int i = 1; i <= MAX_SECRET_CHESTS; i++) // i = 1 так как квестовые тайники не удаляем
	{
	    locatorName = "secret"+i;
		if (checkattribute(loadedlocation, locatorName) && sti(loadedLocation.(locatorName).difficult) == 0)
	    {
            makearef(ar, loadedLocation.(locatorName));
			//хранение лута после перезагрузки локи отключено из за common локаций, чтобы в соседнем доме не обнаружить уже найденный тайник
			//раскомментить и убрать EventHandler, SecretBoxRelog переместить в ReloadEndFade
			//if (sti(ar.visitedTime) + 2 < makeint(Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()))) continue;
	    	DeleteAttribute(ar, "money");
	    	DeleteAttribute(ar, "items");
	    	DeleteAttribute(ar, "visitedTime");
			ar.difficult = -1;
			// удалять атрибут .secret и .difficult нельзя, так как на них подвязана проверка на спавн
	    }
	}
	DelEventHandler(EVENT_LOCATION_UNLOAD, "SecretBoxRelog");
}

void Box_EnterToLocator(aref loc, string locName)
{
	if(!CheckAttribute(loc,locName) || GetBan("Looting")) return;

	if (HasSubStr(locName, "secret"))
    {	// секретные тайники --->
         /* HardCoffee тайники с хабаром концепт:
     	1) секретные сундуки генерируются при первом заходе на локацию
     	2) вместе с лутом сундукам присваивается уровень сложности
     	3) при заходе гг на локатор происходит проверка на внимательность относительно уровня сложности
     	4) если проверка не пройдена - слудующая проверка произойдёт не раньше, чем через отведённое время
     	5) если проверка пройдена - появляется лог, звук и возможность залезть в сундук
     	6) при повторном заходе гг на локатор возможность залезть в обнаруженый сундук остаётся, но нет оповещений
     	7) при выходе гг с локации все обнаруженные сундуки сотрутся */
		//сложность -1 связана с Common локациями, после обнаружения сундука она пресекает возможность его повторного обнаружения
		//сложность -2 выставляется рандомом во время наполнения сундуков и означает пустой сундук
		int iDiff = sti(loc.(locName).difficult);
		if (iDiff == -1) Log_TestInfo (locName +" you have already discovered this chest");
		if (iDiff == -2) Log_TestInfo (locName +" this is the fake chest");
		if (iDiff < 0) return;
		if (iDiff > 0)
		{
			// Викторинщики
		    if (locName == "secret0")
            {
            	switch (loc.id)
            	{
        			case "LaVega_town": //Port Of Spain
        				if (!checkattribute(pchar, "GenQuestRandItem.LaVega_town")) return;
        				CloseQuestHeader("QM_Port_Of_Spein");
        			break;
        			case "PuertoPrincipe_town": //Villemstad Квест 'Неудобная пропажа'
						if (!checkattribute(pchar, "GenQuestRandItem.PuertoPrincipe_town")) return;
						pchar.questTemp.womanHasband_Truba = true;
						AddQuestRecord("SCQ_Hasband_Truba", "4");
						if (CheckAttribute(pchar, "questTemp.womanHasband_Nagrada") && CheckAttribute(pchar, "questTemp.womanHasband_Truba"))
						{
							CloseQuestHeader("SCQ_Hasband_Truba");
							DeleteAttribute(pchar, "questTemp.womanHasband_Nagrada");
							DeleteAttribute(pchar, "questTemp.womanHasband_Truba");
						}
                    break;
                    case "Shore46": //Cumana
                    	if (!checkattribute(pchar, "GenQuestRandItem.Shore46")) return;
						CloseQuestHeader("QM_Cumana");
					break;
					case "Tortuga_Cave":  //Port o Prece (PortPax) Квест 'Пиратская мода' (Вызволение из плена мужа горожанки)
						if (!checkattribute(pchar, "GenQuestRandItem.Tortuga_Cave")) return;
                    	CloseQuestHeader("SCQ_PirateFashion");
						Achievment_Set(ACH_Piratskaya_moda);
                    break;
                    case "Cuba_Grot":  //Santiago
                    	if (!checkattribute(pchar, "GenQuestRandItem.Cuba_Grot")) return;
                        CloseQuestHeader("QM_Santiago");
                    break;
                    case "Shore36": //Port_Royal
                    	if (!checkattribute(pchar, "GenQuestRandItem.Shore36")) return;
                    	CloseQuestHeader("QM_Port_Royal");
                    break;
					case "CommonStoneHouse": //Bridgetown - BloodLine
						//
					break;
                }
                aref toDEL; makearef(toDEL, pchar.GenQuestRandItem);
                DeleteAttribute(toDEL, loc.id);
                goto escapeCheck;
            }

			if (Pchar.questTemp.CapBloodLine == true) return;

			//атрибут .visitedTime присваивается в момент генерации лута, в chestLogic.c
			int timeNOW = makeint(Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()));
			Log_TestInfo(locName +" visitedTime = " +loc.(locName).visitedTime +" timeNOW = " +timeNOW);
			//вместо 24 задаётся нужное время в часах для повторной проверки на внимательность
			//но не менее 24 часа, так как idRand всё равно обновляется раз в сутки
            if (sti(loc.(locName).visitedTime) + 24 > timeNOW) return;
            //проверка на восприятие
			iDiff = makeint(idRand(loc.id +locName +"r1", iDiff)/4.0 +idRand(loc.id +locName +"r2", iDiff)/4.0
			 	+idRand(loc.id +locName +"r3", iDiff)/4.0 +idRand(loc.id +locName +"r4", iDiff)/4.0 -1);
			int iPrec = GetCharacterSPECIAL(pchar, SPECIAL_P)*10;
			if (GetOfficersPerkUsing(pchar, "HawkEye", true)) iPrec += 10;
			//trace(locName +"  realDiff = " +loc.(locName).difficult +"  randDiff = " +iDiff +" precision = " +iPrec);
			Log_TestInfo(locName +"  realDiff = " +loc.(locName).difficult +"  randDiff = " +iDiff +" precision = " +iPrec);
            if (iDiff > iPrec)
            {
            	loc.(locName).visitedTime = timeNOW;
            	return;
            }
            escapeCheck: //Обход проверки для квестовых тайников
            loc.(locName).difficult = 0; //возможность подойти к сундуку заново, после прохождения проверки
			PlaySound("Key");
			log_info(StringFromKey("InfoMessages_62"));
			SetEventHandler(EVENT_LOCATION_UNLOAD, "SecretBoxRelog", 0); //это для очистки обнаруженных сундуков после перезагрузки локации
		}
    	pchar.boxname = locName;
    	Log_SetActiveAction("OpenBox");
    	BLI_RefreshCommandMenu();
    	return;
    }
	// <-- секретные тайники
	
	if(HasSubStr(locName, "private"))
	{
		// check if private box opened
		if(!CheckAttribute(loc, locName+".opened"))
        {
			if(CheckAttribute(loc, locName+".key"))
			{
				if(CheckCharacterItem(pchar, loc.(locName).key)) //проверяем ключ
				{
					loc.(locName).opened = true;
					PlaySound("Key");
					Notification(XI_ConvertString("BoxKeyOpened"), "Key");
					
					if(CheckAttribute(loc, locName+".key.delItem"))
					{
						TakeItemFromCharacter(pchar, loc.(locName).key); //забрать ключ
					}
				}
				else
				{
//					Log_SetStringToLog(XI_ConvertString("You have not need key"));
					Notification(XI_ConvertString("You have not need key"), "Key");
					PlaySound("BoxLocked");
					return;
			    }
			}
			else
			{	
				if(CheckAttribute(loc, locName+".closed")) //проверяем, не закрыт ли сундук
				{
//					Log_SetStringToLog(XI_ConvertString("Box is closed"));
					Notification(XI_ConvertString("Box is closed"), "none");
					PlaySound("DoorLocked");
					return;
			    }
		    }
	    }
	}
	
	// Warship 15.08.09 Проверка на квестовую закрытость сундуков (не только приватов, вообще всех)
	if(CheckAttribute(loc, locName + ".QuestClosed"))
	{
//		Log_SetStringToLog(XI_ConvertString("Box is closed"));
		Notification(XI_ConvertString("Box is closed"), "none");
		PlaySound("DoorLocked");
		return;
	}
	if(CheckAttribute(loc, locName + ".NotChest")) // Jason: для выброшенных на берег сундуков
	{
		Log_Testinfo("Нет доступа");
		return;
	}
	
	pchar.boxname = locName;
	Log_SetActiveAction("OpenBox");
	BLI_RefreshCommandMenu();
}

void Box_ExitFromLocator(aref loc, string locName)
{
	DeleteAttribute(pchar, "boxname");
	Log_SetActiveAction("Nothing");
	BLI_RefreshCommandMenu();
}

void OpenBoxProcedure()
{
	if (!CheckAttribute(pchar, "boxname") || GetBan("Looting")) return;
	int locidx = FindLoadedLocation();
	if(locidx<0) return;
	string atrName = pchar.boxname;
	aref ar;
	makearef(ar,Locations[locidx].(atrName));
	if(GetAttributesNum(ar)==0)
	{
		Locations[locidx].(atrName).Money = 0;
		makearef(ar, Locations[locidx].(atrName));
	}
	// God_hit_us  это такой прикол - задействовать в ловушки для сундуков(boal)
	// токо сундуки и дома
	if (sti(pchar.GenQuest.God_hit_us) == 1 && rand(100) >= (85 + GetCharacterSkillToOld(pchar, SKILL_FORTUNE)))
	{
		Log_Info(StringFromKey("InfoMessages_63"));
		PlaySound("Trapped");
		DoQuestCheckDelay("God_hit_us", 0.2);
	}
	else
	{
		LaunchItemsBox(&ar);
	}
}

void Box_OnLoadLocation(ref _location)
{
	string locatorName;
	aref boxLocator;
	int i;
	bool isAbordageBox = false;
	if (CheckAttribute(_location, "boarding"))
	{
		if (_location.boarding == "true")
		{
            if (isShipInside(_location.id) || _location.id == "Deck_Near_Ship")// boal fix 08.01.04
            {
                isAbordageBox = false;
            }
            else
            {
	            isAbordageBox = true;
            }
		}
	}

       
	// private box
	for (i=1; i < MAX_HANDLED_BOXES; i++)
	{
		locatorName = "private"+i;
		if (!FindLocator(_location.id, locatorName, &boxlocator, true))
		{
			break;
		}

		if (!CheckAttribute(_location, locatorName))
		{
			_location.(locatorName) = "";
			_location.(locatorName).open = true;
		}
		
		// Warship генерим предметы в сундуке
		if(!CheckAttribute(_location, locatorName + ".opened")) 
		{
			makearef(boxLocator, _location.(locatorName));
			FillGenerableItemsForChest(boxLocator);
		}	
	}

	// simple box
	for (i=1; i < MAX_HANDLED_BOXES; i++)
	{
		locatorName = "box"+i;
		if (!FindLocator(_location.id, locatorName, &boxlocator, true))
		{
			break;
		}

		// found box
		bool needRespawn;
		// boal -->
		//needRespawn = true;
	    needRespawn = SetLocationQuestBox(_location, locatorName);
				
		if (!needRespawn)
		{
		// boal <--
    		if (!CheckAttribute(_location, (locatorName)))
    		{
    			needRespawn = true;
    			_location.(locatorName) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
    		}
    		else
    		{
    			if ((sti(_location.(locatorName)) + SPAWN_TIME) < Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()))
    			{
    				needRespawn = true;
    				_location.(locatorName) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
    			}
    			else
    			{
    				needRespawn = false;
    			}
    		}
            if (isShipInside(_location.id) || _location.id == "Deck_Near_Ship")// boal fix 08.01.04
            {
                needRespawn = false;
            }
            // перетираем общие сундуки boal 11/03/06 -->
            if (!needRespawn && CheckAttribute(_location, "MustSetReloadBack"))
            {
                //clear items in box
    			if (CheckAttribute(_location, locatorName))
    			{
                    DeleteAttribute(_location, locatorName + ".items");
				    _location.(locatorName).items = "";
				    _location.(locatorName).money = 0;
    			}
            }
			// <--
            
    		//respawn items in box
    		if (needRespawn || isAbordageBox)
    		{
    			//clear items in box
    			if (CheckAttribute(_location, locatorName))
    			{
    				DeleteAttribute(_location, locatorName + ".items");
    				DeleteAttribute(_location, locatorName + ".Treasure"); // признак сокровища в сундуке boal
				    _location.(locatorName).items = "";
				    _location.(locatorName).money = 0;
    			}

    			//fill box with new items
    			string goodItemName;
    			int spawnItemsCount = OBJECTS_IN_BOX;
    			spawnItemsCount = spawnItemsCount + spawnItemsCount * GetCharacterSkillToOld(pchar, "Fortune") / 10.0;
    			for (int j=0; j<spawnItemsCount; j++)
    			{
    				if (needRespawn || isAbordageBox)
    				{
    					string itemID;
    					if (SpawnItem(pchar, &itemID,isAbordageBox, GetCharacterSkillToOld(pchar, "Fortune")))
    					{
    						if (CheckAttribute(_location, locatorName+".items."+itemID))
    						{
    							_location.(locatorName).items.(itemID) = sti(_location.(locatorName).items.(itemID)) + 1;
    						}
    						else
    						{
    							_location.(locatorName).items.(itemID) = 1;
    						}
    					}
    				}

    			}
				if (needRespawn || isAbordageBox) // это должно быть здесь когда уже известно значение переменной needRespawn
				{
					// Warship генерим предметы в сундуке
					makearef(boxLocator, _location.(locatorName));
					FillGenerableItemsForChest(boxLocator);
				}
    		}
		}
	}
}

// Warship Для новой системы - перебор итемов для генерации, т.к. везде ложится по-старинке - items.(itemID) = n, а генерить нужно
void FillGenerableItemsForChest(aref _chest)
{
	int i, count;
	string itemID;
	
	aref chestItems;
	aref item;
	
	makearef(chestItems, _chest.items);
	
	for(i = 0; i < GetAttributesNum(chestItems); i++)
	{
		item = GetAttributeN(chestItems, i);
		itemID = GetAttributeName(item);
		
		if(IsGenerableItem(itemID))
		{
			count = sti(chestItems.(itemID));
			DeleteAttribute(chestItems, itemID);
			
			itemID = GetGeneratedItem(itemID);
			chestItems.(itemID) = count;
		}
	}
}

bool SpawnItem(ref _chr, ref _id, bool isAbordageBox, float luck)
{
	int i = rand(RANDITEMS_QUANTITY-1);
	int chrRank = sti(_chr.rank);
	int itemRank = 0;
	aref randItem;
	if (Items_FindItem(RandItems[i].id, &randItem) == -1)
	{
		return false;
	}
	if (CheckAttribute(randItem, "minLevel"))
	{
		itemRank = sti(randItem.minLevel);
	}
	if (itemRank > chrRank)
	{
		return false;
	}

	float itemProb = 0.05;
	if (CheckAttribute(randItem, "rare"))
	{
		itemProb = stf(randItem.rare);
	}
	if (isAbordageBox)
	{
		itemProb = itemProb * (1.5 + luck/20.0);
	}
	if (itemProb > 1.0)
	{
		itemProb = 1.0;
	}
	int rndNumber = rand(1000);
	if (rndNumber > (itemProb*1000))
	{
		return false;
	}
	
	// отличные клинки в сундуках больше не генерятся <-- ugeen
	if (CheckAttribute(randItem, "quality") && HasStrEx(randItem.quality, "excellent,unique", "|"))
		return false;
	
	_id = GetGeneratedItem(randItem.id);
	return true;
}

// KZ > автоматическая посадка травы; авторы в ККС: Jason, mitrokosta
bool HarvestHerbAuto(ref rLoc)
{
	if (GetBan("HerbHarvest") || CheckAttribute(rLoc, "HarvestHerbCustom")) return false;
	if (!CheckAttribute(rLoc, "id") || !CheckAttribute(rLoc, "type")) return false;
	if (rLoc.type != "jungle" && rLoc.type != "mayak") return false;
	if (CheckAttribute(rLoc, "fastreload") && CheckAttribute(rLoc, "id.label") && rLoc.id.label != "exittown") return false;
	if (!CheckAttribute(rLoc, "locators.item") || rLoc.id.label == "Cave entrance" || rLoc.type == "seashore" || rLoc.type == "cave") return false;

	int iPerk = CheckCharacterPerk(pchar, "Naturalcure");

	if (CheckAttribute(rLoc, "HarvestHerbAuto") && GetNpcQuestPastDayParam(rLoc, "HarvestHerbAuto") > (9 - iPerk))
	{
		// > травы вырастают вновь каждые 9-10 дней (если у rLoc нет атрибута ручной посадки HarvestHerbCustom)
		HarvestHerbClear(rLoc.id, 0);
	}

	if (!CheckAttribute(rLoc, "HarvestHerbAuto"))
	{
		int i, n = 1 + iPerk; // > сколько растений садить в джунглях и на маяках (1, а при наличии перка "Лечение травами" - 2)
		string sItem, sLocator, sTemp[2];

		if (rLoc.id.label == "exittown")
			n += 1; // > сразу за городскими воротами растёт ещё на 1 растение больше

		for (i = 0; i < MAX_LOADED_HERBS; i++)
		{
			ArrayAddValue(&sTemp, "flower" + (i + 1));
		}

		for (i = 0; i < n; i++)
		{
			sLocator = ArrayGetRandomValue(&sTemp);
			ArrayRemoveValue(&sTemp, sLocator);

			if (!CheckAttribute(rLoc, "locators.item." + sLocator))
				continue;

			sItem = "" + Items[Ingredients_start + rand((Ingredients_end - Ingredients_start) - 1)].id;
			SetItemInLocation(sItem, rLoc.id, sLocator);

			rLoc.HarvestHerbAuto.(sLocator) = true;
//			Logs("Травка " + GetItemName(sItem) + " выросла в " + sLocator);
		}

		SaveCurrentNpcQuestDateParam(rLoc, "HarvestHerbAuto");
		return true;
	}

	return false;
}

// KZ > ручная посадка травы в случайный локатор flower*
bool HarvestHerbCustom(string _sLocation, string _sHerbs)
{
	if (FindLocation(_sLocation) < 0)
		return false;

	ref rLoc = &locations[FindLocation(_sLocation)];
	HarvestHerbClear(_sLocation, 1);

	int i, n, h = KZ|Symbol(_sHerbs, ",");
	int q = 0;
	string sHerb, sLocator, sTemp[2];

	for (i = 0; i < MAX_LOADED_HERBS; i++)
	{
		ArrayAddValue(&sTemp, "flower" + (i + 1));
	}

	for (n = 0; n <= h; n++)
	{
		sHerb = stripblank(GetSubStr(_sHerbs, ",", n));

		if (KZ|Symbol(sHerb, ":") > 0)
		{
			q = sti(FindStringAfterChar(sHerb, ":"));
			sHerb = FindStringBeforeChar(sHerb, ":");
		}

		if (FindItem(sHerb) < 0)
			continue;

		for (i = 0; i < q; i++)
		{
			sLocator = ArrayGetRandomValue(&sTemp);
			ArrayRemoveValue(&sTemp, sLocator);

			SetItemInLocation(sHerb, _sLocation, sLocator);
			rLoc.HarvestHerbCustom.(sLocator) = true;
		}
	}

	return true;
}

// KZ > удалить в локации _sLocation все травы; !bAll - удалить только те, что посажены автоматически, bAll - и те, что вручную тоже
bool HarvestHerbClear(string _sLocation, bool bAll)
{
	if (FindLocation(_sLocation) < 0)
		return false;

	ref rLoc = &locations[FindLocation(_sLocation)];
	aref arHerbs;
	string sHerbType = "HarvestHerbAuto";
	int i, n, q;

	for (i = 0; i <= bAll; i++)
	{
		if (i > 0)
			sHerbType = "HarvestHerbCustom";

		makearef(arHerbs, rLoc.(sHerbType));
		q = GetAttributesNum(arHerbs);

		if (q > 0)
		{
			for (n = 0; n < q; n++)
			{
				string flowerLocator = GetAttributeName(GetAttributeN(arHerbs, n));
				RemoveItemFromLocation(rLoc.id, flowerLocator);
			}
		}
	}

	DeleteAttributeEx(rLoc, "HarvestHerbAuto,HarvestHerbCustom");
	return true;
}

// mitrokosta установить предмет в локации
void SetItemInLocation(string itemID, string location, string locator) {
	int index = FindLocation(location);
	if (index < 0) {
		return;
	}
	
	locations[index].itemShow.(locator) = itemID;
}

// mitrokosta убрать предмет из локации
void RemoveItemFromLocation(string location, string locator) {
	int index = FindLocation(location);
	if (index < 0) {
		return;
	}
	
	DeleteAttribute(&locations[index], "itemShow." + locator);
}

object g_TmpModelVariable; // код от к3, в скриптах нет вообще, есть проверка в ядре
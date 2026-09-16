//> AlexBlade ставим чайку

object SeagullLocModels[9];
object ParrotLocModel;

void CreateSeagullInTown(ref loc)
{
	if (!CheckAttribute(loc, "locators.animals"))
		return;

	CreateParrotInLocation(loc, false);

	if (!IsDay())
		return;

	int modelsMaxCount = GetArraySize(&SeagullLocModels);
	aref _seagull_loc;
	aref _loc_locators;

	// DumpAttributes(loc);

	makearef(_loc_locators,loc.locators.animals);

	int curSeagullModelIdx = 0;
	for (int i = 0; i < GetAttributesNum(_loc_locators); i++)
	{
		if (curSeagullModelIdx >= modelsMaxCount)
			break;

		aref locRef = GetAttributeN(_loc_locators, i);
		if (HasSubStr(GetAttributeName(locRef), "seagull"))
		{
			_seagull_loc = locRef;
			ref _seagullModel = &SeagullLocModels[curSeagullModelIdx];
			curSeagullModelIdx++;

			CreateEntity(_seagullModel, "MODELR");
			string itemFolder = "MainMenu" + "\";
			SendMessage(_seagullModel, "ls", MSG_MODEL_SET_DIRPATH, itemFolder);
			SendMessage(_seagullModel, "ls", MSG_MODEL_LOAD_GEO, itemFolder + "seagull");
			SendMessage(_seagullModel, "ls", MSG_MODEL_LOAD_ANI, "seagull");
			SendMessage(_seagullModel, "ls", MSG_MODEL_SET_DIRPATH,"");
			SendMessage(_seagullModel, "ls", MSG_MODEL_SET_TECHNIQUE, "DLightModel");
			LayerAddObject(REALIZE, _seagullModel, ITEMS_LAYER);
			SendMessage(_seagullModel, "lls", MSG_MODEL_PLAY_ACTION, 0, "idle");
			SendMessage(_seagullModel, "lffffffffffff", MSG_MODEL_SET_POSITION, stf(_seagull_loc.x), stf(_seagull_loc.y), stf(_seagull_loc.z),
				1, 0, 0,
				0, 1, 0,
				0, 0, 1);
		}
	}
}

void CreateParrotInLocation(ref loc, bool fromCabin)
{
	if (!CheckAttribute(loc, "locators.animals.parrot"))
		return;

	aref rLocator;
	string sModel = "amazonBlue";

	if (loc.type != "residence")
	{
		if (!IsDay()) return;
		if (loc.type == "boarding_cabine")
		{
			//HardCoffee это вражеские кэпы. Пока не будем спавнить. Потом, возможно, для квестовых кэпов запилим
			return;
		}
		switch (idRand(loc.id +"amazon", 3))
		{
			case 0: sModel = "amazonGreen"; break;
			case 1: sModel = "amazonBlue"; break;
			case 2: sModel = "amazonRed"; break;
			case 3: return; break;
		}
	}
	else
	{
		//Задаём радиус взаимодействия в резиденциях и подключаем детект локатора
		switch (loc.id)
		{
			case "Pirates_townhall":
				sModel = "amazonBlue";
				SetParrotLocatorRadius(loc, 1.2, 3.0);
			break;
			case "LeFransua_townhall":
				sModel = "amazonRed";
				SetParrotLocatorRadius(loc, 0.7, 3.0);
			break;
			case "LaVega_townhall":
				sModel = "amazonGreen";
				SetParrotLocatorRadius(loc, 0.7, 2.7);
			break;
			case "Bucaneer_outpost_townhall":
				sModel = "amazonBlue";
				SetParrotLocatorRadius(loc, 0.6, 2.6);
			break;
/*			case "PuertoPrincipe_townhall":
				sModel = "amazonGreen";
			break;*/

			//Это спавн в каюту ГГ. Если запустили функцию из селф-диалога, то fromCabin будет true, этот кейс
			//пойдёт дальше и установит атрибут cabinParrot
			if (!GetDLCEnabled(NABOB_PACK))
			{
				TEV.cabinParrot = "0";
				return;
			}
			if ("0" == TEV.cabinParrot && !fromCabin) return;

			sModel = "amazonWhite";
			TEV.cabinParrot = "1";

			case "My_Cabin":
				SetParrotLocatorRadius(loc, 1.0, 2.5);
			break;
			case "My_CabineFDM":
				SetParrotLocatorRadius(loc, 1.0, 2.5);
			break;
			case "My_Cabin_Small":
				SetParrotLocatorRadius(loc, 0.6, 1.1);
			break;
			case "My_Cabin_Small2":
				SetParrotLocatorRadius(loc, 0.60, 1.2);
			break;
			//case "My_Cabin_Small3":
			//break;
			case "My_Cabin_Small4":
				SetParrotLocatorRadius(loc, 0.9, 1.2);
			break;
			case "My_Cabin_Medium":
				SetParrotLocatorRadius(loc, 0.6, 2.0);
			break;
			case "My_Cabin_Medium2":
				SetParrotLocatorRadius(loc, 0.7, 1.2);
			break;
			case "My_Cabin_Medium3":
				SetParrotLocatorRadius(loc, 0.9, 1.9);
			break;
			case "My_Cabin_Medium4":
				SetParrotLocatorRadius(loc, 0.9, 1.9);
			break;
			case "My_Cabin_Medium5":
				SetParrotLocatorRadius(loc, 0.9, 1.9);
			break;
			case "My_Cabin_Medium6":
				SetParrotLocatorRadius(loc, 0.95, 3.0);
			break;
			case "My_Cabin_Big":
				SetParrotLocatorRadius(loc, 0.8, 1.9);
			break;
			case "My_Cabin_Huge":
				SetParrotLocatorRadius(loc, 1.5, 1.0);
			break;
			case "My_Cabin_Quest":
				SetParrotLocatorRadius(loc, 1.0, 2.5);
			break;
		}
	}

	makearef(rLocator, loc.locators.animals.parrot);
	ref rParrot = &ParrotLocModel;
	CreateEntity(rParrot, "MODELR");
	string itemFolder = "Animals" + "\";
	sModel = itemFolder + sModel;
	SendMessage(rParrot, "ls", MSG_MODEL_SET_DIRPATH, itemFolder);
	SendMessage(rParrot, "ls", MSG_MODEL_LOAD_GEO, sModel);
	SendMessage(rParrot, "ls", MSG_MODEL_LOAD_ANI, "amazon");
	SendMessage(rParrot, "ls", MSG_MODEL_SET_DIRPATH,"");
	SendMessage(rParrot, "ls", MSG_MODEL_SET_TECHNIQUE, "DLightModel");
	LayerAddObject(REALIZE, rParrot, ITEMS_LAYER);
	SendMessage(rParrot, "lls", MSG_MODEL_PLAY_ACTION, 0, "idle");
	SendMessage(rParrot, "lffffffffffff", MSG_MODEL_SET_POSITION, stf(rLocator.x), stf(rLocator.y), stf(rLocator.z),
			stf(rLocator.vx.x), stf(rLocator.vx.y), stf(rLocator.vx.z),
			stf(rLocator.vy.x), stf(rLocator.vy.y), stf(rLocator.vy.z),
			stf(rLocator.vz.x), stf(rLocator.vz.y), stf(rLocator.vz.z));
}

//> AlexBlade Удаляем чайку
void UnloadSeagullInTown(aref loc)
{
	if (!CheckAttribute(loc, "type"))
		return;

	if (!CheckAttribute(loc, "locators.animals"))
		return;

	int modelsMaxCount = GetArraySize(&SeagullLocModels);
	for (int i = 0; i < modelsMaxCount; i++)
	{
		if (IsEntity(&SeagullLocModels[i]))
			DeleteClass(&SeagullLocModels[i]);
	}

	if (!CheckAttribute(loc, "locators.animals.parrot"))
		return;

	if (IsEntity(&ParrotLocModel))
		DeleteClass(&ParrotLocModel);
}

void SetParrotLocatorRadius(ref loc, float fRadius, float height)
{
	loc.locators_radius.animals.parrot = fRadius;
	SendMessage(loc, "lssf", MSG_LOCATION_LOC_RADIUS, "animals", "parrot", fRadius);
	AddCharacterLocatorGroup(pchar, "animals");
	SendMessage(loc, "lf", MSG_UPDATE_LOCATOR_DETECTOR, height);
}

void DisableCabinParrot()
{
	if (SendMessage(&Sound, "ll", MSG_SOUND_IS_PLAYING, CharVoice))
		SendMessage(&Sound, "lll", MSG_SOUND_STOP, CharVoice, 0);

    SendMessage(&ParrotLocModel, "lslff", MSG_MODEL_BLEND, "blenditemlit", 1000, 1.0, 0.0);
	loadedlocation.locators_radius.animals.parrot = 0.0;
	SendMessage(loadedlocation, "lssf", MSG_LOCATION_LOC_RADIUS, "animals", "parrot", 0.0);
	DelCharacterLocatorGroup(pchar, "animals");
	SendMessage(loadedlocation, "lf", MSG_UPDATE_LOCATOR_DETECTOR, 1.0);
	Lai_MethodDelay("DeleteParrotFromLoc", 2.0);

	TEV.cabinParrot = "0";
}

void DeleteParrotFromLoc()
{
    DeleteClass(&ParrotLocModel);
}
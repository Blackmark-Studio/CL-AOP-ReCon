// Warship 06.09.08 Переделка интерфейса обыска трупов, обмена с офами и сундука
// Большая часть интерфейса - это интерфейс покупки/продажи предметов

#define INTERFACETYPE_EXCHANGE_ITEMS		1
#define INTERFACETYPE_CHEST					2
#define INTERFACETYPE_DEADMAN				3
#define INTERFACETYPE_BARREL				4
#define INTERFACETYPE_STORAGE				5
#define INTERFACE_ITEMSBOX_CHAR_ARROYSIZE	10

int nCurScrollNum = 0;
int iCharCapacity, iCharQty, iStoreQty, iCurGoodsIdx;
float fCharWeight, fStoreWeight, fWeight;
bool bShowChangeWin = false;
bool bChestEnable = false;
int BuyOrSell = 0;
ref refCharacter, rCabin, rHold;
bool bBoxUsed = false; // Сундук-ли?
aref refToChar, arChest, arDeadChar, arBox;
string sCharactersArroy[INTERFACE_ITEMSBOX_CHAR_ARROYSIZE];
for (int i = 0; i < INTERFACE_ITEMSBOX_CHAR_ARROYSIZE; i++)
{
    sCharactersArroy[i] = "";
}

int iInterfaceType;

int iTableAddAllBtnX = 240;
int iTableAddAllBtnY = 187;
int iTableRemoveAllBtnX = 518;
int iTableRemoveAllBtnY = 187;

int FilterMode = 1;
int sortColumnIdx = -1;

int iLinesCount = 0;

void InitInterface_RS(string iniName, ref itemsRef, string faceID)
{
	//trace("InitInterface_RS!!!");
	DeleteAttribute(&TEV, "BoxTransferItems");
	FixDublicateThreasureMaps(itemsRef);

	iInterfaceType = GetInterfaceType(faceID);

	//HardCoffee обмен с компаньоном прямая замена ссылки на реального персонажа, вместо клона
	if (iInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS && CheckAttribute(itemsRef, "IsCompanionClone"))
		itemsRef = &characters[sti(itemsRef.RealCompanionIdx)];

	// Warship fix 17.04.09 паузить или нет игру. Если false - не паузить. Нужно для обысков сундуков - кражи
	if (iInterfaceType == INTERFACETYPE_BARREL || iInterfaceType == INTERFACETYPE_STORAGE)
	{
		StartAboveForm(true);
	}
	else
	{
		StartAboveForm(false);
	}
	refCharacter = GetMainCharacter();
	makearef(refToChar, itemsRef);

	if (CheckAttribute(itemsRef, "Money"))
	{
		Log_TestInfo(XI_ConvertString("Money") + " - " + itemsRef.money);
	}

	LAi_SetActorTypeNoGroup(PChar); // Тип актера - чтоб с нами могли побазарить, если увидели в сундуке

	if (iInterfaceType == INTERFACETYPE_CHEST || iInterfaceType == INTERFACETYPE_BARREL) // Если сундук или бочка
	{
		makearef(arChest, itemsRef);
		bBoxUsed = true;

		if (!LAi_boarding_process)
		{
			QuestCheckTakeBoxes(itemsRef); // Перехват
		}
		else
		{
			if (CheckWeights(arChest))
				TEV.BoxTransferItems.Button = "1";
		}
	}

	if (iInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS || iInterfaceType == INTERFACETYPE_DEADMAN)
	{
		if (iInterfaceType == INTERFACETYPE_DEADMAN) // Если обыск трупа
		{
			makearef(arDeadChar, itemsRef);
		}

		iSetCharIDToCharactersArroy(itemsRef); // Не нужно это, но и не помешает
		bBoxUsed = false;
	}

	// evganat - энциклопедия
	if (iInterfaceType == INTERFACETYPE_CHEST && CheckAttribute(arChest, "encyclopedia"))
	{
		GetPage(arChest.encyclopedia.tome, sti(arChest.encyclopedia.page));
		DeleteAttribute(arChest, "encyclopedia");
	}
	if (iInterfaceType == INTERFACETYPE_DEADMAN && CheckAttribute(arDeadChar, "encyclopedia"))
	{
		GetPage(arDeadChar.encyclopedia.tome, sti(arDeadChar.encyclopedia.page));
		DeleteAttribute(arDeadChar, "encyclopedia");
	}

	if (iInterfaceType == INTERFACETYPE_CHEST || iInterfaceType == INTERFACETYPE_DEADMAN) // проверка квестовых ситуаций в каюте кэпа если сундук или обыск трупа
	{
		ShipSituation_SetQuestSituation(ShipSituation_0);
	}

	if (Get_My_Cabin() == "")
		Set_My_Cabin();

	if (iInterfaceType == INTERFACETYPE_STORAGE && FindLocation(Get_My_Cabin()) != -1 && or(CheckShipMoored(), pchar.location == "Secret_Fort_Ammo"))
	{
		bChestEnable = true;
		rCabin = &locations[FindLocation(Get_My_Cabin())];
		rHold = &locations[FindLocation("My_Deck")];
	}

	GameInterface.TABLE_LIST.hr.td1.str = XI_ConvertString("QuantityShort");
	GameInterface.TABLE_LIST.hr.td1.scale = 0.85;
	GameInterface.TABLE_LIST.hr.td2.str = XI_ConvertString("Common") + "\n" + LowerFirst(XI_ConvertString("weight"));
	GameInterface.TABLE_LIST.hr.td2.scale = 0.85;
	GameInterface.TABLE_LIST.hr.td2.textoffset = "0, 2";
	GameInterface.TABLE_LIST.hr.td3.str = XI_ConvertString("ItemsColonTitle");
	GameInterface.TABLE_LIST.hr.td3.scale = 0.85;
	GameInterface.TABLE_LIST.hr.td4.str = XI_ConvertString("Common") + "\n" + LowerFirst(XI_ConvertString("weight"));
	GameInterface.TABLE_LIST.hr.td4.scale = 0.85;
	GameInterface.TABLE_LIST.hr.td4.textoffset = "0, 2";
	GameInterface.TABLE_LIST.hr.td5.str = XI_ConvertString("QuantityShort");
	GameInterface.TABLE_LIST.hr.td5.scale = 0.85;

	FillCharactersScroll();

	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);

	if (CheckAttribute(&TEV, "LootCollector.Run"))
		SetFormatedText("MAIN_CAPTION", XI_ConvertString("TrophiesCollected"));
	else
		SetFormatedText("MAIN_CAPTION", XI_ConvertString(sGetInterfaceTypeStr()));

	if (iInterfaceType == INTERFACETYPE_CHEST)
	{
		if (HasSubStr(GetAttributeName(arChest), "secret"))
		{
			SetFormatedText("MAIN_CAPTION", XI_ConvertString("titleSectet"));
			SetFormatedText("TABSTR_3", XI_ConvertString("Item_SECRET"));
		}
		else SetFormatedText("TABSTR_3", XI_ConvertString("Item_CHEST"));
	}
	if (iInterfaceType == INTERFACETYPE_BARREL) SetFormatedText("TABSTR_3", XI_ConvertString("Item_BARREL"));
	if (iInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS) SetFormatedText("TABSTR_3", XI_ConvertString("Item_EXCHANGE"));
	if (iInterfaceType == INTERFACETYPE_DEADMAN) SetFormatedText("TABSTR_3", XI_ConvertString("Item_DEADMAN"));
	if (iInterfaceType == INTERFACETYPE_STORAGE) SetFormatedText("TABSTR_3", XI_ConvertString("Item_STORAGE"));

	SetVAligmentFormatedText("TABSTR_3");

	SetControlsTabMode(3);

	CreateString(true, "CharName", "", FONT_NORMAL, COLOR_MONEY, 400, 99, SCRIPT_ALIGN_CENTER, 0.7);

	InterfaceInitButtons(refCharacter);

	// Тут позиционим кнопки взятия на таблице
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY - 12, iTableAddAllBtnX + 30, iTableAddAllBtnY + 22, 0);
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY - 12, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 22, 0);

	if (iInterfaceType == INTERFACETYPE_CHEST || iInterfaceType == INTERFACETYPE_BARREL) // Только если сундук - у него никаких кнопок нету
	{

	}

	if (iInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS) // Установим строки с именами
	{
		GameInterface.strings.CharName = GetFullNameTitulForm(refToChar);
	}
	else
	{
		GameInterface.strings.CharName = GetFullNameTitulForm(refCharacter);
	}

	SetCharWeight();
	SetDescription();

	SetCharacterMoneyToGold(refCharacter); // Переводим деньги ГГ в золото
	SetCharacterMoneyToGold(itemsRef);
	iSetCharIDToCharactersArroy(refCharacter); // Заносим в список ГГ

	AddToTable(itemsRef, FilterMode);
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index));
	FillCharactersImages();

	SetEventHandler("InterfaceBreak", "ProcessBreakExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("ievnt_command", "ProcCommand", 0);
	SetEventHandler("evntDoPostExit", "DoPostExit", 0);
	SetEventHandler("OnTableClick", "OnTableClick", 0);
	SetEventHandler("MouseRClickUP", "EndTooltip", 0);
	SetEventHandler("ShowHelpHint", "ShowHelpHint", 0);
	SetEventHandler("ShowItemInfo", "ShowItemInfo", 0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("TransactionOK", "TransactionOK", 0);
	SetEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT", 0);
	SetEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON", 0);
	SetEventHandler("ADD_BUTTON", "ADD_BUTTON", 0);
	SetEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON", 0);
	SetEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON", 0);
	SetEventHandler("frame", "ProcessFrame", 1);
	SetEventHandler("eTabControlPress", "procTabChange", 0); // Событие смены закладки
	SetEventHandler("OnHeaderClick", "OnHeaderClick", 0);

	if (CheckAttribute(&TEV, "LootCollector.Run") && !CheckAttribute(&TEV, "LootCollector.Tutor"))
	{
		string sHeader, sText1, sText2, sText3, sText4;

		// --> TODO: потом добавить
		string sPicture = "none";
		string sGroup = "none";
		string sGroupPicture = "none";
		// <--

		sHeader = XI_ConvertString("FastTrophiesCollected");
		sText1 = XI_ConvertString("TrophiesHelper_1");
		sText2 = XI_ConvertString("TrophiesHelper_2");
		sText3 = "";
		sText4 = XI_ConvertString("TrophiesHelper_3");

		CreateTooltip("#" + sHeader, sText1, argb(255, 255, 255, 255), sText2, argb(255, 255, 255, 130), sText3, argb(255, 175, 255, 175), sText4, argb(255, 255, 255, 255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void InterfaceInitButtons(ref _refCharacter)
{
	SetNodeUsing("GETALL_BUTTON", false);
	SetNodeUsing("DELBODY_BUTTON", false);
	SetNodeUsing("SKULL_BUTTON", false);
	SetNodeUsing("TRANSFERALL_BUTTON", false);

	bool okBox = false;
	bool okLoc = false;

	if (FindLocation(pchar.location) >= 0)
	{
		ref locRef = &locations[FindLocation(pchar.location)];
		okLoc = !StrStartsWith(pchar.location, "my_");
		okBox = LAi_boarding_process && okLoc && LootCollectorCheckCrew() && CheckAttribute(locRef, "type") && locRef.type == "boarding_cabine";
	}

	float foffsetX, foffsetY;
	GetXYWindowOffset(&foffsetX, &foffsetY);
	//Отображаем кнопку "Взять Всё" только если нет шанса что нас заметят живые ownerЫ и watchBoxesЫ
	if (okLoc && !LAi_CanNearOwners(pchar, 30))
	{
		TEV.BoxTransferItems.GETALL_BUTTON = true;
		SetNodeUsing("GETALL_BUTTON", true);
		SetCurrentNode("GETALL_BUTTON");

		if (CheckAttribute(&TEV, "BoxTransferItems.Button") && okBox)
			SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "GETALL_BUTTON", 1, 230 + makeint(foffsetX), 557 + makeint(foffsetY), 370 + makeint(foffsetX), 582 + makeint(foffsetY));
		else
			SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "GETALL_BUTTON", 1, 330 + makeint(foffsetX), 557 + makeint(foffsetY), 470 + makeint(foffsetX), 582 + makeint(foffsetY));
	}
	switch (iInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			SetNodeUsing("GETALL_BUTTON", true);
			SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "GETALL_BUTTON", 1, 330 + makeint(foffsetX), 557 + makeint(foffsetY), 470 + makeint(foffsetX), 582 + makeint(foffsetY));
		break;

		case INTERFACETYPE_DEADMAN:
			SetNodeUsing("GETALL_BUTTON", true);
			SetNodeUsing("DELBODY_BUTTON", true);
			SetCurrentNode("GETALL_BUTTON");

			SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "GETALL_BUTTON", 1, 255 + makeint(foffsetX), 557 + makeint(foffsetY), 395 + makeint(foffsetX), 582 + makeint(foffsetY));
			SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "DELBODY_BUTTON", 1, 405 + makeint(foffsetX), 557 + makeint(foffsetY), 545 + makeint(foffsetX), 582 + makeint(foffsetY));
			if (CheckCharacterItem(_refCharacter, "SkullAztec") && IsAztecSkullOfficer(arDeadChar) && LAi_IsDead(characters[sti(arDeadChar.index)]) && CheckNPCQuestDate(_refCharacter, "AztecSkull"))
			{
				SetNodeUsing("SKULL_BUTTON", true);
				SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "GETALL_BUTTON", 1, 180 + makeint(foffsetX), 557 + makeint(foffsetY), 320 + makeint(foffsetX), 582 + makeint(foffsetY));
				SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "SKULL_BUTTON", 1, 330 + makeint(foffsetX), 557 + makeint(foffsetY), 470 + makeint(foffsetX), 582 + makeint(foffsetY));
				SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "DELBODY_BUTTON", 1, 480 + makeint(foffsetX), 557 + makeint(foffsetY), 620 + makeint(foffsetX), 582 + makeint(foffsetY));
			}
		break;

		case INTERFACETYPE_CHEST:
			if (CheckAttribute(&TEV, "LootCollector.Run"))
			{
				SetNodeUsing("GETALL_BUTTON", true);
				SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "GETALL_BUTTON", 1, 330 + makeint(foffsetX), 557 + makeint(foffsetY), 470 + makeint(foffsetX), 582 + makeint(foffsetY));
			}
			else
			{
				if (CheckAttribute(&TEV, "BoxTransferItems.Button") && okBox) // KZ > если ГГ и компания физически не могут утащить на себе всё содержимое сундука, то рисуем кнопку "Сгрузить в трюм!"
				{
					SetNodeUsing("TRANSFERALL_BUTTON", true);
					if (CheckAttribute(&TEV, "BoxTransferItems.GETALL_BUTTON"))
						SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "TRANSFERALL_BUTTON", 1, 420 + makeint(foffsetX), 557 + makeint(foffsetY), 560 + makeint(foffsetX), 582 + makeint(foffsetY));
					else
						SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "TRANSFERALL_BUTTON", 1, 330 + makeint(foffsetX), 557 + makeint(foffsetY), 470 + makeint(foffsetX), 582 + makeint(foffsetY));
				}
			}
		break;

		case INTERFACETYPE_BARREL:
			SetNodeUsing("GETALL_BUTTON", true);
			SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "GETALL_BUTTON", 1, 330 + makeint(foffsetX), 557 + makeint(foffsetY), 470 + makeint(foffsetX), 582 + makeint(foffsetY));
		break;

		case INTERFACETYPE_STORAGE:
			SetNodeUsing("GETALL_BUTTON", true);
			SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_MSG_TO_NODE, "GETALL_BUTTON", 1, 330 + makeint(foffsetX), 557 + makeint(foffsetY), 470 + makeint(foffsetX), 582 + makeint(foffsetY));
		break;
	}
}

void SetCharacterMoneyToGold(aref rChar) // В интерфейсе оперируем с деньгами как с предметом "gold"
{
	bool bOk = iInterfaceType == INTERFACETYPE_CHEST || iInterfaceType == INTERFACETYPE_BARREL;
	if (bOk && !CheckAttribute(rChar, "ID"))
	{
		if (!CheckAttribute(rChar, "Items.Gold")) rChar.Items.Gold = 0;
		rChar.items.gold = sti(rChar.items.gold) + sti(GetAttrValue(rChar, "money")); // По квестам ложится сразу золото, а не деньги
	}
	else
	{
		bOk = CheckAttribute(rChar, "ID") && rChar.id == pchar.id;
		if (iInterfaceType != INTERFACETYPE_STORAGE || bOk)
			rChar.items.gold = sti(GetAttrValue(rChar, "money"));
	}
}

int iSetCharIDToCharactersArroy(ref _rChar)
{
	string sCurArroyID;
	string sCharID = _rChar.id;
	for (int i = 0; i < INTERFACE_ITEMSBOX_CHAR_ARROYSIZE; i++)
	{
		sCurArroyID = sCharactersArroy[i];
		if (sCurArroyID == sCharID) return i;

		if (sCurArroyID == "")
		{
			sCharactersArroy[i] = sCharID;
			return i;
		}
	}

	// Не знаю, возможна ли нехватка свободных, ведь define INTERFACE_ITEMSBOX_CHAR_ARROYSIZE 10
	sCharactersArroy[0] = sCharID; // Свободных нету, но поставить-то нужно
	return 0;
}

void MakeMoneyFromGoldWithowtChest()
{
	string sCurArroyID;
	ref arCurChar;
	for (int i = 0; i < INTERFACE_ITEMSBOX_CHAR_ARROYSIZE; i++)
	{
		sCurArroyID = sCharactersArroy[i];
		if (sCurArroyID != "")
		{
			arCurChar = CharacterFromID(sCurArroyID);
			arCurChar.money = GetCharacterItem(arCurChar, "Gold");
			DeleteAttribute(arCurChar, "items.gold");
		}
	}
}

void MakeMoneyFromGoldWithChest(aref _arChest)
{
	_arChest.money = GetCharacterItem(_arChest, "Gold");
	DeleteAttribute(_arChest, "items.gold");
	MakeMoneyFromGoldWithowtChest();
}

void MakeMoneyFromGoldWithDeadMan(aref _arDeadChar)
{
	_arDeadChar.money = GetCharacterItem(_arDeadChar, "Gold");
	DeleteAttribute(_arDeadChar, "items.gold");
	MakeMoneyFromGoldWithowtChest();
}

int GetInterfaceType(string sFaceID)
{
	if (sFaceID == "")			return	INTERFACETYPE_CHEST;	// Сундук
	if (sFaceID == "Barrel")	return	INTERFACETYPE_BARREL;	// Бочонок (с паузой игры)
	if (sFaceID == "DeadMan")	return	INTERFACETYPE_DEADMAN;	// Мертвец
	if (sFaceID == "Storage")	return	INTERFACETYPE_STORAGE;	// Ячейка ростовщика
	return INTERFACETYPE_EXCHANGE_ITEMS;
}

string sGetInterfaceTypeStr()
{
	string sRetStr = "";

	switch (iInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:	sRetStr = "titleExchangeItems";	break;
		case INTERFACETYPE_CHEST:			sRetStr = "titleItemsBox";		break;
		case INTERFACETYPE_BARREL:			sRetStr = "titleBarrel";		break;
		case INTERFACETYPE_DEADMAN:			sRetStr = "titleDeadItems";		break;
		case INTERFACETYPE_STORAGE:			sRetStr = "titleItemsBox";		break;
	}
	return sRetStr;
}

void SetCharactersMoneyOnExit() // Выставим деньги
{
	switch (iInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:    MakeMoneyFromGoldWithowtChest();    break;
		case INTERFACETYPE_CHEST:    MakeMoneyFromGoldWithChest(arChest);        break;
		case INTERFACETYPE_BARREL:    MakeMoneyFromGoldWithChest(arChest);        break;
		case INTERFACETYPE_DEADMAN:
			MakeMoneyFromGoldWithDeadMan(arDeadChar);
			if (CheckAttribute(&TEV, "DeadmanMoney") && sti(TEV.DeadmanMoney) > 0)
				pchar.money = sti(pchar.money) + sti(TEV.DeadmanMoney);
		break;
		case INTERFACETYPE_STORAGE:    MakeMoneyFromGoldWithowtChest();            break;
	}
}

void ShowItemsWeight()
{
	if (iInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS)
	{
		SetFormatedText("STORE_CAPACITY", XI_ConvertString("Weight") + ":" + NewStr() + FloatToString(GetItemsWeight(refToChar), 1) + " / " + GetMaxItemsWeight(refToChar));
	}
	else if (iInterfaceType == INTERFACETYPE_DEADMAN)
	{
		if (CheckAttribute(&arDeadChar, "name") && CheckAttribute(&arDeadChar, "lastname"))
		{
			SetFormatedText("STORE_CAPACITY", arDeadChar.name + " " + arDeadChar.lastname);
		}
		else if (CheckAttribute(&arDeadChar, "name"))
		{
			SetFormatedText("STORE_CAPACITY", arDeadChar.name);
		}
	}
	else if (iInterfaceType == INTERFACETYPE_STORAGE)
	{
		SetFormatedText("STORE_CAPACITY", XI_ConvertString("Weight") + ":" + NewStr() + FloatToString(GetItemsWeight(refToChar), 1) + " / 1000");
	}
	else
	{
		SetFormatedText("STORE_CAPACITY", "");
	}

	SetFormatedText("CAPACITY", XI_ConvertString("Weight") + ":" + NewStr() + FloatToString(GetItemsWeight(refCharacter), 1) + " / " + GetMaxItemsWeight(refCharacter));
}

void ProcessBreakExit()
{
	IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
}

void ProcessCancelExit()
{
	if (bShowChangeWin)    EndTooltip();
	else    IDoExit(RC_INTERFACE_FOOD_INFO_EXIT);
}

void IDoExit(int exitCode)
{
	ref arCurChar;
	string sCurArroyID, sGun;
	// boal проверка на перегруз 21.01.2004 -->
	CheckAndSetOverloadMode(GetMainCharacter());
	// boal 21.01.2004 <--
	SetCharactersMoneyOnExit(); // Переводим монеты "gold" в деньгиъ
	RefreshEquippedMaps(GetMainCharacter()); // рефрешим карты, если купили
	ref sld;

	if (!bBoxUsed)
	{
		for (int i = 0; i < INTERFACE_ITEMSBOX_CHAR_ARROYSIZE; i++)
		{
			sCurArroyID = sCharactersArroy[i];
			if (sCurArroyID != "")
			{
				arCurChar = CharacterFromID(sCurArroyID);
				if (IsMainCharacter(arCurChar)) continue;

				if (CheckAttribute(arCurChar, "skill.Fencing")) //boal fix иначе не берут саблю при перегрузе
				{
					if (GetCharacterSkill(arCurChar, "Fencing") > 0.1) // boal 08.10.04 броню офицерам
						EquipCharacterByItem(arCurChar, FindCharacterItemByGroup(arCurChar, CIRASS_ITEM_TYPE));

					EquipCharacterByItem(arCurChar, FindCharacterItemByGroup(arCurChar, BLADE_ITEM_TYPE));
				}

				if (CheckAttribute(arCurChar, "skill.Pistol") && GetCharacterSkill(arCurChar, "Pistol") > 0.1)
				{
					if (CheckAttribute(arCurChar, "MushForever"))
					{
						sGun = FindCharacterItemByGroup(arCurChar, MUSKET_ITEM_TYPE);
						SetCharacterToMushketer(arCurChar, sGun);
					}
					else
					{
						sGun = FindCharacterItemByGroup(arCurChar, GUN_ITEM_TYPE);
						EquipCharacterByItem(arCurChar, sGun);
					}
				}

				bool bOk = false;
				if (CheckAttribute(pchar, "MainQuest"))
				{
					bOk = pchar.MainQuest == "FL2_s22" || pchar.MainQuest == "FL2_s23";
				}
				if (CheckAttribute(arCurChar, "id") && arCurChar.id == "FL_DuranRimber" && bOk)
				{
					DoQuestCheckDelay("FL2_s24", 0.5);
				}
			}
		}
	}
	else
	{
		bMainCharacterInBox = false; // снимаем флаг 'в боксе'
	}

	// Для обыска трупов - если пуст, то убрать из выдачи (мы все равно его уже не сможем обыскать)
	if (iInterfaceType == INTERFACETYPE_DEADMAN)
	{
		aref arItems; makearef(arItems, refToChar.items);
		bool hasLoot = or(GetAttributesNum(arItems) > 0, CheckAttribute(refToChar, "money") && sti(refToChar.money) > 0);
		if (!hasLoot)
		{
			Dead_DelLoginedCharacter(refToChar);
		}
	}

	EndAboveForm(true);

	DelEventHandler("InterfaceBreak", "ProcessBreakExit");
	DelEventHandler("exitCancel", "ProcessCancelExit");
	DelEventHandler("ievnt_command", "ProcCommand");
	DelEventHandler("evntDoPostExit", "DoPostExit");

	DelEventHandler("OnTableClick", "OnTableClick");
	DelEventHandler("MouseRClickUP", "EndTooltip");
	DelEventHandler("ShowHelpHint", "ShowHelpHint");
	DelEventHandler("ShowItemInfo", "ShowItemInfo");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("frame", "ProcessFrame");
	DelEventHandler("TransactionOK", "TransactionOK");
	DelEventHandler("confirmChangeQTY_EDIT", "confirmChangeQTY_EDIT");
	DelEventHandler("ADD_ALL_BUTTON", "ADD_ALL_BUTTON");
	DelEventHandler("ADD_BUTTON", "ADD_BUTTON");
	DelEventHandler("REMOVE_BUTTON", "REMOVE_BUTTON");
	DelEventHandler("REMOVE_ALL_BUTTON", "REMOVE_ALL_BUTTON");

	DelEventHandler("eTabControlPress", "procTabChange"); // Событие смены закладки
	DelEventHandler("OnHeaderClick", "OnHeaderClick");

	interfaceResultCommand = exitCode;
	EndCancelInterface(true);

	LAi_SetPlayerType(PChar); // Возвращаем тип игрока

	// evganat - пасха
	if (!CheckAttribute(pchar, "questTemp.easter.checkskeleton"))
		EasterCheckSkeleton();

	if (CheckAttribute(&TEV, "LootCollector.Run"))
	{
		HideLootCollectorBox();

		if (!CheckAttribute(&TEV, "LootCollector.Tutor"))
		{
			TEV.LootCollector.Tutor = true;

			Log_Clear();
			Log_Info(XI_ConvertString("TrophiesHelper_4"));
			Log_Info(XI_ConvertString("TrophiesHelper_5"));

			PlayStereoSound("interface\notebook.wav");
		}
	}

	DeleteAttribute(&TEV, "LootCollector.Run");
	DeleteAttribute(&TEV, "BoxTransferItems");
	DeleteAttribute(&TEV, "DeadmanMoney");

	//HardCoffee чтобы заново не подбегать к сундуку
	SetEventHandler("Location_CharacterInLocator", "CharacterStillInLocator", 0);
}

void ProcCommand()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	switch (nodName)
	{
		case "TABLE_ADD_ALL_BUTTON":
			if (comName == "activate" || comName == "click")
				onTableAddAllBtnClick();
		break;

		case "TABLE_REMOVE_ALL_BUTTON":
			if (comName == "activate" || comName == "click")
				onTableRemoveAllBtnClick();
		break;

		case "QTY_OK_BUTTON":
			if (comName == "leftstep")            ADD_BUTTON();
			else if (comName == "rightstep")    REMOVE_BUTTON();
			else if (comName == "speedleft")    ADD_ALL_BUTTON();
			else if (comName == "speedright")    REMOVE_ALL_BUTTON();
		break;

		case "QTY_CANCEL_BUTTON":
			if (comName == "leftstep")            ADD_BUTTON();
			else if (comName == "rightstep")    REMOVE_BUTTON();
			else if (comName == "speedleft")    ADD_ALL_BUTTON();
			else if (comName == "speedright")    REMOVE_ALL_BUTTON();
		break;

		case "TABLE_LIST":
			if (comName == "leftstep")            ADD_BUTTON();
			else if (comName == "rightstep")    REMOVE_BUTTON();
			else if (comName == "speedleft")    ADD_ALL_BUTTON();
			else if (comName == "speedright")    REMOVE_ALL_BUTTON();
		break;

		case "GETALL_BUTTON":
			if (comName == "activate" || comName == "click")
				onGetAllBtnClick();
		break;

		case "TRANSFERALL_BUTTON":
			if (comName == "activate" || comName == "click")
			{
				if (LAi_boarding_process)
				{
					TEV.LootCollector.Transfer = true;
					FilterMode = 3;
					string sTemp = XI_ConvertString("TrophiesHelper_6");

					if (CheckAttribute(&TEV, "LootCollector.Mode") && sti(TEV.LootCollector.Mode) == 3)
						sTemp = XI_ConvertString("TrophiesHelper_7");

					PlayVoice("Yes_Cap_0");
					ProcessCancelExit();
					AddTimeToCurrent(0, 10 + (rand(15)));
					LootCollectorTransferItemsToShip(true);
					SetLaunchFrameFormParam(sTemp + XI_ConvertString("TrophiesHelper_8"), "", 0, 4);
					LAi_MethodDelay("LaunchFrameForm", 0.1);
				}
			}
		break;

		//navy --> Убрать тело
		case "DELBODY_BUTTON":
			if (comName == "downstep" && GetSelectable("SKULL_BUTTON"))
			{
				SetCurrentNode("SKULL_BUTTON");
			}

			if (comName == "activate" || comName == "click")
			{
				if (CheckAttribute(refToChar, "money") && sti(refToChar.money) > 0)
					TEV.DeadmanMoney = sti(refToChar.money);
				Dead_DelLoginedCharacter(refToChar);
				ProcessCancelExit();
			}
		break;
		//navy <--

		case "SKULL_BUTTON":
			if (comName == "upstep")
			{
				SetCurrentNode("DELBODY_BUTTON");
			}

			if (comName == "activate" || comName == "click")
			{
				SetNPCQuestDate(refCharacter, "AztecSkull"); //запомним день

				// KZ > сохраняем предметы и деньги убитого офицера
				DeleteAttribute(&TEV, "Reincarnation");
				TEV.Reincarnation.Items = "";
				TEV.Reincarnation.Money = "";

				aref arToChar, arFromChar;

				makearef(arFromChar, refToChar.items);
				makearef(arToChar, TEV.Reincarnation.Items);
				CopyAttributes(arToChar, arFromChar);

				makearef(arFromChar, refToChar.items.gold);
				makearef(arToChar, TEV.Reincarnation.Money);
				CopyAttributes(arToChar, arFromChar);
				// <

				OfficerReincarnation(&characters[sti(refToChar.index)]);
				Dead_DelLoginedCharacter(refToChar);
				ProcessCancelExit();
			}
		break;
	}
}

void procTabChange()
{
	int comIndex = GetEventData();
	string nodName = GetEventData();
	SetCurrentNode("TABLE_LIST");

	switch (nodName)
	{
		case "TABBTN_1":    SetControlsTabMode(1);    break;
		case "TABBTN_2":    SetControlsTabMode(2);    break;
		case "TABBTN_3":    SetControlsTabMode(3);    break;
		case "TABBTN_4":    SetControlsTabMode(4);    break;
		case "TABBTN_5":    SetControlsTabMode(5);    break;
	}
	return;
}

void SetControlsTabMode(int nMode)
{
	int iColor1 = argb(255, 196, 196, 196);
	int iColor2 = iColor1;
	int iColor3 = iColor1;
	int iColor4 = iColor1;
	int iColor5 = iColor1;

	string sPic1 = "TabSelected";
	string sPic2 = sPic1;
	string sPic3 = sPic1;
	string sPic4 = sPic1;
	string sPic5 = sPic1;

	switch (nMode)
	{
		case 1:
			sPic1 = "TabDeSelected";
			iColor1 = argb(255, 255, 255, 255);
		break;

		case 2:
			sPic2 = "TabDeSelected";
			iColor2 = argb(255, 255, 255, 255);
		break;

		case 3:
			sPic3 = "TabDeSelected";
			iColor3 = argb(255, 255, 255, 255);
		break;

		case 4:
			sPic4 = "TabDeSelected";
			iColor4 = argb(255, 255, 255, 255);
		break;

		case 5:
			sPic5 = "TabDeSelected";
			iColor5 = argb(255, 255, 255, 255);
		break;
	}

	// Выставим таблицу в начало
	GameInterface.TABLE_LIST.select = 1;
	GameInterface.TABLE_LIST.top = 0;

	// Сбросим позицию стрелок
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY - 12, iTableAddAllBtnX + 30, iTableAddAllBtnY + 22, 0);
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY - 12, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 22, 0);

	SetNewGroupPicture("TABBTN_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS", sPic2);
	SetNewGroupPicture("TABBTN_3", "TABS", sPic3);
	SetNewGroupPicture("TABBTN_4", "TABS", sPic4);
	SetNewGroupPicture("TABBTN_5", "TABS", sPic5);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_1", 8, 0, iColor1);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_2", 8, 0, iColor2);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_3", 8, 0, iColor3);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_4", 8, 0, iColor4);
	SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, "TABSTR_5", 8, 0, iColor5);
	FillControlsList(nMode);
}

void FillControlsList(int nMode)
{
	switch (nMode)
	{
		case 1: FilterMode = 1; break;  // все предметы
		case 2: FilterMode = 2; break;  // предметы героя
		case 3: FilterMode = 3; break;  // предметы - в сундуке, в бочонке, у офицера, на трупе
		case 4: FilterMode = 4; break;  // снаряжение
		case 5: FilterMode = 5; break;  // зелья
	}
	sortColumnIdx = -1;
	AddToTable(refToChar, FilterMode);
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.tr1.index)); // Hokkins: при смене вкладки возвращаем информацию о предмете на первую строку.
}

void DoPostExit()
{
	int exitCode = GetEventData();
	IDoExit(exitCode);
}

void FillCharactersScroll()
{
	int i, _curCharIdx;
	string attributeName;
	bool bOfficer, bOk = false;
	bool bCabin = Pchar.SystemInfo.CabinType == pchar.location;
	string sCharID = "";
	int nListSize = 1;
	ref chr;
	DeleteAttribute(&GameInterface, "CHARACTERS_SCROLL");

	nCurScrollNum = -1;
	GameInterface.CHARACTERS_SCROLL.current = 0;

	GameInterface.CHARACTERS_SCROLL.NotUsed = 6;

	GameInterface.CHARACTERS_SCROLL.ImagesGroup.t0 = "EMPTYFACE";
	GameInterface.CHARACTERS_SCROLL.ImagesGroup.t1 = "BOX_IMAGE";

	FillFaceList("CHARACTERS_SCROLL.ImagesGroup", pchar, 2); // passengers

	GameInterface.CHARACTERS_SCROLL.BadTex1 = 0;
	GameInterface.CHARACTERS_SCROLL.BadPic1 = "emptyface";
	GameInterface.CHARACTERS_SCROLL.BadTex2 = 0;
	GameInterface.CHARACTERS_SCROLL.BadPic2 = "BOX_IMAGE";

	if (iInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS) // При обмене предметами с офом первая картинка - собсно офф
	{
		sCharID = refToChar.ID;
		int iCharIDX = GetCharacterIndex(sCharID);

		attributeName = "pic" + (nListSize);

		if (CheckAttribute(refToChar, "Tasks.Clone")) //HardCoffee обмен с компаньоном фикс портрета
			AddFaceGroup("CHARACTERS_SCROLL.ImagesGroup", "FACE128_" + refToChar.faceID);

		SetCharacterMoneyToGold(refToChar);
		iSetCharIDToCharactersArroy(refToChar); // Пометим его для удаления золота и дачи денег
		GameInterface.CHARACTERS_SCROLL.(attributeName).character = refToChar.index;
		GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(refToChar);
		GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup", "FACE128_" + refToChar.FaceID);
	}
	else
	{
		attributeName = "pic" + (nListSize);
		GameInterface.CHARACTERS_SCROLL.(attributeName).character = nMainCharacterIndex;
		GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(pchar);
		GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup", "FACE128_" + pchar.FaceID);
	}

	for (i = 0; i < GetPassengersQuantity(pchar); i++)
	{
		_curCharIdx = GetPassenger(pchar, i);
		if (_curCharIdx < 0) continue;
		chr = &characters[_curCharIdx];
		if (sCharID == chr.ID) continue;
		if (CheckAttribute(chr, "prisoned") && sti(chr.prisoned)) continue;
		if (CheckAttribute(chr, "isquest") || CheckAttribute(chr, "NonRemovable")) continue;
		bOfficer = IsOfficer(chr);
		if (CheckFighters(chr)) bOk = bOfficer;
		//HardCoffee возможность для абордажников залезть в сундук каюты, даже если они не в каюте
		else if (bOfficer && bCabin) bOk = true;
		// boal // fix - ГГ и офы должны быть в одной локации // KZ > фикс фикса
		else bOk = bOfficer && IsEntity(chr) && PChar.location == chr.location && !GetBan("Exchange");
		if (!bOk) continue;
		SetCharacterMoneyToGold(chr);
		iSetCharIDToCharactersArroy(chr); // Пометим его для удаления золота и дачи денег
		nListSize++;
		attributeName = "pic" + (nListSize);
		GameInterface.CHARACTERS_SCROLL.(attributeName).character = _curCharIdx;
		GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(chr);
		GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup", "FACE128_" + chr.FaceID);
	}
	//HardCoffee возможность приглашённым компаньонам залезть в сундук каюты
	if (bCabin)
	{
		rCabin = &locations[FindLocation(Get_My_Cabin())];
		for (i = 0; i < COMPANION_MAX; i++)
		{
			_curCharIdx = GetCompanionIndex(PChar, i);
			if (_curCharIdx < 0) continue;
			chr = &characters[_curCharIdx];
			if (!CheckAttribute(chr, "Tasks.Clone")) continue;

			_curCharIdx = sti(chr.Tasks.Clone);
			if (_curCharIdx < 0) continue;
			if (sCharID == chr.ID) continue;

			AddFaceGroup("CHARACTERS_SCROLL.ImagesGroup", "FACE128_" + chr.faceID);
			SetCharacterMoneyToGold(chr);
			iSetCharIDToCharactersArroy(chr);
			nListSize++;
			attributeName = "pic" + (nListSize);
			GameInterface.CHARACTERS_SCROLL.(attributeName).character = chr.index;
			GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = GetFacePicName(chr);
			GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup", "FACE128_" + chr.FaceID);

		}
		//раскомментить для отображения всех сундуков в каюте
		/*if (iInterfacetype == INTERFACETYPE_CHEST)
		{
			i = 1;
			while (true)
			{
				if (CheckAttribute(rCabin, "box" + i))
				{
					if (GetAttributeName(refToChar) == ("box" + i))
					{
						i++;
						continue;
					}
					nListSize++;
					attributeName = "pic" + nListSize;
					GameInterface.CHARACTERS_SCROLL.(attributeName).character = "box" + i;
					GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = "BoxImage";
					GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup", "EMPTYFACE");
					GameInterface.CHARACTERS_SCROLL.(attributeName).img2 = "BoxImage";
					GameInterface.CHARACTERS_SCROLL.(attributeName).tex2 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup", "BOX_IMAGE");
				}
				else break;
				i++;
			}
			bChestEnable = false;
		}*/
	}

	if (bChestEnable)
	{
		chr = GetRealShip(sti(pchar.ship.type));

		i = FindLocation("My_Deck");

		if (sti(chr.Class) < 7 && i >= 0)
		{
			rHold = &locations[i];

			if (CheckAttribute(rHold, "box1") && sti(rHold.box1) > 0)
			{
				nListSize++;
				attributeName = "pic" + nListSize;
				GameInterface.CHARACTERS_SCROLL.(attributeName).character = "Hold|box1";
				GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = "BoxImage";
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup", "EMPTYFACE");
				GameInterface.CHARACTERS_SCROLL.(attributeName).img2 = "BoxImage";
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex2 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup", "BOX_IMAGE");
				
			}
		}

		i = 1;
		while (true)
		{
			if (CheckAttribute(rCabin, "box" + i))
			{
				nListSize++;
				attributeName = "pic" + nListSize;
				GameInterface.CHARACTERS_SCROLL.(attributeName).character = "Cabin|box" + i;
				GameInterface.CHARACTERS_SCROLL.(attributeName).img1 = "BoxImage";
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex1 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup", "EMPTYFACE");
				GameInterface.CHARACTERS_SCROLL.(attributeName).img2 = "BoxImage";
				GameInterface.CHARACTERS_SCROLL.(attributeName).tex2 = FindFaceGroupNum("CHARACTERS_SCROLL.ImagesGroup", "BOX_IMAGE");
			}
			else break;
			i++;
		}
	}
	//Закомментть для прокрутки по кругу
	GameInterface.CHARACTERS_SCROLL.ListSize = nListSize+1;
}

void AddToTable(ref rChar, int _mode)
{
	string sList, sItem;
	string groupID, itemType;
	int i, iLeftQty, iRightQty, Index, iSelLine, n = 1;
	ref rItem;
	bool ok, ok1, ok2, ok3 = false;

	// Warship fix 31.05.09 - слетала текущая полоска + кнопочки забрать/отдать все
	// Садо-мазо получилось ещё то
	ok = FilterMode == 2 || FilterMode == 3; // Долбаный шторм не понимает И и ИЛИ в одном выражении, даж со скобками
	if (ok && iLinesCount > 2)
	{
		if (sti(GameInterface.TABLE_LIST.select) + 1 == iLinesCount)
		{
			iLinesCount -= 2;
			GameInterface.TABLE_LIST.select = iLinesCount;

			iSelLine = iLinesCount;

			if (CheckAttribute(&GameInterface, "TABLE_LIST.top"))
			{
				if (sti(GameInterface.TABLE_LIST.top) > 0)
				{
					GameInterface.TABLE_LIST.top = sti(GameInterface.TABLE_LIST.top) - 1;
				}

				iSelLine = iLinesCount - sti(GameInterface.TABLE_LIST.top);
			}

			SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY - 12 + 42 * (iSelLine - 1), iTableAddAllBtnX + 30, iTableAddAllBtnY - 8 + 42 * (iSelLine - 1) + 30, 0);
			SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY - 12 + 42 * (iSelLine - 1), iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY - 8 + 42 * (iSelLine - 1) + 30, 0);

			sList = "tr" + sti(GameInterface.TABLE_LIST.select);
			iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(sList).index);
			ShowGoodsInfo(iCurGoodsIdx);
		}
		else
		{
			GameInterface.TABLE_LIST.select = sti(GameInterface.TABLE_LIST.select) + 1;

			ok3 = true; // См. ниже проверку if(ok3) - бред-бредом конечно, но по-другому не получается
		}
	}

	iLinesCount = 1;

	Table_Clear("TABLE_LIST", false, true, false);

	iLeftQty = GetCharacterFreeItem(refCharacter, "Gold");
	iRightQty = GetCharacterFreeItem(rChar, "Gold");

	// Фикс - должно быть всегда, иначе у нищих офов слетает стрелочки
	//if(iLeftQty > 0 || iRightQty > 0)
	//{
	sList = "tr" + n;
	Index = FindItem("Gold");
	rItem = &Items[Index];
	sItem = rItem.id;
	GameInterface.TABLE_LIST.(sList).index = Index;
	GameInterface.TABLE_LIST.(sList).td1.str = iLeftQty;
	GameInterface.TABLE_LIST.(sList).td2.str = "-";
	GameInterface.TABLE_LIST.(sList).td3.icon.group = rItem.picTexture;
	GameInterface.TABLE_LIST.(sList).td3.icon.image = "itm" + rItem.picIndex;
	GameInterface.TABLE_LIST.(sList).td3.icon.offset = "0, 1";
	GameInterface.TABLE_LIST.(sList).td3.icon.width = 39;
	GameInterface.TABLE_LIST.(sList).td3.icon.height = 39;
	GameInterface.TABLE_LIST.(sList).td3.textoffset = "60, 0";
	GameInterface.TABLE_LIST.(sList).td3.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
	GameInterface.TABLE_LIST.(sList).td4.str = "-";
	GameInterface.TABLE_LIST.(sList).td5.str = iRightQty;
	n++;

	iLinesCount++;
	//}

	// Сначало заполняем рандомящимся оружием
	for (i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		sList = "tr" + n;
		rItem = &Items[i];

		if (!CheckAttribute(rItem, "ID"))
		{
			continue;
		}

		sItem = rItem.id;
		groupID = "";
		itemType = "";

		if (sItem == "Gold") continue; // Золото выше

		// evganat - энциклопедия
		if (sItem == "encyclopedia") continue;

		// Hokkins: новая сортировка предметов -->
		if (CheckAttribute(rItem, "groupID")) groupID = rItem.groupID;
		if (CheckAttribute(rItem, "itemType")) itemType = rItem.itemType;

		// Проверка на экипировку
		iLeftQty = GetCharacterFreeItem(refCharacter, sItem);
		iRightQty = GetCharacterFreeItem(rChar, sItem);

		// Снаряжение -->
		ok1 = (groupID == BLADE_ITEM_TYPE)    || // холодное оружие
              (groupID == GUN_ITEM_TYPE)      || // пистолеты
              (groupID == MUSKET_ITEM_TYPE)   || // ружья
              (groupID == SPYGLASS_ITEM_TYPE) || // подзорные трубы
              (groupID == CIRASS_ITEM_TYPE)   || // костюмы и доспехи
              (groupID == AMMO_ITEM_TYPE);       // боеприпасы

		// Зелья -->
		ok2 = (groupID == POTION_ITEM_TYPE);    // зелья

		if (iLeftQty > 0 || iRightQty > 0)
		{
			if (FilterMode == 2 && iLeftQty < 1) continue;     // Сортировка "у героя"
			if (FilterMode == 3 && iRightQty < 1) continue;    // Сортировка "в сундуке"
			if (FilterMode == 4 && !ok1) continue;             // Сортировка "cнаряжение"
			if (FilterMode == 5 && !ok2) continue;             // Сортировка "зелья"

			GameInterface.TABLE_LIST.(sList).index = i;
			GameInterface.TABLE_LIST.(sList).td1.str = iLeftQty;
			GameInterface.TABLE_LIST.(sList).td2.str = FloatToString(stf(rItem.Weight) * iLeftQty, 1);
			GameInterface.TABLE_LIST.(sList).td3.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST.(sList).td3.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST.(sList).td3.icon.offset = "0, 1";
			GameInterface.TABLE_LIST.(sList).td3.icon.width = 39;
			GameInterface.TABLE_LIST.(sList).td3.icon.height = 39;
			GameInterface.TABLE_LIST.(sList).td3.textoffset = "60, 0";
			GameInterface.TABLE_LIST.(sList).td3.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			GameInterface.TABLE_LIST.(sList).td4.str = FloatToString(stf(rItem.Weight) * iRightQty, 1);
			GameInterface.TABLE_LIST.(sList).td5.str = iRightQty;
			n++;

			iLinesCount++;
		}
	}

	for (i = 0; i < ITEMS_QUANTITY; i++)
	{
		sList = "tr" + n;
		rItem = &Items[i];
		sItem = rItem.id;
		groupID = "";
		itemType = "";

		if (sItem == "Gold") continue; // Золото выше
		if (sItem == "unarmed") continue; //HardCoffee кулаки не отображать
		// Hokkins: новая сортировка предметов -->
		if (CheckAttribute(rItem, "groupID")) groupID = rItem.groupID;
		if (CheckAttribute(rItem, "itemType")) itemType = rItem.itemType;

		// Проверка на экипировку
		iLeftQty = GetCharacterFreeItem(refCharacter, sItem);
		iRightQty = GetCharacterFreeItem(rChar, sItem);

		// Снаряжение -->
		ok1 = (groupID == BLADE_ITEM_TYPE)    || // холодное оружие
              (groupID == GUN_ITEM_TYPE)      || // пистолеты
              (groupID == MUSKET_ITEM_TYPE)   || // ружья
              (groupID == SPYGLASS_ITEM_TYPE) || // подзорные трубы
              (groupID == CIRASS_ITEM_TYPE)   || // костюмы и доспехи
              (groupID == AMMO_ITEM_TYPE);       // боеприпасы

		// Зелья -->
		ok2 = (groupID == POTION_ITEM_TYPE);    // зелья

		if (iLeftQty > 0 || iRightQty > 0)
		{
			if (FilterMode == 2 && iLeftQty < 1) continue; // Сортировка "у героя"
			if (FilterMode == 3 && iRightQty < 1) continue; // Сортировка "в сундуке"
			if (FilterMode == 4 && !ok1) continue; // Сортировка "cнаряжение"
			if (FilterMode == 5 && !ok2) continue; // Сортировка "зелья"

			GameInterface.TABLE_LIST.(sList).index = i;
			GameInterface.TABLE_LIST.(sList).td1.str = iLeftQty;
			GameInterface.TABLE_LIST.(sList).td2.str = FloatToString(stf(rItem.Weight) * iLeftQty, 1);
			GameInterface.TABLE_LIST.(sList).td3.icon.group = rItem.picTexture;
			GameInterface.TABLE_LIST.(sList).td3.icon.image = "itm" + rItem.picIndex;
			GameInterface.TABLE_LIST.(sList).td3.icon.offset = "0, 1";
			GameInterface.TABLE_LIST.(sList).td3.icon.width = 39;
			GameInterface.TABLE_LIST.(sList).td3.icon.height = 39;
			GameInterface.TABLE_LIST.(sList).td3.textoffset = "60, 0";
			GameInterface.TABLE_LIST.(sList).td3.str = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			GameInterface.TABLE_LIST.(sList).td4.str = FloatToString(stf(rItem.Weight) * iRightQty, 1);
			GameInterface.TABLE_LIST.(sList).td5.str = iRightQty;
			n++;

			iLinesCount++;
		}
	}

	if (ok3)
	{
		GameInterface.TABLE_LIST.select = sti(GameInterface.TABLE_LIST.select) - 1;
		sList = "tr" + sti(GameInterface.TABLE_LIST.select);

		// Warship 10.07.09 fix - Могло не быть, при сбрасывании в начало при переключении персонажей
		if (CheckAttribute(&GameInterface, "TABLE_LIST." + sList + ".index"))
		{
			iCurGoodsIdx = sti(GameInterface.TABLE_LIST.(sList).index);
			ShowGoodsInfo(iCurGoodsIdx);
		}
	}

	Table_UpdateWindow("TABLE_LIST");
	SetEventHandler("frame", "RefreshTableByFrameEvent", 0);
}

void RefreshTableByFrameEvent()
{
	DelEventHandler("frame", "RefreshTableByFrameEvent");
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "TABLE_LIST", 0);
	int column = sortColumnIdx;
	if (column >= 0)
	{
		SortTradeList(column, true, "TABLE_LIST"); // сортируем список если уже стояла сортировка
	    SetCurrentNode("TABLE_LIST");
	    SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_LIST", 2, sti(GameInterface.TABLE_LIST.select)-1);
	}
}

void OnTableClick()
{
	string sControl = GetEventData();
	int iRow = GetEventData();
	int iColumn = GetEventData();

	string sRow = "tr" + (iRow + 1);
	Table_UpdateWindow(sControl);
}

void ChangePosTable()
{

}

void ShowHelpHint()
{
	string sHeader;
	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	if (!bShowChangeWin) // покажем помощь по работе с формой
	{
		sHeader = XI_ConvertString("titleItemsTrade");
		sText1 = XI_ConvertString("ItemsHelper_5") + newStr() +
				XI_ConvertString("ItemsHelper_6") + newStr() +
					XI_ConvertString("ItemsHelper_7") + newStr() +
						XI_ConvertString("ItemsHelper_8") + newStr() +
							XI_ConvertString("ItemsHelper_9");

		sText3 = XI_ConvertString("ItemsHelper_10");
		sText2 = XI_ConvertString("ItemsHelper_11");

		CreateTooltip("#" + sHeader, sText1, argb(255, 255, 255, 255), sText2, argb(255, 192, 192, 192), sText3, argb(255, 255, 255, 255), "", argb(255, 255, 255, 255), sPicture, sGroup, sGroupPicture, 64, 64);
	}
}

void EndTooltip()
{
	CloseTooltip(); // всегда убирать, если был
	GameInterface.qty_edit.str = 0;
	SetCharWeight();
	SetVariable();
	SetCurrentNode("TABLE_LIST");
	XI_WindowDisable("QTY_WINDOW", true);
	XI_WindowShow("QTY_WINDOW", false);
	bShowChangeWin = false;
}

void ShowItemInfo()
{
	if (bShowChangeWin) // жмем окей, когда курсор на таблице
	{
		TransactionOK();
	}
	else
	{
		GameInterface.qty_edit.str = "0";
		BuyOrSell = 0;
		ChangeQTY_EDIT();

		XI_WindowDisable("QTY_WINDOW", false);
		XI_WindowShow("QTY_WINDOW", true);
		bShowChangeWin = true;
	}
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	int iSelected = GetEventData();
	int iCol = GetEventData();

	// Warship 26.04.09 fix - при прокрутке можго вылазить за экран, неправильно определялась текущая линия
	int iSelLine = iSelected;

	if (CheckAttribute(&GameInterface, "TABLE_LIST.top"))
	{
		iSelLine = iSelected - sti(GameInterface.TABLE_LIST.top);
	}

	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY - 12 + 42 * (iSelLine - 1), iTableAddAllBtnX + 30, iTableAddAllBtnY - 8 + 42 * (iSelLine - 1) + 30, 0);
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY - 12 + 42 * (iSelLine - 1), iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY - 8 + 42 * (iSelLine - 1) + 30, 0);

	string sList = "tr" + iSelected;
	SetCharWeight();
	SetVariable();
	ShowGoodsInfo(sti(GameInterface.TABLE_LIST.(sList).index));
}

void SetVariable()
{
	string sText, sTextSecond;

	iCharCapacity = GetMaxItemsWeight(refCharacter);
	sText = FloatToString(fCharWeight, 1) + " / " + iCharCapacity;
	ShowItemsWeight(); // Переделка
}

void ProcessFrame()
{
	aref arCurCharFromImage;
	if (sti(GameInterface.CHARACTERS_SCROLL.current) != nCurScrollNum && GetCurrentNode() == "CHARACTERS_SCROLL")
	{
		XI_WindowDisable("QTY_WINDOW", true);
		XI_WindowShow("QTY_WINDOW", false);
		nCurScrollNum = sti(GameInterface.CHARACTERS_SCROLL.current);
		string sAttr = "pic" + (nCurScrollNum + 1);
		int iCurCharImageIndex = sti(GameInterface.CHARACTERS_SCROLL.(sAttr).character);

		switch (iInterfaceType)
		{
			case INTERFACETYPE_EXCHANGE_ITEMS:
				makearef(refToChar, characters[iCurCharImageIndex]);
			break;

			case INTERFACETYPE_CHEST:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;

			case INTERFACETYPE_BARREL:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;

			case INTERFACETYPE_DEADMAN:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;

			case INTERFACETYPE_STORAGE:
				makeref(refCharacter, characters[iCurCharImageIndex]);
			break;
		}

		FillCharactersImages();
		SetDescription();
		AddToTable(refToChar, FilterMode);
		GameInterface.TABLE_LIST.select = 1;
		GameInterface.TABLE_LIST.top = 0;

		// Стрлочки на первую позицию
		SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY - 12, iTableAddAllBtnX + 30, iTableAddAllBtnY + 22, 0);
		SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY - 12, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 22, 0);
	}
}

void FillCharactersImages()
{
	string sAttr = "pic" + (sti(GameInterface.CHARACTERS_SCROLL.current) + 1);
	string sTemp, sName = GameInterface.CHARACTERS_SCROLL.(sAttr).character;

	if (bChestEnable && HasStr(sName, "|box"))
	{
		sTemp = FindStringAfterSubStr(sName, "|");

		if (StrStartsWith(sName, "Hold|"))
			makearef(arBox, rHold.(sTemp));
		else			
			makearef(arBox, rCabin.(sTemp));

		makeref(refCharacter, arBox);

		SetFormatedText("TABSTR_2", XI_ConvertString("Item_CHEST"));
		SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\BoxImage.tga");
		GameInterface.strings.CharName = XI_ConvertString("Item_CHEST_IN_" + FindStringBeforeSubStr(sName, "|")) + " " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(pchar.Ship.Type)].BaseName + "Acc")) + " '" + pchar.ship.name + "'";
	}
	else
	{
		if (CheckAttribute(refCharacter, "sex") && refCharacter.sex == "woman")
			SetFormatedText("TABSTR_2", XI_ConvertString("Item_CHARACTERF"));
		else
			SetFormatedText("TABSTR_2", XI_ConvertString("Item_CHARACTER"));
		SetNewPicture("MAIN_CHARACTER_PICTURE", "interfaces\portraits\128\face_" + refCharacter.FaceId + ".tga");
		ref rChr = &Characters[sti(sName)];
		GameInterface.strings.CharName = GetFullNameTitulForm(rChr) +" " +GetOfficerOccupation(rChr);
	}
	SetVAligmentFormatedText("TABSTR_2");

	switch (iInterfaceType)
	{
		case INTERFACETYPE_EXCHANGE_ITEMS:
			SetNewPicture("OTHER_PICTURE", "interfaces\portraits\128\face_" + refToChar.FaceId + ".tga");
		break;

		case INTERFACETYPE_CHEST:
			SetNewPicture("OTHER_PICTURE", "interfaces\Search.tga");
		break;

		case INTERFACETYPE_BARREL:
			SetNewGroupPicture("OTHER_PICTURE", "BARREL_IMAGE", "BarrelImage");
		break;

		case INTERFACETYPE_DEADMAN:
			SetNewPicture("OTHER_PICTURE", "interfaces\Corpse.tga");
		break;

		case INTERFACETYPE_STORAGE:
			SetNewPicture("OTHER_PICTURE", "interfaces\store.tga");
		break;
	}
}

void SetDescription()
{
	SetVariable();
}

void SetCharWeight()
{
	fCharWeight = GetItemsWeight(refCharacter);
	fStoreWeight = GetItemsWeight(refToChar);
}

// Жмакнули по кнопке "взять все"
void onGetAllBtnClick()
{
	int iItemsQty;
	string itemID;

	int maxItemsToAdd;
	float weight;
	bool bOk = false;
	SetCharWeight();

	for (int i = 0; i < TOTAL_ITEMS; i++)
	{
		if (CheckAttribute(&Items[i], "ID"))
		{
			itemID = Items[i].id;
			iItemsQty = GetCharacterFreeItem(refToChar, itemID);
			if (iItemsQty < 1) continue;

			if (itemID == "mushket2x2" && iInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS && refToChar.id == "Douglas")
				continue; // Руки прочь от мушкета!

			// Учет перегруза -->
			maxItemsToAdd = GetMaxItemsToTake(true, itemID);

			if (maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;
			// <-- Учет перегруза

			if (iItemsQty < 1) continue;

			RemoveItems(refToChar, itemID, iItemsQty);
			AddItems(refCharacter, itemID, iItemsQty);

			bOk = true;

			weight = iItemsQty * stf(Items[i].weight);
			fCharWeight += weight; // Тут обновляем для метода GetMaxItemsToTake, иначе тормоза
			fStoreWeight -= weight;
		}
	}

	if (bOk) WaitDate("", 0, 0, 0, 0, 1);

	// Warship fix 10.06.09 -->
	// Обновление текущего веса и т.д.
	SetCharWeight();
	SetVariable();

	GameInterface.TABLE_LIST.top = 0;
	GameInterface.TABLE_LIST.select = 1;

	iCurGoodsIdx = sti(GameInterface.TABLE_LIST.tr1.index);
	ShowGoodsInfo(iCurGoodsIdx);

	AddToTable(refToChar, FilterMode); // Рефрешь таблицы
	// Рефреш позиции стрелочек
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_ADD_ALL_BUTTON", 0, iTableAddAllBtnX, iTableAddAllBtnY - 12, iTableAddAllBtnX + 30, iTableAddAllBtnY + 22, 0);
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_REMOVE_ALL_BUTTON", 0, iTableRemoveAllBtnX, iTableRemoveAllBtnY - 12, iTableRemoveAllBtnX + 30, iTableRemoveAllBtnY + 22, 0);
	// <-- Warship fix 10.06.09
}

// Нажали на табличной стрелочке "взять все предметы одного типа"
void onTableAddAllBtnClick()
{
	string item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(refToChar, item);

	if (item == "mushket2x2" && iInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS && refToChar.id == "Douglas")
		return; // Руки прочь от мушкета!

	// Учет перегруза
	int maxItemsToAdd = GetMaxItemsToTake(true, item);

	if (maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;

	if (iItemsQty > 0) // fix
	{
		RemoveItems(refToChar, item, iItemsQty);
		AddItems(refCharacter, item, iItemsQty);
		WaitDate("", 0, 0, 0, 0, 1);

		AddToTable(refToChar, FilterMode);

		// Обновление текущего веса и т.д.
		SetCharWeight();
		SetVariable();

		iCharQty = GetCharacterFreeItem(refCharacter, item);
		iStoreQty = GetCharacterFreeItem(refToChar, item);
	}
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
}

// Нажали на табличной стрелочке "отдать все предметы одного типа"
void onTableRemoveAllBtnClick()
{
	string item = Items[iCurGoodsIdx].id;
	int iItemsQty = GetCharacterFreeItem(refCharacter, item);

	if (IsQuestUsedItem(item) && item != "Gold") return; // Квестовые не отдать, только золото

	// Учет перегруза (в сундуки и трупы можно ложить сколько угодно)
	int maxItemsToAdd = GetMaxItemsToTake(false, item);

	if (maxItemsToAdd < iItemsQty) iItemsQty = maxItemsToAdd;

	if (iItemsQty > 0) // fix
	{
		RemoveItems(refCharacter, item, iItemsQty);
		AddItems(refToChar, item, iItemsQty);
		WaitDate("", 0, 0, 0, 0, 1);

		AddToTable(refToChar, FilterMode);

		// Обновление текущего веса и т.д.
		SetCharWeight();
		SetVariable();

		iCharQty = GetCharacterFreeItem(refCharacter, item);
		iStoreQty = GetCharacterFreeItem(refToChar, item);
	}
	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
}

// инфа о предмете
void ShowGoodsInfo(int iGoodIndex)
{
	string GoodName = Items[iGoodIndex].name;
	ref arItm = &Items[iGoodIndex];
	string sHeader = GetConvertStr(GoodName, "ItemsDescribe.txt");

	iCurGoodsIdx = iGoodIndex;
	string describeStr = "";

	if (bBettaTestMode)
	{
		describeStr += "id = " + Items[iGoodIndex].id + NewStr();
	}
	describeStr += GetItemDescribe(iGoodIndex);

	fWeight = stf(Items[iGoodIndex].weight);

	BuyOrSell = 0;
	SetFormatedText("QTY_TypeOperation", "");
	GameInterface.qty_edit.str = "0";

	SetNewGroupPicture("QTY_GOODS_PICTURE", Items[iCurGoodsIdx].picTexture, "itm" + Items[iCurGoodsIdx].picIndex);
	SetFormatedText("QTY_CAPTION", sHeader);
	SetFormatedText("QTY_GOODS_INFO", describeStr);

	iCharQty = GetCharacterFreeItem(refCharacter, Items[iGoodIndex].id);
	iStoreQty = GetCharacterFreeItem(refToChar, Items[iGoodIndex].id);

	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty));
	BuyOrSell = 0;
}

void TransactionOK()
{
	int nTradeQuantity;
	string list;
	confirmChangeQTY_EDIT();
	nTradeQuantity = sti(GameInterface.qty_edit.str);
	if (BuyOrSell == 0)
	{
		EndTooltip();
		return;
	}

	if (BuyOrSell == 1) // Забираем
	{
		RemoveItems(refToChar, Items[iCurGoodsIdx].id, nTradeQuantity);
		AddItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
		WaitDate("", 0, 0, 0, 0, 1);
	}
	else // Отдаем
	{
		AddItems(refToChar, Items[iCurGoodsIdx].id, nTradeQuantity);
		RemoveItems(refCharacter, Items[iCurGoodsIdx].id, nTradeQuantity);
		WaitDate("", 0, 0, 0, 0, 1);
	}

	AddToTable(refToChar, FilterMode);
	EndTooltip();

	ShowGoodsInfo(iCurGoodsIdx); //сбросим все состояния
}

void confirmChangeQTY_EDIT()
{
	ChangeQTY_EDIT();
	SetCurrentNode("QTY_OK_BUTTON");
}

void ChangeQTY_EDIT()
{
	float iWeight;
	float fRefCharWeight, fRefCharMaxWeight;

	SetCharWeight();
	GameInterface.qty_edit.str = sti(GameInterface.qty_edit.str);
	if (sti(GameInterface.qty_edit.str) == 0)
	{
		SetFormatedText("QTY_TypeOperation", "");
		BuyOrSell = 0;
	}
	else
	{
		if (sti(GameInterface.qty_edit.str) < 0 || BuyOrSell == -1)
		{
			if (BuyOrSell != -1)
			{
				GameInterface.qty_edit.str = -sti(GameInterface.qty_edit.str);
			}

			BuyOrSell = -1;

			// проверка на колво доступное -->
			if (sti(GameInterface.qty_edit.str) > iCharQty)
			{
				GameInterface.qty_edit.str = iCharQty;
			}
			// Сундуки, бочки и трупы бездонны, а для остальных -->
			if (iInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS || iInterfaceType == INTERFACETYPE_STORAGE)
			{
				fRefCharWeight = GetItemsWeight(refToChar);
				if (iInterfaceType == INTERFACETYPE_STORAGE) fRefCharMaxWeight = 1000.0;
				else fRefCharMaxWeight = GetMaxItemsWeight(refToChar);
				iWeight = (fWeight * sti(GameInterface.qty_edit.str));
				if ((fRefCharWeight + iWeight) > fRefCharMaxWeight)
				{
					iWeight = fRefCharMaxWeight - fRefCharWeight - 0.01; // чуть меньше

					if (iWeight < 0) iWeight = 0;

					GameInterface.qty_edit.str = makeint(iWeight / fWeight);
					iWeight = fWeight * sti(GameInterface.qty_edit.str);
					GameInterface.qty_edit.str = makeint(iWeight / fWeight); // округление
				}
			}
			// проверка на колво доступное <--
			// квестовые не продать -->
			if (IsQuestUsedItem(Items[iCurGoodsIdx].id) && Items[iCurGoodsIdx].id != "Gold")
			{
				GameInterface.qty_edit.str = 0;
			}
			// квестовые не продать <--
			SetFormatedText("QTY_TypeOperation", XI_ConvertString("GIVEAWAY"));
		}
		else
		{
			BuyOrSell = 1;

			// проверка на колво доступное -->
			if (sti(GameInterface.qty_edit.str) > iStoreQty)
			{
				GameInterface.qty_edit.str = iStoreQty;
			}
			iWeight = (fWeight * sti(GameInterface.qty_edit.str));
			if ((fCharWeight + iWeight) > iCharCapacity)
			{
				iWeight = iCharCapacity - fCharWeight - 0.01; // чуть меньше

				if (iWeight < 0) iWeight = 0;

				GameInterface.qty_edit.str = makeint(iWeight / fWeight);
				iWeight = fWeight * sti(GameInterface.qty_edit.str);
				GameInterface.qty_edit.str = makeint(iWeight / fWeight); // округление
			}
			// проверка на колво доступное <--
			// Руки прочь от мушкета!
			if (Items[iCurGoodsIdx].id == "mushket2x2" && iInterfaceType == INTERFACETYPE_EXCHANGE_ITEMS
			&& refToChar.id == "Douglas")
			{
				GameInterface.qty_edit.str = 0;
			}
			SetFormatedText("QTY_TypeOperation", XI_ConvertString("PICKUP"));
		}
	}
	// если получили ноль
	if (sti(GameInterface.qty_edit.str) == 0)
	{
		SetFormatedText("QTY_TypeOperation", "");
		BuyOrSell = 0;
	}
	SetFormatedText("QTY_INFO_STORE_QTY", its(iStoreQty - BuyOrSell * sti(GameInterface.qty_edit.str)));
	SetFormatedText("QTY_INFO_SHIP_QTY", its(iCharQty + BuyOrSell * sti(GameInterface.qty_edit.str)));
	SetCharWeight();
	fCharWeight = fCharWeight + BuyOrSell * iWeight;
	fStoreWeight = fStoreWeight - BuyOrSell * iWeight;
	SetVariable();
}

void REMOVE_ALL_BUTTON()  // продать все
{
	if (!bShowChangeWin)
	{
		ShowItemInfo();
	}

	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = -iCharQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void ADD_ALL_BUTTON()  // купить все
{
	if (!bShowChangeWin)
	{
		ShowItemInfo();
	}

	ShowGoodsInfo(iCurGoodsIdx);
	GameInterface.qty_edit.str = iStoreQty;
	BuyOrSell = 0;
	ChangeQTY_EDIT();
}

void REMOVE_BUTTON()  // продать
{
	if (!bShowChangeWin) return;

	if (BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = -1;
	}
	else
	{
		if (BuyOrSell == -1)
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) - 1);
		}

		BuyOrSell = 0;
	}

	ChangeQTY_EDIT();
}

void ADD_BUTTON()  // купить
{
	if (!bShowChangeWin) return;

	if (BuyOrSell == 0)
	{
		GameInterface.qty_edit.str = 1;
	}
	else
	{
		if (BuyOrSell == 1)
		{
			GameInterface.qty_edit.str = (sti(GameInterface.qty_edit.str) + 1);
		}
		else
		{
			GameInterface.qty_edit.str = -(sti(GameInterface.qty_edit.str) - 1);
		}

		BuyOrSell = 0;
	}

	ChangeQTY_EDIT();
}

// Сколько ещё могет утащить указанного предмета, в штуках
// mitrokosta переписал  без сравнения ссылок
// take == true, значит берём в refCharacter
int GetMaxItemsToTake(bool take, string _item)
{
	float curWeight;
	int maxItems, maxWeight;

	if (take)
	{
		curWeight = fCharWeight;
		maxWeight = GetMaxItemsWeight(refCharacter);
	}
	else
	{
		curWeight = fStoreWeight;
		maxWeight = GetMaxItemsWeight(refToChar);
	}

	float itemWeight = stf(Items[FindItem(_item)].weight);

	// Это золото и прочая байда - лезла ошибка деления на нуль
	if (itemWeight == 0) return 1000000000;

	maxItems = MakeInt((maxWeight - curWeight) / itemWeight);
	if (maxItems < 0) return 0;

	return maxItems;
}


void OfficerReincarnation(ref rPassanger)
{
	ref rOff = GetCharacter(NPC_GenerateCharacter("Clon", "none", rPassanger.sex, rPassanger.model.animation, 1, sti(rPassanger.nation), -1, false));

	if (!CheckAttribute(rPassanger, "OfficerReincarnation"))
		rPassanger.OfficerReincarnation = "0";

	rPassanger.OfficerReincarnation = sti(rPassanger.OfficerReincarnation) + 1; // счётчик воскрешений офицера (на будущее, может где пригодится)

	ChangeAttributesFromCharacter(rOff, rPassanger, true);
	rOff.id = rPassanger.id;

	RemoveCharacterEquip(rOff, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(rOff, GUN_ITEM_TYPE);
    RemoveCharacterEquip(rOff, MUSKET_ITEM_TYPE);
	RemoveCharacterEquip(rOff, SPYGLASS_ITEM_TYPE);
	RemoveCharacterEquip(rOff, PATENT_ITEM_TYPE);
	RemoveCharacterEquip(rOff, CIRASS_ITEM_TYPE);
	RemoveCharacterEquip(rOff, MAPS_ITEM_TYPE);

	DeleteAttribute(rOff, "items");
	rOff.items = "";

	// KZ > восстанавливаем предметы и деньги воскрешённому офицеру
	rOff.money = "0";
	rOff.items.gold = "0";

	if (CheckAttribute(&TEV, "Reincarnation.Items"))
	{
		aref arToChar, arFromChar;
		makearef(arFromChar, TEV.Reincarnation.Items);
		makearef(arToChar, rOff.items);
		CopyAttributes(arToChar, arFromChar);
	}

	if (CheckAttribute(rOff, "MushForever"))
    {
        GiveItem2Character(rOff, "unarmed");
        EquipCharacterByItem(rOff, "unarmed");
		SetCharacterToMushketer(rOff, FindCharacterItemByGroup(rOff, MUSKET_ITEM_TYPE));
    }

	if (CheckAttribute(&TEV, "Reincarnation.Money"))
		rOff.money = sti(TEV.Reincarnation.Money);

	DeleteAttribute(&TEV, "Reincarnation");
	// <

	AddPassenger(pchar, rOff, false);

	LogSound_WithNotify(StringFromKey("InfoMessages_201", rOff, GetFullNameTitulForm(rOff)), "Notebook_1", "SkullAztec");
}

bool CheckWeights(ref chest)
{
	return false;

	if (GetOfficersQuantity(pchar) > 0)
	{
		int i, iOff, totalWeights = GetMaxItemsWeight(PChar);
		int takenWeights = GetItemsWeight(PChar);

		for (i = 1; i < 4; i++)
		{
			iOff = GetOfficersIndex(pchar, i);

			if (iOff >= 0)
			{
				totalWeights += GetMaxItemsWeight(GetCharacter(iOff));
				takenWeights += GetItemsWeight(GetCharacter(iOff));
			}
		}

		if ((totalWeights - takenWeights) <= GetItemsWeight(chest))
			return true;
	}
	else
	{
		if ((GetMaxItemsWeight(PChar) - GetItemsWeight(PChar)) <= GetItemsWeight(chest))
			return true;
	}

	return false;
}

void OnHeaderClick()
{
	string sControl = GetEventData();
	int iColumn = GetEventData();
	if (sControl == "TABLE_LIST")
	{
		sortColumnIdx = iColumn;
		SortTradeList(iColumn, false, sControl);
		SetCurrentNode("TABLE_LIST");
	    SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, "TABLE_LIST", 2, sti(GameInterface.TABLE_LIST.select)-1);
	}
}

void SortTradeList(int column, bool preserveState, string tableName)
{
	string datatype = "string";
	switch (column)
	{
		case 1: datatype = "integer"; break;
		case 2: datatype = "float"; break;
		case 4: datatype = "float"; break;
		case 5: datatype = "integer"; break;
	}

	QoLSortTable(tableName, column, datatype, preserveState, 0);
}

//костыль проблемы наличия части карты в контейнере, если у игрока уже есть подобная карта
void FixDublicateThreasureMaps(ref itemsRef)
{
	bool hasPcharPart1 = GetCharacterItem(pchar, "map_part1");
	bool hasPcharPart2 = GetCharacterItem(pchar, "map_part2");

	bool hasItemsPart1 = CheckAttribute(itemsRef, "items.map_part1");
	bool hasItemsPart2 = CheckAttribute(itemsRef, "items.map_part2");

	if (!hasItemsPart1 && !hasItemsPart2) return; //если в сундуке нет карт, то и париться не о чем

	if (hasPcharPart1 && hasPcharPart2 && or(hasItemsPart1, hasItemsPart2))
	{
		if (hasItemsPart1) DeleteAttribute(itemsRef, "items.map_part1");
		if (hasItemsPart2) DeleteAttribute(itemsRef, "items.map_part2");

		itemsRef.items.map_normal = 1; // Если есть обе половинки, то найдем карту
		return;
	}

	if (hasPcharPart1 && hasItemsPart1)
	{
		DeleteAttribute(itemsRef, "items.map_part1");
		itemsRef.items.map_part2 = 1; // Если есть первая половинка, то найдем вторую
		return;
	}

	if (hasPcharPart2 && hasItemsPart2)
	{
		DeleteAttribute(itemsRef, "items.map_part2");
		itemsRef.items.map_part1 = 1; // Если есть вторая половинка, то найдем первую
		return;
	}
}

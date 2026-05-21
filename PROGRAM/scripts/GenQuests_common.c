//ugeen 12.01.10 --> отдельный файл для функций, общих для всех генераторов
string GenQuest_GenerateGoodBlade() // генерация хороших клинков для призов и подарков
{
	string itemID;
	switch(rand(5))
	{
		case 0:
			itemID = GetGeneratedItem("blade19"); // "маринера"
		break;
		case 1:
			itemID = GetGeneratedItem("blade22"); // "конкилья"
		break;
		case 2:
			itemID = GetGeneratedItem("blade31"); //  "шамшир"
		break;
		case 3:
			itemID = GetGeneratedItem("blade34"); // "скаллоп"
		break;
		case 4:
			itemID = GetGeneratedItem("blade15"); // "сторта"
		break;
		case 5:
			itemID = GetGeneratedItem("blade21"); // "бастард"
		break;
	}
	return itemID;
}

string GenQuest_GenerateBestBlade() // генерация отличных клинков для призов и подарков
{
	string itemID;
	switch(rand(10))
	{
		case 0:
			itemID = GetGeneratedItem("blade13"); // "кракемарт"
		break;
		case 1:
			itemID = GetGeneratedItem("blade13"); // "кракемарт"
		break;
		case 2:
			itemID = GetGeneratedItem("blade20"); // "клейбэг"
		break;
		case 3:
			itemID = GetGeneratedItem("blade23"); //  "бретта"
		break;
		case 4:
			itemID = GetGeneratedItem("blade24"); // "скьявона"
		break;
		case 5:
			itemID = GetGeneratedItem("blade24"); // "скьявона"
		break;
		case 6:
			itemID = GetGeneratedItem("blade25"); // "карабела"
		break;
		case 7:
			itemID = GetGeneratedItem("blade26"); // "паппенхаймер"
		break;
		case 8:
			itemID = GetGeneratedItem("blade30"); // "нобиль"
		break;
		case 9:
			itemID = GetGeneratedItem("blade33"); // "хаудеген"
		break;		
		case 10:
			itemID = GetGeneratedItem("blade24"); // "скьявона"
		break;		
	}	
	return itemID;
}

string GenQuest_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(17))
	{
		case 0:
			itemID = "indian1";
		break;
		case 1:
			itemID = "indian2";
		break;
		case 2:
			itemID = "indian3";
		break;
		case 3:
			itemID = "indian5";
		break;
		case 4:
			itemID = "indian7";
		break;
		case 5:
			itemID = "indian7";
		break;
		case 6:
			itemID = "indian10";
		break;
		case 7:
			itemID = "indian12";
		break;
		case 8:
			itemID = "indian12";
		break;
		case 9:
			itemID = "indian14";
		break;
		case 10:
			itemID = "indian14";
		break;
		case 11:
			itemID = "indian17";
		break;
		case 12:
			itemID = "indian17";
		break;
		case 13:
			itemID = "indian2";
		break;
		case 14:
			itemID = "indian19";
		break;
		case 15:
			itemID = "indian22";
		break;		
		case 16:
			itemID = "indian6";
		break;	
		case 17:
			itemID = "indian15";
		break;			
	}
	return itemID;
}

string GenQuest_GenerateTotem() // тотемы или артефакт
{
	string itm;
	for(int i = 1; i <= 10; i++)
	{
		if(!CheckMainHeroTotem("Totem_" + i) && rand(15) == 1) 
		{ 
			itm = "Totem_" + i; 	
			return itm;
		} 	
	}
	
	if(rand(12) > 2) itm = GenQuest_GenerateArtefact();
	else			 itm = GenQuest_GenerateBestBlade();
	return itm;
}

string GenQuestCommon_GenerateItem()
{
	string itm;
	if(rand(1) == 0) itm = GenQuest_GenerateTotem();
	else
	{
		if(rand(1) == 0 )
		{
			if (GetCharacterItem(pchar, "map_full") == 0) 
			{
				if (GetCharacterItem(pchar, "map_part1") == 0) { itm = "map_part1"; }
				else
				{
					if (GetCharacterItem(pchar, "map_part2") == 0) { itm = "map_part2"; }
					else itm = GenQuest_GenerateGoodBlade();
				}
			} 					
		}
		else itm = GenQuest_GenerateGoodBlade();
	}
	return itm;
}

string GenQuest_GetQuestTreasureMapDescription(ref itmRef) // надпись на квестовой карте
{
	string MapDescription;
	int i;

	i = FindLocation(itmRef.MapLocId);  // ищем ареал
	if (i != -1 && locations[i].islandId != "Mein")
	{
		string MapLocation = GetConvertStr(locations[i].islandId, "LocLables.txt");
		MapDescription = GetConvertStr("type_quest_0_isl", "MapDescribe.txt") + " " + MapLocation;
	}
	else
	{
		MapDescription = GetConvertStr("type_quest_0_mein", "MapDescribe.txt");
	}
	itmRef.MapIslName = MapDescription;
	
	MapDescription = GetConvertStr(itmRef.MapLocId, "MapDescribe.txt") + ", " + GetConvertStr(itmRef.MapLocId + "_" + itmRef.MapBoxId, "MapDescribe.txt");
	itmRef.MaplocName = MapDescription;

	MapDescription = itmRef.MapOwnId;
	itmRef.MapOwner = MapDescription;	
		
	MapDescription = GetConvertStr("type_quest_0", "MapDescribe.txt");
	MapDescription = GetAssembledString(MapDescription, itmRef);
	
	itmRef.MapDescription = MapDescription;
	return MapDescription;   	
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "ChurchCup", 1);
	ref rItem = ItemsFromID("ChurchCup");
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
}

// Для генераторго квеста "Пираты на необитаемом острове"
string PiratesOnUninhabited_GetStringNum(int _num)
{
	string retValue = "";
	
	switch(_num)
	{
		case 5: retValue = XI_ConvertString("five");  break;
		case 6: retValue = XI_ConvertString("six");   break;
		case 7: retValue = XI_ConvertString("seven"); break;
		case 8: retValue = XI_ConvertString("eight"); break;
		case 9: retValue = XI_ConvertString("nine");  break;
		case 10: retValue = XI_ConvertString("ten");  break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		// шестерки
		retShipType = SHIP_LUGGER + rand(SHIP_CUTTER - SHIP_LUGGER);
	}
	
	if(rank >= 5 && rank < 20)
	{
		retShipType = SHIP_SLOOP + rand(SHIP_BRIG - SHIP_SLOOP);
	}
	
	if(rank >= 20)
	{
		retShipType = SHIP_PINNACE + rand(SHIP_FRIGATE - SHIP_PINNACE);
	}
	
	return retShipType;
}

string PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	string retShoreId;
	
	switch(dRand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	string group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true));
	
	SetCaptanModelByEncType(character, "pirate");
	
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
	SetBaseShipData(character);
	SetCrewQuantityFull(character);
	Fantom_SetCannons(character, "pirate");
	Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	// evganat - энциклопедия
	if(CheckRandomPage("questcaptain", "pirates", -1))
	{
		character.encyclopedia.tome = GetRandomTome();
		character.encyclopedia.page = 5;
	}
	
	character.Ship.Mode = "pirate";	

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SelAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придет
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromColony2Colony(character.toCity, character.fromCity) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + dRand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Пираты на необитайке: кэп вышел из " + character.fromCity + " и направился в: " + character.toShore);
}

// belamour gen количество каторжан прописью
string Convict_GetStringNum(int iCQTY)
{
	string ConvictStr = "";

	switch(iCQTY)
	{
		case 2: ConvictStr = XI_ConvertString("ConvictTwo");    break;
		case 3: ConvictStr = XI_ConvertString("ConvictThree");  break;
		case 4: ConvictStr = XI_ConvertString("ConvictFour");   break;
		case 5: ConvictStr = XI_ConvertString("ConvictFive");   break;
		case 6: ConvictStr = XI_ConvertString("ConvictSix");    break;
		case 7: ConvictStr = XI_ConvertString("ConvictSeven");  break;
	}

	return ConvictStr;
}

void GetNearestQuestShipLocatorByLocation(string sLocId)
{
	float x, y, z;
    aref aIsland;

    for (int i=0; i<MAX_ISLANDS; i++)
    {
        if (!CheckAttribute(&Islands[i], "reload")) continue;
        makearef(aIsland, Islands[i].reload);
        int num = GetAttributesNum(aIsland);
        if (num <= 0) continue;

        for(int j = 0; j < num; j++)
        {
            aref loc = GetAttributeN(aIsland, j);
            if (UpperFirst(loc.label) == sLocId)
            {
                FindIslandLocatorXYZ(Islands[i].id, loc.name, &x, &y, &z);
                Group_SetAddress("JusticeOnSaleGroup", Islands[i].id, "quest_ships", GetSeaQuestShipNearestLocator(&Islands[i], "Quest_ships", x, y, z));
                return;
            }
        }
    }
}

void CommonGeneratorConvoyAndPassenger(ref _NPChar, string _sCharID)
{
	dialogDisable = true;
	string sTemp, sQuestGiver = "Tavern";

	if (StrEndsWith(_NPChar.id, "_PortMan"))
		sQuestGiver = "PortOffice";

	if (GetCharacterIndex(_sCharID) >= 0)
		ChangeCharacterAddressGroup(characterFromID(_sCharID), "none", "", "");

	if (!CheckAttribute(&TEV, "ArtOfDeals." + sQuestGiver + ".Colony"))
		TEV.ArtOfDeals.(sQuestGiver).Colony = "Panama";

	sTemp = TEV.ArtOfDeals.(sQuestGiver).Colony;

	if (_sCharID == "QuestTrader")
	{
		pchar.quest.destination = FindDestinationCity(_NPChar, sti(TEV.ArtOfDeals.(sQuestGiver).Convoy) + 1, sTemp);
		TEV.ArtOfDeals.(sQuestGiver).Colony = TEV.ArtOfDeals.(sQuestGiver).Colony + "," + pchar.quest.destination;
		pchar.ConvoyQuest.City = _NPChar.city;
		AddDialogExitQuest("prepare_for_convoy_quest");
	}
	else if (_sCharID == "QuestPassanger")
	{
		TEV.GenQuest_DestinationCity = FindDestinationCity(_NPChar, sti(TEV.ArtOfDeals.(sQuestGiver).Passenger) + 1, sTemp);
		pchar.GenQuest.GetPassenger_City = _NPChar.city;
		TEV.ArtOfDeals.(sQuestGiver).Colony = TEV.ArtOfDeals.(sQuestGiver).Colony + "," + TEV.GenQuest_DestinationCity;
		AddDialogExitQuest("prepare_for_passenger_quest");
	}

	sTemp = "work_date";
	if (sQuestGiver == "PortOffice")
		sTemp += "_PU";

	SaveCurrentNpcQuestDateParam(_NPChar, sTemp);
}

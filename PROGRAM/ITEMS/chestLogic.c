//HardCoffee в этот файл начинаю переносить функции работы с сундуками

//перенесено из utils_recon.c
// > простая проверка сундуков в локации на наличие в них определённых предметов TODO > ref or del
bool CheckItemsInBox(string loc, string chest, string itemList)
{
	aref itemsARef, arItemBox;
	ref locRef = &locations[FindLocation(loc)];
	int i, j, n, itm, boxQty, sym = KZ|Symbol(itemList, ",");
	int result = -1;
	string sItemBox, sItemCheck, sBox;
	
	for (i = 1; i <= 4; i++)
	{
		if (CheckAttribute(locRef, "box" + i))
			boxQty++;
	}
	
	if (boxQty > 0)
	{
		for (i = 1; i <= boxQty; i++)
		{
			sBox = "box" + i;
			
			if (chest != "" && sBox != chest)
				continue;
			
			if (CheckAttribute(locRef, sBox + ".items"))
			{
				makearef(itemsARef, locRef.(sBox).items);
				itm = GetAttributesNum(itemsARef);
				
				if (itm > 0)
				{
					for (n = 0; n < itm; n++)
					{
						arItemBox = GetAttributeN(itemsARef, n);
						sItemBox = GetAttributeName(arItemBox);
						
						if (sItemBox != "")
						{
							for (j = 0; j <= sym; j++)
							{
								sItemCheck = GetSubStr(itemList, ",", j);
								
								if (HasStr(sItemBox, sItemCheck))
									result++;
							}
						}
					}
				}
			}
		}
	}
	
	if (result >= sym)
		return true;
	
	return false;
}

// Jason подсчет указанных предметов в конкретном сундуке конкретной локации
int CheckItemInBox(string _itemID, string _locationID, string _box)
{
	int i, n, Qty = 0; 
	string attr;
	ref loc = &locations[FindLocation(_locationID)];
	aref arBox, curItem;

	if (CheckAttribute(loc , _box + ".items"))
	{
		makearef(arBox, loc.(_box).items);
		n = GetAttributesNum(arBox);

		if (n > 0)
		{
			for (i=0; i<n; i++)
			{
				curItem = GetAttributeN(arBox, i);
				attr = GetAttributeName(curItem);
				if (attr == _itemID) Qty += makeint(GetAttributeValue(curItem));
			}
		}
	}

	return Qty;
}

// Получить общеее количество предмета в боксах в переданной локации
int CheckItemInAllBoxes(ref loc, string itemId, string boxAttributeName, int boxesNum)
{
	int qty = 0;
	aref box;

	if (boxAttributeName == "")
		boxAttributeName = "box";

	if (boxesNum <= 0)
		boxesNum = 4;

	for (int n = 1; n <= boxesNum; n++)
	{
		string boxId = boxAttributeName + n;
		if (!CheckAttribute(loc, boxId + ".items")) continue;
		makearef(box, loc.(boxId).items);
		int boxItemsQty = GetAttributesNum(box);
		for (int i = 0; i < boxItemsQty; i++)
		{
			aref boxItem = GetAttributeN(box, i);
			if (GetAttributeName(boxItem) != itemId) continue;

			qty += makeint(GetAttributeValue(boxItem));
		}
	}

	return qty;
}

// Забрать (удалить) n предметов из боксов в переданной локации
int GetItemFromAllBoxes(ref loc, string itemId, int itemsToTakeQty, string boxAttributeName, int boxesNum)
{
	int itemsTaken = 0;

	if (boxAttributeName == "")
		boxAttributeName = "box";

	if (boxesNum <= 0)
		boxesNum = 4;

	for (int n = 1; n <= boxesNum; n++)
	{
		string boxId = boxAttributeName + n;
		if (!CheckAttribute(loc, boxId + ".items")) continue;

		aref box;
		makearef(box, loc.(boxId).items);
		int boxItemsQty = GetAttributesNum(box);

		for (int i = boxItemsQty-1; i >= 0; i--)
		{
			aref boxItem = GetAttributeN(box, i);
			if (GetAttributeName(boxItem) != itemId) continue;

			int inBoxQty = makeint(GetAttributeValue(boxItem));
			if (inBoxQty < 1) continue;

			if (inBoxQty > itemsToTakeQty) // в боксе достаточно предметов
			{
				itemsTaken += itemsToTakeQty;
				loc.(boxId).items.(itemId) = makeint(inBoxQty - itemsToTakeQty);
				return itemsTaken;
			}
			else // берём сколько есть
			{
				itemsTaken += inBoxQty;
				itemsToTakeQty -= inBoxQty;
				DeleteAttribute(loc, boxId + ".items." + itemId);
			}
		}
	}

	return itemsTaken;
}

// belamour положить предмет в сундук в КАЮТЕ!
void PutItemMyBox(string _Box, string _itemID, int _qty)
{
	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)	return;
	if (Pchar.SystemInfo.CabinType != "")
	{
		ref loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 
		if(CheckAttribute(loc,_Box+".items."+_itemID))
		{
			loc.(_Box).items.(_itemID) = makeint(sti(loc.(_Box).items.(_itemID)) + _qty);
		}
		else
		{
			loc.(_Box).items.(_itemID) = _qty;
		}
	}
} 

// belamour количество предмета в конкретном корабельном сундуке в КАЮТЕ!
int CheckItemMyBox(string _Box, string _itemID)
{
	int     i;	
	int		Qty = 0; 
    ref     loc;
	aref    arBox;
    aref    curItem;
	string  attr;

	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)	return 0;
	if (Pchar.SystemInfo.CabinType != "")
	{
		loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 			
		makearef(arBox, loc.(_Box).items);
		for(i=0; i<GetAttributesNum(arBox); i++)
		{
			curItem = GetAttributeN(arBox, i);
			attr = GetAttributeName(curItem);
			if (attr == _itemID)
			{
				Qty += makeint(GetAttributeValue(curItem));
			}
		}			
	}
	return Qty;
}

// belamour взять предмет из конкретного корабельного сундука, только из КАЮТЫ!
int GetItemMyBox(string _Box, string _itemID, int _qty)
{
	int     i;	
	int		Qty = 0; 
	int 	rQty = 0;	
    ref     loc;
	aref    arBox;
    aref    curItem;
	string  attr;
	
	int nShipType = GetCharacterShipType(pchar);
	if (nShipType == SHIP_NOTUSED)	return;
	if (Pchar.SystemInfo.CabinType != "")
	{
		loc = &locations[FindLocation(Pchar.SystemInfo.CabinType)]; 			
		makearef(arBox, loc.(_Box).items);
		for(i=0; i<GetAttributesNum(arBox); i++)
		{
			curItem = GetAttributeN(arBox, i);
			attr = GetAttributeName(curItem);
			if (attr == _itemID)
			{
				Qty = makeint(GetAttributeValue(curItem));
				if(Qty > 0)
				{
					if(Qty > _qty) 
					{
						loc.(_Box).items.(attr) = makeint(sti(loc.(_Box).items.(attr)) - _qty);
						rQty += Qty;
						return rQty;
					}
					else
					{
						DeleteAttribute(loc, _Box + ".items." + attr);
						_qty -= Qty;
						rQty += Qty;
					}		
				}
			}
		}
		
	}
	return rQty;
}

// заполнить сундук каюты во время абордажа //перенесено из QuestsUtilite.c проверено, работает
void FillAboardCabinBox(ref _location, ref _npchar)
{
    int     iTemp;
    bool    ok;
	float   nLuck;
	int 	iNation;
	int     iRnd;

	_location.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()); // нужно, чтоб не перетерлось
	// нужно отметить, что в сундуке сгенерятся рандомные вещи, этот код срабатывает потом и правит токо деньги

	ok = true;
	// заготовка под квест
	if (_npchar.id == "GhostCapt" && CheckAttribute(pchar , "GenQuest.GhostShip.LastBattle"))
	{
        // трем все в сундуке
        DeleteAttribute(_location, "box1");
        // кладем супер хрень
        _location.box1.items.indian11 = 1;
        _location.box1.money = 66666;
		_location.box1.items.recipe_cartridge_colt = 1;
		_location.box1.items.recipe_GunCap_colt = 1;
        ok = false;
	}
	// пасхалка Кукурузина
	/*if (CheckAttribute(_npchar, "Ship.Name") && _npchar.Ship.Name == FUNY_SHIP_NAME)
	{
        // не трем все в сундуке
        _location.box1.items.mineral4 = 25;
        ok = false;
        PChar.questTemp.FUNY_SHIP_FIND = true;
	}       */
	// маленькая пасхалка от меня -> ugeen  17.06.09

	if (CheckAttribute(_npchar, "Ship.Name") && _npchar.Ship.Name == FindPersonalName("WheelFortunaShip_ship"))
	{
		DeleteAttribute(_location, "box1");
		if (idRand(_location.id + _npchar.id, 100) > 85)
		{
			if(rand(1) == 0) { _location.box1.items.jewelry1 = rand(1500) + 461; }
			if(rand(1) == 0) { _location.box1.items.jewelry2 = rand(800) + 1214; }
			if(rand(1) == 0) { _location.box1.items.jewelry3 = rand(2210) + 750; }
			if(rand(1) == 0) { _location.box1.items.jewelry4 = rand(3450) + 280; }
			if(rand(1) == 0) { _location.box1.items.jewelry5 = rand(2471) + 370; }
			iRnd = drand(4);
			switch (iRnd)
			{
				case 0: _location.box1.items.indian18 = 1; break;
				case 1: _location.box1.items.indian21 = 1; break;
				case 2: _location.box1.items.indian20 = 1; break;
				case 3: _location.box1.items.indian11 = 1; break;
				case 4: _location.box1.items.indian6  = 1; break;
			}
		}
		else
		{
			if(rand(1) == 0) { _location.box1.items.mineral4 = rand(118) + 85; }
			_location.box1.items.mineral5 = rand(78) + 115;
			if(rand(1) == 0) { _location.box1.items.mineral8 = rand(86) + 44; }
			_location.box1.items.mineral11 = rand(146) + 131;
		}
		_location.box1.money = 12560 + rand(1000);
		ok = false;
	}

	// квест №4, англ., боевка с голландским кораблем
	if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.EngLineQ4_PutLetter"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.items.letter_EngLineQ4 = 1;
        _location.box1.money = 7460;
        _location.box1.items.map_Curacao = 1;
        ok = false;
	}
	// квест №6, англ., боевка с испанским пинасом
	if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.EngLineQ6_PutMoney"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 140000;
        _location.box1.items.map_venesuela = 1;
        _location.box1.items.spyglass3 = 1;
        _location.box1.items.potion4 = 10;
        _location.box1.items.indian7 = 1;
        ok = false;
	}
    // квест №8, англ., боевка с испанским галеоном
	if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.ELQ8_PutLetter"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.items.letter_EngLineQ8 = 1;
        _location.box1.money = 2203;
        _location.box1.items.map_cuba = 1;
        _location.box1.items.spyglass2 = 1;
        _location.box1.items.potion2 = 7;
        _location.box1.items.potionwine = 2;
        ok = false;
	}
    // квест №9, англ., боевка с Пардалем
	if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.ELQ9_Diffrent"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 853000;
        _location.box1.items.blade28 = 1;
        _location.box1.items.pistol6 = 1;
        _location.box1.items.pistol4 = 1;
        _location.box1.items.potion4 = 10;
        _location.box1.items.chest = 1;
        _location.box1.items.incas_collection = 1;
        _location.box1.items.map_cuba = 1;
        _location.box1.items.jewelry4 = 25;
        _location.box1.items.cirass3 = 1;
        ok = false;
	}
    // квест №7, испанка , выручаем Пардаля, сундук кэпа флибустьеров
	if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.SLQ7_Diffrent"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 753400;
        _location.box1.items.blade28 = 1;
        _location.box1.items.pistol6 = 1;
        _location.box1.items.pistol4 = 1;
        _location.box1.items.potion2 = 10;
        _location.box1.items.potionwine = 1;
        _location.box1.items.jewelry4 = 25;
        _location.box1.items.cirass3 = 1;
		_location.box1.items.cirass4 = 1;
        ok = false;
	}
    // квест №8, испанка , защищаем Куману, сундук кэпа флибустьеров
	if (_npchar.id == "CaptainAttack_1" && CheckAttribute(PChar, "questTemp.SLQ8_Diffrent"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 996400;
        _location.box1.items.spyglass4 = 1;
        _location.box1.items.potionrum = 2;
        _location.box1.items.pistol4 = 5;
        _location.box1.items.potion3 = 11;
        _location.box1.items.chest = 1;
        _location.box1.items.incas_collection = 1;
        _location.box1.items.jewelry5 = 50;
		_location.box1.items.indian13 = 1;
        ok = false;
	}
	// квест Аскольда.
	if (CheckAttribute(PChar, "questTemp.Ascold.Ship"))
	{
        if (_npchar.id == pchar.questTemp.Ascold.Ship)
        {
            DeleteAttribute(_location, "box1");
            _location.box1.items.AscoldInventoryList = 1;
            ok = false;
        }
	}
	// Осады  homo 22/10/06
	if (HasSubStr(_npchar.id, "SiegeCap_"))
	{
	    aref aData, itm;
	    makearef(aData, NullCharacter.Siege);
	    string sGroup = "Sea_"+NationShortName(sti(aData.nation))+"SiegeCap_1";
	    ref rchar = Group_GetGroupCommander(sGroup);  //поиск текущего командера, он меняется от убиеня
	    Log_TestInfo( _npchar.id +" == "+ rchar.id);
		if (_npchar.id == rchar.id && CheckAttribute(aData, "loot"))
		{
	        DeleteAttribute(_location, "box1");
	        _location.box1.money = sti(aData.loot);
	        _location.box1.items.potionrum = 3;
	        _location.box1.items.potionwine = 1;
	        string idmap = "map_"+aData.island;
            if (Items_FindItem(idmap, &itm) != -1)
            {
                _location.box1.items.(idmap) = 1;
            }

	        ok = false;
		}
	}
	//homo =>
    if (HasSubStr(_npchar.id, "_QuestMerchant"))
    {
        if (trap)
        {
            DeleteAttribute(_location, "box1");
            _location.box1.money = (idRand(_npchar.id + "_QuestMerchant", 30)+1) * 40;
            _location.box1.items.blade31 = 1;
            ok = false;
        }
    }

    if (_npchar.id == "Head_of_Gold_Squadron" )
    {

        DeleteAttribute(_location, "box2");
        _location.box2.money = 2212;
        _location.box2.items.map_normal = 1;
        ok = false;

    }
    //homo <=
    // пиратка, квест №7. драгоценности в каюту
	if (_npchar.id == "QuestCap_PL7")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 3983;
        _location.box1.items.jewelry1 = 763;
        _location.box1.items.jewelry2 = 562;
        _location.box1.items.jewelry3 = 1771;
        _location.box1.items.jewelry4 = 678;
        _location.box1.items.jewelry6 = 236;
        _location.box1.items.jewelry7 = 321;
        _location.box1.items.jewelry14 = 121;
		_location.box1.items.jewelry15 = 45;
		_location.box1.items.jewelry18 = 311;
        ok = false;
	}
    // пиратка, квест №7. драгоценности в каюту
	if (_npchar.id == "MushketCap")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 103;
		_location.box1.items.mushket2x2 = 1;
        ok = false;
	}
	//работорговец, 2 эпизод
	if (_npchar.id == "CaptainSlaveAttack_2" && CheckAttribute(PChar, "questTemp.Slavetrader"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 20000;
		_location.box1.items.statue1 = 1;
        ok = false;
	}
	//работорговец, письмо, 4 эпизод
	if (_npchar.id == "CapBrigAttack" && CheckAttribute(PChar, "questTemp.Slavetrader"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 5500;
		_location.box1.items.letter_1 = 1;
        ok = false;
	}
	//работорговец, линкор
	if (_npchar.id == "GaleonCap" && CheckAttribute(PChar, "questTemp.Slavetrader"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 2350;
		_location.box1.items.jewelry5 = 1000;
		DeleteAttribute(_location, "box2");
		_location.box2.items.indian15 = 1;
		_location.box2.items.indian8 = 528;
		_location.box2.items.indian9 = 9;
		_location.box2.items.indian2 = 3;
		_location.box2.items.indian14 = 16;
		DeleteAttribute(_location, "box3");
		_location.box3.items.indian5 = 2;
		_location.box3.items.indian16 = 114;
		_location.box3.items.indian13 = 58;
		_location.box3.items.indian12 = 1;
		_location.box3.items.indian1 = 1;
        ok = false;
	}

	//малява курьер
	if (_npchar.id == "CureerAttack")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 1000;
        _location.box1.items.jewelry1 = 50+rand(200);
        _location.box1.items.jewelry2 = 50+rand(100);
        _location.box1.items.jewelry3 = 50+rand(100);
        _location.box1.items.jewelry4 = 50+rand(100);
        _location.box1.items.jewelry6 = 50+rand(80);
        _location.box1.items.jewelry7 = 50+rand(100);
		_location.box1.items.jewelry10 = 50+rand(160);
        _location.box1.items.jewelry14 = 50+rand(150);
		_location.box1.items.jewelry15 = rand(40);
		_location.box1.items.jewelry18 = rand(200);
		DeleteAttribute(_location, "box2");
		// evganat - энциклопедия
		if(CheckRandomPage("questprisoner", "cureer", -1))
		{
			_location.box2.encyclopedia.tome = GetRandomTome();
			_location.box2.encyclopedia.page = 5;
		}
		iRnd = rand(5);
			switch (iRnd)
			{
				case 0: _location.box2.items.cirass4 = 1; break;
				case 1: _location.box2.items.spyglass4 = 1; break;
				case 2: _location.box2.items.pistol5 = 1; break;
				case 3: _location.box2.items.blade34 = 1; break;
				case 4: _location.box2.items.blade19 = 1; break;
				case 5: _location.box2.items.pistol4 = 1; break;
			}
        ok = false;
	}
	//ОЗГ, пинас Крысы, драгоценности
	if (_npchar.id == "RatCaptain" && CheckAttribute(PChar, "questTemp.Headhunter"))
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 21500;
		_location.box1.items.incas_collection = rand(2);
		_location.box1.items.jewelry1 = 20+rand(20);
        _location.box1.items.jewelry2 = 20+rand(20);
        _location.box1.items.jewelry3 = 30+rand(20);
        _location.box1.items.jewelry4 = 10+rand(10);
        _location.box1.items.jewelry6 = rand(50);
        _location.box1.items.jewelry7 = rand(100);
		_location.box1.items.jewelry10 = rand(50);
        _location.box1.items.jewelry14 = rand(50);
		_location.box1.items.jewelry15 = rand(10);
		_location.box1.items.jewelry18 = rand(100);
        ok = false;
	}
	//Квест "Остепенившийся пират", английский галеон у Доминики, драгоценности
	if (_npchar.id == "PDM_Lesopilka_Galeon")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 10000;
		_location.box1.items.jewelry1 = 20+rand(10);
        _location.box1.items.jewelry2 = 20+rand(10);
        _location.box1.items.jewelry3 = 30+rand(10);
        _location.box1.items.jewelry4 = 30+rand(10);
        _location.box1.items.jewelry5 = rand(80);
		_location.box1.items.LesopilkaLog = 1;
        ok = false;
	}
	//Шарп, морская дуэль после первого похода
	if (_npchar.id == "Sharp" && CheckAttribute(PChar, "questTemp.Sharp") && PChar.questTemp.Sharp == "FirstPearlNotPay")
	{
        DeleteAttribute(_location, "box1");
        _location.box1.money = 20000;
		_location.box1.items.jewelry11 = 600+rand(100);
        _location.box1.items.jewelry12 = 300+rand(100);
        ok = false;
	}

    if (ok) // не квестовый
    {
    	// код для всех

		// Warship 02.07.09 Это прикол такой - можно у случайного кэпа в сундуке обраружить ключ от сундуков Моргана
		// Причем, сундуков у Моргана два, а открыть получится только один из них
		if(!CheckAttribute(PChar, "QuestTemp.MorganKeyTaken") && rand(99) == 1)
		{
			PChar.QuestTemp.MorganKeyTaken = true;
			_location.box1.items.keyMorgan = 1;
			Log_TestInfo(StringFromKey("QuestsUtilite_4"));
		}

    	iTemp = GetCharacterShipClass(_npchar);

		// evganat - энциклопедия
		if(iTemp == 1)
		{
			if(CheckRandomPage("cabinchest", "", -1))
			{
				_location.box1.encyclopedia.tome = GetRandomTome();
				_location.box1.encyclopedia.page = 3;
			}
		}

		iNation = sti(_npchar.nation);

		if(iNation == PIRATE)
		{
			nLuck   = GetCharacterSkillToOld(Pchar, SKILL_FORTUNE);
			if (nLuck > rand(250) && GetCharacterItem(pchar, "map_full") == 0)  // шанс 1/30
			{
				if (GetCharacterItem(pchar, "map_part1") == 0)
				{
					_location.box1.items.map_part1 = 1;
				}
				else
				{
					if (GetCharacterItem(pchar, "map_part2") == 0)
					{
						_location.box1.items.map_part2 = 1;
					}
				}
			}
			FillCabinBoxMap(_location, 200 - (7 - iTemp) * 5);
		}
		else
		{
			FillCabinBoxMap(_location, 250 - (7 - iTemp) * 5);
		}

		if (CheckAttribute(_npchar, "Ship.Mode") && _npchar.Ship.Mode == "Trade")  // торговец
		{
			_location.box1.money = (10 - iTemp) * 200 + rand(10 - iTemp) * 2000 + rand(10)*50 + rand(6 - iTemp) * 4000;
		}
		else // все остальные
		{
			_location.box1.money = (10 - iTemp) * 90 + rand((10 - iTemp) * 2000);
		}
    }
}

//перенесено из QuestsUtilite.c //вызывается в LAi_boarding.c и в void FillAboardCabinBox проверено, работает
// --> ugeen  - генерация карт островов в сундуке каюты во время абордажа   07.07.09
void FillCabinBoxMap(ref _location, int _probability)
{
	int 	i;
	string  itemID, groupID;
    ref     itm;

	for (i=0; i<ITEMS_QUANTITY; i++)
	{
		makeref(itm,Items[i]);
		if(CheckAttribute(itm, "ID") && CheckAttribute(itm, "groupID"))
		{
			itemID = itm.id;
			groupID = itm.groupID;
			if(groupID == MAPS_ITEM_TYPE && !CheckAttribute(itm, "mapSpecial") && (itemID != "Map_Best") && (itemID != "Map_LSC"))
			{
				if(rand(_probability) == 1)
				{
					_location.box1.items.(itemID) = 1;
					return;
				}
			}
		}
	}
}
//<-- ugeen

//перенесено из QuestsUtilite.c
//ugeen --> заполнить сундук в трюме квестовым барахлом
void FillQuestHoldBox(ref _location)
{
	//_location.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()); // нужно, чтоб не перетерлось

	int nShipType = sti(pchar.ship.type);

	if(CheckAttribute(pchar,"GenQuest.CaptainComission.CanFindChest"))
	{
		if(nShipType == sti(pchar.GenQuest.CaptainComission.ShipType) && !CheckAttribute(pchar,"GenQuest.CaptainComission.Treasure"))
		{
			Log_QuestInfo(StringFromKey("QuestsUtilite_3"));
			if (CheckAttribute(_location, "box1.items.chest") && sti(_location.box1.items.chest) > 0)
				_location.box1.items.chest = sti(_location.box1.items.chest) + 3;
			else
				_location.box1.items.chest = 3;
			pchar.GenQuest.CaptainComission.Treasure = true;
		}
	}
}
// <-- ugeen

//перенесено из QuestsUtilite.c, вызывается в itemLogic.c
// заполнение сундуков и рандитема по квесту
bool SetLocationQuestRandItem(int _index, aref _location, string _locatorName, aref al) // al - ветка локатора из модели, остальное тоже из обратотки локации
{   // метод редактировать не нужно - все задается в квестах
	string  lastSpawnTimeString;
    int     n;
	string  itemId;
	aref checkAref;

	/* Пример
 	pchar.GenQuestRandItem.QC_Port = true;
    pchar.GenQuestRandItem.QC_Port.randitem1 = "pistol6";
    // если нужно чтоб было всегда
	pchar.GenQuestRandItem.QC_Port.stay = true; - тереть потом эту ветку самому по квесту

    QC_Port - локация где
    randitem1 - локатор
    pistol6 - предмет

    если нужно сразу несколько локаторов, то
    pchar.GenQuestRandItem.QC_Port.randitem1 = "pistol6";
    pchar.GenQuestRandItem.QC_Port.randitem2 = "pistol1";
 	*/
	lastSpawnTimeString = _location.id;
    if (CheckAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString) && CheckAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString +"."+_locatorName))
    {
        itemId = pchar.GenQuestRandItem.(lastSpawnTimeString).(_locatorName);
        if (!CheckAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString +".stay"))
        {
			//--> fix eddy. нельзя было положить в несколько локаторов
			DeleteAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString + "." + _locatorName); // если токо один раз
			makearef(checkAref,  pchar.GenQuestRandItem.(lastSpawnTimeString));
			if (GetAttributesNum(checkAref) == 0) DeleteAttribute(pchar , "GenQuestRandItem." + lastSpawnTimeString);
        }
        // только один предмет!!!!!!!!!!!!
        n = SetRandItemShow(_index, al, itemId); // вывести 3д модель в локацию, если модель вообще есть
		if (n != -1)
		{
            Log_TestInfo("SetLocationQuestRandItem");
            lastSpawnTimeString = "LastSpawnTime"+_index;
		    _location.(lastSpawnTimeString) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
            lastSpawnTimeString = "RandItemType"+_index;
        	_location.(lastSpawnTimeString) = n;
            return true;
        }
    }

    return false;
}
// загрузить модель //используется в bool SetLocationQuestRandItem
int SetRandItemShow(int _index, aref al, string _itemId)
{
    int     n;
    aref    randItem;

    n = Items_FindItem(_itemId, &randItem);
	if (n != -1)
	{
        if (!CheckAttribute(randItem, "model") || randItem.model == "")
    	{
    		Trace("SetRandItemShow: no model for item "+randItem.id);
    		return -1;
    	}
	    Items_LoadModel(&randItemModels[_index],  randItem);
    	SendMessage(&randItemModels[_index], "lffffffffffff", MSG_MODEL_SET_POSITION, makeFloat(al.x), makeFloat(al.y), makeFloat(al.z), makeFloat(al.vx.x), makeFloat(al.vx.y), -makeFloat(al.vx.z), makeFloat(al.vy.x), makeFloat(al.vy.y), -makeFloat(al.vy.z), makeFloat(al.vz.x), makeFloat(al.vz.y), -makeFloat(al.vz.z));

        return n;
    }
    return n;
}

// заполнить сундук //перенесено из QuestsUtilite.c, вызывается в itemLogic.c
bool SetLocationQuestBox(ref _location, string _locatorName)
{   // метод редактировать не нужно - все задается в квестах
    bool    ok = false;
    string  locId;
    aref    arToBox;
    aref    arFromBox;

    /* Пример
 	pchar.GenQuestBox.Havanna_town_04 = true;
    pchar.GenQuestBox.Havanna_town_04.box1.items.jewelry1 = 4;
    pchar.GenQuestBox.Havanna_town_04.box1.items.mineral2 = 10;
    // если нужны деньги, иначе не заполнять
	pchar.GenQuestBox.Havanna_town_04.box1.money          = 100;
    // если нужно чтоб было всегда
	pchar.GenQuestBox.Havanna_town_04.stay = true; - тереть потом эту ветку самому по квесту

    Havanna_town_04 - локация где
    box1 - локатор
    items - список предметов

    если нужно сразу несколько локаторов, то
    pchar.GenQuestBox.Havanna_town_04.box2.items.jewelry1 = 34;
 	*/
 	locId  = _location.id;
    if (CheckAttribute(pchar , "GenQuestBox." + locId) && CheckAttribute(pchar , "GenQuestBox." + locId + "." + _locatorName))
    {
        Log_TestInfo("SetLocationQuestBox");

        makearef(arToBox, _location.(_locatorName));
        makearef(arFromBox, pchar.GenQuestBox.(locId).(_locatorName));
        CopyAttributes(arToBox, arFromBox);
        _location.(_locatorName) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear()); // таймер, чтоб не затерлись рандомом при выходе из локации
        if (!CheckAttribute(pchar , "GenQuestBox." + locId +".stay"))
        {
			//--> fix eddy. нельзя было положить в несколько локаторов
			DeleteAttribute(pchar , "GenQuestBox." + locId + "." + _locatorName); // если токо один раз
			makearef(arToBox,  pchar.GenQuestBox.(locId));
			if (GetAttributesNum(arToBox) == 0) DeleteAttribute(pchar , "GenQuestBox." + locId);
        }
        return true;
    }
    return false;
}

//HardCoffee заполнение тайников
bool FillSecretBox(ref location, string boxName)
{	//Если сундук суже заполен - возвращает true, если заполнился в процессе прохождения этой функции - возвращает false
//основываясь на названии локаци loc.id и названии тайника loc.(boxname) можно придумать логику заполнения
    if (checkattribute(location, boxName +".difficult")) return true;

	//викторинщики
	if (boxName == "secret0")
	{
		switch (location.id)
		{
			case "LaVega_town": //Port Of Spain
				location.(boxName).items.mushket_flint = 1;
			break;
			case "PuertoPrincipe_town": //Villemstad Квест 'Неудобная пропажа'
            	location.(boxName).items.spyglass3 = 1;
            break;
            case "Shore46": //Cumana
            	location.(boxName).items.instrument1 = 1;
            break;
            case "Tortuga_Cave": //Port o Prece (PortPax) Квест 'Пиратская мода' (Вызволение из плена мужа горожанки)
				location.(boxName).items.suit_2 = 1;
			break;
			case "Cuba_Grot": //Santiago
				location.(boxName).items.pistol6 = 1;
			break;
			case "Shore36": //Port Royale
				location.(boxName).items.cirass4 = 1;
			break;
			case "CommonStoneHouse": //Bridgetown - BloodLine
				location.(boxName).items.indian1 = 1;
				location.(boxName).items.EngTradeLicence = 1;
				location.(boxName).money = 8500;
			break;
			location.(boxName).difficult = -2; //Default заглушка для локаций с одинаковыми локаторами, чтобы не залезли в сундук
			return false;
        }
        location.(boxName).difficult = 1; // этот аттрибут нужен для определения заполненности
        return false;
	}

	string sID = location.id + boxName;
	int iChestType = idRand(sID, 6);
	sID = sId + its(iChestType);
	switch (iChestType)
    {
    	/*сложность сундука:
    	1) определяется для каждого тайника при первом заходе на локацию и остаётся всю игру
    	2) проверка на "восприятие" рандомит эту сложность от 0 до максимума
    	это необходимо для того, чтобы был шанс открыть сундук с высокой сложностью при низком восприятии
    	шанс должен быть, иначе хомяки начнут возмущаться
    	3) сложность сравнивается с "восприятием" умноженным на 10
    	4) тайник со сложностью 100 откроется с вероятностью 100% при восприятии 10
    	и с примерно 10% вероятностью с восприятием 1
    	5) тайник со сложностью 10 откроется с вероятностью 100% при восприятии 1
		6) тесты с восприятием 6 показали, что 100 - достаточно лёгкий сундук, а 200 - трудный
		*/
    	//сложность 0 не ставить - она для проверки на "уже обнаружен/нет"
		//формируем содержимое тайников Konstrush
    	case 0: // зельевой
			if (idRand(sID + "potion5", 1) == 1) location.(boxName).items.potion5 = idRand(sID + "potion5" +"qty", 20);
            if (idRand(sID + "potion3", 1) == 1) location.(boxName).items.potion3 = its(4 + idRand(sID + "potion3" +"qty", 10));
			if (idRand(sID + "potion1", 1) == 1) location.(boxName).items.potion1 = its(5 + idRand(sID + "potion1" +"qty", 12));
			if (idRand(sID + "potionwine", 1) == 1) location.(boxName).items.potionwine = its(5 + idRand(sID + "potionwine" +"qty", 5));
			if (idRand(sID + "potionrum", 1) == 1) location.(boxName).items.potionrum = its(5 + idRand(sID + "potionrum" +"qty", 10));
			if (idRand(sID + "money", 1) == 1) location.(boxName).money = its(300 + idRand(sID + "money" +"qty", 1200));
			location.(boxName).difficult = its(115 + idrand(sID +"diff", 50));
		break;
		case 1: // индейский схрон
			if (idRand(sID + "chest", 1) == 1) location.(boxName).items.chest = its(1 + idRand(sID + "chest" +"qty", 1));
			if (idRand(sID + "Statue1", 1) == 1) location.(boxName).items.Statue1 = 1;
			if (idRand(sID + "indian9", 1) == 1) location.(boxName).items.indian9 = its(5 + idRand(sID + "indian9" +"qty", 6));
			if (idRand(sID + "indian8", 1) == 1) location.(boxName).items.indian8 = its(5 + idRand(sID + "indian8" +"qty", 10));
			if (idRand(sID + "jewelry11", 1) == 1) location.(boxName).items.jewelry11 = its(20 + idRand(sID + "jewelry11" +"qty", 15));
			if (idRand(sID + "indian18", 1) == 1) location.(boxName).items.indian18 = 1;
			if (idRand(sID + "indian3", 1) == 1) location.(boxName).items.indian3 = its(2 + idRand(sID + "indian3" +"qty", 3));
			if (idRand(sID + "potion4", 1) == 1) location.(boxName).items.potion4 = its(1 + idRand(sID + "potion4" +"qty", 3));
			if (idRand(sID + "money", 1) == 1) location.(boxName).money = its(500 + idRand(sID + "money" +"qty", 2000));
			location.(boxName).difficult = its(145 + idrand(sID +"diff", 50));
    	break;
		case 2: // бытовой хлам
			if (idRand(sID + "kocherg", 1) == 1) location.(boxName).items.kocherg = 1;
			if (idRand(sID + "mineral8", 1) == 1) location.(boxName).items.mineral8 = its(1 + idRand(sID + "mineral8" +"qty", 5));
			if (idRand(sID + "mineral6", 1) == 1) location.(boxName).items.mineral6 = its(4 + idRand(sID + "mineral6" +"qty", 5));
			if (idRand(sID + "mineral10", 1) == 1) location.(boxName).items.mineral10 = its(5 + idRand(sID + "mineral10" +"qty", 5));
			if (idRand(sID + "mineral12", 1) == 1) location.(boxName).items.mineral12 = its(4 + idRand(sID + "mineral12" +"qty", 3));
			if (idRand(sID + "mineral2", 1) == 1) location.(boxName).items.mineral2 = 1;
			if (idRand(sID + "money", 1) == 1) location.(boxName).money = its(idRand(sID + "money" +"qty", 1000));
			location.(boxName).difficult = its(105 + idrand(sID +"diff", 40));
		break;
		case 3: // золотой схрон
			if (idRand(sID + "f13", 1) == 1 && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10 + idRand(sID + "f23", 50) + idRand(sID + "f33", 50))
			{
				location.(boxName).items.jewelry5 = its(10 + idRand(sID + "jewelry5" +"qty", 15));
				location.(boxName).items.jewelry8 = its(20 + idRand(sID + "jewelry8" +"qty", 15));
				location.(boxName).items.jewelry14 = its(10 + idRand(sID + "jewelry14" +"qty", 15));
				location.(boxName).items.jewelry18 = its(5 + idRand(sID + "jewelry18" +"qty", 15));
			}
			else
			{
				location.(boxName).items.incas_collection = 1;
			}
			location.(boxName).difficult = its(150 + idrand(sID +"diff", 55));
		break;
		case 4: // silver
			if (idRand(sID + "f14", 1) == 1 && GetSummonSkillFromName(pchar, SKILL_FORTUNE) >  10 + idRand(sID + "f24", 25) + idRand(sID + "f34", 40))
			{
				location.(boxName).items.jewelry17 = its(10 + idRand(sID + "jewelry17", 20));
				location.(boxName).items.jewelry6 = its(10 + idRand(sID + "jewelry6", 20));
				location.(boxName).items.indian8 = its(15 + idRand(sID + "indian8", 20));
			}
			else
			{
				location.(boxName).money = its(5000 + idRand(sID + "money" +"qty", 7500));
			}
			location.(boxName).difficult = its(150 + idrand(sID +"diff", 50));
		break;
		case 5: // стрелковое
			if (idRand(sID + "GunPowder", 1) == 1) location.(boxName).items.GunPowder = its(25 + idRand(sID + "GunPowder" +"qty", 25));
			if (idRand(sID + "bullet", 1) == 1) location.(boxName).items.bullet = its(25 + idRand(sID + "bullet" +"qty", 25));
			
			if (idRand(sID + "pistol3", 1) == 1) location.(boxName).items.pistol3 = 1;
			else location.(boxName).items.pistol1 = 2;

			if (idRand(sID + "mushket_poor", 1) == 1) location.(boxName).items.mushket_poor = 1;
			//if (idRand(sID + "grapeshot", 1) == 1) location.(boxName).items.grapeshot = its(10 + idRand(sID + "grapeshot" +"qty", 25));
			if (idRand(sID + "cirass1", 1) == 1) location.(boxName).items.cirass1 = 1;
			location.(boxName).difficult = its(120 + idrand(sID +"diff", 45));
		break;
		case 6: //это пустой сундук при заходе на локатор не появится возможность его открыть
			location.(boxName).difficult = -2; //-2 нужно для тестового лога
		break;
    }
    float fRadius = 0.8;
    location.locators_radius.box.(boxName) = fRadius;
    SendMessage(location, "lssf", MSG_LOCATION_LOC_RADIUS, "box", (boxName), fRadius);
	location.(boxName).visitedTime = 1;
    return false;
}

// Jason заполнение выброшенных на берег сундуков //перенесено из QuestsUtilite.c проверено, работает
void FillShorechestBox(string loc, int n, int i)
{
	pchar.GenQuestBox.(loc) = true;
	string boxx = "box"+n;

	// evganat - энциклопедия
	if(CheckRandomPage("shorechest", loc, -1))
	{
		pchar.GenQuestBox.(loc).(boxx).encyclopedia.tome = GetRandomTome();
		pchar.GenQuestBox.(loc).(boxx).encyclopedia.page = 3;
	}

	switch (i)
	{
		case 0: // good нихера там накидано ща будем резать Konstrush
		    if (rand(1) == 1)   pchar.GenQuestBox.(loc).(boxx).money = 2000 + drand(3000);
            if (rand(3) == 1)	pchar.GenQuestBox.(loc).(boxx).items.jewelry8 = drand(40);
            if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.potion3 = 7+drand(10);
            if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.potion1 = 5+drand(12);
	    break;
	    case 1: // best
			if (rand(1) == 1)   pchar.GenQuestBox.(loc).(boxx).money = 4000 + drand(6000);
            if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.chest = 1+drand(1);
	        if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.incas_collection = 1;
	        if (rand(1) == 1)   pchar.GenQuestBox.(loc).(boxx).items.jewelry5 = 20+drand(15);
	        if (rand(1) == 1)   pchar.GenQuestBox.(loc).(boxx).items.jewelry2 = 20+drand(15);
	        if (rand(1) == 1)   pchar.GenQuestBox.(loc).(boxx).items.jewelry8 = 20+drand(15);
			if (rand(3) == 1)	pchar.GenQuestBox.(loc).(boxx).items.jewelry9 = rand(1);
			if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.potion2 = 10+drand(5);
	        if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.potion4 = 10+drand(3);
	    break;
	    case 2: // bad
			if (rand(1) == 1)   pchar.GenQuestBox.(loc).(boxx).money = drand(1000);
	        if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.blade_05 = drand(4);
	        if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.blade_07 = 1;
            if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.potion5 = 6+drand(5);
	        if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.jewelry5 = 6+drand(5);
	        if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.jewelry4 = 6+drand(5);
	        if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.jewelry4 = 6+drand(4);
	        if (rand(2) == 1)   pchar.GenQuestBox.(loc).(boxx).items.jewelry9 = 1;
	    break;
		case 3: // gold
	        if (rand(1) == 1 && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+drand(50)+drand(50))
            		pchar.GenQuestBox.(loc).(boxx).items.jewelry5 = 50+drand(35);
			else	pchar.GenQuestBox.(loc).(boxx).items.potionwine = 35+drand(25);
	    break;

		case 4: // silver
	        if (rand(1) == 0 && GetSummonSkillFromName(pchar, SKILL_FORTUNE) > 10+drand(50)+drand(50))
	        		pchar.GenQuestBox.(loc).(boxx).items.jewelry6 = 60+drand(30);
			else	pchar.GenQuestBox.(loc).(boxx).items.potionrum = 25+drand(30);
	    break;
		case 5: // warrior
			if (rand(1) == 1)	pchar.GenQuestBox.(loc).(boxx).items.GunPowder = 50+drand(50);
			if (rand(1) == 1)	pchar.GenQuestBox.(loc).(boxx).items.bullet = 50+drand(50);

			if (drand(5) == 2)	pchar.GenQuestBox.(loc).(boxx).items.pistol3 = 1;
			else	pchar.GenQuestBox.(loc).(boxx).items.pistol1 = 2;

			if (drand(20) == 5)	pchar.GenQuestBox.(loc).(boxx).items.pistol6 = 1;
			if (drand(9) == 1)	pchar.GenQuestBox.(loc).(boxx).items.cirass1 = 1;
	        if (drand(9) == 5)	pchar.GenQuestBox.(loc).(boxx).items.cirass3 = 1;
	    break;
	}
}
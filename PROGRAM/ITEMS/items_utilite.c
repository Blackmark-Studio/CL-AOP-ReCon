bool IsQuestUsedItem(string itmID)
{
	aref arItm;
	if( Items_FindItem(itmID,&arItm)<0 ) return false;
	if( CheckAttribute(arItm,"price") && sti(arItm.price)>0 ) return false;
	return true;
}

void DoCharacterUsedItem(ref chref, string itmID)
{
	aref arItm;
	if( Items_FindItem(itmID,&arItm)<0 ) return;
	TakeItemFromCharacter(chref,itmID);

	 // Warship 13.06.09 fix - если только отравлен, а жизни полные (а такое бывает), то нечего и строку в лог выводить об прибавлении жизней
	if(CheckAttribute(arItm,"potion.health") && LAi_GetCharacterHP(chref) < LAi_GetCharacterMaxHP(chref))
	{
		LAi_UseHealthBottle(chref,stf(arItm.potion.health));
		if(sti(chref.index)!=GetMainCharacterIndex())
        {
            if(ShowCharString()) Log_Chr(chref, XI_ConvertString("Health UpLog"));
        }
        else
        {
            Log_SetStringToLog( XI_ConvertString("Health Up"));
        }
		// boal
		if( CheckAttribute(arItm,"potion.health.speed") )
		{
			LAi_UseHealthBottleSpeed(chref, stf(arItm.potion.health.speed));
		}
	}
	
	if (CheckAttribute(arItm, "potion.energy") && Lai_CharacterGetEnergy(chref) < LAi_GetCharacterMaxEnergy(chref))
	{
		LAi_UseEnergyBottle(chref, stf(arItm.potion.energy));
		if (sti(chref.index) == GetMainCharacterIndex())
			Log_SetStringToLog( XI_ConvertString("Energy Up"));
		
		if (CheckAttribute(arItm, "potion.energy.speed"))
			LAi_UseEnergyBottleSpeed(chref, stf(arItm.potion.energy.speed));
	}
	
	// Warship 13.06.09 fix - если не отравлен, то нечего и строку в лог выводить
	if(CheckAttribute(arItm,"potion.antidote") && LAi_IsPoison(chref))
	{
		LAi_UseAtidoteBottle(chref);
		if(sti(chref.index)==GetMainCharacterIndex()) {
			Log_SetStringToLog( XI_ConvertString("You are cured from poison") );
		}
		else{
//			Log_SetStringToLog(GetFullName(chref) + XI_ConvertString("are cured from poison") );
			if(ShowCharString()) Log_Chr(chref, XI_ConvertString("are cured from poisonLog"));
            else Log_SetStringToLog(GetFullName(chref) + XI_ConvertString("are cured from poison") );
		}
	}
	
	//navy --> алкоголь
	if (CheckAttribute(arItm, "potion.drunk"))
	{
		LAi_DrunkAlcoholPotion(chref, arItm);
		if(sti(chref.index)==GetMainCharacterIndex())
		{
			Log_SetStringToLog( XI_ConvertString("You're get drunk") );
		}
	}
	//<--
	if (CheckAttribute(arItm, "potion.sound") && arItm.potion.sound != "")
	{
		PlaySound(arItm.potion.sound);
	}
}

float MinHealthPotionForCharacter(ref chref)
{
	float ftmp;
	bool isFinded = false;

	for(int n=0; n<ITEMS_QUANTITY; n++)
	{
		if( CheckAttribute(&Items[n],"potion") )
		{
			if(CheckAttribute(&Items[n],"potion.health"))
			{
				if( GetCharacterItem(chref,Items[n].id)>0 )
				{
					if(isFinded)
					{
						if( stf(Items[n].potion.health)<ftmp )
						{
							ftmp = stf(Items[n].potion.health);
						}
					}else{
						ftmp = stf(Items[n].potion.health);
						isFinded = true;
					}
				}
			}
		}
	}
	if(!isFinded) return 0.0;
	return ftmp;
}

string FindHealthForCharacter(ref chref,float fHealth)
{
	string sret = "";
	float fdelta = fHealth + 100.0;
	float ftmp;

	for(int n=0; n<ITEMS_QUANTITY; n++)
	{
		if( CheckAttribute(&Items[n],"potion") )
		{
			if( CheckAttribute(&Items[n],"potion.health") )
			{
				if( GetCharacterItem(chref,Items[n].id)>0 )
				{
					ftmp = stf(Items[n].potion.health);
					if( ftmp<fHealth )	{ftmp = fHealth - ftmp;}
					else	{ftmp = ftmp - fHealth;}
					if(ftmp<fdelta)
					{
						fdelta = ftmp;
						sret = Items[n].id;
					}
				}
			}
		}
	}

	return sret;
}

int FindPotionFromChr(ref chref, ref arFind, int startIdx)
{
	int i;
	aref arItm;
	for(i=startIdx; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		if( CheckAttribute(arItm,"potion") && GetCharacterItem(chref,Items[i].id)>0 )
		{
			arFind = arItm;
			return i;
		}
	}
	return -1;
}

// belamour найти количество типов лечебных зелий у персонажа
int FindPotionTypesQty(ref chref)
{
	int n = 0;
	ref rItem;
	aref Items, arItems;

	makearef(arItems, chref.items);
	int iItemsNum = GetAttributesNum(arItems);
	for(int i=0; i<iItemsNum; i++)
	{
		string sItem = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sItem);
		if(!CheckAttribute(rItem, "potion")) continue;
		if(!CheckAttribute(rItem, "potion.health")) continue;
		n++;
	}
	return n;
}


int UseBestPotion(ref chref, bool needAntidote)
{
	int i;
	int curPotionID = -1;
	int curPotionHealAmt = 0;
	int newPotionHealAmt = 0;
	bool potionTooGood = false;
	bool bValidPot;
	int reqHealAmt = LAi_GetCharacterMaxHP(chref) - LAi_GetCharacterHP(chref);
	reqHealAmt = makeint(MakeFloat(reqHealAmt) * 1.2);
	if (reqHealAmt <=0 && !needAntidote) 
	{
		return -1;
	}
	
	aref arItm;
	for(i=1; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		bValidPot = false;

		if (!needAntidote && CheckAttribute(arItm,"potion.health") && !CheckAttribute(arItm,"potion.antidote")) 
		{
			bValidPot = true;
		}
		else 
		{
			if (needAntidote && CheckAttribute(arItm,"potion.antidote")) 
			{
				bValidPot = true;
			}
		}
		if( bValidPot && (GetCharacterItem(chref,arItm.id) > 0))
		{
			if (CheckAttribute(arItm,"potion.health"))
				newPotionHealAmt = arItm.potion.health;
			else
				newPotionHealAmt = 0;
								
			if (potionTooGood) 
			{
				if (newPotionHealAmt < curPotionHealAmt) 
				{
					curPotionID = i;
					curPotionHealAmt = newPotionHealAmt;
				}
			}
			else
			{
				if ((newPotionHealAmt + 1) > curPotionHealAmt) 
				{
					if (curPotionHealAmt == 0 || newPotionHealAmt <= reqHealAmt) 
					{
						curPotionID = i;
						curPotionHealAmt = newPotionHealAmt;
					}
				}
			}
			if (curPotionHealAmt > reqHealAmt) 
			{
				potionTooGood = true;
			}
		}
	}
	if (CheckAttribute(chref, "GenQuest.Potion_choice"))
	{
		if (CheckCharacterItem(pchar, chref.GenQuest.Potion_choice))
		{
			DoCharacterUsedItem(pchar, chref.GenQuest.Potion_choice);
			return 1;
		}
		else
		{
//			PlaySound("interface\notebook.wav");
			log_info(XI_ConvertString("PotionMissing"));
			log_info(XI_ConvertString("AutoSelectActivate"));
			DeleteAttribute(pchar, "GenQuest.Potion_choice");
			return 0;
		}
	}
	else
	{
		if (curPotionID > 0)
		{
			DoCharacterUsedItem(pchar, Items[curPotionID].id);
			return 1;
		}
		else return 0;
	}
}

int FindQuestUsableItem(ref arFind, int startIdx)
{
	int i;
	aref arItm;
	bool bSeaInterface = bSeaActive && !bAbordageStarted;

	if(startIdx<0) startIdx=0;
	for(i=startIdx; i<ITEMS_QUANTITY; i++)
	{
		makearef(arItm,Items[i]);
		if( CheckAttribute(arItm,"quest") && CheckAttribute(arItm,"quest.tex"))// boal 16.03.2004
		{
			if( bSeaInterface && arItm.quest.tex=="QuestCommands" )
			{
				arFind = arItm;
				return i;
			}
		}
	}

	return -1;
}

bool EnablePotionUsing(ref mc, aref arItm)
{
	if (CheckAttribute(arItm, "potion.health") && LAi_GetCharacterHP(mc) < LAi_GetCharacterMaxHP(mc))
		return true;
	
	if (CheckAttribute(arItm, "potion.energy") && Lai_CharacterGetEnergy(mc) < LAi_GetCharacterMaxEnergy(mc))
		return true;
	
	return false;
}

// Warship 13.06.09 Для противоядий
bool EnableAntidoteUsing(ref _char, aref _item)
{
	if(CheckAttribute(_item, "potion.antidote") && LAi_IsPoison(_char) && CheckCharacterItem(_char, _item.Id))
	{
		return true;
	}
	
	return false;
}

bool FindCharacterAntidote(ref _char, ref _itemId)
{
	int itemIndex;
	ref item;
	
	for(itemIndex = 0; itemIndex < ITEMS_QUANTITY; itemIndex++)
	{
		item = &Items[itemIndex];
		
		if(EnableAntidoteUsing(_char, item))
		{
			_itemID = item.ID;
			return true;
		}
	}
	
	return false;
}

int FindItem(string sItemID)
{
/*
	for(int i = 0; i < TOTAL_ITEMS; i++)
	{
		if(CheckAttribute(&Items[i], "ID") && Items[i].id == sItemID)
		{
			return i;
		}
	}
	return -1;
*/	
	// Warship 07.07.09 Перевел на движковую функцию - по-идее, так должно работать быстрее
	return NativeFindCharacter(&Items, sItemID);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Warship 08.05.09 НОВАЯ СИСТЕМА ПРЕДМЕТОВ -->
//      Ugeen --> 10.02.10 добавлена первичная генерация предметов и выбор из массива сгенерированных предметов
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ugeen --> начальная генерация генерируемых предметов
void GenerateGenerableItems()
{
	ref itemRef;

	for(int i = 0; i < ITEMS_QUANTITY; i++)
	{
		itemRef = &Items[i];
		if (CheckAttribute(itemRef, "id") && CheckAttribute(itemRef, "Generation.Qty") && !CheckAttribute(itemRef, "GeneratedAll"))
		{
			if (sti(itemRef.Generation.Qty) < 1)
			{
				DeleteAttribute(itemRef, "Generation");
				continue;
			}
			
			for(int j = 0; j < sti(itemRef.Generation.Qty); j++) 
			{
				GenerateItem(itemRef.id);
			}	
			SetItemPrice(itemRef);
			itemRef.GeneratedAll = true;
		}		
	}
}

//ugeen --> вернём случайный ID сгенерированного зараннее предмета
string GetGeneratedItem(string _itemId)
{
	int itemsQty = 0;
	string generatedItems[TOTAL_ITEMS];
	
	if(!IsGenerableItem(_itemId)) // Генерящийся ли предмет
	{
		return _itemID;
	}
	
	for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		if(CheckAttribute(&Items[i], "DefItemID") && Items[i].DefItemID == _itemId)
		{
			generatedItems[itemsQty] = Items[i].ID;
			itemsQty++;
		}
	}
		
	if(itemsQty == 0)
	{
		return _itemId; // Ничего не нашлось
	}
		
	return generatedItems[rand(itemsQty - 1)];
}

//  вернём определённый ID сгенерированного предмета
string GetGeneratedItemNum(string _itemId, int Num)
{
	int itemsQty = 0;
	string generatedItems[TOTAL_ITEMS];
	
	if(!IsGenerableItem(_itemId)) // Генерящийся ли предмет
	{
		return _itemID;
	}
	
	for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		if(CheckAttribute(&Items[i], "DefItemID") && Items[i].DefItemID == _itemId)
		{
			generatedItems[itemsQty] = Items[i].ID;
			itemsQty++;
		}
	}
		
	if(itemsQty == 0 || itemsQty < Num)
	{
		return _itemId; // Ничего не нашлось
	}
				
	return generatedItems[itemsQty + Num];
}

void SetItemPrice(ref item)
{
	int priceMod;
	
	switch(item.FencingType)
	{
		case "FencingLight": // Лёгкое оружие
			priceMod = 4;
		break;
		
		case "Fencing": // Среднее оружие
			priceMod = 5;
		break;
		
		case "FencingHeavy": // Тяжёлое оружие
			priceMod = 7;
		break;
	}
	if(CheckAttribute(item, "Weight") && stf(item.Weight) > 0.0)
	{
		item.price = priceMod * (stf(item.dmg_min) * stf(item.dmg_max)) / stf(item.Weight);
	}	
}

// Создадим предмет, вернёт АйДи нового предмета
string GenerateItem(string _itemId)
{
	int i, defItemIndex, priceMod;
	int itemsQty = 0;
	int itemIndex = FindFirstEmptyItem();
	float minValue, maxValue, curMinDmg, curMaxDmg, curWeight;
	ref item, realItem;
	string generatedItems[TOTAL_ITEMS];
	
	if(!IsGenerableItem(_itemId)) // Генерящийся ли предмет
	{
		return _itemID;
	}
	
	if(itemIndex == -1) // Нету свободных слотов - вернём случайный существующий
	{
		for(i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
		{
			if(CheckAttribute(&Items[i], "DefItemID") && Items[i].DefItemID == _itemId)
			{
				generatedItems[itemsQty] = Items[i].ID;
				itemsQty++;
			}
		}
		
		if(itemsQty == 0)
		{
			return _itemId; // Ничего не нашлось
		}
		
		return generatedItems[rand(itemsQty - 1)];
	}
	
	defItemIndex = FindItem(_itemId);
	item = &Items[defItemIndex];
	realItem = &Items[itemIndex];
	
	CopyAttributes(realItem, item); // Копируем аттрибуты
	
	// Warship 06.06.09 Оптимизация - выкинул нафиг цикл
	
	// Минимальный урон
	minValue = stf(item.Generation.dmg_min.min); // Нижняя граница аттрибута
	maxValue = stf(item.Generation.dmg_min.max); // Верхняя граница аттрибута
	curMinDmg = minValue + frandsmall(maxValue - minValue);
	realItem.dmg_min = curMinDmg;
	
	// Максимальный урон
	minValue = stf(item.Generation.dmg_max.min); // Нижняя граница аттрибута
	maxValue = stf(item.Generation.dmg_max.max); // Верхняя граница аттрибута
	curMaxDmg = minValue + frandsmall(maxValue - minValue);
	realItem.dmg_max = curMaxDmg;
	
	// Вес
	minValue = stf(item.Generation.Weight.min); // Нижняя граница аттрибута
	maxValue = stf(item.Generation.Weight.max); // Верхняя граница аттрибута
	curWeight = minValue + frandsmall(maxValue - minValue);
	realItem.Weight = curWeight;

	// Генерим цену, если нужно
	if(CheckAttribute(item, "Generation.price") && sti(item.Generation.price) > 0)
	{
		switch(item.FencingType)
		{
			case "FencingLight": // Лёгкое оружие
				priceMod = 4;
			break;

			case "Fencing": // Среднее оружие
				priceMod = 5;
			break;

			case "FencingHeavy": // Тяжёлое оружие
				priceMod = 7;
			break;
		}
		realItem.price = priceMod * (curMinDmg * curMaxDmg) / curWeight;
	}
	
	realItem.ID = _itemId + "_" + itemIndex; // Новый АйДи предмету
	realItem.Index = itemIndex; // Новый индекс
	realItem.Generated = true; // Сгенерированный предмет
	realItem.DefItemID = _itemId; // Запомним АйДи и индекс начального предмета
	realItem.DefItemIndex = defItemIndex;
	
	return realItem.ID;
}

// Найдем первый пустой слот для предмета
int FindFirstEmptyItem()
{
	for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		if(!CheckAttribute(&Items[i], "ID") || Items[i].ID == "0")
		{
			return i;
		}
	}	
	return -1;
}

// Проверим на пустые предметы и удалим их
// Метод выполняется долго - лучше вызывать его при переходах между локациями (как щас и сделано)
void RefreshGeneratedItems()
{
	ref item;
	int curLastIndex = FindFirstEmptyItem();

	for(int i = ITEMS_QUANTITY; i < TOTAL_ITEMS; i++)
	{
		item = &Items[i];
		
		if(!CheckAttribute(item, "ID")) continue; // Пустой слот
		
		RefreshGeneratedItem(item.ID);
	}
	
	trace("Произведено удаление пустых предметов");
	trace("Первый свободный элемент (было/стало) == (" + curLastIndex + "/"+ FindFirstEmptyItem() + ")");
}

// Метод рефреша для конкретного предмета. Вернёт булево значение - удалился предмет или нет
bool RefreshGeneratedItem(string _itemID)
{
	int i, j;
	int itemIndex = FindItem(_itemID);
	string curSimpleBox, curPrivateBox;
	ref reference;
	
	if(itemIndex == -1) return false;

	for(i = 0; i < nLocationsNum; i++)
	{
		reference = &Locations[i];
		
		for(j = 1; j < MAX_HANDLED_BOXES; j++)
		{
			curSimpleBox = "box" + j;
			curPrivateBox = "private" + j;
			
			if(!CheckAttribute(reference, curSimpleBox) && !CheckAttribute(reference, curPrivateBox)) break;
			
			// Симпл боксы
			if(CheckAttribute(reference, curSimpleBox + ".Items." + _itemID))
			{
				return false;
			}
			
			// Приваты
			if(CheckAttribute(reference, curPrivateBox + ".Items." + _itemID))
			{
				return false;
			}
		}
	}
	
	for(i = 0; i < TOTAL_CHARACTERS; i++)
	{
		reference = &Characters[i];
			
		// Проверка на торговца, у которого уже можно отобрать предметы
		if(CheckAttribute(reference, "Merchant") && CheckNPCQuestDate(reference, "Item_date"))
		{
			DeleteAttribute(reference, "items");
			continue;
		}
		
		if(CheckAttribute(reference, "Items." + _itemID))
		{
			return false;
		}
	}
		
//	DeleteAttribute(&Items[itemIndex], ""); // Потрем все аттрибуты
	return true;
}

// Проверка, уникален ли каждый предмет "серии", или же идентичен
bool IsGenerableItem(string _itemID)
{
	int itemIndex = FindItem(_itemID);
	ref itemRef;
	
	if(itemIndex == -1)
	{
		return false;
	}
	
	itemRef = &Items[itemIndex];
	
	if(CheckAttribute(itemRef, "Generation") && !CheckAttribute(itemRef, "Generated"))
	{
		return true;
	}
	
	return false;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
//										<-- Warship НОВАЯ СИСТЕМА ПРЕДМЕТОВ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Warship Проверка на оружие
bool IsBlade(string _itemID)
{
	int itemIndex = FindItem(_itemID);
	ref item;
	
	if(itemIndex == -1)
	{
		return false;
	}
	
	item = &Items[itemIndex];

	if(CheckAttribute(&item, "groupID"))
	{
		if(item.groupID == BLADE_ITEM_TYPE)
		{
			return true;
		}
	}
	
	return false;
}

bool isPistol(string sItem)
{
	ref rItem = ItemsFromID(sItem);

	if (TestRef(rItem))
	{
		if (CheckAttribute(rItem, "groupID") && rItem.groupID == GUN_ITEM_TYPE)
			return true;
	}

	return false;
}

bool isMusket(string sItem)
{
	ref rItem = ItemsFromID(sItem);

	if (TestRef(rItem))
	{
		if (CheckAttribute(rItem, "groupID") && rItem.groupID == MUSKET_ITEM_TYPE)
			return true;
	}

	return false;
}

// eddy -->
/////////////////////// ==> Items-методы
ref ItemsFromID(string _Items)
{
	return &items[FindItem(_Items)];
}

void ChangeItemDescribe(string _Items, string _Describe)
{
    Items[FindItem(_Items)].describe = _Describe;
}

void BackItemDescribe(string _Items)
{
    ref ItemAR = ItemsFromID(_Items);
    ItemAR.describe = "itmdescr_" + ItemAR.id;
}

void ChangeItemName(string _Items, string _Name)
{
    Items[FindItem(_Items)].name = _Name;
}

void BackItemName(string _Items)
{
    ref ItemAR = ItemsFromID(_Items);
    ItemAR.name = "itmname_" + ItemAR.id;
}
///////////////////////  Items-методы <--


void QuestCheckEnterLocItem(aref _location, string _locator) /// <<<проверка вхождения ГГ в локаторы группы Item.<<<
{
	ref sld;
	int i;
	
	// dolphin ->
	if(_location.id == "FortFrance_Dungeon" && _locator == "detector1" && CheckAttribute(pchar, "MainQuest") && pchar.MainQuest == "FL1_s33")
	{
		DoQuestCheckDelay("FL1_s35", 0.1);
	}
	
	//======> Генератор инквизиции.
	if(_location.id == "Santiago_Incquisitio" && CheckNPCQuestDate(_location, "AttackGuard_date") && sti(Colonies[FindColony(_location.fastreload)].nation) == SPAIN && HasSubStr(_locator, "detector")) 
	{
		SetNPCQuestDate(_location, "AttackGuard_date"); //одна засада в день.
		LAi_group_AttackGroup("SPAIN_CITIZENS", LAI_GROUP_PLAYER);
		StartIncquisitioAttack();
		//==>фр.линейка, квест №7. Рок Бразилец, даем диалог.
		if(CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "Fr7RockBras_toSeekPlace") LAi_ActorWaitDialog(characterFromId("RockBrasilian"), pchar);
	}
	//=======> Квест Изабеллы, детектор на скрипт базара Сальватора с братом
	if(_location.id == "SanJuan_town" && CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "SeeTalkNearHouse") 
	{
        SeeBrotherDeadNearHouse();
	}
	//=======> Квест Изабеллы, закрываем дверь дома, если прошлялся не заходя домой более 3 месяцев
	if(_location.id == "SanJuan_town" && CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "NewLifeForHero") 
	{
		if (GetQuestPastMonthParam("RomanticQuest") > 3) 
		{
			LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true);
			pchar.RomanticQuest = "TheDoosIsClosed";
			ReOpenQuestHeader("Romantic_Line");
			AddQuestRecord("Romantic_Line", "29");
		}
	}
	//=======> Квест Изабеллы, закрываем дверь дома, если был у шлюх
	if(_location.id == "SanJuan_town" && CheckAttribute(pchar, "RomanticQuest.HorseCheck") && pchar.RomanticQuest.HorseCheck != "-1" && CheckAttribute(pchar, "questTemp.HorseQty") && sti(pchar.questTemp.HorseQty) > sti(pchar.RomanticQuest.HorseCheck))
	{
		LocatorReloadEnterDisable("SanJuan_town", "houseSp6", true);
		pchar.RomanticQuest = "over";
		pchar.RomanticQuest.HorseCheck = -1;
		ReOpenQuestHeader("Romantic_Line");
		AddQuestRecord("Romantic_Line", "29");
	}
	//======> Генератор маяка Порт-Ройал
	if(_location.id == "Mayak3" && StrStartsWith(_locator, "detector"))
	{
		int iNation = GetCityNation("PortRoyal");
		string sGroup = GetNationNameByType(iNation)  + "_mayak";
		LAi_group_AttackGroup(sGroup, LAI_GROUP_PLAYER);
	}
	//======> Генератор монстров при входе в локатор духов
	if(_locator == "duhi1" && CheckAttribute(_location, "locators.monsters") && CheckCharacterPerk(pchar, "WildCaribbean") && !bMonstersGen) // EvgAnat - дикие карибы
	{
		//проверяем флаг запрещения генерации
		if(LAi_LocationIsMonstersGen(_location) && LAi_grp_playeralarm == 0 && GenQuest_CheckMonstersGen()) 
		{
			SetSkeletonsToLocation(_location);
		}
	}
	//======> детектор в тюрьме, вторжение без разрешения
	if(_location.type == "jail" && CheckAttribute(pchar, "questTemp.jailCanMove") && !sti(pchar.questTemp.jailCanMove) && _locator == "detector1")
	{	
		pchar.questTemp.jailCanMove = true; //чтобы не срабатывало 2 раза
		if (!LAi_grp_alarmactive && !IsLocationCaptured(_location.id))
		{
			string slai_group = GetNationNameByType(GetCityNation(_location.parent_colony)) + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			LAi_SetFightMode(pchar, true);
		}
	}
	//======> установка метки нахождения в локаторе item1 в погребке
	if(CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "toInterception" && _location.id == "FleuronTavern" && _locator == "detector1")
	{
        pchar.questTemp.LSC.itemState = true;
	}
	//======> скафандр
	if(CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "toUnderwater" && _location.id == "FenixPlatform")
	{        
		if(CheckAttribute(&TEV, "LSC_UnderwaterSuit"))
		{	//смена со скафандра на норму
			bDisableFastReload = false;
			i = FindLocation("FenixPlatform");
			Locations[i].models.always.inside = "FenixPlatform";
			
			pchar.model.animation = pchar.questTemp.LSC.immersions.animation;
			if (CheckAttribute(pchar, "questTemp.LSC.immersions.cirassId"))
			{
				if (CheckCharacterItem(pchar, pchar.questTemp.LSC.immersions.cirassId))
					EquipCharacterByItem(pchar, pchar.questTemp.LSC.immersions.cirassId);
				DeleteAttribute(pchar, "questTemp.LSC.immersions.cirassId");
			}
			else RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);

			if (CheckAttribute(pchar, "questTemp.LSC.immersions.MushketID")) // Мушкетер
			{
				if (CheckCharacterItem(pchar, pchar.questTemp.LSC.immersions.MushketID))
					EquipCharacterByItem(pchar, pchar.questTemp.LSC.immersions.MushketID);
				DeleteAttribute(pchar, "questTemp.LSC.immersions.MushketID");
			}
			else RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);

			RemoveItems(pchar, "underwater", 1);
			DeleteAttribute(&TEV, "LSC_UnderwaterSuit");
			DeleteAttribute(pchar, "questTemp.LSC.immersions.model");
			DeleteAttribute(pchar, "questTemp.LSC.immersions.animation");

			LocatorReloadEnterDisable("LostShipsCity_town", "reload58", false);
			LocatorReloadEnterDisable("LostShipsCity_town", "reload73", true);
			DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload72", "");
		}
		else
		{	//смена с нормы на скафандр
			if (CheckAttribute(pchar, "questTemp.LSC.immersions.pay") && sti(pchar.questTemp.LSC.immersions.pay))
			{
				bDisableFastReload = true;
				i = FindLocation("FenixPlatform");
				Locations[i].models.always.inside = "FenixPlatform_wout";
				
				if (IsMusketer(PChar)) // Мушкетер
				{
					PChar.questTemp.LSC.immersions.MushketID = PChar.equip.musket;
                    RemoveCharacterEquip(PChar, MUSKET_ITEM_TYPE);
				}
				
				if (CheckAttribute(pchar, "cirassId"))
				{
					pchar.questTemp.LSC.immersions.cirassId = Items[sti(pchar.cirassId)].id;
				}
				pchar.questTemp.LSC.immersions.model = pchar.model;
				if (CheckAttribute(pchar, "HeroModel"))
				{
					pchar.questTemp.LSC.immersions.model = GetSubStringByNum(pchar.HeroModel, 0);
				}
				pchar.questTemp.LSC.immersions.animation = pchar.model.animation;
				
				GiveItem2Character(pchar, "underwater");
				pchar.model.animation = "armor";
				EquipCharacterByItem(pchar, "underwater");
				TEV.LSC_UnderwaterSuit = true;
				
				LocatorReloadEnterDisable("LostShipsCity_town", "reload58", true);
				LocatorReloadEnterDisable("LostShipsCity_town", "reload73", false);
				DoQuestReloadToLocation("LostShipsCity_town", "reload", "reload72", "");
			}
		}
	}
	//======> вхождение в локаторы для раскопок на кладбище в Курасао
    if(CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "FindGraveLSC" && _location.id == "Villemstad_Graveyard" && HasStr(_locator, "read"))
    {
        if (_locator == "read3")
        {
            Log_Info(StringFromKey("InfoMessages_64"));
            DoQuestCheckDelay("DiggingDoneLSC", 1.0);
        }
        else
        {
            //смотрим на деревянные кресты
            if (_locator == "read1" || _locator == "read4") Log_Info(StringFromKey("InfoMessages_65"));
            else Log_Info(StringFromKey("InfoMessages_66"));
        }
    }
	// проверяем пароль касперов - КПП Сан-Габриэль
	if (_locator == "parol1")
	{
		if (!CheckAttribute(pchar, "questTemp.LSC.parol_cpr") && GetCharacterIndex("CasperProt_2") != -1 && !LAi_group_IsEnemy(pchar, &characters[GetCharacterIndex("CasperProt_2")]))
		{
            sld = characterFromId("CasperProt_2");
            sld.dialog.currentnode = "Casper_parol";
            ParolGuardianTalk(sld);
        }
	}
	// проверяем пароль нарвалов - КПП Веласко
	if (_locator == "parol2")
	{
		if (!CheckAttribute(pchar, "questTemp.LSC.parol_nrv") && GetCharacterIndex("NarvalProt_6") != -1 && !LAi_group_IsEnemy(pchar, &characters[GetCharacterIndex("NarvalProt_6")]))
		{
            sld = characterFromId("NarvalProt_6");
            sld.dialog.currentnode = "Narval_parol";
            ParolGuardianTalk(sld);
        }
        if (pchar.questTemp.LSC == "toDestoyAllNarval" && !CheckAttribute(pchar, "questTemp.LSC.CheckParol"))
        {
            pchar.questTemp.LSC.CheckParol = true;
            sld = characterFromId("MentMush_8");
            ParolGuardianTalk(sld);
        }
	}
	// проверяем пароль касперов - КПП Церес Смити
	if (_locator == "parol3")
	{
		if (!CheckAttribute(pchar, "questTemp.LSC.parol_cpr") && GetCharacterIndex("CasperProt_3") != -1 && !LAi_group_IsEnemy(pchar, &characters[GetCharacterIndex("CasperProt_3")]))
		{
            sld = characterFromId("CasperProt_3");
            sld.dialog.currentnode = "Casper_parol";
            ParolGuardianTalk(sld);
        }
	}
	// путь гигочада, открытие каюты с касперами
	if (_locator == "casper")
	{
		if (pchar.questTemp.LSC == "toSeekMechanik" && !CheckAttribute(pchar, "questTemp.LSC.RivadosHelp") && !CheckAttribute(pchar, "questTemp.LSC.MentosHelp") && LSC_CheckDeceasedCaspers() == 0)
		{
			pchar.questTemp.LSC.TalkSelf_Start = true;
            DoQuestCheckDelay("TalkSelf_Start", 0.1);
        }
	}
	// локатор для удобного ожидания свидания каспарышей
	if (_locator == "wait")
	{
		if (CheckAttribute(pchar, "questTemp.LSC.Armo") && GetHour() > 2)
		{
		    if (sti(pchar.questTemp.LSC.Armo) == 1 || sti(pchar.questTemp.LSC.Armo) == 3 || sti(pchar.questTemp.LSC.Armo) == 5)
		    {
                pchar.questTemp.LSC.TalkSelf_Armo = true;
                DoQuestCheckDelay("TalkSelf_Start", 0.1);
		    }
        }
	}
}

void ParolGuardianTalk(ref sld)
{
    if (!LAi_IsDead(sld))
    {
        DoQuestCheckDelay("hide_weapon", 0.5);
        LAi_SetActorType(sld);
        LAi_ActorDialogNow(sld, pchar, "", -1);
    }
}

void QuestCheckExitLocItem(aref _location, string _locator) /// <<<проверка выхода ГГ из локаторов группы Item.<<<
{
	//=======> Испанская линейка, квест №4. В спальне нашёл возле комода нашёл недописанное письмо
	if(_location.id == "Havana_houseS1Bedroom" && CheckAttribute(pchar, "questTemp.State") && pchar.questTemp.State == "Sp4Detection_toMirderPlace" && CheckCharacterItem(pchar, "letter_notes"))
    {
        DoQuestCheckDelay("TalkSelf_Quest", 0.1); //диалог сам-на-сам
    }
	//=======> Квест Аскольда, нашли гробницу.
    if(_location.id == "Guadeloupe_Cave" && _locator == "detector1")
    {
        if(pchar.questTemp.Ascold == "Ascold_SeekGrave" || pchar.questTemp.Ascold == "Ascold_CantSeekGrave")
        {
            Log_QuestInfo("Прерывание на нахождение входа в пещеру сработало.");
            pchar.questTemp.Ascold = "Ascold_NotEnterFoundGrave";
    		DoQuestCheckDelay("TalkSelf_Quest", 0.1); //диалог сам-на-сам
        }
    }
	//=======> Квест Аскольда, ГГ добрался до мумии, но бутылки ещё не имеет. Вместо прерывания на локатор.
    if(_location.id == "Guadeloupe_Cave" && _locator == "button02")
    {
		if (pchar.questTemp.Ascold == "Ascold_SeekRockLetter" || pchar.questTemp.Ascold == "Ascold_EnterGrave")
		{
			pchar.questTemp.Ascold = "Ascold_FoundMummy";
			characters[GetCharacterIndex("Ascold")].dialog.currentnode = "Found_Grave";
			SetCurrentQuestMark(CharacterFromID("Ascold"));
		}
	}
	//=======> Энкаунтеры заманухи в пещеру, открываем закрытый релоад на колодце.
    if(_locator == "CheckReload1" && CheckAttribute(pchar, "GenQuest.OpenTheRopeExit") && pchar.GenQuest.OpenTheRopeExit == pchar.location)
    {
		DeleteAttribute(pchar, "GenQuest.OpenTheRopeExit");
		LocatorReloadEnterDisable(pchar.location, "reload2", false);
	}
	//=======> Изабелла, в доме начало скрипта с братом
    if(_location.id == "SanJuan_houseSp6" && CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "exitFromDetector")
    {
		pchar.RomanticQuest = "executeFromDetector";
		StartQuestMovie(true, true, true);
		// ГГ теперь Сальватор
		SetMainCharacterIndex(GetCharacterIndex("MigelDeValdes"));
        PChar   = GetMainCharacter();			
		locCameraToPos(-2.41, 2.35, -2.41, false);
		SetActorDialogAny2Pchar("Isabella", "", 3.0, 0.0);
		LAi_ActorFollow(PChar, CharacterFromID("Isabella"), "ActorDialog_Any2Pchar", 4.0);
	}
	//=======> Изабелла, в доме Роситы после смерти мужа
    if(_location.id == "Beliz_houseS4" && CheckAttribute(pchar, "RomanticQuest") && pchar.RomanticQuest == "Beliz_exitFromDetector")
    {
		pchar.RomanticQuest = "Beliz_executeFromDetector";
		StartQuestMovie(true, true, true);
        // ГГ теперь Изабелла
		ChangeCharacterAddressGroup(CharacterFromID("Isabella"), pchar.location, "goto",  "goto3");
		ChangeCharacterAddressGroup(CharacterFromID("Rosita"), pchar.location, "goto",  "goto1");
        SetMainCharacterIndex(GetCharacterIndex("Isabella"));
        PChar   = GetMainCharacter();			
        locCameraToPos(-3.84, 2.35, 0.85, false);
		LAi_SetActorType(CharacterFromID("Rosita"));
		LAi_SetActorType(pchar);
		PChar.BaseNation = SPAIN; //скрипт в городе, иначе глючит опрос патрулями
		SetActorDialogAny2Pchar("Rosita", "", 1.0, 0.0);
		LAi_ActorFollow(PChar, CharacterFromID("Rosita"), "ActorDialog_Any2Pchar", 0.0);
	}
	//=======> Пиратка, квест №5
    if(_location.id == "Pirates_houseS1" && CheckAttribute(pchar, "questTemp.piratesLine") && pchar.questTemp.piratesLine == "PL5Hunter_exitReload")
    {
		pchar.questTemp.piratesLine = "PL5Hunter_executeReload";
		StartQuestMovie(true, true, true);
		SetMainCharacterIndex(GetCharacterIndex("Orry"));
        PChar   = GetMainCharacter();			
		locCameraToPos(1.34, 2.1, 1.68, false);
		LAi_SetActorType(CharacterFromID("Aivory"));
		LAi_SetActorType(pchar);
		SetActorDialogAny2Pchar("Aivory", "", 3.0, 0.0);
		LAi_ActorFollow(PChar, CharacterFromID("Aivory"), "ActorDialog_Any2Pchar", 4.0);
	}
	//======> установка метки нахождения в локаторе item1 в погребке
	if(CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "toInterception" && _location.id == "FleuronTavern" && _locator == "detector1")
	{        
		pchar.questTemp.LSC.itemState = false;
	}
}

void QuestCheckUseButton(aref _location, string _locator, string _itemId) /// <<< квестовые действия при установке предметов в button <<<
{
    //==> Квест Аскольда, установка скрижалей для открытия входа в пещеру к гробнице.
    if(_location.id == "Guadeloupe_Cave" && _locator == "button01")
    {
		// AlexBlade > Ставим камушек навсегда
		Location_AddNewModel("Guadeloupe_Cave", "item", "item1", "StoneMap", "always", "", 0, true);
		DoQuestFunctionDelay("Ascold_OpenTheGrave", 1.5);
		LAi_SetActorType(pchar);
    }
    //==> Квест Аскольда, вскрытие гробницы кочергой.
    if(_location.id == "Guadeloupe_Cave" && _locator == "button02" && CheckAttribute(pchar, "questTemp.Ascold") && pchar.questTemp.Ascold == "Ascold_WateringMummy")
    {
        ref sld;
		for (int i=1; i<=3; i++)
        {
			sld = GetCharacter(NPC_GenerateCharacter("Enemy_"+i, "Draugr_"+(1+rand(8 - i)), "skeleton", "man", 30, PIRATE, 0, true));	
			sld.Ghost = 0.6;
			FantomMakeCoolFighter(sld, 30, 85, 85, GetRandSubString("vikingAxe,vikingSword"), "", 100); // AlexBlade - заберем пистоль
            LAi_SetWarriorType(sld);				
			LAi_group_MoveCharacter(sld, "EnemyFight");				
            ChangeCharacterAddressGroup(sld, pchar.location, "goto",  "goto"+i);	
        }
        LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
        LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
        LAi_group_SetCheck("EnemyFight", "Ascold_InGraveAfterFight");
        chrDisableReloadToLocation = true;
    }
    //==> Квест Аскольда, вскрытие лампы и появление Аззи на верфи 
    if(CheckAttribute(pchar, "questTemp.Ascold.ShipyarderColony") && _location.id == (pchar.questTemp.Ascold.ShipyarderColony + "_shipyard") && _locator == "button01")
    {
		LAi_SetActorType(PChar);
		DoQuestCheckDelay("TalkSelf_Quest", 0.2);
		Ascold_FreeAzzy_DelQuestMarks();
    }
	//==> Пиратка, квест №7
    if(_location.id == "PuertoPrincipe_town" && _locator == "button01")
    {
		ref loc = &locations[FindLocation("PuertoPrincipe_townhall")];
		loc.reload.l2.name = "reload2";
		loc.reload.l2.go = "PuertoPrincipe_town";
		loc.reload.l2.emerge = "reload9";
		loc.reload.l2.autoreload = "0";
		loc.reload.l2.label = "Street";
		DoQuestFunctionDelay("PQ7_loadToRecidence", 2.0);
	}
	//установки тотемов в храмах
    if(HasSubStr(_itemId, "Totem_"))
    {
		SetItemModelOnLocation(_location, _itemId, _locator);
		SetAztecUsedTotem(_location, _itemId, _locator);
	}
	//открываем доступ в храм к шотгану
    if(_itemId == "KnifeAztec")
    {
		SetItemModelOnLocation(_location, _itemId, _locator);
		LocatorReloadEnterDisable("Tenochtitlan", "reloadTemple31", false);
	}
}
//проверка взятия предметов из локатора item
void QuestCheckTakeItem(aref _location, string _itemId)
{
	//квест промышленного шпионажа не верфях
	ref sld;
	switch (_itemId)
	{
		case "ShipyardsMap":
			pchar.questTemp.different.ShipyardsMap = "toClient";
			AddQuestRecord("ShipyardsMap", "2");
			if (IsLoginTime() && !IsLocationCaptured(_location.id))
			{
				sld = characterFromId(_location.fastreload + "_shipyarder");
				sld.dialog.currentnode = "Allarm";
				LAi_SetActorType(pchar);
				LAi_ActorDialog(pchar, sld, "", 0, 0);
			}
		break;

		case "CaptainBook": //генератор - "Спихнуть судовые документы"
			ReOpenQuestHeader("GiveShipLetters");
			AddQuestRecord("GiveShipLetters", "1");
			AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("","а"));
		break;

		case "MayorsRing": //квест поиски кольца мэра в борделях
			AddQuestRecord("SeekMayorsRing", "6");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + pchar.questTemp.different.TakeMayorsRing.city + "Gen"));
		break;

		case "UsurersJew": //квест поиска драгоценного камня ростовщика
			string sTitle = _location.townsack + "UsurersJewel";
			AddQuestRecordEx(sTitle, "SeekUsurersJewel", "2");
		break;

		case "OpenBook": //пиратка, квест №7
			AddQuestRecord("Pir_Line_7_Soukins", "9");
			SaveCurrentQuestDateParam("questTemp.piratesLine");
			pchar.questTemp.piratesLine = "Soukins_catchBattleship";
			Pchar.quest.PQ7_setBattleShip.win_condition.l1 = "MapEnter";
			Pchar.quest.PQ7_setBattleShip.function = "PQ7_setBattleShip";

			RemoveLandQuestmark_Main(CharacterFromID("PuertoPrincipe_tavernkeeper"), "Pir_Line");
			RemoveLandQuestmark_Main(CharacterFromID("PuertoPrincipe_waitress"), "Pir_Line");
		break;

		case "letter_LSC_1": //линейка ГПК, разборки с представителем в Мариго
			pchar.questTemp.LSC = "readyGoLSC";
			sld = characterFromId("hol_guber"); //чтобы мог переезжать
			DeleteAttribute(sld, "notMoveAble");
			DeleteAttribute(&colonies[FindColony("Villemstad")], "notCaptured"); //Виллемстад можно себе
			int index = GetCharacterIndex("PoorKillSponsor");
			if(index != -1 && !LAi_IsDead(&characters[index]))
			{
				chrDisableReloadToLocation = true;
				LAi_LocationFightDisable(loadedLocation, false);
				LAi_group_Attack(&characters[index], pchar);
				pchar.quest.PQ8_afterFight.win_condition.l1 = "NPC_Death";
				pchar.quest.PQ8_afterFight.win_condition.l1.character = "PoorKillSponsor";
				pchar.quest.PQ8_afterFight.win_condition = "OpenTheDoors";
			}
			AddLandQuestMark_Main(CharacterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId), "ISS_PoorsMurder");
		break;

		case "admiralKey": //линейка ГПК, квест со скелетом Декстера. найденный ключ адмирала
			if (CheckAttribute(pchar, "questTemp.LSC.lostDecster") && pchar.questTemp.LSC.lostDecster == "admiralLostKey")
			{
				pchar.quest.LSC_admiralFoundOwnKey.over = "yes"; //снимаем таймер
				AddQuestRecord("LSC_findDekster", "12");
			}
		break;

		case "Totem_11": //меняем сеабед у Тено, снимаем 11 тотем
			_location.models.always.seabed = "TenochtitlanWout_sb";
		break;

		case "SkullAztec": //взятие нефритового черепа
			LoginDeadmansGod();
		break;

		case "pistol7": //взятие шотгана
			LoginShotgunGuards();
		break;

		case "Rock_letter": //взятие скрижалей, закрываем джунгли Гваделупы
			pchar.questTemp.Ascold.tmp_disable = true;
		break;

		case "WeddingRing": //Миниквест жителей. Поиск обручального кольца
			PChar.GenQuest.CitizenFindItem.GiveItem = true; // Флаг - взяли предмет
			AddQuestRecord("SeekCitizenRing", "2");
		break;

		case "keyQuestLSC": //Запись в СЖ при поднятии ключа от сундука Стевезанта
			AddQuestRecord("ISS_PoorsMurder", "6_1");
		break;

		case "migraine_potion": // Ускоренная проверка получения лекарства по Бладу
			PostEvent("evntQuestsCheck", 400);
		break;

		case "key3": // Метка на сундук в имении по Бладу
			if (sti(pchar.questTemp.CapBloodLine) && _location.id == "Estate")
			{
			    QuestPointerToLoc("Estate", "quest", "quest3");
			}
		break;

		case "MsStid_ring": // > взятие колечка миссис Стид
			chrDisableReloadToLocation = false;
		break;
	}
}

void StartIncquisitioAttack()
{
	ref sld;
    for (int i=1; i<=5; i++)
    {
		sld = GetCharacter(NPC_GenerateCharacter("IncqAddGuard_"+i, "elite_spa_"+(rand(2)+1), "man", "man", 35, SPAIN, 1, true)); //watch_quest_moment
		FantomMakeCoolFighter(sld, sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+8, 80, 70, BLADE_LONG, "pistol4", 50);
        LAi_SetWarriorType(sld);
        LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");            
        ChangeCharacterAddressGroup(sld, "Santiago_Incquisitio", "goto", LAi_FindRandomLocator("goto"));
    }
}

void SetItemModelOnLocation(ref loc, string model, string locator)
{
	loc.models.always.totem = model;
	loc.models.always.totem.locator.group = "item";
	loc.models.always.totem.locator.name = locator;
	loc.models.always.totem.tech = "DLightModel";
}

void OnLoadUpdateItemArrays()
{
    int i, j;
    ref rItem, rBackItem, sld;
    int backSize = GetArraySize(&Items);

    //сохраняем существующий массив
    object backItems[2];
    SetArraySize(&backItems, backSize);
    for (i = 0; i < backSize; i++)
    {
        backItems[i] = Items[i];
    }

    //расширяем и перениничиваем старый массив
    SetArraySize(&itemModels, ITEMS_QUANTITY);
    SetArraySize(&Items, TOTAL_ITEMS);
    if (LoadSegment("items\initItems.c"))
    {
        InitItems();
        UnloadSegment("items\initItems.c");
    }

    //переносим в переиниченный массив данные по предметам. что бы не потерять их расположение и прочие изменения
    for (i = 0; i < TOTAL_ITEMS; i++)
    {
        makeref(rItem, Items[i]);
        for (j = 0; j < backSize; j++)
        {
            makeref(rBackItem, backItems[j]);
            if (CheckAttribute(rItem, "id") && CheckAttribute(rBackItem, "id") && rItem.id == rBackItem.id)
            {
                rItem = backItems[j];
                break;
            }
        }
    }
    //обновляем индекс надетых кирас
    for (i = 0; i < MAX_CHARACTERS; i++)
    {
        makeref(sld, characters[i]);
        if (CheckAttribute(sld, "cirassId"))
            sld.cirassId = FindItem(backItems[sti(sld.cirassId)].id);
    }
}

// проверка - знает ли ГГ рецепт мультиобъекта
bool isMultiObjectKnown(string sItem)
{
	ref rItem = &Items[FindItem(sItem)];

	if (TestRef(rItem) && CheckAttribute(rItem, "craft") && rItem.craft == "1" && CheckAttribute(pchar, "alchemy." + sItem + ".isKnown") && pchar.alchemy.(sItem).isKnown == "1")
		return true;

	return false;
}

void SetAlchemyRecipeKnown(string Recipe)
{
	pchar.alchemy.(Recipe).isKnown = true;
}

// > инициализации рецептуры по алхимии
//	result - что хотим получить (после знака ":" - сколько; отсутствие заданного кол-ва считается за 1)
//	components - необходимые компоненты (после знака ":" - сколько, пример: "bullet:7, GunPowder:14"; отсутствие заданного кол-ва считается за 1)
//	инструменты (не удаляются при крафте) можно выделить дописав после их id ":tool", пример: "bullet:2, crucible:tool, bullet_mold:tool, lamp:tool", кол-во указывать не нужно - всегда требуется только 1 шт. инструмента
//	для визуального удобства везде можно писать с пробелами, они потрутся автоматически
void InitAlchemyComponents(string result, string components)
{
	int iQty = 1;
	result = stripblank(result);
	components = stripblank(components);

	if (HasStr(result, ":"))
	{
		iQty = sti(FindStringAfterChar(result, ":"));
		result = FindStringBeforeChar(result, ":");
	}

	Restrictor(&iQty, 1, "");

	ref rItem = ItemsFromID(result);
	rItem.craft = true;
	rItem.craft.id = result;
	rItem.craft.components = components;
	rItem.craft.qty = iQty;

	// > пометим, что есть что
	int n, q = KZ|Symbol(components, ",");
	string sA, sB, sItem = components;

	for (n = 0; n <= q; n++)
	{
		if (q > 0)
			sItem = GetSubStr(components, ",", n);

		if (HasStr(sItem, ":"))
		{
			sA = FindStringAfterChar(sItem, ":");
			sB = FindStringBeforeChar(sItem, ":");
			rItem = ItemsFromID(sB);

			if (HasStrEx(sA, "tool,cat", "|"))
			{
				if (HasStr(sA, "tool"))
					rItem.craft.tool = true;		// > инструмент
				else
					rItem.craft.catalyst = true;	// > катализатор // TODO
			}
			else
				rItem.craft.ingredient = true;		// > ингредиент
		}
		else
		{
			rItem = ItemsFromID(sItem);
			rItem.craft.ingredient = true;			// > ингредиент
		}
	}
}

// > рецептура по алхимии
void InitAlchemyCraft()
{
	//						result: qty			components
	InitAlchemyComponents("grapeshot", 			"bullet:5, crucible:tool, bullet_mold:tool");											// "Картечь"
	InitAlchemyComponents("cartridge", 			"bullet, GunPowder");																	// "Бумажный патрон"
	InitAlchemyComponents("harpoon:2", 			"mineral14, mineral11, mechanic_kit:tool");												// "Стрела"
	InitAlchemyComponents("GunEchin:3", 		"GunPowder:6, mineral3, mineral16, mechanic_kit:tool, crucible:tool, lamp:tool");		// "Ежовый заряд"

	InitAlchemyComponents("petard", 			"mineral13, GunPowder:10, mineral3, mineral12, mechanic_kit:tool");						// "Петарда"
	InitAlchemyComponents("grenade", 			"mineral13, GunPowder:10, bullet:15, mineral3, mineral12, mechanic_kit:tool");			// "Граната"

	InitAlchemyComponents("GunPowder_colt", 	"GunPowder:4, mortar_and_pestle:tool");													// "Револьверный порох"
	InitAlchemyComponents("bullet_colt", 		"bullet:4, crucible:tool, bullet_mold:tool, lamp:tool");								// "Револьверная пуля"
	InitAlchemyComponents("GunCap_colt:15", 	"mineral13, fulminate_silver, mechanic_kit:tool, crucible:tool, lamp:tool");			// "Капсюли"
	InitAlchemyComponents("cartridge_colt", 	"bullet_colt, GunPowder_colt, mineral3, tailor_kit:tool");								// "Револьверный картридж"

	InitAlchemyComponents("fulminate_silver",	"jewelry17, nitric_acid, ethanol, alchemy_kit:tool, lamp:tool");						// "Гремучее серебро"

	InitAlchemyComponents("migraine_potion",	"herb_matricaria, herb_zingiber:2, mortar_and_pestle:tool, lamp:tool");					// "Лекарство от мигрени"
	InitAlchemyComponents("potion1",			"herb_matricaria, herb_zingiber, potion5, mortar_and_pestle:tool");						// "Лечебное зелье"

	InitAlchemyComponents("potionsangari:2", 	"potionwine:2, potionrum, indian4");													// Коктейль "Сангари" (2 вина + 1 ром)
}

// KZ > Вернуть конкретные предметы на труп rChar при его обыске
void AddKeepItems(ref rChar)
{
	if (!CheckAttribute(rChar, "KeepItems")) return;

	aref arKeepItems, arItem;
	makearef(arKeepItems, rChar.KeepItems);

	int q, j, i = GetAttributesNum(arKeepItems);
	string sItem = "";

	if (i > 0)
	{
		for (j = 0; j < i; j++)
		{
			arItem = GetAttributeN(arKeepItems, j);
			sItem = GetAttributeName(arItem);
			q = sti(GetAttributeValue(arItem));

			if (q > 0 && FindItem(sItem) >= 0)
				rChar.items.(sItem) = "" + q;
		}
	}

	DeleteAttribute(rChar, "KeepItems");	
}

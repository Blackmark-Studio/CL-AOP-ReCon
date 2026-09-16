/*
KZ FreeStores > магазины без привязки к колонии и нации ("свободные")

Слоты FREE_STORE_FIRST..STORE_QUANTITY-1 массива stores[] стоят пустыми, пока их не занял CreateFreeStore().
Ключом свободного магазина остаётся его собственный атрибут Colony:
колонии с таким id нет, поэтому колониальные механизмы (дипломатия, захват города, торговая книга, бумажная карта) его не видят,
а всё, что считается от самого магазина - ассортимент, цены, деньги, склад, контрабанда, прайс-лист - работает как у колониального.

Пример работы (все три функции идемпотентны, звать можно хоть при каждом входе в локацию):
    int iStore = CreateFreeStore("SmugglerCove", "small", "Shore66");
    FreeStoreSetTrade(iStore, TRADE_TYPE_EXPORT,     GOOD_RUM);
    FreeStoreSetTrade(iStore, TRADE_TYPE_CONTRABAND, GOOD_POWDER);
    FreeStoreFill(iStore, false);	// товар, цены и деньги; true - осознанный перезавоз
    ...
    LaunchStore(iStore);			// торговля; склад - LaunchStorage(iStore)

Запрет торговли отдельными товарами (режим считается со стороны магазина, действует во всех трёх окнах - товары, контрабанда, орудия):
    FreeStoreSetTradeAll(iStore, FREE_STORE_TRADE_NONE);				// магазин не торгует ничем
    FreeStoreSetGoodTrade(iStore, GOOD_RUM,  FREE_STORE_TRADE_SELL);	// ром только продаёт
    FreeStoreSetGoodTrade(iStore, GOOD_HIDE, FREE_STORE_TRADE_BUY);		// шкуры только покупает
    FreeStoreSetViewAll(iStore, true, argb(255, 160, 160, 160));		// остальное показывать без цен и серым, а не прятать
	FreeStoreSetBookView(iStore, true);									// то же в торговом разделе судового журнала: один переключатель на магазин

Заголовок торгового окна: по умолчанию берётся ключ "Colony" + id (то есть, например, достаточно добавить в common.ini строку string = ColonySmugglerCove, "Бухта контрабандистов").
Можно задать и напрямую: Stores[iStore].titlekey = <ключ в common.ini> или Stores[iStore].titlename = "Готовая строка".

NPC-торговцу достаточно ch.StoreNum = iStore - диалог Common_Store.c берёт магазин оттуда, если ch.City не колония.
ch.nation ставить обязательно константой нации: sti("none") == 0 == ENGLAND, нейтральный вариант - PIRATE.
*/

// > сколько слотов реально в массиве: сейв старой сборки приезжает короче
int GetStoreSlotsNum()
{
	int iNum = GetArraySize(&Stores);
	if (iNum > STORE_QUANTITY) iNum = STORE_QUANTITY;
	return iNum;
}

// > индекс свободного слота, который реально есть в массиве
bool IsFreeStoreNum(int iStore)
{
	return iStore >= FREE_STORE_FIRST && iStore < GetStoreSlotsNum();
}

// > свободный слот, в котором реально стоит магазин; пустой слот магазином не считается
bool IsFreeStoreOccupied(int iStore)
{
	if (!IsFreeStoreNum(iStore)) return false;
	if (!CheckAttribute(&Stores[iStore], "id")) return false;
	return Stores[iStore].id != "";
}

// > занятый свободный слот по объекту: интерфейсы держат только ref
bool IsFreeStore(ref pStore)
{
	if (!CheckAttribute(pStore, "index")) return false;
	return IsFreeStoreOccupied(sti(pStore.index));
}

// > трюм встречного торговца в море, а не лавка на берегу
bool IsSeaTradeStore(ref pStore)
{
	if (CheckAttribute(pStore, "index")) return sti(pStore.index) == SHIP_STORE;
	return CheckAttribute(pStore, "Colony") && pStore.Colony == "none"; // > объект собран не InitStores
}

// > подпись магазина в заголовке торгового окна
string GetStoreTitleName(ref pStore)
{
	if (CheckAttribute(pStore, "titlename")) return pStore.titlename;							// > готовая строка
	if (CheckAttribute(pStore, "titlekey"))  return XI_ConvertString(pStore.titlekey);			// > свой ключ common.ini
	if (CheckAttribute(pStore, "Colony"))    return XI_ConvertString("Colony" + pStore.Colony);	// > колониальный магазин
	return "";
}

// > индекс свободного магазина по его id, -1 если такого нет
int FindFreeStore(string sId)
{
	if (sId == "") return -1;

	int iNum = GetStoreSlotsNum();
	for (int i = FREE_STORE_FIRST; i < iNum; i++)
	{
		if (!IsFreeStoreOccupied(i)) continue;
		if (Stores[i].id == sId) return i;
	}
	return -1;
}

// > привести слот к виду незанятого
void FreeStoreClear(int iStore)
{
	if (!IsFreeStoreNum(iStore)) return;

	ref rStore = &Stores[iStore];

	DeleteAttribute(rStore, "");

	rStore.index         = iStore;
	rStore.StoreNum      = iStore; // > SetPriceList берёт номер магазина из самого объекта
	rStore.Colony        = "";     // > пустая строка, а не "none": "none" - это торговля в море
	rStore.group         = FREE_STORE_NO_GROUP; // > не "": пустая группа совпала бы с пустым fastreload
	rStore.StoreSize     = "";     // > без размера FillStoreGoods слот не наполняет
	rStore.money         = 0;
	rStore.smugglerMoney = 0;
}

// > занять свободный слот.
// > sSize - "large"/"medium"/"small"
// > sGroup - группа локации (Locations[n].fastreload), по ней магазин находят контрабандисты; можно оставить "".
// > возвращает номер магазина для Launch* или -1.
int CreateFreeStore(string sId, string sSize, string sGroup)
{
	if (sId == "" || sId == "none" || HasSubStr(sId, ".")) // > "none" - торговля в море; точка - разделитель веток атрибутов
	{
		trace("ERROR CreateFreeStore: пустой, зарезервированный или содержащий точку id магазина");
		return -1;
	}

	int iStore = FindFreeStore(sId);
	if (iStore >= 0) return iStore; // > уже заведён, отдаём как есть

	if (FindColony(sId) >= 0 || FindStore(sId) >= 0)
	{
		trace("ERROR CreateFreeStore: id '" + sId + "' уже занят колонией или магазином");
		return -1;
	}

	string sStoreSize = sSize;
	if (sStoreSize != "large" && sStoreSize != "medium" && sStoreSize != "small") sStoreSize = "small";

	int iNum = GetStoreSlotsNum();
	for (int i = FREE_STORE_FIRST; i < iNum; i++)
	{
		if (IsFreeStoreOccupied(i)) continue; // > слот занят
		iStore = i;
		break;
	}

	if (iStore < 0)
	{
		trace("ERROR CreateFreeStore: свободных слотов нет, поднимите FREE_STORE_QUANTITY в store.h");
		return -1;
	}

	FreeStoreClear(iStore);

	ref rStore = &Stores[iStore];
	rStore.id        = sId;
	rStore.Colony    = sId; // > ключ магазина
	rStore.group     = sGroup;
	if (sGroup == "") rStore.group = FREE_STORE_NO_GROUP; // > группа не задана - ставим ту, что ни с чем не совпадёт
	rStore.StoreSize = sStoreSize;
	rStore.free      = true;
	StoreVoidFill(rStore); // > тот же набор Goods, что у колониальных

	trace("CreateFreeStore: магазин '" + sId + "' занял слот " + iStore);
	return iStore;
}

// > снять товар с одного списка Trade.<ветка>: на место снятой записи переносим последнюю,
// > чтобы нумерация idN осталась сплошной - бумажная карта читает Trade.*.id1..id3 по именам
void FreeStoreTradeListDel(ref rStore, string sBranch, int iGood)
{
	if (!CheckAttribute(rStore, "Trade." + sBranch)) return;

	aref arList;
	makearef(arList, rStore.Trade.(sBranch));

	int iListNum = GetAttributesNum(arList);
	string sHole, sLast;

	for (int n = 0; n < iListNum; n++)
	{
		if (sti(GetAttributeValue(GetAttributeN(arList, n))) != iGood) continue;

		sHole = GetAttributeName(GetAttributeN(arList, n));
		sLast = GetAttributeName(GetAttributeN(arList, iListNum - 1));

		if (sHole != sLast) arList.(sHole) = sti(GetAttributeValue(GetAttributeN(arList, iListNum - 1)));
		DeleteAttribute(arList, sLast);
		if (GetAttributesNum(arList) == 0) DeleteAttribute(rStore, "Trade." + sBranch); // > пустую ветку не держим
		return; // > больше одной записи на товар в списке не бывает, перебор после удаления не нужен
	}
}

// > товар в ассортимент.
// > iTradeType: EXPORT/IMPORT/CONTRABAND попадают в списки Trade.*, которые разворачивает FillStoreGoods;
// > NORMAL/AMMUNITION/CANNONS ставятся товару напрямую.
void FreeStoreSetTrade(int iStore, int iTradeType, int iGood)
{
	if (!IsFreeStoreNum(iStore)) return; // > -1 от неудачного CreateFreeStore: молча, без спама

	if (!IsFreeStoreOccupied(iStore))
	{
		trace("ERROR FreeStoreSetTrade: слот " + iStore + " не заведён, сначала CreateFreeStore()");
		return;
	}

	if (iGood < 0 || iGood >= GOODS_QUANTITY) return;

	ref rStore = &Stores[iStore];
	string sGood = Goods[iGood].Name;
	string sBranch = "";

	switch (iTradeType)
	{
		case TRADE_TYPE_EXPORT:     sBranch = "Export";     break;
		case TRADE_TYPE_IMPORT:     sBranch = "Import";     break;
		case TRADE_TYPE_CONTRABAND: sBranch = "Contraband"; break;
	}

	rStore.Goods.(sGood).TradeType = iTradeType; // > верный тип и до FreeStoreFill

	// > товар должен лежать ровно в одном списке: FillStoreGoods разворачивает все ветки Trade подряд,
	// > и запись из старой ветки вернула бы прежний тип поверх нашего
	if (sBranch != "Export")     FreeStoreTradeListDel(rStore, "Export",     iGood);
	if (sBranch != "Import")     FreeStoreTradeListDel(rStore, "Import",     iGood);
	if (sBranch != "Contraband") FreeStoreTradeListDel(rStore, "Contraband", iGood);

	if (sBranch == "") return; // > NORMAL/AMMUNITION/CANNONS в списках не хранятся

	// > список для FillStoreGoods: имя атрибута любое, значение - индекс товара
	aref arList;
	makearef(arList, rStore.Trade.(sBranch));

	// > повтор не добавляем
	int iListNum = GetAttributesNum(arList);
	for (int n = 0; n < iListNum; n++)
	{
		if (sti(GetAttributeValue(GetAttributeN(arList, n))) == iGood) return;
	}

	// > нумерация с id1, как у колониальных магазинов в store_init.c
	string sSlot;
	for (int i = 1; i <= GOODS_QUANTITY; i++)
	{
		sSlot = "id" + i;
		if (CheckAttribute(arList, sSlot)) continue;
		arList.(sSlot) = iGood;
		break;
	}
}

// > запрет торговли живёт в ветке Stores[i].TradeBan.<товар>:
// > .mode - режим FREE_STORE_TRADE_*,
// > .show и .color - как показывать товар с режимом NONE.
// > нет ветки - обычная торговля.

// > что магазину разрешено с этим товаром
int GetStoreGoodTradeMode(ref rStore, int iGood)
{
	if (iGood < 0 || iGood >= GOODS_QUANTITY) return FREE_STORE_TRADE_BOTH;

	string sGood = Goods[iGood].Name;
	if (!CheckAttribute(rStore, "TradeBan." + sGood + ".mode")) return FREE_STORE_TRADE_BOTH;

	int iMode = sti(rStore.TradeBan.(sGood).mode);
	if (iMode < FREE_STORE_TRADE_BOTH || iMode > FREE_STORE_TRADE_NONE) return FREE_STORE_TRADE_BOTH; // > мусор в атрибуте торговлю не глушит

	return iMode;
}

// > магазин продаёт этот товар, то есть ГГ может его купить
bool StoreCanSellGood(ref rStore, int iGood)
{
	int iMode = GetStoreGoodTradeMode(rStore, iGood);
	return iMode == FREE_STORE_TRADE_BOTH || iMode == FREE_STORE_TRADE_SELL;
}

// > магазин покупает этот товар, то есть ГГ может его продать
bool StoreCanBuyGood(ref rStore, int iGood)
{
	int iMode = GetStoreGoodTradeMode(rStore, iGood);
	return iMode == FREE_STORE_TRADE_BOTH || iMode == FREE_STORE_TRADE_BUY;
}

// > товар вне торговли не показываем вовсе - ни в списке магазина, ни в списке трюма
bool IsStoreGoodHidden(ref rStore, int iGood)
{
	if (GetStoreGoodTradeMode(rStore, iGood) != FREE_STORE_TRADE_NONE) return false;

	string sGood = Goods[iGood].Name;
	if (CheckAttribute(rStore, "TradeBan." + sGood + ".show")) return sti(rStore.TradeBan.(sGood).show) == 0;

	return FREE_STORE_BAN_SHOW == 0;
}

// > то же для торгового раздела судового журнала: там переключатель один на весь магазин
bool IsStoreGoodBookHidden(ref rStore, int iGood)
{
	if (GetStoreGoodTradeMode(rStore, iGood) != FREE_STORE_TRADE_NONE) return false;

	if (CheckAttribute(rStore, "TradeBan.book")) return sti(rStore.TradeBan.book) == 0;

	return FREE_STORE_BOOK_SHOW == 0;
}

// > цвет строки товара вне торговли, если его всё же показываем
int GetStoreGoodBanColor(ref rStore, int iGood)
{
	if (iGood < 0 || iGood >= GOODS_QUANTITY) return argb(255, 255, 255, 255);

	string sGood = Goods[iGood].Name;
	if (CheckAttribute(rStore, "TradeBan." + sGood + ".color")) return sti(rStore.TradeBan.(sGood).color);

	return argb(255, FREE_STORE_BAN_COLOR_R, FREE_STORE_BAN_COLOR_G, FREE_STORE_BAN_COLOR_B);
}

// > снять поле запрета и не держать в сейве ветки, которые от этого опустели
void FreeStoreBanDel(ref rStore, string sGood, string sField)
{
	if (!CheckAttribute(rStore, "TradeBan." + sGood)) return;

	if (CheckAttribute(rStore, "TradeBan." + sGood + "." + sField)) DeleteAttribute(rStore, "TradeBan." + sGood + "." + sField);

	aref arGood;
	makearef(arGood, rStore.TradeBan.(sGood));
	if (GetAttributesNum(arGood) > 0) return;

	DeleteAttribute(rStore, "TradeBan." + sGood);

	aref arBan;
	makearef(arBan, rStore.TradeBan);
	if (GetAttributesNum(arBan) == 0) DeleteAttribute(rStore, "TradeBan");
}

// > запретить или разрешить торговлю одним товаром, iMode - FREE_STORE_TRADE_*
void FreeStoreSetGoodTrade(int iStore, int iGood, int iMode)
{
	if (!IsFreeStoreNum(iStore)) return; // > -1 от неудачного CreateFreeStore: молча, без спама

	if (!IsFreeStoreOccupied(iStore))
	{
		trace("ERROR FreeStoreSetGoodTrade: слот " + iStore + " не заведён, сначала CreateFreeStore()");
		return;
	}

	if (iGood < 0 || iGood >= GOODS_QUANTITY) return;
	if (iMode < FREE_STORE_TRADE_BOTH || iMode > FREE_STORE_TRADE_NONE) return;

	ref rStore = &Stores[iStore];
	string sGood = Goods[iGood].Name;

	if (iMode != FREE_STORE_TRADE_BOTH)
	{
		rStore.TradeBan.(sGood).mode = iMode;
		return;
	}

	FreeStoreBanDel(rStore, sGood, "mode"); // > обычную торговлю в сейве не держим, свой вид строки при этом остаётся
}

// > то же сразу по всем товарам: магазин заводят запретом на всё, дальше разрешают точечно
void FreeStoreSetTradeAll(int iStore, int iMode)
{
	if (!IsFreeStoreNum(iStore)) return;

	if (!IsFreeStoreOccupied(iStore))
	{
		trace("ERROR FreeStoreSetTradeAll: слот " + iStore + " не заведён, сначала CreateFreeStore()");
		return;
	}

	for (int i = 0; i < GOODS_QUANTITY; i++)
	{
		FreeStoreSetGoodTrade(iStore, i, iMode);
	}
}

// > как показывать товар, которым магазину торговать нельзя вовсе:
// > bShow false - строки в списках нет, true - строка есть, но без цен; iColor - её цвет, 0 - общий цвет из store.h
void FreeStoreSetGoodView(int iStore, int iGood, bool bShow, int iColor)
{
	if (!IsFreeStoreNum(iStore)) return;

	if (!IsFreeStoreOccupied(iStore))
	{
		trace("ERROR FreeStoreSetGoodView: слот " + iStore + " не заведён, сначала CreateFreeStore()");
		return;
	}

	if (iGood < 0 || iGood >= GOODS_QUANTITY) return;

	ref rStore = &Stores[iStore];
	string sGood = Goods[iGood].Name;

	if (bShow) rStore.TradeBan.(sGood).show = 1;
	else       rStore.TradeBan.(sGood).show = 0;

	if (iColor != 0) rStore.TradeBan.(sGood).color = iColor;
	else             FreeStoreBanDel(rStore, sGood, "color"); // > свой цвет снят, дальше берётся общий
}

// > то же сразу по всем товарам
void FreeStoreSetViewAll(int iStore, bool bShow, int iColor)
{
	if (!IsFreeStoreNum(iStore)) return;

	if (!IsFreeStoreOccupied(iStore))
	{
		trace("ERROR FreeStoreSetViewAll: слот " + iStore + " не заведён, сначала CreateFreeStore()");
		return;
	}

	for (int i = 0; i < GOODS_QUANTITY; i++)
	{
		FreeStoreSetGoodView(iStore, i, bShow, iColor);
	}
}

// > как показывать товары, которыми магазин не торгует, в торговом разделе судового журнала:
// > bShow false - строки нет, true - строка есть, но без цен и цветом запрета. Переключатель один на весь магазин
void FreeStoreSetBookView(int iStore, bool bShow)
{
	if (!IsFreeStoreNum(iStore)) return;

	if (!IsFreeStoreOccupied(iStore))
	{
		trace("ERROR FreeStoreSetBookView: слот " + iStore + " не заведён, сначала CreateFreeStore()");
		return;
	}

	if (bShow) Stores[iStore].TradeBan.book = 1;
	else       Stores[iStore].TradeBan.book = 0;
}

// > разложить количество товара, надбавки к цене и деньги.
// > второй вызов ничего не делает; bForce - осознанный перезавоз (квест, событие).
bool FreeStoreFill(int iStore, bool bForce)
{
	if (!IsFreeStoreNum(iStore)) return false;

	if (!IsFreeStoreOccupied(iStore))
	{
		trace("ERROR FreeStoreFill: слот " + iStore + " не заведён, сначала CreateFreeStore()");
		return false;
	}

	if (CheckAttribute(&Stores[iStore], "filled") && !bForce) return true; // > уже наполнен

	FillStoreGoods(&Stores[iStore]); // > живёт в главном сегменте (storeutilite.c), сегменты не трогаем

	Stores[iStore].filled = true;
	return true;
}

// > освободить слот
// > товар со склада уходит ГГ в трюм его кораблей, вещи и золото - в карманы
bool DeleteFreeStore(string sId)
{
	int iStore = FindFreeStore(sId);
	if (iStore < 0) return false;

	if (GetStorageUsedWeight(&Stores[iStore]) > 0) SetStorageGoodsToShip(&Stores[iStore]);
	if (CheckAttribute(&NullCharacter, "PriceList." + sId)) DeleteAttribute(&NullCharacter, "PriceList." + sId);

	// > хранилище предметов
	if (CheckAttribute(&Stores[iStore], "items"))
	{
		aref arItems;
		makearef(arItems, Stores[iStore].items);
		int iItemsNum = GetAttributesNum(arItems);
		int iMoved = 0;
		string sItem;
		int iQty, iItem;
		for (int n = 0; n < iItemsNum; n++)
		{
			sItem = GetAttributeName(GetAttributeN(arItems, n));
			iQty  = sti(GetAttributeValue(GetAttributeN(arItems, n)));
			if (iQty <= 0) continue;
			if (sItem == "gold")
			{
				AddMoneyToCharacter(pchar, iQty);
				iMoved++;
				continue;
			}
			iItem = FindItem(sItem);
			if (iItem < 0)
			{
				trace("DeleteFreeStore: на складе магазина '" + sId + "' неизвестный предмет '" + sItem + "', позиция снята");
				continue;
			}
			// > второй тотем или часть карты TakeNItems молча не даёт, как и везде в игре
			if (or(HasSubStr(sItem, "Totem_"), HasSubStr(sItem, "map_part")) && GetCharacterItem(pchar, sItem) > 0)
			{
				trace("DeleteFreeStore: дубль '" + sItem + "' со склада магазина '" + sId + "' отброшен - у ГГ такой уже есть");
				continue;
			}
			if (TakeNItems(pchar, sItem, iQty)) iMoved++;
			else trace("DeleteFreeStore: предмет '" + sItem + "' x" + iQty + " со склада магазина '" + sId + "' не принят TakeNItems");
		}
		if (iMoved > 0) trace("DeleteFreeStore: со склада предметов магазина '" + sId + "' передано ГГ позиций: " + iMoved);
	}

	FreeStoreClear(iStore);
	trace("DeleteFreeStore: магазин '" + sId + "' снят со слота " + iStore);
	return true;
}

// > город торговца - колония?
bool IsColonyTrader(ref rTrader)
{
	if (!CheckAttribute(rTrader, "city")) return false;
	return FindColony(rTrader.city) >= 0;
}

// > номер свободного магазина по его торговцу, -1 если торговец не от свободного магазина
int GetTraderFreeStore(ref rTrader)
{
	if (!CheckAttribute(rTrader, "StoreNum")) return -1;
	if (IsColonyTrader(rTrader)) return -1;

	int iStore = sti(rTrader.StoreNum);
	if (!IsFreeStoreOccupied(iStore)) return -1;

	return iStore;
}

// > номер магазина торговца для Launch* и для складов
int GetTraderStoreNum(ref rTrader)
{
	if (!CheckAttribute(rTrader, "StoreNum")) return -1;

	int iStore = sti(rTrader.StoreNum);
	if (iStore >= 0 && iStore <= SHIP_STORE) return iStore;
	if (IsFreeStoreOccupied(iStore)) return iStore;

	return -1;
}

// > торговец свободного магазина?
// > для мест, где такой магазин участвовать не должен вовсе
bool IsFreeStoreTrader(ref rTrader)
{
	return GetTraderFreeStore(rTrader) >= 0;
}

// > пускать ли NPC в генераторные квесты - целью (фрахт, сундуки ростовщика, разговоры о ценах) и источником.
// > NPC колонии участвует всегда, NPC вне колонии (заставы, свободные магазины) - только с атрибутом QuestsAvailable = true на самом NPC
bool IsNPCQuestsAllowed(ref rChar)
{
	if (IsColonyTrader(rChar)) return true;
	if (!CheckAttribute(rChar, "QuestsAvailable")) return false;
	return sti(rChar.QuestsAvailable) != 0;
}

// > файл дополнительного диалога по атрибуту магазина: свой, если атрибут задан, иначе общий
string FreeStoreDialogByAttr(int iStore, string sAttr, string sDefault)
{
	if (!IsFreeStoreNum(iStore)) return sDefault;
	if (CheckAttribute(&Stores[iStore], sAttr) && Stores[iStore].(sAttr) != "") return Stores[iStore].(sAttr);
	return sDefault;
}

// > дополнительный диалог торговца свободного магазина:
// > Stores[i].StoreDialog (путь вида "DIALOGS\Store\MyShop_Store.c") либо общий Free_Store.c.
// > Грузит его Common_Store.c вместо файла "по городам", когда магазин не колониальный (свободный)
string GetFreeStoreDialogFile(int iStore)
{
	return FreeStoreDialogByAttr(iStore, "StoreDialog", "DIALOGS\Store\Free_Store.c");
}

// > то же для верфиста вне колоний:
// > Stores[i].ShipyardDialog либо общий Free_Shipyard.c
// > Магазин верфисту не обязателен - без StoreNum он получает общий файл
string GetFreeShipyardDialogFile(int iStore)
{
	return FreeStoreDialogByAttr(iStore, "ShipyardDialog", "DIALOGS\Shipyard\Free_Shipyard.c");
}

// > остров торговца для квестовых проверок "не на своём острове":
// > у колониального берётся из таблицы GetIslandNameByCity,
// > у свободного - из атрибута Island его магазина (значение того же вида, что Colonies[].islandLable).
// > не задан - пустая строка.
string GetTraderIslandName(ref rTrader)
{
	string sIsland = "";
	if (CheckAttribute(rTrader, "city")) sIsland = GetIslandNameByCity(rTrader.city);
	if (sIsland != "") return sIsland;

	if (!CheckAttribute(rTrader, "StoreNum")) return "";

	int iStore = sti(rTrader.StoreNum);
	if (!IsFreeStoreNum(iStore)) return "";
	if (!CheckAttribute(&Stores[iStore], "Island")) return "";

	return Stores[iStore].Island;
}

// > имя города торговца для реплик: у колониального из LocLables.txt, у свободного - название магазина
string GetTraderCityName(ref rTrader)
{
	string sName = "";
	if (CheckAttribute(rTrader, "city")) sName = GetCityName(rTrader.city);
	if (sName != "") return sName;

	int iStore = GetTraderFreeStore(rTrader);
	if (iStore < 0) return "";

	return GetStoreTitleName(&Stores[iStore]);
}

// > колония, которой магазин приписан.
// > прайс такого магазина все пути пишет под ключом колонии, как у колониального;
// > неполная приписка (одна строка из двух) - под собственным id
int GetStorePriceColony(ref rStore)
{
	if (!CheckAttribute(rStore, "Colony") || !CheckAttribute(rStore, "index")) return -1;

	int iColony = FindColony(rStore.Colony);
	if (iColony < 0) return -1;
	if (sti(Colonies[iColony].StoreNum) != sti(rStore.index)) return -1;

	return iColony;
}

// > имя ветки прайса магазина в торговой книге:
// > у колониального и трюма - Colony, как в оригинале;
// > у свободного - колония при полной приписке, иначе собственный id.
// > для мест, которые пишут прайс сами, минуя SetPriceList (цена на жемчуг в окнах магазина и контрабандистов)
string GetStorePriceKey(ref rStore)
{
	if (!IsFreeStore(rStore))
	{
		if (CheckAttribute(rStore, "Colony")) return rStore.Colony;
		return "";
	}

	int iColony = GetStorePriceColony(rStore);
	if (iColony >= 0) return Colonies[iColony].id;
	return rStore.id;
}

// > записать прайс торговца в торговую книгу:
// > у колониального ключ - колония, у свободного - его магазин
void SetPriceListByTrader(ref rTrader)
{
	int iColony = -1;
	if (CheckAttribute(rTrader, "city")) iColony = FindColony(rTrader.city);

	if (iColony >= 0)
	{
		SetPriceListByStoreMan(&Colonies[iColony]);
		return;
	}

	if (!CheckAttribute(rTrader, "StoreNum")) return;

	int iStore = sti(rTrader.StoreNum);
	if (!IsFreeStoreOccupied(iStore)) return;

	int iStoreColony = GetStorePriceColony(&Stores[iStore]);
	if (iStoreColony >= 0) SetPriceListByStoreMan(&Colonies[iStoreColony]); // > приписан колонии - её ключ
	else                   SetPriceListByStoreMan(&Stores[iStore]);
}

// > дорастить массив магазинов до объявленного размера.
// > вызов из OnLoad.
void OnLoadUpdateStoreArray()
{
	int iOldSize = GetArraySize(&Stores);
	if (iOldSize >= STORE_QUANTITY) return; // > сейв новее сборки: слоты есть, трогать нечего

	SetArraySize(&Stores, STORE_QUANTITY);

	// > оригинальные слоты (0..SHIP_STORE) в сейве были всегда, чистим только свободный хвост
	for (int i = iOldSize; i < STORE_QUANTITY; i++)
	{
		if (IsFreeStoreNum(i)) FreeStoreClear(i);
		else                   Stores[i].index = i;
	}

	trace("OnLoad: массив магазинов дорощен " + iOldSize + " -> " + STORE_QUANTITY);
}

// > сколько позиций товара реально лежит в магазине
int FreeStoreGoodsCount(int iStore)
{
	if (!IsFreeStoreNum(iStore)) return 0;

	int iCount = 0;
	for (int i = 0; i < GOODS_QUANTITY; i++)
	{
		if (GetStoreGoodsQuantity(&Stores[iStore], i) > 0) iCount++;
	}
	return iCount;
}

// > занятые свободные слоты в лог; молчит, если их нет
void FreeStoresTrace(string sWhere)
{
	int iNum = GetStoreSlotsNum();
	ref rStore;

	for (int i = FREE_STORE_FIRST; i < iNum; i++)
	{
		if (!IsFreeStoreOccupied(i)) continue;

		rStore = &Stores[i];
		trace(sWhere + ": свободный магазин [" + i + "] '" + rStore.id + "', размер " + rStore.StoreSize + ", группа '" + rStore.group + "', позиций товара " + FreeStoreGoodsCount(i) + ", денег " + rStore.money);
	}
}

// > единственный вызов из OnLoad: дорастить массив и записать в лог, что приехало из сейва
void StoresOnLoadCheck()
{
	OnLoadUpdateStoreArray();
	FreeStoresTrace("OnLoad");
}

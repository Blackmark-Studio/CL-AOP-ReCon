#define STORE_QUANTITY			37	// KZ FreeStores > 31 штатный слот (0..30) + FREE_STORE_QUANTITY свободных; держать равным FREE_STORE_FIRST + FREE_STORE_QUANTITY

#define Bridgetown_STORE		0
#define SanJuan_STORE			1
#define Santiago_STORE			2
#define Villemstad_STORE		3
#define Tortuga_STORE			4
#define Marigo_STORE			5
#define PortSpein_STORE			6
#define Charles_STORE			7
#define PortoBello_STORE		8
#define SentJons_STORE			9
#define Havana_STORE			10
#define BasTer_STORE			11
#define FortFrance_STORE		12
#define LeFransua_STORE			13
#define LaVega_STORE			14
#define SantoDomingo_STORE		15
#define PortPax_STORE			16
#define Pirates_STORE			17
#define PuertoPrincipe_STORE    18
#define PortRoyal_STORE         19
#define FortOrange_STORE        20
#define Panama_STORE          	21
#define Cartahena_STORE         22
#define Maracaibo_STORE         23
#define Caracas_STORE          	24
#define Cumana_STORE          	25
#define SantaCatalina_STORE     26
#define Beliz_STORE          	27
#define Providencia_STORE       28
#define Gibraltar_STORE       	29

#define SHIP_STORE 				30

// FreeStores > свободные магазины - без колонии и нации
#define FREE_STORE_FIRST		31
#define FREE_STORE_QUANTITY		6

// FreeStores > группа незанятого слота (и магазина без группы)
#define FREE_STORE_NO_GROUP		"#free"

// FreeStores > запрет торговли отдельным товаром, режим считается со стороны магазина
#define FREE_STORE_TRADE_BOTH	0				// > и покупает, и продаёт - обычная торговля
#define FREE_STORE_TRADE_BUY	1				// > только покупает: ГГ может продать, но не купить
#define FREE_STORE_TRADE_SELL	2				// > только продаёт: ГГ может купить, но не продать
#define FREE_STORE_TRADE_NONE	3				// > ни купить, ни продать

// FreeStores > показ товара с запретом NONE, пока товару не задан свой вид через FreeStoreSetGoodView
#define FREE_STORE_BAN_SHOW		0				// > 0 - строки в списках нет; 1 - строка есть, но без цен
#define FREE_STORE_BAN_COLOR_R	128				// > цвет такой строки - серый
#define FREE_STORE_BAN_COLOR_G	128
#define FREE_STORE_BAN_COLOR_B	128

// FreeStores > показ товара, которым магазин не торгует, в торговом разделе судового журнала:
// > переключатель один на весь магазин, задаётся через FreeStoreSetBookView
#define FREE_STORE_BOOK_SHOW	0				// > 0 - строки в журнале нет; 1 - строка есть, но без цен и цветом запрета

#define TRADE_TYPE_NORMAL		0
#define TRADE_TYPE_EXPORT		1
#define TRADE_TYPE_IMPORT		2
#define TRADE_TYPE_CONTRABAND	3
#define TRADE_TYPE_AMMUNITION	4
#define TRADE_TYPE_CANNONS 		5

#define TRADE_TYPE_NORMAL_NAME		"normal"
#define TRADE_TYPE_EXPORT_NAME		"export"
#define TRADE_TYPE_IMPORT_NAME		"import"
#define TRADE_TYPE_CONTRABAND_NAME	"contraband"
#define TRADE_TYPE_AMMUNITION_NAME	"ammunition"
#define TRADE_TYPE_CANNONS_NAME     "cannons"

//HardCoffee для ограничения денег
#define STORE_MIN_MONEY		1000000 //магазины
#define STORE_RAND_MONEY	1000000 //+рандом
#define SMUGG_MIN_MONEY		500000  //контрабандисты
#define SMUGG_RAND_MONEY	500000

#define BANK_TRADER_MIN_MONEY		60000	// банкиры
#define BANK_TRADER_RAND_MONEY		60000   //+рандом
#define STORE_TRADER_MIN_MONEY		30000	// магазины
#define STORE_TRADER_RAND_MONEY		60000
#define MERCH_TRADER_MIN_MONEY		10000	// лоточнки
#define MERCH_TRADER_RAND_MONEY		20000
#define LIGHT_TRADER_MIN_MONEY		2000	// смотрители маяков, погостов и бродячие торговцы
#define LIGHT_TRADER_RAND_MONEY		5000

object  stores[STORE_QUANTITY];

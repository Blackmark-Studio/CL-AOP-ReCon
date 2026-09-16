#define SAILS_COLOR_QUANTITY				9

#define SHIP_TYPES_QUANTITY					57
#define SHIP_TYPES_QUANTITY_WITH_FORT		58	// must be (SHIP_TYPES_QUANTITY + 1)

///////////////////////////////////////////////////////////////////////////
/// NORMAL SHIPS START
///////////////////////////////////////////////////////////////////////////

#define SHIP_NORMAL				0			// > здесь и далее SHIP_NORMAL, SHIP_CLASS_*, SHIP_QUEST и т.д. - это просто разделители-указатели (какой класс с какого корабля начинается), для удобства подбора кораблей в коде

// 7 class
#define SHIP_CLASS_7			0
#define SHIP_BARKAS				0			// Баркас				(EFSH)		- не военный и не торговый, 7-ой класс
#define SHIP_TARTANE			1   		// Тартана				(EFSH)		- не военный и не торговый, 7-ой класс
#define SHIP_LIUTO				2			// Леудо				(EFSH)		- торговый, 7-ой класс
#define SHIP_WAR_TARTANE		3			// Дау					(EFSHP)		- торговый, 7-ой класс
#define SHIP_FELUCA				4			// Фелюка				(EFSHP)		- военный, 7-ой класс
#define SHIP_BILANCETTA			5			// Кеч					(EFSHP)		- универсал, 7-ой класс

// 6 class
#define SHIP_CLASS_6			6
#define SHIP_LUGGER				6			// Люггер				(EFSHP)		- военный, 6-ой класс
#define SHIP_CAREERLUGGER		7			// Курьерский Люггер	(EFSHP)		- торговый, 6-ой класс
#define SHIP_SLOOP				8			// Шлюп					(EFSHP)		- военный, 6-ой класс
#define SHIP_SLOOP_W			9			// Хой					(EFSH)		- торговый, 6-ой класс
#define	SHIP_CUTTER				10			// Куттер				(EFSHP)		- универсал, 6-ой класс

// 5 class
#define SHIP_CLASS_5			11
#define SHIP_SCHOONER			11			// Торговая шхуна		(EFSH)		- торговый, 5-ый класс
#define SHIP_SCHOONER_W			12			// Военная шхуна		(EFSHP)		- военный, 5-ый класс
#define SHIP_BARQUE				13			// Торговый барк		(EFSH)		- торговый, 5-ый класс
#define SHIP_BARQUE_W			14			// Усиленный барк		(EFSH)		- военный, 5-ый класс
#define SHIP_XEBEK_L			15			// Лёгкая щебека		(FSHP)		- универсал, 4-ый класс

// 4 class
#define SHIP_CLASS_4			16
#define SHIP_BARKENTINE			16			// Баркентина			(SH)		- торговый, 4-ый класс
#define SHIP_BRIGANTINE			17			// Бригантина			(SHP)		- военный, 4-ый класс
#define SHIP_SHNYAVA			18			// Шнява				(EFSHP)		- универсал, 4-ый класс
#define SHIP_FLEUT				19			// Флейт				(EFSH)		- торговый, 4-ый класс
#define SHIP_BRIG_L				20			// Лёгкий бриг			(SHP)		- военный, 4-ый класс
#define SHIP_BRIG				21			// Бриг					(EFP)		- военный, 4-ый класс
#define SHIP_CARAVEL			22			// Торговая каравелла	(EFSH)		- торговый, 4-ый класс
#define SHIP_CARAVEL_W			23			// Военная каравелла	(EFSH)		- военный, 4-ый класс
#define SHIP_GALEON_L			24			// Лёгкий галеон		(EFSHP)		- универсал, 4-ый класс

// 3 class
#define SHIP_CLASS_3			25
#define SHIP_PINNACE			25			// Пинас				(EF)		- торговый, 3-ий класс
#define SHIP_CARACCA			26			// Каракка				(SH)		- универсал, 3-ий класс
#define SHIP_CORVETTE_L			27 			// Лёгкий корвет		(EFP)		- военный, 3-ий класс
#define SHIP_CORVETTE			28			// Корвет				(EFP)		- военный, 3-ий класс
#define SHIP_POLACRE			29			// Полакр 				(SH)		- военный, 3-ий класс
#define SHIP_GALEON				30			// Галеон				(SHP)		- универсал, 3-ий класс

// 2 class
#define SHIP_CLASS_2			31
#define SHIP_EASTINDIAMAN		31			// Ост-Индец			(EFSH)		- торговец, 2-ой класс
#define SHIP_GALEON_H			32			// Тяжёлый галеон		(SHP)		- универсал, 2-ой класс
#define SHIP_FRIGATE			33			// Фрегат				(EFP)		- военный, 2-ой класс
#define SHIP_FRIGATE_H			34			// Тяжёлый фрегат		(EFSH)		- военный, 2-ой класс

// 1 class
#define SHIP_CLASS_1			35
#define SHIP_LINESHIP			35			// Военный корабль		(EFSH)		- военный, 1-ый класс
#define SHIP_WARSHIP			36			// Линейный корабль		(EFSH)		- военный, 1-ый класс
#define SHIP_BATTLESHIP			37			// Боевой корабль		(EFSH)		- военный, 1-ый класс
#define SHIP_MANOWAR			38			// Мановар				(EFSH)		- военный, 1-ый класс

///////////////////////////////////////////////////////////////////////////
/// NORMAL SHIPS END
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/// QUEST SHIPS START
///////////////////////////////////////////////////////////////////////////

#define SHIP_QUEST				39

// 6 class
#define SHIP_QUEST_CLASS_6		39
#define SHIP_LUGGERQUEST        39			// Курьерский люггер	- люггер, военный, 6-ой класс
#define SHIP_VEINARD			40			// Везунчик		 		- быстрый шлюп, военный, 6-ой класс

// 5 class
#define SHIP_QUEST_CLASS_5		41
#define SHIP_XebekVML			41			// Синяя птица			- щебека, военный, 5-ый класс

// 4 class
#define SHIP_QUEST_CLASS_4		42
#define SHIP_BRIGQEEN			42			// Стрела				- быстрая бригантина, военный, 4-ый класс
#define SHIP_BRIGSW				43			// Морской волк			- тяжёлый бриг, военный, 4-ый класс

// 3 class
#define SHIP_QUEST_CLASS_3		44
#define SHIP_CORVETTE_QUEST		44			// Пёс Войны			- тяжёлый корвет, военный, 3-ий класс
#define SHIP_CORVETTE_QUEST_O	45			// Оч.Пёс Войны			- легендарный корвет, военный, 3-ий класс
#define SHIP_POLACRE_QUEST		46			// Призрак Тени 		- тяжёлый полакр, военный, 3-ий класс

// 2 class
#define SHIP_QUEST_CLASS_2		47
#define SHIP_ARABELLA			47			// Синко Льягас			- быстрый фрегат, военный, 2-ой класс
#define SHIP_FRIGATEQUEEN		48			// Королева				- быстрый фрегат, военный, 2-ой класс
#define SHIP_FRIGATE_M			49			// Оксфорд				- фрегат, военный, 2-ой класс
#define SHIP_FLYINGDUTCHMAN		50			// Летучий Голландец	- призрачный варшип, военный, 2-ой класс
#define SHIP_FLYINGDUTCHMAN_O	51			// Оч.Летучий Голландец	- легендарный варшип, военный, 2-ой класс
#define SHIP_MARGARITA			52			// Маргарита			- испанский галеон, военный, 2-ой класс

// 1 class
#define SHIP_QUEST_CLASS_1		53
#define SHIP_SANTISIMA		    53			// Быстрый мановар		- мановар, военный, 1-ый класс
#define SHIP_SOLEYRU			54			// Королевский мановар	- мановар, военный, 1-ый класс

///////////////////////////////////////////////////////////////////////////
/// QUEST SHIPS END
///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
/// SPECIAL SHIPS START
///////////////////////////////////////////////////////////////////////////

#define SHIP_SPECIAL			55

#define SHIP_BOAT               55			// лодка у причала
#define SHIP_SHELL              56			// лодка нагруженная товарами (скорлупка)
#define SHIP_FORT               57			// форт

///////////////////////////////////////////////////////////////////////////
/// SPECIAL SHIPS END
///////////////////////////////////////////////////////////////////////////

#define SHIP_NOTUSED			 1000
#define SHIP_NOTUSED_TYPE_NAME	"Not Used"
#define SHIP_NAME_NOTUSED		"Noname"

object  ShipsTypes[SHIP_TYPES_QUANTITY_WITH_FORT];  // RealShips
object	SailsColors[SAILS_COLOR_QUANTITY];

// KZ > отпечаток файлов, из которых собраны таблицы кораблей, на момент сборки
string sShipsStamp = "";

// пользовать GetRealShip
// KZ > заглушка как в GetRealShip: осиротевший BaseType (тип удалён из ships_init.c, сейв от удалённого/отключённого мода) без проверки валил бы скрипт ошибкой invalid index
ref GetShipByType(int iType)
{
	if (iType < 0 || iType >= SHIP_TYPES_QUANTITY_WITH_FORT)
	{
		trace("--- Wrong Ship Type Index. iType is " + iType);
		Log_TestInfo("--- Wrong Ship Type Index. iType is " + iType);
		return &ShipsTypes[SHIP_TYPES_QUANTITY]; // > слот форта, последний валидный индекс массива
	}

	return &ShipsTypes[iType];
}

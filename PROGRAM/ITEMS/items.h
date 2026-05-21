#define GOLD					"gold"

//TEMP
#define BLADE_SABER				"blade1"
#define BLADE_SHORT				"blade8"
#define BLADE_NORMAL			"blade10"
#define BLADE_LONG				"blade16"
#define GUN_COMMON				"pistol1"
#define CHEAP_SPYGLASS			"spyglass1"
#define COMMON_SPYGLASS			"spyglass2"
#define GOOD_SPYGLASS			"spyglass3"
#define SUPERIOR_SPYGLASS		"spyglass4"
#define POTION					"potion1"
#define INVALID_SUIT			"NoSuit"

// items group id
#define GUN_ITEM_TYPE			"gun"
#define BLADE_ITEM_TYPE			"blade"
#define SPYGLASS_ITEM_TYPE		"spyglass"
#define PATENT_ITEM_TYPE        "patent"
#define CIRASS_ITEM_TYPE		"cirass"
#define MAPS_ITEM_TYPE		    "maps"		// Добавлена новая группа
#define READING_ITEM_TYPE	    "reading"	// группа для интерактивных вещей, для которых должна работать кнопка "Взять"
#define AMMO_ITEM_TYPE			"ammo"		// Боеприпасы
#define POTION_ITEM_TYPE		"potion"	// Зелья
#define ALCHEMY_ITEM_TYPE		"alchemy"	// Алхимия
#define MUSKET_ITEM_TYPE		"musket"	// evganat - мушкеты

// indexes for items` array
// evganat - энциклопедия, прибавил по два
#define TOTAL_ITEMS				1182 		// Warship 08.05.09 - Новая система предметов
#define ITEMS_QUANTITY			583  		// не забываем менять номер
#define MAX_BUTTONS				64
#define RANDITEMS_QUANTITY		45
#define BUTTON_ACTIVATION_TIME	1000
#define ITEMS_LAYER				65549
#define MAX_LOADED_RANDITEMS	10
#define MAX_LOADED_HERBS		10			// количество растений на одной локации
#define MAX_HANDLED_BOXES		25
#define MAX_SECRET_CHESTS		4 			// HardCoffee количество тайников на одной локации
#define ITEM_PROBABILITY		0.5
#define OBJECTS_IN_BOX			9
#define MAPS_IN_ATLAS			26 			// ugeen 21.06.09  -не забываем увеличивать при появлении новых карт

//группы типов холодного оружия
#define SLAVE_BLADE			"slave" 			// группа для рабов и прочих бомжей
#define ORDINARY_BLADE		"common" 			// группа серо-белых клинков
#define OFFICER_BLADE		"officer" 			// группа бело-синих клинки
#define COOL_BLADE			"cool" 				// группа сине-красных клинки
#define INDIAN_BLADE		"indian" 			// группа для индейцев
#define SOLDER_BLADE		"solder" 			// группа для солдат в городе
#define VIKING_BLADE		"viking" 			// группа для викингов

//группы типов огнестрела
#define POOR_GUN			"poor" 				// группа серых пушек
#define ORDINARY_GUN		"common" 			// группа серо-белых пушек
#define OFFICER_GUN			"officer" 			// группа бело-синих пушек
#define COOL_GUN			"cool" 				// группа сине-красных пушек

object Items[TOTAL_ITEMS];
object RandItems[RANDITEMS_QUANTITY];
object JungleHerbs[MAX_LOADED_HERBS];

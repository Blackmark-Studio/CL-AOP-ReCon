#include "scripts\colony.c"
#include "scripts\food.c"
#include "scripts\time_events.c"
#include "scripts\Rumour_Init.c" // homo 23/06/06
#include "scripts\islandships.c"
#include "scripts\officers.c"
#include "scripts\companions.c"
#include "scripts\ShipsUtilites.c"
#include "scripts\Crew.c"
#include "scripts\bountyhunters.c"
#include "scripts\tavern.c"
#include "scripts\idioms.c"
#include "scripts\smuggling.c"
#include "scripts\PsHero.c" // navy
#include "scripts\duel.c" // navy
#include "scripts\MerchantOnMap.c" // homo 29/07/06
#include "scripts\Siege.c" // homo 09/09/06 Осады
#include "scripts\Treasure.c"  // boal 02.09.06 клады
#include "scripts\Other_Quests.c" // Warship 09.05.08 прочие квесты
#include "scripts\GenQuests.c" // Warship 16.05.08 генераторы
#include "scripts\CompanionTravel.c" // Warship 17.07.08 Методы для свободного плавания компаньонов
#include "scripts\GameModeCondition.c" // Warship. Обраобтка прерывания, выполняющегося в каждом фрейме
#include "scripts\GenQuests_common.c" // Ugeen 12.01.10 общие функции для генераторов

#define MAN 0
#define WOMAN 1

#define WITHOUT_SHIP 0
#define WITH_SHIP 1

#define WARRIOR 0
#define CITIZEN 1
#define TRADER 2
#define BOSS	3
#define FORT_COMMANDER	4
#define FORT_DEFENDER	5
#define BOUNTY_HUNTER	6
#define SOLDIER	7
#define OFFICER	8

#define QUEST_NOT_ACCEPTED	0
#define QUEST_ACCEPTED	1
#define QUEST_COMPLETED	2

// Для GetRandSubString
#define COMMONERS "barmen_0,barmen_1,citiz_42,citiz_45,citiz_46,citiz_47,citiz_48,citiz_50,barmen_13,shipowner_5"

void SetNames()
{
	for(int i = 1; i <MAX_CHARACTERS; i++)
	{
		if (!CheckAttribute(&Characters[i], "name") || Characters[i].name == "none")
		{
			SetRandomNameToCharacter(&Characters[i]);
		}
	}
}

void SetNationRelations()
{
    Nations_SetAllFriends();

	SetNationRelationBoth(ENGLAND, PIRATE, RELATION_ENEMY);
	SetNationRelationBoth(ENGLAND, FRANCE, RELATION_NEUTRAL);

	SetNationRelationBoth(HOLLAND, PIRATE, RELATION_ENEMY);
	SetNationRelationBoth(FRANCE, PIRATE, RELATION_ENEMY);

	SetNationRelationBoth(SPAIN, ENGLAND, RELATION_ENEMY);
    SetNationRelationBoth(SPAIN, PIRATE, RELATION_ENEMY);
    SetNationRelationBoth(SPAIN, FRANCE, RELATION_ENEMY);
    SetNationRelationBoth(SPAIN, HOLLAND, RELATION_NEUTRAL);

    SetNationRelationBoth(HOLLAND, ENGLAND, RELATION_ENEMY);
    SetNationRelationBoth(HOLLAND, FRANCE, RELATION_FRIEND);
    
	// ГГ отношения от нации
	pchar = GetMainCharacter();
	SetNationRelation2MainCharacter(ENGLAND, GetNationRelation(sti(pchar.nation), ENGLAND));
	SetNationRelation2MainCharacter(FRANCE,  GetNationRelation(sti(pchar.nation), FRANCE));
	SetNationRelation2MainCharacter(SPAIN,   GetNationRelation(sti(pchar.nation), SPAIN));
	SetNationRelation2MainCharacter(PIRATE,  GetNationRelation(sti(pchar.nation), PIRATE));
    SetNationRelation2MainCharacter(HOLLAND, GetNationRelation(sti(pchar.nation), HOLLAND));
}

// метод установки отношений по дипломату
void ChangeNationRelationFromRelationAgent(aref chr)
{
	int iNation = sti(chr.quest.relation);

    int iDays = rand(10) + 5;
	string sQuest = "Change_Relation_for_Nation_" + GetNationNameByType(iNation) + "_by_relation_agent_" + iDays;
	
	SetTimerCondition(sQuest, 0, 0, iDays, false);
	pchar.quest.(sQuest).function = "ChangeNationRelationFromRelationAgentComplete";
	pchar.quest.(sQuest).nation = iNation;
}

void ChangeNationRelationFromRelationAgentComplete(string sQuest)
{
	int iNation = sti(pchar.quest.(sQuest).nation);
    string sNation = "RelationAgentRate" + GetNationNameByType(iNation);
    
	SetNationRelation2MainCharacter(iNation, RELATION_NEUTRAL);
	ChangeCharacterNationReputation(pchar, iNation, sti(Pchar.GenQuest.(sNation)));
	sti(Pchar.GenQuest.(sNation)) = 0; // чтоб второй раз не было
	sNation = "RelationAgent" + GetNationNameByType(iNation);
    Pchar.GenQuest.(sNation) = false;
    
	Log_Info(StringFromKey("InfoMessages_119"));
}

int CalculateRelationSum(int iNation)
{
	string sNation = "RelationAgentRate" + GetNationNameByType(iNation);
	Pchar.GenQuest.(sNation) = abs(GetCharacterReputation_WithNation(pchar, iNation));
	int iSumm = sti(Pchar.GenQuest.(sNation)) * 1500 +  makeint(stf(Pchar.rank)/stf(Pchar.reputation)*100000);

	//iSumm = iSumm * (1.0 + (0.1 * MOD_SKILL_ENEMY_RATE));
	
	return iSumm;
}

void GenerateMaps(aref ch, int iProbability1, int iProbability2)
{
	int rank = sti(PChar.rank);
	
	if(rand(10) == 1) AddItems(ch, "map_bad", 1);
	if(rand(40) == 1 && rank >= 4) AddItems(ch, "map_normal", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_jam")) AddItems(ch, "map_jam", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_barbados")) AddItems(ch, "map_barbados", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_trinidad")) AddItems(ch, "map_trinidad", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_Curacao")) AddItems(ch, "map_Curacao", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_martiniqua")) AddItems(ch, "map_martiniqua", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_puerto")) AddItems(ch, "map_puerto", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cuba")) AddItems(ch, "map_cuba", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_hisp")) AddItems(ch, "map_hisp", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_nevis")) AddItems(ch, "map_nevis", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_guad")) AddItems(ch, "map_guad", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_antigua")) AddItems(ch, "map_antigua", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_TORTUGA")) AddItems(ch, "map_TORTUGA", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_sm")) AddItems(ch, "map_sm", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_bermudas")) AddItems(ch, "map_bermudas", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_beliz")) AddItems(ch, "map_beliz", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_santa")) AddItems(ch, "map_santa", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_panama")) AddItems(ch, "map_panama", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_maracaibo")) AddItems(ch, "map_maracaibo", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_cumana")) AddItems(ch, "map_cumana", 1);
	if(rand(iProbability1) == 1 && !CheckMainHeroMap("map_providence")) AddItems(ch, "map_providence", 1);
	
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_cayman")) AddItems(ch, "map_cayman", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_dominica")) AddItems(ch, "map_dominica", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_terks")) AddItems(ch, "map_terks", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_Pearl")) AddItems(ch, "map_Pearl", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_1")) AddItems(ch, "map_maine_1", 1);
	if(rand(iProbability2) == 1 && !CheckMainHeroMap("map_maine_2")) AddItems(ch, "map_maine_2", 1);
}

void GiveItemToTrader(aref ch)
{
	int i, irand;
	string itemID;
	int rank = sti(PChar.rank); // makeint(pchar.rank) - и так было везде... Нет бы сразу переменную завести - это ведь быстрее будет в разы
	ref itm; // ref itm = ItemsFromID("map_LSC"); - тоже самое... Че за бред, заводить переденную внутри блока иф?
	
	DeleteAttribute(ch, "items");
	// boal зачем они в продаже?  ДЛЯ ОТЛАДКИ  -->
	if (bBettaTestMode)
	{
    	for (i = 0; i < ITEMS_QUANTITY; i++)
    	{
			itemID = Items[i].ID;
			itm = ItemsFromID(itemID);
			irand = rand(2) + 1;
			
			if (StrHasStr(itemID, "fire,gold", 1) || itm.name == "") // > "забаненные" для торговли предметы
				continue;
			
			// Warship переделка
			if (IsGenerableItem(itemID)) // Уникальные предметы, которые сначало нужно генерить
			{
				GenerateAndAddItems(ch, itemID, irand);
				continue;
			}
			
            AddItems(ch, itemID, irand);
    	}
		
		return;
	}
	
	// TODO перенести типажи лоточников из ККС
	// > Ростовщики, TODO мб, добавить им что-нибудь оккультное, индейские побрякушки и т.д.?
	if (StrEndsWith(ch.id, "_usurer"))
	{
		// > тир 1, редко в ассортименте
		if (rand(5) == 1) AddItems(ch, "jewelry2", 1 + rand(4));		// "Алмаз"
		if (rand(5) == 1) AddItems(ch, "jewelry3", 1 + rand(4));		// "Рубин"
		if (rand(5) == 1) AddItems(ch, "jewelry4", 1 + rand(4));		// "Рубин"
		if (rand(5) == 1) AddItems(ch, "jewelry1", 1 + rand(4));		// "Сапфир"
		if (rand(5) == 1) AddItems(ch, "jewelry18", 1 + rand(4));		// "Золотое кольцо с рубином"
		if (rand(5) == 1) AddItems(ch, "jewelry15", 1 + rand(4));		// "Изумрудные подвески"

		// > тир 2, часто в ассортименте
		if (rand(3) == 0) AddItems(ch, "jewelry5", 1 + rand(5));		// "Золотой самородок"
		if (rand(3) == 1) AddItems(ch, "jewelry14", 1 + rand(5));		// "Золотая брошь"
		if (rand(3) == 2) AddItems(ch, "jewelry7", 1 + rand(5));		// "Золотое кольцо с изумрудом"
		if (rand(3) == 3) AddItems(ch, "jewelry10", 1 + rand(5));		// "Золотое кольцо с сапфиром"
		if (rand(3) == 2) AddItems(ch, "jewelry13", 1 + rand(5));		// "Камея"
		if (rand(3) == 1) AddItems(ch, "jewelry17", 1 + rand(5));		// "Серебряный самородок"
		if (rand(3) == 0) AddItems(ch, "jewelry6", 1 + rand(5));		// "Серебряное кольцо с сапфиром"

		// > тир 3, очень часто в ассортименте
		if (rand(1)) AddItems(ch, "jewelry8", 1 + rand(5));				// "Бронзовое кольцо"	(+1 Везение)
		if (rand(1)) AddItems(ch, "jewelry9", 1 + rand(5));				// "Бронзовый крестик"	(+1 Везение)

		// есть всегда
		AddItems(ch, "jewelry16", 3 + rand(6));							// "Ожерелье"
		return;
	}
	
	// > Смотрители маяков
	if (StrEndsWith(ch.id, "_Lightman"))
	{
		irand = rand(10);

		if (rand(3) == 1) AddItems(ch, "mineral12", 1 + rand(3));		// "Верёвка"
		if (rand(2) == 1) AddItems(ch, "mineral11", 1 + rand(5));		// "Точильный камень"
		if (rand(2) == 1) AddItems(ch, "mineral13", 1 + rand(5));		// "Бронзовый котелок"

		if (rand(3) == 3) AddItems(ch, "indian2", 1);					// "Пугающая фигурка" (-1 лидерство)
		if (rand(3) == 1) AddItems(ch, "indian1", 1);					// "Оберег Тлальчитонатиу"
		if (rand(3) == 1) AddItems(ch, "indian3", 1);					// "Нефритовая маска"
		if (rand(3) == 3) AddItems(ch, "indian5", 1);					// "Двойная маска"
		if (rand(3) == 1) AddItems(ch, "jewelry8", 1 + rand(1));		// "Бронзовое кольцо" (+1 к везению)
		if (rand(3) == 1) AddItems(ch, "jewelry9", 1 + rand(1));		// "Бронзовый крестик" (+1 к везению)

		
		if (rank > 2 && irand >= 3)										// < качество poor
		{
			// > лёгкое холодное оружие
			if (rand(1)) GenerateAndAddItems(ch, "blade5", 1);			// "Дага"
			if (rand(1)) GenerateAndAddItems(ch, "blade2", 1);			// "Венецианская шпага"

			// > среднее холодное оружие
			if (rand(1)) GenerateAndAddItems(ch, "blade1", 1);			// "Канонирский тесак"
			if (rand(1)) GenerateAndAddItems(ch, "blade4", 1);			// "Кавалерийская сабля"
		}
		if (rank > 4 && irand >= 4)										// < качество ordinary
		{
			GenerateAndAddItems(ch, "blade6", 1);						// "Дворянка"
			if (drand(1)) GenerateAndAddItems(ch, "blade9", 1);			// "Сайдсворд"
		}
		if (rank > 6 && irand >= 6)										// < качество good
		{
			GenerateAndAddItems(ch, "blade19", 1);						// "Маринера"
			if (drand(1)) GenerateAndAddItems(ch, "blade22", 1);		// "Конкилья"
		}
		if (rank > 6 && irand >= 4)										// < качество ordinary
		{
			GenerateAndAddItems(ch, "blade6", 1);						// "Дворянка"
		}
		if (rank > 9 && irand >= 5)										// < качество good
		{
			GenerateAndAddItems(ch, "blade7", 1);						// "Бильбо"
		}

		if (rand(3) == 3) AddItems(ch, "spyglass3", 1);					// "Обычная подзорная труба"
		if (rand(1)) AddItems(ch, "potionrum", 1 + rand(3));			// "Бутылка рома"
		if (rand(1)) AddItems(ch, "jewelry12", 1 + rand(9));			// "Маленькая жемчужина"
		if (rand(1)) AddItems(ch, "jewelry11", 1 + rand(5));			// "Большая жемчужина"
		if (rand(1)) AddItems(ch, "spyglass2", 1);						// "Дешёвая подзорная труба"

		// > травы
		if (rand(2) == 0) AddItems(ch, "herb_zingiber", 1 + rand(2));	// "Корень имбиря"
		if (rand(2) == 1) AddItems(ch, "herb_matricaria", 1 + rand(2));	// "Матрикария"
		if (rand(2) == 2) AddItems(ch, "herb_ginseng", 1 + rand(2));	// "Женьшень"

		// > филлерный мусор, то, что есть всегда, шанс 100%
		AddItems(ch, "mineral6", 2 + rand(5));							// "Коралл"
		return;
	}
	
	// > Смотрители кладбищ
	if (StrEndsWith(ch.id, "_Cemeteryman"))
	{
		irand = rand(10);

		// > тир 1, полезные предметы с + к статам и для крафта, шансы: ~60% на общий прок и ~25-30% индивидуальный; TODO дополнить
		if (irand >= 5)
		{
			if (rand(2) == 1) AddItems(ch, "indian17", 1);				// "Тельная ладанка" (+3 скрытность)
			if (rand(2) == 1) AddItems(ch, "jewelry8", 1 + rand(1));	// "Бронзовое кольцо" (+1 к везению)
			if (rand(2) == 1) AddItems(ch, "jewelry9", 1 + rand(1));	// "Бронзовый крестик" (+1 к везению)
		}

		if (rand(3) == 1) AddItems(ch, "mineral12", 1 + rand(3));		// "Верёвка"
		if (rand(2) == 1) AddItems(ch, "mineral14", 1 + rand(5));		// "Ножницы"
		if (rand(2) == 1) AddItems(ch, "mineral16", 1 + rand(5));		// "Гвозди"

		if (rank > 4 && irand >= 3)										// < качество poor
		{
			// > среднее холодное оружие
			if (rand(1)) GenerateAndAddItems(ch, "topor3", 1);			// "Клевец"
			if (rand(1)) GenerateAndAddItems(ch, "blade3", 1);			// "Катласс"
			
			// > тяжёлое холодное оружие
			if (rand(1)) GenerateAndAddItems(ch, "blade10", 1);			// "Фальшион"
			if (rand(1)) GenerateAndAddItems(ch, "blade35", 1);			// "Корделас"
			if (rand(1)) GenerateAndAddItems(ch, "topor1", 1);			// "Боевой топор"
			if (rand(1)) GenerateAndAddItems(ch, "blade17", 1);			// "Клеймор"
		}
		if (rank > 6 && irand >= 4)										// < качество ordinary
		{
			GenerateAndAddItems(ch, "blade12", 1);						// "Катцбальгер"
			
			if (CheckAttribute(&TEV, "GipsyFortuneBonus"))
				GenerateAndAddItems(ch, "blade18", 1);					// "Хангер"
		}
		if (rank > 9 && irand >= 6)										// < качество good
		{
			if (CheckAttribute(&TEV, "GipsyFortuneBonus"))
			{
				if (rand(1))
					GenerateAndAddItems(ch, "blade31", 1);				// "Шамшир"
				else
					GenerateAndAddItems(ch, "blade34", 1);				// "Скаллоп"
			}
		}

		if (rank > 6 && irand >= 4)										// < качество ordinary
		{
			if (rand(1)) GenerateAndAddItems(ch, "blade8", 1);			// "Госсемесер"
		}

		if (rank > 9 && irand >= 5)										// < качество good
		{
			if (rand(1)) GenerateAndAddItems(ch, "blade15", 1);			// "Сторта"
			if (rand(1)) GenerateAndAddItems(ch, "blade21", 1);			// "Бастард"
			if (rand(1)) GenerateAndAddItems(ch, "topor2", 1);			// "Рейтарский чекан"
		}

		// > тир 2
		if (rand(1)) AddItems(ch, "potion5", 1 + rand(4));				// "Виноград"
		if (rand(2) == 1) AddItems(ch, "potionwine", 1 + rand(2));		// "Отличное вино"
		if (rand(3) == 1) AddItems(ch, "potion3", 1 + rand(1));			// "Противоядие"

		// > тир 3
		if (rand(1)) AddItems(ch, "indian8", 1 + rand(3));

		// > травы
		if (rand(1)) AddItems(ch, "herb_zingiber", 1 + rand(4));		// "Корень имбиря"
		if (rand(1)) AddItems(ch, "herb_matricaria", 1 + rand(4));		// "Матрикария"
		if (rand(1)) AddItems(ch, "herb_ginseng", 1 + rand(4));			// "Женьшень"

		// филлерный мусор, то, что есть всегда
		AddItems(ch, "mineral7", 1 + rand(1));							// "Трубка"
		return;
	}

	// издевательство -->
    if(rank == 1 && rand(5) == 1) AddItems(ch, "sculMa3", 1);
	if(rank == 1 && rand(10) == 1 && !CheckMainHeroTotem("Totem_13")) AddItems(ch, "Totem_13", 1);
	if(rank == 1 && rand(10) == 1 && !CheckMainHeroTotem("Totem_8")) AddItems(ch, "Totem_8", 1);
	if(rank == 1 && rand(10) == 1 && !CheckMainHeroTotem("Totem_2")) AddItems(ch, "Totem_2", 1);
	// издевательство <--
	
	// evganat - энциклопедия
	if (!ENCYCLOPEDIA_DISABLED && CheckAttribute(ch, "city") && CheckRandomPage("trader", ch.city, sti(ch.nation)))
	{
		//HardCoffee для тестов нового рандома
		ch.encyclopedia.tome = GetRandomTomeToMerch(ch.id);
		//ch.encyclopedia.tome = GetRandomTome();
		ch.encyclopedia.page = 2;
		AddItems(ch, "encyclopedia_page", 1);
	}
	
	//дача карты ГПК в магазин Йоста -->
	if(ch.id == "LSC_Trader") 
	{
		if(!CheckAttribute(ch, "quest.takeMap") || ch.quest.takeMap != "changePrice")
		{
			AddItems(ch, "map_LSC", 1);
			if(!CheckAttribute(pchar, "questTemp.FindMapLSC")) ch.quest.takeMap = "mapIsToken";
		}
		else
		{			
			itm = ItemsFromID("map_LSC");
			itm.price = 1000;
			AddItems(ch, "map_LSC", 1);
			ch.quest.takeMap = "smallPrice";
		}
	}
	//<-- дача карты ГПК в магазин Йоста 

	// > КРАФТ: рецепты и предметы
	if (rand(4) == 4) AddItems(ch, "mineral12", 1 + rand(1));	// "Верёвка"
	if (ch.sex == "man")
	{
		if (rank >= 5)
		{
			if (rand(3) == 3)
				AddItems(ch, "crucible", 1);

			if (rand(3) == 2)
				AddItems(ch, "bullet_mold", 1);

			itemID = "recipe_cartridge";
			if (rand(3) == 1 && !isMultiObjectKnown(itemID))
				AddItems(ch, itemID, 1);

			itemID = "recipe_harpoon";
			if (rand(3) == 0 && !isMultiObjectKnown(itemID))
				AddItems(ch, itemID, 1);
		}

		if (rand(3) == 3) AddItems(ch, "mineral11", 1 + rand(2));	// "Точильный камень"
		if (rand(3) == 3) AddItems(ch, "mineral16", 1 + rand(2));	// "Гвозди"
	}
	else if (ch.sex == "woman")
	{
		if (rank >= 5)
		{
			if (rand(3) == 3)
				AddItems(ch, "mortar_and_pestle", 1);

			if (rand(3) == 2)
				AddItems(ch, "lamp", 1);

			if (rank >= 7)
			{
				itemID = "recipe_potion1";
				if (rand(3) == 1 && !isMultiObjectKnown(itemID))
					AddItems(ch, itemID, 1);
			}
		}

		if (rand(3) == 3) AddItems(ch, "mineral14", 1 + rand(2));	// "Ножницы"
		if (rand(3) == 3) AddItems(ch, "mineral13", 1 + rand(2));	// "Бронзовый котелок"
	}
	// < КРАФТ

	// Warship Переделка - новая система генерации оружия
	irand = rand(3);
    if(irand == 1) GenerateAndAddItems(ch, "blade5", Rand(2) + 1); // кинжал
	irand = rand(3);
    if(irand == 1) GenerateAndAddItems(ch, "blade1", Rand(2) + 1);
	irand = rand(3);
    if(irand == 1) GenerateAndAddItems(ch, "blade2", Rand(2) + 1);
	irand = rand(3);
    if(irand == 1) GenerateAndAddItems(ch, "blade3", 1);
	irand = rand(4);
    if(irand == 1) GenerateAndAddItems(ch, "blade4", 1);
    if(irand == 2) GenerateAndAddItems(ch, "blade10", Rand(1) + 1);
    if(irand == 3 && rank >= 2) GenerateAndAddItems(ch, "blade35", 1);

    irand = rand(3);
    if(irand == 1 && rank >= 3) GenerateAndAddItems(ch, "topor3", 1);
    if(irand == 2 && rank >= 5) GenerateAndAddItems(ch, "blade11", 1);

    irand = rand(6);
    if(irand == 1 && rank >= 7) GenerateAndAddItems(ch, "topor1", 1);

	if(rank >= 5)
	{
	    irand = rand(6);
		if(irand == 1) GenerateAndAddItems(ch, "blade6", 1);
		if(irand == 2) GenerateAndAddItems(ch, "blade7", Rand(1) + 1);
		if(irand == 3) GenerateAndAddItems(ch, "blade9", Rand(1) + 1);
		if(irand == 4) GenerateAndAddItems(ch, "blade8", Rand(1) + 1);
	}
	
	irand = rand(10);
    if (irand == 1 && rank >= 4) AddItems(ch, "cirass1", 1);
	irand = rand(15);
    if (irand == 1 && rank >= 8) AddItems(ch, "cirass2", 1);
	irand = rand(20);
    if (irand == 1 && rank >= 12) AddItems(ch, "cirass4", 1);

    if(rank >= 7)
	{
		irand = rand(10);
        if(irand == 1) GenerateAndAddItems(ch, "blade12", Rand(1) + 1);
	}
	
	if(rank >= 10)
	{
		irand = rand(12);
		if(irand == 1) GenerateAndAddItems(ch, "blade16", 1);
	}

	if(rank >= 13)
	{
		irand = rand(5);
		if(irand == 1) GenerateAndAddItems(ch, "blade17", 1);
        if(irand == 2) GenerateAndAddItems(ch, "blade18", 1);
	}
	
	AddItems(ch, "bullet", Rand(20) + 10);
	AddItems(ch, "grapeshot", Rand(10) + 5);
	AddItems(ch, "GunPowder", Rand(15) + 5);
	
    irand = rand(4);
    if(irand == 1) AddItems(ch, "pistol1", Rand(2) + 1);
	
	if(rank >= 2)
	{
		irand = rand(5);
		if(irand == 1) AddItems(ch, "pistol2", Rand(1) + 1);
	}
	
	if(rank >= 5)
	{
		irand = rand(7);
		if(irand == 1) AddItems(ch, "pistol3", Rand(1) + 1);
	}
	
    irand = rand(10);
    if(irand == 1) AddItems(ch, "spyglass1", 1);

	irand = rand(8);
	if(irand == 1 && rank >=3) AddItems(ch, "spyglass2", 1);
	irand = rand(15);
	if(irand == 1  && rank >=10) AddItems(ch, "spyglass3", 1);

    AddItems(ch, "potion1", Rand(8) + 1);
    irand = rand(7);
    if(irand == 1)
    {
	    AddItems(ch,"potion2", Rand(3) + 1);
	}
	
	irand = rand(5);
    if(irand == 1)
    {
	    AddItems(ch, "potion3", Rand(3) + 1);
	}
	
	irand = rand(8);
	if(irand == 1)
    {
	    AddItems(ch, "potion4", Rand(1) + 1);
	}
	
	irand = rand(3);
	if(irand == 1)
    {
        AddItems(ch, "potion5", Rand(5) + 1);
    }

	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry1", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry2", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry3", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry5", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry6", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry7", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry10", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry11", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry12", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry13", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry14", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "jewelry16", Rand(4) + 1);
	irand = rand(9);
    if(irand == 1) AddItems(ch, "jewelry17", Rand(4) + 1);
	irand = rand(9);
    if(irand == 1) AddItems(ch, "jewelry18", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "indian4", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "indian7", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "indian8", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "indian9", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "indian13", Rand(4) + 1);
	irand = rand(9);
	if(irand == 1) AddItems(ch, "indian16", Rand(4) + 1);

	// генерация карт	
	GenerateMaps(ch, 75, 150);
	
	//тотемы
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_1")) AddItems(ch, "Totem_1", 1);
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_2")) AddItems(ch, "Totem_2", 1);
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_3")) AddItems(ch, "Totem_3", 1);
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_4")) AddItems(ch, "Totem_4", 1);
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_5")) AddItems(ch, "Totem_5", 1);
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_6")) AddItems(ch, "Totem_6", 1);
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_7")) AddItems(ch, "Totem_7", 1);
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_8")) AddItems(ch, "Totem_8", 1);
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_9")) AddItems(ch, "Totem_9", 1);
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_10")) AddItems(ch, "Totem_10", 1);
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_13")) AddItems(ch, "Totem_13", 1);
	if(rand(200) == 77 && !CheckMainHeroTotem("Totem_14")) AddItems(ch, "Totem_14", 1);
}

string PlaceCharacter(aref ch, string group, string location) //boal change
{  // location = "random"  "random_free"  и "random_must_be" - должен быть, даже если все занято  random_must_be_near - рядом
	float locx, locy, locz;
	string homelocator;
	bool ok;
	
	GetCharacterPos(GetMainCharacter(), &locx, &locy, &locz);
	if (location == "random_free") location = "random"; // совместимость с пред. правкой
	
	if (location == "random" || location == "random_must_be")
	{
		homelocator = LAi_FindFreeRandomLocator(group);
		ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
	}
	else
	{
		homelocator = LAi_FindNearestFreeLocator(group, locx, locy, locz);
		if (location == "random_must_be_near")
		{
		    ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
		}
		else
		{
			ChangeCharacterAddressGroup(ch, location, group, homelocator);
		}
	}

	if (homelocator == "" && location == "random_must_be") // дело плохо, свободных уже нет, но НПС-то нужен, ищем занятый
	{
	    homelocator = LAi_FindFarLocator(group, locx, locy, locz);
		ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
	}
	if (homelocator == "" && location == "random_must_be_near") // дело плохо, свободных уже нет, но НПС-то нужен, ищем занятый
	{
	    homelocator = LAi_FindNearestLocator(group, locx, locy, locz);
		ChangeCharacterAddressGroup(ch, pchar.location, group, homelocator);  // всегда, где ГГ
	}
	DeleteAttribute(&TEV, "place_check");
    return homelocator; // boal нужно проверять куда его занесло
}

void PrepareVisitCity()
{
	string sQuest;
	for (int i=0; i<MAX_COLONIES; i++)
	{
		if (Colonies[i].nation != "none")
		{
			sQuest = "VisitColony_" + Colonies[i].id;
			pchar.quest.(sQuest).win_condition.l1 = "location";
			pchar.quest.(sQuest).win_condition.l1.location = Colonies[i].id + "_town";
			pchar.quest.(sQuest).win_condition = "FirstVisitCity";
			pchar.quest.(sQuest).function      = "FirstVisitCity";
			pchar.quest.(sQuest).colonyId = Colonies[i].id;
		}
	}
}

void FirstVisitCity(string sQuest)
{
	string sColony = pchar.quest.(sQuest).colonyId;
	Colonies[FindColony(sColony)].visited = true;
}

// переделал 25.09.06 метод не зависит от ГГ, просто ранд корабли для порта
// KZ 19.11.25 ref > охрана порта только на военных/универсальных кораблях; торговцы с 90% шансом на торговых кораблях, c 10% на военных/универсальных
int GenerateShipForPort(aref chr, int isLock, int iEncType)
{
	// Коммендант форта
	if (iEncType == FORT_COMMANDER)
		return GenerateShip(SHIP_FORT, isLock);

	int i, iShipType, iMaxShipsType;
	string sTradeShips[2], sWarShips[2];
	ref rShip;

	// Старое, пусть пока будет. TODO > (потом) сделать зависимость крутости кораблей от развитости колонии или силы форта
	if (sti(chr.nation) != PIRATE)
	{
		if (rand(100) > 70)
			iMaxShipsType = SHIP_FRIGATE_H;
		else
			iMaxShipsType = SHIP_BRIG;
	}
	else
	{
	 	if (rand(100) > 70)
			iMaxShipsType = SHIP_BATTLESHIP;
		else
			iMaxShipsType = SHIP_GALEON_L;
	}

	for (i = 0; i <= iMaxShipsType; i++)
	{
		makeref(rShip, ShipsTypes[i]);

		if (CheckAttribute(rShip, "Type.War") && sti(rShip.Type.War) > 0)
			ArrayAddValue(&sWarShips, "" + i); // массив военных и универсальных кораблей
		else if (CheckAttribute(rShip, "Type.Merchant") && sti(rShip.Type.Merchant) > 0)
			ArrayAddValue(&sTradeShips, "" + i); // массив торговых кораблей
	}

	// на случай, если вдруг энкаунтер не FORT_DEFENDER и не TRADER
	iShipType = func_max(sti(ArrayGetRandomValue(&sTradeShips)), sti(ArrayGetRandomValue(&sWarShips)));

	switch (iEncType)
	{
		// военный в порту
		case FORT_DEFENDER:
			iShipType = sti(ArrayGetRandomValue(&sWarShips));

			// вояка не должен быть на корабле ниже 6 класса
			if (iShipType < SHIP_LUGGER)
				iShipType = SHIP_LUGGER + rand(iMaxShipsType - SHIP_LUGGER);
		break;

		// торговец в порту
		case TRADER:
			if (rand(9) == 2)
				iShipType = sti(ArrayGetRandomValue(&sWarShips)); // 10% шанс, что торговец будет на военнике или универсале
			else
				iShipType = sti(ArrayGetRandomValue(&sTradeShips));
		break;
	}

	Restrictor(&iShipType, rand(2), iMaxShipsType); // баркасы и тартаны пореже

	return GenerateShip(iShipType, isLock);
}

int FindFirstEmptyCharacter()
{
	for(int i = GlobalCharacters; i<TOTAL_CHARACTERS; i++)
	{
		if (characters[i].id == "0")
		{
			if (i >= MAX_CHARACTERS) MAX_CHARACTERS = i+1; //сдвигаем планку НПС
			return i;
		}
	}		
	return -1;
}

void AddGeometryToLocation(string LocationID, string ModelName)
{
	ref LocationRef;
	int n = 1;
	string str;
	locationRef = &locations[FindLocation(LocationID)];

	for(n = 1; n < 10; n++)
	{
		str = "l" + n;
		if(!CheckAttribute(LocationRef, "models.always." + str))
		{
			LocationRef.models.always.(str) = ModelName;
			LocationRef.models.always.(str).tech = "DLightModel";
			break;
		}
	}
}	

void RemoveGeometryFromLocation(string LocationID, string ModelName)
{
	ref LocationRef;
	int n = 1;
	string str;
	//trace("FUNCTION RemoveGeometryFromLocation reports: Current location ID is " + LocationID + " and geometry " + ModelName + " should be removed");
	if(FindLocation(LocationID) != -1)
	{
		locationRef = &locations[FindLocation(LocationID)];
	}
	else
	{
		return;
	}

	for(n = 1; n < 10; n++)
	{
		str = "l" + n;
		//trace("FUNCTION RemoveGeometryFromLocation reports: Checking Geometry name for n = " + str + ". It is " + LocationRef.models.always.(str));
		if(CheckAttribute(LocationRef, "models.always." + str) && LocationRef.models.always.(str) == ModelName)
		{
			DeleteAttribute(LocationRef, "models.always." + str);
			break;
		}
	}
}	

//функция заполнения массива arrayNPCModel из строки с моделями
void FillArrayNPCModel(string modelList)
{
	string value;
	int iCount = KZ|Symbol(modelList, ",");
	for (int i = 0; i <= iCount; i++)
	{
		value = GetSubStr(modelList, ",", i);
		arrayNPCModel[i] = value;
	}
}

//функция для получения уникальной модели носильщиков
string GetUniqCarrierModel(string sType)
{
	string modelList;
	int index = -1;
	string result = "";

	switch (sType)
	{
		case "carrier_city":
			modelList = "GenresBag1,GenresBag2,GenresBarrel1,GenresBarrel2,GenresBarrelTop1,GenresBarrelTop2,GenresBottle1,GenresBottle2,GenresChest1,GenresChest2";
		break;
		case "carrier_mine":
			modelList = "SlaveGenresBag1,SlaveGenresBag2,SlaveGenresBag3,SlaveGenresBag4,SlaveGenresBag5,SlaveGenresBarrel1,SlaveGenresBarrel2,SlaveGenresBarrelTop1,SlaveGenresChest1,SlaveGenresChest2";
		break;
		case "carrier_plantation":
			modelList = "SlaveGenresBag1,SlaveGenresBag2,SlaveGenresBag3,SlaveGenresBag4,SlaveGenresBag5,SlaveGenresBarrel1,SlaveGenresBarrel2,SlaveGenresBarrelTop1,SlaveGenresBarrelTop2,SlaveGenresCane1,SlaveGenresCane2,SlaveGenresCane3,SlaveGenresCane4,SlaveGenresCane5,SlaveGenresCane6,SlaveGenresChest1,SlaveGenresChest2";
		break;
	}
	index = ArrayFindRandomIndex(&arrayNPCModel, modelList);
	if (index == -1)
	{
		FillArrayNPCModel(modelList);
		index = ArrayFindRandomIndex(&arrayNPCModel, modelList);
	}
	result = arrayNPCModel[index];
	arrayNPCModel[index] = "";

	return result;
}

void CreateModel(int iChar, string sType, int iSex)
{
	int iNation = sti(characters[iChar].nation);
	
	string sBody = "";
	string sPrefix = "_";
	string sResult = "";
	int iNumber = -1;
		
	switch (sType)
	{
	
	// ReCon Team -->
	// ОФИЦЕРЫ
		case "army_off":	sBody = "off"; iNumber = rand(1)+5;		 break;	//Офицеры армии
		case "urban_off":	sBody = "off"; iNumber = rand(1)+3;		 break;	//Офицеры городской стражи
		case "milit_off":	sBody = "off"; iNumber = rand(1)+1;		 break;	//Офицеры ополчения
		case "navy_off":	sBody = "navy_off"; iNumber = rand(1)+1; break;	//Офицеры флота (МЛАДШИЕ)
	// СОЛДАТЫ
		case "army_sold":	sBody = "sold";  iNumber = rand(7)+1;	 break;	//Пехотинцы
		case "army_veteran":sBody = "sold";  iNumber = rand(7)+9;	 break;	//Пехотинцы-ветераны
		case "urban_sold":	sBody = "urban"; iNumber = rand(7)+1;	 break;	//Городская стража
		case "urban_mush":	sBody = "urban_mush"; iNumber = rand(7)+1;	 break;	//Городская стража (мушкетеры)
		case "milit_sold":	sBody = "milit"; iNumber = rand(7)+1;	 break;	//Ополчение
		case "navy_sold":	sBody = "navy";  iNumber = rand(7)+1;	 break;	//Морпехи
		case "navy_veteran":sBody = "navy";  iNumber = rand(7)+9;	 break;	//Морпехи-ветераны
		case "navy_mush":	sBody = "navy_mush";  iNumber = rand(5)+1;	 break;	//Морпехи (мушкетеры)
		case "guard":		sBody = "guard"; iNumber = rand(3)+1;	 break;	//Гвардейцы
	// ЭЛИТА
		case "elite_fra":	sBody = "elite";  iNumber = rand(7)+1;	 break;	//Мальтийцы
		case "elite_eng":	sBody = "elite";  iNumber = rand(4)+1;	 break;	//Хайлендеры
		case "elite_eng_mush":sBody = "elite";  iNumber = rand(4)+1; break;	//Хайлендеры
		case "elite_spa":	sBody = "elite";  iNumber = rand(2)+1;	 break;	//Конкистадоры
		case "elite_hol":	sBody = "elite";  iNumber = rand(1)+1;	 break;	//Ландскнехты
	// <-- ReCon Team
		
		// Пираты-мушкетеры в городах
		case "pirate_mush":
			sBody = "mush_ctz";
			iNumber = rand(2)+7;
		break;
		
		case "pofficer":
			sBody = "officer";
			iNumber = rand(19)+1;
		break;
		
		case "senior":
			sBody = "officer";
			iNumber = rand(7)+21;
		break;
		
		case "pirate":
			sBody = "pirate";
			iNumber = rand(15)+1;
		break;
		
		case "smuggler":
			sBody = "citiz";
			iNumber = rand(9)+21;
		break;

		case "trader":
			sBody = "trader";
			iNumber = rand(15)+1;
		break;

		case "merchant":
			sBody = "merch";
			iNumber = rand(14)+1;
		break;
		
		case "shipowner":
			sBody = "shipowner";
			iNumber = rand(16)+1;
		break;
		
		case "citizen":
			if(iSex == MAN)
			{
				sBody = "citiz"; // Горожане
				iNumber = rand(9)+11;
			}
			else
			{
				sBody = "women"; // Женщины
				iNumber = rand(11)+1;
			}
		break;
		
		case "girl": // Девушки
			sBody = "girl";
			iNumber = rand(9)+1;
		break;
		
		case "oldwoman": // Бабушки
			sBody = "oldWoman";
			iNumber = rand(1)+1; // для улиц только 2
		break;
		
		case "commoner": // Простолюдины
			sResult = GetRandSubString(COMMONERS);
		break;
		
		case "diplomat": // Дипломаты
			if(rand(30) <= 14)
			{
				sBody = "usurer";
				iNumber = rand(14)+1;
			}
			else
			{
				sBody = "portman";
				iNumber = rand(15)+1;
			}
		break;
		
		case "hawker": // Лоточники
			if(iSex == MAN)
			{
				sBody = "MarketMan";
				iNumber = rand(4)+1;
			}
			else
			{
				sBody = "MarketGirl";
				iNumber = rand(4)+1;
			}
		break;
		
		case "sailor": // Матросы
			sBody = "citiz";
			iNumber = rand(9)+31;
		break;

		case "noble": // Дворяне
			if(iSex == MAN)
			{
				sBody = "citiz";
				iNumber = rand(9)+1;
			}
			else
			{
				sBody = "lady";
				iNumber = rand(6)+1;
			}
		break;
		
		case "gipsy": // Цыганки
			sBody = "gipsy";
			iNumber = rand(3)+1;
		break;
		
		case "monk": // Монахи
			sBody = "monk";
			iNumber = rand(5)+1;
		break;
		
		case "convict": // Каторжники
			sBody = "slave";
			iNumber = rand(8)+1;
		break;
		
		case "mercenary": // Наёмники (элита)
			sBody = "citiz";
			iNumber = rand(9)+51;
		break;
		
		case "whore": // Шлюхи
			sBody = "horse0";
			sPrefix = "";
			iNumber = rand(7)+1;
		break;
		
		case "skel": // Скелеты
			sBody = "Skel";
			sPrefix = "";
			iNumber = rand(3)+1;
		break;
		
		case "sailor_merchant":
			aref aSailors;
			makearef(aSailors, Nations[iNation].boardingModel.merchant);
			iNumber = Rand(GetAttributesNum(aSailors) - 1);
			sResult = GetAttributeN(aSailors, iNumber);
		break;
		
		case "miskito":	// Мискито
			sBody = "miskito";
			iNumber = rand(5)+1;
		break;
		
		case "canib":	// Карибы
			sBody = "canib";
			iNumber = rand(5)+1;
		break;

		case "hwic":	// Наёмники ГВИК
			sBody = "wic_hol";
			iNumber = rand(7)+1;
		break;

		case "rivados":	// остатки клана Ривадос ГПК
			sBody = "rivados";
			iNumber = rand(6)+1;
		break;

		case "rivados_mush": // мушкетеры клана Ривадос ГПК
			sBody = "mush_rvd";
			iNumber = rand(2)+1;
		break;

		case "slaves": // рабы
			sBody = "slave";
			iNumber = rand(8)+1;
		break;
	}
	
	bool isNeedPrefix1 = HasSubStr(sType,"_off") || HasSubStr(sType,"_sold") || HasSubStr(sType,"_vet") || HasSubStr(sType,"elite") || sType == "guard";
	bool isNeedPrefix2 = sBody == "urban_mush";
	
	if(isNeedPrefix1 || isNeedPrefix2)
	{
		if (iNation != PIRATE)
		{
			sPrefix = "_" + NationShortName(iNation) + "_";
		}
	}
	
	// AlexBlade - Армейские мушкетеры, для пиратов отдельный кейс выше
	if (sType == "army_sold_mush") {
		switch (iNation)
		{
			case ENGLAND:	sBody = "eng_mush"; iNumber = rand(7)+1; sPrefix = "_"; break;
			case FRANCE:	sBody = "fra_mush"; iNumber = rand(7)+1; sPrefix = "_"; break;
			case SPAIN:		sBody = "spa_mush"; iNumber = rand(7)+1; sPrefix = "_"; break;
			case HOLLAND:	sBody = "hol_mush"; iNumber = rand(7)+1; sPrefix = "_"; break;
		}
	}
	
	if(sType != "commoner" && sType != "sailor_merchant")
	sResult = sBody+sPrefix+iNumber;
	
	characters[iChar].model = sResult;

	FaceMaker(&characters[iChar]);
}

// метод вернёт случайный дружественный iNation город, неравный  sBeginColony _checkPort - Проверка порта
int FindNonEnemyColonyForAdventure(int iNation, string sBeginColony, bool _checkPort)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	
	for (int i=0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation != "none")
		{
			if (_checkPort && CheckAttribute(&Colonies[i], "HasNoFort")) continue;  // без форта не берем
			
			if (GetNationRelation(sti(Colonies[i].nation), iNation) != RELATION_ENEMY && Colonies[i].id != sBeginColony && colonies[i].id != "Panama")
			{
				iArray[m] = i;
				m++;
			}
		}
	}
	
	if (m == 0)
	{
		return -1;
	}
	
	m = rand(m-1);
	m = iArray[m];
	return m;
}

int FindNonEnemyColonyForNation(int iNation, bool _checkPort)
{
	return FindNonEnemyColonyForAdventure(iNation, "NOT_IN_USE", _checkPort);
}

//TODO: УНИФИЦИРОВАТЬ, ниже нормальная функция
string FindFriendCityToMC(bool bRand) //радномный дружественный к ГГ город
{
	int n;
    int storeArray[MAX_COLONIES];
    int howStore = 0;
	int nation = GetBaseHeroNation();
	if (nation == PIRATE) nation = ENGLAND;
	int curIsland = GetCharacterCurrentIsland(pchar);

	for(n = 0; n < MAX_COLONIES; n++)
	{
		bool notSameIsland = (curIsland < 0) || (Islands[curIsland].id != colonies[n].island);
		if (notSameIsland && colonies[n].id != "Panama" && colonies[n].nation != "none" && colonies[n].nation != PIRATE && GetNationRelation(nation, sti(colonies[n].nation)) != RELATION_ENEMY)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	
	if (howStore == 0) return "none";
	if (bRand) nation = storeArray[Rand(howStore-1)];
	else nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}

string FindCityToMC(bool bFriend, bool bRand) //радномный к ГГ город с указанным отношением
{
	int n;
    int storeArray[MAX_COLONIES];
    int howStore = 0;
	int nation = GetBaseHeroNation();
	if (nation == PIRATE) nation = ENGLAND;
	int curIsland = GetCharacterCurrentIsland(pchar);
	bool notSameIsland, relation;
	
	for(n = 0; n < MAX_COLONIES; n++)
	{
		notSameIsland = (curIsland < 0) || (Islands[curIsland].id != colonies[n].island);
		relation = bFriend == (GetNationRelation(nation, sti(colonies[n].nation)) != RELATION_ENEMY);
		if (notSameIsland && colonies[n].id != "Panama" && colonies[n].nation != "none" && colonies[n].nation != PIRATE && relation)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	
	if (howStore == 0) return "none";
	if (bRand) nation = storeArray[Rand(howStore-1)];
	else nation = storeArray[dRand(howStore-1)];
	return colonies[nation].id;
}

string FindAlliedColonyForNation(int iNation, bool _checkPort)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	string sColony = "";
	
	for (int i = 0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation != "none" && colonies[i].id != "Panama")
		{
			if (_checkPort && CheckAttribute(&Colonies[i], "HasNoFort")) // без форта не берем, если это не Форт Оранж, конечно же
			{
				if (colonies[i].id != "FortOrange") continue;
			}
			if (sti(Colonies[i].nation)== iNation)
			{
				iArray[m] = i;
				m++;
			}
		}
	}
	
	if (m == 0)
	{
		return "-1";
	}
	
	m = rand(m-1);
	m = iArray[m];
	sColony =  Colonies[m].id;
	
	return sColony;
}

string FindAlliedColonyForNationExceptColony(string sHomeColony)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	string sColony = "";

	int iNation = sti(colonies[FindColony(sHomeColony)].nation);
	
	for (int i = 0; i<MAX_COLONIES; i++)
	{
		if(colonies[i].nation != "none" && colonies[i].id != sHomeColony && colonies[i].id != "Panama")
		{
			if (sti(Colonies[i].nation) == iNation)
			{
				iArray[m] = i;
				m++;
			}
		}
	}
	
	if (m == 0)
	{
		return "-1";
	}
	
	m = rand(m-1);
	m = iArray[m];
	sColony =  Colonies[m].id;
	
	return sColony;
}

string FindColonyWithMayakExceptIsland(string sIsland)
{
	int iArray[MAX_COLONIES];
	int m = 0;
	string sColony = "";
	
	for (int i = 0; i<MAX_COLONIES; i++)
	{
		if (colonies[i].nation != "none" && GetMayakByCityName(colonies[i].id) != "" && GetArealByCityName(colonies[i].id) != sIsland)	
		{
			iArray[m] = i;
			m++;		
		}
	}
	if (m == 0)
	{
		return "-1";
	}
	m = rand(m-1);
	m = iArray[m];
	sColony =  Colonies[m].id;
	
	return sColony;	
}
/*
string SelectQuestDestinationAnyNationExceptTargetNation(int iNation)
{
	string sArray[MAX_COLONIES];
	int m = 0;

	for (int i = 0; i<MAX_COLONIES; i++)
	{
		if (sti(Colonies[i].nation) != iNation)
		{
			sArray[m] = Colonies[i].id;
			m++;
		}
	}

	if (m > 0)
	{
		m = rand(m-1);
		return sArray[m];
	}
	else
	{
		return "Error in select Destination for capture ship";
	}
}

string SelectQuestDestinationAnyNationExceptIsland(string sIsland)
{
	int m = 0;

	string sTempIsland = sIsland;

	while(sTempIsland == sisland)
	{
		m = rand(MAX_COLONIES-1);
		if(colonies[m].nation != "none")
		{
			sTempIsland = Colonies[m].island;
		}
	}
	string sTempColony  = Colonies[m].id
	return sTempColony;
}
*/
// TODO
string SelectQuestDestinationAnyNationExceptColony(string sColony)
{
	int m;

	string sTempColony = sColony;

	while(sTempColony == sColony)
	{
		m = rand(MAX_COLONIES-1);
		if(colonies[m].nation != "none")
		{
			sTempColony = Colonies[m].id;
		}
	}

	return sTempColony;
}

// ugeen --> выбор случайной бухты на острове, где находится ГГ
string SelectQuestShoreLocation() 
{
    ref CurIsland;
	int n, i;
	string TargetLocation = "";
	
	i = 0;
	n = GetCharacterCurrentIsland(pchar);
	if (n < 0) 
	{
		TargetLocation = "";
	}
	else
	{
		CurIsland = GetIslandByIndex(n);
		while(TargetLocation == "" && i < 10)
		{
			TargetLocation = GetIslandRandomFreeShoreId(CurIsland.id);
			if (TargetLocation == "")
			{
			    break;
			}
			if (!isLocationFreeForQuests(TargetLocation)) 
			{
				TargetLocation = ""; i++;
			}	
		}		
    }
	if(TargetLocation == "") TargetLocation = GetIslandRandomShoreId(CurIsland.id);
	Log_QuestInfo("TargetLocation = " + TargetLocation);
    return TargetLocation;
}

string SelectQuestShoreLocationFromSea(string CurIsland)
{
	string TargetLocation = "";
	int n, i;
	ref rIsland;
	
	i = 0;
	n = FindIsland(CurIsland);
	if (n < 0) 
	{
		TargetLocation = "None";
	}	
	else
	{
		rIsland = GetIslandByIndex(n);
		while(TargetLocation == "" && i < 10)
		{
			TargetLocation = GetIslandRandomFreeShoreId(rIsland.id);
			if (TargetLocation == "")
			{
			    break;
			}
			if (!isLocationFreeForQuests(TargetLocation)) 
			{
				TargetLocation = ""; i++;
			}	
		}		
	}
	if(TargetLocation == "") TargetLocation = GetIslandRandomShoreId(rIsland.id);
	Log_QuestInfo("TargetLocation = " + TargetLocation);
	return TargetLocation;
}

void EmptyAbordageCharacters()
{
	for (int i=GlobalCharacters; i<MAX_CHARACTERS; i++)
	{
		if (CheckAttribute(&characters[i], "AboardFantom"))	InitCharacter(&characters[i], i);		
	}
}

void EmptyAllFantomCharacter()
{
	if (bAbordageStarted) return; // иначе трутся НПС при переходе в каюте
	int cn = -1;
	for (int i=GlobalCharacters; i<MAX_CHARACTERS; i++)
	{
		// отдельный код зачистки boal -->
		if (LAi_IsDead(&characters[i]) && !CheckAttribute(&characters[i], "RebirthPhantom"))
		{
      			if(GetCompanionQuantity(&characters[i]) > 1) // Хм, а у фантомов есть компаньоны как у взрослых ГГ? оставлю на всяк случай (для ПГГ)
				{
					for(int k = 0; k < COMPANION_MAX; k++)
					{
						cn = GetCompanionIndex(&characters[i], k);
						if(cn != -1)
						{
							InitCharacter(&characters[cn], cn);
						}
					}
				}
				else
				{
     				InitCharacter(&characters[i], i);
				}
		}
		else
		{
			if (CheckAttribute(&characters[i], "LifeDay") &&
			    GetNpcQuestPastDayParam(&characters[i], "LifeTimeCreate") >= sti(characters[i].LifeDay) &&
				characters[i].location != pchar.location) // не трем, если ГГ в локации,иначе горожане пропадают на лету
			{ // время вышло
				CheckPhantomExpire(&characters[i]);
				InitCharacter(&characters[i], i);  // тут проверку на компаньонов не нужно, тк они все одинаковые по времени
			}
		}
		// boal <--
	}
}

// метод оставлен для совместимости со старым кодом К3
int GeneratePortCharacter(int iNation, int isShip, string sModel, int iSex, int isLock, int iEncType)
{
    int iChar = NPC_GeneratePhantomCharacter(sModel, iNation, iSex, -isLock);
	string sEncType = "war";

	if (IsShip == WITH_SHIP)
	{
		characters[iChar].ship.type = GenerateShipForPort(&characters[iChar], isLock, iEncType);

		if (iEncType == TRADER)
			sEncType = "trade";

		Fantom_SetRandomCrewExp(&characters[iChar], sEncType);
		SetBaseShipData(&characters[iChar]);
		SetRandomNameToShip(&characters[iChar]);
	}
	else
	{
		characters[iChar].ship.type = SHIP_NOTUSED;
		DeleteAttribute(&characters[iChar], "ship.upgrades");
	}

	return iChar;
}

int GetRandomNationForMapEncounter(string sIslandID, bool bMerchant)
{   // boal: метод соверненно не понятен, убрал из него массив НатионСтайт, заменив на 1.0, раз работало - пусть будет как было, но логика чумовая
	int iNation = -1;
	
	if(sIslandID != "")
	{
		int iIsland = FindIsland(sIslandID);
		for(int i = 0; i < MAX_COLONIES; i++)
		{
			if(colonies[i].island == sIslandID)
			{
				if (colonies[i].nation != "none")
				{
					//TODO: Надо чекать раcстояние, если их несколько
					//смотря, в какой точке генерируется
					iNation = sti(colonies[i].nation);
					break;
				}
			}
		}
	}

	float fEngland  = 1.0;
	float fFrance   = 1.0;
	float fSpain    = 1.0;
	float fHolland  = 1.0;
	float fPirate   = 1.0;

	// бонус за ближ город
	if(iNation != -1)
	{
	    switch (iNation)
		{
			case ENGLAND:
				fEngland += 0.2;
			break;
			case FRANCE:
    			fFrance += 0.2;
			break;
			case SPAIN:
    			fSpain += 0.2;
			break;
			case HOLLAND:
    			fHolland += 0.2;
			break;
			case PIRATE:
    			fPirate += 0.2;
			break;
		}
	}

	float fProbablyNation;
	if(bMerchant)
	{
		fProbablyNation = fEngland + fFrance + fSpain + fHolland;
	}
	else
	{
		fProbablyNation = fEngland + fFrance + fSpain + fHolland + fPirate;
	}

	fProbablyNation = frand(fProbablyNation);

	fFrance   = fFrance  + fEngland;
	fSpain    = fFrance  + fSpain;
	fHolland  = fSpain   + fHolland;
	fPirate   = fHolland + fPirate;

	if(bMerchant == 0)
	{
		if(fProbablyNation >= fFrance && fProbablyNation < fSpain)
		{
			return FRANCE;
		}

		if(fProbablyNation >= fSpain && fProbablyNation < fHolland)
		{
			return SPAIN;
		}

		if(fProbablyNation >= fHolland && fProbablyNation < fPirate)
		{
			return HOLLAND;
		}

		if(fEngland <= fProbablyNation)
		{
			return ENGLAND;
		}
	}
	else
	{
		if (rand(2) == 1) return HOLLAND; //голланцев на карту
		
		if(fProbablyNation >= fFrance && fProbablyNation < fSpain)
		{
			return FRANCE;
		}

		if(fProbablyNation >= fSpain && fProbablyNation < fHolland)
		{
			return SPAIN;
		}

		if(fProbablyNation >= fHolland && fProbablyNation < fPirate)
		{
			return HOLLAND;
		}

		if(fEngland <= fProbablyNation)
		{
			return ENGLAND;
		}
	}

	return PIRATE;
}


string CheckingTranslate(int idLngFile, string idString)
{
	string retString = LanguageConvertString ( idLngFile, idString );
	if(retString=="")
	{
		trace("Warning! No text for lable <" + idString + "> into language file <LocLables.txt>");
	}
	return retString;
}

// TODO
void LaunchMoneyGraphCollect()
{
	string sYear = "year" + worldMap.date.year;
	string sMonth = "month" + worldMap.date.month;

	pchar.MoneyGraph.(sYear).(sMonth) = pchar.money;
}

string FindNearestFreeLocator(string group)
{
	float locx;
	float locy;
	float locz;
	string homelocator;
	
	GetCharacterPos(pchar, &locx, &locy, &locz);
	homelocator = LAi_FindNearestFreeLocator(group, locx, locy, locz);
	
	return homelocator;
}

// НЕ ИСПОЛЬЗУЕТСЯ
//string SetModelFlag(aref chr)
//{
//	string sResult = "";
//
//	if(chr.chr_ai.type == LAI_TYPE_ACTOR)
//	{
//		return "";
//	}
//
//	if(CheckAttribute(&InterfaceStates,"EnabledQuestsMarks") )
//	{
//		if(sti(InterfaceStates.EnabledQuestsMarks) == 0)
//		{
//			return "";
//		}
//	}
//
//	if(CheckAttribute(chr, "quest.questflag"))
//	{
//		switch(sti(chr.quest.questflag))
//		{
//			case 1:
//				sResult = "exclamationmarkY";
//			break;
//
//			case 2:
//				sResult = "questionmarkY";
//			break;
//
//			case 3:
//				sResult = "questionmarkW";
//			break;
//		}
//	}
//
//	chr.quest.questflag.technique = GetTechNameForSign();
//
//	return sResult;
//}

string GetTechNameForSign()
{
	return "RandItem";
}

// НЕ ИСПОЛЬЗУЕТСЯ
void CheckQuestForCharacter(aref chr)
{

}

////////////////////////// boal набор методов для генерации фантомов
// boal -->
void InitCharacter(ref ch, int n)
{
	DelRelations(ch);
	DeleteNPCInRumourGroups(ch);
    //DeleteAttribute(ch,"act");
	DeleteAttribute(ch,"");
	//Logic data
	ch.id = "0";
	ch.index = n;
	ch.name 	= "none";
	ch.lastname = "none";
	ch.sex = "man";
	//Model data
	ch.model = "none";
	ch.model.entity = "NPCharacter";
	ch.model.animation = "";
	//Address
	ch.location = "none";
	ch.location.group = "";
	ch.location.locator = "";
	ch.location.from_sea = "";
	//Ship data
	ch.Ship.Type = SHIP_NOTUSED;
	//Quest data
	ch.Dialog.CurrentNode = "First time";
	ch.Dialog.TempNode = "First time";
	ch.quest.meeting = "0";
	ch.quest = "True";
	ch.quest_date = 0;
	//Misc data
	ch.nation = ENGLAND;
	ch.skill.freeskill = 0;
	ch.perks.freepoints = 0;
	ch.rank = 1;
	ch.reputation = REPUTATION_NEUTRAL;
	ch.reputation.france = 0;
	ch.reputation.england = 0;
	ch.reputation.spain = 0;
	ch.reputation.holland = 0;
	ch.reputation.pirate = 0;
	ch.reputation.smuggler = 0;
	ch.reputation.trader = 0;
	ch.fame = 1;
	// boal -->
    SetRandSPECIAL(ch);
    //InitStartParam(ch);
    SetSelfSkill(ch, 1, 1, 1, 1, 1);
    SetShipSkill(ch, 1, 1, 1, 1, 1, 1, 1, 1, 1);

	ch.Skill.FreeSPECIAL  = 0;
    ch.Health.HP        = 60.0; // отличное
	ch.Health.maxHP     = 60.0;
	ch.Health.Damg      = 0.0;
	ch.Health.weekDamg  = 0.0;
	ch.Health.TotalDamg = 0.0;
	// <--
	ch.rank = 1;
	ch.experience = 0;

	ch.Fellows.Passengers.id0 = n; // свой пассажир

	ch.Fellows.Passengers.boatswain = "-1";
	ch.Fellows.Passengers.navigator = "-1";
	ch.Fellows.Passengers.doctor = "-1";
	ch.Fellows.Passengers.cannoner = "-1";
	ch.Fellows.Passengers.treasurer = "-1";
	ch.Fellows.Passengers.carpenter = "-1";

	//ch.prisoned = false;

	ch.money = "0";
	// battle hp
	ch.headModel = "";
	//LAi_SetLoginTime(ch, 6.0, 21.98333);
	LAi_SetLoginTime(ch, 0.0, 24.0); // круглосуточно
 	LAi_SetHP(ch, LAI_DEFAULT_HP, LAI_DEFAULT_HP_MAX);
}
// boal <--
// метод ищет или создает НПС с указанным ID. Для последуешего применения
int NPC_FindOrCreateCharacter(string _id)
{
	int ci = GetCharacterIndex(_id);
	if (ci == -1)
    { // не нашли
        ci = FindFirstEmptyCharacter();
        if (ci != -1)
		{
			InitCharacter(&Characters[ci], ci);
			Characters[ci].id = _id;
		}
    }
    return ci;
}
// _ani нужно для двух рас пкм + к3
// _LifeDay - сколько дней живёт, если -1, то вечный, если 0, то трется при выходе из локации
// _equip - экипировка саблями, перки всё равно раздадутся
int NPC_GenerateCharacter(string _id, string _model, string _sex, string _ani, int _rank, int _nation, int _LifeDay, bool _equip)
{
    int iChar = NPC_FindOrCreateCharacter(_id);
	ref ch;
	if (iChar == -1) return -1;
	
    ch = &Characters[iChar];
	ch.rank 	= _rank;
    ch.nation   = _nation;
    ch.sex      = _sex;
    ch.model    = _model;
    if(ch.sex == "man")
		ch.model.height = 1.8;
	else
		ch.model.height = 1.75;
	ch.model.animation = _ani;
	FaceMaker(ch);
	SetRandomNameToCharacter(ch);
	SetFantomParamFromRank(ch, _rank, _equip);
	if (_LifeDay >= 0)
	{
	    ch.LifeDay = _LifeDay;
	    SaveCurrentNpcQuestDateParam(ch, "LifeTimeCreate");
	}
	else
	{
     	DeleteAttribute(ch, "LifeDay");
	}
	if (HasStrEx(ch.model.animation, "Danielle,Jessika", "|"))
		SetCharacterPerk(ch, "Dignity"); //HardCoffee запретим брать кулаки персонажам без кулачных анимаций
	return  iChar;
}
int NPC_GenerateCharacterEx(string _id, string _model, string _sex, string _ani, int _rank, int _nation, int _LifeDay, bool _equip, string _type)
{
    int iChar = NPC_FindOrCreateCharacter(_id);
	ref ch;
	if (iChar == -1) return -1;
	
    ch = &Characters[iChar];
	ch.rank			= _rank;
    ch.nation		= _nation;
    ch.sex			= _sex;
    ch.model		= _model;
	ch.PhantomType	= _type;
    if(ch.sex == "man")
		ch.model.height = 1.8;
	else
		ch.model.height = 1.75;
	ch.model.animation = _ani;
	FaceMaker(ch);
	//CirassMaker(ch);
	SetRandomNameToCharacter(ch);
	SetFantomParamFromRank(ch, _rank, _equip);
	if (_LifeDay >= 0)
	{
	    ch.LifeDay = _LifeDay;
	    SaveCurrentNpcQuestDateParam(ch, "LifeTimeCreate");
	}
	else
	{
     	DeleteAttribute(ch, "LifeDay");
	}
	return  iChar;
}
// сгенерим разового фантома - нашего моряка (в  форме, если патент)
ref GetOurSailor(string _id) // моежт быть нужно несколько
{
    string  smodel;
    ref     CrOur;
    string  ani;
    int     i;

    smodel = LAi_GetBoardingModel(GetMainCharacter(), &ani);
    
	i = NPC_GenerateCharacter(_id, smodel, "man", ani, 10, sti(pchar.nation), 0, true);
	CrOur = GetCharacter(i);
	CrOur.name     = UpperFirst(XI_ConvertString("sailor1"));
	CrOur.lastname = "";
	
	return CrOur;
}

int NPC_GeneratePhantomCharacter(string sType, int iNation, int iSex, int _LifeDay)
{
    int iChar = FindFirstEmptyCharacter();
    ref ch;

	if (iChar == -1) return -1;
	ch = &Characters[iChar];
    InitCharacter(ch, iChar);
    
	if (_LifeDay >= 0)
	{
	    ch.LifeDay = _LifeDay;
	    SaveCurrentNpcQuestDateParam(ch, "LifeTimeCreate");
	}
	else
	{
     	DeleteAttribute(ch, "LifeDay");
	}
	
	ch.PhantomType = sType; // не нужно пока для дела, впрок

	if (iSex == MAN)
	{
		ch.sex = "man";
		if (sType == "monk") ch.model.animation = "man_B";
		else if (HasStr(sType, "_mush")) ch.model.animation = "mushketer";
		else ch.model.animation = "man";
		ch.model.height = 1.80;
	}
	else
	{
		ch.sex = "woman";
		ch.model.animation = "towngirl";
		ch.model.height = 1.70;
	}

	ch.nation = iNation;

	SetRandomNameToCharacter(ch);
    ch.reputation = (1 + rand(44) + rand(44));// репа всем горожанам
	ch.id = "GenChar_" + iChar;
	
    CreateModel(iChar, sType, iSex);
    SetFantomParam(ch);
    
    if(HasSubStr("citizen,commoner,diplomat,hawker,monk", sType))
	{
		LAi_NPC_Equip(ch, sti(ch.rank), false, false);
	}
	else
	{
	    LAi_NPC_Equip(ch, sti(ch.rank), true, true);
	}
	
	return  iChar;
}

// boal prison count -->
int GetPrisonerQty()
{
    ref offref;
    int i, cn, iMax;
    ref mchr = GetMainCharacter();
    int qty = 0;

    iMax = GetPassengersQuantity(mchr);
    for(i=0; i < iMax; i++)
    {
        cn = GetPassenger(mchr,i);
        if(cn != -1)
        {
            offref = GetCharacter(cn);
            if(CheckAttribute(offref,"prisoned"))
            {
	            if(sti(offref.prisoned)==true && GetRemovable(offref)) // ставим только фантомов
	            {
                    qty++;
                }
            }
        }
    }
    return qty;
}
int SetCharToPrisoner(ref refEnemyCharacter)
{
    ref  rChTo, refMyCharacter;

    refMyCharacter =  GetMainCharacter();

    int  iNextPrisoner = FindFirstEmptyCharacter();
	
	if (iNextPrisoner != -1)
	{
	    rChTo = &Characters[iNextPrisoner];
	    InitCharacter(rChTo, iNextPrisoner);

		ChangeAttributesFromCharacter(rChTo, refEnemyCharacter, false);   // было четкое копирование, но что-то наследовалось от той жизни и в море вел по АИ убегания
	    rChTo.index = iNextPrisoner;
	    rChTo.id = "prisoner_" + iNextPrisoner;
	    if (CheckAttribute(refEnemyCharacter, "survivor")) rChTo.survivor = "";
	    rChTo.Dialog.Filename = "Capitan_ransack_dialog.c";
	    rChTo.Dialog.CurrentNode = "First time";
	    DeleteAttribute(rChTo, "items");
		DeleteAttribute(rChTo, "equip");
		DeleteAttribute(rChTo, "LifeDay"); // постоянный
		DeleteAttribute(rChTo, "ship");
		DeleteAttribute(rChTo, "ShipSails.gerald_name");

		DeleteAttribute(rChTo, "AlwaysEnemy");
		DeleteAttribute(rChTo, "ShipTaskLock");
		DeleteAttribute(rChTo, "WatchFort");
		DeleteAttribute(rChTo, "AnalizeShips");

	    rChTo.ship.type = SHIP_NOTUSED;
		GiveItem2Character(rChTo, "unarmed");
	    EquipCharacterByItem(rChTo, "unarmed");

	    rChTo.greeting = "Gr_Ransack";
				
		if(rand(2) == 1) Hold_GenQuest_Init(rChTo);
		
	    LAi_SetCitizenTypeNoGroup(rChTo);
	    LAi_group_MoveCharacter(rChTo, "Prisoner");
	    LAi_SetLoginTime(rChTo, 0.0, 24.0);
	    LAi_NoRebirthEnable(rChTo);

	    SetCharacterRemovable(rChTo, true);
	    AddPassenger(refMyCharacter,rChTo,true);
    }
    return iNextPrisoner;
}

void ReleasePrisoner(ref NPChar)
{
    DeleteAttribute(NPChar,"prisoned"); // освободили пленника
	RemovePassenger(PChar, NPChar);
	NPChar.LifeDay = 0; // трем
}

void FreeSitLocator(string location, string locator)
{
    //если уже сидим, то ссвой стул не отдаем
	if (CheckAttribute(&TEV, "begin_sit") && pchar.location == location && pchar.location.locator == locator) return;

	ref rCharacter; //ищем
	int n;
	bool bOk = false;
	float locx, locy, locz;
	string sLocator = "";

	for (n=0; n<MAX_CHARACTERS; n++)
	{
		bOk = false;
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "location"))
		{
            if (rCharacter.location == location && rCharacter.location.locator == locator)
            {
            	ChangeCharacterAddressGroup(rCharacter, "none", "none", "none"); // в никуда
            	bOk = true;
            }
            else
            {
            	if (rCharacter.location == "none") // офы, которые уже наняты, но сидят
            	{
            		//Если загруженны, то выйдем из локации
					LogoffCharacter(rCharacter);
					bOk = true;
            	}
            }
            if (bOk && IsEntity(rCharacter))
			{
				GetCharacterPos(rCharacter, &locx, &locy, &locz);

				sLocator = LAi_FindNearestLocator("tables", locx, locy, locz);
				if (sLocator != "")
				{
					TeleportCharacterToLocator(rCharacter, "tables", sLocator);
				}
				else
				{
					TeleportCharacterToPos(rCharacter, locx-0.8, locy, locz-0.8);
				}
			}
		}
    }
}

bool CheckFreeLocator(string location, string locator, int idxDontSee)
{
	return LAi_CheckLocatorFree("sit", locator);
}

//Rosarak. К сожалению проверка локаторов коллизией часто даёт сбой; TODO: посмотреть в движке
//Для таверн будем использовать оба метода проверки
bool CheckFreeLocatorEx(string location, string locator, int idxDontSee)
{
	ref rCharacter; //ищем
	int n;

	for (n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, "location") && n != idxDontSee) // не смотрим самого себя, если нужно
		{
            if (rCharacter.location == location && rCharacter.location.locator == locator)
            {
				return false;
            }
		}
    }
    return true;
}
// boal <--

int RandFromThreeDight(int _Num1, int _Num2, int _Num3)
{
	switch (rand(2))
	{
		case 0: return _Num1; break;
		case 1: return _Num2; break;
		case 2: return _Num3; break;
	}
}

// Отключить на время форт (потом сам восстановится)
void MakeFortDead(string _ColonyFort)
{
	int ind = GetCharacterIndex(_ColonyFort + " Fort Commander");
	if(ind == -1) return;
	ref FC = &Characters[ind];
	FC.Fort.Mode = FORT_DEAD;
	// data of fort die
	FC.Fort.DieTime.Year = GetDataYear();
	FC.Fort.DieTime.Month = GetDataMonth();
	FC.Fort.DieTime.Day = GetDataDay();
	FC.Fort.DieTime.Time = GetTime();
	Event(FORT_DESTROYED, "l", sti(FC.index));
}

// ugeen --> получить наиболее дальний из группы локаторов для постановки квестовых  кораблей
string GetSeaQuestShipFarLocator(ref _loc, string group, float x, float y, float z)
{
	if(CheckAttribute(_loc, group) == 0) return "";
	aref grp;
	makearef(grp, _loc.(group));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist = -1;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float dx = x - stf(loc.x);
		float dy = y - stf(loc.y);
		float dz = z - stf(loc.z);
		float d = dx*dx + dy*dy + dz*dz;
		if(j >= 0)
		{
			if(d >= dist)
			{
				dist = d;
				j = i;
			}
		}
		else
		{
			j = i;
			dist = d;
		}				
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}

// ugeen --> получить наиболее ближний из группы локаторов для постановки квестовых  кораблей
string GetSeaQuestShipNearestLocator(ref _loc, string group, float x, float y, float z)
{
	if(CheckAttribute(_loc, group) == 0) return "";
	aref grp;
	makearef(grp, _loc.(group));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist = -1;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		if (HasStr(GetAttributeName(loc), "fort")) continue; //локаторы содержащие в имени "fort" скипаем
		float dx = x - stf(loc.x);
		float dy = y - stf(loc.y);
		float dz = z - stf(loc.z);
		float d = dx*dx + dy*dy + dz*dz;
		if(j >= 0)
		{
			if(d < dist)
			{
				dist = d;
				j = i;
			}
		}
		else
		{
			j = i;
			dist = d;
		}
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}

string GetModelType(string model)	//Rosarak. Для SetNPCModelUniq
{									//TODO: отрефакторить
	int iNum;
	
	if(HasSubStr(model, "sold_"))
	{
		model = StrReplaceAll(model, "sold_", "");
		iNum = sti(FindStringAfterChar(model, "_"));
		if(iNum < 9) return "army_sold";
		else return "army_veteran";
	}
	
	if(HasSubStr(model, "navy_") && !HasSubStr(model, "off"))
	{
		model = StrReplaceAll(model, "navy_", "");
		iNum = sti(FindStringAfterChar(model, "_"));
		if(iNum < 9) return "navy_sold";
		else return "navy_veteran";	
	}
	
	if(HasSubStr(model, "Skel"))
	{
		return "skel";
	}
	
	iNum = sti(FindStringAfterChar(model, "_"));
	model = FindStringBeforeChar(model, "_");
	
	switch(model)
	{
		case "pirate": return "pirate"; break;
		
		case "citiz":
			if(iNum < 11) return "noble";
			if(iNum < 21) return "citizen";
			if(iNum < 31) return "smuggler";
			if(iNum < 41) return "sailor";
			if(iNum < 51) return "commoner";
			if(iNum < 61) return "mercenary";
		break;
		
		case "barmen":
			if(iNum == 0 || iNum == 1 || iNum == 13) return "commoner";
		break;
		
		case "shipowner":
			if(iNum == 5) return "commoner";
		break;
	}
	
	return ""; //Если тип не нашёлся, то в SetNPCModelUniq ничего не меняем
}

// evganat - энциклопедия
void GetPage(string sTome, int iPage)
{
	if (ENCYCLOPEDIA_DISABLED) return;
	if(GetCharacterItem(pchar, "encyclopedia") <= 0)
	{
		GiveItem2Character(pchar, "encyclopedia");
	    DoQuestFunctionDelay("Tutorial_Encyclopedia", 1.5);
	}

	if(sTome == "")
	{
		sTome = GetRandomTome();
	}
	
	if(iPage == 0)
		iPage = rand(4)+1;
	
	string sPage = "p"+iPage;
	
	if(!CheckAttribute(pchar, "encyclopedia.tomes."+sTome+"."+sPage))
		pchar.encyclopedia.tomes.(sTome).(sPage) = 0;
	
	pchar.encyclopedia.tomes.(sTome).(sPage) = sti(pchar.encyclopedia.tomes.(sTome).(sPage)) + 1;
	
	if(sti(pchar.encyclopedia.tomes.(sTome).(sPage)) == 1)
	{
		AddCharacterSkillDontClearExp(pchar, sTome, 1);	// увеличиваем навык на единицу, опыт идёт
		// записываем бонус в атрибуты
		string sParam = GetPageBonusParam(sTome, iPage);
		string sBonus = GetParamPageBonusSlow(sParam);
		pchar.encyclopedia.bonus.(sParam) = ColorText("(+"+sBonus+")", "gold");	// текст для меню перков
		pchar.encyclopedia.bonus.(sParam).value = sBonus;	// атрибут для быстрого доступа
		// применение бонуса к активным перкам
		int iBonus = 0;
		if(sParam == "Rush")
		{
			iBonus = sti(sBonus);
			ChrPerksList.list.Rush.TimeDelay = sti(ChrPerksList.list.Rush.TimeDelay) + iBonus;
			ChrPerksList.list.Rush.TimeDuration = sti(ChrPerksList.list.Rush.TimeDuration) + iBonus;
		}
		if(sParam == "ImmediateReload")
		{
			iBonus = sti(sBonus);
			ChrPerksList.list.ImmediateReload.TimeDelay = sti(ChrPerksList.list.ImmediateReload.TimeDelay) + iBonus;
			ChrPerksList.list.ImmediateReload.TimeDuration = sti(ChrPerksList.list.ImmediateReload.TimeDuration) + iBonus;
		}
	}
	
	LogSound_WithNotify(StringFromKey("InfoMessages_120"), "Notebook_2", "Document");

	int mPage;
	string mTome;
	if(!GetRandomMissingPage(&mTome, &mPage))
	{
		pchar.encyclopedia.full = true;
		pchar.encyclopedia.bonus.SharedExperience = ColorText(StringFromKey("InfoMessages_122"), "gold");
		LogSound_WithNotify(StringFromKey("InfoMessages_121"), "Notebook_2", "Document");
	}
}

bool GetRandomDuplicatePage(ref tome, ref page)
{
	aref arTomes, arTome, arDuplicates, arDuplicate;
	if(CheckAttribute(pchar, "encyclopedia.duplicates"))
		DeleteAttribute(pchar, "encyclopedia.duplicates");
	makearef(arTomes, pchar.encyclopedia.tomes);
	int n = GetAttributesNum(arTomes);
	string sPage, sTome, sTemp;
	bool bOk = false;
	for(int i=0; i<n; i++)
	{
		arTome = GetAttributeN(arTomes, i);
		sTome = GetAttributeName(arTome);
		for(int j=1; j<=5; j++)
		{
			sPage = "p"+j;
			if(CheckAttribute(arTome, sPage) && sti(arTome.(sPage)) > 1)
			{
				sTemp = sTome+sPage;
				pchar.encyclopedia.duplicates.(sTemp).tome = sTome;
				pchar.encyclopedia.duplicates.(sTemp).page = j;
				bOk = true;
			}
		}
	}
	
	if(!bOk)
		return false;
	
	makearef(arDuplicates, pchar.encyclopedia.duplicates);
	n = GetAttributesNum(arDuplicates);
	int iRand = rand(n-1);
	arDuplicate = GetAttributeN(arDuplicates, iRand);
	tome = arDuplicate.tome;
	page = sti(arDuplicate.page);
	return true;
}

bool GetRandomMissingPage(ref tome, ref page)
{
	string sTome, sPage, sTemp;
	aref arMissing, arMiss;
	bool bOk = false;
	if(CheckAttribute(pchar, "encyclopedia.missing"))
		DeleteAttribute(pchar, "encyclopedia.missing");
	for(int i=0; i<12; i++)
	{
		switch(i)
		{
			case 0:		sTome = "Leadership";	break;
			case 1:		sTome = "FencingLight";	break;
			case 2:		sTome = "Fencing";		break;
			case 3:		sTome = "FencingHeavy";	break;
			case 4:		sTome = "Pistol";		break;
			case 5:		sTome = "Sneak";		break;
			case 6:		sTome = "Fortune";		break;
			case 7:		sTome = "Sailing";		break;
			case 8:		sTome = "Accuracy";		break;
			case 9:		sTome = "Cannons";		break;
			case 10:	sTome = "Defence";		break;
			case 11:	sTome = "Repair";		break;
		}
		for(int j=1; j<=5; j++)
		{
			sPage = "p"+j;
			if(!CheckAttribute(pchar, "encyclopedia.tomes."+sTome+"."+sPage))
			{
				sTemp = sTome+sPage;
				pchar.encyclopedia.missing.(sTemp).tome = sTome;
				pchar.encyclopedia.missing.(sTemp).page = j;
				bOk = true;
			}
		}
	}
	
	if(!bOk)
		return false;
	
	makearef(arMissing, pchar.encyclopedia.missing);
	int n = GetAttributesNum(arMissing);
	int iRand = rand(n-1);
	arMiss = GetAttributeN(arMissing, iRand);
	tome = arMiss.tome;
	page = sti(arMiss.page);
	return true;
}

string GetTomeStringGen(string sTome)
{
	return GetConvertStr(sTome+"_gen", "Encyclopedia.txt");
}

string GetPageString(int iPage)
{
	string res = "";
	switch(iPage)
	{
		case 1:		res = XI_ConvertString("PageOne");		break;
		case 2:		res = XI_ConvertString("PageTwo");		break;
		case 3:		res = XI_ConvertString("PageThree");	break;
		case 4:		res = XI_ConvertString("PageFour");	    break;
		case 5:		res = XI_ConvertString("PageFive");		break;
	}
	return res;
}

string GetRandomTome()
{
	string sTome;
	int iRnd = dRandEx(11, true);
	switch(iRnd)
	{
		case 0:		sTome = "Leadership";	break;
		case 1:		sTome = "FencingLight";	break;
		case 2:		sTome = "Fencing";		break;
		case 3:		sTome = "FencingHeavy";	break;
		case 4:		sTome = "Pistol";		break;
		case 5:		sTome = "Sneak";		break;
		case 6:		sTome = "Fortune";		break;
		case 7:		sTome = "Sailing";		break;
		case 8:		sTome = "Accuracy";		break;
		case 9:		sTome = "Cannons";		break;
		case 10:	sTome = "Defence";		break;
		case 11:	sTome = "Repair";		break;
	}
	return sTome;
}

string GetRandomTomeToMerch(string sID)
{
	string sTome;
	int iRnd = idRand(sID +"tome", 11);
	switch(iRnd)
	{
		case 0:		sTome = "Leadership";	break;
		case 1:		sTome = "FencingLight";	break;
		case 2:		sTome = "Fencing";		break;
		case 3:		sTome = "FencingHeavy";	break;
		case 4:		sTome = "Pistol";		break;
		case 5:		sTome = "Sneak";		break;
		case 6:		sTome = "Fortune";		break;
		case 7:		sTome = "Sailing";		break;
		case 8:		sTome = "Accuracy";		break;
		case 9:		sTome = "Cannons";		break;
		case 10:	sTome = "Defence";		break;
		case 11:	sTome = "Repair";		break;
	}
	return sTome;	
}

bool CheckRandomPage(string sSituation, string sTag, int iTag)
{
	if (ENCYCLOPEDIA_DISABLED) return false;

	int iRand = 100;		// общее количество исходов, по умолчанию 100
	int iReq = 0;			// количество благоприятных исходов
	bool bFirst = false;	// на всякий случай флаг первой попытки такого типа
	bool bRes = false;		// результат
	int iBonusNation;		// бонусы наций, меняются после каждого успеха
	string sNation;			// вспомогательный стринг для нации
	int iBonusQuest;		// бонус квеста, накапливается или не накапливается
	int iMaxProb;			// лимит вероятности
	// вычисляем прошедшие с прошлой успешной попытки дни, недели и месяцы (по 30 дней считаем)
	if(!CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".last"))
	{
		bFirst = true;	// первый раз
		pchar.encyclopedia.gen.(sSituation).last.year = GetDataYear();
		pchar.encyclopedia.gen.(sSituation).last.month = GetDataMonth();
		pchar.encyclopedia.gen.(sSituation).last.day = GetDataDay();
	}
	int lastDay, lastMonth, lastYear;
	lastYear = sti(pchar.encyclopedia.gen.(sSituation).last.year);
	lastMonth = sti(pchar.encyclopedia.gen.(sSituation).last.month);
	lastDay = sti(pchar.encyclopedia.gen.(sSituation).last.day);
	int iDays = GetPastTime("day", lastYear, lastMonth, lastDay, 0.0, GetDataYear(), GetDataMonth(), GetDataDay(), 0.0);
	int iWeeks = iDays / 7;
	int iMonths = iDays / 30;
	// вычисляем количество попыток с прошлой успешной
	if(!CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".try"))
	{
		bFirst = true;
		pchar.encyclopedia.gen.(sSituation).try = 0;
	}
	int iTry = sti(pchar.encyclopedia.gen.(sSituation).try);
			
	// с помощью кейсов ситуаций определяются параметры рандома
	switch(sSituation)
	{
		case "captain":	// на трупе капитана, iTag - класс корабля
			switch(iTag)
			{
				case 3:		iReq = 5 + 4*func_min(iWeeks, iTry);	break;	// 5% плюс 4% за попытку в неделю
				case 2:		iReq = 7 + 5*func_min(iWeeks, iTry);	break;	// 7% плюс 5% за попытку в неделю
				case 1:		iReq = 9 + 6*func_min(iWeeks, iTry);	break;	// 9% плюс 6% за попытку в неделю
			}
			if(iReq > 50)
				iReq = 50;	// не может превышать 50%
		break;
		
		case "fort":	// при штурме форта
			iReq = 30 + 15*func_min(iMonths, iTry);	// 30% плюс 15% за попытку в месяц
			if(iReq > 80)
				iReq = 80;	// не может превышать 80%
		break;
		
		case "trader":	// в продаже, iTag - нация, sTag - колония
			iRand = 200;	// по 0.5% за единичку
			iBonusNation = 0;
			sNation = "n"+iTag;
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".nation."+sNation))
				iBonusNation = 15*sti(pchar.encyclopedia.gen.(sSituation).nation.(sNation));	// две нации получают +7.5%, две нации получают -7.5%, пираты нейтральны
			iReq = 1 + func_min(iDays, iTry);	// 0.5% плюс 0.5% за попытку в день
			if(iReq > 40)	// не может превышать 20% без бонуса нации
				iReq = 40;
			iReq += iBonusNation;
			if(iReq < 0)
				iReq = 0;
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".last.colony") && pchar.encyclopedia.gen.(sSituation).last.colony == sTag)
				iReq = iReq / 4;	// в 4 раза меньше в той же колонии, где в прошлый раз выпала
		break;
		
		case "treasurechest":	// в суперкладе
			iReq = 30 + 10*iTry;	// 30% плюс 10% за попытку в неделю
		break;
		
		case "shorechest":	// в береговом сундуке, sTag - локация
			iReq = 10 + 5*iTry;	// 10% плюс 5% за попытку
			if(iReq > 60)
				iReq = 60;	// не может превышать 60%
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".last.shore") && pchar.encyclopedia.gen.(sSituation).last.shore == sTag)
				iReq = iReq / 4;	// в 4 раза меньше на том же побережье, где в прошлый раз выпала
		break;
		
		case "cabinchest":	// в сундуке каюты 1 класса
			iReq = 10 + 5*func_min(iWeeks, iTry);	// 10% плюс 5% за попытку в неделю
			if(iReq > 50)
				iReq = 50;	// не может превышать 50%
		break;
		
		case "governor":	// у губернатора, iTag - нация, sTag - колония
			// нужно добавить губернатору, ростовщику и начальнику порта недельный кулдаун диалога
			iBonusNation = 0;
			sNation = "n"+iTag;
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".nation."+sNation))
				iBonusNation = 2 + 8*sti(pchar.encyclopedia.gen.(sSituation).nation.(sNation));	// две нации получают +10%, две нации получают -6%, пираты нейтральны
			iReq = 12 + 8*func_min(iWeeks, iTry);	// 12% плюс 8% за попытку в неделю
			if(iReq > 44)	
				iReq = 44;	// не может превышать 44% без бонуса нации
			iReq += iBonusNation;
			if(iReq < 0)
				iReq = 0;
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".last.colony") && pchar.encyclopedia.gen.(sSituation).last.colony == sTag)
				iReq = 0;	// в той же колонии два раза подряд не может быть
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".colonies."+sTag) && sti(pchar.encyclopedia.gen.(sSituation).colonies) < 6)
				iReq = 0;	// нельзя добиться повторного успеха в той же колонии, пока не найдена страница хотя бы у 6 губернаторов
		break;
		
		case "usurer":	// у ростовщика, iTag - нация, sTag - колония
			// нужно добавить губернатору, ростовщику и начальнику порта недельный кулдаун диалога
			iBonusNation = 0;
			sNation = "n"+iTag;
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".nation."+sNation))
				iBonusNation = 2 + 8*sti(pchar.encyclopedia.gen.(sSituation).nation.(sNation));	// две нации получают +10%, две нации получают -6%, пираты нейтральны
			iReq = 14 + 10*func_min(iWeeks, iTry);	// // 14% плюс 10% за попытку в неделю
			if(iReq > 44)	
				iReq = 44;	// не может превышать 44% без бонуса нации
			iReq += iBonusNation;
			if(iReq < 0)
				iReq = 0;
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".last.colony") && pchar.encyclopedia.gen.(sSituation).last.colony == sTag)
				iReq = 0;	// в той же колонии два раза подряд не может быть
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".colonies."+sTag) && sti(pchar.encyclopedia.gen.(sSituation).colonies) < 8)
				iReq = 0;	// нельзя добиться повторного успеха в той же колонии, пока не найдена страница хотя бы у 8 ростовщиков
		break;
		
		case "portman":	// у начальника порта, iTag - нация, sTag - колония
			// нужно добавить губернатору, ростовщику и начальнику порта недельный кулдаун диалога
			iBonusNation = 0;
			sNation = "n"+iTag;
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".nation."+sNation))
				iBonusNation = 2 + 8*sti(pchar.encyclopedia.gen.(sSituation).nation.(sNation));	// две нации получают +10%, две нации получают -6%, пираты нейтральны
			iReq = 10 + 8*func_min(iWeeks, iTry);	// 10% плюс 8% за попытку в неделю
			if(iReq > 42)	
				iReq = 42;	// не может превышать 42% без бонуса нации
			iReq += iBonusNation;
			if(iReq < 0)
				iReq = 0;
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".last.colony") && pchar.encyclopedia.gen.(sSituation).last.colony == sTag)
				iReq = 0;	// в той же колонии два раза подряд не может быть
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".colonies."+sTag) && sti(pchar.encyclopedia.gen.(sSituation).colonies) < 10)
				iReq = 0;	// нельзя добиться повторного успеха в той же колонии, пока не найдена страница хотя бы у 10 начальников порта
		break;
		
		case "questjungle":	// у квестового нпс в джунглях, sTag - квест	mayorquest	rapers	churchquest 1,2
			iBonusQuest = 0;
			if(CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".bonus"))
				iBonusQuest = sti(pchar.encyclopedia.gen.(sSituation).bonus);
			iReq = 4 + func_min(iDays, iBonusQuest);	// 4% плюс 1/2/3/6% за попытку в день
			switch(sTag)
			{
				case "mayorquest":	iMaxProb = 35;				iBonusQuest = 2;		break;
				case "rapers":		iMaxProb = 25;				iBonusQuest = 1;		break;
				case "churchquest":	iMaxProb = 35 + 10*iTag;	iBonusQuest = 3*iTag;	break;
			}
			if(iReq > iMaxProb)	
				iReq = iMaxProb;	// не может превышать 25/35/45/55% в зависимости от квеста
		break;
		
		case "questcaptain":	// по квесту капитана, пиратов на необитайке	pirates		comission 1,2,3,4,5,6 (пока iTag не влияет, на всякий случай)
			iBonusQuest = 0;
			iMaxProb = 40;
			if(sTag == "comission")
			{
				iBonusQuest = 15;
				iMaxProb = 65;
			}
			iReq = 15 + 10*func_min(iMonths, iTry);	// 15% плюс 10% за попытку в месяц
			iReq += iBonusQuest;
			if(iReq > iMaxProb)	
				iReq = iMaxProb;	// не может превышать 40/65% в зависимости от квеста
		break;
		
		case "questprisoner":	// по квесту заключённого	treasure 1,2	cureer
			switch(sTag)
			{
				case "treasure":	iMaxProb = 50 - 8*iTag;		iBonusQuest = 10 - 5*iTag;	break;
				case "cureer":		iMaxProb = 50;				iBonusQuest = 10;			break;
			}
			iReq = 11 + 7*func_min(iWeeks, iTry);	// 11% плюс 7% за попытку в неделю
			iReq += iBonusQuest;
			if(iReq > iMaxProb)	
				iReq = iMaxProb;	// не может превышать 34/42/50% в зависимости от ветки
		break;
		
		case "questskeleton":	// на трупе скелета/индейца по квесту церкви
			iReq = 12 + 6*func_min(iWeeks, iTry);	// 12% плюс 6% за попытку в неделю
			if(iReq > 42)	
				iReq = 42;	// не может превышать 42%
		break;
	}
	
	int x = dRandEx(iRand-1, true);
	if(x < iReq)
		bRes = true;
	
	Log_TestInfo("Генерация страницы: выпало "+x+"/"+iRand+", необходимо "+iReq);
	
	if(bRes)	// успех
	{
		pchar.encyclopedia.gen.(sSituation).last.year = GetDataYear();
		pchar.encyclopedia.gen.(sSituation).last.month = GetDataMonth();
		pchar.encyclopedia.gen.(sSituation).last.day = GetDataDay();
		pchar.encyclopedia.gen.(sSituation).try = 0;
		if(sSituation == "trader" || sSituation == "governor" || sSituation == "usurer" || sSituation == "portman")
		{
			pchar.encyclopedia.gen.(sSituation).last.colony = sTag;
			if(!CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".colonies"))
				pchar.encyclopedia.gen.(sSituation).colonies = 0;
			if(!CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".colonies."+sTag))
			{
				pchar.encyclopedia.gen.(sSituation).colonies = sti(pchar.encyclopedia.gen.(sSituation).colonies) + 1;
				pchar.encyclopedia.gen.(sSituation).colonies.(sTag) = true;
			}
			int iRandNation1 = rand(3);
			int iRandNation2 = rand(2);
			if(iRandNation2 >= iRandNation1)
				iRandNation2++;
			for(int i=ENGLAND; i<=HOLLAND; i++)
			{
				sNation = "n"+i;
				if(i == iRandNation1 || i == iRandNation2)
					pchar.encyclopedia.gen.(sSituation).nation.(sNation) = 1;
				else
					pchar.encyclopedia.gen.(sSituation).nation.(sNation) = -1;
			}
		}
		if(sSituation == "shorechest")
		{
			pchar.encyclopedia.gen.(sSituation).last.shore = sTag;
		}
		if(sSituation == "questjungle")
		{
			DeleteAttribute(pchar, "encyclopedia.gen."+sSituation+".bonus");
		}
	}
	else	// провал
	{
		iTry++;
		pchar.encyclopedia.gen.(sSituation).try = iTry;
		if(sSituation == "questjungle")
		{
			if(!CheckAttribute(pchar, "encyclopedia.gen."+sSituation+".bonus"))
				pchar.encyclopedia.gen.(sSituation).bonus = 0;
			pchar.encyclopedia.gen.(sSituation).bonus = sti(pchar.encyclopedia.gen.(sSituation).bonus) + iBonusQuest;
		}
	}
	
	return bRes;
}

bool CheckPage(string tome, int page)
{
	string sPage = "p"+page;
	return CheckAttribute(pchar, "encyclopedia.tomes."+tome+"."+sPage);
}

string GetPageBonusParam(string tome, int page)
{
	if(!CheckPage(tome, page))
		return "";
	
	string sParam = "";
	switch(tome)
	{
		case "Leadership":
			switch(page)
			{
				case 1:		sParam = "SailsMan";		break;
				case 2:		sParam = "Tireless";		break;
				case 3:		sParam = "Grus";	break;
				case 4:		sParam = "Sliding";		break;
				case 5:		sParam = "Rush";		break;
			}
		break;
		case "FencingLight":
			switch(page)
			{
				case 1:		sParam = "Tireless";		break;
				case 2:		sParam = "Sliding";		break;
				case 3:		sParam = "BladeDancer";		break;
				case 4:		sParam = "SwordplayProfessional_defence";		break;
				case 5:		sParam = "SwordplayProfessional_critical";		break;
			}
		break;
		case "Fencing":
			switch(page)
			{
				case 1:		sParam = "Tireless";		break;
				case 2:		sParam = "Sliding";		break;
				case 3:		sParam = "BladeDancer";		break;
				case 4:		sParam = "SwordplayProfessional_defence";		break;
				case 5:		sParam = "SwordplayProfessional_critical";		break;
			}
		break;
		case "FencingHeavy":
			switch(page)
			{
				case 1:		sParam = "Tireless";		break;
				case 2:		sParam = "Sliding";		break;
				case 3:		sParam = "BladeDancer";		break;
				case 4:		sParam = "SwordplayProfessional_defence";		break;
				case 5:		sParam = "SwordplayProfessional_critical";		break;
			}
		break;
		case "Pistol":
			switch(page)
			{
				case 1:		sParam = "GunProfessional_accuracy";		break;
				case 2:		sParam = "GunProfessional_charge";		break;
				case 3:		sParam = "Grus";		break;
				case 4:		sParam = "Impression";		break;
				case 5:		sParam = "MusketsShoot";		break;
			}
		break;
		case "Sneak":
			switch(page)
			{
				case 1:		sParam = "Grus";	break;
				case 2:		sParam = "GunProfessional_accuracy";		break;
				case 3:		sParam = "SwordplayProfessional_critical";		break;
				case 4:		sParam = "SwordplayProfessional_defence";		break;
				case 5:		sParam = "Sliding";		break;
			}
		break;
		case "Fortune":
			switch(page)
			{
				case 1:		sParam = "CannonProfessional_critical";		break;
				case 2:		sParam = "SwordplayProfessional_critical";		break;
				case 3:		sParam = "Luck";		break;
				case 4:		sParam = "Sliding";		break;
				case 5:		sParam = "GunProfessional_accuracy";		break;
			}
		break;
		case "Sailing":
			switch(page)
			{
				case 1:		sParam = "SailingProfessional_speed";		break;
				case 2:		sParam = "SailingProfessional_turnrate";		break;
				case 3:		sParam = "SailsMan";		break;
				case 4:		sParam = "WindCatcher";		break;
				case 5:		sParam = "StormProfessional";		break;
			}
		break;
		case "Accuracy":
			switch(page)
			{
				case 1:		sParam = "GunProfessional_accuracy";		break;
				case 2:		sParam = "MusketsShoot";		break;
				case 3:		sParam = "CannonProfessional_critical";		break;
				case 4:		sParam = "LongRangeShoot";		break;
				case 5:		sParam = "GrapplingProfessional";		break;
			}
		break;
		case "Cannons":
			switch(page)
			{
				case 1:		sParam = "LongRangeShoot";		break;
				case 2:		sParam = "CannonProfessional_critical";		break;
				case 3:		sParam = "CannonProfessional_damage";	break;
				case 4:		sParam = "FastReload";	break;
				case 5:		sParam = "ImmediateReload";	break;
			}
		break;
		case "Defence":
			switch(page)
			{
				case 1:		sParam = "ShipDefenseProfessional_critical";		break;
				case 2:		sParam = "ShipDefenseProfessional_damage";		break;
				case 3:		sParam = "Doctor3";	break;
				case 4:		sParam = "StormProfessional";		break;
				case 5:		sParam = "SwordplayProfessional_defence";		break;
			}
		break;
		case "Repair":
			switch(page)
			{
				case 1:		sParam = "Carpenter";		break;
				case 2:		sParam = "Shipbuilder";	break;
				case 3:		sParam = "InstantRepair";	break;
				case 4:		sParam = "WindCatcher";		break;
				case 5:		sParam = "ProfessionalCommerce";		break;
			}
		break;
	}
	return sParam;
}

int GetPageBonusValue(string tome, int page)
{
	if(!CheckPage(tome, page))
		return 0;
	
	int iBonus = 0;
	switch(tome)
	{
		case "Leadership":
			switch(page)
			{
				case 1:		iBonus = 5;		break;
				case 2:		iBonus = 4;		break;
				case 3:		iBonus = 10;	break;
				case 4:		iBonus = 2;		break;
				case 5:		iBonus = 2;		break;
			}
		break;
		case "FencingLight":
			switch(page)
			{
				case 1:		iBonus = 2;		break;
				case 2:		iBonus = 2;		break;
				case 3:		iBonus = 2;		break;
				case 4:		iBonus = 2;		break;
				case 5:		iBonus = 2;		break;
			}
		break;
		case "Fencing":
			switch(page)
			{
				case 1:		iBonus = 2;		break;
				case 2:		iBonus = 2;		break;
				case 3:		iBonus = 3;		break;
				case 4:		iBonus = 2;		break;
				case 5:		iBonus = 2;		break;
			}
		break;
		case "FencingHeavy":
			switch(page)
			{
				case 1:		iBonus = 2;		break;
				case 2:		iBonus = 2;		break;
				case 3:		iBonus = 5;		break;
				case 4:		iBonus = 2;		break;
				case 5:		iBonus = 2;		break;
			}
		break;
		case "Pistol":
			switch(page)
			{
				case 1:		iBonus = 2;		break;
				case 2:		iBonus = 5;		break;
				case 3:		iBonus = 5;		break;
				case 4:		iBonus = 1;		break;
				case 5:		iBonus = 5;		break;
			}
		break;
		case "Sneak":
			switch(page)
			{
				case 1:		iBonus = 10;	break;
				case 2:		iBonus = 2;		break;
				case 3:		iBonus = 2;		break;
				case 4:		iBonus = 2;		break;
				case 5:		iBonus = 2;		break;
			}
		break;
		case "Fortune":
			switch(page)
			{
				case 1:		iBonus = 5;		break;
				case 2:		iBonus = 2;		break;
				case 3:		iBonus = 1;		break;
				case 4:		iBonus = 2;		break;
				case 5:		iBonus = 2;		break;
			}
		break;
		case "Sailing":
			switch(page)
			{
				case 1:		iBonus = 5;		break;
				case 2:		iBonus = 5;		break;
				case 3:		iBonus = 5;		break;
				case 4:		iBonus = 5;		break;
				case 5:		iBonus = 5;		break;
			}
		break;
		case "Accuracy":
			switch(page)
			{
				case 1:		iBonus = 4;		break;
				case 2:		iBonus = 5;		break;
				case 3:		iBonus = 5;		break;
				case 4:		iBonus = 5;		break;
				case 5:		iBonus = 5;		break;
			}
		break;
		case "Cannons":
			switch(page)
			{
				case 1:		iBonus = 5;		break;
				case 2:		iBonus = 5;		break;
				case 3:		iBonus = 10;	break;
				case 4:		iBonus = 10;	break;
				case 5:		iBonus = 10;	break;
			}
		break;
		case "Defence":
			switch(page)
			{
				case 1:		iBonus = 5;		break;
				case 2:		iBonus = 5;		break;
				case 3:		iBonus = 10;	break;
				case 4:		iBonus = 5;		break;
				case 5:		iBonus = 2;		break;
			}
		break;
		case "Repair":
			switch(page)
			{
				case 1:		iBonus = 5;		break;
				case 2:		iBonus = 10;	break;
				case 3:		iBonus = 10;	break;
				case 4:		iBonus = 5;		break;
				case 5:		iBonus = 5;		break;
			}
		break;
	}
	return iBonus;
}

int GetParamPageBonus(string param)
{
	if (ENCYCLOPEDIA_DISABLED) return 0;
	int iBonus = 0;
	if(CheckAttribute(pchar, "encyclopedia.bonus."+param+".value"))
		iBonus = sti(pchar.encyclopedia.bonus.(param).value);
	return iBonus;
}

int GetParamPageBonusSlow(string param)
{
	int iBonus = 0;
	switch(param)
	{
		case "SailsMan":
			iBonus += GetPageBonusValue("Leadership", 1);
			iBonus += GetPageBonusValue("Sailing", 3);	
		break;
		case "Tireless":	
			iBonus += GetPageBonusValue("Leadership", 2);
			iBonus += GetPageBonusValue("FencingLight", 1);
			iBonus += GetPageBonusValue("Fencing", 1);
			iBonus += GetPageBonusValue("FencingHeavy", 1);	
		break;
		case "Grus":		
			iBonus += GetPageBonusValue("Leadership", 3);
			iBonus += GetPageBonusValue("Pistol", 3);
			iBonus += GetPageBonusValue("Sneak", 1);	
		break;
		case "Sliding":		
			iBonus += GetPageBonusValue("Leadership", 4);
			iBonus += GetPageBonusValue("FencingLight", 2);
			iBonus += GetPageBonusValue("Fencing", 2);
			iBonus += GetPageBonusValue("FencingHeavy", 2);
			iBonus += GetPageBonusValue("Sneak", 5);
			iBonus += GetPageBonusValue("Fortune", 4);
		break;
		case "Rush":		
			iBonus += GetPageBonusValue("Leadership", 5);
		break;
		case "BladeDancer":	
			iBonus += GetPageBonusValue("FencingLight", 3);
			iBonus += GetPageBonusValue("Fencing", 3);
			iBonus += GetPageBonusValue("FencingHeavy", 3);	
		break;
		case "SwordplayProfessional_defence":	
			iBonus += GetPageBonusValue("FencingLight", 4);
			iBonus += GetPageBonusValue("Fencing", 4);
			iBonus += GetPageBonusValue("FencingHeavy", 4);
			iBonus += GetPageBonusValue("Sneak", 4);
			iBonus += GetPageBonusValue("Defence", 5);	
		break;
		case "SwordplayProfessional_critical":	
			iBonus += GetPageBonusValue("FencingLight", 5);
			iBonus += GetPageBonusValue("Fencing", 5);
			iBonus += GetPageBonusValue("FencingHeavy", 5);
			iBonus += GetPageBonusValue("Sneak", 3);
			iBonus += GetPageBonusValue("Fortune", 2);	
		break;
		case "GunProfessional_accuracy":	
			iBonus += GetPageBonusValue("Pistol", 1);
			iBonus += GetPageBonusValue("Sneak", 2);
			iBonus += GetPageBonusValue("Fortune", 5);
			iBonus += GetPageBonusValue("Accuracy", 1);	
		break;
		case "GunProfessional_charge":	
			iBonus += GetPageBonusValue("Pistol", 2);
		break;
		case "CannonProfessional_critical":		
			iBonus += GetPageBonusValue("Fortune", 1);
			iBonus += GetPageBonusValue("Accuracy", 3);
			iBonus += GetPageBonusValue("Cannons", 2);
		break;
		case "CannonProfessional_damage":
			iBonus += GetPageBonusValue("Cannons", 3);
		break;
		case "Luck":
			iBonus += GetPageBonusValue("Fortune", 3);
		break;
		case "Impression":
			iBonus += GetPageBonusValue("Pistol", 4);
		break;
		case "MusketsShoot":
			iBonus += GetPageBonusValue("Pistol", 5);
			iBonus += GetPageBonusValue("Accuracy", 2);
		break;
		case "SailingProfessional_speed":
			iBonus += GetPageBonusValue("Sailing", 1);
		break;
		case "SailingProfessional_turnrate":
			iBonus += GetPageBonusValue("Sailing", 2);
		break;
		case "WindCatcher":
			iBonus += GetPageBonusValue("Sailing", 4);
			iBonus += GetPageBonusValue("Repair", 4);
		break;
		case "StormProfessional":
			iBonus += GetPageBonusValue("Sailing", 5);
			iBonus += GetPageBonusValue("Defence", 4);
		break;
		case "LongRangeShoot":
			iBonus += GetPageBonusValue("Accuracy", 4);
			iBonus += GetPageBonusValue("Cannons", 1);
		break;
		case "GrapplingProfessional":
			iBonus += GetPageBonusValue("Accuracy", 5);
		break;
		case "FastReload":
			iBonus += GetPageBonusValue("Cannons", 4);
		break;
		case "ImmediateReload":
			iBonus += GetPageBonusValue("Cannons", 5);
		break;
		case "ShipDefenseProfessional_damage":
			iBonus += GetPageBonusValue("Defence", 2);
		break;
		case "ShipDefenseProfessional_critical":
			iBonus += GetPageBonusValue("Defence", 1);
		break;
		case "Doctor3":
			iBonus += GetPageBonusValue("Defence", 3);
		break;
		case "Carpenter":
			iBonus += GetPageBonusValue("Repair", 1);
		break;
		case "Shipbuilder":
			iBonus += GetPageBonusValue("Repair", 2);
		break;
		case "InstantRepair":
			iBonus += GetPageBonusValue("Repair", 3);
		break;
		case "ProfessionalCommerce":
			iBonus += GetPageBonusValue("Repair", 5);
		break;
	}
	return iBonus;
}

// evganat - отношение нпс к ГГ
void IncreaseNPCDisposition(ref chr, int add)
{
	//TODO: корректное определение высоты
	//if(add > 0)	SendMessage(chr, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS,  0.0,  0.0,  0.07, "Одобрение", 0.0, 255.0, 0.0);
	//else		SendMessage(chr, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS,  0.0,  0.0,  0.07, "Недовольство", 255.0, 0.0, 100.0);
	IncreaseNPCDispositionEx(chr, pchar, false, add);
}

int GetNPCDisposition(ref chr)
{
	return GetNPCDispositionEx(chr, pchar);
}

// EvgAnat, Rosarak отношения между NPC
// symmetry менять обоим сразу или только одному
void IncreaseNPCDispositionEx(ref chr1, ref chr2, bool symmetry, int add)
{
	string index  = "idx" + chr2.index;
	string index2 = "idx" + chr1.index;
	
	if(!CheckAttribute(chr1, "disposition." + index))
		chr1.disposition.(index) = 0;
	if(!CheckAttribute(chr2, "disposition." + index2)) //обоюдно, чтобы затирать без поиска
		chr2.disposition.(index2) = 0;
	
	int curRel = sti(chr1.disposition.(index)) + add;
	if(curRel >  100) curRel =  100;
	if(curRel < -100) curRel = -100;
	chr1.disposition.(index) = curRel;
	
	if(symmetry) IncreaseNPCDispositionEx(chr2, chr1, false, add);
}

int GetNPCDispositionEx(ref chr1, ref chr2)
{
	string index  = "idx" + chr2.index;
	string index2 = "idx" + chr1.index;
	
	if(!CheckAttribute(chr1, "disposition." + index))
		chr1.disposition.(index) = 0;
	if(!CheckAttribute(chr2, "disposition." + index2))
		chr2.disposition.(index2) = 0;
		
	int res = sti(chr1.disposition.(index));
	
	if(CheckCharacterPerk(chr2, "Trustworthy"))
		res += 2;
	
	return res;
}

// evganat - определение пассажира-офицера
bool IsCharacterOfficer(ref chr)
{
	int charIdx;
	int n = GetPassengersQuantity(pchar);
	bool ok;
	for(int i=0; i<n; i++)
	{
		charIdx = GetPassenger(pchar, i);
		if(charIdx != -1 && chr.index == characters[charIdx].index)
		{
			if(CheckAttribute(chr, "capellan"))
				return true;
			ok = CheckAttribute(chr, "prisoned") && sti(chr.prisoned) == true;
			if (!ok && GetRemovable(chr))
				return true;
			return false;
		}
	}
	return false;
}

// забвение погибших
void DelRelations(ref chr)
{
	aref disposition;
	makearef(disposition, chr.disposition);
	int n = GetAttributesNum(disposition);
	int idx;
	
	for(int i=0; i < n; i++)
	{
		idx = sti(FindStringAfterChar(GetAttributeName(GetAttributeN(disposition, i)), "x"));
		DeleteAttribute(&characters[idx], "disposition.idx" + chr.index);
	}
	
	DeleteAttribute(chr, "disposition");
}

// > время жизни квестового фантома закончилось, можно что-нибудь записать в СЖ (если нужно) и т.д.
void CheckPhantomExpire(ref chr)
{
	if (CheckAttribute(chr, "id"))
	{
		switch (chr.id)
		{
			case "FriendLinney":
				if (CheckAttribute(pchar, "questTemp.piratesLine") && pchar.questTemp.piratesLine == "Soukins_toLaVegaSea")
					PQ7_FriendLinneyExpire();
			break;
		}
	}
}

// > конвертация жемчужниц в жемчуг предметный
// ref iSmall, iBig возвращает количество полученных жемчужин
void ConvertPinctadaToPearlItems(ref chr, ref iSmall, ref iBig)
{
    int pinctadaQty = GetSquadronGoods(chr, GOOD_PINCTADA);

    if (pinctadaQty <= 0)
        return;

    int totalPearlQty = pinctadaQty / 5;
    float SmallToBigPearlRel = 1.25 + frandSmall(1.0);

    int bigPearlQty = makeint(1.0 / SmallToBigPearlRel * totalPearlQty);
    int smallPearlQty = makeint(SmallToBigPearlRel * bigPearlQty);

    RemoveCharacterGoods(chr, GOOD_PINCTADA, pinctadaQty);

    iSmall = smallPearlQty;
    iBig = bigPearlQty;

    if (MOD_BETTATESTMODE == "On")
        Log_TestInfo("Обмен жемчужниц: pinctadaQty: " +pinctadaQty +" iSmall: " +iSmall +" iBig: " +iBig);
}

bool CharacterIsAlive(string id) 
{
	int idx = GetCharacterIndex(id);
	if (idx < 0) return false;

	return !CharacterIsDead(&characters[idx]);
}

bool CharacterIsHere(string id)
{
	int idx = GetCharacterIndex(id);
	if (idx < 0) return false;

	ref sld = &characters[idx];
	if (sld.location == pchar.location && !LAi_IsDead(sld))
	{
		return true;
	}

    return false;
}

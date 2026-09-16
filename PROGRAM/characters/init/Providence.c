
int CreateProvidenceCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////
	
	makeref(ch,Characters[n]);			//губернатор
	ch.id		= "Providencia_Mayor";
	ch.model	= "Edward_Colier";
	ch.name 	= FindPersonalName("Providencia_Mayor_name");
    ch.lastname = FindPersonalName("Providencia_Mayor_lastname");
	ch.rank     = 35;
	ch.sex 		= "man";
	ch.model.animation = "man";
	ch.City = "Providencia";
	ch.greeting = "mayor_4";
	ch.location = "Providencia_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Mayor\Colier.c";
	ch.greeting = "Gr_HeadPirates";
	ch.nation = PIRATE;
	ch.quest.type = "hovernor"; //?
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	EquipCharacterbyItem(ch, GUN_COMMON);
	EquipCharacterbyItem(ch, BLADE_LONG);
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.watchBoxes = true;
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.watchBoxes = true;
	ch.standUp = true;
	n = n + 1;

	makeref(ch,Characters[n]);		// ОФициантка
	ch.id		= "Providencia_waitress";
	ch.model	= "girl_7";
	ch.sex = "woman";
	ch.City = "Providencia";
	ch.location	= "Providencia_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Common_Waitress.c";
	ch.greeting = "Gr_officiant";
	ch.nation = PIRATE;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Трактирщик
	ch.id		= "Providencia_tavernkeeper";
	ch.model	= "barmen_23";
	ch.greeting = "Gr_Barmen";
	ch.name		= FindPersonalName("Providencia_tavernkeeper_name");
	ch.lastname = FindPersonalName("Providencia_tavernkeeper_lastname");
	ch.sex 		= "man";
	ch.City = "Providencia";
	ch.location	= "Providencia_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = PIRATE;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Торговец
	ch.id		= "Providencia_trader";
	ch.name		= FindPersonalName("Providencia_trader_name");
	ch.lastname = FindPersonalName("Providencia_trader_lastname");
	ch.model	= "trader_2";
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "Providencia";
	ch.location	= "Providencia_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = PIRATE;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	ch.Merchant = true;
    ch.money = makeint(STORE_TRADER_MIN_MONEY + frand(1.0)*STORE_TRADER_RAND_MONEY);
	n = n + 1;
	
	makeref(ch,Characters[n]);			//Хозяйка борделя
	ch.id		= "Providencia_Hostess";
	ch.name		= FindPersonalName("Providencia_Hostess_name");
	ch.lastname = FindPersonalName("Providencia_Hostess_lastname");
	ch.model	= "Maman_8";
	ch.model.animation = "woman_B";
	ch.sex = "woman";
	ch.City = "Providencia";
	ch.location	= "Providencia_SecBrRoom";
	ch.location.group = "goto";
	ch.location.locator = "goto7";
	ch.Dialog.Filename = "Common_Brothel.c";
	ch.greeting = "hostess";
	ch.nation = PIRATE;
	ch.questChurch = ""; //флаг для пожертвований
	ch.no_donation = true;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	n = n + 1;
	
	/*makeref(ch,Characters[n]);			//Священик
	ch.id		= "Providencia_Priest";
	ch.model	= "priest_2";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "Providencia";
	ch.location	= "Providencia_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Church.c";
	ch.greeting = "padre_2";
	ch.nation = PIRATE;
//	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;*/
	
	/*makeref(ch,Characters[n]);			//Корабел
	ch.id		= "Providencia_shipyarder";
	ch.model	= "shipowner_1";
	ch.greeting = "shipyarder_1";
	ch.sex = "man";
	ch.City = "Providencia";
	ch.location	= "Providencia_Shipyard";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = PIRATE;
	ch.quest.shiping = "0";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor_02");
	EquipCharacterbyItem(ch, GUN_COMMON);
	EquipCharacterbyItem(ch, "topor_02");
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.watchBoxes = true;
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(ch);
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;*/

	/*makeref(ch,Characters[n]);			//Банкир
	ch.id		= "Providencia_usurer";
	ch.model	= "banker_1";
	ch.sex = "man";
	ch.City = "Providencia";
	ch.Merchant.type = "jeweller";
	ch.location	= "Providencia_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Usurer.c";
	ch.nation = PIRATE;
	ch.greeting = "Gr_bankeer"; //ch.greeting = "usurer_5";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 10000; // *1000 денег
	//ch.money = USURER_MIN_MONEY + rand(USURER_NORM);
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.Merchant = true;
    ch.money = makeint(BANK_TRADER_MIN_MONEY + frand(1.0)*BANK_TRADER_RAND_MONEY);
	n = n + 1;*/

	makeref(ch,Characters[n]);			//Начальник порта
	ch.id		= "Providencia_PortMan";
	ch.model	= "citiz_2";
	ch.sex = "man";
	ch.City = "Providencia";
	ch.location	= "Providencia_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.nation = PIRATE;
	ch.greeting = "portman_2";
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	ch.storeShipsNum = 5; //атрибут для определения количества судов в доке отличным от значения по умолчанию (3)
	ch.dontGive = true; //если атрибут имеется, то исключает возможность отдать корабли в док
	n = n + 1;
	
	/*makeref(ch,Characters[n]); //Контрабандист
	ch.name 	= "Контрабандист";
	ch.lastname = "";
	ch.id		= "Providencia_Smuggler";
	ch.model    = "citiz_1";
	ch.sex      = "man";
	LAi_SetLoginTime(ch, 0.0, 24.0);
	ch.nation = PIRATE;
	GiveItem2Character(ch, BLADE_SABER);
	EquipCharacterbyItem(ch, BLADE_SABER);
	// посадим в генераторе
	ch.Dialog.Filename = "Smuggler_Agent_dialog.c";
	LAi_SetSitType(ch);
	LAi_SetHP(ch, 80.0, 80.0);
	ch.greeting = "smuggler";
	n = n + 1;*/
	
	return n;
}

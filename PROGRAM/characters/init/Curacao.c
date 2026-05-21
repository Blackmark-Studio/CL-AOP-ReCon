
int CreateCuracaoCharacters(int n)
{
	ref ch;
	
	///////////////////////////////////////////////////////////////////////////////
	// ОСНОВНЫЕ ПЕРСОНАЖИ
	///////////////////////////////////////////////////////////////////////////////

	makeref(ch,Characters[n]);			//Губернатор
	ch.id		= "Villemstad_Mayor";
	ch.model	= "huber_hol";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_townhall";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Mayor.c";
	ch.greeting = "hol_gov_common";
	ch.nation = HOLLAND;
	ch.quest.type = "hovernor";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, BLADE_LONG);
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.watchBoxes = true;
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetHuberType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Священик
	ch.id		= "Villemstad_Priest";
	ch.model	= "priest_4";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_church";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Church.c";
	ch.greeting = "Gr_Church";
	ch.nation = HOLLAND;
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetPriestType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);		// ОФициантка
	ch.id		= "Villemstad_waitress";
	ch.model	= "women_5";
	ch.name 	= FindPersonalName("Villemstad_waitress_name");
	ch.lastname = FindPersonalName("Villemstad_waitress_lastname");
	ch.sex = "woman";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_tavern";
	ch.location.group = "waitress";
	ch.location.locator = "barmen";
	ch.Dialog.Filename = "Common_Waitress.c";
	ch.greeting = "Gr_officiant";
	ch.nation = HOLLAND;
	LAi_SetWaitressType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Трактирщик
	ch.id		= "Villemstad_tavernkeeper";
	ch.model	= "barmen_4";
	ch.greeting = "Gr_Barmen";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_Tavern";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Tavern.c";
	ch.TavernMan = true;
	ch.nation = HOLLAND;
	LAi_SetBarmanType(ch);
	LAi_RemoveLoginTime(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Торговец
	ch.id		= "Villemstad_trader";
	ch.model	= "trader_4";
	ch.name 	= FindPersonalName("Villemstad_trader_name");
	ch.lastname = FindPersonalName("Villemstad_trader_lastname");
	ch.greeting = "tra_common";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_Store";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Store.c";
	ch.quest.type = "trader";
	ch.nation = HOLLAND;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	ch.Merchant = true;
    ch.money = makeint(STORE_TRADER_MIN_MONEY + frand(1.0)*STORE_TRADER_RAND_MONEY);
	n = n + 1;

	makeref(ch,Characters[n]);			//Корабел
	ch.id		= "Villemstad_shipyarder";
	ch.model	= "shipowner_4";
	ch.greeting = "Gr_shipyarder";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_Shipyard";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Shipyard.c";
	ch.nation = HOLLAND;
	ch.quest.shiping = "0";
	GiveItem2Character(ch, GUN_COMMON);
	GiveItem2Character(ch, "topor1");
	SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 60, 70);
	ch.watchBoxes = true;
	ch.standUp = true; //вставать и нападать на врага
	LAi_SetLoginTime(ch, 6.0, 21.99);
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Банкир
	ch.id		= "Villemstad_usurer";
	ch.name 	= FindPersonalName("Villemstad_usurer_name");
	ch.lastname = FindPersonalName("Villemstad_usurer_lastname");
	ch.model	= "usurer_4";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_Bank";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "Common_Usurer.c";
	ch.nation = HOLLAND;
	ch.greeting = "Gr_bankeer";
	ch.quest.shiping = "0";
	ch.UsurerDeposit = 11000; // *1000 денег
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
    ch.Merchant = true;
    ch.money = makeint(BANK_TRADER_MIN_MONEY + frand(1.0)*BANK_TRADER_RAND_MONEY);
	n = n + 1;

	makeref(ch,Characters[n]);			//Начальник порта
	ch.id		= "Villemstad_PortMan";
	ch.model	= "portman_6";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_PortOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "Common_Portman.c";
	ch.nation = HOLLAND;
	ch.greeting = "portmans";
	LAi_SetHuberType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.item_date = "";
	n = n + 1;
	
	makeref(ch,Characters[n]);			//Хозяйка борделя
	ch.id		= "Villemstad_Hostess";
	ch.name		= FindPersonalName("Villemstad_Hostess_name");
	ch.lastname = "";
	ch.model	= "Maman_1";
	ch.model.animation = "woman_B";
	ch.sex = "woman";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_SecBrRoom";
	ch.location.group = "goto";
	ch.location.locator = "goto8";
	ch.Dialog.Filename = "Common_Brothel.c";
	ch.greeting = "hostess";
	ch.nation = HOLLAND;
	ch.questChurch = ""; //флаг для пожертвований
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	n = n + 1;
	
	makeref(ch,Characters[n]);
	ch.name 	= UpperFirst(XI_ConvertString("WhoSmuggler"));
	ch.lastname = "";
	ch.id		= "Villemstad_Smuggler";
	ch.model    = "citiz_29";
	ch.sex      = "man";
	LAi_SetLoginTime(ch, 0.0, 24.0);
	ch.nation = PIRATE;
	GiveItem2Character(ch, BLADE_SABER);
	ch.equip.blade = BLADE_SABER;
	// посадим в генераторе
	ch.Dialog.Filename = "Smuggler_Agent_dialog.c";
	LAi_SetSitType(ch);
	LAi_SetHP(ch, 80.0, 80.0);
	ch.greeting = "Gr_Smuggler Agent";
	n = n + 1;
	
	makeref(ch,Characters[n]);			//Смотритель кладбища
	ch.id		= "Villemstad_Cemeteryman";
	ch.model	= "keeper_7";
	ch.model.animation = "man_B";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location = "Villemstad_KeepersHouse";
	ch.location.group = "goto";
	ch.location.locator = "goto5";
	ch.Dialog.Filename = "Common_Cemeteryman.c";
	ch.greeting = "lighthouseman_1";
	ch.Merchant = true;
	// ch.Merchant.type = "cemeteryman";
	ch.money = makeint(LIGHT_TRADER_MIN_MONEY + frand(1.0)*LIGHT_TRADER_RAND_MONEY);
	ch.nation = HOLLAND;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//главный клерк
	ch.id		= "HWIC_headclerk";
	ch.name 	= FindPersonalName("HWIC_headclerk_name");
	ch.lastname = FindPersonalName("HWIC_headclerk_lastname");
	ch.model	= "portman_7";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location = "GVIK";
	ch.location.group = "sit";
	ch.location.locator = "sit3";
	ch.Dialog.Filename = "HWIC_Office.c";
	ch.dialog.currentnode = "HWIC_headclerk";
	ch.greeting = "official";
	ch.nation = HOLLAND;
	ch.standUp = true;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	LAi_SetHuberType(ch);
	LAi_SetLoginTime(ch, 6.0, 21.99);
	SetFantomParamFromRank(ch, 20, true);
	n = n + 1;

	makeref(ch,Characters[n]);			//Заведущий пакгауза
	ch.id		= "Villemstad_GlavSklad";
	ch.model	= "citiz_17";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_PackhouseOffice";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "House_dialog.c";
	ch.dialog.currentnode = "GlavSklad";
	ch.nation = HOLLAND;
	ch.greeting = "official";
    ch.nonTable = true;
    ch.standUp = true;
    ch.watchBoxes = true;
	LAi_SetSitType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	ch.Storage = true;
	ch.item_date = "";
	n = n + 1;

	makeref(ch,Characters[n]);			//Заведающий хранилища
	ch.id		= "Villemstad_bankvault";
	ch.model	= "citiz_14";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location	= "Villemstad_bankvault";
	ch.location.group = "barmen";
	ch.location.locator = "stay";
	ch.Dialog.Filename = "House_dialog.c";
	ch.dialog.currentnode = "GlavBankVault";
	ch.nation = HOLLAND;
	ch.greeting = "official";
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
    ch.watchBoxes = true;
	ch.Storage = true;
	n = n + 1;
	
	makeref(ch,Characters[n]);			//глава ГВИК
	ch.id		= "HWIC_head";
	ch.name 	= FindPersonalName("HWIC_head_name");
	ch.lastname = FindPersonalName("HWIC_head_lastname");
	ch.model	= "huber_1";
	ch.model.animation = "man";
	ch.sex = "man";
	ch.City = "Villemstad";
	ch.location = "Villemstad_Residence_GVIK";
	ch.location.group = "sit";
	ch.location.locator = "sit1";
	ch.Dialog.Filename = "HWIC_head.c";
	ch.dialog.currentnode = "First time";
	ch.greeting = "official";
	ch.nation = HOLLAND;
	ch.standUp = true;
	LAi_SetOwnerType(ch);
	LAi_group_MoveCharacter(ch, "HOLLAND_CITIZENS");
	LAi_SetImmortal(ch, true);
	LAi_SetHuberType(ch);
	LAi_SetLoginTime(ch, 6.0, 21.99);
	SetFantomParamFromRank(ch, 20, true);
	n = n + 1;
	
	return n;
}

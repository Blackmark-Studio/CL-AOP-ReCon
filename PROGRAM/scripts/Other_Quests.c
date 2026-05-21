//=====================================================================================================================================
// Warship, Квест "Сопровождение флейта 'Орион'" -->
//=====================================================================================================================================
void Andre_Abel_Quest_CreateAbel(string sQuest)
{
	if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 5 || makeint(7 - GetCharacterShipClass(pchar)) < 1) //при низком лидерстве и на 7 класс не даем
	{
		pchar.quest.Andre_Abel_Quest_Start_1.win_condition.l1 = "ExitFromLocation";
		pchar.quest.Andre_Abel_Quest_Start_1.win_condition.l1.location = pchar.location;
		pchar.quest.Andre_Abel_Quest_Start_1.function = "Andre_Abel_Quest_CreateAbel_Again";
	}
	else
	{
		CreateAbel();
	}
}

void Andre_Abel_Quest_CreateAbel_Again(string sQuest)
{
	pchar.quest.Andre_Abel_Quest_Start.win_condition.l1 = "location";
	pchar.quest.Andre_Abel_Quest_Start.win_condition.l1.location = "FortFrance_tavern";
	pchar.quest.Andre_Abel_Quest_Start.function = "Andre_Abel_Quest_CreateAbel";
}

void CreateAbel()
{
	ref sld;
	PChar.QuestTemp.AndreAbelQuest = true;
	
	sld = GetCharacter(NPC_GenerateCharacter("Andre_Abel", "Andre_Abel", "man", "man", 10, FRANCE, -1, true));
	FantomMakeCoolFighter(sld, 10, 30, 35, "blade9", "pistol2", 10);
	FantomMakeCoolSailor(sld, SHIP_FLEUT, FindPersonalName("Andre_Abel_ship"), CANNON_TYPE_CANNON_LBS20, 30, 30, 30);
	sld.name = FindPersonalName("Andre_Abel_name");
	sld.lastname = FindPersonalName("Andre_Abel_lastname");
	sld.SaveItemsForDead = true; // сохранять на трупе вещи
	sld.DontClearDead = true; // не убирать труп через 200с
	sld.dialog.FileName = "Quest\Andre_Abel_Dialog.c";
	sld.greeting = "cit_quest";
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);	// До поры нельзя убить
	SetCharacterGoods(sld, GOOD_SILK, 700);
	SetCharacterGoods(sld, GOOD_TOBACCO, 500);

	AddLandQuestMark_Main(sld, "Andre_Abel_Quest");
    AddMapQuestMark_Major("FortFrance_town", "Andre_Abel_Quest", "");

	LAi_MethodDelay("MoveAbelToTavern", 1.0);
}

void MoveAbelToTavern()
{
	ref rChar = CharacterFromID("Andre_Abel");
	FreeSitLocator("FortFrance_tavern", "sit7");
	ChangeCharacterAddressGroup(rChar, "FortFrance_tavern", "sit", "sit7");
}

void Andre_Abel_Quest_1Day_Left(string sQuest)	// Провал квеста 
{
	ref rChar = CharacterFromID("Andre_Abel");
	rChar.LifeDay = 0;
	LAi_CharacterDisableDialog(rChar);
	ChangeCharacterAddressGroup(rChar, "none", "", "");
	AddQuestRecord("Andre_Abel_Quest", "2");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
}

void Andre_Abel_Quest_2Days_Left(string sQuest)	// Провал квеста - не решили свои дела за два дня
{
	ref rChar = CharacterFromID("Andre_Abel");
	rChar.LifeDay = 0;
	LAi_CharacterDisableDialog(rChar);
//	ChangeCharacterAddressGroup(rChar, "none", "", "");
	AddQuestRecord("Andre_Abel_Quest", "2");
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
}

void Andre_Abel_Quest_Delete_Andre_From_Tavern(string sQuest)	// Убираем Абеля из таверны
{
	ref rChar = CharacterFromID("Andre_Abel");
	ChangeCharacterAddressGroup(rChar, "none", "", "");
	// Присоединяем Андрэ Абеля к игроку в качестве компаньона
	SetCompanionIndex(Pchar, -1, GetCharacterIndex(rChar.id));
	SetCharacterRemovable(rChar, false);	// нельзя сменить
	LAi_SetImmortal(rChar, false);	// можно убить
//	rChar.Dialog.CurrentNode = "Andre_Abel_To_Sea_1";
}

void Andre_Abel_Quest_15_Days_Is_Left(string sQuest)	// Не успели в Порт-о-Принс за 15 дней
{
	ref rChar = CharacterFromID("Andre_Abel");
	rChar.LifeDay = 0;
	AddQuestRecord("Andre_Abel_Quest", "4");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
	RemoveCharacterCompanion(PChar, rChar);
	QuestSetCurrentNode("Andre_Abel", "Andre_Abel_15Days_Left_1");
	PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Delete_Andre_From_Tavern.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Battle_With_Pirates_Squadron.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Speak_In_PortPax.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Pirates_Is_Dead.over = "yes";
	PChar.Quest.Andre_Abel_Quest_EnterMap.over = "yes";
}

void Andre_Abel_Quest_Andre_Is_Dead(string sQuest)	// Андрэ Абеля потопили
{
	AddQuestRecord("Andre_Abel_Quest", "5");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","ла"));
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
	PChar.Quest.Andre_Abel_Quest_15_Days_Is_Left.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Speak_In_PortPax.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Battle_With_Pirates_Squadron.over = "yes";
}

void Andre_Abel_Quest_Battle_With_Pirates_Squadron(string sQuest)	// Выполнилось прерывание на Hispaniola2. Боевка с пиратами
{
	Log_TestInfo("Сгенерилась пиратская эскадра.");
	ref rChar;
	string sName, sLastName, sModel, sShipName;
	PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead.over = "yes";
	Group_FindOrCreateGroup("Andre_Abel_Quest_Pirates_Ships");
	TEV.Andre_Abel_Quest_Battle_With_Pirates_Squadron = "1";
	
	int shipsCount = Andre_Abel_Quest_GetPiratesSquadronShipCount();
	for(int i=1; i<=shipsCount; i++)
	{
		switch(i)
		{
			case 1:
				sName = FindPersonalName("Andre_Abel_Quest_Pirate_1_name");
				sLastName = FindPersonalName("Andre_Abel_Quest_Pirate_1_lastname");
				sModel = "citiz_53";	//watch_quest_moment
				sShipName = FindPersonalName("Andre_Abel_Quest_Pirate_1_ship");
				break;
				
			case 2:
				sName = FindPersonalName("Andre_Abel_Quest_Pirate_2_name");
				sLastName = FindPersonalName("Andre_Abel_Quest_Pirate_2_lastname");
				sModel = "citiz_57";	//watch_quest_moment
				sShipName = FindPersonalName("Andre_Abel_Quest_Pirate_2_ship");
				break;
				
			case 3:
				sName = FindPersonalName("Andre_Abel_Quest_Pirate_3_name");
				sLastName = FindPersonalName("Andre_Abel_Quest_Pirate_3_lastname");
				sModel = "officer_22";	//watch_quest_moment
				sShipName = FindPersonalName("Andre_Abel_Quest_Pirate_3_ship");
				break;
		}
		
		rChar = GetCharacter(NPC_GenerateCharacter("Andre_Abel_Quest_Pirate_" + i, sModel, "man", "man", 15, PIRATE, -1, true));
		FantomMakeCoolFighter(rChar, 35, 40, 35, "blade24", "pistol3", 10);
		FantomMakeCoolSailor(rChar, RandShipFromPcharSquadron(), sShipName, CANNON_TYPE_LBS_BY_SHIP, 50, 45, 40);
		rChar.name = sName;
		rChar.Lastname = sLastName;
		rChar.Abordage.Enable = true; //  Включено разрешение на абордаж пиратских кораблей. Konstrush
		Group_AddCharacter("Andre_Abel_Quest_Pirates_Ships", "Andre_Abel_Quest_Pirate_" + i);
	}
	
	DeleteAttribute(&TEV, "Andre_Abel_Quest_Battle_With_Pirates_Squadron");
	Group_SetType("Andre_Abel_Quest_Pirates_Ships", "war");
	Group_SetGroupCommander("Andre_Abel_Quest_Pirates_Ships", "Andre_Abel_Quest_Pirate_1");
	Group_SetTaskAttack("Andre_Abel_Quest_Pirates_Ships", PLAYER_GROUP);
	Group_LockTask("Andre_Abel_Quest_Pirates_Ships");
	Group_SetAddress("Andre_Abel_Quest_Pirates_Ships", "Hispaniola2", "", "");
	Group_SetPursuitGroup("Andre_Abel_Quest_Pirates_Ships", PLAYER_GROUP);
//	Island_SetReloadEnableGlobal("Hispaniola2", false); // На берег нельзя
	SetFunctionLocationCondition("Andre_Abel_Quest_Speak_In_PortPax", "PortPax_town", false);
	SetFunctionNPCDeathCondition("Andre_Abel_Quest_Andre_Is_Dead_2", "Andre_Abel", false);
	SetFunctionInterruptionToShips("Andre_Abel_Quest_Pirates_Ships", "Andre_Abel_Quest_Pirates_Is_Dead", "Andre_Abel_Quest_EnterMap");
}

int Andre_Abel_Quest_GetPiratesSquadronShipCount()
{
	if (MOD_SKILL_ENEMY_RATE < 5) return 1;
	if (MOD_SKILL_ENEMY_RATE < 9) return 2;
	
	return 3;
}

void Andre_Abel_Quest_Andre_Is_Dead_2(string sQuest) // Абеля потопили при боевке с пиратами
{
	AddQuestRecord("Andre_Abel_Quest", "6");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","ла"));
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
//	Island_SetReloadEnableGlobal("Hispaniola2", true);
	PChar.Quest.Andre_Abel_Quest_Speak_In_PortPax.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Pirates_Is_Dead.over = "yes";
	PChar.Quest.Andre_Abel_Quest_EnterMap.over = "yes";
}

void Andre_Abel_Quest_EnterMap(string sQuest)	// Свалили
{
	ref rChar = CharacterFromID("Andre_Abel");
	AddQuestRecord("Andre_Abel_Quest", "7");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
	Group_DeleteGroup("Andre_Abel_Quest_Pirates_Ships");
	RemoveCharacterCompanion(PChar, rChar);
//	Island_SetReloadEnableGlobal("Hispaniola2", true);
	PChar.Quest.Andre_Abel_Quest_Speak_In_PortPax.over = "yes";
	PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead_2.over = "yes";	// Не храним лишние прерывания
}

void Andre_Abel_Quest_Pirates_Is_Dead(string sQuest)	// Победили пиратскую эскадру
{
	AddQuestRecord("Andre_Abel_Quest", "8");
	SetFunctionNPCDeathCondition("Andre_Abel_Quest_Andre_Is_Dead_3", "Andre_Abel", false);
//	SetFunctionLocationCondition("Andre_Abel_Quest_Speak_In_PortPax", "PortPax_town", false);
//	Island_SetReloadEnableGlobal("Hispaniola2", true);
	PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead_2.over = "yes";
}

void Andre_Abel_Quest_Andre_Is_Dead_3(string sQuest)	// Абеля утопил кто-то в порту
{
	AddQuestRecord("Andre_Abel_Quest", "5");
	CloseQuestHeader("Andre_Abel_Quest");
	DeleteAttribute(pchar,"QuestTemp.AndreAbelQuest");
	PChar.Quest.Andre_Abel_Quest_Speak_In_PortPax.over = "yes";
}

void Andre_Abel_Quest_Speak_In_PortPax(string sQuest)	// Разговор с Абелем в порту Порт-о-Принса
{
	ref rChar = CharacterFromID("Andre_Abel");
	RemoveCharacterCompanion(PChar, rChar);
	rChar.Dialog.CurrentNode = "Andre_Abel_In_PortPax";
	LAi_LocationDisableOfficersGen("PortPax_town", true);
	LAi_SetImmortal(rChar, true);
	ChangeCharacterAddressGroup(rChar, "PortPax_town", "quest", "quest1");
	LAi_SetActorType(rChar);
	LAi_SetActorType(PChar);
    SetActorDialogAny2Pchar("Andre_Abel", "", -1, 0.0);
	LAi_ActorFollow(PChar, rChar, "ActorDialog_Any2Pchar", -1);
	LAi_ActorFollow(rChar, PChar, "ActorDialog_Any2Pchar", -1);
	bDisableFastReload = true;
	chrDisableReloadToLocation = true;
	PChar.Quest.Andre_Abel_Quest_Andre_Is_Dead_3.over = "yes";
}

void Andre_Abel_Quest_Dialog_In_PortPax_Tavern()	// В таверне...
{
	ref rChar = CharacterFromID("Andre_Abel");
	LAi_ActorDialogNow(rChar, PChar, "", -1);
}

void Andre_Abel_Quest_After_First_Jackman_Dialog()	// Джекмен выставил игрока из своей резиденции
{
	AddQuestRecord("Andre_Abel_Quest", "11");
	//QuestSetCurrentNode("Henry Morgan", "Andre_Abel_Quest_Morgan_Dialog_1");
	pchar.QuestTemp.AndreAbelQuest = "GoTo_Morgan1";

	AddLandQuestMark_Main(CharacterFromId("Henry Morgan"), "Andre_Abel_Quest");
}

void Andre_Abel_Quest_Curasao_10Days_Left(string sQuest)	// Не успели к Стэвезанту за 10 дней
{
	AddQuestRecord("Andre_Abel_Quest", "15");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("","а"));
	TakeItemFromCharacter(PChar, "Andre_Abel_Letter_1");
	ChangeCharacterAddressGroup(CharacterFromID("Andre_Abel"), "none", "", "");
	ref rChar = CharacterFromID("hol_guber");
	rChar.Dialog.CurrentNode = rChar.Dialog.TempNode; // Вернём ноду диалога Ген-Губеру
    RemoveLandQuestMark_Main(rChar, "Andre_Abel_Quest");

	PChar.QuestTemp.Andre_Abel_Quest_PortPax_TavernOwner_Speek = true;
    AddLandQuestMark_Main(CharacterFromID("PortPax_tavernkeeper"), "Andre_Abel_Quest");

	if(!CheckAttribute(PChar, "Quest.Andre_Abel_Quest_In_Curacao_Townhall"))
	{
		rChar = CharacterFromID("Andre_Abel_Quest_Guard_1");
		rChar.LifeDay = 0;
	}

	PChar.Quest.Andre_Abel_Quest_In_Curacao_Townhall.over = "yes";
}

void Andre_Abel_Quest_In_Curacao_Townhall(string sQuest)	// Зашли в резиденцию Виллемстеда
{
	ref rChar = GetCharacter(NPC_GenerateCharacter("Andre_Abel_Quest_Guard_1", "guard_hol_3", "man", "man", 20, HOLLAND, -1, true)); //watch_quest_moment 
	FantomMakeCoolFighter(rChar, 15, 60, 65, "blade24", "pistol3", 100);
	rChar.Dialog.FileName = "Quest\Other_Quests_NPC.c";
	rChar.greeting = "soldier_common";
	LAi_SetGuardianType(rChar);
	LAi_SetImmortal(rChar, true);
	ChangeCharacterAddressGroup(rChar, "Villemstad_Townhall2", "goto", "goto6");
	string slai_group = "HOLLAND_citizens";
	LAi_group_MoveCharacter(rChar, slai_group);
}

void Andre_Abel_Quest_Curacao_Townhall_Clear(string sQuest)	// очистка резиденции Виллемстеда
{
	ref rChar;
	
	rChar = CharacterFromID("hol_guber");
	rChar.Dialog.CurrentNode = rChar.Dialog.TempNode; // Вернём ноду диалога Ген-Губеру
	
	int chIndex = GetCharacterIndex("Andre_Abel_Quest_Guard_1");
	if (chIndex != -1)
	{
		rChar = &Characters[chIndex];
		rChar.LifeDay = 0; // Убираем гвардейца из резиденции
	}
}

void Andre_Abel_Quest_In_Prison()	// В тюрьме...
{
	AddQuestRecord("Andre_Abel_Quest", "17");
	ref rChar = GetCharacter(NPC_GenerateCharacter("Martin_Bleker", "Blacker_jail", "man", "man", 10, PIRATE, -1, true));
	rChar.rank = 18;
	LAi_SetHP(rChar, 200, 200);
	SetSPECIAL(rChar, 8, 6, 9, 4, 5, 8, 7);
	SetSelfSkill(rChar, 60, 60, 60, 60, 40);
	SetShipSkill(rChar, 55, 10, 45, 50, 60, 50, 50, 50, 40);
	SetCharacterPerk(rChar, "BasicDefense");
	SetCharacterPerk(rChar, "AdvancedDefense");
	SetCharacterPerk(rChar, "CriticalHit");
	SetCharacterPerk(rChar, "Sliding");
	SetCharacterPerk(rChar, "ByWorker");
	SetCharacterPerk(rChar, "Tireless");
	SetCharacterPerk(rChar, "Gunman");
	SetCharacterPerk(rChar, "IronWill");
	SetCharacterPerk(rChar, "ShipEscape");
	SetCharacterPerk(rChar, "LongRangeGrappling");
	SetCharacterPerk(rChar, "GrapplingProfessional");
	SetCharacterPerk(rChar, "HullDamageUp");
	SetCharacterPerk(rChar, "CrewDamageUp");
	SetCharacterPerk(rChar, "AdvancedBattleState");
	SetCharacterPerk(rChar, "BasicBattleState");
	SetCharacterPerk(rChar, "ShipSpeedUp");
	SetCharacterPerk(rChar, "ShipTurnRateUp");
	SetCharacterPerk(rChar, "Doctor1");
	//черты
	SetCharacterPerk(rChar, "Energaiser");
	SetCharacterPerk(rChar, "LoyalOff");
	SetCharacterPerk(rChar, "Rebel"); //TODO: надо ли ему?
	
	ChangeCharacterAddressGroup(rChar, "Villemstad_prison", "goto", "goto24");
	rChar.Dialog.Filename = "Quest\Other_Quests_NPC.c";
	rChar.greeting = "pirat_quest";
	rChar.name = FindPersonalName("Martin_Bleker_name");
	rChar.Lastname = FindPersonalName("Martin_Bleker_lastname");
	LAi_SetStayType(rChar);
	RemoveAllCharacterItems(rChar, true);
	LAi_SetRolyPoly(rChar, true); //неваляха
	rChar = CharacterFromID("Andre_Abel_Quest_Guard_1");
	rChar.LifeDay = 0;
	ChangeCharacterAddressGroup(rChar, "none", "", ""); // Убираем гвардейца из резиденции
	
	PChar.QuestTemp.JailCanMove = false; // Если было - уберем
	PChar.QuestTemp.Andre_Abel_Quest_In_Prison = true;

	// Запоминаем тип экипированного оружия
	Andre_Abel_Quest_RememberBladeFencingType();
	
	ref location = &Locations[FindLocation("Villemstad_prison")];	
	
	// Перекладываем предметы ГГ в сундук 
	aref arItems, boxItems;
	ref rItem;
	string sName;
	makearef(arItems, PChar.items);
	makearef(boxItems, location.box1.items);
	int iItemsNum = GetAttributesNum(arItems);
	for(int i=0; i<iItemsNum; i++)
	{
		sName = GetAttributeName(GetAttributeN(arItems, i));
		rItem = ItemsFromID(sName);
		if (rItem.ItemType != "QUESTITEMS")
		{
			boxItems.(sName) = PChar.items.(sName);
		}
	}
	location.box1.money = PChar.money;	
	location.box1 = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
		
	RemoveAllCharacterItems(PChar, true);	
}

void Andre_Abel_Quest_Runaway_From_Prison()	// По другую сторону решетки
{
	chrDisableReloadToLocation = true;
	
	ref rChar = CharacterFromID("Martin_Bleker");
	AddQuestRecord("Andre_Abel_Quest", "18");
	LAi_SetOfficerType(rChar);

	LAi_Group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
	//HardCoffee рефакторинг диалогов с Морганом
	//QuestSetCurrentNode("Henry Morgan", "Andre_Abel_Quest_Morgan_Dialog_11");
	pchar.QuestTemp.AndreAbelQuest = "GoTo_MorganPrison";
	AddLandQuestMark_Main(CharacterFromId("Henry Morgan"), "Andre_Abel_Quest");
	
	rChar = CharacterFromID("VillemstadJailOff");
	LAi_Group_Attack(PChar, rChar);	// Как будто мы его ударили
	LAi_group_SetCheck(rChar.chr_ai.group, "OpenTheDoors");
	Flag_PIRATE();
	
	PChar.Quest.Andre_Abel_Quest_In_Sea_After_Prison.win_condition.l1 = "EnterToSea";
	PChar.Quest.Andre_Abel_Quest_In_Sea_After_Prison.function = "Andre_Abel_Quest_In_Sea_After_Prison";
	
	int n = FindLocation("Villemstad_prison");
	Locations[n].reload.l1.go = "Villemstad_ExitTown";
	Locations[n].reload.l1.emerge = "reload4";
}

void Andre_Abel_Quest_RememberBladeFencingType()
{
	PChar.QuestTemp.Andre_Abel_Quest_In_Prison.FencingType = SKILL_FENCING;
	
	string sBlade = GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE);
	if (sBlade != "") 
	{
		ref rItm = ItemsFromID(sBlade);
		if (CheckAttribute(rItm, "FencingType"))
			PChar.QuestTemp.Andre_Abel_Quest_In_Prison.FencingType = rItm.FencingType;
	}
}

string Andre_Abel_Quest_GetBladeId_ByFencingType()
{
	if (CheckAttribute(PChar, "QuestTemp.Andre_Abel_Quest_In_Prison.FencingType"))
	{
		switch(PChar.QuestTemp.Andre_Abel_Quest_In_Prison.FencingType)
		{
			case "FencingLight": // Лёгкое оружие
				return "blade9"; // "Сайдсворд"
			break;
			
			case "Fencing": // Среднее оружие
				return "blade7"; // "Бильбо"
			break;
			
			case "FencingHeavy": // Тяжёлое оружие
				return "blade8"; // "Госсемесер"
			break;
		}
	}

	return "blade7";
}

void Andre_Abel_Quest_Martin_Bleker_Is_Dead(string sQuest)	// Мартина убили
{
	Log_TestInfo("Мартина убили");
	PChar.Quest.Andre_Abel_Quest_Liberty.over = "yes";
}

void Andre_Abel_Quest_Liberty(string sQuest)	// Локация выхода из Виллемстада
{
	ref rChar = CharacterFromID("Martin_Bleker");
	ChangeCharacterAddressGroup(rChar, "Villemstad_ExitTown", "goto", "goto2");
	DeleteAttribute(PChar, "QuestTemp.Andre_Abel_Quest_In_Prison");
	QuestSetCurrentNode("Martin_Bleker", "Andre_Abel_Quest_In_Liberty_1");
	LAi_SetActorType(rChar);
	LAi_SetActorType(PChar);
    SetActorDialogAny2Pchar("Martin_Bleker", "", -1, 0.0);
	LAi_ActorFollow(PChar, rChar, "ActorDialog_Any2Pchar", -1);
	LAi_ActorFollow(rChar, PChar, "ActorDialog_Any2Pchar", -1);
	PChar.Quest.Andre_Abel_Quest_Martin_Bleker_Is_Dead.over = "yes";
}

void Andre_Abel_Quest_Delete_Martin(string sQuest)	// Попрощались с Мартином
{
	for(int i = 1; i < 4; i++)
	{
		if(GetCharacterIndex("Martin_Bleker") == GetOfficersIndex(pchar, i)) return;
	}
	ref rChar = CharacterFromID("Martin_Bleker");
	ChangeCharacterAddressGroup(rChar, "none", "", "");
}

void MartinRecovery(string sQuest) // Мартин поправился
{
	ref rChar = CharacterFromID("Martin_Bleker");
	rChar.model = "Blacker_Martin";
}

void Andre_Abel_Quest_In_Sea_After_Prison(string sQuest)	// Вышли в море
{
	AddQuestRecord("Andre_Abel_Quest", "20");
	AddQuestUserData("Andre_Abel_Quest", "sSex", GetSexPhrase("ся","ась"));
}
//=====================================================================================================================================
// <-- Warship, Квест "Сопровождение флейта 'Орион'"
//=====================================================================================================================================

//=====================================================================================================================================
// Jason, 26.05.11. Серия миниквестов "Дело чести" -->
//=====================================================================================================================================
// Функция вернет строковый идентификатор квеста из дел чести, который выполняется в данный момент
string AffairOfHonor_GetCurQuest()
{
	// "Навязчивый кавалер"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Cavalier.Started"))
	{
		return "Cavalier";
	}
	
	// "Невольник чести"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.HonorSlave.Started"))
	{
		return "HonorSlave";
	}
	
	// "Красотка и пират"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.BeautifulPirate.Started"))
	{
		return "BeautifulPirate";
	}
	
	// "Заносчивый нахал"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.Jackanapes.Started"))
	{
		return "Jackanapes";
	}
	
	// "Волки и овцы"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.WolvesAndSheeps.Started"))
	{
		return "WolvesAndSheeps";
	}
	
	// "Трусливый фехтовальщик"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.Started"))
	{
		return "CowardFencer";
	}
	
	// "Честь мундира"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CoatHonor.Started"))
	{
		return "CoatHonor";
	}
	
	// "Божий суд"
	if(CheckAttribute(PChar, "QuestTemp.AffairOfHonor.GodJudgement.Started"))
	{
		return "GodJudgement";
	}
	
	return "";
}

// Jason: отсрочка на два часа, раз уж в диалоге договорились
void AffairOfHonor_LighthouseGotoMeeting(string _quest)
{
	SetFunctionLocationCondition("AffairOfHonor_LighthouseLocEnter", PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
}

// Функция, вызываемая при заходе в локацию маяка, где должна происходить дуэль
void AffairOfHonor_LighthouseLocEnter(string _quest)
{
	string modelFirst, modelSecond;
	int iRand1 = rand(1);
	int iRand2 = rand(1);
	
	ref sld = &Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)];
	DeleteAttribute(sld, "DisableEncounters");
	LAi_LocationFightDisable(sld, true); // Пока-что низя рубиццо
	
	sld = CharacterFromID("AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man");
	
	switch(AffairOfHonor_GetCurQuest()) //watch_quest_moment
	{
		case "Cavalier":
			modelFirst  = "urban_" + NationShortName(sti(sld.nation)) + "_" + (rand(7)+1);
			modelSecond = "urban_" + NationShortName(sti(sld.nation)) + "_" + (rand(7)+1);
		break;
		
		case "HonorSlave":
			modelFirst  = "citiz_" + (iRand1*(rand(2) + 42) + (1-iRand1)*(rand(2) + 48));
			modelSecond = "citiz_" + (iRand2*(rand(2) + 42) + (1-iRand2)*(rand(2) + 48));
		break;
		
		case "BeautifulPirate":
			modelFirst  = "pirate_" + (rand(15) + 1);
			modelSecond = "pirate_" + (rand(15) + 1);
		break;
		
		case "Jackanapes":
			modelFirst  = "citiz_" + (rand(9) + 41);
			modelSecond = "citiz_" + (rand(9) + 41);
		break;
		
		case "WolvesAndSheeps":
			modelFirst  = "citiz_" + (iRand1*(rand(9) + 1) + (1-iRand1)*(rand(9) + 11));
			modelSecond = "citiz_" + (iRand2*(rand(9) + 1) + (1-iRand2)*(rand(9) + 11));
		break;
		
		case "CowardFencer":
			modelFirst  = "pirate_" + (rand(4) + 12);
			modelSecond = "pirate_" + (rand(4) + 12);
		break;
		
		case "CoatHonor":
			modelFirst  = "urban_" + NationShortName(sti(sld.nation)) + "_" + (rand(7)+1);
			modelSecond = "urban_" + NationShortName(sti(sld.nation)) + "_" + (rand(7)+1);
		break;
		
		case "GodJudgement":
			modelFirst  = "citiz_" + (rand(9) + 21);
			modelSecond = "citiz_" + (rand(9) + 21);
		break;
	}
	
	ChangeCharacterAddressGroup(sld, PChar.QuestTemp.AffairOfHonor.LighthouseId, "goto", "goto20");
	LAi_SetGuardianType(sld);
	sld.protector = true; // Начать диалог
	sld.Dialog.CurrentNode = "AffairOfHonor_BeforeFight_1";
	LAi_SetImmortal(sld, false);
	LAi_CharacterEnableDialog(sld);
	
	int Rank = sti(pchar.rank)+MOD_SKILL_ENEMY_RATE+5;
	sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Helper_1", modelFirst, "man", "man", Rank, sti(sld.nation), -1, true));
	SetFantomParamFromRank(sld, Rank, true);
	ChangeCharacterAddressGroup(sld, PChar.QuestTemp.AffairOfHonor.LighthouseId, "goto", "goto22");
	LAi_SetActorType(sld);
	LAi_ActorTurnToLocator(sld, "goto", "goto19");
	LAi_SetImmortal(sld, true);
	
	sld = GetCharacter(NPC_GenerateCharacter("AffairOfHonor_Helper_2", modelSecond, "man", "man", sti(PChar.rank) + rand(5), sti(sld.nation), -1, true));
	SetFantomParamFromRank(sld, sti(PChar.rank) + rand(5), true);
	ChangeCharacterAddressGroup(sld, PChar.QuestTemp.AffairOfHonor.LighthouseId, "goto", "goto23");
	LAi_SetActorType(sld);
	LAi_ActorTurnToCharacter(sld, PChar);
	LAi_SetImmortal(sld, true);
	
	DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
	DeleteQuestCondition("AffairOfHonor_TimeIsLeft2");
	
	DisableAllExits(true);
	
	Log_Info(StringFromKey("InfoMessages_115"));
}

// Функция, вызываемая по истечении двух часов с момента взятия квеста
void AffairOfHonor_TimeIsLeft(string _quest)
{
	int charIndex;
	
	DeleteAttribute(&Locations[FindLocation(PChar.QuestTemp.AffairOfHonor.LighthouseId)], "DisableEncounters");
	LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
	DeleteQuestCondition("AffairOfHonor_LighthouseLocEnter");
	
	charIndex = GetCharacterIndex("AffairOfHonor_" + AffairOfHonor_GetCurQuest() + "_Man");
	if (AffairOfHonor_GetCurQuest() == "CoatHonor") PChar.quest.CoatHonor.over = "yes";
	
	// Вариант истечения времени при живом противнике
	if(charIndex != -1)
	{
		ChangeCharacterAddressGroup(GetCharacter(charIndex), "none", "", "");
		ref sld = CharacterFromId("AffairOfHonor_QuestMan");
		
		switch(AffairOfHonor_GetCurQuest())
		{
			case "Cavalier":
				LAi_CharacterEnableDialog(sld);
				
				AddQuestRecord("AffairOfHonor", "2_1");
				AddQuestUserData("AffairOfHonor", "sSex", GetSexPhrase("","а"));
				AddQuestUserData("AffairOfHonor", "sSex2", GetSexPhrase(StringFromKey("SexPhrase_27"),StringFromKey("SexPhrase_28")));
				sld.Dialog.CurrentNode = "AffairOfHonor_Cavalier_6";
				// ChangeCharacterAddressGroup(sld, sld.City + "_church", "quest", "quest3");
			break;
			
			case "HonorSlave":
				LAi_CharacterEnableDialog(sld);
				
				AddQuestRecord("AffairOfHonor", "4_1");
				AddQuestUserData("AffairOfHonor", "sSex", GetSexPhrase("ёл","ла"));
				sld.Dialog.CurrentNode = "AffairOfHonor_HonorSlave_9";
			break;
			
			case "BeautifulPirate":
				ChangeCharacterAddressGroup(sld, "none", "", "");
				
				AddQuestRecord("AffairOfHonor", "6_1");
				AddQuestUserData("AffairOfHonor", "sSex", GetSexPhrase("","а"));
			break;
			
			case "Jackanapes":
				LAi_CharacterEnableDialog(sld);
				
				AddQuestRecord("AffairOfHonor", "8_1");
				AddQuestUserData("AffairOfHonor", "sSex", GetSexPhrase("","а"));
				sld.Dialog.CurrentNode = "AffairOfHonor_Jackanapes_2";
			break;
			
			case "WolvesAndSheeps":
				ChangeCharacterAddressGroup(sld, "none", "", "");
				
				AddQuestRecord("AffairOfHonor", "10_1");
			break;
			
			case "CowardFencer":
				LAi_CharacterEnableDialog(sld);
				
				AddQuestRecord("AffairOfHonor", "12_1");
				AddQuestUserData("AffairOfHonor", "sSex", GetSexPhrase("","а"));
				sld.Dialog.CurrentNode = "AffairOfHonor_CowardFencer_4_1";
			break;
			
			case "CoatHonor":
				ChangeCharacterAddressGroup(sld, "none", "", "");
				
				AddQuestRecord("AffairOfHonor", "14_1");
				AddQuestUserData("AffairOfHonor", "sSex", GetSexPhrase("","а"));
			break;
			
			case "GodJudgement":
				ChangeCharacterAddressGroup(sld, "none", "", "");
				
				AddQuestRecord("AffairOfHonor", "16_1");
			break;
		}
	}
	
	DeleteAttribute(PChar, "QuestTemp.AffairOfHonor." + AffairOfHonor_GetCurQuest() + ".Started");
	
	CloseQuestHeader("AffairOfHonor");
	
	Log_TestInfo("Дело чести: время вышло");
}

// Тоже, что и выше. Нужно было просто другое название, чтобы параллельно они могли работать (разное время стоит)
void AffairOfHonor_TimeIsLeft2(string _quest)
{
	// В чем фича:
	// Если делать как
	//
	// DeleteQuestCondition("AffairOfHonor_TimeIsLeft");
	// SetFunctionTimerConditionParam("AffairOfHonor_TimeIsLeft", 0, 0, 0, 3, false);
	//
	// В один момент времени, то выйдет так, что прошлому квесту "AffairOfHonor_TimeIsLeft" присвоится ветка "завершен", но он не удалится,
	// а затем на его место станет новый квест "AffairOfHonor_TimeIsLeft", который автоматом будет с пометкой "завершен". Поэтому вот так сделано.
	
	AffairOfHonor_TimeIsLeft(_quest);
}

// Функция, вызываемая при убийстве персонажа, с которым дуэлимся
void AffairOfHonor_KillChar(string _quest)
{
	switch(AffairOfHonor_GetCurQuest())
	{
		case "Cavalier":
			AddQuestRecord("AffairOfHonor", "2");
		break;
		
		case "HonorSlave":
			AddQuestRecord("AffairOfHonor", "4");
		break;
		
		case "BeautifulPirate":
			AddQuestRecord("AffairOfHonor", "6");
		break;
		
		case "Jackanapes":
			AddQuestRecord("AffairOfHonor", "8");
		break;
		
		case "WolvesAndSheeps":
			AddQuestRecord("AffairOfHonor", "10");
		break;
		
		case "CowardFencer":
			AddQuestRecord("AffairOfHonor", "12");
			PChar.QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk = true;
		break;
		
		case "CoatHonor":
			AddQuestRecord("AffairOfHonor", "14");
		break;
		
		case "GodJudgement":
			AddQuestRecord("AffairOfHonor", "16");
			AddQuestUserData("AffairOfHonor", "sSex", GetSexPhrase("","а"));
		break;
	}
	
	CloseQuestHeader("AffairOfHonor");
	
	SetFunctionTimerCondition("AffairOfHonor_DayAfterDuel", 0, 0, 1, false);
	
	ref sld = CharacterFromID("AffairOfHonor_Helper_1");
	sld.Dialog.filename = "Quest\ForAll_dialog.c";
	sld.Dialog.CurrentNode = "AffairOfHonor_AfterFight_1";
	LAi_ActorDialog(sld, PChar, "", -1, 5);
	
	int FinishCount = sti(PChar.QuestTemp.AffairOfHonor.FinishCount) + 1;
	PChar.QuestTemp.AffairOfHonor.FinishCount = FinishCount;
	if(FinishCount == 5) SetCharacterPerk(pchar, "Duelist");
	
	DisableAllExits(false);
	
	SetFunctionExitFromLocationCondition("AffairOfHonor_LocExitAfterFight", PChar.location, false);
}

// Функция, вызываемая по истечении одного дня с момента дуэли
void AffairOfHonor_DayAfterDuel(string quest)
{
	DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
}

// Функция, вызываемая при выходе из локации после дуэли
void AffairOfHonor_LocExitAfterFight(string _quest)
{
	ref sld = CharacterFromId("AffairOfHonor_QuestMan");
	LAi_SetFightMode(PChar, false);
	
	DeleteAttribute(sld, "CityType");
	
	if(!CheckAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers"))
	{
		ChangeCharacterAddressGroup(CharacterFromID("AffairOfHonor_Helper_1"), "none", "", "");
		ChangeCharacterAddressGroup(CharacterFromID("AffairOfHonor_Helper_2"), "none", "", "");
	}
	
	switch(AffairOfHonor_GetCurQuest())
	{
		case "Cavalier":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_Cavalier_5";
			// ChangeCharacterAddressGroup(sld, sld.City + "_church", "quest", "quest3");
		break;
		
		case "HonorSlave":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_HonorSlave_7";
		break;
		
		case "WolvesAndSheeps":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_WolvesAndSheeps_12";
			// ChangeCharacterAddressGroup(sld, sld.City + "_church", "quest", "quest3");
		break;
		
		case "CowardFencer":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_CowardFencer_5";
			// ChangeCharacterAddressGroup(sld, sld.City + "_church", "quest", "quest3");
		break;
		
		case "GodJudgement":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_GodJudgement_2";
			// ChangeCharacterAddressGroup(sld, sld.City + "_church", "quest", "quest3");
		break;
		
		case "CoatHonor":
			sld.Dialog.CurrentNode = "AffairOfHonor_CoatHonor_Final";
		break;
		
		case "BeautifulPirate":
			LAi_CharacterEnableDialog(sld);
			sld.Dialog.CurrentNode = "AffairOfHonor_BeautifulPirate_5";
		break;
		
		case "Jackanapes":
			AddCrewMorale(pchar, 2);
			ChangeOfficersLoyality("good_all", 1);
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
		break;
	}
	LAi_LocationDisableOfficersGen(PChar.QuestTemp.AffairOfHonor.LighthouseId, false);
	DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.FightWithHelpers");
	DeleteAttribute(PChar, "QuestTemp.AffairOfHonor." + AffairOfHonor_GetCurQuest() + ".Started");
}

// Функция, вызываемая при выходе из интерфекса карт, когда играем с челом по квесту "волки и овцы"
void AffairOfHonor_AfterCards(string _quest)
{
	ref sld = characterFromID("AffairOfHonor_WolvesAndSheeps_Man");
	
	LAi_SetSitType(PChar);
	LAi_SetActorType(sld);
	LAi_ActorSetSitMode(sld);
	LAi_ActorDialogNow(sld, PChar, "", -1);
}

// Rosarak. Для рандомной выдачи (только мужики на улице)
int GetHonorQuestNum()
{
	string sTemp = "QuestTemp.AffairOfHonor.";
	int branches[6];
	int iRand = rand(5);
	
	branches[0] = CheckAttribute(pchar, sTemp + "HonorSlave");
	branches[1] = CheckAttribute(pchar, sTemp + "BeautifulPirate");
	branches[2] = CheckAttribute(pchar, sTemp + "Jackanapes");
	branches[3] = CheckAttribute(pchar, sTemp + "WolvesAndSheeps");
	branches[4] = CheckAttribute(pchar, sTemp + "CowardFencer");
	branches[5] = CheckAttribute(pchar, sTemp + "GodJudgement");
	
	while(branches[iRand] == 1) iRand = rand(5);
	
	return iRand;
}

// Rosarak. Чтобы не выдавало баговетку в диалогах
int NumManAffairQuests()
{
	string sTemp = "QuestTemp.AffairOfHonor.";
	return CheckAttribute(pchar, sTemp + "HonorSlave") + CheckAttribute(pchar, sTemp + "BeautifulPirate") + CheckAttribute(pchar, sTemp + "Jackanapes") + CheckAttribute(pchar, sTemp + "WolvesAndSheeps") + CheckAttribute(pchar, sTemp + "CowardFencer") + CheckAttribute(pchar, sTemp + "GodJudgement");
}

//=====================================================================================================================================
// <-- Серия миниквестов "Дело чести".
//=====================================================================================================================================

//=====================================================================================================================================
// Квест летучего голландца -->
//=====================================================================================================================================
ref SetFantomSkeletForts(string group, string locator, string enemygroup, string _type)
// _type = "GhostShipCrew"   _type = "ParamHunter"  _type = "none"
{
    string emodel;
    ref    Cr;

    emodel = GetRandSkelModel();

    Cr = LAi_CreateFantomCharacterEx(emodel, "man", group, locator);

    if (Cr.location.locator != "")
    {
		if (_type == "GhostShipCrew" || _type == "ParamHunter")
		{
			SetFantomParamHunter(Cr);
		}
		else
		{
		    SetFantomParam(Cr);
		}
		LAi_SetWarriorType(Cr);
	    LAi_group_MoveCharacter(Cr, enemygroup);
	    LAi_NoRebirthEnable(Cr); //не показывать убитых при входе в локацию
	    LAi_LoginInCaptureTown(Cr, true); // для записи игры
	    if (_type == "GhostShipCrew")
	    {
		    // возможно даёт вылеты от многих трупов Cr.DontClearDead = true;
		    Cr.GhostShipCrew = true;
	    }
    }
    return Cr;
}

// летучий голландец
void  GhostShipOnMap()
{
    ref  sld;
    int  i;
    ref  rRealShip;

    sld = characterFromID("GhostCapt");
    // пушки чинятся в SetBaseShipData DeleteAttribute(sld, "ship.cannons");

    SetBaseShipData(sld);
    rRealShip = GetRealShip(sti(sld.Ship.Type));
    rRealShip.ShipSails.SailsColor = argb(255, 60, 60, 60);  // 1.2.3 переделка цвета паруса от НПС

    ShipOverhaul(sld);

    Ship_SetTaskNone(SECONDARY_TASK, sti(sld.index));

    if (CheckAttribute(pchar , "GenQuest.GhostShip.LastBattle"))
    {
		sld.Ship.Type = GenerateShipExt(SHIP_FLYINGDUTCHMAN, true, sld);
		rRealShip = GetRealShip(sti(sld.Ship.Type));
		rRealShip.EmblemedSails.normalTex = "ships\parus_common_torn.tga";

        SetBaseShipData(sld);
        DeleteAttribute(rRealShip, "ShipSails.SailsColor");  // белый парус

        sld.ship.Cannons.Type = CANNON_TYPE_CULVERINE_LBS32;

        Character_SetAbordageEnable(sld, true);
    }
    else
    {
        sld.ship.hp = 52000; // 13%
    }

    SetCrewQuantityOverMax(sld, 666);
    sld.mapEnc.type = "war";
    sld.mapEnc.Name = FindPersonalName("GhostCapt_mapEnc");
	// sld.mapEnc.worldMapShip = "Flying_Dutchman";
	sld.mapEnc.worldMapShip = "FlyingDutchmanShip";

    sld.ship.Crew.Morale = 90;
    ChangeCrewExp(sld, "Sailors", 100);
	ChangeCrewExp(sld, "Cannoners", 100);
	ChangeCrewExp(sld, "Soldiers", 100);

    Fantom_SetBalls(sld, "pirate");
    Fantom_SetCharacterGoods(sld, GOOD_BALLS,  3900 + rand(300), 0);
	Fantom_SetCharacterGoods(sld, GOOD_BOMBS,  2900 + rand(300), 0);
	Fantom_SetCharacterGoods(sld, GOOD_POWDER, 6900 + rand(300), 0);

    LAi_SetCurHPMax(sld); // если он умер

    string sGroup = "Sea_GhostCapt";  // приставка "Sea_" + ИД важна
    Group_FindOrCreateGroup(sGroup);
	Group_AddCharacter(sGroup, "GhostCapt");
    Group_SetGroupCommander(sGroup, "GhostCapt");

    SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_ENEMY);
    Group_SetTaskAttackInMap(sGroup, PLAYER_GROUP);
    Group_LockTask(sGroup);

    Map_CreateWarrior("", "GhostCapt", 3);

    Pchar.quest.GhostShip_Dead.win_condition.l1 = "NPC_Death";
	Pchar.quest.GhostShip_Dead.win_condition.l1.character = "GhostCapt";
	Pchar.quest.GhostShip_Dead.win_condition = "GhostShip_Dead";
}

void Survive_In_Sea_Go2Land()
{
    string  sTemp;
    int     iDay, n, i, idx;
    ref 	ch;
    
	PChar.nation = GetBaseHeroNation();
    // трем всех офов и компаньонов, не квестовых
    iDay = GetPassengersQuantity(pchar);
    i = 0;
    n = 0;
 	while (i < iDay)
	{
		i++;
		idx = GetPassenger(pchar, n); // всегда первый в массиве со смещением, если не трем
		if (idx==-1) break;
		ch = GetCharacter(idx);
		if (GetRemovable(ch)) // квестовых не трогаем
		{
		    ch.LifeDay = 1; // чтоб не сразу потерся
		    RemovePassenger(pchar, ch);
			ChangeCharacterAddress(ch,"none","");
		}
		else
		{
		    n++;
		}
	}
	
    for (i=0; i<COMPANION_MAX; i++)
	{
		idx = GetCompanionIndex(pchar, i);
		if (idx != -1)
		{
            ch = GetCharacter(idx);
			if (GetShipRemovable(ch) && GetRemovable(ch))  // не трогаем квестовых и ПГГ
			{
			    ch.LifeDay = 1; // чтоб не сразу потерся
			    RemoveCharacterCompanion(pchar, ch);
			}
		}
	}
	
	DeleteAttribute(pchar, "ship");
	pchar.ship.name = "";
	pchar.ship.type = SHIP_NOTUSED;
	pchar.money = 0;

	SetCharacterShipLocation(pchar, "");

	// выбор островного города близ бухты
	i = 1;
	n = 0;
	if (MOD_SKILL_ENEMY_RATE >= 10)
	{
		i--;
		n++;
	}
	sTemp = SelectColonyExt(pchar, "I", "5", i, "", n, "");

    makeref(ch, colonies[FindColony(sTemp)]);
    setWDMPointXZ(ch.from_sea);
    pchar.location = ch.from_sea; // это порт, ниже ищем бухту

    // нулим предметы на корабле
    CleanAllShipBoxes(true);

	Pchar.GenQuest.Hunter2Pause = true;
    iDay = 5+rand(17);
    bQuestCheckProcessFreeze = true;
    WaitDate("",0,0,iDay, rand(10), 1); // прошло время
    bQuestCheckProcessFreeze = false;
    
	// бухта контры
    pchar.location = SelectSmugglingLocation();
    
    pchar.Health.Damg = stf(pchar.chr_ai.hp_max)*40;
	// даёт лог в + и - AddCharacterHealth(pchar, -30);
	Log_Info(StringFromKey("InfoMessages_117", pchar));
	if (sti(PChar.GenQuest.GhostShip.KillMe) <= 1)
	{
		AddQuestRecord("GhostShipQuest", "Survive_1");
		AddQuestUserData("GhostShipQuest", "sSex", GetSexPhrase("","а"));
	}
	else
	{
	    AddQuestRecord("GhostShipQuest", "Survive_2");
	    // добавить предмет Т102
	    if (CheckCharacterPerk(pchar, "WildCaribbean") && sti(PChar.GenQuest.GhostShip.KillMe) == 2)
		{
			Log_Info(StringFromKey("InfoMessages_118"));
			TakeNItems(Pchar, "term_arm", 1);
	    	pchar.QuestTemp.TakeArmT102 = true;
	    }
	}
	TEV.FD_Reload = "afterFDsink";
	bDisableMapEnter           = false;   // мир, был бой с ЛГ
	
	//слухи
	for(i = 0; i < 2; i++)
	{
		switch(i)
		{
			case 0:
				sTemp = StringFromKey("Common_rumours_173", GetAddress_Form(pchar));
			break;
			case 1:
				sTemp = StringFromKey("Common_rumours_174");
			break;
		}
		n = FindRumour(AddSimpleRumourTip(sTemp, 60, 2, "habitue", ""));
		Rumour[n].group = "GhostShip_Sink";
	}
	
	SetLaunchFrameFormParam(StringFromKey("InfoMessages_33", iDay, XI_ConvertString("day3"), NewStr(), XI_ConvertString("Colonyisland"), GetConvertStr(ch.islandLable, "LocLables.txt"), NewStr(), GetConvertStr(pchar.location, "LocLables.txt")), "Reload_To_Location", 0.1, 7.0);
    SetLaunchFrameReloadLocationParam(pchar.location, "Smugglers", "Smuggler01", "");
	LaunchFrameForm();
}

void GhostShipInit()
{
	ref sld;
	//============> Капитан призрака
	sld = GetCharacter(NPC_GenerateCharacter("GhostCapt", "VanderDecken", "skeleton", "man", 55, PIRATE, -1, true));
	sld.skeleton = "1";
	sld.dialog.filename      = "Quest\GhostShip_dialog.c";
	sld.dialog.currentnode   = "GhostCapt";
	sld.name 	= FindPersonalName("GhostCapt_name");
	sld.lastname = FindPersonalName("GhostCapt_lastname");
	sld.reputation = 15;
	LAi_NoRebirthDisable(sld);
	LAi_RebirthOldName(sld);
	sld.RebirthPhantom     = true;
	sld.AlwaysEnemy        = true;
	sld.DontHitInStorm     = true; // не ломается в шторм
	sld.DontRansackCaptain = true; //квестовые не сдаются
	sld.SinkTenPercent     = false;  // не тонуть после 10% корпуса
	sld.Abordage.Enable    = false; // запрет абордажа
	sld.SaveItemsForDead   = true; // сохранять на трупе вещи
	sld.cirassId           = FindItem("cirass5");  // предмета нет, но влияение есть
	sld.AlwaysSandbankManeuver = true;  // тупым запрет тонуть об берег
	sld.CrewType.Skel       = true; // на абордаже скелеты
	LAi_SetHP(sld, 666, 666);
	SetCharacterPerk(sld, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, дается ГГ и боссам уровней
    sld.SuperShooter  = true;
    
	DeleteAttribute(sld, "items");
	GiveItem2Character(sld, "topor2");
	EquipCharacterByItem(sld, "topor2");
	GiveItem2Character(sld, "pistol6");
	EquipCharacterByItem(sld, "pistol6");
	TakeNItems(sld, "bullet", 10);
	AddItems(sld, "GunPowder", 10);
	TakeNItems(sld,"potion2", 10);
	sld.money = 70000;
	
//	LAi_SetLoginTime(sld, 6.0, 21.99); // <---  а вот это вот нахрена было ? ugeen
	LAi_SetCitizenType(sld);
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	sld.Ship.Type = CreateBaseShip(SHIP_FLYINGDUTCHMAN);
	sld.Ship.Name = FindPersonalName("GhostCapt_ship");
	
	ref rRealShip = GetRealShip(sti(sld.Ship.Type));
	//sld.ship.sailscolor = argb(255,60,60,60);
	rRealShip.ship.upgrades.sails = 3;
	rRealShip.EmblemedSails.normalTex =  "ships\parus_common_torn.tga";
	rRealShip.ShipSails.SailsColor = argb(255,60,60,60);
	rRealShip.MaxCaliber = 48;
    rRealShip.Cannon     = CANNON_TYPE_CANNON_LBS48;
    rRealShip.HP         = 400000;
	
	pchar.GenQuest.GhostShip.ShipType   = sti(sld.Ship.Type); // запомним, потом пригодится, когда парус нужно сменить на целый
}

// Появление Т-102 в комнате таверны
void QuestArmT102()
{
	ref sld;
	sld = GetCharacter(NPC_GenerateCharacter("T102", "skelT", "man", "man_B", 55, PIRATE, 0, false));
	sld.skeleton = "1";
	sld.dialog.filename = "Quest\T102_dialog.c";
    
	sld.name = "Terminator";
	sld.lastname = "";
	TakeNItems(sld,"potion2", 30);
	LAi_SetHP(sld, 1600.0, 1600.0);
	
	ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
	LAi_group_MoveCharacter(sld, "TmpEnemy");
	LAi_SetActorType(sld);
	LAi_SetActorType(pchar);

	SetActorDialogAny2Pchar(sld.id, "", 2.0, 0.0);
	LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 4.0);
	LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
}

//=====================================================================================================================================
// <-- Квест летучего голландца
//=====================================================================================================================================

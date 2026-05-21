
bool bInteractiveReadCommand = true;
string sInteractiveCommand = "";

void InitInteractiveInterface()
{
	SetEventHandler("Control Activation", "II_ProcessControlPress", 0);
}

void DeleteInteractiveInterface()
{
	DelEventHandler("Control Activation", "II_ProcessControlPress");
}

void II_ProcessControlPress()
{
	string ControlName = GetEventData();
	if( sti(InterfaceStates.Launched) != 0 ) {return;}
	
	switch(ControlName)
	{
		case "IntCode0": 
			II_AddCodeToCommand("0");
		break;
		
		case "IntCode1": 
			II_AddCodeToCommand("1");
		break;
		
		case "IntCode2": 
			II_AddCodeToCommand("2");
		break;
		
		case "IntCode3": 
			II_AddCodeToCommand("3");
		break;
		
		case "IntCode4": 
			II_AddCodeToCommand("4");
		break;
		
		case "IntCode5": 
			II_AddCodeToCommand("5");
		break;
		
		case "IntCode6": 
			II_AddCodeToCommand("6");
		break;
		
		case "IntCode7": 
			II_AddCodeToCommand("7");
		break;
		
		case "IntCode8": 
			II_AddCodeToCommand("8");
		break;
		
		case "IntCode9": 
			II_AddCodeToCommand("9");
		break;
		
		case "IntCodeEnd": 
			II_ExecuteCommand();
		break;
	}
}

void II_AddCodeToCommand(string code)
{
	if(!bInteractiveReadCommand) return;
	sInteractiveCommand = sInteractiveCommand + code;
}

void II_ExecuteCommand()
{
	if(sInteractiveCommand == "")
	{
		bInteractiveReadCommand = true;
		return;
	}
	
	if(bSeaActive && bAbordageStarted)
	{
		II_ExecuteCommand_SeaAbordage();
	}
	else if(bSeaActive)
	{
	    II_ExecuteCommand_Sea();
	}
	else if(isEntity(&worldMap))
	{
		II_ExecuteCommand_Worldmap();
	}
	else
	{
		II_ExecuteCommand_Land();
	}
	
	bInteractiveReadCommand = false;
	sInteractiveCommand = "";
}

void II_ExecuteCommand_Land()
{
	trace("Выполнение команды (land) - " + sInteractiveCommand);
	ref RandChar;
	int iRank;
	if(CheckAttribute(pchar, "rank")) iRank = (1 + rand(pchar.rank));
	else iRank = 1;
	
	switch(sInteractiveCommand)
	{
		case "100":
			trace("Команда 100 - призыв 1 враждебного персонажа (гражданин испанец).");
			
			RandChar = GetCharacter(NPC_GenerateCharacter("RandSpainCitizen_" + rand(999), "citiz_" + (11 + rand(9)), "man", "man", iRank, SPAIN, -1, true));
			LAi_SetWarriorType(RandChar);
			LAi_group_MoveCharacter(RandChar, "EnemyFight");
			//ChangeCharacterAddressGroup(RandChar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			PlaceCharacter(RandChar, "goto", "random_must_be_near");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		case "101":
			trace("Команда 101 - призыв 1 враждебного персонажа (нищий испанец).");
			
			RandChar = GetCharacter(NPC_GenerateCharacter("RandSpainBomj_" + rand(999), "panhandler_" + (1 + rand(5)), "man", "man", iRank, SPAIN, -1, true));
			LAi_SetWarriorType(RandChar);
			LAi_group_MoveCharacter(RandChar, "EnemyFight");
			ChangeCharacterAddressGroup(RandChar, pchar.location, "goto", "goto1");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		case "102":
			trace("Команда 102 - призыв 1 враждебного персонажа (солдат испанец).");
			
			RandChar = GetCharacter(NPC_GenerateCharacter("RandSpainSoldier_" + rand(999), "sold_spa_" + (1 + rand(7)), "man", "man", iRank, SPAIN, -1, true));
			LAi_SetWarriorType(RandChar);
			LAi_group_MoveCharacter(RandChar, "EnemyFight");
			ChangeCharacterAddressGroup(RandChar, pchar.location, "goto", "goto1");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		case "103":
			trace("Команда 103 - призыв 1 враждебного персонажа (мушкетер испанец).");
			
			RandChar = GetCharacter(NPC_GenerateCharacter("RandSpainMusketeer_" + rand(999), "spa_mush_" + (1 + rand(3)), "man", "mushketer", iRank, SPAIN, -1, true));
			LAi_SetWarriorType(RandChar);
			LAi_group_MoveCharacter(RandChar, "EnemyFight");
			ChangeCharacterAddressGroup(RandChar, pchar.location, "goto", "goto1");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		case "104":
			trace("Команда 104 - призыв 1 враждебного персонажа (пират).");
			
			RandChar = GetCharacter(NPC_GenerateCharacter("RandPirate_" + rand(999), "pirate_" + (1 + rand(15)), "man", "man", iRank, PIRATE, -1, true));
			LAi_SetWarriorType(RandChar);
			LAi_group_MoveCharacter(RandChar, "EnemyFight");
			ChangeCharacterAddressGroup(RandChar, pchar.location, "goto", "goto1");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		case "105":
			trace("Команда 105 - призыв 1 враждебного персонажа (скелет).");
			
			RandChar = GetCharacter(NPC_GenerateCharacter("RandSkeleton_" + rand(999), "Skel" + (1 + rand(3)), "skeleton", "man", iRank, PIRATE, -1, true));
			RandChar.skeleton = "1";
			LAi_SetWarriorType(RandChar);
			LAi_group_MoveCharacter(RandChar, "EnemyFight");
			ChangeCharacterAddressGroup(RandChar, pchar.location, "goto", "goto1");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		break;
		case "106":
			trace("Команда 106 - призыв команды враждебных персонажей (испанцы).");
			
			int iGroup = rand(999);
			RandChar = GetCharacter(NPC_GenerateCharacter("RandSpainGroup_" + iGroup, "off_spa_" + (1 + rand(1)), "man", "man", iRank, SPAIN, -1, true));
			LAi_SetWarriorType(RandChar);
			LAi_group_MoveCharacter(RandChar, "EnemyGroupFight");	
			ChangeCharacterAddressGroup(RandChar, pchar.location, "goto", "goto1");
			for (int i=1; i<=rand(iRank); i++)
			{
				RandChar = GetCharacter(NPC_GenerateCharacter("RandSpainGroup_" + iGroup + "_" + i, "sold_spa_" + (1 + rand(7)), "man", "man", iRank, SPAIN, -1, true));
				DeleteAttribute(RandChar, "SuperShooter");
				RandChar.BreakTmplAndFightGroup = true;
				LAi_SetWarriorType(RandChar);
				LAi_group_MoveCharacter(RandChar, "EnemyGroupFight");
				ChangeCharacterAddressGroup(RandChar, pchar.location, "goto", "goto" + i);
			}
			LAi_group_SetRelation("EnemyGroupFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyGroupFight", LAI_GROUP_PLAYER, true);
		break;
		
	}
}

void II_ExecuteCommand_Sea()
{
	trace("Выполнение команды (sea) - " + sInteractiveCommand);
	switch(sInteractiveCommand)
	{
		case "100":
			trace("Команда 100 - призыв 1 враждебного корабля.");
			
		break;
		case "101":
			trace("Команда 101 - призыв группы враждебных кораблей.");
			
		break;
	}
}

void II_ExecuteCommand_SeaAbordage()
{
	trace("Выполнение команды (abordage) - " + sInteractiveCommand);
	
}

void II_ExecuteCommand_Worldmap()
{
	trace("Выполнение команды (worldmap) - " + sInteractiveCommand);
	
}

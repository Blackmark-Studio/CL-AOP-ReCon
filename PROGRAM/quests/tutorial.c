bool TryLaunchTutorial(string tutName, bool bVideo)
{
	return TryLaunchTutorialEx(tutName, bVideo, "Tutorial_" + tutName);
}

bool TryLaunchTutorialEx(string tutName, bool bVideo, string backFunction)
{
	Trace("Try Launch Tutorial: " + tutName);
    if (LaunchTutorial(tutName, bVideo))
	{
		Trace("Try Launch Tutorial Result = " + true);
	    return true;
	}
	else
	{
		Trace("Try Launch Tutorial Result = " + false);
		DoQuestFunctionDelay(backFunction, 1.0);
	    return false;
	}
}

void CheckDeleteFightTutorial(string tutorialName)
{
	DeleteAttribute(&TEV, "TutorialInfo.FightTutorials." + tutorialName);
    if (CheckAttribute(&TEV, "TutorialInfo.FightTutorials"))
	{
	    aref tutAttr; makearef(tutAttr, TEV.TutorialInfo.FightTutorials);
	    int q = GetAttributesNum(tutAttr);
	    if (q < 1)
		{
		    DeleteAttribute(&TEV, "TutorialInfo.FightTutorials");
		}
	}
}

bool TryLaunchTutorialForced(string tutName, bool bVideo, string sPicture, string backFunction)
{
	Trace("Try Launch Tutorial Forced: " + tutName);
    if (LaunchTutorialForced(tutName, bVideo, sPicture))
	{
		Trace("Try Launch Tutorial Result = " + true);
	    return true;
	}
	else
	{
		Trace("Try Launch Tutorial Result = " + false);
		DoQuestFunctionDelay(backFunction, 1.0);
	    return false;
	}
}

// Туториалы - Песочница
void SetTutorials_SandBox_TutDeck()
{
	TEV.TutorialInfo.Cure = true;
	TEV.TutorialInfo.TutDeck.GuideFight = true;
	TEV.TutorialInfo.TutDeck.LandTimeScaleDown = true;
	TEV.TutorialInfo.FightTutorials.BloodPrologue_Parry = true;
}

void Tutorial_TutDeck_GuideFight(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.TutDeck.GuideFight"))
	{
		if (TryLaunchTutorialEx("BloodPrologue_GuideFight", 1, "Tutorial_TutDeck_GuideFight"))
		{
			DeleteAttribute(&TEV, "TutorialInfo.TutDeck.GuideFight");
		}
	}
}

void Tutorial_TutDeck_LandTimeScaleDown(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.TutDeck.LandTimeScaleDown"))
	{
		if (TryLaunchTutorialEx("LandTimeScaleDown", 1, "Tutorial_TutDeck_LandTimeScaleDown"))
		{
			DeleteAttribute(&TEV, "TutorialInfo.TutDeck.LandTimeScaleDown");
			TEV.TutorialInfo.FightTutorials.Marksmanship = true;
		}
	}
}

void SetTutorials_SandBox_AfterDeck()
{
	// Суша - мирный
	TEV.TutorialInfo.TimeScale = true;
	TEV.TutorialInfo.Box = true;
	TEV.TutorialInfo.Rest = true;
	TEV.TutorialInfo.Health = true;
	TEV.TutorialInfo.Fighters = true;
	TEV.TutorialInfo.Stealth = true;
	TEV.TutorialInfo.Stashes = true;
	TEV.TutorialInfo.Mushket = true;

	// Суша - бой
	// перенос туториалов с палубы -->
	if (CheckAttribute(&TEV, "TutorialInfo.TutDeck.GuideFight"))
	{
		TEV.TutorialInfo.FightTutorials.GuideFight = true;
	}
	else
	{
		if (CheckAttribute(&TEV, "TutorialInfo.TutDeck.LandTimeScaleDown"))
		{
			SetTutorials_SandBox_Fight2("");
		}
		else
		{
		    SetTutorials_SandBox_Fight3("");
		}
	}
	DeleteAttribute(&TEV, "TutorialInfo.TutDeck");
	// <--
	TEV.TutorialInfo.Collision = true;

	// Море - мирный
	TEV.TutorialInfo.ShipControl = true;
	TEV.TutorialInfo.SeaFastTravel = true;
	TEV.TutorialInfo.SeaFastTravel_Advanced = true;
	TEV.TutorialInfo.SeaStorm = true;

	// Море - бой
	TEV.TutorialInfo.SeaBattle = true;
    TEV.TutorialInfo.BoardingTactics = true;

	// Прочее
	TEV.TutorialInfo.LogBook = true;
	TEV.TutorialInfo.Perk = true;
	TEV.TutorialInfo.Navigation = true;
	TEV.TutorialInfo.Encyclopedia = true;
	TEV.TutorialInfo.Alchemy = true;

	TEV.TutorialInfo.WorldMap = true;
	pchar.quest.Tut_WorldMap.win_condition.l1          = "MapEnter";
	pchar.quest.Tut_WorldMap.function                  = "Tutorial_WorldMap";

	TEV.TutorialInfo.Salary = true;
	SetFunctionTimerCondition("Tutorial_Salary_Delay", 0, 0, 28, true);
}

void CheckLandTutorials()
{
	if(!bLandInterfaceStart) return;

	Tutorial_TimeScale("");
	Tutorial_Rest("");
	Tutorial_Box("");
	Tutorial_Stealth("");
	Tutorial_Navigation("");
	Tutorial_Fighters("");
	Tutorial_Mushket("");
	Tutorial_Stashes("");
}

void CheckAlarmFightTutorials()
{
	if (CheckAttribute(&TEV, "TutorialInfo.FightTutorials"))
	{
		// 1 сражение
		Tutorial_BloodPrologue_GuideFight("");
		Tutorial_GuideFight("");
		// 2 сражение
		Tutorial_LandTimeScaleDown("");
		Tutorial_BloodPrologue_Marksmanship("");
		Tutorial_Marksmanship("");
		// 3 сражение
		Tutorial_Dash("");
	}
}

void CheckBoardingTutorials()
{
	if(!bAbordageStarted || bCabinStarted) return;

	Tutorial_Collision("");
}

#event_handler("Event_CheckSeaTutorials", "CheckSeaTutorials");
void CheckSeaTutorials()
{
	bool isSeaLoaded = bSeaActive && !bAbordageStarted;
	if (!isSeaLoaded)
		return;

	Tutorial_ShipControl("");
	Tutorial_SeaFastTravel("");
	Tutorial_Navigation("");
	Tutorial_SeaStorm("");
}

#event_handler("Event_CheckSeaBattleTutorials", "CheckSeaBattleTutorials");
void CheckSeaBattleTutorials()
{
	bool isSeaLoaded = bSeaActive && !bAbordageStarted;
	if (!isSeaLoaded)
		return;

	Tutorial_SeaBattle("");
	Tutorial_BoardingTactics("");
	Tutorial_BoardingTactics_Advanced("");
}

// запускается вручную при загрузке в порту -->
void Tutorial_CameraControl_Delay(string qName)
{
	DoQuestFunctionDelay("Tutorial_CameraControl", 2.0);

	Achievment_Set(ACH_Korsary_akhoy);
}

void Tutorial_CameraControl(string qName)
{
	if (TryLaunchTutorial("CameraControl", 1))
	{
		SetTutorials_SandBox_AfterDeck();
		DoQuestFunctionDelay("MakeQuestAutoSaveDelay", 0.1);
	}
}
// <--

void Tutorial_GuideFight(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.FightTutorials.GuideFight"))
	{
		if (TryLaunchTutorialEx("BloodPrologue_GuideFight", 1, "Tutorial_GuideFight"))
		{
			CheckDeleteFightTutorial("GuideFight");

			pchar.quest.Tutorial_SandBox_fight1_AlarmOff.win_condition.l1 = "Alarm";
			pchar.quest.Tutorial_SandBox_fight1_AlarmOff.win_condition.l1.value = 1;
			pchar.quest.Tutorial_SandBox_fight1_AlarmOff.win_condition.l1.operation = "<";
			pchar.quest.Tutorial_SandBox_fight1_AlarmOff.function = "SetTutorials_SandBox_Fight2";
		}
	}
}

void SetTutorials_SandBox_Fight2(string qName)
{
	TEV.TutorialInfo.FightTutorials.LandTimeScaleDown = true;
	TEV.TutorialInfo.FightTutorials.Marksmanship = true;
}

void Tutorial_LandTimeScaleDown(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.FightTutorials.LandTimeScaleDown"))
	{
		if (TryLaunchTutorial("LandTimeScaleDown", 1))
		{
			CheckDeleteFightTutorial("LandTimeScaleDown");

			pchar.quest.Tutorial_SandBox_fight2_AlarmOff.win_condition.l1 = "Alarm";
			pchar.quest.Tutorial_SandBox_fight2_AlarmOff.win_condition.l1.value = 1;
			pchar.quest.Tutorial_SandBox_fight2_AlarmOff.win_condition.l1.operation = "<";
			pchar.quest.Tutorial_SandBox_fight2_AlarmOff.function = "SetTutorials_SandBox_Fight3";
		}
	}
}

void SetTutorials_SandBox_Fight3(string qName)
{
	TEV.TutorialInfo.FightTutorials.Dash = true;
}

void Tutorial_Dash(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.FightTutorials.Dash"))
	{
		if (TryLaunchTutorialEx("BloodPrologue_Dash", 1, "Tutorial_Dash"))
		{
			CheckDeleteFightTutorial("Dash");
		}
	}
}

void Tutorial_Marksmanship(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.FightTutorials.Marksmanship"))
	{
		bool isGunEquip = GetCharacterEquipByGroup(pchar, GUN_ITEM_TYPE) != "";
		if (!isGunEquip) return;

		if (TryLaunchTutorialEx("BloodPrologue_Marksmanship", 1, "Tutorial_Marksmanship"))
		{
			CheckDeleteFightTutorial("Marksmanship");
		}
	}
}

void Tutorial_Cure(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Cure"))
	{
		bool isPotInInventory = ForceFindCharacterItemByGroup(pchar, POTION_ITEM_TYPE) != "";
		if (!isPotInInventory) return;

		if (TryLaunchTutorial("Cure", 1))
		{
			DeleteAttribute(&TEV, "TutorialInfo.Cure");
		}
	}
}

void Tutorial_Logbook(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Logbook"))
	{
		if (TryLaunchTutorial("Logbook", 1))
		{
			DeleteAttribute(&TEV, "TutorialInfo.Logbook");
		}
	}
}

void Tutorial_Mushket(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Mushket"))
	{
		bool isMusInInventory = ForceFindCharacterItemByGroup(pchar, MUSKET_ITEM_TYPE) != "";
		if (!isMusInInventory) return;

		if (TryLaunchTutorial("Mushket", 1))
		{
			DeleteAttribute(&TEV, "TutorialInfo.Mushket");
		}
	}
}

void Tutorial_Collision(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Collision"))
	{
		if (TryLaunchTutorial("Collision", 1))
		{
			DeleteAttribute(&TEV, "TutorialInfo.Collision");
		}
	}
}

void Tutorial_Rest(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Rest"))
	{
		if (bAbordageStarted || bCabinStarted)
			return;
    	if (!IsTimeSkipPossible() || IsLoginTime())
    		return;

		if (TryLaunchTutorial("Rest", 1))
		{
			DeleteAttribute(&TEV, "TutorialInfo.Rest");
		}
	}
}

void Tutorial_Health(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Health"))
	{
		if (TryLaunchTutorial("Health", 1))
		{
			DeleteAttribute(&TEV, "TutorialInfo.Health");
		}
	}
}

void Tutorial_Box(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Box"))
	{
		if (!bCabinStarted || pchar.location != Pchar.SystemInfo.CabinType)
			return;

		if (TryLaunchTutorial("Box", 1))
		{
			DeleteAttribute(&TEV, "TutorialInfo.Box");
		}
	}
}

void Tutorial_Fighters(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Fighters"))
	{
		if (!CheckFighterOfficers())
			return;

		if (TryLaunchTutorial("Fighters", 1))
		{
			DeleteAttribute(&TEV, "TutorialInfo.Fighters");
		}
	}
}

void Tutorial_Encyclopedia(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Encyclopedia"))
	{
		if (TryLaunchTutorial("Encyclopedia", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.Encyclopedia");
		}
	}
}

void Tutorial_WorldMap(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.WorldMap"))
	{
		if (TryLaunchTutorial("WorldMap", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.WorldMap");
		}
	}
}

void Tutorial_Salary_Delay(string qName)
{
	if (CheckAttribute(pchar, "quest.Tutorial_Salary_Delay"))
	{
		pchar.quest.Tutorial_Salary_Delay.over = "yes"; //снять таймер
	}

	DoQuestFunctionDelay("Tutorial_Salary", 5.0);
}

void Tutorial_Salary(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Salary"))
	{
		if (bAbordageStarted)
		{
			pchar.quest.Tutorial_Salary1.win_condition.l1 = "ExitFromSea";
			pchar.quest.Tutorial_Salary1.function = "Tutorial_Salary_Delay";
			return;
		}
		if (TryLaunchTutorial("Salary", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.Salary");
		}
	}
}

void Tutorial_Navigation(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Navigation"))
	{
		// На всякий случай
		if (sti(pchar.rank) >= 15)
		{
			DeleteAttribute(&TEV, "TutorialInfo.Navigation");
		    return;
		}
		// считаем навигацию
        int sailSkill = GetSummonSkillFromNameSimple(pchar, SKILL_SAILING);
        int needSkill = GetShipClassNavySkill(GetCharacterShipClass(pchar));

        if (sailSkill >= needSkill)
        {
			return;
        }

		if (TryLaunchTutorial("Navigation", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.Navigation");
		}
	}
}

void Tutorial_Perk(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Perk"))
	{
		if (TryLaunchTutorial("Perk", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.Perk");
		}
	}
}

void Tutorial_TimeScale(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.TimeScale"))
	{
		if (!IsEntity(loadedLocation)) return;
		if (loadedLocation.type != "jungle")
		{
			return;
		}

		if (TryLaunchTutorialEx("BloodPrologue_TimeScale", 1, "Tutorial_TimeScale"))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.TimeScale");
		}
	}
}


void Tutorial_Stealth(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.Stealth"))
	{
		if (!IsEntity(loadedLocation)) return;
		if (!CheckAttribute(loadedLocation, "townsack")) return;
		string townSack = loadedLocation.townsack;
		if (loadedLocation.type != "jungle" || townSack == "")
		{
			return;
		}
		int iNation = GetCityNation(townSack);
		if (iNation == PIRATE || GetNationRelation2MainCharacter(iNation) != RELATION_ENEMY)
			return;

		if (TryLaunchTutorial("Stealth", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.Stealth");
		}
	}
}

void Tutorial_Stashes(string qName)
{
	aref secretBox;

	if (CheckAttribute(&TEV, "TutorialInfo.Stashes"))
	{
		if (!IsEntity(loadedLocation)) return;
		if (loadedLocation.type != "house" || !(FindLocator(loadedLocation.id, "secret1", &secretBox, true))) return; // если sectet1 нет, то выходим

		if (TryLaunchTutorial("Stashes", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.Stashes");
		}
	}
}

void Tutorial_ShipControl(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.ShipControl"))
	{
		if (TryLaunchTutorial("ShipControl", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.ShipControl");
		}
	}
}

void Tutorial_SeaFastTravel(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.SeaFastTravel"))
	{
		if (TryLaunchTutorial("SeaFastTravel", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.SeaFastTravel");
		}
	}
}

void PGGQuest_LaunchBoatTutor(string qName)
{
	if (CheckAttribute(PChar, "GenQuest.PGG_Quest.PGGid"))
	{
		ref chr = CharacterFromID(PChar.GenQuest.PGG_Quest.PGGid);
		if (GetRelation(sti(pchar.index), sti(chr.index)) != RELATION_ENEMY)
		{
			DoQuestFunctionDelay("Tutorial_SeaFastTravel_Advanced", 1.5);
		}
	}
}

void Tutorial_SeaFastTravel_Advanced(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.SeaFastTravel_Advanced"))
	{
		if (TryLaunchTutorial("SeaFastTravel_Advanced", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.SeaFastTravel_Advanced");
		}
	}
}

void Tutorial_SeaStorm(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.SeaStorm"))
	{
		if (iStormLockSeconds <= 0)
		{
			return;
		}

		if (TryLaunchTutorial("SeaStorm", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.SeaStorm");
		}
	}
}

void Tutorial_SeaBattle(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.SeaBattle"))
	{
		bool isSeaLoaded = bSeaActive && !bAbordageStarted;
		if (!isSeaLoaded)
			return;

		if (TryLaunchTutorial("SeaBattle", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.SeaBattle");
		}
	}
}

void Tutorial_BoardingTactics(string qName)
{
	aref aShips;

	if (CheckAttribute(&TEV, "TutorialInfo.BoardingTactics"))
	{
		bool isSeaLoaded = bSeaActive && !bAbordageStarted;
		if (!isSeaLoaded)
			return;
		if (!CheckAttribute(pchar, "Ship.Cannons.Charge.Type") || sti(pchar.Ship.Cannons.Charge.Type) != GOOD_GRAPES)
			return;
		if (!CheckAttribute(pchar, "SeaAI.Update.Ships"))
		    return;

		makearef(aShips, pchar.SeaAI.Update.Ships);
		int iShipsNum = GetAttributesNum(aShips);

		if (iShipsNum < 0)
			return;

		if (TryLaunchTutorial("BoardingTactics", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.BoardingTactics");

	    	pchar.Quest.Tutorial_SandBox_ExitSeaBattle2.win_condition.l1 = "ExitFromSea";
			pchar.Quest.Tutorial_SandBox_ExitSeaBattle2.function = "SetTutorials_SandBox_EnterToSea3";
		}
	}
}

void SetTutorials_SandBox_EnterToSea3(string qName)
{
    TEV.TutorialInfo.BoardingTactics_Advanced = true;
}

void Tutorial_BoardingTactics_Advanced(string qName)
{
	aref aShips;
	bool bOk = false;

	if (CheckAttribute(&TEV, "TutorialInfo.BoardingTactics_Advanced"))
	{
		bool isSeaLoaded = bSeaActive && !bAbordageStarted;
		if (!isSeaLoaded)
			return;
		if (!CheckAttribute(pchar, "SeaAI.Update.Ships"))
		    return;

		makearef(aShips, pchar.SeaAI.Update.Ships);
		int iShipsNum = GetAttributesNum(aShips);
		for (int i=0; i<iShipsNum; i++)
		{
			aref aShip = GetAttributeN(aShips, i);
			ref rShipCharacter = GetCharacter(sti(aShip.idx));
			ref rRealShip = GetRealShip(sti(rShipCharacter.Ship.Type));

			if (CheckAttribute(rRealShip, "isFort") || GetRelation(sti(pchar.index), sti(aShip.idx)) != RELATION_ENEMY)
			{
				continue;
			}

			if (GetCharacterShipClass(rShipCharacter) <= 3)
			{
			    bOk = true;
			    break;
			}
		}

		if (!bOk)
			return;

		if (TryLaunchTutorial("BoardingTactics_Advanced", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.BoardingTactics_Advanced");
		}
	}
}


// Туториалы - Блад
void Tutorial_BloodPrologue_CameraControl_Delay()
{
	DoQuestFunctionDelay("Tutorial_BloodPrologue_CameraControl", 1.5);

	Achievment_Set(ACH_Korsary_akhoy);
}

void Tutorial_BloodPrologue_CameraControl(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.BloodPrologue_CameraControl"))
	{
		if (TryLaunchTutorial("BloodPrologue_CameraControl", 1))
		{
	    	DeleteAttribute(&TEV, "TutorialInfo.BloodPrologue_CameraControl");
	    	DoQuestFunctionDelay("MakeQuestAutoSaveDelay", 0.1);
		}
	}
}

void Tutorial_BloodPrologue_LocItems(string qName)
{
	TryLaunchTutorial("BloodPrologue_LocItems", 1);
}

void Tutorial_BloodPrologue_Equipment(string qName)
{
	TryLaunchTutorial("BloodPrologue_Equipment", 1);
}


void Tutorial_BloodPrologue_GuideFight(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.FightTutorials.BloodPrologue_GuideFight"))
	{
		if (TryLaunchTutorial("BloodPrologue_GuideFight", 1))
		{
			CheckDeleteFightTutorial("BloodPrologue_GuideFight");
		}
	}
}

void Tutorial_BloodPrologue_Parry(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.FightTutorials.BloodPrologue_Parry"))
	{
		if (TryLaunchTutorial("BloodPrologue_Parry", 1))
		{
			CheckDeleteFightTutorial("BloodPrologue_Parry");
		}
	}
}

void Tutorial_BloodPrologue_Marksmanship(string qName)
{
	if (CheckAttribute(&TEV, "TutorialInfo.FightTutorials.BloodPrologue_Marksmanship"))
	{
		if (TryLaunchTutorial("BloodPrologue_Marksmanship", 1))
		{
			CheckDeleteFightTutorial("BloodPrologue_Marksmanship");
		}
	}
}

// эти запускаются вручную в нужный момент -->
void Tutorial_BloodPrologue_TimeScale_Delay()
{
	DoQuestFunctionDelay("Tutorial_BloodPrologue_TimeScale", 5.0);
}

void Tutorial_BloodPrologue_TimeScale(string qName)
{
	TryLaunchTutorial("BloodPrologue_TimeScale", 1);
}

void Tutorial_BloodPrologue_Alchemy_Delay()
{
	DoQuestFunctionDelay("Tutorial_BloodPrologue_Alchemy", 2.0);
}

void Tutorial_BloodPrologue_Alchemy(string qName)
{
	TryLaunchTutorial("BloodPrologue_Alchemy", 1);
}

void Tutorial_BloodPrologue_StashesDelay(string qName)
{
	DoQuestFunctionDelay("Tutorial_BloodPrologue_Stashes", 1.5);
}

void Tutorial_BloodPrologue_Stashes(string qName)
{
	TryLaunchTutorial("BloodPrologue_Stashes", 1);
}

void Tutorial_BloodPrologue_LandTimeScaleDown(string qName)
{
	if (!CheckAttribute(&TEV, "TutorialInfo.BloodState.LandTimeScaleDown"))
	{
		if (TryLaunchTutorialEx("LandTimeScaleDown", 1, "Tutorial_BloodPrologue_LandTimeScaleDown"))
		{
			TEV.TutorialInfo.BloodState.LandTimeScaleDown = true;
		}
	}
}

void Tutorial_BloodPrologue_Dash(string qName)
{
	if (!CheckAttribute(&TEV, "TutorialInfo.BloodState.Dash"))
	{
		if (TryLaunchTutorial("BloodPrologue_Dash", 1))
		{
			TEV.TutorialInfo.BloodState.Dash = true;
		}
	}
}

void Tutorial_BloodPrologue_DeadSearch(string qName)
{
	if (!CheckAttribute(&TEV, "TutorialInfo.BloodState.DeadSearch"))
	{
		if (TryLaunchTutorial("BloodPrologue_DeadSearch", 1))
		{
			TEV.TutorialInfo.BloodState.DeadSearch = true;
		}
	}
}

void Tutorial_BloodPrologue_StartBarbadosFightTutorials_OnDialogExit()
{
	Tutorial_BloodPrologue_StartBarbadosFightTutorials("");
}

void Tutorial_BloodPrologue_StartBarbadosFightTutorials(string qName)
{
	if (!CheckAttribute(&TEV, "TutorialInfo.BloodState.LandTimeScaleDown"))
	{
		Tutorial_BloodPrologue_LandTimeScaleDown("");
		return;
	}
	if (!CheckAttribute(&TEV, "TutorialInfo.BloodState.Dash"))
	{
		Tutorial_BloodPrologue_Dash("");
		return;
	}
}

void Tutorial_BloodPrologue_Officers(string qName)
{
	TryLaunchTutorial("BloodPrologue_Officers", 1);
}

void Tutorial_BloodPrologue_ShipControl(string qName)
{
	TryLaunchTutorial("BloodPrologue_ShipControl", 1);
}

void Tutorial_BloodPrologue_SeaBattle(string qName)
{
	TryLaunchTutorial("BloodPrologue_SeaBattle", 1);
}

void Tutorial_BloodPrologue_SeaEscape(string qName)
{
	if(CheckCharacterItem(Pchar, "Spyglass2") == 0) GiveItem2Character(Pchar, "Spyglass2");
	EquipCharacterbyItem(Pchar, "Spyglass2");

	TryLaunchTutorial("BloodPrologue_SeaEscape", 1);
}

void Tutorial_BloodPrologue_EnterMap(string qName)
{
	TryLaunchTutorial("BloodPrologue_EnterMap", 1);
}

void Tutorial_BloodPrologue_WorldMap(string qName)
{
	TryLaunchTutorial("BloodPrologue_WorldMap", 1);
}

void Tutorial_BloodPrologue_FastTravel(string qName)
{
	if (!bSeaActive) return;

	if (!CheckAttribute(&TEV, "TutorialInfo.BloodState.FastTravelShown"))
	{
		if (TryLaunchTutorial("BloodPrologue_FastTravel", 1))
		{
			TEV.TutorialInfo.BloodState.FastTravelShown = true;
		}
	}
}

void Tutorial_BloodPrologue_Navigation(string qName)
{
    TryLaunchTutorial("BloodPrologue_Navigation", 1);
}

void Tutorial_BloodPrologue_BuyShip(string qName)
{
    TryLaunchTutorial("BloodPrologue_BuyShip", 1);
}

void Tutorial_BloodPrologue_ShipChange(string qName)
{
    TryLaunchTutorial("BloodPrologue_ShipChange", 1);
}

void Tutorial_BloodPrologue_SandBox(string qName)
{
	if (TryLaunchTutorialForced("BloodPrologue_SandBox", 1, "", "Tutorial_BloodPrologue_SandBox"))
	{
		SetBloodTutorials_SandBox();
		DoQuestFunctionDelay("BloodLine_WaitSandboxClose", 1.0);
	}
}

void BloodLine_WaitSandboxClose(string qName)
{
	if (sti(InterfaceStates.Launched))
	{
		DoQuestFunctionDelay("BloodLine_WaitSandboxClose", 1.0);
		return;
	}
	ChangePIRATES();
}
// <--

void SetTutorials_Blood_Start()
{
	TEV.TutorialInfo.BloodPrologue_CameraControl = true;
	TEV.TutorialInfo.FightTutorials.BloodPrologue_GuideFight = true;
	TEV.TutorialInfo.FightTutorials.BloodPrologue_Parry = true;
	TEV.TutorialInfo.Cure = true;
	TEV.TutorialInfo.Perk = true;
}

void SetTutorials_Blood_AfterFirstFight()
{
	TEV.TutorialInfo.FightTutorials.BloodPrologue_Marksmanship = true;
	TEV.TutorialInfo.BloodState.WinFirstFight = true;
}

void SetBloodTutorials_AfterEstate()
{
    if (!CheckAttribute(&TEV, "TutorialInfo.BloodState.WinFirstFight"))
	{
	    TEV.TutorialInfo.FightTutorials.Marksmanship = true; // ставим из SandBox с проверкой
	}
    TEV.TutorialInfo.LogBook = true;
}

void SetBloodTutorials_SandBox()
{
	// Суша - мирный
	TEV.TutorialInfo.Box = true;
	TEV.TutorialInfo.Rest = true;
	TEV.TutorialInfo.Health = true;
	TEV.TutorialInfo.Fighters = true;
	TEV.TutorialInfo.Stealth = true;
	TEV.TutorialInfo.Mushket = true;

	// Суша - бой
	TEV.TutorialInfo.Collision = true;
	// перенос туториалов из пролога -->
	if (!CheckAttribute(&TEV, "TutorialInfo.BloodState.LandTimeScaleDown"))
	{
		TEV.TutorialInfo.FightTutorials.LandTimeScaleDown = true;
	}
	else
	{
		if (!CheckAttribute(&TEV, "TutorialInfo.BloodState.Dash"))
		{
			TEV.TutorialInfo.FightTutorials.Dash = true;
		}
	}
	DeleteAttribute(&TEV, "TutorialInfo.BloodState");
	// <--

	// Море - мирный
	TEV.TutorialInfo.SeaFastTravel_Advanced = true;
	TEV.TutorialInfo.SeaStorm = true;

	// Море - бой
	TEV.TutorialInfo.BoardingTactics = true;

	// Прочее
	TEV.TutorialInfo.Encyclopedia = true;
	TEV.TutorialInfo.Salary = true;

	int curMonthDays = GetMonthDays(GetDataMonth(), GetDataYear());
	int daysRemain = curMonthDays - GetDataDay() - 3;
	if (daysRemain > 0)
	{
		SetFunctionTimerCondition("Tutorial_Salary_Delay", 0, 0, daysRemain, true);
	}
	else
	{
		SetFunctionTimerCondition("Tutorial_Salary_Delay", 0, 0, 1, true);
	}
}

// Шаблон для сообщения, вызываемого помимо обучения
void StartPlaytestMessage(string qName)
{
	if (true)
		return;

	if (TryLaunchTutorialForced("PlaytestRevardMessage", 0, "", "StartPlaytestMessage"))
	{
		// Здесь вызывать нужные ништяки
		//Log_TestInfo("Вы получили достижение за плейтест!");
	}

	// Текст необходимого сообщения, записывать в resource/INI/texts/russian/TutorialDescribe.txt
/*	;;;

	PlaytestRevardMessage_title {Steam Playtest}
	PlaytestRevardMessage_descr
	{
		Поздравляем! Вы получили достижение за плейтест. Свою награду получите в полной игре! Ура!
	}*/
}

void ApplyMigration(ref migrationState)
{
	Migration0004_GibraltarNoFort();
	Migration0004_MaracaiboExitTownFortReload();
	Migration0004_Misc();

	trace("Migration 0004_MaracaiboFortFixes successfuly applied");
}

// > Гибралтар без фантомного форта
void Migration0004_GibraltarNoFort()
{
	int iColony, iFort, iMayor, iFortNation;
	ref rColony, rMayor;

	iColony = FindColony("Gibraltar");
	if (iColony < 0)
	{
		trace("MaracaiboFortFixes: colony Gibraltar not found -> skipped");
		return;
	}
	makeref(rColony, Colonies[iColony]);

	iFort  = GetCharacterIndex("Gibraltar Fort Commander");
	iMayor = GetCharacterIndex("Gibraltar_Mayor");

	// > идущую осаду Гибралтара снимаем целиком
	if (CheckAttribute(&NullCharacter, "Siege.Colony") && NullCharacter.Siege.Colony == "Gibraltar" && CheckAttribute(&NullCharacter, "Siege.isSiege") && sti(NullCharacter.Siege.isSiege) == 1)
	{
		SiegeClear("");
		trace("MaracaiboFortFixes: active siege of Gibraltar cleared");
	}

	// > мэр становится комендантом Гибралтара
	if (iMayor >= 0)
	{
		makeref(rMayor, Characters[iMayor]);
		rMayor.Default.Crew.Quantity    = 1900;
		rMayor.Default.Crew.MinQuantity = 1200;
		if (!CheckAttribute(rMayor, "Default.nation"))
		{
			if (iFort >= 0 && CheckAttribute(&Characters[iFort], "Default.nation")) rMayor.Default.nation = Characters[iFort].Default.nation;
			else rMayor.Default.nation = rMayor.nation;
		}
		trace("MaracaiboFortFixes: Gibraltar_Mayor garrison -> applied");
	}
	else
		trace("MaracaiboFortFixes: Gibraltar_Mayor not found");

	// > освобождаем слот фантомного коменданта
	if (iFort >= 0)
	{
		// > штурм Гибралтара с суши (идущий или уже завершённый) переводим на мэра
		if (iMayor >= 0 && CheckAttribute(pchar, "GenQuestFort.fortCharacterIdx") && sti(pchar.GenQuestFort.fortCharacterIdx) == iFort)
		{
			pchar.GenQuestFort.fortCharacterIdx = iMayor;
			trace("MaracaiboFortFixes: GenQuestFort.fortCharacterIdx re-pointed to the mayor");
		}
		DeleteAttribute(pchar, "relation." + iFort);
		// > счётчик фортов нации рос на фантоме при создании
		iFortNation = -1;
		if (CheckAttribute(&Characters[iFort], "Default.nation")) iFortNation = sti(Characters[iFort].Default.nation);
		else if (rColony.nation != "none") iFortNation = sti(rColony.nation);
		if (iFortNation >= 0) AddFortNation(iFortNation, -1);
		InitCharacter(&Characters[iFort], iFort);
		trace("MaracaiboFortFixes: Gibraltar Fort Commander (slot " + iFort + ") removed");
	}

	rColony.commander = "-1";
	DeleteAttribute(rColony, "commanderIdx");
	rColony.HasNoFort = true;
	trace("MaracaiboFortFixes: Gibraltar.HasNoFort -> applied");
}

// > выход из Маракайбо без перехода в форт
void Migration0004_MaracaiboExitTownFortReload()
{
	aref arRld, arDis;
	int iLoc, i, iLeft;
	string sGo;

	iLoc = FindLocation("Maracaibo_ExitTown");
	if (iLoc < 0)
	{
		trace("MaracaiboExitTownFortReload: location Maracaibo_ExitTown not found -> skipped");
		return;
	}

	iLeft = 0;
	if (CheckAttribute(&Locations[iLoc], "reload"))
	{
		makearef(arRld, Locations[iLoc].reload);
		for (i = GetAttributesNum(arRld) - 1; i >= 0; i--)
		{
			arDis = GetAttributeN(arRld, i);
			if (!CheckAttribute(arDis, "name") || arDis.name != "reload2_back") continue;

			sGo = "";
			if (CheckAttribute(arDis, "go")) sGo = arDis.go;
			if (sGo != "Maracaibo_Fort")
			{
				iLeft++;
				continue;
			}

			trace("MaracaiboExitTownFortReload: reload." + GetAttributeName(arDis) + " (reload2_back -> Maracaibo_Fort) removed");
			DeleteAttribute(arRld, GetAttributeName(arDis));
		}
	}

	// > радиус локатора без перехода, который его использует - мусор
	if (iLeft == 0 && CheckAttribute(&Locations[iLoc], "locators_radius.reload.reload2_back"))
	{
		DeleteAttribute(&Locations[iLoc], "locators_radius.reload.reload2_back");
		trace("MaracaiboExitTownFortReload: locators_radius.reload.reload2_back removed");
	}
}

// > разное
void Migration0004_Misc()
{
	if (startHeroType == 1 && !GetGlobalTutor())
	{
		if (CheckAttribute(pchar, "questTemp.CapBloodLine") && pchar.questTemp.CapBloodLine != true)
		{
			DeleteQuestCondition("CapBloodLine_PittInCabin");
			DeleteQuestCondition("PrepareToEscape2_3");
			DeleteQuestCondition("CapBloodLine_InStidBedroom_1");
			DeleteQuestCondition("CapBloodLine_InGuberRoomAgain_1");
			trace("MaracaiboFortFixes: CapBloodLine fixes -> applied");
		}
	}

	if (CheckAttribute(pchar, "QuestInfo.Hunting_huntsman"))
	{
		aref arQuest; makearef(arQuest, pchar.QuestInfo.Hunting_huntsman);
		if (CheckQuestRecordEx(&arQuest, "0", "Hunting_huntsman") && !CheckAttrValue(pchar, "alchemy.dried_meat.isKnown", "1"))
		{
			pchar.alchemy.dried_meat.isKnown = "1";
			trace("MaracaiboFortFixes: Hunting_huntsman recipe_dried_meat -> applied");
		}
	}
}

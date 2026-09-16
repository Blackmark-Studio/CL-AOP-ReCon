void ApplyMigration(ref migrationState)
{
	aref arList;
	int n, iMaracaiboEnd, iGibraltarBegin, iGibraltarEnd;
	bool bPrologueOver = true;

	if (startHeroType == 1 && !GetGlobalTutor())
	{
		if (CheckAttribute(pchar, "questTemp.CapBloodLine"))
		{
			bPrologueOver = pchar.questTemp.CapBloodLine != true;
		}

		if (bPrologueOver && LAi_IsImmortal(pchar) && !CheckAttribute(pchar, "questTemp.Azzy.Immortal"))
		{
			LAi_SetImmortal(pchar, false);
			trace("PostBetaTestFixes pchar immortal fix -> applied");
		}
	}

	n = FindLocation("Aruba_Outpost");
	if (n >= 0)
	{
		Locations[n].models.always.jungle.tech = "DLightModel";
		trace("PostBetaTestFixes Aruba_Outpost -> applied");
	}

	n = FindLocation("Maracaibo_sklad02");
	if (n >= 0)
	{
		locations[n].type = "house";
		trace("PostBetaTestFixes Maracaibo_sklad02 -> applied");
	}

	n = FindLocation("Maracaibo_CaveEntrance");
	if (n >= 0)
	{
		locations[n].reload.l2.go = "Maracaibo_jungle_03";
		trace("PostBetaTestFixes Maracaibo_jungle_03 -> applied");
	}

	n = GetCharacterIndex("Providencia_trader");
	if (n >= 0)
	{
		Characters[n].greeting = "tra_common";
		trace("PostBetaTestFixes Providencia_trader greeting fix -> applied");
	}

	makearef(arList, Locations[0].IslandsList);
	if (CheckAttribute(arList, "Gibraltar"))
	{
		iMaracaiboEnd   = sti(arList.Maracaibo.end);
		iGibraltarBegin = sti(arList.Gibraltar.begin);
		iGibraltarEnd   = sti(arList.Gibraltar.end);

		if (iMaracaiboEnd == iGibraltarBegin)
		{
			arList.Maracaibo.end = iGibraltarEnd;
			DeleteAttribute(arList, "Gibraltar");
			trace("PostBetaTestFixes: Gibraltar -> Maracaibo (" + iGibraltarBegin + ".." + (iGibraltarEnd - 1) + ") applied");
		}
	}

	if (CheckAttribute(arList, "LostShipsIsland") && !CheckAttribute(arList, "LostShipsCity"))
	{
		arList.LostShipsCity.begin = sti(arList.LostShipsIsland.begin);
		arList.LostShipsCity.end   = sti(arList.LostShipsIsland.end);
		DeleteAttribute(arList, "LostShipsIsland");
		trace("PostBetaTestFixes: LostShipsIsland -> в LostShipsCity (" + arList.LostShipsCity.begin + ".." + (sti(arList.LostShipsCity.end) - 1) + ") applied");
	}

	// > Исправление бага в испанской линейке, 5 задание, захват Ла Веги
	// > Исправление бага в английской линейке, 8 задание, посещение Ла Веги
	if (sti(pchar.rank) >= 5)
	{
		n = FindLocation("LaVega_town");
		if (n >= 0)
		{
			locations[n].models.always.town = "LaVega";
			trace("PostBetaTestFixes LaVega_town models.always fix -> applied");
		}
	}

	TEV.ClearLostMigrations = "";

	trace("Migration 0003_PostBetaTestFixes successfuly applied");
}

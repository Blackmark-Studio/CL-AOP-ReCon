
void ApplyMigration(ref migrationState)
{
	int n, i, idx;
	bool bPrologueOver = true;
	ref sld, rPGG;
	aref arHold, curTable;
	string sOfficers[5];

	n = FindLocation("Gibraltar_tavern");
	if (n >= 0)
	{
		locations[n].filespath.models = "locations\inside\Tavern04\";
		trace("BetaTestFixesAll Gibraltar_tavern -> applied");
	}

	n = FindLocation("SantoDomingo_Admiralty");
	if (n >= 0)
	{
		locations[n].Admiralty = true;
		trace("BetaTestFixesAll SantoDomingo_Admiralty -> applied");
	}

	n = FindItem("MedicalSupplies");
	if (n >= 0)
	{
		Items[n].picIndex = "12";
		Items[n].picTexture = "ITEMS_15";
		trace("BetaTestFixesAll MedicalSupplies -> applied");
	}

	n = FindLocation("Aruba_Jungle_03");
	if (n >= 0)
	{
		Locations[n].filespath.models = "locations\Outside\Jungles\jungle14";
		Locations[n].models.always.jungle = "jungle14";
		Locations[n].models.always.locators = "jungle14_locators";
		Locations[n].models.always.grassPatch = "jungle14_grass";
		Locations[n].models.always.grassPatch.texture = "grass\grassshore.tga.tx";
		Locations[n].models.day.charactersPatch = "jungle14_patch";
		Locations[n].models.night.charactersPatch = "jungle14_patch";
		DeleteAttribute(&Locations[n], "models.always.rope");
		trace("BetaTestFixesAll Aruba_Jungle_03 -> applied");
	}

	n = FindLocation("Aruba_IndianVillage");
	if (n >= 0)
	{
		Locations[n].image = "loading\towns\pearl.tga";
		trace("BetaTestFixesAll Aruba_IndianVillage: loading image fixed");
	}

	n = FindLocation("Beliz_LowerShaft");
	if (n >= 0)
	{
		sld = &locations[n];
		DeleteAttribute(sld, "models.always.lamps");
		DeleteAttributeMass(sld, "locators_radius.item", "button01,detector1,item1,duhi1");
		trace("BetaTestFixesAll Beliz_LowerShaft -> applied");
	}

	// Лечим Бладовцев
	if (startHeroType == 1 && !GetGlobalTutor())
	{
		if (CheckAttribute(pchar, "questTemp.CapBloodLine"))
			bPrologueOver = pchar.questTemp.CapBloodLine != true;

		if (bPrologueOver)
		{
			sOfficers[0] = "Pitt";
			sOfficers[1] = "Dieke";
			sOfficers[2] = "Ogl";
			sOfficers[3] = "Volverston";
			sOfficers[4] = "Hugtorp";

			for (i = 0; i < 5; i++)
			{
				idx = GetCharacterIndex(sOfficers[i]);
				if (idx < 0) continue;

				sld = &Characters[idx];
				sld.Dialog.FileName = "Officer_Man.c";
				sld.Dialog.CurrentNode = "hired";
				sld.Dialog.TempNode = "hired";
				LAi_CharacterEnableDialog(sld);

				if (sOfficers[i] == "Pitt")
				{
					sld.Health.HP = 60.0;
					sld.Health.maxHP = 60.0;
					SetEnergyToCharacter(sld);
					LAi_SetCurHPMax(sld);
					LAi_SetRolyPoly(sld, true);
				}
			}

			// хвосты ветки с оружейником
			idx = GetCharacterIndex("Griffin");
			if (idx >= 0)
			{
				sld = &characters[idx];
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}

			idx = GetCharacterIndex("CPBQuest_Solder");
			if (idx >= 0)
			{
				sld = &characters[idx];
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}

			idx = GetCharacterIndex("Spain_spy");
			if (idx >= 0)
			{
				sld = &characters[idx];
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.lifeday = 0;
			}

			trace("BetaTestFixesAll CapBloodLine fixes -> applied");
		}
	}

	// > корректные координаты Арубы
	worldMap.islands.Aruba.position.x = 166.772;
	worldMap.islands.Aruba.position.z = -578.37;
	worldMap.islands.Aruba.Shore67.position.x = 188.992;
	worldMap.islands.Aruba.Shore67.position.z = -582.122;
	worldMap.islands.Aruba.Shore68.position.x = 149.774;
	worldMap.islands.Aruba.Shore68.position.z = -590.987;
	trace("BetaTestFixesAll worldMap.islands.Aruba -> applied");

	// > слот колонии - приводим к виду незанятого слота, как в цикле инициализации InitColonies
	i = FindColony("BucaneerOutpost");
	if (i >= 0)
	{
		DeleteAttribute(&Colonies[i], "");
		Colonies[i].index = i;
		Colonies[i].id = "";
		Colonies[i].nation = "none";
		Colonies[i].commander = "-1";
		Colonies[i].island = "0";
		colonies[i].HeroOwn = false;
		colonies[i].isBought = false;
		colonies[i].from_sea = "";
		colonies[i].Default.BoardLocation = "";
		Colonies[i].visited = false;
		Colonies[i].money = 0;
		Colonies[i].reload_enable = true;
		Colonies[i].visible = true;
		Colonies[i].capturetime = "";
		Colonies[i].capture_day = "";
		Colonies[i].capture_month = "";
		Colonies[i].capture_year = "";
		Colonies[i].timerInfo = "0";
		Colonies[i].captureInfo = "0";
		Colonies[i].captureSuccesInfo = "0";
		Colonies[i].resquetime = "";
		Colonies[i].days_for_resque = "-1";
		Colonies[i].capture_flag = "0";
		Colonies[i].agressor = "-1";
		Colonies[i].loyality = "1";
		Colonies[i].disease = "0";
		Colonies[i].disease.time = "0";
		Colonies[i].num = 1;
		colonies[i].population = 0;
		colonies[i].colonists = 0;
		colonies[i].tax_rate = (MOD_SKILL_ENEMY_RATE);
		colonies[i].isBuild = 0;
		colonies[i].info.day = worldMap.date.day;
		colonies[i].info.month = worldMap.date.month;
		colonies[i].info.year = worldMap.date.year;
		colonies[i].ismaincolony = 0;
		colonies[i].fort = 3;
		colonies[i].jail = 1;
		colonies[i].type = "inhabited";
		trace("BetaTestFixesAll BucaneerOutpost -> colony slot " + i + " cleared");
	}

	// > вытаскиваем ПГГ, застрявших в заставе буканьеров
	for (i = 0; i < TOTAL_CHARACTERS; i++)
	{
		rPGG = &characters[i];
		if (!CheckAttribute(rPGG, "PGGAi")) continue;

		if (CheckAttribute(rPGG, "PGGAi.location.town") && rPGG.PGGAi.location.town == "BucaneerOutpost")
		{
			rPGG.PGGAi.location.town = PGG_FindRandomTownByNation(sti(rPGG.nation));
			trace("BetaTestFixesAll BucaneerOutpost -> relocate PGG from outpost: " + rPGG.id + " town -> " + rPGG.PGGAi.location.town);
		}

		if (CheckAttribute(rPGG, "PGGAi.location.town.back") && rPGG.PGGAi.location.town.back == "BucaneerOutpost")
		{
			rPGG.PGGAi.location.town.back = PGG_FindRandomTownByNation(sti(rPGG.nation));
			trace("BetaTestFixesAll BucaneerOutpost -> relocate PGG from outpost: " + rPGG.id + " town.back -> " + rPGG.PGGAi.location.town.back);
		}

		if (CheckAttribute(rPGG, "PGGAi.Task.Target") && rPGG.PGGAi.Task.Target == "BucaneerOutpost")
		{
			// > цель пути - свой же (уже перевыбранный) город, как в fallback PGG_FindTargetTown; если ПГГ сейчас вне города (town = "none"), цель перевыбираем по нации
			if (CheckAttribute(rPGG, "PGGAi.location.town") && FindColony(rPGG.PGGAi.location.town) >= 0)
				rPGG.PGGAi.Task.Target = rPGG.PGGAi.location.town;
			else
				rPGG.PGGAi.Task.Target = PGG_FindRandomTownByNation(sti(rPGG.nation));

			rPGG.PGGAi.Task.Target.days = 1;
			trace("BetaTestFixesAll BucaneerOutpost -> relocate PGG from outpost: " + rPGG.id + " Task.Target -> " + rPGG.PGGAi.Task.Target);
		}

		if (CheckAttribute(rPGG, "BackUp.town") && rPGG.BackUp.town == "BucaneerOutpost")
		{
			rPGG.BackUp.town = PGG_FindRandomTownByNation(sti(rPGG.nation));
			trace("BetaTestFixesAll BucaneerOutpost -> relocate PGG from outpost: " + rPGG.id + " BackUp.town -> " + rPGG.BackUp.town);
		}
	}

	// > метки "нанял экипаж", уехавшие в NullCharacter через CharacterFromID несуществующего тавернщика
	if (CheckAttribute(&NullCharacter, "CrewHired"))
	{
		DeleteAttribute(&NullCharacter, "CrewHired");
		trace("BetaTestFixesAll BucaneerOutpost: NullCharacter.CrewHired removed");
	}

	// > торговая книга - разведанные цены снятой колонии
	if (CheckAttribute(&NullCharacter, "PriceList.BucaneerOutpost"))
	{
		DeleteAttribute(&NullCharacter, "PriceList.BucaneerOutpost");
		trace("BetaTestFixesAll BucaneerOutpost: PriceList branch removed");
	}

	// > генератор "поручение капитана" - город перевыбираем той же логикой, что при генерации
	if (CheckAttribute(pchar, "GenQuest.CaptainComission.City1") && pchar.GenQuest.CaptainComission.City1 == "BucaneerOutpost")
	{
		pchar.GenQuest.CaptainComission.City1 = FindAlliedColonyForNationExceptColony(pchar.GenQuest.CaptainComission.City);
		trace("BetaTestFixesAll BucaneerOutpost: CaptainComission.City1 -> " + pchar.GenQuest.CaptainComission.City1);
	}

	// > Hold_GenQuest квест "наводка" на самом ГГ (после обыска капитана)
	if (CheckAttribute(pchar, "GenQuest.Hold_GenQuest"))
	{
		makearef(arHold, pchar.GenQuest.Hold_GenQuest);
		FixHoldGenQuestCities(arHold);
	}

	// > и на капитанах-носителях, которых ещё не обыскали
	for (i = 0; i < TOTAL_CHARACTERS; i++)
	{
		if (!CheckAttribute(&characters[i], "Hold_GenQuest")) continue;
		makearef(arHold, characters[i].Hold_GenQuest);
		FixHoldGenQuestCities(arHold);
	}

	// > корректно увеличиваем пул быстрых переходов у заставы
	DeleteAttribute(&objFastReloadTable, "table.BucaneerOutpost");
	makearef(curTable, objFastReloadTable.table.BucaneerOutpost);
	// дом ле Баска
	curTable.l1.pic = 4;
	curTable.l1.tex = 0;
	curTable.l1.location = "Bucaneer_outpost_townhall";
	// улица поселения
	curTable.l2.pic = 8;
	curTable.l2.tex = 0;
	curTable.l2.location = "Bucaneer_outpost";
	// бухта Бычий рог
	curTable.l3.pic = 10;
	curTable.l3.tex = 0;
	curTable.l3.location = "Shore66";
	trace("BetaTestFixesAll BucaneerOutpost: fast reload table -> applied");

    trace("Migration BetaTestFixesAll successfuly applied");
}

// > Перевыбор городов Hold_GenQuest, если целью успела стать застава
void FixHoldGenQuestCities(aref rQuest)
{
	if (CheckAttribute(rQuest, "ToCity") && rQuest.ToCity == "BucaneerOutpost")
	{
		// > FromCity выбирался союзным заставе, то есть пиратским - перевыбор от него держит города разными
		if (CheckAttribute(rQuest, "FromCity") && FindColony(rQuest.FromCity) >= 0)
			rQuest.ToCity = FindAlliedColonyForNationExceptColony(rQuest.FromCity);
		else
			rQuest.ToCity = FindAlliedColonyForNationExceptColony("Pirates");

		trace("BetaTestFixesAll BucaneerOutpost: Hold_GenQuest.ToCity -> " + rQuest.ToCity);
	}

	if (CheckAttribute(rQuest, "FromCity") && rQuest.FromCity == "BucaneerOutpost")
	{
		if (CheckAttribute(rQuest, "ToCity"))
			rQuest.FromCity = FindAlliedColonyForNationExceptColony(rQuest.ToCity);
		else
			rQuest.FromCity = FindAlliedColonyForNationExceptColony("Pirates");

		trace("BetaTestFixesAll BucaneerOutpost: Hold_GenQuest.FromCity -> " + rQuest.FromCity);
	}

	if (CheckAttribute(rQuest, "City") && rQuest.City == "BucaneerOutpost")
	{
		if (CheckAttribute(rQuest, "ToCity"))
			rQuest.City = rQuest.ToCity;
		else
			rQuest.City = FindAlliedColonyForNationExceptColony("Pirates");

		trace("BetaTestFixesAll BucaneerOutpost: Hold_GenQuest.City -> " + rQuest.City);
	}
}

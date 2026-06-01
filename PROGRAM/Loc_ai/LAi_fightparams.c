/*

	Возможные типы атаки attackType:
	"fast" быстрая атака
	"force" обычная
	"round" круговая
	"break" пробивающая блок
	"feint" атака после финта


*/

//--------------------------------------------------------------------------------
//Blade parameters
//--------------------------------------------------------------------------------

//Расчитать повреждение для персонажа
float LAi_CalcDamageForBlade(aref attack, aref enemy, string attackType, bool isBlocked)
{
	//Расчитываем повреждение от сабли
	float min = 10.0;
	float max = 10.0;

	//Коэфициент в зависимости от скилов
	float aSkill = LAi_GetCharacterFightLevel(attack);
	float eSkill = LAi_GetCharacterFightLevel(enemy);

	bool bPchar = IsMainCharacter(attack);
	bool bOfficer = IsOfficer(attack);

	if (CheckAttribute(attack, "equip.blade"))
	{
		ref rBlade = &Items[FindItem(attack.equip.blade)];
		min = stf(rBlade.dmg_min);
		max = stf(rBlade.dmg_max);
	}

	// evganat - пасха
	if (CheckAttribute(attack, "easter.damage"))
	{
		string sItem = GetCharacterEquipByGroup(attack, BLADE_ITEM_TYPE);
		if (CheckAttribute(attack, "easter.damage."+sItem))
		{
			switch (attack.easter.damage.(sItem))
			{
				case "1":	min += (min+max)*0.125;		max += (min+max)*0.125;		break;
				case "2":	min += (min+max)*0.25;		max += (min+max)*0.25;		break;
			}
		}
	}
	
	float bladeDmg = min + (max - min)*frandSmall(aSkill);
	
    if (aSkill < eSkill)
	{
		bladeDmg = bladeDmg * (1.0 + 0.7 * (aSkill - eSkill));
	}
	
	// Warship 27.08.09 Для сильных противников
	// Если долбить совсем сильных (хардкорные абордажи), то шансов взять шип будет меньше
	if (sti(enemy.Rank) > 50)
	{
		bladeDmg = bladeDmg * 45 / sti(enemy.Rank);
	}
	
	if (CheckAttribute(loadedLocation, "CabinType") && sti(enemy.index) == GetMainCharacterIndex())
	{
		bladeDmg = bladeDmg * (1.0 + stf(attack.rank)/100);
	}
	
	//Коэфициент в зависимости от удара
	float kAttackDmg = 1.0;
	
	// TODO оптимизация на ветку параметров
	switch (attackType)
	{
		case "fast":
			if (isBlocked) kAttackDmg = 0.0;
			else kAttackDmg = 0.7;
		break;

		case "force":
			if (isBlocked) kAttackDmg = 0.0;
			else kAttackDmg = 1.0;
		break;

		case "round":
			if (isBlocked) kAttackDmg = 0.0;
			else kAttackDmg = 0.6;
			if (CheckCharacterPerk(attack, "BladeDancer"))
			{
				// evganat - энциклопедия
				int iBonus = 0;
				if (!ENCYCLOPEDIA_DISABLED)
				{
					if (bPchar || bOfficer)
						iBonus += GetParamPageBonus("BladeDancer");
				}
				kAttackDmg = kAttackDmg * (1.3 + 0.01 * iBonus);
			}
		break;

		case "break":
			if (isBlocked) kAttackDmg = 1.0;
			else kAttackDmg = 3.0;
		break;
		
		case "feintc":  // фикс после изучения ядра //Атакующие продолжение финта
			if (isBlocked) kAttackDmg = 0.0;
			else kAttackDmg = 0.8;
		break;
		
		case "feint":
			if (isBlocked) kAttackDmg = 0.0;
			else kAttackDmg = 0.5;
		break;
	}
	
	if(kAttackDmg > 0)  // оптимизация boal
	{
		//Результирующий демедж
		float dmg = bladeDmg * kAttackDmg;
		
		if (CheckCharacterPerk(attack, "HardHitter") && CheckAttribute(enemy, "chr_ai.energy"))
		{
			enemy.chr_ai.energy = (stf(enemy.chr_ai.energy) * 0.9); //fix
		}
		
		if (MOD_SKILL_ENEMY_RATE < 5 && sti(enemy.index) == GetMainCharacterIndex())	
		{
			dmg = dmg * (4.0 + MOD_SKILL_ENEMY_RATE) * 0.1;
		}
		
		if (or(bPchar, bOfficer) && CharUseMusket(attack))
			dmg *= 0.3333333; // TO_DO: Приклады-штыки

		if (CheckCharacterPerk(attack, "BasicAttack"))
		{
			dmg *= 1.05;
		}

		// Урон по крабам +10% при наличии Акульего Зуба
		if (CheckCharacterItem(attack, "shark_tooth") && CheckAttribute(enemy, "model") && enemy.model == "crabBig")
		{
            dmg *= 1.1;
		}

		if (CheckCharacterPerk(attack, "InquisitionBlessing"))
		{
			if (CheckAttributeEx(enemy, "skeleton,indian,GhostShipCrew,monster,ghost,undead", "|"))
				dmg *= 1.2;
		}

		if (CheckCharacterPerk(enemy, "WitchCharm"))
		{
			if (CheckAttributeEx(attack, "skeleton,indian,GhostShipCrew,monster,ghost,undead", "|"))
				dmg *= 0.8;
		}

		return dmg;
	}
	
	return 0.0;
}

//Расчитать полученный опыт при ударе саблей
float LAi_CalcExperienceForBlade(aref attack, aref enemy, string attackType, bool isBlocked, float dmg)
{
	//Вычисляем полученый опыт
	float ra = 1.0;
	float re = 1.0;
	if(CheckAttribute(attack, "rank"))
	{
		ra = stf(attack.rank);
	}
	if(CheckAttribute(enemy, "rank"))
	{
		re = stf(enemy.rank);
	}
	if(ra < 1.0) ra = 1.0;
	if(re < 1.0) re = 1.0;
	dmg = dmg*((1.0 + re*0.5)/(1.0 + ra*0.5));

	switch(attackType)
	{
		case "break":
			if(isBlocked) dmg = dmg*1.1;
			else dmg = dmg*1.2;
            break;
		case "feint":
			dmg = dmg*1.5;
            break;
		case "feintc":
			dmg = dmg*1.5;
            break;
	}
	if (stf(enemy.chr_ai.hp) < dmg)
	{
       dmg = stf(enemy.chr_ai.hp);
	}
	return dmg;
}

//Энергия, необходимая для запуска действия
float LAi_CalcUseEnergyForBlade(aref character, string actionType)
{
	float energy = 0.0;
	
	switch (actionType)
	{
        case "fast":  energy = 10.0; break;
        case "force": energy = 7.0;  break;
        case "round": energy = 14.0; break;
        case "break": energy = 25.0; break;
      //case "feint": energy = 7.0;  break;
      //case "parry": energy = 20.0; break;
        case "feintc": energy = 7.0; break; // расход при успехе финта
        case "hit_parry": energy = 20.0; break; // boal fix эту энергию тратит не атакующий, а атакуемый в анимации fgt_hit_parry
	}

	if (energy > 0)  // оптимизация
	{
		float fSkill = LAi_GetCharacterFightLevel(character);
		fSkill = (1.0 - (0.3 * fSkill));
		energy = energy * fSkill * LAi_GetBladeEnergyType(character); // энергоёмкость от веса
	}
	
	return energy;
}

float Lai_UpdateEnergyPerDltTime(aref chr, float curEnergy, float dltTime)
{
	float dltep = LAI_DEFAULT_DLTEP;
	if (CheckAttribute(chr, "chr_ai.ep_dlt"))
		dltep = stf(chr.chr_ai.ep_dlt);

	if(CheckCharacterPerk(chr, "Energaiser")) // скрытый перк боссов и ГГ
	{
		dltep *= 1.5;
	}
	if(CheckCharacterPerk(chr, "Tireless")) 
	{
		// evganat - энциклопедия
		int iBonus = 0;
		if (!ENCYCLOPEDIA_DISABLED)
		{
			if (chr.chr_ai.type == LAI_TYPE_OFFICER || IsMainCharacter(chr))
				iBonus = GetParamPageBonus("Tireless");
		}
		dltep *= 1.15 + 0.01 * iBonus;
	}
    // честно все всем
	/*
	if(chr.id == pchar.id || chr.chr_ai.group == LAI_GROUP_PLAYER)
	{
		dltep = dltep * (1.0 + (0.025 * MOD_SKILL_ENEMY_RATE));
	}
	*/

	return curEnergy + dltTime * dltep;
}


//--------------------------------------------------------------------------------
//Gun parameters
//--------------------------------------------------------------------------------

//Расчитаем вероятность попадания
float LAi_GunCalcProbability(aref attack, aref enemy, float kDist, string sType)
{
	//Если близко, то попадём точно
	if(kDist >= 0.9) return 1.0;
	//Расчитаем вероятность на конце отрезка
	float pmin = 0.3;

 	if(CheckAttribute(attack, "chr_ai." + sType + ".accuracy")) // boal это меткость самого пистолета, а не скил!
	{
		pmin = stf(attack.chr_ai.(sType).accuracy);
	}
 	//Применим разброс от скила
	// boal -->
	float aSkill = LAi_GetCharacterGunLevel(attack);
	// boal <--

	pmin = pmin + 0.3*aSkill;

	//Вероятность попадания в текущей позиции
	float p = pmin + (1.0 - pmin)*(kDist/0.9);
 	//Учесть абилити
	if(IsCharacterPerkOn(attack, "GunProfessional"))
	{
		// evganat - энциклопедия
		int iBonus = 0;
		if (!ENCYCLOPEDIA_DISABLED)
		{
			if (attack.chr_ai.type == LAI_TYPE_OFFICER || IsMainCharacter(attack))
				iBonus = GetParamPageBonus("GunProfessional_accuracy");
		}
		p += 0.25 + 0.01 * iBonus;
	}
	else
	{
		if (sType == GUN_ITEM_TYPE)
		{
			if (IsCharacterPerkOn(attack, "GunAdvanced")) p += 0.15;
			else if (IsCharacterPerkOn(attack, "Gunman")) p += 0.1;
		}
	}

	if (sType == MUSKET_ITEM_TYPE && IsCharacterPerkOn(attack, "MusketsTraining")) p += 0.2;

	// путь будет больше 1 - тогда 100% попал
	return p;
}

//Получить повреждение от пистолета
float LAi_GunCalcDamage(aref attack, aref enemy, string sType, int nShots)
{
	//Расчитываем повреждение
	float min = 10.0;
	float max = 10.0;

	string sBullet = LAi_GetCharacterBulletType(attack, sType);
	bool bBoom = or(sBullet == "grenade", sBullet == "petard" && enemy.chr_ai.group != LAI_GROUP_PLAYER);

	if (StrHasStr(sBullet, "grenade,petard", 1))
		LaunchAmmoBlast(enemy, sBullet);

	if (CheckAttributeMass(attack, "chr_ai." + sType, "DmgMin_C,DmgMax_C,DmgMin_NC,DmgMax_NC,EnergyP_C,EnergyP_NC", "&"))
	{
		if (CheckAttribute(enemy, "cirassId"))
		{
			min = stf(attack.chr_ai.(sType).DmgMin_C);
			max = stf(attack.chr_ai.(sType).DmgMax_C);

			if (stf(attack.chr_ai.(sType).EnergyP_C) > 0.0 && bBoom)
				Lai_CharacterChangeEnergy(enemy, -stf(attack.chr_ai.(sType).EnergyP_C));
		}
		else
		{
			min = stf(attack.chr_ai.(sType).DmgMin_NC);
			max = stf(attack.chr_ai.(sType).DmgMax_NC);

			if (stf(attack.chr_ai.(sType).EnergyP_NC) > 0.0 && bBoom)
				Lai_CharacterChangeEnergy(enemy, -stf(attack.chr_ai.(sType).EnergyP_NC));
		}
	}
	else
	{
		if (CheckAttributeMass(attack, "chr_ai." + sType, "dmggunmin,dmggunmax", "&"))
		{
			min = stf(attack.chr_ai.(sType).dmggunmin);
			max = stf(attack.chr_ai.(sType).dmggunmax);
		}
	}

	//Учитываем скилы
	float aSkill = LAi_GetCharacterGunLevel(attack);
	float eSkill = LAi_GetCharacterLuckLevel(enemy); // good luck

	float dmg = min + (max - min)*frandSmall(aSkill);
	dmg *= nShots;
	//Модифицировать повреждение от pistol с учетом скилов
    if(aSkill < eSkill)
	{
		dmg = dmg * (1.0 + 0.7 * (aSkill - eSkill));
	}
	// упрощение игры новичкам 
	/*if (MOD_SKILL_ENEMY_RATE == 1 && CheckAttribute(enemy, "chr_ai.group"))	
	{
		if (enemy.chr_ai.group == LAI_GROUP_PLAYER) 
		{
			dmg = dmg * 0.5;
		}
	}   */
	if (MOD_SKILL_ENEMY_RATE < 5 && sti(enemy.index) == GetMainCharacterIndex())	
	{
		dmg = dmg * (4.0 + MOD_SKILL_ENEMY_RATE) / 10.0;
	}

	if (IsCharacterPerkOn(attack, "Shoottech"))
		dmg = dmg * 1.1;

	if (CheckCharacterPerk(attack, "DevilsEye") && rand(99) < 10)
	{
		dmg = dmg * 2.0;
		Log_Info(XI_ConvertString("Critical Shot"));
	}

	//урон по крабам +10% при наличии Акульего Зуба
    if (CheckCharacterItem(attack, "shark_tooth") && CheckAttribute(enemy, "model") && enemy.model == "crabBig")
    {
        dmg = dmg * 1.1;
    }

	if (CheckCharacterPerk(attack, "InquisitionBlessing"))
	{
		if (CheckAttributeEx(enemy, "skeleton,indian,GhostShipCrew,monster,ghost,undead", "|"))
			dmg = dmg * 1.2;
	}

	if (CheckCharacterPerk(enemy, "WitchCharm"))
	{
		if (CheckAttributeEx(attack, "skeleton,indian,GhostShipCrew,monster,ghost,undead", "|"))
			dmg = dmg * 0.8;
	}

	return dmg;
}

//Расчитать полученный опыт при попадании из пистолета - evganat - переделал
float LAi_GunCalcDamageExperience(aref attack, aref enemy, float dmg, bool isHeadShot)
{
	float hp = stf(enemy.chr_ai.hp);
	if(dmg > hp) dmg = hp;
	float exp = dmg * 0.08;
	if(isHeadShot) exp *= 1.5;
	return LAi_GunCalcExperience(attack, enemy, exp);
}

float LAi_GunCalcKillExperience(aref attack, aref enemy)
{
	return LAi_GunCalcExperience(attack, enemy, 20.0);
}

//Расчитать полученный опыт при попадании из пистолета
float LAi_GunCalcExperience(aref attack, aref enemy, float dmg)
{
	int attackRank = sti(attack.rank);
	int enemyRank = sti(enemy.rank);
	float kRank = 1.0 + (enemyRank - attackRank) * 0.1;
	if(kRank > 1.6)
		kRank = 1.6;
	else
	{
		if(kRank < 0.4)
			kRank = 0.4;
	}
	dmg *= kRank;
	
	return dmg;
}

//Расчитаем текущую скорость перезарядки пистолета
float LAi_GunReloadSpeed(aref chr, string sType)
{
	//Получим текущее состояние скорости зарядки
	float charge_dlt = LAI_DEFAULT_DLTCHRG;
	if(CheckAttribute(chr, "chr_ai." + sType + ".charge_dlt"))
	{
		charge_dlt = stf(chr.chr_ai.(sType).charge_dlt);
	}
	//Модифицируем скилом
	// boal -->
	//float skill = LAi_GetCharacterFightLevel(chr);
	float skill = LAi_GetCharacterGunLevel(chr);
	// boal <--

	charge_dlt = charge_dlt*(1.0 + 0.3*skill);//boal
	//Учтём абилити
	if (IsCharacterPerkOn(chr, "GunProfessional"))
	{
		// evganat - энциклопедия
		int iBonus = 0;
		if (!ENCYCLOPEDIA_DISABLED)
		{
			if (IsMainCharacter(chr) || and(CheckAttribute(chr, "chr_ai.type" && chr.chr_ai.type == LAI_TYPE_OFFICER), true))
				iBonus = GetParamPageBonus("GunProfessional_charge");
		}
		charge_dlt = charge_dlt * (1.25 + 0.01 * iBonus);
	}
	else
	{
		if (sType == GUN_ITEM_TYPE)
		{
			if (IsCharacterPerkOn(chr, "GunAdvanced"))
				charge_dlt = charge_dlt*1.15;
			else
			{
				if (IsCharacterPerkOn(chr, "Gunman"))
					charge_dlt = charge_dlt*1.1;
			}
		}
	}

	if (sType == MUSKET_ITEM_TYPE && IsCharacterPerkOn(chr, "MusketsTraining"))
	{
		charge_dlt = charge_dlt*1.2;
	}

	return charge_dlt;
}

//--------------------------------------------------------------------------------
//Calculate total
//--------------------------------------------------------------------------------

//Начисление повреждений при атаке в ближнем бою
void LAi_ApplyCharacterAttackDamage(aref attack, aref enemy, string attackType, bool isBlocked)
{
	//Если неубиваемый, то нетрогаем его
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}
	//Нарвалы и Касперы мирняку урон не причиняют
	if (enemy.chr_ai.group == LAI_GROUP_TmpEnemy && or(attack.chr_ai.group == "LSC_NARVAL", attack.chr_ai.group == "LSC_CASPER"))
        return;
	
	//Вычисляем повреждение
	float dmg = LAi_CalcDamageForBlade(attack, enemy, attackType, isBlocked);
	
	int iBonus = 0;	// evganat - энциклопедия
	float critical = 0.0; //Вычисляем крит
	ProcessCriticalDamageForBlades(attack, enemy, attackType, isBlocked, &critical);

	float kDmg = 1.0;
	if(IsCharacterPerkOn(attack, "Rush"))
	{
		kDmg = 1.5;
	}
	
	dmg *= kDmg;
	
	if (CheckAttribute(attack, "MultiFighter")) // мультифайтер
	{
		dmg *= stf(attack.MultiFighter);
	}
	
	if(CheckCharacterPerk(attack, "Duelist") && bDuelModif(attack))
	{
		dmg *= 1.05;
	}
	
	if(CheckCharacterPerk(enemy, "Duelist") && bDuelModif(enemy))
	{
		dmg *= 0.95;
	}
	
	//Аттака своей группы
	bool noExp = false;
	if(CheckAttribute(attack, "chr_ai.group") && CheckAttribute(enemy, "chr_ai.group"))
	{
		if(attack.chr_ai.group == enemy.chr_ai.group)
		{
			dmg = 0.0;
			critical = 0.0;
			noExp = true;
		}
	}
	
	if(critical > 0.0)
	{
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 5);
        if(ShowCharString())
        {
            Log_Chr(enemy, XI_ConvertString("Critical Hit"));
        }
        else
        {
            if(sti(attack.index) == GetMainCharacterIndex())
            {
                Log_Info(XI_ConvertString("Critical Hit"));
            }
        }
	}

	if (IsCharacterPerkOn(enemy, "SwordplayProfessional"))
	{
		// evganat - энциклопедия
		if (!ENCYCLOPEDIA_DISABLED)
		{
			if (enemy.chr_ai.type == LAI_TYPE_OFFICER || IsMainCharacter(enemy))
				iBonus = GetParamPageBonus("SwordplayProfessional_defence");
		}
		kDmg = 0.7 - 0.01 * iBonus;
	}
	else if (IsCharacterPerkOn(enemy, "AdvancedDefense")) kDmg = 0.8;
	else if (IsCharacterPerkOn(enemy, "BasicDefense")) kDmg = 0.9;
	else kDmg = 1.0;

	// ГПК 1.2.3
	dmg = dmg * kDmg;
	dmg = dmg * (1 + critical); //dmg + critical;
	if(CheckAttribute(enemy, "cirassId"))
	{
		dmg = dmg * (1.0 - stf(Items[sti(enemy.cirassId)].CirassLevel));
	}
	if(dmg > 0.0)
	{
		//Наносим повреждение
		LAi_ApplyCharacterDamage(enemy, MakeInt(dmg + 0.5), "fight");
		//Проверим на смерть
		LAi_CheckKillCharacter(enemy);
		//проверим на отравление
		MakePoisonAttackCheckSex(enemy, attack);

	}
	//Есть ли оружие у цели
	bool isSetBalde = (CheckAttribute(enemy, "equip.blade") == true);//(SendMessage(enemy, "ls", MSG_CHARACTER_EX_MSG, "IsSetBalde") != 0);
	//Начисляем опыта
	float exp = LAi_CalcExperienceForBlade(attack, enemy, attackType, isBlocked, dmg);
	/*if(LAi_grp_alarmactive == false)
	{
		if(CheckAttribute(pchar, "sneak.success"))
		{
			if(sti(pchar.sneak.success) == 1)
			{
				pchar.sneak.success = 0;
			}
		}
	} */
	if(LAi_IsDead(enemy))
	{
		//Начислим за убийство
		// boal  check skill -->
		float ra = 1.0;
	    float re = 1.0;
	    if(CheckAttribute(attack, "rank"))
	    {
	       ra = stf(attack.rank);
	    }
	    if(CheckAttribute(enemy, "rank"))
	    {
	       re = stf(enemy.rank);
	    }
        AddCharacterExpToSkill(attack, LAi_GetBladeFencingType(attack), makefloat(10.0 + ((1 + re) / (1+ra))*6.5));
        AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
        AddCharacterExpToSkill(attack, SKILL_FORTUNE, 1);
        AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
        // boal <--
        // boal statistic info 17.12.2003 -->
        Statistic_KillChar(attack, enemy, "_s");
        // boal statistic info 17.12.2003 <--
        LAi_SetResultOfDeath(attack, enemy, isSetBalde);
	}
	if(!isSetBalde)
	{
		exp = 0.0;
	}
	
	if (!noExp)
    {
        //AddCharacterExp(attack, MakeInt(exp*0.5 + 0.5));
        AddCharacterExpToSkill(attack, LAi_GetBladeFencingType(attack), Makefloat(exp*0.2));
    }
	
}
//boal 19.09.05 -->
void LAi_SetResultOfDeath(ref attack, ref enemy, bool isSetBalde)
{
    if (sti(attack.index) == GetMainCharacterIndex())
    {
		if (GetRelation2BaseNation(sti(enemy.nation)) == RELATION_ENEMY)
		{
			if (!isSetBalde)
			{
				LAi_ChangeReputation(attack, -1);   // TODO
				if (rand(1) && CheckAttribute(enemy, "City"))
				{
					ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 1);
				}
			}
		}
		else
		{
			if (CheckAttribute(enemy, "City"))
			{
				ChangeCharacterHunterScore(attack, NationShortName(sti(enemy.nation)) + "hunter", 2);
			}
		}
		// обида нации на разборки в городе boal 19.09.05
  		if (CheckAttribute(enemy, "City"))
		{
			// нужна проверка на дуэли и квесты
			if (GetSummonSkillFromName(attack, SKILL_SNEAK) < rand(140)) // скрытность
			{
			    SetNationRelation2MainCharacter(sti(enemy.nation), RELATION_ENEMY);
		    }
		}
		
		if (HasStr(enemy.id, "SkladMan_"))
		{
			if (!CheckAttribute(&TEV, "SkladManIsDead"))
				TEV.SkladManIsDead = "none";
			
			if (!HasStr(TEV.SkladManIsDead, enemy.id))
				TEV.SkladManIsDead = TEV.SkladManIsDead + "," + enemy.id;
		}
		// Jason: репутация индейцев
		if (HasStr(enemy.model, "canib"))
        {
            ChangeIndianRelation(-0.1);
        }
		if (HasStr(enemy.model, "miskito"))
		{
			ChangeIndianRelation(-0.5);
		}
	}
}
// boal <--

//Начисление повреждений при попадании
void LAi_ApplyCharacterFireDamage(aref attack, aref enemy, float kDist, float fAimingTime, bool isHeadShot, int nShots)
{
	//Если неубиваемый, то нетрогаем его
	if(CheckAttribute(enemy, "chr_ai.immortal"))
	{
		if(sti(enemy.chr_ai.immortal) != 0)
		{
			return;
		}
	}

	// Чем стреляли?
	string sType;
	if(!CharUseMusket(attack)) sType = GUN_ITEM_TYPE;
	else sType = MUSKET_ITEM_TYPE;

	//Вероятность поподания
	float p = LAi_GunCalcProbability(attack, enemy, kDist, sType);
	//Если промахнулись, то выйдем
	if(rand(10000) > p*10000) return;	  
	// boal брон работает всегда, а не токо в блоке 23.05.2004 -->
	if(CheckAttribute(enemy, "cirassId"))
	{
        if(rand(1000) < stf(Items[sti(enemy.cirassId)].CirassLevel)*500) return;
	}
	// boal 23.05.2004 <--
	//Начисляем повреждение
	float damage = LAi_GunCalcDamage(attack, enemy, sType, nShots);
	
	// evganat - прицеливание
	if(fAimingTime >= 0.0)
	{
		float fMaxTime = MAX_AIMING_TIME;
		damage *= Bring2Range(0.75, 1.5, 0.0, fMaxTime, fAimingTime);
	}

	//Аттака своей группы
	bool noExp = false;
	if(CheckAttribute(attack, "chr_ai.group"))
	{
		if(CheckAttribute(enemy, "chr_ai.group"))
		{
			if(attack.chr_ai.group == enemy.chr_ai.group)
			{
				damage = 0.0;
				noExp = true;
			}
		}
	}
	
	if(IsMainCharacter(enemy))
		isHeadShot = false;
	if(isHeadShot)
	{
		damage *= 2;
//		Log_Info("Хэдшот!!!");
		if(!CheckAttribute(enemy, "chr_ai.getheadshot"))
        {
            enemy.chr_ai.getheadshot = 0.1;
            if(ShowCharString() && IsMainCharacter(attack))
            {
                Log_Chr(enemy, XI_ConvertString("HeadShot"));
            }
            else
            {
                if(IsMainCharacter(attack)) log_info(XI_ConvertString("HeadShot"));
            }
        }
	}
	if(damage > 0.0)
	{
		if (CheckCharacterPerk(attack, "StunningShot"))
			Lai_CharacterChangeEnergy(enemy, -(10 + rand(5)));
		
		//Rosarak. Звуки попадания пуль теперь здесь; TODO: Доработать их и разделить по полам
		string Sound = GetSexCase(enemy, "bullethit", "bullethit", "s_manhit");
		if(Sound != "") LAi_CharacterPlaySound(enemy, Sound); //Пустая строка у животных
		LAi_ApplyCharacterDamage(enemy, MakeInt(damage + 0.5), "fire");	
		//Проверим на смерть
		LAi_CheckKillCharacter(enemy);
	}
	//Есть ли оружие у цели
	bool isSetBalde = (CheckAttribute(enemy, "equip.blade") == true);//(SendMessage(enemy, "ls", MSG_CHARACTER_EX_MSG, "IsSetBalde") != 0);
	//Начисляем опыт
	float exp = LAi_GunCalcDamageExperience(attack, enemy, damage, isHeadShot);
	/*if(LAi_grp_alarmactive == false)
	{
		if(CheckAttribute(pchar, "sneak.success"))
		{
			if(sti(pchar.sneak.success) == 1)
			{
				pchar.sneak.success = 0;
			}
		}
	}  */
	if(LAi_IsDead(enemy))
	{
		//Начислим за убийство
		float expKill = LAi_GunCalcKillExperience(attack, enemy);
		AddCharacterExpToSkill(attack, SKILL_PISTOL, expKill);
		AddCharacterExpToSkill(attack, SKILL_DEFENCE, 1);
		AddCharacterExpToSkill(attack, SKILL_FORTUNE, 2);
		AddCharacterExpToSkill(attack, SKILL_LEADERSHIP, 1);
		// boal statistic info 17.12.2003 -->
        Statistic_KillChar(attack, enemy, "_g");
        // boal statistic info 17.12.2003 <--
        
        //Начислим за убийство
  		LAi_SetResultOfDeath(attack, enemy, isSetBalde);
  		if(fAimingTime >= 0.0)	// после убийства на секунду меняем прицел
			pchar.chr_ai.kill_timer = BLI_KILL_MARKER_TIMER;
	}
	if(!isSetBalde)
	{
		//LAi_ChangeReputation(attack, -1);
		exp = 0.0;
	}
	if(!noExp)
    {
        AddCharacterExpToSkill(attack, SKILL_PISTOL, Makefloat(exp*0.85));
    }
}

//--------------------------------------------------------------------------------
//Параметры NPC
//--------------------------------------------------------------------------------

float npc_return_tmp;
bool npc_return_tmpb;

//Атаки
//Скорость нарастания вероятности атаки в секунду  p > 0
#event_handler("NPC_Event_GetAttackActive","LAi_NPC_GetAttackActive");
float LAi_NPC_GetAttackActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	npc_return_tmp = 0.3 + level*0.7;
	npc_return_tmp = npc_return_tmp + 0.1;
	return npc_return_tmp;
}

//Вес выбора удара "fast", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightFast","LAi_NPC_GetAttackWeightFast");
float LAi_NPC_GetAttackWeightFast()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Вес выбора удара "force", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightForce","LAi_NPC_GetAttackWeightForce");
float LAi_NPC_GetAttackWeightForce()
{
	aref chr = GetEventData();
	npc_return_tmp = 50.0;
	npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Вес выбора удара "round", 0 - никогда не выбирать, если врагов <3 то удар не выбирается
#event_handler("NPC_Event_GetAttackWeightRound","LAi_NPC_GetAttackWeightRound");
float LAi_NPC_GetAttackWeightRound()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	npc_return_tmp = npc_return_tmp * (0.8 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Вес выбора удара "break", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightBreak","LAi_NPC_GetAttackWeightBreak");
float LAi_NPC_GetAttackWeightBreak()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0;
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Вес выбора удара "feint", 0 - никогда не выбирать
#event_handler("NPC_Event_GetAttackWeightFeint","LAi_NPC_GetAttackWeightFeint");
float LAi_NPC_GetAttackWeightFeint()
{
	aref chr = GetEventData();
	npc_return_tmp = 10.0; //30 boal fix
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Прараметры защиты
//Вероятность желания защитится - кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetDefenceActive","LAi_NPC_GetAttackDefence");
float LAi_NPC_GetAttackDefence()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterFightLevel(chr);
	//npc_return_tmp = 0.05 + level*0.4;
	npc_return_tmp = 0.3 + level*0.35;
	/*if (!iArcadeFencingAI)	// TODO
	{
		npc_return_tmp = npc_return_tmp + 0.2;
	}*/
	return npc_return_tmp;
}

// boal 20.01.08 коммент - забавно, что спустя два года, понал как и что с вероятностями. Они все приводятся к 0-1 от веса общей суммы, то есть фактически умножение на сложность или цифры распределяют сумму по другим акшенам, а не усиливают этот
// Экшены идут парами - все атаки и защита (блок + пари)
//Вес выбора блока, 0 - никогда не выбирать
#event_handler("NPC_Event_GetDefenceWeightBlock","LAi_NPC_GetDefenceWeightBlock");
float LAi_NPC_GetDefenceWeightBlock()
{
	aref chr = GetEventData();
	npc_return_tmp = 80.0;
	npc_return_tmp = npc_return_tmp * (0.5 + (0.05 * MOD_SKILL_ENEMY_RATE));   // boal
	return npc_return_tmp;
}

//Вес выбора  паррирования, 0 - никогда не выбирать
//кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetDefenceWeightParry","LAi_NPC_GetDefenceWeightParry");
float LAi_NPC_GetDefenceWeightParry()
{
	aref chr = GetEventData();
	npc_return_tmp = 20.0; // 40 boal
	npc_return_tmp = npc_return_tmp * (0.6 + (0.1 * MOD_SKILL_ENEMY_RATE));
	return npc_return_tmp;
}

//Разрешён ли отскок
#event_handler("NPC_Event_EnableRecoil","LAi_NPC_EnableRecoil");
bool LAi_NPC_EnableRecoil()
{
	aref chr = GetEventData();
	npc_return_tmpb = true;
	return npc_return_tmpb;
}


//Параметры стрельбы
//Вероятность желания выстрелить - кубик с такой вероятностью кидается 2 раза в секунду
#event_handler("NPC_Event_GetFireActive","LAi_NPC_GetFireActive");
float LAi_NPC_GetFireActive()
{
	aref chr = GetEventData();
	float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmp = 0.001 + level*0.06;
	// boal наши офицеры пулят из всех стволов -->
	if (chr.chr_ai.group == LAI_GROUP_PLAYER)
	{
        npc_return_tmp = 0.38 + npc_return_tmp;
	}
	else
	{
	// boal наши офицеры пулят из всех стволов <--
		if (CheckAttribute(chr, "SuperShooter"))
		{
			npc_return_tmp = npc_return_tmp + 0.4 * MOD_SKILL_ENEMY_RATE / 10.0;
		}
		else
		{
			npc_return_tmp = npc_return_tmp + 0.1 * MOD_SKILL_ENEMY_RATE / 10.0;
		}
	}
	//if (npc_return_tmp > 0.5) npc_return_tmp = 0.5;
	
	return npc_return_tmp;
}

//Разрешён ли выстрел
#event_handler("NPC_Event_EnableFire","LAi_NPC_EnableFire");
bool LAi_NPC_EnableFire()
{
	aref chr = GetEventData();
	return   true;
	/*float level = LAi_GetCharacterGunLevel(chr);
	npc_return_tmpb = false;
	if(!iArcadeFencingAI)
	{
		level = level + 0.02;
	}
	else
	{
		level = level - 0.01;
	}
	if(level > 0.1) npc_return_tmpb = true;
	return npc_return_tmpb;    */
}

//Разрещён ли временный перевыбор цели среди ближних - опрашивается постоянно
#event_handler("NPC_Event_AdaptiveTargetSelect","LAi_NPC_AdaptiveTargetSelect");
bool LAi_NPC_AdaptiveTargetSelect()
{
	aref chr = GetEventData();
	if(chr.chr_ai.type == LAI_TYPE_ACTOR) npc_return_tmpb = false;
	else npc_return_tmpb = true;
	return npc_return_tmpb;
}


//--------------------------------------------------------------------------------
//Work
//--------------------------------------------------------------------------------

#event_handler("Location_CharacterSGFire","LAi_Location_CharacterSGFire");
void LAi_Location_CharacterSGFire()
{
	aref attack = GetEventData();
	aref enemy = GetEventData();
	float kDmg = GetEventData();
	if(LAi_IsDead(enemy)) return;
	//Реакция груп на атаку
	LAi_group_Attack(attack, enemy);
	//AddCharacterExp(attack, 100*kDmg);
	//Наносим повреждение
	LAi_ApplyCharacterDamage(enemy, MakeInt((5 + rand(5))*kDmg), "fire");
	//Проверим на смерть
	LAi_CheckKillCharacter(enemy);
}

#event_handler("ChrAttackAction", "LAi_ChrAttackAction");
bool LAi_ChrAttackAction()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float curEnergy = Lai_CharacterGetEnergy(attack);
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType);
	if(curEnergy >= needEnergy)
	{
		npc_return_tmpb = true;
	}
	else
	{
		npc_return_tmpb = false;
	}
	if (CheckParryTutorial(attack, attackType))
	{
		npc_return_tmpb = false; // туториал покажем, но атаки не будет)
	}
	return npc_return_tmpb;
}

#event_handler("ChrFgtActApply", "LAi_ChrFightActionApply");
void LAi_ChrFightActionApply()
{
	aref attack = GetEventData();
	string attackType = GetEventData();
	float needEnergy = LAi_CalcUseEnergyForBlade(attack, attackType);
	Lai_CharacterChangeEnergy(attack, -needEnergy);
}

//Получить относительную затрачиваемую энергию
#event_handler("NPC_Event_GetActionEnergy","LAi_NPC_GetActionEnergy");
float LAi_NPC_GetActionEnergy()
{
	aref chr = GetEventData();
	string act = GetEventData();
	npc_return_tmp = LAi_CalcUseEnergyForBlade(chr, act) / LAi_GetCharacterMaxEnergy(chr);  // boal
	return npc_return_tmp;
}

//Необходимо вернуть максимально быстро нормализованое значение жизни
#event_handler("NpcEvtHP", "LAi_NPC_EvtGetHP");
float LAi_NPC_EvtGetHP()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelHP(chr);
	return npc_return_tmp;
}


//Необходимо вернуть максимально быстро нормализованое значение энергии
#event_handler("NpcEvtEny", "LAi_NPC_EvtGetEny");
float LAi_NPC_EvtGetEny()
{
	aref chr = GetEventData();
	npc_return_tmp = LAi_GetCharacterRelEnergy(chr);
	return npc_return_tmp;
}

//Вероятность стана после удара, опрашивается единожды при загрузке персонажа
#event_handler("NPC_Event_StunChance","LAi_NPC_StunChance");
int LAi_NPC_StunChance()
{
	aref chr = GetEventData();
	int npc_return_tmpi = 100;
	if(CheckCharacterPerk(chr, "SwordplayProfessional"))
	{
		npc_return_tmpi = 40;
	}
	else 
	{
		if(CheckCharacterPerk(chr, "AdvancedDefense"))
		{
			npc_return_tmpi = 70;
		}
		else
		{	
			if(CheckCharacterPerk(chr, "BasicDefense"))
			{
				npc_return_tmpi = 80;
			}
			else
			{
				npc_return_tmpi = 90;
			}
		}	
	}		
	return npc_return_tmpi;
}

// EvgAnat - требование энергии для отскока -->
bool bIsRecoilEnableWithoutEnergy = true; // можно ли выполнять отскоки при недостатке энергии (это не влияет на расход энергии)

float SprintStartEnergyReq = 15.0;

#event_handler("ChrCheckEnergy", "LAi_Chr_CheckEnergy");
bool LAi_Chr_CheckEnergy()
{
	aref chr = GetEventData();
	string action = GetEventData(); // "recoil" - отскок назад, "strafe_l" и "strafe_r" - отскоки влево и вправо
	bool res = false;
	float needEnergy = 0.0;
	switch(action)
	{
		case "sprint":		needEnergy = SprintStartEnergyReq;	break;
		case "recoil":		needEnergy = 2.0;	break;
		case "strafe_l":	needEnergy = 2.0;	break;
		case "strafe_r":	needEnergy = 2.0;	break;
	}
	if(CheckAttribute(chr, "exhausted"))
		DeleteAttribute(chr, "exhausted");
	if(CheckAttribute(chr, "cirassId"))
	{
		needEnergy += stf(Items[sti(chr.cirassId)].Weight)*0.1;
	}
	if (stf(chr.chr_ai.energy) >= needEnergy)
	{	
		res = true;
		if(action != "sprint")
			Lai_CharacterChangeEnergy(chr, -needEnergy);
	}
	else
	{
		if (action != "sprint" && bIsRecoilEnableWithoutEnergy)
		{
			res = true;
			Lai_CharacterChangeEnergy(chr, -needEnergy);
			chr.exhausted = true;
		}
	}
	return res;
}
// EvgAnat - требование энергии для отскока <--

// EvgAnat - включено ли уклонение от выстрела для нпс -->
#event_handler("NPC_IsDodgeEnabled", "LAi_Chr_IsDodgeEnabled");
bool LAi_Chr_IsDodgeEnabled()
{
	return true;
}
// EvgAnat - включено ли уклонение от выстрела для нпс <--

// EvgAnat - уклонение от выстрела -->
#event_handler("Check_ChrHitFire", "LAi_Chr_CheckHitFire");
int LAi_Chr_CheckHitFire() // 0 - не попал, 1 - попал
{
	aref shooter = GetEventData(); // стрелок
	aref target = GetEventData(); // цель
	bool isRecoil = GetEventData(); // находится ли цель в окне уклонения 
	float kDist = GetEventData(); // коэффициент дальности, равный 1-d/25; k(0)=1; k(10)=0.6; k(25)=0
	int res = 1;
	float r = Random();
	float chance = 1.0;
	if (CheckAttribute(target, "exhausted"))
		chance = 0.5;
	if (isRecoil && r <= chance)
	{
		res = 0;
		if (shooter.index == GetMainCharacterIndex())
		{
		    if(ShowCharString())
            {
                Log_Chr(target, StringFromKey("InfoMessages_82"));
            }
            else
            {
                Log_SetStringToLog(StringFromKey("InfoMessages_82"));
            }
		}
	}
	return res;
}
// EvgAnat - уклонение от выстрела <--

// EvgAnat - уклонение от атаки -->
#event_handler("Check_ChrHitAttack", "LAi_Chr_CheckHitAttack");
bool LAi_Chr_CheckHitAttack() // попала ли атака
{
	aref attack = GetEventData();
	aref enemy = GetEventData();
	bool isRecoil = GetEventData(); // находится ли цель в окне уклонения
	bool res = true;
	float r = Random();
	float chance = 1.0;
	if (CheckAttribute(enemy, "exhausted"))
		chance = 0.5;
	if (isRecoil && r <= chance)
		res = false;	
	return res;
}
// EvgAnat - уклонение от атаки <--

// EvgAnat - вероятность желания уклониться от выстрела у нпс -->
#event_handler("NPC_IsDodge", "LAi_NPC_IsDodge");
bool LAi_NPC_IsDodge() // true - уклоняется, false - не уклоняется
{
	aref chr = GetEventData();
	float r = Random();
	bool res = false;
	//Log_SetStringToLog("1. " + GetFullName(chr) + " ищет в себе желание уклониться")
	if (CheckAttribute(chr, "canDodge") || chr.chr_ai.type == LAI_TYPE_OFFICER)
	{
		//Log_SetStringToLog("2. " + GetFullName(chr) + " умеет уклоняться");
		if (r <= 0.25)
		{
			//Log_SetStringToLog("3. " + GetFullName(chr) + " желает уклониться");
			res = true;
		}
	}
	return res;
}
// EvgAnat - вероятность желания уклониться от выстрела у нпс <--

// EvgAnat - дальность отскока и стрейфа -->
#event_handler("GetCharacterRecoilDistance", "LAi_GetRecoilDistance");
float LAi_GetRecoilDistance()
{
	aref chr = GetEventData();
	string aType = GetEventData();
	float res = 2.0;
	switch(aType)
	{
		case "recoil":
			res = 7.0; // по умолчанию 2.0
		break;
		case "strafe":
			res = 10.0; // по умолчанию 15.0
		break;
	}
	return res;
}
// EvgAnat - дальность отскока и стрейфа <--

//Rosarak. Для отложенного возврата запрета на обнажение оружия
void FightDisable()
{
	LAi_LocationFightDisable(&Locations[FindLocation(TEV.noFight.loc)], true);
	DeleteAttribute(&TEV, "noFight");
	FightDisable_Forced();
}

//Rosarak. Оружие в ножны без возможности задоджить выстрелом или анимацией
void FightDisable_Forced()
{
	if(SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", false))
		LAi_MethodDelay("FightDisable_Forced", 0.1);
}

bool bDuelModif(aref chr)
{
	int countEnemy = 0;
	int num = FindNearCharacters(chr, 15.0, -1.0, -1.0, 0.001, false, true);
	
	for(int i = 0; i < num; i++)
	{
		int idx = sti(chrFindNearCharacters[i].index);
		if(LAi_group_IsEnemy(chr, &Characters[idx])) countEnemy++;
		if(countEnemy > 1) return false;
	}
	
	return true;
}

// AlexBlade - Вынес вычисления в отдельный метод
void ProcessCriticalDamageForBlades(aref attack, aref enemy, string attackType, bool isBlocked, float critical)
{
	critical = 0.0;
	
	int iBonus = 0;	// evganat - энциклопедия
	// ГПК 1.2.3
	if (IsCharacterPerkOn(attack, "SwordplayProfessional"))
	{
		// evganat - энциклопедия
		if (!ENCYCLOPEDIA_DISABLED)
		{
			if (attack.chr_ai.type == LAI_TYPE_OFFICER || IsMainCharacter(attack))
				iBonus = GetParamPageBonus("SwordplayProfessional_critical");
		}
		if (rand(99) < 15 + iBonus)
		{
			critical = 1.0;//LAi_GetCharacterMaxHP(enemy)*0.30;
		}
	}
	else if (IsCharacterPerkOn(attack, "CriticalHit"))
	{
		if (rand(99) < 5) critical = 1.0; //LAi_GetCharacterMaxHP(enemy)*0.20;
	}
	
	// Дайнслейф - 100% крит при первом силовом ударе
	bool hasAttackAbsoluteCrit = false;
	if (LAi_HasCharacterActiveBlade(attack, "vikingHeroSword"))
	{
		if (attackType == "break" && CheckAttribute(attack, "FightParams.NoFirstBreakAttack")) {
			Log_TestInfo("Critical from VikingSword");
			hasAttackAbsoluteCrit = true;
			critical = 1.0;
			DeleteAttribute(&attack, "FightParams.NoFirstBreakAttack");
		}
	}
	
	bool isCritImpossible = isBlocked || CheckAttribute(enemy, "cirassId"); // если кираса или блок, то критикал невозможен
	if(!hasAttackAbsoluteCrit && isCritImpossible)
	{
		critical = 0;
	}
}

// evganat - прицеливание - обновление
#event_handler("AimingUpdate", "AimingUpdate");
void AimingUpdate()
{
	float fTime = GetEventData();
	int isFindedTarget = GetEventData();
	aref target = GetEventData();
	BI_CrosshairRefresh(fTime, isFindedTarget, target);
}

#event_handler("GetShardsQuantity","GetShardsQuantity");
int GetShardsQuantity()
{
	aref chr = GetEventData();

	string sType;
	if(CharUseMusket(chr)) sType = MUSKET_ITEM_TYPE;
	else sType = GUN_ITEM_TYPE;

	string sBullet = LAi_GetCharacterBulletType(chr, sType);
	if(IsBulletGrape(sBullet))
	{
		//chr.chr_ai.(sType).grape.test_lights = 1;
		if(sBullet == "grapeshot")
		{
			chr.chr_ai.(sType).grape.shards = 36;
			chr.chr_ai.(sType).grape.width = 6.0;
			chr.chr_ai.(sType).grape.height = 3.0;
		}
		else if(sBullet == "GunEchin")
		{
			chr.chr_ai.(sType).grape.shards = 12;
			chr.chr_ai.(sType).grape.width = 10.0;
			chr.chr_ai.(sType).grape.height = 6.0;
		}
		if(CheckAttribute(chr, "chr_ai." + sType + ".grape.shards"))
			return sti(chr.chr_ai.(sType).grape.shards);
	}
	return 1;
}

#event_handler("GetShotParams","GetShotParams");
aref GetShotParams()
{
	aref chr = GetEventData();

	string sType;
	if(CharUseMusket(chr)) sType = MUSKET_ITEM_TYPE;
	else sType = GUN_ITEM_TYPE;

	aref arShards;
	makearef(arShards, chr.chr_ai.(sType).grape);
	return arShards;
}

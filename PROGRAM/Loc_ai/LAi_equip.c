#define PERK_TEMPLATE_SHIPDEFENCE	0	// 4 perks
#define PERK_TEMPLATE_REPAIR		1	// 7 perks
#define PERK_TEMPLATE_CANNONS		2	// 8 perks
#define PERK_TEMPLATE_COMMERCE		3	// 8 perks
#define PERK_TEMPLATE_SAILING		4	// 7 perks
#define PERK_TEMPLATE_GRAPPLING		5	// 8 perks
#define PERK_TEMPLATE_MEDIC			6	// 9 perks
#define PERK_TEMPLATE_MELEE		    7	// 18 perks
#define PERK_TEMPLATE_PERSONAL		8	// 3 perks
#define PERK_TEMPLATE_LAST          9

//Экипировать NPC оружием и перками (переделал полнсотью 11/11/04 boal)
void LAi_NPC_Equip(ref chr, int rank, bool isWeapons, bool isGun)
{
	// boal не нужно - ранг и так точно расчитан r = rank + rand(3) - 1;
	DeleteAttribute(chr, "equip");
	DeleteAttribute(chr, "perks.list"); // FIX 101104 убрать накопивщиеся умения
	//ПРИСВАИВАТЬ ПЕРСОНАЖАМ ПЕРКИ НУЖНО ПОСЛЕ LAi_NPC_Equip или функций, вызвающих её
	DelBakSkillAttr(chr); // fix

	if (chr.model.animation == "mushketer") return;
	if (chr.sex == "woman" && !CheckAttribute(chr, "PGGAi")) return;

	if (CheckAttribute(chr, "quest.officertype"))
	{
		// наши офицеры
		LAi_NPC_EquipPerk(chr, chr.quest.officertype);
	}
	else
	{
		LAi_NPC_EquipPerk(chr, "fantom");
	}

	//Подберём саблю
	if (isWeapons)
	{
		string blade = LAi_NPC_EquipBladeSelection(chr);

		DeleteAttribute(chr, "items"); // это можно не делать, но так наверняка (идет проверка на колво предметов, и сабель может стать вагон)
		//DeleteAttribute(chr, "cirassId"); // трем броню

		ItemTakeEquip(chr, blade, 1);
		// boal -->
		if (rand(1500) < MOD_SKILL_ENEMY_RATE * 100)
		{
			TakeNItems(chr, "potion1", rand(makeint(rank / (11 - MOD_SKILL_ENEMY_RATE) + 0.5))); // даю меньше
		}
		// boal <--
	}
	else
	{
		isGun = false;
	}
	// boal выдаем пистоль -->
	if (isGun)
	{
		if (CheckAttribute(chr, "PhantomType") && or(chr.PhantomType == "native", chr.PhantomType == "slave")) return; //Jason
		if (CheckAttribute(chr, "model") && StrStartsWith(chr.model, "draugr")) return;  //AlexBlade - Драуграм не выдаем

		string sGun = LAi_NPC_EquipGunSelection(chr);
		string sAmmo = "bullet";

		if (sGun != "")
		{
			ItemTakeEquip(chr, sGun, 1);

			if (sGun == "pistol3")
				sAmmo = "grapeshot";

			if (LAi_GetAmmoGunpowderType(sAmmo) != "")
				sAmmo += "," + LAi_GetAmmoGunpowderType(sAmmo);

			ItemTakeEx(chr, sAmmo, "" + (5 + rand(10)));
			LAi_SetCharacterDefaultBulletType(chr, GUN_ITEM_TYPE);
		}
	}
	// boal выдаем пистоль <--
}

void LAi_NPC_MushketerEquip(ref chr)
{
	while (FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE) != "")
        TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
    while (FindCharacterItemByGroup(chr, GUN_ITEM_TYPE) != "")
        TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
	while (FindCharacterItemByGroup(chr, MUSKET_ITEM_TYPE) != "")
        TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, MUSKET_ITEM_TYPE));

	GiveItem2Character(chr, "unarmed");
	EquipCharacterbyItem(chr, "unarmed");

    string sMush, sBullet;

	if (CheckAttribute(chr, "MushketType"))
		 sMush = chr.MushketType;
	else sMush = LAi_NPC_EquipMushketSelection(chr);

	if (CheckAttribute(chr, "MushketBulletType"))
         sBullet = chr.MushketBulletType;
    else sBullet = "bullet"; // ~!mu GetGunAmmoType "mortar"

	GiveItem2Character(chr, sMush);
	EquipCharacterbyItem(chr, sMush);

    AddItems(chr, sBullet, 50 + rand(50));
    AddItems(chr, LAi_GetAmmoGunpowderType(sBullet), 50 + rand(50));
    LAi_SetCharacterUseBullet(chr, MUSKET_ITEM_TYPE, sBullet);

	chr.MusketOutfit = true; // При повторном ините шаблона больше не выдаст
	if (!CheckAttribute(chr, "MusketerDistance")) chr.MusketerDistance = 10.0 + frand(10.0);
}

string GetBladeByNpcType(string wType)
{
	return GetWeaponByNpcType(wType, BLADE_ITEM_TYPE, "blade5");
}

string GetGunByNpcType(string wType)
{
	return GetWeaponByNpcType(wType, GUN_ITEM_TYPE, "pistol1");
}

string GetMushketByNpcType(string wType)
{
	return GetWeaponByNpcType(wType, MUSKET_ITEM_TYPE, "mushket_poor");
}

string GetWeaponByNpcType(string wType, string weaponType, string sDefault)
{
	ref rItem;
	string sTemp;
	string result = sDefault;
	string filteredWeapons[2]; //если создать массив [1] то оно считается просто стрингой, а не массивом.
	//фильтруем список предметов в filteredWeapons
	for (int i = 0; i < TOTAL_ITEMS; i++)
	{
		makeref(rItem, Items[i]);
		//нам подходит только не сгенерированное оружие
		if (CheckAttribute(rItem, "groupID") && rItem.groupID == weaponType && !CheckAttribute(rItem, "generated"))
		{
			if (CheckAttribute(rItem, "wType") && HasStrEx(wType, rItem.wType, "|"))
			{
				ArrayAddValue(&filteredWeapons, rItem.id);
			}
		}
	}
	if (ArrayIsEmpty(&filteredWeapons)) return result;
	result = filteredWeapons[rand(GetArraySize(&filteredWeapons) - 1)];
	return GetGeneratedItem(result);
}

//функция подбора рукопашного оружия, условия по моделям и проч вести тут
string LAi_NPC_EquipBladeSelection(ref chr)
{
	if (CheckAttribute(chr, "CityType") && chr.CityType == "soldier") // у солдат в городе свои сабли
		return GetBladeByNpcType(SOLDER_BLADE);
	if (CheckAttribute(chr, "quest.officertype")) // для офицеров выдаем по их навыкам
		return LAi_NPC_EquipBladeSelection_Officer(chr);
	if (CheckAttribute(chr, "mayor") && sti(chr.mayor) == 1) // Губерам даем офицерские сине-красное
		return GetBladeByNpcType(COOL_BLADE);
	if (HasStr(chr.model, "off_") || HasStr(chr.model, "officer_")) // офицерским солдатам даем бело-синее
		return GetBladeByNpcType(OFFICER_BLADE);
	if (CheckAttribute(chr, "indian")) //индейцам индейское
		return GetBladeByNpcType(INDIAN_BLADE);
	if (CheckAttribute(chr, "model") && StrStartsWith(chr.model, "draugr")) //викингам викингское
		return GetBladeByNpcType(VIKING_BLADE);
	if (CheckAttribute(chr, "PhantomType") && chr.PhantomType == "slave") //беглым рабам мачете и гарпуны
		return GetBladeByNpcType(SLAVE_BLADE);
	if (CheckAttribute(chr, "PGGAi")) //ПГГ выдаем по их навыкам
		return LAi_NPC_EquipBladeSelection_Officer(chr);
	if (CheckAttribute(chr, "captanid")) //капитанам бело-синее
		return GetBladeByNpcType(OFFICER_BLADE);

	//всем остальным серо-белые сабли
	return GetBladeByNpcType(ORDINARY_BLADE);

}

//функция подбора пистолетов (НЕ мушкетов), условия по моделям и проч вести тут
string LAi_NPC_EquipGunSelection(ref chr)
{
	if (rand(1000) < MOD_SKILL_ENEMY_RATE * sti(chr.rank) * 8)
	{
		if (CheckAttribute(chr, "quest.officertype"))  // для офицеров выдаем по их навыкам
			return LAi_NPC_EquipGunSelection_Officer(chr);
		if (CheckAttribute(chr, "mayor") && sti(chr.mayor) == 1)  // Губерам даем офицерские сине-красное
			return GetGunByNpcType(COOL_GUN);
		if (HasStr(chr.model, "off_") || HasStr(chr.model, "officer_")) // офицерским солдатам даем бело-синее
			return GetGunByNpcType(OFFICER_GUN);
		if (HasStr(chr.model, "AztecWarrior")) //индейцам плохое
			return GetGunByNpcType(POOR_GUN);
		if (CheckAttribute(chr, "PGGAi")) //ПГГ выдаем по их навыкам
			return GetGunByNpcType(COOL_GUN);
		if (CheckAttribute(chr, "captanid")) //капитанам бело-синее
			return GetGunByNpcType(OFFICER_GUN);

		//всем остальным серо-белое
		return GetGunByNpcType(ORDINARY_GUN);
	}
	//иногда без пистолетиков
	return "";
}

//функция подбора мушкетов, условия по моделям и проч вести тут
string LAi_NPC_EquipMushketSelection(ref chr)
{
	if (CheckAttribute(chr, "indian")) //индейцам плохое (затычка на будущее, вдруг такое будет)
		return GetMushketByNpcType(POOR_GUN);
	if (CheckAttribute(chr, "PhantomType") && chr.PhantomType == "slave") //беглым рабам плохое (затычка на будущее, вдруг такое будет)
		return GetMushketByNpcType(POOR_GUN);

	//всем остальным серо-белые мушкеты
	return GetMushketByNpcType(ORDINARY_GUN);
}

string LAi_NPC_EquipGunSelection_Officer(ref npchar)
{
	if (!CheckAttribute(Npchar, "quest.officertype_fighter") ||
	Npchar.quest.officertype_fighter != "fighter_p")
	{
		return GetGunByNpcType(ORDINARY_GUN);
	}

	string sItemId = "pistol1";

	int Rank = sti(npchar.rank);
	int iRnd = rand(2);
	if (Rank >= 15) iRnd = rand(2) + 1;
	if (Rank >= 20) iRnd = rand(3) + 2;

	switch (iRnd)
	{
		case 0:
			sItemId = "pistol1";
		break;

		case 1:
			sItemId = "pistol2";
		break;

		case 2:
			sItemId = "pistol3";
		break;

		case 3:
			sItemId = "pistol6";
		break;

		case 4:
			sItemId = "pistol4";
		break;

		case 5:
			sItemId = "pistol5";
		break;
	}

	return GetGeneratedItem(sItemId);
}

string LAi_NPC_EquipBladeSelection_Officer(ref npchar)
{
	int fencType = 1;
	int curMax = sti(npchar.skill.Fencing);
	if (sti(npchar.skill.FencingHeavy) > curMax)
	{
		fencType = 2;
		curMax = sti(npchar.skill.FencingHeavy);
	}
	if (sti(npchar.skill.FencingLight) > curMax)
	{
		fencType = 0;
	}

	return LAi_NPC_EquipBladeSelection_ExType(sti(npchar.rank), fencType);
}

// type 0 - light, 1 - medium, 2 - heavy
string LAi_NPC_EquipBladeSelection_ExType(int Rank, int type)
{
	int _type = type;
	Restrictor(&_type, 0, 2);
	int group = 1000 * _type;

	int min = rank - 8;
	if (min < 0) min = 0;
	int max = rank + 4;
	if (max > 25)
	{
		min = 12;
		max = 24;
	}
	if (max > 29)
	{
		min = 20;
		max = 31;
	}
	int sel = rand(max - min) + min;
	int val = group + sel;
	string blade = GetGeneratedItem("blade7");

	if (val <= 1)
		return GetGeneratedItem("Blade2");
	if (val <= 4)
		return GetGeneratedItem("Blade5");
	if (val <= 10)
		return GetGeneratedItem("blade6");
	if (val <= 13)
		return GetGeneratedItem("Blade9");
	if (val <= 19)
		return GetGeneratedItem("blade19");
	if (val <= 21)
		return GetGeneratedItem("blade22");
	if (val <= 31)
		return GetGeneratedItem("blade23");

	if (val <= 1000)
		return GetGeneratedItem("blade1");
	if (val <= 1002)
		return GetGeneratedItem("Blade3");
	if (val <= 1003)
		return GetGeneratedItem("Blade4");
	if (val <= 1008)
		return GetGeneratedItem("topor3");
	if (val <= 1011)
		return GetGeneratedItem("Blade7");
	if (val <= 1015)
		return GetGeneratedItem("blade12");
	if (val <= 1017)
		return GetGeneratedItem("blade18");
	if (val <= 1022)
		return GetGeneratedItem("blade31");
	if (val <= 1023)
		return GetGeneratedItem("blade34");
	if (val <= 1028)
		return GetGeneratedItem("blade24");
	if (val <= 1029)
		return GetGeneratedItem("blade25");
	if (val <= 1031)
		return GetGeneratedItem("blade30");

	if (val <= 2005)
		return GetGeneratedItem("Blade10");
	if (val <= 2006)
		return GetGeneratedItem("Blade35");
	if (val <= 2007)
		return GetGeneratedItem("topor1");
	if (val <= 2009)
		return GetGeneratedItem("blade17");
	if (val <= 2012)
		return GetGeneratedItem("Blade8");
	if (val <= 2014)
		return GetGeneratedItem("blade11");
	if (val <= 2016)
		return GetGeneratedItem("blade16");
	if (val <= 2018)
		return GetGeneratedItem("Blade15");
	if (val <= 2020)
		return GetGeneratedItem("blade21");
	if (val <= 2024)
		return GetGeneratedItem("topor2");
	if (val <= 2025)
		return GetGeneratedItem("blade13");
	if (val <= 2026)
		return GetGeneratedItem("blade20");
	if (val <= 2031)
		return GetGeneratedItem("blade33");

	return blade;
}

// new perks generator, more specialized (Gray 12.11.2004)
void LAi_NPC_EquipPerk(ref chr, string kind)
{
	int i;
	int rest = 0;
	int PerkTemplates[PERK_TEMPLATE_LAST];
	int NumPerks[PERK_TEMPLATE_LAST];
	int OfficerPerkRates[PERK_TEMPLATE_LAST];
	int rank = sti(chr.rank);

	NumPerks[PERK_TEMPLATE_SHIPDEFENCE] = 4;
	NumPerks[PERK_TEMPLATE_REPAIR] = 7;
	NumPerks[PERK_TEMPLATE_CANNONS] = 8;
	NumPerks[PERK_TEMPLATE_COMMERCE] = 8;
	NumPerks[PERK_TEMPLATE_SAILING] = 7;
	NumPerks[PERK_TEMPLATE_GRAPPLING] = 8;
	NumPerks[PERK_TEMPLATE_MEDIC] = 9;
	NumPerks[PERK_TEMPLATE_MELEE] = 18;
	NumPerks[PERK_TEMPLATE_PERSONAL] = 3;

	string hobbyKind = "";
	if (CheckAttribute(chr, "quest.officertype_hobby"))
	{
		hobbyKind = chr.quest.officertype_hobby;
		if (StrStartsWith(hobbyKind, "fighter_"))
		{
			hobbyKind = "fighter";
		}
	}

	float hasHobbyCoef = 1.0;
	if (hobbyKind != "")
	{
		hasHobbyCoef = 1.5;
	}
	for (i = 0; i < PERK_TEMPLATE_LAST; i++)
	{
		PerkTemplates[i] = 0;
		rest += NumPerks[i];
		OfficerPerkRates[i] = GetOfficerPrimaryPerkRate(i) * hasHobbyCoef;
	}
	if (rest > rank)
	{
		rest = rank;
	}

	switch (kind)
	{
		case "boatswain" :
			PerkTemplates[PERK_TEMPLATE_GRAPPLING] = makeint((rank + rand(3)) / OfficerPerkRates[PERK_TEMPLATE_GRAPPLING]);
		break;

		case "cannoner" :
			PerkTemplates[PERK_TEMPLATE_CANNONS] = makeint((rank + rand(2)) / OfficerPerkRates[PERK_TEMPLATE_CANNONS] + 1);
		break;

		case "treasurer" :
			PerkTemplates[PERK_TEMPLATE_COMMERCE] = makeint((rank + rand(3)) / OfficerPerkRates[PERK_TEMPLATE_COMMERCE] + 1);
		break;

		case "navigator" :
			PerkTemplates[PERK_TEMPLATE_SAILING] = makeint((rank + rand(2)) / OfficerPerkRates[PERK_TEMPLATE_SAILING] + 1);
		break;

		case "doctor" :
			PerkTemplates[PERK_TEMPLATE_MEDIC] = makeint((rank + rand(2)) / OfficerPerkRates[PERK_TEMPLATE_MEDIC]);
		break;

		case "carpenter" :
			PerkTemplates[PERK_TEMPLATE_REPAIR] = makeint((rank + rand(2)) / OfficerPerkRates[PERK_TEMPLATE_REPAIR]);
			PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] = makeint((rank + rand(3)) / OfficerPerkRates[PERK_TEMPLATE_SHIPDEFENCE]);
		break;

		case "fighter" :
			PerkTemplates[PERK_TEMPLATE_MELEE] = makeint((rank + rand(1)) / OfficerPerkRates[PERK_TEMPLATE_MELEE] + 1);
		break;

		case "fantom" :
			PerkTemplates[PERK_TEMPLATE_MELEE] = makeint((rank + rand(4)) / 4.0);
			PerkTemplates[PERK_TEMPLATE_SAILING] = makeint((rank + rand(5)) / 8.0);
			PerkTemplates[PERK_TEMPLATE_GRAPPLING] = makeint((rank + rand(7)) / 9.0);
			PerkTemplates[PERK_TEMPLATE_REPAIR] = makeint((rank + rand(10)) / 15.0);
			PerkTemplates[PERK_TEMPLATE_CANNONS] = makeint((rank + rand(2)) / 5.0);
			PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] = makeint((rank + rand(4)) / 7.0);
			PerkTemplates[PERK_TEMPLATE_MEDIC] = makeint((rank + rand(4)) / 7.0);
		break;
	}

	switch (hobbyKind)
	{
		case "boatswain" :
			PerkTemplates[PERK_TEMPLATE_GRAPPLING] = makeint((rank + rand(3)) / OfficerPerkRates[PERK_TEMPLATE_GRAPPLING]);
		break;

		case "cannoner" :
			PerkTemplates[PERK_TEMPLATE_CANNONS] = makeint((rank + rand(2)) / OfficerPerkRates[PERK_TEMPLATE_CANNONS]);
		break;

		case "treasurer" :
			PerkTemplates[PERK_TEMPLATE_COMMERCE] = makeint((rank + rand(3)) / OfficerPerkRates[PERK_TEMPLATE_COMMERCE]);
		break;

		case "doctor" :
			PerkTemplates[PERK_TEMPLATE_MEDIC] = makeint((rank + rand(4)) / OfficerPerkRates[PERK_TEMPLATE_MEDIC]);
		break;

		case "carpenter" :
			PerkTemplates[PERK_TEMPLATE_REPAIR] = makeint((rank + rand(2)) / OfficerPerkRates[PERK_TEMPLATE_REPAIR]);
			PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE] = makeint((rank + rand(3)) / OfficerPerkRates[PERK_TEMPLATE_SHIPDEFENCE]);
		break;

		case "fighter" :
			PerkTemplates[PERK_TEMPLATE_MELEE] = makeint((rank + rand(1)) / OfficerPerkRates[PERK_TEMPLATE_MELEE] + 1);
		break;
	}

	for (i = 0; i < PERK_TEMPLATE_LAST; i++)
	{
		if (PerkTemplates[i] > NumPerks[i])
		{
			PerkTemplates[i] = NumPerks[i];
		}

		rest = rest - PerkTemplates[i];
	}

	// the rest perks (like half usually) distributed randomly among templates
	while (rest > 0)
	{
		i = rand(PERK_TEMPLATE_LAST - 1);
		if (PerkTemplates[i] < NumPerks[i])
		{
			PerkTemplates[i] = PerkTemplates[i] + 1;
			rest--;
		}
	}

	ApplyPerkTemplate_ShipDefence(chr, kind, PerkTemplates[PERK_TEMPLATE_SHIPDEFENCE]);
	ApplyPerkTemplate_Repair(chr, kind, PerkTemplates[PERK_TEMPLATE_REPAIR]);
	ApplyPerkTemplate_Cannons(chr, kind, PerkTemplates[PERK_TEMPLATE_CANNONS]);
	ApplyPerkTemplate_Commerce(chr, kind, PerkTemplates[PERK_TEMPLATE_COMMERCE]);
	ApplyPerkTemplate_Sailing(chr, kind, PerkTemplates[PERK_TEMPLATE_SAILING]);
	ApplyPerkTemplate_Grappling(chr, kind, PerkTemplates[PERK_TEMPLATE_GRAPPLING]);
	ApplyPerkTemplate_Medic(chr, kind, PerkTemplates[PERK_TEMPLATE_MEDIC]);
	ApplyPerkTemplate_Melee(chr, kind, PerkTemplates[PERK_TEMPLATE_MELEE]);
	ApplyPerkTemplate_Personal(chr, kind, PerkTemplates[PERK_TEMPLATE_PERSONAL]);
}

float GetOfficerPrimaryPerkRate(int perkType)
{
	switch (perkType)
	{
		case PERK_TEMPLATE_GRAPPLING :
			return 4.0;
		break;
		case PERK_TEMPLATE_CANNONS :
			return 3.0;
		break;
		case PERK_TEMPLATE_COMMERCE :
			return 4.0;
		break;
		case PERK_TEMPLATE_SAILING :
			return 4.0;
		break;
		case PERK_TEMPLATE_MEDIC :
			return 3.5;
		break;
		case PERK_TEMPLATE_REPAIR :
			return 4.0;
		break;
		case PERK_TEMPLATE_SHIPDEFENCE :
			return 6.0;
		break;
		case PERK_TEMPLATE_MELEE :
			return 2.0;
		break;
	}

	return 4.0;
}

void ApplyPerkTemplate_ShipDefence(ref chr, string kind, int level)
{
	if (level < 1) return;

	bool isPGG = CheckCharacterPerk(chr, "PGGTrait");

	if (rand(2) == 1 && !isPGG)
	{
		chr.perks.list.Caulking = "1";
		if (level >= 2) chr.perks.list.BasicBattleState = "1";
		if (level >= 3) chr.perks.list.AdvancedBattleState = "1";
		if (level >= 4) chr.perks.list.ShipDefenseProfessional = "1";
	}
	else
	{
		chr.perks.list.BasicBattleState = "1";
		if (level >= 2) chr.perks.list.AdvancedBattleState = "1";
		if (level >= 3) chr.perks.list.ShipDefenseProfessional = "1";
		if (level >= 4) chr.perks.list.Caulking = "1";
	}
}

void ApplyPerkTemplate_Medic(ref chr, string kind, int level)
{
	if (level < 1) return;

	chr.perks.list.Doctor1 = "1";
	if (level >= 2) chr.perks.list.Doctor2 = "1";
	if (level >= 3) chr.perks.list.Naturalcure = "1";
	if (level >= 4) chr.perks.list.Aptekar = "1";

	bool isPGG = CheckCharacterPerk(chr, "PGGTrait");
	int patternNum = rand(2);
	if (isPGG)
		patternNum = 0;
	switch (patternNum)
	{
		case 0:
			if (level >= 5) chr.perks.list.PainResistance = "1";
			if (level >= 6) chr.perks.list.PersonalCare = "1";
			if (level >= 7) chr.perks.list.LifeSupport = "1";
			if (level >= 8) chr.perks.list.Prevention = "1";
			if (level >= 9) chr.perks.list.Doctor3 = "1";
		break;

		case 1:
			if (level >= 5) chr.perks.list.LifeSupport = "1";
			if (level >= 6) chr.perks.list.Prevention = "1";
			if (level >= 7) chr.perks.list.Doctor3 = "1";
			if (level >= 8) chr.perks.list.PainResistance = "1";
			if (level >= 9) chr.perks.list.PersonalCare = "1";
		break;

		case 2:
			if (level >= 5) chr.perks.list.PainResistance = "1";
			if (level >= 6) chr.perks.list.LifeSupport = "1";
			if (level >= 7) chr.perks.list.Prevention = "1";
			if (level >= 8) chr.perks.list.Doctor3 = "1";
			if (level >= 9) chr.perks.list.PersonalCare = "1";
		break;
	}
}

void ApplyPerkTemplate_Repair(ref chr, string kind, int level)
{
	if (level < 1) return;

	bool isPGG = CheckCharacterPerk(chr, "PGGTrait");
	int patternNum = rand(2);
	if (isPGG)
		patternNum = 0;

	switch (patternNum)
	{
		case 0:
			chr.perks.list.Carpenter = "1";
			if (level >= 2)
			{
				if (CheckCharacterPerk(chr, "Caulking"))
					level += 1;
				else
					chr.perks.list.Caulking = "1";
			}
			if (level >= 3) chr.perks.list.LightRepair = "1";
			if (level >= 4) chr.perks.list.Builder = "1";
			if (level >= 5) chr.perks.list.InstantRepair = "1";
			if (level >= 6) chr.perks.list.Shipbuilder = "1";
			if (level >= 7) chr.perks.list.SelfRepair = "1";
		break;

		case 1:
			if (CheckCharacterPerk(chr, "Caulking"))
				level += 1;
			else
				chr.perks.list.Caulking = "1";

			if (level >= 2) chr.perks.list.LightRepair = "1";
			if (level >= 3) chr.perks.list.InstantRepair = "1";
			if (level >= 4) chr.perks.list.SelfRepair = "1";
			if (level >= 5) chr.perks.list.Carpenter = "1";
			if (level >= 6) chr.perks.list.Builder = "1";
			if (level >= 7) chr.perks.list.Shipbuilder = "1";
		break;

		case 2:
			chr.perks.list.Carpenter = "1";
			if (level >= 2)
			{
				if (CheckCharacterPerk(chr, "Caulking"))
					level += 1;
				else
					chr.perks.list.Caulking = "1";
			}
			if (level >= 3) chr.perks.list.Builder = "1";
			if (level >= 4) chr.perks.list.LightRepair = "1";
			if (level >= 5) chr.perks.list.Shipbuilder = "1";
			if (level >= 6) chr.perks.list.InstantRepair = "1";
			if (level >= 7) chr.perks.list.SelfRepair = "1";
		break;
	}
}

void ApplyPerkTemplate_Cannons(ref chr, string kind, int level)
{
	if (level < 1) return;

	bool isPGG = CheckCharacterPerk(chr, "PGGTrait");
	int patternNum = rand(2);
	if (isPGG)
		patternNum = 0;

	switch (patternNum)
	{
		case 0:
			chr.perks.list.HullDamageUp = "1";
			if (level >= 2) chr.perks.list.SailsDamageUp = "1";
			if (level >= 3) chr.perks.list.CrewDamageUp = "1";
			if (level >= 4) chr.perks.list.CriticalShoot = "1";
			if (level >= 5) chr.perks.list.FastReload = "1";
			if (level >= 6) chr.perks.list.LongRangeShoot = "1";
			if (level >= 7) chr.perks.list.CannonProfessional = "1";
			if (level >= 8) chr.perks.list.ImmediateReload = "1";
		break;

		case 1:
			chr.perks.list.HullDamageUp = "1";
			if (level >= 2) chr.perks.list.CrewDamageUp = "1";
			if (level >= 3) chr.perks.list.SailsDamageUp = "1";
			if (level >= 4) chr.perks.list.CriticalShoot = "1";
			if (level >= 5) chr.perks.list.FastReload = "1";
			if (level >= 6) chr.perks.list.ImmediateReload = "1";
			if (level >= 7) chr.perks.list.LongRangeShoot = "1";
			if (level >= 8) chr.perks.list.CannonProfessional = "1";
		break;

		case 2:
			chr.perks.list.FastReload = "1";
			if (level >= 2) chr.perks.list.HullDamageUp = "1";
			if (level >= 3) chr.perks.list.ImmediateReload = "1";
			if (level >= 4) chr.perks.list.LongRangeShoot = "1";
			if (level >= 5) chr.perks.list.CrewDamageUp = "1";
			if (level >= 6) chr.perks.list.SailsDamageUp = "1";
			if (level >= 7) chr.perks.list.CriticalShoot = "1";
			if (level >= 8) chr.perks.list.CannonProfessional = "1";
		break;
	}
}

void ApplyPerkTemplate_Commerce(ref chr, string kind, int level)
{
	if (level < 1) return;

	bool isPGG = CheckCharacterPerk(chr, "PGGTrait");
	int patternNum = rand(2);
	if (isPGG)
		patternNum = 0;

	switch (patternNum)
	{
		case 0:
			chr.perks.list.BasicCommerce = "1";
			if (level >= 2) chr.perks.list.QuickCalculation = "1";
			if (level >= 3) chr.perks.list.AdvancedCommerce = "1";
			if (level >= 4) chr.perks.list.ArtOfDeals = "1";
			if (level >= 5) chr.perks.list.PriceRecon = "1";
			if (level >= 6) chr.perks.list.Investor = "1";
			if (level >= 7) chr.perks.list.ProfessionalCommerce = "1";
			if (level >= 8) chr.perks.list.Packer = "1";
		break;

		case 1:
			chr.perks.list.BasicCommerce = "1";
			if (level >= 2) chr.perks.list.QuickCalculation = "1";
			if (level >= 3) chr.perks.list.AdvancedCommerce = "1";
			if (level >= 4) chr.perks.list.Packer = "1";
			if (level >= 5) chr.perks.list.ArtOfDeals = "1";
			if (level >= 6) chr.perks.list.PriceRecon = "1";
			if (level >= 7) chr.perks.list.Investor = "1";
			if (level >= 8) chr.perks.list.ProfessionalCommerce = "1";
		break;

		case 2:
			chr.perks.list.BasicCommerce = "1";
			if (level >= 2) chr.perks.list.QuickCalculation = "1";
			if (level >= 3) chr.perks.list.AdvancedCommerce = "1";
			if (level >= 4) chr.perks.list.ArtOfDeals = "1";
			if (level >= 5) chr.perks.list.Investor = "1";
			if (level >= 6) chr.perks.list.PriceRecon = "1";
			if (level >= 7) chr.perks.list.ProfessionalCommerce = "1";
			if (level >= 8) chr.perks.list.Packer = "1";
		break;
	}
}

void ApplyPerkTemplate_Sailing(ref chr, string kind, int level)
{
	if (level < 1) return;

	bool isPGG = CheckCharacterPerk(chr, "PGGTrait");
	int patternNum = rand(1);
	if (isPGG)
		patternNum = 0;

	switch (patternNum)
	{
		case 0:
			chr.perks.list.ShipSpeedUp = "1";
			if (level >= 2) chr.perks.list.ShipTurnRateUp = "1";
			if (level >= 3) chr.perks.list.StormProfessional = "1";
			if (level >= 4) chr.perks.list.SailsMan = "1";
			if (level >= 5) chr.perks.list.WindCatcher = "1";
			if (level >= 6) chr.perks.list.Turn180 = "1";
			if (level >= 7) chr.perks.list.SailingProfessional = "1";
		break;

		case 1:
			chr.perks.list.StormProfessional = "1";
			if (level >= 2) chr.perks.list.SailsMan = "1";
			if (level >= 3) chr.perks.list.ShipSpeedUp = "1";
			if (level >= 4) chr.perks.list.WindCatcher = "1";
			if (level >= 5) chr.perks.list.ShipTurnRateUp = "1";
			if (level >= 6) chr.perks.list.Turn180 = "1";
			if (level >= 7) chr.perks.list.SailingProfessional = "1";
		break;
	}
}

void ApplyPerkTemplate_Grappling(ref chr, string kind, int level)
{
	if (level < 1) return;

	chr.perks.list.LongRangeGrappling = "1";

	bool isPGG = CheckCharacterPerk(chr, "PGGTrait");
	int patternNum = rand(2);
	if (isPGG)
		patternNum = 1;

	switch (patternNum)
	{
		case 0:
			if (level >= 2) chr.perks.list.LootCollection = "1";
			if (level >= 3) chr.perks.list.Mentor = "1";
			if (level >= 4) chr.perks.list.IronWill = "1";
			if (level >= 5) chr.perks.list.MusketsShoot = "1";
			if (level >= 6) chr.perks.list.GrapplingProfessional = "1";
			if (level >= 7) chr.perks.list.Brander = "1";
			if (level >= 8) chr.perks.list.Troopers = "1";
		break;

		case 1:
			if (level >= 2) chr.perks.list.IronWill = "1";
			if (level >= 3) chr.perks.list.MusketsShoot = "1";
			if (level >= 4) chr.perks.list.Mentor = "1";
			if (level >= 5) chr.perks.list.GrapplingProfessional = "1";
			if (level >= 6) chr.perks.list.LootCollection = "1";
			if (level >= 7) chr.perks.list.Brander = "1";
			if (level >= 8) chr.perks.list.Troopers = "1";
		break;

		case 2:
			if (level >= 2) chr.perks.list.Mentor = "1";
			if (level >= 3) chr.perks.list.IronWill = "1";
			if (level >= 4) chr.perks.list.MusketsShoot = "1";
			if (level >= 5) chr.perks.list.LootCollection = "1";
			if (level >= 6) chr.perks.list.GrapplingProfessional = "1";
			if (level >= 7) chr.perks.list.Brander = "1";
			if (level >= 8) chr.perks.list.Troopers = "1";
		break;
	}
}

void ApplyPerkTemplate_Melee(ref chr, string kind, int level)
{
	if (level < 1) return;

	chr.perks.list.BasicDefense = "1";
	if (level >= 2) chr.perks.list.AdvancedDefense = "1";

	bool isPGG = CheckCharacterPerk(chr, "PGGTrait");
	int patternNum = rand(2);
	if (isPGG)
		patternNum = 0;
	if (CheckAttribute(chr, "quest.officertype_fighter") && chr.quest.officertype_fighter == "fighter_p")
	{
		patternNum = 1;
	}

	switch (patternNum)
	{
		// приближен к старой прокачке
		case 0:
			if (level >= 3) chr.perks.list.BasicAttack = "1";
			if (level >= 4) chr.perks.list.CriticalHit = "1";
			if (level >= 5) chr.perks.list.Gunman = "1";
			if (level >= 6) chr.perks.list.HardHitter = "1";
			if (level >= 7) chr.perks.list.Tireless = "1";
			if (level >= 8) chr.perks.list.AdvancedAttack = "1";
			if (level >= 9) chr.perks.list.Sliding = "1";
			if (level >= 10) chr.perks.list.BladeDancer = "1";
			if (level >= 11) chr.perks.list.SwordplayProfessional = "1";
			if (level >= 12) chr.perks.list.GunAdvanced = "1";
			if (level >= 13) chr.perks.list.GunProfessional = "1";
			if (level >= 14) chr.perks.list.Ciras = "1";
			if (level >= 15) chr.perks.list.Grus = "1";
			if (level >= 16) chr.perks.list.Shoottech = "1";
			if (level >= 17) chr.perks.list.DevilsEye = "1";
			if (level >= 18) chr.perks.list.StunningShot = "1";
		break;
		// уклон в огнестрел
		case 1:
			if (level >= 3) chr.perks.list.Gunman = "1";
			if (level >= 4) chr.perks.list.GunAdvanced = "1";
			if (level >= 5) chr.perks.list.StunningShot = "1";
			if (level >= 6) chr.perks.list.Shoottech = "1";
			if (level >= 7) chr.perks.list.GunProfessional = "1";
			if (level >= 8) chr.perks.list.Ciras = "1";
			if (level >= 9) chr.perks.list.DevilsEye = "1";
			if (level >= 10) chr.perks.list.Grus = "1";
			if (level >= 11) chr.perks.list.BasicAttack = "1";
			if (level >= 12) chr.perks.list.CriticalHit = "1";
			if (level >= 13) chr.perks.list.HardHitter = "1";
			if (level >= 14) chr.perks.list.Tireless = "1";
			if (level >= 15) chr.perks.list.AdvancedAttack = "1";
			if (level >= 16) chr.perks.list.Sliding = "1";
			if (level >= 17) chr.perks.list.BladeDancer = "1";
			if (level >= 18) chr.perks.list.SwordplayProfessional = "1";
		break;
		// уклон в холодное оружие
		case 2:
			if (level >= 3) chr.perks.list.BasicAttack = "1";
			if (level >= 4) chr.perks.list.CriticalHit = "1";
			if (level >= 5) chr.perks.list.Tireless = "1";
			if (level >= 6) chr.perks.list.HardHitter = "1";
			if (level >= 7) chr.perks.list.AdvancedAttack = "1";
			if (level >= 8) chr.perks.list.Sliding = "1";
			if (level >= 9) chr.perks.list.BladeDancer = "1";
			if (level >= 10) chr.perks.list.SwordplayProfessional = "1";
			if (level >= 11) chr.perks.list.Ciras = "1";
			if (level >= 12) chr.perks.list.Grus = "1";
			if (level >= 13) chr.perks.list.Gunman = "1";
			if (level >= 14) chr.perks.list.StunningShot = "1";
			if (level >= 15) chr.perks.list.GunAdvanced = "1";
			if (level >= 16) chr.perks.list.GunProfessional = "1";
			if (level >= 17) chr.perks.list.Shoottech = "1";
			if (level >= 18) chr.perks.list.DevilsEye = "1";
		break;
	}
}

void ApplyPerkTemplate_Personal(ref chr, string kind, int level)
{
	if (level < 1) return;

	if (CheckCharacterPerk(chr, "Grus"))
		level += 1;
	else
		chr.perks.list.Grus = "1";

	if (level >= 2) chr.perks.list.ShipEscape = "1";
	if (level >= 3) chr.perks.list.HawkEye = "1";

}


//Проверить ссылку на персонажа
bool LAi_CheckCharacter(aref chr, string out)
{
	if(!TestRef(chr))
	{
		Trace("LAi_CheckCharacter -> invalide aref, call from " + out);
		return false;
	}
	if(CheckAttribute(chr, "index") == false)
	{
		Trace(out + " -> invalide character, no field <index>");
		return false;
	}
	if(CheckAttribute(chr, "chr_ai.type") == false)
	{
		Trace(out + " -> invalide character " + chr.id + ", no field <chr_ai.type>");
		return false;
	}
	if(CheckAttribute(chr, "chr_ai.tmpl") == false)
	{
		Trace(out + " -> invalide character, no field <chr_ai.tmpl>");
		return false;
	}
	return true;
}

//Зарядилось ли используемое персонажем огнестрельное оружие
bool LAi_CharacterCanFire(aref chr)
{
	string sGunType = GUN_ITEM_TYPE;

	if (CharUseMusket(chr))
		sGunType = MUSKET_ITEM_TYPE;

	if (!CheckAttribute(chr, "chr_ai." + sGunType + ".chargeprc"))
	{
		chr.chr_ai.(sGunType).chargeprc = "1";
		chr.chr_ai.(sGunType).charge = 0;
		return false;
	}

	if (stf(chr.chr_ai.(sGunType).charge) >= 1.0) return true;

	return false;
}

//Получить количество энергии у персонажа 0..100
float Lai_CharacterGetEnergy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		return stf(chr.chr_ai.energy);
	}
	return 0.0;
}

//Изменить количество энергии у персонажа 0..100
void Lai_CharacterChangeEnergy(aref chr, float dlt)
{
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		float cur = stf(chr.chr_ai.energy);
		cur = cur + dlt;
		if(cur < 0.0) cur = 0.0;
		if(cur > LAi_GetCharacterMaxEnergy(chr)) cur = LAi_GetCharacterMaxEnergy(chr); //boal
		chr.chr_ai.energy = cur;
	}else{
		if(dlt < 0.0) dlt = 0.0;
		if(dlt > LAi_GetCharacterMaxEnergy(chr)) dlt = LAi_GetCharacterMaxEnergy(chr);
		chr.chr_ai.energy = dlt;
	}
}

//Может ли сражаться персонаж в заданной локации
bool LAi_LocationCanFight()
{
	if(IsEntity(loadedLocation) != true) return true;
	if(CheckAttribute(loadedLocation, "noFight") != true)  return true;
	if(sti(loadedLocation.noFight) != false) return false;
	return true;
}

//Найт кол-во локаторов в заданной группе <-- ugeen 
int LAi_GetLocatorNum(string group)
{
	if(IsEntity(loadedLocation) != true) return -1;
	string at = "locators." + group;
	if(CheckAttribute(loadedLocation, at) == 0) return 0;
	aref grp;
	makearef(grp, loadedLocation.(at));
	return GetAttributesNum(grp);
}

//Найти случайный локатор в заданной группе локаторов
string LAi_FindRandomLocator(string group)
{
	if(IsEntity(loadedLocation) != true) return "";
	string at = "locators." + group;
	if(CheckAttribute(loadedLocation, at) == 0) return "";
	aref grp;
	makearef(grp, loadedLocation.(at));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	num = rand(num - 1);
	return GetAttributeName(GetAttributeN(grp, num));
}

//Найти дальний локатор в заданной группе локаторов
string LAi_FindFarLocator(string group, float x, float y, float z)
{
	if(IsEntity(loadedLocation) != true) return "";
	string at = "locators." + group;
	if(CheckAttribute(loadedLocation, at) == 0) return "";
	aref grp;
	makearef(grp, loadedLocation.(at));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist = -1;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float dx = x - stf(loc.x);
		float dy = y - stf(loc.y);
		float dz = z - stf(loc.z);
		float d = dx*dx + dy*dy + dz*dz;
		if(j >= 0)
		{
			if(d >= dist)
			{
				dist = d;
				j = i;
			}
		}else{
			j = i;
			dist = d;
		}
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}

//Найти дальний свободный локатор в заданной группе локаторов
string LAi_FindFarFreeLocator(string group, float x, float y, float z)
{
	if(IsEntity(loadedLocation) != true) return "";
	string at = "locators." + group;
	if(CheckAttribute(loadedLocation, at) == 0) return "";
	aref grp;
	makearef(grp, loadedLocation.(at));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float lx = stf(loc.x);
		float ly = stf(loc.y);
		float lz = stf(loc.z);
		if(CheckLocationPosition(loadedLocation, lx, ly, lz))
		{
			float dx = x - lx;
			float dy = y - ly;
			float dz = z - lz;
			float d = dx*dx + dy*dy + dz*dz;
			if(j >= 0)
			{
				if(d > dist)
				{
					dist = d;
					j = i;
				}
			}else{
				j = i;
				dist = d;
			}
		}
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}

//Найти ближайший свободный локатор
string LAi_FindNearestFreeLocator(string group, float x, float y, float z)
{
	if(IsEntity(loadedLocation) != true) return "";
	string at = "locators." + group;
	if(CheckAttribute(loadedLocation, at) == 0) return "";
	aref grp;
	makearef(grp, loadedLocation.(at));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist = 0;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float lx = stf(loc.x);
		float ly = stf(loc.y);
		float lz = stf(loc.z);
		if(CheckLocationPosition(loadedLocation, lx, ly, lz))
		{
			float dx = x - lx;
			float dy = y - ly;
			float dz = z - lz;
			float d = dx*dx + dy*dy + dz*dz;
			if(j >= 0)
			{
				if(d < dist)
				{
					dist = d;
					j = i;
				}
			}
			else
			{
				j = i;
				dist = d;
			}
		}
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}
// boal
string LAi_FindNearestLocator(string group, float x, float y, float z)
{
	if(IsEntity(loadedLocation) != true) return "";
	string at = "locators." + group;
	if(CheckAttribute(loadedLocation, at) == 0) return "";
	aref grp;
	makearef(grp, loadedLocation.(at));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist = -1;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float dx = x - stf(loc.x);
		float dy = y - stf(loc.y);
		float dz = z - stf(loc.z);
		float d = dx*dx + dy*dy + dz*dz;
		if(j >= 0)
		{
			if(d < dist)
			{
				dist = d;
				j = i;
			}
		}
		else
		{
			j = i;
			dist = d;
		}
	}
	if(j < 0) return "";
	return GetAttributeName(GetAttributeN(grp, j));
}

string LAi_FindNearestFreeLocator2Pchar(string group)
{
	float locx, locy, locz;
	GetCharacterPos(Pchar, &locx, &locy, &locz);
	return LAi_FindNearestFreeLocator(group, locx, locy, locz);
}

string LAi_FindNearestLocator2NPC(ref chr, string group) //Необязательно свободный
{
	float locx, locy, locz;
	GetCharacterPos(chr, &locx, &locy, &locz);
	return LAi_FindNearestLocator(group, locx, locy, locz);
}

//поиск локатора в указанном радиусе от NPC
bool LAi_CheckLocatorWithinRadiusNPC(ref char, string sLocatorGroup, string sLocatorName, int iRadius)
{
    float locx, locy, locz;
    GetCharacterPos(char, &locx, &locy, &locz);
    if(IsEntity(loadedLocation) != true) return false;
    string at = "locators." + sLocatorGroup;
    if(CheckAttribute(loadedLocation, at) == 0) return false;
    aref grp;
    makearef(grp, loadedLocation.(at));
    int num = GetAttributesNum(grp);
    if(num <= 0) return false;

    for(int i = 0; i < num; i++)
    {
        aref loc = GetAttributeN(grp, i);
        float dx = locx - stf(loc.x);
        float dy = locy - stf(loc.y);
        float dz = locz - stf(loc.z);
        float dist = dx*dx + dy*dy + dz*dz;

        if (iRadius >= sti(dist))
        {
            string sTempLocName = GetAttributeName(GetAttributeN(grp, i));
            if (sTempLocName == sLocatorName) return true;
        }
    }
    return false;
}

//поиск локатора в указанном радиусе от pchar
bool LAi_CheckLocatorWithinRadius(string sLocatorGroup, string sLocatorName, int iRadius)
{
    return LAi_CheckLocatorWithinRadiusNPC(pchar, sLocatorGroup, sLocatorName, iRadius);
}

void LAi_PlaceCharInTavern(ref chr)
{
	bool clone = loadedLocation.type == "clone" && HasSubStr(pchar.questTemp.LocationClone.id, "tavern");
	if(!clone && loadedLocation.type != "tavern" && loadedlocation.id != "FleuronTavern" && loadedlocation.id != "FortFrance_Malta_Dungeon" && loadedlocation.id.label != "cabine") return;
	float locx, locy, locz;
    GetCharacterPos(chr, &locx, &locy, &locz);
	string loc1 = LAi_FindNearestFreeLocator("tables", locx, locy, locz);
	string loc2 = LAi_FindNearestFreeLocator("goto", locx, locy, locz);
    if (loc1 == "") // Для кают
    {
        ChangeCharacterAddressGroup(chr, chr.location, "goto", loc2);
        return;
    }
    aref aloc1, aloc2;
	makearef(aloc1, loadedLocation.locators.tables.(loc1));
	makearef(aloc2, loadedLocation.locators.goto.(loc2));
	float dist1, dist2;
	dist1 = 0.0; dist2 = 0.0;
	for (int i = 0; i <= 1; i++)
	{
		aref loc;
		if(i == 0) loc = aloc1;
		else loc = aloc2;
		float dx = locx - stf(loc.x);
		float dy = locy - stf(loc.y);
		float dz = locz - stf(loc.z);
		dist2 = dx*dx + dy*dy + dz*dz;
		if(i == 0) dist1 = dist2;
	}
	if(dist1 < dist2) ChangeCharacterAddressGroup(chr, chr.location, "tables", loc1);
	else ChangeCharacterAddressGroup(chr, chr.location, "goto", loc2);
}

string LAi_FindSitLocatorNear()
{
	float x, float y, float z;
	GetCharacterPos(Pchar, &x, &y, &z);
	if(IsEntity(loadedLocation) != true) return "";
	string at = "locators.sit";
	if(CheckAttribute(loadedLocation, at) == 0) return "";
	aref grp;
	makearef(grp, loadedLocation.(at));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int j = -1;
	float dist = -1;
	for(int i = 0; i < num; i++)
	{
		aref loc = GetAttributeN(grp, i);
		float dx = x - stf(loc.x);
		float dy = y - stf(loc.y);
		float dz = z - stf(loc.z);
		float d = dx*dx + dy*dy + dz*dz;
		TEV.sitting = GetAttributeName(loc);
		if(!LAi_CheckLocatorFree("sit", TEV.sitting)) continue;
		if(j >= 0)
		{
			if(d < dist)
			{
				dist = d;
				j = i;
			}
		}
		else
		{
			j = i;
			dist = d;
		}
	}
	if(j < 0 || dist > 1.7) return "";
	string result = GetAttributeName(GetAttributeN(grp, j));
	if(HasSubStr(result, "Fire")) return "";
	return result;
}

void LAi_GetUpCheck()
{
	if (GetEventData() == "ChrAction")
        LAi_GetUpFromChair();
}

void LAi_GetUpFromChair()
{
	LAi_CharacterDisableDialog(PChar);
	LAi_MethodDelay("LAi_PCharTalking", 0.2);
	LAi_SetPlayerType(PChar);
	if (loadedlocation.type != "tavern" && loadedlocation.id != "FleuronTavern" && loadedlocation.id != "FortFrance_Malta_Dungeon" && loadedlocation.id.label != "cabine")
    {
		 PlaceCharacter(PChar, "goto", PChar.location);
	}
    else LAi_PlaceCharInTavern(PChar);
}

void LAi_SitOnChair()
{
	ChangeCharacterAddressGroup(PChar, loadedlocation.id, "sit", TEV.chair);
	SetEventHandler("Control Activation", "LAi_GetUpCheck", 1);
    bool bTavern = (loadedlocation.type == "tavern") || (loadedlocation.id == "FleuronTavern");
	bool bResidence = HasStrEx(loadedlocation.id, "townhall,Residence", "|") &&
                      loadedlocation.filespath.models != "locations\Inside\BigHouse04";
	if (bResidence)
        LAi_SetHuberType(PChar);
    else
    {
        if (!bTavern) PChar.nonTable = true;
        LAi_SetSitType(PChar);
    }
	TEV.begin_sit = true;
	PChar.turn_ang = 180.0;
}

void LAi_PCharTalking()
{
	LAi_CharacterEnableDialog(PChar);
}

void LAi_NPC_GetUp(ref chr)
{
	float locx, locy, locz;
	GetCharacterPos(chr, &locx, &locy, &locz);
	if(loadedlocation.type != "tavern" && loadedlocation.id != "FleuronTavern" && loadedlocation.id != "FortFrance_Malta_Dungeon" && loadedlocation.id.label != "cabine")
		 ChangeCharacterAddressGroup(chr, chr.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
	else LAi_PlaceCharInTavern(chr);
}

//Найти ближайшего персонажа в заданном радиусе
int LAi_FindNearestCharacter(aref chr, float radius)
{
	int res = FindNearCharacters(chr, radius, -1.0, -1.0, 0.01, false, true);
	if(res <= 0) return -1;
	return sti(chrFindNearCharacters[0].index);
}

//Найти ближайшего видимого персонажа в заданном радиусе
int LAi_FindNearestVisCharacter(aref chr, float radius)
{
	int res = FindNearCharacters(chr, radius, -1.0, -1.0, 0.01, true, true);
	if(res <= 0) return -1;
	return sti(chrFindNearCharacters[0].index);
}

//Проверить видит ли npc игрока в заданном радиусе
bool LAi_CharacterSeesThePchar(aref chr, float radius)
{
	int iNum = FindNearCharacters(chr, radius, -1.0, -1.0, 0.01, true, true);
	if (iNum <= 0) return false;
    ref sld;
    for (int i = 0; i < iNum; i++)
    {
        makeref(sld, characters[sti(chrFindNearCharacters[i].index)]);
        if (sld.id == pchar.id) return true;
    }
    return false;
}

//Получить уровень драки приведёный к 0..1
float LAi_GetCharacterFightLevel(aref character)
{
	float fgtlevel = 0.0;
	if (CharUseMusket(character)) fgtlevel = GetCharacterSkill(character, SKILL_PISTOL);
	else fgtlevel = GetCharacterSkill(character, LAi_GetBladeFencingType(character));
	fgtlevel = fgtlevel/SKILL_MAX;
	return fgtlevel;
}

//Получить уровень pistol приведёный к 0..1
float LAi_GetCharacterGunLevel(aref character)
{
	//pistol skill
	float fgtlevel = 0.0;
	fgtlevel = GetCharacterSkill(character, SKILL_PISTOL);
	fgtlevel = fgtlevel/SKILL_MAX;
	return fgtlevel;
}

float LAi_GetCharacterLuckLevel(aref character)
{
	float fgtlevel = 0.0;
	fgtlevel = GetCharacterSkill(character, SKILL_FORTUNE);
	fgtlevel = fgtlevel/SKILL_MAX;
	return fgtlevel;
}

//Применить повреждение к персонажу
void LAi_ApplyCharacterDamage(aref chr, int dmg, string DamageType)
{
	float damage    = MakeFloat(dmg);
	bool  bIsOfficer = false;
	//Офицерам ослабляем поврежрение
	if(CheckAttribute(chr, "chr_ai.type"))
	{
		if(chr.chr_ai.type == LAI_TYPE_OFFICER)
		{
			damage = damage*0.7;
			bIsOfficer = true;
		}
	}
	//Получаем текущие параметры
	if(!CheckAttribute(chr, "chr_ai.hp"))     chr.chr_ai.hp     = LAI_DEFAULT_HP;
	if(!CheckAttribute(chr, "chr_ai.hp_max")) chr.chr_ai.hp_max = LAI_DEFAULT_HP_MAX;
	float maxhp = stf(chr.chr_ai.hp_max);
	float hp    = stf(chr.chr_ai.hp);
	//Пересчитываем
	if (damage > hp)  damage = hp;
	hp = hp - damage;
	if(hp < 1.0) hp = 0.0;
	chr.chr_ai.hp = hp;
	//Проверим квест
	LAi_ProcessCheckMinHP(chr);
	
	bool bloodSize = false;
	if (damage > 30.0) bloodSize = true;
	float fRange = 1.0 + frand(0.6);
	
	if (CheckAttribute(chr, "model.animation") && or(chr.sex != "skeleton", !HasSubStr(chr.model, "skel")))
	{
		if (DamageType == "fire" || DamageType == "fight")
		{
			LaunchBlood(chr, fRange, bloodSize, DamageType);
		}
	}
	
	if(sti(pchar.index) == sti(chr.index)) 
	{
		// здоровье -->
        pchar.Health.Damg      = stf(pchar.Health.Damg) + damage;
	    pchar.Health.weekDamg  = stf(pchar.Health.weekDamg) + damage;
        pchar.Health.TotalDamg = stf(pchar.Health.TotalDamg) + damage;
        // здоровье <--
        if (LAi_GetCharacterRelHP(pchar) < 0.5 && hp > 1.0)
        	 Tutorial_Cure("");
        return;
	}
	if (bIsOfficer)
    {
        chr.Health.TotalDamg = stf(chr.Health.TotalDamg) + damage; // статистика
        return;
    }
	//Напишем о нанесённом повреждении
	SendMessage(chr, "lfff", MSG_CHARACTER_VIEWDAMAGE, dmg, MakeFloat(MakeInt(hp)), MakeFloat(MakeInt(maxhp)));
}

//Убить персонажа, если закончились hp
void LAi_CheckKillCharacter(aref chr)
{
	if(SendMessage(chr, "ls", MSG_CHARACTER_EX_MSG, "IsDead")) return;
	if(!CheckAttribute(chr, "chr_ai.hp")) chr.chr_ai.hp = 0.0;
	//Проверяем
	if(stf(chr.chr_ai.hp) < 1.0)
	{
		//Ванька-Встанька просто ляжет полежать пока всё не утихнет
		if (CheckAttribute(chr, "chr_ai.roly_poly"))
		{
			if (chr.chr_ai.roly_poly == "1")
			{
				bool bNotDie = true;

				if (IsOfficer(chr))
				{
					AddCharacterHealth(chr, -10-rand(1)*10-rand(1)*5);
//			если захотим убивать офецеров, а не просто портить им здоровье, то надо расскоментить этот код. Вместо того что выше
//					if (rand(GetHealthMaxNum(chr)) <= GetHealthNum(chr)) AddCharacterHealth(chr, -10-rand(1)*10-rand(1)*5);
//					else bNotDie = false; //Здоровье кончилось, настало время умирать
				}
				if (bNotDie)
				{
					chr.chr_ai.hp = 1.0;
					if (!CheckAttribute(chr, "chr_ai.type") || chr.chr_ai.type != LAI_TYPE_INJURE) LAi_SetInjureTypeNoGroup(chr);
					return;
				}
			}
		}
		
		// Квестовое бессмертие, персонаж садится на землю
		if(CheckAttribute(chr, "QuestImmortal"))
		{
			chr.chr_ai.hp = 10.0 + LAi_GetCharacterMaxHP(chr) * 0.5;
			LAi_SetActorType(chr);
			LAi_ActorSetGroundSitMode(chr);
			LAi_group_MoveCharacter(chr, LAI_GROUP_ACTOR);
			return;
		}
		
		//Убиваем, если смертен
		if(CheckAttribute(chr, "chr_ai.immortal"))
		{
			if(sti(chr.chr_ai.immortal) != 0)
			{
				chr.chr_ai.hp = 1.0;
				return;
			}
		}

		DelLandQuestMark(chr);
		DelRelations(chr);
		DeleteNPCInRumourGroups(chr);

		chr.chr_ai.hp = 0.0;
		// boal dead can be searched 14.12.2003 -->
		Dead_AddLoginedCharacter(chr); // записали ещё живого в список трупов
		// boal dead can be searched 14.12.2003 <--
		LAi_type_monkey_GoAway(chr);
		SetCharacterTask_Dead(chr);
		Postevent(EVENT_CHARACTER_DEAD, 1, "a", chr);
		//Переинициируем параметры
		if(CheckAttribute(chr, "chr_ai.type"))
		{
			string func = chr.chr_ai.type;
			chr.chr_ai.type = "";
			chr.chr_ai.tmpl = "";
			if(func != "")
			{
				func = "LAi_type_" + func + "_Init";
				call func(chr);
			}
			if(sti(chr.index) == nMainCharacterIndex)
			{
				//Если убили игрока, то запретим интерфейс
				InterfaceStates.Launched = true;
			}
		}
		LAi_Character_Dead_Process(chr);
	}
}

//Создать фантомного персонажа
ref LAi_CreateFantomCharacter(string model, string group, string locator)
{
	return LAi_CreateFantomCharacterEx(model, "man", group, locator);
}

//Создать фантомного персонажа
ref LAi_CreateFantomCharacterEx(string model, string ani, string group, string locator)
{
	//Ищем свободное место для персонажа
	int i;
	for(i = 0; i < MAX_CHARS_IN_LOC; i++)
	{
		if(CheckAttribute(&Characters[LOC_FANTOM_CHARACTERS + i], "id") == false) break;
		if(Characters[LOC_FANTOM_CHARACTERS + i].id == "") break;
	}
	if(i >= MAX_CHARS_IN_LOC)
	{
		for(i = 0; i < MAX_CHARS_IN_LOC; i++)
		{
			if(!IsEntity(&Characters[LOC_FANTOM_CHARACTERS + i])) break;
		}
		if(i >= MAX_CHARS_IN_LOC) i = 0;
	}
	ref chr = &Characters[LOC_FANTOM_CHARACTERS + i];

	//Заполняем поля персонажа
	chr.id = "Location fantom character <" + i + ">";
	chr.index = LOC_FANTOM_CHARACTERS + i;
	//address
	if(IsEntity(loadedLocation) != true)
			chr.location = "none";
	else	chr.location = loadedLocation.id;
	chr.location.group = "";
	chr.location.locator = "";
	chr.location.from_sea = "";
	chr.location.fantom = "1";
	//model
	if(model != "") chr.model = model;
	else chr.model = "man1"; //TODO: ???
	chr.model.entity = "NPCharacter";
	chr.model.animation = ani;
	// fix -->
    if (chr.model.animation == "towngirl" || chr.model.animation == "towngirl2")
    {
       chr.model.height = 1.75;
	   chr.sex = "Woman";
    }
    else
    {
	   chr.model.height = 1.8;
	   chr.sex = "man";
	}
	// fix <--
	// AlexBlade Настройкп драугров
	if(CheckAttribute(chr, "model"))
	{
		if (StrStartsWith(chr.model, "draugr"))
		{
			chr.Ghost = 0.6;
			chr.sex = "skeleton";
		}
		else if (StrStartsWith(chr.model, "skel"))
		{
			chr.skeleton = "1";
			chr.sex = "skeleton";
		}
	}
	chr.FaceId = "0";
	chr.headModel = "h_" + chr.model;
	FaceMaker(chr);
	//game params
 	CalculateAppropriateSkills(chr);
    SetFantomHP(chr);
	chr.money = 100 + rand(500);
	chr.reputation = 10 + rand(70);
	chr.skill.freeskill = 0;
	chr.experience = 0;
	chr.spyglass.itemID = COMMON_SPYGLASS;
	//Quest data
	chr.Dialog.CurrentNode = "First time";
	chr.Dialog.TempNode = chr.Dialog.CurrentNode;
	chr.quest.meeting = "0";
	chr.quest = "True";
	//blade
	//GiveItem2Character(chr, BLADE_SABER); //boal потом дадим!
	//chr.equip.blade = BLADE_SABER;
    //  boal не нужно тут - будет выдан в LAi_NPC_Equip с учётом сложности и ранга  GiveItem2Character(chr, GUN_COMMON);
	//chr.equip.gun = GUN_COMMON;
    TakeNItems(chr,"potion1", Rand(4)+1);
	//nation
	int nat = GetLocationNation(loadedLocation);
	if(nat >= 0) chr.nation = nat;
	else		 chr.nation = pchar.nation;
	//name
	SetRandomNameToCharacter(chr);
	
	//Логинем персонажа в локацию
	chr.chr_ai.type    = LAI_DEFAULT_TYPE;
	chr.chr_ai.tmpl    = LAI_DEFAULT_TEMPLATE;
	chr.chr_ai.group   = LAI_DEFAULT_GROUP;
	chr.chr_ai.alarmreact = LAI_DEFAULT_ALARMREACT;
	chr.chr_ai.grpalarmr  = LAI_DEFAULT_GRPALARMR;
	//chr.chr_ai.hp      = LAI_DEFAULT_HP;
	//chr.chr_ai.hp_max  = LAI_DEFAULT_HP_MAX;
	chr.chr_ai.gun.charge  = LAI_DEFAULT_CHARGE;
	chr.chr_ai.musket.charge  = LAI_DEFAULT_CHARGE;
	chr.chr_ai.FencingType  = "Fencing"; //fix
	//chr.chr_ai.energy = LAI_DEFAULT_ENERGY;
	SetEnergyToCharacter(chr); // boal
	if(LAi_numloginedcharacters >= MAX_CHARS_IN_LOC)
	{
		Trace("LAi_CreateFantomCharacter -> many logined characters in location > " + MAX_CHARS_IN_LOC);
		return chr;
	}
	LAi_AddLoginedCharacter(chr);
	// boal del lag Event("Fantom_FillSkills", "a", chr);
	if(!CreateCharacter(chr))
	{
		Trace("LAi_CreateFantomCharacter -> CreateCharacter return false");
		return chr;
	}
	//Поставим персонажа на локатор
	if(group == "")
	{
		group = "goto";
		locator = "";
	}
	if(locator == "")
	{
		//Выбираем дальний локатор
		locator = LAi_FindNPCLocator(group);
	}
	chr.location.group = group;
	chr.location.locator = locator;
	if(SendMessage(chr, "lss", MSG_CHARACTER_ENTRY_TO_LOCATION, group, locator) == false)
	{
		Trace("LAi_CreateFantomCharacter -> can't teleportation character to <" + group + "::" + locator + ">");
	}
	return chr;
}
// boal
string LAi_FindNPCLocator(string group)
{
    string  locator = "";
	//Выбираем дальний локатор
	float posX, posY, posZ;
	posX = 0.0; posY = 0.0; posZ = 0.0;
	
	ref  MnChar = GetMainCharacter();

	if(GetCharacterPos(MnChar, &posX, &posY, &posZ))
	{
		// boal -->
		if (sti(MnChar.GenQuestFort.FarLocator) == true)
		{
			locator = LAi_FindFarFreeLocator(group, posX, posY, posZ);
		}
		else
		{
			locator = LAi_FindNearestFreeLocator(group, posX, posY, posZ);  // ближайший
            if(locator == "")
			{
				locator = LAi_FindRandomLocator(group);
			}
		}
		if(locator == "")
		{
			locator = LAi_FindFarLocator(group, posX, posY, posZ);
			if(locator == "")
			{
				locator = LAi_FindRandomLocator(group);
			}
		}
	}
	else
	{
		locator = LAi_FindRandomLocator(group);
	}
	return locator;
}

object lai_questdelays;
string LAi_QuestDelay(string quest, float delayTime)
{
	int num = GetAttributesNum(&lai_questdelays);
	string atr = "e";
	for(int i = 0; i < num + 10; i++)
	{
		atr = "e" + i;
		if(!CheckAttribute(&lai_questdelays, atr)) break;
		if (lai_questdelays.(atr).quest == quest) break; // boal Это уже сущ квест, нам нужно его переназначить
	}
	lai_questdelays.(atr) = delayTime;
	lai_questdelays.(atr).quest = quest;
	
	return atr; //boal
}
//boal -->
void LAi_MethodDelay(string quest, float delayTime)
{
	string atr = LAi_QuestDelay(quest, delayTime);
	lai_questdelays.(atr).method = true;
}
// boal <--
void LAi_QuestDelayProcess(float dltTime)
{
	string atr;
	int i;
	int num = GetAttributesNum(&lai_questdelays);
	//Обсчитываем времена
	for(i = 0; i < num; i++)
	{
		atr = GetAttributeName(GetAttributeN(&lai_questdelays, i));
		lai_questdelays.(atr) = stf(lai_questdelays.(atr)) - dltTime;
	}
	//Проверяем исполнение и вызываем обработку
	for(i = 0; i < num; i++)
	{
		atr = GetAttributeName(GetAttributeN(&lai_questdelays, i));
		if(atr == "root")
		{
			Trace("LAi_QuestDelayProcess -> invalide attibute field: root!!!");
			continue;
		}
		float time = stf(lai_questdelays.(atr));
		if (time <= 0)
		{
			string quest = lai_questdelays.(atr).quest;
			if (CheckAttribute(&lai_questdelays, atr + ".method"))
			{
                DeleteAttribute(&lai_questdelays, atr);
                call quest();
			}
			else
			{
                DeleteAttribute(&lai_questdelays, atr);
                CompleteQuestName(quest, "");
			}
			i = -1;
			num = GetAttributesNum(&lai_questdelays);
		}
	}
}

void LAi_ChangeReputation(aref chr, int repPoints)
{
	if(chr.reputation != "None")
	{
		if(chr.reputation != "")
		{
			int reput = sti(chr.reputation) + repPoints;
			if(reput < REPUTATION_MIN) reput = REPUTATION_MIN;
			if(reput > REPUTATION_MAX) reput = REPUTATION_MAX;
			chr.reputation = reput;
		}
	}

}

void LAi_CheckCharacterID(aref chr)
{
	SendMessage(chr, "ss", "CheckID", chr.id);
}

void LAi_SetDefaultStayAnimation(aref chr)
{
	if(IsEntity(chr))
	{
		BeginChangeCharacterActions(chr);
		SetDefaultStayIdle(chr);
		SetDefaultNormWalk(chr);
		SetDefaultFight(chr);
		SetDefaultDead(chr);
		SetDefaultFightDead(chr);
		EndChangeCharacterActions(chr);
	}
}

void LAi_SetDefaultDead(aref chr)
{
	if(IsEntity(chr))
	{
		BeginChangeCharacterActions(chr);
		SetDefaultDead(chr);
		EndChangeCharacterActionsBlend(chr);
	}
}

void LAi_SetAfraidDead(aref chr)
{
	if(IsEntity(chr))
	{
		BeginChangeCharacterActions(chr);
		SetAfraidDead(chr);
		EndChangeCharacterActionsBlend(chr);
	}
}

void LAi_SetDefaultSitAnimation(aref chr)
{
	if(IsEntity(chr))
	{
	    // если уже сидим то анимацию не меняем
        if (CheckAttribute(chr, "actions.dead.d1") && chr.actions.dead.d1 == "Sit_Death") return;

		BeginChangeCharacterActions(chr);
		if (CheckAttribute(chr, "nonTable")) SetDefaultSit2Idle(chr);
		else SetDefaultSitIdle(chr);
		SetDefaultSitDead(chr);
		EndChangeCharacterActions(chr);
	}
}

void LAi_SetHuberSitAnimation(aref chr)
{
	if(IsEntity(chr))
	{
		BeginChangeCharacterActions(chr);
		SetHuberAnimation(chr);	
		SetDefaultSitDead(chr);
		EndChangeCharacterActions(chr);
	}
}

void LAi_SetDefaultLayAnimation(aref chr)
{
	if(IsEntity(&chr))
	{
		chr.chr_ai.type.mode = "lay";
		BeginChangeCharacterActions(chr);
		chr.actions.idle.i1		    = "Lay_1";
		chr.actions.HitNoFight	    = "Lay_1";
		chr.actions.hit_attack.h1   = "Lay_1";
		chr.actions.hit_attack.h2   = "Lay_1";
		chr.actions.hit_attack.h3   = "Lay_1";
		chr.actions.hit_feint 		= "Lay_1";
		chr.actions.hit_parry 		= "Lay_1";
		chr.actions.hit_round 		= "Lay_1";
		chr.actions.hit_shot  		= "Lay_1";
		chr.actions.aim_hit1   		= "Lay_1";
		chr.actions.aim_hit2   		= "Lay_1";
		chr.actions.fightidle.i1    = "Lay_1";
		chr.actions.fightdead.d1    = "Lay_1";
		chr.actions.dead.d1		    = "Lay_1";
		EndChangeCharacterActionsBlend(chr);
	}
}

//Вывести экран в темноту, выполнить квест questFadeOut, вернуть всё обратно, выполнить квест questFadeIn
object LAi_QuestFader;
void LAi_Fade(string questFadeOut, string questFadeIn)
{
	if(questFadeOut != "") LAi_QuestDelay(questFadeOut, 0.55);
	if(questFadeIn != "") LAi_QuestDelay(questFadeIn, 1.10);
	
	if(IsEntity(&LAi_QuestFader))
	{
		Trace("LAi_Fade -> previous fade operation not ended!");
		return;
	}
	//Fader
	SetEventHandler("FaderEvent_EndFade", "LAi_FadeEndFadeOut", 0);
	SetEventHandler("FaderEvent_EndFadeIn", "LAi_FadeEndFadeIn", 0);
	CreateEntity(&LAi_QuestFader, "fader");
	SendMessage(&LAi_QuestFader, "lfl", FADER_OUT, 0.5, false);
	LAi_QuestFader.oldSaveState = InterfaceStates.Buttons.Save.enable;
	InterfaceStates.Buttons.Save.enable = 0;
}

void LAi_FadeEndFadeOut()
{
	DelEventHandler("FaderEvent_EndFade", "LAi_FadeEndFadeOut");
	SendMessage(&LAi_QuestFader, "lfl", FADER_IN, 0.5, true);
}

void LAi_FadeEndFadeIn()
{
	DelEventHandler("FaderEvent_EndFadeIn", "LAi_FadeEndFadeIn");
	InterfaceStates.Buttons.Save.enable = LAi_QuestFader.oldSaveState;
}

void LAi_FadeEx(float f_start, float f_duration, float f_end, string questFadeOut, string questFadeDuration, string questFadeIn)
{
	if(questFadeOut != "") DoQuestFunctionDelay(questFadeOut, f_start);
	if(questFadeDuration != "") DoQuestFunctionDelay(questFadeDuration, f_start + f_duration);
	if(questFadeIn != "") DoQuestFunctionDelay(questFadeIn, f_start + f_duration + f_end);
	
	if(IsEntity(&LAi_QuestFader))
	{
		Trace("LAi_Fade -> previous fade operation not ended!");
		return;
	}
	//Fader
	pchar.FadeEx.End = f_end;
	CreateEntity(&LAi_QuestFader, "fader");
	SendMessage(&LAi_QuestFader, "lfl", FADER_OUT, f_start, false);
	DoQuestFunctionDelay("LAi_FadeEx_end", f_start + f_duration);
}

void LAi_FadeEx_end(string qName)
{
	float f_end = pchar.FadeEx.End;
	SendMessage(&LAi_QuestFader, "lfl", FADER_IN, f_end, true);
}

//Вывести экран в темноту, через указанное время вернуть
void LAi_FadeDelay(float _delayTime, string sPath)
{
    pchar.GenQuest.CallFunctionParam = "FadeDelay";
    DoQuestCheckDelay("CallFunctionParam", _delayTime);
	//Fader
	CreateEntity(&LAi_QuestFader, "fader");
	//SendMessage(&LAi_QuestFader, "ls", FADER_PICTURE0, "interfaces\card_desk.tga");
	SendMessage(&LAi_QuestFader, "ls", FADER_PICTURE0, sPath);
	SendMessage(&LAi_QuestFader, "lfl", FADER_OUT, 0.5, false);
	LAi_QuestFader.oldSaveState = InterfaceStates.Buttons.Save.enable;
	InterfaceStates.Buttons.Save.enable = 0;
}
void FadeDelay()    // относится к методу выше.
{
	LAi_FadeEndFadeIn();
	LAi_FadeEndFadeOut();
}

//Есть ли оружие у персонада
bool LAi_IsSetBale(aref chr)
{
	return (SendMessage(chr, "ls", MSG_CHARACTER_EX_MSG, "IsSetBalde") != 0);
}

//В режиме боя
bool LAi_IsFightMode(aref chr)
{
//	if ((bLandInterfaceStart) && CheckAttribute(chr, "equip.blade"))
	// fix для Даньки без сабли, но с мушкетом =>
	if ((bLandInterfaceStart) && or(CheckAttribute(chr, "equip.blade"), CheckAttribute(chr, "equip.musket")))
        return (SendMessage(&chr, "ls", MSG_CHARACTER_EX_MSG, "CheckFightMode") != 0);

    return false;
}

//Установить флажёк для востановления хитпойнтов и отношений
#event_handler("EventWorldMapInit", "LAi_SetRestoreStates");
#event_handler(EVENT_SEA_LOGIN, "LAi_SetRestoreStates");
void LAi_SetRestoreStates()
{
	LAi_restoreStates = true;
	// boal 04/02/2005 FIX
	QuestsCheck();
}

#event_handler("EventSGMode", "LAi_GetSGMode");
bool globalSGMode = false;
bool LAi_GetSGMode()
{
	return globalSGMode;
}

bool LAi_IsBottleWork(aref chr, bool type)
{
	if (type && CheckAttribute(chr, "chr_ai.hp_bottle") && stf(chr.chr_ai.hp_bottle) > 0.0)
		return true;
	else
	{
		if (!type && CheckAttribute(chr, "chr_ai.ep_bottle") && stf(chr.chr_ai.ep_bottle) > 0.0)
			return true;
	}
	
	return false;
}

//Найти в близи врагов
bool LAi_CanNearEnemy(aref chr, float radius)
{
	int num = FindNearCharacters(chr, radius, -1.0, -1.0, 0.001, false, false);
	if(num <= 0) return false;
	for(int i = 0; i < num; i++)
	{
		int idx = sti(chrFindNearCharacters[i].index);
		/*if(characters[idx].id == pchar.id)   // TODO boal
		{
			if(LAi_grp_alarmactive == false)
			{
				return false;
			}
		}	  */
		if(LAi_group_IsEnemy(chr, &Characters[idx])) return true;
	}	
	return false;
}

//Проверяем есть ли риск, что открытый контейнер кому-то принадлежит
bool LAi_CanNearOwners(aref chr, float radius)
{
    int num = FindNearCharacters(chr, radius, -1.0, -1.0, 0.001, false, false);
	if (num <= 0) return false;

    ref sld;

    for(int i = 0; i < num; i++)
    {
        makeref(sld, characters[sti(chrFindNearCharacters[i].index)]);
        if (CheckAttribute(sld, "chr_ai.type"))
        {
            //палят только живые ownerЫ и watchBoxesЫ
            if (!LAi_IsDead(sld) && or(sld.chr_ai.type == "owner", CheckAttribute(sld, "watchBoxes"))) return true;
        }
    }
	return false;
}

// boal dead can be searched 14.12.2003 -->
object	Dead_Characters[MAX_CHARS_IN_LOC];
int     Dead_Char_num = 0;

void Dead_AddLoginedCharacter(aref chr)
{
	float	x, y, z;
	ref		chref, rItem;
	aref	arFromChar;
	aref	arToChar;
	float	nLuck   = GetCharacterSkillToOld(GetMainCharacter(), SKILL_FORTUNE);
	string	itemID;
	int		value, count;
	aref	typeRef;
    string  sBullet, sGunPowder;
	//trace("Dead_AddLoginedCharacter nLuck = " + nLuck);
	
	if(GetCharacterPos(chr, &x, &y, &z) == true && Dead_Char_num < MAX_CHARS_IN_LOC)
	{
		Dead_Characters[Dead_Char_num].id = chr.id;
		Dead_Characters[Dead_Char_num].index = chr.index;
		Dead_Characters[Dead_Char_num].name     = chr.name;
		Dead_Characters[Dead_Char_num].lastname = chr.lastname;
		if (CheckAttribute(chr, "faceid")) 
		{
			Dead_Characters[Dead_Char_num].faceid   = chr.faceid;
		}
		chref = &Dead_Characters[Dead_Char_num];
		DeleteAttribute(chref, "items");
		DeleteAttribute(chref, "Money");
		if (IsOfficer(chr) || CheckAttribute(chr, "SaveItemsForDead") || CheckAttribute(chr, "SaveQuestItemsForDead") || CheckAttribute(chr, "KeepItems"))// для офицеров и НПС сохраняем все вещи
		{
			if (CheckAttribute(chr, "SaveQuestItemsForDead"))
			{
				RemoveAllCharacterItems(chr, false);
				DeleteAttribute(chr, "SaveQuestItemsForDead");
			}

			if (CheckAttribute(chr, "KeepItems"))
			{
				RemoveAllCharacterItems(chr, false);
				AddKeepItems(chr);
			}

		    chref.Money = chr.Money;
            makearef(arToChar, chref.items);
            makearef(arFromChar, chr.items);
	        CopyAttributes(arToChar, arFromChar);
	        DeleteAttribute(chref,"items.unarmed"); // 18.06.05 убираем безоружность с трупа офицера
	        DelBakSkillAttr(pchar); // boal оптимизация скилов
	        ClearCharacterExpRate(pchar);
	        DeleteAttribute(chr, "SaveItemsForDead");// убрать чтоб не было случайно потом
	
			// Генерим предметы
			for(value = 0; value < ITEMS_QUANTITY; value++)
			{
				itemID = Items[value].ID;
				
				if(IsGenerableItem(itemID) && CheckCharacterItem(chr, itemID))
				{
					count = GetCharacterItem(chr, itemID);
					RemoveItems(chr, itemID, count); // Забираетм обычные
					GenerateAndAddItems(chr, itemID, count); // Даем сгенеренные
				}
			}
	    }
	    else
	    {
		    // матрос с ЧЖ -->
		    if (CheckAttribute(chr, "GhostShipCrew"))
		    {
                //TakeNItems(chref, "Coins", Rand(9) + 3);
                // обыск скелетов давал вылет, даем сразу в ГГ
                TakeNItems(pchar, "Coins", Rand(9) + 3);
                Log_Info(StringFromKey("InfoMessages_84"));
		    }
		    else
		    // матрос с ЧЖ <--
		    {
		    	// evganat - энциклопедия
				if (!ENCYCLOPEDIA_DISABLED && CheckAttribute(chr, "encyclopedia"))
				{
					chref.encyclopedia.tome = chr.encyclopedia.tome;
					chref.encyclopedia.page = chr.encyclopedia.page;
				}
				
				if (CheckAttribute(chr, "SaveMoneyForDead"))
				{
					chref.Money = chr.Money;
				}
				else
				{
					if (makeint(nLuck + 0.5) > rand(15))
					{
						chref.Money = rand(9) + rand(makeint(nLuck))*5 + rand(makeint(nLuck))*20;
					}
				}
				
    		    // вернём саблю и пистоль -->
    		    if(CheckAttribute(chr, "equip.blade"))
				{
					if(rand(MOD_SKILL_ENEMY_RATE + 5) == 1 && chr.equip.blade != "unarmed") // 20% for 3+2=5
					{
						rItem = ItemsFromID(chr.equip.blade);
						if(CheckAttribute(rItem,"quality") && !HasStrEx(rItem.quality, "excellent,unique", "|")) // ugeen --> на обычных трупах топовое оружие не даем !!!
						{	// Даем трупу сгенеренное оружие
							AddItems(chref, GetGeneratedItem(chr.equip.blade), 1);
						}	
					}
				}
				bool bGun = CheckAttribute(chr, "equip.gun");
				bool bMus = CheckAttribute(chr, "equip.musket");
				if (bGun || bMus)
				{
					if (rand(MOD_SKILL_ENEMY_RATE + 10) == 2)
					{
						if (bGun)
						{
							rItem = ItemsFromID(chr.equip.gun);
							if (CheckAttribute(rItem, "quality") && !HasStrEx(rItem.quality, "excellent,unique", "|")) // ugeen --> на обычных трупах топовое оружие не даем !!!
								GiveItem2Character(chref, chr.equip.gun);
						}

						if (bMus)
						{
							rItem = ItemsFromID(chr.equip.musket);
							if (CheckAttribute(rItem, "quality") && !HasStrEx(rItem.quality, "excellent,unique", "|")) // ugeen --> на обычных трупах топовое оружие не даем !!!
								GiveItem2Character(chref, chr.equip.musket);
						}

						if (chr.model.animation != "mushketer") //с мушкетеров пуль меньше, слишком у них их много - халява
						{
                            sBullet = LAi_GetCharacterBulletType(chr, GUN_ITEM_TYPE);
                            sGunPowder = LAi_GetCharacterGunpowderType(chr, GUN_ITEM_TYPE);
							TakeNItems(chref, sBullet, GetCharacterItem(chr, sBullet));// boal gun bullet													
							if(sGunPowder != "")
							{
								AddItems(chref, sGunPowder, GetCharacterItem(chr, sGunPowder)); // 21.03.09 Warship fix Порох
							}
						}
						else
						{
                            sBullet = LAi_GetCharacterBulletType(chr, MUSKET_ITEM_TYPE);
                            sGunPowder = LAi_GetCharacterGunpowderType(chr, MUSKET_ITEM_TYPE);
							TakeNItems(chref, sBullet, makeint(GetCharacterItem(chr, sBullet) * 0.5)); // boal gun bullet
							if(sGunPowder != "")
							{
								AddItems(chref, sGunPowder, makeint(GetCharacterItem(chr, sGunPowder) * 0.5)); // 21.03.09 Warship fix Порох
							}
						}
					}
				}
    		    // вернём саблю и пистоль <--

                //fill box with new items
                int j, howI;
                ref    itm;
                string name = "";
                string  sModel = chr.model;
                howI = 0;

                // Определение набора генерируемого лута -->
				// Типы: Solder < Warrior < Officer; Citizen, Citizen_f, Monster. Конкретный список в InitItemsRarity
				// GetCharType используется для стастистики, поэтому в общем случае желательно определить лут без неё
				// Например, у офицеров должен быть лут Officer, а в статистику идти как Solder
                if (chr.sex != "man")
                {
					name = "Citizen_f";
					if(CheckAttribute(chr, "PGGAi.IsPGG") || CheckAttribute(chr, "Payment"))
						name = "Warrior";	//Для Данек
    		    }
    		    else
    		    {
                    if (HasStr(sModel, "off_"))
	    		        name = "Officer";
    		    }
                if (name == "") name = GetCharType(chr);
            	// <-- Определение набора генерируемого лута
				
				// ItemDeadStartCount для небольшой оптимизации, чтобы не смотреть на предметы,
				// не использующиеся в InitItemsRarity()
                for (j = ItemDeadStartCount; j < ITEMS_QUANTITY; j++) 
    			{
					if (howI >= (11 - MOD_SKILL_ENEMY_RATE))
					{
					   break;
					}
					makeref(itm,Items[j]);
					if (CheckAttribute(itm, name))
					{
						makearef(typeRef, itm.(name));
                        //attrName = name+".rare";
                        if (!CheckAttribute(typeRef, "rare"))
						{
							trace("Dead_AddLoginedCharacter error: Не найден атрибут RARE для предмета " + itm.id + " тип " + name);
							Log_TestInfo("Dead_AddLoginedCharacter error: Не найден атрибут RARE для предмета " + itm.id + " тип " + name);
						}
						else
						{
							if (stf(typeRef.rare) <= 0.0)
								continue;
						}

                        if (rand(1000) < (((stf(typeRef.rare) + stf(typeRef.rare)*nLuck / 20.0) / makefloat(MOD_SKILL_ENEMY_RATE))*930.0))
                        {
                            value = sti(typeRef.min);
                            value = value+rand(sti(typeRef.max) - value);
                            itemID = itm.id;
							chref.items.(itemID) = value;
							howI++;
						}
					}
    			}
			}
			// заполнили по списку
	    }
		Dead_Characters[Dead_Char_num].px = x;
		Dead_Characters[Dead_Char_num].pz = z;
	    Dead_Char_num++;
	}
}
void Dead_DelLoginedCharacter(aref chr)
{
	aref arToChar;
	aref arFromChar;
	ref c1, c2;
    for(int i = 0; i < Dead_Char_num; i++)
	{
		if(CheckAttribute(chr, "index") && Dead_Characters[i].index == chr.index)
		{
            Dead_Characters[i].px = 30000; // локация -2000 до 2000
			Dead_Characters[i].pz = 30000;
		}		
	}
	if(Dead_Char_num < 0) Dead_Char_num = 0;
}

int Dead_FindCloseBody()
{
	ref mainChr = GetMainCharacter();
	int dchr_index = -1;
	float x, y, z;
	float x1, y1, z1, rd, min_rd = 100; // 100 - is super max
	GetCharacterPos(mainChr, &x, &y, &z);
	
	if (GetBan("Looting"))
		return -1;
	
    for(int i = 0; i < Dead_Char_num; i++)
	{
	    x1 = Dead_Characters[i].px;
		z1 = Dead_Characters[i].pz;
		rd = sqrt(sqr(x1 - x) + sqr(z1 - z));
		if (rd < 1.8)
		{
		    if (min_rd > rd)
		    {
		        min_rd = rd;
                dchr_index = i;
		    }
		}
	}
	return dchr_index;
}

// Приоритет у непустых трупов
int Dead_FindCloseBodyExt(ref isEmpty)
{
    isEmpty = true;
    aref arItems;
    bool bLoot, bOk;

	int dchr_index = -1;
	float x, y, z;
	float x1, y1, z1, rd, min_rd = 100;
	GetCharacterPos(pchar, &x, &y, &z);

    if (GetBan("Looting"))
        return -1;

    for(int i = 0; i < Dead_Char_num; i++)
	{
	    x1 = Dead_Characters[i].px;
		z1 = Dead_Characters[i].pz;
		rd = sqrt(sqr(x1 - x) + sqr(z1 - z));
		if (rd < 1.8)
		{
            makearef(arItems, Dead_Characters[i].items);
            bOk = CheckAttribute(&Dead_Characters[i], "money") && sti(Dead_Characters[i].money) > 0;
            bLoot = GetAttributesNum(arItems) > 0 || bOk;
			if(bLoot)
			{
				if(rd < min_rd || isEmpty)
				{
					min_rd = rd;
					dchr_index = i;
					isEmpty = false;
				}
			}
			else if(isEmpty && rd < min_rd)
			{
				min_rd = rd;
				dchr_index = i;
			}
		}
	}
	return dchr_index;
}

void Dead_OpenBoxProcedure()
{
	ref chr = GetMainCharacter();
	int dchr_index;
    ref deadCh;
//    dchr_index = Dead_FindCloseBody();
    bool isEmpty;
    dchr_index = Dead_FindCloseBodyExt(&isEmpty);
    if (dchr_index == -1) return;
    
	deadCh = &Dead_Characters[dchr_index];

    if (isEmpty)
    {
        // Дубль квестовых триггеров из интерфейса:
        ShipSituation_SetQuestSituation(ShipSituation_0);
        // Вывести лог, убрать труп
        Notification(GetConvertStr("NoLootCorpse" + rand(20), "ReactionsTexts.txt"),"x");
        Dead_DelLoginedCharacter(deadCh);
        return;
    }

	Dead_LaunchCharacterItemChange(deadCh);
}
void Dead_LaunchCharacterItemChange(ref chref)
{
	if(procInterfacePrepare(INTERFACE_ITEMSBOX))
	{
		nPrevInterface = -1;
		CurrentInterface = INTERFACE_ITEMSBOX;
		aref charef; makearef(charef,chref);
		InitInterface_RS(Interfaces[CurrentInterface].IniFile,&charef, "DeadMan");
	}
}

// boal dead can be searched 14.12.2003 <--

void MakePoisonAttack(aref attack, aref enemy)
{
	if (!CheckAttribute(enemy, "chr_ai.poison"))
	{
		if (enemy.index == GetMainCharacterIndex()) Log_SetStringToLog(XI_ConvertString("You've been poisoned"));
		else Log_SetStringToLog(GetFullName(enemy) + XI_ConvertString("is poisoned"));
	}
	//Отравляем персонажа
	float poison = 0.0;
	if(CheckAttribute(enemy, "chr_ai.poison"))
	{
		poison = stf(enemy.chr_ai.poison);
		if(poison < 1.0) poison = 1.0;
	}
	enemy.chr_ai.poison = poison + 30 + rand(20);
}

void MakePoisonAttackCheckSex(aref attacked, aref enemy)
{
	if (enemy.sex == "skeleton" || enemy.sex == "crab")
	{
		if (rand(1000) < 150) MakePoisonAttack(enemy, attacked);
	}
}

string LAi_FindFreeRandomLocator(string group)
{
	if(IsEntity(loadedLocation) != true) return "";
	string at = "locators." + group;
	if(CheckAttribute(loadedLocation, at) == 0) return "";
	aref grp;
	makearef(grp, loadedLocation.(at));
	int num = GetAttributesNum(grp);
	if(num <= 0) return "";
	int base = rand(num - 1);
	if (Get_My_Cabin() == pchar.location && base == 0) return ""; //HardCoffe чтобы не садились на капитанское кресло
	for(int i = 0; i < num; i++)
	{
		int index = base + i;
		if(index >= num)
		{
			index = index - num;
		}
		aref loc = GetAttributeN(grp, index);
		float lx = stf(loc.x);
		float ly = stf(loc.y);
		float lz = stf(loc.z);
		
		if(CheckAttribute(&TEV, "place_check"))
		{
			string aName = GetAttributeName(loc);
			if(TEV.place_check == "Villemstad")
			{
				if(aName == "patrol1" || aName == "goto19") continue;
			}
			//...
		}
		
		if(CheckLocationPosition(loadedLocation, lx, ly, lz))
		{
			return GetAttributeName(GetAttributeN(grp, index));
		}
	}
	return "";
}

bool LAi_CheckLocatorFree(string _group, string _locator)
{
	if(!IsEntity(loadedLocation)) return false;	
	string at = "locators." + _group + "." + _locator;
	if(!CheckAttribute(loadedLocation, at)) return false;
	aref grp;
	makearef(grp, loadedLocation.(at));
	float lx = stf(grp.x);
	float ly = stf(grp.y);
	float lz = stf(grp.z);
	bool ok = CheckLocationPosition(loadedLocation, lx, ly, lz);
	if(CheckAttribute(&TEV, "sitting") && !ok) //Если мы садимся, то не должно учитывать нахождение ГГ внутри локатора
	{
		ok = true;
		ref chrTarget;
		int iTemp;
		int num = FindNearCharacters(pchar, 4.0, -1.0, -1.0, 0.001, false, true);
		for(int i = 0; i < num; i++)
		{
			iTemp = chrFindNearCharacters[i].index;
			chrTarget = &characters[iTemp];
			if(IsCharacterInLocator(chrTarget, "sit", TEV.sitting)) ok = false;
		}
		DeleteAttribute(&TEV, "sitting");
	}
	return ok;
}

bool LAi_IsLocatorFree(string _group, string _locator, float chrRad)
{	//HardCoffee функция определяет соприкасается ли радиус локатора с радиусом персонажей на локации
	//гибкая настройка как радиуса локатора, так и радиуса персонажа
	if(!IsEntity(loadedLocation)) return false;
	string at = "locators." + _group + "." + _locator;
	if(!CheckAttribute(loadedLocation, at)) return false;

	float locRad = 1.0;
	if (CheckAttribute(loadedLocation, "locators_radius."+_group+"."+_locator))
		locRad = loadedLocation.locators_radius.(_group).(_locator);

	return SendMessage(loadedLocation, "lfffff", MSG_LOCATION_ISLOCATORFREE,
		stf(loadedLocation.(at).x), stf(loadedLocation.(at).y), stf(loadedLocation.(at).z), locRad, chrRad);
}
void LaunchBlood(aref chr, float addy, bool isBig, string DamageType)
{
	float x, y, z;
	GetCharacterPos(chr, &x, &y, &z);
	
	if (loadedLocation.type == "underwater")
	{
		y = y + 0.9;
		CreateParticleSystem("bloodUnderwater", x, y, z, 0,1.0,0,0);
	}
	else
	{
		y = y + addy;
		if(isBig == true)
		{
			if (DamageType == "fire")
			{
				if (rand(1))
					CreateParticleSystem("blood_big", x, y, z, 0,1.0,0,0);
				else
					CreateParticleSystem("blood_massshoot_teho", x, y, z, 0,1.0,0,0);
			}
			else
				CreateParticleSystem("blood_big", x, y, z, 0,1.0,0,0);
		}
		else
		{
			if (DamageType == "fire")
				CreateParticleSystem("blood_fire" + (1 + rand(2)) + "_teho", x, y, z, 0,1.0,0,0);
			else
				CreateParticleSystem("blood", x, y, z, 0,1.0,0,0);
		}
		SendMessage(loadedLocation, "lsfff", MSG_LOCATION_EX_MSG, "AddBlood", x,y,z);
	}
}

void LaunchAmmoBlast(aref chr, string sAmmo)
{
	float x, y, z;
	GetCharacterPos(chr, &x, &y, &z);
	y = y + 0.5;
	CreateParticleSystem("blast_inv", x, y, z, 0, 1.0, 0, 0);
	
	if (sAmmo == "petard")
	{
		y = y + 0.1;
		CreateParticleSystem("blast_inv", x, y, z, 0, 1.0, 0, 0);
		y = y + 0.9;
		CreateParticleSystem("blast_inv", x, y, z, 0, 1.0, 0, 0);
		Play3DSound("petard", x, y, z);
	}
	else
	{
		CreateParticleSystem("blast_dirt_teho", x, y, z, 0, 1.0, 0, 0);
		Play3DSound("grenade", x, y, z);
	}
}

void LAi_Explosion(ref chr, int damage)
{
	float x, y, z;						
	GetCharacterPos(chr, &x, &y, &z);
	CreateParticleSystemX("blast", x, y, z, x, y, z, 0);	
	CreateParticleSystemX("fort_fire", x, y, z, x, y, z, 5);
	CreateParticleSystemX("blood_shoot_teho", x, y, z, x, y, z, 0);	
	CreateParticleSystemX("cancloud_fire_teho", x, y, z, x, y, z, 20);
	
	PlayStereoSound("Sea Battles\vsriv_orud_00" + (1 + rand(2)) + ".wav");

	int num = FindNearCharacters(chr, 3.0, -1.0, -1.0, 0.001, false, true);

	for(int j = 0; j <= num; j++)	
	{
		int idx = sti(chrFindNearCharacters[j].index);	
		ref findCh;
		findCh = GetCharacter(idx);	
    
		float dist = -1.0;
		if(GetCharacterDistByChr3D(chr, findCh, &dist) && dist < 4)
		{
			LAi_ApplyCharacterDamage(findCh, damage, "fire");		
			if (sti(LAi_GetCharacterHP(findCh)) < damage + 1) 
			{ 
				if(findCh.chr_ai.group != LAI_GROUP_PLAYER)  
				{
					Lai_KillCharacter(findCh);
				} 
				else
				{
					findCh.chr_ai.hp = 10;
				} 
			}
		}
	}	

	LAi_ApplyCharacterDamage(chr, damage, "fire");

	if (sti(LAi_GetCharacterHP(chr)) < damage + 1) Lai_KillCharacter(chr);
}

// AlexBlade Tutorials -->
bool CheckParryTutorial(aref attack, string attackType)
{
	if (!CheckAttribute(&TEV, "TutorialInfo.FightTutorials.BloodPrologue_Parry"))
		return false;

	int chrTmpIdx = LAi_tmpl_fight_GetTarget(attack);
	if (chrTmpIdx >= 0 && attackType == "break")
	{
		ref chrTmp = GetCharacter(chrTmpIdx);
		if (IsMainCharacter(chrTmp))
		{
			Tutorial_BloodPrologue_Parry("");
			return true;
		}
	}

	return false;
}
// <--

// Меняет анимации обычной ходьбы на ходьбу с оружием
// Нужна для имитации боевого режима у актёров
void LAi_SetActorReplaceWalkOnFightAnimation(aref chr)
{
	if(IsEntity(chr))
	{
		SetActorReplaceWalkOnFight(chr);
		EndChangeCharacterActions(chr);
	}
}

void SetActorReplaceWalkOnFight(ref character)
{
	string tagMus = "";
	if(LAi_CheckFightMode(character) == 2) tagMus = "_mus";

	int i, j, k, l;
	string tagFightMode = "fight";
	string tagMoveMode;		// "walk", "run" или "sprint"
	string tagDirection;	// "forward", "back", "right", "left", "forward-left", "forward-right", "back-left" или "back-right"
	string tagStep;			// "rstep", "lstep" или ""
	string sAttr, sAnim;
	for(j=0; j<3; j++)	// тип движения
	{
		switch(j)
		{
			case 0:		tagMoveMode = "walk";		break;
			case 1:		tagMoveMode = "run";		break;
			case 2:		tagMoveMode = "sprint";		break;
		}
		for(k=0; k<8; k++)	// направление движения
		{
			if(j == 2 && k > 2)	// в спринте нет других направлений
				continue;

			switch(k)
			{
				case 0:		tagDirection = "forward";			break;
				case 1:		tagDirection = "forward-right";		break;
				case 2:		tagDirection = "forward-left";		break;
				case 3:		tagDirection = "back";				break;
				case 4:		tagDirection = "back-right";		break;
				case 5:		tagDirection = "back-left";			break;
				case 6:		tagDirection = "right";				break;
				case 7:		tagDirection = "left";				break;
			}

			sAttr = tagDirection + "_" + tagMoveMode;
			sAnim = StrConCheck(tagFightMode, " ") + tagDirection + " " + tagMoveMode;
			character.actions.(sAttr) = sAnim;	// выставляем анимацию постоянного движения

			if(j == 0)	// при ходьбе нет инерции и подбора шагов
				continue;

			sAttr = "start_" + tagDirection + "_" + tagMoveMode;
			sAnim = "start " + StrConCheck(tagFightMode, " ") + tagDirection + " " + tagMoveMode;
			character.actions.(sAttr) = sAnim;	// выставляем анимацию разгона

			if(i == 1)	// в боевом режиме нет торможения и подбора шагов
				continue;

			for(l=0; l<3; l++)	// подбор шагов
			{
				switch(l)
				{
					case 0:		tagStep = "";		break;
					case 1:		tagStep = "rstep";	break;
					case 2:		tagStep = "lstep";	break;
				}

				sAttr = "stop_" + tagDirection + "_" + tagMoveMode + StrConCheck("_", tagStep);
				sAnim = "stop " + StrConCheck(tagFightMode, " ") + tagDirection + " " + tagMoveMode + StrConCheck(" ", tagStep);
				character.actions.(sAttr) = sAnim;	// выставляем анимацию торможения
			}
		}
	}

    string tagVert = "";
    for(i=0; i<2; i++)
    {
        if(i == 0)	tagVert = "up";
        else		tagVert = "down";
		for(k=0; k<4; k++)
		{
			switch(k)
			{
				case 0:	tagDirection = "forward";	break;
				case 1:	tagDirection = "back";		break;
				case 2:	tagDirection = "right";		break;
				case 3:	tagDirection = "left";		break;
			}
			sAttr = tagDirection + "_walk_stairs_" + tagVert;
			sAnim = StrConCheck(tagFightMode, " ") + tagDirection + " walk stairs " + tagVert;
			character.actions.(sAttr) = sAnim;
		}
    }
}

// Спасательный круг, если файт мод не сняли напрямую (из-за багов например)
// Срабатывает при выгрузке локации
void DisableLockFightMode_OnUnloadLocation()
{
	if (CheckAttribute(&TEV, "LockFightMode"))
	{
		DeleteAttribute(&TEV, "LockFightMode");
	}
}

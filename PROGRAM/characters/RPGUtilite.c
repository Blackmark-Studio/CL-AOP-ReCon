// 11.08.05 Boal Модуль для новой РПГ системы S.P.E.C.I.A.L
// метод для совместимости с .ИНИ файлом (секция SKILLCHANGER)

// порог ранга
int GetCharacterRankRate(ref _refCharacter)
{
    return 35 - GetCharacterSPECIALSimple(_refCharacter, SPECIAL_I);
}
int GetCharacterRankRateCur(ref _refCharacter)
{
    if(!CheckAttribute(_refCharacter, "rank_exp"))
	{
		_refCharacter.rank_exp = 0;
	}
    return sti(_refCharacter.rank_exp);
}
// прирост НР
int GetCharacterAddHPValue(ref _refCharacter)
{
    int ret = makeint(2 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_E) * 0.55 + 0.5);
	return ret;
}

int GetCharacterBaseHPValue(ref _refCharacter)
{
	int ret = makeint(30.0 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_S)*GetCharacterSPECIALSimple(_refCharacter, SPECIAL_E)*0.5);
	// HPPlus обновит здоровье в любом случае, но на здоровье фантомов пусть не влияет
	return ret;
}

float GetCharEnergy(ref rChar, bool bCurrent)
{
	if (!CheckAttribute(rChar, "chr_ai.energy"))
		SetEnergyToCharacter(rChar);
	
	if (bCurrent)
		return stf(rChar.chr_ai.energy);
	
	return GetCharacterMaxEnergyValue(rChar);
}

float GetCharacterMaxEnergyValue(ref _refCharacter)
{
    float ret = (30.0 + GetCharacterSPECIAL(_refCharacter, SPECIAL_A)*10);
	if (CheckCharacterPerk(_refCharacter, "EnergyPlus"))
	{
  		ret += stf(_refCharacter.rank);
	}
	return ret;
}

float GetCharacterMaxEnergyABSValue(ref _refCharacter)
{
	float ret = (30.0 + GetCharacterSPECIALSimple(_refCharacter, SPECIAL_A)*10);
	if (CheckCharacterPerk(_refCharacter, "EnergyPlus"))
	{
  		ret += stf(_refCharacter.rank);
	}
	return ret;
}

void SetEnergyToCharacter(ref _refCharacter)
{
	_refCharacter.chr_ai.energyMax = GetCharacterMaxEnergyValue(_refCharacter);
	if (!CheckAttribute(_refCharacter, "chr_ai.energy"))
	{
		_refCharacter.chr_ai.energy    = _refCharacter.chr_ai.energyMax;
	}
	else
	{
	    if (sti(_refCharacter.chr_ai.energy) > sti(_refCharacter.chr_ai.energyMax))
	    {
	        _refCharacter.chr_ai.energy    = _refCharacter.chr_ai.energyMax;
	    }
	}
}

int GetCharacterMaxOfficersQty(ref _refCharacter)
{
    return GetCharacterSPECIAL(_refCharacter, SPECIAL_C)*2;
}

int AddCharacterExp(ref _refCharacter,int _exp)
{
	int retVal = false;
	// boal now use AddCharacterExpToSkill

	return retVal;
}

int CalculateExperienceFromRank(int _Rank)
{
	if(_Rank<2) return 0;
	int retVal = 100;//(MakeInt(1000 * pow(_Rank-1,2.3))/1000)*1000;
	return retVal;
}

int GetFreePoints_SelfRate(ref _chref)
{
    return 40 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
}

int GetFreePoints_ShipRate(ref _chref)
{
    return 40 - GetCharacterSPECIALSimple(_chref, SPECIAL_I);
}
/////////////////////////////////////////////////////////////////////////

void SetSelfSkill(ref _refCharacter, int _fl, int _f, int _fh, int _p, int _fr)
{
    _refCharacter.Skill.FencingLight  = _fl;
    _refCharacter.Skill.Fencing       = _f;
    _refCharacter.Skill.FencingHeavy  = _fh;
    _refCharacter.Skill.Pistol        = _p;
    _refCharacter.Skill.Fortune       = _fr;
//    _refCharacter.Skill.Leadership = _ld;
//    _refCharacter.Skill.Sneak      = _sn;
}

void SetShipSkill(ref _refCharacter, int _ld, int _cr, int _ac, int _cn, int _sl, int _re, int _gr, int _de, int _sn)
{
    _refCharacter.Skill.Leadership = _ld;
    _refCharacter.Skill.Commerce   = _cr;
    _refCharacter.Skill.Accuracy   = _ac;
    _refCharacter.Skill.Cannons    = _cn;
    _refCharacter.Skill.Sailing    = _sl;
    _refCharacter.Skill.Repair     = _re;
    _refCharacter.Skill.Grappling  = _gr;
    _refCharacter.Skill.Defence    = _de;
    _refCharacter.Skill.Sneak      = _sn;
}

void SetSPECIAL(ref _refCharacter, int _s, int _p, int _e, int _c, int _i, int _a, int _l)
{
    _refCharacter.SPECIAL.Strength   = _s;
    _refCharacter.SPECIAL.Perception = _p;
    _refCharacter.SPECIAL.Endurance  = _e;
    _refCharacter.SPECIAL.Charisma   = _c;
    _refCharacter.SPECIAL.Intellect  = _i;
    _refCharacter.SPECIAL.Agility    = _a;
    _refCharacter.SPECIAL.Luck       = _l;
}

void SetRandSPECIAL(ref _refCharacter)
{
    SetSPECIAL(_refCharacter,
               (3 + rand(7)),
               (3 + rand(7)),
               (3 + rand(7)),
               (2 + rand(8)),
               (4 + rand(6)),
               (4 + rand(6)),
               (2 + rand(8)));
}

// > Меняет показатели (P)ower (I)nsight (R)eaction (A)llure (T)alent (E)ndurance (S)uccess как угодно, от одного значения до всех подряд; указывать PIRATES можно в любом порядке
// > SetPIRATES(chr, "P7") - установить персу chr только значение (P)ower в 7
// > SetPIRATES(chr, "P10,I3,R10,A3,T3,E10,S3") - установить персу chr значения PIRATES 10,3,10,3,3,10,3
void SetPIRATES(ref chr, string sPirates)
{
	int i, v, s = KZ|Symbol(sPirates, ",");
	string tmp, sym;
	
	for (i = 0; i <= s; i++)
	{
		tmp = GetSubStr(sPirates, ",", i);
		
		if (!HasStrEx(tmp, "P,I,R,A,T,E,S", "|"))
			continue;
		
		sym = GetSymbol(tmp, 0);
		v = sti(FindStringAfterChar(tmp, sym));
		Restrictor(&v, 1, 10);
		
		switch (sym)
		{
			case "P": sym = "Strength"; break;
			case "I": sym = "Perception"; break;
			case "R": sym = "Agility"; break;
			case "A": sym = "Charisma"; break;
			case "T": sym = "Intellect"; break;
			case "E": sym = "Endurance"; break;
			case "S": sym = "Luck"; break;
		}
		
		if (CheckAttribute(chr, "SPECIAL." + sym))
			chr.SPECIAL.(sym) = v;
	}
}

/// влияет только на СПЕЦИАЛ
int ApplayNavyPenalty(ref _refCharacter, string skillName, int sumSkill)
{
    if (IsCompanion(_refCharacter) && GetRemovable(_refCharacter))//пусть будет для компаньонов тоже sti(_refCharacter.index) == GetMainCharacterIndex()) // только для главного, чтоб не тормозить всю игру
    {
        int sailSkill;
        int needSkill;

		//в ГПК не пенальтим
		if (CheckAttribute(_refCharacter, "questTemp.LSC.IgnoreShipStatPenalty"))
			return sumSkill;

        // общее умение навигации
        if (CheckAttribute(_refCharacter, "TempSailing"))
        	sailSkill = _refCharacter.TempSailing;
        else sailSkill = GetSummonSkillFromNameSimple(_refCharacter, SKILL_SAILING);

        int shipClass = GetCharacterShipClass(_refCharacter);
        needSkill = GetShipClassNavySkill(shipClass);

        if (sailSkill < needSkill)
        {
			sailSkill = makeint((needSkill - sailSkill)/10.0 + 0.9); // округление до мах всегда
			sumSkill = sumSkill - sailSkill;
	        if (sumSkill < 1) sumSkill = 1;
        }
    }
    return sumSkill;
}
// пенальти в скилы
int ApplayNavyPenaltyToSkill(ref _refCharacter, string skillName, int sumSkill)
{
    if (IsCompanion(_refCharacter) && GetRemovable(_refCharacter))//пусть будет для компаньонов тоже sti(_refCharacter.index) == GetMainCharacterIndex()) // только для главного, чтоб не тормозить всю игру
    {
        int sailSkill;
        int needSkill;

		//в ГПК не пенальтим
		if (CheckAttribute(_refCharacter, "questTemp.LSC.IgnoreShipStatPenalty"))
			return sumSkill;

		// общее умение навигации
		if (CheckAttribute(_refCharacter, "TempSailing"))
        	sailSkill = _refCharacter.TempSailing;
        else sailSkill = GetSummonSkillFromNameSimple(_refCharacter, SKILL_SAILING);

        int shipClass = GetCharacterShipClass(_refCharacter);
        needSkill = GetShipClassNavySkill(shipClass);

        if (sailSkill < needSkill)
        {
			sailSkill = needSkill - sailSkill;
			sumSkill = sumSkill - sailSkill;
	        if (sumSkill < 1) sumSkill = 1;
        }
    }
    return sumSkill;
}
// с пенальти и вещами +1
int GetCharacterSPECIAL(ref _refCharacter, string skillName)
{
    int skillN;

	skillN = GetCharacterSPECIALSimple(_refCharacter, skillName);

 	skillN = ApplayNavyPenalty(_refCharacter, skillName, skillN);
	
	// evganat - энциклопедия
	if (ENCYCLOPEDIA_DISABLED) return skillN;
	int iBonus = 0;
	switch (skillName)
	{
		case SPECIAL_P:
			if (IsMainCharacter(_refCharacter) || IsCompanion(_refCharacter) || IsCharacterOfficer(_refCharacter))
				iBonus = GetParamPageBonus("Impression");
		break;
		case SPECIAL_L:
			if (IsMainCharacter(_refCharacter) || IsCompanion(_refCharacter) || IsCharacterOfficer(_refCharacter))
				iBonus = GetParamPageBonus("Luck");
		break;
		case SPECIAL_I:
			if(IsMainCharacter(_refCharacter) || IsCompanion(_refCharacter) || IsCharacterOfficer(_refCharacter))
			{
				if(CheckAttribute(pchar, "encyclopedia.full"))
					iBonus = 5;
			}
		break;
	}
	skillN += iBonus;

    return skillN;
}

int GetCharacterSPECIALSimple(ref _refCharacter, string skillName)
{
	if (!CheckAttribute(_refCharacter,"SPECIAL."+skillName) )
    {
        return 3;
    }
	int skillN = sti(_refCharacter.SPECIAL.(skillName));
    // Health
    if (sti(_refCharacter.index) == GetMainCharacterIndex() && MOD_SKILL_ENEMY_RATE > 1) // не халява
    {
        skillN = skillN + GetHealthNum(_refCharacter) - 6; // max -5
    }
    // boal учет вещей -->
    if (IsMainCharacter(_refCharacter) || IsCompanion(_refCharacter) || IsOfficer(_refCharacter))
    {
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "jewelry9", 1);

    	//TO: Konstrush раскомментить по необходимости
		//skillN = skillN + SetCharacterSkillByEquipedItem(_refCharacter, skillName, SPECIAL_C, "suit_3", 1);

/*    	// нельзя  Иначе рекурсия без выхода
    	if (GetItemsWeight(_refCharacter) > GetMaxItemsWeight(_refCharacter))
    	{
  	        skillN -=2;
    	}
    	// boal учет перегруза 19.01.2004 <--*/
	}
	// boal <--
	if (skillN <= 1) skillN = 1;
	if( skillN > SPECIAL_MAX ) skillN = SPECIAL_MAX;

	return skillN;
}


void InitRPGType()
{
    NullCharacter.SPECIALType.Strength = true;
    NullCharacter.SPECIALType.Perception = true;
    NullCharacter.SPECIALType.Endurance = true;
    NullCharacter.SPECIALType.Charisma = true;
    NullCharacter.SPECIALType.Intellect = true;
    NullCharacter.SPECIALType.Agility = true;
    NullCharacter.SPECIALType.Luck = true;
    
    NullCharacter.SelfType.Leadership = true;
	NullCharacter.SelfType.FencingLight = true;
    NullCharacter.SelfType.Fencing = true;
    NullCharacter.SelfType.FencingHeavy = true;
    NullCharacter.SelfType.Pistol = true;
    NullCharacter.SelfType.Fortune = true;
    NullCharacter.SelfType.Sneak = true;
    // остальные корабельные
    NullCharacter.ShipType.Commerce = true;
    NullCharacter.ShipType.Accuracy = true;
    NullCharacter.ShipType.Cannons = true;
    NullCharacter.ShipType.Sailing = true;
    NullCharacter.ShipType.Repair = true;
    NullCharacter.ShipType.Grappling = true;
    NullCharacter.ShipType.Defence = true;

}

bool isSPECIALTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "SPECIALType." + _param);
}

bool isShipTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "ShipType." + _param);
}
bool isSelfTypeSkill(string _param)
{
    return CheckAttribute(&NullCharacter, "SelfType." + _param);
}

string GetRPGText(string _param)
{
    return GetConvertStr(_param, "RPGDescribe.txt");
}

string GetSkillNameByIdx(int idx)
{
    string ret = "";
    
    switch (idx)
    {
        case 1:    ret = SKILL_F_LIGHT;   break;
        case 2:    ret = SKILL_FENCING;   break;
        case 3:    ret = SKILL_F_HEAVY;   break;
        case 4:    ret = SKILL_PISTOL;    break;
        case 5:    ret = SKILL_FORTUNE;   break;
        
        case 6:    ret = SKILL_LEADERSHIP; break;
        case 7:    ret = SKILL_COMMERCE;   break;
        case 8:    ret = SKILL_ACCURACY;   break;
        case 9:    ret = SKILL_CANNONS;    break;
        case 10:   ret = SKILL_SAILING;    break;
        case 11:   ret = SKILL_REPAIR;     break;
        case 12:   ret = SKILL_GRAPPLING;  break;
        case 13:   ret = SKILL_DEFENCE;    break;
        case 14:   ret = SKILL_SNEAK;      break;
        
        case 15:   ret = SPECIAL_S;   break;
        case 16:   ret = SPECIAL_P;   break;
        case 17:   ret = SPECIAL_A;   break;
        case 18:   ret = SPECIAL_C;   break;
        case 19:   ret = SPECIAL_I;   break;
        case 20:   ret = SPECIAL_E;   break;
        case 21:   ret = SPECIAL_L;   break;
    }
    return ret;
}
//  _type   ShipType SelfType  SPECIALType
string GetSkillNameByTRIdx(string _type, int idx)
{
    string ret = "";

	switch (_type)
	{
		case "SelfType" :
		    switch (idx)
		    {
                case 1:    ret = SKILL_LEADERSHIP; break;
				case 2:    ret = SKILL_F_LIGHT;   break;
		        case 3:    ret = SKILL_FENCING;   break;
		        case 4:    ret = SKILL_F_HEAVY;   break;
		        case 5:    ret = SKILL_PISTOL;    break;
		        case 6:    ret = SKILL_FORTUNE;   break;
                case 7:    ret = SKILL_SNEAK;      break;
		    }
		break;
		
		case "ShipType" :
		    switch (idx)
		    {
                case 1:    ret = SKILL_SAILING; break;
				case 2:    ret = SKILL_ACCURACY;   break;
		        case 3:    ret = SKILL_CANNONS;   break;
		        case 4:    ret = SKILL_GRAPPLING;   break;
		        case 5:    ret = SKILL_DEFENCE;    break;
		        case 6:    ret = SKILL_REPAIR;   break;
                case 7:    ret = SKILL_COMMERCE;      break;
		    }
		break;
		
		case "SPECIALType" :
		    switch (idx)
		    {
                case 1:   ret = SPECIAL_S;   break;
		        case 2:   ret = SPECIAL_P;   break;
		        case 3:   ret = SPECIAL_A;   break;
		        case 4:   ret = SPECIAL_C;   break;
		        case 5:   ret = SPECIAL_I;   break;
		        case 6:   ret = SPECIAL_E;   break;
		        case 7:   ret = SPECIAL_L;   break;
		    }
		break;
    }
    return ret;
}
// по имени скила вернуть значение
int GetSkillValue(ref _refCharacter, string _type, string _skillName)
{
    if (CheckAttribute(_refCharacter, _type + "." + _skillName))
    {
        return sti(_refCharacter.(_type).(_skillName));
    }
    return 0;
}

float GetSkillValueExp(ref _refCharacter, string _skillName)
{
    string skillName_exp = _skillName + "_exp";
    if (!CheckAttribute(_refCharacter, "Skill."+skillName_exp))
	{
		_refCharacter.Skill.(skillName_exp) = 0;
	}
    return stf(_refCharacter.Skill.(skillName_exp));
}
int AddSPECIALValue(ref _refCharacter, string _skillName, int _add)
{
    string _type = SPECIAL_TYPE;
    
    if (CheckAttribute(_refCharacter, _type + "." + _skillName))
    {
        _refCharacter.(_type).(_skillName) = sti(_refCharacter.(_type).(_skillName)) + _add;
    }
    else
    {
        _refCharacter.(_type).(_skillName) = _add;
    }
    if (sti(_refCharacter.(_type).(_skillName)) < 1) {_refCharacter.(_type).(_skillName) = 1;}
    if (sti(_refCharacter.(_type).(_skillName)) > SPECIAL_MAX) {_refCharacter.(_type).(_skillName) = SPECIAL_MAX;}
    
    return sti(_refCharacter.(_type).(_skillName));
}

int AddCharacterSkill(ref _chref, string _skill, int _addValue)
{
    string  _skill_exp = _skill + "_exp";

    if (_addValue > 0)
	{
	    if ((sti(_chref.skill.(_skill)) + _addValue) > SKILL_MAX)
	    {
	        _addValue = SKILL_MAX - sti(_chref.skill.(_skill));
	    }
	}
    _chref.skill.(_skill) = sti(_chref.skill.(_skill)) + _addValue;

	if (sti(_chref.skill.(_skill)) < 1)
	{
        _chref.skill.(_skill) = 1;
	}
	if (sti(_chref.skill.(_skill)) > SKILL_MAX )
	{
	    _chref.skill.(_skill) = SKILL_MAX;
	}
	_chref.skill.(_skill_exp) = 0;
	if (_addValue >= 0)
	{
	   ApplayNewSkill(_chref, _skill, _addValue);
	}
	return sti(_chref.skill.(_skill));
}

void AddCharacterSkillDontClearExp(ref _chref, string _skill, int _addValue)
{
    /*if (_addValue > 0)
	{
	    if ((sti(_chref.skill.(_skill)) + _addValue) > SKILL_MAX)
	    {
	        _addValue = SKILL_MAX - sti(_chref.skill.(_skill));
	    }
	} */
	_chref.skill.(_skill) = sti(_chref.skill.(_skill)) + _addValue;

	if (sti(_chref.skill.(_skill)) < 1)
	{
        _chref.skill.(_skill) = 1;
	}
	if (sti(_chref.skill.(_skill)) > SKILL_MAX )
	{
	    _chref.skill.(_skill) = SKILL_MAX;
	}
	if (_addValue >= 0)
	{
	   ApplayNewSkill(_chref, _skill, _addValue);
	}
}

void ApplayNewSkill(ref _chref, string _skill, int _addValue)
{
    // трем кэш
    DeleteAttribute(_chref, "BakSkill." + _skill);
    
	// boal 05.05.04 разделение по группам -->
    if (isSelfTypeSkill(_skill))
    {
       if(CheckAttribute(_chref,"perks.FreePoints_self_exp"))
       {
           _chref.perks.FreePoints_self_exp = sti(_chref.perks.FreePoints_self_exp) + _addValue;
       }
       else
       {	_chref.perks.FreePoints_self_exp = _addValue;
       }
       if (sti(_chref.perks.FreePoints_self_exp) >= GetFreePoints_SelfRate(_chref))
       {
           _chref.perks.FreePoints_self_exp = 0;
           if(CheckAttribute(_chref,"perks.FreePoints_self"))
           {
               _chref.perks.FreePoints_self = sti(_chref.perks.FreePoints_self) + 1;
           }
           else
           {	_chref.perks.FreePoints_self = 1;
           }
           if (or(IsOfficer(_chref), IsCompanion(_chref)) && !CheckAttribute(pchar, "AllSelf"))
           {
                notification(ColorTextLine(StringFromKey("InfoMessages_213", _chref, GetFullName(_chref)), "gold"), "Personal abilities");
                if (IsMainCharacter(_chref))
				{
					DoQuestFunctionDelay("Tutorial_Perk", 1.5);
				}
           }
       }
    }
    else
    {
       if(CheckAttribute(_chref,"perks.FreePoints_ship_exp"))
       {
           _chref.perks.FreePoints_ship_exp = sti(_chref.perks.FreePoints_ship_exp) + _addValue;
       }
       else
       {	_chref.perks.FreePoints_ship_exp = _addValue;
       }
       if (sti(_chref.perks.FreePoints_ship_exp) >= GetFreePoints_ShipRate(_chref))
       {
           _chref.perks.FreePoints_ship_exp = 0;
           if(CheckAttribute(_chref,"perks.FreePoints_ship"))
           {
               _chref.perks.FreePoints_ship = sti(_chref.perks.FreePoints_ship) + 1;
           }
           else
           {	_chref.perks.FreePoints_ship = 1;
           }
           if (or(IsOfficer(_chref), IsCompanion(_chref)) && !CheckAttribute(pchar, "AllShip"))
           {
                notification(ColorTextLine(StringFromKey("InfoMessages_214", _chref, GetFullName(_chref)), "gold"), "Ship abilities");
				if (IsMainCharacter(_chref))
				{
					DoQuestFunctionDelay("Tutorial_Perk", 1.5);
				}
           }
       }
    }
    // boal 05.05.04 разделение по группам <--


    if(!CheckAttribute(_chref, "rank_exp"))
    {
      _chref.rank_exp = 0;
    }
    _chref.rank_exp = sti(_chref.rank_exp) + _addValue;

    if (sti(_chref.rank_exp) >= GetCharacterRankRate(_chref)) // use classic mode - 2 skill = 1 rank
    {
        _chref.rank_exp = 0;
        _chref.rank = sti(_chref.rank) + 1;
        float mhp = LAi_GetCharacterMaxHP(_chref) + GetCharacterAddHPValue(_chref);
        LAi_SetHP(_chref, _chref.chr_ai.hp, mhp);

        if (CheckCharacterPerk(_chref, "EnergyPlus"))
		{
			SetEnergyToCharacter(_chref);
		}

        // сообщение в лог
        if(sti(_chref.index) == GetMainCharacterIndex())
        {
            AddMsgToCharacter(_chref, MSGICON_LEVELUP);
            LA_LevelUp(XI_ConvertString("Level Up"), ""+sti(_chref.rank)+"");
        }
        else
        {
            if(IsOfficer(_chref) || IsCompanion(_chref))
            {
                AddMsgToCharacter(_chref,MSGICON_LEVELUP);
                notification(ColorTextLine(StringFromKey("InfoMessages_212", _chref, GetFullName(_chref)), "gold"), "none");
                PlayStereoSound("interface\new_level.wav");
            }
        }
    }
}
// по специал распередить скилы
void InitStartParam(ref _chref)
{
    int i;
    string  skillName;
    
    ClearCharacterExpRate(_chref);
    
    for (i=1; i<15; i++)
    {
        skillName = GetSkillNameByIdx(i);
        _chref.skill.(skillName) = makeint(MOD_EXP_RATE / GetCharacterExpRate(_chref, skillName) + 0.5);
    }
    LAi_SetHP(_chref, GetCharacterBaseHPValue(_chref), GetCharacterBaseHPValue(_chref));
}
// порог следующего скила (множетель)
float GetCharacterExpRate(ref _chref, string _skill)
{
    string  skill_rate = _skill + "_rate";

    if (!CheckAttribute(_chref, "skill." + skill_rate))
    {
        float  divBy = 1.0;

        switch (_skill)
        {
            case SKILL_F_LIGHT:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.9 + GetCharacterSPECIAL(_chref, SPECIAL_P)*0.1;
            break;
            case SKILL_FENCING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_S)*0.6 + GetCharacterSPECIAL(_chref, SPECIAL_A)*0.4;
            break;
            case SKILL_F_HEAVY:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_S)*0.9 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.1;
            break;
            case SKILL_PISTOL:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.5 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.5;
            break;
            case SKILL_FORTUNE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_L);
            break;
            
            case SKILL_LEADERSHIP:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.1 + GetCharacterSPECIAL(_chref, SPECIAL_C)*0.9;
            break;
            case SKILL_COMMERCE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.8 + GetCharacterSPECIAL(_chref, SPECIAL_C)*0.2;
            break;
            case SKILL_ACCURACY:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.8 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.2;
            break;
            case SKILL_CANNONS:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_I)*0.6 + GetCharacterSPECIAL(_chref, SPECIAL_S)*0.4;
            break;
            case SKILL_SAILING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.2 + GetCharacterSPECIAL(_chref, SPECIAL_I)*0.8;
            break;
            case SKILL_REPAIR:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.2 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.8;
            break;
            case SKILL_GRAPPLING:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_A)*0.7 + GetCharacterSPECIAL(_chref, SPECIAL_I)*0.3;
            break;
            case SKILL_DEFENCE:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_C)*0.5 + GetCharacterSPECIAL(_chref, SPECIAL_E)*0.5;
            break;
            case SKILL_SNEAK:
                divBy = GetCharacterSPECIAL(_chref, SPECIAL_P)*0.5 + GetCharacterSPECIAL(_chref, SPECIAL_L)*0.5;
            break;
        }
        _chref.skill.(skill_rate) = makefloat(MOD_EXP_RATE / divBy);
    }
    return  stf(_chref.skill.(skill_rate));
}

// table service
// table service
string GetReputationName(int reputation)
{
    if(reputation<11)
        return "REPUTATIONT_BAD_4";
    if(reputation<21)
        return "REPUTATIONT_BAD_3";
    if(reputation<31)
        return "REPUTATIONT_BAD_2";
    if(reputation<41)
        return "REPUTATIONT_BAD_1";
    if(reputation<51)
        return "REPUTATIONT_NEUTRAL";
    if(reputation<61)
        return "REPUTATIONT_GOOD_1";
    if(reputation<71)
        return "REPUTATIONT_GOOD_2";
    if(reputation<81)
        return "REPUTATIONT_GOOD_3";
    if(reputation<=90)
        return "REPUTATIONT_GOOD_4";

	return "REPUTATIONT_GOOD_4";
}

string GetMoraleName(int morale)
{
	if(morale<10)
		return MoraleTable[MORALET_TREACHEROUS];
	if(morale<20)
		return MoraleTable[MORALET_AWFUL];
	if(morale<30)
		return MoraleTable[MORALET_LOW];
	if(morale<40)
		return MoraleTable[MORALET_POOR];
	if(morale<50)
		return MoraleTable[MORALET_NORMAL];
	if(morale<60)
		return MoraleTable[MORALET_ELATED];
	if(morale<70)
		return MoraleTable[MORALET_GOOD];
	if(morale<80)
		return MoraleTable[MORALET_HIGH];
	if(morale<90)
		return MoraleTable[MORALET_EXCELLENT];
	if(morale<=100)
		return MoraleTable[MORALET_HEROIC];
	return "";
}

string GetLoyalityName(int iLoyality)
{
	if(iLoyality<10)
		return LoyalityTable[MORALET_TREACHEROUS];
	if(iLoyality<20)
		return LoyalityTable[MORALET_AWFUL];
	if(iLoyality<30)
		return LoyalityTable[MORALET_LOW];
	if(iLoyality<40)
		return LoyalityTable[MORALET_POOR];
	if(iLoyality<50)
		return LoyalityTable[MORALET_NORMAL];
	if(iLoyality<60)
		return LoyalityTable[MORALET_ELATED];
	if(iLoyality<70)
		return LoyalityTable[MORALET_GOOD];
	if(iLoyality<80)
		return LoyalityTable[MORALET_HIGH];
	if(iLoyality<90)
		return LoyalityTable[MORALET_EXCELLENT];
	if(iLoyality<=100)
		return LoyalityTable[MORALET_HEROIC];
	return "";
}

// boal 15/01/04 учет вещей выношу в спец метод для простоты работы далее -->
int SetCharacterSkillByItem(ref _refCharacter, string _skillName, string _itemSkillName, string _item, int _addValue)
{
	int iRetValue = 0;

	if(_skillName == _itemSkillName && GetCharacterItem(_refCharacter, _item) > 0)
	{
		iRetValue = _addValue;
	}

	return iRetValue;
}

//HardCoffee учёт экипированных предметов
int SetCharacterSkillByEquipedItem(ref rChr, string _skillName, string _itemSkillName, string itemID, int _addValue)
{
	if (_skillName != _itemSkillName) return 0;

	aref arItm;
	if (Items_FindItem(itemID, &arItm) < 0) return 0;
	if (!CheckAttribute(arItm, "groupID")) return 0;
	if (!CheckCharacterItem(rChr, itemID)) return 0;

	string sGroupID = arItm.groupID;
	if (!CheckAttribute(rChr, "equip." +sGroupID)) return 0;
	if (itemID == rChr.equip.(sGroupID)) return _addValue;
	return 0;
}

//HardCoffee учёт перков
int SetCharacterSkillByPerk(ref _refCharacter, string _skillName, string _perkSkillName, string _perk, int _addValue)
{
	if (_skillName == _perkSkillName && CheckCharacterPerk(_refCharacter, _perk))
	{
		return _addValue;
	}

	return 0;
}

int SetCharacterSkillBySculArtefact(ref _refCharacter, string _skillName)
{
    if (_skillName == SKILL_CANNONS || _skillName == SKILL_DEFENCE || _skillName == SKILL_GRAPPLING || _skillName == SKILL_SAILING)
	{
		int iSculMa1 = GetCharacterItem(_refCharacter, "sculMa1");
		int iSculMa2 = GetCharacterItem(_refCharacter, "sculMa2");
		int iSculMa3 = GetCharacterItem(_refCharacter, "sculMa3");
		if (iSculMa1 > 0 && iSculMa1 > 0 && iSculMa3 > 0) return 10;
		switch (_skillName)
		{
		    case SKILL_GRAPPLING:
		    	if (iSculMa1 > 0) return 5;
		    break;
		    case SKILL_CANNONS:
		    	if (iSculMa2 > 0) return 5;
		    break;
		    case SKILL_DEFENCE:
		    	if (iSculMa3 > 0) return 5;
		    break;
		}
    }
    return 0;
}

// Warship 25.10.08 Учет одежды
int SetCharacterSkillBySuit(ref rChar, string sSkillName)
{
	int iValue = 0;
	string sSuit = GetCharacterEquipSuitID(rChar);
	
	if(sSuit == INVALID_SUIT) return 0;
	
	switch(sSuit)
	{
		case "suit_1": // Обноски
			if(sSkillName == SKILL_SNEAK)
			{
				iValue = 20;
			}
		break;
		
		case "suit_2": // Одежда торговца
			if(sSkillName == SKILL_COMMERCE)
			{
				iValue = 20;
			}
		break;
		
		case "suit_3": // Платье дворянина
			if(sSkillName == SKILL_LEADERSHIP)
			{
				iValue = 20;
			}
		break;
	}
	
	return iValue;
}

// boal 15/01/04 учет вещей выношу в спец метод для простоты работы далее <--
float GetCharacterSkillToOld(ref _refCharacter, string skillName)
{
    return makefloat(GetCharacterSkill(_refCharacter, skillName) / SKILL_TO_OLD);
}
int GetCharacterSkill(ref _refCharacter, string skillName)
{
    int skillN;

    // boal 051104 метод тормозит страшно - проверка +1 вещей, будет опрос раз в 10
    if (CheckAttribute(_refCharacter, "BakSkill." + skillName))
    {
        if (sti(_refCharacter.BakSkillCount.(skillName)) < 20 )
        {
            _refCharacter.BakSkillCount.(skillName) = sti(_refCharacter.BakSkillCount.(skillName)) + 1;
            return sti(_refCharacter.BakSkill.(skillName));
        }
    }

	skillN = GetCharacterSkillSimple(_refCharacter, skillName);


    // 14.03.05 пенальти от класса корабля -->
 	skillN = ApplayNavyPenaltyToSkill(_refCharacter, skillName, skillN);
	// 14.03.05 пенальти от класса корабля <--

	_refCharacter.BakSkill.(skillName)      =  skillN; // значение
    _refCharacter.BakSkillCount.(skillName) = rand(5); // счетчик немного размажем пересчет

    return skillN;
}

int GetCharacterSkillSimple(ref _refCharacter, string skillName)
{
	if( !CheckAttribute(_refCharacter,"Skill."+skillName) ) return 1;
	int skillN = sti(_refCharacter.Skill.(skillName));

	bool   bHero = (sti(_refCharacter.index) == GetMainCharacterIndex());
	
    // boal учет вещей -->
    if (bHero || CheckAttribute(_refCharacter, "Payment"))
    {
        // Health
        if (bHero && MOD_SKILL_ENEMY_RATE > 1) // не халява
        {
            if (isSelfTypeSkill(skillName))
            {
                skillN = skillN + 5*(GetHealthNum(_refCharacter) - 6); // max -5
            }
        }

        //перки
        skillN = skillN + SetCharacterSkillByPerk(_refCharacter, skillName, SKILL_LEADERSHIP, "Stuttering", -5);
		skillN = skillN + SetCharacterSkillByPerk(_refCharacter, skillName, SKILL_COMMERCE, "Stuttering", -5);

		// РЕЛИГИОЗНЫЕ ПРЕДМЕТЫ
        // Бронзовый крестик
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "jewelry9", 1);
		
		// Бронзовое колечко
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "jewelry8", 1);

    	// Тельная Ладанка {Статуэтка тигра}
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "indian17", 3);

        // крест Антониу де Соуза +5 везение, +3 лидерство, +2 торговля.
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "DeSouzaCross", 15);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "DeSouzaCross", 10);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_COMMERCE, "DeSouzaCross", 5);

		//Я ЗНАЛ, ЧТО ТЫ ЗАХОЧЕШЬ НАЗАД ВСЕ БОНУСЫ ХИТРЕЦ!
		//НУ... ТЕБЕ ОСТАЛОСЬ ТОЛЬКО РАССКОМЕНТИТЬ...
		//*СТАРОЕ ВОРЧАНИЕ ДЕДА*

    	// Emerald Pendant Изумрудные подвески +1 скрытность
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "jewelry15", 10);

    	// ТОТЕМЫ АЦТЕКОВ
    	/*skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "Totem_1", 2);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "Totem_2", 2);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_DEFENCE, "Totem_3", 2);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_ACCURACY, "Totem_4", 2);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_PISTOL, "Totem_5", 2);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "Totem_6", 2);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, "Totem_7", 2);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_LIGHT, "Totem_8", 2);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_HEAVY, "Totem_9", 2);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_COMMERCE, "Totem_10", 2);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SAILING, "Totem_12", 2);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_REPAIR, "Totem_15", 2);*/
		
		
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "SkullAztec", -10);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "SkullAztec", 15);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_PISTOL, "KnifeAztec", -10);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_LIGHT, "KnifeAztec", -10);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, "KnifeAztec", -10);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_HEAVY, "KnifeAztec", -10);
		
		//	ИНДЕЙСКИЕ ИДОЛЫ	
		//statue1 "Статуэтка Шочипилли" +3 ремонт
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_REPAIR, "statue1", 30);
		
		//itmname_indian1 "Оберег Тлальчитонатиу" {Идол Иргантахула} (+1 лидерство и удача, -2 пистолеты).
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "indian1", 10);
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "indian1", 10);
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_PISTOL, "indian1", -20);
		
		// Пугающая Статуэтка {Weird Animal Figurine} (-1 лидерство)
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "indian2", -1);

		// "Нефритовая маска" {Маленькая Мозайка} (+1 торговля)
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_COMMERCE, "indian3", 10);
		
		// "Двойная маска"	{Маска Маркуханкату} (+1 удача).
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "indian5", 10);
		
		// "Амулет Шиукоатля"	{Статуэтка Акумаларту}  (+1 фехтование)
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FENCING, "indian6", 10);
		
		// "Идол Великой Матери" {Идол Пикахуатла} +1 удача
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "indian7", 10);
		
		// itmname_indian10	{Идол Йкстоикхатлу} (+2 пистолеты, +1 меткость, -2 удача).
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_PISTOL, "indian10", 20);
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "indian10", -20);
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_ACCURACY, "indian10", 10);
		
		// "Кубок-тотем Тепейоллотля" {Идол Морхахтулака} (+1 фехтование).
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_HEAVY, "indian12", 10);

    	// "Чаша Ололиуки" {Идол Ихтилокстумба} (+2 торговля, -2 лидерство).
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "indian14", -20);
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_COMMERCE, "indian14", 20);

    	// "Базальтовая голова"	{Ритуальная ванна} (+1 лидерство и защита, -1 удача).
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "indian15", 10);
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_DEFENCE, "indian15", 10);
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "indian15", -10);

    	// "Идол Атлауа" {идол древнего божества} (+2 навигация, -2 удача).
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SAILING, "indian18", 5);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "indian18", -10);

    	// "Статуэтка Тлалока"	{маска из красного золота} (+2 меткость, +1 орудия, -2 удача).
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_ACCURACY, "indian19", 5);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_CANNONS, "indian19", 5);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "indian19", -10);

    	// "Церемониальный нож"	{скипетр жреца} (+2 лидерство и -1 удача)
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "indian20", 10);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "indian20", -5);

    	// "Церемониальный сосуд"	{Церемониальный сосуд} (+2 лидерство, -1 удача).
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "indian21", 10);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "indian21", -5);

    	// "Голова воина племени майя" {странная вещь} (+2 защита, +1 фехтование, -1 лидерство и удача).
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_DEFENCE, "indian22", 10);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_F_LIGHT, "indian22", 5);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "indian22", -10);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "indian22", -10);
		
    	// Изумруд (+1 лидерство)
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "jewelry4", 10);

    	// iitmname_Mineral4	{Баклан} (-1 лидерство и  -1 удача)
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_LEADERSHIP, "mineral4", -1);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "mineral4", -1);

    	//  itmname_Mineral3	{Хризоберилл} (+1 удача).
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "Mineral3", 10);

    	// itmname_Mineral8
    	//skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_GRAPPLING, "Mineral8", 20);
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "Mineral8", -1);

        skillN = skillN + SetCharacterSkillBySculArtefact(_refCharacter, skillName);
		
    	//  itmname_Coins		{Монета ацтеков} (-5 удача)
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "Coins", -50);
		
		//  itmname_Cursed_idol		{Идол Хурукацелитипочтли} (-4 удача)
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "Cursed_idol", -80);
		
		//  itmname_PDM_PJ_BsRL		{Бутылка с розовой ленточкой} (+0.5 везение, +0.5 торговля, -0.5 скрытность)
    	skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_FORTUNE, "PDM_PJ_BsRL", 2);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_COMMERCE, "PDM_PJ_BsRL", 2);
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_SNEAK, "PDM_PJ_BsRL", -2);

		//  itmname_instrument1	{Отличная пила} (+5 ремонт)
		skillN = skillN + SetCharacterSkillByItem(_refCharacter, skillName, SKILL_REPAIR, "instrument1", 5);
	
		// Warship 25.10.08 Новый учет одежды
		skillN += SetCharacterSkillBySuit(_refCharacter, skillName);
	
		//navy --> действие алкоголя
		if (CheckAttribute(_refCharacter, "chr_ai.drunk.skill." + skillName))
		{
			skillN += sti(_refCharacter.chr_ai.drunk.skill.(skillName));
		}
		//<--
    	// boal учет перегруза 19.01.2004 -->
    	if ( GetItemsWeight(_refCharacter) > GetMaxItemsWeight(_refCharacter))
    	{
   	        skillN -= 20;
    	}
    	// boal учет перегруза 19.01.2004 <--
		
		if (!bHero && StrHasStr(skillName, "Sailing,Accuracy,Cannons,Grappling,Defence,Repair,Commerce", 1) && CheckAttribute(_refCharacter, "isfree") && sti(_refCharacter.isfree) > 1)
			skillN += GetCharPostCombinationPenalty(_refCharacter, skillName);
	}
	// boal <--
	if (skillN <= 1) skillN = 1;
	if( skillN > SKILL_MAX ) skillN = SKILL_MAX;

	return skillN;
}

int GetCharPostCombinationPenalty(ref chr, string sSkill)
{
	if (GetAttributeQty(chr, "", "navigator,boatswain,cannoner,doctor,treasurer,carpenter") < 2)
		return 0;
	
	string sPost = "";
	
	switch (sSkill)
	{
		case "Sailing":
			sPost = "navigator";
		break;
		case "Accuracy":
			sPost = "cannoner";
		break;
		case "Cannons":
			sPost = "cannoner";
		break;
		case "Grappling":
			sPost = "boatswain";
		break;
		case "Defence":
			sPost = "doctor";
		break;
		case "Repair":
			sPost = "carpenter";
		break;
		case "Commerce":
			sPost = "treasurer";
		break;
	}
	
	if (sPost == "" || !CheckAttribute(chr, sPost))
		return 0;

	int iSkill = GetCharacterSkill(chr, SKILL_LEADERSHIP);
	if (iSkill < 100)
	{
		return -25 + (iSkill / 25) * 5;
	}
	
	return 0;
}

// boal 20.03.2004 -->
int GetShipClassNavySkill(int shipClass)
{
    int needSkill = 0;

    switch (shipClass)
    {
            case 1 : needSkill = 95; break;
            case 2 : needSkill = 80; break;
            case 3 : needSkill = 65; break;
            case 4 : needSkill = 40; break;
            case 5 : needSkill = 25; break;
            case 6 : needSkill = 1; break;
            case 7 : needSkill = 0; break;
    }
    return needSkill;
}
// boal 20.03.2004 <--
void DelBakSkillAttr(ref _refCharacter) // boal оптимизация скилов
{
    DeleteAttribute(_refCharacter, "BakSkill");
    DeleteAttribute(_refCharacter, "BakSkillCount");
}
// сброс всех порогов (буфер расчёта, пересчитывается от вещей +1)
void ClearCharacterExpRate(ref _chref)
{
    int    i;
    string name;

    for (i=1; i<15; i++)
    {
        name = GetSkillNameByIdx(i);
        DeleteAttribute(_chref, "skill." + name + "_rate");
    }
}
// когда меняется порог кача, нужно сбросить очки, иначе будет по 120%
void RefreshCharacterSkillExpRate(ref _chref)
{
    int    i;
    string name;

	// --> Оптимизация для интерфейсов. Тут цикл, где на каждом шагу:
    // Посмотреть порог -> посмотреть спешиал -> проверить пенальти -> посмотреть Навигацию
    AddCharacterExpToSkill(_chref, SKILL_SAILING, 0.0);
    ApplayNewSkill(_chref, SKILL_SAILING, 0);
    _chref.TempSailing = GetSummonSkillFromNameSimple(_chref, SKILL_SAILING); // бэкапим её
    // <-- Оптимизация (and its really works!)

    for (i=1; i<15; i++)
    {
        name = GetSkillNameByIdx(i);
        AddCharacterExpToSkill(_chref, name, 0.0);
        ApplayNewSkill(_chref, name, 0); // иначе перки  будут 23/22
    }

    DeleteAttribute(_chref, "TempSailing"); // убираем бэкап
}

float GetSummonSkillFromNameToOld(ref _refCharacter, string skillName)
{
    return (GetSummonSkillFromName(_refCharacter, skillName) / SKILL_TO_OLD);
}
int GetSummonSkillFromName(ref _refCharacter, string skillName)
{
    int sumSkill;

    // boal 051104 метод тормозит страшно - проверка +1 вещей, будет опрос раз в 10
    if (CheckAttribute(_refCharacter, "BakSkill." + skillName))
    {
        if (sti(_refCharacter.BakSkillCount.(skillName)) < 25 )
        {
            _refCharacter.BakSkillCount.(skillName) = sti(_refCharacter.BakSkillCount.(skillName)) + 1;
            return sti(_refCharacter.BakSkill.(skillName));
        }
    }

    sumSkill = GetSummonSkillFromNameSimple(_refCharacter, skillName);

    // boal 27.01.2004 пенальти за крутой корабль -->
 	sumSkill = ApplayNavyPenaltyToSkill(_refCharacter, skillName, sumSkill);
    // boal 27.01.2004 <--

    _refCharacter.BakSkill.(skillName)      =  sumSkill; // значение
    _refCharacter.BakSkillCount.(skillName) = rand(5); // счетчик немного размажем пересчет

    return sumSkill;
}

int GetSummonSkillFromNameSimple(ref _refCharacter, string skillName)
{
    int sumSkill = GetCharacterSkillSimple(_refCharacter,skillName);

	if (sti(_refCharacter.index) == sti(pchar.index))
	{
	    int iOfficer = -1;
		int iOffSkill = -1;
		switch (skillName)
		{
			/*case SKILL_LEADERSHIP:
				iOfficer = sti(pchar.Fellows.Passengers.boatswain);
			break;*/

			case SKILL_SAILING:
				iOfficer = sti(pchar.Fellows.Passengers.navigator);
			break;

			case SKILL_CANNONS:
				iOfficer = sti(pchar.Fellows.Passengers.cannoner);
			break;

			case SKILL_ACCURACY:
				iOfficer = sti(pchar.Fellows.Passengers.cannoner);
			break;

			case SKILL_GRAPPLING:
				iOfficer = sti(pchar.Fellows.Passengers.boatswain);
			break;

			case SKILL_DEFENCE:
				iOfficer = sti(pchar.Fellows.Passengers.doctor);
			break;

			case SKILL_REPAIR:
				iOfficer = sti(pchar.Fellows.Passengers.carpenter);
			break;

			case SKILL_COMMERCE:
				iOfficer = sti(pchar.Fellows.Passengers.treasurer);
			break;
		}

		if(iOfficer != -1)
		{
			iOffSkill = GetCharacterSkillSimple(&characters[iOfficer], skillName);
			if (iOffSkill > sumSkill)
			{
				sumSkill = iOffSkill;
			}
		}
	}
	return sumSkill;
}

void AddPartyExp(ref _refCharacter,int _exp)
{
	/*int cn,i;
	ref chref;
	i = GetOfficersQuantity(_refCharacter);
	_exp = (_exp+i)/(i+1);
	for(i=0; i<4; i++)
	{
		cn = GetOfficersIndex(_refCharacter,i);
		if(cn!=-1)
		{	AddCharacterExp(GetCharacter(cn),_exp);
		}
	}*/
}

void AddExpAndShow(ref chref, int _exp)
{
	// boal Log_SetStringToLog("+" + _exp + XI_ConvertString("add experience"));
	//AddCharacterExp(chref, _exp);
}
// boal -->


void AddCharacterExpToSkillSquadron(ref _refCharacter, string _skill, float _addValue)
{
    int cn,i;
	ref chref;

	for(i=0; i<4; i++)
	{
		cn = GetCompanionIndex(_refCharacter,i);
		if(cn!=-1)
		{    // и квестовым тоже
			AddCharacterExpToSkill(GetCharacter(cn), _skill, _addValue);
		}
	}
}
void AddCharacterExpToSkill(ref _chref, string _skill, float _addValue)
// _chref - character _skill - name ex -"Fencing"  _skill_exp = "Fencing_exp"   _addValue = 100
{
    string  _skill_exp = _skill + "_exp";
    if (!CheckAttribute(_chref, "skill." + _skill_exp))
    {
        _chref.skill.(_skill_exp) = 0;
    }
	
    if (bExpLogShow && _addValue > 0)
    {
	   if (IsOfficer(_chref))  Log_Info(_chref.id + " take " + FloatToString(_addValue, 2) + " exp to " + _skill);
    }
    // boal 300804 падение экспы -->
    if (_addValue < 0)
    {
        if(CheckAttribute(_chref, "skill." + _skill_exp))
        {
            _chref.skill.(_skill_exp) = sti(_chref.skill.(_skill_exp)) + _addValue;
            if (sti(_chref.skill.(_skill_exp)) < 0)
            {
                _chref.skill.(_skill_exp) = 0;
            }
        }
        return;
    }
    // boal 300804 падение экспы <--
    if (CheckAttribute(_chref, "skill." + _skill) && sti(_chref.skill.(_skill)) < SKILL_MAX)// && sti(_chref.skill.(_skill)) > 0)
    { // if skill = 0 then it is great loser
        _chref.skill.(_skill_exp) = stf(_chref.skill.(_skill_exp)) + _addValue;
		float fExpRate = GetCharacterExpRate(_chref, _skill);

        while ( makeint(sti(_chref.skill.(_skill)) * fExpRate) <= stf(_chref.skill.(_skill_exp))
                && sti(_chref.skill.(_skill)) < SKILL_MAX )
        {
            _chref.skill.(_skill_exp) = stf(_chref.skill.(_skill_exp)) - makeint(sti(_chref.skill.(_skill)) * fExpRate);
            AddCharacterSkillDontClearExp(_chref, _skill, 1);
            fExpRate = GetCharacterExpRate(_chref, _skill); // Обновим на случай повышения fRateReg
            // оптимизация скилов
            DeleteAttribute(_chref, "BakSkill." + _skill);
            DeleteAttribute(_chref, "BakSkillCount." + _skill);
        }
    }
    /// officers
    if (_addValue > 0 && sti(_chref.index) == GetMainCharacterIndex()) // только для ГГ
    {
        if(ShowExpNotifications() && sti(_chref.skill.(_skill)) != SKILL_MAX) notification(StringFromKey("InfoMessages_225"), _skill);

		int cn, i, iPas;
		float div;
		iPas = GetPassengersQuantity(_chref); // оптимиация
		bool  bShare = CheckCharacterPerk(_chref, "SharedExperience");

		// evganat - энциклопедия
		int iBonus = 1;
		if(!ENCYCLOPEDIA_DISABLED && CheckAttribute(pchar, "encyclopedia.full"))
		{
			iBonus = 2;
		}

		for(i=0; i<iPas; i++)
		{
			cn = GetPassenger(_chref,i);
			if(cn!=-1)
			{
				if (isOfficerInShip(GetCharacter(cn), true))
				{
					if(bShare) div = 2.0;
					else div = 4.0;
				}
				else
				{
					if(bShare) div = 10.0;
					else div = 20.0;
				}

				if (isOfficerInShip(GetCharacter(cn), true))
				{
					AddCharacterExpToSkill(GetCharacter(cn), _skill, iBonus*_addValue / div);
				}
				else
				{
					AddCharacterExpToSkill(GetCharacter(cn), _skill, iBonus*_addValue / div);
				}
			}
		}
		for(i=1; i<COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(_chref,i);
			if(cn!=-1)
			{
				if(bShare) div = 3.0;
				else div = 6.0;
				AddCharacterExpToSkill(GetCharacter(cn), _skill, iBonus*_addValue / div);
			}
		}
	}
}

string GetPerkListText(ref _chref, string _type)
{
    int    perksQ,i;
	string perkName;
	string ret;
	aref   arPerksRoot;

	// Варианты перков, которые можно добавить
	makearef(arPerksRoot, _chref.perks.list);
	perksQ = GetAttributesNum(arPerksRoot);
	ret = "";
	for(i=0; i<perksQ; i++)
	{
		perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));

        if (CheckAttribute(&ChrPerksList, "list." + perkName) && CheckAttribute(&ChrPerksList, "list." + perkName + ".BaseType"))
        {
            if (ChrPerksList.list.(perkName).BaseType == _type)
            {
                ret += "* " + GetConvertStr(perkName, "AbilityDescribe.txt") + " ";
            }
        }
	}
	return ret;
}
// boal Вес предметов 19.01.2004 -->
float GetItemsWeight(ref _chref)
{
    float   Amount = 0.0;
    string  itemID;

	aref arCurItem, arItem, arItems; makearef(arItems, _chref.items);
	int j, q = GetAttributesNum(arItems);

    if (bCabinStarted || bAbordageStarted || !bSeaActive || !CheckAttribute(_chref, "ItemsWeight"))
    {
        for (j = 0; j < q; j++)
    	{
    		arCurItem = GetAttributeN(arItems, j);

			if (Items_FindItem(GetAttributeName(arCurItem), &arItem) >= 0)
			{
				if (CheckAttribute(arItem, "ID"))
				{
					itemID = arItem.id;

					if (CheckAttribute(_chref, "items." + itemID) && itemID != "MapsAtlas")      // ugeen - атлас карт не учитываем !!
					{
						Amount += sti(_chref.items.(itemID)) * stf(arItem.Weight);
					}
				}
			}
        }

        _chref.ItemsWeight = Amount; // оптимицация тормозов в бою на море
    }
    else
        Amount = stf(_chref.ItemsWeight);

    return Amount;
}
int GetMaxItemsWeight(ref _chref)
{
	if (CheckAttribute(_chref, "Skill.Fencing"))
    {
        int iBonus = 0;
		// evganat - энциклопедия
        if (IsCharacterPerkOn(_chref, "Grus")) 
		{
			iBonus = 30;
			if (!ENCYCLOPEDIA_DISABLED)
			{
				if (IsMainCharacter(_chref) || IsCompanion(_chref) || IsCharacterOfficer(_chref))
					iBonus += GetParamPageBonus("Grus");
			}
		}
                                  //опасная рекурсия  если писать GetCharacterSPECIAL
        iBonus = iBonus + CHAR_ITEMS_WEIGHT + GetCharacterSPECIALSimple(_chref, SPECIAL_S)*(GetCharacterSPECIALSimple(_chref, SPECIAL_E) + 12 - MOD_SKILL_ENEMY_RATE);
        return  iBonus;
    }
    else
    {
        return 10000; // сундук или труп не имееют скила и ограничения
    }
}
// boal 19.01.2004 <--

// boal -->
int Statistic_AddValue(ref _chref, string _attrName, int _add) // set and get(_add==0) value
{
    // KillShip_ 1 ..7
    // AbordShip_ 1..7
    // KillAbordShip_ 1..7
    // Solder_s  Solder_g ( s=sword g=gun)
    // Citizen_s  Citizen_g
    // Monster_s Monster_g
    // Warrior_s  Warrior_g
    // Fort
	if(!CheckAttribute(_chref, "index")) return 0;
	
    if (sti(_chref.index) != GetMainCharacterIndex()) return 0; // оптимизация
    
    if( !CheckAttribute(_chref,"Statistic." + _attrName) )
    {
        _chref.Statistic.(_attrName) = 0;
    }
    _chref.Statistic.(_attrName) = sti(_chref.Statistic.(_attrName)) + _add;

    if (sti(_chref.Statistic.(_attrName)) < 0)
    {
        _chref.Statistic.(_attrName) = 0;
    }
    return sti(_chref.Statistic.(_attrName));
}
void Statistic_KillChar(aref _attack, aref _enemy, string _attrName)
{
	if (sti(_attack.index) != GetMainCharacterIndex()) return; // оптимизация
	string  name = GetCharType(_enemy);

	name = name + _attrName;

	Statistic_AddValue(_attack, name, 1);
	// для ачивок
	Achievement_AddStats_KillCharEnemies();
}
string GetCharType(aref _enemy)
{
    string  name  = "Warrior";
    string  model = _enemy.model;
	string	sex   = _enemy.sex;
	
    switch (_enemy.chr_ai.type)
	{
		case LAI_TYPE_PATROL :
		    name = "Solder";
		break;
		case LAI_TYPE_GUARDIAN :
		    name = "Solder";
		break;
		case LAI_TYPE_OFFICER :
		    name = "Solder";
		break;
        // Citizen
		case LAI_TYPE_ACTOR :
		    name = "Citizen";
		break;
		case LAI_TYPE_BARMAN :
		    name = "Citizen";
		break;
		case LAI_TYPE_CITIZEN :
		    name = "Citizen";
		break;
		case LAI_TYPE_HUBER :
		    name = "Citizen";
		break;
		case LAI_TYPE_HUBERSTAY :
		    name = "Citizen";
		break;
		case LAI_TYPE_MERCHANT :
		    name = "Citizen";
		break;
		case LAI_TYPE_POOR :
		    name = "Citizen";
		break;
		case LAI_TYPE_PRIEST :
		    name = "Citizen";
		break;
		case LAI_TYPE_SIT :
		    name = "Citizen";
		break;
		case LAI_TYPE_STAY :
		    name = "Citizen";
		break;
		case LAI_TYPE_WAITRESS :
		    name = "Citizen";
		break;
		case LAI_TYPE_OWNER :
		    name = "Citizen";
		break;

		case LAI_TYPE_WARRIOR :
		    if (model == "mummy" || HasStr(model, "Skel") || sex == "skeleton")
		    {
		        name = "Monster";
		    }
		    else
		    {
                if (HasStrEx(model, "off_,sold_,urban_,navy_,milit_,guard_", "|")) //watch_type
                {
                    name = "Solder";
                }
		    }
		break;
	}

	return  name;
}
// boal statistic info 17.12.2003 <--

// boal Блок здоровье ГГ -->
int GetHealthNum(ref ch)
{
    if (!CheckAttribute(ch, "Health"))
	{
        return 0;
	}
    int i;

    i = makeint((stf(ch.Health.HP) + 9) / 10.0); // до целого

    return i;
}

int GetHealthMaxNum(ref ch)
{
    if (!CheckAttribute(ch, "Health"))
	{
        return 0;
	}
    int i;

    i = makeint((stf(ch.Health.maxHP) + 9) / 10.0); // до целого

    return i;
}
string GetHealthName(ref ch)
{
    string name = "";

    switch (GetHealthNum(ch))
    {
        case 1:
            name = ToUpper(XI_ConvertString("Terrible_Health"));
        break;
        case 2:
            name = ToUpper(XI_ConvertString("Bad_Health"));
        break;
        case 3:
            name = ToUpper(XI_ConvertString("Poor_Health"));
        break;
        case 4:
            name = ToUpper(XI_ConvertString("Average_Health"));
        break;
        case 5:
            name = ToUpper(XI_ConvertString("Good_Health"));
        break;
        case 6:
            name = ToUpper(XI_ConvertString("Excellent_Health"));
        break;
    }
    return name;
}

string GetHealthNameMaxSmall(ref ch)
{
    string name = "";

    switch (GetHealthMaxNum(ch))
    {
        case 1:
            name = XI_ConvertString("Terrible_Health");
        break;
        case 2:
            name = XI_ConvertString("Bad_Health");
        break;
        case 3:
            name = XI_ConvertString("Poor_Health");
        break;
        case 4:
            name = XI_ConvertString("Average_Health");
        break;
        case 5:
            name = XI_ConvertString("Good_Health");
        break;
        case 6:
            name = XI_ConvertString("Excellent_Health");
        break;
    }
    return name;
}

void RestoreNewDayHealth()
{
	int indx;
	ref chref;
	SetNewDayHealth(pchar);
	for (int i = 0; i < GetPassengersQuantity(pchar); i++)
	{
		indx = GetPassenger(pchar,i);
		if (indx == -1) continue;
		chref = GetCharacter(indx);
		if (CheckAttribute(chref, "chr_ai.roly_poly")) SetNewDayHealth(chref);
	}
}

void SetNewDayHealth(ref cref)
{
	ref rDoctor = RefOfficer("doctor");

    float maxhp = stf(cref.chr_ai.hp_max);
    float damg  = stf(cref.Health.Damg);
    int   add   = 0;

    pchar.Health.Damg = 0.0;

    if (IsCharacterPerkOn(cref, "Medic") || IsCharacterPerkOn(rDoctor, "PersonalCare"))
    {
        add = 1;
    }
    if (damg >= (maxhp / 1.5) )
    {
        if ((damg / maxhp) > add)
        {
            AddCharacterHealth(cref, -damg / maxhp + add);
        }
    }
    else
    {
        if (!IsEntity(&worldMap)) // не на карте
        {
            AddCharacterHealth(cref, 1 + add);
        }
        else
        {
            AddCharacterHealth(cref, 0.5 + add / 2.0);
        }
    }
}

void SetNewDayHealthMax()
{
    float maxhp = stf(pchar.chr_ai.hp_max);
    float damg  = stf(pchar.Health.weekDamg);

    pchar.Health.weekDamg = 0.0;

    if (damg > (maxhp * 3.5))
    {
        AddCharacterMaxHealth(pchar, -1);
    }
}

void AddCharacterHealth(ref mainChr, float add)
{
    float maxhp = stf(mainChr.chr_ai.hp_max);
    int   remHP = GetHealthNum(mainChr);

    mainChr.Health.HP = makefloat(stf(mainChr.Health.HP) + add);

    if (stf(mainChr.Health.HP) < 1)
    {
        mainChr.Health.HP = 1.0;
    }

    if (stf(mainChr.Health.HP) > stf(mainChr.Health.maxHP))
    {
        mainChr.Health.HP = stf(mainChr.Health.maxHP);
    }

    if (GetHealthNum(mainChr) > remHP)
    {
        notification(StringFromKey("InfoMessages_10", GetFullName(mainChr)),"HealthUp");
        TEV.WDM_ShipRadiusUpdate = true;
    }

    if (GetHealthNum(mainChr) < remHP)
    {
        notification(StringFromKey("InfoMessages_9", GetFullName(mainChr)),"HealthDown");
        DoQuestFunctionDelay("Tutorial_Health", 1.5);
        TEV.WDM_ShipRadiusUpdate = true;
    }
}

void AddCharacterMaxHealth(ref mainChr, float add)
{
    mainChr.Health.maxHP = makefloat(stf(mainChr.Health.maxHP) + add);

    if (stf(mainChr.Health.maxHP) < 1)
    {
        mainChr.Health.maxHP = 1.0;
    }

    if (stf(mainChr.Health.maxHP) > 60)
    {
        mainChr.Health.maxHP = 60.0;
    }

    if (stf(mainChr.Health.HP) > stf(mainChr.Health.maxHP))
    {
        mainChr.Health.HP = stf(mainChr.Health.maxHP);
    }
}
// boal Блок здоровье ГГ <--

// увеличение счетчика награды за голову -->
int ChangeCharacterHunterScore(ref chref, string _huntName, int incr)
{
	int prevVal = -5; // мин набор

	if (_huntName == "pirhunter") return 0;
	if (CheckAttribute(chref, "GenQuest.HunterScore2Pause")) incr = 0;

	if (CheckAttribute(chref, "reputation." + _huntName) )	prevVal = sti(chref.reputation.(_huntName));

	int newVal = prevVal + incr;
	if (newVal < -100)  newVal = -100;
	if (newVal > 100)   newVal = 100;

	chref.reputation.(_huntName) = newVal;

	if( sti(chref.index) != GetMainCharacterIndex() ) return newVal;

	if (newVal >= 10)
	{
	 	if (prevVal < newVal)
		{
//			Log_SetStringToLog(StringFromKey("InfoMessages_11", XI_ConvertString(_huntName)));
		    notification(StringFromKey("InfoMessages_11", XI_ConvertString(_huntName)), _huntName);
		}

	    if (prevVal > newVal)
		{
//	        Log_SetStringToLog(StringFromKey("InfoMessages_12", XI_ConvertString(_huntName)));
	        notification(StringFromKey("InfoMessages_12", XI_ConvertString(_huntName)), _huntName);
		}
	}
	else
	{
		int iNation = 0;
		switch (_huntName) // код для совместимости со старым
		{
		    case "enghunter":  iNation = ENGLAND; break;
		    case "frahunter":  iNation = FRANCE; break;
		    case "spahunter":  iNation = SPAIN; break;
		    case "holhunter":  iNation = HOLLAND; break;
		}
		string prevName = GetNationReputationName(iNation, -prevVal);
		string newName  = GetNationReputationName(iNation, -newVal);
		if (prevName!=newName)
		{
			string outString = XI_ConvertString("Your reputation with country")+ XI_ConvertString(Nations[iNation].Name + "Gen") +" ";
			if (incr<0)	{outString+=XI_ConvertString("increase");}
			else	{outString+=XI_ConvertString("decrease");}
			outString += " "+XI_ConvertString("to")+" "+newName;
//			Log_SetStringToLog(outString);
            notification(outString, _huntName);
		}
	}
	return newVal;
}

int CharacterHunterRedemp(ref chref, string sNationName) //Количество писатров, что бы откупиться
{
    return ChangeCharacterHunterScore(chref, sNationName + "hunter", 0) * 6000;
}

int ChangeCharacterNationReputation(ref chref, int _Nation, int incr)
{
	return -ChangeCharacterHunterScore(chref, NationShortName(_Nation) + "hunter", -incr); // все наоборот, - это хорошо, + есть НЗГ
}

string GetNationReputation(ref chref, int _Nation)
{
    return GetNationReputationName(_Nation, ChangeCharacterNationReputation(chref, _Nation, 0));
}

string GetNationReputationName(int _Nation, int i)
{
	if (i <= -10)  return XI_ConvertString("ReputationHeadPrice") + (-i*1000);
    if (i < 0 )    return XI_ConvertString("ReputationHostile");
    if (i <= 20 )  return XI_ConvertString("ReputationNeutral");
    if (i <= 50 )  return XI_ConvertString("ReputationGood");
    if (i <= 80 )  return XI_ConvertString("ReputationExcellent");
    if (i <= 100 ) return XI_ConvertString("ReputationAdmiration");

    return XI_ConvertString("ReputationExcellent");
}
// boal 04.04.04
string NationShortName(int iNation)
{
    switch(iNation)
	{
		case ENGLAND:
            return "eng";
		break;
		case FRANCE:
            return "fra";
		break;
		case SPAIN:
            return "spa";
		break;
		case HOLLAND:
			return "hol";
		break;
		case PIRATE:
			return "pir";
		break;
	}
	return "eng";
}
// увеличение счетчика награды за голову <--

void setWDMPointXZ(string _location)
{
    // координаты на глобал карте -->
    int n;
	string sTemp;

    n = FindIslandBySeaLocation(_location);
	if(n!=-1)
	{
		worldMap.island = Islands[n].id;
		Pchar.curIslandId = worldMap.island; // fix
		sTemp = worldMap.island;
		if (CheckAttribute(&worldMap, "islands." + sTemp))
		{
		    worldMap.zeroX = worldMap.islands.(sTemp).position.x;
			worldMap.zeroZ = worldMap.islands.(sTemp).position.z;
			if (CheckAttribute(&worldMap, "islands." + sTemp + "." + _location))
			{
			    worldMap.playerShipX = worldMap.islands.(sTemp).(_location).position.x;
				worldMap.playerShipZ = worldMap.islands.(sTemp).(_location).position.z;
				//trace(sTemp + "." + _location);
			}
			else
			{// для бухт с незаданными координатами
			    worldMap.playerShipX = worldMap.zeroX;
				worldMap.playerShipZ = worldMap.zeroZ;
			}
		}
	}
	// координаты на глобал карте <--
}

// копируем в НПС другого НПС
// нужно не перекрывать ещё и признаки фантома
void ChangeAttributesFromCharacter(ref CopyChref, ref PastChref, bool _dialogCopy)
{
    aref arToChar;
    aref arFromChar;

	if (CheckAttribute(PastChref, "heromodel"))
		CopyChref.heromodel = PastChref.heromodel;

    CopyChref.model            = PastChref.model;
    CopyChref.model.animation  = PastChref.model.animation;
    CopyChref.sex              = CopyChref.sex;
    CopyChref.headModel        = PastChref.headModel;
    CopyChref.FaceId           = PastChref.FaceId;
    CopyChref.nation           = PastChref.nation;

	CopyChref.name             = PastChref.name;
    CopyChref.lastname         = PastChref.lastname;

    CopyChref.rank             = PastChref.rank;
    CopyChref.reputation       = makeint(PastChref.reputation);

	CopyChref.baseCapIdx       = PastChref.index; //Id оригинального в структуру клона

    if (CheckAttribute(PastChref, "loyality"))
    {
    	CopyChref.loyality     = PastChref.loyality;
	}
	else DeleteAttribute(CopyChref, "loyality");

	if (CheckAttribute(PastChref, "alignment"))
	{
    	CopyChref.alignment    = PastChref.alignment;
    }
    else DeleteAttribute(CopyChref, "alignment");

    CopyChref.Money            = PastChref.Money;

	if (CheckAttribute(PastChref, "rank_exp"))
		CopyChref.rank_exp = sti(PastChref.rank_exp);

	//копируем структуру quest от оригинального кэпа, очень нужно по квестам
	if (CheckAttribute(PastChref, "quest"))
    {
	    aref arToCharQuest, arFromCharQuest;
		makearef(arFromCharQuest, PastChref.quest);
		makearef(arToCharQuest, CopyChref.quest);
		DeleteAttribute(arToCharQuest, "");
		CopyAttributes(arToCharQuest, arFromCharQuest);
	}

	if (CheckAttribute(PastChref, "quest.officertype"))
			CopyChref.quest.officertype = PastChref.quest.officertype;
	else	DeleteAttribute(CopyChref, "quest.officertype");

	if (CheckAttribute(PastChref, "Payment"))
			CopyChref.Payment = PastChref.Payment;		//получать бонусы от предметов; при true платить зарплату
	else	DeleteAttribute(CopyChref, "Payment");

	if (CheckAttribute(PastChref, "HoldEquip"))
			CopyChref.HoldEquip = PastChref.HoldEquip;	// не отдавать саблю и пистоль
	else	DeleteAttribute(CopyChref, "HoldEquip");

	if (CheckAttribute(PastChref, "SaveItemsForDead"))	// сохранять все вещи и деньги при смерти
			CopyChref.SaveItemsForDead = true;
	else	DeleteAttribute(CopyChref, "SaveItemsForDead");

	if (CheckAttribute(PastChref, "SaveQuestItemsForDead"))	// сохранять только квестовые вещи и деньги при смерти
			CopyChref.SaveQuestItemsForDead = true;
	else	DeleteAttribute(CopyChref, "SaveQuestItemsForDead");

	if (CheckAttribute(PastChref, "KeepItems"))			// > оставлять / добавлять определённые предметы при смерти
	{
			CopyChref.KeepItems = "";
			makearef(arToChar, CopyChref.KeepItems);
			makearef(arFromChar, PastChref.KeepItems);
			CopyAttributes(arToChar, arFromChar);
	}
	else	DeleteAttribute(CopyChref, "KeepItems");

	if (CheckAttribute(PastChref, "DontClearDead"))
			CopyChref.DontClearDead = true;
	else	DeleteAttribute(CopyChref, "DontClearDead");

	if (CheckAttribute(PastChref, "OfficerWantToGo.DontGo"))
			CopyChref.OfficerWantToGo.DontGo = true;
	else	DeleteAttribute(CopyChref, "OfficerWantToGo.DontGo");

	if (CheckAttribute(PastChref, "CompanionDisable"))
			CopyChref.CompanionDisable = true;
	else	DeleteAttribute(CopyChref, "CompanionDisable");

	if (CheckAttribute(PastChref, "GovernorDisable"))
			CopyChref.GovernorDisable = true;
	else	DeleteAttribute(CopyChref, "GovernorDisable");

	if (CheckAttribute(PastChref, "AllowedPosts"))
			CopyChref.AllowedPosts = PastChref.AllowedPosts;
	else	DeleteAttribute(CopyChref, "AllowedPosts");

	if (CheckAttribute(PastChref, "canDodge"))
			CopyChref.canDodge = true;
	else	DeleteAttribute(CopyChref, "canDodge");

	if (CheckAttribute(PastChref, "MultiFighter"))
			CopyChref.MultiFighter = PastChref.MultiFighter;
	else	DeleteAttribute(CopyChref, "MultiFighter");

	if (CheckAttribute(PastChref, "AllShip"))
			CopyChref.AllShip = true;
	else	DeleteAttribute(CopyChref, "AllShip");

	if (CheckAttribute(PastChref, "AllSelf"))
			CopyChref.AllSelf = true;
	else	DeleteAttribute(CopyChref, "AllSelf");
/*
	if (CheckAttribute(PastChref, "NoCheckFightMode"))
			CopyChref.NoCheckFightMode = true;
	else	DeleteAttribute(CopyChref, "NoCheckFightMode");
*/
	// > мушкетёры
	if (CheckAttribute(PastChref, "SuperShooter"))
			CopyChref.SuperShooter = true;
	else    DeleteAttribute(CopyChref, "SuperShooter");

	if (CheckAttribute(PastChref, "MusketerDistance"))
		CopyChref.MusketerDistance = PastChref.MusketerDistance;

    if (CheckAttribute(PastChref, "MushForever"))
            CopyChref.MushForever = "";
    else    DeleteAttribute(CopyChref, "MushForever");
	// <

    // skill
    DeleteAttribute(CopyChref, "skill");
    CopyChref.skill = "";

    makearef(arToChar, CopyChref.skill);
    makearef(arFromChar, PastChref.skill);

    CopyAttributes(arToChar,arFromChar);

	if (CheckAttribute(PastChref, "skill.freespecial"))
		CopyChref.skill.freespecial = PastChref.skill.freespecial;

	//переносим неваляшковость
	if (CheckAttribute(PastChref, "chr_ai.roly_poly"))
		CopyChref.chr_ai.roly_poly = true;

    // SPECIAL
    DeleteAttribute(CopyChref, "SPECIAL");
    CopyChref.SPECIAL = "";

    makearef(arToChar, CopyChref.SPECIAL);
    makearef(arFromChar, PastChref.SPECIAL);

    CopyAttributes(arToChar,arFromChar);

    // Statistic
    DeleteAttribute(CopyChref, "Statistic");
    CopyChref.Statistic = "";

    makearef(arToChar, CopyChref.Statistic);
    makearef(arFromChar, PastChref.Statistic);

    CopyAttributes(arToChar,arFromChar);

    // perks
    DeleteAttribute(CopyChref, "perks");
    CopyChref.perks = "";

    makearef(arToChar, CopyChref.perks);
    makearef(arFromChar, PastChref.perks);

    CopyAttributes(arToChar, arFromChar);
	
	if (CheckAttribute(PastChref, "perks.freepoints_self"))
		CopyChref.perks.freepoints_self = PastChref.perks.freepoints_self;

	if (CheckAttribute(PastChref, "perks.freepoints_ship"))
		CopyChref.perks.freepoints_ship = PastChref.perks.freepoints_ship;

    // items
    DeleteAttribute(CopyChref, "Items");
    CopyChref.Items = "";

    makearef(arToChar, CopyChref.Items);
    makearef(arFromChar, PastChref.Items);
    CopyAttributes(arToChar,arFromChar);

	DeleteAttribute(CopyChref, "cirassId");

	makearef(arToChar, CopyChref.equip);
	makearef(arFromChar, PastChref.equip);
	CopyAttributes(arToChar, arFromChar);

	if (CheckAttribute(PastChref, "chr_ai.gun.bullet"))
	{
		LAi_SetCharacterUseBullet(CopyChref, GUN_ITEM_TYPE, PastChref.chr_ai.gun.bullet);
	}

	if (CheckAttribute(PastChref, "chr_ai.musket.bullet"))
	{
		LAi_SetCharacterUseBullet(CopyChref, MUSKET_ITEM_TYPE, PastChref.chr_ai.musket.bullet);
	}

	// health
	if (CheckAttribute(PastChref, "Health.TotalDamg"))
    {
		CopyChref.Health.TotalDamg = PastChref.Health.TotalDamg;
	}
	else
	{
        CopyChref.Health.TotalDamg = 0;
	}

	// ugeen --> нужно для генерации различных ситуации в каюте абордированного кэпа
	if (CheckAttribute(PastChref,"Situation")) // если в каюте кэпа возникла ситуация 
	{
		CopyChref.Situation = PastChref.Situation;
		CopyChref.Situation.type = PastChref.Situation.type;
	}

	if (CheckAttribute(PastChref,"EncType"))
	{
		CopyChref.EncType = PastChref.EncType;
	}

	if (CheckAttribute(PastChref,"RealEncounterType"))
	{
		CopyChref.RealEncounterType = PastChref.RealEncounterType;
	}
/*
	if (CheckAttribute(PastChref,"curshipnum"))
	{
		CopyChref.curshipnum = PastChref.curshipnum;
	}
*/
	if (CheckAttribute(PastChref,"Ship"))
	{
		makearef(arToChar, CopyChref.Back.Ship);
		makearef(arFromChar, PastChref.Ship);
		CopyAttributes(arToChar, arFromChar);
	}
	// <-- ugeen

	//AI в море
	//AnalizeShips AlwaysSandbankManeuver DontHitInStorm DontRansackCaptain
	//SinkTenPercent WatchFort AlwaysEnemy AlwaysFriend Abordage.Enable
	//CrewType.Skel CrewType.Smugglers CompanionEnemyEnable QuestFireAction
	//AboardToFinalDeck ShipTaskLock Coastal_Captain Nation.Bak...
	if (CheckAttribute(PastChref, "PearlTartane"))
    {
        CopyChref.PearlTartane = PastChref.PearlTartane;
    }

	if (_dialogCopy && CheckAttribute(PastChref, "Dialog.Filename"))
	{
	    CopyChref.Dialog.Filename    = PastChref.Dialog.Filename;
	    CopyChref.Dialog.CurrentNode = PastChref.Dialog.CurrentNode;

		if (CheckAttribute(PastChref, "Dialog.tempnode"))
			CopyChref.Dialog.tempnode = PastChref.Dialog.tempnode;

	    if (CheckAttribute(PastChref, "greeting"))
			CopyChref.greeting = PastChref.greeting; //eddy.нет логам!
		else
		{
			DeleteAttribute(CopyChref, "greeting");
		}
	}

	LAi_SetHP(CopyChref, makeint(PastChref.chr_ai.hp_max), makeint(PastChref.chr_ai.hp_max));

	if (CheckAttribute(PastChref, "OfficerReincarnation"))
	{
		if (CheckCharacterPerk(CopyChref, "HPPlus") && stf(CopyChref.chr_ai.hp_max) > sti(CopyChref.Rank))
			CopyChref.chr_ai.hp_max = stf(CopyChref.chr_ai.hp_max) - sti(CopyChref.Rank);

		CopyChref.OfficerReincarnation = PastChref.OfficerReincarnation;
	}

	LAi_SetCurHPMax(CopyChref);
	SetEnergyToCharacter(CopyChref);

	if (CheckAttributeMass(PastChref, "HiredDate", "control_day,control_month,control_year,control_time", "&"))
	{
		CopyChref.HiredDate.control_day = PastChref.HiredDate.control_day;
		CopyChref.HiredDate.control_month = PastChref.HiredDate.control_month;
		CopyChref.HiredDate.control_year = PastChref.HiredDate.control_year;
		CopyChref.HiredDate.control_time = PastChref.HiredDate.control_time;
	}

	//SetNewModelToChar(CopyChref);  // чтоб сабли были правильные
}

int GetCharacterLoyality(ref chr)
{
    if (CheckAttribute(chr, "loyality"))
    {
        if (sti(chr.loyality) > MAX_LOYALITY)
        {
            return MAX_LOYALITY;
        }
        if (sti(chr.loyality) < 0)
        {
            return 0;
        }
        return sti(chr.loyality);
    }
    else
    {
        return  0; // для пленных и гг
    }
}

// boal 091004 много героев  -->
// boal 23.01.2004 выбор персонажа-->
void setNewMainCharacter(ref ch, int num)
{
	string heroModel, heroFaceId;
	int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");

    totalInfo = LanguageConvertString(idLngFile, "heroFace_" + num);
    heroFaceId  = sti(totalInfo);
    ch.FaceId   = heroFaceId;

    totalInfo = LanguageConvertString(idLngFile, "heroModel_" + num);
    ch.HeroModel = totalInfo;
    ch.model	= GetSubStringByNum(ch.HeroModel, 0);
    ch.headModel = "h_" + ch.model;

    totalInfo = LanguageConvertString(idLngFile, "heroName_" + num);
    ch.name 	=  totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "heroLastname_" + num);
    ch.lastname = totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "sex_" + num);
    ch.sex = totalInfo;

    totalInfo = LanguageConvertString(idLngFile, "animation_" + num);
    ch.model.animation = totalInfo;

    if(ch.sex == "woman")
	{
		ch.model.height = 1.75;
	}
    else
    {
		ch.model.height = 1.8;
	}

    LanguageCloseFile(idLngFile);
    // для НПС
    ch.HeroParam.HeroType = GetNewMainCharacterType(num);
    ch.nation             = GetNewMainCharacterNation(num);

}

void initNewMainCharacter()
{
	ref ch = GetMainCharacter();
	string sTemp;
	int    iTmp, i;

	//HardCoffee Начальный дневной рандом dRand и временный dRandEx
	g_sDayRand = Rand(32768);
	TEV.dRandEx.last = "0";
	for (i = 1; i <= 10; i++) //TODO: избавиться от dRandEx
	{
		sTemp = ""+i;
		TEV.dRandEx.(sTemp) = Rand(32768);
	}

    setNewMainCharacter(ch, startHeroType);
    // контроль версий -->
    InitMigrations();
    ch.VersionNumber              = GetVerNum();
    ch.VersionNumberCompatibility = VERSION_NUM;
    // контроль версий <--
    ch.nation     = NullCharacter.HeroParam.nation;
    ch.BaseNation = NullCharacter.HeroParam.nation;
    
    //MOD_EXP_RATE =  10;  задаем в начале игры (выбор, от 5 до 15, 10 - середина по умолчанию)
    //MOD_EXP_RATE =  MOD_EXP_RATE + (MOD_SKILL_ENEMY_RATE)*6; // разные уровни для всех
    MOD_EXP_RATE =  makeint(MOD_EXP_RATE + MOD_SKILL_ENEMY_RATE * MOD_EXP_RATE / 1.666666666); // разные уровни для всех
    if (MOD_EXP_RATE < 10) MOD_EXP_RATE = 10; // иначе будет развал целостности данных, порог релиховой версии бля всех сложностей.
    
	// куда плывем
	if (sti(ch.nation) != PIRATE)
	{
		ch.HeroParam.ToCityId     = FindAlliedColonyForNation(sti(ch.nation), true);
	}
	else
	{
		ch.HeroParam.ToCityId = FindAlliedColonyForNationExceptColony("Pirates"); //Бермуды не берем, туда ещё добираться надо
	}

	// откуда плывем
    ch.HeroParam.FromCityId  = Colonies[FindNonEnemyColonyForAdventure(sti(ch.nation), ch.HeroParam.ToCityId, true)].id;

	// где появимся
	if (sti(ch.nation) != PIRATE)
	{
		ch.HeroParam.Location = ch.HeroParam.ToCityId + "_town";
		ch.HeroParam.Group    = "reload";
		ch.HeroParam.Locator  = "reload1";
		
		if (ch.HeroParam.ToCityId == "FortOrange")	//Форт Оранж
		{
			ch.HeroParam.Location = "Shore35";
			ch.HeroParam.Group    = "reload";
			ch.HeroParam.Locator  = "sea";
		}
	}
	else
	{
		ch.HeroParam.Location = ch.HeroParam.ToCityId + "_port";
		ch.HeroParam.Group    = "reload";
		ch.HeroParam.Locator  = "sea";
		if (ch.HeroParam.ToCityId == "LaVega")	//Ла Вега town
		{
			ch.HeroParam.Location = ch.HeroParam.ToCityId + "_town";
			ch.HeroParam.Group    = "reload";
			ch.HeroParam.Locator  = "reload1";
		}
		if (ch.HeroParam.ToCityId == "LeFransua")	//Ле Франсуа town
		{
			ch.HeroParam.Location = ch.HeroParam.ToCityId + "_town";
			ch.HeroParam.Group    = "reload";
			ch.HeroParam.Locator  = "sea";
		}
		if (ch.HeroParam.ToCityId == "Providencia")	//Провиденсия town
		{
			ch.HeroParam.Location = ch.HeroParam.ToCityId + "_town";
			ch.HeroParam.Group    = "reload";
			ch.HeroParam.Locator  = "reload2";
		}
	}

	setCharacterShipLocation(ch, ch.HeroParam.Location);
    setWDMPointXZ(ch.HeroParam.Location);  // коорд на карте
    
	SetTimerCondition("Move_Govenour", 0, 0, 25 + rand(10), true); // TODO перенести в один метод инициации
	//Запускаем проверку на падение здоровья раз в 5 дней
    SetTimerCondition("CheckMaxHealthQuest", 0, 0, 5, true);
    
    SetTimerCondition("Nation_Legend", 0, 0, 25 + rand(10), true);

	/// Рассадим губернаторов
    SetGovenourToCity(ENGLAND, "PortRoyal");
    SetGovenourToCity(SPAIN, "Havana");
    SetGovenourToCity(FRANCE, "Tortuga");
    SetGovenourToCity(HOLLAND, "Villemstad");
    // TODO PrepareVisitCity(); // задать квест на посежение города для нанесения его на карту

	AddQuestRecordInfo("Recipe", "grapeshot");
	AddQuestRecordInfo("Tutorial_Dictonary", "1");
	AddQuestRecordInfo("Tutorial_Eng", "1");
	AddQuestRecordInfo("Tutorial_Fra", "1");
	AddQuestRecordInfo("Tutorial_Spa", "1");
	AddQuestRecordInfo("Tutorial_Hol", "1");
	AddQuestRecordInfo("Tenochtitlan_info", "9");
	AddQuestRecordInfo("Tenochtitlan_info", "8");
	AddQuestRecordInfo("Tenochtitlan_info", "7");
	AddQuestRecordInfo("Tenochtitlan_info", "6");
	AddQuestRecordInfo("Tenochtitlan_info", "5");
	AddQuestRecordInfo("Tenochtitlan_info", "4");
	AddQuestRecordInfo("Tenochtitlan_info", "3");
	AddQuestRecordInfo("Tenochtitlan_info", "2");
	AddQuestRecordInfo("Tenochtitlan_info", "1");
	AddQuestRecordInfo("Tutorial_Sharp", "1");
	AddQuestRecordInfo("Tutorial_Fight_Info", "1");
	AddQuestRecordInfo("Tutorial_Seafight_Info", "1");

	ReloadProgressUpdate();

 	SetNationRelations();
 	// от кого драпаем
	ch.HeroParam.EnemyNation  = FindEnemyNation2Nation(sti(ch.nation));
	
    // boal вешаем прерывание на охотников навечно (для моря и земли) -->
    SetTimerCondition("SeaHunterCheck", 0, 0, 6, true);
    SaveCurrentQuestDateParam("Land_HunterTimerEng");
    SaveCurrentQuestDateParam("Land_HunterTimerFra");
    SaveCurrentQuestDateParam("Land_HunterTimerSpa");
    SaveCurrentQuestDateParam("Land_HunterTimerHol");
    //SaveCurrentQuestDateParam("Land_HunterTimerHasBeen");
    // boal вешаем прерывание на охотников навечно (для моря и земли) <--
    LAi_SetHP(ch, LAI_DEFAULT_HP, LAI_DEFAULT_HP);

    ch.HeroParam.HeroType = NullCharacter.HeroParam.HeroType;

	SetSPECIAL(ch, 4,4,4,4,4,4,4); //фикс для любителей стирать тип ГГ в файле - была дыра
	switch (ch.HeroParam.HeroType)
	{
        /*case "Master":
    	    SetSPECIAL(ch, 8,5,7,5,7,4,4);
	    break;  */

        case "Merchant":
    	    SetSPECIAL(ch, 4,9,5,8,9,3,4);
			SetCharacterPerk(pchar, "Grus");
	    break;

	    case "Corsair":
         	SetSPECIAL(ch, 7,6,6,3,5,9,6);
			SetCharacterPerk(pchar, "IronWill");
	    break;

	    case "Adventurer":
    	    SetSPECIAL(ch, 5,7,6,4,6,6,8);
			SetCharacterPerk(pchar, "HawkEye");
	    break;

	   /* case "Inquisitor":
    	    ch.perks.list.IronWill = "1";
    	    SetSPECIAL(ch, 6,4,5,8,6,6,5);
	    break;

	    case "SecretAgent":
    	    SetSPECIAL(ch, 6,6,6,6,6,6,6);
	    break;   */

	}
	ch.skill.freeskill   = 0;
	ch.Skill.FreeSPECIAL = 0;
	SetCharacterPerk(pchar, "Flag" + NationShortName(sti(pchar.nation))); // перк флага нации
	if (sti(ch.nation) != PIRATE || startHeroType == 1) SetCharacterPerk(pchar, "FlagPir");
	else
	{
		SetCharacterPerk(pchar, "Gunman");
		SetCharacterPerk(pchar, "SelfRepair");
	}
	SetCharacterPerk(pchar, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, дается ГГ и боссам уровней
    SetBonusPush(ch, true);
	// начальные скилы задать
    InitStartParam(pchar);
    SetEnergyToCharacter(pchar);
    initMainCharacterItem();
    DeleteAttribute(pchar, "Ship");
    if (sti(ch.nation) != PIRATE)
	{
	    pchar.Ship.Type = GenerateShipExt((SHIP_BILANCETTA + rand(2) - 1), 0, pchar);
	    SetBaseShipData(pchar);
	    SetCrewQuantity(pchar, GetMinCrewQuantity(pchar));
	}
	else
	{
		pchar.Ship.Type = GenerateShipExt(SHIP_SLOOP, 0, pchar);
		SetBaseShipData(pchar);
		SetCrewQuantity(pchar, 40);
		SetCharacterGoods(pchar, GOOD_RUM, 25);
		SetCharacterPerk(pchar, "BasePirate");
	}
    SetRandomNameToShip(pchar); //ZhilyaevDm случ имя для стартового корабля
	// коцаем корабль
	pchar.ship.SP = sti(pchar.ship.SP) - 10;
	pchar.ship.HP = sti(pchar.ship.HP) - makeint(sti(pchar.ship.HP)/2);

	//Tutorial - НАЧАЛО ИГРЫ
	if (startHeroType == 1) //21/07/07 homo для Блада даем другое начало
    {
        pchar.quest.Tut_start.win_condition.l1          = "location";
        pchar.quest.Tut_start.win_condition.l1.location = "Estate";
        pchar.quest.Tut_start.function                  = "Blood_StartGame";
        Pchar.questTemp.CapBloodLine = true;
    }
/*    else if (startHeroType == 2) //для Граммона даем другое начало konstrush
    {
        pchar.quest.Tut_start.win_condition.l1          = "location";
        pchar.quest.Tut_start.win_condition.l1.location = "GrammonEstate";
		pchar.quest.Tut_start.win_condition             = "FL1_s1";
		//Pchar.questTemp.MGrammonLine = true; //TODO: сделаем по аналогии с Бладом
        Pchar.questTemp.CapBloodLine = false;
    }*/
    else //Tutorial - НАЧАЛО ИГРЫ
    {
        pchar.quest.Tut_start.win_condition.l1          = "location";
        pchar.quest.Tut_start.win_condition.l1.location = "Ship_deck_Low";
        pchar.quest.Tut_start.function                  = "Tut_StartGame";
		Pchar.questTemp.CapBloodLine = false;
		Set_My_Cabin();
    }
	
	//Раздаём черты разных ГГ
	if(startHeroType == 2 || startHeroType == 9) //Шарль, Граммон
		SetCharacterPerk(pchar, "Nobleman");
	if(startHeroType == 22) //Леклерк TO_DO: DEL
		SetCharacterPerk(pchar, "OneLegMan");

	if (HasStrEx(pchar.model.animation, "Danielle,Jessika", "|"))
		SetCharacterPerk(pchar, "Dignity");
	else SetCharacterPerk(pchar, "NachoPuncher");
	// Warship Для разных квестов
	// Важно: функция MaryCelesteInit() должна быть тут, а не в initStartState2Character()
	// т.к. в ней идет выборка колоний, которые в функции initStartState2Character() ещё не инитились
	MaryCelesteInit(); // Warship 07.07.09 Пасхалка "Мэри Селест"
	PDMQuestsInit(); // ==> Квесты Проклятие Дальних Морей
}

void initMainCharacterItem()
{
	string itemID;
    //trace("initMainCharacterItem "  + pchar.HeroParam.HeroType);
	
	switch (pchar.HeroParam.HeroType)
	{
        case "Master":
			itemID = GetGeneratedItem("topor3");
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
            TakenItems(Pchar, "potion2", 1);
	        if(CheckCharacterItem(Pchar, "Spyglass1") == 0) GiveItem2Character(Pchar, "Spyglass1");
	        EquipCharacterbyItem(Pchar, "Spyglass1");
	    break;

        case "Merchant":
			itemID = GetGeneratedItem("blade1");
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
            GiveItem2Character(Pchar, "pistol2");
            EquipCharacterbyItem(Pchar, "Pistol2");
            TakenItems(Pchar, "potion1", 3);
            TakeNItems(Pchar, "bullet", 5);
			AddItems(Pchar, "GunPowder", 5); // Warship. Порох
	        if(CheckCharacterItem(Pchar, "Spyglass1") == 0) GiveItem2Character(Pchar, "Spyglass1");
	        EquipCharacterbyItem(Pchar, "Spyglass1");
	        pchar.money = 2000;
	    break;

		case "Corsair":
			itemID = GetGeneratedItem("blade2");
			GiveItem2Character(Pchar, itemID);
			EquipCharacterbyItem(Pchar, itemID);
			GiveItem2Character(Pchar, "pistol1");
			EquipCharacterbyItem(Pchar, "Pistol1");
			TakenItems(Pchar, "potion1", 5);
			TakeNItems(Pchar, "bullet", 10);
			AddItems(Pchar, "GunPowder", 10); // Warship. Порох
			if(CheckCharacterItem(Pchar, "Spyglass1") == 0) GiveItem2Character(Pchar, "Spyglass1");
			EquipCharacterbyItem(Pchar, "Spyglass1");
			if (sti(pchar.nation) == PIRATE)
			{
				GiveItem2Character(pchar, "map_part1");
				pchar.money = 361;
			}
		break;

	    case "Adventurer":
			itemID = GetGeneratedItem("Blade10");
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
            TakenItems(Pchar, "potion1", 2);
	        if(CheckCharacterItem(Pchar, "Spyglass2") == 0) GiveItem2Character(Pchar, "Spyglass2");
	        EquipCharacterbyItem(Pchar, "Spyglass2");
         	pchar.money = 500;
	    break;

	    case "Inquisitor":
			itemID = GetGeneratedItem("blade5");
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
            TakenItems(Pchar, "potion1", 3);
            TakenItems(Pchar, "jewelry9", 1);
	        if(CheckCharacterItem(Pchar, "Spyglass1") == 0) GiveItem2Character(Pchar, "Spyglass1");
	        EquipCharacterbyItem(Pchar, "Spyglass1");
	    break;

	    case "SecretAgent":
			itemID = GetGeneratedItem("blade5");
            GiveItem2Character(Pchar, itemID);
            EquipCharacterbyItem(Pchar, itemID);
	        if(CheckCharacterItem(Pchar, "Spyglass1") == 0) GiveItem2Character(Pchar, "Spyglass1");
	        EquipCharacterbyItem(Pchar, "Spyglass1");
	    break;
	}

	if (GetDLCenabled(NABOB_PACK))
		TEV.cabinParrot = "1";
	else
		TEV.cabinParrot = "0";
}

int GetNewMainCharacterFace()
{
    return sti(GetNewMainCharacterParam("heroFace_" + startHeroType));
}

string GetNewMainCharacterName()
{
    return GetHeroName(startHeroType);
}

string GetMainCharacterNameGen()  // ==> eddy. родительный падеж полного имени ГГ
{
    return GetHeroNameGen(startHeroType);
}

string GetMainCharacterNameDat()  // ==> eddy. дательный падеж полного имени ГГ
{
    return GetHeroNameDat(startHeroType);
}

string GetHeroName(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroName_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastname_" + _n);

    return totalInfo;
}

string GetHeroNameGen(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroNameGen_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastnameGen_" + _n);

    return totalInfo;
}

string GetHeroNameDat(int _n)
{
    string totalInfo;

    totalInfo = GetNewMainCharacterParam("heroNameDat_" + _n);
    totalInfo = totalInfo + " " + GetNewMainCharacterParam("heroLastnameDat_" + _n);

    return totalInfo;
}

int GetNewMainCharacterNation(int _startHeroType)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, "heroNation_" + _startHeroType);
    LanguageCloseFile(idLngFile);

    if (totalInfo == XI_ConvertString("enghunter")) return ENGLAND;
    if (totalInfo == XI_ConvertString("frahunter")) return FRANCE;
    if (totalInfo == XI_ConvertString("spahunter")) return SPAIN;
    if (totalInfo == XI_ConvertString("holhunter")) return HOLLAND;
    if (totalInfo == XI_ConvertString("pirhunter")) return PIRATE;

    switch(totalInfo)
	{
		case "ENGLAND":
            return ENGLAND;
		break;
		case "FRANCE":
            return FRANCE;
		break;
		case "SPAIN":
            return SPAIN;
		break;
		case "HOLLAND":
			return HOLLAND;
		break;
		case "PIRATE":
			return PIRATE;
		break;
	}
	return PIRATE;
}

string GetNewMainCharacterType(int _startHeroType)
{
    string ret = GetNewMainCharacterParam("heroType_" + _startHeroType);

    if (ret == XI_ConvertString("Merchant"))    return "Merchant";
    if (ret == XI_ConvertString("Master"))      return "Master";
    if (ret == XI_ConvertString("Corsair"))     return "Corsair";
    if (ret == XI_ConvertString("Adventurer"))  return "Adventurer";
    if (ret == XI_ConvertString("Inquisitor"))  return "Inquisitor";
    if (ret == XI_ConvertString("SecretAgent")) return "SecretAgent";

	return ret;
}

string GetNewMainCharacterParam(string _param)
{
    int    idLngFile = -1;
    string totalInfo;

    idLngFile = LanguageOpenFile("HeroDescribe.txt");
    totalInfo = LanguageConvertString(idLngFile, _param);
    LanguageCloseFile(idLngFile);

    return totalInfo;
}

// вернуть базовую нацию ГГ или патент
int GetBaseHeroNation()
{
	if (isMainCharacterPatented())
	{
	    return sti(Items[sti(pchar.EquipedPatentId)].Nation);
	}
	return sti(pchar.BaseNation);
}


bool PlayerRPGCheck_SPECIAL(string stat, int threshold)
{
    return PlayerRPGCheck_SPECIAL_Sum(stat, threshold);
}

bool PlayerRPGCheck_SPECIAL_Sum(string stats, int threshold)
{
    int i, iAttrs = KZ|Symbol(stats, ",");

    string stat;
    int statVal = 0;
    int sum = 0;
    for (i = 0; i <= iAttrs; i++)
    {
        stat = GetSubStr(stats, ",", i);

        if (stat == "")
        {
            continue;
        }

        statVal = GetCharacterSPECIAL(pchar, stat);
        sum += statVal;
    }

    bool res = sum >= threshold;

    if (res)
    {
        for (i = 0; i <= iAttrs; i++)
        {
            stat = GetSubStr(stats, ",", i);

            if (stat == "")
            {
                continue;
            }

            PlayerRPGCheck_SPECIAL_NotifyPass(stat);
        }
    }
    else
    {
        int n = threshold / (iAttrs + 1);
        for (i = 0; i <= iAttrs; i++)
        {
            stat = GetSubStr(stats, ",", i);

            if (stat == "")
            {
                continue;
            }

            statVal = GetCharacterSPECIAL(pchar, stat);
            if (statVal > n)
            {
                PlayerRPGCheck_SPECIAL_NotifyPass(stat);
                continue;
            }
            PlayerRPGCheck_SPECIAL_NotifyFail(stat);
        }
    }

    return res;
}

void PlayerRPGCheck_SPECIAL_NotifyPass(string stat)
{
    string statName = XI_ConvertString(stat);
    if (statName == "")
    {
        statName = stat;
    }
    Notification(StringFromKey("InfoMessages_229", statName), stat);
}

void PlayerRPGCheck_SPECIAL_NotifyFail(string stat)
{
    int curStatVal = GetCharacterSPECIAL(pchar, stat);

    if (curStatVal >= 10)
    {
        Notification(StringFromKey("InfoMessages_230", XI_ConvertString(stat)), stat);
        return;
    }

    string statName = XI_ConvertString(stat + "Gen");
    if (statName == "")
    {
        statName = stat;
    }
    Notification(StringFromKey("InfoMessages_231", statName, curStatVal), stat);
}

// useSummon == true - использовать для расчета корабельного скилла бонусы от офицеров
bool PlayerRPGCheck_Skill(string stat, int threshold, bool useSummon)
{
    bool isShipAbility = StrHasStr(stat, "Sailing,Accuracy,Cannons,Grappling,Defence,Repair,Commerce", true);
    int curStatVal = 0;
    if (isShipAbility && useSummon)
    {
        curStatVal = GetSummonSkillFromName(pchar, stat);
    }
    else
    {
        curStatVal = GetCharacterSkill(pchar, stat);
    }
    bool res = curStatVal >= threshold;

    if (res)
    {
        PlayerRPGCheck_Skill_NotifyPass(stat);
    }
    else
    {
        PlayerRPGCheck_Skill_NotifyFail(stat, useSummon);
    }

    return res;
}

void PlayerRPGCheck_Skill_NotifyPass(string stat)
{
    string statName = XI_ConvertString(stat);
    if (statName == "")
    {
        statName = stat;
    }
    Notification(StringFromKey("InfoMessages_229", statName), stat);
}

// useSummon == true - использовать для расчета корабельного скилла бонусы от офицеров
void PlayerRPGCheck_Skill_NotifyFail(string stat, bool useSummon)
{
    bool isShipAbility = StrHasStr(stat, "Sailing,Accuracy,Cannons,Grappling,Defence,Repair,Commerce", true);
    int curStatVal = 0;
    if (isShipAbility && useSummon)
    {
        curStatVal = GetSummonSkillFromName(pchar, stat);
    }
    else
    {
        curStatVal = GetCharacterSkill(pchar, stat);
    }
    string statName = XI_ConvertString(stat);
    if (statName == "")
    {
        statName = stat;
    }
    if (curStatVal < 100)
    {
        Notification(StringFromKey("InfoMessages_232", statName, curStatVal), stat);
    }
    else
    {
        Notification(StringFromKey("InfoMessages_230", statName), stat);
    }
}

void PlayerRPGCheck_Perk_NotifyPass(string stat)
{
    string perkName = GetConvertStr(stat, "AbilityDescribe.txt");
    if (perkName == "")
    {
        perkName = stat;
    }
    Notification(perkName, stat);
}

void PlayerRPGCheck_Perk_NotifyFail(string stat)
{
    notification(StringFromKey("InfoMessages_233"), stat);
}

// Если не нужно логирование используйте isBadReputation()
// logPassFull - если false, то успех логировать только при наличии Trustworthy
bool PlayerRPGCheck_BadReputation(int threshold, bool logPassFull)
{
    bool checkRes = isBadReputation(pchar, threshold);
    if (!checkRes)
    {
        if (logPassFull)
        {
            PlayerRPGCheck_Reputation_NotifyPass(true, true);
        }
        else
        {
            if (CheckCharacterPerk(pchar, "Trustworthy"))
            {
                PlayerRPGCheck_Perk_NotifyPass("Trustworthy");
            }
        }
    }
    else
    {
        PlayerRPGCheck_Reputation_NotifyFail("good");
    }

    return checkRes;
}

// useTrustworthy - true, если при проверке репы использовался isBadReputation()
// positive - true, иконка '+', иначе иконка '-'
void PlayerRPGCheck_Reputation_NotifyPass(bool useTrustworthy, bool positive)
{
    if (useTrustworthy && CheckCharacterPerk(pchar, "Trustworthy"))
    {
        PlayerRPGCheck_Perk_NotifyPass("Trustworthy");
    }
    else
    {
        string iconName = "RepUp";
        if (!positive && !useTrustworthy)
        {
            iconName = "RepDown";
        }
        Notification(StringFromKey("InfoMessages_234"), iconName);
    }
}

// alignment = "good" | "bad";
void PlayerRPGCheck_Reputation_NotifyFail(string alignment)
{
    int stat = sti(pchar.reputation);
    if (alignment == "good")
    {
        Notification(StringFromKey("InfoMessages_235", stat), "RepDown");
    }
    else
    {
        Notification(StringFromKey("InfoMessages_236", stat), "RepUp");
    }
}

void PlayerRPGCheck_NationReputation_NotifyFail(int nation)
{
    Notification(StringFromKey("InfoMessages_237"), NationShortName(nation) + "hunter");
}


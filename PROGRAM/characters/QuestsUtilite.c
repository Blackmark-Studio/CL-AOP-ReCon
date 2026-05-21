// строковая дата, день_мес
string LastSpeakDate()
{
    return environment.date.day + " " + environment.date.month;
}
// Для диалогов НПС -->
string GetNPCQuestDate(ref npchar, string _type)
{
    if (!CheckAttribute(npchar, "QuestDate." + _type))
    {
        npchar.QuestDate.(_type) = "";
    }
    return npchar.QuestDate.(_type);
}
void SetNPCQuestDate(ref npchar, string _type)
{
    npchar.QuestDate.(_type) = LastSpeakDate();
}
bool CheckNPCQuestDate(ref npchar, string _type)
{
    if (GetNPCQuestDate(npchar, _type) != LastSpeakDate())
    {
        return true;
    }
    return false;
}
// Для ГГ <--
void SaveCurrentQuestDateParam(string _quest)
{ // запись даты получения квеста
    aref  arQ;
    makearef(arQ, PChar.(_quest));
    
    arQ.control_day = GetDataDay();
    arQ.control_month = GetDataMonth();
    arQ.control_year = GetDataYear();
    arQ.control_time = GetTime();
}
int GetQuestPastMonthParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));
	
	if (CheckAttribute(PChar, _quest + ".control_year"))
    {
		return GetPastTime("month", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	} 
	return 0;
}
int GetQuestPastDayParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));
    if (CheckAttribute(PChar, _quest + ".control_year"))
    {
    	return GetPastTime("day", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	} 
	return 0;   	
}
int GetQuestPastTimeParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));
    if (CheckAttribute(PChar, _quest + ".control_year"))
    {
    	return GetPastTime("hour", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}  
	return 0;
}
//navy -->
//Ввел ещё одну функцию, т.к. нужны прошедшие минуты.
int GetQuestPastMinutesParam(string _quest)
{
    aref  arQ;
    makearef(arQ, PChar.(_quest));
    if (CheckAttribute(PChar, _quest + ".control_year"))
    {
    	return GetPastTime("minute", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}
	return 0;
}
//navy <--

// eddy
// ************* для неписей.
void SaveCurrentNpcQuestDateParam(ref _character, string _quest)
{ // запись даты получения квеста
    aref  arQ;
    makearef(arQ, _character.(_quest));

    arQ.control_day = GetDataDay();
    arQ.control_month = GetDataMonth();
    arQ.control_year = GetDataYear();
    arQ.control_time = GetTime();
}

int GetNpcQuestPastDayParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
        return GetPastTime("day", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), 0,GetDataYear(), GetDataMonth(), GetDataDay(), 0);
    }
    else {return 0;}
}

int GetNpcQuestPastDayWOInit(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
        return GetPastTime("day", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), 0,GetDataYear(), GetDataMonth(), GetDataDay(), 0);
    }
    else {return 1000;}  // если нет ветки, то это значит черти когда было дело
}

int GetNpcQuestPastTimeParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
    	return GetPastTime("hour", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), sti(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}
	return 0;
}
int GetNpcQuestPastMinutesParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
    	return GetPastTime("minute", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), stf(arQ.control_time), GetDataYear(), GetDataMonth(), GetDataDay(), GetTime());
	}
	return 0;
}

int GetNpcQuestPastMonthParam(ref _character, string _quest)
{
    aref  arQ;
    makearef(arQ, _character.(_quest));
    if (CheckAttribute(_character, _quest + ".control_year"))
    {
        return GetPastTime("month", sti(arQ.control_year), sti(arQ.control_month), sti(arQ.control_day), 0,GetDataYear(), GetDataMonth(), GetDataDay(), 0);
    }
    else return 0;
}
// *************


// Поместить непися в компаньоны и тут же отправить его на выход из текущей локации.
void CharacterIntoCompanionAndGoOut(ref _mainCharacter, ref _compCharacter, string _group, string _locator, int _timeToGoOut, bool _compRemove)
{
    if (!bDisableFastReload) //чтобы не снимать запрет, если он установлен другим методом
	{
		bDisableFastReload = true;
		_mainCharacter.GenQuest.CallFunctionParam.CharacterIntoCompanion.FastReload = true;
	}
	if (_group == "")    {_group = "reload";}
    if (_locator == "")
    {
    	float locx, locy, locz;
        GetCharacterPos(_compCharacter, &locx, &locy, &locz);
        _locator = LAi_FindNearestFreeLocator(_group, locx, locy, locz);
    }
    LAi_ActorGoToLocation(_compCharacter, _group, _locator, "none", "", "", "", _timeToGoOut);
    _mainCharacter.GenQuest.CallFunctionParam = "Character_into_companion";
    _mainCharacter.GenQuest.CallFunctionParam.CharacterIntoCompanion.Id = _compCharacter.id;
    _mainCharacter.GenQuest.CallFunctionParam.CharacterIntoCompanion.Remove = _compRemove;
    DoQuestCheckDelay("CallFunctionParam", _timeToGoOut);
}

void Character_into_companion()    // относится к методу выше.
{
    ref NPChar = characterFromID(PChar.GenQuest.CallFunctionParam.CharacterIntoCompanion.Id);
    SetCompanionIndex(pchar, -1, getcharacterIndex(PChar.GenQuest.CallFunctionParam.CharacterIntoCompanion.Id));
    if (PChar.GenQuest.CallFunctionParam.CharacterIntoCompanion.Remove == false)    {SetCharacterRemovable(npchar, false);}
	//снимать запрет, только если он установлен этим методом
	if (CheckAttribute(PChar, "GenQuest.CallFunctionParam.CharacterIntoCompanion.FastReload")) bDisableFastReload = false;
}

string GetBookData(int day, int mn, int year)
{
	string result = "";

	if (day < 10)
	{
	    result = result + "0";
	}
	result = result + day + ".";
	if (mn < 10)
	{
	    result = result + "0";
	}
	result = result + mn + "." + year;

    return result;
}

// ========>>>>>> квест Аззи, подсчет контрольных сумм по неуязвимости =================
void AzzyCheckSumControl()
{
    int   QtyKilled, Result;
    float CurHP, MaxHP;

	if (CheckAttribute(pchar, "questTemp.Azzy.Immortal"))
    {
        QtyKilled = Statistic_AddValue(pchar, "Solder_s", 0) +
                    Statistic_AddValue(pchar, "Solder_g", 0) +
                    Statistic_AddValue(pchar, "Warrior_s", 0) +
                    Statistic_AddValue(pchar, "Warrior_g", 0) +
                    Statistic_AddValue(pchar, "Citizen_s", 0) +
                    Statistic_AddValue(pchar, "Citizen_g", 0) +
                    Statistic_AddValue(pchar, "Monster_s", 0) +
                    Statistic_AddValue(pchar, "Monster_g", 0) -
                    sti(pchar.questTemp.Azzy.Immortal.EarlyKilled);
        pchar.questTemp.Azzy.Immortal.AllQuota = makeint(pchar.questTemp.Azzy.Immortal.AllQuota) + sti(pchar.questTemp.Azzy.Immortal.DayQuota);
        Result = QtyKilled - sti(pchar.questTemp.Azzy.Immortal.AllQuota);
        if (Result < 0)
        {
            MaxHP = LAi_GetCharacterMaxHP(pchar);
            CurHP = LAi_GetCharacterHP(pchar);
            MaxHP = MaxHP - 5;
            pchar.questTemp.Azzy.Immortal.Penalty = makeint(pchar.questTemp.Azzy.Immortal.Penalty) + 5;
            if (!CheckAttribute(pchar, "questTemp.Azzy.OK"))
            {
                pchar.questTemp.Azzy = "HowToKnowAzzy";
                pchar.questTemp.Azzy.OK = 1;
                AddLandQuestmark_Main(CharacterFromID("Ascold"), "Azzy_HellSign");
            }
            if (MaxHP < 1)
            {
                LAi_KillCharacter(pchar);
                Log_SetStringToLog(StringFromKey("QuestsUtilite_1"));
            }
            else
            {
                Log_SetStringToLog(StringFromKey("QuestsUtilite_2"));
            }
            LAi_SetHP(pchar, CurHP, MaxHP);
        }
        if (GetQuestPastDayParam("questTemp.Azzy.Immortal") > 30)
        {
            pchar.questTemp.Azzy.Immortal.DayQuota = makeint(pchar.questTemp.Azzy.Immortal.DayQuota) * 2;
            SaveCurrentQuestDateParam("questTemp.Azzy.Immortal");
        }
        pchar.questTemp.Azzy.Immortal.CurKilled = QtyKilled;
        pchar.questTemp.Azzy.Immortal.CurBalance = Result;
        DeleteQuestHeader("Azzy_HellSign");
		if (sti(pchar.questTemp.Azzy.Immortal.Penalty) > 0)
		{		
			AddQuestRecord("Azzy_HellSign", "2");	
			AddQuestUserData("Azzy_HellSign", "Penalty", pchar.questTemp.Azzy.Immortal.Penalty);
		}
		AddQuestRecord("Azzy_HellSign", "1");
		AddQuestUserData("Azzy_HellSign", "sName", GetMainCharacterNameGen());
		AddQuestUserData("Azzy_HellSign", "DayQuota", pchar.questTemp.Azzy.Immortal.DayQuota);
		AddQuestUserData("Azzy_HellSign", "AllQuota", pchar.questTemp.Azzy.Immortal.AllQuota);
		AddQuestUserData("Azzy_HellSign", "CurKilled", pchar.questTemp.Azzy.Immortal.CurKilled);
		AddQuestUserData("Azzy_HellSign", "CurBalance", pchar.questTemp.Azzy.Immortal.CurBalance);
    }
}
// <<<<<======== квест Аззи, подсчет контрольныйх сумм по неуязвимости =================

// репутация плохого парня с границами
bool isBadReputation(ref _pchar, int _rep)
{
    if (GetCharacterPerkUsing(_pchar, "Trustworthy") || sti(_pchar.reputation) >= _rep)
    {
        return false;// good guy
    }
    return true;// bad guy
}

// ugeen --> вычисление ранга квестовых проитвников в зависимости от ранга ГГ и уровня сложности
int SetQuestCharacterRank()
{
	int rank = 25 + makeint(sti(pchar.rank)*(0.1 + MOD_SKILL_ENEMY_RATE));

	return rank;
}
// <-- ugeen

// ==> две функции Эдди для крутизны невероятной.
void FantomMakeCoolSailor(ref _Character, int _ShipType, string _ShipName, int _CannonsType, int _Sailing, int _Accuracy, int _Cannons)
{
    if (_CannonsType == CANNON_TYPE_LBS_BY_SHIP) SetShipSuitableCannons(_ShipType, "");
    else _Character.Ship.Cannons.Type = _CannonsType;
	_Character.skill.Sailing  = GetCoffDiff(_Sailing, SKILL_MAX);
	_Character.skill.Accuracy = GetCoffDiff(_Accuracy, SKILL_MAX);
	_Character.skill.Cannons  = GetCoffDiff(_Cannons, SKILL_MAX);
	//_Character.skill.Grappling  = GetCoffDiff((_Cannons+_Accuracy)/2, SKILL_MAX); //zagolski. расчёт абордажа и защиты
	//_Character.skill.Defence  = GetCoffDiff((_Sailing+_Accuracy)/2, SKILL_MAX);
    
    _Character.DontRansackCaptain = true; //квестовые не сдаются
    _Character.SinkTenPercent     = false; // не тонуть при 10%, не убегать в бою
    _Character.AboardToFinalDeck  = true; // абордаж всегда
	_Character.DontClearDead      = true;
	_Character.SaveItemsForDead   = true;
	_Character.AlwaysSandbankManeuver = true;

    _Character.Ship.Type = GenerateShipExt(_ShipType, true, _Character);
    if (_ShipName == "none" || _ShipName == "") {SetRandomNameToShip(_Character);}
    else {_Character.Ship.Name = _ShipName;}

    SetBaseShipData(_Character);
    SetCrewQuantityFull(_Character);
    Fantom_SetBalls(_Character, "pirate");

	SetCharacterPerk(_Character, "FastReload");
	SetCharacterPerk(_Character, "HullDamageUp");
	SetCharacterPerk(_Character, "SailsDamageUp");
	SetCharacterPerk(_Character, "CrewDamageUp");
	SetCharacterPerk(_Character, "CriticalShoot");
	SetCharacterPerk(_Character, "LongRangeShoot");
	SetCharacterPerk(_Character, "CannonProfessional");
	SetCharacterPerk(_Character, "ShipDefenseProfessional");
	SetCharacterPerk(_Character, "ShipSpeedUp");
	SetCharacterPerk(_Character, "ShipTurnRateUp");

	ShipOverhaul(_Character);
    DeleteAttribute(_Character, "Killer.status"); // снять аттрибут 'был захвачен на абордаж'
    _Character.questTemp.abordage = 0; //снять аттрибут отказа повторного захвата
   	DeleteAttribute(_Character, "Abordage.Enable"); //снять невозможноть абордажа
}

//Jason, функция уменьшенного кулсейлора + скилл защиты и абордажа
void FantomMakeSmallSailor(ref _Character, int _ShipType, string _ShipName, int _CannonsType, int _Sailing, int _Accuracy, int _Cannons, int _Grappling, int _Defence)
{
    if (_CannonsType == CANNON_TYPE_LBS_BY_SHIP) SetShipSuitableCannons(_ShipType, "");
    else _Character.Ship.Cannons.Type = _CannonsType;
	_Character.skill.Sailing  = GetCoffDiff(_Sailing, SKILL_MAX);
	_Character.skill.Accuracy = GetCoffDiff(_Accuracy, SKILL_MAX);
	_Character.skill.Cannons  = GetCoffDiff(_Cannons, SKILL_MAX);
	_Character.skill.Grappling  = GetCoffDiff(_Grappling, SKILL_MAX);
	_Character.skill.Defence  = GetCoffDiff(_Defence, SKILL_MAX);
	
    _Character.DontRansackCaptain = true; //квестовые не сдаются
    _Character.SinkTenPercent     = false; // не тонуть при 10%, не убегать в бою
    _Character.AboardToFinalDeck  = true; // абордаж всегда
	_Character.AlwaysSandbankManeuver = true;

    _Character.Ship.Type = GenerateShipExt(_ShipType, true, _Character);
    if (_ShipName == "none" || _ShipName == "") {SetRandomNameToShip(_Character);}
    else {_Character.Ship.Name = _ShipName;}

    SetBaseShipData(_Character);
    SetCrewQuantityFull(_Character);
    Fantom_SetBalls(_Character, "pirate");

	SetCharacterPerk(_Character, "HullDamageUp");
	SetCharacterPerk(_Character, "SailsDamageUp");
	SetCharacterPerk(_Character, "CrewDamageUp");
	SetCharacterPerk(_Character, "AdvancedBattleState");
	SetCharacterPerk(_Character, "ShipSpeedUp");
	SetCharacterPerk(_Character, "ShipTurnRateUp");
	SetCharacterPerk(_Character, "Doctor1");
	SetCharacterPerk(_Character, "LongRangeGrappling");

    ShipOverhaul(_Character);
    DeleteAttribute(_Character, "Killer.status"); // снять аттрибут 'был захвачен на абордаж'
    _Character.questTemp.abordage = 0; //снять аттрибут отказа повторного захвата
   	DeleteAttribute(_Character, "Abordage.Enable"); //снять невозможноть абордажа
}

void FantomMakeCoolFighter(ref _Character, int _Rank, int _Fencing, int _Pistol, string _Blade, string _Gun, float _AddHP)
{
    _Character.rank = GetCoffDiff(_Rank, 1000);
    _Character.skill.Fencing = GetCoffDiff(_Fencing, SKILL_MAX);
    _Character.Skill.FencingLight  = GetCoffDiff(sti(_Character.skill.Fencing), SKILL_MAX);
    _Character.Skill.FencingHeavy  = GetCoffDiff(sti(_Character.skill.Fencing), SKILL_MAX);
    _Character.skill.Pistol = GetCoffDiff(_Pistol, SKILL_MAX);
    _Character.skill.Fortune = GetCoffDiff(_Pistol, SKILL_MAX); //zagolski. если умеет хорошо стрелять из пистоля, то умеет и хорошо от него защищаться
	_Character.chr_ai.hp = stf(_Character.chr_ai.hp) + GetCoffDiff(_AddHP, 5000);
	_Character.chr_ai.hp_max = stf(_Character.chr_ai.hp_max) + GetCoffDiff(_AddHP, 5000);
	SetCharacterPerk(_Character, "Energaiser"); // скрытый перк даёт 1.5 к приросту энергии, дается ГГ и боссам уровней
	SetCharacterPerk(_Character, "SwordplayProfessional");
	SetCharacterPerk(_Character, "AdvancedDefense");
	SetCharacterPerk(_Character, "CriticalHit");
	SetCharacterPerk(_Character, "Sliding");
	SetCharacterPerk(_Character, "HardHitter");
	_Character.canDodge = true;	// EvgAnat - кулфайтеры отскакивают от выстрелов
	DeleteAttribute(_Character, "Items");
	_Character.SuperShooter  = true;

	if (_Blade == "auto")
		_Blade = LAi_NPC_EquipBladeSelection(_Character); // Rosarak

	if (_Blade != "")
		_Blade += ",";

	ItemTakeEquip(_Character, _Blade + "spyglass3", 1);
	ItemTakeEx(_Character, "potion1,potion2", "" + (rand(MOD_SKILL_ENEMY_RATE)+1) + "," + (rand(2)+1));
	
    if (_Gun != "")
	{
        if (IsMusket(_Gun))
        {
            SetCharacterPerk(_Character, "MusketsTraining");
			_Character.MushketType = _Gun;
			//_Character.MushketBulletType = _Bullet; // ~!mu
			LAi_NPC_MushketerEquip(_Character);
        }
        else
        {
            string sAmmo = "bullet";
            if (_Gun == "auto") _Gun = LAi_NPC_EquipGunSelection(_Character);
            ItemTakeEquip(_Character, _Gun, 0);
            if (_Gun == "pistol3")  sAmmo = "grapeshot";
            if (LAi_GetAmmoGunpowderType(sAmmo) != "")
                sAmmo += "," + LAi_GetAmmoGunpowderType(sAmmo);
            ItemTakeEx(_Character, sAmmo, "" + (30+rand(20)));
        }
	}

    FaceMaker(_Character);
    SetNewModelToChar(_Character);  // перерисуем модель на лету
}

int GetCoffDiff(float _num, int _maxRange)
{
	switch (MOD_SKILL_ENEMY_RATE)
	{
		case  1: _num *= 0.6;  break;
		case  2: _num *= 0.75; break;
		case  3: _num *= 0.85; break;
		case  4: _num *= 0.9;  break;
		case  5: _num *= 0.95; break;
		case  6: _num *= 1;    break;
		case  7: _num *= 1.1;  break;
		case  8: _num *= 1.2;  break;
		case  9: _num *= 1.3;  break;
		case 10: _num *= 1.5;  break;
	}
	_num += 0.5;
	if (_num > _maxRange) return _maxRange;
	else return sti(_num);
}

// ==> Метод открытия\закрытия локаторов релоад. Если _flag=true - закрыть локатор, если _flag=false - открыть.
void LocatorReloadEnterDisable(string _locationID, string _locator, bool _flag)
{
    aref arDis, arRld;
	makearef(arRld, Locations[FindLocation(_locationID)].reload);
	int	Qty = GetAttributesNum(arRld);
	for (int i=0; i<Qty; i++)
	{
		arDis = GetAttributeN(arRld, i);
        if (arDis.name == _locator)
        {
    		if (_flag) arDis.disable = 1;
    		else DeleteAttribute(arDis, "disable");
            break;
        }
	}
}

//===>>> Функции по работе с диалоговыми файлами. Эдди. ================================================================
// == _strNormal - обычная строка диалога
// == _strBad1, _strBad2, _strBad3 - строки степени возмущения,  "" и "none" - базовый набор.
// == _kind - вид возмущения: "repeat" - снимается на следующий день при условии, что НПС вконец не разозлился (не задействован анги-файл).
//                            "quest"  - квестовые повторялки, не снимаются на следующий день, но может быть задан срок примирения после перевода на ангри.
//                            "block"  - реакцию НПС на повторные клики без включения ангри, для того, чтобы обозначить интеллект, но не ругаться. Ангри вообще не делать.
//                            "cycle"  - крутим цикл из повторялок, ангри не заряжать. На след. день все снимается.
// == _terms для "repeat" и "quest" - сроки в днях примирения само-собой после задействоания ангри-файла, если == 0, то ругань навсегда (примерение только через подарки).
//    _terms для "block" - сроки возврата в норму в днях, если 0 - навсегда.
// == _character и _Node - npchar и Dialog.CurrentNode

string NPCStringReactionRepeatNumber(string _kind, int _terms, ref _character, string _Node)
{
	_Node = stripblank(_Node); //fix spaces
	string strBack;
	string strTemp = "quest.repeat." + _Node;
	if (!CheckAttribute(_character , strTemp))
	{
		return "0";
	}
	if (_kind == "cycle" || _kind == "repeat") //на след.день все снимается.
	{
		if (GetNpcQuestPastDayParam(_character, strTemp) >= 1)
		{
			return "0";
		}
	}
	else
	{
		if (GetNpcQuestPastDayParam(_character, strTemp) >= _terms && _terms!=0 && _kind != "quest") //снятие по "block"
		{
			return "0";
		}
	}

	return _character.quest.repeat.(_Node);
}

string NPCStringReactionRepeat(string _strNormal, string _strBad1, string _strBad2, string _strBad3, string _kind, int _terms, ref _character, string _Node)
{
    _Node = stripblank(_Node); //fix spaces
	string strBack;
    string strTemp = "quest.repeat." + _Node;
    if (!CheckAttribute(_character , strTemp))
    {
        _character.quest.repeat.(_Node) = 0;
        _character.quest.repeat.(_Node).ans = 0;
    }
    if (_kind == "cycle" || _kind == "repeat") //на след.день все снимается.
    {
        if (GetNpcQuestPastDayParam(_character, strTemp) >= 1)
        {
            _character.quest.repeat.(_Node) = 0;
            _character.quest.repeat.(_Node).ans = 0;
        }
    }
    else
    {
        if (GetNpcQuestPastDayParam(_character, strTemp) >= _terms && _terms!=0 && _kind != "quest") //снятие по "block"
        {
            _character.quest.repeat.(_Node) = 0;
            _character.quest.repeat.(_Node).ans = 0;
        }
    }
    switch(_character.quest.repeat.(_Node))
	{
        case "0":
            strBack = _strNormal;
            _character.quest.repeat.(_Node) = 1;
            _character.quest.repeat.(_Node).ans = 0;
            SaveCurrentNpcQuestDateParam(_character, strTemp);
        break;
        case "1":
            if (_strBad1 == "none" || _strBad1 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_5"),
                          StringFromKey("QuestsUtilite_6"),
                          StringFromKey("QuestsUtilite_7"));
            }
            else
            {
                strBack = _strBad1;
            }
            _character.quest.repeat.(_Node) = 2;
            _character.quest.repeat.(_Node).ans = 1;
        break;
        case "2":
            if (_strBad2 == "none" || _strBad2 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_8"),
                          StringFromKey("QuestsUtilite_9"),
                          StringFromKey("QuestsUtilite_10"));
            }
            else
            {
                strBack = _strBad2;
            }
            _character.quest.repeat.(_Node) = 3;
            _character.quest.repeat.(_Node).ans = 2;
        break;
        case "3":
            if (_strBad3 == "none" || _strBad3 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_12"),
                          StringFromKey("QuestsUtilite_13"),
                          StringFromKey("QuestsUtilite_11", pchar) + StringFromKey("QuestsUtilite_26"));
            }
            else
            {
                strBack = _strBad3;
            }
            // ==> Реакция на третье повторение.
            if (_kind == "cycle") //снова на первую строку.
            {
			    _character.quest.repeat.(_Node) = 0;
            }
			else
            {
                if(_kind != "block") //если block, то опять в последнюю строку
                {
                    _character.quest.repeat.(_Node) = 4;
                    CharacterAddAngry(_character, _Node, _kind, _terms);
    			}
            }
            _character.quest.repeat.(_Node).ans = 3;
        break;
        case "4":
            strBack = "NPCStringReactionRepeat error!!!";
        break;
	}
    return strBack;
}

string HeroStringReactionRepeat(string _strNormal, string _strBad1, string _strBad2, string _strBad3, ref _character, string _Node)
{
    _Node = stripblank(_Node); //fix spaces
	string strBack;
    switch(_character.quest.repeat.(_Node).ans)
	{
        case "0":
            strBack = _strNormal;
        break;
        case "1":
            if (_strBad1 == "none" || _strBad1 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_15"),
                          StringFromKey("QuestsUtilite_16"),
                          StringFromKey("QuestsUtilite_14"));
            }
            else
            {
                strBack = _strBad1;
            }
        break;
        case "2":
            if (_strBad2 == "none" || _strBad2 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_17"),
                          StringFromKey("QuestsUtilite_18"),
                          StringFromKey("QuestsUtilite_19"));
            }
            else
            {
                strBack = _strBad2;
            }
        break;
        case "3":
            if (_strBad3 == "none" || _strBad3 == "")
            {
                strBack = LinkRandPhrase(StringFromKey("QuestsUtilite_20"),
                          StringFromKey("QuestsUtilite_21"),
                          StringFromKey("QuestsUtilite_22"));
            }
            else
            {
                strBack = _strBad3;
            }
        break;
        case "4":
            strBack = "HeroStringReactionRepeat error!!!";
        break;
	}
    return strBack;
}

// возможны только две переходные ноды: _GoNode1 и _GoNode2, третья не нужна, т.к. идет сразу в ангри-файл.
// неверно, оставил третью ноду для циклов и прочего.
string DialogGoNodeRepeat(string _NormalNode, string _GoNode1, string _GoNode2, string _GoNode3, ref _character, string _Node)
{
    _Node = stripblank(_Node); //fix spaces
	string strBack, Temp;
    Temp = sti(_character.quest.repeat.(_Node).ans);
    switch(Temp)
	{
        case "0":
            strBack = _NormalNode;
        break;
        case "1":
            if (_GoNode1 == "none" || _GoNode1 == "")
            {
                strBack = "exit";
            }
            else
            {
                strBack = _GoNode1;
            }
        break;
        case "2":
            if (_GoNode2 == "none" || _GoNode2 == "")
            {
                strBack = "exit";
            }
            else
            {
                strBack = _GoNode2;
            }
        break;
        case "3":
            if (_GoNode3 == "none" || _GoNode3 == "")
            {
                strBack = "exit";
            }
            else
            {
                strBack = _GoNode3;
            }
        break;
        case "4":
            strBack = "exit";
            Log_SetStringToLog("DialogGoNodeRepeat#4 error!!!");
        break;
    }
    return strBack;
}

// _Node - имя ноды, идентификатор текущей ангри. Если метод вызывается не в диалоговом файле, то == "none".
void CharacterAddAngry(ref _character, string _Node, string _kind, int _terms)
{
    if (_kind == "repeat" || _kind == "quest")
    {
        DeleteAttribute(_character, "angry");
        _character.angry.kind = _kind;
        _character.angry.name = _Node; //и имя ноды тоже, для расфасовки разных ангри
        if (_terms != 0) // если == 0, то ссора непроходящая с течением времени.
        {
            _character.angry.terms = _terms;
            SaveCurrentNpcQuestDateParam(_character, "angry.terms");
            if (_terms < 10) // размер вознаграждения за примирение, анти с/л
            {
                _character.angry.QtyMoney = (rand(10)+1) * 500;
            }
            else
            {
                _character.angry.QtyMoney = (rand(10)+1) * 5000;
            }
        }
        else
        {
            _character.angry.QtyMoney = (rand(10)+1) * 10000;
        }
    }
    else {Log_Info("CharacterAddAngry error!!!");}
}

void CharacterDelAngry(ref _character)
{
    DeleteAttribute(_character, "angry");
    DeleteAttribute(_character, "quest.repeat");
}

//В условиях возможного тотального применения ангри по квестам, нужно подстраховаться.
//Если нода дается НПС в момет, когда у него задействован ангри, то нода будет возвращена после примирения.
//Соотв. менять ноды желательно данным методом.
void QuestSetCurrentNode(string _chID, string _Node)
{
    ref chref = characterFromID(_chID);
    if (CheckAttribute(chref, "angry")) chref.dialog.TempNode = _Node;
    else chref.dialog.currentnode = _Node;
}
/*
void SaveCurrentNodeAndSetNew(string _chID, string _Node)
{	//HardCoffee сохранить ноды предыдущего квеста при взятии нового
	ref chref = characterFromID(_chID);
	if (CheckAttribute(chref, "dialog.currentnode"))
		chref.dialog.BackupCurrent = chref.dialog.currentnode;
	if (CheckAttribute(chref, "dialog.TempNode"))
		chref.dialog.BackupTemp = chref.dialog.TempNode;
	QuestSetCurrentNode(_chID, _Node);
}

void RestoreSavedNodes(ref rChr)
{
	if (CheckAttribute(rChr, "dialog.BackupCurrent"))
	{
		rChr.dialog.currentnode = rChr.dialog.BackupCurrent;
		DeleteAttribute(rChr, "dialog.BackupCurrent");
	}

	if (CheckAttribute(rChr, "dialog.BackupTemp"))
	{
		rChr.dialog.TempNode = rChr.dialog.BackupTemp;
		DeleteAttribute(rChr, "dialog.BackupTemp");
	}
}
*/
// фраза от пола НПС
string NPCharSexPhrase(ref _character, string StrMan, string StrWoman)
{
    if (_character.sex == "woman") return StrWoman;
    else return StrMan;
}
// фраза от пола ГГ
string GetSexPhrase(string StrMan, string StrWoman)
{
    return NPCharSexPhrase(PChar, StrMan, StrWoman);
}
// окончание фразы от пола ГГ в языках, которых это уместно
string GetLangSexPhrase(string StrMan, string StrWoman)
{
	return GetLangNPCharSexPhrase(pchar, StrMan, StrWoman);
}
// окончание фразы от пола НПС в языках, которых это уместно
string GetLangNPCharSexPhrase(ref _character, string StrMan, string StrWoman)
{
	if (LanguageGetLanguage() == "russian")
		return NPCharSexPhrase(_character, StrMan, StrWoman);
	else
		return "";
}
//<<<=== Функции по работе с диалоговыми файлами. =======================================================================


// Временно сохранить все данные о нашем корабле в памяти
//--------------------------------------------------------
bool SetTempRemoveParam(ref _refCharacter, string _param)
{
    string sParam = "TmpRemember" + _param;
    
	if( CheckAttribute(_refCharacter, sParam) ) return false;
	if( !CheckAttribute(_refCharacter, _param) ) return false;

	aref dstRef; makearef(dstRef, _refCharacter.(sParam));
	aref srcRef; makearef(srcRef, _refCharacter.(_param));

	CopyAttributes(dstRef,srcRef);
	return true;
}

// Восстановить данные о нашем старом корабле из памяти
//------------------------------------------------------
bool RestoreTempRemoveParam(ref _refCharacter, string _param)
{
    string sParam = "TmpRemember" + _param;
    
	if( !CheckAttribute(_refCharacter, sParam) ) return false;

	aref dstRef; makearef(dstRef, _refCharacter.(_param));
	aref srcRef; makearef(srcRef, _refCharacter.(sParam));

	DeleteAttribute(_refCharacter, _param);
	//--> eddy. структура быть должна, иначе вылет в винду.
	_refCharacter.(_param) = "";
	CopyAttributes(dstRef,srcRef);
	DeleteAttribute(_refCharacter, sParam);
	return true;
}

// установка отмены боевки в резиденции при захвате города
// ВАЖНО: работает только не в пиратском городе - иначе это просто мятеж и губернатора там нет вообще
void SetCaptureResidenceQuest(string _city, string _method, bool _majorOff)
{
    PChar.GenQuestFort.ResidenceQuest.(_city) = true;
    // убирать ли губернатора из локации вообще, он пропадет, но потом обратно пропишется, чтоб не рушить мир игры.
    PChar.GenQuestFort.ResidenceQuest.(_city).MayorOff = _majorOff;
    if (_method != "")
    {
        PChar.GenQuestFort.ResidenceQuest.(_city).method = _method;
	}
}

// вернём диалог после разговора и спрячем
void  SetReturn_Gover_Dialog_Exit(ref NPChar)
{
	LAi_LoginInCaptureTown(NPChar, false);

	PChar.GenQuest.GoverIdx = NPChar.index;
	Pchar.quest.Return_Gover_Dialog_Exit.win_condition.l1          = "ExitFromLocation";
    Pchar.quest.Return_Gover_Dialog_Exit.win_condition.l1.location = Pchar.location;
    Pchar.quest.Return_Gover_Dialog_Exit.win_condition             = "Return_Gover_Dialog_Exit";
}

void SetNewModelToChar(ref chref)
{
    float liveTime = 0.1;
	int colors = argb(64, 64, 64, 64);
	int colore = argb(0, 32, 32, 32);
	ref rItem;

    if (IsEntity(chref))
    {
    	if(CheckAttribute(chref, "model"))
        {
            SendMessage(chref, "lss",   MSG_CHARACTER_SETMODEL, chref.model, chref.model.animation);
        }
        if(CheckAttribute(chref, "equip.gun"))
        {
            SendMessage(chref, "ls",    MSG_CHARACTER_SETGUN,   chref.equip.gun);
        }
        if(CheckAttribute(chref, "equip.blade"))
        {
			rItem = ItemsFromID(chref.equip.blade);
            //SendMessage(chref, "lsfll", MSG_CHARACTER_SETBLADE, chref.equip.blade, liveTime, colors, colore);
            //SendMessage(chref, "llsfll", MSG_CHARACTER_SETBLADE, 0, chref.equip.blade, liveTime, colors, colore);
			SendMessage(chref, "llsfll", MSG_CHARACTER_SETBLADE, 0, rItem.model, liveTime, colors, colore);
        }
		if(CheckAttribute(chref, "equip.musket"))
        {
			rItem = ItemsFromID(chref.equip.musket);
            SendMessage(chref, "ls", MSG_CHARACTER_SETMUS, rItem.model);
        }
    }
}
// функции из квест_реакшн
void SetNationToOfficers(int _nat)
{
    int j, cn;
    ref officer;

    for(j=1; j<COMPANION_MAX; j++)
    {
        cn = GetCompanionIndex(GetMainCharacter(),j);
        if( cn>0 )
        {
	        officer = GetCharacter(cn);
	        if (!GetRemovable(officer) && !CheckAttribute(officer, "Capellan")) continue;
	        officer.nation = _nat;
	        Ship_FlagRefresh(officer); //флаг на лету
	    }
	}
}

bool IsOfficerCompanion(ref _refCharacter)
{
	int findIdx = sti(_refCharacter.index);
	ref mc = GetMainCharacter();
	int ci, cn;
	ref npc;
	for(int i=1; i<COMPANION_MAX; i++)
	{
		ci = GetCompanionIndex(mc,i);
		npc = GetCharacter(ci);
		for(int j=1; j<4; j++)
		{
			if(GetOfficersIndex(npc,j)==findIdx) return true;
		}
	}
	return false;
}
///////////////////////////////////////////////////////////////////
// установка квестовых товаров и цен
void SetQuestGoodsToStore(ref refStore)
{
	string    goodName;
	// пример использования по квест_реакшн
	/*
	pchar.GenQuest.StoreGoods.StoreIdx = Bridgetown_STORE;
	pchar.GenQuest.StoreGoods.NowNeedToBe = true;
	*/
	if (CheckAttribute(pchar, "GenQuest.StoreGoods.StoreIdx") && refStore.index == pchar.GenQuest.StoreGoods.StoreIdx)
	{
        // пример обработки события
		/*if (CheckAttribute(pchar, "GenQuest.StoreGoods.NowNeedToBe")) // состояние говорящие, то нужно делать
		{
		    DeleteAttribute(pchar, "GenQuest.StoreGoods"); // одноразовая операция, трем обе ветки
		    goodName = Goods[GOOD_RUM].Name;
		    refStore.Goods.(goodName).Quantity       = 666;
		    // цена из обратного вычисления 20 в модификатор
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_RUM, PRICE_TYPE_BUY, pchar, 20);
		}  */
		if (CheckAttribute(pchar, "GenQuest.StoreGoods.HL2_DiscountPrices")) //Голл.линейка, квест №2, дискаунт в форте Оранж.
		{
		    DeleteAttribute(pchar, "GenQuest.StoreGoods"); // одноразовая операция, трем обе ветки
			goodName = Goods[GOOD_EBONY].Name;
		    pchar.questTemp.HL2Save.EbonyQty = refStore.Goods.(goodName).Quantity;
		    refStore.Goods.(goodName).Quantity       = 400;
		    pchar.questTemp.HL2Save.EbonyPrice = GetStoreGoodsPrice(refStore, GOOD_EBONY, PRICE_TYPE_BUY, pchar, refStore.Goods.(goodName).RndPriceModify);
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_EBONY, PRICE_TYPE_BUY, pchar, 10);

		    goodName = Goods[GOOD_COFFEE].Name;
		    pchar.questTemp.HL2Save.CoffeeQty = refStore.Goods.(goodName).Quantity;
		    refStore.Goods.(goodName).Quantity       = 400;
		    pchar.questTemp.HL2Save.CoffeePrice = GetStoreGoodsPrice(refStore, GOOD_COFFEE, PRICE_TYPE_BUY, pchar, refStore.Goods.(goodName).RndPriceModify);
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 9);

		    goodName = Goods[GOOD_MAHOGANY].Name;
		    pchar.questTemp.HL2Save.MahoganyQty = refStore.Goods.(goodName).Quantity;
		    refStore.Goods.(goodName).Quantity       = 400;
		    pchar.questTemp.HL2Save.MahoganyPrice =  GetStoreGoodsPrice(refStore, GOOD_MAHOGANY, PRICE_TYPE_BUY, pchar, refStore.Goods.(goodName).RndPriceModify);
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_MAHOGANY, PRICE_TYPE_BUY, pchar, 14);

		    goodName = Goods[GOOD_SANDAL].Name;
		    pchar.questTemp.HL2Save.SandalQty = refStore.Goods.(goodName).Quantity;
		    refStore.Goods.(goodName).Quantity       = 400;
		    pchar.questTemp.HL2Save.SandalPrice = GetStoreGoodsPrice(refStore, GOOD_SANDAL, PRICE_TYPE_BUY, pchar, refStore.Goods.(goodName).RndPriceModify);
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_SANDAL, PRICE_TYPE_BUY, pchar, 11);
        	pchar.GenQuest.StoreGoods.StoreIdx = FortOrange_STORE; //держим цены для след. посещений
        	pchar.GenQuest.StoreGoods.HL2_AgainDiscount = true;
        	AddLandQuestmark_Main_WithCondition(characterFromID("FortOrange_trader"), "Hol_Line", "HolLine_2_FortOrangeStore_QuestMarkCondition");
		}
		if (CheckAttribute(pchar, "GenQuest.StoreGoods.HL2_AgainDiscount")) //Голл.линейка, квест №2, держим дисконтные цены
		{
		    goodName = Goods[GOOD_EBONY].Name;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_EBONY, PRICE_TYPE_BUY, pchar, 10);

		    goodName = Goods[GOOD_COFFEE].Name;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 9);

		    goodName = Goods[GOOD_MAHOGANY].Name;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_MAHOGANY, PRICE_TYPE_BUY, pchar, 14);

		    goodName = Goods[GOOD_SANDAL].Name;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_SANDAL, PRICE_TYPE_BUY, pchar, 11);
		}		
		if (CheckAttribute(pchar, "GenQuest.StoreGoods.HL2_QtyPriceIsBack")) //Голл.линейка, квест №2, возврат цен и кол-ва после квеста.
		{
            DeleteAttribute(pchar, "GenQuest.StoreGoods"); // одноразовая операция, трем обе ветки
		    goodName = Goods[GOOD_EBONY].Name;
		    refStore.Goods.(goodName).Quantity       = pchar.questTemp.HL2Save.EbonyQty;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_EBONY, PRICE_TYPE_BUY, pchar, sti(pchar.questTemp.HL2Save.EbonyPrice));

		    goodName = Goods[GOOD_COFFEE].Name;
		    refStore.Goods.(goodName).Quantity       = pchar.questTemp.HL2Save.CoffeeQty;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_COFFEE, PRICE_TYPE_BUY, pchar, sti(pchar.questTemp.HL2Save.CoffeePrice));

		    goodName = Goods[GOOD_MAHOGANY].Name;
		    refStore.Goods.(goodName).Quantity       = pchar.questTemp.HL2Save.MahoganyQty;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_MAHOGANY, PRICE_TYPE_BUY, pchar, sti(pchar.questTemp.HL2Save.MahoganyPrice));

		    goodName = Goods[GOOD_SANDAL].Name;
		    refStore.Goods.(goodName).Quantity       = pchar.questTemp.HL2Save.SandalQty;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_SANDAL, PRICE_TYPE_BUY, pchar, sti(pchar.questTemp.HL2Save.SandalPrice));
            DeleteAttribute(pchar, "questTemp.HL2Save");
        }
		if (CheckAttribute(pchar, "GenQuest.StoreGoods.HL5_ThreeFleutes")) //Голл.линейка, квест №5, добавляем количества.
		{
            DeleteAttribute(pchar, "GenQuest.StoreGoods"); // одноразовая операция, трем обе ветки
            goodName = Goods[GOOD_FOOD].Name;
		    refStore.Goods.(goodName).Quantity       = 100000;
			refStore.Goods.(goodName).RndPriceModify = GetStoreGoodsRndPriceModify(refStore, GOOD_FOOD, PRICE_TYPE_BUY, pchar, 10);

        }
	}
}

void HolLine2_NullGoods() //для второго квеста голл. линейки.
{
    ref sld;
    int chComp;
    if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) pchar.Ship.Cargo.Goods.Ebony = 0;
    if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) pchar.Ship.Cargo.Goods.Coffee = 0;
    if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) pchar.Ship.Cargo.Goods.Mahogany = 0;
    if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) pchar.Ship.Cargo.Goods.Sandal = 0;
    for (int i=1; i<=COMPANION_MAX; i++)
	{
        chComp = GetCompanionIndex(pchar,i);
        if(chComp != -1)
		{
			sld = GetCharacter(chComp);
            if (CheckAttribute(pchar, "questTemp.EbonyQtyElseNeed")) sld.Ship.Cargo.Goods.Ebony = 0;
            if (CheckAttribute(pchar, "questTemp.CoffeeQtyElseNeed")) sld.Ship.Cargo.Goods.Coffee = 0;
            if (CheckAttribute(pchar, "questTemp.MahoganyQtyElseNeed")) sld.Ship.Cargo.Goods.Mahogany = 0;
            if (CheckAttribute(pchar, "questTemp.SandalQtyElseNeed")) sld.Ship.Cargo.Goods.Sandal = 0;
        }
    }
}

// метод обработки капитана в каюте на абордаже. Ставим проверку на минНР + дилог
// refChar - это фантом, а не реальный кэп, он копия, диалог от настоящего, но ИД и индекс не его, а фантомный, поэтому управляем имено этим актером
// CaptanId - реальный ИД кэпа, запомненный в момент копирования.
void SetQuestAboardCabinDialog(ref refChar)
{
	// пример. тут задаю для теста, всё это должно быть на изначальном капитане по квестам
	//refChar.DontClearDead      = true;
	//refChar.SaveItemsForDead   =   true;
	//TakeNItems(refChar, "Chest", 1);
	// пример. <--

	if (CheckAttribute(refChar, "CaptanId"))
	{
        pchar.GenQuest.QuestAboardCabinDialogIdx = refChar.index;
        // как использовать, пример
		/*if (true) // true - для теста, должно быть это CheckAttribute(pchar, "квестовая ветка, если нужно") && refChar.CaptanId == "IdNPC")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
            refChar.Dialog.Filename    = "Capitan_dialog.c";   // это нужно задать на изначальном кэпе в др месте
	    	refChar.Dialog.CurrentNode = "QuestAboardCabinDialog";
	    	// все остальное в диалоге, по образцу
		}*/
        //Голл. линейка, квест №7, доставка депеши до Тортуги
        if (refChar.CaptanId == "CaptainAttack_1" && pchar.questTemp.State == "DelivLettTortuga_NotFoundLetter")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		if (refChar.CaptanId == "AntonioDeBarras" && pchar.questTemp.State == "DelivLettTortuga_NotFoundLetter")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
        //Исп. линейка, квест №2, задания Инквизиции
		if (refChar.CaptanId == "JansenDeFonceicao" && CheckAttribute(pchar, "questTemp.State.Usurer"))
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		//Исп. линейка, квест №3, захват Рока Бразильца
		if (refChar.CaptanId == "RockBrasilian" && pchar.questTemp.State == "TakeRockBras_toNearestMaracaibo")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		//Исп. линейка, квест №7, спасение рядового Пардаля, базар с Моисеем Воклейном
		if (refChar.CaptanId == "CaptainAttack_1" && pchar.questTemp.State == "Sp7SavePardal_toAntigua")
		{
		    LAi_SetCheckMinHP(refChar, 50, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		if (refChar.CaptanId == "CaptainAttack_1" && pchar.questTemp.State == "Sp7SavePardal_PardalIsSink")
		{
		    LAi_SetCheckMinHP(refChar, 50, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		if (refChar.CaptanId == "CaptainAttack_1" && pchar.questTemp.State == "Sp8SaveCumana_toCumana")
		{
		    LAi_SetCheckMinHP(refChar, 50, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		//фр. линейка, квест №2, атака галеона испанских пиратов
		if (refChar.CaptanId == "CaptainAttack_1" && pchar.questTemp.State == "Fr2Letter_SeekProblems")
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		//капитан брига, который везет Изабеллу на убой Сальватору
		if (refChar.CaptanId == "IsaAttackCap" && pchar.RomanticQuest == "AttackBrig")
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		//капитан по квесту мэра на поиск и уничтожение пирата.
		if (refChar.CaptanId == "MQPirate" && CheckAttribute(pchar, "GenQuest.DestroyPirate"))
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.dialog.currentnode = "DestroyPirate_Abordage";
		}
		//засада на ГГ по наводке на купца homo
		if (HasSubStr(refChar.CaptanId, "_QuestMerchant") && trap)
		{
		    LAi_SetCheckMinHP(refChar, 30, true, "QuestAboardCabinDialog");  // сколько НР мин
		    refChar.dialog.filename = "Capitan_dialog.c";  //fix homo 23/03/07
			refChar.dialog.currentnode = "MerchantTrap_Abordage";
		}
		//капитан шебеки Синяя Птица
		if (refChar.CaptanId == "BlueBirdCapitain" && pchar.questTemp.BlueBird == "toSeaBattle")
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		//капитан шебеки Синяя Птица
		if (refChar.CaptanId == "BlueBirdTrader" && pchar.questTemp.BlueBird == "attackFleut")
		{
		    LAi_SetCheckMinHP(refChar, 20, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		//пиратка, Эдвард Лоу на бриге Морской Волк
		if (refChar.CaptanId == "EdwardLoy" && pchar.questTemp.piratesLine == "KillLoy_SeaWolfBattle")
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		//пиратка, квест №7, кэп, продавший Ласточку
		if (refChar.CaptanId == "LeonCapitain" && pchar.questTemp.piratesLine == "Soukins_seekLeon")
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		//квест возврата украденного корабля
		if (HasSubStr(refChar.CaptanId, "SeekCap_"))
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.CurrentNode = "SeekCap"; //даем абордажную ноду
		}
		//квест Вызволение из плена мужа горожанки
		if (refChar.CaptanId == "QuetionsPortPax_KoriBoll")
		{
		    LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		//квест горожанина по возвращения украденной жены
		if (HasSubStr(refChar.CaptanId, "SeekCitizCap_"))
		{
			if (refChar.quest.SeekCap == "manRapeWife")
			{
				LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
				refChar.Dialog.CurrentNode = "RapeWifeCap_Board"; //даем абордажную ноду
			}
		    if (refChar.quest.SeekCap == "womanRevenge")
			{
				LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
				refChar.Dialog.CurrentNode = "RevengeCap_board"; //даем абордажную ноду
			}
			if (refChar.quest.SeekCap == "womanPirates")
			{
				LAi_SetCheckMinHP(refChar, 5, true, "QuestAboardCabinDialog");  // сколько НР мин
				refChar.Dialog.CurrentNode = "PiratesCap_Board"; //даем абордажную ноду
			}
		}
		//захват пассажиров
		if (refChar.CaptanId == "MarginCap")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\Marginpassenger.c";
			refChar.Dialog.CurrentNode = "MarginCap_abordage"; //даем абордажную ноду		
		}
		//зачарованный город, штурм брига с Данькой
		if (refChar.CaptanId == "Danielle")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		//генератор "Продажный патруль" 
		if (refChar.CaptanId == "PirateCapt")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
		}
		
		// Warship Генер "Пираты на необитайке"
		if(refChar.CaptanId == "PiratesOnUninhabited_BadPirate")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\GenQuests_dialog.c";
			refChar.Dialog.CurrentNode = "PiratesOnUninhabited_46"; //даем абордажную ноду
		}
		
		// Генерратор "Поручение капитана 'Выкуп' или 'Операция Галеон'"
		if(CheckAttribute(pchar,"GenQuest.CaptainComission") && pchar.GenQuest.CaptainComission == "Begin")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\GenQuests_dialog.c";
			refChar.Dialog.CurrentNode = "CaptainComission_1"; //даем абордажную ноду
		}
		
		if(refChar.CaptanId == "ShipWreck_BadPirate")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\GenQuests_dialog.c";
			refChar.Dialog.CurrentNode = "ShipWreck_50"; //даем абордажную ноду		
		}
		
		if (refChar.CaptanId == "GhostCapt" && CheckAttribute(pchar,"GenQuest.GhostShip.Prize"))
		{
		    LAi_SetCheckMinHP(refChar, 50, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.CurrentNode = "GhostCapt_LastDialog";
		}
		if (refChar.CaptanId == "Slaveshorecap")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\Other_Quests_NPC.c";
			refChar.Dialog.CurrentNode = "TakeShoreCap"; //даем абордажную ноду		
		}
		if (refChar.CaptanId == "RatCaptain")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\Other_Quests_NPC.c";
			refChar.Dialog.CurrentNode = "Rat_talk"; //даем абордажную ноду		
		}
		if (refChar.CaptanId == "Jafar")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\Other_Quests_NPC.c";
			refChar.Dialog.CurrentNode = "Ja_talk"; //даем абордажную ноду		
		}
		if (refChar.CaptanId == "FL_blackTwister_captain")
		{
		    LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.FileName = "Quest\FranceLine\BlackTwister_capitan.c";
			refChar.Dialog.CurrentNode = "BlackTwister_capitan"; //даем абордажную ноду		
		}
		// квест Шарпа, дуэль - битва с кэпом после убийства информатора
		if(refChar.CaptanId == "Sharp" && CheckAttribute(pchar,"questTemp.Sharp") && pchar.questTemp.Sharp == "sharpRevengeToFight")
		{
			LAi_SetCheckMinHP(refChar, 10, true, "QuestAboardCabinDialog");  // сколько НР мин
			refChar.Dialog.CurrentNode = "Sharp_Encounter_AboardCabin"; //даем абордажную ноду
		}
	}
}

// ugeen --> ситуации на абордаже в каюте вражеского кэпа (эпидемия или взрыв)
void SetQuestAboardCabinDialogSituation(ref refChar)
{
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	refChar.Dialog.FileName = "Quest\GenQuests_dialog.c";	
	switch(refChar.situation.type)
	{
		case "pirate": 	// пираты или ДУ	
			refChar.Dialog.CurrentNode = "ShipSituation11";
		break;
		case "hunter": 	// ОЗГ
			refChar.Dialog.CurrentNode = "ShipSituation31";
		break;
		case "war": 	// военные корабли
			refChar.Dialog.CurrentNode = "ShipSituation21";
		break;
		case "trade": 	// торговцы
			refChar.Dialog.CurrentNode = "ShipEpidemy1";
		break;		
	}
	LAi_SetActorType(refChar);
	LAi_ActorDialog(refChar, pchar, "", -1, 0);
}
// <-- ugeen

void SetQuestAboardCabin_CheckCaptain(ref refChar) {
	// Зачарованный город, Данька
	if (refChar.CaptanId == "Danielle")
	{
		if (!CheckCharacterItem(pchar, "SkullAztec"))
		{
			refChar.undead = "1";
			LAi_RemoveCheckMinHP(refChar);
			refChar.model = "Danielle_Sheppard_D";
			FaceMaker(refChar);
			SetNewModelToChar(refChar);
		}
	}
}

void QuestAboardCabinDialogFree()
{
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
    LAi_SetWarriorType(sld);
    LAi_group_MoveCharacter(sld, LAI_GROUP_BRDENEMY);
}
//выход без боевки, но в плен не надо
void QuestAboardCabinDialogNotBattle()
{
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
    LAi_SetWarriorType(sld);
	DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
}
// выход с боевкой
void QuestAboardCabinDialogExitWithBattle(string _questName)
{
    QuestAboardCabinDialogFree(); // важный метод
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	LAi_SetFightMode(pchar, true);
	LAi_SetFightMode(sld, true);
	LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck(LAI_GROUP_BRDENEMY, _questName);
	// SetCharacterTask_Fight(sld, pchar);
}

void QuestAboardCabinDialogExitWithBattleNoParam()// homo тоже самое, только без параметров
{
    QuestAboardCabinDialogExitWithBattle("");
}

void QuestAboardCabinDialogSurrender()
{
 	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	DeleteAttribute(sld, "DontRansackCaptain"); // если было зачем-то
	pchar.GenQuest.QuestAboardCaptanSurrender = true;
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
	//на форме убиваем LAi_SetCurHP(characterFromId(sld.CaptanId), 0.0);
	//sld.LifeDay = 0;    это не фантом многодневка, а фантом локации, трется он сам при закрузке локации, но не при выгрузке
	DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
}
//==> квестовое пленение с сохранением индекса пленного.
void QuestAboardCabinDialogQuestSurrender()
{
	ref sld;
	sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
	sld.DontRansackCaptain = true; // чтоб не сдался второй раз
	Lai_SetPlayerType(pchar);
	LAi_RemoveCheckMinHP(sld);
	LAi_SetImmortal(sld, false);
	//на форме убиваем LAi_SetCurHP(characterFromId(sld.CaptanId), 0.0);
	//sld.LifeDay = 0;
	pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
	SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
	DoQuestCheckDelay("LAi_ReloadBoarding", 1.0);
}

// eddy. лицензии торговых компаний. -->
//дать лицензию
void GiveNationLicence(int _nation, int _validity)
{
	string sTemp;
	ref rItem;
	for(int i=0; i<4; i++)
	{
		if (CheckNationLicence(i) && GetDaysContinueNationLicence(i) == -1) TakeNationLicence(i);
	}
	if (_nation != PIRATE) 
	{
		if (CheckNationLicence(_nation)) TakeNationLicence(_nation);
		sTemp = NationShortName(_nation)+"TradeLicence";
		GiveItem2Character(pchar, sTemp);
		rItem = ItemsFromID(sTemp);
		SaveCurrentNpcQuestDateParam(rItem, "Action_date");
		rItem.Action_date = GetCurrentDate();
		rItem.Validity = FindDaysString(_validity); //строка для дескрайба
		rItem.Validity.QtyDays = _validity; //время действия лицензии в днях для расчётов
	}
}
//забрать лицензию 
void TakeNationLicence(int _nation)
{
	string sTemp;
	if (_nation != PIRATE && CheckNationLicence(_nation)) 
	{
		sTemp = NationShortName(_nation)+"TradeLicence";
		TakeItemFromCharacter(pchar, sTemp);
		DeleteAttribute(ItemsFromID(sTemp), "Action_date");
		DeleteAttribute(ItemsFromID(sTemp), "Validity");
	}
}
//проверить наличие лицензии
bool CheckNationLicence(int _nation)
{
	if (_nation != PIRATE) 
	{
		if (CheckCharacterItem(pchar, NationShortName(_nation)+"TradeLicence")) return true;
	}
	return false;
}
//проверить сроки лицензии, сколько осталось дней. если -1, то просрочена или отсутствует
int GetDaysContinueNationLicence(int _nation)
{
	int iTerms = -1;
	ref rItem;
	if (_nation != PIRATE) 
	{
		if (CheckNationLicence(_nation))
		{
			rItem = ItemsFromID(NationShortName(_nation)+"TradeLicence");
			
			if(!CheckAttribute(rItem, "Validity")) // Warship 10.07.09 fix - Судя по логам, могло не быть
			{
				return -1;
			}
			
			int Validity = sti(rItem.Validity.QtyDays);
			iTerms = GetNpcQuestPastDayParam(rItem, "Action_date");
			if (iTerms > Validity) iTerms = -1;
			else iTerms = Validity - iTerms;
		}
	}
	return iTerms;
}
//дать наименование лицензии, например 'Лицензия Голландской Вест-Индской компании'
string GetRusNameNationLicence(int _nation)
{
	string sTemp, itmTitle;
	if (_nation != PIRATE) 
	{
		if (CheckNationLicence(_nation))
		{
			sTemp = NationShortName(_nation)+"TradeLicence";
			itmTitle = GetConvertStr(Items[FindItem(sTemp)].name, "ItemsDescribe.txt");
		}
	}
	return itmTitle;
}
// eddy. лицензии торговых компаний. <--

//--> eddy. квест Изабеллы, методы для контроля семейной жизни
//запишем текущие показтели статистики. записать так же не все, а один из показателей.
// если _TypeOfCheck == "all", то обнулить все. _TypeOfCheck может быть "KillFort", "TakeTown", 
void IsabellaSetCurrentState(string _TypeOfCheck)
{
	if (_TypeOfCheck == "all" || _TypeOfCheck == "KillFort")
	{
		DeleteAttribute(pchar, "RomanticQuest.Cheking.KillFort");
		pchar.RomanticQuest.State.KillFort = Statistic_AddValue(PChar, "pir_KillFort", 0) +
											Statistic_AddValue(PChar, "eng_KillFort", 0) +
											Statistic_AddValue(PChar, "fra_KillFort", 0) +
											Statistic_AddValue(PChar, "spa_KillFort", 0) +
											Statistic_AddValue(PChar, "hol_KillFort", 0);
	}
	if (_TypeOfCheck == "all" || _TypeOfCheck == "TakeTown")
	{
		DeleteAttribute(pchar, "RomanticQuest.Cheking.TakeTown");
		pchar.RomanticQuest.State.TakeTown = Statistic_AddValue(PChar, "pir_TakeTown", 0) +
											Statistic_AddValue(PChar, "eng_TakeTown", 0) +
											Statistic_AddValue(PChar, "fra_TakeTown", 0) +
											Statistic_AddValue(PChar, "spa_TakeTown", 0) +
											Statistic_AddValue(PChar, "hol_TakeTown", 0);
	}
	if (_TypeOfCheck == "all" || _TypeOfCheck == "GrabbingTown")
	{
		DeleteAttribute(pchar, "RomanticQuest.Cheking.GrabbingTown");
		pchar.RomanticQuest.State.GrabbingTown = Statistic_AddValue(PChar, "pir_GrabbingTown", 0) +
												Statistic_AddValue(PChar, "eng_GrabbingTown", 0) +
												Statistic_AddValue(PChar, "fra_GrabbingTown", 0) +
												Statistic_AddValue(PChar, "spa_GrabbingTown", 0) +
  												Statistic_AddValue(PChar, "hol_GrabbingTown", 0);
	}
	if (_TypeOfCheck == "all" || _TypeOfCheck == "AbordShip")
	{
		DeleteAttribute(pchar, "RomanticQuest.Cheking.AbordShip");
		pchar.RomanticQuest.State.AbordShip = Statistic_AddValue(PChar, "pir_AbordShip", 0) +
											Statistic_AddValue(PChar, "eng_AbordShip", 0) +
											Statistic_AddValue(PChar, "fra_AbordShip", 0) +
											Statistic_AddValue(PChar, "spa_AbordShip", 0) +
											Statistic_AddValue(PChar, "hol_AbordShip", 0);
	}
	if (_TypeOfCheck == "all" || _TypeOfCheck == "KillShip")
	{
		DeleteAttribute(pchar, "RomanticQuest.Cheking.KillShip");	
		pchar.RomanticQuest.State.KillShip = Statistic_AddValue(PChar, "pir_KillShip", 0) +
											Statistic_AddValue(PChar, "eng_KillShip", 0) +
											Statistic_AddValue(PChar, "fra_KillShip", 0) +
											Statistic_AddValue(PChar, "spa_KillShip", 0) +
											Statistic_AddValue(PChar, "hol_KillShip", 0);
	}
}
//проверим текущее состояние в рамках контроля за статистикой
void IsabellaCheckBreachState()
{
	int iTemp;
	iTemp = Statistic_AddValue(PChar, "pir_KillFort", 0) +
			Statistic_AddValue(PChar, "eng_KillFort", 0) +
			Statistic_AddValue(PChar, "fra_KillFort", 0) +
			Statistic_AddValue(PChar, "spa_KillFort", 0) +
			Statistic_AddValue(PChar, "hol_KillFort", 0);
	if (iTemp > sti(pchar.RomanticQuest.State.KillFort)) pchar.RomanticQuest.Cheking.KillFort = iTemp - sti(pchar.RomanticQuest.State.KillFort);
	iTemp = Statistic_AddValue(PChar, "pir_TakeTown", 0) +
			Statistic_AddValue(PChar, "eng_TakeTown", 0) +
			Statistic_AddValue(PChar, "fra_TakeTown", 0) +
			Statistic_AddValue(PChar, "spa_TakeTown", 0) +
			Statistic_AddValue(PChar, "hol_TakeTown", 0);
	if (iTemp > sti(pchar.RomanticQuest.State.TakeTown)) pchar.RomanticQuest.Cheking.TakeTown = iTemp - sti(pchar.RomanticQuest.State.TakeTown);
	iTemp = Statistic_AddValue(PChar, "pir_GrabbingTown", 0) +
			Statistic_AddValue(PChar, "eng_GrabbingTown", 0) +
			Statistic_AddValue(PChar, "fra_GrabbingTown", 0) +
			Statistic_AddValue(PChar, "spa_GrabbingTown", 0) +
  			Statistic_AddValue(PChar, "hol_GrabbingTown", 0);
	if (iTemp > sti(pchar.RomanticQuest.State.GrabbingTown)) pchar.RomanticQuest.Cheking.GrabbingTown = iTemp - sti(pchar.RomanticQuest.State.GrabbingTown);
	iTemp = Statistic_AddValue(PChar, "pir_AbordShip", 0) +
			Statistic_AddValue(PChar, "eng_AbordShip", 0) +
			Statistic_AddValue(PChar, "fra_AbordShip", 0) +
			Statistic_AddValue(PChar, "spa_AbordShip", 0) +
			Statistic_AddValue(PChar, "hol_AbordShip", 0);
	if (iTemp > sti(pchar.RomanticQuest.State.AbordShip)) pchar.RomanticQuest.Cheking.AbordShip = iTemp - sti(pchar.RomanticQuest.State.AbordShip);
	iTemp = Statistic_AddValue(PChar, "pir_KillShip", 0) +
			Statistic_AddValue(PChar, "eng_KillShip", 0) +
			Statistic_AddValue(PChar, "fra_KillShip", 0) +
			Statistic_AddValue(PChar, "spa_KillShip", 0) +
			Statistic_AddValue(PChar, "hol_KillShip", 0);
	if (iTemp > sti(pchar.RomanticQuest.State.KillShip)) pchar.RomanticQuest.Cheking.KillShip = iTemp - sti(pchar.RomanticQuest.State.KillShip);		
	return;
}
//сбросить счетчик по семейному бюджету
void IsabellaNullBudget()
{
	pchar.RomanticQuest.Budget = "0";
	SaveCurrentQuestDateParam("RomanticQuest.Budget");
}
//возвращает текущую задолженность в деньгах. положительное значение - задолж., отрицательное - профицит.
int IsabellaCheckBudgetMoney()
{
	int Debt = GetQuestPastMonthParam("RomanticQuest.Budget")*MOD_SKILL_ENEMY_RATE*10000;
	int CurMoney = sti(pchar.RomanticQuest.Budget);
	return Debt - CurMoney;
}
//добавить денег на текущий баланс бюджета
void IsabellaAddMoneyBudget(int _money)
{
	pchar.RomanticQuest.Budget = sti(pchar.RomanticQuest.Budget) + _money;
	AddMoneyToCharacter(pchar, -_money);
}
// <-- eddy. квест Изабеллы, методы для контроля семейной жизни

void SelectAscoldRendom()
{
	if (CheckAttribute(&colonies[1], "nation"))
	{
		int n, nation;
		int storeArray[MAX_COLONIES];
		int howStore = 0;
		for(n=0; n<MAX_COLONIES; n++)
		{			
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && colonies[n].id != "FortOrange")
			{           
				storeArray[howStore] = n;
				howStore++;
			}
		}
		nation = storeArray[rand(howStore-1)];
		pchar.questTemp.Ascold.TraderId = colonies[nation].id + "_trader";
		nation = storeArray[rand(howStore-1)];
		pchar.questTemp.Ascold.MerchantColony = colonies[nation].id;
		pchar.questTemp.Ascold.dialogNation = sti(colonies[nation].nation);
		nation = storeArray[rand(howStore-1)];
		while (colonies[nation].id == "Panama")
		{
			nation = storeArray[rand(howStore-1)];
		}
		
		pchar.questTemp.Ascold.ShipyarderId = colonies[nation].id + "_shipyarder";
		pchar.questTemp.Ascold.ShipyarderColony = colonies[nation].id;
		items[FindItem("Azzy_bottle")].useLocation = colonies[nation].id + "_Shipyard";

        // квест-метки
        AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Ascold.TraderId), "Ascold");
	    AddMapQuestMark_Major(Characters[GetCharacterIndex(pchar.questTemp.Ascold.TraderId)].city+"_town", "Ascold", "Ascold_Begin_WDMQuestMarkCondition");
        Ascold_FreeAzzy_AddQuestMarks();
	}
}
void SelectSlavetraderRendom() // работорговец, выбор города
{
	if (CheckAttribute(&colonies[1], "nation"))
	{
		int n, nation;
		int storeArray[MAX_COLONIES];
		int howStore = 0;
		for(n=0; n<MAX_COLONIES; n++)
		{			
			if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && colonies[n].id != "FortOrange" && colonies[n].id != "Havana" && colonies[n].id != "Santiago" && colonies[n].id != "Portroyal" && colonies[n].id != "Villemstad" && colonies[n].id != "Tortuga" && colonies[n].id != "Panama")
			{           
				storeArray[howStore] = n;
				howStore++;
			}
		}
		nation = storeArray[rand(howStore-1)];
		pchar.questTemp.Slavetrader.UsurerId = colonies[nation].id + "_usurer";

		// квест-метки
        AddLandQuestmark_Main(CharacterFromID(pchar.questTemp.Slavetrader.UsurerId), "Slavetrader");
	    AddMapQuestMark_Major(colonies[nation].id + "_town", "Slavetrader", "Slavetrader_Begin_WDMQuestMarkCondition");
	}
}

// квест Изабеллы
void IsabellaInit()
{
	ref ch;
	// ==> состояние квеста Изабеллы, если равен "" - то квест Атилла не даст.
	pchar.RomanticQuest = "canTakeQuest";
	//Атилла
	ch = GetCharacter(NPC_GenerateCharacter("Atilla", "Atilla", "man", "man", 22, PIRATE, -1, false));
	ch.name 	= FindPersonalName("Atilla_name");
	ch.lastname 	= "";
	GiveItem2Character(ch, GUN_COMMON);
	ch.equip.gun = GUN_COMMON;
	GiveItem2Character(ch, BLADE_LONG);
	ch.equip.blade = BLADE_LONG;
	ch.location	= "Pirates_town";
	ch.location.group = "goto";
	ch.location.locator = "goto1";
	ch.Dialog.Filename = "Quest\Isabella\Atilla.c";
	ch.greeting = "Gr_Smuggler Agent";
	ch.rank 	= 25;
	ch.reputation = "30";
	ch.talker = 5; //начать диалог
	ch.TiedItems.itm1.model = "HandsItems\meet";
	ch.TiedItems.itm1.locator = "Saber_hand";	
	ch.TiedItems.itm2.model = "HandsItems\cup";
	ch.TiedItems.itm2.locator = "Saber_hand";
    SetRandSPECIAL(ch);
    SetSelfSkill(ch, 80, 70, 90, 60, 50);
    SetShipSkill(ch, 50, 10, 60, 60, 40, 70, 70, 40, 50);
	ch.money = "200";
	LAi_SetCitizenType(ch);
	LAi_group_MoveCharacter(ch, "PIRATE_CITIZENS");
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 200.0, 200.0);
	LAi_NoRebirthEnable(ch);
	ch.DontClearDead = true;  // не убирать труп
	ch.greeting = "Gr_Atilla";
	// проверка на pchar.sex != "woman" здесь не работает, добавляем для всех
	AddLandQuestMark_Main_WithCondition(ch, "Romantic_Line", "RomanticLine_Begin_QuestMarkCondition");
	AddMapQuestMark_Major("Pirates_town", "Romantic_Line", "RomanticLine_Begin_WDMQuestMarkCondition");
	// Злой муж
	ch = GetCharacter(NPC_GenerateCharacter("Husband", "portman_6", "man", "man", 22, PIRATE, -1, false));	
	ch.name 	= FindPersonalName("Husband_name");
	ch.lastname = FindPersonalName("Husband_lastname");
	ch.location	= "SanJuan_houseSp6";
	ch.location.group = "goto";
	ch.location.locator = "goto2";
	ch.Dialog.Filename = "Quest\Isabella\Husband.c";
	GiveItem2Character(ch, "pistol5");
	ch.equip.gun = "pistol5";
	TakeNItems(ch,"bullet", Rand(20)+20);
	AddItems(ch, "GunPowder", rand(20)+20);
	GiveItem2Character(ch, "blade34");
	ch.equip.blade = "blade34";
	ch.rank 	= 40;
	ch.reputation = "35";
    SetRandSPECIAL(ch);
    SetSelfSkill(ch, 90, 90, 90, 70, 90);
    SetShipSkill(ch, 20, 90, 10, 10, 10, 20, 10, 10, 50);
	ch.money = "1000";
	ch.SaveItemsForDead = true; // сохранять на трупе вещи
	ch.DontClearDead = true; // не убирать труп через 200с
	LAi_SetLoginTime(ch, 0.0, 24.0);
	LAi_SetHP(ch, 220.0, 220.0);
	LAi_SetHuberStayType(ch);
	LAi_SetStayHuberPointWindow(ch, "goto", "goto1");
	LAi_SetStayHuberPointMap(ch, "goto", "goto2");
	LAi_group_MoveCharacter(ch, "SPAIN_CITIZENS");
	LAi_SetImmortal(ch, true);
	LAi_LoginInCaptureTown(ch, true);
	ch.greeting = "Gr_OliverTrast";
}
//установить говорилку на горожанина. нужно по Изабелле.
void SetIsabellaTalker(string qName)
{
	ref chr = characterFromID("Isabella");
	chr.talker = 10;
	AddLandQuestmark_Main(chr, "Romantic_Line");
}
//Проклятие Дальних Морей
void PDMQuestsInit()
{
	if (!GetDLCenabled(PDM_QUESTS)) return;
	if (CheckAttribute(&TEV, "PDMQuestsInit") && TEV.PDMQuestsInit == "complete") return;

	ref sld;
	int i;

	//******Проклятый идол Sinistra******
	//Джеймс Кэллоу
	pchar.quest.PDM_CI_SpawnJC.win_condition.l1 = "Rank";
	pchar.quest.PDM_CI_SpawnJC.win_condition.l1.value = 1;
	pchar.quest.PDM_CI_SpawnJC.win_condition.l1.operation = ">=";
	PChar.quest.PDM_CI_SpawnJC.win_condition = "PDM_CI_SpawnJC";

	//******Невыносимая жара Sinistra******
	//Стражники
	for (i = 0; i < TOTAL_CHARACTERS; i++) //уберём уже существующих, если загрузились с сохранения
	{
		sld = &Characters[i];
		if (!CheckAttribute(sld, "location")) continue;
		if (sld.location != "FortFrance_town") continue;
		if (!CheckAttribute(sld, "location.locator")) continue;
		if (sld.location.locator == "special1" || sld.location.locator == "special2")
		{
		    if (HasSubStr(sld.id, "GenChar"))
			{
				ChangeCharacterAddressGroup(sld, "none", "none", "none");
				LAi_KillCharacter(sld);
				sld.lifeday = 0;
			}
		}
	}
	sld = GetCharacter(NPC_GenerateCharacter("PDM_PJ_Strajnik_1", "elite_fra_6", "man", "man", 10, FRANCE, -1, false));
	sld.name	= FindPersonalName("PDM_PJ_Strajnik_1_name");
	sld.lastname	= "";
	//sld.greeting = "soldier_common"; TODO вместе с согласование воспроизведения звуков
	sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	sld.talker = 7;
	LAi_SetStayType(sld);
	FantomMakeCoolFighter(sld, 15, 50, 50, "blade_maltes", "", 40);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	sld.City = "FortFrance";
	pchar.quest.PDM_Jori.win_condition.l1 = "NPC_Death"; //индикатор для генерации
	pchar.quest.PDM_Jori.win_condition.l1.character = "PDM_PJ_Strajnik_1";
	ChangeCharacterAddressGroup(sld,"FortFrance_town","soldiers","special2");
	AddLandQuestMark_Main(sld, "PDM_Proklyataya_Jara");
	AddMapQuestMark_Major("FortFrance_town", "PDM_Proklyataya_Jara", "");

	sld = GetCharacter(NPC_GenerateCharacter("PDM_PJ_Strajnik_2", "elite_fra_1", "man", "man", 10, FRANCE, -1, false));
	sld.name	= FindPersonalName("PDM_PJ_Strajnik_2_name");
	sld.lastname	= "";
	//sld.greeting = "soldier_common"; TODO вместе с согласование воспроизведения звуков
	sld.dialog.filename   = "Common_Soldier.c";
	LAi_SetLoginTime(sld, 6.0, 21.99);
	LAi_SetGuardianType(sld);
	FantomMakeCoolFighter(sld, 15, 50, 50, "blade_maltes", "", 40);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	sld.City = "FortFrance";
	pchar.quest.PDM_Aler.win_condition.l1 = "NPC_Death"; //индикатор для генерации
	pchar.quest.PDM_Aler.win_condition.l1.character = "PDM_PJ_Strajnik_2";
	ChangeCharacterAddressGroup(sld,"FortFrance_town","soldiers","special1");

	//******Потерянное кольцо Sinistra******
	//Жозефина Лодет
	sld = GetCharacter(NPC_GenerateCharacter("Josephine_Lodet", "JosefinLodet", "woman", "towngirl2", 10, FRANCE, -1, false));
	sld.name	= FindPersonalName("Josephine_Lodet2_name");
	sld.lastname	= "";
	sld.Dialog.Filename = "Quest\PDM\Poteryanoe_Koltso.c";
	LAi_SetCitizenType(sld);
	LAi_SetLoginTime(sld, 6.0, 21.99);
	sld.talker = 4;
	LAi_SetImmortal(sld, true);
	LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
	sld.City = "PortPax";
	ChangeCharacterAddressGroup(sld,"PortPax_town","goto","goto14");
	AddLandQuestMark_Main(sld, "PDM_Poteryanoe_Koltso");
    AddMapQuestMark_Major("PortPax_town", "PDM_Poteryanoe_Koltso", "");

	//******Непутёвый казначей Sinistra******
	//Андреас Фиклер
	pchar.quest.PDM_NK_Nachalo.win_condition.l1 = "Rank";
	pchar.quest.PDM_NK_Nachalo.win_condition.l1.value = 1;
	pchar.quest.PDM_NK_Nachalo.win_condition.l1.operation = ">=";
	PChar.quest.PDM_NK_Nachalo.win_condition = "PDM_NK_Nachalo";

	//******Клан Ламбрини******
	//Октавио Ламбрини
	sld = GetCharacter(NPC_GenerateCharacter("PDM_Octavio_Lambrini", "Octavio_Lambrini", "man", "man", 10, PIRATE, -1, true));
	sld.name	= FindPersonalName("PDM_Octavio_Lambrini_name");
	sld.lastname	= FindPersonalName("PDM_Octavio_Lambrini_lastname");
	sld.Dialog.Filename = "Quest\PDM\Clan_Lambrini.c";
	LAi_SetSitType(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	ChangeCharacterAddressGroup(sld,"PortSpein_tavern","sit","sit_front2");
	AddLandQuestMark_Main(sld, "PDM_Clan_Lambrini");
    AddMapQuestMark_Major("PortSpein_town", "PDM_Clan_Lambrini", "");

	//******Прокажённая******
	//Бартоломью Ольстер
	pchar.quest.PDM_ONV_Nachalo.win_condition.l1 = "Rank";
	pchar.quest.PDM_ONV_Nachalo.win_condition.l1.value = 1;
	pchar.quest.PDM_ONV_Nachalo.win_condition.l1.operation = ">=";
	PChar.quest.PDM_ONV_Nachalo.function = "PDM_ONV_Nachalo";

	//******"Остепенившийся пират******
	//Хьюго Лесопилка
	sld = GetCharacter(NPC_GenerateCharacter("Hugo_Lesopilka", "officer_18", "man", "man", 10, PIRATE, -1, true));
	sld.name	= FindPersonalName("Hugo_Lesopilka_name");
	sld.lastname	= FindPersonalName("Hugo_Lesopilka_lastname");
	sld.Dialog.Filename = "Quest\PDM\Lesopilka.c";
	LAi_SetSitType(sld);
	LAi_SetImmortal(sld, true);
	ChangeCharacterAddressGroup(sld,"Providencia_tavern","sit","sit5");
	AddLandQuestMark_Main(sld, "PDM_Lesopilka");
    AddMapQuestMark_Major("Providencia_town", "PDM_Lesopilka", "");

    TEV.PDMQuestsInit = "complete";
}

// Сопровождение флейта "Орион" - Инициализация
void Andre_Abel_Quest_Init()
{
	pchar.quest.Andre_Abel_Quest_Start.win_condition.l1 = "location";
	pchar.quest.Andre_Abel_Quest_Start.win_condition.l1.location = "FortFrance_tavern";
	pchar.quest.Andre_Abel_Quest_Start.function = "Andre_Abel_Quest_CreateAbel";
}

void OfficerGirlInit()
{
    ref sld;
    
    sld = GetCharacter(NPC_GenerateCharacter("YokoDias", "YokoDias", "woman", "Beatrice", 15, PIRATE, -1, false));
	sld.HeroModel = "YokoDias,YokoDias_1,YokoDias_2,YokoDias_3,YokoDias_4,YokoDias_5";  // Прописка всех моделей для кирас. <-- Konstrush
	sld.name 	= FindPersonalName("YokoDias_name");
	sld.lastname = FindPersonalName("YokoDias_lastname");
	sld.rank 	= 15;
    sld.reputation = 70; // good девочка
	sld.alignment = "good";
	GiveItem2Character(sld, "blade15");
	TakeNItems(sld,"potion2", Rand(4)+1);
	sld.equip.blade = "blade15";
	GiveItem2Character(sld, "pistol2");
	sld.equip.gun = "pistol2";
    TakeNItems(sld,"bullet", Rand(20)+20);
	AddItems(sld, "GunPowder", rand(20)+20);
    sld.Payment = true;
	LAi_SetRolyPoly(sld, true); //неваляха
    
	sld.location	= "Pirates_town";
	sld.location.group = "goto";
	sld.location.locator = "goto20";
	sld.dialog.filename   = "Officer_Girl.c";
	sld.greeting = "Gr_Danielle";
	sld.money = 0;
 	SetSPECIAL(sld, 8,5,8,7,10,9,5);
	//f_l, f, f_h, p, f
	SetSelfSkill(sld, 32,22,49,45,34);
	// l, c, a, cn, sl, re, gr, de, sn
	SetShipSkill(sld, 22,13,23,24,24,33,54,52,40);
	LAi_NPC_EquipPerk(sld, "fantom");
	sld.perks.list.BasicDefense = true;
    sld.perks.list.AdvancedDefense = true;
    sld.perks.list.SwordplayProfessional = true;
    sld.perks.list.CriticalHit = true;
    sld.perks.list.Gunman = true;
    sld.perks.list.GunProfessional = true;
    sld.perks.list.ByWorker = true;
	sld.perks.list.ShipEscape = true;
	sld.perks.list.Ciras = true;
	
	//черты
	sld.perks.list.Energaiser = true;
	sld.perks.list.LoyalOff = true;
	sld.perks.list.SweetBaby = true;
	sld.perks.list.Honest = true;
	
    LAi_NoRebirthEnable(sld);
    LAi_SetWarriorType(sld);
	sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
	sld.loyality = MAX_LOYALITY;
    LAi_warrior_DialogEnable(sld, true);
    LAi_SetLoginTime(sld, 0.0, 24.0);
    LAi_SetHP(sld, 255, 255);
	SetCharacterPerk(sld, "HPPlus"); // обязательно через функцию и после присвоения HP
	SetCharacterPerk(sld, "EnergyPlus");
	//SetFantomHP(sld);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	
	sld = GetCharacter(NPC_GenerateCharacter("Angellica", "Angellica", "woman", "Beatrice", 15, PIRATE, -1, false));
	sld.HeroModel = "Angellica,Angellica_1,Angellica_2,Angellica_3,Angellica_4,Angellica_5";  // Прописка всех моделей для кирас. <-- Konstrush
	sld.name 	= FindPersonalName("Angellica_name");
	sld.lastname = FindPersonalName("Angellica_lastname");
	sld.rank 	= 17;
    sld.reputation = 10; // bad девочка
	sld.alignment = "bad";
	GiveItem2Character(sld, "blade12");
	TakeNItems(sld,"potion2", Rand(4)+1);
	sld.equip.blade = "blade12";
	GiveItem2Character(sld, "pistol2");
	sld.equip.gun = "pistol2";
    TakeNItems(sld,"bullet", Rand(20)+20);
	AddItems(sld, "GunPowder", rand(20)+20);
    sld.Payment = true;
	LAi_SetRolyPoly(sld, true); //неваляха

	sld.location	= "PuertoPrincipe_town";
	sld.location.group = "goto";
	sld.location.locator = "goto6";
	sld.dialog.filename   = "Officer_Girl.c";
	sld.greeting = "Gr_Danielle";
	sld.money = 0;
  	SetSPECIAL(sld, 8,6,9,6,8,9,6); //сила,восп,вын,обаяние,инт,ловкость,удача
	//f_l, f, f_h, p, f
	SetSelfSkill(sld, 23,68,38,35,33);
	// l, c, a, cn, sl, re, gr, de, sn
	SetShipSkill(sld, 56,15,35,46,40,22,33,21,34);
	LAi_NPC_EquipPerk(sld, "fantom");
	sld.perks.list.BasicDefense = true;
    sld.perks.list.AdvancedDefense = true;
    sld.perks.list.SwordplayProfessional = true;
    sld.perks.list.CriticalHit = true;
    sld.perks.list.Gunman = true;
    sld.perks.list.GunProfessional = true;
    sld.perks.list.ByWorker = true;
	sld.perks.list.ShipEscape = true;
	sld.perks.list.Ciras = true;
	
	//черты
	sld.perks.list.Energaiser = true;
	sld.perks.list.LoyalOff = true;
	sld.perks.list.SweetBaby = true;
	sld.perks.list.Rebel = true;
	
    LAi_NoRebirthEnable(sld);
    LAi_SetWarriorType(sld);
	sld.OfficerWantToGo.DontGo = true; //не пытаться уйти
	sld.loyality = MAX_LOYALITY;
    LAi_warrior_DialogEnable(sld, true);
    LAi_SetLoginTime(sld, 0.0, 24.0);
	LAi_SetHP(sld, 258, 258);
    //SetFantomHP(sld);
    LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
}

void OfficerMushketerInit()
{
    ref sld;
    // мушкетёр №1 - пират
    sld = GetCharacter(NPC_GenerateCharacter("Rimalier", "Rimalier", "man", "man", 15, PIRATE, -1, true));
	sld.name = FindPersonalName("OfMush1_name");
	sld.lastname = FindPersonalName("OfMush1_lastname");
	sld.greeting = "Gr_Officer";
	sld.loyality = 18;
	sld.rank = 15;
	sld.reputation = 20;
	sld.HeroModel = "Rimalier,Rimalier_1,Rimalier_2,Rimalier_3,Rimalier_4,Rimalier_5";
	sld.alignment = "bad";
	LAi_SetHP(sld, 180, 180);
	sld.Dialog.Filename = "Officer_Mush.c";
	sld.dialog.currentnode = "Lostpirate";
	TakeNItems(sld,"potion2", Rand(2)+2);
    sld.Payment = true;
	sld.location	= "Shore59";
	sld.location.group = "goto";
	sld.location.locator = "goto3";
	sld.money = 0;
 	SetSPECIAL(sld, 6, 9, 8, 3, 6, 9, 9);
	SetSelfSkill(sld, 61, 3, 3, 100, 80);
	SetShipSkill(sld, 40, 7, 25, 15, 8, 10, 5, 10, 25);
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunAdvanced");
	SetCharacterPerk(sld, "MusketsTraining");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "HPPlus");
	SetCharacterPerk(sld, "Ciras");
    // мушкетёрское
    MakeOffMush(sld, "mushket", 100, 100);
	// черты
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "Rebel");
	SetCharacterPerk(sld, "MusketeerOnly");
	LAi_NPC_EquipPerk(sld, "fantom");
    LAi_SetWarriorType(sld);
	LAi_warrior_DialogEnable(sld, true);
	LAi_group_MoveCharacter(sld, "PIRATE_CITIZENS");
	locations[FindLocation("Shore59")].DisableEncounters = true; //энкаутеры в локации закроем до поры

	// мушкетёр №2 - саксонец
	sld = GetCharacter(NPC_GenerateCharacter("Magnus", "Magnus", "man", "man", 18, SPAIN, -1, true));
	sld.name = FindPersonalName("OfMush2_name");
	sld.lastname = FindPersonalName("OfMush2_lastname");
	sld.greeting = "Gr_Officer";
	sld.loyality = 13;
	sld.rank = 18;
	sld.reputation = 75;
	sld.HeroModel = "Magnus,Magnus_1,Magnus_2,Magnus_3,Magnus_4,Magnus_5";
	sld.alignment = "good";
	LAi_SetHP(sld, 210, 210);
	sld.Dialog.Filename = "Officer_Mush.c";
	sld.dialog.currentnode = "Saxon";
	TakeNItems(sld,"potion2", Rand(2)+2);
	GiveItem2Character(sld, "cirass2");
	EquipCharacterbyItem(sld, "cirass2");
    sld.Payment = true;
	sld.location	= "Santodomingo_town";
	sld.location.group = "goto";
	sld.location.locator = "goto10";
	sld.money = 0;
 	SetSPECIAL(sld, 7, 9, 7, 4, 3, 10, 8);
	SetSelfSkill(sld, 70, 10, 10, 100, 70);
	SetShipSkill(sld, 30, 9, 8, 8, 15, 20, 18, 5, 30);
	SetCharacterPerk(sld, "AdvancedDefense");
	SetCharacterPerk(sld, "Gunman");
	SetCharacterPerk(sld, "GunAdvanced");
	SetCharacterPerk(sld, "MusketsTraining");
	SetCharacterPerk(sld, "GunProfessional");
	SetCharacterPerk(sld, "IronWill");
	SetCharacterPerk(sld, "Ciras");
    // мушкетёрское
    MakeOffMush(sld, "mushket", 100, 100);
	// черты
	SetCharacterPerk(sld, "Energaiser");
	SetCharacterPerk(sld, "Honest");
	SetCharacterPerk(sld, "MusketeerOnly");
	LAi_NPC_EquipPerk(sld, "fantom");
    LAi_SetWarriorType(sld);
    LAi_warrior_DialogEnable(sld, true);
	LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
}

void VikingDoorInit()
{
	ref sld = GetCharacter(NPC_GenerateCharacter("VikingDoor", "cavernBig1_door", "man", "cavernBig1_door", 5, PIRATE, -1, false));
    sld.name = "";
    sld.lastname = "";
	ChangeCharacterAddressGroup(sld, "Guadeloupe_Cave", "item", "door1");
	LAi_SetImmortal(sld, true);
	LAi_SetActorType(sld);
	MakeUnpushable(sld, true);
}

//===>>> постановка прерываний на жемчужный генератор
void PearlGen_SetSantaCatalina(string sQuest)
{
	pchar.quest.PearlGen_checkSantaCatalina.win_condition.l1 = "location";
	pchar.quest.PearlGen_checkSantaCatalina.win_condition.l1.location = "Pearl_Jungle_06";
	pchar.quest.PearlGen_checkSantaCatalina.win_condition = "PearlGen_checkSantaCatalina";
}
void PearlGen_SetTeno(string sQuest)
{
	pchar.quest.PearlGen_checkTeno.win_condition.l1 = "location";
	pchar.quest.PearlGen_checkTeno.win_condition.l1.location = "Pearl_Jungle_02";
	pchar.quest.PearlGen_checkTeno.win_condition = "PearlGen_checkTeno";
}
//домашние энкаунтеры. установка тамера 'покинуть дом'
void HouseEnc_TimerGoUot(string qName)
{
	if (CheckAttribute(pchar, "questTemp.HouseEncTimer"))
	{
		if (pchar.location == pchar.questTemp.HouseEncTimer && !actLoadFlag && !LAi_grp_alarmactive)
		{
			LAi_group_Attack(characterFromId(pchar.questTemp.HouseEncTimer.Id), Pchar);
		}
		DeleteAttribute(pchar, "questTemp.HouseEncTimer");
	}
}

//удаления группы с задержкой
void Delay_DeleteGroup(string GroupName)
{	
	pchar.quest.DeleteGroupOnExitLocation.GroupName = GroupName;
	DoQuestCheckDelay("DeleteGroupOnExitLocation", 2.0);
}

//Jason --> сделаю функции добавления боевых морских и личных скиллов комплексом - много где надо дать сразу по 4-6, а стопки экспы в функциях мешают
//морские навыки, нужны для экспы после морских боев
void AddComplexSeaExpToScill(int s, int a, int c, int g, int d, int r, int t)
{
	AddCharacterExpToSkill(pchar, "Sailing", s);//навигация
	AddCharacterExpToSkill(pchar, "Accuracy", a);//меткость
	AddCharacterExpToSkill(pchar, "Cannons", c);//орудия
	AddCharacterExpToSkill(pchar, "Grappling", g);//абордаж
	AddCharacterExpToSkill(pchar, "Defence", d);//защита
	AddCharacterExpToSkill(pchar, "Repair", r);//починка
	AddCharacterExpToSkill(pchar, "Commerce", t);//торговля
}

//личные боевые навыки, нужны для экспы после сухопутных боев
void AddComplexSelfExpToScill(int l, int m, int h, int p)
{
	AddCharacterExpToSkill(pchar, "FencingLight", l);//легкое оружие
	AddCharacterExpToSkill(pchar, "Fencing", m);//среднее оружие
	AddCharacterExpToSkill(pchar, "FencingHeavy", h);//тяжелое оружие
	AddCharacterExpToSkill(pchar, "Pistol", p); //пистоли
}

//установка скелетов по пещерам
void SetSkeletonsToLocation(aref _location)
{
	int iRank;
	ref sld;
	bMonstersGen = true; //флаг генерации монстров

	// генерим ранг 
	iRank =	GetCoffDiff(sti(pchar.rank)+3, 1000);

	aref grp;
	makearef(grp, _location.locators.monsters);
	int num = GetAttributesNum(grp);
	int rNum = drand(num);

	for(int i = 0; i < num; i++)
	{
		sld = GetCharacter(NPC_GenerateCharacter("Skelet"+_location.index+"_"+i, "Skel"+(rand(3)+1), "skeleton", "man", iRank, PIRATE, 1, true));
		sld.skeleton = "1";
		//если квест по зачистке от нечисти - скелетов делаем круче
		if (CheckAttribute(_location, "DestroyGhost"))
		{
		    //один кулфайтер, типо босс. остальные послабже, но не лохи
			if (i == 0)
			{
				sld.model = "skeletcap";
				FantomMakeCoolFighter(sld, sti(pchar.rank)+5, 90, 90, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol3"), MOD_SKILL_ENEMY_RATE*4);
				// evganat - энциклопедия
				if(CheckRandomPage("questskeleton", "", -1))
				{
					sld.encyclopedia.tome = GetRandomTome();
					sld.encyclopedia.page = 5;
				}
			}
			else SetFantomParamHunter(sld);
			DeleteAttribute(sld, "SuperShooter");
		}
		else
		{
			if (i == rNum && sti(pchar.rank) > 5)
			{
				FantomMakeCoolFighter(sld, sti(pchar.rank)+5, 80, 80, LinkRandPhrase(RandPhraseSimple("blade23","blade25"), RandPhraseSimple("blade30","blade26"), RandPhraseSimple("blade24","blade13")), RandPhraseSimple("pistol6", "pistol4"), MOD_SKILL_ENEMY_RATE*3);
				DeleteAttribute(sld, "SuperShooter");
			}
			else SetFantomParamFromRank(sld, iRank, true);
		}
		LAi_SetWarriorType(sld);
		LAi_warrior_SetStay(sld, true);
		LAi_group_MoveCharacter(sld, LAI_GROUP_MONSTERS);
		ChangeCharacterAddressGroup(sld, _location.id, "monsters", GetAttributeName(GetAttributeN(grp, i)));
	}
	//проверяем, есть ли на локацию квест по очистке от нечисти
	if (CheckAttribute(_location, "DestroyGhost"))
	{	
		chrDisableReloadToLocation = true;
		characters[sti(_location.DestroyGhost)].quest.DestroyGhost = "GoodResult";
		DeleteAttribute(_location, "DestroyGhost");
		LAi_LocationDisableMonGenTimer(_location.id, 3); //монстров не генерить 3 дня
		LAi_group_SetCheck(LAI_GROUP_MONSTERS, "Church_ClearGhost");
		AddQuestRecordEx(pchar.questTemp.GhostType.title + "Church_DestroyGhost", "Church_DestroyGhost", "2");
	}
	else
	{
		LAi_LocationDisableMonGenTimer(_location.id, 1); //монстров не генерить 1 день
		pchar.GenQuest.monstersTimer = true;
		SetFunctionTimerConditionParam("GenQuest_EnableMonstersGen", 0, 0, 0, 24, false);
	}
}

//Перехват всех попыток ГГ залезть в боксы
void QuestCheckTakeBoxes(ref itemsRef) 
{	
//	ref locLoad = &locations[reload_location_index];
	ref locLoad = &LoadedLocation; // Warship fix - косило в каютах
    ref sld;
	int i, num;
	
	string title;
	
	//--> флаг 'в сундуке'
	bMainCharacterInBox = true;
	//<-- флаг 'в сундуке'
	//-------------------- КЛАДЫ ------------>>>>>>>>>>>>>
	if (CheckAttribute(itemsRef, "Treasure"))
	{
		Log_Info(StringFromKey("QuestsUtilite_23"));
		PlaySound("Notebook");
		DeleteAttribute(itemsRef, "Treasure");
		//eddy. для безконфликтности квестов

		if(!CheckAttribute(itemsRef, "PiratesOnUninhabitedTreasure"))
		{
			if (LAi_LocationIsMonstersGen(locLoad) && !bMonstersGen && LAi_grp_playeralarm == 0 && CheckCharacterPerk(pchar, "WildCaribbean")) // EvgAnat - дикие карибы
			{
				SetSkeletonsToLocation(locLoad);
			}
		}
		else
		{
			title = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			
			if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.UseMainPiratename"))
			{
				AddQuestRecordEx(title, "PiratesOnUninhabited", "10");
				AddQuestUserData(title, "sSex", StringFromKey("му","й"));
			}
			else
			{
				AddQuestRecordEx(title, "PiratesOnUninhabited", "9");
				AddQuestUserData(title, "sSex", GetSexPhrase("ёл","ла"));
				AddQuestUserData(title, "shore", XI_ConvertString(PChar.location + "Gen"));
			}
			
			CloseQuestHeader(title);
			
			PChar.Quest.PiratesOnUninhabited_ShoreTreasureLose.over = "yes";
			
			DeleteAttribute(itemsRef, "PiratesOnUninhabitedTreasure");
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
		}
		
		if(CheckAttribute(itemsRef, "Hold_GenQuest_Treasure"))
		{
			if(sti(pchar.GenQuest.Hold_GenQuest.Treasure) == 0)
			{
				AddQuestRecord("HoldQuest", "18");
				AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.Name);
			}
			else
			{
				AddQuestRecord("HoldQuest", "17");
				AddQuestUserData("HoldQuest", "sCapName", pchar.GenQuest.Hold_GenQuest.CapName);
			}
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(itemsRef, "Hold_GenQuest_Treasure");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");
		}
	}
	//<<<<<<<<<<---------- КЛАДЫ --------------------------
	//-->> Генератор грабежа жемчуга, у главы поселения 
	if (GetCharacterIndex("HeadMan_2") != -1 && locLoad.id == "PearlTown2_Townhall")
	{
		if (pchar.questTemp.Sharp.SeekSpy != "begin" && pchar.questTemp.Sharp.SeekSpy != "over")
		{	//если взят квест на поиски крысы Шарпа - закрываем его
			pchar.questTemp.Sharp.SeekSpy = "over";
			CloseQuestHeader("SharpPearl_SeekSpy");
    		ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
		}
		ChangeCharacterReputation(pchar, -20);
		SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		LAi_group_Attack(characterFromId("HeadMan_2"), Pchar);
		chrDisableReloadToLocation = true;
		pchar.quest.PearlGen_HeadMan_2_death.win_condition.l1 = "NPC_Death";
		pchar.quest.PearlGen_HeadMan_2_death.win_condition.l1.character = "HeadMan_2";
		pchar.quest.PearlGen_HeadMan_2_death.win_condition = "OpenTheDoors";
		return;
	}
	if (GetCharacterIndex("HeadMan_1") != -1 && locLoad.id == "PearlTown1_Townhall")
	{
		if (pchar.questTemp.Sharp.SeekSpy != "begin" && pchar.questTemp.Sharp.SeekSpy != "over")
		{	//если взят квест на поиски крысы Шарпа - закрываем его
			pchar.questTemp.Sharp.SeekSpy = "over";
			CloseQuestHeader("SharpPearl_SeekSpy");
    		ChangeCharacterReputation(pchar, -10);
			ChangeCharacterNationReputation(pchar, SPAIN, -10);
		}		
		ChangeCharacterReputation(pchar, -20);
		SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		LAi_group_Attack(characterFromId("HeadMan_1"), Pchar);
		chrDisableReloadToLocation = true;
		pchar.quest.PearlGen_HeadMan_1_death.win_condition.l1 = "NPC_Death";
		pchar.quest.PearlGen_HeadMan_1_death.win_condition.l1.character = "HeadMan_1";
		pchar.quest.PearlGen_HeadMan_1_death.win_condition = "OpenTheDoors";
		return;
	}
	//<<-- Генератор грабежа жемчуга, у главы поселения 
	//-->> Квест Изабеллы.
	if (GetCharacterIndex("Husband") != -1  && locLoad.id == "SanJuan_houseSp6" && characters[GetCharacterIndex("Isabella")].location != "SanJuan_houseSp6" && characters[GetCharacterIndex("Husband")].location == "SanJuan_houseSp6")
	{		
		ChangeCharacterReputation(pchar, -3);
		SetNationRelation2MainCharacter(SPAIN, RELATION_ENEMY);
		sld = characterFromId("Husband");
		LAi_SetWarriorType(sld);
		//LAi_SetImmortal(sld, false);
		LAi_group_Attack(sld, Pchar);
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(locLoad, false);
		LocatorReloadEnterDisable(locLoad.id, "reload2", true);
		pchar.quest.Husband_death.win_condition.l1 = "NPC_Death";
		pchar.quest.Husband_death.win_condition.l1.character = "Husband";
		pchar.quest.Husband_death.win_condition = "OpenTheDoors";
	}
}
//открытие дверей в локации города для коммонов. только на текущие сутки + ещё одни, потом снимается само.
void SetOpenDoorCommonLoc(string City, string locationId)
{
	aref arRld, arDis, arRld2, arDis2;
	string LocId;
	makearef(arRld, locations[FindLocation(City + "_town")].reload);
    int Qty2, n, i;
	int Qty = GetAttributesNum(arRld);
	for (i=0; i<Qty; i++)
    {
    	arDis = GetAttributeN(arRld, i);
		LocId = arDis.go;
    	if (LocId == locationId)
    	{
			arDis.disable = false;
			arDis.canEnter = true;
			return;
    	}
		if (arDis.label != "Sea" && !CheckAttribute(arDis, "questDisable"))
		{	
			makearef(arRld2, Locations[FindLocation(LocId)].reload);
			Qty2 = GetAttributesNum(arRld2);
			for (n=0; n<Qty2; n++)
			{
    			arDis2 = GetAttributeN(arRld2, n);
				LocId = arDis2.go;
				if (LocId == locationId)
    			{
    			    //открываем сам дом
                    arDis.disable = false;
                    arDis.canEnter = true;
                    //открываем комнату с энкаунтером
					arDis2.disable = false;
					arDis2.canEnter = true;
					return;					
				}
			}
		}
    }
}
// Dolphin ->
void SetLifeDay(ref ch, int i)
{
	ch.LifeDay = i;
}

// Снять предметы
void DelEqiup(ref chr, bool isMoney, bool isSave)
{
	int i=0;
	string str = "itm";
	
	RemoveCharacterEquip(chr, BLADE_ITEM_TYPE);
    while (FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE) != "")
    {
        if(isSave)
		{
			str = "itm"+i;
			chr.tmp_items.(str) = FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE);
			i++;
		}

		TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, BLADE_ITEM_TYPE));
    }
    RemoveCharacterEquip(chr, GUN_ITEM_TYPE);
	while (FindCharacterItemByGroup(chr, GUN_ITEM_TYPE) != "")
    {             
        if(isSave)
		{
			str = "itm"+i;
			chr.tmp_items.(str) = FindCharacterItemByGroup(chr, GUN_ITEM_TYPE);
			i++;
		}

		TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, GUN_ITEM_TYPE));
    }
    RemoveCharacterEquip(chr, MUSKET_ITEM_TYPE);
	while (FindCharacterItemByGroup(chr, MUSKET_ITEM_TYPE) != "")
    {             
        if(isSave)
		{
			str = "itm"+i;
			chr.tmp_items.(str) = FindCharacterItemByGroup(chr, MUSKET_ITEM_TYPE);
			i++;
		}

		TakeItemFromCharacter(chr, FindCharacterItemByGroup(chr, MUSKET_ITEM_TYPE));
    }

	if(isMoney)
	{
		if(isSave)
		{
			chr.tmp_money = chr.money;
		}
		chr.money = 0;
	}
}

void CheckCountCemeteryLSC()
{
    if(CheckAttribute(pchar, "questTemp.UndertakersSurveyLSC") && pchar.questTemp.UndertakersSurveyLSC == "3")
    {
        pchar.questTemp.LSC = "UndertakersSurveyCompleteLSC";
        ref sld = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
        AddQuestRecord("ISS_PoorsMurder", "22");
		AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("ёл","ела"));
        AddQuestUserData("ISS_PoorsMurder", "sCity", XI_ConvertString("Colony" + sld.city + "Acc"));
        AddLandQuestMark_Main(sld, "ISS_PoorsMurder");
    }
}

void RestoreEquip(ref chr)
{
	aref arItm, arSub;
	if(CheckAttribute(chr, "tmp_items"))
	{
		makearef(arItm, chr.tmp_items);
		
		for(int i=0; i<GetAttributesNum(arItm); i++)
		{
			arSub = GetAttributeN(arItm, i);
			GiveItem2Character(chr, GetAttributeValue(arSub));
		}
		DeleteAttribute(chr, "tmp_items");
	}
		
	if(CheckAttribute(chr, "tmp_money"))
	{
		chr.money = (sti(chr.money)+sti(chr.tmp_money));
		DeleteAttribute(chr, "tmp_money");
	}
}
//// от <- Dolphin

//-------------------------------------------------------------------------------------------
//  Dolphin -> установка квеста на вход в локатор возле двери комнаты таверны
void EnterTavernRoomLocator(string sQuest, string sTavern, string sAction)
{
	pchar.quest.(sQuest).win_condition.l1 = "locator";
	pchar.quest.(sQuest).win_condition.l1.location = sTavern;
	pchar.quest.(sQuest).win_condition.l1.locator_group = "reload";
	pchar.quest.(sQuest).win_condition.l1.locator = "reload2_back";
	pchar.quest.(sQuest).win_condition = sAction;
}

//-------------------------------------------------------------------------------------------
//  Dolphin -> проверка на квестовость НПС (для блокировки установки в Абордажники)
bool CheckNpcForQuest(ref ch)
{
	bool bOk = false;

	switch(ch.id)
	{
		case "FL_granie": bOk = true; break;
		case "FL4_1stMate1": bOk = true; break;
		case "FL4_1stMate2": bOk = true; break;
		case "FL_LoranDeGraff": bOk = true; break;
	}

	return bOk;
}

//-------------------------------------------------------------------------------------------
//  Dolphin -> Чтение квестовых записок
bool CheckLetterForQuest(ref itmRef)
{
	int i;
	ref sld;
	/*if (itmRef.id == "ProblemMoney")
	{
		if(!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			DoQuestCheckDelay("ProblemMoney_ReadLetter", 1.0);
		}
		return true;
	}
	if (itmRef.id == "ProblemMoneyMap") SetFormatedText("MAP_TEXT", GetConvertStr("itmdescr_ProblemMoneyMap", "ItemsDescribe.txt"));
	*/
	if (itmRef.id == "FQ_letter1")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			DoQuestCheckDelay("FL1_s53", 1.0);
		}
		SetFormatedItemText("FQ_letter1");
		return true;
    }

	if (itmRef.id == "LogbookLSC" && CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "InvestigationCryptLSC")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			itmRef.describe = "itmdescr_LogbookLSCReading";
			AddQuestRecord("ISS_PoorsMurder", "18");
			AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("","а"));
			pchar.questTemp.LSC = "LogbookFoundLSC";
		}
		return false;
	}
	if (itmRef.id == "LogbookLSC" && CheckAttribute(pchar, "questTemp.LSC") && pchar.questTemp.LSC == "LogToDecryptLSC_Taken")
    {
        if (!CheckAttribute(itmRef, "read"))
        {
            itmRef.read = true;
            itmRef.describe = "itmdescr_LogbookLSCDecryptedReading";
            AddQuestRecord("ISS_PoorsMurder", "24");
            pchar.questTemp.LSC = "LogbookDecryptedAndReadLSC";
        }
        return false;
    }

	if (itmRef.id == "RingCapBook")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			itmRef.describe = "itmdescr_RingCapBookRead";
            pchar.questTemp.LSC.Ring.ReadCapBook = "true";
		}
		SetFormatedItemText("RingCapBook");
		return true;
	}
	
	if (itmRef.id == "LesopilkaLog")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			itmRef.describe = "itmdescr_LesopilkaLog";
            pchar.questTemp.PDM_Lesopilka_ReadBook = "true";
			PDM_Lesopilka_Treasures_ReadLog();
		}
		SetFormatedItemText("LesopilkaLog");
		return true;
	}

	if (itmRef.id == "letter_LSC")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
		    itmRef.read = true;
            itmRef.name = "itmname_letter_open";
            sld = characterFromId(pchar.questTemp.LSC.qtyTalk.headPoormanId);
			AddQuestRecord("ISS_PoorsMurder", "6_2");
			AddQuestUserData("ISS_PoorsMurder", "sCity", XI_ConvertString("Colony" + sld.city + "Acc"));
			AddQuestUserData("ISS_PoorsMurder", "sName", GetFullName(sld));

			AddLandQuestMark_Main(sld, "ISS_PoorsMurder");
		}
		SetFormatedItemText("letter_LSC");
		return true;
	}

	if (itmRef.id == "letter_LSC_1")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
		    itmRef.read = true;
		    AddQuestRecord("ISS_PoorsMurder", "11");
            AddQuestUserData("ISS_PoorsMurder", "sSex", GetSexPhrase("ся", "ась"));
            AddQuestUserData("ISS_PoorsMurder", "sName", pchar.questTemp.LSC.poorName);
		}
		SetFormatedItemText("letter_LSC_1");
		return true;
	}

	if (itmRef.id == "letter_LSC_2")
	{
		if (!CheckAttribute(itmRef, "read")) itmRef.read = true;
		SetFormatedItemText("letter_LSC_2");
		return true;
	}

	if (itmRef.id == "strangeNoteLSC")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			pchar.questTemp.LSC = "FindGulfOfDoomLSC";
			CreateSecretFort();
		}
		SetFormatedItemText("strangeNoteLSC");
		return true;
	}

	if (itmRef.id == "TizerJournal")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			AddQuestRecord("PreparationForISS", "4");

			if (!HaveAllPerks(pchar, "self"))
			{
				if (CheckAttribute(pchar, "perks.FreePoints_self"))
					pchar.perks.FreePoints_self = sti(pchar.perks.FreePoints_self) + 1;
				else
					pchar.perks.FreePoints_self = 1;

				notification(ColorTextLine(StringFromKey("InfoMessages_213", pchar, GetFullName(pchar)), "gold"), "Personal abilities");
			}
			else if (!HaveAllPerks(pchar, "ship"))
			{
				if (CheckAttribute(pchar, "perks.FreePoints_ship"))
					pchar.perks.FreePoints_ship = sti(pchar.perks.FreePoints_ship) + 1;
				else
					pchar.perks.FreePoints_ship = 1;

				notification(ColorTextLine(StringFromKey("InfoMessages_213", pchar, GetFullName(pchar)), "gold"), "Ship abilities");
			}

			AddCharacterExpToSkill(pchar, SKILL_LEADERSHIP,	250);
			AddCharacterExpToSkill(pchar, SKILL_F_LIGHT,	250);
			AddCharacterExpToSkill(pchar, SKILL_FENCING,	250);
			AddCharacterExpToSkill(pchar, SKILL_F_HEAVY,	250);
			AddCharacterExpToSkill(pchar, SKILL_PISTOL,		250);
			AddCharacterExpToSkill(pchar, SKILL_FORTUNE,	250);
			AddCharacterExpToSkill(pchar, SKILL_SNEAK,		250);
			AddCharacterExpToSkill(pchar, SKILL_SAILING,	250);
			AddCharacterExpToSkill(pchar, SKILL_ACCURACY,	250);
			AddCharacterExpToSkill(pchar, SKILL_CANNONS,	250);
			AddCharacterExpToSkill(pchar, SKILL_GRAPPLING,	250);
			AddCharacterExpToSkill(pchar, SKILL_DEFENCE,	250);
			AddCharacterExpToSkill(pchar, SKILL_REPAIR,		250);
			AddCharacterExpToSkill(pchar, SKILL_COMMERCE,	250);

			sld = CharacterFromId("Secret_Fort_Commander");
			sld.dialog.currentnode = "Commander_3_talk_1";

			// > чтение дневника занимает некоторое время
			AddTimeToCurrent(0, 19 + rand(25));
			RefreshLandTime();
			Whr_UpdateWeather();
		}
		SetFormatedItemText("TizerJournal");
		return true;
	}

	/*if (itmRef.id == "FQ_letter3")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			DoQuestCheckDelay("FL3_s32", 1.0);
		}
		return true;
	}

	if (itmRef.id == "FQ_letter4")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			AddQuestRecord("FL4", "1");
			//DoQuestCheckDelay("FL4_s35", 1.0);
		}
		return true;
	}

	if (itmRef.id == "FQ_letter5")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			DoQuestCheckDelay("FL4_s46", 1.0);
		}
		return true;
	}

	if (itmRef.id == "FQ_letter6")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			DoQuestCheckDelay("FL6_6", 1.0);
		}
		return true;
	}

	if (itmRef.id == "FQ_letter7")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			DoQuestCheckDelay("FL8_s7", 1.0);
		}
		return true;
	}

	if (itmRef.id == "FQ_letter8")
	{
		if (!CheckAttribute(itmRef, "read"))
		{
			itmRef.read = true;
			DoQuestCheckDelay("FL9_s4", 1.0);
		}
		return true;
	}*/
	return false;
}

void SetFormatedItemText(string sItem)
{
    SetFormatedText("READ_TEXT", GetConvertStr("itmtext_" + sItem, "ItemsDescribe.txt"));
}

//-------------------------------------------------------------------------------------------
//  Dolphin Семейная жизнь ->
//	Изменение отношения супруги к ГГ от 0..100
int ChangeMariedRelation(ref chr, int point)
{
	if(!CheckAttribute(chr, "Maried_relation")) chr.Maried_relation = 50;

	chr.Maried_relation = (sti(chr.Maried_relation) + point);
	if(sti(chr.Maried_relation) < 0) chr.Maried_relation = 0;
	if(sti(chr.Maried_relation) > 100) chr.Maried_relation = 100;
	
	Log_TestInfo(StringFromKey("QuestsUtilite_24") + " " + point);
	Log_TestInfo(StringFromKey("QuestsUtilite_25") + " " + chr.Maried_relation);

	return sti(chr.Maried_relation);
}

//вынесена реализация активации сценки смерти брата Изабель т.к. теперь дергается в двух местах
void SeeBrotherDeadNearHouse()
{
    pchar.quest.Romantic_DeadBrother_Cancel.over = "yes"; //убираем таймер на вовремя не явлился
    StartQuestMovie(true, true, true);
    pchar.RomanticQuest = "BrotherIsDead";
    LAi_SetActorType(pchar);
    SetMainCharacterIndex(GetCharacterIndex("Husband"));
    locCameraToPos(40.585, 6.0, -47.549, false);
    LAi_SetActorType(PChar);
    PChar.BaseNation = SPAIN; //скрипт в городе, иначе глючит опрос патрулями
    PChar.RomanticQuest = "";
    LAi_SetActorType(CharacterFromID("MigelDeValdes"));
    SetActorDialogAny2Pchar("MigelDeValdes", "", 1.0, 0.0);
    LAi_ActorFollow(pchar, CharacterFromID("MigelDeValdes"), "ActorDialog_Any2Pchar", 0.0);
}

//Мини-квесты городских NPC
void SetPassengerParameter(string _sIndex, bool bEnemy)//Jason, общие параметры пассажиров
{
	if (bEnemy)
	{
		pchar.GenQuest.(_sIndex).City = FindCityToMC(false, true); //мб лучше drand на второй аргумент? (false)
		pchar.GenQuest.(_sIndex).Enemycity = true;
	}
	else pchar.GenQuest.(_sIndex).City = FindCityToMC(true, true); //мб лучше drand на второй аргумент? (false)
	pchar.GenQuest.(_sIndex).StartCity = GetCurrentTown(); //стартовый город
	int DaysQty = GetMaxDaysFromColony2Colony(pchar.GenQuest.(_sIndex).City, pchar.GenQuest.(_sIndex).StartCity);
	if (DaysQty > 16) DaysQty = 16;
	if (DaysQty < 1) DaysQty = 7; // на всякий пожарный
	pchar.GenQuest.(_sIndex).DaysQty = makeint(sti(DaysQty)*(frand(1.5)+1.0)); //дни
	float fShipIdx;
	switch(7-sti(RealShips[sti(Pchar.Ship.Type)].Class))
	{
		case 0: fShipIdx = 0.8; break; // не используется
		case 1: fShipIdx = 1.0; break;
		case 2: fShipIdx = 1.2;	break;
		case 3: fShipIdx = 1.5; break;
		case 4: fShipIdx = 2.2; break;
		case 5: fShipIdx = 3.0; break;
		case 6:	fShipIdx = 4.5; break;
	}
	pchar.GenQuest.(_sIndex).Money = (sti(DaysQty)*500*stf(fShipIdx)+rand(100))*sti(DaysQty)/sti(pchar.GenQuest.(_sIndex).DaysQty);
	if (bEnemy) pchar.GenQuest.(_sIndex).Money = makeint(sti(pchar.GenQuest.(_sIndex).Money)*1.2); //оплата
}

//фикс продажи товаров и сверх заработка у ПГГ
void CheckPGGQuestGoods(int iCurGoodsIdx, int nTradeQuantity)
{
    if (CheckAttribute(pchar, "GenQuest.PGG_Quest.StartGoods") && sti(PChar.GenQuest.PGG_Quest.Goods) == iCurGoodsIdx)
    {
        if (sti(PChar.GenQuest.PGG_Quest.StartGoods) <= nTradeQuantity) PChar.GenQuest.PGG_Quest.StartGoods = 0;
        else PChar.GenQuest.PGG_Quest.StartGoods = sti(PChar.GenQuest.PGG_Quest.StartGoods) - nTradeQuantity;
    }
}

bool CheckCaribGuns() // Jason: есть ли пистоли для продажи карибам
{
	for (int i = 1; i <= 6; i++)
    {
		if (GetCharacterFreeItem(pchar, "pistol" + i) > 0) return true;
	}
	return false;
}

// ugeen -->
//--> расчёт аренды склада
int GetStoragePrice(int cof)
{
	float fLeadership = 1.5 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)/120.0; // учитываем лидерство
	float fCommerce = 1.5 - GetSummonSkillFromName(pchar, SKILL_COMMERCE)/120.0; // учитываем торговлю

	int price = makeint(cof * MOD_SKILL_ENEMY_RATE * fLeadership * fCommerce);

	return price;
}
//<-- расчёт аренды склада
// --> перемещаем остатки груза со склада на корабль ГГ с перегрузом, пусть сам разбирается что делать со всем этим барахлом
void SetStorageGoodsToShip(ref pStorage)
{
	int iStoreQ;
	for (int i = 0; i< GOODS_QUANTITY; i++)
	{
		iStoreQ = GetStorageGoodsQuantity(pStorage, i);
		if (iStoreQ == 0) continue;
		SetCharacterGoods(pchar, i, GetCargoGoods(pchar, i) + iStoreQ);// перегруз
		RemoveStorageGoods(pStorage, i, iStoreQ);
	}
}
// <-- ugeen

// KZ > ref вопрошаек
void SeaQuestionsInit()
{
	int i, j = 84;
	int n = 0;
	string q, a;
	
    NullCharacter.SeaQuestions = j;
	
	for (i = 0; i <= j; i++)
	{
		q = "q" + i;
		a = "a" + i;
		
		n++;
		NullCharacter.SeaQuestions.(q) = StringFromKey("SeaQuestions_" + n);
		n++;
		NullCharacter.SeaQuestions.(a) = StringFromKey("SeaQuestions_" + n);
	}
}

// AlexBlade > Установка квестовых маркеров для некоторых мэйн-квестов
void MainQuestMarks_Init()
{
    // Кондотьер
    HeadHunter_Smuggler_AddQuestMarks();

    // Tравля крыс
    pirateStartQuest_Begin_AddQuestMarks();

    // Шарп
    SeaPearl_Begin_AddQuestMarks();

    // ЛГ
    GhostShipQuest_Begin_AddQuestMarks();

    // Нац. линейки
    StateLines_Begin_AddQuestMarks();

    // ==> линейка Теночтитлана
    AddMapQuestMark_Major("Shore53", "TenochtitlanQuest", "Teno_Begin_WDMQuestMarkCondition");

    //зачарованный город
    AddMapQuestMark_Major("Caracas_town", "MagicCity", "MagicCity_Begin_WDMQuestMarkCondition");

	// Опасный груз
	AddMapQuestMark_Major("Cumana_Fort", "zpq", "zpq_Begin_WDMQuestMarkCondition");
	AddLandQuestmarkToFantoms_Main("AmmoOff", "zpq", "zpq_Begin_AmmoOff_QuestMarkCondition");
}


// Глобальный туториал
// В этом режиме метки и указатели всегда показываются
// Туториалы нельзя отключить
// А также меняется поведение игры в некоторых моментах
bool GetGlobalTutor()
{
    return CheckAttribute(&TEV, "GlobalTutor");
}
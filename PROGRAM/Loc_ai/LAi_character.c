
//------------------------------------------------------------------------------------------
//Login
//------------------------------------------------------------------------------------------

//Установить время загрузки персонажа
void LAi_SetLoginTime(aref chr, float start, float end)
{
	Restrictor(&start, 0.0, 23.99999999);
	Restrictor(&end, 0.0, 23.99999999);
	chr.location.stime = start;
	chr.location.etime = end;
}

//Удалить время загрузки персонажа
void LAi_RemoveLoginTime(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "stime");
	DeleteAttribute(loc, "etime");
}

//Данный персонаж является верующим, и в определённое время находиться в церкви
void LAi_SetFanatic(aref chr, string churchID, string group, string locator, float start, float end)
{
	chr.location.church = churchID;
	chr.location.church.group = group;
	chr.location.church.locator = locator;
	chr.location.church.stime = start;
	chr.location.church.etime = end;
}

//Сделать обычным персонаж
void LAi_RemoveFanatic(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "church");
}

//Запретить перерождение персонажа после убийства
void LAi_NoRebirthEnable(aref chr)
{
	chr.location.norebirth = "1";
}

//Разрешить перерождение персонажа после убийства
void LAi_NoRebirthDisable(aref chr)
{
	aref loc;
	makearef(loc, chr.location);
	DeleteAttribute(loc, "norebirth");
}

//Перерождение нпс со старым именем
void LAi_RebirthOldName(aref chr)
{
	chr.location.rebirthOldName = true;
}

//Разрешить/запретить персонажу загружаться в захваченную локацию
void LAi_LoginInCaptureTown(aref chr, bool isEnable)
{
	aref loc;
	makearef(loc, chr.location);
	if(isEnable)
	{
		loc.loadcapture = "1";
	}else{
		DeleteAttribute(loc, "loadcapture");
	}
}

//------------------------------------------------------------------------------------------
//Fight, hp
//------------------------------------------------------------------------------------------

//Установить хитпойнты
void LAi_SetHP(aref chr, float cur, float max)
{
	if(max < 1) max = 1;
	if(cur < 0) cur = 0;
	if(cur > max) cur = max;
	chr.chr_ai.hp = cur;
	chr.chr_ai.hp_max = max;
}

//Установить текущии хитпойнты
void LAi_SetCurHP(aref chr, float cur)
{
	float maxHP = LAI_DEFAULT_HP_MAX;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		maxHP = stf(chr.chr_ai.hp_max);
		if(maxHP < 1) maxHP = 1;
	}
	chr.chr_ai.hp_max = maxHP;
	if(cur < 0) cur = 0;
	if(cur > maxHP) cur = maxHP;
	chr.chr_ai.hp = cur;
	if (cur == 0.0 && CheckAttribute(chr, "PGGAi"))
	{
		PGG_CheckDead(chr);
	}
}

//Установить текущии хитпойнты и энергию максимальными
void LAi_SetCurHPMax(aref chr)
{
	float maxHP = LAI_DEFAULT_HP_MAX;
	if(CheckAttribute(chr, "chr_ai.hp_max"))
	{
		maxHP = stf(chr.chr_ai.hp_max);
		if(maxHP < 1) maxHP = 1;
	}
	chr.chr_ai.hp_max = maxHP;
	chr.chr_ai.hp = maxHP;

	chr.chr_ai.energy    = LAi_GetCharacterMaxEnergy(chr); // восстановление там, где мах НР
}

//Скорость изменения хп в секунду
void LAi_SetDltHealth(aref chr, float healthPerSec)
{
	//if(healthPerSec < 0) healthPerSec = 0;
	chr.chr_ai.hp_dlt = healthPerSec;
}

//Использовать бутылочку-лечилку
void LAi_UseHealthBottle(aref chr, float healthInBottle)
{
	if(healthInBottle <= 0) return;	
	if(!CheckAttribute(chr, "chr_ai.hp_bottle"))
	{
		chr.chr_ai.hp_bottle = "0";
	}
	chr.chr_ai.hp_bottle = stf(chr.chr_ai.hp_bottle) + healthInBottle;
	if(chr.id == Characters[nMainCharacterIndex].id) chr.chr_ai.usedbottlemax = stf(chr.chr_ai.hp_bottle);
}
// boal

void LAi_UseEnergyBottle(aref chr, float energyInBottle)
{
	if (energyInBottle <= 0) return;
	
	if (!CheckAttribute(chr, "chr_ai.ep_bottle"))
		chr.chr_ai.ep_bottle = "0";
	
	chr.chr_ai.ep_bottle = stf(chr.chr_ai.ep_bottle) + energyInBottle;
}

void LAi_UseHealthBottleSpeed(aref chr, float healthSpeed)
{
	if (healthSpeed <= 0) return;
	
	chr.chr_ai.hp_dlt_bottle = healthSpeed;
}

void LAi_UseEnergyBottleSpeed(aref chr, float energySpeed)
{
	if (energySpeed <= 0) return;
	
	chr.chr_ai.ep_dlt_bottle = energySpeed;
}

// KZ > кастомное восполнение HP и/или EP; эмуляция работы бутылок
// > chr - кому; sSource - что (hp или health - здоровье; ep или energy - энергия);
// > sQuantity - сколько; sSpeed - с какой скоростью; sSound - воспроизвести звук.
void LAi_UseCustomBottle(aref chr, string sSource, string sQuantity, string sSpeed, string sSound)
{
	sSource = GetStrSmallRegister(stripblank(sSource));
	
	int i, q = KZ|Symbol(sSource, ",");
	float fQty, fSpd;
	string tmp, func, snd = "";
	
	for (i = 0; i <= q; i++)
	{
		tmp = GetSubStr(sSource, ",", i);
		
		if (!StrHasStr(tmp, "hp,health,ep,energy", true))
			continue;
		
		if (HasStrEx(tmp, "hp,health", "|"))
			tmp = "Health";
		else
			tmp = "Energy";
		
		func = "LAi_Use" + tmp + "Bottle";
		fQty = stf(GetSubStr(sQuantity, ",", i));
		if (fQty <= 0) fQty = 40.0;
		
		call func(chr, fQty);
		
		func = "LAi_Use" + tmp + "BottleSpeed";
		fSpd = stf(GetSubStr(sSpeed, ",", i));
		if (fSpd <= 0) fSpd = 5.0;
		
		call func(chr, fSpd);
		
		if (sSound != "")
		{
			tmp = GetSubStr(sSound, ",", i);
			
			if (tmp != "" && snd != tmp)
			{
				snd = tmp;
				PlaySound(snd);
			}
		}
	}
}

//navy -->
void LAi_AlcoholSetDrunk(aref chr, float alcoholDegree, float time)
{
	//float energyMax;
	chr.chr_ai.drunk = time;
    LAi_AlcoholDebaff(chr, alcoholDegree);
}

void LAi_AlcoholDebaff(aref chr, float alcoholDegree)
{
	//много рома в таверне
	if (alcoholDegree > 70)
	{
		chr.chr_ai.drunk.skill.FencingLight = -20;
		chr.chr_ai.drunk.skill.Fencing 	    = -20;
		chr.chr_ai.drunk.skill.FencingHeavy = -20;
		chr.chr_ai.drunk.skill.Pistol       = -20;
		chr.chr_ai.drunk.skill.Fortune      = -20;
		chr.chr_ai.drunk.skill.Sneak        = -20;
		chr.chr_ai.drunk.skill.Leadership   = -20;
	}
	else
	{
		//Ром
		if (alcoholDegree > 50)
		{
			chr.chr_ai.drunk.skill.FencingLight = -10;
			chr.chr_ai.drunk.skill.FencingHeavy = 10;
		}
		//вино
		else
		{
			chr.chr_ai.drunk.skill.FencingLight = 10;
			chr.chr_ai.drunk.skill.FencingHeavy = -10;
		}
		chr.chr_ai.drunk.skill.Fortune = 5;
		chr.chr_ai.drunk.skill.Pistol = -20;
	}
}

void LAi_SetAlcoholNormal(aref chr)
{
	/*
	if(CheckAttribute(chr, "chr_ai.energyMax"))
	{
		chr.chr_ai.energyMax = stf(chr.chr_ai.energyMax) - stf(chr.chr_ai.drunk.energyMax);
	}
	*/
	if (CheckAttribute(chr, "questTemp.Rum"))         DeleteAttribute(chr, "questTemp.Rum");
	if (CheckAttribute(chr, "GenQuest.CamShuttle"))   DeleteAttribute(chr, "GenQuest.CamShuttle");

	DeleteAttribute(chr, "chr_ai.drunk");
}

//функция установки степени опьянения и качания камеры ГГ
//при значениях выше 4 камера сильнее трястись не будет, имеет смысл только для установки длительности эффекта
void LAi_SetAlcoholState(int iShuttle)
{
    pchar.GenQuest.CamShuttle = iShuttle;
    pchar.questTemp.Rum = iShuttle * 2;
    DeleteAttribute(pchar, "chr_ai.drunk");
    LAi_AlcoholSetDrunk(pchar, 71, iShuttle * 5600);
}

//функция повышения алкоголя в крови. применяется в тавернах
void LAi_UpAlcoholState()
{
    if (CheckAttribute(pchar, "questTemp.Rum"))
    {
        DeleteAttribute(pchar, "chr_ai.drunk");
        pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
        if (sti(pchar.questTemp.Rum) < 3) LAi_AlcoholSetDrunk(pchar, 51, 5600);
        else
        {
            LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum)*2800);
            pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum)/2); // Jason
        }
    }
    else
    {
        pchar.questTemp.Rum = 1;
        pchar.chr_ai.drunk = 2800;
    }
}

//функция повышения алкоголя при распитии бутылочных напитков
void LAi_DrunkAlcoholPotion(ref chref, ref arItm)
{
    if (CheckAttribute(chref, "questTemp.Rum"))
    {
        DeleteAttribute(chref, "chr_ai.drunk");
        chref.questTemp.Rum = sti(chref.questTemp.Rum) + 2;
        chref.GenQuest.CamShuttle = makeint(sti(chref.questTemp.Rum)/2);
        LAi_AlcoholSetDrunk(chref, 71, sti(chref.questTemp.Rum)*2800);
    }
    else
    {
        LAi_AlcoholSetDrunk(chref, stf(arItm.potion.drunk), stf(arItm.potion.drunk.time));
        chref.questTemp.Rum = 2;
        chref.GenQuest.CamShuttle = 1;
    }
}

//функция понижения алкоголя в крови посредством сна в таверне или прокрутки времени через мысли в слух
void LAi_DawnWaitAlcoholState(int iAddtime)
{
    if (CheckAttribute(pchar, "questTemp.Rum") && CheckAttribute(pchar, "chr_ai.drunk"))
    {
        int iTmp = sti(pchar.chr_ai.drunk);
        iTmp -= (iAddtime * 900);
        LAi_DawnAlcoholState(pchar, iTmp);
    }
}

//функция понижения алкоголя в крови в режиме реального времени
void LAi_DawnAlcoholState(ref chref, int iDrunk)
{
    if (iDrunk < 1) LAi_SetAlcoholNormal(chref);
    if (CheckAttribute(chref, "chr_ai.drunk"))
    {
        if (iDrunk < 16800) DeleteAttribute(chref, "chr_ai.drunk");
        chref.chr_ai.drunk = iDrunk;

        if (iDrunk < 2700) //CamShuttle = 0
        {
            LAi_AlcoholDebaff(chref, 51);
            if (CheckAttribute(chref, "questTemp.Rum")) DeleteAttribute(chref, "questTemp.Rum");
            if (CheckAttribute(chref, "GenQuest.CamShuttle")) DeleteAttribute(chref, "GenQuest.CamShuttle");
        }
        else if (iDrunk < 5600) //CamShuttle = 1
        {
            LAi_AlcoholDebaff(chref, 51);
            chref.questTemp.Rum = 2;
            chref.GenQuest.CamShuttle = 1;
        }
        else if (iDrunk < 11200) //CamShuttle = 2
        {
            LAi_AlcoholDebaff(chref, 71);
            chref.questTemp.Rum = 4;
            chref.GenQuest.CamShuttle = 2;
        }
        else if (iDrunk < 16800) //CamShuttle = 3
        {
            LAi_AlcoholDebaff(chref, 71);
            chref.questTemp.Rum = 6;
            chref.GenQuest.CamShuttle = 3;
        }
    }
    if (sti(chref.index) == GetMainCharacterIndex()) LAi_UpdateAlcoholCamShuttleCamera();
}

//функция вызова бултыхания камеры
//если атрибута CamShuttle нет, то стабилизирует камеру без необходимости перемещения в другую локацию
void LAi_UpdateAlcoholCamShuttleCamera()
{
    if (pchar.chr_ai.tmpl != LAI_TMPL_DIALOG) //в диалогах камеру не бултыхаем
    {
        int locIndex = FindLocation(pchar.location);
        SetCamShuttle(&Locations[locIndex]);
    }
}
//<--

//Использовать бутылочку-противоядие
void LAi_UseAtidoteBottle(aref chr)
{
	DeleteAttribute(chr, "chr_ai.poison");
}

//Отравлен
bool LAi_IsPoison(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.poison")) return true;
	return false;
}

//Сделать персонажа бессмертным
void LAi_SetImmortal(aref chr, bool isImmortal)
{
	if(isImmortal)
	{
		chr.chr_ai.immortal = "1";
	}
    else
    {
		aref chr_ai;
		makearef(chr_ai, chr.chr_ai);
		DeleteAttribute(chr_ai, "immortal");
	}
}

//Сделать персонажа Ванькой-Встанькой
void LAi_SetRolyPoly(aref chr, bool isRolyPoly)
{
	if (isRolyPoly) chr.chr_ai.roly_poly = 1;
	else DeleteAttribute(chr, "chr_ai.roly_poly");
}

//Узнать отношение персонажа к бессмертию
bool LAi_IsImmortal(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.immortal"))
	{
		if(sti(chr.chr_ai.immortal) != 0)
		{
			return true;
		}
	}
	return false;
}


//Получить хп персонажа
float LAi_GetCharacterHP(aref chr)
{
	float curHp = 0.0;
	if(CheckAttribute(chr, "chr_ai.hp"))
	{
		curHp = stf(chr.chr_ai.hp);
	}
	float maxHp = LAi_GetCharacterMaxHP(chr);
	if(curHp > maxHp) curHp = maxHp;
	chr.chr_ai.hp = curHp;
	chr.chr_ai.hp_max = maxHp;
	return curHp;
}

//Получить максимальные хп персонажа
float LAi_GetCharacterMaxHP(aref chr)
{
	float max_hp = 0.0;
	float bonus = 0.0;
	
	if (CheckAttribute(chr, "chr_ai.hp_max"))
	{
		if (CheckAttribute(chr, "chr_ai.bonus_hp"))
			max_hp = stf(chr.chr_ai.hp_max) - stf(chr.chr_ai.bonus_hp);
		else
			max_hp = stf(chr.chr_ai.hp_max);
	}
	
	if (max_hp < 0.0)
		max_hp = 0.0;
	
	if (IsFighter(chr) && CheckCharacterPerk(pchar, "PersonalCare"))
		bonus += max_hp * 0.2;
	
	if (CheckCharacterPerk(chr, "HPPlus"))
		bonus += stf(chr.rank);
	
	chr.chr_ai.hp_max = max_hp + bonus;
	chr.chr_ai.bonus_hp = bonus;
	
	return stf(chr.chr_ai.hp_max);
}

//Получить относительные хп персонажа 0..1
float LAi_GetCharacterRelHP(aref chr)
{
	float hp = LAi_GetCharacterHP(chr);
	float maxhp = LAi_GetCharacterMaxHP(chr);
	if(maxhp <= 0.0) return 0.0;
	if(maxhp > 0.0)
	{
		return hp/maxhp;
	}
	return 0.0;
}

//Получить относительную энергию персонажа 0..1
float LAi_GetCharacterRelEnergy(aref chr)
{
	float energy = 0.0;
	if(CheckAttribute(chr, "chr_ai.energy"))
	{
		energy = stf(chr.chr_ai.energy);
		energy = energy / LAi_GetCharacterMaxEnergy(chr); // boal
	}
	return energy;
}
// boal
float LAi_GetCharacterMaxEnergy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.energyMax"))
	{
		return stf(chr.chr_ai.energyMax);
	}
	return LAI_DEFAULT_ENERGY_MAX;
}

//Установить проверяльщик хп, если их становиться меньше чем, вызвать квест
void LAi_SetCheckMinHP(aref chr, float min, bool immortal, string quest)
{
	if(min < 0.9999999) min = 0.9999999;
	chr.chr_ai.hpchecker = min;
	chr.chr_ai.hpchecker.quest = quest;
	chr.chr_ai.hpchecker.immortal = immortal;
}

//Удалить проверяльщик хп
void LAi_RemoveCheckMinHP(aref chr)
{
	aref chr_ai;
	makearef(chr_ai, chr.chr_ai);
	DeleteAttribute(chr_ai, "hpchecker");	
}

//Убить персонажа
void LAi_KillCharacter(aref chr)
{
	chr.chr_ai.hp = "0";
	if(CheckAttribute(chr, "chr_ai.immortal"))
	{
		string old = chr.chr_ai.immortal;
		chr.chr_ai.immortal = "0";
		LAi_CheckKillCharacter(chr);
		chr.chr_ai.immortal = old;
	}
	else
	{
		LAi_CheckKillCharacter(chr);
	}
}

//Убит ли персонаж
bool LAi_IsDead(aref chr)
{
	if(CheckAttribute(chr, "id"))
	{
		if(chr.id == "0") return true; // boal если фантома нет, то НПС умер
	}
	if(!CheckAttribute(chr, "chr_ai.hp"))
	{
		return true;
	}
	else
	{
		if(stf(chr.chr_ai.hp) < 1.0) return true;
	}
	return false;
}

//------------------------------------------------------------------------------------------
//Other
//------------------------------------------------------------------------------------------

//Является ли персонаж управляемым
bool LAi_IsCharacterControl(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.tmpl"))
	{
		if(chr.chr_ai.tmpl == LAI_TMPL_PLAYER) return true;
	}
	return false;
}

//Запретить диалог с персонажем
void LAi_CharacterDisableDialog(aref chr)
{
	chr.chr_ai.disableDlg = "1";
}

//Разрешить диалог с персонажем
void LAi_CharacterEnableDialog(aref chr)
{
	chr.chr_ai.disableDlg = "0";
}

//Разрешить при смерти порождить фантома
void LAi_CharacterReincarnation(aref chr, bool isEnable, bool isUseCurModel)
{
	LAi_CharacterReincarnationEx(chr, isEnable, isUseCurModel, "");
}

//Разрешить при смерти порождить фантома
void LAi_CharacterReincarnationEx(aref chr, bool isEnable, bool isUseCurModel, string locgroup)
{
	if(isEnable)
	{
		if(isUseCurModel)
		{
			chr.chr_ai.reincarnation = "0";
		}
		else
		{
			chr.chr_ai.reincarnation = "1";
		}
		if(locgroup == "") locgroup = "goto";
		chr.chr_ai.reincarnation.group = locgroup;
	}
	else
	{
		chr.chr_ai = "";
		aref chr_ai;
		makearef(chr_ai, chr.chr_ai);
		DeleteAttribute(chr_ai, "reincarnation");
	}	
}

bool LAi_CharacterIsReincarnation(aref chr)
{
	if(!CheckAttribute(chr, "chr_ai.reincarnation")) return false;
	return true;
}

bool LAi_CharacterReincarnationMode(aref chr)
{
	if(!CheckAttribute(chr, "chr_ai.reincarnation"))
	{
		Trace("LAi_CharacterReincarnationMode -> no field chr.chr_ai.reincarnation");
		return false;
	}
	if(sti(chr.chr_ai.reincarnation) != 0) return true;
	return false;
}

string LAi_CharacterReincarnationGroup(aref chr)
{
	if(!CheckAttribute(chr, "chr_ai.reincarnation.group"))
	{
		Trace("LAi_CharacterReincarnationGroup -> no field chr.chr_ai.reincarnation");
		return "goto";
	}
	if(chr.chr_ai.reincarnation.group != "") return chr.chr_ai.reincarnation.group;
	return "goto";
}

//eddy. установить установить шаг повышения ранга фантома при реинкарнации.
bool LAi_SetReincarnationRankStep(aref _chr, int _step) 
{
	if(CheckAttribute(_chr, "chr_ai.reincarnation"))
	{
		_chr.chr_ai.reincarnation.step = _step;
		_chr.baseIndex = _chr.index; //теперь все реинкарнированные фантомы будут помнить индекс своего прародителя.
		return true;
	}
	else Trace("LAi_SetReincarnationRankStep -> no field chr.chr_ai.reincarnation");
	return false;
}

//------------------------------------------------------------------------------------------
//Other
//------------------------------------------------------------------------------------------

//Проиграть звук
void LAi_CharacterPlaySound(aref chr, string soundname)
{
	SendMessage(chr, "s", soundname);
}

//Переключиться в боевой или мирный режим
void LAi_SetFightMode(aref chr, int isFightMode)
{
	if (isFightMode != 0)
	{
		if (SendMessage(chr, "ls", MSG_CHARACTER_EX_MSG, "CheckFightMode") != 0)
			return; //Не для переключения между режимами эта функция
		if (CheckAttribute(chr, "PriorityMode"))
			isFightMode = sti(chr.PriorityMode);
	}
	if (IsMainCharacter(chr))
	{
		if (isFightMode != 0) LAi_LockFightMode(chr, false); // если вызвали, значит точно разлочим)
		SendMessage(&objLandInterface, "ll", MSG_BATTLE_LAND_CROSSHAIR_SHOW, 0);
	}
	SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "ChangeFightMode", isFightMode);
}

// Активировать боевой режим по PriorityMode, либо выключить
void LAi_SetFightModeForOfficers(bool isFightMode)
{
    ref chr;
    int i, idx;
    for (i = 1; i < 4; i++)
    {
        idx = GetOfficersIndex(PChar, i);
        if (idx > 0)
        {
	        chr = GetCharacter(idx);
	        LAi_type_officer_Init(chr);
	        //LAi_group_UpdateTargets(chr);
			LAi_SetFightMode(chr, isFightMode);
	    }
	}
}

//Присвоить персонажу боевой режим (для появления без анимации доставания оружия на абордажах, штурмах и т.д.)
void LAi_InstantFightMode(aref chr)
{
	if(CheckAttribute(chr, "PriorityMode"))
		SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", sti(chr.PriorityMode));
	else
		SendMessage(chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 1);
}

//Заблокировать текущий режим (!!! сбрасывается при смене шаблона !!!)
void LAi_LockFightMode(aref chr, bool isLockFightMode)
{
	// Попытка заставить LAi_LockFightMode(pchar, true) работать нормально
	// FightMode разблокируется вручную вызовом LAi_LockFightMode(pchar, false)
	// Или принудительно с вызовом LAi_SetFightMode(pchar, true)
	// Для LAI_TYPE_PLAYER правило - "сбрасывается при смене шаблона" - неактуально, и не должно так работать
	if (IsMainCharacter(chr))
	{
		if (isLockFightMode)
		{
	    	TEV.LockFightMode = true;
		}
		else
		{
		    DeleteAttribute(&TEV, "LockFightMode");
		}
	}
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "LockFightMode", isLockFightMode);
}

//Получить режим боя (2 - мушкетный у универсалов, 1 - сабля у универсалов и просто боевой у остальных, 0 - мирный)
int LAi_CheckFightMode(aref chr)
{
	return SendMessage(&chr, "ls", MSG_CHARACTER_EX_MSG, "CheckFightMode");
}

//HardCoffee проверка на безоружность -->
bool LAi_CheckForWeapon(ref rNPChar)
{
	if (Pchar.questTemp.CapBloodLine == true) //Скриптовый детект для вооружённого блада
	{
		if (Pchar.questTemp.CapBUnarmed == true && chrDisableReloadToLocation == true
			&& GetCharacterIndex("SolderTakeBlades") >= 0) return true;
	}
    if (!LAi_CheckFightMode(pchar)) return false;
	if (sti(rNPChar.nation) == PIRATE && TEV.checkPirateNoBlade > 0) return false; //пиратов можно посылать
	if (LAi_IsUnarmed(pchar)) return false; //не докапываться до безоружных
	if (LAi_IsOurCitizen(rNPChar)) return false; //не докапываться в городе гг
	return true;
}

bool LAi_IsUnarmed(ref rChr)
{
    aref arEquip;

	if (CharUseMusket(rChr)) return false;

	makearef(arEquip, rChr.equip);
	int q = GetAttributesNum(arEquip);
	string sTemp = "";
	for (int i = 0; i < q; i++)
	{
		sTemp = GetAttributeValue(GetAttributeN(arEquip, i));
		if ("unarmed" == sTemp) return true;
	}
	return false;
}

bool LAi_IsOurCitizen(ref rNPChar) //является ли нпс жителем колонии гг
{
    // ~!~ LAI_GROUP_PLAYER_OWN ?
	if (!CheckAttribute(rNPChar, "City")) return false;
	ref rColony;
	int iTemp = FindColony(rNPChar.City);
	if (iTemp < 0) return false;
	rColony = GetColonyByIndex(iTemp);
	if (!CheckAttribute(rColony, "HeroOwn")) return false;
	if (sti(rColony.HeroOwn) > 0) return true;
	return false;
}
// проверка на безоружность <--

//------------------------------------------------------------------------------------------
//Weapons
//------------------------------------------------------------------------------------------

//Получить относительный заряд пистолета
float LAi_GetCharacterRelCharge(aref chr, string sType)
{
	if(CheckAttribute(chr, "chr_ai." + sType + ".charge"))
	{
		if(CheckAttribute(chr, "chr_ai." + sType + ".chargeprc"))
		{
			if(sti(chr.chr_ai.(sType).chargeprc))
			{
				if(!CheckAttribute(chr, "chr_ai." + sType + ".charge_max")) return 0.0;
				float charge = stf(chr.chr_ai.(sType).charge);
				float chargemax = stf(chr.chr_ai.(sType).charge_max);
				if(chargemax <= 0) return 0.0;
				if(charge >= chargemax) charge = chargemax;
				charge = charge/chargemax;
				Restrictor(&charge, 0.0, 1.0);
				return charge;
			}
            else return 1.0;
		}
        else chr.chr_ai.(sType).chargeprc = "1";
	}
	return 0.0;
}

//Получить максимальное количество зарядов пистолета
int LAi_GetCharacterChargeQuant(aref chr, string sType)
{
	if(CheckAttribute(chr, "chr_ai." + sType + ".charge_max"))
	{
		return sti(chr.chr_ai.(sType).charge_max);
	}
	return 0;
}

//Получить текущее количество зарядов пистолета
int LAi_GetCharacterChargeCur(aref chr, string sType)
{
	if(CheckAttribute(chr, "chr_ai."+sType+".charge"))
	{
		float charge = stf(chr.chr_ai.(sType).charge);
		return MakeInt(charge);
	}
	return 0;
}

//Установить количество зарядов
void LAi_GunSetChargeQuant(aref chr, string sType, int quant)
{
	Restrictor(&quant, 0, 5);
	chr.chr_ai.(sType).charge_max = quant;
	
	int iCharge = iGetPistolChargeNum(chr, sType, quant);
	chr.chr_ai.(sType).charge = iCharge;
	
	chr.chr_ai.(sType).chargeprc = "1";
}

void LAi_SetCharacterBulletType(ref rChar, string sBullet)
{
	switch (sBullet)
	{
        case "petard":  TakeNItems(rChar, sBullet, 5 + rand(5)); break;
        case "grenade": TakeNItems(rChar, sBullet, 5 + rand(5)); break;
        case "harpoon": TakeNItems(rChar, sBullet, 5 + rand(5)); break;
        case "bullet":  TakeNItems(rChar, sBullet, 30 + rand(20)); break;
        case "cartridge": TakeNItems(rChar, sBullet, 10 + rand(10));  break;
        case "grapeshot": TakeNItems(rChar, sBullet, 10 + rand(5));   break;
        case "bullet_colt": TakeNItems(rChar, sBullet, 10 + rand(5)); break;
        case "cartridge_colt": TakeNItems(rChar, sBullet, 5 + rand(5)); break;
	}
}

// ugeen --> получим тип пуль на одетом огнестрельном оружии
string LAi_GetCharacterBulletType(ref rChar, string sType)
{
	string sBulletType = "";	
	string sGun = GetCharacterEquipByGroup(rChar, sType);

	if (sGun != "" && CheckAttribute(rChar, "chr_ai." + sType + ".bullet"))
	{
        sBulletType = rChar.chr_ai.(sType).bullet;
	}

	return sBulletType;
}

bool IsBulletGrape(string sBullet)
{
	if(sBullet == "grapeshot" || sBullet == "GunEchin" || sBullet == "grapeshot_double")
		return true;
	return false;
}

// ugeen --> получим тип пороха на одетом огнестрельном оружии и известном типе пуль
string LAi_GetCharacterGunpowderType(ref rChar, string sType)
{
	string sGunpowderType = "";		
	string sGun = GetCharacterEquipByGroup(rChar, sType);

    if (sGun == "") return "";
	if (CheckAttribute(rChar, "chr_ai." + sType + ".gunpowder")) sGunpowderType = rChar.chr_ai.(sType).gunpowder;
    else sGunpowderType = LAi_GetAmmoGunpowderType(LAi_GetCharacterBulletType(rChar, sType));

	return sGunpowderType;
}

string LAi_GetAmmoGunpowderType(string sAmmo)
{
	if (StrHasStr(sAmmo, "bullet,grapeshot,harpoon", 1))
		return "GunPowder";			// > пуле, картечи и гарпуну нужен гранулированный порох

	if (sAmmo == "bullet_colt")
		return "GunPowder_colt";	// > револьверной пуле нужен револьверный порох

	if (sAmmo == "cartridge_colt")
		return "GunCap_colt";		// > картриджу для револьвера требуются капсюли

	return "";						// > всему остальному более ничего не нужно
}

string LAi_SetCharacterDefaultBulletType(ref rChar, string sType)
{
	int i, iNum, n;
	bool isBulletSet = false;
	ref rItm;
	string sAttr, sChargeType, sBulletType = "";
	string sGun = GetCharacterEquipByGroup(rChar, sType);

	if (sGun != "" && FindItem(sGun) >= 0)
	{
		rItm = ItemsFromID(sGun);
		sChargeType = rItm.chargetype;
		sAttr = sChargeType;
		iNum = KZ|Symbol(sChargeType, ",");

		if (CheckAttribute(rChar, "chr_ai." + sType + ".bullet"))
		{
			for (i = 0; i <= iNum; i++)
			{
				if (iNum > 0)
					sAttr = GetSubStr(sChargeType, ",", i);
				
				if (sAttr != "" && rItm.type.(sAttr).bullet == rChar.chr_ai.(sType).bullet)
				{
					sBulletType = rItm.type.(sAttr).bullet;
					isBulletSet = LAi_SetCharacterUseBullet(rChar, sType, sBulletType);
					break;
				}
			}
		}

		if (sBulletType == "")
		{
			for (i = 0; i <= iNum; i++)
			{
				if (iNum > 0)
					sAttr = GetSubStr(sChargeType, ",", i);
				
				if (sAttr != "" && sti(rItm.type.(sAttr).Default) > 0)
				{
					sBulletType = rItm.type.(sAttr).bullet;
					isBulletSet = LAi_SetCharacterUseBullet(rChar, sType, sBulletType);
					break;
				}
			}
		}

		if (isBulletSet)
			rChar.chr_ai.(sType).bullet = sBulletType;
		else
			trace("WARNING > LAi_SetCharacterDefaultBulletType > can't set default bullet for character id " + rChar.id);
	}

	return sBulletType;
}

bool LAi_SetCharacterUseBullet(ref rChar, string sType, string sBullet)
{
	int i, iNum;
	ref rItm;
	string sAttr, sChargeType, sBulletType;
	string sGun = GetCharacterEquipByGroup(rChar, sType);

	if (sGun != "" && FindItem(sGun) >= 0) 
	{
		rItm = ItemsFromID(sGun);
		sChargeType = rItm.chargetype;
		sAttr = sChargeType;
		iNum = KZ|Symbol(sChargeType, ",");

		for (i = 0; i <= iNum; i++)
		{
			if (iNum > 0) sAttr = GetSubStr(sChargeType, ",", i);
			sBulletType = rItm.type.(sAttr).bullet;
			if (sAttr != "" && sBulletType == sBullet)
			{
				rChar.chr_ai.(sType).sGun			= sGun;
				rChar.chr_ai.(sType).bulletType		= sAttr;
				rChar.chr_ai.(sType).bulletNum 		= iNum;
				rChar.chr_ai.(sType).bullet 		= sBulletType;
				rChar.chr_ai.(sType).gunpowder		= rItm.type.(sAttr).gunpowder;
				
				rChar.chr_ai.(sType).DmgMin_NC		= rItm.type.(sAttr).DmgMin_NC;
				rChar.chr_ai.(sType).DmgMax_NC 		= rItm.type.(sAttr).DmgMax_NC;
                rChar.chr_ai.(sType).DmgGunMin      = rItm.type.(sAttr).DmgMin_NC;
                rChar.chr_ai.(sType).DmgGunMax      = rItm.type.(sAttr).DmgMax_NC;
				rChar.chr_ai.(sType).DmgMin_C 		= rItm.type.(sAttr).DmgMin_C;
				rChar.chr_ai.(sType).DmgMax_C 		= rItm.type.(sAttr).DmgMax_C;
				rChar.chr_ai.(sType).EnergyP_NC 	= rItm.type.(sAttr).EnergyP_NC;
				rChar.chr_ai.(sType).EnergyP_C 		= rItm.type.(sAttr).EnergyP_C;
				rChar.chr_ai.(sType).Stun_NC 		= rItm.type.(sAttr).Stun_NC;
				rChar.chr_ai.(sType).Stun_C			= rItm.type.(sAttr).Stun_C;
				rChar.chr_ai.(sType).AOEDamage		= rItm.type.(sAttr).AOEDamage;
				rChar.chr_ai.(sType).MisFire		= rItm.type.(sAttr).misfire;
				rChar.chr_ai.(sType).SelfDamage		= rItm.type.(sAttr).SelfDamage;
				rChar.chr_ai.(sType).Explosion		= rItm.type.(sAttr).Explosion;

                float fAccuracy = rItm.type.(sAttr).Accuracy;
                float fChargeSpeed = rItm.type.(sAttr).ChargeSpeed; 
                LAi_GunSetAccuracy(rChar, sType, fAccuracy * 0.01);
                LAi_GunSetChargeQuant(rChar, sType, sti(rItm.chargeQ));
                LAi_GunSetChargeSpeed(rChar, sType, 1.0 / fChargeSpeed);
				rChar.chr_ai.(sType).charge_pSkill = LAi_GunReloadSpeed(rChar, sType);

				return true;
			}
		}
	}

	return false;
}

float LAi_GetGunChargeProgress(aref chr)
{
	float charge;
	if(GetCharacterEquipByGroup(chr, GUN_ITEM_TYPE) == "") return 0.0;
	if(CheckAttribute(chr, "chr_ai.gun.charge"))
	{
		charge = chr.chr_ai.gun.charge;
		if(charge > 1.0) charge -= MakeInt(chr.chr_ai.gun.charge);
		if(CheckAttribute(chr, "chr_ai.gun.charge_max") && MakeInt(chr.chr_ai.gun.charge_max) == MakeInt(chr.chr_ai.gun.charge))
			charge = 0.0;
	}
	else return 0.0;

	return charge;
}

float LAi_GetMusketChargeProgress(aref chr)
{
	float charge;
	if(GetCharacterEquipByGroup(chr, MUSKET_ITEM_TYPE) == "") return 0.0;
	if(CheckAttribute(chr, "chr_ai.musket.charge"))
	{
		charge = chr.chr_ai.musket.charge;
		if(charge > 1.0) charge -= MakeInt(chr.chr_ai.musket.charge);
		if(CheckAttribute(chr, "chr_ai.musket.charge_max") && MakeInt(chr.chr_ai.musket.charge_max) == MakeInt(chr.chr_ai.musket.charge))
			charge = 0.0;
	}
	else return 0.0;

	return charge;
}

float LAi_GetPotionProgress(aref chr)
{
	float fcur, fmax;
	if(CheckAttribute(chr, "chr_ai.usedbottlemax"))
	{
		fmax = stf(chr.chr_ai.usedbottlemax);
		if(CheckAttribute(chr, "chr_ai.hp_bottle"))
		{
			fcur = stf(chr.chr_ai.hp_bottle);
		}
		else return 1.0;

		return 1.0 - fcur/fmax;
	}
	return 1.0;
}

// Warship. Методы по зарядке пистоля -->
// Ugeen --> переработка с учетом нескольких типов пуль и пороха на одетом огнестреле
int iGetMinPistolChargeNum(ref rChar, string sType) // Чего меньше, пороха или пуль?
{
	string sBulletType = LAi_GetCharacterBulletType(rChar, sType);              // узнаем тип пуль
	int iBulletQty = GetCharacterItem(rChar, sBulletType);   					// считаем кол-во пуль
	string sGunPowderType = LAi_GetCharacterGunpowderType(rChar, sType);        // тип пороха
	if(sGunPowderType != "")
	{
		int iGunPowderQty = GetCharacterItem(rChar, sGunPowderType);            // кол-во пороха		
		int iChargeQty = func_min(iBulletQty, iGunPowderQty);                   // Узнаем, чего меньше
		return iChargeQty;
	}		
	return iBulletQty;
}

int iGetPistolChargeNum(ref rChar, string sType, int iQuant) // Скока можем зарядить
{
	int iChargeQty = iGetMinPistolChargeNum(rChar, sType);

	if(iChargeQty == 0) return 0;
	if(iChargeQty >= iQuant) return iQuant;
	else return iChargeQty;
}
// <-- Методы по зарядке пистоля

//Разрядить пистолет
void LAi_GunSetUnload(aref chr, string sType)
{
	chr.chr_ai.(sType).charge = "0";
	chr.chr_ai.(sType).chargeprc = "1";
}

//Установить скорость заряда пистолета
void LAi_GunSetChargeSpeed(aref chr, string sType, float speed)
{
	Restrictor(&speed, 0.0, 5.0);
	chr.chr_ai.(sType).charge_dlt = speed;
    chr.chr_ai.(sType).chargespeed = speed; // ??
}

//Установить вероятность попадания на максимальной дальности стрельбы
void LAi_GunSetAccuracy(aref chr, string sType, float accuracy)
{
	Restrictor(&accuracy, 0.0, 1.0);
	chr.chr_ai.(sType).accuracy = accuracy;
}

// тип сабли boal
void LAi_BladeFencingType(aref chr, string FencingType)
{
	chr.chr_ai.FencingType = FencingType;
}

string LAi_GetBladeFencingType(aref chr)
{
    if(CheckAttribute(chr, "chr_ai.FencingType"))
	{
        return chr.chr_ai.FencingType;
    }
    return SKILL_FENCING;
}

void LAi_BladeEnergyType(aref chr, float fEnergyType)
{
	chr.chr_ai.EnergyType = fEnergyType;
}

float LAi_GetBladeEnergyType(aref chr)
{
    if (CheckAttribute(chr, "chr_ai.EnergyType"))
	{
        return stf(chr.chr_ai.EnergyType);
    }
    return 1.0;
}

// Имеется ли в руке клинок с указанным id
bool LAi_HasCharacterActiveBlade(aref chr, string bladeId)
{
	// В руке мушкет
	if (CheckAttribute(chr, "model.animation") && HasStr(chr.model.animation, "mushketer"))
	{
		return false;
	}
	if (CheckAttribute(chr, "equip.blade") && StrStartsWith(chr.equip.blade, bladeId))
	{
		return true;
	}
		
	return false;
}

//------------------------------------------------------------------------------------------
//Internal
//------------------------------------------------------------------------------------------

float SprintEnergyCost = 3.0;

//Процессируем всех загруженных персонажей
void LAi_AllCharactersUpdate(float dltTime)
{
	for(int i = 0; i < LAi_numloginedcharacters; i++)
	{
		int idx = LAi_loginedcharacters[i];
		if(idx >= 0)
		{
			//Персонаж
			aref chr_ai;
			makearef(chr_ai, Characters[idx].chr_ai);
			ref chr = &Characters[idx];
			if(LAi_IsDead(chr)) continue;
			//Восcтановление жизни
			float dlthp = LAI_DEFAULT_DLTHP;
			if(CheckAttribute(chr_ai, "hp_dlt")) dlthp = stf(chr_ai.hp_dlt);
			float hp = stf(chr_ai.hp) + dlthp*dltTime;
			float oldhp = hp;
			if(CheckAttribute(chr_ai, "hp_bottle"))
			{
				float bottle = stf(chr_ai.hp_bottle);
				if(bottle > 0)
				{
					//Скорость высасывания из бутылки
					float bottledlthp = LAI_DEFAULT_DLTBLTHP;
					if(CheckAttribute(chr_ai, "hp_dlt_bottle"))
					{
						bottledlthp = stf(chr_ai.hp_dlt_bottle);
					}
					//Количество вытянутых хп за текущий период времени
					bottledlthp = bottledlthp*dltTime;				
					if(bottledlthp > bottle)
					{
						bottledlthp = bottle;
					}
					bottle = bottle - bottledlthp;
					hp = hp + bottledlthp;
					chr_ai.hp_bottle = bottle;
				}else{
					//Нет больше бутылки
					DeleteAttribute(chr_ai, "hp_bottle");
					DeleteAttribute(chr_ai, "hp_dlt_bottle");
					if(idx==GetMainCharacterIndex())
						DeleteAttribute(chr, "chr_ai.usedbottlemax");
				}
			}
			if(CheckAttribute(chr_ai, "poison"))
			{
				chr_ai.poison = stf(chr_ai.poison) - dltTime;
				if(stf(chr_ai.poison) <= 0.0)
				{
					DeleteAttribute(chr_ai, "poison");
				}else{
					hp = hp - dltTime*2.0;
					if (!CheckAttribute(chr, "poison.hp") || hp < sti(chr.poison.hp)-1.0)
					{
						chr.poison.hp = hp;
						SendMessage(chr, "lfff", MSG_CHARACTER_VIEWDAMAGE, hp, MakeFloat(MakeInt(chr.chr_ai.hp)), MakeFloat(MakeInt(chr.chr_ai.hp_max)));
					}
				}
			}
			//navy --> время действия бутылки
			if(CheckAttribute(chr_ai, "drunk"))
				LAi_DawnAlcoholState(chr, sti(chr_ai.drunk) - 1);
			//<--
			if(LAi_IsImmortal(chr))
			{
				if(hp < oldhp) hp = oldhp;
			}
			float maxhp = stf(chr_ai.hp_max);
			if(hp > maxhp)
			{
				hp = maxhp;
				DeleteAttribute(chr_ai, "bottle");
			}
			chr_ai.hp = hp;
			//Проверка квеста на hp
			LAi_ProcessCheckMinHP(chr);
			//Проверка на смерть
			LAi_CheckKillCharacter(chr);
			//Проверка на поднятие тревоги
			LAi_ProcessCheckAlarm(chr);

//--> Восстановление зарядов огнестрельного оружия
			float charge, dltcharge;
			float ChargeMax = 0.0;
			bool bMus = CharUseMusket(chr);
			bool bPeace = !LAi_IsFightMode(chr);
			bool bAiming = false;

			if (idx == GetMainCharacterIndex())
			{
				string sAimingStep;
				SendMessage(pchar, "lse", MSG_CHARACTER_EX_MSG, "GetAimingStep", &sAimingStep);
				if(sAimingStep != "none")
					bAiming = true;
				if(CheckAttribute(chr_ai, "kill_timer"))
				{
					float killTimer = stf(chr_ai.kill_timer);
					killTimer -= dltTime;
					if(killTimer <= 0.0)
						DeleteAttribute(chr_ai, "kill_timer");
					else
						chr_ai.kill_timer = killTimer;
				}
			}

			if (CheckAttribute(chr_ai, "getheadshot"))
			{
				float headshotCD = stf(chr_ai.getheadshot);
				headshotCD -= dltTime;
				if(headshotCD <= 0.0)
					DeleteAttribute(chr_ai, "getheadshot");
				else
					chr_ai.getheadshot = headshotCD;
			}

			if (!bAiming)
			{
                // Пистолет:
                // Персонаж не держит в руках мушкет во время боя, при этом либо дозарядка разрешена, либо оружие в ножнах
				if (!and(bMus, LAi_grp_alarmactive) && or(bRechargePistolOnLine, bPeace))
				{
					if(CheckAttribute(chr_ai, "gun.charge_max")) ChargeMax = stf(chr_ai.gun.charge_max);
					if(ChargeMax > 0.0)
					{
						if(sti(chr_ai.gun.chargeprc))
						{
							charge = stf(chr_ai.gun.charge);
							if((iGetMinPistolChargeNum(chr, "gun") - charge) > 0)
							{
								if(!CheckAttribute(chr_ai, "gun.charge_pSkill"))
								{	//Скорость зарядки
									chr_ai.gun.charge_pSkill = LAi_GunReloadSpeed(chr, "gun");
								}

								dltcharge = stf(chr_ai.gun.charge_pSkill);

								//Подзаряжаем пистолет
								charge = charge + dltcharge*dltTime;
								if(charge >= ChargeMax)
								{
									charge = ChargeMax;
									chr_ai.gun.chargeprc = "0";
									DeleteAttribute(chr_ai, "gun.charge_pSkill");

									if (Characters[idx].index == GetMainCharacterIndex() && LAi_IsFightMode(pchar))
									{
										PlaySound("Reload");
									}
								}
								chr_ai.gun.charge = charge;
							}
						}
					}
					else chr_ai.gun.charge = "0";
				}

                // Мушкет:
                // Персонаж либо держит мушкет в руках, либо вне боя и оружие в ножнах
				if (and(bPeace, !LAi_grp_alarmactive) || bMus)
				{
					ChargeMax = 0.0;
					if(CheckAttribute(chr_ai, "musket.charge_max")) ChargeMax = stf(chr_ai.musket.charge_max);
					if(ChargeMax > 0.0)
					{
						if(sti(chr_ai.musket.chargeprc))
						{
							charge = stf(chr_ai.musket.charge);
							if((iGetMinPistolChargeNum(chr, "musket") - charge) > 0)
							{
								if(!CheckAttribute(chr_ai, "musket.charge_pSkill"))
								{	//Скорость зарядки
									chr_ai.musket.charge_pSkill = LAi_GunReloadSpeed(chr, "musket");
								}

								dltcharge = stf(chr_ai.musket.charge_pSkill);

								//Подзаряжаем мушкет
								charge = charge + dltcharge*dltTime;
								if(charge >= ChargeMax)
								{
									charge = ChargeMax;
									chr_ai.musket.chargeprc = "0";
									DeleteAttribute(chr_ai, "musket.charge_pSkill");

									if (Characters[idx].index == GetMainCharacterIndex() && LAi_IsFightMode(pchar))
									{
										PlaySound("People Fight\reload1.wav");
									}
								}
								chr_ai.musket.charge = charge;
							}
						}
					}
					else chr_ai.musket.charge = "0";
				}
			}
//<-- Восстановление зарядов огнестрельного оружия

			// Восстановление энергии
			if(CheckAttribute(chr_ai, "energy"))
			{
				float cEnergy = stf(chr_ai.energy);
				float mEnergy = LAi_GetCharacterMaxEnergy(chr);
				if(idx == GetMainCharacterIndex() && SendMessage(pchar, "ls", MSG_CHARACTER_EX_MSG, "IsSprint") == 1 && LAi_group_IsActivePlayerAlarm())
				{
					cEnergy -= dltTime * SprintEnergyCost;
					if(cEnergy < 0.0)
						SendMessage(pchar, "ls", MSG_CHARACTER_EX_MSG, "StopSprint");
				}
				else
					cEnergy = Lai_UpdateEnergyPerDltTime(chr, stf(chr_ai.energy), dltTime);
				if(cEnergy < 0.0)
					cEnergy = 0.0;
				if(cEnergy > mEnergy)
				{
					DeleteAttribute(chr_ai, "ep_bottle");
					DeleteAttribute(chr_ai, "ep_dlt_bottle");
					cEnergy = mEnergy;
				}				
				if (CheckAttribute(chr_ai, "ep_bottle") && cEnergy < mEnergy)
				{
					float dltep = LAI_DEFAULT_DLTEP;
					
					if (CheckAttribute(chr_ai, "ep_dlt"))
						dltep = stf(chr_ai.ep_dlt);
					
					cEnergy = stf(chr_ai.energy) + dltep*dltTime;
					
					float ebottle = stf(chr_ai.ep_bottle);
					if (ebottle > 0 || cEnergy >= mEnergy)
					{
						//Скорость высасывания из бутылки
						float bottledltep = LAI_DEFAULT_DLTBLTEP;
						if (CheckAttribute(chr_ai, "ep_dlt_bottle"))
							bottledltep = stf(chr_ai.ep_dlt_bottle);
						
						//Количество вытянутых ехп за текущий период времени
						bottledltep = bottledltep*dltTime;
						if (bottledltep > ebottle)
							bottledltep = ebottle;
						
						ebottle = ebottle - bottledltep;
						cEnergy = cEnergy + bottledltep;
						chr_ai.ep_bottle = ebottle;
						chr_ai.energy = chr_ai.energy + cEnergy;
					}
					else
					{
						//Нет больше бутылки
						DeleteAttribute(chr_ai, "ep_bottle");
						DeleteAttribute(chr_ai, "ep_dlt_bottle");
					}
				}
				else
				{
					//Нет больше бутылки
					DeleteAttribute(chr_ai, "ep_bottle");
					DeleteAttribute(chr_ai, "ep_dlt_bottle");
				}
				
				chr_ai.energy = cEnergy;
			}
		}
	}
}

void LAi_ProcessCheckMinHP(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.hpchecker"))
	{
		float minhp = stf(chr.chr_ai.hpchecker);
		float hp = stf(chr.chr_ai.hp);
		if(hp < minhp)
		{
			if(sti(chr.chr_ai.hpchecker.immortal))
			{
				LAi_SetImmortal(chr, true);
				chr.chr_ai.hp = minhp;
			}
			if(chr.chr_ai.hpchecker.quest != "")
			{
				LAi_QuestDelay(chr.chr_ai.hpchecker.quest, 0.0);
			}
			LAi_RemoveCheckMinHP(chr);
		}
	}
}

void LAi_CharacterSaveAy(aref chr)
{
	float ay = 0.0;
	if(GetCharacterAy(chr, &ay) == false) ay = 0.0;
	chr.chr_ai.type.ay = ay;	
}

void LAi_CharacterRestoreAy(aref chr)
{
	if(CheckAttribute(chr, "chr_ai.type.ay"))
	{
		float ay = stf(chr.chr_ai.type.ay);
		aref type;
		makearef(type, chr.chr_ai.type);
		DeleteAttribute(type, "ay");
		CharacterTurnAy(chr, ay);
	}
}

// KZ > получить атрибут заряженного типа снаряда у огнестрела
string GetGunAmmoAttr(ref rGun, string sBullet, string sAttr)
{
	if (CheckAttribute(rGun, "type." + sBullet + "." + sAttr))
		return rGun.type.(sBullet).(sAttr);

	return "";
}

// KZ > получить строку всех доступных типов снарядов
string GetGunAmmoType(string sGun)
{
	if (FindItem(sGun) < 0)
		return "";

	ref rGun = ItemsFromID(sGun);
    return rGun.chargetype;
}

// KZ > подсчитать кол-во доступных зарядов у огнестрела sGun на основе всех имеющихся в инвентаре rChar снарядов под него
int GetGunCharges(ref rChar, string sGun)
{
	ref rGun = ItemsFromID(sGun);

	string sBullet, sPowder, sCharge = rGun.chargetype;
	int i, n, iNum = KZ|Symbol(sCharge, ",");
	int iResult = 0;

	for (i = 0; i <= iNum; i++)
	{
		if (iNum > 0)
			sBullet = GetSubStr(sCharge, ",", i);

		if (sBullet != "")
		{
			n = GetCharacterItem(rChar, sBullet);
			
			if (n > 0)
			{
				sPowder = LAi_GetAmmoGunpowderType(sBullet);
				
				if (sPowder != "")
					n = func_min(n, GetCharacterItem(rChar, sPowder));

				iResult += n;
			}
		}
	}

	return iResult;
}

//HardCoffee реакция нпс на поднятие тревоги на локации -->
void LAi_SetCheckAlarm(ref rChr, string sFunc)
{
    rChr.chr_ai.alarmFunc = sFunc;
}

void LAi_ProcessCheckAlarm(ref rChr)
{
	if (!CheckAttribute(rChr, "chr_ai.alarmFunc")) return;

	if (LAi_grp_playeralarm > 0)
	{
		string sFunc = rChr.chr_ai.alarmFunc;
		if (sFunc != "" && sFunc != "error") call sFunc();

		DeleteAttribute(rChr, "chr_ai.alarmFunc");
	}
}

void LAi_RemoveCheckAlarm(ref rChr)
{
	DeleteAttribute(rChr, "chr_ai.alarmFunc");
}
// <-- реакция нпс на поднятие тревоги на локации

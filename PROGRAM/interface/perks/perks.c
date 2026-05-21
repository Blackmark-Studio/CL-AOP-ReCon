
#event_handler("evntChrPerkDelay","procChrPerkDelay");

object ChrPerksList;

extern void extrnInitPerks();

void InitPerks()
{
	if( LoadSegment("interface\perks\perks_init.c") )
	{
		extrnInitPerks();
		UnloadSegment("interface\perks\perks_init.c");
	}
}

bool CheckCharacterPerk(ref chref, string perkName)
{
	if( CheckAttribute(chref,"perks.list."+perkName) ) return true;
	return false;
}

bool SetCharacterPerk(ref chref, string perkName)
{
	bool bRefresh = false; // надо ли обновить интерфейс, когда, например, меняются HP
	if(CheckCharacterPerk(chref, perkName) && ChrPerksList.list.(perkName).BaseType == "trait") return false;
	
	chref.perks.list.(perkName) = true;
	
	switch (perkName)
	{
		case "PersonalCare":
			LAi_SetHP(chref, LAi_GetCharacterHP(chref), LAi_GetCharacterMaxHP(chref));
		break;
		
		case "HPPlus":
			LAi_SetHP(chref, LAi_GetCharacterMaxHP(chref), LAi_GetCharacterMaxHP(chref));
			bRefresh = true;
		break;
		
		case "EnergyPlus":
			SetEnergyToCharacter(chref);
			chref.chr_ai.energy = chref.chr_ai.energyMax;
			bRefresh = true;	
		break;
		
		case "Grus":
			bRefresh = true;
		break;
		
		case "WildCaribbean":	// EvgAnat - дикие Карибы, получение перка
			SetWildCaribbean();
		break;
	}
	
	bool bOk = IsEntity(&worldMap) || IsEntity(pchar); //отключение при входе в игру
	if(bOk && ChrPerksList.list.(perkName).BaseType == "trait")
	{
		if(CheckAttribute(&ChrPerksList, "list." + perkName + ".FemName") && chref.sex == "woman") perkName += "Fem";
		if(IsMainCharacter(chref))
			Log_SetStringToLog(XI_ConvertString("Got_the_perk") + GetConvertStr(perkName, "AbilityDescribe.txt"));
		else
		{
			if(IsCompanion(chref) || isOfficerInShip(chref, true))
				Log_SetStringToLog(GetFullNameTitulForm(chref) + NPCharSexPhrase(chref,XI_ConvertString("NPC_got_the_perk"),XI_ConvertString("NPC_got_the_perk_woman")) + GetConvertStr(perkName, "AbilityDescribe.txt"));
		}
		
		if(IsMainCharacter(chref) || IsCompanion(chref) || isOfficerInShip(chref, true))
		{
			if (CheckAttribute(&ChrPerksList, "list." + perkName) && !HasSubStr(ChrPerksList.list.(perkName).Parameters, "negative") && perkName != "GhostsGift")
				 PlayStereoSound("interface\new_level.wav"); //TODO: отдельный другой звук!
			else PlayStereoSound("interface\sobitie_na_karte_001.wav");
		}
		return bRefresh;
	}
	
	//Если всё набрано и доступных перков больше нет, то выдаём атрибут для интерфейса
	if(ChrPerksList.list.(perkName).BaseType != "trait")
	{
		if(HaveAllPerks(chref, "self")) chref.AllSelf = "";
		if(HaveAllPerks(chref, "ship")) chref.AllShip = "";
	}
	return bRefresh;
}

void DeleteTrait(ref chref, string traitName)
{
	if(!CheckCharacterPerk(chref, traitName)) return;
	DeleteAttribute(chref, "perks.list." + traitName);
	if(IsMainCharacter(chref))
		Log_SetStringToLog(XI_ConvertString("Lost_the_perk") + GetConvertStr(traitName, "AbilityDescribe.txt"));
	else if(IsCompanion(chref) || isOfficerInShip(chref, true))
		Log_SetStringToLog(GetFullNameTitulForm(chref) + NPCharSexPhrase(chref,XI_ConvertString("NPC_lost_the_perk"),XI_ConvertString("NPC_lost_the_perk_woman")) + GetConvertStr(traitName, "AbilityDescribe.txt"));
	PlayStereoSound("interface\noviy_urov_001.wav");
}

void ActivateCharacterPerk(ref chref, string perkName)
{
	if( !CheckAttribute(&ChrPerksList,"list."+perkName) )
	{
		trace("Invalid perk name - " + perkName);
		return;
	}

	int timeDelay = 0;
	int timeDuration = 0;

	if( CheckAttribute(&ChrPerksList,"list."+perkName+".TimeDuration") )
	{	timeDelay = sti(ChrPerksList.list.(perkName).TimeDuration);
		timeDuration = timeDelay;
	}
	if( CheckAttribute(&ChrPerksList,"list."+perkName+".TimeDelay") )
	{	timeDelay = sti(ChrPerksList.list.(perkName).TimeDelay);
		if(timeDuration<=0)	{timeDuration=timeDelay;}
	}
    // boal fix
    // иначе после применения давался ГГ
	
    int cn;
    if (!CheckCharacterPerk(chref, perkName))
    {

        cn = GetOfficersPerkUsingIdx(chref, perkName);
        if (cn != -1)
        chref = GetCharacter(cn);
    }
    // <--
	chref.perks.list.(perkName).delay = timeDelay;
	chref.perks.list.(perkName).active = timeDuration;

	//if(sti(chref.index) == nMainCharacterIndex)
	if (sti(chref.index) == nMainCharacterIndex || isOfficerInShip(chref, false)) // наследие перка от офа boal 30.06.06
	{
		AddPerkToActiveList(perkName);
	}

	AddPerkEffect(chref, perkName);

	if (timeDelay > 0) PostEvent("evntChrPerkDelay", 100, "sl", perkName, sti(chref.index));
	Event("eSwitchPerks","l",sti(chref.index));
	// fix boal всегда для ГГ
	Event("eSwitchPerks","l", GetMainCharacterIndex());
}

void AddPerkEffect(ref chr, string sPerk)
{
	aref arRoot, arBase;
	makearef(arRoot, chr.perks.list);
	if (!CheckAttribute(arRoot, sPerk)) return false;
	makearef(arBase, ChrPerksList.list.(sPerk));
	
	float fTemp;
	
	switch (sPerk)
	{
		case "SecondWind":	// "Второе дыхание"
			fTemp = makefloat(GetCharEnergy(chr, 0) - GetCharEnergy(chr, 1)) * 0.5;	// > потраченная энергия / 2
			LAi_UseCustomBottle(chr, "energy", fTemp, "8.0", "");
		break;
	}
}

bool GetCharacterPerkUsing(ref chref, string perkName)
{   // можно ли пользовать умение (задержки нет)
	if( !CheckAttribute(chref,"perks.list."+perkName) ) return false;
	if( CheckAttribute(chref,"perks.list."+perkName+".delay") ) return false;
	return true;
}

bool GetOfficersPerkUsing(ref chref, string perkName, bool bOnline)
{ // boal препишем внутрянку под новых офов, че в к3 не было? не ведаю.
	string  sOfficerType, sFighter = "id";
	ref   offc;	   
	bool  ok = false; // boal fix 25.03.05 проверка на запрет
	bool  okDelay = true;
	int   cn;
	if (GetCharacterPerkUsing(chref, perkName)) {return true;} // босс отдельно
	if (!CheckAttribute(chref,"perks.list."+perkName) && CheckAttribute(chref, "Fellows"))  // у гг нет перка вообще, тогда смотрим офов, иначе выход
	{
		for(int i=1; i<=9; i++)
		{
			sOfficerType = GetOfficerTypeByNum(i);
			if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
			{
				if (i <= 6)
					cn = sti(chref.Fellows.Passengers.(sOfficerType));
				else
					cn = GetOfficersIndex(pchar, i - 6);

				if (cn<0) {continue;}
				offc = &Characters[cn];
				if (sOfficerType == "fighter" && bOnline && !IsEntity(offc)) continue;
				if (CheckAttribute(offc, "perks.list."+perkName) )          ok = true;
				if (CheckAttribute(offc, "perks.list."+perkName+".delay") ) okDelay = false;
				//if (GetCharacterPerkUsing(chref, perkName) return true;
			}
		}
	}
	if (HasSubStr(perkName, "Capellan") && CheckAttribute(chref, "questTemp.ShipCapellan.Yes")) //капеллан
	{
		offc = CharacterFromId(chref.questTemp.ShipCapellan.id);
		if (CheckAttribute(offc, "perks.list."+perkName)) ok = true;
		//if (CheckAttribute(offc, "perks.list."+perkName+".delay")) okDelay = false;
	}
	return (ok) && (okDelay);
}

// boal
int GetOfficersPerkUsingIdx(ref chref, string perkName)
{
	string  sOfficerType;
	int     cn;
	if (GetCharacterPerkUsing(chref, perkName)) {return sti(chref.index);} // босс отдельно
	for(int i=1; i<=6; i++)
	{
		sOfficerType = GetOfficerTypeByNum(i);
		if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
		{
			cn = sti(chref.Fellows.Passengers.(sOfficerType));
			if(cn<0) {continue;}
			if (GetCharacterPerkUsing(&Characters[cn], perkName) ) {return cn;}
		}
	}
	return -1;
}

bool IsCharacterPerkOn(ref chref, string perkName)
{
	aref arRoot, arBase;
	makearef(arRoot,chref.perks.list);
	if( !CheckAttribute(arRoot,perkName) ) return false;
	makearef(arBase,ChrPerksList.list.(perkName));
	if( CheckAttribute(arBase,"TimeDuration") || CheckAttribute(arBase,"TimeDelay") ) {
		return CheckAttribute(arRoot,perkName+".active");
	}
	return true;
}

void CharacterPerkOff(ref chref, string perkName)
{
	if (perkName == "Turn180")
	{
		chref.Tmp.SpeedRecall = 0; // чтоб манёвр применить
	}
	DeleteAttribute(chref,"perks.list."+perkName+".active");
	Event("eSwitchPerks","l",sti(chref.index));	 
	// fix boal всегда для ГГ
	Event("eSwitchPerks","l", GetMainCharacterIndex());
	if (sti(chref.index) == nMainCharacterIndex || isOfficerInShip(chref, false)) // наследие перка от офа boal 30.06.06
	{
		DelPerkFromActiveList(perkName);
	}
}

bool CheckOfficersPerk(ref chref, string perkName)
{ // активность перка в данный момент, для временных - режим активности, а не задержки
	if (!CheckAttribute(chref, "id")) return false;
	bool ret = CheckOfficersPerkWOSelf(chref, perkName);

	if (ret) return true;
	// самого НПС
	if(IsCharacterPerkOn(chref,perkName) == true)
	{
		return true;
	}
	return false;
}

bool CheckOfficersPerkWOSelf(ref chref, string perkName)
{
	int     iOfficer = -1;
	string  sOfficerType;
	if(chref.id == pchar.id)
	{
		// boal новая схема наследования. switch не наш метод
		if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType"))
		{
			sOfficerType = ChrPerksList.list.(perkName).OfficerType;
			iOfficer = sti(pchar.Fellows.Passengers.(sOfficerType));
		}
	}

	if(iOfficer != -1)
	{
		if(IsCharacterPerkOn(GetCharacter(iOfficer), perkName) == true )
		{
			return true;
		}
	}
	return false;
}
// нигде не юзан
bool CheckCompanionsPerk(ref chref, string perkName)
{
	int i,cn;
	for(i=0; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(chref,i);
		if(cn>=0)
		{	if( IsCharacterPerkOn(GetCharacter(cn),perkName) )	{return true;}
		}
	}
	return false; // fix by boal
}

void procChrPerkDelay()
{
	string perkName = GetEventData();
	int chrIdx = GetEventData();

	aref arPerk;
	makearef(arPerk,Characters[chrIdx].perks.list.(perkName));
	if( !CheckAttribute(arPerk,"delay") ) return;
	int delay = sti(arPerk.delay);
 	// фикс в каюте, палубе, абордаже
 	bool ok;
 	ok = (!bAbordageStarted) && (!bSeaReloadStarted);
 	if (ok || perkName == "Rush" || perkName == "SecondWind")
 	{
		delay--;
	}
	
	bool isOfficerPerk = false;
	bool isMainCharPerk = false;
	if (CheckAttribute(ChrPerksList, "list."+perkName+".OfficerType"))
	{
		string sOfficerType = ChrPerksList.list.(perkName).OfficerType;
		isOfficerPerk = sti(pchar.Fellows.Passengers.(sOfficerType)) == chrIdx;
	}
	isMainCharPerk = sti(Characters[chrIdx].index) == nMainCharacterIndex || isOfficerPerk;

	if( CheckAttribute(arPerk,"active") )
	{
		int iActive = sti(arPerk.active)-1;
		if( iActive>0 )	{arPerk.active = iActive;}
		else
		{
			CharacterPerkOff(GetCharacter(chrIdx),perkName);
		}
	}

	if( delay<=0 )
	{
		DeleteAttribute(&Characters[chrIdx],"perks.list."+perkName+".delay");
		DeleteAttribute(&Characters[chrIdx],"perks.list."+perkName+".active");
		PostEvent("evntPerkAgainUsable",1);
		if (isMainCharPerk)
		{
			DelPerkFromActiveList(perkName);
		}
	}
	else
	{
		Characters[chrIdx].perks.list.(perkName).delay = delay;
		PostEvent("evntChrPerkDelay",1000,"sl",perkName,chrIdx);
		if (isMainCharPerk)
		{
			bool isSeaLoaded = bSeaActive && !bAbordageStarted;
			bool bActive = false;
			if (perkName == "Rush" || perkName == "SecondWind" || isSeaLoaded)
			{
				if (CheckAttribute(arPerk,"active"))
				{
					bActive = true;
				    delay = sti(arPerk.active);
				}
				SetCooldownTextForActivePerkInList(perkName, delay, bActive);
			}
		}
	}
}

void EnableUsingAbility(ref chref,string perkName)
{
    // boal fix
    // иначе после применения давался ГГ
	int cn;
    if (!CheckCharacterPerk(chref, perkName))
    {

        cn = GetOfficersPerkUsingIdx(chref, perkName);
        if (cn != -1)
        chref = GetCharacter(cn);
    }
    // <--
    
	Event("evntChrPerkDelay","sl",perkName, sti(chref.index));
}

void PerkLoad(bool bReset)
{
//	int iRDTSC = RDTSC_B();
	string sPerk;
	aref arPerksRoot,arPerk;
	int i,j,n,tmpi;

	for(i=0; i<MAX_CHARACTERS; i++)
	{
		if(Characters[i].location == pchar.location)
		{
			makearef(arPerksRoot,Characters[i].perks.list);
			n = GetAttributesNum(arPerksRoot);
			for(j=0; j<n; j++)
			{
				arPerk = GetAttributeN(arPerksRoot,j);
				sPerk = GetAttributeName(arPerk);
				
				if( CheckAttribute(arPerk,"delay") )
				{
					if (bReset) // KZ > принудительный сброс активности и кулдауна перков, на всякий случай
					{
						DelPerkFromActiveList(sPerk);
						DeleteAttributeEx(arPerk, "active,delay");
						PostEvent("evntPerkAgainUsable", 1);
						continue;
					}
					
					tmpi = sti(arPerk.delay);
					if( tmpi>0 )
					{
						PostEvent("evntChrPerkDelay",1000,"sl",sPerk,i);
					}
				}
			}
		}
	}

//	trace("TIME!!! PerkLoad() = " + RDTSC_E(iRDTSC));
}
// boal под новые слоты -->
void ClearActiveChrPerks(ref chref)
{
	return; // KZ > функция херит кулдаун перков в море
	
	int i,cn;
    ref offc; // boal
    string  sOfficerType;	
    
    if (bAbordageStarted || bSeaReloadStarted) return;
	
	ClearActivePerks(chref); // босс отдельно
	if (CheckAttribute(chref, "Fellows.Passengers")) // не у всех есть
	{
		for (i=1; i<=6; i++)
		{
			sOfficerType = GetOfficerTypeByNum(i);
			cn = sti(chref.Fellows.Passengers.(sOfficerType));
			if(cn<0) {continue;}
			offc = &Characters[cn];
			ClearActivePerks(offc);
		}
	}
}

// > AlexBlade - Относится ли перк к 'морским' активным
bool IsSeaActivePerk(string perkName)
{
	aref arPerksRoot, arPerk;
	int i,n;
	
	makearef(arPerksRoot, ChrPerksList.list);
		
	n = GetAttributesNum(arPerksRoot);
	for (i=0; i<n; i++)
	{
		arPerk = GetAttributeN(arPerksRoot,i);
		if (GetAttributeName(arPerk) != perkName)
			continue;

		if (CheckAttribute(arPerk,"TimeDelay") && CheckAttribute(arPerk,"BaseType") && arPerk.BaseType == "ship")
        {
			return true;
		}
		
		return false;
	}
	
	return false;
}

// > AlexBlade - Относится ли перк к 'наземным' активным
bool IsLandActivePerk(string perkName) {
	return !IsSeaActivePerk(perkName);
}

void ClearActivePerks(ref offic)
{
	if (CheckAttribute(&TEV, "RefreshActiveSeaPerks"))
	{
		RefreshActiveSeaPerks(false);
		DeleteAttribute(&TEV, "RefreshActiveSeaPerks");
	}

	aref arPerksRoot, arPerk;
	makearef(arPerksRoot, offic.perks.list);
	
	int i, n = GetAttributesNum(arPerksRoot);
	string sPerk;
	
	for (i = 0; i < n; i++)
	{
		arPerk = GetAttributeN(arPerksRoot,i);
		sPerk = GetAttributeName(arPerk);
		
		if (and(IsLandActivePerk(sPerk), GetPos(1) != 2) || and(!IsLandActivePerk(sPerk), GetPos(1) == 2)) // KZ > сохраняем счётчики откатов морских перков при загрузке в море и наземных на суше
			continue;
		
		DeleteAttributeEx(arPerk, "active,delay");
	}
}

// был баг К3, этот перк не работал вовсе
void AcceptWindCatcherPerk(ref refCharacter)
{
    int  nShipType;
    ref  refBaseShip, refRealShip;

	nShipType = GetCharacterShipType(refCharacter);
	if (nShipType==SHIP_NOTUSED) return;

	refRealShip = GetRealShip(nShipType);
	refBaseShip = GetShipByType(sti(refRealShip.BaseType));
		
	if (CheckOfficersPerk(refCharacter, "WindCatcher"))
	{
		// evganat - энциклопедия
		int iBonus = 0;
		if (!ENCYCLOPEDIA_DISABLED)
		{
			if (IsMainCharacter(refCharacter) || IsCompanion(refCharacter))
				iBonus = GetParamPageBonus("WindCatcher");
		}
		refRealShip.InertiaAccelerationX	= stf(refBaseShip.InertiaAccelerationX) + stf(refBaseShip.InertiaAccelerationX) * (0.1 + 0.01*iBonus);
		refRealShip.InertiaAccelerationY	= stf(refBaseShip.InertiaAccelerationY) + stf(refBaseShip.InertiaAccelerationY) * (0.1 + 0.01*iBonus);
		refRealShip.InertiaAccelerationZ	= stf(refBaseShip.InertiaAccelerationZ) + stf(refBaseShip.InertiaAccelerationZ) * (0.1 + 0.01*iBonus);
		// потмоу что перк помогает только быстрее набирать скорость, нет торможения
	}
	else
	{   // вернём, если перк снят
	    refRealShip.InertiaAccelerationX	= stf(refBaseShip.InertiaAccelerationX);
		refRealShip.InertiaAccelerationY	= stf(refBaseShip.InertiaAccelerationY);
		refRealShip.InertiaAccelerationZ	= stf(refBaseShip.InertiaAccelerationZ);
	}
	if (iArcadeSails == 0) // момент инерции ниже для тактики
	{
	    refRealShip.InertiaAccelerationY = stf(refRealShip.InertiaAccelerationY) / 2.0;
	}
}

// EvgAnat - переключение опции быстрого нахождения предметов -->
void SetHawkEye(ref loc)
{
	ref itm;
	int i, iOff;
	bool enableHE = false;
	float fTemp, x, y, z, up;
	string sGroup, sLocator;
	if (CheckAttribute(loc, "id") && loc.id == "Temple_round") return;
	if (GetOfficersPerkUsing(pchar, "HawkEye", true))
	{
		enableHE = true;
	}
	if (!enableHE) return;
    for (i = 0; i < ITEMS_QUANTITY; i++)
    {
        makeref(itm, Items[i]);
        if (CheckAttribute(itm, "shown") && itm.shown == true
            && CheckAttribute(itm, "startLocation") && CheckAttribute(itm, "startLocator")
            && itm.startLocation == pchar.location)
        {
            if (StrHasStr(itm.startLocator, "fire,button", 1)) continue;
            sGroup = "item";
            sLocator = itm.startLocator;
            if (!CheckAttribute(loc, "locators.item." + sLocator) || !CheckFreeItemLocator(pchar.location, sLocator) || !CheckAttributeMass(loc, "locators.item." + sLocator, "x,y,z", "|")) continue;
            x = stf(loc.locators.(sGroup).(sLocator).x);
            y = stf(loc.locators.(sGroup).(sLocator).y);
            z = stf(loc.locators.(sGroup).(sLocator).z);
            up = 0.2;

            //если камень ростовщика или кольцо "красавицы", то подсветку поднимаем на высоту травы
            if (CheckAttribute(&InterfaceStates, "HerbDetails.Height") && StrHasStr(itm.id, "UsurersJew,WeddingRing", 1))
            {
                fTemp = stf(InterfaceStates.HerbDetails.Height);
                if (fTemp > 0.65) up = 0.6;
                else if (fTemp < 0.17) up = 0.25;
                else if (fTemp < 0.25) up = fTemp * 1.5;
                else up = fTemp * 1.75;
            }

            itm.particleId = CreateParticleSystemX("HawkEye", x, y+up, z, x, y+up, z, 0); //подсветка предмета
        }
    }
}
// EvgAnat - переключение опции быстрого нахождения предметов <--

// EvgAnat - дикие Карибы, возвращение сфер во все локации
void SetWildCaribbean()
{
	//QuestionsInit();
	//SeaQuestionsInit();
	int n;
	n = FindLocation("SentJons_TownCave");
	SetSphereToLocation(n, "DungeonDuffer1");
	n = FindLocation("Antigua_Grot");
	SetSphereToLocation(n, "grotto1");
	n = FindLocation("Barbados_Cave");
	SetSphereToLocation(n, "DungeonDuffer2");
	n = FindLocation("Beliz_Cave");
	SetSphereToLocation(n, "cavernMedium1");
	n = FindLocation("Beliz_Cave_2");
	SetSphereToLocation(n, "DungeonDuffer2");
	n = FindLocation("Bermudes_Dungeon");
	SetSphereToLocation(n, "DungeonVault1");
	n = FindLocation("Bermudes_Cavern");
	SetSphereToLocation(n, "cavernLow1");
	n = FindLocation("Caiman_Grot");
	SetSphereToLocation(n, "grotto1");
	n = FindLocation("Caracas_Grot");
	SetSphereToLocation(n, "grotto1");
	n = FindLocation("Cartahena_Cave");
	SetSphereToLocation(n, "cavernMedium2");
	n = FindLocation("Cumana_Cave");
	SetSphereToLocation(n, "cavernMedium1");
	n = FindLocation("Curacao_Cave");
	SetSphereToLocation(n, "cavernMedium2");
//	n = FindLocation("Dominica_Grot");
//	SetSphereToLocation(n, "GrotI");
	n = FindLocation("Guadeloupe_Cave");
	SetSphereToLocation(n, "cavernBig1");
	n = FindLocation("Jamaica_Grot");
	SetSphereToLocation(n, "grotto1");
	n = FindLocation("Maracaibo_Cave");
	SetSphereToLocation(n, "cavernMedium2");
	n = FindLocation("FortFrance_Dungeon");
	SetSphereToLocation(n, "DungeonVault2");
	n = FindLocation("Charles_Grot");
	SetSphereToLocation(n, "grotto2");
	n = FindLocation("Panama_Cave");
	SetSphereToLocation(n, "DungeonDuffer2");
	n = FindLocation("Pearl_Grot");
	SetSphereToLocation(n, "grotto1");
	n = FindLocation("PortoBello_Cave");
	SetSphereToLocation(n, "DungeonDuffer2");
	n = FindLocation("SanJuan_Cave");
	SetSphereToLocation(n, "cavernMedium1");
	n = FindLocation("SantaCatalina_Cave");
	SetSphereToLocation(n, "cavernMedium2");
	n = FindLocation("SantaCatalina_Grot");
	SetSphereToLocation(n, "grotto2");
	n = FindLocation("SantaCatalina_PearlCave");
	SetSphereToLocation(n, "cavernMedium1");
	n = FindLocation("Cuba_Grot");
	SetSphereToLocation(n, "grotto2");
	n = FindLocation("Hispaniola_Cave");
	SetSphereToLocation(n, "cavernMedium1");
	n = FindLocation("Marigo_Cave");
	SetSphereToLocation(n, "cavernMedium2");
	n = FindLocation("Tenotchitlan_Cave");
	SetSphereToLocation(n, "cavernMedium1");
	n = FindLocation("Terks_Grot");
	SetSphereToLocation(n, "grotto1");
	n = FindLocation("Tortuga_Cave");
	SetSphereToLocation(n, "DungeonVault1");
	n = FindLocation("Tortuga_Grot");
	SetSphereToLocation(n, "grotto2");
	n = FindLocation("Trinidad_Grot");
	SetSphereToLocation(n, "grotto2");
	n = FindLocation("Providence_Cavern");
	SetSphereToLocation(n, "cavernLow1");
}
// EvgAnat - дикие Карибы, возвращение сфер в конкретную локацию
void SetSphereToLocation(int n, string sLoc)
{
	string sRays = sLoc+"_rays";
	string sLocators = sLoc+"_locatorsdk";
	if(n == FindLocation("SantaCatalina_PearlCave"))
	{
		sLocators = "CavernMedium1_lSCPearlsdk";
		sRays = "cavernMedium1_rays";
	}
	Locations[n].models.always.locators = sLocators;
	Locations[n].locators_radius.item.duhi1 = 1.3;
	Locations[n].models.always.rays = sRays;
	Locations[n].models.always.rays.level = 49;
	Locations[n].models.always.rays.tech = "LocVisRays";
	Locations[n].models.always.rays.uvslide.u1 = -0.03;
	Locations[n].models.always.rays.uvslide.v1 = -0.03;
}

// Rosarak убрать раздражающие цифры и оповещения
bool HaveAllPerks(ref sld, string type)
{
	string perkName;
	aref arPerksRoot;
	makearef(arPerksRoot,ChrPerksList.list);
	int perksQ = GetAttributesNum(arPerksRoot);
	for(int i = 0; i < perksQ; i++)
	{
		//Эти скипаются в интерфейсе
		perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
		if (ChrPerksList.list.(perkName).BaseType != type || perkName == "WildCaribbean")	continue;
		if (CheckAttribute(sld, "CompanionDisable") && perkName == "ShipEscape")			continue;
		if (sld.id == pchar.id && CheckAttribute(arPerksRoot, perkName + ".NPCOnly"))		continue;
		if (sld.id != pchar.id && CheckAttribute(arPerksRoot, perkName + ".PlayerOnly"))	continue;
		if (CheckAttribute(arPerksRoot, perkName + ".Hidden") && !ShowHiddenPerks(sld, perkName)) continue;
		if (CheckAttribute(sld, "AllowedPosts"))
		{
			if(perkName == "ByWorker"  && GetCountSubString(sld.AllowedPosts) < 2)	continue;
			if(perkName == "ByWorker2" && GetCountSubString(sld.AllowedPosts) < 3)	continue;
		}
		if (CheckAttribute(arPerksRoot, perkName + ".OfficerType"))
		{
			if(arPerksRoot.(perkName).OfficerType == "capellan" && !CheckAttribute(sld, "Capellan"))
				continue;
			if(CheckAttribute(sld, "AllowedPosts") && !HasSubStr(sld.AllowedPosts, arPerksRoot.(perkName).OfficerType)
			&& CheckAttribute(sld, "CompanionDisable"))
				continue;
		}
		//Проверяем теперь отображаемый
		if(!CheckCharacterPerk(sld, perkName)) return false;
	}
	return true;
}

// KZ > отображать в перечне доступных перков и скрытые, разрешённые для rChar
bool ShowHiddenPerks(ref rChar, string sPerkName)
{
	switch (sPerkName)
	{
		case "ByWorker":			// > перк "Совместитель" доступен только этим персам
			if (CheckAttribute(rChar, "PGGAi") || StrHasStr(rChar.id, "Angellica,DanielleOff,Dieke,Hugtorp,Jafarry,James_Callow,Martin_Bleker,Pitt,YokoDias,Volverston", 1))
				return true;
		break;
		case "ByWorker2":			// > перк "Совместитель-универсал" доступен только этим персам
			if (StrHasStr(rChar.id, "DanielleOff,Martin_Bleker", 1))
				return true;
		break;
		case "MusketsTraining":		// > перк "Мушкетёрская подготовка" доступен только этим персам
			if (PChar.id == rChar.id) return true;
			if (CheckAttribute(rChar, "MushForever")) return true;
            //if (CheckAttribute(rChar, "PGGAi") && CharCanTakeMushket(rChar)) return true;
		break;
	}

	return false;
}

// AlexBlade > расширения для SeaPerkShower
bool IsOfficersPerkAcquired(ref chref, string perkName)
{
	string  sOfficerType;
	ref   offc;
	bool  ok = false;
	bool  okDelay = true;
	int   cn;
	if (CheckCharacterPerk(chref, perkName)) {return true;}
	if (!CheckAttribute(chref,"perks.list."+perkName))
	{
		for(int i=1; i<=6; i++)
		{
			sOfficerType = GetOfficerTypeByNum(i);
			if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && ChrPerksList.list.(perkName).OfficerType == sOfficerType)
			{
				cn = sti(chref.Fellows.Passengers.(sOfficerType));
				if (cn<0) {continue;}
				offc = &Characters[cn];
				if (CheckAttribute(offc, "perks.list."+perkName))
					ok = true;
			}
		}
	}
	if (HasSubStr(perkName, "Capellan") && CheckAttribute(chref, "questTemp.ShipCapellan.Yes")) //капеллан
	{
		offc = CharacterFromId(chref.questTemp.ShipCapellan.id);
		if (CheckAttribute(offc, "perks.list."+perkName)) ok = true;
	}
	return ok;
}

// KZ > обновить / удалить активные морские перки у офицеров и компаньонов ГГ
void RefreshActiveSeaPerks(bool bRestart)
{
	if (sti(InterfaceStates.Launched) == 1) return;

	int i, iComp, q = GetPassengersQuantity(pchar);
	ref rChar;

	if (q > 0)
	{
		for (i = 0; i < q; i++)
		{
			rChar = &Characters[GetPassenger(pchar, i)];

			if (IsOfficerRemovable(rChar))
				RefreshActiveSeaPerksFunc(rChar, bRestart);
		}
	}

	q = GetCompanionQuantity(pchar);

	if (q > 1)
	{
		for (i = 1; i <= q; i++)
		{
			iComp = GetCompanionIndex(pchar, i);

			if (iComp >= 0)
			{
				rChar = GetCharacter(iComp);

				if (GetShipRemovable(rChar) && GetRemovable(rChar))
					RefreshActiveSeaPerksFunc(rChar, bRestart);
			}
		}
	}
}

void RefreshActiveSeaPerksFunc(ref _rChar, bool _bRestart)
{
	int j, iPerks;
	aref arPerksRoot, arPerk;
	string sPerk;

	makearef(arPerksRoot, _rChar.perks.list);
	iPerks = GetAttributesNum(arPerksRoot);

	for (j = 0; j < iPerks; j++)
	{
		arPerk = GetAttributeN(arPerksRoot, j);
		sPerk = GetAttributeName(arPerk);

		if (IsSeaActivePerk(sPerk))
		{
			if (_bRestart)
			{
				DelPerkFromActiveList(sPerk);
				DeleteAttributeEx(arPerk, "active,delay");
				PostEvent("evntPerkAgainUsable", 1);							
			}
			else
				PostEvent("evntChrPerkDelay", 50, "sl", sPerk, sti(_rChar.index));
		}
	}
}

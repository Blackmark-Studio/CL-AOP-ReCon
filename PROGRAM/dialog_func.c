#include "scripts\utils.c"

#define MAX_TITLENEXTRATE   13 // счетчик для званий
#define MAX_TITLE           5

object Address_Form;

void Set_inDialog_Attributes()
{ 
	ref The_Character_is;

	The_Character_is = GetMainCharacter();
    if (!CheckAttribute(The_Character_is, "sex") || The_Character_is.sex == "man")
	{
		Address_Form.Spa = GlobalStringConvert("Address_Form_Spa");
		Address_Form.Fra = GlobalStringConvert("Address_Form_Fra");
		Address_Form.Eng = GlobalStringConvert("Address_Form_Eng");
		Address_Form.Hol = GlobalStringConvert("Address_Form_Hol");
		Address_Form.Pir = GlobalStringConvert("Address_Form_Pir");
    }
    else
    {
		Address_Form.Spa = GlobalStringConvert("Address_Form_SpaWoman");
		Address_Form.Fra = GlobalStringConvert("Address_Form_FraWoman");
		Address_Form.Eng = GlobalStringConvert("Address_Form_EngWoman");
		Address_Form.Hol = GlobalStringConvert("Address_Form_HolWoman");
		Address_Form.Pir = GlobalStringConvert("Address_Form_PirWoman");
	}
	Address_Form.Spa.Title1 = GlobalStringConvert("Address_Form_Spa_Title1");
	Address_Form.Fra.Title1 = GlobalStringConvert("Address_Form_Fra_Title1");
	Address_Form.Eng.Title1 = GlobalStringConvert("Address_Form_Eng_Title1");
	Address_Form.Hol.Title1 = GlobalStringConvert("Address_Form_Hol_Title1");
	Address_Form.Pir.Title1 = GlobalStringConvert("Address_Form_Pir_Title1");

    Address_Form.Spa.Title2 = GlobalStringConvert("Address_Form_Spa_Title2");
	Address_Form.Fra.Title2 = GlobalStringConvert("Address_Form_Fra_Title2");
	Address_Form.Eng.Title2 = GlobalStringConvert("Address_Form_Eng_Title2");
	Address_Form.Hol.Title2 = GlobalStringConvert("Address_Form_Hol_Title2");
	Address_Form.Pir.Title2 = GlobalStringConvert("Address_Form_Pir_Title2");
	
	Address_Form.Spa.Title3 = GlobalStringConvert("Address_Form_Spa_Title3");
	Address_Form.Fra.Title3 = GlobalStringConvert("Address_Form_Fra_Title3");
	Address_Form.Eng.Title3 = GlobalStringConvert("Address_Form_Eng_Title3");
	Address_Form.Hol.Title3 = GlobalStringConvert("Address_Form_Hol_Title3");
	Address_Form.Pir.Title3 = GlobalStringConvert("Address_Form_Pir_Title3");

	Address_Form.Spa.Title4 = GlobalStringConvert("Address_Form_Spa_Title4");
	Address_Form.Fra.Title4 = GlobalStringConvert("Address_Form_Fra_Title4");
	Address_Form.Eng.Title4 = GlobalStringConvert("Address_Form_Eng_Title4");
	Address_Form.Hol.Title4 = GlobalStringConvert("Address_Form_Hol_Title4");
	Address_Form.Pir.Title4 = GlobalStringConvert("Address_Form_Pir_Title4");

	Address_Form.Spa.Title5 = GlobalStringConvert("Address_Form_Spa_Title5");
	Address_Form.Fra.Title5 = GlobalStringConvert("Address_Form_Fra_Title5");
	Address_Form.Eng.Title5 = GlobalStringConvert("Address_Form_Eng_Title5");
	Address_Form.Hol.Title5 = GlobalStringConvert("Address_Form_Hol_Title5");
	Address_Form.Pir.Title5 = GlobalStringConvert("Address_Form_Pir_Title5");

	Address_Form.Spa.woman = GlobalStringConvert("Address_Form_SpaWoman2");
	Address_Form.Fra.woman = GlobalStringConvert("Address_Form_FraWoman2");
	Address_Form.Eng.woman = GlobalStringConvert("Address_Form_EngWoman2");
	Address_Form.Hol.woman = GlobalStringConvert("Address_Form_HolWoman2");
	Address_Form.Pir.woman = GlobalStringConvert("Address_Form_PirWoman2");

	Address_Form.Spa.man = GlobalStringConvert("Address_Form_Spa");
	Address_Form.Fra.man = GlobalStringConvert("Address_Form_Fra");
	Address_Form.Eng.man = GlobalStringConvert("Address_Form_Eng");
	Address_Form.Hol.man = GlobalStringConvert("Address_Form_Hol");
	Address_Form.Pir.man = GlobalStringConvert("Address_Form_Pir");
}

string RandSwear()
{
	string sRandSwear;
	switch (rand(14))
	{
		case 0:
			sRandSwear = GlobalStringConvert("Swear_1");
		break;

		case 1:
			sRandSwear = GlobalStringConvert("Swear_2");
		break;

		case 2:
			sRandSwear = GlobalStringConvert("Swear_3");
		break;

		case 3:
			sRandSwear = GlobalStringConvert("Swear_4");
		break;

		case 4:
			sRandSwear = GlobalStringConvert("Swear_5");
		break;

		case 5:
			sRandSwear = GlobalStringConvert("Swear_6");
		break;

		case 6:
			sRandSwear = GlobalStringConvert("Swear_7");
		break;

		case 7:
			sRandSwear = GlobalStringConvert("Swear_8");
		break;	 
		
		case 8:
			sRandSwear = GlobalStringConvert("Swear_9");	// стандартное пиратское "твою мать"
		break;
		
		case 9:
			sRandSwear = GlobalStringConvert("Swear_10");
		break;

		case 10:
			sRandSwear = GlobalStringConvert("Swear_11");
		break;
		
		case 11:
			sRandSwear = GlobalStringConvert("Swear_12");
		break;
		
		case 12:
			sRandSwear = GlobalStringConvert("Swear_13");
		break;
		
		case 13:
			sRandSwear = GlobalStringConvert("Swear_14");
		break;
		
		case 14:
			sRandSwear = GlobalStringConvert("Swear_15");
		break;
	}
	return sRandSwear;
}

//т.к. "О, Боже!!! Я вырежу тебе сердце" звучит мягко говоря странно
string RandExclamation()
{
    string sRandExclamation;
	switch(rand(2))
	{
		case 0:
			sRandExclamation = GlobalStringConvert("Exclamation_1");
		break;

		case 1:
			sRandExclamation = GlobalStringConvert("Exclamation_2");
		break;

		case 2:
			sRandExclamation = GlobalStringConvert("Exclamation_3");
		break;
	}
	return sRandExclamation + " ";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                Выбор фраз для диалога
////////////////////////////////////////////////////////////////////////////////////////////////////////

string RandPhraseSimple(string Var1, string Var2)
{
	int RandP;
	RandP = Rand(1);
	switch(RandP)
	{
		case 0:
			return /*"First phrase selected" + */ Var1;
		break;

		case 1:
			return /*"Second phrase selected" + */Var2;
		break;
	}
	return "ERROR";
}
// выбор фразы из трёх
string LinkRandPhrase(string Var1, string Var2, string Var3)
{
	int RandP;
	RandP = Rand(2);
	switch(RandP)
	{
		case 0:

			return /*"First phrase selected" + */ Var1;

		break;

		case 1:

			return /*"Second phrase selected" + */Var2;

		break;

		case 2:

			return /*"Third phrase selected" + */Var3;

		break;
	}
	return "ERROR";
}

string NationKingsCrown(ref Character)
{
    switch(sti(Character.nation))
	{
		case ENGLAND:
            return GlobalStringConvert("NationKingsCrown_Eng");
		break;
		case FRANCE:
            return GlobalStringConvert("NationKingsCrown_Fra");
		break;
		case SPAIN:
            return GlobalStringConvert("NationKingsCrown_Spa");
		break;
		case HOLLAND:
			return GlobalStringConvert("NationKingsCrown_Hol");
		break;
		case PIRATE:
			return GlobalStringConvert("NationKingsCrown_Pir");
		break;
	}
}
string NationKingsName(ref NPChar)
{
    switch(sti(NPChar.nation))
	{
		case ENGLAND:
            return GlobalStringConvert("NationKingsName_Eng");
		break;
		case FRANCE:
            return GlobalStringConvert("NationKingsName_Fra");
		break;
		case SPAIN:
            return GlobalStringConvert("NationKingsName_Spa");
		break;
		case HOLLAND:
			return GlobalStringConvert("NationKingsName_Hol");
		break;
		case PIRATE:
			return GlobalStringConvert("NationKingsName_Pir");
		break;
	}
}

string NationNameMan(int pNation)
{
    switch(pNation)
	{
		case ENGLAND:
            return XI_ConvertString("manOfEngland");
		break;
		case FRANCE:
            return XI_ConvertString("manOfFrance");
		break;
		case SPAIN:
            return XI_ConvertString("manOfSpain");
		break;
		case HOLLAND:
			return XI_ConvertString("manOfHolland");
		break;
		case PIRATE:
			return XI_ConvertString("manOfPirate");
		break;
	}
}

string NationNamePeople(int pNation)
{
    switch(pNation)
	{
		case ENGLAND:
            return XI_ConvertString("peopleEngland");
		break;
		case FRANCE:
            return XI_ConvertString("peopleFrance");
		break;
		case SPAIN:
            return XI_ConvertString("peopleSpain");
		break;
		case HOLLAND:
			return XI_ConvertString("peopleHolland");
		break;
		case PIRATE:
			return XI_ConvertString("peoplePirate");
		break;
	}
}

string NationNamePeopleAcc(int pNation)
{
    switch(pNation)
	{
		case ENGLAND:
            return XI_ConvertString("peopleEnglandIns");
		break;
		case FRANCE:
            return XI_ConvertString("peopleFranceIns");
		break;
		case SPAIN:
            return XI_ConvertString("peopleSpainIns");
		break;
		case HOLLAND:
			return XI_ConvertString("peopleHollandIns");
		break;
		case PIRATE:
			return XI_ConvertString("peoplePirateIns");
		break;
	}
}

string NationNameInstrumental(int iNation) //творительный падеж
{
    switch(iNation)
	{
		case ENGLAND:
            return XI_ConvertString("EnglandIns");
		break;
		case FRANCE:
            return XI_ConvertString("FranceIns");
		break;
		case SPAIN:
            return XI_ConvertString("SpainIns");
		break;
		case HOLLAND:
			return XI_ConvertString("HollandIns");
		break;
		case PIRATE:
			return XI_ConvertString("PirateIns");
		break;
	}
}

string NationNameNominative(int iNation) //именительный падеж
{
    switch(iNation)
	{
		case ENGLAND:
            return XI_ConvertString("England");
		break;
		case FRANCE:
            return XI_ConvertString("France");
		break;
		case SPAIN:
            return XI_ConvertString("Spain");
		break;
		case HOLLAND:
			return XI_ConvertString("Holland");
		break;
		case PIRATE:
			return XI_ConvertString("Pirate");
		break;
	}
}

string NationNameGenitive(int iNation) // родительный падеж
{
    switch(iNation)
	{
		case ENGLAND:
            return XI_ConvertString("EnglandGen");
		break;
		case FRANCE:
            return XI_ConvertString("FranceGen");
		break;
		case SPAIN:
            return XI_ConvertString("SpainGen");
		break;
		case HOLLAND:
			return XI_ConvertString("HollandGen");
		break;
		case PIRATE:
			return XI_ConvertString("PirateGen");
		break;
	}
}

string GetCityName(string city) // имена городов по аттрибуту chr.city
{
    return GetConvertStr(city + " Town", "LocLables.txt");
}

string TimeGreeting()
{
	if (GetHour() >= 18 && GetHour() < 23)	return GlobalStringConvert("EveningGreeting");
	if (GetHour() >= 6 && GetHour() < 12)	return GlobalStringConvert("MorningGreeting");
	if (GetHour() >= 12 && GetHour() < 18)	return GlobalStringConvert("DayGreeting");
	if (GetHour() >= 23 || GetHour() < 6)	return GlobalStringConvert("NightGreeting");
    return GlobalStringConvert("TimeGreeting");
}

// выбор фразы от репутации
string PCharRepPhrase (string bad, string good)
{
	return NPCharRepPhrase(pchar, bad, good);
}
// boal для НПС
string NPCharRepPhrase(ref _pchar, string bad, string good)
{
	if(makeint(_pchar.reputation) < 41)
	{
		return bad;
	}
	else
	{
		return good;
	}
}

////////// поиск нужного перса для диалога
string GetCharIDByParam(string attrPresent1, string attr2, string val2)
{
    ref rCharacter; //ищем
	int n = GetCharIDXByParam(attrPresent1, attr2, val2);

    if (n > 0)
    {
        makeref(rCharacter,Characters[n]);
        return  rCharacter.id;
    }
    return  "";
}
int GetCharIDXByParam(string attrPresent1, string attr2, string val2)
{
    ref rCharacter; //ищем
	int n;

	for(n=0; n<MAX_CHARACTERS; n++)
	{
		makeref(rCharacter,Characters[n]);
		if (CheckAttribute(rCharacter, attrPresent1))
		{
            if (rCharacter.(attr2) == val2)
                return  n;
		}
    }
    return  -1;
}
int GetCharIDXForTownAttack(string attrPresent1)
{
    ref   rColony; //ищем
	int   n;
	bool  ok;
	
	for (n=0; n<MAX_COLONIES; n++)
	{
		makeref(rColony, colonies[n]);
		ok = false;
		if (CheckAttribute(rColony, "Default.BoardLocation2") && rColony.Default.BoardLocation2 == attrPresent1)
		{
		    ok = true;
		}
		if (rColony.Default.BoardLocation == attrPresent1 || ok)
        {
			if (rColony.HeroOwn == true)
			{
			    return  -1;
			}
			
			return GetFortCommanderIdx(rColony.id);
		}
    }
    return  -1;
}

// обращение НПС к ГГ, зависит от нации НПС и пола ГГ
string GetAddress_Form(ref NPChar)
{
    string attr = NationShortName(sti(NPChar.nation));
    return Address_Form.(attr);
}

// обращение ГГ к НПС, зависит от нации НПС и его пола
string GetAddress_FormToNPC(ref NPChar)
{
    string attr  = NationShortName(sti(NPChar.nation));
    string attr2 = NPChar.sex;
    // проверка на скелетов
    if (attr2 != "woman")
    {
        attr2 = "man";
    }
    return Address_Form.(attr).(attr2);
}

string GetAddress_FormTitle(int nation, int num)
{
    string attr  =  NationShortName(nation);
    string attr2 =  "Title" + num;
    string ret   =  "нет звания";
    if (CheckAttribute(&Address_Form, attr + "." + attr2))
    {
        ret = Address_Form.(attr).(attr2);
    }
    return ret;
}

// eddy. кто по профессии (только для типовых статиков, не фантомов). sPrefix - приставка для падежей: Gen, Dat..
string GetWorkTypeOfMan(ref NPChar, string sPrefix)
{
	string sCity, sTemp;
	sTemp = "unknown";
	if (CheckAttribute(NPChar, "City")) 
	{
		sCity = NPChar.City;
		sTemp = NPChar.id;
		sTemp = strcut(sTemp, strlen(sCity)+1, strlen(sTemp)-1);
	}
	return XI_ConvertString("Who" + sTemp + sPrefix);
}

//проверка на скрытность, возвращаем сразу строку для link.l.go
string CheckSneakByGuards(int iNation)
{
    int iRel = GetCharacterReputation_WithNation(pchar, iNation);
    if (iRel <= 20) iRel = 0;
    int sneakValRes = GetSummonSkillFromName(pchar, SKILL_SNEAK) + iRel;
    TEV.TempGuardDeceptionChance = makeint(GetDeceptionChance(sneakValRes));
    if (sneakValRes < (10 + rand(50) + rand(50))) return "PegYou";
    else return "NotPegYou";
}

float GetDeceptionChance(int sneakVal)
{
    int _sneakVal = sneakVal - 10;
    if (_sneakVal >= 100)
        return 100.0;
    if (_sneakVal < 1)
        return 0.0;

    int posRes;
    if (_sneakVal <= 50)
    {
        posRes = (1 + (_sneakVal + 1)) * (_sneakVal + 1) / 2;
    }
    else
    {
        posRes = (_sneakVal - 50 + 1) * 51 + ((_sneakVal + 1) * (100 - _sneakVal) / 2);
    }

    return posRes / makefloat(51*51) * 100;
}

// Обертка для текста, приписываем вероятность обмана
string DeceptionChance_TextWrapper(string linkText)
{
    if (CheckAttribute(&TEV, "TempGuardDeceptionChance"))
    {
        return StringFromKey("InfoMessages_228", TEV.TempGuardDeceptionChance) + " " + linkText;
        DeleteAttribute(&TEV, "TempGuardDeceptionChance");
    }

    return linkText;
}

string GetInfoPhrase(ref rWho, string info, string str1, string str2)
{
	if (CheckAttribute(rWho, info))
		return str1;
	else
		return str2;
}

bool MakeNavigateRouteToThem()
{
	int idxloc = FindLoadedLocation();

	if(idxloc >= 0)
    {
        TEV.CitizenHelpRoutes = Locations[idxloc].id;

        aref reloads, arTo;
        makearef(reloads, Locations[idxloc].reload);
        int iNum = GetAttributesNum(reloads);
        string sSeeked = GetStrSmallRegister(dialogEditStrings[3]);
        string sConvSeeked = "sConvSeeked";

        //блок условий для удобного поиска -->
        if (HasStr(LowerFirst(XI_ConvertString("whouserers")), sSeeked)) sConvSeeked = GetStrSmallRegister(GetConvertStr("Usurer House", "LocLables.txt"));
        else if (HasStr(LowerFirst(XI_ConvertString("Merchant")), sSeeked)) sConvSeeked = GetStrSmallRegister(GetConvertStr("Store", "LocLables.txt"));
        else if (HasStr(LowerFirst(XI_ConvertString("ft_1")), sSeeked)) sConvSeeked = GetStrSmallRegister(GetConvertStr("Sea", "LocLables.txt"));
        //блок условий для удобного поиска <--

        for(int i = 0; i < iNum; i++)
        {
            aref aLoc = GetAttributeN(reloads, i);
            if (!CheckAttribute(aLoc, "label")) continue; //скипаем локации без названий
            if (HasStr(aLoc.go, "room")) continue; //скипаем вход в комнату борделя
            string sNamePlace = GetStrSmallRegister(GetConvertStr(aLoc.label, "LocLables.txt"));

            if (sConvSeeked == "sConvSeeked")
            {
                if (HasSubStr(sNamePlace, sSeeked))
                {
                    makearef(arTo, TEV.CitizenHelpRoutes);
                    CopyAttributes(arTo, aLoc);
                    TEV.CitizenHelpRoutes.placeName = UpperFirst(GetConvertStr(aLoc.label, "LocLables.txt"));
                    return true;
                }
            }
            else
            {
                if (sNamePlace == sConvSeeked)
                {
                    makearef(arTo, TEV.CitizenHelpRoutes);
                    CopyAttributes(arTo, aLoc);
                    TEV.CitizenHelpRoutes.placeName = UpperFirst(sConvSeeked);
                    return true;
                }
            }
        }
    }
    return false;
}

void ExitNoHideBlade() //HardCoffee задержка для выхода из CitizenNotBlade если гг не хочет убирать саблю
{
    LAi_InstantFightMode(PChar);
	if (CheckAttribute(&TEV, "ChrAfraidIdx")) //Заставим нпс бояться дерзкого кэпа
	{
		ref rChr = GetCharacter(sti(TEV.ChrAfraidIdx));
		LAi_tmpl_afraid_SetAfraidCharacter(rChr, pchar, true);
		DeleteAttribute(&TEV, "ChrAfraidIdx");
		LAi_tmpl_afraid_CharacterUpdate(rChr, 0.0001);
	}
}

void ExitHideBlade() //задержка для выхода из CitizenNotBlade если гг убирает саблю
{
	LAi_InstantFightMode(PChar);
	LAi_SetFightMode(pchar, false);
}

//Поиск города назначения для эскортов у портманов и трактирщиков
string FindDestinationCity(ref NPChar, int iDelta, string sExcludeColony)
{
	int n, nation, storeArray[MAX_COLONIES], howStore = 0;

	for (n = 0; n < MAX_COLONIES; n++)
	{
		if (!CheckAttribute(&colonies[n], "nation")) continue;
		if (colonies[n].nation == "none") continue;
		if (colonies[n].id == "Panama") continue;
		//Во вражеские города тоже отправляем, что бы перк имел смысл
		//if (GetNationRelation(sti(npchar.nation), sti(colonies[n].nation)) == RELATION_ENEMY) continue;
		if (sti(colonies[n].nation) == PIRATE) continue;
		if (GetIslandNameByCity(npchar.city) == colonies[n].islandLable) continue;
		if (StrHasStr(colonies[n].id, sExcludeColony, 1)) continue;
		//если добраться нельзя, то не добавляем
		if (GetMaxDaysFromColony2Colony(npchar.city, colonies[n].id) == -1) continue;
		storeArray[howStore] = n;
		howStore++;
	}

	Restrictor(&iDelta, 0, 3);
	n = storeArray[idRand("DestinationCity_" + NPChar.id, (howStore - 1) - iDelta) + iDelta];
	return colonies[n].id;
}

string LocatorToSendConvoyNpc(ref rChr) //HardCoffee найдём подходящий локатор для уходящего нпс по квесту сопровождения
{
	ref rLoc = &Locations[FindLocation(pchar.location)];

	SendMessage(rChr, "lsl", MSG_CHARACTER_EX_MSG, "SetBonusPush", true);
	MakeUnpushable(rChr, true);
	rChr.ToPointForced = "";

	aref arLoc;
	makearef(arLoc, rLoc.id);
	//этот ивент снимет Push атрибуты и аварийно телепортирует нпс ели он не успел добраться до локатора
	SetEventHandler(EVENT_LOCATION_UNLOAD, "TeleportNpcToLocation", 0);
	TEV.TeleportNpc.id = rChr.id;
	TEV.TeleportNpc.location = "none";

	if (CheckAttribute(arLoc, "label"))
	{
		if (HasStr(arLoc.label, "Tavern") && CheckAttribute(rLoc, "locators.reload.reload1_back"))
			return "reload1_back";
		if (HasStr(arLoc.label, "PortOffice") && CheckAttribute(rLoc, "locators.reload.reload1"))
			return "reload1";
		if (HasStr(arLoc.label, "Street") && CheckAttribute(rLoc, "locators.reload.reload4_back"))
			return "reload4_back";
	}

	float locX, locY, locZ;
	GetCharacterPos(rChr, &locX, &locY, &locZ);
	string sTmp = LAi_FindNearestFreeLocator("reload", locX, locY, locZ);
	if (sTmp == "")
	{
	    sTmp = LAi_FindFarLocator("reload", locX, locY, locZ);
	}
	return sTmp;
}

//HardCoffee fix: если у нпс было задание идти в локатор, но игрок перезагрузился в локацию до того,
//как нпс дошёл до локатора, при следующей загрузке игрока на локацию, нпс не появится
void TeleportNpcToLocation()
{
	DelEventHandler(EVENT_LOCATION_UNLOAD, "TeleportNpcToLocation");
	if (!CheckAttribute(&TEV, "TeleportNpc"))
	{
		trace("TeleportNpcToLocation can't find TEV.TeleportNpc");
	    return;
	}

	ref rChr = characterFromID(TEV.TeleportNpc.id);
	if (rChr.id == nullcharacter.id)
	{
		trace("TeleportNpcToLocation can't find character");
	    DeleteAttribute(&TEV, "TeleportNpc");
	    return;
	}

	ChangeCharacterAddressGroupEx(rChr, TEV.TeleportNpc.location, "goto", "", true);
	SendMessage(rChr, "lsl", MSG_CHARACTER_EX_MSG, "SetBonusPush", false);
	MakeUnpushable(rChr, false);
}

void SeaQuestion_Chinese_GenerateRandomAnswers(ref Npchar, aref Link)
{
	if (LanguageGetLanguage() != "chinese")
	{
		return;
	}

	DeleteAttribute(&TEV, "SeaQuestionTemp");

	TEV.SeaQuestionTemp = Link.l1.go;
	DeleteAttribute(Link, "");
	object answers;
	int iAnswersQty = 5;

	string sTemp, sTemp1;
	int numQuestion = -1;
	if (npchar.id == "Pirates_shipyarder")
	{
	    numQuestion = sti(npchar.SeaQuestions);
	}
	else
	{
		numQuestion = sti(npchar.quest.numQuestion);
	}
	int answerRightLinkNum = 1 + rand(iAnswersQty - 1);

	int iTemp, i;
	i = iAnswersQty - 1;
	while (i > 0)
	{
		iTemp = rand(sti(NullCharacter.questions));
		if (iTemp == numQuestion)
		{
			continue;
		}

		sTemp = "a" + iTemp;
		sTemp1 = NullCharacter.questions.(sTemp);
		sTemp = "w" + i;
		answers.(sTemp) = sTemp1;
		i--;
	}

//	DumpAttributes(&answers);

	iTemp = 1;
	for (i = 1; i <= iAnswersQty; i++)
	{
		sTemp = "l" + i;
		if (i == answerRightLinkNum)
		{
			sTemp1 = "a" + numQuestion;
		    Link.(sTemp) = NullCharacter.questions.(sTemp1);
		}
		else
		{
			sTemp1 = "w" + iTemp;
			Link.(sTemp) = answers.(sTemp1);
			iTemp++;
		}
		Link.(sTemp).go = "SeaQuestionChooseAnswer_"+Link.(sTemp);
	}
}

void LSCParol_Chinese_GenerateRandomAnswers(ref Npchar, aref Link)
{
	if (LanguageGetLanguage() != "chinese")
	{
		return;
	}

	DeleteAttribute(&TEV, "TEV.LSCParolCheck");

	TEV.LSCParolCheck = Link.l1.go;
	DeleteAttribute(Link, "");
	bool isKnownParol = false;
	string rightParol = "";
	if (StrStartsWith(TEV.LSCParolCheck, "Ccheck_parol"))
	{
	    isKnownParol = CheckAttribute(pchar, "questTemp.LSC.CParol_bye");
		rightParol = pchar.questTemp.LSC.CasperParol;
	}
	else
	{
	    isKnownParol = CheckAttribute(pchar, "questTemp.LSC.NParol_bye");
		rightParol = pchar.questTemp.LSC.NarvalParol;
	}
	object answers;
	int iAnswersQty = 3;

	string sTemp, sTemp1;
	int answerRightLinkNum = 1 + rand(iAnswersQty - 1);

	int iTemp, i;
	i = iAnswersQty;
	if (isKnownParol)
	{
		i = iAnswersQty - 1;
	}
	while (i > 0)
	{
		iTemp = rand(sti(NullCharacter.questions));
		sTemp = "a" + iTemp;
		sTemp1 = NullCharacter.questions.(sTemp);

		if (sTemp1 == rightParol)
		{
			continue;
		}

		sTemp = "w" + i;
		answers.(sTemp) = sTemp1;
		i--;
	}

//	DumpAttributes(&answers);

	iTemp = 1;
	for (i = 1; i <= iAnswersQty; i++)
	{
		sTemp = "l" + i;
		if (i == answerRightLinkNum && isKnownParol)
		{
		    Link.(sTemp) = rightParol;
		}
		else
		{
			sTemp1 = "w" + iTemp;
			Link.(sTemp) = answers.(sTemp1);
			iTemp++;
		}
		Link.(sTemp).go = "LSCParolChooseAnswer_"+Link.(sTemp);
	}
}
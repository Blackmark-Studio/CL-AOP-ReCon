// BOAL полностью переделано под нужны ВМЛ

// -> ugeen 27.01.09 - лочим лояльность квестовых офф-ов (всегда максимальная)
void OfficersReaction(string alignment)
{
	ChangeOfficersLoyality(alignment, 1);
}
//-> ugeen

void ChangeOfficersLoyality(string alignment, int iLoyality)
{ // aliggnment types : "bad" , "good" , "bad_all" , "good_all"

	int iPassenger;
	int i, cn;
	ref sld;
	
	for (int io = 0; io<GetPassengersQuantity(pchar); io++)
	{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе	
		iPassenger = GetPassenger(pchar, io);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			ChangeOfficerLoyality(sld, alignment, makefloat(iLoyality));
		}	
	}
	for (i=1; i<COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);
		if(cn!=-1)
		{
			sld = GetCharacter(cn);
			ChangeOfficerLoyality(sld, alignment, makefloat(iLoyality));								
		}
	}	
}

// Изменить лояльность персонажа
float ChangeOfficerLoyality(ref chref, string alignment, float incr)
{
	float result;
	float fLoyality = incr;
	float fLoyalityDecreaseCoef = 1.0;
	float chRepDelta = 0;
	if (CheckAttribute(chref, "reputation"))
	{
		chRepDelta = abs(makefloat(chref.reputation) - REPUTATION_NEUTRAL);
	}
	
	if (CheckAttribute(chref, "loyality") && !CheckAttribute(chref, "OfficerWantToGo.DontGo"))
	{
		if (alignment == "bad" || alignment == "good")
		{
			if (chref.alignment == alignment)
			{
				result = ChangeCharacterLoyality(chref, fLoyality);
				if (CheckAttribute(chref, "PGGAi")) PGG_ChangeRelation2MainCharacter(chref, 1); //navy
			}
			else
			{
				fLoyalityDecreaseCoef = chRepDelta * 0.086 - makefloat(GetCharacterSkill(pchar, SKILL_LEADERSHIP)) / 100.0;
				Restrictor(&fLoyalityDecreaseCoef, 1.0, 3.0);
				fLoyality = incr * fLoyalityDecreaseCoef;
				
				result = ChangeCharacterLoyality(chref, -fLoyality);
				if (CheckAttribute(chref, "PGGAi")) PGG_ChangeRelation2MainCharacter(chref, -1); //navy
			}
		}
		
		if (alignment == "bad_all")
		{
			fLoyalityDecreaseCoef = chRepDelta * 0.086 - makefloat(GetCharacterSkill(pchar, SKILL_LEADERSHIP)) / 100.0;
			Restrictor(&fLoyalityDecreaseCoef, 1.0, 3.0);
			fLoyality = incr * fLoyalityDecreaseCoef;
			
			result = ChangeCharacterLoyality(chref, -fLoyality);
			if (CheckAttribute(chref, "PGGAi")) PGG_ChangeRelation2MainCharacter(chref, -1); //navy
		}
		
		if (alignment == "good_all")
		{
			result = ChangeCharacterLoyality(chref, fLoyality);
			if (CheckAttribute(chref, "PGGAi")) PGG_ChangeRelation2MainCharacter(chref, 1); //navy
		}
	}
	
	return result;
}

float ChangeCharacterLoyality(ref chref, float incr)
{
	float result = 0.0;
	if (CheckAttribute(chref, "loyality"))
	{
		result = makefloat(chref.loyality) + incr;
		
		if (result > MAX_LOYALITY)
        {
            result = MAX_LOYALITY;
        }
		
		if (result < 0.0)
        {
            result = 0.0;
        }
		
		chref.loyality = result;
	}
	
	return result;
}

// результат реакции - действия офа - диалог
void OfficersReactionResult()
{
	int iPassenger;
	int i;
	ref sld;
	
	if (LAi_IsCapturedLocation) return;
	if (chrDisableReloadToLocation) return; // идет некий другой квест с запретом выхода
	if (CheckAttribute(Pchar,"questTemp.MunityOfficerIDX.begin") && Pchar.questTemp.MunityOfficerIDX.begin == "1") return;
	if (GetGlobalTutor()) return;

	if (CheckCharacterPerk(pchar, "IronWill") && drand(3) == 3) // с перком 'Железная воля' у ГГ есть шанс в 25%, что при заходе в таверну в этот день никто из офицеров не будет возмущаться на его действия или требовать повышения зп
		return;
	
	for (i = 0; i<GetPassengersQuantity(pchar); i++)
	{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе
		iPassenger = GetPassenger(pchar, i);
		if (iPassenger != -1)
		{
			sld = GetCharacter(iPassenger);
			if (CheckAttribute(sld, "loyality") && !CheckAttribute(sld,"prisoned") && GetRemovable(sld) && !CheckAttribute(sld, "OfficerWantToGo.DontGo"))
			{
				if (stf(sld.loyality) < CalculateRemoveThresholdLoyality())
				{
					if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
					{
						sld.dialog.filename = "Officer_Man.c";
						sld.dialog.currentnode = "WantToRemove";
				      	if (sld.sex != "woman")
						{
					    	sld.greeting = "Gr_Officer_Fired";
					    }
						DeleteAttribute(sld, "quest.officertype");
	
						LAi_SetActorType(sld);
						LAi_ActorDialog(sld, pchar, "", 2.0, 0);
						//SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0);
			    		//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			    		chrDisableReloadToLocation = true;
			    		DoQuestCheckDelay("OpenTheDoors", 5.0);
						break;
					}
				}
			}
		}
	}
	if (chrDisableReloadToLocation) return; // уже увольняется
	
	if (CheckNPCQuestDate(pchar, "OfficerWantToGo") && rand(1) == 1) // только раз в день
	{
		SetNPCQuestDate(pchar, "OfficerWantToGo");
		for (i = 0; i<GetPassengersQuantity(pchar); i++)
		{   // любой пассажир у кого есть пристрастие может свалить если наши дела ему не по душе
			iPassenger = GetPassenger(pchar, i);
			if (iPassenger != -1)
			{
				sld = GetCharacter(iPassenger);
				if (!CheckAttribute(sld,"prisoned")                                         //заключенным все ок
					&& !CheckAttribute(sld, "OfficerWantToGo.DontGo")                       //если офицер не уходит, то и не уйдет
					&& GetRemovable(sld) && GetNpcQuestPastDayParam(sld, "HiredDate") > 60  //просит повышать оклад после 60 дней от даты найма
					&& GetNpcQuestPastDayParam(sld, "OfficerWantToGo") > 30                 //повторная просьба возможна только после 30 дней с последней просьбы
					&& rand(10) == 5)
				{
					SetNPCQuestDate(sld, "OfficerWantToGo");
					
					// Квестовые и мушкетёры не достают даже без черты; TODO: имеет смысл везде выдать, а эту проверку убрать
					if (sld.dialog.filename == "Enc_Officer_dialog.c" || sld.dialog.filename == "Enc_OfficerGirl.c")
					{
						if (PlaceCharacter(sld, "goto", "random_must_be_near") != "")
						{
							sld.dialog.currentnode = "WantToGo";
							sld.greeting           = "Gr_Officer_Salary";
		
							LAi_SetActorType(sld);
							LAi_ActorDialog(sld, pchar, "", 2.0, 0);
							//SetActorDialogAny2Pchar(sld.id, "pchar_back_to_player", 0.0, 0.0);
							//LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
							chrDisableReloadToLocation = true;
							DoQuestCheckDelay("OpenTheDoors", 5.0);
							break;
						}
					}
				}
			}
		}
	}
}

float CalculateRemoveThresholdLoyality()
{
	int result = 1 - (GetCharacterSPECIAL(pchar, SPECIAL_C) - 5);
	
	if (result < 1)
		result = 1;
	
	return makefloat(result);
}

bool IsOfficerRemovable(ref _chr) //HardCoffee функция проверяет на офицерство, даже если у офицера нет назначений
{	//используется для обмена предметами
	//в отличии от GetRemovable - исключает зэков
	//цикл нужен на случай, если в _chr попал не офицер
	int i, iTemp;
	ref compareChr;
	for (i = 0; i < GetPassengersQuantity(pchar); i++)
	{
		iTemp = GetPassenger(pchar,i);
		if (iTemp < 0) continue;
		compareChr = &characters[iTemp];
		if (compareChr.id == _chr.id)
		{
			if (CheckAttribute(compareChr,"NonRemovable")) return false;
			if (CheckAttribute(compareChr,"prisoned") && sti(compareChr.prisoned) > 0) return false;
			return true;
		}
	}
	return false;
}

bool isOfficerInShip(ref _chr, bool _withBoard)
{
	if (sti(pchar.Fellows.Passengers.navigator)	== sti(_chr.index))	return true;
	if (sti(pchar.Fellows.Passengers.boatswain)	== sti(_chr.index))	return true;
	if (sti(pchar.Fellows.Passengers.cannoner)	== sti(_chr.index))	return true;
	if (sti(pchar.Fellows.Passengers.doctor)	== sti(_chr.index))	return true;
	if (sti(pchar.Fellows.Passengers.carpenter)	== sti(_chr.index))	return true;
    if (sti(pchar.Fellows.Passengers.treasurer)	== sti(_chr.index))	return true;
	if (_withBoard && IsOfficer(_chr))	return true;
	if (CheckAttribute(_chr, "Capellan") && CheckAttribute(pchar, "questTemp.ShipCapellan.Yes")) return true;
	return false;
}

void CheckForReleaseOfficer(int iCharIndex)	// метод увольняет офицера - название левое, наследие к3
{
	if(sti(pchar.Fellows.Passengers.navigator) == iCharIndex)
	{
		pchar.Fellows.Passengers.navigator = -1;
		DeleteAttribute(&characters[iCharIndex], "navigator"); // совместитель дожности
	}

	if(sti(pchar.Fellows.Passengers.boatswain) == iCharIndex)
	{
		pchar.Fellows.Passengers.boatswain = -1;
		DeleteAttribute(&characters[iCharIndex], "boatswain"); // совместитель дожности
	}

	if(sti(pchar.Fellows.Passengers.cannoner) == iCharIndex)
	{
		pchar.Fellows.Passengers.cannoner = -1;
		DeleteAttribute(&characters[iCharIndex], "cannoner"); // совместитель дожности
	}

	if(sti(pchar.Fellows.Passengers.doctor) == iCharIndex)
	{
		pchar.Fellows.Passengers.doctor = -1;
		DeleteAttribute(&characters[iCharIndex], "doctor"); // совместитель дожности
	}

	if(sti(pchar.Fellows.Passengers.carpenter) == iCharIndex)
	{
		pchar.Fellows.Passengers.carpenter = -1;
		DeleteAttribute(&characters[iCharIndex], "carpenter"); // совместитель дожности
	}
	
    if(sti(pchar.Fellows.Passengers.treasurer) == iCharIndex)
	{
		pchar.Fellows.Passengers.treasurer = -1;
		DeleteAttribute(&characters[iCharIndex], "treasurer"); // совместитель дожности
	}
	
	//if (IsOfficer(&characters[iCharIndex]) == true)
	//{
		// все проверки внутри,  иначе не работает на трупе
		RemoveOfficersIndex(pchar, iCharIndex);
		DeleteAttribute(&characters[iCharIndex], "fighter"); // совместитель дожности
	//}
	DeleteAttribute(&characters[iCharIndex], "isfree"); // для формы ф2, название странное - обратный смысл, если есть, то занят
}

//////////////// OFFICER ////////////////
void __DEPRECATED_SetOfficerParam(ref Npchar, int _type)
{
	float upSkill = 0.7;
	
	ClearCharacterExpRate(Npchar); // трем все пороги экспы на всяк сулчай

    Npchar.quest.LeadershipModify  = 0;
	Npchar.quest.FencingModify     = 0;
	Npchar.quest.SailingModify     = 0;
	Npchar.quest.AccuracyModify    = 0;
	Npchar.quest.CannonsModify     = 0;
	Npchar.quest.GrapplingModify   = 0;
	Npchar.quest.RepairModify      = 0;
	Npchar.quest.DefenseModify     = 0;
	Npchar.quest.CommerceModify    = 0;
	Npchar.quest.SneakModify       = 0;
	Npchar.quest.PistolModify      = 0;

	SetRandSPECIAL(Npchar);
	Npchar.quest.officertype_2 = "";
    switch(_type)
	{
		case 0:
			Npchar.quest.officertype = "boatswain";
			Npchar.quest.officertype_2 = RandPhraseSimple(StringFromKey("Officer_Common_555"), StringFromKey("Officer_Common_556"));
			Npchar.quest.LeadershipModify     = frandSmall(2.0);
			Npchar.quest.FencingModify     = Rand(1);
			Npchar.quest.GrapplingModify   = frandSmall(2.0) + 2;
			Npchar.quest.DefenseModify     = frandSmall(2.0) + 2;
			Npchar.quest.SneakModify       = Rand(1);
			
			//Npchar.skill.Grappling_rate = makeint(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Defence_rate   = makeint(MOD_EXP_RATE * upSkill);
		break;

		case 1:
			Npchar.quest.officertype = "cannoner";
			Npchar.quest.AccuracyModify      = frandSmall(2.0) + 2;
			Npchar.quest.CannonsModify       = frandSmall(2.0) + 2;
			Npchar.quest.SneakModify         = Rand(1);
			
			//Npchar.skill.Cannons_rate = makeint(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Accuracy_rate   = makeint(MOD_EXP_RATE * upSkill);
		break;

		case 2:
			Npchar.quest.officertype_2 = RandPhraseSimple(StringFromKey("Officer_Common_557"), StringFromKey("Officer_Common_558"));
			Npchar.quest.officertype = "treasurer";
			Npchar.quest.RepairModify        = frandSmall(2.0) + 2;
			Npchar.quest.CommerceModify      = frandSmall(2.0) + 3;
			Npchar.quest.SneakModify         = frandSmall(2.0) + 2;
			
			//Npchar.skill.Repair_rate = makeint(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Commerce_rate   = makeint(MOD_EXP_RATE * upSkill);
		break;

		case 3:
			Npchar.quest.officertype_2 = RandPhraseSimple(StringFromKey("Officer_Common_559"), StringFromKey("Officer_Common_560"));
			Npchar.quest.officertype = "navigator";
			Npchar.quest.SailingModify        = frandSmall(2.0) + 2;
			Npchar.quest.DefenseModify        = frandSmall(2.0) + 1.3;
			Npchar.quest.SneakModify          = frandSmall(2.0);
			
			//Npchar.skill.Sailing_rate = makeint(MOD_EXP_RATE * upSkill);
		break;

        case 4:
			Npchar.quest.officertype = "fighter";
			Npchar.quest.FencingModify         = frandSmall(2.0) + 2;
			Npchar.quest.PistolModify          = frandSmall(2.0) + 2;
			
			//Npchar.skill.Fencing_rate = makeint(MOD_EXP_RATE * upSkill);
            //Npchar.skill.Pistol_rate   = makeint(MOD_EXP_RATE * upSkill);
		break;
		// не при делах -->
		case 5:
		//Npchar.quest.officertype = OFFIC_TYPE_FIRSTMATE;
			Npchar.quest.LeadershipModify     = frandSmall(3.0) + 2;
			Npchar.quest.SailingModify        = frandSmall(1.0) + 1;
			Npchar.quest.SneakModify          = Rand(3) + 1;

		//Npchar.skill.Leadership_rate = makeint(MOD_EXP_RATE * upSkill);
		//Npchar.skill.Sneak_rate   = makeint(MOD_EXP_RATE * upSkill);
		break;

		case 6:
		//Npchar.quest.officertype = OFFIC_TYPE_DOCTOR;
			Npchar.quest.DefenseModify       = Rand(3) + 3;
			Npchar.quest.SneakModify         = Rand(3);
		break;
		// не при делах
		case 7:
		//Npchar.quest.officertype = OFFIC_TYPE_CARPENTER;
			Npchar.quest.RepairModify         = Rand(3) + 3;
			Npchar.quest.SneakModify          = Rand(3);
		break;
	}

	// boal Npchar.rank = makeint(Pchar.rank) - 2 + Rand(4);
	Npchar.experience = 0;// boal CalculateExperienceFromRank(sti(Npchar.rank));
    // boal fix 16.12.2003 -->
	//CalculateAppropriateSkills(NPchar);
	float MiddleK = GetMiddleMainSkill();

    Npchar.skill.Leadership    = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Fencing       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Sailing       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Accuracy      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Cannons       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Grappling     = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Repair        = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Defence       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Commerce      = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
	Npchar.skill.Sneak         = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.Pistol        = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.FencingLight  = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.FencingHeavy  = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;
    Npchar.skill.Fortune       = MiddleK - frandSmall(10*MOD_SKILL_ENEMY_RATE / 1.5) + 7;

    CorrectSkillParam(Npchar); // привести к 0-1
    // boal fix 16.12.2003 <--

	Npchar.skill.Leadership   = makeint(stf(Npchar.skill.Leadership)   + 10*stf(Npchar.quest.LeadershipModify));
	Npchar.skill.Fencing      = makeint(stf(Npchar.skill.Fencing)      + 10*stf(Npchar.quest.FencingModify));
	Npchar.skill.Sailing      = makeint(stf(Npchar.skill.Sailing)      + 10*stf(Npchar.quest.SailingModify));
	Npchar.skill.Accuracy     = makeint(stf(Npchar.skill.Accuracy)     + 10*stf(Npchar.quest.AccuracyModify));
	Npchar.skill.Cannons      = makeint(stf(Npchar.skill.Cannons)      + 10*stf(Npchar.quest.CannonsModify));
	Npchar.skill.Grappling    = makeint(stf(Npchar.skill.Grappling)    + 10*stf(Npchar.quest.GrapplingModify));
	Npchar.skill.Repair       = makeint(stf(Npchar.skill.Repair)       + 10*stf(Npchar.quest.RepairModify));
	Npchar.skill.Defence      = makeint(stf(Npchar.skill.Defence)      + 10*stf(Npchar.quest.DefenseModify));
	Npchar.skill.Commerce     = makeint(stf(Npchar.skill.Commerce)     + 10*stf(Npchar.quest.CommerceModify));
	Npchar.skill.Sneak        = makeint(stf(Npchar.skill.Sneak)        + 10*stf(Npchar.quest.SneakModify));
    Npchar.skill.Pistol       = makeint(stf(Npchar.skill.Pistol)       + 10*stf(Npchar.quest.PistolModify));
    Npchar.skill.FencingLight = makeint(stf(Npchar.skill.FencingLight) + 10*stf(Npchar.quest.FencingModify));
    Npchar.skill.FencingHeavy = makeint(stf(Npchar.skill.FencingHeavy) + 10*stf(Npchar.quest.FencingModify));
    Npchar.skill.Fortune      = makeint(stf(Npchar.skill.Fortune)      + 10*stf(Npchar.quest.SneakModify));

    CorrectSkillParam(Npchar); // привести к 0-10

    SetRankFromSkill(Npchar);

    LAi_NPC_Equip(Npchar, sti(Npchar.rank), true, true); // fix 101104 выдадим все заново!!!!
	
	Npchar.reputation = rand(84) + 5;
    // пристрастие офицера -->
    Npchar.loyality = 5 + rand(10);
    if (sti(Npchar.reputation) > 41)
    {
        Npchar.alignment = "good";
		SetCharacterPerk(Npchar, "Honest");
    }
    else
    {
        Npchar.alignment = "bad";
		SetCharacterPerk(Npchar, "Rebel");
    }
    
    SetFantomHP(Npchar);
    
    Npchar.quest.OfficerPrice    = (11 + 2*sti(Npchar.rank))*(150 + MOD_SKILL_ENEMY_RATE*20) + rand(5)*10;
    Npchar.quest.OfficerLowPrice = makeint(sti(Npchar.quest.OfficerPrice)/1.5 + 0.5);
}

// Новая система прокачки офицеров
void SetOfficerParam(ref Npchar, int _type)
{
	ClearCharacterExpRate(Npchar); // трем все пороги экспы на всякий случай

	bool hasHobby = rand(1);
	string _hobbies = "";

	switch(_type)
	{
		case 0:
			Npchar.quest.officertype = "boatswain";
			// + врач, плотник, боец (средне-тяж.)
			_hobbies = "doctor,carpenter,fighter_h,fighter_m";
		break;

		case 1:
			Npchar.quest.officertype = "cannoner";
			// + боец (средне-тяж.)
			_hobbies = "fighter_h,fighter_m";
		break;

		case 2:
			Npchar.quest.officertype = "treasurer";
			// + плотник,  боец (легкий)
			_hobbies = "carpenter,fighter_l";
		break;

		case 3:
			Npchar.quest.officertype = "navigator";
			// + врач, боец (легкий-средне)
			_hobbies = "doctor,fighter_l,fighter_m";
		break;

		case 4:
			Npchar.quest.officertype = "fighter";

			// предпочтения по типу оружия
			switch(rand(3))
			{
			    case 0:
			    	Npchar.quest.officertype_fighter = "fighter_l";
			    break;
			    case 1:
			    	Npchar.quest.officertype_fighter = "fighter_m";
			    break;
			    case 2:
					Npchar.quest.officertype_fighter = "fighter_h";
			    break;
			    case 3:
					Npchar.quest.officertype_fighter = "fighter_p";
			    break;
			}

			// + врач, казначей, плотник, канонир, Боцман
			_hobbies = "doctor,treasurer,carpenter,cannoner,boatswain";
		break;

		case 5:
			Npchar.quest.officertype         = "doctor";
			// + боец (легкий)
			_hobbies = "fighter_l";
		break;
		case 6:
			Npchar.quest.officertype          = "carpenter";
			// + казначей, боец (средне-тяжелый)
			_hobbies = "treasurer,fighter_h,fighter_m";
		break;
	}

	if (hasHobby)
	{
		Npchar.quest.officertype_hobby = GetRandSubString(_hobbies);
	}

	Npchar.reputation = rand(84) + 5;
	// пристрастие офицера -->
	Npchar.loyality = 5 + rand(10);
	if (sti(Npchar.reputation) > 41)
	{
		Npchar.alignment = "good";
	}
	else
	{
		Npchar.alignment = "bad";
	}

	SetOfficerParam_SPECIAL(npchar);

	Npchar.experience = 0;
	SetOfficerParam_Skills(npchar);

	// 'рисуем' ранг
	SetRankFromSkill(Npchar);
	Npchar.rank = func_max(sti(Npchar.rank), sti(pchar.rank) + abs(4 - (sti(npchar.reputation) - 1) / 10));

	bool isEquipWeapon = true;
	if (HasStrEx(Npchar.quest.officertype, "doctor,treasurer", "|"))
	{
		isEquipWeapon = hasHobby && StrStartsWith(Npchar.quest.officertype_hobby, "fighter_");
	}

	LAi_NPC_Equip(Npchar, sti(Npchar.rank), isEquipWeapon, isEquipWeapon); // экипировка, перки
	if (sti(Npchar.reputation) > 41)
	{
		SetCharacterPerk(Npchar, "Honest");
	}
	else
	{
		SetCharacterPerk(Npchar, "Rebel");
	}
	SetFantomHP(Npchar);

	Npchar.quest.OfficerPrice    = (11 + 2*sti(Npchar.rank))*(150 + MOD_SKILL_ENEMY_RATE*20) + rand(5)*10;
	Npchar.quest.OfficerLowPrice = makeint(sti(Npchar.quest.OfficerPrice)/1.5 + 0.5);
}

void SetOfficerParam_SPECIAL(ref npchar)
{
	if (!CheckAttribute(npchar, "quest.officertype"))
	{
		SetRandSPECIAL(Npchar);
		return;
	}

	int i;
	int pirates_list[7];
	float pirates_prob_list[7];

	for (i = 0; i < 7; i++)
	{
		pirates_list[i] = 1;
		pirates_prob_list[i] = 1.0;
	}
	int pointsQty = 21 + rand(10 + abs(4 - (sti(npchar.reputation) - 1) / 10)) +
	 	rand(GetCharacterSPECIAL(pchar, SPECIAL_L) + 10 - MOD_SKILL_ENEMY_RATE + 1);
	Restrictor(&pointsQty, 21, 70 - 7);

	float primaryProbFactor = 1.5;
	float hobbyProbFactor = primaryProbFactor * 0.33;
	string offtype = Npchar.quest.officertype;
	switch(offtype)
	{
		case "navigator":
			pirates_prob_list[1] += 0.04 * primaryProbFactor;
			pirates_prob_list[4] += 0.16 * primaryProbFactor;
		break;
		case "doctor":
			pirates_prob_list[5] += 0.1 * primaryProbFactor;
			pirates_prob_list[3] += 0.1 * primaryProbFactor;
		break;
		case "carpenter":
			pirates_prob_list[5] += 0.16 * primaryProbFactor;
			pirates_prob_list[1] += 0.04 * primaryProbFactor;
		break;
		case "treasurer":
			pirates_prob_list[4] += 0.16 * primaryProbFactor;
			pirates_prob_list[3] += 0.04 * primaryProbFactor;
		break;
		case "cannoner":
			pirates_prob_list[1] += 0.08 * primaryProbFactor;
			pirates_prob_list[6] += 0.02 * primaryProbFactor;
			pirates_prob_list[4] += 0.06 * primaryProbFactor;
			pirates_prob_list[0] += 0.04 * primaryProbFactor;
		break;
		case "boatswain":
			pirates_prob_list[2] += 0.14 * primaryProbFactor;
			pirates_prob_list[4] += 0.06 * primaryProbFactor;
		break;
		case "fighter":
			if (CheckAttribute(npchar, "quest.officertype_fighter"))
			{
				offtype = Npchar.quest.officertype_fighter;
				switch(offtype)
				{
					case "fighter_l":
						pirates_prob_list[2] += 0.18 * primaryProbFactor;
						pirates_prob_list[1] += 0.02 * primaryProbFactor;
					break;
					case "fighter_m":
						pirates_prob_list[0] += 0.12 * primaryProbFactor;
						pirates_prob_list[2] += 0.08 * primaryProbFactor;
					break;
					case "fighter_h":
						pirates_prob_list[0] += 0.092 * primaryProbFactor;
						pirates_prob_list[5] += 0.016 * primaryProbFactor;
						pirates_prob_list[2] += 0.092 * primaryProbFactor;
					break;
					case "fighter_p":
						pirates_prob_list[2] += 0.1 * primaryProbFactor;
						pirates_prob_list[6] += 0.1 * primaryProbFactor;
					break;
				}
			}
		break;
	}

	if (CheckAttribute(npchar, "quest.officertype_hobby"))
	{
		offtype = Npchar.quest.officertype_hobby;
		switch(offtype)
		{
		    case "doctor":
				pirates_prob_list[5] += 0.1 * hobbyProbFactor;
				pirates_prob_list[3] += 0.1 * hobbyProbFactor;
			break;
			case "carpenter":
				pirates_prob_list[5] += 0.16 * hobbyProbFactor;
				pirates_prob_list[1] += 0.04 * hobbyProbFactor;
			break;
			case "treasurer":
				pirates_prob_list[4] += 0.16 * hobbyProbFactor;
				pirates_prob_list[3] += 0.04 * hobbyProbFactor;
			break;
			case "cannoner":
				pirates_prob_list[1] += 0.08 * hobbyProbFactor;
				pirates_prob_list[6] += 0.02 * hobbyProbFactor;
				pirates_prob_list[4] += 0.06 * hobbyProbFactor;
				pirates_prob_list[0] += 0.04 * hobbyProbFactor;
			break;
			case "boatswain":
				pirates_prob_list[2] += 0.14 * hobbyProbFactor;
				pirates_prob_list[4] += 0.06 * hobbyProbFactor;
			break;
			case "fighter_l":
				pirates_prob_list[2] += 0.18 * hobbyProbFactor;
				pirates_prob_list[1] += 0.02 * hobbyProbFactor;
			break;
			case "fighter_m":
				pirates_prob_list[0] += 0.12 * hobbyProbFactor;
				pirates_prob_list[2] += 0.08 * hobbyProbFactor;
			break;
			case "fighter_h":
				pirates_prob_list[0] += 0.092 * hobbyProbFactor;
				pirates_prob_list[5] += 0.016 * hobbyProbFactor;
				pirates_prob_list[2] += 0.092 * hobbyProbFactor;
			break;
		}
	}

	float prob_sum = 0.0;
	for (i = 0; i < 7; i++)
	{
		prob_sum += pirates_prob_list[i];
	}
	for (i = 0; i < 7; i++)
	{
		pirates_prob_list[i] /= prob_sum;
	}

	int rest = 0;
	for (int n = 0; n < pointsQty; n++)
	{
		float _rnd = Random();
		float accum_prob = 0.0;
		for (i = 0; i < 7; i++)
		{
			accum_prob += pirates_prob_list[i];
			if (_rnd <= accum_prob)
			{
				if (pirates_list[i] < 10)
				{
					pirates_list[i] += 1;
				}
				else
				{
					rest += 1;
				}
				break;
        	}
		}
	}
	while (rest > 0)
	{
		i = rand(6);
		if (pirates_list[i] < 10)
		{
			pirates_list[i] += 1;
			rest--;
		}
	}
	
	SetSPECIAL(npchar, 
		pirates_list[0],
		pirates_list[1], 
		pirates_list[5], 
		pirates_list[3], 
		pirates_list[4],
		pirates_list[2], 
		pirates_list[6]
	);
}

void SetOfficerParam_Skills(ref npchar)
{
	string skillName;
	int i;

	InitStartParam(npchar); // скиллы от пиратес
	ClearCharacterExpRate(Npchar); // трем все пороги экспы на всякий случай

	string hobbyType = "";
	if (CheckAttribute(npchar, "quest.officertype_hobby"))
	{
		hobbyType = Npchar.quest.officertype_hobby;
	}
	string primaryType = Npchar.quest.officertype;
	if (primaryType == "fighter")
	{
		primaryType = Npchar.quest.officertype_fighter;
	}

	for (i=1; i<15; i++)
	{
		skillName = GetSkillNameByIdx(i);
		float primaryValue = SetOfficerParam_Skills_GetPrimaryValue(npchar);
		float restValue = SetOfficerParam_Skills_GetRestValue();
		if (hobbyType != "")
		{
		    primaryValue *= 0.7;
		}
		int tempValue = makeint(SetOfficerParam_Skills_GetSkillValue(skillName, primaryType, primaryValue, restValue));
		tempValue = func_max(tempValue, makeint(SetOfficerParam_Skills_GetSkillValue(skillName, hobbyType, primaryValue, restValue)));
		tempValue = func_max(tempValue, sti(npchar.skill.(skillName)));

		npchar.skill.(skillName) = tempValue;
	}

	CorrectSkillParam(Npchar); // приведём к 0-100
}

float SetOfficerParam_Skills_GetSkillValue(string skillName, string type, float primaryVal, float restVal)
{
	float tempValue;
	switch(type)
	{
		case "treasurer": if (skillName == SKILL_COMMERCE)  return primaryVal; break;
		case "boatswain":
			if (skillName == SKILL_GRAPPLING) return primaryVal;
			if (skillName == SKILL_LEADERSHIP) return primaryVal * (1 - 0.3);
		break;
		case "navigator":
			if (skillName == SKILL_SAILING)   return primaryVal;
			if (skillName == SKILL_LEADERSHIP) return primaryVal * (1 - 0.3);
		break;
		case "doctor":    if (skillName == SKILL_DEFENCE)   return primaryVal; break;
		case "carpenter": if (skillName == SKILL_REPAIR)    return primaryVal; break;
		case "cannoner":
			if (skillName == SKILL_ACCURACY)  return primaryVal;
			if (skillName == SKILL_CANNONS)   return primaryVal;
		break;
		case "fighter_l":
			if (skillName == SKILL_F_LIGHT) return primaryVal;
			if (skillName == SKILL_FENCING) return primaryVal * (1 - 0.3);
			if (skillName == SKILL_PISTOL)  return primaryVal * (1 - 0.3);
		break;
		case "fighter_m":
			if (skillName == SKILL_FENCING) return primaryVal;
			if (skillName == SKILL_F_LIGHT) return primaryVal * (1 - 0.3);
			if (skillName == SKILL_F_HEAVY) return primaryVal * (1 - 0.3);
			if (skillName == SKILL_PISTOL)  return primaryVal * (1 - 0.3);
		break;
		case "fighter_h":
			if (skillName == SKILL_F_HEAVY) return primaryVal;
			if (skillName == SKILL_FENCING) return primaryVal * (1 - 0.3);
			if (skillName == SKILL_PISTOL)  return primaryVal * (1 - 0.3);
		break;
		case "fighter_p":
			if (skillName == SKILL_PISTOL)  return primaryVal;
			if (skillName == SKILL_FENCING) return primaryVal * (1 - 0.3);
			if (skillName == SKILL_F_LIGHT) return primaryVal * (1 - 0.3);
		break;
	}

	tempValue = restVal;
	Restrictor(&tempValue, 0.0, 70.0);
	return tempValue;
}

float SetOfficerParam_Skills_GetPrimaryValue(ref npchar)
{
	int rank = sti(pchar.rank);
	int rep_bias = abs(4 - (sti(npchar.reputation) - 1) / 10);
	if (rank <= 10)
        return 20 + 3.4 * (rank - 1) + (5.0 - frandsmall(10.0 - rep_bias));
    else
        return 50 + 2.65 * (rank - 10) + (10.0 - frandsmall(20.0 - 2*rep_bias));
}

float SetOfficerParam_Skills_GetRestValue()
{
	int rank = sti(pchar.rank);
	return 10 + 2.0 * (rank - 1) + (5.0 - frandsmall(15.0));
}

///////////////////////////////////////////////////////////////////////////

int FindFreeRandomOfficer()
{
	int Counter, OfficerIdx;
	string OfficerId;
	// special -->
	if (GetCharacterMaxOfficersQty(Pchar) <= (GetOfficerPassengerQuantity(Pchar) + GetCompanionQuantity(Pchar) - 1)) return -1;
	return 1;
}
void LandEnc_OfficerHired()
{
	ref sld = &Characters[sti(Pchar.questTemp.HiringOfficerIDX)];
    sld.Money = 0; // деньги

	AddPassenger(pchar, sld, false);
	
	LAi_RemoveLoginTime(sld); // для ходоков
	DeleteAttribute(sld, "walker");

	sld.location = "None";
	sld.Dialog.CurrentNode = "hired";
	
	sld.Payment = true;  // признак офицера для бонусов от предметов; true - просит зарплату
	sld.DontClearDead = true;  // не убирать труп
	sld.SaveItemsForDead = true; //оставлять эквип при смерти
	
	DeleteAttribute(Pchar, "questTemp.HiringOfficerIDX");
	DeleteAttribute(sld, "LifeDay"); // постоянный
	DeleteAttribute(sld, "watchBoxes"); //мало ли
	SaveCurrentNpcQuestDateParam(sld, "HiredDate"); // дата найма
}

void LandEnc_OfficerStay()
{
    SetCharacterTask_Stay(Characters[makeint(Pchar.questTemp.HiringOfficerIDX)]);
    Characters[makeint(Pchar.questTemp.HiringOfficerIDX)].chr_ai.tmpl = LAI_TMPL_STAY;
    DeleteAttribute(Pchar, "questTemp.HiringOfficerIDX");
}   

void LandEnc_OfficerFired()
{
	ref sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
	CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
	RemovePassenger(Pchar, sld);
	RemoveCharacterCompanion(pchar, sld);
	LAi_SetCitizenType(sld);
	if (sld.sex != "woman")
	{
    	sld.greeting = "Gr_Officer_Fired";
    }
    LAi_group_MoveCharacter(sld, sld.id + "_group");
    sld.LifeDay = 0; // стереть при выходе
    DeleteAttribute(sld, "Payment"); // признак офицера для бонусов предметов  
	DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");
	if(sld.id == "Douglas") // TODO: Ещё бы слух добавить и опции при захвате города
	{
		DeleteAttribute(pchar, "quest.Duglas_Officer");
		LocatorReloadEnterDisable("PortSpein_town", "houseH3", true);
	}
	if (Get_My_Cabin() == sld.location)
   	{ //HardCoffee фикс для увольнения в каюте (чтобы ушёл)
    	if (CheckAttribute(loadedLocation, "locators.reload.reload1"))
    	{
    		LAi_SetActorTypeNoGroup(sld);
    		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 4.0);
    	}
    	else ChangeCharacterAddress(sld, "none", "");
    }
    else sld.location = "none";
}

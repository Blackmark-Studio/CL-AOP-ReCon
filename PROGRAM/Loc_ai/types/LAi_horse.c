#define LAI_TYPE_HORSE			"horse"

#define HORSE_STAY_ANIM_NUM		5
#define HORSE_SIT_ANIM_NUM		4

void LAi_SetHorseStayAnimation(aref chr)
{
	if (!IsEntity(chr)) return;

	int i, iNum;
	string Attr;
	BeginChangeCharacterActions(chr);
	for (i = 1; i < 12; i++)
	{
		iNum = i;
		while (iNum > HORSE_STAY_ANIM_NUM) { iNum = iNum - HORSE_STAY_ANIM_NUM; }
		Attr = "i" + i;
		chr.actions.idle.(Attr) = "Horse_Stay_idle_" + iNum;
	}
	EndChangeCharacterActions(chr);
}

void LAi_SetHorseSitAnimation(aref chr)
{
	if (!IsEntity(chr)) return;

	int i, iNum;
	string Attr;
	BeginChangeCharacterActions(chr);
	for (i = 1; i < 12; i++)
	{
		iNum = i;
		while (iNum > HORSE_SIT_ANIM_NUM) { iNum = iNum - HORSE_SIT_ANIM_NUM; }
		Attr = "i" + i;
		chr.actions.idle.(Attr) = "Horse_Sit_idle_" + iNum;
	}
	EndChangeCharacterActions(chr);
}


//------------------------------------------------------------------------------------------
//Инициализация
//------------------------------------------------------------------------------------------

void LAi_type_horse_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_HORSE;
	LAi_tmpl_stay_InitTemplate(chr);

	if (!CheckAttribute(chr, "horse"))
	{
		chr.horse = "HorseStay";
	}

	switch (chr.horse)
	{
		case "HorseStay":	LAi_SetHorseStayAnimation(chr);	break;
		case "HorseSit":	LAi_SetHorseSitAnimation(chr);	break;
		default:			LAi_SetHorseStayAnimation(chr);	break;
	}

	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}


//------------------------------------------------------------------------------------------
//Процессирование типа персонажа
//------------------------------------------------------------------------------------------

void LAi_type_horse_CharacterUpdate(aref chr, float dltTime)
{
	if (chr.chr_ai.tmpl != LAI_TMPL_DIALOG)
	{
		if (rand(1000) == 313)
		{
			LAi_CharacterPlaySound(chr, "female-sit");
		}
	}
}

//Загрузка персонажа в локацию
bool LAi_type_horse_CharacterLogin(aref chr)
{
	return true;
}

//Выгрузка персонажа из локации
bool LAi_type_horse_CharacterLogoff(aref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_horse_TemplateComplite(aref chr, string tmpl)
{
}

//Сообщить о желании завести диалог
void LAi_type_horse_NeedDialog(aref chr, aref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_horse_CanDialog(aref chr, aref by)
{
	//Если уже говорим - откажем
	if (chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return false;
	if (CheckAttribute(chr, "horse") && chr.horse == "HorseSit") return false;
	return true;
}

//Начать диалог
void LAi_type_horse_StartDialog(aref chr, aref by)
{
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//Закончить диалог
void LAi_type_horse_EndDialog(aref chr, aref by)
{
	LAi_CharacterRestoreAy(chr);
	LAi_tmpl_stay_InitTemplate(chr);
	if (CheckAttribute(chr, "horse") && chr.horse == "HorseSit")
	{
		LAi_SetHorseSitAnimation(chr);
	}
	else
	{
		LAi_SetHorseStayAnimation(chr);
	}
	chr.chr_ai.type.notalk = 10.0 + rand(20);
}

//Персонаж выстрелил
void LAi_type_horse_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}

//Персонаж атакован
void LAi_type_horse_Attacked(aref chr, aref by)
{
	if (chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
	{
		LAi_tmpl_dialog_StopNPC(chr);
		LAi_type_horse_CharacterUpdate(chr, 0.0);
	}
}

int LAi_type_horse_FindNearEnemy(aref chr)
{
	if (LAi_grp_alarmactive == true)
	{
		int num = FindNearCharacters(chr, 5.0, -1.0, -1.0, 0.001, false, true);
		if (num <= 0)
		{
			chrFindNearCharacters[0].index = "-1";
			return -1;
		}
		for (int i = 0; i < num; i++)
		{
			int idx = sti(chrFindNearCharacters[i].index);
			if (LAi_group_IsEnemy(chr, &Characters[idx])) return idx;
		}
	}
	return -1;
}

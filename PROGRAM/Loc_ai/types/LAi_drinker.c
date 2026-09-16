#define LAI_TYPE_DRINKER		"drinker"


//------------------------------------------------------------------------------------------
//Анимации
//------------------------------------------------------------------------------------------

void LAi_SetDrinkerAnimation(aref chr)
{
	if (!IsEntity(chr)) return;
	BeginChangeCharacterActions(chr);
	chr.actions.idle.i1 = "Drink_Stand_1";
	chr.actions.idle.i2 = "Drink_Stand_2";
	chr.actions.idle.i3 = "Drink_Stand_3";
	chr.actions.idle.i4 = "Drink_Stand_4";
	chr.actions.idle.i5 = "Drink_Stand_5";
	chr.actions.idle.i6 = "Drink_Stand_6";
	chr.actions.dead.d1 = "Drink_SitGround_Death";
	chr.actions.dead.d2 = "Drink_SitGround_Death";
	chr.actions.HitNoFight = "HitNoFightSit";
	EndChangeCharacterActions(chr);
}

void LAi_SetDrinkerSitAnimation(aref chr)
{
	if (!IsEntity(chr)) return;
	BeginChangeCharacterActions(chr);
	chr.actions.idle.i1 = "Drink_SitGround_1";
	chr.actions.idle.i2 = "Drink_SitGround_2";
	chr.actions.idle.i3 = "Drink_SitGround_3";
	chr.actions.idle.i4 = "Drink_SitGround_4";
	chr.actions.idle.i5 = "Drink_SitGround_1";
	chr.actions.dead.d1 = "Drink_SitGround_Death";
	chr.actions.dead.d2 = "Drink_SitGround_Death";
	chr.actions.HitNoFight = "HitNoFightSit";
	EndChangeCharacterActions(chr);
}

void LAi_SetDrinkerSitBenchAnimation(aref chr)
{
	if (!IsEntity(chr)) return;
	BeginChangeCharacterActions(chr);
	chr.actions.idle.i1 = "Drink_SitBench_1";
	chr.actions.idle.i2 = "Drink_SitBench_2";
	chr.actions.idle.i3 = "Drink_SitBench_3";
	chr.actions.idle.i4 = "Drink_SitBench_4";
	chr.actions.dead.d1 = "Drink_SitBench_Death";
	chr.actions.dead.d2 = "Drink_SitBench_Death";
	chr.actions.HitNoFight = "HitNoFightSit";
	EndChangeCharacterActions(chr);
}


//------------------------------------------------------------------------------------------
//Инициализация
//------------------------------------------------------------------------------------------

void LAi_type_drinker_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	DeleteAttribute(chr, "chr_ai.type");
	chr.chr_ai.type = LAI_TYPE_DRINKER;
	LAi_tmpl_stay_InitTemplate(chr);

	if (CheckAttribute(chr, "drinkersit"))
	{
		LAi_SetDrinkerSitAnimation(chr);
	}
	else
	{
		if (CheckAttribute(chr, "drinkersitbench")) LAi_SetDrinkerSitBenchAnimation(chr);
		else LAi_SetDrinkerAnimation(chr);
	}
}


//------------------------------------------------------------------------------------------
//Процессирование типа персонажа
//------------------------------------------------------------------------------------------

void LAi_type_drinker_CharacterUpdate(aref chr, float dltTime)
{

}

//Загрузка персонажа в локацию
bool LAi_type_drinker_CharacterLogin(aref chr)
{
	return true;
}

//Выгрузка персонажа из локации
bool LAi_type_drinker_CharacterLogoff(aref chr)
{
	return true;
}

void LAi_type_drinker_TemplateComplite(aref chr, string tmpl)
{
}

void LAi_type_drinker_NeedDialog(aref chr, aref by)
{
}

bool LAi_type_drinker_CanDialog(aref chr, aref by)
{
	return false;
}

//Начать диалог
void LAi_type_drinker_StartDialog(aref chr, aref by)
{
}

//Закончить диалог
void LAi_type_drinker_EndDialog(aref chr, aref by)
{
}

//Персонаж выстрелил
void LAi_type_drinker_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}

//Персонаж атакован
void LAi_type_drinker_Attacked(aref chr, aref by)
{
}

//Найти врага
int LAi_type_drinker_FindNearEnemy(aref chr)
{
	return -1;
}

/*
Тип: стоячий, всегда стоит, отвечает на диалоги, никогда не боится

	Используемые шаблоны:
		stay
		dialog
		goto
*/

#define LAI_TYPE_PATROL        "patrol"

//Инициализация
void LAi_type_patrol_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if (CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}
	else
	{
		if (chr.chr_ai.type != LAI_TYPE_PATROL) isNew = true;
	}
	if (isNew)
	{
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_PATROL;
		chr.chr_ai.type.locator = "";
		chr.chr_ai.type.state = "stay";
		chr.chr_ai.type.time = rand(5);
		chr.chr_ai.type.checkPatrol = "0";
		//chr.chr_ai.type.stealthcough = "0.0";
		chr.chr_ai.type.bottle = rand(10) + 2;
		chr.chr_ai.type.checkTarget = 0;
		LAi_tmpl_stay_InitTemplate(chr);
	}
	else
	{
		if (!CheckAttribute(chr, "chr_ai.type.locator")) chr.chr_ai.type.locator = "";
		if (!CheckAttribute(chr, "chr_ai.type.state")) chr.chr_ai.type.state = "stay";
		if (!CheckAttribute(chr, "chr_ai.type.time")) chr.chr_ai.type.time = rand(5);
		if (!CheckAttribute(chr, "chr_ai.type.checkPatrol")) chr.chr_ai.type.checkPatrol = "0";
	}
	//Установим анимацию персонажу
	if (chr.model.animation == "mushketer" && !CheckAttribute(chr, "MusketOutfit"))
	{
		LAi_NPC_MushketerEquip(chr);
	}
	else
	{
		LAi_SetDefaultStayAnimation(chr);
	}
	SendMessage(&chr, "lsl", MSG_CHARACTER_EX_MSG, "SetFightWOWeapon", false);
}

//Процессирование типа персонажа
void LAi_type_patrol_CharacterUpdate(aref chr, float dltTime)
{
	if (LAi_IsDead(chr)) return;
	int trg = -1;
	//Если болтаем, то ничего пока не меняем
	if (chr.chr_ai.tmpl == LAI_TMPL_DIALOG) return;

	// boal  лечимся -->
	float fCheck = stf(chr.chr_ai.type.bottle) - dltTime;
	if (fCheck < 0)
	{
		chr.chr_ai.type.bottle = 5.0;
		if (!LAi_IsBottleWork(chr, 1) && MOD_SKILL_ENEMY_RATE > 2) // TODO > energy
		{
			string btl = "";
			float dhlt;
			if (LAi_GetCharacterRelHP(chr) < 0.75)
			{
				dhlt = LAi_GetCharacterMaxHP(chr) - LAi_GetCharacterHP(chr);
				btl = FindHealthForCharacter(&Characters[sti(chr.index)], dhlt);
				DoCharacterUsedItem(&Characters[sti(chr.index)], btl);
				chr.chr_ai.type.bottle = 10.0;
			}
		}
	}
	else chr.chr_ai.type.bottle = fCheck;
	// boal  лечимся <--
	float radius, time;
	int i;
	if (chr.chr_ai.tmpl != LAI_TMPL_FIGHT && !LAi_grp_alarmactive)
	{
		//Ищем цель
		trg = LAi_group_GetTarget(chr);
		if (trg < 0)
		{
			/*time = stf(chr.chr_ai.type.stealthcough) - dltTime; //Кашель, если прошли проверку на скрытность
			if (time < 0) time = 0;
			chr.chr_ai.type.stealthcough = time;*/

			time = stf(TEV.checkPirateNoBlade) - dltTime;
			if (time < 0) time = 0;
			TEV.checkPirateNoBlade = time;

			//Патрулирование
			time = stf(chr.chr_ai.type.checkPatrol) - dltTime;
			if (time < 0) time = 0; //HardCoffee обнулим таймер, чтоб не уходил в сильный минус
			chr.chr_ai.type.checkPatrol = time;

			if (true) //if (time <= 0.0) //Чтобы адекватно реагировал на оружие и квесты
			{
				//Анализируем окружающих персонажей
				if (isDay() || GetRelation2BaseNation(sti(chr.nation)) != RELATION_ENEMY)
					radius = 3.0; //eddy. дневной и начной патруль - разные, ночью смотрят дальше
				else
				{
					if (CheckCharacterPerk(pchar, "Trustworthy")) // KZ > перк "Искусство обмана" чуть снижает радиус обнаружения у патрульных
						radius = 5.0;
					else
						radius = 6.0;
				}
				int num = FindNearCharacters(chr, radius, -1.0, 180.0, 0.1, true, true);
				if (num > 0)
				{
					for (i = 0; i < num; i++)
					{
						if (nMainCharacterIndex == sti(chrFindNearCharacters[i].index))
						{
							/*if (!HasStrEx(loadedlocation.id.label, "Incquisitio,Mayak2,Prison", "|") && !CheckNationLicence(sti(chr.nation)) && stf(chr.chr_ai.type.checkPatrol) > 0.0 && !HasStrEx(GetCharCurAni(pchar), "idle_,walk,turn ", "|"))
							{
								if (GetNationRelation2MainCharacter(sti(chr.nation)) == RELATION_ENEMY || GetNationRelation(sti(chr.nation), GetBaseHeroNation()) == RELATION_ENEMY || ChangeCharacterNationReputation(pchar, sti(chr.nation), 0) <= -10)
									chr.chr_ai.type.checkPatrol = "0.0";
							}*/ //HardCoffee TODO: добавлено было недавно, но временно комменчу, так как весь смысл от проверок на скрытность теряется
							break;
						}
					}
					if (i < num) //Нашли главного персонажа
					{	//с начала проверим на обнажённый клинок, для того, что бы при checkPatrol == 0 обратится к гг с правильной фразой
						if (LAi_CheckForWeapon(chr))
						{
							LAi_SoldierTestControl(chr, true, false);
							return;
						}
						else if (time <= 0.0)
						{
							LAi_SoldierTestControl(chr, false, false);
							return;
						}
					}
					else
					{
						trg = sti(chrFindNearCharacters[0].index);
					}
				}
			}
			//Анализируем состояние ходьбы
			if (chr.chr_ai.tmpl == LAI_TMPL_GOTO)
			{
				if (LAi_tmpl_goto_IsWait(chr))
				{
					if (rand(100) < 20) LAi_type_patrol_Goto(chr);
				}
				return;
			}
			//Иногда звучим
			if (rand(1000) == 125)
			{
				LAi_CharacterPlaySound(chr, "sigh");
			}
			//Стоим
			time = stf(chr.chr_ai.type.time) - dltTime;
			chr.chr_ai.type.time = time;
			if (time > 0.0)
			{
				if (trg >= 0) CharacterTurnByChr(chr, &Characters[trg]);
				return;
			}
			else
			{
				LAi_type_patrol_Goto(chr);
				return;
			}

		}
		else
		{
			//Начинаем атаку
			chr.chr_ai.type.state = "fight";
			if (CheckAttribute(loadedlocation, "noFight")) //Rosarak. fix странных вставаний, но ГГ оружие всё равно не дадим
			{
				TEV.noFight = ""; //на момент
				TEV.noFight.loc = loadedlocation.id;
				DeleteAttribute(loadedlocation, "noFight");
			}
			if (!LAi_tmpl_SetFight(chr, &Characters[trg]))
			{
				//Несмогли инициировать шаблон
				LAi_type_patrol_Stay(chr);
			}
			else chr.chr_ai.type.checkTarget = rand(4) + 3; //таймер на проверялку расстояния до таргета
			if (CheckAttribute(&TEV, "noFight")) LAi_MethodDelay("FightDisable", 1.0);
		}
	}
	else
	{
		//Проверим на правильность цель
		bool isValidate = false;
		trg = LAi_tmpl_fight_GetTarget(chr);
		fCheck = stf(chr.chr_ai.type.checkTarget) - dltTime;
		chr.chr_ai.type.checkTarget = fCheck;
		if (trg >= 0)
		{
			if (LAi_group_ValidateTarget(chr, &Characters[trg]))
			{
				if (!LAi_tmpl_fight_LostTarget(chr))
				{
					isValidate = true;
					if (stf(LAi_grp_relations.distance) > 2.0 && fCheck < 0) //цель далеко, попробуем сменить на ближайшую
						isValidate = false;
					if (characters[trg].chr_ai.type == LAI_TYPE_INJURE) //цель лежит, переключаемся с лежачей
						isValidate = false;
				}
			}
		}
		if (!isValidate)
		{
			//Ищем новую цель
			trg = LAi_group_GetTarget(chr);
			if (trg >= 0)
			{
				chr.chr_ai.type.state = "fight";
				if (!LAi_tmpl_SetFight(chr, &Characters[trg]))
				{
					//Несмогли инициировать шаблон
					LAi_type_patrol_Stay(chr);
				}
				else chr.chr_ai.type.checkTarget = rand(4) + 3; //таймер на проверялку расстояния до таргета
			}
			else
			{
				LAi_type_patrol_Stay(chr);
			}
		}
	}
}

//Загрузка персонажа в локацию
bool LAi_type_patrol_CharacterLogin(aref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_patrol_CharacterLogoff(aref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_patrol_TemplateComplite(aref chr, string tmpl)
{
	if (tmpl == "goto")
	{
		LAi_type_patrol_Stay(chr);
		CharacterTurnByLoc(chr, "goto", chr.chr_ai.type.locator);
		chr.chr_ai.type.locator = "";
	}
}

//Сообщить о желании завести диалог
void LAi_type_patrol_NeedDialog(aref chr, aref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_patrol_CanDialog(aref chr, aref by)
{
	if (chr.chr_ai.type.state == "dialog")
	{
		if (sti(by.index) == nMainCharacterIndex)
		{
			chr.chr_ai.type.state = "stay";
			return true;
		}
		return false;
	}
	if (LAi_CanNearEnemy(chr, 5.0)) return false;
	if (chr.chr_ai.tmpl == LAI_TMPL_STAY) return true;
	if (chr.chr_ai.tmpl == LAI_TMPL_GOTO) return true;
	if (sti(by.index) == nMainCharacterIndex)
	{
		if (chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
		{
			if (LAi_tmpl_dialog_StopNPC(chr)) return true;
		}
	}
	return false;
}

//Начать диалог
void LAi_type_patrol_StartDialog(aref chr, aref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//Закончить диалог
void LAi_type_patrol_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
	bool isSet = false;
	if (chr.chr_ai.type.state == "goto")
	{
		if (chr.chr_ai.type.locator != "")
		{
			LAi_tmpl_goto_InitTemplate(chr);
			LAi_tmpl_goto_SetLocator(chr, "goto", chr.chr_ai.type.locator, -1.0);
			isSet = true;
		}
	}
	if (!isSet)
	{
		LAi_type_patrol_Stay(chr);
	}
}

//Персонаж выстрелил
void LAi_type_patrol_Fire(aref attack, aref enemy, float kDist, bool isFindedEnemy)
{
}

//Персонаж атакован
void LAi_type_patrol_Attacked(aref chr, aref by)
{
	if (chr.chr_ai.tmpl == LAI_TMPL_DIALOG)
	{
		LAi_tmpl_dialog_StopNPC(chr);
	}
	//если наносящий удар уже таргет, нефиг крутить код и переназначать цель
	if (LAi_tmpl_fight_GetTarget(chr) == sti(by.index)) return;
	//Своих пропускаем
	if (!LAi_group_IsEnemy(chr, by)) return;
	//boal fix ai -->
	float dist = -1.0;

	if (!GetCharacterDistByChr3D(chr, by, &dist)) return;
	if (dist < 0.0) return;
	if (dist > 20.0) return;
	//Натравливаем
	LAi_tmpl_SetFight(chr, by);
	// boal <--
	if (rand(100) > 95 && !LAi_IsDead(chr) && !LAi_IsDead(pchar)) LAi_CharacterPlaySound(chr, "warrior");
}

//Проверить персонажа с заданной вероятностью
void LAi_type_patrol_Stay(aref chr)
{
	chr.chr_ai.type.time = 2 + rand(20);
	chr.chr_ai.type.state = "stay";
	LAi_tmpl_stay_InitTemplate(chr);
}

//Отправить персонажа в новую точку
void LAi_type_patrol_Goto(aref chr)
{
	//Идём в новую точку
	string newloc;
	if (CheckAttribute(chr, "CityType") && chr.CityType == "fortPatrol")
	{
		string sTemp = chr.location.locator;
		newloc = "goto" + rand(6) + GetSymbol(sTemp, 7);
	}
	else
	{
		newloc = LAi_FindRandomLocator("goto");
		//Log_TestInfo("Ghf: " + chr.id); спамит сильно
	}
	if (newloc != "")
	{
		LAi_tmpl_goto_InitTemplate(chr);
		LAi_tmpl_goto_SetLocator(chr, "goto", newloc, -1.0);
		chr.chr_ai.type.state = "goto";
		chr.chr_ai.type.locator = newloc;
	}
}

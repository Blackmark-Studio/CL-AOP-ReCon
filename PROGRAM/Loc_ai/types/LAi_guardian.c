/*
Тип: охраник

	Используемые шаблоны:
		stay
		talk
		fight		
		goto
*/

#define LAI_TYPE_GUARDIAN    "guardian"

//Инициализация
void LAi_type_guardian_Init(aref chr)
{
	DeleteAttribute(chr, "location.follower");
	bool isNew = false;
	if (CheckAttribute(chr, "chr_ai.type") == false)
	{
		isNew = true;
	}
	else
	{
		if (chr.chr_ai.type != LAI_TYPE_GUARDIAN) isNew = true;
	}
	if (isNew == true)
	{
		//Новый тип
		DeleteAttribute(chr, "chr_ai.type");
		chr.chr_ai.type = LAI_TYPE_GUARDIAN;
		chr.chr_ai.type.enemy = "";
		chr.chr_ai.type.etime = "0";
		chr.chr_ai.type.wait = "";
		chr.chr_ai.type.checkGuard = "0.0"; //для таймера на инициализацию диалога. eddy
		//chr.chr_ai.type.stealthcough = "0.0";
		chr.chr_ai.type.bottle = rand(10) + 2;
		//Установим шаблон стояния
		LAi_tmpl_stay_InitTemplate(chr);
	}
	//Востанавливаем состояние
	else if (chr.chr_ai.type.wait == "attack") LAi_type_guardian_CmdAttack(chr);
	else if (chr.chr_ai.type.wait == "return") LAi_type_guardian_Return(chr);

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
	//Сохраним адрес как точку охраны
	chr.chr_ai.type.group = chr.location.group;
	chr.chr_ai.type.locator = chr.location.locator;
}

//Процессирование типа персонажа
void LAi_type_guardian_CharacterUpdate(aref chr, float dltTime)
{
	if (LAi_IsDead(chr)) return;
	aref type;
	int trg, t;
	float time, dist;
	makearef(type, chr.chr_ai.type);
	//Режим ожидания
	if (type.wait != "") return;

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

	//Нормальная работа
	string tmpl = chr.chr_ai.tmpl;
	if (tmpl == LAI_TMPL_DIALOG) return;
	if (tmpl == LAI_TMPL_FIGHT)
	{
		bool isValidate = false;
		trg = LAi_tmpl_fight_GetTarget(chr);
		//Пробуем обновить оптимальную цель
		time = stf(type.etime) - dltTime;
		type.etime = time;
		if (trg >= 0)
		{
			if (LAi_group_ValidateTarget(chr, &Characters[trg]))
			{
				if (!LAi_tmpl_fight_LostTarget(chr))
				{
					isValidate = true;
					if (stf(LAi_grp_relations.distance) > 2.0 && fCheck < 0) //цель далеко, попробуем сменить на ближайшую
						isValidate = false;
					if (characters[trg].chr_ai.type == LAI_TYPE_INJURE)
						isValidate = false;
				}
			}
		}
		//Если текущая цель не действительна, получим новую
		if (!isValidate)
		{
			//Ищем новую цель
			trg = LAi_group_GetTarget(chr);
			if (trg < 0)
			{
				//Переходим в режим ожидания
				LAi_tmpl_fight_SetWaitState(chr);
				LAi_type_guardian_Return(chr);
			}
			else
			{
				//Натравливаем на новую цель
				LAi_type_guardian_CmdAttack_Now(chr, trg);
				if (rand(100) < 10)
				{
					LAi_CharacterPlaySound(chr, "warrior");
				}
			}
		}
	}
	else
	{
		if (tmpl == LAI_TMPL_STAY)
		{
			if (rand(1000) == 125)
			{
				LAi_CharacterPlaySound(chr, "sigh");
			}
			//Проверим наличие врагов
			trg = LAi_group_GetTarget(chr);
			if (trg >= 0)
			{
				if (CheckAttribute(loadedlocation, "noFight")) //Rosarak. fix странных вставаний, но ГГ оружие всё равно не дадим
				{
					TEV.noFight = ""; //на момент
					TEV.noFight.loc = loadedlocation.id;
					DeleteAttribute(loadedlocation, "noFight");
				}
				chr.chr_ai.type.enemy = trg;
				LAi_type_guardian_CmdAttack(chr);
				if (CheckAttribute(&TEV, "noFight")) LAi_MethodDelay("FightDisable", 1.0);
			}
			else
			{
				//eddy. активация диалога у гарда c атрибутом протектора если не враг и если это не колония базовой нации.
				if (!LAi_grp_alarmactive)
				{
					/*time = stf(chr.chr_ai.type.stealthcough) - dltTime; //Кашель, если прошли проверку на скрытность
					if (time < 0) time = 0;
					chr.chr_ai.type.stealthcough = time;*/

					time = stf(TEV.checkPirateNoBlade) - dltTime;
					if (time < 0) time = 0;
					TEV.checkPirateNoBlade = time;

					time = stf(chr.chr_ai.type.checkGuard) - dltTime;
					if (time < 0) time = 0; //HardCoffee обнулим таймер, чтоб не уходил в сильный минус
					chr.chr_ai.type.checkGuard = time;

					//Анализируем окружающих персонажей
					int num = FindNearCharacters(chr, 4.0, -1.0, 180.0, 0.1, true, true);
					int i;
					if (num > 0)
					{
						for (i = 0; i < num; i++)
						{
							if (nMainCharacterIndex == sti(chrFindNearCharacters[i].index))
							{
								/*if (!HasStrEx(loadedlocation.id.label, "Incquisitio,Mayak2,Prison", "|") && !CheckNationLicence(sti(chr.nation)) && stf(chr.chr_ai.type.checkGuard) > 0.0 && !HasStrEx(GetCharCurAni(pchar), "idle_,walk,turn ", "|"))
								{
									if (GetNationRelation2MainCharacter(sti(chr.nation)) == RELATION_ENEMY || GetNationRelation(sti(chr.nation), GetBaseHeroNation()) == RELATION_ENEMY || ChangeCharacterNationReputation(pchar, sti(chr.nation), 0) <= -10)
										chr.chr_ai.type.checkGuard = "0.0";
								}*/ //HardCoffee добавлено было недавно, но временно комменчу, так как весь смысл от проверок на скрытность теряется
								break;
							}
						}
						if (i < num) //Нашли главного персонажа
						{	//с начала проверим на обнажённый клинок, для того, что бы при checkPatrol == 0 обратится к гг с правильной фразой
							if (LAi_CheckForWeapon(chr))
							{
							    LAi_SoldierTestControl(chr, true, true);
							    return;
							}
							else if (stf(chr.chr_ai.type.checkGuard) <= 0.0 && CheckAttribute(chr, "protector"))
							{	//HardCoffee TODO: этого атрибута нет у привратников в тюрьмах, они не обратятся к гг пока он сам не заговорит с ними
								LAi_SoldierTestControl(chr, false, true);
								return;
							}
							else return; //TODO: Посмотреть KZ, если ГГ рядом и не вызывает подозрений, то стражнику не надо возвращаться на пост? (следующий if)
						}
						else
						{
							trg = sti(chrFindNearCharacters[0].index);  //TODO: Посмотреть KZ, дальше trg никак не используется (там else), зачем присвоение?
						}
					}
				}
				//Проверяем дистанцию до точки охраны
				dist = -1.0;
				if (GetCharacterDistByLoc(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator, &dist))
				{
					if (dist > 1.0)
					{
                        chr.ToPointForced = "";
						LAi_tmpl_runto_InitTemplate(chr);
						LAi_tmpl_runto_SetLocator(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator, -1.0);
					}
					else
					{
						CharacterTurnByLoc(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator);
					}
				}
				else
				{
					CharacterTurnByLoc(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator);
				}
			}
		}
		else
		{
			//Проверим наличие врагов
			trg = LAi_group_GetTarget(chr);
			if (trg >= 0)
			{
				chr.chr_ai.type.enemy = trg;
				LAi_type_guardian_CmdAttack(chr);
			}
			else
			{
				if (tmpl != LAI_TMPL_RUNTO)
				{
					LAi_tmpl_stay_InitTemplate(chr);
				}
				else
				{
					if (LAi_tmpl_runto_IsStay(chr))
					{
						LAi_tmpl_stay_InitTemplate(chr);
					}
				}
			}
		}
	}
}

//Загрузка персонажа в локацию
bool LAi_type_guardian_CharacterLogin(aref chr)
{
	return true;
}

//Выгрузка персонажа из локацию
bool LAi_type_guardian_CharacterLogoff(aref chr)
{
	return true;
}

//Завершение работы темплейта
void LAi_type_guardian_TemplateComplite(aref chr, string tmpl)
{
	LAi_tmpl_stay_InitTemplate(chr);
	CharacterTurnByLoc(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator);
}

//Сообщить о желании завести диалог
void LAi_type_guardian_NeedDialog(aref chr, aref by)
{
}

//Запрос на диалог, если возвратить true то в этот момент можно начать диалог
bool LAi_type_guardian_CanDialog(aref chr, aref by)
{
	//Если просто стоим, то согласимся на диалог
	if (chr.chr_ai.tmpl == LAI_TMPL_STAY)
	{
		if (LAi_CanNearEnemy(chr, 5.0)) return false;
		return true;
	}
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
void LAi_type_guardian_StartDialog(aref chr, aref by)
{
	//Если мы пасивны, запускаем шаблон без времени завершения
	LAi_CharacterSaveAy(chr);
	CharacterTurnByChr(chr, by);
	LAi_tmpl_SetActivatedDialog(chr, by);
}

//Закончить диалог
void LAi_type_guardian_EndDialog(aref chr, aref by)
{
	LAi_tmpl_stay_InitTemplate(chr);
	LAi_CharacterRestoreAy(chr);
}

//Персонаж выстрелил
void LAi_type_guardian_Fire(aref chr, aref enemy, float kDist, bool isFindedEnemy)
{

}

//Персонаж атакован
void LAi_type_guardian_Attacked(aref chr, aref by)
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
	if (rand(100) > 90)    LAi_CharacterPlaySound(chr, "warrior");
}

//------------------------------------------------------------------------------------------
//Внутреннии функции
//------------------------------------------------------------------------------------------

void LAi_type_guardian_CmdAttack(aref chr)
{
	chr.chr_ai.type.wait = "attack";
	PostEvent("Event_type_guardian_Attacked", rand(5) * 100, "i", chr);
	if (rand(100) > 80 && !LAi_IsDead(chr) && !LAi_IsDead(pchar))    LAi_CharacterPlaySound(chr, "warrior");
}

#event_handler("Event_type_guardian_Attacked", "LAi_type_guardian_CmdAttack_Event");
void LAi_type_guardian_CmdAttack_Event()
{
	aref chr = GetEventData();
	if (!TestRef(chr)) return;
	chr.chr_ai.type.wait = "";
	if (chr.chr_ai.type.enemy == "") return;
	int trg = sti(chr.chr_ai.type.enemy);
	LAi_type_guardian_CmdAttack_Now(chr, trg);
}

bool LAi_type_guardian_CmdAttack_Now(aref chr, int trg)
{
	if (trg < 0)
	{
		LAi_tmpl_stay_InitTemplate(chr);
		return false;
	}
	chr.chr_ai.type.etime = 3 + rand(5);
	if (!LAi_tmpl_SetFight(chr, &Characters[trg]))
	{
		//Несмогли инициировать шаблон
		LAi_tmpl_stay_InitTemplate(chr);
		return false;
	}
	if (rand(100) > 90 && !LAi_IsDead(chr) && !LAi_IsDead(pchar)) LAi_CharacterPlaySound(chr, "warrior");
	return true;
}

void LAi_type_guardian_Return(aref chr)
{
	chr.chr_ai.type.wait = "return";
	chr.chr_ai.type.enemy = "";
	PostEvent("Event_type_guardian_Return", rand(10) * 100, "i", chr);
}

#event_handler("Event_type_guardian_Return", "LAi_type_guardian_Return_Event");
void LAi_type_guardian_Return_Event()
{
	aref chr = GetEventData();
	if (!TestRef(chr)) return;
	chr.chr_ai.type.wait = "";
	chr.chr_ai.type.enemy = "";
    chr.ToPointForced = "";
	LAi_tmpl_runto_InitTemplate(chr);
	LAi_tmpl_runto_SetLocator(chr, chr.chr_ai.type.group, chr.chr_ai.type.locator, -1.0);
}

//HardCoffee ref SoldierNotBlade CitizenNotBlade -->
//Проверить персонажа с заданной вероятностью
void LAi_SoldierTestControl(aref chr, bool bFightMode, bool bGuard)  //HardCoffee TODO: придумать куда это перенести, используется ещё и в LAi_patrol.c
{
	if (dialogRun) return;

	int iNPCNation = sti(chr.nation);
	bool bDay = isDay();
	//Днём патрульные сразу за волыну спрашивают, а ночью, если не повезёт
	if (bFightMode && or(bDay, bGuard))
	{
		LAi_SoldierAboutToAsk(chr, true);
		return;
	}

	bool bAskAgain = CheckAttribute(chr, "WhoAreYou");

	if (bGuard) //Чтобы отличить шаблон lai_guardian от lai_patrol
	{
		//HardCoffee TODO: диалог гвардов на маяке не различает своих и чужих
		//флаг "опрашивать всегда", но с паузой
		if (CheckAttribute(chr, "protector.CheckAlways") && sti(chr.protector.CheckAlways) > 0)
		{
			if (bAskAgain) DeleteAttribute(chr, "WhoAreYou");
			LAi_SoldierAboutToAsk(chr, bFightMode); //Переходим к диалогу
			return;
		}

		//если гг на входе сумел обмануть гвардов, то на некоторое время вешается этот атрибут
		if (CheckAttribute(&TEV, "BlindGuards") && !bAskAgain)
			return;
	}

	if (iNPCNation == PIRATE) return; //Пираты не проверяют на шпиона

	bool bGoodRep = GetCharacterReputation_WithNation(pchar, iNPCNation) > -10;
	//Солдаты не спрашивают при отсутствии войны у наций и отсутствии НЗГ
	if (GetNationRelation(iNPCNation, GetBaseHeroNation()) != RELATION_ENEMY
	&& GetNationRelation2MainCharacter(iNPCNation) != RELATION_ENEMY && bGoodRep)
	{
		if (bAskAgain) DeleteAttribute(chr, "WhoAreYou");
		if (bGuard && Rand(549) == 0) LAi_SoldierAboutToAsk(chr, bFightMode); //к другу докапаемся от нечего делать
		return;
	}

	//Если лицензию уже проверили, больше не докапываемся
	if (CheckNationLicence(iNPCNation) && GetDaysContinueNationLicence(iNPCNation) >= 0 && GetSneakFastReloadByGuardian(chr.City))
	{
		if (bAskAgain) DeleteAttribute(chr, "WhoAreYou");
		return;
	}

	//Повторная проверка, если до гг изначально докапались с оружием во вражеском городе, чтобы не упустить его
	//Это только для врагов, по этому расположена после проверок на отношения и лицензию
	if (bAskAgain)
	{
		DeleteAttribute(chr, "WhoAreYou");
		if (CheckAttribute(chr, "greeting")) //чтобы не пересеклось с уже идущим приветствием
		{
			chr.greeting_base = chr.greeting;
			chr.greeting = "";
		}
		LAi_SoldierAboutToAsk(chr, bFightMode);
		return;
	}

	bool bWalk = HasStrEx(GetCharCurAni(pchar), "idle_,walk,turn ", "|");
	//Первая проверка на скрытность А она нужна вообще?
	if (!bGuard)
	{
		int irand;
		if (bFightMode) iRand = 500;
		else if (bDay) iRand = 120;
		else iRand = 360;

		if (rand(iRand) <= GetCharacterSkill(pchar, "Sneak"))
		{
			/*if (stf(chr.chr_ai.type.stealthcough) <= 0.0 && !SoundIsPlaying(charVoice))
			{
				PlayVoice("stealth_cough_" + rand(3));
				chr.chr_ai.type.stealthcough = "25.0";
			}*/
			if (bWalk) AddCharacterExpToSkill(pchar, SKILL_SNEAK, 7.0);
			else AddCharacterExpToSkill(pchar, SKILL_SNEAK, 10.0);
			chr.chr_ai.type.checkPatrol = its(5 + rand(10));
			return;
		}
	}

	// KZ > если имеется НЗГ, то нет никаких шансов остаться незамеченным таким образом; для баланса, дабы не снижать ценность торговой лицензии
	if (bWalk && bGoodRep)
	{
		int chance = makeint(GetSneakChance()); // на всякий

		if (!bDay)
		{
			if (CheckOddValue(chance))
				chance++;

			chance /= 2;
		}

		chance += GetSneakChanceBonus(); // бонусы от цыганки и перка "Искусство обмана" не штрафятся ночью

		if (rand(119) <= chance)
		{
			float posX, posY, posZ; GetCharacterPos(chr, &posX, &posY, &posZ);

			/*if (stf(chr.chr_ai.type.stealthcough) <= 0.0 && !SoundIsPlaying(charVoice))
			{
				PlayVoice3D("stealth_cough_" + rand(3), posX, posY, posZ);
				chr.chr_ai.type.stealthcough = "25.0";
			}*/

			chr.chr_ai.type.CheckGuard = its(5 + rand(10)); //25
			AddCharacterExpToSkill(pchar, SKILL_SNEAK, 10.0);
			return;
		}
	}
	LAi_SoldierAboutToAsk(chr, bFightMode); //Не прошли проверку на скрытность, пытаемся начать диалог
}

void LAi_SoldierAboutToAsk(ref rSld, bool bFightMode) //HardCoffee TODO: придумать куда это перенести, используется ещё и в LAi_patrol.c
{
	SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 0); // Убрать оружие без анимации
	if (!LAi_Character_CanDialog(rSld, pchar)) return;
	if (rSld.dialog.Filename == "Common_Soldier.c" || rSld.dialog.Filename == "Common_Fort.c")
		rSld.IWantAskYou = "1"; //чтобы понять, что это именно нпс обратился к игроку

	if (bFightMode) //докопаемся до оружия
	{
		if (rSld.dialog.Filename == "Quest\CapBloodLine\questNPC.c")
		{
			if (Pchar.questTemp.CapBUnarmed == false) LAi_CharacterPlaySound(rSld, "sold_weapon_off");
			else PlaySound("VOICE\" + VoiceGetLanguage() + "\soldier_arest_1.wav");
			rSld.Dialog.CurrentNode = "SoldierNotBlade";
			if (HasSubStr(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE), "blade5"))
				TEV.BloodDetectDagger = "1";
		}
		else
		{
			rSld.Dialog.Base_Filename = rSld.Dialog.Filename;
			rSld.Dialog.Filename = "Common_NotBlade.c";
			rSld.Dialog.TempNode = rSld.Dialog.CurrentNode;
			rSld.Dialog.CurrentNode = "GuardianNotBlade";
		}
		if (rSld.chr_ai.type == "patrol") rSld.chr_ai.type.checkPatrol = "1";
		else rSld.chr_ai.type.checkGuard = "1";
	}
	else
	{
		LAi_SetFightMode(pchar, false); //Уберём кулаки, если они есть
		//время до следующей проверки
		if (rSld.chr_ai.type == "patrol") rSld.chr_ai.type.checkPatrol = "25";
		else if (CheckAttribute(rSld, "protector")) rSld.chr_ai.type.checkGuard = "50";
	}

	if (CheckAttribute(rSld, "greeting"))
	{	//Правильный greeting запишем в диалоговом файле, а этот восстановим в DialogExit
		rSld.greeting_base = rSld.greeting;
		rSld.greeting = "";
	}
	rSld.chr_ai.type.state = "dialog";
	LAi_tmpl_SetDialog(rSld, pchar, -1.0);
}

void LAi_TemporaryBlindGuards() //HardCoffee Это для гвардов, так как они стоят по двое, чтобы 2 раза не доказывать одно и то же
{
	TEV.BlindGuards = "1";
	Lai_MethodDelay("LAi_GuardCanSeeAgain", 10.0 + makefloat(Rand(15)));
}

void LAi_GuardCanSeeAgain()
{
    DeleteAttribute(&TEV, "BlindGuards");
}
// ref SoldierNotBlade CitizenNotBlade <--

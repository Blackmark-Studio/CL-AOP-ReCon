
// > получить активный кейс анимации персонажа chr
string GetCharCurAni(ref chr)
{
	string sAniCaseName;
	SendMessage(chr, "le", MSG_CHARACTER_GETCURANIMATION, &sAniCaseName);
	return sAniCaseName;
}

// bIs == true (str1 == str2); bIs == false (HasStr(str1, str2))
bool StrHasStr(string str1, string str2, bool bIs)
{
//	str1 = GetStrSmallRegister(str1);
//	str2 = GetStrSmallRegister(str2);

	int iLen1 = strlen(&str1);
	int iLen2 = strlen(&str2);

	if (iLen1 < 1 || iLen2 < 1)
		return false;

	int i = 0;
	int j, iEnd1, iEnd2;
	string temp1, temp2;

	while (i < iLen2)
	{
		iEnd2 = findSubStr(&str2, ",", i);

		if (iEnd2 < 0)
			iEnd2 = iLen2;

		if (iEnd2 > i)
		{
			temp2 = strcut(&str2, i, iEnd2 - 1);
			j = 0;

			while (j < iLen1)
			{
				iEnd1 = findSubStr(&str1, ",", j);

				if (iEnd1 < 0)
					iEnd1 = iLen1;

				if (iEnd1 > j)
				{
					temp1 = strcut(&str1, j, iEnd1 - 1);

					if (bIs)
					{
						if (temp1 == temp2)
							return true;
					}
					else if (HasStr(temp1, temp2))
						return true;
				}

				j = iEnd1 + 1;
			}
		}

		i = iEnd2 + 1;
	}

	return false;
}

int CheckFilesInDir(string sDir)
{
	object oFileFinder;
	aref arFileList;
	int iFilesQty = 0;

	DeleteAttribute(&oFileFinder, "");
	oFileFinder.dir = sDir;
	CreateEntity(&oFileFinder, "FINDFILESINTODIRECTORY");

	makearef(arFileList, oFileFinder.filelist);
	iFilesQty = GetAttributesNum(arFileList);
	DeleteClass(&oFileFinder);

	return iFilesQty;
}

// > разбивание строки "<путь к файлу>\<файл>" на "<путь к файлу>" и "<файл>"
bool SeparatePath(string path, ref file, ref dir)
{
	if (path == "" || !HasStrEx(path, "\,/", "|"))
		return false;

	string sym, tmp = "";
	int i = strlen(path) - 1;

	for (; i > 0; i--)
	{
		sym = GetSymbol(path, i);

		if (!HasStrEx(sym, "\,/", "|"))
			tmp = sym + tmp;
		else
		{
			if (tmp != "")
			{
				file = tmp;
				dir = FindStringBeforeChar(path, tmp);
				return true;
			}
		}
	}

	return false;
}

// > TODO del ?
int GetItemSneakBonus(bool bSkill)
{
	int i, value = 0;
	aref ItemListARef;
	string sItemName;

	makearef(ItemListARef, pchar.items);
	int Qty = GetAttributesNum(ItemListARef);

	if (Qty > 0)
	{
		for (i = 0; i < Qty; i++)
		{
			sItemName = GetAttributeName(GetAttributeN(ItemListARef, i));

			if (bSkill) // > Sneak
			{
				if (sItemName == "suit_1" && GetCharacterEquipSuitID(pchar) == sItemName)
					value += 20;
				else if (sItemName == "indian17")
					value += 3;
				else if (StrHasStr(sItemName, "indian18,indian19", true))
					value -= 10;
				else if (sItemName == "indian21")
					value -= 5;
				else if (sItemName == "mineral4")
					value -= 1;
			}
			else // > Fortune
			{
				if (sItemName == "DeSouzaCross")
					value += 15;
				else if (StrHasStr(sItemName, "jewelry8,jewelry9", true))
					value += 1;
				else if (sItemName == "Cursed_idol")
					value -= 80;
				else if (sItemName == "Coins")
					value -= 50;
				else if (StrHasStr(sItemName, "SkullAztec,indian22", true))
					value -= 10;
				else if (sItemName == "indian20")
					value -= 5;
				else if (sItemName == "Mineral8")
					value -= 1;
			}
		}
	}

	return value;
}

float GetSneakChance()
{
	float fChance = GetCharacterSPECIAL(pchar, SPECIAL_L) + GetCharacterSPECIAL(pchar, SPECIAL_P) + round_up(makefloat(GetCharacterSkill(pchar, "Sneak")) / 3) + round_up(makefloat(GetCharacterSkill(pchar, "Fortune")) / 4);

	if (CheckAttributeEx(pchar, "Skill.Sneak,Skill.Fortune", "&"))
	{
		if (sti(pchar.Skill.Sneak) >= 100)
			fChance = fChance + GetItemSneakBonus(0); // если "Скрытность" полностью прокачана, то все предметы со статами к этому умению получают вторую жизнь - 10% от бонуса (-10% от штрафа) к fChance
		
		if (sti(pchar.Skill.Fortune) >= 100)
			fChance = fChance + GetItemSneakBonus(1); // то же самое для "Везения"
	}

	Restrictor(&fChance, 0.0, 100.0);

	return fChance;
}

int GetSneakChanceBonus()
{
	int iChance = GetFortuneBonus(5);

	if (CheckCharacterPerk(pchar, "Trustworthy"))
		iChance += 5;

	return iChance;
}

void GipsyFortuneBonusEnd(string str)
{
	DeleteQuestCondition("GipsyFortuneBonusEnd");
	DeleteAttributeMass(&TEV, "", "GipsyFortuneBonus,GipsyFortuneTimer,GipsyFortuneText");
}

// > при наличии бонуса от гадания цыганки вернуть fResult равное value
float GetFortuneBonus(float value)
{
	float fResult = 0.0;
	
	if (CheckAttribute(&TEV, "GipsyFortuneBonus"))
		fResult = value;
	
	return fResult;
}

// > проверка целого значения на нечётность
bool CheckOddValue(int value)
{
	return value % 2 != 0;
}

// > адаптация мода на быстрые переходы во вражеских городах от mrtehon
bool GetSneakFastReload()
{
	if (CheckAttribute(&TEV, "SneakFastReload") && CheckAttribute(loadedLocation, "fastreload") && FindColony(loadedLocation.fastreload) != -1 && TEV.SneakFastReload == Colonies[FindColony(loadedLocation.fastreload)].id + GetDataDay() + GetDataMonth() + GetDataYear())
		return true;
	
	DeleteAttribute(&TEV, "SneakFastReload");
	return false;
}

// проверка для пинга стражников после проверки лицензии
//на плантациях нет фастрелоада, но стражники пингуют так же, потому колонию определяем по регистрации стража
bool GetSneakFastReloadByGuardian(string sColony)
{
	if (CheckAttribute(&TEV, "SneakFastReload") && TEV.SneakFastReload == Colonies[FindColony(sColony)].id + GetDataDay() + GetDataMonth() + GetDataYear())
		return true;

	DeleteAttribute(&TEV, "SneakFastReload");
	return false;
}

// > фейковая прокрутка времени
string FakeNextTime(int iHour)
{
	float nexttime = GetTime() + iHour;
	int addingDays = 0;
	
	while (nexttime >= 24.0)
	{
		nexttime = nexttime - 24.0;
		addingDays++;
	}
	
	int nextDay = GetDataDay() + addingDays;
	int curMonth = GetDataMonth();
	int curYear = GetDataYear();
	while (GetMonthDays(curMonth, curYear) < nextDay)
	{
		nextDay = nextDay - GetMonthDays(curMonth, curYear);
		curMonth++;
		if (curMonth > 12) { curMonth -= 12; curYear++; } // учёт перехода через год для корректной длины февраля
	}

	int nextMonth = curMonth;
	int nextYear = curYear;
	while (12 < nextMonth)
	{
		nextMonth = nextMonth - 12;
		nextYear++;
	}
	
	string sTemp = "  ";
	if (makeint(nexttime) < 10)
		sTemp += "0";
	
	string sMins = Environment.date.min;
	if (sti(sMins) < 10)
		sMins = "0" + sMins;
	
	return nextDay + " " + XI_ConvertString("target_month_" + nextMonth) + " " + nextYear + sTemp + makeint(nexttime) + ":" + sMins;
}

// > проверка наличия карты сокровищ или двух её кусков у chr
bool CheckForTreasureMap(ref chr)
{
	return ItemCheck(chr, "map_full,mapQuest", 0) || ItemCheck(chr, "map_part1,map_part2", 1);
}

// > метод сохраняет список абордажников ГГ; отрабатывает при загрузке пешей локации
void StoreFighters()
{
	//сносим старую базу
	DeleteAttribute(&TEV, "StoreFighters");
	TEV.StoreFighters = "";
	//заполняем новую
	aref arFromBox, arIntoBox;
	makearef(arFromBox, pchar.fellows.passengers.officers);
	makearef(arIntoBox, TEV.StoreFighters);
	CopyAttributes(arIntoBox, arFromBox);
}

// > метод проверяет наличие chr в сохранённом в StoreFighters() списке абордажников
bool CheckFighters(ref chr)
{
	if (!CheckAttribute(&TEV, "StoreFighters.id1") || !CheckAttribute(chr, "index"))
		return false;
	
	aref arOfficer;
	makearef(arOfficer, TEV.StoreFighters);
	
	for (int i = 1; i < 4; i++)
	{
		string sTemp = "id" + i;
		if (arOfficer.(sTemp) == chr.index && IsEntity(&chr))
			return true;
	}
	
	return false;
}

// > функция получения количества загруженных в локу абордажников
int GetCountFighters()
{
	int iFighters = 0;

	if (!CheckAttribute(&TEV, "StoreFighters.id1")) return iFighters;

	aref arOfficer;
	makearef(arOfficer, TEV.StoreFighters);

	for (int i = 1; i < 4; i++)
	{
		string sTemp = "id" + i;
		if (arOfficer.(sTemp) != "-1") iFighters++;
	}

	return iFighters;
}

// > установка (bBan) и снятие (!bBan) запретов на различные активности
//
// все имеющиеся запреты:
// Looting - обыск трупов, сундуков и нычек;
// ItemLocator - локаторы item, randitem;
// Exchange - обмен предметами;
// Map - выход на глобалку;
// TimeSpeed - ускорение / замедление времени
// HerbHarvest - запретить спавн растений в локациях;
// HerbPickup - запретить срывать растения
//
// TODO добавить > Travel - быстрое перемещение; Talk - диалог; Swap - обмен кораблями
// можно через запятую задать или снять сразу все запреты: sType = "Looting,Exchange,Map,HerbHarvest,HerbPickup"
void SetBan(string sType, bool bBan)
{
	int iLen = strlen(&sType);
	int iPos = 0;
	int iEnd;
	string tmp;

	while (iPos < iLen)
	{
		iEnd = findSubStr(&sType, ",", iPos);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iPos)
		{
			tmp = stripblank(strcut(&sType, iPos, iEnd - 1));

			if (tmp != "")
			{
				tmp = "Forbidden." + tmp;

				if (bBan)
					TEV.(tmp) = "1";
				else
					DeleteAttribute(&TEV, tmp);
			}
		}

		iPos = iEnd + 1;
	}
}

// > проверка запретов
bool GetBan(string sType)
{
	return CheckAttribute(&TEV, "Forbidden." + sType) && TEV.Forbidden.(sType) == "1";
}

// > сообщения в логе со звуковым сопровождением; отделяя знаком "&" можно задать несколько strings и sounds
void LogSound(string strings, string sounds)
{
	int iLen = strlen(&strings);
	int iPos = 0;
	int iEnd;
	string tmp, snd = "";

	while (iPos < iLen)
	{
		iEnd = findSubStr(&strings, "&", iPos);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iPos)
			Notification(strcut(&strings, iPos, iEnd - 1), "none");

		iPos = iEnd + 1;
	}

	iLen = strlen(&sounds);
	iPos = 0;

	while (iPos < iLen)
	{
		iEnd = findSubStr(&sounds, "&", iPos);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iPos)
		{
			tmp = strcut(&sounds, iPos, iEnd - 1);

			if (snd != tmp)
			{
				snd = tmp;
				PlaySound(snd);
			}
		}

		iPos = iEnd + 1;
	}
}

// > множественные сообщения в логе; отделяя знаком "&" можно задать несколько strings
void Logs(string strings)
{
	int iLen = strlen(&strings);
	int iPos = 0;
	int iEnd;

	while (iPos < iLen)
	{
		iEnd = findSubStr(&strings, "&", iPos);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iPos)
			Log_Info(strcut(&strings, iPos, iEnd - 1));

		iPos = iEnd + 1;
	}
}

// LogSound с новой системой оповещений
void LogSound_WithNotify(string strings, string sounds, string iconName)
{
	int iLen = strlen(&strings);
	int iPos = 0;
	int iEnd;
	string tmp, snd = "";

	while (iPos < iLen)
	{
		iEnd = findSubStr(&strings, "&", iPos);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iPos)
			Notification(strcut(&strings, iPos, iEnd - 1), iconName);

		iPos = iEnd + 1;
	}

	iLen = strlen(&sounds);
	iPos = 0;

	while (iPos < iLen)
	{
		iEnd = findSubStr(&sounds, "&", iPos);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iPos)
		{
			tmp = strcut(&sounds, iPos, iEnd - 1);

			if (snd != tmp)
			{
				snd = tmp;
				PlaySound(snd);
			}
		}

		iPos = iEnd + 1;
	}
}

// > выдача или отъём предметов с текстовым и звуковым сопровождением
void AddItemLog(ref rChar, string sItems, string sQty, string str, string snd)
{
	// Автоудаление пробелов
	sItems = stripblank(sItems);
	sQty = stripblank(sQty);

	int iLenI = strlen(&sItems);
	int iLenQ = strlen(&sQty);
	int iPosI = 0;
	int iPosQ = 0;
	int iEndI, iEndQ, iQty;
	int iFirst = 0;
	bool bFirst = true;
	string sItem;

	while (iPosI < iLenI)
	{
		iEndI = findSubStr(&sItems, ",", iPosI);

		if (iEndI < 0)
			iEndI = iLenI;

		iQty = 0;

		if (iPosQ < iLenQ)
		{
			iEndQ = findSubStr(&sQty, ",", iPosQ);

			if (iEndQ < 0)
				iEndQ = iLenQ;

			if (iEndQ > iPosQ)
				iQty = sti(strcut(&sQty, iPosQ, iEndQ - 1));

			iPosQ = iEndQ + 1;

			if (bFirst)
			{
				iFirst = iQty;
				bFirst = false;
			}
		}

		if (iQty == 0)
			iQty = iFirst;

		if (iEndI > iPosI)
		{
			sItem = strcut(&sItems, iPosI, iEndI - 1);

			if (iQty < 0)
				TakeNItems(rChar, sItem, iQty);
			else
				GenerateAndAddItems(rChar, sItem, iQty);
		}

		iPosI = iEndI + 1;
	}

	LogSound_WithNotify(str, snd, "BoxPlus");
}

// > получить название предмета из ItemsDescribe.txt по его id
string GetItemName(string sItemID)
{
	ref refItem = ItemsFromID(sItemID);
	if (CheckAttribute(refItem, "name"))
		return GetConvertStr(refItem.name, "ItemsDescribe.txt");
	else
		return sItemID;
}

// KZ > из ЧМ для КС от Cheatsurfer взял наиболее интересные методы; местами внесены правки и дополнения, убраны приписки csm, нейминг функций приведён в более читабельный вид
// csmCheckAttributeMassive --> CheckAttribute, рассчитанный на массовый, но простенький чек аттрибутов у объекта
// sBranch не обязателен, если в нем нет нужды (в таком случае, кавычки оставлять пустыми)
// В sLeaves через запятую и без пробелов можно указывать перечень аттрибутов к проверке у объекта oTree
// В качестве sCond задаётся "&" (условие "&&") и любой другой символ (условие "||")
// TODO: добавить чек значений (sValues), с локальными условиями (!=, >, <= и т.д.)
bool CheckAttributeMass(object oTree, string sBranch, string sLeaves, string sCond)
{
	if (sLeaves == "")
		return false;

	// Автоудаление пробелов, сейчас оставлено так на случай, если они там быть должны
	//sBranch = stripblank(sBranch);
	//sLeaves = stripblank(sLeaves);
	sCond = stripblank(sCond);

	if (sBranch != "")
		sBranch += ".";

	bool bAnd = HasStr(sCond, "&");

	int iLen = strlen(&sLeaves);
	int iPos = 0;
	int iEnd;
	int n = 0; // > найдено
	int q = 0; // > непустых сегментов обработано

	string sT;

	while (iPos < iLen)
	{
		iEnd = findSubStr(&sLeaves, ",", iPos);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iPos)
		{
			sT = strcut(&sLeaves, iPos, iEnd - 1);
			q++;

			if (CheckAttribute(&oTree, sBranch + sT))
			{
				if (!bAnd)
					return true;

				n++;
			}
			else
			{
				if (bAnd)
					return false;
			}
		}

		iPos = iEnd + 1;
	}

	// > Порог считаем по фактически обработанным непустым сегментам q, а не по числу запятых
	if (q > 0 && n >= q)
		return true;

	return false;
}

// > без sBranch
bool CheckAttributeEx(object _obj, string _str, string _cond)
{
	return CheckAttributeMass(&_obj, "", _str, _cond);
}

// > подсчёт указанных атрибутов объекта
int GetAttributeQty(object obj, string coreStr, string subStr)
{
	int iRes = 0;
	int iLen = strlen(&subStr);
	int iPos = 0;
	int iEnd;

	if (coreStr != "")
		coreStr += ".";

	while (iPos < iLen)
	{
		iEnd = findSubStr(&subStr, ",", iPos);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iPos && CheckAttribute(&obj, coreStr + strcut(&subStr, iPos, iEnd - 1)))
			iRes++;

		iPos = iEnd + 1;
	}

	return iRes;
}

// csmDeleteAttributeMassive --> DeleteAttribute, рассчитанный на массовое удаление аттрибутов у объекта
// sBranch не обязателен, если в нем нет нужды (в таком случае, следует оставить кавычки пустыми)
// В sLeaves через запятую и без пробелов можно указывать перечень аттрибутов к удалению у объекта oTree
void DeleteAttributeMass(object oTree, string sBranch, string sLeaves)
{
	if (sLeaves == "")
		return;

	if (sBranch != "")
		sBranch += ".";

	// Автоудаление пробелов, сейчас оставлено так на случай, если они там быть должны
	//sBranch = stripblank(sBranch);
	//sLeaves = stripblank(sLeaves);

	int iLen = strlen(&sLeaves);
	int iPos = 0;
	int iEnd;

	while (iPos < iLen)
	{
		iEnd = findSubStr(&sLeaves, ",", iPos);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iPos)
			DeleteAttribute(&oTree, sBranch + strcut(&sLeaves, iPos, iEnd - 1));

		iPos = iEnd + 1;
	}
}

// > без sBranch
void DeleteAttributeEx(object obj, string str)
{
	DeleteAttributeMass(&obj, "", str);
}

// --[ Где это мы?
// 0 - хз, 1 - на своих двоих, 2 - управляем кораблем, 3 - на глобалке
int GetPos(bool bOpenSea)
{
	if (bOpenSea)
	{
		if (bSeaActive && !bAbordageStarted && !IsEntity(&chrAnimationKipper) && !IsEntity(&worldMap))
			return 2;
		else
			return GetPos(0);
	}
	
	if (IsEntity(&ILogAndActions))
	{
		switch (ILogAndActions.type)
		{
			case "land": return 1; break;
			case "sea": return 2; break;
			case "map": return 3; break;
		}
	}
	else
	{
		if (!IsEntity(&worldMap))
		{
			if (IsEntity(&chrAnimationKipper) || IsEntity(&loadedLocation))
				return 1;
			else
			{
				if (bSeaActive && !bAbordageStarted)
					return 2;
			}
		}
		else
			return 3;
	}

	return 0;
}
// ]--

// Сокращение HasSubStr, есть ли в строке sText то, что указано в sAttr
// > вызовы GetStrSmallRegister тут лишние - движковый FindSubStr регистронезависимый
bool HasStr(string sText, string sAttr)
{
	return FindSubStr(sText, sAttr, 0) != -1;
}

// > AlexBlade - Начинается ли строка sText с подстроки sSubStr
bool StrStartsWith(string sText, string sSubStr)
{
	int iTextLen = strlen(sText);
	int iSubLen = strlen(sSubStr);
	
	if (iSubLen == 0)
		return false;
	if (iSubLen > iTextLen)
		return false;
	
	return strcut(sText, 0, iSubLen - 1) == sSubStr;
}

// KZ > Заканчивается ли строка sText с подстроки sSubStr
bool StrEndsWith(string sText, string sSubStr)
{
	int iTextLen = strlen(sText);
	int iSubLen = strlen(sSubStr);
	
	if (iSubLen == 0 || iSubLen > iTextLen)
		return false;
	
	return strcut(sText, iTextLen - iSubLen, iTextLen - 1) == sSubStr;
}

// > AlexBlade - Расширение метода FindStringAfterChar. Возвращает строку после позиции первого вхождения подстроки sSubStr
string FindStringAfterSubStr(string _string, string sSubStr)
{
	int i = FindSubStr(_string, sSubStr , 0);
	if(i == -1) return "";
	string sRetStr = strcut(_string, i+strlen(sSubStr), strlen(_string)-1);
	return sRetStr;
}

// > AlexBlade - Альтернатива методу FindStringAfterChar. Возвращает строку перед позицией первого вхождения подстроки sSubStr
string FindStringBeforeSubStr(string _string, string sSubStr)
{
	return FindStringBeforeChar(_string, sSubStr);
}

// KZ > Метод сверяет у объекта _rChar значение атрибута _sAttr со значением _sValue
bool CheckAttrValue(ref _rChar, string _sAttr, string _sValue)
{
	return CheckAttribute(_rChar, _sAttr) && _rChar.(_sAttr) == _sValue;
}

// KZ > Метод проверяет у объекта _rChar атрибут _sAttr на наличие в нём хотя бы части значения _sValue
bool HasAttrValue(ref _rChar, string _sAttr, string _sValue)
{
	return CheckAttribute(_rChar, _sAttr) && HasStrMass(_rChar.(_sAttr), _sValue, ",", "|");
}

// csmHasStringMassive --> апгрейднутый вариант HasStr, рассчитанный на массовый чек значений sAttrs в строке sText
// Есть ли в строке sText всё или что-то из указанного в sAttrs, разделённое символом sDiv
// В качестве sCond задаётся "&" (условие "&&") и любой другой символ (условие "||")
bool HasStrMass(string sText, string sAttrs, string sDiv, string sCond)
{
	if (strlen(sText) <= 0 || strlen(sAttrs) <= 0)
		return false;

	if (sDiv == "")
		sDiv = ",";

	bool bAnd = HasStr(sCond, "&");

	int iLen = strlen(&sAttrs);
	int iDiv = strlen(&sDiv);
	int iPos = 0;
	int iEnd;
	int n = 0; // > найдено
	int q = 0; // > непустых сегментов обработано

	string sT;

	while (iPos < iLen)
	{
		iEnd = findSubStr(&sAttrs, sDiv, iPos);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iPos)
		{
			sT = strcut(&sAttrs, iPos, iEnd - 1);
			q++;

			if (HasStr(sText, sT))
			{
				if (!bAnd)
					return true;

				n++;
			}
			else
			{
				if (bAnd)
					return false;
			}
		}

		// > разделитель длиннее одного символа теперь тоже отрабатывает
		iPos = iEnd + iDiv;
	}

	// > порог считаем по фактически обработанным непустым сегментам q, а не по числу разделителей
	if (q > 0 && n >= q)
		return true;

	return false;
}

// > разделитель всегда запятая
bool HasStrEx(string str, string attr, string cond)
{
	return HasStrMass(str, attr, ",", cond);
}

// Чуть видоизмененная функция GetSubStringByNum: в качестве разделителя sDiv можно указывать не только запятую (в т.ч. несколько символов; поиск разделителя регистронезависимый)
// Возвращает сегмент номер iSelect (отсчёт с нуля) строки sText, разбитой разделителем sDiv
// > ref: пустой сегмент и iSelect вне диапазона возвращают "" (раньше был мусор с разделителем или ошибка strcut "Invalid range")
string GetSubStr(string sText, string sDiv, int iSelect)
{
	if (sDiv == "")
		sDiv = ",";

	if (iSelect < 0)
		return "";

	int iStart = 0;
	int iDivLen = strlen(sDiv);
	int iPos = findSubStr(&sText, sDiv, 0);

	while (iSelect > 0 && iPos != -1)
	{
		iStart = iPos + iDivLen;
		iPos = findSubStr(&sText, sDiv, iStart);
		iSelect--;
	}

	if (iSelect > 0)
		return ""; // > сегментов меньше, чем запрошено

	if (iPos == -1)
		iPos = strlen(&sText);

	if (iPos <= iStart)
		return ""; // > пустой сегмент

	return strcut(&sText, iStart, iPos - 1);
}

// Возвращает количество подстрок разделенных разделителем sDiv
int GetSubStrCount(string sText, string sDiv)
{
	if (sDiv == "")
		sDiv = ",";

	string sTemp = sText;
	int iNumFind = 1;
	int iFindPos = findSubStr(&sTemp, sDiv, 0);

	while (iFindPos > 0)
	{
		iNumFind++;
		iFindPos = findSubStr(&sTemp, sDiv, iFindPos + 1);
	}

	return iNumFind;
}

// csmGetRandMassive --> чуть видоизмененная функция GetRandSubString: в качестве разделителя sDiv, можно указывать любой символ, не только запятую
// Возвращает случайную из частей строки sText, отделенных разделителем sDiv
string GetRandStr(string sText, string sDiv)
{
	int i, iSelect, iFindPos;
	int iNumFind = 1;
	int iLastPos = 0;

	string sTemp;

	if (sDiv == "")
		sDiv = ",";

	if (strlen(sText) > 0)
	{
		iFindPos = findSubStr(sText, sDiv, 0);

		if (iFindPos < 0)
			return sText;

		while (iFindPos > 0)
		{
			iNumFind++;
			iFindPos = findSubStr(sText, sDiv, iFindPos + 1);
		}

		iSelect = rand(iNumFind - 1);

		iFindPos = 0;

		for (i = 0; i < iNumFind; i++)
		{
			iFindPos = findSubStr(sText, sDiv, iFindPos + 1);

			if (i == iSelect)
			{
				if (iFindPos == -1)
					iFindPos = strlen(sText);

				if (iLastPos >= iFindPos)
					return "";

				sTemp = strcut(sText, iLastPos, iFindPos - 1);

				return sTemp;
			}

			iLastPos = iFindPos + 1;
		}
	}

	return "";
}

// Дополненный stripblank: удалить из строки sText все символы sDel (в компанию к strlen() и strcut())
string strdel(string sText, string sDel)
{
	int i, iMax = strlen(sText);

	string sR = "";

	if (iMax <= 0)
		return sR;

	if (sDel == " ")
		return stripblank(sText);

	for (i = 0; i < iMax; i++)
	{
		if (GetSymbol(sText, i) != sDel)
			sR += GetSymbol(sText, i);
	}

	return sR;
}

// Сокращение TakeNItems, с парой дополнений:
// 1 - если iQty = 0, то забрать у rChar все имеющиеся sItem
// 2 - если sItem = "", то забрать у rChar вообще все предметы (кроме квестовых); деньги тоже отнять при iQty = 0
void ItemTake(ref rChar, string sItem, int iQty)
{
	int n = 0;

	if (sItem == "")
	{
		if (iQty == 0)
			n++;

		RemoveAllCharacterItems(rChar, n);
		SetNewModelToChar(rChar);
		return;
	}

	n = GetCharacterItem(rChar, sItem);

	if (iQty == 0)
		TakeNItems(rChar, sItem, -n);
	else
	{
		if (iQty > 0)
			sItem = GetGeneratedItem(sItem);
		
		TakeNItems(rChar, sItem, iQty);
	}
}

// Аналог ItemTake, рассчитанный на массовую выдачу/изъятие предметов у rChar
// в sItems, через запятую и без пробелов, можно указывать множество предметов; в sQty через запятую их кол-во
// если в sQty задано лишь 1 значение, то оно будет распространяться на все указанные предметы
// если в sQty значений меньше, чем указанных предметов в sItems, то для всех предметов, обделённых конкретикой выдаваемого кол-ва, будет браться самое первое значение
// > правило sItem == "" из ItemTake в ItemTakeEx не учитывается
void ItemTakeEx(ref rChar, string sItems, string sQty)
{
	// Автоудаление пробелов
	sItems = stripblank(sItems);

	if (sItems == "")
		return;

	sQty = stripblank(sQty);

	// > обе строки проходятся один раз параллельно
	int iLenI = strlen(&sItems);
	int iLenQ = strlen(&sQty);
	int iPosI = 0;
	int iPosQ = 0;
	int iEndI, iEndQ;
	int iQ = 1;
	int iFirst = 0;
	bool bFirst = true;
	string sN;

	while (iPosI < iLenI)
	{
		iEndI = findSubStr(&sItems, ",", iPosI);

		if (iEndI < 0)
			iEndI = iLenI;

		iQ = 1;

		if (iLenQ > 0)
		{
			iQ = 0;

			if (iPosQ < iLenQ)
			{
				iEndQ = findSubStr(&sQty, ",", iPosQ);

				if (iEndQ < 0)
					iEndQ = iLenQ;

				if (iEndQ > iPosQ)
					iQ = sti(strcut(&sQty, iPosQ, iEndQ - 1));

				iPosQ = iEndQ + 1;

				if (bFirst)
				{
					iFirst = iQ;
					bFirst = false;
				}
			}

			// > пустое или нулевое количество берётся с первого предмета
			if (iQ == 0)
				iQ = iFirst;
		}

		if (iEndI > iPosI)
		{
			sN = strcut(&sItems, iPosI, iEndI - 1);
			ItemTake(rChar, sN, iQ);
		}

		iPosI = iEndI + 1;
	}
}

// > выдать rChar предметы sItems и сразу экипировать их (bGen - генерировать ли предмет)
void ItemTakeEquip(ref rChar, string sItems, bool bGen)
{
	int iLen = strlen(&sItems);
	int iPos = 0;
	int iEnd;
	string s;

	while (iPos < iLen)
	{
		iEnd = findSubStr(&sItems, ",", iPos);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iPos)
		{
			s = strcut(&sItems, iPos, iEnd - 1);

			if (bGen)
				s = GetGeneratedItem(s);

			if (TakeNItems(rChar, s, 1))
				EquipCharacterByItem(rChar, s);
		}

		iPos = iEnd + 1;
	}
}

// > проверить инвентарь rChar на наличие предметов sItems; требуемое кол-во можно указать после знака ":" прямо в sItems, например: "bullet:6,gunpowder:4,potionrum" - нужно 6+ пуль, 4+ пороха и 1+ бутылка рома (отсутствие ":" или отсутствие значения после ":" считается за 1)
// "gold" можно проверять деньги rChar ("bullet:6,gunpowder:4,potionrum,gold:9500")
// при bAll необходимо наличие всех предметов sItems с указанным кол-ом, при !bAll достаточно любого из sItems в указанном кол-ве
// > ref: разбор строки идёт одним нативным проходом (был посимвольный KZ|Symbol и перескан GetSubStr с нуля на каждый сегмент), кол-во считается своим для каждого пункта, пустые сегменты пропускаются
bool ItemCheck(ref rChar, string sItems, bool bAll)
{
	int iLen = strlen(&sItems);

	if (iLen < 1)
		return false;

	int iEnd, iColon, iNameLen, iQ;
	int iStart = 0;
	bool bHas, bChecked = false;
	string sName;

	while (iStart < iLen)
	{
		iEnd = findSubStr(&sItems, ",", iStart);

		if (iEnd < 0)
			iEnd = iLen;

		if (iEnd > iStart) // > пустой сегмент (лишняя запятая) пропускаем
		{
			sName = strcut(&sItems, iStart, iEnd - 1);
			iQ = 1;
			iColon = findSubStr(&sName, ":", 0);

			if (iColon > 0)
			{
				iNameLen = strlen(&sName);

				if (iColon + 1 < iNameLen) // > после ":" пусто - остаётся 1
					iQ = sti(strcut(&sName, iColon + 1, iNameLen - 1));

				sName = strcut(&sName, 0, iColon - 1);

				if (iQ < 1)
					iQ = 1;
			}

			if (sName == "gold")
				bHas = sti(rChar.money) >= iQ;
			else
				bHas = GetCharacterItem(rChar, sName) >= iQ;

			bChecked = true;

			if (bAll)
			{
				if (!bHas)
					return false; // > не хватило - остальное можно не смотреть
			}
			else
			{
				if (bHas)
					return true; // > нашли одно - этого достаточно
			}
		}

		iStart = iEnd + 1;
	}

	// > при bAll сюда доходим, только если ничего не провалилось, при !bAll - если ничего не нашлось
	return bAll && bChecked;
}

string SetModifyTextColor(int line)
{
	string sConvert, sText = "";
	int idxloc = FindLoadedLocation();

	if (idxloc >= 0 && CheckAttribute(&Locations[idxloc], "fastreload"))
	{
		string sTemp, sCity = Locations[idxloc].fastreload;
		int n, start = 1;

		if (line > 1)
			start = 6;

		for (n = start; n <= 10; n++)
		{
			sTemp = GetLocFromFastReloadTable(idxloc, XI_ConvertString("fte_" + n));
		    sConvert = "ft_" + n;
		    if (Locations[idxloc].fastreload == "LostShipsCity" && sConvert == "ft_3") sConvert = "ft_phoenix";
		    if (Locations[idxloc].fastreload == "LostShipsCity" && sConvert == "ft_9") sConvert = "ft_diffIndoor";

			if (sTemp != "" && !CheckFastJump(Locations[idxloc].id, sTemp))
			{
				if (pchar.location == sTemp)
				{
					if (n == 5 || n == 10)
						sText = sText + ColorTextLine(XI_ConvertString(sConvert), "khaki");
					else
						sText = sText + ColorText(XI_ConvertString(sConvert), "khaki");
				}
				else
				{
					if (n == 5 || n == 10)
						sText = sText + ColorTextLine(XI_ConvertString(sConvert), "darkgray");
					else
						sText = sText + ColorText(XI_ConvertString(sConvert), "darkgray");
				}
			}
			else
			{
				if (HasStr(sCity, "LaVega") && n > 5)
					sText = sText + ColorText(XI_ConvertString(sConvert), "darkgray");
				else
					sText = sText + XI_ConvertString(sConvert);
			}

			if (line < 2 && n > 4)
				break;
		}
	}

	return sText;
}

//получение полного и корректного названия локации перемещения из объекта для быстрых перемещений
string GetLocFromFastReloadTable(int curLocIdx, string sFind)
{
    if (sFind == XI_ConvertString("fte_1") && Locations[curLocIdx].fastreload != "LostShipsCity")
        return pchar.location.from_sea;
	if (curLocIdx > -1 && CheckAttribute(&Locations[curLocIdx], "fastreload"))
	{
	    aref curloc, locref;
	    string outGroupName = Locations[curLocIdx].fastreload;
	    if (CheckAttribute(&objFastReloadTable, "table." + outGroupName))
	    {
            makearef(locref, objFastReloadTable.table.(outGroupName));
			int n = GetAttributesNum(locref);
			//TODO разобраться с индекасами в fast_reload_table.c и убрать эти костыли
            if (outGroupName == "LostShipsCity" && sFind == XI_ConvertString("fte_5"))
                outGroupName = "Residence";
            else if (outGroupName == "LostShipsCity" && sFind == XI_ConvertString("fte_3"))
                outGroupName = "FenixPlatform";
            else if (outGroupName == "LostShipsCity" && sFind == XI_ConvertString("fte_9"))
                outGroupName = "DiffIndoor";
            else if (outGroupName == "Villemstad" && sFind == XI_ConvertString("fte_5"))
                outGroupName = "hall";
            else
                outGroupName = sFind;

			for (int i = 0; i < n; i++)
			{
			    curloc = GetAttributeN(locref, i);
			    if (HasStr(curloc.location, outGroupName)) return curloc.location;
			}
	    }
	}
    return sFind;
}

// belamour Альтернативный модификатор
void HKT_Button(string sHKB) // быстрый переход
{
	int curLocIdx;
	string sFind = FindStringAfterChar(sHKB, "_");
	string sTxt = XI_ConvertString("There is no way there now");
	bool bOk = true;

	curLocIdx = FindLoadedLocation();

	string outGroupName = GetLocFromFastReloadTable(curLocIdx, sFind);

	// --> проверка запретов перехода
	Log_TestInfo("HKT_Button: "+ sHKB +  " outGroupName: "+ outGroupName +  " sFind: "+ sFind);
	if (LAi_group_IsActivePlayerAlarm() || !LAi_IsCharacterControl(pchar) || bDisableFastReload || chrDisableReloadToLocation || !IsEnableFastTravel()) bOk = false;
	else if (sHKB != "AltModeFastTravel_port" && !CheckFastJump(Locations[curLocIdx].id, outGroupName)) bOk = false;
	else if (sHKB == "AltModeFastTravel_port" && !CheckFastJump(Locations[curLocIdx].id, pchar.location.from_sea)) bOk = false;
	if (!bBettaTestMode && bOk) // проверка города на враждебность
	{
		int iFastColony = FindColony(loadedLocation.fastreload);
		if (iFastColony >= 0) // > ключ fastreload не колония - вне дипломатии, переход свободен
		{
			string sNation = Colonies[iFastColony].nation;
			if (sNation != "none")
			{
				int n = sti(sNation);
				bOk = (GetNationRelation2MainCharacter(n) == RELATION_ENEMY) || GetRelation2BaseNation(n) == RELATION_ENEMY;
				if (bOk && (n != PIRATE))
					bOk = GetSneakFastReload(); // если есть действующая лицензия, то при пройденной проверке не запрещаем быстрый переход
				else
					bOk = true;
			}
		}
	}
	// <--
	if(bOk)
	{
		if (sHKB == "AltModeFastTravel_port")
		{
			//if (pchar.location == pchar.location.from_sea) // TODO > сделать нормально - с проверками, фейдером и т.д.
				//ChangeCharacterAddressGroup(pchar, pchar.location, "reload", "reload1");
			//else
				PlayerFastTravel(curLocIdx, pchar.location.from_sea, "reload1");
		}
		else
			PlayerFastTravel(curLocIdx, outGroupName, "");
		
		return;
	}

	if (or(pchar.location == outGroupName, pchar.location == pchar.location.from_sea && sHKB == "AltModeFastTravel_port"))
		sTxt = XI_ConvertString("You are already there");

	LogSound(sTxt, "knopka");
}

void ModifyTextInfo() // belamour обновление всплывающей подсказки
{
	if (CheckAttribute(&TEV, "AltMode.FastTravel") && CheckAttribute(loadedLocation, "fastreload") && bFastEnable())
	{
		float fHtRatio = GetScreenScale();
		string sLine2 = SetModifyTextColor(1);
		string sLine3 = SetModifyTextColor(2);
		int iOffset = 0;

		float fScale = 1.1 * fHtRatio;

		int k2 = makeint((GetStringWidth(sLine2, "interface_normal", 1.0) + 1) / 2 * fScale) - makeint((GetStringWidth(StripColorTags(sLine2), "interface_normal", 1.0) + 1) / 2 * fScale);
		int k3 = makeint((GetStringWidth(sLine3, "interface_normal", 1.0) + 1) / 2 * fScale) - makeint((GetStringWidth(StripColorTags(sLine3), "interface_normal", 1.0) + 1) / 2 * fScale);

		k2 -= 1;

		aref arChar; makearef(arChar, objLandInterface.data.icons.id0);
		if (arChar.HideStates == 0) iOffset = 230;

		SetNewTextInfoEx("AltModificatorLine1", -1.0, XI_ConvertString("ft_Help"), sti(showWindow.left) + RecalculateHIcon(makeint((iOffset + 325) * fHtRatio)), RecalculateVIcon(makeint(30 * fHtRatio)), "interface_normal", fScale, argb(243,254,252,169));
		SetNewTextInfoEx("AltModificatorLine2", -1.0, sLine2, sti(showWindow.left) + RecalculateHIcon(makeint((iOffset + 342) * fHtRatio)) + k2, RecalculateVIcon(makeint(52 * fHtRatio)), "interface_normal", fScale, argb(255,255,255,255));
		SetNewTextInfoEx("AltModificatorLine3", -1.0, sLine3, sti(showWindow.left) + RecalculateHIcon(makeint((iOffset + 364) * fHtRatio)) + k3, RecalculateVIcon(makeint(74 * fHtRatio)), "interface_normal", fScale, argb(255,255,255,255));
	}
	else
		ModifyTextHide();
}

void ModifyTextHide()
{
	DeleteAttribute(&TEV, "AltMode.FastTravel");
	SendMessage(&objLandInterface,"l",MSG_BATTLE_LAND_TEXTINFO_SET);
	
	for (int x = 1; x < 4; x++)
	{
		PostEvent("NewTextInfoEnd", 0, "s", "AltModificatorLine" + x);
	}
}

bool bFastEnable() // belamour возможен ли переход
{
	if (LAi_group_IsActivePlayerAlarm()) return false;
	if (!LAi_IsCharacterControl(pchar)) return false;
	if (bDisableFastReload)	return false;
	if (!IsEnableFastTravel()) return false;
	if (chrDisableReloadToLocation) return false;
	if (!CheckAttribute(&loadedLocation, "fastreload")) return false;
	if (!SetReloadIcons()) return false;
	//в ГПК быстрый переход работает только при наличии карты
	if (loadedLocation.fastreload == "LostShipsCity" && !CheckCharacterItem(pchar, "map_LSC")) return false;
	
	int iFastColony = FindColony(loadedLocation.fastreload);
	if (iFastColony < 0) return true; // > ключ fastreload не колония - вне дипломатии, переход свободен

	string sNation = Colonies[iFastColony].nation;
	if (sNation != "none")
	{
		int i = sti(sNation);
		bool bOk = (GetNationRelation2MainCharacter(i) == RELATION_ENEMY) || GetRelation2BaseNation(i) == RELATION_ENEMY;
		
		if (bOk && (i != PIRATE))
			return GetSneakFastReload(); // > если есть действующая лицензия, то при пройденной проверке не запрещаем быстрый переход
		else
			return true;
	}
	
	return true;
}

string StrReplace(string strSource, string from, string into, bool bFirst)
{
	if (findSubStr(strSource, from, 0) < 0) return strSource;
	int iStep = strlen(from) - 1;
	int sourceSize = strlen(strSource);
	string sCut, sResult;
	for (int i = 0; i < sourceSize; i++)
	{
	    if (i + iStep >= sourceSize)
	    {
	        sResult += strcut(strSource, i, sourceSize - 1);
	        return sResult;
	    }
	    sCut = strcut(strSource, i, i + iStep);
	    if (sCut == from)
	    {
	        sResult += into;
	        i += iStep;
	        if (bFirst) return sResult + strcut(strSource, i + 1, sourceSize - 1);
	    }
	    else sResult += strcut(strSource, i, i);
	}
	return sResult;
}

//функция заменяет все найденные совпадения и возвращает измененную строку
string StrReplaceAll(string strSource, string from, string into)
{
	return StrReplace(strSource, from, into, false);
}

//функция заменяет первое найденное совпадение и возвращает измененную строку
string StrReplaceFirst(string strSource, string from, string into)
{
    return StrReplace(strSource, from, into, true);
}

void GiveGoldOnAmount(int moneyQty)
{
	//TODO: оценка сундука в 12к и мерного самородка в 0.2к стандартно используется в скриптах, например:
	//makeint(sti(pchar.GenQuest.Convict.Sum)/200) и makeint(sti(NPChar.Quest.BurntShip.Money)/12000)
	//но, вероятно, честнее привязать стоимость к уровню? кстати, makeint там не нужен
	int chestsQty = moneyQty / 13000;
	int barsQty  = (moneyQty % 13000) / 220;
	AddItemLog(pchar, "chest,jewelry5", "" + chestsQty + "," + barsQty, StringFromKey("InfoMessages_133"), "Important_item");
}

void RandTeacher(ref chr) //Rosarak. Параметры учителей тут
{
	float fResult = round_up(makefloat(GetCharacterSPECIAL(pchar, SPECIAL_L) + GetSummonSkillFromNameToOld(pchar, SKILL_FORTUNE)) / 10.0) + GetFortuneBonus(1);
	if(fResult > Rand(28))
	{
		string ModelType;
		int Rank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 15;
		int Scl = 30 + 2*sti(pchar.rank);
		chr.diag = 18;
		chr.diag.skill = rand(7);
		switch(sti(chr.diag.skill))
		{
			case 0: //Фехтование и Защита (наёмник)
				chr.greeting = "Enc_Waiker";
				ModelType = "mercenary";
				Rank = 100;
				Scl = 100;
				chr.MultiFighter = 2.0;
			break;
			case 1: //Лидерство (мореплаватель)
				chr.greeting = "Gr_MiddPirate";
				ModelType = "senior";
				Rank = 100;
				Scl = 100;
				chr.MultiFighter = 2.0;
			break;
			case 2: //Навигация (штурман)
				chr.greeting = "Voice\" + VoiceGetLanguage() + "\Gr_Tavern_Mate_1.wav";
				ModelType = "pofficer";
			break;
			case 3: //Меткость (канонир)
				chr.greeting = "Voice\" + VoiceGetLanguage() + "\pirat_guard_4.WAV";
				ModelType = "pofficer";
			break;
			case 4: //Орудия (канонир)
				chr.greeting = "Voice\" + VoiceGetLanguage() + "\pirat_guard_4.WAV";
				ModelType = "pofficer";
			break;
			case 5: //Абордаж (боцман)
				chr.greeting = "Voice\" + VoiceGetLanguage() + "\PDM\Privetstvu_vas_kapitan.wav";
				ModelType = "pofficer";
			break;
			case 6: //Починка (работник верфи)
				chr.greeting = "Gr_Master";
				ModelType = "shipowner";
			break;
			case 7: //Торговля (купец)
				chr.greeting = "Gr_bankeer";
				ModelType = "merchant";
			break;
		}
		FantomMakeCoolFighter(chr, Rank, Scl, Scl, "auto", "auto", Scl*2);
		CreateModel(sti(chr.index), ModelType, MAN);
		SetNewModelToChar(chr);
	}
}

//Rosarak. Для боевых звуков
string GetSexCase(aref chr, string man, string woman, string skeleton)
{
	if(CheckAttribute(chr, "sex"))
	{
		switch(chr.sex)
		{
			case "man":			return man;			break;
			case "woman":		return woman;		break;
			case "skeleton":	return skeleton;	break;
		}
	}
	return "";
}

//выставить скорлупку в локации sLocation и локаторе sLocator (в последствии можно расширить на любое судно)
void DeployShipToReload(string sLocation, string sLocator)
{
    TEV.ship_to_reload.location = sLocation;
    TEV.ship_to_reload.locator  = sLocator;
    //если ГГ в той же локации то грузим в момент, если нет то загрузится само при входе в локу
    if (pchar.location == sLocation)
    {
        DeleteShipEnvironment();
        LocLoadShips(&Locations[FindLocation(sLocation)]);
    }
}

//убрать скорлупку
void DeleteShellBoat(string sLocation)
{
    DeleteAttribute(&TEV, "ship_to_reload");
    //если ГГ в той же локации то убираем в момент
    //TODO опасно убирать в момент, так как при стечении времени, при появлении фонариков на лодке что-то меняется в Entity, что приводит к вылету при вызове DeleteEntitiesByType("ship"); чинить надо в движке, когда пойму как
   /* if (pchar.location == sLocation)
    {
        DeleteShipEnvironment();
        LocLoadShips(&Locations[FindLocation(sLocation)]);
    }*/
}

//Радиусы box-локаторов склепа и крипты
void CryptBoxRadius(int n, string size)
{
	switch(size)
	{
	case "big":
		locations[n].locators_radius.box.box5 = 1.2;
		locations[n].locators_radius.box.box6 = 1.2;
		locations[n].locators_radius.box.box7 = 1.2;
		locations[n].locators_radius.box.box8 = 1.2;
		break;
	case "small":
		locations[n].locators_radius.box.box4 = 1.2;
		break;
	}
}

//получение свободного и открытого помещения в городе для квестовых нужд
string GetRandomCommonLoc(ref npchar)
{
    aref arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2, iLoc;
    int howStore = 0;
	string LocId;
	string storeArray[50];
	string sPlaceTaken = "Init";

	//фильтруем локацию по квесту доставки малявы
	CheckQuestCommonLoc("questTemp.jailCanMove.Deliver.locationId", &sPlaceTaken);
	//фильтруем локацию по квесту поиска шпионов
	CheckQuestCommonLoc("GenQuest.SeekSpy.Location", &sPlaceTaken);
	//фильтруем локацию по квесту Дело чести
	CheckQuestCommonLoc("QuestTemp.AffairOfHonor.CoatHonor.locationId", &sPlaceTaken);

	// > без города искать нечего
	if (!CheckAttribute(npchar, "city")) return "none";
	iLoc = FindLocation(npchar.city + "_town");
	if (iLoc < 0) return "none";

    makearef(arRld, Locations[iLoc].reload);
	Qty = GetAttributesNum(arRld);
    for (i=0; i<Qty; i++)
    {
        arCommon = GetAttributeN(arRld, i);
        if (!CheckAttribute(arCommon, "go")) continue;
        LocId = arCommon.go;
        if (HasSubStr(LocId, "Common") && !HasStrEx(LocId, sPlaceTaken, "|") && howStore < 50)
        {
            storeArray[howStore] = LocId;
            howStore++;
        }
        if (CheckAttribute(arCommon, "label") && arCommon.label == "Sea") continue;
        if (CheckAttribute(arCommon, "questDisable")) continue;
        // > в переход проваливаемся только если там действительно есть локация и она доступна к посещению
        iLoc = FindLocation(LocId);
        if (iLoc < 0) continue;
        makearef(arRld2, Locations[iLoc].reload);
        Qty2 = GetAttributesNum(arRld2);
        for (n=0; n<Qty2; n++)
        {
            arCommon = GetAttributeN(arRld2, n);
            if (!CheckAttribute(arCommon, "go")) continue;
            LocId = arCommon.go;
            if (HasSubStr(LocId, "Common") && !HasStrEx(LocId, sPlaceTaken, "|") && !StrHasStr(LocId, "CommonBedroom,CommonPackhouse_1,CommonPackhouse_2,CommonResidence_1,CommonResidence_2,CommonResidence_3,CommonResidence_4", true) && howStore < 50)
            {
                storeArray[howStore] = LocId;
                howStore++;
            }
        }
    }
	if (howStore == 0) return "none";
	LocId = storeArray[dRand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for (n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId)
		    characters[n].lifeDay = 0;
	}
	return LocId;
}

void CheckQuestCommonLoc(string sPath, string sPlaceTaken)
{
    if (CheckAttribute(pchar, sPath) && pchar.(sPath) != "")
        sPlaceTaken = sPlaceTaken + "," + pchar.(sPath);
}

// Перенесён из Habitue_dialog.c
bool CheckFreeSitFront(ref _npchar)
{
	ref rCharacter; //ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator")) return false;

	// Оптимизация
	for (n = 0; n < LAi_numloginedcharacters; n++)
	{
		makeref(rCharacter, Characters[LAi_loginedcharacters[n]]);
		if (!CheckAttribute(rCharacter, "location")) continue;
		if (rCharacter.id != "Blaze" && rCharacter.location.locator == _npchar.Default.ToLocator)
		{
			return false;
		}
	}
	return true;
}

// отдых/проматывание времени
bool IsTimeSkipAvailable()
{
    return IsTimeSkipPossible() && CheckPossibleTimeSkip();
}

bool IsTimeSkipPossible()
{
    bool bSeaBattle = (bDisableMapEnter) && (bSeaActive) && (!CheckAttribute(pchar, "GenQuest.MapClosedNoBattle"));

	return !LAi_IsFightMode(pchar) && !bSeaBattle && Pchar.questTemp.CapBloodLine == false &&
	PChar.location != "Deck_Near_Ship" && PChar.location != "CommonPackhouse_2" && !CheckAttribute(pchar, "GenQuest.CannotWait");
}

// Перенесён из MainHero_dialog.c
bool CheckPossibleTimeSkip()
{
	string sTemp = "";

	if (CheckAttribute(&TEV, "DesMoinesTimeSkipDisable"))
	{
		if (pchar.location == "DesMoines_town")
			return false;

		if (!CheckAttribute(pchar, "questTemp.MC.DesMoines") && reload_location_index > 0 && reload_cur_location_index > 0)
		{
			if (HasStr(locations[reload_location_index].id.label, "DesMoines") || HasStr(locations[reload_cur_location_index].id.label, "DesMoines"))
				return false;
		}
	}

	if (HasAttrValue(pchar, "questTemp.different.ShipyardsMap", "toTarget") && CheckAttribute(pchar, "questTemp.different.ShipyardsMap.city"))
	{
		sTemp = pchar.questTemp.different.ShipyardsMap.city;

		if (pchar.location == sTemp + "_Shipyard" || pchar.location == sTemp + "_Packhouse" || pchar.location == sTemp + "_PackhouseOffice")
			return false;
	}

	return true;
}
// <-- отдых/проматывание времени

string sfks(string any)
{
    return "'" + any + "'";
}

// AlexBlade - Create a matrix with rotation order rz * rx * ry
void CreateRotationMatrixZXY(float xAng, float yAng, float zAng, aref mtx)
{
	float _sinAx = sin(xAng);
    float _cosAx = cos(xAng);
    float _sinAy = sin(yAng);
    float _cosAy = cos(yAng);
    float _sinAz = sin(zAng);
    float _cosAz = cos(zAng);

    mtx.vx.x = _cosAz * _cosAy + _sinAz * _sinAx * _sinAy;
    mtx.vy.x = -_sinAz * _cosAy + _cosAz * _sinAx * _sinAy;
    mtx.vz.x = _cosAx * _sinAy;

    mtx.vx.y = _sinAz * _cosAx;
    mtx.vy.y = _cosAz * _cosAx;
    mtx.vz.y = -_sinAx;

	mtx.vx.z = _cosAz * -_sinAy + _sinAz * _sinAx * _cosAy;
    mtx.vy.z = -_sinAz * -_sinAy + _cosAz * _sinAx * _cosAy;
    mtx.vz.z = _cosAx * _cosAy;
}

// Wazar - Check for compilation errors for dialogs
void CheckSegmentsForCE()
{
	string sPrefix = "PROGRAM\";
	string sScriptsSubdir = "DIALOGS";
	int iPrefixLength = strlen(&sPrefix);

    object oFileFinder;
    string sSearchDir = sPrefix+sScriptsSubdir;

    oFileFinder.dir = sSearchDir;
    oFileFinder.mask = "*.c";
	oFileFinder.recursive = "1";
	oFileFinder.getpaths = "1";
	oFileFinder.stripOverlayPath = "1";
    CreateEntity(&oFileFinder, "FINDFILESINTODIRECTORY");

	aref arFileList;
    makearef(arFileList, oFileFinder.filelist);
    int iFileNum = GetAttributesNum(arFileList);
    DeleteClass(&oFileFinder);

	for(int n = 0; n < iFileNum; n++)
	{
		aref arFile = GetAttributeN(arFileList, n);
		string sFileName = GetAttributeValue(arFile);
		sFileName = strcut(&sFileName, iPrefixLength, strlen(&sFileName) - 1);
		if (LoadSegment(sFileName))
		{
			UnloadSegment(sFileName);
		}
		else
		{
			Trace("Find some error in " + sFileName);
		}
	}
}

bool checkRef(ref rChar)
{
	return CheckAttribute(rChar, "sex");
}

ref nullRef()
{
	return &NullCharacter;
}

bool TestMode()
{
	return bBettaTestMode || MOD_BETTATESTMODE == "On" || MOD_BETTATESTMODE == "Test";
}

void ResetParamsAfterSit()
{
    DelEventHandler("Control Activation", "LAi_GetUpCheck");
    DeleteAttribute(&TEV, "begin_sit");
    DeleteAttribute(PChar, "nonTable");
    PChar.turn_ang = 10.0;
}

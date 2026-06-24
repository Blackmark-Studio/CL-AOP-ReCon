
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

	int i, q1 = KZ|Symbol(str1, ",");
	int j, q2 = KZ|Symbol(str2, ",");
	string temp1, temp2;

	for (i = 0; i <= q2; i++)
	{
		temp2 = GetSubStr(str2, ",", i);
		if (temp2 == "") continue;

		for (j = 0; j <= q1; j++)
		{
			temp1 = GetSubStr(str1, ",", j);
			if (temp1 == "") continue;

			if (bIs)
			{
				if (temp1 == temp2)
					return true;
			}
			else if (HasStr(temp1, temp2))
				return true;
		}
	}

	return false;
}

// > найти в папке sFolder файл sFileName по маске sMask; если атрибут sFileName пустой, то искать только по маске sMask; bStrict - строгий поиск по точному имени
bool FindFile(string sFolder, string sFileName, string sMask, bool bStrict)
{
	if (!XI_CheckFolder(sFolder + "\"))
		return false;

	object fileFinder;
	aref fileList, file;
	int n, fileNum = 0;
	string fileName;

	DeleteAttribute(&fileFinder, "");
	SearchBase(&fileFinder, sFolder, sMask, "1", "0", "1");
	CreateEntity(&fileFinder, "FINDFILESINTODIRECTORY");

	makearef(fileList, fileFinder.filelist);
	fileNum = GetAttributesNum(fileList);
	DeleteClass(&fileFinder);

	if (fileNum > 0)
	{
		if (sFileName == "")
			return true;

		for (n = 0; n < fileNum; n++)
		{
			file = GetAttributeN(fileList, n);
			fileName = GetAttributeValue(file);

			if (bStrict)
			{
				if (fileName == sFileName)
					return true;
			}
			else
			{
				if (HasStr(fileName, sFileName))
					return true;
			}	
		}
	}

	return false;
}

void SearchBase(object oResFinder, string sDir, string sMask, string sRecursive, string sGetPaths, string sSOP)
{
	oResFinder.dir = sDir;
    oResFinder.mask = sMask;
	oResFinder.recursive = sRecursive;
	oResFinder.getpaths = sGetPaths;
	oResFinder.stripOverlayPath = sSOP;
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
		return 0;
	
	string sym, tmp = "";
	
	for (int i = strlen(path); i > 0; i--)
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
				return 1;
			}
		}
	}
	
	return 0;
}

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
				else if (StrHasStr(sItemName, "indian18,indian19", 1))
					value -= 10;
				else if (sItemName == "indian21")
					value -= 5;
				else if (sItemName == "PDM_PJ_BsRL")
					value -= 2;
				else if (sItemName == "mineral4")
					value -= 1;
			}
			else // > Fortune
			{
				if (sItemName == "DeSouzaCross")
					value += 15;
				else if (sItemName == "PDM_PJ_BsRL")
					value += 2;
				else if (StrHasStr(sItemName, "jewelry8,jewelry9", 1))
					value += 1;
				else if (sItemName == "Cursed_idol")
					value -= 80;
				else if (sItemName == "Coins")
					value -= 50;
				else if (StrHasStr(sItemName, "SkullAztec,indian22", 1))
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
	float chance = GetCharacterSPECIAL(pchar, SPECIAL_L) + GetCharacterSPECIAL(pchar, SPECIAL_P) + round_up(makefloat(GetCharacterSkill(pchar, "Sneak")) / 3) + round_up(makefloat(GetCharacterSkill(pchar, "Fortune")) / 4);

	if (CheckAttributeEx(pchar, "Skill.Sneak,Skill.Fortune", "&"))
	{
		if (sti(pchar.Skill.Sneak) >= 100)
			chance = chance + GetItemSneakBonus(0); // если "Скрытность" полностью прокачана, то все предметы со статами к этому умению получают вторую жизнь - 10% от бонуса (-10% от штрафа) к chance
		
		if (sti(pchar.Skill.Fortune) >= 100)
			chance = chance + GetItemSneakBonus(1); // то же самое для "Везения"
	}

	Restrictor(&chance, 0.0, 100.0);

	return chance;
}

int GetSneakChanceBonus()
{
	int chance = GetFortuneBonus(5);

	if (CheckCharacterPerk(pchar, "Trustworthy"))
		chance += 5;

	return chance;
}

void GipsyFortuneBonusEnd(string str)
{
	DeleteQuestCondition("GipsyFortuneBonusEnd");
	DeleteAttributeMass(&TEV, "", "GipsyFortuneBonus,GipsyFortuneTimer,GipsyFortuneText");
}

// > при наличии бонуса от гадания цыганки вернуть result равное value
float GetFortuneBonus(float value)
{
	float result = 0.0;
	
	if (CheckAttribute(&TEV, "GipsyFortuneBonus"))
		result = value;
	
	return result;
}

// > проверка целого значения на нечётность
bool CheckOddValue(int value)
{
	if (value%2 > 0)
		return true;
	
	return false;
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
	while (GetMonthDays(curMonth, GetDataYear()) < nextDay)
	{
		nextDay = nextDay - GetMonthDays(curMonth, GetDataYear());
		curMonth++;
	}
	
	int nextMonth = curMonth;
	int nextYear = GetDataYear();
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
	if (ItemCheck(chr, "map_full,mapQuest", 0) || ItemCheck(chr, "map_part1,map_part2", 1))
		return true;
	
	return false;
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
	int n, q = KZ|Symbol(sType, ",");
	string tmp;

	for (n = 0; n <= q; n++)
	{
		tmp = stripblank(GetSubStr(sType, ",", n));
		
		if (tmp != "")
		{
			tmp = "Forbidden." + tmp;
			
			if (bBan)
				TEV.(tmp) = "1";
			else
				DeleteAttribute(&TEV, tmp);
		}
	}
}

// > проверка запретов
bool GetBan(string sType)
{
	if (CheckAttribute(&TEV, "Forbidden." + sType) && TEV.Forbidden.(sType) == "1")
		return true;

	return false;
}

// > сообщения в логе со звуковым сопровождением; отделяя знаком "&" можно задать несколько strings и sounds
void LogSound(string strings, string sounds)
{
	int q, n;
	string tmp, snd = "";
	
	if (strings != "")
	{
		q = KZ|Symbol(strings, "&");
		
		for (n = 0; n <= q; n++)
		{
			tmp = GetSubStr(strings, "&", n);
			
			if (tmp != "")
			    Notification(tmp, "none");
		}
	}
	
	if (sounds != "")
	{
		q = KZ|Symbol(sounds, "&");
		
		for (n = 0; n <= q; n++)
		{
			tmp = GetSubStr(sounds, "&", n);
			
			if (tmp != "" && snd != tmp)
			{
				snd = tmp;
				PlaySound(snd);
			}
		}
	}
}

// > множественные сообщения в логе; отделяя знаком "&" можно задать несколько strings
void Logs(string strings)
{
	int q, n;
	string tmp, snd = "";
	
	if (strings != "")
	{
		q = KZ|Symbol(strings, "&");
		
		for (n = 0; n <= q; n++)
		{
			tmp = GetSubStr(strings, "&", n);
			
			if (tmp != "")
				Log_Info(tmp);
		}
	}
}

// LogSound с новой системой оповещений
void LogSound_WithNotify(string strings, string sounds, string iconName)
{
    int q, n;
    string tmp, snd = "";

    if (strings != "")
    {
        q = KZ|Symbol(strings, "&");

        for (n = 0; n <= q; n++)
        {
            tmp = GetSubStr(strings, "&", n);

            if (tmp != "")
            {
                string _iconName = "none";
                if (iconName != "")
                {
                    _iconName = iconName;
                }
                Notification(tmp, iconName);
            }
        }
    }

    if (sounds != "")
    {
        q = KZ|Symbol(sounds, "&");

        for (n = 0; n <= q; n++)
        {
            tmp = GetSubStr(sounds, "&", n);

            if (tmp != "" && snd != tmp)
            {
                snd = tmp;
                PlaySound(snd);
            }
        }
    }
}

// > выдача или отъём предметов с текстовым и звуковым сопровождением
void AddItemLog(ref rChar, string sItems, string sQty, string str, string snd)
{
	// Автоудаление пробелов
	sItems = stripblank(sItems);
	sQty = stripblank(sQty);
	int iQty;
	
	int iNum, coms = KZ|Symbol(sItems, ","); // Sticks: чтоб в цикле не пересчитывать одно и тоже
	string tmp;
	
	for (iNum = 0; iNum <= coms; iNum++)
	{
	    iQty = sti(GetSubStr(sQty, ",", iNum));
	    if (iQty < 0)
	        TakeNItems(rChar, sItems, iQty);
		else
		    GenerateAndAddItems(rChar, GetSubStr(sItems, ",", iNum), iQty);
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
// В качестве sCond задаётся "&" (условие "&&") и "|" или любой другой символ (условие "||")
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

	if (HasStr(sCond, "&"))
		sCond = "&";
	else
		sCond = "|";

	int i, iAttrs = KZ|Symbol(sLeaves, ",");
	int n = -1;

	string sT;

	for (i = 0; i <= iAttrs; i++)
	{
		sT = GetSubStr(sLeaves, ",", i);

		switch (sCond)
		{
			case "&":
				if (CheckAttribute(&oTree, sBranch + sT))
					n++;
				else
					return false;
			break;
			case "|":
				if (CheckAttribute(&oTree, sBranch + sT))
					return true;
			break;
		}
	}

	if (n >= iAttrs)
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
	int i, res = 0;
	int n = KZ|Symbol(subStr, ",");
	
	if (coreStr != "")
		coreStr += ".";
	
	for (i = 0; i <= n; i++)
	{
		if (CheckAttribute(&obj, coreStr + GetSubStr(subStr, ",", i)))
			res++;
	}
	
	return res;
}

// csmDeleteAttributeMassive --> DeleteAttribute, рассчитанный на массовое удаление аттрибутов у объекта
// sBranch не обязателен, если в нем нет нужды (в таком случае, следует оставить кавычки пустыми)
// В sLeaves через запятую и без пробелов можно указывать перечень аттрибутов к удалению у объекта oTree
void DeleteAttributeMass(object oTree, string sBranch, string sLeaves)
{
	int iA, iLeaves = KZ|Symbol(sLeaves, ",");

	if (sLeaves == "")
		return;

	if (sBranch != "")
		sBranch += ".";

	// Автоудаление пробелов, сейчас оставлено так на случай, если они там быть должны
	//sBranch = stripblank(sBranch);
	//sLeaves = stripblank(sLeaves);

	for (iA = 0; iA <= iLeaves; iA++)
	{
		DeleteAttribute(&oTree, sBranch + GetSubStr(sLeaves, ",", iA));
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
bool HasStr(string sText, string sAttr)
{
	bool bHas = FindSubStr(GetStrSmallRegister(sText), GetStrSmallRegister(sAttr), 0) != -1;
	return bHas;
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
	if (CheckAttribute(_rChar, _sAttr) && _rChar.(_sAttr) == _sValue)
		return true;
	
	return false;
}

// KZ > Метод проверяет у объекта _rChar атрибут _sAttr на наличие в нём значения _sValue
bool HasAttrValue(ref _rChar, string _sAttr, string _sValue)
{
	if (CheckAttribute(_rChar, _sAttr) && HasStrEx(_rChar.(_sAttr), _sValue, "|"))
		return true;
	
	return false;
}

// csmHasStringMassive --> апгрейднутый вариант HasStr, рассчитанный на массовый чек значений sAttrs в строке sText
// Есть ли в строке sText всё или что-то из указанного в sAttrs, разделённое символом sDiv
// В качестве sCond задаётся "=" (условие "=="; чувствительно к регистру, прочие два нет), "&" (условие "&&") и "|" или любой другой символ (условие "||")
bool HasStrMass(string sText, string sAttrs, string sDiv, string sCond)
{
	if (strlen(sText) <= 0 || strlen(sAttrs) <= 0)
		return false;

	if (sDiv == "")
		sDiv = ",";

	if (HasStr(sCond, "&"))
		sCond = "&";
	else
	{
		if (HasSubStr(sCond, "="))
			sCond = "=";
		else 
			sCond = "|";
	}

	int i, iAttrs = KZ|Symbol(sAttrs, sDiv);
	int n = -1;

	string sT;

	for (i = 0; i <= iAttrs; i++)
	{
		sT = GetSubStr(sAttrs, sDiv, i);
		
		if (sT == "")
		{
			continue;
		}
		
		switch (sCond)
		{
			case "=":
				if (HasSubStr(sText, sT))
					n++;
				else
					return false;
			break;
			case "&":
				if (HasStr(sText, sT))
					n++;
				else
					return false;
			break;
			case "|":
				if (HasStr(sText, sT))
					return true;
			break;
		}
	}

	if (n >= iAttrs)
		return true;

	return false;
}

// > разделитель всегда запятая
bool HasStrEx(string str, string attr, string cond)
{
	return HasStrMass(str, attr, ",", cond);
}

// Чуть видоизмененная функция GetSubStringByNum: в качестве разделителя sDiv, можно указывать любой символ, не только запятую
// Возвращает часть строки sText перед указанным в iSelect (отсчёт с нуля) разделителем sDiv
string GetSubStr(string sText, string sDiv, int iSelect)
{
	if (sDiv == "")
		sDiv = ",";

	string sTemp = sText;
	int i, iNumFind = 1;
	int iLastPos = 0;
	int iFindPos = findSubStr(&sTemp, sDiv, 0);

	if (iFindPos < 0)
		return sTemp;

	while (iFindPos > 0)
	{
		iNumFind++;
		iFindPos = findSubStr(&sTemp, sDiv, iFindPos + 1);
	}

	if (iNumFind <= iSelect)
		return GetSubStr(sTemp, sDiv, 0);

	iFindPos = 0;

	for (i = 0; i < iNumFind; i++)
	{
		iFindPos = findSubStr(&sTemp, sDiv, iFindPos + 1);

		if (i == iSelect)
		{
			if (iFindPos < 0)
				iFindPos = strlen(&sTemp);

			if (iLastPos >= iFindPos)
				iFindPos = iLastPos + 2;

			return strcut(&sTemp, iLastPos, iFindPos - 1);
		}

		iLastPos = iFindPos + 1;
	}

	return GetSubStr(sTemp, sDiv, 0);
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
	
	int iNum, coms = KZ|Symbol(sItems, ","); // Sticks: чтоб в цикле не пересчитывать одно и тоже
	int iQty = KZ|Symbol(sQty, ",");
	string sN, sQ;
	
	for (iNum = 0; iNum <= coms; iNum++)
	{
		sN = sItems;
		sQ = sQty;
		
		if (coms > 0)
			sN = GetSubStr(sItems, ",", iNum);
		
		if (iQty > 0)
			sQ = GetSubStr(sQty, ",", iNum);
		
		if (sN != "")
			ItemTake(rChar, sN, sti(sQ));
	}
}

// > выдать rChar предметы sItems и сразу экипировать их (bGen - генерировать ли предмет)
void ItemTakeEquip(ref rChar, string sItems, bool bGen)
{
	int i, n = KZ|Symbol(sItems, ",");
	string s;
	
	for (i = 0; i <= n; i++)
	{
		s = GetSubStr(sItems, ",", i);
		
		if (s == "")
			continue;
		
		if (bGen)
			s = GetGeneratedItem(s);
		
		if (TakeNItems(rChar, s, 1))
			EquipCharacterByItem(rChar, s);
	}
}

// > проверить инвентарь rChar на наличие предметов sItems; требуемое кол-во можно указать после знака ":" прямо в sItems, например: "bullet:6,gunpowder:4,potionrum" - нужно 6+ пуль, 4+ пороха и 1+ бутылка рома (отсутствие ":" считается за 1)
// "gold" можно проверять деньги rChar ("bullet:6,gunpowder:4,potionrum,gold:9500")
// при bAll необходимо наличие всех предметов sItems с указанным кол-ом, при !bAll нужно хоть что-то из sItems в кол-ве как минимум 1 шт
bool ItemCheck(ref rChar, string sItems, bool bAll)
{
	int i, q, s = KZ|Symbol(sItems, ",");
	int r = -1;
	string tmp;
	
	for (i = 0; i <= s; i++)
	{
		tmp = GetSubStr(sItems, ",", i);
		
		if (KZ|Symbol(tmp, ":") > 0)
		{
			q = sti(FindStringAfterChar(tmp, ":"));
			tmp = FindStringBeforeChar(tmp, ":");
		}
		
		if (q < 1)
			q = 1;
		
		if (tmp == "gold")
		{
			if (sti(rChar.money) > 0)
			{
				if (bAll)
				{
					if (sti(rChar.money) >= q)
						r++;
					else
						return false;
				}
				else
					return true;
			}
		}
		else
		{
			if (GetCharacterItem(rChar, tmp) >= q)
			{
				if (bAll)
					r++;
				else
					return true;
			}
		}
	}
	
	if (r >= s)
		return true;
	
	return false;
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
		string sNation = Colonies[FindColony(loadedLocation.fastreload)].nation;
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

		int c2 = strlen(sLine2);
		int c3 = strlen(sLine3);

		int k2 = 0;
		int k3 = 0;

		// KZ > TODO use TaskWindow
		if (!or(c2 == 55 && c3 == 62, c2 == 55 && c3 == 60))
		{
			if (!IsDay())
			{
				k2 += 2;
				k3 += 2;

				if (c2 == 58)
				{
					if (c3 == 69) k3 += 3;
					else if (c3 == 68) k3 += 2;
					else if (c3 == 66 || c3 == 67) k2 -= 1;
				}
				else if (c3 == 64)
				{
					if (c2 == 57) k2 -= 1;
					else if (c2 == 60) k3 -= 1;
				}
				else if (or(c2 == 59, c2 == 60) && c3 == 69)
				{
					k3 += 2;
					if (c2 == 59) k2 -= 1;
				}
			}
			else if (c2 == 57)
			{
				if (c3 == 60) k3 -= 1;
				else if (c3 == 65) k3 += 2;
				else if (c3 == 67) k3 += 3;
				else if (c3 == 69) k3 += 4;
			}
			else if (c2 == 53)
			{
				if (c3 == 60)
				{
					k2 -= 2;
					k3 -= 1;
				}
				else if (c3 == 61 || c3 == 62)
					k2 -= 2;
				else if (c3 == 64)
				{
					k2 -= 1;
					k3 += 2;
				}
			}
			else if (c2 == 55)
			{
				if (c3 == 65)
				{
					k2 -= 1;
					k3 += 2;
				}
				else if (c3 == 67)
				{
					k2 -= 1;
					k3 += 3;
				}
				else if (c3 == 69)
				{
					k2 -= 1;
					k3 += 4;
				}
			}
			else if (c2 == 56 && or(c3 == 67, c3 == 69))
				k3 += 3;
		}
		else if (c2 == 55)
		{
			if (c3 == 60) k3 -= 1;
			else if (c3 == 62) k2 -= 1;
		}

		aref arChar; makearef(arChar, objLandInterface.data.icons.id0);
		if (arChar.HideStates == 0) iOffset = 230;

		SetNewTextInfoEx("AltModificatorLine1", -1.0, XI_ConvertString("ft_Help"), sti(showWindow.left) + RecalculateHIcon(makeint((iOffset + 325) * fHtRatio)), RecalculateVIcon(makeint(30 * fHtRatio)), "interface_normal", 1.1 * fHtRatio, argb(243,254,252,169));
		SetNewTextInfoEx("AltModificatorLine2", -1.0, sLine2, sti(showWindow.left) + RecalculateHIcon(makeint((iOffset + 342 + k2) * fHtRatio)), RecalculateVIcon(makeint(52 * fHtRatio)), "interface_normal", 1.1 * fHtRatio, argb(255,255,255,255));
		SetNewTextInfoEx("AltModificatorLine3", -1.0, sLine3, sti(showWindow.left) + RecalculateHIcon(makeint((iOffset + 364 + k3) * fHtRatio)), RecalculateVIcon(makeint(74 * fHtRatio)), "interface_normal", 1.1 * fHtRatio, argb(255,255,255,255));
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
	
	string sNation = Colonies[FindColony(loadedLocation.fastreload)].nation;
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
    int	i, n, Qty, Qty2;
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

    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    for (i=0; i<Qty; i++)
    {
        arCommon = GetAttributeN(arRld, i);
        LocId = arCommon.go;
        if (HasSubStr(LocId, "Common") && !HasStrEx(LocId, sPlaceTaken, "|"))
        {
            storeArray[howStore] = LocId;
            howStore++;
        }
        if (arCommon.label != "Sea" && !CheckAttribute(arCommon, "questDisable"))
        {
            makearef(arRld2, Locations[FindLocation(LocId)].reload);
            Qty2 = GetAttributesNum(arRld2);
            for (n=0; n<Qty2; n++)
            {
                arCommon = GetAttributeN(arRld2, n);
                LocId = arCommon.go;
                if (HasSubStr(LocId, "Common") && !HasStrEx(LocId, sPlaceTaken, "|") && !StrHasStr(LocId, "CommonBedroom,CommonPackhouse_1,CommonPackhouse_2,CommonResidence_1,CommonResidence_2,CommonResidence_3,CommonResidence_4", 1))
                {
                    storeArray[howStore] = LocId;
                    howStore++;
                }
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
			return  false;
		}
	}
	return  true;
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
	if (bBettaTestMode || MOD_BETTATESTMODE == "On" || MOD_BETTATESTMODE == "Test")
		return true;
	return false;
}

void ResetParamsAfterSit()
{
    DelEventHandler("Control Activation", "LAi_GetUpCheck");
    DeleteAttribute(&TEV, "begin_sit");
    DeleteAttribute(PChar, "nonTable");
    PChar.turn_ang = 10.0;
}

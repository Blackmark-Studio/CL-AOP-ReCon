//======================================================================================================================
//                      функции для взаимодействия с массивами
//
//  сравнение значений:
//  точное  				- ArrayIsEqualValue, ArrayRemoveValue
//  подстрока 				- ArrayIsContainValue, ArrayFindRandomValue
//  список через HasStrEx 	- ArrayFindRandomIndex
//======================================================================================================================

//слияние массивов. к массиву 1 добавляется массив 2
void ArrayAddAll(ref array_1, ref array_2)
{
    if (ArrayIsEmpty(array_2)) return; //если второй массив пустой, то можно ничего не делать

    int base = 0;
    if (!ArrayIsEmpty(array_1)) base = GetArraySize(array_1); //пустой массив перезаписываем с нуля, а не дописываем к дырке

    int arraySize_2 = GetArraySize(array_2); //размер читаем до SetArraySize - иначе сломается слияние массива с самим собой
    string newValue;

    SetArraySize(array_1, base + arraySize_2);
    for (int i = 0; i < arraySize_2; i++)
    {
        newValue = array_2[i];
        array_1[base + i] = newValue;
    }
}

//добавление значения в массив с увеличением размера
void ArrayAddValue(ref array, string value)
{
    if (ArrayIsEmpty(array))
    {
        array[0] = value;
    }
    else
    {
        int newArraySize = GetArraySize(array) + 1;
        SetArraySize(array, newArraySize);
        array[newArraySize-1] = value;
    }
}
//получение случайного значения с удалением и уменьшением размера массива
//если массив пустой возвращается пустая строка
//удаляется именно вытянутый индекс, а не первое равное значение - из дублей уходит вытянутый, пустая дырка тоже уходит
string ArrayCutRandomValue(ref array)
{
    if (ArrayIsEmpty(array)) return "";
    int index = rand(GetArraySize(array) - 1);
    string result = array[index];
    ArrayRemoveValueByIndex(array, index);
    return result;
}

//получение случайного значения из найденных по неполному соответствию
//если значение не найдено, то возвращается пустая строка
string ArrayFindRandomValue(ref array, string value)
{
    string result = "";
    if (ArrayIsEmpty(array)) return result;
    int arraySize = GetArraySize(array);
    int i, found = 0;

    //два прохода вместо временного массива
    for (i = 0; i < arraySize; i++)
    {
        if (HasStr(array[i], value)) found++;
    }
    if (found == 0) return result;

    int pick = rand(found - 1);
    for (i = 0; i < arraySize; i++)
    {
        if (HasStr(array[i], value))
        {
            if (pick == 0)
            {
                result = array[i];
                return result;
            }
            pick--;
        }
    }
    return result;
}

//получение случайного индекса из найденных по строковому списку
//если значение не найдено, то возвращается -1
int ArrayFindRandomIndex(ref array, string value)
{
    if (ArrayIsEmpty(array)) return -1;
    string sTemp;
    int arraySize = GetArraySize(array);
    int i, found = 0;

    for (i = 0; i < arraySize; i++)
    {
        sTemp = array[i];
        if (HasStrEx(sTemp, value, "|")) found++;
    }
    if (found == 0) return -1;

    int pick = rand(found - 1);
    for (i = 0; i < arraySize; i++)
    {
        sTemp = array[i];
        if (HasStrEx(sTemp, value, "|"))
        {
            if (pick == 0) return i;
            pick--;
        }
    }
    return -1;
}

//получение случайного значения из массива
//если массив пустой, то возвращается пустая строка
string ArrayGetRandomValue(ref array)
{
    string result = "";
    if (ArrayIsEmpty(array)) return result;
    result = array[rand(GetArraySize(array) - 1)];
    return result;
}

//проверка содержит ли массив переданное значение (по вхождению подстроки, точное сравнение - ArrayIsEqualValue)
bool ArrayIsContainValue(ref array, string value)
{
    if (ArrayIsEmpty(array)) return false;
    int arraySize = GetArraySize(array);

    for (int i = 0; i < arraySize; i++)
    {
        if (HasStr(array[i], value)) return true;
    }
    return false;
}

//поиск в массиве значения по жесткому соответствию
bool ArrayIsEqualValue(ref array, string value)
{
    if (ArrayIsEmpty(array)) return false;
    int arraySize = GetArraySize(array);

    for (int i = 0; i < arraySize; i++)
    {
        if (array[i] == value) return true;
    }
    return false;
}

//определение пустой ли массив
bool ArrayIsEmpty(ref array)
{
    int arraySize = GetArraySize(array);
    //битый или неинициализированный ref - GetArraySize отдаёт 0, иначе такой массив просочится во все функции файла
    if (arraySize < 1) return true;
    //массива с размером равным 0 быть не может, потому проверяем на пустоту значения.
    if (arraySize == 1)
    {
        if (array[0] == "") return true;
    }
    //это условие нужно для удобства работы с массивами когда надо заполнить его с нуля.
    //т.к. создать новый массив в скриптах можно только с размером 2 и больше, если указать размер 1, то оно считается просто строкой
    //попутно такой массив сжимается до размера 1 - на это опирается ArrayAddValue
    if (arraySize == 2)
    {
        if (array[0] == "" && array[1] == "")
        {
            ArrayClear(array);
            return true;
        }
    }
    return false;
}

//очистка массива
void ArrayClear(ref array)
{
    SetArraySize(array, 1);
    array[0] = "";
}

//удаление первого совпавшего значения из массива с уменьшением размера
//если значение не найдено, массив не меняется
void ArrayRemoveValue(ref array, string value)
{
    int arraySize = GetArraySize(array); //ArrayIsEmpty здесь не нужен, его сделает ArrayRemoveValueByIndex

    for (int i = 0; i < arraySize; i++)
    {
        if (array[i] == value)
        {
            ArrayRemoveValueByIndex(array, i);
            return;
        }
    }
}

//удаление значения из массива по индексу с уменьшением размера
//если индекс вне диапазона, массив не меняется
void ArrayRemoveValueByIndex(ref array, int index)
{
    if (ArrayIsEmpty(array)) return;
    int arraySize = GetArraySize(array);
    if (index < 0 || index >= arraySize) return;

    string newValue;
    for (int i = index; i < arraySize - 1; i++)
    {
        newValue = array[i+1];
        array[i] = newValue;
    }
    if (arraySize == 1) array[0] = "";
    else SetArraySize(array, arraySize - 1);
}

// перемешивание элементов массива (int)
void ShuffleArray_Int(ref array)
{
    int elementsCount = GetArraySize(array);
    for (int i = elementsCount - 1; i >= 1; i--)
    {
        int j = rand(i);
        int _tmpElementJ = array[j];
        int _tmpElementI = array[i];
        array[j] = _tmpElementI;
        array[i] = _tmpElementJ;
    }
}

// перемешивание элементов массива (string)
void ShuffleArray_String(ref array)
{
    int elementsCount = GetArraySize(array);
    for (int i = elementsCount - 1; i >= 1; i--)
    {
        int j = rand(i);
        string _tmpElementJ = array[j];
        string _tmpElementI = array[i];
        array[j] = _tmpElementI;
        array[i] = _tmpElementJ;
    }
}

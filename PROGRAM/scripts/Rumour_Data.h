#define SIMPLE_RUMOUR_NUM	12
#define CITIZEN_RUMOUR_NUM	10

// KZ > ref 08.07.2026, уменьшение дёрганья StringFromKey

/// Слухи по осадам / шебеке / Шарпу / ацтекам / ГПК + общие
// 0..30 -> Rumour_Data_1..31
string DefaultText(int index)
{
    string sKey = "Rumour_Data_" + (index + 1);
    return StringFromKey(sKey);
}

/// Слухи нищих
// 0..9 -> Rumour_Data_32..41
string PoorRumourText(int index)
{
    string sKey = "Rumour_Data_" + (index + 32);
    return StringFromKey(sKey);
}

/// Сплетни при отсутствии актуальных слухов (простолюдинов, корчмарей, маргиналов, ...)
// 0..11 -> Rumour_Data_42..53
string NoRumourText(int index)
{
    string sKey = "Rumour_Data_" + (index + 42);
    return StringFromKey(sKey);
}

/// Сплетни капитанов (при отсутствии актуальных слухов)
// 0..9 -> Rumour_Data_54..63
string CaptainRumourText(int index)
{
    string sKey = "Rumour_Data_" + (index + 54);
    return StringFromKey(sKey);
}

/// Сплетни мещан мужские (при отсутствии актуальных слухов)
// 0..9 -> Rumour_Data_64..73
string CitizenManRumourText(int index)
{
    string sKey = "Rumour_Data_" + (index + 64);
    return StringFromKey(sKey);
}

/// TODO: Сплетни мещан женские (при отсутствии актуальных слухов)
// 0..3 -> _74..77 ; 7,8 -> _78,79 ; 4,5,6,9 - заглушки
string CitizenWomanRumourText(int index)
{
    int n = -1;
    if (index >= 0 && index <= 3) n = index + 74;
    if (index == 7 || index == 8) n = index + 71;
    if (n < 0) return "------------";

    string sKey = "Rumour_Data_" + n;
    return StringFromKey(sKey);
}

/// Сплетни дворян (при отсутствии актуальных слухов)
// 0..9 -> Rumour_Data_80..89
string NobleManRumourText(int index)
{
    string sKey = "Rumour_Data_" + (index + 80);
    return StringFromKey(sKey);
}

/// TODO: Сплетни дворянок (при отсутствии актуальных слухов)
// 0..3 -> _90..93 ; 7,8 -> _94,95 ; 4,5,6,9 - заглушки
string NobleWomanRumourText(int index)
{
    int n = -1;
    if (index >= 0 && index <= 3) n = index + 90;
    if (index == 7 || index == 8) n = index + 87;
    if (n < 0) return "------------";

    string sKey = "Rumour_Data_" + n;
    return StringFromKey(sKey);
}

/// Сплетни матросов (при отсутствии актуальных слухов)
// 0..9 -> Rumour_Data_96..105
string SailorRumourText(int index)
{
    string sKey = "Rumour_Data_" + (index + 96);
    return StringFromKey(sKey);
}

/// Если новостей нет в ГПК
// 0..4 -> Rumour_Data_106..110
string NoRumourTextLSC(int index)
{
    string sKey = "Rumour_Data_" + (index + 106);
    return StringFromKey(sKey);
}

string	sEnManFaces = "30,35,10,6,32,33,42,43";
string	sFrManFaces = "19,27,29,31,32,33,43,43";
string	sSpManFaces = "25,37,38,44,7,32,33,42,43";
string	sHoManFaces = "11,26,28,36,32,33,42,43";
string	sPoManFaces = "12,30,39,32,33,42,43";
string	sPiManFaces = "0,1,13,14,2,23,24,3,40,5";

void SetRandomFaceToCharacter(ref rCharacter)
{
	string sFaceID = "1";
	if (rCharacter.sex == "man")
	{
		switch (sti(rCharacter.nation))
		{
			case ENGLAND:	
				sFaceID = GetRandSubString(sEnManFaces);
			break;
			case FRANCE:	
				sFaceID = GetRandSubString(sFrManFaces);
			break;
			case SPAIN:		
				sFaceID = GetRandSubString(sSpManFaces);
			break;
			case PIRATE:	
				sFaceID = GetRandSubString(sPiManFaces);
			break;
			case HOLLAND:	
				sFaceID = GetRandSubString(sHoManFaces);
			break;
		}
	}
	else
	{
		sFaceID = "16";
	}
	
	rCharacter.FaceId = sti(sFaceID);
}

void FaceMaker(aref rCharacter)
{
	string sModel = rCharacter.model;
	
	// Warship 07.07.09 Пасхалка с кораблём "Мэри Селест" - за место лица кэпа - море с облаками
	if(rCharacter.ID == "MaryCelesteCapitan")
	{
		rCharacter.FaceId = 333;
		return;
	}
	
	// Блок ВРЕМЕННЫХ заглушек, пока не нарисуем -->
	if (HasSubStr("MarketMan,gipsy,keeper,vrach,trader", sModel))
	{
		int iTemp;
		switch(sModel)
		{
			case "trader"	:	iTemp = 3001;	break;
			case "MarketMan":	iTemp = 3001;	break;
			case "gipsy"	:	iTemp = 3002;	break;
			case "keeper"	:	iTemp = 3003;	break;
			case "vrach"	:	iTemp = 3005;	break;
		}
		rCharacter.FaceId = iTemp;
		return;
	}
	if (CheckAttribute(rCharacter, "PhantomType") && rCharacter.PhantomType == "hawker")
	{
		rCharacter.FaceId = 2001;
		return;
	}
	// <-- Блок ВРЕМЕННЫХ заглушек, пока не нарисуем
	
	switch (sModel)
	{
		case "beatrice":		rCharacter.FaceId = 0; break;
		case "beatriceA":		rCharacter.FaceId = 0; break;
		case "devlin":			rCharacter.FaceId = 0; break;
		//бармены - НУЖНЫ ИЗ COMMONERS
		case "barmen_0"		:		rCharacter.FaceId = 1; break;
		case "barmen_1"		:		rCharacter.FaceId = 2; break;
		case "barmen_2"		:		rCharacter.FaceId = 3; break;
		case "barmen_3"		:		rCharacter.FaceId = 4; break;
		case "barmen_4"		:		rCharacter.FaceId = 5; break;
		case "barmen_5"		:		rCharacter.FaceId = 6; break;
		case "barmen_6"		:		rCharacter.FaceId = 7; break;
		case "barmen_7"		:		rCharacter.FaceId = 8; break;
		case "barmen_8"		:		rCharacter.FaceId = 9; break;
		case "barmen_9"		:		rCharacter.FaceId = 10; break;
		case "barmen_10"	:		rCharacter.FaceId = 11; break;
		case "barmen_11"	:		rCharacter.FaceId = 12; break;
		case "barmen_12"	:		rCharacter.FaceId = 13; break;
		case "barmen_13"	:		rCharacter.FaceId = 14; break;
		case "barmen_14"	:		rCharacter.FaceId = 15; break;
		case "barmen_15"	:		rCharacter.FaceId = 16; break;
		case "barmen_16"	:		rCharacter.FaceId = 17; break;
		case "barmen_17"	:		rCharacter.FaceId = 18; break;
		case "barmen_18"	:		rCharacter.FaceId = 19; break;
		case "barmen_19"	:		rCharacter.FaceId = 20; break;
		case "barmen_20"	:		rCharacter.FaceId = 21; break;
		case "barmen_21"	:		rCharacter.FaceId = 22; break;
		case "barmen_22"	:		rCharacter.FaceId = 23; break;
		case "barmen_23"	:		rCharacter.FaceId = 24; break;
		case "barmen_24"	:		rCharacter.FaceId = 25; break;
		case "barmen_25"	:		rCharacter.FaceId = 26; break;
		case "barmen_26"	:		rCharacter.FaceId = 27; break;
		case "barmen_27"	:		rCharacter.FaceId = 28; break;
		case "barmen_33"	:		rCharacter.FaceId = 1033; break; //толстяк Жером временно тут
		
		// наемники-контрактники,  обычные капитаны - ГОТОВО
		case "officer_1"	: 		rCharacter.FaceId = 29;		break;
		case "officer_2"	: 		rCharacter.FaceId = 30;		break;
		case "officer_3"	: 		rCharacter.FaceId = 31;		break;
		case "officer_4"	: 		rCharacter.FaceId = 32;		break;
		case "officer_5"	: 		rCharacter.FaceId = 33;		break;
		case "officer_6"	: 		rCharacter.FaceId = 34;		break;
		case "officer_7"	: 		rCharacter.FaceId = 35;		break;
		case "officer_8"	: 		rCharacter.FaceId = 36;		break;
		case "officer_9"	: 		rCharacter.FaceId = 37;		break;
		case "officer_10"	: 		rCharacter.FaceId = 38;		break;
		case "officer_11"	: 		rCharacter.FaceId = 39;		break;
		case "officer_12"	: 		rCharacter.FaceId = 40;		break;
		case "officer_13"	: 		rCharacter.FaceId = 41;		break;
		case "officer_14"	: 		rCharacter.FaceId = 42;		break;
		case "officer_15"	: 		rCharacter.FaceId = 43;		break;
		// наемники-компаньоны,  пиратские капитаны - ГОТОВО
		case "officer_16"	: 		rCharacter.FaceId = 44;		break;
		case "officer_17"	: 		rCharacter.FaceId = 45;		break;
		case "officer_18"	: 		rCharacter.FaceId = 46;		break;
		case "officer_19"	: 		rCharacter.FaceId = 47;		break;
		case "officer_20"	: 		rCharacter.FaceId = 48;		break;
		case "officer_21"	: 		rCharacter.FaceId = 49;		break;
		case "officer_22"	: 		rCharacter.FaceId = 50;		break;
		case "officer_23"	: 		rCharacter.FaceId = 51;		break;
		case "officer_24"	: 		rCharacter.FaceId = 52;		break;
		case "officer_25"	: 		rCharacter.FaceId = 53;		break;
		case "officer_26"	: 		rCharacter.FaceId = 54;		break;
		case "officer_27"	: 		rCharacter.FaceId = 55;		break;
		case "officer_28"	: 		rCharacter.FaceId = 56;		break;
		//свободны 57 
		//58 - 60 это губернаторы
	
		// гражданское население
		// дворяне - ГОТОВО
		case "citiz_1"		:		rCharacter.FaceId = 61; 	break;
		case "citiz_2"		:		rCharacter.FaceId = 62; 	break;
		case "citiz_3"		:		rCharacter.FaceId = 63; 	break;
		case "citiz_4"		:		rCharacter.FaceId = 64; 	break;
		case "citiz_5"		:		rCharacter.FaceId = 65; 	break;
		case "citiz_6"		:		rCharacter.FaceId = 66; 	break;
		case "citiz_7"		:		rCharacter.FaceId = 67; 	break;
		case "citiz_8"		:		rCharacter.FaceId = 68; 	break;
		case "citiz_9"		:		rCharacter.FaceId = 69; 	break;
		case "citiz_10"		:		rCharacter.FaceId = 70; 	break;
		// бюргеры - ГОТОВО
		case "citiz_11"		:		rCharacter.FaceId = 71; 	break;
		case "citiz_12"		:		rCharacter.FaceId = 72; 	break;
		case "citiz_13"		:		rCharacter.FaceId = 73; 	break;
		case "citiz_14"		:		rCharacter.FaceId = 74; 	break;
		case "citiz_15"		:		rCharacter.FaceId = 75; 	break;
		case "citiz_16"		:		rCharacter.FaceId = 76; 	break;
		case "citiz_17"		:		rCharacter.FaceId = 77; 	break;
		case "citiz_18"		:		rCharacter.FaceId = 78; 	break;
		case "citiz_19"		:		rCharacter.FaceId = 79; 	break;
		case "citiz_20"		:		rCharacter.FaceId = 80; 	break;
		// контрабандисты - готово
		case "citiz_21"		:		rCharacter.FaceId = 81; 	break;
		case "mush_ctz_1"	:		rCharacter.FaceId = 81; 	break; //_21 с мушкетом
		case "citiz_22"		:		rCharacter.FaceId = 82; 	break;
		case "citiz_23"		:		rCharacter.FaceId = 83; 	break;
		case "mush_ctz_2"	:		rCharacter.FaceId = 83; 	break; //_23 с мушкетом
		case "citiz_24"		:		rCharacter.FaceId = 84; 	break;
		case "mush_ctz_3"	:		rCharacter.FaceId = 84; 	break; //_24 с мушкетом
		case "citiz_25"		:		rCharacter.FaceId = 85; 	break;
		case "citiz_26"		:		rCharacter.FaceId = 86; 	break;
		case "citiz_27"		:		rCharacter.FaceId = 87; 	break;
		case "citiz_28"		:		rCharacter.FaceId = 88; 	break;
		case "citiz_29"		:		rCharacter.FaceId = 89; 	break;
		case "citiz_30"		:		rCharacter.FaceId = 90; 	break;		
		// матросы - ГОТОВО
		case "citiz_31"		:		rCharacter.FaceId = 91; 	break;
		case "mush_ctz_4"	:		rCharacter.FaceId = 91; 	break; //_31 с мушкетом
		case "citiz_32"		:		rCharacter.FaceId = 92; 	break;
		case "mush_ctz_5"	:		rCharacter.FaceId = 92; 	break; //_32 с мушкетом
		case "citiz_33"		:		rCharacter.FaceId = 93; 	break;
		case "citiz_34"		:		rCharacter.FaceId = 94; 	break;
		case "citiz_35"		:		rCharacter.FaceId = 95; 	break;
		case "citiz_36"		:		rCharacter.FaceId = 96; 	break;
		case "citiz_37"		:		rCharacter.FaceId = 97; 	break;
		case "citiz_38"		:		rCharacter.FaceId = 98; 	break;
		case "mush_ctz_6"	:		rCharacter.FaceId = 98; 	break; //_38 с мушкетом
		case "citiz_39"		:		rCharacter.FaceId = 99; 	break;
		case "citiz_40"		:		rCharacter.FaceId = 100; 	break;
		//простолюдины - НУЖНЫ ИЗ COMMONERS
		case "citiz_41"		:		rCharacter.FaceId = 101; 	break; //из оригинала. подойдет исходник от ситиз25
		case "citiz_42"		:		rCharacter.FaceId = 102; 	break; //из оригинала. подойдет исходник от ситиз22 или офицера4
		case "citiz_43"		:		rCharacter.FaceId = 103; 	break; //подойдет исходник от офицера10
		case "citiz_44"		:		rCharacter.FaceId = 104; 	break;
		case "mush_ctz_9"	:		rCharacter.FaceId = 104; 	break; //_44 с мушкетом, пиратский мушкетёр (ККС стек)
		case "citiz_45"		:		rCharacter.FaceId = 105; 	break; //из оригинала подойдет исходник от ситиз47
		case "citiz_46"		:		rCharacter.FaceId = 106; 	break; //из оригинала подойдет исходник от ситиз47
		case "citiz_47"		:		rCharacter.FaceId = 107; 	break; //идеализировать другой фон простолюдина
		case "citiz_48"		:		rCharacter.FaceId = 108; 	break;
		case "citiz_49"		:		rCharacter.FaceId = 109; 	break;
		case "citiz_50"		:		rCharacter.FaceId = 110; 	break;
		// наемная охрана - ГОТОВО
		case "citiz_51"		:		rCharacter.FaceId = 111; 	break;
		case "citiz_52"		:		rCharacter.FaceId = 112; 	break;
		case "citiz_53"		:		rCharacter.FaceId = 113; 	break;
		case "mush_ctz_12"	:		rCharacter.FaceId = 113; 	break; //_53 с мушкетом
		case "citiz_54"		:		rCharacter.FaceId = 114; 	break;
		case "mush_ctz_11"	:		rCharacter.FaceId = 114; 	break; //_54 с мушкетом
		case "citiz_55"		:		rCharacter.FaceId = 115; 	break;
		case "citiz_56"		:		rCharacter.FaceId = 116; 	break;
		case "citiz_57"		:		rCharacter.FaceId = 117; 	break;
		case "citiz_58"		:		rCharacter.FaceId = 118; 	break;
		case "citiz_59"		:		rCharacter.FaceId = 119; 	break;
		case "citiz_60"		:		rCharacter.FaceId = 120; 	break;
		// пираты - НУЖНЫ СРЕДНЕ
		case "pirate_1"		:		rCharacter.FaceId = 121; 	break;
		case "pirate_2"		:		rCharacter.FaceId = 122; 	break;
		case "pirate_3"		:		rCharacter.FaceId = 123; 	break;
		case "pirate_4"		:		rCharacter.FaceId = 124; 	break;
		case "pirate_5"		:		rCharacter.FaceId = 125; 	break;
		case "pirate_6"		:		rCharacter.FaceId = 126; 	break;
		case "pirate_7"		:		rCharacter.FaceId = 127; 	break;
		case "mush_ctz_7"	:		rCharacter.FaceId = 127; 	break; //_7 с мушкетом
		case "pirate_8"		:		rCharacter.FaceId = 128; 	break;
		case "pirate_9"		:		rCharacter.FaceId = 129; 	break;
		case "pirate_10"	:		rCharacter.FaceId = 130; 	break;
		case "pirate_11"	:		rCharacter.FaceId = 131; 	break; //готово
		case "Mushketer_2"	:		rCharacter.FaceId = 131; 	break; //_11 с мушкетом
		case "pirate_12"	:		rCharacter.FaceId = 132; 	break; //готово
		case "Mushketer_5"	:		rCharacter.FaceId = 132; 	break; //_12 с мушкетом
		case "pirate_13"	:		rCharacter.FaceId = 133; 	break; //готово
		case "pirate_14"	:		rCharacter.FaceId = 134; 	break; //готово
		case "Mushketer_1"	:		rCharacter.FaceId = 134; 	break; //светлый _14 с мушкетом
		case "pirate_15"	:		rCharacter.FaceId = 135; 	break; //готово
		case "Mushketer_3"	:		rCharacter.FaceId = 135; 	break; //_15 с мушкетом
		case "pirate_16"	:		rCharacter.FaceId = 136; 	break; //готово
		//case "Mushketer_4":		rCharacter.FaceId = xxx; 	break; //пиратский мушкетёр (обычный стек)
		//case "mush_ctz_8"	:		rCharacter.FaceId = xxx; 	break; //пиратский мушкетёр (ККС стек)
		// рабочие невольники - готово		
		case "slave_1"		:		rCharacter.FaceId = 137; 	break;
		case "slave_2"		:		rCharacter.FaceId = 138; 	break;
		case "slave_3"		:		rCharacter.FaceId = 139; 	break;
		case "slave_4"		:		rCharacter.FaceId = 140; 	break;
		case "slave_5"		:		rCharacter.FaceId = 141; 	break;
		case "slave_6"		:		rCharacter.FaceId = 142; 	break;
		case "slave_7"		:		rCharacter.FaceId = 143; 	break;
		case "slave_8"		:		rCharacter.FaceId = 144; 	break;
		case "slave_9"		:		rCharacter.FaceId = 145; 	break;
		// пожилые женщины (простые) - НУЖНЫ СРЕДНЕ
		case "oldwoman_1"	:		rCharacter.FaceId = 146; 	break;
		case "oldwoman_2"	:		rCharacter.FaceId = 147; 	break;
		// пожилые женщины (зажиточные) - ПОКА НЕ НУЖНЫ
		case "oldwoman_3"	:		rCharacter.FaceId = 148; 	break; //портрета нет
		case "oldwoman_4"	:		rCharacter.FaceId = 149; 	break; //портрет есть в ккс (жена левассера), но нелучшего качества
		// дворянки - ГОТОВО
		case "lady_1"		:		rCharacter.FaceId = 150; 	break;
		case "lady_2"		:		rCharacter.FaceId = 151; 	break;
		case "lady_3"		:		rCharacter.FaceId = 152; 	break;
		case "lady_4"		:		rCharacter.FaceId = 153; 	break;
		case "lady_5"		:		rCharacter.FaceId = 154; 	break;
		case "lady_6"		:		rCharacter.FaceId = 155; 	break;
		case "lady_7"		:		rCharacter.FaceId = 156; 	break;
		// горожанки - ГОТОВО
		case "women_1"		:		rCharacter.FaceId = 157; 	break;
		case "women_2"		:		rCharacter.FaceId = 158; 	break;
		case "women_3"		:		rCharacter.FaceId = 159; 	break;
		case "women_4"		:		rCharacter.FaceId = 160; 	break;
		case "women_5"		:		rCharacter.FaceId = 161; 	break;
		case "women_6"		:		rCharacter.FaceId = 162; 	break;
		case "women_7"		:		rCharacter.FaceId = 163; 	break;
		case "women_8"		:		rCharacter.FaceId = 164; 	break;
		case "women_9"		:		rCharacter.FaceId = 165; 	break;
		case "women_10"		:		rCharacter.FaceId = 166; 	break;
		case "women_11"		:		rCharacter.FaceId = 167; 	break;
		case "women_12"		:		rCharacter.FaceId = 168; 	break;
		// проститутки - ГОТОВО
		case "horse01"		: 		rCharacter.FaceId = 169; 	break;
		case "horse02"		: 		rCharacter.FaceId = 170; 	break;
		case "horse03"		: 		rCharacter.FaceId = 171; 	break;
		case "horse04"		: 		rCharacter.FaceId = 172; 	break;
		case "horse05"		: 		rCharacter.FaceId = 173; 	break;
		case "horse06"		: 		rCharacter.FaceId = 174; 	break;
		case "horse07"		: 		rCharacter.FaceId = 175; 	break;
		case "horse08"		: 		rCharacter.FaceId = 176; 	break;
		// молодые девушки - ГОТОВО
		case "girl_1"		: 		rCharacter.FaceId = 177; 	break;
		case "girl_2"		: 		rCharacter.FaceId = 178; 	break;
		case "girl_3"		: 		rCharacter.FaceId = 179; 	break;
		case "girl_4"		: 		rCharacter.FaceId = 180; 	break;
		case "girl_5"		: 		rCharacter.FaceId = 181; 	break;
		case "girl_6"		: 		rCharacter.FaceId = 182; 	break;
		case "girl_7"		: 		rCharacter.FaceId = 183; 	break;
		case "girl_8"		: 		rCharacter.FaceId = 184; 	break;
		case "girl_9"		: 		rCharacter.FaceId = 185; 	break;
		case "girl_10"		: 		rCharacter.FaceId = 186; 	break;
		// цыганки - НЕ НУЖНЫ
		case "gipsy_1"		: 		rCharacter.FaceId = 187; 	break;
		case "gipsy_2"		: 		rCharacter.FaceId = 188; 	break;
		case "gipsy_3"		: 		rCharacter.FaceId = 189; 	break;
		case "gipsy_4"		:		rCharacter.FaceId = 190; 	break;
		case "gipsy_5"		:		rCharacter.FaceId = 191; 	break;
		case "gipsy_6"		:		rCharacter.FaceId = 192; 	break;
		case "gipsy_7"		:		rCharacter.FaceId = 193; 	break;		
		// монахи - ГОТОВО
		case "monk_1"		:		rCharacter.FaceId = 194; 	break;
		case "monk_2"		:		rCharacter.FaceId = 195; 	break;
		case "monk_3"		:		rCharacter.FaceId = 196; 	break;
		case "monk_4"		:		rCharacter.FaceId = 197; 	break;
		case "monk_5"		:		rCharacter.FaceId = 198; 	break;
		case "monk_6"		:		rCharacter.FaceId = 199; 	break;
		// торговцы - ПОКА НЕ НУЖНЫ
		/*case "trader_1"		:		rCharacter.FaceId = 200; 	break;
		case "trader_2"		:		rCharacter.FaceId = 201; 	break;
		case "trader_3"		:		rCharacter.FaceId = 202; 	break;
		case "trader_4"		:		rCharacter.FaceId = 203; 	break;
		case "trader_5"		:		rCharacter.FaceId = 204; 	break;
		case "trader_6"		:		rCharacter.FaceId = 205; 	break;
		case "trader_7"		:		rCharacter.FaceId = 206; 	break;
		case "trader_8"		:		rCharacter.FaceId = 207; 	break;
		case "trader_9"		:		rCharacter.FaceId = 208; 	break;
		case "trader_10"	:		rCharacter.FaceId = 209; 	break;
		case "trader_11"	:		rCharacter.FaceId = 210; 	break;
		case "trader_12"	:		rCharacter.FaceId = 211; 	break;
		case "trader_13"	:		rCharacter.FaceId = 212; 	break;
		case "trader_14"	:		rCharacter.FaceId = 213; 	break;
		case "trader_15"	:		rCharacter.FaceId = 214; 	break;
		// ростовщики из ККС - ПОКА НЕ НУЖНЫ
		case "usurer_1"		:		rCharacter.FaceId = 215; 	break;
		case "usurer_2"		:		rCharacter.FaceId = 216; 	break;
		case "usurer_3"		:		rCharacter.FaceId = 217; 	break;
		case "usurer_4"		:		rCharacter.FaceId = 218; 	break;
		case "usurer_5"		:		rCharacter.FaceId = 219; 	break;
		case "usurer_6"		:		rCharacter.FaceId = 220; 	break;
		case "usurer_7"		:		rCharacter.FaceId = 221; 	break;
		case "usurer_8"		:		rCharacter.FaceId = 222; 	break;
		case "usurer_9"		:		rCharacter.FaceId = 223; 	break;
		case "usurer_10"	:		rCharacter.FaceId = 224; 	break;
		case "usurer_11"	:		rCharacter.FaceId = 225; 	break;
		case "usurer_12"	:		rCharacter.FaceId = 226; 	break;
		case "usurer_13"	:		rCharacter.FaceId = 227; 	break;
		case "usurer_14"	:		rCharacter.FaceId = 228; 	break;
		case "usurer_15"	:		rCharacter.FaceId = 229; 	break;
		//корабелы - НЕ НУЖНЫ
		case "shipowner_1"	:		rCharacter.FaceId = 230; 	break;
		case "shipowner_2"	:		rCharacter.FaceId = 231; 	break;
		case "shipowner_3"	:		rCharacter.FaceId = 232; 	break; //Бернард Венсан
		case "shipowner_4"	:		rCharacter.FaceId = 233; 	break;
		case "shipowner_5"	:		rCharacter.FaceId = 234; 	break;
		case "shipowner_6"	:		rCharacter.FaceId = 235; 	break;
		case "shipowner_7"	:		rCharacter.FaceId = 236; 	break;
		case "shipowner_8"	:		rCharacter.FaceId = 237; 	break;
		case "shipowner_9"	:		rCharacter.FaceId = 238; 	break;
		case "shipowner_10"	:		rCharacter.FaceId = 239; 	break;
		case "shipowner_11"	:		rCharacter.FaceId = 240; 	break;
		case "shipowner_12"	:		rCharacter.FaceId = 241; 	break;
		case "shipowner_13"	:		rCharacter.FaceId = 242; 	break;
		case "shipowner_14"	:		rCharacter.FaceId = 243; 	break;
		case "shipowner_15"	:		rCharacter.FaceId = 244; 	break;
		case "shipowner_16"	:		rCharacter.FaceId = 245; 	break;
		case "shipowner_17"	:		rCharacter.FaceId = 246; 	break; //мэриман
		// начальники порта - НЕ НУЖНЫ
		case "portman_1"	:		rCharacter.FaceId = 247; 	break;
		case "portman_2"	:		rCharacter.FaceId = 248; 	break;
		case "portman_3"	:		rCharacter.FaceId = 249; 	break;
		case "portman_4"	:		rCharacter.FaceId = 250; 	break;
		case "portman_5"	:		rCharacter.FaceId = 251; 	break;
		case "portman_6"	:		rCharacter.FaceId = 252; 	break;
		case "portman_7"	:		rCharacter.FaceId = 253; 	break;
		case "portman_8"	:		rCharacter.FaceId = 254; 	break;
		case "portman_9"	:		rCharacter.FaceId = 255; 	break;
		case "portman_10"	:		rCharacter.FaceId = 256; 	break;
		case "portman_11"	:		rCharacter.FaceId = 257; 	break;
		case "portman_12"	:		rCharacter.FaceId = 258; 	break;
		case "portman_13"	:		rCharacter.FaceId = 259; 	break;
		case "portman_14"	:		rCharacter.FaceId = 260; 	break;
		case "portman_15"	:		rCharacter.FaceId = 261; 	break;
		//священники - НЕ НУЖНЫ
		case "priest_1"		:		rCharacter.FaceId = 262; 	break;
		case "priest_2"		:		rCharacter.FaceId = 263; 	break;
		case "priest_3"		:		rCharacter.FaceId = 264; 	break;
		case "priest_4"		:		rCharacter.FaceId = 265; 	break;
		case "priest_5"		:		rCharacter.FaceId = 266; 	break;
		case "priest_6"		:		rCharacter.FaceId = 267; 	break;
		case "priest_7"		:		rCharacter.FaceId = 268; 	break;
		case "priest_8"		:		rCharacter.FaceId = 269; 	break;
		case "priest_9"		:		rCharacter.FaceId = 270; 	break;
		case "priest_10"	:		rCharacter.FaceId = 271; 	break;
		case "priest_11"	:		rCharacter.FaceId = 272; 	break;
		case "priest_12"	:		rCharacter.FaceId = 273; 	break;
		//бордельмаман - НЕ НУЖНЫ
		case "maman_1"		:		rCharacter.FaceId = 274; 	break;
		case "maman_2"		:		rCharacter.FaceId = 275; 	break;
		case "maman_3"		:		rCharacter.FaceId = 276; 	break;
		case "maman_4"		:		rCharacter.FaceId = 277; 	break;
		case "maman_5"		:		rCharacter.FaceId = 278; 	break;
		case "maman_6"		:		rCharacter.FaceId = 279; 	break;
		case "maman_7"		:		rCharacter.FaceId = 280; 	break;
		case "maman_8"		:		rCharacter.FaceId = 281; 	break;
		//губернаторы - ПОКА НЕ НУЖНЫ (часть есть в ККС)
		case "huber_1"		:		rCharacter.FaceId = 282; 	break;
		case "huber_2"		:		rCharacter.FaceId = 283; 	break;
		case "huber_3"		:		rCharacter.FaceId = 284; 	break;
		case "huber_4"		:		rCharacter.FaceId = 285; 	break;
		case "huber_5"		:		rCharacter.FaceId = 286; 	break;
		case "huber_6"		:		rCharacter.FaceId = 287; 	break;
		case "huber_7"		:		rCharacter.FaceId = 288; 	break;
		case "huber_8"		:		rCharacter.FaceId = 289; 	break;
		case "huber_9"		:		rCharacter.FaceId = 290; 	break;
		case "huber_10"		:		rCharacter.FaceId = 291; 	break;
		case "huber_11"		:		rCharacter.FaceId = 292; 	break;
		case "huber_12"		:		rCharacter.FaceId = 293; 	break;
		case "huber_13"		:		rCharacter.FaceId = 294; 	break;
		case "huber_14"		:		rCharacter.FaceId = 295; 	break;
		case "huber_15"		:		rCharacter.FaceId = 296; 	break;
		case "huber_16"		:		rCharacter.FaceId = 297; 	break;
		case "huber_17"		:		rCharacter.FaceId = 298; 	break;
		case "huber_18"		:		rCharacter.FaceId = 299; 	break;
		case "huber_19"		:		rCharacter.FaceId = 300; 	break;
		case "huber_20"		:		rCharacter.FaceId = 301; 	break;
		case "huber_21"		:		rCharacter.FaceId = 302; 	break;
		case "huber_22"		:		rCharacter.FaceId = 303; 	break;
		case "huber_23"		:		rCharacter.FaceId = 304; 	break;
		case "huber_24"		:		rCharacter.FaceId = 305; 	break;
		case "huber_25"		:		rCharacter.FaceId = 306; 	break;
		case "huber_26"		:		rCharacter.FaceId = 307; 	break;
		case "huber_27"		:		rCharacter.FaceId = 308; 	break;*/
		//затычка на будущее
		/*
		case "huber_28"		:		rCharacter.FaceId = 309; 	break;
		case "huber_29"		:		rCharacter.FaceId = 310; 	break;
		case "huber_30"		:		rCharacter.FaceId = 311; 	break;
		case "huber_31"		:		rCharacter.FaceId = 312; 	break;		
		case "huber_32"		:		rCharacter.FaceId = 313; 	break;		
		case "huber_33"		:		rCharacter.FaceId = 314; 	break;		
		case "huber_34"		:		rCharacter.FaceId = 315; 	break;		
		case "huber_35"		:		rCharacter.FaceId = 316; 	break;*/
		// заключенные
		case "prison_1"		:		rCharacter.FaceId = 317; 	break;
		case "prison_2"		:		rCharacter.FaceId = 318; 	break;		
		case "prison_3"		:		rCharacter.FaceId = 319; 	break;		
		case "prison_4"		:		rCharacter.FaceId = 320; 	break;		
		case "prison_5"		:		rCharacter.FaceId = 321; 	break;
		case "prison_6"		:		rCharacter.FaceId = 322; 	break;
		//лоточники на рынке - пока не имеется моделей - можно взять за исходник жителей из ККС - не приоритет 
		/*
		case "MarketMan_1"	:		rCharacter.FaceId = 326; 	break;
		case "MarketMan_2"	:		rCharacter.FaceId = 327; 	break;
		case "MarketMan_3"	:		rCharacter.FaceId = 328; 	break;
		case "MarketMan_4"	:		rCharacter.FaceId = 329; 	break;
		case "MarketMan_5"	:		rCharacter.FaceId = 330; 	break;*/
		//дипломаты - ПОКА НЕ НУЖНЫ
		/*case "diplom_1"	:		rCharacter.FaceId = 331; 	break;
		case "diplom_2"		:		rCharacter.FaceId = 332; 	break;
		case "diplom_3"		:		rCharacter.FaceId = 333; 	break;
		case "diplom_4"		:		rCharacter.FaceId = 334; 	break;
		case "diplom_5"		:		rCharacter.FaceId = 335; 	break;
		case "diplom_6"		:		rCharacter.FaceId = 336; 	break;
		case "diplom_7"		:		rCharacter.FaceId = 337; 	break;
		case "diplom_8"		:		rCharacter.FaceId = 338; 	break;
		case "diplom_9"		:		rCharacter.FaceId = 339; 	break;*/
		// купцы из ККС - ГОТОВО
		case "merch_1"		:		rCharacter.FaceId = 340; 	break;
		case "merch_2"		:		rCharacter.FaceId = 341; 	break;
		case "merch_3"		:		rCharacter.FaceId = 342; 	break;
		case "merch_4"		:		rCharacter.FaceId = 343; 	break;
		case "merch_5"		:		rCharacter.FaceId = 344; 	break;
		case "merch_6"		:		rCharacter.FaceId = 345; 	break;
		case "merch_7"		:		rCharacter.FaceId = 346; 	break;
		case "merch_8"		:		rCharacter.FaceId = 347; 	break;
		case "merch_9"		:		rCharacter.FaceId = 348; 	break;
		case "merch_10"		:		rCharacter.FaceId = 349; 	break;
		case "merch_11"		:		rCharacter.FaceId = 350; 	break;
		case "merch_12"		:		rCharacter.FaceId = 351; 	break;
		case "merch_13"		:		rCharacter.FaceId = 352; 	break;
		case "merch_14"		:		rCharacter.FaceId = 353; 	break;
		case "merch_15"		:		rCharacter.FaceId = 354; 	break;
		/*//затычка на будущее 
		//жены губернаторов
		case "hwife_1"		:		rCharacter.FaceId = 355; 	break;
		case "hwife_2"		:		rCharacter.FaceId = 356; 	break;
		case "hwife_3"		:		rCharacter.FaceId = 357; 	break;
		case "hwife_4"		:		rCharacter.FaceId = 358; 	break;
		case "hwife_5"		:		rCharacter.FaceId = 359; 	break;
		case "hwife_6"		:		rCharacter.FaceId = 360; 	break;
		case "hwife_7"		:		rCharacter.FaceId = 361; 	break;
		case "hwife_8"		:		rCharacter.FaceId = 362; 	break;
		case "hwife_9"		:		rCharacter.FaceId = 363; 	break;
		case "hwife_10"		:		rCharacter.FaceId = 364; 	break;
		case "hwife_11"		:		rCharacter.FaceId = 365; 	break;
		case "hwife_12"		:		rCharacter.FaceId = 366; 	break;
		case "hwife_13"		:		rCharacter.FaceId = 367; 	break;
		case "hwife_14"		:		rCharacter.FaceId = 368; 	break;
		case "hwife_15"		:		rCharacter.FaceId = 369; 	break;
		case "hwife_16"		:		rCharacter.FaceId = 370; 	break;
		case "hwife_17"		:		rCharacter.FaceId = 371; 	break;
		case "hwife_18"		:		rCharacter.FaceId = 372; 	break;
		case "hwife_19"		:		rCharacter.FaceId = 373; 	break;
		case "hwife_20"		:		rCharacter.FaceId = 374; 	break;
		case "hwife_21"		:		rCharacter.FaceId = 375; 	break;
		case "hwife_22"		:		rCharacter.FaceId = 376; 	break;
		case "hwife_23"		:		rCharacter.FaceId = 377; 	break;
		case "hwife_24"		:		rCharacter.FaceId = 378; 	break;
		case "hwife_25"		:		rCharacter.FaceId = 379; 	break;
		case "hwife_26"		:		rCharacter.FaceId = 380; 	break;
		case "hwife_27"		:		rCharacter.FaceId = 381; 	break;
		case "hwife_28"		:		rCharacter.FaceId = 382; 	break;
		case "hwife_29"		:		rCharacter.FaceId = 383; 	break;
		case "hwife_30"		:		rCharacter.FaceId = 384; 	break;
		case "hwife_31"		:		rCharacter.FaceId = 385; 	break;
		case "hwife_32"		:		rCharacter.FaceId = 386; 	break;
		case "hwife_33"		:		rCharacter.FaceId = 387; 	break;
		case "hwife_34"		:		rCharacter.FaceId = 388; 	break;
		case "hwife_35"		:		rCharacter.FaceId = 389; 	break;*/
		
		/*//затычка на будущее врачи - таких персонажей нет - на будущее
		case "doctor_1"		:		rCharacter.FaceId = 390; 	break;
		case "doctor_2"		:		rCharacter.FaceId = 391; 	break;
		case "doctor_3"		:		rCharacter.FaceId = 392; 	break;
		case "doctor_4"		:		rCharacter.FaceId = 393; 	break;
		case "doctor_5"		:		rCharacter.FaceId = 394; 	break;
		case "doctor_6"		:		rCharacter.FaceId = 395; 	break;
		case "doctor_7"		:		rCharacter.FaceId = 396; 	break;
		case "doctor_8"		:		rCharacter.FaceId = 397; 	break;
		case "doctor_9"		:		rCharacter.FaceId = 398; 	break;
		case "doctor_10"	:		rCharacter.FaceId = 399; 	break;
		case "doctor_11"	:		rCharacter.FaceId = 400; 	break;
		case "doctor_12"	:		rCharacter.FaceId = 401; 	break;
		case "doctor_13"	:		rCharacter.FaceId = 402; 	break;
		case "doctor_14"	:		rCharacter.FaceId = 403; 	break;
		case "doctor_15"	:		rCharacter.FaceId = 404; 	break;*/
		
		/*//затычка на будущее кузнецы - таких персонажей нет - на будущее
		case "blacksmith_1"	:		rCharacter.FaceId = 405; 	break;
		case "blacksmith_2"	:		rCharacter.FaceId = 406; 	break;
		case "blacksmith_3"	:		rCharacter.FaceId = 407; 	break;
		case "blacksmith_4"	:		rCharacter.FaceId = 408; 	break;
		case "blacksmith_5"	:		rCharacter.FaceId = 409; 	break;
		case "blacksmith_6"	:		rCharacter.FaceId = 410; 	break;
		case "blacksmith_7"	:		rCharacter.FaceId = 411; 	break;
		case "blacksmith_8"	:		rCharacter.FaceId = 412; 	break;
		case "blacksmith_9"	:		rCharacter.FaceId = 413; 	break;
		case "blacksmith_10":		rCharacter.FaceId = 414; 	break;
		case "blacksmith_11":		rCharacter.FaceId = 415; 	break;
		case "blacksmith_12":		rCharacter.FaceId = 416; 	break;
		case "blacksmith_13":		rCharacter.FaceId = 417; 	break;
		case "blacksmith_14":		rCharacter.FaceId = 418; 	break;
		case "blacksmith_15":		rCharacter.FaceId = 419; 	break;*/
		
		//молодые мужчинки
		case "Youngman"			:		rCharacter.FaceId = 420; 	break;
		
		// французские офицеры (море) - ГОТОВО
		case "navy_off_fra_1"	:		rCharacter.FaceId = 505; 	break;
		case "navy_off_fra_2"	:		rCharacter.FaceId = 506; 	break;
		case "navy_off_fra_3"	:		rCharacter.FaceId = 507; 	break;
		case "navy_off_fra_4"	:		rCharacter.FaceId = 508; 	break;
		case "navy_off_fra_5"	:		rCharacter.FaceId = 509; 	break;
		case "navy_off_fra_6"	:		rCharacter.FaceId = 510; 	break;
		// английские офицеры (море) - ГОТОВО
		case "navy_off_eng_1"	:		rCharacter.FaceId = 511; 	break;
		case "navy_off_eng_2"	:		rCharacter.FaceId = 512; 	break;
		case "navy_off_eng_3"	:		rCharacter.FaceId = 513; 	break;
		case "navy_off_eng_4"	:		rCharacter.FaceId = 514; 	break;
		case "navy_off_eng_5"	:		rCharacter.FaceId = 515; 	break;
		case "navy_off_eng_6"	:		rCharacter.FaceId = 516; 	break;
		// голландские офицеры (море) - ГОТОВО
		case "navy_off_hol_1"	:		rCharacter.FaceId = 517; 	break;	//готово
		case "navy_off_hol_2"	:		rCharacter.FaceId = 518; 	break;
		case "navy_off_hol_3"	:		rCharacter.FaceId = 519; 	break;
		case "navy_off_hol_4"	:		rCharacter.FaceId = 520; 	break;
		case "navy_off_hol_5"	:		rCharacter.FaceId = 521; 	break;	//готово
		case "navy_off_hol_6"	:		rCharacter.FaceId = 522; 	break;	//готово
		// испанские офицеры (море) - ГОТОВО
		case "navy_off_spa_1"	:		rCharacter.FaceId = 523; 	break;	//готово
		case "navy_off_spa_2"	:		rCharacter.FaceId = 524; 	break;	//готово
		case "navy_off_spa_3"	:		rCharacter.FaceId = 525; 	break;	//готово
		case "navy_off_spa_4"	:		rCharacter.FaceId = 526; 	break;	//готово
		case "navy_off_spa_5"	:		rCharacter.FaceId = 527; 	break;	//готово
		case "navy_off_spa_6"	:		rCharacter.FaceId = 528; 	break;	//готово
		
		//ПОЛОЖНЯК:
		//1-2 командуют ополчением, 3-4 командуют в городах 
		//5-6 командуют солдатами, 7-11 коменданты
		// французские офицеры - НУЖНЫ
		case "off_fra_1"		:		rCharacter.FaceId = 530; 	break;
		case "off_fra_2"		:		rCharacter.FaceId = 531; 	break;
		case "off_fra_3"		:		rCharacter.FaceId = 532; 	break;
		case "off_fra_4"		:		rCharacter.FaceId = 533; 	break;
		case "off_fra_5"		:		rCharacter.FaceId = 534; 	break;
		case "off_fra_6"		:		rCharacter.FaceId = 535; 	break;
		case "off_fra_7"		:		rCharacter.FaceId = 3004; 	break; //536
		case "off_fra_8"		:		rCharacter.FaceId = 3004; 	break; //537
		case "off_fra_9"		:		rCharacter.FaceId = 3004; 	break; //538
		case "off_fra_10"		:		rCharacter.FaceId = 3004; 	break; //539
		case "off_fra_11"		:		rCharacter.FaceId = 3004; 	break; //540
		// английские офицеры - НУЖНЫ
		case "off_eng_1"		:		rCharacter.FaceId = 541; 	break;
		case "off_eng_2"		:		rCharacter.FaceId = 542; 	break;
		case "off_eng_3"		:		rCharacter.FaceId = 543; 	break;
		case "off_eng_4"		:		rCharacter.FaceId = 544; 	break;
		case "off_eng_5"		:		rCharacter.FaceId = 545; 	break; //портрета нет
		case "off_eng_6"		:		rCharacter.FaceId = 546; 	break; //портрета нет
		case "off_eng_7"		:		rCharacter.FaceId = 3004; 	break; //547 портрета нет
		case "off_eng_8"		:		rCharacter.FaceId = 3004; 	break; //548 портрета нет
		case "off_eng_9"		:		rCharacter.FaceId = 3004; 	break; //549 портрета нет
		case "off_eng_10"		:		rCharacter.FaceId = 3004; 	break; //550 портрета нет
		case "off_eng_11"		:		rCharacter.FaceId = 3004; 	break; //551 портрета нет
		// голландские офицеры - НУЖНЫ
		case "off_hol_1"		:		rCharacter.FaceId = 552; 	break; //портрета нет
		case "off_hol_2"		:		rCharacter.FaceId = 553; 	break; //портрета нет
		case "off_hol_3"		:		rCharacter.FaceId = 554; 	break;
		case "off_hol_4"		:		rCharacter.FaceId =	555; 	break;
		case "off_hol_5"		:		rCharacter.FaceId = 556; 	break; //портрета нет
		case "off_hol_6"		:		rCharacter.FaceId = 557; 	break; //портрета нет
		case "off_hol_7"		:		rCharacter.FaceId = 3004; 	break; //558 портрета нет
		case "off_hol_8"		:		rCharacter.FaceId = 3004; 	break; //559 портрета нет
		case "off_hol_9"		:		rCharacter.FaceId = 3004; 	break; //560 портрета нет
		case "off_hol_10"		:		rCharacter.FaceId = 3004; 	break; //561 портрета нет
		case "off_hol_11"		:		rCharacter.FaceId = 3004; 	break; //562 портрета нет
		// испанские офицеры - НУЖНЫ (есть из ккс)
		case "off_spa_1"		:		rCharacter.FaceId = 563; 	break; //портрета нет
		case "off_spa_2"		:		rCharacter.FaceId = 564; 	break;
		case "off_spa_3"		:		rCharacter.FaceId = 565; 	break;
		case "off_spa_4"		:		rCharacter.FaceId = 566; 	break;
		case "off_spa_5"		:		rCharacter.FaceId = 567; 	break;
		case "off_spa_6"		:		rCharacter.FaceId = 568; 	break;
		case "off_spa_7"		:		rCharacter.FaceId = 3004; 	break; //569
		case "off_spa_8"		:		rCharacter.FaceId = 3004; 	break; //570
		case "off_spa_9"		:		rCharacter.FaceId = 3004; 	break; //571
		case "off_spa_10"		:		rCharacter.FaceId = 3004; 	break; //572
		case "off_spa_11"		:		rCharacter.FaceId = 3004; 	break; //573

		case "huber_eng"		:		rCharacter.FaceId = 59; 	break;
		case "huber_fra"		:		rCharacter.FaceId = 60; 	break;
		case "huber_spa"		:		rCharacter.FaceId = 61; 	break;
		case "huber_hol"		:		rCharacter.FaceId = 62; 	break;
		
		// КВЕСТОВЫЕ \\
		
		//пролог
		case "Sandro_Thorne"	:		rCharacter.FaceId = 2001; 	break; //Сандро Торн
		case "Sandro_Thorne_6"	:		rCharacter.FaceId = 2001;	break; //Сандро в обносках
		//case "Hopkins"		:		rCharacter.FaceId = 2002; 	break; //Хопкинс
		
		// квестовые офицеры
		// линейка Блада
		case "Blood5"			:		rCharacter.FaceId = 1001; 	break; // кандидат к удалению
		case "blood_bomj"		:		rCharacter.FaceId = 1001; 	break; // кандидат к удалению
		case "Pitt"				:		rCharacter.FaceId = 2003; 	break; // Джереми Питт
		case "Pitt_6"			:		rCharacter.FaceId = 2003; 	break; // Джереми Питт (плантация)
		case "Ogl"				:		rCharacter.FaceId = 2004; 	break; // Нед Огл
		case "Ogl_6"			:		rCharacter.FaceId = 2004; 	break; // Нед Огл (плантация)
		case "Hugtorp"			:		rCharacter.FaceId = 2005;	break; // Натаниэль Хагторп
		case "Hugtorp_6"		:		rCharacter.FaceId = 2005; 	break; // Натаниэль Хагторп (плантация)
		case "Volverston"		:		rCharacter.FaceId = 2006; 	break; // Недвард Волверстон
		case "Volverston_6"		:		rCharacter.FaceId = 2006; 	break; // Недвард Волверстон (плантация)
		case "Dieke"			:		rCharacter.FaceId = 2007; 	break; // Николас Дайк
		case "Dieke_6"			:		rCharacter.FaceId = 2007; 	break; // Николас Дайк (плантация)
		// Проклятый идол
		case "James_Callow"		:		rCharacter.FaceId = 2008; 	break; // Джеймс Кэллоу
		// Непутевый казначей
		case "Fickler"			:		rCharacter.FaceId = 2009; 	break; // Андреас Фиклер	
		// Кондотьер
		case "Jafar_Preston"	:		rCharacter.FaceId = 2010; 	break; // Джа Престон
		// Флейт Орион
		case "Blacker_jail"		:		rCharacter.FaceId = 2011; 	break; // Мартин-зек
		case "Blacker_Martin"	:		rCharacter.FaceId = 2011; 	break; // Мартин Блэкер
		// Двуствольный мушкет
		case "Humphrey_Douglas"	:		rCharacter.FaceId = 2012; 	break; // Хэмфри Дуглас
		// Спасение краснокожего
		case "Tichingitu"		:  		rCharacter.FaceId = 2013; 	break; // Тиничгиту
		// Зачарованный город
		case "Danielle_Sheppard":		rCharacter.FaceId = 2014; 	break; // Даниэль Шеппард
		case "Danielle_Sheppard_D":		rCharacter.FaceId = 2014; 	break; // Даниэль Шеппард проклятая
		// Остров Справедливости
		case "Workman"			:		rCharacter.FaceId = 2015; 	break; // Джон Уоркман
		
		// уникальные офицеры
		case "Angellica"		:		rCharacter.FaceId = 2016; 	break; // Анжелика Шарп
		case "YokoDias"			:		rCharacter.FaceId = 2017; 	break; // Йоко Диаз
		case "Magnus"			:		rCharacter.FaceId = 2018; 	break; // Магнус фон Коккай - Штаде
		case "Rimalier"			:		rCharacter.FaceId = 2019;	break; // Николя Рималье

		// Главный Квест ГПК
		case "Oliver_Trusts"	:		rCharacter.FaceId = 2020;	break; // Оливер Траст (не обязательно)
		case "CitizenWom_1"		:		rCharacter.FaceId = 2021; 	break; // Армо Дюлин
		case "Malcolm_Fawn"		:		rCharacter.FaceId = 2022; 	break; // Малькольм Фаун
		case "Chad_Capper"		:		rCharacter.FaceId = 2023; 	break; // Чад Каппер (не обязательно)
		case "Eddy_Black"		:		rCharacter.FaceId = 2024; 	break; // Черный Эдди
		case "Thomas_Boyle"		:		rCharacter.FaceId = 2025;	break; // Томас Бойл (можно сделать)
		case "Tither"			:		rCharacter.FaceId = 2026;	break; // Тизер Бомж
		case "Tither_Monk"		:		rCharacter.FaceId = 2026;	break; // Тизер Монах
		
		// пиратские главари
		case "Morgan"			:		rCharacter.FaceId = 2057; 	break; // Генри Морган
		case "Richard_Sawkins"	:		rCharacter.FaceId = 2058;  	break; // Ричард Соукинс
		case "Jacob_Fackman"	:		rCharacter.FaceId = 2059;	break; // Джейкоб Факмен aka Джекмен
		case "Bart_Rogers"		:		rCharacter.FaceId = 2060; 	break; // Бартоломью Роджерс aka Черный Барт
		case "Edward_Colier"	:		rCharacter.FaceId = 2061; 	break; // Эдвард Кольер
		case "Mansfield"		:		rCharacter.FaceId = 2062; 	break; // Эдвард Мэнсфилд
		case "John_Morris"		:		rCharacter.FaceId = 2063; 	break; // Джон Моррис
		case "John_Coxon"		:		rCharacter.FaceId = 2064; 	break; // Джон Коксон

		// пиратские капитаны
		case "MorrisWillams"	:		rCharacter.FaceId = 2065; 	break; // Моррис Уильямс
		case "Bartholomew_Sharp":		rCharacter.FaceId = 2066; 	break; // Бартоломью Шарп
		case "EdwardLow"		:		rCharacter.FaceId = 2067; 	break; // Эдвард Лоу
		case "Goodley"			:		rCharacter.FaceId = 2068; 	break; // капитан Гудли
		case "RockBrasilian"	:		rCharacter.FaceId = 2069; 	break; // Рок Бразилец
		
		// Кондотьер	
		case "Snakeman_Yang"	:		rCharacter.FaceId = 2080; 	break; // Снейкман Янг (можно сделать)
		case "ozg_carlos"		:		rCharacter.FaceId = 2081; 	break; // Карлос Кассир
		case "ozg_horn"			:		rCharacter.FaceId = 2082; 	break; // Ганнибал Холм
		case "ozg_piRat"		:		rCharacter.FaceId = 2083; 	break; // Матиас Грин-Крыса
		case "ozg_miko"			:		rCharacter.FaceId = 2084; 	break; // Мико Пистольеро
		case "ozg_martin"		:		rCharacter.FaceId = 2085; 	break; // Мартин ван Хален
		
		// умельцы
		case "Henry_Mechanic"	:		rCharacter.FaceId = 2086; 	break; // Механик (можно сделать)
		case "Alexus_Reseacher"	:		rCharacter.FaceId = 2087; 	break; // Алексус (можно сделать)
		
		// Остинцы
		case "Ostins_1"			:		rCharacter.FaceId = 2091; 	break;
		case "Ostins_2"			:		rCharacter.FaceId = 2092; 	break;
		case "Ostins_3"			:		rCharacter.FaceId = 2093; 	break;
		case "Ostins_4"			:		rCharacter.FaceId = 2094; 	break;
		case "Ostins_5"			:		rCharacter.FaceId = 2095; 	break;
		case "Ostins_6"			:		rCharacter.FaceId = 2096; 	break;	
		case "Ostin"			:		rCharacter.FaceId = 2097; 	break; // Остин 
		
		// англйиская линейка
		case "Albermal"			:		rCharacter.FaceId = 2100; 	break; // герцог Албермаль
		case "ThomasLinch"		:		rCharacter.FaceId = 2105; 	break; // Томас Линч

		// нацлинейки
		case "BigPirate"		:		rCharacter.FaceId = 2110; 	break; // Олоне (франц) и д'Эстре (исп) (ремастер бы)
		
		// Работорговец
		case "horse99"			:		rCharacter.FaceId = 2183; 	break; // Изаура - пассия Таманго
		case "Tamango"			:		rCharacter.FaceId = 2024; 	break; // Таманго
		
		// Флейт Орион
		case "Andre_Abel"		:		rCharacter.FaceId = 2195; 	break; // Андре Абель
		
		// Кольцо Жозефины Лодет
		case "Francesca"		:		rCharacter.FaceId = 2201; 	break; // Франческа (можно сделать)
		
		// Аскольд
		case "Ascoldit"			:		rCharacter.FaceId = 2203; 	break; // Аскольд
		case "Margarita"		:		rCharacter.FaceId = 2206; 	break; // Маргарита (из ККС)
		case "Leif_Erikson"		:		rCharacter.FaceId = 2207; 	break; // Лейф Эриксон
		
		// Английская Линейка Блада
		case "Hobart"			:		rCharacter.FaceId = 2227; 	break; // полговник Хобарт
		
		// Летучий Голландец
		case "skeletcap"		:		rCharacter.FaceId = 2231; 	break; // главарь скелетов
		case "VanderDecken"		:		rCharacter.FaceId = 2232; 	break; // Ван дер Деккен
		
		// Синяя Птица
		case "Pasquale"			:		rCharacter.FaceId = 2236; 	break; // Паскаль
		
		// Французская Линейка де Граммона
		case "Fushe"			:		rCharacter.FaceId = 2250; 	break; // Джозеф Фуше
		case "granie"			:		rCharacter.FaceId = 2251; 	break; // Жан-Жак Гранье

		// Прекрасная Изабелла
		case "liza"				: 		rCharacter.FaceId = 2308; 	break; // Изабелла
		case "Atilla"			:		rCharacter.FaceId = 2310; 	break; // Атилла
		//case "girl_11":				rCharacter.FaceId = xxx; 	break; // Росита
		
		// Бывшие Викторинщики - Серия Квестов "Малые Приключения"
		// Неудобная Пропажа
		case "GrunIrma"			:		rCharacter.FaceId = 2331; break; // Ирма Грун (ремастер)
		case "GrunMaurits"		:		rCharacter.FaceId = 2332; break; // Мауритс Грун (ремастер)
		
		// Пиратская Мода
		case "LabbeLiliana"		:		rCharacter.FaceId = 2333; break; // Лелиана Лаббе (ремастер)
		case "LabbeVincent"		:		rCharacter.FaceId = 2334; break; // Винсен Лаббе (ремастер)
	}
}

void CirassMaker(aref rCharacter) //TODO: import from CL
{

}

// boal выбор модели в зависимости от типа
void SetCaptanModelByEncType(ref Chref, string sFantomType)
{
	string ModelPirate = "Albermal"; // значит баг
	
	int st = GetCharacterShipType(Chref); // ship нужно устанавливать до вызова этой функции

	if (sti(Chref.nation) == PIRATE) sFantomType = "pirate"; // иначе баг
	
	if(st != SHIP_NOTUSED) 	// есть корабль
	{
		ref rBaseShip = GetRealShip(sti(Chref.Ship.Type));
		int shClass = sti(rBaseShip.Class);
		switch (sFantomType)
		{
			case "trade":
				ModelPirate = "merch_" + (rand(14) + 1);
				/* TODO:
				if(shClass >= 4) ModelPirate = ;
				if(shClass == 3) ModelPirate = ;
				if(shClass <  3) ModelPirate = ;*/
				Chref.PhantomType = "citizen"; // пусть будет
			break;
			case "pirate":
				if(shClass > 4)					ModelPirate = "officer_" + (rand(9) + 1); //МЛАДШИЕ
				if(shClass < 5 && shClass > 2)	ModelPirate = "officer_" + (rand(9) + 11);//СТАРШИЕ
				if(shClass < 3)					ModelPirate = "officer_" + (rand(7) + 21);//ВЫСШИЕ
				//"citiz_" + (rand(9) + 51);
				Chref.PhantomType = "pirate";
			break;
			case "war":			
				if(shClass >= 4) 				ModelPirate = "navy_off_" + NationShortName(sti(Chref.nation)) + "_" + (rand(1) + 1); //МЛАДШИЕ
				if(shClass <  4 && shClass > 1)	ModelPirate = "navy_off_" + NationShortName(sti(Chref.nation)) + "_" + (rand(1) + 3); //СТАРШИЕ
				if(shClass == 1)
				{
						if(sti(RealShips[sti(Chref.ship.type)].basetype) == SHIP_FORT) // командующие фортами
						{
							ModelPirate = "off_" + NationShortName(sti(Chref.nation)) + "_" + (rand(4) + 7);
						}
						else // командующие линейными кораблями
						{
							if(sti(RealShips[sti(Chref.ship.type)].basetype) == SHIP_MANOWAR) //АДМИРАЛЫ
							ModelPirate = "navy_off_" + NationShortName(sti(Chref.nation)) + "_6";
							else ModelPirate = "navy_off_" + NationShortName(sti(Chref.nation)) + "_5"; //ВЫСШИЕ
						}
				}
				Chref.PhantomType = "officer";
			break;
		}
	}
	else // корабль отсутствует
	{
		switch (sFantomType)
		{
			case "trade":
				ModelPirate = "merch_" + (rand(14) + 1);
				Chref.PhantomType = "citizen";
			break;
			case "war":
				ModelPirate = "navy_off_" + NationShortName(sti(Chref.nation)) + "_" + (rand(1) + 1); //берём МЛАДШИХ
				Chref.PhantomType = "officer";
			break;
			case "pirate":
				ModelPirate = "officer_" + (rand(19) + 1); //берём рандомного офицера
				Chref.PhantomType = "pirate";
			break;
		}
	}
	
	Chref.model = ModelPirate;
	FaceMaker(Chref);
	CirassMaker(Chref);
}

void SetModelPirate(ref ChrefPirate)
{
    string ModelPirate;
    
    ModelPirate = "Pirate_" + (rand(15) + 1);
    
    ChrefPirate.model = ModelPirate;
    FaceMaker(ChrefPirate);
	CirassMaker(ChrefPirate);
}

// Warship. Обновим персу модель и анимацию. Пока-что здесь
void Characters_RefreshModel(ref rChar)
{
	SendMessage(rChar, "lss", MSG_CHARACTER_SETMODEL, rChar.model, rChar.model.animation);
}

//Создадим вражеских фантомов
string GetRandSkelModel()
{
	string emodel = "mummy";

	switch (rand(3))
    {
        case 0: emodel = "Skel1";	break;
        case 1: emodel = "Skel2";	break;
        case 2: emodel = "Skel3";	break;
        case 3: emodel = "Skel4";	break;
    }
    return emodel;
}

// Rosarak. Рандом из зажиточных и простых горожан
string RandCitizenModel()
{
	if(rand(1)) return "citiz_"+(rand(9)+11);
	else		return GetRandSubString(COMMONERS);
}

string RandCitizenType()
{
	if(rand(1)) return "citizen";
	else		return "commoner";
}

string RandPirCitizenModel()
{
	if (rand(1)) return "pirate_"+(rand(15)+1);
	else		 return "citiz_" +(rand(9)+21);
}
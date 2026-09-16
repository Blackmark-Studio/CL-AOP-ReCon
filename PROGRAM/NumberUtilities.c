// Warship. методы для работы с числами
// Большую часть попереносил из других файлов, чтобы все в одном месте было

#define PI 3.14159265
#define PIm2  6.28318530   // PI * 2.0
#define PId2  1.57079632   // PI / 2.0
#define PId3  1.04719755   // PI / 3.0
#define PId4  0.78539816   // PI / 4.0
#define PId6  0.52359878   // PI / 6.0

float FRAND(float _x)
{
	return rand(32768) / 32768.0 * _x;
}

float frandSmall(float _x)
{
	return rand(32) / 32.0 * _x;
}

// рандом 0.0 ... 1.0
float Random()
{
	return rand(32768) / 32768.0; // 32769.0
}

//HardCoffee Оригинальная задумка корсарских скриптов - возможность пихать отрицательные значения в max rand
//так как для idRand я убрал такую возможность, то оставляю для dRand как и задумывалось духом корсаров
//idRand в свою очередь будет обрабатывать отрицательный max rand как скриптовую ошибку с записью в лог
int dRand(int _max)
{
	bool isNeg = false;
	if (_max < 0)
	{
		_max = abs(_max);
		isNeg = true;
	}
	_max = idRand("oldDrand", _max);
	if (isNeg)
	{
	    _max = -_max;
	}
	return _max;
}

int dRandEx(int _num, bool next) //перегрузка для dRandEx
{
	int i;
	int n;
	aref aNum, attribute;
	string sTemp;
	if (!CheckAttribute(&TEV, "dRandEx"))
	{
		TEV.dRandEx.last = "0";
		for(i = 1; i <= 10; i++)
		{
			sTemp = ""+i;
			TEV.dRandEx.(sTemp) = Rand(32762);
		}
	}
	n = sti(TEV.dRandEx.last);
	makearef(aNum, TEV.dRandEx);

	attribute = GetAttributeN(aNum, n);
	sTemp = "DrandEx" +GetAttributeName(attribute);
	n++;
	if (n == 10) n = 0;
	TEV.dRandEx.last = its(n);
	return idRand(sTemp, _num);
}


// радианы в градусы
float Radian2Degree(float _rad) 
{
	return 180 / PI * _rad;
}

int func_max(int a, int b)
{
	if (a > b) return a;
	return b;
}

int func_min(int a, int b)
{
	if (a > b) return b;
	return a;
}

int round_up(float x) // evganat - округление вверх
{
	if (makefloat(makeint(x)) == x)
	{
		return makeint(x);
	}
	if (x > 0)
	{
		return makeint(x+1.0);
	}
	return makeint(x-1.0);
}

int round_near(float x) // evganat - округление до ближайшего
{
	if (makefloat(makeint(x)) == x)
	{
		return makeint(x);
	}
	if (abs(x) - makefloat(makeint(abs(x))) >= 0.5)
	{
		return round_up(x);
	}
	return makeint(x);
}

// evganat - бинарный рандом, делит диапазон пополам, пока не сможет вычислить напрямую; использовать при значениях аргумента, больших 32767
int RandBin(int iArg)
{
	if(iArg <= 32767)
		return rand(iArg);
	int iTag, r;
	int res = 0;
	while(iArg > 63)
	{
		if(iArg % 2 == 1)
			iTag = 1;
		else
			iTag = 0;
		iArg = iArg / 2;
		r = rand(1);		
		res = res + r * iArg;
		if(r == 1)
			iArg += iTag;
	}
	if(res == 0)
		res = res + rand(iArg);
	else
		res = res + rand(iArg-1) + 1;
	return res;
}

// KZ > значение value не может быть меньше min или больше max; "" в min/max - не ограничивать min/max
void Restrictor(ref value, ref min, ref max)
{
	if (value < min)
		value = min;
	else if (value > max)
		value = max;
}

string its(int iNumber)
{
	string sText = iNumber;
	return sText;
}

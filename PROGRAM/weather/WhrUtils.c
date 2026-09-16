int Whr_GetColor(aref arRef, string sAttribute)
{
	if (!CheckAttribute(arRef, sAttribute)) return 0;
	return sti(arRef.(sAttribute));
}

float Whr_GetFloat(aref arRef, string sAttribute)
{
	string sTmpAttr = sAttribute + ".max";
	if (CheckAttribute(arRef,sTmpAttr))
	{
		float fMin = stf(arRef.(sAttribute).min);
		float fMax = stf(arRef.(sAttribute).max);
		return fMin + frnd() * (fMax - fMin);
	}

	if (!CheckAttribute(arRef, sAttribute)) return 0.0; //задолбало

	return stf(arRef.(sAttribute));
}

int Whr_GetLong(aref arRef, string sAttribute)
{
	string sTmpAttr = sAttribute + ".max";
	if (CheckAttribute(arRef,sTmpAttr))
	{
		int iMin = sti(arRef.(sAttribute).min);
		int iMax = sti(arRef.(sAttribute).max);
		return iMin + rand(iMax - iMin);
	}
	if (!CheckAttribute(arRef, sAttribute)) return 0;
	return sti(arRef.(sAttribute));
}

string Whr_GetString(aref arRef, string sAttribute)
{
	if (!CheckAttribute(arRef, sAttribute)) return "";
	return arRef.(sAttribute);
}

void eChangeDayNight()
{
	/*if(Whr_IsDay() == true)
	{
		ShowCitizens(false, FindLocation(pchar.location));
	}

	if(Whr_IsNight() == true)
	{
		HideCitizens();
	}
	RecalculateJumpTable();*/
	// для вмл это не нужно, тк время обрабатывается он лайн
}

//navy -->
float GetSunHeightAngle(int _hour)
{
	if (_hour > 5 && _hour < 13)
	{
		return Degree2Radian(0.0 + 12.0*(_hour-6));
	}
	if (_hour > 12 && _hour < 19)
	{
		return Degree2Radian(72.0 - 12.0*(_hour-12));
	}
	return -1;
}
//navy <--

// конвертор часов в интенсивность освещения (2 часа ночи - самый чёрный час, интенсивность 0; 14 часов - самый яркий час, интенсивность 1)
float SM_HourToLightIntencity(float hour)
{
	return abs(abs((hour - 14) / 12) - 1);
}

// тоже самое, только для текущего часа
float SM_CurrentHourToLightIntencity()
{
	return SM_HourToLightIntencity(GetHour());
}

// округление до знаков после точки
float SM_FastRound(float f, int d)
{
	float h = 0.5;
	if (f < 0) h = -0.5;
	
	if (d == 0)
		return makeint(f + h);
	
	float p = pow(10, d);
	return makefloat(makeint(f * p + h)) / p;
}
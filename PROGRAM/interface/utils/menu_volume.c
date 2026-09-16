// KZ > плавное приглушение и возврат громкости на экранах меню

#define MENUVOL_TIME     3.7    // > сколько длится полный переход, сек
#define MENUVOL_QUIET    0.333  // > доля громкости музыки в приглушённом состоянии
#define MENUVOL_MIN_STEP 0.004  // > мельче этого изменения громкости в движок не шлём

float fMenuVol = 1.0;   // > текущий уровень: 0.0 приглушено, 1.0 обычная громкость
float fMenuVolGoal;     // > куда едем
float fMenuVolSent;     // > уровень, последним ушедший в движок
bool  bMenuVolFade;     // > переход идёт
bool  bMenuVolAmbience; // > в конце приглушения сбросить схему звука

// > Приглушить громкость.
// > bStopAmbience - в конце сбросить схему звука: экран выбора героя грузит локацию, и её фон после приглушения уже не нужен.
void MenuVolume_FadeOut(bool bStopAmbience)
{
	bMenuVolAmbience = bStopAmbience;
	MenuVolume_Start(0.0);
}

// > Вернуть громкость к обычной.
void MenuVolume_FadeIn()
{
	bMenuVolAmbience = false;
	MenuVolume_Start(1.0);
}

// > Вернуть громкость сразу и забыть уровень.
void MenuVolume_Restore()
{
	MenuVolume_Halt();
	DeleteAttribute(&TEV, "MENUVOLUME.LEVEL");

	if (fMenuVol == 1.0)
		return; // > громкость и так обычная

	fMenuVol = 1.0;
	MenuVolume_Apply();
}

// > Выход из интерфейса.
void MenuVolume_Stop()
{
	MenuVolume_Halt();
	TEV.MENUVOLUME.LEVEL = fMenuVol;
}

void MenuVolume_Start(float fGoal)
{
	fMenuVol = 1.0;

	if (CheckAttribute(&TEV, "MENUVOLUME.LEVEL")) fMenuVol = stf(TEV.MENUVOLUME.LEVEL);
	if (fMenuVol < 0.0) fMenuVol = 0.0;
	if (fMenuVol > 1.0) fMenuVol = 1.0;

	fMenuVolGoal = fGoal;
	bMenuVolFade = (fMenuVol != fGoal);

	if (!bMenuVolFade)
	{	// > ехать некуда, и трогать громкость нельзя: установка с id 0 сбрасывает собственную громкость каждому играющему звуку, в том числе фоновому
		if (bMenuVolAmbience)
			ResetSoundScheme();
		return;
	}

	// > стартовую громкость ставим сразу, не дожидаясь кадра: музыку и схему звука экран заводит перед вызовом, а новые звуки стартуют с обычной громкостью
	MenuVolume_Apply();
	SetEventHandler("frame", "MenuVolume_Frame", 0);
}

// > Один кадр перехода.
// > Время реальное, поэтому переход длится MENUVOL_TIME при любом FPS и любом таймскейле - меняется только плавность.
void MenuVolume_Frame()
{
	if (!bMenuVolFade) return;

	float fStep = GetRealDeltaTime() / MENUVOL_TIME;

	if (fMenuVolGoal > fMenuVol)
	{
		fMenuVol = fMenuVol + fStep;
		if (fMenuVol > fMenuVolGoal)
			fMenuVol = fMenuVolGoal;
	}
	else
	{
		fMenuVol = fMenuVol - fStep;
		if (fMenuVol < fMenuVolGoal)
			fMenuVol = fMenuVolGoal;
	}

	// > установка громкости обходит в движке все играющие звуки, а разницу мельче MENUVOL_MIN_STEP на слух не поймать: шлём заметные изменения и конец пути
	if (fMenuVol == fMenuVolGoal || fMenuVol - fMenuVolSent > MENUVOL_MIN_STEP || fMenuVolSent - fMenuVol > MENUVOL_MIN_STEP)
	{
		MenuVolume_Apply();
	}

	if (fMenuVol != fMenuVolGoal) return;

	MenuVolume_Halt();

	if (bMenuVolAmbience)
		ResetSoundScheme(); // > приглушение доехало, фон больше не нужен
}

// > Уровень в громкость.
// > У музыки своя обычная громкость, её ставит KZ|MusicPlay и оттуда же её берёт KZ|Mute
void MenuVolume_Apply()
{
	float fMusic = 1.0; // > обычная громкость трека

	if (CheckAttribute(&TEV, "Music.Volume"))
		fMusic = stf(TEV.Music.Volume);

	fMusic = fMusic * (MENUVOL_QUIET + (1.0 - MENUVOL_QUIET) * fMenuVol);

	fMenuVolSent = fMenuVol;
	KZ|Volume(fMusic, fMenuVol);
}

void MenuVolume_Halt()
{
	DelEventHandler("frame", "MenuVolume_Frame");
	bMenuVolFade = false;
}

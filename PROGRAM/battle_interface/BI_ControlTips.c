
#define KEY_ALIGN "left"
#define N_TIPS 6 //Сколько максимум подсказок в столбике

bool bCommMenu = false;

string sCommandTip = "";
float fTipKeyScale = 1.0;

int ITxtLines[N_TIPS];
int IKeyLines[N_TIPS];
int IFadLines[N_TIPS];

void InitSeaTips(int iIconSize, int iPosY)
{
	int i, iDeltaX, iDeltaY, iPosX, iTipKeyOffsetX, iTipKeyOffsetY;
	float fHtRatio = GetScreenScale();

	fTipKeyScale = 0.6 * fHtRatio; //размер значка кнопки зарядов и перков
	fTextScale = 1.2 * fHtRatio; //размер шрифта подсказок
	itextColor = GetColorInt("white");

	int iTipKeyColor = itextColor;
	int iTipX = sti(showWindow.left) + RecalculateHIcon(29 * fHtRatio); //позиция подсказок от начала экрана
	int iTipYDelta = RecalculateVIcon(45 * fHtRatio); //расстояние между подсказками по высоте
	int iTipXText = iTipX + RecalculateHIcon(42 * fHtRatio); //расстояние между изображением кнопки и текстом
	int iTipTextY = RecalculateVIcon(4 * fHtRatio);  //корректировка для описания клавиши
	int iTipFadY = RecalculateVIcon(5 * fHtRatio); //корректировка высоты текста
	int iTipFadX = iTipX + RecalculateHIcon(171 * fHtRatio); //корректировка отступа подложки от края экрана
	int ifaderColor = GetColorArgb("white", 155); //прозрачность подложки
	float fFaderScale = 0.6 * fHtRatio; //Размер подложки

	if (GetArraySize(&IKeyLines) < N_TIPS) SetArraySize(&IKeyLines, N_TIPS);
	if (GetArraySize(&ITxtLines) < N_TIPS) SetArraySize(&ITxtLines, N_TIPS);
	if (GetArraySize(&IFadLines) < N_TIPS) SetArraySize(&IFadLines, N_TIPS);

	IKeyLines[0] = sti(showWindow.bottom) - RecalculateVIcon(65 * fHtRatio); //расстояние от низа экрана до первой подсказки
	ITxtLines[0] = IKeyLines[0] + iTipTextY;
	IFadLines[0] = IKeyLines[0] - iTipFadY; //корректировка высоты подложки

	for (i = 1; i < N_TIPS; i++)
	{
		IKeyLines[i] = IKeyLines[i - 1] - iTipYDelta;
		ITxtLines[i] = IKeyLines[i] + iTipTextY;
		IFadLines[i] = IKeyLines[i] - iTipFadY;
	}

	if (iShowTips >= CONTROL_TIPS_BASE)
	{
//кнопки зарядов -->
		iDeltaY = iIconSize * 0.5 - RecalculateVIcon(16 * fHtRatio); //Отступы от центра значка
		iDeltaX = iIconSize * 0.5 - RecalculateHIcon(8 * fHtRatio);
		iPosY += iDeltaY;

		BattleInterface.textinfo.BallsKey.font = "keyboard_symbol";
		BattleInterface.textinfo.BallsKey.scale = fTipKeyScale;
		BattleInterface.textinfo.BallsKey.color = iTipKeyColor;
		BattleInterface.textinfo.BallsKey.pos.x = sti(BattleInterface.bottomBar.ballsPos) - iDeltaX;
		BattleInterface.textinfo.BallsKey.pos.y = iPosY;
		BattleInterface.textinfo.BallsKey.text = GetKeyCodeImg("hk_charge1");

		BattleInterface.textinfo.GrapesKey.font = "keyboard_symbol";
		BattleInterface.textinfo.GrapesKey.scale = fTipKeyScale;
		BattleInterface.textinfo.GrapesKey.color = iTipKeyColor;
		BattleInterface.textinfo.GrapesKey.pos.x = sti(BattleInterface.bottomBar.grapesPos) - iDeltaX;
		BattleInterface.textinfo.GrapesKey.pos.y = iPosY;
		BattleInterface.textinfo.GrapesKey.text = GetKeyCodeImg("hk_charge2");

		BattleInterface.textinfo.KnippelsKey.font = "keyboard_symbol";
		BattleInterface.textinfo.KnippelsKey.scale = fTipKeyScale;
		BattleInterface.textinfo.KnippelsKey.color = iTipKeyColor;
		BattleInterface.textinfo.KnippelsKey.pos.x = sti(BattleInterface.bottomBar.knippelsPos) - iDeltaX;
		BattleInterface.textinfo.KnippelsKey.pos.y = iPosY;
		BattleInterface.textinfo.KnippelsKey.text = GetKeyCodeImg("hk_charge3");

		BattleInterface.textinfo.BombsKey.font = "keyboard_symbol";
		BattleInterface.textinfo.BombsKey.scale = 0.6 * fHtRatio;
		BattleInterface.textinfo.BombsKey.color = iTipKeyColor;
		BattleInterface.textinfo.BombsKey.pos.x = sti(BattleInterface.bottomBar.bombsPos) - iDeltaX;
		BattleInterface.textinfo.BombsKey.pos.y = iPosY;
		BattleInterface.textinfo.BombsKey.text = GetKeyCodeImg("hk_charge4");
// <-- кнопки зарядов
// кнопки перков -->
		iDeltaY = RecalculateVIcon(24 * fHtRatio); //Отступы от центра сегмента
		iDeltaX = RecalculateHIcon(0 * fHtRatio);
		iTipKeyOffsetX = RecalculateVIcon(-2 * fHtRatio);
		iTipKeyOffsetY = RecalculateHIcon(-10 * fHtRatio);
		if (IsSeaPerkAcquired(objSeaPerkShower.SegmentsInfo.Up))
		{
			iPosY = sti(FindStringAfterChar(objSeaPerkShower.SeaPerkShowerPos, ",")) +
				sti(FindStringAfterChar(objSeaPerkShower.UpSegmentOffset, ",")) +
				iTipKeyOffsetY;
			iPosX = sti(FindStringBeforeChar(objSeaPerkShower.SeaPerkShowerPos, ",")) +
				sti(FindStringBeforeChar(objSeaPerkShower.UpSegmentOffset, ",")) +
				iTipKeyOffsetX;
			BattleInterface.textinfo.TurnKey.font = "keyboard_symbol";
			BattleInterface.textinfo.TurnKey.scale = fTipKeyScale;
			BattleInterface.textinfo.TurnKey.color = iTipKeyColor;
			BattleInterface.textinfo.TurnKey.pos.x = iPosX + iDeltaX + makeint(0 * fHtRatio);
			BattleInterface.textinfo.TurnKey.pos.y = iPosY + iDeltaY + makeint(6 * fHtRatio);
			BattleInterface.textinfo.TurnKey.text = GetKeyCodeImg("hk_perk1");
		}

		if (IsSeaPerkAcquired(objSeaPerkShower.SegmentsInfo.Left))
		{
			iPosY = sti(FindStringAfterChar(objSeaPerkShower.SeaPerkShowerPos, ",")) +
				sti(FindStringAfterChar(objSeaPerkShower.LeftSegmentOffset, ",")) +
				iTipKeyOffsetY;
			iPosX = sti(FindStringBeforeChar(objSeaPerkShower.SeaPerkShowerPos, ",")) +
				sti(FindStringBeforeChar(objSeaPerkShower.LeftSegmentOffset, ",")) +
				iTipKeyOffsetX;
			BattleInterface.textinfo.ImmReloadKey.font = "keyboard_symbol";
			BattleInterface.textinfo.ImmReloadKey.scale = fTipKeyScale;
			BattleInterface.textinfo.ImmReloadKey.color = iTipKeyColor;
			BattleInterface.textinfo.ImmReloadKey.pos.x = iPosX + iDeltaY + makeint(2 * fHtRatio);
			BattleInterface.textinfo.ImmReloadKey.pos.y = iPosY + iDeltaX + makeint(-3 * fHtRatio);
			BattleInterface.textinfo.ImmReloadKey.text = GetKeyCodeImg("hk_perk2");
		}
		if (IsSeaPerkAcquired(objSeaPerkShower.SegmentsInfo.Right))
		{
			iPosY = sti(FindStringAfterChar(objSeaPerkShower.SeaPerkShowerPos, ",")) +
				sti(FindStringAfterChar(objSeaPerkShower.RightSegmentOffset, ",")) +
				iTipKeyOffsetY;
			iPosX = sti(FindStringBeforeChar(objSeaPerkShower.SeaPerkShowerPos, ",")) +
				sti(FindStringBeforeChar(objSeaPerkShower.RightSegmentOffset, ",")) +
				iTipKeyOffsetX;
			BattleInterface.textinfo.InstantRepKey.font = "keyboard_symbol";
			BattleInterface.textinfo.InstantRepKey.scale = fTipKeyScale;
			BattleInterface.textinfo.InstantRepKey.color = iTipKeyColor;
			BattleInterface.textinfo.InstantRepKey.pos.x = iPosX - iDeltaY;
			BattleInterface.textinfo.InstantRepKey.pos.y = iPosY + iDeltaX + makeint(-3 * fHtRatio);
			BattleInterface.textinfo.InstantRepKey.text = GetKeyCodeImg("hk_perk3");
		}
		if (IsSeaPerkAcquired(objSeaPerkShower.SegmentsInfo.Down))
		{
			iPosY = sti(FindStringAfterChar(objSeaPerkShower.SeaPerkShowerPos, ",")) +
				sti(FindStringAfterChar(objSeaPerkShower.DownSegmentOffset, ",")) +
				iTipKeyOffsetY;
			iPosX = sti(FindStringBeforeChar(objSeaPerkShower.SeaPerkShowerPos, ",")) +
				sti(FindStringBeforeChar(objSeaPerkShower.DownSegmentOffset, ",")) +
				iTipKeyOffsetX;
			BattleInterface.textinfo.LightRepKey.font = "keyboard_symbol";
			BattleInterface.textinfo.LightRepKey.scale = fTipKeyScale;
			BattleInterface.textinfo.LightRepKey.color = iTipKeyColor;
			BattleInterface.textinfo.LightRepKey.pos.x = iPosX - iDeltaX;
			BattleInterface.textinfo.LightRepKey.pos.y = iPosY - iDeltaY + makeint(-6 * fHtRatio);
			BattleInterface.textinfo.LightRepKey.text = GetKeyCodeImg("hk_perk4");
		}
// кнопки перков <--
	}
	// <-- iShowTips >= CONTROL_TIPS_BASE

	// убираем тип для каюты - сдвигаем остальные строки
	int iShiftLine = 1;
	if (!GetGlobalTutor())
	{
		iShiftLine = 0;
	}

	fTipKeyScale = 0.9 * fHtRatio; //размер значка кнопки столбика подсказок
	if (iShowTips >= CONTROL_TIPS_EXTEND)
	{
//провести залп -->
		if (iShowTips == CONTROL_TIPS_EXTEND) iPosY = 0;
		else if (iShowTips >= CONTROL_TIPS_ALL) iPosY = 4 - iShiftLine;
		BattleInterface.textinfo.SalvoFad.font = "INFO_FADER_LS";
		BattleInterface.textinfo.SalvoFad.scale = fFaderScale;
		BattleInterface.textinfo.SalvoFad.color = ifaderColor;
		BattleInterface.textinfo.SalvoFad.pos.x = iTipFadX;
		BattleInterface.textinfo.SalvoFad.align = "centr";
		BattleInterface.textinfo.SalvoFad.pos.y = IFadLines[iPosY];
		BattleInterface.textinfo.SalvoFad.text = " ";
		BattleInterface.textinfo.SalvoFad.refreshable = true;

		BattleInterface.textinfo.SalvoKey.font = "keyboard_symbol";
		BattleInterface.textinfo.SalvoKey.scale = fTipKeyScale;
		BattleInterface.textinfo.SalvoKey.color = iTipKeyColor;
		BattleInterface.textinfo.SalvoKey.pos.x = iTipX;
		BattleInterface.textinfo.SalvoKey.align = KEY_ALIGN;
		BattleInterface.textinfo.SalvoKey.pos.y = IKeyLines[iPosY];
		BattleInterface.textinfo.SalvoKey.text = " ";
		BattleInterface.textinfo.SalvoKey.refreshable = true;

		BattleInterface.textinfo.SalvoTip.font = "interface_normal";
		BattleInterface.textinfo.SalvoTip.scale = fTextScale;
		BattleInterface.textinfo.SalvoTip.color = itextColor;
		BattleInterface.textinfo.SalvoTip.pos.x = iTipXText;
		BattleInterface.textinfo.SalvoTip.align = "left";
		BattleInterface.textinfo.SalvoTip.pos.y = ITxtLines[iPosY];
		BattleInterface.textinfo.SalvoTip.text = " ";
		BattleInterface.textinfo.SalvoTip.refreshable = true;
//провести залп <--
	}
	// <-- iShowTips >= CONTROL_TIPS_EXTEND
	if (iShowTips >= CONTROL_TIPS_ALL)
	{
//в каюту -->
		if (!GetGlobalTutor())
		{
			iPosY = 1;
			BattleInterface.textinfo.CabinFad.font = "INFO_FADER_LS";
			BattleInterface.textinfo.CabinFad.scale = fFaderScale;
			BattleInterface.textinfo.CabinFad.color = ifaderColor;
			BattleInterface.textinfo.CabinFad.pos.x = iTipFadX;
			BattleInterface.textinfo.CabinFad.align = "centr";
			BattleInterface.textinfo.CabinFad.pos.y = IFadLines[iPosY];
			BattleInterface.textinfo.CabinFad.text = "1";
			BattleInterface.textinfo.CabinFad.refreshable = true;

			BattleInterface.textinfo.CabinKey.font = "keyboard_symbol";
			BattleInterface.textinfo.CabinKey.scale = fTipKeyScale;
			BattleInterface.textinfo.CabinKey.color = iTipKeyColor;
			BattleInterface.textinfo.CabinKey.pos.x = iTipX;
			BattleInterface.textinfo.CabinKey.align = KEY_ALIGN;
			BattleInterface.textinfo.CabinKey.pos.y = IKeyLines[iPosY];
			BattleInterface.textinfo.CabinKey.text = GetKeyCodeImg("hk_cabin");
			BattleInterface.textinfo.CabinKey.refreshable = true;


			BattleInterface.textinfo.CabinTip.font = "interface_normal";
			BattleInterface.textinfo.CabinTip.scale = fTextScale;
			BattleInterface.textinfo.CabinTip.color = itextColor;
			BattleInterface.textinfo.CabinTip.pos.x = iTipXText;
			BattleInterface.textinfo.CabinTip.align = "left";
			BattleInterface.textinfo.CabinTip.pos.y = ITxtLines[iPosY];
			BattleInterface.textinfo.CabinTip.text = LanguageConvertString(iControlsFile, "hk_cabin");
			BattleInterface.textinfo.CabinTip.refreshable = true;
		}
//в каюту <--
//зоны стрельбы -->
		iPosY = 0;
		BattleInterface.textinfo.FirezoneFad.font = "INFO_FADER_LS";
		BattleInterface.textinfo.FirezoneFad.scale = fFaderScale;
		BattleInterface.textinfo.FirezoneFad.color = ifaderColor;
		BattleInterface.textinfo.FirezoneFad.pos.x = iTipFadX;
		BattleInterface.textinfo.FirezoneFad.align = "centr";
		BattleInterface.textinfo.FirezoneFad.pos.y = IFadLines[iPosY];
		BattleInterface.textinfo.FirezoneFad.text = "1";
		BattleInterface.textinfo.FirezoneFad.refreshable = true;

		BattleInterface.textinfo.FirezoneKey.font = "keyboard_symbol";
		BattleInterface.textinfo.FirezoneKey.scale = fTipKeyScale;
		BattleInterface.textinfo.FirezoneKey.color = iTipKeyColor;
		BattleInterface.textinfo.FirezoneKey.pos.x = iTipX;
		BattleInterface.textinfo.FirezoneKey.align = KEY_ALIGN;
		BattleInterface.textinfo.FirezoneKey.pos.y = IKeyLines[iPosY];
		BattleInterface.textinfo.FirezoneKey.text = GetKeyCodeImg("FirezoneKey");
		BattleInterface.textinfo.FirezoneKey.refreshable = true;

		BattleInterface.textinfo.FirezoneTip.font = "interface_normal";
		BattleInterface.textinfo.FirezoneTip.scale = fTextScale;
		BattleInterface.textinfo.FirezoneTip.color = itextColor;
		BattleInterface.textinfo.FirezoneTip.pos.x = iTipXText;
		BattleInterface.textinfo.FirezoneTip.align = "left";
		BattleInterface.textinfo.FirezoneTip.pos.y = ITxtLines[iPosY];
		BattleInterface.textinfo.FirezoneTip.text = "";
		BattleInterface.textinfo.FirezoneTip.refreshable = true;
		RefreshFireZoneTip();
//зоны стрельбы <--
//навигация по командному меню -->
		//Позиция из массива присвоится в BI_SetSelectTip
		iPosY = 0;
		BattleInterface.textinfo.HorFad.font = "INFO_FADER_LS";
		BattleInterface.textinfo.HorFad.scale = fFaderScale;
		BattleInterface.textinfo.HorFad.color = ifaderColor;
		BattleInterface.textinfo.HorFad.pos.x = iTipFadX;
		BattleInterface.textinfo.HorFad.align = "centr";
		BattleInterface.textinfo.HorFad.pos.y = iPosY;
		BattleInterface.textinfo.HorFad.text = " ";
		BattleInterface.textinfo.HorFad.refreshable = true;

		BattleInterface.textinfo.HorKey.font = "keyboard_symbol";
		BattleInterface.textinfo.HorKey.scale = fTipKeyScale;
		BattleInterface.textinfo.HorKey.color = iTipKeyColor;
		BattleInterface.textinfo.HorKey.pos.x = iTipX;
		BattleInterface.textinfo.HorKey.align = KEY_ALIGN;
		BattleInterface.textinfo.HorKey.pos.y = iPosY;
		BattleInterface.textinfo.HorKey.text = " ";
		BattleInterface.textinfo.HorKey.refreshable = true;

		BattleInterface.textinfo.HorTip.font = "interface_normal";
		BattleInterface.textinfo.HorTip.scale = fTextScale;
		BattleInterface.textinfo.HorTip.color = itextColor;
		BattleInterface.textinfo.HorTip.pos.x = iTipXText +RecalculateHIcon(65 * fHtRatio);
		BattleInterface.textinfo.HorTip.align = "left";
		BattleInterface.textinfo.HorTip.pos.y = iPosY;
		BattleInterface.textinfo.HorTip.text = " ";
		BattleInterface.textinfo.HorTip.refreshable = true;

		BattleInterface.textinfo.VerFad.font = "INFO_FADER_LS";
		BattleInterface.textinfo.VerFad.scale = fFaderScale;
		BattleInterface.textinfo.VerFad.color = ifaderColor;
		BattleInterface.textinfo.VerFad.pos.x = iTipFadX;
		BattleInterface.textinfo.VerFad.align = "centr";
		BattleInterface.textinfo.VerFad.pos.y = iPosY;
		BattleInterface.textinfo.VerFad.text = " ";
		BattleInterface.textinfo.VerFad.refreshable = true;

		BattleInterface.textinfo.VerKey.font = "keyboard_symbol";
		BattleInterface.textinfo.VerKey.scale = fTipKeyScale;
		BattleInterface.textinfo.VerKey.color = iTipKeyColor;
		BattleInterface.textinfo.VerKey.pos.x = iTipX;
		BattleInterface.textinfo.VerKey.align = KEY_ALIGN;
		BattleInterface.textinfo.VerKey.pos.y = iPosY;
		BattleInterface.textinfo.VerKey.text = " ";
		BattleInterface.textinfo.VerKey.refreshable = true;

		BattleInterface.textinfo.VerTip.font = "interface_normal";
		BattleInterface.textinfo.VerTip.scale = fTextScale;
		BattleInterface.textinfo.VerTip.color = itextColor;
		BattleInterface.textinfo.VerTip.pos.x = iTipXText +RecalculateHIcon(35 * fHtRatio);
		BattleInterface.textinfo.VerTip.align = "left";
		BattleInterface.textinfo.VerTip.pos.y = iPosY;
		BattleInterface.textinfo.VerTip.text = " ";
		BattleInterface.textinfo.VerTip.refreshable = true;
//навигация по командному меню <--
//командное меню -->
		iPosY = 2 - iShiftLine;
		BattleInterface.textinfo.EnterFad.font = "INFO_FADER_LS";
		BattleInterface.textinfo.EnterFad.scale = fFaderScale;
		BattleInterface.textinfo.EnterFad.color = ifaderColor;
		BattleInterface.textinfo.EnterFad.pos.x = iTipFadX;
		BattleInterface.textinfo.EnterFad.align = "centr";
		BattleInterface.textinfo.EnterFad.pos.y = IFadLines[iPosY];
		BattleInterface.textinfo.EnterFad.text = "1";
		BattleInterface.textinfo.EnterFad.refreshable = true;

		BattleInterface.textinfo.EnterKey.font = "keyboard_symbol";
		BattleInterface.textinfo.EnterKey.scale = fTipKeyScale;
		BattleInterface.textinfo.EnterKey.color = iTipKeyColor;
		BattleInterface.textinfo.EnterKey.pos.x = iTipX;
		BattleInterface.textinfo.EnterKey.align = KEY_ALIGN;
		BattleInterface.textinfo.EnterKey.pos.y = IKeyLines[iPosY];
		BattleInterface.textinfo.EnterKey.text = GetKeyCodeImg("BICommandsActivate");
		BattleInterface.textinfo.EnterKey.refreshable = true;

		BattleInterface.textinfo.EnterTip.font = "interface_normal";
		BattleInterface.textinfo.EnterTip.scale = fTextScale;
		BattleInterface.textinfo.EnterTip.color = itextColor;
		BattleInterface.textinfo.EnterTip.pos.x = iTipXText;
		BattleInterface.textinfo.EnterTip.align = "left";
		BattleInterface.textinfo.EnterTip.pos.y = ITxtLines[iPosY];
		BattleInterface.textinfo.EnterTip.text = LanguageConvertString(iControlsFile, "BICommandsActivate");
		BattleInterface.textinfo.EnterTip.refreshable = true;
//командное меню <--
//переключить камеру -->
		iPosY = 3 - iShiftLine;
		BattleInterface.textinfo.CameraFad.font = "INFO_FADER_LS";
		BattleInterface.textinfo.CameraFad.scale = fFaderScale;
		BattleInterface.textinfo.CameraFad.color = ifaderColor;
		BattleInterface.textinfo.CameraFad.pos.x = iTipFadX;
		BattleInterface.textinfo.CameraFad.align = "centr";
		BattleInterface.textinfo.CameraFad.pos.y = IFadLines[iPosY];
		BattleInterface.textinfo.CameraFad.text = "1";
		BattleInterface.textinfo.CameraFad.refreshable = true;

		BattleInterface.textinfo.CameraKey.font = "keyboard_symbol";
		BattleInterface.textinfo.CameraKey.scale = fTipKeyScale;
		BattleInterface.textinfo.CameraKey.color = iTipKeyColor;
		BattleInterface.textinfo.CameraKey.pos.x = iTipX;
		BattleInterface.textinfo.CameraKey.align = KEY_ALIGN;
		BattleInterface.textinfo.CameraKey.pos.y = IKeyLines[iPosY];
		BattleInterface.textinfo.CameraKey.text = GetKeyCodeImg("Sea_CameraSwitch");
		BattleInterface.textinfo.CameraKey.refreshable = true;

		BattleInterface.textinfo.CameraTip.font = "interface_normal";
		BattleInterface.textinfo.CameraTip.scale = fTextScale;
		BattleInterface.textinfo.CameraTip.color = itextColor;
		BattleInterface.textinfo.CameraTip.pos.x = iTipXText;
		BattleInterface.textinfo.CameraTip.align = "left";
		BattleInterface.textinfo.CameraTip.pos.y = ITxtLines[iPosY];
		if (Crosshair.OutsideCamera == true)
			BattleInterface.textinfo.CameraTip.text = LanguageConvertString(iControlsFile, "Sea_CameraSwitchShort") +": " +LanguageConvertString(iControlsFile, "Sea_CameraDeck");
		else
			BattleInterface.textinfo.CameraTip.text = LanguageConvertString(iControlsFile, "Sea_CameraSwitchShort") +": " +LanguageConvertString(iControlsFile, "Sea_CameraShip");
		BattleInterface.textinfo.CameraTip.refreshable = true;
//переключить камеру <--
//труба -->
		iPosY = 5 - iShiftLine;
		BattleInterface.textinfo.SpyFad.font = "INFO_FADER_LS";
		BattleInterface.textinfo.SpyFad.scale = fFaderScale;
		BattleInterface.textinfo.SpyFad.color = ifaderColor;
		BattleInterface.textinfo.SpyFad.pos.x = iTipFadX;
		BattleInterface.textinfo.SpyFad.align = "centr";
		BattleInterface.textinfo.SpyFad.pos.y = IFadLines[iPosY];
		BattleInterface.textinfo.SpyFad.text = " ";
		BattleInterface.textinfo.SpyFad.refreshable = true;

		BattleInterface.textinfo.SpyKey.font = "keyboard_symbol";
		BattleInterface.textinfo.SpyKey.scale = fTipKeyScale;
		BattleInterface.textinfo.SpyKey.color = iTipKeyColor;
		BattleInterface.textinfo.SpyKey.pos.x = iTipX;
		BattleInterface.textinfo.SpyKey.align = KEY_ALIGN;
		BattleInterface.textinfo.SpyKey.pos.y = IKeyLines[iPosY];
		BattleInterface.textinfo.SpyKey.text = " ";
		BattleInterface.textinfo.SpyKey.refreshable = true;

		BattleInterface.textinfo.SpyTip.font = "interface_normal";
		BattleInterface.textinfo.SpyTip.scale = fTextScale;
		BattleInterface.textinfo.SpyTip.color = itextColor;
		BattleInterface.textinfo.SpyTip.pos.x = iTipXText;
		BattleInterface.textinfo.SpyTip.align = "left";
		BattleInterface.textinfo.SpyTip.pos.y = ITxtLines[iPosY];
		BattleInterface.textinfo.SpyTip.text = " ";
		BattleInterface.textinfo.SpyTip.refreshable = true;

		RefreshCameraTip();
//труба <--
	}
}

void EraseFastKeyTip()
{
    BI_ShowFastKeyTip("Nothing");
	DelEventHandler("EraseFastKeyTip", "EraseFastKeyTip");
}

void BI_ShowFastKeyTip(string sAction)
{
	ref rChr;
	string sTemp = "";
	switch (sAction)
	{
		case "Nothing":
			ILogAndActions.ActiveActions.text1.text = "";
			ILogAndActions.ActiveActions.text2.text = "";
			ILogAndActions.ActiveActions.Moor.Text = "";
			ILogAndActions.ActiveActions.Board.Text = "";
			ILogAndActions.ActiveActions.Map.Text = "";
			ILogAndActions.ActiveActions.Reload.Text = "";
			ILogAndActions.ActiveActions.Nothing.Text = "";
			BattleInterface.textinfo.FastKey.text = " ";
			return;
		break;
		case "map":
			SetEventHandler("EraseFastKeyTip", "EraseFastKeyTip", 1);
			if (iShowTips >= CONTROL_TIPS_EXTEND)
			{
				ILogAndActions.ActiveActions.text2.text = LanguageConvertString(iCommandsFile, "sea_GlobalMap");
				PostEvent("EraseFastKeyTip", 30000);
			}
			else PostEvent("EraseFastKeyTip", 10);
		break;
		case "moor":
			ILogAndActions.ActiveActions.text2.text = LanguageConvertString(iCommandsFile, "sea_Moor");
			sTemp = BattleInterface.textinfo.Location.text;
		break;
		case "board":
			ILogAndActions.ActiveActions.text2.text = LanguageConvertString(iCommandsFile, "sea_Abordage");
			rChr = GetCharacter(iAbordageShipEnemyCharacter);
			sTemp = rChr.Ship.Name;
		break;
		case "LandTroops":
			ILogAndActions.ActiveActions.text2.text = LanguageConvertString(iCommandsFile, "sea_LandTroops");
			sTemp = TEV.FortLandTroops;
		break;
		case "reload": //Обмен товарами
			ILogAndActions.ActiveActions.text2.text = LanguageConvertString(iCommandsFile, "sea_Reload");
		   	rChr = GetCharacter(bi_nReloadTarget);
		   	sTemp = rChr.Ship.Name;
		break;
	}
	if (sTemp != "")
		ILogAndActions.ActiveActions.text2.text = ILogAndActions.ActiveActions.text2.text +" (" +sTemp +")";

	Log_SetActiveAction_SetText(GetKeyByControl(FindControlFromActionName(sAction)), ILogAndActions.ActiveActions.text2.text);
}

void BI_SetSelectTip() //при активации и перемещении по командному меню
{
	if (iShowTips < CONTROL_TIPS_ALL) return;

    string sAddress = GetEventData();
    int iTipChrIdx = GetEventData();
    int iCurLine = 0;
    string sTemp = "";
	bCommMenu = true;

	BattleInterface.textinfo.HorFad.text = "1";
	BattleInterface.textinfo.HorTip.text = LanguageConvertString(iControlsFile, "Order_Select");
	BattleInterface.textinfo.HorKey.text = GetKeyCodeImg("BICommandsLeft") +GetKeyCodeImg("BICommandsRight") +objControlsState.key_codes.VK_MWHEEL_UP.img;

	BattleInterface.textinfo.HorTip.pos.y = ITxtLines[iCurLine];
	BattleInterface.textinfo.HorKey.pos.y = IKeyLines[iCurLine];
	BattleInterface.textinfo.HorFad.pos.y = IFadLines[iCurLine];
	iCurLine++;

	if (GetCompanionQuantity(pchar) > 1)
	{
		BattleInterface.textinfo.VerFad.text = "1";
		BattleInterface.textinfo.VerTip.text = LanguageConvertString(iControlsFile, "Ship_Select");
		BattleInterface.textinfo.VerKey.text = GetKeyCodeImg("BICommandsUp") +GetKeyCodeImg("BICommandsDown");

		BattleInterface.textinfo.VerTip.pos.y = ITxtLines[iCurLine];
		BattleInterface.textinfo.VerKey.pos.y = IKeyLines[iCurLine];
		BattleInterface.textinfo.VerFad.pos.y = IFadLines[iCurLine];
		iCurLine++;
	}

	if (sAddress == LanguageConvertString(iCommandsFile, "sea_Map"))
	{
		sAddress = LanguageConvertString(iCommandsFile, "sea_GlobalMap");
	}
	else if (iTipChrIdx != -1 && sAddress != LanguageConvertString(iCommandsFile, "sea_Cancel"))
	{
		if (iTipChrIdx != sti(pchar.index))
		{
			sTemp = LanguageConvertString(iCommandsFile, "sea_CCommand") +": " +LowerFirst(sCommandTip);
		    if (sCommandTip != "") sTemp = sTemp +" ";
		    else sAddress = LowerFirst(sAddress);
		}
		else if (iTipChrIdx == sti(pchar.index) && sCommandTip != "")
			sTemp = sCommandTip +": ";
	}

	BattleInterface.textinfo.EnterFad.text = "1";
	BattleInterface.textinfo.EnterTip.text = sTemp +sAddress;
	BattleInterface.textinfo.EnterTip.pos.y = ITxtLines[iCurLine];
	BattleInterface.textinfo.EnterKey.pos.y = IKeyLines[iCurLine];
	BattleInterface.textinfo.EnterFad.pos.y = IFadLines[iCurLine];

	BattleInterface.textinfo.SalvoFad.text = " ";
	BattleInterface.textinfo.SalvoKey.text = " ";
	BattleInterface.textinfo.SalvoTip.text = " ";

	BattleInterface.textinfo.CameraFad.text = " ";
	BattleInterface.textinfo.CameraKey.text = " ";
	BattleInterface.textinfo.CameraTip.text = " ";

	BattleInterface.textinfo.SpyFad.text = " ";
	BattleInterface.textinfo.SpyKey.text = " ";
	BattleInterface.textinfo.SpyTip.text = " ";

	BattleInterface.textinfo.CabinFad.text = " ";
	BattleInterface.textinfo.CabinKey.text = " ";
	BattleInterface.textinfo.CabinTip.text = " ";

	BattleInterface.textinfo.FireZoneFad.text = " ";
	BattleInterface.textinfo.FireZoneKey.text = " ";
	BattleInterface.textinfo.FireZoneTip.text = " ";
}

void BI_DeactivateSelectTip() //при выходе из командного меню
{
	if (iShowTips < CONTROL_TIPS_ALL) return;

	bCommMenu = false;
	sCommandTip = "";

	BattleInterface.textinfo.CabinFad.text = "1";
	BattleInterface.textinfo.CabinKey.text = GetKeyCodeImg("hk_cabin");
	BattleInterface.textinfo.CabinTip.text = LanguageConvertString(iControlsFile, "hk_cabin");

	BattleInterface.textinfo.FireZoneFad.text = "1";
	BattleInterface.textinfo.FireZoneKey.text = GetKeyCodeImg("FireZoneKey");
	BattleInterface.textinfo.FireZoneTip.text = "";
	RefreshFireZoneTip();

	// убираем тип для каюты - сдвигаем остальные строки
	int iShiftLine = 1;
	if (!GetGlobalTutor())
	{
		iShiftLine = 0;
	}

	BattleInterface.textinfo.EnterFad.text = "1";
	BattleInterface.textinfo.EnterTip.text = LanguageConvertString(iControlsFile, "BICommandsActivate");
	BattleInterface.textinfo.EnterTip.pos.y = ITxtLines[2-iShiftLine]; //в столбике подсказок они отображаются только в режиме Все
	BattleInterface.textinfo.EnterKey.pos.y = IKeyLines[2-iShiftLine];
	BattleInterface.textinfo.EnterFad.pos.y = IFadLines[2-iShiftLine];

	BattleInterface.textinfo.CameraFad.text = "1";
	BattleInterface.textinfo.CameraKey.text = GetKeyCodeImg("Sea_CameraSwitch");
	if (Crosshair.OutsideCamera == "1")
		BattleInterface.textinfo.CameraTip.text = LanguageConvertString(iControlsFile, "Sea_CameraSwitchShort") +": " +LanguageConvertString(iControlsFile, "Sea_CameraDeck");
	else
	{
			BattleInterface.textinfo.CameraTip.text = LanguageConvertString(iControlsFile, "Sea_CameraSwitchShort") +": " +LanguageConvertString(iControlsFile, "Sea_CameraShip");

			BattleInterface.textinfo.SpyFad.text = "1";
			BattleInterface.textinfo.SpyKey.text = objControlsState.key_codes.vk_control.img;
			//BattleInterface.textinfo.SpyKey.text = GetKeyCodeImg("Telescope");
			BattleInterface.textinfo.SpyTip.text = LanguageConvertString(iControlsFile, "Telescope");
	}

	BattleInterface.textinfo.HorFad.text = " ";
	BattleInterface.textinfo.HorTip.text = " ";
	BattleInterface.textinfo.HorKey.text = " ";

	BattleInterface.textinfo.VerFad.text = " ";
	BattleInterface.textinfo.VerTip.text = " ";
	BattleInterface.textinfo.VerKey.text = " ";
}

void RefreshCameraTip()
{
    if (iShowTips < CONTROL_TIPS_ALL) return;

	if (Crosshair.OutsideCamera == "1")
	{
		BattleInterface.textinfo.CameraTip.text = LanguageConvertString(iControlsFile, "Sea_CameraSwitchShort") +": " +LanguageConvertString(iControlsFile, "Sea_CameraDeck");
		BattleInterface.textinfo.SpyFad.text = " ";
		BattleInterface.textinfo.SpyKey.text = " ";
		BattleInterface.textinfo.SpyTip.text = " ";
	}
	else
	{
		BattleInterface.textinfo.CameraFad.text = "1";
		BattleInterface.textinfo.CameraTip.text = LanguageConvertString(iControlsFile, "Sea_CameraSwitchShort") +": " +LanguageConvertString(iControlsFile, "Sea_CameraShip");
		BattleInterface.textinfo.SpyFad.text = "1";
		BattleInterface.textinfo.SpyKey.text = objControlsState.key_codes.vk_control.img;
		//BattleInterface.textinfo.SpyKey.text = GetKeyCodeImg("Telescope");
		BattleInterface.textinfo.SpyTip.text = LanguageConvertString(iControlsFile, "Telescope");
	}
}

void RefreshFireZoneTip()
{
	if (iShowTips < CONTROL_TIPS_ALL) return;

	if (!bCannonsRangeShow)
		BattleInterface.textinfo.FirezoneTip.text = LanguageConvertString(iControlsFile, "FireZoneKey");
	else
		BattleInterface.textinfo.FirezoneTip.text = LanguageConvertString(iControlsFile, "FireZoneKeyHide");
}

// boal 10.06.05
// KZ > ref 10.03.24
//	 DICE GAME
int scx, scy, spx, spy, sgxy, ssxy, smxy;
int move_i, dir_i, dir_i_start, x_rand, y_rand, r_delta;
bool openExit;
int	 money_i, moneyOp_i;
string money_s, sDiceTemp;

ref npchar;

int iRate, iMoneyP, iMoneyN, iChest, iExpRate;
int bStartGame;
int iHeroLose, iHeroWin;
int iTurnGame; // count for time

object	DiceState;

bool  bLockClick;
bool  bSetRandDice; // жухло компа

// > кон уже подсчитан: ставки разошлись, штрафовать за выход больше не за что
bool  bRoundDone;

string ResultStr;

// > кэш, чтобы не дёргать движок вхолостую
int  iPackX1, iPackY1, iPackX2, iPackY2;
int  iDiceLineX, iDiceLineY;

string sHeroDiceShown[6];
string sCompDiceShown[6];
bool   bDiceOnTable;
int    iClearMoneyP, iClearMoneyN;

string sTxtInfo, sTxtBtn1, sTxtTime, sTxtSessTime;
string sTxtWins, sTxtLoses, sTxtWinMoney, sTxtLoseMoney, sTxtDiff;

int    iSessMinCached;
string sSessTimeCached;

// > Перелёт выигранных монет (ставки со стола и банк) на портрет победителя.
float fCoinFlyTime;    // > сколько летит одна монета, сек
float fCoinFlyDelay;   // > на сколько позже стартует следующая монета, сек
float fCoinFlyMax;     // > под этот потолок ужимается разбег стартов, сек
float fCoinFlyEndSize; // > размер монеты у портрета, доля от исходного
int   iCoinFlyBank;    // > сколько монет вылетает из банка (0 - выключить)

float fCoinFlyStep;    // > фактический сдвиг стартов, ужат под потолок

bool  bCoinFly;         // > анимация идёт
int   iCoinFlyNum;      // > всего монет в полёте
int   iCoinFlyBankN;    // > из них монет банка (летят первыми)
int   iCoinFlyP;        // > монет ГГ (следом за банком)
int   iCoinFlyN;        // > монет соперника (последними)
int   iCoinFlyDone;     // > монеты левее этого номера уже долетели
float fCoinFlyTimer;    // > накопленное реальное время, сек
float fCoinFlyTotal;    // > сколько всего длится анимация, сек
int   iCoinFlyToX, iCoinFlyToY;  // > центр портрета победителя
int   iCoinFlySize;     // > сторона монеты на старте
int   iCoinFlyX, iCoinFlyY;      // > результат CoinFlySetStart

// > Портрет победителя "подрастает" от каждой прилетевшей монеты, а когда прилетела последняя - так же плавно возвращается к исходному размеру.
float fPortrGrowStep;  // > на сколько подрастает портрет от одной монеты (доля)
float fPortrGrowMax;   // > потолок увеличения (пример: 0.30 = не больше чем +30%)
float fPortrGrowUp;    // > сек на разгон от исходного размера до потолка
float fPortrGrowBack;  // > сек на возврат от потолка к исходному размеру

// > Мигание портрета при прилёте монеты.
bool  bPortrBlink;     // > мигание включено
float fPortrBlinkTime; // > сколько длится одна вспышка, сек
float fPortrBlinkHold; // > доля вспышки на удержании яркости (0 - сразу гаснет, 0.9 - почти вся)
int   iPortrBlinkR, iPortrBlinkG, iPortrBlinkB; // > цвет на пике вспышки
int   iPortrRestR,  iPortrRestG,  iPortrRestB;  // > цвет портрета в покое

int   iPortr1X1, iPortr1Y1, iPortr1X2, iPortr1Y2; // > исходный прямоугольник ICON_1
int   iPortr2X1, iPortr2Y1, iPortr2X2, iPortr2Y2; // > исходный прямоугольник ICON_2

string sPortrNode;      // > какой портрет сейчас растёт, "" - никакой
int   iPortrX1, iPortrY1, iPortrX2, iPortrY2; // > его исходный прямоугольник
float fPortrCur;        // > текущее увеличение, доля
float fPortrTarget;     // > к какому увеличению идём
bool  bPortrBack;       // > последняя монета прилетела, идёт возврат
float fPortrBlinkLeft;  // > сколько ещё гореть вспышке, сек
int   iPortrShownW, iPortrShownH; // > последний отправленный движку прирост
int   iPortrColorShown; // > последний отправленный цвет

// > неизменные за сеанс строки из common.ini
string sLngWin, sLngLose, sLngMoneyWin, sLngMoneyLose, sLngTimePassed, sLngDifference;
string sLngEndTurn, sLngBets, sLngNext_4, sLngNoMore;
string sLngTurn_1, sLngTurn_4, sLngTurn_5, sLngTurn_6, sLngTurn_7, sLngTurn_8, sLngTurn_9;
string sLngTurnNPC_4, sLngTurnNPC_5, sLngTurnNPC_6;
string sLngDiceState[9];

//> сброс всех кэшей сегмента (лезут в глобал)
void ResetInterfaceCache()
{
	int i;
	for (i = 1; i <= 5; i++)
	{
		sHeroDiceShown[i] = "";
		sCompDiceShown[i] = "";
	}
	bDiceOnTable = false;
	iClearMoneyP = 0;
	iClearMoneyN = 0;

	sTxtInfo      = "";
	sTxtBtn1      = "";
	sTxtTime      = "";
	sTxtSessTime  = "";
	sTxtWins      = "";
	sTxtLoses     = "";
	sTxtWinMoney  = "";
	sTxtLoseMoney = "";
	sTxtDiff      = "";

	iSessMinCached  = -1;
	sSessTimeCached = "";

	// > прошлый сеанс мог закрыться в момент перелёта монет
	bCoinFly     = false;
	iCoinFlyNum  = 0;
	iCoinFlyDone = 0;
}

// > один и тот же текст движку второй раз не шлём
void SetInfoText(string sText)
{
	if (sTxtInfo == sText) return;
	sTxtInfo = sText;
	SetFormatedText("INFO_TEXT", sText);
}

void SetBtnText(string sText)
{
	if (sTxtBtn1 == sText) return;
	sTxtBtn1 = sText;
	SetFormatedText("B_TEXT_1", sText);
}

// > обе "часовые" строки разом, с отсевом повторов
void SetTimeTexts()
{
	string sTmp = GetQuestBookData();
	if (sTxtTime != sTmp)
	{
		sTxtTime = sTmp;
		SetFormatedText("TIME_TEXT", sTmp);
	}
	sTmp = GetSessionTime();
	if (sTxtSessTime != sTmp)
	{
		sTxtSessTime = sTmp;
		SetFormatedText("STATS_TIME_TEXT", sTmp);
	}
}

void InitInterface(string iniName)
{
	DeleteAttribute(pchar, "StartGameSession");
	DeleteAttribute(&TEV, "Gambling");
	TEV.Gambling.LoseMoney = "0";
	TEV.Gambling.WinMoney = "0";

	if (!CheckAttribute(&TEV, "Stats.Gambling.Dice.LoseMoney"))
		TEV.Stats.Gambling.Dice.LoseMoney = "0";

	if (!CheckAttribute(&TEV, "Stats.Gambling.Dice.WinMoney"))
		TEV.Stats.Gambling.Dice.WinMoney = "0";

	GameInterface.title = "";

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("My_eventMoveImg","MoveImg",0);
	SetEventHandler("My_eStartGame","StartGame",0);
	SetEventHandler("My_eContinueGame","ContinueGame",0);
	SetEventHandler("My_eNewNextGame","NewNextGame",0);
	SetEventHandler("My_eCompTurn","CompTurn",0);
	SetEventHandler("My_eCheckGame","CheckGame",0);
	/*
	gold, silver   - 100x100
	screen: -40..680 x -30..510	 (720x540)
	cup: 219x178
	dice: 92x84
	таблица (в прорядке убывания значимости)
	1) Покер - 5 одинаковых
	2) Стрит Бол.стрит - 2,3,4,5,6 Мал.стрит - 1,2,3,4,5
	3) Каре - 4 одинаковых
	4) Фул - 3 + 2
	5) триада - 3 одинаковых
	6) две пары 2 + 2
	7) одна пара 2- одинаковых
	8) ничего нет
	*/
	r_delta = makeint(Bring2Range(20.0, 5.0, 5.0, 20.0, GetRDeltaTime() * 1.0));
	sgxy = 50;
	ssxy = 70;

	scx = 82;
	scy = 77;

	spx = 274;
	spy = 222;

	x_rand = -1;
	y_rand = -1;

	openExit = false;  // можно ли прервать игру
	bRoundDone = false;

	pchar = GetMainCharacter();

	iRate  = sti(pchar.GenQuest.Dice.iRate); // ставки золотых

	npchar = GetCharacter(sti(pchar.GenQuest.Dice.npcharIdx));

	iMoneyP = sti(pchar.Money); // mitrokosta реальные деньги смотрим только в начале и в конце
	iMoneyN = sti(npchar.Money);

	int i, iPlayMode;
	if (iRate < 200) iPlayMode = 1;
	else if (iRate < 500) iPlayMode = 2;
		else if (iRate < 2000) iPlayMode = 3;
			else iPlayMode = 4;

	switch (iPlayMode)
	{
		case 1 :
			money_s = "silver";
			iExpRate = 1;
		break;

		case 2 :
			money_s = "silver";
			SetNewPicture("SCROLLPICT", "interfaces\card_sukno1.tga");
			iExpRate = 2;
		break;

		case 3 :
			money_s = "silver";
			SetNewPicture("SCROLLPICT", "interfaces\card_sukno.tga");
			iExpRate = 4;
		break;

		case 4 :
			money_s = "gold";
			SetNewPicture("SCROLLPICT", "interfaces\card_sukno.tga");
			iExpRate = 8;
		break;
	}
	if (money_s == "gold")
	{
		smxy = sgxy;
	}
	else
	{
		smxy = ssxy;
	}

	// > Скорость перелёта монет. fCoinFlyTime = 0.0 выключает анимацию.
	fCoinFlyTime    = 0.55;
	fCoinFlyDelay   = 0.04;
	fCoinFlyMax     = 1.60;
	fCoinFlyEndSize = 0.55;
	iCoinFlyBank    = 0;

	if (CheckAttribute(pchar, "GenQuest.Dice.CoinFlyTime"))  fCoinFlyTime  = stf(pchar.GenQuest.Dice.CoinFlyTime);
	if (CheckAttribute(pchar, "GenQuest.Dice.CoinFlyDelay")) fCoinFlyDelay = stf(pchar.GenQuest.Dice.CoinFlyDelay);
	if (CheckAttribute(pchar, "GenQuest.Dice.CoinFlyMax"))   fCoinFlyMax   = stf(pchar.GenQuest.Dice.CoinFlyMax);
	if (CheckAttribute(pchar, "GenQuest.Dice.CoinFlyBank"))  iCoinFlyBank  = sti(pchar.GenQuest.Dice.CoinFlyBank);
	if (CheckAttribute(pchar, "GenQuest.Dice.CoinFlyEndSize")) fCoinFlyEndSize = stf(pchar.GenQuest.Dice.CoinFlyEndSize);

	if (fCoinFlyDelay < 0.0) fCoinFlyDelay = 0.0;
	if (fCoinFlyEndSize < 0.05) fCoinFlyEndSize = 0.05;
	if (iCoinFlyBank < 0)  iCoinFlyBank = 0;  // > атрибут задаёт кто угодно,
	if (iCoinFlyBank > 12) iCoinFlyBank = 12; // > а картинки заводим мы

	// > Портрет победителя: рост от каждой монеты и возврат после последней.
	// > fPortrGrowMax = 0.0 выключает рост, bPortrBlink = false выключает мигание.
	fPortrGrowStep  = 0.09;
	fPortrGrowMax   = 0.35;
	fPortrGrowUp    = 0.18;
	fPortrGrowBack  = 0.35;

	bPortrBlink     = true;
	fPortrBlinkTime = 0.22;
	fPortrBlinkHold = 0.25;
	iPortrBlinkR = 255; iPortrBlinkG = 245; iPortrBlinkB = 170; // > тёплая вспышка
	// > цвет покоя
	iPortrRestR  = 128; iPortrRestG  = 128; iPortrRestB  = 128;

	if (CheckAttribute(pchar, "GenQuest.Dice.PortrGrowStep"))  fPortrGrowStep  = stf(pchar.GenQuest.Dice.PortrGrowStep);
	if (CheckAttribute(pchar, "GenQuest.Dice.PortrGrowMax"))   fPortrGrowMax   = stf(pchar.GenQuest.Dice.PortrGrowMax);
	if (CheckAttribute(pchar, "GenQuest.Dice.PortrGrowUp"))    fPortrGrowUp    = stf(pchar.GenQuest.Dice.PortrGrowUp);
	if (CheckAttribute(pchar, "GenQuest.Dice.PortrGrowBack"))  fPortrGrowBack  = stf(pchar.GenQuest.Dice.PortrGrowBack);
	if (CheckAttribute(pchar, "GenQuest.Dice.PortrBlink"))     bPortrBlink     = sti(pchar.GenQuest.Dice.PortrBlink);
	if (CheckAttribute(pchar, "GenQuest.Dice.PortrBlinkTime")) fPortrBlinkTime = stf(pchar.GenQuest.Dice.PortrBlinkTime);
	if (CheckAttribute(pchar, "GenQuest.Dice.PortrBlinkHold")) fPortrBlinkHold = stf(pchar.GenQuest.Dice.PortrBlinkHold);

	// > на эти числа делим
	if (fPortrGrowStep  < 0.0)  fPortrGrowStep  = 0.0;
	if (fPortrGrowMax   < 0.0)  fPortrGrowMax   = 0.0;
	if (fPortrGrowUp    < 0.01) fPortrGrowUp    = 0.01;
	if (fPortrGrowBack  < 0.01) fPortrGrowBack  = 0.01;
	if (fPortrBlinkTime < 0.01) fPortrBlinkTime = 0.01;
	if (fPortrBlinkHold < 0.0)  fPortrBlinkHold = 0.0;
	if (fPortrBlinkHold > 0.9)  fPortrBlinkHold = 0.9;

	sPortrNode = "";

	// > B_PACK всегда неподвижен, запоминаем его прямоугольник один раз, дальше MoveImg берёт его из кэша
	ResetInterfaceCache();
	GetNodePosition("B_PACK", &iPackX1, &iPackY1, &iPackX2, &iPackY2);

	// > исходные размеры портретов запоминаем один раз, пока их никто не растягивал
	GetNodePosition("ICON_1", &iPortr1X1, &iPortr1Y1, &iPortr1X2, &iPortr1Y2);
	GetNodePosition("ICON_2", &iPortr2X1, &iPortr2Y1, &iPortr2X2, &iPortr2Y2);

	int x1, y1, x2, y2;
	GetNodePosition("B_HeroDice1", &x1, &y1, &x2, &y2);
	iDiceLineX = x1 - 16;
	iDiceLineY = y1 - 11;

	for(i = 1; i<=5; i++)
	{
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "HeroDice" + i, 100);
		SetNodeUsing("HeroDice" + i, false);
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "CompDice" + i, 100);
		SetNodeUsing("CompDice" + i, false);
		// > ряды кубиков стоят на месте всю игру, расставим их один раз
		SetNodePosition("HeroDice" + i, iDiceLineX + 80 * (i - 1), iDiceLineY, iDiceLineX + 80 * (i - 1) + scx, iDiceLineY + scy);
		SetNodePosition("CompDice" + i, iDiceLineX + 80 * (i - 1), iDiceLineY - 444, iDiceLineX + 80 * (i - 1) + scx, iDiceLineY - 444 + scy);
	}

	XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "DiceCup", 100);
	SetNewGroupPicture("DiceCup", "DICE", "cup");

	x1 = iPackX1 - 91;
	y1 = iPackY1 - 38;
	x2 = x1 + spx;
	y2 = y1 + spy;
	SetNodePosition("DiceCup", x1, y1, x2, y2);

	CreateImage("GOLD","GOLD","GOLD", 482,444,524,486);

	string sFace = "interfaces\PORTRAITS\64\face_";

	if (CheckAttribute(npchar, "faceId") && sti(npchar.faceId) > 1)
	{
		string sPic = sFace + npchar.faceId + ".tga";

		if (XI_CheckFolder("RESOURCE\\Textures\\" + sPic + ".tx") || XI_CheckFolder("RESOURCE\\Textures\\" + sPic))
			SetNewPicture("ICON_1", sPic);
	}

	SetNewPicture("ICON_2", sFace + pchar.faceId + ".tga");

	CreateString(true,"Money","",FONT_NORMAL,COLOR_MONEY,613,508,SCRIPT_ALIGN_CENTER,1.1);
	CreateString(true,"MoneyInChest","",FONT_NORMAL,COLOR_MONEY,615,452,SCRIPT_ALIGN_CENTER,1.3);

	if (rand(1))
	{
		dir_i  = -1;  // кто ходит - комп
	}
	else
	{
		dir_i  = 1;	 // кто ходит - ГГ
	}
	dir_i_start = dir_i; // запомним кто начал

	CreateString(true,"Wins", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 269, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Loses", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 284, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"MoneyWin", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 299, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"MoneyLose", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 314, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"MoneyDiff", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 329, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"TimePassed", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 344, SCRIPT_ALIGN_LEFT,1.0);

	CreateString(true,"Beta_MoneyN", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 530, 250, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Beta_DiceN", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 80, 170, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Beta_DiceP", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 80, 465, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Beta_TXT", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 80, 555, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Beta_WinLose", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 530, 555, SCRIPT_ALIGN_LEFT,1.0);
	iHeroLose = 0;
	iHeroWin  = 0;
	iTurnGame = 0;

	// > все неизменные строки читаем из common.ini один раз и более не дёргаем движок линейными поисками
	sLngWin        = XI_ConvertString("BoalGameWin");
	sLngLose       = XI_ConvertString("BoalGameLose");
	sLngMoneyWin   = XI_ConvertString("BoalGameMoneyWin");
	sLngMoneyLose  = XI_ConvertString("BoalGameMoneyLose");
	sLngTimePassed = XI_ConvertString("BoalGameTimePassed");
	sLngDifference = XI_ConvertString("BoalGameDifference");
	sLngEndTurn    = XI_ConvertString("BoalGameEndTurn");
	sLngBets       = XI_ConvertString("BoalGameBets");
	sLngNext_4     = XI_ConvertString("BoalGameCheckGame_4");
	sLngNoMore     = XI_ConvertString("BoalGameCheckGame_5");
	sLngTurn_1     = XI_ConvertString("BoalGameTurn_1");
	sLngTurn_4     = XI_ConvertString("BoalGameTurn_4");
	sLngTurn_5     = XI_ConvertString("BoalGameTurn_5");
	sLngTurn_6     = XI_ConvertString("BoalGameTurn_6");
	sLngTurn_7     = XI_ConvertString("BoalGameTurn_7");
	sLngTurn_8     = XI_ConvertString("BoalGameTurn_8");
	sLngTurn_9     = XI_ConvertString("BoalGameTurn_9");
	sLngTurnNPC_4  = XI_ConvertString("BoalGameTurnNPC_4");
	sLngTurnNPC_5  = XI_ConvertString("BoalGameTurnNPC_5");
	sLngTurnNPC_6  = XI_ConvertString("BoalGameTurnNPC_6");

	for (i = 1; i <= 8; i++)
	{
		sLngDiceState[i] = XI_ConvertString("BoalGameDiceState_" + i);
	}

	// новая игра
	SaveCurrentQuestDateParam("StartGameSession");
	NewGameBegin(true);
	SetTimeTexts();
	SetFormatedText("STATS_TEXT", XI_ConvertString("Statistic"));
}

void ProcessBreakExit()
{
	Exit();
}

void ProcessCancelExit()
{
	Exit();
}

void Exit()
{
	// > монеты могли остаться в полёте - снимаем обработчик кадра до выгрузки сегмента
	CoinFlyStop();

	if (!openExit && !bRoundDone) // > fix: штраф - это плата за брошенный недоигранный кон
	{
		PlaySound("uplata");
		TEV.Gambling.LoseMoney = sti(TEV.Gambling.LoseMoney) + (money_i * iRate);
	}

	AddMoneyToCharacter(pchar, iMoneyP - sti(pchar.Money)); // mitrokosta раздача денег теперь в конце
	AddMoneyToCharacter(npchar, iMoneyN - sti(npchar.Money));

	TEV.Stats.Gambling.Dice.LoseMoney = sti(TEV.Stats.Gambling.Dice.LoseMoney) + sti(TEV.Gambling.LoseMoney);
	TEV.Stats.Gambling.Dice.WinMoney = sti(TEV.Stats.Gambling.Dice.WinMoney) + sti(TEV.Gambling.WinMoney);

	Log_Clear();

	TEV.Gambling.Diff.Plus = "";
	TEV.Gambling.DiffAll.Plus = "";

	string sDiceWin = XI_ConvertString("BoalGameDiceWin");
	string sTotal;

	if (GetOfficersPerkUsing(pchar, "HawkEye", true))
	{
		sTotal = GetStrSmallRegister(XI_ConvertString("Total"));

		Log_Info(sDiceWin + ": " + iHeroWin + " (" + sTotal + " " + (Statistic_AddValue(Pchar, "GameDice_Win", 0) + iHeroWin) + ")");
		Log_Info(sLngLose + ": " + iHeroLose + " (" + sTotal + " " + (Statistic_AddValue(Pchar, "GameDice_Lose", 0) + iHeroLose) + ")");
		Log_Info(sLngMoneyWin + ": " + TEV.Gambling.WinMoney + " (" + sTotal + " " + TEV.Stats.Gambling.Dice.WinMoney + ")");
		Log_Info(sLngMoneyLose + ": " + TEV.Gambling.LoseMoney + " (" + sTotal + " " + TEV.Stats.Gambling.Dice.LoseMoney + ")");

		TEV.Gambling.Diff = makeint(TEV.Gambling.WinMoney) - makeint(TEV.Gambling.LoseMoney);
		TEV.Gambling.DiffAll = makeint(TEV.Stats.Gambling.Dice.WinMoney) - makeint(TEV.Stats.Gambling.Dice.LoseMoney);

		if (sti(TEV.Gambling.Diff) > 0)
			TEV.Gambling.Diff.Plus = "+";

		if (sti(TEV.Gambling.DiffAll) > 0)
			TEV.Gambling.DiffAll.Plus = "+";

		Log_Info(sLngDifference + ": " + TEV.Gambling.Diff.Plus + FindMoneyString(sti(TEV.Gambling.Diff)) + " (" + sTotal + " " + TEV.Gambling.DiffAll.Plus + FindMoneyString(sti(TEV.Gambling.DiffAll))  + ")");
	}
	else
	{
		Log_Info(sDiceWin + ": " + iHeroWin);
		Log_Info(sLngLose + ": " + iHeroLose);
		Log_Info(sLngMoneyWin + ": " + TEV.Gambling.WinMoney);
		Log_Info(sLngMoneyLose + ": " + TEV.Gambling.LoseMoney);
		TEV.Gambling.Diff = makeint(sti(TEV.Gambling.WinMoney) - sti(TEV.Gambling.LoseMoney));

		if (sti(TEV.Gambling.Diff) > 0)
			TEV.Gambling.Diff.Plus = "+";

		Log_Info(sLngDifference + ": " + TEV.Gambling.Diff.Plus + FindMoneyString(sti(TEV.Gambling.Diff)));
	}

	DeleteAttribute(&TEV, "Gambling");

	DelEventHandler("InterfaceBreak","ProcessBreakExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("My_eventMoveImg","MoveImg");
	DelEventHandler("My_eStartGame","StartGame");
	DelEventHandler("My_eContinueGame","ContinueGame");
	DelEventHandler("My_eNewNextGame","NewNextGame");
	DelEventHandler("My_eCompTurn","CompTurn");
	DelEventHandler("My_eCheckGame","CheckGame");
	DelEventHandler("frame","CoinFlyFrame"); // > ещё раз, на случай сбитого флага

	if (sti(pchar.GenQuest.Dice.SitType) == true)
	{
		DoQuestCheckDelay("exit_sit", 0.6);
	}
	interfaceResultCommand = RC_INTERFACE_SALARY_EXIT;

	Statistic_AddValue(Pchar, "GameDice_Win", iHeroWin);
	AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*4*iHeroWin);
	AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*2*iHeroLose);
	Statistic_AddValue(Pchar, "GameDice_Lose", iHeroLose);
	NPChar.Quest.HeroLose = (iHeroWin < iHeroLose); //navy -- в итоге проиграл или выйграл. (не по деньгам.)

	// > убрано: между ними сейчас ничего не выполняется
	//bQuestCheckProcessFreeze = true;
	//bQuestCheckProcessFreeze = false;
	RefreshLandTime();
	EndCancelInterface(true);
	DeleteAttribute(pchar, "StartGameSession");
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();

	if (bLockClick) return;

	switch(nodName)
	{
		case "B_PACK":
			if(comName=="activate" || comName=="click")
			{
				if (openExit == true)
				{	// ещё одна игра
					dir_i = -dir_i_start;
					dir_i_start = dir_i;
					ClearDiceOnTable();
					NewGameBegin(true);
				}
				else
				{
					// ГГ перебрасывает часть кубиков
					// ГГ брасает кубики первый раз кубиков
					if (dir_i == 1 && CheckCupForDice())
					{
						SetDiceTip("");
						UpdateTime();
						bLockClick = true;
						move_i = 0;
						PlaySound("DiceMix");
						PostEvent("My_eventMoveImg", 100);
					}
					else
					{
						PlaySound("knock");
					}
				}
			}
		break;

		case "B_ICON_1":
			if(comName=="activate" || comName=="click")
			{
				if (dir_i == 1 && CheckCupForDice())  // выбрана часть кубиков
				{
					PlaySound("knock");
					break;
				}
				if (dir_i_start == 1 && bStartGame == 2)  // пропуск хода
				{
					CheckGame();
					break;
				}
				if (dir_i_start == -1 && bStartGame == 3)  // пропуск хода
				{
					CheckGame();
					break;
				}
				PlaySound("knock");
			}
		break;

		case "B_ICON_2":
			if(comName=="activate" || comName=="click")
			{
				//PlaySound("knock");
			}
		break;

		case "B_HeroDice1":
			if(comName=="activate" || comName=="click")
			{
				ClickHeroDice(1);
			}
		break;

		case "B_HeroDice2":
			if(comName=="activate" || comName=="click")
			{
				ClickHeroDice(2);
			}
		break;
		case "B_HeroDice3":
			if(comName=="activate" || comName=="click")
			{
				ClickHeroDice(3);
			}
		break;
		case "B_HeroDice4":
			if(comName=="activate" || comName=="click")
			{
				ClickHeroDice(4);
			}
		break;
		case "B_HeroDice5":
			if(comName=="activate" || comName=="click")
			{
				ClickHeroDice(5);
			}
		break;
	}
}

void MoveImg()
{
	float t, scale;
	int x, y, x1, y1, x2, y2;

	x1 = iPackX1 - 231;
	y1 = iPackY1 - 38;
	x2 = x1 - 274;
	y2 = iPackY2 + 37;

	move_i++;
	if (move_i < 50)
	{
		if(move_i == 1)
		{
			x_rand = x1 - 150 + rand(x2 - x1 + 300);
			y_rand = y1 - 150 + rand(y2 - y1 + 300);
		}
		t = move_i / 50.0;
		x = makeint((1.0 - t) * (1.0 - t) * x1 + 2.0 * (1.0 - t) * t * x_rand + t * t * x2);
		y = makeint((1.0 - t) * (1.0 - t) * y1 + 2.0 * (1.0 - t) * t * y_rand + t * t * y2);
		scale = 1.0 + 0.1 * 5.0 * t * (1.0 - t); // плавное увеличение кружки к середине, уменьшение после середины
		SetNodePosition("DiceCup", 140 + x, y, 140 + x + makeint(spx * scale), y + makeint(spy * scale));
		PostEvent("My_eventMoveImg", r_delta);
	}
	else
	{
		if(move_i == 50)
		{
			x_rand = x1 + x2 - x_rand;
			y_rand = y1 + y2 - y_rand;
		}

		t = (move_i - 50) / 50.0;
		x = makeint((1.0 - t) * (1.0 - t) * x2 + 2.0 * (1.0 - t) * t * x_rand + t * t * x1);
		y = makeint((1.0 - t) * (1.0 - t) * y2 + 2.0 * (1.0 - t) * t * y_rand + t * t * y1);
		if (move_i <= 100)
		{
			scale = 1.0 + 0.1 * 5.0 * t * (1.0 - t); // плавное увеличение кружки к середине, уменьшение после середины
			SetNodePosition("DiceCup", 140 + x, y, 140 + x + makeint(spx * scale), y + makeint(spy * scale));

			if (move_i == 100) // все - собрать кубики в линеку
			{
				PostEvent("My_eventMoveImg", 200);
			}
			else
			{
				PostEvent("My_eventMoveImg", r_delta);
			}
		}
		// сброс
		if (move_i == 60)
		{
			PlaySound("interface\dice_end.wav");
			if (bSetRandDice)
			{
				SetDiceForTableRand(); // случайно, 2й ход компа будем жухлить!!!
			}
			else
			{
				bSetRandDice = true;
			}
			PutDiceOnTable();
		}
		// все - собрать кубики в линеку
		if (move_i == 101)
		{
			SetLineAfterDeck();
		}
	}
}

void PutNextCoin()
{
	if (money_i > 27) return;
	CreateImage("Money_"+money_i,"CARDS",money_s, 530+money_i*3, 310-money_i*3, 530+money_i*3 + smxy, 310-money_i*3 + smxy);
	if (money_i >= iClearMoneyP) iClearMoneyP = money_i + 1;
}
void PutNextCoinOp()
{
	if (moneyOp_i > 27) return;
	CreateImage("Money_"+(28+moneyOp_i),"CARDS",money_s, 630+moneyOp_i*3, 310-moneyOp_i*3, 630+moneyOp_i*3 + smxy, 310-moneyOp_i*3 + smxy);
	if (moneyOp_i >= iClearMoneyN) iClearMoneyN = moneyOp_i + 1;
}

// ------------------------------------------------------------------
// > Перелёт выигранных монет на портрет победителя
// ------------------------------------------------------------------

// > Переставить уже созданную картинку, не трогая её текстуру
void MoveImage(string AttrName, int left, int top, int right, int bottom)
{
	SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_PLACE_IMAGE, AttrName, true, left, top, right, bottom);
}

// > Откуда стартует монета номер i: сначала монеты банка, за ними ставки ГГ, последними ставки соперника.
void CoinFlySetStart(int iCoin)
{
	int k = iCoin;

	// > Банк летит первым (анимация монет банка есть только при iCoinFlyBank > 0).
	if (k < iCoinFlyBankN)
	{	// > картинка банка GOLD, монеты вылетают из неё горкой
		iCoinFlyX = 503 - iCoinFlySize / 2 - 16 + k * 9;
		iCoinFlyY = 465 - iCoinFlySize / 2 - 12 + k * 7;
		return;
	}
	k = k - iCoinFlyBankN;
	if (k < iCoinFlyP)
	{
		iCoinFlyX = 530 + k * 3;
		iCoinFlyY = 310 - k * 3;
		return;
	}
	k = k - iCoinFlyP;
	iCoinFlyX = 630 + k * 3;
	iCoinFlyY = 310 - k * 3;
}

// > Летящие монеты - отдельные картинки, оригиналы со стола к этому моменту уже сняты.
// > Поэтому новый кон спокойно пересоздаёт свои Money_*, даже если предыдущие монеты ещё в воздухе.
void CoinFlyClear()
{
	int i;
	for (i = iCoinFlyNum - 1; i >= 0; i--)
	{
		CreateImage("CoinFly_" + i, "", "", 0, 0, 0, 0);
	}
	iCoinFlyNum = 0;
}

// > Прямая установка цвета картинки-узла. У CXI_PICTURE это команда 4; команда 5 (SetPictureBlind) для тонкой настройки не годится - движок читает в ней только флаг, а цвета и времена берёт из ini.
void SetPictureColor(string nodeName, int color)
{
	SendMessage(&GameInterface, "lsll", MSG_INTERFACE_MSG_TO_NODE, nodeName, 4, color);
}

// > Цвет портрета на текущей яркости вспышки: 1.0 - пик, 0.0 - покой.
void CoinFlySetPortraitColor(float fBright)
{
	int iR = makeint(iPortrRestR + (iPortrBlinkR - iPortrRestR) * fBright);
	int iG = makeint(iPortrRestG + (iPortrBlinkG - iPortrRestG) * fBright);
	int iB = makeint(iPortrRestB + (iPortrBlinkB - iPortrRestB) * fBright);

	int iCol = argb(255, iR, iG, iB);
	if (iCol == iPortrColorShown) return; // > тот же цвет второй раз движку не шлём
	iPortrColorShown = iCol;
	SetPictureColor(sPortrNode, iCol);
}

// > Вернуть портрет в исходный вид. Зовётся и при обрыве анимации, поэтому портрет не может остаться раздутым или подсвеченным.
void CoinFlyPortraitReset()
{
	if (sPortrNode == "") return;

	if (iPortrShownW != 0 || iPortrShownH != 0)
		SetNodePosition(sPortrNode, iPortrX1, iPortrY1, iPortrX2, iPortrY2);

	if (iPortrColorShown != 0)
		SetPictureColor(sPortrNode, argb(255, iPortrRestR, iPortrRestG, iPortrRestB));

	sPortrNode       = "";
	fPortrCur        = 0.0;
	fPortrTarget     = 0.0;
	bPortrBack       = false;
	fPortrBlinkLeft  = 0.0;
	iPortrShownW     = 0;
	iPortrShownH     = 0;
	iPortrColorShown = 0;
}

// > Прилетела очередная монета: подрастить портрет и мигнуть.
void CoinFlyPortraitHit()
{
	if (sPortrNode == "") return;

	fPortrTarget = fPortrTarget + fPortrGrowStep;
	if (fPortrTarget > fPortrGrowMax) fPortrTarget = fPortrGrowMax;

	if (bPortrBlink) fPortrBlinkLeft = fPortrBlinkTime;
}

// > Кадр жизни портрета: размер ползёт к цели с постоянной скоростью (поэтому не зависит от FPS), вспышка гаснет по своему таймеру.
void CoinFlyPortraitFrame(float fDelta)
{
	if (sPortrNode == "") return;

	float fRate;
	if (bPortrBack)
		fRate = fPortrGrowMax / fPortrGrowBack;
	else
		fRate = fPortrGrowMax / fPortrGrowUp;

	float fStep = fRate * fDelta;

	if (fPortrCur < fPortrTarget)
	{
		fPortrCur = fPortrCur + fStep;
		if (fPortrCur > fPortrTarget) fPortrCur = fPortrTarget;
	}
	else
	{
		if (fPortrCur > fPortrTarget)
		{
			fPortrCur = fPortrCur - fStep;
			if (fPortrCur < fPortrTarget) fPortrCur = fPortrTarget;
		}
	}

	// > растём симметрично от центра, поэтому прибавка делится пополам
	int iDW = makeint((iPortrX2 - iPortrX1) * fPortrCur * 0.5);
	int iDH = makeint((iPortrY2 - iPortrY1) * fPortrCur * 0.5);

	if (iDW != iPortrShownW || iDH != iPortrShownH)
	{
		iPortrShownW = iDW;
		iPortrShownH = iDH;
		SetNodePosition(sPortrNode, iPortrX1 - iDW, iPortrY1 - iDH, iPortrX2 + iDW, iPortrY2 + iDH);
	}

	if (!bPortrBlink) return;
	if (fPortrBlinkLeft <= 0.0) return;

	fPortrBlinkLeft = fPortrBlinkLeft - fDelta;
	if (fPortrBlinkLeft < 0.0) fPortrBlinkLeft = 0.0;

	float fBright = fPortrBlinkLeft / fPortrBlinkTime;
	if (fBright > 1.0) fBright = 1.0;

	// > начало вспышки держим на полной яркости, остаток плавно гасим
	if (fBright > 1.0 - fPortrBlinkHold)
		fBright = 1.0;
	else
		fBright = fBright / (1.0 - fPortrBlinkHold);

	CoinFlySetPortraitColor(fBright);
}

void CoinFlyStop()
{
	if (bCoinFly)
	{
		bCoinFly = false;
		DelEventHandler("frame", "CoinFlyFrame");
	}
	CoinFlyPortraitReset();
	CoinFlyClear();
}

// > who: 1 - выиграл ГГ (нижний портрет), -1 - соперник (верхний).
// > При ничьей банк переходит в следующий кон, монеты никуда не летят.
void CoinFlyStart(int who)
{
	CoinFlyStop(); // > хвост прошлой анимации не должен мешаться с новой

	if (who == 0) return;
	if (fCoinFlyTime <= 0.0) return; // > выключено настройкой

	int nP = iClearMoneyP; // > ровно столько картинок монет реально создано
	int nN = iClearMoneyN;
	int nBank = iCoinFlyBank;

	if (nBank < 0 || iChest <= 0) nBank = 0;

	int iTotal = nP + nN + nBank;
	if (iTotal < 1) return;

	iCoinFlyBankN = nBank;
	iCoinFlyP     = nP;
	iCoinFlyN     = nN;
	iCoinFlyNum   = iTotal;
	iCoinFlyDone  = 0;
	iCoinFlySize  = smxy;

	// > числа взяты из boal_dice.ini: картинки и узлы ini живут в одних и тех же координатах, отступ канвы движок добавляет сам.
	// > ICON_2 - ГГ, ICON_1 - соперник.
	iCoinFlyToX = 729;
	if (who == 1)
	{	// > портрет ГГ
		iCoinFlyToY = 519;
		sPortrNode  = "ICON_2";
		iPortrX1 = iPortr2X1; iPortrY1 = iPortr2Y1;
		iPortrX2 = iPortr2X2; iPortrY2 = iPortr2Y2;
		iPortrBlinkR = 255; iPortrBlinkG = 245; iPortrBlinkB = 170; // > тёплая вспышка
	}
	else
	{	// > портрет соперника
		iCoinFlyToY = 411;
		sPortrNode  = "ICON_1";
		iPortrX1 = iPortr1X1; iPortrY1 = iPortr1Y1;
		iPortrX2 = iPortr1X2; iPortrY2 = iPortr1Y2;
		iPortrBlinkR = 255; iPortrBlinkG = 196; iPortrBlinkB = 196; // > светло-красная вспышка
	}
	fPortrCur        = 0.0;
	fPortrTarget     = 0.0;
	bPortrBack       = false;
	fPortrBlinkLeft  = 0.0;
	iPortrShownW     = 0;
	iPortrShownH     = 0;
	iPortrColorShown = 0;

	int i;
	for (i = 0; i < iTotal; i++)
	{
		CoinFlySetStart(i);
		CreateImage("CoinFly_" + i, "CARDS", money_s, iCoinFlyX, iCoinFlyY, iCoinFlyX + iCoinFlySize, iCoinFlyY + iCoinFlySize);
	}
	// > оригиналы убираем, дальше стол чистить уже нечего
	for (i = nP - 1; i >= 0; i--)
	{
		CreateImage("Money_" + i, "", "", 0, 0, 0, 0);
	}
	for (i = nN - 1; i >= 0; i--)
	{
		CreateImage("Money_" + (28 + i), "", "", 0, 0, 0, 0);
	}
	iClearMoneyP = 0;
	iClearMoneyN = 0;

	// > при полном столе монет много, поэтому сдвиг стартов ужимаем под потолок: анимация не растягивается, но настройку игрока при этом не портим
	fCoinFlyStep = fCoinFlyDelay;
	if (iTotal > 1 && fCoinFlyTime + fCoinFlyStep * (iTotal - 1) > fCoinFlyMax)
	{
		fCoinFlyStep = (fCoinFlyMax - fCoinFlyTime) / (iTotal - 1);
		if (fCoinFlyStep < 0.0) fCoinFlyStep = 0.0;
	}

	fCoinFlyTimer = 0.0;
	fCoinFlyTotal = fCoinFlyTime + fCoinFlyStep * (iTotal - 1);
	bCoinFly = true;
	SetEventHandler("frame", "CoinFlyFrame", 0);
	PlaySound("Took_item");
}

// > Один кадр перелёта. Время берём реальное, поэтому, например, на 30 и на 144 FPS монеты летят одинаково долго (меняется только плавность картинки).
void CoinFlyFrame()
{
	if (!bCoinFly) return;

	float fDelta = GetRealDeltaTime();
	fCoinFlyTimer = fCoinFlyTimer + fDelta;

	int   i, x, y, w;
	float t, s, fcx, fcy;

	for (i = iCoinFlyDone; i < iCoinFlyNum; i++)
	{
		t = (fCoinFlyTimer - fCoinFlyStep * i) / fCoinFlyTime;
		if (t <= 0.0) break; // > монеты правее ещё не тронулись

		if (t >= 1.0 && i == iCoinFlyDone)
		{	// > долетевшую монету убираем сразу: она уже "вошла" в портрет.
			// > Заодно список картинок не приходится обходить из-за неё каждый кадр.
			CreateImage("CoinFly_" + i, "", "", 0, 0, 0, 0);
			iCoinFlyDone++;
			PlaySound("interface\uplata_001.wav");
			CoinFlyPortraitHit(); // > портрет подрос и мигнул
			continue;
		}
		if (t > 1.0) t = 1.0;

		s = t * t * (3.0 - 2.0 * t); // > мягкий разгон и торможение

		CoinFlySetStart(i);
		// > ведём центр монеты, чтобы она села ровно на портрет, как ни уменьшалась
		fcx = iCoinFlyX + iCoinFlySize * 0.5;
		fcy = iCoinFlyY + iCoinFlySize * 0.5;
		fcx = fcx + (iCoinFlyToX - fcx) * s;
		fcy = fcy + (iCoinFlyToY - fcy) * s - 40.0 * 4.0 * t * (1.0 - t); // > лёгкая дуга

		w = makeint(iCoinFlySize * (1.0 - (1.0 - fCoinFlyEndSize) * s));
		x = makeint(fcx - w * 0.5);
		y = makeint(fcy - w * 0.5);
		MoveImage("CoinFly_" + i, x, y, x + w, y + w);
	}

	if (iCoinFlyDone >= iCoinFlyNum && !bPortrBack)
	{	// > прилетела последняя монета: портрет пошёл обратно к исходному размеру
		bPortrBack   = true;
		fPortrTarget = 0.0;

		// > показываем пополнившийся кошелёк и пустой кон.
		// > iChest не трогаем - его, как и раньше, обнулит RedrawDeck.
		GameInterface.strings.Money        = MakeMoneyShow(iMoneyP, MONEY_SIGN, MONEY_DELIVER);
		GameInterface.strings.MoneyInChest = MakeMoneyShow(0, MONEY_SIGN, MONEY_DELIVER);
		PlaySound("interface\button3.wav");
	}

	CoinFlyPortraitFrame(fDelta);

	// > обработчик живёт, пока портрет не сядет обратно и не догорит вспышка
	if (bPortrBack && fPortrCur <= 0.0 && fPortrBlinkLeft <= 0.0)
	{
		CoinFlyStop();
	}
}

void RedrawDeck(bool _newGame, bool _clearDice)
{
	int i;
	if (_newGame)
	{
		// > fix: чистим ровно те монетки, которые в прошлом коне действительно клались на стол
		for (i = iClearMoneyP - 1; i >= 0; i--)
		{
			CreateImage("Money_" + i ,"", "", 0, 0, 0, 0);
		}
		for (i = iClearMoneyN - 1; i >= 0; i--)
		{
			CreateImage("Money_" + (28 + i) ,"", "", 0, 0, 0, 0);
		}
		iClearMoneyP = 0;
		iClearMoneyN = 0;

		money_i = 0; // индекс монетки
		moneyOp_i = 0;
		iChest = 0; // на кону
		bRoundDone = false; // > ставки обнулились вместе с money_i, штраф снова осмыслен
	}
	// место под кубики
	if (_clearDice)
	{
		for (i = 1; i <= 5; i++)
		{
			SetNodeUsing("HeroDice" + i, false);
			SetNodeUsing("CompDice" + i, false);
		}
	}

	ShowMoney();
	BetaInfo();
}

void BetaInfo()
{
	if (bBettaTestMode)
	{
		GameInterface.strings.Beta_MoneyN = "Beta_MoneyN " + MakeMoneyShow(iMoneyN, MONEY_SIGN,MONEY_DELIVER);
		GameInterface.strings.Beta_DiceN  = "Beta_DiceN Type: " + DiceState.Comp.Result.Type + " Rate1: " + DiceState.Comp.Result.Rate1 + " Rate2: " +DiceState.Comp.Result.Rate2;
		GameInterface.strings.Beta_DiceP  = "Beta_DiceP Type: " + DiceState.Hero.Result.Type + " Rate1: " + DiceState.Hero.Result.Rate1 + " Rate2: " +DiceState.Hero.Result.Rate2;
		GameInterface.strings.Beta_TXT	  = "dir_i_start " + dir_i_start + " dir_i " + dir_i + " Position " + bStartGame;
		GameInterface.strings.Beta_WinLose = "Beta Win " + (Statistic_AddValue(Pchar, "GameDice_Win", 0) + iHeroWin)+ " Lose " + (Statistic_AddValue(Pchar, "GameDice_Lose", 0) + iHeroLose)+ " Turn " + iTurnGame;
		if (CheckAttribute(NPchar, "Quest.DiceCheats")) GameInterface.strings.Beta_WinLose = GameInterface.strings.Beta_WinLose + " Cheats " + NPchar.Quest.DiceCheats;
	}

	int iDiff = sti(TEV.Gambling.WinMoney) - sti(TEV.Gambling.LoseMoney);
	string sDiff = "";

	if (iDiff > 0)
		sDiff = "+";
	else
	{
		if (iDiff < 0)
			sDiff = "-";
	}

	iDiff = abs(iDiff);

	// > fix: снова бессмысленные поиски по common.ini на каждый вызов
	GameInterface.strings.Wins			= sLngWin + " ";
	GameInterface.strings.Loses			= sLngLose + " ";
	GameInterface.strings.MoneyWin		= sLngMoneyWin + " ";
	GameInterface.strings.MoneyLose		= sLngMoneyLose + " ";
	GameInterface.strings.TimePassed	= sLngTimePassed + " ";
	GameInterface.strings.MoneyDiff		= sLngDifference;

	// > одинаковый текст второй раз не отправляем
	string sTmp = "" + sDiff + iDiff;
	if (sTxtDiff != sTmp)
	{
		sTxtDiff = sTmp;
		SetFormatedText("STATS_DIFF_TEXT", sTmp);
	}
	sTmp = "" + iHeroWin;
	if (sTxtWins != sTmp)
	{
		sTxtWins = sTmp;
		SetFormatedText("STATS_WINS_TEXT", sTmp);
	}
	sTmp = "" + iHeroLose;
	if (sTxtLoses != sTmp)
	{
		sTxtLoses = sTmp;
		SetFormatedText("STATS_LOSES_TEXT", sTmp);
	}
	sTmp = "" + TEV.Gambling.WinMoney;
	if (sTxtWinMoney != sTmp)
	{
		sTxtWinMoney = sTmp;
		SetFormatedText("STATS_WINMONEY_TEXT", sTmp);
	}
	sTmp = "" + TEV.Gambling.LoseMoney;
	if (sTxtLoseMoney != sTmp)
	{
		sTxtLoseMoney = sTmp;
		SetFormatedText("STATS_LOSEMONEY_TEXT", sTmp);
	}
	sTmp = GetSessionTime();
	if (sTxtSessTime != sTmp)
	{
		sTxtSessTime = sTmp;
		SetFormatedText("STATS_TIME_TEXT", sTmp);
	}
}

// сдать карту
void StartGame()
{
	int i;
	move_i = 0;
	openExit = false;

	PlaySound("Took_item");
	SetBtnText("");

	if (dir_i == -1) // комп первый
	{
		UpdateTime();
		PlaySound("DiceMix");
		SetInfoText(sLngTurn_5);
		PostEvent("My_eventMoveImg", 100);
	}
	else
	{
		SetInfoText(sLngTurn_6 + GetLangSexPhrase("ый", "ая") +". " + sLngTurn_4);
		bLockClick = false;
		SetDiceTip("action");
	}
	// оба ставят
	for (i=0; i<5; i++)
	{
		PutNextCoin();
		money_i++;
		iMoneyP = iMoneyP - iRate;
	}
	for (i=0; i<5; i++)
	{
		PutNextCoinOp();
		moneyOp_i++;
		iMoneyN = iMoneyN - iRate;
	}
	iChest += 10*iRate;
	PlaySound("Took_item");
	ShowMoney();
}

void ShowMoney()
{
	GameInterface.strings.Money		   = MakeMoneyShow(iMoneyP,MONEY_SIGN,MONEY_DELIVER);
	GameInterface.strings.MoneyInChest = MakeMoneyShow(iChest,MONEY_SIGN,MONEY_DELIVER);
}

void NewGameBegin(bool _newGame)
{
	iTurnGame++;
	InitDiceState();
	RedrawDeck(_newGame, true); // новая игра
	bStartGame = 0;
	SetDiceTip("");
	SetDiceTip("action");
	if (_newGame)
	{
		SetInfoText(XI_ConvertString("BoalGameStart") + " "+NewStr()+sLngBets);
	}
	else
	{
		SetInfoText(XI_ConvertString("BoalGameContinue") + " "+NewStr()+sLngBets);
	}
	bSetRandDice = true;
	PostEvent("My_eStartGame", 1000);
	bLockClick = true;
	openExit = false;
	BetaInfo();
	WaitDate("", 0, 0, 0, 0, 1 + (rand(4)));
	SetTimeTexts();
}
// деньги в карман
void EndGameCount(int who)
{
	//openExit = true;
	if (who == 1) // ГГ
	{
		iMoneyP += iChest;
		TEV.Gambling.WinMoney = sti(TEV.Gambling.WinMoney) + (iChest - (money_i * iRate));
		bRoundDone = true; // > ставки разошлись
	}
	else if (who == -1)
	{
		iMoneyN += iChest;
		TEV.Gambling.LoseMoney = sti(TEV.Gambling.LoseMoney) + (iChest - (moneyOp_i * iRate));
		bRoundDone = true; // > ставки разошлись
	}
	else if (who == 0)// ничья
	{
		// > банк остаётся на кону, bRoundDone не ставим: брошенный кон всё ещё штрафуется
	}
	// > единственная точка, через которую проходят все концы партии
	CoinFlyStart(who);
}

// проверить деньги для след игры
bool CheckNextGame()
{
	bool ret = true;
	if (iRate*6 > iMoneyN) ret = false;
	if (iRate*6 > iMoneyP) ret = false;

	return ret;
}

void PutDiceOnTable()
{
	int ix, iy;
	if (DiceState.Desk.d1.Mix == true)
	{
		ix = rand(40);
		iy = rand(40);
		CreateImage("Dice1","DICE","dice_"+DiceState.Desk.d1+"_" + rand(2), 160+ix, 180+iy, 160 +ix + scx, 180 +iy+ scy);
	}
	if (DiceState.Desk.d2.Mix == true)
	{
		ix = rand(40);
		iy = rand(40);
		CreateImage("Dice2","DICE","dice_"+DiceState.Desk.d2+"_" + rand(2), 280+ix, 150+iy, 280 +ix + scx, 150 +iy+ scy);
	}
	if (DiceState.Desk.d3.Mix == true)
	{
		ix = rand(40);
		iy = rand(40);
		CreateImage("Dice3","DICE","dice_"+DiceState.Desk.d3+"_" + rand(2), 150+ix, 280+iy, 150 +ix + scx, 280 +iy+ scy);
	}
	if (DiceState.Desk.d4.Mix == true)
	{
		ix = rand(40);
		iy = rand(40);
		CreateImage("Dice4","DICE","dice_"+DiceState.Desk.d4+"_" + rand(2), 260+ix, 310+iy, 260 +ix + scx, 310 +iy+ scy);
	}
	if (DiceState.Desk.d5.Mix == true)
	{
		ix = rand(40);
		iy = rand(40);
		CreateImage("Dice5","DICE","dice_"+DiceState.Desk.d5+"_" + rand(2), 350+ix, 260+iy, 350 +ix + scx, 260 +iy+ scy);
	}
	bDiceOnTable = true; // > на столе что-то лежит, чистить есть что
}

void ClearDiceOnTable()
{
	if (!bDiceOnTable) return;
	for (int i = 1; i <= 5; i++)
	{
		CreateImage("Dice" + i, "", "", 0, 0, 0, 0);
	}
	bDiceOnTable = false;
}

void InitDiceState()
{
	int i = 1;
	string _s = "";

	DeleteAttribute(&DiceState, "");

	for (; i <= 5; i++)
	{
		_s = "d" + i;
		DiceState.Desk.(_s) = "";
		DiceState.Desk.(_s).Mix = true;
		DiceState.Hero.(_s) = "";
		DiceState.Hero.(_s).Mix = false;
		DiceState.Comp.(_s) = "";
		DiceState.Comp.(_s).Mix = false;
	}

	DiceState.Hero.Result.Type	= ""; // тип комбинации
	DiceState.Hero.Result.Rate1 = ""; // значение старшей пары
	DiceState.Hero.Result.Rate2 = "";

	DiceState.Comp.Result.Type	= ""; // тип комбинации
	DiceState.Comp.Result.Rate1 = ""; // значение старшей пары
	DiceState.Comp.Result.Rate2 = ""; // значение младшей пары (если есть, для сравнения фул и две пары, когда старшие равны)
	DiceState.Comp.Result.d1 = ""; // 1-6 колво фишек
}

void ClickHeroDice(int d)
{
	if (bLockClick) return;
	if (bStartGame < 2 || bStartGame > 3)  return;
	if (iMoneyP >= iRate)
	{
		sDiceTemp = "d"+d;
		if (CheckAttribute(&DiceState, "LockDice." + sDiceTemp) && sti(DiceState.LockDice.(sDiceTemp)) > 0)
			return;

		SetBtnText("");
		SetNodeUsing("HeroDice" + d, false);
		DiceState.Hero.(sDiceTemp).Mix = true;
		DiceState.Desk.(sDiceTemp).Mix = true;
		PutNextCoin();
		money_i++;
		iMoneyP = iMoneyP - iRate;
		iChest += iRate;
		PlaySound("Took_item");
		ShowMoney();
		DiceState.LockDice.(sDiceTemp) = 1;
		SetDiceTip("action");
	}
	else
	{
		PlaySound("knock");
	}
}

void SetLineAfterDeck()
{
	int i;
	ClearDiceOnTable();

	if (dir_i == -1) // комп первый
	{
		for (i = 1; i<=5; i++)
		{
			sDiceTemp = "d"+i;
			if (DiceState.Desk.(sDiceTemp).Mix == true)
			{
				DiceState.Comp.(sDiceTemp)	   = DiceState.Desk.(sDiceTemp);
				DiceState.Comp.(sDiceTemp).Mix = false;
				if (bStartGame >0 ) DiceState.Desk.(sDiceTemp).Mix = false;

			}
		}
		SortDiceOnHand("Comp");
		RecalcDiceOnHand("Comp");
		RecalcAIDice("Comp");
		PutCompLine();
	}
	else
	{
		for (i = 1; i<=5; i++)
		{
			sDiceTemp = "d"+i;
			if (DiceState.Desk.(sDiceTemp).Mix == true)
			{
				DiceState.Hero.(sDiceTemp)	   = DiceState.Desk.(sDiceTemp);
				DiceState.Hero.(sDiceTemp).Mix = false;
				if (bStartGame >0) DiceState.Desk.(sDiceTemp).Mix = false;
			}
		}
		SortDiceOnHand("Hero");
		RecalcDiceOnHand("Hero");
		RecalcAIDice("Hero");
		PutHeroLine();
	}
	CheckGame();
}

bool CheckGame()
{
	int i;

	if (dir_i == -1) // комп первый
	{
		dir_i = 1;
		bLockClick = false;
		if (bStartGame <1 )// первый заход
		{
			SetInfoText(sLngTurn_1 + " " + sLngTurn_4);
			SetBtnText("");
		}
		else
		{
			SetInfoText(sLngTurn_7);
			SetBtnText(sLngEndTurn);
		}
	}
	else
	{
		dir_i = -1;
		bLockClick = true;
		SetBtnText("");
		if (bStartGame <1 )// первый заход
		{
			UpdateTime();
			SetInfoText(sLngTurn_8);
			move_i = 0;
			PlaySound("DiceMix");
			PostEvent("My_eventMoveImg", 500);
		}
		else
		{
			if (bStartGame <3)
			{
				// решаем ходить ли вообще
				SetInfoText(sLngTurn_9);
				PostEvent("My_eCompTurn", 800);
			}
		}
	}
	bStartGame++;
	SetDiceTip("");
	if (bStartGame > 3)
	{
		SetBtnText("");
		// подвод итога
		openExit = false;
		bLockClick = true;
		if (EndTurnGame())
		{
			PostEvent("My_eNewNextGame", 2000);
		}
		else
		{
			PostEvent("My_eContinueGame", 3500);
		}
	}
	else
	{
		if(dir_i == 1)
			SetDiceTip("action");
	}
	BetaInfo();
	return true;
}

// > картинку грани трогаем только когда на кубике выпало другое число
void PutCompLine()
{
	int i;
	string sPic;

	for (i = 1; i<=5; i++)
	{
		sDiceTemp = "d"+i;
		if (DiceState.Comp.(sDiceTemp).Mix == false)
		{
			SetNodeUsing("CompDice" + i, true);
			sPic = "dice_" + DiceState.Comp.(sDiceTemp) + "_1";
			if (sCompDiceShown[i] != sPic)
			{
				sCompDiceShown[i] = sPic;
				SetNewGroupPicture("CompDice" + i, "DICE", sPic);
			}
		}
	}
}

void PutHeroLine()
{
	int i;
	string sPic;

	for (i = 1; i<=5; i++)
	{
		sDiceTemp = "d"+i;
		if (DiceState.Hero.(sDiceTemp).Mix == false)
		{
			SetNodeUsing("HeroDice" + i, true);
			sPic = "dice_" + DiceState.Hero.(sDiceTemp) + "_1";
			if (sHeroDiceShown[i] != sPic)
			{
				sHeroDiceShown[i] = sPic;
				SetNewGroupPicture("HeroDice" + i, "DICE", sPic);
			}
		}
	}
}

bool CheckCupForDice()
{
	int i;
	for (i = 1; i<=5; i++)
	{
		sDiceTemp = "d"+i;
		if (sti(DiceState.Desk.(sDiceTemp).Mix) == true)
		{
			return true;
		}
	}
	return false;
}

// посчитать комбинацию
void RecalcDiceOnHand(string _whom)
{
	int	   i, k, iOk, vk, iRate1, iRate2;
	bool   ok;

	int dv[6]; 	// > dv[1..5]
	int cnt[7];	// > cnt[0..6]

	for (i = 0; i <= 6; i++)
	{
		cnt[i] = 0;
	}

	for (i = 1; i <= 5; i++)
	{
		sDiceTemp = "d" + i;
		dv[i] = sti(DiceState.(_whom).(sDiceTemp));
		if (dv[i] < 0) dv[i] = 0;  // > грань бывает только 0..6, индекс cnt[] обязан быть валиден
		if (dv[i] > 6) dv[i] = 6;
		cnt[dv[i]] = cnt[dv[i]] + 1;
	}
	// 1) Покер - 5 одинаковых
	ok = true;
	for (i = 2; i<=5; i++)
	{
		if (dv[1] != dv[i])
		{
			ok = false;
			break;
		}
	}
	if (ok)
	{
		DiceState.(_whom).Result.Type  = 1;
		DiceState.(_whom).Result.Rate1 = dv[1];
		DiceState.(_whom).Result.Rate2 = dv[1];
		return;
	}
	// 2) Стрит Бол.стрит - 2,3,4,5,6 Мал.стрит - 1,2,3,4,5
	ok = true;
	for (i = 1; i<=4; i++)
	{
		if (dv[i] != (dv[i+1] - 1))
		{
			ok = false;
			break;
		}
	}
	if (ok)
	{
		DiceState.(_whom).Result.Type  = 2;
		DiceState.(_whom).Result.Rate1 = dv[5];
		DiceState.(_whom).Result.Rate2 = dv[5];
		return;
	}
	// 3) Каре - 4 одинаковых
	for (k = 1; k<=5; k++)
	{
		vk = dv[k];
		iOk = cnt[vk];
		if (iOk >= 4)
		{
			DiceState.(_whom).Result.Type  = 3;
			DiceState.(_whom).Result.Rate1 = vk;
			DiceState.(_whom).Result.Rate2 = vk;
			return;
		}
	}
	// 4) Фул - 3 + 2
	ok = false;
	iRate1 = 0;
	for (k = 1; k<=5; k++)
	{
		vk = dv[k];
		iOk = cnt[vk];
		if (iOk >= 3)
		{
			iRate1 = vk;
			DiceState.(_whom).Result.Rate1 = vk;
			ok = true;
			break;
		}
	}
	if (ok)
	{
		ok = false;
		for (k = 1; k<=5; k++)
		{
			vk = dv[k];
			if (vk == iRate1) continue;
			iOk = cnt[vk];
			if (iOk >= 2)
			{
				DiceState.(_whom).Result.Rate2 = vk;
				ok = true;
				break;
			}
		}
	}
	if (ok)
	{
		DiceState.(_whom).Result.Type  = 4;
		return;
	}
	// 5) триада - 3 одинаковых
	ok = false;
	for (k = 1; k<=5; k++)
	{
		vk = dv[k];
		iOk = cnt[vk];
		if (iOk >= 3)
		{
			DiceState.(_whom).Result.Rate1 = vk;
			ok = true;
			break;
		}
	}
	if (ok)
	{
		DiceState.(_whom).Result.Type  = 5;
		DiceState.(_whom).Result.Rate2 = DiceState.(_whom).Result.Rate1;
		return;
	}
	// 6) две пары 2 + 2
	ok = false;
	iRate2 = 0;

	for (k = 1; k<=5; k++)
	{
		vk = dv[k];
		iOk = cnt[vk];
		if (iOk >= 2)
		{
			iRate2 = vk;
			DiceState.(_whom).Result.Rate2 = vk; // младшая
			ok = true;
			break;
		}
	}
	if (ok)
	{
		ok = false;
		for (k = 1; k<=5; k++)
		{
			vk = dv[k];
			if (vk == iRate2) continue;
			iOk = cnt[vk];
			if (iOk >= 2)
			{
				DiceState.(_whom).Result.Rate1 = vk; // старшая
				ok = true;
				break;
			}
		}
	}
	if (ok)
	{
		DiceState.(_whom).Result.Type  = 6;
		return;
	}
	// 7) одна пара 2- одинаковых
	ok = false;
	for (k = 1; k<=5; k++)
	{
		vk = dv[k];
		iOk = cnt[vk];
		if (iOk >= 2)
		{
			DiceState.(_whom).Result.Rate1 = vk;
			ok = true;
			break;
		}
	}
	if (ok)
	{
		DiceState.(_whom).Result.Type  = 7;
		DiceState.(_whom).Result.Rate2 = DiceState.(_whom).Result.Rate1;
		return;
	}
	// 8) ничего нет
	DiceState.(_whom).Result.Type  = 8;
	DiceState.(_whom).Result.Rate1 = 0;
	DiceState.(_whom).Result.Rate2 = 0;
}
// сортирова по возрастанию, нужно для визуализации и аглоритма вычисления комбинаций
void SortDiceOnHand(string _whom)
{
	int	 j,k,w,m;
	string sTemp;
	/*
	Поиск наименьшего (простой выбор).

  При первом проходе находим наименьший элемент и ставим его на первое место,
потом наименьший из оставшихся...
	*/

	int dv[6];

	for (k = 1; k <= 5; k++)
	{
		sDiceTemp = "d" + k;
		dv[k] = sti(DiceState.(_whom).(sDiceTemp));
	}

	for (k = 1; k <= 4; k++)
	{
		w = dv[k];
		j = k;

		for (m = k+1; m<=5; m++)
		{
			if (dv[m] < w)
			{
				j = m;
				w = dv[m];
			}
		}
		dv[j] = dv[k];
		dv[k] = w;
	}

	for (k = 1; k <= 5; k++)
	{
		sDiceTemp = "d" + k;
		DiceState.(_whom).(sDiceTemp) = dv[k];
	}
}
// сравнение результата
int GetResult()
{
	if (sti(DiceState.Hero.Result.Type) < sti(DiceState.Comp.Result.Type))
	{
		return 1;
	}
	if (sti(DiceState.Hero.Result.Type) > sti(DiceState.Comp.Result.Type))
	{
		return -1;
	}
	if (sti(DiceState.Hero.Result.Rate1) > sti(DiceState.Comp.Result.Rate1))
	{
		return 1;
	}
	if (sti(DiceState.Hero.Result.Rate1) < sti(DiceState.Comp.Result.Rate1))
	{
		return -1;
	}
	if (sti(DiceState.Hero.Result.Rate2) > sti(DiceState.Comp.Result.Rate2))
	{
		return 1;
	}
	if (sti(DiceState.Hero.Result.Rate2) < sti(DiceState.Comp.Result.Rate2))
	{
		return -1;
	}
	return 0; // ничья
}

bool EndTurnGame()
{
	string sTemp;
	int	  ok = 0;
	bool  ret = true;

	ok = GetResult();
	sTemp = UpperFirst(XI_ConvertString("BoalGameOpenCards_3")) + " " + GetTypeName(sti(DiceState.Comp.Result.Type)) + ". " + UpperFirst(XI_ConvertString("BoalGameOpenCards_2")) + " " + GetTypeName(sti(DiceState.Hero.Result.Type)) + ".";
	if (ok == 0)
	{
		sTemp += NewStr() + XI_ConvertString("BoalGameContinue2");
		ret = false;
	}
	else if (ok == -1)
	{
		sTemp += NewStr() + XI_ConvertString("BoalGameOpenCards_5");
		iHeroLose++;
	}
	else if (ok == 1)
	{
		sTemp += NewStr() +	 RandSwear() + " " + XI_ConvertString("BoalGameOpenCards_1")+ GetLangSexPhrase("", "а") +".";
		iHeroWin++;
	}
	EndGameCount(ok);
	ResultStr = sTemp;
	SetInfoText(sTemp);
	return ret;
}

void ContinueGame()
{
	if (CheckNextGame())
	{
		dir_i		= -dir_i_start;
		dir_i_start = dir_i;
		// > выбери, что нравится больше:
		NewGameBegin(true);		// < банк переходит в следующий кон (оригинальная задумка)
		//NewGameBegin(false);	// < банк обнуляется (поставленные деньги возвращаются игрокам)
	}
	else
	{
		if (iRate*6 > iMoneyP)
		{
			ResultStr = XI_ConvertString("BoalGameNoMoney2") + NewStr() + sLngNoMore;
			SetInfoText(ResultStr);
			EndGameCount(-1);
			iHeroLose++;
		}
		else//if (iRate*6 > iMoneyN)
		{
			ResultStr = XI_ConvertString("BoalGameNPCNoMoney2")+ GetLangSexPhrase("", "а") +"!" + NewStr() + sLngNoMore;
			SetInfoText(ResultStr);
			EndGameCount(1);
			iHeroWin++;
		}
		npchar.game_over = true;
		RedrawDeck(true, true);
		openExit = true;
		bLockClick = true;
	}
}

void NewNextGame()
{
	RedrawDeck(true, false);
	openExit = true;
	if (CheckNextGame() && rand(10) < 10) // есть деньги на игру
	{
		ResultStr += NewStr() + sLngNext_4;
		bLockClick = false;
		SetDiceTip("");
		SetDiceTip("restart");
	}
	else
	{
		ResultStr += NewStr() + sLngNoMore;
		npchar.game_over = true;
		bLockClick = true;
	}
	SetInfoText(ResultStr);
}

string GetTypeName(int _type)
{
	if (_type < 1 || _type > 7) return sLngDiceState[1]; // "ничего нет"
	return sLngDiceState[_type + 1];
}

void SetDiceForTableRand()
{
	int i;

	for (i = 1; i<=5; i++)
	{
		sDiceTemp = "d"+i;
		if (sti(DiceState.Desk.(sDiceTemp).Mix) == true)
		{
			DiceState.Desk.(sDiceTemp) = (rand(5)+1);
		}
	}
}
/////////////////////////// AI //////////////////////////////////
void CompTurn()
{
	int i, d, j;
	bool ok, ok2, ok3, b;

	// если комп ходит последним и у него уже больше, то нафиг ему бросать???
	ok = true;
	if (GetResult() == -1 && dir_i_start == 1 && bStartGame == 3) // пропуск хода
	{
		ok = false;
	}
	if (ok)
	{
		if (sti(DiceState.Comp.Result.Type) == 8 && sti(DiceState.Hero.Result.Type) >= 2)
		{
			UpdateTime();
			//перебросим всегда первую фишку (это 100% 1)
			SetInfoText(sLngTurnNPC_4);
			// for test
			ClickCompDice(1);
			move_i = 0;
			PlaySound("DiceMix");
			PostEvent("My_eventMoveImg", 500);
			return;
		}

		// две пары бросаем на фул (один кубик)
		ok3 = (sti(DiceState.Comp.Result.Type) == 6) && (sti(DiceState.Hero.Result.Type) >= 5);
		ok	= (sti(DiceState.Comp.Result.Type) == 6) && (sti(DiceState.Hero.Result.Type) == 4) && (sti(DiceState.Hero.Result.Rate1) <= sti(DiceState.Comp.Result.Rate2));
		ok3 = ok3 || ok;
		// пара бросаем триаду, каре или две пары, а может фулл??
		ok = (sti(DiceState.Comp.Result.Type) == 7) || (sti(DiceState.Comp.Result.Type) == 5);
		ok = ok && (sti(DiceState.Hero.Result.Type) >= 3);
		// каре, но у ГГ больше
		ok2 = (sti(DiceState.Hero.Result.Type) == 3) && (sti(DiceState.Hero.Result.Rate1) > sti(DiceState.Comp.Result.Rate1));
		b	= (sti(DiceState.Hero.Result.Type) == 1) && (sti(DiceState.Hero.Result.Rate1) <= sti(DiceState.Comp.Result.Rate1));
		ok2 = ok2 || b;
		ok2 = (sti(DiceState.Comp.Result.Type) == 3) && ok2;
		if (ok || ok2 || ok3)
		{
			ok = false;
			SetInfoText(sLngTurnNPC_5);
			for (i = 1; i<=6; i++)
			{
				sDiceTemp = "d"+i;
				if (sti(DiceState.Comp.Result.(sDiceTemp)) == 1)
				{
					d = i; // че за фишка
					for (j = 1; j<=5; j++)
					{
						sDiceTemp = "d"+j;
						if (sti(DiceState.Comp.(sDiceTemp).Mix) == true) continue;
						if (sti(DiceState.Comp.(sDiceTemp)) == d)
						{
							ok = ClickCompDice(j) || ok;
							break;
						}
					}
				}
			}

			if (ok)
			{
				UpdateTime();
				move_i = 0;
				PlaySound("DiceMix");
				PostEvent("My_eventMoveImg", 500);
				return;
			}
		}

		// супер жухло!!!!! -->
		if (sti(DiceState.Comp.Result.Type) > sti(DiceState.Hero.Result.Type) && (GetCharacterSkillToOld(pchar, SKILL_FORTUNE) + GetOfficersPerkUsing(pchar, "HawkEye", true)) < rand(12) && rand(4) > 1)
		{
			//navy --> счетчик жульничеств
			if (!CheckAttribute(npchar, "Quest.DiceCheats")) npchar.Quest.DiceCheats = 0;
			npchar.Quest.DiceCheats = sti(npchar.Quest.DiceCheats) + 1;
			//navy <--
			SetInfoText(sLngTurnNPC_5);
			ok = false;
			if (sti(DiceState.Hero.Result.Type) == 1)
			{
				d = sti(DiceState.Hero.Result.Rate1) + 1;
			}
			else
			{
				d = rand(5) + 1;
			}
			if (d > 6) d = 6;

			for (i = 1; i<=5; i++)
			{
				sDiceTemp = "d"+i;
				if (sti(DiceState.Comp.(sDiceTemp)) != d)
				{
					ok = ClickCompDice(i) || ok;
					DiceState.Desk.(sDiceTemp) = d;
				}
			}
			if (ok)
			{
				UpdateTime();
				move_i = 0;
				bSetRandDice = false;
				PlaySound("DiceMix");
				PostEvent("My_eventMoveImg", 500);
				return;
			}
		}
		// жухло!!!!! <--
	}
	// решаем не перебрасывать
	SetInfoText(sLngTurnNPC_6);
	PostEvent("My_eCheckGame", 800);
}

bool ClickCompDice(int d)
{
	sDiceTemp = "d"+d;

	if (iMoneyN >= iRate && sti(DiceState.Comp.(sDiceTemp).Mix) == false)
	{
		SetNodeUsing("CompDice" + d, false);
		DiceState.Comp.(sDiceTemp).Mix = true;
		DiceState.Desk.(sDiceTemp).Mix = true;
		PutNextCoinOp();
		moneyOp_i++;
		iMoneyN = iMoneyN - iRate;
		iChest += iRate;
		PlaySound("Took_item");
		ShowMoney();
		return true;
	}
	return false;
}
// заполнить колвом атрибуты фишек
void RecalcAIDice(string _whom)
{
	int	   i;
	string sTemp;

	for (i = 1; i<=6; i++)
	{
		sDiceTemp = "d"+i;
		DiceState.(_whom).Result.(sDiceTemp) = 0;
	}

	for (i = 1; i<=5; i++)
	{
		sDiceTemp = "d" + i;
		sTemp		= "d" + sti(DiceState.(_whom).(sDiceTemp));
		DiceState.(_whom).Result.(sTemp) = sti(DiceState.(_whom).Result.(sTemp)) + 1;
	}
}

void UpdateTime()
{
	WaitDate("", 0, 0, 0, 0, 1);
	SetTimeTexts();
}

string GetSessionTime()
{
	if (!CheckAttribute(&TEV, "Gambling.Session"))
		TEV.Gambling.Session = "0";

	if (!CheckAttribute(PChar, "StartGameSession"))
		PChar.StartGameSession = "0";

	// > пересчитываем ровно тогда, когда надо
	int iMin = GetQuestPastMinutesParam("StartGameSession");
	if (iMin == iSessMinCached) return sSessTimeCached;
	iSessMinCached = iMin;

	TEV.Gambling.Session = makefloat(iMin / 60.0);
	string sM = makeint(stf("0." + FindStringAfterChar(TEV.Gambling.Session, ".")) * 60);
	string sH = FindStringBeforeChar(TEV.Gambling.Session, ".");

	//if (sti(sH) < 10)
		//sH = "0" + sH;

	if (sti(sM) < 10)
		sM = "0" + sM;

	sSessTimeCached = sH + ":" + sM;
	return sSessTimeCached;
}

/*
restart - новый кон
action - перебросить кубик, сделать бросок, передать ход, подсчитать очки
*/
void SetDiceTip(string tag)
{
	int i;
	string sDice;
	switch(tag)
	{
		case "":	// убираем все подсказки
			for(i = 1; i <= 5; i++)
			{
				SetPictureBlind("HeroDice" + i, false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
			}
			SetPictureBlind("DiceCup", false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
			SetPictureBlind("ICON_1", false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
		break;
		case "restart":
			if(!bLockClick && openExit)	// можно начать новую игру - колода
			{
				SetPictureBlind("DiceCup", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
			}
		break;
		case "action":
			if(!bLockClick && dir_i == 1)
			{
				if(bStartGame >= 2 && bStartGame <= 3 && iMoneyP >= iRate)	// хватает денег на переброс
				{
					for(i = 1; i <= 5; i++)
					{
						sDice = "d" + i;
						if(DiceState.Hero.(sDice).Mix == false)	// есть ли на столе
						{
							SetPictureBlind("HeroDice" + i, true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
						}
					}
				}
				if(CheckCupForDice())	// в стакане что-то есть
				{
					SetPictureBlind("DiceCup", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
					SetPictureBlind("ICON_1", false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
				}
				else
				{
					if(dir_i_start == 1 && bStartGame == 2)	// передача хода
					{
						SetPictureBlind("ICON_1", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
					}
					if(dir_i_start == -1 && bStartGame == 3)	// подсчёт очков
					{
						SetPictureBlind("ICON_1", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
					}
				}
			}
		break;
	}
}

// boal 13.05.05
// KZ > ref 10.03.24
int scx, scy, sgxy, ssxy, smxy;
int move_i, dir_i, dir_i_start, x_rand, y_rand, r_delta;
bool openExit, cardMove;
int  money_i, moneyOp_i;
string money_s;

ref npchar;

int cardsPack[36], cardsP[36], cardsN[36];
int howCard;

int howPchar, howNpchar;
int iRate, iMoneyP, iMoneyN, iChest, iExpRate;
int bStartGame;

int iTurnGame;
int iHeroLose, iHeroWin;

// > кэш, чтобы не дёргать движок вхолостую
int  iPackX1, iPackY1, iPackX2, iPackY2;

string sCardShownP[18];
string sCardShownN[18];
int    iClearMoneyP, iClearMoneyN, iClearCardP, iClearCardN;

string sTxtInfo, sTxtBtn1, sTxtTime, sTxtSessTime;
string sTxtWins, sTxtLoses, sTxtWinMoney, sTxtLoseMoney, sTxtDiff;

int    iSessMinCached;
string sSessTimeCached;

// > Перелёт выигранных монет (ставки со стола и банк) на портрет победителя.
float fCoinFlyTime;    // > сколько летит одна монета, сек
float fCoinFlyDelay;   // > на сколько позже стартует следующая монета, сек
float fCoinFlyMax;     // > под этот потолок ужимается разбег стартов, сек
float fCoinFlyEndSize; // > размер монеты у портрета, доля от исходного
int   iCoinFlyBank;    // > сколько монет вылетает из сундука (0 - выключить)

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

// > Портрет победителя подрастает от каждой прилетевшей монеты, а когда прилетела последняя - так же плавно возвращается к исходному размеру.
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
string sLngGetCard, sLngBet, sLngGetCard2, sLngMoneyBet, sLngEndTurn;
string sLngTurn_1, sLngTurn_2, sLngTurn_3, sLngTurnNPC_1, sLngTurnNPC_2, sLngTurnNPC_3;
string sLngNext_3, sLngNext_4, sLngNoMore;

// > переставить уже созданную картинку, не трогая её текстуру
// > Работает только для картинок, которые в сеансе интерфейса уже прошли через CreateImage
void MoveImage(string AttrName, int left, int top, int right, int bottom)
{
	SendMessage(&GameInterface, "lslllll", MSG_INTERFACE_PLACE_IMAGE, AttrName, true, left, top, right, bottom);
}

// > картинки карт игрока меняем только если они реально другие
void ShowCardP(int i, string sPic, int x, int y)
{
	if (sCardShownP[i] != sPic)
	{
		sCardShownP[i] = sPic;
		CreateImage("PCard" + i, "CARDS", sPic, x, y, x + scx, y + scy);
		return;
	}
	MoveImage("PCard" + i, x, y, x + scx, y + scy);
}

// > то же самое для карт компа
void ShowCardN(int i, string sPic, int x, int y)
{
	if (sCardShownN[i] != sPic)
	{
		sCardShownN[i] = sPic;
		CreateImage("PCard" + (18 + i), "CARDS", sPic, x, y, x + scx, y + scy);
		return;
	}
	MoveImage("PCard" + (18 + i), x, y, x + scx, y + scy);
}

//> сброс всех кэшей сегмента (лезут в глобал)
void ResetInterfaceCache()
{
	int i;
	for (i = 0; i < 18; i++)
	{
		sCardShownP[i] = "";
		sCardShownN[i] = "";
	}
	iClearMoneyP = 0;
	iClearMoneyN = 0;
	iClearCardP  = 0;
	iClearCardN  = 0;

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

void InitInterface(string iniName)
{
	DeleteAttribute(pchar, "StartGameSession");
	DeleteAttribute(&TEV, "Gambling");
	TEV.Gambling.LoseMoney = "0";
	TEV.Gambling.WinMoney = "0";
	
	if (!CheckAttribute(&TEV, "Stats.Gambling.Cards.LoseMoney"))
		TEV.Stats.Gambling.Cards.LoseMoney = "0";
	
	if (!CheckAttribute(&TEV, "Stats.Gambling.Cards.WinMoney"))
		TEV.Stats.Gambling.Cards.WinMoney = "0";
	
    GameInterface.title = "";

    SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessBreakExit",0);
	SetEventHandler("exitCancel","ProcessCancelExit",0);
	SetEventHandler("ievnt_command","ProcessCommandExecute",0);
	SetEventHandler("My_eventMoveImg","MoveImg",0);
	SetEventHandler("My_eStartGame","StartGame",0);
	SetEventHandler("My_eOpenCards","OpenCards",0);
	/*
	hearts_A,diamonds_A,clubs_A,spades_A  - 124x184
	blank - 124x184
	pack -  186x202
	gold, silver   - 100x100
	A - ace
	J - Jack
	Q - Queen
	K - King
	10..6 - other
	
	screen: -40..680 x -30..510  (720x540)
	*/
	
	r_delta = makeint(Bring2Range(20.0, 5.0, 5.0, 20.0, GetRDeltaTime() * 1.0));
	
    sgxy = 50;
    ssxy = 70;
    
    scx = 114;
    scy = 170;
    
    openExit = false;  // можно ли прервать игру
	cardMove = false; // игрок перемещает карту
    
    pchar = GetMainCharacter();
    
    iRate = sti(pchar.GenQuest.Cards.iRate); // ставки золотых
    
    npchar = GetCharacter(sti(pchar.GenQuest.Cards.npcharIdx));

	iMoneyP = sti(pchar.Money); // mitrokosta теперь смотрим на реальные деньги только в начале и в конце
	iMoneyN = sti(npchar.Money);

	int iPlayMode;

	if (iRate < 500) iPlayMode = 1;
	else if (iRate < 1000) iPlayMode = 2;
		else if (iRate < 5000) iPlayMode = 3;
			else iPlayMode = 4;

    switch (iPlayMode)
    {
        case 1 :
            money_s = "silver";
            iExpRate = 1;
        break;
        
        case 2 :
            money_s = "gold";
			SetNewPicture("SCROLLPICT", "interfaces\card_sukno1.tga");
            iExpRate = 2;
        break;
        
        case 3 :
            money_s = "silver";
            SetNewPicture("SCROLLPICT", "interfaces\card_sukno.tga");
            iExpRate = 3;
        break;

        case 4 :
            money_s = "gold";
            SetNewPicture("SCROLLPICT", "interfaces\card_sukno.tga");
            iExpRate = 6;
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

	if (CheckAttribute(pchar, "GenQuest.Cards.CoinFlyTime"))  fCoinFlyTime  = stf(pchar.GenQuest.Cards.CoinFlyTime);
	if (CheckAttribute(pchar, "GenQuest.Cards.CoinFlyDelay")) fCoinFlyDelay = stf(pchar.GenQuest.Cards.CoinFlyDelay);
	if (CheckAttribute(pchar, "GenQuest.Cards.CoinFlyMax"))   fCoinFlyMax   = stf(pchar.GenQuest.Cards.CoinFlyMax);
	if (CheckAttribute(pchar, "GenQuest.Cards.CoinFlyBank"))  iCoinFlyBank  = sti(pchar.GenQuest.Cards.CoinFlyBank);
	if (CheckAttribute(pchar, "GenQuest.Cards.CoinFlyEndSize")) fCoinFlyEndSize = stf(pchar.GenQuest.Cards.CoinFlyEndSize);

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

	if (CheckAttribute(pchar, "GenQuest.Cards.PortrGrowStep"))  fPortrGrowStep  = stf(pchar.GenQuest.Cards.PortrGrowStep);
	if (CheckAttribute(pchar, "GenQuest.Cards.PortrGrowMax"))   fPortrGrowMax   = stf(pchar.GenQuest.Cards.PortrGrowMax);
	if (CheckAttribute(pchar, "GenQuest.Cards.PortrGrowUp"))    fPortrGrowUp    = stf(pchar.GenQuest.Cards.PortrGrowUp);
	if (CheckAttribute(pchar, "GenQuest.Cards.PortrGrowBack"))  fPortrGrowBack  = stf(pchar.GenQuest.Cards.PortrGrowBack);
	if (CheckAttribute(pchar, "GenQuest.Cards.PortrBlink"))     bPortrBlink     = sti(pchar.GenQuest.Cards.PortrBlink);
	if (CheckAttribute(pchar, "GenQuest.Cards.PortrBlinkTime")) fPortrBlinkTime = stf(pchar.GenQuest.Cards.PortrBlinkTime);
	if (CheckAttribute(pchar, "GenQuest.Cards.PortrBlinkHold")) fPortrBlinkHold = stf(pchar.GenQuest.Cards.PortrBlinkHold);

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
	x1 = iPackX1 - 53;
	y1 = iPackY1;
	x2 = iPackX2 + 4;
	y2 = iPackY2 + 15;

	XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "Pack", 100);
	SetNewGroupPicture("Pack", "CARDS", "pack");
	SetNodePosition("Pack", x1, y1, x2, y2);
	XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "Blank", 100);
	SetNewGroupPicture("Blank", "CARDS", "blank");
	SetNodePosition("Blank", x1 - 120, y1 - 5, x1 - 8, y1 + scy);
	SetNodeUsing("Blank", false);

	string sFace = "interfaces\PORTRAITS\64\face_";

	if (CheckAttribute(npchar, "faceId") && sti(npchar.faceId) > 1)
	{
		string sPic = sFace + npchar.faceId + ".tga";

		if (XI_CheckFolder("RESOURCE\\Textures\\" + sPic + ".tx") || XI_CheckFolder("RESOURCE\\Textures\\" + sPic))
			SetNewPicture("ICON_1", sPic);
	}

	SetNewPicture("ICON_2", sFace + pchar.faceId + ".tga");

    SetCardTip("");
    CreateString(true,"Money","",FONT_NORMAL,COLOR_MONEY, 613,348,SCRIPT_ALIGN_CENTER,1.1);
    CreateString(true,"MoneyInChest","",FONT_NORMAL,COLOR_MONEY,615,292,SCRIPT_ALIGN_CENTER,1.3);
    
    if (rand(1))
    {
        dir_i  = -1;  // кто ходит - комп
    }
    else
    {
        dir_i  = 1;  // кто ходит - ГГ
    }
    dir_i_start = dir_i; // запомним кто начал
    
	CreateString(true,"Wins", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 269, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"Loses", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 284, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"MoneyWin", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 299, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"MoneyLose", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 314, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"MoneyDiff", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 329, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"TimePassed", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 785, 344, SCRIPT_ALIGN_LEFT,1.0);
	CreateString(true,"CountCardsPlayer", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 390, 365, SCRIPT_ALIGN_CENTER,1.5);
    CreateString(true,"Beta_P", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 380, 370, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_N", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 380, 210, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_Next", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 230, 310, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_MoneyN", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 530, 210, SCRIPT_ALIGN_LEFT,1.0);
    CreateString(true,"Beta_WinLose", "", "INTERFACE_ULTRASMALL",COLOR_NORMAL, 530, 370, SCRIPT_ALIGN_LEFT,1.0);

	// > все неизменные строки читаем из common.ini один раз и более не дёргаем движок линейными поисками
	sLngWin        = XI_ConvertString("BoalGameWin");
	sLngLose       = XI_ConvertString("BoalGameLose");
	sLngMoneyWin   = XI_ConvertString("BoalGameMoneyWin");
	sLngMoneyLose  = XI_ConvertString("BoalGameMoneyLose");
	sLngTimePassed = XI_ConvertString("BoalGameTimePassed");
	sLngDifference = XI_ConvertString("BoalGameDifference");
	sLngGetCard    = XI_ConvertString("BoalGameGetCard");
	sLngBet        = XI_ConvertString("BoalGameBet");
	sLngGetCard2   = XI_ConvertString("BoalGameGetCard2");
	sLngMoneyBet   = XI_ConvertString("BoalGameMoneyBet");
	sLngEndTurn    = XI_ConvertString("BoalGameEndTurn");
	sLngTurn_1     = XI_ConvertString("BoalGameTurn_1");
	sLngTurn_2     = XI_ConvertString("BoalGameTurn_2");
	sLngTurn_3     = XI_ConvertString("BoalGameTurn_3");
	sLngTurnNPC_1  = XI_ConvertString("BoalGameTurnNPC_1");
	sLngTurnNPC_2  = XI_ConvertString("BoalGameTurnNPC_2");
	sLngTurnNPC_3  = XI_ConvertString("BoalGameTurnNPC_3");
	sLngNext_3     = XI_ConvertString("BoalGameCheckGame_3");
	sLngNext_4     = XI_ConvertString("BoalGameCheckGame_4");
	sLngNoMore     = XI_ConvertString("BoalGameCheckGame_5");

    // новая игра
	SaveCurrentQuestDateParam("StartGameSession");
    iTurnGame = 1; // игра первая
    iHeroLose = 0; // > обнуляем до NewGameBegin (он через RedrawDeck зовёт)
    iHeroWin  = 0; // > BetaInfo, которая иначе показала бы счёт прошлого сеанса
    NewGameBegin();
	SetTimeTexts();
	SetFormatedText("STATS_TEXT", XI_ConvertString("Statistic"));
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
	bool bAffairOfHonor = false;

	// > монеты могли остаться в полёте - снимаем обработчик кадра до выгрузки сегмента
	CoinFlyStop();

	if (!openExit)
	{
		PlaySound("uplata");
		TEV.Gambling.LoseMoney = sti(TEV.Gambling.LoseMoney) + (money_i * iRate);
	}
	else
	{
		if (npchar.id == "AffairOfHonor_WolvesAndSheeps_Man") bAffairOfHonor = true;
	}

	AddMoneyToCharacter(pchar, iMoneyP - sti(pchar.Money)); // mitrokosta раздача денег теперь в конце
	AddMoneyToCharacter(npchar, iMoneyN - sti(npchar.Money));

	TEV.Stats.Gambling.Cards.LoseMoney = sti(TEV.Stats.Gambling.Cards.LoseMoney) + sti(TEV.Gambling.LoseMoney);
	TEV.Stats.Gambling.Cards.WinMoney = sti(TEV.Stats.Gambling.Cards.WinMoney) + sti(TEV.Gambling.WinMoney);
	
	Log_Clear();
	
	TEV.Gambling.Diff.Plus = "";
	TEV.Gambling.DiffAll.Plus = "";
	
	string sCardWin = XI_ConvertString("BoalGameCardWin");
	string sTotal;

	if (GetOfficersPerkUsing(pchar, "HawkEye", true))
	{
		sTotal = GetStrSmallRegister(XI_ConvertString("Total"));

		Log_Info(sCardWin + ": " + iHeroWin + " (" + sTotal + " " + (Statistic_AddValue(Pchar, "GameCards_Win", 0) + iHeroWin) + ")");
		Log_Info(sLngLose + ": " + iHeroLose + " (" + sTotal + " " + (Statistic_AddValue(Pchar, "GameCards_Lose", 0) + iHeroLose) + ")");
		Log_Info(sLngMoneyWin + ": " + TEV.Gambling.WinMoney + " (" + sTotal + " " + TEV.Stats.Gambling.Cards.WinMoney + ")");
		Log_Info(sLngMoneyLose + ": " + TEV.Gambling.LoseMoney + " (" + sTotal + " " + TEV.Stats.Gambling.Cards.LoseMoney + ")");

		TEV.Gambling.Diff = makeint(TEV.Gambling.WinMoney) - makeint(TEV.Gambling.LoseMoney);
		TEV.Gambling.DiffAll = makeint(TEV.Stats.Gambling.Cards.WinMoney) - makeint(TEV.Stats.Gambling.Cards.LoseMoney);

		if (sti(TEV.Gambling.Diff) > 0)
			TEV.Gambling.Diff.Plus = "+";

		if (sti(TEV.Gambling.DiffAll) > 0)
			TEV.Gambling.DiffAll.Plus = "+";

		Log_Info(sLngDifference + ": " + TEV.Gambling.Diff.Plus + FindMoneyString(sti(TEV.Gambling.Diff)) + " (" + sTotal + " " + TEV.Gambling.DiffAll.Plus + FindMoneyString(sti(TEV.Gambling.DiffAll))  + ")");
	}
	else
	{
		Log_Info(sCardWin + ": " + iHeroWin);
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
    DelEventHandler("My_eOpenCards","OpenCards");
	DelEventHandler("frame","CoinFlyFrame"); // > ещё раз, на случай сбитого флага
	
	// > ровно одна отправка на выход из-за стола
	if (sti(pchar.GenQuest.Cards.SitType) == true)
	{
		if (bAffairOfHonor)
			DoQuestFunctionDelay("AffairOfHonor_AfterCards", 0.6);
		else
			DoQuestCheckDelay("exit_sit", 0.6);
	}
	interfaceResultCommand = RC_INTERFACE_SALARY_EXIT;

    Statistic_AddValue(Pchar, "GameCards_Win", iHeroWin);
    AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*5*iHeroWin);
    AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*2*iHeroLose);
    Statistic_AddValue(Pchar, "GameCards_Lose", iHeroLose);

	if(!CheckCardsGameSmallRate()) SetCharacterPerk(pchar, "SaveLoadAbuser");
	if(CheckCharacterPerk(pchar, "SaveLoadAbuser") && CheckCardsGameSmallRate()) DeleteTrait(pchar, "SaveLoadAbuser");

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

	switch(nodName)
	{
    	case "B_PACK":
    		if(comName=="activate" || comName=="click")
    		{
                if (openExit == true)
                {   // ещё одна игра
                    if (bStartGame != 100)
                    {
                        dir_i = -dir_i_start;
                        dir_i_start = dir_i;
                        iTurnGame++;
                        NewGameBegin();
                        openExit = false;
                    }
                    else
                    {
                        PlaySound("knock");
                    }
                }
                else
                {   // ГГ берёт карты
                    if (bStartGame <2) break; // ещё сдают
                    if (bStartGame == 100) break; // открываемся
                    
                    if (dir_i == 1 && (iMoneyP - iRate) < 0)
                    {
                        PlaySound("knock");
                        SetInfoText(XI_ConvertString("BoalGameNoMoney") + GetLangSexPhrase("ий","ая"));
                        break;
                    }
                    if (dir_i == -1 && (iMoneyN - iRate) < 0)
                    {
                        PlaySound("knock");
                        SetInfoText(XI_ConvertString("BoalGameNPCNoMoney"));
                        break;
                    }

                    // > fix: клик по колоде не в свой ход молча жёг время (WaitDate) и кадры (крутил полную проверку квестов QuestsCheck)
                    if (dir_i != 1) break;

					if (cardMove) break; // mitrokosta фикс множественного взятия
					cardMove = true;     // начинаем перемещение

                    move_i = 0;
                    PlaySound("Took_item");
					SetCardTip("");
                    PostEvent("My_eventMoveImg", 100);

                    PutNextCoin();
                    money_i++;

                    iMoneyP = iMoneyP - iRate;
                    iChest += iRate;
                    howCard--;
                    cardsP[howPchar] = cardsPack[howCard];
                    howPchar++;

                    UpdateTime();
                    ShowMoney();
                }
    		}
    	break;
    	
    	case "B_ICON_1":
    		if(comName=="activate" || comName=="click")
    		{
                if (cardMove) break; // > fix: передача хода в момент, когда карта ещё летит, роняла кон дважды

                if (dir_i == 1 && bStartGame != 100 && bStartGame > 1 && !openExit) // только передача хода или открываемся
                {
					SetCardTip("");
                    dir_i = -1; // смена хода
                    SetNextTip();
                    if (dir_i_start == -1)// комп начинал игру первый
                    {
                        SetInfoText(XI_ConvertString("BoalGameOpenCard"));
                        bStartGame = 100;
                        PostEvent("My_eOpenCards", 2000);
                    }
                    else
                    {// комп должен себе набрать
                        SetInfoText(XI_ConvertString("BoalGameNPCGetCard"));

						cardMove = true; // > карта компа тоже летит - блокируем колоду
                        move_i = 0;
                        PlaySound("Took_item");
                        PostEvent("My_eventMoveImg", 500);
                        
                        PutNextCoinOp();
                        moneyOp_i++;
                        iMoneyN = iMoneyN - iRate;
                        iChest += iRate;
                        howCard--;
                        cardsN[howNpchar] = cardsPack[howCard];
                        howNpchar++;
                        UpdateTime();
                        ShowMoney();
                    }
                }
                else
                {
                    PlaySound("knock");
                }
    		}
    	break;
    	
    	case "B_ICON_2":
    		if(comName=="activate" || comName=="click")
    		{
                //PlaySound("knock");
    		}
    	break;
	}
}

void MoveImg()
{
	int k = scx;
	int n;
	if(dir_i > 0)
		n = howPchar;
	else
		n = howNpchar;
    if (n > 6)
        k = scx/2;

	int i, x, y, x1, x2, y1, y2;
	int iBase, iShift;
	float tSlide;
	x1 = iPackX1;
	y1 = iPackY1;

	x1 = x1 - 200;
	x2 = x1 + 315 - n * k / 2 + (n - 1) * k;	// карта летит к следующему слоту
	y2 = y1 + 185 + dir_i * 345;

    if (move_i == 0)
    {
		SetNodeUsing("Blank", true);
		// случайная промежуточная точка
        x_rand = x1 + (x2 - x1) / 2 - 200 + rand(400);
        y_rand = y1 + dir_i * 120 - 150 + rand(300);
    }

	float t = move_i / 50.0;
    t = t * t * (3.0 - 2.0 * t);	// ускорение в начале, замедление в конце
    x = 200 + makeint((1.0 - t)*(1.0 - t)*x1 + 2.0*(1.0 - t)*t*x_rand + t*t*x2);
	if (dir_i > 0)
		y2 -= 340;
	else
		y2 -= 10;
    y = makeint((1.0 - t)*(1.0 - t)*y1 + 2.0*(1.0 - t)*t*y_rand + t*t*y2);
	float scale = 1.0 + 0.1 * 4.0 * t * (1.0 - t);	// плавное увеличение карты к середине, уменьшение после середины
	SetNodePosition("Blank", x, y, x + makeint(scx * scale), y + makeint(scy * scale));
	
	if(t > 0.5)	// карты в руке плавно сдвигаются влево
	{
		// > fix: здесь ранее на каждом кадре стоял CreateImage на каждую карту в руке.
		// > Картинка при этом не меняется (движется только прямоугольник).
		// > За один полёт карты это были десятки тысяч бессмысленных сравнений строк.
		// > Теперь шлём только MSG_INTERFACE_PLACE_IMAGE.
		tSlide = (t - 0.5) * 2.0;
		iBase  = 220 - (n - 1) * k / 2;
		iShift = 240 - n * k / 2;

		if(dir_i > 0)
		{
			for (i = 0; i < n - 1; i++)
			{
				x1 = iBase  + i * k;
				x2 = iShift + i * k;
				x = 150 + makeint(x1 + (x2 - x1) * tSlide);
				SlideCardP(i, x, 390);
			}
		}
		else
		{
			for (i = 0; i < n - 1; i++)
			{
				x1 = iBase  + i * k;
				x2 = iShift + i * k;
				x = 150 + makeint(x1 + (x2 - x1) * tSlide);
				SlideCardN(i, x, 40);
			}
		}
	}

    move_i++;
    if (move_i < 50)
    {
        PostEvent("My_eventMoveImg", r_delta);
    }
    else
    {
		cardMove = false; // закончили перемещение
		SetNodeUsing("Blank", false);
        PlaySound("interface\button3.wav");
        // перерисуем все карты на руках
        RedrawCards();
        
        // начало игры, по карте каждому -->
        if (bStartGame < 2)
        {
            dir_i = -dir_i; // смена хода
            bStartGame++;
            if (bStartGame == 1)  PostEvent("My_eStartGame", 500);
        }
        // начало игры, по карте каждому <--
        SetNextTip();
        CheckGame();
		if(bStartGame >= 2 && dir_i == 1)
			SetCardTip("action");
    }
}

// > Сдвиг уже лежащих карт игрока/компа
void SlideCardP(int i, int x, int y)
{
	string sCard;
	if (sCardShownP[i] == "")
	{
		sCard = "c" + cardsP[i];
		ShowCardP(i, NullCharacter.Cards.(sCard).pic, x, y);
		return;
	}
	MoveImage("PCard" + i, x, y, x + scx, y + scy);
}

void SlideCardN(int i, int x, int y)
{
	if (sCardShownN[i] == "")
	{
		ShowCardN(i, "blank", x, y);
		return;
	}
	MoveImage("PCard" + (18 + i), x, y, x + scx, y + scy);
}

void PutNextCoin()
{
    if (money_i > 17) return;
    CreateImage("Money_"+money_i,"CARDS",money_s, 280+money_i*3, 280-money_i*3, 280+money_i*3 + smxy, 280-money_i*3 + smxy);
    if (money_i >= iClearMoneyP) iClearMoneyP = money_i + 1;
}
void PutNextCoinOp()
{
    if (moneyOp_i > 17) return;
    CreateImage("Money_"+(18+moneyOp_i),"CARDS",money_s, 380+moneyOp_i*3, 280-moneyOp_i*3, 380+moneyOp_i*3 + smxy, 280-moneyOp_i*3 + smxy);
    if (moneyOp_i >= iClearMoneyN) iClearMoneyN = moneyOp_i + 1;
}

// ------------------------------------------------------------------
// > Перелёт выигранных монет на портрет победителя
// ------------------------------------------------------------------

// > Откуда стартует монета номер i: сначала монеты сундука, за ними ставки ГГ, последними ставки соперника.
void CoinFlySetStart(int iCoin)
{
	int k = iCoin;

	// > Банк летит первым (анимация монет банка есть только при iCoinFlyBank > 0).
	if (k < iCoinFlyBankN)
	{	// > сундук ICON_CHECT из ini, монеты вылетают из него горкой
		iCoinFlyX = 729 - iCoinFlySize / 2 - 16 + k * 9;
		iCoinFlyY = 305 - iCoinFlySize / 2 - 12 + k * 7;
		return;
	}
	k = k - iCoinFlyBankN;
	if (k < iCoinFlyP)
	{
		iCoinFlyX = 280 + k * 3;
		iCoinFlyY = 280 - k * 3;
		return;
	}
	k = k - iCoinFlyP;
	iCoinFlyX = 380 + k * 3;
	iCoinFlyY = 280 - k * 3;
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

// > who: 1 - выиграл ГГ (нижний портрет), иначе соперник (верхний).
void CoinFlyStart(int who)
{
	CoinFlyStop(); // > хвост прошлой анимации не должен мешаться с новой

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

	// > числа взяты из boal_cards.ini: картинки и узлы ini живут в одних и тех же координатах, отступ канвы движок добавляет сам. ICON_2 - ГГ, ICON_1 - соперник.
	iCoinFlyToX = 515;
	if (who == 1)
	{	// > портрет ГГ
		iCoinFlyToY = 357;
		sPortrNode  = "ICON_2";
		iPortrX1 = iPortr2X1; iPortrY1 = iPortr2Y1;
		iPortrX2 = iPortr2X2; iPortrY2 = iPortr2Y2;
		iPortrBlinkR = 255; iPortrBlinkG = 245; iPortrBlinkB = 170; // > тёплая вспышка
	}
	else
	{	// > портрет соперника
		iCoinFlyToY = 251;
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
		CreateImage("Money_" + (18 + i), "", "", 0, 0, 0, 0);
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

void PackShake()
{
    // тасуем карты
    // > заменил на тасование Фишера-Йейтса
   
    int i, j, tmp;

    for (i = 0; i < 36; i++)
	{
        cardsPack[i] = i + 1;
	}

    for (i = 35; i > 0; i--)
    {
        j = rand(i);
        tmp = cardsPack[i];
        cardsPack[i] = cardsPack[j];
        cardsPack[j] = tmp;
    }

    howCard = 36;
}
void RedrawCards()
{
    int i;
    string sTemp;
    int k, x;
    k = scx;
    if (howPchar > 6)
    {
        k = scx/2;
    }

    x = 390 - howPchar*k/2;
    for (i=0; i<howPchar; i++)
	{
        sTemp = "c"+cardsP[i];
        ShowCardP(i, NullCharacter.Cards.(sTemp).pic, x + i*k, 390);
	}
	if (howPchar > iClearCardP) iClearCardP = howPchar; // > сколько слотов чистить

	k = scx;
	if (howNpchar > 6)
    {
        k = scx/2;
    }
	x = 390 - howNpchar*k/2;
	for (i=0; i<howNpchar; i++)
	{
        if (openExit)
        {
            sTemp = "c"+cardsN[i];
            sTemp = NullCharacter.Cards.(sTemp).pic;
        }
        else
        {
            sTemp = "blank";
        }
        ShowCardN(i, sTemp, x + i*k, 40);
	}
	if (howNpchar > iClearCardN) iClearCardN = howNpchar;
}
void RedrawDeck()
{
	// > fix: чистим ровно те слоты, которые в прошлом коне действительно занимали
	int i;
	for (i = iClearMoneyP - 1; i >= 0; i--)
	{
        CreateImage("Money_" + i, "", "", 0, 0, 0, 0);
	}
	for (i = iClearMoneyN - 1; i >= 0; i--)
	{
        CreateImage("Money_" + (18 + i), "", "", 0, 0, 0, 0);
	}
	for (i = iClearCardP - 1; i >= 0; i--)
	{
        CreateImage("PCard" + i, "", "", 0, 0, 0, 0);
        sCardShownP[i] = "";
	}
	for (i = iClearCardN - 1; i >= 0; i--)
	{
        CreateImage("PCard" + (18 + i), "", "", 0, 0, 0, 0);
        sCardShownN[i] = "";
	}
	iClearMoneyP = 0;
	iClearMoneyN = 0;
	iClearCardP  = 0;
	iClearCardN  = 0;

	money_i = 0; // индекс монетки
	moneyOp_i = 0;
	iChest = 0; // на кону

	UpdateTime();
	ShowMoney();

	// тасуем карты
	PackShake();
	howPchar  = 0; // карты на руках
	howNpchar = 0;
	SetNextTip();
	BetaInfo();
}

void SetNextTip()
{
    if (dir_i == 1)
    {
        if (bStartGame <2)
        {
            SetInfoText(sLngGetCard + NewStr() + sLngBet);
			SetBtnText("");
        }
        else
        {
            SetInfoText(LinkRandPhrase(sLngTurn_1, sLngTurn_2, RandSwear() + " " + sLngTurn_3));
			SetBtnText(sLngEndTurn);
        }
    }
    else
    {
		SetBtnText("");
        if (bStartGame <2)
        {
            SetInfoText(sLngGetCard2 + NewStr() + sLngMoneyBet);
        }
        else
        {
            SetInfoText(LinkRandPhrase(sLngTurnNPC_1, sLngTurnNPC_2, sLngTurnNPC_3));
        }
    }
}
int CountCardsP()
{
    int ret = 0;
    int i;
    string sTemp;
    
    for (i = 0; i < howPchar; i++)
    {
        sTemp = "c"+cardsP[i];
        ret += sti(NullCharacter.Cards.(sTemp).count);
    }
    return ret;
}

int CountCardsN()
{
    int ret = 0;
    int i;
    string sTemp;

    for (i = 0; i < howNpchar; i++)
    {
        sTemp = "c"+cardsN[i];
        ret += sti(NullCharacter.Cards.(sTemp).count);
    }
    return ret;
}

void BetaInfo()
{
	BetaInfoEx(CountCardsP());
}

void BetaInfoEx(int iCountP)
{
    if (bBettaTestMode)
    {
        GameInterface.strings.Beta_P       = "Beta_P " + iCountP;
        GameInterface.strings.Beta_N       = "Beta_N " + CountCardsN();
        GameInterface.strings.Beta_Next    = "Beta_Next " + NextCardPack();
        GameInterface.strings.Beta_MoneyN  = "Beta_MoneyN " + MakeMoneyShow(iMoneyN, MONEY_SIGN,MONEY_DELIVER);
        GameInterface.strings.Beta_WinLose = "Beta Win " + (Statistic_AddValue(Pchar, "GameCards_Win", 0)+iHeroWin) + " Lose " + (Statistic_AddValue(Pchar, "GameCards_Lose", 0)+iHeroLose);
    }

	if (iCountP > 0)
		GameInterface.strings.CountCardsPlayer = "" + iCountP;
	else
		GameInterface.strings.CountCardsPlayer = "";
	
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
int NextCardPack()
{
    string sTemp;
    int ret;

    if (howCard < 1) return 0;

    sTemp = "c"+cardsPack[howCard-1];
    ret = sti(NullCharacter.Cards.(sTemp).count);
    
    return ret;
}
// сдать карту
void StartGame()
{
    move_i = 0;
	openExit = false;

    PlaySound("Took_item");
	SetCardTip("");
    PostEvent("My_eventMoveImg", 70);
	SetBtnText("");

	cardMove = true; // > карта в полёте - колода заблокирована

    if (dir_i == 1)
    {
        PutNextCoin();
        money_i++;

        iMoneyP = iMoneyP - iRate;

        howCard--;
        cardsP[howPchar] = cardsPack[howCard];
        howPchar++;
    }
    else
    {
        PutNextCoinOp();
        moneyOp_i++;
        iMoneyN = iMoneyN - iRate;
        howCard--;
        cardsN[howNpchar] = cardsPack[howCard];
        howNpchar++;
    }
    iChest += iRate;
    UpdateTime();
    ShowMoney();
}

// > Время игры вынесено из ShowMoney отдельно (чтобы не дёргать QuestsCheck лишний раз)
void UpdateTime()
{
	WaitDate("", 0, 0, 0, 0, 1);
	SetTimeTexts();
}

void ShowMoney()
{
    GameInterface.strings.Money        = MakeMoneyShow(iMoneyP,MONEY_SIGN,MONEY_DELIVER);
    GameInterface.strings.MoneyInChest = MakeMoneyShow(iChest,MONEY_SIGN,MONEY_DELIVER);
}

bool CheckGame()
{
    string sTemp;
    int   ok = 0;
    bool  ok1;
    bool  ret = false;

    int iCountP = CountCardsP();
    int iCountN = CountCardsN();

    if (iCountP > 21)
    {
        ok = -1;
        sTemp = XI_ConvertString("BoalGameCheckGame_1");
        iHeroLose++;
    }
    else if (iCountN > 21)
    {
        ok = 1;
        sTemp = RandSwear() + " " + XI_ConvertString("BoalGameCheckGame_2")+ GetLangSexPhrase("","а") +".";
        iHeroWin++;
    }
    if (ok != 0)
    {
		SetBtnText("");
        EndGameCount(ok);
        if (ok == 1) RedrawCards(); // покажем перебор

        if (CheckNextGame() && rand(10) < 10) // есть деньги на игру
        {
            sTemp += NewStr() + RandPhraseSimple(sLngNext_3, sLngNext_4);
        }
        else
        {
            bStartGame = 100;//признак запрета новой игры
            npchar.game_over = true;
            sTemp += NewStr() + sLngNoMore;
        }
        SetInfoText(sTemp);
        ret = true;
		SetCardTip("");
		SetCardTip("restart");
    }
    else
    {
		bool bChecker = (GetCharacterSPECIAL(pchar, SPECIAL_P) > 3) || (GetOfficersPerkUsing(pchar, "HawkEye", true));

        int iNext = NextCardPack();
        int iFortune = GetCharacterSkillToOld(pchar, SKILL_FORTUNE);
        ok1 = (iCountN > 16) && (iCountN < 22);
        // жухло!!!!! -->
        if (!bChecker && iFortune < rand(12))
        {
            if (ok1 && (iCountN + iNext) <= 21)
            {
                ok1 = false;
            }
            if (iFortune < rand(10) && iCountN < 17 &&  (iCountN + iNext) > 21)
            {
                ok1 = true;
            }
        }
        // жухло!!!!! <--

        if (ok1 || (iMoneyN - iRate) < 0)
        {
            if (dir_i == -1 && dir_i_start == 1)// комп ходит последним
            {
                SetInfoText(XI_ConvertString("BoalGameCheckGame_6"));
				SetBtnText("");
                bStartGame = 100;
				SetCardTip("");
                PostEvent("My_eOpenCards", 2000);
                ret = true;
            }
            if (dir_i == -1 && dir_i_start == -1)// комп начинает
            {
                dir_i = 1;
                SetInfoText(XI_ConvertString("BoalGameCheckGame_7"));
				SetBtnText(sLngEndTurn);
                ret = true;
            }
        }
        else
        {
            if (dir_i == -1 && bStartGame >= 2) // комп играет сам
            {
				cardMove = true; // начинаем перемещение
                move_i = 0;
                PlaySound("Took_item");
				SetCardTip("");
                PostEvent("My_eventMoveImg", 500);

                PutNextCoinOp();
                moneyOp_i++;
                iMoneyN = iMoneyN - iRate;
                iChest += iRate;
                howCard--;
                cardsN[howNpchar] = cardsPack[howCard];
                howNpchar++;
                UpdateTime();
                ShowMoney();

                ret = true;
            }
        }
    }
	BetaInfoEx(iCountP);
    return ret;
}

void NewGameBegin()
{
	SetCardTip("");
	WaitDate("", 0, 0, 0, 0, 1 + (rand(4)));
	SetTimeTexts();
    RedrawDeck(); // новая игра
    bStartGame = 0;
    SetInfoText(XI_ConvertString("BoalGameGetCards") + " "+NewStr()+XI_ConvertString("BoalGameBets"));
    PostEvent("My_eStartGame", 1000);
}

void EndGameCount(int who)
{
    openExit = true;
    if (who == 1) // ГГ
    {
		iMoneyP += iChest;
		TEV.Gambling.WinMoney = sti(TEV.Gambling.WinMoney) + (iChest - (money_i * iRate));
    }
    else
    {
		iMoneyN += iChest;
		TEV.Gambling.LoseMoney = sti(TEV.Gambling.LoseMoney) + (iChest - (moneyOp_i * iRate));
    }
	// > единственная точка, через которую проходят оба конца партии - и перебор, и вскрытие
	CoinFlyStart(who);
}

void OpenCards()
{
    string sTemp;
	SetBtnText("");

    int iCountP = CountCardsP();
    int iCountN = CountCardsN();

    string sMine  = XI_ConvertString("BoalGameOpenCards_3");
    string sYours = XI_ConvertString("BoalGameOpenCards_2");

    if (iCountP > makefloat(iCountN + 0.1 * dir_i_start)) // преимущество тому, кто сдает (те ходит последним)
    {
        EndGameCount(1);
        sTemp = RandSwear() + " " + XI_ConvertString("BoalGameOpenCards_1") + GetLangSexPhrase("","а") + ". " + UpperFirst(sYours) + " " + iCountP + ", " + sMine + " " + iCountN + "." ;
        iHeroWin++;
    }
    else
    {
        EndGameCount(-1);
        sTemp = XI_ConvertString("BoalGameOpenCards_4") + " " + sMine + " " + iCountN + ", " + sYours + " " + iCountP + ". " + XI_ConvertString("BoalGameOpenCards_5");
        iHeroLose++;
    }
	SetCardTip("");
    if (CheckNextGame() && rand(10) < 10) // есть деньги на игру
    {
		SetCardTip("action");
        sTemp += NewStr() + RandPhraseSimple(sLngNext_3, sLngNext_4);
        bStartGame = 2;
    }
    else
    {
        bStartGame = 100;//признак запрета новой игры
        npchar.game_over = true;
        sTemp += NewStr() + sLngNoMore;
    }
    SetInfoText(sTemp);
    RedrawCards();
	BetaInfoEx(iCountP);
}

bool CheckNextGame()
{
    bool ret = true;
    if (iRate * 3 > iMoneyN) ret = false;
    if (iRate * 3 > iMoneyP) ret = false;
    
    return ret;
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
action - взять карту, передать ход, открыть карты
*/
void SetCardTip(string tag)
{
	switch(tag)
	{
		case "":	// убираем все подсказки
			SetPictureBlind("Pack", false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
			SetPictureBlind("ICON_1", false, argb(255, 128, 128, 128), argb(255, 155, 155, 155), 0.6, 0.6);
		break;
		case "restart":
			if(bStartGame >= 2 && bStartGame != 100)	// можно начать новую игру - колода
			{
				SetPictureBlind("Pack", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
			}
		break;
		case "action":
			if(dir_i == 1 && bStartGame >= 2 && !openExit && bStartGame != 100)
			{
				if(iMoneyP - iRate >= 0)	// хватает денег на ставку - колода
				{
					SetPictureBlind("Pack", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
				}
				SetPictureBlind("ICON_1", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
			}
		break;
	}
}

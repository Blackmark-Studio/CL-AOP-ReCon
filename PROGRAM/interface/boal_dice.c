// boal 10.06.05
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

string ResultStr;

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

	for(i = 1; i<=5; i++)
	{
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "HeroDice" + i, 100);
		SetNodeUsing("HeroDice" + i, false);
		XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "CompDice" + i, 100);
		SetNodeUsing("CompDice" + i, false);
	}

	XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "DiceCup", 100);
	SetNewGroupPicture("DiceCup", "DICE", "cup");

	int x1, y1, x2, y2;
	GetNodePosition("B_PACK", &x1, &y1, &x2, &y2);
	x1 = x1 - 91;
	y1 = y1 - 38;
	x2 = x1 + spx;
	y2 = y1 + spy;
	SetNodePosition("DiceCup", x1, y1, x2, y2);

	CreateImage("GOLD","GOLD","GOLD", 482,444,524,486);

	if (CheckAttribute(npchar, "faceId") && sti(npchar.faceId) > 1 && FindFile("RESOURCE\\Textures\\interfaces\\PORTRAITS\\64\\", "face_" + npchar.faceId + ".tga.tx", "*.tx", true))
		SetNewPicture("ICON_1", "interfaces\PORTRAITS\64\face_" + npchar.faceId + ".tga");

	SetNewPicture("ICON_2", "interfaces\PORTRAITS\64\face_" + pchar.faceId+ ".tga");

	CreateString(true,"Money","",FONT_NORMAL,COLOR_MONEY,613,508,SCRIPT_ALIGN_CENTER,1.1);
	CreateString(true,"MoneyInChest","",FONT_NORMAL,COLOR_MONEY,615,452,SCRIPT_ALIGN_CENTER,1.3);

	if (rand(1) == 1)
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
	// новая игра
	SaveCurrentQuestDateParam("StartGameSession");
	NewGameBegin(true);
	SetFormatedText("TIME_TEXT", "" + GetQuestBookData());
	SetFormatedText("STATS_TIME_TEXT", "" + GetSessionTime());
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
	if (!openExit)
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

	if (GetOfficersPerkUsing(pchar, "HawkEye", true))
	{
		Log_Info(XI_ConvertString("BoalGameDiceWin") + ": " + iHeroWin + " (" + GetStrSmallRegister(XI_ConvertString("Total")) + " " + (Statistic_AddValue(Pchar, "GameDice_Win", 0) + iHeroWin) + ")");
		Log_Info(XI_ConvertString("BoalGameLose") + ": " + iHeroLose + " (" + GetStrSmallRegister(XI_ConvertString("Total")) + " " + (Statistic_AddValue(Pchar, "GameDice_Lose", 0) + iHeroLose) + ")");
		Log_Info(XI_ConvertString("BoalGameMoneyWin") + ": " + TEV.Gambling.WinMoney + " (" + GetStrSmallRegister(XI_ConvertString("Total")) + " " + TEV.Stats.Gambling.Dice.WinMoney + ")");
		Log_Info(XI_ConvertString("BoalGameMoneyLose") + ": " + TEV.Gambling.LoseMoney + " (" + GetStrSmallRegister(XI_ConvertString("Total")) + " " + TEV.Stats.Gambling.Dice.LoseMoney + ")");

		TEV.Gambling.Diff = makeint(TEV.Gambling.WinMoney) - makeint(TEV.Gambling.LoseMoney);
		TEV.Gambling.DiffAll = makeint(TEV.Stats.Gambling.Dice.WinMoney) - makeint(TEV.Stats.Gambling.Dice.LoseMoney);

		if (sti(TEV.Gambling.Diff) > 0)
			TEV.Gambling.Diff.Plus = "+";

		if (sti(TEV.Gambling.DiffAll) > 0)
			TEV.Gambling.DiffAll.Plus = "+";

		Log_Info(XI_ConvertString("BoalGameDifference") + ": " + TEV.Gambling.Diff.Plus + FindMoneyString(sti(TEV.Gambling.Diff)) + " (" + GetStrSmallRegister(XI_ConvertString("Total")) + " " + TEV.Gambling.DiffAll.Plus + FindMoneyString(sti(TEV.Gambling.DiffAll))  + ")");
	}
	else
	{
		Log_Info(XI_ConvertString("BoalGameDiceWin") + ": " + iHeroWin);
		Log_Info(XI_ConvertString("BoalGameLose") + ": " + iHeroLose);
		Log_Info(XI_ConvertString("BoalGameMoneyWin") + ": " + TEV.Gambling.WinMoney);
		Log_Info(XI_ConvertString("BoalGameMoneyLose") + ": " + TEV.Gambling.LoseMoney);
		TEV.Gambling.Diff = makeint(sti(TEV.Gambling.WinMoney) - sti(TEV.Gambling.LoseMoney));

		if (sti(TEV.Gambling.Diff) > 0)
			TEV.Gambling.Diff.Plus = "+";

		Log_Info(XI_ConvertString("BoalGameDifference") + ": " + TEV.Gambling.Diff.Plus + FindMoneyString(sti(TEV.Gambling.Diff)));
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

	bQuestCheckProcessFreeze = true;
	bQuestCheckProcessFreeze = false;
	RefreshLandTime();
	EndCancelInterface(true);
	DeleteAttribute(pchar, "StartGameSession");
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
	ref chr = GetMainCharacter();

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
				}if (dir_i_start == 1 && bStartGame == 2)  // пропуск хода
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

	GetNodePosition("B_PACK", &x1, &y1, &x2, &y2);
	x1 = x1 - 231;
	y1 = y1 - 38;
	x2 = x1 - 274;
	y2 = y2 + 37;

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
	CreateImage("Money_"+money_i,"CARDS",money_s, 530+money_i*3, 310-money_i*3, 530+money_i*3 + smxy, 310-money_i*3 + smxy);
}
void PutNextCoinOp()
{
	CreateImage("Money_"+(28+moneyOp_i),"CARDS",money_s, 630+moneyOp_i*3, 310-moneyOp_i*3, 630+moneyOp_i*3 + smxy, 310-moneyOp_i*3 + smxy);
}

void RedrawDeck(bool _newGame, bool _clearDice)
{
	// монетки с запасом
	int i;
	if (_newGame)
	{
		for (i=55; i>=0; i--)
		{
			CreateImage("Money_" + i ,"", "", 0, 0, 0, 0);
		}
		money_i = 0; // индекс монетки
		moneyOp_i = 0;
		iChest = 0; // на кону
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

	GameInterface.strings.Wins			= XI_ConvertString("BoalGameWin") + " ";
	GameInterface.strings.Loses			= XI_ConvertString("BoalGameLose") + " ";
	GameInterface.strings.MoneyWin		= XI_ConvertString("BoalGameMoneyWin") + " ";
	GameInterface.strings.MoneyLose		= XI_ConvertString("BoalGameMoneyLose") + " ";
	GameInterface.strings.TimePassed	= XI_ConvertString("BoalGameTimePassed") + " ";

	SetFormatedText("STATS_DIFF_TEXT", "" + sDiff + iDiff);
	GameInterface.strings.MoneyDiff	= XI_ConvertString("BoalGameDifference");

	SetFormatedText("STATS_WINS_TEXT", "" + iHeroWin);
	SetFormatedText("STATS_LOSES_TEXT", "" + iHeroLose);
	SetFormatedText("STATS_WINMONEY_TEXT", "" + TEV.Gambling.WinMoney);
	SetFormatedText("STATS_LOSEMONEY_TEXT", "" + TEV.Gambling.LoseMoney);
	SetFormatedText("STATS_TIME_TEXT", "" + GetSessionTime());
}

// сдать карту
void StartGame()
{
	int i;
	move_i = 0;
	openExit = false;

	PlaySound("Took_item");
	SetFormatedText("B_TEXT_1", "");

	if (dir_i == -1) // комп первый
	{
		UpdateTime();
		PlaySound("DiceMix");
		SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameTurn_5"));
		PostEvent("My_eventMoveImg", 100);
	}
	else
	{
		SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameTurn_6")+ GetLangSexPhrase("ый", "ая") +". " + XI_ConvertString("BoalGameTurn_4"));
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
		SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameStart") + " "+NewStr()+XI_ConvertString("BoalGameBets"));
	}
	else
	{
		SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameContinue") + " "+NewStr()+XI_ConvertString("BoalGameBets"));
	}
	bSetRandDice = true;
	PostEvent("My_eStartGame", 1000);
	bLockClick = true;
	openExit = false;
	BetaInfo();
	WaitDate("", 0, 0, 0, 0, 1 + (rand(4)));
	SetFormatedText("TIME_TEXT", "" + GetQuestBookData());
	SetFormatedText("STATS_TIME_TEXT", "" + GetSessionTime());
}
// деньги в карман
void EndGameCount(int who)
{
	//openExit = true;
	if (who == 1) // ГГ
	{
		iMoneyP += iChest;
		TEV.Gambling.WinMoney = sti(TEV.Gambling.WinMoney) + (iChest - (money_i * iRate));
	}
	else if (who == -1)
	{
		iMoneyN += iChest;
		TEV.Gambling.LoseMoney = sti(TEV.Gambling.LoseMoney) + (iChest - (moneyOp_i * iRate));
	}
	else if (who == 0)// ничья
	{
		//
	}
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
}

void ClearDiceOnTable()
{
	for (int i = 1; i <= 5; i++)
	{
		CreateImage("Dice" + i, "", "", 0, 0, 0, 0);
	}
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

		SetFormatedText("B_TEXT_1", "");
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
			SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameTurn_1") + " " + XI_ConvertString("BoalGameTurn_4"));
			SetFormatedText("B_TEXT_1", "");
		}
		else
		{
			SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameTurn_7"));
			SetFormatedText("B_TEXT_1", XI_ConvertString("BoalGameEndTurn"));
		}
	}
	else
	{
		dir_i = -1;
		bLockClick = true;
		SetFormatedText("B_TEXT_1", "");
		if (bStartGame <1 )// первый заход
		{
			UpdateTime();
			SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameTurn_8"));
			move_i = 0;
			PlaySound("DiceMix");
			PostEvent("My_eventMoveImg", 500);
		}
		else
		{
			if (bStartGame <3)
			{
				// решаем ходить ли вообще
				SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameTurn_9"));
				PostEvent("My_eCompTurn", 800);
			}
		}
	}
	bStartGame++;
	SetDiceTip("");
	if (bStartGame > 3)
	{
		SetFormatedText("B_TEXT_1", "");
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

void PutCompLine()
{
	int i, x1, y1, x2, y2, x_dist = 80;

	GetNodePosition("B_HeroDice1", &x1, &y1, &x2, &y2);
	x1 = x1 - 16;
	y1 = y1 - 455;

	for (i = 1; i<=5; i++)
	{
		sDiceTemp = "d"+i;
		if (DiceState.Comp.(sDiceTemp).Mix == false)
		{
			SetNodeUsing("CompDice" + i, true);
			SetNewGroupPicture("CompDice" + i, "DICE", "dice_" + DiceState.Comp.(sDiceTemp) + "_1");
			SetNodePosition("CompDice" + i, x1 + x_dist * (i - 1), y1, x1 + x_dist * (i - 1) + scx, y1 + scy);
		}
	}
}

void PutHeroLine()
{
	int i, x1, y1, x2, y2, x_dist = 80;

	GetNodePosition("B_HeroDice1", &x1, &y1, &x2, &y2);
	x1 = x1 - 16;
	y1 = y1 - 11;

	for (i = 1; i<=5; i++)
	{
		sDiceTemp = "d"+i;
		if (DiceState.Hero.(sDiceTemp).Mix == false)
		{
			SetNodeUsing("HeroDice" + i, true);
			SetNewGroupPicture("HeroDice" + i, "DICE", "dice_" + DiceState.Hero.(sDiceTemp) + "_1");
			SetNodePosition("HeroDice" + i, x1 + x_dist * (i - 1), y1, x1 + x_dist * (i - 1) + scx, y1 + scy);
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
	int	   i, k, iOk;
	string sTemp;
	bool   ok;
	// 1) Покер - 5 одинаковых
	ok = true;
	for (i = 2; i<=5; i++)
	{
		sDiceTemp = "d"+i;
		if (sti(DiceState.(_whom).d1) != sti(DiceState.(_whom).(sDiceTemp)))
		{
			ok = false;
			break;
		}
	}
	if (ok)
	{
		DiceState.(_whom).Result.Type  = 1;
		DiceState.(_whom).Result.Rate1	= sti(DiceState.(_whom).d1);
		DiceState.(_whom).Result.Rate2	= sti(DiceState.(_whom).d1);
		return;
	}
	// 2) Стрит Бол.стрит - 2,3,4,5,6 Мал.стрит - 1,2,3,4,5
	ok = true;
	for (i = 1; i<=4; i++)
	{
		sDiceTemp = "d"+i;
		sTemp		= "d"+(i+1);
		if (sti(DiceState.(_whom).(sDiceTemp)) != (sti(DiceState.(_whom).(sTemp)) - 1) )
		{
			ok = false;
			break;
		}
	}
	if (ok)
	{
		DiceState.(_whom).Result.Type  = 2;
		DiceState.(_whom).Result.Rate1	= sti(DiceState.(_whom).d5);
		DiceState.(_whom).Result.Rate2	= sti(DiceState.(_whom).d5);
		return;
	}
	// 3) Каре - 4 одинаковых
	ok = true;
	for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
			sDiceTemp = "d"+i;
			if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sDiceTemp)))
			{
				iOk--;
			}
		}
		if (iOk >= 4)
		{
			DiceState.(_whom).Result.Type  = 3;
			DiceState.(_whom).Result.Rate1	= sti(DiceState.(_whom).(sTemp));
			DiceState.(_whom).Result.Rate2	= sti(DiceState.(_whom).(sTemp));
			return;
		}
	}
	// 4) Фул - 3 + 2
	ok = false;
	for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
			sDiceTemp = "d"+i;
			if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sDiceTemp)))
			{
				iOk--;
			}
		}
		if (iOk >= 3)
		{
			DiceState.(_whom).Result.Rate1	= sti(DiceState.(_whom).(sTemp));
			ok = true;
			break;
		}
	}
	if (ok)
	{
		ok = false;
		for (k = 1; k<=5; k++)
		{
			iOk = 5;
			sTemp = "d" + k;
			if (sti(DiceState.(_whom).(sTemp)) == sti(DiceState.(_whom).Result.Rate1)) continue;

			for (i = 1; i<=5; i++)
			{
				sDiceTemp = "d"+i;
				if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sDiceTemp)))
				{
					iOk--;
				}
			}
			if (iOk >= 2)
			{
				DiceState.(_whom).Result.Rate2	= sti(DiceState.(_whom).(sTemp));
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
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
			sDiceTemp = "d"+i;
			if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sDiceTemp)))
			{
				iOk--;
			}
		}
		if (iOk >= 3)
		{
			DiceState.(_whom).Result.Rate1	= sti(DiceState.(_whom).(sTemp));
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
	for (k = 1; k<=5; k++)
	{
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
			sDiceTemp = "d"+i;
			if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sDiceTemp)))
			{
				iOk--;
			}
		}
		if (iOk >= 2)
		{
			DiceState.(_whom).Result.Rate2	= sti(DiceState.(_whom).(sTemp)); // младшая
			ok = true;
			break;
		}
	}
	if (ok)
	{
		ok = false;
		for (k = 1; k<=5; k++)
		{
			iOk = 5;
			sTemp = "d" + k;
			if (sti(DiceState.(_whom).(sTemp)) == sti(DiceState.(_whom).Result.Rate2)) continue;

			for (i = 1; i<=5; i++)
			{
				sDiceTemp = "d"+i;
				if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sDiceTemp)))
				{
					iOk--;
				}
			}
			if (iOk >= 2)
			{
				DiceState.(_whom).Result.Rate1	= sti(DiceState.(_whom).(sTemp)); // старшая
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
		iOk = 5;
		sTemp = "d" + k;
		for (i = 1; i<=5; i++)
		{
			sDiceTemp = "d"+i;
			if (sti(DiceState.(_whom).(sTemp)) != sti(DiceState.(_whom).(sDiceTemp)))
			{
				iOk--;
			}
		}
		if (iOk >= 2)
		{
			DiceState.(_whom).Result.Rate1	= sti(DiceState.(_whom).(sTemp));
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

	for (k = 1; k<=4; k++)
	{
		sDiceTemp = "d"+k;
		w = sti(DiceState.(_whom).(sDiceTemp));
		j = k;
		for (m = k+1; m<=5; m++)
		{
			sDiceTemp = "d"+m;
			if (sti(DiceState.(_whom).(sDiceTemp)) < w)
			{
				j = m;
				w = sti(DiceState.(_whom).(sDiceTemp));
			}
		}
		sDiceTemp = "d"+j;
		sTemp		= "d"+k;
		DiceState.(_whom).(sDiceTemp) = DiceState.(_whom).(sTemp);
		DiceState.(_whom).(sTemp) = w;
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
	if (ok == -1)
	{
		sTemp += NewStr() + XI_ConvertString("BoalGameOpenCards_5");
		iHeroLose++;
	}
	if (ok == 1)
	{
		sTemp += NewStr() +	 RandSwear() + " " + XI_ConvertString("BoalGameOpenCards_1")+ GetLangSexPhrase("", "а") +".";
		iHeroWin++;
	}
	EndGameCount(ok);
	ResultStr = sTemp;
	SetFormatedText("INFO_TEXT", sTemp);
	return ret;
}

void ContinueGame()
{
	if (CheckNextGame())
	{
		dir_i		= -dir_i_start;
		dir_i_start = dir_i;
		NewGameBegin(true);
	}
	else
	{
		if (iRate*6 > iMoneyP)
		{
			ResultStr = XI_ConvertString("BoalGameNoMoney2") + NewStr() + XI_ConvertString("BoalGameCheckGame_5");
			SetFormatedText("INFO_TEXT",ResultStr);
			EndGameCount(-1);
			iHeroLose++;
		}
		else//if (iRate*6 > iMoneyN)
		{
			ResultStr = XI_ConvertString("BoalGameNPCNoMoney2")+ GetLangSexPhrase("", "а") +"!" + NewStr() + XI_ConvertString("BoalGameCheckGame_5");
			SetFormatedText("INFO_TEXT",ResultStr);
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
		ResultStr += NewStr() + XI_ConvertString("BoalGameCheckGame_4");
		bLockClick = false;
		SetDiceTip("");
		SetDiceTip("restart");
	}
	else
	{
		ResultStr += NewStr() + XI_ConvertString("BoalGameCheckGame_5");
		npchar.game_over = true;
		bLockClick = true;
	}
	SetFormatedText("INFO_TEXT",ResultStr);
}

string GetTypeName(int _type)
{
	Restrictor(&_type, 0, 7);
	return XI_ConvertString("BoalGameDiceState_" + (_type + 1));
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
			SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameTurnNPC_4"));
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
			SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameTurnNPC_5"));
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
			SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameTurnNPC_5"));
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
	SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameTurnNPC_6"));
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
	bool   ok;

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
	SetFormatedText("TIME_TEXT", "" + GetQuestBookData());
	SetFormatedText("STATS_TIME_TEXT", "" + GetSessionTime());
}

string GetSessionTime()
{
	if (!CheckAttribute(&TEV, "Gambling.Session"))
		TEV.Gambling.Session = "0";

	if (!CheckAttribute(PChar, "StartGameSession"))
		PChar.StartGameSession = "0";

	TEV.Gambling.Session = makefloat(GetQuestPastMinutesParam("StartGameSession") / 60.0);
	string sM = makeint(stf("0." + FindStringAfterChar(TEV.Gambling.Session, ".")) * 60);
	string sH = FindStringBeforeChar(TEV.Gambling.Session, ".");

	//if (sti(sH) < 10)
		//sH = "0" + sH;

	if (sti(sM) < 10)
		sM = "0" + sM;

	return sH + ":" + sM;
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

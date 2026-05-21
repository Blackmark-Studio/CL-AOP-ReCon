// boal 13.05.05
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

	int x1, y1, x2, y2;
	GetNodePosition("B_PACK", &x1, &y1, &x2, &y2);
	x1 = x1 - 53;
	x2 = x2 + 4;
	y2 = y2 + 15;

	XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "Pack", 100);
	SetNewGroupPicture("Pack", "CARDS", "pack");
	SetNodePosition("Pack", x1, y1, x2, y2);
	XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "Blank", 100);
	SetNewGroupPicture("Blank", "CARDS", "blank");
	SetNodePosition("Blank", x1 - 120, y1 - 5, x1 - 8, y1 + scy);
	SetNodeUsing("Blank", false);

	if (CheckAttribute(npchar, "faceId") && sti(npchar.faceId) > 1 && FindFile("RESOURCE\\Textures\\interfaces\\PORTRAITS\\64\\", "face_" + npchar.faceId + ".tga.tx", "*.tx", true))
		SetNewPicture("ICON_1", "interfaces\PORTRAITS\64\face_" + npchar.faceId + ".tga");
	
    SetNewPicture("ICON_2", "interfaces\PORTRAITS\64\face_" + pchar.faceId + ".tga");
    SetCardTip("");
    CreateString(true,"Money","",FONT_NORMAL,COLOR_MONEY, 613,348,SCRIPT_ALIGN_CENTER,1.1);
    CreateString(true,"MoneyInChest","",FONT_NORMAL,COLOR_MONEY,615,292,SCRIPT_ALIGN_CENTER,1.3);
    
    if (rand(1) == 1)
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
    // новая игра
	SaveCurrentQuestDateParam("StartGameSession");
    NewGameBegin();
    iTurnGame = 1; // игра первая
    iHeroLose = 0;
    iHeroWin  = 0;
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
	else
	{
		if (sti(pchar.GenQuest.Cards.SitType) == true)
		{
			if(npchar.id == "AffairOfHonor_WolvesAndSheeps_Man")
				DoQuestFunctionDelay("AffairOfHonor_AfterCards", 0.6);
			else
				DoQuestCheckDelay("exit_sit", 0.6);
		}
	}

	AddMoneyToCharacter(pchar, iMoneyP - sti(pchar.Money)); // mitrokosta раздача денег теперь в конце
	AddMoneyToCharacter(npchar, iMoneyN - sti(npchar.Money));

	TEV.Stats.Gambling.Cards.LoseMoney = sti(TEV.Stats.Gambling.Cards.LoseMoney) + sti(TEV.Gambling.LoseMoney);
	TEV.Stats.Gambling.Cards.WinMoney = sti(TEV.Stats.Gambling.Cards.WinMoney) + sti(TEV.Gambling.WinMoney);
	
	Log_Clear();
	
	TEV.Gambling.Diff.Plus = "";
	TEV.Gambling.DiffAll.Plus = "";
	
	if (GetOfficersPerkUsing(pchar, "HawkEye", true))
	{
		Log_Info(XI_ConvertString("BoalGameCardWin") + ": " + iHeroWin + " (" + GetStrSmallRegister(XI_ConvertString("Total")) + " " + (Statistic_AddValue(Pchar, "GameCards_Win", 0) + iHeroWin) + ")");
		Log_Info(XI_ConvertString("BoalGameLose") + ": " + iHeroLose + " (" + GetStrSmallRegister(XI_ConvertString("Total")) + " " + (Statistic_AddValue(Pchar, "GameCards_Lose", 0) + iHeroLose) + ")");
		Log_Info(XI_ConvertString("BoalGameMoneyWin") + ": " + TEV.Gambling.WinMoney + " (" + GetStrSmallRegister(XI_ConvertString("Total")) + " " + TEV.Stats.Gambling.Cards.WinMoney + ")");
		Log_Info(XI_ConvertString("BoalGameMoneyLose") + ": " + TEV.Gambling.LoseMoney + " (" + GetStrSmallRegister(XI_ConvertString("Total")) + " " + TEV.Stats.Gambling.Cards.LoseMoney + ")");
		
		TEV.Gambling.Diff = makeint(TEV.Gambling.WinMoney) - makeint(TEV.Gambling.LoseMoney);
		TEV.Gambling.DiffAll = makeint(TEV.Stats.Gambling.Cards.WinMoney) - makeint(TEV.Stats.Gambling.Cards.LoseMoney);
		
		if (sti(TEV.Gambling.Diff) > 0)
			TEV.Gambling.Diff.Plus = "+";
		
		if (sti(TEV.Gambling.DiffAll) > 0)
			TEV.Gambling.DiffAll.Plus = "+";
		
		Log_Info(XI_ConvertString("BoalGameDifference") + ": " + TEV.Gambling.Diff.Plus + FindMoneyString(sti(TEV.Gambling.Diff)) + " (" + GetStrSmallRegister(XI_ConvertString("Total")) + " " + TEV.Gambling.DiffAll.Plus + FindMoneyString(sti(TEV.Gambling.DiffAll))  + ")");
	}
	else
	{
		Log_Info(XI_ConvertString("BoalGameCardWin") + ": " + iHeroWin);
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
    DelEventHandler("My_eOpenCards","OpenCards");
	
	if (sti(pchar.GenQuest.Cards.SitType) == true)
	{
		DoQuestCheckDelay("exit_sit", 0.6);
	}
	interfaceResultCommand = RC_INTERFACE_SALARY_EXIT;
	
    Statistic_AddValue(Pchar, "GameCards_Win", iHeroWin);
    AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*5*iHeroWin);
    AddCharacterExpToSkill(Pchar, SKILL_FORTUNE, iExpRate*2*iHeroLose);
    Statistic_AddValue(Pchar, "GameCards_Lose", iHeroLose);
	
	if(!CheckCardsGameSmallRate()) SetCharacterPerk(pchar, "SaveLoadAbuser");
	if(CheckCharacterPerk(pchar, "SaveLoadAbuser") && CheckCardsGameSmallRate()) DeleteTrait(pchar, "SaveLoadAbuser");
    
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
                        SetFormatedText("INFO_TEXT", XI_ConvertString("BoalGameNoMoney") + GetLangSexPhrase("ий","ая"));
                        break;
                    }
                    if (dir_i == -1 && (iMoneyN - iRate) < 0)
                    {
                        PlaySound("knock");
                        SetFormatedText("INFO_TEXT", XI_ConvertString("BoalGameNPCNoMoney"));
                        break;
                    }
                    
                    if (dir_i == 1)
                    {
						if (cardMove) { // mitrokosta фикс множественного взятия
							break;
						} else {
							cardMove = true; // начинаем перемещение
						}
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
                    }
                    /*
                    else
                    {
                        PutNextCoinOp();
                        moneyOp_i++;
                        iMoneyN = iMoneyN - iRate;
                        iChest += iRate;
                        howCard--;
                        cardsN[howNpchar] = cardsPack[howCard];
                        howNpchar++;
                    }  */
                    ShowMoney();
                }
    		}
    	break;
    	
    	case "B_ICON_1":
    		if(comName=="activate" || comName=="click")
    		{
                if (dir_i == 1 && bStartGame != 100 && bStartGame > 1 && !openExit) // только передача хода или открываемся
                {
					SetCardTip("");
                    dir_i = -1; // смена хода
                    SetNextTip();
                    if (dir_i_start == -1)// комп начинал игру первый
                    {
                        SetFormatedText("INFO_TEXT", XI_ConvertString("BoalGameOpenCard"));
                        bStartGame = 100;
                        PostEvent("My_eOpenCards", 2000);
                    }
                    else
                    {// комп должен себе набрать
                        SetFormatedText("INFO_TEXT", XI_ConvertString("BoalGameNPCGetCard"));
                        
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
	GetNodePosition("B_PACK", &x1, &y1, &x2, &y2);

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
	
	string sCard;
	if(t > 0.5)	// карты в руке плавно сдвигаются влево
	{
		if(dir_i > 0)
		{
			for (i = 0; i < n - 1; i++)
			{
				x1 = 220 - (n - 1) * k / 2 + i * k;
				x2 = 240 - n * k / 2 + i * k;
				x = 150 + makeint(x1 + (x2 - x1) * (t - 0.5) * 2.0);
				sCard = "c"+cardsP[i];
				CreateImage("PCard"+i, "CARDS", NullCharacter.Cards.(sCard).pic, x, 390, x + scx, 390 + scy);
			}
		}
		else
		{
			for (i = 0; i < n - 1; i++)
			{
				x1 = 220 - (n - 1) * k / 2 + i * k;
				x2 = 240 - n * k / 2 + i * k;
				x = 150 + makeint(x1 + (x2 - x1) * (t - 0.5) * 2.0);
				CreateImage("PCard" + (18 + i), "CARDS", "blank", x, 40, x + scx, 40 + scy);
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
        BetaInfo();
        CheckGame();
		if(bStartGame >= 2 && dir_i == 1)
			SetCardTip("action");
    }
}

void PutNextCoin()
{
    CreateImage("Money_"+money_i,"CARDS",money_s, 280+money_i*3, 280-money_i*3, 280+money_i*3 + smxy, 280-money_i*3 + smxy);
}
void PutNextCoinOp()
{
    CreateImage("Money_"+(18+moneyOp_i),"CARDS",money_s, 380+moneyOp_i*3, 280-moneyOp_i*3, 380+moneyOp_i*3 + smxy, 280-moneyOp_i*3 + smxy);
}

void PackShake()
{
    // тасуем карты
    int  i;
    bool ok;
    int  nextCard;
    
    howCard = 0;
    while (howCard <36)
    {
        ok = false;
        while (!ok)
        {
            ok = true;
            nextCard = rand(35)+1;
            for (i=0; i<howCard; i++)
        	{
                if (nextCard == cardsPack[i])
                {
                    ok = false;
                    break;
                }
        	}
        	if (ok)
        	{
                cardsPack[howCard] = nextCard;
                //log_info(""+nextCard);
                howCard++;
                
        	}
    	}
    }
    /*howCard = 36;
    for (i=0; i<howCard; i++)
	{
        cardsPack[i] = i-20;
	}*/
}
void RedrawCards()
{
    int i;
    string sTemp;
    int k;
    k = scx;
    if (howPchar > 6)
    {
        k = scx/2;
    }
    for (i=0; i<howPchar; i++)
	{
        sTemp = "c"+cardsP[i];
        CreateImage("PCard"+i,"CARDS", NullCharacter.Cards.(sTemp).pic, 390 - howPchar*k/2 + i*k , 390, 390 - howPchar*k/2 + i*k + scx, 390 + scy);
	}
	k = scx;
	if (howNpchar > 6)
    {
        k = scx/2;
    }
	for (i=0; i<howNpchar; i++)
	{
        sTemp = "c"+cardsN[i];
        sTemp = NullCharacter.Cards.(sTemp).pic;
        if (!openExit)
        {
            sTemp = "blank";
        }
        CreateImage("PCard"+(18+i),"CARDS", sTemp, 390 - howNpchar*k/2 + i*k , 40, 390 - howNpchar*k/2 + i*k + scx, 40 + scy);
	}
}
void RedrawDeck()
{
	// монетки с запасом
	int i;
	for (i=35; i>=0; i--)
	{
        CreateImage("Money_" + i, "", "", 0, 0, 0, 0);
        CreateImage("PCard" + i, "", "", 0, 0, 0, 0);
	}
	money_i = 0; // индекс монетки
	moneyOp_i = 0;
	iChest = 0; // на кону

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
            SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameGetCard")+NewStr()+XI_ConvertString("BoalGameBet"));
			SetFormatedText("B_TEXT_1", "");
        }
        else
        {
            SetFormatedText("INFO_TEXT",LinkRandPhrase(XI_ConvertString("BoalGameTurn_1"), XI_ConvertString("BoalGameTurn_2"), RandSwear() + " " + XI_ConvertString("BoalGameTurn_3")));
			SetFormatedText("B_TEXT_1", XI_ConvertString("BoalGameEndTurn"));
        }
    }
    else
    {
		SetFormatedText("B_TEXT_1", "");
        if (bStartGame <2)
        {
            SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameGetCard2")+NewStr()+XI_ConvertString("BoalGameMoneyBet"));
        }
        else
        {
            SetFormatedText("INFO_TEXT",LinkRandPhrase(XI_ConvertString("BoalGameTurnNPC_1"), XI_ConvertString("BoalGameTurnNPC_2"), XI_ConvertString("BoalGameTurnNPC_3")));
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
    if (bBettaTestMode)
    {
        GameInterface.strings.Beta_P       = "Beta_P " + CountCardsP();
        GameInterface.strings.Beta_N       = "Beta_N " + CountCardsN();
        GameInterface.strings.Beta_Next    = "Beta_Next " + NextCardPack();
        GameInterface.strings.Beta_MoneyN  = "Beta_MoneyN " + MakeMoneyShow(iMoneyN, MONEY_SIGN,MONEY_DELIVER);
        GameInterface.strings.Beta_WinLose = "Beta Win " + (Statistic_AddValue(Pchar, "GameCards_Win", 0)+iHeroWin) + " Lose " + (Statistic_AddValue(Pchar, "GameCards_Lose", 0)+iHeroLose);
    }
	
	if (CountCardsP() > 0)
		GameInterface.strings.CountCardsPlayer = "" + CountCardsP();
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
int NextCardPack()
{
    string sTemp;
    int ret;
    
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
	SetFormatedText("B_TEXT_1", "");

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
    ShowMoney();
}

void ShowMoney()
{
	WaitDate("", 0, 0, 0, 0, 1);
	SetFormatedText("TIME_TEXT", "" + GetQuestBookData());
	SetFormatedText("STATS_TIME_TEXT", "" + GetSessionTime());
    GameInterface.strings.Money        = MakeMoneyShow(iMoneyP,MONEY_SIGN,MONEY_DELIVER);
    GameInterface.strings.MoneyInChest = MakeMoneyShow(iChest,MONEY_SIGN,MONEY_DELIVER);
}

bool CheckGame()
{
    string sTemp;
    int   ok = 0;
    bool  ok1;
    bool  ret = false;
    
    if (CountCardsP() > 21)
    {
        ok = -1;
        sTemp = XI_ConvertString("BoalGameCheckGame_1");
        iHeroLose++;
    }
    if (CountCardsN() > 21)
    {
        ok = 1;
        sTemp = RandSwear() + " " + XI_ConvertString("BoalGameCheckGame_2")+ GetLangSexPhrase("","а") +".";
        iHeroWin++;
    }
    if (ok != 0)
    {
		SetFormatedText("B_TEXT_1", "");
        EndGameCount(ok);
        if (ok == 1) RedrawCards(); // покажем перебор
        
        if (CheckNextGame() && rand(10) < 10) // есть деньги на игру
        {
            sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("BoalGameCheckGame_3"), XI_ConvertString("BoalGameCheckGame_4"));
        }
        else
        {
            bStartGame = 100;//признак запрета новой игры
            npchar.game_over = true;
            sTemp += NewStr() + XI_ConvertString("BoalGameCheckGame_5");
        }
        SetFormatedText("INFO_TEXT", sTemp);
        ret = true;
		SetCardTip("");
		SetCardTip("restart");
    }
    else
    {
		bool bChecker = (GetCharacterSPECIAL(pchar, SPECIAL_P) > 3) || (GetOfficersPerkUsing(pchar, "HawkEye", true));
        ok1 = (CountCardsN() > 16) && (CountCardsN() <22);
        // жухло!!!!! -->
        if (!bChecker && GetCharacterSkillToOld(pchar, SKILL_FORTUNE) < rand(12))
        {
            if (ok1 && (CountCardsN() + NextCardPack()) <= 21)
            {
                ok1 = false;
            }
            if (GetCharacterSkillToOld(pchar, SKILL_FORTUNE) < rand(10) && CountCardsN() < 17 &&  (CountCardsN() + NextCardPack()) > 21)
            {
                ok1 = true;
            }
        }
        // жухло!!!!! <--
        
        if (ok1 || (iMoneyN - iRate) < 0)
        {
            if (dir_i == -1 && dir_i_start == 1)// комп ходит последним
            {
                SetFormatedText("INFO_TEXT", XI_ConvertString("BoalGameCheckGame_6"));
				SetFormatedText("B_TEXT_1", "");
                bStartGame = 100;
				SetCardTip("");
                PostEvent("My_eOpenCards", 2000);
                ret = true;
            }
            if (dir_i == -1 && dir_i_start == -1)// комп начинает
            {
                dir_i = 1;
                SetFormatedText("INFO_TEXT", XI_ConvertString("BoalGameCheckGame_7"));
				SetFormatedText("B_TEXT_1", XI_ConvertString("BoalGameEndTurn"));
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
                ShowMoney();
                
                ret = true;
            }
        }
    }
	BetaInfo();
    return ret;
}

void NewGameBegin()
{
	SetCardTip("");
	WaitDate("", 0, 0, 0, 0, 1 + (rand(4)));
	SetFormatedText("TIME_TEXT", "" + GetQuestBookData());
	SetFormatedText("STATS_TIME_TEXT", "" + GetSessionTime());
    RedrawDeck(); // новая игра
    bStartGame = 0;
    SetFormatedText("INFO_TEXT",XI_ConvertString("BoalGameGetCards") + " "+NewStr()+XI_ConvertString("BoalGameBets"));
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
}

void OpenCards()
{
    string sTemp;
	SetFormatedText("B_TEXT_1", "");
    if (CountCardsP() > makefloat(CountCardsN() + 0.1 * dir_i_start)) // преимущество тому, кто сдает (те ходит последним)
    {
        EndGameCount(1);
        sTemp = RandSwear() + " " + XI_ConvertString("BoalGameOpenCards_1") + GetLangSexPhrase("","а") + ". " + UpperFirst(XI_ConvertString("BoalGameOpenCards_2")) + " " + CountCardsP() + ", " + XI_ConvertString("BoalGameOpenCards_3") + " " + CountCardsN() + "." ;
        iHeroWin++;
    }
    else
    {
        EndGameCount(-1);
        sTemp = XI_ConvertString("BoalGameOpenCards_4") + " " + XI_ConvertString("BoalGameOpenCards_3") + " " + CountCardsN() + ", " + XI_ConvertString("BoalGameOpenCards_2") + " " + CountCardsP() + ". " + XI_ConvertString("BoalGameOpenCards_5");
        iHeroLose++;
    }
	SetCardTip("");
    if (CheckNextGame() && rand(10) < 10) // есть деньги на игру
    {
		SetCardTip("action");
        sTemp += NewStr() + RandPhraseSimple(XI_ConvertString("BoalGameCheckGame_3"), XI_ConvertString("BoalGameCheckGame_4"));
        bStartGame = 2;
    }
    else
    {
        bStartGame = 100;//признак запрета новой игры
        npchar.game_over = true;
        sTemp += NewStr() + XI_ConvertString("BoalGameCheckGame_5");
    }
    SetFormatedText("INFO_TEXT", sTemp);
    RedrawCards();
	BetaInfo();
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
				if(dir_i_start == 1)	// передача хода - портрет
				{
					SetPictureBlind("ICON_1", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
				}
				else	// вскрываемся - портрет
				{
					SetPictureBlind("ICON_1", true, argb(255, 95, 95, 95), argb(255, 155, 155, 155), 0.6, 0.6);
				}
			}
		break;
	}
}

// BOAL меню наций
#event_handler("Control Activation", "ProcessInterfaceControls"); // обработка нажатия клавы

int curNationIdx;
string _fileName = "RESOURCE\INI\INTERFACES\NationRelation.ini";
int gLngRPGDescribe = -1;

void InitInterface(string iniName)
{
    InterfaceStack.SelectMenu_node = "LaunchNationRelation"; // запоминаем, что звать по Ф2

    gLngRPGDescribe = LanguageOpenFile("RPGDescribe.txt");
	
	TableNationRelation();
	
	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);
	
	ref chref = GetMainCharacter();
    
	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("FlagsPress","FlagsProcess",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("MouseRClickUP","HideInfo",0);
	SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
    
    /////////////

	CreateString(true,"titul", XI_ConvertString("Hunter_type"),"DIALOG2",COLOR_NORMAL,700,69,SCRIPT_ALIGN_CENTER,1.0); //при включении BetTest
    CreateString(true,"EngH","","INTERFACE_ULTRASMALL",COLOR_NORMAL,700,134,SCRIPT_ALIGN_CENTER,1.0);
    CreateString(true,"FraH","","INTERFACE_ULTRASMALL",COLOR_NORMAL,700,190,SCRIPT_ALIGN_CENTER,1.0);
    CreateString(true,"SpaH","","INTERFACE_ULTRASMALL",COLOR_NORMAL,700,246,SCRIPT_ALIGN_CENTER,1.0);
    CreateString(true,"HolH","","INTERFACE_ULTRASMALL",COLOR_NORMAL,700,302,SCRIPT_ALIGN_CENTER,1.0);
	
	SetFormatedText("NATION_RELATION_CAPTION", XI_ConvertString("NationRelationToPchar"));
	SetFormatedText("SHIP_FLAG_CAPTION", XI_ConvertString("ChangeFlag") + " " + XI_ConvertString("Continuous music ship"));

	// доп инфа в шапку --->
	SetFormatedText("WEIGHT", FloatToString(GetItemsWeight(chref), 1) + " / " + GetMaxItemsWeight(chref));
	SetFormatedText("MONEY", FindMoneyString(sti(chref.money)));
	SetFormatedText("CURRENT_DATE_CAPTION", GetDateString() + " "+ GetTimeString());
	// <--

    CalculateHunter();
	
    curNationIdx = sti(chref.nation);
    SetNewNation(0);
	XI_RegistryExitKey("NationsMenu");
	SetAlertMarks(chref);
}

void CalculateHunter()
{

     ref mc = GetMainCharacter();

     SetFormatedText("NATION_RELATION_ENGLAND", XI_ConvertString("England") + "\n\n" + GetNationReputation(pchar, ENGLAND));
     SetFormatedText("NATION_RELATION_FRANCE", XI_ConvertString("France") + "\n\n" + GetNationReputation(pchar, FRANCE));
     SetFormatedText("NATION_RELATION_SPAIN", XI_ConvertString("Spain") + "\n\n" + GetNationReputation(pchar, SPAIN));
     SetFormatedText("NATION_RELATION_HOLLAND", XI_ConvertString("Holland") + "\n\n" + GetNationReputation(pchar, HOLLAND));
	 
	 SetVAligmentFormatedText("NATION_RELATION_ENGLAND");
	 SetVAligmentFormatedText("NATION_RELATION_FRANCE");
	 SetVAligmentFormatedText("NATION_RELATION_SPAIN");
	 SetVAligmentFormatedText("NATION_RELATION_HOLLAND");
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
    DelEventHandler("FlagsPress","FlagsProcess");
    DelEventHandler("ievnt_command","ProcessCommandExecute");
    DelEventHandler("MouseRClickUP","HideInfo");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");

	if (gLngRPGDescribe >= 0) { LanguageCloseFile(gLngRPGDescribe); gLngRPGDescribe = -1; }

	interfaceResultCommand = exitCode;
	if( CheckAttribute(&InterfaceStates,"ReloadMenuExit"))
	{
        DeleteAttribute(&InterfaceStates,"ReloadMenuExit");
		EndCancelInterface(false);
	}
	else
	{
		EndCancelInterface(true);
	}
}

void TableNationRelation()
{
	int WidthIcons = 60;
	int HeightIcons = 60;
	string OffsetIcons = "4,7";
	
	// int WidthIcons = 65;
	// int HeightIcons = 65;
	// string OffsetIcons = "4,6";
	
	GameInterface.TABLE_NATIONS.hr.td1.str = "";
	GameInterface.TABLE_NATIONS.hr.td1.scale = 0.0;
 	GameInterface.TABLE_NATIONS.hr.td2.icon.group = "NATIONS";
	GameInterface.TABLE_NATIONS.hr.td2.icon.image = Nations[0].Name;
	GameInterface.TABLE_NATIONS.hr.td2.icon.width = WidthIcons;
    GameInterface.TABLE_NATIONS.hr.td2.icon.height = HeightIcons;
    GameInterface.TABLE_NATIONS.hr.td2.icon.offset = OffsetIcons;
 	GameInterface.TABLE_NATIONS.hr.td3.icon.group = "NATIONS";
	GameInterface.TABLE_NATIONS.hr.td3.icon.image = Nations[1].Name;
	GameInterface.TABLE_NATIONS.hr.td3.icon.width = WidthIcons;
    GameInterface.TABLE_NATIONS.hr.td3.icon.height = HeightIcons;
    GameInterface.TABLE_NATIONS.hr.td3.icon.offset = OffsetIcons;
	GameInterface.TABLE_NATIONS.hr.td4.icon.group = "NATIONS";
	GameInterface.TABLE_NATIONS.hr.td4.icon.image = Nations[2].Name;
	GameInterface.TABLE_NATIONS.hr.td4.icon.width = WidthIcons;
    GameInterface.TABLE_NATIONS.hr.td4.icon.height = HeightIcons;
    GameInterface.TABLE_NATIONS.hr.td4.icon.offset = OffsetIcons;
	GameInterface.TABLE_NATIONS.hr.td5.icon.group = "NATIONS";
	GameInterface.TABLE_NATIONS.hr.td5.icon.image = Nations[3].Name;
	GameInterface.TABLE_NATIONS.hr.td5.icon.width = WidthIcons;
    GameInterface.TABLE_NATIONS.hr.td5.icon.height = HeightIcons;
    GameInterface.TABLE_NATIONS.hr.td5.icon.offset = OffsetIcons;
	GameInterface.TABLE_NATIONS.hr.td6.icon.group = "NATIONS";
	GameInterface.TABLE_NATIONS.hr.td6.icon.image = Nations[4].Name;
	GameInterface.TABLE_NATIONS.hr.td6.icon.width = WidthIcons;
    GameInterface.TABLE_NATIONS.hr.td6.icon.height = HeightIcons;
    GameInterface.TABLE_NATIONS.hr.td6.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr1.td1.icon.group = "NATIONS";
	GameInterface.TABLE_NATIONS.tr1.td1.icon.image = Nations[0].Name;
	GameInterface.TABLE_NATIONS.tr1.td1.icon.width = WidthIcons;
    GameInterface.TABLE_NATIONS.tr1.td1.icon.height = HeightIcons;
    GameInterface.TABLE_NATIONS.tr1.td1.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr1.td2.str = "";
	GameInterface.TABLE_NATIONS.tr1.td2.scale = 0.0;

	GameInterface.TABLE_NATIONS.tr1.td3.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr1.td3.icon.image = GetRelationName(GetNationRelation(0, 1));
	GameInterface.TABLE_NATIONS.tr1.td3.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr1.td3.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr1.td3.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr1.td4.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr1.td4.icon.image = GetRelationName(GetNationRelation(0, 2));
	GameInterface.TABLE_NATIONS.tr1.td4.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr1.td4.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr1.td4.icon.offset = OffsetIcons;
				
	GameInterface.TABLE_NATIONS.tr1.td5.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr1.td5.icon.image = GetRelationName(GetNationRelation(0, 3));
	GameInterface.TABLE_NATIONS.tr1.td5.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr1.td5.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr1.td5.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr1.td6.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr1.td6.icon.image = GetRelationName(GetNationRelation(0, 4));
	GameInterface.TABLE_NATIONS.tr1.td6.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr1.td6.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr1.td6.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr2.td1.icon.group = "NATIONS";
	GameInterface.TABLE_NATIONS.tr2.td1.icon.image = Nations[1].Name;
	GameInterface.TABLE_NATIONS.tr2.td1.icon.width = WidthIcons;
    GameInterface.TABLE_NATIONS.tr2.td1.icon.height = HeightIcons;
    GameInterface.TABLE_NATIONS.tr2.td1.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr2.td2.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr2.td2.icon.image = GetRelationName(GetNationRelation(1, 0));
	GameInterface.TABLE_NATIONS.tr2.td2.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr2.td2.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr2.td2.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr2.td3.str = "";
	GameInterface.TABLE_NATIONS.tr2.td3.scale = 0.0;
	
	GameInterface.TABLE_NATIONS.tr2.td4.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr2.td4.icon.image = GetRelationName(GetNationRelation(1, 2));
	GameInterface.TABLE_NATIONS.tr2.td4.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr2.td4.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr2.td4.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr2.td5.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr2.td5.icon.image = GetRelationName(GetNationRelation(1, 3));
	GameInterface.TABLE_NATIONS.tr2.td5.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr2.td5.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr2.td5.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr2.td6.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr2.td6.icon.image = GetRelationName(GetNationRelation(1, 4));
	GameInterface.TABLE_NATIONS.tr2.td6.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr2.td6.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr2.td6.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr3.td1.icon.group = "NATIONS";
	GameInterface.TABLE_NATIONS.tr3.td1.icon.image = Nations[2].Name;
	GameInterface.TABLE_NATIONS.tr3.td1.icon.width = WidthIcons;
    GameInterface.TABLE_NATIONS.tr3.td1.icon.height = HeightIcons;
    GameInterface.TABLE_NATIONS.tr3.td1.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr3.td2.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr3.td2.icon.image = GetRelationName(GetNationRelation(2, 0));
	GameInterface.TABLE_NATIONS.tr3.td2.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr3.td2.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr3.td2.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr3.td3.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr3.td3.icon.image = GetRelationName(GetNationRelation(2, 1));
	GameInterface.TABLE_NATIONS.tr3.td3.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr3.td3.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr3.td3.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr3.td4.str = "";
	GameInterface.TABLE_NATIONS.tr3.td4.scale = 0.0;
	
	GameInterface.TABLE_NATIONS.tr3.td5.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr3.td5.icon.image = GetRelationName(GetNationRelation(2, 3));
	GameInterface.TABLE_NATIONS.tr3.td5.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr3.td5.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr3.td5.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr3.td6.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr3.td6.icon.image = GetRelationName(GetNationRelation(2, 4));
	GameInterface.TABLE_NATIONS.tr3.td6.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr3.td6.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr3.td6.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr4.td1.icon.group = "NATIONS";
	GameInterface.TABLE_NATIONS.tr4.td1.icon.image = Nations[3].Name;
	GameInterface.TABLE_NATIONS.tr4.td1.icon.width = WidthIcons;
    GameInterface.TABLE_NATIONS.tr4.td1.icon.height = HeightIcons;
    GameInterface.TABLE_NATIONS.tr4.td1.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr4.td2.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr4.td2.icon.image = GetRelationName(GetNationRelation(3, 0));
	GameInterface.TABLE_NATIONS.tr4.td2.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr4.td2.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr4.td2.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr4.td3.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr4.td3.icon.image = GetRelationName(GetNationRelation(3, 1));
	GameInterface.TABLE_NATIONS.tr4.td3.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr4.td3.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr4.td3.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr4.td4.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr4.td4.icon.image = GetRelationName(GetNationRelation(3, 2));
	GameInterface.TABLE_NATIONS.tr4.td4.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr4.td4.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr4.td4.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr4.td5.str = "";
	GameInterface.TABLE_NATIONS.tr4.td5.scale = 0.0;
	
	GameInterface.TABLE_NATIONS.tr4.td6.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr4.td6.icon.image = GetRelationName(GetNationRelation(3, 4));
	GameInterface.TABLE_NATIONS.tr4.td6.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr4.td6.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr4.td6.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr5.td1.icon.group = "NATIONS";
	GameInterface.TABLE_NATIONS.tr5.td1.icon.image = Nations[4].Name;
	GameInterface.TABLE_NATIONS.tr5.td1.icon.width = WidthIcons;
    GameInterface.TABLE_NATIONS.tr5.td1.icon.height = HeightIcons;
    GameInterface.TABLE_NATIONS.tr5.td1.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr5.td2.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr5.td2.icon.image = GetRelationName(GetNationRelation(4, 0));
	GameInterface.TABLE_NATIONS.tr5.td2.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr5.td2.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr5.td2.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr5.td3.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr5.td3.icon.image = GetRelationName(GetNationRelation(4, 1));
	GameInterface.TABLE_NATIONS.tr5.td3.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr5.td3.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr5.td3.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr5.td4.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr5.td4.icon.image = GetRelationName(GetNationRelation(4, 2));
	GameInterface.TABLE_NATIONS.tr5.td4.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr5.td4.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr5.td4.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr5.td5.icon.group = "RELATIONS";
	GameInterface.TABLE_NATIONS.tr5.td5.icon.image = GetRelationName(GetNationRelation(4, 3));
	GameInterface.TABLE_NATIONS.tr5.td5.icon.width = WidthIcons;
	GameInterface.TABLE_NATIONS.tr5.td5.icon.height = HeightIcons;
	GameInterface.TABLE_NATIONS.tr5.td5.icon.offset = OffsetIcons;
	
	GameInterface.TABLE_NATIONS.tr5.td6.str = "";
	GameInterface.TABLE_NATIONS.tr5.td6.scale = 0.0;
}

void ShowInfoWindow()
{
	string sHeader = "TEST";
	string sNode = GetCurrentNode();

	string sText1, sText2, sText3, sPicture, sGroup, sGroupPicture;
	sPicture = "none";
	sGroup = "none";
	sGroupPicture = "none";

	switch(sNode)
	{
		case "FlagPic":
			sHeader = XI_ConvertString("Nation");
			sText1 = GetRPGText("Nation_hint");
		break;
		
		case "INFO_CLICK":
			sHeader = XI_ConvertString("Hunter_type");
			sText1 = GetRPGText("Hunter_hint");
		break;

		case "WEIGHT":
			sHeader = XI_ConvertString("Weight");
			sText1 = GetRPGText("Weight_hint");
		break;

		case "MONEY":
			sHeader = XI_ConvertString("Money");
			sText1 = GetRPGText("Money_hint");
		break;
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,255,255,255), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);
}

void HideInfo()
{
	CloseTooltip();
	SetCurrentNode("OK_BUTTON");
}

void FlagsProcess()
{
	if (CheckAttribute(pchar, "questTemp.AoP.ForcePirateFlag"))
	{
		PlaySound("knock");
		return;
	}
	// boal 04.04.2004 -->
	bool bTmpBool = true;
	int i, cn;
	ref chref;
	
	if (CheckAttribute(pchar, "DisableChangeFlagMode")) return; // нефиг менять файл за 3 секунды сразу
	
	if (!bBettaTestMode)
	{
    	//if(LAi_group_IsActivePlayerAlarm()) bTmpBool = false;
    	//if(!LAi_IsCharacterControl(GetMainCharacter())) bTmpBool = false;
    	if (bLandInterfaceStart)  bTmpBool = false; // на суше нельзя в принципе
    	if (bSeaActive && !CheckEnemyCompanionDistance2GoAway(false)) bTmpBool = false; // компаньон под ударом
        // проверка класса кораблей в эскадре -->
        /*for (i=0; i<4; i++)
    	{
    		cn = GetCompanionIndex(GetMainCharacter(), i);
    		if ( cn>=0 )
    		{
    			chref = GetCharacter(cn);
                if (GetCharacterShipClass(chref) <= 2) bTmpBool = false;
    		}
    	}  */
        // проверка класса кораблей в эскадре <--
	}
	if (bDisableMapEnter || !bTmpBool)
	{
        if (!bBettaTestMode)
        {
            PlaySound("knock");
            return;
        }
	}
	// смена флага
	Sea_ClearCheckFlag(); // сбросить всем в море проверку смотрения на флаг.
	pchar.DisableChangeFlagMode = true; //закрываем Флаг
	DoQuestFunctionDelay("FreeChangeFlagMode", 15.0); // ролик + запас
	
	switch (curNationIdx)
	{
    	case ENGLAND:	EnglandProcess();	break;
    	case FRANCE:	FranceProcess();	break;
    	case SPAIN:		SpainProcess();	break;
    	case PIRATE:	PirateProcess();	break;
    	case HOLLAND:	HollandProcess();	break;
	}
}

void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
        case "LEFTCHANGE_NATION":
    		if(comName=="activate" || comName=="click")
    		{
				if (!CheckAttribute(pchar, "DisableChangeFlagMode"))
				{
					SetNewNation(-1);
				}
    		}
    	break;

    	case "RIGHTCHANGE_NATION":
    		if(comName=="activate" || comName=="click")
    		{
                if (!CheckAttribute(pchar, "DisableChangeFlagMode"))
                {
					SetNewNation(1);
				}
    		}
    	break;
		case "I_CHARACTER_2":
			if(comName=="click")
			{
			    nodName = "I_CHARACTER";
			}
		break;
		case "I_SHIP_2":
			if(comName=="click")
			{
			    nodName = "I_SHIP";
			}
		break;
		case "I_QUESTBOOK_2":
			if(comName=="click")
			{
			    nodName = "I_QUESTBOOK";
			}
		break;
		case "I_ALCHEMY_2":
			if(comName=="click")
			{
			    nodName = "I_ALCHEMY";
			}
		break;
		case "I_NATIONS_2":
			if(comName=="click")
			{
			    nodName = "I_NATIONS";
			}
		break;
		case "I_ITEMS_2":
			if(comName=="click")
			{
			    nodName = "I_ITEMS";
			}
		break;
	}
	// boal new menu 31.12.04 -->
	if (nodName == "I_CHARACTER" || nodName == "I_SHIP" ||
	    nodName == "I_QUESTBOOK" || nodName == "I_ALCHEMY" ||
		nodName == "I_NATIONS" || nodName == "I_ITEMS")
	{
		if(comName=="click")
		{
            InterfaceStates.ReloadMenuExit = true;
			IDoExit(RC_INTERFACE_ANY_EXIT);
			PostEvent("LaunchIAfterFrame",1,"sl", nodName, 2);
			return;
		}
	}
	// boal new menu 31.12.04 -->
}
void SetNewNation(int add)
{
    ref   mchar = GetMainCharacter();
    bool  ok, ok2;
	 if (CheckAttribute(pchar, "questTemp.AoP.ForcePirateFlag"))
    {
        curNationIdx = PIRATE;
        SetNewGroupPicture("FlagPic", "NATIONS", GetNationNameByType(PIRATE));
        SetSelectable("FLAGS", false);
        SetNodeUsing("RIGHTCHANGE_NATION", false);
        SetNodeUsing("LEFTCHANGE_NATION", false);
        return;
    }
    
    curNationIdx = curNationIdx + add;
    if (curNationIdx < 0) curNationIdx = 4;
    if (curNationIdx > 4) curNationIdx = 0;
    //CreateImage("FlagPic", "NATIONS",GetNationNameByType(curNationIdx), 648, 455, 715, 522);
    SetNewGroupPicture("FlagPic", "NATIONS", GetNationNameByType(curNationIdx));
    
    if (IsCharacterPerkOn(mchar,"FlagPir")  ||
	    IsCharacterPerkOn(mchar,"FlagEng")  ||
		IsCharacterPerkOn(mchar,"FlagFra")  ||
		IsCharacterPerkOn(mchar,"FlagSpa")  ||
		IsCharacterPerkOn(mchar,"FlagHol"))
    {
        SetSelectable("FLAGS",true);
        ok  = !IsCharacterPerkOn(mchar,"Flag" + NationShortName(curNationIdx)) && (sti(mchar.nation) != curNationIdx);
        ok2 =  true;
        if (isMainCharacterPatented())
        {
            ok2 = (sti(Items[sti(mchar.EquipedPatentId)].Nation) != curNationIdx);
        }
        if (ok && ok2)
        {
            SetNewNation(add);
        }
        if (sti(mchar.nation) == curNationIdx)
        {
            SetSelectable("FLAGS",false);
        }
    }
    else
    {
        SetSelectable("FLAGS",false);
	    SetNodeUsing("RIGHTCHANGE_NATION",false);
	    SetNodeUsing("LEFTCHANGE_NATION",false);
    }
}
void PirateProcess()
{
    //DoQuestCheckDelay("pir_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "Pirate";
    PChar.GenQuest.VideoAfterQuest = "pir_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
	ProcessExitCancel();
}

void EnglandProcess()
{
    //DoQuestCheckDelay("eng_flag_rise", 1.0);
    PChar.GenQuest.VideoAVI        = "England";
    PChar.GenQuest.VideoAfterQuest = "eng_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
    ProcessExitCancel();
}

void FranceProcess()
{
    PChar.GenQuest.VideoAVI        = "France";
    PChar.GenQuest.VideoAfterQuest = "fra_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
	ProcessExitCancel();
}

void SpainProcess()
{
    PChar.GenQuest.VideoAVI        = "Spain";
    PChar.GenQuest.VideoAfterQuest = "spa_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
    ProcessExitCancel();
}

void HollandProcess()
{
    PChar.GenQuest.VideoAVI        = "Holland";
    PChar.GenQuest.VideoAfterQuest = "hol_flag_rise";

    DoQuestCheckDelay("PostVideo_Start", 0.2);
	ProcessExitCancel();
}

// обработка нажатия клавы
void ProcessInterfaceControls()
{
	string controlName = GetEventData();

	if (controlName == "InterfaceGoLeft")
	{
		IDoExit(RC_INTERFACE_TO_ITEMS);
	}
	if (controlName == "InterfaceGoRight")
	{
		IDoExit(INTERFACE_CHARACTER_ALL);
	}
	if (controlName == "CharacterShipMenu")
	{
		IDoExit(RC_INTERFACE_TO_SHIP);
	}
	if (controlName == "LogbookMenu")
	{
		IDoExit(RC_INTERFACE_TO_LOGBOOK);
	}
	if (controlName == "ItemsMenu")
	{
		IDoExit(RC_INTERFACE_TO_ITEMS);
	}
	if (controlName == "AlchemyKey")
	{
		IDoExit(RC_INTERFACE_TO_ALCHEMY);
	}
	if (controlName == "Interface")
	{
		IDoExit(INTERFACE_CHARACTER_ALL);
	}
}
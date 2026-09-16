// BOAL меню персонажи
ref xi_refCharacter;
int nCurScrollNum, nCurScrollOfficerNum;
string CurTable, CurRow;
int iSelected; // курсор в таблице
bool bChangePIRATES, bAddPIRATES; // evganat - пасха
bool bAllSelf = false;
bool bAllShip = false;
string sPerkMode = "perks";	// evganat - черты

int gLngAbilityDescribe = -1;
int gLngRPGDescribe = -1;

void InitInterface_R(string iniName, ref _char)
{
	xi_refCharacter = _char;
	GameInterface.title = "titleCharacter";

	gLngAbilityDescribe = LanguageOpenFile("AbilityDescribe.txt");
	gLngRPGDescribe = LanguageOpenFile("RPGDescribe.txt");

    bChangePIRATES = false;
	if (CheckAttribute(xi_refCharacter, "SystemInfo.ChangePIRATES"))
	{
		bChangePIRATES = true;
		DeleteAttribute(xi_refCharacter, "SystemInfo.ChangePIRATES");
	}

	// evganat - пасха
	bAddPIRATES = false;
    if (CheckAttribute(xi_refCharacter, "SystemInfo.AddPIRATES"))
    {
		bAddPIRATES = true;
		DeleteAttribute(xi_refCharacter, "SystemInfo.AddPIRATES");
	}
	
	GameInterface.StatusLine.LOYALITY.Max = 1;
    GameInterface.StatusLine.LOYALITY.Min = 0;
    GameInterface.StatusLine.LOYALITY.Value = 0;

	SendMessage(&GameInterface,"ls",MSG_INTERFACE_INIT,iniName);

	SetEventHandler("InterfaceBreak","ProcessExitCancel",0);
	SetEventHandler("exitCancel","ProcessExitCancel",0);
    SetEventHandler("ievnt_command","ProcessCommandExecute",0);
    SetEventHandler("ShowInfoWindow","ShowInfoWindow",0);
	SetEventHandler("MouseRClickUp","HideInfoWindow",0);
	SetEventHandler("TableSelectChange", "CS_TableSelectChange", 0);
	SetEventHandler("eTabControlPress","procTabChange",0);
	SetEventHandler("ChoosePerk","ChoosePerk",0);
	SetEventHandler("ExitPerkMenu","ExitPerkMenu",0);
	SetEventHandler("AcceptPerk","AcceptPerk",0);
	SetEventHandler("ExitMsgMenu", "ExitMsgMenu", 0);
	// evganat - черты
	SetEventHandler("ShowPerks","ShowPerks",0);
	SetEventHandler("ShowTraits","ShowTraits",0);
	
    SetVariable();
    SetCurrentNode("TABLE_OTHER");
    SetFormatedText("LOYALITY_STR", XI_ConvertString("Loyality"));
    HideSkillChanger();
    SetNodeUsing("GAME_ACCEPT", false);
    SetNodeUsing("GAME_CANCEL", false);
	if (bChangePIRATES)
	{
    	ShowMsgMenu(1); // инфо чё делать в начале	evganat - пасха
	}
	// evganat - пасха
	if(bAddPIRATES)
	{
		ShowMsgMenu(2);
	}
}

void ProcessExitCancel()
{
	IDoExit(RC_INTERFACE_ANY_EXIT);
}

void IDoExit(int exitCode)
{
	if (bChangePIRATES)
	{
		xi_refCharacter.skill.FreeSPECIAL = 0; // если не все распределил, сам дурак

		if (startherotype > 3) //Для сюжетных персов  konstrush
		{
			xi_refCharacter.chr_ai.energy = xi_refCharacter.chr_ai.energyMax;
    		ref sld = characterFromID("Sailor_1");
    		LAi_SetActorTypeNoGroup(pchar);
			LAi_SetActorTypeNoGroup(sld);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 0.5);
		}//homo
	}

	DelEventHandler("InterfaceBreak","ProcessExitCancel");
	DelEventHandler("exitCancel","ProcessExitCancel");
	DelEventHandler("ievnt_command","ProcessCommandExecute");
	DelEventHandler("ShowInfoWindow","ShowInfoWindow");
	DelEventHandler("MouseRClickUp","HideInfoWindow");
	DelEventHandler("TableSelectChange", "CS_TableSelectChange");
	DelEventHandler("eTabControlPress","procTabChange");
	DelEventHandler("ChoosePerk","ChoosePerk");
	DelEventHandler("ExitPerkMenu","ExitPerkMenu");
	DelEventHandler("AcceptPerk","AcceptPerk");
	DelEventHandler("ExitMsgMenu", "ExitMsgMenu");
	// evganat - черты
	DelEventHandler("ShowPerks","ShowPerks");
	DelEventHandler("ShowTraits","ShowTraits");

	if (gLngAbilityDescribe >= 0) { LanguageCloseFile(gLngAbilityDescribe); gLngAbilityDescribe = -1; }
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
void ProcessCommandExecute()
{
	string comName = GetEventData();
	string nodName = GetEventData();
    switch(nodName)
	{
        case "B_SKILLUP":
			if (comName=="click")
			{
                IncreaseSkill(1);
			}
			if (comName=="rclick")
			{
                IncreaseSkill(5);
			}
		break;

		case "B_SKILLDOWN":
	        if (comName=="click")
			{
			    DecreaseSkill(1);
			}
			if (comName=="rclick")
			{
			    DecreaseSkill(5);
			}
		break;
		/////////////////////// menu ///////////////
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

void SetVariable()
{
	bAllSelf = CheckAttribute(xi_refCharacter,"AllSelf");
	bAllShip = CheckAttribute(xi_refCharacter,"AllShip");
	FillSkillTables();
	
	SetNewPicture("CHARACTER_BIG_PICTURE", "interfaces\portraits\256\face_" + xi_refCharacter.FaceId + ".tga");
	SetFormatedText("HERO_NAME", GetFullNameTitulForm(xi_refCharacter));

    // теперь это Лояльность
    GameInterface.StatusLine.LOYALITY.Max   = MAX_LOYALITY;
    GameInterface.StatusLine.LOYALITY.Min   = 0;
    GameInterface.StatusLine.LOYALITY.Value = GetCharacterLoyality(xi_refCharacter);

	//здоровье отображается у всех
	GameInterface.StatusLine.BAR_HEALTH.Max   = 54;
	GameInterface.StatusLine.BAR_HEALTH.Min   = 1;
	GameInterface.StatusLine.BAR_HEALTH.Value = makeint(xi_refCharacter.Health.HP);
	if (sti(xi_refCharacter.Health.HP) > 54 )
	{
		GameInterface.StatusLine.BAR_HEALTH.Value = 54;
	}

    GameInterface.StatusLine.BAR_REPUTATION.Max   = REPUTATION_MAX;
    GameInterface.StatusLine.BAR_REPUTATION.Min   = REPUTATION_MIN;
    GameInterface.StatusLine.BAR_REPUTATION.Value = makeint(xi_refCharacter.reputation);

    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"LOYALITY",0);
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"BAR_HEALTH",0);
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE,"BAR_REPUTATION",0);
}

void ShowInfoWindow()
{
	string sCurrentNode = GetCurrentNode();
	string sHeader, sText1, sText2, sText3, sPicture;
	string sGroup, sGroupPicture;
	int iItem;

	sPicture = "-1";
	string sAttributeName;
	int nChooseNum = -1;
	switch (sCurrentNode)
	{
		case "TABLE_SPECIAL":
		    sHeader = XI_ConvertString("Characteristics");
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID + "_hint");
		break;
		case "TABLE_SKILL_1":
		    sHeader = XI_ConvertString("Personal skill");
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID + "_hint");
		break;
		case "TABLE_SKILL_2":
		    sHeader = XI_ConvertString("Ship skill");
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID + "_hint");
		break;
		case "LOYALITY_STR":
		    sHeader = XI_ConvertString("Loyality");
		    sText1  = GetRPGText("Loyality_hint");
		break;
		case "TABBTN_1":
			if(sPerkMode == "perks")
			{
				sHeader = XI_ConvertString("Personal abilities");
				sText1  = GetRPGText("Personal_abilities_hint");
			}
			else
			{
				sHeader = XI_ConvertString("Static traits full");
				sText1  = GetRPGText("Static_traits_hint");
			}
		break;
		case "TABBTN_2":
			if(sPerkMode == "perks")
			{
				sHeader = XI_ConvertString("Ship abilities");
				sText1  = GetRPGText("Ship_abilities_hint");
			}
			else
			{
				sHeader = XI_ConvertString("Dynamic traits full");
				sText1  = GetRPGText("Dynamic_traits_hint");
			}
		break;
		case "TABLE_OTHER":
		    sHeader = XI_ConvertString(GameInterface.(CurTable).(CurRow).UserData.ID);
		    sText1  = GetRPGText(GameInterface.(CurTable).(CurRow).UserData.ID + "_hint");
		break;
		case "TABLE_PERKS":
		    sHeader = GetRPGText("TABLE_PERKS");
		    sText1  = GetRPGText("TABLE_PERKS_desc");
		break;
		case "PERK_TABLE_NEED":
		    sHeader = GetRPGText("PERK_TABLE_NEED");
		    sText1  = GetRPGText("PERK_TABLE_NEED_desc");
		break;
	}
	CreateTooltip("#" + sHeader, sText1, argb(255,255,255,255), sText2, argb(255,255,192,192), sText3, argb(255,192,255,192), "", argb(255,255,255,255), sPicture, sGroup, sGroupPicture, 64, 64);

}

void HideInfoWindow()
{
	CloseTooltip();
}

void FillSkillTables()
{
	int     i;
	string  row, skillName, sTemp;
    int     diff, skillVal;

    // boal оптимизация скилов -->
    DelBakSkillAttr(xi_refCharacter);
    ClearCharacterExpRate(xi_refCharacter);
    RefreshCharacterSkillExpRate(xi_refCharacter);

    SetEnergyToCharacter(xi_refCharacter);
    // boal оптимизация скилов <--

	// Оптимизон для проверок пенальти в десятках вызовов ниже и внутри функций
    xi_refCharacter.TempSailing = GetSummonSkillFromNameSimple(xi_refCharacter, SKILL_SAILING);

    if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_self") )
		xi_refCharacter.perks.FreePoints_self = 0;
    if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_ship") )
		xi_refCharacter.perks.FreePoints_ship = 0;

	sTemp = XI_ConvertString("Personal_abilities");
	if (!bAllSelf) sTemp += " " + xi_refCharacter.perks.FreePoints_self;
    SetFormatedText("TABSTR_1", sTemp);
	
	sTemp = XI_ConvertString("Ship_abilities");
	if (!bAllShip) sTemp += " " + xi_refCharacter.perks.FreePoints_ship;
    SetFormatedText("TABSTR_2", sTemp);
	
    ShowPerks();	// evganat - черты
    
	GameInterface.TABLE_SPECIAL.select = 0;
	GameInterface.TABLE_SPECIAL.hr.td1.icon.group = "RECON_ICONS";
	GameInterface.TABLE_SPECIAL.hr.td1.icon.image = "frame caption red short";
	GameInterface.TABLE_SPECIAL.hr.td1.icon.width = 209;
	GameInterface.TABLE_SPECIAL.hr.td1.icon.height = 24;
	GameInterface.TABLE_SPECIAL.hr.td1.icon.offset = "-2, 0";
	GameInterface.TABLE_SPECIAL.hr.td1.str = "";
	if (bChangePIRATES)
	{
		SetFormatedText("STR_1", XI_ConvertString("Characteristics") + " - " + xi_refCharacter.Skill.FreeSPECIAL + " / 21");
	}
	else
    	{
		if(bAddPIRATES)	// evganat - пасха
		{
			SetFormatedText("STR_1", XI_ConvertString("Characteristics") + " - " + xi_refCharacter.questTemp.FreePIRATES);
		}
		else
		{
			SetFormatedText("STR_1", XI_ConvertString("Characteristics"));
		}
    	}
	
	for (i=1; i<=7; i++)
	{
	    row = "tr" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);

        GameInterface.TABLE_SPECIAL.(row).UserData.ID = skillName;
		GameInterface.TABLE_SPECIAL.(row).td1.fontidx = 0;
		GameInterface.TABLE_SPECIAL.(row).td1.textoffset = "0,-6";
		GameInterface.TABLE_SPECIAL.(row).td1.scale = 0.85;
		GameInterface.TABLE_SPECIAL.(row).td2.textoffset = "5,0";
		GameInterface.TABLE_SPECIAL.(row).td2.scale = 0.88;
		GameInterface.TABLE_SPECIAL.(row).td3.align = "center";
		GameInterface.TABLE_SPECIAL.(row).td4.scale = 0.90;
		GameInterface.TABLE_SPECIAL.(row).td4.fontidx = 1;

		GameInterface.TABLE_SPECIAL.(row).td1.str = XI_ConvertString(skillName + "T");
		GameInterface.TABLE_SPECIAL.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, skillName);
		GameInterface.TABLE_SPECIAL.(row).td4.str = skillVal;
		// рассчет драйна
		diff = GetCharacterSPECIAL(xi_refCharacter, skillName) - skillVal;
		if (diff == 0)
		{
     		GameInterface.TABLE_SPECIAL.(row).td3.str = "";
     		DeleteAttribute(&GameInterface, "TABLE_SPECIAL." + row + ".td3.color");
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.TABLE_SPECIAL.(row).td3.str = "(+" + diff + ")";
	          GameInterface.TABLE_SPECIAL.(row).td3.color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.TABLE_SPECIAL.(row).td3.str = "(" + diff + ")";
	          GameInterface.TABLE_SPECIAL.(row).td3.color = argb(255,255,196,196);
	       }
		}
	}
    GameInterface.TABLE_SKILL_1.select = 0;
    GameInterface.TABLE_SKILL_1.hr.td1.icon.group = "RECON_ICONS";
	GameInterface.TABLE_SKILL_1.hr.td1.icon.image = "frame caption red short";
	GameInterface.TABLE_SKILL_1.hr.td1.icon.width = 208;
	GameInterface.TABLE_SKILL_1.hr.td1.icon.height = 24;
	GameInterface.TABLE_SKILL_1.hr.td1.icon.offset = "-2, 0";
	GameInterface.TABLE_SKILL_1.hr.td1.str = "";
	
	if (sti(xi_refCharacter.Skill.FreeSkill) > 0)
	{
		SetFormatedText("STR_2", XI_ConvertString("Personal skill") + " - " + xi_refCharacter.Skill.FreeSkill);
    }
    else
    {
		SetFormatedText("STR_2", XI_ConvertString("Personal skill"));
    }
	
	for (i=1; i<=7; i++)
	{
	    row = "tr" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);

        GameInterface.TABLE_SKILL_1.(row).UserData.ID = skillName;
		GameInterface.TABLE_SKILL_1.(row).td1.icon.group = "ICONS_SPEC";
	    GameInterface.TABLE_SKILL_1.(row).td1.icon.image = skillName + " skill icon";
	    GameInterface.TABLE_SKILL_1.(row).td1.icon.width = 30;
    	GameInterface.TABLE_SKILL_1.(row).td1.icon.height = 30;
    	GameInterface.TABLE_SKILL_1.(row).td1.icon.offset = "-4, 0";
		GameInterface.TABLE_SKILL_1.(row).td2.align = "left";
		GameInterface.TABLE_SKILL_1.(row).td2.scale = 0.75;
		GameInterface.TABLE_SKILL_1.(row).td2.textoffset = "3,0";
		GameInterface.TABLE_SKILL_1.(row).td5.fontidx = 0;
		GameInterface.TABLE_SKILL_1.(row).td5.scale = 0.65;
		GameInterface.TABLE_SKILL_1.(row).td5.align = "left";
		GameInterface.TABLE_SKILL_1.(row).td3.scale = 0.75;
		GameInterface.TABLE_SKILL_1.(row).td4.scale = 0.85;

		GameInterface.TABLE_SKILL_1.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
		GameInterface.TABLE_SKILL_1.(row).td5.str = skillVal;
		// рассчет драйна
		diff = GetSummonSkillFromName(xi_refCharacter, skillName) - skillVal;

		if (skillVal < SKILL_MAX)
		{
			GameInterface.TABLE_SKILL_1.(row).td3.str = makeint(GetSkillValueExp(xi_refCharacter, skillName) * 100.0 / makefloat(skillVal * GetCharacterExpRate(xi_refCharacter, skillName))) + "%";
		}
		else
		{
		    GameInterface.TABLE_SKILL_1.(row).td3.str = "";
		}
		if (diff == 0)
		{
     		GameInterface.TABLE_SKILL_1.(row).td4.str = "";
     		DeleteAttribute(&GameInterface, "TABLE_SKILL_1." + row + ".td4.color");
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.TABLE_SKILL_1.(row).td4.str = "(+" + diff + ")";
	          GameInterface.TABLE_SKILL_1.(row).td4.color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.TABLE_SKILL_1.(row).td4.str = "(" + diff + ")";
	          GameInterface.TABLE_SKILL_1.(row).td4.color = argb(255,255,196,196);
	       }
		}
	}
	GameInterface.TABLE_SKILL_2.select = 0;
	GameInterface.TABLE_SKILL_2.hr.td1.icon.group = "RECON_ICONS";
	GameInterface.TABLE_SKILL_2.hr.td1.icon.image = "frame caption red short";
	GameInterface.TABLE_SKILL_2.hr.td1.icon.width = 208;
	GameInterface.TABLE_SKILL_2.hr.td1.icon.height = 24;
	GameInterface.TABLE_SKILL_2.hr.td1.icon.offset = "-2, 0";
	GameInterface.TABLE_SKILL_2.hr.td1.str = "";
	SetFormatedText("STR_3", XI_ConvertString("Ship skill"));
	for (i=1; i<=7; i++)
	{
	    row = "tr" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);

        GameInterface.TABLE_SKILL_2.(row).UserData.ID = skillName;
		GameInterface.TABLE_SKILL_2.(row).td1.icon.group = "ICONS_SPEC";
	    GameInterface.TABLE_SKILL_2.(row).td1.icon.image = skillName + " skill icon";
	    GameInterface.TABLE_SKILL_2.(row).td1.icon.width = 30;
    	GameInterface.TABLE_SKILL_2.(row).td1.icon.height = 30;
    	GameInterface.TABLE_SKILL_2.(row).td1.icon.offset = "-1, 0";
		GameInterface.TABLE_SKILL_2.(row).td2.align = "left";
		GameInterface.TABLE_SKILL_2.(row).td2.scale = 0.75;
		GameInterface.TABLE_SKILL_2.(row).td2.textoffset = "3,0";
		GameInterface.TABLE_SKILL_2.(row).td5.fontidx = 0;
		GameInterface.TABLE_SKILL_2.(row).td5.scale = 0.65;
		GameInterface.TABLE_SKILL_2.(row).td5.align = "left";
		GameInterface.TABLE_SKILL_2.(row).td3.scale = 0.75;
		GameInterface.TABLE_SKILL_2.(row).td4.scale = 0.85;

		GameInterface.TABLE_SKILL_2.(row).td2.str = XI_ConvertString(skillName);
		skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
		GameInterface.TABLE_SKILL_2.(row).td5.str = skillVal;
		// рассчет драйна
		diff = GetSummonSkillFromName(xi_refCharacter, skillName) - skillVal;

		if (skillVal < SKILL_MAX)
		{
			GameInterface.TABLE_SKILL_2.(row).td3.str = makeint(GetSkillValueExp(xi_refCharacter, skillName) * 100.0 / makefloat(skillVal * GetCharacterExpRate(xi_refCharacter, skillName))) + "%";
		}
		else
		{
		    GameInterface.TABLE_SKILL_2.(row).td3.str = "";
		}
		if (diff == 0)
		{
     		GameInterface.TABLE_SKILL_2.(row).td4.str = "";
     		DeleteAttribute(&GameInterface, "TABLE_SKILL_2." + row + ".td4.color");
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.TABLE_SKILL_2.(row).td4.str = "(+" + diff + ")";
	          GameInterface.TABLE_SKILL_2.(row).td4.color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.TABLE_SKILL_2.(row).td4.str = "(" + diff + ")";
	          GameInterface.TABLE_SKILL_2.(row).td4.color = argb(255,255,196,196);
	       }
		}
	}
	////  остальное
	GameInterface.TABLE_OTHER.select = 0;
	for (i=1; i<=9; i++)
	{
	    row = "tr" + i;

	    GameInterface.TABLE_OTHER.(row).td1.icon.width = 26;
    	GameInterface.TABLE_OTHER.(row).td1.icon.height = 26;
    	GameInterface.TABLE_OTHER.(row).td1.icon.offset = "-1, 0";
		GameInterface.TABLE_OTHER.(row).td2.align = "left";
		GameInterface.TABLE_OTHER.(row).td2.scale = 0.85;
		GameInterface.TABLE_OTHER.(row).td2.textoffset = "3,0";
		GameInterface.TABLE_OTHER.(row).td3.align = "right";
	}
	GameInterface.TABLE_OTHER.tr1.UserData.ID = "Rank";
	GameInterface.TABLE_OTHER.tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr1.td1.icon.image = "Rank";
	GameInterface.TABLE_OTHER.tr1.td2.str = XI_ConvertString("Rank");
	GameInterface.TABLE_OTHER.tr1.td3.str = sti(xi_refCharacter.rank);

	GameInterface.TABLE_OTHER.tr2.UserData.ID = "Life";
	GameInterface.TABLE_OTHER.tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr2.td1.icon.image = "Life";
	GameInterface.TABLE_OTHER.tr2.td2.str = XI_ConvertString("Life");
	GameInterface.TABLE_OTHER.tr2.td3.str = MakeInt(LAi_GetCharacterHP(xi_refCharacter)) + " / " + MakeInt(LAi_GetCharacterMaxHP(xi_refCharacter));

    GameInterface.TABLE_OTHER.tr3.UserData.ID = "Health";
	GameInterface.TABLE_OTHER.tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr3.td1.icon.image = "Health";
	GameInterface.TABLE_OTHER.tr3.td2.str = XI_ConvertString("Health");
	GameInterface.TABLE_OTHER.tr3.td3.str = GetHealthName(xi_refCharacter);
	GameInterface.TABLE_OTHER.tr3.td3.scale = 0.75;

	if (GetHealthNum(xi_refCharacter) >= GetHealthMaxNum(xi_refCharacter))
    {
        GameInterface.TABLE_OTHER.tr3.td3.color = SetAlphaIntoColor(COLOR_MONEY, GetAlphaFromSkill(10));
    }
    else
    {
        GameInterface.TABLE_OTHER.tr3.td3.color = SetAlphaIntoColor(COLOR_NORMAL, GetAlphaFromSkill(makeint(GetHealthNum(xi_refCharacter)* 1.9)));
    }

    GameInterface.TABLE_OTHER.tr4.UserData.ID = "Energy";
	GameInterface.TABLE_OTHER.tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr4.td1.icon.image = "Energy";
	GameInterface.TABLE_OTHER.tr4.td2.str = XI_ConvertString("Energy");
	GameInterface.TABLE_OTHER.tr4.td3.str = sti(Lai_CharacterGetEnergy(xi_refCharacter)) + " / " + sti(LAi_GetCharacterMaxEnergy(xi_refCharacter));
	diff = sti(LAi_GetCharacterMaxEnergy(xi_refCharacter) - GetCharacterMaxEnergyABSValue(xi_refCharacter));
	if (diff != 0)
	{
	   if (diff > 0)
	   {
          GameInterface.TABLE_OTHER.tr4.td3.color = argb(255,196,255,196);
       }
       else
       {
          GameInterface.TABLE_OTHER.tr4.td3.color = argb(255,255,196,196);
       }
	}
	else
	{
		DeleteAttribute(&GameInterface, "TABLE_OTHER.tr4.td3.color");
	}

	GameInterface.TABLE_OTHER.tr5.UserData.ID = "Money";
	GameInterface.TABLE_OTHER.tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr5.td1.icon.image = "Money";
	GameInterface.TABLE_OTHER.tr5.td2.str = XI_ConvertString("Money");
	GameInterface.TABLE_OTHER.tr5.td3.str = MakeMoneyShow(sti(xi_refCharacter.Money), MONEY_SIGN,MONEY_DELIVER);
	//GameInterface.TABLE_OTHER.tr5.td3.scale = 0.95;
	//GameInterface.TABLE_OTHER.tr5.td3.color = SetAlphaIntoColor(COLOR_MONEY, GetAlphaFromSkill(10));

    GameInterface.TABLE_OTHER.tr6.UserData.ID = "Reputation";
	GameInterface.TABLE_OTHER.tr6.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr6.td1.icon.image = "Reputation";
	GameInterface.TABLE_OTHER.tr6.td2.str = XI_ConvertString("Reputation");
	GameInterface.TABLE_OTHER.tr6.td3.str = XI_ConvertString(GetReputationName(sti(xi_refCharacter.reputation)));
	GameInterface.TABLE_OTHER.tr6.td3.scale = 0.78;

	GameInterface.TABLE_OTHER.tr7.UserData.ID = "weight";
	GameInterface.TABLE_OTHER.tr7.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr7.td1.icon.image = "weight";
	GameInterface.TABLE_OTHER.tr7.td2.str = XI_ConvertString("weight");
	GameInterface.TABLE_OTHER.tr7.td3.str = FloatToString(GetItemsWeight(xi_refCharacter), 1) + " / "+GetMaxItemsWeight(xi_refCharacter);

    GameInterface.TABLE_OTHER.tr8.UserData.ID = "Title";
	GameInterface.TABLE_OTHER.tr8.td1.icon.group = "ICONS_CHAR";
	GameInterface.TABLE_OTHER.tr8.td1.icon.image = "Title";

	DeleteAttribute(&GameInterface, "TABLE_OTHER.tr8.td2");
	GameInterface.TABLE_OTHER.tr8.td2.str = XI_ConvertString("Title");
	GameInterface.TABLE_OTHER.tr8.td2.align = "left";
	GameInterface.TABLE_OTHER.tr8.td2.scale = 0.85;
	GameInterface.TABLE_OTHER.tr8.td2.textoffset = "3,0";

    DeleteAttribute(&GameInterface, "TABLE_OTHER.tr8.td3");
    GameInterface.TABLE_OTHER.tr8.td3.str = "";
	GameInterface.TABLE_OTHER.tr8.td3.scale = 0.9;

	if (xi_refCharacter.id == pchar.id && isMainCharacterPatented())
    {
        GameInterface.TABLE_OTHER.tr8.td3.str = GetAddress_FormTitle(sti(Items[sti(pchar.EquipedPatentId)].Nation), sti(Items[sti(pchar.EquipedPatentId)].TitulCur));
        GameInterface.TABLE_OTHER.tr8.td2.icon.group = "NATIONS";
		GameInterface.TABLE_OTHER.tr8.td2.icon.image = GetNationNameByType(sti(Items[sti(pchar.EquipedPatentId)].Nation));
		GameInterface.TABLE_OTHER.tr8.td2.icon.offset = "60, 1";
		GameInterface.TABLE_OTHER.tr8.td2.icon.width = 24;
		GameInterface.TABLE_OTHER.tr8.td2.icon.height = 24;
    }
    else
    {
        GameInterface.TABLE_OTHER.tr8.td3.str = XI_ConvertString("noTitle");
    }

	GameInterface.TABLE_OTHER.tr9.UserData.ID = "NextExp";
	GameInterface.TABLE_OTHER.tr9.td1.icon.group = "ICONS_CHAR";
    GameInterface.TABLE_OTHER.tr9.td1.icon.image = "NextExp";
	GameInterface.TABLE_OTHER.tr9.td2.str = XI_ConvertString("NextExp");
	GameInterface.TABLE_OTHER.tr9.td3.str = "";

	// прорисовка
	Table_UpdateWindow("TABLE_SPECIAL");
    Table_UpdateWindow("TABLE_SKILL_1");
    Table_UpdateWindow("TABLE_SKILL_2");
    Table_UpdateWindow("TABLE_OTHER");

	// Убираем бэкап
    DeleteAttribute(xi_refCharacter, "TempSailing");
}

void CS_TableSelectChange()
{
	string sControl = GetEventData();
	iSelected = GetEventData();
    CurTable = sControl;
    CurRow   =  "tr" + (iSelected);
    //sti(GameInterface.(sControl).(sRow).index);
 	NullSelectTable("TABLE_SPECIAL");
    NullSelectTable("TABLE_SKILL_1");
    NullSelectTable("TABLE_SKILL_2");
    NullSelectTable("TABLE_PERKS");
    NullSelectTable("TABLE_OTHER");
    // перерисует порог опыта
    GameInterface.TABLE_OTHER.tr9.td3.str = "";
    if (CurTable == "TABLE_OTHER" && CurRow == "tr1")
    {
    	GameInterface.TABLE_OTHER.tr9.td3.str = GetCharacterRankRateCur(xi_refCharacter) + "/" + GetCharacterRankRate(xi_refCharacter);
    }

	if (CurTable == "TABLE_SKILL_1" || CurTable == "TABLE_SKILL_2")
	{
        string skillName;
        int skillVal;
        skillName = GameInterface.(CurTable).(CurRow).UserData.ID;
        skillVal = GetSkillValue(xi_refCharacter, SKILL_TYPE, skillName);
		if (skillVal != SKILL_MAX && skillVal != 0)
		{
	       GameInterface.TABLE_OTHER.tr9.td3.str = sti(GetSkillValueExp(xi_refCharacter, skillName))+ "/" + makeint(skillVal * GetCharacterExpRate(xi_refCharacter, skillName));
		}
	}
	Table_UpdateWindow("TABLE_OTHER");
	// установим скилчанжер, если нужно
	HideSkillChanger();
    SetSkillArrows();
}

void SetSkillArrows()
{
   	bool ok;
	int  minP;
	
	ok = sti(xi_refCharacter.skill.freeskill) > 0 || sti(xi_refCharacter.skill.FreeSPECIAL) > 0 || bChangePIRATES;  //для начала игры
	if (ok && CurTable == "TABLE_SPECIAL")
	{
        minP = 1;
        if (bChangePIRATES)
        {
            minP = 3;
        }
		if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) > minP)
        {
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLDown",0, 265 - 70, 85 + 26 * (iSelected - 1), 297 - 70, 85 + 26 + 26 * (iSelected - 1), 0);
			SetNodeUsing("B_SKILLDown", true);
        }
        if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) < SPECIAL_MAX && sti(xi_refCharacter.skill.FreeSPECIAL) > 0)
        {
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 288 - 70, 85 + 26 * (iSelected - 1), 320 - 70, 85 + 26 + 26 * (iSelected - 1), 0);
            SetNodeUsing("B_SKILLUP",  true);
        }
	}

	// evganat - пасха
	if(bAddPIRATES && CurTable == "TABLE_SPECIAL" && sti(xi_refCharacter.questTemp.FreePIRATES) > 0)
	{
		if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, GameInterface.(CurTable).(CurRow).UserData.ID) < SPECIAL_MAX)
		{
			SendMessage(&GameInterface,"lsllllll", MSG_INTERFACE_MSG_TO_NODE,"B_SKILLUP",0, 288 - 70, 85 + 26 * (iSelected - 1), 320 - 70, 85 + 26 + 26 * (iSelected - 1), 0);
            SetNodeUsing("B_SKILLUP",  true);
		}
	}
}
void NullSelectTable(string sControl)
{
	if (sControl == CurTable) return;

	if (CheckAttribute(&GameInterface, sControl + ".select") && sti(GameInterface.(sControl).select) == 0) return;

	GameInterface.(sControl).select = 0;
	Table_UpdateWindow(sControl);
}


void procTabChange()
{
	int iComIndex = GetEventData();
	string sNodName = GetEventData();
	SetCurrentNode("TABLE_PERKS");
	if( sNodName == "TABBTN_1" )
	{
		SetControlsTabMode( 1 );
		return;
	}
	if( sNodName == "TABBTN_2" )
	{
		SetControlsTabMode( 2 );
		return;
	}
}

void SetControlsTabMode(int nMode)
{
	int nColor1 = argb(255,196,196,196);
	int nColor2 = nColor1;

	string sPic1 = "TabSelected";
	string sPic2 = sPic1;

	switch (nMode)
	{
		case 1: //
			sPic1 = "TabDeSelected";
			nColor1 = argb(255,255,255,255);
			if(sPerkMode == "traits" || bAllSelf)	break;
			// порог опыта
			if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_self_exp"))
            {
               xi_refCharacter.perks.FreePoints_self_exp = 0;
            }
            GameInterface.TABLE_OTHER.tr9.td3.str = sti(xi_refCharacter.perks.FreePoints_self_exp)+ "/" + GetFreePoints_SelfRate(xi_refCharacter);
		break;
		case 2:
			sPic2 = "TabDeSelected";
			nColor2 = argb(255,255,255,255);
			if(sPerkMode == "traits" || bAllShip)	break;
			// порог опыта
			if (!CheckAttribute(xi_refCharacter,"perks.FreePoints_ship_exp"))
            {
               xi_refCharacter.perks.FreePoints_ship_exp = 0;
            }
            GameInterface.TABLE_OTHER.tr9.td3.str = sti(xi_refCharacter.perks.FreePoints_ship_exp)+ "/" + GetFreePoints_ShipRate(xi_refCharacter);
		break;
	}
    Table_UpdateWindow("TABLE_OTHER"); // порог опыта

	SetNewGroupPicture("TABBTN_1", "TABS", sPic1);
	SetNewGroupPicture("TABBTN_2", "TABS", sPic2);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_1", 8,0,nColor1);
	SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE,"TABSTR_2", 8,0,nColor2);

	FillControlsList(nMode);
	HideSkillChanger();
}

void FillControlsList(int nMode)
{
	// evganat - черты
	if(sPerkMode == "perks")
	{
		switch (nMode)
		{
			case 1: FillPerksTable("Self", true); break;  // Личные перки
			case 2: FillPerksTable("Ship", true); break;  // Корабельные перки
		}
	}
	else
	{
		switch (nMode)
		{
			case 1: FillPerksTable("Static", true); break;  // статические черты
			case 2: FillPerksTable("Dynamic", true); break;  // динамические черты
		}
	}
}

void HideSkillChanger()
{
    SetNodeUsing("B_SKILLUP",  false);
	SetNodeUsing("B_SKILLDown",  false);
}

void IncreaseSkill(int _add)
{
	int     iValue;
	string  sSkillName;

    sSkillName = GameInterface.(CurTable).(CurRow).UserData.ID;
    if (CurTable != "TABLE_SPECIAL")
    {
		if (sti(xi_refCharacter.skill.freeskill) < _add) _add = sti(xi_refCharacter.skill.freeskill);
		if ((GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) + _add) > SKILL_MAX)
		{
		    _add = SKILL_MAX - GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName);
		}
	    if (_add > 0)
	    {
	        iValue = AddCharacterSkill(xi_refCharacter, sSkillName, _add);
			xi_refCharacter.skill.freeskill = sti(xi_refCharacter.skill.freeskill) - _add;
	    }
	    else return;
    }
	else
	{
        	// evganat - пасха
		if(bAddPIRATES)
		{
			if(sti(xi_refCharacter.questTemp.FreePIRATES) < _add) _add = sti(xi_refCharacter.questTemp.FreePIRATES);
			if ((GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) + _add) > SPECIAL_MAX)
			{
				_add = SPECIAL_MAX - GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName);
			}
			iValue = AddSPECIALValue(xi_refCharacter, sSkillName, _add);
			xi_refCharacter.questTemp.FreePIRATES = sti(xi_refCharacter.questTemp.FreePIRATES) - _add;
			SetEnergyToCharacter(xi_refCharacter);
		}
		else
		{
			if (sti(xi_refCharacter.skill.FreeSPECIAL) < _add) _add = sti(xi_refCharacter.skill.FreeSPECIAL);
			if ((GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) + _add) > SPECIAL_MAX)
			{
				_add = SPECIAL_MAX - GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName);
			}
			if (_add > 0)
			{
				iValue = AddSPECIALValue(xi_refCharacter, sSkillName, _add);
				xi_refCharacter.skill.FreeSPECIAL = sti(xi_refCharacter.skill.FreeSPECIAL) - _add;
			}
			else return;
	    
			if (bChangePIRATES)
			{ //для начала игры пересчет скилов
				// начальные скилы задать
				InitStartParam(xi_refCharacter);
				SetEnergyToCharacter(xi_refCharacter);
				xi_refCharacter.chr_ai.energy = xi_refCharacter.chr_ai.energyMax;
			}
		}
    }
	SetVariable();
	SetSkillArrows();
}

void DecreaseSkill(int _add)
{
	int     iValue;
	string  sSkillName;

    sSkillName = GameInterface.(CurTable).(CurRow).UserData.ID;
    if (CurTable != "TABLE_SPECIAL")
    {
	    if (GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) <= _add)
	    {
	        _add = GetSkillValue(xi_refCharacter, SKILL_TYPE, sSkillName) - 1;
	    }
	    if (_add > 0)
	    {
	        iValue = AddCharacterSkill(xi_refCharacter, sSkillName, -_add);
			xi_refCharacter.skill.freeskill = sti(xi_refCharacter.skill.freeskill) + _add;
	    }
	    else return;
    }
    else
    {
		if (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) <= _add)
	    {
	        _add = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - 1;
	    }
	    if (bChangePIRATES && (GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - _add) < 3)
        {
            _add = GetSkillValue(xi_refCharacter, SPECIAL_TYPE, sSkillName) - 3;
		}
	    if (_add > 0)
	    {
	        iValue = AddSPECIALValue(xi_refCharacter, sSkillName, -_add);
			xi_refCharacter.skill.FreeSPECIAL = sti(xi_refCharacter.skill.FreeSPECIAL) + _add;
	    }
	    else return;
	    
	    if (bChangePIRATES)
	    { //для начала игры пересчет скилов
	    	// начальные скилы задать
		    InitStartParam(xi_refCharacter);
		    SetEnergyToCharacter(xi_refCharacter);
	    }
    }
    SetVariable();
    SetSkillArrows();
}
///////////////////////////////////////  PERKS /////////////////////////
void FillPerksTable(string _type, bool _refresh)
{
	int perksQ, i, n;
	string perkName, row, icoGroup;
	aref arPerksRoot, arChrPerks;	// evganat - черты

    Table_Clear("TABLE_PERKS", false, true, false);
	if (_refresh)
	{
	    GameInterface.TABLE_PERKS.select = 0;
	    GameInterface.TABLE_PERKS.top = 0;
	}
	
	if(sPerkMode == "perks")
	{
		makearef(arPerksRoot,ChrPerksList.list); // общий список

		bool bIsPchar = (xi_refCharacter.id == pchar.id);
		bool bHasDignity = CheckCharacterPerk(xi_refCharacter, "Dignity");
		bool bCompanionDisable = CheckAttribute(xi_refCharacter, "CompanionDisable");
		bool bHasAllowedPosts = CheckAttribute(xi_refCharacter, "AllowedPosts");
		int iAllowedPosts = 0;
		if (bHasAllowedPosts) iAllowedPosts = GetCountSubString(xi_refCharacter.AllowedPosts);

		perksQ = GetAttributesNum(arPerksRoot);
		n = 1;
		for(i=0; i<perksQ; i++)
		{
			row = "tr" + n;

			perkName = GetAttributeName(GetAttributeN(arPerksRoot,i));
			if (bIsPchar && CheckAttribute(arPerksRoot, perkName + ".NPCOnly"))		continue;
			if (!bIsPchar && CheckAttribute(arPerksRoot, perkName + ".PlayerOnly"))	continue;
			if (bCompanionDisable && perkName == "ShipEscape")			continue;
			if (CheckAttribute(arPerksRoot, perkName + ".Hidden") && !ShowHiddenPerks(xi_refCharacter, perkName)) continue;
			if (bHasAllowedPosts)
			{
				if(perkName == "ByWorker"  && iAllowedPosts < 2)	continue;
				if(perkName == "ByWorker2" && iAllowedPosts < 3)	continue;
			}
			if (CheckAttribute(arPerksRoot, perkName + ".OfficerType"))
			{
				if(arPerksRoot.(perkName).OfficerType == "capellan" && !CheckAttribute(xi_refCharacter, "Capellan"))
					continue;
				if(bHasAllowedPosts && !HasSubStr(xi_refCharacter.AllowedPosts, arPerksRoot.(perkName).OfficerType)
				&& bCompanionDisable) //TODO: при переделке системы отдельно выносить перки, полезные для наместника
					continue;
			}
			if (bHasDignity) //HardCoffee не отображать кулачные перки тем, у кого нет анимации
			{
				if (perkName == "NachoPuncher" || perkName == "DrunkenMaster") continue;
			}
			if (perkName == "DrunkenMaster") continue;	//HardCoffee временно отключаю Пьяный мастер, так как у него нет функционала
			if (CheckAttribute(arPerksRoot, perkName + ".BaseType") && arPerksRoot.(perkName).BaseType == _type)
			{
				GameInterface.TABLE_PERKS.(row).UserData.ID   = perkName;
				GameInterface.TABLE_PERKS.(row).UserData.Type = _type;
				if (CheckCharacterPerk(xi_refCharacter, perkName))
				{
					icoGroup = "PERK_ENABLE";
					GameInterface.TABLE_PERKS.(row).td2.color = argb(255,255,255,255);
				}
				else
				{
					icoGroup = "PERK_DISABLE";
					GameInterface.TABLE_PERKS.(row).td2.color = argb(255,196,196,196);
				}
				GameInterface.TABLE_PERKS.(row).td1.icon.group  = icoGroup;
				GameInterface.TABLE_PERKS.(row).td1.icon.image  = perkName;
				GameInterface.TABLE_PERKS.(row).td1.icon.width  = 27;
				GameInterface.TABLE_PERKS.(row).td1.icon.height = 27;
				GameInterface.TABLE_PERKS.(row).td1.icon.offset = "-1, 1";

				if(CheckAttribute(arPerksRoot, perkName + ".FemName") && xi_refCharacter.sex == "woman") perkName += "Fem";
				GameInterface.TABLE_PERKS.(row).td2.str = GetConvertStr(perkName, "AbilityDescribe.txt");
				//GameInterface.TABLE_PERKS.(row).td2.textoffset = "0,-6";
				GameInterface.TABLE_PERKS.(row).td2.scale = 0.80;
				n++;
			}
		}
		if (sti(xi_refCharacter.index) != GetMainCharacterIndex())
			TablePerks_SortByEnabled(); // Сначала в таблице будут взятые перки у оффа, порядок сохраняется
	}
	else // evganat - черты
	{
		makearef(arPerksRoot, ChrPerksList.list);
		makearef(arChrPerks, xi_refCharacter.perks.list);
		perksQ = GetAttributesNum(arChrPerks);
		n = 1;
		for(i=perksQ-1; i>=0; i--)
		{
			row = "tr" + n;

			perkName = GetAttributeName(GetAttributeN(arChrPerks,i));
			if (CheckAttribute(arPerksRoot, perkName + ".Hidden") && !ShowHiddenPerks(xi_refCharacter, perkName)) continue;
			if (!CheckAttribute(arPerksRoot, perkName + ".BaseType")) continue;
			if (arPerksRoot.(perkName).BaseType != "trait") continue;
			if (!CheckAttribute(arPerksRoot, perkName + ".Parameters"))
			{
				arPerksRoot.(perkName).Parameters = "dynamic";
			}
			if (HasSubStr(arPerksRoot.(perkName).Parameters, _type))
			{
				GameInterface.TABLE_PERKS.(row).UserData.ID   = perkName;
				GameInterface.TABLE_PERKS.(row).UserData.Type = _type;
				GameInterface.TABLE_PERKS.(row).td1.icon.group  = "PERK_ENABLE";
				GameInterface.TABLE_PERKS.(row).td1.icon.image  = perkName;
				GameInterface.TABLE_PERKS.(row).td1.icon.width  = 28;
				GameInterface.TABLE_PERKS.(row).td1.icon.height = 28;
				GameInterface.TABLE_PERKS.(row).td1.icon.offset = "1, 2";
				GameInterface.TABLE_PERKS.(row).td2.color = argb(255,255,255,255);

				if(CheckAttribute(arPerksRoot, perkName + ".FemName") && xi_refCharacter.sex == "woman") perkName += "Fem";
				GameInterface.TABLE_PERKS.(row).td2.str = GetConvertStr(perkName, "AbilityDescribe.txt");
				GameInterface.TABLE_PERKS.(row).td2.scale = 0.80;
				n++;
			}
		}
	}
	
	// прорисовка
	Table_UpdateWindow("TABLE_PERKS");
}

void ChoosePerk()
{
	if(CurRow == "") return;
	if(!CheckAttribute(&GameInterface, CurTable+"."+CurRow)) return;
	bool ok = true;
	bool showCondition = true;
	string  perkName = GameInterface.(CurTable).(CurRow).UserData.ID;
	
	// evganat - энциклопедия
	aref arBonus;
	if(IsMainCharacter(xi_refCharacter) || IsCharacterOfficer(xi_refCharacter) || IsCompanion(xi_refCharacter))
	{
		makearef(arBonus, pchar.encyclopedia.bonus);
	}
	else
	{
		makearef(arBonus, xi_refCharacter.encyclopedia.bonus);
	}
	string descr, sTemp;
	if(CheckAttribute(&ChrPerksList, "list." + perkName + ".FemDescr") && xi_refCharacter.sex == "woman")
			descr = GetAssembledString(GetConvertStr("perk"+perkName+"Fem", "AbilityDescribe.txt"), arBonus);
	else 	descr = GetAssembledString(GetConvertStr("perk"+perkName, "AbilityDescribe.txt"), arBonus);

	aref rootItems;
	int    i;
	string row, perkCond, icoGroup;

	SetNewGroupPicture("PERK_PICTURE", "PERK_ENABLE", perkName);
	
	string perkTableName = perkName;
	if(CheckAttribute(&ChrPerksList, "list." + perkName + ".FemDescr") && xi_refCharacter.sex == "woman")
		perkTableName += "Fem";
    SetFormatedText("PERK_WINDOW_CAPTION", GetConvertStr(perkTableName, "AbilityDescribe.txt"));

    if (CheckAttribute(&ChrPerksList, "list." + perkName + ".OfficerType") && !HasSubStr(perkName, "Capellan"))
    {
        descr += "\n\n" + XI_ConvertString("ChatacterInderfaceDescr_1") + XI_ConvertString(ChrPerksList.list.(perkName).OfficerType)+ XI_ConvertString("ChatacterInderfaceDescr_2");
    }
    SetFormatedText("PERK_WINDOW_TEXT", descr);
    SetVAligmentFormatedText("PERK_WINDOW_TEXT");
	
	if (sPerkMode == "traits" || CheckAttribute(&ChrPerksList, "list." + perkName + ".Free")) // EvgAnat - дикие карибы
    {
	    if(sPerkMode == "perks")
			SetFormatedText("PERK_TEXT_FREE", XI_ConvertString("ChatacterInderfaceDescr_3"));
		else
			SetFormatedText("PERK_TEXT_FREE", "");
    }
    else
    {
		if (GameInterface.(CurTable).(CurRow).UserData.Type == "self")
		{
			sTemp = XI_ConvertString("Personal abilities");
			if (!bAllSelf) sTemp += ": " + xi_refCharacter.perks.FreePoints_self;
        	SetFormatedText("PERK_TEXT_FREE", sTemp);
			if (sti(xi_refCharacter.perks.FreePoints_self) <= 0) ok = false;
		}
		else
		{
			sTemp = XI_ConvertString("Ship abilities");
			if (!bAllShip) sTemp += ": " + xi_refCharacter.perks.FreePoints_ship;
			SetFormatedText("PERK_TEXT_FREE", sTemp);
			if (sti(xi_refCharacter.perks.FreePoints_ship) <= 0) ok = false;
		}
	}
	// проверка на необходимы перки -->
	if (CheckAttribute(&ChrPerksList, "list." + perkName + ".condition"))
	{
        makearef(rootItems, ChrPerksList.list.(perkName).condition);
		Table_Clear("PERK_TABLE_NEED", false, true, false);
		GameInterface.PERK_TABLE_NEED.select = 0;
		GameInterface.PERK_TABLE_NEED.hr.td1.str = "";
		GameInterface.PERK_TABLE_NEED.top = 0;
		for (i=0; i<GetAttributesNum(rootItems); i++)
    	{
    	    row = "tr" + (i+1);
    	    perkCond = GetAttributeName(GetAttributeN(rootItems, i));
    	    if (CheckCharacterPerk(xi_refCharacter, perkCond))
            {
                icoGroup = "PERK_ENABLE";
                GameInterface.PERK_TABLE_NEED.(row).td2.color = argb(255,255,255,255);
            }
            else
            {
                icoGroup = "PERK_DISABLE";
                GameInterface.PERK_TABLE_NEED.(row).td2.color = argb(255,196,196,196);
                ok = false;
            }
			GameInterface.PERK_TABLE_NEED.(row).td1.icon.group  = icoGroup;
			GameInterface.PERK_TABLE_NEED.(row).td1.icon.image  = perkCond;
			GameInterface.PERK_TABLE_NEED.(row).td1.icon.width  = 24;
		    GameInterface.PERK_TABLE_NEED.(row).td1.icon.height = 24;
		    GameInterface.PERK_TABLE_NEED.(row).td1.icon.offset = "-2, 3";

			GameInterface.PERK_TABLE_NEED.(row).td2.str = GetConvertStr(perkCond, "AbilityDescribe.txt");
			GameInterface.PERK_TABLE_NEED.(row).td2.scale = 0.68;
    	}
		Table_UpdateWindow("PERK_TABLE_NEED");
	}
	else
	{
	    showCondition = false;
	}
	// проверка на необходимы перки <--
	XI_WindowShow("PERK_WINDOW", true);
	XI_WindowDisable("PERK_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	if (CheckCharacterPerk(xi_refCharacter, perkName))
 	{
 	    SetNodeUsing("PERK_ON", true);
 	    ok = false; // уже есть
 	}
 	else
 	{
 	    SetNodeUsing("PERK_ON", false);
 	    SetNewGroupPicture("PERK_PICTURE", "PERK_DISABLE", perkName);
 	}

    SetSelectable("PERK_ACCEPT", ok);
    SetNodeUsing("PERK_TABLE_NEED", showCondition);
	SetCurrentNode("PERK_CANCEL");
}

void ExitPerkMenu()
{
	XI_WindowShow("PERK_WINDOW", false);
	XI_WindowDisable("PERK_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_PERKS");
}

void AcceptPerk()
{
	string sTemp;
    string  perkName = GameInterface.(CurTable).(CurRow).UserData.ID;
    if (GameInterface.(CurTable).(CurRow).UserData.Type == "self")
    {
		xi_refCharacter.perks.FreePoints_self = sti(xi_refCharacter.perks.FreePoints_self) - 1;
	}
	else
	{
		xi_refCharacter.perks.FreePoints_ship = sti(xi_refCharacter.perks.FreePoints_ship) - 1;
    }
    SetCharacterPerk(xi_refCharacter, perkName);
    // перерисуем все -->
	sTemp = XI_ConvertString("Personal_abilities");
	if (!bAllSelf) sTemp += " " + xi_refCharacter.perks.FreePoints_self;
    SetFormatedText("TABSTR_1", sTemp);
	
	sTemp = XI_ConvertString("Ship_abilities");
	if (!bAllShip) sTemp += " " + xi_refCharacter.perks.FreePoints_ship;
    SetFormatedText("TABSTR_2", sTemp);
	
    FillPerksTable(GameInterface.(CurTable).(CurRow).UserData.Type, false);
    // перерисуем все <--
	ExitPerkMenu();
}

void ExitMsgMenu()
{
	XI_WindowShow("MSG_WINDOW", false);
	XI_WindowDisable("MSG_WINDOW", true);
	XI_WindowDisable("MAIN_WINDOW", false);

	SetCurrentNode("TABLE_OTHER");
}

// evganat - пасха
void ShowMsgMenu(int mode)
{
	switch(mode)
	{
		case 1:
			SetFormatedText("MSG_WINDOW_CAPTION", XI_ConvertString("ChatacterInderfaceDescr_4"));
			SetFormatedText("MSG_WINDOW_TEXT", XI_ConvertString("ChatacterInderfaceDescr_5"));
		break;
		case 2:
			SetFormatedText("MSG_WINDOW_CAPTION", XI_ConvertString("ChatacterInderfaceDescr_6"));
			SetFormatedText("MSG_WINDOW_TEXT", XI_ConvertString("ChatacterInderfaceDescr_7"));
		break;
	}
	XI_WindowShow("MSG_WINDOW", true);
	XI_WindowDisable("MSG_WINDOW", false);
	XI_WindowDisable("MAIN_WINDOW", true);

	SetCurrentNode("MSG_OK");
}

// evganat - черты
void ShowPerks()
{
	string sTemp = XI_ConvertString("Personal_abilities");
	if (!bAllSelf) sTemp += " " + xi_refCharacter.perks.FreePoints_self;
	SetFormatedText("TABSTR_1", sTemp);
	
	sTemp = XI_ConvertString("Ship_abilities");
	if (!bAllShip) sTemp += " " + xi_refCharacter.perks.FreePoints_ship;
	SetFormatedText("TABSTR_2", sTemp);
	
	SetSelectable("PERK_BTN", 0);
	SetSelectable("TRAIT_BTN", 1);
	sPerkMode = "perks";
	SetControlsTabMode(1);
}

void ShowTraits()
{
	SetFormatedText("TABSTR_1", XI_ConvertString("Static traits"));
	SetFormatedText("TABSTR_2", XI_ConvertString("Dynamic traits"));
	SetSelectable("PERK_BTN", 1);
	SetSelectable("TRAIT_BTN", 0);
	sPerkMode = "traits";
	SetControlsTabMode(1);
	GameInterface.TABLE_OTHER.tr9.td3.str = "";
	Table_UpdateWindow("TABLE_OTHER");
}

void TablePerks_SortByEnabled()
{
	object tmpRows;
	aref arSrc, arDst;
	int i, q = 0;
	int n = 0;
	string row, sTmp;

	row = "tr1";
	while (CheckAttribute(&GameInterface, "TABLE_PERKS." + row))
	{
		q++;
		row = "tr" + (q + 1);
	}

	if (q < 2) return;

	// > сначала взятые перки (PERK_ENABLE), относительный порядок сохраняется
	for (i = 1; i <= q; i++)
	{
		row = "tr" + i;
		if (GameInterface.TABLE_PERKS.(row).td1.icon.group == "PERK_ENABLE")
		{
			n++;
			sTmp = "p" + n;
			makearef(arSrc, GameInterface.TABLE_PERKS.(row));
			makearef(arDst, tmpRows.(sTmp));
			CopyAttributes(arDst, arSrc);
		}
	}

	if (n == 0 || n == q) return; // > все взяты или ни одного - переставлять нечего

	// > затем остальные
	for (i = 1; i <= q; i++)
	{
		row = "tr" + i;
		if (GameInterface.TABLE_PERKS.(row).td1.icon.group != "PERK_ENABLE")
		{
			n++;
			sTmp = "p" + n;
			makearef(arSrc, GameInterface.TABLE_PERKS.(row));
			makearef(arDst, tmpRows.(sTmp));
			CopyAttributes(arDst, arSrc);
		}
	}

	// > пишем обратно
	for (i = 1; i <= q; i++)
	{
		row = "tr" + i;
		sTmp = "p" + i;
		makearef(arDst, GameInterface.TABLE_PERKS.(row));
		makearef(arSrc, tmpRows.(sTmp));
		CopyAttributes(arDst, arSrc);
	}
}

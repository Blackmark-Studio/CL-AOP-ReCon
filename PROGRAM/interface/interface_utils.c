
//---------------------------------------------------------------------------------------------------
// scrollimage
//---------------------------------------------------------------------------------------------------
void FillScrollImageWithCompanionShips(string sNodeName, int iNotUsed)
{

	DeleteAttribute(&GameInterface, sNodeName);
	GameInterface.(sNodeName).current = -1;

	GameInterface.(sNodeName).ImagesGroup.t0 = "BLANK_SHIP2";
	GameInterface.(sNodeName).BadTex1 = 0;
	GameInterface.(sNodeName).BadPic1 = "Not Used2";

	FillShipList(sNodeName + ".ImagesGroup", pchar);

	string attributeName, shipName;
	int iShipType, cn;
	int iListSize = 0;

	int isPossibleToFill = 1;
	for(int i= 0; i< COMPANION_MAX; i++)
	{
		cn = GetCompanionIndex(pchar, i);

		if(cn!= -1)
		{
			/*if(GetShipRemovable(&characters[cn]) == 0 && cn != nMainCharacterIndex)
			{
				isPossibleToFill = 0;
			}
			else
			{  */
				isPossibleToFill = 1;
			//}
			if(isPossibleToFill == 1)
			{
				iShipType = sti(characters[cn].ship.type);
				if(iShipType != SHIP_NOTUSED)
				{
					iShipType = sti(RealShips[iShipType].basetype);

					if (iShipType!= SHIP_NOTUSED)
					{
						shipName = ShipsTypes[iShipType].Name;
						attributeName = "pic" + (iListSize+1);

						GameInterface.(sNodeName).(attributeName).companionIndex = cn;
						GameInterface.(sNodeName).(attributeName).img1 = "ship";
						GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","SHIPS_"+shipName);

						iListSize++;		
					}
				}
			}
			/*else 
			{
				attributeName = "pic" + (i+1);
				GameInterface.(sNodeName).(attributeName).tex1= 0;
			}  */
		} 
		/*else 
		{
			attributeName = "pic" + (i+1);
			GameInterface.(sNodeName).(attributeName).tex1= 0;
		} */
	}

	GameInterface.(sNodeName).ListSize = iListSize;
	GameInterface.(sNodeName).NotUsed = iNotUsed - iListSize + 1;

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}
//---------------------------------------------------------------------------------------------------
void FillScrollImageWithFaces(string sNodeName, int iNotUsed, bool bCompanions, bool bPassengers)
{

	DeleteAttribute(&GameInterface, sNodeName);
	GameInterface.(sNodeName).current = -1;

	GameInterface.(sNodeName).ImagesGroup.t0 = "EMPTYFACE";
	GameInterface.(sNodeName).BadTex1 = 0;
	GameInterface.(sNodeName).BadPic1 = "emptyface";

	ref refCharacter = pchar;

	int iListSize = 0;
	int cn;
	string attributeName;
	aref pRef,pRef2;
	string PsgAttrName;


	if (bCompanions){

		FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 1); // companions

		for(int n= 0; n< COMPANION_MAX; n++)
		{
			attributeName = "pic" + (iListSize+1);
			cn = GetCompanionIndex(refCharacter, n);

			if(cn!= -1)
			{
				GameInterface.(sNodeName).(attributeName).character = cn;
				GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
				GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

				iListSize++;
			}
		}
	}

	if (bPassengers){


		makearef(pRef,refCharacter.Fellows.Passengers);
		FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 2); // passengers

		for(int i= 0; i< GetPassengersQuantity(refCharacter); i++)
		{
			attributeName = "pic" + (iListSize+1);
			PsgAttrName = "id"+(i+1);
			cn = sti(pRef.(PsgAttrName));

			if(cn!=-1 && !CheckAttribute(&characters[cn], "isfree"))
			{
				GameInterface.(sNodeName).(attributeName).character = cn;
				GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
				GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName + ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

				iListSize++;
			}
		}
	}
	/*
	if (bOfficers)
	{
	makearef(pRef,refCharacter.Fellows.Passengers);

	FillFaceList(sNodeName + ".ImagesGroup", refCharacter, 0); // officers

	for(int o= 0; o< 4; o++)
	{
	attributeName = "pic" + (iListSize+1);
	cn = sti(pRef.(PsgAttrName));
	if(cn!=-1)
	{
	GameInterface.(sNodeName).(attributeName).character = cn;
	GameInterface.(sNodeName).(attributeName).img1 = GetFacePicName(GetCharacter(cn));
	GameInterface.(sNodeName).(attributeName).tex1 = FindFaceGroupNum(sNodeName+ ".ImagesGroup","FACE128_"+ characters[cn].FaceID);

	iListSize++;		
	}
	}
	}
	*/
	GameInterface.(sNodeName).ListSize = iListSize;
	GameInterface.(sNodeName).NotUsed = iNotUsed;	

	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_SCROLL_CHANGE, sNodeName, -1);
}
/// boal -->
void StartAboveForm(bool _pauseTime)
{
    ChangeShowIntarface();
    
	EngineLayersOffOn(true);
	
    if (_pauseTime)
	{
		SetTimeScale(0.0);
		SetEventHandler("frame", "KZ|PlayMusicInterfaceFrame", 0);
	}
	else
	{
		SendMessage(pchar, "l", MSG_CHARACTER_STOPSTRAFE);
		DelEventHandler("frame", "KZ|PlayMusicInterfaceFrame");
	}
	
	locCameraSleep(true);
	LAi_CharacterDisableDialog(pchar);
}

void EndAboveForm(bool _pauseTime)
{
    if (_pauseTime)
    {
		SetTimeScale(1.0);
		TimeScaleCounter = 0;
	 	DelPerkFromActiveList("TimeSpeed");
	 	DeleteAttribute(pchar, "pause");
	}
	locCameraSleep(false);
	LAi_CharacterEnableDialog(pchar);
	if (!IsEntity(&BattleInterface) || !bLandInterfaceStart || !bMainMenu)
	{
		ChangeShowIntarface();
	}
}

void ChangeShowIntarface()
{
    if (bSeaActive && !bAbordageStarted)
    {
        if (!IsEntity(&BattleInterface))
        {
            InitBattleInterface();
            StartBattleInterface();
            RefreshBattleInterface();
        }
        else DeleteBattleInterface();
    }
	else
    {
		if (!IsEntity(&worldMap))
		{
			if (!bLandInterfaceStart && questMovieIsLockPlayerCtrl == false)// если батловый интерфейс не включен или главное меню
	        {
				StartBattleLandInterface(); // включаем
	        }
	        else EndBattleLandInterface(); // выключаем
        }
		else // на глобалке
		{
			if (!IsEntity(&BattleInterface))
			{
				InitWmInterface(); // включаем
//				if (!bGameMenuStart) wdmShowInterface(true);
				wdmShowInterface(true);
			}
			else
			{
				DeleteWmInterface(); // выключаем
				wdmShowInterface(false);
			}
        }
    }
}
// вернуть тип по номеру скрола в ф2 персонаж
string GetOfficerTypeByNum(int nCurScrollNum)
{
    string ret = "";
    
	switch (nCurScrollNum)
	{
		case 1: ret = "navigator";	break;
		case 2: ret = "boatswain";	break;
		case 3: ret = "cannoner";	break;
		case 4: ret = "doctor";		break;
		case 5: ret = "treasurer";	break;
		case 6: ret = "carpenter";	break;
		case 7: ret = "fighter";	break;
		case 8: ret = "fighter";	break;
		case 9: ret = "fighter";	break;
	}
	return ret;
}

//HardCoffee должности, на которые назначен офицер для интерфейсов character_all shipyard transfer_main
string GetOfficerOccupation(ref _officer)
{
	if (_officer.id == pchar.id) return "";
	string sProf = "(";
	int iTemp = sti(_officer.index);
	if (CheckAttribute(_officer, "Tasks.Clone")) return "(" +LowerFirst(XI_ConvertString("companionship"))+")";
	if (CheckAttribute(_officer, "Capellan")) return "(" +LowerFirst(XI_ConvertString("capellan"))+")";
	if (CheckAttribute(_officer, "NonRemovable")) return "(" +LowerFirst(XI_ConvertString("passengership"))+")";
	if (CheckAttribute(_officer, "prisoned") && _officer.prisoned == true) return "(" +LowerFirst(XI_ConvertString("prisonership"))+")";
	if (IsOfficer(_officer)) sProf += LowerFirst(XI_ConvertString("fighter"));
	if (sti(pchar.Fellows.Passengers.navigator) == iTemp)
	{
		if (sProf == "(") sProf += LowerFirst(XI_ConvertString("navigator"));
		else sProf = sProf +", " +LowerFirst(XI_ConvertString("navigator"));
	}
	if (sti(pchar.Fellows.Passengers.boatswain) == iTemp)
	{
		if (sProf == "(") sProf += LowerFirst(XI_ConvertString("boatswain"));
		else sProf = sProf +", " +LowerFirst(XI_ConvertString("boatswain"));
	}
	if (sti(pchar.Fellows.Passengers.cannoner) == iTemp)
	{
		if (sProf == "(") sProf += LowerFirst(XI_ConvertString("cannoner"));
		else sProf = sProf +", " +LowerFirst(XI_ConvertString("cannoner"));
	}
	if (sti(pchar.Fellows.Passengers.doctor) == iTemp)
	{
		if (sProf == "(") sProf += LowerFirst(XI_ConvertString("doctor"));
		else sProf = sProf +", " +LowerFirst(XI_ConvertString("doctor"));
	}
	if (sti(pchar.Fellows.Passengers.carpenter) == iTemp)
	{
		if (sProf == "(") sProf += LowerFirst(XI_ConvertString("carpenter"));
		else sProf = sProf +", " +LowerFirst(XI_ConvertString("carpenter"));
	}
	if (sti(pchar.Fellows.Passengers.treasurer) == iTemp)
	{
		if (sProf == "(") sProf += LowerFirst(XI_ConvertString("treasurer"));
		else sProf = sProf +", " +LowerFirst(XI_ConvertString("treasurer"));
	}
	if (sProf == "(") sProf += LowerFirst(XI_ConvertString("noOccupation"));
	sProf += ")";
	return sProf;
}

void SetOfficersSkills()
{
	string sCharacter = "pic" + (sti(GameInterface.PASSENGERSLIST.current) + 1);
	if (CheckAttribute(&GameInterface, "PASSENGERSLIST." + sCharacter))
	{
		if (CheckAttribute(&GameInterface, "PASSENGERSLIST." + sCharacter + ".character"))
		{
			sCharacter = GameInterface.PASSENGERSLIST.(sCharacter).character;
			ref otherchr = &characters[sti(sCharacter)];
			SetSPECIALMiniTable("TABLE_SMALLSKILL", otherchr);
			SetOTHERMiniTable("TABLE_SMALLOTHER", otherchr);
			SetFormatedText("OFFICER_NAME", GetFullNameTitulForm(otherchr));
			SetFormatedText("OFFICER_OCCUPATION", GetOfficerOccupation(otherchr));
			SetSelectable("ACCEPT_ADD_OFFICER", true);
			return;
		}
	}
	Table_Clear("TABLE_SMALLSKILL", false, true, true);
	Table_Clear("TABLE_SMALLOTHER", false, true, true);
	SetFormatedText("OFFICER_NAME", "");
	SetFormatedText("OFFICER_OCCUPATION", "");
	SetSelectable("ACCEPT_ADD_OFFICER", false);
}

////////////////////////////// общие методы для форм
void SetOTHERMiniTable(string _tabName, ref _chr)
{
    int     i;
	string  row, skillName, col;
    int     skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=5; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 23;
    	GameInterface.(_tabName).(row).td1.icon.height = 23;
    	GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.85;
		GameInterface.(_tabName).(row).td2.textoffset = "3,0";
		GameInterface.(_tabName).(row).td3.align = "right";
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Rank";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Rank";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Rank");
	GameInterface.(_tabName).tr1.td3.str = sti(_chr.rank);

	GameInterface.(_tabName).tr2.UserData.ID = "Life";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr2.td1.icon.image = "Life";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Life");
	GameInterface.(_tabName).tr2.td3.str = MakeInt(LAi_GetCharacterHP(_chr)) + " / " + MakeInt(LAi_GetCharacterMaxHP(_chr));

    GameInterface.(_tabName).tr3.UserData.ID = "Reputation";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr3.td1.icon.image = "Reputation";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Reputation");
	GameInterface.(_tabName).tr3.td3.str = XI_ConvertString(GetReputationName(sti(_chr.reputation)));
	GameInterface.(_tabName).tr3.td3.scale = 0.78;

    GameInterface.(_tabName).tr4.UserData.ID = "Loyality";
	GameInterface.(_tabName).tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr4.td1.icon.image = "Loyality";
	GameInterface.(_tabName).tr4.td2.str = XI_ConvertString("Loyality");
	if (_chr.id == pchar.id)
	{
		GameInterface.(_tabName).tr4.td3.str = "-";
	}
	else
	{
		GameInterface.(_tabName).tr4.td3.str = XI_ConvertString(GetLoyalityName(makeint(GetCharacterLoyality(_chr) * 100 / MAX_LOYALITY)));
	}
	GameInterface.(_tabName).tr4.td3.scale = 0.78;
	
	GameInterface.(_tabName).tr5.UserData.ID = "weight";
	GameInterface.(_tabName).tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr5.td1.icon.image = "weight";
	GameInterface.(_tabName).tr5.td2.str = XI_ConvertString("weight");
	GameInterface.(_tabName).tr5.td3.str = FloatToString(GetItemsWeight(_chr), 1) + " / "+GetMaxItemsWeight(_chr);
	
	// прорисовка
	Table_UpdateWindow(_tabName);
}
void SetSPECIALMiniTable(string _tabName, ref _chr)
{
    int     i;
	string  row, skillName, col;
    int     diff, skillVal;
    
    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	row = "tr1";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);

		GameInterface.(_tabName).(row).(col).fontidx = 0;
		GameInterface.(_tabName).(row).(col).scale = 0.85;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-6";
		GameInterface.(_tabName).(row).(col).str = XI_ConvertString(skillName + "T");
	}
	row = "tr2";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SPECIALType", i);
        skillVal = GetCharacterSPECIAL(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		GameInterface.(_tabName).(row).(col).scale = 0.95;
		GameInterface.(_tabName).(row).(col).textoffset = "-5,-2";
		diff = skillVal - GetSkillValue(_chr, SPECIAL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	row = "tr3";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);

		GameInterface.(_tabName).(row).(col).icon.group = "ICONS_SPEC";
	    GameInterface.(_tabName).(row).(col).icon.image = skillName + " skill icon";
	    GameInterface.(_tabName).(row).(col).icon.width = 30;
    	GameInterface.(_tabName).(row).(col).icon.height = 30;
	}
	row = "tr4";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("SelfType", i);
        skillVal = GetSummonSkillFromName(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		GameInterface.(_tabName).(row).(col).scale = 0.85;
		GameInterface.(_tabName).(row).(col).textoffset = "-9,-4";

		diff = skillVal - GetSkillValue(_chr, SKILL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	
	row = "tr5";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);

		GameInterface.(_tabName).(row).(col).icon.group = "ICONS_SPEC";
	    GameInterface.(_tabName).(row).(col).icon.image = skillName + " skill icon";
	    GameInterface.(_tabName).(row).(col).icon.width = 30;
    	GameInterface.(_tabName).(row).(col).icon.height = 30;
	}
	row = "tr6";
	for (i=1; i<=7; i++)
	{
	    col = "td" + i;
	    skillName = GetSkillNameByTRIdx("ShipType", i);
        skillVal = GetSummonSkillFromName(_chr, skillName);
		GameInterface.(_tabName).(row).(col).fontidx = 1;
		GameInterface.(_tabName).(row).(col).scale = 0.85;
		GameInterface.(_tabName).(row).(col).textoffset = "-9,-4";
		diff = skillVal - GetSkillValue(_chr, SKILL_TYPE, skillName);
		GameInterface.(_tabName).(row).(col).str = skillVal;
		if (diff == 0)
		{
     		GameInterface.(_tabName).(row).(col).color = argb(255,255,255,255);
		}
		else
		{
		   if (diff > 0)
		   {
	          GameInterface.(_tabName).(row).(col).color = argb(255,196,255,196);
	       }
	       else
	       {
	          GameInterface.(_tabName).(row).(col).color = argb(255,255,196,196);
	       }
		}
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
}

// опыт команды нпс _chr
void SetCrewExpTable(ref _chr, string _tabName, string _bar1, string _bar2, string _bar3)
{
    int     i;
	string  row, skillName, col;
    int     skillVal;

    GameInterface.(_tabName).select = 0;
	GameInterface.(_tabName).hr.td1.str = "";
	for (i=1; i<=3; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 23;
    	GameInterface.(_tabName).(row).td1.icon.height = 23;
    	GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.8;
		GameInterface.(_tabName).(row).td2.textoffset = "3,0";
		GameInterface.(_tabName).(row).td3.align = "right";
		GameInterface.(_tabName).(row).td3.scale = 0.8;
	}
	GameInterface.(_tabName).tr1.UserData.ID = "Sailors";
	GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr1.td1.icon.image = "Class";
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Sailors");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr1.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Sailors)));
	}
	else
	{
		GameInterface.(_tabName).tr1.td3.str = "";
	}
	
	GameInterface.(_tabName).tr2.UserData.ID = "Cannoners";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_SPEC";
    GameInterface.(_tabName).tr2.td1.icon.image = "Cannons skill icon";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Cannoners");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr2.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Cannoners)));
	}
	else
	{
		GameInterface.(_tabName).tr2.td3.str = "";
	}
	
    GameInterface.(_tabName).tr3.UserData.ID = "Soldiers";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_SPEC";
    GameInterface.(_tabName).tr3.td1.icon.image = "grappling skill icon";
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Soldiers");
	if (GetCrewQuantity(_chr) > 0)
    {
		GameInterface.(_tabName).tr3.td3.str = XI_ConvertString(GetExpName(sti(_chr.Ship.Crew.Exp.Soldiers)));
	}
	else
	{
		GameInterface.(_tabName).tr3.td3.str = "";
	}
	// прорисовка
	Table_UpdateWindow(_tabName);
	
	///  прогресбары
	GameInterface.StatusLine.(_bar1).Max   = 100;
    GameInterface.StatusLine.(_bar1).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar1).Value = sti(_chr.Ship.Crew.Exp.Sailors);
    }
    else
    {
    	GameInterface.StatusLine.(_bar1).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar1,0);
    
    GameInterface.StatusLine.(_bar2).Max   = 100;
    GameInterface.StatusLine.(_bar2).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar2).Value = sti(_chr.Ship.Crew.Exp.Cannoners);
    }
    else
    {
    	GameInterface.StatusLine.(_bar2).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar2,0);
    
    GameInterface.StatusLine.(_bar3).Max   = 100;
    GameInterface.StatusLine.(_bar3).Min   = 1;
    if (GetCrewQuantity(_chr) > 0)
    {
    	GameInterface.StatusLine.(_bar3).Value = sti(_chr.Ship.Crew.Exp.Soldiers);
    }
    else
    {
    	GameInterface.StatusLine.(_bar3).Value = 1;
    }
    SendMessage(&GameInterface,"lsl",MSG_INTERFACE_MSG_TO_NODE, _bar3,0);
}

void SetShipOTHERTable(string _tabName, ref _chr)
{
    int     i;
	string  row;

    int iShip = sti(_chr.ship.type);
	ref refBaseShip = GetRealShip(iShip);
	
	GameInterface.(_tabName).select = 0;
	for (i=1; i<=9; i++)
	{
	    row = "tr" + i;

	    GameInterface.(_tabName).(row).td1.icon.width = 23;
    	GameInterface.(_tabName).(row).td1.icon.height = 23;
    	GameInterface.(_tabName).(row).td1.icon.offset = "0, 2";
		GameInterface.(_tabName).(row).td2.align = "left";
		GameInterface.(_tabName).(row).td2.scale = 0.85;
		GameInterface.(_tabName).(row).td2.textoffset = "3,0";
		GameInterface.(_tabName).(row).td3.align = "right";
		GameInterface.(_tabName).(row).td3.scale = 0.85;
	}
	    GameInterface.(_tabName).tr1.UserData.ID = "Hull";
	    GameInterface.(_tabName).tr1.td1.icon.group = "ICONS_CHAR";
    	GameInterface.(_tabName).tr1.td1.icon.image = "Hull";
	// evganat - пасха
	if(CheckAttribute(refBaseShip,"atlaua_bonus.HP") && sti(refBaseShip.atlaua_bonus.HP) != 0)
	{
		GameInterface.(_tabName).tr1.td2.icon.group = "TRADE_TYPE";
		GameInterface.(_tabName).tr1.td2.icon.image = "ico_1";
		GameInterface.(_tabName).tr1.td2.icon.width = 8;
		GameInterface.(_tabName).tr1.td2.icon.height = 16;
		GameInterface.(_tabName).tr1.td2.icon.offset = "-12,12";
	}
	else
	{
		GameInterface.(_tabName).tr1.td2.icon.group = "";
		GameInterface.(_tabName).tr1.td2.icon.image = "";
	}
	
	GameInterface.(_tabName).tr1.td2.str = XI_ConvertString("Hull");
	GameInterface.(_tabName).tr1.td3.str = sti(_chr.ship.hp) + " / " + sti(refBaseShip.hp);
    if (!CheckAttribute(&RealShips[iShip], "Tuning.HP")) 
	{
		GameInterface.(_tabName).tr1.td3.color = argb(255,255,255,255);
	}
	else 
	{
		GameInterface.(_tabName).tr1.td3.color = argb(255,128,255,255);
	}

	GameInterface.(_tabName).tr2.UserData.ID = "Sails";
	GameInterface.(_tabName).tr2.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr2.td1.icon.image = "Sails";
	GameInterface.(_tabName).tr2.td2.str = XI_ConvertString("Sails");
	GameInterface.(_tabName).tr2.td3.str = sti(_chr.ship.sp) + " / " + sti(refBaseShip.sp);

    GameInterface.(_tabName).tr3.UserData.ID = "Speed";
	GameInterface.(_tabName).tr3.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr3.td1.icon.image = "Speed";
	// evganat - пасха
	if(CheckAttribute(refBaseShip,"atlaua_bonus.SpeedRate") && sti(refBaseShip.atlaua_bonus.SpeedRate) != 0)
	{
		GameInterface.(_tabName).tr3.td2.icon.group = "TRADE_TYPE";
		GameInterface.(_tabName).tr3.td2.icon.image = "ico_1";
		GameInterface.(_tabName).tr3.td2.icon.width = 8;
		GameInterface.(_tabName).tr3.td2.icon.height = 16;
		GameInterface.(_tabName).tr3.td2.icon.offset = "-12,12";
	}
	else
	{
		GameInterface.(_tabName).tr3.td2.icon.group = "";
		GameInterface.(_tabName).tr3.td2.icon.image = "";
	}
	
	GameInterface.(_tabName).tr3.td2.str = XI_ConvertString("Speed");
	if (CheckAttribute(_chr, "index") && IsCompanion(_chr))
	{
		GameInterface.(_tabName).tr3.td3.str = FloatToString(FindShipSpeed(_chr),2) + " / " + FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr3.td3.str = FloatToString(stf(refBaseShip.SpeedRate),2);
	}
	if (!CheckAttribute(&RealShips[iShip], "Tuning.SpeedRate")) 
	{
		GameInterface.(_tabName).tr3.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr3.td3.color = argb(255,128,255,255);
	}	
	

    GameInterface.(_tabName).tr4.UserData.ID = "Maneuver";
	GameInterface.(_tabName).tr4.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr4.td1.icon.image = "Maneuver";
	// evganat - пасха
	if(CheckAttribute(refBaseShip,"atlaua_bonus.TurnRate") && sti(refBaseShip.atlaua_bonus.TurnRate) != 0)
	{
		GameInterface.(_tabName).tr4.td2.icon.group = "TRADE_TYPE";
		GameInterface.(_tabName).tr4.td2.icon.image = "ico_1";
		GameInterface.(_tabName).tr4.td2.icon.width = 8;
		GameInterface.(_tabName).tr4.td2.icon.height = 16;
		GameInterface.(_tabName).tr4.td2.icon.offset = "-12,12";
	}
	else
	{
		GameInterface.(_tabName).tr4.td2.icon.group = "";
		GameInterface.(_tabName).tr4.td2.icon.image = "";
	}
	
	GameInterface.(_tabName).tr4.td2.str = XI_ConvertString("Maneuver");
	if (CheckAttribute(_chr, "index") && IsCompanion(_chr))
	{
  		GameInterface.(_tabName).tr4.td3.str = FloatToString((stf(refBaseShip.turnrate) * FindShipTurnRate(_chr)), 2) + " / " + FloatToString(stf(refBaseShip.TurnRate),2);
	}
	else
	{
	    GameInterface.(_tabName).tr4.td3.str = FloatToString(stf(refBaseShip.TurnRate),2);
	}
	if (!CheckAttribute(&RealShips[iShip], "Tuning.TurnRate")) 
	{
		GameInterface.(_tabName).tr4.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr4.td3.color = argb(255,128,255,255);
	}

	GameInterface.(_tabName).tr5.UserData.ID = "AgainstWind";
	GameInterface.(_tabName).tr5.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr5.td1.icon.image = "AgainstWind";
	GameInterface.(_tabName).tr5.td2.str = XI_ConvertString("AgainstWind");
	GameInterface.(_tabName).tr5.td3.str = FloatToString(stf(refBaseShip.WindAgainstSpeed),2);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.WindAgainst")) 
	{
		GameInterface.(_tabName).tr5.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr5.td3.color = argb(255,128,255,255);
	}
	
	
	RecalculateCargoLoad(_chr);
	GameInterface.(_tabName).tr6.UserData.ID = "Capacity";
	GameInterface.(_tabName).tr6.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr6.td1.icon.image = "Capacity";
	// evganat - пасха
	if(CheckAttribute(refBaseShip,"atlaua_bonus.Capacity") && sti(refBaseShip.atlaua_bonus.Capacity) != 0)
	{
		GameInterface.(_tabName).tr6.td2.icon.group = "TRADE_TYPE";
		GameInterface.(_tabName).tr6.td2.icon.image = "ico_1";
		GameInterface.(_tabName).tr6.td2.icon.width = 8;
		GameInterface.(_tabName).tr6.td2.icon.height = 16;
		GameInterface.(_tabName).tr6.td2.icon.offset = "-12,12";
	}
	else
	{
		GameInterface.(_tabName).tr6.td2.icon.group = "";
		GameInterface.(_tabName).tr6.td2.icon.image = "";
	}
	
	GameInterface.(_tabName).tr6.td2.str = XI_ConvertString("Capacity");
	GameInterface.(_tabName).tr6.td3.str = GetCargoLoad(_chr) + " / " + GetCargoMaxSpace(_chr);
	if (!CheckAttribute(&RealShips[iShip], "Tuning.Capacity")) 
	{
		GameInterface.(_tabName).tr6.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr6.td3.color = argb(255,128,255,255);
	}
	
	GameInterface.(_tabName).tr7.UserData.ID = "Crew";
	GameInterface.(_tabName).tr7.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr7.td1.icon.image = "Crew";
	// evganat - пасха
	if(CheckAttribute(refBaseShip,"atlaua_bonus.MaxCrew") && sti(refBaseShip.atlaua_bonus.MaxCrew) != 0)
	{
		GameInterface.(_tabName).tr7.td2.icon.group = "TRADE_TYPE";
		GameInterface.(_tabName).tr7.td2.icon.image = "ico_1";
		GameInterface.(_tabName).tr7.td2.icon.width = 8;
		GameInterface.(_tabName).tr7.td2.icon.height = 16;
		GameInterface.(_tabName).tr7.td2.icon.offset = "-12,12";
	}
	else
	{
		GameInterface.(_tabName).tr7.td2.icon.group = "";
		GameInterface.(_tabName).tr7.td2.icon.image = "";
	}
	
	GameInterface.(_tabName).tr7.td2.str = XI_ConvertString("Crew");
	GameInterface.(_tabName).tr7.td3.str = GetCrewQuantity(_chr) + " : "+ sti(refBaseShip.MinCrew) +" / " + sti(refBaseShip.OptCrew);	
	if (!CheckAttribute(&RealShips[iShip], "Tuning.MaxCrew")) 
	{
		GameInterface.(_tabName).tr7.td3.color = argb(255,255,255,255);
	}
	else
	{
		GameInterface.(_tabName).tr7.td3.color = argb(255,128,255,255);
	}
	
	GameInterface.(_tabName).tr8.UserData.ID = "sCannons";
	GameInterface.(_tabName).tr8.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr8.td1.icon.image = "Caliber";
	GameInterface.(_tabName).tr8.td2.str = XI_ConvertString("sCannons");
	GameInterface.(_tabName).tr8.td3.str = XI_ConvertString("caliber" + refBaseShip.MaxCaliber) + " / " + sti(refBaseShip.CannonsQuantity);
	
	if (!CheckAttribute(&RealShips[iShip], "Tuning.Cannon")) 
		GameInterface.(_tabName).tr8.td3.color = argb(255,255,255,255);
	else
		GameInterface.(_tabName).tr8.td3.color = argb(255,128,255,255);
		
	GameInterface.(_tabName).tr9.UserData.ID = "CannonType";
	GameInterface.(_tabName).tr9.td1.icon.group = "ICONS_CHAR";
    GameInterface.(_tabName).tr9.td1.icon.image = "Cannons";
	GameInterface.(_tabName).tr9.td2.str = XI_ConvertString(GetCannonType(sti(_chr.Ship.Cannons.Type)) + "s2");
	if(GetCannonsNum(_chr) > 0)
		GameInterface.(_tabName).tr9.td3.str = XI_ConvertString("caliber" + GetCannonCaliber(sti(_chr.Ship.Cannons.Type))) + " / " + GetCannonsNum(_chr);
	else
		GameInterface.(_tabName).tr9.td3.str = GetCannonsNum(_chr);	
	
	// прорисовка
	Table_UpdateWindow(_tabName);
}

void SetFoodShipInfo(ref chr, string _textName)
{
	int iColor, iFood;
	string sText;
	
	SetFormatedText(_textName, "");
	if (sti(chr.ship.type) != SHIP_NOTUSED)
	{
		sText = XI_ConvertString("Provisions_on_ship") + " " + XI_ConvertString("ForShip") + " ";
		iFood = CalculateShipFood(chr);
		sText = sText + FindDaysString(iFood);
		SetFormatedText(_textName, sText);
		if(iFood >= 5)
		{
			iColor = argb(255,255,255,192);
		}
		if(iFood > 10)
		{
			iColor = argb(255,192,255,192);
		}
		if(iFood < 5)
		{
			iColor = argb(255,255,192,192);
		}
		SendMessage(&GameInterface,"lslll",MSG_INTERFACE_MSG_TO_NODE, _textName, 8,-1,iColor);	
	}
}

// Warship 11.07.09 Вывести в текстовое поле инфу о количестве дней, на сколько хватит рому на судне
void SetRumShipInfo(ref _character, string _node)
{
	int color, rum;
	string text;
	
	SetFormatedText(_node, "");
	
	if(sti(_character.ship.type) != SHIP_NOTUSED)
	{
		text = XI_ConvertString("Rum_on_ship") + " " + XI_ConvertString("ForShip") + " ";
		rum = CalculateShipRum(_character);
		text = text + FindDaysString(rum);
		SetFormatedText(_node, text);
		
		if(rum < 3)
		{
			color = argb(255, 255, 192, 192);
		}
		
		if(rum >= 3)
		{
			color = argb(255, 255, 255, 192);
		}
		
		if(rum >= 10)
		{
			color = argb(255, 192, 255, 192);
		}
		
		SendMessage(&GameInterface, "lslll", MSG_INTERFACE_MSG_TO_NODE, _node, 8, -1, color);	
	}
}

// evganat - двигалка интерфейсов

object MoveList;

void AddNodeToMoveList(string nodeName, int left, int top, int right, int bottom)
{
	float offsetX, offsetY;
	GetXYWindowOffset(&offsetX, &offsetY);
	MoveList.(nodeName).left = makeint(offsetX+left);
	MoveList.(nodeName).top = makeint(offsetY+top);
	MoveList.(nodeName).right = makeint(offsetX+right);
	MoveList.(nodeName).bottom = makeint(offsetY+bottom);
}

void DeleteNodeFromMoveList(string nodeName)
{
	if (CheckAttribute(&MoveList, nodeName))
		DeleteAttribute(&MoveList, nodeName);
}

void ClearMoveList()
{
	int n = GetAttributesNum(&MoveList);
	aref arNode;
	string nodeName;
	for (int i=0; i<n; i++)
	{
		arNode = GetAttributeN(&MoveList, 0);
		nodeName = GetAttributeName(arNode);
		DeleteAttribute(&MoveList, nodeName);
	}
}

#event_handler("MoveNodeSteady", "MoveNodeToDirSteady");
void MoveNodeToDirSteady()
{
	string nodeName = GetEventData();
	string dir = GetEventData();
	int dist = GetEventData();
	int remain = GetEventData();
	string tag = GetEventData();
	if(remain <= 0)
	{
		PostEvent("MoveFinished", 100, "s", tag);
		return;
	}
	if (!CheckAttribute(&MoveList, nodeName))
		return;
	int oldleft = sti(MoveList.(nodeName).left);
	int oldtop = sti(MoveList.(nodeName).top);
	int oldright = sti(MoveList.(nodeName).right);
	int oldbottom = sti(MoveList.(nodeName).bottom);
	int newleft, newright, newtop, newbottom;
	int kleft = 0;
	int kright = 0;
	int ktop = 0;
	int kbottom = 0;
	switch(dir)
	{
		case "up":			ktop = -1;		kbottom = -1;	break;
		case "down":		ktop = 1;		kbottom = 1;	break;
		case "left":		kleft = -1;		kright = -1;	break;
		case "right":		kleft = 1;		kright = 1;		break;
		case "up-left":		ktop = -1;		kbottom = -1;	kleft = -1;		kright = -1;		break;
		case "up-right":	ktop = -1;		kbottom = -1;	kleft = 1;		kright = 1;			break;
		case "down-left":	ktop = 1;		kbottom = 1;	kleft = -1;		kright = -1;		break;
		case "down-right":	ktop = 1;		kbottom = 1;	kleft = 1;		kright = 1;			break;
	}
	if(remain < dist)
		dist = remain;
	newleft = oldleft + kleft*dist;
	newright = oldright + kright*dist;
	newtop = oldtop + ktop*dist;
	newbottom = oldbottom + kbottom*dist;
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, nodeName, -1, 4, newleft, newtop, newright, newbottom);
	MoveList.(nodeName).left = newleft;
	MoveList.(nodeName).top = newtop;
	MoveList.(nodeName).right = newright;
	MoveList.(nodeName).bottom = newbottom;

	
	PostEvent("MoveNodeSteady", 20, "sslls", nodeName, dir, dist, remain-dist, tag);

}	

#event_handler("MoveNodeSoftly", "MoveNodeToDirSoftly");
void MoveNodeToDirSoftly()
{
	string nodeName = GetEventData();
	string dir = GetEventData();
	int startdist = GetEventData();
	int remain = GetEventData();
	int total = GetEventData();
	string tag = GetEventData();
	if(remain <= 0)
	{
		PostEvent("MoveFinished", 100, "s", tag);
		return;
	}
	if (!CheckAttribute(&MoveList, nodeName))
		return;
	
	int oldleft = sti(MoveList.(nodeName).left);
	int oldtop = sti(MoveList.(nodeName).top);
	int oldright = sti(MoveList.(nodeName).right);
	int oldbottom = sti(MoveList.(nodeName).bottom);
	int newleft, newright, newtop, newbottom;
	int kleft = 0;
	int kright = 0;
	int ktop = 0;
	int kbottom = 0;
	switch(dir)
	{
		case "up":			ktop = -1;		kbottom = -1;	break;
		case "down":		ktop = 1;		kbottom = 1;	break;
		case "left":		kleft = -1;		kright = -1;	break;
		case "right":		kleft = 1;		kright = 1;		break;
		case "up-left":		ktop = -1;		kbottom = -1;	kleft = -1;		kright = -1;		break;
		case "up-right":	ktop = -1;		kbottom = -1;	kleft = 1;		kright = 1;			break;
		case "down-left":	ktop = 1;		kbottom = 1;	kleft = -1;		kright = -1;		break;
		case "down-right":	ktop = 1;		kbottom = 1;	kleft = 1;		kright = 1;			break;
	}
	
	int dist = startdist;
	if(remain >= total*0.8)
	{
		dist = round_near((4.2 - (makefloat(remain)/makefloat(total))*4)*startdist);
	}
	else
	{
		if(remain <= total*0.2)
		{
			dist = round_near(startdist*(0.2 + 4*(makefloat(remain)/makefloat(total))));
		}
	}
	
	if(remain < dist)
		dist = remain;
	
	newleft = oldleft + kleft*dist;
	newright = oldright + kright*dist;
	newtop = oldtop + ktop*dist;
	newbottom = oldbottom + kbottom*dist;
	SendMessage(&GameInterface, "lsllllll", MSG_INTERFACE_MSG_TO_NODE, nodeName, -1, 4, newleft, newtop, newright, newbottom);
	MoveList.(nodeName).left = newleft;
	MoveList.(nodeName).top = newtop;
	MoveList.(nodeName).right = newright;
	MoveList.(nodeName).bottom = newbottom;
	
	PostEvent("MoveNodeSoftly", 20, "ssllls", nodeName, dir, startdist, remain-dist, total, tag);
}	

void MoveAllNodesToDirSteady(string dir, int speed, int dist, string tag)
{
	int n = GetAttributesNum(MoveList);
	string nodeName;
	aref arNode;
	for (int i=0; i<n; i++)
	{
		arNode = GetAttributeN(&MoveList, i);
		nodeName = GetAttributeName(arNode);
		Event("MoveNodeSteady", "sslls", nodeName, dir, speed, dist, tag);
	}
}

void MoveAllNodesToDirSoftly(string dir, int speed, int dist, string tag)
{
	int n = GetAttributesNum(MoveList);
	string nodeName;
	aref arNode;
	for (int i=0; i<n; i++)
	{
		arNode = GetAttributeN(&MoveList, i);
		nodeName = GetAttributeName(arNode);
		Event("MoveNodeSoftly", "ssllls", nodeName, dir, speed, dist, dist, tag);
	}
}

// evganat - окрашивание текста -->
string ColorText(string sText, string color)
{
	string sPrefix = GetColorChar(color);
	if(sPrefix != "")
		return sPrefix + sText + "␍";
	
	return sText;
}

string ColorTextLine(string sText, string color)
{
	string sPrefix = GetColorChar(color);
	if(sPrefix != "")
		return sPrefix + sText;
	
	return sText;
}

string GetColorChar(string color)
{
	string sPrefix = "";
	switch(color)
	{
		// TODO Конфликтующие неиспользуемые символы покраски временно закоменчены
//		case "red":		    sPrefix = "¬";		break;	// красный						255, 255, 0, 0
//		case "green":		sPrefix = "¢";		break;	// зелёный						255, 0, 255, 0
//		case "blue":		sPrefix = "£";		break;	// голубой						255, 0, 0, 255
//		case "yellow":		sPrefix = "¤";		break;	// жёлтый						255, 255, 255, 0
//		case "purple":		sPrefix = "¥";		break;	// пурпурный					255, 128, 0, 128
//		case "aqua":		sPrefix = "¦";		break;	// цвет морской волны			255, 0, 255, 255
//		case "black":		sPrefix = "§";		break;	// чёрный						255, 0, 0, 0
//		case "gray":		sPrefix = "¨";		break;	// серый						255, 128, 128, 128
		case "white":		sPrefix = "‼";		break;	// белый						255, 255, 255, 255
//		case "darkgreen":	sPrefix = "ª";		break;	// тёмно-зелёный				255, 0, 100, 0
//		case "brown":		sPrefix = "®";		break;	// коричневый					255, 139, 69, 19
//		case "yellowgreen":	sPrefix = "¯";		break;	// жёлто-зелёный				255, 154, 205, 50
//		case "pink":		sPrefix = "×";		break;	// розовый						255, 255, 192, 203
		case "gold":		sPrefix = "⁇";		break;	// золотой						255, 255, 215, 0
		case "khaki":		sPrefix = "⁈";		break;	// хаки							255, 240, 230, 140
//		case "violet":		sPrefix = "³";		break;	// фиолетовый					255, 238, 130, 238
//		case "darkred":		sPrefix = "´";		break;	// тёмно-красный				255, 139, 0, 0
		case "darkgray":	sPrefix = "⁉";		break;	// тёмно-серый					255, 169, 169, 169
//		case "orange":		sPrefix = "¶";		break;	// оранжевый					255, 255, 165, 0
//		case "navy":		sPrefix = "÷";		break;	// тёмно-синий					255, 0, 0, 128
		case "contra":		sPrefix = "ʖ";		break;	// контрабанда (светло-красный)	255, 255, 196, 196
		case "export":		sPrefix = "ʔ";		break;	// экспорт (светло-зелёный)		255, 196, 255, 196
		case "import":		sPrefix = "ʕ";		break;	// импорт (светло-синий)		255, 196, 196, 255
		case "lightblue":	sPrefix = "ʞ";		break;	// светло-голубой				255, 128, 255, 255
//		case "darkorange":	sPrefix = "ʧ";		break;	// тёмно-оранжевый				255, 255, 116, 62
		case "goldenrod":	sPrefix = "ʘ";		break;	// золотисто-берёзовый			255, 218, 165, 32
	}
	return sPrefix;
}
// evganat - окрашивание текста <--

int GetColorInt(string sClolor)
{
    return GetColorArgb(sClolor, 255);
}

int GetColorArgb(string sClolor, int iAlpha)
{
    if (sClolor == "") return argb(255, 255, 255, 255);
    if (iAlpha > 255) iAlpha = 255;
    else if (iAlpha < 0) iAlpha = 0;
    switch (sClolor)
	{
		case "red":		    return argb(iAlpha, 255, 0, 0);		break;	// красный
		case "green":		return argb(iAlpha, 0, 255, 0);		break;	// зелёный
		case "blue":		return argb(iAlpha, 0, 0, 255);		break;	// голубой
		case "yellow":		return argb(iAlpha, 255, 255, 0);	break;	// жёлтый
		case "purple":		return argb(iAlpha, 128, 0, 128);	break;	// пурпурный
		case "aqua":		return argb(iAlpha, 0, 255, 255);	break;	// цвет морской волны
		case "black":		return argb(iAlpha, 0, 0, 0);		break;	// чёрный
		case "gray":		return argb(iAlpha, 128, 128, 128);	break;	// серый
		case "white":		return argb(iAlpha, 255, 255, 255);	break;	// белый
		case "darkgreen":	return argb(iAlpha, 0, 100, 0);		break;	// тёмно-зелёный
		case "brown":		return argb(iAlpha, 139, 69, 19);	break;	// коричневый
		case "yellowgreen":	return argb(iAlpha, 154, 205, 50);	break;	// жёлто-зелёный
		case "pink":		return argb(iAlpha, 255, 192, 203);	break;	// розовый
		case "gold":		return argb(iAlpha, 255, 215, 0);	break;	// золотой
		case "khaki":		return argb(iAlpha, 240, 230, 140);	break;	// хаки
		case "violet":		return argb(iAlpha, 238, 130, 238);	break;	// фиолетовый
		case "darkred":		return argb(iAlpha, 139, 0, 0);		break;	// тёмно-красный
		case "darkgray":	return argb(iAlpha, 169, 169, 169);	break;	// тёмно-серый
		case "orange":		return argb(iAlpha, 255, 165, 0);	break;	// оранжевый
		case "navy":		return argb(iAlpha, 0, 0, 128);		break;	// тёмно-синий
		case "contra":		return argb(iAlpha, 255, 196, 196);	break;	// контрабанда (светло-красный)
		case "export":		return argb(iAlpha, 196, 255, 196);	break;	// экспорт (светло-зелёный)
		case "import":		return argb(iAlpha, 196, 196, 255);	break;	// импорт (светло-синий)
		case "lightblue":	return argb(iAlpha, 128, 255, 255);	break;	// светло-голубой
		case "darkorange":	return argb(iAlpha, 255, 116, 62);	break;	// тёмно-оранжевый
		case "goldenrod":	return argb(iAlpha, 218, 165, 32);	break;	// золотисто-берёзовый
	}
	return argb(255, 255, 255, 255);
}

//HardCoffee перенёс из QuestsUtilite.c вызывается в interface\items.c
void SortItems(ref NPChar)
{// отсортировать предметы в кармане, сундуке
    aref   arToChar;
    aref   arFromChar;
    object objChar;
    int    i;
    aref   curItem;
	string attr;
	ref    itm;
	ref    rObj;
	int    iSortIndex;
	bool   ok;

    objChar.Items = "";
    rObj = &objChar;

    makearef(arToChar,   rObj.Items);
    makearef(arFromChar, NPChar.Items);

    CopyAttributes(arToChar, arFromChar);

    DeleteAttribute(NPChar, "Items");
    NPChar.Items = "";

    makearef(arFromChar, NPChar.equip); // экипировка
    int iMax = GetAttributesNum(arFromChar);
    for(i=0; i<iMax; i++)
    {
        curItem = GetAttributeN(arFromChar, i);
        attr = GetAttributeValue(curItem);
        if (attr != "") //патенты клинит
        {
        	NPChar.Items.(attr) = sti(rObj.Items.(attr));
        }
    }
    // неоптимальная сортировка по индексу itm.SortIndex
	// размерность индекса определяется автоматом - длжен быть непрерывен!!, начинается с 1 - целое число
	ok = true;
	iSortIndex = 1;
	while (iSortIndex < 3)// 2 типа
	{
		ok = false;
		for (i=0; i<TOTAL_ITEMS; i++)
		{
			// Warship 11.05.09 fix для новой системы предметов
			if(!CheckAttribute(&Items[i], "ID"))
			{
				continue;
			}

			makeref(itm, Items[i]);
			attr = itm.id;
			if (CheckAttribute(rObj, "items."+attr) && CheckAttribute(itm, "SortIndex") && sti(itm.SortIndex) == iSortIndex)
			{
                NPChar.Items.(attr) = sti(rObj.Items.(attr));
	   			ok = true;
	      	}
	    }
	    iSortIndex++;
    }
    // все остальные
    for (i=0; i<TOTAL_ITEMS; i++)
	{
		// Warship 11.05.09 fix для новой системы предметов
		if(!CheckAttribute(&Items[i], "ID"))
		{
			continue;
		}

		makeref(itm, Items[i]);
		attr = itm.id;
		if (CheckAttribute(rObj, "items."+attr) && !CheckAttribute(itm, "SortIndex"))
		{
   			NPChar.Items.(attr) = sti(rObj.Items.(attr));
   			ok = true;
      	}
    }
}

//HardCoffee перенёс из QuestsUtilite.c
// AlexBlade - переведён на native метод
string GetStrSmallRegister(string sBase)
{
	return StringToLower(sBase);
}

// Warship 15.08.09 -->
// Перевод всей строки в верхний регистр
// AlexBlade - переведён на native метод
string ToUpper(string _text)
{
	return StringToUpper(_text);
}

// Первый символ в верхний регистр
string UpperFirst(string _text)
{
	string firstSymbol = GetSymbol(_text, 0);
	return StrReplaceFirst(_text, firstSymbol, ToUpper(firstSymbol));
}

// Первый символ в нижний регистр
string LowerFirst(string _text)
{
	string firstSymbol = GetSymbol(_text, 0);
	return StrReplaceFirst(_text, firstSymbol, GetStrSmallRegister(firstSymbol));
}
// <--

float GetScreenScale()
{
	return stf(Render.screen_y) / screenscaling;
}

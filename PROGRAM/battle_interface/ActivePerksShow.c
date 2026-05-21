
object objActivePerkShower;
object objSeaPerkShower;

#event_handler(EVENT_LOCATION_LOAD, "procLoadIntoNew");

void InitActivePerkShower()
{
	InitShowPlaces();
}

void InitShowPlaces()
{
	float fHtRatio = GetScreenScale();

	int i = 84;

	if (IsEntity(&worldMap))
		i = 4;

	objActivePerkShower.ShowParam.PosRect.left		= sti(showWindow.right) - RecalculateHIcon(makeint(100 * fHtRatio));
	objActivePerkShower.ShowParam.PosRect.top		= sti(showWindow.bottom)/2 + RecalculateVIcon(makeint(i * fHtRatio));
	objActivePerkShower.ShowParam.PosRect.right		= sti(showWindow.right) - RecalculateHIcon(makeint(42 * fHtRatio));
	objActivePerkShower.ShowParam.PosRect.bottom	= sti(showWindow.bottom) - RecalculateVIcon(makeint(0 * fHtRatio));
	objActivePerkShower.ShowParam.IconSize.horz		= RecalculateHIcon(makeint(48 * fHtRatio));
	objActivePerkShower.ShowParam.IconSize.vert		= RecalculateVIcon(makeint(48 * fHtRatio));
	objActivePerkShower.ShowParam.IconSpace.horz	= RecalculateHIcon(2);
	objActivePerkShower.ShowParam.IconSpace.vert	= RecalculateVIcon(2);
}

void procLoadIntoNew()
{
	UnloadActivePerkShower();
	SetEventHandler("frame","LoadActivePerkShower",1);
}

void LoadActivePerkShower()
{
	DelEventHandler("frame","LoadActivePerkShower");

	DeleteAttribute(&objActivePerkShower,"PerkList.list");
	DeleteAttribute(&objActivePerkShower,"Textures");

	bool isSeaLoaded = bSeaActive && !bAbordageStarted;
	// информация о текстурах
	if(isSeaLoaded)
	{	// морская часть
		objActivePerkShower.Textures.t0.file = "battle_interface\list_icons.tga";
		objActivePerkShower.Textures.t0.horz = 16;
		objActivePerkShower.Textures.t0.vert = 8;
	}
	else
	{	// земная часть
		objActivePerkShower.Textures.t0.file = "battle_interface\LandCommands.tga";
		objActivePerkShower.Textures.t0.horz = 16;
		objActivePerkShower.Textures.t0.vert = 4;
	}

	CreateEntity(&objActivePerkShower,"ActivePerkShower");
	if(isSeaLoaded)
	{	// морская часть
		LayerAddObject(SEA_EXECUTE,&objActivePerkShower,-1);
		LayerAddObject(SEA_REALIZE,&objActivePerkShower,-1);

		//fix при выходе в море, очищаем наземные активные перки - AlexBlade
		ClearActivePerks(pchar);
	}
	else
	{
		LayerAddObject(EXECUTE,&objActivePerkShower,-1);
		LayerAddObject(REALIZE,&objActivePerkShower,-1);
	}
	InitShowPlaces();
	SendMessage(&objActivePerkShower,"l",MSG_ACTIVE_PERK_ICON_REFRESH);
	InitSeaPerkShower_AddPerks();

	LoadActivePerkShower_SetPerks(isSeaLoaded);
}

void LoadActivePerkShower_SetPerks(bool isSeaLoaded)
{
	aref arPerksRoot,arPerk;
	ref chr;
	int i,j,n,iTemp;
	string perkName, sOfficerType;
	bool bOk = false;

	if (isSeaLoaded)
	{
		makearef(arPerksRoot, ChrPerksList.list);
		n = GetAttributesNum(arPerksRoot);

		for (i=0; i<n; i++)
		{
			arPerk = GetAttributeN(arPerksRoot,i);
			bOk = CheckAttribute(arPerk, "OfficerType") && CheckAttribute(arPerk,"TimeDelay") && CheckAttribute(arPerk,"BaseType") && arPerk.BaseType == "ship";
			if (!bOk) {continue;}

			perkName = GetAttributeName(arPerk);
			if (CheckAttribute(pchar, "perks.list."+perkName+".delay"))
			{
			    chr = pchar;
			}
			else
			{
				iTemp = -1;
				for(j=1; j<=6; j++)
				{
					sOfficerType = GetOfficerTypeByNum(j);
					if (arPerk.OfficerType == sOfficerType)
					{
						iTemp = sti(pchar.Fellows.Passengers.(sOfficerType));
						if (iTemp >= 0) {break;}
					}
				}
				if (iTemp < 0) {continue;}
				chr = GetCharacter(iTemp);
				if (!CheckAttribute(chr, "perks.list."+perkName+".delay")) {continue;}
			}
			iTemp = sti(chr.perks.list.(perkName).delay);
			if (CheckAttribute(chr, "perks.list."+perkName+".active"))
			{
				AddPerkToActiveList(perkName);
				iTemp = sti(chr.perks.list.(perkName).active);
				SetCooldownTextForActivePerkInList(perkName, iTemp, true);
			}
			else
			{
				AddPerkToActiveListWithCooldown(perkName, iTemp);
			}
		}

		if(IsEntity(&objSeaPerkShower))
		{
			SendMessage(&objSeaPerkShower,"l",MSG_ACTIVE_PERK_ICON_REFRESH);
		}
	}
	else
	{
		makearef(arPerksRoot,pchar.perks.list);
		n = GetAttributesNum(arPerksRoot);

		for(j=0; j<n; j++)
		{
			arPerk = GetAttributeN(arPerksRoot,j);

			if(CheckAttribute(arPerk,"delay"))
			{
				perkName = GetAttributeName(arPerk);

				bool isPerkShow = !IsSeaActivePerk(perkName) || isSeaLoaded;
				if (!isPerkShow)
					continue;

				if(CheckAttribute(arPerk,"active"))
				{
					AddPerkToActiveList(perkName);
					SetCooldownTextForActivePerkInList(perkName, sti(arPerk.active), true);
				}
				else
				{
					AddPerkToActiveListWithCooldown(perkName, sti(arPerk.delay));
				}
			}
		}
	}
}

void UnloadActivePerkShower()
{
	DeleteClass(&objActivePerkShower);
	DeleteAttribute(&objActivePerkShower,"PerkList");
}

bool IsPerkIntoList(string perkID)
{
	return CheckAttribute(&objActivePerkShower,"PerkList.list."+perkID);
}

void AddPerkToActiveList(string perkID)
{
	if( !IsEntity(&objActivePerkShower) ) return;
	aref arRoot,arCur;

	// seaPerkShower -->
	bool isSeaLoaded = bSeaActive && !bAbordageStarted;
	if (isSeaLoaded && perkID != "TimeSpeed")
	{
	    if(!IsEntity(&objSeaPerkShower)) return;

		SeaPerkShower_AddPerk(perkID);
	    return;
	}
	// <--

	makearef(arRoot,objActivePerkShower.PerkList.list);
	if( CheckAttribute(arRoot,perkID) ) return;

	makearef(arCur,arRoot.(perkID));
	arCur.texture = GetTextureIndex(GetPerkTextureName(perkID));
	arCur.pic_idx = GetPerkPictureIndex(perkID);
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"add",arCur);
}

// > AlexBlade - добавить перк с отображением времени восстановления
void AddPerkToActiveListWithCooldown(string perkId, int cooldownInSeconds)
{
	// seaPerkShower -->
	bool isSeaLoaded = bSeaActive && !bAbordageStarted;
	if (isSeaLoaded && perkID != "TimeSpeed")
	{
	    if(!IsEntity(&objSeaPerkShower)) return;

		SeaPerkShower_AddPerkWithCooldown(perkID, cooldownInSeconds, false);
	    return;
	}
	// <--
	AddPerkToActiveListEx(perkID, GetCooldownPerkIconColor(), its(cooldownInSeconds), ARGB(255, 255, 255, 255), 1.2, true);
}

// > AlexBlade - обновить текст на иконке
void SetCooldownTextForActivePerkInList(string perkId, int cooldownInSeconds, bool bActive)
{
	if( !IsEntity(&objActivePerkShower) ) return;
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);

	if (perkId == "TimeSpeed")
	{
		SetTimeScaleText("x" + cooldownInSeconds, ARGB(255, 255, 255, 255), 1.25);
		return;
	}

	// seaPerkShower -->
	bool isSeaLoaded = bSeaActive && !bAbordageStarted;
	if (isSeaLoaded)
	{
	    if(!IsEntity(&objSeaPerkShower)) return;
		SeaPerkShower_AddPerkWithCooldown(perkID, cooldownInSeconds, bActive);
	    return;
	}
	// <--

	if (!CheckAttribute(arRoot,perkID) && !bActive)
	{
		AddPerkToActiveListWithCooldown(perkId, cooldownInSeconds);
		return;
	}

	float fHtRatio = GetScreenScale();
	int iColorIcon = GetCooldownPerkIconColor();	// red color icon (cooldown)
	int iColorText = ARGB(255, 255, 255, 255);	// white color text (cooldown)

	makearef(arCur,arRoot.(perkID));

	if (bActive)
	{
		// > цвет иконки перка при активности
		iColorIcon = GetActivePerkIconColor();	// green color icon (active)
	}

	arCur.texture = GetTextureIndex(GetPerkTextureName(perkID));
	arCur.pic_idx = GetPerkPictureIndex(perkID);
	arCur.iconColor = iColorIcon;
	arCur.textColor = iColorText;
	arCur.textScale = 1.25 * fHtRatio;
	arCur.bTextShadow = true;
	arCur.text = its(cooldownInSeconds);
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"setStyle",arCur);
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"setText",arCur);
}

// > AlexBlade - добавить иконку (+ цвет иконки, + текст, + цвет,масштаб,тень текста)
void AddPerkToActiveListEx(string perkID, int iconColor, string text, int textColor, float textScale, bool bTextShadow)
{
	if( !IsEntity(&objActivePerkShower) ) return;
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);

	float fHtRatio = GetScreenScale();
	makearef(arCur,arRoot.(perkID));
	arCur.texture = GetTextureIndex(GetPerkTextureName(perkID));
	arCur.pic_idx = GetPerkPictureIndex(perkID);
	arCur.iconColor = iconColor;
	arCur.textColor = textColor;
	arCur.textScale = textScale * fHtRatio;
	arCur.bTextShadow = bTextShadow;
	arCur.text = text;
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"add",arCur);
}

void SetTimeScaleText(string text, int textColor, float textScale)
{
    if( !IsEntity(&objActivePerkShower) ) return;
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);
	string perkID = "TimeSpeed";
	bool isSet = CheckAttribute(arRoot,perkID);

	float fHtRatio = GetScreenScale();
	makearef(arCur,arRoot.(perkID));
	arCur.texture = GetTextureIndex(GetPerkTextureName(perkID));
	arCur.pic_idx = GetPerkPictureIndex(perkID);
	arCur.textColor = textColor;
	arCur.textScale = textScale * fHtRatio;
	arCur.textOffsetX = makeint(-16 * fHtRatio);
	arCur.textOffsetY = makeint(-12 * fHtRatio);
	arCur.text = text;

	if(isSet)
	{
		SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"setStyle",arCur);
		SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"setText",arCur);
	}
	else
	{
		SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"add",arCur);
	}

}

int GetPerkPictureIndex(string perkName)
{
	switch(perkName)
	{
		case "TimeSpeed":
	        if (bSeaActive && !bAbordageStarted) return 59;
			else return 15;
		break;
		case "Sink":			return 43; break;
		case "Repair":			return 55; break;
		// boal зачем же так игру кастрировать? Грустно, однако -->
		case "Rush":	        return 28; break;
		case "SecondWind":		return 55; break;
		case "LightRepair":		return 54; break;
		case "InstantRepair":	return 55; break;
		case "ImmediateReload":	return 53; break;
		case "Turn180":			return 56; break;
		// boal <--
	}
	trace("WARNING!!! Perk name - "+perkName+" hav`t picture");
	return 0;
}

string GetPerkTextureName(string perkName)
{
	switch(perkName)
	{
		case "TimeSpeed":
			if(bSeaActive && !bAbordageStarted)
			{
				return "battle_interface\list_icons.tga";
			}
			else
			{
			    return "battle_interface\LandCommands.tga";
			}
		break;
		case "Sink":			return "battle_interface\list_icons.tga"; break;
		case "Repair":			return "battle_interface\list_icons.tga"; break;
		case "Rush":			return "battle_interface\LandCommands.tga";	break;
		case "SecondWind":		return "battle_interface\LandCommands.tga"; break;
		case "ImmediateReload":	return "battle_interface\list_icons.tga"; break;
		case "InstantBoarding":	return "battle_interface\list_icons.tga"; break;
		case "Turn180":			return "battle_interface\list_icons.tga"; break;
		case "LightRepair":		return "battle_interface\list_icons.tga"; break;
		case "InstantRepair":	return "battle_interface\list_icons.tga"; break;
	}
	trace("WARNING!!! Perk name - "+perkName+" hav`t texture");
	return "";
}

int GetTextureIndex(string texName)
{
	aref arTexList,arCurTex;
	makearef(arTexList,objActivePerkShower.Textures);
	int i,q;

	q = GetAttributesNum(arTexList);
	for(i=0; i<q; i++)
	{
		arCurTex = GetAttributeN(arTexList,i);
		if(arCurTex.file == texName) return i;
	}
	trace("WARNING!!! Texture name - "+texName+" hav`t describe");
	return -1;
}

void DelPerkFromActiveList(string perkID)
{
	aref arRoot,arCur;
	makearef(arRoot,objActivePerkShower.PerkList.list);

	// seaPerkShower -->
	bool isSeaLoaded = bSeaActive && !bAbordageStarted;
	if (isSeaLoaded && perkID != "TimeSpeed")
	{
	    if(!IsEntity(&objSeaPerkShower)) return;
		SeaPerkShower_RollbackPerk(perkId);
	    return;
	}
	// <--

	if( !CheckAttribute(arRoot,perkID) ) return;

	makearef(arCur,arRoot.(perkID));
	SendMessage(&objActivePerkShower,"lsa",MSG_ACTIVE_PERK_LIST_REFRESH,"del",arCur);
	DeleteAttribute(arCur,"");
	DeleteAttribute(arRoot,perkID);
}


int GetCooldownPerkIconColor()
{
    return ARGB(255, 255, 145, 128);
}

int GetActivePerkIconColor()
{
    return ARGB(255, 196, 255, 196);
}

int GetNotAvailablePerkIconColor()
{
    return ARGB(200, 109, 109, 109);
}

int GetNotAcquiredPerkIconColor()
{
    return ARGB(108, 245, 245, 245);
}

void InitSeaPerkShower()
{
	float fHtRatio = GetScreenScale();

	// Sea Perk shower - Тот самый "пирог"
//	objSeaPerkShower.SeaPerkShowerPos = "970,1014"; // 888 + 82
	objSeaPerkShower.SeaPerkShowerPos = (sti(showWindow.right)*0.5 + RecalculateHIcon(makeint(1 * fHtRatio))) + "," + RecalculateVIcon(sti(showWindow.bottom) + makeint(-86 * fHtRatio));

	objSeaPerkShower.Backtexturename = "battle_interface\BI_SeaPerkShowerBack.tga";
	objSeaPerkShower.BackUV = "0,0,1,1";
	objSeaPerkShower.BackOffset = RecalculateHIcon(makeint(0 * fHtRatio)) + "," + RecalculateVIcon(makeint(0 * fHtRatio));
	objSeaPerkShower.BackIconSize = RecalculateHIcon(makeint(170 * fHtRatio)) + "," + RecalculateVIcon(makeint(170 * fHtRatio));
	objSeaPerkShower.BackColor = ARGB(255, 255, 255, 255);

	objSeaPerkShower.Segmentstexturename = "battle_interface\BI_SeaPerkShowerSegments.tga";

	int defaultSegColor = ARGB(255, 255, 255, 255);
	objSeaPerkShower.UpSegmentColor = defaultSegColor;
//	objSeaPerkShower.UpSegmentColor = ARGB(255, 169, 169, 169);
	objSeaPerkShower.UpSegmentUV = "0,0,0.15625,0.15625";
	objSeaPerkShower.UpSegmentOffset = RecalculateHIcon(makeint(1 * fHtRatio)) + "," + RecalculateVIcon(makeint(-50 * fHtRatio));
	objSeaPerkShower.UpSegmentSize = RecalculateHIcon(makeint(77 * fHtRatio)) + "," + RecalculateVIcon(makeint(77 * fHtRatio));
	objSeaPerkShower.UpSegmentOn = false;

	objSeaPerkShower.LeftSegmentColor = defaultSegColor;
	objSeaPerkShower.LeftSegmentUV = "0.15625,0,0.3125,0.15625";
	objSeaPerkShower.LeftSegmentOffset = RecalculateHIcon(makeint(-41 * fHtRatio)) + "," + RecalculateVIcon(makeint(1 * fHtRatio));
	objSeaPerkShower.LeftSegmentSize = RecalculateHIcon(makeint(77 * fHtRatio)) + "," + RecalculateVIcon(makeint(77 * fHtRatio));
	objSeaPerkShower.LeftSegmentOn = false;

	objSeaPerkShower.RightSegmentColor = defaultSegColor;
	objSeaPerkShower.RightSegmentUV = "0.3125,0,0.46875,0.15625";
	objSeaPerkShower.RightSegmentOffset = RecalculateHIcon(makeint(42 * fHtRatio)) + "," + RecalculateVIcon(makeint(1 * fHtRatio));
	objSeaPerkShower.RightSegmentSize = RecalculateHIcon(makeint(77 * fHtRatio)) + "," + RecalculateVIcon(makeint(77 * fHtRatio));
	objSeaPerkShower.RightSegmentOn = false;

	objSeaPerkShower.DownSegmentColor = defaultSegColor;
	objSeaPerkShower.DownSegmentUV = "0.46875,0,0.625,0.15625";
	objSeaPerkShower.DownSegmentOffset = RecalculateHIcon(makeint(1 * fHtRatio)) + "," + RecalculateVIcon(makeint(48 * fHtRatio));
	objSeaPerkShower.DownSegmentSize = RecalculateHIcon(makeint(77 * fHtRatio)) + "," + RecalculateVIcon(makeint(77 * fHtRatio));
	objSeaPerkShower.DownSegmentOn = false;

	objSeaPerkShower.PerkIconList.TextureSize = "1024,1024";
	objSeaPerkShower.PerkIconList.TextureIconOffsetY = 320;
	objSeaPerkShower.PerkIconList.TextureIconSize = 160;
//	objSeaPerkShower.PerkIconList.Turn180.UV = "0.15625,0.3125,0.3125,0.46875";
//	objSeaPerkShower.PerkIconList.ImmediateReload.UV = "0,0.3125,0.15625,0.46875";
//	objSeaPerkShower.PerkIconList.InstantRepair.UV = "0,0.46875,0.15625,0.625";
//	objSeaPerkShower.PerkIconList.LightRepair.UV = "0,0.46875,0.15625,0.625";

	objSeaPerkShower.PerkIconList.List.ImmediateReload.idx = 0;
	objSeaPerkShower.PerkIconList.List.Turn180.idx = 1;
	objSeaPerkShower.PerkIconList.List.InstantRepair.idx = 6;
	objSeaPerkShower.PerkIconList.List.LightRepair.idx = 7;

	objSeaPerkShower.Icontextfontid = "interface_normal_smallscale";

	float defaultFontScale = 0.355 * fHtRatio;
	objSeaPerkShower.UpPerkIconOffset = RecalculateHIcon(makeint(2 * fHtRatio)) + "," + RecalculateVIcon(makeint(1 * fHtRatio));
	objSeaPerkShower.UpPerkIconSize = RecalculateHIcon(makeint(62 * fHtRatio)) + "," + RecalculateVIcon(makeint(62 * fHtRatio));
	objSeaPerkShower.UpIconTextcolor = defaultSegColor;
	objSeaPerkShower.UpicontextScale = defaultFontScale;

	objSeaPerkShower.LeftPerkIconOffset = RecalculateHIcon(makeint(2 * fHtRatio)) + "," + RecalculateVIcon(makeint(0 * fHtRatio));
	objSeaPerkShower.LeftPerkIconSize = RecalculateHIcon(makeint(62 * fHtRatio)) + "," + RecalculateVIcon(makeint(62 * fHtRatio));
	objSeaPerkShower.LeftIconTextcolor = defaultSegColor;
	objSeaPerkShower.LefticontextScale = defaultFontScale;

	objSeaPerkShower.RightPerkIconOffset = RecalculateHIcon(makeint(1 * fHtRatio)) + "," + RecalculateVIcon(makeint(0 * fHtRatio));
	objSeaPerkShower.RightPerkIconSize = RecalculateHIcon(makeint(56 * fHtRatio)) + "," + RecalculateVIcon(makeint(56 * fHtRatio));
	objSeaPerkShower.RightIconTextcolor = defaultSegColor;
	objSeaPerkShower.RighticontextScale = defaultFontScale;

	objSeaPerkShower.DownPerkIconOffset = RecalculateHIcon(makeint(0 * fHtRatio)) + "," + RecalculateVIcon(makeint(1 * fHtRatio));
	objSeaPerkShower.DownPerkIconSize = RecalculateHIcon(makeint(57 * fHtRatio)) + "," + RecalculateVIcon(makeint(57 * fHtRatio));
	objSeaPerkShower.DownIconTextcolor = defaultSegColor;
	objSeaPerkShower.DownicontextScale = defaultFontScale;

	objSeaPerkShower.UpIconTextOffset = RecalculateHIcon(makeint(-2 * fHtRatio)) + "," + RecalculateVIcon(makeint(-12 * fHtRatio));
	objSeaPerkShower.LeftIconTextOffset = RecalculateHIcon(makeint(-2 * fHtRatio)) + "," + RecalculateVIcon(makeint(-12 * fHtRatio));
	objSeaPerkShower.RightIconTextOffset = RecalculateHIcon(makeint(-2 * fHtRatio)) + "," + RecalculateVIcon(makeint(-12 * fHtRatio));
	objSeaPerkShower.DownIconTextOffset = RecalculateHIcon(makeint(-2 * fHtRatio)) + "," + RecalculateVIcon(makeint(-12 * fHtRatio));

	objSeaPerkShower.UpIconText = "";
	objSeaPerkShower.LeftIconText = "";
	objSeaPerkShower.RightIconText = "";
	objSeaPerkShower.DownIconText = "";

	objSeaPerkShower.UpPerkIconIdx = -1;
	objSeaPerkShower.LeftPerkIconIdx = -1;
	objSeaPerkShower.RightPerkIconIdx = -1;
	objSeaPerkShower.DownPerkIconIdx= -1;
}

void InitSeaPerkShower_SegmentsInfo()
{
    objSeaPerkShower.SegmentsInfo.Up = "Turn180";
    objSeaPerkShower.SegmentsInfo.Left = "ImmediateReload";
    objSeaPerkShower.SegmentsInfo.Right = "InstantRepair";
    objSeaPerkShower.SegmentsInfo.Down = "LightRepair";
}

void LoadSeaPerkShower()
{
	UnloadSeaPerkShower();

	//AlexBlade - отображение перков в море -->
	InitSeaPerkShower();
	InitSeaPerkShower_SegmentsInfo();
	//отображение перков в море <--

	CreateEntity(&objSeaPerkShower,"SeaPerkShower");
	LayerAddObject(SEA_EXECUTE,&objSeaPerkShower,-1);
	LayerAddObject(SEA_REALIZE,&objSeaPerkShower,-1);
}

void UnloadSeaPerkShower()
{
	if (IsEntity(&objSeaPerkShower)) DeleteClass(&objSeaPerkShower);
	DeleteAttribute(&objSeaPerkShower,"");
}

void InitSeaPerkShower_AddPerks()
{
	if (!CheckAttribute(&objSeaPerkShower, "SegmentsInfo"))
		return;

    aref arRoot,arSegment;
	makearef(arRoot,objSeaPerkShower.SegmentsInfo);

	int segmentsQ = GetAttributesNum(arRoot);

	for (int j = 0; j < segmentsQ; j++)
	{
		arSegment = GetAttributeN(arRoot, j);
		string perkName = GetAttributeValue(arSegment);
		SeaPerkShower_AddPerk(perkName);
	}
}

void SeaPerkShower_AddPerk(string perkId)
{
	if (!CheckAttribute(&objSeaPerkShower, "SegmentsInfo"))
		return;

	aref arRoot,arSegment;
	makearef(arRoot,objSeaPerkShower.SegmentsInfo);

	int segmentsQ = GetAttributesNum(arRoot);

	for (int j = 0; j < segmentsQ; j++)
	{
		arSegment = GetAttributeN(arRoot, j);
		string perkName = GetAttributeValue(arSegment);

		if (perkName != perkId) continue;

		if (CheckAttribute(&objSeaPerkShower, "PerkIconList.List." + perkName + ".idx"))
		{
			string positionName = GetAttributeName(arSegment);
			string segAttrName = positionName + "PerkIconIdx";
			objSeaPerkShower.(segAttrName) = sti(objSeaPerkShower.PerkIconList.List.(perkName).idx);
			segAttrName = positionName + "IconText";
			objSeaPerkShower.(segAttrName) = "";
			segAttrName = positionName + "SegmentOn";
			objSeaPerkShower.(segAttrName) = true;
			segAttrName = positionName + "SegmentColor";

			if (!IsSeaPerkAcquired(perkName))
			{
				objSeaPerkShower.(segAttrName) = GetNotAcquiredPerkIconColor();
				arSegment.status = "notAcquired";
			}
			else
			{
				int color = ARGB(255, 255, 255, 255);
				if (!IsSeaPerkReadyForActivation(PerkId))
				{
					color = GetNotAvailablePerkIconColor();
				}
				objSeaPerkShower.(segAttrName) = color;
			}
		}
		else
		{
			Trace("WARNING!!! SeaPerkShower_AddPerk: Perk name - "+perkName+" not found in PerkIconList");
		}
	}
}

void SeaPerkShower_AddPerkWithCooldown(string perkId, int cooldownInSeconds, bool bActive)
{
	if (!CheckAttribute(&objSeaPerkShower, "SegmentsInfo"))
		return;

	aref arRoot,arSegment;
	makearef(arRoot,objSeaPerkShower.SegmentsInfo);
	float fHtRatio = GetScreenScale();

	int segmentsQ = GetAttributesNum(arRoot);

	for (int j = 0; j < segmentsQ; j++)
	{
		arSegment = GetAttributeN(arRoot, j);
		string perkName = GetAttributeValue(arSegment);

		if (perkName != perkId) continue;

		if (CheckAttribute(&objSeaPerkShower, "PerkIconList.List." + perkName + ".idx"))
		{
			string positionName = GetAttributeName(arSegment);
			string segAttrName = positionName + "PerkIconIdx";
			objSeaPerkShower.(segAttrName) = sti(objSeaPerkShower.PerkIconList.List.(perkName).idx);
			segAttrName = positionName + "IconText";
			objSeaPerkShower.(segAttrName) = its(cooldownInSeconds);
			segAttrName = positionName + "SegmentColor";
			if (bActive)
			{
				objSeaPerkShower.(segAttrName) = GetActivePerkIconColor();
			}
			else
			{
				objSeaPerkShower.(segAttrName) = GetCooldownPerkIconColor();
			}
			segAttrName = positionName + "IconTextScale";
			if (bActive)
			{
				objSeaPerkShower.(segAttrName) = 0.35 * fHtRatio;
			}
			else
			{
				objSeaPerkShower.(segAttrName) = 0.32 * fHtRatio;
			}
			segAttrName = positionName + "SegmentOn";
			objSeaPerkShower.(segAttrName) = true;

			arRoot.(positionName).status = "active";
		}
		else
		{
			Trace("WARNING!!! SeaPerkShower_AddPerk: Perk name - "+perkName+" not found in PerkIconList");
		}
	}
}

void SeaPerkShower_RollbackPerk(string perkId)
{
	if (!CheckAttribute(&objSeaPerkShower, "SegmentsInfo"))
		return;

	aref arRoot,arSegment;
	makearef(arRoot,objSeaPerkShower.SegmentsInfo);

	int segmentsQ = GetAttributesNum(arRoot);

	for (int j = 0; j < segmentsQ; j++)
	{
		arSegment = GetAttributeN(arRoot, j);
		string perkName = GetAttributeValue(arSegment);

		if (perkName != perkId) continue;

		if (CheckAttribute(&objSeaPerkShower, "PerkIconList.List." + perkName + ".idx"))
		{
			string positionName = GetAttributeName(arSegment);
			string segAttrName = positionName + "IconText";
			objSeaPerkShower.(segAttrName) = "";
			segAttrName = positionName + "SegmentColor";
			int color = ARGB(255, 255, 255, 255);
			if (!IsSeaPerkReadyForActivation(PerkId))
			{
				color = GetNotAvailablePerkIconColor();
			}
			objSeaPerkShower.(segAttrName) = color;
			DeleteAttribute(arRoot, positionName + ".status");
		}
		else
		{
			Trace("WARNING!!! SeaPerkShower_AddPerk: Perk name - "+perkName+" not found in PerkIconList");
		}
	}
}

void SeaPerkShower_RefreshPerkForUsing()
{
	if (!CheckAttribute(&objSeaPerkShower, "SegmentsInfo"))
	return;

	aref arRoot,arSegment;
	makearef(arRoot,objSeaPerkShower.SegmentsInfo);

	int segmentsQ = GetAttributesNum(arRoot);

	for (int j = 0; j < segmentsQ; j++)
	{
		arSegment = GetAttributeN(arRoot, j);
		string perkName = GetAttributeValue(arSegment);
		string positionName = GetAttributeName(arSegment);

		if (!CheckAttribute(arRoot, positionName + ".status"))
		{
			string segAttrName = positionName + "SegmentOn";
			if (!sti(objSeaPerkShower.(segAttrName)))
			{
			    continue;
			}
			segAttrName = positionName + "IconText";
			objSeaPerkShower.(segAttrName) = "";
			segAttrName = positionName + "SegmentColor";
			int color = ARGB(255, 255, 255, 255);
			if (!IsSeaPerkReadyForActivation(perkName))
			{
				color = GetNotAvailablePerkIconColor();
			}
			objSeaPerkShower.(segAttrName) = color;
		}
	}
}
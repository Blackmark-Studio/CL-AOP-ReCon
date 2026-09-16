
//HardCoffee work in progress -->

#define ENCGIRL_RAPERS_QTY 3
#define ESCORT_FAILREP -10

bool g_bEncGirl_Sld = false; //Эта переменная для того, чтобы стражники не чекали атрибут каждый кадр

void EncGirl_CloseQuestExit_func(string qName)
{
	ref rChr, rGirl;
	aref arPass;
	int i, iIdx;
	string sTemp;

	g_bEncGirl_Sld = false;
	if (!CheckAttribute(pchar, "GenQuest.EncGirl"))
	{
		trace("ERROR: EncGirl_CloseQuestExit_func has lost GenQuest attribute");
		Log_Info("ERROR: EncGirl_CloseQuestExit_func has lost GenQuest attribute");
		goto link_EncGirlLostAttr;
	}

	if ("Quest_InTavern_ToRoom_Should" == pchar.GenQuest.EncGirl)
		LocatorReloadEnterDisable(pchar.GenQuest.EncGirl.city +"_tavern", "reload2_back", true);

	int iNation = sti(pchar.GenQuest.EncGirl.nation);
	iIdx = GetCharacterIndex("CangGirl");
	if (iIdx > -1)
	{
		rGirl = &characters[iIdx];
		DeleteAttribute(rGirl, "QuestFollower");
		DeleteAttribute(rGirl, "ActorGoToLocationNoCheck");
		rGirl.lifeDay = "0";
		rGirl.chr_ai.disableDlg = "0";
		LAi_RemoveCheckMinHP(rGirl);
		ChangeCharacterAddressGroupEx(rGirl, "None", "goto", "", true);
		MakeUnpushable(rGirl, false);
		SetBonusPush(rGirl, false);
	}
	else
	{
		pchar.GenQuest.EncGirl.CloseQuest = "Close_SheISDead";
	}

	if (CheckAttribute(pchar, "GenQuest.EncGirl.Soldiers.SldID"))
	{
		iIdx = GetCharacterIndex(pchar.GenQuest.EncGirl.Soldiers.SldID);
		if (iIdx > -1)
		{
			rChr = &characters[iIdx];
			rChr.chr_ai.disableDlg = "0";
			LAi_SetGuardianTypeNoGroup(rChr);
			LAi_RemoveCheckMinHP(rChr);
			LAi_RemoveCheckAlarm(rChr);

			MakeUnpushable(rChr, false);
			SetBonusPush(rChr, false);

			rChr.location = pchar.GenQuest.EncGirl.Soldiers.SldPrevLocation;
			rChr.location.group = pchar.GenQuest.EncGirl.Soldiers.SldPrevGroup;
			rChr.location.locator = pchar.GenQuest.EncGirl.Soldiers.SldPrevLocator;

		}
	}

	trace("CloseQuestExit EncGirl: " +pchar.GenQuest.EncGirl);//coffee
	Log_info("CloseQuestExit EncGirl: " +pchar.GenQuest.EncGirl);
	trace("CloseQuestExit CloseQuest: " +pchar.GenQuest.EncGirl.CloseQuest);
	Log_info("CloseQuestExit CloseQuest: " +pchar.GenQuest.EncGirl.CloseQuest);

	switch (pchar.GenQuest.EncGirl.CloseQuest)
	{
		case "Close_close": //Всё порешалось во время диалога
		break;
		case "Close_Rapers_ToParentsHer": //Согласились проводить к родителям, но при этом кудато свалили
		break;
		case "Close_Rapers_LeaveHer": //оставили развлекаться с насильниками
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -8);
			AddSimpleRumour(RandPhraseSimple(StringFromKey("Common_rumours_100", GetFullName(pchar), pchar.GenQuest.EncGirl.name),
					StringFromKey("Common_rumours_101", pchar.GenQuest.EncGirl.name)), iNation, 5, 1);
		break;
		case "Close_Rapers_BoughtOutWhore": //отдали бабло за неё и свалили
			EncGirl_CheckForCorrectRumors(rGirl, iNation);

			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "36");
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sRapersResult", " " +StringFromKey("EncGirl_Girl_289") +" " +FindMoneyString(sti(pchar.GenQuest.EncGirl.price)) +".");
			AddQuestUserData("JungleGirl", "WhatDoesSheDoResult", StringFromKey("EncGirl_Girl_290"));
			CloseQuestHeader("JungleGirl");
		break;
		case "Close_Rapers_AreTheyDead": //Убили бандитов, а может и не убили, но в любом случае не поговорили с ней
			EncGirl_CheckForCorrectRumors(rGirl, iNation);

			ReOpenQuestHeader("JungleGirl");
			AddQuestRecord("JungleGirl", "36");
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));

			for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
			{
				iIdx = GetCharacterIndex("EncGirl_GangMan_" + i);
				if (iIdx > 0 && !LAi_IsDead(&characters[iIdx])) break;
			}

			if (i >= ENCGIRL_RAPERS_QTY)
				AddQuestUserData("JungleGirl", "sRapersResult", " " +StringFromKey("EncGirl_Girl_291"));
			else
				AddQuestUserData("JungleGirl", "sRapersResult", " ");

			if (pchar.GenQuest.EncGirl == "Quest_Rapers_CanFleeFromThem")
				AddQuestUserData("JungleGirl", "WhatDoesSheDoResult", StringFromKey("EncGirl_Girl_294"));
			else
				AddQuestUserData("JungleGirl", "WhatDoesSheDoResult", StringFromKey("EncGirl_Girl_290"));

			CloseQuestHeader("JungleGirl");
		break;
		case "Close_SheIsInSafe":
			EncGirl_SheIsInSafe();
		break;
		case "Close_SheISDead":
			if ("Quest_Soldiers_SheIsUnderArrest" == pchar.GenQuest.EncGirl) break;
			if ("Quest_Escort_GoodEnd" == pchar.GenQuest.EncGirl) break;
			if (CheckAttribute(pchar, "GenQuest.EncGirl.WasKIlledBy") && pchar.GenQuest.EncGirl.WasKIlledBy == pchar.id)
			{
				OfficersReaction("bad");
				ChangeCharacterReputation(pchar, -10);
			}

			AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_94", pchar.GenQuest.EncGirl.name),
				StringFromKey("Common_rumours_95", GetFullName(pchar), pchar.GenQuest.EncGirl.name),
				StringFromKey("Common_rumours_96", pchar.GenQuest.EncGirl.name)), iNation, 5, 1);

			if (pchar.GenQuest.EncGirl == "Quest_toParents" || pchar.GenQuest.EncGirl == "Quest_FindLover") //Coffee TODO:
			{
				ChangeCharacterReputation(pchar, ESCORT_FAILREP);
				AddQuestRecord("JungleGirl", "10");
				AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
				CloseQuestHeader("JungleGirl");
			}
			else if ("Quest_Escort_EnterToSea" == pchar.GenQuest.EncGirl)
			{
				//запись в журнал была ранее в EncGirl_Escort_EnterToSea
				ChangeCharacterReputation(pchar, ESCORT_FAILREP);
			}
			else if (HasSubStr(pchar.GenQuest.EncGirl, "_Escort_"))
			{
				ChangeCharacterReputation(pchar, ESCORT_FAILREP);
				AddQuestRecord("JungleGirl", "38");
				AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
				CloseQuestHeader("JungleGirl");
			}
		break;
		case "Close_FightBegun": //начали драку, девка убежала
			sTemp = GetNationNameByType(sti(pchar.GenQuest.EncGirl.nation));
			sTemp = XI_ConvertString("people" + sTemp +"Ins");
			AddQuestRecord("JungleGirl", "29");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ся", "ась"));
			AddQuestUserData("JungleGirl", "sNation", sTemp);
			CloseQuestHeader("JungleGirl");
		break;
		case "Close_PunchHer":
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -5);

			if ("Quest_Journey_LetsGo" == pchar.GenQuest.EncGirl)
			{
				AddQuestRecord("JungleGirl", "31");
				AddQuestUserData("JungleGirl", "sPirate", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_GEN));
			}
			else
			{
				AddQuestRecord("JungleGirl", "30");
				AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			}
			CloseQuestHeader("JungleGirl");
		break;
		case "Close_Escort_ToTown_Done":
			/*if (pchar.GenQuest.EncGirl == "Quest_InTavern_ToRoom_Should" && pchar.quest.EncGirl_inRoom.win_condition.l1.location == pchar.location)
			{
				DeleteAttribute(pchar, "quest.LandEnc_EncGirl_CloseQuestExit");  //Coffee разобраться с этой хренью
				return;
			}*/
			EncGirl_Escort_CloseLogbook_Good();
			EncGirl_SheIsInSafe();
		break;

		case "Close_InTavern_GoodFuck":
			chrDisableReloadToLocation = false;
			EncGirl_Escort_CloseLogbook_Good();
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Fencing", -20);
			AddCharacterExpToSkill(pchar, "Pistol", -20);
			AddCharacterHealth(pchar, 5);
			ChangeCharacterReputation(pchar, -1);
			//чем больше удачи, тем меньше шанс потерять деньги
			if (drand(sti(GetCharacterSPECIAL(pchar, SPECIAL_L))) != 0)
				pchar.money = sti(pchar.money) - makeint(sti(pchar.money) / 15);
			else
				AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "Close_Pearls_TimeIsUp": //время на доставку жемчуга вышло
			AddSimpleRumour(StringFromKey("Common_rumours_137", pchar.GenQuest.EncGirl.name), iNation, 5, 1);
			ChangeCharacterReputation(pchar, -10);
			AddQuestRecord("JungleGirl", "3");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			CloseQuestHeader("JungleGirl");
		break;
		case "Close_InJungle_AbandonHer":
			OfficersReaction("bad");
			ChangeCharacterReputation(pchar, -5);
			AddSimpleRumour(StringFromKey("Common_rumours_96", pchar.GenQuest.EncGirl.name), iNation, 5, 1);
		break;
		case "Close_Soldiers_ToPrisonHer":
			ChangeCharacterNationReputation(pchar, iNation, 3);
			AddSimpleRumour(StringFromKey("Common_rumours_176", pchar.GenQuest.EncGirl.name), iNation, 5, 1);
		break;
		case "Close_Soldiers_AttackThem":
			ChangeCharacterReputation(pchar, -2);

			AddQuestRecord("JungleGirl", "41");
			CloseQuestHeader("JungleGirl");
		break;
		case "Close_InTavern_MeetBurglar":
			AddQuestRecord("JungleGirl", "42");
			AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
			AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
			CloseQuestHeader("JungleGirl");
		break;
	}

	link_EncGirlLostAttr:

	EncGirl_RemoveQuestMarks();

	for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
	{
		iIdx = GetCharacterIndex("EncGirl_GangMan_" + i);
		if (iIdx < 0) continue;
		rChr = &characters[iIdx];
		ChangeCharacterAddressGroupEx(rChr, "None", "goto", "", true);
		LAi_RemoveCheckMinHP(rChr);
		rChr.lifeDay = "0";
		rChr.chr_ai.disableDlg = "0";
	}

	DeleteAttribute(pchar, "GenQuest.EncGirl");
	//Снимаем все прерывания
	makearef(arPass, pchar.quest);
	iIdx = GetAttributesNum(arPass);
	for (i = 0; i < iIdx; i++)
	{
		sTemp = GetAttributeName(GetAttributeN(arPass, i));
		if (HasSubStr(sTemp, "EncGirl"))
			pchar.quest.(sTemp).over = "yes";
	}
}

bool EncGirl_GenerateQuest(ref location, int iNation, string sCity, string sAreal)
{
	//if (rand(12) > 6) return false; //Coffee test
	 // На необитаемых  островах, маяках и бухтах нельзя
	if (location.type == "seashore" || location.type == "mayak") return false;
	if (CheckAttribute(pchar, "GenQuest.EncGirl")) return false;

	string encGroup = LAi_FindRandomLocator("encdetector");
	string str = "locators." + encGroup;
	aref grp, arDis;
	makearef(grp, location.(str));
	int num = GetAttributesNum(grp); //кол-во локаторов
	if (num < 2) return false;

	int i, iRank, iChar, iRand;
	ref chr;
	string locator;

	if (!CheckAttribute(location, "locators.reload.reloadW_back")) //обычная девка в джунглях
	{
		// Генерим ранг
		iRank = sti(pchar.rank);
		if (iRank > 20) iRank = iRank + sti(MOD_SKILL_ENEMY_RATE * 2.5 / num);
		else if (iRank > 6) iRank = iRank + sti(MOD_SKILL_ENEMY_RATE * 1.6 / num);
		else iRank = sti(pchar.rank);

		LAi_group_Delete("EnemyFight");
		LAi_group_Delete("LandEncGroup");
		//LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true); //Coffee
		//LAi_SetFightMode(pchar, false);
		//LAi_LockFightMode(pchar, true);
		chrDisableReloadToLocation = true;

		//Начинаем перебирать локаторы и логинить фантомов
		i = 0;
		arrayNPCModelHow = 0;
		while (i < num)
		{
			//Получим локатор для логина
			locator = GetAttributeName(GetAttributeN(grp, i));
			if (i == 0)
			{
				iChar = GetCharacterIndex("CangGirl");
				if (iChar > -1)
				{
					InitCharacter(&characters[iChar], iChar);
					iChar = -1;
				}

				if (sti(pchar.rank) > 9) iRand = 2;
				else iRand = 0;

				switch (1)//switch (rand(iRand))
				{
					case 0: //блудница
						iChar =	NPC_GenerateCharacter("CangGirl", "girl_"+(rand(9)+1), "woman", "towngirl", 5, iNation, -1, false);
						chr = &characters[iChar];
						chr.dialog.filename = "Encounters\EncGirl_Girl.c";
						chr.dialog.currentnode = "DlgGirl_Begin_CommonGirl";
						pchar.GenQuest.EncGirl = "Quest_Begin_CommonGirl"; //влияет на диалог с бандитами
					break;
					case 1: //шлюха
						iChar =	NPC_GenerateCharacter("CangGirl", "horse0"+(rand(7)+1), "woman", "towngirl", 5, iNation, -1, false);
						chr = &characters[iChar];
						chr.dialog.filename = "Encounters\EncGirl_Girl.c";
						chr.dialog.currentnode = "DlgGirl_Begin_WhoreGirl";
						pchar.GenQuest.EncGirl = "Quest_Begin_WhoreGirl";
						if (false && sti(pchar.rank) > 15 && GetCharacterIndex(sCity + "_Hostess") > -1) //Coffee Rand(2) == 2
							pchar.GenQuest.EncGirl.EscapedFromBrothel = "1"; // душещипательная история о невинной девочке попавшей в бордель
					break;
					case 2: //Сбежавшая невеста
						iChar =	NPC_GenerateCharacter("CangGirl", "girl_"+(rand(9)+1), "woman", "towngirl", 5, iNation, -1, false);
						chr = &characters[iChar];
						chr.dialog.filename = "Encounters\EncGirl_Girl.c";
						chr.dialog.currentnode = "Begin_3";
						pchar.GenQuest.EncGirl = "Quest_Begin_3";
					break;
				}
				chr.name = GenerateRandomName_Generator(iNation, "woman");
				chr.lastname = "";
				chr.greeting = "Enc_RapersGirl_1";
				ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
				LAi_SetActorTypeNoGroup(chr);


				LAi_group_MoveCharacter(chr, "LandEncGroup");

				LAi_ActorDialog(chr, pchar, "", -1, 0);
				LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr) - 1, false, "LandEnc_EncGirl_FightBeforeDialog");
				str = location.index;
				pchar.GenQuest.EncGirl.city = sCity; //  город девицы
				pchar.GenQuest.EncGirl.nation = iNation; //нация для слухов
				pchar.GenQuest.EncGirl.name = GetFullName(chr); //имя девицы
				pchar.GenQuest.EncGirl.LocIdx = location.index;
				chr.city = sCity;
				chr.chr_ai.disableDlg = "0";

				//EncGirl_SetCheckForDeath();
/*				pchar.quest.EncGirl_CheckForDeath.win_condition.l1 = "NPC_Death";
				pchar.quest.EncGirl_CheckForDeath.win_condition.l1.character = "CangGirl";
				pchar.quest.EncGirl_CheckForDeath.function = "EncGirl_SheISDead";*/
				EncGirl_CloseQuestExit("Close_Rapers_LeaveHer"); //если свалить с локации и не заговорить

				g_bEncGirl_Sld = false;
				i++;
				continue;
			}
			chr = GetCharacter(NPC_GenerateCharacter("EncGirl_GangMan_" + i, "pirate_"+(rand(15)+1), "man", "man", iRank, PIRATE, 100, true));
			DeleteAttribute(chr, "chr_ai");

			SetNPCModelUniq(chr, "pirate", MAN);
			SetFantomParamFromRank(chr, iRank, true);
			chr.dialog.filename = "Encounters\EncGirl_Rapers.c";
			chr.dialog.currentnode = "DlgRapers_BeginQuest";
			chr.greeting = "Enc_Raiders";
			ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
			LAi_SetActorTypeNoGroup(chr);
			LAi_group_MoveCharacter(chr, "EnemyFight");
			LAi_ActorFollow(chr, &characters[iChar], "", -1);
			LAi_SetCheckMinHP(chr, LAi_GetCharacterHP(chr) - 1, false, "LandEnc_EncGirl_FightBeforeDialog");
			chr.chr_ai.disableDlg = "0";

			// evganat - энциклопедия
			if (i == 1 && CheckRandomPage("questjungle", "rapers", -1))
			{
				chr.encyclopedia.tome = GetRandomTome();
				chr.encyclopedia.page = 5;
			}
			if (i == ENCGIRL_RAPERS_QTY) break;
			i++;
		}

		pchar.GenQuest.EncGirl.item = GenQuest_GenerateArtefact();
		pchar.GenQuest.EncGirl.FatherReward  = its(500 * (sti(pchar.rank) + 10) + rand(5000)); //Награда, если привести к бате
		return true;
	}
	else
	{	// Замануха в колодец
		LAi_group_Delete("LandEncGroup");
		makearef(grp, Locations[sti(location.index)].reload);
		num = GetAttributesNum(grp);
		str = "none";
		for (i = 0; i < num; i++)
		{
			arDis = GetAttributeN(grp, i);
			if (arDis.name == "reloadW_back")
			{
				str = arDis.go; //ID смежной локации, куда ведёт колодец
			}
		}
		if (str == "none") return false; //на всякий случай
		//--> снимаем возможный конфликт с бергларами
		if (sAreal == "SentMartin" || sAreal == "SantaCatalina")
		{
			iChar = GetCharacterIndex("BerglarSantaCatalina");
			if (iChar != -1 && characters[iChar].location == str) return false;
			iChar = GetCharacterIndex("BerglarMarigo");
			if (iChar != -1 && characters[iChar].location == str) return false;
		}
		//<-- снимаем возможный конфликт с бергларами
		locator = GetAttributeName(GetAttributeN(grp, 1));
		chr =	GetCharacter(NPC_GenerateCharacter("FriendGirl", "girl_"+(rand(9)+1), "woman", "towngirl", 5, iNation, 0, false));
		chr.dialog.filename = "Encounters\Colodec.c";
		chr.dialog.currentnode = "First time";
		chr.greeting = "Enc_RapersGirl_1";
		ChangeCharacterAddressGroup(chr, location.id, encGroup, locator);
		LAi_SetActorTypeNoGroup(chr);
		LAi_group_MoveCharacter(chr, "LandEncGroup");
		LAi_ActorDialog(chr, pchar, "", -1, 0);
		pchar.GenQuest.EncGirl.locationId = str; //ID локации
		pchar.GenQuest.EncGirl.nation = iNation; //нация для слухов
		pchar.GenQuest.EncGirl.name = GetFullName(chr); //имя девки
		pchar.quest.Enc_FriendGirl_after.win_condition.l1 = "NPC_Death";
		pchar.quest.Enc_FriendGirl_after.win_condition.l1.character = "FriendGirl";
		pchar.quest.Enc_FriendGirl_after.win_condition = "Enc_FriendGirl_after";
	}
	return true;
}

//Coffee TODO: чзнх
/*void EncGirl_SheISDead(string qName) //Закрытие квеста, если преждевременно завалили тётку
{
	pchar.quest.EncGirl_CheckForDeath.over = "yes";
	chrDisableReloadToLocation = false;
	EncGirl_CloseQuestExit("Close_SheISDead");
}*/

void EncGirl_Rapers_FightBeforeDialog() //quests_reaction.c LandEnc_EncGirl_FightBeforeDialog
{
	if (CheckAttribute(pchar, "quest.LandEnc_EncGirl_FightBeforeDialog.over")
		&& pchar.quest.LandEnc_EncGirl_FightBeforeDialog.over == "yes") return;

	pchar.quest.LandEnc_EncGirl_FightBeforeDialog.over = "yes";

	ref rChr;
	int i, iIdx;

	for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
	{
		iIdx = GetCharacterIndex("EncGirl_GangMan_" + i);
		if (iIdx < 0) continue;
		rChr = &Characters[iIdx];
		LAi_RemoveCheckMinHP(rChr);
		LAi_SetWarriorType(rChr);
		LAi_group_MoveCharacter(rChr, "EnemyFight");
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
	LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	LAi_group_SetCheck("EnemyFight", "LandEnc_EncGirl_RapersKilled");

	iIdx = GetCharacterIndex("CangGirl");
	if (iIdx > -1)
	{
	    rChr = &Characters[iIdx];
	    LAi_RemoveCheckMinHP(rChr);
	    if (!LAi_IsDead(rChr))
		{
			LAi_SetActorTypeNoGroup(rChr);
			EncGigl_SheFleeAway(true, false);
		}

		//На случай, если сагрили и убежали
		pchar.GenQuest.EncGirl = "Quest_Rapers_CanFleeFromThem";
		if (HasSubStr(loadedlocation.id, "Town")) //Coffee TODO: чекать непосредственно локу, а не эту хрень
			EncGirl_CloseQuestExit("Close_Rapers_AreTheyDead"); //Возле города есть шанс, что она выживет
		else
			EncGirl_CloseQuestExit("Close_Rapers_LeaveHer"); //но в любом случае их надо убить, иначе её и в городе найдут и продолжат
		//LAi_ActorAfraid(rChr, pchar, true);
	}
	else
	{
		EncGirl_CloseQuestExit("Close_SheISDead");
	}
}

void EncGirl_Rapers_TheyAreDead() //quests_reaction.c LandEnc_EncGirl_RapersKilled
{
	chrDisableReloadToLocation = false;
	trace("EncGirl_Rapers_TheyAreDead"); //Coffee
	Log_info("EncGirl_Rapers_TheyAreDead");

	if (CheckAttribute(pchar, "quest.LandEnc_EncGirl_RapersKilled.over")
		&& pchar.quest.LandEnc_EncGirl_RapersKilled.over == "yes") return;

	pchar.quest.LandEnc_EncGirl_RapersKilled.over = "yes";

	int i, iTemp;
	ref rChr;

	for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
	{
		iTemp = GetCharacterIndex("EncGirl_GangMan_" + i);
		if (iTemp < 0) continue;
		rChr = &characters[iTemp];
		LAi_RemoveCheckMinHP(rChr);
		LAi_group_Delete(rChr.chr_ai.group); //Убрать сигнализацию
	}
	LAi_group_SetRelation(LAI_GROUP_PLAYER, "LandEncGroup", LAI_GROUP_NEITRAL); // На случай ббпе

	if (!CheckAttribute(pchar, "GenQuest.EncGirl"))
		return;

	rChr = GetCharacterFromID("CangGirl");
	if (rChr.id == NullCharacter.id)
	{
		EncGirl_CloseQuestExit("Close_SheISDead");
		return;
	}

	EncGirl_CloseQuestExit("Close_Rapers_AreTheyDead"); //На случай если гг убежит с локации

	if ("Quest_Rapers_CanFleeFromThem" == pchar.GenQuest.EncGirl)
		return;

	rChr.greeting = "Enc_RapersGirl_2";
	rChr.dialog.currentnode = "DlgGirl_Rapers_YouKilledRapers";
	LAi_SetActorTypeNoGroup(rChr);
	LAi_ActorDialog(rChr, pchar, "", -1, 0);
}

 //Coffee TODO: проверить использования
void EncGirl_PunchHer() //quests_reaction.c LandEnc_EncGirl_PunchHer
{
	ref rChr, rColony;
	string sGroup;
	int iColony;

	rChr = GetCharacterFromID("CangGirl");
	if (rChr.id == Nullcharacter.id)
	{
	    EncGirl_CloseQuestExit("Close_SheISDead");
		return;
	}

	if (!HasSubStr(loadedlocation.id, "Town"))
					AddSimpleRumour(StringFromKey("Common_rumours_96", pchar.GenQuest.EncGirl.name), sti(pchar.GenQuest.EncGirl.nation), 5, 1);

	EncGirl_CloseQuestExit("Close_PunchHer");

	EncGigl_SheFleeAway(true, false);
	LAi_SetDefaultDead(rChr);
	LAi_group_MoveCharacter(rChr, "LandEncGroup");

	//просит помощи у жителей города
	if (!CheckAttribute(loadedlocation, "type")) return;
	if (loadedlocation.type != "town") return;

	iColony = FindColony(loadedLocation.fastreload);
	if (iColony < 0) return;
	rColony = &Colonies[iColony];
	if (rColony.HeroOwn == "1") return;

	sGroup = GetNationNameByType(sti(rColony.nation))  + "_citizens"; //нация колонии
	LAi_group_AttackGroup(sGroup, LAI_GROUP_PLAYER);

	LAi_group_MoveCharacter(rChr, sGroup);
	SendMessage(rChr, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, StringFromKey("EncGirl_Girl_300"), 255.0, 255.0, 0.0);
}

void EncGirl_Rapers_BoughtOutWhore()
{
	ref sld = GetCharacterFromID("CangGirl");
	sld.greeting = "Enc_RapersGirl_2";
	sld.dialog.filename = "Encounters\EncGirl_Girl.c";
	sld.dialog.currentnode = "DlgGirl_Rapers_BoughtOutWhore";

	//LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, false, "LandEnc_EncGirl_PunchHer");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void EncGirl_Rapers_ToParentsHer()
{
	ref sld = GetCharacterFromID("CangGirl");
	sld.greeting = "Enc_RapersGirl_2";
	sld.dialog.filename = "Encounters\EncGirl_Girl.c";
	sld.dialog.currentnode = "Rapers_ToParentsHer";

	//LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, false, "LandEnc_EncGirl_PunchHer");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}
/*void EncGirl_SetCheckForDeath() //Coffee чзнх
{
	pchar.quest.EncGirl_CheckForDeath.win_condition.l1 = "NPC_Death";
	pchar.quest.EncGirl_CheckForDeath.win_condition.l1.character = "CangGirl";
	pchar.quest.EncGirl_CheckForDeath.function = "EncGirl_SheISDead";
}*/
void EncGirl_CheckForCorrectRumors(ref rGirl, int iNation) //На случай если гг оставил её в джунглях или решил потыкать ножом
{
	if (rGirl.id == Nullcharacter.id)
	{
		AddSimpleRumour(StringFromKey("Common_rumours_96", pchar.GenQuest.EncGirl.name), iNation, 5, 1);
	}
	else if ("Quest_InJungle_SheGaveYouMoney" == pchar.GenQuest.EncGirl)
	{
		if (stf(rGirl.chr_ai.hp) >= stf(rGirl.chr_ai.hp_max))
			EncGirl_SheIsInSafe();
	}
	else if (drand(2) == 0 || stf(rGirl.chr_ai.hp) < stf(rGirl.chr_ai.hp_max)) //Quest_Rapers_CanFleeFromThem
		AddSimpleRumour(StringFromKey("Common_rumours_96", pchar.GenQuest.EncGirl.name), iNation, 5, 1);
	else
		AddSimpleRumour(StringFromKey("Common_rumours_97", pchar.GenQuest.EncGirl.name), iNation, 5, 1);
}

void EncGirl_SheIsInSafe() //Она обещала всем рассказать
{
	OfficersReaction("good");
	ChangeCharacterReputation(pchar, 5);
	AddSimpleRumour(LinkRandPhrase(StringFromKey("Common_rumours_97", pchar.GenQuest.EncGirl.name),
			StringFromKey("Common_rumours_98", GetFullName(pchar), pchar.GenQuest.EncGirl.name),
			StringFromKey("Common_rumours_99", pchar.GenQuest.EncGirl.name, GetMainCharacterNameGen())), sti(pchar.GenQuest.EncGirl.nation), 3, 1);
}

// ESCORT functions -->
void EncGirl_GirlFollow()
{
	ref rChr = GetCharacterFromId("CangGirl");
	rChr.QuestFollower = "1"; //Rosarak
	DeleteAttribute(rChr, "LifeDay");
/*	GiveItem2Character(sld, "unarmed");
	EquipCharacterbyItem(sld, "unarmed");*/
	LAi_SetActorTypeNoGroup(rChr);
	LAi_group_MoveCharacter(rChr, LAI_GROUP_PLAYER);
	//LAi_group_Register("DeliveQuest_Girl");
	//LAi_group_SetRelation("DeliveQuest_Girl", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
	//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Girl", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
	//LAi_group_MoveCharacter(rChr, "DeliveQuest_Girl");
	LAi_ActorFollowEverywhere(rChr, "", -1);
	AddLandQuestMark_Gen(rChr, "JungleGirl");

	SetBonusPush(rChr, true);
/*	if(pchar.GenQuest.EncGirl != "Journey_LetsGo")
	{
		pchar.quest.EncGirl_DeathSimple.win_condition.l1 = "NPC_Death";
		pchar.quest.EncGirl_DeathSimple.win_condition.l1.character = "CangGirl";
		pchar.quest.EncGirl_DeathSimple.function = "EncGirl_DeathSimple";
	}*/
}

void EncGirl_EscortTo_Done(string qName)
{
	chrDisableReloadToLocation = false;
	pchar.quest.EncGirl_Escort_EnterToSea.over = "yes";

	ref rChr = GetCharacterFromId("CangGirl");
	if (rChr.id == Nullcharacter.id || LAi_IsDead(rChr))
	{
		ClearActiveStageNotifications();
		EncGirl_CloseQuestExit("Close_SheISDead");
		EncGirl_CloseQuestExit_func("");
	    return;
	}

	if (!CheckAttribute(rChr, "QuestFollower")) return;
	EncGirl_Escort_OverQuestHeaders();

	if ("Close_PunchHer" == pchar.GenQuest.EncGirl.CloseQuest) return; //В принципе удаления атрибуда достаточно, но на всякий случай
	if ("Close_FightBegun" == pchar.GenQuest.EncGirl.CloseQuest) return;

	chrDisableReloadToLocation = true;

	rChr.dialog.filename = "Encounters\EncGirl_Girl.c";
	switch (pchar.GenQuest.EncGirl)
	{
		case "Quest_Escort_ToTown_Should":
			EncGirl_CloseQuestExit("Close_Escort_ToTown_Done");
			rChr.dialog.currentnode = "DlgGirl_Escort_ToTown_Done";
		break;
		case "Quest_Escort_ToTavern_FromJungle_Should":
			rChr.dialog.currentnode = "DlgGirl_Escort_ToTavern_FromJungle_RememberInCity";
		break;
		case "Quest_Escort_ToTavern_FromTown_Should":
			QuestPointerDelLocEx(pchar.GenQuest.EncGirl.city +"_Town", "reload", "reload4_back", "JungleGirl");
			EncGirl_CloseQuestExit("Close_Escort_ToTown_Done");
			rChr.dialog.currentnode = "DlgGirl_Escort_InTavern_EscortDone";
		break;
		case "Quest_ChestGetted":
			LAi_type_actor_Reset(rChr);
			rChr.dialog.currentnode = "Journey_ArrivedBackToTown";
			pchar.quest.EncGirl_DeathAgain.over = "yes";
		break;
	}

	if ("Quest_Soldiers_SheIsUnderArrest" == pchar.GenQuest.EncGirl) return;
	LAi_SetActorTypeNoGroup(rChr);
	LAi_ActorFollowEverywhere(rChr, "", -1);
	LAi_MethodDelay("EncGirl_EscortDone_Dialog", 2.0);
}

void EncGirl_EscortDone_Dialog()
{
	if ("Quest_Soldiers_SheIsUnderArrest" == pchar.GenQuest.EncGirl) return;

	ref rChr = GetCharacterFromId("CangGirl");
	if (rChr.id == NullCharacter.id)
	{
		AddQuestRecord("JungleGirl", "37");
		CloseQuestHeader("JungleGirl");
	    return;
	}

	if (!LAi_Character_CanDialog(rChr, pchar))
	{
		LAi_MethodDelay("EncGirl_EscortDone_Dialog", 2.0);
		return;
	}
	LAi_ActorDialog(rChr, pchar, "", -1, 0.0);
}

void EncGirl_Escort_CloseLogbook_Good()
{
	g_bEncGirl_Sld = false;
	chrDisableReloadToLocation = false;

	AddQuestRecord("JungleGirl", "34");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
	AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
	AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
	if ("Treasure_MapIsYour" == pchar.GenQuest.EncGirl)
	{
	    AddQuestUserData("JungleGirl", "WhatDoesSheDoResult", StringFromKey("EncGirl_Girl_295", GetName(NAMETYPE_ORIG, pchar.GenQuest.EncGirl.mapOwner, NAME_NOM)));
	}
	else
	{
	    AddQuestUserData("JungleGirl", "WhatDoesSheDoResult", ""); //Она просто гуляла
	}
	CloseQuestHeader("JungleGirl");
}

void EncGirl_Escort_EnterToSea(string qName)
{
	DeleteAttribute(pchar, "quest.EncGirl_Escort_EnterToSea");

	ReOpenQuestHeader("JungleGirl");
	AddQuestRecord("JungleGirl", "39");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
	AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
	AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.city));
	CloseQuestHeader("JungleGirl");

	pchar.GenQuest.EncGirl = "Quest_Escort_EnterToSea";
	EncGirl_CloseQuestExit("Close_SheIsDead");
	EncGirl_CloseQuestExit_func("");
}

void EncGirl_Escort_OverQuestHeaders()
{
	ref rChr = GetCharacterFromID("CangGirl");
	if (rChr.id != Nullcharacter.id)
	{
		if (CheckAttribute(rChr, "QuestFollower"))
			DeleteAttribute(rChr, "QuestFollower");
	}

	if (CheckAttribute(pchar, "quest.EncGirl_EscortTo"))
		pchar.quest.EncGirl_EscortTo.over = "yes";

	if (CheckAttribute(pchar, "quest.EncGirl_Escort_ToTavernFromTown_Fail"))
		pchar.quest.EncGirl_Escort_ToTavernFromTown_Fail.over = "yes";

	if (CheckAttribute(pchar, "quest.EncGirl_Escort_EnterToSea"))
		pchar.quest.EncGirl_Escort_EnterToSea.over = "yes";

	if (CheckAttribute(pchar, "quest.EncGirl_Escort_ToRoom"))
		pchar.quest.EncGirl_Escort_ToRoom.over = "yes";

	if (CheckAttribute(pchar, "quest.EncGirl_Escort_ToRoom_Fail"))
		pchar.quest.EncGirl_Escort_ToRoom_Fail.over = "yes";
}

void EncGirl_Escort_ToTavernFromTown_Fail()
{
    pchar.quest.EncGirl_EscortTo.over = "yes";

	ref rChr = GetCharacterFromID("CangGirl");
	if (rChr.id == Nullcharacter.id)
	{
	    EncGirl_CloseQuestExit("Close_SheISDead");
	}
    else
	{
		EncGirl_Escort_CloseLogbook_Good();

		if (pchar.GenQuest.EncGirl == "Quest_InTavern_ToRoom_ToBarman" || pchar.GenQuest.EncGirl == "Quest_InTavern_ToRoom_Should")
		{
			EncGirl_CloseQuestExit("Close_Close");
		}
		else
		{
			pchar.GenQuest.EncGirl = "Quest_Escort_GoodEnd";
			EncGirl_CloseQuestExit("Close_SheIsInSafe");
		}
	}
	LAi_MethodDelay("EncGirl_CloseQuestExit_func", 0.2); //Чтобы успел отработать чекер квестов ProcessCondition
}

void EncGirl_Escort_FightBegun() //закрытие квеста, если начались тёрки с представителями нации девки
{
	if (pchar.GenQuest.EncGirl == "Quest_Journey_LetsGo") //Coffee доделать
	{
		AddQuestRecord("JungleGirl", "28");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", "а"));
		CloseQuestHeader("JungleGirl");
		EncGirl_CloseQuestExit("Close_close");
	}
	else
	{
		ref rChr = GetCharacter(LAi_group_GetTarget(pchar));
		pchar.GenQuest.EncGirl.nation = rChr.nation; //Для записи в журнал
	    EncGirl_CloseQuestExit("Close_FightBegun");
	}

	EncGigl_SheFleeAway(true, true);
}
// <-- ESCORT functions
//SOLDIERS ENC functions -->
bool EncGirl_Soldiers_Check(ref rChr)
{
	if (!CheckAttribute(pchar, "GenQuest.EncGirl"))
	{
		g_bEncGirl_Sld = false;
	    return false;
	}

	if (pchar.GenQuest.EncGirl.city != rChr.city)
		return false;

	int iColony = FindColony(rChr.City);
	if (iColony > -1)
	{
		ref rColony = GetColonyByIndex(iColony);
		if ("1" == rColony.HeroOwn)
		{
			g_bEncGirl_Sld = false;
			return false;
		}
	}

	SendMessage(pchar, "lsl", MSG_CHARACTER_EX_MSG, "SetFightMode", 0);
	LAi_SetFightMode(Pchar, false);
	if (!LAi_Character_CanDialog(rChr, pchar)) return false;

	if (pchar.GenQuest.EncGirl == "Quest_Escort_ToTown_Should" ||
	 pchar.GenQuest.EncGirl == "Quest_Escort_ToTavern_FromTown_Should" ||
	 pchar.GenQuest.EncGirl == "Quest_Escort_ToTavern_FromJungle_Should")
	{
		rChr.Dialog.TempNode = rChr.Dialog.CurrentNode;
		rChr.Dialog.CurrentNode = "EncGirl_SldDlg_SheIsUnderArrest";
	}
	else if (pchar.GenQuest.EncGirl == "Quest_Escort_ToFather_Should")
	{
		rChr.Dialog.TempNode = rChr.Dialog.CurrentNode;
		rChr.Dialog.CurrentNode = "EncGirl_FatherSeeksHer";
	}
	else if ("Quest_Soldiers_SheIsUnderArrest" == pchar.GenQuest.EncGirl)
	{
		//Уже заговорили, но g_bEncGirl_Sld пока не снимаем, чтобы солдат сразу после диалога не проверял на шпиона
	    return true;
	}
	else
	{
		g_bEncGirl_Sld = false;
	    return false;
	}

	rChr.chr_ai.type.state = "dialog";
	if (LAi_tmpl_SetDialog(rChr, pchar, -1.0))
	{
		chrDisableReloadToLocation = false;
		return true;
	}
	return false;
}

void EncGirl_Soldiers_GoToJail()
{

	ref rGirl = GetCharacterFromID("CangGirl");
	DeleteAttribute(rGirl, "QuestFollower");

	ref rSld = GetCharacterFromID(pchar.GenQuest.EncGirl.Soldiers.SldID);
	if (rSld.id == Nullcharacter.id || rGirl.id == Nullcharacter.id)
	{
		CloseQuestHeader("JungleGirl");
		EncGirl_CloseQuestExit("Close_close");
		EncGirl_CloseQuestExit_func("");
		trace("ERROR: EncGirl_Soldiers_GoToJail" +" rSld.id: " +rSld.id +" rGirl.id: " +rGirl.id);
	    return;
	}

	LAi_SetDefaultDead(rGirl);
	LAi_group_MoveCharacter(rGirl, GetNationNameByType(sti(rSld.nation)) + "_citizens");

	aref arLocator;
	string sLocator = "reload_jail";
	if (!FindLocator(loadedlocation.id, sLocator, &arLocator, true))
	{
		sLocator = "Reload3_back1";
	    if (!FindLocator(loadedlocation.id, sLocator, &arLocator, true))
		{
			sLocator = "";
			ChangeCharacterAddressGroup(rGirl, "None", "", "");
		}
	}
	if (sLocator != "")
	{
		LAi_SetActorTypeNoGroup(rGirl);
		LAi_type_actor_Reset(rGirl);
		LAi_ActorGoToLocationNoCheck(rGirl, "reload", sLocator, "none", "", "", "LandEnc_EncGirl_SoldierToJail_Go", 180.0);

		LAi_SetActorTypeNoGroup(rSld);
		LAi_ActorFollow(rSld, rGirl, "", -1);
		MakeUnpushable(rGirl, true);
		SetBonusPush(rGirl, true);
		MakeUnpushable(rSld, true);
		SetBonusPush(rSld, true);
		rGirl.chr_ai.disableDlg = "1";
		rSld.chr_ai.disableDlg = "1";

		pchar.EncGirl.Soldiers.ToJailLocator = sLocator;

		LAi_SetCheckMinHP(rSld, LAi_GetCharacterHP(rSld) - 1, false, "LandEnc_EncGirl_SoldierToJail_Atack");
		LAi_SetCheckMinHP(rGirl, LAi_GetCharacterHP(rGirl) - 1, false, "LandEnc_EncGirl_SoldierToJail_Atack");
		LAi_SetCheckAlarm(rSld, "EncGirl_Soldiers_GoToJail_SldAtack");

		SendMessage(rSld, "lfffsfff", MSG_CHARACTER_VIEWSTRPOS, 0.0, 0.0, 0.1, StringFromKey("Common_Soldier_172"), 255.0, 255.0, 255.0);
	}

	AddQuestRecord("JungleGirl", "40");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("JungleGirl");

	EncGirl_CloseQuestExit("Close_Soldiers_ToPrisonHer");
}

void EncGirl_Soldiers_GoToJail_SldToJail()
{
	if (!CheckAttribute(pchar, "GenQuest.EncGirl.Soldiers.SldID")) return;
	ref rSld = GetCharacterFromID(pchar.GenQuest.EncGirl.Soldiers.SldID);
	if (rSld.id == Nullcharacter.id) return;
	LAi_SetActorTypeNoGroup(rSld);
	LAi_type_actor_Reset(rSld);
    LAi_ActorGoToLocationNoCheck(rSld, "reload", pchar.EncGirl.Soldiers.ToJailLocator, "none", "", "", "", 10.0);
}

void EncGirl_Soldiers_GoToJail_SldAtack()
{
    //Игрок решил напасть на стража или девку во время сопровождения девки в тюьму
    ref rGirl = GetCharacterFromID("CangGirl");
    ref rSld = GetCharacterFromID(pchar.GenQuest.EncGirl.Soldiers.SldID);

	if (rGirl.id != Nullcharacter.id)
	{
		LAi_RemoveCheckMinHP(rGirl);
		LAi_type_actor_Reset(rGirl);
		LAi_ActorRunToLocationNoCheck(rGirl, "reload", LAi_FindNearestLocator2NPC(rGirl, "reload"), "none", "", "", "", 20.0);
		MakeUnpushable(rGirl, false);
		SetBonusPush(rGirl, false);
	}

	if (rSld.id != Nullcharacter.id)
	{
		LAi_RemoveCheckAlarm(rSld);
		LAi_RemoveCheckMinHP(rSld);
		LAi_SetGuardianTypeNoGroup(rSld);
		LAi_group_Attack(rSld, Pchar);
		MakeUnpushable(rSld, false);
		SetBonusPush(rSld, false);
	}

	EncGirl_CloseQuestExit("Close_close");
}
// <-- SOLDIERS ENC functions
// TAVERN functions -->
void EncGirl_InTavern_ToRoom_Done(string qName)
{
	LocatorReloadEnterDisable(pchar.GenQuest.EncGirl.city + "_tavern", "reload2_back", true);

	ref rChr = GetCharacterFromId("CangGirl");
	if (rChr.id == Nullcharacter.id)
	{
		chrDisableReloadToLocation = false;
		EncGirl_CloseQuestExit("Close_SheIsDead");
		EncGirl_CloseQuestExit_func("");
		return;
	}

	chrDisableReloadToLocation = true;
	LAi_SetFightMode(pchar, false);
	LAi_LockFightMode(pchar, true);
	rChr.dialog.filename = "Encounters\EncGirl_Girl.c";
	rChr.dialog.currentnode = "DlgGirl_InTavern_SpeakInRoom";
	if (PlaceCharacter(rChr, "goto", "random_must_be_near") == "")
	{
	    TeleportCharacterToLocator(rChr, pchar.location.group, pchar.location.locator);
	}
	RemoveLandQuestMark_Gen(GetCharacterFromID("CangGirl"), "JungleGirl");

	DoQuestFunctionDelay("EncGirl_InTavern_DialogInRoom", 2);
}

void EncGirl_InTavern_DialogInRoom(string qName)
{
	ref rChr = GetCharacterFromId("CangGirl");
	if (rChr.id == Nullcharacter.id)
	{
		chrDisableReloadToLocation = false;
		EncGirl_CloseQuestExit("Close_SheIsDead");
		EncGirl_CloseQuestExit_func("");
		return;
	}

	if (!LAi_Character_CanDialog(rChr, pchar))
	{
		LAi_MethodDelay("EncGirl_InTavern_DialogInRoom", 2.0);
		return;
	}
	LAi_SetActorTypeNoGroup(rChr);
	LAi_ActorDialog(rChr, pchar, "", -1, 0.0);
}

void EncGirl_InTavern_SetBurglar(string qName)
{
	int iTemp = sti(pchar.rank) + rand(5);
	ref rChr = GetCharacter(NPC_GenerateCharacter("EncGirl_Burglar_Chr", "citiz_"+(rand(9)+51), "man", "man", iTemp, PIRATE, -1, true)); //watch_quest_moment
	FantomMakeCoolFighter(rChr, iTemp, 50 + rand(30), 50 + rand(30), "topor2", "pistol6", 50);
	if (!ChangeCharacterAddressGroup(rChr, pchar.location, "reload", "reload1_back"))
	{
		DisableAllExits(false);
		LAi_KillCharacter(rChr);
	    return;
	}

	rChr.dialog.filename = "Encounters\EncGirl_Rapers.c";
	rChr.dialog.currentnode = "EncGirl_InTavern_Burglar";
	rChr.greeting = "Enc_Raiders";
	LAi_SetActorTypeNoGroup(rChr);
	LAi_group_MoveCharacter(rChr, "EnemyFight");
	LAi_ActorDialog(rChr, pchar, "", 4.0, 0);

	if (CheckAttribute(pchar, "GenQuest.EncGirl.BarmanID"))
		AddLandQuestMark_Gen(GetCharacterFromID(pchar.GenQuest.EncGirl.BarmanID), "JungleGirl");

	pchar.GenQuest.EncGirl = "Quest_InTavern_MeetBurglar";
}

void EncGirl_InTavern_FightBurglar()
{
	DisableAllExits(true);
	LAi_LockFightMode(pchar, false);
	AddCharacterExpToSkill(pchar, "FencingLight", 30);
	AddCharacterExpToSkill(pchar, "Fencing", 30);
	AddCharacterExpToSkill(pchar, "FencingHeavy", 30);
	LAi_SetFightMode(pchar, true);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
    LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
	pchar.quest.EncGirl_InTavern_KillBurglar.win_condition.l1 = "NPC_Death";
	pchar.quest.EncGirl_InTavern_KillBurglar.win_condition.l1.character = "EncGirl_Burglar_Chr";
	pchar.quest.EncGirl_InTavern_KillBurglar.win_condition = "OpenTheDoors";
}

void EncGirl_InTavern_PayMoneyToBurglar()
{
	AddCharacterExpToSkill(pchar, "Commerce", 50);
	AddCharacterExpToSkill(pchar, "Fortune", 50);

	ref rChr = GetCharacterFromId("EncGirl_Burglar_Chr");
	rChr.LifeDay = 0;
	LAi_SetActorTypeNoGroup(rChr);
	LAi_ActorGoToLocation(rChr, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
	LAi_LockFightMode(pchar, false);
}


void EncGirl_InTavern_LackMoneyToBurglar()
{
	// ==> Забираем клинки, пистоли и деньги.
	RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
	RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
    RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
    while (FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE) != "")
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, BLADE_ITEM_TYPE));
    while (FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE) != "")
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, GUN_ITEM_TYPE));
    while (FindCharacterItemByGroup(pchar, MUSKET_ITEM_TYPE) != "")
        TakeItemFromCharacter(pchar, FindCharacterItemByGroup(pchar, MUSKET_ITEM_TYPE));
    pchar.money = 0;
    // <== Забираем клинки, пистоли и деньги.
	AddCharacterExpToSkill(pchar, "Commerce", 50);
	AddCharacterExpToSkill(pchar, "Fortune", 50);

	ref rChr = GetCharacterFromId("EncGirl_Burglar_Chr");
	rChr.LifeDay = 0;
	LAi_SetActorTypeNoGroup(rChr);
	LAi_ActorGoToLocation(rChr, "reload", "reload1_back", "none", "", "", "OpenTheDoors", -1.0);
	LAi_LockFightMode(pchar, false);
}

void EncGirl_InTavern_BurglarEnd()
{
	pchar.quest.EncGirl_InTavern_EndBurglar.over = "yes";

	EncGirl_CloseQuestExit("Close_InTavern_MeetBurglar");
	EncGirl_CloseQuestExit_func("");
}

// <-- TAVERN functions
bool EncGigl_SheFleeAway(bool bRun, bool bToCitizens)
{
	EncGirl_Escort_OverQuestHeaders();
	EncGirl_RemoveQuestMarks();

	ref rGirl = GetCharacterFromId("CangGirl");
	if (rGirl.id == Nullcharacter.id) return false;

	rGirl.lifeDay = "1";
	rGirl.chr_ai.disableDlg = "1";
	if (Lai_IsDead(rGirl)) return false;

	string sTemp;
	float locx, locy, locz;

	if (CheckAttribute(rGirl, "QuestFollower")) //убрать шаблон следования за гг
	{
		LAi_tmpl_follow_Complite(rGirl);
		LAi_type_actor_Reset(rGirl);
		DeleteAttribute(rGirl, "QuestFollower");
	}

	LAi_SetDefaultDead(rGirl);

	if (bToCitizens)
	{
		sTemp = GetNationNameByType(sti(rGirl.nation)) + "_citizens";
		LAi_group_MoveCharacter(rGirl, sTemp);
	}

	sTemp = "";
	GetCharacterPos(rGirl, &locx, &locy, &locz);
	sTemp = LAi_FindNearestFreeLocator("reload", locx, locy, locz);
	if (sTemp == "") sTemp = LAi_FindNearestLocator("reload1_back", locx, locy, locz);
	if (sTemp == "") LAi_SetCitizenType(rGirl);
	else
	{
		LAi_SetActorTypeNoGroup(rGirl);
		if (bRun)
		{
			LAi_ActorRunToLocationNoCheck(rGirl, "reload", sTemp, "none", "", "", "", 30.0);
			MakeUnpushable(rGirl, true);
		    SetBonusPush(rGirl, true);
		    DeleteAttribute(rGirl, "ActorGoToLocationNoCheck");
		}
		else
		{
			LAi_ActorGoToLocationNoCheck(rGirl, "reload", sTemp, "none", "", "", "", 60.0);
			rGirl.ActorGoToLocationNoCheck = "1"; //Чтобы убежала когда гг её ударит
		}
	}

	return true;
}

void EncGirl_CloseQuestExit(string sCondition)
{
	//sCondition == "close" не повышать репу и не давать слухи
	pchar.GenQuest.EncGirl.CloseQuest = sCondition;
	pchar.quest.LandEnc_EncGirl_CloseQuestExit.win_condition.l1 = "ExitFromLocation";
	pchar.quest.LandEnc_EncGirl_CloseQuestExit.win_condition.l1.location = loadedlocation.id;
	pchar.quest.LandEnc_EncGirl_CloseQuestExit.function = "EncGirl_CloseQuestExit_func";
}

void EncGirl_Pearls_ToChurch_Func(string qName)
{
	ref sld = GetCharacterFromID("CangGirl");
	ChangeCharacterAddressGroup(sld, pchar.GenQuest.EncGirl.city + "_church", "goto", "goto1");
	LAi_SetStayType(sld);
}

void EncGirl_Pearls_TimeIsUp_Func(string qName)
{
	EncGirl_CloseQuestExit("Close_Pearls_TimeIsUp");
}

void EncGirl_GenQuest_GetChestPlaceName()
{
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0:
			pchar.GenQuest.EncGirl.islandId = "Bermudes";
			pchar.GenQuest.EncGirl.placeId = "Bermudes_Cavern";
			pchar.GenQuest.EncGirl.shoreId = "Shore_ship1";
		break;
		case 1:
			pchar.GenQuest.EncGirl.islandId = "Caiman";
			pchar.GenQuest.EncGirl.placeId = "Caiman_Grot";
			pchar.GenQuest.EncGirl.shoreId = "Shore17";
		break;
		case 2:
			pchar.GenQuest.EncGirl.islandId = "Dominica";
			pchar.GenQuest.EncGirl.placeId = "Dominica_Grot";
			pchar.GenQuest.EncGirl.shoreId = "Shore26";
		break;
		case 3:
			pchar.GenQuest.EncGirl.islandId = "Terks";
			pchar.GenQuest.EncGirl.placeId = "Terks_Grot";
			pchar.GenQuest.EncGirl.shoreId = "Shore56";
		break;
	}
}
//Coffee TODO: ref
void EncGirl_Death(string qName)
{
	AddQuestRecord("JungleGirl", "5");
    AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
	CloseQuestHeader("JungleGirl");
	pchar.quest.EncGirl_FindChest.over = "yes";
	DeleteAttribute(pchar, "GenQuest.EncGirl.islandId");
	DeleteAttribute(pchar, "GenQuest.EncGirl.placeId");
	ChangeCharacterReputation(pchar, -20);
    pchar.quest.DeleteGirlGroup.win_condition.l1 = "ExitFromLocation";
    pchar.quest.DeleteGirlGroup.win_condition.l1.location = pchar.location;
    pchar.quest.DeleteGirlGroup.function = "EncGirl_DeleteGirlGroup";
}

void EncGirl_DeathAgain(string qName)
{
	AddQuestRecord("JungleGirl", "7");
	AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
	CloseQuestHeader("JungleGirl");
	ChangeCharacterReputation(pchar, -20);
	pchar.quest.EncGirl_EscortTo.over = "yes";
	pchar.quest.DeleteGirlGroup.win_condition.l1 = "ExitFromLocation";
    pchar.quest.DeleteGirlGroup.win_condition.l1.location = pchar.location;
    pchar.quest.DeleteGirlGroup.function = "EncGirl_DeleteGirlGroup";
}

void EncGirl_DeathSimple(string qName)
{
	if(pchar.GenQuest.EncGirl == "Quest_toParents" || pchar.GenQuest.EncGirl == "Quest_FindLover")
	{
		AddQuestRecord("JungleGirl", "10");
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		CloseQuestHeader("JungleGirl");
	}
	ChangeCharacterReputation(pchar, -20);
	pchar.quest.EncGirl_EscortTo.over = "yes";
	pchar.quest.DeleteGirlGroup.win_condition.l1 = "ExitFromLocation";
    pchar.quest.DeleteGirlGroup.win_condition.l1.location = pchar.location;
    pchar.quest.DeleteGirlGroup.function = "EncGirl_DeleteGirlGroup";
}

void EncGirl_DeleteGirlGroup(string qName) //coffee TODO: убрать это
{
	LAi_group_Delete("DeliveQuest_Girl");
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_FindChest(string qName)
{
	float locx, locy, locz;
	chrDisableReloadToLocation = true;
	LAi_LocationDisableMonstersGen(pchar.location, true);
	pchar.quest.EncGirl_Death.over = "yes";
	ref sld = GetCharacterFromId("CangGirl");
	sld.dialog.filename = "Encounters\EncGirl_Girl.c";
	sld.dialog.currentnode = "TheChestWasFound";
	LAi_SetActorTypeNoGroup(sld);
	GetCharacterPos(sld, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void EncGirl_AddPassenger(string qName)
{
	ref sld = GetCharacterFromId("CangGirl");
	AddPassenger(pchar, sld, false);
	SetCharacterRemovable(sld, false);
	LAi_type_actor_Reset(sld);
	ChangeCharacterAddress(sld, "none", "");
}

void EncGirl_DialogAtShore(string qName)
{
	ref sld = GetCharacterFromId("CangGirl");
	sld.dialog.filename = "Encounters\EncGirl_Girl.c";
	sld.dialog.currentnode = "Journey_ArrivedAtShore";
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
	pchar.quest.EncGirl_EnterToSea.win_condition.l1 = "EnterToSea";
	pchar.quest.EncGirl_EnterToSea.function = "EncGirl_EnterToSea";
	pchar.quest.EncGirl_Death.over = "yes";
}

void EncGirl_EnterToSea(string qName)
{
	ref sld = GetCharacterFromId("CangGirl");
	if(pchar.GenQuest.EncGirl == "Quest_ChestGetted") // забрали клад
	{
		LAi_type_actor_Reset(sld);
	}
	else // кинули тетку на острове, клад не стали брать
	{
		pchar.quest.EncGirl_EscortTo.over = "yes"; // снимаем ненужные прерывания
		pchar.quest.EncGirl_DeathAgain.over = "yes";
		pchar.quest.EncGirl_FindChest.over = "yes";
		ChangeCharacterReputation(pchar, -5);
		AddQuestRecord("JungleGirl", "5_1");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
		AddQuestUserData("JungleGirl", "sName", pchar.GenQuest.EncGirl.name);
		CloseQuestHeader("JungleGirl");
		RemovePassenger(pchar, sld);
		ChangeCharacterAddress(sld, "none", "");
		sld.lifeDay = 0;
		DeleteAttribute(pchar, "GenQuest.EncGirl");
	}
}

void EncGirl_FindTreasure(string qName)
{
	float locx, locy, locz;
	chrDisableReloadToLocation = true;
	LAi_LocationDisableMonstersGen(pchar.location, true);
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	ref sld = GetCharacterFromId("CangGirl");
	sld.dialog.filename = "Encounters\EncGirl_Girl.c";
	sld.dialog.currentnode = "Node_207";
	LAi_SetActorTypeNoGroup(sld);
	GetCharacterPos(sld, &locx, &locy, &locz);
	ChangeCharacterAddressGroup(sld, pchar.location, "monsters", LAi_FindFarLocator("monsters", locx, locy, locz));
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}


void EncGirl_MeetRapers(string qName)
{
	ref rChr;
	int i, iIdx;
	bool bSpeaker = false;
	for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
	{
		iIdx = GetCharacterIndex("EncGirl_GangMan_" + i);
		if (iIdx < 0) continue;
		rChr = &Characters[iIdx];
		LAi_SetImmortal(rChr, false);
		LAi_type_actor_Reset(rChr);
		rChr.dialog.filename = "Encounters\EncGirl_Rapers.c";
		rChr.dialog.currentnode = "Node_8";
		rChr.greeting = "Enc_Raiders";
		rChr.location = "none";
		PlaceCharacter(rChr, "goto", "random_must_be_near");
		LAi_ActorFollow(rChr, pchar, "", -1);
        LAi_group_MoveCharacter(rChr, "EnemyFight");

        if (!bSpeaker)
		{
			LAi_ActorDialog(rChr, pchar, "", 4.0, 0);
			bSpeaker = true;
		}
	}
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
	LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER_OWN, LAI_GROUP_NEITRAL);

	LAi_group_ClearAllTargets();
	LAi_SetFightModeForOfficers(false);

	chrDisableReloadToLocation = true;
	DoQuestCheckDelay("OpenTheDoors", 5.0);
}

void EncGirl_GenerateLeatherBag(string qName)
{
	ref location;
	string boxId = "box1";
	aref boxItems;

	if(pchar.GenQuest.EncGirl == "Quest_Bag_BrothelRoomUp") // верхняя комната
	{
		location = &Locations[FindLocation(pchar.GenQuest.EncGirl.city + "_Brothel_room")];
	}
	if(pchar.GenQuest.EncGirl == "Quest_Bag_BrothelRoom")
	{
		location = &Locations[FindLocation(pchar.GenQuest.EncGirl.city + "_SecBrRoom")];
	}

	makearef(boxItems, location.(boxId).items);

	boxItems.leather_bag = 1;
	location.(boxId) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	Log_TestInfo("Генерируем саквояж");
}

void EncGirl_RapersChest(string qName)
{
	ref location = &Locations[FindLocation(pchar.GenQuest.TreasureEncGirl)];
	string boxId = pchar.GenQuest.TreasureEncGirlBox;
	aref boxItems;

	makearef(boxItems, location.(boxId).items);

	boxItems.gold = GetSummonSkillFromName(pchar, SKILL_FORTUNE) * 100 + rand(3000);

	if(rand(3) == 1)
	{
		boxItems.jewelry2 = 10 + rand(3);
	}
	if(rand(1) == 1)
	{
		boxItems.jewelry1 = 15 + rand(10);
	}
	if(rand(1) == 1)
	{
		boxItems.jewelry12 = 25 + rand(15);
	}
	if(rand(1) == 1)
	{
		boxItems.jewelry11 = 18 + rand(20);
	}
	if(rand(1) == 1)
	{
		boxItems.jewelry7 = 22 + rand(12);
	}

	location.(boxId) = Items_MakeTime(GetTime(), GetDataDay(), GetDataMonth(), GetDataYear());
	location.(boxId).Treasure = true; // Признак сокровища в сундуке
}

void EncGirl_TreasureLose(string qName)
{
	ref location = &Locations[FindLocation(pchar.GenQuest.TreasureEncGirl)];
	string boxId = pchar.GenQuest.TreasureEncGirlBox;

	pchar.quest.EncGirl_RapersTreasure.over = "yes";

	DeleteAttribute(location, boxId + ".items");
	DeleteAttribute(location, boxId + ".Treasure");

	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_RapersAfter(string qName)
{
	pchar.quest.EncGirl_TreasureLose.win_condition.l1 = "Timer";
	pchar.quest.EncGirl_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
	pchar.quest.EncGirl_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
	pchar.quest.EncGirl_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
	pchar.quest.EncGirl_TreasureLose.function = "EncGirl_TreasureLose";

	pchar.quest.EncGirl_RapersTreasure.win_condition.l1 = "location";
	pchar.quest.EncGirl_RapersTreasure.win_condition.l1.location = pchar.GenQuest.TreasureEncGirl;
	pchar.quest.EncGirl_RapersTreasure.function = "EncGirl_RapersChest";
}

void EncGirl_GenQuest_GetBag(string qName)
{
	ref sld = GetCharacterFromID("CangGirl");
	sld.lifeDay = 0;
	AddSimpleRumour(RandPhraseSimple(StringFromKey("Common_rumours_138"),
				StringFromKey("Common_rumours_139")),
				sti(pchar.GenQuest.EncGirl.nation), 3, 1);
	ChangeCharacterReputation(pchar, -8);
	pchar.quest.EncGirl_GenerateBag.over = "yes";
	pchar.quest.EncGirl_SpeakHorse.over = "yes";
	AddQuestRecord("JungleGirl", "22");
	CloseQuestHeader("JungleGirl");
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_ExitTavernRoom(string qName)
{
	LocatorReloadEnterDisable(pchar.GenQuest.EncGirl.city + "_tavern", "reload2_back", false);

	pchar.quest.EncGirl_SpeakHorse.win_condition.l1 = "location";
	pchar.quest.EncGirl_SpeakHorse.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern_upstairs";
	pchar.quest.EncGirl_SpeakHorse.function = "EncGirl_SpeakHorse";
	ref sld = GetCharacterFromId("CangGirl");
	ChangeCharacterAddress(sld, "none", "");
}

void EncGirl_SpeakHorse(string qName)
{
	ref sld = GetCharacterFromId("CangGirl");
	sld.dialog.filename = "Encounters\EncGirl_Girl.c";
	sld.dialog.currentnode = "Node_240_1";
	ChangeCharacterAddress(sld, pchar.location, "goto1");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", 2.0, 0);
}

void EncGirl_DeliveToParents(string qName)
{
	ref sld;
	sld = GetCharacterFromId("CangGirl");
	RemovePassenger(pchar, sld);
	sld.dialog.filename = "Encounters\EncGirl_Girl.c";
	sld.dialog.currentnode = "Node_245";
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void EncGirl_GenerateLover(string qName)
{
	int iTemp = sti(pchar.rank) + rand(5);
	string LOVER = GetRandSubstring("Youngman,officer_4,officer_12,officer_13,officer_14,officer_15,officer_22,citiz_5,citiz_7"); //TODO: заменить на парней/молодых дворян
	ref sld = GetCharacter(NPC_GenerateCharacter("Lover_EncGirl", LOVER, "man", "man", iTemp, sti(pchar.GenQuest.EncGirl.nation), -1, true));
	sld.name = pchar.GenQuest.EncGirl.sLoverId;
	sld.lastname = "";
	FantomMakeCoolFighter(sld, iTemp, 80, 80, "topor2", "pistol6", 50);
	pchar.quest.EncGirl_SpeakLoverTavern.win_condition.l1 = "location";
	pchar.quest.EncGirl_SpeakLoverTavern.win_condition.l1.location = pchar.GenQuest.EncGirl.city + "_tavern";
	pchar.quest.EncGirl_SpeakLoverTavern.function = "EncGirl_SpeakLover";
}

void EncGirl_SpeakLover(string qName)
{
	chrDisableReloadToLocation = true;
	ref sld = GetCharacterFromId("Lover_EncGirl");
	sld.dialog.filename = "Quest\GenQuests_dialog.c";
	sld.dialog.currentnode = "EncGirl_Lover";
	sld.greeting = "Gr_Officer";
	PlaceCharacter(sld, "goto", pchar.GenQuest.EncGirl.city + "_tavern");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1.0, 0);
}

void EncGirl_LoverExit()
{
	string sTemp;
	ref sld;
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	AddQuestRecord("JungleGirl", "14");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ёл","ела"));
	CloseQuestHeader("JungleGirl");
	ChangeCharacterReputation(pchar, -3);
	sTemp = LAi_FindNearestFreeLocator2Pchar("reload");

	for (int i = 1; i <= 2; i++)
	{
		if (i == 1) sld = GetCharacterFromId("Lover_EncGirl");
		else sld = GetCharacterFromId("CangGirl");
		sld.lifeDay = 0;
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
	}

	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_ToLoverParents()
{
	ref sld;
	string sTemp;
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	ReOpenQuestHeader("JungleGirl");
	AddQuestRecord("JungleGirl", "15");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ся","ась"));
	AddQuestUserData("JungleGirl", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.EncGirl.LoverCity));
	ChangeCharacterReputation(pchar, 1);
	sTemp = LAi_FindNearestFreeLocator2Pchar("reload");

	for (int i = 1; i <= 2; i++)
	{
		if (i == 1) sld = GetCharacterFromId("Lover_EncGirl");
		else sld = GetCharacterFromId("CangGirl");
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		LAi_SetActorTypeNoGroup(sld);
		LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "", "OpenTheDoors", 5.0);
	}

	pchar.quest.EncGirl_DeliveToLoverParents.win_condition.l1 = "location";
	pchar.quest.EncGirl_DeliveToLoverParents.win_condition.l1.location = pchar.GenQuest.EncGirl.LoverCity + "_town";
	pchar.quest.EncGirl_DeliveToLoverParents.function = "EncGirl_DeliveToLoverParents";
}

void EncGirl_ToLoverParentsExit()
{
	pchar.quest.EncGirl_DeathSimple.over = "yes";
	ChangeCharacterReputation(pchar, -3);
	AddMoneyToCharacter(pchar, 500 * (sti(pchar.rank) + 10) + drand(5000));
	AddQuestRecord("JungleGirl", "13");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("ёл","ела"));
	CloseQuestHeader("JungleGirl");
	ref sld = GetCharacterFromID("CangGirl");
	string sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", sTemp, "none", "", "","", -1.0);
	sld.lifeDay = 0;
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_DeliveToLoverParents(string qName)
{
	pchar.GenQuest.Hunter2Pause = true;
	ref sld;
	sld = GetCharacterFromId("CangGirl");
	RemovePassenger(pchar, sld);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
	sld.lifeday = 0;
	sld = GetCharacterFromId("Lover_EncGirl");
	RemovePassenger(pchar, sld);
	chrDisableReloadToLocation = true;
	sld.dialog.filename = "Quest\GenQuests_dialog.c";
	sld.dialog.currentnode = "EncGirl_Lover6";
	PlaceCharacter(sld, "goto", pchar.location);
	LAi_SetActorTypeNoGroup(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void EncGirl_GenQuest_GetLoverFather(string qName)
{
	AddQuestRecord("JungleGirl", "17");
	AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("","а"));
	CloseQuestHeader("JungleGirl");
	DeleteAttribute(pchar, "GenQuest.EncGirl");
}

void EncGirl_Rapers_DisableDlg()
{
	int i, iIdx;
	ref rChr;
	for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
	{
		iIdx = GetCharacterIndex("EncGirl_GangMan_" + i);
		if (iIdx < 0) continue;
		rChr = &Characters[iIdx];
		rChr.chr_ai.disableDlg = "1";
	}
}

void EncGirl_Begin_LetsTalkToTheRapers()
{
	int i, iIdx;
	ref rChr;
	bool bFindSpeaker = false;

	chrDisableReloadToLocation = false;

	for (i = 1; i <= ENCGIRL_RAPERS_QTY; i++)
	{
		iIdx = GetCharacterIndex("EncGirl_GangMan_" + i);
		if (iIdx < 0) continue;
		rChr = &Characters[iIdx];
		if (LAi_IsDead(rChr)) continue;
		LAi_SetActorTypeNoGroup(rChr);
		LAi_ActorDialog(rChr, pchar, "", -1, 0);
		bFindSpeaker = true;
	}

	if (bFindSpeaker)
	{
		LAi_SetFightMode(pchar, false);
		LAi_LockFightMode(pchar, true);
	}
	else
	{
		trace("ERROR: EncGirl_Begin_LetsTalkToTheRapers - no alive raper found");
		Log_Info("ERROR: EncGirl_Begin_LetsTalkToTheRapers - no alive raper found");
		LAi_LockFightMode(pchar, false);
		EncGirl_CloseQuestExit("Close_close");
		EncGirl_CloseQuestExit_func("");
	}
}

void EncGirl_RemoveQuestMarks()
{
	QuestPointerDelLocEx(pchar.GenQuest.EncGirl.city +"_Town", "reload", "reload4_back", "JungleGirl");
	QuestPointerDelLocEx(pchar.GenQuest.EncGirl.city +"_tavern", "reload", "reload2_back", "JungleGirl");
	if (CheckAttribute(pchar, "GenQuest.EncGirl.BarmanID"))
	{
		RemoveLandQuestMark_Gen(GetCharacterFromID(pchar.GenQuest.EncGirl.BarmanID), "JungleGirl");
	}
	int iIdx = GetCharacterIndex("CangGirl");
	if (iIdx > -1)
	{
		RemoveLandQuestMark_Gen(&characters[iIdx], "JungleGirl");
	}
}

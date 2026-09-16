
/////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Эммануэль Пардаль
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void EPL_TFS_TalkedToHovernorSD()
{
	EPL_DOSD_Final();
	
	SetQuestHeader("EPL_TheFirstSteps");
	AddQuestRecord("EPL_TheFirstSteps", "1");
	
	LocatorReloadEnterDisable("SantoDomingo_town", "Reload1_back", false);
	ChangeCharacterNationReputation(pchar, SPAIN, 18);
	AddCharacterExpToSkill(pchar, "Leadership", 100);
	
	ref sld;
	sld = CharacterFromID("SantoDomingo_Mayor");
	RestoreOldDialog(sld);
	
	sld = CharacterFromID("Edward Mansfield");
	SaveOldDialog(sld);
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_3_TheFirstSteps_dialog.c";
	sld.dialog.currentnode = "EPL_TFS_Mansfield";
	
	sld = CharacterFromID("spa_guber");
	SaveOldDialog(sld);
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_3_TheFirstSteps_dialog.c";
	sld.dialog.currentnode = "EPL_TFS_OregonGaskon";
	
	QuestPointerDelLoc("SantoDomingo_town", "reload", "reload3_back");
	
	AddLandQuestMark_Main(CharacterFromID("spa_guber"), "EPL_TheFirstSteps");
	AddLandQuestMark_Main(CharacterFromID("Edward Mansfield"), "EPL_TheFirstSteps");
	AddMapQuestMark_Major("Havana_town", "EPL_TheFirstSteps", "");
	AddMapQuestMark_Major("LaVega_town", "EPL_TheFirstSteps", "");
	
	SetFunctionLocationCondition("EPL_TFS_Sandro", "SantoDomingo_town", false);
	
	pchar.questTemp.EPL_TFS = 0;
}

void EPL_TFS_Sandro(string qName)
{
	ClearActiveStageNotifications();
	chrDisableReloadToLocation = true;
	ref sld = CharacterFromID("EPL_Sandro");
	LAi_SetImmortal(sld, true);
	sld.dialog.filename = "Quest\EmmanuelPardalLine\EPL_3_TheFirstSteps_dialog.c";
	sld.dialog.currentnode = "EPL_TFS_Sandro_1";
	ChangeCharacterAddressGroup(sld, "SantoDomingo_town", "goto", "goto19");
	LAi_SetActorType(sld);
	LAi_ActorDialog(sld, pchar, "", -1, 0);
}

void EPL_TFS_Sandro_DlgExit()
{
	AddQuestRecord("EPL_TheFirstSteps", "2");
	AddQuestUserData("EPL_TheFirstSteps", "sEmma", pchar.name);
	AddQuestUserData("EPL_TheFirstSteps", "sRemedios", FindPersonalName("Remedios_lastname"));
	AddQuestUserData("EPL_TheFirstSteps", "sPardal", pchar.lastname);
	chrDisableReloadToLocation = false;
	ref sld = CharacterFromID("EPL_Sandro");
	LAi_SetActorType(sld);
	LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", -1);
	sld.location = "None";
}

void EPL_TFS_TalkedToMansfield()
{
	AddQuestRecord("EPL_TheFirstSteps", "3");
	ref sld = CharacterFromID("Edward Mansfield");
	RestoreOldDialog(sld);
	AddCharacterExpToSkill(pchar, "Leadership", 100);
	pchar.questTemp.EPL_TFS = sti(pchar.questTemp.EPL_TFS) + 1;
	EPL_TFS_EndQuest();
}

void EPL_TFS_TalkedToOregonGaskon()
{
	AddQuestRecord("EPL_TheFirstSteps", "4");
	ref sld = CharacterFromID("spa_guber");
	RestoreOldDialog(sld);
	AddCharacterExpToSkill(pchar, "Leadership", 100);
	pchar.questTemp.EPL_TFS = sti(pchar.questTemp.EPL_TFS) + 1;
	EPL_TFS_EndQuest();
}

void EPL_TFS_EndQuest()
{
	if (CheckAttrValue(pchar, "questTemp.EPL_TFS", "2"))
	{
		pchar.questTemp.EPL_TFS = "end";
		CloseQuestHeader("EPL_TheFirstSteps");
		Achievment_Set(ACH_EPL_Prologue);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////  -- Эммануэль Пардаль --    конец
/////////////////////////////////////////////////////////////////////////////////////////////////////////

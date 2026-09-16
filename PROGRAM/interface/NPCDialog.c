int AoP_NPCDialogCurrentLine = 0;
bool AoP_NPCDialogClosing = false;

void InitInterface(string iniName)
{
	StartAboveForm(false);

	GameInterface.title = "";
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT, iniName);
	EngineLayersOffOn(true);
	locCameraSleep(false);

	AoP_NPCDialogCurrentLine = 0;
	AoP_NPCDialogClosing = false;

	AoP_NPCDialogSetParticipants();
	AoP_NPCDialogShowCurrentLine();

	SetEventHandler("Control Activation", "AoP_NPCDialogProcessControl", 0);
	SetEventHandler("evntDoPostExit", "AoP_NPCDialogDoPostExit", 0);
}

void AoP_NPCDialogSetParticipants()
{
	string sLeftID = pchar.questTemp.AoP.NPCDialog.LeftCharacter;
	string sRightID = pchar.questTemp.AoP.NPCDialog.RightCharacter;

	AoP_NPCDialogSetPortrait("LEFT_PORTRAIT", "LEFT_NAME", "LEFT_NATION", sLeftID);
	AoP_NPCDialogSetPortrait("RIGHT_PORTRAIT", "RIGHT_NAME", "RIGHT_NATION", sRightID);
}

void AoP_NPCDialogSetPortrait(string pictureNode, string nameNode, string nationNode, string characterID)
{
	int iCharacter = GetCharacterIndex(characterID);
	ref rCharacter;
	SetNodeUsing(nameNode, true);
	SetNodeUsing(nationNode, false);

	if (iCharacter < 0)
	{
		SetFormatedText(nameNode, characterID);
		SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, nameNode, 5);
		return;
	}

	rCharacter = GetCharacter(iCharacter);

	SetFormatedText(nameNode, GetFullName(rCharacter));
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, nameNode, 5);

	SetNewGroupPicture(pictureNode, GetFaceGroupName(iCharacter), GetFacePictureName(iCharacter));

	if (!CheckAttribute(rCharacter, "HideNationIcon"))
	{
		SetNewGroupPicture(nationNode, "NATION_ICONS", GetNationNameByType(sti(rCharacter.nation)));
		SetNodeUsing(nationNode, true);
	}
}

void AoP_NPCDialogShowCurrentLine()
{
	int iCount = sti(pchar.questTemp.AoP.NPCDialog.Count);

	string sLine;
	string sSpeakerID;
	string sText;
	string sLeftID;
	string sRightID;

	bool bLeftSpeaker;
	bool bRightSpeaker;

	if (AoP_NPCDialogCurrentLine >= iCount)
	{
		AoP_NPCDialogFinish();
		return;
	}

	sLine = "line_" + AoP_NPCDialogCurrentLine;

	sSpeakerID = pchar.questTemp.AoP.NPCDialog.Lines.(sLine).Speaker;
	sText      = pchar.questTemp.AoP.NPCDialog.Lines.(sLine).Text;

	sLeftID  = pchar.questTemp.AoP.NPCDialog.LeftCharacter;
	sRightID = pchar.questTemp.AoP.NPCDialog.RightCharacter;

	SetFormatedText("DIALOG_TEXT", sText);
	SetNodeUsing("DIALOG_TEXT", true);
	SendMessage(&GameInterface, "lsl", MSG_INTERFACE_MSG_TO_NODE, "DIALOG_TEXT", 5);

	bLeftSpeaker  = (sSpeakerID == sLeftID);
	bRightSpeaker = (sSpeakerID == sRightID);

	SetNodeUsing("LEFT_SHADE",  bLeftSpeaker);
	SetNodeUsing("RIGHT_SHADE", bRightSpeaker);

	SetNodeUsing("LEFT_ACTIVE",  !bLeftSpeaker);
	SetNodeUsing("RIGHT_ACTIVE", !bRightSpeaker);
}

void AoP_NPCDialogProcessNext()
{
	if (AoP_NPCDialogClosing) return;

	AoP_NPCDialogCurrentLine++;
	AoP_NPCDialogShowCurrentLine();
}

void AoP_NPCDialogProcessControl()
{
	string sControl = GetEventData();

	if (sControl == "IAction" || sControl == "IStartButton" || sControl == "ILClick")
	{
		if (AoP_NPCDialogClosing) return;
		PlaySound("OK");
		AoP_NPCDialogProcessNext();
	}
}

void AoP_NPCDialogFinish()
{
	string sEndAction = "";
	string sEndType = "";
	bool bAutoUnlock = false;

	if (AoP_NPCDialogClosing) return;
	AoP_NPCDialogClosing = true;

	if (CheckAttribute(pchar, "questTemp.AoP.NPCDialog.EndAction"))
	{
		sEndAction = pchar.questTemp.AoP.NPCDialog.EndAction;
	}

	if (CheckAttribute(pchar, "questTemp.AoP.NPCDialog.EndType"))
	{
		sEndType = pchar.questTemp.AoP.NPCDialog.EndType;
	}

	if (CheckAttribute(pchar, "questTemp.AoP.NPCDialog.AutoUnlockPlayer") &&
		sti(pchar.questTemp.AoP.NPCDialog.AutoUnlockPlayer) == 1)
	{
		bAutoUnlock = true;
	}

	EndAboveForm(false);

	DelEventHandler("Control Activation", "AoP_NPCDialogProcessControl");
	DelEventHandler("evntDoPostExit", "AoP_NPCDialogDoPostExit");

	if (bAutoUnlock)
	{
		QuestMovieUnLockPlayer();
	}

	DeleteAttribute(pchar, "questTemp.AoP.NPCDialog");

	if (sEndAction != "")
	{
		if (sEndType == "function")
		{
			DoQuestFunctionDelay(sEndAction, 0.2);
		}
		else
		{
			DoQuestCheckDelay(sEndAction, 0.2);
		}
	}

	interfaceResultCommand = RC_INTERFACE_NPC_DIALOG;
	EndCancelInterface(true);
}

void AoP_NPCDialogDoPostExit()
{
	AoP_NPCDialogFinish();
}

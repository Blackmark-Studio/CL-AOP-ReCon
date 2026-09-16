void AoP_NPCDialogClear()
{
	DeleteAttribute(pchar, "questTemp.AoP.NPCDialog");
	pchar.questTemp.AoP.NPCDialog.Count = 0;
}

bool AoP_NPCDialogLaunchAction(string leftCharacterID, string rightCharacterID, string endAction, string endType)
{
	if (GetCharacterIndex(leftCharacterID) < 0)
	{
		trace("AoP_NPCDialogLaunch: персонаж не найден: " + leftCharacterID);
		return false;
	}

	if (GetCharacterIndex(rightCharacterID) < 0)
	{
		trace("AoP_NPCDialogLaunch: персонаж не найден: " + rightCharacterID);
		return false;
	}

	if (!CheckAttribute(pchar, "questTemp.AoP.NPCDialog.Count") ||
		sti(pchar.questTemp.AoP.NPCDialog.Count) < 1)
	{
		trace("AoP_NPCDialogLaunch: очередь реплик пуста.");
		return false;
	}

	pchar.questTemp.AoP.NPCDialog.LeftCharacter = leftCharacterID;
	pchar.questTemp.AoP.NPCDialog.RightCharacter = rightCharacterID;
	pchar.questTemp.AoP.NPCDialog.EndAction = endAction;
	pchar.questTemp.AoP.NPCDialog.EndType = endType;
	pchar.questTemp.AoP.NPCDialog.AutoUnlockPlayer = 0;

	if (procInterfacePrepare(INTERFACE_NPC_DIALOG))
	{
		nPrevInterface = -1;
		CurrentInterface = INTERFACE_NPC_DIALOG;
		InitInterface(Interfaces[CurrentInterface].IniFile);
		return true;
	}

	if (CheckAttribute(pchar, "questTemp.AoP.NPCDialog.AutoUnlockPlayer") &&
		sti(pchar.questTemp.AoP.NPCDialog.AutoUnlockPlayer) == 1)
	{
		QuestMovieUnLockPlayer();
	}

	return false;
}

bool AoP_NPCDialogLaunch(string leftCharacterID, string rightCharacterID, string endQuest)
{
	return AoP_NPCDialogLaunchAction(leftCharacterID, rightCharacterID, endQuest, "quest");
}

bool AoP_NPCDialogLaunchFunction(string leftCharacterID, string rightCharacterID, string endFunction)
{
	return AoP_NPCDialogLaunchAction(leftCharacterID, rightCharacterID, endFunction, "function");
}

void AoP_NPCDialogAddLine(string sSpeakerID, string sText)
{
	int n = 0;
	string sNode;

	if (CheckAttribute(pchar, "questTemp.AoP.NPCDialog.Count"))
	{
		n = sti(pchar.questTemp.AoP.NPCDialog.Count);
	}

	sNode = "line_" + n;

	pchar.questTemp.AoP.NPCDialog.Lines.(sNode).Speaker = sSpeakerID;
	pchar.questTemp.AoP.NPCDialog.Lines.(sNode).Text = sText;
	pchar.questTemp.AoP.NPCDialog.Count = n + 1;
}

bool AoP_NPCDialogSingleLine(string leftCharacterID, string rightCharacterID, string speakerID, string text, string endQuest)
{
	AoP_NPCDialogClear();
	AoP_NPCDialogAddLine(speakerID, text);

	return AoP_NPCDialogLaunch(leftCharacterID, rightCharacterID, endQuest);
}

bool AoP_NPCDialogSingleLineFunction(string leftCharacterID, string rightCharacterID, string speakerID, string text, string endFunction)
{
	AoP_NPCDialogClear();
	AoP_NPCDialogAddLine(speakerID, text);

	return AoP_NPCDialogLaunchFunction(leftCharacterID, rightCharacterID, endFunction);
}
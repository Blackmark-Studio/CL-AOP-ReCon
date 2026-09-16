void EI_CreateFrame(string sNodeName, int x1, int y1, int x2, int y2)
{
	SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 1, "MAIN_ICONS");

	// UPLEFT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_UPLEFT", argb(255, 128, 128, 128), x1, y1, x1 + 9, y1 + 9);
	// URRIGHT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_UPRIGHT", argb(255, 128, 128, 128), x2 - 9, y1, x2, y1 + 9);
	// DOWNLEFT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_DOWNLEFT", argb(255, 128, 128, 128), x1, y2 - 9, x1 + 9, y2);
	// DOWNRIGHT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_DOWNRIGHT", argb(255, 128, 128, 128), x2 - 9, y2 - 9, x2, y2);
	// LEFT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_LEFT", argb(255, 128, 128, 128), x1, y1 + 9, x1 + 5, y2 - 9);
	// RIGHT
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_LEFT", argb(255, 128, 128, 128), x2 - 5, y1 + 9, x2, y2 - 9);
	// UP
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_CENTER", argb(255, 128, 128, 128), x1 + 9, y1, x2 - 9, y1 + 5);
	// DOWN
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_CENTER", argb(255, 128, 128, 128), x1 + 9, y2 - 5, x2 - 9, y2);
	
}

void EI_CreateFrameWithBack(string sBackNodeName, string sFrameNodeName, string sBackImage, int x1, int y1, int x2, int y2)
{
	// Back
	if (sBackNodeName != "")
	{
		SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sBackNodeName, 1, "PAPIRUS");
		SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sBackNodeName, 0, sBackImage, argb(255, 128, 128, 128), x1, y1, x2, y2);
	}

	// Frame
	if (sFrameNodeName != "") { EI_CreateFrame(sFrameNodeName, x1, y1, x2, y2); }
}

void EI_CreateTriggerFrame(int iFrameType, int x1, int y1, int x2, int y2)
{
//	switch(iFrameType)
//	{
//		case 1:
//			XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "IMAGECOLLECTION", "TRIGGER_NODE_FRAME", 900);
//			EI_CreateFrame("TRIGGER_NODE_FRAME", x1, y1, x2, y2);
//			SetPictureBlind("TRIGGER_NODE_FRAME", true, argb(255, 75, 75, 75), argb(255, 165, 165, 165), 1.0, 1.0);
//		break;
//		case 2:
//			XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "TRIGGER_NODE_FRAME", 900);
//			SetNewGroupPicture("TRIGGER_NODE_FRAME", "LE_ICONS", "traitframe");
//			SetNodePosition("TRIGGER_NODE_FRAME", x1, y1, x2, y2);
//			SetPictureBlind("TRIGGER_NODE_FRAME", true, argb(255, 75, 75, 75), argb(255, 165, 165, 165), 1.0, 1.0);
//		break;
//		case 3:
//			XI_MakeNode("resource\ini\interfaces\defaultnode.ini", "PICTURE", "TRIGGER_NODE_FRAME", 900);
//			SetNewGroupPicture("TRIGGER_NODE_FRAME", "LE_ICONS", "glow1");
//			SetNodePosition("TRIGGER_NODE_FRAME", x1, y1, x2, y2);
//			SetPictureBlind("TRIGGER_NODE_FRAME", true, argb(255, 75, 75, 75), argb(255, 165, 165, 165), 1.0, 1.0);
//		break;
//	}
}

void EI_DeleteTriggerFrame()
{
	XI_DeleteNode("TRIGGER_NODE_FRAME");
}

// create vertical line with width = 3
void EI_CreateVLine(string sNodeName, int x1, int y1, int y2, int iNumLines, int iWidth)
{
	SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 1, "MAIN_ICONS");
	for (int i=0; i<iNumLines; i++)
	{
		SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_LEFT", argb(255, 128, 128, 128), x1 + i * iWidth, y1, x1 + i * iWidth + 3, y2);
	}
}

// create horizontal line with width = 3
void EI_CreateHLine(string sNodeName, int x1, int y1, int x2, int iNumLines, int iHeight)
{
	SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 1, "MAIN_ICONS");
	for (int i=0; i<iNumLines; i++)
	{
		SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, "BORDER_CENTER", argb(255, 128, 128, 128), x1, y1 + i * iHeight, x2, y1 + i * iHeight + 3);
	}
}

void EI_CreateSubstrate(string sNodeName, string sSubsrateType, int x1, int y1, int x2, int y2)
{
	SendMessage(&GameInterface, "lsls", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 1, "MAIN_ICONS");
	// SUBSTRATE
	SendMessage(&GameInterface, "lslslllll", MSG_INTERFACE_MSG_TO_NODE, sNodeName, 0, sSubsrateType, argb(255, 128, 128, 128), x1, y1, x2, y2);
	EI_CreateHLine(sNodeName, x1,y1-3,x2,1, 4);
}

// значки уведомлений в шапке
void SetAlertMarks(ref chr)
{
	SetNodeUsing("A_INVENTORY",false);
	SetNodeUsing("A_SHIP",false);
	SetNodeUsing("A_QUESTBOOK",false);
	SetNodeUsing("A_ATLAS",false);
	SetNodeUsing("A_ABILITIES",false);
	SetNodeUsing("A_NATIONS",false);
	SetNodeUsing("A_QUEST",false);
	SetNodeUsing("A_INFO",false);
	SetNodeUsing("A_RECIPE",false);

	if(CheckAttribute(chr,"perks.FreePoints_self") || CheckAttribute(chr,"perks.FreePoints_ship"))
	{
		if(!HaveAllPerks(chr, "any")) SetNodeUsing("A_ABILITIES",true);
	}

	bool bNewQuest = CheckQuestInfo();
	bool bNewDocs = CheckNewDocs();
	if(bNewQuest || bNewDocs) SetNodeUsing("A_QUESTBOOK",true);
	if(bNewQuest) SetNodeUsing("A_QUEST",true);
	if(bNewDocs) SetNodeUsing("A_INFO",true);
	if(CheckAlchemyRecipe()) SetNodeUsing("A_RECIPE",true);
}

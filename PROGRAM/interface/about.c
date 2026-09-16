// Авторы, форма про нас
// boal ролики делать не умею, зато умею кодить на скриптах, титры на них

#include "interface\utils\menu_volume.c"

float fNewPos;
float factor = 0;

object aboutState;
aref logoPos;
aref logoBMSPos;
aref logoReconPos;

bool debugControl = false;

string StrTextInit()
{
	string text = GetConvertStr("about", "about.txt");

	return text;
}

void InitInterface(string iniName)
{
	EngineLayersOffOn(true);
	GameInterface.title = "";
	
	SendMessage(&GameInterface, "ls", MSG_INTERFACE_INIT,iniName);
	
	SetEventHandler("InterfaceBreak", "ProcessCancelExit", 0);
	SetEventHandler("exitCancel", "ProcessCancelExit", 0);
	SetEventHandler("My_MoveText", "MoveText", 0);
	SetEventHandler("ievnt_command", "ProcCommand", 0);

	// debug управление
	if (MOD_BETTATESTMODE == "On")
	{
	    debugControl = true;
	}

	int i, k;
	
	int logoLeft, logoTop, logoRight, logoBottom;
	int logoBMSLeft, logoBMSTop, logoBMSRight, logoBMSBottom;
	int logoReconLeft, logoReconTop, logoReconRight, logoReconBottom;

	GetNodePosition("LOGO", &logoLeft, &logoTop, &logoRight, &logoBottom);
	GetNodePosition("BMS", &logoBMSLeft, &logoBMSTop, &logoBMSRight, &logoBMSBottom);
	GetNodePosition("RECON_TEAM", &logoReconLeft, &logoReconTop, &logoReconRight, &logoReconBottom);

	makearef(logoPos, aboutState.logo);
	logoPos.left = logoLeft;
	logoPos.top = logoTop;
	logoPos.right = logoRight;
	logoPos.bottom = logoBottom;

	makearef(logoBMSPos, aboutState.logoBMS);
	logoBMSPos.left = logoBMSLeft;
	logoBMSPos.top = logoBMSTop;
	logoBMSPos.right = logoBMSRight;
	logoBMSPos.bottom = logoBMSBottom;

	makearef(logoReconPos, aboutState.logoRecon);
	logoReconPos.left = logoReconLeft;
	logoReconPos.top = logoReconTop;
	logoReconPos.right = logoReconRight;
	logoReconPos.bottom = logoReconBottom;

//	for (i = 0; i < 8; i++)
//	{
//		SendMessage(&GameInterface, "lsle", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 0, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
//	}

//	SendMessage(&GameInterface, "lsle", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 15, StrTextInit() + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	string text = StrTextInit();
	SendMessage(&GameInterface, "lsle", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 15, text);

//	for (i = 0; i < 3; i++)
//	{
//		SendMessage(&GameInterface, "lsle", MSG_INTERFACE_MSG_TO_NODE, "INFO_TEXT", 0, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
//	}

	PostEvent("My_MoveText", 600);
	MenuVolume_FadeOut(false); // > схему звука не трогаем, её глушит нулевая громкость звуков
	fNewPos = 0;
}

void ProcessCancelExit()
{
	if(CheckAttribute(&InterfaceStates, "showGameMenuOnExit") && sti(InterfaceStates.showGameMenuOnExit) == true)
	{
		MenuVolume_Restore(); // > назад в игровое меню
		IDoExit(RC_INTERFACE_LAUNCH_GAMEMENU);
		return;
	}

	IDoExit(RC_INTERFACE_OPTIONSCREEN_EXIT);
	if(!CheckAttribute(&InterfaceStates, "InstantExit") || sti(InterfaceStates.InstantExit) == false)
	{
		ReturnToMainMenu();
	}
}

void IDoExit(int exitCode)
{
 	DelEventHandler("InterfaceBreak","ProcessCancelExit");
	DelEventHandler("exitCancel","ProcessCancelExit");
	DelEventHandler("My_MoveText","MoveText");
	MenuVolume_Stop();
	DelEventHandler("ievnt_command", "ProcCommand");
    
	interfaceResultCommand = exitCode;
	if(CheckAttribute(&InterfaceStates,"InstantExit") && sti(InterfaceStates.InstantExit) == true)
		EndCancelInterface(true);
	else
		EndCancelInterface(false);
}

void MoveText()
{
	if(fNewPos >= 1)
	{
		ProcessCancelExit();
	}
	else
	{
		factor = 6000; // скорость лого (больше быстрее)
		SetNodePosition("LOGO", sti(logoPos.left), makeint(sti(logoPos.top) - fNewPos * factor),
			sti(logoPos.right), makeint(sti(logoPos.bottom) - fNewPos * factor));
		SetNodePosition("BMS", sti(logoBMSPos.left), makeint(sti(logoBMSPos.top) - fNewPos * factor),
		 	sti(logoBMSPos.right), makeint(sti(logoBMSPos.bottom) - fNewPos * factor));
		SetNodePosition("RECON_TEAM", sti(logoReconPos.left), makeint(sti(logoReconPos.top) - fNewPos * factor),
		 	sti(logoReconPos.right), makeint(sti(logoReconPos.bottom) - fNewPos * factor));

		SendMessage(&GameInterface,"lslf",MSG_INTERFACE_MSG_TO_NODE,"INFO_TEXT", 2, fNewPos);
		PostEvent("My_MoveText", 20);
		fNewPos = fNewPos + 0.0001;
	}
}

void ProcCommand()
{
	if (!debugControl)
		return;

	string comName = GetEventData();
	string nodName = GetEventData();

	float scrollDelta = 0.01;

	switch (comName)
	{
		case "upstep":
			fNewPos = fNewPos - scrollDelta;
			if(fNewPos < 0)
			{
				fNewPos = 0;
			}
		break;

		case "downstep":
			fNewPos = fNewPos + scrollDelta;
			if(fNewPos >= 1)
			{
				fNewPos = 1;
			}
		break;
	}

//	Log_Info("newpos: " + fNewPos);
}
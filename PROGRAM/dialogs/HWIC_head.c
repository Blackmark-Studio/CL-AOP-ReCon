// Маттиас Бек - вице-директор ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = StringFromKey("HWIC_head_1");
			NextDiag.TempNode = "First time";
			// Квест "Остепенившийся пират" -->
			if (CheckAttribute(pchar, "questTemp.PDM_Lesopilka_GVIK") && pchar.questTemp.PDM_Lesopilka_GVIK == "InviteHugo")
			{
				link.l1 = StringFromKey("HWIC_head_2");
				link.l1.go = "PDM_Lesopilka_InviteHugo_1";
			}
			if (CheckAttribute(pchar, "questTemp.PDM_Lesopilka_GVIK") && pchar.questTemp.PDM_Lesopilka_GVIK == "AcceptHugo")
			{
				link.l1 = StringFromKey("HWIC_head_3");
				link.l1.go = "PDM_Lesopilka_AcceptHugo_1";
			}
			// Квест "Остепенившийся пират" <--
			link.l99 = StringFromKey("HWIC_head_4");
			link.l99.go = "exit";
		break;
		
		// Квест "Остепенившийся пират" -->
		case "PDM_Lesopilka_InviteHugo_1":
			dialog.text = StringFromKey("HWIC_head_5");
            link.l1 = StringFromKey("HWIC_head_6");
            link.l1.go = "PDM_Lesopilka_InviteHugo_2";
		break;
		
		case "PDM_Lesopilka_InviteHugo_2":
            dialog.text = StringFromKey("HWIC_head_7");
			link.l1 = StringFromKey("HWIC_head_8", pchar);
            link.l1.go = "PDM_Lesopilka_InviteHugo_3";
        break;

		case "PDM_Lesopilka_InviteHugo_3":
            dialog.text = StringFromKey("HWIC_head_9", pchar.name);
            link.l1 = StringFromKey("HWIC_head_10", GetFullName(NPChar));
            link.l1.go = "exit";
			GiveItem2Character(PChar, "LesopilkaDoc");
			AddDialogExitQuestFunction("PDM_Lesopilka_GVIK_TookDocument");
        break;
		
		case "PDM_Lesopilka_AcceptHugo_1":
			dialog.text = StringFromKey("HWIC_head_11", GetAddress_Form(NPChar), pchar.name);
            link.l1 = StringFromKey("HWIC_head_12");
            link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_Lesopilka_GVIK_HugoAccept");
        break;
		// Квест "Остепенившийся пират" <--
	}
}
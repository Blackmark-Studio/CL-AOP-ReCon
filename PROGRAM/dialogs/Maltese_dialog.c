void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "Maltie_officer":
			NextDiag.TempNode = "Maltie_officer";
			dialog.text = StringFromKey("Maltese_dialog_1", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("Maltese_dialog_2");
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "questTemp.PDM_PJ_SS"))    //Квест "Невыносимая жара"
			{
				link.l1 = StringFromKey("Maltese_dialog_3");
				link.l1.go = "PDM_PJ_SS_1";
			}
		break;

		//******************** Квест "Невыносимая жара" ******************
		case "PDM_PJ_SS_1":
			dialog.text = StringFromKey("Maltese_dialog_4");
			link.l1 = StringFromKey("Maltese_dialog_5", GetFullName(NPChar));
			link.l1.go = "PDM_PJ_SS_2";
			DeleteAttribute(pchar, "questTemp.PDM_PJ_SS");
			DeleteAttribute(pchar, "questTemp.PDM_PJ_KV");
			RemoveLandQuestMark_Main(CharacterFromID("FortFrance_tavernkeeper"), "PDM_Proklyataya_Jara");
			RemoveLandQuestMarkToFantoms_Main("Maltie_officer", "PDM_Proklyataya_Jara");
			AddMoneyToCharacter(pchar, 2500);
			GiveItem2Character(pchar, "blade_maltes");
		break;

		case "PDM_PJ_SS_2":
			DialogExit();
			bDisableFastReload = true;
			chrDisableReloadToLocation = true;
			LAi_SetActorType(pchar);
			DoQuestReloadToLocation("FortFrance_town", "goto", "goto2", "PDM_PJ_Arest_0");
		break;

		//**************************************************************

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;

		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;

		case "Maltie_soldier":
			NextDiag.TempNode = "Maltie_soldier";
			if (LAi_grp_playeralarm > 0)
			{
				dialog.text = NPCharRepPhrase(pchar,
						StringFromKey("Maltese_dialog_9", LinkRandPhrase(
								StringFromKey("Maltese_dialog_6"),
								StringFromKey("Maltese_dialog_7"),
								StringFromKey("Maltese_dialog_8", pchar))),
						StringFromKey("Maltese_dialog_13", LinkRandPhrase(
								StringFromKey("Maltese_dialog_10", pchar),
								StringFromKey("Maltese_dialog_11", pchar),
								StringFromKey("Maltese_dialog_12", pchar))));
				link.l1 = NPCharRepPhrase(pchar,
						StringFromKey("Maltese_dialog_16", RandPhraseSimple(
								StringFromKey("Maltese_dialog_14"),
								StringFromKey("Maltese_dialog_15"))),
						StringFromKey("Maltese_dialog_19", RandPhraseSimple(
								StringFromKey("Maltese_dialog_17"),
								StringFromKey("Maltese_dialog_18"))));
				link.l1.go = "fight";
				break;
			}

			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = StringFromKey("Maltese_dialog_22", RandPhraseSimple(
							StringFromKey("Maltese_dialog_20"),
							StringFromKey("Maltese_dialog_21")));
				link.l1 = StringFromKey("Maltese_dialog_25", RandPhraseSimple(
							StringFromKey("Maltese_dialog_23"),
							StringFromKey("Maltese_dialog_24")));
				link.l1.go = "fight";
			}
			else
			{
				dialog.text = StringFromKey("Maltese_dialog_26", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("Maltese_dialog_27");
				link.l1.go = "exit";
			}
		break;
	}
}

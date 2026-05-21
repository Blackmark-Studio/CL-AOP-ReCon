void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "First time":                            //Автор Sinistra
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Kak_zhe_segodnya_zharko.wav");
			dialog.text = StringFromKey("Proklyataya_Jara_1", pchar);
			link.l1 = StringFromKey("Proklyataya_Jara_2", pchar.name);
			link.l1.go = "Mne_Jarko_1";
			RemoveLandQuestMark_Main(npchar, "PDM_Proklyataya_Jara");
			RemoveMapQuestMark("FortFrance_town", "PDM_Proklyataya_Jara");
		break;

		case "Mne_Jarko_1":
			dialog.text = StringFromKey("Proklyataya_Jara_3");
			link.l1 = StringFromKey("Proklyataya_Jara_4");
			link.l1.go = "Mne_Jarko_2";
			link.l2 = StringFromKey("Proklyataya_Jara_5");
			link.l2.go = "exit";
			npchar.dialog.filename = "Common_Soldier.c";
			npchar.dialog.currentnode = "First time";
			LAi_SetGuardianType(npchar);
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS");
		break;

		case "Mne_Jarko_2":
			dialog.text = StringFromKey("Proklyataya_Jara_6");
			link.l1 = StringFromKey("Proklyataya_Jara_7");
			link.l1.go = "Mne_Jarko_3";
		break;

		case "Mne_Jarko_3":
			dialog.text = StringFromKey("Proklyataya_Jara_8", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Proklyataya_Jara_9");
			link.l1.go = "Mne_Jarko_4";
			link.l2 = StringFromKey("Proklyataya_Jara_10");
			link.l2.go = "exit";
			npchar.dialog.filename = "Common_Soldier.c";
			npchar.dialog.currentnode = "First time";
		break;

		case "Mne_Jarko_4":
			dialog.text = StringFromKey("Proklyataya_Jara_11");
			link.l1 = StringFromKey("Proklyataya_Jara_12");
			link.l1.go = "Mne_Jarko_5";
			DeleteAttribute(npchar, "talker");
		break;

		case "Mne_Jarko_5":
			SetQuestHeader("PDM_Proklyataya_Jara");
			AddQuestRecord("PDM_Proklyataya_Jara", "1");
			DialogExit();
			pchar.questTemp.PDM_PJ_KV = "KupitVino";
			pchar.questTemp.PDM_PJ_SS = "SdatSoldata";
			sld = CharacterFromID("PDM_PJ_Strajnik_1");
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Mne_Jarko_5_EsheRaz";
			AddLandQuestMark_Main(CharacterFromID("FortFrance_tavernkeeper"), "PDM_Proklyataya_Jara");
			AddLandQuestMarkToFantoms_Main("Maltie_officer", "PDM_Proklyataya_Jara", "PDM_Proklyataya_Jara_MaltieOfficer_QuestMarkCondition");
		break;

		case "Mne_Jarko_5_EsheRaz":
			dialog.text = StringFromKey("Proklyataya_Jara_13");
			link.l1 = StringFromKey("Proklyataya_Jara_14", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "Mne_Jarko_5_EsheRaz";
		break;

		case "Prines_Vino_1":
			npchar.dialog.filename = "Common_Soldier.c";
			npchar.dialog.currentnode = "First time";
			dialog.text = StringFromKey("Proklyataya_Jara_15", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Proklyataya_Jara_16");
			link.l1.go = "Prines_Vino_2";
		break;

		case "Prines_Vino_2":
			TakeItemFromCharacter(pchar, "PDM_PJ_Vino");
			dialog.text = StringFromKey("Proklyataya_Jara_17", pchar.name);
			link.l1 = StringFromKey("Proklyataya_Jara_18");
			link.l1.go = "Prines_Vino_Drujba_1";
			link.l2 = StringFromKey("Proklyataya_Jara_19", pchar, GetFullName(CharacterFromID("FortFrance_tavernkeeper")));
			link.l2.go = "Prines_Vino_Obman_1";
		break;

		case "Prines_Vino_Drujba_1":
			dialog.text = StringFromKey("Proklyataya_Jara_20");
			link.l1 = StringFromKey("Proklyataya_Jara_21");
			link.l1.go = "A_Eto_eshe_ne_vse";
			ChangeCharacterReputation(pchar, 3);
		break;

		case "Prines_Vino_Obman_1":
			dialog.text = StringFromKey("Proklyataya_Jara_22");
			link.l1 = StringFromKey("Proklyataya_Jara_23");
			link.l1.go = "Prines_Vino_Obman_2";
			link.l2 = StringFromKey("Proklyataya_Jara_24");
			link.l2.go = "Prines_Vino_Drujba_1";
		break;

		case "Prines_Vino_Obman_2":
			dialog.text = StringFromKey("Proklyataya_Jara_25", GetFullName(CharacterFromID("FortFrance_tavernkeeper")));
			link.l1 = StringFromKey("Proklyataya_Jara_26");
			link.l1.go = "A_Eto_eshe_ne_vse";
			ChangeCharacterReputation(pchar, -3);
			AddMoneyToCharacter(pchar, 1000);
			AddCharacterExpToSkill(pchar, "Commerce", 30);
		break;

		case "A_Eto_eshe_ne_vse":
			DialogExit();
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Ya_Toje_Hochu_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0.0, 0);

			RemoveLandQuestMark_Main(npchar, "PDM_Proklyataya_Jara");
		break;

		case "Ya_Toje_Hochu_1":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Privetstvu_vas_kapitan.wav");
			dialog.text = StringFromKey("Proklyataya_Jara_27", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Proklyataya_Jara_28");
			link.l1.go = "Ya_Toje_Hochu_2";
		break;

		case "Ya_Toje_Hochu_2":
			dialog.text = StringFromKey("Proklyataya_Jara_29");
			link.l1 = StringFromKey("Proklyataya_Jara_30", pchar);
			link.l1.go = "Ya_Toje_Hochu_3";
		break;

		case "Ya_Toje_Hochu_3":
			dialog.text = StringFromKey("Proklyataya_Jara_31");
			link.l1 = StringFromKey("Proklyataya_Jara_32", pchar);
			link.l1.go = "Ya_Toje_Hochu_4";
			link.l2 = StringFromKey("Proklyataya_Jara_33");
			link.l2.go = "Ya_Toje_Hochu_Proval";
		break;

		case "Ya_Toje_Hochu_Proval":
			DialogExit();
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.dialog.filename = "Common_Soldier.c";
			sld.dialog.currentnode = "First time";
			CloseQuestHeader("PDM_Proklyataya_Jara");
		break;

		case "Ya_Toje_Hochu_4":
			dialog.text = StringFromKey("Proklyataya_Jara_34", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Proklyataya_Jara_35");
			link.l1.go = "Ya_Toje_Hochu_5";
		break;

		case "Ya_Toje_Hochu_5":
			DialogExit();
			AddQuestRecord("PDM_Proklyataya_Jara", "3");
			pchar.questTemp.PDM_PJ_KR = "KupitRom";
			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			sld.Dialog.Filename = "Quest\PDM\Proklyataya_Jara.c";
			sld.dialog.currentnode = "Ya_Toje_Hochu_5_EsheRaz";
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.City = "FortFrance";
			AddLandQuestMark_Main(CharacterFromID("FortFrance_tavernkeeper"), "PDM_Proklyataya_Jara");
		break;

		case "Ya_Toje_Hochu_5_EsheRaz":
			dialog.text = StringFromKey("Proklyataya_Jara_36");
			link.l1 = StringFromKey("Proklyataya_Jara_37", pchar);
			link.l1.go = "exit";
			NextDiag.TempNode = "Ya_Toje_Hochu_5_EsheRaz";
		break;

		case "Prines_Rom_1":
			npchar.dialog.filename = "Common_Soldier.c";
			npchar.dialog.currentnode = "First time";
			dialog.text = StringFromKey("Proklyataya_Jara_38");
			link.l1 = StringFromKey("Proklyataya_Jara_39");
			link.l1.go = "Prines_Rom_2";
		break;

		case "Prines_Rom_2":
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			TakeItemFromCharacter(pchar, "PDM_PJ_Rom");
			dialog.text = StringFromKey("Proklyataya_Jara_40", pchar);
			link.l1 = StringFromKey("Proklyataya_Jara_41");
			link.l1.go = "Prines_Rom_3";
		break;

		case "Prines_Rom_3":
			dialog.text = StringFromKey("Proklyataya_Jara_42", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Proklyataya_Jara_43");
			link.l1.go = "Prines_Rom_4";
		break;

		case "Prines_Rom_4":
			DialogExit();

			AddQuestRecord("PDM_Proklyataya_Jara", "5");
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			AddCharacterExpToSkill(pchar, "Sneak", 80);

			sld = CharacterFromID("PDM_PJ_Strajnik_2");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "drunk", "", 1.0);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			sld.City = "FortFrance";

			PChar.quest.PDM_PJ_Protrezvel.win_condition.l1 = "ExitFromLocation";
			PChar.quest.PDM_PJ_Protrezvel.win_condition.l1.location = PChar.location;
			PChar.quest.PDM_PJ_Protrezvel.win_condition = "PDM_PJ_Protrezvel";

			RemoveLandQuestMark_Main(npchar, "PDM_Proklyataya_Jara");
			// Ставим флаг для диалога с Жеромом
			pchar.questTemp.PDM_PJ_KV = "Sangari_Jerome_Talk";

			// Добавляем маркер на тавернщика
			AddLandQuestMark_Main(CharacterFromID("FortFrance_tavernkeeper"), "PDM_Proklyataya_Jara");
		break;

	}
}

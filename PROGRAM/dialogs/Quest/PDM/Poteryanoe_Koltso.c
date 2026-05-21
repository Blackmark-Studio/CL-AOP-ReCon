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
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Old Woman.wav");
			dialog.text = StringFromKey("Poteryanoe_Koltso_1", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Poteryanoe_Koltso_2");
			link.l1.go = "Starshka_1";
			RemoveLandQuestMark_Main(npchar, "PDM_Poteryanoe_Koltso");
			RemoveMapQuestMark("PortPax_town", "PDM_Poteryanoe_Koltso");
		break;

		case "Starshka_1":
			dialog.text = StringFromKey("Poteryanoe_Koltso_3");
			link.l1 = StringFromKey("Poteryanoe_Koltso_4", pchar);
			link.l1.go = "Starshka_2";
		break;

		case "Starshka_2":
			dialog.text = StringFromKey("Poteryanoe_Koltso_5", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Poteryanoe_Koltso_6");
			link.l1.go = "Starshka_3";
		break;

		case "Starshka_3":
			dialog.text = StringFromKey("Poteryanoe_Koltso_7");
			link.l1 = StringFromKey("Poteryanoe_Koltso_8");
			link.l1.go = "Starshka_4";
			NextDiag.TempNode = "Starshka_5";
		break;

		case "Starshka_4":
			SetQuestHeader("PDM_Poteryanoe_Koltso");
			AddQuestRecord("PDM_Poteryanoe_Koltso", "1");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "а"));

			pchar.questTemp.PDM_PK_UznatLichnost = "UznatLichnost";
			AddLandQuestMarkToFantoms_Main("ItemTrader", "PDM_Poteryanoe_Koltso", "PDM_Poteryanoe_Koltso_UznatLichnost_QuestMarkCondition");
			AddLandQuestMark_Main(CharacterFromId("PortPax_tavernkeeper"), "PDM_Poteryanoe_Koltso");
			AddLandQuestMarkToFantoms_Main("Citizen", "PDM_Poteryanoe_Koltso", "PDM_Poteryanoe_Koltso_UznatLichnost_QuestMarkCondition");
			AddLandQuestMarkToFantoms_Main("Commoner", "PDM_Poteryanoe_Koltso", "PDM_Poteryanoe_Koltso_UznatLichnost_QuestMarkCondition");

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "Starshka_5":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Old Woman.wav");
			dialog.text = StringFromKey("Poteryanoe_Koltso_9", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Poteryanoe_Koltso_10", pchar);
			link.l1.go = "exit";
		break;

		case "Francheska":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Francesca.wav");
			dialog.text = StringFromKey("Poteryanoe_Koltso_11", pchar);
			link.l1 = StringFromKey("Poteryanoe_Koltso_12", pchar);
			link.l1.go = "SrazuProKoltso";
			link.l2 = StringFromKey("Poteryanoe_Koltso_13");
			link.l2.go = "Istoria";
			pchar.questTemp.PDM_PK_UvestiNaVerh = true;
			AddLandQuestMark_Main(CharacterFromID("SantoDomingo_Hostess"), "PDM_Poteryanoe_Koltso");
		break;

		case "SrazuProKoltso":
			dialog.text = StringFromKey("Poteryanoe_Koltso_14");
			link.l1 = StringFromKey("Poteryanoe_Koltso_15");
			link.l1.go = "Otstan";
			link.l2 = StringFromKey("Poteryanoe_Koltso_16");
			link.l2.go = "Krik";
			NextDiag.TempNode = "Uhodi";
		break;

		case "Otstan":
			dialog.text = StringFromKey("Poteryanoe_Koltso_17");
			link.l1 = StringFromKey("Poteryanoe_Koltso_18");
			link.l1.go = "exit";
		break;

		case "Krik":
			dialog.text = StringFromKey("Poteryanoe_Koltso_19");
			link.l1 = StringFromKey("Poteryanoe_Koltso_20");
			link.l1.go = "exit";
			ChangeCharacterReputation(pchar, -2);
		break;

		case "Uhodi":
			dialog.text = StringFromKey("Poteryanoe_Koltso_21");
			link.l1 = StringFromKey("Poteryanoe_Koltso_22");
			link.l1.go = "exit";
		break;

		case "Istoria":
			dialog.text = StringFromKey("Poteryanoe_Koltso_23", pchar);
			link.l1 = StringFromKey("Poteryanoe_Koltso_24", pchar);
			link.l1.go = "Istoria_2";
		break;

		case "Istoria_2":
			dialog.text = StringFromKey("Poteryanoe_Koltso_25");
			link.l1 = StringFromKey("Poteryanoe_Koltso_26");
			link.l1.go = "Istoria_3";
		break;

		case "Istoria_3":
			dialog.text = StringFromKey("Poteryanoe_Koltso_27");
			link.l1 = StringFromKey("Poteryanoe_Koltso_28");
			link.l1.go = "Volshebnoe";
			if (GetCharacterSPECIAL(pchar, "Charisma") >= 3) //чисто мем конечно
			{
				link.l2 = StringFromKey("Poteryanoe_Koltso_29");
				link.l2.go = "Obichnoe";
			}
		break;

		case "Obichnoe":
			dialog.text = StringFromKey("Poteryanoe_Koltso_30");
			link.l1 = StringFromKey("Poteryanoe_Koltso_31");
			link.l1.go = "Pomenyt";
			AddCharacterExpToSkill(pchar, "Leadership", 50);
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ChangeCharacterReputation(pchar, -5); //за обман
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			RemoveLandQuestMark_Main(npchar, "PDM_Poteryanoe_Koltso");

			DeleteAttribute(pchar, "questTemp.PDM_PK_UvestiNaVerh");
			RemoveLandQuestMark_Main(CharacterFromID("SantoDomingo_Hostess"), "PDM_Poteryanoe_Koltso");
			GiveItem2Character(PChar, "PDM_PK_Koltso");
			AddQuestRecord("PDM_Poteryanoe_Koltso", "4");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "а"));
		break;

		case "Volshebnoe":
			dialog.text = StringFromKey("Poteryanoe_Koltso_32");
			link.l1 = StringFromKey("Poteryanoe_Koltso_33");
			link.l1.go = "Kupit";

			if (GetCharacterSPECIAL(pchar, "Charisma") >= 4)
			{
				link.l2 = StringFromKey("Poteryanoe_Koltso_72");
				link.l2.go = "Ubedil";
			}
		break;

		case "Ubedil":
			dialog.text = StringFromKey("Poteryanoe_Koltso_30");
			link.l1 = StringFromKey("Poteryanoe_Koltso_31");
			link.l1.go = "Pomenyt";
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			ChangeCharacterReputation(pchar, 5);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			RemoveLandQuestMark_Main(npchar, "PDM_Poteryanoe_Koltso");

			DeleteAttribute(pchar, "questTemp.PDM_PK_UvestiNaVerh");
			RemoveLandQuestMark_Main(CharacterFromID("SantoDomingo_Hostess"), "PDM_Poteryanoe_Koltso");
			GiveItem2Character(PChar, "PDM_PK_Koltso");
			AddQuestRecord("PDM_Poteryanoe_Koltso", "4");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "а"));
		break;

		case "Kupit":
			dialog.text = StringFromKey("Poteryanoe_Koltso_34", pchar);
			link.l1 = StringFromKey("Poteryanoe_Koltso_35");
			link.l1.go = "Kupit_20";
			link.l2 = StringFromKey("Poteryanoe_Koltso_36");
			link.l2.go = "Kupit_20000";
			link.l3 = StringFromKey("Poteryanoe_Koltso_37");
			link.l3.go = "Kupit_20000000";
			link.l4 = StringFromKey("Poteryanoe_Koltso_38", pchar);
			link.l4.go = "exit";
			NextDiag.TempNode = "Popitka_Vtoraya";
		break;

		case "Kupit_20":
			dialog.text = StringFromKey("Poteryanoe_Koltso_39");
			link.l1 = StringFromKey("Poteryanoe_Koltso_40", pchar);
			link.l1.go = "Pomenyt";
			AddMoneyToCharacter(pchar, -20);
			NextDiag.TempNode = "UNasKoltso";

			DeleteAttribute(pchar, "questTemp.PDM_PK_UvestiNaVerh");
			RemoveLandQuestMark_Main(CharacterFromID("SantoDomingo_Hostess"), "PDM_Poteryanoe_Koltso");
			GiveItem2Character(PChar, "PDM_PK_Koltso");
			AddQuestRecord("PDM_Poteryanoe_Koltso", "4");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "а"));
		break;

		case "Kupit_20000":
			if (sti(pchar.Money) >= 20000)
			{
				dialog.text = StringFromKey("Poteryanoe_Koltso_41");
				link.l1 = StringFromKey("Poteryanoe_Koltso_42");
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				dialog.text = "";
				link.l1 = StringFromKey("Poteryanoe_Koltso_43");
				link.l1.go = "exit";
			}
		break;

		case "Kupit_20000000":
			if (sti(pchar.Money) >= 20000000)
			{
				dialog.text = StringFromKey("Poteryanoe_Koltso_44");
				link.l1 = StringFromKey("Poteryanoe_Koltso_45");
				link.l1.go = "exit";
				ChangeCharacterReputation(pchar, -1);
			}
			else
			{
				dialog.text = "";
				link.l1 = StringFromKey("Poteryanoe_Koltso_46");
				link.l1.go = "exit";
			}
		break;

		case "Popitka_Vtoraya":
			dialog.text = StringFromKey("Poteryanoe_Koltso_47");
			link.l1 = StringFromKey("Poteryanoe_Koltso_48", pchar);
			link.l1.go = "Popitka_Vtoraya_2";
		break;

		case "Popitka_Vtoraya_2":
			dialog.text = StringFromKey("Poteryanoe_Koltso_49", pchar);
			link.l1 = StringFromKey("Poteryanoe_Koltso_50");
			link.l1.go = "Kupit_20";
			link.l2 = StringFromKey("Poteryanoe_Koltso_51");
			link.l2.go = "Kupit_20000";
			link.l3 = StringFromKey("Poteryanoe_Koltso_52");
			link.l3.go = "Kupit_20000000";
			link.l4 = StringFromKey("Poteryanoe_Koltso_53", pchar);
			link.l4.go = "exit";
		break;

		case "UNasKoltso":
			dialog.text = StringFromKey("Poteryanoe_Koltso_54", pchar);
			link.l1 = StringFromKey("Poteryanoe_Koltso_55", pchar);
			link.l1.go = "UNasKoltso_2";
			link.l2 = StringFromKey("Poteryanoe_Koltso_56");
			link.l2.go = "UNasKoltso_3";
		break;

		case "UNasKoltso_2":
			dialog.text = StringFromKey("Poteryanoe_Koltso_57", pchar);
			link.l1 = StringFromKey("Poteryanoe_Koltso_58", pchar);
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;

		case "UNasKoltso_3":
			dialog.text = StringFromKey("Poteryanoe_Koltso_59");
			link.l1 = StringFromKey("Poteryanoe_Koltso_60");
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			RemoveLandQuestMark_Main(npchar, "PDM_Poteryanoe_Koltso");
		break;

		case "Pomenyt":
			RemoveLandQuestMark_Main(npchar, "PDM_Poteryanoe_Koltso");

			sld = CharacterFromID("Josephine_Lodet");
			sld.dialog.currentnode = "Konets";
			AddLandQuestMark_Main(sld, "PDM_Poteryanoe_Koltso");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NaVerhuSFrancheska":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Francesca.wav");
			dialog.text = StringFromKey("Poteryanoe_Koltso_61");
			link.l1 = StringFromKey("Poteryanoe_Koltso_62");
			link.l1.go = "UbitEE";
			link.l2 = StringFromKey("Poteryanoe_Koltso_63");
			link.l2.go = "TrahEE";
			npchar.lifeday = 0;
			RemoveLandQuestMark_Main(npchar, "PDM_Poteryanoe_Koltso");
		break;

		case "TrahEE":
			AddDialogExitQuest("PlaySex_1");
			GiveItem2Character(pchar, "PDM_PK_Koltso");
			chrDisableReloadToLocation = false;
			sld = CharacterFromID("Josephine_Lodet");
			sld.dialog.currentnode = "Konets";
			AddLandQuestMark_Main(sld, "PDM_Poteryanoe_Koltso");
			sld = CharacterFromID("PDM_PK_Francheska");
			sld.dialog.currentnode = "PosleTraha";

			AddCharacterExpToSkill(pchar, "Sneak", 300);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
			AddCharacterExpToSkill(pchar, "Fortune", 150);
			AddCharacterHealth(pchar, 10);
			ChangeCharacterReputation(pchar, -2);

			AddQuestRecord("PDM_Poteryanoe_Koltso", "5");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "а"));
			DialogExit();
		break;

		case "PosleTraha":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Francesca.wav");
			dialog.text = StringFromKey("Poteryanoe_Koltso_64", pchar);
			link.l1 = StringFromKey("Poteryanoe_Koltso_65");
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
		break;

		case "UbitEE":
			LAi_LocationFightDisable(loadedLocation, false);
			Lai_SetPlayerType(pchar);
			LAi_SetFightMode(pchar, true);

			sld = CharacterFromID("PDM_PK_Francheska");
			LAi_SetHP(sld, 20.0, 20.0);
			LAi_SetImmortal(sld, false);
			sld.SaveItemsForDead = true;
			RemoveAllCharacterItems(sld, true);
			GiveItem2Character(sld, "PDM_PK_Koltso");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "afraid", "", 4.5);

			PChar.quest.PDM_PK_Ubita.win_condition.l1 = "item";
			PChar.quest.PDM_PK_Ubita.win_condition.l1.item = "PDM_PK_Koltso";
			PChar.quest.PDM_PK_Ubita.win_condition = "PDM_PK_Ubita";

			DialogExit();
		break;

		case "Konets":
			PlayVoice("Voice\" + VoiceGetLanguage() + "\PDM\Josephine Lodet.wav");
			dialog.text = StringFromKey("Poteryanoe_Koltso_66", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Poteryanoe_Koltso_67", pchar);
			link.l1.go = "Konets_2";
		break;

		case "Konets_2":
			TakeItemFromCharacter(pchar, "PDM_PK_Koltso");
			dialog.text = StringFromKey("Poteryanoe_Koltso_68");
			link.l1 = StringFromKey("Poteryanoe_Koltso_69", pchar);
			link.l1.go = "Konets_3";
		break;

		case "Konets_3":
			dialog.text = StringFromKey("Poteryanoe_Koltso_70", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Poteryanoe_Koltso_71");
			link.l1.go = "Nagrada";
			AddMoneyToCharacter(pchar, 5735);
			TakeNItems(PChar, "jewelry7", 2);
			TakeNItems(PChar, "jewelry10", 1);
			TakeNItems(PChar, "jewelry13", 1);
			TakeNItems(PChar, "jewelry14", 2);
			TakeNItems(PChar, "jewelry15", 1);
			TakeNItems(PChar, "jewelry18", 2);

			AddCharacterExpToSkill(pchar, "Sailing", 400);
			AddCharacterExpToSkill(pchar, "Sneak", 400);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			ChangeCharacterReputation(pchar, 15);
			ChangeCharacterNationReputation(pchar, FRANCE, 7);
		break;

		case "Nagrada":
			AddQuestRecord("PDM_Poteryanoe_Koltso", "6");
			AddQuestUserData("PDM_Poteryanoe_Koltso", "sSex", GetSexPhrase("", "а"));
			CloseQuestHeader("PDM_Poteryanoe_Koltso");
			LAi_CharacterDisableDialog(npchar);
			//sld = CharacterFromID("Josephine_Lodet");
			//sld.dialog.filename   = "Common_Citizen.c";
			//sld.dialog.currentnode = "First Time";
			npchar.lifeday = 0;
			RemoveLandQuestMark_Main(npchar, "PDM_Poteryanoe_Koltso");
			DialogExit();
			Achievment_Set(ACH_Poteryannoe_koltso);
		break;
	}
}

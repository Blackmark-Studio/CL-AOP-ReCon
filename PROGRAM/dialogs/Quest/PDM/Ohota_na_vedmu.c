
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

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

		case "First_time":
			dialog.text = StringFromKey("Ohota_na_vedmu_1", pchar);
			link.l1 = StringFromKey("Ohota_na_vedmu_2");
			link.l1.go = "Bartolom";
			link.l2 = StringFromKey("Ohota_na_vedmu_3");
			link.l2.go = "exit";
			NextDiag.TempNode = "First_time";
		break;

		case "Bartolom":
			dialog.text = StringFromKey("Ohota_na_vedmu_4");
			link.l1 = StringFromKey("Ohota_na_vedmu_5");
			link.l1.go = "PoraVTavernu";
		break;

		case "PoraVTavernu":
			SetQuestHeader("PDM_Ohota_na_vedmu");
			AddQuestRecord("PDM_Ohota_na_vedmu", "1");
			if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			sld = CharacterFromID("PDM_secretary");
			sld.location = "None";
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3_back", "", "", "", "", -1);
			RemoveLandQuestmark_Main(sld, "PDM_Ohota_na_vedmu");

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Carla", "Witch", "woman", "towngirl", 10, SPAIN, -1, false));
			sld.name = FindPersonalName("PDM_ONV_Carla_name");
			sld.lastname = FindPersonalName("PDM_ONV_Carla_lastname");
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "First_Carla_1";
			sld.city = "Beliz";
			LAi_SetWaitressType(sld);
			ChangeCharacterAddressGroup(sld, "Beliz_tavern", "waitress", "stay2");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark_Main(sld, "PDM_Ohota_na_vedmu");
			
			// sld = CharacterFromID("Beliz_waitress");
			// sld.model	= "girl_6";			

			DialogExit();
		break;

		case "First_Carla_1":
			dialog.text = StringFromKey("Ohota_na_vedmu_6", pchar);
			link.l1 = StringFromKey("Ohota_na_vedmu_7", pchar.name);
			link.l1.go = "First_Carla_2";
		break;

		case "First_Carla_2":
			dialog.text = StringFromKey("Ohota_na_vedmu_8", pchar);
			link.l1 = StringFromKey("Ohota_na_vedmu_9");
			link.l1.go = "First_Carla_Uhodit";
		break;

		case "First_Carla_Uhodit":
			AddQuestRecord("PDM_Ohota_na_vedmu", "2");
			if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			LocatorReloadEnterDisable("Beliz_town", "reload3_back", true);
			LocatorReloadEnterDisable("Beliz_town", "reloadR1", true);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload1", true);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload2", true);
			LocatorReloadEnterDisable("Beliz_TownhallRoom", "reload3", true);
			LocatorReloadEnterDisable("Beliz_townhall", "reload2", true);
			LocatorReloadEnterDisable("Beliz_townhall", "reload1_back", true);

			sld = CharacterFromID("PDM_ONV_Carla");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "", "", "", "", -1);
			sld.location = "None";
			RemoveLandQuestmark_Main(sld, "PDM_Ohota_na_vedmu");

			sld = GetCharacter(NPC_GenerateCharacter("PDM_ONV_Guard", "guard_spa_4", "man", "man", 100, SPAIN, -1, true));
			sld.city = "Beliz";
			LAi_SetImmortal(sld, true);
			ChangeCharacterAddressGroup(sld, "Beliz_town", "reload", "reload3_back");
			LAi_SetGuardianType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			sld.dialog.filename   = "Quest\PDM\Ohota_na_vedmu.c";
			sld.dialog.currentnode   = "OfficerGuard";
			AddLandQuestMark_Main(sld, "PDM_Ohota_na_vedmu");
			
			PChar.quest.PDM_ONV_InRoom.win_condition.l1 = "location";
			PChar.quest.PDM_ONV_InRoom.win_condition.l1.location = "Beliz_TownhallRoom";
			PChar.quest.PDM_ONV_InRoom.function = "PDM_ONV_InRoom";

			DialogExit();
		break;

		case "OfficerGuard":
			dialog.text = StringFromKey("Ohota_na_vedmu_10", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Ohota_na_vedmu_11");
			if (!CheckAttribute(npchar, "talked")) link.l1.go = "OfficerGuard_Cod";
			else link.l1.go = "exit";
			NextDiag.TempNode = "OfficerGuard";
			npchar.talked = true;
		break;

		case "OfficerGuard_Cod":
			AddQuestRecord("PDM_Ohota_na_vedmu", "3");
			if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
			LocatorReloadEnterDisable("Beliz_town", "reloadR1", false);
			RemoveLandQuestmark_Main(npchar, "PDM_Ohota_na_vedmu");
			QuestPointerToLoc("Beliz_town", "reload", "reloadR1");
			
			sld = &Locations[FindLocation("Beliz_TownhallRoom")];
			sld.locators_radius.goto.goto9 = 1.5;
			sld.id.label = "House";

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "SoldatInTownHall":
			dialog.text = StringFromKey("Ohota_na_vedmu_12", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("Ohota_na_vedmu_13");
			link.l1.go = "exit";
			NextDiag.TempNode = "SoldatInTownHall";
		break;

		case "DialogWithHuber":
			dialog.text = StringFromKey("Ohota_na_vedmu_14");
			link.l1 = StringFromKey("Ohota_na_vedmu_15", pchar, GetFullName(pchar));
			link.l1.go = "DialogWithHuber_2";
			RemoveLandQuestmark_Main(npchar, "PDM_Ohota_na_vedmu");
		break;

		case "DialogWithHuber_2":
			dialog.text = StringFromKey("Ohota_na_vedmu_16");
			link.l1 = StringFromKey("Ohota_na_vedmu_17");
			link.l1.go = "DialogWithHuber_3";
		break;

		case "DialogWithHuber_3":
			dialog.text = StringFromKey("Ohota_na_vedmu_18");
			link.l1 = "...";
			link.l1.go = "DialogWithHuber_4";
			sld = &characters[GetCharacterIndex("PDM_secretary")];
			sld.location = "none";
		break;

		case "DialogWithHuber_4":
			dialog.text = StringFromKey("Ohota_na_vedmu_19");
			link.l1 = StringFromKey("Ohota_na_vedmu_20");
			link.l1.go = "DialogWithHuber_5";
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("PDM_ONV_SoldatGub_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
				sld.lifeday = 0;
				sld.location = "None";
			}
		break;

		case "DialogWithHuber_5":
			dialog.text = StringFromKey("Ohota_na_vedmu_21");
			link.l1 = StringFromKey("Ohota_na_vedmu_22");
			link.l1.go = "DialogWithHuber_6";
		break;

		case "DialogWithHuber_6":
			dialog.text = StringFromKey("Ohota_na_vedmu_23");
			link.l1 = StringFromKey("Ohota_na_vedmu_24");
			link.l1.go = "DialogWithHuber_6_1";
		break;

		case "DialogWithHuber_6_1":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "officers", "reload1_2", "", -1);
			DoQuestFunctionDelay("PDM_ONV_ReadyToWork", 2.6);
		break;

		case "DialogWithHuber_7":
			dialog.text = StringFromKey("Ohota_na_vedmu_25", pchar.name);
			link.l1 = StringFromKey("Ohota_na_vedmu_26");
			link.l1.go = "DialogWithHuber_Agree";
			link.l2 = StringFromKey("Ohota_na_vedmu_27");
			link.l2.go = "DialogWithHuber_Refuce";
		break;
		
		case "DialogWithHuber_Refuce":
			dialog.text = StringFromKey("Ohota_na_vedmu_28");
			link.l1 = StringFromKey("Ohota_na_vedmu_29");
			link.l1.go = "DialogWithHuber_Refuce_2";
		break;
		
		case "DialogWithHuber_Refuce_2":
			DialogExit();
			NextDiag.CurrentNode = "DialogWithHuber_Again";
			AddDialogExitQuestFunction("PDM_ONV_FreeMove");
			
			CloseQuestHeader("PDM_Ohota_na_vedmu");
		break;

		case "DialogWithHuber_Agree":
			DialogExit();
			NextDiag.CurrentNode = "DialogWithHuber_Again";
			AddDialogExitQuestFunction("PDM_ONV_FreeMove");
			
			pchar.questTemp.PDM_ONV_Detectiv_Tavern_NET = true;
			AddLandQuestMark_Main(CharacterFromID("Beliz_tavernkeeper"), "PDM_Ohota_na_vedmu");
			
			AddQuestRecord("PDM_Ohota_na_vedmu", "5");
			if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex1", GetSexPhrase("ся","ась"));
			if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex2", GetSexPhrase("ен","на"));
		break;
		
		case "DialogWithHuber_Again":
			dialog.text = StringFromKey("Ohota_na_vedmu_30");
			link.l1 = StringFromKey("Ohota_na_vedmu_31");
			link.l1.go = "exit";
			NextDiag.TempNode = "DialogWithHuber_Again";
		break;

		case "DialogWithSilino_1":
			dialog.text = StringFromKey("Ohota_na_vedmu_32", pchar);
			link.l1 = StringFromKey("Ohota_na_vedmu_33", pchar);
			link.l1.go = "DialogWithSilino_2";
			PlayVoice("Kopcapkz\Voices\PDM\Gavrila Dubinin.wav");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_PortoBello");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_SanJuan");
			DeleteAttribute(pchar, "questTemp.PDM_ONV_Maracaibo");
			RemoveLandQuestmark_Main(npchar, "PDM_Ohota_na_vedmu");
		break;

		case "DialogWithSilino_2":
			dialog.text = StringFromKey("Ohota_na_vedmu_34", pchar);
			link.l1 = StringFromKey("Ohota_na_vedmu_35");
			link.l1.go = "DialogWithSilino_3";
		break;

		case "DialogWithSilino_3":
			ChangeCharacterAddressGroup(pchar, PChar.location, "sit", "sit_front2");
			LAi_SetSitType(pchar);
			LAi_SetSitType(npchar);
			locCameraTarget(PChar);
            locCameraFollow();
			dialog.text = StringFromKey("Ohota_na_vedmu_36");
			link.l1 = StringFromKey("Ohota_na_vedmu_37");
			link.l1.go = "DialogWithSilino_4";
		break;

		case "DialogWithSilino_4":
			dialog.text = StringFromKey("Ohota_na_vedmu_38");
			link.l1 = StringFromKey("Ohota_na_vedmu_39");
			link.l1.go = "DialogWithSilino_5";
		break;

		case "DialogWithSilino_5":
			dialog.text = StringFromKey("Ohota_na_vedmu_40");
			link.l1 = StringFromKey("Ohota_na_vedmu_41");
			link.l1.go = "exit";
			NextDiag.TempNode = "DialogWithSilino_Again";
			AddDialogExitQuestFunction("PDM_ONW_RoadToSantiago");
		break;

		case "DialogWithSilino_Again":
			dialog.text = StringFromKey("Ohota_na_vedmu_42");
			link.l1 = StringFromKey("Ohota_na_vedmu_43");
			link.l1.go = "exit";
			NextDiag.TempNode = "DialogWithSilino_Again";
		break;

		case "Carla_Final_1":
			dialog.text = StringFromKey("Ohota_na_vedmu_44");
			link.l1 = StringFromKey("Ohota_na_vedmu_45");
			link.l1.go = "Carla_Final_2";
			RemoveLandQuestmark_Main(npchar, "PDM_Ohota_na_vedmu");
		break;

		case "Carla_Final_2":
			dialog.text = StringFromKey("Ohota_na_vedmu_46");
			link.l1 = StringFromKey("Ohota_na_vedmu_47");
			link.l1.go = "Carla_Final_5";
			link.l2 = StringFromKey("Ohota_na_vedmu_48");
			link.l2.go = "NaKoster_2";
		break;

		case "Carla_Final_5":
			dialog.text = StringFromKey("Ohota_na_vedmu_49");
			link.l1 = StringFromKey("Ohota_na_vedmu_50");
			link.l1.go = "Carla_Final_6";
		break;

		case "Carla_Final_6":
			dialog.text = StringFromKey("Ohota_na_vedmu_51");
			link.l1 = StringFromKey("Ohota_na_vedmu_52");
			link.l1.go = "Carla_Final_7";
		break;

		case "Carla_Final_7":
			dialog.text = StringFromKey("Ohota_na_vedmu_53");
			link.l1 = StringFromKey("Ohota_na_vedmu_54");
			link.l1.go = "Carla_Final_8";
		break;

		case "Carla_Final_8":
			dialog.text = StringFromKey("Ohota_na_vedmu_55");
			link.l1 = StringFromKey("Ohota_na_vedmu_56");
			link.l1.go = "Carla_Final_10";
		break;

		case "Carla_Final_10":
			dialog.text = StringFromKey("Ohota_na_vedmu_57");
			link.l1 = StringFromKey("Ohota_na_vedmu_58");
			link.l1.go = "NaKoster_2";
			link.l2 = StringFromKey("Ohota_na_vedmu_59");
			link.l2.go = "Carla_Final_11";
		break;

		case "Carla_Final_11":
			dialog.text = StringFromKey("Ohota_na_vedmu_60", pchar);
			link.l1 = "";
			link.l1.go = "Carla_Final_12";
		break;

		case "NaKoster_2":
			dialog.text = StringFromKey("Ohota_na_vedmu_61", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Ohota_na_vedmu_62");
			link.l1.go = "NaKoster_COD";
			NextDiag.TempNode = "NaKoster_Again";
		break;

		case "Carla_Final_12":
			dialog.text = StringFromKey("Ohota_na_vedmu_63");
			link.l1 = StringFromKey("Ohota_na_vedmu_64");
			link.l1.go = "Dobro_Final";
		break;

		case "Dobro_Final":
			DialogExit();
			NextDiag.CurrentNode = "Carla_Final_Again";
			
			npchar.lifeday = 0;
			AddQuestRecord("PDM_Ohota_na_vedmu", "12");
			if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));
			CloseQuestHeader("PDM_Ohota_na_vedmu");
			SetCharacterPerk(pchar, "WitchCharm");
			ChangeCharacterReputation(pchar, 3);
			AddCharacterExpToSkill(pchar, "Fortune", 300);
			RemoveMapQuestMark("Beliz_town", "PDM_Ohota_na_vedmu");
			pchar.questTemp.PDM_ONW_Completed = "Witch";
			Achievment_Set(ACH_Ohota_na_vedmu);
		break;

		case "Carla_Final_Again":
			dialog.text = StringFromKey("Ohota_na_vedmu_65", pchar, GetAddress_Form(NPChar));
			link.l1 = StringFromKey("Ohota_na_vedmu_66");
			link.l1.go = "exit";
			NextDiag.TempNode = "Carla_Final_Again";
		break;

		case "NaKoster_COD":
			pchar.questTemp.PDM_ONV_OhotaNaVedmu = true;
			QuestPointerToLoc("Santiago_town", "reload", "basement1");
			AddLandQuestmark_Main(CharacterFromID("Santiago_Inquisitor"), "PDM_Ohota_na_vedmu");

			AddQuestRecord("PDM_Ohota_na_vedmu", "13");
			if (LanguageGetLanguage() == "russian") AddQuestUserData("PDM_Ohota_na_vedmu", "sSex", GetSexPhrase("","а"));

			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		case "NaKoster_Again":
			dialog.text = StringFromKey("Ohota_na_vedmu_67");
			link.l1 = StringFromKey("Ohota_na_vedmu_68");
			link.l1.go = "exit";
			NextDiag.TempNode = "NaKoster_Again";
		break;

		case "Inqizitor_1":
			dialog.text = StringFromKey("Ohota_na_vedmu_69");
			link.l1 = "...";
			link.l1.go = "Inqizitor_2";
		break;

		case "Inqizitor_2":
			dialog.text = StringFromKey("Ohota_na_vedmu_70");
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("PDM_ONW_Kino_6");
		break;
		}
}

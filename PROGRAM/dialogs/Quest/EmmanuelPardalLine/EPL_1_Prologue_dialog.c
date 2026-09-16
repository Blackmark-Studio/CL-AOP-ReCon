void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	ref _location;
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
		
////////////////////////////////////////////////////////////////////////////////////////////////
// Эммануэль Пардаль: "Пролог - Мечты сбываются"			Авторы: Nikk и Sinistra
////////////////////////////////////////////////////////////////////////////////////////////////

		case "First time":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_1");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_2");
			link.l1.go = "exit";
		break;
		
		case "Rebekka_v_komnate_1":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_ellipsis");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_3");
			link.l1.go = "Rebekka_v_komnate_2";
			locCameraFromToPos(-3.03, 3.22, 10.47, true, 0.74, 1.05, 12.12);
		break;
		
		case "Rebekka_v_komnate_2":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_4");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_5");
			link.l1.go = "Rebekka_v_komnate_3";
		break;
		
		case "Rebekka_v_komnate_3":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_6");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_7");
			link.l1.go = "Rebekka_v_komnate_4";
		break;
		
		case "Rebekka_v_komnate_4":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_8");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_9");
			link.l1.go = "Rebekka_v_komnate_5";
		break;
		
		case "Rebekka_v_komnate_5":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_10");
			link.l1 = "";
			link.l1.go = "Rebekka_v_komnate_5_1";
			locCameraFromToPos(-1.46, 3.07, 10.95, true, 1.14, 1.24, 11.98);
		break;
		
		case "Rebekka_v_komnate_5_1":
			dialog.text = "";
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_11");
			link.l1.go = "Rebekka_v_komnate_6";
			locCameraFromToPos(-0.68, 3.28, 10.41, true, -2.39, 1.30, 11.68);
		break;
		
		case "Rebekka_v_komnate_6":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_12", pchar.name);
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_13", pchar.lastname, FindPersonalName("Remedios_lastname"));
			link.l1.go = "Rebekka_v_komnate_7";
			locCameraFromToPos(-3.03, 3.22, 10.47, true, 0.74, 1.05, 12.12);
		break;
		
		case "Rebekka_v_komnate_7":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_14");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_15");
			link.l1.go = "Rebekka_v_komnate_8";
		break;
		
		case "Rebekka_v_komnate_8":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_16");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_17");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_SettingHero");
		break;
		
		case "LaVegaIspanski_Gubernator":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_18", FindPersonalName("Remedios_lastname"));
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_19");
			link.l1.go = "LaVegaIspanski_Gubernator_2";
		break;
		
		case "LaVegaIspanski_Gubernator_2":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_20");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_21");
			link.l1.go = "exit";
			NextDiag.TempNode = "LaVegaIspanski_Gubernator_3";
		break;
		
		case "LaVegaIspanski_Gubernator_3":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_22");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_23");
			link.l1.go = "exit";
			NextDiag.TempNode = "LaVegaIspanski_Gubernator_3";
		break;
		
		case "Torgovets_1":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_24");
			link.l1 = "";
			link.l1.go = "Torgovets_2";
			locCameraFromToPos(-44.56, 3.68, 30.93, true, -47.10, 0.75, 27.92);
		break;
		
		case "Torgovets_2":
			DialogExit();
			StartInstantDialog("EPL_SofiaPiedad", "Torgovets_3", "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c");
			locCameraSleep(true);
		break;
		
		case "Torgovets_3":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_25");
			link.l1 = "";
			link.l1.go = "Torgovets_4";
		break;
		
		case "Torgovets_4":
			DialogExit();
			StartInstantDialog("EPL_Kotes", "Torgovets_5", "Quest\EmmanuelPardalLine\EPL_1_Prologue_dialog.c");
		break;
		
		case "Torgovets_5":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_26");
			link.l1 = "";
			link.l1.go = "Torgovets_6_1";
		break;
		
		case "Torgovets_6_1":
			DialogExit();
			locCameraSleep(false);
			locCameraFromToPos(-40.24, 3.37, 26.18, true, -45.28, 0.97, 29.50);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "merchant", "mrcActive3", "", -1);
			DoQuestFunctionDelay("EPL_Torgovets_6_2", 1.0);
		break;
		
		case "Torgovets_6_3":
			dialog.text = "";
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_27");
			link.l1.go = "Torgovets_7";
			sld = CharacterFromID("EPL_Kotes");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = CharacterFromID("EPL_SofiaPiedad");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "Torgovets_7":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_28", pchar.name);
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_29");
			link.l1.go = "Torgovets_8";
			sld = CharacterFromID("EPL_Kotes");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			sld = CharacterFromID("EPL_SofiaPiedad");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
		break;
		
		case "Torgovets_8":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_30");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_31");
			link.l1.go = "Torgovets_9";
		break;
		
		case "Torgovets_9":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_32");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_33");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_KotesRun");
			locCameraSleep(true);
		break;
		
		case "Torgovets_10":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_34");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_35");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_Draka_s_Kotesom");
		break;
		
		case "Rebekka_posle_draki":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_36");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_37");
			link.l1.go = "Rebekka_posle_draki_2";
			
			sld = characterFromId("EPL_Kotes");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, pchar);
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
		break;
		
		case "Rebekka_posle_draki_2":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_38");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_39");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Rebekka_posle_draki");
		break;
		
		case "Sofia_1":
			dialog.text = "";
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_40");
			link.l1.go = "Sofia_2";
			RemoveLandQuestmark_Main(npchar, "EPL_Prologue");
		break;
		
		case "Sofia_2":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_41");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_42", pchar.name, FindPersonalName("Remedios_lastname"));
			link.l1.go = "Sofia_3";
		break;
		
		case "Sofia_3":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_43");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_44");
			link.l1.go = "Sofia_4";
		break;
		
		case "Sofia_4":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_45");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_46");
			link.l1.go = "Sofia_5";
		break;
		
		case "Sofia_5":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_47");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_48");
			link.l1.go = "Sofia_6";
		break;
		
		case "Sofia_6":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_49");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_50");
			link.l1.go = "Sofia_7";
		break;
		
		case "Sofia_7":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_51");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_52");
			link.l1.go = "Sofia_8";
		break;
		
		case "Sofia_8":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_53");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_54");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_SofiaDlgExit");
		break;
		
		case "Rebekka_v_grote_1":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_55", pchar.name);
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_56");
			link.l1.go = "Rebekka_v_grote_2";
			locCameraFromToPos(3.07, 2.91, -4.51, true, 2.48, 0.13, 0.16);
		break;
		
		case "Rebekka_v_grote_2":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_57");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_58");
			link.l1.go = "Rebekka_v_grote_3";
			locCameraSleep(true);
		break;
		
		case "Rebekka_v_grote_3":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_59");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_60");
			link.l1.go = "Rebekka_v_grote_4";
		break;
		
		case "Rebekka_v_grote_4":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_61");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_62");
			link.l1.go = "Rebekka_v_grote_5";
		break;
		
		case "Rebekka_v_grote_5":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_63");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_64");
			link.l1.go = "Rebekka_v_grote_6";
		break;
		
		case "Rebekka_v_grote_6":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_65");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_66");
			link.l1.go = "Rebekka_v_grote_7";
		break;
		
		case "Rebekka_v_grote_7":
			DialogExit();
			
			LAi_SetActorType(pchar);
			DoQuestFunctionDelay("EPL_Strelba_is_pushki", 1.3);
		break;
		
		case "Rebekka_v_grote_8":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_67");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_68");
			link.l1.go = "Rebekka_v_grote_9";
		break;
		
		case "Rebekka_v_grote_9":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_69");
			link.l1 = "";
			link.l1.go = "Rebekka_v_grote_10";
		break;
		
		case "Rebekka_v_grote_10":
			DialogExit();
			
			LAi_SetActorType(pchar);
			DoQuestFunctionDelay("EPL_Strelba_is_pushki_4", 1.3);
		break;
		
		case "Rebekka_v_grote_11":
			dialog.text = "";
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_70");
			link.l1.go = "Rebekka_v_grote_12";
		break;
		
		case "Rebekka_v_grote_12":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_71");
			link.l1 = "";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_Rebekka_v_grote_DlgExit");
		break;
		
		case "Pirate_v_grote_1":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_73");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_74");
			link.l1.go = "Pirate_v_grote_2";
		break;
		
		case "Pirate_v_grote_2":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_75");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_76");
			link.l1.go = "Pirate_v_grote_3";
		break;
		
		case "Pirate_v_grote_3":
			DialogExit();
			EndQuestMovie();
			LAi_SetPlayerType(pchar);
			
			sld = characterFromId("EPL_Rebekka");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			
			LAi_SetFightMode(pchar, true);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("EPL_Piraty_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheckFunction("EnemyFight", "EPL_Pobeda_v_grote");
			DoQuestFunctionDelay("MakeQuestAutoSaveDelay", 1.0);
		break;
		
		case "Stoim_na_pirse":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_77", pchar.name);
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_78");
			link.l1.go = "Stoim_na_pirse_2";
			RemoveLandQuestmark_Main(npchar, "EPL_Prologue");
		break;
		
		case "Stoim_na_pirse_2":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_79");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_80");
			link.l1.go = "Stoim_na_pirse_3";
		break;
		
		case "Stoim_na_pirse_3":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_81");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_82");
			link.l1.go = "Stoim_na_pirse_4";
		break;
		
		case "Stoim_na_pirse_4":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_83");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_84");
			link.l1.go = "Stoim_na_pirse_5";
		break;
		
		case "Stoim_na_pirse_5":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_85");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_86");
			link.l1.go = "Stoim_na_pirse_6";
		break;
		
		case "Stoim_na_pirse_6":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_87");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_88");
			link.l1.go = "Stoim_na_pirse_7";
		break;
		
		case "Stoim_na_pirse_7":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_89");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_90");
			link.l1.go = "Stoim_na_pirse_8";
		break;
		
		case "Stoim_na_pirse_8":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_91");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_92");
			link.l1.go = "Stoim_na_pirse_9";
		break;
		
		case "Stoim_na_pirse_9":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_93");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_94");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_CheckFort");
		break;
		
		case "EPL_Hopkins_1":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_97");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_98");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "EPL_Prologue");
			AddDialogExitQuestFunction("EPL_SandroDialog");
		break;
		
		case "EPL_Sandro_1":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_99");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_100");
			link.l1.go = "EPL_Sandro_2";
		break;
		
		case "EPL_Sandro_2":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_101");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_102");
			link.l1.go = "EPL_Sandro_3";
		break;
		
		case "EPL_Sandro_3":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_103");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_104");
			link.l1.go = "EPL_Sandro_4";
		break;

		case "EPL_Sandro_4":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_105", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_106");
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EPL_GoToShip");
		break;
		
		case "EPL_Sandro_11":
			dialog.text = StringFromKey("EPL_1_Prologue_dialog_95");
			link.l1 = StringFromKey("EPL_1_Prologue_dialog_96");
			link.l1.go = "exit";
			RemoveLandQuestmark_Main(npchar, "EPL_Prologue");
			AddDialogExitQuestFunction("EPL_GoToBoat");
		break;
	}
}

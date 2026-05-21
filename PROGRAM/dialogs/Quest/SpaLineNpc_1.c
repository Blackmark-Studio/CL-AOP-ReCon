// диалоговый файл №1 на испанку
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	float locx, locy, locz;

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("SpaLineNpc_1_1");
			link.l1 = StringFromKey("SpaLineNpc_1_2");
			link.l1.go = "exit";

			//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
			//Квест №1, спасение трёх горожан.
			if (npchar.id == "SpaPrisoner1" || npchar.id == "SpaPrisoner2" || npchar.id == "SpaPrisoner3")
			{
				if (pchar.questTemp.State == "SaveFromMorgan_toPrison")
				{
					dialog.text = StringFromKey("SpaLineNpc_1_3", UpperFirst(GetAddress_Form(NPChar)));
					link.l1 = StringFromKey("SpaLineNpc_1_4");
					link.l1.go = "Step_S1_1";
				}
				else
				{
					dialog.text = StringFromKey("SpaLineNpc_1_8", LinkRandPhrase(
								StringFromKey("SpaLineNpc_1_5"),
								StringFromKey("SpaLineNpc_1_6"),
								StringFromKey("SpaLineNpc_1_7")));
					link.l1 = StringFromKey("SpaLineNpc_1_9");
					link.l1.go = "exit";
				}
			}
			if (pchar.questTemp.State == "TakeRockBras_toNearestMaracaibo")// квест №3, Рок Бриазилец в каюте на абордаже
			{
				dialog.text = StringFromKey("SpaLineNpc_1_10", pchar);
				link.l1 = StringFromKey("SpaLineNpc_1_11");
				link.l1.go = "Step_S3_1";
			}
			if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toTortuga")// квест №4, базар со слугой д'Эстре предварительный.
			{
				dialog.text = StringFromKey("SpaLineNpc_1_12", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("SpaLineNpc_1_13");
				link.l1.go = "exit";
			}
			if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toDEstre")// квест №4, базар со слугой д'Эстре
			{
				dialog.text = StringFromKey("SpaLineNpc_1_14", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("SpaLineNpc_1_15");
				link.l1.go = "Step_S4_1";
			}
			if (npchar.id == "ServantDEstre" && pchar.questTemp.State == "Sp4Detection_toDEstre_1")// квест №4, базар со слугой д'Эстре
			{
				dialog.text = StringFromKey("SpaLineNpc_1_16", UpperFirst(GetAddress_Form(NPChar)));
				link.l1 = StringFromKey("SpaLineNpc_1_17");
				link.l1.go = "exit";
			}
			if (npchar.id == "AnryDEstre")// квест №4, базар с самим д'Эстре
			{
				dialog.text = StringFromKey("SpaLineNpc_1_18");
				link.l1 = StringFromKey("SpaLineNpc_1_19");
				link.l1.go = "Step_S4_2";
			}
			if (npchar.id == "LaVega_Comendant") // ==>  квест №5, фантом Мэнсфилада при штурме Ла Веги
			{
				dialog.text = StringFromKey("SpaLineNpc_1_20");
				link.l1 = StringFromKey("SpaLineNpc_1_21");
				link.l1.go = "Step_S5_1";
			}
			if (npchar.id == "Boozer") // ==>  квест №6, базар с алкашом в таверне
			{
				dialog.text = StringFromKey("SpaLineNpc_1_22");
				link.l1 = StringFromKey("SpaLineNpc_1_23", pchar);
				link.l1.go = "Step_S6_1";
			}
			if (npchar.id == "Messanger" && pchar.questTemp.State == "Sp6TakeMess_waitMessanger") //квест №6, базар с голландским вестовым
			{
				dialog.text = StringFromKey("SpaLineNpc_1_24");
				link.l1 = StringFromKey("SpaLineNpc_1_25");
				link.l1.go = "Step_S6_8";
				link.l2 = StringFromKey("SpaLineNpc_1_26");
				link.l2.go = "Step_S6_11";
			}
			if (npchar.id == "Messanger" && pchar.questTemp.State == "Sp6TakeMess_Action") //квест №6, базар с голландским вестовым
			{
				dialog.text = StringFromKey("SpaLineNpc_1_27");
				link.l1 = StringFromKey("SpaLineNpc_1_28");
				link.l1.go = "Step_S6_13";
			}
			if (npchar.id == "OurCaptain_1") //квест №7, базар с Пардалем его на корабле до битвы
			{
				dialog.text = StringFromKey("SpaLineNpc_1_29");
				link.l1 = StringFromKey("SpaLineNpc_1_30");
				link.l1.go = "Exit";
			}
			if (npchar.id == "OurCaptain_1" && pchar.questTemp.State == "Sp7SavePardal_GoodWork") //квест №7, базар с Пардалем его на корабле
			{
				dialog.text = StringFromKey("SpaLineNpc_1_31", pchar);
				link.l1 = StringFromKey("SpaLineNpc_1_32", GetFullName(pchar));
				link.l1.go = "Step_S7_1";
			}
			if (npchar.id == "OurCaptain_1" && pchar.questTemp.State == "Sp7SavePardal_2GoodWork") //квест №7, базар с Пардалем его на корабле
			{
				dialog.text = StringFromKey("SpaLineNpc_1_33");
				link.l1 = StringFromKey("SpaLineNpc_1_34", pchar);
				link.l1.go = "exit";
			}
			if (npchar.id == "SpaTalkOfficer" && pchar.questTemp.State == "Sp10Maracaibo_TalkWithOfficer") //квест №10, базар c оффом на выходе
			{
				dialog.text = StringFromKey("SpaLineNpc_1_35");
				link.l1 = StringFromKey("SpaLineNpc_1_36");
				link.l1.go = "Step_S10_1";
			}

		break;
		//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//********************************* Спасение трёх горожан. Квест №1 **********************************
		case "Step_S1_1":
			dialog.text = StringFromKey("SpaLineNpc_1_37", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("SpaLineNpc_1_38");
			link.l1.go = "Step_S1_2";
		break;
		case "Step_S1_2":
			AddQuestRecord("Spa_Line_1_SaveCitizens", "2");
			pchar.questTemp.State = "SaveFromMorgan_OutOfPrison";
			for (i = 1; i <= 3; i++)
			{
				sld = characterFromId("SpaPrisoner" + i);
				ChangeCharacterAddressGroup(sld, "PortRoyal_Prison", "goto", "goto12");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false);
				RemoveLandQuestmark_Main(sld, "Spa_Line");
			}
			RemoveLandQuestmarkToFantoms_Main("JailOff", "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("spa_guber"), "Spa_Line");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		//********************************* Работа на инквизицию. Квест №3 **********************************
		case "Step_S3_1":
			dialog.text = StringFromKey("SpaLineNpc_1_39");
			link.l1 = StringFromKey("SpaLineNpc_1_40");
			link.l1.go = "Step_S3_2";
		break;
		case "Step_S3_2":
			dialog.text = StringFromKey("SpaLineNpc_1_41");
			link.l1 = StringFromKey("SpaLineNpc_1_42");
			link.l1.go = "Step_S3_3";
		break;
		case "Step_S3_3":
			dialog.text = StringFromKey("SpaLineNpc_1_43");
			link.l1 = StringFromKey("SpaLineNpc_1_44");
			link.l1.go = "Step_S3_4";
		break;
		case "Step_S3_4":
			pchar.questTemp.State = "TakeRockBras_RockTaken";
			AddQuestRecord("Spa_Line_3_RockBrasilian", "5");
			pchar.quest.TakeRockBras_DieHard.over = "yes";
			Island_SetReloadEnableGlobal("Maracaibo", true);
			QuestAboardCabinDialogQuestSurrender();
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
			AddLandQuestmark_Main(CharacterFromID("Santiago_Inquisitor"), "Spa_Line");
		break;
		//********************************* Расследование убийства. Квест №4 **********************************
		case "Step_S4_1":
			dialog.text = StringFromKey("SpaLineNpc_1_45");
			link.l1 = StringFromKey("SpaLineNpc_1_46");
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp4Detection_toDEstre_1";
			pchar.quest.Sp4Detection_Race_1.win_condition.l1 = "location";
			pchar.quest.Sp4Detection_Race_1.win_condition.l1.location = "Tortuga_town";
			pchar.quest.Sp4Detection_Race_1.win_condition = "Sp4Detection_Race_1";
			NPChar.LifeDay = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_S4_2":
			dialog.text = StringFromKey("SpaLineNpc_1_47");
			link.l1 = StringFromKey("SpaLineNpc_1_48", pchar, GetFullName(pchar));
			link.l1.go = "Step_S4_3";
		break;
		case "Step_S4_3":
			dialog.text = StringFromKey("SpaLineNpc_1_49", pchar);
			link.l1 = StringFromKey("SpaLineNpc_1_50");
			link.l1.go = "Step_S4_4";
		break;
		case "Step_S4_4":
			dialog.text = StringFromKey("SpaLineNpc_1_51");
			link.l1 = StringFromKey("SpaLineNpc_1_52", pchar);
			link.l1.go = "Step_S4_5";
		break;
		case "Step_S4_5":
			dialog.text = StringFromKey("SpaLineNpc_1_53");
			link.l1 = StringFromKey("SpaLineNpc_1_54");
			link.l1.go = "Step_S4_6";
		break;
		case "Step_S4_6":
			dialog.text = StringFromKey("SpaLineNpc_1_55", pchar);
			link.l1 = StringFromKey("SpaLineNpc_1_56", pchar);
			link.l1.go = "Step_S4_7";
		break;
		case "Step_S4_7":
			dialog.text = StringFromKey("SpaLineNpc_1_57", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("SpaLineNpc_1_58");
			link.l1.go = "Step_S4_8";
		break;
		case "Step_S4_8":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.State = "Sp4Detection_toDEstre_2";
			LAi_SetHP(npchar, 300, 300);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Sp4Detection_YouWin");
			NPChar.LifeDay = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		//********************************* Уничтожение Ла Веги. Квест №5 **********************************
		case "Step_S5_1":
			dialog.text = StringFromKey("SpaLineNpc_1_59", pchar);
			link.l1 = StringFromKey("SpaLineNpc_1_60");
			link.l1.go = "Step_S5_2";
			// AfterTownBattle();
		break;
		case "Step_S5_2":
			LAi_SetPlayerType(pchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_TmpEnemy);
			LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "Sp5LaVegaAttack_AfterFight");
			NPChar.LifeDay = 0;
			SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
//			SetReturn_Gover_Dialog_Exit(NPChar);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//********************************* Перехват посыльного Сювесанта. Квест №6 **********************************
		case "Step_S6_1": //алкаш
			dialog.text = StringFromKey("SpaLineNpc_1_61");
			link.l1 = StringFromKey("SpaLineNpc_1_62");
			link.l1.go = "Step_S6_2";
		break;
		case "Step_S6_2":
			dialog.text = StringFromKey("SpaLineNpc_1_63");
			link.l1 = StringFromKey("SpaLineNpc_1_64");
			link.l1.go = "Step_S6_3";
		break;
		case "Step_S6_3":
			dialog.text = StringFromKey("SpaLineNpc_1_65");
			link.l1 = StringFromKey("SpaLineNpc_1_66");
			link.l1.go = "Step_S6_4";
		break;
		case "Step_S6_4":
			dialog.text = StringFromKey("SpaLineNpc_1_67");
			link.l1 = StringFromKey("SpaLineNpc_1_68");
			link.l1.go = "Step_S6_5";
		break;
		case "Step_S6_5":
			dialog.text = StringFromKey("SpaLineNpc_1_69");
			link.l1 = StringFromKey("SpaLineNpc_1_70");
			link.l1.go = "Step_S6_6";
			AddMoneyToCharacter(pchar, -100);
		break;
		case "Step_S6_6":
			pchar.questTemp.State = "Sp6TakeMess_Action";
			AddQuestRecord("Spa_Line_6_TakeMessangeer", "4");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Tortuga_tavern", "tables", LAi_FindNearestFreeLocator("tables", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
			Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition.l1 = "location";
			Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition.l1.location = "Tortuga_tavern_upstairs";
			Pchar.quest.Sp6TakeMess_WaitMessanger.win_condition = "Sp6TakeMess_WaitMessanger";
			pchar.quest.Sp6TakeMess_Interception.over = "yes";
			LocatorReloadEnterDisable("Tortuga_tavern", "reload1_back", true);
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		//=====>>> вестовой при попытке взять его в городе.
		case "Step_S6_11":
			dialog.text = StringFromKey("SpaLineNpc_1_71");
			link.l1 = StringFromKey("SpaLineNpc_1_72");
			link.l1.go = "Step_S6_7";
		break;
		case "Step_S6_7":
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS");
			LAi_group_Attack(NPChar, Pchar);
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		case "Step_S6_8":
			dialog.text = NPCStringReactionRepeat(
						StringFromKey("SpaLineNpc_1_73"),
						StringFromKey("SpaLineNpc_1_74"),
						StringFromKey("SpaLineNpc_1_75", pchar), "none", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(
						StringFromKey("SpaLineNpc_1_76"),
						StringFromKey("SpaLineNpc_1_77"),
						StringFromKey("SpaLineNpc_1_78"), "none", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("Step_S6_9", "Step_S6_12", "Step_S6_7", "none", npchar, Dialog.CurrentNode);
		break;
		case "Step_S6_9":
			dialog.text = StringFromKey("SpaLineNpc_1_79");
			link.l1 = StringFromKey("SpaLineNpc_1_80");
			link.l1.go = "Step_S6_10";
		break;
		case "Step_S6_10":
			dialog.text = StringFromKey("SpaLineNpc_1_81");
			link.l1 = StringFromKey("SpaLineNpc_1_82");
			link.l1.go = "Step_S6_12";
		break;
		case "Step_S6_12":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2_back", "none", "", "", "Sp6TakeMess_MessengerOut", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			DialogExit();
		break;
		//=====>>> вестовой захвате в комнате таверны.
		case "Step_S6_13":
			dialog.text = StringFromKey("SpaLineNpc_1_83");
			link.l1 = StringFromKey("SpaLineNpc_1_84");
			link.l1.go = "Step_S6_14";
		break;
		case "Step_S6_14":
			dialog.text = StringFromKey("SpaLineNpc_1_85");
			link.l1 = StringFromKey("SpaLineNpc_1_86");
			link.l1.go = "Step_S6_15";
		break;
		case "Step_S6_15":
			bDisableFastReload = false; // открыть переходы.
			LocatorReloadEnterDisable("Tortuga_tavern", "reload1_back", false);
			LAi_SetPlayerType(pchar);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//********************************* Спасение Пардаля. Квест №7 **********************************
		case "Step_S7_1":
			dialog.text = StringFromKey("SpaLineNpc_1_87");
			link.l1 = StringFromKey("SpaLineNpc_1_88", pchar);
			link.l1.go = "Step_S7_2";
		break;
		case "Step_S7_2":
			dialog.text = StringFromKey("SpaLineNpc_1_89");
			link.l1 = StringFromKey("SpaLineNpc_1_90");
			link.l1.go = "exit";
			pchar.questTemp.State = "Sp7SavePardal_2GoodWork";
			RemoveLandQuestmark_Main(npchar, "Spa_Line");
		break;
		//********************************* Спасение Пардаля. Квест №7 **********************************
		case "Step_S10_1":
			dialog.text = StringFromKey("SpaLineNpc_1_91");
			link.l1 = StringFromKey("SpaLineNpc_1_92");
			link.l1.go = "Step_S10_2";
		break;
		case "Step_S10_2":
			dialog.text = StringFromKey("SpaLineNpc_1_93");
			link.l1 = StringFromKey("SpaLineNpc_1_94");
			link.l1.go = "Step_S10_3";
		break;
		case "Step_S10_3":
			dialog.text = StringFromKey("SpaLineNpc_1_95", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("SpaLineNpc_1_96");
			link.l1.go = "Step_S10_4";
		break;
		case "Step_S10_4":
			pchar.questTemp.State = "Sp10Maracaibo_toGovernor";
			AddQuestRecord("Spa_Line_10_Maracaibo", "2");
			AddQuestUserData("Spa_Line_10_Maracaibo", "sSex", GetSexPhrase("", "а"));
			LocatorReloadEnterDisable("Maracaibo_town", "gate_back", true);
			LocatorReloadEnterDisable("Maracaibo_town", "reload1_back", true);
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload3_back", "none", "", "", "", -1);
			DialogExit();
			AddLandQuestmark_Main(CharacterFromID("Maracaibo_Mayor"), "Spa_Line");
		break;

	}
}

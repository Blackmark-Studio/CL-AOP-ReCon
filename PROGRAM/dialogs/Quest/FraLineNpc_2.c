// диалоговый файл №2 на фр. линейку
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	float locx, locy, locz;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = StringFromKey("FraLineNpc_2_1");
			link.l1 = StringFromKey("FraLineNpc_2_2");
			link.l1.go = "exit";

			//>>>>>>>>>>>>========= Разброс диалогов по персонажам =====================
			//Квест №1, сопровождение Леграна.
			if (pchar.questTemp.State == "Fr1Legran_toLeMaren")// квест №1, базар с бандиами
			{
				dialog.text = StringFromKey("FraLineNpc_2_3", pchar);
				link.l1 = StringFromKey("FraLineNpc_2_4");
				link.l1.go = "Step_F1_1";
			}
			//Квест №2, доставка письма в Кюрасао.
			if (pchar.questTemp.State == "Fr2Letter_Arrest")// квест №2, базар с охраной при аресте
			{
				dialog.text = StringFromKey("FraLineNpc_2_5");
				link.l1 = StringFromKey("FraLineNpc_2_6");
				link.l1.go = "Step_F2_1";
			}
			if (pchar.questTemp.State == "Fr2Letter_PrisonTalk")// квест №2, базар с тюремщиком
			{
				dialog.text = StringFromKey("FraLineNpc_2_7", pchar);
				link.l1 = StringFromKey("FraLineNpc_2_8");
				link.l1.go = "Step_F2_2";
			}
			if (pchar.questTemp.State == "Fr2Letter_VisitGovernor")// квест №2, базар с фантомом губера в тюрьме
			{
				dialog.text = StringFromKey("FraLineNpc_2_9");
				link.l1 = StringFromKey("FraLineNpc_2_10");
				link.l1.go = "Step_F2_8";
			}
			if (pchar.questTemp.State == "Fr2Letter_SeekProblems")// квест №2, базар с кэпом галеона, абордаж
			{
				dialog.text = StringFromKey("FraLineNpc_2_11", pchar);
				link.l1 = StringFromKey("FraLineNpc_2_12");
				link.l1.go = "Step_F2_12";
			}
			if (npchar.id == "AnnaDeLeiva")// квест №3, донна Анна в спальне
			{
				dialog.text = StringFromKey("FraLineNpc_2_13");
				link.l1 = StringFromKey("FraLineNpc_2_14", pchar);
				link.l1.go = "Step_F3_1";
			}
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_toHavana")// квест №5, Инесс
			{
				dialog.text = StringFromKey("FraLineNpc_2_15", UpperFirst(GetAddress_Form(NPChar)));
				link.l1 = StringFromKey("FraLineNpc_2_16", pchar);
				link.l1.go = "Step_F5_1";
			}
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_SeekHoseBrothers")
			{
				dialog.text = StringFromKey("FraLineNpc_2_17", GetAddress_Form(NPChar));
				link.l1 = StringFromKey("FraLineNpc_2_18");
				link.l1.go = "exit";
			}
			if (npchar.id == "InesDeLasCierras" && pchar.questTemp.State == "Fr5AnnaHant_GoodWork")
			{
				dialog.text = StringFromKey("FraLineNpc_2_19");
				link.l1 = StringFromKey("FraLineNpc_2_20");
				link.l1.go = "Step_F5_4";
			}
			if (npchar.id == "Captain_1" || npchar.id == "Captain_2")//квест №6, базар с кэпами
			{
				dialog.text = StringFromKey("FraLineNpc_2_21", UpperFirst(GetAddress_Form(NPChar)));
				link.l1 = StringFromKey("FraLineNpc_2_22");
				link.l1.go = "exit";
			}
			if (npchar.id == "RockBrasilian" && pchar.questTemp.State == "Fr7RockBras_toSeekPlace")//квест №7, базар с Бразильцем. 
			{
				dialog.text = NPCStringReactionRepeat(
							StringFromKey("FraLineNpc_2_23"),
							StringFromKey("FraLineNpc_2_24", pchar),
							StringFromKey("FraLineNpc_2_25", pchar),
							StringFromKey("FraLineNpc_2_26", pchar), "block", 0, npchar, Dialog.CurrentNode);
				if (LAi_group_GetTarget(pchar) <= 0)
				{
					link.l1 = HeroStringReactionRepeat(
								StringFromKey("FraLineNpc_2_27", pchar, GetFullName(pchar)),
								StringFromKey("FraLineNpc_2_28", pchar, GetFullName(pchar)),
								StringFromKey("FraLineNpc_2_29", pchar, GetFullName(pchar)),
								StringFromKey("FraLineNpc_2_30", pchar, GetFullName(pchar)), npchar, Dialog.CurrentNode);
					link.l1.go = "Step_F7_1";
				}
				else
				{
					link.l1 = StringFromKey("FraLineNpc_2_31");
					link.l1.go = "Step_F7_Late";
				}
				// --> типа опоздал...
				if (GetQuestPastDayParam("questTemp") > 8)
				{
					dialog.text = StringFromKey("FraLineNpc_2_32");
					link.l1 = StringFromKey("FraLineNpc_2_33", pchar);
					link.l1.go = "Step_F7_8";
				}
				else SaveCurrentQuestDateParam("questTemp"); //чтобы не глюкнуло во время боя
				// <-- типа опоздал...
			}
			if (npchar.id == "RockBrasilian" && pchar.questTemp.State == "empty")//квест №7, базар с Бразильцем в резиденции дОжерона. 
			{
				dialog.text = StringFromKey("FraLineNpc_2_34");
				link.l1 = StringFromKey("FraLineNpc_2_35");
				link.l1.go = "Step_F7_5";
			}
			if (npchar.id == "CaptainGay")//квест №8, базар с кэпом Геем. 
			{
				dialog.text = StringFromKey("FraLineNpc_2_36", pchar);
				link.l1 = StringFromKey("FraLineNpc_2_37");
				link.l1.go = "Step_F8_1";
			}
		break;
		//<<<<<<<<<<<<===== Разброс диалогов по персонажам =====================
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		//********************************* Спасение трёх горожан. Квест №1 **********************************
		case "Step_F1_1":
			dialog.text = StringFromKey("FraLineNpc_2_38", pchar);
			link.l1 = StringFromKey("FraLineNpc_2_39");
			link.l1.go = "Step_F1_2";
		break;
		case "Step_F1_2":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_SetPlayerType(pchar);
			sld = characterFromId("Legran");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "Fr1Legran_afterFightBandits");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//********************************* Арест ГГ у Стэвезанта. Квест №2 **********************************
		case "Step_F2_1":
			bDisableCharacterMenu = true; //закрываем Ф2
			LAi_SetPlayerType(pchar);
			DoReloadCharacterToLocation("Villemstad_prison", "goto", "goto9");
			pchar.questTemp.money = sti(pchar.money) / 2;
			if (IsEquipCharacterByItem(pchar, FindCharacterItemByGroup(pchar, CIRASS_ITEM_TYPE))) // Hokkins: если на главном герое надета кираса, то снимем её тоже.
			{
				RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
			}
			RemoveCharacterEquip(pchar, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(pchar, GUN_ITEM_TYPE);
			RemoveCharacterEquip(pchar, MUSKET_ITEM_TYPE);
			RemoveCharacterEquip(pchar, SPYGLASS_ITEM_TYPE);
			pchar.money = 0;
			DoQuestCheckDelay("Fr2Letter_intoPrison_1", 20);
			AddQuestRecord("Fra_Line_2_DelivLetter", "2");
			AddQuestUserData("Fra_Line_2_DelivLetter", "sSex", GetSexPhrase(StringFromKey("SexPhrase_7"), StringFromKey("SexPhrase_8")));
			DialogExit();
		break;
		case "Step_F2_2":
			dialog.text = StringFromKey("FraLineNpc_2_40");
			link.l1 = StringFromKey("FraLineNpc_2_41");
			link.l1.go = "Step_F2_3";
		break;
		case "Step_F2_3":
			dialog.text = StringFromKey("FraLineNpc_2_42");
			link.l1 = StringFromKey("FraLineNpc_2_43", pchar);
			link.l1.go = "Step_F2_4";
		break;
		case "Step_F2_4":
			dialog.text = StringFromKey("FraLineNpc_2_44");
			link.l1 = StringFromKey("FraLineNpc_2_45");
			link.l1.go = "Step_F2_5";
		break;
		case "Step_F2_5":
			dialog.text = StringFromKey("FraLineNpc_2_46");
			link.l1 = StringFromKey("FraLineNpc_2_47", pchar);
			link.l1.go = "Step_F2_6";
		break;
		case "Step_F2_6":
			dialog.text = StringFromKey("FraLineNpc_2_48");
			link.l1 = StringFromKey("FraLineNpc_2_49");
			link.l1.go = "Step_F2_7";
		break;
		case "Step_F2_7":
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", 10);
			DialogExit();
			DoQuestCheckDelay("Fr2Letter_intoPrison_3", 10);
		break;
		case "Step_F2_8":
			dialog.text = StringFromKey("FraLineNpc_2_50");
			link.l1 = StringFromKey("FraLineNpc_2_51", pchar);
			link.l1.go = "Step_F2_9";
		break;
		case "Step_F2_9":
			dialog.text = StringFromKey("FraLineNpc_2_52");
			link.l1 = StringFromKey("FraLineNpc_2_53");
			link.l1.go = "Step_F2_10";
		break;
		case "Step_F2_10":
			dialog.text = StringFromKey("FraLineNpc_2_54");
			link.l1 = StringFromKey("FraLineNpc_2_55");
			link.l1.go = "exit";
			bDisableCharacterMenu = false; //открываем Ф2
			AddDialogExitQuestFunction("FrLine_HoverGoOnPrison");
		break;

		case "Step_F2_12":
			dialog.text = StringFromKey("FraLineNpc_2_56", GetFullName(npchar));
			link.l1 = StringFromKey("FraLineNpc_2_57", pchar);
			link.l1.go = "Step_F2_13";
		break;
		case "Step_F2_13":
			AddQuestRecord("Fra_Line_2_DelivLetter", "5");
			LAi_SetCurHPMax(npchar);
			QuestAboardCabinDialogExitWithBattle("");
			pchar.questTemp.State = "Fr2Letter_NiceResult";
			AddLandQuestmark_Main(CharacterFromID("hol_guber"), "Fra_Line");
			DialogExit();
		break;
		//********************************* Похищение донны Анны. Квест №3 **********************************
		case "Step_F3_1":
			dialog.text = StringFromKey("FraLineNpc_2_58");
			link.l1 = StringFromKey("FraLineNpc_2_59", pchar);
			link.l1.go = "Step_F3_2";
		break;
		case "Step_F3_2":
			pchar.questTemp.State = "Fr3TakeAnna_HavanaOut";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition.l1 = "location";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition.l1.location = "Cuba2";
			Pchar.quest.Fr3TakeAnna_DelivShip.win_condition = "Fr3TakeAnna_DelivShip";

			Pchar.quest.Fr3TakeAnna_DelivShip2.win_condition.l1 = "location"; // TODO > win_condition.l2 = "location" не работает
			Pchar.quest.Fr3TakeAnna_DelivShip2.win_condition.l1.location = "Cuba1";
			Pchar.quest.Fr3TakeAnna_DelivShip2.win_condition = "Fr3TakeAnna_DelivShip";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		//********************************* Проблемы донны Анны. Квест №5 **********************************
		case "Step_F5_1":
			dialog.text = StringFromKey("FraLineNpc_2_60", UpperFirst(GetAddress_Form(NPChar)));
			link.l1 = StringFromKey("FraLineNpc_2_61");
			link.l1.go = "Step_F5_2";
		break;
		case "Step_F5_2":
			dialog.text = StringFromKey("FraLineNpc_2_62", GetAddress_Form(NPChar));
			link.l1 = StringFromKey("FraLineNpc_2_63");
			link.l1.go = "Step_F5_3";
		break;
		case "Step_F5_3":
			dialog.text = StringFromKey("FraLineNpc_2_64");
			link.l1 = StringFromKey("FraLineNpc_2_65", pchar);
			link.l1.go = "exit";
			pchar.questTemp.State = "Fr5AnnaHant_SeekHoseBrothers";
			AddQuestRecord("Fra_Line_5_KillAnnaHanters", "3");
			AddQuestUserData("Fra_Line_5_KillAnnaHanters", "sSex", GetSexPhrase("", "а"));
			AddQuestUserData("Fra_Line_5_KillAnnaHanters", "sSex1", GetSexPhrase("ен", "на"));

			npchar.LifeDay = 1; // уберем нпс
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
			locations[FindLocation("Mayak10")].DisableEncounters = true; //энкаутеры закроем
			LAi_LocationDisableOfficersGen("Mayak10", true); //офицеров не пускать
			Pchar.quest.Fr5Anna_InShore.win_condition.l1 = "location";
			Pchar.quest.Fr5Anna_InShore.win_condition.l1.location = "Mayak10";
			Pchar.quest.Fr5Anna_InShore.win_condition = "Fr5Anna_InShore";
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		case "Step_F5_4":
			dialog.text = StringFromKey("FraLineNpc_2_66");
			link.l1 = StringFromKey("FraLineNpc_2_67");
			link.l1.go = "exit";
		break;
		//********************************* Вызволение Рока Бразильца. Квест №7 **********************************
		case "Step_F7_1":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = StringFromKey("FraLineNpc_2_68", pchar);
				link.l1 = StringFromKey("FraLineNpc_2_69");
				link.l1.go = "Step_F7_2";
			}
			else
			{
				dialog.text = StringFromKey("FraLineNpc_2_70");
				link.l1 = StringFromKey("FraLineNpc_2_71");
				link.l1.go = "Step_F7_Late";
			}
		break;
		case "Step_F7_2":
			if (LAi_group_GetTarget(pchar) <= 0)
			{
				dialog.text = StringFromKey("FraLineNpc_2_72");
				link.l1 = StringFromKey("FraLineNpc_2_73");
				link.l1.go = "Step_F7_3";
			}
			else
			{
				dialog.text = StringFromKey("FraLineNpc_2_74");
				link.l1 = StringFromKey("FraLineNpc_2_75");
				link.l1.go = "Step_F7_Late";
			}
		break;
		case "Step_F7_3":
			dialog.text = StringFromKey("FraLineNpc_2_76");
			link.l1 = StringFromKey("FraLineNpc_2_77");
			link.l1.go = "Step_F7_4";
		break;
		case "Step_F7_4":
			bDisableFastReload = false;
			AddQuestRecord("Fra_Line_7_RockBras", "2");
			AddQuestUserData("Fra_Line_7_RockBras", "sSex", GetSexPhrase("ёл", "ла"));
			Pchar.quest.Fr7RockBras_DelivShip.win_condition.l1 = "location";
			Pchar.quest.Fr7RockBras_DelivShip.win_condition.l1.location = "Cuba1";
			Pchar.quest.Fr7RockBras_DelivShip.win_condition = "Fr7RockBras_DelivShip";
			LAi_SetActorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
		break;
		case "Step_F7_5":
			dialog.text = StringFromKey("FraLineNpc_2_78");
			link.l1 = StringFromKey("FraLineNpc_2_79");
			link.l1.go = "Step_F7_6";
		break;
		case "Step_F7_6":
			dialog.text = StringFromKey("FraLineNpc_2_80", pchar);
			link.l1 = StringFromKey("FraLineNpc_2_81");
			link.l1.go = "Step_F7_7";
		break;
		case "Step_F7_7":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "none", "", "", "", 6.0);
			DeleteAttribute(npchar, "RebirthPhantom");
			npchar.LifeDay = 0; // уберем нпс
			pchar.GenQuestRandItem.FortFrance_Dungeon = true;
			pchar.GenQuestRandItem.FortFrance_Dungeon.randitem3 = "cirass5";
			DialogExit();
		break;
		case "Step_F7_8":
			dialog.text = StringFromKey("FraLineNpc_2_82", pchar);
			link.l1 = StringFromKey("FraLineNpc_2_83");
			link.l1.go = "Step_F7_9";
		break;
		case "Step_F7_9":
			bDisableFastReload = true;
			LAi_KillCharacter(npchar);
			DeleteAttribute(npchar, "RebirthPhantom");
			npchar.LifeDay = 0; // уберем нпс
			pchar.questTemp.State = "Fr7RockBras_RockIsAgony";
			DialogExit();
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Santiago_Priest"), "Fra_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Beliz_tavernkeeper"), "Fra_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Havana_tavernkeeper"), "Fra_Line");
			RemoveLandQuestmark_Main(CharacterFromID("SantoDomingo_tavernkeeper"), "Fra_Line");
			RemoveLandQuestmark_Main(CharacterFromID("Santiago_tavernkeeper"), "Fra_Line");
			AddLandQuestmark_Main(CharacterFromID("fra_guber"), "Fra_Line");
		break;
		case "Step_F7_Late":
			bDisableFastReload = true;
			LAi_ActorWaitDialog(npchar, pchar);
			DialogExit();
		break;
		//********************************* Объехать трёх корсаров. Квест №8 **********************************
		case "Step_F8_1":
			dialog.text = StringFromKey("FraLineNpc_2_84");
			link.l1 = StringFromKey("FraLineNpc_2_85");
			link.l1.go = "Step_F8_2";
		break;
		case "Step_F8_2":
			chrDisableReloadToLocation = true;
			LocatorReloadEnterDisable("PortRoyal_tavern", "reload2_back", true);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "CanFightCurLocation");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			RemoveLandQuestmark_Main(npchar, "Fra_Line");
			RemoveLandQuestmark_Main(CharacterFromID("PortRoyal_tavernkeeper"), "Fra_Line");
		break;

	}
}
